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
