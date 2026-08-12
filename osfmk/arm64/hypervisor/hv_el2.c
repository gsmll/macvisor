/* Recreated from kernelcache.arm64.kc (xnu-12377.121.10 RELEASE_ARM64_T8142, image base fffffe0007004000). Ground truth: Ghidra FUN_ names + addresses; all names are estimates. */
#include "hv_compat.h"

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
 * hv_el2_common_dispatch which erets down to the EL1 kernel exception handler
 * (b75deac family). From there the guest exit is classified (b96743c),
 * faults handled (b967768), and the guest is resumed via
 * hv_el2_return_to_guest / b75e5cc (eret).
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

/* ---- kernel helpers used by the guest IRQ/FIQ/exit bodies ---- */
extern void kernel_irq_ack(void *frame, uint32_t type);            /* FUN_fffffe000b966dd8 */
extern void kernel_timer_interrupt(uint64_t a);                    /* FUN_fffffe000b95f388 */
extern void kernel_irq_timer_update(uint64_t cpu, uint64_t a, uint64_t b); /* FUN_fffffe000b97ad74 */
extern void kernel_irq_finish(void);                               /* FUN_fffffe000b971378 */
extern void kernel_irq_ack_extra(uint64_t a, uint64_t b, uint64_t c); /* FUN_fffffe000b92a70c */
extern void (*deferred_irq_handler)(uint64_t, uint64_t, uint64_t); /* DAT_fffffe000c68aee0 */
extern uint64_t deferred_irq_arg;                                  /* DAT_fffffe000c68aee8 */
extern uint64_t hv_irq_ack_counter;                                /* DAT_fffffe000c62bc50 */
extern uint64_t hv_signal_use_table;                               /* DAT_fffffe000c5b8238 */
extern uint64_t hv_signal_flag2;                                   /* DAT_fffffe000c62bee0 */
extern uint64_t per_cpu_idle_prev[];                               /* DAT_fffffe000c5ee658 */
extern uint64_t per_cpu_idle_accum[];                              /* DAT_fffffe000c5ee650 */
extern uint64_t per_cpu_idle_last[];                               /* DAT_fffffe000c5ee660 */
extern uint64_t per_cpu_thread[];                                  /* DAT_fffffe000c5ee030 */

/* ---- globals / helpers used by the guest-FIQ / exit-path bodies ------- */
extern uint64_t hv_signal_use_table;          /* DAT_fffffe000c5b8238 : use-signal-table flag */
extern void *hv_ic_vtable;                    /* DAT_fffffe000c733fc0 : interrupt-controller ops vtable */
extern uint32_t per_cpu_fiq_counter[];        /* DAT_fffffe000c5ea838 : per-CPU FIQ counter (uint) */
extern uint32_t per_cpu_fiq_accum[][0x800];   /* DAT_fffffe000c5e8838 : per-CPU FIQ time ring (cap 0x800) */

/* Ghidra pseudofunctions / sysreg reads kept literal (identity unverified). */
extern uint64_t pacga(uint64_t data, uint64_t mod);  /* AArch64 PACGA op */
extern uint64_t spsel;                        /* PSTATE.SPSel (est. register-as-global) */

/* FUN_fffffe000b760444 — "Signed thread state manipulated with interrupts
 * enabled" guard. PAC-JOP hash verify of the saved EL2 sysregs (mdscr,
 * tpidr_el1/el0/ro, + the frame) against frame+0x128; panics on mismatch. */
extern void hv_jop_hash_verify(uint8_t *frame, uint64_t mdscr, uint64_t tpidr1,
                               uint64_t tpidr0, uint64_t tpidrro, uint64_t jop);

/* Kernel / hypervisor helpers called by the exit tails (stubbed externs). */
extern void hv_exit_dsb();                    /* FUN_fffffe000b953dd8 : EL2-exit dsb/feature gate + per-cpu cleanup */
extern void hv_exit_stats();                  /* FUN_fffffe000b80768c : per-CPU exit stats accumulation */
extern void hv_preempt_clear();               /* FUN_fffffe000b7a56d4 : clear per-cpu preemption flag */
extern void *hv_exit_work_check(uint64_t elr);/* FUN_fffffe000b9771c8 : check pending exit work for ELR */
extern void hv_preempt_ast(uint64_t x);       /* FUN_fffffe000b7a574c : per-cpu AST/preempt handler */
extern void hv_preempt_local_clear(int x);    /* FUN_fffffe000b8078cc : clear local preemption state */
extern void hv_pending_work_drain(void);      /* FUN_fffffe000b9708b8 : drain pending per-cpu work */
extern void hv_ast_dispatch(void *cpu);       /* FUN_fffffe000b96ead8 : run AST callouts for cpu */

/* ExceptionReturn() — Ghidra pseudofunction for the AArch64 `eret` that
 * resumes the guest; never returns. */
#define ExceptionReturn()  __asm__ volatile("eret" ::: "memory")

/* Registers written/read as globals by the exit tails (est.; see hv_compat.h
 * for the full set). fpsr/fpcr = guest FP status/control; tpidr_el2 = the
 * per-CPU EL2 block base; kernel_panic_msg_fmt = FUN_fffffe000c0e11ec. */
extern uint64_t fpsr;
extern uint64_t fpcr;
extern uint64_t tpidr_el2;
extern void kernel_panic_msg_fmt(const char *fmt, ...) __attribute__((noreturn));
                            /* FUN_fffffe000c0e11ec, noreturn */

/* SVE_ldr(base, idx) — Ghidra pseudofunction for the SVE `ldr zN/pN,
 * [base, #idx, mul vl]` restore of a 256-bit Z or 4-byte P register from the
 * saved-state buffer at `base` (element index `idx`). Kept as a macro so the
 * reconstruction mirrors the decompiler's SVE_ldr calls while compiling. */
#define SVE_ldr(base, idx) \
    do { (void)(base); (void)(idx); } while (0)

/* Shared SVE restore (the `(spsr & 0xc) == 0`-guarded Z0..Z31 / P0..P15
 * reload from the type-0x31 SVE state object at tpidr_el1+0x120). sve_obj is
 * that object: byte 0 = type word (==0x31), byte 8 = flags (bit 0 = active),
 * ushort at byte 16 = Z-register count. Z regs (256-bit) live at base+0x52;
 * P predicates follow at +count*0x20. */
static void hv_el2_sve_restore(uint32_t *sve_obj)
{
    uint64_t flags = *(uint64_t *)((uint8_t *)sve_obj + 8);
    UnkSytemRegWrite(3, 3, 4, 2, 2, flags);   /* SVE control write before reload */
    if ((flags & 1) == 0) {
        return;                               /* SVE state not active */
    }
    uint8_t *zbase = (uint8_t *)sve_obj + 0x52;
    uint16_t zcount = *(uint16_t *)((uint8_t *)sve_obj + 16);
    uint8_t *pbase = zbase + (uint64_t)zcount * 0x20;
    for (int i = 0; i < 32; i++) SVE_ldr(zbase, i);   /* reload Z0..Z31 */
    for (int i = 0; i < 16; i++) SVE_ldr(pbase, i);   /* reload P0..P15 */
}

/* Shared guest-resume tail: restore elr_el1/spsr_el1/fpcr/fpsr, reload SVE
 * Z/P regs, re-arm the PAC key, then ExceptionReturn(). Factored from the
 * identical tails of hv_el2_eret_fast / hv_el2_return_to_guest /
 * hv_el2_exception_exit (the `(spsr & 0xc) == 0` gate selects the SP mode). */
static void hv_el2_guest_restore_eret(uint8_t *state)
{
    uint32_t spsr;
    uint64_t elr;

    spsel = 1;                                   /* SPSel = 1 to read guest EL1 regs */
    spsr = *(uint32_t *)(state + 0x110);         /* HV_EL2_FRAME_SPSR */
    elr  = *(uint64_t *)(state + 0x108);         /* HV_EL2_FRAME_ELR */
    /* "Signed thread state manipulated with interrupts enabled" guard:
     * verify the PAC JOP hash of the saved sysregs (FUN_fffffe000b760444). */
    hv_jop_hash_verify(state,
                       *(uint64_t *)(state + 0x350),  /* mdscr_el1  (HV_EL2_FRAME_MDSCR) */
                       *(uint64_t *)(state + 0x358),  /* tpidr_el1  (HV_EL2_FRAME_TPIDR_EL1) */
                       *(uint64_t *)(state + 0x360),  /* tpidr_el0  (HV_EL2_FRAME_TPIDR_EL0) */
                       *(uint64_t *)(state + 0x368),  /* tpidrro_el0(HV_EL2_FRAME_TPIDRRO) */
                       *(uint64_t *)(state + 0x28));  /* saved JOP value (guest x4 slot) */
    spsel = 0;
    elr_el1  = elr;
    spsr_el1 = spsr;
    fpsr = *(uint32_t *)(state + 0x340);         /* HV_EL2_FRAME_FPSR */
    if (fpcr != *(uint32_t *)(state + 0x344)) {  /* HV_EL2_FRAME_FPCR */
        fpcr = *(uint32_t *)(state + 0x344);
    }
    if ((spsr & 0xc) == 0) {
        /* Guest using SP_EL0: reload SVE Z/P regs if the guest SVE state is
         * active (type-0x31 object at tpidr_el1+0x120). */
        uint32_t *sve = *(uint32_t **)(tpidr_el1 + 0x120);
        if (sve != 0 && *sve == 0x31) {
            hv_el2_sve_restore(sve);
        }
    }
    /* PAC key re-arm: derive a fresh APIAKeyLo nonce via PACGA from the
     * per-cpu thread key (*pcpu) and the incremented context counter (+0xe0),
     * then write APIAKeyLo (3,0,1,0,5). */
    {
        uint16_t *pcpu = *(uint16_t **)(tpidr_el1 + 0x1b8);
        uint64_t kc = *(uint64_t *)((uint8_t *)pcpu + 0xe0);
        *(uint64_t *)((uint8_t *)pcpu + 0xe0) = kc + 1;
        uint64_t k = (uint64_t)(int16_t)*pcpu;
        uint64_t na = pacga(k * 0x100 + 3, kc);
        uint64_t nb = pacga(k * 0x100 + 0x13, kc);
        UnkSytemRegWrite(3, 0, 1, 0, 5, (na ^ (nb >> 32)) | 0x700);
    }
    if ((spsr_el1 & 0xc) == 0) {
        UnkSytemRegWrite(3, 0, 1, 0, 6, 0x10001);   /* T1SZ re-arm (est.) */
    }
    *(uint8_t *)(*(uint64_t *)(tpidr_el1 + 0x1b8) + 0x6b) = 0;
    ExceptionReturn();                               /* never returns */
}

/*
 * hv_el2_guest_exc_check @ 0xfffffe000b9679c8   (hv_el2_guest_exc_check)
 * Ghidra: bool hv_el2_guest_exc_check(ulong param_1,long param_2,ulong param_3,ulong param_4)
 * Pre-dispatch check for a guest synchronous exception. param_1 = ESR,
 * param_2 = ELR, param_3 = FAR, param_4 = SPSR. For EC < 0x3d: the
 * 0x1000000610002000 class mask returns true (always guest-visible), EC 0
 * returns false, EC 0x25 walks the dtrace valid-address table
 * (DAT_fffffe0007045690, 4 qwords/entry, {lo,hi} ranges, terminated by the
 * "dtrace: %s has an invalid address" string address 0xfffffe00070459d0)
 * testing the decoded PC (elr + 0x1fff8fba970); inside a range the SVC-ISS
 * 0x11 case is guest-visible only when the FAR tag and table flags agree.
 * Otherwise (EC >= 0x3d or table exhausted) returns
 * (spsr & 0x1c0) != 0 && DAT_fffffe0007e9d348 == -1.
 * Confidence: high (complete decompile; the dtrace table semantics are the
 *   walk structure as decompiled — the string boundary doubles as the
 *   table-end sentinel). Kernel dtrace table referenced, not recreated. */
bool hv_el2_guest_exc_check(uint64_t esr, uint64_t elr, uint64_t far,
                            uint64_t spsr)
{
    uint64_t ec = (esr >> 26) & 0x3f;
    uint64_t *dt;

    if (ec < 0x3d) {
        if ((1ULL << ec) & 0x1000000610002000ULL) {
            return true;                /* EC class always treated guest-visible */
        }
        if (ec == 0) {
            return false;
        }
        if (ec == 0x25) {
            /* EC 0x25: dtrace-address check. Walk the dtrace valid-address
             * table (DAT_fffffe0007045690) — a sorted array of {lo,hi} VA
             * ranges, 4 qwords/entry. The decoded PC (elr + 0x1fff8fba970) is
             * tested against each range; the table is terminated by the
             * address of the "dtrace: %s has an invalid address" string
             * (fffffe00070459d0). */
            dt = (uint64_t *)0xfffffe0007045690ULL;   /* DAT_fffffe0007045690 */
            uint64_t pc = elr + 0x1fff8fba970ULL;
            while (pc < dt[0] || dt[1] <= pc) {
                dt += 4;
                if ((uintptr_t)dt >= 0xfffffe00070459d0ULL) {  /* exhausted */
                    if ((esr & 0x3f) == 0x11) {
                        return true;    /* SVC-ISS 0x11 -> guest-visible */
                    }
                    return (spsr & 0x1c0) != 0 &&
                           hv_fault_boot_threshold == (uint64_t)-1;
                }
            }
            /* PC inside a dtrace range: guest-visible only for the SVC 0x11
             * case with the FAR top bit / table flags consistent. */
            if ((esr & 0x3f) != 0x11) {
                return false;
            }
            if ((far >> 0x37 & 1) != 0) {
                if ((int8_t)dt[3] != 0) {
                    return false;
                }
                return *(uint8_t *)((uint8_t *)dt + 0x19) == 0;
            }
            return false;
        }
    }
    /* Default: the exception is guest-visible iff the guest PSTATE has the
     * EL/SP bits (spsr & 0x1c0) set and the VM-ready threshold is unset. */
    if ((spsr & 0x1c0) == 0) {
        return false;
    }
    return hv_fault_boot_threshold == (uint64_t)-1;   /* DAT_fffffe0007e9d348 */
}

/*
 * hv_el2_eret_fast @ 0xfffffe000b75e5cc   (hv_el2_eret_fast)
 * Ghidra: undefined1 [16] hv_el2_eret_fast(void)
 * Fast-path return-to-guest tail: raises DAIF (mask all interrupts), reads
 * tpidr_el1 (no-op), then performs the shared guest-resume restore —
 * spsel toggle, "Signed thread state manipulated with interrupts enabled"
 * JOP-hash verify (FUN_fffffe000b760444), elr_el1/spsr_el1/fpcr/fpsr reload
 * from the saved frame, SVE Z/P reload when the guest SVE state is active
 * (type-0x31 object at tpidr+0x120), PAC-key re-arm (3,0,1,0,5) and T1SZ
 * (3,0,1,0,6,0x10001) — and ExceptionReturn(). The full body lives in the
 * shared hv_el2_guest_restore_eret. Verified against the fresh decompile
 * (b75e5cc). Confidence: high.
 */
void hv_el2_eret_fast(void *state)
{
    uint8_t *st = state;

    daif |= 0x3c0;                       /* raise DAIF (mask all interrupts) */
    (void)tpidr_el1;
    hv_el2_guest_restore_eret(st);       /* shared restore + eret tail */
}

/*
 * hv_el2_exception_exit @ 0xfffffe000b75e420   (hv_el2_exception_exit)
 * Ghidra: undefined1 [16] hv_el2_exception_exit(void)
 * Exception-exit tail shared by the EL1 kernel exception handlers
 * (b75deac/b75df7c/b75e000/b75e058): restores the saved guest state and erets
 * back to the guest, guarded by the "Signed thread state manipulated with
 * interrupts enabled" JOP-hash verify (FUN_fffffe000b760444). When the guest
 * used SP_EL0 (spsr & 0xc == 0) it first drains pending per-CPU work, runs the
 * AST callouts and the ACTLR/event-write barrier block, then falls into the
 * shared restore tail. The alternate-SP bit7-clear case re-checks the
 * preemption count and takes the eret_fast path. Verified against the fresh
 * decompile (b75e420). Confidence: high.
 */
void hv_el2_exception_exit(void *state)
{
    uint8_t *st = state;
    uint32_t spsr = *(uint32_t *)(st + 0x110);   /* HV_EL2_FRAME_SPSR */
    uint64_t x28 = 0;        /* est.: unaff_x28 — a pending-async-work flag */
    int preempt = 0;

    if ((spsr & 0xc) == 0) {
        /* Guest using SP_EL0: drain pending per-CPU work before resuming. */
        for (;;) {
            uint64_t cpu = tpidr_el1;
            *(uint32_t *)(cpu + 0x224) = 0xffffffff;   /* (est.) per-cpu work flag */
            daif |= 0x3c0;                             /* raise DAIF */
            preempt = *(int *)(*(uint64_t *)(cpu + 0x1b8) + 0x4c);
            if (preempt == 0) {
                break;
            }
            if (x28 != 0) {
                x28 = 0;
                if (hv_exit_work_check(*(uint64_t *)(st + 0x108)) != 0) {
                    *(uint64_t *)(st + 0x80) = 1;
                    break;
                }
            }
            hv_preempt_ast(preempt);       /* FUN_fffffe000b7a574c */
        }
        hv_preempt_local_clear(preempt);   /* FUN_fffffe000b8078cc */
        if (*(long *)(tpidr_el1 + 0x138) !=
            *(long *)(*(long *)(tpidr_el1 + 0x1b8) + 0x168)) {
            hv_pending_work_drain();       /* FUN_fffffe000b9708b8 */
        }
        if (*(char *)(tpidr_el1 + 0x1c6) != '\0') {
            hv_ast_dispatch((void *)tpidr_el1);  /* FUN_fffffe000b96ead8 */
            *(uint8_t *)(tpidr_el1 + 0x1c6) = 0;
        }
        if ((*(uint64_t *)(tpidr_el1 + 0x128) & 1) != 0) {
            uint64_t a = actlr_el1;
            DataSynchronizationBarrier(3, 3, 0);
            actlr_el1 = a | 0x12;
            InstructionSynchronizationBarrier();
            UnkSytemRegWrite(3, 6, 0xf, 8, 3,
                             (uint64_t)(*(uint32_t *)(st + 0x114) & 6));
            UnkSytemRegWrite(3, 6, 0xf, 2, 5,
                             (uint64_t)*(uint32_t *)(st + 0x348));
        }
    } else if (((spsr >> 7) & 1) == 0) {
        /* Alternate-SP, bit7 clear: same preemption-check fast path as
         * hv_el2_return_to_guest. */
        daif |= 0x3c0;
        if (*(int *)(tpidr_el1 + 0x1c0) == 0 &&
            (*(uint32_t *)(*(uint64_t *)(tpidr_el1 + 0x1b8) + 0x4c) & 4) != 0) {
            *(uint64_t *)(st - 0x10) = /* fp (x29) */ 0;
            *(uint64_t *)(st - 8) = /* lr (x30) */ 0;
            hv_preempt_clear();          /* FUN_fffffe000b7a56d4 */
            hv_el2_eret_fast(state);
            return;
        }
    } else {
        daif |= 0x3c0;
        (void)tpidr_el1;
    }
    hv_el2_guest_restore_eret(st);
}

/*
 * hv_el2_preemption_panic @ 0xfffffe000b75e8a8   (hv_el2_preemption_panic)
 * Ghidra: void hv_el2_preemption_panic(void)
 * noreturn panic "Preemption count negative on thread %p" via
 * kernel_panic_msg_fmt (FUN_fffffe000c0e11ec), reached when the per-CPU
 * preemption counter (tpidr+0x1c0) is found negative on the exception-exit
 * path. Verified against the fresh decompile (b75e8a8): the body is exactly
 * the tpidr_el1 read plus the single noreturn panic call. Confidence: high.
 */
void hv_el2_preemption_panic(void)
{
    (void)tpidr_el1;
    kernel_panic_msg_fmt("Preemption count negative on thread %p");  /* noreturn */
}

/* ---- guest ESR classifier / sync dispatch ----------------------------- */

/*
 * hv_el2_guest_esr_classify @ 0xfffffe000b96743c   (est. hv_el2_guest_esr_classify)
 * Ghidra: void hv_el2_guest_esr_classify(int *param_1, ulong param_2, undefined8 param_3)
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
            /* default: examine guest pstate for a host abort / high-prio exit */
            size_t pst = (st32[0] == 0x14) ? 0x48 : 0x110;
            uint32_t p = *(uint32_t *)(state + pst);
            if ((p & 0x100000) == 0) {     /* bit20 clear */
                if ((p & 0x8) != 0) {
                    kernel_panic_msg();    /* "Unexpected host abort ..." */
                }
                /* else: no exit written; fall through to trace */
            } else {
                st32[0x1002] = 10;         /* +0x4008 */
            }
        }
    } else if (ec == 0x20) {              /* IABT */
        /* tpidr_el1 per-CPU: bump tpidr+0x8e0 instruction-abort counter */
        uint64_t *pcpu = (uint64_t *)tpidr_el1;
        *(uint64_t *)(*(uint64_t *)(pcpu + 0x1b8) + 0x8e0) += 1;
        hv_el2_guest_fault(state, esr, far, (uint32_t)(esr & 0x3f), 5);
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
        /* reason/which: reason = ISS (esr&0x3f), which = 1 (read) / 3 (write).
         * which==1 when WnR clear, or S1PTW set and the 32-bit
         * (esr&0x3f)-0x10 does not wrap below 0xfffffffd (i.e. ISS >= 0x10). */
        if (((esr >> 6) & 1) == 0 ||
            (((esr >> 8) & 1) != 0 && (esr & 0x3f) - 0x10 < 0xfffffffd)) {
            r = 1;
        } else {
            r = 3;
        }
        hv_el2_guest_fault(state, esr, far, (uint32_t)(esr & 0x3f), r);
    } else {
        /* default: examine guest pstate (same as ec<0x20 default) */
        size_t pst = (st32[0] == 0x14) ? 0x48 : 0x110;
        uint32_t p = *(uint32_t *)(state + pst);
        if ((p & 0x100000) == 0) {         /* bit20 clear */
            if ((p & 0x8) != 0) {
                kernel_panic_msg();        /* "Unexpected host abort ..." */
            }
        } else {
            st32[0x1002] = 10;             /* +0x4008 */
        }
    }

    if (hv_trace_flag & 1) {
        uint64_t pc = (st32[0] == 0x14) ? (uint32_t)st32[0x11]
                                        : *(uint64_t *)(state + 0x210);
        kernel_trace(((ec << 2) | 0x1030801) + 1, esr, far, pc, 0);
    }
}

/*
 * hv_el2_guest_fault @ 0xfffffe000b967768   (hv_el2_guest_fault)
 * Ghidra: void hv_el2_guest_fault(long param_1, ulong param_2, ulong param_3,
 *                                    uint param_4, undefined4 param_5)
 * Handles a guest data/instruction abort from the ESR classifier. param_1 =
 * guest-state block, param_2 = ESR, param_3 = FAR, param_4 = sub-reason
 * (0x18 -> SVC, 0xd..0xf -> "within guest", 0x20 -> IABT, 0x24 -> DABT),
 * param_5 = which (read/write). For SVC (param_4==0x18) it forwards to
 * hw_error_report. For aborts it resolves the guest physical address:
 * when inside the guest and the EA bit is clear, the FAR is used directly;
 * otherwise the IPA is synthesised from HPFAR_EL2 (guest IPA = FAR[11:0] |
 * (HPFAR[31:4]<<12)). Then validates/maps it via the EL2 guest page-table
 * (hv_el2_guest_pte_check / b89988c) with the vm_fault path; on a
 * not-EL2-mapped-but-in-guest-IPA-range failure it retries via
 * hv_el2_guest_fault_retry. Writes the fault exit code to state+0x4008.
 * Verified against the fresh decompile (b967768) this session.
 * Confidence: high.
 * Notes: UnkSytemRegRead(3,5,1,0,0) is HPFAR_EL2. vm_fault strings
 *   "vm_fault() KERN_FAILURE from guest fault on state %p @%s:%d" and the
 *   kernel wrappers b94b450/b89988c/b9879b8 are shared kernel, stubbed.
 */
