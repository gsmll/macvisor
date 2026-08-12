# Security findings log

Append-only log of security-relevant observations made during decompilation.
Format per AGENTS.md 'Security findings log'. Each entry labels severity as a
hypothesis, never a claim, and carries Ghidra evidence.

---

## [entitlements] fffffe000b985ae4 hv_entitlement_tier

- **Observation**: The entitlement tier gate is entirely client-visible: the
  hypervisor trusts the calling process's own entitlement strings. The
  vmapple tier (3) and private-hypervisor tier (4) both elevate the returned
  level, and tier 4 additionally requires the kernel-config flag
  DAT_fffffe0007e255f8 bit 0x1010. There is no per-call re-validation that the
  tier is still current; the caller's cred is read fresh each call via
  per_cpu_base(FUN_fffffe000b866ec4) + FUN_fffffe000b8663e8 (current_task),
  but the tier value returned is used by the caller to size capabilities.
- **Evidence**: three `(*(uint64_t **)DAT_fffffe0007e93310)[0x38](cred,
  "<entitlement>")` probes — i.e. the double deref `*(*(0x7e93310)+0x1c0)`,
  a boot-resolved probe — against com.apple.security.hypervisor (level 1),
  com.apple.private.hypervisor.vmapple (level 3), com.apple.private.hypervisor
  (level 4 with DAT_fffffe0007e255f8 & 0x1010). No bounds/TOCTOU check on the
  returned tier between probe and use.
- **Severity (hypothesis)**: low — entitlement checks are the intended gate;
  the risk is a mis-scoped caller getting tier 3 when it only holds the base
  entitlement (probe-returned `has_security` fallback), not a privilege
  bypass.
- **Confidence**: medium — the tier encoding (0/1/3/4) is inferred, not
  independently verified.

## [entitlements] fffffe000b987d9c hv_caps_feature_mask

- **Observation**: The capability feature mask is built from the caller's
  entitlement tier, but for tiers < 2 the function falls back to a *default*
  mask (2) when `per_cpu_base`/`current_task` returns NULL or the
  com.apple.private.virtualization probe fails — i.e. a NULL/task-resolution
  failure yields a non-zero capability set rather than an explicit deny.
- **Evidence**: `uVar9 = 2; mask[0xd] = 2;` then `if (lVar3==0) uVar9 = 2;`
  else probe `com.apple.private.virtualization` -> `uVar9 = 0x202` or 2.
  Mask words are then OR'ed with capability bits (mask[0]|0x100000 etc.).
- **Severity (hypothesis)**: informational — defaulting to tier-2-like caps on
  an entitlement-probe failure could over-grant a caller whose task lookup
  failed; but tier<2 callers already hold only a weak entitlement.
- **Confidence**: medium — the NULL path value (2 vs 0) is decompiler-derived
  and the semantic of capability word bits is unverified.

## [entitlements] fffffe000b988038 hv_caps_cpu_report

- **Observation**: The CPU/memory report writes unvalidated feature words read
  straight from per-CPU cache/topology tables (PTR_PTR_fffffe000c5b3f58/60/68)
  and ID registers into a caller-visible 0x1b3-byte block. The cache
  block-size field at +0x1a1/+0x1a9 is computed as `0x40 - (size & 0x3f)`;
  if a page-size table entry reported a block size >= 0x40 this underflows to
  a huge shift value reported to the caller.
- **Evidence**: `lVar10 = 0x40 - (*(ulong *)(puVar9 + 0x50) & 0x3f);` stored to
  `*(long *)(report + 0x1a1)` / `+0x1a9`. No upper-bound check on the table
  value before subtraction.
- **Severity (hypothesis)**: informational/low — the value is derived from
  trusted per-CPU topology tables (kernel-set), so an attacker would need to
  corrupt kernel data first; but a defensive caller should clamp.
- **Confidence**: low — the topology-table contents are kernel-owned and
  presumed sane.

## [hv-deps] fffffe000c0f8cfc osmeta_reserved_slot_panic (NOT an entitlement probe)

- **Observation**: CORRECTED 2026-08-12 — this address is NOT the sandbox
  entitlement probe (the earlier cred_has_entitlement de-guess was wrong). It
  is the OSMetaClass reserved-virtual-slot panic stub: calling it panics the
  kernel. Decoded body (Ghidra mis-bounds it as a single 4-byte `pacibsp`):
  `pacibsp; stp x29,x30,[sp,#-0x10]!; mov x29,sp; adrp/add x0,#0xfffffe000c680fc8;
  mov w1,#N; bl c0f7394`. The helper c0f7394 (0x64 B) calls the class's
  authenticated vtable+0x168 hook (`ldr x8,[*(x0+0x18)]; autda; add #0x168;
  ldr x8; blraa`) then panics `"%s::_RESERVED%s%d called. @%s:%d"` (string
  0xfffffe00070d811f) with `OSMetaClass.cpp` (0xfffffe00070d7f79) line
  0x57e=1406. The 100+ data xrefs are IOKit class vtables sharing the stub
  for their reserved slots — not entitlement tables.
- **Evidence**: raw bytes at fffffe000c0f8cfc: `7f2303d5` (pacibsp 0xd503237f);
  disassembly of the 0x1c-byte stub and of c0f7394; panic format + file/line
  strings read at 0xfffffe00070d811f / 0xfffffe00070d7f79; consecutive vtables
  at 0x7e4...–0x7f0... share the same stub addresses.
- **The actual entitlement probe** the hypervisor uses (hv_entitlement_tier
  b985ae4) is `*(*(0x7e93310)+0x1c0)(task, entitlement)` — a boot-time-filled
  auth pointer (static image value 0 at 0x7e93310), so its identity is not
  statically resolvable. hv_entitlements.c's `==0`-means-entitled contract
  applies to THAT probe, not to c0f8cfc.
- **Severity (hypothesis)**: informational — a reserved-slot call is a panic
  by design (fail-stop for ABI misuse); the earlier finding's "universal
  entitlement choke point" concern is unfounded because the probe is
  boot-resolved, not this stub.
- **Confidence**: high — stub + helper + panic strings fully decoded.

## [entitlements] fffffe0007e0d7f0 quota consumption (boot-arg / quota)

- **Observation**: The ISA VM quota is written by hv_support_init into
  DAT_fffffe0007e0d7f0/7f4/7f8 and the derived pool DAT_fffffe000c5b83b0-b8,
  clamped to INT_MAX (0x7fffffff). The quota boot-arg override path
  (hv_apple_isa_vm_quota) applies the *unclamped* parsed value directly when
  the enable bit DAT_fffffe0007e255f8 bit 4 is set, bypassing the INT_MAX
  clamp. Consumers (hv_vm_create b985588, hv_vcpu_object_release b98533c)
  decrement the pool.
- **Evidence**: hv_support.c: `quota = (quota < 0x80000000u) ? quota :
  0x7fffffff;` for the DT path; the boot-arg path
  `rc = FUN_fffffe000c09cbf0(...); if (rc) { DAT_fffffe000c5b83b0 = boot_quota;
  ... }` stores boot_quota unclamped.
- **Severity (hypothesis)**: low — an unclamped boot-arg quota could let the
  pool exceed INT_MAX and wrap the decrement-based accounting; requires an
  entitlement-gated caller plus a privileged boot-arg, so low impact.
- **Confidence**: medium — the clamp is applied only in the DT branch per the
  decompile; the exact quota-consumption arithmetic in the other trees is not
  re-audited here.

## [hv-deps] fffffe000b78fb24 waitq_validate

- **Observation**: waitq_validate gates its acceptance of a waitq pointer
  almost entirely on a single zone-header magic value (0x15) read from the
  zone slot `(waitq >> 10)`. The accompanying address-range test decompiles to
  a never-true conjunction (`(x < 0xffffffffffffff70) && (x ==
  0xffffffffffffff70)`), so in the recreated logic only the 0x15 magic check
  actually guards the path that registers the embedded lock. If a caller can
  supply a pointer whose zone slot carries a spoofed 0x15 magic, the waitq's
  lock at +0x14 is registered against the global table without a strong
  bounds/liveness check.
- **Evidence**: `if ( ((waitq|0xf...) < 0xffffffffffffff70) &&
  ((waitq|0xf...) == 0xffffffffffffff70) && ((*(ushort*)((waitq>>10)&0xffffffff0)
  & 0x3ff)==0x15) ) { FUN_fffffe000b7f78ec(waitq+0x14, &PTR_s_waitq_fffffe0007d7c8f0); }`
  else `FUN_fffffe000c0eae24(0x15, waitq)` (noreturn panic). Only the magic
  term is reachable.
- **Severity (hypothesis)**: informational/low — the panic path still traps
  non-matching objects, and a spoofed zone magic requires prior kernel memory
  corruption; noted because the effective validation is magic-only.
- **Confidence**: low — the never-true conjunction is a Ghidra artifact of the
  tagged-address range check, so the true range validation may be stronger in
  the real code.

## [hv-deps] fffffe000b7e0d8c hv_object_lookup

- **Observation**: The container object-lookup bounds its type-table index
  (`DAT_fffffe0007d78658 + type*0x28`) with `SoftwareBreakpoint(0xbffc)` assert
  traps only. The index uses the full low 32 bits of `type`
  (`param_3 & 0xffffffff`), and the only guard is `if (0x30 < (uint)param_3)
  SoftwareBreakpoint(...)`. If that brk is compiled out or skipped in a
  non-assert build, a type with low-32 value > 0x30 indexes the table out of
  bounds; the table base/entry stride (0x28) is trusted from kernel data. Also
  the container's own present/dead bits (0x700/0x10000) are assert-checked
  rather than error-returned.
- **Evidence**: `if (0x30 < (uint)param_3) { SoftwareBreakpoint(0xbffc, ...); }`;
  `*(uint16_t*)(&DAT_fffffe0007d78658 + (param_3 & 0xffffffff) * 0x28)`. Assert
  sites at fffffe000b7e0e8c/e98/ea4/eb0/f30.
- **Severity (hypothesis)**: low — in a release kernel the brk is a trap that
  faults the CPU, not a graceful error return; an OOB type would require a
  corrupted or hostile container state first. Noted as an assert-only bounds
  pattern that a defensive caller (the hypervisor, via FUN_fffffe000b985e38)
  should not rely on for privilege separation.
