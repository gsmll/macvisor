/* Recreated from sptm.t8142.release.im4p (SPTM, arm64e, image base 0) — the
 * Secure Page Table Monitor (GL2). Ground truth: Ghidra FUN_ names + addresses;
 * public API names from docs/sptm/headers/sptm_common.h. All names are
 * estimates unless header-matched.
 *
 * This file covers the SPTM guarded-level dispatch / state-transition
 * handlers (region 0xa0000-0xa2b50): the per-state transition handlers
 * entered from the state-transition table @0x16770, the TXM/SK entry
 * context-save helpers, and the exception-return handlers that restore the
 * guest register file and ERET back to the exception vector.
 *
 * The GENTER/GEXIT guarded-level transitions are rendered as opaque calls
 * (opcode 0x00201420 / 0x00201400); the selector in x16 selects the dispatch
 * endpoint per sptm_common.h (SPTM_LOAD_DISPATCH_ID). The actual guarded
 * transition happens inside sptm_dispatch_transition (FUN_000e6bc0), which
 * reads the state table and jumps to the target handler; the entry helpers
 * below perform the context-save that precedes it.
 *
 * Shared SPTM-internal helpers called from these bodies are declared extern
 * with a one-line note giving their Ghidra address and estimated purpose.
 */

#include <stdint.h>
#include <stddef.h>
#include <string.h>

#include "sptm_internal.h"

/* ------------------------------------------------------------------ *
 * System-register + barrier helpers.
 * ------------------------------------------------------------------ */

/* Per-CPU base: the (3,6,0xf,8,0)/(3,6,0xf,0xb,1)/tpidr_el2 selector pattern
 * the decompiler shows on every entry. */
static inline uint64_t *sptm_cpu(void)
{
    uint64_t sel = __builtin_arm_rsr64("s3_6_c15_c8_0");  /* (3,6,0xf,8,0) */
    uint64_t base = sel ? __builtin_arm_rsr64("s3_6_c15_c11_1")  /* (3,6,0xf,0xb,1) */
                        : __builtin_arm_rsr64("tpidr_el2");
    return (uint64_t *)base;
}

static inline void sptm_write_daif(uint64_t v)  { __builtin_arm_wsr64("daif", v); }
static inline uint64_t sptm_read_daif(void)     { return __builtin_arm_rsr64("daif"); }
/* spsel is written with an immediate (msr spsel, #imm) — the builtin needs a
 * constant operand. */
static inline void sptm_write_spsel(int sel) { __asm__ volatile("msr spsel, %0" ::"i"(sel)); }

static inline void sptm_write_elr_el1(uint64_t v)   { __builtin_arm_wsr64("elr_el1", v); }
static inline void sptm_write_spsr_el1(uint64_t v)  { __builtin_arm_wsr64("spsr_el1", v); }
static inline void sptm_write_esr_el1(uint64_t v)   { __builtin_arm_wsr64("esr_el1", v); }
static inline void sptm_write_far_el1(uint64_t v)   { __builtin_arm_wsr64("far_el1", v); }
static inline void sptm_write_mdscr_el1(uint64_t v) { __builtin_arm_wsr64("mdscr_el1", v); }
static inline void sptm_write_sctlr_el1(uint64_t v) { __builtin_arm_wsr64("sctlr_el1", v); }
static inline void sptm_write_tcr_el1(uint64_t v)   { __builtin_arm_wsr64("tcr_el1", v); }
static inline void sptm_write_cptr_el2(uint64_t v)  { __builtin_arm_wsr64("cptr_el2", v); }
static inline void sptm_write_hcr_el2(uint64_t v)   { __builtin_arm_wsr64("hcr_el2", v); }
static inline uint64_t sptm_read_hcr_el2(void)      { return __builtin_arm_rsr64("hcr_el2"); }
static inline void sptm_write_fpsr(uint64_t v)      { __builtin_arm_wsr64("fpsr", v); }
static inline void sptm_write_fpcr(uint64_t v)      { __builtin_arm_wsr64("fpcr", v); }
static inline uint64_t sptm_read_fpcr(void)         { return __builtin_arm_rsr64("fpcr"); }
static inline void sptm_write_sp_el0(uint64_t v)    { __builtin_arm_wsr64("sp_el0", v); }
static inline void sptm_write_sp_el1(uint64_t v)    { __builtin_arm_wsr64("sp_el1", v); }
static inline void sptm_write_tpidr_el1(uint64_t v) { __builtin_arm_wsr64("tpidr_el1", v); }
static inline void sptm_write_tpidr_el0(uint64_t v) { __builtin_arm_wsr64("tpidr_el0", v); }
static inline void sptm_write_tpidrro_el0(uint64_t v){ __builtin_arm_wsr64("tpidrro_el0", v); }
static inline void sptm_write_par_el1(uint64_t v)   { __builtin_arm_wsr64("par_el1", v); }
static inline void sptm_write_csselr_el1(uint64_t v){ __builtin_arm_wsr64("csselr_el1", v); }
static inline uint64_t sptm_read_currentel(void)    { return __builtin_arm_rsr64("currentel"); }

/* ERET — return from the guarded level back to the caller's exception level.
 * Ghidra flags these as "bad instruction" because ERET terminates control
 * flow; the decompiled function therefore appears to fall off the end. */
