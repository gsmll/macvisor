/* Recreated from cl4_kernel.raw (cL4 Secure Kernel, GL1, arm64e, image base 0) —
 * the cL4 microkernel (cL4 (679.100.61)). Ground truth: Ghidra FUN_ names +
 * addresses. Names use seL4/cL4 vocabulary and are estimates unless a
 * string/header matches. English-first transcription of the SKR72 true-gap
 * slice (0x006834f0..0x00685ca0, 120 functions). */
#include <stdint.h>
#include <stddef.h>

/* ------------------------------------------------------------------ */
/* Shared kernel primitives (extern; defined elsewhere in the SK tree) */
/* ------------------------------------------------------------------ */

/* CallSupervisor(n): cL4 supervisor-call dispatch (svc #n). */
extern void sk_svc(int num);
/* LOAcquire()/LORelease(): lightweight-lock acquire/release on an implicit global. */
extern void sk_lox_acquire(void);
extern void sk_lox_release(void);
/* Reads the per-thread read-only TLS base (tpidrro_el0). */
extern uint8_t *sk_tls_base(void);
/* FUN_00661318: returns the current TCB pointer. */
extern uint64_t sk_current_tcb(void);

/* Panic / abort family. */
extern void sk_panic_impl(uint64_t cpu, uint64_t code, void *sp);  /* FUN_0065c310 */
extern void sk_panic(uint64_t code);                               /* FUN_006833d4 */
extern void sk_abort_fatal(uint64_t code);                         /* FUN_0064e030 */
extern void sk_abort_code(uint64_t a, uint64_t code);              /* FUN_0065c2f0 */
extern void sk_abort_simple(uint64_t code);                        /* FUN_0065c288 */
extern void sk_warn(uint64_t code);                                /* FUN_0067b280 */

/* Logging primitives. */
extern void     sk_log_begin(uint64_t ctx, uint64_t msg);          /* FUN_0067d1f0 */
extern uint64_t sk_log_flush(char nl, uint64_t ctx);               /* FUN_0067d3f8 */
extern void     sk_log_puts(uint64_t str);                         /* FUN_0067d72c */
extern uint32_t sk_log_fmt(uint64_t a, uint64_t fmt);              /* FUN_0067d798 */
extern void     sk_log_nl(uint64_t n);                             /* FUN_0067d82c */
extern void     sk_log_msg(uint64_t ctx, uint64_t fmt, void *arg); /* FUN_0067d83c */
extern uint64_t sk_log_poll(uint64_t a, uint64_t b, uint64_t c);   /* FUN_0067f660 */

/* Object / capability / frame management. */
extern void     sk_cap_release(uint64_t obj);                      /* FUN_0064eee8 */
extern void     sk_push(uint64_t a, uint64_t b);                   /* FUN_0064f2bc */
extern void     sk_pop(uint64_t a, uint64_t b);                    /* FUN_006507fc */
extern void     sk_pop3(uint64_t a, uint64_t b);                   /* FUN_0066609c */
extern void     sk_alloc_frames(uint64_t a, int64_t b, uint32_t c, uint32_t d); /* FUN_006504a0 */
extern int64_t  sk_index_lookup(int64_t *tbl, uint64_t idx);       /* FUN_00650af8 */
extern void     sk_pool_release(uint64_t obj);                     /* FUN_0065beb4 */
extern void     sk_fault_report(uint64_t a, int64_t b, uint64_t msg, int c); /* FUN_0065bfa8 */
extern void     sk_lock_enter(void);                               /* FUN_0065c218 */
extern uint64_t sk_pool_alloc(uint64_t pool);                      /* FUN_0065c27c */
extern void     sk_thread_pause(void);                             /* FUN_0065cd38 */
extern void     sk_xt_release(uint64_t *o);                        /* FUN_0065d080 */
extern void     sk_unref(uint64_t o);                              /* FUN_0065eafc */
extern void     sk_unref2(uint64_t o);                             /* FUN_00660b20 */
extern void     sk_method_dispatch(uint64_t obj, uint64_t arg);    /* FUN_006832fc */
extern void     sk_frame_release(int64_t frame);                   /* FUN_006860f4 */

/* Context-switch helpers. */
extern void sk_ctx_save(void);                                     /* FUN_0065f428 */
extern void sk_ctx_restore(void);                                  /* FUN_0065f448 */
extern void sk_ctx_save_full(void);                                /* FUN_0065f454 */
extern void sk_ctx_pre(void);                                      /* FUN_006612c0 */
extern void sk_ctx_post(void);                                     /* FUN_006612e0 */
extern void sk_ctx_swap(void);                                     /* FUN_00662a40 */
extern void sk_lock_big(void);                                     /* FUN_006638d8 */
extern void sk_lock_med(void);                                     /* FUN_006638f8 */
extern void sk_lock_small(void);                                   /* FUN_00663910 */
extern void sk_unlock_all(void);                                   /* FUN_0066453c */
extern void sk_thread_lock(void);                                  /* FUN_00665cec */
extern void sk_thread_flags(uint64_t a, uint64_t b);               /* FUN_00665d0c */
extern void sk_thread_done(void);                                  /* FUN_00665d84 */
extern void sk_thread_probe(void);                                 /* FUN_00665d60 */
extern void sk_reg_put(uint64_t v);                                /* FUN_00665d20 */
extern void sk_reg_sel(uint64_t a, uint64_t b, uint64_t c);        /* FUN_00665d44 */
extern void sk_ctl_u64(uint64_t v);                                /* FUN_00665d70 */
extern void sk_reg_push(uint64_t *a, uint64_t *b);                 /* FUN_00665354 */
extern void sk_memcpy_tls(void *dst, void *src, uint64_t n);       /* FUN_00663c04 */

/* Error-code report printer (the FUN_0065d4e0..FUN_0065d700 family). */
extern void     sk_err_name(uint64_t str);                         /* FUN_0065d4e0 */
extern void     sk_err_lf(void);                                   /* FUN_0065d574 */
extern void     sk_err_tab(void);                                  /* FUN_0065d5a0 */
extern void     sk_err_color(uint64_t c);                          /* FUN_0065d5c8 */
extern void     sk_err_dash(void);                                 /* FUN_0065d5f0 */
extern void     sk_err_flush(void);                                /* FUN_0065d608 */
extern void     sk_err_end(void);                                  /* FUN_0065d620 */
extern void     sk_err_put(uint64_t c);                            /* FUN_0065d670 */
extern void     sk_err_put2(void);                                 /* FUN_0065d680 */
extern void     sk_err_sp(void);                                   /* FUN_0065d69c */
extern void     sk_err_x0(void);                                   /* FUN_0065d6b8 */
extern void     sk_err_x1(void);                                   /* FUN_0065d6d0 */
extern void     sk_err_x2(void);                                   /* FUN_0065d6e8 */
extern void     sk_err_x3(void);                                   /* FUN_0065d700 */
extern void     sk_err_reg(uint64_t v, uint64_t *r);               /* FUN_006645ec */

/* Misc kernel services. */
extern int64_t  sk_copy_out(uint64_t a, uint64_t n, uint64_t c, uint32_t d); /* FUN_0065fa24 */
extern uint64_t sk_read_u64(uint64_t a, uint64_t b, uint32_t c, int d);      /* FUN_0065fd4c */
extern uint64_t sk_cap_lookup(uint64_t a, void *b, void *c, int d, int e);   /* FUN_00661e1c */
extern void     sk_tag_export(uint64_t obj, uint32_t tag);         /* FUN_00662628 */
extern uint64_t sk_pool_lock(void *lock);                          /* FUN_0065db84 */
extern void     sk_pool_unlock(void *lock);                        /* FUN_0065de3c */
extern void     sk_flush_icache(void);                             /* FUN_0067cc18 */

/* Shared kernel globals. */
extern uint64_t sk_log_ctx;     /* _DAT_006b4368 : log context pointer */
extern uint64_t sk_fault_state; /* _DAT_006b5ed0 : fault-state cookie */
extern uint64_t sk_abort_flag;  /* _DAT_006b7350 */
extern uint64_t sk_stat_a;      /* _DAT_006fe794 : event counter */
extern uint64_t sk_stat_b;      /* _DAT_006fe790 : event counter */
extern uint32_t sk_meta_u32;    /* _DAT_006b6fd4 */
extern uint32_t sk_meta_u32b;   /* _DAT_006b6fd8 */
extern uint32_t sk_meta_u32c;   /* DAT_006b6fda */
extern uint8_t  sk_meta_b1;     /* DAT_006b6fdb */
extern uint8_t  sk_meta_b2;     /* DAT_006b6fd7 */
extern uint8_t  sk_meta_b3;     /* DAT_006b6fd6 */

/* Ghidra SoftwareBreakpoint(chk, addr) rendered as an assertion trap. */
__attribute__((noreturn))
static void sk_assert_trap(uint32_t chk, uint32_t addr)
{
    /* SoftwareBreakpoint(chk, addr) — assertion failure trap; never returns. */
    (void)chk; (void)addr;
    __builtin_trap();
}

/* ------------------------------------------------------------------ */
/* In-batch "log failure then abort" trio helpers (forward declared).  */
/* Each logs a message and halts; msg constant differs per function.   */
/* ------------------------------------------------------------------ */
static void sk_fault_log_abort_a(uint64_t ctx);  /* 0x00683ba8 */
static void sk_panic_5376(void);                 /* 0x00683c2c */
static void sk_fault_log_abort_b(uint64_t ctx);  /* 0x00683cc4 */
static void sk_panic_5a67(void);                 /* 0x00683e08 */
static void sk_panic_5e8f(void);                 /* 0x00683f00 */
static void sk_fault_log_abort_c(uint64_t ctx);  /* 0x006847a0 */
static void sk_fault_log_abort_d(uint64_t ctx);  /* 0x0068487c */
static void sk_fault_log_abort_e(uint64_t ctx);  /* 0x00684ca4 */
static void sk_fault_log_abort_f(uint64_t ctx);  /* 0x00684fdc */
static void sk_fault_log_abort_g(uint64_t ctx);  /* 0x006851bc */
static void sk_fault_log_abort_h(uint64_t ctx);  /* 0x00685470 */
static void sk_fault_log_abort_i(uint64_t ctx);  /* 0x006859b0 */
void sk_fault_log_abort_j(uint64_t ctx);  /* 0x00685acc */