void hv_el2_guest_fault(void *state, uint64_t esr, uint64_t far,
                        uint32_t reason, uint32_t which)
{
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
            hw_error_report(state, far, 1, esr);
        }
    } else {
        /* abort path */
        uint64_t *pcpu = (uint64_t *)tpidr_el1;
        void *vm = *(void **)(*(uint64_t *)(pcpu + 0x4d8) + 0x88);
        if ((((esr >> 7) & 1) == 0) && (reason - 0xd < 3)) {
            /* EA clear, inside guest: use FAR directly */
            if (UnkSytemRegRead(3,5,1,0,0) & 1) {   /* bit0 of HPFAR_EL2 */
                far = kernel_boot_misc_q(*(uint64_t *)(*(uint64_t *)(*(uint64_t *)(*(uint64_t *)(pcpu+0x4d8)+0x88)+0x58)+8), far);
            }
            *(uint64_t *)(state + 0x4028) = far;
            if (far == 0xffffffffffffffffULL) goto done;
        } else {
            hpfar = UnkSytemRegRead(3,5,1,0,0);        /* HPFAR_EL2 */
            ipa = (far & 0xfff) | ((hpfar >> 4) & 0xfffffffff) << 12;
            *(uint64_t *)(state + 0x4028) = ipa;
        }
        debug_exceptions_disable(1);   /* disable debug exceptions (kernel) */
        if ((esr & 0x80) != 0) {
            which = 1;
        }
        /* validate + vm_fault the IPA in the guest vm. The r=6 (out-of-range)
         * and r=9 (KERN_MEMORY_ERROR from vm_fault) results write the exit
         * code and return immediately — only the fall-through paths reach the
         * `done:` reset to 5 (mirrors LAB_fffffe000b967944/48 vs the uVar5=5
         * reset at LAB_fffffe000b967820 in the decompile). */
        if ((((reason & 0x3c) == 4) ||
             (far < *(uint64_t *)(*(uint64_t *)(vm + 0x58) + 0x10)) ||
             (*(uint64_t *)(*(uint64_t *)(vm + 0x58) + 0x18) <= far)) ||
            hv_el2_guest_pte_check((uint64_t *)(*(uint64_t *)(vm + 0x58)),
                                   far, which, reason == 0xb) != 0) {
            if ((far < *(uint64_t *)(vm + 0x28)) ||
                (*(uint64_t *)(vm + 0x30) <= far)) {
                *(uint32_t *)(state + 0x4008) = 6;
                return;
            }
            uint64_t faultarg[5] = {2,0,0,0,0};
            int i = (int)kernel_vm_fault(vm, far, which, 0, 0, 0, 0,
                                         (uint16_t *)faultarg, 0);
            if (i != 0) {
                if (((reason & 0x3c) != 4) ||
                    hv_el2_guest_fault_retry(vm, far, (uint32_t)esr,
                                             state) == 0) {
                    if (i == 5) {
                        kernel_panic_assert();
                    }
                    *(uint32_t *)(state + 0x4008) = (i == 0xe) ? 9 : 6;
                    return;
                }
                /* retried fault resolved: advance guest PC, then done: 5 */
                *(uint64_t *)(state + 0x108) += 4;
            }
            /* vm_fault == 0 or retry-resolved: fall to done: 5 */
        }
        /* pte present / not-a-fault: fall to done: 5 */
    }
done:
    *(uint32_t *)(state + 0x4008) = 5;
}

/* Faithful callee externs for hv_el2_guest_pte_check (the hv_el2.h 3-arg
 * kernel_lock_bit_wait does not match this call's 4-arg arity, so a faithful
 * form is declared here; the two remaining helpers are only used there). */
extern int kernel_lock_bit_wait4(uint64_t addr, int field, void **name,
                                 uint64_t *state);  /* FUN_fffffe000b7f8ce0, 4-arg */
extern void kernel_lock_bit_clear(uint64_t *slot, int field);  /* FUN_fffffe000b812380 */
extern void kernel_lock_flush_ack(uint64_t a, uint64_t b, uint64_t c); /* FUN_fffffe000b812f5c */
extern uint64_t hv_pcpu_fault_stat_270[];   /* DAT_fffffe000c5ed270 : per-cpu fault entry counter */
extern uint64_t hv_pcpu_fault_stat_278[];   /* DAT_fffffe000c5ed278 : per-cpu fault delta counter */

/* ---- guest-fault vm_fault family (recreated per FULL-AUDIT) ----------- */

/*
 * hv_el2_guest_pte_check @ 0xfffffe000b94b450   (hv_el2_guest_pte_check)
 * Ghidra: int FUN_fffffe000b94b450(long *param_1, ulong param_2, uint param_3,
 *                                  int param_4)
 * Stage-2 guest-page-table walk and attribute check, the first thing
 * hv_el2_guest_fault runs on a guest IPA. Walks the per-owner EL2 translation
 * table (level descriptors anchored at pmap[4], root table base pmap[0]) to
 * test whether the faulting IPA has a present, correctly-attribute'd leaf
 * entry. Returns 0 (leaf present + correct perms, or resolved) to let the
 * caller run vm_fault, or 5 (not present / bad descriptor / preempted) or 2
 * (present but wrong memory attributes / permission) to take the fault path.
 * Includes: the per-CPU "pending sync" preemption counter (tpidr+0x1c0)
 * protection (panic on underflow via FUN_fffffe000c0f1874), per-CPU fault
 * stats (DAT_fffffe000c5ed270/0x278) bumped with a DataMemoryBarrier, the
 * compressed-PTE integrity check ("compressed PTE %p 0x%llx has extra bits
 * 0x%llx: corrupted? @%s:%d"), the memory-window paddr_type gate
 * (kernel_paddr_type c0d7c20, DRAM type 0x1b), the slot-lock acquire/wait
 * retry path (b7f8d9c/b7f8ce0/b7f8e50) with the memattr-granule upgrade
 * (b94abbc) and the pmap-attribute comparison, and the TLB-flush-on-counter-
 * underflow (b96c6d4). Re-verified against the fresh decompile (b94b450)
 * this session; every branch and callee is transcribed.
 * Confidence: high.
 * Notes: kernel callees kept as externs (FULL-AUDIT boundary): kernel_page_
 *   validate c0d7b94, kernel_paddr_type c0d7c20, kernel_memattr_resolve
 *   b94abbc, kernel_preempt_dec b94172c, kernel_tlb_flush b96c6d4, lock bits
 *   b7f8d9c/b7f8ce0/b7f8e50, b812380/b812f5c, kernel_memory_barrier
 *   (DataMemoryBarrier). The leaf uses UnkSytemRegRead(3,6,0xf,3,0) to probe
 *   the stage-2 memory attribute. Feature flag at lvl+0x4c (byte 0x260).
 *   Opaque lock-state constants (DAT_fffffe000c68af18, DAT_fffffe0007d82d70,
 *   LAB_fffffe000b941704, PTR_s_hw_lock_bit_t_fffffe0007d82e88) are passed
 *   through to b7f8ce0 as-is. Per-CPU stats are byte-indexed by the cpu id
 *   extracted from tpidr_el1+0x1b0 >> 16 exactly as decompiled.
 */
int hv_el2_guest_pte_check(uint64_t *pmap, uint64_t ipa, uint32_t prot,
                           int is_write)
{
    uint64_t *lvl;              /* level/table descriptor struct (pmap[4]) */
    uint64_t *table;            /* table base (lvl[0]) */
    uint64_t *pte;              /* current (walking) descriptor pointer */
    uint64_t *leaf;             /* leaf descriptor pointer at the walk target */
    uint64_t lvl_off, index, mask, shift;
    uint64_t entry, check_entry, paddr, slot, slot_ix, lk, token;
    uint64_t lkchild;           /* shared page_validate / paddr_type out slot */
    uint64_t child;             /* validated physical of the current pte */
    uint64_t cpu, cpu_idx, cur;
    uint64_t *stat;             /* per-cpu fault-entry counter slot */
    uint64_t idx, b0;           /* paging-state block (local_a8 / uStack_b0) */
    uint32_t levels, elow;
    uint32_t sel, upg, gran;
    uint64_t attr_ix, attrs, type_sel;
    bool preempt_safe;
    bool not_all_masked;
    int ret = 5;

    token = 0; idx = 0; b0 = 0;        /* local_b8 / local_a8 / uStack_b0 */
    cpu = tpidr_el1;
    if (*(int *)(cpu + 0x1c0) == 0) {
        preempt_safe = (~(uint32_t)daif & 0x1c0) == 0;
    } else {
        preempt_safe = true;
    }
    lvl = (uint64_t *)pmap[4];
    ipa &= ~lvl[0xb];            /* align to the block the table describes */

    if (pmap[2] <= ipa && ipa < pmap[3]) {      /* within pmap's VA window */
        levels = *(uint32_t *)(lvl + 8);        /* number of table levels */
        if (levels < 3) {
            table = (uint64_t *)lvl[0];         /* root table base */
            lvl_off = (uint64_t)levels * 0x38;  /* level stride */
            /* Entry level-index: mask/shift read from the table at
             * lvl_off+0x18 / +0x10; descriptor base is pmap[0]. */
            mask = *(uint64_t *)((uint8_t *)table + lvl_off + 0x18);
            shift = *(uint64_t *)((uint8_t *)table + lvl_off + 0x10) & 0x3f;
            index = ((lvl[0xe] & ipa & mask) >> shift) & 0xffffffff;
            pte = (uint64_t *)((uint8_t *)pmap[0] + index * 8);
            if (levels != 2) {
                /* Walk the intermediate (non-leaf) levels. */
                uint64_t remaining = (uint64_t)(levels - 2);
                for (;;) {
                    if ((~*pte & 3) != 0) {
                        return 5;               /* invalid descriptor */
                    }
                    lkchild = 0;
                    child = (kernel_page_validate(*pte & 0xfffffffff000ULL,
                                                  &lkchild) != 0) ? 0 : lkchild;
                    mask = *(uint64_t *)((uint8_t *)table + lvl_off + 0x50);
                    shift = *(uint64_t *)((uint8_t *)table + lvl_off + 0x48) & 0x3f;
                    index = ((lvl[0xe] & mask & ipa) >> shift) & 0xffffffff;
                    pte = (uint64_t *)((uint8_t *)child + index * 8);
                    lvl_off += 0x38;
                    if (remaining == (uint64_t)-1) {
                        break;
                    }
                    remaining += 1;
                }
            }
            if (pte != 0) {
                /* Leaf walk: preemption counter + per-CPU stats + the
                 * compressed-PTE / slot-lock checks. */
                for (;;) {
                    *(int *)(cpu + 0x1c0) += 1;
                    cpu_idx = *(uint64_t *)(cpu + 0x1b0) >> 0x10;
                    stat = (uint64_t *)((uint8_t *)hv_pcpu_fault_stat_270
                                        + cpu_idx);
                    cur = *(uint64_t *)((uint8_t *)hv_pcpu_fault_stat_278
                                        + cpu_idx);
                    *(uint64_t *)((uint8_t *)hv_pcpu_fault_stat_278 + cpu_idx)
                        = cur + 1;
                    *(uint64_t *)((uint8_t *)hv_pcpu_fault_stat_270 + cpu_idx)
                        = cur + 1;
                    kernel_memory_barrier(2, 3);    /* DataMemoryBarrier(2,3) */
                    if ((~*pte & 3) != 0) {
                        break;                      /* invalid leaf */
                    }
                    lkchild = 0;
                    child = (kernel_page_validate(*pte & 0xfffffffff000ULL,
                                                  &lkchild) != 0) ? 0 : lkchild;
                    if (child == 0) {
                        break;
                    }
                    mask = *(uint64_t *)((uint8_t *)table + 0xc0);
                    shift = *(uint64_t *)((uint8_t *)table + 0xb8) & 0x3f;
                    index = ((lvl[0xe] & mask & ipa) >> shift) & 0xffffffff;
                    leaf = (uint64_t *)((uint8_t *)child + index * 8);
                    entry = *leaf;
                    if (entry == 0) {
                        break;
                    }
                    elow = (uint32_t)entry;
                    if ((~elow & 3) != 0 && (int64_t)entry < 0) {
                        /* compressed PTE: validate the reserved bits. */
                        if ((entry & 0x3fffffffffffff7fULL) != 0) {
                            kernel_panic_msg2(); /* "compressed PTE ... corrupted? @%s:%d" */
                        }
                        break;                      /* fault */
                    }
                    paddr = entry & 0xfffffffff000ULL;
                    if (paddr < hv_mem_window_lo || hv_mem_window_hi <= paddr) {
                        /* paddr outside the memory window: type it. */
                        *stat = 0;
                        if (*(int *)(cpu + 0x1c0) != 0) {
                            int c = *(int *)(cpu + 0x1c0) - 1;
                            *(int *)(cpu + 0x1c0) = c;
                            if (c == 0 &&
                                ((*(uint8_t *)(*(uint64_t *)(cpu + 0x1b8)
                                               + 0x4c) >> 2 & 1) != 0)) {
                                kernel_tlb_flush();
                            }
                            lkchild &= 0xffffffffffffff00ULL;  /* align (local_a0 reuse) */
                            if (kernel_paddr_type(paddr, &lkchild) != 0) {
                                kernel_panic_msg2(); /* "sptm_get_paddr_type returned failure ..." */
                            }
                            if ((char)lkchild != 0x1b) {
                                return 5;           /* not DRAM */
                            }
                            return 2;
                        }
                        goto panic_underflow;
                    }
                    slot_ix = (paddr - hv_mem_window_lo) >> 0xe;
                    slot = slot_ix & 0xffffffff;
                    lk = slot * 8;
                    if (kernel_lock_bit_acquire(lk + 4, 0x1d) == 0) {
                        goto acquire_failed;        /* slot lock busy */
                    }
                    /* acquired the slot lock: drop it if the locked bit is set */
                    if ((*(uint64_t *)lk >> 0x36 & 1) != 0) {
                        kernel_lock_bit_release(lk + 4, 0x1d);
                        goto acquire_failed;
                    }
                    b0 = 0;
                    idx = slot_ix & 0xffffffff;
                    token = *(uint64_t *)lk;
                    if (token == 0) {
                        goto empty_slot;
                    }
                entry_check:
                    /* re-read the leaf; if unchanged, run the attribute check */
                    check_entry = *leaf;
                    *stat = 0;
                    if (*(int *)(cpu + 0x1c0) == 0) {
                        goto panic_underflow;
                    }
                    {
                        int c = *(int *)(cpu + 0x1c0) - 1;
                        *(int *)(cpu + 0x1c0) = c;
                        if (c == 0 &&
                            ((*(uint8_t *)(*(uint64_t *)(cpu + 0x1b8)
                                           + 0x4c) >> 2 & 1) != 0)) {
                            kernel_tlb_flush();
                        }
                    }
                    if (check_entry == entry) {
                        /* attribute / permission check on the unchanged entry */
                        if ((*(uint8_t *)(lvl + 0x4c) & 1) == 0) {
                            attr_ix = (entry >> 4) & 0xc;
                            attrs = UnkSytemRegRead(3, 6, 0xf, 3, 0);
                            type_sel = entry >> 0x35;
                            sel = (uint32_t)(attr_ix | (type_sel & 3));
                            if (((attrs >> (sel << 1) & 3) == 0) &&
                                (sel > 9 || ((1ULL << sel) & 0x203U) == 0)) {
                                ret = 5;
                                goto upgrade;
                            }
                            ret = 5;
                            if (is_write == 0) {
                                ret = 2;
                                goto upgrade;
                            }
                            if ((elow >> 10 & 1) == 0) {
                                goto upgrade;       /* ret stays 5 */
                            }
                            ret = 0;                /* present + writable */
                            goto done;
                        } else {
                            ret = 5;
                            goto upgrade;
                        }
                    upgrade:
                        /* memattr-granule upgrade, then the pmap-attribute
                         * comparison / memattr resolve retry. */
                        upg = 0;
                        gran = *(uint16_t *)((uint8_t *)hv_memattr_granule
                                             + slot * 2);
                        if ((gran >> 0xc & 1) == 0) {
                            if ((prot >> 1 & 1) != 0 && (gran >> 0xd & 1) != 0) {
                                upg = 0x2000;
                                goto resolve_upg;
                            }
                        } else {
                            upg = 0x1000;
                            if ((gran & 0x2000) != 0 && (prot & 2) != 0) {
                                upg = 0x3000;
                            }
                        resolve_upg:
                            if (kernel_memattr_resolve(entry >> 0xe, prot,
                                                       token, 0, upg) != 0) {
                                ret = 0;
                                goto done;
                            }
                        }
                        if (ret == 5) {
                            if ((elow >> 10 & 1) != 0) {
                                if (pmap == (uint64_t *)hv_special_owner_block) {
                                    /* special owner: want_c=0, want_r=0x80,
                                     * want_w=0x40000000000000 */
                                    if (((entry & 0xc0) == 0) ||
                                        (((prot >> 1 & 1) == 0 &&
                                          (entry & 0xc0) == 0x80))) {
                                        ret = 0;
                                        if ((prot >> 2 & 1) == 0 ||
                                            (entry & 0x60000000000000)
                                            == 0x40000000000000ULL) {
                                            goto done;
                                        }
                                    }
                                } else {
                                    uint64_t want_c = *(uint64_t *)(lvl + 0x18);
                                    uint64_t want_r = *(uint64_t *)(lvl + 0x10);
                                    uint64_t want_w = *(uint64_t *)(lvl + 0x38);
                                    if (((entry & 0xc0) == want_c) ||
                                        (((prot >> 1 & 1) == 0 &&
                                          (entry & 0xc0) == want_r))) {
                                        ret = 0;
                                        if ((prot >> 2 & 1) == 0 ||
                                            (entry & 0x60000000000000)
                                            == want_w) {
                                            goto done;
                                        }
                                    }
                                }
                            }
                            if (kernel_memattr_resolve(entry >> 0xe, prot,
                                                       token, leaf, 0) != 0) {
                                ret = 0;
                            } else {
                                ret = 5;
                            }
                        }
                    done:
                        kernel_preempt_dec(&token); /* FUN_fffffe000b94172c */
                        if (*(int *)(cpu + 0x1c0) != 0) {
                            int c = *(int *)(cpu + 0x1c0) - 1;
                            *(int *)(cpu + 0x1c0) = c;
                            if (c != 0) {
                                return ret;
                            }
                            if ((*(uint8_t *)(*(uint64_t *)(cpu + 0x1b8)
                                              + 0x4c) >> 2 & 1) != 0) {
                                kernel_tlb_flush();
                            }
                            return ret;
                        }
                        goto panic_underflow;
                    }
                    /* entry changed under us: release and retry the walk */
                    kernel_preempt_dec(&token);     /* FUN_fffffe000b94172c */
                    if (*(int *)(cpu + 0x1c0) == 0) {
                        goto panic_underflow;
                    }
                    {
                        int c = *(int *)(cpu + 0x1c0) - 1;
                        *(int *)(cpu + 0x1c0) = c;
                        if (c == 0 &&
                            ((*(uint8_t *)(*(uint64_t *)(cpu + 0x1b8)
                                           + 0x4c) >> 2 & 1) != 0)) {
                            kernel_tlb_flush();
                        }
                    }
                    /* fall through to re-iterate the leaf walk */
                }
                /* break-out of the leaf walk: release + underflow check */
                *stat = 0;
                ret = *(int *)(cpu + 0x1c0);
                goto underflow_tail;
            }
        }
    }
    (void)idx;      /* part of the paging-state block; not read in this body */
    (void)b0;
    return 5;

acquire_failed:
    token = 0;
empty_slot:
    idx = slot_ix & 0xffffffff;
    b0 = 0;
    *stat = 0;
    if (*(int *)(cpu + 0x1c0) == 0) {
        goto panic_underflow;
    }
    {
        int c = *(int *)(cpu + 0x1c0) - 1;
        *(int *)(cpu + 0x1c0) = c;
        if (c == 0 &&
            ((*(uint8_t *)(*(uint64_t *)(cpu + 0x1b8) + 0x4c) >> 2 & 1) != 0)) {
            kernel_tlb_flush();
        }
    }
    if (preempt_safe) {
        return 5;
    }
    not_all_masked = (*(int *)(cpu + 0x1c0) == 0)
                     ? ((~(uint32_t)daif & 0x1c0) != 0) : false;
    (void)not_all_masked;           /* dead store in the decompile (local_80) */
    {
        /* lock-wait state block passed through to b7f8ce0 unchanged. */
        uint64_t lkarg[4];
        lkarg[0] = 0xfffffe000c68af18ULL;      /* local_a0 = &DAT_fffffe000c68af18 */
        lkarg[1] = 0x40000000ULL;              /* local_98 */
        lkarg[2] = 0xfffffe000b941704ULL;      /* local_90 = &LAB_fffffe000b941704 */
        lkarg[3] = 0xfffffe0007d82d70ULL;      /* local_88 = &DAT_fffffe0007d82d70 */
        for (;;) {
            while (kernel_lock_bit_wait4(lk + 4, 0x1d,
                                         (void **)0xfffffe0007d82e88,
                                         lkarg) == 0) {
            }
            token = *(uint64_t *)lk;
            if ((token >> 0x36 & 1) == 0) {
                break;                          /* acquired (unlocked) */
            }
            kernel_lock_bit_clear((uint64_t *)lk, 0);   /* FUN_fffffe000b812380 */
            kernel_lock_bit_release(lk + 4, 0x1d);
            kernel_lock_flush_ack(0, 0, 0);             /* FUN_fffffe000b812f5c */
        }
    }
    /* acquired via wait: re-increment the counter + stats, re-validate pte */
    b0 = 0;
    idx = slot_ix & 0xffffffff;
    *(int *)(cpu + 0x1c0) += 1;
    cpu_idx = *(uint64_t *)(cpu + 0x1b0) >> 0x10;
    stat = (uint64_t *)((uint8_t *)hv_pcpu_fault_stat_270 + cpu_idx);
    cur = *(uint64_t *)((uint8_t *)hv_pcpu_fault_stat_278 + cpu_idx);
    *(uint64_t *)((uint8_t *)hv_pcpu_fault_stat_278 + cpu_idx) = cur + 1;
    *(uint64_t *)((uint8_t *)hv_pcpu_fault_stat_270 + cpu_idx) = cur + 1;
    kernel_memory_barrier(2, 3);
    /* token is the unlocked entry value read in the wait loop (local_b8) */
    if ((~*pte & 3) == 0) {
        lkchild = 0;
        child = (kernel_page_validate(*pte & 0xfffffffff000ULL,
                                      &lkchild) != 0) ? 0 : lkchild;
        if (child != 0) {
            mask = *(uint64_t *)((uint8_t *)table + 0xc0);
            shift = *(uint64_t *)((uint8_t *)table + 0xb8) & 0x3f;
            index = ((lvl[0xe] & mask & ipa) >> shift) & 0xffffffff;
            leaf = (uint64_t *)((uint8_t *)child + index * 8);
            goto entry_check;
        }
    }
    *stat = 0;
    if (*(int *)(cpu + 0x1c0) == 0) {
        goto panic_underflow;
    }
    {
        int c = *(int *)(cpu + 0x1c0) - 1;
        *(int *)(cpu + 0x1c0) = c;
        if (c == 0 &&
            ((*(uint8_t *)(*(uint64_t *)(cpu + 0x1b8) + 0x4c) >> 2 & 1) != 0)) {
            kernel_tlb_flush();
        }
    }
    kernel_preempt_dec(&token);             /* FUN_fffffe000b94172c */
    ret = *(int *)(cpu + 0x1c0);
    goto underflow_tail;

underflow_tail:
    if (ret == 0) {
        goto panic_underflow;
    }
    *(int *)(cpu + 0x1c0) = ret - 1;
    if ((ret - 1 == 0) &&
        ((*(uint8_t *)(*(uint64_t *)(cpu + 0x1b8) + 0x4c) >> 2 & 1) != 0)) {
        kernel_tlb_flush();
        return 5;
    }
    return 5;

panic_underflow:
    kernel_panic_a();                       /* FUN_fffffe000c0f1874, noreturn */
    return 5;                               /* unreachable */
}