static inline void sptm_eret(void) __attribute__((noreturn));
static inline void sptm_eret(void) { __asm__ volatile("eret" ::: "memory"); __builtin_unreachable(); }

static inline void sptm_dsb_sy(void) { __builtin_arm_dsb(15); }  /* DSB SY */
static inline void sptm_dmb_ish(void){ __builtin_arm_dmb(11); }  /* DMB ISH */
static inline void sptm_wfe(void)    { __builtin_arm_wfe(); }

/* ------------------------------------------------------------------ *
 * Shared SPTM-internal helpers (outside this batch) — extern with Ghidra
 * address + estimated role.
 * ------------------------------------------------------------------ */

/* FUN_000e6bc0 — the guarded state-transition dispatcher. Reads the current
 * state (per-CPU +0xa60) and event type, indexes the state-transition table
 * @0x16770, validates the transition, then jumps to the target handler.
 * This is where the actual GENTER/GEXIT (opcode 0x00201420/0x00201400)
 * guarded-level transition is performed (selector in x16). */
extern void sptm_dispatch_transition(uint64_t event, uint64_t arg);

/* FUN_000e74e0 — maps a guarded call selector/arg (param_1) to a transition
 * event type (0x2/0x3/0x4/0xc/0xd/0xe) then invokes sptm_dispatch_transition;
 * validates domain capability flags before the transition. */
extern void sptm_dispatch_route(uint64_t selector, uint64_t arg);

/* FUN_000f8804 — noreturn SPTM panic taking only a format string. */
extern void sptm_panic_str(const char *fmt) __attribute__((noreturn));
/* FUN_000f8844 — noreturn SPTM panic: panic(err, val, fmt). */
extern void sptm_panic(uint32_t err, uint64_t val, const char *fmt) __attribute__((noreturn));

/* FUN_000f89b4 — noreturn "Invalid GENTER" dispatch panic. */
extern void sptm_invalid_genter_panic(void) __attribute__((noreturn));

/* FUN_000e7678 — returns the dispatch name string for a dispatch id (per-CPU
 * +0xa38): validates id <= 8 and returns the name from the table @0x19c18,
 * else panics. */
extern const char *sptm_dispatch_name(uint64_t dispatch_id);

/* FUN_000e78dc — restore EL1 debug/control registers from the given per-CPU
 * context base (param_2 selects the state bank). */
extern void sptm_debug_state_restore(uint64_t mode, void *ctx);
/* FUN_000e7c30 — save the stage-2 (EL2) MMU/exception context for the guest
 * state at the given per-CPU base. */
extern void sptm_stage2_state_save(void *ctx, uint64_t mode, uint64_t flag);

/* FUN_000d8a58 — translate a guest physical address through the PAPT (page
 * table) to a SPTM physical address. */
extern uint64_t sptm_papt_to_phys(uint64_t paddr);

/* FUN_000e3d7c — translate a physical address to its SPTM virtual address. */
extern void *sptm_phystokv(uint64_t paddr);
/* FUN_000d81bc — resolve a guest PC / guarded-call return address to the
 * SPTM virtual form used by the dispatch machinery. */
extern uint64_t sptm_dispatch_resolve(uint64_t pc);

/* Globals referenced from these bodies (SPTM .data). */
extern volatile uint64_t *sptm_exit_record;      /* DAT_000a5028 */
extern uint64_t sptm_cur_sp;                     /* DAT_00114008 */
extern uint64_t sptm_ctx_save_area;              /* DAT_00114018 */
extern volatile uint16_t sptm_handoff_magic;     /* DAT_0010000c */
extern volatile uint16_t sptm_handoff_sel;       /* DAT_0010000e */
extern uint64_t sptm_xnu_exc_return;             /* *DAT_00095468 (indirect) */
extern uint64_t sptm_exc_return_el2;             /* DAT_00094928 */
extern uint64_t sptm_exc_return_el1;             /* DAT_00094930 */
extern uint64_t sptm_exc_return_el0;             /* DAT_00094920 */
extern volatile uint8_t sptm_sve_present;        /* DAT_00095d01 */

/* ------------------------------------------------------------------ *
 * FUN_0009c2c8 @ 0x0009c2c8   (est. sptm_wait_forever)
 * Ghidra: noreturn void FUN_0009c2c8(void)
 * Idle/event-wait spin used as a dead-end by the exception/panic handlers:
 * masks nothing, simply waits-for-event in a tight loop forever. Reached
 * from the SPTM exception handlers when no forward progress is possible.
 * Confidence: medium
 * Notes: Ghidra renders the loop as `do { WaitForEvent(); } while(true);`
 *   (WFE). No state transition is attempted. */
static void sptm_wait_forever(void) __attribute__((noreturn));
static void sptm_wait_forever(void)
{
    for (;;) {
        sptm_wfe();  /* WaitForEvent */
    }
}

/* ------------------------------------------------------------------ *
 * FUN_000a0298 @ 0x000a0298   (est. sptm_dispatch_state_event5_clr)
 * Ghidra: void FUN_000a0298(undefined8 param_1, code *param_2)
 * State-transition handler: invokes the given sub-handler, switches to the
 * EL1 stack pointer, waits for the hop depth to drop to 1, clears the
 * saved dispatch-id slot (+0xa38), and transitions on event 5.
 * Confidence: medium
 * Notes: The two empty `do{}while(1<depth)` loops are Ghidra's rendering of
 *   a wait-for-depth-==-1 spin on the per-CPU +0xa68 hop counter. */