/* ================================================================== */
/* 0x006834f0 .. 0x006839f8 : fatal-abort stubs (sk_abort_fatal path) */
/* ================================================================== */

/* FUN_006834f0 @ 0x006834f0
 * Ghidra: void FUN_006834f0(void)
 * Fatal-abort trap: jumps to the kernel fatal-error path with panic code
 * 0x6a4629. Never returns.
 * Confidence: high (decompile exact)
 * Notes: code 0x6a4629 is an unresolved panic-code reference (see FUN_0065c310). */
void sk_r72_6834f0_abort(void)
{
    sk_abort_fatal(0x6a4629);   /* FUN_0064e030 — does not return */
}

/* FUN_00683518 @ 0x00683518
 * Ghidra: void FUN_00683518(void)
 * Fatal-abort trap; identical to 0x006834f0 (panic code 0x6a4629).
 * Confidence: high
 * Notes: see 0x006834f0. */
void sk_r72_683518_abort(void)
{
    sk_abort_fatal(0x6a4629);
}

/* FUN_00683540 @ 0x00683540
 * Ghidra: void FUN_00683540(void)
 * Fatal-abort trap; panic code 0x6a4629.
 * Confidence: high
 * Notes: see 0x006834f0. */
void sk_r72_683540_abort(void)
{
    sk_abort_fatal(0x6a4629);
}

/* FUN_00683568 @ 0x00683568
 * Ghidra: void FUN_00683568(void)
 * Fatal-abort trap; panic code 0x6a4629.
 * Confidence: high */
void sk_r72_683568_abort(void)
{
    sk_abort_fatal(0x6a4629);
}

/* FUN_00683590 @ 0x00683590
 * Ghidra: void FUN_00683590(void)
 * Fatal-abort trap; panic code 0x6a4629.
 * Confidence: high */
void sk_r72_683590_abort(void)
{
    sk_abort_fatal(0x6a4629);
}

/* FUN_006835b8 @ 0x006835b8
 * Ghidra: void FUN_006835b8(void)
 * Fatal-abort trap; panic code 0x6a4629.
 * Confidence: high */
void sk_r72_6835b8_abort(void)
{
    sk_abort_fatal(0x6a4629);
}

/* FUN_006835e0 @ 0x006835e0
 * Ghidra: void FUN_006835e0(void)
 * Fatal-abort trap; panic code 0x6a4629.
 * Confidence: high */
void sk_r72_6835e0_abort(void)
{
    sk_abort_fatal(0x6a4629);
}

/* FUN_00683608 @ 0x00683608
 * Ghidra: void FUN_00683608(void)
 * Fatal-abort trap; panic code 0x6a4629.
 * Confidence: high */
void sk_r72_683608_abort(void)
{
    sk_abort_fatal(0x6a4629);
}

/* FUN_00683630 @ 0x00683630
 * Ghidra: void FUN_00683630(void)
 * Fatal-abort trap; panic code 0x6a4629.
 * Confidence: high */
void sk_r72_683630_abort(void)
{
    sk_abort_fatal(0x6a4629);
}

/* FUN_00683658 @ 0x00683658
 * Ghidra: void FUN_00683658(void)
 * Clears the abort flag (_DAT_006b7350) then takes the fatal-abort path
 * (panic code 0x6a4629).
 * Confidence: high
 * Notes: global _DAT_006b7350 rendered as sk_abort_flag. */
void sk_r72_683658_abort_clear(void)
{
    sk_abort_flag = 0;
    sk_abort_fatal(0x6a4629);   /* does not return */
}

/* FUN_00683688 @ 0x00683688
 * Ghidra: void FUN_00683688(void)
 * Fatal-abort trap; panic code 0x6a4629.
 * Confidence: high */
void sk_r72_683688_abort(void)
{
    sk_abort_fatal(0x6a4629);
}

/* FUN_006836b0 @ 0x006836b0
 * Ghidra: void FUN_006836b0(void)
 * Fatal-abort trap; panic code 0x6a4629.
 * Confidence: high */
void sk_r72_6836b0_abort(void)
{
    sk_abort_fatal(0x6a4629);
}

/* FUN_006836d8 @ 0x006836d8
 * Ghidra: void FUN_006836d8(void)
 * Fatal-abort trap; panic code 0x6a4629.
 * Confidence: high */
void sk_r72_6836d8_abort(void)
{
    sk_abort_fatal(0x6a4629);
}

/* FUN_00683700 @ 0x00683700
 * Ghidra: void FUN_00683700(void)
 * Fatal-abort trap; panic code 0x6a4629.
 * Confidence: high */
void sk_r72_683700_abort(void)
{
    sk_abort_fatal(0x6a4629);
}

/* FUN_00683728 @ 0x00683728
 * Ghidra: void FUN_00683728(void)
 * Fatal-abort trap; panic code 0x6a4629.
 * Confidence: high */
void sk_r72_683728_abort(void)
{
    sk_abort_fatal(0x6a4629);
}

/* FUN_00683750 @ 0x00683750
 * Ghidra: void FUN_00683750(void)
 * Fatal-abort trap; panic code 0x6a4629.
 * Confidence: high */
void sk_r72_683750_abort(void)
{
    sk_abort_fatal(0x6a4629);
}

/* FUN_00683778 @ 0x00683778
 * Ghidra: void FUN_00683778(void)
 * Fatal-abort trap; panic code 0x6a4629.
 * Confidence: high */
void sk_r72_683778_abort(void)
{
    sk_abort_fatal(0x6a4629);
}

/* FUN_006837a0 @ 0x006837a0
 * Ghidra: void FUN_006837a0(void)
 * Fatal-abort trap; panic code 0x6a4629.
 * Confidence: high */
void sk_r72_6837a0_abort(void)
{
    sk_abort_fatal(0x6a4629);
}

/* FUN_006837c8 @ 0x006837c8
 * Ghidra: void FUN_006837c8(void)
 * Fatal-abort trap; panic code 0x6a4629.
 * Confidence: high */
void sk_r72_6837c8_abort(void)
{
    sk_abort_fatal(0x6a4629);
}

/* FUN_006837f0 @ 0x006837f0
 * Ghidra: void FUN_006837f0(undefined8 *param_1, undefined8 param_2)
 * Looks up param_2 against the head entry *param_1 via sk_index_lookup, then
 * logs message 0x6a4b72.
 * Confidence: medium
 * Notes: lookup result discarded (lVar1); message id unresolved. */
void sk_r72_6837f0_lookup_log(uint64_t *head, uint64_t key)
{
    sk_index_lookup((int64_t *)head, key);      /* FUN_00650af8 */
    sk_log_puts(0x6a4b72);                      /* FUN_0067d72c */
}

/* FUN_00683840 @ 0x00683840
 * Ghidra: void FUN_00683840(long param_1, undefined8 param_2)
 * Looks up param_2 against the entry at param_1+0x10, then logs message
 * 0x6a4b43.
 * Confidence: medium */
void sk_r72_683840_lookup_log(int64_t node, uint64_t key)
{
    sk_index_lookup((int64_t *)(node + 0x10), key);   /* FUN_00650af8 */
    sk_log_puts(0x6a4b43);                            /* FUN_0067d72c */
}

/* FUN_00683890 @ 0x00683890
 * Ghidra: void FUN_00683890(void)
 * Fatal-abort trap; panic code 0x6a4629.
 * Confidence: high */
void sk_r72_683890_abort(void)
{
    sk_abort_fatal(0x6a4629);
}

/* FUN_006838b8 @ 0x006838b8
 * Ghidra: void FUN_006838b8(void)
 * Fatal-abort trap; panic code 0x6a4629.
 * Confidence: high */
void sk_r72_6838b8_abort(void)
{
    sk_abort_fatal(0x6a4629);
}

/* FUN_006838e0 @ 0x006838e0
 * Ghidra: void FUN_006838e0(void)
 * Fatal-abort trap; panic code 0x6a4629.
 * Confidence: high */
void sk_r72_6838e0_abort(void)
{
    sk_abort_fatal(0x6a4629);
}

/* FUN_00683908 @ 0x00683908
 * Ghidra: void FUN_00683908(void)
 * Fatal-abort trap; panic code 0x6a4629.
 * Confidence: high */
void sk_r72_683908_abort(void)
{
    sk_abort_fatal(0x6a4629);
}

/* FUN_00683930 @ 0x00683930
 * Ghidra: void FUN_00683930(void)
 * Fatal-abort trap; panic code 0x6a4629.
 * Confidence: high */
void sk_r72_683930_abort(void)
{
    sk_abort_fatal(0x6a4629);
}

/* FUN_00683958 @ 0x00683958
 * Ghidra: void FUN_00683958(void)
 * Fatal-abort trap; panic code 0x6a4629.
 * Confidence: high */
void sk_r72_683958_abort(void)
{
    sk_abort_fatal(0x6a4629);
}

/* FUN_00683980 @ 0x00683980
 * Ghidra: void FUN_00683980(void)
 * Fatal-abort trap; panic code 0x6a4629.
 * Confidence: high */
void sk_r72_683980_abort(void)
{
    sk_abort_fatal(0x6a4629);
}

/* FUN_006839a8 @ 0x006839a8
 * Ghidra: void FUN_006839a8(void)
 * Fatal-abort trap; panic code 0x6a4629.
 * Confidence: high */
void sk_r72_6839a8_abort(void)
{
    sk_abort_fatal(0x6a4629);
}

/* FUN_006839d0 @ 0x006839d0
 * Ghidra: void FUN_006839d0(void)
 * Fatal-abort trap; panic code 0x6a4629.
 * Confidence: high */
void sk_r72_6839d0_abort(void)
{
    sk_abort_fatal(0x6a4629);
}

/* FUN_006839f8 @ 0x006839f8
 * Ghidra: void FUN_006839f8(void)
 * Fatal-abort trap; panic code 0x6a4629.
 * Confidence: high */
void sk_r72_6839f8_abort(void)
{
    sk_abort_fatal(0x6a4629);
}

/* ================================================================== */
/* 0x00683a20 .. 0x00683ac0 : more fatal-abort stubs                 */
/* ================================================================== */

/* FUN_00683a20 @ 0x00683a20
 * Ghidra: void FUN_00683a20(void)
 * Fatal-abort trap; panic code 0x6a4629.
 * Confidence: high */
void sk_r72_683a20_abort(void)
{
    sk_abort_fatal(0x6a4629);
}

