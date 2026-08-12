/* Recreated from ringminus1/sk/cl4_kernel.raw (cL4 Secure Kernel / GL1, arm64e,
 * image base 0) — Apple's seL4-derived microkernel. Ground truth: Ghidra
 * FUN_ names + addresses; seL4/cL4 vocabulary. All names are estimates unless
 * header/string-matched. Confidence recorded per function. */
#include <stdint.h>
#include <stddef.h>

/* =====================================================================
 * Shared extern helpers (called by functions in this slice).
 * Address in comment = Ghidra FUN_ address of the real callee.
 * ===================================================================== */

/* ---- noreturn panic / assert printers ---- */
extern void sk_fatal_msg(const char *msg);                       /* FUN_00118b28 */
extern void sk_assert_panic(const char *msg);                    /* FUN_004afae4 */
extern void sk_panic_msg(unsigned long code, const char *fmt, ...); /* FUN_0005b1b0 */
extern void sk_security_assert(const char *msg);                 /* FUN_001150e0 */
extern void sk_obj_panic(unsigned long obj, const char *msg);    /* FUN_0005b190 */
extern void sk_internal_panic(const char *msg);                  /* FUN_0005b12c */
extern void sk_stack_check_fail(void);                           /* FUN_0011d7e8 */
extern void sk_corrupt_panic(void);                              /* FUN_00062c14 */
extern void sk_corrupt_panic_b(void);                            /* FUN_00062bfc */
extern void sk_panic_4(const char *a, const char *b, const char *c,
                       unsigned long d);                         /* FUN_00115424 */

/* ---- cL4 printf/log chain ---- */
extern void sk_log_start(unsigned long v, const char *fmt);      /* FUN_001185ec */
extern void sk_log_append(unsigned long key, const char *fmt, void *ctx); /* FUN_00118c38 */
extern void sk_log_end(unsigned long level, unsigned long key);  /* FUN_001187f4 */
extern void sk_log_trace(unsigned long v, const char *msg);      /* FUN_00118b94 */

/* ---- lock ops (seL4 lock-object acquire/release) ---- */
extern void LOAcquire(void);
extern void LORelease(void);

/* ---- monitor/syscall primitives ---- */
extern void CallSupervisor(unsigned long call);
extern void SoftwareBreakpoint(unsigned long code, unsigned long addr);
extern void sk_raise_bad(unsigned long a, unsigned long b);   /* FUN_000101a0 */
extern unsigned long tpidrro_el0;   /* read of the tpidrro_el0 register (per-CPU base) */

/* ---- globals referenced by bodies ---- */
extern unsigned long _DAT_006b26c4;
extern unsigned long _DAT_006b26c0;
extern unsigned long _DAT_006b2828;
extern unsigned long _DAT_006b2840;

/* ---- panic-report context save/restore wrappers ---- */
extern void sk_err_ctx_save(void);      /* FUN_00041138 */
extern void sk_err_ctx_push(void);      /* FUN_0005e4ac */
extern void sk_err_ctx_pop(void);       /* FUN_0005e4cc */
extern void sk_sched_ctx_save(void);    /* FUN_000604cc */
extern void sk_sched_ctx_restore(void); /* FUN_000604ec */
extern void sk_entropy_ctx_save(void);  /* FUN_00062bdc */
extern void sk_entropy_ctx_restore(void); /* FUN_00061cdc */
extern void sk_cnode_ctx_save(void);    /* FUN_000638ec */
extern void sk_tss_ctx_save(void);      /* FUN_00065138 */
extern void sk_tss_ctx_restore(void);   /* FUN_000651d0 */
extern void sk_ipmm_ctx_save(void);     /* FUN_0006c1b4 */
extern void sk_ipmm_ctx_restore(void);  /* FUN_0006c208 */
extern void sk_ipmm_pre(void);          /* FUN_0006c1d4 */
extern void sk_ipmm_post(void);         /* FUN_0006c1e8 */
extern void sk_list_ctx_save(void);     /* FUN_0006d870 */
extern void sk_list_ctx_restore(void);  /* FUN_0006d890 */

/* ---- kernel / monitor calls ---- */
extern void sk_schedule_thread(unsigned long tcb);  /* FUN_004b23d8 */
extern void sk_trace_put(unsigned long v, const char *fmt, void *ctx); /* FUN_00118b94 */
extern void sk_sys_before(void);   /* FUN_0005b0bc */
extern void sk_sys_wait(unsigned long obj);   /* FUN_0005db7c */
extern void sk_sys_signal(unsigned long obj); /* FUN_0005bf20 */
extern void sk_obj_put(unsigned long obj, unsigned long ref); /* FUN_0019ae60 */
extern void sk_fault_slot(unsigned long obj); /* FUN_0005fd24 */
extern void sk_verify_tag(unsigned long obj, unsigned long tag); /* FUN_000618c4 */
extern void sk_mem_ctx(unsigned long obj, unsigned long n); /* FUN_0005b0bc */
extern unsigned long sk_trace_flags(unsigned long n);   /* FUN_0005b120 */
extern void sk_ctx_save_stack(void *buf, ...);         /* FUN_0004cc24 / FUN_0005ea94 (ctx-save) */
extern void sk_ctx_restore_stack(void *buf, ...);      /* FUN_0004dcd0 / FUN_00062f08 */
extern void sk_irq_restore(unsigned long obj, unsigned long a, unsigned long b, unsigned long c); /* FUN_0004d974 */
extern void sk_reboot(void);                           /* FUN_00116d60 noreturn */
extern void sk_raise(unsigned long arg);               /* FUN_0004c890 */
extern unsigned long sk_ctx_switch(unsigned long thread, void *ctx, void *slot, unsigned long n, unsigned long flags); /* FUN_00061044 */
extern void sk_pool_lock_begin(void *obj);             /* FUN_0005cb9c */
extern void sk_pool_refill(void *pool);                /* FUN_0005ad58 */
extern void sk_pool_lock_end(void *obj);               /* FUN_0005ce54 */
extern unsigned long sk_current_thread(void);          /* FUN_004b5f70 (est.; may panic on entropy fail) */
extern void sk_release_check(unsigned long obj, void *slot, const char *msg, unsigned long flag); /* FUN_0005ae4c */
extern void sk_entropy_init(unsigned long ctx);        /* FUN_0006516c */
extern void sk_entropy_add(unsigned long hi, unsigned long lo, unsigned long kind); /* FUN_00065190 */
extern void sk_entropy_seed_check(unsigned long val);  /* FUN_000651bc */
extern void sk_entropy_bind(unsigned long ctx, unsigned long kind); /* FUN_00065158 */
extern void sk_dispatch_ret(void *ctx, ...);           /* FUN_000647a0 */
extern void sk_mem_enter(void *buf, ...);              /* FUN_000654e8 */
extern void sk_cpu_before(void);                       /* FUN_000651ac */
extern void sk_cpu_touch(void);                        /* FUN_00060524 */
extern void sk_trace_begin(void);                      /* FUN_0005bbd8 */
extern void sk_map_phys(unsigned long a, unsigned long b, unsigned long c); /* FUN_00117f8c */
extern void sk_msg_panic(unsigned long v, const char *msg); /* FUN_00118b94 */
extern void sk_switch_back(void *ctx, ...);            /* FUN_0006bbb0 */
extern void sk_irq_ctl(unsigned long a);               /* FUN_0006c214 */
extern void sk_mem_ops_before(void);                   /* FUN_000410f8 */

/* =====================================================================
 * Function bodies (address order).
 * ===================================================================== */

/* FUN_004b5774 @ 0x004b5774  (est. sk_panic_tb_invalid_error_returned)
 * Ghidra: void FUN_004b5774(void)
 * Fatal TB monitor error: the monitor returned an invalid error code. Logs
 * the "TB_FATAL: invalid error returned" message and never returns.
 * Confidence: high (string-matched) */
static void sk_panic_tb_invalid_error_returned(void)
{
    sk_fatal_msg("TB_FATAL: invalid error returned");  /* s_TB_FATAL__invalid_error_returned_005ba98b */
    /* unreachable (Ghidra SoftwareBreakpoint(1,0x4b57a4) after noreturn call) */
}

/* FUN_004b57a4 @ 0x004b57a4  (est. sk_panic_tb_invalid_error_returned)
 * Ghidra: void FUN_004b57a4(void)
 * Same fatal "invalid error returned" monitor panic as 004b5774, distinct
 * message slot. Does not return.
 * Confidence: high (string-matched) */
static void sk_panic_tb_invalid_error_returned2(void)
{
    sk_fatal_msg("TB_FATAL: invalid error returned");  /* s_TB_FATAL__invalid_error_returned_005ba9c5 */
}

/* FUN_004b57d4 @ 0x004b57d4  (est. sk_panic_tb_invalid_error_returned)
 * Ghidra: void FUN_004b57d4(void)
 * Fatal "TB_FATAL: invalid error returned" monitor panic. Does not return.
 * Confidence: high (string-matched) */
static void sk_panic_tb_invalid_error_returned3(void)
{
    sk_fatal_msg("TB_FATAL: invalid error returned");  /* s_TB_FATAL__invalid_error_returned_005baa02 */
}

/* FUN_004b5804 @ 0x004b5804  (est. sk_panic_tb_invalid_error_returned)
 * Ghidra: void FUN_004b5804(void)
 * Fatal "TB_FATAL: invalid error returned" monitor panic. Does not return.
 * Confidence: high (string-matched) */
static void sk_panic_tb_invalid_error_returned4(void)
{
    sk_fatal_msg("TB_FATAL: invalid error returned");  /* s_TB_FATAL__invalid_error_returned_005baa3a */
}

/* FUN_004b5834 @ 0x004b5834  (est. sk_panic_tb_invalid_error_returned)
 * Ghidra: void FUN_004b5834(void)
 * Fatal "TB_FATAL: invalid error returned" monitor panic. Does not return.
 * Confidence: high (string-matched) */
static void sk_panic_tb_invalid_error_returned5(void)
{
    sk_fatal_msg("TB_FATAL: invalid error returned");  /* s_TB_FATAL__invalid_error_returned_005baa76 */
}

/* FUN_004b5864 @ 0x004b5864  (est. sk_panic_tb_invalid_error_returned)
 * Ghidra: void FUN_004b5864(void)
 * Fatal "TB_FATAL: invalid error returned" monitor panic. Does not return.
 * Confidence: high (string-matched) */
static void sk_panic_tb_invalid_error_returned6(void)
{
    sk_fatal_msg("TB_FATAL: invalid error returned");  /* s_TB_FATAL__invalid_error_returned_005baab4 */
}

/* FUN_004b5894 @ 0x004b5894  (est. sk_panic_tb_invalid_error_returned)
 * Ghidra: void FUN_004b5894(void)
 * Fatal "TB_FATAL: invalid error returned" monitor panic. Does not return.
 * Confidence: high (string-matched) */
static void sk_panic_tb_invalid_error_returned7(void)
{
    sk_fatal_msg("TB_FATAL: invalid error returned");  /* s_TB_FATAL__invalid_error_returned_005baaf0 */
}

/* FUN_004b58c4 @ 0x004b58c4  (est. sk_panic_tb_invalid_error_returned)
 * Ghidra: void FUN_004b58c4(void)
 * Fatal "TB_FATAL: invalid error returned" monitor panic. Does not return.
 * Confidence: high (string-matched) */
static void sk_panic_tb_invalid_error_returned8(void)
{
    sk_fatal_msg("TB_FATAL: invalid error returned");  /* s_TB_FATAL__invalid_error_returned_005bab31 */
}

/* FUN_004b58f4 @ 0x004b58f4  (est. sk_panic_tb_invalid_error_returned)
 * Ghidra: void FUN_004b58f4(void)
 * Fatal "TB_FATAL: invalid error returned" monitor panic. Does not return.
 * Confidence: high (string-matched) */
static void sk_panic_tb_invalid_error_returned9(void)
{
    sk_fatal_msg("TB_FATAL: invalid error returned");  /* s_TB_FATAL__invalid_error_returned_005bab70 */
}

/* FUN_004b5924 @ 0x004b5924  (est. sk_panic_tb_invalid_error_returned)
 * Ghidra: void FUN_004b5924(void)
 * Fatal "TB_FATAL: invalid error returned" monitor panic. Does not return.
 * Confidence: high (string-matched) */