static void sptm_dispatch_state_event5_clr(void (*sub)(void), uint64_t arg)
{
    uint64_t *cpu;

    sub();
    cpu = sptm_cpu();
    sptm_write_spsel(1);
    uint64_t depth = cpu[0xa68 / 8] - 1;
    while (depth > 1) { sptm_wfe(); }
    while (depth > 1) { sptm_wfe(); }
    cpu[0xa38 / 8] = 0;
    sptm_dispatch_transition(5, 0);
}

/* ------------------------------------------------------------------ *
 * FUN_000a0360 @ 0x000a0360   (est. sptm_dispatch_state_event5_swap)
 * Ghidra: void FUN_000a0360(undefined8 param_1, code *param_2)
 * State-transition handler: like event5_clr but moves the saved dispatch-id
 * slot +0xa40 down into +0xa38 and zeroes +0xa40 before transitioning on
 * event 5 (rotates the saved-id ring).
 * Confidence: medium
 * Notes: +0xa40 is the "previous dispatch id" slot; +0xa38 the current one. */
static void sptm_dispatch_state_event5_swap(void (*sub)(void), uint64_t arg)
{
    uint64_t *cpu;

    sub();
    cpu = sptm_cpu();
    sptm_write_spsel(1);
    uint64_t depth = cpu[0xa68 / 8] - 1;
    while (depth > 1) { sptm_wfe(); }
    while (depth > 1) { sptm_wfe(); }
    cpu[0xa38 / 8] = cpu[0xa40 / 8];
    cpu[0xa40 / 8] = 0;
    sptm_dispatch_transition(5, 0);
}

/* ------------------------------------------------------------------ *
 * FUN_000a03d4 @ 0x000a03d4   (est. sptm_dispatch_call_with_state)
 * Ghidra: void FUN_000a03d4(code *param_1, long param_2)
 * Calls a state handler with the DAIF interrupt-mask restored from the
 * current (depth-selected) saved context, saving and restoring the per-CPU
 * argument/exception registers (+0xa80..+0xaa8) and the guest arg block
 * (+0xa70). When param_2==0 the DAIF mask is derived from the saved SPSR
 * (+0xb0 of the active context bank) with bit 0x200 forced on.
 * Confidence: medium
 * Notes: The 16-byte return of (*param_1)() is stored at +0xa70 (two
 *   uint64: x0/x1). DAT offsets as decompiled. */
static void sptm_dispatch_call_with_state(uint64_t (*handler)(uint64_t, uint64_t),
                                          uint64_t mode)
{
    uint64_t *cpu = sptm_cpu();
    uint64_t saved0 = cpu[0xa80 / 8], saved1 = cpu[0xa88 / 8];
    uint64_t saved2 = cpu[0xa90 / 8], saved3 = cpu[0xa98 / 8];
    uint64_t saved4 = cpu[0xaa0 / 8], saved5 = cpu[0xaa8 / 8];
    uint64_t daif_mask;

    if (mode == 0) {
        uint64_t depth = cpu[0xa68 / 8] - 1;
        while (depth > 1) { sptm_wfe(); }
        uint64_t *bank = (depth == 1) ? (uint64_t *)((uint8_t *)cpu + 0xb68)
                                      : (uint64_t *)((uint8_t *)cpu + 0xab0);
        daif_mask = (bank[0xb0 / 8] & 0x3c0) | 0x200;
    } else {
        daif_mask = 0x3c0;  /* mask all interrupts */
    }

    sptm_write_daif(daif_mask);
    uint64_t ret0 = handler(cpu[0xa70 / 8], cpu[0xa78 / 8]);
    sptm_write_daif(sptm_read_daif() | 0x3c0);

    cpu = sptm_cpu();
    cpu[0xa70 / 8] = ret0;
    cpu[0xa78 / 8] = ((uint64_t *)((uint8_t *)&ret0))[1];
    cpu[0xa80 / 8] = saved0; cpu[0xa88 / 8] = saved1;
    cpu[0xa90 / 8] = saved2; cpu[0xa98 / 8] = saved3;
    cpu[0xaa0 / 8] = saved4; cpu[0xaa8 / 8] = saved5;
}

/* ------------------------------------------------------------------ *
 * FUN_000a0594 @ 0x000a0594   (est. sptm_dispatch_event11)
 * Ghidra: void FUN_000a0594(void)
 * Trivial state-transition handler: transition on event 0xb with arg 0.
 * Confidence: medium */
static void sptm_dispatch_event11(void)
{
    sptm_dispatch_transition(0xb, 0);
}

/* ------------------------------------------------------------------ *
 * FUN_000a05dc @ 0x000a05dc   (est. sptm_invalid_genter_handler)
 * Ghidra: void FUN_000a05dc(void)
 * Noreturn handler for an invalid GENTER: reports the bad guarded entry and
 * never returns (the trailing `return` is unreachable).
 * Confidence: high (FUN_000f89b4 is the SPTM "Invalid GENTER" panic). */
