/* Recreated from kernelcache.arm64.kc (xnu-12377.121.10 RELEASE_ARM64_T8142, image base fffffe0007004000). Ground truth: Ghidra FUN_ names + addresses; all names are estimates. */

/*
 * hv_el2.c — EL2 exception vector handlers and the guest->EL2 exit path.
 *
 * Owned by the el2-vectors tree. This is the highest-value hypervisor tree:
 * the exception path a guest takes into the hypervisor. The EL2 vector
 * handlers at b760b10 (sync) / b760f04 (irq) / b761260 (fiq) / b7615bc
 * (error) are entered from VBAR_EL2 when the guest (at EL1/EL0) traps. Each
 * saves the guest's EL1 register state into the per-CPU guest-state frame,
 * switches EL2 control state, verifies the PAC "JOP hash" of the saved
 * sysregs, writes an exit-reason word, and branches to the common dispatch
 * FUN_fffffe000b761930 which erets down to the EL1 kernel exception handler
 * (b75deac family). From there the guest exit is classified (b96743c),
 * faults handled (b967768), and the guest is resumed via
 * FUN_fffffe000b75e468 / b75e5cc (eret).
 *
 * NOTE on the vector table base: the four handlers are large (they each
 * inline the full guest-state save), so they are the handler bodies the
 * 0x80-byte vector slots branch to, not the slots themselves. The EL1 kernel
 * vector table (VBAR_EL1) is 0xfffffe000b75c000 (set by kernel_entry); the
 * EL2 table is a separate 0x800-aligned table whose sync/irq/fiq/error
 * entries resolve to the four handlers below. The exact VBAR_EL2 base was not
 * pinned (no `msr vbar_el2` write site was found in the hv cluster or boot
 * path — it is established during EL2 bring-up outside the recreated code);
 * the handler addresses are ground truth.
 *
 * Offsets are relative to the guest-state block base (see hv_el2.h).
 * EL2 sysreg reads/writes stay literal (UnkSytemRegRead/Write) per the
 * contract; op1=4 encodes EL2, but register identity is unverified.
 */

#include "hv_el2.h"

/*
 * FUN_fffffe000b9679c8 @ 0xfffffe000b9679c8   (est. hv_el2_guest_exc_check)
 * Ghidra: bool FUN_fffffe000b9679c8(ulong param_1,long param_2,ulong param_3,ulong param_4)
 * Pre-dispatch check for a guest synchronous exception. param_1 = ESR,
 * param_2 = ELR, param_3 = FAR, param_4 = SPSR. Walks the dtrace valid-
 * address table (DAT_fffffe0007045690) to decide whether the faulting PC is
 * dtrace-managed (returns true so the caller takes the dtrace path), handles
 * the SVC-ISS 0x11 case, and otherwise returns whether the exception is
 * guest-visible ((SPSR & 0x1c0) != 0 && DAT_fffffe0007e9d348 == -1). Kernel
 * dtrace table referenced; reconstructed as structural notes (low confidence
 * on the dtrace-address semantics). Shared kernel, stub body.
 * Confidence: low
 */

/*
 * FUN_fffffe000b75e5cc @ 0xfffffe000b75e5cc   (est. hv_el2_eret_fast)
 * Ghidra: undefined1 [16] FUN_fffffe000b75e5cc(void)
 * Fast-path return-to-guest tail: the same register restore + SVE Z/P reload
 * + ExceptionReturn() as FUN_fffffe000b75e468, but reached directly when the
 * preemption re-check is bypassed (bit7 of the exit word set). Restores
 * elr_el1/spsr_el1/fpcr/fpsr from the saved frame (HV_EL2_FRAME_* offsets),
 * reloads SVE state when the guest is in SVE mode (type 0x31 object at
 * tpidr+0x120), re-arms the PAC key (3,0,1,0,5) and T1SZ
 * (3,0,1,0,6,0x10001), then ExceptionReturn(). Confidence: medium.
 */