static void sk_panic_tb_invalid_error_returned10(void)
{
    sk_fatal_msg("TB_FATAL: invalid error returned");  /* s_TB_FATAL__invalid_error_returned_005baba8 */
}

/* FUN_004b5954 @ 0x004b5954  (est. sk_panic_tb_invalid_error_returned)
 * Ghidra: void FUN_004b5954(void)
 * Fatal "TB_FATAL: invalid error returned" monitor panic. Does not return.
 * Confidence: high (string-matched) */
static void sk_panic_tb_invalid_error_returned11(void)
{
    sk_fatal_msg("TB_FATAL: invalid error returned");  /* s_TB_FATAL__invalid_error_returned_005babe6 */
}

/* FUN_004b5984 @ 0x004b5984  (est. sk_panic_tb_invalid_error_returned)
 * Ghidra: void FUN_004b5984(void)
 * Fatal "TB_FATAL: invalid error returned" monitor panic. Does not return.
 * Confidence: high (string-matched) */
static void sk_panic_tb_invalid_error_returned12(void)
{
    sk_fatal_msg("TB_FATAL: invalid error returned");  /* s_TB_FATAL__invalid_error_returned_005bac34 */
}

/* FUN_004b59b4 @ 0x004b59b4  (est. sk_panic_tb_invalid_error_returned)
 * Ghidra: void FUN_004b59b4(void)
 * Fatal "TB_FATAL: invalid error returned" monitor panic. Does not return.
 * Confidence: high (string-matched) */
static void sk_panic_tb_invalid_error_returned13(void)
{
    sk_fatal_msg("TB_FATAL: invalid error returned");  /* s_TB_FATAL__invalid_error_returned_005bac74 */
}

/* FUN_004b59e4 @ 0x004b59e4  (est. sk_panic_tb_invalid_error_returned)
 * Ghidra: void FUN_004b59e4(void)
 * Fatal "TB_FATAL: invalid error returned" monitor panic. Does not return.
 * Confidence: high (string-matched) */
static void sk_panic_tb_invalid_error_returned14(void)
{
    sk_fatal_msg("TB_FATAL: invalid error returned");  /* s_TB_FATAL__invalid_error_returned_005bacb1 */
}

/* FUN_004b5a14 @ 0x004b5a14  (est. sk_panic_tb_invalid_error_returned)
 * Ghidra: void FUN_004b5a14(void)
 * Fatal "TB_FATAL: invalid error returned" monitor panic. Does not return.
 * Confidence: high (string-matched) */
static void sk_panic_tb_invalid_error_returned15(void)
{
    sk_fatal_msg("TB_FATAL: invalid error returned");  /* s_TB_FATAL__invalid_error_returned_005bacf0 */
}

/* FUN_004b5a44 @ 0x004b5a44  (est. sk_panic_tb_invalid_error_returned)
 * Ghidra: void FUN_004b5a44(void)
 * Fatal "TB_FATAL: invalid error returned" monitor panic. Does not return.
 * Confidence: high (string-matched) */
static void sk_panic_tb_invalid_error_returned16(void)
{
    sk_fatal_msg("TB_FATAL: invalid error returned");  /* s_TB_FATAL__invalid_error_returned_005bad32 */
}

/* FUN_004b5a74 @ 0x004b5a74  (est. sk_panic_trap_invalid)
 * Ghidra: void FUN_004b5a74(void)
 * Raw illegal/trap entry with no preceding message: traps immediately via
 * SoftwareBreakpoint(1,0x4b5a78).
 * Confidence: low */
static void sk_panic_trap_invalid(void)
{
    /* unreachable trap: SoftwareBreakpoint(1, 0x4b5a78) */
    SoftwareBreakpoint(1, 0x4b5a78);
}

/* FUN_004b5a78 @ 0x004b5a78  (est. sk_panic_trap_bad)
 * Ghidra: void FUN_004b5a78(void)
 * Trap entry that first raises a fixed bad-argument fault code
 * (FUN_000101a0(0, 0x100004077774924)) then traps at 0x4b5aa0.
 * Confidence: low */
static void sk_panic_trap_bad(void)
{
    sk_raise_bad(0, 0x100004077774924ULL);   /* FUN_000101a0 */
    /* unreachable trap: SoftwareBreakpoint(1, 0x4b5aa0) */
    SoftwareBreakpoint(1, 0x4b5aa0);
}

/* FUN_004b5aa0 @ 0x004b5aa0  (est. sk_pmm_self_set_twice_panic)
 * Ghidra: void FUN_004b5aa0(void)
 * PMM panic: set_self was called more than once. Does not return.
 * Confidence: high (string-matched) */
static void sk_pmm_self_set_twice_panic(void)
{
    sk_assert_panic("pmm: set_self: called multiple times");  /* s_pmm__set_self___called_multiple_t_005bad74 */
}

/* FUN_004b5ab8 @ 0x004b5ab8  (est. sk_pmm_self_set_invalid_panic)
 * Ghidra: void FUN_004b5ab8(void)
 * PMM panic: set_self was called with an invalid argument. Does not return.
 * Confidence: high (string-matched) */
static void sk_pmm_self_set_invalid_panic(void)
{
    sk_assert_panic("pmm: set_self: called with invalid...");  /* s_pmm__set_self___called_with_inva_005badc1 */
}

/* FUN_004b5ad0 @ 0x004b5ad0  (est. sk_pmm_alloc_stream_panic)
 * Ghidra: void FUN_004b5ad0(void)
 * libpmm panic: alloc_stream does not support this. Does not return.
 * Confidence: high (string-matched) */
static void sk_pmm_alloc_stream_panic(void)
{
    sk_assert_panic("libpmm: alloc_stream: does not su...");  /* s_libpmm__alloc_stream_does_not_su_005bb07b */
}

/* FUN_004b5ae8 @ 0x004b5ae8  (est. sk_pmm_alloc_slots_panic)
 * Ghidra: void FUN_004b5ae8(void)
 * libpmm panic: alloc_slots failed to allocate. Does not return.
 * Confidence: high (string-matched) */
static void sk_pmm_alloc_slots_panic(void)
{
    sk_assert_panic("libpmm: alloc_slots: failed to al...");  /* s_libpmm__alloc_slots_failed_to_al_005bb0ba */
}

/* FUN_004b5b00 @ 0x004b5b00  (est. sk_pmm_create_object_retry)
 * Ghidra: void FUN_004b5b00(ulong param_1, undefined8 param_2, undefined8 param_3)
 * Retries the monitor create-object call until the pending-bind flag clears;
 * on a non-success final status raises the error and panics
 * "libpmm: create_object: %d, %zx" with the object address.
 * Confidence: medium */
static void sk_pmm_create_object_retry(unsigned long status, unsigned long arg2, unsigned long arg3)
{
    do {
        CallSupervisor(4);
    } while (status == 1);
    if ((status & 0xff) == 0) {
        return;
    }
    sk_raise(arg3);                              /* FUN_0004c890 */
    sk_assert_panic("libpmm: create_object: %d, %zx");  /* s_libpmm__create_object__d____zx____005bb032 */
}

/* FUN_004b5b88 @ 0x004b5b88  (est. sk_panic_report_context)
 * Ghidra: void FUN_004b5b88(undefined8 param_1)
 * Prints the panic-context trailer: emits "  %s: %s: %d: %s" header, appends
 * "%s: %zu" value, and flushes the log line (level 10, key 0xeb1a02bf914012ba).
 * Confidence: medium */
static void sk_panic_report_context(unsigned long v)
{
    char ctx[32];
    sk_log_start(v, "  %s: %s: %d: %s");   /* s___s____s__d____s___005a8c67 */
    sk_log_append(0xeb1a02bf914012baULL, "%s: %zu", ctx);  /* s__s__zu___005a8a1d */
    sk_log_end(10, 0xeb1a02bf914012baULL);  /* FUN_001187f4 */
}

/* FUN_004b5c0c @ 0x004b5c0c  (est. sk_l4_error_panic)
 * Ghidra: void FUN_004b5c0c(void)
 * Prints and panics with the generic "Unexpected L4 Error: %s: %zu, err"
 * message (code 0). Does not return.
 * Confidence: high (string-matched) */
static void sk_l4_error_panic(void)
{
    sk_panic_msg(0, "Unexpected L4 Error: %s: %zu, err");  /* s_Unexpected_L4_Error___s__zu__err_005bb1f9 */
}

/* FUN_004b5c44 @ 0x004b5c44  (est. sk_l4_error_report)
 * Ghidra: void FUN_004b5c44(ulong param_1, undefined1 *param_2)
 * Reports a caught L4 fault: saves the previous context buffer, logs the
 * context, re-enters the message buffer with the fault payload, then prints
 * the "Unexpected L4 Error" trailer. Used by the fault-report trampoline.
 * Confidence: medium */
static void sk_l4_error_report(unsigned long fault, uint8_t *payload)
{
    uint8_t prev_ctx[32];
    uint8_t *ctx = prev_ctx;
    unsigned long saved = fault >> 8;
    sk_panic_report_context(0xeb1a02bf914012baULL);
    sk_ctx_restore_stack(payload, fault);      /* FUN_0004cc24 */
    ctx = payload;
    saved = fault >> 8;
    sk_l4_error_panic();
    sk_log_start(0, "  %s: %s: %d: %s");      /* s___s____s__d____s___005a8c67 */
    sk_log_append(0xeb1a02bf914012baULL, "%s: %zu", &ctx);  /* s__s__zu___005a8a1d */
    sk_log_end(10, 0xeb1a02bf914012baULL);
}

/* FUN_004b5ca4 @ 0x004b5ca4  (est. sk_panic_report_context)
 * Ghidra: void FUN_004b5ca4(undefined8 param_1)
 * Prints the panic-context trailer (same body as 004b5b88).
 * Confidence: medium */
static void sk_panic_report_context2(unsigned long v)
{
    char ctx[32];
    sk_log_start(v, "  %s: %s: %d: %s");   /* s___s____s__d____s___005a8c67 */
    sk_log_append(0xeb1a02bf914012baULL, "%s: %zu", ctx);  /* s__s__zu___005a8a1d */
    sk_log_end(10, 0xeb1a02bf914012baULL);
}

/* FUN_004b5d28 @ 0x004b5d28  (est. sk_pmm_max_cow_regions_panic)
 * Ghidra: void FUN_004b5d28(void)
 * PMM panic: ran out of MAX_COW_REGIONS. Does not return.
 * Confidence: high (string-matched) */
static void sk_pmm_max_cow_regions_panic(void)
{
    sk_assert_panic("Ran out of MAX_COW_REGIONS");  /* s_Ran_out_of__MAX_COW_REGIONS__005bb2c6 */
}

/* FUN_004b5d40 @ 0x004b5d40  (est. sk_init_vector_page_fault)
 * Ghidra: void FUN_004b5d40(undefined8 param_1)
 * Warns that an init vector page is present, restores 0x4000 bytes at the
 * page with prot 8/flags 0xf, then reboots (does not return).
 * Confidence: medium */
static void sk_init_vector_page_fault(unsigned long page)
{
    sk_fatal_msg("Warning: an init vector page ...");  /* s_Warning__an_init_vector_page___l_005bb492 */
    sk_irq_restore(page, 0x4000, 8, 0xf);   /* FUN_0004d974 */
    sk_reboot();                             /* FUN_00116d60 */
}

/* FUN_004b5d80 @ 0x004b5d80  (est. sk_l4_error_report_bad)
 * Ghidra: void FUN_004b5d80(undefined8 param_1, undefined8 param_2)
 * Saves a context buffer, logs the context trailer, then panics with the
 * "Unexpected L4 Error" message using a fresh message buffer.
 * Confidence: medium */
static void sk_l4_error_report_bad(unsigned long a, unsigned long b)
{
    uint8_t ctx[32];
    sk_ctx_save_stack(ctx);                  /* FUN_0004dcd0 */
    sk_panic_report_context2(0xeb1a02bf914012baULL);
    sk_ctx_save_stack((void *)b, a);                 /* FUN_0004dcd0 */
    sk_assert_panic("Unexpected L4 Error: %s: %zu, err");  /* s_Unexpected_L4_Error___s__zu__err_005bb421 */
}

/* FUN_004b5de8 @ 0x004b5de8  (est. sk_rebase_chain_panic)
 * Ghidra: void FUN_004b5de8(void)
 * Panics with "Requested to rebase chain on a p..." (code 0). Does not return.
 * Confidence: high (string-matched) */