static void sptm_invalid_genter_handler(void) __attribute__((noreturn));
static void sptm_invalid_genter_handler(void)
{
    sptm_invalid_genter_panic();
}

/* ------------------------------------------------------------------ *
 * FUN_000a0abc @ 0x000a0abc   (est. sptm_dispatch_route_entry)
 * Ghidra: void FUN_000a0abc(void)
 * Thin entry that forwards the guarded-call selector/arg (which ride in x0/x1,
 * not modeled as C parameters) to sptm_dispatch_route, which derives the
 * transition event and performs the guarded transition.
 * Confidence: low
 * Notes: register passthrough (x0/x1) — the decompiler drops the arguments. */
static void sptm_dispatch_route_entry(void)
{
    /* selector/arg forwarded via registers (x0/x1) — see FUN_000e74e0. */
    sptm_dispatch_route(/* selector */ 0, /* arg */ 0);
}

/* ------------------------------------------------------------------ *
 * FUN_000a0adc @ 0x000a0adc   (est. sptm_exception_return)
 * Ghidra: void FUN_000a0adc(undefined8 param_1, ulong param_2)
 * The unified guest exception-return handler: restores the full guest GP +
 * FP/SIMD (q0-q31) register file, the exception registers (ELR/SPSR/SP/ESR/
 * FAR/FPSR/FPCR) from the saved per-CPU context, sets ELR_EL1 to the XNU
 * exception-return handler (*DAT_00095468), and ERETs back to EL1.
 *   param_2&3 == 3: (re)store the EL2/guest exception regs, then GP+FP file.
 *   param_2&3 == 1: restore EL1 debug/control regs only.
 *   param_2&3 == 2: save the stage-2 state (sptm_stage2_state_save).
 *   param_2&3 == 0: capture ESR_EL1/FAR_EL1.
 * Called from the vector-type dispatcher FUN_000e7100 after validating the
 * vector type and the xnu exc-return handler.
 * Confidence: low (assembly-level reconstruction; decompiler collapses the
 *   ERET tail to "bad instruction").
 * Notes: GP regs restored from cpu+0xa30+0x1f0; FP from cpu+0xa30+0x310;
 *   fpsr/fpcr from cpu+0xf40/+0xf44; spsr from active context bank +0xb0;
 *   sp_el0 from bank +0xa0. The 31-q-register file restore is rendered as a
 *   comment (plain LDP q0..q31). */
static void sptm_exception_return(uint64_t target_elr, uint64_t mode) __attribute__((noreturn));
static void sptm_exception_return(uint64_t target_elr, uint64_t mode)
{
    uint64_t *cpu = sptm_cpu();
    uint64_t *base = (uint64_t *)((uint8_t *)cpu + 0xa30);
    uint64_t sel = mode & 3;

    if (sel == 3) {
        /* Capture the current exception return state, then switch to the
         * saved guest exception state. */
        uint64_t elr = __builtin_arm_rsr64("elr_el1");
        (void)elr;
        sptm_write_elr_el1(elr);
        sptm_write_spsr_el1(__builtin_arm_rsr64("spsr_el1"));
        sptm_write_esr_el1(__builtin_arm_rsr64("esr_el1"));
        sptm_write_far_el1(__builtin_arm_rsr64("far_el1"));
        sptm_write_spsr_el1(sptm_read_currentel() | 0x4003c1);
        sptm_write_sp_el0(cpu[0xd18 / 8]);
        sptm_write_fpsr((uint64_t)*(uint32_t *)((uint8_t *)cpu + 0xf40));
        sptm_write_fpcr((uint64_t)*(uint32_t *)((uint8_t *)cpu + 0xf44));
        /* GP + q0..q31 restored from base+0x1f0 (see function Notes). */
    } else if (sel == 1) {
        uint64_t *dbg = (uint64_t *)((uint8_t *)cpu + 0xf88);
        __builtin_arm_wsr64("s3_6_c15_c1_5", dbg[0]);       /* (3,6,0xf,1,5) */
        sptm_write_mdscr_el1(dbg[1]);
        __builtin_arm_wsr64("s3_1_c15_c1_5", dbg[2]);       /* (3,1,0xf,1,5) */
        __builtin_arm_wsr64("s3_4_c15_c0_4", dbg[3]);       /* (3,4,0xf,0,4) */
        sptm_write_sctlr_el1(dbg[4]);
        sptm_write_tcr_el1(dbg[5]);
        __builtin_arm_wsr64("s3_6_c15_c0_5", dbg[6]);       /* (3,6,0xf,0,5) */
    } else if (sel == 2) {
        sptm_stage2_state_save(base, 2, (mode >> 2) & 1);
    } else {  /* sel == 0 */
        sptm_write_esr_el1(__builtin_arm_rsr64("esr_el1"));
        sptm_write_far_el1(__builtin_arm_rsr64("far_el1"));
    }

    sptm_write_elr_el1(target_elr);

    /* Wait for hop depth to reach 1, then drop it by one. */
    while (cpu[0xa68 / 8] != 1) { sptm_wfe(); }
    uint64_t depth = cpu[0xa68 / 8] - 1;
    cpu[0xa68 / 8] = depth;
    while (depth > 1) { sptm_wfe(); }
    uint64_t *bank = (depth == 1) ? (uint64_t *)((uint8_t *)cpu + 0xb68)
                                  : (uint64_t *)((uint8_t *)cpu + 0xab0);
    sptm_write_spsr_el1(bank[0xb0 / 8]);
    sptm_write_sp_el0(bank[0xa0 / 8]);
    sptm_write_elr_el1(sptm_xnu_exc_return);
    sptm_write_spsr_el1(sptm_read_currentel() | 0x4003c1);
    __builtin_arm_wsr64("spsel", 1);
    sptm_eret();  /* never returns */
}