- **Confidence**: low — whether release kernels keep the brk (panicking) or
  elide it is unverified; the assert pattern is what the decompiler shows.

## [hv-deps] fffffe000b95c144 copyin (recreated 2026-08-12)

- **Observation**: The universal copyin enforces a user-range bounds check
  against the current task's address-space spec before copying
  (`src < as->min` or `as->max < src+len` → returns 0xe EFAULT), and it
  special-cases a literal zero user address. Now RECREATED with a full body
  in hv_glue_audit_mem.c (was extern): the observed bounds check is confirmed
  against the complete decompile, and the surrounding machinery (address-
  space-spec tagged-address sentinel DAT_fffffe000c62b698, PAN toggling
  pan=0/1 around the PAN copy with a 0x23 retry, sentinel-map copy,
  fallback copy, `0x4000001` length ceiling → 0x16) is audited.
- **Evidence**: `if (va < *(ulong*)(task+0x28) || CARRY8(va,len) ||
  *(ulong*)(task+0x30) < va+len) return 0xe;` in the recreated body
  (copyin, hv_glue_audit_mem.c); first copy kernel_copy (b95c414, (dst,len));
  PAN copy kernel_copy_pan (b75f890); fallback kernel_copy_fallback
  (b75fed8); sentinel copy kernel_copy_sentinel (b758bd0); panic c0e11ec
  "NULL task in %s @%s:%d" / "copy_ensure_address_space_spec changed
  address". Direct callee of hv_vcpu_create (b989040). Decompiler warning:
  Removing unreachable block (ram,0xfffffe000b95c28c).
- **Severity (hypothesis)**: informational — copyin is the canonical trusted
  primitive; the hv vCPU-create path passes a user pointer for the 0x10-byte
  state structure; the bounds contract is present and now fully audited.
- **Confidence**: high — full ~70-line decompile recreated, matching the
  earlier observed evidence exactly.

## [hv-deps] fffffe000b95d6f4 copyout (recreated 2026-08-12)

- **Observation**: The universal kernel->user copyout — mirror of copyin with
  PAN handling, RECREATED with a full body in hv_glue_audit_mem.c (was
  extern). The PAN-eligible path disables PAN (S3_6_15_1_6 write of
  0x2020a53a302abae6; state read S3_6_15_1_5) around kernel_copyout_pan
  (b75fb2c), re-enables it (0x2020a52a302abae6), takes the preemption counter
  (+0x1c0, kernel_panic c0f1874 at 0, kernel_tlb_flush b96c6d4 when the
  counter returns to 0 with +0x1b8+0x4c bit 2 set), sets the per-cpu copy
  flag +0x1f0, then falls through to kernel_copyout_fallback (b76002c).
- **Evidence**: recreated body (copyout, hv_glue_audit_mem.c); sentinel path
  kernel_copy_sentinel (b758bd0); panic c0e11ec "copy_ensure_address_space_spec
  changed address"; bounds contract identical to copyin (+0x28/+0x30, 0xe,
  CARRY8, 0x4000001 ceiling → 0x16). Direct callee of hv_vcpu_create
  (b989040) and hv_trap_op_0 (b984fd8). Decompiler warning: Removing
  unreachable block (ram,0xfffffe000b95d840).
- **Severity (hypothesis)**: informational — the user destination range is
  bounds-checked before the copy; the PAN/preemption dance is standard
  copyout behavior; nothing anomalous observed.
- **Confidence**: high — full ~120-line decompile recreated.

## [boot-audit] fffffe000bdbb37c code_signing_monitor_lockdown

- **Observation**: The code-signing lockdown runs at boot and *silently* clears
  the enable bits of four monitored code-signing features (masks
  0xfbffffff/0xefffffff/0xdfffffff/0xbfffffff on DAT_fffffe0007e31c58) — the
  single-gate trust decision is the init flag DAT_fffffe0007e31c50 bit 0. If
  that init bit is clear the kernel panics (fail-closed); if it is set the
  features are disabled with only a DataMemoryBarrier between clears. This is
  the point where the kernel drops from "monitoring" to "enforced lockdown" —
  there is no per-feature re-validation that the feature was actually enabled
  before its bit is cleared.
- **Evidence**: `if ((*(byte*)(cs+0x4f)&1)==0) { if ((DAT_fffffe0007e31c50&1)==0)
  goto _panic; DAT_fffffe0007e31c58 &= 0xfbffffff; DataMemoryBarrier(2,3); }`
  repeated for +0x4b/0x4a/0x49; gate `FUN_fffffe000bdbdffc()` (features
  enabled?) guards the whole block; panic string "attempted to disable code
  signing feature without init: %u @%s:%d".
- **Severity (hypothesis)**: informational — disabling code-signing monitoring
  at boot is the intended lockdown; the noteworthy property is that a single
  boot-time flag gates whether all four features are dropped, and the clear is
  unconditional once the flag is set.
- **Confidence**: high — the bit clears and the panic-on-not-init path are
  directly observed in the decompile.

## [boot-audit] fffffe000bf2413c oskext_remove_kext_bootstrap

- **Observation**: The kext bootstrap segments (__HEADER/__SYMTAB/__KLDDATA/
  __LINKEDIT) are un-mapped after boot to reclaim memory, but the __LINKEDIT
  symbol segment is retained whenever the "keepsyms" boot-arg flag
  (DAT_fffffe000c732541 bit 0) is set or the kernel was booted as a fileset
  (i==3). Retaining __LINKEDIT leaves the full symbol table resident in kernel
  memory, which aids any post-exploitation symbol resolution; it is gated only
  on a privileged boot-arg.
- **Evidence**: `if ((i==3) || ((DAT_fffffe000c732541 & 1) != 0)) {
  FUN_fffffe000bf0a554(0,0x13,"keepsyms boot arg specified; keeping linkedit
  segment for symbols."); } else { FUN_fffffe000bf775ec("Kernel-__LINKEDIT",
  ...); }`; segment unmaps via FUN_fffffe000bf775ec with round-up
  `lsize+0x3fff & 0xffffc000`.
- **Severity (hypothesis)**: informational/low — requires a privileged boot-arg
  or fileset boot; the residual symbol data is a memory-hardening observation,
  not an active bypass.
- **Confidence**: high — the keepsyms branch and the segment jettison are
  directly observed.

## [boot-audit] fffffe000b95af80 arm_cpu_init (EL2 control setup)

- **Observation**: The per-CPU EL2/EL1 control-register programming is gated on
  the EL2 feature global DAT_fffffe0007e0da68: when it is zero, the CPACR_EL1 /
  CNTKCTL_EL1 / counter-timer EL2 setup (UnkSytemRegWrite with op1=4) is
  skipped entirely, yet the CPU is still marked online and the boot continues.
  The hv availability that later gates the trap dispatcher depends on
  hv_support_init's separate EL2 check (FUN_fffffe000b984d4c), not on this
  path, so an EL2-feature-mis-set SoC could reach normal operation with
  partially-programmed EL2 control state.
- **Evidence**: `if (DAT_fffffe0007e0da68 != 0) { cpacr_el1 = ... | 0x1000000;
  UnkSytemRegWrite(3,0,1,2,6,0x4000000f); UnkSytemRegWrite(3,0,1,2,4,0);
  UnkSytemRegWrite(3,4,1,2,5,0); UnkSytemRegWrite(3,3,0xd,0,5,0); }` — the whole
  EL2 control block is inside the DAT_fffffe0007e0da68 test; DAT_fffffe0007e0c6d8
  (bit index) is only bounds-checked (`if (0x3f < DAT_fffffe0007e0c6d8)` panics)
  before being OR'ed into an EL2 register.
- **Severity (hypothesis)**: informational — the EL2-feature globals are
  kernel-set during hv_support_init / hv_el2_feature_detect, so a mismatch
  requires an EL2-detect failure; noted because EL2 control programming and the
  hv-availability gate are decoupled.
- **Confidence**: medium — the gate is directly observed; whether a zero
  DAT_fffffe0007e0da68 can actually occur on supported hardware is inferred.

## [el2-vectors] fffffe000b96743c hv_el2_guest_esr_classify — unknown EC -> panic

- **Observation**: The guest synchronous-exception classifier panics the whole
  kernel on any ESR exception class it does not explicitly handle (EC > 0x34,
  or EC in a gap of the dispatch table), via the noreturn assert
  FUN_fffffe000c0e11ec with "Unrecognized guest trap exception, state=%p,
  esr=%#llx @%s:%d". A guest that can trigger an unhandled EC therefore turns
  a guest bug into a host panic (availability), not a host compromise. The
  handled set is only {0x18 SVC, 0x1d, 0x20 IABT, 0x24 DABT, 0x3f SMC-ish};
  everything else falls through to the panic (after a host-abort bit check).
- **Evidence**: `if ((0x34 < uVar6) || ((1L << uVar7 & 0x10001100000000U) == 0))
  uVar5 = 0;` then for the not-handled path
  `FUN_fffffe000c0e11ec("Unrecognized guest trap exception, state=%p,
  esr=%#llx @%s:%d")` at fffffe000b967748; also "Unexpected host abort from
  guest context" (FUN_fffffe000c0f0fa4) when guest pstate bit3 (EA) is set on
  a non-handled EC. Exit word written at state+0x4008.
- **Severity (hypothesis)**: medium — an unhandled EC aborts the hypervisor
  (denial of service against co-tenants), but the panic is fail-closed (no
  silent wrong handling), so it is not a privilege escalation.
- **Confidence**: high — the panic strings and the EC dispatch structure are
  directly observed in the decompile.

## [el2-vectors] fffffe000b967768 hv_el2_guest_fault — IPA synthesis from HPFAR_EL2

- **Observation**: When a guest data/instruction abort is NOT resolvable via
  the FAR (EA set, or reason outside the in-guest range), the hypervisor
  synthesises the guest IPA as `FAR[11:0] | (HPFAR_EL2[31:4] << 12)` and
  stores it to state+0x4028 before vm_fault. HPFAR_EL2 bits [31:4] are the
  physical page that faulted; the low 12 bits come from the guest VA (FAR).
  This is the standard stage-2 IPA recovery, but the code trusts HPFAR_EL2
  without re-validating that the resulting IPA lies inside the guest's IPA
  space before passing it to vm_fault — the only range check is on the FAR
  against vm+0x28/0x30, which for the synthesised-IPA path (EA set) is
  skipped. A corrupted HPFAR (or a guest EL2 read of the register on a
  faulting access) could route vm_fault to an out-of-space IPA.