static void sk_rebase_chain_panic(void)
{
    sk_panic_msg(0, "Requested to rebase chain on a p...");  /* s_Requested_to_rebase_chain_on_a_p_005bb92b */
}

/* FUN_004b5e20 @ 0x004b5e20  (est. sk_pmm_server_set_twice)
 * Ghidra: void FUN_004b5e20(void)
 * PMM panic: pmm_server_already_set. Calls the rebase-chain panic then
 * asserts. Does not return.
 * Confidence: high (string-matched) */
static void sk_pmm_server_set_twice(void)
{
    sk_rebase_chain_panic();
    sk_assert_panic("pmm_server already set");  /* s_pmm_server_already_set_005bb96f */
}

/* FUN_004b5e30 @ 0x004b5e30  (est. sk_pmm_server_set_twice)
 * Ghidra: void FUN_004b5e30(void)
 * PMM panic: pmm_server_already_set. Does not return.
 * Confidence: high (string-matched) */
static void sk_pmm_server_set_twice2(void)
{
    sk_assert_panic("pmm_server already set");  /* s_pmm_server_already_set_005bb96f */
}

/* FUN_004b5e48 @ 0x004b5e48  (est. sk_pmm_alloc_slot_panic)
 * Ghidra: void FUN_004b5e48(void)
 * PMM per-thread panic: failed to allocate a slot. Does not return.
 * Confidence: high (string-matched) */
static void sk_pmm_alloc_slot_panic(void)
{
    sk_assert_panic("Failed to alloc slot in pmm perthrea...");  /* s_Failed_to_alloc_slot_in_pmm_pert_005bba1f */
}

/* FUN_004b5e60 @ 0x004b5e60  (est. sk_pmm_slotarg_null_panic)
 * Ghidra: void FUN_004b5e60(void)
 * PMM per-thread panic: slotarg was NULL. Does not return.
 * Confidence: high (string-matched) */
static void sk_pmm_slotarg_null_panic(void)
{
    sk_assert_panic("slotarg was NULL in pmm perthrea...");  /* s_slotarg_was_NULL_in_pmm_perthrea_005bba57 */
}

/* FUN_004b5e78 @ 0x004b5e78  (est. sk_pmm_no_cnodes_panic)
 * Ghidra: void FUN_004b5e78(void)
 * PMM panic: no cnode found, need %zd slots. Does not return.
 * Confidence: high (string-matched) */
static void sk_pmm_no_cnodes_panic(void)
{
    sk_assert_panic("no cnodes found: need %zd slots f...");  /* s_no_cnodes_found__need__zd_slots_f_005bbbfd */
}

/* FUN_004b5e9c @ 0x004b5e9c  (est. sk_pmm_bad_slot_layout_panic)
 * Ghidra: void FUN_004b5e9c(void)
 * PMM panic: bad slot layout: nodes %zx. Does not return.
 * Confidence: high (string-matched) */
static void sk_pmm_bad_slot_layout_panic(void)
{
    sk_assert_panic("bad slot layout: nodes %zx");  /* s_bad_slot_layout__nodes____zx_____005bbadb */
}

/* FUN_004b5ee0 @ 0x004b5ee0  (est. sk_pmm_boot_slot_reserve_panic)
 * Ghidra: void FUN_004b5ee0(void)
 * PMM panic: boot_slot_reserve was empty. Does not return.
 * Confidence: high (string-matched) */
static void sk_pmm_boot_slot_reserve_panic(void)
{
    sk_assert_panic("boot_slot_reserve empty");  /* s_boot_slot_reserve_empty_005bbb72 */
}

/* FUN_004b5ef8 @ 0x004b5ef8  (est. sk_rand_loc_fail_panic)
 * Ghidra: void FUN_004b5ef8(void)
 * Panics with "unable to get random location fo..." (code 0). Does not return.
 * Confidence: high (string-matched) */
static void sk_rand_loc_fail_panic(void)
{
    sk_panic_msg(0, "unable to get random location fo...");  /* s_unable_to_get_random_location_fo_005bbe99 */
}

/* FUN_004b5f30 @ 0x004b5f30  (est. sk_security_assert_fail)
 * Ghidra: void FUN_004b5f30(void)
 * Security assertion failure: logs "Security assertion failed: %s: %f" and
 * does not return.
 * Confidence: high (string-matched) */
static void sk_security_assert_fail(void)
{
    sk_security_assert("Security assertion failed: %s: %f");  /* s_Security_assertion_failed___s__f_005a8b30 */
}

/* FUN_004b5f70 @ 0x004b5f70  (est. sk_entropy_fail)
 * Ghidra: void FUN_004b5f70(void)
 * Entropy failure panic: prints "Failed to take entropy for insec..." (code
 * 0) and does not return. NOTE: in callers this is used as a value-returning
 * "current thread" getter whose entropy-failure branch Ghidra collapsed; the
 * x0 return is lost in the decompile. Confidence: low */
static unsigned long sk_entropy_fail(void)
{
    sk_panic_msg(0, "Failed to take entropy for insec...");  /* s_Failed_to_take_entropy_for_insec_005bbeed */
    return 0;
}

/* FUN_004b5fa8 @ 0x004b5fa8  (est. sk_sync_trace_alloc)
 * Ghidra: undefined8 FUN_004b5fa8(undefined8 param_1, undefined8 param_2, long param_3)
 * Allocates an entry from the single global sync-trace pool (key 0x6b04b8)
 * for the current thread, populates it with the given data word, stamps a
 * trace length, and links it onto the thread's pending-trace list
 * (thread+0x60). Returns 1 on success, 0 when the pool is exhausted. Guards
 * re-entrancy with the thread+0x48 bit-4 flag and an atomic pool counter.
 * Traps (SoftwareBreakpoint 0x5519) on pool/pointer corruption.
 * Confidence: medium */
static unsigned long sk_sync_trace_alloc(unsigned long unused_a, unsigned long unused_b, unsigned long data)
{
    uint8_t *flags = (uint8_t *)((unsigned long)sk_entropy_fail() + 0x48);
    void **slot;
    void **prev;
    unsigned long idx;
    unsigned long count;
    unsigned long n;
    uint8_t saved_ctx[16];

    if (((*flags >> 4) & 1) == 0) {
        uint32_t *pool = (uint32_t *)sk_trace_flags(0x6b04b8);   /* FUN_0005b120 */
        slot = (void **)*(unsigned long *)((char *)pool + 0x58); /* free-list head */
        if (slot == NULL) {
            /* pool exhausted on free-list: bump the atomic counter */
            LOAcquire();
            idx = *(unsigned long *)((char *)pool + 0x50);
            *(unsigned long *)((char *)pool + 0x50) = idx + 1;
            LORelease();
            *flags |= 0x10;
            sk_pool_lock_begin((char *)pool + 0x10);   /* FUN_0005cb9c */
            if (idx < *(unsigned long *)((char *)pool + 0x28)) {
                if (idx < *(unsigned long *)((char *)pool + 0x48)) {
                    sk_pool_refill(pool);              /* FUN_0005ad58 */
                }
            } else {
                count = *(unsigned long *)((char *)pool + 0x50);
                *(unsigned long *)((char *)pool + 0x50) = count - 1;
                sk_log_trace(count, "xrt: sync trace pool exhausted");  /* s__xrt__sync_trace_pool_exhausted_005bc466 */
                *pool = 3;                             /* pool state = exhausted */
            }
            sk_pool_lock_end((char *)pool + 0x10);     /* FUN_0005ce54 */
            *flags &= ~0x10;
            if (*(unsigned long *)((char *)pool + 0x28) <= idx) {
                return 0;
            }
            slot = (void **)(*(unsigned long *)((char *)pool + 0x40) + idx * 0x40);
            prev = slot + 8;
            goto init_slot;
        }
        prev = slot + 8;
        if (prev < slot) goto trap;
        do {
        } while (*(void **)((char *)pool + 0x58) != slot);
        *(void **)((char *)pool + 0x58) = *slot;
        *slot = NULL;
init_slot:
        saved_ctx[8] = 0;
        if (prev < slot + 8 || slot + 8 < slot) goto trap;
        *slot = NULL;
        slot[1] = (void *)data;
        slot[3] = NULL;
        slot[4] = NULL;
        slot[5] = NULL;
        slot[6] = NULL;
        slot[7] = NULL;
        slot[2] = NULL;
        n = sk_ctx_switch((unsigned long)sk_entropy_fail(), saved_ctx, slot + 2, 5, 0); /* FUN_00061044 */
        if (4 < n) n = 5;
        slot[7] = (void *)n;
        prev = (void **)((unsigned long)sk_entropy_fail() + 0x60);
        do {
            if (*slot != NULL) {
                sk_internal_panic("AppleInternal Library BuildRoot");  /* FUN_0005b12c */
            }
            count = (unsigned long)*prev;
            *slot = (void *)count;
            if ((void **)((unsigned long)sk_entropy_fail() + 0x68) < prev) goto trap;
        } while ((unsigned long)*prev != count);
        *prev = (void *)slot;
    }
    return 1;
trap:
    /* SoftwareBreakpoint(0x5519, 0x4b6194): detected pool/list corruption */
    SoftwareBreakpoint(0x5519, 0x4b6194);
    return 0;
}

/* FUN_004b5fb8 @ 0x004b5fb8  (est. sk_sync_trace_alloc_for)
 * Ghidra: undefined8 FUN_004b5fb8(long param_1, undefined8 param_2, long param_3)
 * Identical to 004b5fa8 but takes the target thread explicitly in param_1
 * instead of deriving it from the current thread; allocates a sync-trace entry
 * and links it onto thread+0x60. Returns 1 on success, 0 when the pool is
 * exhausted. Confidence: medium */
static unsigned long sk_sync_trace_alloc_for(unsigned long thread, unsigned long tag, unsigned long data)
{
    uint8_t *flags = (uint8_t *)(thread + 0x48);
    void **slot;
    void **prev;
    unsigned long idx;
    unsigned long count;
    unsigned long n;
    unsigned long saved_ctx;

    if (((*flags >> 4) & 1) == 0) {
        uint32_t *pool = (uint32_t *)sk_trace_flags(0x6b04b8);   /* FUN_0005b120 */
        slot = (void **)*(unsigned long *)((char *)pool + 0x58);
        if (slot == NULL) {
            LOAcquire();
            idx = *(unsigned long *)((char *)pool + 0x50);
            *(unsigned long *)((char *)pool + 0x50) = idx + 1;
            LORelease();
            *flags |= 0x10;
            sk_pool_lock_begin((char *)pool + 0x10);
            if (idx < *(unsigned long *)((char *)pool + 0x28)) {
                if (idx < *(unsigned long *)((char *)pool + 0x48)) {
                    sk_pool_refill(pool);
                }
            } else {
                count = *(unsigned long *)((char *)pool + 0x50);
                *(unsigned long *)((char *)pool + 0x50) = count - 1;
                sk_log_trace(count, "xrt: sync trace pool exhausted");
                *pool = 3;
            }
            sk_pool_lock_end((char *)pool + 0x10);
            *flags &= ~0x10;
            if (*(unsigned long *)((char *)pool + 0x28) <= idx) {
                return 0;
            }
            slot = (void **)(*(unsigned long *)((char *)pool + 0x40) + idx * 0x40);
            prev = slot + 8;
            goto init_slot;
        }
        prev = slot + 8;
        if (prev < slot) goto trap;
        do {
        } while (*(void **)((char *)pool + 0x58) != slot);
        *(void **)((char *)pool + 0x58) = *slot;
        *slot = NULL;
init_slot:
        saved_ctx = tag;
        if (prev < slot + 8 || slot + 8 < slot) goto trap;
        *slot = NULL;
        slot[1] = (void *)data;
        slot[3] = NULL;
        slot[4] = NULL;
        slot[5] = NULL;
        slot[6] = NULL;
        slot[7] = NULL;
        slot[2] = NULL;
        n = sk_ctx_switch(thread, &saved_ctx, slot + 2, 5, 0);  /* FUN_00061044 */
        if (4 < n) n = 5;
        slot[7] = (void *)n;
        prev = (void **)(thread + 0x60);
        do {
            if (*slot != NULL) {
                sk_internal_panic("AppleInternal Library BuildRoot");
            }
            count = (unsigned long)*prev;
            *slot = (void *)count;
            if ((void **)(thread + 0x68) < prev) goto trap;
        } while ((unsigned long)*prev != count);
        *prev = (void *)slot;
    }
    return 1;
trap:
    /* SoftwareBreakpoint(0x5519, 0x4b6194) */
    SoftwareBreakpoint(0x5519, 0x4b6194);
    return 0;
}