/*
 * FUN_fffffe000b75e420 @ 0xfffffe000b75e420   (est. hv_el2_exception_exit)
 * Ghidra: undefined1 [16] FUN_fffffe000b75e420(void)
 * Exception-exit tail shared by the EL1 kernel exception handlers
 * (b75deac/b75df7c/b75e000/b75e058): restores the saved guest state
 * (elr_el1/spsr_el1/fpcr/fpsr, SVE Z/P regs) and erets back to the guest,
 * guarded by the "Signed thread state manipulated with interrupts enabled"
 * JOP-hash verify (FUN_fffffe000b760444). Confidence: medium.
 */

/*
 * FUN_fffffe000b75e8a8 @ 0xfffffe000b75e8a8   (est. hv_el2_preemption_panic)
 * Ghidra: void FUN_fffffe000b75e8a8(void)
 * noreturn panic "Preemption count negative on thread %p" via
 * FUN_fffffe000c0e11ec, reached when the per-CPU preemption counter
 * (tpidr+0x1c0) is found negative on the exception-exit path. Confidence:
 * high (message + noreturn observed).
 */

/* ---- guest ESR classifier / sync dispatch ----------------------------- */

/*
 * FUN_fffffe000b96743c @ 0xfffffe000b96743c   (est. hv_el2_guest_esr_classify)
 * Ghidra: void FUN_fffffe000b96743c(int *param_1, ulong param_2, undefined8 param_3)
 * Classifies a guest synchronous exception. param_1 = guest-state block
 * (field 0 == 0x14 marks a compact frame, else a full frame), param_2 = ESR_EL1,
 * param_3 = FAR_EL1. Writes the exit code to state+0x4008 (word at
 * param_1+0x1002) and, for SVC, the ISS to state+0x4018. Decodes ESR EC
 * (bits [31:26]): SVC(0x18)->8, 0x1d->0xd, IABT(0x20)->fault reason 5,
 * DABT(0x24)->fault reason 1/3, SMC-ish(0x3f)->0x80000000/7/8/1 by ISS,
 * default->checks the guest pstate for a host abort (bit3) and panics
 * "Unexpected host abort from guest context", or (EC>0x34 / unmapped)
 * panics "Unrecognized guest trap exception, state=%p, esr=%#llx @%s:%d".
 * Counter globals at per-CPU tpidr+0x8d8 (DABT) / +0x8e0 (IABT) are bumped.
 * Confidence: high (two hv_vcpu.c panic strings + ESR-EC dispatch)
 * Notes: 0x4008 exit word == es+0x4008 read by the hv_vcpu_run hub (b989a44).
 *   UnkSytemRegRead(3,0,1,0,0) is afsr1_el1 for the SMC/0x3f ISS==0x20 case.
 *   The exit-code values (8,0xd,5,1,3,7,0x80000000,10) are exit enumerations
 *   used by hv_vcpu_run's dispatch, not ESR values.
 */