/* FUN_00683a48 @ 0x00683a48
 * Ghidra: void FUN_00683a48(void)
 * Fatal-abort trap; panic code 0x6a4629.
 * Confidence: high */
void sk_r72_683a48_abort(void)
{
    sk_abort_fatal(0x6a4629);
}

/* FUN_00683a70 @ 0x00683a70
 * Ghidra: void FUN_00683a70(void)
 * Fatal-abort trap; panic code 0x6a4629.
 * Confidence: high */
void sk_r72_683a70_abort(void)
{
    sk_abort_fatal(0x6a4629);
}

/* FUN_00683a98 @ 0x00683a98
 * Ghidra: void FUN_00683a98(void)
 * Fatal-abort trap; panic code 0x6a4629.
 * Confidence: high */
void sk_r72_683a98_abort(void)
{
    sk_abort_fatal(0x6a4629);
}

/* FUN_00683ac0 @ 0x00683ac0
 * Ghidra: void FUN_00683ac0(void)
 * Panic with code 0x6a4e7a (direct sk_panic path). Never returns.
 * Confidence: high */
void sk_r72_683ac0_panic(void)
{
    sk_panic(0x6a4e7a);   /* FUN_006833d4 — does not return */
}

/* FUN_00683ad8 @ 0x00683ad8
 * Ghidra: void FUN_00683ad8(void)
 * Panic with code 0x6a4ec7.
 * Confidence: high */
void sk_r72_683ad8_panic(void)
{
    sk_panic(0x6a4ec7);
}

/* FUN_00683af0 @ 0x00683af0
 * Ghidra: void FUN_00683af0(void)
 * Panic with code 0x6a51e1.
 * Confidence: high */
void sk_r72_683af0_panic(void)
{
    sk_panic(0x6a51e1);
}

/* FUN_00683b08 @ 0x00683b08
 * Ghidra: void FUN_00683b08(void)
 * Panic with code 0x6a5220.
 * Confidence: high */
void sk_r72_683b08_panic(void)
{
    sk_panic(0x6a5220);
}

/* FUN_00683b20 @ 0x00683b20
 * Ghidra: void FUN_00683b20(ulong param_1, undefined8 param_2, undefined8 param_3)
 * Drains a refcount: spins on supervisor call 4 while param_1 == 1; if
 * param_1 != 0 (after the &0xff check) releases obj param_3 and panics with
 * code 0x6a5198.
 * Confidence: medium
 * Notes: spin loop is svc(4) busy-wait; param_3 released via sk_cap_release. */
void sk_r72_683b20_drain_release(uint64_t ref, uint64_t a, uint64_t obj)
{
    (void)a;   /* decompiler-unused arg 2 */
    do {
        sk_svc(4);
    } while (ref == 1);
    if ((ref & 0xff) == 0) {
        return;
    }
    sk_cap_release(obj);   /* FUN_0064eee8 */
    sk_panic(0x6a5198);    /* does not return */
}

/* ================================================================== */
/* 0x00683ba8 .. 0x00683da0 : log-and-abort helpers + fault printers  */
/* ================================================================== */

/* FUN_00683ba8 @ 0x00683ba8
 * Ghidra: void FUN_00683ba8(undefined8 param_1)
 * Log-and-abort trio: begin log (0x6a53b8), emit message 0x6a536c, flush.
 * param_1 is the log context.
 * Confidence: medium
 * Notes: message ids unresolved (see FUN_0065c310). */
static void sk_fault_log_abort_a(uint64_t ctx)
{
    sk_log_begin(ctx, 0x6a53b8);            /* FUN_0067d1f0 */
    sk_log_msg(sk_log_ctx, 0x6a536c, &ctx); /* FUN_0067d83c */
    sk_log_flush(10, sk_log_ctx);           /* FUN_0067d3f8 */
}

/* FUN_00683c2c @ 0x00683c2c
 * Ghidra: void FUN_00683c2c(void)
 * Panic helper: invokes the full panic implementation with code 0x6a5376.
 * Confidence: high */
static void sk_panic_5376(void)
{
    uint8_t sp[8];
    sk_panic_impl(0, 0x6a5376, (void *)sp);   /* does not return */
}

/* FUN_00683c64 @ 0x00683c64
 * Ghidra: void FUN_00683c64(ulong param_1, undefined1 *param_2)
 * Fault printer: pushes the fault value (param_1) and a stack copy, calls the
 * log-abort helper (0x00683ba8), then the panic helper (0x00683c2c), then the
 * log trio again. The value of the (noreturn) panic call is carried as the
 * log context in the final begin.
 * Confidence: low (decompiler sampled registers / noreturn call value)
 * Notes: sk_push/sk_pop are TLS stack saves; 0x00683c2c does not return. */
void sk_r72_683c64_fault_print(uint64_t val, uint8_t *buf)
{
    uint64_t ctx = sk_log_ctx;
    sk_push((uint64_t)buf, val >> 8);       /* FUN_0064f2bc */
    sk_fault_log_abort_a(ctx);              /* 0x00683ba8 */
    sk_push((uint64_t)buf, val);            /* FUN_0064f2bc */
    sk_panic_5376();                        /* 0x00683c2c — does not return */
    sk_log_begin(0, 0x6a53b8);              /* unreachable; arg dropped */
    sk_log_msg(sk_log_ctx, 0x6a536c, (void *)&buf);
    sk_log_flush(10, sk_log_ctx);
}

/* FUN_00683cc4 @ 0x00683cc4
 * Ghidra: void FUN_00683cc4(undefined8 param_1)
 * Log-and-abort trio; message 0x6a536c. param_1 is the log context.
 * Confidence: medium */
static void sk_fault_log_abort_b(uint64_t ctx)
{
    sk_log_begin(ctx, 0x6a53b8);
    sk_log_msg(sk_log_ctx, 0x6a536c, &ctx);
    sk_log_flush(10, sk_log_ctx);
}

/* FUN_00683d48 @ 0x00683d48
 * Ghidra: void FUN_00683d48(void)
 * Panic with code 0x6a5474.
 * Confidence: high */
void sk_r72_683d48_panic(void)
{
    sk_panic(0x6a5474);
}

/* FUN_00683d60 @ 0x00683d60
 * Ghidra: void FUN_00683d60(undefined8 param_1)
 * Logs message 0x6a5640, allocates/initialises frames
 * (sk_alloc_frames(param_1, 0x4000, 8, 0xf)), then flushes the icache.
 * Confidence: medium
 * Notes: sk_alloc_frames returns undefined1[16] (ignored); 0x0067cc18 flushes
 *   the instruction cache. */
void sk_r72_683d60_alloc_flush(uint64_t frame)
{
    sk_log_puts(0x6a5640);                          /* FUN_0067d72c */
    sk_alloc_frames(frame, 0x4000, 8, 0xf);         /* FUN_006504a0 */
    sk_flush_icache();                              /* FUN_0067cc18 — does not return */
}

/* FUN_00683da0 @ 0x00683da0
 * Ghidra: void FUN_00683da0(undefined8 param_1, undefined8 param_2)
 * Fault printer: pushes param_2/param_1 onto the TLS stack, calls the
 * log-abort helper (0x00683cc4), then panics with code 0x6a55cf.
 * Confidence: medium
 * Notes: sk_pop is the TLS stack pop; panic does not return. */
void sk_r72_683da0_fault_print(uint64_t val, uint64_t buf)
{
    uint64_t ctx = sk_log_ctx;
    sk_pop(buf, val >> 8);                  /* FUN_006507fc */
    sk_fault_log_abort_b(ctx);              /* 0x00683cc4 */
    sk_pop(buf, val);                       /* FUN_006507fc */
    sk_panic(0x6a55cf);                     /* does not return */
}

/* ================================================================== */
/* 0x00683e08 .. 0x00683f4c : panic + lock helpers                   */
/* ================================================================== */

/* FUN_00683e08 @ 0x00683e08
 * Ghidra: void FUN_00683e08(void)
 * Panic helper with code 0x6a5a67 (full panic implementation).
 * Confidence: high */
static void sk_panic_5a67(void)
{
    sk_panic_impl(0, 0x6a5a67, (void *)&sk_panic_5a67);
}

/* FUN_00683e40 @ 0x00683e40
 * Ghidra: void FUN_00683e40(void)
 * Runs the 0x00683e08 panic helper then panics again with code 0x6a5b44.
 * Confidence: medium */
void sk_r72_683e40_panic2(void)
{
    sk_panic_5a67();            /* 0x00683e08 — does not return */
    sk_panic(0x6a5b44);
}

/* FUN_00683e50 @ 0x00683e50
 * Ghidra: void FUN_00683e50(void)
 * Panic with code 0x6a5b44.
 * Confidence: high */
void sk_r72_683e50_panic(void)
{
    sk_panic(0x6a5b44);
}

/* FUN_00683e68 @ 0x00683e68
 * Ghidra: void FUN_00683e68(void)
 * Panic with code 0x6a5b7c.
 * Confidence: high */
void sk_r72_683e68_panic(void)
{
    sk_panic(0x6a5b7c);
}

/* FUN_00683e80 @ 0x00683e80
 * Ghidra: void FUN_00683e80(void)
 * Panic with code 0x6a5d22.
 * Confidence: high */
void sk_r72_683e80_panic(void)
{
    sk_panic(0x6a5d22);
}

/* FUN_00683ea4 @ 0x00683ea4
 * Ghidra: void FUN_00683ea4(void)
 * Panic with code 0x6a5c00.
 * Confidence: high */
void sk_r72_683ea4_panic(void)
{
    sk_panic(0x6a5c00);
}

/* FUN_00683ee8 @ 0x00683ee8
 * Ghidra: void FUN_00683ee8(void)
 * Panic with code 0x6a5c97.
 * Confidence: high */
void sk_r72_683ee8_panic(void)
{
    sk_panic(0x6a5c97);
}

/* FUN_00683f00 @ 0x00683f00
 * Ghidra: void FUN_00683f00(void)
 * Panic helper with code 0x6a5e8f (full panic implementation).
 * Confidence: high */
static void sk_panic_5e8f(void)
{
    sk_panic_impl(0, 0x6a5e8f, (void *)&sk_panic_5e8f);
}

/* FUN_00683f38 @ 0x00683f38
 * Ghidra: void FUN_00683f38(void)
 * Runs the 0x00683f00 panic helper then hits an assertion trap
 * (SoftwareBreakpoint 1 @ 0x683f4c).
 * Confidence: medium */