/* FUN_004b6194 @ 0x004b6194  (est. sk_release_held_object)
 * Ghidra: void FUN_004b6194(long param_1, long param_2)
 * Releases a previously-held synchronisation object (param_2) from the held-
 * object list rooted at param_1+0x60. Walks the list, unlinks the matching
 * entry, returns it to the shared pool free-list (pool+0x58), and validates
 * the held-object invariants; panics with specific messages when the object
 * is not held, was released while being held, or is a synchronisation object
 * release that should go through the sync path. Traps on list corruption.
 * Confidence: medium */
static void sk_release_held_object(unsigned long owner, unsigned long target)
{
    uint8_t *flags = (uint8_t *)(owner + 0x48);
    long *node;
    long *next;
    long *prev;
    long count;
    unsigned long head;

    if (((*flags >> 4) & 1) == 0) {
        unsigned long chk1 = 1, chk2 = 1;
        uint32_t *pool = (uint32_t *)sk_trace_flags(0x6b04b8);   /* FUN_0005b120 */
        uint32_t flags2 = *(uint32_t *)((char *)pool + 0x20);
        if ((flags2 >> 1) & 1) {
            chk1 = (*(unsigned long *)((char *)pool + 0x20) & 4) == 0;
            chk2 = (*(uint8_t *)((char *)pool + 0x20) & 8) == 0;
        }
        node = *(long **)(owner + 0x60);
        if (node == NULL) {
            sk_obj_panic(owner, "release_unheld_object: %p");  /* s_release_unheld_object__p_005bc2bb */
        }
        next = node + 8;
        if (node[1] == (long)target) {
            prev = NULL;
        } else {
            do {
                prev = next;
                if (chk2) {
                    if (next < node) goto trap;
                    sk_release_check(owner, node, "released outer object while hold", chk1);  /* s_released_outer_object_while_hold_005bc297 */
                }
                node = (long *)*node;
                if (node == NULL) {
                    sk_obj_panic(owner, "release_unheld_object: %p");
                }
                next = node + 8;
            } while (node[1] != (long)target);
        }
        if (node != (long *)*(long *)(owner + 0x60)) {
            if (chk2) {
                if (next < node) goto trap;
                sk_release_check(owner, node, "released", chk1);  /* s_released_005bc2d4 */
            }
            if (!((flags2 >> 1) & 1)) {
                sk_obj_panic(owner, "released synchronisation object o...");  /* s_released_synchronisation_object_o_005bc2dd */
            }
        }
        if (prev == NULL) {
            if ((long *)(owner + 0x68) < (long *)(owner + 0x60)) goto trap;
            do {
                prev = (long *)*(long *)(owner + 0x60);
                if (prev == NULL) goto not_in_list;
                if (prev + 8 < prev) goto trap;
            } while (*(long *)(owner + 0x60) != (long)prev);
            *(long *)(owner + 0x60) = *prev;
        } else {
            if (prev < node + 8) goto trap;
            *prev = *node;
        }
        node = prev;
not_in_list:
        *node = 0;
        do {
            if (*node != 0) {
                sk_internal_panic("AppleInternal Library BuildRoot");
            }
            count = *(long *)((char *)sk_trace_flags(0x6b04b8) + 0x58);  /* pool free-list head */
            *node = count;
        } while (*(long *)((char *)sk_trace_flags(0x6b04b8) + 0x58) != count);
        *(long *)((char *)sk_trace_flags(0x6b04b8) + 0x58) = (long)node;
    }
    return;
trap:
    /* SoftwareBreakpoint(0x5519, 0x4b63ac): list corruption */
    SoftwareBreakpoint(0x5519, 0x4b63ac);
}

/* FUN_004b63cc @ 0x004b63cc  (est. sk_release_all_held_on_exit)
 * Ghidra: void FUN_004b63cc(long param_1)
 * Walks the held-object list at param_1+0x60 and panics with
 * "exited returned while holding" for the first still-held object, i.e. an
 * object that was not released before a thread exited. Traps on corruption.
 * Confidence: medium */
static void sk_release_all_held_on_exit(unsigned long owner)
{
    unsigned long *node = *(unsigned long **)(owner + 0x60);
    while (1) {
        if (node == NULL) return;
        if (node + 8 < node) break;
        sk_release_check(owner, node, "exited returned while holding", 1);  /* s_exited_returned_while_holding_005bc349 */
        node = (unsigned long *)*node;
    }
    /* SoftwareBreakpoint(0x5519, 0x4b6430) */
    SoftwareBreakpoint(0x5519, 0x4b6430);
}

/* FUN_004b6430 @ 0x004b6430  (est. sk_fault_retry_report)
 * Ghidra: void FUN_004b6430(undefined8 param_1)
 * Retry/report trampoline for a faulted IPC: re-enters the faulted context
 * (0x1b8 bytes), maps the error-code permission-invalid string, and decodes
 * the monitor return status into one of the L4 error-code strings
 * (SlotInvalid / MethodInvalid / ArgumentInvalid / OperationInvalid /
 * PermissionInvalid), flushing the panic-context trailer and re-entering the
 * fault handler. Falls through to the error report + stack-check on return.
 * Confidence: low */
static void sk_fault_retry_report(unsigned long arg)
{
    unsigned long status;
    uint64_t tmp;
    uint64_t code;
    char ctx[8];
    void *save;
    unsigned long st;

    sk_ctx_save_stack((void *)arg, 0x1b8, 0, 0);   /* FUN_0005ea94 */
    save = (void *)sk_ctx_switch(0x37, 0, 0, 0, 0);  /* FUN_0005ee58 */
    sk_log_start(0, "L4 Error: PermissionInvalid");  /* s_L4_ErrorCodePermissionInvalid_00689d90 + 5 */
    sk_log_end(0, 0);
    status = 0;
    if (status != 0) {
        sk_dispatch_ret(&tmp, &ctx);       /* FUN_000639a0 */
        sk_log_end(0, 0);
        if (9 < (unsigned long)(uint8_t)status) {
            sk_switch_back(NULL);          /* FUN_0005c588 */
            goto done;
        }
        switch ((unsigned int)status) {
        default: break;
        case 1: sk_log_end(0, 0x706d); break;   /* FUN_0005c510 */
        case 2: sk_log_end(0, 0); break;        /* FUN_0005c570 */
        case 3: sk_log_end(0, 0x6163); break;   /* FUN_0005c510 */
        case 4: sk_log_end(0, 0); break;        /* FUN_0005c520 */
        case 5:
            sk_log_start(0, "L4 Error: SlotInvalid");  /* s_L4_ErrorCodeSlotInvalid_004bdf8f */
            sk_ctx_save_stack(NULL);         /* FUN_0005c490 */
            sk_log_end(0, 0);
            goto done;
        case 6:
            sk_log_start(0, "L4 Error: MethodInvalid");  /* s_L4_ErrorCodeMethodInvalid_004bdfaf */
            goto flush;
        case 7:
            sk_log_start(0, "L4 Error: ArgumentInvalid"); /* s_L4_ErrorCodeArgumentInvalid_004bdfcf */
            goto flush;
        case 8:
            sk_log_start(0, "L4 Error: OperationInvalid"); /* s_L4_ErrorCodeOperationInvalid_004bdfef */
            goto flush;
        case 9:
            sk_log_start(0, "L4 Error: PermissionInvalid"); /* s_L4_ErrorCodePermissionInvalid_004be00f */
flush:
            sk_log_end(0, 0);
            goto done;
        }
        sk_ctx_save_stack(NULL);            /* FUN_0005c414 */
        sk_log_end(0, 0);
    }
done:
    sk_panic_report_context(arg);           /* FUN_004b67e4 */
    if (0 != (long)0xd37afd4bb400012aULL) { /* stack canary check */
        sk_stack_check_fail();              /* FUN_0011d7e8 */
    }
}

/* FUN_004b67e4 @ 0x004b67e4  (est. sk_panic_report_context)
 * Ghidra: void FUN_004b67e4(undefined8 param_1)
 * Prints the panic-context trailer with the "panic_call_returned" message.
 * Confidence: medium */
static void sk_panic_report_context_call(unsigned long v)
{
    char ctx[32];
    sk_log_start(v, "  %s: %s: %d: %s");      /* s___s____s__d____s___005a8c67 */
    sk_log_append(0xeb1a02bf914012baULL, "%s: %zu: panic call returned", ctx);  /* s__s__zu___panic_call_returned_005bc6a9 */
    sk_log_end(10, 0xeb1a02bf914012baULL);
}

/* FUN_004b6864 @ 0x004b6864  (est. sk_security_assert_fail)
 * Ghidra: void FUN_004b6864(void)
 * Security assertion failure (same body as 004b5f30). Does not return.
 * Confidence: high (string-matched) */
static void sk_security_assert_fail2(void)
{
    sk_security_assert("Security assertion failed: %s: %f");  /* s_Security_assertion_failed___s__f_005a8b30 */
}

/* FUN_004b68a4 @ 0x004b68a4  (est. sk_timebase_not_updated_panic)
 * Ghidra: void FUN_004b68a4(void)
 * Panics "timebases were not updated after..." for object 0. Does not return.
 * Confidence: high (string-matched) */
static void sk_timebase_not_updated_panic(void)
{
    sk_obj_panic(0, "timebases were not updated after");  /* s_timebases_were_not_updated_after_005bc6eb */
}

/* FUN_004b68c0 @ 0x004b68c0  (est. sk_panic_report_context)
 * Ghidra: void FUN_004b68c0(undefined8 param_1)
 * Prints the panic-context trailer. Confidence: medium */
static void sk_panic_report_context3(unsigned long v)
{
    char ctx[32];
    sk_log_start(v, "  %s: %s: %d: %s");   /* s___s____s__d____s___005a8c67 */
    sk_log_append(0xeb1a02bf914012baULL, "%s: %zu", ctx);  /* s__s__zu___005a8a1d */
    sk_log_end(10, 0xeb1a02bf914012baULL);
}

/* FUN_004b6938 @ 0x004b6938  (est. sk_assert_fail_report)
 * Ghidra: void FUN_004b6938(void)
 * Standard assertion-failure reporter: saves err context, pushes the panic
 * context, prints the trailer, pops it, then panics with "Unexpected L4
 * Error". Does not return. Confidence: medium */
static void sk_assert_fail_report(void)
{
    sk_err_ctx_save();        /* FUN_00041138 */
    sk_err_ctx_push();        /* FUN_0005e4ac */
    sk_panic_report_context3(0);
    sk_err_ctx_pop();         /* FUN_0005e4cc */
    sk_assert_panic("Unexpected L4 Error: %s: %zu, err");  /* s_Unexpected_L4_Error___s__zu__err_005bc93d */
}

/* FUN_004b6984 @ 0x004b6984  (est. sk_assert_fail_report)
 * Ghidra: void FUN_004b6984(void)
 * Assertion-failure reporter (message variant). Does not return.
 * Confidence: medium */
static void sk_assert_fail_report2(void)
{
    sk_err_ctx_save();
    sk_err_ctx_push();
    sk_panic_report_context3(0);
    sk_err_ctx_pop();
    sk_assert_panic("Unexpected L4 Error: %s: %zu, err");  /* s_Unexpected_L4_Error___s__zu__err_005bc844 */
}

/* FUN_004b69d0 @ 0x004b69d0  (est. sk_schedule_thread_retry)
 * Ghidra: void FUN_004b69d0(undefined2 *param_1, long param_2, ulong *param_3)
 * Schedule entry used during thread bootstrap: spins on a monitor call until
 * the pending flag clears, then writes the given runnable-state word into the
 * target TCB message area. Verifies the monitor's method-invalid sentinel
 * constant (L4_ErrorCodeMethodInvalid) before scheduling; sets the
 * out-parameter bit 3 (bad) if the sentinel is unexpected, otherwise calls the
 * schedule routine and panics "couldn't schedule thread" on failure.
 * Confidence: medium */