- **Evidence**: `uVar2 = hpfar_el2; param_3 = param_3 & 0xfff |
  (uVar2 >> 4 & 0xfffffffff) << 0xc; *(ulong*)(param_1+0x4028) = param_3;`
  then the FAR-in-range checks at `param_3 < vm+0x10` / `vm+0x18 <= param_3`
  and `param_3 < vm+0x28` / `vm+0x30 <= param_3` guard the vm_fault call —
  but on the EA-set branch `param_3` is the synthesised IPA and the range
  compare uses it against the vm bounds, so an IPA beyond the guest map falls
  to the `r=6` (translation fault) exit rather than being vm_fault'd.
- **Severity (hypothesis)**: low — the synthesised IPA that falls outside the
  guest map is rejected (exit 6); the risk is only if HPFAR/guest-map bounds
  are inconsistent. The EA-set path also bypasses the stage-1 translate.
- **Confidence**: medium — the HPFAR synthesis is directly observed; the
  exact vm-fault rejection semantics for an out-of-map IPA are inferred.

## [el2-vectors] fffffe000b760b94..b7615bc — guest-state PAC "JOP hash" integrity

- **Observation**: Every EL2 vector handler computes a chained PAC value
  (JOP hash) over the saved guest sysregs (MDSCR_EL1, tpidr_el1/el0/ro,
  par_el1, ...) using pacga, and panics with "Sysreg JOP hash mismatch
  detected (guest state corruption)" if it does not match the value stored at
  the time the guest was entered. This is a strong integrity check: it
  prevents a guest or a race from silently corrupting the saved host/guest
  state between save and use. The panic is fail-closed.
- **Evidence**: in FUN_fffffe000b760b94 (sync): `uVar37 = pacga(puVar3<<4|4,
  puVar3[1]&0xffffffff1377bfbf); ... ; if (puVar3[6] == lVar36) { ... b761930
  } else { FUN_fffffe000c0e11ec("Sysreg JOP hash mismatch ..."); }` — the
  same pattern repeats in all four handlers.
- **Severity (hypothesis)**: informational — this is a positive control, not
  a defect; noted because it bounds the exploitability of any guest-state
  corruption bug (a guest cannot forge the PAC hash without the key).
- **Confidence**: high — the pacga chain and the mismatch panic are directly
  observed.

## [el2-vectors] fffffe000b96743c — SVC ISS passthrough to userland exit record

- **Observation**: For a guest SVC (EC 0x18) the classifier stores the full
  25-bit ISS (`esr & 0x1ffffff`) into state+0x4018 and exit code 8 into
  state+0x4008. The ISS is handed to userland via the hv_vcpu_run exit record
  (hub b989a44 reads es+0x4008/0x4010..). An unvalidated guest-chosen 25-bit
  value is exposed; if any consumer uses it as an index/offset without bounds
  checking, it could be an out-of-bounds primitive. This is informational
  here (no consumer bug observed in this tree).
- **Evidence**: `*(ulong*)(param_1+0x1006*4) = param_2 & 0x1ffffff;` and
  `param_1[0x1002] = 8;` for EC 0x18 in FUN_fffffe000b96743c.
- **Severity (hypothesis)**: informational — requires a downstream consumer
  that mis-uses the ISS; flagged for the hv.c/hv_vcpu exit-record audit.
- **Confidence**: medium — the ISS is a literal guest ESR field copied out;
  the consumer-side risk is not re-audited here.

## [el2-vectors] fffffe000b75e468 hv_el2_return_to_guest — SVE/FPSR restore on eret

- **Observation**: The return-to-guest path restores fpcr/fpsr and, when the
  guest SVE state is active (type 0x31 object at tpidr+0x120), reloads all 32
  Z registers and 16 P registers from the guest frame before ExceptionReturn.
  The restore is gated on `(spsr_el1 & 0xc) == 0` (guest at EL0/EL1) and on
  the SVCR bit; the SVE vector length used for the P-register stride comes
  from the saved frame's +0x18 word. If the guest SVE state and the current
  vector length ever disagree (e.g. a length change mid-exit), the P-register
  base `frame + vl*0x20` could read beyond the frame. No guard on the stored
  vector length was observed.
- **Evidence**: `lVar8 = lVar8 + (ulong)*(ushort *)(piVar4 + 4) * 0x20;
  SVE_ldr(in_p0,lVar8,0); ... SVE_ldr(in_p15,...)` in FUN_fffffe000b75e468,
  gated on `(uVar1 & 0xc) == 0` and `(*(ulong*)(piVar4+2) & 1) != 0`.
- **Severity (hypothesis)**: low — requires a guest-controlled vector-length
  inconsistency to over-read the frame; the frame is kernel-allocated so the
  blast radius is a kernel OOB read, not guest-controlled memory.
- **Confidence**: low — the frame bounds for the P-register block are not
  independently verified (the +0x18 vector-length word is trusted).

## [hv-pmap] fffffe000b986b34 hv_pmap_resolve_owner — map-pointer trust + assert-only name check