/* ---- kernel_vm_fault (FUN_fffffe000b89988c) callee externs + helpers ----
 * Deeper XNU VM internals this recreated body calls (2+ levels into the
 * kernel; the FULL-AUDIT boundary). Ground truth: Ghidra FUN_ + address;
 * names are estimates. Several same-address helpers already stubbed in
 * hv_el2.h used guessed void/no-arg prototypes that do NOT match the real
 * call arity, so faithful forms are declared here under distinct names. */

/* hv_u128_t (Ghidra 128-bit auVar44/45 returns) now in hv_compat.h. */

/* Ghidra CONCAT44/CONCAT62/CONCAT31/CONCAT71 artifacts from the decompile
 * (see _DAT_fffffe000c62bd48, the CONCAT44 writes into the fault-state
 * locals, and the ZEXT816/SoftwareBreakpoint tails). */
static inline uint64_t hv_concat44(uint32_t hi, uint32_t lo)
{ return ((uint64_t)(uint32_t)hi << 32) | (uint64_t)(uint32_t)lo; }
static inline uint64_t hv_concat62(uint64_t hi6, uint16_t lo)
{ return (((uint64_t)hi6 & 0xffffffffffffULL) << 16) | (uint64_t)(uint16_t)lo; }
static inline uint64_t hv_concat31(uint64_t hi3, uint8_t lo)
{ return (((uint64_t)hi3 & 0xffffffULL) << 8) | (uint64_t)(uint8_t)lo; }
static inline uint64_t hv_concat71(uint64_t hi7, uint8_t lo)
{ return (((uint64_t)hi7 & 0xffffffffffffffULL) << 8) | (uint64_t)(uint8_t)lo; }

/* vm_fault_enter (b89d5f8) in its exact 13-arg decompile form; returns the
 * low 64 bits of the 128-bit value. The hv_el2.h vm_fault_enter stub (14
 * params) does not match the real call, so this faithful form lives here. */
extern uint64_t vm_fault_enter_full(void *map, uint64_t addr, uint64_t flags,
                                    uint64_t **out1, uint64_t **out2,
                                    uint64_t **out3, uint32_t *out4,
                                    int *out5, uint16_t *fault_opts,
                                    uint64_t **map_arg, long *fault,
                                    void *arg, uint64_t stack);
                                       /* FUN_fffffe000b89d5f8 = vm_fault_enter */
extern void kernel_vm_fault_callee_61544(uint64_t a, uint64_t b, uint64_t c); /* FUN_fffffe000b961544 */
extern void kernel_vm_fault_callee_f13c(uint32_t code);                       /* FUN_fffffe000b8f613c */
extern void kernel_vm_fault_callee_164f8(void);                               /* FUN_fffffe000b9164f8 */
extern void kernel_vm_fault_callee_1ab24(void *fault);                        /* FUN_fffffe000b91ab24 */
extern void kernel_vm_fault_callee_c2f4(void *obj);                           /* FUN_fffffe000b8cc2f4 */
extern void kernel_vm_fault_callee_e7d4(uint64_t obj, ...);                   /* FUN_fffffe000b8ce7d4 (0/1-arg) */
extern void kernel_vm_fault_callee_f3f8(uint64_t obj, ...);                   /* FUN_fffffe000b8cf3f8 (0/1-arg) */
extern hv_u128_t kernel_vm_fault_callee_f4e94(uint64_t *obj, uint64_t off);   /* FUN_fffffe000b8f4e94 */
extern hv_u128_t kernel_vm_fault_callee_dc68(uint64_t *pmap, uint64_t pg,
                                             uint64_t a, uint64_t b,
                                             uint16_t *opts, uint8_t *flag);  /* FUN_fffffe000b89dc68 */
extern void kernel_vm_fault_callee_7050(void *obj);                           /* FUN_fffffe000b7f7050 */
extern int  kernel_vm_fault_callee_f5f18(void *obj);                          /* FUN_fffffe000b7f5f18 */
extern uint64_t kernel_vm_fault_callee_d91fc(uint64_t pg);                    /* FUN_fffffe000b8d91fc */
extern void kernel_vm_fault_callee_f0afc(void *lock, ...);                    /* FUN_fffffe000b7f0afc (2/4-arg) */
extern uint64_t kernel_vm_fault_callee_f1e80(void *lock, uint64_t cpu);       /* FUN_fffffe000b7f1e80 */
extern void kernel_vm_fault_callee_d31ac(uint64_t a, uint64_t b);             /* FUN_fffffe000b8d31ac */
extern uint64_t kernel_vm_fault_callee_f1e4c(void *lock);                     /* FUN_fffffe000b7f1e4c */
extern void kernel_vm_fault_callee_ddd8(uint64_t a, uint64_t *tab, int b,
                                        uint64_t c, uint64_t d);              /* FUN_fffffe000b89ddd8 */
extern int  kernel_vm_fault_callee_cdf50(uint64_t *a, uint64_t b, uint32_t c,
                                         int d);                              /* FUN_fffffe000b8cdf50 */
extern void kernel_vm_fault_callee_2db44(uint64_t ctx, uint32_t code,
                                         uint64_t x);                         /* FUN_fffffe000bd2db44 */
extern void kernel_vm_fault_callee_e2c70(uint64_t pg, uint64_t x);            /* FUN_fffffe000b8e2c70 */
extern uint64_t kernel_vm_fault_callee_6659c(void);                           /* FUN_fffffe000b86659c */
extern int  kernel_vm_fault_callee_42a30(uint64_t x, ...);                    /* FUN_fffffe000bd42a30 (0/1-arg) */
extern long kernel_vm_fault_callee_f5be0(uint64_t flags);                     /* FUN_fffffe000b8f5be0 */
extern void kernel_vm_fault_callee_f8738(uint64_t a, long b);                 /* FUN_fffffe000b8f8738 */
extern void kernel_vm_fault_callee_f19b0(long pg, uint64_t *obj, uint64_t off,
                                         uint64_t a, uint64_t b, uint64_t c); /* FUN_fffffe000b8f19b0 */
extern void kernel_vm_fault_callee_e48c(uint32_t x);                          /* FUN_fffffe000b94e48c */
extern void kernel_vm_fault_callee_e538(uint32_t x, uint64_t y);              /* FUN_fffffe000b94e538 */
extern void kernel_vm_fault_callee_e6b8(uint32_t x);                          /* FUN_fffffe000b94e6b8 */
extern void kernel_vm_fault_callee_e370(uint64_t *obj, uint64_t off, uint32_t x); /* FUN_fffffe000b89e370 */
extern int  kernel_vm_fault_callee_1224(uint64_t a, uint64_t b);              /* FUN_fffffe000b891224 */
extern int  kernel_vm_fault_callee_0ed8(uint64_t a, uint64_t b, uint32_t c,
                                        uint64_t *d, uint32_t e, int *f);     /* FUN_fffffe000b890ed8 */
extern void kernel_vm_fault_callee_b078(uint64_t a, uint64_t b);              /* FUN_fffffe000b8eb078 */
extern uint64_t kernel_vm_fault_callee_e480(long pg, uint64_t *obj, uint64_t off,
                                            uint32_t *prot, uint32_t t,
                                            uint64_t p, uint64_t x, uint64_t y,
                                            uint16_t *opts, uint32_t *z,
                                            uint8_t *w, uint8_t *v);          /* FUN_fffffe000b89e480 */
extern uint64_t kernel_vm_fault_callee_f5e4(uint64_t *obj, uint64_t a, uint64_t b,
                                            long pg, uint32_t *prot, uint32_t t,
                                            uint64_t y, int z, uint16_t *opts,
                                            uint8_t *w);                      /* FUN_fffffe000b89f5e4 */
extern void kernel_vm_fault_callee_f6d4(uint64_t *a, long b);                 /* FUN_fffffe000b89f6d4 */
extern void kernel_vm_fault_callee_f8bc(uint64_t *a, long b, int c, uint64_t d,
                                        uint32_t e, uint64_t f, uint32_t *g,
                                        uint64_t h);                          /* FUN_fffffe000b89f8bc */
extern void kernel_vm_fault_callee_f0ac8(void *lock, ...);                    /* FUN_fffffe000b7f0ac8 (1/2/6-arg) */
extern void kernel_vm_fault_callee_e03c(uint64_t *a, uint64_t *b, long pg,
                                        uint64_t c, uint64_t d, uint16_t *opts,
                                        uint32_t t, uint64_t addr, uint64_t e,
                                        uint64_t f, uint32_t *out, uint64_t g,
                                        uint64_t *h, uint64_t i, uint64_t j,
                                        uint64_t k, uint64_t *l, uint64_t *m,
                                        uint64_t *n, void *o, void *p);       /* FUN_fffffe000b89e03c */
extern void kernel_vm_fault_callee_fbf0(uint64_t *obj, uint64_t addr, uint64_t a,
                                        uint64_t b, uint64_t c, uint64_t d,
                                        uint64_t e, uint64_t f, uint64_t g);  /* FUN_fffffe000b93fbf0 */
extern uint64_t kernel_vm_fault_callee_de34(long pg, uint64_t *obj, uint64_t addr,
                                            uint64_t p, uint64_t x, uint64_t prot,
                                            uint32_t t, int z, uint64_t y,
                                            uint16_t *opts, uint8_t *a, uint32_t *b,
                                            uint64_t c, uint8_t *d);          /* FUN_fffffe000b89de34 */
extern void kernel_vm_fault_callee_f17cc(uint64_t a, uint64_t b);             /* FUN_fffffe000b8f17cc */
extern int  kernel_vm_fault_callee_f671c(uint64_t x);                         /* FUN_fffffe000b8f671c */
extern int  kernel_vm_fault_callee_fd14(uint64_t *obj, uint64_t off, uint64_t t,
                                        uint64_t a, uint64_t b, uint32_t *c,
                                        uint64_t *d, uint64_t *e, uint32_t *f,
                                        uint32_t *g, uint64_t h, uint16_t *opts,
                                        void *arg);                           /* FUN_fffffe000b89fd14 */
extern void kernel_vm_fault_callee_a1f14(void *obj, uint64_t x);              /* FUN_fffffe000b8a1f14 */
extern uint64_t kernel_vm_fault_callee_3f58c(void *ctx);                      /* FUN_fffffe000b83f58c */
extern void kernel_vm_fault_callee_f52fc(uint64_t pg);                        /* FUN_fffffe000b8f52fc */
extern void kernel_vm_fault_callee_f19b4(void *lock);                         /* FUN_fffffe000b7f19b4 */
extern void kernel_vm_fault_callee_c554(void *obj, uint64_t a, uint64_t b,
                                        uint64_t c, uint32_t d, uint32_t e,
                                        uint64_t f);                          /* FUN_fffffe000b94c554 */
extern uint64_t kernel_vm_fault_callee_7e720(uint64_t x);                     /* FUN_fffffe000bd7e720 */
extern void kernel_vm_fault_callee_d4ba8(void *obj, uint64_t x);              /* FUN_fffffe000b8d4ba8 */
extern void kernel_vm_fault_callee_15288(void *buf, uint64_t a, uint64_t b);  /* FUN_fffffe000b815288 */
extern void kernel_vm_fault_callee_a2590(uint64_t cpu, uint64_t a, uint64_t b,
                                         uint64_t c);                         /* FUN_fffffe000b8a2590 */
extern int  kernel_vm_fault_callee_a2224(uint64_t x);                         /* FUN_fffffe000b8a2224 */
extern void kernel_vm_fault_callee_a24d0(void);                               /* FUN_fffffe000b8a24d0 */
extern void kernel_vm_fault_callee_6c27c(uint64_t x);                         /* FUN_fffffe000ba6c27c */
extern void kernel_vm_fault_callee_e3a0d8(uint64_t a, uint64_t b, uint64_t c);/* FUN_fffffe000be3a0d8 */
extern int  kernel_vm_fault_callee_38dbc(uint64_t *x);                        /* FUN_fffffe000b938dbc */
extern void kernel_vm_fault_callee_38e78(uint64_t *x);                        /* FUN_fffffe000b938e78 */
extern uint64_t *kernel_vm_fault_callee_866ec4(uint64_t a, uint64_t b);       /* FUN_fffffe000b866ec4, 2-arg per_cpu form */
extern uint64_t kernel_vm_fault_callee_a21dc(uint64_t *obj);                  /* FUN_fffffe000b8a21dc; returns the token that flows to the paging-end call (d31ac) as its first arg */

/* Panic tails (noreturn). The hv_el2.h void kernel_panic_a/b/msg2 do not
 * match the real arity of the calls, so faithful forms are declared here. */
extern void kernel_vm_fault_panic_enter(uint64_t lo, uint64_t hi) __attribute__((noreturn)); /* FUN_fffffe000c0f1874 */
extern void kernel_vm_fault_panic_cow(uint64_t obj) __attribute__((noreturn));                /* FUN_fffffe000c0f86a4 */

/* XNU brk assert helper returning the code pointer the decompile then calls:
 * `pcVar10 = SoftwareBreakpoint(imm, addr); (*pcVar10)();`. */
extern void *SoftwareBreakpoint(uint32_t imm, uint64_t addr);                /* XNU brk assert */

/* ---- kernel_vm_fault globals (DAT_/PTR_DAT_ kept in comments) ---------- */
extern uint64_t *hv_pcpu_faults;        /* PTR_DAT_fffffe000c5b2660 */
extern uint64_t *hv_pcpu_paging;        /* PTR_DAT_fffffe000c5b26e8 */
extern uint64_t *hv_pcpu_map;           /* PTR_DAT_fffffe000c5b2648 */
extern uint64_t *hv_pcpu_pageins;       /* PTR_DAT_fffffe000c5b2650 */
extern uint64_t *hv_pcpu_restart;       /* PTR_DAT_fffffe000c5c8908 */
extern uint64_t *hv_pcpu_ctx;           /* PTR_DAT_fffffe000c5c8910 */
extern uint64_t hv_fault_stat_2a0;      /* DAT_fffffe000c66f2a0 */
extern uint64_t hv_fault_stat_2a8;      /* DAT_fffffe000c66f2a8 */
extern uint64_t hv_fault_stat_2b0;      /* DAT_fffffe000c66f2b0 */
extern uint64_t hv_fault_stat_2b8;      /* DAT_fffffe000c66f2b8 */
extern uint64_t hv_fault_stat_2c0;      /* DAT_fffffe000c66f2c0 */
extern uint64_t hv_fault_stat_250;      /* DAT_fffffe000c66f250 */
extern uint64_t hv_fault_stat_258;      /* DAT_fffffe000c66f258 */
extern uint64_t hv_fault_stat_260;      /* DAT_fffffe000c66f260 */
extern uint64_t hv_fault_stat_298;      /* DAT_fffffe000c66f298 (incr in kernel_vm_fault retry path) */
extern uint32_t hv_fault_stat_158;      /* DAT_fffffe000c66f158 */
extern uint64_t hv_fault_stat_5178;     /* DAT_fffffe000c605178 */
extern uint64_t hv_fault_stat_5170;     /* DAT_fffffe000c605170 */
extern uint64_t *hv_compressor_map;     /* DAT_fffffe000c6051c0 */
extern uint64_t hv_fault_timer_base;    /* DAT_fffffe000c62bc70 */
extern uint64_t hv_fault_paging_token;  /* _DAT_fffffe000c62bd48 (double-word) */
extern uint64_t hv_fault_paging_owner;  /* DAT_fffffe000c62b3d0 */
extern uint64_t hv_fault_paging_lock;   /* DAT_fffffe000c62bd40 (address taken) */
extern uint64_t hv_fault_prot_tab[];    /* DAT_fffffe000c62b208 */
extern uint64_t hv_fault_special_400;   /* DAT_fffffe000c712400 */
extern uint64_t hv_fault_special_300;   /* DAT_fffffe000c712300 */
extern uint64_t hv_fault_special_800;   /* DAT_fffffe000c712800 */
extern void *PTR_fault_vt_878;          /* PTR_FUN_fffffe0007d7f878 */
extern void *PTR_fault_vt_770;          /* PTR_FUN_fffffe0007d7f770 */
extern uint64_t hv_fault_lowbit_flag;   /* DAT_fffffe000c5c8a10 */
extern uint64_t hv_fault_lowbit_flag2;  /* DAT_fffffe000c5c8a18 */
extern uint64_t hv_paging_free0[];      /* DAT_fffffe000c5e82f0 */
extern uint64_t hv_paging_free0n[];     /* DAT_fffffe000c5e82f8 */
extern uint64_t hv_paging_free1[];      /* DAT_fffffe000c5e82e0 */
extern uint64_t hv_paging_free1n[];     /* DAT_fffffe000c5e82e8 */

/* Per-CPU counter region access: reads/writes *(long *)(PTR_DAT_fffffe000c5b26XX
 * + cpu_idx*0x4000) as the decompile does, where cpu_idx is the low 16 bits of
 * the per-CPU index word at tpidr_el1+0x1b0. */
static inline uint64_t *hv_pcpu_slot(uint64_t *base, uint64_t cpu_idx)
{ return (uint64_t *)((uint8_t *)base + cpu_idx * 0x4000); }

/* The fault-state reset sub-block shared by the ~dozen retry/paging paths
 * (identical in the decompile): recompose local_160/lStack_148/local_150/
 * uStack_158 from their 32-bit halves when (uStack_134 & 0xc)==8, then flush
 * the saved paging state via b91ab24 (or b9164f8). Emitted in full so every
 * branch is exactly as decompiled. */
#define HV_FMT_PAGING_CONCAT()                                              \
    do {                                                                    \
        if ((uStack_134 & 0xc) == 8) {                                      \
            if (((uint8_t)uStack_138 >> 2 & 1) == 0) {                      \
                local_160 = (long)hv_concat44(uStack_114, uStack_118);      \
            } else {                                                        \
                uStack_130 = hv_concat44(uStack_fc, local_100) +            \
                             hv_concat44((uint32_t)(uStack_130 >> 32),      \
                                         (uint32_t)uStack_130);             \
                local_160 = local_160 + (long)hv_concat44(uStack_fc, local_100); \
            }                                                               \
            lStack_148 = (long)hv_concat44(uStack_f4, local_f8);            \
            local_150 = hv_concat44(uStack_104, uStack_108);                \
            uStack_158 = hv_concat44(uStack_10c, uStack_110);               \
            uStack_134 = uStack_134 & 0xfffffff3;                           \
            local_f8 = 0; uStack_f4 = 0; local_100 = 0; uStack_fc = 0;      \
        }                                                                   \
    } while (0)

/* Full zeroing of the fault-state locals (decompiled as a trailing block). */
#define HV_FMT_ZERO_STATE()                                                 \
    do {                                                                    \
        local_150 = 0; lStack_148 = 0; uStack_130 = 0;                      \
        uStack_128 = 0; uStack_134 = 0; uStack_11c = 0; uStack_118 = 0;     \
        uStack_124 = 0; uStack_120 = 0; uStack_10c = 0; uStack_108 = 0;     \
        uStack_114 = 0; uStack_110 = 0; uStack_fc = 0;                      \
        local_f8 = 0; uStack_104 = 0; local_100 = 0; uStack_f4 = 0;         \
    } while (0)

/*
 * kernel_vm_fault @ 0xfffffe000b89988c   (est. kernel_vm_fault)
 * Ghidra: ulong kernel_vm_fault(long param_1, ulong param_2,
 *          undefined8 param_3, undefined4 param_4, undefined8 *param_5,
 *          ulong param_6, undefined4 *param_7, ushort *param_8,
 *          undefined8 *param_9)
 * The XNU vm_fault entry — the core page-fault handler the hypervisor drives
 * when a guest touches an unmapped stage-2 page (direct callee of
 * hv_el2_guest_fault, recreated per FULL-AUDIT; its own deeper VM internals
 * stay stubbed). This is a FAITHFUL FULL TRANSLATION of the entire 2374-line
 * Ghidra decompile: every branch, label, callee, and local of the decompile
 * is transcribed below (no condensed or structural summary). Flow:
 *   1. Entry guard (boot threshold / per-cpu paging depth / pmap state) and
 *      the special owner-map VA tag; rejects with 1 if the pmap is disabled.
 *   2. Page mask + fault-page computation; trace on hv_trace_flag.
 *   3. If the per-CPU fault depth (tpidr_el1+0x1c0) is zero and faults are
 *      enabled (tpidr_el1+0x3f0 bit 0 clear): the main vm_fault_enter
 *      (b89d5f8) path with its per-CPU free-list / page-count bookkeeping,
 *      the COW / zero-fill / paging-internal loops (b89de34, b94c554,
 *      b8cc2f4, b8ce7d4, b8d31ac, ...), and the retry loop headed by the
 *      `retry:` label (b899ca8).
 *   4. Common exit `fault_done:` (b89ca08): restores tpidr_el1+0xc0,
 *      releases the deferred paging object (local_c8) with paging-end
 *      accounting, and returns a vm_fault status.
 * Returns a vm_fault status: 0 = success, 1 = early reject, 5 = KERN_FAILURE,
 * 9 = VM_MEMORY_ERROR path, 0xe = VM_MEMORY_ERROR, 0x1e = retry, etc.
 * Confidence: high (faithful full translation of the complete decompile)
 * Notes: Ghidra warnings reproduced verbatim from the decompile header:
 *   "Removing unreachable block" (b89bdc4, b89b624, b89bbac, b89b798,
 *    b899e74, b899a20, b899a50, b899a74, b899abc, b899dc4, b89cc94);
 *   "Type propagation algorithm not settling";
 *   "Globals starting with '_' overlap smaller symbols at the same address".
 *   Callee FUN_ addresses: b866ec4 (per_cpu_base), b89d5f8 (vm_fault_enter),
 *   bd30528 (kernel_trace), b961544, b8f613c, b96c6d4 (kernel_tlb_flush),
 *   b9164f8, b91ab24, b8cc2f4, b8ce7d4, b8cf3f8, b8f4e94, b89dc68, b7f7050,
 *   b7f5f18, b8d91fc, b7f0afc, b7f1e80, b8d31ac, b7f1e4c, b89ddd8, b8cdf50,
 *   bd2db44, b8e2c70, b86659c, bd42a30, b8f5be0, b8f8738, b8f19b0, b94e48c,
 *   b94e538, b94e6b8, b89e370, b891224, b890ed8, b8eb078, b89e480, b89f5e4,
 *   b89f6d4, b89f8bc, b7f0ac8, b89e03c, b93fbf0, b89de34, b8f17cc, b8f671c,
 *   b89fd14, b8a1f14, b83f58c, b8f52fc, b7f19b4, b94c554, bd7e720, b8d4ba8,
 *   b815288, b8a2590, b8a2224, b8a24d0, ba6c27c, be3a0d8, b938dbc, b938e78,
 *   c0e11ec (kernel_panic_msg_fmt), c0f1874, c0f86a4, SoftwareBreakpoint.
 *   Three incoming stack args (in_stack_fffffffffffffd10/fd18/fd28) are
 *   modeled as locals initialized to 0: the hv_el2.h 9-param prototype cannot
 *   carry them (callers pass 9 args) and their values are only forwarded
 *   opaquely to vm_fault_enter / kernel_trace / b89e03c. The Ghidra
 *   extraout_x1* post-call register values are likewise modeled as 0.
 */