void sk_r72_683f38_panic_trap(void)
{
    sk_panic_5e8f();                        /* 0x00683f00 — does not return */
    sk_assert_trap(1, 0x683f4c);
}

/* FUN_00683f48 @ 0x00683f48
 * Ghidra: void FUN_00683f48(void)
 * Empty function (decompiler produced no body).
 * Confidence: low
 * Notes: likely a padding / aliased stub; no instructions recovered. */
void sk_r72_683f48_noop(void)
{
}

/* FUN_00683f4c @ 0x00683f4c
 * Ghidra: void FUN_00683f4c(void)
 * Warns with code 0x100004077774924 (a compressed fault descriptor) via
 * sk_warn (FUN_006827a8).
 * Confidence: medium
 * Notes: 0x100004077774924 is an unusual packed value; sk_warn does not
 *   return per the caller context. */
void sk_r72_683f4c_warn(void)
{
    sk_warn(0x100004077774924ULL);   /* FUN_006827a8 */
}

/* ================================================================== */
/* 0x00683f74 .. 0x006843ec : list/pool object insert/unlink          */
/* ================================================================== */

/* FUN_00683f74 @ 0x00683f74
 * Ghidra: undefined8 FUN_00683f74(long param_1, undefined8 param_2, long param_3)
 * Allocates a pool object (pool 0x6fc590) and links it into the caller's list.
 * Guards against overflow via POINTER_OVERFLOW checks; uses a lightweight lock
 * (LOAcquire/LORelease) around the refcount bump. On overflow hits an
 * assertion trap. Returns 1 on success (or when the list is already marked
 * busy), 0 on pool exhaustion.
 * Confidence: medium (Ghidra pointer-overflow checks and goto structure)
 * Notes: 0x6fc590 is the pool allocator; overflow check id 0x5519 @ 0x684150. */
uint64_t sk_r72_683f74_insert(uint64_t obj, uint64_t key, uint64_t payload)
{
    uint32_t *pool;
    uint64_t slot;
    int64_t *node, *head;
    int64_t lvar;
    uint64_t lookup;
    uint64_t local;

    if (((*(uint8_t *)(obj + 0x48) >> 4) & 1) == 0) {
        pool = (uint32_t *)sk_pool_alloc(0x6fc590);        /* FUN_0065c27c */
        do {
            node = *(int64_t **)(pool + 0x16);
            if (node == (int64_t *)0x0) {
                sk_lox_acquire();                           /* LOAcquire() */
                slot = *(uint64_t *)(pool + 0x14);
                *(uint64_t *)(pool + 0x14) = slot + 1;
                sk_lox_release();                           /* LORelease() */
                *(uint64_t *)(obj + 0x48) = *(uint64_t *)(obj + 0x48) | 0x10;
                if ((uint64_t)(pool + 0x1c) < (uint64_t)pool) {
                    sk_assert_trap(0x5519, 0x684150);
                }
                sk_pool_lock(pool + 4);                     /* FUN_0065db84 */
                if (slot < *(uint64_t *)(pool + 10)) {
                    if (slot < *(uint64_t *)(pool + 0x12)) {
                        sk_pool_release((uint64_t)pool);    /* FUN_0065beb4 */
                    }
                } else {
                    lvar = (int64_t)*(uint64_t *)(pool + 0x14);
                    *(uint64_t *)(pool + 0x14) = (uint64_t)(lvar - 1);
                    sk_log_fmt((uint64_t)lvar, 0x6a6449);  /* FUN_0067d798 */
                    *pool = 3;
                }
                sk_pool_unlock(pool + 4);                   /* FUN_0065de3c */
                *(uint64_t *)(obj + 0x48) = *(uint64_t *)(obj + 0x48) & 0xffffffffffffffefULL;
                if (*(uint64_t *)(pool + 10) <= slot) {
                    return 0;
                }
                node = (int64_t *)(*(uint64_t *)(pool + 0x10) + slot * 0x40);
                head = node + 8;
                goto link_node;
            }
            head = node + 8;
            if ((uint64_t)head < (uint64_t)node) {
                sk_assert_trap(0x5519, 0x684150);
            }
        } while (*(int64_t **)(pool + 0x16) != node);
        *(int64_t *)(pool + 0x16) = *node;
        *node = 0;
link_node:
        local = key;
        if ((uint64_t)(head) < (uint64_t)(node + 8) || (uint64_t)(node + 8) < (uint64_t)node) {
            sk_assert_trap(0x5519, 0x684150);
        }
        *node = 0;
        node[1] = (int64_t)payload;
        node[3] = 0;
        node[4] = 0;
        node[5] = 0;
        node[6] = 0;
        node[7] = 0;
        node[2] = 0;
        lookup = sk_cap_lookup(obj, &local, node + 2, 5, 0);   /* FUN_00661e1c */
        if (4 < lookup) {
            lookup = 5;
        }
        node[7] = (int64_t)lookup;
        head = (int64_t *)(obj + 0x60);
        do {
            if (*node != 0) {
                sk_abort_simple(0x6a61a9);      /* FUN_0065c288 — does not return */
            }
            lvar = *head;
            *node = lvar;
            if ((uint64_t)(obj + 0x68) < (uint64_t)head) {
                sk_assert_trap(0x5519, 0x684150);
            }
        } while (*head != lvar);
        *head = (int64_t)node;
    }
    return 1;
}

/* FUN_00684150 @ 0x00684150
 * Ghidra: void FUN_00684150(long param_1, long param_2)
 * Unlinks the list node whose key equals param_2 from the chain at param_1+0x60.
 * Validates overflow on every pointer walk; if the feature bit is set it emits
 * a fault report (sk_fault_report, messages 0x6a627a / 0x6a62b7). On a missing
 * entry aborts with sk_abort_code(0x6a629e / 0x6a62c0).
 * Confidence: medium (overflow-check goto structure)
 * Notes: pool 0x6fc590; fault-report messages unresolved. */
void sk_r72_684150_unlink(uint64_t obj, int64_t key)
{
    int64_t *head, *prev, *node, *next, *tmp;
    int64_t slot_val;
    uint64_t fl;
    int b_f, b_v;

    if (((*(uint8_t *)(obj + 0x48) >> 4) & 1) == 0) {
        b_f = 1;
        fl = *(uint64_t *)(sk_pool_alloc(0x6fc590) + 0x20);
        b_v = 1;
        if ((fl >> 1) & 1) {
            fl = *(uint64_t *)(sk_pool_alloc(0x6fc590) + 0x20);
            b_f = (fl & 4) == 0;
            fl = *(uint64_t *)(sk_pool_alloc(0x6fc590) + 0x20);
            b_v = (fl & 8) == 0;
        }
        head = *(int64_t **)(obj + 0x60);
        if (head == (int64_t *)0x0) {
            sk_abort_code(obj, 0x6a629e);       /* does not return */
        }
        node = head;
        next = head + 8;
        if (head[1] == key) {
            prev = (int64_t *)0x0;
        } else {
            do {
                prev = head;
                node = (int64_t *)*head;
                if (b_v) {
                    if ((uint64_t)prev < (uint64_t)head) {
                        sk_assert_trap(0x5519, 0x684368);
                    }
                    sk_fault_report(obj, (int64_t)head, 0x6a627a, b_f);  /* FUN_0065bfa8 */
                }
                head = node;
                if (head == (int64_t *)0x0) {
                    sk_abort_code(obj, 0x6a629e);   /* does not return */
                }
                next = head + 8;
            } while (head[1] != key);
        }
        tmp = (int64_t *)(obj + 0x60);
        if (head != (int64_t *)*tmp) {
            if (b_v) {
                if ((uint64_t)next < (uint64_t)head) {
                    sk_assert_trap(0x5519, 0x684368);
                }
                sk_fault_report(obj, (int64_t)head, 0x6a62b7, b_f);
            }
            if (((fl >> 1) & 1) == 0) {
                sk_abort_code(obj, 0x6a62c0);   /* does not return */
            }
        }
        if (prev == (int64_t *)0x0) {
            if ((uint64_t)(obj + 0x68) < (uint64_t)tmp) {
                sk_assert_trap(0x5519, 0x684368);
            }
            do {
                prev = (int64_t *)*tmp;
                if (prev == (int64_t *)0x0) {
                    goto reuse_pool;
                }
                if ((uint64_t)(prev + 8) < (uint64_t)prev) {
                    sk_assert_trap(0x5519, 0x684368);
                }
            } while ((int64_t *)*tmp != prev);
            *tmp = *prev;
        } else {
            if ((uint64_t)head < (uint64_t)(prev + 8)) {
                sk_assert_trap(0x5519, 0x684368);
            }
            *prev = *head;
            prev = head;
        }
        *prev = 0;
reuse_pool:
        do {
            if (*head != 0) {
                sk_abort_simple(0x6a61a9);      /* does not return */
            }
            tmp = (int64_t *)sk_pool_alloc(0x6fc590);
            slot_val = *(int64_t *)(tmp + 0x58);
            *head = slot_val;
            tmp = (int64_t *)sk_pool_alloc(0x6fc590);
            if ((uint64_t)next < (uint64_t)head) {
                sk_assert_trap(0x5519, 0x684368);
            }
        } while (*(int64_t *)(tmp + 0x58) != slot_val);
        *(int64_t *)(tmp + 0x58) = (int64_t)head;
    }
}

/* FUN_00684388 @ 0x00684388
 * Ghidra: void FUN_00684388(long param_1)
 * Walks the list at param_1+0x60, emitting a fault report (message 0x6a632c,
 * report=1) for every node, until the chain ends. On an overflow while
 * advancing hits an assertion trap.
 * Confidence: medium */
void sk_r72_684388_walk_report(uint64_t obj)
{
    uint64_t *node;

    node = *(uint64_t **)(obj + 0x60);
    while (1) {
        if (node == (uint64_t *)0x0) {
            return;
        }
        if ((uint64_t)(node + 8) < (uint64_t)node) {
            sk_assert_trap(0x5519, 0x6843ec);
        }
        sk_fault_report(obj, (int64_t)node, 0x6a632c, 1);   /* FUN_0065bfa8 */
        node = (uint64_t *)*node;
    }
}