/* ------------------------------------------------------------------ *
 * FUN_000a0d80 @ 0x000a0d80   (est. sptm_exception_return_save)
 * Ghidra: void FUN_000a0d80(void)
 * Saves the EL1 debug/control registers into the per-CPU context
 * (+0xf88..+0xfb8), programs the debug/MDSCR/SCTLR/TCR control fields for
 * exception delivery, sets ELR_EL1 to DAT_00094928, then ERETs.
 * Confidence: low (decompiler shows the ERET tail truncated). */
static void sptm_exception_return_save(void) __attribute__((noreturn));
static void sptm_exception_return_save(void)
{
    uint64_t *cpu = sptm_cpu();

    sptm_write_elr_el1(sptm_exc_return_el2);
    sptm_write_spsr_el1(0x3c0);

    cpu[0xf88 / 8] = __builtin_arm_rsr64("s3_6_c15_c1_5");   /* (3,6,0xf,1,5) */
    __builtin_arm_wsr64("s3_6_c15_c1_5", 0x8004000c8080);
    cpu[0xf90 / 8] = __builtin_arm_rsr64("mdscr_el1");
    sptm_write_mdscr_el1(0x1000);
    cpu[0xf98 / 8] = __builtin_arm_rsr64("s3_1_c15_c1_5");   /* (3,1,0xf,1,5) */
    __builtin_arm_wsr64("s3_1_c15_c1_5", 1);
    uint64_t ctl = __builtin_arm_rsr64("s3_4_c15_c0_4");     /* (3,4,0xf,0,4) */
    cpu[4000 / 8] = ctl;
    __builtin_arm_wsr64("s3_4_c15_c0_4", ctl & 0xffffffffffffffefULL);
    uint64_t sctlr = __builtin_arm_rsr64("sctlr_el1");
    cpu[0xfa8 / 8] = sctlr;
    sptm_write_sctlr_el1(sctlr | 0xc8002000);
    uint64_t tcr = __builtin_arm_rsr64("tcr_el1");
    cpu[0xfb0 / 8] = tcr;
    sptm_write_tcr_el1(tcr & 0xfeffffffffffffffULL);
    cpu[0xfb8 / 8] = __builtin_arm_rsr64("s3_6_c15_c0_5");   /* (3,6,0xf,0,5) */
    __builtin_arm_wsr64("s3_6_c15_c0_5", 0);

    sptm_eret();  /* never returns */
}

/* ------------------------------------------------------------------ *
 * FUN_000a10e0 @ 0x000a10e0   (est. sptm_txm_entry)
 * Ghidra: void FUN_000a10e0(undefined8 param_1)
 * TXM entry stub: switches to EL1 sp, stores the frame pointer / link
 * register just below the context sp, then transitions on event 0 with
 * param_1 as the argument (the TXM guarded entry).
 * Confidence: low (thin wrapper; event-0 domain entry). */
static void sptm_txm_entry(uint64_t arg)
{
    uint64_t *cpu = sptm_cpu();

    sptm_write_spsel(1);
    uint64_t *sp = (uint64_t *)cpu[0xa50 / 8];
    sp[-2] = (uint64_t)__builtin_frame_address(0);
    sp[-1] = (uint64_t)__builtin_return_address(0);

    sptm_dispatch_transition(0, arg);
}

/* ------------------------------------------------------------------ *
 * FUN_000a11e0 @ 0x000a11e0   (est. sptm_sk_entry_early)
 * Ghidra: void FUN_000a11e0(undefined8 param_1)
 * SK entry stub: like sptm_txm_entry but transitions on event 1 with
 * param_1 as the argument.
 * Confidence: low */
static void sptm_sk_entry_early(uint64_t arg)
{
    uint64_t *cpu = sptm_cpu();

    sptm_write_spsel(1);
    uint64_t *sp = (uint64_t *)cpu[0xa50 / 8];
    sp[-2] = (uint64_t)__builtin_frame_address(0);
    sp[-1] = (uint64_t)__builtin_return_address(0);

    sptm_dispatch_transition(1, arg);
}

/* ------------------------------------------------------------------ *
 * FUN_000a121c @ 0x000a121c   (est. sptm_exception_return_el1)
 * Ghidra: void FUN_000a121c(void)
 * Sets ELR_EL1 to DAT_00094930, SPSR to CurrentEL|0x3c1, SPSel=0, then ERETs.
 * Confidence: low (ERET tail truncated by decompiler). */
static void sptm_exception_return_el1(void) __attribute__((noreturn));
static void sptm_exception_return_el1(void)
{
    sptm_cpu();
    sptm_write_elr_el1(sptm_exc_return_el1);
    sptm_write_spsr_el1(sptm_read_currentel() | 0x3c1);
    __builtin_arm_wsr64("spsel", 0);
    sptm_eret();  /* never returns */
}

