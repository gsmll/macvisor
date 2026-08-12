/* Recreated from kernelcache.arm64.kc (xnu-12377.121.10 RELEASE_ARM64_T8142, image base fffffe0007004000). Ground truth: Ghidra FUN_ names + addresses; all names are estimates. */

/*
 * hv_hvc.h — guest hypercall (hvc) interface constants (est.).
 *
 * Owned by the hvc-abi tree. Documents the guest->host HVC ABI as observed in
 * the recreated hv_vcpu_run / hv_el2_guest_esr_classify reconstructions.
 *
 * ============================================================================
 * GUEST HYPERCALL ABI — what IS observed
 * ============================================================================
 *
 * The guest issues an AArch64 `hvc` instruction at EL0/EL1; the exception
 * traps to the hypervisor EL2 vectors (hv_el2.c), the guest state is saved to
 * el2_state (base = vcpu->el2_state), and the run hub (hv_vcpu_run,
 * est. hv_vcpu_run) dispatches on the exit.  Two dispatch levels are present:
 *
 *   1. The EL2 guest-ESR classifier (hv_el2_guest_esr_classify, est.
 *      hv_el2_guest_esr_classify, full body in hv_el2.c) decodes ESR_EL1
 *      EC = (esr >> 26) & 0x3f and writes:
 *        - the raw ESR low 32 bits   to es+0x4010
 *        - the ISS (esr & 0x1ffffff) to es+0x4018  (for SVC)
 *        - an exit-code word         to es+0x4008
 *      Standard EC values are used here: SVC 0x18 -> exit 8 (ISS captured at
 *      +0x4018), 0x1d -> 0xd, IABT 0x20 -> fault reason 5, DABT 0x24 -> fault
 *      reason 1/3, SMC-ish 0x3f -> 0x80000000/7/8/1 by ISS.  HVC is NOT one of
 *      the classifier's handled classes; it falls through (guest pstate
 *      host-abort check / "Unrecognized guest trap" panic on unmapped EC).
 *
 *   2. The run hub (hv_vcpu_run, case 0x8 -> FUN_fffffe000b98a08c) then
 *      "masks es[0x4018] against 0x332c00..0x30fc1e families and dispatches on
 *      the encoded exception class" via a jump table at 0xfffffe000b989cf4.
 *      es[0x4018] is the ISS of the guest exception.  This is the HVC path: the
 *      hub selects the hypercall handler by the ENCODED IMMEDIATE/ISS in
 *      es[0x4018], NOT by a general-purpose register such as x16/x0.
 *
 * SO what is / is not known (deepened by TreeRunHubDeep, 3958-instruction
 * disassembly + targeted disassemble_bytes on the HVC dispatch region):
 *
 *   [known]   The hypercall SELECTOR is the `hvc #imm` immediate (the ISS),
 *             NOT a general-purpose register.  The run hub loads the ISS
 *             (es+0x4018) into a scratch GPR (x8) and the HVC64 case
 *             (0xfffffe000b98a76c) compares it against the class tokens
 *             0xc3000003 / 0xc3000004 / ... (materialized via
 *             `mov w9,#imm; movk w9,#0xc300,lsl#16`; `subs xzr,x8,x9`).
 *             No x16/x0 dispatch exists.
 *
 *   [known]   Hypercall enable gating: HVC64 hypercalls are gated by a per-VM
 *             enable mask — `if (imm<=6)` then `mask & (1<<imm)`, else the
 *             hypercall is skipped (not dispatched).  The mask is a 64-bit
 *             word in the container (disasm: `ldr x9,[x21,#0x1350]`; the
 *             reconstruction recorded container+0x2130 — exact offset
 *             unconfirmed).  Imm > 6 (HVC64) is not dispatched.
 *
 *   [known]   Observed hypercall numbers (ISS values dispatched):
 *               HVC64 family (0xc3000000 | imm): imm 3..6 observed
 *                 (mrs/msr-style emulations, timer offset, vcpu-slot CAS).
 *               HVC-32/hint family (0xc1000000 | imm): imm 1..0xf.
 *               IABT-channel family (0x83000000 | imm): imm 0xfeff / 0xff01 /
 *                 0xff03 (an alternate hvc-with-imm encoding channel).
 *               SVC/VM-op family (0xc6000000 | imm): imm 0x10..0x1a routes to
 *                 hv_vm_op_dispatch (b98e020) / hv_vcpu_slot_op (b98e12c) /
 *                 the per-slot map path (b9866d0); gated by the container
 *                 opcode count (vm+0x2128), requires no attach id
 *                 (vcpu+0xe0==0) and no pending SPSR bit.
 *
 *   [known]   Args are read from the guest's SAVED GPR/vector registers in the
 *             EL2 save frame (the low region at es+0x8..0x28; q0/q1 from the
 *             save stack at sp+0x50/0x60; a blob at sp+0x80) — i.e. x0-x3 /
 *             q0-q1 style GPR/vector passing, NOT a dedicated hypercall-arg
 *             register.
 *
 *   [partial] Return convention: the hypervisor writes the emulated result
 *             back into the guest save-frame GPR region (es+0x8 / +0x18 /
 *             +0x28 = guest x0/x1/x2 slots) so the return-to-guest path
 *             re-injects it, and injects the synthetic sentinel
 *             0xfedefacafeadfad9 into that region (or encodes x0..x3).  The
 *             sentinel's exact role (a return/status code in x0 vs. a distinct
 *             emulation-completed marker) is UNVERIFIED — the reconstruction
 *             records both readings ("writing ... the 0xfedefacafeadfad9 magic
 *             into es+0x8/0x18/0x28, or encoding x0..x3").
 *
 *   [unknown] The full 16-bit `hvc #imm` -> operation map beyond the observed
 *             numbers above, and the per-operation arg->register layout and
 *             exact error-code convention (the hub returns 0xfae94001 on the
 *             unhandled-EC path).  Not derivable from the reconstructions;
 *             not fabricated.
 *
 * ============================================================================
 * OBSERVED ESR-CLASS DISPATCH CONSTANTS (run hub, es+0x4008/0x4018 family)
 * ============================================================================
 * The run hub compares these full 32-bit class tokens.  Their EC meanings are
 * the vcpu-core agent's ESTIMATES (recorded in hv_vcpu.c @ b989a44) and are
 * UNVERIFIED: they do NOT match the ARM-architecture standard EC encodings for
 * the same named class (see cross-check below).  They may be an internal
 * hypervisor "exception class token" (e.g. a tag bit OR'd with EC<<26), not a
 * raw ESR_EL1 value.  No correctness claim is made.
 */
