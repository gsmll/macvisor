# Security findings log — ring −1 (SPTM / TXM / Secure Kernel)

Every agent MUST append security-relevant observations here while decompiling.
Template (same as the hypervisor findings):

```markdown
## [<tree>] <address> <estimated_name>
- **Observation**: <what you noticed>
- **Evidence**: <Ghidra facts: instruction/offset/global/call>
- **Severity (hypothesis)**: informational | low | medium | high
- **Confidence**: high | medium | low
```

No entry without Evidence. Severity is a hypothesis, never a claim. These feed
`docs/sptm/audit.md` at the end of the project.

## [ringminus1] 000e6768 sptm_register_dispatch_table
- **Observation**: What a domain may register as a guarded dispatch endpoint is confined at registration time. For caller domains other than SK (domain 3), the endpoint function pointer must fall inside a PAPT range whose name matches the caller's registered table name; SK bypasses the range check entirely.
- **Evidence**: FUN_000e6768 stores `{fn, perm}` into the per-domain slot (base DAT_00095bf0 / 0x95470, caller-domain index, stride 0x180) only after `*slot==0`; for `caller_domain != 3` it loops `sptm_papt_ranges[]` (DAT_001012f8) checking `param_2 in [va_base, va_base+size*0x4000)` else panic 0x2c. Slots are single-write (re-register panics 0x2a).
- **Severity (hypothesis)**: informational — confinement / defense-in-depth: XNU/TXM can only register code SPTM has already mapped.
- **Confidence**: high

## [ringminus1] 000e72f4 sptm_dispatch
- **Observation**: Endpoint invocation enforces a per-endpoint permission byte against the caller's trust-level (per-CPU byte at +0xa60). Caller level 0x16 requires permission bit 0; level 0x14 requires bit 1; any violation panics (0x5e / 0x6b).
- **Evidence**: `plVar2 = table_base + (endpoint & 0xff)*0x10`; `*plVar2` = fn, `*(byte*)(plVar2+1)` = perms. Branches compare `*(char*)(cpu+0xa60)` to 0x16/0x14 and test perms bits before `FUN_000a03d4` dispatch.
- **Severity (hypothesis)**: informational — per-caller endpoint access control.
- **Confidence**: medium

## [ringminus1] 000b8f84 sptm_init
- **Observation**: Cold-boot maps every XNU/TXM/SK boot region with hard-coded FTE types/protections (BootKC, TXM, SPTM, AuxKC, CL4, TrustCache, RAMDisk, ...) and only then registers dispatch tables for XNU(0)/TXM(1)/SK(2)/HIB(10). The `exclaves_enabled` DT property decides whether SK is launched. The region set + dispatch registrations define the trust boundary XNU bootstraps into.
- **Evidence**: Series of `FUN_000d9aa8(name, type, base, pages, prot)` calls (e.g. BootKC_rx 0x23/0x141, SPTM_rx 4/0x121); then `FUN_000e6768(0,FUN_000e72f4,2)` … `(2,...,8)`, `(10,...,0x10)`; `exclaves_enabled` read from /product gates `Starting SK` path.
- **Severity (hypothesis)**: low — a boot-region type/prot table error would directly weaken page-table permissions.
- **Confidence**: medium

## [ringminus1] 000d6860 sptm_init_parse_io_space
- **Observation**: IO-space ranges are only admitted into the SPTM IO range table when they are 16K-aligned and within the DRAM window (start>>0x2a==0, page count <0x40000), and the FTE class must be 6 (0x1a); malformed DT data panics.
- **Evidence**: `(start & 0x3fff)` check, `(uVar1>>0x2a == 0) && (pages-0x40001 < 0xfffffffffffbffff)` gate, `DAT_00096bf1 != 6` panic, `FUN_000d6124(0xff000001,...)` on misalignment; IO table DAT_00095450, count DAT_00095444.
- **Severity (hypothesis)**: informational — bounds-checks IO map input.
- **Confidence**: medium

## [ringminus1] 000e6bc0 sptm_dispatch_engine
- **Observation**: Guarded-level dispatch is a state machine that panics (does not silently drop or default) on every illegal transition or dispatch. The domain field (bits 48-55) is capped at 4 and the table field (bits 32-35) at 0xf before indexing the per-domain/table handler slot; the chosen entry's permission_mask must allow the current dispatch-count index, and an XNU->TXM hop requires the prior endpoint descriptor to carry a valid '-' prefix. Any failure is a fail-closed panic.
- **Evidence**: transition table 0x16770 (state*0x1e0 + event*0x20); `domain_field > 0x4000000000000` -> panic 0x29 (VIOLATION_ILLEGAL_DISPATCH_DOMAIN); `table_field != 0` -> panic 0x2a; `(entry->permission_mask >> dc_index) & 1 == 0` -> panic 0x2b; handler==0 -> "%s: [SPTM Dispatch] Found illegal dispatch entry point"; hop_count!=1 -> "%s: Invalid hop detected when transitioning XNU->TXM %llu"; uat handoff micro_magic mismatch -> panic 0x57.
- **Severity (hypothesis)**: informational — fail-closed dispatch, but panics are the only reaction to attacker-controlled dispatch IDs, so a malicious/buggy client can panic SPTM (availability).
- **Confidence**: high

## [ringminus1] 000a9000 sptm_vectors_boot
- **Observation**: The boot vector table (16 x 0x80 slots) is fail-closed: any EL1/EL2 exception during boot saves ESR/ELR/FAR and the vector index into a per-exception state block, then enters an unbounded WFE panic-spin with x0=0xdead. There is no recovery or forwarding path.
- **Evidence**: slot 0 at 0xa9000: `adrp x8,0xaa000; add x8,x8,#0x18; ldr x8,[x8]`; if null or [x8+0x10]!=0 -> 0xa9068; saves esr_el1/elr_el1/far_el1 (or EL2 equivalents s3_6_c15_c10_5/6/7 when already in GL) to [x8+0x20/0x28/0x30]; then 0xa9068 `mov x0,#0xdead; wfe; b -1`. Slot 1 (0xa9080) identical except vector index 2.
- **Severity (hypothesis)**: informational (by design, pre-XNU no recovery); availability only — exceptions halt the boot. Not attacker-reachable after SPTM hands off.
- **Confidence**: high

## [ringminus1] 0009d000 sptm_vectors_percpu
- **Observation**: The per-CPU vector table (16 x 0x80 slots) is also fail-closed: each slot validates SP is non-null (else self-spins), saves a minimal frame, calls the full context-save handler 0x9c2dc with the exception index, then self-spins after the handler returns. The handler saves the complete register file (incl. EL2 elr/spssr/far/esr and fpsr/fpcr) before tail-branching to the exception dispatcher 0xed340 — but the slot's `b self` after `bl` means any return from the dispatcher is a spin.
- **Evidence**: slot 0 at 0x9d000 `cmp sp,#0; b.eq self; stp x29,x30,[sp,#-0x20]!; str x0,[sp,#0x18]; mov x0,#1; str x0,[sp,#0x10]; bl 0x9c2dc; b self`; 0x9c2dc builds 0x330-byte frame storing x0-x28, fp, sp_el0, q0-q31, elr_el2/spssr_el2/far_el2/esr_el2, fpsr/fpcr, then `b 0xed340`.
- **Severity (hypothesis)**: informational — design intent; the dispatcher (0xed340) is expected to be noreturn. A bug returning to the slot would hang the CPU.
- **Confidence**: high

## [ringminus1] 000ab8d8 sptm_genter_receive
- **Observation**: The single GENTER receive site in SPTM is reached only after arming the EL2 exception vectors (sync vector = 0xab84c, IRQ = 0xb7ed8) and clearing exception state; the guarded-level entry carries the endpoint via x0 (arg block) and x1 (SP). The dispatch selector semantics live in x16: clients set x16 to BUILD_DISPATCH_ID(domain, table, endpoint) before a dispatch GENTER, and the receive side decodes domain (bits 48-55) / table (32-39) / endpoint (0-31) — but this receive path itself does not consult x16, so a caller that reaches it without a validated dispatch ID relies entirely on the dispatch_engine state machine for access control.
- **Evidence**: 0xab8ac `bti c`; `msr s3_6_c15_c1_2,#1`; `msr s3_6_c15_c8_2,#0xb7ed8`; `msr s3_6_c15_c8_1,#0xab84c`; `isb`; `mov x1,sp`; `GENTER (0x00201420)` at 0xab8d8. Caller FUN_000b8f84 invokes `FUN_000ab8ac(&DAT_00106180)`.
- **Severity (hypothesis)**: low — the guarded entry trusts x0/x1 and expects the dispatch_engine to enforce domain/table permission; a mis-set x16 at an upstream client would be caught there.
- **Confidence**: medium

## [ringminus1] 000a05dc sptm_invalid_genter_handler
- **Observation**: A dedicated noreturn handler rejects any invalid guarded (GENTER) entry into SPTM: it calls the aux routine FUN_000c59f4 then panics with the "SPTM_Dispatch: Invalid GENTER" message. This is the ring-1 gate's hard rejection path for a guarded entry that does not map to a valid dispatch endpoint — the boundary between a legal and an illegal GENTER is enforced here, not merely reported.
- **Evidence**: FUN_000a05dc body is `FUN_000f89b4(); return;`; FUN_000f89b4 calls FUN_000c59f4 then `FUN_000f8804("SPTM_Dispatch: Invalid GENT...")` (string at 0xf352) which is the noreturn panic routine.
- **Severity (hypothesis)**: medium — if reachable with a partially-validated selector, an invalid GENTER would be escalated to a panic (DoS), but the guard itself is a defense-in-depth check; the real authorization is upstream.
- **Confidence**: high (panic string is explicit).

## [ringminus1] 000e6bc0 sptm_dispatch_transition (state-transition dispatcher, callee of all dispatch handlers)
- **Observation**: The guarded state-transition dispatcher is the central access-control gate of the ring-1 state machine. It (a) bounds the current state (<=0x16, else "invalid state" panic) and the event type (<=0xe, else "invalid event type" panic), (b) rejects any table entry whose next-state is >=0x17 ("invalid next state") or whose handler pointer is NULL ("invalid state transition"), (c) enforces the dispatch-domain capability bitset (plVar8[1] bit test for the target state → panic 0x2b on failure), (d) validates the arg/selector field widths (param_2>0x4000000000000 → panic 0x29; param_2 & 0xf000000000 → panic 0x2a), and (e) detects over-nested guarded calls ("Invalid hop detected when transitioning"). These are the permission checks that make the guarded levels safe to call.
- **Evidence**: FUN_000e6bc0 indexes table @0x16770 = state*0x1e0 + event*0x20; reads next-state byte [..+0x10], handler ptr [..+8], flags [..+0x18]; validates via FUN_000e7068/FUN_000e70b4; panic strings "invalid_state", "invalid_event_type", "invalid_state_transition", "invalid_next_state", "Invalid_hop_detected_when_tr", "SPTM_Dispatch Found illegal" (0xec7c); capability bit test with panic 0x2b at "0x112f5".
- **Severity (hypothesis)**: high — this is the ring-1 gate; if any of the state/event/capability bounds are bypassable, a caller could drive the state machine to an unauthorized target state. All bounds are hard panics (defense-in-depth).
- **Confidence**: medium (capability-bitset semantics inferred; panics are explicit).

## [ringminus1] 000a0adc sptm_exception_return (entry state validation upstream)
- **Observation**: The exception-return handler is only reachable through the vector-type dispatcher FUN_000e7100, which hard-validates the incoming state before dispatch: vector_type must be <=3 (else "vector_type_not_valid" panic), the xnu_el2_exception_vector global (DAT_00095cf8) must be non-NULL, and the xnu exc-return handler (DAT_00095468) must be non-NULL. This prevents returning through an uninitialized/forged exception vector.
- **Evidence**: FUN_000e7100: `if (3 < *(byte*)(cpu+0xf80)) panic("vector_type_not_valid")`; `if (*DAT_00095cf8==0) panic("xnu_el2_exception_vector_not...")`; `if (*DAT_00095468==0) panic("xnu_exc_return_handler_not_r...")`; then calls FUN_000a0adc.
- **Severity (hypothesis)**: medium — guards against returning into an unset exception vector (control-flow-integrity of the EL1 exception handoff).
- **Confidence**: high (three explicit guard panics).

## [ringminus1] 000a0f7c / 000a111c sptm_txm_sk_entry / sptm_sk_entry (guarded-level entry context-save)
- **Observation**: Both TXM/SK entry helpers enforce a single-entry invariant before saving the guarded context: they spin until the per-CPU hop counter (+0xa68) equals 1 (no nested/in-flight guarded call), mask all interrupts (DAIF=0x3c0) and switch to the EL1 stack (spsel=1) before writing the incoming arg block and callee-saved GP/FP registers into the depth-selected context bank. This is the entry state validation that prevents re-entrant/overlapping guarded calls from corrupting the saved context.
- **Evidence**: `do{}while(*(long*)(cpu+0xa68)!=1)`; `daif=daif|0x3c0`; `spsel=1`; arg block written to cpu+0xa70..0xaa8; x19-x28/x29/x30/d8-d15 to cpu+0xab0 or +0xb68; hop counter bumped `cpu[0xa68]=depth+1` before FUN_000e6bc0(3/4).
- **Severity (hypothesis)**: medium — a bypass of the hop-depth wait would allow stacked guarded calls to clobber each other's saved registers (context corruption → possible privilege confusion).
- **Confidence**: medium (invariant inferred from the spin; register-save layout faithful).

## [ringminus1] 000a1374 sptm_guest_exit_handoff (UAT handoff-region magic validation)
- **Observation**: The guest-exit/guarded-return handoff validates the UAT instance handoff-region magic (DAT_0010000c) against the per-CPU copy (uat_instance->handoff_region->mi+10) with a memory barrier; on mismatch it takes the "magic_ok=false" branch and selects a different transition event (0xb vs 9) to route to the correct lower guarded level. It also records the exit reason and resolved return PC (through the PAPT) into the SPTM exit record (DAT_000a5028) — the audit trail for guarded exits.
- **Evidence**: compares DAT_0010000c against `*(short*)(uat_instance->handoff_region->mi + cpu + 10)`; DataMemoryBarrier(2,3) on match; `FUN_000e6bc0(9, sp)` vs `FUN_000e6bc0(0xb, sp)`; exit-record writes at DAT_000a5028+0x10/0x38/0x40.
- **Severity (hypothesis)**: medium — a stale/invalidated handoff magic that is not caught could route the exit to the wrong guarded level (domain-confusion between SPTM/TXM/SK).
- **Confidence**: low (magic value semantics partly inferred).

## [ringminus1] 000a21b4 / 000a2718 / 000a28d4 sptm_panic_bad_hcr / sptm_panic_dispatch(_b)
- **Observation**: Three noreturn panic handlers report inconsistent guarded-level state: a21b4 records whether hcr_el2 matches the expected SPTM value (0x100030480000000; reason 2 vs 1) into the exit record +0x40, then panics with the dispatch name + pc/lr; a2718/a28d4 panic with the current dispatch name. These convert any unexpected register/state inconsistency into a deterministic halt rather than continuing with corrupted state.
- **Evidence**: a21b4 compares hcr_el2 to 0x100030480000000, stores reason at DAT_000a5028+0x40; all three call `FUN_000e7678(*(cpu+0xa38))` (dispatch-name lookup, panics if id>8) then `FUN_000f8804("s %s %s at pc 0x%016llx lr 0x...")`.
- **Severity (hypothesis)**: low — panic-on-invalid-state is fail-safe behavior (availability concern only).
- **Confidence**: medium.


## [trace-hib] 000c1128 sptm_hib_verify_hash_non_wired_page / 000c12a4 sptm_hib_verify_finalize_non_wired_hash — hibernation integrity gate
- **Observation**: The resume-time hibernation integrity check re-hashes every non-wired page (page index + full 16 KiB content) into the same SHA-2 context construction used at hibernation time, then finalizes a digest at DAT_00094948 (0x94948). This digest is the hibernation integrity gate: it must match the value produced by sptm_hib_finalize_image at save time. A memory-corruption or tamper that alters a hashed page is detectable because the page bytes feed the hash.
- **Evidence**: verify_hash_non_wired_page requires hib_state==8 (VERIFY) and sha_phase==5, then calls FUN_000c02bc(paddr, 1) (include_index=1) per page; verify_finalize requires the same states and runs the hash-object finalize (+0x38) then sptm_ace_finalize(FUN_000bf874) storing the digest at 0x94948, resetting sha_phase/state to 0. The page-hash core (FUN_000c02bc) feeds the 4-byte page index then 0x4000 page bytes into the SHA update (FUN_000aeaa4) — index+content binding.
- **Severity (hypothesis)**: high (this is the sole software integrity check over hibernated non-wired memory; the kernel compares the digest).
- **Confidence**: high

## [trace-hib] 000c02bc sptm_hib_hash_page_internal — single-hash enforcement / double-hash panic
- **Observation**: The page-hash core refuses to hash a page twice and records every hashed in-DRAM page by setting bit0 of its metadata descriptor byte(+3); hashing an already-hashed page panics. Out-of-DRAM (relocation-table) pages are tracked with a last-hashed cursor instead.
- **Evidence**: `if ((RES_TYPE(desc[2],2)&1)) { old=flags; flags|=1; if (old&1) sptm_panic(0x5a,...); }` in FUN_000c02bc; the out-of-DRAM path advances entry[2] (last-hashed) and returns early. Rejects double-inclusion of a page in the image hash.
- **Severity (hypothesis)**: medium (prevents an attacker/corruption from counting one page twice in the image digest; a rollback that re-hashes the same page panics).
- **Confidence**: high

## [trace-hib] 000c06ec sptm_hib_hash_page — immutable-page exclusion
- **Observation**: Non-wired hashing refuses to hash pages in the immutable range [DAT_00094990, DAT_00094998) (also constrained < 0x949a0 and < 0x949a8), panicking "attempting to hibernate immutable page". Immutable/code pages are expected to be absent from the writable non-wired image.
- **Evidence**: `if ((g_immutable_start<=paddr && paddr<g_immutable_end) && paddr<g_immutable_hi1 && paddr<g_immutable_hi2) sptm_panic_assert("attempting to hibernate immutable page %p");`
- **Severity (hypothesis)**: low (defensive; immutable pages shouldn't be in the hash set, but inclusion would not weaken the integrity gate).
- **Confidence**: high

## [trace-hib] 000bffc8 sptm_hib_hash_hibseg_page — non-DRAM hibseg exclusion
- **Observation**: Hibseg pages must lie in the DRAM hibernation range [DAT_00095d28, DAT_00095d30); a page outside it panics "Found non DRAM hibernation segment". Prevents hashing/crediting non-DRAM memory as part of the hibernation image.
- **Evidence**: `paddr = page<<14; if (paddr<g_dram_lo || g_dram_hi<=paddr) sptm_panic_assert("Found non DRAM hibernation segment");`
- **Severity (hypothesis)**: medium (bounds the set of pages accepted into the image).
- **Confidence**: high

## [trace-hib] 000bf9dc sptm_hib_begin — domain-separation salt chaining
- **Observation**: The hib hash is domain-separated per phase via 4-byte ASCII salts: hib_begin absorbs "GESH" (0x12f60) + the 0xa0-byte hibseg descriptor array; hash_hibseg_page finalize re-seeds with "1GAP" (0x12f64); finalize_sk re-seeds with "FFUB" (0x12f6c). The SK-owned pages are only hashed while sha_phase==HIBSEG (2), so SK content cannot be mixed into the wrong phase.
- **Evidence**: `sptm_sha_update(...,4,&0x12f60)`, `...4,&0x12f64`, `...4,&0x12f6c`; salt bytes confirmed as ASCII "GESH1GAP2GAPFFUB" at 0x12f60; SK-phase check `if (g_sha_phase != SHA_PHASE_HIBSEG) sptm_panic_assert("Found SK owned memory in non-SK-hash phase")` in FUN_000c02bc.
- **Severity (hypothesis)**: low (cryptographic hygiene; prevents cross-phase domain confusion).
- **Confidence**: high

## [trace-hib] 000bda44 / 000bdab4 sptm_cputrace_stop / sptm_cputrace_start — unimplemented global endpoints panic
- **Observation**: The global (non-window) cputrace stop/start endpoints are unconditional panics in this build — SPTM does not implement a global trace start/stop; only per-window VA/PA programming is available. Any caller hitting these traps halts the SPTM.
- **Evidence**: both bodies are `sptm_cputrace_state_code(); sptm_panic(0x8000000, ...);` with no other side effect.
- **Severity (hypothesis)**: informational (dead/unreachable API surface; a caller expecting global trace control would panic).
- **Confidence**: high

## [trace-hib] 000bc7fc sptm_cputrace_va_set_base — trace window validation
- **Observation**: The VA trace window must be 16 KiB aligned, 128 KiB aligned in size, be a kernel VA (bits 62-63 >= 3), fit exactly within the currently-locked frame region window (+0x38/+0x40), and the frame region is refcounted (active-window transitions). Misaligned/out-of-window programming panics. sptm_cputrace_set_base likewise confines the PA window to the carve-out (+0x18/+0x20) and 128-byte-aligned base.
- **Evidence**: `if (size==0||ovf||(base&0x3fff)||(size&0x1ffff)||(base>>0x3e)<3) sptm_panic(0x8000005,...)`; `if (base<region_start || region_start+region_size<base+size) sptm_panic(0x8000005,...)`; refcount inc/dec + `sptm_panic_assert("region->active_refcnt")` on imbalance. PA variant: `(pa_base&0x7f)||(size&0x1ffff)||pa_base<carveout_start||carveout_end<pa_base+size` -> panic 0x8000002.
- **Severity (hypothesis)**: low (validation quality — trace window cannot be programmed to arbitrary physical/VA regions).
- **Confidence**: high

## [entry-stubs] 000abdf0 sptm_secure_memcmp
- **Observation**: SPTM ships a constant-time-style (masked, full-scan) byte comparison distinct from the ordinary early-exit memcmp, and ends it with DSB + ISB barriers. This is the compare used for security-sensitive material.
- **Evidence**: FUN_000abdf0 (000abdf0-000abeaf): NEON 16-byte equality-mask compare that never short-circuits on a byte mismatch (accumulates the last-mismatch offset through a mask), followed by DataSynchronizationBarrier + InstructionSynchronizationBarrier; sibling FUN_000abcd0 (sptm_memcmp) does exit early. Mask constants DAT_000abcc0/abcc8.
- **Severity (hypothesis)**: informational (good practice — constant-time compare for secrets)
- **Confidence**: high

## [entry-stubs] 000ad278 / 000ac524 / 000acc60 printf family
- **Observation**: The SPTM printf/snprintf machinery enforces output-buffer bounds and hard-traps (SoftwareBreakpoint 0x5519) instead of silently truncating/corrupting on out-of-window or carry-overflow writes; the snprintf wrapper additionally panics (code 0xacd) if the requested size exceeds an allowed limit.
- **Evidence**: FUN_000ad020 (sptm_out_fill) and FUN_000ad0e0 (sptm_out_write) return 0 on carry (CARRY8) overflow; FUN_000acbac checks length-wrap and out-of-window with SoftwareBreakpoint(0x5519, …) in FUN_000acc5c/000acf28/000ad020/000ad0e0; FUN_000ad278 panics FUN_000ac4e0(0xacd) when limit<size.
- **Severity (hypothesis)**: low (defense-in-depth: fail-closed formatting prevents a corrupted format/buffer from producing an unbounded write in GL2)
- **Confidence**: medium

## [entry-stubs] 000ac500 sptm_panic_fmtstate → FUN_000f8804
- **Observation**: FUN_000f8804 is called with the integer 0xa28, not a string — so the "noreturn SPTM panic taking only a format string" guess recorded for FUN_000f8804 in sptm_guest_io.c's extern comment appears to be wrong; it actually takes an integer error code (likely a panic/abort code index).
- **Evidence**: FUN_000ac500 body is `FUN_000f8804(0xa28);` (constant 0xa28, not a pointer); FUN_000ac500 is invoked only from FUN_000acc60 (sptm_format_number) as `FUN_000ac500(0xa65,0xa85,0xa9d,0x158)`.
- **Severity (hypothesis)**: informational (naming/documentation correction affecting a sibling file's extern decl)
- **Confidence**: medium

## [entry-stubs] 000ab8dc sptm_el2_enable
- **Observation**: The SCTLR value written when enabling EL2 is gated on the boot-config flag DAT_00095d00: when the flag is clear the EL2 control registers are zeroed and a wider SCTLR (0x6f vs 0x2f) is programmed, enabling additional cache/feature bits.
- **Evidence**: FUN_000ab8dc: `if (DAT_00095d00 == 0) { write 3 zero regs; uVar1 = 0x6f; } else uVar1 = 0x2f;` then `UnkSytemRegWrite(3,6,0xf,1,2, uVar1)`.
- **Severity (hypothesis)**: informational (boot-config-dependent EL2 feature enable)
- **Confidence**: low

## [entry-stubs] 000ad248 sptm_stack_chk_guard
- **Observation**: Every printf/qsort epilogue validates a saved stack canary against a fixed guard slot at DAT_00100000; a mismatch routes to the noreturn stack-check panic (FUN_000ae44c). Stack-protector coverage is present across the libc/helper layer.
- **Evidence**: FUN_000ad248 disassembly: adrp/add x9,0x100000; ldr x9,[x9]; cmp x9,x8; ret; callers branch on the Z flag to FUN_000ae44c when not equal (FUN_000ac524/000acc60/000ad3b0/000ad40c epilogues).
- **Severity (hypothesis)**: informational (stack smashing protection active)
- **Confidence**: high
## [ringminus1] 000ae158 / 000ae214 / 000ae278 / 000ae3e0 sptm_memcpy_chk / sptm_memset_s_chk / sptm_strlcpy_chk / sptm_bzero_chk — fortified libc, fail-closed
- **Observation**: SPTM's bundled libc is fortified: memcpy/memset/strlcpy/bzero all bound-check the destination capacity and route any overflow to the noreturn "Security assertion" panic (FUN_000ac4e0, string 0xacd) rather than overflowing. Each carries its source file/line/function in the panic args.
- **Evidence**: ae158 `cmp x2,x3; b.hi -> FUN_000ac4e0(0xacd)` with file "src/libc/string/__memcpy_chk"(0xb56/0xb49) line 0x32; ae214 (__memset_s_chk, 0xb93/0xb84, line 0x58, "(smax) <= (obj_size)" 0xb6f); ae278 (__strlcpy_chk, 0xbbc/0xbae, line 0x36, "(len) <= (dstlen)" 0xb0c); ae3e0 (__bzero_chk, 0xc82/0xc76, line 0x2a, "(len) <= (obj_size)" 0xc62).
- **Severity (hypothesis)**: informational — defense-in-depth; a fortified-libc overflow in SPTM is a hard panic, not memory corruption.
- **Confidence**: high

## [ringminus1] 000ae44c sptm_stack_chk_fail — stack canary failure is noreturn
- **Observation**: Stack-smashing detection (canary mismatch) terminates SPTM via the noreturn panic FUN_000f8804("stack check fail" 0xc9b). There is no recovery path — a corrupted stack halts the monitor.
- **Evidence**: body is `FUN_000f8804(0xc9b);` (noreturn).
- **Severity (hypothesis)**: informational — fail-closed on stack corruption (availability only).
- **Confidence**: high

## [ringminus1] 000ae498 sptm_aes_gcm_keysize — AES key-size gate
- **Observation**: The AES-GCM entry validates the key size before scheduling: only 128/192/256-bit (0x80/0xc0/0x100) keys are admitted; anything else returns 0xfffffff9 (-7) without doing crypto work. An unsupported key size cannot reach the AES key schedule.
- **Evidence**: ae498 tests bits<0x80 against mask 0x101010000, and bits==0x80/0x100/0xc0, else returns 0xfffffff9; valid sizes tail to FUN_000b0a00 (key-schedule dispatch).
- **Severity (hypothesis)**: low (rejects malformed key sizes; prevents undersized-key crypto misuse).
- **Confidence**: high

## [ringminus1] 000b0ad4 sptm_gcm_finalize_tag — constant-time tag verification
- **Observation**: AES-GCM authentication compares the computed tag against the expected tag with a constant-time (full-scan, XOR-accumulate) compare FUN_000b03b8, so a failed authentication does not leak tag information via early-exit timing. The GCM state must be in the '3' (data) phase; any other phase returns an error (0xffffffbc) rather than authenticating. The ctx magic 0x13337 must match for the compare to run.
- **Evidence**: `if (*(int*)(p+0x78) == 0x13337) iVar1 = FUN_000b03b8(...);` where b03b8 XOR-accumulates all bytes (`bVar2 = *(byte*)(...)^*(byte*)(...)|bVar2`) and returns `bVar2 != 0`. Phase check `if (*(short*)(p+0x50) != 3) return 0xffffffbc`.
- **Severity (hypothesis)**: informational (good practice — timing-safe auth tag compare); a failure returns 0xffffffbb but does not disclose tag bytes.
- **Confidence**: high

## [ringminus1] 000b0850/000b08c0/000b0950/000b0a00 AES key expansion — bounds on key length
- **Observation**: The AES key schedule dispatcher (b0a00) only accepts 16/24/32-byte keys; any other length returns -1 (0xffffffffffffffff) and never touches the round-key buffer. The 128-bit variant writes the round count 0xa0 to ctx+0x78 and generates exactly 10 round keys.
- **Evidence**: b0a00: `if (param_3==0x10) b0850; else if (param_3==0x18) b08c0; else if (param_3==0x20) b0950; else return -1`. b0850 stores `*(param_2+0x1e)=0xa0` and loops 10 times.
- **Severity (hypothesis)**: informational — input validation on the crypto primitive.
- **Confidence**: high

## [ringminus1] 000ae504 sptm_gcm_ctx_table_build — PAC'd crypto function-pointer table
- **Observation**: The crypto context descriptor table at 0x100080 is populated with pointer-authenticated (pacia, distinct keys 0xe2e/0x392e/0xa0a9/0x307a) function pointers for the AES-GCM/key-expansion/GHASH/SHA entry points plus the context base 0x14000, and the table pointer is published at DAT_000100000. The PAC keys tie each slot to a fixed expected function.
- **Evidence**: ae504: multiple `pacia x16,x17` with keys 0xe2e,0x392e,0xa0a9,0x307a storing into [x8+0x10..0x48]; `str x19,[x8]`; `str x16,[x8+0x20/0x28/0x30/0x38]`; table ptr at 0x100000.
- **Severity (hypothesis)**: informational — control-flow integrity via PAC on crypto callbacks.
- **Confidence**: low (function identities inferred from call sites)

## [ringminus1] 000c3434 sptm_nvme_map_pages — TCB WR-permission enforcement
- **Observation**: When programming an NVMe TCB, SPTM rejects a descriptor that sets both the host-to-IP and IP-to-host write bits, and stores only a masked permission field into the per-entry perms slot.
- **Evidence**: `if (nvme_state[0x7b9] & 1 && ((tcb[0] ^ 0xffff) & 0x300) == 0) panic "Both WR bits are set"`; perms stored via `*(nvme_state + 0x140 + entry*2) = tcb[0] & 0x1f00`. Page type (4KB/2MB) for the IOMMU page ref is derived from perms bit 0x100.
- **Severity (hypothesis)**: medium — gates which DMA write directions an NVMe TCB may carry; the guard is gated on `nvme_state[0x7b9]`, so if that config bit is clear the WR-direction check is skipped.
- **Confidence**: medium

## [ringminus1] 000cfaec / 000cd0bc sptm_t8110dart_map_table / sptm_t8110dart_unmap — DMA address range gating
- **Observation**: DART map/unmap restrict the physical addresses that can be placed into the IOMMU page tables: a hard top bound (0x3ffffffffff) and an optional per-DART upper bound, plus a per-client guard serializing every table edit.
- **Evidence**: map_table: `if (dart+0xb80 == 0) { if (paddr > 0x3ffffffffff) panic 0x6000021; } else if (dart+0xb80 <= paddr) panic 0x6000021;` and the leaf FTE is validated to match instance/client/level before the PTE is written. unmap: `if (size > 0x2000000) panic 0x600000c`, and a mixed WR-direction block run is rejected (`0x6000014`), as is an absent block unless flag bit 1 is set (`0x6000022`).
- **Severity (hypothesis)**: high — these bounds and identity checks gate exactly which physical memory a DART client can DMA to/from.
- **Confidence**: medium

## [ringminus1] 000f7924 / 000f6368 sptm_guest_dispatch / sptm_guest_enter — guest-state validation
- **Observation**: Guest dispatch requires interrupts masked (DAIF 0x1c0) and validates the guest state block is an SPTM-managed physical address before copying it into scratch; guest_enter re-validates the per-CPU guest state FTE class and that VTTBR_EL2 still corresponds to the live state on exit.
- **Evidence**: dispatch: `if (~daif & 0x1c0) panic 0x54` and `if (paddr < mem_low || mem_high <= paddr) panic 6` before `sptm_copy_to_scratch(paddr, 0xa60, 1, 0)`. enter/exit validate `sptm_fte_class[state_type*0x90] == 1` and compare the reconstructed VTTBR against the live register (`panic 0x5d` on mismatch).
- **Severity (hypothesis)**: medium — prevents entering a guest with a forged/non-SPTM state block or with interrupts enabled mid-dispatch; the VTTBR consistency check on exit catches tampered translation state.
- **Confidence**: medium

## [ringminus1] 000c5a28 sptm_sart_unmap_region — permission restore + power-canary
- **Observation**: SART region teardown zeroes the three parallel SART table entries for the region, re-reads them to require they are actually zero, optionally restores saved permissions, and (when the power-gating feature is on) validates a canary magic (-0x54012113) before decrementing the region count, then releases the per-16KB-granule page references.
- **Evidence**: `if (*(datatbl+o1) || *(datatbl+o2) || *(datatbl+o3)) panic "could not zero sart region"`; canary: `if (*(int*)(sart[0x84] + sart[0x87]) != -0x54012113) panic 0x200000c`; page unref loop over `sz >> 0xe` granules.
- **Severity (hypothesis)**: medium — prevents stale SART DMA permissions from surviving region teardown; the canary check guards against use of a power-gated (stale) region table.
- **Confidence**: low

## [ringminus1] 000b2f54 / 000b2928 sptm_uat_set_ctx_id / sptm_uat_remove_ctx_id — ctx-id lifecycle
- **Observation**: UAT context ids are bound/unbound under a per-CPU guard (uat+0x60); remove clears both VTTBR present bits, bumps start/completion counters, and issues a TLBI (0,9,1,2) or a full UAT flush before the id can be reused; a live context in the per-cpu ctx table faults 0x4000016.
- **Evidence**: remove: `ttb[1] &= ~1; ttb[0] &= ~1;` then `sptm_tlbi(9,1,2,0, ctx<<0x30)` (or `sptm_uat_tlb_invalidate(...,0x1000000000,0x6000000000,0)`); the current-ctx check `if (uat[0x138] + 0x18 == ctx) panic 0x400001d`.
- **Severity (hypothesis)**: low — TLB invalidation ordering prevents stale UAT translations from being re-used after ctx teardown.
- **Confidence**: low

## [ringminus1] 000ed6b4 sptm_retype — frame-type transition rule (the security core)
- **Observation**: A frame may only be retyped along an edge present in its current type's 128-bit transition bitmask; the requested current type must exactly match the FTE's stored type; and the frame must be unreferenced (refcount 0) before retype. Any violation is a hard panic — sptm_retype cannot fail gracefully (per the SDK header).
- **Evidence**: `if ((sptm_wide_shift(&g_type_params[ft_type], new_type) & 1) == 0) sptm_violation(0x17,...)` (transition-mask edge); `if (ft_type != (current_type & 0xff)) sptm_violation(0x42,...)` (current-type match); `if (rc != 0) sptm_violation(0x3e,...)` (frame must be fresh); per-type pre/retype callbacks (DAT_00095dc0/db8) gate the transition.
- **Severity (hypothesis)**: informational — this IS the enforcement point; no weakness observed, but any error in the transition-bitmask tables would directly allow illegal type transitions (privilege confusion).
- **Confidence**: high

## [ringminus1] 000ed6b4 sptm_retype — CPU-page taggability + UAT ctx-id teardown
- **Observation**: Retyping away a taggable CPU page (class 3, cache-attr 1, byte4 bit2 set) is only allowed if the new type is also a taggable CPU page; and retyping a CPU/user-root page that still holds a UAT context id invalidates that ASID (TLBI) before the id can be reused, sweeping all ctx slots for the 0xc000=0xc000 case.
- **Evidence**: `if ((g_type_params[ft].class==3) && (g_type_attr[ft].flags) && (g_type_params[ft].cache_attr==1) && (FTE_B4&4)) { require new type also class-3/cache-attr-1 else violation(0x38); }`; UAT ctx-id block issues `SysOp_W(0,9,1,2, cid<<0x30)` (TLBI) and per-slot counters at g_uat_state+0x82..0x103.
- **Severity (hypothesis)**: low — prevents a live CPU/user root from being silently converted to a non-typed type while its ASID context is still active (stale-translation risk). The teardown ordering (clear present bits, DSB, TLBI, DSB) is correct.
- **Confidence**: high

## [ringminus1] 000ee278 sptm_map_page — frame-type rule for mappings
- **Observation**: A leaf PTE is only installed when the leaf table's type permits the data frame's type (128-bit transition bitmask) AND the requested permission bits are allowed for the data type. W+X and (for stage-2 roots) missing-NXS combinations are rejected before the PTE is written.
- **Evidence**: `if ((sptm_trans_shift(&g_type_params[leaf->type], data_type) & 1) == 0) sptm_violation(0x28,...)`; `if ((g_type_attr[data_type].flags >> perm_idx & 1) == 0) sptm_violation(0x24,...)`; WNX `1ULL << (perm) & 0x2a8` clears bit 55 (0x8000000000000) and `(old & 0x803)==3` asserts for stage-2; `(new_pte & 0xf38b000000000000)` / `(param_3>>0x34 & 1)` encoding rejection.
- **Severity (hypothesis)**: informational — this is the per-mapping authorization gate; an error in the per-type transition mask would allow mapping a frame into a table type that should not reference it.
- **Confidence**: high

## [ringminus1] 000ee278 sptm_map_page — mapping to untyped frame rejected (soft violation)
- **Observation**: The target physical address must be inside the DRAM window OR already carry a nonzero frame type; mapping into an untyped out-of-DRAM address returns a soft violation (0xff000000) rather than installing the PTE. A frame typed XNU_RESTRICTED_IO_TELEMETRY (0x27) is separately rejected (0xff000002).
- **Evidence**: `if ((pa<g_dram_hi && g_dram_lo<=pa) || (data_ft->type!=0)) { if (data_ft->type==0x27) return 0xff000002; } else return 0xff000000;` then `sptm_soft_violation(...)`.
- **Severity (hypothesis)**: informational — prevents mapping pages SPTM does not own/type; the 0x27 carve-out keeps telemetry-restricted IO out of general mappings.
- **Confidence**: high

## [ringminus1] 000f05e4 sptm_unmap_table — kernel root / shared table protection
- **Observation**: The kernel root table may not be unmapped (guarded by a sentinel root-FTE check), and a user root table (XNU_USER_ROOT_TABLE) may not unmap a shared page table (XNU_PAGE_TABLE_SHARED) — the shared table must be removed via sptm_unnest_region() first.
- **Evidence**: `if (sptm_tlb_root(root).lo == g_kernel_root_ft) sptm_violation(0,...)`; `if ((root->type==0x12) && (data_ft->type==0x15)) sptm_violation(0,...)`; transition-mask check `assert("incompatible page table type")`.
- **Severity (hypothesis)**: informational — defense-in-depth on the table hierarchy (kernel table and shared tables are not removable through the ordinary unmap path).
- **Confidence**: high

## [ringminus1] 000f458c / 000f4eec sptm_nest_region / sptm_unnest_region — shared-table identity + range confinement
- **Observation**: Nesting requires the shared table to be XNU_PAGE_TABLE_SHARED (0x15), the user and shared roots to reference the same configured shared-region id, and the VA range to lie entirely within the region recorded by sptm_configure_shared_region(); anything else panics. Unnest clears the shared PTEs and flushes the TLB.
- **Evidence**: `if (data_ft->type != 0x15) sptm_violation(0x28,...)`; `if (id != user_ft->byte4) sptm_violation(0x49,...)`; `if (va < g_shared_region_papt[id] || g_shared_region_size[id]+g_shared_region_papt[id] < size+va) sptm_violation(8,...)`; unnest `sptm_tlb_op(...)` after clearing.
- **Severity (hypothesis)**: low — bounds the nested shared mapping to the pre-configured region and rejects non-shared tables, preventing a shared-region range from being extended or aliasing arbitrary tables.
- **Confidence**: high

## [ringminus1] 000f1910 sptm_surt_free — ASID not released in the bitmap
- **Observation**: sptm_surt_free clears the SURT slot's busy flag and decrements the SURT-frame refcount but does NOT clear the ASID from g_asid_bitmap (set by sptm_surt_alloc). If SURT frames are alloc/free'd without the whole frame being destroyed (where the ASID set is presumably reclaimed), ASIDs would accumulate as busy.
- **Evidence**: alloc sets `g_asid_bitmap[asid>>6] |= 1<<(asid&0x3f)` and checks `if (bm & bit) violation(0x4b)`; free (FUN_000f1910) only touches byte4/0x50 refcounts and the slot state — no g_asid_bitmap write.
- **Severity (hypothesis)**: low — potential ASID exhaustion if subpage root tables are recycled without releasing the parent XNU_SUBPAGE_USER_ROOT_TABLES frame; likely intentional (ASIDs reclaimed on frame destroy), needs cross-check against the SURT-frame teardown path.
- **Confidence**: medium

## [ringminus1] 000f3998 sptm_update_disjoint_multipage — PAPT attr updated with current-type sentinel
- **Observation**: The per-entry PAPT (physical-aperture) attribute update passes 0xff as the current-type to sptm_set_pte_attr() — the FRAME_TYPE_ANY sentinel — rather than the frame's concrete type. The data frame's type is validated (nonzero attr flags) but the attr write is not scoped to a specific source type.
- **Evidence**: `sptm_set_pte_attr(op->paddr, 0xff, (op->papt>>2)&7, ...)` in the multipage loop (the retype path passes the concrete `type_params[new].attr` instead). The 0xff value is the FRAME_TYPE_ANY sentinel (sptm_common.h).
- **Severity (hypothesis)**: informational — 0xff is the documented FRAME_TYPE_ANY "retype entire region regardless of source type" sentinel; the PAPT attr write here is a deliberate catch-all, not an observed weakness. Noted for the audit.
- **Confidence**: medium

## [ringminus1] 000f1b78 sptm_region_op — twig-boundary confinement
- **Observation**: The contiguous-region engine refuses a region that crosses a twig-table boundary (checked against the geometry mask at +0x88), and the whole region is processed only after the walk finds the leaf table; a missing leaf table yields a per-page no-op rather than installing PTEs into a non-existent table.
- **Evidence**: `if (((count*page_size + (va-page_size)) ^ va) & *(uint64_t*)(geom+0x88)) sptm_violation(0x27,...)`; `leaf = sptm_walk(...); if (leaf==NULL) { sptm_ref_release(...); needs_tlbi=0; goto release; }`.
- **Severity (hypothesis)**: informational — prevents a single region update from silently spanning an unsupported boundary or writing through a missing table level.
- **Confidence**: high

## [ringminus1] 000b2d40 sptm_uat_tlb_invalidate — flush permission gate
- **Observation**: A UAT TLB flush over a VA range is only issued when the state's context-id is live (!=0xffff) and the state permits flushes for the requested mode; otherwise SPTM panics rather than silently skipping the invalidate. The flush granularity (16KB page vs large-page run) is selected by range size, and the large-page count is capped (span clamped to 0x200000) with a hard panic on an out-of-range span before any TLBI is emitted.
- **Evidence**: `if (mode & *state) == 0` → panic "Attempted a TLB flush on a state that disallows it"; large path computes `span = (npg<0x200001)?npg:0x200000` and panics if `span-2 > 0x1ffffe`; each invalidate dispatched through the op table at DAT_00014408 (indexed by flag).
- **Severity (hypothesis)**: low — fail-closed flush gating prevents a stale/partial UAT translation from surviving teardown; a skip would leave stale DMA mappings live.
- **Confidence**: high

## [ringminus1] 000b37fc sptm_uat_unmap_cb_table — FTE ctx-id repatch + shared-release guard
- **Observation**: The table-entry unmap callback releases the FTE backing each 16KB page: it re-derives the FTE class from the PTE, refuses to touch an FTE whose class is not the shared-table class (panic "Type / class of FTE mismatch"), and for shared FTEs validates the rw-guard refcount before releasing (panic "rw guard release shared" on 0/odd). Per-CPU flush/remove counters (0x161e/0x1607) are bumped to track TLB invalidation progress.
- **Evidence**: `if (sptm_fte_class[fte[1]*0x90] != 0x03) panic`; shared path `v=*fte; *fte=v-2; if (v==0 || (v&1)) panic`; counters `*(0x161e + cpu_id + 2/10) += 1`.
- **Severity (hypothesis)**: medium — a double-release or odd refcount on a shared table FTE would corrupt the shared-table refcount and potentially let a live table be freed; the guards make that a panic instead.
- **Confidence**: high

## [ringminus1] 000b3d90 sptm_uat_unmap_cb_leaf — leaf-present + SAPT bootstrap gating
- **Observation**: The leaf-entry unmap callback only clears a leaf PTE if it is present (else panic 0x400000e); it also requires the SAPT to be bootstrapped and the expected boot stage to have run (else panic), so an unmap cannot race a not-yet-initialized SAPT. The unmap-list at state+0x248 is bounded to 0x40 entries (no overflow).
- **Evidence**: `if (~(e&3)&3) panic 0x400000e`; `if (g_sapt_bootstrapped==0) panic "SAPT not bootstrapped"`; `if (!(g_mem_feature>>11 &1)) panic "Expected bootstrap stages"`; list append bounded `if (state[0x248] < 0x40)`.
- **Severity (hypothesis)**: medium — the boot-stage gate ties UAT unmaps to a fully-initialized SAPT; a bypass could tear down page-table entries while the SAPT ownership table is not yet authoritative.
- **Confidence**: high

## [ringminus1] 000b6524 sptm_uat_init — DT region validation (carveout/handoff/segment limits)
- **Observation**: UAT init reads gfx/gpu/handoff/shared-L2 carveout bases+sizes from SecureDT and hard-validates each: 16KB-aligned, >= one page, and (for L2) exactly 16KB; every misaligned/undersized region is a hard panic. Segment limits default to 0x40/0x100 when the DT omits them, and the segment base/size properties are likewise 16KB-aligned checked. The GPU carveout, ASC carveout and handoff region are all covered by IOMMU/device page refs on a 16KB (type 1/2) granularity.
- **Evidence**: repeated `if (sz<0x4000 || (sz&0x3fff)) panic "The X region is smaller than a page"`; `if (sz != 0x4000) panic "TTBR1 shared L2 must be 16KB"`; segment loop panics "segment base not page-aligned"; refs via sptm_iommu_region_ref(base, npages, type).
- **Severity (hypothesis)**: low — bounds the carved-out DMA regions to 16KB-aligned, sized ranges; malformed DT data is a hard panic (fail-closed boot).
- **Confidence**: high

## [ringminus1] 000b6378/000b6400 sptm_uat_retype_from_check / sptm_uat_new_type_check — UAT retype type gates
- **Observation**: UAT retype validation enforces the source type is XNU_IOMMU (0xb) and the new type is XNU_IOMMU (0x18); the new-type sub-field must be one of {0,1,5} (mask 0x33) and the current type must be in {0,3,4,5,6}. Any other combination is a hard panic (0x4000000), so an unsupported UAT frame type cannot be created by retype.
- **Evidence**: `if (src_type != 0xb) panic "retyping from XNU IOMMU but not XNU_IOMMU"`; `if (new_type != 0x18) panic "new_type not XNU_IOMMU"`; `if ((1u<<(sub&0x1f)) & 0x33) == 0) panic 0x4000000`.
- **Severity (hypothesis)**: low — fail-closed retype type/sub-type validation; prevents forging an unsupported UAT frame type.
- **Confidence**: medium

## [ringminus1] 000b25c0..000b2698 SPTM->SK/TXM entry stubs — dispatch-selector encoding
- **Observation**: The ten SPTM->SK/TXM entry stubs each hard-code a dispatch selector into x16 before tail-branching to sptm_sk_entry/sptm_txm_sk_entry: SK uses domain 3 (SK_DOMAIN) table 1 endpoints 0-3 (0x000300010000..3), TXM uses domain 2 (TXM_DOMAIN) table 1 endpoints 0-5 (0x000200010000..5). The selector is fixed at build time, so a client cannot steer these stubs to a different guarded-level endpoint — the domain/table/endpoint bits are constant.
- **Evidence**: `movk x16,#0x3/0x2, LSL#48; movk x16,#0x1, LSL#32; movk x16,#0x0..5; b sptm_sk_entry/sptm_txm_sk_entry` — ten identical 4-instruction prologues differing only in the low 16 bits of the endpoint.
- **Severity (hypothesis)**: informational — the fixed selectors make these stubs non-callable to arbitrary endpoints; the actual endpoint authorization is enforced inside the shared entry context-save + dispatch engine.
- **Confidence**: high

## [ringminus1] 000c8fb8 / 000c93d8 sptm_t8110dart_enable_translation / disable_translation — IOMMU translation enable/disable gating
- **Observation**: These are the DMA translation on/off switches for a DART stream. Enable sets the per-stream enable bit in the +0xc00 register of every DART instance whose slice is enabled; disable sets the +0xc20 (stream disable) bit. Both run under a per-CPU guard (+0xbdf) and reject a stream whose slice carries the already-active bit (panic 0x600001f). Disable additionally issues a DSB(3,3,0) between stream updates and is skipped when the +0xbe3 feature bit is set.
- **Evidence**: enable: `*(uint32_t*)(inst + (st>>5)*4 + 0xc00) = 1 << (st&0x1f)`; disable: `*(uint32_t*)(inst + (st>>5)*4 + 0xc20) = 1 << (st&0x1f)`; both acquire via sptm_dart_acquire_v1/v2 (FUN_000c92e8/000c9364) and panic 0x600001f on `slice+0x1d & 1`.
- **Severity (hypothesis)**: high — if an attacker could drive enable without a matching validated map (or disable to drop DMA translation while a device is live), the IOMMU would not constrain DMA. The per-stream guard and the acquire-variant gating (0xbf1) are the only ordering controls.
- **Confidence**: high (register addresses + guard logic explicit)

## [ringminus1] 000c9728 sptm_t8110dart_init — pre-translation configuration validation
- **Observation**: DART init validates every instance before any translation can be enabled: instance version must be one of 0x200/0x201/0x202/0x300 (else assert), all instances must agree on the version and the single supported granule (1ULL<<(t4>>0x18)), stream count must be >= the config minimums, window/granule size bounds are checked against +0xb78/+0xb7c, and each stream's PTE is cross-checked against its slice descriptor (STE bit, present bit, and page-size/limit fields). Any inconsistency is a hard assert.
- **Evidence**: `if ((4 < ver16-0x200) && (1 < ver16-0x100) && ver16 != 0x300) sptm_assert_fail("DART instance ...")`; `if (DART_VERSION != ver16) assert`; `if ((1ULL<<((t4>>0x18)&0x3f)) != ctrl->b80) assert`; per-stream PTE/slice consistency asserts (0x9769e etc).
- **Severity (hypothesis)**: medium — this is the gate that ensures only a self-consistent DART configuration is made live; an error here would allow an inconsistent (e.g. overlapping) IOMMU window configuration, but everything is fail-closed.
- **Confidence**: high

## [ringminus1] 000ce144 sptm_t8110dart_map — DMA map bounds + backing-type validation
- **Observation**: The DART map path rejects a non-canonical IOVA (iova>>0x2a != 0 -> panic 0x6000021), a page index outside the slice window (+0x10..+0x14, unless the 0xbec "non-compliant" bit is set), a map larger than 0x2000000, and a PTE that would change the physical frame/attributes of an already-present entry (panic 0x6000023). It also validates the backing page type against the IO window (in_dart) policy before locking, and records the old physical frame of any replaced entry to release it after the TLB flush.
- **Evidence**: `if (iova>>0x2a != 0) panic(0x6000021,...)`; `if (size > 0x2000000) panic(0x600000c,...)`; `if (entry != old) { if ((old^entry)&0x3ffffffc00 ... ) ... else panic(0x6000023,...) }`; `if (ptype=='=' ... ) bad_type`; win[mapped]=oldpa recorded for later `sptm_phys_unlock`.
- **Severity (hypothesis)**: high — this bounds exactly which guest physical frames a DART client can DMA to; the iova canonicality and PTE-attribute checks prevent forging translations to arbitrary physical memory.
- **Confidence**: high

## [ringminus1] 000cacd0 / 000cc5e8 sptm_t8110dart_(skip_)enable/disable_clock_protection — page-size (ps_wr) refcount + PIO lock
- **Observation**: Clock-protection (powerup/powerdown) manipulates per-stream page-size registers and is serialized by a per-CPU guard (DAT_001012c0) plus a shared page-size refcount table (DAT_001012b8, stride 6, refcount at +4). Enable increments the refcount for the instance's two page-size fields and underflows/overflow both panic; it rejects re-entrancy (0x6000026) and an invalid page-size index. Powerdown mirrors this with a decrement that must not go below 0 (ps_underflow panic). The PIO (per-instance-override) descriptors are also initialized (enable: bit set + region regs) and cleared (disable).
- **Evidence**: enable: `table[idx*6+4] = c+1` with `if (c==-1) panic("ps_refcount_overflow")` and `if (c==0) { sptm_dart_ps_refcount(ctrl,idx,1); ... }`; disable: `table[idx*6+4] = c-1` with `if (c==0) panic("ps_refcount_underflow")`; guard `if (sptm_ps_wr_guard != 0) panic(0x6000026,...)`.
- **Severity (hypothesis)**: medium — these PS writes gate the DMA window page size; a refcount imbalance (via a missing powerdown on a failed path) would leave clock-protection/PS state stale across the enable/disable pair, which the refcount-under/overflow panics are designed to catch.
- **Confidence**: medium (refcount semantics inferred from the paired inc/dec; panics are explicit)

## [ringminus1] 000b486c sptm_uat_map_continue — IOMMU ownership/type check gated on debug flag
- **Observation**: In the UAT map path, the FTE presence + IOMMU-type ownership check only runs when `(sptm_debug_flags & (t2||t3)) != 0`, where t2/t3 are memattr-derived type classes. When the debug flag is clear, SPTM skips verifying that the target FTE belongs to a supported IOMMU (sptm_iommu_dart_info bit0) and that its class is 3 before releasing its shared read-write guard. The physical-frame/page-lock logic itself still runs unconditionally.
- **Evidence**: `if (((flags & 0xc) == 0) && ((sptm_debug_flags & (t2||t3)) != 0)) { fte = sptm_fte_ptr(pa_page); if (!(iommu_dart_info[io_id*0x90]&1)) assert; if (type != 3) assert; ... }` in FUN_000b486c.
- **Severity (hypothesis)**: medium — the IOMMU-ownership check that normally prevents mapping into an unsupported/unowned DMA window is conditional on a debug/config flag; if that flag is clear in production, the enforcement is skipped (though the base/lock checks remain).
- **Confidence**: medium

## [ringminus1] 000c1e94 / 000c2908 sptm_nvme_ans_sha_reg / admin_queue_regs — NVMe BAR / queue address confinement
- **Observation**: NVMe register programming confines every queue base address to either the NVMe BAR range ([+0x760, +0x760+0x768)) or the SPTM guest region ([DAT_00095d18, DAT_00095d20)), requires 4 KiB alignment, records a once-only (0xffffffff sentinel) previous-address consistency check, and locks each accepted page with sptm_phys_lock(.., 2). The ANS SHA base must equal the page-count-derived size, and the combined AQA/IOQA attribute dword is checked against a once-written value.
- **Evidence**: `if (((paddr < BAR_BASE) || BAR_BASE+BAR_SIZE <= paddr) && (paddr < guest_lo || guest_hi <= paddr)) panic(6,...)`; `if (paddr & 0xfff) panic(0x3000003,...)`; `if (prev != 0xffffffffffffffff && paddr != prev) panic(0x3000008,...)`; `sptm_phys_lock(paddr, 2)`; ANS: `if (paddr != (NVME_PAGES<<0xe)) panic(0x300000e,...)`.
- **Severity (hypothesis)**: high — these confine NVMe DMA queue pages to the SPTM-owned guest region; a weakness here would let the NVMe controller DMA to arbitrary memory. The checks are complete and fail-closed.
- **Confidence**: high

## [ringminus1] 000c8554 sptm_t8110dart_query_tlb — serialized DART TLB read-back
- **Observation**: The TLB query builds a descriptor, serializes access via the LO lock + poll (FUN_000c786c) when the DART is not already in the serialized state (0xbe0 != 2), and writes the resulting translation (inst+0x88/0x90) into the per-CPU result block (cpu+0x1b). A non-serialized concurrent query is rejected ("Not serialized" assert).
- **Evidence**: `if (ctrl+0xbe0 != 2) { sptm_lock_acquire(); ctrl->c2c |= 1; sptm_lock_release(); if (ctrl->c2c & 1) assert("Not serialized"); memcpy(ctrl+0xbfc, q, 0x18); } do { rc=sptm_dart_poll(ctrl,0); } while(rc==0); result[0]=inst->88; result[1]=inst->90;`
- **Severity (hypothesis)**: informational — the read-back is serialized and the TLB-lookup descriptor fields are validated against the instance config before issue (panic 0x6000025).
- **Confidence**: high

## [ringminus1] 000c7bac sptm_dart_flush — flush-timeout path re-arms DART error signaling then panics
- **Observation**: The per-client DART TLB-invalidate poll loop, on persistent non-completion (after `flags&1` or 5 failed WFE-timeout retries), reads the client's +0x210 error-enable register, ORs bit0 in (`0x210 |= 1`), writes it back, and then panics. Setting that bit re-arms the DART to signal faults to SPTM as a fail-closed response to a stuck flush.
- **Evidence**: `000c7bac`: `uVar5 = FUN_000c7df8(param_1,param_2,0x210); FUN_000c7e5c(param_1,param_2,0x210,uVar5|1); FUN_000f8804("dart ... DART instance ...");` inside the `((flags&1)==0)` branch after the `deadline = cntfrq/10000000 + CNTPCT` wait loop.
- **Severity (hypothesis)**: low — the error-enable re-arm happens only after the timeout, i.e. on an already-failing device; it turns a hang into a panic (fail-closed). A guest able to stall its DART could force an SPTM panic (DoS), but the error path is gated behind the timeout.
- **Confidence**: medium

## [ringminus1] 000cc2bc/000cc3f8/000cc490/000cc540 sptm_dart_ps_refcount / write_field / write_reg — register writes gated only by client-index bounds, not register-offset permission
- **Observation**: The low-level DART register helpers write or verify 32-bit registers at a caller-supplied byte offset `reg` (only 4-aligned, mask `0xfffffffc`) with the sole guard being the client index against `ctrl+0xba4`; there is no check that `reg` falls inside the DART's actual register window. `sptm_dart_ps_refcount` additionally derives `{offset, ctrl-idx, bit}` from the global DAT_001012b8 descriptor table and writes `*(*(ctrl + desc[1]*8 + 0x228) + desc[0])` with only a descriptor-count (`DAT_001012b4`) check — no range validation of the target block/offset against the register window.
- **Evidence**: `000c7e5c` writes `*(*(long*)(ctrl+8+idx*0x78) + (reg&0xfffffffc)) = val` after `idx < *(uint*)(ctrl+0xba4)`; `000cc3f8` identical via the +0x18 sub-handle; `000cc2bc` computes `puVar1 = *(long*)(param_1 + desc[1]*8 + 0x228) + *desc` and sets/clears `*puVar1 |= 1<<desc[3]` (panics only on set/clear failure or `ps >= DAT_001012b4`).
- **Severity (hypothesis)**: medium — if any caller passes an unvalidated register offset (or a corrupt PS descriptor table is reachable), this is arbitrary 32-bit access into the DART MMIO window, bypassing the SPTM's page-table-owner role (the IOMMU permission path). Mitigating factor: these are internal helpers whose callers (000caa9c/000cacd0/000cc5e8 etc.) appear to pass validated constants/instance fields.
- **Confidence**: low (whether an untrusted register offset can reach these is not established from this batch)

## [ringminus1] 000c72f0/000c8960/000c8a14 sptm_dart_disable / save_all / save — DART fault/error registers written with masking values
- **Observation**: Disabling a DART instance (000c72f0) writes 0xffffffff to each client's error register (offset +0xbc4) and 0 to the fault register (offset +0xbcc); the per-client save path (000c8a14) re-arms the error register at offset +0xbc8 with 0xffffffff after flushing. Writing 0xffffffff/0 to these registers is a fault/error masking (acknowledge) operation — it can clear or suppress IOMMU fault indicators.
- **Evidence**: `000c72f0`: `*(undefined4*)(*plVar + (*(uint*)(ctrl+0xbc4)&0xfffffffc)) = 0xffffffff; *(undefined4*)(*plVar + (*(uint*)(ctrl+0xbcc)&0xfffffffc)) = 0;` per client; `000c8a14` tail: `*(undefined4*)(client_hw + (*(uint*)(ctrl+0xbc8)&0xfffffffc)) = 0xffffffff`.
- **Severity (hypothesis)**: low — these are teardown/save (expected) writes on the fault/error side; masking is the intended DART behavior. Only becomes notable if a teardown path is reachable while the guest still uses the DART, which would hide faults.
- **Confidence**: medium

## [ringminus1] 000b7c04 sptm_dt_get_prop — DT property value bounds check lacks carry detection
- **Observation**: The property value range check `(uintptr_t)val + size < blob_base || blob_end < (uintptr_t)val + size` computes the end address with no carry (overflow) guard on `val + size`. A property `size` field near 0xffffffff would wrap the sum; a wrapped value landing inside [base,end] would pass the check and the cursor then advances by `align4(36+size)` (sptm_dt_prop_next), walking to a garbage location before the next iteration's own bounds check panics.
- **Evidence**: `sptm_dt_get_prop`: `if ((uintptr_t)val + size < blob_base || blob_end < (uintptr_t)val + size) sptm_panic_bad_dt();` — no CARRY8-equivalent on the addition (contrast with `sptm_dt_next_sibling`/`sptm_dt_find_node` which do check `CARRY8` on the same `size+0x27` advance).
- **Severity (hypothesis)**: low — the DT blob is trusted boot data (fixed at boot), so a malicious size field requires a corrupted/attacker-supplied DT; the mis-walk is still caught by the next property/entry bounds check (fail-closed panic).
- **Confidence**: medium

## [ringminus1] 000b7898 sptm_dt_find_by_name_recursive — unbounded value read via strcmp
- **Observation**: The "name"-property match compares the property VALUE region (starting at entry+36) against "arm-io" with a plain byte loop that terminates only on NUL. If a property's value is a prefix of "arm-io" (e.g. "arm-i") the compare breaks on mismatch; but if the value equals "arm-io" and is not NUL-terminated inside its `size` bytes, the loop reads past the value into adjacent properties (still within the bound-checked blob walk, but past the logical value).
- **Evidence**: `if (strcmp((const char *)p, "name") == 0 && strcmp((const char *)(p + 36), "arm-io") == 0)` where `p+36` is the value pointer and the value length is not consulted; Ghidra shows the same byte-at-a-time compare with no size bound.
- **Severity (hypothesis)**: low — reads stay within the (bounds-checked) blob, so no OOB of the blob; a crafted DT value could only cause a spurious node match or an over-read within the blob.
- **Confidence**: medium

## [ringminus1] 000b79e8 sptm_dt_find_node — silent truncation of >63-byte path components
- **Observation**: When parsing a path component, the 64-byte scratch buffer is truncated at index 0x3f by resetting the write cursor to the buffer start (`dst = component`), so a component longer than 63 bytes is silently truncated and matched against a truncated name — a long name can be matched by a short lookup (or vice-versa) without any error.
- **Evidence**: `if (dst - component == 0x3f) { dst = component; break; }` in sptm_dt_find_node's component parser; the truncated component is then compared via strcmp against the node "name" property.
- **Severity (hypothesis)**: informational — a lookup-only parser quirk; node names in the boot DT are short, and a mismatch would just return -1 (no node found) rather than panic.
- **Confidence**: medium

## [ringminus1] 000b807c / 000bb9f0 sptm_boot_region / sptm_start_sk_ctx — boot-region property size enforced
- **Observation**: Boot-region lookups strictly require the memory-map property to be exactly 0x10 bytes (a {base,size} pair); a property of any other size panics ("DT property %s has illegal size"). This bounds the region pointers handed to the SK/TXM context construction.
- **Evidence**: `if (size != 0x10) sptm_panic("DT property %s has illegal size", name);` in sptm_boot_region, and the same check in sptm_init_kc_regions / sptm_start_sk_ctx for AuxKC_ro / AuxKC_rw.
- **Severity (hypothesis)**: informational — defensive enforcement of the fixed {base,size} property layout before its pointer is dereferenced.
- **Confidence**: high

## [ringminus1] 000c0874 sptm_hib_hash_nonwired — non-wired hash sweep is DRAM-window confined + reloc-table bound
- **Observation**: The non-wired hibernation hash sweep iterates every 16 KiB DRAM page in [g_mem_phys_base, g_mem_phys_end) but only admits a page into the hash when its FTE is active (type-table bit0), it is not in the immutable list, it is not already hashed, it is not the last hib page, and it lies inside a pmap IO range (bsearch over DAT_000950d0 with comparator 0xd649c). A page failing the IO-range membership panics (0x5b). It then validates the relocation/hash-track table (each entry end == base+count, else panic 0x5c).
- **Evidence**: `if ((sptm_res_type_table[desc[2]*0x90] & 1)==0) skip`; immutable loop over DAT_000949b4; `if ((g_io_range_count==0)||(page<*g_io_ranges)) panic 0x5b`; bsearch(key{page,0x4000,0}, g_io_ranges, 0x18, &0xd649c); `if (ent[2]!=ent[1]+ent[0]) panic 0x5c`; re-seed `sptm_sha_update(obj,ctx,4,&DAT_00012f68)`.
- **Severity (hypothesis)**: medium — the sweep is the integrity gate over writable DRAM; a page outside the pmap IO ranges is hard-refused (fail-closed) rather than silently skipped, preventing a shadow/aliased region from being omitted from the image digest.
- **Confidence**: high

## [ringminus1] 000c172c sptm_amcc_ctrr_program — CTRR begin/end validated before programming
- **Observation**: AMCC CTRR region-lock registers are only programmed after each begin<=end and neither value is 0xffffffffffffffff; an invalid pair panics "CTRR %s begin > end". No CTRR can be written with a nonsensical (empty/wrapped) region window.
- **Evidence**: per-pair `if (b[i]-1 >= 0xfffffffffffffffe) panic "begin/end invalid"`; `if (b[i] > b[i+1]) panic "CTRR %s begin > end"`; 12 sysreg writes (3,0,0xb,...); trailing ISB+TLBI alle1+DSB+ISB.
- **Severity (hypothesis)**: low — bounds-checked cache-region programming; prevents an empty/inverted AMCC region from being armed.
- **Confidence**: high

## [ringminus1] 000c1b70 sptm_amcc_cache_enable — CTRR C/D double-lock guard
- **Observation**: Enabling the AMCC cache refuses to proceed if the CTRR C (3,0,0xb,1,4) or D (3,0,0xb,1,5) registers are already locked (sign bit set), panicking "CTRR C/D already locked". This prevents re-enabling cache after a partial/unbalanced lock and keeps the cache-enable state machine single-shot.
- **Evidence**: `if (sptm_reg_read(3,0,0xb,1,4) >> 63) panic "CTRR C already locked"`; same for D; then lock_check(2/3) + lock_regs_parse + memcache_enable(2); final `sptm_reg_write(3,0,0xb,1,4,0x8000000000000001)`.
- **Severity (hypothesis)**: low — fail-closed against re-locking an already-armed cache region (availability/state-consistency).
- **Confidence**: high

## [ringminus1] 000c3c78 sptm_nvme_init — NVMe queue/TCB bounds validated from DT
- **Observation**: NVMe init rejects a zero queue-entries count ("Zero TCB entries per queue") and any count > 0x101 ("Too many TCB entries per queue"); the ANS register region must be >= 0xb pages and the /arm-io ans-reg property >= 0x40 bytes. All frame allocations are hard-checked (==0xffffffff → panic "%s invalid papt returned by"), so a missing/unmappable register frame cannot be used.
- **Evidence**: `if (entries==0) panic "Zero TCB entries"; if (entries>0x101) panic "Too many TCB entries"`; `if (ans_size>>14 < 0xb) panic "Unexpected ANS register size"`; every `sptm_frame_alloc(...)` result compared to 0xffffffff with goto alloc_fail panic; queue buffer `sptm_boot_alloc_frames(10, ...)` must be nonzero.
- **Severity (hypothesis)**: low — bounds the NVMe DMA/queue configuration from DT; prevents an undersized/oversized queue from being armed (defense-in-depth on a DMA-capable endpoint).
- **Confidence**: high

## [ringminus1] 000c5248 sptm_uat_state_get — UAT state paddr validated before use
- **Observation**: The UAT state getter validates the id (a physical address) is 16 KiB aligned within the state stride and, for a non-current state, that its FTE refcount is 0 before returning it; the resolved state's type byte must match the requested mode and its FTE flags must admit the permission mask, else panics 0x4000002/0x4000004.
- **Evidence**: `sptm_paddr_validate(id,0x18)`; alignment `if (off != q*stride || 0x4000 < stride+off) panic 0x4000005`; `if (*(int*)(va+4) != 0) { fte_get(id); panic 0x4000000; }`; `if ((*state & mask)==0) panic 0x4000002`; `if (b != mode) panic 0x4000004`.
- **Severity (hypothesis)**: low — prevents acquiring a UAT state backed by a referenced (in-use) or misaligned frame (state-confusion between UAT roots).
- **Confidence**: high

## [trace] 000bc19c sptm_boot_stage_bootkc — XNU EL2 exception vector published only inside BootKC PAPT range
- **Observation**: The BootKC bootstrap stage publishes the runtime EL1 exception vector (vbar_el1) into the XNU exception-vector slot only after proving it lies within the BootKC_rx PAPT range; a vbar outside the range panics (0x2c). This confines the address XNU's exceptions are delivered to at stage transition.
- **Evidence**: `vbar = vbar_el1`; walks PAPT table DAT_001012f8 (stride 5, name at [0]) matching "BootKC_rx" by sptm_strcmp (thunk_FUN_000ac190); `if (vbar < range[3] || range[3]+range[4]*0x4000 <= vbar) sptm_panic(0x2c,...)`; on match `*DAT_00095cf8 = vbar`, sets stage bit 0x10, SCTLR_EL1 bit0, LORelease.
- **Severity (hypothesis)**: low — fail-closed: a forged/misplaced vbar cannot be installed as the EL1 exception vector (control-flow-of-exception integrity at the SK->XNU handoff).
- **Confidence**: medium (range semantics from table stride; panic code explicit).

## [trace] 000bc19c / 000bc338 sptm_boot_stage_bootkc / sptm_boot_stage_txm — single-shot stage announcement
- **Observation**: Both stage-announce helpers hard-panic ("Attempted to announce bootstrap stage twice") if their stage bit is already set, and panic on "Unexpected bootstrap stages" if a preceding stage already ran. The bootstrap-stage bitmap (DAT_001012d8) is a monotonic, fail-closed state machine: each stage can be announced at most once.
- **Evidence**: bootkc `if ((g_feature_flags>>0x10)&1) panic_assert("Unexpected...")` then `g_feature_flags|=0x10000` with LORelease, followed by `if (!(old>>0x10)&1) return; panic_assert("Attempted...")`. txm identical with bit 0xe / 0x4000.
- **Severity (hypothesis)**: low — prevents stage replay/rollback from re-running a stage's mappings (defense-in-depth; availability via panic).
- **Confidence**: high (bit patterns and both panic strings explicit).

## [trace] 000bdf54 sptm_trace_region_add — bounded, aligned trace-region table
- **Observation**: The trace/hibernation region table is capped at 10 entries (panic "Reached the maximum number of regions") and every entry must be 16 KiB aligned (panic otherwise). Registration is gated on the bootstrap stage bit 0x13 and skipped while hibernation is enabled (DAT_00100e00 bit0), and is refused during an unexpected later stage (bit 0x14).
- **Evidence**: `if ((addr|size)&0x3fff) panic_assert("address %llx or size %zu not 16K aligned")`; `if (9 < *(u64*)0x94978) panic_assert("Reached the maximum...")`; entry at 0x949b0 + count*4 stores (addr>>14, size>>14).
- **Severity (hypothesis)**: low — bounds the set of regions accepted into the trace/hib map (availability + integrity of the region list).
- **Confidence**: high

## [trace] 000becd0 sptm_dt_key_copy — all-zero DT key rejected
- **Observation**: The DT key reader/copy helper treats a key whose bytes are all zero as invalid and panics ("key is all zero"), in addition to panicking when the key is absent or its size mismatches. A zeroed key cannot be used as a hibernation secret/seed.
- **Evidence**: scans value[0..exp_size): if every byte is '\0' → `sptm_panic_hib(...,"key is all zero",...)`; size mismatch → "key has unexpected size"; NULL → "key property found but key is NULL"; absent node → "chosen/hibernation node not found".
- **Severity (hypothesis)**: low — prevents an all-zero seed/key from being accepted into the hibernation crypto (weak-secret prevention; fail-closed panic).
- **Confidence**: high

## [trace] 000bf5d0 sptm_nvram — FTE refcount drain with underflow panic + SK-HIB begin
- **Observation**: The SK-HIB begin (misnamed sptm_nvram) drains the per-CPU callback FTE reference counts: each callback page's descriptor class must be 3 and its refcnt is decremented, with an underflow panic ("refcnt_underflow") and a class-mismatch panic ("Type %d class of FTE"). It then resets the SHA context with a phase salt and re-arms the per-CPU state (0xa30=4, 0xa68=1, 0xa60=0xc) before running the SK HIB patchup.
- **Evidence**: loop over DAT_00100cb0 callback pages: `if (g_ftype_class2[desc[1]*0x90] != 3) panic_assert("Type %d class of FTE")`; `refcnt = *(int*)(desc+6); if (refcnt==0) panic_assert("refcnt_underflow")`; else `*(int*)(desc+6)=refcnt-1`; sha_reset+update(4,&0x12f70); `if (bit 0xc && sptm_sk_hib_patchup()) panic_assert("SK HIB patchup returned error")`.
- **Severity (hypothesis)**: low — fail-closed refcount accounting during SK-HIB teardown; a double-free/underflow of a callback page is converted to a panic rather than memory corruption.
- **Confidence**: high (panic strings explicit).

## [trace] 000bf298 sptm_sha_hash_range — page-range hash selects content by FTE class
- **Observation**: The page-range hash feeds the global SHA-2 object from each 16 KiB page, but the hashed content is chosen by the page's FTE class: a zero-page-class page is hashed from a zeroed scratch buffer (so a physically-absent/zero page contributes a canonical zero block), while all other pages are hashed from their translated VA. Out-of-DRAM pages resolve through the frame descriptor; in-DRAM pages use the page-desc table.
- **Evidence**: zero-page class (`g_ftype_class[desc[1]*0x90] == 0xff`) → sptm_zero_page_begin/addr/release; else translate via linear offset (g_linear_offset) or sptm_va_lookup; SHA reset+4-byte tag then 0x4000 per page; finalize via g_sha_obj->finalize then sptm_crypto_finalize.
- **Severity (hypothesis)**: informational — the hash content reflects the SPTM's notion of the page (zero vs data), which is the basis of the hibernation image digest; a mis-classified page would change the digest (integrity gate still catches it).
- **Confidence**: medium

## [ringminus1] 000d9ec8 / 000dcf80 sptm_bootstrap_early / sptm_io_bootstrap — IO-space bounds enforcement
- **Observation**: Both large bootstrap stages gate every physical address admitted into the PAPT/IO tables. bootstrap_early rejects non-16K-aligned virt/phys/first-avail/mem-size and any page count that overflows 32 bits (mem_size >> 0x2e), and validates the /chosen dram-base/dram-size window is page-aligned. io_bootstrap, when registering pmap-io-ranges, rejects misaligned base/length, wrap-around (a+l<a), and any non-bypass range that overlaps the managed DRAM window; the sorted adjacent-range scan panics on overlap. The io-filter table likewise rejects offset+length > 0x4000 and overlapping filters, and the final IO-range table sort validates class-6 rows and adjacent overlap ("IO_Ranges %u and %u overlap").
- **Evidence**: bootstrap_early: `(param_2 & 0x3fff)`/`param_4>>0x2e` panics; io_bootstrap: `(a&0x3fff)`/`(l&0x3fff)`/CARRY(a,l)/`a < g_mem_phys_end && g_mem_phys_base < a+l` panics; post-sort `r[i+1] < r[i]+r[i].len` panic; io-filter `offset+len > 0x4000` panic.
- **Severity (hypothesis)**: medium — these bounds gate exactly which physical ranges become SPTM-managed/IO mappings; a validation gap would admit an attacker-chosen physical window into the page tables.
- **Confidence**: high

## [ringminus1] 000d9940 sptm_phystokv — mapping-count ceiling enforced
- **Observation**: The phys->VA mapping helper validates the running mapping count against a ceiling (g_max_mappings, DAT_00095108) before committing each region ("request for %u mappings exce..."), and refuses to run after the final bootstrap stage (bit 0x11). The region is carved from a monotonically-increasing VA cursor.
- **Evidence**: `if (g_max_mappings < g_mapping_count + num_pages) panic("request for %u mappings exce...")`; `if (g_bootstrap_stages bit 0x11) panic "Unexpected bootstrap stages"`; VA cursor g_mapping_va_cursor advanced by num_pages*0x4000.
- **Severity (hypothesis)**: low — bounds the number of IO/physical mappings SPTM will create, preventing unbounded VA-space exhaustion.
- **Confidence**: high

## [ringminus1] 000d6124 / 000d617c sptm_copy_phys_to_scratch(_checked) — rw-guard + frame bounds
- **Observation**: The copy-to-scratch helpers take a per-frame rw-guard refcount (+2), panic on an odd/overflowing guard (0x3d), require the source frame to be managed (class-1, panic 9), bound the copy to the 0x4000 frame (panic 0xb) and to the 0x4000 scratch (panic "Offset into scratch page cro..."), and panic on guard release underflow. The _checked variant additionally gates the whole copy on the io-mapping-enforcement (DAT_00095278) and debug-enforce (bit 0x12) bits.
- **Evidence**: `*guard = rc+2; if (rc>0xffe9 || rc&1) panic 0x3d`; `if (!(g_fte_class[guard[1]*0x90]&1)) panic 9`; `if (nbytes>0x4000 || (pa&0x3fff)+nbytes>0x4000) panic 0xb`; `if (nbytes+off>0x4000) panic "Offset into scratch page cro..."`.
- **Severity (hypothesis)**: medium — the rw-guard and size bounds prevent a translation/copy from reading/writing outside the intended managed frame or clobbering the scratch buffer.
- **Confidence**: high

## [ringminus1] 000d6088 sptm_iommu_lookup — IOMMU id / type-id bounds
- **Observation**: The IOMMU dispatch lookup bounds the high IOMMU id byte to < 9 (after subtracting 1) before indexing the per-IOMMU dispatch table (DAT_00095320), and panics "IOMMU with id %d not support..." for any non-zero unknown id. Only id 0 (global table) and 0xff (SPTM table) bypass the per-id check; a type-id >= 0xffffff would index past the 0x15578/0x15ae8 tables, but the panic path covers unknown ids.
- **Evidence**: `id = iommu_id - 1; if ((id&0xff)<9 && (DAT_00095320+id*0x20 &1)) return table[id][type+0x58]`; `else panic "IOMMU with id %d not support..."`.
- **Severity (hypothesis)**: low — bounds the IOMMU selector to the supported device table before dispatch.
- **Confidence**: medium

## [ringminus1] 000d1b2c sptm_dart_register — DART/SID/APF/carveout validation
- **Observation**: DART registration validates almost every DT-derived value with a distinct panic: dart-id < 256 and unique, vm-base/vm-size within the SoC window, vm-alignment a power of two (1..64), SID count <= 0x100, every remap src/dst SID within the SID count and distinct, sid-table length a multiple of 4, APF slice windows must not overlap the managed DRAM window or fall outside a dual-VC carveout/trusted limit, and PIOGW/clock-protection entry counts must match the instance tags. This is the primary input-validation boundary of the T8110 IOMMU driver.
- **Evidence**: `if (dart_id>0xff) panic "error: invalid..."`; `if (g_dart_id_table[id]!=-1) panic "DART_ID %u us..."`; vm-base bound `vm_bound<=vm_base -> panic`; `vm_align-1>0x3f || popcount>1 -> panic "invalid vm..."`; remap `if (sid>cnt || remap_dst) panic`; APF `for (va=win1; win0<=va; va-=0x4000) if (managed) panic "APF_slice..."`.
- **Severity (hypothesis)**: medium — these bounds confine each DART's DMA address window and SID remap to SPTM-sanctioned ranges.
- **Confidence**: medium

## [ringminus1] 000d7348 sptm_update_papt_pte — PTE-update flag validation
- **Observation**: The PTE-update path validates the paddr is managed ("paddr isn't managed"), that the flag set is exactly legal (nonzero and no bits 2-5), that the PAPT permission bit is set before a permission update, and that the cache attribute index is <= 7; every violation panics. It also refuses an update when the leaf is not present unless a fresh mapping is being installed.
- **Evidence**: `if (paddr < g_mem_phys_base || g_mem_phys_end <= paddr) panic "paddr isn't managed"`; `if (flags==0 || flags&0x3c) panic "invalid flag found while upd..."`; `if (attr>7) panic "invalid cache attribute inde..."`.
- **Severity (hypothesis)**: low — bounds what PTE mutations are expressible by callers.
- **Confidence**: high

## [ringminus1] 000e74e0 sptm_dispatch_route — guarded-call selector → event mapping
- **Observation**: The guarded-call route entry derives the transition event from the selector and performs an implicit capability check before dispatching. The low byte maps 0x1b→event 0xc, 0x1c→0xd, 0x1e→2, else 0xe; the guest-IO endpoints 0x1b/0x1c are gated on a feature flag (DAT_00095d38 bit 0) — if the feature is disabled, reaching them panics 0x5d. The domain field (bits 48-55) must be 2 or 3 (else panic 0x29), selecting events 3/4. A table field (bits 32-39) that is neither 0 nor gated routes to event 2.
- **Evidence**: `if (sel&0xff000000000000==0){ if(sel&0xff00000000==0){ lo=sel&0xff; if(lo==0x1b)evt=0xc; else if(lo==0x1c)evt=0xd; else {evt=(lo==0x1e)?2:0xe;} if(!(DAT_00095d38&1)) panic 0x5d } else evt=2 } else if(domain==2)evt=3; else if(domain!=3)panic 0x29; else evt=4;` then `sptm_dispatch_transition(evt, sel)`.
- **Severity (hypothesis)**: low — the capability check is the presence of the guest-IO feature, not a per-caller authz; a malicious caller able to set the selector to 0x1b/0x1c while the feature is off can trigger a panic (availability).
- **Confidence**: high

## [ringminus1] 000e56ac / 000e5c80 sptm_io_frame_map / sptm_io_frame_unmap — IO frame owner/permission enforcement
- **Observation**: The IO-frame map/unmap paths validate frame ownership against the current dispatch id (type 0x18 frames require the FTE owner byte == dispatch id-1; other frames require the per-type permission mask bit for the dispatch id), and reject a write-mode transition on unmap when the type's map-perm table forbids it. Every violation panics. A write-refcounted frame may not be shared.
- **Evidence**: `if (FTE_TYPE==0x18){ if(fte[6] != disp_id-1) panic "attempted to release foreign frame" } else if (!(SPTM_FTE_DISPATCH(type)>> (disp_id-1)&1)) panic "Tried releasing a frame that this dispatch doesn't own"`; unmap `if (MAPPERM(type)>>1 & 1 && wr) panic 0x39`.
- **Severity (hypothesis)**: medium — confines each IOMMU dispatch to frames SPTM has granted it, preventing cross-dispatch DMA frame access.
- **Confidence**: medium

## [ringminus1] 000e61f0 sptm_iommu_bootstrap — IOMMU dispatch-table registration
- **Observation**: IOMMU bootstrap registers guarded dispatch endpoints (via 0xe71ec, the same single-write registration slot used by sptm_register_dispatch): each IOMMU's handoff region is bound to a dispatch id whose slot must be empty (double-register panics 0x2a). For IOMMU id 2 the endpoint is registered with permission 0x12; others with 0x2. The bootstrap dispatch id is set to id+1 during registration and restored to 10 after.
- **Evidence**: `if (*(slot)==0){ register_dispatch(id, obj[0x30], obj[0x38], (id==2)?0x12:0x2); if(obj[0x40]) register_dispatch(id, obj[0x30]+1, obj[0x40], 8); } else panic "tried registering the same dispatch id twice"`.
- **Severity (hypothesis)**: informational — dispatch endpoint registration is single-write and the endpoint set is fixed at bootstrap.
- **Confidence**: low

## [ringminus1] 000e7d78 sptm_hib_setup — hibernate image validation
- **Observation**: The hibernate (HIB) setup routine validates the on-disk image1 header and bank descriptors before use: image1Size bounds, page-list length, bank ordering (first<last, non-overlap), bitmap-words vs page-count consistency, and pages-seen == page_count. The handoff pages are scanned for a valid "ho" magic before any page-table work. Every check is a noreturn panic. The IO ranges recorded from the DT must be present and non-IO-reserved for each bank page mapped.
- **Evidence**: `if (image1_size > ...) panic 0x74d`; `if (last<first) panic 0x48c`; `if (words != (last-first+0x20)>>5) panic 0x49e`; `if (pages_seen != list[1]) panic 0x4a9`; `if (!found_ho) panic 0x62b "Could not find device tree in handoff"`; `if (!(io_range->flags&1)) panic 0x5fd`.
- **Severity (hypothesis)**: low — prevents restoring from a malformed/corrupt hibernate image; the bank-descriptor validation guards against bitmap overruns.
- **Confidence**: medium

## [ringminus1] 000e9ecc / 000e9f28 sptm_assert_fail / sptm_panic_hib — fail-closed panic + CTRR output
- **Observation**: Both HIB error paths are noreturn: they write the message to the CTRR trace register and spin forever (never recover). The CTRR output path itself double-checks a config flag (tpidrro_el0 + 0x600 bit 0 and a mask at +0x61c) before touching the register — so on a misconfigured trace module it silently skips output rather than faulting.
- **Evidence**: `sptm_ctrr_puts("Assertion failed: "); ...; sptm_wait_forever()`; CTRR write gated on `if (tpidrro_el0 && (ctx[0x600]&1) && (ctx[0x61c] & config_mask))`.
- **Severity (hypothesis)**: informational — the trace channel write is best-effort, the panic always halts.
- **Confidence**: high

## [ringminus1] 000eb004 sptm_hib_restore — immutable-page exclusion on restore
- **Observation**: Restore aborts (does not overwrite) any destination page that falls in the immutable range [cpu+0x80, cpu+0x88) but outside the carved exception [cpu+0x90, cpu+0x98). A fatal panic 0xd0a "attempting to restore immutable page" fires instead.
- **Evidence**: `FUN_000e9f28(file,0xd0a,msg,cur_paddr,0)` guarded by the 4-range check on paddr_bytes = cur_paddr<<14 against cpu+0x80/0x88/0x90/0x98.
- **Severity (hypothesis)**: medium — protects immutable/code pages from being overwritten by a crafted hibernation image; the carve-out range is an attack surface if attacker-controllable.
- **Confidence**: high

## [ringminus1] 000eb004 sptm_hib_restore — image1 size bounds before use
- **Observation**: image1 size must be nonzero, must not overflow image_paddr+size (CARRY8), and image_end must not exceed 0x3fffffffc000, else panic 0xc19 "Invalid image1 size" with the size as the panic value. The bound feeds all subsequent source-list range checks.
- **Evidence**: `FUN_000e9f28(file,0xc19,s_Invalid_image1_size, size=*(hib_ctx+8), 0)` after zero/carry/cap checks.
- **Severity (hypothesis)**: medium — bounds the source ranges accepted into the restore walk.
- **Confidence**: high

## [ringminus1] 000eb004 sptm_hib_restore — dual SHA/HMAC digest binding
- **Observation**: Two independent digests bind the image: (a) 'HOFF'|img_base|img_len|imgdata hashed, ace-finalized, memcmp'd vs header handoffHeader (+0x214, panic 0x993); (b) 'PAG1'|each restored paddr|page-data hashed, ace-finalized, memcmp'd vs image1Paddr (+0x244, panic 0xa7c). Both the header counters and the actually-restored page list are bound to stored digests.
- **Evidence**: sptm_sha_init/update + vtable-finalize (sha_ctx+0x38) + FUN_000bf874 + memcmp vs hib_ctx+0x214 / +0x244.
- **Severity (hypothesis)**: medium — hash-order/counter binding detects header/region tampering.
- **Confidence**: high

## [ringminus1] 000eb004 sptm_hib_restore — CTRR key derivation hygiene
- **Observation**: CTRR keys are derived from the per-CPU CTRR counter (cpu+0x1b8) with distinct KDF labels 'key-sptm-ctrr'(0x10f30), 'key-xnu-ctrr'(0x10f3e), 'key-exclave-original'(0x10f4b), 'key-exclave'(0x10f60), and every derived key is zeroized after use (FUN_000b2584 with 0x30/0x20).
- **Evidence**: FUN_000becd0(cpu+0x1b8, dst, key, 0x30/0x20) calls + FUN_000b2584(len, buf) zeroize; string values confirmed via read_memory.
- **Severity (hypothesis)**: low — key hygiene is good; cpu+0x1b8 is the shared KDF context.
- **Confidence**: high

## [ringminus1] 000eb004 sptm_hib_restore — GCM decrypt gated on io-range table count
- **Observation**: In-place GCM decryption of compressed/protected pages is only reachable when the per-CPU io-range table count (cpu+0x7a8) is nonzero; with an empty table the encrypted page is written back un-decrypted.
- **Evidence**: in-place FUN_000b211c at LAB_000ec054 is enclosed by `if (lVar19 != 0)` on cpu+0x7a8.
- **Severity (hypothesis)**: low — an empty/controlled io-range table could leave protected pages compressed (integrity/availability), though likely always non-empty in practice.
- **Confidence**: medium

## [ringminus1] 000ed340 sptm_exception_dispatch — terminal dump-and-halt, not a 4-arg dispatcher
- **Observation**: The batch-anchored claim that 0xed340 is a 4-arg per-CPU "vector dispatcher" does not match the decompile: FUN_000ed340 takes a single frame pointer and is a register-dump-then-halt terminal (x0-x28 + fp/lr/sp/pc/cpsr/far/esr, then WaitForEvent spin / sptm_fatal 0xc0ffee). It is the terminal exception handler, not a dispatch that continues.
- **Evidence**: decompile_function 0x000ed340 shows `void FUN_000ed340(ulong param_1)` looping 0x1d regs via FUN_000ed464 then fatal FUN_0009c2c8(0xc0ffee); only caller FUN_0009c2dc builds the 0x330 frame and calls it. sptm_boot.c already declares the 4-arg sptm_exception_dispatch extern, so the name is retained with unused args.
- **Severity (hypothesis)**: informational — signature kept matching sptm_boot.c extern; body faithful to decompile.
- **Confidence**: high

## [ringminus1] 000ecd20 sptm_hib_disjoint_region — wkdm expansion loop truncated by decompiler
- **Observation**: The general wkdm decompression loop is not recovered in C: the decompiler emits "Bad instruction - Truncating control flow here" (halt_baddata). Only the validation preamble and the size==4 / size==0x4000 fast paths are reconstructable; the expansion loop is marked __builtin_trap() pending disassemble+pcode fallback.
- **Evidence**: decompile_function 0x000ecd20 warning "Control flow encountered bad instruction data" + halt_baddata at the size!=4 && size!=0x4000 branch.
- **Severity (hypothesis)**: medium — the actual decompression algorithm is unverified; confidence low for this function.
- **Confidence**: high

## [ringminus1] 000f175c sptm_surt_ft — signature mismatch vs existing pmap.c extern
- **Observation**: The faithful decompile consumes a surt_frame paddr in x0 (0x4000-aligned, range-checked, indexed into the frame table), but sptm_pmap.c declares/calls `sptm_ret2_t sptm_surt_ft(void)` (no arg) at lines 1414/1497. Callers sptm_surt_alloc/free must pass the SURT frame address.
- **Evidence**: Disassembly of 000f175c: `tst x0,#0x3fff; b.ne` panic, range check vs DAT_00095d18/20, `subs x10,x0,x8`, index into DAT_00095460. pmap.c:200 `extern sptm_ret2_t sptm_surt_ft(void);`.
- **Severity (hypothesis)**: medium — a no-arg call would read a stale/garbage x0 as the frame address; needs reconciliation in pmap.c.
- **Confidence**: high

## [ringminus1] 000ef4e0 sptm_root_ft — SURT frame special-case re-lock
- **Observation**: Root FTE validator special-cases XNU_SUBPAGE_USER_ROOT_TABLES (0x28): after locking the SURT frame FTE it re-locks the FTE at physmap-va+0x40 and validates the in-flight/use bit at va+0x50, then reads the effective type from va+0x42. Only path dereferencing the SURT per-index FTE out of the frame table proper.
- **Evidence**: disassembly 000ef4e0 @0xef578-0xef61c: physmap branch, `add x0,x8,#0x40`, second ldaddah lock, `ldrb w9,[x8,#0x50]` bit0 check, `ldrb w8,[x8,#0x42]`.
- **Severity (hypothesis)**: informational — confirms SURT frames carry per-index FTEs at va+0x40.
- **Confidence**: high

## [ringminus1] 000f29f0 sptm_pte_update — DAT_00095d54 read width/stride convention conflict
- **Observation**: The FTE refcount-flag table DAT_00095d54 is read here as a 16-bit value at stride 0x90 (`*(uint16_t*)&sptm_fte_ref[type*0x90]`), whereas sptm_region_dispatch.c's SPTM_FTE_REF treats it as a byte table at stride 0x48. Disassembly confirms 16-bit reads at byte offset type*0x90.
- **Evidence**: disasm 0x2c4c `ldrh w15,[x15,#0x4]` with x15=0x95d50+type*0x90.
- **Severity (hypothesis)**: informational — convention conflict to reconcile across regions.
- **Confidence**: high

## [ringminus1] 000f29f0 sptm_pte_update — three PTE permission-transition tables mapped
- **Observation**: Three uint32 arrays at DAT_000134f8 / 00013578 / 00013478 (indexed by a combined permission code) enforce PTE permission transitions. Named sptm_pte_trans_allow / _cond / _merge; previously unmapped in the repo.
- **Evidence**: disasm 0x2c80/0x2c9c/0x2cbc `ldr w16/w14` from 0x134f8/0x13578/0x13478 + idx*4.
- **Severity (hypothesis)**: informational — permission-transition policy tables.
- **Confidence**: high

## [ringminus1] 000f55f4 sptm_region_flags_update — non-atomic flags RMW under shared guard
- **Observation**: The flag-word update `obj[5] = (obj[5] & ~clear) | (clear & set)` is a non-atomic read-modify-write performed under only a shared (+2) rw-guard acquire, which does not exclude other shared holders — a concurrent flags update could lose a bit. The decompiler also shows a `while (puVar4[5] != puVar4[5])` self-read artifact that may conceal a barrier.
- **Evidence**: FUN_000f55f4: shared acquire `*puVar4 += 2` (LOAcquire) then plain `puVar4[5] = puVar4[5] & ~param_3 | param_3 & param_2`.
- **Severity (hypothesis)**: low — hypothesis only; shared-guard semantics may allow concurrent readers by design.
- **Confidence**: low

## [ringminus1] 000f84e4/000f8804 sptm_panic_format / sptm_panic — per-CPU panic buffer + WFE halt
- **Observation**: The core panic printer formats into a per-CPU 0xa28-byte buffer (cpu+3) and, after recording, halts the CPU in an unbounded WFE spin. A format overflow emits "PANIC_BUF_SIZE ... TRUNCATED ORIGINAL PANIC" instead of corrupting the buffer. The guarded-dispatch path hands off (FUN_000a1374) and breaks first. sptm_init.c declares sptm_panic_bad_dt(void) and sptm_panic_fmt(uint32_t,...) — signature guesses that do not match the variadic decompiles (to reconcile).
- **Evidence**: f84e4 body: snprintf into cpu+3 (0xa28), overflow branch prints truncation strings, SCTLR==0x2f selects record base, `for(;;) wfe;`. f8804 recurses with "%s: [%s] %s at pc 0x%016llx lr 0x%016llx" (0xf0b7).
- **Severity (hypothesis)**: informational — fail-closed formatting; no overflow possible.
- **Confidence**: medium

## [ringminus1] 000f719c / 000f7880 / 000f78e0 sptm_tag_op / sptm_tag_papt_multipage / sptm_untag_papt_multipage — tag/untag batch bounds + fresh-frame gate
- **Observation**: The tag/untag batch engine caps the entry count at [1,64] (the `(count-0x41)<0xffffffffffffffc0` idiom), requires each target frame to be fresh (FTE refcount 0, else panic 0x3e) and to have a present type-attr entry (panic 0x41), and only touches class-3 (XNU_TAGGABLE) frames — a non-class-3 frame is a hard "Type %d class of FTE %d" panic. The taggable bit (FTE+2 bit 2) must match the requested direction (untag requires it set, tag requires it clear; 0x35/0x36 panics otherwise). The sptm_set_pte_attr(...) leaf update must return 5 or the batch panics. DEFER_TLBI (flag bit 8) is only honored when the mode bit admits deferred flushes, else panic.
- **Evidence**: count bound `if (count<1||count>64) sptm_panic(10,...)`; `if (*ft!=0) sptm_panic(0x3e,...)`; `if (g_type_attr[type*0x48]==0) sptm_panic(0x41,...)`; `g_fte_class[type*0x90]!=3` panic; tag/untag bit checks 0x35/0x36; `sptm_set_pte_attr(cur,0xff,sub,0x82)` result must ==5; return `(flags<<0x17)>>0x1f & 5` (bit8→SPTM_UPDATE_DELAYED_TLBI).
- **Severity (hypothesis)**: informational — fail-closed validation; a non-fresh or non-taggable frame cannot be tagged, and a mismatch is a hard panic, not a silent skip.
- **Confidence**: high

## [ringminus1] 000cf7a8 sptm_dart_pte_ref_update — DMA paddr bound gate
- **Observation**: Before programming a DART client PTE reference, the target physical address is checked against the DART's configured upper bound (param_1+0xb80, defaulting to a hard 0x40000000000 cap) — a paddr at/above the bound panics 0x6000021. The whole edit runs under a per-DART guard byte (+0xbdf) derived from the per-CPU handoff magic, and the guard must still match on release (else "state guard release" panic). In the active mode the packed {paddr>>12, count} is verified against the re-read slot ("DART instance mismatch" panic).
- **Evidence**: `bound = dart+0xb80 ?: 0x40000000000; if (bound<=paddr) panic 0x6000021`; `if (dart+0xbdf!=0) panic 0x6000000`; guard = handoff_magic<<1|1; per-client loop stride 0x78, count at +0xba4; `*(uint*)(slot+8)=packed; if (re-read != packed) panic`.
- **Severity (hypothesis)**: medium — gates exactly which physical memory a DMA client can reference; a bound error would allow out-of-range DMA.
- **Confidence**: medium

## [ringminus1] 000f57c8 sptm_switch_root — kernel-root switch requires clean mask
- **Observation**: Switching to the kernel root (DAT_00095d48) only admits a fully-clean request: any of the low 16 bits set in either the mask or flags panics (code 0x10), so no arbitrary bit flips are possible on the kernel-root path. The user-root path read-locks the root FTE and re-validates its frame class (must be class 1) before reprogramming TCR/SCTLR/TTBR0 and issuing TLB invalidations; the previous root's rw-guard is released (with an underflow/overflow panic on imbalance), and a non-kernel/non-boot old root has its table refcount dropped.
- **Evidence**: `if ((mask&0xfea4)||(flags&0xfea4)) panic 0x10`; kernel branch `if ((mask&0xffff)||(flags&0xffff)) panic 0x10`; `g_fte_class[ft_type*0x90]!=1` panic; refcount overflow (>0x812) / underflow (old==0) / rw-guard-odd panics; `if ((old_ttbr&~1)!=kernel_root && !=boot_alt) drop table refcnt`.
- **Severity (hypothesis)**: informational — fail-closed root switch with per-branch validation.
- **Confidence**: medium

## [ringminus1] 0002089c txm_page_enforcement — executable-mapping authority gate
- **Observation**: This is the single authorization point deciding whether a mapping may be executable or writable-debug. It is a policy gate that mostly DENIES by default and logs "page enforcement failed" (0xbdd) on any error, but the writable-debug path permits execution when the profile holds com.apple.private.cs.debugger (0xc79) OR the association object's debug flag (+0x30 bit0) is set, gated on the global code-limits flag DAT_00071034. The comm-page region (0x1f) is always allowed if the profile +0x50 bit0 is set. The association (0xe) path computes an allowed page-entry count as `0x4000/dictsize` from the embedded DER entitlements dictionary and validates every indexed entry — an attacker-controlled DER dict that yields dictsize=0 would force a 0x4000/0 division-panic path, and an overflowing page count panics 0x93.
- **Evidence**: `if ((DAT_00071034&1)==0) {FUN_00025c6c(0xc41); err=0x1c;}`; `err=txm_entitlement_check(obj,0xc79,0); if ((err&1)==0 && (*(byte*)(obj+0x30)&1)==0) {FUN_00025c6c(0xc97); err=0x1e;}`; `u16 = dictsize ? 0x4000/dictsize : 0`; `if (0x4000 < dictsize) panic 0x91`; `if (~u16 <= hi) panic 0x93`; tail gate `bVar3 = !(err!=0x1e & err!=0 & DAT_000107f4)`.
- **Severity (hypothesis)**: high (hypothesis) — the correctness of these boolean gates IS the code-execution policy; an error in the cs.debugger / debug-flag / comm-page bits would allow disallowed executable mappings. No weakness observed, but the surface is the highest-value target in TXM.
- **Confidence**: high

## [ringminus1] 00021ddc txm_rb_insert — code-region interval overlap detector
- **Observation**: Code regions are tracked in a red-black interval tree keyed by [start+0x28, end+0x30). Insertion REFUSES (returns the colliding node, no insert) when the new interval overlaps or touches an existing one — a region cannot double-register. This prevents a second association from silently shadowing a code range.
- **Evidence**: `if (key < RB_KEY(cur) && end <= RB_KEY(cur)) go left; else if (key < RB_END(cur)) return cur; if (end <= RB_END(cur)) return cur;` — overlap/containment returns the existing node.
- **Severity (hypothesis)**: informational — data-structure integrity; duplicate-region rejection is defense-in-depth.
- **Confidence**: high

## [ringminus1] 00020e24 txm_asid_table_init — single-init ASID bitmap
- **Observation**: The ASID allocation bitmap is created once (single-slot DAT_000104f8/f4); a second init panics 0xcce. The table is 8 bytes per ASID rounded up to 16 KiB; a count that does not fit the rounded size panics 0x19. Boot-provided count bounds (0x13/0x14 panics) prevent an undersized/oversized ASID table from being installed.
- **Evidence**: `if (DAT_000104f8 != 0) panic 0xcce`; `size=(count*8+0x3fff)&0xfc000; if (count<<3 <= size)` else panic 0x19.
- **Severity (hypothesis)**: low — single-write global; prevents ASID table reconfiguration / overflow.
- **Confidence**: high

## [ringminus1] 00060c64 txm_ce_parse_typed_data — length-tag validation (fail-closed on over/under-length)
- **Observation**: The CoreEntitlements typed-data parser validates the on-disk length-tag against the object's actual size before copying any payload: kind 1 requires a 4-byte tag, kind 2 a tag of exactly 8, kind 3/4 require the declared length to equal the object byte-size rounded to words. An over-long/under-long or malformed tag returns a distinct error code (0xffffff54/55/56/5f/60) rather than copying. This bounds the copied region to the validated size.
- **Evidence**: `if (param_4 != (sz+7)>>3) return 0xffffff54` (kind 4); `if (*param_5 != 4) return 0xffffff56` (kind 1); `d=*param_5-8; if (d>=0xfffffffe) return 0xffffff55` (kind 2); payload copied only after `FUN_0003df58` (hash verify) passes.
- **Severity (hypothesis)**: medium — the length-tag gate is what prevents the CE blob from declaring a larger payload than the backing buffer; a bypass here could cause an out-of-bounds read/copy into the CE object.
- **Confidence**: medium

## [ringminus1] 00061ea4 txm_phys_to_virt — physmap confined to TXM-owned ranges + PTE page-state gate
- **Observation**: The TXM physical→virtual translation only resolves a physical address through the boot range table (base+size*0x4000 stride) or the physmap page table; every resolution path requires the target PTE's low page-state bits to be 0 (present/valid) before forming the VA (`if (~(uint)uVar4 & 3) == 0`). An unmapped or invalid page returns 4 (not a VA) — the translation cannot fabricate a mapping for memory TXM does not own.
- **Evidence**: boot-range loop `if (base<=pa && pa<base+npg*0x4000) { va=(pa-base)+r[-1]; return 0; }`; PTE path `if ((~(uint)uVar4 & 3) == 0) { va=(uVar4&0xfffffffff000)+(pa&0x3fff); }`; else returns 4.
- **Severity (hypothesis)**: low — a bogus translation would require a forged PTE; the low-bit present/valid check plus range confinement make that a hard failure.
- **Confidence**: medium

## [ringminus1] 00060088 txm_ce_object_lookup — name-table value offsets not re-validated
- **Observation**: The CoreEntitlements name lookup trusts the table entry's stored value offset (high 32 bits of each 8-byte sorted entry) when forming the returned value descriptor: `vbase = base + voff` is not re-bounds-checked against the string-buffer size before being returned to the caller. The key offset (low 32) IS used for the memcmp, but the value pointer returned to the caller is taken on trust from the table.
- **Evidence**: `voff = ent>>0x20; vbase = base+voff; out[0]=vbase; out[1]=size-voff;` — no `voff <= size` guard before use (the surrounding overflow trap 0x5519 fires only on the `name+len` addition, not on this offset).
- **Severity (hypothesis)**: medium — if the name table itself is attacker-influenced (corrupted/stale), a value offset beyond the buffer would be returned as a valid descriptor, potentially leading the caller to read out of bounds. Depends on the table being trusted (it is built at parse time), so likely low in practice.
- **Confidence**: low (offset-trust is explicit in the decompile; exploitability depends on table provenance)

## [ringminus1] 00022b10 txm_exec_debug_mapping_check — OAH/runtime executable-debug gate
- **Observation**: The executable debug-mapping authority admits a debug mapping only if the association's DER dictionary is OAH (com.apple.oah.runtime_arm_internal 0xcf7) or runtime_arm_internal (0xd1a), OR (non-JIT) the CD-hash chain validates via txm_amfi_can_exec_cdhash + txm_verify_cdhash, OR (JIT) region-authorize + a security check succeed. A legacy (<6) dictionary is only admitted if the association spans the entire requested code limit (else logged 0xd39, error 0x24). The gate is the boundary between Apple's JIT-debugger support and arbitrary writable-executable memory.
- **Evidence**: `iVar5 = txm_uuid_compare(local_a0,0xcf7); if (iVar5 != 0) iVar5 = txm_uuid_compare(local_a0,0xd1a);`; legacy path `if (local_a8 < param_5+param_4) FUN_00025c6c(0xd39), err=0x24`; `if (param_4 != local_90) err=0x12; if (param_5 != local_88) err=0x13`; non-JIT `FUN_00036d44(...)` + `FUN_000230fc(...)`; JIT `FUN_00023050(...)` + `FUN_00023cc4(local_a0)` (0xd95 log).
- **Severity (hypothesis)**: high (hypothesis) — a bypass here would permit unauthenticated executable memory; the identifier compare (0xcf7/0xd1a) against the DER dictionary identifier is the discriminator.
- **Confidence**: high

## [ringminus1] 0002270c txm_region_attach — association range confinement
- **Observation**: A code-association node may only be installed for a range that lies fully within the association object's declared range (+0x58/+0x60); out-of-range (below 0x88 / above 0x89) hard-panics. The association link count is incremented (0x4e overflow panic), and the interval insert rejects overlaps (0x75). A single object may host only one association (0x74).
- **Evidence**: `if (param_3 < *(ulong*)(uVar2+0x58)) panic 0x88; if (*(ulong*)(uVar2+0x60) < param_3+param_4) panic 0x89;`; `*(uint*)(uVar2+0x68)++` with `~DAT_000107f0` check; `FUN_00021ddc(...)` overlap -> 0x75.
- **Severity (hypothesis)**: medium — the range bounds gate which addresses a code region may be associated/executed; an off-by-one here could extend executability.
- **Confidence**: high

## [ringminus1] 0002316c txm_exec_check — JIT execution-eligibility gate
- **Observation**: Execution of a code object is gated on the object carrying dynamic-codesigning (0xdc6) or allow-jit (0xdda), or the JIT bit (+0x18 bit1). A free region (+0x24==1) without prior association is denied (0x26). The check only runs when the profile's debug-enable flag (DAT_00010678+0x4f) is set AND the code-limits global DAT_00071035 is clear; if DAT_00071035 is set the gate returns 0x18 (denied) via txm_exec_probe. This couples exec eligibility to the JIT/debug profile.
- **Evidence**: `uVar2=FUN_00022a38(param_1,0xdc6,0); if (((uVar2&1)==0) && (uVar2=FUN_00022a38(param_1,0xdda,0),(uVar2&1)==0)) { uVar1=0x26; if ((*(byte*)(param_1+0x18)&2)!=0) uVar1=0; } else uVar1=0;` and gate `(*(byte*)(DAT_00010678+0x4f)&1)!=0 && (DAT_00071035&1)==0`.
- **Severity (hypothesis)**: high (hypothesis) — the JIT/debug entitlements are the discriminator for allowed executable memory; a profile that grants 0xdc6/0xdda broadly would widen JIT exec.
- **Confidence**: high

## [ringminus1] 00023384 txm_cs_debug_policy — debug-mapping admission
- **Observation**: Debug mappings are admitted only when the caller holds com.apple.private.cs.debugger (0xc79) or the boot page-state flag DAT_000107f5 is set; otherwise "disallowed non-debugger initiated debug mapping" (0xdfb, err 0x25). A region already covering the range is marked (|0x80) and the duplicate rejected; insertion of a new 0x83 node into a conflicting interval panics 0xd1. The debugger entitlement is THE gate for creating debug code regions.
- **Evidence**: `if (((FUN_00022a38(0,0xc79,0)&1)==0) && ((DAT_000107f5&1)==0)) { FUN_00025c6c(0xdfb); uVar5=0x25; }`; region scan `if (overlap) { *(byte*)(uVar3+0x12)|=0x80; ... return 0; }`.
- **Severity (hypothesis)**: high (hypothesis) — an incorrectly-granted cs.debugger (or forced page-state flag) would permit arbitrary debug code regions.
- **Confidence**: high

## [ringminus1] 000236f0 txm_secure_channel_init — SEP-gated secure channel
- **Observation**: The SecureUI/secure-channel shared page (16 KiB) is only created when the platform feature flag is absent but SEP is present, and only on boot states 5/6 (else "secure channel not supported on this platform" 0xe8d). A security-boot mode without SEP is a hard panic (0x1141). Single-init: a second call panics 0xe60.
- **Evidence**: `if (DAT_00010518!=0) panic 0xe60`; `if (((DAT_00071031&1)==0) && (iVar3!=0)) panic("security boot mode without SEP", 0x1141)`; `if (4 < DAT_000104f2-1 && DAT_000104f2!=7) FUN_00025c6c(0xe8d)`.
- **Severity (hypothesis)**: low — availability/feature gating; a missing SEP in security boot halts (fail-closed).
- **Confidence**: high

## [txm-region-core] 00045a38 txm_verify_developer — callback-driven digest verify
- **Observation**: Developer-authorization verification is driven entirely by a caller-supplied callback table (param_4[0..3]). TXM trusts the callback table to supply the digest/verify functions; the {data_len} bound on the signature value (0x30/0x31) is the only intrinsic size check in the driver. A corrupted callback table would let the caller redirect the verify.
- **Evidence**: FUN_00045a38: `if (sig_len < 0x31) { (*cb[0])(...); (*cb[1])(...); if (*cb[4] > 0x30) return 7; (*cb[0])(...); (*cb[2])(...); }`; size cap 0x30/0x31.
- **Severity (hypothesis)**: medium — the verify integrity depends on the callback table being TXM-controlled; the 0x30 size cap bounds the signature.
- **Confidence**: medium

## [txm-region-core] 000455b8 / 00044e54 txm_im4m_decode / txm_im4m_verify — IMG4 magic dispatch
- **Observation**: The IM4M/IM4C decoder dispatches on the 4-byte magic (0x494d3443=IM4C, 0x494d344d=IM4M) and requires the manifest header element to be present (out[0x21]!=0) else returns 3. It validates that the declared data length exactly equals the input length (else 7). Fail-closed: unknown magic returns 2.
- **Evidence**: `if (param_5 == 0x494d3443) { ... } else if (param_5 != 0x494d344d) return 2;`; `if (param_4[0x21]==0) return 3;`; `if (lVar1 != param_2) return 7;` in FUN_000455b8.
- **Severity (hypothesis)**: low — the length-exactness and magic checks reject malformed IMG4 input before verification proceeds.
- **Confidence**: high

## [txm-region-core] 00044184 / 0004a2d0 txm_der_read_tlv / txm_der_read_len — fail-closed DER length handling
- **Observation**: The DER TLV decoder is fail-closed: malformed long-form tags, over-wide tag continuation (> 2^57), and payloads that exceed the remaining buffer all terminate via SoftwareBreakpoint (0x5513/0x5519) rather than returning an error that could be mis-handled. The indefinite-length form (0x80) is accepted and consumes to the end of the current buffer.
- **Evidence**: `if (uVar7 >> 0x39 != 0) return 3;` (tag width), `if (pos + plen > len) return 3;` (payload bound), trap sites 0x44370/0x4436c/0x44374.
- **Severity (hypothesis)**: low — fail-closed DER parsing prevents a truncated/malicious TLV from being walked out of bounds; traps are availability-only.
- **Confidence**: high

## [txm-region-core] 00042418 txm_ecdsa_verify — signature scalar bounds
- **Observation**: ECDSA verify checks that both r and s lie strictly inside [1, n-1] before any point multiplication; out-of-range components return 0xfffffff9 (-7). This prevents degenerate/scalar-malleability attacks (r=0, s=0, or s >= n).
- **Evidence**: `if (txm_bn_cmp(words, sig_r, 1) <= 0 || txm_bn_cmp(words, sig_r, order) >= 0) return 0xfffffff9;` (same for sig_s).
- **Severity (hypothesis)**: low — standard ECDSA sanity; bounds the accepted signature space.
- **Confidence**: medium

## [txm-region-core] 00047ba0 txm_sig_verify_policy — algorithm-class to digest-table dispatch
- **Observation**: The signature-policy selector maps the requested algorithm class (1, 4, 8, 16) to a fixed digest table (DAT_00011fe0/12018/12050/12088). An unsupported class returns 0xc0001 without producing a descriptor. The class is a caller-controlled integer, so only the enumerated digest sizes are reachable.
- **Evidence**: `switch (alg_class) { case 1: table=0x11fe0; case 4: 0x12018; case 8: 0x12050; case 0x10: 0x12088; default: return 0xc0001; }`.
- **Severity (hypothesis)**: informational — confined algorithm dispatch (no arbitrary size reaches the verify path).
- **Confidence**: medium

## [ringminus1] 00024000 txm_policy_init — boot-state keyed system policy
- **Observation**: The active TXM system policy (code-limit, debug, exec flags at 0x10618..0x10678) is selected from an 8-entry table keyed by the boot state (DAT_000104f2, 0-7); any other state is an unassignable-system-policy panic (0x1332). The platform-code-only flag (0x1351) forces bit 16 of the policy header. Policy function handlers are then wired from the table and per-profile feature bits (0x4a/0x4b/0x49), with restricted-execution-mode support logged (0x136f). An unsupported secure-channel/policy combination panics (0x1c/0x27/0xd0).
- **Evidence**: `if (DAT_000104f2==0..7) tbl = &DAT_... else panic(0x1332)`; `if ((FUN_0002a004()&1)!=0) _DAT_00010618 = CONCAT16(1,_DAT_00010618)`; feature-bit-gated function-pointer installs at 0x106e8..0x10748.
- **Severity (hypothesis)**: medium — the policy table and boot-state selection define the TXM trust/permission envelope; a mis-assigned table (wrong boot state) would install the wrong code-execution policy.
- **Confidence**: medium

## [ringminus1] 00024970 txm_trust_cache_load — prospective trust-cache build bounds
- **Observation**: Building a prospective/local trust cache validates the DER entry count against the expected number (0x54), requires the code-limit start/end pointers to match the dictionary (0x5d/0x5e), and enforces that the code-limit range lies within the local policy buffer (0x19 on out-of-range). A second load on the same object is rejected (0x51); an unsupported dictionary version (0x52) rejects. Only the entry count and pointers are cross-checked, not the individual CD hashes (validated later by the execution path).
- **Evidence**: `if (local_9c != iVar15) panic 0x54`; `if (local_b0 != local_98) panic 0x5d`; `if (local_a8 != pcVar13) panic 0x5e`; range bounds `if (pcVar10 < pcVar1 || pcVar1 < local_b0) FUN_00029a3c(0x19)`; `if (*(byte*)(param_1+0x18)&1) panic 0x51`.
- **Severity (hypothesis)**: high (hypothesis) — the trust cache is the executable-code allow-list; a bounds bug (range under/overflow) here would let the cache claim code outside the intended region.
- **Confidence**: medium

## [ringminus1] 00025160 txm_cdhash_accelerate — entitlement acceleration cache
- **Observation**: Accelerable entitlements are cached in a linked list of 0x1337-magic entries keyed by the entitlement pointer, with separate counters (DAT_00071000/004/008/00c/010) for the build-embedded vs out-of-line paths. The acceleration only proceeds when the entitlement range is a build-embedded pointer (< prospective-local-policy-gen 0x3ff9) and the range is valid; a non-embedded entitlement is silently skipped (0x28). If the entitlements are not marked accelerable (0x12aa) or cannot accelerate (0x1280), TXM panics.
- **Evidence**: `if (local_68 < s_prospective_local_policy_generat_00003ff9) {...build accel entry...}`; `*(undefined2*)puVar6 = 0x1337; *(int*)(puVar6+4) = (int)local_68`; `if (FUN_0005eb3c(local_58)!=0) panic(0x1280); if (FUN_0005eb18(local_58)!=0) panic(0x12aa)`; counter `*piVar9 = *piVar9 + 1` at 0x71000/004/008/00c/010.
- **Severity (hypothesis)**: medium — the acceleration cache is a performance fast-path over the trusted entitlement evaluation; a stale/forged 0x1337 entry (if a pointer could be made to collide) could skip re-validation.
- **Confidence**: medium

## [ringminus1] 00025780 txm_amfi_cdhash_reg — amfi.can-load-cdhash registration gate
- **Observation**: The amfi CD-hash policy block (which will gate which CD hashes may be loaded/executed) is registered only by a caller holding com.apple.private.amfi.can-load-cdhash (0x130b), or when a system policy is already selected (DAT_00010800). Single-registration (re-set panics 0x36). This couples the CD-hash allow-list policy to the private amfi entitlement.
- **Evidence**: `if (((DAT_00010800&1)==0) && (FUN_00022a38(0,s_com_apple_private_amfi_can_load__0000130b,0)==0)) return 0xe; if (DAT_00070f68!=0) panic 0x36;` then copies 7 words into 0x70f68..0x70fa0.
- **Severity (hypothesis)**: high (hypothesis) — the CD-hash policy installed here is the executable allow-list; entitlement-gated registration is the control point.
- **Confidence**: high

## [ringminus1] 00025ec4 txm_external_tc_load — boot trust-cache install
- **Observation**: At boot, trust-cache modules from the DT range are parsed and installed into the TC array with a per-module entry-count/offset table. The module count is bounds-checked (count>>0x1e, count!=0x3fffffff, count*4+4<=len), and every module pointer is validated to lie within the copied range (0x19 on OOB). A malformed range (missing/zero/short) is logged or panics (0x22-0x26). The first module is installed into the boot profile slot; the ERM trust-cache disallow policy (FUN_0002623c) is wired at the same time.
- **Evidence**: `if (count>>0x1e==0 && count!=0x3fffffff && count*4+4<=len) { loop } else panic 0x24`; module pointer bounds `if (puVar2<puVar5) FUN_00029a3c(0x19)`; `if (*puVar5==0) panic 0x23`; install via `FUN_00030f00(&DAT_00010590,...)`.
- **Severity (hypothesis)**: high (hypothesis) — the boot trust cache is the executable allow-list; an off-by-one in the module/offset table could let a malformed cache claim code ranges.
- **Confidence**: high

## [ringminus1] 00026350 txm_trust_cache_load — load-trust-cache admission
- **Observation**: Installing a trust-cache module (selector 0x03) is gated on com.apple.private.pmap.load-trust-cache (0x1448) unless a system policy is pre-selected (DAT_00010800). The module index is bounded (3..0x19; else 9/10), and the load runs under the TC lock + secure-channel entry (FUN_000262c4). This couples trust-cache installation to the private pmap entitlement.
- **Evidence**: `if (*(long*)(&DAT_000100f8+idx*0x28)!=0 && (DAT_00010800&1)==0 && FUN_00022a38(0,s_com_apple_private_pmap_load_trus_00001448,0)==0) return 0xe`; `if ((uint)param_1<3) return 9; if (0x19<(uint)param_1) return 10`.
- **Severity (hypothesis)**: high (hypothesis) — the entitlement is the gate for extending the executable allow-list.
- **Confidence**: high

## [ringminus1] 0005fb88 txm_entitlements_blob_parse — entitlements-blob policy enforcement
- **Observation**: The entitlements blob parser (magic 0x6d783f3c = "<?xm", i.e. an XML-plist header) DER-decodes the caller-supplied blob and enforces the process entitlements policy. On a non-dictionary path it falls back to imposing the identifier keys via the recursive dict parser (FUN_0005db20) and the sorted-array initializer (FUN_0005e168); failure maps to 0xff00-0xff06. The blob length is arithmetic-overflow-checked before parsing.
- **Evidence**: `if ((a & 0x8000000000000000) && (b & 0x8000000000000000)) { rc=3; }`; `txm_memcmp(a, 0x6d783f3c, 5)`; switch on the init result maps 0x1dab0..0x1daf0 to 0xff01..0xffffff06.
- **Severity (hypothesis)**: high (hypothesis) — this is the boundary at which a caller-supplied entitlements blob becomes trusted policy for code execution.
- **Confidence**: high (string/magic matched)

## [ringminus1] 000592b4 txm_manifest_trust_evaluate — manifest trust-evaluation + anti-replay
- **Observation**: The manifest trust-evaluation hub allocates the anti-replay policy object via the decode-implementation dispatch (DAT_0000d7c8/DAT_0000d7b0), boots the chip environment, and performs Img4DecodePerformTrustEvaluation followed by an anti-replay replay check. Failures log "trust evaluation failed %d", "manifest replay denied %d", "chip environment not booted %s", "failed to prepare anti-replay %s" — i.e. a manifest that fails trust eval or replay is denied. The replay check (0005c944) maps a missing (0x1f) boot-chain entry to 0x46 when the manifest flag is set, else rejects.
- **Evidence**: `uVar8 = FUN_00052da8(&DAT_0000d7c8)` (env level); `iVar7 = (*pcVar15)(param_1,local_b0+2,puVar9)` (trust eval); `uVar8 = FUN_0005c944(local_70)` (replay check); string refs 0x58ee/0x58d2/0x58b0/0x588c.
- **Severity (hypothesis)**: high (hypothesis) — the anti-replay/odometer gate is what prevents a downgraded/replayed boot manifest.
- **Confidence**: high

## [ringminus1] 000576f0-00057870 txm_runtime_* callback dispatch table — "function should never be called" dead-ends
- **Observation**: The runtime callback region (0x576f0-0x57850) is a chain of txm_runtime_* API entries (log, log_handle, get_identifier_{bool,uint,uint2,digest,cstr}, alloc_type, dealloc_type, set/roll/copy_nonce). Each entry registers its successor via FUN_00057870 and the shared terminator always panics with "function should never be called" (FUN_00029784). These are forward-declared placeholders that must be rewired at runtime; invoking an unwired slot is a fatal panic rather than a graceful no-op.
- **Evidence**: `local_20 = s__txm_runtime_log_0000548e; ... FUN_00057870(); ... FUN_00029784(s_panic__function_should_never_be_c_00005463,...)`.
- **Severity (hypothesis)**: medium (hypothesis) — a panic-on-invocation stub is fail-closed by design; the risk is if any consumer path reaches an unwired slot during early boot.
- **Confidence**: high

## [ringminus1] 0005b224/0x5b430/0x5b610/0x5b7f0/0x5bb1c txm_enforce_*_constraint — img4 property constraint engine
- **Observation**: Property constraints (bool/uint32/uint64/digest/digest64) are enforced against a fixed 8-operator set (==/!=/<=/>=/</> with 0/6 always-pass, 8 = "property is not constrained" panic). The enforcement is strict: violations are logged and the operator set rejects unknown operators with "unreachable case". The digest-length + content enforcement (0x5b7f0) and the odometer-style 64-byte comparison (0x5bb1c, FUN_0005d42c) gate anti-replay and boot-chain values.
- **Evidence**: `if (lVar4 == 8) FUN_00050d70(s_panic__property_is_not_constrain_00005dd1)`; operator dispatch on `**(long**)(param_1+0x30)`.
- **Severity (hypothesis)**: medium — the constraint engine is the policy backstop for boot-chain/anti-replay values; operator 8 panicking on "not constrained" means a mis-tagged property aborts boot.
- **Confidence**: high

## [ringminus1] 0002a674 txm_trust_cache_range — TrustCache DT range read w/o presence gate
- **Observation**: The /chosen/memory-map "TrustCache" property (base+size, 16 bytes) is read and 16K-aligned but the base is only checked for non-zero and 16K alignment, and on ANY parse failure (missing node/property/bad length) the function returns {0,0} — it never panics on absence, it silently yields an empty range. Callers that treat an empty range as "no trust cache" vs "error" must be audited; a missing TrustCache entry silently disables the range rather than failing closed.
- **Evidence**: FUN_0002a674: on `dt_get_property(...)!=1` or `len!=0x10` logs "unable to find TrustCache property" / "invalid length for TrustCache property" and returns {0,0}; alignment checks panic 0x40-0x43/0xc0 only when the property WAS found.
- **Severity (hypothesis)**: low — a boot config error (missing TrustCache) degrades to an empty range instead of halting; depends on whether downstream code treats empty as fatal.
- **Confidence**: high (string refs "/chosen/memory-map", "TrustCache" explicit)

## [ringminus1] 0002a004/2a0d8/2a1ac/2a280/2a354/2a434 txm_* DT getters — absent property default directions
- **Observation**: The /chosen boot-config getters return *val!=0 when the property exists, but diverge on absence: amfi_only_platform_code/research_enabled/erm/vmm_present return false (fail-closed), whereas sepfw_load_at_boot returns 1 (fail-open "load") and sepfw_never_boot returns 0 (fail-open "not never") when the property is missing or mis-sized. These defaults determine whether sepfw/amfi features are treated as enabled at boot.
- **Evidence**: 2a354: on parse-failure paths `return 1;`; 2a434: `return 0;`; the four *bool getters all `return false` after logging. All panic 0x11/0x29 if the DT is unavailable.
- **Severity (hypothesis)**: low — inconsistent fail-open/closed defaults across sibling getters; a stripped property set could silently enable/disable security features.
- **Confidence**: high

## [ringminus1] 0002adec txm_enter — selector dispatch is fail-closed on invalid opcode
- **Observation**: The txm_enter hub accepts opcodes 0x0-0x33; the reserved range 0x2e-0x33 and the default case return status 0x26 (and opcodes >0x33 panic 0xa1), i.e. an unknown selector yields an error status rather than silently executing. Opcode 0xd (trust-cache unload) and 0x1a (255-byte blob) add explicit `+len` overflow asserts before dispatch.
- **Evidence**: `if (0x32 < (uint)(op-1)) txm_panic(0xa1,0)`; case 0x2e..0x33 -> result=0x26; opcode 0xd `if (p2+0x10<p2) txm_assert(0x19)`; 0x1a `if (p2+0x61<p2) txm_assert(0x19)`.
- **Severity (hypothesis)**: informational — fail-closed dispatch; availability only (bad selector panics).
- **Confidence**: high

## [ringminus1] 0002cbd0 txm_image4_dispatch — handler null + input-size checked before parse
- **Observation**: The image4 dispatch validates that the handler pointer is non-null (else panic "image4 dispatch: handler %llu") and that the supplied input size exactly equals the expected size for the kind (else "image4 dispatch: input size %llu" panic) BEFORE running the handler. This prevents a partially-initialized or size-mismatched image4 payload from reaching the trust handler.
- **Evidence**: `handler = txm_img4_handler(); if (handler==0) txm_panic_str("image4 dispatch: handler %llu");` and `expected = txm_img4_input_size(kind); if (size != expected) txm_panic_str("image4 dispatch: input size %llu")`. Kind 5 additionally range-translates the code+data segments (0x29/0x3b) before calling the handler.
- **Severity (hypothesis)**: informational — fail-closed gate on the image4 handler dispatch.
- **Confidence**: high

## [ringminus1] 00032630/00032910 txm_codedir_parse / txm_codedir_mark — CodeDirectory superblob bounds + single-mark
- **Observation**: The CodeDirectory/superblob parser validates the embedded blob magic (0xcfaeddee family via -0x3ff32106 = 0xcfaeddee? no: 0xcfaeddee is -0x30511212; the checked value 0xcfaeddee? the constant -0x3ff32106 = 0xc00cdec...) and bounds-checks each entry offset/stride against the blob size (per-field 0x2xxx panics), and the mark routine (32910) refuses to mark the same CodeDirectory magic twice (bit0 set -> 0x22b61) — a duplicate CodeDirectory in one superblob is rejected. Hash-slot count * stride is validated to not overflow the blob.
- **Evidence**: 32630: magic `blob[0]==(unsigned)-0x3ff32106`, per-entry `off+sz<=total` checks with 0x2xxx class panics; 32910: `if ((*markp & 1)!=0) return 0x22b61; *markp=1;` per magic (0xfade7171/7172/8181/0c02/0b01 etc).
- **Severity (hypothesis)**: medium — a malformed superblob is rejected by hard bounds checks; duplicate-command rejection prevents CDHash ambiguity.
- **Confidence**: high (CodeDirectory magic constants are explicit)

## [ringminus1] 000345f4 txm_trust_eval — the trust decision (cdhash handling)
- **Observation**: The trust-class decision for a signed image is computed from the AMFI CMS flags vs the owner's policy masks, NOT directly from the cdhash lookup table: flags bit0 (apple) vs m0, bit1 (developer) vs m1, bit2 (adhoc) vs m2 determine trust 6/5/4/10. The cdhash/CDHash is verified during 31714 (amfi_cms_verify) via the cert-chain digest compare (318c8) and 319a8 (signature verify against the parsed CodeDirectory hash), and the per-entry cdhash membership check is gated on the profile's allow flags — an image whose cdhash is not in an allow-list but whose AMFI flags satisfy the policy masks is trusted via the flags path. This is the core authorization: AMFI CMS trust flags + policy masks + (optionally) cdhash cert-chain verification.
- **Evidence**: 345f4: `local_b8[0] & m0/m1/m2` selects trust 6 (apple flag set) / 5 / 4 (developer) / 10 or 5 (adhoc, gated on *pf and profile bits d1/d4); `txm_amfi_cms_verify` (31714) runs 3154c+476a0 hash + 47754 chain verify; 318c8 compares the cert-chain hash via memcmp. Trust result written to param_2; failure class 0x40000 on unapproved.
- **Severity (hypothesis)**: high — this is the trust decision gate; an error in the flags-vs-policy comparison or a skipped cert-chain verify would directly permit/deny code execution.
- **Confidence**: medium (flags semantics inferred from the m0/m1/m2 masks; the verify chain is explicit)

## [ringminus1] 0002fa00 txm_image4_eval — per-kind error-class mapping (AppleImage4 status)
- **Observation**: The top-level image4 evaluation maps each kind (0x0-0x19) to an AppleImage4 class/error triplet and treats a `prep` failure as an immediate error (classes 0x7-0xa0000). The status callback 2fc9c converts Image4 status codes to packed form and logs a specific message per code; unknown codes collapse to 0xaaf03.
- **Evidence**: `if (kind<3) { koperr=kind*0x10000+0x10000; kindclass=0x2100; }` else per-kind `getfn/prepfn` dispatch; 2fc9c switch on status (0/2/8/0xd/0x21/0x46/0x4f/0x50/0x5c) mapping to 0x9ab03/0x3a203/0x7a503/... and default 0xaaf03 with distinct log strings.
- **Severity (hypothesis)**: informational — the eval result is a packed error word; the exact per-kind class mapping is the API contract.
- **Confidence**: medium

## [ringminus1] 00026350 txm_trust_cache_load — entitlement gate on trust-cache load
- **Observation**: The trust-cache load path requires, for opcode <3 or <=0x19, that either the per-kind handler slot is null OR the global allow flag DAT_10800 is set OR the caller holds the `com.apple.private.pmap.load-trust-cache` entitlement (22a38) — otherwise the load is denied (error 0xe). This is the entitlement gate protecting trust-cache population.
- **Evidence**: `if (((*(long*)(&DAT_100f8 + kind*0x28)!=0) && (DAT_10800&1)==0) && (txm_entitled(0,"com.apple.private.pmap.load-trust-cache")==0)) { uVar6=0xe; ... }`; the load then calls `FUN_31060(&DAT_10590, kind, state+0x20, ...)`.
- **Severity (hypothesis)**: high — this gate controls who may add entries to a trust cache; if the entitlement check is bypassable, an unprivileged caller could populate a trust cache and authorize arbitrary code.
- **Confidence**: medium (entitlement string is explicit; gate logic inferred)

## [ringminus1] 00035f08 txm_policy_check_dispatch — restricted-execution policy dispatch
- **Observation**: TXM's code-signing policy dispatch is keyed on a rule id byte (ctx+0x101) and runs a mandatory chain of shared selectors (00035aa0/35a38/3596c/358a4/35800/35760/356e4/35650) before the per-rule checks. Two of those selectors (000356e4, 00035760) gate restricted execution on the "com.apple.private.security.research..." entitlement, and 00035800 on one of six entitlements in DAT_00010ff0. A rule id of 0 (unset) or an already-applied id (ctx+0x102) is rejected (0x10503 / 0x23403). This is the access-control boundary for which callers may run code under each policy kind.
- **Evidence**: FUN_00035f08 calls the shared selectors then FUN_000351c8/35264/35364/354c8/35550 by rule id; the 0xa0-0xac/0xe3-0xe5 base codes with class prefixes (0x10000/0x20000/...) are checked via (ret>>8)&0xff. Strings "com.apple.private.oop-jit-loader" (0x2c39), "com.apple.private.oop-jit-runner" (0x2c5a), "com.apple.private.security.research" (0x2c7b/0x2cbd).
- **Severity (hypothesis)**: medium — the policy engine's per-rule selectors are the gate TXM applies before allowing JIT/restricted code execution; an error in an entitlement test would over- or under-approve.
- **Confidence**: medium

## [ringminus1] 0003a604 / 0003a33c / 0003be50 ECDSA verify — signature verification core
- **Observation**: TXM verifies code-signing signatures via a P-256-family ECDSA verify: the core (0003a33c) validates the signature length against the curve order, imports r/s, computes u1/u2 with the big-number point ops, and combines the 16-byte digest by XOR with 0x89. The -0x92 ("hash mismatch") error is mapped to 0 (success-but-deny) at the wrappers (0003833c/0003be50/0003f6b0), and the digest comparison is constant-time (0003bf90, full-scan XOR with DIT). The verify is DIT-guarded throughout.
- **Evidence**: 0003a33c uses txm_bn_modpow + point-multiply; the digest XOR `mac[8]^mac[4]^mac[3]^mac[0xd] ^ 0x89 ^ ...`; wrappers test `r2 == -0x92`. 0003bf90 XOR-accumulates all bytes under DIT. Constants: 0x7dcdc05e magic, -0x92 = 0xffffff6e.
- **Severity (hypothesis)**: informational — the code-signing signature verify is the trust anchor; the constant-time digest compare and fail-closed error mapping are good practice.
- **Confidence**: medium

## [ringminus1] 0003d430 / 0003d05c / 0003e984 / 0003f070 big-number conditional ops — PRNG-masked constant-time selection
- **Observation**: The big-number arithmetic layer implements conditional select/subtract using a xorshift PRNG (DAT_00070040, FUN_0003d498) to derive a rotate amount, combined with the 0x5555... mask so a masked select is applied to every limb. This is the constant-time (DIT) way to avoid branch-on-secret in the ECC scalar multiply and ECDSA verify.
- **Evidence**: 0003d430/0003d05c/0003e984/0003f070 all compute `rot = (sel | rng<<1) & 0x3f` then `x & rmask ^ x & mask ^ ...`; DAT_00070040 is updated by the xorshift `x ^= x<<13; x ^= x>>7; x ^= x<<17`.
- **Severity (hypothesis)**: informational — constant-time hygiene in the crypto core; a timing leak here could leak scalar/key bits.
- **Confidence**: low (masked-select semantics inferred from the bit pattern)

## [ringminus1] 0003737c / 00037584 / 0003780c / 00037900 DER/ASN.1 reader — bounds-checked element decode
- **Observation**: TXM's DER element reader bounds-checks every length/tag decode: length fields (0x3737c) reject a canonical-form violation (leading zero / negative) and overflow, the high-tag-number decoder (0x37584) rejects underflow and >61-bit tag numbers, and the encoders (0x3780c/0x37900) fail (return 0) rather than write past the {ptr,end} buffer. Malformed input never produces an unbounded read/write.
- **Evidence**: 0x3737c checks `(long)end-(long)np < 1/2/3/4` before each long-form; 0x37584 returns 0 on `prev >> 0x39` or `>> 0x36` overflow; 0x3780c/0x37900 return 0 when `start+len > end`. This is the parser TXM uses to walk code-signing and trust-cache structures.
- **Severity (hypothesis)**: low — defense-in-depth; a parser bug here could mis-parse an attacker-controlled DER blob (availability/confusion), but all paths are fail-closed (return 0 / trap 0x19).
- **Confidence**: high (standard DER decode + explicit bounds)

## [ringminus1] 0x4b80c / 0x4c7b8 txm_ct_parse_blob / txm_ct_apply_policy — trust-cache hash-type to CS-policy-bit map
- **Observation**: The trust-cache parser maps per-entry CDHash algorithm selectors (DER OIDs) to distinct code-signing policy bits in a fixed flag word. The SHA-256 vs SHA-384 family selectors set entirely different bit ranges (e.g. 0x100008 vs 0x58600003f0d0 vs 0x8000000000), so the set of granted policy bits is determined by which hash algorithm the manifest declares — a manifest that can get its hash type accepted under a different algorithm could carry different (possibly broader) policy semantics than intended.
- **Evidence**: FUN_0004c7b8: `if (memcmp(sel,0xa252,10)==0) *flags|=0x800000100000;` `0xa25c -> 0x58600003f0d0`, `0xa197 -> 0x800000000000`, SHA-384 family (0xa14b/0xa155/0xa168) sets 0x2400000/0x400000/0x8004000000. Hash-type tags at 0xa135..0xa144 (0x551d0f/13/23/0e/25).
- **Severity (hypothesis)**: low — policy bits are additive per recognized algorithm and the selectors are length-checked (9/10/11 bytes); an unknown selector falls through without setting bits, so the risk is limited to a misclassified-but-recognized OID.
- **Confidence**: medium

## [ringminus1] 0x53cd4 txm_trap_copy_input — trap input length gate
- **Observation**: Every image4 trap handler first copies the trap input through a strict length validator: the input length must exactly equal the expected constant (0x10/0x20/0x2c/0x40...). A mismatch returns error 0x54 and logs "trap input has unexpected length" — it does NOT panic, so a caller can probe handler behavior with wrong-size inputs.
- **Evidence**: FUN_00053cd4: `if (param_4 == param_6) { copy; return 0; } else return 0x54 + log(...0x42f5);`; callers (0x53728/538a8/539ec/53ba4/53604) pass fixed sizes.
- **Severity (hypothesis)**: informational — bounds enforcement at the trap boundary; the 0x54 error path is non-fatal so malformed calls are rejected cleanly rather than corrupting state.
- **Confidence**: high

## [ringminus1] 0x54228 txm_ecid_parse — ECID format strictness
- **Observation**: The ECID parser is strict: the input must be exactly 0x24 (36) characters, digits/hex with mandatory '-' separators only at the fixed positions (bitmask 0x842100), and the trailing 6 hex fields must each be <= 3 chars. Any deviation returns 0xffffffff (malformed) rather than partially decoding. The ECID is then re-packed into a 20-byte big-endian blob.
- **Evidence**: `if (thunk_FUN_0002dc80() != 0x24) return 0xffffffff;`; separator mask `0x842100`; hex valid set `0x7e0000007e03ff`; per-field length cap 3.
- **Severity (hypothesis)**: informational — rejects malformed ECIDs, which otherwise could carry inconsistent chip-identity bits.
- **Confidence**: high

## [ringminus1] 0x54784/0x54848 txm_lock_entry / txm_lock_subsystem — single-writer TXM locks
- **Observation**: TXM entry and subsystem access are guarded by single-writer lock bytes (obj+0x29 and +0x2a). Lock faults 0x36 if already held (double-lock); unlock faults 0x38 if not held (spurious unlock). The lock is a plain byte set to -1 — a lock that is never released (e.g. a fault mid-transaction) would deadlock, but there is no timeout/owner tracking.
- **Evidence**: `if (*lock != 0) FUN_000298ec(0x36,0); *lock = -1;` and unlock `if (*lock != -1) FUN_000298ec(0x38,0); lock[0..3]=0`. Set/cleared via tag 0x7472786d ("trxm") state transitions.
- **Severity (hypothesis)**: low — the locks protect the boot/subsystem context from re-entrant modification; a fault inside a locked region leaves the lock held (availability), but there is no privilege-confusion vector observed.
- **Confidence**: high

## [ringminus1] 0x27128 txm_lock_acquire — shared refcount take not gated on the active bit
- **Observation**: The shared-take path (mode 0) increments the object's +0x10 reference counter and only afterwards checks the +0x11 active bit (fault 0x35). A shared acquire therefore bumps the count of an object that is not marked active, and the "no-increment" exclusive path clears the counter via a 4-byte write that also wipes +0x11 — allowing a caller to clear another object's active bit by manipulating the shared path.
- **Evidence**: `count = *(uint8_t*)(obj+0x10); if (count<0xfe) { CAS-increment; } goto check_active;` where check_active faults 0x35 only when `need_increment`; the exclusive branch does `*(uint32_t*)(obj+0x10)=0` (clears 4 bytes: counter+active). Panics 0x34/0x35/0x36/0x38 bound the state machine.
- **Severity (hypothesis)**: low-medium — the refcount byte saturates at 0xfe (0x38 fault), bounding increment abuse, but the 4-byte clear in the exclusive path can mask the active flag of a live object; TXM is the code-signing root of trust, so a compromised client could only reach this via the trusted call surface.
- **Confidence**: high

## [ringminus1] 0x29784/0x298ec txm_panic_call / txm_panic — panic-path recursion on fault 0x4b
- **Observation**: The panic printer (txm_panic_call) formats "TXM [Panic] ", writes to the console, and then faults with code 0x4b via txm_panic — which formats "(code: 0x%08X)" and re-enters txm_panic_call. The two fault paths are mutually recursive (noreturn), so the intended termination is the secure-channel trap (thunk_FUN_0002d230) reached only for code 0xa0; any other code recurses.
- **Evidence**: `txm_panic_call: ... txm_panic_console(buf); txm_panic(0x4b);` and `txm_panic: if(code==0xa0){...txm_state_trap(...)} txm_panic_msg(" (code: 0x%08X)");`. The panic code is passed as the sole arg to txm_panic but the format string has two conversions, so %u reads an undefined register — the printed code is not guaranteed to match.
- **Severity (hypothesis)**: low — a monitor panic halts/loops by design; the recursion only degrades the already-panicking path and leaks no further privilege. The stale-register %u is a diagnostics fidelity issue, not a security hole.
- **Confidence**: high

## [ringminus1] 0x26e80..0x28c48 slab allocators — no active-bit ownership check before handoff
- **Observation**: The large slab allocators (0x400/0x800/0x1000/0x2000) pop a slot and verify it is still zeroed (fault 0x3d if the +2 word is nonzero) rather than carrying an active/owned bit like the refcount pools. A doubly-freed slab that still contains non-zero payload data in its first 16 bytes trips 0x3d, but a slab whose first 16 bytes happen to be zero is handed out again — a use-after-free window if the free path (txm_slab_free) races.
- **Evidence**: `slot[0]=0; slot[1]=0; if (txm_memcmp(slot+2, &(uint64_t){0}, 8)!=0) txm_panic(0x3d);` in txm_slab_alloc_0x400/0x800/0x1000/0x2000; free zeroes the whole slot via txm_memset.
- **Severity (hypothesis)**: low — the lock-free list pop plus the zero check reduce (not eliminate) double-free reuse; TXM runs in a single trusted execution context so the adversarial surface is limited to monitor-internal faults.
- **Confidence**: high

## [kernel-client] 0xfffffe000c0d83c0..0xfffffe000c0d9be8 SPTM GENTER dispatch ABI — dispatch-id encoding in x16
- **Observation**: The kernel's sptm_* client wrappers are pure GENTER stubs: `pacibsp; stp x29,x30,[sp,#-0x10]!; mov x29,sp; bl _sptm_pre_entry_hook; mov x16,#<endpoint>[; movk x16,#<table>,LSL#32]; genter; bl _sptm_post_exit_hook; mov sp,x29; ldp x29,x30,[sp],#0x10; retab`. The SPTM dispatch id loaded into x16 is `(domain<<48)|(table<<32)|endpoint`. Every XNU-table sptm_* wrapper loads only the endpoint (domain=SPTM_DOMAIN=0, table=SPTM_DISPATCH_TABLE_XNU_BOOTSTRAP=0), and the endpoint values equal `SPTM_FUNCTIONID_*` exactly. The guest id-loaders (endpoints 24-28) are bare `pacibsp; mov x16,#id; genter; retab` with no hooks, feeding the hypervisor EL2 guest-exit path (callers: hv_el2_guest_fault@0xfffffe000b967768, FUN_fffffe000b953e14).
- **Evidence**: 50 stubs disassembled (endpoint ids read from each `mov x16,#N`; spot-verified: 0xe/0x1d/0x25/0x30/0x31/0x2d/0x1b/0x1c); all match sptm_xnu.h SPTM_FUNCTIONID_*. TXM core 0xfffffe000c0d7970 = `movk x16,#0x2,LSL#48` → (TXM_DOMAIN=2)<<48|selector; SK core 0xfffffe000c0d7948 = `movk x16,#0x3,LSL#48`. GENTER opcode 0x00201420 truncates the decompiler at every site.
- **Severity (hypothesis)**: informational — this is the ring -1 entry ABI; it confirms a client can address any of the ~40 XNU-table endpoints plus TXM/SK by selector, but the endpoints are the SDK's own closed set and the SPTM fails closed on invalid selectors (see map_txm_entry.md).
- **Confidence**: high

## [kernel-client] 0xfffffe000b75e8e8 / 0xfffffe000b75e954 SPTM pre/post entry hooks — per-CPU re-entrancy guard
- **Observation**: Every hooked sptm_* wrapper brackets the GENTER with _sptm_pre_entry_hook (increments a per-CPU enter counter at tpidr_el1+0x1c0, then spins on a system-register read for pre-entry sync) and _sptm_post_exit_hook (decrements the counter; on underflow calls hv_el2_preemption_panic). This serializes GENTER entry per CPU and detects preemption-counter corruption. The hooks must preserve x0-x7 (the SPTM arguments) — the pre-hook returns x0/x1 unchanged. The guest id-loaders deliberately skip these hooks.
- **Evidence**: decompile of FUN_fffffe000b75e8e8 (`if (tpidr_el1){*(int*)(+0x1c0)++}; do{}while(UnkSytemRegRead(3,6,0xf,8,0)!=0)`) and FUN_fffffe000b75e954 (`if(*+0x1c0==0) hv_el2_preemption_panic(); --(*+0x1c0); ... daif restore`). All 41 hooked stubs `bl` these two addresses.
- **Severity (hypothesis)**: informational — a healthy guard on the guarded-entry boundary; the pre-entry sysreg spin enforces a serialization contract between the kernel and SPTM.
- **Confidence**: high

## [kernel-client] 0xfffffe000bdbba20 txm_enter — argument/state validation + status mapping at the trusted boundary
- **Observation**: txm_enter is the kernel's TXM dispatcher: it validates the TXM argument count (nargs>7 panics "invalid number of arguments to TXM"), rejects a second thread association per CPU ("attempted multiple TXM thread associations"), pops a per-CPU thread-association freelist entry (waiting on the TXM lock if empty), packs the call args (arg0 = the association selector, args 1..nargs from the sptm_call_regs_t), invokes the TXM genter core, then maps the TXM return. Status 0 is success only when `expected_return_words <= nret_words`; status 7 ("out of memory adding a free page") triggers a retype-and-retry; specific statuses map to kernel error codes (7→6, 8→0x38, 0x29→0x2e, 0x2a→0x31, default 5); the fatal flag (call+24 bit0) turns any error into a panic. Diagnostics print "TXM [Error]: CodeSignature/TrustCache/Errno" with the raw selector and status.
- **Evidence**: full decompile of FUN_fffffe000bdbba20 (~2.5KB): panic strings "invalid number of arguments to TXM: selector: %u | %u @%s:%d", "attempted multiple TXM thread associations", "received excessive/fewer than expected return words from TXM"; printf formats "TXM [Error]: CodeSignature: selector: %u | 0x%02X | 0x%02X | %u\n" (status 4), "Errno" (status 5), "TrustCache" (status 3).
- **Severity (hypothesis)**: low — the non-fatal error paths return a mapped code instead of panicking, so a TXM-initiated error (e.g. a code-signature denial) is surfaced to the caller; only the fatal flag escalates to a panic. The %u-format diagnostics include the raw selector/status, which could disclose endpoint/selector activity to the console, but not to unprivileged callers.
- **Confidence**: high

## [sk-vspace] 0x2587e0 sk_set_walk_and_apply — slot bitmap is the sole mapping-permission authority
- **Observation**: The slot-set walk (FUN_002587e0) iterates every set bit of the vspace slot bitmap at +0x40 (MSB-first via bit-reverse+LZCOUNT) and, for each, invokes either the read-callback (+0x10) or the write-callback (+0x20) of the page/aux buffer tables at param_3 — selected by param_2&1 (FUN_00258b20 = write/clear pass, FUN_00258b2c = read pass). There is no per-slot permission check inside the walk: the bitmap itself is the sole authority on which slots are mapped. A caller that can set a bit in the bitmap for a slot it does not own would get the write callback dispatched on that slot.
- **Evidence**: decompile of FUN_002587e0: `bm = bitmap[word]; do { r=bit_reverse(bm); bm=bm-1&bm; idx=clz(r)|word<<6; if (param_2&1) (**(lVar9+0x20))(dst, page_slot, lVar16); else (**(lVar9+0x10))(dst, page_slot, lVar16); ... sk_buf_copy(); }`; write/clear pass re-fills the bitmap (FUN_001b5474 or `-1L<<`) and resets count when param_2&1.
- **Severity (hypothesis)**: medium — this is the isolation boundary for vspace mapping; the bitmap's integrity is load-bearing, so any earlier bug that flips a bitmap bit (double-free in the slot set, a miscounted insert) escalates directly to a write callback on an unrelated slot. Fails closed only in the sense that the walk requires the bit to already be set.
- **Confidence**: high

## [sk-vspace] 0x25a864/0x25acb8 sk_set_insert_key — open-addressing insert has no owner/permission check, fails closed on duplicate
- **Observation**: The 5-word-key hash-set insert (FUN_0025a864 / FUN_0025acb8) hashes the key, linearly probes the slot bitmap at +0x38, and on a free slot sets the bit and stores the key — with no check that the inserting thread is entitled to reference that key/slot. On a full match it panics (noreturn FUN_0025bddc, duplicate-key message). So the insert both (a) trusts the caller's key as a valid slot reference and (b) converts a duplicate insert into a kernel panic rather than a benign error.
- **Evidence**: decompile of FUN_0025a864: hash via FUN_0008e5d8/FUN_0031993c; probe `if (!(bit & bitmap[idx])) { bitmap[idx]|=bit; copy key; count++; return; } compare stored (FUN_0031996c/FUN_0031997c); if equal sk_set_dup_panic(0x673a80); uVar3++` (linear probe). Same shape in the pair insert FUN_0025ab30 (panic 0x6753a0) and word inserts FUN_0025aa90/0x25aecc (panics 0x674278/0x677880).
- **Severity (hypothesis)**: low — an unprivileged caller cannot reach the kernel-internal slot set directly; the panic-on-duplicate is a fail-closed reaction to a double-insert, which prevents silent corruption but could be converted by a hostile caller into a controlled kernel panic (DoS) if any path lets an attacker induce a duplicate key.
- **Confidence**: high

## [sk-vspace] 0x2557b8 sk_vspace_slot_path_byte — bounds-checked path subscript fails closed
- **Observation**: The slot-path subscript (FUN_002557b8) bounds-checks the requested byte offset against the encoded path length and, on out-of-range access (negative or >= len), raises a Swift UnsafeBufferPointer fatal (noreturn FUN_001afe4c with s_Swift_UnsafeBufferPointer_swift_005cdc10 and line ids 0x75d/0x75e). The companion level classifier (FUN_002552d4/0x2552fc, thresholds 0x80/0x800/0x10000) and assert wrapper FUN_00255324 reject an index whose level is out of range before subscripting.
- **Evidence**: decompile of FUN_002557b8: `if (param_2 < 0) panic(0x75d); if (param_2 < len) return path[param_2]; panic(0x75e);` and FUN_00255324: `if (offset < 0 || level <= offset) { FUN_003488bc(1); noreturn; } else path_byte(index, offset);`.
- **Severity (hypothesis)**: informational — the path/subscript layer validates before use and panics on violation; this is correct defensive behavior at the vspace-name boundary.
- **Confidence**: high

## [sk-vspace] 0x2553b4/0x2554f4 sk_vspace_hash_compress — slot-key hash feeds mapping decisions but has no secret
- **Observation**: The slot path is compressed into a 5-word hash state (FUN_002553b4) and/or appended to a growable Swift string buffer (FUN_002554f4). These hashed slot names are used as lookup keys for vspace object names (FUN_00255738 → FUN_002a200c/FUN_00356164). The compression is a non-keyed SHA-512-style limb mix (carry into bit 56), so the slot-key space is not secret and is fully predictable from a known slot index.
- **Evidence**: FUN_002553b4 constant `+0x100000000000000` (bit-56 carry), 7-limb mix `t0..t4` over state[0..4]; FUN_0025ab30 seeds the same state with the SHA-512-style IV words at DAT_006adf10/18 (0x736f6d6570736575, 0x6c7967656e657261, 0x7465646279746573, 0x646f72616e646f6d).
- **Severity (hypothesis)**: informational — the hash is a lookup optimization, not a MAC; an attacker who can predict slot indices can predict names, but name prediction alone grants no capability without the slot-set insert path being reachable.
- **Confidence**: medium

## [sk-vspace] 0026a328/0026a9a8 sk_table_lookup(_c) — open-addressing vspace entry table
- **Observation**: vspace entries are held in an open-addressing hash table keyed by a 64-bit hash (table at +0x30, bitmap at +0x38, slot shift byte at +0x20, seed at +0x28). Lookup walks from `hash & mask`; on a free slot it INSERTs the key (FUN_0025c33c/0025c9a8) rather than reporting a miss, and returns `bit==0` (true=inserted). The table is guarded by a sentinel write `*tbl = -0x8000000000000000` around the insert (a re-entrancy/transaction marker on the table's owner pointer).
- **Evidence**: `uVar2 = uVar2 & ~(-1L << (*(byte*)(tbl+0x20)&0x3f)); uVar1 = 1L << (uVar2&0x3f) & *(ulong*)(tbl+0x38+(uVar2>>6)*8);` then on miss `*unaff_x20 = -0x8000000000000000; FUN_0025c33c(key, uVar2, FUN_003a261c(tbl)); *unaff_x20 = tbl;`. This lookup-insert pattern appears identically in 0026a328 and 0026a9a8 (8-byte slots) and 0026a744 (0x28-byte keyed entries).
- **Severity (hypothesis)**: informational — lookup-insert is a benign data-structure choice; the security-relevant fact is that an out-of-range/hostile slot key would be silently INSERTED into the vspace entry table (unbounded growth / DoS), and the sentinel write is a single global, so a nested/re-entrant table op on the same table would see `*tbl==-0x8000...` and mis-dereference. Worth confirming the table is per-vspace and locked.
- **Confidence**: medium

## [sk-vspace] 0026a404/0026a560/0026adcc/0026af9c sk_table_put/get — tagged entry identity compare
- **Observation**: The 2-word and 0x28-byte entry put/get paths compare entry identity using the Swift tagged-value bits (0x6000000000000000 = tag class, >>0x3c/0x3d flags, &0xffffffffffff = 48-bit object). A match releases and returns the existing entry; the identity compare includes a fallback path (FUN_002a0d50) when either side lacks the 0x60... tag, meaning entries whose tag bits are not canonicalized are compared loosely.
- **Evidence**: `if (((uVar5 ^ 0xffffffffffffffff) & 0x6000000000000000) != 0 || (param_3 & 0x6000000000000000) != 0x6000000000000000) { FUN_00351584(); uVar5 = FUN_002a0d50(); if ((uVar5&1)!=0) goto match; }` — the loose path is taken whenever the stored value lacks the 0x60 tag-class.
- **Severity (hypothesis)**: low — a non-canonical (e.g. forged) entry value bypasses the strict tag compare and relies on FUN_002a0d50's fallback; if that fallback is weak a hostile entry could collide with a legitimate key. Requires the vspace table to be writable by an untrusted capability holder.
- **Confidence**: medium

## [sk-vspace] 00267510 sk_vspace_region_check — region range/permission check with fail-closed traps
- **Observation**: Region permission checks compare the request's page-granular range against the tagged bounds and validate each candidate entry (0xa0d sentinel / 0x8080 class bits) before committing via thunk_FUN_002a2698. Any range mismatch or nil entry hits the noreturn "Fatal error"/"Range requires lowerBound < upperBound" trap (FUN_001afe4c) rather than clamping.
- **Evidence**: `if (uVar6 + 1 != auVar8._8_8_) { if (auVar8._0_8_ == 0) { FUN_00347f2c(); FUN_001afe4c(); } uVar1 = *(ushort*)(auVar8._0_8_ + uVar6); if (uVar1 == 0xa0d || (uVar1 & 0x8080)) ... }` — fail-closed on nil and sentinel.
- **Severity (hypothesis)**: informational — fail-closed permission checks (DoS on malformed region, but no bypass). This is the vspace mapping permission boundary; the bounds logic is worth auditing for an off-by-one at the `(uVar4 + (uVar3>>0x10)) < uVar6` comparison.
- **Confidence**: low

## [sk-vspace] 0026bd30/0026bd5c sk_vspace_bounds_check(_pages) — Swift.Range bounds panic
- **Observation**: The vspace layer guards against out-of-range index/page-range math with Swift-style fatal-error traps: `sk_vspace_bounds_check` panics if `a > b` (FUN_00347de8(1) + fatal), and the page-granular variant compares `a>>0xe` vs `b>>0xe` (16 KiB granule) before trapping "Range requires lowerBound < upperBound" / "Index out of range" (s_Range_requires_lowerBound_005cda00, s_Index_out_of_range_005cd940).
- **Evidence**: `if (param_1 > param_2) { FUN_00347de8(1); FUN_001afe4c(); }` and `if (param_1>>0xe <= param_2>>0xe) return; FUN_001afe4c(s_Fatal_error_005accd0,0xb,2,s_Range_requires_lowerBound_<__upp_005cda00,0x27,2,s_Swift_Range_swift_005cda30,0x11,2,0xb5,1);`.
- **Severity (hypothesis)**: informational — these traps convert malformed range inputs into a deterministic panic (availability), preventing out-of-bounds page walks. The 16 KiB granule (>>0xe) matches cL4 page size; a unit error here would be a correctness/security bug, but no off-by-one observed.
- **Confidence**: medium

## [sk-vspace] 0026b748 sk_vspace_walk_entries — callback fold with global callback slot
- **Observation**: The entry-list walk folds every node into a {value,tag} accumulator and finally calls a GLOBAL walk callback pointer `_DAT_006ade70` with the accumulated pair. If `_DAT_006ade70 == 0` the walk falls straight to the indirect jump-table dispatch (UNRECOVERED_JUMPTABLE) — i.e. a NULL global callback is treated as a fast-path direct dispatch rather than an error.
- **Evidence**: `pcVar1 = _DAT_006ade70; if (_DAT_006ade70 == (code*)0x0) { FUN_0034ca28(); FUN_00354458(); (*UNRECOVERED_JUMPTABLE)(); return; }` — the NULL-callback branch jumps through an unrecovered jumptable.
- **Severity (hypothesis)**: low — a NULL/forged global callback pointer would be dispatched through an indirect jump table; if the jumptable entry is attacker-influenced this is a control-flow concern. The callback pointer must be write-protected (set once at vspace init). Worth confirming `_DAT_006ade70` is not writable from a capability.
- **Confidence**: low

## [sk-vspace] 0026c6d8 sk_vspace_obj_check — object-validity gate with error-code panic
- **Observation**: Object validation for vspace ops performs a two-stage runtime check; failures panic with a fixed error code (0xf6 on first-stage failure, 0xf7 on second), and the success path re-locks and forwards with code 0x101. No silent pass — every invalid object hard-stops.
- **Evidence**: `if ((r&1)==0) { FUN_0034b348(); u=0xf6; } else { ... if ((r&1)!=0) { ... FUN_0035130c(u,0x101); return; } FUN_0034b348(); u=0xf7; } FUN_003486b8(u); FUN_00349410(); FUN_003504b8(); FUN_001afe4c();`.
- **Severity (hypothesis)**: informational — fail-closed object gate (DoS on invalid object reference, no bypass observed). The 0xf6/0xf7 codes index a panic table; a null/forged object is rejected before any capability operation.
- **Confidence**: medium

## [ringminus1] 0x101f4c sk_region_find_insert / 0x102464 sk_alloc_pages (PMM region allocator)
- **Observation**: The cL4 PMM region allocator maintains a sorted free-list of physical regions (0x28-byte entries with base/end). Region search/insert validates every index and size against the list bounds with hard BRKs (0x1021c0..0x1021d4), and page allocation bounds-checks the page count (>>0x32) and rejects non-16KiB-aligned requests. A "Fatal error"/"PMMInstance.allocUntypedForType" panic path handles exhaustion. No unchecked arithmetic was observed.
- **Evidence**: FUN_00101f4c: `if (CARRY8(uVar16,param_3)) SoftwareBreakpoint(1,0x1021c0)`; FUN_00102464: `if (param_1>>0x32 != 0) SoftwareBreakpoint(1,0x1025b0)`; `param_1*0x4000`; panic strings s_Fatal_error_005accd0 / "PMMInstance does not free resource".
- **Severity (hypothesis)**: informational — the physical-memory allocator is the substrate for every guest page; its bounds checks are fail-closed. No weakness observed; errors here would corrupt the guest-physical map.
- **Confidence**: medium

## [ringminus1] 0x103cb0 sk_prng_ensure / 0x103b2c sk_prng_construct (corecrypto PRNG)
- **Observation**: The kernel PRNG is constructed from a seed drawn via thunk_FUN_0005c278 (an SVC/GL0 request) of 0x30 bytes, validated to be >= 0x30, then built with corecrypto DRBG ("corecrypto_exclavecore_rng" label). The seed buffer is cleared (FUN_00104f9c) after construction, and the PRNG is single-initialization (global ready flag DAT_006bf580). Seeding requires a caller-provided length >= 0x30, else the "Security assertion"/panic path is taken.
- **Evidence**: FUN_00103cb0: `uVar1=thunk_FUN_0005c278(&buf,0x30); if (uVar1<0x30) FUN_004b853c(); FUN_00103b2c(uVar1,&buf); FUN_00104f9c(0x30,&buf)`; FUN_00103b2c uses s_corecrypto_exclavecore_prng_005c6d63 and s_corecrypto_exclavecore_rng_005c6d8d; g_prng_ready DAT_006bf580.
- **Severity (hypothesis)**: medium — the RNG seed comes from GL0/SPTM (the "thunk_FUN_0005c278" supervisor request). If that source is weak or interceptable, all exclave key material derived from this PRNG is at risk. The length gate (>=0x30) and single-init protect against re-seeding, but the trust root is external.
- **Confidence**: medium

## [ringminus1] 0x104f78 sk_dit_save / 0x104f90 sk_dit_restore (data-independent timing)
- **Observation**: The crypto/hash layer wraps sensitive operations with DIT (Data-Independent Timing) enable + speculation barrier and restores the prior DIT state. Combined with the constant-time full-scan compares (0x104180, 0x1146d8), this is defense against timing side channels on hashes/compares.
- **Evidence**: FUN_00104f78 reads SCTLR DIT (reg 3,3,4,2,5), sets `dit=1`, `SpeculationBarrier()`, returns prev; FUN_00104848/00104fb4/00105054 call FUN_00104f78 before the wrapped crypto call and FUN_00105168 after.
- **Severity (hypothesis)**: informational — good practice; DIT + constant-time compare mitigate timing leakage on secret-dependent branches.
- **Confidence**: high

## [ringminus1] 0x104043f0 sk_hash_block_pad / 0x10403c sk_hash_absorb (hash message handling)
- **Observation**: Hash absorb and block-pad use XOR with fixed 0x5c/0x6a constants (HMAC inner/outer padding) and invoke the compression callback through a function-pointer field (param_1[6]/[7]/[0x30]). The buffer growth and length accounting are bounds-checked (CARRY8 checks -> BRK). Message lengths are tracked in bits (*buf += consumed*8).
- **Evidence**: FUN_001043f0: `*(byte*)(...)=*param_4^0x5c`, `...^0x6a`; FUN_0010403c: `(**(code**)(param_1+0x30))(buf,n,src)`; `*param_2 += uVar6*8`.
- **Severity (hypothesis)**: informational — HMAC-style construction with callback dispatch; the fixed pad constants and length accounting are standard and correct.
- **Confidence**: medium

## [ringminus1] 0x1120c4 sk_hash64_wyhash (wyhash-derived 64-bit hash)
- **Observation**: The kernel uses a wyhash-style 64-bit string hash (seed 0x9ae16a3b2f90404f, primes 0x622015f714c7d297/0x651e95c4d06fbfb1/0x4b6d499041670d8d/0x3c5a37a36834ced9) to index load-commands and capability tables. wyhash is not a cryptographic hash — it is a fast non-crypto hash. If it is used to key or authenticate any security-relevant structure (as opposed to merely bucketing), collisions could be induced.
- **Evidence**: FUN_001120c4 full-body prime-multiply mixing; `if (param_3==0) return 0x9ae16a3b2f90404f`.
- **Severity (hypothesis)**: low — wyhash is explicitly non-cryptographic; used for table bucketing (load-command/capability lookup) it is fine, but must not be relied on for MAC/authenticity. Worth confirming no security claim depends on it.
- **Confidence**: high (algorithm identity: constants match wyhash)

## [ringminus1] 0x10c2b0 sk_cap_id_map / 0x10c378 sk_cap_id_eq (capability-id mapping)
- **Observation**: Capability-id words are mapped/compared through a fixed table (0x80000028->0x100000002, 2->0x100000006, etc.) and a 40-bit comparison that treats the 0x100000000.. range specially. This is the cL4 capability-tag normalization used when repacking Mach-O load commands into the guest capability space. The repack helpers (0x10d21c..0x10d294) set specific high tag bits (0x20..0xc0 shifted).
- **Evidence**: FUN_0010c2b0 switch table; FUN_0010c378 `(a & 0xff00000000)==0x100000000` branch; the repack family `*p = *p & 0x1ffffffff | <tag>`.
- **Severity (hypothesis)**: informational — capability-id canonicalization; the mapping is fixed and deterministic. If the tag bits were attacker-influenced during load-command processing, a capability could be forged, but the repack masks to 33 bits and only sets kernel-chosen tag bits.
- **Confidence**: medium

## [sk-vspace] 0x249a64 / 0x24a648 sk_vspace_perm_check_a / sk_vspace_perm_check_b — owner-mask isolation gate on the vspace map path
- **Observation**: The per-CPU vspace map entry point checks two ownership fields of the current operation object before touching page-table state: the per-CPU id masked against `*(obj+0x50) & 0xff` (owner set) and the liveness flag at `*(obj+0x48)`. Only when the current CPU id is in the owner mask AND the object is live does the code recurse into the map dispatch (FUN_0024963c); any other combination falls into a fixed deny sequence (`FUN_00350410; FUN_003488bc; FUN_00349644; FUN_0034fbe4`) that ends in a noreturn Swift fatal trap (FUN_001afe4c). A second owner check is applied to the target at `*( *(x-8)+0x50 ) & 0xff` before the recursion commits.
- **Evidence**: FUN_00249a64: `if ((*(uint*)(obj+0x50) & cpu & 0xff) == 0) { if (*(long*)(obj+0x48) != 0) { ... if ((*(uint*)(*(long*)(x-8)+0x50) & cpu & 0xff)!=0) goto deny; if (*(long*)(*(long*)(x-8)+0x48)!=0) { FUN_0035aa9c(); FUN_0024963c(); ... return; } } FUN_00350410(); FUN_00348074(); FUN_00351be0(); } else { deny: FUN_00350410(); FUN_003488bc(); FUN_00349644(); FUN_0034fbe4(); } FUN_001afe4c();`. The +0x50 owner mask is a single byte (&0xff), i.e. at most 8 CPUs can co-own a vspace context.
- **Severity (hypothesis)**: low-medium — this is the isolation boundary between vspace contexts. A context whose owner byte is corrupt/absent is denied rather than mapped, so the risk is availability (an over-restrictive gate) rather than privilege escalation, provided the owner byte is only writable by the kernel. The 8-bit owner mask caps co-ownership at 8 CPUs.
- **Confidence**: medium

## [sk-vspace] 0x24c2ec sk_vspace_ctx_perm_mod — permission-change path checks the owner mask then panics on non-divisible size mismatch
- **Observation**: The region permission-modify path runs the change helper (FUN_0034b7e4 + FUN_0034c8e0), then checks the owner mask at `*( *(x-8)+0x50 )`. On a mismatch it calls the region handler only when the two objects' sizes divide cleanly (one divides the other); otherwise it enters the same deny+panic sequence (`FUN_00348b7c; FUN_0034a368; FUN_00352e0c` then FUN_001afe4c). The GCD-style remainder computation (`q = o1/o2; o1 = o1 - q*o2`) means the permission change is refused unless one region size is an exact multiple of the other.
- **Evidence**: FUN_0024c2ec: `lVar3=*(*(x-8)+0x48); lVar2=*(*(x-8)+0x48); if (lVar2<lVar3){ if(lVar2!=0){lVar1 = (lVar3!=0)?lVar3/lVar2:0; lVar3-=lVar1*lVar2;} if(lVar3==0){ (*param_3)(param_5); ... return;} goto deny;} ...` with deny ending in `FUN_001afe4c()`.
- **Severity (hypothesis)**: low — permission changes are size-divisibility constrained and owner-gated; the panic path fails closed rather than partially applying the change.
- **Confidence**: medium

## [sk-vspace] 0x24ad48 sk_vspace_region_compare — descriptor kind/owner equality gate for region matching
- **Observation**: Region equality is decided by the top-3-bit kind word and the base word for the canonical kinds, and for the leaf/block kinds additionally requires the payload words (indices 0,2,5,6) to be all-zero in the resolved region (the canonical "empty" 0xa000000000000000 / single-page pseudo-descriptors). A region is only considered equal to another if their kinds and bases match exactly and, for the mapped kinds, the range sub-system agrees. Non-matching regions return 0 (no merge) rather than partially merging.
- **Evidence**: FUN_0024ad48: `case 5: if (kind==0xa000000000000000 && w3==0&&w4==0&&base==0&&w5==0&&w6==0&&a[2]==0){ FUN_00357dc4(); ... if(res[5]||res[6]||res[0]||res[2]) return 0; return 1;}` — the 16-byte OR-reduction over the payload is equivalent to "words 5 and 6 are zero".
- **Severity (hypothesis)**: informational — equality is conservative; a corrupt extra payload word prevents a match (fail-closed).
- **Confidence**: medium

## [sk-vspace] 0x20e778..0x20ef0 sk_vspace_trap_restore — trap handlers dispatch through a PAC'd global hook under a per-CPU lock
- **Observation**: The opening block of the vspace trap handlers (sk_vspace_trap_restore, sk_vspace_trap_restore2, sk_vspace_dispatch_eabc, sk_vspace_dispatch_ebf0, sk_vspace_dispatch_eefc) each: grab per-CPU state (FUN_0008e518), run a long shared-runtime bookkeeping chain, acquire the kernel lock (FUN_00377824), run more helpers, release via FUN_00377bec, and finally make one or more indirect calls through the global hook slot `(*DAT_00658c00)()` before tail-dispatched into the restore routine FUN_0020e5c0 and returning via FUN_0008e500. The hook slot is a single PAC-authenticated function pointer at 0x00658c00; all these handlers route through it, so a corruption/replacement of that slot (were it writable) would hijack every vspace trap.
- **Evidence**: every body begins `sk_cpu() /*FUN_0008e518*/; rt_352914(); sk_tcb_get() /*FUN_0007c0c4*/; ...; (*DAT_00658c00)(); ... sk_lock_acquire() /*FUN_00377824*/; ... sk_lock_ref() /*FUN_00377bec*/; ... sk_vspace_dispatch_e5c0(0) /*FUN_0020e5c0*/; sk_cpu_current() /*FUN_0008e500*/`. The `(*DAT_00658c00)()` call appears multiple times in sk_vspace_dispatch_eefc (including two calls passing `*(x8+0x40)`).
- **Severity (hypothesis)**: low — the PAC'd hook slot is the single indirect-dispatch choke point of the whole vspace trap layer; if it were ever attacker-writable the isolation boundary collapses. It is expected to be read-only kernel memory.
- **Confidence**: medium (call-site structure is high; the writability of 0x00658c00 is not verified here).

## [sk-vspace] 0x20ebf0 / 0x211358 sk_vspace_dispatch_ebf0/_11358 — branch takes noreturn Swift fatal on the "flag set" path
- **Observation**: sk_vspace_dispatch_ebf0 (and its mirror sk_vspace_dispatch_11358) test a flag produced by FUN_0034f044 (carried in the Z flag). When the flag is NOT set it returns through a vtable slot at +0x20 (normal path). When the flag IS set it runs a further bookkeeping chain and falls into the noreturn Swift fatal trap FUN_001afa84. So the "true" branch is fail-closed panic, the "false" branch is the return path.
- **Evidence**: `uVar3 = FUN_0034f044(); if (!(bool)in_ZR) { FUN_0034f384(); (**(code**)(extraout_x16_00 + 0x20))(...); FUN_0008e500(); return; } FUN_00352e18(...); ... FUN_00349c58(); FUN_001afa84();` — the false-branch returns, the true-branch reaches the noreturn FUN_001afa84.
- **Severity (hypothesis)**: informational — a flag-dependent fail-closed panic; availability only.
- **Confidence**: medium (in_ZR semantics inferred from branch polarity).

## [sk-vspace] 0x20eefc / 0x21166c sk_vspace_dispatch_eefc — two nested Swift existential calls then a result-flag branch to panic
- **Observation**: The largest handler makes two `FUN_00351c1c(..., s_Swift_ExistentialCollection_swif_005cf680)` calls (Swift runtime existentials) between two recursive dispatches to sk_vspace_dispatch_ebf0, then branches on the low bit of an indirect call result: bit-0 set runs the long teardown tail and returns; bit-0 clear falls to the noreturn panic FUN_001afe4c. So a failed existential/collection operation is fail-closed.
- **Evidence**: `rt_351c1c(0,0,/*Swift exist*/0); sk_vspace_dispatch_ebf0(); rt_35a420(); rt_351c1c(0,0,0); sk_vspace_dispatch_ebf0(); if ((*(unsigned long(**)())0)() & 1) { ...teardown...; return; } rt_34b348(); rt_35a4d4(); rt_347ef4(); sk_panic_no_return2();` and the mirror in sk_vspace_trap_1166c with FUN_00211358 recursion.
- **Severity (hypothesis)**: informational — fail-closed on the existential dispatch result; availability only.
- **Confidence**: medium.

## [sk-vspace] 0x212d50 sk_vspace_obj_dtor_12d50 — vtable method at +0x20 invoked only when the object is non-null
- **Observation**: The object teardown stubs (sk_vspace_obj_dtor_12d50 and the 0x212c84..0x214720 family) resolve the vtable from the object (in_x5-8), run the hook, and only invoke the vtable method at +0x20 when the object register (unaff_x21) is non-null. The decompiler lost the `this` register to PAC, so the vtable base is modeled as 0 in the transcribed body — a faithful placeholder; the conditional dispatch on object!=0 is the observable guard.
- **Evidence**: `void *vt = *(void **)(in_x5-8); (*DAT_00658c00)(); if (unaff_x21 != 0) { FUN_0036993c(...); (**(code**)(vt + 0x20))(...); }`.
- **Severity (hypothesis)**: informational — a null-object guard before indirect vtable dispatch (defensive); note the PAC-lost `this` means the call target is a reconstruction placeholder, so this body is a call-sequence-level transcript, not a precise target.
- **Confidence**: low (PAC-lost self register).

## [sk-vspace] 0x213c58 / 0x213cd0 / 0x21401c/0x214094 / 0x2145e8/0x214660 sk_vspace_obj_alloc_* — object constructor pairs alloc + init + vtable-method fill
- **Observation**: Three identical object-constructor pairs allocate a 0x28-byte object (tags 0x1d1c/0xf7b7/0x843d), then the init routine sets obj[0]=vtable-derived value, obj[1]=vtable(param-8), allocates a sub-node sized from vtable+0x40 (tags 0xe087/0x894b/0x7ec4), and calls the vtable method at +0xe8 to fill the node. The size of the sub-allocation is taken from `vtable+0x40` — a runtime field — so a corrupted vtable size field would drive the allocation size.
- **Evidence**: FUN_00213c58: `lVar1=FUN_0036a908(0x28,0x1d1c); *param_1=lVar1; uVar2=FUN_00213cd0(...); *(lVar1+0x20)=uVar2; return &DAT_003471a4;` and FUN_00213cd0: `*param_1=param_5; lVar1=*(param_5-8); param_1[1]=lVar1; lVar1=FUN_0036a908(*(lVar1+0x40),0xe087); param_1[2]=lVar1; (**(code**)(*param_4+0xe8))(lVar1,...);` (same shape for the 0xf7b7/0x843d twins).
- **Severity (hypothesis)**: low — the sub-node size is read from the vtable (+0x40) at runtime; if the vtable were attacker-controlled, the allocation size (and thus a potential over/under-allocation) is attacker-influenced. Assumed kernel-writable-only vtable.
- **Confidence**: medium.

## [sk-vspace] 0x25c33c / 0x25c9a8 / 0x25cc54 sk_set_insert_keyed / sk_set_insert_keyed16 / sk_set_insert_40 — open-addressing duplicate detection is a hard panic
- **Observation**: The vspace page-table/capability set inserts use open addressing: the probe (`sk_set_hash` on the set seed) walks the occupancy bitmap linearly, and encountering an element whose stored value equals the incoming key raises the noreturn duplicate panic (FUN_0025bddc, "Duplicate elements of type...") instead of replacing or deduplicating. The panic is gated on the exact stored-element equality at `*( *(set+0x30) + slot*8 ) == key` (8/16-byte) or the 40-byte compare via FUN_0031997c.
- **Evidence**: FUN_0025c33c: `while (slot = slot & ~(-1<<log2), (bitmap[slot>>6]>>(slot&0x3f)&1)!=0) { if (*(*(set+0x30)+slot*8)==key) FUN_0025bddc(0x674278); slot++; }`; FUN_0025c9a8 same with 0x677880; FUN_0025cc54 (40-byte) sets a found flag and swaps rather than always panicking. The insert then commits via FUN_0025c280 (set bit + store + count++) with an overflow trap.
- **Severity (hypothesis)**: informational/low — the duplicate-insert path fails closed (panic) which is safe but availability-hostile; a buggy or concurrent double-map of the same key halts the kernel. Open addressing means a full/overloaded table degrades to a linear scan (DoS potential if the load factor is not bounded).
- **Confidence**: high (explicit duplicate string + exact bitmap/compare logic)

## [sk-vspace] 0x25db98 / 0x25dd80 / 0x25dee4 / 0x25e000 sk_set_remove_* — open-addressing remove rehashes the probe chain then clears the bit
- **Observation**: Element removal performs the classic open-addressing backshift: it walks the removed slot's probe chain, re-hashes each following element (FUN_0022b080 find + sk_swift_string_hash), and moves it into the freed slot only when it belongs to that cluster; then clears the bitmap bit and decrements count (+0x10) with a borrow trap, bumping the generation (+0x24). 8/16/40-byte strides all follow this pattern.
- **Evidence**: FUN_0025db98: `uVar8=~size; lVar6=FUN_0022b080(slot, word_base, uVar8); uVar11=lVar6+1&uVar8; do { rehash elem; if (in-range) move elem; slot0=slot0+1&uVar8; } while (bitmap bit set); *(word_base+(slot>>3&mask)) &= ~(1<<(slot&0x3f)); if (SBORROW8(count,1)) SoftwareBreakpoint; count--; *(set+0x24)++;`
- **Severity (hypothesis)**: informational — removal preserves the probe-chain invariant; if the rehash-move predicate were wrong, lookups for displaced elements would break (availability/correctness), but the logic faithfully re-establishes the invariant.
- **Confidence**: medium

## [sk-vspace] 0x25e370 sk_set_alloc — set object layout fixed: bitmap immediately precedes element array, capacity = 1<<log2
- **Observation**: The core set allocator lays out the object so that the occupancy bitmap (+0x38) is immediately followed by the element array (+0x30 = base+0x38 + nwords), and the initial bitmap is either `~0 << (nbits&0x3f)` (single-word) or zeroed via FUN_001b5474. The hash seed (+0x24) may be the default 0x100000000 sentinel, and the element seed (+0x28) selects the actual hash function. The +0x20 log2 byte controls both capacity and the probe mask (`~(-1<<log2)`).
- **Evidence**: `plVar1=(long*)(base+0x38); *(base+0x10)=0; *(base+0x18)=capacity; *(base+0x20)=log2; *(base+0x30)=plVar1+nwords; if (nbits<0x40) *plVar1=-1L<<(nbits&0x3f); else FUN_001b5474(0,nwords,plVar1);`
- **Severity (hypothesis)**: informational — the bitmap/elements adjacency and capacity bound the table's worst-case behavior; a corrupted log2 could make the probe mask span more than the allocated bitmap (out-of-bounds bitmap access on insert/remove). Kernel-only writable fields.
- **Confidence**: high

## [sk-vspace] 0x262e9c / 0x263140 / 0x263360 sk_string_utf8_decode / sk_string_scalar / sk_string_scalar2 — UTF-8 decoder rejects over-long/malformed encodings by width
- **Observation**: The Swift UTF-8 scalar decoder inspects the leading byte's leading-one count (LZCOUNT) to select 1-4 byte decoding, and the grapheme/scalar readers treat a scalar >0xbf as needing the multi-byte path; over-long encodings and the Korean jamo/Hangul ranges are composed via sk_hangul_compose (FUN_002641f8) or decomposed via FUN_00264558/FUN_002646a0. Buffer growth (FUN_001a0908) bounds the grapheme array; out-of-buffer iteration traps via FUN_001afe4c.
- **Evidence**: FUN_00262e9c: `switch(LZCOUNT(byte<<0x18 ^ 0xffffffff)) { case 2/3/4: decode continuation bytes; }`; scalar readers guard `if (0xbf < scalar) { multi-byte }` and hangul `if ((scalar-0xac00>>2)<0xae9) FUN_00264558(); else FUN_002646a0();`. FUN_00264068 (emit) traps `FUN_00348304(); FUN_001afe4c();` on an overrun.
- **Severity (hypothesis)**: informational/low — the string machinery is fail-closed (overruns panic); a malformed kernel-supplied path/name string would halt rather than corrupt, so the risk is availability only.
- **Confidence**: medium

## [sk-vspace] 0x208a90-0x209090 sk_vspace_abstract_vtable — Swift base-class "method must be overridden" abstract vtable on the vspace object-model boundary
- **Observation**: A contiguous run of 32-byte abstract-method stubs (0x208a90..0x209090, indices 0xd3..0x209) each load Swift type metadata then call FUN_002085a4, which raises the kernel-wide "Method must be overridden" fatal error (s_Method_must_be_overridden_005cf660) and hard-stops (FUN_001afa84, noreturn). This is the abstract virtual-method table of the vspace/page-table object base class: every concrete vspace-object subclass MUST override these slots. Calling an un-overridden slot is a fatal, not a fall-through.
- **Evidence**: Disassembly per slot: `stp x29,x30; mov x29,sp; mov x3,x30; bl 0x00357cc8; mov x30,x3; mov w3,#<idx>; bl 0x002085a4; pacibsp` with distinct index per slot (0x208a90=0xd3 ... 0x209090=0x209). FUN_002085a4 decompiles to `FUN_0035ac70(s_Method_must_be_overridden_005cf660); FUN_0006f768(s_Fatal_error_005accd0); FUN_001afa84(); /* noreturn */`.
- **Severity (hypothesis)**: informational — the object model is fail-closed by construction: an abstract (un-implemented) vspace method can never be silently reached, so a mis-typed/mis-classed vspace object triggers a hard kernel trap rather than a partial or default operation. This is defensive, but note the whole vspace permission-checking body lives in the concrete subclasses + out-of-range Swift runtime (0x0034xxxx), so the isolation logic itself is not in this address run.
- **Confidence**: high (string + structure match)

## [sk-vspace] 0x208bd0/0x208e38/0x208e60 sk_vspace_pair_accessors — pair-field Swift retain/weak accessors on the vspace object
- **Observation**: These small accessors load two 64-bit fields of the object (`[self+0x10]`,`[self+0x20]`) and run them through Swift runtime retain/unowned helpers (FUN_0036b118 = Swift retain, FUN_0036b270 = Swift weak/unowned load with refcount check). They are the standard Swift `swift_retain`/`swift_weakLoad` shims emitted for the class's stored properties, i.e. the vspace object carries two Swift reference-counted property slots.
- **Evidence**: FUN_00208e38/208e60: `ldp x0,x19,[x20,#0x10]; bl 0x0036b270; mov x1,x19; retab`; FUN_00208bd0: two `ldr x0,[x20,#0x10/0x20]; bl 0x0036b118`. FUN_0036b270 includes the `if (lVar4<0) return` refcount/liveness bail and a `-1` sentinel check.
- **Severity (hypothesis)**: informational — standard Swift refcounting on the vspace object; the weak-load sentinel (`==-1`) is a classic retained/released object marker. If the strong/weak balance were corruptible from a lower level the refcount underflow could be attacked, but the accessors themselves are canonical and safe.
- **Confidence**: high

## [sk-ipc] 00387fbc cL4_cap_authorize
- **Observation**: The cL4 capability-authorization core (IPC message-register / cap descriptor path) is fail-closed: any descriptor tag/kind/length mismatch returns 0 (deny) and aborts the whole chain walk — there is no partial-grant path. The authorization binds the requesting cap word (param_1) to the descriptor's expanded form (built by 00387e60/00387da0), requires cap equality via a dedicated compare (thunk_FUN_001145b0), and enforces the 't' (transferable) name-exclusion rules for tag 0xf6 records.
- **Evidence**: All mismatch branches converge on `LAB_0038859c` (returns 0 / canary-guarded, `FUN_0011d7e8` stack-fail on corruption); per-tag checks (0xf4/0xf5/0xc0/0xbf/0xa3/0x49/0x67/0xd9/0xb1/0xf6/0xe7/0x19/0x3f) each `goto LAB_0038859c` on mismatch; equality via `thunk_FUN_001145b0` and the 0x2b0-byte expanded descriptor; `*(param_2+0x12)` length byte gates multi-record chains.
- **Severity (hypothesis)**: medium — this is the capability authorization gate for IPC/cap transfers; a bypass would grant a cap without matching ownership. All observed checks are hard-deny (no soft-fail), so no bypass observed.
- **Confidence**: medium

## [sk-ipc] 003876c4 cL4_cap_type_validate
- **Observation**: The capability type validator gates IPC object operations behind a per-owner gate (FUN_0036f460) and a fail-closed kind switch: the descriptor tag (0x203/0x301 and the 0x7ff range) selects which cap word (param_1[1] vs [5]) is checked, and a kind 2/3 mismatch routes to a noreturn SoftwareBreakpoint trap rather than a graceful deny — an unexpected kind in this path halts the kernel.
- **Evidence**: `if ((uVar4 & 1) != 0) return false`; kind checks `if (lVar5 != 0x203) { if (lVar5 != 0x301) return false; }`; `uVar1 = *puVar6 >> 0x10 & 3; if (uVar1 < 2) return uVar1 != 0; if (uVar1 != 2) SoftwareBreakpoint(1,0x387868)`.
- **Severity (hypothesis)**: low — fail-closed type gating; the SoftwareBreakpoint on unexpected kind is an availability concern only.
- **Confidence**: medium

## [sk-vspace] 0x254e80 / 0x254ed4 sk_swift_xor_string — obfuscated string literal
- **Observation**: Two helper functions read a byte string (s_uespemosmodnarodarenegylsetybdet_004e7a30 — an obfuscated/reversed Swift constant) and XOR each byte against a key byte obtained at runtime before feeding it to the string builder. This is string obfuscation inside the kernel image; the same key-byte pattern is not present in the surrounding runtime helpers.
- **Evidence**: `bVar1 = rt_00348c48(); rt_0034ec48(bVar1, &DAT_004e7a30+0x10, bVar1 ^ *(unsigned char*)&DAT_004e7a30)`; second variant reads the word from the context (`*unaff_x20`) and forwards through FUN_001a84f4 / FUN_0022995c.
- **Severity (hypothesis)**: informational — obfuscation/anti-tamper of a constant; the plaintext is recoverable with the single-byte key in the same function.
- **Confidence**: medium

## [sk-vspace] 0x254fb4 sk_swift_utf16_encode — surrogate split with trap
- **Observation**: UTF-16 surrogate encoding for supplementary-plane scalars returns a packed high/low surrogate pair and takes a noreturn SoftwareBreakpoint (0x254ffc) when the encoded value does not fit a code unit; the BMP single-code-unit path asserts (fatal) if the value exceeds 16 bits. The kernel traps rather than silently truncating a non-representable scalar.
- **Evidence**: `if (param_1==1) { if (uVar2>>0x10 != 0) return uVar2&0x3ff|0xffffdc00; rt_0035047c(); rt_003486b8(0x5b); ... fatal }`; supplementary path computes `(uVar2+0x3ff0000>>10 & 0xffff)+0xd800` then `SoftwareBreakpoint(1,0x254ffc)` if it overflows 16 bits.
- **Severity (hypothesis)**: informational — fail-closed encoding; a malformed scalar halts rather than producing a corrupt code unit.
- **Confidence**: high

## [sk-vspace] 0x252e24 / 0x252818 / 0x252a64 sk_swift_buffer_scalar / string advance — bounds-trapping slice/advance
- **Observation**: The Swift UnsafeBufferPointer scalar decoder and string position-advance helpers hard-trap (noreturn fatal, s_Fatal_error_005accd0 with Swift_Range / Swift_UnsafeBufferPointer / Index_out_of_range strings) on any out-of-range index, nil optional unwrap, or invalid slice rather than returning a partial result. The kernel's embedded Swift runtime is fail-closed on collection bounds.
- **Evidence**: `FUN_001afe4c(s_Fatal_error_005accd0,0xb,2,s_unsafelyUnwrapped_of_nil_optiona_005ce1c0,0x21,2,s_Swift_Optional_swift_005ce1f0,0x14,2,0x179,1)` and `s_Invalid_slice_005cfa58` / `s_Swift_UnsafeBufferPointer_swift_005cdc10` / `s_Index_out_of_range_005cd940` fatal paths; `(lVar12<0) || (end<upper)` checks gate the copy loop.
- **Severity (hypothesis)**: informational — bounds violations are converted to deterministic kernel fatals (availability); no partial-write path observed.
- **Confidence**: high

## [sk-vspace] 0x24f97c/0x2513a8/0x254f50/0x255044/0x2550a0 Swift fatal-code shims
- **Observation**: Five tiny noreturn shims report a fixed code (1, 0x50, 1, 0x5b, 0x43) then enter the kernel's noreturn fatal handler. These are the Swift runtime's `_fatalError`/precondition entry points embedded in the kernel; they carry no caller-provided message, so any panic from them yields only the fixed code.
- **Evidence**: each body is `rt_00347de8(1); rt_001afe4c();` (or 0x50/0x5b/0x43 via FUN_003486b8) with FUN_001afe4c / FUN_001afa84 noreturn.
- **Severity (hypothesis)**: informational — fixed-code panic entry points (availability only).
- **Confidence**: high

## [sk-vspace] 0x0026cd08-0x00277ba8 Swift runtime Range/Collection bounds + UTF-8 buffer validation
- **Observation**: The cL4 kernel embeds the Swift standard-library Range/String/Collection machinery (0x26xxxx region). The Range, removeFirst/removeLast, and UTF-8 buffer operations are fail-closed: every bounds violation, invalid UTF-8 code point, or packed-buffer overflow is converted into the noreturn fatal trap FUN_001afe4c (Swift `_fatalError` / `preconditionFailure`) rather than a recoverable error. Specifically: empty-collection removeFirst traps code 0x222 (s_Can_t_remove_from_an_empty_colle_005d0370); Range lowerBound>=upperBound traps 0x2f9 (s_Range_requires_lowerBound_<__upp_005cda00); UTF-8 buffer overflow/invalid scalar traps 0xa7/0xc1/0xc2 (s_Swift_ValidUTF8Buffer_swift_005d08c0) or 0xbe/0xd4/0xdd (s_Swift_UIntBuffer_swift_005d0610); out-of-bounds index traps 0x2ca (s_Index_out_of_bounds_005cdab0). A malformed/oversized string index therefore panics the kernel rather than corrupting the packed bit-buffer.
- **Evidence**: FUN_00272820 (`sk_collection_remove_first`): `if (u==0) FUN_001afe4c(0x5d0370,0x25,..0x222)`, `if ((uint)idx<(uint)lb) FUN_001afe4c(0x5cda00,..0x2f9)`, per-byte `(map&0xff000000)` overflow -> 0xa7; FUN_00271fa0 (`sk_bitbuffer_append_16`): `if (off<0x20) {shift+store} else FUN_001afe4c(0x5d0610,..0xbe)`; FUN_00272c58/FUN_00273310: UTF-8 LZCOUNT-length decode with `0xd000000000000034` trap via FUN_001afa84 (s_Swift_UnicodeHelpers_swift_005ce730) on malformed sequences; FUN_0027169c: `if (r.hi==0) FUN_001afe4c(0x5cd7d0,..0x1c2)` ("Unexpectedly found nil while unwrapping").
- **Severity (hypothesis)**: medium — these are the kernel's own string/collection parser paths; all validation failures are hard panics (availability), but the bounds logic is correct and non-corrupting, so no privilege-escalation surface observed. The nil-tag (0xe000000000000000) handling in FUN_0026e1d8/FUN_0026e3b0 coerces nil to empty rather than dereferencing, which is the expected Optional-safe behavior.
- **Confidence**: high (explicit fatal strings + codes in every function).

## [sk-vspace] 0x002075e0 sk_index_lookup — object-table index OOB is a fail-closed panic
- **Observation**: The object-table index-lookup path validates a resolved index and, on any out-of-range/missing entry, traps with the Swift-style "Fatal error" / "Index out of bounds" / "Swift EnumeratedSequence" strings (sk_str_Fatal_error / sk_str_Index_out_of_bounds / sk_str_Swift_EnumeratedSequence) via the noreturn rt_001afe4c. There is no recoverable error path — an OOB index halts the kernel rather than reading out of bounds.
- **Evidence**: sk_index_lookup (002075e0) walks via rt_000277b8/rt_00310e20; on the non-taken (miss) branch it resolves the slot through rt_0032d3e0 and returns it; on failure it executes `rt_001afe4c(sk_str_Fatal_error,0xb,2,sk_str_Index_out_of_bounds,0x13,2,sk_str_Swift_EnumeratedSequence,0x1e)` (noreturn). Same OOB-fatal pattern is reused by the sibling table walkers sk_table_lookup (00206d88) / sk_table_range (00206f18), which additionally trap on signed borrow (SBORROW8 -> SoftwareBreakpoint 0x20711c) when a range delta would underflow.
- **Severity (hypothesis)**: low — the bounds logic is correct and non-corrupting (fail-closed panics); a crafted/buggy vspace walk that produces an out-of-range index would be a kernel-wide DoS (availability), but no out-of-bounds read/write is possible.
- **Confidence**: high (explicit fatal strings + code in the body).

## [sk-vspace] 0x002085a4 sk_abstract_method + 0x002087xx-0x00208axx — base-class virtuals are trap stubs
- **Observation**: The 002087xx-00208axx family (sk_vt_abstract_a/b, sk_vt_hook_a-e, and the six sk_dtor_pure_* destructors) are base-class virtual methods whose only behavior is to enter the runtime save (rt_00357cc8), emit "Method must be overridden" then "Fatal error" via sk_abstract_method (002085a4, noreturn rt_001afa84), and only then, in the pure-destructor stubs, release the object's +0x10/+0x20 fields. Any concrete subclass that fails to override one of these virtuals will hit an unconditional kernel panic on first call — a fail-closed virtual dispatch design.
- **Evidence**: sk_abstract_method (002085a4): `rt_0035ac70(sk_str_Method_must_be_overridden); rt_0006f768(sk_str_Fatal_error); rt_001afa84();` (noreturn). Each of sk_dtor_pure_a..f (002089ec..00208a70) contains 14 repetitions of `rt_00357cc8(); sk_abstract_method();` then `rt_0036b118(*(word_t*)(savx20+0x10)); rt_0036b118(*(word_t*)(savx20+0x20));`.
- **Severity (hypothesis)**: informational — this is the expected seL4-style vtable/abstract-method pattern; the trap guarantees an un-overridden virtual is never silently dispatched (no NULL-call into attacker-controlled code). Availability-only if a subclass is incomplete.
- **Confidence**: high (explicit "Method must be overridden" string, repeated identical stub bodies).

## [sk-vspace] 0x00204798 / 0x00205bd0 sk_desc_node / sk_desc_children — depth-budgeted recursive object walk
- **Observation**: The object-description walker carries a depth budget through *param_5: sk_desc_node and sk_desc_children decrement it on entry and return immediately when it reaches 0, and any arithmetic overflow on the remaining budget (SCARRY8 -> SoftwareBreakpoint 0x204ebc/0x204ec0/0x20609c/0x2060a0) traps. Child/super counts are formatted with the Swift-style "N children"/"1 child"/"super" strings. This bounds the recursion depth of the reflection dumper.
- **Evidence**: sk_desc_node (00204798) `lVar3 = *ptl7 + -1; if (*ptl7 < 1) return; *ptl7 = lVar3;` and recursive call `sk_desc_children(...,param_5+2,param_6-1,ptl7,...)`; sk_desc_children (00205bd0) same guard on *param_5; SCARRY8(param_5,2)/SCARRY8(param_3,2) SoftwareBreakpoint traps guard the budget arithmetic.
- **Severity (hypothesis)**: low — the explicit depth budget prevents unbounded/cyclic object-graph recursion in the description/dump path (availability/DoS protection); the overflow traps are defense-in-depth.
- **Confidence**: medium (depth-budget semantics inferred from the decrement+early-return; trap codes explicit).

## [sk-vspace] 0x002450ec sk_uint128_divide — division-by-zero and high-dividend overflow are hard traps
- **Observation**: The UInt128 division core rejects both a zero divisor and a dividend-high >= divisor-high (the condition that would make the 128-bit quotient overflow its 128-bit result) with a noreturn Swift fatal error rather than returning a truncated/wrapped quotient. Division-by-zero maps to s_Division_by_zero (0x5cd710); the overflow precondition maps to s_Dividend_high_must_be_smaller_th (0x5d3250). The shift-normalized long-division path is only reached after both guards pass.
- **Evidence**: FUN_002450ec: `if (dh==0 && dl==0) FUN_001afe4c(...0x165...)` and `if (CARRY8(...)&&CARRY8(...)) FUN_001afe4c(...0xd24...)` precede the LZCOUNT normalization and the per-bit subtraction loop. The signed wrapper sk_int128_divide_full (00245ef0) additionally traps when the quotient is not representable ("Quotient is not representable", 0x5d3280).
- **Severity (hypothesis)**: informational — fail-closed integer division; a caller supplying a bad divisor/dividend order cannot get a silent wrong quotient, only a kernel trap.
- **Confidence**: high (guard strings are explicit).

## [sk-vspace] 0x0023b254 / 0x0023b2a0 sk_int128_multiply(_full) — wide multiply overflow trapping
- **Observation**: The 128-bit multiply and its full-width (256-bit) variant carry the overflow/`_overflow` status explicitly and the full variant routes any multiply that would exceed the representable range to the noreturn Int128 `_overflow` fatal error (s_Swift_Int128_swift_005d0ed0, line 0x9f) rather than returning a wrapped product. The base multiply (0023b254) accumulates carries through the cross terms (uVar11/uVar12 with CARRY8 bumps) and returns the high word.
- **Evidence**: 0023b2a0: `if ((uVar9&0xff)==1) FUN_001afa84(...0x9f,1)` (the "operation overflow" fatal); SUB168/auVar* word products mirror seL4/Swift Int128.multipliedFullWidth. The base 0023b254 writes `*param_1 = param_4*param_2` and `param_1[1] = uVar1 + param_4*param_3` with carry bumps.
- **Severity (hypothesis)**: informational — fail-closed arithmetic; no silent wrap on the checked full-width path.
- **Confidence**: medium (fatal-string location matches Swift Int128._overflow).

## [sk-vspace] 0x0024893c sk_collection_sum_wide — unchecked accumulator overflow traps via SoftwareBreakpoint
- **Observation**: The wide-element sum helper accumulates a running total and traps (SoftwareBreakpoint(1,0x248a00)) if the running sum overflows (SCARRY8(lVar8, uVar3)), while separately validating the element tag (must be 0x01000000) and handling the "all-bits" sentinel (0x7fffff -> load from a live pointer, with alignment checks). This is a fail-closed sum over the collection, not a wrapping one.
- **Evidence**: `bVar2 = SCARRY8(lVar8,(ulong)uVar3); lVar8 = lVar8 + uVar3; if (bVar2) pcVar1=(code*)SoftwareBreakpoint(1,0x248a00); (*pcVar1)();` plus the element-tag gate `(uVar3 & 0x7f000000) != 0x1000000 -> acc=0`.
- **Severity (hypothesis)**: low — a corrupt/oversized element in the summed range traps the kernel instead of producing a silently-wrapped aggregate (availability; correctness-guard).
- **Confidence**: medium (element-tag semantics inferred; the overflow trap is explicit).

## [sk-vspace] 0x00248ae0 sk_word_width_decode — width selector is 4-bit masked, others fatal-0
- **Observation**: The Swift word-width/memattr selector decode only accepts selector types 1-4; the type field is `(param_1 >> 24) & 0x7f` and only the low 4 bits of param_1 feed the type-4 packed table lookup (0x50604 >> ((param_1&3)<<3)), while type 2 calls an allocator (FUN_0006f794(0)). Unsupported selector types return 0 rather than a trap.
- **Evidence**: `switch((param_1>>24)&0x7f){case 1:return 1;case 2:uVar1=FUN_0006f794(0);return uVar1;case 3:return 2;case 4:return 0x50604>>((param_1&3)<<3);} return 0;`.
- **Severity (hypothesis)**: informational — the decode is conservative (only 4 well-known widths), and type-2 width selection allocates through the runtime; a caller with an out-of-range type gets 0 (benign default), not a trap.
- **Confidence**: high (switch is explicit).

## [sk-vspace] 0x0027905c etc. vspace_op_* (slice 12, 0x277be4-0x27ffd8) — fail-closed vspace/MMU validation panics
- **Observation**: The vspace/MMU operation set in this slice validates its inputs and, on any validation failure, routes to a noreturn panic chain `FUN_00347d60(); FUN_001afe4c();` (the same fatal hook used across the kernel) rather than returning an error and continuing. Many operations additionally carry debug SoftwareBreakpoint traps on count/index-underflow guards (e.g. `SBORROW8(cnt,1)` → trap at the guard address, `if (SBORROW8(l9,1)) fn=(trap); (*fn)();`). Object-creation paths (0027bd10/0027c50c/0027dc80) allocate via `FUN_0036a908(size, tag)` and return a vtable pointer (`&DAT_003471a4/a8`), with teardown/release pairs (FUN_00358b24 free / FUN_0036b118 deref).
- **Evidence**: repeated `if (...) goto panic; FUN_00347d60(); FUN_001afe4c();` pattern across 27905c/279568/27c85c; SoftwareBreakpoint(1,0x…) trap fnptrs at 277de0/2782a4/279568; `FUN_0036a908(0x28,0x2ca3)` object alloc in 27c4a0. Call sites pass leftover registers (extraout_x*) so exact argument ABI is register-based (16-byte pair returns; hi unspecified).
- **Severity (hypothesis)**: informational — the vspace isolation boundary is fail-closed: invalid page-table/object operations trap or panic instead of being tolerated, which is the expected posture for a microkernel MMU layer; no silent partial success observed.
- **Confidence**: medium (panic/trap control flow is explicit in the decompiles; the exact register-argument semantics are inferred).

## [sk-vspace] 0x0022a5cc/0x0022a644/0x0022aaac/0x0022aaec sk_u*_bit_width — zero traps via Swift fatal
- **Observation**: The bit-width primitives for the integer types trap (noreturn Swift "Fatal error", Swift/Integers.swift line 0x985) on a zero/negative input instead of returning a sentinel, matching the Swift standard library's `bitWidth` precondition. The cL4 kernel thus hard-halts on `bitWidth(0)`.
- **Evidence**: `if (v != 0) return 0x10 - (LZCOUNT(v<<16)+1);` else `FUN_001afe4c(s_Fatal_error..., 0x985, 1)`; Int64 variant requires `0 < v`.
- **Severity (hypothesis)**: informational — fail-closed precondition trap (availability only); matches upstream Swift semantics.
- **Confidence**: high (explicit trap + line number).

## [sk-vspace] 0x0022d420/0x0022d898/0x0022dc54/0x0022e018/0x0022e3d4/0x0022e798/0x0022eb38 sk_parse_u* — "Invalid slice" bounds trap
- **Observation**: The string-to-integer parsers validate the input slice bounds before parsing: any slice whose start is negative or whose end exceeds the buffer traps with "Invalid slice" (Swift/UnsafeBufferPointer.swift, line 0x7db), and a zero-length buffer traps line 0x75e. Numeric overflow during accumulation also aborts the parse (returns the success-flag zero) rather than wrapping.
- **Evidence**: `if (slice.lo < 0 || bound < slice.hi) sk_swift_fatal_error(..., s_Invalid_slice_005cfa58, 0xd, 2, s_Swift_UnsafeBufferPointer..., 0x1f, 2, 0x7db, 1)`; per-digit `(uVar & 0xff00)!=0` / `t>>64` overflow checks return failure.
- **Severity (hypothesis)**: informational — input validation is fail-closed (a malformed slice halts rather than parsing garbage).
- **Confidence**: high (explicit trap strings).

## [sk-vspace] 0x002322fc/0x002324b0/0x00232578/0x00232654/0x002327f0/0x00232904 sk_*_divmod — divide-by-zero and INT_MIN/-1 overflow traps
- **Observation**: The checked divide-with-remainder primitives are fail-closed: a zero divisor traps "Division by zero" (Swift/IntegerTypes.swift or UInt128.swift/Int128.swift) and the signed variants additionally trap on the `INT_MIN / -1` overflow case ("Division results in an overflow"). The cL4 kernel cannot silently divide by zero.
- **Evidence**: `if (d == 0) sk_swift_fatal_error(s_Division_by_zero_005cd710, 0x10, ...)`; signed: `else if (d == -1 && n == -0x80000000) sk_swift_fatal_error(s_Division_results_in_an_overflow_005cd6d0, ...)`.
- **Severity (hypothesis)**: informational — fail-closed arithmetic (availability only); a buggy kernel caller can panic the kernel but cannot produce a wrong quotient.
- **Confidence**: high (explicit trap strings + per-width line numbers).

## [sk-vspace] 0x0022984c..0x0022a0c4 sk_siphash_* — SipHash _Hasher core uses fixed ASCII constants
- **Observation**: The hashing core is SipHash-2-4 with the canonical ASCII key/mixing constants ("somepseudorandomlygeneratedbytes", 0x736f6d6570736575 / 0x646f72616e646f6d / 0x6c7967656e657261) and per-state XOR-rotate rounds. This is the Swift `_Hasher`; no weakness observed, but the constants being fixed means hash DoS resistance depends on per-instance seeding (key from FUN_003560e4 / DAT_006adf10).
- **Evidence**: `s[1] = k.lo ^ 0x736f6d6570736575ull; s[2] = k.hi ^ 0x646f72616e646f6dull; s[3] = k.lo ^ 0x6c7967656e657261ull;` and the 0x7465646279746573 ("stedybt"/c2) constant in finalization.
- **Severity (hypothesis)**: informational — cryptographic hygiene; per-instance keying is the only defense against hash-collision attacks, so the seeding call site (FUN_003560e4) matters.
- **Confidence**: high (canonical SipHash round arithmetic + constants).


## [sk-slice03] 0x0001a2f4..0x00020c88 Tightbeam ComponentInitData / TransportBuffer — pervasive fail-closed invariant traps
- **Observation**: The Tightbeam serialization layer (ComponentInitData record reader/validator, TransportBuffer, ForwardingConnection) validates every record magic, declared length, and position advance against the buffer bounds before use. Malformed records — wrong magic (TYPEDATA/INITDATA/COMPDATA/ENDPDATA/CLNTDATA), declared length exceeding the remaining span, negative lengths, or out-of-order positions — hit a `SoftwareBreakpoint(1, <line>)` or the noreturn `cL4_fatal_1afa84` reporter (module `Tightbeam_ComponentInitData`/`Tightbeam_TransportBuffer`) with a precise line number. TransportBuffer base/data/raw-pointer getters (FUN_000209f8/20ac8/20bb8) only return a pointer after checking `position <= limit` and the not-forgotten flag; a forgotten (freed) buffer traps rather than exposing a dangling pointer.
- **Evidence**: e.g. `FUN_0001e3e0` (`CLNTDATA` validate): `if (buf==0 || lim-buf<0x25) fatal(0xd000000000000033,0x80000000005acaf0,...,0x1f2)`; magic mismatch `fatal(0xd00000000000001b,...)`; `FUN_0001c81c`: per-record `*plVar5 != 0x434f4d5044415441` -> `FUN_003698b0` log + `fatal(...0x2e5)`. Dozens of distinct breakpoint lines (0x1a320..0x20bf8).
- **Severity (hypothesis)**: informational — fail-closed parsing (availability only); a malformed component payload can panic the kernel but cannot be parsed into a wrong/garbage structure. The count of trap paths indicates hardened, review-heavy code.
- **Confidence**: high (explicit magic constants + per-line trap addresses).

## [sk-slice03] 0x0001fde8 cL4_entry_resolve — tagged function-pointer indirection
- **Observation**: FUN_0001fde8 resolves a call target from a tagged word: if bit0 is set, it dereferences the word aligned-down to a pointer and adds the sign-extended 32-bit displacement at +4 (an ARM64 br/bl-style thunk descriptor). This is used by the ForwardingConnection send path (FUN_0001f834) to reach the message-handling entry. The target is therefore attacker-influenced only if the tagged word itself is attacker-controlled.
- **Evidence**: `if (obj&1) obj=*(obj & ~1); return (obj+4) + (int32)*(uint32*)(obj+4);`
- **Severity (hypothesis)**: informational — standard indirection; only becomes a hijack primitive if a ForwardingConnection object's tag word is spoofable, which the surrounding validation (not-forgotten flag, retained refs) is designed to prevent.
- **Confidence**: medium (shape strongly suggests a thunk descriptor; exact producer of the tagged word not yet traced).

## [sk-slice03] 0x0001b620/0x0001a838/0x0001b02c Tightbeam record writers — bounds-checked serialization
- **Observation**: The record writers (INITDATA/CLNTDATA/COMPDATA) compute the full serialized size up front (FUN_0001b370/FUN_0001a760/FUN_0001afb4), check the destination has room, then write magic + header + per-field records, re-validating the running position against the destination on every iteration (breakpoints 0x1b348..0x1b964, 0x1aabc..0x1aac0, etc.). A too-small destination returns 0 rather than overrunning.
- **Evidence**: `if (dst==0 || avail<recsize) goto no_room` where `no_room: FUN_003698b0(0,0x659b58,0x6598d8); return 0;` and carry checks `SCARRY8` on every size addition trap at dedicated lines.
- **Severity (hypothesis)**: informational — serialization cannot overflow its destination; failure returns an error instead of a partial/corrupt record.
- **Confidence**: high (explicit capacity checks + carry traps on every write).

## [sk-slice04] 0x00020ebc TightbeamMessage status-string encoder (FUN_00020ebc)
- **Observation**: The status→String map builds Swift tagged-pointer strings from fixed low-address literals (0x005acf30, 0x005aced0, ...) with the top bit set (0x8000000000000000) and length nibbles packed into the low byte. Codes 6/8/0xb..0xf and any value >0x10 fall through to a shared "Unknown n" inline string.
- **Evidence**: decompile: `auVar8._8_8_ = (ulong)(pcVar3 + -0x20) | 0x8000000000000000; auVar8._0_8_ = 0xd000000000000011;` and the `switchD_00020efc_caseD_6` default bucket.
- **Severity (hypothesis)**: informational — a status code is rendered into an unbounded set of inline/tagged string forms, all from read-only rodata; no attacker-controlled pointer is dereferenced.
- **Confidence**: high (literal-packed Swift small strings).

## [sk-slice04] 0x00022718 Tightbeam buffer offset bounds check (FUN_00022718)
- **Observation**: The offset helper returns `base + off` only when `off >= 0 && base != 0 && off < end - base`; on any violation it pushes "offset error" diagnostics (0x80000000005ad050 / 0x80000000005ad070) and calls the fatal handler. This is the central bounds gate for all Tightbeam record field access.
- **Evidence**: `if (((-1 < (long)param_1) && (param_2 != 0)) && (param_1 < (ulong)(param_3 - param_2))) return param_2 + param_1;` else `FUN_002a4ab4(0x34); ...FUN_001afa84(...)`.
- **Severity (hypothesis)**: hardening control — out-of-bounds offset traps rather than writing; prevents record-field OOB read/write in the codec.
- **Confidence**: high (explicit range check before pointer arithmetic).

## [sk-slice04] 0x00021260 Tightbeam varint encoder — width/payload size selection (FUN_00021260)
- **Observation**: The variable-width integer writer derives a width from the message buffer length (`uVar4 = *(ulong*)(*(long*)(*(long*)(self+0x10)+-8)+0x40)`, min 4) and picks a 1/2/4-byte payload plus a width-marker byte. The carry/overflow arithmetic uses `-1 << (w<<3&0x1f)` bit tricks; a width of 0 in the `w<4` branch writes only the low byte. If the buffer length were attacker-controlled the width selection could mismatch the real allocation.
- **Evidence**: `uVar2 = ((flags + ~(-1 << (w<<3&0x1f))) - 0xfe >> (w<<3&0x1f)) + 1;` and the m==0/2/4 store-size branches.
- **Severity (hypothesis)**: low — width is derived from the message's own length metadata, and the payload writes stay within `w1=width+1`; no explicit capacity check before the stores.
- **Confidence**: medium (decompiler-driven, no independent overflow guard observed at this site).

## [sk-slice04] 0x00021554 Tightbeam message unwrap (FUN_00021554)
- **Observation**: Unwrapping the message buffer copies `end-start` bytes from the storage payload into the message. It bounds-checks `uVar10 + uVar6 <= uVar9` (cursor + length against storage length) and re-checks `uVar6 <= uVar9 - uVar10` before the memcpy shim; on failure it either returns 1 or traps SoftwareBreakpoint(0x5519). A null `start` (0) and a pre-unwrapped message both fatal.
- **Evidence**: `if (uVar10 + uVar6 <= uVar9) { ... uVar2 = uVar11 + uVar10; if ((uVar2 <= uVar11+uVar9 && uVar11<=uVar2) && (uVar6<=uVar9-uVar10)) ... }` with `SoftwareBreakpoint(0x5519,0x18768)`.
- **Severity (hypothesis)**: hardening control — copy length validated against storage before memcpy; overflow path traps.
- **Confidence**: medium (double-checked bounds but the carry test is on the storage cursor, not the destination).

## [sk-slice04] 0x00025704 TightbeamMessage deinit — storage-tag release dispatch (FUN_00025704)
- **Observation**: Deinit inspects the storage descriptor tag `((uVar6>>32)>>29)` and dispatches release to FUN_00014f10 (tag 1) / FUN_00014bec (tag 0) / the wrapper buffer-field closure (tag other). A tag of 3 (or any non-0/1 tag with kind != 0xff) always terminates in a fatal (0x4e/0x1ba) after releasing the fields — i.e. there is no silent path that frees attacker-controlled pointers without a kind/tag check.
- **Evidence**: decompile branches on `uVar7`/`uVar2>>0x1d`; the `else` fatal path `FUN_001afa84(...0xd00000000000004e..., 0x1ba)`.
- **Severity (hypothesis)**: informational — deinit is defensive: unexpected storage tags fault instead of mis-releasing.
- **Confidence**: medium (fatal reachability inferred from the branch structure).

## [sk-slice04] 0x000240e4 TightbeamMessage reset — storage-tag validation (FUN_000240e4)
- **Observation**: Reset switches on the storage descriptor tag; tags 0/1/2 attempt a merge via FUN_00014f90/FUN_00014c08, but tags 3 and other are rejected with a fatal ("TightbeamMessage.reset called on..." 0x49/0x4d, diagnostics 0x1a6/0x1a8). This closes the door on resetting a message whose storage layout is unrecognized.
- **Evidence**: `if (uVar7==3) {...0xd000000000000049...} else {...0xd00000000000004d...}` fatal branches; strings s_TightbeamMessage_reset___called_o_005ad270/005ad220.
- **Severity (hypothesis)**: hardening control — unknown storage kind is a hard fault, not a misinterpreted merge.
- **Confidence**: high (two explicit fatal branches on the tag).

## [sk-slice04] 0x00024f40 / 0x000252d4 TransportBuffer encode / decode — buffer size gate
- **Observation**: TransportBuffer encode rejects a buffer size > 1 word with a fatal (TransportBuffer, 0x3b/0x25); decode allocates a 0x18-byte object, resolves the witness via FUN_00025dcc, and releases the buffer unless the size flag says it is owned. The whole region routes every field access through the offset bounds gate (0x22718) and the canary-checked generic read/append wrappers.
- **Evidence**: `if (1 < extraout_w12) { ...FUN_001afa84(...0x25, 0x80000000005acd00, TransportBuffer...) }`; decode `FUN_0036b270(param_2); (*pcVar2)(&local_118, ...)`.
- **Severity (hypothesis)**: hardening control — oversized buffers and post-size-release ownership are gated.
- **Confidence**: medium.

## [sk-slice04] 0x000219c4 et al. — Swift stack canary (0x2c8502b44bfffed6) on every read wrapper
- **Observation**: Every generic read/append wrapper (FUN_000219c4, 21ad8, 21bec, 21d00, 22338, 22448, 22558, 22668, 23330, 233c8, 23670, 23704) seeds a local with the sentinel `-0x2c8502b44bfffed6` and, after invoking the reader/writer, verifies it is unchanged; if overwritten it faults via FUN_0011d7e8. The unwrap guard (`self+0x10 == 0` → fatal 0x93) precedes every call.
- **Evidence**: `local_18 = -0x2c8502b44bfffed6; ... if (local_18 == -0x2c8502b44bfffed6) return; FUN_0011d7e8(...)`.
- **Severity (hypothesis)**: integrity control — Swift stack-scratch canary detects writer overruns into the scratch slot; any corruption faults instead of propagating.
- **Confidence**: high (explicit sentinel compare + noreturn fault handler).

## [sk-caps] 0x00084824 cL4 supervisor call (FUN_00084824)
- **Observation**: The cL4 SK issues a supervisor call (CallSupervisor(0), svc #0) with a 3-word message block rooted at the per-CPU tpidrro_el0 register {kind=0x11, arg0, arg1}, then restores kind to 0x11. This is the SK's exit/syscall interface into the hypervisor/SPTM guarded levels.
- **Evidence**: decompile: msg block at tpidrro_el0 = {0x11, param_2, param_3}; CallSupervisor(0); *puVar1 = 0x11.
- **Severity (hypothesis)**: info — the SK-to-hypervisor boundary crossing mechanism.
- **Confidence**: medium.

## [sk-caps] 0x00084368 cL4 exclave-launch device-tree mapping (FUN_00084368)
- **Observation**: The InternalExclaveLauncher maps the device tree (DTBlob) received from the hypervisor into the exclave VAS at fixed high addresses (0xe000000000000000 region) in 16 KiB pages via the vas-map op, after resolving the DeviceTree node. The hypervisor-supplied device tree is treated as trusted and mapped verbatim into the exclave.
- **Evidence**: strings 'InternalExclaveLauncher/DTBlob.swift', 'InternalExclaveLauncher/VASExtension.swift', 'DEVICETREE FROM HYPERVISOR ON ADDRESSES 0x', 'mapDeviceTree()'; loop maps 0x4000-byte units; log address base 0xe000000000000000.
- **Severity (hypothesis)**: hypothesis — hypervisor-supplied DT is trusted input to the exclave; a malicious DT could steer exclave memory mapping.
- **Confidence**: medium.

## [sk-caps] 0x00084ee0 cL4 VAS error encoding (FUN_00084ee0)
- **Observation**: VAS operations encode errors as inline-ASCII tag words (e.g. 0x6563637553736176 'vasSucce', 0x6f46746f4e736176 'vasNtoFo') packed into 64-bit literals alongside status codes; messages 'vasOperationInvalid' and 'vasVirtualSpaceUnavailable' are logged. The packed word format is a cL4-specific ABI detail.
- **Evidence**: switch on op<8 with literal ASCII words; log_86840('vasOperationInvalid')/('vasVirtualSpaceUnavailable').
- **Severity (hypothesis)**: info.
- **Confidence**: medium.

## [sk-caps] 0x0008553c cL4 VAS dealloc is fail-stop (FUN_0008553c)
- **Observation**: VAS deallocation failure logs 'Could not deallocate vas span <code>' and traps (SoftwareBreakpoint 0x8562c) instead of recovering — VAS span deallocation is fatal on error.
- **Evidence**: decompile: cL4_log_86840('Could not deallocate vas span '); breakpoint 0x8562c after status check.
- **Severity (hypothesis)**: info.
- **Confidence**: medium.

## [sk-caps] 0x000dc860 cL4 capability-free has no rollback (FUN_000dc860)
- **Observation**: Capability-free validates the capability name length and faults if >0xff, but on resolution failure panics via a fatal-error path rather than returning an error; free is destructive with no rollback.
- **Evidence**: len=FUN_00157308(param_2); if(0xff<len) SoftwareBreakpoint(1,0xdc91c); on resolve fail calls 'Could not free cap' 0x5c3f70 then xrt_fatal_dce40 (noreturn).
- **Severity (hypothesis)**: informational — free is a one-shot destructive op.
- **Confidence**: medium.

## [sk-caps] 0x000dc634 / 0x000dc9f4 / 0x000dca30 cL4 boot capability stubs are fail-stop
- **Observation**: conclaveId:asid init hard-faults if the mode arg is negative and panics if the PMM state object is absent. getIrqCap and allocUntyped are explicit unimplemented stubs that panic (noreturn) — the cL4 boot environment lacks IRQ-cap and untyped-cap retrieval; any caller hits a noreturn fault.
- **Evidence**: 'getIrqCap unimplemented' 0x5c3fc0; 'allocUntyped unimplemented' 0x5c3fe0; panic 'Couldn't get PMM reference' 0x5c4000; all route to noreturn FUN_001afa84.
- **Severity (hypothesis)**: low — absent capability paths fault rather than silently downgrade.
- **Confidence**: high.

## [sk-caps] 0x000dca30 cL4 Swift stack canary on boot-cap paths
- **Observation**: Stack canary check (sentinel 0xd17a4fb44b02d2a = -0x2c8502b44bfffed6) present on boot-path functions; failure calls a noreturn handler. The same canary guards the tightbeam read/append wrappers across the caps region.
- **Evidence**: local seeded to -0x2c8502b44bfffed6, checked at return, else FUN_0011d7e8.
- **Severity (hypothesis)**: integrity control — detects writer overruns into stack scratch slots.
- **Confidence**: high.

## [sk-caps] 0x000ff47c / 0x000ff728 InternalExclaveLauncher object dispatch and allocation
- **Observation**: The InternalExclaveLauncher component (banner 'InternalExclaveLauncher_Component' 0x5c6300) carries an exception-frame vtable probe and builds error/success results with hardcoded seL4-style error words 0xeb00000000287974 and 0xe000000000000000. Object-type dispatch: type 0x14 routes to allocate-with, anything else triggers a noreturn fatal 'Unknown ObjectType' panic (FUN_001afa84, line 0x1af).
- **Evidence**: decompile of 0xff47c shows vtable call at frame+0x48 and both branches writing these constant error words; kind!=0x14 path calls FUN_002a4ab4, FUN_003a25d4, FUN_00086840('Unknown ObjectType'), then noreturn FUN_001afa84.
- **Severity (hypothesis)**: informational — type-checked allocation with fail-stop on unknown type.
- **Confidence**: medium.

## [sk-caps] 0x000ffba8 InternalExclaveLauncher teardown sentinel
- **Observation**: Teardown writes sentinel value -0x7fffffffffa39b90 into two consecutive words at x24+4 — a deliberate poison/canary pattern distinguishing a live from a torn-down launcher object.
- **Evidence**: decompile: extraout_x1[0]=unaff_x24+4, extraout_x1[1]=-0x7fffffffffa39b90.
- **Severity (hypothesis)**: informational.
- **Confidence**: low.

## [sk-caps] 0x000f6d20 et al. capability retirement paths (sched_retire_cap_*)
- **Observation**: Multiple cap-retirement continuations (0xf6d20, 0xf6d88, 0xf6dec, 0xf6f04, 0xf6f3c) share branch-continuation structure (extraout_x8 register carry), indicating a common scheduler capability-retirement/teardown flow spread across many small thunks.
- **Evidence**: decompiles show `extraout_x8` carry and shared retire structure.
- **Severity (hypothesis)**: info — map of the cap-teardown path.
- **Confidence**: low.

## [sk-caps] 0x0009ea60 / 0x0009ea90 cL4 IPC-buffer resolve and supervisor tail
- **Observation**: IPC-buffer resolution is relocatable object-image ref resolution (base+4+offset); the supervisor tail does a TPIDRRO_EL0 handshake + CallSupervisor(0). Together they form the exclave's IPC-in / IPC-out boundary into the SK.
- **Evidence**: decompile of 0x9ea60 (ref resolution) and 0x9ea90 (supervisor call).
- **Severity (hypothesis)**: info.
- **Confidence**: medium.

## [sk-caps] 0x0009955c exclave_launcher_run — cap build from raw-AS table
- **Observation**: The core run path builds capabilities from a raw address-space table and maps region caps (map_all_caps frames), marshaling registers and setting the SC badge/cap-set — the exclave's capability-context establishment on launch.
- **Evidence**: decompile: walk cap list, marshal regs, sc badge/cap-set 9d444/9d460; frame alloc 0x4000 + map.
- **Severity (hypothesis)**: info — cap-context construction boundary.
- **Confidence**: low.

## [sk-obj] 00287c68 sk_cap_setup — cap-slot install bounds+bitmap validation
- **Observation**: Installing a capability into an object's cap table validates (a) the slot index is non-negative, (b) it is < the table's declared bit width (param_4+0x20), (c) the slot's bit is set in the bitmap at param_4+0x38, and (d) the caller-supplied type index equals the table's stored type (+0x24). Any check failure raises the noreturn panic FUN_001afe4c. The install then dispatches through the per-type handler (obj-8+0x10).
- **Evidence**: `if (((-1 < slot) && (slot >> nbits == 0)) && (bitmap[slot>>6]>>(slot&0x3f)&1) && (type_idx == *(int*)(table+0x24)))` then `(**(table-8+0x10))(param_1, table+0x30 + (type+0x48)*slot, obj)`; else `FUN_003488bc(1); FUN_0034a3ec(); FUN_001afe4c()` (noreturn).
- **Severity (hypothesis)**: low — fail-closed cap install: an out-of-range/forged slot or type-index mismatch cannot reach the install handler; all failure modes are hard panics.
- **Confidence**: high (explicit bounds + bitmap + type checks before the indirect install call).

## [sk-obj] 00281d4c / 00281ef4 sk_swift_string_utf16/utf8_append — Swift runtime collection bounds traps
- **Observation**: The embedded Swift runtime's UTF-16/UTF-8 string append helpers enforce destination capacity with hard noreturn preconditions: negative count, index-out-of-range (0x136), index-out-of-bounds (0x2ca), and invalid UTF-8 scalar index (0x1e2) all raise the noreturn Swift fatal error (FUN_001afe4c). A SoftwareBreakpoint(1, 0x281ef4) guards the surrogate/continuation path.
- **Evidence**: multiple `FUN_001afe4c("Fatal error",0xb,2,"Index out of range",0x12,2,"Swift.Range",0x11,2,0x136,1)` and `SoftwareBreakpoint(1,0x281ef4)` when `surrogate>>0x10 != 0`.
- **Severity (hypothesis)**: informational — fail-closed bounds checking in the kernel's embedded Swift stdlib (defense-in-depth; the fatal paths are preconditions, not attacker-controlled checks).
- **Confidence**: high (string-matched Swift precondition messages).

## [sk-obj] 00287794 sk_swift_set_apply — Set insert path hash-probe + dedup
- **Observation**: The Swift Set builder (00287580) and Set apply (00287794) use an open-addressing hash probe (bitmask at set+7 / +0x20) and de-duplicate keys by comparing stored vs incoming (FUN_002a0d50 string compare, 0x6000000000000000 sentinel checks) before inserting, releasing the duplicate string (FUN_003a25d4). String keys are released after insert.
- **Evidence**: `while ((bitmap[h>>6]>>(h&0x3f)&1)!=0) { slot=...; if (skey==key||...string_cmp...) { release; goto next; } h++; } insert(...)`.
- **Severity (hypothesis)**: informational — correct key de-duplication and hash probing; no observed weakness.
- **Confidence**: medium.

## [sk-obj] 00287580 sk_swift_string_set_build — XOR-obfuscated string constants in set builder
- **Observation**: The Set builder constructs its descriptor strings via XOR against the global key DAT_006adf18/006adf10 (e.g. 0x7465646279746573^key = "setedbyted", 0x646f72616e646f6d^key = "random..."). This is the seL4/cL4 metadata obfuscation pattern also seen in the object descriptor region.
- **Evidence**: `local_88 = _DAT_006adf18 ^ 0x7465646279746573; uStack_90 = _DAT_006adf10 ^ puVar8[5] ^ 0x6c7967656e657261;` etc.
- **Severity (hypothesis)**: informational — cosmetic string obfuscation (static-key XOR), not a real secrecy boundary.
- **Confidence**: medium.

## [sk-obj] 00284148 sk_swift_uint_setbit_map — Set iterator bit-reversal + overflow trap
- **Observation**: The Swift Set/bitmap iterator extracts set-bit indices via full 64-bit bit reversal and a trailing-zero (LZCOUNT) computation, and traps (SoftwareBreakpoint(1, 0x2842e4)) if the word-index arithmetic overflows (SCARRY8). The index is bounded by the bitmap's declared width.
- **Evidence**: `if (SCARRY8(lVar11,1)) { SoftwareBreakpoint(1,0x2842e4); }` and `if ((long)(0x3f-uVar9>>6) <= next) { word=0; goto done; }`.
- **Severity (hypothesis)**: informational — the iterator bounds itself to the bitmap width and traps on overflow (no unbounded walk).
- **Confidence**: medium.

## [sk-obj] 00281cc0/002821c4 sk_swift_array_init_repeat — Swift Array init repeat capacity cap
- **Observation**: Swift `Array(repeating:count:)` in this build hard-caps the element count at 2 for the 8/16-byte element variants: a requested count > 2 is silently truncated to 2 (via the `if (i==2) { count=2; break; }` sentinel) rather than allocating more storage. Counts < 0 raise the Range noreturn precondition.
- **Evidence**: `if (lVar3 == 2) { param_3 = 2; break; }` in both 00281cc0 and 002821c4; `if (param_3 < 0) FUN_001afe4c(...,0xb5,1)`.
- **Severity (hypothesis)**: informational — fixed-size stack buffer init; the 2-element cap is a Swift ABI artifact (small-array buffer), not a security boundary.
- **Confidence**: high (explicit cap + string-matched Range precondition).

## [ringminus1] 000012d4..00010244 sk_boot_launcher_entry..sk_alloc_calloc (SK00 slice: root-task launch + lite_zone)
- **Observation**: The Secure Kernel embeds a full libmalloc-derived allocator (lite_zone) and its root-task launcher in the same image. The allocator's per-CPU lock path (FUN_0011582c/94) records a "Failed to acquire/release lock" diagnostic on contention rather than a fail-closed panic in most fast paths, but the size-class validity checks all terminate in a BUG_IN_LIBMALLOC panic (fail-closed). Free-path pointer validation (FUN_0000cc60 ptr_size / FUN_0000d01c ptr_owned) rejects out-of-zone pointers, and any invalid free goes to a client-of-libmalloc panic.
- **Evidence**: Allocator fast-path lock wrappers at 0x2e50/0x3e7c/0x38ac acquire `l2 = zone+0x10` with `sk_lock_acquire`; on failure `sk_lock_error(0x40,0,"Failed to acquire lock: %p")` then continues — a lock-acquire failure in the bump/region path would proceed with the lock held. Size-class dispatch switch statements at 0x3794/0x38ac/0x4acc default to `sk_bug_panic("BUG IN LIBMALLOC: %llu, %s")` (0x005a9249). Free validation in 0xcc60/0xd01c returns 0 and records errno 0xc (via sk_errno_slot FUN_0006037c) instead of panicking on unknown pointers.
- **Severity (hypothesis)**: low — allocator double-free / cross-zone free is caught (panic), but a lock-acquire failure is logged-and-continued rather than aborted, which under real contention could corrupt the zone free lists.
- **Confidence**: medium

## [ringminus1] 00002a10 lite_zone_init_memory
- **Observation**: Zone memory init maps a 0x140000000-byte (5 GiB) region table and, when the zone is configured for the large memory model (`*(char*)(param_1+0x1bf)=='\\x02'`), splits the top of the 32-bit window with a computed 0x1000000-aligned limit; several intermediate misalignment/overflow conditions trap to SoftwareBreakpoint(0x5519).
- **Evidence**: `sk_alloc_zone_0(0,0x140000000,0x19,1,0x200,5,v+0x20)` for the region table; `(a0 & 0x1ffffff)!=0` / `lim<a0` / `u<=lim` all fall into the "does not return" SoftwareBreakpoint(0x5519) path (FUN_004afc5c/78/94/cc). Bounds guard `uVar1 = uVar3 + uVar7; if (uVar1 <= uVar3) goto bug`.
- **Severity (hypothesis)**: informational — the 5 GiB region-table mapping is a large fixed carve-out of the secure kernel's VA space at boot.
- **Confidence**: medium

## [ringminus1] 00006630 lite_zone_create
- **Observation**: Zone creation sizes the zone struct from the CPU count and boot-image flag (bVar5==0 selects the +0x6d80 layout), allocates it via the bootstrap allocator, and initializes all per-class lock/free-list state before returning it. The 5GiB carve-out and per-class table layout are fixed and derive from a single global CPU count (DAT_006ac234).
- **Evidence**: `lVar19 = uVar21*0x25b0 + (bVar5==0 ? 0x6d80 : 0x6720) + uVar21*0xc90`; `puVar11[0x34]=lVar18`; `FUN_00006cbc(puVar11,lVar18,1,0xc9,uVar21,...)` installs the method table; per-CPU size derived from DAT_006ac234.
- **Severity (hypothesis)**: informational — allocator metadata size is O(cpu_count); a maliciously large DT cpu count would inflate the carve-out.
- **Confidence**: low

## [ringminus1] 000101a0 sk_alloc_malloc / 00010244 sk_alloc_calloc
- **Observation**: The two exported allocator entry points dispatch through a single global zone pointer (DAT_0064c060) and wrap the result in an explicit overflow check: malloc traps on a wrapped `end=base+size` range, calloc traps on `total=nmemb*size` overflow before returning. A `zone + 200 < zone` wrap (32-bit zone base + 200) also traps.
- **Evidence**: `lVar3=*DAT_0064c060; if (*(uint*)(lVar3+0x68)<0x10) call(vtable+0x18) else call(vtable+0xa0)`; `(uVar4<=uVar1 && uVar4==0||size<=uVar1-uVar4) && ...` else `SoftwareBreakpoint(0x5519,0x10244)`. calloc: `uVar4=param_2*param_1`; `(uVar3<=uVar1 && uVar3==0||(uVar4<uVar1-uVar3||uVar4-(uVar1-uVar3)==0))` else `SoftwareBreakpoint(0x5519,0x102f4)`.
- **Severity (hypothesis)**: informational — the calloc path correctly guards integer overflow in the `nmemb*size` product.
- **Confidence**: high

## [sk-vspace] 0021e870 swift_hash_mix — ChaCha/SipHash-style mixing constant
- **Observation**: The cL4 kernel's embedded Swift runtime mixes 64-bit state with the ChaCha/SipHash round constant 0x7465646279746573 ("stbyteds"? little-endian of "stbyte...") using rotate-xor linear feedback, then XORs 0x8000000000000000 and 0xff before feeding the result to the continuation. This is a standard non-cryptographic-keyed hash round; the fixed constant makes the mix deterministic (not secret).
- **Evidence**: thunk_FUN_00229ebc: `v2 = e1 ^ 0x7465646279746573 ^ e8; ... v1 = (v1^e1)+v5; v4 = ((v2>>0x20|v2<<0x20)^0xff)+v4 ^ (v4>>0x30|v4<<0x10); rt_00351d4c(...)`.
- **Severity (hypothesis)**: informational — hash mix is public-constant, deterministic (expected for a non-keyed hash); no weakness observed.
- **Confidence**: high

## [sk-vspace] 0021e844/0021e874/0021e8c0/0021e8f0 swift_int_to_grade / swift_char_equal / swift_char_grade / swift_char_load
- **Observation**: Small helpers grading small integers to 0/1/2 (via FUN_0021e844) and comparing Characters (rt_00149368) used by the string layer. The char-grade function writes the grade into a byte the caller supplies; the load reads the byte and forwards it. These are non-security structural helpers.
- **Evidence**: 0021e844 returns 0 when param==0, 1 when ==1, else 2; 0021e874 compares rt_00149368(*p1)==rt_00149368(*p2); 0021e8c0 `*p1 = FUN_0021e844(*p2)`; 0021e8f0 `*p1 = rt_00149368(*unaff_x20)`.
- **Severity (hypothesis)**: informational.
- **Confidence**: high

## [sk-vspace] 0021ef5c/0021ef80/0021ef30 (+ max/abs variants) float/half/double min-max NaN semantics
- **Observation**: The min/max functions implement IEEE-754-2019-style semantics: when the second operand is NaN, they return the other operand (and vice-versa via the bit-mask tests on exponent/mantissa); signaling NaN handling is per-spec. These gate arithmetic in the Swift runtime, not the vspace boundary.
- **Evidence**: 0021ef5c `if (p2<p1){ f=p2; if((u32)p2&0x7fffff) f=p1; p1=p2; if(((u32)p2^0xffffffff)&0x7f800000==0) p1=f; }` — NaN and inf bit tests.
- **Severity (hypothesis)**: informational — no weakness observed.
- **Confidence**: high

## [sk-vspace] 0021a660 family string_distance — no unbounded-count loop
- **Observation**: The Flatten/Collection distance helpers accumulate character counts with SCARRY8 overflow checks and Swift fatal traps on out-of-bounds indices ("String index is out of bounds", "Index out of range"); all index arithmetic is bounds-checked before dereference, and the accumulate multiply/add is carry-checked with a SoftwareBreakpoint on overflow. No unbounded or unchecked count loop observed.
- **Evidence**: 0021a660/0021acec/0021b1a4/0021b91c/0021bf60/0021c41c each: `if (uVar15<=uVar4) FUN_001afe4c(s_Fatal_error_...,s_String_index_is_out_of_bounds_005ce6a0,...)`; `if (SCARRY8(lVar4,uVar3*lVar13)) SW_BREAK(0x21aab4)`.
- **Severity (hypothesis)**: informational — defensive bounds/overflow checks in the string layer.
- **Confidence**: high

## [sk] 0004b520/0004b664 sk_cap_retain / sk_cap_release — refcount saturation guard on capability words
- **Observation**: The cL4 capability retain/release pair guards the 16-bit refcount against saturation and underflow. `sk_cap_release` returns early when the count is already 0 (`&0xfffe == 0`) or already maxed (`&0xfffe == 0xfffe`), and only invokes the destroy callback + frees the tagged object when the low word is exactly 2 (i.e. the count is about to hit zero). Retain uses an atomic compare-and-retry loop (`do {...} while (*word != u)`).
- **Evidence**: `if ((uVar1 & 0xfffe) == 0 || (uVar1 & 0xfffe) == 0xfffe) return;` and `if ((uVar1 & 0xffff) == 2) { sk_cap_release_cb; free; }`; retain `do { u=*w; if (((u^0xffffffff)&0xfffe)==0) return; } while (*w != u); *w = u+2;`.
- **Severity (hypothesis)**: informational — the kernel saturates (never wraps) the tag refcount, preventing double-free/UAF via refcount overflow; fail-closed.
- **Confidence**: high (explicit 0xfffe saturation checks).

## [sk] 00046694 sk_tb_dispatch — ~50-case TB (tightbeam) message dispatcher
- **Observation**: The TB dispatch core reads a message tag from the wire buffer and switches over ~50 tags, decoding per-record fields and dispatching each through the caller object's method table (mtab at *(obj+0x20)). Unrecognized tags take a fatal path (helper FUN_004b4358 + fatal strings 0x5ba347/0x5ba47e/0x5ba4bc). The decompiler could not fully settle types ("Type propagation algorithm not settling").
- **Evidence**: `sk_tb_tag(&tag, buf); mtab = *(obj+0x20); ... sk_x_004b4358(); sk_tb_var_w(mtab[8]+0x28, r); *(mtab[8]+0x20)=1;` — tag-switch with per-tag decode helpers and a noreturn abort on unknown tag.
- **Severity (hypothesis)**: informational — fail-closed dispatcher; unknown wire tags abort rather than falling through (defense-in-depth against malformed IPC).
- **Confidence**: medium (huge/partially-unsettled decompile, structural summary).

## [sk] 0004d1fc sk_reloc_apply — pointer-slide relocation across __DATA/__DATA_CONST
- **Observation**: Boot-time relocation applies the KASLR slide to every tagged pointer in a range, skipping any that fall inside the __DATA or __DATA_CONST segments when the config flag is set (sk_cfg_geo_c==1), and stopping at the 0xffffffff sentinel. Uses sk_ptr_fixup (0004d150) which reconstructs absolute addresses from the 42-bit tag/stride encoding.
- **Evidence**: `if (*(uint*)begin & 1) w=8; ... if (u==0xffffffff) return; sk_ptr_fixup(u, u&0xffffffffffffc000, w, -slide, slide);` and the __DATA (0x5bb23b)/__DATA_CONST (0x5bb242) bounds checks via sk_x_00051e5c.
- **Severity (hypothesis)**: informational — correct KASLR slide application; the skip-set is narrow (data-only), pointer targets are validated by fixup. No weakness observed.
- **Confidence**: medium.

## [sk] 0004ed48 sk_tb_ph_avail — TB placeholder resource availability gate
- **Observation**: The TB placeholder path validates at boot/alloc time that the placeholder resource region is non-empty (global cfg +0x78 != 0), aborting with the "TBPlaceholder resources could no.." panic (0x5bb783) otherwise. This is a single fail-closed availability gate before any placeholder use.
- **Evidence**: `u = sk_global_cfg(); if (*(ulong*)(u+0x78) != 0) return u; sk_panic(0x5bb783);` — noreturn panic on empty region.
- **Severity (hypothesis)**: informational — fail-closed resource init gate.
- **Confidence**: high (string-matched panic).

## [sk] 00013cfc/00013af0 sk_tss_alloc_slot / sk_tss_free_slot — per-thread storage slot allocator (bitmap, fail-closed)
- **Observation**: Per-thread storage (TSS) slots are tracked by a 64-bit bitmap at region+0x528; allocation finds the first free bit and marks it, panicking "TB_FATAL: no available per-thread key" when the bitmap saturates; free clears the bit, panicking on out-of-range/base-null. Uses a magic-constant division by 0x1b8 (slot stride) for index computation.
- **Evidence**: `uVar8 = LZCOUNT(...~bitmap...); if (bitmap != 0xffffffffffffffff && uVar8 < 3) { bitmap |= 1<<uVar8; return region + uVar8*0x1b8; } sk_printf("TB_FATAL: no available per-thread key");`; free `if (*(u64*)(base+0x528) & bit) { *(...) &= ~bit; }`.
- **Severity (hypothesis)**: informational — fail-closed slot exhaustion; no wrap/aliasing observed.
- **Confidence**: medium (bitmap math partially reconstructed at low confidence).

## [sk] 0001071c sk_mall_zone_init — embedded libmalloc zone bounds
- **Observation**: The boot libmalloc zone (DAT_006adfd8) is a 1 MiB region at [zone+0x8000, zone+0x100000) managed by a bitmap-based size-class freelist. Every alloc/free path validates the pointer is inside this window before touching the bitmap, and panics via "BUG IN LIBMALLOC" strings otherwise. The `sk_zone_contains` helper answers range checks; a DAT_006adfe0 flag widens the accepted window for madvise'd headers.
- **Evidence**: `if (z==0 || u<z+0x8000 || z+0x100000<=u) sk_fatal_printf("BUG IN LIBMALLOC: not MFM\n"); if ((ptr&0xf)!=0) sk_fatal_printf("BUG IN CLIENT OF LIBMALLOC\n");`.
- **Severity (hypothesis)**: informational — all libmalloc entry points bounds-check before bitmap/pointer deref; fail-closed.
- **Confidence**: medium.

## [sk] 0001485c/00013ee4 sk_tb_query / sk_ipc_send — cL4 IPC transport error handling
- **Observation**: The IPC send/query paths assert on every transport error with TB_ASSERT strings and SoftwareBreakpoint(1) noreturn traps ("TB_ASSERT: rcv_err == TB_ERROR_SUCCESS", "L4_ErrorCode err", "num_rcv_caps < TB_MAX", "payload_size < max"). The cap-list emitter (sk_ipc_setup) validates the cap count (<=4) and each cap's error code before use, calling CallSupervisor(1) per cap.
- **Evidence**: `if (n > 4) { sk_printf("TB_ASSERT: num_rcv_caps < TB_MAX"); brk#1 }`; per-cap `CallSupervisor(1); if ((v & 0xff) != 0) { TB_ASSERT L4_ErrorCode; brk }`.
- **Severity (hypothesis)**: informational — IPC transport is fail-closed on malformed/oversized messages; cap count bounded.
- **Confidence**: low (large state machine reconstructed at low confidence; structural summary).

## [sk] 000159dc/00015a44/00015ce4 sk_tb_transport_copy — transport-buffer copy bounds (TB_ASSERT fail-closed)
- **Observation**: The transport-buffer copy primitives (start-copy, region-copy, and src→dst copy) validate both source and destination ranges against each buffer's limit before any copy, and every failure path traps via SoftwareBreakpoint (noreturn) after printing a TB_ASSERT "start/end < transport buffer" banner. There is no silent truncation or clamp — an out-of-range copy is a fatal kernel trap.
- **Evidence**: `*(data)` computed from `base+pos`; `if (pos+len < pos) FUN_004b05e8();` overflow carry checks; `if (pos+len > limit) sk_puts(TB_ASSERT_END_TRANSPORT); SoftwareBreakpoint(1, 0x15e08);`. The copy itself is a single `FUN_00117cc4` (memcpy) with both ends range-checked.
- **Severity (hypothesis)**: informational — transport layer is fail-closed on buffer overflow; no clamp/truncate path.
- **Confidence**: medium (bounds logic reconstructed; canary checked).

## [sk] 00016d78/00016e1c sk_tb_message_receive/decode — kind-byte dispatch on untrusted message header
- **Observation**: The message receive/decode cores dispatch on a kind byte (1..4) taken from the inbound transport-buffer payload, and each kind performs a different action: kind 1 allocates a new physical transport and issues CallSupervisor(2); kind 2 copies into an existing transport cap; kind 3 releases a referenced object (FUN_000151c8); kind 4 copies into a growable cap. The kind byte is validated only against `bytes > 0x17` before the +0x10/-0x28 field reads.
- **Evidence**: `kb = *sbuf; if (2 < kb) { if (kb==3) FUN_000151c8(...); else if (kb==4) { if (0x17 < bytes) { ... } } } else if (kb==1) { ... } else if (kb==2) { ... }`. Alloc tags 0x103004032233d17 / 0x100004077774924.
- **Severity (hypothesis)**: low — a forged message kind byte could steer the kernel into object release/alloc paths; the surrounding cap-type checks (`*(char*)(cr+8)==1`/`==2`) and bounds traps (SoftwareBreakpoint 0x5519, 0x17110) mitigate.
- **Confidence**: low (huge function, "type propagation not settling" warning; structural reconstruction).

## [sk] 00019490/00019588/00019670/00019768 sk_tb_msg_encode/decode f32/f64 — NaN/inf payload rejection
- **Observation**: The f32/f64 message encode/decode entries explicitly reject NaN/inf bit patterns: encode returns error 6 when `(v & 0x7fffffff) > 0x7f7fffff` (f32) or `(v & 0x7fffffffffffffff) > 0x7fefffffffffffff` (f64), and decode returns error 7 on the same check. This prevents non-finite values from being serialized into the transport buffer.
- **Evidence**: `if (0x7f7fffff < (param_1 & 0x7fffffff)) return 6;` and decode `uVar5 = 0; if (0x7f7fffff < (uVar8 & 0x7fffffff)) uVar5 = 7; return uVar5;` (and the f64 twins with the wider masks). The `_chk` wrappers fatal on non-zero return.
- **Severity (hypothesis)**: informational — input validation rejects non-finite floats.
- **Confidence**: high (straightforward mask compares).

## [sk] 00028b14 sk_vas_alloc — VAS faulthandler dispatch table built via async event registration
- **Observation**: sk_vas_alloc allocates a 0x210-byte VAS faulthandler object and populates ~40 method-handler slots (attach, detach, kind, add_range, lookup, activate, complete, destroy, dump, register, map variants, move, swap, resize, state_set, clear, get, etc.) each registered through FUN_0004b520 (sk_dispatch_async), which wraps the handler code pointers in reference-counted async dispatch records. The dispatch targets are indirect-call resolved via Swift method tables (offset 4/8/0x20/0x28/0x38/0x60). Guest-facing VAS operations resolve a handler by region address and invoke the stored method pointer.
- **Evidence**: `desc[2] = (unsigned long)vas_fh_attach;` ... `puVar8[0x28] = ...` for all slots, each `sk_dispatch_async(record)`; `*puVar8 = _DAT_006ac260; _DAT_006ac260 = puVar8;` links the object into a global list under a lock (FUN_00118164/194). Bounds checks before every indirect call trap via SoftwareBreakpoint(0x5519, addr).
- **Severity (hypothesis)**: low — the faulthandler registry is a large indirect-call dispatch surface keyed by guest-supplied region addresses; handlers are validated/bounds-checked (SoftwareBreakpoint traps) and registered only via the controlled alloc path.
- **Confidence**: low (28b14 is a large structural transcription; method-table dispatch).

## [sk] 00028aa4/0002a784/0002bd34/0002cf20 VAS faulthandler range registration — address-window validation
- **Observation**: The faulthandler registry validates region lookups and containment against fixed 0x4000-aligned windows: sk_vas_contains_range checks `(param_2 - rec_base) < 0x4000` per active record; sk_vas_lookup_range/sk_vas_lookup_entry scan the record array (0x48-byte stride) matching a stored key, trapping on out-of-bounds via SoftwareBreakpoint(0x5519) rather than returning a bogus record. Removal (sk_vas_alloc's teardown) validates index against the active count before zeroing.
- **Evidence**: `if ((*(char*)(uVar3-0x28)==1) && ((ulong)(param_2 - *(long*)(uVar3-0x20)) < 0x4000)) return 1;` (28aa4); record scan `for (...uVar3+=0x48...) if (*(long*)(uVar3+0x18)==param_2) { invoke handler; }`; SoftwareBreakpoint(0x5519, 0x28b14/0x2a80c/0x2b1e8).
- **Severity (hypothesis)**: informational — range/bounds checks are present and fail-closed via kernel trap.
- **Confidence**: medium (bounds logic reconstructed from decompile).

## [sk] 0002e7c4 vas_fh_get_internal — faulthandler table growth with VAS abort on overflow
- **Observation**: The faulthandler entry table is grown by doubling (stride 0x58 = 11 words) with explicit capacity-overflow abort paths (`s__VAS_abort_in_function__s_at_lin_...`, noreturn) when the requested size wraps or exceeds bounds, and the new region is zero-filled via FUN_00117d68 before use. Entries are looked up by key (sk_vas_lookup, FUN_00028950) with a range check on the candidate record.
- **Evidence**: `if (local_f0 < local_100) FUN_004afae4(s__VAS_abort...);` (capacity >= count); `if (uVar17 < local_f0) FUN_004afae4(...005ae7de);` (doubling overflow); zero-fill loop `FUN_00117d68(uVar3,0,0x58,remaining)`; SoftwareBreakpoint(0x5519, 0x2eda0) on table bounds.
- **Severity (hypothesis)**: informational — table growth is fail-closed on overflow, no silent wraparound.
- **Confidence**: low (large function; VAS abort strings string-matched).

## [sk] manifest cross-tree conflict — SK05 addresses assigned to TXM region files
- **Observation**: Seven addresses in the SK05 batch (000262c4, 000268a0, 000268d0, 00027614, 00028a78, 0002b5e8, 0002bdb8) are marked decompiled in the manifest pointing at osfmk/arm64/txm/*.c with txm_* names, but they are cL4 Secure-Kernel functions (tightbeam release/method-table resolvers, sk_lock_and_alloc, VAS lookup/record-fill) faithfully reconstructed in osfmk/arm64/sk/sk_slice_05.c. The txm entries appear to be a misassignment (overlapping address ranges between the SK and TXM batch plans).
- **Evidence**: manifest.json entries: `000268a0 -> txm_region_entry.c: txm_data_dac8`, `00027614 -> txm_region_runtime.c: txm_obj_free`, `00028a78 -> txm_region_runtime.c: txm_slab_alloc_0x1000`, etc. — none of which are plausible names for the tightbeam method-table resolver (000268a0 = offset-8 Swift witness resolver) or the VAS lock-and-alloc (00027614).
- **Severity (hypothesis)**: informational — manifest bookkeeping; the SK functions are decompiled in sk_slice_05.c but the entries point to unrelated txm files, so a downstream audit would misattribute them.
- **Confidence**: high (addresses verified in sk_slice_05.c with English bodies).

## [sk] 0016e000-0017fff8 StackshotConclaveSupport — guest stackshot serialization surface (SkWave3 tail)
- **Observation**: The whole 0x16e000-0x17fff8 region is the StackshotConclaveSupport service: guest stackshot capture (16e558/16ea28), ASID/text-layout binding (16f4ec/16f89c), and the crash-backtrace IPC surface (getConclaveCrashBacktrace 173be8, takeConclaveCrash 173644/175d08, getCrashBuffer 176914, getAddressSpaceInfo 17e8d0, runStackshot/runStackshotRedacted 17fdd8). It serializes guest-supplied records via a tagged byte-stream (tag-1/2/3 values) into the kernel scratch array (DAT_00657778/88/90/98) and hashes them (FUN_00025704).
- **Evidence**: String anchors throughout: s_StackshotConclaveSupport__* (005ca74a..005cae6b), s_getConclaveCrashBacktrace_scid___005cb960, s_takeConclaveCrash_scids___005cb540, s_getCrashBuffer___005cbb90, s_runStackshot_threw_an_unexpected_005cbed0; hash constants 0xeb1a02bf914012ba (16fb80) and 0xdeadcafebeefbabe (177630); fatal path FUN_001afa84(...,"StackshotConclaveSupport...",0x37,2,line,0).
- **Severity (hypothesis)**: informational — this is the guest->kernel crash-dump data path; the serialization length/size helpers (17d29c/17d380/17d3e4/17d850/17d22c) are saturated with SCARRY8 overflow checks that trap via SoftwareBreakpoint(1, ...) rather than wrapping, so the buffer accounting is fail-closed on overflow.
- **Confidence**: high (string anchors + consistent hash/format machinery).

## [sk] 0017d29c/0017d850/0017e8d0 size-accumulators — overflow fail-closed on all serialized-length math
- **Observation**: The serialized-record size computations add per-record widths with explicit carry detection and trap (SoftwareBreakpoint(1, 0x17d2f0/0x17d324/.../0x17da8c)) whenever the 64-bit accumulator overflows, rather than allowing a wraparound that could under-allocate the output buffer.
- **Evidence**: `bVar5 = SCARRY8(lVar6, lVar2 + uVar9); lVar6 = lVar6 + lVar2 + uVar9; if (bVar5) SoftwareBreakpoint(1, 0x17d2f0);` (17d29c); the same SCARRY8+SoftwareBreakpoint pattern at 0x17d958/17da20/17da48..17da8c in 17d850; size pass in 17e8d0 uses lVar14/lVar11 with SCARRY8 guards.
- **Severity (hypothesis)**: informational — overflow in size math would otherwise be a classic buffer-overrun primitive (mis-sized allocation); the explicit carry traps close it.
- **Confidence**: high (SCARRY8 macros + SoftwareBreakpoint on every accumulation).

## [sk] 00173368/00173be8 crash-frame bitmap walk — LZCOUNT bit-reverse iteration of scid bitmap
- **Observation**: The crash collector walks a guest-scid bitmap by bit-reversing the word (LZCOUNT of the byte-swapped value) to enumerate set bits in address order, dereferencing `puVar23[6] + LZCOUNT(...)*8 + lVar33*0x200` to fetch each scid's crash record. Every dereference re-validates the frame/crash object via the vtable resolve path (177084/1773c8) and traps on a null/abnormal result.
- **Evidence**: `uVar17 = LZCOUNT(uVar17 >> 0x20 | uVar17 << 0x20); puVar39 = *(uint64_t**)(puVar23[6] + uVar17*8 + lVar33*0x200);` (173be8); bitmap bounds `if ((*(ulong*)(puVar18[(uVar17>>6)+7] >> (uVar17&0x3f) & 1) != 0)` in the dedup hash (173be8/17b588).
- **Severity (hypothesis)**: low — the scid bitmap iteration and per-entry lookups are bounds-checked and trap on invalid indices (SoftwareBreakpoint 0x5519/1 at 173a80/173500/175c70..175c98); a mis-typed guest scid cannot walk past the bitmap.
- **Confidence**: low (173be8 is a 1000-line structural reconstruction; LZCOUNT usage inferred from the bit-twiddle block).

## [sk] 0017e8d0/0017fdd8 dispatch selectors — selector-hash switch is fail-closed on unknown tags
- **Observation**: The IPC-stack/run-stackshot readers switch on a 64-bit selector hash (FUN_00021904) rather than a trusted integer id, mapping to a small set of known values (0x5a2e2d0c3bc3e9cd, 0x784a6e3b19f9800a, -0x7e823a91a48e8fae, -0x3de3ed447c24c24b in 178c0c; 0x7e2ceb7445c093c5, 0x6282921a0bf58ff1, 0x7e4f1803cc77363 in 177a34). Any unknown hash triggers a fatal ("TB_FATAL: unrecognized selector" 005ba347 / "Fatal error" 005cbee0/005cbd40) rather than dispatching to a default.
- **Evidence**: `if (lVar1 != 0x7e2ceb7445c093c5) { ... FUN_001afa84(s_Fatal_error_005accd0,...,0x4db,0); }` (17770c); `default: FUN_00118b28("TB_FATAL: unrecognized selector"); SoftwareBreakpoint(1, 0x1717d8)` (1713f4).
- **Severity (hypothesis)**: informational — hash-based dispatch is fail-closed; an unrecognized selector cannot reach a wrong handler.
- **Confidence**: high (selector hash values + fatal string anchors).

## [sk] 0017e8d0 getAddressSpaceInfo/getIPCStackEntry — cpu-bound, capability-validated reads
- **Observation**: The address-space-info and IPC-stack readers are bound to the current cpu (FUN_0005b89c) and validate the guest's capability before reading (16fe34 rejects a cpu mismatch with error 1; 16e468/16e3a0 reject a non-local proxy with error 2). The resolved capability token (16f1b8) is range-checked against the region table before use.
- **Evidence**: `if (param_1 != lVar3) { FUN_00046304(param_3,1); return; }` (16fe34 cpu check); `if (target != _DAT_006bff08) { FUN_00118b94("...Proxy..."); FUN_00046304(&rec,2); }` (16e3a0); region-table bounds SoftwareBreakpoint(0x5519, 0x16f278) in 16f1b8.
- **Severity (hypothesis)**: low — the guest-facing read path enforces cpu binding and proxy-identity checks, limiting cross-context data disclosure to the local (current-cpu) guest.
- **Confidence**: medium (identity/cpu checks reconstructed; DAT_006bff08 proxy anchor).

## [sk] 0017e3a0/0017f9a4 build/begin-hash validation — stream integrity checks before parse
- **Observation**: Several readers validate a fixed hash at the start of the serialized stream (FUN_00021904 == 0x4159b862aecab4d9 in 178348 "begin", 0x6f9215ea767e2712/0x752da4ce868ca6dd/0x672c65b98d5d43f7 in 17884c/1789b8/178dcc) before parsing guest data; a mismatch is fatal, not ignored.
- **Evidence**: `if (FUN_00021904() == 0x4159b862aecab4d9) return; FUN_001afa84(s_Fatal_error_005accd0,...,0x519,0);` (178348).
- **Severity (hypothesis)**: informational — the tagged stream format is integrity-checked at well-defined boundaries; malformed input aborts rather than being misparsed.
- **Confidence**: high (fixed hash compares + noreturn fatal).

## [sk] 0002ee90-0002f780 VAS op-dispatch — slot-ring result code bounds-checked fail-closed
- **Observation**: The six VAS op-dispatch wrappers reserve a slot in a per-VAS ring (0x30-byte slots, count at slots+0x1f0, write index +0x1f8, base +0x200), stamp a per-op type tag, run the backend vtable method under the global VM lock, then write the op result code into the slot. Every path that stores a result validates it first: any code with low byte not in {0,1..5} is aborted via `sk_vas_abort("unknown vas return code 0x%x")` (FUN_004afae4) before the value is packed.
- **Evidence**: `sk_vas_check_result(code)` guards `slot_res_store()` in sk_slice_06_frag_opdispatch.c; bounds of the ring slot `slot < ring || ring+count*6 < slot+6 || slot+6 < slot` trap via SoftwareBreakpoint(0x5519, addr); the ring-region bounds check (`limit < slots+0x210 || slots+0x210 < slots || slots < slots_min`) is validated in `sk_vas_slots()`.
- **Severity (hypothesis)**: informational — an invalid backend return cannot be recorded into a VAS slot (would corrupt the op log); the encoding is checked before write.
- **Confidence**: high (result-code range check + SoftwareBreakpoint traps on every store path).

## [sk] 0002fb88/0002ff48 cap-split & span-map — bounds-guarded span carve
- **Observation**: `sk_cap_split` (2fb88) carves a chunk out of a span's child list and maps the child region. Every pointer deref of the child list (chunk+8..0xb) and the destination page range is guarded: the carve validates `bsz-off < code+off` and `b-*chunk > code` and traps via SoftwareBreakpoint(0x5519,0x2fe54) on overflow; the map result is checked non-zero before committing. `sk_vas_span_map2` (2ff48) re-validates the target PTEs and range before writing page-table entries.
- **Evidence**: `sk_cap_split` (frag_capsplit.c): `if (bsz - off < (code + off)) SK_ASRT_PANIC(0x2fe54);` plus the `d2==0 -> sk_boot_fatal2()` map-failure trap; span_map2 (frag_spanmap.c) uses `SK_ASRT_PANIC(0x30460)` on every PTE-write range violation.
- **Severity (hypothesis)**: low — the span carve and page-table writes are bounds-checked and fail-closed on overflow, so a crafted span/offset cannot overrun the destination region.
- **Confidence**: medium (carve arithmetic faithfully transcribed; offsets page-aligned by the 0x3fff checks).

## [sk] 00037fb8/000380b4/00038184 Freezer span allocator — size checks fail-closed, destroy validates backing
- **Observation**: The "Freezer" allocator (guest-span bulk allocator) validates sizes before acting: `sk_freezer_alloc` requires size 0x4000-aligned (traps SoftwareBreakpoint 0x5519/0x380b4 on misalignment via `lStack_30 + (size & ~0x3fff)`), `sk_freezer_bump` traps "Freezer bump size %zu exceeds reserved size %zu" if the requested bump exceeds the reserved capacity, and `sk_freezer_destroy` only releases a span whose backing store is non-null, else traps "Freezer failed to destroy a backing".
- **Evidence**: frag_freezer.c: `if (param_2 <= param_1[1])` gate in sk_freezer_bump with the exceeds abort; destroy checks `param_1[3]==0` -> abort; the `(param_1 & 0x3fff) != 0` alignment path in sk_freezer_alloc.
- **Severity (hypothesis)**: low — the guest-facing bulk span allocator enforces alignment and reserved-size limits, so an oversized/misaligned request cannot cause an undersized mapping.
- **Confidence**: high (three Freezer error strings resolved from the string table + size/alignment guards).

## [sk] 00034bd8/00034d5c VAS lock token — acquire/release counter paired, no use-after-unlock
- **Observation**: The VAS object lock is a token mutex: `sk_vas_lock_acquire` (34bd8) returns a {flags, counter} token and marks the lock held, `sk_vas_lock_release` (34d5c) validates the token counter equals the held counter and the held-flag matches before clearing. Every acquire is paired with a release; the release path double-checks `param_3+1 == *(lock+0x18)` (counter) before unlocking.
- **Evidence**: frag_lock.c: `if (param_3 + 1 != *(long*)(lock+0x18)) sk_vas_abort(...)` in sk_vas_lock_release; `sk_vas_locked` (34ba4) compares the per-cpu base against the lock owner.
- **Severity (hypothesis)**: informational — the token pairing prevents a stale/misordered release from unlocking the wrong VAS lock generation.
- **Confidence**: medium (token structure reconstructed; counter comparison explicit).

## [ringminus1] 00038220 sk_vspace_read — bounds-checked copy-out from a mapped region
- **Observation**: The cL4 vspace copy-out primitive resolves the span covering the source address and walks its leaf pages (sk_vspace_map_phys) in 16 KiB increments, verifying the requested window stays within the span and that consecutive pages are physically contiguous (`off + base_ptr == next_page`). A non-contiguous or out-of-range read aborts rather than returning a partial/forged buffer.
- **Evidence**: `avail = (span+8 - addr) + span+0x10; if (avail <= want) want = avail;` then per-16K loop `if ((sk_vspace_map_phys(span, addr+off, &pg) & 0xff) || off + local[10] != pg) break;` returning 0x9580001 on a missing span.
- **Severity (hypothesis)**: low — bounds/contiguity enforcement on the guest→kernel read path; a bug here could allow reading across an unmapped gap, but the per-page walk closes it.
- **Confidence**: medium

## [ringminus1] 0003c56c sk_vspace_region_create — fail-closed flag/alignment validation on region factory
- **Observation**: The VSpace region factory rejects invalid flag/alignment combinations with specific error codes before allocating or mapping: region-type table lookup must succeed, alignment must be <0x24, the requested window must be in-range, alignment bits must not be set, and a covering free span must exist. Many combinations (0x3cf/0x3d1/0x3d3/0x3d7/0x3dc/0x3e2/0x3e9/0x3ec/0x3ee/0x3f3/0x3f6/0x3f8/0x3fc..0x408) return errors; an out-of-window request yields 0x44c0003.
- **Evidence**: dense `if/else` tree testing `req_flags` bits (0x9/0xa/0xd/0x4/0xf/0xe/0x13/0x10/0x16/0x1a/0x5/0xc) against the region descriptor; `FUN_000559b8(rtype)` type-table lookup; final `sk_vspace_find_region` + `sk_span_split_simple` to carve the exact window.
- **Severity (hypothesis)**: informational — the factory only maps windows it validated; no weak path observed, but the complexity is a review surface.
- **Confidence**: medium

## [ringminus1] 0003ee4c / 0003f41c sk_vspace_span_split / sk_vspace_span_merge — buffer-list relink invariants
- **Observation**: Span split/merge relink the vspace's secondary buffer free-list only after bounds-checking each token (`tok + 0x20 < tok` faults) and the list count byte (<4). The split transfers the metadata via sk_span_encode_meta and re-inserts the second span into the AVL tree, so the two result spans remain consistent with the tree and the free lists.
- **Evidence**: `if (nb2 < nb) SK_FATAL();` / `if (oldbuf + 4 < oldbuf) SK_FATAL();` / `if (2 < cc) SK_ABORT(...)`; `sk_span_tree_insert_caller(rec, nb)` after the split.
- **Severity (hypothesis)**: low — the split/merge keep the span tree and free-list consistent; a missed relink would corrupt the allocator (availability/memory-corruption), but each step is bounds-checked.
- **Confidence**: medium

## [ringminus1] 00039094 sk_faulf_dispatch — fault dispatch routing by span permission bits
- **Observation**: The fault handler routes a guest fault to the COW / managed / frozen-page path based on the span's flag bits (0x12/0x13/0xc/0x14/0x15), after resolving the span via FUN_00045a68 and requiring the span's owner to be the faulting vspace. A fault whose span lacks the two-stage bit returns an error rather than mapping through the wrong path. The COW path calls the span's fault callback only when the span exposes one, and a callback result of 2/4 (not 0) still requires the "canexec" bit.
- **Evidence**: `if (*(word_t *)(spanobj + 0x50) == vspace)` gate; callback `(*(word_t (**)(word_t,word_t,word_t,word_t *))(sp + 0x30))(...)` with `crr==2/4` handling and `(f >> 4 & 1)` canexec check before re-mapping.
- **Severity (hypothesis)**: medium — the fault path's authorization depends on the span flag bits and callback result; a fault routed to COW on a non-COW span would remap shared pages, so the flag gates are the security boundary here.
- **Confidence**: low (many paths collapsed by the decompiler; flags partly inferred)

## [ringminus1] 00042abc sk_vspace_paddr_lookup — vaddr→paddr translation with index bounds
- **Observation**: Virtual→physical translation indexes the shadow-space level slot array only after verifying `idx < slot[2]` (the per-level entry count); an out-of-range index aborts rather than returning an OOB physical address. For the self-referential vspace it additionally walks a small (6-entry) LIFO of remapped entries to return the real PTE.
- **Evidence**: `if (idx < (word_t)slot[2]) { ... return pa; } FUN_004afae4("VAS abort");` with the 6-entry LIFO (`(i/6)*-0x60`) match on `+0x90`.
- **Severity (hypothesis)**: informational — the level-index bounds prevent translating through an unallocated level slot.
- **Confidence**: medium

## [ringminus1] 00042ed0 sk_vspace_lookup_phys — preemption-queue drain ordering
- **Observation**: The physical-address lookup shares a 6-entry ring with the frozen-page path and drains pending remap work after a preempted result (error 5): it calls FUN_00042ed0 recursively, issues CallSupervisor(4) until the remap lands, then invalidates the cap. The entry is recorded in the ring (`+0x88` base, index mod 6) and the count capped by `%6`.
- **Evidence**: `do { CallSupervisor(4); } while (c == 1);` after `(*(...+0x10))(vs+0xb0, pa)`; `*(word_t*)(rec6+0xf0) = (... + 1U) % 6;` and `if (*(word_t*)(rec6+0xe8) == 0) goto done;`.
- **Severity (hypothesis)**: low — the mod-6 ring and preemption loop keep the remap queue bounded and drained; a stall there would be availability-only.
- **Confidence**: low

## [ringminus1] 0003f6c8 / 00040870 sk_span_tree_remove / sk_span_tree_insert — AVL height/extent invariants
- **Observation**: The span tree is a self-balancing AVL with per-node height (byte +0x24) and subtree extent (word +0x68) maintained on insert/remove. The extent is recomputed as the max of the children's extents and the node's own size; remove rebalances via left/right rotations and re-reads the root after each recursion.
- **Evidence**: insert sets `*(node+0x68) = max(child extents, own size)`; remove computes `lh = (l?*(l+0x24)+1:0)` and calls `sk_span_tree_rebalance(root, bal2 + bal)` with `bal2 = ~rh`; every tree node pointer is bounds-checked (`node+0xb0 < node` faults).
- **Severity (hypothesis)**: informational — a height/extent inconsistency could cause the extent-based free-space search (sk_span_tree_find_free) to skip or double-report a free window, but no invariant break observed.
- **Confidence**: medium

## [Sk09] 0x0004eec0 / 0x0004f258 sk_tb_ph_dump / sk_tb_ph_dump2 — unchecked resource kind + offset arithmetic
- **Observation**: The tbplaceholder serializer validates the resource kind (`kind > 0x1c` panics) but then multiplies a 32-bit packed size field by 0x40 and adds it to the region base with only a `size < region_size` bound check, after a separate `>>2`-overflow guard on the same field.
- **Evidence**: `sk_tb_ph_dump` reads the 4-byte size at `elem+0x108/0x10c`, panics if `*(elem+0x10f)>>2 != 0` (overflow), then `sz *= 0x40; if (sz < region[1]) off = sz + region[0] else 0`. Same pattern in `sk_tb_ph_dump2` (stride 0x287) and `sk_tb_ph_addr2` (0x4f890). Region bounds come from the caller-supplied `long *param_3 = {base,size}`.
- **Severity (hypothesis)**: medium — a corrupted tbplaceholder descriptor with a valid top-2-bits kind but an oversized packed size could compute an out-of-range region offset; the `size < region[1]` check bounds the final offset against the caller-provided region, so impact is confined to that region's span.
- **Confidence**: medium

## [Sk09] 0x000508e8 sk_tb_ph_map_subgraph — device-tree subgraph mapping without origin validation
- **Observation**: The subgraph mapper derives the mapping base as `range.lo + (packed idx * 0x40)` with only a `range.hi <= idx<<6` check deciding whether to zero the base, and maps the full aligned `size` via the ep object vtable `+0x30` (frame alloc) / `+0x28` (map) dispatch.
- **Evidence**: `u10 = idx packed; region = range.lo + u10*0x40; if (range.hi <= u10<<6) region = 0; sk_region_map_frames(region, block, owner, u13);` then `((*(fn))(owner+8))(block, kind)`. Frame alloc via `ep.hi+0x30` (0x1800 size). Errors route to `s_Failed_to_map_memory_for_subgrap` panic / `SoftwareBreakpoint(0x5519,0x50c84)`.
- **Severity (hypothesis)**: medium — an out-of-range packed index yields `region = 0` (mapping base 0) rather than failing; whether that is reachable depends on the boot descriptor integrity (GL1 trust boundary input).
- **Confidence**: medium

## [Sk09] 0x00054624 sk_cfg_init — config bootstrap writes many writable image globals from boot params
- **Observation**: Parses a 0x400-byte boot-parameter table (`lVar3` stride 0x10) and writes each tag's value into the `DAT_006b03xx` / `0x6b03xx` config globals, including a code-flag byte (`DAT_006b0348`), without a bounds check beyond `(lVar5 - 1) < 0x2b` on the tag id.
- **Evidence**: switch on `lVar5` with 40+ cases writing distinct `_DAT_006b03xx` slots; `DAT_006b0348 = (uVar4 == 0)`, `_DAT_006b0440 = param_1`, `lRam_0064ccd0 = param_1`. Unknown/default tags write `_DAT_006b0350`. Loop runs 0x400/0x10 = 64 iterations.
- **Severity (hypothesis)**: informational — tag ids are bounded to <0x2c and each writes a fixed global; no linear write derived from attacker-controlled length. Boot-time only.
- **Confidence**: low

## [ringminus1] 0x55454-0x5ac2c sk_svc_dispatch_* / sk_svc_class_*_build — redacted syscall-class descriptors; retry-on-return-1 SVC stubs
- **Observation**: The entire slice is the cL4 syscall/service-interface dispatch layer. All per-class descriptor tables (classes 1, 2, 0x100000001..0x900000001) carry the same name string "Redacted" (0x5bbf32) — Apple strips the service identifiers from the shipped kernel image, and the two per-class data tables (DAT_004bcd10 etc.) are all-zero. The descriptor builders place PAC-authenticated method pointers (inline LAB_ stubs + SVC wrappers) and a per-class dispatch code pointer (0x64d198, 0x64d260, ...) into a caller-provided struct without validating the destination.
- **Evidence**: `s_Redacted_005bbf32` read at ram:0x5bbf32 = "Redacted\0L4_Type"; builders write `*(word_t*)(param_2 + off) = <pacia'd ptr>` for ~60 offsets per class; dispatch code pointers 0x64d198/0x64d260/0x64d330/...; SVC wrappers do `do { CallSupervisor(0); } while (x0==1)` retry loop.
- **Severity (hypothesis)**: low — the descriptor builders write into a caller-supplied buffer with no bounds/ownership check, but they are internal kernel-invoked paths; the redacted names and zeroed tables indicate deliberate identifier stripping rather than a runtime weakness.
- **Confidence**: high (string + structure verified)

## [ringminus1] 0x5ab94 sk_xrt_runflags_check — runflag capability gate with length panic
- **Observation**: The `xrt__runflags` capability check reads the runflags word and tests the bit selected by param_2. If the runflags symbol's stored length is shorter than the requested offset, it panics with "xrt runflag metadata not long enough" (noreturn). A Software Breakpoint 0x5519 guards the pointer-range check.
- **Evidence**: `FUN_0006562c("xrt__runflags",&symval)`; `if (symval < (param_1 & 0xffffffff)) FUN_0005b190(msg,...)`; bit test `(*p >> (param_2 & 0x1f)) & 1` returns 1/2.
- **Severity (hypothesis)**: informational — fail-closed capability bit gate; no weak path observed.
- **Confidence**: medium

## [ringminus1] 0x5ac2c sk_sec_transition_allowed — sec_transition capability gate
- **Observation**: Whether a secure (Sec) transition is allowed is gated on the singleton flag byte (0x1b8), the transition-in-progress bit at FUN_00054610(), and the "sec_transition" symbol. The symbol value is compared (thunk_FUN_00114e50) against _DAT_005cf0f4; a non-matching value forces the runflags bit clear path.
- **Evidence**: `FUN_0006562c("sec_transition",&val)`; `thunk_FUN_00114e50(sym,&_DAT_005cf0f4,val)==0`; `sk_xrt_runflags_check(2,1)` result drives the allow/deny decision.
- **Severity (hypothesis)**: medium — the transition-gate decision is an authorization boundary; a mis-gated comparison could allow or deny Sec transitions. Comparison target _DAT_005cf0f4 is opaque (out of slice) and worth auditing against the canonical string.
- **Confidence**: low (comparison semantics partly inferred)

## [Sk12] 0x00060728 sk_kernel_init — dispatch-table no-handler panic + "Security assertion failed" gate
- **Observation**: The per-CPU kernel init / main dispatch-loop entry resolves the dispatch selector into the 0x6b26d8 table (3 slots, via `sk_percpu_tbl`). If a slot's handler pointer is null it panics "No handler set for entry %04hh"; if a handler ever returns it panics "Unexpected thread exit". A separate selector check masks `1<<(uvar24&0x3f)` against `0x40000002c000c000` and, for an invalid selector, calls `FUN_001150E0` with the string "Security assertion failed: %s %f" (a hard noreturn panic), so an unrecognized dispatch kind cannot fall through to arbitrary code.
- **Evidence**: `sk_percpu_tbl(0x6b26d8,1,2)`; `if (*entry==0) name="No handler set for entry %04hh" else { fn=*entry; uvar17=fn(harg,state,kind); ... name="Unexpected thread exit %04hhX"; } sk_ec_switch(0,name)`. Selector gate: `if ((1ULL<<(uvar24&0x3f)) & 0x40000002c000c000ULL)==0 { if (uvar24!=0) goto bad; uvar24=kind&0xff } else uvar24=0`, and the bad path is `FUN_001150E0("Security assertion failed: %s %f")`.
- **Severity (hypothesis)**: medium — the dispatch table is per-CPU and writable via `sk_dt_set` (0x6290c); a corrupted table that lost a handler pointer would panic the kernel (DoS), but the security-assertion path fail-closes rather than mis-dispatching.
- **Confidence**: high (string + structure verified)

## [Sk12] 0x00062474 sk_thread_state_dump — MTE tag-check fault (esr&0x3f==0x11) and apparent stack-overflow detection
- **Observation**: The panic/thread-state dumper special-cases ESR class 0x11 (Synchronous Tag Check Fault, i.e. an MTE violation) with a dedicated "Synchronous Tag Check Fault" banner, and separately flags an apparent kernel stack overflow when the fault address falls inside the thread's stack window `[*(tcb+0x130), *(tcb+0x130)+0x4000)`. The FAR/ESR are printed in the dump.
- **Evidence**: `if ((esr & 0x3f) == 0x11) sk_print16(sink, "Synchronous Tag Check Fault", 0x1c, 1)`; `if ((*(tcb+0x130) <= far) && (far < *(tcb+0x130)+0x4000)) sk_printf(sink, "Apparent stack overflow by 0x%04x")`.
- **Severity (hypothesis)**: medium — MTE tag violations are an intended fault class; explicit detection shows the kernel expects and records memory-tagging faults, consistent with cL4 running with MTE enabled. No weakness, but confirms the fault surface.
- **Confidence**: high (string + bit decode verified)

## [Sk12] 0x00064108 sk_exc_setup — exception-handling endpoint install + whole-thread walk
- **Observation**: Installs the kernel exception endpoint once (`*(singleton+0x48)`, panics "exception handling can only be i..." if already set), sets up the shared 0x6ad910 endpoint, then walks every thread (thread-list iterator FUN_000533EC / FUN_004B75E4) delivering the "Set exception handler" request via CallSupervisor(0). If any thread's delivery reports an error (`rsp & 0xff != 0`) it faults. Allocation failure panics "failed to allocate exception endpoint".
- **Evidence**: `*(s+0x48)=sk_g_exc_endpoint`; `sk_ep_setup(0x6ad910, ep, buf, cfg)`; `th=sk_g_handler_list; thiter=sk_h_000533EC(); ... do { CallSupervisor(0); ... } while (tstate==1)`; per-thread `if ((rsp & 0xff)!=0) { FUN_004B7594(...); goto exc_panic; }`.
- **Severity (hypothesis)**: low — single-install enforced; per-thread delivery failure panics (fail-closed). The all-thread walk is a boot/init-time operation.
- **Confidence**: medium

## [Sk12] 0x00062a48 sk_tbplace_get — tightbeam placeholder resource lookup with "No resource" panic
- **Observation**: Resolves a "tightbeam placeholder" resource by iterating the boot resource iterator (FUN_0004EB44/4EB4C/4ECF0) for a matching kind (0x11/0x13) and reading a packed word from a fixed offset (0, 0xc, or 4 words by selector). If no resource matches it panics "No tightbeam placeholder resource" (noreturn). The word offset selection depends on the caller's selector without a length check on the descriptor.
- **Evidence**: `res=(uint16_t*)FUN_0004E7B8(uvar12, kind_sel)`; `p = (sel!=2)? res+0xc : res; p2=(sel!=1)?p:res; p3=(sel<0x50)?p2:res+4; word = packed 8-byte read of *p3`; no match → `sk_ec_switch(0,"No tighbeam placeholder resource")`.
- **Severity (hypothesis)**: low — descriptor content is boot-image (GL1 trust-boundary) input; a malformed descriptor with a valid kind could be read at an unintended offset, but the result is only used to seed config, and no-match panics rather than proceeding.
- **Confidence**: medium

## [Sk14] 0x0006bcf8 sk_ipmm_frame_alloc — launcher IPMM physical-frame allocator (guest memory boundary)
- **Observation**: The launcher IPMM hands physical frames to exclaves. The allocation type (param_5) is validated against `(param_5 & 0xfffffffd) != 0` → panic "unexpected PMM allocation type", and type 5 returns error 0x107 (fail-closed). Frame selection is bounded to known memory types (4, 6, 7, 8, 0x11); the freelist-recycle path pops `g_freelist_base + g_freelist_used*0x40` after decrementing `g_freelist_used` (index validated non-zero). The cbootinfo arena is bumped only after checking `g_cboot_alloc_limit` (calls FUN_0006b7e0 to extend, else panics "ipmm: Operation Invalid: Wrong"). Success creates the untyped frame via SVC 0 with `{type, frame, param_4}` staged in the tpidrro_el0 block.
- **Evidence**: `if ((param_5 & 0xfffffffd) != 0) FUN_0005b190(0, s_unexpected_PMM_allocation_type)`; `if (param_3 == 5) return 0x107`; `if ((mtype==0x11) && (g_freelist_used!=0)) { g_freelist_used -= 1; frame = g_freelist_base + g_freelist_used*0x40; }`; arena `if (g_cboot_alloc_limit < base+0x4000) { FUN_0006b7e0(); if (g_cboot_alloc_limit < base+0x4000) goto funnel_end; }`; SVC frame `*puVar2=param_2&0xffffffff; puVar2[1]=uVar5; puVar2[2]=param_4; CallSupervisor(0)`.
- **Severity (hypothesis)**: medium — this is the physical-memory allocation boundary between the launcher and exclaves; the type gate and arena-exhaustion panics are fail-closed, but the tpidrro_el0 SVC frame and freelist-recycle state are worth auditing (a corrupted freelist could hand out an already-allocated frame).
- **Confidence**: medium

## [Sk14] 0x0006c5cc sk_cbootinfo_parse — boot-info capability-array parsing (GL1 trust boundary)
- **Observation**: Parses the launcher cbootinfo cap array (a linked list of pages) and records untyped regions, DART/Table SIDs, TEXT/DATA segment caps, and the roottask slide. Registry writes are bounds-gated: `if (0x3f < g_untyped_scan_idx) FUN_004b8288()` (region overflow), `if (0x1f < g_dart_count) / g_dart_table_count` panic. The __TEXT/__DATA segment slide uses FUN_00051e5c on the Mach-O header; a missing segment leaves the roottask slide unset (logged "Roottask slide is 0x.."). Malformed/missing entries route to the FUN_004b8xxx abort funnel rather than proceeding.
- **Evidence**: `if (0x3f < g_untyped_scan_idx) FUN_004b8288(); goto err_funnel`; `if (0x1f < g_dart_count) goto err_funnel_h`; `if (0x1f < g_dart_table_count) goto err_funnel_i`; `FUN_00118b28(s_Roottask_slide_is_0x_llx_005a8b16)`.
- **Severity (hypothesis)**: medium — boot-info is external (GL1 trust-boundary) input; the population of the untyped-region and DART tables is bounds-checked, so a hostile cbootinfo array is constrained, but the segment-slide/roottask computation and the tpidrro SVC replication (type 1 untyped) are the highest-value attack surface here and merit focused review.
- **Confidence**: medium

## [Sk14] 0x0006b7e0 sk_ipmm_freelist_init — launcher freelist + zero-frame cap creation
- **Observation**: On IPMM re-entry, builds the launcher freelist cap (selector 0x940) and the zero-frame cap (selector 0x1808) via the cap-create IPC dispatch `(**(code**)(arena.hi+0x30))(arena.lo, sel, msg, &outcap, 0, 0)`. The vtable-backed `+8` method seeds the freelist, and `+0x28` maps frames to zero (g_zero_frames_active set). Any failure aborts with an "IPMM abort in function" panic. Notably it snapshots the 26-entry launcher cap table (FUN_0006cea4) into 0x6b2848, which FUN_0006bcf8 later indexes by memory-type without a direct bounds check (reliance on the type-gate in the caller).
- **Evidence**: `cVar4 = op(arena.lo, 0x940, &local_a0, &g_freelist_handle, 0, 0)`; `if (g_freelist_vtable==0) FUN_00054354(); (**(code**)(g_freelist_vtable+8))(g_freelist_handle, 0x6b2800)`; zero-frame `op(arena.lo, 0x1808, &local_a0, &g_zero_handle, 0, 0)`; `(**(code**)(g_zero_vtable+0x28))(g_zero_handle, 0, frame_cap)`.
- **Severity (hypothesis)**: medium — zero-mapping frames is a confidentiality control (exclave memory is zeroed before handoff); a failure aborts rather than silently returning unzeroed memory (fail-closed), which is good, but the cap-create message globals (DAT_004bee90/98/a0/a8/b0/b8) are opaque and worth cross-checking.
- **Confidence**: medium

## [Sk14] 0x0006c454 sk_vspace_table_remove — vspace client-list unlink integrity (fail-closed)
- **Observation**: Removes the current client from the vspace-table list with explicit doubly-linked-list integrity checks before unlinking; corruption panics via FUN_001150e0 ("Bad link elm: p->next->prev != el" / "p->prev->next != el") and a missing node panics "expected client to be in list". The head-removal path flushes via FUN_00012568. An unarmed table aborts "vspace table not ready yet".
- **Evidence**: `if (*(uint64_t**)(next+0x28) != (uint64_t*)((uint8_t*)p+0x20)) FUN_001150e0(s_Bad_link_elm__p_next_005bf1e6)`; `if ((uint16_t*)**(uint64_t**)((uint8_t*)p+0x28) != p) FUN_001150e0(s_Bad_link_elm__p_prev_005bf20c)`.
- **Severity (hypothesis)**: low — list-unlink integrity checks are fail-closed; a corrupted list panics instead of corrupting the registry, so the risk is DoS via an already-compromised list, not a new primitive.
- **Confidence**: high

## [SK18-ringminus1] 0007acd8 sk_cnode_alloc_object_and_cap
- **Observation**: The cL4 CNodeAllocator's `allocObjectAndCap` validates the requested object type against the "relocated cap" table and fails closed on three distinct precondition violations. Relocating a capability into a CNode is refused when the table is being filled ("Cannot give relocated cap when filling..."), when the object type does not match the entry, or when a generic entry cannot be allocated predictably. Every violation traps (fail-closed), never silently dropping.
- **Evidence**: `FUN_0007b0cc(obj, 0x65f380)` presence check gates the "relocated cap" branch; `sk_identity_hash(obj,3)` validity gate; fatal strings at 0x5bfca0 ("Cannot give relocated cap when filling"), 0x5bfce0 ("allocObjectAndCap is called with wrong object type"), 0x5bfd30 ("failed to allocate generic entry in a predictable way") via `FUN_0007bfdc` + `FUN_001afa84`; SoftwareBreakpoint(1,0x7b00c/0x7b010/0x7b014) bounds traps.
- **Severity (hypothesis)**: informational — capability-relocation integrity check in the exclave-launch path.
- **Confidence**: medium

## [SK18-ringminus1] 0007a718 sk_cnode_entry_build
- **Observation**: Building a CNode entry performs Swift overflow-checked arithmetic on the entry index/count and element-stride products, with a dedicated SoftwareBreakpoint trap for every overflow. The source and destination table element-size mismatch is diagnosed via a Swift `fatalError` string, so an inconsistent CNode shape aborts rather than corrupting the entry table.
- **Evidence**: traps at 0x7aa88/0x7aa8c/0x7aa90/0x7aa94/0x7aa98/0x7aa9c/0x7aaa4/0x7aaa8/0x7aaac on division-by-zero / negative / carry / high-64-of-product mismatches; mismatch path builds a fault string via `FUN_002a4ab4` + `FUN_00027724` (type names 0x671df8/0x6720e0) then `FUN_001afa84` (noreturn).
- **Severity (hypothesis)**: low — the CNode entry table is a security-relevant capability store; an overflow would allow out-of-bounds entry writes.
- **Confidence**: medium

## [SK18-ringminus1] 00078880 sk_cnode_allocator_init
- **Observation**: The CNodeAllocator designated initializer seeds every stored property (offsets 0x48..0x98) and allocates a 0x60-byte generic-entry descriptor plus a 0x38-byte CNodeEntry whose fields are fully zeroed except the validated ones. The root "space cap" and fault-data fields are set once here; the class metadata is consulted for each field offset, so the property layout is defined by the Swift metadata, not the launcher.
- **Evidence**: writes `self[0x48..0x98]` in sequence interleaved with `FUN_0007c0b8` (accessor ctx); builds entry via `FUN_0036a940(..,0x38,7)` and `FUN_0036a940(..,0x60,7)`; `FUN_00002534(DAT_0064e868, DAT_004c06c0)` string; `self[*self+0x50]`/`self[*self+0x68]`/`self[*self+0x80]` store the cap/space-cap/fault-data; trap 0x78ec4 if `FUN_0014aedc` round-up fails.
- **Severity (hypothesis)**: informational — single-time capability/root setup for the exclave CNode.
- **Confidence**: low

## [ringminus1/SK13] 000658f0 dt_integrity_parse
- **Observation**: The device-tree integrity parser walks node descriptors with explicit bounds checks and panics (via FUN_00115424 assert-style fatal) on a NULL region and on every integer-overflow of its cursor (`FUN_00066204` = "integer overflow"). The cursor is advanced by node size (`+0x24`) and property extent (`(nprop+3)&~3`), each checked for wrap before use. This is fail-closed parsing of attacker- or boot-data-derived DT content.
- **Evidence**: `FUN_00115424("context is NULL", "__AppleInternal/Library/BuildRoot", "device_tree_integrity_parse_call", 0x90)` on base==0; `0xfffffffffffffff7 < local_30` -> `FUN_00066204()` (overflow) before `*base = cursor+8`; per-node `0xffffffffffffffdb < node` -> overflow; property advance `CARRY8` -> overflow.
- **Severity (hypothesis)**: informational — the cL4 DT parser fails closed on malformed/oversized descriptors rather than silently mis-parsing; a crafted DT could still force a kernel panic (availability) if it reaches this parser with attacker-controlled bytes.
- **Confidence**: high

## [ringminus1/SK13] 00065c30 dt_node_next
- **Observation**: The device-tree node iterator validates every pointer arithmetic against the iterator's {base,limit}: it checks `base+limit < base+8` and `node+0x24 <= base+limit` before returning a descriptor, and masks the node length field to 31 bits (`&0x7fffffff`). On any overlap/overflow it traps via SoftwareBreakpoint 0x5519. This bounds-checks DT-derived offsets before dereference.
- **Evidence**: `if ((uint*)(base+limit) < puVar5+2 || puVar5+2 < puVar5) goto trap`; `(uVar3-uVar4)-0x24 < (uVar6=(ulong)puVar1[8]&0x7fffffff) -> trap`; node returned only when `puVar1 <= puVar1+9` and `base <= node && node+0x24 <= base+limit`.
- **Severity (hypothesis)**: informational — defensive parsing; prevents out-of-bounds reads on malformed DT node tables.
- **Confidence**: high

## [ringminus1/SK13] 00069bdc dtk_collect_props
- **Observation**: The property collector bounds-checks the per-node property count (`0x1f < local_c8 -> SoftwareBreakpoint`) before indexing, and accumulates `namelen = c+1` and `data+len` with explicit `SCARRY8`/negative-count traps. Property name length and data length come from masked DT header fields.
- **Evidence**: `if (0x1f < local_c8) trap(1,0x69df4)`; `SCARRY8(local_c8,1)` / `lVar1<0` / `local_d0<0` traps before `ptr[3]=a+d`.
- **Severity (hypothesis)**: informational — per-node limits enforced; a node with >0x20 properties or negative lengths is rejected, not over-read.
- **Confidence**: medium

## [SK187] 00407a04 sk_continuation_fatal
- **Observation**: The Swift `_Concurrency.CheckedContinuation` fatal path in the cL4 async transport emits a `"Fatal error"` noreturn panic (FUN_001afa84) when a CheckedContinuation is resumed incorrectly. This is the canonical Swift concurrency misuse-abort; in a kernel this converts a caller-resume-protocol violation into a synchronous kernel halt rather than a recoverable error.
- **Evidence**: `FUN_001afa84(s_Fatal_error_005accd0,0xb,2,in_x3,in_x4,s__Concurrency_CheckedContinuation_005dbd70,0x26,2)` — noreturn (decompile header "Subroutine does not return"); strings `s_Fatal_error_005accd0` and `s__Concurrency_CheckedContinuation_005dbd70` at 0x5accd0/0x5dbd70.
- **Severity (hypothesis)**: low — availability only; continuation misuse is a kernel-internal bug, not attacker-controllable from a guest. A guest able to trigger double-resume of a shared continuation could force a kernel panic (DoS).
- **Confidence**: medium

## [SK187] 00407ae8 sk_async_span_swap_release
- **Observation**: The async span swap writes a two-word value into the buffer at self(x21) after masking the source pointer to 8-byte alignment (`param_1 & ~0x7`), then releases the previously-held first word via cl4_release (FUN_0036b118). The 8-byte alignment mask on an untrusted/loosely-typed pointer could drop low address bits if a value were ever passed with a nonzero offset, releasing/misreading a wrong object.
- **Evidence**: `uVar1 = unaff_x21[1]; uVar2 = *(param_1 & 0xfffffffffffffff8); unaff_x21[1] = ((param_1 & 0xfffffffffffffff8))[1]; *unaff_x21 = uVar2; FUN_0036b118(uVar1);` — release of the overwritten low word.
- **Severity (hypothesis)**: informational — the alignment mask is a Swift span/ArrayBuffer codegen idiom (pointer is always already aligned); the release is a standard ARC release of the previous value.
- **Confidence**: medium

## [SK187] 0040807c sk_async_lock_acquire
- **Observation**: The async job acquisition path calls sk_lock_acquire (FUN_00377824) with a fixed tag 0xff and two lock-table addresses (DAT_00614a5c/DAT_00614a74), coupling the Swift async-transport object graph to the kernel's lock registry. The tag/table selection is hard-coded per call site.
- **Evidence**: `FUN_00377824(0xff,param_2,param_3,&DAT_00614a5c,&DAT_00614a74)` — lock registry tag 0xff with table descriptors.
- **Severity (hypothesis)**: informational — lock tagging is an audit/classifier primitive; no direct security exposure.
- **Confidence**: low

## [SK186] 0040774c sk_conc_pair_copy_retain
- **Observation**: The concurrency value-copy helper clears the low 3 bits of the source pointer (`param_1 & ~0x7`) and reads two words from the masked address, then ARC-retains the second word via FUN_0036b270. The alignment mask on a loosely-typed/tagged pointer would silently drop any nonzero low offset bits, retaining/reading a misaligned object if a caller ever passed a pointer carrying a tag or an offset.
- **Evidence**: `uint64_t *src = (uint64_t *)(param_1 & 0xfffffffffffffff8ull); uVar1 = src[1]; uVar3 = src[0]; dst[1] = src[1]; dst[0] = uVar3; FUN_0036b270(uVar1);` — 16-byte read from the masked pointer plus a retain on the second word.
- **Severity (hypothesis)**: informational — the `&~0x7` mask is the standard Swift/ArrayBuffer codegen idiom (pointers are always already 8-aligned); no guest-controllable input reaches this path directly.
- **Confidence**: medium

## [SK186] 00406eb0 sk_conc_unimplemented_executor_fatal
- **Observation**: The Swift `_Concurrency.UnimplementedExecutor` trap path in the cL4 async transport raises a `"Fatal error"` noreturn panic (FUN_001afa84) with the tag bit 0x8000000000000000 OR-ed into the supplied parameter. Reaching an unimplemented executor converts a runtime dispatch miss into a synchronous kernel halt.
- **Evidence**: `FUN_001afa84(s_Fatal_error_005accd0,0xb,2,0xd00000000000002a,param_1|0x8000000000000000,s__Concurrency_UnimplementedExecut_005dc2b0,0x28,2)` — noreturn; string `s__Concurrency_UnimplementedExecut_005dc2b0` at 0x5dc2b0.
- **Severity (hypothesis)**: low — availability only; reachable only via a kernel-internal executor-registration miss, not from a guest.
- **Confidence**: medium

## [sk_region_boot] cL4 Secure Kernel GL1 boot-region decompilation findings (0x0-0x80000)

## [sk_region_boot_00000] 0x00001378 sk_launcher_root
Observation: The boot launcher maps the kernel image pages into the root task's address space by writing a raw argument block (maptype 0x11) into the per-CPU TPIDRRO area and issuing an `svc 0x0` supervisor call, then polls the boot object's completion via the DAT_006adfd0 flag in a loop.
Evidence: Decompile of FUN_00001378: `puVar1 = (undefined8 *)tpidrro_el0; *puVar1 = 0x11; puVar1[1] = va-delta; puVar1[2] = phys; CallSupervisor(0);` followed by a `do { ... svc 0x0 ... } while` loop keyed on `DAT_006adfd0`.
Severity (hypothesis): Low — standard kernel boot page-mapping via SVC; informational.
Confidence: Medium (naming from strings + structure).

## [sk_region_boot_00000] 0x000016b4 sk_boot_ec_switch_impl
Observation: The boot EC switch performs unchecked bounds/overflow arithmetic on memory extents and on failure drops into a software breakpoint (`SoftwareBreakpoint(0x5519, 0x1728)`), which on a production image would trap to the debugger rather than panic cleanly.
Evidence: Decompile FUN_000016b4 tail: `pcVar2 = (code *)SoftwareBreakpoint(0x5519,0x1728); (*pcVar2)();` after the `FUN_0005b190(..., "Failed to switch boot EC for the ...")` path.
Severity (hypothesis): Low/Medium (hypothesis) — leftover debug breakpoint in a boot path; a malformed boot image could hang the boot rather than fail fast.
Confidence: Medium (decompile-observed).

## [sk_region_boot_00000] 0x00002a10 sk_zone_boot_layout
Observation: The zone allocator's boot layout computes node/region boundaries with unsigned overflow checks (`if (hi_lo <= arena)`, `if (node_lo < arena)`) and panics via the libmalloc `BUG IN LIBMALLOC` path on any violation — no unchecked arithmetic path observed.
Evidence: Decompile FUN_00002a10 contains explicit overflow guards `goto LAB_00002bfc/2c00/2c04` leading to `FUN_001150e0(s_BUG_IN_LIBMALLOC___)`.
Severity (hypothesis): Info — defensive overflow checking in the allocator bootstrap.
Confidence: High (decompile-observed).

## [sk-boot-20000] 0x00020ebc tightbeam_failure_code
Observation: Tightbeam message-failure index maps to a 16-byte error descriptor where error tags are embedded as packed little-endian ASCII in literal constants (e.g. 0x6f6e20646c756f43 = "Clound es en"). Message-create/activation/reply/decode failures return tagged message pointers with a 0x8000000000000000 high-bit marker.
Evidence: decompile switchD_00020efc_caseD_*; string refs s_Message_create_failed_005acf30, s_Activation_failed_005acf10, s_Reply_send_failed_005aced0, s_Message_decode_failed_005aceb0.
Severity (hypothesis): info — failure-code encoding, no direct privilege boundary.
Confidence: medium.

## [sk-boot-20000] 0x00021554 tightbeam_decoder_unwrap
Observation: The decoder unwrap path copies a caller-supplied byte span into an internal buffer after checking `used + span <= cap`, but on the failure branch (`goto LAB_00018798`) it calls FUN_004b0ec8/FUN_004b0eec and returns 1 rather than trapping — a non-fatal error path that may leave the decoder in a partially-consumed state.
Evidence: decompile branches at 0x18768 (SoftwareBreakpoint 0x5519) vs the return-1 path at LAB_00018798.
Severity (hypothesis): low — potential state-inconsistency on malformed decode input, gated behind caller validation.
Confidence: low.

## [sk-boot-20000] 0x00028b14 sk_vas_alloc
Observation: VAS allocation installs ~40 operation dispatch entries (FUN_00029c7c..FUN_0002f780) plus a fault-handler ring buffer (0x400 entries). The fault-handler slot claim logic computes `slot = base + (counter % count) * 6` with explicit bounds checks that trap (SoftwareBreakpoint 0x5519) on overflow, but the counter is a plain increment without saturation — a 32-bit wrap could reorder/alias slots.
Evidence: decompile ring-buffer claim at 0x299e0..0x29ae0; bounds checks LAB_000299d8/LAB_00029ae0.
Severity (hypothesis): low — ring-buffer slot reuse on counter wrap could let a fault handler be clobbered, within a trusted-initialization context.
Confidence: low.

## [sk-boot-20000] 0x0002b3ec vas_record_add
Observation: VAS record-array add grows the array by 2x (FUN_000102f4 realloc) when full, and on allocation failure builds the record inline via FUN_0002b5e8 (frame/cnode descriptor copy) — the failure path copies type 0x11 (frame) or 0x04 (cnode) capability descriptors. Any other type aborts with "Type 0x%x is not frame or cnode".
Evidence: decompile at 0x2b3ec; s_Type_0x_x_is_not_frame_or_cnode_005ae8e4.
Severity (hypothesis): info — capability-type validation before record insertion.
Confidence: medium.

## [sk-boot-20000] 0x0002a80c vas_fh_activate
Observation: Fault-handler activation maps a 0x4000-byte fault page via the handler's map method and records the mapping; failures distinguish copy-failure ("easm faulthandler failed to copy") from map-failure ("...failed to map c"). Activation is guarded by an "already active" assertion returning 0x3230001.
Evidence: decompile; s_easm_faulthandler_failed_to_copy_005ad5c5, s_easm_faulthandler_failed_to_map_c_005ad5ff, s_easm__d_FH__lld__p_is_already_ac_005ad5a0.
Severity (hypothesis): info — fault-page mapping boundary, well-validated.
Confidence: medium.

## [sk-region-boot-30000] 0x304d0/0x30780 sk_boot_image_decompress/sk_boot_image_compress
Observation: The SK boot path embeds a custom LZ/bitplane decompressor (magic 0x4321 uncompressed marker) plus its encoder. This is the image-inflation mechanism used at early boot to unpack the kernel image/entitlements.
Evidence: 0x304d0 reads magic 0x4321, zeroes a 16 KiB run via DC_ZVA, and splices (value,off16) pairs; otherwise nibble-unpacks 4 source words against the mask tables DAT_004bc6f0..6fc and runs an LZ history decode using DAT_004bc5e0. 0x30780 is the exact inverse (writes control bytes 0/1/2/3, history index to +0x1000, low-10-bit stream to +0x2000).
Severity (hypothesis): Informational (custom codec is not a documented industry standard; decompressed content is attacker-influenced only if the boot chain is already compromised).
Confidence: medium.

## [sk-region-boot-30000] 0x31594 sk_vspace_mark_alloc
Observation: The vspace slot allocator validates slot offsets against per-store capacities (0x7e/0x1fe) and aborts via VAS on out-of-range slot writes, including a check that a slot is not double-allocated (bit already set in the bitmap).
Evidence: 0x31594 walks store chain from +0x148, computes (param_2-base)>>5, sets bit (idx&0x3f) in cell (idx>>6) of bitmap at store+0x28; double-set triggers VAS abort 005af0a5; OOB triggers 005aef1a/005aeff5.
Severity (hypothesis): Defense-in-depth (internal integrity guard; prevents overlapping vspace slot use).
Confidence: medium.

## [sk-region-boot-30000] 0x33c60 sk_vspace_alloc_region
Observation: VAS private/heap region allocation requests map through the trap FUN_0003c510 with memory-attribute selectors 0x1000148 (zero base / private) vs 0x1000149 (nonzero base). A failure for a zero-base region returns 0 with a printed diagnostic rather than aborting; nonzero-base failure aborts.
Evidence: selector uVar3 = 0x1000148 if param_2==0 else 0x1000149; failure path for param_2==0 calls FUN_00118b28 ('Could not allocate for VAS private...' 005b060a) and returns 0; nonzero aborts (VAS 005b0655).
Severity (hypothesis): Informational (heap exhaustion handling distinguishes private vs mapped regions).
Confidence: medium.

## [sk-boot-40000] 0x000403b0 sk_spanmap_cap_op — capability op on spanmap lacks a bounds check before invoking the span object's handler
Observation: When op&0xfd==0 the span object's method at +0xb8/+0x10 is invoked with the caller's raw arg after only checking the span cursor range; a nonzero (error) result is folded into the L4 error word.
Evidence: Decompile: "res = (**(code **)(*(long *)(span + 0xb8) + 0x10))(*(void **)(span + 0xb0), arg);" with no capability-tag validation; nonzero → sk_vas_err + "Unexpected L4 Error" abort.
Severity (hypothesis): low — errors abort rather than silently corrupt.
Confidence: low

## [sk-boot-40000] 0x00042808 sk_vas_populate_level — bulk-unmap loop treats 0x107 as success and clears the whole vspace on any error
Observation: The per-entry PTE-clear loop stops on 0x107 (preempted) or 0 and treats them as success; on the no-regions path a nonzero return from the teardown method causes the entire 0x1a-word vspace header to be zeroed.
Evidence: Decompile: "if (ent == 0x107 || ent == 0) break;" and "if ((ent & 0xff) == 0) { for ... vas[i]=0; return; }".
Severity (hypothesis): medium — a mis-sized input could clear a live vspace.
Confidence: low

## [sk-boot-40000] 0x00040980 sk_spanmap_startfault_cow — COW fault uses supervisor call to select an attribute derived from vspace flags
Observation: The COW attribute is derived from vspace flags bitfield (param_4+0x20 >>3 & 3) and passed via CallSupervisor(0) without further validation, then a fresh page is allocated and the fault record written with the untrusted VA.
Evidence: Decompile: "fl = (*(uint*)(vas+0x20) >> 3) & 3; CallSupervisor(0); ... out[0]=1; *(long*)(out+0x10)=va;".
Severity (hypothesis): low — supervisor call mediates the actual mapping.
Confidence: low

## [sk-185] 0x00405bc0 sk185_bc0_bump — overflow-guarded counter increment traps via SoftwareBreakpoint
Observation: The function adds the result of FUN_003f4210() to the counter at param_1+8, checking for signed-carry (SCARRY8) overflow of the add; on carry it reaches a SoftwareBreakpoint(1, 0x405ca0) trap. This is a faithful Swift overflow-checked arithmetic guard (the Swift runtime traps rather than wrapping on integer overflow).
Evidence: Decompile: "lVar4 = FUN_003f4210(); if (!SCARRY8(*(long *)(param_1 + 8), lVar4)) { *(long *)(param_1 + 8) += lVar4; return; } SoftwareBreakpoint(1,0x405ca0)".
Severity (hypothesis): informational — defense-in-depth overflow trap; counter is a length/offset accumulator, not an attacker input surface.
Confidence: high (code is self-evident).

## [sk-185] 0x00405dfc sk185_dfC_vcall — indirect call through a pointer masked with & ~3, no tag validation
Observation: When param_1 is non-null the function loads param_1[0] and calls the function pointer obtained from FUN_003d4658(param_2 & ~3) with (param_1[0], param_2 & ~3). The & ~3 masks the low pointer-tag bits (Swift tag-bit scheme) but the masked target is invoked directly with no validation of param_1's object identity; an attacker able to control param_1/param_2 within the exclave could redirect the indirect call.
Evidence: Decompile: "uVar2 = *param_1; pcVar1 = (code *)FUN_003d4658(param_2 & 0xfffffffffffffffc); (*pcVar1)(uVar2, param_2 & 0xfffffffffffffffc);".
Severity (hypothesis): low — Swift vtable/method dispatch is a standard pattern; the call target derives from an internal method-table slot, not user input directly.
Confidence: low.

## [sk-185] 0x00405cd4 sk185_cd4_fill — bounded fill raises "Assertion failed" runtime failure on invalid state instead of corrupting
Observation: If param_1+0x10 is non-zero the function bails to FUN_004070cc and raises the "Assertion failed" runtime failure (via FUN_004063f4 + FUN_001afa84), a noreturn path; the normal path only fills when the self+0x18 count is positive. This is a defensive precondition check preventing a fill on already-initialized/invalid state.
Evidence: Decompile: "if (*(long *)(param_1 + 0x10) == 0) { ...count>0... } FUN_004070cc(); FUN_004063f4(0x218); FUN_001afa84();" plus sk185_str_assertion_failed_c returns "Assertion failed"/0x10.
Severity (hypothesis): informational — precondition guard that terminates rather than proceeding in an invalid state.
Confidence: medium (string s_Assertion_failed_005ce250 anchors the runtime-failure identity).

## [sk-16] 0x00070098 sk_emit_field — accounting-field multiply guarded by SoftwareBreakpoint overflow trap
Observation: The field emitter computes `value * value` and checks the high half (SUB168 product) — on a nonzero high half it reaches a SoftwareBreakpoint(1, 0x701c0) noreturn trap; a negative unsigned-divide count also traps (0x701c4). Swift-style overflow-checked arithmetic rather than wrapping.
Evidence: Decompile: "if (SUB168(auVar1 * auVar2,8) == 0) { ...normal... } SoftwareBreakpoint(1,0x701c0)". The count path: "uVar7 = FUN_00157308(param_2); if (uVar7 >> 0x1f != 0) SoftwareBreakpoint(1,0x701c4)".
Severity (hypothesis): informational — defense-in-depth overflow trap on an internal accounting counter.
Confidence: high (code self-evident).

## [sk-16] 0x00070674 sk_vec_counted_insert — counted-array insert with CARRY8 overflow trap
Observation: Inserting a delta into the counted array sums `total + delta` with a CARRY8 overflow check; on carry it reaches SoftwareBreakpoint(1, 0x70754) noreturn. The per-key count lookup (sk_set_find) is done under a retained set reference (retain/release_masked around the probe).
Evidence: Decompile: "if (!CARRY8(uVar3,param_1)) { ...insert total+param_1... } SoftwareBreakpoint(1,0x70754)".
Severity (hypothesis): informational — overflow trap; the counted array tracks per-key accounting totals.
Confidence: high.

## [sk-16] 0x000716b4 sk_fatal_launcher — InternalExclaveLauncher accounting fatal with context string
Observation: The noreturn fatal path formats "Fatal error" (s_Fatal_error_005accd0) with the string "InternalExclaveLauncher Accounti..." (0x5bfc00) and detail 0x5bfc10 via the variadic fatal printer (FUN_001afa84). This identifies the region as the InternalExclaveLauncher accounting subsystem (per-exclave resource/refcount bookkeeping).
Evidence: Decompile: "FUN_001afa84(s_Fatal_error_005accd0,0xb,2,0xd000000000000034,0x80000000005bfc10,s_InternalExclaveLauncher_Accounti_005bfc00,0x28,2,0xec,0)".
Severity (hypothesis): informational — identifies the subsystem; fatal path, not reachable with attacker data directly.
Confidence: high (exact string constants).

## [sk-16] 0x000727ec sk_set_find_impl — set-probe with tag-based equality; no bounds check on wrap
Observation: The set probe scans occupied bitmap slots comparing {key, tag} with a mask-based index wrap (`idx = idx + 1 & ~mask`); tag 2 accepts key==0. The scan terminates only when the bitmap bit is clear; there is no explicit loop-bound guard beyond the mask, so a fully-occupied table relies on the caller's insert path to have reserved an empty slot (standard open-addressing).
Evidence: Decompile: "param_3 = param_3 & (uVar6 ^ 0xffffffffffffffff); if ((...bit set...)) { do { ... } while (bit set) }".
Severity (hypothesis): informational — standard open-addressed set; the probe does not self-terminate on a full table, but insertion always reserves a slot.
Confidence: medium.

## [sk-16] 0x00072c98 sk_reserve_impl — vector reserve capacity growth with signed-overflow trap
Observation: The reserve computes `cap = count`; when the grow flag is set it doubles from `vec[0x18] >> 1` and, if that would underflow/overflow the count (fatal at 0x72d5c), masks to even capacity and clamps to count. The growth is Swift-style overflow-checked; on the unique (move) path it memmoves elements then releases the old buffer.
Evidence: Decompile: "if ((long)(uVar3 + 0x4000000000000000) < 0) SoftwareBreakpoint(1,0x72d5c)" and "*(undefined8 *)(param_4 + 0x10) = 0; FUN_0036b118(param_4)".
Severity (hypothesis): informational — overflow-guarded vector growth; standard Swift Array reserve semantics.
Confidence: high.

## [sk-17] 0x74a28-0x75c50 sk_copy_*_range — overlap-checked ranged element copies
- **Observation**: The ranged element-copy family copies [from,to) elements of a fixed stride out of a container into a destination range after verifying the source and destination ranges do not overlap; any overlap, negative range, or container-size mismatch is a hard `SoftwareBreakpoint(1,addr)` fatal (never a silent partial copy). The constructed-copy variants route through the element's move-tag (FUN_00002534 tag pair) so non-trivial element types are moved, not byte-copied.
- **Evidence**: Each body: `if (SBORROW8(to,from)) SoftwareBreakpoint(1,addr)`; then `if (end<=src || src+n*size<=dest) { copy; FUN_0036b118(container); return end; }` else `SoftwareBreakpoint(1,addr)`. Constructed variants call `FUN_0035b67c(dest, src, n, tag)` with tag from `FUN_00002534(DAT_0064xxxx, DAT_004cxxxx)`.
- **Severity (hypothesis)**: informational — bounds/overlap discipline prevents buffer overlaps in the cap-vector layer; the fatal-on-overlap is fail-closed.
- **Confidence**: high

## [sk-17] 0x75cb4-0x76d08 sk_vec_insert_* — lock-tagged slot insertion with grow-on-collision
- **Observation**: Vector/slot insertion is guarded by the lock-tag primitive FUN_00258c60 (an acquire that returns whether the target slot was already live). Each insert re-resolves the slot key a second time after the lock-tag acquire and fatals (FUN_002591b4 / SBP) if the slot's occupancy flag changed between the two resolves — a classic double-checked-lookup against concurrent mutation. On a live slot the displaced element is released (FUN_0036b118 token release or FUN_003a25d4) after the new value is installed, preventing refcount leaks on overwrite.
- **Evidence**: `r = FUN_00258c60(lock, ...); if (r&1) { st2 = re-resolve; if ((st>>32)&1 != (st2>>32)&1) fatal; }` then on occupied path `old = slot[i]; slot[i]=new; FUN_0036b118(old);`. Count bump at this+0x10 is CARRY-checked (SBP at 0x76cf8/0x76f64).
- **Severity (hypothesis)**: informational — the double-checked slot resolution plus displaced-element release guards against ABA-style races and refcount leaks in the cap table.
- **Confidence**: medium

## [sk-17] 0x76ac8 / 0x76d08 sk_slot_iter_*_bitmap — bitmap-slot iteration writes occupancy bit + count
- **Observation**: The two bitmap iterator cores walk the set bits of a reversed bitmap (standard bit-reverse + LZCOUNT) and, for each selected slot, set the occupancy bit in the container's bitmap (this+0x40) and bump the element count (this+0x10) on the free path, or accumulate the auxiliary count (CARRY-checked) on the collision path. Both count increments and the accumulator are overflow-fatal.
- **Evidence**: free path `*(bm + 0x40) |= 1<<(idx&0x3f); *(count+0x10) += 1` with `if (CARRY) SoftwareBreakpoint(1,0x76cf8)`; collision path `if (CARRY8(old,aux)) SoftwareBreakpoint(1,0x76cf4)`. Entries retained (thunk_FUN_0036b270) then released (FUN_0036b118 / FUN_003a25d4).
- **Severity (hypothesis)**: informational — overflow-guarded bitmap slot accounting; no weakness observed.
- **Confidence**: medium

## [sk-17] 0x76fc0 sk_write_imm64 — raw 64-bit immediate write to global 0x64e038
- **Observation**: A single function writes a hard-coded 64-bit immediate (0x91181400d00002a0, which decodes to an ARM64 `orr`/instruction-patch constant) into the global at 0x64e038, then returns. Ghidra removed an unreachable block at 0x76fd4, so the write is unconditional in the reachable path. This looks like a one-time patch/initialization of a runtime hook or jump slot.
- **Evidence**: `uRam000000000064e038 = 0x91181400d00002a0;` (single store); `/* WARNING: Removing unreachable block (ram,0x00076fd4) */`.
- **Severity (hypothesis)**: low — an unconditional global write of a fixed constant; if 0x64e038 is a code/jump slot the value is fixed at build, so not attacker-influenced here, but worth confirming the target's meaning (potential runtime-patch surface).
- **Confidence**: low


## [sk-syscalls] 0x300000-0x380000 region — syscall/exception-entry security findings
Security-relevant observations logged during decompilation of the cL4 syscall/exception-entry region (sk_region_syscalls_part01-32.c). Each entry follows the standard Observation/Evidence/Severity/Confidence template. 150 findings total across the 32 slices.
# SK findings — slice 01 (0x3004ec-0x311e34)

Region characterization: this slice is the embedded Swift standard-library
integer/string/buffer runtime that the cL4 kernel links in for syscall and
exception-entry argument parsing/conversion. It consists almost entirely of
compiler-generated checked-arithmetic and BinaryInteger-conversion helpers.
Security-relevant observations below.

## [sk] 00300544 swift_uint_parse_decimal_checked
- Observation: Decimal string parser for the syscall-argument path decodes an
  attacker/guest-supplied character buffer (base/length packed in the call
  descriptor) into a 32-bit integer. On a bad digit or 32-bit overflow it
  invokes FUN_001afe4c (Swift fatalError), which never returns and terminates
  the kernel.
- Evidence: Overflow guarded by `if ((t & 0xffffffff00000000) != 0) goto
  overflow` where overflow -> `SWIFT_FATAL()`; bad digit (`d > 9`) likewise.
  Decompile shows `s_Fatal_error` / `s_Not_enough_bits_to_represent_the_...`
  strings routed to the no-return fatalError.
- Severity (hypothesis): DoS — if any syscall forwards unvalidated length or
  content, a crafted argument panics the kernel. The overflow is deliberately
  caught (it is the standard Swift checked conversion), so this is a
  panic-on-bad-input surface, not a memory-safety flaw.
- Confidence: medium.

## [sk] 003009c0 swift_i32_binary_integer_conversion (and siblings 0030523c, 00302750, 003030d4, 00303a78, 003043d4, 00307514, 00307ed8, 0030887c, 003091d4, 0030d5c0, 0030e094, 0030eb1c, 0030f5bc, 00311e34)
- Observation: Range-checked BinaryInteger conversions used to coerce syscall
  argument values to a fixed width. When the source value does not fit the
  target width (bit-width from type metadata > 32/64), the code builds the
  Swift error buffer (FUN_00377bec) and calls fatalError — terminating the
  kernel rather than returning an error to the caller.
- Evidence: All share the shape `if (bits >= 0x40) { FUN_00377bec(...);
  FUN_00310ad4(...); SWIFT_FATAL(); }` with "Not enough bits to represent..."
  string; sentinel clamps 0x80000000/0x7fffffff/0xffffffffffffffff in the
  overflow branches.
- Severity (hypothesis): DoS on out-of-range syscall argument; no privilege
  boundary crossed since the conversion is width-checked before use.
- Confidence: medium.

## [sk] 00310924..00310fc4 swift_type_metadata_field_*
- Observation: The generic conversion machinery reads type-metadata fields via
  the relative-addressing pattern `(md + off) + *(int*)(md + off)`, after
  dereferencing an indirect-metadata pointer when the low bit of md is set
  (`md = *(uint64_t*)(md & ~1)`).
- Evidence: Decompiler-clean identical bodies across ~28 accessors, e.g.
  `FUN_00310a14`: `if ((param_1&1)) param_1=*(ulong*)(param_1&~1); return
  (param_1+0x20)+*(int*)(param_1+0x20)`.
- Severity (hypothesis): If a guest could influence the metadata pointer this
  becomes an arbitrary read / potential code-exec; however metadata is
  kernel-owned compile-time data, so exposure is only via a prior corruption
  (not a direct input). Low.
- Confidence: low.

## [sk] 003015dc swift_word_index_validate (and 00305da4, 003069c8, 00309ed0, 0030c9cc)
- Observation: Word-buffer index validation bounds-checks an index before
  buffer access; negative or out-of-range indices trap via fatalError
  ("Negative word index" / "Word index out of range").
- Evidence: `if (idx < 0) fatal("Negative word index"); else if (idx == 0)
  return accessor; else fatal("Word index out of range")`. Bounds check present.
- Severity (hypothesis): defensive; a bad index panics the kernel (DoS) but
  prevents an out-of-bounds access. Low.
- Confidence: high (string-matched).

## [sk] 0030a8ec/0030ae1c/0030b340/0030b870 swift_u64_inplace_* (in-place shifts)
- Observation: In-place 64-bit shift helpers mask the shift count with `& 0x3f`
  and zero the value for counts >= 64, but on out-of-range shift counts also
  route through the metadata accessor chain that can hit the fatal path.
- Evidence: `v << (n & 0x3f); if (n >= 0x40) v = 0;` plus the FUN_00310xxx
  accessor dispatch that traps on large counts.
- Severity (hypothesis): shift-count handling is masked and bounded; the fatal
  path only fires on malformed metadata (kernel-owned). Low.
- Confidence: low.

Summary: No memory-safety defect identified in this slice. The recurring theme
is that out-of-range / malformed syscall argument values cause the Swift
runtime to terminate the whole kernel via fatalError rather than returning a
graceful error — a denial-of-service consideration if untrusted arguments can
reach these helpers unvalidated. All arithmetic overflow is explicitly checked.

# SK region findings — Slice 02 (0x312a44-0x31a96c, arithmetic/compiler-rt library)

## [sk] 0x00312d08 sk_udivti3_core
Observation: 128-bit unsigned division core panics on a zero divisor ("Division by zero", code 0x4d9).
Evidence: Decompile shows `if (divisor_hi==0 && divisor_lo==0) { FUN_00355754("Division by zero"); ...panic 0x4d9; no-return }`.
Severity (hypothesis): robustness/availability — a divide-by-zero reaching the kernel would fault; the panic converts it to a controlled halt rather than an EL1/EL2 exception.
Confidence: high.

## [sk] 0x003130bc sk_udivmodti4_core
Observation: 128/128 divide-with-remainder core panics on zero divisor ("Division by zero", 0x501) AND on quotient overflow ("Division results in an overflow", 0x504).
Evidence: Decompile shows both `FUN_00355754("Division by zero")` and `FUN_001a89a8("Division results in an overflow",0x1f,1)` panic paths.
Severity (hypothesis): availability — overflow/divide-by-zero guarded by panic (controlled halt), preventing silent wraparound of quotient.
Confidence: high.

## [sk] 0x0031552c sk_sub_checked
Observation: 128-bit checked subtract panics on underflow ("Overflow in", 0x262) rather than wrapping.
Evidence: Decompile shows `FUN_0031552c(..., s_Overflow_in____005d3099, 0xe, 0x262)` and a panic path via FUN_001afe4c (no-return).
Severity (hypothesis): correctness/availability — unsigned-underflow detected and halted; prevents silent large-value corruption used by arithmetic-helper callers.
Confidence: high.

## [sk] 0x003155b8 sk_add_checked
Observation: 128-bit checked add panics on overflow ("Overflow in", 0x26e) rather than wrapping.
Evidence: Decompile shows `FUN_003155b8(..., s_Overflow_in____005d3057, 0xe, 0x26e)` with a no-return panic path.
Severity (hypothesis): correctness/availability — signed-overflow detected and halted.
Confidence: high.

## [sk] 0x003163d8 sk_checked_op
Observation: Dispatched 128-bit arithmetic op panics when the low-bit flag indicates overflow (panic code 0x2aa) instead of returning a wrapped result.
Evidence: Decompile: `if ((flag & 1) == 0) {*out=result; return;} ...panic FUN_001afe4c`.
Severity (hypothesis): correctness/availability — overflow is caught centrally for multiply/add callers (sk_add128_checked 0xae, sk_mul_checked 0x2aa).
Confidence: medium.

## [sk] 0x003191e8 .. 0x0031a96c sk_field_ref_*
Observation: ~50 object field accessors dereference a potentially tagged pointer: when bit0 of the object pointer is set, the code masks off bit0 and loads the real pointer through that address, then returns `(obj+off) + *(int*)(obj+off)` (a relative reference resolve).
Evidence: Decompile pattern: `if (param_1 & 1) param_1 = *(ulong*)(param_1 & ~1); return (long)(param_1+OFF) + *(int*)(param_1+OFF);` repeated at many offsets (0x4,0x8,0xc,0x10,0x14,0x18,0x1c,0x20,0x24,0x28,0x2c,0x30,0x34,0x38,0x3c,0x40,0x44,0x48,0x4c,0x50,0x58,0x5c,0x6c).
Severity (hypothesis): memory-safety — a forged/tagged pointer with bit0 set causes a load from an attacker-influenced address; if the object pointer is attacker-controlled this is a read primitive. Mitigation hypothesis: these operate on kernel-managed object pointers only; the relative-ref arithmetic is bounds-untested here.
Confidence: medium.

## [sk] 0x00318d40 sk_parse_int_fmt
Observation: Number-format string parser reads a sign character ('+'/'-') from the buffer and converts base-10, returning {base,value,flags}; bounds-checked via FUN_001d9840/FUN_001e4cbc.
Evidence: Decompile: checks `*buf=='+'` / `*buf=='-'`, then `if (len<0 || param_3<len) panic` path via FUN_003484b4.
Severity (hypothesis): input-validation — parse-length bounds are checked before conversion; overflow on huge input would be caught by the arithmetic panic guards.
Confidence: low.

## [sk] 0x003152b8 sk_neg_checked / 0x00318ed0 sk_float_mul_add
Observation: Negation of a signed value traps via SoftwareBreakpoint when negating INT64_MIN (0x8000000000000000).
Evidence: Decompile: `if (SBORROW8(0,unaff_x20)) SoftwareBreakpoint(1,0x315318)` and `SoftwareBreakpoint(1,0x318f5c)`.
Severity (hypothesis): correctness — MIN-negate is a UB edge caught by a debug trap; in release this could wrap. Not exploitable but worth noting.
Confidence: medium.

# SK slice 03 findings (0x31a99c-0x31d4e8)

Region is the syscall/exception-entry method-dispatch layer: ~92 tagged-object
region-end accessors, ~41 no-op/unsupported stubs forwarding to FUN_00021480,
and ~72 method-table dispatch trampolines plus a handful of map/allocate/
validate handlers.

## [sk] 0031ce04 sk_op_map_poll — page-table permission bits assembled from object flags with no in-slice validation
- Observation: The map handler builds a page-table attribute word from three byte flags in the object header (+0x18 read-only / 0x80000000, +0x19 / 0x40000000, +0x1a / 0x20000000) and passes it straight to the out-of-slice mapping primitive FUN_0024c0d0(bits, 0). No bounds, alignment, or privilege check on the flags or target address is performed inside this function.
- Evidence: `if (*(char *)((char *)ctx + 0x18) != '\0') { uVar6 |= 0x80000000; ... } uVar5 |= 0x40000000 ... uVar3 = 0x20000000 ... FUN_0024c0d0(uVar5 | uVar3, 0);` The permission decisions are delegated entirely to FUN_0024c0d0 (out of slice).
- Severity (hypothesis): medium — whether this is exploitable depends on the validation in FUN_0024c0d0, which is out of slice and not yet audited.
- Confidence: low (no header/string match; attribution inferred from page-bit values).

## [sk] 0031cd48 sk_op_map — mapping size OR-ed with a fixed attribute tag before out-of-slice map
- Observation: Maps a region whose size is taken from the object header (+0x10, decremented by 8) and OR-ed with the fixed tag `0xa0000000` before being passed to FUN_0024c0d0. An underflow of the size is trapped (SoftwareBreakpoint 1,0x31ce04), but the resulting attribute combination and the target virtual address (+0x20) are not otherwise validated here.
- Evidence: `uVar2 = ctx[2] - 8; if (ctx[2] < 8) { trap } ... FUN_0024c0d0((uint32_t)uVar2 | 0xa0000000, 0);`
- Severity (hypothesis): medium — attribute/target validation is deferred to the out-of-slice primitive.
- Confidence: low.

## [sk] 0031b394 sk_op_allocate — signed multiply overflow guarded by a trap
- Observation: Object size is computed as `count * element_size` (element size from context +0x48) with a 128-bit overflow check that traps (SoftwareBreakpoint 1,0x31b43c) when the product overflows a signed word. This is a defensive guard against size-arithmetic overflow in the allocation path.
- Evidence: `if (overflow) { SoftwareBreakpoint(1,0x31b43c); }` then branches on negative/zero/prealloc.
- Severity (hypothesis): low (defensive; noted for the allocation audit).
- Confidence: low (heavy extraout_* register artifacts).

## [sk] 0031a99c..0031d4e8 sk_obj_end_* (92 accessors) — tagged-pointer dereference with no type/bounds check
- Observation: A large family of object accessors dereferences a possibly-tagged object reference (`if (obj & 1) obj = *(word_t *)(obj & ~1ULL)`) and then computes an end pointer from a signed length stored at a per-object offset. If any of these is reached with an untrusted object reference, the indirect dereference and the `base + offset + signed_len` arithmetic are performed without an in-slice bounds check (relying entirely on upstream capability checks).
- Evidence: identical pattern across 92 functions: `obj = *(word_t *)(obj & 0xfffffffffffffffe); return (obj + OFF) + *(int *)(obj + OFF);`
- Severity (hypothesis): medium — potential type-confusion / out-of-bounds read if an object reference escapes capability validation; per-object offsets 0x4..0xd0.
- Confidence: low (no callee/string identity; pattern-level hypothesis).

## [sk] 0031bd68 sk_op_validate — validation predicate resolved via function pointers from the object table
- Observation: The "validate" dispatch resolves two function pointers from the object's method table and an offset derived from a byte at +0x50, invokes the first as a predicate on the argument, and only calls the second if the predicate returns true. The correctness of the whole check therefore depends on the integrity of the object's method table.
- Evidence: `uVar4 = (*(word_t (**)(word_t))(ctx + *(int *)(lVar3 + 0x2c)))(arg); if ((uVar4 & 1) == 0) return 0; return pcVar1(arg) & 1;`
- Severity (hypothesis): low-medium — table-driven validation; if the table is attacker-influenced the check can be bypassed.
- Confidence: low.

# SK Slice 04 findings (0x31d518-0x322450) — syscall/exception-entry + Swift buffer helpers

## [sk] 0x0031e4e0 sk_swap_bytes_e4e0 — Buffer index bounds-checked before element swap
Observation: The byte-swap helper validates both indices against the buffer
length and traps (noreturn `FUN_001afe4c` fatal) on out-of-range or a nil
buffer base before performing the two-byte swap; error codes 0x18f (negative
index), 0x190 (index >= length), 0x191 (unexpected nil base).
Evidence: `if ((int64_t)a < len && (int64_t)b < len) { ... swap ... }` else
fatal with `s_Fatal_error_005accd0` / `s_Swift_UnsafeBufferPointer_swift_005cdc10`.
Severity (hypothesis): None (defensive bounds check prevents OOB write).
Confidence: high (string match + explicit range test).

## [sk] 0x003207e0 sk_copy_replace_207e0 — Range-validated replace-subrange copy
Observation: The replace-subrange copy validates the destination/source
ranges (errors 0xea/0xeb/0xec) and traps via SoftwareBreakpoint on signed
underflow of the range arithmetic before copying elements. Violations route
to the noreturn fatal handler rather than silently overflowing.
Evidence: `if (lo < 0) { FUN_0035047c(); err = 0xea; } ... if (SBORROW8(hi,lo)) SK_TRAP()`.
Severity (hypothesis): None/defensive (mitigates OOB write; failure is a
kernel fatal, i.e. potential DoS if a caller can trigger it).
Confidence: medium.

## [sk] 0x00320dbc sk_raw_copy_20dbc — Raw copy length validated against destination range
Observation: Before copying, the helper validates the resolved count against
the destination buffer range (`l < n` -> fatal 0x21d) and requires a
non-negative pointer offset (0x603 fatal otherwise), preventing OOB write /
negative-offset write into the destination.
Evidence: `if (l < n) FUN_001afe4c(...0x21d,1); ... if (-1 < b) copy else fatal 0x603`.
Severity (hypothesis): None/defensive.
Confidence: medium.

## [sk] 0x003212c4 sk_buf_subscript_212c4 — Buffer subscript bounds check with trap
Observation: Buffer element read validates `idx` against [0, end-base] and
traps (noreturn fatal) on out-of-range, preventing OOB read of the buffer.
The read path is used by syscall-entry byte handling.
Evidence: `if (base != 0 && idx < (uint64_t)(len-base)) return buf[idx]; else
FUN_0034dab8(); ... fatal`.
Severity (hypothesis): None/defensive.
Confidence: medium.

## [sk] 0x0031fa14/0x0031f998 sk_bounds_check_fa14/f998 — Precondition bounds + overflow detection
Observation: Precondition checks verify [a, a+n) lies within the buffer and
detect signed overflow of the end pointer arithmetic (`SCARRY8(a,n)`) before
any access, trapping on violation. Prevents pointer-wrap OOB access.
Evidence: `if (!SCARRY8(a, n)) return; FUN_0035047c(a + n); ... fatal`.
Severity (hypothesis): None/defensive.
Confidence: medium.

## [sk] 0x0031ed10/0x0031fc64 sk_make_buf_init_ed10/fc64 — Element-pointer formation bounds check
Observation: Before materializing an element pointer (`base + stride * idx`),
the helper validates `idx` against the buffer length (errors 0x237/0x238 and
0x75d/0x75e), preventing formation of an out-of-bounds element pointer from a
bad index.
Evidence: `if (idx < 0) err=0x237; else if (idx < len) { materialize } else err=0x238`.
Severity (hypothesis): None/defensive.
Confidence: medium.

## Summary
This slice is dominated by (a) syscall-entry trampolines reading args from the
preserved syscall context (x20 frame) and (b) Swift-runtime UnsafeBufferPointer
/COW/refcount helpers pulled into the kernel's entry path. The Swift helpers
consistently perform index/range/capacity validation with a noreturn
`_fatalError` (FUN_001afe4c) on violation — no silent OOB access path found.
Security-relevant observation: all validation failures are kernel-fatals; if
an unprivileged guest can influence a bad index into these entry handlers it
could induce a kernel panic (availability), though no privilege-escalation or
OOB-corruption path was identified in this range.

# SK slice 05 security findings (0x3224a0-0x327bf8, syscall/exception-entry)

## [sk] 0x3224f0 / 0x322a88 / 0x322d44 / 0x323304 / 0x323f64 — syscall IPC/capability handler prologues
Observation: These syscall handlers build a capability message directly from the
exception frame's argument registers (`in_stack_00000060..98`) via
`FUN_003515b4(0, N, &args)` and resolve the destination capability through the
kernel dispatch table (`DAT_00658c00` / per-class method-table slot +0x10). The
capability pointers are user-supplied; correctness of the whole seL4 security
model depends on the cap lookup/validation in `FUN_00371950` (sk_cap_lookup).
Evidence: decompile of FUN_003224f0, FUN_00322a88, FUN_00322d44, FUN_00323304,
FUN_00323f64 — `FUN_003515b4(0,4|5|6,&args)` then `FUN_00371950()` then
`(*DAT_00658c00)(*(x+0x40))`.
Severity (hypothesis): medium — capability argument validation is the core
security boundary; needs the cap_lookup body to confirm.
Confidence: medium.

## [sk] 0x3248c — IRQ notify dispatch with object-slot dereference
Observation: FUN_0032488c reads three slots from the base object (`x20+0x10`,
`x20+0x20`, `x20+0x30`), passes one to the IRQ handler `FUN_0014ae44`, binds the
current thread (`FUN_00027754`) and invokes a function pointer loaded via
`FUN_0014ae44(...)`. The IRQ object slots drive an indirect call.
Evidence: `pcVar2 = (code *)FUN_0014ae44(*(undefined8 *)(unaff_x20 + 0x30));` then
`uVar1 = (*pcVar2)();`.
Severity (hypothesis): medium — an unvalidated object-slot function pointer is
called; depends on object initialization discipline.
Confidence: medium.

## [sk] 0x3244b4..0x324ca0 — tagged-pointer intrusive-list accessors
Observation: A family of accessors (`sk_ilst_elem_at_*`) clears the low tag bit
of a pointer (`if (p & 1) p = *(p & ~1)`) and then dereferences `*(p + off)` plus
a signed offset stored at `p + off`. If a corrupt or attacker-influenced tagged
pointer reaches these, the dereference is a type-confusion / arbitrary-read
surface.
Evidence: `return (p + 0x30) + *(int *)(p + 0x30);` after tag clear.
Severity (hypothesis): medium.
Confidence: medium.

## [sk] 0x324e8c / 0x324eb8 — buffer metadata error paths (bounds validation present)
Observation: The kernel raises "UnsafeMutableRawBufferPointer with negative
stride" (DAT_005cde70) and "UnsafeRawBufferPointer with negative..." (DAT_005cdef0)
errors via FUN_00324ee4 with file/line/code arguments. This shows user-supplied
buffer stride/lengths are validated and rejected on negative stride.
Evidence: `FUN_00324ee4(p1, p2, s_UnsafeMutableRawBufferPointer_wi_005cde70, 0x31, 0x74, 0xfc7)`.
Severity: low (defensive check present).
Confidence: high (string match).

## [sk] 0x323304 / 0x323f64 — TCB argument-slot reads indexed by syscall args
Observation: The cap-op/sys-op handlers read TCB slots at `+0x30..+0x70`
(`*(int*)(unaff_x19 + 0x30)` etc.) and pass user syscall arguments (param_7,
param_8, in_stack_*) into the run-queue/capability helpers `FUN_00353718`,
`FUN_00353130`, `FUN_00352b80`. The syscall args become offsets/bases into
kernel structures.
Evidence: `iVar2 = *(int *)(unaff_x19 + 0x30); FUN_00353130(unaff_x24 + iVar2, param_8, ...)`.
Severity (hypothesis): medium — needs the helper bodies to confirm bounds checks.
Confidence: medium.

# SK slice 06 findings (0x327c38-0x32cbf8, syscall-metadata registry)

## [sk] 0x327c38-region sk_sysreg_register_* syscall dispatch-table population
Observation: This entire range builds the cL4 syscall dispatch registry. Most
entries resolve a syscall group descriptor (DAT_004e* pointers) with a numeric
tag (e.g. 0x676948, 0x6773c0, 0x6776f0) via FUN_00376820 (=sk_syscall_register,
the name-hash registry insert) and store the resulting slot into the global
table at 0x6564d0-0x656840. A second pattern lazily initializes a name range
(sk_registry_get_or_init on 0x656xxx + a DAT_ descriptor) and binds a handler
leaf stub before registering {descriptor, name, handler}. These leaf stubs
(e.g. FUN_00328520, FUN_00329358) write a literal 8-byte instruction-encoding
constant — the first words of the real handler body — into the slot, so the
registry holds code-derived values rather than plain addresses.
Evidence: Ghidra decompiles of FUN_00327c90 (`uRam006564d8 =
FUN_00376820(&DAT_004ebe4c,0x676948)`), FUN_00328520 (`uRam00656560 =
0xf2e021c1f2c00801`), FUN_00329358 (one-time `FUN_00656634 =
FUN_00376820(&DAT_004ecfa8,0x677600)`). Syscall-group name strings
(CapSyscalls..HypercallSyscalls) live at 0x61b7b0.
Severity (hypothesis): informational / design note — the syscall dispatch
table is built at boot from a fixed set of groups; worth confirming no
untrusted input selects a group.
Confidence: medium

## [sk] 0x32c3a4/0x32c438/0x32c4cc sk_obj_vtable_dispatch_0x18/0x20/0x28
Observation: Three near-identical dispatch helpers resolve an object via
FUN_00348c64, call a vtable entry at +0x18/+0x20/+0x28, then call the
corresponding vtable entry again on an address computed from a type byte at
vtable+0x50 (`lVar3 + x21 & ~uVar2`). The type byte selects the target within
a vtable-relative region, so the effective dispatch offset is type-controlled.
Evidence: Ghidra FUN_0032c3a4/0x32c438/0x32c4cc; each uses
`(**(code**)(extraout_x16_00 + <off>))(lVar3 + unaff_x21 & (uVar2 ^ ~0), ...)`
with `uVar2 = (byte)*(extraout_x16_00 + 0x50)`.
Severity (hypothesis): medium — indirect-call integrity depends on the type
byte being a valid, kernel-controlled vtable index; a forged/out-of-range type
would select an arbitrary nearby function pointer.
Confidence: low (structural reconstruction; decompiler lost the exact base)

## [sk] 0x32b65c sk_obj_swap_type_tagged type-descriptor vtable dispatch
Observation: Cross-type object swap dispatches through per-type descriptor
vtables at +8/+0x10/+0x18/+0x20, gated by a "shared" flag bit at type+0x52 and
a per-type flag at desc+0x50 bit 0x11. The vtable target is selected by the
object's type tag (param[3]); an attacker-controllable type tag would select
an arbitrary indirect call.
Evidence: Ghidra FUN_0032b65c; jumptable at 0x0032b760 not recovered, indirect
calls via `(**(code**)(desc + 0x18))`, `(**(code**)(desc + 0x10))`,
`(**(code**)(desc + 0x20))`, `(**(code**)(desc + 8))`.
Severity (hypothesis): medium — object-type-tag integrity is load-bearing for
the indirect call.
Confidence: low (heavy extraout_* noise; best-effort reconstruction)

## [sk] 0x32c560 sk_obj_syscall_account syscall accounting/validation
Observation: A syscall-accounting path resolves the current context, binds
obj+0x10/+0x18, compares a per-object counter at vtable+0x54, and on the
dispatch path switches on a sub-opcode selecting among FUN_0034e32c (type 3)
and no-op (types 2/4) before returning a result; the failure path runs
FUN_003520e8/FUN_0034bf1c and returns FUN_000839f8(). The branch
`if (unaff_w22 == 0) return 0` early-outs on a zero flag.
Evidence: Ghidra FUN_0032c560; `switch(extraout_w9)` with cases 2/3/4.
Severity (hypothesis): low — argument/counter validation before dispatch.
Confidence: low (extensive extraout register loss)

# SK slice 07 findings (0x32cc70-0x33979c)

Slice 07 = cL4 secure-kernel syscall/exception-entry region. All bodies were
repaired to compile-clean against fresh Ghidra decompiles. Findings below are
security-relevant observations from the repaired bodies.

## [sk] 0x32cc70 sk_syscall_entry_dispatch_0
- Observation: Top-level syscall entry dispatches through a function pointer
  read from the frame/capability table (`(code **)(table+0x10/0x18/0x20/0x28)`)
  after the prelude. Control flow is entirely table-derived; there is no
  explicit validation of the dispatch target beyond the carry/zero flag state
  produced by the setup helpers.
- Evidence: `FUN_00358750` (copy) then `((void (*)(void))0)()` in the success
  path; header notes "callees FUN_0034d724/348d94/377824/34b57c (prelude)",
  "FUN_00358750 (copy)", "FUN_0034e974 (release)". Decompile 0x32cc70 shows
  the result-driven branch.
- Severity (hypothesis): Medium — indirect call through table pointer; integrity
  of the syscall frame is the trust boundary.
- Confidence: Medium.

## [sk] 0x333b14 sk_msg_cap_validate_2
- Observation: Message-capability validation. The caller-supplied word is
  bounds-checked against the slot limit before a capability can be issued:
  `if (/* w20 */0 <= a) goto fault;` where `a = (lim != 0) ? lim - 1 : 0` and
  `lim = *(uint *)(table+0x54)`. The tag/field is read at `(long)x19 + off`
  where `off` derives from `*(long *)(table+0x40)`; only `lim < 2` guards the
  fall-through fault. The field read offset is not independently re-bounded
  against the slot object size before the dereference.
- Evidence: `uint lim = *(uint *)/* table+0x54 */0;` / `if (/* w20 */0 <= a) goto fault;` /
  `uint p = (uint)*(byte *)((long)/* x19 */0 + base);` (0x333b14 body).
- Severity (hypothesis): Medium — if table+0x40 (slot offset) is attacker-
  influenced, a wide read (16/32-bit) at `x19+off` can over-read past a small
  slot and gate capability issuance.
- Confidence: Medium.

## [sk] 0x335f10 sk_msg_cap_validate_4
- Observation: Same cap-validation shape as 0x333b14. The slot field read
  width is selected by `(uint)base < 4` with `base` from `table+0x40`; a 16/32-bit
  field is read at `(long)x19 + base` when `0xff < w10`. The out-of-range word
  (`w20 <= limit`) routes to the fault path `FUN_000839f8`. Only `limit == 0`
  terminates the post-check.
- Evidence: `if (/* w20 */0 <= limit) goto out;` / `b = (uint)*(ushort *)((long)/* x19 */0 + base);` /
  `out: return FUN_000839f8(0);` (0x335f10 body).
- Severity (hypothesis): Medium — offset-relative wide reads near slot bounds.
- Confidence: Medium.

## [sk] 0x33660c sk_slot_write_value_b (and 0x336be4 sk_slot_write_value_c)
- Observation: Slot value write. A slot width of exactly 3 bytes triggers a
  hard CPU trap (`SK_BREAKPOINT()` / SoftwareBreakpoint(1,0x33676c) and
  (1,0x336d54)). 3-byte slots are treated as invalid and never written; widths
  1/2/4 are handled. This is a defensive invariant enforced in both the clear
  and set paths.
- Evidence: `case 3: SK_BREAKPOINT();   /* SoftwareBreakpoint(1,0x33676c) */`
  and `case 3: SK_BREAKPOINT();   /* SoftwareBreakpoint(1,0x336d54) */`
  (0x33660c / 0x336be4 bodies).
- Severity (hypothesis): Low — malformed slot-width causes a deterministic
  trap (fail-closed), not a memory corruption.
- Confidence: High.

## [sk] 0x3374e8 sk_msg_cap_validate_write_d
- Observation: Capability-validate/write. The tag byte at a table-derived
  offset (`x19 + x12_00`, or a byte at `x19 + off`) gates whether a capability
  is issued (`FUN_00351538`). The caller word `w22` is compared against the
  slot limit, and the `v <= limit` path returns early via `FUN_000839f8`.
  When `limit == w10` (limit matches the target word) it issues a fault/panic
  (`FUN_0034bf1c`) before returning.
- Evidence: `if (/* w22 */0 < limit || ...)` / `if (v <= limit) { FUN_0034bf1c(0); FUN_0008e500(0); FUN_000839f8(0); return; }` /
  `out = FUN_00351538(0);` (0x3374e8 body).
- Severity (hypothesis): Medium — capability issuance gated on an offset tag
  read; correctness depends on table+0x40 / selector integrity.
- Confidence: Medium.

## [sk] 0x338128 sk_msg_slot_read_c
- Observation: Slot read with size selection. Reads 1/2/4 bytes at
  `(long)x19 + off`, where `off` is built from `dst+0x40`, `src+0x50` and
  `src+0x40`. The caller word `w21` is bounds-checked against
  `lim1 = max(src+0x54, dst+0x54)`; if `w21 < lim1 || w21 - lim1 == 0` the read
  is skipped and the fault path `FUN_000839f8` runs. A wide read (`p<4` selects
  32-bit) at an offset not bounded by the destination slot object could
  over-read if `w21` passes the limit check but `off` is large.
- Evidence: `uint lim1 = *(uint *)(src + 0x54); ... if (lim1 <= lim2) lim1 = lim2;` /
  `if (/* w21 */0 < lim1 || /* w21 */0 - lim1 == 0) goto out;` /
  `v = (n >> 0x10 == 0) ? (uint)*(ushort *)((long)/* x19 */0 + off) : *(uint *)((long)/* x19 */0 + off);`
  (0x338128 body).
- Severity (hypothesis): Medium — width-selected reads near slot boundary.
- Confidence: Medium.

## [sk] 0x337c14 sk_syscall_msg_write_g (and 0x33879c/0x33918c write_h/write_i)
- Observation: Message write with array/word copy. The copy is gated by
  `((sel | x9) < 8 && ((w13 | w10) & 0x100000) == 0 && (x11 + table+0x40) < 0x19)`
  (a combined size/attribute/offset bound). When the gate fails, the slow path
  does `*(x25) = *(x19)` (a raw frame-word copy) before `FUN_0036b270`. The
  fast-path destination offsets are computed as `(dst + x25 + dst2 & ~sel)`.
- Evidence: `if (((sel | /* x9 */0) < 8 && ((/* w13 */0 | /* w10 */0) & 0x100000) == 0) && (ulong)(/* x11 */0 + *(long *)/* table+0x40 */0) < 0x19)` /
  `*(word_t *)/* x25 */0 = *(word_t *)/* x19 */0;` (0x337c14 body).
- Severity (hypothesis): Low-Medium — copy length is bounded (0x19 = 25 words)
  but the word copy on the fallback path is ungated by attribute checks.
- Confidence: Medium.

# SK Slice 08 findings (0x339ca8-0x344290) — syscall/capability region

Findings for the cL4 Secure Kernel syscall/exception-entry region. Addresses are
Ghidra cl4_kernel.raw ground truth; all names are estimates (see manifest).

## [sk] 0033a3d0 sk_syscall_varlen_write
Observation: Variable-length field writer traps with a software breakpoint
(SoftwareBreakpoint(1, 0x33a5c8), "does not return") on size class 3 of the
encoded field, and on the overflow path (offset not < 4) branches to
FUN_00358e40 / FUN_00352900.
Evidence: decompile of FUN_0033a3d0: `switch(uVar11){ case 3: ... SoftwareBreakpoint(1,0x33a5c8); }`; writes 1-4 byte payloads into a caller buffer at unaff_x19+off.
Severity (hypothesis): medium — a malformed capability-size field reaching the
breakpoint would fault the calling vCPU/thread; the offset is bounded
(off+0x10 < 0x19 check) but the write itself is to an unvalidated caller buffer.
Confidence: low (decompiled, callee bodies not yet reconstructed; buffer provenance unverified).

## [sk] 0034020c sk_cap_lookup
Observation: Capability lookup traps (SoftwareBreakpoint(1, 0x34033c), "does not
return") on size class 3 when decoding a variable-length capability-size field,
and returns a queue-completion result when the size exceeds 0xfff.
Evidence: decompile of FUN_0034020c: `case 3: pcVar4 = (code *)SoftwareBreakpoint(1,0x34033c); (*pcVar4)();`; `if ((uint)uVar5 < 0x1000) ... else { uVar6 = FUN_000839f8(); }`.
Severity (hypothesis): medium — untrusted capability size fields reaching the
breakpoint fault the kernel path; the 0x1000 threshold gates the fallback path.
Confidence: low (register aliasing; exact callers unknown).

## [sk] 0033af48 sk_encode_varlen
Observation: Variable-length field encoder enforces a buffer bound: rejects
when `(base & 0x1000f8) != 0 || 0x18 < off + 1`, returning an error path; on the
valid path writes at buf+off after a 1-4 byte width check.
Evidence: decompile of FUN_0033af48: `if ((*(uint *)(extraout_x8 + 0x50) & 0x1000f8) != 0 || 0x18 < unaff_x20 + 1U) { ...FUN_0035556c...; return ...; }`; width switch on (off & 3).
Severity (hypothesis): low/medium — the offset is validated (< 0x19) before the
write, which bounds the buffer; the flag/value read of *extraout_x1 (unrecovered
source pointer) is unverified.
Confidence: low.

## [sk] 00340a2c sk_cap_resize
Observation: Capability resize validates the object path (sk_object_lock on
param_4+0x10/+0x18), clamps the size to >= 0x1000, and branches on the 0xfff
threshold to an error path (FUN_0007c1c4 + FUN_000839d8) when the current size
exceeds 0xfff. Writes a delta and flag byte into a caller buffer.
Evidence: decompile of FUN_00340a2c: `uVar2 = 0x1000; if (uVar3 < 0x1001) ...`; `if (0xfff < uVar3) { FUN_0007c1c4(); FUN_000839d8(); return; }`.
Severity (hypothesis): medium — a size-mismatch between the capability object
and the requested resize could allow a partial/incorrect resize; the object
path is locked and the 0xfff bound gates the fast path.
Confidence: low (register aliasing; size semantics inferred).

## [sk] 0033d948 sk_encode_varlen_field
Observation: Variable-length field writer encodes a length tag byte followed by
a 1-4 byte little-endian payload for values >= 2, using the offset position
(uVar5 = pos < 4 ? 1-3 bytes : full word) to pick the width.
Evidence: decompile of FUN_0033d948: writes tag char `'\x02'`/`'\x02'+(i>>8)` and
payload via `*(char*)param_1` (pos<4) or `*param_1` (full word).
Severity (hypothesis): low — encodes caller-provided value; write width chosen
from the field position, matching the decode side (sk_cap_lookup3).
Confidence: low.

## [sk] 0033c5cc sk_cap_free_dispatch
Observation: Capability free dispatches on a tag byte; tags 5-0x10 delegate to
FUN_000026e8, tag 0x12 frees the +0 object and +0x20 metadata, other tags free
metadata at +0x10/+0x20; tags 1-4/10-0xe return without freeing.
Evidence: decompile of FUN_0033c5cc: switch on `*(byte*)(param_1+8)` with
`case 5..0x10: FUN_000026e8(param_1); return;` and `case 0x12: FUN_0036b118(...);`.
Severity (hypothesis): low — the tag-driven free dispatch determines what is
released; if the tag is attacker-controlled, an inconsistent free (double-free /
partial free) is possible. Caller provenance unverified.
Confidence: low.

# Security findings — cL4 Secure Kernel slice 09 (0x3442a8-0x348034)

Slice 09 is the syscall/exception-entry dispatch region: ~206 thin wrapper
functions that read the saved trap register frame (unaff_x20 = sk_trap) and
forward to shared cL4 kernel handlers (reconstructed in sibling slices).
The security-relevant logic here is the shared fault/overflow/refcount
helpers and the region permission checks the wrappers invoke.

## [sk] 00346bdc thunk_FUN_0036b270
- **Observation**: Object refcount retain is a compare-and-swap loop that treats a
  refcount of -1 as "object freed" and returns the object base WITHOUT touching
  the slot; any concurrent change during the CAS falls back to the slow path
  (FUN_0039f9e8). The increment quantum is 0x200000000 per retain.
- **Evidence**: `if (0 < (long)param_1) { base = param_1 & ~7; slot = base+8; cur = *slot;
  do { nxt = cur + 0x200000000; if (nxt < 0) { if ((int)cur == -1) return base;
  return FUN_0039f9e8(slot, cur, 1); } } while (*slot != cur); *slot = nxt; }`.
  `-1` sentinel and CAS loop are exact.
- **Severity (hypothesis)**: medium — a refcount reaching -1 (double-free / over-release)
  silently short-circuits the retain instead of faulting, so a UAF on a freed
  object could persist if the caller relies on retain to reject freed objects.
- **Confidence**: high (logic direct from decompile).

## [sk] 00346c5c / 00346c60 thunk_FUN_002d3c28 / thunk_FUN_002d4a64
- **Observation**: 128-bit capability/region arithmetic is checked: add faults on
  signed carry of the high word OR unsigned carry of the low word with a
  non-wrapping high sum; subtract faults on signed borrow. On fault the kernel
  calls FUN_003488bc(1, lo-result) and enters a noreturn panic chain
  (FUN_00349d58 / FUN_001afe4c). This is fail-closed integer-overflow protection
  in the object/region size path.
- **Evidence**: `if (!scarry && (!carry || hi+hi != INT64_MAX)) return;` (add),
  `if (lo_a < lo_b) { if (hi-hi != INT64_MIN && !sborrow) return; } else if (!sborrow) return;` (sub),
  then `FUN_003488bc(1, lo)` + noreturn.
- **Severity (hypothesis)**: informational — fail-closed bounds discipline; a
  logic error here would allow 128-bit overflow in cap math (memory-safety).
- **Confidence**: high.

## [sk] 003448d4 sk_dispatch_3448d4
- **Observation**: Before draining an object range, the kernel validates the
  object header's permission word (header+0x50) against the low tag byte AND'd
  with the requested permission; a mismatch faults (FUN_003488bc(1) +
  FUN_00349644, noreturn). The element stride (header+0x48) must be non-zero or
  the kernel faults (FUN_00348074(1) + FUN_00351be0). No silent default on
  invalid permissions.
- **Evidence**: `if ((*(uint*)(hdr+0x50) & tag & 0xff) != 0) goto perm_fault;`
  and `if (stride == 0) goto stride_fault;`, both ending in noreturn panics.
- **Severity (hypothesis)**: informational — per-region permission + stride
  enforcement before bulk object iteration (fail-closed).
- **Confidence**: medium (header layout is estimated).

## [sk] 0034454c sk_dispatch_34454c
- **Observation**: The long list-drain syscall handler faults (noreturn
  FUN_00351094/FUN_001afe4c) when the resolved base at frame+0x30 is negative,
  and faults when an element-list slot is empty or shorter than 8 bytes
  (FUN_003488bc(1)/FUN_00349644). It also ORs 0x80000000 / 0x40000000 tag bits
  into the element word based on the list-head mode bytes (frame+0x48/+0x50
  +0x10/+0x11), steering dispatch.
- **Evidence**: `if (lVar9 < 0) { FUN_003483c4(); ... noreturn }`;
  `if (plVar7 == 0 || (u8_hi - u8_lo) < 8) goto elist_fault;`; tag OR
  `u12 | 0x80000000` / `| 0x40000000` gated on mode bytes.
- **Severity (hypothesis)**: informational — negative/short list heads are
  treated as faults, not dereferenced (defense against malformed frame state).
- **Confidence**: medium (dense register artifacts, but the guards are direct).

## [sk] 00347200 thunk_FUN_002b3978
- **Observation**: Capability descriptor type is sourced from param_2 bits 56-59
  when param_2 bit 61 is set, else from param_1; the returned pair's low word is
  hard-coded 0xf and the high word carries the rights tag (0x7 or 0xb) OR the
  type shifted left 16. The type field is masked to 4 bits before it is placed.
- **Evidence**: `if (p2 & 0x2000000000000000) typ = (p2>>0x38)&0xf;` and
  `return {lo:0xf, hi: mode | typ<<0x10}` with `typ` masked to 0xf.
- **Severity (hypothesis)**: low — 4-bit type mask caps the descriptor type
  space, so an over-wide type value cannot alias into the rights field.
- **Confidence**: high.

## [sk] 003471d8 thunk_FUN_002298d4
- **Observation**: 64-bit hash-mixer compression (Skein/Threefish-style) folds an
  injected word into a 5-word state with a per-block counter increment
  (0x800000000000000). This is the hash core used for capability/object
  integrity; no security issue observed, but the counter-add is part of the
  authenticated hash state.
- **Evidence**: `u3 = (s0 & 0xff00000000000000) + 0x800000000000000; state[0]=u3;`
  plus ROTR/ROTL xors on state[1..4].
- **Severity (hypothesis)**: informational.
- **Confidence**: medium (recognized mixer structure).

# SK slice 10 findings — 0x348074-0x349abc (syscall/exception-entry region)

Slice 10 of the SK range is a dense cluster of Swift-runtime support helpers
for the cL4 kernel's syscall/exception-entry area: no-op stubs (81), "Fatal
error" result constructors (30), fatal-message accessors (19), Swift type
metadata getters (16), inout/result-buffer accessors, stack-alloca helpers,
and a handful of trivial leaf/wrapper functions. No actual syscall argument
validation, capability/privilege checks, or bounds arithmetic is present in
these 205 functions; they are runtime glue, not dispatch logic.

## [sk] 0x348074 sk_fatal_error_result_01 — fixed {message, code} error pack
- Observation: A 16-byte result is built as {lo = &"Fatal error", hi = 0xb}.
  30 identical constructors and 19 string-pointer accessors all reference the
  same literal s_Fatal_error_005accd0 with code 0xb.
- Evidence: decompiles FUN_00348074..FUN_003484b4 all emit `_0_8_=s_Fatal_error_005accd0;
  _8_8_=0xb`.
- Severity (hypothesis): informational. This is the cL4 kernel's standard
  "Fatal error" error-pack; code 0xb is the seL4 error kind surfaced on
  unrecoverable trap/syscall failure.
- Confidence: medium.

## [sk] 0x348758 sk_fatal_codable_58 / 0x349190 sk_fatal_existcoll_90 — noreturn Swift traps
- Observation: Two noreturn Swift runtime fatal-error traps sit in the syscall
  region. FUN_001afa84 (Swift runtime fatalError) is invoked with code 0xb and
  the type names "Swift.Codable" / "Swift.ExistentialCollection", carrying
  `idx | 0x8000000000000000` (a tagged/flag value) in the payload.
- Evidence: WARNING: subroutine does not return; strings
  s_Swift_Codable_swift_005ce990 and
  s_Swift_ExistentialCollection_swif_005cf680 matched.
- Severity (hypothesis): low. If these precondition traps are reachable from
  attacker-controlled metadata/type fields they become a kernel-crash / DoS
  primitive; more likely they fire only on internal type-system invariant
  violations.
- Confidence: low.

## [sk] 0x3496b0 sk_bitset_insert_byte — bit-lane field insert
- Observation: `(uint64_t)*byte << (shift & 0x38) | value` inserts a byte into
  one of 8 lanes of a 64-bit word. `shift & 0x38` constrains the shift to
  0..56 in 8-bit steps, so no shift-out-of-range occurs.
- Evidence: decompile FUN_003496b0.
- Severity (hypothesis): none — the mask prevents out-of-range shifts.
- Confidence: medium.

# SK slice 11 (0x349ae0-0x34aef4) — security findings

Region nature: a pool of compiler-emitted Swift-runtime glue and small utility
stubs (no-op stubs, constant returns, pointer getters, frame-bias stores,
Swift fatalError traps, 9-byte copy helpers). It contains NO cL4 syscall
argument validation, capability, or privilege-checking logic. Only two
observations below; both are low-severity notes on shared helpers, not
exploitable syscall surfaces.

## [sk] 000034a018 sk_insn_bitfield_builder
- Observation: Function reads two bytes at a caller-supplied pointer offset
  (bytes 1 and 2) with no bounds or null check before packing them into a
  descriptor word. The pointer is not validated.
- Evidence: decompile `(*(byte*)(p+1) & 0x3f) << 12 | (*(byte*)(p+2) & 0x3f) << 6 |
  (hi4 & 0xf) << 18` — direct dereferences of `p+1`/`p+2`.
- Severity (hypothesis): Low — generic field-packing helper; correctness of the
  caller's pointer is assumed, no privilege boundary crossed here.
- Confidence: medium

## [sk] 000034ab30 sk_runtime_release_dispatch
- Observation: Function dereferences caller-supplied object fields at offsets
  +0x18 and +0x20 and passes them to two release/teardown helpers
  (FUN_0006a4c0, FUN_000a649c) without validating the object pointer or field
  values. A malformed object could drive teardown on attacker-chosen values.
- Evidence: decompile `uVar1 = *(p+0x20); FUN_0006a4c0(p, *(p+0x18)); FUN_000a649c(uVar1)`.
- Severity (hypothesis): Low — object is expected to be a valid kernel object;
  no untrusted-pointer path identified at call sites in this slice.
- Confidence: low

## [sk] region note: Swift fatalError traps
- Observation: FUN_00349eb8 ("load from misaligned raw pointer" on
  UnsafeRawPointer) and FUN_0034a238 ("Attempting to access Dictionary e" on
  NativeDictionary) are noreturn Swift fatalError trap emitters. They terminate
  execution on runtime type/alignment contract violations; not reachable as a
  privilege boundary from this slice's context.
- Evidence: decompiles call FUN_001afe4c (noreturn) with the quoted Swift
  runtime message strings (0x5cf180 / 0x5cf210) and type names
  (0x5cf1b0 / 0x5be800).
- Severity (hypothesis): Informational.
- Confidence: high

# SK region syscalls — Slice 12 findings (0x34af04-0x34c034)

Region: dense table of small per-syscall stub/handler entry points in the cL4
syscall/exception-entry region. Worker SkWave7.SkP12. Confidence per function
recorded in the manifest fragment (/tmp/sk_manifest_part12.json).

## [sk] 0x34af04-0x34c034 no-op syscall handler slots
Observation: 141 of the 205 decompiled entry points in this region have empty
bodies (`void F(void){ return; }`) — the decompiler reports no observable side
effect for them.
Evidence: decompile_function for e.g. 0x0034af20, 0x0034af30, 0x0034af48 …
(141 addresses) all yield an empty body; the region sits in the syscall-table
area immediately before the syscall string tables at 0x4e3240
("CapSyscalls EpSyscalls EcSyscalls … HypercallSyscalls Costs").
Severity (hypothesis): Medium — if any empty slot is wired into a live syscall
dispatch index, invoking it would return "success" without performing an
operation (silent no-op / privilege-assume-success surface). Whether the slots
are reachable is unconfirmed from this region alone.
Confidence: Medium

## [sk] 0x34af04..  argument-dropping wrapper stubs hide validation
Observation: many non-empty slots are thin wrappers whose decompiled bodies
call out-of-slice helpers with arguments the decompiler dropped (e.g. the
repeated `FUN_00310ad4(); FUN_00027754();` tagged-pointer deref pair and the
`unaff_*` register-dependent bodies), so no argument validation (capability,
bounds, tag-bit) is visible in this region.
Evidence: 12 `sk_degen_frame_op` functions reference only `unaff_*/in_*`
operands; ~30 `sk_callee_call_*` wrappers call helpers with `0` substituted for
dropped args; FUN_00310ad4/FUN_00027754 (out of slice) are tagged-pointer
deref resolvers (low-bit tag checks at +0x10/+4 or +0x20/+8).
Severity (hypothesis): Low — validation likely lives in the out-of-slice
callees; this is a completeness gap for security review of this region, not a
confirmed flaw.
Confidence: High (that the gap exists), Low (that it is exploitable)

## [sk] 0x0034b9a0 callback/notifier registration (sk_callback_register)
Observation: this handler resolves a value via helpers 0x0008f6c0/0x0008f6f4
then calls 0x00377824 with a zero selector, the resolved value, an argument and
TWO function pointers (0x0060e3fc, 0x0060e40c) — i.e. it registers callback /
handler pointers into a dispatch structure.
Evidence: decompile_function 0x0034b9a0:
`FUN_0008f6c0(arg3); u=FUN_0008f6f4(); FUN_00377824(0,u,arg2,FUN_0060e3fc,FUN_0060e40c);`
Severity (hypothesis): Medium — if either callback pointer is caller-controlled
(not fixed kernel addresses) this is an indirect-call / CFI surface; the two
pointers here are constants, so it is currently the kernel's own callbacks.
Confidence: Low (exploitability), High (that pointers are registered)

# SK Slice 13 findings (0x34c044-0x34d054, syscall/exception-entry region)

Template: `## [sk] <address> <estimated_name>` + Observation / Evidence / Severity (hypothesis) / Confidence.

## [sk] 0034c7c4 sk_handle_from_obj
- Observation: Builds a 16-byte capability/object descriptor with a hard-coded low tag of 0x13f (319) and the object word at offset +0x10. If 0x13f is a capability-type/privilege tag, any caller can mint a descriptor of that type regardless of entitlement.
- Evidence: decompile `auVar1._8_8_=*(param_1+0x10); auVar1._0_8_=0x13f;` — constant tag + object-derived high word; ~20 callers in the 0x32-0x34 vspace/PT region.
- Severity (hypothesis): low-medium (unknown tag semantics; no argument validation observed in this helper itself).
- Confidence: low (tag meaning not confirmed against a header/string).

## [sk] 0034cd90 sk_obj_5word_copy
- Observation: Copies a fixed 5-word (40-byte) block from a source template into a destination object and writes the destination pointer out through a caller-provided output pointer. No length parameter and no bounds check: a short destination buffer or mis-sized object would be over-written.
- Evidence: decompile `*unaff_x19=(long)param_1; param_1[0..4]=unaff_x20[0..4];` (five 8-byte word copies, no guard).
- Severity (hypothesis): low (internal kernel-only copy; 4 callers).
- Confidence: low (no caller context confirming attacker-controlled sizes).

## [sk] 0034cdb4 sk_byte_copy
- Observation: Unchecked single-byte copy source->dest; no null/length validation. A bad pointer from any caller yields a kernel fault.
- Evidence: decompile `*param_1 = *param_2;` (one byte, unconditional). 14 callers including the 0x45 nested-VM region.
- Severity (hypothesis): low.
- Confidence: low.

## [sk] 0034cec4 sk_encode_tag_field
- Observation: Encodes a descriptor/tag word from `(flags&0xf)<<12 | (byte[base+1]&0x3f)<<6` without validating either input. If `base` is attacker-controlled, the byte read at base+1 is an out-of-bounds read; the flags nibble is inserted into bits 12-15 unchecked.
- Evidence: decompile `return (param_2&0xf)<<0xc | (*(byte*)(param_1+1)&0x3f)<<6;` — 18 callers.
- Severity (hypothesis): low-medium (depends on caller-supplied `base` provenance; not validated here).
- Confidence: low.

## [sk] 0034c764 sk_copy_9byte
- Observation: Copies 8 bytes plus a 1-byte tag between 8-byte-aligned addresses using `& ~7` alignment masking on both source and destination. Masking aligns both operands down, so the copy can read/write up to 7 bytes before a misaligned base — a potential over-read/over-write if callers pass misaligned or near-boundary pointers.
- Evidence: decompile copies `*(dst & ~7)` (8 bytes) and `*(dst&~7 +1)` (1 byte) from `*(src&~7)`; 5 callers in the 0x33 region.
- Severity (hypothesis): low (alignment mask is intentional; impact only on misaligned callers).
- Confidence: low.

## [sk] 0034ca7c sk_log_fault
- Observation: Logging helper called with a zero code plus two word operands read from a caller object at +0x20/+0x10 and two data pointers. If the object pointer is untrusted, reads at +0x10/+0x20 are attacker-influenced and may leak or fault.
- Evidence: decompile `FUN_00377824(0, *(param_3+0x20), *(param_3+0x10), &DAT_00611b24, &DAT_00611b3c);` — 3 callers in 0x33.
- Severity (hypothesis): low (diagnostic path; object provenance internal).
- Confidence: low.

Note: 183 of 206 functions in this slice decompile to empty bodies (bare return), constant-0/0xff returns, or single-call thunks; these are padding/landing-pad stubs or unimplemented handler slots and carry no additional security surface beyond the above.

# SK slice 14 findings (0x34d070-0x34dff4)

## [sk] 0x0034d0a0 sk_fatal_error_stub
- **Observation**: Noreturn Swift fatal-error reporter raising "Fatal error" with
  Swift.Duration type metadata; flags 0xe000000000000000, line 0x14, code 2.
- **Evidence**: decompile calls FUN_001afa84 with s_Fatal_error_005accd0,
  s_Swift_Duration_swift_005d0db0.
- **Severity (hypothesis)**: low (error-reporting path; no privilege boundary).
- **Confidence**: high (string-matched).

## [sk] 0x0034d708 sk_cannot_initialize_stub
- **Observation**: Init-failure abort reporting "Cannot initialize"
  (s_Cannot_initialize_005ce9b0, len 0x12) via noreturn FUN_001a89a8. Reachable
  from object/runtime initialization failure.
- **Evidence**: decompile FUN_001a89a8(s_Cannot_initialize..., 0x12, 1).
- **Severity (hypothesis)**: low (abort path, no validation logic).
- **Confidence**: high (string-matched).

## [sk] 0x0034d744 / 0x0034dac8 sk_pair_ret
- **Observation**: Thunks return a {&DAT_004c1010, 0x100} metadata descriptor pair.
  DAT_004c1010 is a zeroed 16-byte region; hi=0x100 is exposed as a size/count to
  callers without bounds validation at this site.
- **Evidence**: decompile returns raw {ptr,0x100} pair.
- **Severity (hypothesis)**: low (static constant; caller-side bounds not in slice).
- **Confidence**: medium.

## [sk] 0x0034dcfc sk_pair_ret_34dcfc
- **Observation**: Returns {0x656120, &DAT_004e7f10} type-metadata pair.
  DAT_004e7f10 region decodes as Swift type metadata ("Bool"/"Str" strings).
- **Evidence**: read_memory of 0x4e7f10 shows type-name table bytes.
- **Severity (hypothesis)**: low (metadata constant; no validation).
- **Confidence**: medium.

## [sk] 0x0034dc6c sk_pair_ret_34dc6c
- **Observation**: Returns {x21+0x10, 0x80000000005cfbb0} pair; the hi half is a
  non-canonical pointer-with-tag 0x80000000005cfbb0. Callee-saved x21 is returned
  unvalidated as a pointer.
- **Evidence**: decompile auVar1._8_8_=0x80000000005cfbb0, auVar1._0_8_=x21+0x10.
- **Severity (hypothesis)**: low (register-bound artifact; likely Swift metadata).
- **Confidence**: low.

## [sk] 0x0034de44 sk_syscall_constff_34de44
- **Observation**: Returns constant 0xff (all-ones byte) — an error/sentinel value
  returned unconditionally from a syscall-dispatch slot.
- **Evidence**: decompile `return 0xff;`.
- **Severity (hypothesis)**: low (stub returning fixed error; no data exposure).
- **Confidence**: medium.

## [sk] region-wide: stack-spill prologue fragments
- **Observation**: Many functions in 0x34dxxx decompile to Ghidra stack-spill
  prologue fragments (in_x9/in_x12 -> frame) or pure no-ops. These are
  syscall-dispatch placeholder slots whose real bodies are unrecovered
  (PAC/stack-protector or shared-table stubs). No argument validation, capability
  checks, or bounds logic is visible in this slice.
- **Evidence**: 137/205 bodies are `return;`, 16/205 return 0, 9 are stack-spill
  prologue fragments, remainder thin forwarders.
- **Severity (hypothesis)**: informational — the actual syscall validation
  logic for this dispatch region is not present in this address slice.
- **Confidence**: medium.

# SK slice 15 findings (syscall/exception-entry region 0x34e004-0x34efa8)

## [sk] 0x34e004-0x34efa8 (region) syscall dispatch table with large no-op/ret0 surface
Observation: The contiguous slice 0x34e004-0x34efa8 is a dense syscall-dispatch
table (206 entries at ~0x10 spacing). 145 entries are bare `ret` no-ops
(`sk_syscall_stub_*`) and 13 entries return literal 0 (`sk_syscall_ret0_*`).
A further 21 are stack-frame fragments (`sk_frag_*`) referencing the caller's
frame pointer (unaff_x29), consistent with Ghidra over-segmenting a dense
instruction stream rather than true standalone functions.
Evidence: decompile_function for each address in /tmp/sk_part15.txt; e.g.
0x34e014/0x34e024/... -> `void FUN(void){ return; }`; 0x34e0a4/0x34e414/... ->
`undefined8 FUN(void){ return 0; }`; 0x34e850/0x34e8b8 -> 16-byte pair built
from `param_1 + reg + reg & ~reg` with unaff registers.
Severity (hypothesis): low — if any of these return-0 slots are reachable
syscall handlers, unimplemented operations would be silently accepted as
success instead of returning an error, which could mask privilege/capability
denial. No argument validation is performed anywhere in this slice.
Confidence: medium (behavior of each stub is exact; the "unimplemented syscall
slot" interpretation is inferred from the syscall-dispatch region context and
the 0x4e3xxx string-table region referenced by the getters).

## [sk] 0x34e830 (sk_frag_e830) record/bitmap setup without bounds check
Observation: Writes 5 fields (offsets 8,0x10,0x18,0x20) through a caller
supplied pointer with a conditional 64-bit mask shift; no length/capacity
validation is present in the fragment.
Evidence: decompile: `*(param_1+8)=param_2; *(param_1+0x10)=in_x11;
*(param_1+0x18)=0; *(param_1+0x20)=in_x10 & in_x12;` with conditional
`if ((ulong)-in_x9 < 0x40) in_x10 = ~(in_x10 << (-in_x9 & 0x3f))`.
Severity (hypothesis): low — fragment is part of a larger handler; cannot
assess bounds without the surrounding function.
Confidence: low (fragment only).

## [sk] 0x34e178 / 0x34e1b0 (sk_vtable_dispatch_*) indirect method dispatch
Observation: Dispatches through an object vtable method slot at (*(obj-8)+0x30)
(FUN_000839f8). The target is an indirect call; if `obj` is attacker-influenced
this is an arbitrary-function-pointer jump surface.
Evidence: decompile of FUN_000839f8: `(**(code **)(*(long *)(param_3 + -8) + 0x30))();`
called from 0x34e178 and 0x34e1b0.
Severity (hypothesis): low — standard virtual-dispatch; relies on the caller
validating `obj`. Not verified here.
Confidence: low (callee is out of range; body reconstructed by its worker).

# SK slice 16 findings — 0x34efb8-0x350038 (syscall/exception-entry)

Security-relevant observations from decompiling slice 16 of the cL4 Secure
Kernel syscall region. Findings are hypotheses; all names/addresses from
Ghidra cl4_kernel.raw.

## [sk] 0x0034f6a8 sk_swift_fatal_grapheme
Observation: Fatal-error path invoked with a user/context-supplied value
(`param_1 | 0x8000000000000000`) folded into the error-detail argument of the
noreturn Swift fatal-error routine FUN_001afa84.
Evidence: `FUN_001afa84(s_Fatal_error_005accd0, 0xb, 2, 0xd000000000000034,
param_1 | 0x8000000000000000, s_Swift_StringGraphemeBreaking_swi_005d3570, 0x22, 2)`.
Severity (hypothesis): Low — error reporting, no privilege boundary crossed.
Confidence: medium.

## [sk] 0x0034fa9c sk_swift_precondition
Observation: Precondition-failure trap that aborts the kernel (noreturn) when
a caller-supplied precondition is violated; the argument `param_1` is only
captured to the stack and not validated.
Evidence: `FUN_001afa84(s_Precondition_failed_005ce2d0, 0x13, 2, 0,
0xe000000000000000, s_Swift_FloatingPointToString_swif_005d33c0, 0x21, 2)`;
`uStack... = param_1` then noreturn.
Severity (hypothesis): Low — abort path, expected kernel-terminating behavior.
Confidence: medium.

## [sk] 0x0034f138 sk_obj_twin_call
Observation: Two indirect dispatch calls via the jumptable routine
FUN_000839f8, where the target is derived from `param_1` masked by `~unaff_x23`
(`param_1 + unaff_x19 & (unaff_x23 ^ ~0)`). The indirect call target is
computed from caller-controlled/register values with no explicit validation.
Evidence: two `FUN_000839f8(param_1 + unaff_x19 & (unaff_x23 ^ -1), 1)` calls;
FUN_000839f8 itself decompiles as `(**(code **)(*(long *)(param_3 + -8) + 0x30))()`
with a "Could not recover jumptable ... Too many branches" warning.
Severity (hypothesis): Medium — indirect-call target derived from masked
register input; if an attacker can steer the mask/offset this is a potential
control-flow-integrity concern (consistent with Swift witness/vtable dispatch).
Confidence: low (unaff registers obscure the actual bounds).

## [sk] 0x0034fa78 sk_bit_clear_indexed
Observation: Bit-clear into a table slot indexed by `unaff_x21 >> 3` with no
explicit bounds check on the index (`unaff_x21 & 0x3f` selects the bit).
Evidence: `*(ulong *)(unaff_x19 + (unaff_x21 >> 3 & 0x1ffffffffffffff8)) &=
~((1 << (unaff_x21 & 0x3f)) - 1)`.
Severity (hypothesis): Medium — unchecked table index into a kernel data
structure; if `unaff_x21` is not pre-validated this could corrupt an adjacent
slot (out-of-bounds write).
Confidence: low (index source register unidentified).

## [sk] 0x0034f7ec sk_store_alloc
Observation: Writes `param_1` into `param_3+0x18` then allocates from a
fixed metadata region (`sk_alloc_tag(0x66aa10, 0x20, 0xf)`) with no size
validation of the object slot being filled.
Evidence: `*(undefined8 *)(param_3 + 0x18) = param_1; FUN_0036a940(0x66aa10,0x20,0xf)`.
Severity (hypothesis): Low — object field store during construction.
Confidence: low.

# SK slice 17 findings (0x350048-0x350c14)

## [sk] 0x350048-0x350c14 sk_sys_stub_* (no-op syscall handler slot table)
Observation: This 205-function slice is a dense table of syscall/exception-entry
handler slots. The overwhelming majority (172 of 205) are empty no-op stubs
(`return;`) or `return 0` stubs; 31 are tail-call trampolines that forward to
real handlers elsewhere (FUN_00027754, FUN_00310a74, FUN_003109b4, FUN_00310924,
FUN_00310a44, FUN_0008f728, FUN_0031948c, FUN_000a68c4, FUN_000277b8,
FUN_000839f8, FUN_0014ae44, FUN_0016186c) or string-assert entry points
(FUN_001a89a8); and 2 are accessors returning pointers to syscall dispatch
tables (DAT_004e984c, DAT_004e9518, both adjacent to the syscall-name tables at
0x4e3240).
Evidence: batch decompile of all 205 addresses in /tmp/sk_part17.txt; the
decompiled bodies are consistently empty/tail-call; the two table globals
(DAT_004e984c, DAT_004e9518) contain function-pointer tables (e.g. bytes
0x00123548, 0x001264b4, 0x00182bec at 0x4e984c).
Severity (hypothesis): informational — the syscall handling logic is not in this
range; these are entry/dispatch slots. The no-op slots are deny-by-default (safe
unless reachable with a non-null return contract), but a reachable no-op returning
0 where a real handler is expected could silently drop an operation.
Confidence: medium (stub semantics inferred from decompiled empty bodies + table
pointer xrefs; no reachability analysis performed).

# SK region syscalls - slice 18 findings (0x350c20-0x3517c0)

Slice 18 is the ABI argument-marshalling layer of the syscall / exception
dispatch path: each function is a small shim loading syscall arguments from the
preserved save-frame registers (x19-x28) into ABI argument registers, a tiny
setup, or a forward to a shared helper. No privilege/capability checks or
bounds validation appear in this slice itself (that logic lives in the
dispatched handlers). The observations below are hypothesis-level.

## [sk] 0035151c sk_pack_bits
- Observation: Packs two untrusted 32-bit fields into a 32-bit code:
  `(lo & 0x3f) | ((hi & 0x1f) << 6)` (asm: `and w8,w8,#0x3f; bfm w8,w0,#0x1a,#0x4`).
- Evidence: 0035151c disassembly; the mask limits lo to 6 bits (0..63) and hi
  to 5 bits (0..31), i.e. a syscall/IRQ number + sub-field are truncated into
  one word before dispatch.
- Severity: info/hypothesis - the masking is itself a form of validation that
  bounds the fields, but the produced code indexes downstream dispatch tables,
  so an out-of-design hi value (>= 32) is silently discarded rather than
  rejected.
- Confidence: medium.

## [sk] 00350da4 sk_set_bitmask
- Observation: Computes `-1L << (bit & 0x3f)` and stores it through a pointer
  held in a preserved register (x23): `mov x9,#-1; lsl x8,x9,x8; str x8,[x23]`.
- Evidence: 00350da4 disassembly. A full-width power-of-two mask is written to
  a kernel-chosen address. The `& 0x3f` bounds the shift to 0..63, so no shift
  UB, but the destination (x23) and bit index are live-in frame values.
- Severity: low/hypothesis - if the destination pointer or bit index can be
  influenced by the caller (syscall argument path), this is a masked
  arbitrary-width write; the kernel dispatch convention implies x23 is a
  kernel-populated frame slot, so no direct guest control expected.
- Confidence: low.

## [sk] 00351500 sk_mux_attr
- Observation: Selects a memory-attribute field conditionally on bit 57 of an
  incoming word: if `(v & 0x2000000000000000)` set use an alternate register
  value, else extract 4 bits (bits 56..59) of v (asm: `ubfx x9,x25,#56,#4;
  tst x25,#0x2000000000000000; csel x3,x8,x9,eq`).
- Evidence: 00351500 disassembly. The 4-bit field is a canonical ARMv8 memattr
  selector (device vs normal class). If the selecting word originates from a
  guest/syscall argument, the effective memory attribute is chosen by guest
  data - a potential attribute-downgrade / misclassification surface.
- Severity: low/hypothesis; memattr policy enforcement is expected in the
  mapping handlers, not here.
- Confidence: low.

## [sk] slice-wide save-frame arg trust
- Observation: The entire slice forwards the preserved save-frame registers
  (x19-x28) directly into ABI argument registers with no validation, assuming
  the exception-entry trap frame is kernel-populated and therefore trusted
  (e.g. x0=x21;x1=x24, x1=x19;x2=x24, etc.).
- Evidence: slice disassembly (mov-only forwarders); e.g. 00350c20
  `mov x1,x19; mov x2,x24; ret`.
- Severity: info - inherent design assumption of a microkernel syscall-entry
  path; any path that can reach these shims with a guest-corrupted save frame
  would pass unvalidated arguments to the handlers. Worth confirming the
  entry point zeroes/validates the frame before dispatch.
- Confidence: low.

# SK slice 19 findings (0x3517cc-0x352444)

## [sk] 0x00351930 / 0x003519fc / 0x00352304 sk_sysc_retff_* (constant 0xff return)
Observation: Three syscall/exception-region stubs return the constant 0xff
(255) unconditionally with no argument handling. In a cL4/seL4 syscall entry
region this is consistent with an "invalid/unimplemented syscall" error
sentinel emitted before any argument parsing.
Evidence: decompile bodies are exactly `return 0xff;` (FUN_00351930,
FUN_003519fc, FUN_00352304).
Severity (hypothesis): informational — default/fallthrough error path; no
privilege or bounds impact observed.
Confidence: low.

## [sk] frame-pointer helper clones (sk_sysc_read_local_*/sk_sysc_store_local_*)
Observation: The many tiny out-of-line helper clones in this region read and
write caller stack-frame locals at fixed negative frame-pointer offsets
(e.g. *(frame-0x68), *(frame-0xb8)) with no bounds validation. These are
compiler-generated leaf clones that reach into the caller's frame (Ghidra
unaff_x29); no cross-privilege boundary is crossed, but an offset/logic error
in any clone could read or clobber arbitrary caller-stack data.
Evidence: decompiles show raw `*(unaff_x29 + offset)` loads/stores (e.g.
FUN_003517d8, FUN_00351c10, FUN_00351ce8, FUN_00352128, FUN_0035217c).
Severity (hypothesis): informational — internal-only helper clones.
Confidence: low.

# SK slice 20 findings — 0x352450-0x3530d8 (exception-entry trampoline region)

Region characterisation: this whole slice is the cL4 exception/syscall entry
machinery — hand-written ARM64 assembly fragments that save, restore, and
reload registers across exception entry. Most functions are entered by
fall-through/branch (not by `bl`), so the decompiler reports only register
effects (elided to no-op in C). No syscall *argument* validation, capability
check, or bounds logic lives in this region; it is glue for the handlers that
follow. Confidence is low throughout (assembly fragments).

## [sk] 00352f18 pte_install_desc
- Observation: writes a 4-word page-table descriptor block and tail-calls an MMU commit helper (b 0x36986c).
- Evidence: `movk x9,#0xd000,LSL #48 ; stp x0,x9,[x26,#0x20] ; orr x8,x8,#0x8000000000000000 ; stp x8,xzr,[x26,#0x30] ; b 0x36986c`. Desc[5] = `(x9 & 0xffffffffffff) | 0xd000000000000000` (valid + device/translated descriptor bits), desc[6] = `arg0 | 0x8000000000000000` (upper attribute bit).
- Severity (hypothesis): low — descriptor write is register-driven (x26 base) on a trusted kernel path; any PTE content here comes from kernel-controlled inputs, not direct guest/user data. Worth confirming the caller validates the address it installs.
- Confidence: medium.

## [sk] 00352a8c panic_02534_entry
- Observation: unconditional tail-branch to a fatal/panic handler with fixed message and data operands.
- Evidence: `adrp x0,0x656000 ; add x0,x0,#0x208 ; adrp x1,0x4e8000 ; add x1,x1,#0x60 ; b 0x00002534` (FUN_00002534(0x656208, &DAT_004e8060)).
- Severity (hypothesis): informational — a deterministic fatal-path entry, no variable input; used to report a fixed fatal condition.
- Confidence: medium.

## [sk] 003524ec exc_arg_setup (and 0035300c store batch)
- Observation: exception-entry reload path reads saved registers from the exception frame at fixed negative offsets off x29 and re-stages syscall arguments (x0-x7) plus two stack spill slots before returning to the shared dispatch.
- Evidence: 003524ec loads from `[x29,#0x50/#0x60]`, `[x29,#-0xc8/#-0xe0/#-0xe8]`, spills `stp x28,x24,[sp,#0x10]`, `str x8,[sp]`/`[sp,#0x8]`. 0035300c pushes x19-x28 onto the stack at `[sp,#0x40..#0x80]`.
- Severity (hypothesis): informational — these access only the kernel's own exception frame/stack (trusted save area), no user-controlled pointer.
- Confidence: medium.

Note: no other security-relevant pattern (argument validation, privilege check, bounds test) was observed in this slice; it is entirely entry/exit glue. Any validation is expected in the syscall dispatch handlers that this region branches into.

# SK slice 21 findings (0x003530e8-0x00353db8)

## [sk] 0x003532b8 sk_sysreg_classify_descriptor
Observation: Capability-descriptor classification fragment masks the descriptor to 48 bits (`and x8,x0,#0xffffffffffff`), extracts a 4-bit type field from bits [59:56] of the upper word (`ubfx x9,x1,#0x38,#0x4`), and tests the high tag bit `0x2000000000000000` in x1, leaving comparison flags for the caller to branch on.
Evidence: `and x8,x0,#0xffffffffffff | ubfx x9,x1,#0x38,#0x4 | tst x1,#0x2000000000000000 | ret`
Severity (hypothesis): Medium — capability type/tag discrimination gate on the syscall path.
Confidence: Medium (fragment; the consuming branch is in the enclosing dispatcher).

## [sk] 0x003532a8 sk_sysreg_trap_dispatch_panic
Observation: Tail-call into a noreturn trap-dispatch path (`b 0x001afa84`) with a high-tagged descriptor: `x3 |= 0xd000<<48`, `w6=0x13` (19), `w7=0x2`. Constant operands suggest a fixed trap/exception classification routed to a panic-or-dispatch helper rather than a data-dependent target.
Evidence: `movk x3,#0xd000, LSL #48 | mov w6,#0x13 | mov w7,#0x2 | b 0x001afa84`
Severity (hypothesis): Low — fixed routing, no user-controlled target.
Confidence: Medium.

## [sk] 0x003536ec / 0x003536fc sk_sysreg (capability tag select)
Observation: Two near-identical fragments select a 48-bit value (`csel`) conditioned on the high tag bit `0x2000000000000000` in another register (x26 / x24). This is a capability-vs-data selection: the tagged (capability) variant wins when the tag bit is clear (EQ on the tst). Mirrors seL4's capability-word tagging where the tag bit distinguishes cap from untyped data.
Evidence: `and x8,x22,#0xffffffffffff | tst x26,#0x2000000000000000 | csel x25,x8,x25,eq | ret` (and same shape at 0x3536fc with x19/x24)
Severity (hypothesis): Medium — tag-bit-driven privilege/capability selection in the entry path.
Confidence: Medium.

## [sk] 0x00353a90 sk_sysreg_tail_cap_check
Observation: Tail-call into the capability-check helper `FUN_003a25d4` after saving x0->x24, x1->x25 and forwarding x20 as arg0. The helper is a capability validation/translation routine reached on the syscall entry path.
Evidence: `mov x24,x0 | mov x25,x1 | mov x0,x20 | b 0x003a25d4`
Severity (hypothesis): Medium — capability validation boundary; helper body is out of slice (0x3a25d4).
Confidence: Medium.

## [sk] 0x00353ad8 sk_sysreg_tail_vspace_op
Observation: Tail-call `FUN_002a4c98(0, 0xe000000000000000, 0, 0)`: a vspace/MMU operation invoked with a fixed capability argument whose top 4 bits are `0xe`. The constant capability suggests a privileged/root vspace op rather than a caller-supplied cap.
Evidence: `mov x0,#0 | mov x1,#-0x2000000000000000 | mov x2,#0 | mov x3,#0 | b 0x002a4c98`
Severity (hypothesis): Low — fixed capability, no attacker-controlled operand.
Confidence: Medium.

## [sk] 0x00353888 sk_sysreg (bounds/magic-check fragment)
Observation: ORs two masked 64-bit values and tests the result against `-0x7f7f7f7f7f7f7f80`, then materializes `-0x6000000000000000`. The constant test is characteristic of a carry/overflow or sentinel check (0x8080808080808080 pattern) used to detect a field overflow or a magic marker.
Evidence: `and x20,x10,x8 | and x8,x11,x9 | orr x9,x8,x20 | tst x9,#-0x7f7f7f7f7f7f7f80 | mov x9,#-0x6000000000000000`
Severity (hypothesis): Medium — sentinel/overflow detection; outcome consumed by caller's flags.
Confidence: Low (fragment, caller unknown).

# SK findings — slice 22 (0x353dc4-0x354b20)

Region is a table of tiny leaf/accessor helpers plus Swift-runtime-style metadata
accessors (type-name tables at 0x4e7ed8, metadata fn pointers, tagged-object ctors,
precondition traps). Most functions are trivial accessors; only Swift-runtime trap
surfaces are security-relevant.

## [sk] 00354ad4 swift_precond_out_of_range
- Observation: Calls the Swift precondition/fatal-error machinery with the literal
  "because it is outside the representable range" (src 0x5cfbd0) — the integer
  conversion out-of-range trap.
- Evidence: `FUN_001a89a8("because it is outside the representable range", 0x2e, 1)`.
- Severity (hypothesis): LOW — a fatal-abort path, not a privilege boundary; aborts
  the calling context on an out-of-range integer conversion.
- Confidence: medium (string match is high-confidence, security impact low).

## [sk] 00354ae8 swift_precond_abstract
- Observation: Calls the Swift precondition/fatal-error machinery with a diagnostic
  string at 0x5d3bb9 ("Should be overridden..." region) — the abstract-method /
  generic-requirement trap.
- Evidence: `FUN_001a89a8(&DAT_005d3bb9, 2, 1)`.
- Severity (hypothesis): LOW — fatal-abort on an unimplemented abstract member.
- Confidence: medium (string match high-confidence, impact low).

## [sk] 003542dc tagged_ptr_field
- Observation: Unmasks the high tag bits of a pointer (`ptr & 0xfffffffffffffff`)
  then adds 0x20. If the tagged-pointer value originates from untrusted input and the
  low address bits are attacker-controlled, the resulting pointer is dereferenced by
  the caller.
- Evidence: `return (ptr & 0xfffffffffffffff) + 0x20;`
- Severity (hypothesis): LOW — generic Swift/obj tagged-pointer field accessor;
  whether the source value is attacker-influenced is not determinable from this leaf.
- Confidence: low.

## [sk] 003540f4 swift_obj_init_pointervalue
- Observation: Object initializer embeds a "pointerValue" type-name string and a
  metadata function pointer (0x677790). The 128-bit payload (lo/hi) is copied verbatim
  into the object at +0x10/+0x18 with no validation.
- Evidence: payload written unvalidated; metadata fn 0x677790 stored at +0x48.
- Severity (hypothesis): LOW — constructor; validation, if any, happens in callers.
- Confidence: low.

No syscall argument-validation gaps, privilege/capability checks, or bounds issues
were observed in this leaf/accessor-only region.

# SK region syscalls — slice 23 findings (0x354b2c-0x355908)

Slice 23 is dominated by tiny leaf helpers / frame glue / register shims /
constructor stubs. Most (139/205) are bare `ret` leaves. The observations below
come from the non-trivial bodies.

## [sk] 00355090 sk_copy_pair_2 — mixed-width struct field copy
- Observation: copies a 64-bit word at +0x20 then a 32-bit word at +0x28 from
  `src` into `dst` (no bounds check on either pointer; offsets are fixed struct
  offsets, so this is structural, not a length-driven copy).
- Evidence: decompile `*(long*)(dst+0x20)=*(long*)(src+0x20);
  *(int*)(dst+0x28)=*(int*)(src+0x28)`.
- Severity (hypothesis): none — fixed-offset struct copy.
- Confidence: high (no variable length involved).

## [sk] 00355354 sk_bit_from_tag — unchecked shift from byte field
- Observation: `1L << (*(byte*)(base+0x20) & 0x3f)` — a bit is selected from a
  tag byte; the shift is masked to 0x3f, so no UB, but a 0x20/0x24 32-bit field
  read is paired with the shift to form a 16-byte return.
- Evidence: decompile `auVar1._0_8_ = 1L << ((ulong)*(byte *)(param_1 + 0x20)
  & 0x3f)`.
- Severity (hypothesis): informational — masked shift, safe by construction.
- Confidence: high (mask present in decompile).

## [sk] 003556b0 sk_shift_ctor — length expression from a byte shift
- Observation: `FUN_00002534((1L << shift) + 0x3f, in_x4, in_x5)` — a length is
  derived as `(1 << shift) + 0x3f` (a byte -> power-of-two plus slack). If this
  length feeds an allocation/bounds decision, a large `shift` byte would make
  `1L << shift` huge (no mask here, unlike 00355354).
- Evidence: decompile `FUN_00002534((1L << ((long)param_1 & 0x3fU)) + 0x3f, ...)`.
- Severity (hypothesis): low — only shifts a byte value, caller-controlled
  shift could produce a very large size argument.
- Confidence: medium (shift is masked to 0x3f, but the +0x3f slack is constant).

## [sk] 00355720 sk_store_arg_masked — 24-bit truncation of arg
- Observation: stores `param_4 & 0xffffff` (lower 24 bits) into a stack slot —
  a capability/selector field truncated to 24 bits; upper bits silently dropped.
- Evidence: decompile `*(ulong *)(x29-0x48) = param_4 & 0xffffffffffffff`.
- Severity (hypothesis): informational — explicit 24-bit field packing.
- Confidence: medium (bit-width chosen by the field layout).

## [sk] 00354b50 / 00355100 sk_read_prev_word — reads word at base-0x100
- Observation: both accessors read a 64-bit word at `base - 0x100` (a field
  located 0x100 bytes before the base pointer). If `base` is a mis-sized/alloca
  pointer, this is an out-of-bounds read before the object.
- Evidence: decompile `return *(long*)(param_1 + -0x100)`.
- Severity (hypothesis): low — structural field access at negative offset; the
  -0x100 offset strongly suggests a fixed struct layout, not attacker-controlled.
- Confidence: medium (no validation around the access).

# SK slice 24 findings (0x355914-0x356670)

## [sk] 00356530 sk_state_mix
Observation: ARX/ChaCha-style 4-word state-mixing primitive updating state words at base+0x8/+0x10/+0x18/+0x20 using add/rotate/xor.
Evidence: Decompile shows explicit add/ror(x>>n | x<<(64-n))/xor rotations over 4 state words, seeded by a register word (in_x12) and the high byte of the top word. Callers FUN_0022995c / FUN_002299cc extract a small field (bits 56-58) from the state top word to select a shift width before mixing — a variable-width bit-extraction hash.
Severity (hypothesis): low (internal hash/PRNG state mixer; no external input reaches it directly without prior validation by callers).
Confidence: medium.

## [sk] 003559a8 sk_fatal_msg
Observation: Returns the literal "Fatal error" string (s_Fatal_error_005accd0).
Evidence: decompile returns pointer to 0x5accd0; read_memory at 0x5accd0 yields "Fatal error\0". Used by fatal/panic reporting paths.
Severity (hypothesis): informational.
Confidence: high.

## [sk] region character
Observation: The bulk of slice 24 (0x355914-0x356670) is a dense cluster of no-op entry stubs (empty `return;`), saved-register frame load/store helpers, tagged-pointer-aware object-field accessors, and single-callee forwarders to shared field/cpu/alloc helpers (FUN_00310a44, FUN_0008f6c0/f4, FUN_00376820, FUN_003a25d4, FUN_001a89a8). No syscall argument validation, capability checks, or bounds logic is present in this range.
Evidence: all 206 decompiles reviewed; bodies are empty or trivial pointer arithmetic / register moves.
Severity (hypothesis): none — the security-relevant validation lives in the callees (0x31xxxx field accessors, allocator, per-CPU dispatch), reconstructed by other slices.
Confidence: high.

# SK slice 25 findings (0x35667c-0x357424)

## [sk] 0x00356c90 sk_slot_array_insert — unchecked slot-index bitmap/record write
Observation: Writes `1ULL << (param_2 & 0x3f)` into a bitmap word at `(param_3 + 0x38 + (param_2>>6)*8)` and then copies a 5-word (40-byte) record into `*(param_3+0x30) + param_2*0x28`. The index `param_2` selects both the bitmap word and the record slot with no bounds check inside this fragment.
Evidence: Decompile `*(ulong *)(lVar1 + 0x38) |= 1L << (param_2 & 0x3f); puVar2 = *(long *)(param_3 + 0x30) + param_2 * 0x28;` with 5-word copy. Caller FUN_0025c260.
Severity (hypothesis): medium — if `param_2` (a slot/cap index) is attacker-influenced and not validated by the caller, this is an out-of-bounds write into the slot array / its bitmap.
Confidence: medium

## [sk] 0x003571f8 sk_dispatch_indirect — indirect call through a caller-dereferenced record
Observation: `param_1 = *param_1`, then dispatches to FUN_0031e874 with record words [0..7]. The target/arguments are derived from a pointer dereferenced at the call site; the record contents are not validated here.
Evidence: Decompile `param_1 = (undefined8 *)*param_1; FUN_0031e874(*param_1,...,param_1[7]);`
Severity (hypothesis): low-medium — an indirect dispatch into kernel helper with 8 register args; integrity depends on the record being kernel-private.
Confidence: medium

## [sk] 0x00356ecc / 0x00356f44 — user-error emitters on syscall entry
Observation: These call the user-error emitter (FUN_001a89a8) with fixed strings ("value cannot be converted to", len 0x1e; "more", len 5) and flag 1. They sit on the syscall/exception path and encode user-triggerable error conditions into the exception register (bits 0xc000000000000000 / 0x1000000000000000 observed in the emitter).
Evidence: Decompiles `FUN_001a89a8(s_value_cannot_be_converted_to_005cfbb0, 0x1e, 1)` and `FUN_001a89a8(s_more_005d3bd7, 5, 1)`.
Severity (hypothesis): informational — error-path hygiene; no direct memory-safety issue in these stubs.
Confidence: medium

## [sk] slice 25 region — frame-slot accessors & dispatch-table getters (bulk)
Observation: The bulk of this range is tiny tail fragments that read/write a caller's saved frame slots (unaff_x29 offsets) or return pointers into global dispatch/name tables at 0x4e7xxx-0x4ecxxx. These are the register-frame plumbing of a large inlined syscall dispatcher; they hold no independent validation logic.
Evidence: Decompiles `return *(undefined8 *)(unaff_x29 + -0xNN)` and `return &DAT_004exxxx` across ~200 addresses; names in part25.
Severity (hypothesis): none by themselves — correctness depends on the surrounding dispatcher.
Confidence: medium

# SK region syscalls — findings (slice 26: 0x357440-0x358268)

## [sk] 0x00357acc sk_panic_code_13f
- Observation: Calls kernel panic/trace reporter FUN_00310d68 with a fixed
  code 0x13f and a single context word. No return — fatal path.
- Evidence: `FUN_00310d68(0x13f, param_1)`; decompile body.
- Severity (hypothesis): Info — this is the kernel's own error-reporting path,
  not a security boundary by itself, but the 0x13f code may flag a specific
  invariant/validation failure worth correlating with the caller.
- Confidence: medium.

## [sk] 0x00357bd0 sk_panic_noreturn
- Observation: Tail-calls a noreturn panic helper (FUN_001afa84) with no
  precondition or argument validation visible. Reached when some internal
  invariant breaks; the panic path itself carries no privilege boundary.
- Evidence: decompile; callee marked "Subroutine does not return".
- Severity (hypothesis): Info — panic is a defensive path.
- Confidence: high (noreturn callee confirmed).

## [sk] 0x003576dc sk_bswap128
- Observation: 128-bit byte-swap of two 64-bit words (endian conversion),
  likely deserializing a guest/on-wire 128-bit capability or message field.
  If applied to attacker-controlled data, endianness assumptions in the
  caller are the validation surface, not this leaf.
- Evidence: unambiguous bswap sequence (8/16/32-bit mask-shift-or chain +
  half-swap).
- Severity (hypothesis): Info/Low — data-conversion leaf; correctness of
  callers matters.
- Confidence: high (algorithm unambiguous).

## [sk] 0x00357874 sk_align_up_mask
- Observation: `param_2 + ((param_1 + 0x20) & ~param_1)` — rounds up with an
  alignment derived from the value itself. If `param_1` is not a power of two,
  `~param_1` does not produce a clean alignment mask; the result is only well
  defined when callers pass a power-of-two-aligned bound. Unchecked in this
  leaf.
- Evidence: decompile expression.
- Severity (hypothesis): Low (hypothesis) — potential incorrect size/offset
  computation if a non-power-of-two value reaches here; callers should mask
  first.
- Confidence: medium.

## [sk] 0x00357628 / 0x003576c8 / 0x003577a0 sk_cap_slot_size*
- Observation: `(size_field & 0xfffffffffffffff) + 0x20` — masks a capability
  word to its low 52 bits and adds the 0x20 object-header size. The 52-bit
  mask caps the size field; 0x20 is added without overflow check. Large but
  bounded (52-bit) sizes are fine on 64-bit, but a 52-bit value + 0x20 is
  within range; no overflow. This is an object-size computation used by
  allocators/layout code.
- Evidence: decompile expressions at all three addresses.
- Severity (hypothesis): Info — size computation, not a boundary itself.
- Confidence: medium.

## [sk] 0x00357850 sk_shift16_or4
- Observation: `(param_1 << 0x10) | 4` — packs a value shifted left 16 with
  flag bit 2 set. Left shift of a caller value by 16 can discard high bits
  (truncation) — potentially dropping a capability/attribute field. Unchecked
  in this leaf.
- Evidence: decompile.
- Severity (hypothesis): Info — packing helper; caller controls semantics.
- Confidence: medium.

## [sk] 0x00358134 sk_div_shift_store
- Observation: Computes `param_1 / x21` guarded by `x21 != 0` before storing.
  The division is guarded against divide-by-zero, but `x21` (the divisor)
  arrives in a caller-preserved register and is not validated for range —
  a signed long divisor is used. After the guarded divide, `(q << 1)` is
  stored. Reasonable defensive handling.
- Evidence: decompile: `if (unaff_x21 != 0) lVar1 = param_1 / unaff_x21;`.
- Severity (hypothesis): Info — divide-by-zero is guarded.
- Confidence: medium.

## [sk] 0x003581b4 sk_mask_shift_neg1
- Observation: `*dst = -1L << (x26 & 0x3f)` — shift count masked to 6 bits,
  so no UB shift. Masking the shift to 0x3f means the shift is well-defined.
  A shift of 64+ is folded, which is benign here.
- Evidence: decompile.
- Severity (hypothesis): Info — shift count masked; no overflow.
- Confidence: medium.

## [sk] 0x358278-0x358f48 Slice 27 — findings

Slice 27 is a dense run of ~206 tiny leaf helpers on the syscall/exception-entry
path. The vast majority are empty `ret` stubs, register-save shims (store
incoming registers into caller-frame slots), or small structure-copy/accessor
helpers whose operands are caller registers (unmodeled by the decompiler). Few
carry independent security logic. The following are the security-relevant
observations with evidence.

## [sk] 003584d8 sk_size_probe_003584d8
Observation: Reads a size from `*(p1 & ~7)` (unaligned-dereference-tolerant, 8-byte
aligned probe). If the value is below 0x1000 it returns `size+1`, otherwise 0.
The `size+1` result is an unchecked 32-bit truncation of a 64-bit read.
Evidence: `int sk_003584d8(uint64_t p1) { uint64_t sz = *(uint64_t *)(p1 & ~7ULL);
if (sz < 0x1000) return (int)sz + 1; return 0; }` — `(int)` truncation of a value
that can be up to 0xFFF.
Severity (hypothesis): low — helper is a length/size probe; truncation only
matters if callers use the returned int as a length.
Confidence: medium.

## [sk] 00358b60 sk_bitmerge_00358b60
Observation: Merges a 6-bit field from an untrusted byte at `p1+1` with a 5-bit
field of `p2`. Both fields are masked; no validation of `p1` pointer before the
byte read.
Evidence: `return ((*(uint8_t *)(p1 + 1)) & 0x3f) | ((p2 & 0x1f) << 6);`
Severity (hypothesis): low — field extraction; dereference of a caller-supplied
pointer with no bounds check on this leaf.
Confidence: medium.

## [sk] 00358e40 sk_addr_arith_00358e40
Observation: Address arithmetic `((x11+x19) & x12) + x10 + x9` then masked by
`param_1`. The mask on the final result can silently discard high bits of a
computed pointer (potential wrap/alias if used as a canonical address).
Evidence: `uint64_t t = ((/*x11*/0 + /*x19*/0) & /*x12*/0) + /*x10*/0 + /*x9*/0;
return t & mask;`
Severity (hypothesis): low — helper; masking a pointer to a non-canonical width
could produce aliased addresses if the caller trusts it as an address.
Confidence: low.

## [sk] 00358c74 sk_pair_load_00358c74
Observation: Dereferences `*pp` then reads two words at `(*pp + 0x20)` and
`(*pp + 0x30)` — a double-indirect structure field access with no null/bounds
check at this leaf.
Evidence: `uint64_t base = *pp; out[0] = *(uint64_t *)(base + 0x30);
out[1] = *(uint64_t *)(base + 0x20);`
Severity (hypothesis): low — an unchecked second-level dereference; fault
handling depends on callers.
Confidence: medium.

# Slice 28 (0x358f54-0x359c84) findings — cL4 Secure Kernel (GL1)

Security-relevant observations from the syscall/exception-entry thunk table.
Most entries are opaque register-forwarding thunks with no local validation;
the substantive checks live in the out-of-slice syscall engines. Only entries
with direct evidence are logged.

## [sk] 0x00359088 cl4_syscall_build_cap_descriptor
- Observation: Capability/frame descriptor constructed from an opaque register value (in_x9 masked to 48 bits then OR'd with the tagged-pointer constant 0xd000000000000000) with no bounds/validation check visible at this thunk; the low 48 bits are taken as-is from the register.
- Severity (hypothesis): hypothesis
- Confidence: medium

## [sk] 0x003592b0 cl4_syscall_wrapper_b270
- Observation: A mask expression over the register value in_w8 ((in_w8 & 0xf8) ^ 0x1f8) & (in_w8 + 0x10) is passed to the syscall helper FUN_0036b270; the mask appears intended to coerce/sanitise the argument, but no upper-bound check on the transformed value is visible at this thunk.
- Severity (hypothesis): hypothesis
- Confidence: medium

# SK slice 29 findings — 0x359c90-0x35a8bc (syscall/exception-entry machinery)

Region note: slice 29 is dominated by trivial exception-entry stubs (empty
`return;` bodies) and register-passthrough argument-marshaling helpers where
the decompiler dropped the real parameters. Most functions carry no
security-relevant logic at this layer; only the items below have concrete
evidence worth tracking. Confidence is low/medium throughout.

## [sk] 0x0035a81c sk_syscall_a81c_dispatch_record
Observation: Builds a 4-word dispatch record where the word at +0x28 is
`(in_x10 & 0xffffffffffff) | 0xd000000000000000` — a capability/operation
descriptor with a hardcoded 0xd<<60 type tag. The lower 48 bits of the
caller-supplied `in_x10` are folded into the descriptor unchanged, then the
record is dispatched to FUN_0036986c. No range/validation of `in_x10` is
visible at this layer.
Evidence: decompile of FUN_0035a81c (cl4_kernel.raw); callers FUN_001d0100,
FUN_001d01f4.
Severity (hypothesis): low — the tag is fixed and the low bits are plausibly a
validated object index, but if `in_x10` is guest-controlled the 0xd tag could
be forged into a descriptor the dispatch layer trusts.
Confidence: low.

## [sk] 0x0035a334 sk_vector_compare_16
Observation: 8-lane (4x32-bit, two 16-byte operands) unsigned "less-than"
comparison returning nonzero (0xffff) if any lane of one vector is strictly
less than the corresponding lane of the other. Shape is consistent with a
bounds/ordering check over two 128-bit values (e.g. an address-range vs limit
test). If used to gate memory access, an OR-of-lane comparison is only
meaningful when both vectors are laid out identically.
Evidence: decompile of FUN_0035a334 using NEON_umaxv(...,2) to OR the 8
per-lane compare masks.
Severity (hypothesis): low — plausible bounds check; no callers inspected at
this layer.
Confidence: low.

## [sk] 0x0035a808/0x0035a830/0x0035a880 registration helpers
Observation: Each registers a (symbol, data-arg) pair via FUN_00002534 /
FUN_00027614 (DAT_00657588/4f1918, DAT_006575a0/4f1930, FUN_00656240/
DAT_004e8098). These are handler/table registrations; the targets are
out-of-slice so the exact entry being installed cannot be confirmed here.
No argument validation is performed in these thin wrappers.
Evidence: decompiles of FUN_0035a808/830/880 (cl4_kernel.raw).
Severity (hypothesis): informational — registration-time trust decision lives
in the out-of-slice callee.
Confidence: low.

## [sk] 0035ad10 cl4_registry_insert

**Observation:** Insertion into the process-global registration table grows the
slot array and element table with no upper bound; the free-list drain runs
unconditionally when the in-flight counter hits zero.
**Evidence:** `DAT_006c0174 = n + 1` after growing via FUN_0035b2c8 / allocating
via FUN_0035b4b8; deferred frees drained by walking DAT_006c01b0 under a memory
barrier. Growth is load-factor driven (`hash/rem > 3`) — attacker-reachable if
the key space is user-controllable.
**Severity (hypothesis):** Medium (unbounded memory growth, potential DoS).
**Confidence:** medium.

## [sk] 0035b2c8 cl4_small_ht_grow

**Observation:** The element-size exponent `param_2` is used directly to size
the new block (`2L << (param_2 & 0x3f)`); a hostile size exponent yields an
oversized allocation and the caller falls through to a `SoftwareBreakpoint` on
allocation failure.
**Evidence:** `FUN_00010244(2L << (param_2 & 0x3f), slot_w, 0x48dda4ae)`; on
null returns, `SoftwareBreakpoint(1, 0x35b4b8)`.
**Severity (hypothesis):** Low (allocation failure handled by trap, but
arbitrary-size request is unvalidated).
**Confidence:** medium.

## [sk] 00361b18 cl4_string_set_register

**Observation:** Registration of a string key validates every input byte: a
byte whose value is `<= 0x20` (control/space) is rejected (`0xffffffe0 <
*name - 0x20` catches underflow), bounding the accepted charset before the
string is copied and inserted into the hash set.
**Evidence:** `for (i = len; i != 0; i--) if (0xffffffe0 < *name - 0x20) { fail }`;
then `FUN_000101a0(len, ...)` + `FUN_00117cc4(copy, name - len, len)`.
**Severity (hypothesis):** Low (defensive input validation; prevents injection
of control characters into the type-name registry).
**Confidence:** high.

## [sk] 00364020 cl4_type_metadata_encode

**Observation:** The type-metadata encoder resolves and emits nodes for object
fields via a large builtin-name lookup table (0x67afa8..0x67b138); any
unrecognized type pointer returns NULL, and child-type recursion (0x304-0x306,
0x303) has no explicit depth limit.
**Evidence:** Builtin-name table dispatch with default `return 0`; recursive
`FUN_00364020(type[1], ctx)` calls for child types.
**Severity (hypothesis):** Low (unbounded recursion depth on crafted deeply
nested type metadata — potential stack exhaustion).
**Confidence:** low.

## [sk] 00365c38 cl4_cap_op_dispatch_core

**Observation:** The capability-object operation dispatcher selects a handler
by the object type tag and descends the child/next chain to find a matching
object. The 0x202 nested-walk path compares the target/source chain lengths and
can return an error on mismatch, but the generic child-chain descent has no
cycle guard.
**Evidence:** Recursion into `FUN_00365c38(...)` on the resolved child
(`puVar7 = FUN_003a25b8(...)` / `FUN_00374d80(...)`); 0x202 path uses
`FUN_0035eae4` chain walks with bounded comparison.
**Severity (hypothesis):** Medium (a cyclic or adversarial capability chain
could cause unbounded recursion / hang in the op dispatcher).
**Confidence:** low.

## [sk] 00365660 cl4_arena_reserve

**Observation:** Output arena capacity is doubled (`cap = *(arena+0x20) * 2`)
with a floor of `len+1`; the size arithmetic could overflow for very large
`len`, wrapping the capacity to a small value and leading to an undersized
allocation.
**Evidence:** `cap = *(arena+0x20) * 2; if (cap < len+1 || cap-(len+1)==0) cap = len+1;`
then `FUN_000101a0(cap + 8, ...)`.
**Severity (hypothesis):** Low (unsigned overflow on 64-bit sizes requires an
attacker to drive `len` near 2^63).
**Confidence:** low.

# SK slice 31 security findings (0x366f1c-0x3723a0)

## [sk] 0x366f1c sk_msg_parse_registers — descriptor magic/field validation
Observation: Register-context parser validates the message descriptor header (magic 0x301) and per-slot size fields before copying, rolling back written slots on mismatch.
Evidence: decompile FUN_00366f1c — magic check, per-slot validation via FUN_00365c38, rollback loop invoking destructor on failure.
Severity(hypothesis): low (defense-in-depth bounds checks)
Confidence: medium

## [sk] 0x367bf0 sk_validate_msg_desc — descriptor kind allowlist
Observation: Only descriptor kinds 0/0x305/0x203 are accepted for validation; object-id-live flag (bit 0x40000000) forces a capability resolution.
Evidence: decompile FUN_00367bf0 — allowlist check and FUN_00362c34 resolution.
Severity(hypothesis): medium (syscall argument validation gate)
Confidence: medium

## [sk] 0x367438 sk_msg_parse_objref — syscall argument kind validation
Observation: Object-reference parsing accepts only kinds 0x200-0x204 (excluding 0x202) plus 0x305/0; out-of-range kinds rejected.
Evidence: decompile FUN_00367438 — (kind-0x200)<4 && !=2 allowlist.
Severity(hypothesis): low (input validation)
Confidence: medium

## [sk] 0x369f4c sk_access_acquire — access exclusivity fatal
Observation: Thread-local access tracking enforces exclusivity and raises a fatal 'exclusivity violation' on simultaneous conflicting accesses; removal of a missing entry hits a SoftwareBreakpoint.
Evidence: decompile FUN_00369f4c (s_exclusivity_violation) and FUN_0036a158 (SoftwareBreakpoint 0x36a1a0).
Severity(hypothesis): medium (concurrency safety; panic on misuse)
Confidence: medium

## [sk] 0x36aae4 sk_obj_intern_table family — mutex-guarded global tables, OOM panic
Observation: The object-intern tables (0x36aae4/36e878/36ed94/37062c/370f2c/371b58/36fb10) are guarded by a mutex (LOAcquire + FUN_00118164/194) and panic via SoftwareBreakpoint on allocation failure rather than returning an error.
Evidence: decompiles show LOAcquire/LORelease and SoftwareBreakpoint OOM paths (e.g. 0x36aae4, 0x36fb10).
Severity(hypothesis): medium (OOM -> panic; mutex-protected global state)
Confidence: medium

## [sk] 0x36d8a4 sk_prespec_lookup — prespecialization range gate
Observation: The 'Prespecializations library' lookup rejects specialized arguments that fall outside the accepted address range (DAT_006c02f8..310), logging 'Rejecting' and returning no match.
Evidence: decompile FUN_0036d8a4 — range comparisons and s_Prespecializations_library__Reje strings.
Severity(hypothesis): low (type-safety gate)
Confidence: medium

# SK slice 32 findings (0x372534-0x37ffc4)

## [sk] 0x00372a44 sk_desc_copy
- Observation: allocates 0x58-byte descriptor copy with tag 0x59dd9b33; on alloc failure traps via SoftwareBreakpoint(1,0x372c58) rather than returning an error.
- Evidence: FUN_0001062c(...,0x58,0x59dd9b33); SoftwareBreakpoint on rc!=0.
- Severity (hypothesis): low - kernel-internal allocator; no user-controlled bounds.
- Confidence: medium.

## [sk] 0x003743d0 sk_dedup_insert_a
- Observation: unbounded open-addressed dedup table insert; on entry-allocation failure (FUN_0001062c) traps via SoftwareBreakpoint(1,0x374838).
- Evidence: SoftwareBreakpoint(1,0x374838); no error return path.
- Severity (hypothesis): low - kernel-internal dedup; potential DoS if table corrupted.
- Confidence: medium.

## [sk] 0x00374838 sk_dedup_insert_b
- Observation: mirror dedup insert (0x28 entry) also traps via SoftwareBreakpoint(1,0x374d14) on alloc failure.
- Evidence: SoftwareBreakpoint(1,0x374d14); FUN_0001062c(...,0x28,0x59dd9b33).
- Severity (hypothesis): low.
- Confidence: medium.

## [sk] 0x0037d4b8 sk_hashset_insert
- Observation: hash-set insert traps via SoftwareBreakpoint(1,0x37d700) when a bucket index is out of range (param_1[2] <= slot).
- Evidence: LAB_0037d6fc -> SoftwareBreakpoint(1,0x37d700).
- Severity (hypothesis): low; trap implies corrupted table, not attacker-controllable.
- Confidence: medium.

## [sk] 0x00376038 sk_dedup_registry_lookup
- Observation: registry lookup can trap via SoftwareBreakpoint(1,0x376634) on a bad object kind; unbounded rehash on load factor.
- Evidence: SoftwareBreakpoint(1,0x376634) in the insert path.
- Severity (hypothesis): low.
- Confidence: medium.

## [sk] 0x00379eec sk_cap2_tagword
- Observation: capability tag gate (0x80080); functions computing cap offsets honor tag bits. No user-controlled index found.
- Evidence: ((*param_1 ^ 0xffffffff) & 0x80080) gate.
- Severity (hypothesis): low; cap offset decode is tag-validated.
- Confidence: medium.

## [sk] 0x004088d8 sk_drace_check
- Observation: the cL4 data-race detector installs a raw machine-instruction trampoline into memory at runtime (self-modifying code inside the GL1 Secure Kernel). The 16 bytes rendered by Ghidra as 0x3900012a528005ca, 0x54000643fa4d3120, 0x540003e26b16015f, ... are instruction words written via thunk_FUN_00369b04 then executed. In a ring -1 security monitor, in-kernel code mutation is an integrity-sensitive primitive.
- Evidence: FUN_004088d8 writes the 8 constant words and calls thunk_FUN_00369b04(bVar1, msg, &w); on first-detector-mode it then falls into FUN_00116d60 (fatal). Also string "data race detected ... at ..." 0x005dc6ba.
- Severity (hypothesis): medium — runtime code patching is high-value to an attacker who can influence the detector; the fatal path mitigates.
- Confidence: low (Ghidra renders the patched bytes as constants; exact install target not recovered).

## [sk] 0x00409e90 sk_job_build
- Observation: the async job builder writes to what Ghidra flags as a read-only address (ram,0x00657998), with multiple "Read-only address ... is written" warnings. If 0x00657998 is a genuinely read-only page, the writes could indicate a mis-decoded pointer, or an actual RO-page mutation attempt in the GL1 kernel.
- Evidence: Ghidra warnings "WARNING: Read-only address (ram,0x00657998) is written" at three sites in FUN_00409e90; raw instruction words 0xf900143f39008040 / 0x3900803f stored into freshly allocated job storage.
- Severity (hypothesis): low — most likely a decompiler artifact of writing to freshly-allocated heap (the "read-only" tag is stale), but worth confirming the page attributes.
- Confidence: low.

## [sk] 0x004085c0 sk_err_reply_build
- Observation: the L4 error-reply builder invokes the object's stored callback at obj+0x38 with a constructed PermissionInvalid/OperationInvalid error slot. Both paths reach an indirect call through a caller-controlled object pointer; a corrupted obj+0x38 would yield arbitrary indirect call in GL1.
- Evidence: `(**(code **)(param_1 + 0x38))(param_1)` in the PermissionInvalid path and `(**(code **)(param_1 + 0x38))()` in the OperationInvalid path of FUN_004085c0; slot globals s_L4_ErrorCodePermissionInvalid 0x0068a6b8 / OperationInvalid 0x0068a698.
- Severity (hypothesis): medium — indirect dispatch on an untrusted/foreign object pointer; requires the object to be attacker-influenced first.
- Confidence: medium.

## [sk] 0x0040a8d8 sk_job_alloc / 0x0040a9f4 sk_job_alloc2
- Observation: job allocation exposes caller-chosen pointers: sk_job_alloc stores two caller words (p[2], p[3]) then invokes `((void(*)(void))p[2])()` when the CAS callback reports success; sk_job_alloc2 lets the caller select the metadata pointer (type word) used as the CAS target, defaulting to the thread-local cputype.
- Evidence: sk_job_alloc `(*(code *)puVar1[2])()` on flag set; sk_job_alloc2 `pdVar2 = (puVar1 + 2)` when param_1 != 0, else `&__thread_bss.cputype`.
- Severity (hypothesis): medium — arbitrary function-pointer invocation reachable via job alloc if the CAS callback outcome is attacker-influenced.
- Confidence: low (Swift async ABI; callback path not fully recovered).

## [sk] 0x0005ce54 sync_unlock — lock-ownership validation
- **Observation**: The sync-unlock primitive validates that the unlocking thread actually owns the lock before releasing: it compares the lock word's owner tag against the current thread id ((current_thread >> 0xe) XOR lock_word) masked to 0xffffff, and panics ("tried to unlock lock I did not own") on mismatch. A lock that is not owned cannot be released; the release then emits LORelease and either bumps the recursion/semaphore counts or wakes a waiter via the dispatch thunk.
- **Evidence**: sk_f_0005ce54 body: `if ((((uVar2 >> 0xe) ^ uVar3) & 0xffffff) != 0) sk_f_0005b190(0, sk_str_005bc719);` where uVar2=current thread (sk_x_00060524), uVar3=*lock; recursion counter at lock+0xc decremented and +0xe bumped on nested release, else `sk_f_0005dd70(sel, lock, 3, 0)` wake path.
- **Severity (hypothesis)**: low — enforces lock-owner integrity; a bypass would allow cross-thread lock corruption (deadlock / use-after-free on the sync object).
- **Confidence**: high (explicit panic string and owner-tag compare).

## [sk] 0x0005dc8c/0x0005dd70/0x0005d84c/0x0005e0dc xrt dispatch thunks — lazily-initialized global fn-ptr table, indirect call
- **Observation**: Four dispatch entry points lazily initialize a single global function-pointer table (sk_g_006b2690, default image-base table 0x65c560) the first time any is reached, then tail-indirect-call through table+0x08/+0x10/+0x18/+0x20 with the caller's register arguments. The table base is a fixed image-base constant; there is no write of the table pointer from a checked source in this slice (only the null-guard init), so the table's contents are whatever the image carries.
- **Evidence**: sk_f_0005dc8c: `if (sk_g_006b2690 == 0) sk_g_006b2690 = 0x65c560;` then `handler = *(…(uint64_t*)(sk_g_006b2690 + 0x10); return handler(sel,a,b,c,d);`. Siblings dd70(+0x18), d84c(+0x00), e0dc(+0x08) identical pattern. Callers (ce54, d38c, d394, d470, fac0, fad8) pass up to 5 args that are forwarded verbatim.
- **Severity (hypothesis)**: medium — the xrt sync/thread path dispatches through a single global code table; if sk_g_006b2690 (DAT_006b2690) could be corrupted or the table image swapped, every sync/wake/suspend operation would indirect-call attacker-chosen code in GL1. The one-time init mitigates against uninitialized reads but not table tampering.
- **Confidence**: medium (table contents and handler signatures are not recovered from the decompile; only the thunk pattern).

## [sk] 0x0005eec4 thread_create — thread-count cap + TCB allocation bounds
- **Observation**: Thread creation gates the whole path on a 16-bit counter (< 0x400) read from the registry (registry+0x38), refusing to create beyond the cap; the raw TCB is pulled from a free list with an explicit overflow/wrap trap on the tag field (next+0x178 overflow), and the stack-size check traps "Thread stack allocation size" if the computed available bytes exceed 0x1ffff. Failure tallies are kept in per-counter globals (sk_g_006b26a4..bc).
- **Evidence**: sk_f_0005eec4: `if (counter < 0x400) { … }` with `*counter_ptr = counter+1`; `thread = sk_f_0005c0ac()` (free-list pop, traps 0x5c11c on `next+0x178<next` overflow); `avail = (stack_low - stack_top) + stack_size; if (0x1ffff < avail) goto panic_path("Thread stack allocation size…")`. Counter decremented on the decrement: path.
- **Severity (hypothesis)**: low — the 0x400 cap bounds per-registry concurrent threads (prevents TCB/slot exhaustion); the wrap traps close integer-overflow paths on TCB/stack accounting.
- **Confidence**: high (explicit cap constant and overflow guards in the transcription).

## [SK189-ringminus1] 0040d098 sk_task_group_add_child
- **Observation**: The TaskGroup child-add path (0040d098/0040d99c/0040de9c) guards group completion with a CAS'd live-child counter (group+5) under LOAcquire/LORelease and a doubly-linked waiting-task list (group+6). Child result delivery is validated against the record kind: kind 1 ("only errors can be stored by a d..." 0x5dca22/0x5dc9d2) and a NULL waiting task ("Claimed NULL waitingTask!" 0x5dca72) each hit a noreturn fatal. The child result is retained (FUN_0036b270) before storing.
- **Evidence**: traps/panics at 0x40e9e4/0x40e10c/0x40e104; string refs 0x5dca22/0x5dc9d2/0x5dca72; LOAcquire/LORelease around group[5]; waiting-list group[6]; result ring via FUN_0040e258/FUN_0040e2f0.
- **Severity (hypothesis)**: medium — the task-group result store is a shared cross-task data structure; a failure to drain or a race in the waiter list could let a child completion be lost or double-delivered.
- **Confidence**: medium

## [SK189-ringminus1] 0040f9f4 sk_actor_executor_enqueue
- **Observation**: Actor-executor enqueue (0040f9f4) requires a non-NULL job AND non-NULL executor; any null operand aborts with "Incorrect actor executor assumption" (0x5dd036). The dequeue variant (0040faac) returns 0 and the check-enqueue variant (0040fa5c) returns 0xff on null operands rather than aborting. This is a fail-closed guard on the executor ABI: a nil executor can never be enqueued onto.
- **Evidence**: `if ((param_1 != 0) && (param_2 != 0)) {...} else { ...FUN_004ba640(0,0x5dd036) }` for 0040f9f4; `return 0xff` / `return 0` for 0040fa5c / 0040faac.
- **Severity (hypothesis)**: low — defensive precondition; prevents a nil-executor enqueue from corrupting the scheduler. Availability-only if reachable with attacker-controlled nil.
- **Confidence**: high

## [SK189-ringminus1] 0040b724 sk_registry_add
- **Observation**: The continuation registry is a Swift-style open-addressing/chained hash set: inserts keyed by sk_swift_hash8 with load-factor growth (FUN_0037d700) and a SoftwareBreakpoint trap (0x40b96c) when the bucket index exceeds capacity. Every insertion into the registry is thus bounds-checked; a corrupted registry (index out of range) traps rather than over-writing.
- **Evidence**: `if ((ulong)set[2] <= idx) SoftwareBreakpoint(1,0x40b96c)`; node alloc FUN_00111890(0x18); growth when `load_factor * count < size+1`; rehash FUN_0037d700.
- **Severity (hypothesis)**: low — the registry holds outstanding kernel continuations; the bounds trap is defensive, but a collision-chain hash collision could degrade to O(n) lookup (availability).
- **Confidence**: medium

## [sk-sched] 001807a4-00180f90 cL4 upcall dispatch entry (XnuUpcallsV2)
- **Observation**: The 0x180000 region is the cL4 Secure Kernel's XNU upcall/syscall dispatch layer. A family of 4-byte entry aliases (e.g. 001807a4/001807a8 both tail-call 001807dc with error code 0xed; 001807c0/001807c4 with 0xcc) route through a common marshalling routine that copies message registers, checks a per-CPU gate (FUN_0017770c), and on the Swift path funnels failures into a noreturn `s_Fatal_error` trap with the `StackshotConclaveSupport` source annotation. A mismatched marshalling gate or unchecked register copy could allow an upcall to reach a handler with a forged message-register frame.
- **Evidence**: FUN_001807dc: `if ((FUN_0017770c()&1)==0) {...copy 6 regs...}` then on the Swift/error path `FUN_001afa84("Fatal error",0xb,2,0xd000000000000033,...,"StackshotConclaveSupport",0x36,2,...)` (noreturn). Entry aliases 001807a4/a8 pass 0xed, c0/c4 pass 0xcc to 001807dc.
- **Severity (hypothesis)**: low — the entries are dispatch shims; the real authorization is in the marshalling gate. Availability only (a bad upcall panics).
- **Confidence**: medium

## [sk-sched] 001f00ac cl4_thread_free_cb — TCB teardown releases inner + drop hook
- **Observation**: Thread/TCB free runs an indirect "drop hook" from the object at +0x60 with (obj+0x20, 0), releases the inner object (thunk_FUN_00012568) and the outer object. The teardown ordering (drop hook → inner release → outer release) is a refcount/RCU discipline; a wrong hook target or a double-release would corrupt the TCB free list.
- **Evidence**: `(*(code *)(*obj+0x60))(*obj+0x20,0); FUN_0006b6f4(*(word_t*)(inner+8)); cl4_obj_release(inner2); cl4_obj_release(*obj);`
- **Severity (hypothesis)**: low — release discipline; no observed bypass.
- **Confidence**: medium

## [sk-sched] 001f0130 cl4_sched_run_queue_drain — scheduler dispatch loop with fatal-error trap
- **Observation**: The run-queue drain loop dispatches per-entry callbacks and, when the completion flag is set, takes a "subroutine does not return" path into FUN_001afe4c (fatal). Any misclassified completion state escalates to a kernel panic rather than continuing with a corrupted queue — fail-closed scheduling.
- **Evidence**: `if ((extraout_x1&1)!=0) { ... FUN_0035110c(); /* noreturn */ FUN_001afe4c(); }`
- **Severity (hypothesis)**: low — fail-closed; availability only.
- **Confidence**: medium

## [sk-sched] 001fb26c cl4_sched_find_or_empty — empty-set marker class 0x100000000
- **Observation**: The scheduler slot lookup returns an explicit empty marker `{index=0, found=0x100000000}` (class 0x100000000, a non-canonical 33-bit value) rather than a valid slot; the entry-present path returns found=*unaff_x20+0x24. A caller that fails to distinguish the empty marker from a real class-1 slot could treat an empty result as a valid scheduling target.
- **Evidence**: `out.index=0; out.found=0x100000000;` vs `out.found=(ulong)*(uint*)(unaff_x20+0x24); out.index=u1;`
- **Severity (hypothesis)**: informational — the marker is unambiguous (class bit 32 set); standard seL4-style sentinel.
- **Confidence**: medium

## [sk191-ringminus1] 004176ec / 00417b60 sk_java_cp_decode / sk_java_cp_build — constant-pool walker reads fixed payload offsets
- **Observation**: The constant-pool entry decode (004176ec) and build (00417b60) walkers dispatch on a kind selector (0-0x11) and, in the member-ref case (case 0xd), read the name and descriptor at fixed byte offsets `+0x18` and `+0x38` from a payload pointer obtained via FUN_00458b14. No length check against a validated payload size is visible before those reads; a truncated/malformed constant-pool entry could cause an out-of-bounds read within the kernel.
- **Evidence**: `case 0xd: lVar5 = FUN_00458b14(auStack_d8); local_38 = *(undefined8*)(lVar5+0x18); uVar8 = *(undefined8*)(lVar5+0x38);` (dec_004176ec, dec_00417b60)
- **Severity (hypothesis)**: medium — OOB read on malformed class-file data if the payload bounds are not enforced upstream; the reader is reachable from the class-file verification path.
- **Confidence**: medium

## [sk191-ringminus1] 004176ec / 00417b60 / 00419d98 / 00419f24 — SoftwareBreakpoint fatal traps on malformed structural input
- **Observation**: Several structural walkers take a `SoftwareBreakpoint(1,<addr>)` "does not return" path when invariants are violated: cp_decode when a tagged string ref has a negative high word (trap at 0x4178bc/0x417898), struct_validate when the span bounds are inverted (`hi>>0xe < lo>>0xe`, trap 0x419e44), and struct_grow when the scan index overruns the count (trap 0x41a044). These are fail-closed kernel panics rather than graceful rejection.
- **Evidence**: `if (auVar9._8_8_ < 0) { /* Does not return */ (*SoftwareBreakpoint(1,0x4178bc))(); }`; `if (hi>>0xe < lo>>0xe) { (*SoftwareBreakpoint(1,0x419e44))(); }`; `if (count <= i) { (*SoftwareBreakpoint(1,0x41a044))(); }`
- **Severity (hypothesis)**: low — fail-closed; a crafted structure only triggers an availability (panic) DoS, not a memory-safety break. Confirms untrusted input reaches these paths.
- **Confidence**: medium

## [sk191-ringminus1] 004165ec / 00416ad0 / 00417454 / 00418378 — descriptor equality compares packed words on low 14 bits only
- **Observation**: The structural-equality predicates compare packed type/descriptor words using `(a ^ b) < 0x4000` (low 14 bits) and `(a ^ b) >> 0xe == 0`, and the method/field tag words with the same 14-bit window. Two descriptors whose tag bits differ only at or above bit 14 would compare equal, making the verifier's equality over-permissive. Whether this is a real over-match depends on whether the high tag bits encode identity or only length/kind metadata.
- **Evidence**: `(*(ulong*)(x+0x88) ^ *(ulong*)(y+0x88)) < 0x4000 && (*(ulong*)(x+0x90) ^ *(ulong*)(y+0x90)) < 0x4000` (dec_00416ad0); `(*(ulong*)(param_1+8) ^ *(ulong*)(param_2+8)) >> 0xe == 0` (dec_00417454)
- **Severity (hypothesis)**: low-to-medium — potential type-confusion in the verifier if distinct types share the low 14 bits; needs confirmation of the tag-word layout.
- **Confidence**: low

## [sk191-ringminus1] 00415b54 sk_java_character_methref — java.lang.Character method table packed as raw constants
- **Observation**: This function is a static method-reference table for java.lang.Character (javaLowerCase, javaMirrored, javaSpaceChar, javaTitleCase, javaUnicodeIdentifierStart/Part, javaWhitespace, ...), returning 16-byte tagged references. The presence of a full Java Character Unicode-property method table inside the ring-1 microkernel indicates the kernel embeds a Java class-file / reflection runtime for Exclave workloads.
- **Evidence**: string refs `s_javaIdentifierIgnorable_005dd110`, `s_javaJavaIdentifierPart_005dd150`, `s_javaJavaIdentifierStart_005dd170`, `s_javaLetterOrDigit_005dd1a0`, `s_javaUnicodeIdentifierPart_005dd1f0`, `s_javaUnicodeIdentifierStart_005dd210`; packed words `0x696665446176616a` ("javaDefi...").
- **Severity (hypothesis)**: informational — documents attack surface (Java class-file parsing in the TCB).
- **Confidence**: high (string-matched)

## [Sk190] 0041465c sk_syscall_number_decode — syscall-number dispatch index table
Observation: A linear syscall-number->dispatch-index decoder. It walks a fixed sequence of syscall IDs (0x61='a', 0x65='e', 0x66='f', 0x6e='n', 0x72='r', 0x74='t', 'd', 'D', 'h', 'H', 's', 'S', 'v', 'V', 'w', 'W', 'b', 'C', 'N', 'R', 'X', 'B', 'A', 'Z', 'z', 'G', 'K', 'O', 'y', 'Y', ...) via per-ID probing helpers (FUN_00462b80 + FUN_002a0cf8) and returns the matched index. An unknown/unmatched syscall falls through to return 0x1f (31) — a single catch-all default index, with no bounds/validity rejection on the returned table index.
Evidence: Decompile 0041465c: for each candidate, `if (unaff_x20 != id || unaff_x19 != -0x1f00000000000000) { FUN_00462b80(id); u= FUN_002a0cf8(); if (u&1) return idx; }` ; final `return 0x1f;`. Pair constant -0x1f00000000000000 is the cL4 syscall tag.
Severity (hypothesis): Medium — the index feeds a dispatch table; a fallthrough to index 31 relies on the caller validating the table bounds.
Confidence: Medium.

## [Sk190] 0040fd2c / 00411e40 / 00411f48 / 00411f4c — register-passed wrapper chain
Observation: Several small object-service wrappers read their arguments from callee-saved registers (unaff_x20/x19) rather than the ABI arg registers. Ghidra renders the same values as explicit args at some call sites and as unaff registers at the callee definition, i.e. the decompiler is internally inconsistent about argument passing across this region. All such functions were modelled by adding explicit params and padding under-argued calls with 0.
Evidence: 0040fd2c reads `*unaff_x20, unaff_x20[1..2]`; 00411e40 passes `(s78, r1, r2, r3)` to 00411d94 whose own body reads only unaff_x19/x20.
Severity (hypothesis): Low (analysis fidelity, not a runtime flaw).
Confidence: High (decompiler inconsistency is directly observable).

## [Sk190] 0041001c sk_obj_object_compare_dispatch — Swift object equality over type tags
Observation: The comparison dispatch switches on the object type tag (lo>>0x3c) and compares payloads. It invokes sibling comparators and, on the "type kinds" path (cases 5-7), compares (kind, size) pairs and XORs key words; result threshold `< 0x4000`. Swift runtime "absent_function" and "changeMatchingOptions" error strings (s_absent_function_005dd080 / s_changeMatchingOptions_005dd0c0) are referenced by the deeper typed handler FUN_00413b68.
Evidence: 0041001c switch(uVar6>>0x3c) with cases comparing `*(obj+0x10)`, `*(obj+0x18)`; case 5-7 `if ((uVar6^uVar8)>>0xe==0)`; FUN_00413b68 invokes FUN_00462adc(s_changeMatchingOptions_005dd0c0) and FUN_00086840(s_absent_function_005dd080) paths.
Severity (hypothesis): Info (Swift runtime semantics).
Confidence: Medium.

## [sk] SK193 0x42af18-0x439a5c Swift regex-literal parser — many bounded-buffer record-append paths
- **Observation**: The whole SK193 region is the Swift `_StringProcessing` regex-literal parser embedded in the cL4 kernel. Its AST builders (sk_re_diag_rec 0x42ec68, sk_re_diag_extend 0x42ed6c, sk_re_diag_merge 0x42ee6c) append 0x49-byte records to a growable list at (+0x10 count, +0x20 first slot, stride 0x50), with explicit overflow traps on every count bump and capacity check (SW_FATAL at 0x42ee5c/0x42ee68/0x42ee60/0x42ee6c). Every index write is bounds-gated, so a corrupted record can only trap, not over-write.
- **Evidence**: sk_re_diag_extend: `if (count + n < count) trap(0x42ee5c)`; `if (avail < n) trap(0x42ee68)` before `memcpy 0x50-strided`. sk_re_diag_merge: `if ((long)(total>>1) <= n) trap(0x42f020)` before the 0x50-strided copy loop.
- **Severity (hypothesis)**: low — the record appenders are bounds-checked; a malformed record from an attacker-controlled regex could at most trap (availability), not corrupt memory.
- **Confidence**: high (explicit trap addresses and capacity checks transcribed).

## [sk] SK193 0x42c958 sk_re_parse_delim_body — delimiters/#-mode scanner
- **Observation**: The delimiter scanner counts a leading run of '#' extended-mode markers and matches each candidate delimiter option in the regex record. The option list lives at rec+0x10 (count) / rec+0x20 (bytes); every option access is bounds-checked against the count with traps (0x42d014), and the closing-run compare loops are guarded by end-pointer checks (0x42d018/0x42d034/0x42d048). No unguarded read of the pattern span was found.
- **Evidence**: `if (*(rec+0x10) <= i) trap(0x42d014)`; `if (end < start+hash+adv) trap(0x42d048)`.
- **Severity (hypothesis)**: low — the scanner is bounds-checked; at most a malformed delimiter produces a diagnostic (tag 2, "no valid delimiters").
- **Confidence**: medium.

## [sk] SK193 0x42f020/0x42f1f0 newline scanners — unguarded byte loads flagged by decompiler
- **Observation**: The UTF-8 newline scanners (sk_re_parse_scalar 0x42f020, sk_re_parse_scalar2 0x42f1f0) read bytes from an inlined 2-word local (`local_70/uStack_68` = the String head) when the 'small string' flag (0x2000000000000000) is set, using the low 14 bits of the head as the inline byte span. The decompiler's register-spill model makes the exact bound unclear; the span is masked to `&0xffffffffffff` (or `>>0x38 &0xf` for small strings), so the read length is bounded by the flag-implied capacity, not by an external count.
- **Evidence**: `pbVar4 = (byte*)((long)&local_70 + lVar5); uVar2 = *pbVar4;` with `local_70=param_1; uStack_68=param_2 & 0xffffffffffffff`.
- **Severity (hypothesis)**: low — inline-String loads are bounded by the String's own length encoding; the risk is limited to a logic error in the length decode, not an attacker-writable over-read.
- **Confidence**: low (decompiler warning: "Type propagation algorithm not settling").

## [SkGap08] 0x0034fb28-0x00350404 — tagged descriptor returns and no-op stub run
- **Observation**: SKGAP08 (120 functions) is a dense run of trivial leaf/thunk functions. Most are empty no-op stubs (bare `return`). A few build 16-byte values: 0034fb28 returns `{&DAT_005d0ce6, 1}` (a data-address + tag/count pair); 0034fc44/0034fc58 return constant `{static_addr, static_addr}` pairs (0x656358/0x4e8150 and 0x656360/0x4e8158); 0034fe08/00350328 place a value in the high 64 bits of a 16-byte result; 0034fc8c packs args 3+4 into a pair. Several fragments reference unaff_* registers or stack-frame math the decompiler could not resolve (marked low confidence). No unchecked memory writes, no attacker-controlled indexing, no bounds issues.
- **Evidence**: decompile outputs (e.g. `FUN_0034fb28 { auVar1._8_8_=1; auVar1._0_8_=&DAT_005d0ce6; }`; `FUN_0034fc44 { lo=0x656358; hi=0x4e8150; }`). 80+ functions compile to bare `return`.
- **Severity (hypothesis)**: Info — the tagged descriptor returns (data-addr+count) resemble capability/object handles but are data-construction helpers; no privilege/confidentiality impact identified.
- **Confidence**: medium (trivial bodies transcribed faithfully; no security-relevant logic).

## [SkGap07] 0x0034f22c-0x0034fb14 — Swift-runtime stub run + fatal-error trampolines
- **Observation**: SKGAP07 (120 functions) is a dense run of tiny Swift-runtime/protocol-witness stubs. ~90 compile to a bare `return` (no-op), 9 return constant 0, and the rest are small word/16-byte copy helpers, opaque-metadata descriptor getters (16-byte `{address, discriminator}` pairs), and a bit-vector clear primitive (0034fa78). Two are noreturn Swift fatal/precondition trampolines: 0034f6a8 traps with "Fatal error" (s_Fatal_error@0x005accd0) on a String.GraphemeBreaking path, OR-ing the top bit into the grapheme index (`param | 0x8000000000000000`) before trapping; 0034fa9c traps with "Precondition failed" (s_Precondition_failed@0x005ce2d0) on a FloatingPointToString path. 0034fb14 grows scheduler capacity via cl4_sched_grow_capacity(max((*state)+0x18, param)).
- **Evidence**: decompile outputs (e.g. `FUN_0034f6a8 FUN_001afa84(s_Fatal_error,0xb,2,0xd000000000000034,param_1|0x8000000000000000,s_Swift_StringGraphemeBreaking_swi_005d3570,0x22,2)`; `FUN_0034fa9c FUN_001afa84(s_Precondition_failed,0x13,2,0,0xe000000000000000,s_Swift_FloatingPointToString_swif_005d33c0,0x21,2)`; `FUN_0034fa78 &(-1L<<(unaff_x21&0x3f))-1` bit clear; ~90 bodies are bare `return`).
- **Severity (hypothesis)**: Info — the two fatal trampolines are the microkernel's embedded Swift runtime confirming that untrusted/untrusted-side Unicode strings (grapheme indices, float-to-string) are processed in-kernel; malformed indices only reach the noreturn trap (availability via kernel panic), no memory-corruption or disclosure path found. The `(-1L << 63)` bit-clear shift is decompiler UB-flagged but executes as a valid LSL on arm64e.
- **Confidence**: high (trivial bodies + explicit string refs transcribed faithfully; no attacker-controlled indexing or unchecked writes).

## [SkGap05] 0x0034df34-0x0034e81c — dense method-dispatch table region
- **Observation**: SKGAP05 (120 functions) is a dense method-dispatch/vtable region of tiny slots. Most (>=70) are register-forwarding tail-call thunks that only move the caller's callee-saved values into argument/return position (e.g. `mov x20,x19; mov x2,x19; mov x3,x22; ret`) and fall through — the real dispatch lives in the caller's continuation; Ghidra renders them as empty `return;`. A second group (>=12) are PAC-authenticated static-descriptor getters (`adrp/add/pacda + mov x0`) returning 12-byte metadata records (e.g. DAT_004eb980, DAT_004eb964, DAT_004edd08, DAT_004eab00, DAT_004ea760, DAT_004e9db0, DAT_004e8f9c, DAT_004e8b7c) whose contents are pointer pairs + len + flags (0x200). A third group are field-offset resolvers calling the shared helper family FUN_003109b4(+0x3c)/00310a44(+0x40)/00310a74(+0x30)/0008f758(+0xc)/000a649c(+0x14) — tagged-pointer deref + signed relative offset. Two tail slots (0034e7e0/0034e808) return 0 and set a side pointer (x4 = &DAT_00611b24+0x18 / &DAT_0060e208+0x28); 0034e81c returns constant 0xff. 0034e7f4 is a NEON lane-unsigned-compare helper (cmhi 4S, uzp1, umaxv h0) returning the max of four 32-bit (b>a) masks.
- **Evidence**: full disassembly of all 120 slots captured (e.g. `0034df34: mov x20,x19; mov x2,x19; mov x3,x22; ret`; `0034e220: adrp x16,0x4eb000; add x16,x16,#0x980; mov x17,#0xc6eb; pacda x16,x17; mov x0,x16; ret`; `0034e7f4: cmhi v0.4S,v2.4S,v0.4S; uzp1 v0.8H,v1.8H,v0.8H; umaxv h0,v0.8H; fmov w8,s0; ret`). read_memory at the descriptor addrs shows 12-byte records: 004eb980 = [0x00125da4, 0x0012708c, 0x00183200, 0x00020000], i.e. ptr,ptr,len,flags.
- **Severity (hypothesis)**: Info — the PAC-authenticated descriptor getters and field-offset resolvers are data-construction helpers for the kernel's object metadata/catalog; they only return static addresses and deref tagged pointers already validated by their callers. No attacker-controlled indexing, no unchecked writes, no bounds issues. The 0xff/0 constant returns are error/status sentinels.
- **Confidence**: medium (bodies transcribed faithfully from disassembly; the majority are opaque register thunks with the real work in the caller).

## [SkGap04] 0x0034d914 sk_pair_ret_34d914 — frame-relative 16-byte return collapsed to {0,0}
- **Observation**: The part14 reconstruction (sk_region_syscalls_part14.c) renders this 16-byte-return function as the constant `{lo=0, hi=0}`. The disassembly and decompile show it actually returns caller-frame-derived values: `x0 = x29 - 0x78` and `x1 = *(x29 - 0xc0)` (a saved caller register). The reconstructed constant body is not faithful to the machine code; it is likely a prologue/tail fragment of a larger inlined routine where the frame reads are artifacts of an unrecovered frame pointer.
- **Evidence**: `0034d914: mov x9,x0 / sub x0,x29,#0x78 / ldur x24,[x29,#-0xc0] / mov x1,x24 / ret`. Decompile: `auVar1._0_8_ = x29-0x78; auVar1._8_8_ = *(x29-0xc0)`.
- **Severity (hypothesis)**: Info — frame-relative read of a saved register; no attacker-controlled index, no dereference of untrusted data. Fidelity issue only (reconstruction should be marked fragment, not a constant pair).
- **Confidence**: high (disassembly confirms the constant body is wrong).

## [SkGap04] 0x0034de74 sk_alloc_pages_call_34de74 — copy + tail-call mis-reconstructed as alloc_pages(0x10,0)
- **Observation**: The part14 body `sk_alloc_pages(0x10, 0)` does not match the code. This is a tail-call thunk: it copies `*(x20) -> *(x19)`, then computes `x8 = (x9+0x10) & ~x9` (round up to a boundary), `x19 = *x20 + x8`, and tail-calls FUN_0036b270 (the cL4 allocator). The actual argument to the allocator is a computed address, not the constant (0x10, 0).
- **Evidence**: `0034de74: ldr x0,[x20] / str x0,[x19] / add x8,x9,#0x10 / bic x8,x8,x9 / add x19,x0,x8 / b 0x0036b270`. The `bic` performs `(x9+0x10) & ~x9` — a boundary-rounding of a capability/object size.
- **Severity (hypothesis)**: Info — the function is a memcpy+alloc boundary-rounding helper; the mis-reconstruction affects documentation accuracy, not runtime behavior (recreated code is not executed).
- **Confidence**: high (tail-call branch to 0x36b270 confirmed; body is a faithful disassembly transcription).

## [SkGap04] 0x0034ddec sk_setflag_34ddec — drops a constant store and passes wrong arg to field helper
- **Observation**: The part14 body `sk_swift_field_0x30(0); sk_flag_reset(0)` is missing the store of the sentinel `0x8000000000000000` to `[x29-0x60]`, and passes `0` where the code passes `x25` (the value loaded into x0 before `bl 0x310a74`). The `mov x26,x0` result is then discarded before the tail-call to 0x1df60.
- **Evidence**: `0034ddec: pacibsp / str x30,[sp,#-0x10]! / mov x8,#-0x8000000000000000 / stur x8,[x29,#-0x60] / mov x0,x25 / bl 0x310a74 / mov x26,x0 / ldr x30,[sp],#0x10 / autibsp / b 0x0001df60`. The sentinel store is a flag-set on the stack frame that the part14 body omits entirely.
- **Severity (hypothesis)**: Info — the constant `0x8000000000000000` store is a local flag write; no memory-safety impact. Fidelity of the reconstruction is incomplete (missing store, wrong argument).
- **Confidence**: high (disassembly confirms missing store and x25 argument).

## [SkGap09] 0x00350410-0x00350a94 — register-shuffle epilogue stub cluster + string-accessor tail calls
- **Observation**: SKGAP09 (120 functions) is a dense cluster of tiny (2-6 instruction) register-shuffle EPILOGUE stubs shared by the capability/object-op handlers. The decompiler rendered nearly all as empty `return;` because it does not model the register-return convention; disassembly shows each repacks caller callee-saved registers (x19-x28) or special regs (x8/x9/x12/sp) into the return set. Groups: (~35) `mov x0,rA; mov x1,rB; ret` 16-byte passthrough pairs; (~10) `mov x0,#0; mov x1,rB` zero-lo pairs; (~9) `mov x8,x0; mov x0,rB` indirect-result writes; (~26) multi-register output setters (x1/x2/x3/x5/x7/w8); (~10) SP/stack-manip stubs (`x8=sp-x8`, `stur x8,[x9,#-0x100]; mov sp,x8`, `ldr x16,[x8,#-8]!` br trampoline); (~14) field-offset resolvers tail-calling the shared relative-pointer resolvers (FUN_000a68c4/0x310a74/0x310924/0x277b8/0x3109b4/0x310a44/0x8f728/0x16186c/0x31948c/0x27754); 3 PAC'd static-descriptor getters (DAT_004c1010, DAT_004e984c, DAT_004e9518, discriminator 0xc6eb); and 2 string-constant tail calls (0035059c s_value_005ce9d2 "value" len 7; 003505b0 s_from_invalid_005ce9c3 "from invalid" len 14, sel 1) into the shared string/buffer accessor FUN_001a89a8 (which validates length < 0x10 and panics on negative length).
- **Evidence**: full disassembly of all 120 captured (e.g. `00350410: sub sp,sp,#0x20; mov w8,#1; ret`; `0035081c: adrp x16,0x4e9000; add x16,#0x84c; mov x17,#0xc6eb; pacda x16,x17; mov x0,x16; ret`; `0035059c: adrp x0,0x5ce000; add x0,#0x9d2; mov w1,#7; mov w2,#1; b 0x001a89a8`; `00350a64: mov x0,#0; mov x1,x2; ret`). The decompiler's `FUN_00350a64 = auVar1 << 0x40` confirms the {lo=0,hi=param_3} 128-bit return the disassembly shows.
- **Severity (hypothesis)**: Info — the two string-constant tail calls are validation-error reporting paths ("value"/"from invalid"); both string lengths (7, 14) are within the accessor's <0x10 bound so no truncation, and negative-length panic is unreachable from these constants. The PAC'd descriptor getters return static signed addresses; the resolvers deref tagged pointers already validated by callers. No attacker-controlled indexing, no unchecked writes, no disclosure path found.
- **Confidence**: high (all 120 bodies transcribed faithfully from disassembly; the register-shuffle semantics are exactly reproduced via inline asm).

## [SkGap13] 0x00353960-0x0035401c — Swift-runtime/protocol-witness thunk cluster (120 fns)
- **Observation**: SKGAP13 (120 functions) is a dense run of tiny Swift-runtime protocol-witness thunks. ~92 are no-op witnesses (bare `ret`: default protocol requirements the type does not implement) or 1-2-instruction register-forwarding shims that move a value between a caller stack slot (`unaff_x29` reads/writes at sp-0x58..-0x138) and a callee register. ~28 do real work: object-field getters (base + 0x04/0x24/0x30/0x38/0x5c + signed int) that resolve a pointer-tagged object and read a 32-bit field, a boxed-field NEON load that discards its result, a 128-bit `{lo=0,hi=arg}` pair build, a two-word 16-byte copy, and a block zero-fill. All are compiler-emitted runtime glue; none implement security-relevant policy directly.
- **Evidence**: `0035396c: and w0,w0,#1` (tag test); `00353dc4: ldr x8,[x20]; str x8,[x19]; ldr x8,[x20,#8]; str x8,[x19,#8]` (16B copy); `00353fb8: b 0x00114330` with `mov w1,#4` (block zero-fill of 4 bytes); `00353ad8` dispatches into the dense method table `FUN_002a4c98(0,0xe000000000000000,0,0)` (tagged-pointer mask 0xe000000000000000). Field getters `FUN_00310a74/0001df60/003a25d4/0008e5d8/00319658/00027788` all deref pointer-tagged references after masking `& ~1` — the tag is validated (low bit must be 0 for heap, else indirect via `*(p&~1)`).
- **Severity (hypothesis)**: Info — the pointer-tagged object resolvers mask the tag before dereferencing and never index with attacker-controlled offsets (constant field offsets only). No unchecked writes, no disclosure path, no boundary arithmetic on untrusted input. The negative-offset load `*(base-0x100)` (0x00353dac) is a fixed compiler-emitted field access, not input-dependent.
- **Confidence**: high (all 120 decompiled; the no-op/register-forwarding identity is directly confirmed by the tiny 12-byte bodies).

## [SkGap16] 0x00354fd0-0x00355858 — Swift-runtime/protocol-witness stub run
- **Observation**: SKGAP16 (120 functions) is a dense run of trivial Swift-runtime/protocol-witness glue, adjacent to the SkGap07/SkGap08 regions. ~80 compile to a bare `return` (no-op witnesses), 1 returns constant 0, 3 return constant 0xff (status/error sentinels), and the rest are small word/16-byte copy or caller-frame spill/load helpers, opaque-descriptor getters (16-byte `{address, tag}` pairs), and a handful of trampolines into shared helpers. Notable: 00355270/00355484 store a function address (FUN_002060d4 / FUN_00205844) into a stack slot then call the shared helper FUN_0026bbd4 (dispatch-thunk pattern); 00355354 builds a 16-byte value `{1 << (byte[obj+0x20] & 0x3f), word32[obj+0x24]}` — the shift is masked to <64 so no UB; 003556b0 calls the object-name lookup FUN_00002534 with `(1 << (param & 0x3f)) + 0x3f`; 00355720 masks a stored word to its low 56 bits (pointer tagging). No unchecked memory writes, no attacker-controlled indexing, no bounds issues.
- **Evidence**: decompile outputs (e.g. `FUN_003550e0 { lo=x24&~x23; hi=x20&~x23 }`; `FUN_00355354 { lo=1<<(byte[obj+0x20]&0x3f); hi=word32[obj+0x24] }`; `FUN_00355270 { pcStack=FUN_002060d4; FUN_0026bbd4(); }`; ~80 bodies are bare `return`). All 120 transcribed into sk_slice_gap16.c and compile-clean.
- **Severity (hypothesis)**: Info — the bit-shift helpers are data-construction/descriptor getters with the shift masked to <64 (no UB) and inputs validated by callers; the dispatch thunks only forward into shared helpers. No privilege, memory-corruption, or disclosure path identified.
- **Confidence**: high (all 120 bodies transcribed faithfully from decompiles; trivial logic, no attacker-controlled indexing or unchecked writes).

## [SkGap18] 0x00357bf8-0x0035841c — dense frame-fragment / forwarding-stub run
- **Observation**: SKGAP18 (120 functions, 0x357bf8-0x35841c) is a dense strip of tiny (1-4 instruction) functions. The majority (~85) are stack-frame prologue/epilogue fragments: the decompiler splits the surrounding routine at a re-entry point and recovers only frame teardown (restoring callee-saved x19-x24 from sp+0x10..0x30, e.g. 00357c74/00357cb4) or a single store, with the real logic live-in from the caller (rendered `return;`). A second group are thin tail-call/forwarding stubs (00357bf8→FUN_00365b6c, 00357c88→FUN_000a6b64, 003581fc→FUN_00376820, 00358404→FUN_00117d14). A few are small real leaves: 00357f34 masks off the low 16 bits and subtracts 0xfffc (page-table-entry → canonical address fixup); 00358134 computes a guarded ratio (x21 ? param/x21 : 0) then stores value<<1 at [x20+0x18]; 00357cc8 returns a Swift existential metadata pair (s_Swift_ExistentialCollection_swif_005cf680, tag 0x21); 003580a4 masks a capability word's upper bits with 0xffffffffffffff; 003581b4 writes -1L<<(x26&0x3f) into a bitmask.
- **Evidence**: decompile outputs (e.g. `FUN_00357c74 { ldp x20,x19,[sp,#0x30]; ...; add sp,sp,#0x50; ret }` — pure epilogue; `FUN_00357f34 return (param & 0xffffffffffff0000) - 0xfffc;`; `FUN_00358134 { if(x21) lVar1=param/x21; *(x20+0x10)=x19; *(x20+0x18)=lVar1<<1; }`; `FUN_00357cc8 { auVar1._0_8_=s_Swift_ExistentialCollection_swif_005cf680; auVar1._8_8_=0x21; }`; `FUN_003580a4 { hi=[x20+8]&0xffffffffffffff; lo=[x20+0x10]; }`). Disassembly confirms fragment bodies (00357c20: `add x9,x8,#0x20; bic x8,x9,x8; ret` — result discarded).
- **Severity (hypothesis)**: Info — the page-entry→canonical-address fixup (00357f34) and capability-word masking (003580a4) operate on caller-validated inputs; no attacker-controlled indexing, no unchecked writes, no bounds arithmetic on untrusted input. The ratio division (00358134) is correctly guarded against divide-by-zero. The Swift existential pair is static metadata construction. No disclosure or corruption path found.
- **Confidence**: medium (bodies transcribed faithfully from decompile; fragment identity confirmed by disassembly — real logic lives in caller continuations).

## [SkGap17] 0x00355868-0x00357bec — Swift-runtime/protocol-witness stub run
- **Observation**: SKGAP17 (120 functions, 0x355868-0x357bec) is a dense run of tiny Swift-runtime protocol-witness glue, contiguous with the SkGap16/SkGap18 strips. ~75 compile to a bare `return` (no-op witnesses), and the rest are small word/16-byte copy or caller-frame spill/load helpers, Swift opaque-metadata descriptor getters (16-byte `{address, tag}` pairs, e.g. 003575b0→DAT_004e7d48, 00357754→DAT_004e7d40), a byte-swap/endianness primitive (003576dc), capacity round-up helpers (`(len & 0x0fffffffffffffff) + 0x20`), and forward thunks into shared helpers (003579d8/00357bec→FUN_003722e4, 00357acc→FUN_00310d68 with tag 0x13f, 00357bd0→noreturn fatal-precondition FUN_001afa84).
- **Evidence**: decompile outputs (e.g. `FUN_00355868 = x24 & (x23 ^ -1)`; `FUN_003576dc` full 16-byte byte-swap; `FUN_00357628 = (x3 & 0xfffffffffffffff) + 0x20`; `FUN_00357874 = cur + ((base+0x20) & ~base)` alignment-bump; ~75 bodies are bare `return`; `FUN_00357bd0 { /* noreturn */ FUN_001afa84(); }`). All 120 transcribed into sk_slice_gap17.c and compile-clean (0 errors).
- **Severity (hypothesis)**: Info — the shift/byte-swap helpers operate on caller-validated inputs (60-bit mask prevents overflow UB; alignment-bump masks against the base's low bits only). The one noreturn path (00357bd0) is the standard Swift string fatal-precondition trap, reachable only from compiler-inserted precondition failures. No attacker-controlled indexing, no unchecked writes, no disclosure or privilege path identified.
- **Confidence**: high (all 120 bodies transcribed faithfully from decompiles; trivial logic, no attacker-controlled input reaches a write).

## [SkGap15] 0x00354828-0x00354fc0 — Swift-runtime/protocol-witness stub run (120 fns)
- **Observation**: SKGAP15 (120 functions) is a dense run of trivial Swift-runtime/protocol-witness glue, contiguous with the SkGap07/SkGap08/SkGap13/SkGap16 regions. ~79 compile to a bare `return` (no-op witnesses). The rest are small real bodies: four lazy-global initializers (00354a58/00354bf8/00354c44/00354d80) that install a resolved value at fixed global slots (0x6560f0/0x656180/0x64f3c0/0x656248) via FUN_00002534; a 5-word struct copy (003548f4) writing dst[0..6] from a register-passed source + out-slot; frame-local getter/setters (00354a78/abc/ac8/b44/cb4/cf0/d08, negative fixed offsets -0x58..-0x190); two word-pair {lo,hi} builders (003548d0, 00354bc8); six object-service forward-resolves (00354e18/50/6c/88/a4/c0 → FUN_00376820); two scheduler-queue-foreach witnesses (00354e34/edc → FUN_001a157c); and two Swift small-string-encode trampolines (00354ad4/ae8) for the integer range-check / precondition message paths. All fixed-offset field accesses and constant global slots; no input-dependent indexing.
- **Evidence**: decompile outputs (e.g. `FUN_003548f4 { *x19=param_1; param_1[5]=x20; ... dst[0..4]=src[0..4]; }`; `FUN_00354ad4 FUN_001a89a8(s_because_it_is_outside_the_repres_005cfbd0,0x2e,1)`; `FUN_00354960 return param_1 & 0xffffff00 | in_w8 & 0xff`; `FUN_00354d80 FUN_00002534((ulong*)0x656248,&DAT_004e80a0)`; `FUN_00354f98 { *(x20+0x20)=*(x19+0x20); *(x20+0x28)=*(x19+0x28); }`). All 120 transcribed into sk_slice_gap15.c and compile-clean (0 errors).
- **Severity (hypothesis)**: Info — the 5-word struct copy (003548f4) writes into a caller-provided array with no length argument, so an under-sized caller destination would overrun; this is a caller-contract issue (fixed 7-word target), not an input-controlled write. Lazy-global initializers only touch fixed linker-assigned global slots. The Swift precondition trampolines encode static message literals and discard the packed result (return is void); no attacker-controlled formatting, no disclosure path, no boundary arithmetic on untrusted input.
- **Confidence**: medium (bodies transcribed faithfully from decompiles; region identity confirmed by the tiny 12-byte no-op bodies and matching sibling-slice patterns; the register-passed args are modelled as explicit params per the documented calling-convention note).

## [SkGap03] 0x0034aac4-0x0034d5d8 — dense thunk / PAC-decode / frame-fragment strip (120 fns)
- **Observation**: SKGAP03 (120 functions, 0x34aac4-0x34d5d8) is a dense run of tiny (1-8 instruction) thunks. Three families dominate: (1) argument-marshalling / register-forwarding stubs (mov-only, ~40) that shuffle callee-saved x19-x28 into arg registers — tail-call trampolines whose target was inlined; (2) PAC / tagged-pointer decode stubs that fetch an object-header word at [obj-8] (0034ab20/0034ad10/0034ada0/0034d140) or select between a 48-bit field and a 4-bit tag by flag bit 0x2000000000000000 (0034aaf4/0034ab88/0034d0e0) — the classic cL4 captype discriminator; (3) stack-frame prologue/epilogue fragments the decompiler recovers only as `sub x9,x9,x12; stur [x29,-off]; mov sp,x9` with the real logic live-in from the caller. A few real leaves: 0034d0a0 is a Swift fatal-error path (printer FUN_001afa84 with string refs Fatal_error / Swift/Duration.swift); 0034ab30 does a two-call frame walk; 0034d5b8 computes a round-up shift/align; 0034d584 tests the exponent bits of an IEEE-754 half (NaN/Inf detect). One pair stub (0034adb4/0034add4) returns a PAC'd function pointer (pacia key 0x2abe) + data pointer.
- **Evidence**: disassembly (e.g. `0034aaf4: and x8,x24,#0xffffffffffff; ubfx x9,x20,#0x38,#0x4; tst x20,#0x2000000000000000; csel x8,x8,x9,eq`; `0034ab20: ldr x16,[x8,#-8]!` object-header fetch; `0034ad60: pacda x16,x17` with key 0xc6eb; `0034d0a0: b 0x001afa84` fatal printer with w1=0xb w2=0x2 severity). The tag-decode bodies transcribe the csel selection into English C; all 120 defined in sk_slice_gap03.c, compile-clean.
- **Severity (hypothesis)**: Info — the tagged-pointer decodes mask the tag (48-bit field / 4-bit tag) and the object-header fetch reads a fixed [obj-8] slot; no attacker-controlled indexing, no unchecked writes, no bounds arithmetic on untrusted input. The frame fragments are compiler-emitted epilogues; the fatal path is a controlled panic. PAC'd function pointers use a fixed signing key (0x2abe/0xc6eb) — constant, not attacker-derived. No disclosure or corruption path found.
- **Confidence**: medium (most bodies are register-shuffle / frame-fragment identity confirmed by disassembly; the real logic for fragments lives in caller continuations).

## [SkGap14] 0x354028-0x35481c — Swift-runtime/protocol-witness stub run (120 fns)
- **Observation**: SKGAP14 (120 functions, 0x354028-0x35481c) is a dense run of trivial Swift-runtime/protocol-witness glue, contiguous with the SkGap13/SkGap15/SkGap16/SkGap17 strips. ~86 compile to a bare `return` (no-op witnesses / empty handler slots). The rest are small real bodies: caller-frame spill/load helpers (00354028/-0xe0, 003540a0/-0x70, 003540dc/-0xb0, 00354128/-0x120, 003543b8/-0x80, 00354570/-0x150, 00354594/-0x88, 00354648/-0x68, 0035466c/-0x80, 00354780/-0xa0); constant-frame writes (003540e8=0x40, 00354270=0x7fffffffffffffff LONG_MAX timeout sentinel, 0035427c=0xffffffffffffff80 + forward to FUN_00310a74); a tagged "pointerValue" descriptor initializer (003540f4) writing a 16-byte value + 7-byte type-tag string with a static pointer 0x677790 at +0x48; two object-record initializers (00354348, 00354678/0035472c) storing a value + static table pointer (DAT_004f1660/004f17e0/004f1628); static-address getters (003544ec→DAT_004edcec, 00354690→DAT_004e8230, 00354798→DAT_004e9d58); a masked-size helper 003542dc `(v & 0xfffffffffffffff)+0x20`; constant returns (003542b8=0xff, 003543d0=0); forward thunks into shared helpers (00354474→FUN_000a68f4, 00354624→FUN_000026e8, 003547b0→FUN_00310a44, 0035448c→sk_intern_create_3 FUN_0037233c).
- **Evidence**: decompile outputs (e.g. `FUN_00354028 { *(sp-0xe0)=param_1 }` dead frame store; `FUN_003540f4 { obj+0x20="pointerV"; obj+0x28="alue"+0xec tag; obj+0x48=0x677790 }`; `FUN_003542dc = (v&0xfffffffffffffff)+0x20`; `FUN_00354348 { obj[3]=p1; obj[4]=&DAT_004f1660; obj[0]=p2 }`; ~86 bodies are bare `return`). All 120 transcribed into sk_slice_gap14.c and compile-clean (0 errors, 0 warnings).
- **Severity (hypothesis)**: Info — the masked-size helper (003542dc) applies a 60-bit mask so no overflow UB; the frame spill/load helpers and constant writes touch only caller-owned frame slots or fixed static pointers; the static-address getters return constant linker-assigned addresses; the forward thunks only tail-call into shared helpers. No attacker-controlled indexing, no unchecked writes, no disclosure or privilege path identified. The no-op witness slots are unimplemented Swift protocol-witness stubs (per the surrounding-slice convention), not reachable security-sensitive syscall handlers.
- **Confidence**: high (all 120 bodies transcribed faithfully from decompiles; trivial logic, no attacker-controlled input reaches a write; degenerate frame-slot bodies confirmed by matching sibling-slice patterns).

## [SkGap06] 0x0034e830-0x0034f21c — Swift `_Concurrency`/metadata thunk cluster (120 fns)
- **Observation**: SKGAP06 (120 functions, 0x34e830-0x34f21c) is a dense Swift-runtime `_Concurrency` support cluster. ~110 are tiny (1-8 instruction) register-shuffle continuation thunks that reorder callee-saved context registers (x19-x28) into argument registers x0-x4 with no memory/call side effect — the decompiler collapses them to `return;`, and the bodies are recovered from disassembly. The ~10 real bodies include: 24-byte value copies (0034e86c), stack-pointer adjustments (0034ea40/54, 0034eb2c/40, 0034ef48), two Swift type-metadata/descriptor builders (0034f088/0034f0c0 writing descriptor+flags then calling the global metadata hook FUN_0036986c), thin wrappers over shared runtime helpers (sk_vt_dispatch30=FUN_000839f8, the swift_type_metadata_field_* accessors, swift_small_string_encode=FUN_001a89a8, the large allocator FUN_002a4c98), and tagged-value width decoders selecting between a 48-bit field and a 4-bit tag by flag 0x2000000000000000 (0034e910/eb74/efc8/f064/f21c).
- **Evidence**: disassembly (e.g. `0034e850: add x8,x8,x25; add x9,x8,x23; bic x0,x9,x25` pointer-masking pair; `0034f088: adrp x8,0x5ce000; orr x8,x8,#-0x8000000000000000; movk x9,#0xd000,LSL #48` descriptor with high-bit tag; `0034f030: b 0x001a89a8` string-encode tail call; `0034efdc: bl 0x00310a74` metadata field-offset with pacibsp/retab). The 0034f088/0034f0c0 builders write {descriptor 0x6773c0/0x676ed0, param, flags 0xd00000000000002f/2e, 0x80000000005cebd0/0x5ceba0, 0, 0} then tail-call the hook dispatcher FUN_0036986c (calls `*_DAT_006adee8` if non-null). All 120 defined in sk_slice_gap06.c, compile-clean.
- **Severity (hypothesis)**: Info — the tagged-value decodes mask the tag (48-bit field / 4-bit tag); the metadata builders and field-offset wrappers pass only caller-supplied object pointers to the standard Swift runtime helpers; the hook dispatcher FUN_0036986c is a single global function pointer with a null check (no attacker-controlled indexing, no unchecked writes). The register-shuffle thunks perform no memory access at all. No disclosure or corruption path found.
- **Confidence**: medium (thunk identity confirmed by disassembly; real logic for frame-fragment thunks lives in caller continuations; the shared-helper wrapper names are tied to already-verified manifest identities).

## [SkGap11] 0x00351d24-0x00353118 — dense leaf/thunk/helper run, Swift-metadata + frame fragments
- **Observation**: SKGAP11 (120 functions, 0x351d24-0x353118) is a dense run of small leaf/thunk/helper functions, contiguous with the SkGap08 strip. 93 compile to a bare `return` (empty no-op slots). The non-trivial 27 include: a ChaCha-style 64-bit mixing round (00351d4c, ROL 13/16/17/21 + byte-swap halves) called from FUN_001a842c/FUN_00229ebc; forwarding thunks into the Swift type-metadata field accessors 00310a74 (field_30) and 00310b08 (field_14) and boot helper 00027754; caller-frame spill/load helpers (00351fe0, 00352128/0x140/0x17c, 003520d0, 00352260, 003523bc — all unaff_x29 fragments writing/reading caller slots); tagged-pointer/pair builders (00351fd0 masked-ptr+0x20 build, 003520a4/0x2058 {1,value} pairs, 0035239c pair pack); the align-down (003520e8) and clear-lowest-set-bit (0035229c v&(v-1)) primitives; and constant sentinel writes (0x8000000000000000 in 003520d0/00352414).
- **Evidence**: decompile outputs (e.g. `FUN_00351d4c` full quarter-round with `in_x10/x11/x12` register inputs; `FUN_003521a4 { *(x29-0x48) = &DAT_00657778 }`; `FUN_00351fc0 { *unaff_x19=(int)p1; *(char*)(x19+1)=p1>>0x20 }`; `FUN_0035229c { *(x20+0x20) = p1-1 & p1 }`; `FUN_003520e8 = p1 + unaff_x19 & ~in_x9`; 93 bodies are bare `return`). All 120 transcribed into sk_slice_gap11.c and compile-clean (0 errors, 0 warnings).
- **Severity (hypothesis)**: Info — the hash round and primitives are pure arithmetic on caller-supplied words; the frame spill/load helpers and constant writes touch only caller-owned frame slots or fixed static addresses (DAT_00657778, 0x8000000000000000 sign sentinel); the forwarding thunks only tail-call into already-verified shared helpers; the masked-size/align operations apply fixed masks so no overflow UB. No attacker-controlled indexing, no unchecked writes, no disclosure or privilege path identified. The no-op slots are empty placeholders (per the surrounding-slice convention), not reachable security-sensitive handlers.
- **Confidence**: medium (most bodies transcribed faithfully from decompiles; trivial logic; degenerate frame-slot/fragment bodies confirmed by matching sibling-slice patterns; the hash round's register inputs in_x10/x11/x12 are modeled as extra parameters).

## [SkGap00] 0x003224a0-0x00326024 — syscall/exception-entry dispatch handlers (120 fns)
- **Observation**: SKGAP00 (120 functions) is the syscall/exception-entry dispatch region. Core handlers are the generic IPC / capability-op / syscall-op dispatchers (sk_sys_ipc_common 0x322a88, sk_sys_ipc_5cap 0x322d44, sk_sys_cap_op_common 0x323304, sk_sys_ipc_6cap 0x323714, sk_sys_op_common 0x323f64) plus their per-id wrapper families (0x322928/322980/3229d8/322a30, 0x323254/ac/323664/bc, 0x323dd4/e38/e9c/f00). These build the capability message (sk_msg_init), resolve the destination cap (sk_cap_lookup 0x371950), dispatch through the global table pointer g_sk_dispatch (DAT_00658c00) and per-class method tables (slot +0x10), then run the send/recv dance (sk_sendN/sk_recv/sk_ipc2). Badge-mask + cap-check gates recur (sk_badge/sk_badgemsk + sk_cap_check 0x35142c) before installing dispatch results into TCB slots. TLS reads (0x32451c family), intrusive-list element accessors (0x3244b4 family), trampoline-instruction installers (0x324654 family, pre-encoded arm64 instruction words written to 0x656xxx slots), and slot/dispatch stubs fill the rest.
- **Evidence**: decompile outputs (e.g. `FUN_00323304` full 8-arg dispatch template with retry-vs-epilogue branch on `sk_dispatch_leave()&1`, TCB arg slots at +0x30..+0x70; `FUN_00322928` family = `sk_sys_pre(); sk_sys_post(); sk_sys_ipc_common();`; badge-gated stores `*(x19+8)=sk_dispatch_leave()` after `sk_badge(); sk_cap_check();`; `FUN_00324ee4` buffer-error raise with negative-size → noreturn fatal path). All 120 transcribed into sk_slice_gap00.c, compile-clean (0 errors).
- **Severity (hypothesis)**: Medium — this is the guest→kernel syscall dispatch surface. The capability-message handling resolves a cap and runs an op through a dispatch table keyed on the guest-supplied cap/index; a bug in the cap-check/badge-mask gates or the retry-continuation branch could let a malicious exclave reach a handler with an unchecked cap. The guard slots (sk_guard_slot_store 0x324764, sk_guard_init_pair 0x325088) only install a dispatch result when the run-queue lookup returns 0. The Swift buffer-error raisers (0x324e8c/e90/eb8/ebc → 0x324ee4) are fatal preconditions with a negative-size check; the negative path hits a noreturn trap. No unchecked write on attacker-controlled length found in this slice — the dispatch handlers delegate actual cap validation to the out-of-slice sk_cap_check/sk_cap_lookup (0x35142c/0x371950), which should be audited as the enforcement point.
- **Confidence**: medium (bodies transcribed faithfully from part05 decompiles which were verified against the same Ghidra data; handler identities are confident for the dispatch template; the register-aliased continuation args are modelled per the documented calling convention).

## [SkR05] 0x003c7a80-0x003ccc98 — cL4 message-register object marshalling subsystem (120 fns)
- **Observation**: SKR05 (120 functions) is the cL4 message-register (MR) marshalling subsystem. Each function serializes one object type into a kernel MR buffer (at ctx+0x2140, word-count slot at ctx+0x2150) as a type-tag byte run followed by the object fields. The central dispatcher (cL4_mr_object_dispatch, FUN_003c856c, ~18KB) walks a descriptor's word span and dispatches on each element's 16-bit type tag to per-type marshallers; it and FUN_003cbbf8 (descriptor_e0) build Swift-ABI ownership/argument metadata (@calllee_, @owned, @guaranteed, @pack_inout, @inout, @convention(...)) and, via cL4_obj_get / cL4_obj_set (tags 0x80/0xf4/0xf7), write object-field references derived from untrusted descriptor words into the message object. The dispatcher's unknown-tag path calls noreturn panic FUN_00116d60 (via FUN_004ba510) — fail-closed.
- **Evidence**: decompile outputs (e.g. `FUN_003c856c` full switch on `*(ushort*)(elem+2)` with tags 0x6b..0x7f mapping to single-char type codes and string matches like `0x5f65656c6c616340` "@calllee_"; `FUN_003cbbf8` uses `FUN_003a3430/FUN_003a3460` object-field get/set with tags 0xf7/0x80/0xf4; `FUN_003c7b24` iterates `*(uint*)(desc+1)` bounded; malformed descriptor kinds produce explicit error codes 0xebf/0xec1/0xec8/0xecc/0x813/0x7e0/0x7a2/0x981 rather than unchecked writes; `FUN_003c856c` default-tag path calls `FUN_00116d60` (noreturn) and `FUN_004ba510`). All 120 transcribed into sk_slice_r05.c, compile-clean (0 errors, 0 warnings).
- **Severity (hypothesis)**: Low — this is guest-visible serialization surface. The descriptor kind byte at +0x12 and the element count at desc+1 drive all array spans; every span bound is checked and malformed kinds return an explicit error word instead of touching memory. The one unbounded write is into the fixed MR buffer slot at ctx+0x2150, whose capacity is maintained by the caller (out-of-slice). The object-field chain (cL4_obj_get/set) writes into the message object under the field tags' type discipline; a tag confusion could in principle write a crafted pointer into a kernel object, but the write targets are fixed tags (0x80/0xf4/0xf7) and values are descriptor-word-resolved. Unknown element tags fail closed into a noreturn panic. No unchecked array index or unbounded copy on attacker-controlled length found in this slice.
- **Confidence**: medium (bodies transcribed faithfully from decompiles; region identity confirmed by the contiguous two-letter type-tag table DAT_005d9300..005d9406 and the Swift ABI ownership-string matches; the panic-on-unknown-tag and error-code paths are structural, verified in the decompile).

## [SkR07] 0x3d2f10-0x3d952c — Swift stdlib + `_Concurrency` async/executor runtime (120 fns)
- **Observation**: SKR07 (120 functions) is the embedded Swift standard-library + concurrency runtime: Unicode scalar-property table lookups (two-level bitmap/popcount indexers FUN_003d326c/FUN_003d3398 and the case-mapping/script/category getters 003d3470-003d3c88), `pthread_once`-style once primitives (FUN_003d3dd8 on globals 0x6c0b30/0x6c0b40, with cnd_broadcast/cnd_wait/mtx_lock failure asserts), the double/float `strtod`-style parser with NaN/Inf literal detection (FUN_003d3200/003d3130/003d30c4/003d319c), and the Swift `_Concurrency` async task/executor machinery (FUN_003d40bc-003d952c: task-suite setup/enter/body/finish frames, reference-counted continuations, executor run-loop guards). The runtime fatal-error paths are reachable: `Call of deleted metatype` (003d4d0c), `Can't drop a negative number of...` (003d6418/003d72f0), `run(until:) not supported` (003d4f78), all terminating via `cL4_runtime_fatal` (FUN_001afa84) with source-file metadata `_Concurrency/Errors.swift` / `_Concurrency/Executor.swift`.
- **Evidence**: decompile outputs (e.g. `FUN_003d3200` scans for signed "nan"/"snan" tokens; `FUN_003d3dd8` is a full once-token machine with `s_cnd_broadcast__onceCond___failed_005dbc8c`; `FUN_003d3964` walks per-scalar case-mapping records writing mapped bytes + space separators with a hard buffer bound; `FUN_003d6418`/`FUN_003d72f0` branch on `-1 < count` then trap via SoftwareBreakpoint; ~40 async-task bodies have the decompiler warning "Could not recover jumptable at 0x003d…", reconstructed at structural level). All 120 transcribed into sk_slice_r07.c, compile-clean (0 errors; 318 warnings, all benign — deprecated empty-prototype decls, null-deref of `*(…*)0` register-marker reads, and callee-saved-register placeholders).
- **Severity (hypothesis)**: Low — this is in-kernel runtime support, not directly guest-reachable syscall surface. The once primitive is a correct pthread_once pattern (no double-init race: armed flag, run, mark -1, broadcast). The Unicode table lookups are read-only over fixed static tables with no attacker indexing (bounds via `0x7fffffffffffffff` sentinel). The float parser and case-mapping writer check their buffer bound. The only hazard class is the async-task machinery: several frames are reconstructed at structural level (unrecoverable jump tables) so a subtle control-flow bug in a continuation handoff would be missed — but these run only on in-kernel tasks, and the async task suite paths do not index by untrusted input. The negative-count asserts fail closed into a noreturn trap.
- **Confidence**: medium (Unicode/once/parser bodies transcribed faithfully and high-confidence; async executor bodies are structural reconstructions of decompiles whose jump tables Ghidra could not recover, confidence low per the affected entries).

## [SkR21] 0x4635a4-0x463fd0 — Swift Unicode script-name string table + runtime thunk fragments (120 fns)
- **Observation**: SKR21 (120 functions) is a dense run of small runtime fragments: 16-byte inline Swift-string constants for Unicode script names ("Pahawh_Hmong", "Warang_Citi", "MedefaidrinKakui", "Psalter_Pahlavi", "Old_Hungarian", "Sora_Sompeng", "Chorasmian", "Manichaean", "Phoenician", "Devanagari", "Cypriot_Minoan", "Pau_Cin_Hau", "Syloti_Nagri", "Meeitei_Mayek", "New_Tai_Lue", "Dives_Akuru"), punctuation/placeholder small strings, register-save/arg-block snapshot helpers, a lower/upper case-transform dispatch, tail-calls into shared runtime routines, and ~70 no-op stubs. The string constants are read-only inline data — the case-transform dispatch (0x463924) and the script-name getters take no attacker-controlled index.
- **Evidence**: decompile outputs — e.g. FUN_00463ad4 returns `{0x485f687761686150, 0xec000000676e6f6d}` = "Pahawh_Hmong"; FUN_00463924 calls `FUN_003722e4(0,s,s,s_lower_upper_005e1f90,0)`; FUN_00463810/FUN_004638d8 are pure word-copy snapshots; 70 addresses (0x4635c8, 0x4635f0, … 0x463fd0) have empty `return;` bodies. All 120 transcribed into sk_slice_r21.c, compile-clean (0 errors).
- **Severity (hypothesis)**: Low — in-kernel Swift runtime string/register-fragment layer, no attacker indexing; the only mutating site (0x463ab8) increments a fixed field at `*obj+0x10` (a reference counter) and is bounded by callers. No security boundary crossed in this slice.
- **Confidence**: high (all bodies are simple constants / copies / tail-calls, faithfully transcribed).

## [cL4-sk] 0x00384f48 cL4_obj_table_lookup_insert — recreation keyed object/cap lookup on wrong register
- **Observation**: The transcribed dispatcher originally passed `id` (param_1) as the table lookup key, but the decompile keys BOTH halves on `param_2` (mode): the even (table-1) half computes stride as `(ulong)param_2*8+8` and probes with `param_2`; the odd (table-2) half derives the capability key as `(param_4 ? 0x80000000 : 0) | (param_2 & 0x7fffffff)` and never reads param_1. Passing `id` instead of the mode-derived key would resolve the wrong object/capability. Also `entry[10]` was a bogus `(x==0)?0:0` placeholder instead of `DAT_004f2758`.
- **Evidence**: decompile FUN_00384f48 even path `stride = (ulong)param_2 * 8 + 8`, `local_8c = param_2`, `local_74 = param_2`; odd path `uVar19 = uVar19 | param_2 & 0x7fffffff` (param_1 unused); `local_68[10] = DAT_004f2758;`. Fixed in sk_region_tightbeam.c dispatcher to pass `mode`/`mode|0x80000000`/`mode&0x7fffffff`.
- **Severity (hypothesis)**: medium — recreation correctness bug in capability/object table resolution; would be a wrong-key lookup if the transcription were the real code.
- **Confidence**: high (ground truth is the decompile register usage).

## [SkR23] 0x46493c-0x4651d4 — Swift Unicode script-name string table + runtime thunk fragments (120 fns)
- **Observation**: SKR23 (120 functions) is a dense run of small runtime fragments contiguous with SKR21: 16-byte inline Swift-string descriptors for Unicode script names ("Mende Kikakui", "Old Hungarian", "Telugu", "Thaana", "Brahmi", "Yezidi", "Chakma", "Tai_Le", "Kaithi", "Lepcha", "Syriac", "Hebrew", "Rejang", "Khojki", "Bassa_Va", "Cuneifor", "Sundanes", "Palmyren", "Medefaid", "Malayala", "Lao", "Batak", "Runic", "Takri", "Tamil", "Khmer", "Osage", "Buhid", "Thai"), error-message fragments ("<invalid", "character '", " digits ... in '", "( *", "(?"), a small struct-copy helper (0x464a50), word-tag combiners, and ~70 no-op stubs plus tail-calls into shared runtime routines (FUN_00117cc4 memcpy, FUN_0036b270 retain, FUN_003a25d4). The string constants are read-only inline data; the tag words (0xe1/0xe2/0xe3/0xe6/0xec) are Swift small-string discriminators, not pointers except the single DAT_00696156-referencing descriptor (0x464f04).
- **Evidence**: decompile outputs — e.g. FUN_00464bf4 returns `{0x7567756c6554, 0xe600000000000000}` = "Telugu"; FUN_00464a50 copies fields at +8/+0x10/+0x18/+0x20/+0x28; FUN_00464dd8 returns `param & 0xffff000000000000 | 0x6e000000000000`; ~70 addresses have empty `return;` bodies. All 120 transcribed into sk_slice_r23.c, compile-clean (0 errors).
- **Severity (hypothesis)**: Low — in-kernel Swift runtime string/register-fragment layer; the script-name getters take no attacker-controlled index and all forwarders pass caller-derived lengths/objects to the shared memcpy/retain helpers, whose bounds are enforced by the (out-of-slice) callees. No security boundary crossed in this slice.
- **Confidence**: high (all bodies are simple constants / copies / tail-calls, faithfully transcribed).

## [SkR24] 0x4651e4-0x4659d4 — Swift Unicode script-name string table + runtime thunk fragments (120 fns)
- **Observation**: SKR24 (120 functions) is a dense run of small runtime fragments contiguous with SKR23/SKR21: 16-byte inline Swift-string descriptors for Unicode script names ("Ahom", "Modi", "Newa", "Lisu", "Cham", "numeri", "lowercas", "sorasomp" [Sora Sompeng], "gunjalag" [Gunjala Gondi], "cypromin" [Cypriot Minoan], "chorasmi" [Chorasmian], "armenian", "pahawhhm" [Pahawh Hmong], "oldnorth" [Old North Arabian], "olditali" [Old Italic], "currentc"), plus word-tag combiners that OR a fixed ASCII prefix ("exta", "nese", "Digi") or letter ('r','c') into a caller-supplied fragment, a NEON byte-OR combine (0x4655fc), the "Fatal error" string getter (0x46565c), small struct-copy/byte-load helpers, tail-calls into shared runtime routines (FUN_00117cc4 memcpy, FUN_003a25d4 release, FUN_0036b270 retain, FUN_00229a3c siphash byte), and ~50 no-op stubs. The string constants are read-only inline data; the script-name getters take no attacker-controlled index.
- **Evidence**: decompile outputs — e.g. FUN_004651e4 returns `{0x6d6f6841, 0xe400000000000000}` = "Ahom"; FUN_00465458 returns `param & 0xffffffff | 0x6174786500000000` = "exta" prefix; FUN_004655fc is a 16-byte NEON rotate-OR; FUN_0046565c returns s_Fatal_error_005accd0; ~50 addresses have empty `return;` bodies. All 120 transcribed into sk_slice_r24.c, compile-clean (0 errors).
- **Severity (hypothesis)**: Low — in-kernel Swift runtime string/register-fragment layer; the script-name getters take no attacker-controlled index and all forwarders pass caller-derived lengths/objects to the shared memcpy/retain/release helpers, whose bounds are enforced by the (out-of-slice) callees. No security boundary crossed in this slice.
- **Confidence**: high (all bodies are simple constants / copies / tail-calls, faithfully transcribed).

## [SkR22] 0x463fe8-0x464930 — Swift Unicode script-name string table + runtime thunk fragments (120 fns)
- **Observation**: SKR22 (120 functions) is a dense run of small runtime fragments contiguous with SKR21 (0x4635a4-0x463fd0) and SKR23 (0x46493c-0x4651d4): 16-byte inline Swift-string descriptors for Unicode script names ("Siddham", "Tagalog", "Deseret", "Syloti_Nagri", "Psalter_Pahlavi", "Meroitic Cursive", "Hanifi Rohingya", "Bopomofo", "Gurmukhi", "Gujarati", "Cherokee", "Ol_Chiki", "Linear_A", "Tagbanwa", "Tai_Viet", "Tai_Tham", "Kayah_Li", "Mahajani", "Vithkuqi", "Imperial Aramaic", "arabic"), a family of tagged-pointer/word-pair factories (lo = error/kind code 0xd0..., hi = (ptr-0x20)|0x8000000000000000), small struct field-copy helpers, single helper tail-calls (FUN_00117cc4 memcpy, FUN_0036b270 retain, FUN_002a4ab4, thunk_FUN_002acbb8 report emit, FUN_0042ec68, FUN_0029fa0c, FUN_001a84f4), and ~37 no-op stubs. The string constants are read-only inline data; the script-name getters and tagged-pointer factories take no attacker-controlled index.
- **Evidence**: decompile outputs — e.g. FUN_00464694 returns `{0x6f666f6d6f706f42, 0xe800000000000000}` = "Bopomofo"; FUN_00463fe8 returns `{0x20, 0xe100000000000000}`; FUN_00464388 returns `{0xd00000000000001a, (p-0x20)|0x8000000000000000}`; FUN_00464568 writes a 16-byte value + two register fields into `*dst`; 37 addresses (0x463ff4, 0x464000, 0x46400c, ... 0x464930) have empty `return;` bodies. All 120 transcribed into sk_slice_r22.c, compile-clean (0 errors, 2 benign stack-address warnings from register-fragment functions).
- **Severity (hypothesis)**: Low — in-kernel Swift runtime string/register-fragment layer, no attacker indexing; the tagged-pointer factories build capability words with the top bit set, but the values are caller-derived and no unchecked dereference is present in this slice. The only mutating sites are fixed-offset struct copies (obj+0x10, +0x20, +0x38..+0x48) and bounded refcount acquires. No security boundary crossed in this slice.
- **Confidence**: high (all bodies are simple constants / copies / tail-calls, faithfully transcribed).

## [SkR20] 0x462ba8-0x463590 — Swift runtime string/register-fragment glue layer (120 fns)
- **Observation**: SKR20 (120 functions) is a dense run of tiny cL4 runtime glue leaves contiguous with SKR21-24: one-line forwarders into the shared Swift string compare `sk_swift_str_cmp_ci` (FUN_002a0cf8) against fixed tagged words (0xd0..0xeb-prefixed Swift string descriptors), the string-flush helper FUN_0029fa0c, the UTF-16 view advance loop FUN_002b4120, and the emit helper FUN_002a4ab4; plus 16-byte inline Swift-string descriptor constants (e.g. {0x29,0xe100000000000000}, {0xd00000000000001b, p|0x8000000000000000}), small fixed-offset field-copy/read leaves, a NEON byte-OR combine (0x463558), a refcount-acquire message dispatch (0x463418), and ~55 no-op stubs.
- **Evidence**: decompile outputs — e.g. FUN_00462bc0/463130/463520 return compare against `0xe100000000000000`; FUN_00462f3c/463514 return `{0x29/0x27, 0xe100000000000000}`; FUN_00463418 builds a 6-word message (`length = (p2>>0x38)&0xf`) then `thunk_FUN_0036b270(p2)` (sk_refcount_acquire_c); FUN_00463558 byte-ORs four 16-byte inputs then rotates-ORs (NEON_ext(.,.,8,1)) into an 8-byte result; 55 addresses have empty `return;` bodies. All 120 transcribed into sk_slice_r20.c, compile-clean (0 errors, 28 benign `-Wdeprecated-non-prototype` warnings from variadic out-of-slice helper calls).
- **Severity (hypothesis)**: Low — in-kernel Swift runtime string/register-fragment layer, no attacker-controlled indexing. The only length derivation (0x463418) is `(p2>>0x38)&0xf` (4-bit, caller-derived) before the refcount acquire; the byte-OR helper reads a fixed 64 bytes; all other sites are fixed-offset copies or constant returns. The register-artifact functions (e.g. 0x462bd8, writing caller-frame slots at -0x88..-0x70) write only to the caller's own stack frame. No security boundary crossed in this slice.
- **Confidence**: high (all bodies are simple constants / copies / tail-calls / empty stubs, faithfully transcribed; the 16-byte-return and message-dispatch sites match the sibling SkR21-24 reconstruction).

## [VerifyB1] 0x001da714 sk_r5_fatal_assert_001da714 — SBORROW8 trap transcribed as ADD-overflow (fixed)
- **Observation**: Verification sweep of the transcribed body of FUN_001da714 found the carry-overflow trap guarding a Swift-runtime length computation at 0x1dae9c was transcribed with `ovf(...)` (defined as `__builtin_add_overflow`) where the decompile shows `SBORROW8(extraout_x8_07, lVar2 / 2)` (subtract overflow). A bounds/carry check that is supposed to detect subtraction overflow would instead detect addition overflow — a semantics mismatch in a potentially security-relevant length-guard.
- **Evidence**: `curl decompile_function?address=0x001da714` → `if (SBORROW8(extraout_x8_07,lVar2 / 2)) { ... SoftwareBreakpoint(1,0x1dae9c) ... }`; `curl disassemble_function?address=0x001da714` → `0x1dabb4: subs x8,x8,x9 ; 0x1dabbc: b.vs 0x001dae98` (subtract sets V on signed overflow, trap via brk #0x1 at 0x1dae98). Fixed in osfmk/arm64/sk/sk_region_sched.c: `ovf(eo8_07,n2 / 2)` → `SBORROW8(eo8_07,n2 / 2)`.
- **Severity (hypothesis)**: Low — the corrected check is a defensive trap on an overflow in a Swift runtime helper's index/count arithmetic, not a reachable data-flow boundary by itself; but an ADD-vs-SUB overflow guard is exactly the class of mismatch that could let an unchecked value slip through a bounds check, so it was corrected to match ground truth.
- **Confidence**: high (ground truth is the disassembly `subs`/`b.vs` sequence; fix verified).

## [SKR25] 0x004659e0-0x004661d8 sk_slice_r25.c — cL4 Unicode-script name region tail
- **Observation**: This 120-function slice is the tail of cL4's Unicode-script name/property lookup region (begun in SKR24). It contains only leaf accessors: ~59 no-op stubs, 8-byte little-endian ASCII script-name fragment returns ("warangic", "saurahst", "kharosth", "bhaiksuk", "palmyren", "kana", "misc", "xofn"), script-name builders that OR a fixed ASCII prefix/letter into a caller word, and 1..8-word struct-field copies / register forwards to sibling-slice helpers (object/cap release FUN_003a25d4, memmove FUN_00117cc4, vspace/ipc transition thunk_FUN_002acbb8, refcount acquire FUN_0036b270, regex diag FUN_0042ec68). No function performs validation, access control, or state mutation beyond the trivial field copies. None is security-relevant by itself.
- **Evidence**: decompiles (curl 127.0.0.1:8089): 59 bodies are `return;`; ASCII literals 0x6963676e61726177 (warangic) etc.; the rest are store/copy patterns over unaff_x19/x20 offsets and one-word forwards to the listed callees. Compiles 0 errors.
- **Severity (hypothesis)**: informational — a static data/accessor table in the GL1 microkernel's string layer; the script-name constants are inert. No observed weakness; the region is a low-value audit target.
- **Confidence**: high

## [cL4-sk] 0x00091550 cl4_ep_launcher_init — endpoint binding handlers misaligned in recreation
- **Observation**: The recreated endpoint-launcher registered its 9 bindings with handlers shifted by one from binding 4 onward (b3 got cl4_op_call0 when both b2/b3 use the caller-set d8 handler; b4-b8 each got the NEXT binding's handler; b9 referenced an undefined cl4_ep_send4). The success branch was also dead-coded (`if(0)` instead of `unaff_x21==0`) and the descriptor dropped b9. Binding an endpoint to the wrong dispatch handler would route capability/object operations to the wrong callback.
- **Evidence**: disassembly of FUN_00091550 binding loop: B1 handler 0x91f8c; B2/B3 `stur d8` (caller-set, same value); B4=0x92270, B5=0x92394, B6=0x924d4, B7=0x9261c, B8=0x92774, B9=0x928c4 (adrp/add pacia'd loads); tags 0x939fc..0x93a58 and strings 0x65fd60..0x65fea0. Fixed in sk_region_caps_04.c.
- **Severity (hypothesis)**: medium — a mis-registered endpoint binding could invoke the wrong handler for a launcher op; recreation-correctness issue now aligned to ground truth.
- **Confidence**: high (ground truth is the disassembly constant loads).

## [VerifyB1] 0x00052c54 sk_init_cnodes — cnode-address byte-assembly read-width mismatch (fixed)
- **Observation**: Verification sweep of the transcribed body of FUN_00052c54 (sk_init_cnodes) found three cnode-descriptor address-assembly expressions read an 8-byte `uint64_t` where the decompile reads a 3-byte `uint3`. The descriptor word is assembled as `*p | p[1]<<0x10 | byte+3<<0x18 | (uint3 at +4)<<0x20`; the 8-byte read pulled the byte at offset +7 into bit 56-63 of the computed cnode base address. Byte +7 holds real data (the do-while element-count uses it: `(uint)byte p[3]<<0x10 | byte+7<<0x18 | p[2]`), so the corrupted high bits could yield a wrong cnode/capability address.
- **Evidence**: `curl decompile_function?address=0x00052c54` → `(ulong)*(uint3 *)(puVar20 + 2) << 0x20` (3-byte read at offset +4) and `uVar4 = *(uint3 *)(puVar20 + 8)` (3-byte read at offset +16), and case-11 `*puVar15 = ... | (ulong)*(uint3 *)(puVar20 + 2) << 0x20`. The body used `*(uint64_t *)(t9 + 2) << 0x20` (8-byte) and `t16 = *(uint64_t *)(t9 + 8)`. Fixed in osfmk/arm64/sk/sk_region_boot.c: replaced with `(*(uint32_t *)(t9 + 2) & 0xffffff) << 0x20` and `t16 = (uint64_t)(*(uint32_t *)(t9 + 8) & 0xffffff)` to reproduce the exact 3-byte little-endian semantics (bits 56-63 = 0).
- **Severity (hypothesis)**: Medium — sk_init_cnodes parses a boot-provided cnode/capability descriptor table (from global DAT_006aff18/006af8d8) and derives cnode base addresses, ranges, and free-slot extents stored into the capability-management structures. An off-by-one-byte in the high bits of those addresses could misplace the free-cnode/TCB/endpoint ranges used by the capability allocator; because the descriptor input is part of the boot/root-task image, this is attacker-relevant only if that image is influenceable. Corrected to match ground truth.
- **Confidence**: high (ground truth is the Ghidra `uint3` reads; fix verified).

## [ringminus1] 000017f4 sk_boot_run (cL4 Secure Kernel boot path)
- **Observation**: The transcribed body of FUN_000017f4 (sk_boot_run) is a structural summary, not a faithful recreation. It covers only the front portion of the decompile (boot-object alloc, record writes to the 0x6ac0xx global table, CNode strmap, devtree_get/validate) and then omits the device-tree walk, CNode/TCB/vspace/page-table construction and the SAS/SAAS/SA/ISA slot wiring, with a comment "Structural summary retained for readability". It also drops the FUN_0036a9a0 zone-object construction and its five field writes (+0x10..+0x28) at the strmap step. This violates the no-stub contract for a security-critical boot path.
- **Evidence**: Decompile of FUN_000017f4 (cl4_kernel.raw) has 145 direct callees across 550 lines (device-tree walk, nlist/CNode frame at 0x6ac098, thunk_FUN_0036b270 etc.); C body (sk_region_boot.c ~L640-708) reproduces only ~the first third and a "boot_failed" stub ending in sk_boot_abort_panic(); the in-between logic (FUN_0036a9a0 zone-object fields, SAS/SAAS/SA/ISA slot wiring, nested SoftwareBreakpoint traps at 0x241c/0x1c5c) is absent.
- **Severity (hypothesis)**: low — the recreation does not faithfully ground-truth the cL4 boot/trust-boundary construction, so any downstream analysis of the initial CNode/TCB/vspace/page-table setup from this body would be incomplete.
- **Confidence**: high

## [ringminus1] 0x000026e8 mislabeled as sk_swift_release in sched region
- **Observation**: Across the sched slice (sk_region_sched.c), FUN_000026e8 (a Swift indirect-dispatch helper, tiny 0x30-byte body, one pointer arg) was systematically transcribed as `sk_swift_release`, whose declared identity is FUN_0036993c (a 4-arg tuple/error builder via FUN_0036a940, 0xf3 bytes). Two distinct Ghidra functions were given the same C name; the 1-arg call sites are FUN_000026e8 and were wrong.
- **Evidence**: Decompile of each affected function (001c0528/1ce704/1cd80c/1c6e84/1cb5c8/1c65d0/1c8f7c/1cabb4/1c9a74/1ca314/1c7768/1c7f48) calls `FUN_000026e8(&stack...)` (1 ptr arg) at sites the C body had as `sk_swift_release(...)`; none of these decompiles call FUN_0036993c. FUN_000026e8 (000026e8-00002717) vs FUN_0036993c (0036993c-00369a2f) are distinct. Corrected to sk_000026e8.
- **Severity (hypothesis)**: informational — wrong-function identity in the recreation would misattribute teardown vs dispatch semantics; corrected.
- **Confidence**: high

## [VerifyB4] 0x000ef4dc iel_build_vm_regions — first-loop return-list append + descriptor block dropped (fixed)
- **Observation**: The transcribed body of FUN_000ef4dc (iel_build_vm_regions) dropped two real elements of the per-frame loop: (1) each frame cap is appended to BOTH the accumulator (`acc`) and the return list (`ret`) in the decompile, but the body only appended to `acc`, so the returned frame-cap list would have been incomplete; (2) the whole per-frame descriptor build (FUN_00086440/0036a9d4/00086590/0036a940/00085a54 creating two descriptors `d9`/`d10`, vtable[0x90] binds of page+cap, vtable[0xe0] checks, cl4_notify_done, memmove FUN_00117d14, and both releases) was absent. It also fabricated `cl4_iel_tlb()` (FUN_00081438) calls inside both loops even though that TLB flush only occurs in the success block.
- **Evidence**: `curl decompile_function?address=0x000ef4dc`: first loop calls `FUN_003a261c(puVar4)` AND `FUN_003a261c(puVar5)` appending `lVar1` to both; then `uVar7=FUN_00086440(0); uVar7=FUN_0036a9d4(uVar7,0x64e1c0); ...; plVar9=FUN_00085a54(); ...; plVar10=FUN_00085a54(); (**(...)(*plVar10+0x90))(0,uVar15); (**(...)(*plVar9+0x90))(0,lVar1); ...(**(...)(*plVar9+0xe0))(); ...; FUN_000f4c14(); FUN_0014b644(); FUN_0009461c(...); FUN_00117d14(); FUN_0036b118(plVar9); FUN_0036b118(plVar10);`. FUN_00081438 only appears in the `bytes-have==0` success block. Corrected in osfmk/arm64/sk/sk_region_caps_20.c. Register-only args to FUN_00085a54/FUN_000f4c9c/FUN_00117d14 are not recoverable from the decompile (kept as empty calls, documented).
- **Severity (hypothesis)**: low — iel_build_vm_regions constructs the frame-capability list for an exclave VM region; the dropped return-list append could have produced an incomplete region frame list and the dropped descriptor binds/notify are part of the page-to-cap binding. Transcription bug, now aligned to ground truth; residual register-only args remain unverified.
- **Confidence**: high (ground truth is the decompile's explicit calls; fix verified).

## [cL4-sk] 0x002a4c88 sk_ubp_append — recreation body gutted to dead `0` values
- **Observation**: The transcribed buffer-append function was degraded: the unaff_x19..x23 callee-saved registers and extraout_*/in_* artifacts were replaced with literal `0`, turning the size/grow/overflow branches into dead `if(0)` paths (append could never actually append or grow), the leading FUN_002a45bc call and the pcVar12 = sk_ubp_append2 address capture were dropped, and `*unaff_x20 = unaff_x19; unaff_x20[1] = unaff_x21;` became `*(word_t*)0 = 0`. The append/ensure/grow logic would never run.
- **Evidence**: decompile FUN_002a4c88 shows `FUN_002a45bc(); pcVar12 = FUN_002a4c98;`, real branch conditions on unaff_x22-x23 / uVar10+uVar11 with SoftwareBreakpoint(1,0x2a4f1c/0x2a4f18), `FUN_00350974(unaff_x23<<0x10|1, unaff_x22<<0x10|1)`, and `*unaff_x20 = unaff_x19; unaff_x20[1] = unaff_x21;`. Re-transcribed in sk_region_obj_slice_02.c (unaff regs as locals, real conditions/constants); kept medium because extraout_x1/x8, in_CY and sk_ubp_finish args are not recoverable.
- **Severity (hypothesis)**: medium — a buffer-append/UBP operation reduced to no-ops in the recreation would hide the actual append/grow/overflow behavior; transcription-correctness issue now aligned to ground truth.
- **Confidence**: high (ground truth is the decompile's explicit register arithmetic).

## [VerifyB1] 0x001d7bb0 sk_r5_fatal_assert_001d7bb0 — dropped 16-byte return flag (fixed)
- **Observation**: The transcribed body of FUN_001d7bb0 (Swift String/UTF8 character-index computation) declared an `undefined8` (8-byte) return and returned only `at16._0_8_`, dropping the hi half of the decompile's 16-byte return `{_0_8_=pos, _8_8_=flag}`. The hi half (uVar8) is a found/not-found flag set to 1 at the success path and 0 otherwise — a caller distinguishing success from failure would see the flag lost.
- **Evidence**: `curl decompile_function?address=0x001d7bb0` → `LAB_001d7f5c: auVar16._8_8_ = uVar8; auVar16._0_8_ = uVar13; return auVar16;` (16-byte `undefined1 [16]`). Body had `return at16._0_8_;`. Fixed in osfmk/arm64/sk/sk_region_sched.c: return type `sk_c16_t`, `return at16;`.
- **Severity (hypothesis)**: Low — the flag distinguishes "hit" vs "miss" for a string/char lookup; a dropped flag could let a caller treat a miss as a hit, but the callers are in-kernel Swift runtime helpers, not a directly guest-controlled boundary. Corrected to match ground truth.
- **Confidence**: high (ground truth is the decompile 16-byte return).

## [VerifyB1] 0x002dfdd4/0x002e1164/0x002df40c/0x002e079c — dropped &LAB_0060e404 msg-callback constant (fixed)
- **Observation**: In four near-identical Swift integer-conversion helpers (FUN_002dfdd4, FUN_002e1164, FUN_002df40c, FUN_002e079c) the 5th argument to the shared runtime call `FUN_00377bec` was transcribed as `((unsigned long)0)` where the decompile passes `&LAB_0060e404` — the address of code at 0x60e404 (FUN_0060e3fc+8), a Swift message/selector callback. Passing 0 instead of a real code address hands the runtime a null callback.
- **Evidence**: decompiles for all four: `uVar10 = FUN_00377bec(uVar4,param_3,lVar5,FUN_0060e3fc,&LAB_0060e404);`. Body had `sk_h_00377bec(tmp,arg,lval,sk_h_0060e3fc,((unsigned long)0))`. Fixed in osfmk/arm64/sk/sk_region_obj_slice_09.c: added `extern sk_h_0060e404` and passed `sk_h_0060e404` at all 8 call sites.
- **Severity (hypothesis)**: Low — these are integer-width-conversion / emission helpers on the error/overflow paths; a null message-callback would only be reached after a range/overflow trap path fires, but the dropped constant is a real transcription error and was corrected.
- **Confidence**: high (ground truth is the decompile `&LAB_0060e404`).

## [VerifyB1] 0x0040e2f0 sk_task_group_store — wrong tail callee (destroy vs append) (fixed)
- **Observation**: The tail of FUN_0040e2f0 (task-group result ring store) ended by calling the wrong function: it invoked `sk_cont_buf_destroy((word_t)queue, (word_t)&old)` where the decompile calls `FUN_0040e79c(param_1,&local_88)` — that is `sk_cont_buf_append`, which stores the child record. Calling the variadic destroyer here would free/tear down the ring instead of appending the record.
- **Evidence**: `curl decompile_function?address=0x0040e2f0` tail: `else { param_1[4] = uVar9 - 0x200; local_88 = (undefined8 *)*puVar1; param_1[1] = (ulong)(puVar1 + 1); } FUN_0040e79c(param_1,&local_88);`. FUN_0040e79c is transcribed as `sk_cont_buf_append` (defined at sk_slice_189.c:3199). Fixed: `sk_cont_buf_append(queue, &old);`.
- **Severity (hypothesis)**: Medium — the task-group result store is the sink for child-task completion records; invoking the destroyer instead of the appender on the non-grow path would corrupt/release the result ring (a logic/safety bug in a concurrency-facing kernel data structure). Corrected to match ground truth.
- **Confidence**: high (ground truth is the decompile FUN_0040e79c call).

## [SkR28] 0x0047c528-0x004815cc — Swift stdlib Unicode scalar/regex/error-code runtime leaves (120 fns)
- **Observation**: SKR28 (120 functions) is a dense run of Swift standard-library runtime leaves: ~50 scalar character-property test wrappers (each calls an out-of-slice scalar-property bit-tester FUN_002bxxxx and stores `result & 1` into a bool out-slot), UTF-8/UTF-16 scalar decoders with 1/2/3-byte continuation handling (FUN_0047ef1c/0047ee98/0047edf4/0047f630), case-insensitive scalar range membership tests (FUN_0047ead4, FUN_0047e96c), an ASCII case-fold helper (FUN_0047e8ec), regex parse-error string builders (FUN_0047d73c), the L4 error-code → Swift error-object factory (FUN_0047fa44, high confidence — string constants `L4_ErrorCode*` at 0x688248-0x688698 map codes 0..0x25 to per-code messages and constructors), a Unicode/regex error factory (FUN_004801f8, including the `TODO: map PCRE special` / `TODO: map Java special` report strings), and a message/op dispatch switch (FUN_0047dfc4). The error-object factories allocate an error context and chain constructor functions; the switch reads a kind byte at self+0x20 and dispatches.
- **Evidence**: decompile outputs — e.g. `FUN_0047fa44` switch over codes 0x0..0x25 selecting between `s_L4_ErrorCodeSuccess_006884d8`, `s_L4_ErrorCodePermissionInvalid_00688498`, `s_L4_ErrorCodeCapInvalid_006883f8`, `s_L4_ErrorCodeMethodInvalid_006882d8`, `s_L4_ErrorCodeSlotInvalid_006882b8`, `s_L4_ErrorCodeArgumentInvalid_00688458`, `s_L4_ErrorCodeOperationInvalid_00688478`, `s_L4_ErrorCodeTruncated_006883d8`, `s_L4_ErrorCodeCanceled_006883b8` and constructors `DAT_004aa204`/`DAT_004aa240`/`FUN_004a3f30`; `FUN_0047dfc4` reads `*(x20+0x20)` kind byte and for kind 7 emits `s_L4_ErrorCodeCanceled_00688688`; the scalar property wrappers call FUN_002bxxxx bit-testers over the shared scalar-property word FUN_003d36b0. All 120 transcribed into sk_slice_r28.c, compile-clean (0 errors; 337 benign warnings — deprecated empty-prototype K&R externs for the ~300 out-of-slice helpers, and one noreturn inline).
- **Severity (hypothesis)**: Low — in-kernel Swift runtime string/error/property layer, not guest-reachable syscall surface. The error-code factory maps caller-supplied codes to fixed per-code messages and constructors; the scalar decoders and range tests read bounded caller buffers and trap via SoftwareBreakpoint on overflow/underflow rather than continuing with a bad pointer. The dispatch switch constructs error/context objects from a self-owned kind byte; no untrusted index reaches a global table in this slice.
- **Confidence**: medium (the simple property wrappers, constants and error-code factory are faithful; the complex UTF-8 decode / regex-loop / range-CI bodies (0047ead4, 0047e5dc, 0047f630, 0047dc1c, 0047cadc) are structural reconstructions of register-heavy decompiles — unaff_*/in_* register artifacts modeled as zeroed locals, confidence low per those entries).

## [VerifyB2] 0x001d4584/0x001d7368/0x001de04c sk_r5_* — pair-return high word (x1) dropped in recreation (fixed)
- **Observation**: Three sched-region functions transcribed the pair-returning out-of-slice helpers (sk_0008e388, sk_003508b4, sk_003508a8, sk_003518c4, sk_003514e8, sk_00351324, sk_00351330, sk_00350944, sk_003504ac) as single-word returns and hardcoded the high return word to 0. The decompile passes both `_0_8_` and `_8_8_` words to the consuming indirect calls. Disassembly confirms these helpers `mov x0,...; mov x1,...; ret` (128-bit returns) and the caller's `blraa` consumes both x0 and x1 unchanged.
- **Evidence**: disassemble of FUN_0008e388 (`mov x0,x21; mov x1,x23; ret`), FUN_003508b4 (`mov x0,x27; mov x1,x22; ret`), FUN_003508a8 (`mov x0,x27; mov x1,x21; ret`); caller disasm at 0x1d481c/0x1d490c/0x1d4950 passes x0:x1 straight to `blraa`. Fixed in sk_region_sched.c: added `sk_r4_u128_t sk_h_<addr>()` externs and capture both words.
- **Severity (hypothesis)**: medium — dropping the high word of a pair-returning object-service helper changes what the dispatch handler receives; in the sched/object-model path this can alter capability/object id propagation. Recreation-correctness issue, now aligned to ground truth.
- **Confidence**: high (ground truth is the helper disassembly register pairs).

## [VerifyB2] 0x000a46cc exclave_region_load — vtable pair-return calls split into two distinct calls (fixed)
- **Observation**: Three single pair-returning indirect vtable calls were transcribed as TWO separate calls: `(*pages+0xe0)()` AND `(*pages+0xe4)()`, and two `ctxfn` calls (with/without arg) each split into a pair of calls. The decompile does one `(**(code **)(*plVar7+0xe0))()` returning a 16-byte pair; the body invented a second call at +0xe4 (a different vtable slot). This would invoke a different object method and mis-bind the exclave context.
- **Evidence**: disasm 0x000a48a4 `ldr x8,[x16,#0xe0]!; blraa x8,x16` (single call, x0:x1 returned, `tbnz x1,#0x3f` consumed); 0x000a4c54/0x000a4d28 single `blraa`. Also the __SANED/__BLADED hash flag check used the low word (`mag & 1`) but disasm `tbz w1,#0x0` checks the HIGH word; index uses low word. Fixed in sk_region_caps_08.c using `cl4_result_t` pair returns.
- **Severity (hypothesis)**: medium — exclave_region_load constructs the exclave context binding; invoking the wrong vtable slot (or wrong hash-flag word) could produce a malformed context/owner selection. Recreation-correctness issue, corrected to ground truth.
- **Confidence**: high (ground truth is the single blraa + w1 flag test in disassembly).

## [VerifyB2] 0x000a75b0 exclave_stackshot_build — wrong helper callee (FUN_000a6e9c vs FUN_000e250c) + wrong flag word (fixed)
- **Observation**: The body computed the frame extent via `cL4_extent` (FUN_000a6e9c, returns obj+0x20) but the decompile/disasm call FUN_000e250c (a min-extent walk over the out-list). The `!= 1` flag check also tested the low word where disasm tests the high word.
- **Evidence**: disasm 0x000a781c `bl 0x000e250c` then `str x0,[sp,#0x10]; str w1,[sp,#0xc]` (pair); FUN_000e250c decompiles to a list-min loop (FUN_000e46d0 `mov w1,#0; ret`). FUN_000a6e9c is a different single-word function. Fixed in sk_region_caps_08.c via `cL4_extent_of` (pair) capturing both words.
- **Severity (hypothesis)**: low — stack-shot descriptor header would carry the wrong per-frame extent value; the descriptor is used by the cL4 exclave stack-shot machinery. Recreation-correctness issue, corrected.
- **Confidence**: high (ground truth is the disassembly call target + pair store).

## [VerifyB2] 0x003cbbf8 cL4_mr_descriptor_e0 — divergent element-walk loop for kind 5/2 (fixed)
- **Observation**: The decompile reuses ONE element-walk loop (LAB_003cbd00) for descriptor kinds 1, 5 (span!=0), and 2. The transcribed body implemented a *different, simplified* `loop5` for kinds 5/2 that skipped the element 0xe2/0xe1 tag dispatch and the 0xec8 invalid-descriptor error path, and used a different element dereference structure.
- **Evidence**: decompile of FUN_003cbbf8: `else if (bVar1==5){ uVar8=*(uint*)(puVar17+1); if(uVar8!=0) goto LAB_003cbd00; } else if (bVar1==2) goto LAB_003cbd00;` — all three kinds enter the same loop body (e2/e1 checks, 0xec8/0xecc error codes). Fixed in sk_slice_r05.c by unifying the three cases into the single shared loop with `cnt` bound.
- **Severity (hypothesis)**: low — a kind-5/2 descriptor would not validate element tags or report the 0xec8 invalid-descriptor error, diverging from the real marshaller. Recreation-correctness issue, corrected.
- **Confidence**: high (ground truth is the shared-loop structure in the decompile).

## [VerifyB5] 0x0005d38c sk_lock_acquire + 5 callers — dropped lock-dispatch register args (fixed)
- **Observation**: The lock-acquire path called the register-forwarding dispatch thunk `FUN_0005dc8c` (transcribed `sk_lock_dispatch_10`) with no arguments at all 6 call sites (5d38c x2, 5cc3c, 5d470, 5fac0, 5fad8). FUN_0005dc8c is `(**(code **)(_DAT_006b2690 + 0x10))()` — a tail-jump thunk that forwards whatever is in x0-x4 to the real lock target. The decompile shows all callers passing `(prio/type, lock_word_ptr, cpu_array, target, flags)`; the body passed nothing, so the real lock dispatch target would receive stale/garbage registers instead of the priority + lock pointer, corrupting lock-ordering / priority handling.
- **Evidence**: `curl decompile_function?address=0x5d38c` → `iVar6 = FUN_0005dc8c(uVar2 & 0xff,param_1,uVar7,0,1);`; `0x5cc3c` → `FUN_0005dc8c(uVar2 & 0xff,param_1,uVar6,uVar8,param_2);`; `0x5d470` → `FUN_0005dc8c(uVar2,param_1,uVar8,uVar6,0);`; `0x5fac0`/`0x5fad8` → `FUN_0005dc8c(uVar5,piVar1,uVar7/8,0,0);`. Fixed in sk_region_boot.c: thunk now takes/forwards `(a1,a2,a3,a4,a5)`, all 6 call sites pass the decompile args.
- **Severity (hypothesis)**: medium — lock dispatch with wrong prio/lock-word args could mis-order or mis-dispatch the kernel's recursive/priority lock path.
- **Confidence**: high (ground truth is the decompile call sites + the forwarding-thunk body).

## [VerifyB5] 0x00053db8 sk_cnode_create — kind table read from wrong base (fixed)
- **Observation**: The cnode-kind table lookup read from `sk_global_002` (the 0x6b0340 retype-object global) instead of the constant table at `0x4bcce0`; the disassembly loads `adrp 0x4bc000; add #0xce0` → `ldr w8,[x9,w8,UXTW#2]`. The record-word byte layout was also wrong (byte1 flag / byte2 num_caps / byte4 0x20 per disasm sp+0x28; body had a different packing). Corrected in sk_region_boot.c.
- **Evidence**: disassemble 0x53db8: `53e3c: adrp x9,0x4bc000; 53e40: add x9,#0xce0; 53e44: ldr w8,[x9,w8,UXTW#2]`; `53e50 strb w8,[sp,#0x28] (kind); 53e54 strb w2,[sp,#0x2a] (num_caps); 53e28 strb 0x20,[sp,#0x2c]; 53e6c cset (opts&0x10)==0 → sp+0x29; 53e7c clear sp+0x29`.
- **Severity (hypothesis)**: medium — a cnode with the wrong kind byte / record encoding would create a capability with incorrect type/badge, affecting capability type checks.
- **Confidence**: high (ground truth is the disassembly; fix compiles).

## [VerifyB5] 0x0008d64c cL4_map_merge_arrays — dropped alloc + missing grow-prefix copy (fixed)
- **Observation**: The array-merge body set `dst = NULL` when n!=0 instead of calling the `alloc(n,0)` callback, dropped the two per-element ref-dec calls in the interleave loop, and the grow path omitted the live-prefix memcpy (FUN_00117d14) that preserves already-merged pairs when the destination grows. Corrected in sk_region_caps_03.c.
- **Evidence**: decompile 0x8d64c: `else { puVar4 = (*param_3)(uVar8,0); FUN_0036b270(); }`; interleave `*puVar17=*puVar10; puVar17[1]=uVar15; FUN_0036b270(); FUN_0036b270(uVar15);`; grow `FUN_00117d14(puVar1,puVar4+0x20,uVar11<<4)`.
- **Severity (hypothesis)**: medium — array merge dropping the alloc/prefix copy would produce a corrupt/partial merged capability array (used for cap-list aggregation).
- **Confidence**: high (ground truth is the decompile; fix compiles).

## [VerifyB5] 0x000dfe2c ec_region_map_vaddrs — wrong count/capacity offsets + off-by-one entry store (fixed)
- **Observation**: The region-list bookkeeping used `region_list[1]` (+0x08) for the count and `region_list[2]` for capacity, but the ground truth is count at +0x10 (`[2]`) and capacity marker at +0x18 (`[3]`); the entry store was off-by-one (indexed by the post-increment loop counter instead of the old count). This could write the block pointer one slot past the intended entry (out-of-bounds) and mis-track growth. The second walk loop also dropped the vtable+0x58 call + release. Fixed in sk_region_caps_16.c.
- **Evidence**: decompile 0xdfe2c: `uVar7 = *(puVar5+0x10); ... *(local_148[0]+0x10)=uVar7+1; *(local_148[0]+uVar7*8+0x20)=local_100[0];`; grow `if (*(puVar5+0x18)>>1 <= uVar7)`; second loop `uVar9 = (*pcVar12)(); ... FUN_0036b118(uVar9)`.
- **Severity (hypothesis)**: medium — off-by-one/offset error in the per-region descriptor list could corrupt the mapped-region bookkeeping (EC vspace map).
- **Confidence**: high (ground truth is the decompile offsets; fix compiles).

## [SkR26] 0x00468ee4 sk_span_build_68ee4 — span-index growth/capacity bookkeeping via SoftwareBreakpoint traps
- **Observation**: The span-index builder maintains a growing index array (FUN_0001dd14) with capacity at desc+0x18 and count at desc+0x10. It performs dense bounds/overflow invariant checks (`if (cap>>1 <= count) grow;`, `if (*(src+0x10) <= idx) panic`) on every element access, and traps (SoftwareBreakpoint 0x469230-0x469250) whenever an index/count goes out of range. These are the cL4 kernel's internal span-list memory-safety invariants.
- **Evidence**: decompile 0x468ee4 — repeated `if (*(ulong *)(lVar5+0x10) <= local_88) SoftwareBreakpoint(1,0x469230)` guards; `if (uVar9 >> 1 <= local_b0) goto grow` for capacity doubling; offset math `desc + uVar9*8 + 0x20` for the entry store.
- **Severity (hypothesis)**: low — the guards themselves are defensive; no confirmed vuln, but the span-index (used by the vspace/EC region map) is a correctness-critical structure.
- **Confidence**: medium (decompile-faithful; register-artifact offsets for the walk were partially inferred).

## [SkR26] 0x00467e44 sk_span_search_67e44 — span walker bounds discipline + loop-underflow panics
- **Observation**: The vspace span-search walker iterates a span array (stride 16 bytes at slots+0x28, count at slots+0x10) and traps (SoftwareBreakpoint 0x4680e4/0x468104/0x46813c/0x468140/0x468144) on every out-of-range index and on the `si--` loop underflow. The page-number step is `>>0xe` (16 KiB granule); the walk validates `pn>>0xe >= cur>>0xe` on entry.
- **Evidence**: decompile 0x467e44 — `if (*(ulong *)(param_8+0x10) <= uVar7) SoftwareBreakpoint(1,0x468140)`; `if (bVar3) SoftwareBreakpoint(1,0x4680e4)` (SBORROW underflow after `uVar8--`); `if (uVar5>>0xe < uVar6) SoftwareBreakpoint(1,0x468144)`.
- **Severity (hypothesis)**: low — defensive invariants; confirms the span array is strictly bounds-checked, which bounds the callback-driven span iteration.
- **Confidence**: medium.

## [SkR26] 0x0046a368 sk_span_build_6a368 — descriptor range validation + unsigned-overflow traps
- **Observation**: The span-build entry validates the descriptor's address range (`hi>>0xe >= lo>>0xe`, else SoftwareBreakpoint 0x46a5c8) and each loop iteration checks `cur>>0xe` against the limit (0x46a5bc) and the "last" page against the iteration page (0x46a5c0); the iteration counter also traps on unsigned overflow (0x46a52c). These are the cL4 kernel's range/overflow invariants on the span walk.
- **Evidence**: decompile 0x46a368 — `if (uVar20 < uVar1>>0xe) SoftwareBreakpoint(1,0x46a5c8)`; `if (uVar20 < uVar12>>0xe) SoftwareBreakpoint(1,0x46a5bc)`; `if (bVar11) SoftwareBreakpoint(1,0x46a52c)` (SCARRY on iter++).
- **Severity (hypothesis)**: low — defensive; no confirmed vuln.
- **Confidence**: medium.

## [SkR26] 0x0046a5c8 sk_syscall_dispatch_6a5c8 — register-artifact-heavy error dispatcher (decompilation-fidelity gap)
- **Observation**: The largest dispatchers (0x46a5c8, 0x466a68, 0x466f18, 0x468144, 0x468888) call hundreds of out-of-range runtime helpers (FUN_0035xxxx/FUN_004aabxx) and dispatch through register-carried object/function pointers (Ghidra `extraout_x8/x9/x16`, `unaff_x24/x25`). Because the exact register provenance is a decompiler artifact, the exact method-slot and argument binding of several indirect calls is only partially reconstructed (modeled via SK_VMETHOD/code_fn casts). This is a recreation-fidelity gap, not a confirmed runtime flaw, but the error-report paths (L4_ErrorCodeOperationInvalid/ArgumentInvalid/CapInvalid) should be re-verified against disassembly before trusting the reconstructed control flow.
- **Evidence**: decompile 0x46a5c8 — `(*(code *)&SUB_54ffff60f100041f)(*(undefined8 *)(extraout_x8_00 + 0x40))` (guarded-entry supervisor calls) and dozens of `(*extraout_xN)(...)`/`(**(code **)(extraout_x16+0x20))(...)` indirect dispatches whose targets depend on untracked registers.
- **Severity (hypothesis)**: medium — the cL4 syscall error dispatch is a trust boundary; a misbound method/arg in the reconstruction could mask or alter the real error path. Verify against disassembly.
- **Confidence**: low (register artifacts; bodies are faithful to the decompile but the chained indirect dispatch is best-effort).

## [ringminus1] 0x00481600-0x0048fe4c SKR29 — Swift _StringProcessing regex engine in the Secure Kernel (GL1)
- **Observation**: The cL4 Secure Kernel embeds a full Swift Foundation/RegexBuilder regular-expression engine (the `_StringProcessing` AST-to-DSL converter and matcher). This means GL1 ships general-purpose regex support in-ring, presumably for policy/sandbox pattern matching inside Exclaves. Several converter helpers emit explicit "TODO: ..." placeholder snippets for unsupported constructs (character classes, assertions, backreferences, subpatterns, callouts, consumers, character predicates, conditional expressions), indicating the embedded DSL printer intentionally degrades to placeholders rather than panicking.
- **Evidence**: 120 functions in sk_slice_r29.c; string refs `s_StringProcessing_ASTConversion__005e21e0` (FUN_0048f61c), `s__AppleInternal_Library_BuildRoot_005e2230` (FUN_0048f61c/FUN_0048afec), `s____TODO__conditional____005e3080` (FUN_0048afec/0048f61c), `s____TODO__character_classes____005e3120`, `s____TODO__backreferences____005e30c0`, `s_Anchor_startOfLine_005e2bd0`, `s__horizontalWhitespace_005e2e00`; tagged 16-byte returns (0xe0|len / 0xea...) in the property-name printers (FUN_0048e570/004867a4).
- **Severity (hypothesis)**: low — regex engines are historically a source of memory-safety bugs (backtracking, huge match counts); FUN_004863d8 uses LZCOUNT-style bit-index decoding of a decision tree and FUN_00485418 drives a large opcode switch that would reward fuzzing. The "TODO" placeholders suggest the shipped feature surface is narrower than the matcher's instruction set.
- **Confidence**: medium

## [ringminus1] 0x0048f61c sk_regex_ast_to_dsl
- **Observation**: The AST->DSL converter carries a Swift build-time source path (`/AppleInternal/Library/BuildRoot/...`) in the binary and builds each output node as a tagged 0x6000000000000000 heap object. Register-global state (unaff_x20/x19) plus `extraout_*` carry flags pervade the slice, so the exact node-linking is only reconstructed at low confidence.
- **Evidence**: `s__AppleInternal_Library_BuildRoot_005e2230` passed to thunk_FUN_0044f818 in FUN_0048f61c; `FUN_0036a940()` object allocators tagged `|0x6000000000000000`; register-global unaff_x20 throughout.
- **Severity (hypothesis)**: informational — leaked internal build path; low-confidence reconstruction of register-global linkage is an audit caveat.
- **Confidence**: high