/* ------------------------------------------------------------------ *
 * FUN_000a1318 @ 0x000a1318   (est. sptm_exception_return_el0)
 * Ghidra: undefined8 FUN_000a1318(undefined8 param_1)
 * Restores EL1 debug/control registers from the per-CPU context (via
 * sptm_debug_state_restore(1, cpu+0xa30)), sets ELR_EL1 to DAT_00094920,
 * SPSR to 0x3c5, SPSel=1, then ERETs back to EL0.
 * Confidence: low */
static uint64_t sptm_exception_return_el0(uint64_t arg)
{
    uint64_t *cpu = sptm_cpu();

    sptm_write_elr_el1(sptm_exc_return_el0);
    sptm_write_spsr_el1(0x3c5);
    __builtin_arm_wsr64("spsel", 1);
    sptm_debug_state_restore(1, (uint8_t *)cpu + 0xa30);
    sptm_eret();  /* never returns */
    return arg;   /* unreachable */
}

/* ------------------------------------------------------------------ *
 * FUN_000a1374 @ 0x000a1374   (est. sptm_guest_exit_handoff)
 * Ghidra: void FUN_000a1374(undefined8, long, undefined8, char)
 * The guest-exit / guarded-return handoff: records the exit reason and args
 * into the SPTM exit record (DAT_000a5028), resolves the return PC through
 * the PAPT, checks the UAT handoff-region magic (DAT_0010000c/0x10) to pick
 * the context-save bank, then transitions on event 9 (or 0xb when the
 * handoff magic is stale) to return to the lower guarded level. On the
 * EL1-sp path it instead writes the state/selector fields and spins waiting
 * for the handoff (WFI loop) with a DSB.
 * Confidence: low (complex register/stack manipulation; decompiler drops the
 *   stack-frame writes).
 * Notes: DAT_0010000c is the UAT instance handoff-region magic (compared
 *   against the per-CPU copy at uat_instance->handoff_region->mi+10); a
 *   DMB ISH is taken when the magic matches. */
static void sptm_guest_exit_handoff(uint64_t reason, uint64_t mode,
                                    uint64_t arg, uint8_t sel) __attribute__((noreturn));
static void sptm_guest_exit_handoff(uint64_t reason, uint64_t mode,
                                    uint64_t arg, uint8_t sel)
{
    uint64_t *cpu;
    uint64_t *rec = (uint64_t *)sptm_exit_record;

    if (sptm_exit_record != 0) {
        rec[0x10 / 8] = 1;
        rec[0x38 / 8] = reason;
        rec[0x40 / 8] = arg;
        if (sptm_cur_sp != 0) {
            /* Store fp/lr/sp under the context sp and resolve the return PC
             * through the PAPT into rec+0x38. */
            ((uint64_t *)sptm_cur_sp)[-2] = reason;
            ((uint64_t *)sptm_cur_sp)[-4] = (uint64_t)rec;
            ((uint64_t *)sptm_cur_sp)[-3] = (uint64_t)__builtin_return_address(0);
            rec[0x38 / 8] = sptm_papt_to_phys(reason);
        }
    }

    if (__builtin_arm_rsr64("spsel") == 1) {  /* spsel==1 → EL1-sp path */
        /* EL1-sp path: record the state/selector, then spin (WFI) until the
         * handoff completes. */
        sptm_dsb_sy();
        for (;;) sptm_wfe();
    }

    /* EL0-sp path: save fp/lr/sp, then transition to the lower guarded level. */
    sptm_write_daif(sptm_read_daif() | 0x3c0);
    sptm_write_spsel(1);
    cpu = sptm_cpu();
    uint64_t *sp = (uint64_t *)cpu[0xa50 / 8];
    uint16_t magic = sptm_handoff_magic;
    int magic_ok;
    if (magic == 0x8000) {
        /* initialize from the per-CPU uat handoff copy */
        magic_ok = 0;
        sptm_dmb_ish();
    } else {
        magic_ok = 1;
    }
    if (sptm_handoff_sel == 0xffff) {
        sptm_handoff_sel = sel;
    }
    uint64_t event = magic_ok ? 0xb : 9;
    sp[-2] = (uint64_t)__builtin_frame_address(0);
    sp[-1] = (uint64_t)__builtin_return_address(0);
    sptm_dispatch_transition(event, (uint64_t)sp);
    for (;;) {} /* unreachable */
}

/* ------------------------------------------------------------------ *
 * FUN_000a21b4 @ 0x000a21b4   (est. sptm_panic_bad_hcr)
 * Ghidra: void FUN_000a21b4(void)
 * Noreturn panic: checks hcr_el2 against the expected SPTM value
 * (0x100030480000000); records a reason (2=expected, 1=unexpected) into the
 * exit record +0x40, formats the dispatch name, and panics with the
 * "s %s %s at pc 0x%016llx lr 0x..." message.
 * Confidence: medium */
static void sptm_panic_bad_hcr(void) __attribute__((noreturn));
static void sptm_panic_bad_hcr(void)
{
    uint64_t reason;
    uint64_t hcr = sptm_read_hcr_el2();

    if (hcr == 0x100030480000000ULL) {
        reason = 2;
        (void)__builtin_arm_rsr64("spsr_el1");  /* value discarded (decompiled read) */
    } else {
        reason = 1;
    }
    if (sptm_exit_record != 0) {
        sptm_exit_record[0x40 / 8] = reason;
    }
    uint64_t *cpu = sptm_cpu();
    sptm_panic_str(sptm_dispatch_name(cpu[0xa38 / 8]));
}