/* FUN_006843ec @ 0x006843ec
 * Ghidra: void FUN_006843ec(undefined8 param_1)
 * L4 error-code report printer. Reads a fault record, and prints the L4 error
 * code as a symbolic name (SlotInvalid / MethodInvalid / ArgumentInvalid /
 * OperationInvalid / PermissionInvalid) with register/colour formatting. Two
 * near-identical halves cover the two error-path kinds; both converge on the
 * log-abort helper 0x006847a0 and the fault-state check.
 * Confidence: low (decompiler sampled register values extraout_* / switch
 *   selector from prior call return registers)
 * Notes: string symbols s_L4_ErrorCode*_00689a3f..abf are rendered as their
 *   Ghidra addresses; 0x3f3f20 is a label/data pointer. */
void sk_r72_6843ec_err_dump(uint64_t context)
{
    uint64_t reg, local50, err_w8, err_code, lo, hi;
    uint64_t saved_state;
    uint64_t local38, ustack30, ustack40;
    uint8_t *local48;

    saved_state = sk_fault_state;
    sk_copy_out(context, 0x1b8, 0, 0);          /* FUN_0065fa24 */
    local50 = sk_read_u64(0x37, 0, 0, 0);       /* FUN_0065fd4c */
    sk_err_color(0x6b6ecd);                     /* FUN_0065d5c8 */
    sk_err_flush();                             /* FUN_0065d608 */
    hi = 0; lo = 0;
    reg = hi | (lo << 32);
    if (reg != 0) {
        sk_err_reg(reg, &local50);              /* FUN_006645ec */
        sk_err_sp();                            /* FUN_0065d69c */
        err_w8 = 0;
        if (9 < err_w8) {
            local38 = 0; ustack30 = 0;
            local48 = (uint8_t *)0x3f3f20;      /* &LAB_003f3f20_3 */
            ustack40 = 0;
            sk_err_x2();                        /* FUN_0065d6e8 */
            goto dump_first;
        }
        err_code = 0;
        switch (err_code) {
        default:
            sk_err_x0();                        /* FUN_0065d6b8 */
            break;
        case 1:
            sk_err_put(0x706d);                 /* FUN_0065d670 */
            break;
        case 2:
            sk_err_x1();                        /* FUN_0065d6d0 */
            break;
        case 3:
            sk_err_put(0x6163);
            break;
        case 4:
            sk_err_put2();                      /* FUN_0065d680 */
            break;
        case 5:
            sk_err_name(0x00689a3f);            /* s_L4_ErrorCodeSlotInvalid */
            local48 = (uint8_t *)0;
            ustack40 = 0;
            sk_err_dash();                      /* FUN_0065d5f0 */
            sk_err_flush();
            local38 = 0; ustack30 = 0;
            goto dump_first;
        case 6:
            sk_err_name(0x00689a5f);            /* s_L4_ErrorCodeMethodInvalid */
            sk_err_tab();                       /* FUN_0065d5a0 */
            goto dump_flush;
        case 7:
            sk_err_name(0x00689a7f);            /* s_L4_ErrorCodeArgumentInvalid */
            sk_err_tab();
            goto dump_flush;
        case 8:
            sk_err_name(0x00689a9f);            /* s_L4_ErrorCodeOperationInvalid */
            sk_err_tab();
            goto dump_flush;
        case 9:
            sk_err_name(0x00689abf);            /* s_L4_ErrorCodePermissionInvalid */
            sk_err_tab();
dump_flush:
            sk_err_flush();
            local38 = 0; ustack30 = 0;
            goto dump_first;
        }
        sk_err_lf();                            /* FUN_0065d574 */
        sk_err_end();                           /* FUN_0065d620 */
dump_first:
        sk_err_x3();                            /* FUN_0065d700 */
        goto dump_done;
    }
    sk_err_color(0x6b6dc6);
    sk_err_flush();
    sk_err_reg(0, &local50);
    sk_err_sp();
    err_w8 = 0;
    if (9 < err_w8) {
        local38 = 0; ustack30 = 0;
        local48 = (uint8_t *)0x3f3f20;          /* &LAB_003f3f20_3 */
        ustack40 = 0;
        sk_err_x2();
        goto dump_second;
    }
    err_code = 0;
    switch (err_code) {
    default:
        sk_err_x0();
        break;
    case 1:
        sk_err_put(0x706d);
        break;
    case 2:
        sk_err_x1();
        break;
    case 3:
        sk_err_put(0x6163);
        break;
    case 4:
        sk_err_put2();
        break;
    case 5:
        sk_err_name(0x00689a3f);                /* s_L4_ErrorCodeSlotInvalid */
        local48 = (uint8_t *)0;
        ustack40 = 0;
        sk_err_dash();
        sk_err_flush();
        local38 = 0; ustack30 = 0;
        goto dump_second;
    case 6:
        sk_err_name(0x00689a5f);                /* s_L4_ErrorCodeMethodInvalid */
        sk_err_tab();
        goto dump_flush2;
    case 7:
        sk_err_name(0x00689a7f);                /* s_L4_ErrorCodeArgumentInvalid */
        sk_err_tab();
        goto dump_flush2;
    case 8:
        sk_err_name(0x00689a9f);                /* s_L4_ErrorCodeOperationInvalid */
        sk_err_tab();
        goto dump_flush2;
    case 9:
        sk_err_name(0x00689abf);                /* s_L4_ErrorCodePermissionInvalid */
        sk_err_tab();
dump_flush2:
        sk_err_flush();
        local38 = 0; ustack30 = 0;
        goto dump_second;
    }
    sk_err_lf();
    sk_err_end();
dump_second:
    sk_err_x3();
dump_done:
    (void)local38; (void)ustack30; (void)ustack40; (void)local48;   /* decompiler-sampled stack slots */
    sk_fault_log_abort_c(sk_log_ctx);           /* 0x006847a0 */
    if (sk_fault_state != saved_state) {
        sk_log_poll(0, 0, 0);                   /* FUN_0067f660 — does not return */
    }
}

/* ================================================================== */
/* 0x006847a0 .. 0x00684e58 : log-abort + counter helpers             */
/* ================================================================== */

/* FUN_006847a0 @ 0x006847a0
 * Ghidra: void FUN_006847a0(undefined8 param_1)
 * Log-and-abort trio; message 0x6a668c. param_1 is the log context.
 * Confidence: medium */
static void sk_fault_log_abort_c(uint64_t ctx)
{
    sk_log_begin(ctx, 0x6a53b8);
    sk_log_msg(sk_log_ctx, 0x6a668c, &ctx);
    sk_log_flush(10, sk_log_ctx);
}

/* FUN_00684820 @ 0x00684820
 * Ghidra: void FUN_00684820(void)
 * Warns with code 0x6a612a.
 * Confidence: medium */
void sk_r72_684820_warn(void)
{
    sk_warn(0x6a612a);   /* FUN_0067b280 */
}

/* FUN_00684860 @ 0x00684860
 * Ghidra: void FUN_00684860(void)
 * Aborts with code 0x6a66ce via sk_abort_code.
 * Confidence: high */
void sk_r72_684860_abort(void)
{
    sk_abort_code(0, 0x6a66ce);   /* FUN_0065c2f0 — does not return */
}

/* FUN_0068487c @ 0x0068487c
 * Ghidra: void FUN_0068487c(undefined8 param_1)
 * Log-and-abort trio; message 0x6a536c.
 * Confidence: medium */
static void sk_fault_log_abort_d(uint64_t ctx)
{
    sk_log_begin(ctx, 0x6a53b8);
    sk_log_msg(sk_log_ctx, 0x6a536c, &ctx);
    sk_log_flush(10, sk_log_ctx);
}

/* FUN_006848f4 @ 0x006848f4
 * Ghidra: void FUN_006848f4(void)
 * Fault-dump wrapper: saves context (sk_ctx_save_full / sk_ctx_save), logs the
 * fault (0x0068487c), restores context, then panics with code 0x6a6920.
 * Confidence: medium */
void sk_r72_6848f4_fault_dump(void)
{
    sk_ctx_save_full();     /* FUN_0065f454 */
    sk_ctx_save();          /* FUN_0065f428 */
    sk_fault_log_abort_d(sk_log_ctx);   /* 0x0068487c */
    sk_ctx_restore();       /* FUN_0065f448 */
    sk_panic(0x6a6920);     /* does not return */
}

/* FUN_00684940 @ 0x00684940
 * Ghidra: void FUN_00684940(void)
 * Fault-dump wrapper identical to 0x006848f4 but panics with code 0x6a6827.
 * Confidence: medium */
void sk_r72_684940_fault_dump(void)
{
    sk_ctx_save_full();
    sk_ctx_save();
    sk_fault_log_abort_d(sk_log_ctx);
    sk_ctx_restore();
    sk_panic(0x6a6827);     /* does not return */
}

/* FUN_0068498c @ 0x0068498c
 * Ghidra: void FUN_0068498c(undefined2 *param_1, long param_2, ulong *param_3)
 * Builds a 64-byte TLS message header at param_1 from saved byte fields,
 * issuing a supervisor call (0) around the first byte-scatter, then writes
 * param_2 spread across offsets 0xe0..0x1c7. Reads six global metadata bytes
 * and combines them with 0x10000 as a magic check; if zero, sets bit 3 of
 * *param_3 and returns; otherwise releases frame param_2 and aborts with code
 * 0x6a6894.
 * Confidence: low (byte-scatter layout; decompiler register sampling)
 * Notes: the combined magic = u32<<32 | (u16/u32 sub-fields) | 0x10000. */