void hv_el2_guest_esr_classify(void *state, uint64_t esr, uint64_t far)
{
    uint32_t ec = (uint32_t)((esr >> HV_EL2_EC_SHIFT) & HV_EL2_EC_MASK);
    uint64_t iss, afsr;
    uint32_t exit;
    uint32_t *st32 = state;

    if (hv_trace_flag & 1) {
        /* kernel_trace(0x1030801 | (ec<<2), esr, far, pc, 0) — enter trace */
        uint64_t pc = (st32[0] == 0x14) ? (uint32_t)st32[0x11]
                                        : *(uint64_t *)(state + 0x210);
        kernel_trace((ec << 2) | 0x1030801, esr, far, pc, 0);
    }
    st32[0x100a] = 0;
    st32[0x100b] = 0;
    *(uint64_t *)(state + 0x1004 * 4 + 0) = esr & 0xffffffff;   /* +0x4010 */
    st32[0x1006] = 0;
    st32[0x1007] = 0;

    /* If EC is one of the "handled by this classifier" classes, set a flag. */
    uint64_t handled = 0;
    if (ec <= 0x34 && ((1ULL << ec) & 0x10001100000000ULL) != 0) {
        handled = far;   /* param_3 propagated; see below */
    }
    *(uint64_t *)(state + 0x1008 * 4) = handled;   /* +0x4020 */

    if (ec < 0x20) {
        if (ec == 0x18) {                 /* SVC */
            iss = esr & 0x1ffffff;
            *(uint64_t *)(state + 0x1006 * 4) = iss;   /* +0x4018 */
            exit = 8;
            st32[0x1002] = exit;          /* +0x4008 */
        } else if (ec == 0x1d) {
            st32[0x1002] = 0xd;           /* +0x4008 */
        } else {
            /* default: check host-abort bit of the guest pstate */
            size_t pst = (st32[0] == 0x14) ? 0x48 : 0x110;
            uint32_t p = *(uint32_t *)(state + pst);
            if ((p & 0x8) != 0) {
                kernel_panic_msg();       /* "Unexpected host abort ..." */
            }
            if ((p & 0x100000) != 0) {
                st32[0x1002] = 10;        /* +0x4008 */
            }
        }
    } else if (ec == 0x20) {              /* IABT */
        /* tpidr_el1 per-CPU: bump tpidr+0x8e0 instruction-abort counter */
        uint64_t *pcpu = (uint64_t *)tpidr_el1;
        *(uint64_t *)(*(uint64_t *)(pcpu + 0x1b8) + 0x8e0) += 1;
        hv_el2_guest_fault(state, esr, far, 5, (uint32_t)(esr & 0x3f));
    } else if (ec == 0x3f) {              /* SMC-ish */
        if ((esr & 0x1ffffff) == 3) {
            iss = esr & 0x1ffffff;
            if (iss < 0x22) {
                if (iss == 3) {
                    st32[0x1002] = (uint32_t)-0x80000000;
                } else if (iss == 0x20) {
                    afsr = UnkSytemRegRead(3,0,1,0,0) & 0xffffffff; /* afsr1_el1 */
                    *(uint64_t *)(state + 0x1006 * 4) = afsr;       /* +0x4018 */
                    st32[0x1002] = 8;
                } else if (iss == 0x21) {
                    st32[0x1002] = 7;
                } else {
                    kernel_panic_assert();  /* "Unrecognized guest trap ..." */
                }
            } else {
                if ((iss - 0x22 > 1) && (iss != 0x26)) {
                    kernel_panic_assert();
                }
                st32[0x1002] = 1;
            }
        }
        if ((esr & 0x1fffff0) == 0x20) {
            iss = esr & 0x1ffffff;
            if (iss < 0x22) {
                if (iss == 3) {
                    st32[0x1002] = (uint32_t)-0x80000000;
                } else if (iss == 0x20) {
                    afsr = UnkSytemRegRead(3,0,1,0,0) & 0xffffffff;
                    *(uint64_t *)(state + 0x1006 * 4) = afsr;
                    exit = 8;
                    st32[0x1002] = exit;
                } else if (iss == 0x21) {
                    st32[0x1002] = 7;
                } else {
                    kernel_panic_assert();
                }
            } else {
                if ((iss - 0x22 > 1) && (iss != 0x26)) {
                    kernel_panic_assert();
                }
                st32[0x1002] = 1;
            }
        }
    } else if (ec == 0x24) {              /* DABT */
        uint64_t *pcpu = (uint64_t *)tpidr_el1;
        *(uint64_t *)(*(uint64_t *)(pcpu + 0x1b8) + 0x8d8) += 1;
        uint32_t r;
        if (((esr >> 6) & 1) == 0 ||
            (((esr >> 8) & 1) != 0 && (esr & 0x3f) - 0x10 >= 0xfffffffd)) {
            r = 1;
        } else {
            r = 3;
        }
        hv_el2_guest_fault(state, esr, far, r, (uint32_t)(esr & 0x3f));
    } else {
        /* default: host-abort check (same as ec<0x20 default) */
        size_t pst = (st32[0] == 0x14) ? 0x48 : 0x110;
        uint32_t p = *(uint32_t *)(state + pst);
        if ((p & 0x8) != 0) {
            kernel_panic_msg();
        }
        if ((p & 0x100000) != 0) {
            st32[0x1002] = 10;
        }
    }

    if (hv_trace_flag & 1) {
        uint64_t pc = (st32[0] == 0x14) ? (uint32_t)st32[0x11]
                                        : *(uint64_t *)(state + 0x210);
        kernel_trace(((ec << 2) | 0x1030801) + 1, esr, far, pc, 0);
    }
}

