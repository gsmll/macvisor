/* Recreated from kernelcache.arm64.kc (xnu-12377.121.10 RELEASE_ARM64_T8142, image base fffffe0007004000). Ground truth: Ghidra FUN_ names + addresses; all names are estimates. */

/*
 * hv_el2.h — EL2 exception vector table and the guest->EL2 exit path.
 *
 * Owned by the el2-vectors tree. Documents the EL2 exception vector
 * handlers (VBAR_EL2 target) and the full guest-exit flow: EL2 vector ->
 * save guest state -> common dispatch -> EL1 kernel exception handler ->
 * guest ESR classifier / fault handler -> return to guest (eret).
 *
 * Verified handlers (addresses from Ghidra; see hv_el2.c for decompiles):
 *   EL2 vector handlers (save guest EL1 state, write exit reason, branch
 *   to common dispatch b761930):
 *     FUN_fffffe000b760b94 @ b760b10  (sync from guest)   reason 1
 *     FUN_fffffe000b760f04 @ b760f04  (irq  from guest)   reason 3
 *     FUN_fffffe000b761260 @ b761260  (fiq  from guest)   reason 4
 *     FUN_fffffe000b7615bc @ b7615bc  (error from guest)  reason 2
 *   Common dispatch: FUN_fffffe000b761930 (eret to EL1 kernel handler)
 *   EL1 kernel exception handlers reached by the dispatch (VBAR_EL1 =
 *   0xfffffe000b75c000, set by kernel_entry):
 *     FUN_fffffe000b75deac (sync), FUN_fffffe000b75df7c (fiq),
 *     FUN_fffffe000b75e000 (irq), FUN_fffffe000b75e058 (error tail)
 *   Guest exit C-level handlers:
 *     FUN_fffffe000b96743c (guest ESR classifier / sync dispatch)
 *     FUN_fffffe000b967768 (guest fault / vm_fault path)
 *     FUN_fffffe000b967004 (guest IRQ)
 *     FUN_fffffe000b966c74 (guest FIQ)
 *     FUN_fffffe000b9679c8 (guest exception check / pre-dispatch)
 *   Return to guest:
 *     FUN_fffffe000b75e468 / FUN_fffffe000b75e5cc (restore + eret)
 *     FUN_fffffe000b75e420 (exception-exit tail)
 *     FUN_fffffe000b75e8a8 (preemption-count-negative panic)
 *
 * Guest exit reason is stored at guest-state block +0x4008 (values: 1 sync,
 * 2 error, 3 irq, 4 fiq). The hub FUN_fffffe000b989a44 (hv_vcpu_run,
 * vcpu-core tree) reads es+0x4008 to dispatch the exit. See docs/chain-map.md
 * 'EL2 exception vector table / guest-exit path'.
 */

#ifndef _HV_EL2_H_
#define _HV_EL2_H_

#include <stdint.h>
#include <stddef.h>

/* Exit reason codes written by the EL2 vector handlers (est. semantics). */
#define HV_EL2_EXIT_REASON_SYNC   1   /* synchronous exception (incl. HVC) */
#define HV_EL2_EXIT_REASON_ERROR  2   /* SError / async abort               */
#define HV_EL2_EXIT_REASON_IRQ    3   /* IRQ from guest                     */
#define HV_EL2_EXIT_REASON_FIQ    4   /* FIQ from guest                     */

/*
 * The guest-state block layout touched by the EL2 entry/exit code. Offsets
 * relative to the block base (the per-CPU EL2 state / guest saved-state
 * frame). All estimates; the el2-state tree's hv_vmm.h owns the EL2 register
 * bank offsets (+0x4000..). The entry code saves the guest's EL1 registers
 * into this frame before dispatching to EL1.
 */
#define HV_EL2_FRAME_SP0       0x370   /* saved sp_el0                       */
#define HV_EL2_FRAME_SP1       0x378   /* saved sp_el1                       */
#define HV_EL2_FRAME_MDSCR     0x350   /* mdscr_el1                          */
#define HV_EL2_FRAME_TPIDR_EL1 0x358   /* tpidr_el1                          */
#define HV_EL2_FRAME_TPIDR_EL0 0x360   /* tpidr_el0                          */
#define HV_EL2_FRAME_TPIDRRO   0x368   /* tpidrro_el0                        */
#define HV_EL2_FRAME_PAR       0x380   /* par_el1                            */
#define HV_EL2_FRAME_CSSELR    0x388   /* csselr_el1                         */
#define HV_EL2_FRAME_ELR       0x108   /* elr_el1 (guest PC)                 */
#define HV_EL2_FRAME_SPSR      0x110   /* spsr_el1 (guest PSTATE)            */
#define HV_EL2_FRAME_FAR       0x118   /* far_el1 (guest fault address)      */
#define HV_EL2_FRAME_ESR       0x120   /* esr_el1 (guest syndrome)           */
#define HV_EL2_FRAME_EXIT      0x4008  /* exit reason word (written by vec)   */
#define HV_EL2_FRAME_FPSR      0x340   /* fpsr                                */
#define HV_EL2_FRAME_FPCR      0x344   /* fpcr                                */
#define HV_EL2_FRAME_FP_BASE   0x140   /* q0..q31 (32x16 = 0x200 bytes)      */