void sk_r72_68498c_tls_header(uint8_t *hdr, int64_t frame, uint64_t *flags)
{
    uint8_t b0, b1, b2, b3, b4, b6, b7;
    uint16_t w0, w1;
    uint32_t m0, m1;

    w0 = *(uint16_t *)hdr;
    b1 = hdr[3];
    b2 = hdr[2];
    w1 = *(uint16_t *)(hdr + 4);
    b3 = hdr[7];
    b4 = hdr[6];
    do {
        sk_svc(0);
        hdr[0] = (uint8_t)w0;
        hdr[5] = (uint8_t)((uint16_t)w1 >> 8);
        hdr[3] = b1;
        hdr[2] = b2;
        hdr[1] = (uint8_t)((uint16_t)w0 >> 8);
        hdr[4] = (uint8_t)w1;
        hdr[7] = b3;
        hdr[6] = b4;
    } while (frame == 1);
    hdr[0xe0] = (uint8_t)frame;
    hdr[0x1c5] = (uint8_t)((uint64_t)frame >> 0x28);
    hdr[0x1c3] = (uint8_t)((uint64_t)frame >> 0x18);
    hdr[0xe1] = (uint8_t)((uint64_t)frame >> 0x10);
    hdr[0x1c1] = (uint8_t)((uint64_t)frame >> 8);
    hdr[0xe2] = (uint8_t)((uint64_t)frame >> 0x20);
    hdr[0x1c7] = (uint8_t)((uint64_t)frame >> 0x38);
    hdr[0xe3] = (uint8_t)((uint64_t)frame >> 0x30);
    m0 = sk_meta_u32;            /* _DAT_006b6fd4 */
    m1 = sk_meta_u32b;           /* _DAT_006b6fd8 */
    b0 = sk_meta_b1;             /* DAT_006b6fdb */
    b6 = sk_meta_b2;             /* DAT_006b6fd7 */
    b7 = sk_meta_b3;             /* DAT_006b6fd6 */
    hdr[0] = 0x40;
    hdr[1] = 0;
    hdr[4] = 0;
    hdr[5] = 0;
    hdr[2] = 1;
    hdr[3] = 0;
    hdr[6] = 0;
    hdr[7] = 0;
    sk_svc(0);
    hdr[0] = 0x40;
    hdr[7] = 0;
    hdr[6] = 0;
    hdr[5] = 0;
    hdr[4] = 0;
    hdr[3] = 0;
    hdr[2] = 1;
    hdr[1] = 0;
    hdr[0x1e5] = 0;
    hdr[0x1e3] = 0;
    hdr[0xf1] = 0;
    hdr[0x1e1] = 0;
    hdr[0xf2] = 0;
    hdr[0xf0] = 0;
    hdr[0x1e7] = 0;
    hdr[0xf3] = 0;
    {
        /* combined magic: (u32 hi)<<32 | u16/u32 sub-fields | 0x10000 */
        uint64_t hi = (uint64_t)(sk_meta_u32c << 16 | ((uint32_t)b0 << 24) | m1);
        uint64_t lo = ((uint64_t)b7 << 16) | ((uint64_t)b6 << 24) | m0;
        if ((lo | (hi << 32) | 0x10000ULL) == 0) {
            *flags |= 8;
            return;
        }
    }
    sk_frame_release(frame);        /* FUN_006860f4 */
    sk_abort_code(0, 0x6a6894);     /* does not return */
}

/* FUN_00684bc0 @ 0x00684bc0
 * Ghidra: void FUN_00684bc0(void)
 * Fault-dump wrapper (context save / log / restore) then panic 0x6a6a2a.
 * Confidence: medium */
void sk_r72_684bc0_fault_dump(void)
{
    sk_ctx_save_full();
    sk_ctx_save();
    sk_fault_log_abort_d(sk_log_ctx);
    sk_ctx_restore();
    sk_panic(0x6a6a2a);     /* does not return */
}

/* FUN_00684c0c @ 0x00684c0c
 * Ghidra: void FUN_00684c0c(void)
 * Fault-dump wrapper then panic 0x6a69b4.
 * Confidence: medium */
void sk_r72_684c0c_fault_dump(void)
{
    sk_ctx_save_full();
    sk_ctx_save();
    sk_fault_log_abort_d(sk_log_ctx);
    sk_ctx_restore();
    sk_panic(0x6a69b4);     /* does not return */
}

/* FUN_00684c58 @ 0x00684c58
 * Ghidra: void FUN_00684c58(void)
 * Fault-dump wrapper then panic 0x6a6ac5.
 * Confidence: medium */
void sk_r72_684c58_fault_dump(void)
{
    sk_ctx_save_full();
    sk_ctx_save();
    sk_fault_log_abort_d(sk_log_ctx);
    sk_ctx_restore();
    sk_panic(0x6a6ac5);     /* does not return */
}

/* FUN_00684ca4 @ 0x00684ca4
 * Ghidra: void FUN_00684ca4(undefined8 param_1)
 * Log-and-abort trio; message 0x6a536c.
 * Confidence: medium */
static void sk_fault_log_abort_e(uint64_t ctx)
{
    sk_log_begin(ctx, 0x6a53b8);
    sk_log_msg(sk_log_ctx, 0x6a536c, &ctx);
    sk_log_flush(10, sk_log_ctx);
}

/* FUN_00684d1c @ 0x00684d1c
 * Ghidra: void FUN_00684d1c(long param_1)
 * Object teardown: enters the lock, unrefs the object and its extension, then
 * conditionally releases two tagged capabilities (tags 0x15, 0x14) and a
 * capability (tag 6), draining each refcount with supervisor-call spin loops
 * (svc 5 / svc 4) until the count leaves 1. Releases the frame at param_1+0x88
 * and param_1+0x70, then invokes the object's destructor via the method table
 * at param_1+0x38.
 * Confidence: medium (indirect destructor call not recovered)
 * Notes: jumptable at 0x00684ddc not recovered; destructor = (*(fn**)(+0x38))(+0x30). */
void sk_r72_684d1c_teardown(int64_t obj)
{
    sk_lock_enter();                        /* FUN_0065c218 */
    sk_unref((uint64_t)obj);                /* FUN_0065eafc */
    sk_xt_release((uint64_t *)obj);         /* FUN_0065d080 */
    if (*(int64_t *)(obj + 0x108) != 0) {
        sk_method_dispatch(*(uint64_t *)(obj + 0x108), 0x15);   /* FUN_006832fc */
        *(uint64_t *)(obj + 0x108) = 0;
    }
    if (*(int64_t *)(obj + 0x110) != 0) {
        sk_method_dispatch(*(uint64_t *)(obj + 0x110), 0x14);
        *(uint64_t *)(obj + 0x110) = 0;
    }
    sk_method_dispatch(*(uint64_t *)(obj + 0x28), 6);
    do { sk_svc(5); } while (*(int64_t *)(obj + 0x88) == 1);
    do { sk_svc(4); } while (*(int64_t *)(obj + 0x88) == 1);
    sk_frame_release(*(int64_t *)(obj + 0x88));     /* FUN_006860f4 */
    do { sk_svc(4); } while (*(int64_t *)(obj + 0x70) == 1);
    sk_frame_release(*(int64_t *)(obj + 0x70));
    /* (*(code **)**(obj + 0x38))(*(obj + 0x30)) — destructor dispatch */
    (*(void (**)(uint64_t))**(uint64_t **)(obj + 0x38))(*(uint64_t *)(obj + 0x30));
}

/* FUN_00684de0 @ 0x00684de0
 * Ghidra: void FUN_00684de0(void)
 * Context-save / log-abort / context-restore wrapper then panic 0x6a71a1.
 * Confidence: medium */
void sk_r72_684de0_fault_dump(void)
{
    sk_ctx_pre();                   /* FUN_006612c0 */
    sk_fault_log_abort_e(sk_log_ctx);   /* 0x00684ca4 */
    sk_ctx_post();                  /* FUN_006612e0 */
    sk_panic(0x6a71a1);             /* does not return */
}

/* FUN_00684e30 @ 0x00684e30
 * Ghidra: void FUN_00684e30(void)
 * Increments the event counter sk_stat_a (_DAT_006fe794).
 * Confidence: high */
void sk_r72_684e30_counter_a(void)
{
    sk_stat_a = sk_stat_a + 1;
}

/* FUN_00684e44 @ 0x00684e44
 * Ghidra: void FUN_00684e44(void)
 * Increments the event counter sk_stat_b (_DAT_006fe790).
 * Confidence: high */
void sk_r72_684e44_counter_b(void)
{
    sk_stat_b = sk_stat_b + 1;
}

/* FUN_00684e58 @ 0x00684e58
 * Ghidra: void FUN_00684e58(long param_1)
 * Releases the frame referenced at param_1+0x88.
 * Confidence: medium */
void sk_r72_684e58_frame_release(int64_t obj)
{
    sk_frame_release(*(int64_t *)(obj + 0x88));   /* FUN_006860f4 */
}

/* FUN_00684e8c @ 0x00684e8c
 * Ghidra: void FUN_00684e8c(void)
 * Context-save / log-abort / context-restore wrapper then panic 0x6a6f83.
 * Confidence: medium */
void sk_r72_684e8c_fault_dump(void)
{
    sk_ctx_pre();
    sk_fault_log_abort_e(sk_log_ctx);
    sk_ctx_post();
    sk_panic(0x6a6f83);             /* does not return */
}

/* FUN_00684edc @ 0x00684edc
 * Ghidra: void FUN_00684edc(void)
 * Aborts with code 0x6a4f12.
 * Confidence: high */
void sk_r72_684edc_abort(void)
{
    sk_abort_code(0, 0x6a4f12);     /* does not return */
}

/* FUN_00684f04 @ 0x00684f04
 * Ghidra: void FUN_00684f04(void)
 * Aborts with code 0x6a4ef1.
 * Confidence: high */
void sk_r72_684f04_abort(void)
{
    sk_abort_code(0, 0x6a4ef1);     /* does not return */
}

/* FUN_00684f2c @ 0x00684f2c
 * Ghidra: void FUN_00684f2c(void)
 * Context-save / log-abort / context-restore wrapper then panic 0x6a7059.
 * Confidence: medium */
void sk_r72_684f2c_fault_dump(void)
{
    sk_ctx_pre();
    sk_fault_log_abort_e(sk_log_ctx);
    sk_ctx_post();
    sk_panic(0x6a7059);             /* does not return */
}

/* FUN_00684f7c @ 0x00684f7c
 * Ghidra: void FUN_00684f7c(void)
 * Panic with code 0x6a70ac.
 * Confidence: high */
void sk_r72_684f7c_panic(void)
{
    sk_panic(0x6a70ac);
}

/* FUN_00684f94 @ 0x00684f94
 * Ghidra: void FUN_00684f94(void)
 * Panic with code 0x6a70c7.
 * Confidence: high */
void sk_r72_684f94_panic(void)
{
    sk_panic(0x6a70c7);
}

/* FUN_00684fac @ 0x00684fac
 * Ghidra: void FUN_00684fac(void)
 * Panic with code 0x6a728d.
 * Confidence: high */
void sk_r72_684fac_panic(void)
{
    sk_panic(0x6a728d);
}