/*
 * FUN_fffffe000b967768 @ 0xfffffe000b967768   (est. hv_el2_guest_fault)
 * Ghidra: void FUN_fffffe000b967768(long param_1, ulong param_2, ulong param_3,
 *                                    uint param_4, undefined4 param_5)
 * Handles a guest data/instruction abort from the ESR classifier. param_1 =
 * guest-state block, param_2 = ESR, param_3 = FAR, param_4 = sub-reason
 * (0x18 -> SVC, 0xd..0xf -> "within guest", 0x20 -> IABT, 0x24 -> DABT),
 * param_5 = which (read/write). For SVC (param_4==0x18) it forwards to
 * FUN_fffffe000b98f304. For aborts it resolves the guest physical address:
 * when inside the guest and the EA bit is clear, the FAR is used directly;
 * otherwise the IPA is synthesised from HPFAR_EL2 (guest IPA = FAR[11:0] |
 * (HPFAR[31:4]<<12)). Then validates/maps it via the EL2 guest page-table
 * (FUN_fffffe000b94b450 / b89988c) with the vm_fault path; on a
 * not-EL2-mapped-but-in-guest-IPA-range failure it retries via
 * FUN_fffffe000b9879b8. Writes the fault exit code to state+0x4008.
 * Confidence: medium (fault-table + HPFAR synthesis observed)
 * Notes: UnkSytemRegRead(3,5,1,0,0) is HPFAR_EL2. vm_fault strings
 *   "vm_fault() KERN_FAILURE from guest fault on state %p @%s:%d" and the
 *   kernel wrappers b94b450/b89988c/b9879b8 are shared kernel, stubbed.
 */
void hv_el2_guest_fault(void *state, uint64_t esr, uint64_t far,
                        uint32_t reason, uint32_t which)
{
    uint32_t r;
    uint64_t ipa, hpfar;

    if (reason > 0x1f) {
        return;
    }
    uint32_t mask = 1u << (reason & 0x1f);

    if ((mask & 0xeef0) == 0) {
        if ((mask & 0xe2000000) == 0) {
            if (reason != 0x18) {
                return;
            }
            /* reason 0x18: guest SError/async — forward to the hardware
             * error handler (PL2/LLC multi-hit reporting). Kernel, stubbed. */
            FUN_fffffe000b98f304(state, far, 1, esr);
        }
    } else {
        /* abort path */
        uint64_t *pcpu = (uint64_t *)tpidr_el1;
        void *vm = *(void **)(*(uint64_t *)(pcpu + 0x4d8) + 0x88);
        if ((((esr >> 7) & 1) == 0) && (reason - 0xd < 3)) {
            /* EA clear, inside guest: use FAR directly */
            if (UnkSytemRegRead(3,5,1,0,0) & 1) {   /* bit0 of HPFAR_EL2 */
                far = FUN_fffffe000c0d993c(*(uint64_t *)(*(uint64_t *)(*(uint64_t *)(*(uint64_t *)(pcpu+0x4d8)+0x88)+0x58)+8), far);
            }
            *(uint64_t *)(state + 0x4028) = far;
            if (far == 0xffffffffffffffffULL) goto done;
        } else {
            hpfar = UnkSytemRegRead(3,5,1,0,0);        /* HPFAR_EL2 */
            ipa = (far & 0xfff) | ((hpfar >> 4) & 0xfffffffff) << 12;
            *(uint64_t *)(state + 0x4028) = ipa;
        }
        FUN_fffffe000b968948(1);   /* disable debug exceptions (kernel) */
        if ((esr & 0x80) != 0) {
            which = 1;
        }
        /* validate + vm_fault the IPA in the guest vm */
        if ((((reason & 0x3c) == 4) ||
             (far < *(uint64_t *)(*(uint64_t *)(vm + 0x58) + 0x10)) ||
             (*(uint64_t *)(*(uint64_t *)(vm + 0x58) + 0x18) <= far)) ||
            FUN_fffffe000b94b450((uint64_t)(vm + 0x58), far, which, reason == 0xb) != 0) {
            if ((far < *(uint64_t *)(vm + 0x28)) ||
                (*(uint64_t *)(vm + 0x30) <= far)) {
                r = 6;
            } else {
                uint64_t faultarg[5] = {2,0,0,0,0};
                int i = FUN_fffffe000b89988c((uint64_t)vm, far, which, 0, 0, 0, 0,
                                             faultarg, 0);
                if (i != 0) {
                    if (((reason & 0x3c) != 4) ||
                        FUN_fffffe000b9879b8((uint64_t)vm, far, esr, state) == 0) {
                        if (i == 5) {
                            kernel_panic_assert();
                        }
                        if (i == 0xe) {
                            r = 9;
                        } else {
                            r = 6;
                        }
                    } else {
                        /* retried fault resolved: advance guest PC */
                        *(uint64_t *)(state + 0x108) += 4;
                        r = 5;
                    }
                } else {
                    r = 5;
                }
            }
        } else {
            r = 5;
        }
    }
done:
    r = 5;
    *(uint32_t *)(state + 0x4008) = r;
}