static void sk_schedule_thread_retry(unsigned short *msg, unsigned long state, unsigned long *out)
{
    unsigned short lo = *msg;
    uint8_t m1 = *(uint8_t *)((char *)msg + 3);
    uint8_t m2 = *(uint8_t *)((char *)msg + 2);
    unsigned short hi = msg[2];
    uint8_t m3 = *(uint8_t *)((char *)msg + 7);
    uint8_t m4 = *(uint8_t *)((char *)msg + 6);
    uint64_t sentinel;
    unsigned long v;

    do {
        CallSupervisor(0);
        *msg = lo;
        *(uint8_t *)((char *)msg + 5) = (uint8_t)(hi >> 8);
        *(uint8_t *)((char *)msg + 3) = m1;
        *(uint8_t *)((char *)msg + 2) = m2;
        *(uint8_t *)((char *)msg + 1) = (uint8_t)(lo >> 8);
        msg[2] = hi;
        *(uint8_t *)((char *)msg + 7) = m3;
        *(uint8_t *)((char *)msg + 6) = m4;
    } while (state == 1);

    /* little-endian 8-byte store of `state` at byte offset 0x1c0
     * (decompile's `param_1 + 0xe0` is undefined2* arithmetic = +0x1c0 bytes) */
    *(uint8_t *)((char *)msg + 0x1c0) = (uint8_t)state;
    *(uint8_t *)((char *)msg + 0x1c5) = (uint8_t)(state >> 0x28);
    *(uint8_t *)((char *)msg + 0x1c3) = (uint8_t)(state >> 0x18);
    *(uint8_t *)((char *)msg + 0x1c2) = (uint8_t)(state >> 0x10);
    *(uint8_t *)((char *)msg + 0x1c1) = (uint8_t)(state >> 8);
    *(uint8_t *)((char *)msg + 0x1c4) = (uint8_t)(state >> 0x20);
    *(uint8_t *)((char *)msg + 0x1c7) = (uint8_t)(state >> 0x38);
    *(uint8_t *)((char *)msg + 0x1c6) = (uint8_t)(state >> 0x30);

    /* check the monitor's method-invalid error sentinel (L4_ErrorCodeMethodInvalid,
     * a fixed non-zero constant; the decompile reads the 8 bytes at 0x689e9c..0x689ea3
     * and ORs 0x10000 — this check never fires, kept faithful as dead-code branch). */
    sentinel = 0x10000UL
        | ((uint8_t)'E' << 0x18) | ((uint8_t)'_' << 0x10) | ((uint8_t)'4' << 8) | (uint8_t)'L'
        | (((unsigned long)((uint8_t)'i') << 0x18) | ((unsigned long)'n' << 0x10)
           | ((unsigned long)(uint8_t)'v' << 8) | (unsigned long)'a') << 0x20;
    *(uint8_t *)((char *)msg) = 0x40;
    *(uint8_t *)((char *)msg + 1) = 0;
    *(uint8_t *)((char *)msg + 4) = 0;   /* param_1+2 (undefined2*) */
    *(uint8_t *)((char *)msg + 5) = 0;
    *(uint8_t *)((char *)msg + 2) = 1;   /* param_1+1 */
    *(uint8_t *)((char *)msg + 3) = 0;
    *(uint8_t *)((char *)msg + 6) = 0;   /* param_1+3 */
    *(uint8_t *)((char *)msg + 7) = 0;
    CallSupervisor(0);
    *(uint8_t *)((char *)msg) = 0x40;
    *(uint8_t *)((char *)msg + 7) = 0;
    *(uint8_t *)((char *)msg + 6) = 0;
    *(uint8_t *)((char *)msg + 5) = 0;
    *(uint8_t *)((char *)msg + 4) = 0;
    *(uint8_t *)((char *)msg + 3) = 0;
    *(uint8_t *)((char *)msg + 2) = 1;
    *(uint8_t *)((char *)msg + 1) = 0;
    *(uint8_t *)((char *)msg + 0x1e5) = 0;
    *(uint8_t *)((char *)msg + 0x1e3) = 0;
    *(uint8_t *)((char *)msg + 0x1e2) = 0;  /* param_1+0xf1 */
    *(uint8_t *)((char *)msg + 0x1e1) = 0;
    *(uint8_t *)((char *)msg + 0x1e4) = 0;  /* param_1+0xf2 */
    *(uint8_t *)((char *)msg + 0x1e0) = 0;  /* param_1+0xf0 */
    *(uint8_t *)((char *)msg + 0x1e7) = 0;
    *(uint8_t *)((char *)msg + 0x1e6) = 0;  /* param_1+0xf3 */

    if (sentinel == 0) {
        *out |= 8;
        return;
    }
    sk_schedule_thread(state);             /* FUN_004b23d8 */
    sk_obj_panic(0, "couldn't schedule thread");  /* FUN_0005b190 s_couldn_t_schedule_thread_005bc8b1 */
}

/* FUN_004b6c04 @ 0x004b6c04  (est. sk_assert_fail_report)
 * Ghidra: void FUN_004b6c04(void)
 * Assertion-failure reporter (message variant). Does not return.
 * Confidence: medium */
static void sk_assert_fail_report3(void)
{
    sk_err_ctx_save();
    sk_err_ctx_push();
    sk_panic_report_context3(0);
    sk_err_ctx_pop();
    sk_assert_panic("Unexpected L4 Error: %s: %zu, err");  /* s_Unexpected_L4_Error___s__zu__err_005bca47 */
}

/* FUN_004b6c50 @ 0x004b6c50  (est. sk_assert_fail_report)
 * Ghidra: void FUN_004b6c50(void)
 * Assertion-failure reporter (message variant). Does not return.
 * Confidence: medium */
static void sk_assert_fail_report4(void)
{
    sk_err_ctx_save();
    sk_err_ctx_push();
    sk_panic_report_context3(0);
    sk_err_ctx_pop();
    sk_assert_panic("Unexpected L4 Error: %s: %zu, err");  /* s_Unexpected_L4_Error___s__zu__err_005bc9d1 */
}

/* FUN_004b6c9c @ 0x004b6c9c  (est. sk_assert_fail_report)
 * Ghidra: void FUN_004b6c9c(void)
 * Assertion-failure reporter (message variant). Does not return.
 * Confidence: medium */
static void sk_assert_fail_report5(void)
{
    sk_err_ctx_save();
    sk_err_ctx_push();
    sk_panic_report_context3(0);
    sk_err_ctx_pop();
    sk_assert_panic("Unexpected L4 Error: %s: %zu, err");  /* s_Unexpected_L4_Error___s__zu__err_005bcae2 */
}

/* FUN_004b6ce8 @ 0x004b6ce8  (est. sk_panic_report_context)
 * Ghidra: void FUN_004b6ce8(undefined8 param_1)
 * Prints the panic-context trailer. Confidence: medium */
static void sk_panic_report_context4(unsigned long v)
{
    char ctx[32];
    sk_log_start(v, "  %s: %s: %d: %s");   /* s___s____s__d____s___005a8c67 */
    sk_log_append(0xeb1a02bf914012baULL, "%s: %zu", ctx);  /* s__s__zu___005a8a1d */
    sk_log_end(10, 0xeb1a02bf914012baULL);
}

/* FUN_004b6d60 @ 0x004b6d60  (est. sk_tcb_destroy)
 * Ghidra: void FUN_004b6d60(long param_1)
 * Destroys a TCB: runs the sys-before hooks, signals/wakes its two wait
 * objects, releases the objects at +0x108 (ref 0x15) and +0x110 (ref 0x14)
 * and the master object at +0x28 (ref 6), drains the pending scheduling
 * flags, releases the bound scheduler TCBs, then invokes the object's
 * destroy method (vtbl at +0x38 with instance at +0x30).
 * Confidence: medium */
static void sk_tcb_destroy(unsigned long tcb)
{
    sk_sys_before();                        /* FUN_0005b0bc */
    sk_sys_wait(tcb);                       /* FUN_0005db7c */
    sk_sys_signal(tcb);                     /* FUN_0005bf20 */
    if (*(long *)(tcb + 0x108) != 0) {
        sk_obj_put(*(long *)(tcb + 0x108), 0x15);  /* FUN_0019ae60 */
        *(unsigned long *)(tcb + 0x108) = 0;
    }
    if (*(long *)(tcb + 0x110) != 0) {
        sk_obj_put(*(long *)(tcb + 0x110), 0x14);
        *(unsigned long *)(tcb + 0x110) = 0;
    }
    sk_obj_put(*(unsigned long *)(tcb + 0x28), 6);
    do { CallSupervisor(5); } while (*(long *)(tcb + 0x88) == 1);
    do { CallSupervisor(4); } while (*(long *)(tcb + 0x88) == 1);
    sk_schedule_thread(*(unsigned long *)(tcb + 0x88));
    do { CallSupervisor(4); } while (*(long *)(tcb + 0x70) == 1);
    sk_schedule_thread(*(unsigned long *)(tcb + 0x70));
    /* jumptable dispatch into destroy method; Ghidra: indirect call
     * (*(code**)**(uint64**)(tcb+0x38))(*(uint64*)(tcb+0x30)) */
    (*(void (**)(void *))**(unsigned long **)(tcb + 0x38))(*(void **)(tcb + 0x30));
}

/* FUN_004b6e24 @ 0x004b6e24  (est. sk_assert_fail_report)
 * Ghidra: void FUN_004b6e24(void)
 * Assertion-failure reporter using the scheduler context hooks. Does not
 * return. Confidence: medium */
static void sk_assert_fail_report6(void)
{
    sk_sched_ctx_save();       /* FUN_000604cc */
    sk_panic_report_context4(0);
    sk_sched_ctx_restore();    /* FUN_000604ec */
    sk_assert_panic("Unexpected L4 Error: %s: %zu, err");  /* s_Unexpected_L4_Error___s__zu__err_005b010f */
}

/* FUN_004b6e74 @ 0x004b6e74  (est. sk_enabled_counter_inc)
 * Ghidra: void FUN_004b6e74(void)
 * Increments the global enabled-counter (DAT_006b26c4).
 * Confidence: medium */
static void sk_enabled_counter_inc(void)
{
    _DAT_006b26c4 = _DAT_006b26c4 + 1;  /* global counter DAT_006b26c4 */
}

/* FUN_004b6e88 @ 0x004b6e88  (est. sk_enabled_counter_inc2)
 * Ghidra: void FUN_004b6e88(void)
 * Increments the global enabled-counter (DAT_006b26c0).
 * Confidence: medium */
static void sk_enabled_counter_inc2(void)
{
    _DAT_006b26c0 = _DAT_006b26c0 + 1;  /* global counter DAT_006b26c0 */
}

/* FUN_004b6e9c @ 0x004b6e9c  (est. sk_tcb_unbind_sched)
 * Ghidra: void FUN_004b6e9c(long param_1)
 * Drains the pending scheduling flag (monitor call until clear) and releases
 * the TCB's bound scheduler reference.
 * Confidence: medium */
static void sk_tcb_unbind_sched(unsigned long tcb)
{
    do { CallSupervisor(4); } while (*(long *)(tcb + 0x88) == 1);
    sk_schedule_thread(*(unsigned long *)(tcb + 0x88));
}

/* FUN_004b6ed0 @ 0x004b6ed0  (est. sk_assert_fail_report)
 * Ghidra: void FUN_004b6ed0(void)
 * Assertion-failure reporter using the scheduler context hooks. Does not
 * return. Confidence: medium */
static void sk_assert_fail_report7(void)
{
    sk_sched_ctx_save();
    sk_panic_report_context4(0);
    sk_sched_ctx_restore();
    sk_assert_panic("Unexpected L4 Error: %s: %zu, err");  /* s_Unexpected_L4_Error___s__zu__err_005bcfd0 */
}

/* FUN_004b6f20 @ 0x004b6f20  (est. sk_key_in_destructor_panic)
 * Ghidra: void FUN_004b6f20(void)
 * Panics "getting key %lu while destructor..." for object 0. Does not return.
 * Confidence: high (string-matched) */
static void sk_key_in_destructor_panic(void)
{
    sk_obj_panic(0, "getting key %lu while destructor...");  /* s_getting_key__lu_while_destructor_005ab2c6 */
}

/* FUN_004b6f48 @ 0x004b6f48  (est. sk_key_deleted_panic)
 * Ghidra: void FUN_004b6f48(void)
 * Panics "getting key %lu which is deleted..." for object 0. Does not return.
 * Confidence: high (string-matched) */
static void sk_key_deleted_panic(void)
{
    sk_obj_panic(0, "getting key %lu which is deleted...");  /* s_getting_key__lu_which_is_deleted_005ab2a5 */
}