#define HV_HVC_ESR_CLASS_HVC     0xc3000000u  /* est. HVC      — EC bits[31:26]=0x30; UNVERIFIED */
#define HV_HVC_ESR_CLASS_UNK     0x83000000u  /* est. IABT-ish — EC bits[31:26]=0x20; UNVERIFIED */
#define HV_HVC_ESR_CLASS_SVC     0xc6000000u  /* est. SVC      — EC bits[31:26]=0x31; UNVERIFIED (label inconsistent with EC decode) */
/* 0xc1xxxxxx family (est. "data aborts" in the earlier partial reconstruction;
 * the deepened TreeRunHubDeep reconstruction identifies it as the HVC-32 /
 * hint range 0xc1000001..0xc100000f).  Recorded with a wildcard lower byte
 * (not a valid C literal) — EC bits[31:26]=0x30, same as HV_HVC_ESR_CLASS_HVC.
 * The "data abort" label was inconsistent with the EC decode and is superseded
 * by the HVC-hint identification; still unverified (assembly-only). */

/*
 * Cross-check — ARM-Architecture standard EC values for these classes, so the
 * reader can see the 0xc3-family tokens above are NOT standard ESR_EL1 ECs:
 *   EC 0x18 = SVC from AArch64 (SVC64)      EC 0x21 = IABT from a lower EL
 *   EC 0x19 = HVC from AArch64 (HVC64)      EC 0x24 = DABT from a lower EL
 *   EC 0x1b = SMC from AArch64 (SMC64)
 * The classifier (hv_el2_guest_esr_classify) DOES use standard ECs
 * (0x18/0x20/0x24/0x3f); only the run-hub's 0xc3-family tokens are nonstandard
 * (they look like an internal "tag bit | EC<<26" class encoding).
 */

/*
 * Observed hypercall numbers, keyed by family.  The selector is the `hvc #imm`
 * immediate (the ISS); the run hub compares the full (class | imm) token.
 */
#define HV_HVC_NUM_HVC64_MIN      3u    /* 0xc3000003 first observed HVC64 imm */
#define HV_HVC_NUM_HVC64_MAX      6u    /* 0xc3000006 last observed HVC64 imm; imm>6 not dispatched */
#define HV_HVC_NUM_HINT_MIN       1u    /* 0xc1000001 HVC-hint range start      */
#define HV_HVC_NUM_HINT_MAX       0xfu  /* 0xc100000f HVC-hint range end        */
#define HV_HVC_NUM_SVC_MIN        0x10u /* 0xc6000010 VM-op dispatch range start */
#define HV_HVC_NUM_SVC_MAX        0x1au /* 0xc600001a VM-op dispatch range end   */
#define HV_HVC_ISS_IABT_FEFF      0xfeffu  /* IABT-channel hvc-imm (0x83000000|imm) */
#define HV_HVC_ISS_IABT_FF01      0xff01u  /* IABT-channel hvc-imm              */
#define HV_HVC_ISS_IABT_FF03      0xff03u  /* IABT-channel hvc-imm              */
#define HV_HVC_ENABLE_MASK        0x2130u  /* per-VM hypercall enable mask offset in container (est.; disasm read container+0x1350) */
#define HV_HVC_OPCOUNT            0x2128u  /* container opcode count gating SVC/VM-op channel (est.) */

/* Per-HVC64-imm enable gating: hypercall `imm` is dispatched only if
 * imm<=6 AND (container_enable_mask & (1<<imm)) != 0. */
#define HV_HVC_GATE_MAX_IMM       6u