/* FUN_00684fc4 @ 0x00684fc4
 * Ghidra: void FUN_00684fc4(void)
 * Panic with code 0x6a5bed.
 * Confidence: high */
void sk_r72_684fc4_panic(void)
{
    sk_panic(0x6a5bed);
}

/* FUN_00684fdc @ 0x00684fdc
 * Ghidra: void FUN_00684fdc(undefined8 param_1)
 * Log-and-abort trio; message 0x6a536c.
 * Confidence: medium */
static void sk_fault_log_abort_f(uint64_t ctx)
{
    sk_log_begin(ctx, 0x6a53b8);
    sk_log_msg(sk_log_ctx, 0x6a536c, &ctx);
    sk_log_flush(10, sk_log_ctx);
}

/* FUN_00685054 @ 0x00685054
 * Ghidra: void FUN_00685054(void)
 * Aborts with code 0x6a72e6 via sk_abort_simple.
 * Confidence: high */
void sk_r72_685054_abort(void)
{
    sk_abort_simple(0x6a72e6);      /* does not return */
}

/* FUN_00685084 @ 0x00685084
 * Ghidra: void FUN_00685084(void)
 * Aborts with code 0x6a72e6 via sk_abort_simple.
 * Confidence: high */
void sk_r72_685084_abort(void)
{
    sk_abort_simple(0x6a72e6);      /* does not return */
}

/* FUN_006850b4 @ 0x006850b4
 * Ghidra: void FUN_006850b4(void)
 * Acquires the small lock (FUN_00663910).
 * Confidence: medium */
void sk_r72_6850b4_lock_small(void)
{
    sk_lock_small();    /* FUN_00663910 */
}

/* FUN_006850c8 @ 0x006850c8
 * Ghidra: void FUN_006850c8(void)
 * Acquires the medium lock (FUN_006638f8).
 * Confidence: medium */
void sk_r72_6850c8_lock_med(void)
{
    sk_lock_med();      /* FUN_006638f8 */
}

/* FUN_006850dc @ 0x006850dc
 * Ghidra: void FUN_006850dc(void)
 * Panic with code 0x6a78a7.
 * Confidence: high */
void sk_r72_6850dc_panic(void)
{
    sk_panic(0x6a78a7);
}

/* FUN_006850f4 @ 0x006850f4
 * Ghidra: void FUN_006850f4(void)
 * Panic with code 0x6a78d9.
 * Confidence: high */
void sk_r72_6850f4_panic(void)
{
    sk_panic(0x6a78d9);
}

/* FUN_0068510c @ 0x0068510c
 * Ghidra: void FUN_0068510c(void)
 * Big-lock / log-abort / context-swap wrapper then panic 0x6a794a.
 * Confidence: medium */
void sk_r72_68510c_fault_dump(void)
{
    sk_lock_big();                  /* FUN_006638d8 */
    sk_fault_log_abort_f(sk_log_ctx);   /* 0x00684fdc */
    sk_ctx_swap();                  /* FUN_00662a40 */
    sk_panic(0x6a794a);             /* does not return */
}

/* FUN_00685164 @ 0x00685164
 * Ghidra: void FUN_00685164(void)
 * Big-lock / log-abort / context-swap wrapper then panic 0x6a7410.
 * Confidence: medium */
void sk_r72_685164_fault_dump(void)
{
    sk_lock_big();
    sk_fault_log_abort_f(sk_log_ctx);
    sk_ctx_swap();
    sk_panic(0x6a7410);             /* does not return */
}

/* FUN_006851bc @ 0x006851bc
 * Ghidra: void FUN_006851bc(undefined8 param_1)
 * Log-and-abort trio; message 0x6a536c.
 * Confidence: medium */
static void sk_fault_log_abort_g(uint64_t ctx)
{
    sk_log_begin(ctx, 0x6a53b8);
    sk_log_msg(sk_log_ctx, 0x6a536c, &ctx);
    sk_log_flush(10, sk_log_ctx);
}

/* FUN_00685234 @ 0x00685234
 * Ghidra: void FUN_00685234(long param_1)
 * Fault-state header build: saves the TLS head bytes, spins a supervisor call
 * (0) while the object type at param_1+0x28 == 1, and while doing so restores
 * the saved bytes into the TLS area (a read-modify-write around the call).
 * If the object type is 0 and the fault state is unchanged, returns; otherwise
 * copies the TLS record, logs (0x006851bc), and panics with code 0x6a7da3.
 * Confidence: low (byte-scatter; TLS base from tpidrro_el0)
 * Notes: uVar10 = object type tag; 0x0067f660 does not return on mismatch. */
void sk_r72_685234_fault_header(int64_t obj)
{
    uint64_t saved_state, tag;
    uint16_t *tls;
    uint8_t b0, b1, b2, b3;
    uint16_t w0, w1;
    uint8_t buf[32];

    saved_state = sk_fault_state;
    tag = *(uint64_t *)(obj + 0x28);
    tls = (uint16_t *)sk_tls_base();
    w0 = *tls;
    b0 = *(uint8_t *)((uint8_t *)tls + 3);
    b1 = *(uint8_t *)((uint8_t *)tls + 2);
    w1 = tls[2];
    b2 = *(uint8_t *)((uint8_t *)tls + 7);
    b3 = *(uint8_t *)((uint8_t *)tls + 6);
    do {
        sk_svc(0);
        *(uint8_t *)tls = (uint8_t)w0;
        *(uint8_t *)((uint8_t *)tls + 5) = (uint8_t)((uint16_t)w1 >> 8);
        *(uint8_t *)((uint8_t *)tls + 3) = b0;
        *(uint8_t *)((uint8_t *)tls + 2) = b1;
        *(uint8_t *)((uint8_t *)tls + 1) = (uint8_t)((uint16_t)w0 >> 8);
        *(uint8_t *)((uint8_t *)tls + 4) = (uint8_t)w1;
        *(uint8_t *)((uint8_t *)tls + 7) = b2;
        *(uint8_t *)((uint8_t *)tls + 6) = b3;
    } while (tag == 1);
    if ((tag & 0xff) == 0) {
        if (sk_fault_state == saved_state) {
            return;
        }
        sk_log_poll(0, 0, 0);       /* FUN_0067f660 — does not return */
    }
    sk_memcpy_tls(buf, (void *)tag, 0x10);      /* FUN_00663c04 */
    sk_fault_log_abort_g(sk_log_ctx);           /* 0x006851bc */
    sk_memcpy_tls(buf, (void *)tag, (uint64_t)tag);  /* FUN_00663c04 */
    sk_panic(0x6a7da3);             /* does not return */
}

/* FUN_0068538c @ 0x0068538c
 * Ghidra: void FUN_0068538c(void)
 * Unlock-all / log-abort / memcpy wrapper then panic 0x6a7d2d.
 * Confidence: medium */
void sk_r72_68538c_fault_dump(void)
{
    sk_unlock_all();                /* FUN_0066453c */
    sk_fault_log_abort_g(sk_log_ctx);   /* 0x006851bc */
    sk_memcpy_tls((void *)0, (void *)0, 0); /* FUN_00663c04 (args dropped) */
    sk_panic(0x6a7d2d);             /* does not return */
}

/* FUN_006853e4 @ 0x006853e4
 * Ghidra: void FUN_006853e4(void)
 * Unlock-all / log-abort / memcpy wrapper then panic 0x6a7e24.
 * Confidence: medium */
void sk_r72_6853e4_fault_dump(void)
{
    sk_unlock_all();
    sk_fault_log_abort_g(sk_log_ctx);
    sk_memcpy_tls((void *)0, (void *)0, 0);
    sk_panic(0x6a7e24);             /* does not return */
}

/* FUN_0068543c @ 0x0068543c
 * Ghidra: void FUN_0068543c(void)
 * Aborts with code 0x6a7ed1.
 * Confidence: high */
void sk_r72_68543c_abort(void)
{
    sk_abort_code(0, 0x6a7ed1);     /* does not return */
}

/* FUN_00685458 @ 0x00685458
 * Ghidra: void FUN_00685458(void)
 * Panic with code 0x6a7efc.
 * Confidence: high */
void sk_r72_685458_panic(void)
{
    sk_panic(0x6a7efc);
}

/* FUN_00685470 @ 0x00685470
 * Ghidra: void FUN_00685470(undefined8 param_1)
 * Log-and-abort trio; message 0x6a536c.
 * Confidence: medium */
static void sk_fault_log_abort_h(uint64_t ctx)
{
    sk_log_begin(ctx, 0x6a53b8);
    sk_log_msg(sk_log_ctx, 0x6a536c, &ctx);
    sk_log_flush(10, sk_log_ctx);
}

/* FUN_006854e8 @ 0x006854e8
 * Ghidra: void FUN_006854e8(void)
 * Thread-lock / log-abort / thread-done wrapper then panic 0x6a806c.
 * Confidence: medium */
void sk_r72_6854e8_fault_dump(void)
{
    sk_thread_lock();               /* FUN_00665cec */
    sk_fault_log_abort_h(sk_log_ctx);   /* 0x00685470 */
    sk_thread_done();               /* FUN_00665d84 */
    sk_panic(0x6a806c);             /* does not return */
}

/* FUN_00685538 @ 0x00685538
 * Ghidra: void FUN_00685538(void)
 * Thread-lock / log-abort / thread-done wrapper then panic 0x6a8134.
 * Confidence: medium */
void sk_r72_685538_fault_dump(void)
{
    sk_thread_lock();
    sk_fault_log_abort_h(sk_log_ctx);
    sk_thread_done();
    sk_panic(0x6a8134);             /* does not return */
}

/* FUN_00685588 @ 0x00685588
 * Ghidra: undefined4 FUN_00685588(ulong param_1, ulong param_2, long *param_3)
 * Export/export-check on a capability object param_1 for range param_2: drains
 * the refcount (svc 5 spin) while param_1+0x88 == 1. If param_2 < param_1
 * returns 0; otherwise tags the object as exported (sk_tag_export with tag
 * 0x65787074 "extp"), sets bit 0 of param_1+0x48, unrefs, reads the slot at
 * param_1+0x50 into *param_3, and returns 1 (or 2 if the slot is non-null).
 * Confidence: medium
 * Notes: 0x65787074 = ASCII "extp" (export tag). */