/* FUN_004b6f70 @ 0x004b6f70  (est. sk_assert_fail_report)
 * Ghidra: void FUN_004b6f70(void)
 * Assertion-failure reporter using the scheduler context hooks. Does not
 * return. Confidence: medium */
static void sk_assert_fail_report8(void)
{
    sk_sched_ctx_save();
    sk_panic_report_context4(0);
    sk_sched_ctx_restore();
    sk_assert_panic("Unexpected L4 Error: %s: %zu, err");  /* s_Unexpected_L4_Error___s__zu__err_005bd0a6 */
}

/* FUN_004b6fc0 @ 0x004b6fc0  (est. sk_counter_overflow_panic)
 * Ghidra: void FUN_004b6fc0(void)
 * Panics "overflowed enabled counter". Does not return.
 * Confidence: high (string-matched) */
static void sk_counter_overflow_panic(void)
{
    sk_assert_panic("overflowed enabled counter");  /* s_overflowed_enabled_counter_005bd0f9 */
}

/* FUN_004b6fd8 @ 0x004b6fd8  (est. sk_counter_underflow_panic)
 * Ghidra: void FUN_004b6fd8(void)
 * Panics "underflowed enabled counter". Does not return.
 * Confidence: high (string-matched) */
static void sk_counter_underflow_panic(void)
{
    sk_assert_panic("underflowed enabled counter");  /* s_underflowed_enabled_counter_005bd114 */
}

/* FUN_004b6ff0 @ 0x004b6ff0  (est. sk_altstack_counter_wrap_panic)
 * Ghidra: void FUN_004b6ff0(void)
 * Panics "altstack create counter wrapped". Does not return.
 * Confidence: high (string-matched) */
static void sk_altstack_counter_wrap_panic(void)
{
    sk_assert_panic("altstack create counter wrapped");  /* s_altstack_create_counter_wrapped_005bd2b3 */
}

/* FUN_004b7008 @ 0x004b7008  (est. sk_overflow_detected_panic)
 * Ghidra: void FUN_004b7008(void)
 * Panics "overflow detected". Does not return.
 * Confidence: high (string-matched) */
static void sk_overflow_detected_panic(void)
{
    sk_assert_panic("overflow detected");  /* s_overflow_detected_005bbac8 */
}

/* FUN_004b7020 @ 0x004b7020  (est. sk_panic_report_context)
 * Ghidra: void FUN_004b7020(undefined8 param_1)
 * Prints the panic-context trailer. Confidence: medium */
static void sk_panic_report_context5(unsigned long v)
{
    char ctx[32];
    sk_log_start(v, "  %s: %s: %d: %s");   /* s___s____s__d____s___005a8c67 */
    sk_log_append(0xeb1a02bf914012baULL, "%s: %zu", ctx);  /* s__s__zu___005a8a1d */
    sk_log_end(10, 0xeb1a02bf914012baULL);
}

/* FUN_004b7098 @ 0x004b7098  (est. sk_internal_panic)
 * Ghidra: void FUN_004b7098(void)
 * Internal panic: "AppleInternal Library BuildRoot". Does not return.
 * Confidence: high (string-matched) */
static void sk_internal_panic_buildroot(void)
{
    sk_internal_panic("AppleInternal Library BuildRoot");  /* s__AppleInternal_Library_BuildRoot_005bd30c */
}

/* FUN_004b70c8 @ 0x004b70c8  (est. sk_internal_panic)
 * Ghidra: void FUN_004b70c8(void)
 * Internal panic: "AppleInternal Library BuildRoot". Does not return.
 * Confidence: high (string-matched) */
static void sk_internal_panic_buildroot2(void)
{
    sk_internal_panic("AppleInternal Library BuildRoot");  /* s__AppleInternal_Library_BuildRoot_005bd30c */
}

/* FUN_004b70f8 @ 0x004b70f8  (est. sk_corrupt_panic)
 * Ghidra: void FUN_004b70f8(void)
 * Corruption panic (FUN_00062c14). Does not return.
 * Confidence: low */
static void sk_corrupt_panic_wrap(void)
{
    sk_corrupt_panic();  /* FUN_00062c14 */
}

/* FUN_004b710c @ 0x004b710c  (est. sk_corrupt_panic_b)
 * Ghidra: void FUN_004b710c(void)
 * Corruption panic (FUN_00062bfc). Does not return.
 * Confidence: low */
static void sk_corrupt_panic_b_wrap(void)
{
    sk_corrupt_panic_b();  /* FUN_00062bfc */
}

/* FUN_004b7120 @ 0x004b7120  (est. sk_entropy_insert_fail_panic)
 * Ghidra: void FUN_004b7120(void)
 * Panics "Failed to insert entropy into pr...". Does not return.
 * Confidence: high (string-matched) */
static void sk_entropy_insert_fail_panic(void)
{
    sk_assert_panic("Failed to insert entropy into pr...");  /* s_Failed_to_insert_entropy_into_pr_005bd880 */
}

/* FUN_004b7138 @ 0x004b7138  (est. sk_entropy_no_root_panic)
 * Ghidra: void FUN_004b7138(void)
 * Panics "No entropy passed to non roottas...". Does not return.
 * Confidence: high (string-matched) */
static void sk_entropy_no_root_panic(void)
{
    sk_assert_panic("No entropy passed to non roottas...");  /* s_No_entropy_passed_to_non_roottas_005bd8b2 */
}

/* FUN_004b7150 @ 0x004b7150  (est. sk_assert_fail_report)
 * Ghidra: void FUN_004b7150(void)
 * Assertion-failure reporter using the entropy context hooks. Does not return.
 * Confidence: medium */
static void sk_assert_fail_report9(void)
{
    sk_entropy_ctx_save();       /* FUN_00062bdc */
    sk_panic_report_context5(0);
    sk_entropy_ctx_restore();    /* FUN_00061cdc */
    sk_assert_panic("Unexpected L4 Error: %s: %zu, err");  /* s_Unexpected_L4_Error___s__zu__err_005bd923 */
}

/* FUN_004b71a8 @ 0x004b71a8  (est. sk_assert_fail_report)
 * Ghidra: void FUN_004b71a8(void)
 * Assertion-failure reporter using the entropy context hooks. Does not return.
 * Confidence: medium */
static void sk_assert_fail_report10(void)
{
    sk_entropy_ctx_save();
    sk_panic_report_context5(0);
    sk_entropy_ctx_restore();
    sk_assert_panic("Unexpected L4 Error: %s: %zu, err");  /* s_Unexpected_L4_Error___s__zu__err_005bd436 */
}

/* FUN_004b7200 @ 0x004b7200  (est. sk_panic_report_context)
 * Ghidra: void FUN_004b7200(undefined8 param_1)
 * Prints the panic-context trailer. Confidence: medium */
static void sk_panic_report_context6(unsigned long v)
{
    char ctx[32];
    sk_log_start(v, "  %s: %s: %d: %s");   /* s___s____s__d____s___005a8c67 */
    sk_log_append(0xeb1a02bf914012baULL, "%s: %zu", ctx);  /* s__s__zu___005a8a1d */
    sk_log_end(10, 0xeb1a02bf914012baULL);
}

/* FUN_004b7278 @ 0x004b7278  (est. sk_fault_retry_tcb)
 * Ghidra: void FUN_004b7278(long param_1)
 * Retry trampoline for a faulted TCB: spins on a monitor call until the
 * pending flag clears, then for a non-success final status re-enters the
 * fault message buffer, prints the panic context, and panics "Unexpected L4
 * Error". Confidence: medium */
static void sk_fault_retry_tcb(unsigned long tcb)
{
    uint8_t buf[32];
    unsigned long state = *(unsigned long *)(tcb + 0x28);
    uint16_t *msg = (uint16_t *)tpidrro_el0;
    unsigned short lo = *msg;
    uint8_t m1 = *(uint8_t *)((char *)msg + 3);
    uint8_t m2 = *(uint8_t *)((char *)msg + 2);
    unsigned short hi = msg[2];
    uint8_t m3 = *(uint8_t *)((char *)msg + 7);
    uint8_t m4 = *(uint8_t *)((char *)msg + 6);

    do {
        CallSupervisor(0);
        *msg = lo;
        *(uint8_t *)((char *)msg + 5) = (uint8_t)(hi >> 8);
        *(uint8_t *)((char *)msg + 3) = m1;
        *(uint8_t *)((char *)msg + 2) = m2;
        *(uint8_t *)((char *)msg + 1) = (uint8_t)(lo >> 8);
        msg[2] = hi;
        *(uint8_t *)((char *)msg + 7) = m3;
        *(uint8_t *)((char *)msg + 6) = m4;
    } while (state == 1);

    if ((state & 0xff) != 0) {
        sk_ctx_restore_stack(buf, state, 0x10);   /* FUN_00062f08 */
        sk_panic_report_context6(0xeb1a02bf914012baULL);
        sk_ctx_restore_stack(buf, state);         /* FUN_00062f08 */
        sk_assert_panic("Unexpected L4 Error: %s: %zu, err");  /* s_Unexpected_L4_Error___s__zu__err_005bdd7c */
    }
}

/* FUN_004b73d0 @ 0x004b73d0  (est. sk_assert_fail_report)
 * Ghidra: void FUN_004b73d0(void)
 * Assertion-failure reporter using the cnode context hooks. Does not return.
 * Confidence: medium */
static void sk_assert_fail_report11(void)
{
    sk_cnode_ctx_save();       /* FUN_000638ec */
    sk_panic_report_context6(0);
    sk_ctx_restore_stack(NULL);   /* FUN_00062f08 */
    sk_assert_panic("Unexpected L4 Error: %s: %zu, err");  /* s_Unexpected_L4_Error___s__zu__err_005bdd06 */
}

/* FUN_004b7428 @ 0x004b7428  (est. sk_assert_fail_report)
 * Ghidra: void FUN_004b7428(void)
 * Assertion-failure reporter using the cnode context hooks. Does not return.
 * Confidence: medium */
static void sk_assert_fail_report12(void)
{
    sk_cnode_ctx_save();
    sk_panic_report_context6(0);
    sk_ctx_restore_stack(NULL);
    sk_assert_panic("Unexpected L4 Error: %s: %zu, err");  /* s_Unexpected_L4_Error___s__zu__err_005bddfd */
}

/* FUN_004b7480 @ 0x004b7480  (est. sk_tss_destructors_running_panic)
 * Ghidra: void FUN_004b7480(void)
 * Panics "tss destructors running: cannot a..." for object 0. Does not return.
 * Confidence: high (string-matched) */
static void sk_tss_destructors_running_panic(void)
{
    sk_obj_panic(0, "tss destructors running: cannot a...");  /* s_tss_destructors_running__cannot_a_005bdeaa */
}

/* FUN_004b749c @ 0x004b749c  (est. sk_tss_keys_exhausted_panic)
 * Ghidra: void FUN_004b749c(void)
 * Panics "exhausted TSS keys". Does not return.
 * Confidence: high (string-matched) */
static void sk_tss_keys_exhausted_panic(void)
{
    sk_assert_panic("exhausted TSS keys");  /* s_exhausted_TSS_keys_005bded5 */
}

/* FUN_004b74b4 @ 0x004b74b4  (est. sk_tss_init_nonstatic_panic)
 * Ghidra: void FUN_004b74b4(void)
 * Panics "attempted to init non static TSS...". Does not return.
 * Confidence: high (string-matched) */
static void sk_tss_init_nonstatic_panic(void)
{
    sk_assert_panic("attempted to init non static TSS...");  /* s_attempted_to_init_non_static_TSS_005bdee8 */
}

/* FUN_004b74b8 @ 0x004b74b8  (est. sk_tss_init_nonstatic_panic)
 * Ghidra: void FUN_004b74b8(void)
 * Panics "attempted to init non static TSS..." (same as 004b74b4). Does not
 * return. Confidence: high (string-matched) */
static void sk_tss_init_nonstatic_panic2(void)
{
    sk_assert_panic("attempted to init non static TSS...");  /* s_attempted_to_init_non_static_TSS_005bdee8 */
}

/* FUN_004b74cc @ 0x004b74cc  (est. sk_panic_report_context)
 * Ghidra: void FUN_004b74cc(undefined8 param_1)
 * Prints the panic-context trailer. Confidence: medium */
