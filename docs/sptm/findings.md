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