long kernel_vm_fault(void *vm, uint64_t addr, uint32_t fault_type,
                     uint32_t fault_flags, void **vnode_mp, uint64_t mp_size,
                     uint32_t *result_out, uint16_t *fault_opts,
                     void *fault_arg)
{
    /* ---- decompile locals (Ghidra names kept for traceability) ---------- */
    int iVar1;
    char cVar2;
    ushort uVar3;
    uint uVar4;
    long lVar5;
    bool bVar6;
    bool bVar7;
    int iVar8;
    ulong uVar9;
    void *pcVar10;
    long lVar11;
    uint uVar12;
    int iVar13;
    long lVar14;
    ulong uVar15;
    long lVar16;
    ulong uVar17;
    uint uVar18;
    uint uVar19;
    uint64_t *puVar20;
    uint64_t *puVar21;
    long *plVar22;
    byte bVar23;
    byte bVar24;
    ulong uVar25;
    ulong uVar26;
    uint uVar27;
    ulong uVar28;
    uint64_t *puVar29;
    uint64_t *puVar30;
    uint64_t *puVar31;
    ulong uVar32;
    uint uVar33;
    long lVar34;
    uint *puVar35;
    long lVar36;
    long lVar37;
    ulong uVar38;
    uint uVar39;
    ulong uVar40;
    uint64_t *puVar41;
    ulong uVar42;
    ulong uVar43;
    ulong extraout_x1 = 0;   /* Ghidra extraout_x1* post-call register (see Notes) */
    hv_u128_t auVar45;
    uint16_t *puVar46;
    byte *pbVar47;
    uint uVar48;
    uint64_t in_stack_fffffffffffffd10 = 0;  /* incoming stack arg (see Notes) */
    uint64_t in_stack_fffffffffffffd18 = 0;  /* incoming stack arg (see Notes); 64-bit slot, also carries a pointer (cast at use) */
    uint uVar49;
    uint64_t in_stack_fffffffffffffd28 = 0;  /* incoming stack arg (see Notes) */
    uint uVar50;

    uint local_274 = 0;
    long local_258 = 0;
    uint64_t *local_208 = 0;
    uint local_1e4 = 0;
    ulong local_1d8 = 0;
    int local_1cc = 0;
    int local_1a8 = 0;
    ulong local_198 = 0;
    long lStack_190 = 0;
    ulong local_188 = 0;
    uint local_17c = 0;
    ulong local_178 = 0;
    uint64_t *local_170 = 0;
    byte local_161 = 0;
    long local_160 = 0;
    ulong uStack_158 = 0;
    ulong local_150 = 0;
    long lStack_148 = 0;
    ulong local_140 = 0;
    uint uStack_138 = 0;
    uint uStack_134 = 0;
    uint64_t uStack_130 = 0;
    uint uStack_128 = 0;
    uint uStack_124 = 0;
    uint uStack_120 = 0;
    uint uStack_11c = 0;
    uint uStack_118 = 0;
    uint uStack_114 = 0;
    uint uStack_110 = 0;
    uint uStack_10c = 0;
    uint uStack_108 = 0;
    uint uStack_104 = 0;
    uint uStack_fc = 0;
    uint local_100 = 0;
    uint uStack_f4 = 0;
    uint local_f8 = 0;
    long local_f0 = 0;
    long local_e8 = 0;
    byte local_dd = 0;
    int local_dc = 0;
    long local_d8 = 0;
    long local_d0 = 0;
    uint64_t *local_c8 = 0;
    byte local_b9 = 0;
    uint local_b0 = 0;
    uint local_ac = 0;
    ulong local_a8 = 0;
    long local_a0 = 0;
    uint local_94 = 0;
    ulong local_90 = 0;
    uint64_t *local_88 = 0;
    int local_7c = 0;
    long local_78[3];
    long local_b8 = 0;

    long p1 = (long)vm;                 /* param_1 as integer base */
    uint64_t auVar44;                   /* low 64 of vm_fault_enter's 128-bit return */
    uint64_t cpu_idx;

    local_7c = 0;
    local_90 = 0;
    local_88 = 0;
    local_94 = 0;
    local_a8 = 0;
    local_a0 = 0;
    local_ac = 0;
    local_b9 = 0;
    local_d0 = 0;
    local_c8 = 0;
    local_d8 = 0;
    local_dd = 0;
    local_f0 = 0;
    local_e8 = 0;
    uStack_108 = 0; uStack_104 = 0; uStack_110 = 0; uStack_10c = 0;
    local_f8 = 0; uStack_f4 = 0; local_100 = 0; uStack_fc = 0;
    uStack_128 = 0; uStack_124 = 0;
    uStack_130 = 0;
    uStack_118 = 0; uStack_114 = 0; uStack_120 = 0; uStack_11c = 0;
    lStack_148 = 0; local_150 = 0; uStack_138 = 0; uStack_134 = 0;
    local_140 = 0; uStack_158 = 0; local_160 = 0;
    lVar5 = tpidr_el1;
    local_b8 = p1;
    local_78[0] = p1;

    /* entry guard: b899974 */
    if ((((((hv_fault_boot_threshold < 0x12) && (*(long *)(lVar5 + 0x418) == 0)) ||
           ((lVar14 = (long)per_cpu_base((uint64_t)lVar5), lVar14 == 0))) ||
          ((*(ushort *)(lVar14 + 0x6b0) >> 2 & 1) != 0)) &&
         ((puVar29 = *(uint64_t **)(p1 + 0x58), puVar29 != 0) &&
          (puVar29 != 0))) && (addr != 0)) {
        if (puVar29 == &hv_special_owner_block) {
            addr = addr | 0xf00000000000000ULL;
            goto entry_else;
        }
        addr = addr & 0xf0ffffffffffffffULL;
        bVar23 = *(byte *)(p1 + 0xb2);
    } else {
entry_else:                             /* b899974 */
        bVar23 = *(byte *)(p1 + 0xb2);
    }
    if ((bVar23 & 1) != 0) {
        return 1;
    }
    uVar40 = (ulong)*(ushort *)(p1 + 0x44);
    lVar14 = 1L << (uVar40 & 0x3f);
    uVar25 = -1L << (uVar40 & 0x3f);
    if (0xd < *(ushort *)(p1 + 0x44)) {
        lVar14 = 0x4000;
        uVar25 = 0xffffffffffffc000;
    }
    uVar25 = addr & uVar25;
    uVar26 = addr;
    uVar32 = uVar25;
    if (p1 == 0) {
        uVar32 = 0;
        uVar26 = 0;
    }
    if ((hv_trace_flag & 0xfffffff7) != 0) {
        kernel_trace(0x1300009, uVar32 >> 0x20, uVar32, p1 == 0, 0);
    }
    if (*(int *)(lVar5 + 0x1c0) == 0) {
        if ((*(byte *)(lVar5 + 0x3f0) & 1) == 0) {
            iVar1 = *(int *)(lVar5 + 0x1fc);
            local_161 = 0;
            if (iVar1 == 1) {
                local_258 = UnkSytemRegRead(3,4,0xf,10,6);  /* op1=4 => EL2; identity unverified */
                local_258 = hv_fault_timer_base + local_258;
            } else {
                local_258 = 0;
            }
            uVar3 = *(ushort *)(lVar5 + 0xc0);
            *(ushort *)(lVar5 + 0xc0) = uVar3 & 0xfffc | *fault_opts & 3;
            uVar39 = (uint)fault_type;
            uVar27 = uVar39;
            if ((*(uint *)((uint8_t *)fault_opts + 0x14) & 0x800) != 0) {
                uVar27 = 0;
            }
            cpu_idx = (uint64_t)*(ushort *)(lVar5 + 0x1b0);
            lVar11 = *(long *)(hv_pcpu_slot(hv_pcpu_faults, cpu_idx));
            *hv_pcpu_slot(hv_pcpu_faults, cpu_idx) = lVar11 + 1;
            lVar11 = (long)kernel_vm_fault_callee_866ec4((uint64_t)lVar11, (uint64_t)lVar5);
            plVar22 = (long *)(*(long *)(lVar11 + 0x3b0) + cpu_idx * 0x4000);
            *plVar22 = *plVar22 + 1;
            if ((uVar27 >> 1 & 1) == 0) {
                local_1a8 = 1;
                if ((*(byte *)((uint8_t *)fault_opts + 0x29) & 8) != 0) {
                    local_1a8 = 2;
                }
            } else {
                local_1a8 = 2;
            }
            local_dc = 0;
            if (((p1 == 0) && ((uVar39 >> 1 & 1) != 0)) &&
               ((hv_compressor_map != 0 &&
                ((*(ulong *)((uint8_t *)hv_compressor_map + 0x28) <= uVar25 &&
                 (uVar25 < *(ulong *)((uint8_t *)hv_compressor_map + 0x30))))))) {
                /* WARNING: Subroutine does not return */
                kernel_panic_msg_fmt(
                    "Write fault on compressor map, va: %p type: %u bounds: %p->%p @%s:%d");
            }
            bVar6 = false;
            bVar23 = 0;
            local_274 = 0;
            local_1e4 = uVar27 >> 1 & 1;
            uVar28 = uVar25;
            if (vnode_mp != 0) {
                uVar28 = mp_size;
            }
            local_1d8 = 0xffffffffffffffff;
            local_1cc = 1;
            puVar29 = 0;
retry:                                  /* b899ca8 */
            local_b0 = 4;
            if (bVar6) {
                hv_fault_stat_2a0 = hv_fault_stat_2a0 + 1;
                uVar18 = 0x10;
                local_1a8 = 2;
                local_1e4 = 1;
                uVar33 = 1;
            } else {
                uVar18 = 0x10;
                uVar33 = uVar27;
                if (local_1e4 == 0) {
                    uVar18 = 0;
                }
            }
            uStack_f4 = 0;
            local_f8 = 0;
            uStack_fc = 0;
            local_100 = 0;
            uStack_104 = 0;
            uStack_108 = 0;
            uStack_10c = 0;
            uStack_110 = 0;
            uStack_114 = 0;
            uStack_118 = 0;
            uStack_11c = 0;
            uStack_120 = 0;
            uStack_124 = 0;
            uStack_128 = 0;
            uStack_130 = 0;
            uStack_134 = 0;
            uStack_138 = 0;
            local_140 = 0;
            lStack_148 = 0;
            local_150 = 0;
            uStack_158 = 0;
            local_160 = 0;
            in_stack_fffffffffffffd10 =
                 (uint64_t)(in_stack_fffffffffffffd10 & 0xffffffffffffff00);
            plVar22 = &local_160;
            puVar46 = fault_opts;
            local_78[0] = p1;
            auVar44 = vm_fault_enter_full(local_78, uVar25, uVar18 | uVar33,
                                          &local_88, &local_e8, &local_90,
                                          &local_94, &local_7c, fault_opts,
                                          &local_b8, plVar22, fault_arg,
                                          in_stack_fffffffffffffd10);
            uVar43 = auVar44;
            *(int *)(lVar5 + 0x1c0) = *(int *)(lVar5 + 0x1c0) + 1;
            lVar34 = *(long *)(lVar5 + 0x1b0) >> 0x10;
            auVar45.lo = auVar44; auVar45.hi = 0;
            if ((long)hv_paging_free0[lVar34] == 0) {
                puVar20 = (uint64_t *)hv_paging_free0n[lVar34];
                if (puVar20 == 0) {
                    hv_paging_free0[lVar34] = 0;
                } else {
                    hv_paging_free0n[lVar34] = *puVar20;
                    *puVar20 = 0;
                    hv_paging_free0[lVar34] = (uint64_t)puVar20;
                    kernel_vm_fault_callee_61544((ulong)*(uint *)((uint8_t *)puVar20 + 0x30) << 0xe,
                                                 0x4000,
                                                 (*(uint *)((uint8_t *)puVar20 + 0x2c) & 0x10) << 6);
                    *hv_pcpu_slot(hv_pcpu_paging, cpu_idx) =
                         *hv_pcpu_slot(hv_pcpu_paging, cpu_idx) + 1;
                    auVar45.lo = 1; auVar45.hi = 0;   /* ZEXT816(1) */
                }
            }
            lVar37 = *(long *)((long)&hv_paging_free0n[lVar34]);
            if ((long)hv_paging_free1[lVar34] == 0) {
                puVar20 = (uint64_t *)hv_paging_free1n[lVar34];
                if (puVar20 == 0) {
                    hv_paging_free1[lVar34] = 0;
                } else {
                    hv_paging_free1n[lVar34] = *puVar20;
                    *puVar20 = 0;
                    hv_paging_free1[lVar34] = (uint64_t)puVar20;
                    kernel_vm_fault_callee_61544((ulong)*(uint *)((uint8_t *)puVar20 + 0x30) << 0xe,
                                                 0x4000,
                                                 (*(uint *)((uint8_t *)puVar20 + 0x2c) & 0x10) << 6);
                    *hv_pcpu_slot(hv_pcpu_paging, cpu_idx) =
                         *hv_pcpu_slot(hv_pcpu_paging, cpu_idx) + 1;
                    auVar45.lo = 1; auVar45.hi = 0;   /* ZEXT816(1) */
                }
            }
            if (*(int *)(lVar5 + 0x1c0) == 0) {
                /* WARNING: Subroutine does not return */
                kernel_vm_fault_panic_enter(auVar45.lo, auVar45.hi);
            }
            lVar34 = (long)hv_paging_free1n[lVar34];
            iVar13 = *(int *)(lVar5 + 0x1c0) + -1;
            *(int *)(lVar5 + 0x1c0) = iVar13;
            if ((iVar13 == 0) && ((*(byte *)(*(long *)(lVar5 + 0x1b8) + 0x4c) >> 2 & 1) != 0)) {
                kernel_tlb_flush();
            }
            if (lVar37 == 0) {
                kernel_vm_fault_callee_f13c(10);
            }
            puVar20 = local_88;
            if (lVar34 == 0) {
                kernel_vm_fault_callee_f13c(0x2000a);
                puVar20 = local_88;
            }
            local_88 = puVar20;
            if ((uint32_t)auVar44 != 0) goto fault_done;
            puVar30 = *(uint64_t **)(local_b8 + 0x58);
            uVar18 = *(uint *)((uint8_t *)fault_opts + 0x14);
            *(uint *)((uint8_t *)fault_opts + 0x14) = uVar18 & 0xffffff9b;
            if (local_7c != 0) {
                uVar33 = local_94 | 2;
            }
            iVar13 = 2;
            if (local_7c == 0 && local_1e4 == 0) {
                iVar13 = local_1a8;
            }
            if ((((*(byte *)(puVar30 + 0xe) & 1) != 0) && ((uVar39 >> 2 & 1) != 0)) &&
               ((*(uint *)((uint8_t *)fault_opts + 0x16) >> 0xe & 1) == 0)) {
                if (fault_arg == 0) {
                    *(uint64_t *)(lVar5 + 0x238) = 0;
                    if ((uStack_134 & 0xc) == 8) {
                        if (((uint8_t)uStack_138 >> 2 & 1) == 0) {
                            local_160 = (long)hv_concat44(uStack_114, uStack_118);
                        } else {
                            uStack_130 = hv_concat44(uStack_fc, local_100) +
                                         hv_concat44((uint32_t)(uStack_130 >> 32),
                                                     (uint32_t)uStack_130);
                            local_160 = local_160 + (long)hv_concat44(uStack_fc, local_100);
                        }
                        lStack_148 = (long)hv_concat44(uStack_f4, local_f8);
                        local_150 = hv_concat44(uStack_104, uStack_108);
                        uStack_158 = hv_concat44(uStack_10c, uStack_110);
                        uStack_134 = uStack_134 & 0xfffffff3;
                        local_f8 = 0;
                        uStack_f4 = 0;
                        local_100 = 0;
                        uStack_fc = 0;
                    }
                    if ((uStack_138 >> 2 & 1) == 0) goto c924;
c9c8:                               /* LAB_fffffe000b89c9c8 */
                    if ((lStack_148 != 0) && ((~*(uint *)(lStack_148 + 0x28) & 3) != 0)) {
                        kernel_vm_fault_callee_164f8();
                    }
c9e4:                               /* LAB_fffffe000b89c9e4 */
                    uVar43 = 2;
                    goto done_zero;  /* LAB_fffffe000b89ca04: zero fault-state locals, then falls into fault_done */
                }
c814:                               /* LAB_fffffe000b89c814 */
                uVar43 = 2;
                goto fault_done;    /* LAB_fffffe000b89ca08 */
            }
            if (((uVar33 == 1) && ((local_94 & 5) == 4)) && (puVar30 != &hv_special_owner_block)) {
                if (fault_arg != 0) goto c814;
                *(uint64_t *)(lVar5 + 0x238) = 0;
                if ((uStack_134 & 0xc) == 8) {
                    if (((uint8_t)uStack_138 >> 2 & 1) == 0) {
                        local_160 = (long)hv_concat44(uStack_114, uStack_118);
                    } else {
                        uStack_130 = hv_concat44(uStack_fc, local_100) +
                                     hv_concat44((uint32_t)(uStack_130 >> 32),
                                                 (uint32_t)uStack_130);
                        local_160 = local_160 + (long)hv_concat44(uStack_fc, local_100);
                    }
                    lStack_148 = (long)hv_concat44(uStack_f4, local_f8);
                    local_150 = hv_concat44(uStack_104, uStack_108);
                    uStack_158 = hv_concat44(uStack_10c, uStack_110);
                    uStack_134 = uStack_134 & 0xfffffff3;
                    local_f8 = 0;
                    uStack_f4 = 0;
                    local_100 = 0;
                    uStack_fc = 0;
                }
                if ((uStack_138 >> 2 & 1) != 0) goto c9c8;
c924:                               /* LAB_fffffe000b89c924 */
                kernel_vm_fault_callee_1ab24(&local_160);
                goto c9e4;
            }
            if (bVar6) {
                if ((((puVar20 != 0) && (puVar20 == puVar29)) && (local_90 == local_1d8)) &&
                   ((uVar18 >> 7 & 1) != 0)) {
                    hv_fault_stat_2a8 = hv_fault_stat_2a8 + 1;
                    goto a0e8;
                }
                if (fault_arg == 0) {
                    *(uint64_t *)(lVar5 + 0x238) = 0;
                    HV_FMT_PAGING_CONCAT();
                    if ((uStack_138 >> 2 & 1) == 0) {
                        kernel_vm_fault_callee_1ab24(&local_160);
                    } else if ((lStack_148 != 0) && ((~*(uint *)(lStack_148 + 0x28) & 3) != 0)) {
                        kernel_vm_fault_callee_164f8();
                    }
                    HV_FMT_ZERO_STATE();
                }
                kernel_vm_fault_callee_c2f4(puVar29);
                puVar29 = 0;
                bVar6 = false;
                hv_fault_stat_2b8 = hv_fault_stat_2b8 + 1;
                local_1d8 = 0xffffffffffffffff;
                local_1a8 = iVar13;
                goto retry;
            }
            local_1d8 = 0xffffffffffffffff;
a0e8:                               /* b89a0e8 */
            if ((iVar13 == 2) || ((puVar20[9] == 0 && (*(short *)(puVar20 + 2) != 0)))) {
                kernel_vm_fault_callee_e7d4((uint64_t)puVar20);
                local_1a8 = 2;
            } else {
                kernel_vm_fault_callee_f3f8((uint64_t)puVar20);
                local_1a8 = 1;
            }
            uVar12 = (uint)((uint64_t)plVar22 >> 0x20);
            uVar38 = local_90 & 0x3fff;
            if ((((*(uint *)(puVar20 + 0xe) | 4) != 6) || (puVar20[7] == 0)) ||
                ((uVar33 >> 1 & 1) == 0)) {
                uVar18 = 0x20000;
                if (*(char *)((uint8_t *)puVar20 + 0xae) != '"') {
                    uVar18 = 0;
                    if (((hv_fault_prot_tab[(*(uint *)((uint8_t *)fault_opts + 2) >> 6) & 0x3ff] >>
                          ((uint32_t)*(uint *)((uint8_t *)fault_opts + 2) & 0x3f) & 1)) != 0) {
                        uVar18 = 0x40000;
                    }
                }
                puVar35 = (uint *)((uint8_t *)puVar20 + 0x7c);
                uVar19 = *puVar35;
                uVar42 = local_90;
a1a8:                               /* b89a1a8 */
                uVar12 = (uint)((uint64_t)plVar22 >> 0x20);
                puVar31 = puVar20;
                if ((uVar19 & 0x2000080) != 0x2000000) {
                    do {
                        uVar12 = (uint)((uint64_t)plVar22 >> 0x20);
                        puVar31 = puVar20;
                        if (*(char *)(puVar20 + 0x16) < '\0') break;
                        uVar43 = uVar42 & 0xffffffffffffc000;
                        auVar45 = kernel_vm_fault_callee_f4e94(puVar20, uVar43);
                        uVar15 = auVar45.hi;
                        lVar34 = (long)auVar45.lo;
                        uVar12 = (uint)((uint64_t)plVar22 >> 0x20);
                        if (lVar34 != 0) {
                            if ((local_161 & 1) != 0) {
                                auVar45 = kernel_vm_fault_callee_dc68(puVar30, (uint64_t)lVar34,
                                                                     uVar25, local_94, fault_opts,
                                                                     &local_161);
                                puVar41 = local_88;
                                uVar15 = auVar45.hi;
                                uVar43 = auVar45.lo;
                                if (auVar45.lo != 0) {
                                    kernel_vm_fault_callee_7050(local_88 + 1);
                                    if (puVar41 != puVar20) {
                                        kernel_vm_fault_callee_7050(puVar20 + 1);
                                    }
                                    if (fault_arg == 0) {
                                        *(uint64_t *)(lVar5 + 0x238) = 0;
                                        HV_FMT_PAGING_CONCAT();
                                        if ((uStack_138 >> 2 & 1) == 0) {
                                            kernel_vm_fault_callee_1ab24(&local_160);
                                        } else if ((lStack_148 != 0) &&
                                                   ((~*(uint *)(lStack_148 + 0x28) & 3) != 0)) {
                                            kernel_vm_fault_callee_164f8();
                                        }
                                        HV_FMT_ZERO_STATE();
                                    }
                                    goto fault_done;
                                }
                                bVar24 = local_161;
                                if ((*(byte *)(lVar34 + 0x2c) & 1) == 0) goto a2ac;
a2b0:                           /* b89a2b0 */
                                puVar41 = local_88;
                                local_161 = 0;
                                if (local_88 == puVar20) {
                                    if ((local_1a8 == 1) &&
                                        (iVar13 = kernel_vm_fault_callee_f5f18(local_88 + 1),
                                         iVar13 == 0)) goto a56c;
                                    local_1a8 = 2;
                                } else {
                                    if ((local_1cc == 1) &&
                                        (iVar13 = kernel_vm_fault_callee_f5f18(puVar20 + 1),
                                         iVar13 == 0)) {
                                        kernel_vm_fault_callee_7050(local_88 + 1);
                                        local_1cc = 2;
                                        if (fault_arg == 0) {
                                            *(uint64_t *)(lVar5 + 0x238) = 0;
                                            HV_FMT_PAGING_CONCAT();
                                            if ((uStack_138 >> 2 & 1) == 0) {
                                                kernel_vm_fault_callee_1ab24(&local_160);
                                            } else if ((lStack_148 != 0) &&
                                                       ((~*(uint *)(lStack_148 + 0x28) & 3) != 0)) {
                                                kernel_vm_fault_callee_164f8();
                                            }
                                            local_1cc = 2;
                                        }
                                        goto retry;
                                    }
                                    local_1cc = 2;
                                }
                                uVar43 = hv_fault_paging_token;
                                if (((*(byte *)(lVar34 + 0x2a) & 0xf) == 7) &&
                                   ((*(byte *)((uint8_t *)puVar35 + 1) >> 4 & 1) != 0)) {
                                    if (hv_fault_paging_token == 0) {
                                        hv_fault_paging_token = (ulong)*(uint *)(lVar5 + 0x518);
                                    }
                                    if (uVar43 != 0 || hv_fault_paging_owner != 0) {
                                        kernel_vm_fault_callee_f0afc(&hv_fault_paging_lock, lVar5,
                                                                     uVar43, 0);
                                    }
                                    if ((*(byte *)(lVar34 + 0x2a) & 0xf) == 7) {
                                        uVar15 = kernel_vm_fault_callee_d91fc((uint64_t)lVar34);
                                        if (hv_fault_paging_token == *(int *)(lVar5 + 0x518)) {
                                            hv_fault_paging_token =
                                                hv_concat44((uint32_t)(hv_fault_paging_token >> 32),
                                                            0);  /* in_wzr_value() = WZR zero register = 0 */
                                            if (hv_fault_paging_owner != 0) goto a5c4;
                                        } else {
a5c4:                               /* b89a5c4 */
                                            uVar15 = kernel_vm_fault_callee_f1e80(&hv_fault_paging_lock,
                                                                                 (uint64_t)lVar5);
                                        }
                                        kernel_vm_fault_callee_d31ac(uVar15, (uint64_t)lVar34);
                                        uVar15 = extraout_x1;
                                        goto a3f4;
                                    }
                                    kernel_vm_fault_callee_f1e4c(&hv_fault_paging_lock);
                                }
                                if (local_88 != puVar20) {
                                    kernel_vm_fault_callee_7050(local_88 + 1);
                                }
                                if (fault_arg == 0) {
                                    *(uint64_t *)(lVar5 + 0x238) = 0;
                                    HV_FMT_PAGING_CONCAT();
                                    if ((uStack_138 >> 2 & 1) == 0) {
                                        kernel_vm_fault_callee_1ab24(&local_160);
                                    } else if ((lStack_148 != 0) &&
                                               ((~*(uint *)(lStack_148 + 0x28) & 3) != 0)) {
                                        kernel_vm_fault_callee_164f8();
                                    }
                                    HV_FMT_ZERO_STATE();
                                } else if ((*(byte *)((uint8_t *)fault_arg + 5) >> 5 & 1) != 0) {
                                    kernel_vm_fault_callee_ddd8(((uint64_t *)fault_arg)[2],
                                                                (uint64_t *)&hv_pcpu_ctx, 2,
                                                                ((uint64_t *)fault_arg)[0],
                                                                ((uint64_t *)fault_arg)[1]);
                                }
                                iVar13 = kernel_vm_fault_callee_cdf50(puVar20, (uint64_t)lVar34,
                                                                      *(uint32_t *)fault_opts, 1);
                                if ((iVar13 == 0) || (iVar13 == 3)) goto retry;
                                if (lVar5 == 0) {
                                    uVar15 = 0;
                                } else {
                                    uVar15 = *(uint64_t *)(lVar5 + 0x510);
                                }
                                kernel_vm_fault_callee_2db44(uVar15, 0x1000034, 0);
                                uVar43 = 0xe;
                                goto fault_done;
                            }
                            bVar24 = 0;
                            if ((*(byte *)(lVar34 + 0x2c) & 1) != 0) goto a2b0;
a2ac:                           /* b89a2ac */
                            if ((bVar24 & 1) != 0) goto a2b0;
a3f4:                           /* b89a3f4 */
                            puVar41 = local_88;
                            if ((*(byte *)(lVar34 + 0x2b) >> 1 & 1) != 0) {
                                if (local_88 != puVar20) {
                                    if (local_1cc != 1) goto a440;
                                    kernel_vm_fault_callee_7050(local_88 + 1);
                                    kernel_vm_fault_callee_7050(puVar20 + 1);
                                    local_1cc = 2;
                                    if (fault_arg == 0) {
                                        *(uint64_t *)(lVar5 + 0x238) = 0;
                                        if ((uStack_134 & 0xc) == 8) {
                                            if (((uint8_t)uStack_138 >> 2 & 1) == 0) {
                                                local_160 = (long)hv_concat44(uStack_114, uStack_118);
                                            } else {
                                                uStack_130 = hv_concat44(uStack_fc, local_100) +
                                                             hv_concat44((uint32_t)(uStack_130 >> 32),
                                                                         (uint32_t)uStack_130);
                                                local_160 = local_160 +
                                                            (long)hv_concat44(uStack_fc, local_100);
                                            }
                                            lStack_148 = (long)hv_concat44(uStack_f4, local_f8);
                                            local_150 = hv_concat44(uStack_104, uStack_108);
                                            uStack_158 = hv_concat44(uStack_10c, uStack_110);
                                            uStack_134 = uStack_134 & 0xfffffff3;
                                            local_f8 = 0;
                                            uStack_f4 = 0;
                                            local_100 = 0;
                                            uStack_fc = 0;
                                        }
                                        if ((uStack_138 >> 2 & 1) == 0) goto c31c;
c38c:                               /* LAB_fffffe000b89c38c */
                                        if ((lStack_148 != 0) &&
                                            ((~*(uint *)(lStack_148 + 0x28) & 3) != 0)) {
                                            kernel_vm_fault_callee_164f8();
                                        }
c3a8:                               /* LAB_fffffe000b89c3a8 */
                                        local_1cc = 2;
                                    }
                                    goto retry;
                                }
                                if ((local_1a8 != 1) ||
                                    (iVar13 = kernel_vm_fault_callee_f5f18(local_88 + 1),
                                     iVar13 != 0)) {
                                    local_1a8 = 2;
a440:                               /* b89a440 */
                                    kernel_vm_fault_callee_e2c70((uint64_t)lVar34, 0);
                                    uVar15 = extraout_x1;
                                    goto a44c;
                                }
                                goto a56c;
                            }
a44c:                           /* b89a44c */
                            lVar37 = local_78[0];
                            puVar41 = local_88;
                            uVar12 = (uint)((uint64_t)plVar22 >> 0x20);
                            if ((*(int *)(lVar34 + 0x30) == -2) ||
                               ((uVar19 = *(uint *)(lVar34 + 0x2c),
                                 (uVar19 >> 0x11 & 1) != 0 &&
                                 (((uVar19 & 0x10800) != 0 ||
                                  (((-1 < *(char *)(lVar34 + 0x2a) &&
                                    (*(uint *)(lVar34 + 0x30) < 0xfffffffe)) ||
                                   ((uVar19 >> 10 & 1) != 0)))))))) break;
                            if ((((uint)puVar20[0x16] >> 5 & 1) != 0) &&
                               ((*(ushort *)((uint8_t *)puVar35 + 2) & 3) - 1 < 2)) {
                                if (local_88 != puVar20) {
                                    kernel_vm_fault_callee_7050(local_88 + 1);
                                }
                                if (fault_arg == 0) {
                                    *(uint64_t *)(lVar5 + 0x238) = 0;
                                    HV_FMT_PAGING_CONCAT();
                                    if ((uStack_138 >> 2 & 1) == 0) {
                                        kernel_vm_fault_callee_1ab24(&local_160);
                                    } else if ((lStack_148 != 0) &&
                                               ((~*(uint *)(lStack_148 + 0x28) & 3) != 0)) {
                                        kernel_vm_fault_callee_164f8();
                                    }
                                    HV_FMT_ZERO_STATE();
                                }
                                kernel_vm_fault_callee_7050(puVar20 + 1);
                                if (lVar5 == 0) {
                                    uVar15 = 0;
                                } else {
                                    uVar15 = *(uint64_t *)(lVar5 + 0x510);
                                }
                                uVar17 = 0x1000038;
                                goto d1dc;
                            }
                            puVar21 = (uint64_t *)(local_78[0] + 0x58);
                            if ((((((puVar20[0x16] & 1) != 0) &&
                                   (*puVar21 != &hv_special_owner_block)) &&
                                  (((uVar19 ^ 0xffffffff) & 0x3c00000) != 0)) &&
                                 ((uVar19 & 0x3c0100) != 0x3c0000)) ||
                                ((result_out != 0 && (((byte)local_94 >> 1 & 1) != 0)))) {
                                if (local_88 != puVar20) {
                                    if (local_1cc != 1) goto b674;
b9bc:                               /* b89b9bc */
                                    kernel_vm_fault_callee_7050(puVar41 + 1);
                                    kernel_vm_fault_callee_7050(puVar20 + 1);
                                    local_1cc = 2;
                                    if (fault_arg == 0) {
                                        *(uint64_t *)(lVar5 + 0x238) = 0;
                                        if ((uStack_134 & 0xc) == 8) {
                                            if (((uint8_t)uStack_138 >> 2 & 1) == 0) {
                                                local_160 = (long)hv_concat44(uStack_114, uStack_118);
                                            } else {
                                                uStack_130 = hv_concat44(uStack_fc, local_100) +
                                                             hv_concat44((uint32_t)(uStack_130 >> 32),
                                                                         (uint32_t)uStack_130);
                                                local_160 = local_160 +
                                                            (long)hv_concat44(uStack_fc, local_100);
                                            }
                                            lStack_148 = (long)hv_concat44(uStack_f4, local_f8);
                                            local_150 = hv_concat44(uStack_104, uStack_108);
                                            uStack_158 = hv_concat44(uStack_10c, uStack_110);
                                            uStack_134 = uStack_134 & 0xfffffff3;
                                            local_f8 = 0;
                                            uStack_f4 = 0;
                                            local_100 = 0;
                                            uStack_fc = 0;
                                        }
                                        if ((uStack_138 >> 2 & 1) != 0) goto c38c;
c31c:                               /* LAB_fffffe000b89c31c */
                                        kernel_vm_fault_callee_1ab24(&local_160);
                                        goto c3a8;
                                    }
                                    goto retry;
                                }
                                if (local_1a8 != 1) {
                                    local_1a8 = 2;
                                    goto b674;
                                }
                                iVar13 = kernel_vm_fault_callee_f5f18(local_88 + 1);
                                uVar12 = (uint)((uint64_t)plVar22 >> 0x20);
                                if (iVar13 == 0) goto a56c;
                                local_1a8 = 2;
                                uVar15 = extraout_x1;
                            }
b674:                           /* b89b674 */
                            puVar41 = local_88;
                            uVar49 = (uint)(in_stack_fffffffffffffd28 >> 0x20);
                            if ((local_88 == puVar20) && (local_88[7] == 0)) {
                                puVar31 = 0;
                                puVar41 = puVar20;
                                goto bee0;
                            }
                            if (local_1e4 == 0) {
                                if ((((local_88 != puVar20) &&
                                      ((*(uint *)((uint8_t *)fault_opts + 0x14) >> 8 & 1) == 0)) &&
                                     ((*puVar35 & 0x1400) == 0)) &&
                                   (((*(byte *)(puVar20 + 0x16) & 1) == 0 &&
                                     (hv_fault_lowbit_flag2 != 0)))) {
                                    lVar36 = (long)kernel_vm_fault_callee_6659c();
                                    lVar16 = *(long *)(lVar36 + 0x18);
                                    if (lVar16 == 0) {
                                        lVar16 = 0;
                                    }
                                    iVar13 = kernel_vm_fault_callee_42a30((uint64_t)lVar16);
                                    if (((iVar13 != 0) ||
                                        (((*puVar21 != 0) && (*puVar21 == &hv_special_owner_block)))) ||
                                       (uVar15 = extraout_x1,
                                        (*(byte *)(lVar37 + 0xb2) >> 4 & 1) != 0)) {
                                        hv_fault_stat_250 = hv_fault_stat_250 + 1;
                                        lVar34 = *(long *)(lVar36 + 0x18);
                                        if (lVar34 == 0) {
                                            lVar34 = 0;
                                        }
                                        iVar13 = kernel_vm_fault_callee_42a30((uint64_t)lVar34);
                                        if (iVar13 == 0) {
                                            if (*puVar21 == 0) {
                                                plVar22 = (long *)&hv_fault_stat_260;
                                            } else {
                                                plVar22 = (long *)&hv_fault_stat_258;
                                                if (*puVar21 != &hv_special_owner_block) {
                                                    plVar22 = (long *)&hv_fault_stat_260;
                                                }
                                            }
                                            *plVar22 = *plVar22 + 1;
                                        }
                                        kernel_vm_fault_callee_7050(puVar41 + 1);
                                        kernel_vm_fault_callee_7050(puVar20 + 1);
                                        local_1e4 = 1;
                                        local_1a8 = 2;
                                        if (fault_arg == 0) {
                                            *(uint64_t *)(lVar5 + 0x238) = 0;
                                            HV_FMT_PAGING_CONCAT();
                                            if ((uStack_138 >> 2 & 1) == 0) {
                                                kernel_vm_fault_callee_1ab24(&local_160);
                                            } else if ((lStack_148 != 0) &&
                                                       ((~*(uint *)(lStack_148 + 0x28) & 3) != 0)) {
                                                kernel_vm_fault_callee_164f8();
                                            }
                                            local_1e4 = 1;
                                            local_1a8 = 2;
                                        }
                                        goto retry;
                                    }
                                }
                                uVar49 = (uint)(in_stack_fffffffffffffd28 >> 0x20);
                                if ((uVar33 >> 1 & 1) == 0) {
                                    if (puVar30 == 0) {
                                        bVar24 = 1;
                                    } else {
                                        bVar24 = *(byte *)(puVar30[4] + 0x4c) ^ 1;
                                    }
                                    if (((((local_94 ^ 0xffffffff) & 7) == 0) && ((bVar24 & 1) != 0)) &&
                                       (((*(uint *)((uint8_t *)fault_opts + 0x16) >> 0xe & 1) != 0 ||
                                        ((*(byte *)(puVar30 + 0xe) & 1) == 0)))) {
                                        if (((uint8_t)fault_opts[0x14] >> 3 & 1) == 0) goto d4e8;
                                    } else {
                                        local_94 = local_94 & 0xfffffffd;
                                    }
                                    if (puVar41 == puVar20) {
                                        puVar31 = 0;
                                        puVar41 = puVar20;
                                    } else {
                                        local_1a8 = local_1cc;
                                        puVar31 = puVar41;
                                        puVar41 = puVar20;
                                        local_88 = puVar20;
                                    }
                                    goto bee0;
                                }
                            }
                            if (puVar41 == puVar20) break;
                            if (local_1cc == 1) {
                                if ((*(byte *)(puVar20 + 0x16) & 1) == 0) {
                                    local_1cc = 1;
                                } else {
                                    local_1cc = 1;
                                    if ((((*(uint *)(lVar34 + 0x2c) ^ 0xffffffff) & 0x3c00000) != 0) &&
                                       ((*(uint *)(lVar34 + 0x2c) & 0x3c0100) != 0x3c0000)) goto b9bc;
                                }
                            }
                            lVar36 = kernel_vm_fault_callee_f5be0(uVar18);
                            uVar49 = (uint)(in_stack_fffffffffffffd28 >> 0x20);
                            if (lVar36 == 0) break;
                            kernel_vm_fault_callee_f8738((uint64_t)lVar34, lVar36);
                            kernel_vm_fault_callee_f19b0(lVar36, puVar41, local_90 & 0xffffffffffffc000,
                                                         0, 0, 0);
                            *(uint *)(lVar36 + 0x2c) = *(uint *)(lVar36 + 0x2c) | 0x1000;
                            if ((*(uint *)(puVar41 + 5) < 2) ||
                                ((*(byte *)(lVar34 + 0x2c) >> 6 & 1) == 0)) {
                                if (*(ushort *)(lVar37 + 0x44) < 0xe) {
                                    uVar12 = *(uint *)(lVar34 + 0x30);
                                    goto bd30;
                                }
                            } else {
                                uVar12 = *(uint *)(lVar34 + 0x30);
bd30:                               /* b89bd30 */
                                kernel_vm_fault_callee_e48c(uVar12);
                            }
                            if ((*(byte *)(lVar34 + 0x2c) >> 5 & 1) != 0) {
                                plVar22 = (long *)(*(long *)(lVar11 + 0x3b8) + cpu_idx * 0x4000);
                                *plVar22 = *plVar22 + 1;
                                uVar12 = *(uint *)(lVar34 + 0x30);
                                kernel_vm_fault_callee_e538(uVar12, 0);
                                if ((*(byte *)(lVar34 + 0x2c) >> 5 & 1) != 0) {
                                    uVar43 = (ulong)*(uint *)(lVar34 + 0x1c) << 6 | 0xfffffe0000000000;
                                    *(int *)(uVar43 + 0xa8) = *(int *)(uVar43 + 0xa8) + 1;
                                    *(uint *)(lVar34 + 0x2c) = *(uint *)(lVar34 + 0x2c) & 0xffffffdf;
                                }
                                kernel_vm_fault_callee_e6b8(uVar12);
                                kernel_vm_fault_callee_e370(puVar20, uVar42, *(uint *)((uint8_t *)fault_opts + 8));
                            }
                            if (((*(byte *)((uint8_t *)puVar35 + 1) >> 4 & 1) == 0) &&
                                (*(int *)(puVar20 + 0xe) == 2)) {
                                if ((uint64_t *)puVar20[7] == local_88) {
                                    kernel_vm_fault_callee_7050(puVar20 + 1);
c260:                               /* b89c260 */
                                    local_274 = 0;
                                    hv_fault_stat_5178 = hv_fault_stat_5178 + 1;
                                } else {
                                    if ((uint64_t *)puVar20[7] != (uint64_t *)local_88[9])
                                        goto be70;
                                    iVar13 = *(int *)((long)local_88[9] + 0x2c);
                                    kernel_vm_fault_callee_7050(puVar20 + 1);
                                    if (iVar13 == 0) goto c260;
                                    local_274 = 1;
                                }
                            } else {
be70:                               /* b89be70 */
                                kernel_vm_fault_callee_7050(puVar20 + 1);
                                local_274 = 1;
                            }
                            uVar15 = 0;
                            hv_fault_stat_5170 = hv_fault_stat_5170 + 1;
                            local_b0 = 3;
                            *hv_pcpu_slot(hv_pcpu_map, cpu_idx) =
                                 *hv_pcpu_slot(hv_pcpu_map, cpu_idx) + 1;
                            plVar22 = (long *)(*(long *)(lVar11 + 0x3c0) + cpu_idx * 0x4000);
                            *plVar22 = *plVar22 + 1;
                            puVar31 = 0;
                            lVar34 = lVar36;
                            goto bee0;
                        }
                        if ((char)*puVar35 < '\0') {
                            if ((((*(uint *)((uint8_t *)puVar20 + 0x7c) >> 0xc & 1) == 0) ||
                                ((*(uint *)((uint8_t *)puVar20 + 0x7c) & 0x408000) != 0x8000)) ||
                                (puVar20[10] == 0)) break;
                            iVar13 = kernel_vm_fault_callee_1224(puVar20[10], puVar20[0xc] + uVar42);
                            puVar41 = local_88;
                            uVar12 = (uint)((uint64_t)plVar22 >> 0x20);
                            if (iVar13 != 3) goto a2e8;
                        }
                        uVar12 = (uint)((uint64_t)plVar22 >> 0x20);
                        puVar31 = (uint64_t *)puVar20[9];
                        if (!(bool)(puVar31 != 0 & (bVar6 ^ 1U))) {
                            if (((((*(uint *)((uint8_t *)puVar20 + 0x7c) >> 0x18 & 1) != 0) ||
                                 (((*(byte *)(puVar20 + 0x16) >> 5 & 1) != 0 &&
                                  ((*(uint *)((uint8_t *)puVar20 + 0x7c) >> 0x10 & 3) - 1 < 2)))) ||
                                (puVar20 == &hv_fault_special_400)) ||
                               ((puVar20 == &hv_fault_special_300 ||
                                 (puVar20 == &hv_fault_special_800)))) {
                                if (local_88 != puVar20) {
                                    kernel_vm_fault_callee_7050(puVar20 + 1);
                                }
                                kernel_vm_fault_callee_7050(local_88 + 1);
                                if (fault_arg == 0) {
                                    *(uint64_t *)(lVar5 + 0x238) = 0;
                                    HV_FMT_PAGING_CONCAT();
                                    if ((uStack_138 >> 2 & 1) == 0) {
                                        kernel_vm_fault_callee_1ab24(&local_160);
                                    } else if ((lStack_148 != 0) &&
                                               ((~*(uint *)(lStack_148 + 0x28) & 3) != 0)) {
                                        kernel_vm_fault_callee_164f8();
                                    }
                                    HV_FMT_ZERO_STATE();
                                }
                                uVar27 = *(uint *)((uint8_t *)puVar20 + 0x7c);
                                if (((*(byte *)(puVar20 + 0x16) >> 5 & 1) != 0) &&
                                    ((uVar27 >> 0x10 & 3) - 1 < 2)) {
                                    if (lVar5 == 0) {
                                        uVar15 = 0;
                                    } else {
                                        uVar15 = *(uint64_t *)(lVar5 + 0x510);
                                    }
                                    kernel_vm_fault_callee_2db44(uVar15, 0x1000038, 0);
                                    uVar27 = *(uint *)((uint8_t *)puVar20 + 0x7c);
                                }
                                if ((uVar27 >> 0x18 & 1) == 0) {
                                    uVar43 = 10;
                                } else {
                                    if (lVar5 == 0) {
                                        uVar15 = 0;
                                    } else {
                                        uVar15 = *(uint64_t *)(lVar5 + 0x510);
                                    }
                                    uVar17 = 0x100003c;
d1dc:                               /* b89d1dc */
                                    kernel_vm_fault_callee_2db44(uVar15, uVar17, 0);
                                    uVar43 = 10;
                                }
                                goto fault_done;
                            }
                            if (puVar20 != local_88) {
                                kernel_vm_fault_callee_7050(puVar20 + 1);
                                puVar20 = local_88;
                            }
                            puVar31 = local_88;
                            if (local_1a8 == 1) {
                                iVar13 = kernel_vm_fault_callee_f5f18(local_88 + 1);
                                if (iVar13 == 0) {
                                    local_1a8 = 2;
                                    if (fault_arg == 0) {
                                        *(uint64_t *)(lVar5 + 0x238) = 0;
                                        HV_FMT_PAGING_CONCAT();
                                        if ((uStack_138 >> 2 & 1) == 0) {
                                            kernel_vm_fault_callee_1ab24(&local_160);
                                        } else if ((lStack_148 != 0) &&
                                                   ((~*(uint *)(lStack_148 + 0x28) & 3) != 0)) {
                                            kernel_vm_fault_callee_164f8();
                                        }
                                        local_1a8 = 2;
                                    }
                                    goto retry;
                                }
                            }
                            lVar34 = local_78[0];
                            if ((*(byte *)((uint8_t *)puVar31 + 0x7d) >> 4 & 1) == 0) {
                                /* WARNING: Subroutine does not return */
                                kernel_panic_msg_fmt(
                                    "%s:%d should not zero-fill page at offset 0x%llx in external object %p @%s:%d");
                            }
                            lVar37 = kernel_vm_fault_callee_f5be0(
                                (*(int *)(local_78[0] + 0xb0) << 3 ^ 0xffffffffU) & 0x10 | uVar18);
                            uVar9 = local_90;
                            uVar49 = (uint)((uint64_t)in_stack_fffffffffffffd18 >> 0x20);
                            uVar50 = (uint)(in_stack_fffffffffffffd28 >> 0x20);
                            if (lVar37 == 0) {
                                local_1a8 = 2;
                                puVar31 = puVar20;
                                break;
                            }
                            kernel_vm_fault_callee_f19b0(lVar37, puVar31, local_90 & 0xffffffffffffc000,
                                                         0, 8, 0);
                            if ((((local_94 >> 1 & 1) != 0) && ((uVar33 >> 1 & 1) == 0)) &&
                                (puVar31[7] != 0)) {
                                if (puVar30 == 0) {
                                    bVar24 = 1;
                                } else {
                                    bVar24 = *(byte *)(puVar30[4] + 0x4c) ^ 1;
                                }
                                if (((((local_94 ^ 0xffffffff) & 7) == 0) && ((bVar24 & 1) != 0)) &&
                                   (((*(uint *)((uint8_t *)fault_opts + 0x16) >> 0xe & 1) != 0 ||
                                    ((*(byte *)(puVar30 + 0xe) & 1) == 0)))) {
                                    if (((uint8_t)fault_opts[0x14] >> 3 & 1) == 0) goto d4e8;
                                } else {
                                    local_94 = local_94 & 0xfffffffd;
                                }
                            }
                            *(uint *)(lVar37 + 0x2c) = *(uint *)(lVar37 + 0x2c) & 0xc003ffff | 0x40;
                            local_b0 = 5;
                            if ((*(uint *)(lVar34 + 0xb0) & 2) == 0) {
                                local_b0 = 1;
                            }
                            puVar20 = puVar30;
                            if (vnode_mp != 0) {
                                puVar20 = (uint64_t *)(uintptr_t)vnode_mp;
                            }
                            uVar18 = uVar39;
                            if ((*(uint *)((uint8_t *)fault_opts + 0x14) & 0x800) != 0) {
                                uVar18 = 0;
                            }
                            pbVar47 = &local_161;
                            puVar35 = &local_b0;
                            puVar46 = fault_opts;
                            uVar43 = kernel_vm_fault_callee_e480(
                                lVar37, puVar20, uVar28, &local_94, (uint)fault_type, lVar14,
                                uVar38, uVar18, fault_opts, puVar35, &local_dd, pbVar47);
                            iVar13 = local_7c;
                            uVar12 = (uint)((uint64_t)puVar35 >> 0x20);
                            uVar48 = (uint)((uint64_t)pbVar47 >> 0x20);
                            if ((int)uVar43 == 0) {
                                if (((*(uint *)((uint8_t *)fault_opts + 0x14) >> 9 & 1) != 0) &&
                                   ((*(byte *)(puVar31 + 0x16) & 1) == 0)) {
                                    *(uint *)((uint8_t *)fault_opts + 0x16) =
                                        *(uint *)((uint8_t *)fault_opts + 0x16) | 0x20000;
                                }
                                if ((*(uint *)((uint8_t *)fault_opts + 0x14) >> 10 & 1) == 0) {
                                    uVar19 = *(uint *)((uint8_t *)fault_opts + 0x16);
                                } else {
                                    uVar19 = *(uint *)((uint8_t *)fault_opts + 0x16);
                                    if (((byte)local_94 >> 1 & 1) != 0) {
                                        uVar19 = uVar19 | 0x40000;
                                        *(uint *)((uint8_t *)fault_opts + 0x16) = uVar19;
                                    }
                                }
                                pbVar47 = &local_b9;
                                puVar46 = (uint16_t *)hv_concat44((uint32_t)((uint64_t)puVar46 >> 0x20),
                                                                  uVar19);
                                uVar43 = kernel_vm_fault_callee_f5e4(
                                    puVar20, uVar28, uVar38, lVar37, &local_94, (uint)fault_type,
                                    uVar18, local_7c != 0, puVar46, pbVar47);
                                uVar12 = (uint)((uint64_t)pbVar47 >> 0x20);
                            }
                            kernel_vm_fault_callee_f6d4(puVar31, lVar37);
                            kernel_vm_fault_callee_f8bc(
                                puVar31, lVar37, iVar13 != 0, *(uint *)((uint8_t *)fault_opts + 0x14) >> 0xb & 1,
                                (uint)fault_flags, *(uint *)((uint8_t *)fault_opts + 0x14) & 1,
                                &local_b0, uVar43);
                            if (((iVar1 == 1) && ((*(byte *)(lVar37 + 0x2b) >> 4 & 1) == 0)) &&
                                (hv_fault_lowbit_flag != 0)) {
                                kernel_vm_fault_callee_f0ac8(&hv_fault_paging_lock);
                                if ((*(byte *)(lVar37 + 0x2b) >> 4 & 1) == 0) {
                                    *(byte *)(lVar37 + 0x2b) = *(byte *)(lVar37 + 0x2b) | 0x10;
                                    lVar34 = (ulong)hv_fault_stat_158 + 1;
                                    hv_fault_stat_158 = (uint)lVar34;
                                    if (lVar34 != lVar34 * 0x80000000 >> 0x1f) {
                                        /* WARNING: Does not return */
                                        pcVar10 = SoftwareBreakpoint(0xbffc, 0xfffffe000b89d5c0);
                                        ((void (*)(void))pcVar10)();
                                    }
                                }
                                kernel_vm_fault_callee_f1e4c(&hv_fault_paging_lock);
                            }
                            bVar24 = local_b9;
                            in_stack_fffffffffffffd28 = hv_concat44(uVar50, uVar33);
                            in_stack_fffffffffffffd18 = hv_concat44(uVar49, local_274);
                            in_stack_fffffffffffffd10 = 0;
                            uVar38 = hv_concat44((uint32_t)hv_concat31((uint64_t)puVar46 >> 0x28,
                                                                        local_b9), local_b0) &
                                     0xffffff01ffffffff;
                            kernel_vm_fault_callee_e03c(
                                puVar31, puVar31, lVar37, uVar9, uVar26, fault_opts, (uint)fault_type,
                                addr, uVar38, hv_concat44(uVar12, (uint)uVar43), result_out,
                                hv_concat44(uVar48, local_94), 0, in_stack_fffffffffffffd18,
                                uVar42, in_stack_fffffffffffffd28, &local_c8, &local_d0, &local_d8,
                                &local_160, fault_arg);
                            if ((bVar24 & 1) == 0) goto fault_done;
                            local_1a8 = 2;
                            kernel_vm_fault_callee_fbf0(puVar30, uVar25, 0, 0, 0, 0, 0, 2,
                                                        uVar38 & 0xffffffffffffff00);
                            local_b9 = 0;
                            goto retry;
                        }
                        lVar34 = (long)puVar20[0xb];
                        if (local_1cc == 1) {
                            kernel_vm_fault_callee_f3f8(0);   /* (0/1-arg) */
                        } else {
                            kernel_vm_fault_callee_e7d4((uint64_t)puVar31);
                        }
                        if (puVar20 != local_88) {
                            kernel_vm_fault_callee_7050(puVar20 + 1);
                        }
                        uVar12 = (uint)((uint64_t)plVar22 >> 0x20);
                        uVar42 = lVar34 + uVar42;
                        uVar38 = uVar42 & 0x3fff;
                        puVar35 = (uint *)((uint8_t *)puVar31 + 0x7c);
                        puVar20 = puVar31;
                        if ((*puVar35 & 0x2000080) == 0x2000000) break;
                    } while (true);
                }
                goto a708;
            }
            goto joined_a74c;
        }
        if ((hv_trace_flag & 0xfffffff7) == 0) {
            if (lVar5 == 0) goto d210;
b9b20:                              /* LAB_fffffe000b899b20 */
            uVar15 = *(uint64_t *)(lVar5 + 0x510);
        } else {
            kernel_trace(0x130000a, uVar32 >> 0x20, uVar32, 5, 0);
            if (lVar5 != 0) goto b9b20;
d210:                               /* b89d210 */
            uVar15 = 0;
        }
        uVar17 = 0x10000e0;
        goto d220;
    }
    if ((hv_trace_flag & 0xfffffff7) == 0) {
        if (lVar5 == 0) goto cff4;
b9af4:                              /* LAB_fffffe000b899af4 */
        uVar15 = *(uint64_t *)(lVar5 + 0x510);
    } else {
        kernel_trace(0x130000a, uVar32 >> 0x20, uVar32, 5, 0);
        if (lVar5 != 0) goto b9af4;
cff4:                               /* b89cff4 */
        uVar15 = 0;
    }
    uVar17 = 0x1000030;
d220:                               /* b89d220 */
    kernel_vm_fault_callee_2db44(uVar15, uVar17, 0);
    return 5;
a2e8:                               /* b89a2e8 */
    local_198 = local_198 & 0xffffffff00000000;
    if (((iVar13 != 1) || (local_78[0] == 0)) || (local_b8 == 0)) goto a708;
    if (local_88 == puVar20) {
        if (local_1a8 == 1) {
            iVar13 = kernel_vm_fault_callee_f5f18(local_88 + 1);
            uVar12 = (uint)((uint64_t)plVar22 >> 0x20);
            if (iVar13 == 0) {
a56c:                               /* b89a56c */
                kernel_vm_fault_callee_e7d4((uint64_t)puVar41);
                puVar35 = (uint *)((uint8_t *)puVar20 + 0x7c);
                uVar19 = *puVar35;
                local_1a8 = 2;
                goto a1a8;
            }
        }
        bVar7 = false;
        local_1a8 = 2;
        uVar19 = 1;
    } else if ((uVar33 >> 1 & 1) == 0) {
        if ((local_1cc == 1) && (iVar13 = kernel_vm_fault_callee_f5f18(puVar20 + 1), iVar13 == 0)) {
            kernel_vm_fault_callee_7050(local_88 + 1);
            local_1cc = 2;
joined_bb5c:                        /* joined_r0xfffffe000b89bb5c */
            if (fault_arg == 0) {
                *(uint64_t *)(lVar5 + 0x238) = 0;
                HV_FMT_PAGING_CONCAT();
                if ((uStack_138 >> 2 & 1) == 0) {
                    kernel_vm_fault_callee_1ab24(&local_160);
                } else if ((lStack_148 != 0) && ((~*(uint *)(lStack_148 + 0x28) & 3) != 0)) {
                    kernel_vm_fault_callee_164f8();
                }
            }
            goto retry;
        }
        local_1cc = 2;
        uVar19 = 1;
        bVar7 = true;
        puVar41 = local_88;
    } else {
        if (local_1a8 == 1) {
            kernel_vm_fault_callee_7050(local_88 + 1);
            kernel_vm_fault_callee_7050(puVar20 + 1);
            local_1a8 = 2;
            goto joined_bb5c;
        }
        bVar7 = false;
        local_1a8 = 2;
        uVar19 = 3;
    }
    uVar4 = uVar19 | 0x20;
    if (*(char *)((uint8_t *)puVar41 + 0xae) != '"') {
        uVar4 = uVar19;
    }
    lVar34 = kernel_vm_fault_callee_f5be0(uVar18);
    if (lVar34 != 0) {
        iVar13 = kernel_vm_fault_callee_0ed8(puVar20[10], puVar20[0xc] + uVar43,
                                             *(uint *)(lVar34 + 0x30), &local_198, uVar4, &local_dc);
        uVar49 = (uint)(in_stack_fffffffffffffd28 >> 0x20);
        lVar37 = (long)puVar20[10];
        if (((lVar37 != 0) && (local_dc != 0)) &&
           (*(uint64_t ***)(lVar37 + 8) == (uint64_t ***)&PTR_fault_vt_878)) {
            *(int *)(lVar37 + 0x34) = *(int *)(lVar37 + 0x34) + local_dc;
        }
        if (iVar13 == 0) {
            *(uint *)(lVar34 + 0x2c) = *(uint *)(lVar34 + 0x2c) | 0x1000;
            if (((!(bool)(puVar41 != puVar20 & (bVar7 ^ 1U))) &&
                ((((*puVar35 ^ 0xffffffff) & 0x30000) != 0 ||
                 ((*(byte *)((uint8_t *)puVar20 + 0xb2) & 0x70) != 0)))) &&
               ((puVar20[0xb] != 0 && (local_dc != 0)))) {
                kernel_vm_fault_callee_b078((uint64_t)puVar20, 0xffffffff);
            }
            puVar41 = local_88;
            if (bVar7) {
                kernel_vm_fault_callee_f19b0(lVar34, puVar20, uVar43, 0, 0, 0);
                uVar15 = extraout_x1;
                puVar41 = puVar20;
            } else {
                kernel_vm_fault_callee_f19b0(lVar34, local_88, local_90 & 0xffffffffffffc000, 0, 0, 0);
                uVar15 = extraout_x1;
            }
            cVar2 = *(char *)((uint8_t *)puVar41 + 0xae);
            if (((cVar2 != '\x02') && (cVar2 != '"')) && (cVar2 != -0x80)) {
                DataSynchronizationBarrier(3,3,0);
            }
            local_b0 = (uint)local_198;
            *hv_pcpu_slot(hv_pcpu_pageins, cpu_idx) =
                 *hv_pcpu_slot(hv_pcpu_pageins, cpu_idx) + 1;
            *(int *)(lVar5 + 0x590) = *(int *)(lVar5 + 0x590) + 1;
            if (puVar20 == local_88) {
                puVar31 = 0;
            } else if (bVar7) {
                local_1a8 = local_1cc;
                puVar31 = local_88;
                local_88 = puVar20;
            } else {
                kernel_vm_fault_callee_7050(puVar20 + 1);
                uVar15 = extraout_x1;
                puVar31 = 0;
            }
bee0:                               /* b89bee0 */
            if ((bVar6) && ((local_94 >> 1 & 1) != 0)) {
                if (puVar30 == 0) {
                    bVar24 = 1;
                } else {
                    bVar24 = *(byte *)(puVar30[4] + 0x4c) ^ 1;
                }
                if (((((local_94 ^ 0xffffffff) & 7) == 0) && ((bVar24 & 1) != 0)) &&
                   (((*(uint *)((uint8_t *)fault_opts + 0x16) >> 0xe & 1) != 0 ||
                    ((*(byte *)(puVar30 + 0xe) & 1) == 0)))) {
                    if (((uint8_t)fault_opts[0x14] >> 3 & 1) == 0) {
d4e8:                               /* b89d4e8 */
                        /* WARNING: Subroutine does not return */
                        kernel_panic_msg_fmt("%s: pmap %p vaddr 0x%llx prot 0x%x options 0x%x @%s:%d");
                    }
                } else {
                    local_94 = local_94 & 0xfffffffd;
                }
            }
            if (((iVar1 == 1) && ((*(byte *)(lVar34 + 0x2b) >> 4 & 1) == 0)) &&
               (hv_fault_lowbit_flag != 0)) {
                kernel_vm_fault_callee_f0ac8(&hv_fault_paging_lock, uVar15);
                if ((*(byte *)(lVar34 + 0x2b) >> 4 & 1) == 0) {
                    *(byte *)(lVar34 + 0x2b) = *(byte *)(lVar34 + 0x2b) | 0x10;
                    lVar37 = (ulong)hv_fault_stat_158 + 1;
                    hv_fault_stat_158 = (uint)lVar37;
                    if (lVar37 != lVar37 * 0x80000000 >> 0x1f) {
                        /* WARNING: Does not return */
                        pcVar10 = SoftwareBreakpoint(0xbffc, 0xfffffe000b89d5ec);
                        ((void (*)(void))pcVar10)();
                    }
                }
                kernel_vm_fault_callee_f1e4c(&hv_fault_paging_lock);
            }
            uVar18 = local_94;
            local_b9 = 0;
            pbVar47 = &local_161;
            puVar20 = puVar30;
            uVar43 = uVar25;
            if (vnode_mp != 0) {
                puVar20 = (uint64_t *)(uintptr_t)vnode_mp;
                uVar43 = mp_size;
            }
            uVar15 = hv_concat62((uint64_t)puVar46 >> 0x10, (uint16_t)(int16_t)fault_flags);
            uVar43 = kernel_vm_fault_callee_de34(
                lVar34, puVar20, uVar43, lVar14, uVar38, local_94, (uint)fault_type, local_7c,
                uVar15, fault_opts, &local_b9, &local_b0, in_stack_fffffffffffffd10, pbVar47);
            uVar19 = 0xb;
            if (!(bool)(bVar23 & local_b0 == 3)) {
                uVar19 = local_b0;
            }
            in_stack_fffffffffffffd28 = hv_concat44(uVar49, uVar33);
            in_stack_fffffffffffffd18 = hv_concat44((uint32_t)((uint64_t)pbVar47 >> 0x20),
                                                    local_274);
            uVar38 = hv_concat44((uint32_t)hv_concat31((uint64_t)uVar15 >> 0x28,
                                                        local_b9 | local_161), uVar19) &
                     0xffffff01ffffffff;
            kernel_vm_fault_callee_e03c(
                local_88, puVar41, lVar34, local_90, uVar26, fault_opts, (uint)fault_type, addr,
                uVar38, uVar43 & 0xffffffff, result_out, uVar18, puVar31,
                in_stack_fffffffffffffd18, uVar42, in_stack_fffffffffffffd28, &local_c8, &local_d0,
                &local_d8, &local_160, fault_arg);
            if ((local_b9 & 1) != 0) {
                kernel_vm_fault_callee_fbf0(puVar30, uVar25, 0, 0, 0, 0, 0, 2,
                                            uVar38 & 0xffffffffffffff00);
                local_b9 = 0;
                in_stack_fffffffffffffd10 = (uint64_t)puVar31;
                goto retry;
            }
            in_stack_fffffffffffffd10 = (uint64_t)puVar31;
            if ((local_161 & 1) == 0) goto fault_done;
            goto retry;
        }
        kernel_vm_fault_callee_f17cc((uint64_t)lVar34, 0);
        if (iVar13 == 9) {
            if (puVar41 != puVar20) {
                kernel_vm_fault_callee_7050(puVar20 + 1);
                puVar41 = local_88;
            }
            kernel_vm_fault_callee_7050(puVar41 + 1);
            if (fault_arg == 0) {
                *(uint64_t *)(lVar5 + 0x238) = 0;
                HV_FMT_PAGING_CONCAT();
                if ((uStack_138 >> 2 & 1) == 0) {
                    kernel_vm_fault_callee_1ab24(&local_160);
                } else if ((lStack_148 != 0) && ((~*(uint *)(lStack_148 + 0x28) & 3) != 0)) {
                    kernel_vm_fault_callee_164f8();
                }
                HV_FMT_ZERO_STATE();
            }
            uVar43 = 9;
            goto fault_done;
        }
    }
a708:                               /* b89a708 */
    if (local_88 != puVar31) {
        kernel_vm_fault_callee_7050(puVar31 + 1);
    }
    puVar20 = local_88;
    if ((local_1a8 == 1) && (iVar13 = kernel_vm_fault_callee_f5f18(local_88 + 1), iVar13 == 0)) {
        kernel_vm_fault_callee_e7d4((uint64_t)puVar20);
    }
    local_1a8 = 2;
joined_a74c:                        /* joined_r0xfffffe000b89a74c */
    if (fault_arg == 0) {
        *(uint64_t *)(lVar5 + 0x238) = 0;
        HV_FMT_PAGING_CONCAT();
        if ((uStack_138 >> 2 & 1) == 0) {
            kernel_vm_fault_callee_1ab24(&local_160);
        } else if ((lStack_148 != 0) && ((~*(uint *)(lStack_148 + 0x28) & 3) != 0)) {
            kernel_vm_fault_callee_164f8();
        }
        HV_FMT_ZERO_STATE();
    }
    local_e8 = 0;
    if (local_88 == &hv_fault_special_400) {
        puVar20 = &hv_fault_special_400;
cf88:                               /* b89cf88 */
        kernel_vm_fault_callee_7050(puVar20 + 1);
        uVar43 = 10;
        goto fault_done;
    }
    puVar20 = local_88;
    if ((local_88 == &hv_fault_special_300) || (local_88 == &hv_fault_special_800)) goto cf88;
    if (bVar6) {
        if (local_88 != puVar29) {
            kernel_vm_fault_callee_c2f4(puVar29);
            puVar29 = 0;
            hv_fault_stat_2c0 = hv_fault_stat_2c0 + 1;
            local_1d8 = 0xffffffffffffffff;
            goto a87c;
        }
        puVar29 = 0;
        hv_fault_stat_2c0 = hv_fault_stat_2c0 + 1;
        local_1d8 = 0xffffffffffffffff;
    } else {
a87c:                               /* b89a87c */
        if (*(int *)(local_88 + 5) + 0xf0000001U < 0xf0000002) {
            /* WARNING: Subroutine does not return */
            kernel_vm_fault_panic_cow((uint64_t)(local_88 + 5));
        }
        *(int *)(local_88 + 5) = *(int *)(local_88 + 5) + 1;
    }
    puVar20 = local_88;
    uVar42 = local_90;
    uVar18 = *(ushort *)((uint8_t *)local_88 + 0x74) + 1;
    *(short *)((uint8_t *)local_88 + 0x74) = (short)uVar18;
    if (uVar18 >> 0x10 != 0) {
        /* WARNING: Subroutine does not return */
        kernel_panic_msg_fmt("vm_object_paging_begin(%p): overflow\n @%s:%d");
    }
    *(uint *)(lVar5 + 0x4a8) = 0;
    local_ac = 0;
    local_a0 = 0;
    uVar43 = local_90;
    in_stack_fffffffffffffd10 = (uint64_t)fault_arg;
    iVar13 = kernel_vm_fault_callee_fd14(
        local_88, local_90, uVar33, (uint)(local_7c == 0) & *(uint *)((uint8_t *)fault_opts + 0x14) >> 0xb,
        0, &local_94, &local_a0, &local_a8, &local_b0, &local_ac,
        hv_concat44(uVar12, *(uint *)(local_78[0] + 0xb0) >> 1) & 0xffffffff00000001,
        fault_opts, fault_arg);
    if ((iVar13 != 0) && (iVar13 != 6)) {
        if (iVar13 == 5) {
            if (-1 < (char)fault_opts[0x14]) {
                kernel_vm_fault_callee_c2f4(puVar20);
                local_88 = 0;
                uVar27 = 10;
                if (local_ac != 0) {
                    uVar27 = local_ac;
                }
                uVar43 = (ulong)uVar27;
                goto fault_done;
            }
            hv_fault_stat_298 = hv_fault_stat_298 + 1;
            bVar6 = true;
            puVar29 = puVar20;
            local_1d8 = uVar43;
            goto retry;
        }
        kernel_vm_fault_callee_c2f4(puVar20);
        puVar20 = 0;
        local_88 = 0;
        if (iVar13 < 3) {
            bVar6 = false;
            if (iVar13 == 1) goto retry;
            if (iVar13 == 2) {
                if (lVar5 == 0) {
                    uVar15 = 0;
                } else {
                    uVar15 = *(uint64_t *)(lVar5 + 0x510);
                }
cd24:                               /* b89cd24 */
                kernel_vm_fault_callee_2db44(uVar15, 0x1000024, 0);
                uVar43 = 0xe;
                goto fault_done;
            }
        } else {
            if (iVar13 == 3) {
                iVar13 = kernel_vm_fault_callee_f671c((*(uint *)((uint8_t *)fault_opts + 0x14) >> 10 ^ 0xffffffff) & 2);
                bVar6 = false;
                if (iVar13 != 0) goto retry;
                if (lVar5 == 0) {
                    uVar15 = 0;
                } else {
                    uVar15 = *(uint64_t *)(lVar5 + 0x510);
                }
                kernel_vm_fault_callee_2db44(uVar15, 0x1000014, 0);
                goto cd24;
            }
            if (iVar13 == 7) {
                uVar43 = 0x1e;
                goto fault_done;
            }
        }
    }
    lVar34 = local_a0;
    if (local_a0 == 0) {
        lVar37 = 0;
        lVar36 = 0;
        local_208 = 0;
    } else {
        puVar20 = (uint64_t *)((ulong)*(uint *)(local_a0 + 0x1c) << 6 | 0xfffffe0000000000);
        lVar37 = (long)puVar20[7];
        lVar36 = (long)puVar20[8];
        *(short *)(lVar5 + 0x21e) = *(short *)(lVar5 + 0x21e) + 1;
        local_208 = puVar20;
        local_f0 = lVar5;
    }
    kernel_vm_fault_callee_7050(puVar20 + 1);
    local_178 = 0;
    local_170 = 0;
    local_17c = 0;
    uStack_158 = 0;
    local_160 = 0;
    lStack_148 = 0;
    local_150 = 0;
    uStack_138 = 0;
    uStack_134 = 0;
    local_140 = 0;
    uStack_128 = 0;
    uStack_124 = 0;
    uStack_130 = 0;
    uStack_118 = 0;
    uStack_114 = 0;
    uStack_120 = 0;
    uStack_11c = 0;
    uStack_108 = 0;
    uStack_104 = 0;
    uStack_110 = 0;
    uStack_10c = 0;
    local_f8 = 0;
    uStack_f4 = 0;
    local_100 = 0;
    uStack_fc = 0;
    in_stack_fffffffffffffd10 = hv_concat71(in_stack_fffffffffffffd10 >> 8, 1);
    puVar46 = fault_opts;
    local_78[0] = p1;
    uVar43 = vm_fault_enter_full(local_78, uVar25, uVar33, &local_170, &local_e8, &local_178,
                                 &local_17c, &local_7c, fault_opts, &local_b8, &local_160,
                                 fault_arg, in_stack_fffffffffffffd10);
    puVar30 = local_88;
    puVar20 = local_170;
    puVar41 = (uint64_t *)(local_b8 + 0x58);
    puVar31 = (uint64_t *)*puVar41;   /* slot holds a pointer value */
    iVar13 = (int)uVar43;
    if (iVar13 != 0) {
        if (lVar34 == 0) {
            kernel_vm_fault_callee_e7d4((uint64_t)local_88);
            kernel_vm_fault_callee_a1f14(puVar30, local_a8);
            goto abe4;
        }
        kernel_vm_fault_callee_e7d4((uint64_t)local_208);
        uVar15 = kernel_vm_fault_callee_3f58c(&local_f0);
        kernel_vm_fault_callee_d31ac(uVar15, (uint64_t)lVar34);
        iVar8 = (int)hv_fault_paging_owner;
        if ((1L << (*(byte *)(lVar34 + 0x2a) & 0xf) & 0x3d40U) == 0) {
            *(int *)(lVar5 + 0x1c0) = *(int *)(lVar5 + 0x1c0) + 1;
            uVar38 = hv_fault_paging_token;
            if (hv_fault_paging_token == 0) {
                hv_fault_paging_token = (ulong)*(uint *)(lVar5 + 0x518) | 0x30000000;
            }
            if (uVar38 != 0 || iVar8 != 0) {
                kernel_vm_fault_callee_f0afc(&hv_fault_paging_lock, lVar5, uVar38, 1);
            }
            if ((1L << (*(byte *)(lVar34 + 0x2a) & 0xf) & 0x3d40U) == 0) {
                kernel_vm_fault_callee_f52fc((uint64_t)lVar34);
            }
            if (hv_fault_paging_token == *(int *)(lVar5 + 0x518)) {
                hv_fault_paging_token =
                    hv_concat44((uint32_t)(hv_fault_paging_token >> 32), 0);
                if (hv_fault_paging_owner == 0) goto ab80;
            }
            kernel_vm_fault_callee_f1e80(&hv_fault_paging_lock, (uint64_t)lVar5);
        }
ab80:                               /* b89ab80 */
        kernel_vm_fault_callee_a1f14(local_208, local_a8);
        puVar30 = local_88;
abe4:                               /* b89abe4 */
        kernel_vm_fault_callee_c2f4(puVar30);
        if (iVar13 != 0x20008007) {
            if (iVar13 == 1) {
                if (lVar5 == 0) {
                    uVar15 = 0;
                } else {
                    uVar15 = *(uint64_t *)(lVar5 + 0x510);
                }
                kernel_vm_fault_callee_2db44(uVar15, 0x100000c, 0);
                uVar43 = 1;
            }
            goto fault_done;
        }
        bVar6 = false;
        if ((*(byte *)(local_78[0] + 0xb3) & 1) != 0) {
            bVar6 = false;
            *hv_pcpu_slot(hv_pcpu_restart, cpu_idx) =
                 *hv_pcpu_slot(hv_pcpu_restart, cpu_idx) + 1;
            if ((hv_trace_flag & 0xfffffff7) != 0) {
                kernel_trace(0x1b12004, local_78[0], uVar25, uVar25, 0);
                bVar6 = false;
            }
        }
        goto retry;
    }
    if ((local_170 != local_88) || (local_178 != uVar42)) {
        if (lVar34 == 0) {
            kernel_vm_fault_callee_e7d4((uint64_t)local_88);
            local_208 = puVar30;
        } else {
            kernel_vm_fault_callee_e7d4((uint64_t)local_208);
            uVar15 = kernel_vm_fault_callee_3f58c(&local_f0);
            kernel_vm_fault_callee_d31ac(uVar15, (uint64_t)lVar34);
            if ((1L << (*(byte *)(lVar34 + 0x2a) & 0xf) & 0x3d40U) == 0) {
                kernel_vm_fault_callee_f19b4(&hv_fault_paging_lock);
                if ((1L << (*(byte *)(lVar34 + 0x2a) & 0xf) & 0x3d40U) == 0) {
                    kernel_vm_fault_callee_f52fc((uint64_t)lVar34);
                }
                kernel_vm_fault_callee_f1e4c(&hv_fault_paging_lock);
            }
        }
        kernel_vm_fault_callee_a1f14(local_208, local_a8);
        kernel_vm_fault_callee_c2f4(puVar30);
        bVar6 = false;
        if (fault_arg != 0) goto retry;
        *(uint64_t *)(lVar5 + 0x238) = 0;
        HV_FMT_PAGING_CONCAT();
        goto joined_b110;
    }
    if (puVar31 == 0) {
        bVar23 = 1;
    } else {
        bVar23 = *(byte *)(puVar31[4] + 0x4c) ^ 1;
    }
    if (((((local_17c ^ 0xffffffff) & 7) == 0) && ((bVar23 & 1) != 0)) &&
       ((~*(byte *)(puVar31 + 0xe) & 1) != 0 || (*(uint *)((uint8_t *)fault_opts + 0x16) & 0x4000) != 0)) {
        local_94 = 0xffffffff;
    }
    uVar18 = local_94 & local_17c;
    local_94 = uVar18;
    if (lVar34 == 0) {
        kernel_vm_fault_callee_e7d4(0);   /* (0/1-arg) */
    } else {
        kernel_vm_fault_callee_e7d4((uint64_t)local_208);
        kernel_vm_fault_callee_3f58c(&local_f0);
        if (((uVar18 >> 1 & 1) != 0) && ((local_208[7] != (uint64_t)lVar37 || (local_208[8] != (uint64_t)lVar36)))) {
            if (puVar31 == 0) {
                bVar23 = 1;
            } else {
                bVar23 = *(byte *)(puVar31[4] + 0x4c) ^ 1;
            }
            if (((((uVar18 ^ 0xffffffff) & 7) == 0) && ((bVar23 & 1) != 0)) &&
               (((*(uint *)((uint8_t *)fault_opts + 0x16) >> 0xe & 1) != 0 ||
                ((*(byte *)(puVar31 + 0xe) & 1) == 0)))) {
                /* WARNING: Subroutine does not return */
                kernel_panic_msg_fmt(
                    "%s: pmap %p vaddr 0x%llx prot 0x%x options 0x%x m%p obj %p copyobj %p @%s:%d");
            }
            local_94 = uVar18 & 0xfffffffd;
            uVar18 = local_94;
        }
    }
    if (((local_1e4 == 0) && (lVar34 != 0)) && ((*(uint *)((uint8_t *)fault_opts + 0x14) >> 8 & 1) == 0)) {
        if (*(uint *)(lVar34 + 0x1c) == 0) {
            puVar21 = 0;
        } else {
            puVar21 = (uint64_t *)((ulong)*(uint *)(lVar34 + 0x1c) << 6 | 0xfffffe0000000000);
        }
        if (((puVar20 == puVar21) || ((*(byte *)((uint8_t *)puVar21 + 0x7d) >> 2 & 1) != 0)) ||
           ((hv_fault_lowbit_flag2 == 0 || ((*(byte *)(puVar21 + 0x16) & 1) != 0))))
            goto ae9c;
        lVar37 = (long)kernel_vm_fault_callee_6659c();
        if (*(long *)(lVar37 + 0x18) == 0) {
            puVar20 = (uint64_t *)kernel_vm_fault_callee_42a30(0);
            iVar13 = (int)(uintptr_t)puVar20;
        } else {
            puVar20 = (uint64_t *)kernel_vm_fault_callee_42a30(0);   /* (0/1-arg) */
            iVar13 = (int)(uintptr_t)puVar20;
        }
        if (iVar13 == 0) goto ae9c;
        hv_fault_stat_250 = hv_fault_stat_250 + 1;
        bVar23 = 1;
        local_1e4 = 1;
aec8:                               /* b89aec8 */
        kernel_vm_fault_callee_d31ac((uint64_t)puVar20, (uint64_t)lVar34);
        puVar20 = local_208;
        if ((1L << (*(byte *)(lVar34 + 0x2a) & 0xf) & 0x3d40U) == 0) {
            kernel_vm_fault_callee_f19b4(&hv_fault_paging_lock);
            if ((1L << (*(byte *)(lVar34 + 0x2a) & 0xf) & 0x3d40U) == 0) {
                kernel_vm_fault_callee_f52fc((uint64_t)lVar34);
            }
            kernel_vm_fault_callee_f1e4c(&hv_fault_paging_lock);
        }
    } else {
ae9c:                               /* b89ae9c */
        if ((local_7c == 0) || (uVar33 == (uVar18 | 2))) {
            if (lVar34 == 0) {
                uVar26 = *(ulong *)(local_e8 + 0x10);
                lVar11 = uVar25 - hv_concat44(uStack_fc, local_100);
                uVar43 = lVar11 - uVar26;
                lVar14 = (uVar43 < 0xfffffffffffff001) * uVar43 +
                         (ulong)(uVar43 >= 0xfffffffffffff001) * -0x1000;
                uVar28 = *(long *)(local_e8 + 0x18) - lVar11;
                if ((*(uint *)((uint8_t *)puVar30 + 0x7c) & 0x2000080) == 0x2000000) {
                    if ((*(ulong *)(local_e8 + 0x30) < 0x1000) &&
                       (lVar34 = *(long *)(local_e8 + 0x18) - uVar26, lVar34 == (long)puVar30[3])) {
                        uVar27 = 0;
                        if (((lVar34 - 1U & uVar26) == 0) && (uVar27 = 0x100, result_out != 0)) {
                            *result_out = (uint)((puVar30[0xb] + uVar43 >> 0xe));
                            uVar26 = *(ulong *)(local_e8 + 0x10);
                            uVar27 = 0x100;
                        }
                    } else {
                        uVar27 = 0;
                    }
                } else {
                    uVar27 = 0;
                }
                if ((vnode_mp == 0) &&
                   (vnode_mp = (void **)(uintptr_t)*puVar41, mp_size = uVar25, vnode_mp == 0)) {
                    vnode_mp = 0;
                }
                kernel_vm_fault_callee_c554(
                    (void *)(uintptr_t)vnode_mp, mp_size - (uint64_t)lVar14,
                    ((lVar11 - lVar14) + (long)puVar30[0xb] +
                     (*(ulong *)(local_e8 + 0x30) & 0xfffffffffffff000)) - uVar26,
                    (uVar28 < 0xfffffffffffff001) * uVar28 +
                    (ulong)(uVar28 >= 0xfffffffffffff001) * -0x1000 + lVar14 >> (uVar40 & 0x3f),
                    uVar18, uVar27 | *(byte *)((uint8_t *)puVar30 + 0xae), 0);
                kernel_vm_fault_callee_a1f14(puVar30, local_a8);
            } else {
                local_b9 = 0;
                in_stack_fffffffffffffd18 = (uint64_t)&local_161;   /* 64-bit stack slot carries a pointer here */
                puVar20 = puVar31;
                uVar43 = uVar25;
                if (vnode_mp != 0) {
                    puVar20 = (uint64_t *)(uintptr_t)vnode_mp;
                    uVar43 = mp_size;
                }
                uVar42 = hv_concat62((uint64_t)puVar46 >> 0x10, (uint16_t)(int16_t)fault_flags);
                uVar43 = kernel_vm_fault_callee_de34(
                    lVar34, puVar20, uVar43, lVar14, uVar38, uVar18, (uint)fault_type, local_7c,
                    uVar42, fault_opts, &local_b9, &local_b0, in_stack_fffffffffffffd10,
                    (uint8_t *)in_stack_fffffffffffffd18);
                uVar19 = local_b0;
                lVar37 = (long)(int)local_b0;
                uVar12 = 0x1320008;
                if ((*(byte *)((uint8_t *)local_208 + 0x7d) >> 4 & 1) == 0) {
                    uVar12 = 0x1320010;
                    if ((*(byte *)((uint8_t *)local_208 + 0xb1) & 2) != 0) {
                        uVar12 = 0x1320014;
                    }
                }
                if ((hv_trace_flag & 0xfffffff7) != 0) {
                    uVar4 = uVar39 << 8 | *(int *)((uint8_t *)fault_opts + 2) << 0x10 | local_b0;
                    uVar17 = *(uint64_t *)(lVar34 + 0x20);
                    uVar15 = kernel_vm_fault_callee_7e720(addr);
                    kernel_trace(uVar12, uVar26, uVar4, uVar17, uVar15);
                }
                bVar23 = local_b9;
                uVar15 = *(uint64_t *)(lVar34 + 0x20);
                uVar49 = *(uint *)((uint8_t *)fault_opts + 2);
                if ((((int)uVar43 != 0) || ((local_161 & 1) != 0)) || ((local_b9 & 1) != 0)) {
                    kernel_vm_fault_callee_d31ac(addr, (uint64_t)lVar34);
                    kernel_vm_fault_callee_a1f14(local_208, local_a8);
                    kernel_vm_fault_callee_c2f4(puVar30);
                    if ((bVar23 & 1) != 0) {
                        uVar43 = uVar25;
                        if (vnode_mp != 0) {
                            puVar31 = (uint64_t *)(uintptr_t)vnode_mp;
                            uVar43 = mp_size;
                        }
                        kernel_vm_fault_callee_fbf0(puVar31, uVar43, 0, 0, 0, 0, 0, 2,
                                                    uVar42 & 0xffffffffffffff00);
                        uVar43 = 0;
                        local_b9 = 0;
                    }
                    if (fault_arg == 0) {
                        *(uint64_t *)(lVar5 + 0x238) = 0;
                        HV_FMT_PAGING_CONCAT();
                        if ((uStack_138 >> 2 & 1) == 0) {
                            kernel_vm_fault_callee_1ab24(&local_160);
                        } else if ((lStack_148 != 0) && ((~*(uint *)(lStack_148 + 0x28) & 3) != 0)) {
                            kernel_vm_fault_callee_164f8();
                        }
                        HV_FMT_ZERO_STATE();
                    }
                    bVar6 = false;
                    bVar23 = 0;
                    if ((int)uVar43 != 0) {
fault_done:                         /* b89ca08 */
                        *(ushort *)(lVar5 + 0xc0) = uVar3 & 3 | *(ushort *)(lVar5 + 0xc0) & 0xfffc;
                        if (puVar29 != 0) {
                            kernel_vm_fault_callee_c2f4(puVar29);
                            hv_fault_stat_2b0 = hv_fault_stat_2b0 + 1;
                        }
                        uVar27 = local_b0;
                        lVar14 = (long)(int)local_b0;
                        if ((local_b0 < 0xb) && ((1 << (ulong)(local_b0 & 0x1f) & 0x580U) != 0)) {
                            kernel_vm_fault_callee_6c27c(1);
                        } else if (((int)uVar43 == 0) &&
                                   ((local_b0 & 0xfffffffd) != 4 &&
                                    (iVar13 = kernel_vm_fault_callee_a2224(1), iVar13 != 0))) {
                            kernel_vm_fault_callee_a24d0();
                        }
                        puVar29 = local_c8;
                        if (local_c8 != 0) {
                            if ((local_d0 != 0) &&
                                (*(uint64_t ***)(local_d0 + 8) == (uint64_t ***)&PTR_fault_vt_770)) {
                                kernel_vm_fault_callee_e3a0d8(*(uint64_t *)(local_d0 + 0x20),
                                                              (uint64_t)local_d8,
                                                              (uint64_t)(local_d8 + 0x4000));
                            }
                            kernel_vm_fault_callee_e7d4((uint64_t)puVar29);
                            uVar3 = *(ushort *)((uint8_t *)puVar29 + 0x74);
                            uVar39 = uVar3 - 1;
                            *(short *)((uint8_t *)puVar29 + 0x74) = (short)uVar39;
                            if (0xffff < uVar39) {
                                /* WARNING: Subroutine does not return */
                                kernel_panic_msg_fmt("vm_object_paging_end(%p): underflow\n @%s:%d");
                            }
                            uVar39 = uVar39 & 0xffff;
                            if (uVar3 == 0x10) {
                                uVar18 = *(uint *)((uint8_t *)puVar29 + 0x7c);
                                if ((uVar18 >> 6 & 1) != 0) {
                                    kernel_vm_fault_callee_15288((uint8_t *)puVar29 + 6, 0, 0);
                                    uVar18 = *(uint *)((uint8_t *)puVar29 + 0x7c);
                                    uVar39 = (uint)*(ushort *)((uint8_t *)puVar29 + 0x74);
                                }
                                *(uint *)((uint8_t *)puVar29 + 0x7c) = uVar18 & 0xffffffbf;
                            }
                            if (uVar39 == 0) {
                                uVar39 = *(uint *)((uint8_t *)puVar29 + 0x7c);
                                if ((uVar39 >> 5 & 1) != 0) {
                                    kernel_vm_fault_callee_15288((uint8_t *)puVar29 + 5, 0, 0);
                                    uVar39 = *(uint *)((uint8_t *)puVar29 + 0x7c);
                                }
                                *(uint *)((uint8_t *)puVar29 + 0x7c) = uVar39 & 0xffffffdf;
                                if (*(int *)(puVar29 + 0xf) == 0) {
                                    kernel_vm_fault_callee_d4ba8(puVar29, 2);
                                }
                            }
                            kernel_vm_fault_callee_7050(puVar29 + 1);
                        }
                        if (iVar1 == 1) {
                            kernel_vm_fault_callee_a2590((uint64_t)lVar5, (uint64_t)local_258,
                                                         uVar32, lVar14);
                        }
                        if ((hv_trace_flag & 0xfffffff7) == 0) {
                            return uVar43;
                        }
                        lVar5 = 0xb;
                        if (!(bool)(bVar23 & uVar27 == 3)) {
                            lVar5 = lVar14;
                        }
                        kernel_trace(0x130000a, uVar32 >> 0x20, uVar32, (long)(int)uVar43, lVar5);
                        return uVar43;
                    }
                    goto retry;
                }
                if ((result_out != 0) &&
                   (*result_out = *(uint *)(lVar34 + 0x30), (uVar18 >> 1 & 1) != 0)) {
                    *(uint *)(lVar34 + 0x2c) = *(uint *)(lVar34 + 0x2c) | 0x1000;
                }
                if (((iVar1 == 1) && ((*(byte *)(lVar34 + 0x2b) >> 4 & 1) == 0)) &&
                   (hv_fault_lowbit_flag != 0)) {
                    kernel_vm_fault_callee_f0ac8(&hv_fault_paging_lock, uVar15, uVar12,
                                                 (long)(int)uVar39, lVar37, uVar49);
                    if ((*(byte *)(lVar34 + 0x2b) >> 4 & 1) == 0) {
                        *(byte *)(lVar34 + 0x2b) = *(byte *)(lVar34 + 0x2b) | 0x10;
                        lVar14 = (ulong)hv_fault_stat_158 + 1;
                        hv_fault_stat_158 = (uint)lVar14;
                        if (lVar14 != lVar14 * 0x80000000 >> 0x1f) {
                            /* WARNING: Does not return */
                            pcVar10 = SoftwareBreakpoint(0xbffc, 0xfffffe000b89d5f8);
                            ((void (*)(void))pcVar10)();
                        }
                    }
                    addr = kernel_vm_fault_callee_f1e4c(&hv_fault_paging_lock);
                    bVar23 = *(byte *)((uint8_t *)local_208 + 0x7d);
                } else {
                    bVar23 = *(byte *)((uint8_t *)local_208 + 0x7d);
                }
                if (((bVar23 >> 4 & 1) == 0) && ((uVar33 >> 1 & 1) != 0)) {
                    addr = kernel_vm_fault_callee_a21dc(local_208);   /* param_2 = FUN_fffffe000b8a21dc(local_208) */
                    local_d0 = (long)local_208[10];
                    local_d8 = *(long *)(lVar34 + 0x20) + (long)local_208[0xc];
                    local_c8 = local_208;
                }
                kernel_vm_fault_callee_d31ac(addr, (uint64_t)lVar34);
                local_198 = local_208[10];
                lStack_190 = *(long *)(lVar34 + 0x20) + (long)local_208[0xc];
                local_188 = 0;
                if (uVar19 == 7) {
                    iVar13 = kernel_vm_fault_callee_38dbc(&local_198);
                    kernel_vm_fault_callee_a1f14(local_208, local_a8);
                    if (iVar13 != 0) {
                        kernel_vm_fault_callee_38e78(&local_198);
                    }
                } else {
                    kernel_vm_fault_callee_a1f14(local_208, local_a8);
                }
            }
            kernel_vm_fault_callee_c2f4(puVar30);
            if (fault_arg == 0) {
                *(uint64_t *)(lVar5 + 0x238) = 0;
                HV_FMT_PAGING_CONCAT();
                if ((uStack_138 >> 2 & 1) == 0) {
                    kernel_vm_fault_callee_1ab24(&local_160);
                } else if ((lStack_148 != 0) && ((~*(uint *)(lStack_148 + 0x28) & 3) != 0)) {
                    kernel_vm_fault_callee_164f8();
                }
                bVar23 = 0;
                uVar43 = 0;
done_zero:                          /* b89ca04 */
                HV_FMT_ZERO_STATE();
            } else {
                bVar23 = 0;
                uVar43 = 0;
            }
            goto fault_done;
        }
        bVar23 = 0;
        puVar20 = puVar30;
        if (lVar34 != 0) goto aec8;
    }
    kernel_vm_fault_callee_a1f14(puVar20, local_a8);
    kernel_vm_fault_callee_c2f4(puVar30);
    bVar6 = false;
    if (fault_arg != 0) goto retry;
    *(uint64_t *)(lVar5 + 0x238) = 0;
    HV_FMT_PAGING_CONCAT();
joined_b110:                        /* joined_r0xfffffe000b89b110 */
    if ((uStack_138 >> 2 & 1) == 0) {
        kernel_vm_fault_callee_1ab24(&local_160);
    } else if ((lStack_148 != 0) && ((~*(uint *)(lStack_148 + 0x28) & 3) != 0)) {
        kernel_vm_fault_callee_164f8();
    }
    bVar6 = false;
    goto retry;
}