static void sk_panic_report_context7(unsigned long v)
{
    char ctx[32];
    sk_log_start(v, "  %s: %s: %d: %s");   /* s___s____s__d____s___005a8c67 */
    sk_log_append(0xeb1a02bf914012baULL, "%s: %zu", ctx);  /* s__s__zu___005a8a1d */
    sk_log_end(10, 0xeb1a02bf914012baULL);
}

/* FUN_004b7544 @ 0x004b7544  (est. sk_assert_fail_report)
 * Ghidra: void FUN_004b7544(void)
 * Assertion-failure reporter using the TSS context hooks. Does not return.
 * Confidence: medium */
static void sk_assert_fail_report13(void)
{
    sk_tss_ctx_save();       /* FUN_00065138 */
    sk_panic_report_context7(0);
    sk_tss_ctx_restore();    /* FUN_000651d0 */
    sk_assert_panic("Unexpected L4 Error: %s: %zu, err");  /* s_Unexpected_L4_Error___s__zu__err_005be06a */
}

/* FUN_004b7594 @ 0x004b7594  (est. sk_assert_fail_report)
 * Ghidra: void FUN_004b7594(void)
 * Assertion-failure reporter using the TSS context hooks. Does not return.
 * Confidence: medium */
static void sk_assert_fail_report14(void)
{
    sk_tss_ctx_save();
    sk_panic_report_context7(0);
    sk_tss_ctx_restore();
    sk_assert_panic("Unexpected L4 Error: %s: %zu, err");  /* s_Unexpected_L4_Error___s__zu__err_005be132 */
}

/* FUN_004b75e4 @ 0x004b75e4  (est. sk_tcb_entangle)
 * Ghidra: undefined4 FUN_004b75e4(ulong param_1, ulong param_2, long *param_3)
 * Entangles (binds) TCB param_1 to a target: drains the pending scheduling
 * flag, validates the target range, tags the TCB with 'expt', sets its busy
 * bit (bit 0 of +0x48), rebinds, and returns the entanglement state code via
 * out-param: 0 = rejected (out of range), 1 = entangled (target empty), 2 =
 * entangled with existing occupant. Confidence: medium */
static unsigned int sk_tcb_entangle(unsigned long tcb, unsigned long target, long *out)
{
    unsigned int rc;

    do { CallSupervisor(5); } while (*(long *)(tcb + 0x88) == 1);
    if (target < tcb) {
        rc = 0;
    } else {
        sk_verify_tag(tcb, 0x65787074);    /* 'expt' tag */
        *(unsigned long *)(tcb + 0x48) |= 1;
        sk_fault_slot(tcb);                /* FUN_0005fd24 */
        *out = *(long *)(tcb + 0x50);
        rc = 1;
        if (*out != 0) rc = 2;
    }
    return rc;
}

/* FUN_004b7664 @ 0x004b7664  (est. sk_assert_fail_report)
 * Ghidra: void FUN_004b7664(void)
 * Assertion-failure reporter using the TSS context hooks. Does not return.
 * Confidence: medium */
static void sk_assert_fail_report15(void)
{
    sk_tss_ctx_save();
    sk_panic_report_context7(0);
    sk_tss_ctx_restore();
    sk_assert_panic("Unexpected L4 Error: %s: %zu, err");  /* s_Unexpected_L4_Error___s__zu__err_005be288 */
}

/* FUN_004b76b4 @ 0x004b76b4  (est. sk_assert_fail_report)
 * Ghidra: void FUN_004b76b4(void)
 * Assertion-failure reporter using the TSS context hooks. Does not return.
 * Confidence: medium */
static void sk_assert_fail_report16(void)
{
    sk_tss_ctx_save();
    sk_panic_report_context7(0);
    sk_tss_ctx_restore();
    sk_assert_panic("Unexpected L4 Error: %s: %zu, err");  /* s_Unexpected_L4_Error___s__zu__err_005be330 */
}

/* FUN_004b7704 @ 0x004b7704  (est. sk_ipc_msg_retry)
 * Ghidra: void FUN_004b7704(long param_1, undefined8 *param_2, ulong param_3)
 * IPC message send/recv retry trampoline: seeds entropy from the per-CPU
 * ID, spins on a monitor call until the pending flag clears while writing the
 * message word, then verifies the result; on failure re-enters the fault
 * context, prints the panic trailer, and panics "Unexpected L4 Error".
 * Confidence: low */
static void sk_ipc_msg_retry(unsigned long tcb, unsigned long *msg, unsigned long word)
{
    uint8_t buf[32];
    unsigned long state = *(unsigned long *)(tcb + 0x28);
    uint8_t *cpu = (uint8_t *)tpidrro_el0;
    uint8_t saved;
    unsigned long result;

    sk_entropy_init((unsigned long)cpu[2] << 0x10 | (unsigned long)*(uint8_t *)(cpu + 3) << 0x18 | (unsigned long)cpu[0]);  /* FUN_0006516c */
    do {
        saved = 0;
        CallSupervisor(0);
        cpu[0] = (uint8_t)word;
        cpu[5] = (uint8_t)(word >> 0x28);
        cpu[3] = (uint8_t)(word >> 0x18);
        cpu[2] = (uint8_t)(word >> 0x10);
        cpu[1] = (uint8_t)(word >> 8);
        sk_entropy_add(word >> 0x20, state, 0x12);  /* FUN_00065190 */
        saved = 1;
    } while (!saved);

    state = *(unsigned long *)(tcb + 0x28);
    result = *msg;
    cpu[0] = (uint8_t)result;
    cpu[1] = (uint8_t)(result >> 8);
    cpu[2] = (uint8_t)(result >> 0x10);
    cpu[3] = (uint8_t)(result >> 0x18);
    cpu[4] = (uint8_t)(result >> 0x20);
    cpu[5] = (uint8_t)(result >> 0x28);
    cpu[6] = (uint8_t)(result >> 0x30);
    cpu[7] = (uint8_t)(result >> 0x38);
    CallSupervisor(0);
    cpu[0] = (uint8_t)result;
    cpu[7] = (uint8_t)(result >> 0x38);
    cpu[6] = (uint8_t)(result >> 0x30);
    cpu[5] = (uint8_t)(result >> 0x28);
    cpu[4] = (uint8_t)(result >> 0x20);
    cpu[3] = (uint8_t)(result >> 0x18);
    cpu[2] = (uint8_t)(result >> 0x10);
    cpu[1] = (uint8_t)(result >> 8);

    if ((state & 0xff) == 0) {
        sk_entropy_seed_check(0xd37afd4bb400012aULL);  /* FUN_000651bc */
        return;
    }
    sk_entropy_bind(state, 0x11);          /* FUN_00065158 */
    sk_dispatch_ret(buf);                  /* FUN_000647a0 */
    sk_panic_report_context7((unsigned long)cpu + 2);
    sk_dispatch_ret((void *)word, msg);            /* FUN_000647a0 */
    sk_assert_panic("Unexpected L4 Error: %s: %zu, err");  /* s_Unexpected_L4_Error___s__zu__err_005be1ad */
}

/* FUN_004b78c0 @ 0x004b78c0  (est. sk_trace_begin_report)
 * Ghidra: void FUN_004b78c0(void)
 * Begins a trace and prints the "xrt: Image %02hhX:%02hhX:%02hhX" header line.
 * Confidence: medium */
static void sk_trace_begin_report(void)
{
    sk_trace_begin();                     /* FUN_0005bbd8 */
    sk_log_start(0xeb1a02bf914012baULL, "xrt: Image %02hhX:%02hhX:%02hhX");  /* s__xrt__Image___02hhX_02hhX_02hhX__005be491 */
}

/* FUN_004b7984 @ 0x004b7984  (est. sk_cpu_trace_report)
 * Ghidra: void FUN_004b7984(void)
 * CPU-trace report: binds entropy context, touches the CPU, and starts the
 * log line. Confidence: low */
static void sk_cpu_trace_report(void)
{
    sk_entropy_bind(0, 0);                /* FUN_00065158 */
    sk_cpu_touch();                       /* FUN_00060524 */
    sk_log_start(0, NULL);
}

/* FUN_004b79c8 @ 0x004b79c8  (est. sk_cpu_trace_report)
 * Ghidra: void FUN_004b79c8(void)
 * CPU-trace report (variant using FUN_000651ac). Confidence: low */
static void sk_cpu_trace_report2(void)
{
    sk_cpu_before();                      /* FUN_000651ac */
    sk_cpu_touch();                       /* FUN_00060524 */
    sk_log_start(0, NULL);
}

/* FUN_004b7a0c @ 0x004b7a0c  (est. sk_panic_report_context)
 * Ghidra: void FUN_004b7a0c(undefined8 param_1)
 * Prints the panic-context trailer. Confidence: medium */
static void sk_panic_report_context8(unsigned long v)
{
    char ctx[32];
    sk_log_start(v, "  %s: %s: %d: %s");   /* s___s____s__d____s___005a8c67 */
    sk_log_append(0xeb1a02bf914012baULL, "%s: %zu", ctx);  /* s__s__zu___005a8a1d */
    sk_log_end(10, 0xeb1a02bf914012baULL);
}

/* FUN_004b7a90 @ 0x004b7a90  (est. sk_l4_error_panic)
 * Ghidra: void FUN_004b7a90(void)
 * Panics with the generic "Unexpected L4 Error" message (code 0). Does not
 * return. Confidence: high (string-matched) */
static void sk_l4_error_panic2(void)
{
    sk_panic_msg(0, "Unexpected L4 Error: %s: %zu, err");  /* s_Unexpected_L4_Error___s__zu__err_005be610 */
}

/* FUN_004b7ac8 @ 0x004b7ac8  (est. sk_l4_error_report)
 * Ghidra: void FUN_004b7ac8(ulong param_1, undefined1 *param_2)
 * Reports a caught L4 fault (like 004b5c44): re-enters the message buffer
 * with the payload and prints the "Unexpected L4 Error" trailer.
 * Confidence: medium */
static void sk_l4_error_report2(unsigned long fault, uint8_t *payload)
{
    uint8_t prev_ctx[32];
    uint8_t *ctx = prev_ctx;
    unsigned long saved = fault >> 8;
    sk_panic_report_context8(0xeb1a02bf914012baULL);
    sk_mem_enter(payload, fault);          /* FUN_000654e8 */
    ctx = payload;
    saved = fault >> 8;
    sk_l4_error_panic2();
    sk_log_start(0, "  %s: %s: %d: %s");  /* s___s____s__d____s___005a8c67 */
    sk_log_append(0xeb1a02bf914012baULL, "%s: %zu", &ctx);  /* s__s__zu___005a8a1d */
    sk_log_end(10, 0xeb1a02bf914012baULL);
}

/* FUN_004b7b28 @ 0x004b7b28  (est. sk_panic_report_context)
 * Ghidra: void FUN_004b7b28(undefined8 param_1)
 * Prints the panic-context trailer. Confidence: medium */
static void sk_panic_report_context9(unsigned long v)
{
    char ctx[32];
    sk_log_start(v, "  %s: %s: %d: %s");   /* s___s____s__d____s___005a8c67 */
    sk_log_append(0xeb1a02bf914012baULL, "%s: %zu", ctx);  /* s__s__zu___005a8a1d */
    sk_log_end(10, 0xeb1a02bf914012baULL);
}

/* FUN_004b7ba0 @ 0x004b7ba0  (est. sk_assert_fail_report)
 * Ghidra: void FUN_004b7ba0(void)
 * Assertion-failure reporter using the ipmm context hooks. Does not return.
 * Confidence: medium */
static void sk_assert_fail_report17(void)
{
    sk_err_ctx_save();       /* FUN_00041138 */
    sk_ipmm_ctx_save();      /* FUN_0006c1b4 */
    sk_panic_report_context9(0);
    sk_ipmm_ctx_restore();   /* FUN_0006c208 */
    sk_assert_panic("Unexpected L4 Error: %s: %zu, err");  /* s_Unexpected_L4_Error___s__zu__err_005bebb6 */
}

/* FUN_004b7bec @ 0x004b7bec  (est. sk_ipmm_map_retry)
 * Ghidra: void FUN_004b7bec(ulong param_1)
 * ipmm map retry: runs the ipmm pre-hook, spins on a monitor call until the
 * pending flag clears, and on a non-success final status re-enters the fault
 * context, prints the panic trailer, and panics "Unexpected L4 Error".
 * Confidence: medium */