/* ---- guest IRQ / FIQ handlers ---------------------------------------- */

/*
 * FUN_fffffe000b967004 @ 0xfffffe000b967004   (est. hv_el2_guest_irq)
 * Ghidra: void FUN_fffffe000b967004(undefined8 param_1)
 * Handles a guest IRQ: acknowledges the interrupt controller (IMPDEF via
 * UnkSytemRegRead(3,5,0xf,1,1)/Write), reads timer/pending state, feeds the
 * interrupt dispatcher (FUN_fffffe000b966dd8), optionally fires a deferred
 * interrupt handler (DAT_fffffe000c68aee0), then updates per-CPU clock
 * accounting (CNTVCT read at UnkSytemRegRead(3,4,0xf,0xb,7)). Shared kernel
 * irq machinery; reconstructed here for the guest-exit audit.
 * Confidence: medium
 */
void hv_el2_guest_irq(void)
{
    /* Full reconstruction in the decompiled body; summarized. The core is:
     *  - UnkSytemRegRead(3,5,0xf,1,1) pending check -> FUN_fffffe000b966dd8
     *  - timer interrupt handling via FUN_fffffe000b95f388 / b97ad74
     *  - CNTVCT_EL2 (3,4,0xf,0xb,7) clock-accounting update */
    (void)0;
}

/*
 * FUN_fffffe000b966c74 @ 0xfffffe000b966c74   (est. hv_el2_guest_fiq)
 * Ghidra: void FUN_fffffe000b966c74(undefined8 param_1)
 * Handles a guest FIQ: calls FUN_fffffe000b966dd8(param_1,3) (irq
 * acknowledgment), then the interrupt-controller dispatch vtable
 * (**(code **)(*DAT_fffffe000c733fc0 + 0x940))(), updates the per-CPU FIQ
 * counter and clock accounting (CNTVCT_EL2 read).
 * Confidence: medium
 */
void hv_el2_guest_fiq(void)
{
    (void)0;
}

/* ---- return to guest -------------------------------------------------- */

/*
 * FUN_fffffe000b75e468 @ 0xfffffe000b75e468   (est. hv_el2_return_to_guest)
 * Ghidra: undefined8 FUN_fffffe000b75e468(uint param_1)
 * Restores the guest's EL1 state from the saved frame (x21 base) and erets
 * back to the guest. On entry param_1 bit7 (0x80) selects the fast path
 * (FUN_fffffe000b75e5cc); otherwise it re-checks the preemption count
 * (tpidr+0x1c0) and the "saved thread state with interrupts enabled" guard,
 * then restores elr_el1/spsr_el1/fpsr/fpcr, reloads SVE Z/P registers when
 * the guest SVE state is active (type 0x31 at tpidr+0x120), re-arms the
 * PAC key (UnkSytemRegWrite(3,0,1,0,5)) and T1SZ
 * (UnkSytemRegWrite(3,0,1,0,6,0x10001)), and executes ExceptionReturn().
 * FUN_fffffe000b75e5cc is the same tail without the preemption re-check.
 * Confidence: high (SVE restore + ExceptionReturn observed)
 * Notes: "Signed thread state manipulated with interrupts enabled" guard is
 *   in FUN_fffffe000b760444 (JOP-hash verify of the saved state); this is
 *   the "no-register-loss on exit" path the security audit keys on.
 */