- **Observation**: The map layer resolves a guest-supplied vm id (or the
  current CPU's bound owner) to the host map pointer that implements the
  guest's stage-2 translation, and the map core (hv_vm_map_core b9868a8) then
  validates the requested range only against that resolved owner's own window
  (owner+0x28/+0x30) and page mask (owner+0x44). On the low-32-bit container-id
  path the returned map is dereferenced (`name+0x50`) after validating only the
  name's `-` prefix and a single flag byte (`local_38[1] & 7`); any name lacking
  the `-` prefix panics via FUN_fffffe000c0e1c3c (assert-style, noreturn), so
  the only real gate on a non-registered id is the kernel object registry
  (FUN_fffffe000b7e0f30). There is no independent check that the resolved
  +0x2120/+0x50 pointer is the *guest's own* map rather than some other
  registered kernel object's map.
- **Evidence**: `result = *(long *)(lVar4 + 0x2120);` and `return
  *(undefined8 *)(local_38 + 0x50);` with the only guards being `(*local_38 ==
  '-')` and `(local_38[1] & 7U) != 0` before the dereference; id==0/-1 paths
  return owner/vcpu slots directly without re-validation. Range/cap checks
  live in the caller (b9868a8: carry-checked `CARRY8(uVar9,local_60)`, page
  mask from `(1L << *(ushort*)(owner+0x44))-1`, cap `0x7ffffe000000`).
- **Severity (hypothesis)**: informational/low — a guest can only reach this
  with a kernel-registered object id (or its own bound vcpu), so the trust
  boundary is the kernel registry, not the hypervisor; the assert-style panic
  is fail-closed.
- **Confidence**: medium — the offset dereferences and prefix/flag checks are
  directly observed; whether the registry can hand out a non-`-`/mis-typed
  name to a guest is inferred.

## [hv-pmap] fffffe000b9868a8 / b986d34 — unwind releases owner only when no vcpu bound

- **Observation**: On a map failure the unwind path (hv_pmap_unwind b986d34)
  releases the resolved owner reference (os_release b8afa78) ONLY when no vcpu
  is currently bound to the CPU (`tpidr_el1+0x4d8 == 0`); if a vcpu is bound it
  returns without releasing, and the map core then detaches via
  FUN_fffffe000b793cf4. This means a failed map/unmap on a CPU that owns a live
  vcpu does not drop the owner reference — the owner is kept alive by the bound
  vcpu. Combined with the id-based owner resolution bumping the refcount around
  the +0x2120 read, the owner can never be released below its bind count.
- **Evidence**: `if (*(long *)(lVar1 + 0x4d8) != 0) return;` before
  `os_release(param_2)` in FUN_fffffe000b986d34; the `iVar2 == 1 ->
  FUN_fffffe000b98533c(lVar4)` owner-release in hv_pmap_resolve_owner only at
  refcount==1.
- **Severity (hypothesis)**: informational — this is a correct keep-alive
  pattern, noted because a mis-sized refcount elsewhere (e.g. the 
  `kernel_refcount_inc(0)` no-op artifact in b986b34) could make the owner
  leak rather than double-free.
- **Confidence**: medium — the refcount dance is directly observed; the
  no-op `kernel_refcount_inc(0)` looks like a lost decompiler argument, so the
  exact inc/dec pairing is not fully certain.

## [hv-pmap] EL2 stage-2 table — fixed small table, descriptor format unobserved

- **Observation**: The EL2 translation table is a fixed ~32KB block (root L1
  at +0x0, L2 at +0x1000, L3 at +0x2000, EL2 state at +0x4000) allocated by
  hv_el2_pt_alloc (b98e344) and referenced by the EL2 state builder (b9895b8)
  via config slots 0xd/0xe. No software page-table walker or descriptor writer
  is present in the hv cluster: guest->host translation is built on the host
  vm_map (hv_vm_map_core) plus hardware page-walk, and the stage-2 descriptor
  format (VMSAv8-64) is modelled only as an estimate in hv_pmap.h, not
  observed. If the fixed table were ever undersized for a guest's IPA space, a
  guest access beyond the installed region would fault at hardware level and be
  routed to the vm_fault path (b967768) — fail-closed.
- **Evidence**: `param_1[0xd] = param_2 + 0x1000; param_1[0xe] = param_2 +
  0x2000;` in b9895b8; hv_el2_pt_alloc (b98e344) allocates the 0x4000 block and
  stores base at vm+0x4150. No `UnkSytemRegWrite` to TTBR/VTCR descriptor
  table population was found in the map/unmap functions.
- **Severity (hypothesis)**: informational — no defect observed; the finding is
  that descriptor encode/level constants are estimates, and the translation is
  hardware- and host-vm_map-driven.
- **Confidence**: low — the EL2 block layout offsets are observed; the absence
  of a software walker is a search-negative, not proof.

## [op-table-id] fffffe000b98e488 hv_trap_op_10 — CPU-bitmask slot index (CORRECTED 2026-08-12: in-bounds, NOT an OOB write)

- **Observation**: The op takes the raw 64-bit trap arg as a CPU/vcpu-slot
  bitmask (no copyin). For every set bit it derives `idx = CTZ(mask)` — a
  value in 0..63 — and then touches the vm owner block's per-CPU slot
  metadata at byte offsets `owner + idx*0x80 + 0x80` (slot-pointer read),
  `+0x90` (dirty-tag byte = 1), `+0x94` (busy word |= 4, atomic ldsetal),
  plus the cpu-to-signal qword at `+0x88`. **CORRECTED**: the earlier "~8
  entries" premise was wrong — it conflated the 8 page-registration array
  POINTERS (`owner[0x429..0x430]`, walked in hv_vcpu_object_release) with
  the inline per-CPU vcpu slot table. The slot table is **64 entries**:
  hv_vcpu_create (b989040) bounds the vcpu id with `if (0x3f < local_58)
  return 0xfae94003;` and installs at `*owner + id*0x80 + 0x80` for id in
  0..63 (verified in the fresh decompile). CTZ(mask) ∈ 0..63 therefore
  indexes the table in-bounds for every mask value; no OOB write exists.
- **Evidence**: disassembly of FUN_fffffe000b98e488 loops: `ctz x11, x10`
  (0xdac0194b) / `ctz x28, x19` (0xdac01a7c); tag store
  `strb w9, [x11]` with x11 = (owner+0x90) + idx*0x80 (add x8,x21,#0x90;
  add x11,x8,x11,lsl #7); busy `ldsetal w9,w8,[x8]` with x8 =
  (owner+0x94) + idx*0x80 (add x24,x21,#0x94); slot read `ldr x1,[x26]`
  with x26 = (owner+0x80) + idx*0x80. No `idx < 8`/`idx < ncpu` guard —
  but none is needed: bind-path writes at the same offsets for id 0..63
  (b989040 decompile) prove the 64-entry table.
- **Residual (informational/low)**: the mask is not validated against the
  number of *bound* slots or the physical CPU count. With all 64 slots
  bound, an all-ones mask makes the op lock + flush + signal every slot
  (a broadcast flush — expensive but functional; empty slots are skipped by
  the `*slot != 0 && vcpu != *slot` guard). From an entitled caller this is
  at most a self-inflicted performance/robustness note, not memory
  corruption. RECREATION NOTE: the project body originally transcribed the
  busy-word access with long* element arithmetic (8x too far) — fixed to
  byte arithmetic per the disassembly; the finding that survives is the
  fidelity lesson, not a kernel OOB.
- **Severity (hypothesis)**: informational — the earlier high was based on
  an incorrect slot-table-size inference.
- **Confidence**: high — index function and table size both verified at
  instruction/decompile level (CTZ decode via llvm-objdump; 64-entry bound
  from the b989040 decompile).

## [op-table-id] fffffe000b986f1c hv_vm_set_trap_debug — NULL vm resource deref in b954160

- **Observation**: idx14 copies in 0x18 bytes [id(8), value(8), reg-sel(8)],
  bounds-checks the reg selector to 0..9 (good), looks up the vm by id
  (b986b34), then calls `FUN_fffffe000b954160(vm+0x58, sel, value)`
  UNCONDITIONALLY. If the resolved vm has no resource block (`vm+0x58 == NULL`),
  b954160 dereferences `*(long *)(param_1 + 0x20)` (param_1 = NULL -> deref of
  0x20) before its stage-1-pmap panic check — a NULL-pointer fault. The
  decompile's `if (lVar3 == 0) lVar3 = 0;` is a no-op that still passes 0.
- **Evidence**: FUN_fffffe000b986f1c: `lVar3 = *(long *)(lVar2 + 0x58);
  if (lVar3 == 0) lVar3 = 0; FUN_fffffe000b954160(lVar3, local_30, local_28);`
  and FUN_fffffe000b954160: `if ((*(byte *)(*(long *)(param_1 + 0x20) + 0x4c) &
  1) == 0) panic(c0e11ec, "%s: invoked on stage 1 pmap ...")`. The vm resource
  is optional elsewhere (hv_vm_map_core checks `vm+0x58 != NULL` before using it).
- **Severity (hypothesis)**: medium — reachable only with a kernel-registered
  vm id whose resource is NULL; the resulting fault is a kernel panic (DoS), not
  corruption, and the vm owner registry is the trust boundary.
- **Confidence**: medium — the unconditional call with a possibly-NULL arg is
  observed; whether a valid guest can obtain a resource-less vm is inferred.

## [op-table-id] fffffe000b986da4 hv_vm_map_shared — mapping persists when handle copyout fails

- **Observation**: idx12 maps guest memory via hv_vcpu_map_memory (b9866d0) and
  copies the 8-byte shared-region handle out at args+0x18. If that copyout
  FAILS it does not unwind the mapping — it instead still notifies the per-cpu
  state block (b7a1dd8(handle & 0xffffffff)) and returns 0xfae94003. The guest
  thus has a mapped shared region it was never handed the handle for, and the
  region remains registered/visible even though the trap reports failure.
- **Evidence**: FUN_fffffe000b986da4: `uVar2 = copyout(&local_48, param_1+0x18,
  8); if ((int)uVar2 == 0) return uVar2; ... lVar3 = per_cpu+0x318;
  FUN_fffffe000b7a1dd8(lVar3, local_48 & 0xffffffff); return 0xfae94003;` — the
  b7a1dd8 notify runs on the copyout-failure path, after the mapping succeeded.
- **Severity (hypothesis)**: low — a copyout failure is an unusual kernel/user
  boundary condition; the effect is a leaked/registered mapping rather than a
  privilege change. Worth confirming the mapping is torn down on the caller's
  eventual vm teardown.
- **Confidence**: medium — control flow is directly observed.

## [op-table-id] fffffe000b986d84 hv_vm_protect — bare branch stub, no standalone validation

- **Observation**: idx4 is not a function in Ghidra; it is a 5-instruction
  stub (`dsb; mov w1,#1; mov w2,#0; b core@b9868a8`) that selects the protect
  path (op=1) of the shared map core. It performs no argument validation of its
  own; all range/cap checks live in hv_vm_map_core (hv_pmap, b9868a8). The
  protect call therefore inherits the core's validation but also its failure
  path (teardown of the caller's per-cpu vcpu on a bad range).
- **Evidence**: read_memory b986d84: `5f2403d5 21008052 02008052 c6feff17`
  (dsb / movz w1,#1 / movz w2,#0 / b -0x4e8). Core dispatch at b986a10:
  `orr w8,w21,w20; cbz w8,map; cbz w20,unmap; bl b8a8078 (protect)`.
- **Severity (hypothesis)**: informational — no new defect; documents that
  protect is a thin alias into the shared core.
- **Confidence**: high — bytes and dispatch decode are directly observed.

## [op-table-id] fffffe000b984fd8 hv_capabilities — fixed-size report copyout, no size negotiation

- **Observation**: idx0 copies out a fixed 0x1b3 (435)-byte capabilities report
  with no caller-supplied size field. The report is built from the caller's own
  entitlement tier (b985ae4) plus CPU/ID registers. The content is
  guest-visible and entitlement-gated; the copyout length is constant, so a
  caller with an undersized buffer would fault in copyout (kernel handles), not
  overrun.
- **Evidence**: FUN_fffffe000b984fd8: `copyout(report, param_1, 0x1b3)`; report
  built by b987d9c (feature mask, entitlement-tier driven) + b988038 (id_aa64*
  + cache geometry). No size arg in the 0x1b3 copyout.
- **Severity (hypothesis)**: informational — no defect; notes the report is
  client-entitlement-derived and fixed-length.
- **Confidence**: high — the constant copyout length is directly observed.

## [op-table-id] fffffe000b98e788 / b98e964 hv_trap_op_15/16 — SVE-mode select and feature-gated EL2 pt alloc

- **Observation**: idx15 validates its mode arg to 0..3 and requires EL2
  (DAT_fffffe0007e0da68) and a bound vcpu before lazily mapping a 0x4000 EL2 SVE
  save area into the guest VA space (via vm_map_enter b8b51c8) and forcing
  HCR_EL2 bits 0x3000000. idx16 only calls hv_el2_pt_alloc (b98e344) when the
  vcpu's opcode count (vcpu+0x2128) > 2 and the SoC feature index
  (DAT_fffffe0007e31628) is nonzero — otherwise returns error. Both are
  fail-closed and bounds-checked on their inputs; no defect observed.
- **Evidence**: FUN_fffffe000b98e788 `if (3 < param_1) return 0xfae94003;` and
  EL2/AMX guards; FUN_fffffe000b98e964 `if (2 < *(uint*)(*plVar3+0x2128))` +
  `DAT_fffffe0007e31628 != 0` gate before b98e344.
- **Severity (hypothesis)**: informational — input-bounds and EL2-feature gates
  present; the 0x4000 guest-visible EL2 scratch mapping is the only notable
  surface (guest can observe an extra mapping once SVE mode is enabled).
- **Confidence**: medium — the guards are directly observed; the scratch
  mapping's guest-visibility is inferred from the vm_map_enter call.

## [hvc-abi] fffffe000b989a44 hv_vcpu_run / b98a08c — guest-controlled HVC dispatch index, no observed privilege gate

- **Observation**: The run hub dispatches the guest HVC by masking the
  exception ISS/immediate (es+0x4018, the value the guest controls via the
  `hvc #imm` immediate and its register-visible exception) against the
  0x332c00..0x30fc1e families and routing through the jump table at
  0xfffffe000b989cf4. The dispatch selector is therefore guest-influenced.
  No bounds check on the derived table index is visible in the partial
  reconstruction, and no SPSR_EL1 EL-field (guest EL0 vs EL1) privilege check
  is observed between the HVC trap and dispatch — both a user guest and a
  supervisor guest appear to enter the same HVC path. These gaps are real but
  UNVERIFIED: the hub is a partial assembly-only reconstruction (decompiler
  failed), so the absence of a bounds check / privilege gate may be a
  reconstruction artifact, not a genuine defect.
- **Evidence**: hv_vcpu.c @ b989a44 case 0x8 -> b98a08c: "mask es[0x4018]
  against 0x332c00..0x30fc1e families and dispatch on the encoded exception
  class (see jump table at 0xfffffe000b989cf4)"; hv_el2_guest_esr_classify
  (b96743c) does NOT list HVC (0x30-class) among its handled ECs, so HVC
  reaches the hub; no register-arg or EL-privilege validation documented in
  either reconstruction.
- **Severity (hypothesis)**: low — guest-controlled dispatch index is standard
  for a hypercall table; a real OOB/privilege defect would be high, but the
  evidence is a partial reconstruction and cannot support that claim.
- **Confidence**: low — dispatch-by-ISS is directly observed; the absence of a
  bounds/privilege check is inferred from an incomplete reconstruction.

## [hvc-abi] fffffe000b989a44 hv_vcpu_run — HVC64 enable-mask gate verified; SVC/VM-op channel gated only by opcode count (2nd pass, deepened)

- **Observation**: Second pass (TreeRunHubDeep + targeted disassemble_bytes of
  the HVC dispatch region) VERIFIES a per-VM hypercall enable mask on the HVC64
  path: `imm<=6` AND `(container_enable_mask & (1<<imm)) != 0` else the
  hypercall is skipped — a positive privilege control (a VM must opt in to each
  HVC64 hypercall).  This supersedes the earlier "no bounds check" hypothesis:
  the imm<=6 bound IS present.  The residual asymmetry is that the SVC/VM-op
  channel (0xc6000010..0xc600001a -> hv_vm_op_dispatch b98e020 /
  hv_vcpu_slot_op b98e12c / per-slot map b9866d0) is gated only by the
  container opcode count (vm+0x2128) plus "no attach id (vcpu+0xe0==0) and no
  pending SPSR bit" — NOT by the enable mask.  A guest reaching the VM-op SVC
  channel up to the configured opcode count is not separately vetted per op.
- **Evidence**: disasm at 0xfffffe000b98a76c: `ldr x9,[x21,#0x1350]` (enable
  mask), `and x10,x8,#0xff` (imm), `subs xzr,x10,#6; b.hi` (imm<=6),
  `mov w10,#1; lsl x10,x10,x8; and x9,x9,x10; cbz x9` (mask bit test); HVC64
  numbers materialized as `mov w9,#imm; movk w9,#0xc300,lsl#16` then `subs
  xzr,x8,x9` (0xc3000003/0xc3000004/...).  SVC/VM-op gate at 0xfffffe000b98b3d0
  (opcode-count vm+0x2128, no enable-mask check observed).  Reconstruction
  noted the enable mask at container+0x2130 (disasm read +0x1350; offset
  unconfirmed).
- **Severity (hypothesis)**: informational — HVC64 hypercalls are mask-gated
  (good); the VM-op SVC channel's opcode-count-only gate is a mild privilege
  asymmetry, not a demonstrated defect.
- **Confidence**: medium — the enable-mask gate is directly observed in the
  disassembly; the VM-op channel's lack of a mask check is inferred from the
  reconstruction (the VM-op bodies themselves are not fully re-verified).

## [vcpu-core] fffffe000b989a44 hv_vcpu_run / b98a08c — guest-triggerable host panic on unhandled ESR EC / exit reason
- **Observation**: The run hub classifies synchronous exceptions from the guest ESR (es+0x4018) against a large set of EC families (0x24-0x3f debug/arch, 0x83000000 IABT, 0xc1000000/0xc3000000 HVC, 0xc6000000 SVC). For every family the guest-enable bit is tested (vm+0x20a8/0x20b0 masks ANDed with es+0x6xx per-EC bits) and a matching exception is emulated/re-injected; a class whose enable bit is clear falls through to the unhandled-EC path. That path and several invariant checks reach HOST-KERNEL PANICS (FUN_fffffe000c0e11ec with line-numbered format strings at 0xfffffe000b98db24 [line 0x4e6], 0xfffffe000b98dbb8 [line 0x12f0], 0xfffffe000b98dbe0 [line 0xfb8] via c0e0620/c0e4d74). A guest that triggers an exception class/state the hypervisor does not expect can therefore panic the host kernel (denial of service) rather than being surfaced as a recoverable exit error.
- **Evidence**: disasm 0xfffffe000b98a08c..0xfffffe000b98cbe0: per-family `tbnz ... -> 0xfffffe000b98d860` (unhandled) and `bl 0xfffffe000c0e11ec` panic calls at 0xfffffe000b98db24/0xfffffe000b98dbb8/0xfffffe000b98dbe0; the SVC handler also panics/asserts on invalid opcode-count state (0xfffffe000b98dbb4 -> 0xfffffe000b98dbb8).
- **Severity (hypothesis)**: medium — a guest-driven host panic is a real DoS, but whether a benign/attacker guest can actually reach these invariant panics (vs. the recoverable 0xfae94001 return) is unverified.
- **Confidence**: medium — the panic calls are directly observed; guest reachability is inferred.

## [vcpu-core] fffffe000b989a44 hv_vcpu_run — conditional AMX/SVE EL2 state save may leak across vcpus
- **Observation**: The EL2 state is captured per dirty-mask group by hv_vcpu_save_el2_state (b988358); the AMX payload block (es+0x8e8..0x9c8) is only saved when the mask bit-4 group is set AND (es+0x4138 >> 1 & 1) is set, and the hub restores it only for restore bits 0x3a/0x3b. If a vcpu that enabled AMX exits without that gate being set, its AMX/SVE register payload may not be captured, so a later vcpu (or the host) could observe stale AMX state — a potential cross-vcpu privilege-domain data leak.
- **Evidence**: b988358 decompile: `if ((uVar8>>4&1)!=0 && ((*(byte*)(lVar5+0x4138)>>1&1)!=0))` guards the es+0xd0 AMX area clear; hub restore blocks 0xfffffe000b98af84/0xfffffe000b98b0a0 gate the AMX payload on restore bits 0x3a/0x3b.
- **Severity (hypothesis)**: low — would require a missed dirty-tracking gate; the save is guarded, not unconditional, so the leak is conditional on tracking correctness.
- **Confidence**: low — the conditional gates are directly observed; a real save-miss is not demonstrated.

## [vcpu-core] fffffe000b989a44 hv_vcpu_run — synthetic register blob injected into guest on HVC/SVC emulation
- **Observation**: On the HVC (0xc1000001..0xc100000f, 0xc3000003..0xc3000006) and IABT (0x83000000) handlers the hub stores hypervisor-chosen constant vectors (loaded from DAT tables into q0/q1 at sp+0x50/0x60/0x70/0x80/0x90 and the fixed magic 0xfeedfacefeedfad9 — verified 2026-08-12 from the movk chain at b98bd28-34: `mov #0xfad9; movk #0xfeed<<16; movk #0xface<<32; movk #0xfeed<<48`; the earlier 0xfedefacafeadfad9 transcription was wrong) into the guest-visible save area es+0x8/0x18/0x28. These become the guest-visible x0..x3/PC-style register state after return-to-guest. The injected values are constants in the traced disassembly, but any future code path that mixes guest-controlled data into these blobs would be a register-injection / privilege bug; the fixed magic also fingerprints the hypervisor emulation to the guest.
- **Evidence**: disasm 0xfffffe000b98bd1c (stores q0/q1 from sp+0x50 to es[0x8]/[0x18], magic 0xfeedfacefeedfad9 to es[0x28]); 0xfffffe000b98c464/0xfffffe000b98c50c/0xfffffe000b98c5b4/0xfffffe000b98c648 (same magic family writes); 0xfffffe000b98a7d8 (rev-swapped 32-bit pair stores for the HVC hint handler).
- **Severity (hypothesis)**: informational/low — observed values are constant; no guest influence in the traced paths.
- **Confidence**: high — the injection writes are directly observed; the 'no guest influence' part is limited to the traced constant paths.

## [kernel-iface] fffffe0007e41db0 hv_available_flag — single-flag presence gate, no per-call re-validation

- **Observation**: The entire hypervisor presence decision is one boot-time
  global (`hv_available_flag`, DAT_fffffe0007e41db0). Its complete xref
  closure is four references: WRITE by kernel_bootstrap_thread (from
  hv_support_init return), READ by hv_available (b984ed8), and two DATA refs
  (0x7e2bda8 / 0x7e41dd0) that are the `hv_support`/`hv_disable` boot-arg
  descriptors whose value-storage target IS the flag. Because the two boot-arg
  descriptors write into the same flag, a privileged `hv_disable`/`hv_support`
  boot-arg can override the EL2-detection result; and because the flag is only
  checked once per mach-trap call at the top of hv_available, there is no
  TOCTOU window within a call (it is read once), but there is also no
  re-validation that the EL2 configuration is still consistent at dispatch.
- **Evidence**: get_xrefs_to(DAT_fffffe0007e41db0) = {0x7e2bda8, 0x7e41dd0
  [DATA], b984f08 in hv_available [READ], b823ee4 in kernel_bootstrap_thread
  [WRITE]}; hv_support.c hv_available reads the flag once and returns
  -0x516bff1 (0xfae9400f) when clear. hv_vmm_present (be39fd0) uses a separate
  IOKit "vmm-present" property, not the flag.
- **Severity (hypothesis)**: informational — a boot-arg override requires
  privileged boot-arg control, and the flag is read atomically per call; the
  notable property is that no hibernation/power/vm subsystem re-checks it.
- **Confidence**: high — the four-ref xref closure is exhaustive (only these
  references exist).

## [kernel-iface] fffffe0007e34f98 coredump_docmd_trigger_kernel_coredump — live-dump handler pointer lands mid-function

- **Observation**: The panic/coredump "docommand" entry
  "trigger_kernel_coredump" (desc: "Request that the hypervisor take a live
  kernel dump") carries a +0x08 code pointer 0xfffffe000b8f9f08 that falls
  INSIDE FUN_fffffe000b8f91b8, a large VM contiguous-page-allocation function.
  Either Ghidra failed to split a small docommand handler out of the enclosing
  VM function, or the docommand dispatch invokes it at a mid-function offset.
  Either way the dump-request entry point is not a clean, independently
  verifiable function — the actual live-dump path is shared kernel
  panic/coredump code (not hypervisor code), so a request to dump a live
  kernel via the hypervisor routes through this entry whose exact semantics
  are unverified.
- **Evidence**: get_xrefs_to(0x70c58af) -> 0x7e34fb0 [DATA] only;
  get_function_by_address(0xfffffe000b8f9f08) -> FUN_fffffe000b8f91b8
  (entry 0xfffffe000b8f91b8, body ..b8fa467). Entry record at 0x7e34f98:
  name@+0x00, value_or_func@+0x08=0xfffffe000b8f9f08, help@+0x10,
  desc@+0x18, flags@+0x20=1, chain@+0x28=0x7e34f18.
- **Severity (hypothesis)**: informational — no privilege boundary is crossed
  by an ambiguous coredump-command pointer; flagged because the dump-request
  interface's real entry point is unverified and could route to the VM
  allocator if the pointer is genuine.
- **Confidence**: medium — the mid-function landing is directly observed;
  whether it is a Ghidra split failure vs. a genuine off-entry call is unknown.

## [kernel-iface] fffffe0007e2bda8 / fffffe0007e41dd0 hv_support / hv_disable boot-arg descriptors — flag is a writable boot-arg target

- **Observation**: The hv availability flag address is the value-storage
  target of both the `hv_support` (0x7e2bda8) and `hv_disable` (0x7e41dd0)
  boot-arg descriptors (each also references the shared trap munger
  bda3ca8). This means a boot-time "hv_disable" argument can clear the same
  flag that hv_support_init's EL2 check sets, and "hv_support" can force it.
  The presence decision is therefore attacker-influencable only at boot (not
  at runtime), but the two paths (boot-arg write vs. EL2-detection write) are
  not reconciled — the last writer wins.
- **Evidence**: at 0x7e2bda8 the 8 bytes = 0xfffffe0007e41db0 (flag address),
  with name "hv_support" @0x70b84d5 and munger 0xfffffe000bda3ca8 nearby; at
  0x7e41dd0 the value 0xfffffe0007e41db0 again with munger bda3ca8 and name
  near 0x70b84e0 ("hv_disable").
- **Severity (hypothesis)**: low — requires privileged boot-arg control
  (secure boot / EFI), so not a runtime bypass; noted as a single point where
  a boot-time knob and the hardware-EL2 gate share one flag with last-writer-
  wins semantics.
- **Confidence**: medium — the flag address appears as the descriptor value
  target in both records; the "last writer wins" ordering is inferred from
  the shared storage, not a traced call sequence.

## [vcpu-core] fffffe000b98a08c hv_esr_classify — HVC/SVC opcode-count gate bounds

- **Observation**: The in-hub ESR classifier gates the SVC/HVC hypercall
  dispatch on a per-VM opcode count read from the container at +0x2128. For
  SVC the gate is `count-3 in [0,2)` (i.e. only count==3 or count==4 are
  accepted; count<3 writes -1 to the guest return reg es[0x8], count>=5 is
  rejected). The per-op enable bits live in VM bytes +0x2190/+0x2191 and the
  HVC64 mask at vm+0x2130 (& (1<<imm), imm<=6). No other validation is applied
  to the guest-supplied SVC number before it is used to index the VM op table;
  an unrecognized number in the accepted count window falls to the unhandled
  path (fail-closed) rather than mis-dispatching.
- **Evidence**: b98b3f4 `subs w10,w9,#0x3; b.cc bc14` (count<3 -> es[0x8]=-1,
  b98bc14), `b.cs dbb4` (count>=5 -> unhandled); SVC nr compare tree
  b98c824..b98caa4; HVC64 mask check b98a790 `cmp x10,#0x6; b.hi d860` +
  `and x9,x9,x10; cbz x9,d860`; HVC32 hint gate b98a484 `sub w10,w9,#0x2;
  cmp w10,#0x3; b.cs ba94`.
- **Severity (hypothesis)**: informational — the bounds are correct
  (fail-closed on out-of-range), but the opcount window is a shared counter
  (vm+0x2128) used by both SVC and HVC; a guest that can perturb the count
  could force the reject path and get a spurious -1 return, not a privilege
  change.
- **Confidence**: medium — the gate values (3/4 for SVC, 2..4 for HVC32,
  imm<=6 for HVC64) are taken from the disassembly; the security impact of
  the shared counter is inferred.

## [el2-vectors] fffffe000b75e468 hv_el2_return_to_guest — PAC key re-arm nonce derivation

- **Observation**: On every guest resume the hypervisor re-arms APIAKeyLo
  (3,0,1,0,5) with a nonce derived via pacga from the per-CPU thread key
  `*pcpu` (a 16-bit signed value) and an incrementing context counter
  (per-cpu+0xe0), OR'ed with 0x700. The key seed reduces to the 16-bit thread
  key; if that word is low-entropy or attacker-influenceable, the re-armed PAC
  key is weak and a guest could forge pointer-authentication codes. The same
  tail appears in hv_el2_exception_exit (b75e420) and hv_el2_eret_fast
  (b75e5cc).
- **Evidence**: `uint64_t k = (uint64_t)(int16_t)*pcpu; na = pacga(k*0x100+3,
  kc); nb = pacga(k*0x100+0x13, kc); UnkSytemRegWrite(3,0,1,0,5,
  (na ^ (nb>>32)) | 0x700);` where kc = *(pcpu+0xe0) incremented. Literal
  (3,0,1,0,5) write; identity unverified per contract.
- **Severity (hypothesis)**: informational/low — the key is kernel-set per
  cpu and PACGA + the counter add entropy; the strength still depends on the
  16-bit thread-key field, which is a kernel datum a guest should not reach.
- **Confidence**: medium — the pacga/0x700 derivation is directly observed;
  whether the 16-bit key field is ever attacker-controlled is inferred.

## [el2-vectors] fffffe000b760f04 / b761260 — irq/fiq tails PAC-authenticate the EL2 stack

- **Observation**: The IRQ (b760f04) and FIQ (b761260) vector tails re-derive
  the EL2 stack pointer via `autda x1,x2` (PAC-Authenticate, key context
  0xe94d<<48) from the per-CPU thread frame, whereas sync (b760b94) and error
  (b7615bc) use `mov sp,x21` — the frame base saved at [tpidr_el2+0x28]. The
  asymmetric handling means the IRQ/FIQ entry path is additionally bound to a
  PAC-authenticated thread frame, while sync/error trust the saved x21.
- **Evidence**: `mrs x1,tpidr_el1; ldr x2,[x1,#0x1b8]; add x2,x2,#0x10; ldr
  x1,[x2]; movk x2,#0xe94d,LSL #48; autda x1,x2; mov sp,x1;` at b76122c (irq)
  and b761588 (fiq); sync/error do `mov sp,x21` after `ldr x21,[sp,#0x28]`.
- **Severity (hypothesis)**: informational — both paths are already guarded
  by the JOP hash; the autda path additionally binds the stack to the
  thread's PAC, a defense against a forged/raced stack pointer on the
  interrupt path.
- **Confidence**: high (directly observed in the disassembly).

## [el2-vectors] fffffe000b9679c8 hv_el2_guest_exc_check — dtrace table walk uses string-address sentinel

- **Observation**: The EC-0x25 dtrace address check walks DAT_fffffe0007045690
  (4 qwords/entry) terminating only when the walk pointer reaches the address
  of the "dtrace: %s has an invalid address" string (fffffe00070459d0). If the
  table were corrupted or the sentinel absent, the walk reads past the table.
  The 0x1fff8fba970 addition to the PC decodes a tagged address; range
  membership in the table is the only gate for returning the SVC-ISS 0x11
  guest-visible path.
- **Evidence**: `while (pc < dt[0] || dt[1] <= pc) { dt += 4; if
  ((uintptr_t)dt >= 0xfffffe00070459d0ULL) { ... } }` with pc = elr +
  0x1fff8fba970.
- **Severity (hypothesis)**: informational — the table is kernel-owned and
  presumed valid; the string-address terminator is fragile to corruption but
  there is no attacker-controlled index.
- **Confidence**: medium — the walk and sentinel are directly observed; table
  integrity is assumed.

## [el2-vectors] fffffe000b75e468 — fast-eret path writes 16 bytes below the frame base

- **Observation**: When the preemption count is 0 and the per-cpu +0x4c bit2
  flag is set, hv_el2_return_to_guest (and hv_el2_exception_exit) store the
  caller's fp/lr at frame-0x10 / frame-0x8 — 16 bytes below the guest-state
  frame base — before calling the preempt-clear helper (FUN_fffffe000b7a56d4)
  and the fast eret. There is no bounds check on this underflow write; the
  frame is kernel-allocated so the adjacent page is kernel memory.
- **Evidence**: `*(uint64_t *)(st - 0x10) = /* fp */ 0; *(uint64_t *)(st - 8)
  = /* lr */ 0;` in the eret_fast branch of b75e468 and b75e420.
- **Severity (hypothesis)**: informational/low — a fixed 16-byte underflow
  write; impact is limited to adjacent kernel data, but a frame placed near an
  allocation boundary could clobber the preceding object.
- **Confidence**: high (directly observed; offset constant from the decompile).

## [trap-dispatch] fffffe000b986ff4 hv_vm_map_region — duplicate-start insert abandons a live node

- **Observation**: On the insert path, the leaf-search loop treats a node with
  the same vm whose start is >= the new region's start (`newstart <= cur.start`)
  as success (jumps to the success epilogue: result=0, version++, keep-node
  flag set). The freshly allocated region node was already given its fields
  (node[0]=vm via kernel_refcount_inc b8af98c, node[4]=ret) but is NOT linked
  into the rbtree and, because the keep-node flag is set, is NOT released in
  the insert epilogue (`if (!b) { os_release(node[0]); zfree(node[4]);
  refcount_dec(node); }`). The node, its vm reference and its backing-store
  reference are left live and unreachable.
- **Evidence**: Ghidra FUN_fffffe000b986ff4: `if (uVar24 <= puVar13[2]) goto
  LAB_fffffe000b987790` inside the LAB...454 leaf-search do/while; LAB...790
  sets `uVar25=0; *plVar2 = cVar4+1; bVar6=true;` and the epilogue
  LAB...7a4 releases only `if (!bVar6)`. Node was allocated at
  FUN_fffffe000b7eb624(DAT_fffffe0007d54038) before the search.
- **Severity (hypothesis)**: low/medium — repeated duplicate-start calls leak
  node objects, a vm retain and a backing store per call (DoS via memory
  exhaustion if the user can force it); no memory corruption.
- **Confidence**: medium — the control flow (allocate, abandon with keep flag
  set) is directly observed; whether upstream callers ever pass a duplicate
  start is not established.

## [trap-dispatch] fffffe000b986ff4 hv_vm_map_region — partial-overlap returns generic 0xfae94003 vs exact 0xfae94008

- **Observation**: The insert distinguishes exact overlap (`cstart == newstart
  && cand.end == keyend` -> 0xfae94008, a specific "already present" error)
  from partial overlap (node released, result left at the function-default
  0xfae94003, a generic failure). A caller cannot tell "region already mapped"
  from any other map failure on the partial-overlap path, and the error-code
  asymmetry (08 for exact, 03 for partial) is undocumented.
- **Evidence**: Ghidra FUN_fffffe000b986ff4 LAB...3bc: exact branch sets
  `uVar25 = 0xfae94008`; the else branch (`cstart==keyend || cand.end<=newstart`
  false) only sets `bVar6=false` and falls to the epilogue with uVar25 still
  0xfae94003 from initialization.
- **Severity (hypothesis)**: informational — inconsistent-but-non-critical
  error reporting; no privilege/confidentiality impact.
- **Confidence**: high (directly observed in the decompile).

## [trap-dispatch] fffffe000b985588 hv_vm_create — requested tier is user-copied and compared, not clamped

- **Observation**: The requested tier (local_48, bytes 24..27 of the 0x1c-byte
  copyin block) is user-controlled and must satisfy `req <= granted_entitlement`
  or the call fails with 0xfae94007. The granted tier is derived inline from
  three sandbox entitlements (max tier 4). The user's requested tier is then
  stored (`owner[0x425] = tier`) and drives quota/caps, so a user can request a
  LOWER tier than granted (harmless) but never a higher one. The check is
  correct, but the granted-tier computation is gated on the global
  `hv_caps_gate == 0`; if that gate is ever set nonzero, VM creation is denied
  outright (0xfae94007), so the gate cannot be used to bypass the entitlement
  check.
- **Evidence**: Ghidra FUN_fffffe000b985588: copyin 0x1c -> local_48;
  `if (local_48 != 0 && DAT_fffffe000c649750 == 0) { ...probe 3 strings via
  DAT_fffffe0007e93310+0x1c0... if (uVar2 <= uVar10) { alloc ... } }
  return 0xfae94007;`
- **Severity (hypothesis)**: informational — entitlement enforcement is sound;
  noted for completeness of the tier/quota audit.
- **Confidence**: high (the `req <= ent` guard and the three-string probe are
  directly observed).

## [trap-dispatch] fffffe000b986ff4 hv_vm_map_region — region RB rebalance reconstructed inline; hv_rbtree_insert has no body

- **Observation**: The region-tree insert fixup (standard red-black rebalance)
  is inlined in this function and was reproduced as static
  hv_rb_insert_rebalance. hv_rbtree_insert (declared extern in hv_internal.h)
  has NO decompiled body in the tree, so the two implementations are not yet
  reconciled; if hv_rbtree_insert is later filled with the same algorithm and
  this function keeps its inline copy, the module would duplicate the fixup.
  This is a correctness/maintainability note, not a vulnerability.
- **Evidence**: hv_internal.h:252 `extern int hv_rbtree_insert();` has no
  definition in osfmk/arm64/hypervisor; hv_vmapple.c provides only
  hv_rbtree_unlink (b9860bc).
- **Severity (hypothesis)**: informational.
- **Confidence**: high (absence of the body verified by grep).

## [vcpu-core] fffffe000b98a08c hv_esr_classify — per-EC enable-bit gates are family-specific

- **Observation**: The debug/arch exception families (ESR EC 0x24-0x3f) are
  each gated by a family-specific enable bit, NOT a shared mask.  Each family
  reads a different enable word from the guest save area (es+0x6a8/0x6b0/
  0x6c0/0x730) ANDed with a different VM mask pair (vm+0x20a8/b0, +0x20c0/c8,
  +0x2090/98, +0x20d8/e0) and tests a different bit (tbnz/tst #0x300,
  #0x1c00, bits 0xb/0xe/0x1a/0x1b).  The enable word lives in the *guest
  save area*, so a guest that can influence its saved EL2 state could set a
  per-EC enable bit; but the VM mask pair must also be set, and the VM masks
  are host-owned config words.
- **Evidence**: leaf b98b870 reads es+0x6c0 with vm+0x20c8|0x20c0 and
  `tst #0x300`; b98c8e0/b98c8d8 use es+0x6b0, vm+0x20b0|0x20a8, tbnz #0xe;
  b98c928 uses es+0x6a8, vm+0x2098|0x2090, tbnz #0x1a; b98bf3c uses es+0x730,
  vm+0x20e0|0x20d8, tst #0x1c00; b98c2c0 uses bit 0x1b; b98c328 bit 0xb.
- **Severity (hypothesis)**: informational — the enable bits are guest-state
  AND host-config gated, so no bypass; noted because an earlier collapsed
  reconstruction incorrectly used a single `& 0x300` for all families.
- **Confidence**: medium — enable offsets/bits taken from leaf disassembly;
  the semantic of each bit (which guest debug feature it toggles) unverified.

## [de-guess] fffffe000b9888a4 hv_vcpu_debug_save — debug-state claim may over-write watchpoints

- **Observation**: On the EL2 debug-save path the function writes
  `DBGCLAIMCLR_EL1 = 0xff`, claiming ALL 16 breakpoints + 16 watchpoints
  (each of the two count globals is capped at 0x10 in the switch). If the
  guest was mid-debug with more watchpoints configured than the host count
  allows, the wholesale claim and per-register save is consistent with
  standard kernel debug-state save, but the reconstruction had no bounds
  beyond `count < 0x10`. No guest-visible bypass: it saves then re-reads the
  count-capped register set into host-owned EL2 save memory.
- **Evidence**: decompile reads dbgclaimclr_el1 -> es+0x690, writes 0xff back
  to claim, then loops dbgbvr/dbgbcr (es+0x478/0x480) and dbgwvr/dbgwcr
  (es+0x578/0x580) up to DAT_fffffe000c71693c / DAT_fffffe000c716938 (each
  gated `< 0x10`).
- **Severity (hypothesis)**: informational — standard debug-state save; no
  unverified guest input, the count is a host-side global.
- **Confidence**: high (decompile verbatim).

## [de-guess] fffffe000b98e12c hv_vcpu_slot_op — no bounds check between slot-descriptor write and use

- **Observation**: The vcpu slot op validates `slot < 8` and `which < 0x40`,
  then transitions a per-slot word 1->2 and wires/copies guest memory using
  lengths read from the EL2 config (`src+0x20`/`src+0x28`). The fault table
  passed to kernel_copyin2 is the VM_MAP_UNWIRE table (DAT_fffffe0007d81408);
  sizes come from host config words, not guest-controlled values directly.
- **Evidence**: decompile: `if (7 < param_2) return 0xfae94003; if (0x3f <
  param_3) return 0xfae94003;` then `iVar6 = FUN_fffffe000b8b122c(0,lVar11,
  uVar8+uVar12+lVar11,0,&DAT_fffffe0007d81408)`.
- **Severity (hypothesis)**: informational — bounds are host config-derived.
- **Confidence**: high (decompile verbatim).

## [de-guess] fffffe000b986898/fffffe000b986d94 hv_vm_map/hv_vm_unmap — thin wrappers over shared core

- **Observation**: Both op-table handlers (idx 3 / idx 5) are single-call
  wrappers into `hv_vm_map_core(args, op, mode)` with op=0, mode=0 (map) /
  mode=1 (unmap). No per-op validation in the wrapper; all arg parsing and
  bounds live in the shared core (b9868a8). Confirm both remain gated by the
  same hv_available dispatch (FUN_fffffe000b984ed8).
- **Evidence**: `hv_vm_map = hv_vm_map_core(param_1,0,0); hv_vm_unmap =
  hv_vm_map_core(param_1,0,1)`.
- **Severity (hypothesis)**: informational.
- **Confidence**: high.

## [de-guess] fffffe000b85f794 zone_create — element-size bound enforced but zone flags trusted

- **Observation**: `zone_create` (previously guessed `kernel_vm_pages`)
  panics on element size > 0x8000 and on bad/duplicate zone IDs, but the
  ZC_* flag bits are used directly to configure caching/nogc/destructible
  behavior without revalidation — expected for a kernel zone allocator; the
  only caller-relevant surface is that hv must not feed it a non-canonical
  flag word. Not hv-observable here.
- **Evidence**: `if (0x8000 < param_2) panic("zone_create: element size too
  large");` plus ZC_VM/ZC_DESTRUCTIBLE/ZC_OBJ_CACHE/ZC_PERCPU/ZC_READONLY
  string dispatch.
- **Severity (hypothesis)**: informational.
- **Confidence**: high.

## [de-guess] fffffe000b8f6e54 kernel_queue_free_walk — frees caller-controlled list

- **Observation**: Walks `*param_1` as an intrusive list and frees every
  element (b958108/b8f4310 + b85d440). There is no cycle guard: a cyclic list
  would loop forever. Called by machine_lockdown / kernel_bootstrap_thread
  with host-owned lists; not guest-reachable. Noted for the audit doc only.
- **Evidence**: `do { puVar10 = *param_1; *param_1 = 0; ... } while
  (puVar10 != 0)`.
- **Severity (hypothesis)**: informational.
- **Confidence**: high.
- **2026-08-12 correction**: hv_glue_audit_mem.c had declared this address
  under two additional wrong names (`kernel_page_unlink`, `kernel_vm_free_pages`)
  for the zalloc-core free paths; unified to `kernel_queue_free_walk` per this
  finding (prototype-less decl matching hv_kernel_shims.h).

## [vcpu-classifier] fffffe000b989a44 hub — full ESR-classifier hypercall surface transcribed

- **Observation**: The entire SVC/HVC hypercall dispatch in the run hub was
  transcribed from disassembly this session: HVC64 0xc3000003/4/5/6, HVC32
  0xc1000000-0xf, SVC 0xc6000010-0x1a. Attack surface: opcode-count gate
  (vm+0x2128, count must be 2-4 for HVC32, 3-4 for SVC64), per-op enable
  gates (vm+0x2190/0x2191), and the per-hypercall enable mask vm+0x2130.
  Errors surface to the guest as 0xfffffffffae9400X.
- **Evidence**: instruction-level traces with resolved DATs (e.g. HVC64
  0x4/6 hashes the guest-chosen slot pointer into the kernel waitq hash
  table DAT_fffffe0007d7c8e0; SVC 0x1a SIMD-select returns the error vector
  {0xfffffffffae9400f,0} from rodata DAT_fffffe000700f400; SVC 0x10/0x11/0x19
  slot-record machinery uses 0x2bad/0xc8a2-tagged slot pointers).
- **Severity (hypothesis)**: the waitq-hash flush (HVC64 0x4/6) feeds a
  guest-selected value through a 64-bit hash into a kernel bucket; the slot
  tables (vm+0x2148, vm+0x2188) are validated (idx <= 7/0x3f, owner cpu
  check, busy CAS) before use. No unchecked guest index found in the traced
  leaves.
- **Confidence**: high (disassembly-verified).

## [vcpu-classifier] fffffe000b989a44 hub — PAC-tagged pointer arithmetic (0x2bad/0xc8a2)

- **Observation**: The slot-table and sub-slot indexing use the Ghidra
  sign-extension csel idiom: `add` (signed) vs `add` (unsigned) compared,
  with the mismatch case OR-ing 0x2bad000000000000 (or 0xc8a2000000000000)
  into the pointer. This is the kernel's address-tagging for pointer
  validation, not a real PAC operation (autda/autib are used separately for
  the JOP hashes and the per-cpu map at b98d0f8).
- **Evidence**: repeated `cmp x10,w10,SXTW; add x11,...; add x16,...; movk
  x16,#0x2bad,LSL#48; csel` sequences at b98cd88, b98d07c, b98d308, b98d3fc.
- **Severity (hypothesis)**: informational (a faithful transcription note;
  the tagged pointers are dereferenced as ordinary addresses).
- **Confidence**: high.

## [kernel-names] Confirmed-wrong assumed kernel names (2026-08-12 audit)

- **Observation**: Three kernel helper names used across the hypervisor
  reconstruction were assumed, not verified, and the disassembly proves two
  were wrong and one was misleading:
  - `kernel_memzero` (b8b6860) is NOT a memzero — it is a no-arg batch
    vm-object release (param_count=0; drains the global free list calling
    b8a9e4c = refcount-dec + queue free). Renamed
    `kernel_vm_object_batch_dealloc(void)`.
  - `kernel_alloc`/`kalloc_zalloc` (b8a6c14) is a vm-object allocation that
    returns `{error, block}` in x0/x1 (modelled as `hv_u128_t
    kernel_alloc(uint64_t, size, c, flags, e, void *f)`). The fabricated
    `kalloc_zalloc(void *out, size)` wrapper was removed.
  - `kernel_mem_validate` (b8b51c8) is actually vm_map_enter (11 args) —
    the name was a guess; the address was right.
- **Evidence**: instruction-level disassembly of b8b6860 (no argument
  loads; calls b8a9e4c in a drain loop) and b8a6c14 (writes x0/x1 as
  {err, block}); fresh decompiles of the callers b986f1c, b986d34,
  b989040, b988e70, b98533c.
- **Severity**: high for exploit research — an assumed "memzero" that
  actually frees objects changes the memory-safety picture of every call
  site that used it.
- **Confidence**: high (disassembly-verified).

## [kernel-names] Lock alias unification (b7f0afc/b7f1e80/b7f1e4c, b793cf4, b8afa78, b866ec4)

- **Observation**: Six kernel functions had multiple project names. Fresh
  decompiles confirmed the real identities and the names were unified to
  one canonical name per address:
  - b7f0afc = `lck_mtx_lock` (was lock_acquire/kernel_lock_acquire) — the
    `s_lck_mtx_t_ilk` string at fffffe0007d790b8 confirms XNU lck_mtx;
    decompile: 4 args (lock, thread, old, flags), LZCOUNT class table at
    fffffe000c5b0400.
  - b7f1e80 = `lck_mtx_unlock` (was lock_sync/kernel_lock_release2) —
    3 args (lock, thread, flags), validates *(thread+0x518)==(flags&0xfffffff)
    else panic c0e4d74, handles 0x80000000, TLB flush b96c6d4.
  - b7f1e4c = `lock_release` (was kernel_lock_release) — fast-path release:
    clears the cpu-owner slot at *(lock+8) when it equals the current cpu
    id and the debug flag is clear, else falls through to b7f1e80.
  - b793cf4 = `zfree_waitq` (was kfree_type/kernel_vcpu_detach) — zone free
    with waitq teardown; the decompiler drops the argument at most call
    sites (FUN_fffffe000b793cf4()), so the decl is a no-prototype
    `extern void zfree_waitq();`.
  - b8afa78 = `os_release` (was os_ref_release) — ARC-style release.
  - b866ec4 = `per_cpu_base` (was current_cpu_datap).
- **Evidence**: fresh decompiles of b7f0afc, b7f1e80, b7f1e4c, b793cf4,
  b8afa78, b866ec4 and the call sites b986f1c/b986d34 (both render
  FUN_fffffe000b793cf4() with the arg dropped — the old
  `kernel_vcpu_detach(name)` passed a fabricated argument).
- **Severity**: medium (naming correctness for exploit-research use; the
  fabricated `kernel_vcpu_detach(name)` argument was a latent correctness
  bug in the reconstruction).
- **Confidence**: high (fresh decompile per function).

## [kernel-names] zfree_waitq call-site argument-drop pattern

- **Observation**: The decompiler renders b793cf4 with no arguments at
  several call sites (b986f1c, b986d34) and with the object at others
  (b987c44). The no-arg form is a faithful rendering of the leftover
  register (like the b8b6860 batch-free call sites), not a missing free.
  The canonical decl is deliberately prototype-less.
- **Evidence**: fresh decompiles of b986f1c (`FUN_fffffe000b793cf4();`)
  and b986d34 (`FUN_fffffe000b793cf4();`).
- **Severity**: informational (faithfulness note).
- **Confidence**: high.

## [hv-deps] Full-audit kernel touch-set recreation wave (2026-08-12)

- **Observation**: Per the FULL-AUDIT rule (maintainer-confirmed: "these are
  recreated"), the hypervisor's DIRECT kernel touch-set was recreated with
  faithful bodies. Five files (~7150 lines) were produced:
  - hv_glue_audit_locks.c: lck_mtx_lock (b7f0afc, full futex/waitq core),
    lck_mtx_unlock (b7f1e80), lock_release (b7f1e4c), kernel_lock_ref
    (b7f62e8), kernel_spinlock_acquire/release (b7f8738/b7f8a60),
    kernel_lock_bit_acquire/release/wait4/clear/flush_ack
    (b7f8d9c/b7f8e50/b7f8ce0/b812380/b812f5c), kernel_owner_mismatch_panic
    (c0e4d74).
  - hv_glue_audit_mem.c: kernel_copyin (b8afb18 = vm_map_wire),
    kernel_copyin2 (b8b122c = vm_map_unwire), kernel_copyout (b8b49e8 =
    vm_map_protect), kernel_mem_release (b8a8078), kernel_mem_validate
    (b8b51c8 = vm_map_enter, 11 args), kernel_alloc (b8a6c14, {err,block}),
    kernel_vm_object_batch_dealloc (b8b6860, no-arg), hv_zone_alloc
    (b7eb624), kernel_kalloc (b859c38 = XNU zalloc core).
  - hv_glue_audit_obj.c: os_release (b8afa78), os_ref_retain (b7f089c),
    zfree_waitq (b793cf4), refcount_dec (b862b6c), kernel_refcount_inc
    (b8af98c), kernel_obj_release (b78cc20), kernel_region_lock (b78fd40),
    kernel_obj_lookup (b7e0f30), kernel_obj_lookup_core (b78d064),
    kernel_fault_post (b7e16f0).
  - hv_glue_audit_panic.c: kernel_panic (c0f1874), kernel_panic_a (c0f86a4,
    takes uint *refcount — the no-arg headers drop it), kernel_panic_b
    (c0f8674), kernel_panic_c (c0e1c3c, 3 real args), kernel_panic_msg_fmt
    (c0e11ec; kernel_panic_assert/msg2 are ALIASES of this address),
    kernel_zone_array_panic (c0eae24), kernel_stack_check_panic (c0e0620,
    found via the 'Kernel stack memory corruption detected' string).
  - hv_glue_audit_sys.c: per_cpu_base (b866ec4, DISASSEMBLY reconstruction —
    decompiler collapses to panic c0eae44(3)), kernel_tlb_flush (b96c6d4),
    kernel_page_validate (c0d7b94), kernel_paddr_type (c0d7c20; DRAM type
    0x1a, not 0x1b as the earlier note guessed), kernel_memattr_resolve
    (b94abbc), kernel_preempt_dec (b94172c), kernel_trace (bd30528 wrapper +
    bd310e8 core), kernel_boot_arg_get (c09cbf0, returns 1 on success not 0),
    kernel_dt_node_lookup (c09c084), kernel_dt_prop_get (c09c31c).
- **Evidence**: fresh decompiles of every function (all high confidence
  except per_cpu_base low, documented assembly fallback per AGENTS.md).
- **Severity**: high for exploit research — the touch-set (copyin/copyout,
  locks, alloc/free, refcount, panics) now has auditable bodies confirming
  what each function does; several names were corrected by the decompiles
  (kernel_copyin is vm_map_wire, not a copyin; kernel_boot_arg_get returns
  1 on success; kernel_paddr_type DRAM type is 0x1a).
- **Confidence**: high (fresh decompile per function; spot-verified
  lck_mtx_unlock, kernel_panic, zfree_waitq against the decompiles).

## [naming] Zero code-level Ghidra identifiers project-wide (2026-08-12)

- **Observation**: After the hv_el2.c kernel_vm_fault rename and the audit
  wave, every .c file in the tree now has ZERO code-level Ghidra
  identifiers (uVar*/local_*/LAB_*/joined_* appear only in comments, which
  is the documented convention). The audit files' register-reuse
  transcribers (kernel_alloc, kernel_kalloc, kernel_mem_validate,
  kernel_copyout) were renamed to English in the same pass (~250 tokens).
- **Evidence**: stateful comment-aware scan of all 17 .c files: 0 code
  tokens; all files compile with clang -fsyntax-only, 0 errors.
- **Severity**: informational (naming/readability mandate complete).
- **Confidence**: high (mechanical scan + compile).