/*
 * Guest ESR classification (FUN_fffffe000b96743c). Decodes ESR_EL1 EC
 * (Exception Class, bits [31:26]) and writes an exit code to state+0x4008.
 * Observed EC handling (value = ESR>>26 & 0x3f):
 *   0x18 (SVC)   -> exit code 8, iss = ESR & 0x1ffffff at +0x4018
 *   0x1d (?)     -> exit code 0xd
 *   0x20 (IABT)  -> counter tpidr+0x8e0, fault handler reason 5
 *   0x24 (DABT)  -> counter tpidr+0x8d8, fault handler reason 1/3
 *   0x3f (?)     -> SMC-like: iss==3 -> 0x80000000; iss==0x20 -> afsr1 reason 8;
 *                   iss==0x21 -> 7; iss in [0x23,0x26] -> 1
 *   others -> host-abort check (bit3 of pstate @ +0x48/+0x110) -> panic
 *             "Unexpected host abort from guest context"
 *   EC>0x34 or unmapped -> "Unrecognized guest trap exception" panic.
 * These are ESTIMATES of the EC encodings; register/ESR semantics unverified.
 */
#define HV_EL2_EC_SHIFT   26
#define HV_EL2_EC_MASK    0x3f

/* Shared kernel deps (NOT recreated; see docs/chain-map.md + manifest). */
extern void kernel_trace(uint32_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern void kernel_panic_assert(void);        /* c0e11ec, noreturn */
extern void kernel_panic_msg(void);           /* c0f0fa4, noreturn */
extern void kernel_vm_fault(uint64_t, uint64_t, int, int, int, int, int,
                            uint64_t *, int); /* b89988c, b94b450, b9879b8 wrappers */
extern void FUN_fffffe000b98f304(void *, uint64_t, uint32_t, uint64_t);
                                    /* hw error (PL2/LLC) reporter, kernel */
extern void FUN_fffffe000b968948(int);   /* disable debug exceptions, kernel */
extern uint64_t FUN_fffffe000c0d993c(uint64_t, uint64_t); /* hw table walk */
extern int FUN_fffffe000b94b450(uint64_t, uint64_t, uint32_t, int);
extern int FUN_fffffe000b89988c(uint64_t, uint64_t, uint32_t, int, int, int,
                                int, uint64_t *, int);
extern int FUN_fffffe000b9879b8(uint64_t, uint64_t, uint64_t, void *);

/* Hypervisor/feature globals (see docs/kernelcache.md anchors). Names match
 * hv_internal.h's shared global naming table; DAT_ addresses kept here. */
extern uint64_t hv_build_gate;              /* DAT_fffffe0007e0da68 : EL2 feature gate (==0 normal) */
extern uint16_t hv_el2_capable;             /* DAT_fffffe0007e0d81e : feature flag bit 0 */
extern uint8_t  hv_trace_flag;              /* DAT_fffffe000c68ac90 : trace-enable flag (bit 0) */
extern uint8_t *tpidr_el1;                  /* per-cpu data base (kernel) */

/* EL2 sysreg reads — kept literal; identity unverified (op1=4 => EL2). */
extern uint64_t UnkSytemRegRead(int op0, int op1, int crn, int crm, int op2);
extern void UnkSytemRegWrite(int op0, int op1, int crn, int crm, int op2,
                             uint64_t val);

/*
 * hv_el2.c prototypes — the decompiled EL2 vector handlers and guest-exit
 * helpers. Implemented as faithful C re-creations of the Ghidra decompiles.
 */
void hv_el2_vector_sync(void);    /* FUN_fffffe000b760b94 (est.) */
void hv_el2_vector_irq(void);     /* FUN_fffffe000b760f04 (est.) */
void hv_el2_vector_fiq(void);     /* FUN_fffffe000b761260 (est.) */
void hv_el2_vector_error(void);   /* FUN_fffffe000b7615bc (est.) */
void hv_el2_common_dispatch(void);/* FUN_fffffe000b761930 (est.) */
void hv_el2_guest_esr_classify(void *state, uint64_t esr, uint64_t far);
                                    /* FUN_fffffe000b96743c (est.) */
void hv_el2_guest_fault(void *state, uint64_t esr, uint64_t far,
                        uint32_t reason, uint32_t which);
                                    /* FUN_fffffe000b967768 (est.) */
void hv_el2_return_to_guest(void *state);  /* FUN_fffffe000b75e468/5e5cc */
void hv_el2_guest_irq(void);      /* FUN_fffffe000b967004 (est.) */
void hv_el2_guest_fiq(void);      /* FUN_fffffe000b966c74 (est.) */

#endif /* _HV_EL2_H_ */