/* ------------------------------------------------------------------ *
 * FUN_000a2318 @ 0x000a2318   (est. sptm_dispatch_event2)
 * Ghidra: void FUN_000a2318(void)
 * Trivial state-transition handler: transition on event 2 with arg 0.
 * Confidence: medium */
static void sptm_dispatch_event2(void)
{
    sptm_dispatch_transition(2, 0);
}

/* ------------------------------------------------------------------ *
 * FUN_000a235c @ 0x000a235c   (est. sptm_dispatch_event7_ctx)
 * Ghidra: void FUN_000a235c(long param_1, undefined8 param_2, ulong param_3)
 * State-transition handler on event 7: stores the incoming arg into the
 * context +0x550, waits for the hop depth to drop to 1, copies the
 * depth-selected bank's x19/x20 slots into the context save (+0x2d8), saves
 * the link register at +0x2f0, and transitions with the event flag
 * `(param_3 & 1) << 2 | 2`.
 * Confidence: medium */
static void sptm_dispatch_event7_ctx(uint64_t *ctx, uint64_t arg, uint64_t flag)
{
    ctx[0x550 / 8] = arg;
    uint64_t depth = ctx[0x38 / 8] - 1;
    while (depth > 1) { sptm_wfe(); }
    uint64_t *bank = (depth == 1) ? (uint64_t *)((uint8_t *)ctx + 0x138)
                                  : (uint64_t *)((uint8_t *)ctx + 0x80);
    uint64_t b0 = bank[0x90 / 8];
    uint64_t b1 = bank[0x98 / 8];
    ctx[0x2f0 / 8] = (uint64_t)__builtin_return_address(0);
    ctx[0x2d8 / 8] = b0;
    ctx[0x2e0 / 8] = b1;
    sptm_dispatch_transition(7, ((flag & 1) << 2) | 2);
}

/* ------------------------------------------------------------------ *
 * FUN_000a2458 @ 0x000a2458   (est. sptm_dispatch_event2_b)
 * Ghidra: void FUN_000a2458(void)
 * Trivial state-transition handler: transition on event 2 with arg 0.
 * Confidence: medium */
static void sptm_dispatch_event2_b(void)
{
    sptm_dispatch_transition(2, 0);
}

/* ------------------------------------------------------------------ *
 * FUN_000a249c @ 0x000a249c   (est. sptm_guest_state_restore)
 * Ghidra: void FUN_000a249c(long, 8 x undefined8)
 * Restores the guest EL1 debug/control registers (+0x558..+0x588) and the
 * incoming argument block (param_2..param_9) into the per-CPU context
 * (+0x40..+0x78), then transitions on event 5. Companion to the exception
 * state save.
 * Confidence: medium */
static void sptm_guest_state_restore(uint64_t *ctx, uint64_t x1, uint64_t x2,
                                     uint64_t x3, uint64_t x4, uint64_t x5,
                                     uint64_t x6, uint64_t x7, uint64_t x8)
{
    ctx[0x40 / 8] = x1; ctx[0x48 / 8] = x2;
    ctx[0x50 / 8] = x3; ctx[0x58 / 8] = x4;
    ctx[0x60 / 8] = x5; ctx[0x68 / 8] = x6;
    ctx[0x70 / 8] = x7; ctx[0x78 / 8] = x8;

    __builtin_arm_wsr64("s3_6_c15_c1_5", ctx[0x558 / 8]);   /* (3,6,0xf,1,5) */
    sptm_write_mdscr_el1(ctx[0x560 / 8]);
    __builtin_arm_wsr64("s3_1_c15_c1_5", ctx[0x568 / 8]);   /* (3,1,0xf,1,5) */
    __builtin_arm_wsr64("s3_4_c15_c0_4", ctx[0x570 / 8]);   /* (3,4,0xf,0,4) */
    sptm_write_sctlr_el1(ctx[0x578 / 8]);
    sptm_write_tcr_el1(ctx[0x580 / 8]);
    __builtin_arm_wsr64("s3_6_c15_c0_5", ctx[0x588 / 8]);   /* (3,6,0xf,0,5) */

    sptm_dispatch_transition(5, 0);
}

/* ------------------------------------------------------------------ *
 * FUN_000a2530 @ 0x000a2530   (est. sptm_dispatch_event7)
 * Ghidra: void FUN_000a2530(void)
 * State-transition handler: transition on event 7 with arg 1.
 * Confidence: medium */
static void sptm_dispatch_event7(void)
{
    sptm_dispatch_transition(7, 1);
}

/* ------------------------------------------------------------------ *
 * FUN_000a259c @ 0x000a259c   (est. sptm_dispatch_event5)
 * Ghidra: void FUN_000a259c(void)
 * State-transition handler: transition on event 5 with arg 0.
 * Confidence: medium */
static void sptm_dispatch_event5(void)
{
    sptm_dispatch_transition(5, 0);
}