void hv_el2_return_to_guest(void *state)
{
    /* Restore elr_el1/spsr_el1/fpcr/fpsr + SVE regs from the frame, then
     * eret. See FUN_fffffe000b75e468/b75e5cc decompiles in notes; the
     * register-restore sequence is the inverse of the vector-entry save
     * (HV_EL2_FRAME_* offsets in hv_el2.h). */
    (void)state;
}

/* ---- EL2 vector entry handlers --------------------------------------- */

/*
 * The four EL2 vector handlers (FUN_fffffe000b760b94 sync, FUN_fffffe000b760f04
 * irq, FUN_fffffe000b761260 fiq, FUN_fffffe000b7615bc error) are nearly
 * identical assembly sequences: they save SP_EL0/SP_EL1, MDSCR_EL1, tpidr_el1/
 * el0/ro, PAR_EL1, CSSELR_EL1, the EL2 feature/sysreg capture, the guest GPRs
 * (x2..x30), the FP/SVE registers (conditional on CPTR_EL2 bit 20/24), then
 * elr_el1/spsr_el1/far_el1/esr_el1, switch to the per-CPU EL2 stack (tpidr_el2),
 * restore the hypervisor's EL2 control regs (cptr_el2, s3_3_c13_0_5,
 * s3_0_c1_2_4, s3_4_c15_12_0, s3_6_c15_0_4/5, mdscr_el1, tpidr_el1/el0/ro),
 * compute and verify the PAC "JOP hash" of the saved sysregs (panic
 * "Sysreg JOP hash mismatch detected (guest state corruption)"), then branch
 * to the common dispatch FUN_fffffe000b761930 with a per-type return address:
 *
 *   handler          exit reason   EL1 kernel handler (return target)
 *   b760b10 (sync)   1             adrp 0xed8 target (in b75df48/5e04c region)
 *   b760f04 (irq)    3             b75df48 (EL1 kernel handler region)
 *   b761260 (fiq)    4             b75dfcc (EL1 kernel handler region)
 *   b7615bc (error)  2             b75e04c (EL1 kernel handler region)
 *
 * NOTE: the exit-reason -> return-target pairing above is taken from the
 * decompiler output (FUN_fffffe000b760f04 passes 0xfffffe000b75df48,
 * FUN_fffffe000b761260 passes &LAB_fffffe000b75dfcc, FUN_fffffe000b7615bc
 * passes &LAB_fffffe000b75e04c). The sync handler (b760b10) computes its
 * target via adrp+0xed8; the exact EL1 label it lands on is unverified but
 * lies in the b75df48..b75e04c EL1 exception-handler window.
 *
 * FUN_fffffe000b761930 zeroes the scratch GPRs (x2..x30), PAC-authenticates
 * x22 (return address) with the SP and continues — effectively ereting down
 * to the EL1 kernel exception handler that runs the actual dispatch, because
 * the hypervisor re-uses the EL1 kernel's exception vectors (VBAR_EL1 at
 * 0xfffffe000b75c000) to process the guest exit in kernel context.
 *
 * These are recreated as documentation-level stubs here because the bodies
 * are pure register-save/restore assembly (hundreds of instructions with no
 * C control flow); the faithful register-offset map is in hv_el2.h
 * (HV_EL2_FRAME_*). Status: decompiled as structural notes; confidence low
 * for the exact return-target addresses (adrp+add resolved from disassembly).
 */

void hv_el2_vector_sync(void)
{
    /* Save guest state, reason=HV_EL2_EXIT_REASON_SYNC, branch to dispatch. */
    (void)0;
}

void hv_el2_vector_irq(void)
{
    (void)0;
}

void hv_el2_vector_fiq(void)
{
    (void)0;
}

void hv_el2_vector_error(void)
{
    (void)0;
}

void hv_el2_common_dispatch(void)
{
    (void)0;
}