static void sk_ipmm_map_retry(unsigned long status)
{
    uint8_t ok;

    sk_ipmm_pre();                         /* FUN_0006c1d4 */
    do { CallSupervisor(4); } while (status == 1);
    ok = (status & 0xff) == 0;
    if (ok) {
        sk_mem_ops_before();               /* FUN_000410f8 */
        if (ok) return;
        sk_stack_check_fail();             /* FUN_0011d7e8 */
    }
    sk_ipmm_post();                        /* FUN_0006c1e8 */
    sk_panic_report_context9(0);
    sk_switch_back(NULL);                  /* FUN_0006bbb0 */
    sk_assert_panic("Unexpected L4 Error: %s: %zu, err");  /* s_Unexpected_L4_Error___s__zu__err_005bec76 */
}

/* FUN_004b7c88 @ 0x004b7c88  (est. sk_assert_fail_report)
 * Ghidra: void FUN_004b7c88(void)
 * Assertion-failure reporter using the ipmm context hooks. Does not return.
 * Confidence: medium */
static void sk_assert_fail_report18(void)
{
    sk_err_ctx_save();
    sk_ipmm_ctx_save();
    sk_panic_report_context9(0);
    sk_ipmm_ctx_restore();
    sk_assert_panic("Unexpected L4 Error: %s: %zu, err");  /* s_Unexpected_L4_Error___s__zu__err_005becdd */
}

/* FUN_004b7cd4 @ 0x004b7cd4  (est. sk_assert_fail_report)
 * Ghidra: void FUN_004b7cd4(void)
 * Assertion-failure reporter using the ipmm context hooks. Does not return.
 * Confidence: medium */
static void sk_assert_fail_report19(void)
{
    sk_err_ctx_save();
    sk_ipmm_ctx_save();
    sk_panic_report_context9(0);
    sk_ipmm_ctx_restore();
    sk_assert_panic("Unexpected L4 Error: %s: %zu, err");  /* s_Unexpected_L4_Error___s__zu__err_005b010f */
}

/* FUN_004b7d20 @ 0x004b7d20  (est. sk_ipmm_unmap_retry)
 * Ghidra: void FUN_004b7d20(ulong param_1, undefined8 param_2)
 * ipmm unmap retry: runs the ipmm pre-hook, maps a phys region, spins on a
 * monitor call until the pending flag clears, and on non-success re-enters
 * the fault context and panics "Unexpected L4 Error".
 * Confidence: medium */
static void sk_ipmm_unmap_retry(unsigned long status, unsigned long arg)
{
    uint8_t buf[40];
    uint8_t ok;

    sk_ipmm_pre();
    sk_map_phys(_DAT_006b2840, 0x4000, 0xffffffffffffffffULL);  /* FUN_00117f8c */
    do { CallSupervisor(5); } while (status == 1);
    ok = (status & 0xff) == 0;
    if (ok) {
        sk_mem_ops_before();
        if (ok) return;
        sk_stack_check_fail();
    }
    sk_switch_back(buf);                   /* FUN_0006bbb0 */
    sk_panic_report_context9(0xeb1a02bf914012baULL);
    sk_switch_back((void *)arg, status);           /* FUN_0006bbb0 */
    sk_assert_panic("Unexpected L4 Error: %s: %zu, err");  /* s_Unexpected_L4_Error___s__zu__err_005bed86 */
}

/* FUN_004b7dec @ 0x004b7dec  (est. sk_ipmm_oom_panic)
 * Ghidra: void FUN_004b7dec(undefined8 param_1, undefined8 param_2, undefined8 param_3)
 * ipmm out-of-memory panic: logs "iPMM: Out of Memory", prints the alloc
 * context, and panics "Unexpected L4 Error". Does not return.
 * Confidence: medium */
static void sk_ipmm_oom_panic(unsigned long a, unsigned long b, unsigned long c)
{
    uint8_t buf[32];
    sk_log_trace(0, "iPMM: Out of Memory");  /* s__iPMM__Out_of_Memory__005befae */
    sk_switch_back(buf, 8);
    sk_panic_report_context9(0xeb1a02bf914012baULL);
    sk_log_start(0, "ipmm_alloc");         /* s__ipmm_alloc_005becd1 */
    sk_switch_back((void *)a, 8);
    sk_assert_panic("Unexpected L4 Error: %s: %zu, err");  /* s_Unexpected_L4_Error___s__zu__err_005bed1e */
}

/* FUN_004b7e64 @ 0x004b7e64  (est. sk_assert_fail_report)
 * Ghidra: void FUN_004b7e64(void)
 * Assertion-failure reporter using the ipmm context hooks. Does not return.
 * Confidence: medium */
static void sk_assert_fail_report20(void)
{
    sk_err_ctx_save();
    sk_ipmm_ctx_save();
    sk_panic_report_context9(0);
    sk_ipmm_ctx_restore();
    sk_assert_panic("Unexpected L4 Error: %s: %zu, err");  /* s_Unexpected_L4_Error___s__zu__err_005b010f */
}

/* FUN_004b7eb0 @ 0x004b7eb0  (est. sk_ipmm_state_init_panic)
 * Ghidra: void FUN_004b7eb0(void)
 * Panics when the ipmm state has already been initialized: emits the state,
 * buildroot, and free message symbols with line 0x16d. Does not return.
 * Confidence: medium */
static void sk_ipmm_state_init_panic(void)
{
    sk_panic_4("ipmm state initialized", "AppleInternal Library BuildRoot",
               "ipmm_free", 0x16d);  /* s__ipmm_state_initialized_005bee35 s__AppleInternal_Library_BuildRoot_005be83c s__ipmm_free_005bee4d */
}

/* FUN_004b7edc @ 0x004b7edc  (est. sk_assert_fail_report)
 * Ghidra: void FUN_004b7edc(void)
 * Assertion-failure reporter using the ipmm context hooks. Does not return.
 * Confidence: medium */
static void sk_assert_fail_report21(void)
{
    sk_err_ctx_save();
    sk_ipmm_ctx_save();
    sk_irq_ctl(0x4b7ef8);                 /* FUN_0006c214 */
    sk_panic_report_context9(0);
    sk_ipmm_ctx_restore();
    sk_assert_panic("Unexpected L4 Error: %s: %zu, err");  /* s_Unexpected_L4_Error___s__zu__err_005bee81 */
}

/* FUN_004b7f24 @ 0x004b7f24  (est. sk_assert_fail_report)
 * Ghidra: void FUN_004b7f24(void)
 * Assertion-failure reporter using the ipmm context hooks. Does not return.
 * Confidence: medium */
static void sk_assert_fail_report22(void)
{
    sk_err_ctx_save();
    sk_ipmm_ctx_save();
    sk_irq_ctl(0x4b7f40);
    sk_panic_report_context9(0);
    sk_ipmm_ctx_restore();
    sk_assert_panic("Unexpected L4 Error: %s: %zu, err");  /* s_Unexpected_L4_Error___s__zu__err_005beec2 */
}

/* FUN_004b7f6c @ 0x004b7f6c  (est. sk_assert_fail_report)
 * Ghidra: void FUN_004b7f6c(void)
 * Assertion-failure reporter using the ipmm context hooks. Does not return.
 * Confidence: medium */
static void sk_assert_fail_report23(void)
{
    sk_err_ctx_save();
    sk_ipmm_ctx_save();
    sk_irq_ctl(0x4b7f88);
    sk_panic_report_context9(0);
    sk_ipmm_ctx_restore();
    sk_assert_panic("Unexpected L4 Error: %s: %zu, err");  /* s_Unexpected_L4_Error___s__zu__err_005beeff */
}

/* FUN_004b7fb4 @ 0x004b7fb4  (est. sk_ipmm_free_retry)
 * Ghidra: void FUN_004b7fb4(ulong param_1)
 * ipmm free retry: runs the ipmm pre-hook, spins on a monitor call until the
 * pending flag clears, and on non-success re-enters the fault context and
 * panics "Unexpected L4 Error"; on success bumps the free counter
 * (DAT_006b2828) and returns.
 * Confidence: medium */
static void sk_ipmm_free_retry(unsigned long status)
{
    uint8_t ok;

    sk_ipmm_pre();
    do { CallSupervisor(5); } while (status == 1);
    ok = (status & 0xff) == 0;
    if (ok) {
        _DAT_006b2828 = _DAT_006b2828 + 1;  /* global counter DAT_006b2828 */
        sk_mem_ops_before();
        if (ok) return;
        sk_stack_check_fail();
    }
    sk_ipmm_post();
    sk_irq_ctl(0);
    sk_panic_report_context9(0);
    sk_switch_back(NULL);
    sk_assert_panic("Unexpected L4 Error: %s: %zu, err");  /* s_Unexpected_L4_Error___s__zu__err_005beec2 */
}

/* FUN_004b8054 @ 0x004b8054  (est. sk_overflow_detected_panic)
 * Ghidra: void FUN_004b8054(void)
 * Panics "overflow detected" (code 0). Does not return.
 * Confidence: high (string-matched) */
static void sk_overflow_detected_panic2(void)
{
    sk_panic_msg(0, "overflow detected");  /* s_overflow_detected_005bbac8 */
}

/* FUN_004b808c @ 0x004b808c  (est. sk_bad_list_head_panic)
 * Ghidra: void FUN_004b808c(void)
 * Security assertion: "Bad list head: p->first > prev...". Does not return.
 * Confidence: high (string-matched) */
static void sk_bad_list_head_panic(void)
{
    sk_security_assert("Bad list head: p->first >prev ...");  /* s_Bad_list_head__p_first_>prev____h_005bf16c */
}

/* FUN_004b80b8 @ 0x004b80b8  (est. sk_overflow_report)
 * Ghidra: void FUN_004b80b8(void)
 * Reports an overflow-detected panic then prints the panic-context trailer.
 * Confidence: low */
static void sk_overflow_report(void)
{
    sk_overflow_detected_panic2();
    sk_log_start(0, "  %s: %s: %d: %s");      /* s___s____s__d____s___005a8c67 */
    sk_log_append(0xeb1a02bf914012baULL, 0, (void *)0xfffffffffffffff0ULL);
    sk_log_end(10, 0xeb1a02bf914012baULL);
}

/* FUN_004b80c8 @ 0x004b80c8  (est. sk_panic_report_context)
 * Ghidra: void FUN_004b80c8(undefined8 param_1)
 * Prints the panic-context trailer. Confidence: medium */
static void sk_panic_report_context10(unsigned long v)
{
    sk_log_start(v, "  %s: %s: %d: %s");      /* s___s____s__d____s___005a8c67 */
    sk_log_append(0xeb1a02bf914012baULL, 0, 0);
    sk_log_end(10, 0xeb1a02bf914012baULL);
}

/* FUN_004b8148 @ 0x004b8148  (est. sk_assert_fail_report)
 * Ghidra: void FUN_004b8148(void)
 * Assertion-failure reporter using the list context hooks. Does not return.
 * Confidence: medium */
static void sk_assert_fail_report24(void)
{
    sk_list_ctx_save();      /* FUN_0006d870 */
    sk_panic_report_context10(0);
    sk_list_ctx_restore();   /* FUN_0006d890 */
    sk_assert_panic("Unexpected L4 Error: %s: %zu, err");  /* s_Unexpected_L4_Error___s__zu__err_005bf57c */
}

/* FUN_004b8198 @ 0x004b8198  (est. sk_assert_fail_report)
 * Ghidra: void FUN_004b8198(void)
 * Assertion-failure reporter using the list context hooks. Does not return.
 * Confidence: medium */
static void sk_assert_fail_report25(void)
{
    sk_list_ctx_save();
    sk_panic_report_context10(0);
    sk_list_ctx_restore();
    sk_assert_panic("Unexpected L4 Error: %s: %zu, err");  /* s_Unexpected_L4_Error___s__zu__err_005bf653 */
}

/* FUN_004b81e8 @ 0x004b81e8  (est. sk_assert_fail_report)
 * Ghidra: void FUN_004b81e8(void)
 * Assertion-failure reporter using the list context hooks. Does not return.
 * Confidence: medium */
static void sk_assert_fail_report26(void)
{
    sk_list_ctx_save();
    sk_panic_report_context10(0);
    sk_list_ctx_restore();
    sk_assert_panic("Unexpected L4 Error: %s: %zu, err");  /* s_Unexpected_L4_Error___s__zu__err_005bf6d3 */
}
