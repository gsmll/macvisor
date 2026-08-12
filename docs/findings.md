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
- **Evidence**: three `(**(code **)(DAT_fffffe0007e93310 + 0x1c0))(cred,
  "<entitlement>")` probes against com.apple.security.hypervisor (level 1),
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

## [entitlements] fffffe000c0f8cfc cred_has_entitlement (sandbox probe)

- **Observation**: The universal sandbox entitlement probe (DAT_fffffe0007e93310
  slot +0x1c0) is referenced from 100+ kernel sysctl/ops tables — it is the
  single choke point for entitlement checks, so a weakness here affects every
  hypervisor capability gate. Ghidra's body analysis collapses it to a 4-byte
  stub (mis-analyzed), so its exact return contract is unverified; callers
  treat "return 0 == entitled".
- **Evidence**: analyze_function_complete reports body fffffe000c0f8cfc-
  c0f8cff (4 bytes, pacibsp only) yet raw bytes show a real prologue
  (stp x29,x30; adrp; add); xref_count 100. Callers in hv_entitlements.c/
  hv_vmapple.c rely on `==0` semantics.
- **Severity (hypothesis)**: informational — universal-primitive trust anchor;
  no bug observed, but the contract is not independently confirmed.
- **Confidence**: low — the 4-byte body is a Ghidra analysis artifact, not an
  observed defect.

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

## [hv-deps] fffffe000b95c144 copyin (extern, not recreated)

- **Observation**: The universal copyin enforces a user-range bounds check
  against the current task's address-space spec before copying
  (`src < as->min` or `as->max < src+len` → returns 0xe EFAULT), and it
  special-cases a literal zero user address. It is left as an extern (100+
  kernel callers), so its full fault path is not re-audited here; the observed
  bounds check is present but the fault/fixup machinery is 2+ levels deep.
- **Evidence**: `if (uVar4 < *(ulong*)(lVar6+0x28) || *(ulong*)(lVar6+0x30) <
  uVar4+param_3) return 0xe;` in FUN_fffffe000b95c144; address-space-spec
  handling via DAT_fffffe000c62b698. Direct callee of hv_vcpu_create (b989040).
- **Severity (hypothesis)**: informational — copyin is the canonical trusted
  primitive; the hv vCPU-create path passes a user pointer for the 0x10-byte
  state structure, so the bounds contract matters, but it is kernel-owned and
  unchanged.
- **Confidence**: medium — the range check is directly observed in the
  decompile; the surrounding fault-machinery semantics are inferred.

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

## [op-table-id] fffffe000b98e488 hv_trap_op_10 — unbounded CPU-bitmask slot index

- **Observation**: The op takes the raw 64-bit trap arg as a CPU/vcpu-slot
  bitmask (no copyin). For every set bit it derives `idx = LZCOUNT(bitrev64(mask))`
  — a value in 0..63 with NO upper bound check — and then writes into the vm
  owner block at `owner + idx*0x10 + 0x12` (slot-dirty tag) and reads/writes
  `owner + idx*0x80 + 0x94` (`|= 4` busy flag), plus `plVar3 = owner + idx*0x10
  + 0x10` deref. The owner's per-slot registration table is only ~8 entries
  (7 slots allocated in hv_vm_create at `owner[0x429+j]`; 8 arrays walked in
  hv_vcpu_object_release). A guest that sets a high bit (e.g. bit 63 -> idx 63,
  writing `owner + 0x1e60 + 0x12`) indexes far past the 8-slot table.
- **Evidence**: decompile of FUN_fffffe000b98e488: `idx = LZCOUNT(uVar10 >> 0x20
  | uVar10 << 0x20); *(undefined1 *)(plVar11 + idx*0x10 + 0x12) = 1;` and later
  `puVar4 = (uint *)((long)plVar11 + idx*0x80 + 0x94); *puVar4 |= 4;` with no
  `idx < 8` / `idx < ncpu` guard before either write. param_1 is the guest trap
  arg (dispatcher FUN_fffffe000b984ed8 passes cmd+8).
- **Severity (hypothesis)**: high — guest-controlled out-of-bounds write into
  the vm owner block (dirty-tag byte + busy-flag word + a slot pointer read),
  potentially corrupting adjacent owner state, if the slot table is indeed ~8
  entries and the bitmask is not pre-masked to the physical CPU count.
- **Confidence**: medium — the unbounded 0..63 index and the two writes are
  directly observed; the ~8-entry slot-table size is inferred from the create /
  object_release paths and should be confirmed against the owner block layout
  (hv_vm_create b985588 / hv_vcpu_object_release b98533c).

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