uint32_t sk_r72_685588_export(uint64_t obj, uint64_t range, int64_t *slot)
{
    uint32_t ret;
    int64_t v;

    do { sk_svc(5); } while (*(int64_t *)(obj + 0x88) == 1);
    if (range < obj) {
        ret = 0;
    } else {
        sk_tag_export(obj, 0x65787074);     /* FUN_00662628 */
        *(uint64_t *)(obj + 0x48) = *(uint64_t *)(obj + 0x48) | 1;
        sk_unref2(obj);                     /* FUN_00660b20 */
        v = *(int64_t *)(obj + 0x50);
        *slot = v;
        ret = 1;
        if (v != 0) {
            ret = 2;
        }
    }
    return ret;
}

/* FUN_00685608 @ 0x00685608
 * Ghidra: void FUN_00685608(void)
 * Thread-lock / log-abort / thread-done wrapper then panic 0x6a828a.
 * Confidence: medium */
void sk_r72_685608_fault_dump(void)
{
    sk_thread_lock();
    sk_fault_log_abort_h(sk_log_ctx);
    sk_thread_done();
    sk_panic(0x6a828a);             /* does not return */
}

/* FUN_00685658 @ 0x00685658
 * Ghidra: void FUN_00685658(void)
 * Thread-lock / log-abort / thread-done wrapper then panic 0x6a8332.
 * Confidence: medium */
void sk_r72_685658_fault_dump(void)
{
    sk_thread_lock();
    sk_fault_log_abort_h(sk_log_ctx);
    sk_thread_done();
    sk_panic(0x6a8332);             /* does not return */
}

/* FUN_006856a8 @ 0x006856a8
 * Ghidra: void FUN_006856a8(long param_1, undefined8 *param_2, ulong param_3)
 * Context/state swap: writes param_3 byte-scattered into the TLS area around a
 * supervisor call (0), then writes the 64-bit value *param_2 into the same
 * TLS bytes, again around a supervisor call. If the object's low type byte at
 * param_1+0x28 is zero, updates the control register and returns (or takes the
 * no-return poll path). Otherwise reports thread flags (0x11), pushes registers,
 * logs the fault (0x00685470), pushes more, and panics with code 0x6a81af.
 * Confidence: low (byte-scatter layout; decompiler register sampling)
 * Notes: TLS base from tpidrro_el0; the do-while uses an in_ZR residue flag. */
void sk_r72_6856a8_state_swap(int64_t obj, uint64_t *src, uint64_t val)
{
    uint8_t *tls;
    uint64_t v, type;
    uint8_t buf[32];

    tls = sk_tls_base();
    type = *(uint64_t *)(obj + 0x28);
    sk_reg_put(((uint64_t)tls[1] << 16) | ((uint64_t)tls[3] << 24) | (uint64_t)tls[0]);  /* FUN_00665d20 */
    do {
        sk_svc(0);
        tls[0] = (uint8_t)val;
        tls[5] = (uint8_t)(val >> 0x28);
        tls[3] = (uint8_t)(val >> 0x18);
        tls[2] = (uint8_t)(val >> 0x10);
        tls[1] = (uint8_t)(val >> 8);
        sk_reg_sel(val >> 0x20, type, 0x12);    /* FUN_00665d44 */
    } while (0);
    v = *src;
    tls[0] = (uint8_t)v;
    tls[1] = (uint8_t)(v >> 8);
    tls[4] = (uint8_t)(v >> 0x20);
    tls[5] = (uint8_t)(v >> 0x28);
    tls[2] = (uint8_t)(v >> 0x10);
    tls[3] = (uint8_t)(v >> 0x18);
    tls[6] = (uint8_t)(v >> 0x30);
    tls[7] = (uint8_t)(v >> 0x38);
    sk_svc(0);
    tls[0] = (uint8_t)v;
    tls[7] = (uint8_t)(v >> 0x38);
    tls[6] = (uint8_t)(v >> 0x30);
    tls[5] = (uint8_t)(v >> 0x28);
    tls[4] = (uint8_t)(v >> 0x20);
    tls[3] = (uint8_t)(v >> 0x18);
    tls[2] = (uint8_t)(v >> 0x10);
    tls[1] = (uint8_t)(v >> 8);
    if ((type & 0xff) == 0) {
        sk_ctl_u64(sk_fault_state);             /* FUN_00665d70 */
        return;
    }
    sk_thread_flags(type, 0x11);                /* FUN_00665d0c */
    sk_reg_push((uint64_t *)buf, (uint64_t *)buf);  /* FUN_00665354 */
    sk_fault_log_abort_h(sk_log_ctx);           /* 0x00685470 */
    sk_reg_push((uint64_t *)buf, (uint64_t *)src);  /* FUN_00665354 */
    sk_panic(0x6a81af);                         /* does not return */
}

/* FUN_00685864 @ 0x00685864
 * Ghidra: void FUN_00685864(void)
 * Pauses the thread (sk_thread_pause), then begins a log on the current context
 * with message 0x6a8493.
 * Confidence: medium
 * Notes: log begin's msg id unresolved. */
void sk_r72_685864_log_pause(void)
{
    sk_thread_pause();                          /* FUN_0065cd38 */
    sk_log_begin(sk_log_ctx, 0x6a8493);         /* FUN_0067d1f0 */
}

/* FUN_00685928 @ 0x00685928
 * Ghidra: void FUN_00685928(void)
 * Reports thread flags (0x00665d0c), reads the current TCB, and begins a log
 * (args dropped by decompiler).
 * Confidence: low */
void sk_r72_685928_thread_report(void)
{
    sk_thread_flags(0, 0);                      /* FUN_00665d0c (args dropped) */
    sk_current_tcb();                           /* FUN_00661318 */
    sk_log_begin(sk_log_ctx, 0);                /* FUN_0067d1f0 (args dropped) */
}

/* FUN_0068596c @ 0x0068596c
 * Ghidra: void FUN_0068596c(void)
 * Probes the thread (0x00665d60), reads the current TCB, and begins a log
 * (args dropped by decompiler).
 * Confidence: low */
void sk_r72_68596c_thread_report(void)
{
    sk_thread_probe();                          /* FUN_00665d60 */
    sk_current_tcb();                           /* FUN_00661318 */
    sk_log_begin(sk_log_ctx, 0);                /* FUN_0067d1f0 (args dropped) */
}

/* FUN_006859b0 @ 0x006859b0
 * Ghidra: void FUN_006859b0(undefined8 param_1)
 * Log-and-abort trio; message 0x6a536c.
 * Confidence: medium */
static void sk_fault_log_abort_i(uint64_t ctx)
{
    sk_log_begin(ctx, 0x6a53b8);
    sk_log_msg(sk_log_ctx, 0x6a536c, &ctx);
    sk_log_flush(10, sk_log_ctx);
}

/* FUN_00685a34 @ 0x00685a34
 * Ghidra: void FUN_00685a34(void)
 * Panic helper with code 0x6a8612 (full panic implementation).
 * Confidence: high */
static void sk_panic_8612(void)
{
    sk_panic_impl(0, 0x6a8612, (void *)&sk_panic_8612);
}

/* FUN_00685a6c @ 0x00685a6c
 * Ghidra: void FUN_00685a6c(ulong param_1, undefined1 *param_2)
 * Fault printer: pops param_1/param_2 onto the TLS stack, calls the log-abort
 * helper (0x006859b0), then the panic helper (0x00685a34), then the log trio
 * with message 0x6a981c.
 * Confidence: low (decompiler register sampling around noreturn call)
 * Notes: sk_pop3 is the TLS stack pop; 0x00685a34 does not return. */
void sk_r72_685a6c_fault_print(uint64_t val, uint8_t *buf)
{
    uint64_t ctx = sk_log_ctx;
    sk_pop3((uint64_t)buf, val >> 8);           /* FUN_0066609c */
    sk_fault_log_abort_i(ctx);                  /* 0x006859b0 */
    sk_pop3((uint64_t)buf, val);                /* FUN_0066609c */
    sk_panic_8612();                            /* 0x00685a34 — does not return */
    sk_log_begin(0, 0x6a53b8);                  /* unreachable; arg dropped */
    sk_log_msg(sk_log_ctx, 0x6a981c, (void *)&buf);
    sk_log_flush(10, sk_log_ctx);
}

/* FUN_00685acc @ 0x00685acc
 * Ghidra: void FUN_00685acc(undefined8 param_1)
 * Log-and-abort trio; message 0x6a981c.
 * Confidence: medium */
void sk_fault_log_abort_j(uint64_t ctx)
{
    sk_log_begin(ctx, 0x6a53b8);
    sk_log_msg(sk_log_ctx, 0x6a981c, &ctx);
    sk_log_flush(10, sk_log_ctx);
}

/* FUN_00685b50 @ 0x00685b50
 * Ghidra: void FUN_00685b50(void)
 * Panic with code 0x6a86ea.
 * Confidence: high */
void sk_r72_685b50_panic(void)
{
    sk_panic(0x6a86ea);
}

/* FUN_00685b88 @ 0x00685b88
 * Ghidra: void FUN_00685b88(byte *param_1)
 * Prints two messages (0x6a88bb, 0x6a88c4), a newline (10), then panics with
 * code 0x6a88ca.
 * Confidence: medium */
void sk_r72_685b88_print_panic(uint8_t *arg)
{
    (void)arg;   /* decompiler-unused arg */
    sk_log_puts(0x6a88bb);              /* FUN_0067d72c */
    sk_log_puts(0x6a88c4);              /* FUN_0067d72c */
    sk_log_nl(10);                      /* FUN_0067d82c */
    sk_panic(0x6a88ca);                 /* does not return */
}

/* FUN_00685c2c @ 0x00685c2c
 * Ghidra: void FUN_00685c2c(void)
 * Panic with code 0x6a8d63.
 * Confidence: high */
void sk_r72_685c2c_panic(void)
{
    sk_panic(0x6a8d63);
}

/* FUN_00685c64 @ 0x00685c64
 * Ghidra: void FUN_00685c64(void)
 * Panic with code 0x6a8fc4.
 * Confidence: high */
void sk_r72_685c64_panic(void)
{
    sk_panic(0x6a8fc4);
}

/* FUN_00685ca0 @ 0x00685ca0
 * Ghidra: void FUN_00685ca0(void)
 * Panic with code 0x6a8f3a (direct sk_panic path).
 * Confidence: high */
void sk_r72_685ca0_panic(void)
{
    sk_panic(0x6a8f3a);     /* does not return */
}