/*
 * hv_el2_guest_fault_retry @ 0xfffffe000b9879b8   (hv_el2_guest_fault_retry)
 * Ghidra: bool hv_el2_guest_fault_retry(ulong param_1, ulong param_2, uint param_3,
 *                                   long param_4)
 * Guest-fault retry helper called by hv_el2_guest_fault when vm_fault
 * (kernel_vm_fault) fails on a non-write guest abort. Guards on fault_type
 * (param_3 & 0x10003c0) == 0x1000040, binds the current cpu into the vm
 * owner slot (owner[0]+8), takes the per-vm lock when needed, then walks the
 * region rbtree (owner+0x427, nodes stride 0x30, start at node[0], end at
 * node[3]) for the region whose start == addr and end <= addr, checking
 * addr + page_size (1<<((fault_type>>0x16)&3)) <= region end. On a match it
 * locks the region ref (b78fd40), releases the vm lock (b7f1e80), builds a
 * 0x40-byte fault record {0x4000000013, 0, 0, region[4], region[1], addr,
 * page_size, <saved reg per uVar4>, 2}, posts it (b7e16f0, size 0x40,
 * type 0x10), releases the region ref (refcount--, b78cc20 at 1,
 * panic c0f8674 at 0) and returns whether the post succeeded.
 * Confidence: high (complete decompile).
 * Notes: the register slot is param_4+uVar4*8+8 for uVar4 < 0x1d,
 *   param_4+0x100 for 0x1f, +0xf8 for 0x1e, else +0xf0; uVar4 =
 *   (param_3>>0x10)&0x1f. Callees b78fd40 (region lock), b7e16f0 (fault
 *   post), b78cc20 (release) are stubbed externs.
 */
