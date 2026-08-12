/* Recreated from kernelcache.arm64.kc (xnu-12377.121.10 RELEASE_ARM64_T8142, image base fffffe0007004000). Ground truth: Ghidra FUN_ names + addresses; all names are estimates. */
#include "hv_compat.h"

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
 *     hv_el2_vector_sync @ b760b10  (sync from guest)   reason 1
 *     hv_el2_vector_irq @ b760f04  (irq  from guest)   reason 3
 *     hv_el2_vector_fiq @ b761260  (fiq  from guest)   reason 4
 *     hv_el2_vector_error @ b7615bc  (error from guest)  reason 2
 *   Common dispatch: hv_el2_common_dispatch (eret to EL1 kernel handler)
 *   EL1 kernel exception handlers reached by the dispatch (VBAR_EL1 =
 *   0xfffffe000b75c000, set by kernel_entry):
 *     el1_sync_handler (sync), el1_fiq_handler (fiq),
 *     el1_irq_handler (irq), el1_error_handler (error tail)
 *   Guest exit C-level handlers:
 *     hv_el2_guest_esr_classify (guest ESR classifier / sync dispatch)
 *     hv_el2_guest_fault (guest fault / vm_fault path)
 *     hv_el2_guest_irq (guest IRQ)
 *     hv_el2_guest_fiq (guest FIQ)
 *     hv_el2_guest_exc_check (guest exception check / pre-dispatch)
 *   Return to guest:
 *     hv_el2_return_to_guest / hv_el2_eret_fast (restore + eret)
 *     hv_el2_exception_exit (exception-exit tail)
 *     hv_el2_preemption_panic (preemption-count-negative panic)
 *
 * Guest exit reason is stored at guest-state block +0x4008 (values: 1 sync,
 * 2 error, 3 irq, 4 fiq). The hub hv_vcpu_run (hv_vcpu_run,
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
 * Guest ESR classification (hv_el2_guest_esr_classify). Decodes ESR_EL1 EC
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
extern void hw_error_report(void *, uint64_t, uint32_t, uint64_t);
                                    /* hw error (PL2/LLC) reporter, kernel */
extern void debug_exceptions_disable(int);   /* disable debug exceptions, kernel */
extern uint64_t kernel_boot_misc_q(uint64_t, uint64_t); /* hw table walk */

/*
 * Guest-fault vm_fault family — DIRECT callees of hv_el2_guest_fault,
 * recreated with bodies in hv_el2.c per the FULL-AUDIT rule (tree
 * guest-fault). Ground truth: FUN_ + address; names are estimates.
 */
int  hv_el2_guest_pte_check(uint64_t *pmap, uint64_t ipa, uint32_t prot,
                            int is_write); /* FUN_fffffe000b94b450, stage-2 walk */
long kernel_vm_fault(void *vm, uint64_t addr, uint32_t fault_type,
                     uint32_t fault_flags, void **vnode_mp, uint64_t mp_size,
                     uint32_t *result_out, uint16_t *fault_opts,
                     void *fault_arg);     /* FUN_fffffe000b89988c, XNU vm_fault */
int  hv_el2_guest_fault_retry(void *vm, uint64_t addr, uint32_t fault_type,
                              void *state); /* FUN_fffffe000b9879b8, region+post */

/*
 * Deeper kernel VM internals the recreated vm_fault family calls (2+ levels
 * into XNU). Stubbed externs — the FULL-AUDIT boundary. Ground truth: Ghidra
 * FUN_ + address.
 */
extern void *per_cpu_base(uint64_t cpu);              /* b866ec4 */
extern long vm_fault_enter(void *map, uint64_t addr, uint64_t flags,
                           void **out1, void **out2, void **out3,
                           uint32_t *out4, int *out5, uint16_t *fault_opts,
                           void **map_arg, void *fault, void *arg,
                           uint64_t stack, void *stack_arg); /* b89d5f8 */
extern void  vm_fault_internal(void);                  /* b89de34 */
extern void  vm_fault_finish(void);                    /* b94c554 */
extern int   kernel_page_validate(uint64_t, uint64_t *);      /* c0d7b94 (0 = ok) */
extern int   kernel_paddr_type(uint64_t, uint64_t *);         /* c0d7c20 (0 = ok) */
extern int   kernel_memattr_resolve(uint64_t, uint32_t, uint64_t,
                                    void *, uint32_t);        /* b94abbc */
extern void  kernel_preempt_dec(uint64_t *);                  /* b94172c */
extern void  kernel_tlb_flush(void);                          /* b96c6d4 */
extern int   kernel_lock_bit_acquire(uint64_t, int);          /* b7f8d9c (0 = busy) */
extern void  kernel_lock_bit_wait(uint64_t, int, void **);    /* b7f8ce0 (see hv_el2.c 4-arg form) */
extern void  kernel_lock_bit_release(uint64_t, int);          /* b7f8e50 */
extern void  kernel_memory_barrier(int, int);                 /* DataMemoryBarrier */
extern void  kernel_region_lock(uint64_t);                    /* b78fd40 */
extern int   kernel_fault_post(void *rec, uint64_t, uint64_t,
                               int, int);                     /* b7e16f0 */
extern void  kernel_obj_release(uint64_t);                    /* b78cc20 */
extern void  kernel_panic_a(void) __attribute__((noreturn));  /* c0f1874 */
extern void  kernel_panic_b(void) __attribute__((noreturn));  /* c0f8674 */
extern void  kernel_panic_msg2(void) __attribute__((noreturn)); /* c0e11ec (assert) */

/* Hypervisor/feature globals (see docs/kernelcache.md anchors). Names match
 * hv_internal.h's shared global naming table; DAT_ addresses kept here. */
extern uint64_t hv_build_gate;              /* DAT_fffffe0007e0da68 : EL2 feature gate (==0 normal) */
extern uint16_t hv_el2_capable;             /* DAT_fffffe0007e0d81e : feature flag bit 0 */
extern uint64_t hv_trace_flag;              /* DAT_fffffe000c68ac90 : trace-enable flag (bit 0) */
extern uint64_t tpidr_el1;                  /* per-cpu data base (kernel) */

/* Guest-fault vm_fault family globals (recreated bodies; DAT_ kept here). */
extern uint64_t hv_fault_boot_threshold;    /* DAT_fffffe0007e9d348 : VM ready threshold (<0x12 = not booted) */
extern uint64_t hv_mem_window_lo;           /* DAT_fffffe0007e0c050 : DRAM window lower bound */
extern uint64_t hv_mem_window_hi;           /* DAT_fffffe0007e0c058 : DRAM window upper bound */
extern uint8_t  hv_memattr_granule[];       /* DAT_fffffe0007d82e20 : per-attr granularity table (0x2000/0x1000/0x3000) */
extern uint64_t hv_special_owner_block;     /* DAT_fffffe000c62b698 : special unrestricted owner/pmap block */

/* EL2 sysreg reads — kept literal; identity unverified (op1=4 => EL2). */
extern uint64_t UnkSytemRegRead(int op0, int op1, int crn, int crm, int op2);
extern void UnkSytemRegWrite(int op0, int op1, int crn, int crm, int op2,
                             uint64_t val);

/*
 * hv_el2.c prototypes — the decompiled EL2 vector handlers and guest-exit
 * helpers. Implemented as faithful C re-creations of the Ghidra decompiles.
 */
void hv_el2_vector_sync(void);    /* FUN_fffffe000b760b94 (est.; asm in hv_el2_vectors.s) */
void hv_el2_vector_irq(void);     /* FUN_fffffe000b760f04 (est.; asm in hv_el2_vectors.s) */
void hv_el2_vector_fiq(void);     /* FUN_fffffe000b761260 (est.; asm in hv_el2_vectors.s) */
void hv_el2_vector_error(void);   /* FUN_fffffe000b7615bc (est.; asm in hv_el2_vectors.s) */
void hv_el2_common_dispatch(void *frame, void (*target)(void)); /* FUN_fffffe000b761930 (est.) */
void hv_el2_guest_esr_classify(void *state, uint64_t esr, uint64_t far);
                                    /* FUN_fffffe000b96743c (est.) */
void hv_el2_guest_fault(void *state, uint64_t esr, uint64_t far,
                        uint32_t reason, uint32_t which);
                                    /* FUN_fffffe000b967768 (est.) */
int hv_el2_guest_pte_check(uint64_t *pmap, uint64_t ipa, uint32_t prot,
                           int is_write);   /* FUN_fffffe000b94b450 (est.) */
long kernel_vm_fault(void *vm, uint64_t addr, uint32_t fault_type,
                     uint32_t fault_flags, void **vnode_mp, uint64_t mp_size,
                     uint32_t *result_out, uint16_t *fault_opts,
                     void *fault_arg);      /* FUN_fffffe000b89988c (est.) */
int hv_el2_guest_fault_retry(void *vm, uint64_t addr, uint32_t fault_type,
                             void *state);  /* FUN_fffffe000b9879b8 (est.) */
void hv_el2_return_to_guest(void *state);  /* FUN_fffffe000b75e468 (frame in x21, flag in w0) */
void hv_el2_eret_fast(void *state);        /* FUN_fffffe000b75e5cc (frame in x21) */
void hv_el2_guest_irq(void *frame);   /* FUN_fffffe000b967004 (est.) */
void hv_el2_guest_fiq(void);      /* FUN_fffffe000b966c74 (est.) */
bool hv_el2_guest_exc_check(uint64_t esr, uint64_t elr, uint64_t far, uint64_t spsr); /* FUN_fffffe000b9679c8 */
void hv_el2_exception_exit(void *state); /* FUN_fffffe000b75e420 (frame in x21) */
void hv_el2_preemption_panic(void) __attribute__((noreturn)); /* FUN_fffffe000b75e8a8 */

#endif /* _HV_EL2_H_ */