/* ------------------------------------------------------------------ *
 * FUN_000a2718 @ 0x000a2718   (est. sptm_panic_dispatch)
 * Ghidra: void FUN_000a2718(void)
 * Noreturn panic: formats the current dispatch name (per-CPU +0xa38) and
 * panics with the "at pc / lr" message. Same body as FUN_000a28d4.
 * Confidence: medium */
static void sptm_panic_dispatch(void) __attribute__((noreturn));
static void sptm_panic_dispatch(void)
{
    uint64_t *cpu = sptm_cpu();
    sptm_panic_str(sptm_dispatch_name(cpu[0xa38 / 8]));
}

/* ------------------------------------------------------------------ *
 * FUN_000a28d4 @ 0x000a28d4   (est. sptm_panic_dispatch_b)
 * Ghidra: void FUN_000a28d4(void)
 * Noreturn panic, byte-identical to FUN_000a2718.
 * Confidence: medium */
static void sptm_panic_dispatch_b(void) __attribute__((noreturn));
static void sptm_panic_dispatch_b(void)
{
    uint64_t *cpu = sptm_cpu();
    sptm_panic_str(sptm_dispatch_name(cpu[0xa38 / 8]));
}

/* ------------------------------------------------------------------ *
 * FUN_000a28fc @ 0x000a28fc   (est. sptm_restore_full_context)
 * Ghidra: void FUN_000a28fc(long param_1)
 * Full register-context restore + ERET: reloads sp_el0/sp_el1, mdscr, the
 * four TPIDR registers, par/csselr, the (3,6,0xf,2,5)/(3,4,0xf,0xc,0) control
 * regs, the optional SVE/AMU register (when DAT_00095d01 != 0), ELR_EL1,
 * SPSR_EL1, SPSel, the guest exception return regs, cptr_el2, and — when the
 * cptr bit 20 (FP/SIMD) is set — fpsr/fpcr plus the full SVE Z0-Z31/P0-P15
 * register file from the context (+0x1c0 / +0x9c0), then ERETs.
 * Confidence: low (assembly-level reconstruction; decompiler truncates the
 *   ERET and renders the SVE loads as SVE_ldr pseudofunctions).
 * Notes: the Z/P predicate file (32x32B Z + 16x P) is loaded from
 *   param_1+0x1c0 (Z) and param_1+0x9c0 (P). */
static void sptm_restore_full_context(uint64_t *ctx) __attribute__((noreturn));
static void sptm_restore_full_context(uint64_t *ctx)
{
    sptm_write_spsel(1);
    sptm_cpu();
    sptm_write_sp_el0(ctx[0x38 / 8]);
    sptm_write_sp_el1(ctx[0x40 / 8]);
    sptm_write_spsel(0);
    sptm_write_mdscr_el1(ctx[0x48 / 8]);
    sptm_write_tpidr_el1(ctx[0x50 / 8]);
    sptm_write_tpidr_el0(ctx[0x58 / 8]);
    sptm_write_tpidrro_el0(ctx[0x60 / 8]);
    sptm_write_par_el1(ctx[0x68 / 8]);
    sptm_write_csselr_el1(ctx[0x70 / 8]);
    __builtin_arm_wsr64("s3_6_c15_c2_5", ctx[0x78 / 8]);     /* (3,6,0xf,2,5) */
    __builtin_arm_wsr64("s3_4_c15_c12_0", ctx[0x80 / 8]);    /* (3,4,0xf,0xc,0) */
    if (sptm_sve_present != 0) {
        __builtin_arm_wsr64("s3_3_c13_c0_7", ctx[0x88 / 8]); /* (3,3,0xd,0,7) */
    }
    sptm_write_elr_el1(ctx[0xa48 / 8]);
    uint64_t spsr = ctx[0xa40 / 8];
    if (((uint32_t)spsr >> 3) & 1) {
        spsr = (spsr & ~1ULL) | 0x100000;
    }
    __builtin_arm_wsr64("spsr_el1", spsr);
    sptm_write_sp_el0(ctx[0xa50 / 8]);   /* (3,6,0xf,10,4) = sp_el0 */
    __builtin_arm_wsr64("s3_3_c13_c0_5", ctx[0x1a0 / 8]);    /* (3,3,0xd,0,5) */
    __builtin_arm_wsr64("s3_0_c1_c2_4", ctx[0x1a8 / 8]);     /* (3,0,1,2,4) */
    sptm_write_cptr_el2(ctx[0x90 / 8]);
    uint32_t cptr = (uint32_t)ctx[0x90 / 8];
    if ((cptr >> 0x14) & 1) {
        sptm_write_fpsr(ctx[0x98 / 8]);
        if (ctx[0xa0 / 8] != sptm_read_fpcr()) {
            sptm_write_fpcr(ctx[0xa0 / 8]);
        }
        /* SVE Z0-Z31 (ctx+0x1c0) and P0-P15 (ctx+0x9c0) restored here; the
         * decompiler renders these as SVE_ldr pseudofunctions. */
        if (((cptr >> 0x18) & 1) &&
            (__builtin_arm_wsr64("s3_3_c4_c2_2", ctx[0x1b0 / 8]),
             (ctx[0x1b0 / 8] & 1) != 0)) {
            /* Z0..Z31 <- ctx+0x1c0; P0..P15 <- ctx+0x9c0 (see Notes). */
        }
    }
    sptm_eret();  /* never returns */
}