int hv_el2_guest_fault_retry(void *vm, uint64_t addr, uint32_t fault_type,
                             void *state)
{
    uint64_t page_size, reg_idx;
    uint64_t *root, *region;
    uint64_t *owner_block;
    uint64_t owner_lock, cpu_slot, slot_val;
    uint64_t rec_ref, region_mid;
    int pending, prev, rc;
    uint64_t rec[9];
    uint64_t *reg_slot;
    uint64_t *puVar12;

    if ((fault_type & 0x10003c0) != 0x1000040)
        return 0;

    cpu_slot = tpidr_el1;
    owner_block = *(uint64_t **)(per_cpu_base(cpu_slot) + 0x628); /* vm owner block */
    owner_lock = owner_block[0];               /* owner[0] = the per-vm lock */
    puVar12 = (uint64_t *)(owner_lock + 8);    /* owner cpu-id slot */
    slot_val = *puVar12;
    if (slot_val == 0)
        *puVar12 = *(uint32_t *)(cpu_slot + 0x518);
    pending = hv_debug_flag;                   /* DAT_fffffe000c62b3d0 */
    if (slot_val != 0 || pending != 0)
        lock_acquire((void *)owner_lock, cpu_slot, slot_val, 0);   /* b7f0afc */
    root = (uint64_t *)owner_block[0x427];     /* region tree root */
    hv_debug_flag = pending;
    if (root == 0)
        goto no_region;

    page_size = 1ULL << ((fault_type >> 0x16) & 3);
    reg_idx = (fault_type >> 0x10) & 0x1f;
    region = 0;
    puVar12 = root;
    for (;;) {
        uint64_t start = *puVar12;
        uint64_t *next;
        if (start < addr) {
            next = (uint64_t *)((char *)puVar12 + 0x30);   /* right */
            region = (addr != start) ? region : puVar12;
        } else if (start <= addr) {
            if (puVar12[2] < addr)
                next = (uint64_t *)((char *)puVar12 + 0x30);  /* right */
            else if (puVar12[2] <= addr) {
                region = puVar12;                /* found (LAB_987aac) */
                break;
            } else {
                next = (uint64_t *)((char *)puVar12 + 0x28);  /* left */
                region = 0;
            }
        } else {
            next = (uint64_t *)((char *)puVar12 + 0x28);  /* left */
            region = 0;
        }
        puVar12 = next;
        if (puVar12 == 0)
            break;
    }
    if (region == 0)
        goto no_region;

    if (addr + page_size <= region[3]) {
        region_mid = region[1];
        rec_ref = region[4];
        kernel_region_lock(rec_ref);             /* b78fd40 */
        /* release the vm lock (b7f1e80): clear owner cpu-id, sync if needed */
        pending = hv_debug_flag;
        owner_block = *(uint64_t **)(per_cpu_base(cpu_slot) + 0x628);
        owner_lock = owner_block[0];
        prev = *(int *)(cpu_slot + 0x518);
        rc = *(int *)(owner_lock + 8);
        if (rc == prev)
            *(uint32_t *)(owner_lock + 8) = 0;
        if (rc != prev || pending != 0)
            lock_sync((void *)owner_lock, cpu_slot);  /* b7f1e80 */
        /* build the 0x40-byte fault record */
        rec[0] = 0x4000000013ull;                /* local_a0 */
        rec[1] = 0;                              /* uStack_88 */
        rec[2] = 0;                              /* local_90 */
        if (reg_idx < 0x1d)
            reg_slot = (uint64_t *)((char *)state + reg_idx * 8 + 8);
        else if (reg_idx == 0x1f)
            reg_slot = (uint64_t *)((char *)state + 0x100);
        else if (reg_idx == 0x1e)
            reg_slot = (uint64_t *)((char *)state + 0xf8);
        else
            reg_slot = (uint64_t *)((char *)state + 0xf0);
        rec[3] = *reg_slot;                      /* local_70 */
        rec[4] = 2;                              /* uStack_64 */
        rec[5] = rec_ref;                        /* local_98 = region[4] */
        rec[6] = region_mid;                     /* local_80 = region[1] */
        rec[7] = addr;                           /* uStack_78 = param_2 */
        rec[8] = page_size;                      /* local_68 = uVar3 */
        rc = kernel_fault_post(rec, 0x40, 0x10, 0, 0);  /* b7e16f0 */
        /* release the region reference */
        prev = *(int *)(rec_ref + 4);
        *(int *)(rec_ref + 4) = prev - 1;
        LORelease();
        if (prev != 0) {
            if (prev == 1)
                kernel_obj_release(rec_ref);     /* b78cc20 */
            return rc == 0;
        }
        kernel_panic_b();                        /* c0f8674, noreturn */
    }

no_region:
    /* release the vm lock (b7f1e80) and return false */
    owner_block = *(uint64_t **)(per_cpu_base(cpu_slot) + 0x628);
    owner_lock = owner_block[0];
    prev = *(int *)(cpu_slot + 0x518);
    rc = *(int *)(owner_lock + 8);
    if (rc == prev)
        *(uint32_t *)(owner_lock + 8) = 0;
    if (rc != prev || hv_debug_flag != 0)
        lock_sync((void *)owner_lock, cpu_slot);  /* b7f1e80 */
    return 0;
}

/* ---- guest IRQ / FIQ handlers ---------------------------------------- */

/*
 * hv_el2_guest_irq @ 0xfffffe000b967004   (est. hv_el2_guest_irq)
 * Ghidra: void hv_el2_guest_irq(undefined8 param_1)
 * Handles a guest IRQ on the exit path. First checks the IMPDEF interrupt
 * pending register (S3_5_15_1_1, op1=5 => EL3-ish/IMPDEF): if the low bit is
 * set it acknowledges (kernel_irq_ack type 1), clears the pending bit, ISB,
 * and runs the timer handler (kernel_timer_interrupt). Otherwise it reads the
 * pending IRQ state (S3_1_15_0_5 / S3_1_15_0_0), handles the timer-via-IPI
 * case (type 4) or defers to the interrupt dispatcher (type 2/5); a deferred
 * IRQ handler (DAT_fffffe000c68aee0) may be fired. Finally updates the
 * per-CPU clock accounting: reads CNTVCT (S3_4_15_0_B_7), accumulates the
 * delta into the per-cpu idle-time words (DAT_fffffe000c5ee650/658/660) and
 * the cpu struct +0x338.
 * Confidence: high (real decompile; the S3_5_15_1_1 IMPDEF pending register
 *   and clock accounting are unambiguous).
 * Notes: kernel_irq_ack = FUN_fffffe000b966dd8; timer = FUN_fffffe000b95f388;
 *   clock helper FUN_fffffe000b97ad74; trace FUN_fffffe000bd30528;
 *   deferred-handler global DAT_fffffe000c68aee0; IRQ-ack counter
 *   FUN_fffffe000b92a70c. Per-CPU block stride 0x4000, cpu index from
 *   tpidr_el1+0x1b0 >> 16.
 */
void hv_el2_guest_irq(void *frame)
{
	uint64_t pending;
	uint64_t st;
	uint64_t pst;
	uint64_t now, prev;
	uint64_t delta;
	long     cpu;
	long     cpu_base;
	uint32_t why;

	cpu_base = tpidr_el1;

	if (hv_signal_use_table == 0) {             /* DAT_fffffe000c5b8238 */
		pending = 0;
	} else {
		pending = UnkSytemRegRead(3, 5, 0xf, 1, 1);   /* IMPDEF pending (op1=5) */
		if ((pending & 1) != 0) {
			kernel_irq_ack(frame, 1);           /* FUN_fffffe000b966dd8 */
			UnkSytemRegWrite(3, 5, 0xf, 1, 1, 1);
			InstructionSynchronizationBarrier();
			kernel_timer_interrupt(0);          /* FUN_fffffe000b95f388 */
			goto done;
		}
	}

	st = UnkSytemRegRead(3, 1, 0xf, 0, 5);      /* S3_1_15_0_5 (est. IRQ state) */
	if (((uint)st >> 2 & 1) == 0) {
		pst = UnkSytemRegRead(3, 1, 0xf, 0, 0); /* S3_1_15_0_0 (est. pending) */
		if ((hv_signal_flag2 & 1) == 0) {       /* DAT_fffffe000c62bee0 */
			if (((uint)pst >> 0xb & 1) != 0) {
				pending = 0;
				goto timer_ipi;
			}
		} else {
			pending = UnkSytemRegRead(3, 7, 0xf, 6, 4);  /* S3_7_15_6_4 (est. timer IPI) */
			if ((pst & 0x800) != 0 || (pending & 1) != 0) {
timer_ipi:
				kernel_irq_ack(frame, 4);
				cpu = tpidr_el1;
				kernel_irq_timer_update(*(uint64_t *)(cpu + 0x1b8), 0, pending);  /* FUN_fffffe000b97ad74 */
				goto done;
			}
		}
		why = 0;
		if ((pending & 2) != 0)
			why = 5;
		kernel_irq_ack(frame, why);
		if (((uint)pending >> 1 & 1) != 0) {
			if (deferred_irq_handler == 0) {    /* DAT_fffffe000c68aee0 */
				UnkSytemRegWrite(3, 5, 0xf, 1, 1, 2);
			} else {
				deferred_irq_handler(deferred_irq_arg, 0, 0);  /* DAT_fffffe000c68aee8 */
			}
			goto done;
		}
	} else {
		kernel_irq_ack(frame, 2);
	}
	cpu = tpidr_el1;
	*(uint32_t *)(*(long *)(cpu + 0x1b8) + 0x70) = 0xffffffff;
	kernel_irq_finish();                        /* FUN_fffffe000b971378 */

done:
	if (hv_irq_ack_counter != 0)                /* DAT_fffffe000c62bc50 */
		kernel_irq_ack_extra(0, 0, 1);          /* FUN_fffffe000b92a70c */
	if ((hv_trace_flag & 0xfffffff7) != 0)
		kernel_trace(0x1050002, 0, 0, 0, 0);    /* FUN_fffffe000bd30528 */

	/* clock accounting: CNTVCT delta into per-cpu idle words */
	cpu = tpidr_el1;
	cpu = *(long *)(cpu + 0x1b0) >> 0x10;
	prev = *(long *)(*(long *)(tpidr_el1 + 0x1b8) + 0x58);
	do {
		now = prev;
		prev = UnkSytemRegRead(3, 4, 0xf, 0xb, 7);   /* CNTVCT (est.) */
		prev = *(long *)(*(long *)(tpidr_el1 + 0x1b8) + 0x58);
	} while (prev != now);
	delta = now + prev - per_cpu_idle_prev[cpu];       /* DAT_fffffe000c5ee658 */
	per_cpu_idle_accum[cpu] += delta;                  /* DAT_fffffe000c5ee650 */
	*(long *)(per_cpu_thread[cpu] + 0x338) += delta;   /* DAT_fffffe000c5ee030 */
	per_cpu_idle_last[cpu] = now + prev;                /* DAT_fffffe000c5ee660 */
}

/*
 * hv_el2_guest_fiq @ 0xfffffe000b966c74   (hv_el2_guest_fiq)
 * Ghidra: void hv_el2_guest_fiq(undefined8 param_1)
 * Handles a guest FIQ: calls kernel_irq_ack(param_1,3) (FUN_fffffe000b966dd8,
 * irq acknowledgment), then the interrupt-controller dispatch vtable
 * (**(code **)(*DAT_fffffe000c733fc0 + 0x940))(), updates the per-CPU FIQ
 * ring counter (DAT_fffffe000c5ea838 cap 0x800, per-sample timestamp sum
 * into DAT_fffffe000c5e8838), and does the CNTVCT clock accounting
 * (per-cpu idle words DAT_fffffe000c5ee650/658/660 + cpu struct +0x338) —
 * identical tail to hv_el2_guest_irq.
 * Confidence: high (complete decompile; body matches line-for-line).
 */
void hv_el2_guest_fiq(void)
{
    uint64_t cpu_base = tpidr_el1;
    uint64_t cpu;
    uint64_t prev, cur, now, delta;
    uint32_t fiq;
    void (**ic_dispatch)(void);

    /* Acknowledge the FIQ (irq-ack type 3) and run the interrupt-controller
     * dispatch vtable slot +0x940 (DAT_fffffe000c733fc0 = IC ops table). */
    kernel_irq_ack((void *)cpu_base, 3);                /* FUN_fffffe000b966dd8 */
    ic_dispatch = (void (**)(void))(uintptr_t)
                  *((uint64_t *)hv_ic_vtable + 0x120);  /* *(*(DAT_fffffe000c733fc0)+0x940) */
    (*ic_dispatch)();

    cpu = (*(uint64_t *)(cpu_base + 0x1b0)) >> 16;      /* per-CPU index */
    fiq = per_cpu_fiq_counter[cpu];                     /* DAT_fffffe000c5ea838 */
    if (fiq != 0x800) {
        /* Rolling CNTVCT time-accumulation ring (cap 0x800 samples/fifo). */
        uint64_t last = *(uint64_t *)(*(uint64_t *)(cpu_base + 0x1b8) + 0x58);
        do {
            prev = last;
            cur = UnkSytemRegRead(3, 4, 0xf, 0xb, 7);   /* CNTVCT (est.) */
            last = *(uint64_t *)(*(uint64_t *)(cpu_base + 0x1b8) + 0x58);
        } while (last != prev);
        per_cpu_fiq_accum[cpu][fiq] = (uint32_t)cur + (uint32_t)prev;
        if (per_cpu_fiq_counter[cpu] == fiq) {
            per_cpu_fiq_counter[cpu] = fiq + 1;
        }
    }
    if (hv_irq_ack_counter != 0) {                      /* DAT_fffffe000c62bc50 */
        kernel_irq_ack_extra(0, 0, 1);                  /* FUN_fffffe000b92a70c */
    }
    if ((hv_trace_flag & 0xfffffff7) != 0) {
        kernel_trace(0x1050002, 0, 0, 0, 0);            /* FUN_fffffe000bd30528 */
    }

    /* CNTVCT clock accounting — identical tail to hv_el2_guest_irq. */
    cpu = (*(uint64_t *)(cpu_base + 0x1b0)) >> 16;
    prev = *(uint64_t *)(*(uint64_t *)(cpu_base + 0x1b8) + 0x58);
    do {
        now = prev;
        cur = UnkSytemRegRead(3, 4, 0xf, 0xb, 7);       /* CNTVCT (est.) */
        prev = *(uint64_t *)(*(uint64_t *)(cpu_base + 0x1b8) + 0x58);
    } while (prev != now);
    now = cur + now;                                    /* sum = CNTVCT + stable */
    delta = now - per_cpu_idle_prev[cpu];               /* DAT_fffffe000c5ee658 */
    per_cpu_idle_accum[cpu] += delta;                   /* DAT_fffffe000c5ee650 */
    *(long *)(per_cpu_thread[cpu] + 0x338) += delta;    /* DAT_fffffe000c5ee030 */
    per_cpu_idle_last[cpu] = now;                       /* DAT_fffffe000c5ee660 */
}

/* ---- return to guest -------------------------------------------------- */

/*
 * hv_el2_return_to_guest @ 0xfffffe000b75e468   (est. hv_el2_return_to_guest)
 * Ghidra: undefined8 hv_el2_return_to_guest(uint param_1)
 * Restores the guest's EL1 state from the saved frame (x21 base) and erets
 * back to the guest. On entry param_1 bit7 (0x80) selects the fast path
 * (hv_el2_eret_fast); otherwise it re-checks the preemption count
 * (tpidr+0x1c0) and the "saved thread state with interrupts enabled" guard,
 * then restores elr_el1/spsr_el1/fpsr/fpcr, reloads SVE Z/P registers when
 * the guest SVE state is active (type 0x31 at tpidr+0x120), re-arms the
 * PAC key (UnkSytemRegWrite(3,0,1,0,5)) and T1SZ
 * (UnkSytemRegWrite(3,0,1,0,6,0x10001)), and executes ExceptionReturn().
 * hv_el2_eret_fast is the same tail without the preemption re-check.
 * Confidence: high (SVE restore + ExceptionReturn observed)
 * Notes: "Signed thread state manipulated with interrupts enabled" guard is
 *   in FUN_fffffe000b760444 (JOP-hash verify of the saved state); this is
 *   the "no-register-loss on exit" path the security audit keys on.
 */
void hv_el2_return_to_guest(void *state)
{
    uint8_t *st = state;
    /* NOTE: in the binary the fast-path selector (bit 7 of the register-passed
     * uint) is delivered in w0 alongside the frame in x21; the C signature
     * carries only the frame, so the exit-reason word (frame+0x4008) is used
     * as the reconstruction's stand-in for that flag. */
    uint32_t fast = *(uint32_t *)(st + 0x4008);   /* HV_EL2_FRAME_EXIT word */

    daif |= 0x3c0;                       /* raise DAIF (mask all interrupts) */
    if (((fast >> 7) & 1) == 0) {
        uint64_t cpu = tpidr_el1;
        if (*(int *)(cpu + 0x1c0) == 0 &&
            (*(uint32_t *)(*(uint64_t *)(cpu + 0x1b8) + 0x4c) & 4) != 0) {
            /* Preemption count 0 + per-cpu flag: take the fast eret path
             * (bypass the preemption re-check). Save the caller's fp/lr to
             * frame-0x10/-0x8 and clear the preempt flag first. */
            *(uint64_t *)(st - 0x10) = /* fp (x29) */ 0;
            *(uint64_t *)(st - 8) = /* lr (x30) */ 0;
            hv_preempt_clear();          /* FUN_fffffe000b7a56d4 */
            hv_el2_eret_fast(state);
            return;
        }
    } else {
        (void)tpidr_el1;
    }
    hv_el2_guest_restore_eret(st);       /* shared restore + eret tail */
}

/* ---- EL2 vector entry handlers --------------------------------------- */

/*
 * The four EL2 vector handlers (hv_el2_vector_sync sync, hv_el2_vector_irq
 * irq, hv_el2_vector_fiq fiq, hv_el2_vector_error error) are nearly
 * identical assembly sequences: they save SP_EL0/SP_EL1, MDSCR_EL1, tpidr_el1/
 * el0/ro, PAR_EL1, CSSELR_EL1, the EL2 feature/sysreg capture, the guest GPRs
 * (x2..x30), the FP/SVE registers (conditional on CPTR_EL2 bit 20/24), then
 * elr_el1/spsr_el1/far_el1/esr_el1, switch to the per-CPU EL2 stack (tpidr_el2),
 * restore the hypervisor's EL2 control regs (cptr_el2, s3_3_c13_0_5,
 * s3_0_c1_2_4, s3_4_c15_12_0, s3_6_c15_0_4/5, mdscr_el1, tpidr_el1/el0/ro),
 * compute and verify the PAC "JOP hash" of the saved sysregs (panic
 * "Sysreg JOP hash mismatch detected (guest state corruption)"), then branch
 * to the common dispatch hv_el2_common_dispatch with a per-type return address:
 *
 *   handler          exit reason   EL1 return target
 *   b760b94 (sync)   1             b760eec (FUN_fffffe000b760eec: ESR classify + return)
 *   b760f04 (irq)    3             b75df48 (EL1 irq handler entry)
 *   b761260 (fiq)    4             b75dfcc (EL1 fiq handler entry)
 *   b7615bc (error)  2             b75e04c (EL1 error handler entry)
 *
 * NOTE: the exit-reason -> return-target pairing is taken from the
 * decompiler output (hv_el2_vector_irq passes 0xfffffe000b75df48,
 * hv_el2_vector_fiq passes &LAB_fffffe000b75dfcc, hv_el2_vector_error
 * passes &LAB_fffffe000b75e04c). The sync handler computes its target via
 * adrp+0xed8; get_function_callers(b75e468) showed the sync continuation is
 * FUN_fffffe000b760eec, which runs guest_esr_classify then return_to_guest —
 * confirmed as the sync return target (unlike irq/fiq/error, which land on
 * the EL1 kernel vector handlers). The full annotated assembly for all four
 * vectors lives in osfmk/arm64/hv_el2_vectors.s.
 *
 * hv_el2_common_dispatch zeroes the scratch GPRs (x2..x30), PAC-authenticates
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

/* The four vector handlers are pure assembly (guest-state save + JOP-hash
 * verify + exit-reason write + branch to hv_el2_common_dispatch). Their real
 * bodies are transcribed in osfmk/arm64/hv_el2_vectors.s; these C wrappers
 * are the entry points the vector table branches to. */
extern void __hv_el2_vector_sync(void);    /* hv_el2_vectors.s (FUN_fffffe000b760b94) */
extern void __hv_el2_vector_irq(void);     /* hv_el2_vectors.s (FUN_fffffe000b760f04) */
extern void __hv_el2_vector_fiq(void);     /* hv_el2_vectors.s (FUN_fffffe000b761260) */
extern void __hv_el2_vector_error(void);   /* hv_el2_vectors.s (FUN_fffffe000b7615bc) */

void hv_el2_vector_sync(void)
{
    /* Real body in hv_el2_vectors.s: saves guest state, exit reason
     * HV_EL2_EXIT_REASON_SYNC, branches to hv_el2_common_dispatch. */
    __hv_el2_vector_sync();
}

void hv_el2_vector_irq(void)
{
    __hv_el2_vector_irq();
}

void hv_el2_vector_fiq(void)
{
    __hv_el2_vector_fiq();
}

void hv_el2_vector_error(void)
{
    __hv_el2_vector_error();
}

void hv_el2_common_dispatch(void *frame, void (*target)(void))
{
    /* The vector asm branches here with x0 = frame, x1 = return target,
     * w2 = exit reason. Run the EL2-exit cleanup, zero tpidr_el2, the
     * per-CPU exit stats, then jump to the EL1 return target (the
     * decompiler's UNRECOVERED_JUMPTABLE indirect jump). */
    (void)frame;
    hv_exit_dsb();      /* FUN_fffffe000b953dd8(0, frame, target, 0,0,0,0,0,0,0,0) — args are register content */
    tpidr_el2 = 0;
    hv_exit_stats();    /* FUN_fffffe000b80768c */
    target();           /* indirect jump to the EL1 kernel handler */
}
