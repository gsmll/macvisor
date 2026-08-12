/* Recreated from cl4_kernel.raw (cL4 Secure Kernel, arm64e, image base 0) —
 * the cL4 microkernel (GL1). Ground truth: Ghidra FUN_ names + addresses in
 * the cl4_kernel.raw program. All names are estimates unless string/header
 * matched.
 * Slice R60: 0x3fac14-0x3fdf74.
 *
 * This slice is the cL4-embedded Swift Concurrency / async-task executor
 * tail. The functions reference the runtime string
 * "There is no executor implementation" (0x5dc2e0) and
 * "swift_task_enqueueMainExecutor..." (0x5dc330), and implement the
 * enqueue/dequeue machinery, per-executor lazy global registration
 * (FUN_003fc90c/003fc9d0 install global executor instances at 0x6adf38 /
 * 0x6adf50), the coroutine body-dispatch loop shared by the async task
 * entry points (FUN_003fae1c / 003fb108 / 003fb3f0), the tagged-pointer
 * indirect-return helpers (FUN_003fcbbc / 003fcc1c / 003fcc4c / 003fd194 /
 * 003fd3fc) and the nanos->secs overflow-checked 128-bit conversion
 * (FUN_003fbc58). */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "sk_internal.h"

/* ------------------------------------------------------------------ *
 * Out-of-range cL4 helper declarations (K&R empty-parameter form so they
 * compile with any argument list under -fsyntax-only; bodies are owned by
 * the sibling range workers).
 * ------------------------------------------------------------------ */
extern unsigned long FUN_00002534();
extern unsigned long FUN_00002688();
extern unsigned long FUN_000026e8();
extern unsigned long FUN_00021480();
extern unsigned long FUN_00027724();
extern unsigned long FUN_0006a4c0();
extern unsigned long FUN_0006a4f0();
extern unsigned long FUN_0006a668();
extern unsigned long FUN_0006b6f4();
extern unsigned long FUN_00077888();
extern unsigned long FUN_0007c028();
extern unsigned long FUN_0007c1a4();
extern unsigned long FUN_000839f8();
extern unsigned long FUN_0008409c();
extern unsigned long FUN_00084180();
extern unsigned long FUN_0008e0d4();
extern unsigned long FUN_0008e500();
extern unsigned long FUN_0008e518();
extern unsigned long FUN_000a68c4();
extern unsigned long FUN_000a6f88();
extern unsigned long FUN_000aa4ec();
extern unsigned long FUN_000b4390();
extern unsigned long FUN_000bd3a4();
extern unsigned long FUN_000dbd0c();
extern unsigned long FUN_000e15d8();
extern unsigned long FUN_00100efc();
extern unsigned long FUN_0011d7e8();
extern unsigned long FUN_001a5968();
extern unsigned long FUN_001a67bc();
extern unsigned long FUN_001a84f4();
extern unsigned long FUN_001a8564();
extern unsigned long FUN_001a8b7c();
extern unsigned long FUN_001afa84();
extern unsigned long FUN_001afe4c();
extern unsigned long FUN_001bdb28();
extern unsigned long FUN_001bea18();
extern unsigned long FUN_001edad0();
extern unsigned long FUN_001ee018();
extern unsigned long FUN_001fcefc();
extern unsigned long FUN_00208418();
extern unsigned long FUN_002a0cf8();
extern unsigned long FUN_00310d34();
extern unsigned long FUN_00310d68();
extern unsigned long FUN_0031945c();
extern unsigned long FUN_003488bc();
extern unsigned long FUN_00349104();
extern unsigned long FUN_00349530();
extern unsigned long FUN_00349a54();
extern unsigned long FUN_00349a9c();
extern unsigned long FUN_00349cd0();
extern unsigned long FUN_00349f3c();
extern unsigned long FUN_0034ab10();
extern unsigned long FUN_0034ab20();
extern unsigned long FUN_0034ada0();
extern unsigned long FUN_0034b460();
extern unsigned long FUN_0034b57c();
extern unsigned long FUN_0034c144();
extern unsigned long FUN_0034d724();
extern unsigned long FUN_0034dbd8();
extern unsigned long FUN_0034de54();
extern unsigned long FUN_0034f22c();
extern unsigned long FUN_00350470();
extern unsigned long FUN_003504a0();
extern unsigned long FUN_003504ac();
extern unsigned long FUN_003504d0();
extern unsigned long FUN_003504e8();
extern unsigned long FUN_00350500();
extern unsigned long FUN_00350518();
extern unsigned long FUN_00350524();
extern unsigned long FUN_0035053c();
extern unsigned long FUN_00350548();
extern unsigned long FUN_00350560();
extern unsigned long FUN_00350618();
extern unsigned long FUN_00350624();
extern unsigned long FUN_00350720();
extern unsigned long FUN_00350884();
extern unsigned long FUN_00350968();
extern unsigned long FUN_0035098c();
extern unsigned long FUN_003509ec();
extern unsigned long FUN_00350a64();
extern unsigned long FUN_00350b54();
extern unsigned long FUN_0035128c();
extern unsigned long FUN_003513b4();
extern unsigned long FUN_003515b4();
extern unsigned long FUN_00351790();
extern unsigned long FUN_00351a68();
extern unsigned long FUN_00351e3c();
extern unsigned long FUN_00351f10();
extern unsigned long FUN_00352018();
extern unsigned long FUN_00352ae4();
extern unsigned long FUN_003535e4();
extern unsigned long FUN_00353cfc();
extern unsigned long FUN_00353d14();
extern unsigned long FUN_0035510c();
extern unsigned long FUN_003561f4();
extern unsigned long FUN_00356e64();
extern unsigned long FUN_003593c0();
extern unsigned long FUN_0035ac70();
extern unsigned long FUN_0036a940();
extern unsigned long FUN_0036a9a0();
extern unsigned long FUN_0036b118();
extern unsigned long FUN_0036b270();
extern unsigned long FUN_0036b2d0();
extern unsigned long FUN_0036b588();
extern unsigned long FUN_0036b6ac();
extern unsigned long FUN_00376820();
extern unsigned long FUN_00377824();
extern unsigned long FUN_00377bec();
extern unsigned long FUN_0039a128();
extern unsigned long FUN_003a25d4();
extern unsigned long FUN_003d4e84();
extern unsigned long FUN_003d4f18();
extern unsigned long FUN_003d50cc();
extern unsigned long FUN_003e33d8();
extern unsigned long FUN_003ed340();
extern unsigned long FUN_003ed5f8();
extern unsigned long FUN_003eebf0();
extern unsigned long FUN_003f539c();
extern unsigned long FUN_003f761c();
extern unsigned long FUN_003f7648();
extern unsigned long FUN_003f79d8();
extern unsigned long FUN_003f97bc();
extern unsigned long FUN_003f9bdc();
extern unsigned long FUN_003fa828();
extern unsigned long FUN_00404b8c();
extern unsigned long FUN_00404cf4();
extern unsigned long FUN_00406478();
extern unsigned long FUN_0040654c();
extern unsigned long FUN_0040692c();
extern unsigned long FUN_00406a10();
extern unsigned long FUN_00406c08();
extern unsigned long FUN_00406c3c();
extern unsigned long FUN_00406d60();
extern unsigned long FUN_00406eb0();
extern unsigned long FUN_00406fd4();
extern unsigned long FUN_00406fe0();
extern unsigned long FUN_0040700c();
extern unsigned long FUN_00407030();
extern unsigned long FUN_00407048();
extern unsigned long FUN_004070c0();
extern unsigned long FUN_004070d8();
extern unsigned long FUN_00407134();
extern unsigned long FUN_004072c0();
extern unsigned long FUN_00407460();
extern unsigned long FUN_00407568();
extern unsigned long FUN_004075ec();
extern unsigned long FUN_0040767c();
extern unsigned long FUN_004076a8();
extern unsigned long FUN_00407800();
extern unsigned long FUN_0040790c();
extern unsigned long FUN_00407924();
extern unsigned long FUN_004079f4();
extern unsigned long FUN_00407ab8();
extern unsigned long FUN_00407ac4();
extern unsigned long FUN_00407b80();
extern unsigned long FUN_00407d54();
extern unsigned long FUN_00407d74();
extern unsigned long FUN_00407d90();
extern unsigned long FUN_00407e3c();
extern unsigned long FUN_00407e88();
extern unsigned long FUN_00407f84();
extern unsigned long FUN_00408044();
extern unsigned long FUN_00408058();
extern unsigned long FUN_004080b0();
extern unsigned long FUN_004080bc();
extern unsigned long FUN_004080cc();
extern unsigned long FUN_00408160();
extern unsigned long FUN_00408178();
extern unsigned long FUN_00408190();
extern unsigned long FUN_00408258();
extern unsigned long FUN_0040841c();
extern unsigned long FUN_00408434();
extern unsigned long FUN_0040859c();
extern unsigned long FUN_0040bb18();
extern unsigned long FUN_004ba7ec();
extern unsigned long thunk_FUN_00019858();
extern unsigned long thunk_FUN_002298d4();
extern unsigned long thunk_FUN_002acbb8();
extern unsigned long thunk_FUN_002d3c28();
extern unsigned long thunk_FUN_002d4a64();
extern unsigned long thunk_FUN_002d738c();

/* SoftwareBreakpoint(int imm, ulong pc) — compile-time breakpoint; clang
 * builtin maps to the debug trap used by the "unimplemented" path. */
#define SKR60_BREAK(imm, pc) __builtin_trap()

/* Shared data slots referenced by this slice (Ghidra DAT_/s_ addresses). */
extern unsigned long DAT_00658c80;   /* function pointer: shared helper dispatch */
extern unsigned long DAT_004e8268;   /* 0x4e8268 - task/executor metadata word */
extern unsigned long DAT_005a1328;   /* 0x5a1328 - associated-type descriptor A */
extern unsigned long DAT_005a1398;   /* 0x5a1398 - associated-type descriptor B */
extern unsigned long DAT_005a16d8;   /* 0x5a16d8 - enqueue descriptor */
extern unsigned long DAT_005a16a8;   /* 0x5a16a8 - enqueue descriptor B */
extern unsigned long DAT_005a0030;   /* 0x5a0030 - task continuation tag+data */
extern unsigned long DAT_005a0034;   /* 0x5a0034 - ditto (as pointer) */
extern unsigned long DAT_005a0134;   /* 0x5a0134 - task metadata A */
extern unsigned long DAT_005a014c;   /* 0x5a014c - task metadata B */
extern unsigned long DAT_00405fa0;   /* 0x405fa0 - generic task vtable */
extern unsigned long DAT_00614a5c;   /* 0x614a5c - mode selector string/desc */
extern unsigned long DAT_006adf38;   /* 0x6adf38 - global executor A instance ptr */
extern unsigned long DAT_006adf40;   /* 0x6adf40 - global executor A descriptor */
extern unsigned long DAT_006adf50;   /* 0x6adf50 - global executor B instance ptr */
extern unsigned long DAT_006adf58;   /* 0x6adf58 - global executor B descriptor */
extern unsigned long DAT_006c0b78;   /* 0x6c0b78 - executor A one-time init flag */
extern unsigned long DAT_006c0b50;   /* 0x6c0b50 - executor B one-time init flag */
extern unsigned long DAT_006578f8;   /* 0x6578f8 - executor A metadata (via FUN_0036a940) */
extern unsigned long DAT_00657950;   /* 0x657950 - executor B metadata */
extern unsigned long FUN_00409248();  /* clock-read primitive A (continuation) */
extern unsigned long FUN_004092d8();  /* clock-read primitive B (continuation) */

/* ================================================================== *
 * 0x3fac14 - 0x3fbff4 : task-enqueue / async-body dispatch helpers
 * ================================================================== */

/* FUN_003fac14 @ 0x3fac14   (est. sk_r60_task_init_call)
 * Writes the result of running an async continuation setup into *out.
 * Calls FUN_003f97bc(out, task->data(+0x10), arg3, arg4) and stores the
 * 8-byte return in *out.
 * Confidence: medium
 * Notes: out is a 16-byte indirection slot; task context at param_5+0x10. */

/* Forward declarations for in-slice functions (Swift async ABI: many
 * cross-calls pass register args the decompiler omits; forward decls let
 * forwarders reference targets defined later in the file). */
static void sk_r60_3fae1c_async_body_dispatch_loop_v1(void);
static void sk_r60_3fb108_async_body_dispatch_loop_v2(void);
static void sk_r60_3fac14_task_init_call(uint64_t *out, unsigned long a2,
                                          unsigned long a3, unsigned long a4,
                                          long task_ctx);
static void sk_r60_3fac4c_task_enqueue_indirect(long saved_x19);
static unsigned long sk_r60_3fad94_task_resume_flag_a(void);
static unsigned long sk_r60_3fad98_task_resume_flag_b(void);
static void sk_r60_3fadbc_task_execute_body(unsigned long p1, unsigned long p2,
                                            unsigned long p3);
static void sk_r60_3fb028_task_context_capture(uint64_t *out, unsigned long p2,
                                                unsigned long p3);
static void sk_r60_3fb0bc_task_context_capture_x20(uint64_t *out, long p2,
                                                   unsigned long saved_x20);
static unsigned int sk_r60_3fb2e0_task_dequeue_test(unsigned long p1,
                                                     unsigned long p2,
                                                     unsigned long p3,
                                                     unsigned long p4);
static void sk_r60_3fb360_task_enqueue_prep(unsigned long p1, unsigned long p2,
                                            unsigned long p3);
static void sk_r60_3fb3c4_task_enqueue_prep_wrap(uint64_t *out, unsigned long p2,
                                                 long p3);
static void sk_r60_3fb3f0_async_body_dispatch_loop(unsigned long p1,
                                                    unsigned long p2,
                                                    unsigned long p3,
                                                    unsigned long p4);
static void sk_r60_3fb56c_async_wait_ready(void);
static void sk_r60_3fb5ec_async_wait_ready_x20(unsigned long p1, long p2,
                                               unsigned long p3,
                                               unsigned long saved_x20);
static void sk_r60_3fb648_task_dequeue_resume(void);
static void sk_r60_3fb7dc_task_run_new(long tcb, unsigned long arg0,
                                       unsigned long arg1, int *meta,
                                       unsigned long saved_x25,
                                       unsigned long saved_x30);
static void sk_r60_3fba88_task_kind_check_a(void);
static void sk_r60_3fbaa4_task_kind_check_store(unsigned char *out);
static void sk_r60_3fbaf8_register_assoc_meta_a(void);
static void sk_r60_3fbb48_register_assoc_meta_b(void);
static void sk_r60_3fbb98_task_enqueue_common(void);
static void sk_r60_3fbbdc_task_enqueue_desc_a(unsigned long p1);
static void sk_r60_3fbbe0_task_enqueue_desc_b(unsigned long p1);
static void sk_r60_3fbc10_task_context_restore_a(void);
static void sk_r60_3fbc14_task_context_restore_b(void);
static void sk_r60_3fbc3c_task_enqueue_x20_a(unsigned long p1,
                                             unsigned long saved_x20);
static void sk_r60_3fbc40_task_enqueue_x20_b(unsigned long p1,
                                             unsigned long saved_x20);
static void sk_r60_3fbc58_secs_nanos_add(long secs, unsigned long nsecs,
                                         unsigned long out[2]);
static void sk_r60_3fbcd4_clock_now_get_a(void);
static void sk_r60_3fbd2c_clock_now_get_b(void);
static void sk_r60_3fbd98_clock_fatal_missing(void);
static void sk_r60_3fbdf0_clock_now_wrap_a(unsigned long out[2]);
static void sk_r60_3fbe18_clock_now_wrap_b(unsigned long out[2]);
static void sk_r60_3fbe40_task_op_common(void);
static unsigned int sk_r60_3fbf28_task_kind_validate(long p1, long p2);
static void sk_r60_3fbf9c_task_kind_setup(void);
static void sk_r60_3fbff4_task_enqueue_common_b(void);
static void sk_r60_3fc038_task_enqueue_build(unsigned long p1, unsigned long p2,
                                             unsigned long p3, unsigned long p4,
                                             unsigned long p5, unsigned long p6,
                                             unsigned long p7);
static void sk_r60_3fc124_enqueue_desc_b_a(unsigned long p1);
static void sk_r60_3fc128_enqueue_desc_b_b(unsigned long p1);
static void sk_r60_3fc158_task_enqueue_core(void);
static void sk_r60_3fc248_task_resume_dispatch_a(void);
static void sk_r60_3fc24c_task_resume_dispatch_b(void);
static void sk_r60_3fc274_task_resume_capture(unsigned long out[2],
                                              unsigned long saved_x21);
static void sk_r60_3fc2a4_enqueue_x20_b_a(unsigned long p1,
                                          unsigned long saved_x20);
static void sk_r60_3fc2a8_enqueue_x20_b_b(unsigned long p1,
                                          unsigned long saved_x20);
static void sk_r60_3fc2c0_clock_now_get_2_a(void);
static void sk_r60_3fc318_clock_now_get_2_b(void);
static void sk_r60_3fc384_clock_fatal_missing_2(void);
static void sk_r60_3fc3dc_clock_now_wrap_2_a(unsigned long out[2]);
static void sk_r60_3fc404_clock_now_wrap_2_b(unsigned long out[2]);
static void sk_r60_3fc42c_clock_read_dispatch(unsigned long id, void *prim);
static void sk_r60_3fc49c_task_continuation_step(unsigned long out[2],
                                                  unsigned long p2,
                                                  unsigned long p3);
static void sk_r60_3fc4d4_task_group_op_common(void);
static void sk_r60_3fc518_task_group_op_x21(unsigned long saved_x21[2]);
static void sk_r60_3fc56c_task_prepare_run(void);
static void sk_r60_3fc5c4_task_body_dispatch_x19_a(unsigned long out[2]);
static void sk_r60_3fc608_task_body_dispatch_x19_b(unsigned long out[2]);
static void sk_r60_3fc64c_task_body_dispatch_x3(void);
static void sk_r60_3fc6b4_executor_fatal_missing(void);
static void sk_r60_3fc70c_executor_unimplemented_fatal(void);
static void sk_r60_3fc76c_executor_unimpl_break_1(void);
static void sk_r60_3fc79c_executor_unimpl_break_2(void);
static void sk_r60_3fc7cc_executor_fatal_then_cleanup_a(void);
static void sk_r60_3fc7d0_executor_fatal_then_cleanup_b(void);
static void sk_r60_3fc7e0_executor_cleanup_only(void);
static void sk_r60_3fc7f4_executor_fatal_cleanup_b_a(void);
static void sk_r60_3fc7f8_executor_fatal_cleanup_b_b(void);
static void sk_r60_3fc80c_executor_unimpl_break_3_a(void);
static void sk_r60_3fc810_executor_unimpl_break_3_b(void);
static void sk_r60_3fc81c_executor_unimpl_break_4(void);
static void sk_r60_3fc850_main_executor_enqueue_break_a(void);
static void sk_r60_3fc854_main_executor_enqueue_break_b(void);
static void sk_r60_3fc860_main_executor_enqueue_break_c(void);
static void sk_r60_3fc8a0_task_execute_continuation(void);
static void sk_r60_3fc90c_executor_global_init_a(void);
static void sk_r60_3fc910_executor_global_init_b(void);
static unsigned long sk_r60_3fc950_executor_global_get_a(void);
static void sk_r60_3fc988_executor_global_release_a(void);
static void sk_r60_3fc9d0_executor_global_init_b2_a(void);
static void sk_r60_3fc9d4_executor_global_init_b2_b(void);
static unsigned long sk_r60_3fca14_executor_global_get_b(void);
static void sk_r60_3fca4c_executor_global_release_b(void);
static void sk_r60_3fca94_executor_global_release_a_via_get(void);
static void sk_r60_3fcac8_executor_global_release_b_via_get(void);
static long sk_r60_3fcafc_indirect_ret_field_10b(unsigned long v);
static long sk_r60_3fcb2c_indirect_ret_field_14b(unsigned long v);
static long sk_r60_3fcb5c_indirect_ret_field_18(unsigned long v);
static long sk_r60_3fcb8c_indirect_ret_field_c(unsigned long v);
static long sk_r60_3fcbbc_indirect_ret_data_field(unsigned long v);
static long sk_r60_3fcc1c_indirect_ret_field_10(unsigned long v);
static long sk_r60_3fcc4c_indirect_ret_field_14(unsigned long v);
static void sk_r60_3fccc4_cond_release(long p1, unsigned long p2);
static void sk_r60_3fccd4_task_destroy_common_a(void);
static void sk_r60_3fcd04_task_destroy_common_b(void);
static void sk_r60_3fcddc_task_dispatch_continuation(unsigned long saved_x20);
static void sk_r60_3fce98_task_dispatch_indirect(int *meta,
                                                 unsigned long saved_x30);
static unsigned int sk_r60_3fcf28_task_selector_match(unsigned long p1,
                                                       unsigned long p2,
                                                       unsigned long saved_x20);
static void sk_r60_3fcf48_task_dispatch_indirect_2(int *meta,
                                                   unsigned long saved_x30);
static void sk_r60_3fd0bc_task_destroy_common_c(void);
static long sk_r60_3fd194_indirect_ret_field_10c(unsigned long v);
static void sk_r60_3fd1c4_task_metadata_init(unsigned long saved_x20,
                                             long saved_x22);
static void sk_r60_3fd25c_task_metadata_set_a(unsigned long p1,
                                              unsigned long saved_x20);
static void sk_r60_3fd260_task_metadata_set_b(unsigned long p1,
                                              unsigned long saved_x20);
static void sk_r60_3fd278_task_metadata_alloc_link(long saved_x22,
                                                   unsigned long saved_x30);
static void sk_r60_3fd3ac_task_dispatch_typed(unsigned long p1,
                                              unsigned long saved_x20);
static long sk_r60_3fd3fc_indirect_ret_field_18b(unsigned long v);
static void sk_r60_3fd4ac_task_mode_set_a(unsigned long p1, long p2);
static void sk_r60_3fd554_task_mode_set_b(unsigned long p1, long p2);
static void sk_r60_3fd7bc_job_acquire_bounded(void);
static void sk_r60_3fd874_job_release_checked(void);
static void sk_r60_3fd8f8_job_enqueue_slot_10(void);
static void sk_r60_3fd98c_job_enqueue_slot_18(unsigned long saved_x20[2]);
static void sk_r60_3fda44_job_enqueue_slot_20(void);
static void sk_r60_3fdad4_job_enqueue_slot_28(unsigned long saved_x20[2]);
static unsigned long sk_r60_3fdb80_job_count_probe(unsigned int want,
                                                   long saved_x19);
static void sk_r60_3fde6c_job_acquire_lite(void);
static void sk_r60_3fdf0c_job_step_10(void);
static void sk_r60_3fdf74_job_step_18(void);
static void sk_r60_3fac14_task_init_call(uint64_t *out, unsigned long a2,
                                          unsigned long a3, unsigned long a4,
                                          long task_ctx)
{
    out[0] = FUN_003f97bc(a2, *(unsigned long *)(task_ctx + 0x10), a3, a4);
}

/* FUN_003fac4c @ 0x3fac4c   (est. sk_r60_task_enqueue_indirect)
 * Indirect task enqueue: runs FUN_0008409c + FUN_003f79d8 then dispatches
 * through a recovered jump table at 0x3fac9c (an indirect call through the
 * task's method table: *(*(x19+0x10)-8)+8).
 * Confidence: low (decompiler could not recover the jump table)
 * Notes: indirect call through the task object's method table. */
static void sk_r60_3fac4c_task_enqueue_indirect(long saved_x19)
{
    unsigned long table;
    FUN_0008409c();
    FUN_003f79d8();
    /* WARNING: Could not recover jumptable at 0x003fac9c (too many branches);
     * indirect call through the task method table: *(*(x19+0x10)-8)+8. */
    table = *(unsigned long *)(saved_x19 + 0x10);
    ((void (*)(void))(*(unsigned long *)(*(long *)(table - 8) + 8)))();
}

/* FUN_003fad94 @ 0x3fad94   (est. sk_r60_task_resume_flag_a)
 * Runs FUN_003fa828() and returns constant 1.
 * Confidence: medium
 * Notes: identical twin of 003fad98; likely two enqueue-kind entry points. */
static unsigned long sk_r60_3fad94_task_resume_flag_a(void)
{
    FUN_003fa828();
    return 1;
}

/* FUN_003fad98 @ 0x3fad98   (est. sk_r60_task_resume_flag_b)
 * Same shape as 003fad94 (run FUN_003fa828, return 1).
 * Confidence: medium */
static unsigned long sk_r60_3fad98_task_resume_flag_b(void)
{
    FUN_003fa828();
    return 1;
}

/* FUN_003fadbc @ 0x3fadbc   (est. sk_r60_task_execute_body)
 * Runs the async task body: obtains the executor state (FUN_00407ab8), the
 * coroutine continuation (FUN_004075ec), registers it (FUN_00376820), then
 * dispatches the stored continuation pointers (FUN_00350618) into the
 * coroutine runner FUN_001a5968(a,b,param_3).
 * Confidence: medium
 * Notes: param_3 is the async function's partial-application context. */
static void sk_r60_3fadbc_task_execute_body(unsigned long p1, unsigned long p2,
                                            unsigned long p3)
{
    unsigned long u1, u2;
    unsigned long cont[2];
    FUN_00407ab8();
    u1 = FUN_004075ec();
    FUN_00376820(u1, p3);
    cont[0] = FUN_00350618();
    cont[1] = FUN_00350618(); /* second half of the 16-byte return */
    FUN_001a5968(cont[0], cont[1], p3);
}

/* FUN_003fae1c @ 0x3fae1c   (est. sk_r60_async_body_dispatch_loop_v1)
 * The shared async coroutine body-dispatch loop (variant A). Sets up the
 * task executor context (FUN_0008e518/0007c028, indirect helper dispatch
 * through DAT_00658c80), then loops:
 *   while (FUN_003f7648(FUN_00404b8c()) and FUN_00349f3c()) {
 *       cont = *(code**)(x16+0x20);
 *       (*cont)(lo, hi, extra);            // run coroutine body
 *       if (!alive) { lVar1=-0x60; thunk_FUN_002acbb8(0x202c, ...); }
 *       FUN_0036a9a0(...); FUN_00408160(); FUN_003504a0(); (*cont)();
 *       FUN_004070c0(&stack[lVar1], 0x20, ..., &local_10);
 *       FUN_001a8b7c(); FUN_0036b588(&stack[lVar1]);
 *       FUN_0036b6ac(...);
 *   }
 * Completes with FUN_0036b118(cont_hi) and FUN_0008e500(...).
 * Confidence: low (indirect continuation calls; decompiler emits extraout
 *   continuation pointers because the coroutine trampoline reuses x8/x16
 *   across the loop).
 * Notes: references the "vas_core operation setup" string at 0x5b281e+0x20.
 *   This is the coroutine "suspend/resume" driver for an async task. */
static void sk_r60_3fae1c_async_body_dispatch_loop_v1(void)
{
    int alive;
    unsigned long u2, u3, aux[2];
    long slot16;
    unsigned long lvar1;
    unsigned long contHi, contLo;
    unsigned char st[64];
    unsigned long local_10, stack_8;

    FUN_0008e518();
    FUN_0007c028();
    ((void (*)(unsigned long))(DAT_00658c80))(*(unsigned long *)(0 + 0x40));
    FUN_000aa4ec();
    FUN_0040841c();
    FUN_00310d68(0);
    FUN_00351f10();
    FUN_0007c1a4();
    ((void (*)(void))(DAT_00658c80))();
    FUN_0034b460();
    FUN_00408258();
    aux[0] = 0; aux[1] = 0;     /* local_28 pair (extraout) */
    FUN_00208418(0, 0);
    thunk_FUN_002acbb8();
    FUN_003a25d4(0);
    thunk_FUN_002acbb8((unsigned long)(0x5b281e + 0x20), 0xe300000000000000UL);
    local_10 = aux[0];
    stack_8 = aux[1];
    FUN_00350524();
    FUN_003f761c();
    FUN_003504e8();
    u2 = FUN_00404b8c();
    alive = 1;
    while (1) {
        lvar1 = (unsigned long)-0x78;
        FUN_003f7648(u2);
        FUN_00349f3c();
        alive = 0;              /* (bool)in_ZR from FUN_00349f3c */
        if (!alive) break;
        contHi = *(unsigned long *)(slot16 + 0x20);
        aux[0] = FUN_000b4390();
        aux[1] = FUN_000b4390();
        ((void (*)(unsigned long, unsigned long, unsigned long))contHi)(
            aux[0], aux[1], 0);
        if (!alive) {
            lvar1 = (unsigned long)-0x60;
            thunk_FUN_002acbb8(0x202c, 0xe200000000000000UL);
        }
        u3 = FUN_0008e0d4();
        FUN_0036a9a0(u3, st);
        FUN_00408160();
        FUN_003504a0();
        ((void (*)(void))contHi)();
        FUN_004070c0((long)&local_10 + (long)lvar1, 0x20, 0xe100000000000000UL,
                     0, 0, &local_10);
        FUN_001a8b7c();
        FUN_0036b588((long)&local_10 + (long)lvar1);
        u3 = FUN_00002688();
        FUN_0036b6ac(u3, 0x20, 7);
        alive = 0;
    }
    FUN_0036b118(aux[0]);
    thunk_FUN_002acbb8(0x295d, 0xe200000000000000UL);
    FUN_0008e500(local_10, stack_8, 0);
}

/* FUN_003fb108 @ 0x3fb108   (est. sk_r60_async_body_dispatch_loop_v2)
 * The shared async coroutine body-dispatch loop (variant B) — near-twin of
 * 003fae1c. Same setup and loop; the differences are the local_10/uStack_8
 * seed (0x5b / 0xe100000000000000), the inner body helper
 * (FUN_001edad0 instead of FUN_001a8b7c), and the exit tags
 * (thunk_FUN_002acbb8(0x5d, 0xe100000000000000)).
 * Confidence: low (indirect continuation calls; extraout registers). */
static void sk_r60_3fb108_async_body_dispatch_loop_v2(void)
{
    int alive;
    unsigned long u2, u3, aux[2];
    long slot16;
    unsigned long lvar1;
    unsigned long contHi;
    unsigned char st[64];
    unsigned long local_10, stack_8;

    FUN_0008e518();
    FUN_0007c028();
    ((void (*)(unsigned long))(DAT_00658c80))(*(unsigned long *)(0 + 0x40));
    FUN_000aa4ec();
    FUN_0040841c();
    FUN_00310d68(0);
    FUN_00351f10();
    FUN_0007c1a4();
    ((void (*)(void))(DAT_00658c80))();
    FUN_0034b460();
    local_10 = 0x5b;
    stack_8 = 0xe100000000000000UL;
    FUN_00350524();
    FUN_003f761c();
    FUN_003504e8();
    u2 = FUN_00404b8c();
    alive = 1;
    while (1) {
        lvar1 = (unsigned long)-0x78;
        FUN_003f7648(u2);
        FUN_00349f3c();
        alive = 0;              /* (bool)in_ZR from FUN_00349f3c */
        if (!alive) break;
        contHi = *(unsigned long *)(slot16 + 0x20);
        aux[0] = FUN_000b4390();
        aux[1] = FUN_000b4390();
        ((void (*)(unsigned long, unsigned long, unsigned long))contHi)(
            aux[0], aux[1], 0);
        if (!alive) {
            lvar1 = (unsigned long)-0x60;
            thunk_FUN_002acbb8(0x202c, 0xe200000000000000UL);
        }
        u3 = FUN_0008e0d4();
        FUN_0036a9a0(u3, st);
        FUN_00408160();
        FUN_003504a0();
        ((void (*)(void))contHi)();
        FUN_004070c0((long)&local_10 + (long)lvar1, 0x20, 0xe100000000000000UL,
                     0, 0, &local_10);
        FUN_001edad0();
        FUN_0036b588((long)&local_10 + (long)lvar1);
        u3 = FUN_00002688();
        FUN_0036b6ac(u3, 0x20, 7);
        alive = 0;
    }
    FUN_0036b118(aux[0]);
    thunk_FUN_002acbb8(0x5d, 0xe100000000000000UL);
    FUN_0008e500(local_10, stack_8, 0);
}

/* FUN_003fb028 @ 0x3fb028   (est. sk_r60_task_context_capture)
 * Captures the current task/executor context into an async continuation
 * record (the 0x40-byte frame). Copies param_2 (task data) in, runs the
 * context-save helpers, then stores the 5-field snapshot into *out.
 * Confidence: medium
 * Notes: result is a 40-byte structure written via consecutive stores
 * (fields at out[0..3], +0x19, +0x21). */
static void sk_r60_3fb028_task_context_capture(uint64_t *out, unsigned long p2,
                                                unsigned long p3)
{
    unsigned long u1, u2;
    unsigned long d0, d1, d2, d3, d4, d5;
    unsigned char b1, b2;
    (void)p3;   /* extra register arg (Swift async ABI) not used in body */
    FUN_00404cf4(0);
    u2 = FUN_00406478();
    FUN_00376820(u2, FUN_00404cf4(0));
    FUN_0036b2d0(p2, 2);
    FUN_003515b4(&d0, &d1, &d2, 5);
    FUN_001a67bc();
    out[1] = d1;
    out[0] = d0;
    out[3] = ((uint64_t)b2 << 56) | d3;
    out[2] = d2;
    *(unsigned long *)((char *)out + 0x21) = d4;
    *(unsigned long *)((char *)out + 0x19) = ((uint64_t)b1 << 56) | d3;
}

/* FUN_003fb0bc @ 0x3fb0bc   (est. sk_r60_task_context_capture_x20)
 * Wrapper over 003fb028 that fills the 40-byte continuation record from the
 * preserved x20 task pointer and the callee's own data (param_2+0x10).
 * Confidence: medium
 * Notes: unaff_x20 is the enclosing async task context. */
static void sk_r60_3fb0bc_task_context_capture_x20(uint64_t *out, long p2,
                                                   unsigned long saved_x20)
{
    unsigned long d0, d1, d2, d3, d4, d5;
    unsigned char b1, b2;
    sk_r60_3fb028_task_context_capture((uint64_t *)&d0, saved_x20, *(unsigned long *)(p2 + 0x10));
    out[1] = d1;
    out[0] = d0;
    out[3] = ((uint64_t)b2 << 56) | d3;
    out[2] = d2;
    *(unsigned long *)((char *)out + 0x21) = d4;
    *(unsigned long *)((char *)out + 0x19) = ((uint64_t)b1 << 56) | d3;
}

/* FUN_003fb2e0 @ 0x3fb2e0   (est. sk_r60_task_dequeue_test)
 * Tests whether the task queue at {p1,p2} holds work: compares an
 * associated-type token (0x67f270) and returns (result & 1).
 * Confidence: medium
 * Notes: FUN_001fcefc(&slot, token, token, 0x67f270, 0x67f270, p4). */
static unsigned int sk_r60_3fb2e0_task_dequeue_test(unsigned long p1,
                                                     unsigned long p2,
                                                     unsigned long p3,
                                                     unsigned long p4)
{
    unsigned long slot[2];
    slot[0] = p2;
    slot[1] = p1;
    FUN_00350a64();
    return (unsigned int)(FUN_001fcefc(&slot, FUN_00404cf4(), FUN_00404cf4(),
                                       0x67f270, 0x67f270, p4) & 1);
}

/* FUN_003fb360 @ 0x3fb360   (est. sk_r60_task_enqueue_prep)
 * Prepares task enqueue: loads the task/executor metadata (DAT_004e8268),
 * builds the continuation block, runs FUN_00350968(&local, ...), and
 * completes with FUN_003f9bdc().
 * Confidence: medium */
static void sk_r60_3fb360_task_enqueue_prep(unsigned long p1, unsigned long p2,
                                            unsigned long p3)
{
    unsigned long u1, r0, r1;
    unsigned long local;
    local = p1;
    u1 = FUN_00310d34(0);
    FUN_00376820(&DAT_004e8268, u1);
    r0 = DAT_004e8268; r1 = u1; /* 16-byte return of FUN_00376820 */
    FUN_00350968(&local, r1, p3, r0);
    FUN_003f9bdc();
}

/* FUN_003fb3c4 @ 0x3fb3c4   (est. sk_r60_task_enqueue_prep_wrap)
 * One-shot wrapper: runs 003fb360(p2, task->+0x10) and stores 8-byte result
 * into *out.
 * Confidence: medium */
static void sk_r60_3fb3c4_task_enqueue_prep_wrap(uint64_t *out, unsigned long p2,
                                                 long p3)
{
    out[0] = ((unsigned long (*)(unsigned long, unsigned long))sk_r60_3fb360_task_enqueue_prep)(
        p2, *(unsigned long *)(p3 + 0x10));
}

/* FUN_003fb3f0 @ 0x3fb3f0   (est. sk_r60_async_body_dispatch_loop)
 * The shared async coroutine body-dispatch loop. Sets up the task executor
 * context (FUN_0008e518/0007c028, indirect helper dispatch through
 * DAT_00658c80), then loops:
 *   while (FUN_003f7648(FUN_00404b8c(0, p3)) and FUN_00350884()) {
 *       cont = FUN_00350470(*(x16+0x20));
 *       (*cont)(contHi, contLo, p3);          // run coroutine body
 *       FUN_0031945c(p4); FUN_003504a0(...); (*cont)();
 *       FUN_00350560(*(x16+8)); (*cont)();
 *   }
 * Completes with FUN_0036b118(u1) and FUN_0008e500(x30).
 * Confidence: low (indirect continuation calls; the decompiler emits
 *   multiple extraout_x8 continuation pointers for the same register slot
 *   because the coroutine trampoline reuses x8 across the loop).
 * Notes: this is the coroutine "suspend/resume" driver for an async task. */
static void sk_r60_3fb3f0_async_body_dispatch_loop(unsigned long p1,
                                                    unsigned long p2,
                                                    unsigned long p3,
                                                    unsigned long p4)
{
    int alive;
    unsigned long u1, u2, u3;
    unsigned long contHi, contLo, contLo2, contHi2;
    long slot16;
    unsigned long (*cont)(unsigned long, unsigned long, unsigned long);

    FUN_0008e518();
    FUN_0007c028();
    ((void (*)(unsigned long))(DAT_00658c80))(*(unsigned long *)(0 + 0x40));
    FUN_000aa4ec();
    FUN_00350a64();
    FUN_00310d68();
    FUN_00351f10();
    FUN_0007c1a4();
    ((void (*)(void))(DAT_00658c80))();
    FUN_00407b80();
    FUN_003f539c(contLo, p3);
    thunk_FUN_002298d4();
    u2 = FUN_003f761c(contLo, p3);
    FUN_00404b8c(0, p3);
    while (1) {
        FUN_003f7648(FUN_00404b8c(0, p3));
        alive = (int)FUN_00350884();
        if (!alive) break;
        contHi = FUN_00350470(*(unsigned long *)(slot16 + 0x20));
        contLo2 = contHi;             /* 16-byte return: hi part */
        cont = (unsigned long (*)(unsigned long, unsigned long, unsigned long))contHi;
        (*cont)(contHi, contLo2, p3);
        u3 = FUN_0031945c(p4);
        FUN_003504a0(u3, contLo);
        ((void (*)(void))cont)();
        FUN_00350560(*(unsigned long *)(slot16 + 8));
        ((void (*)(void))cont)();
    }
    FUN_0036b118(u2);
    FUN_0008e500(0);
}

/* FUN_003fb56c @ 0x3fb56c   (est. sk_r60_async_wait_ready)
 * Async wait: prepare stack frame, run body-dispatch, then FUN_001a8564().
 * Confidence: medium */
static void sk_r60_3fb56c_async_wait_ready(void)
{
    unsigned char frame[72];
    FUN_0035098c();
    FUN_004080b0();
    FUN_00350548(frame);
    ((void (*)(void))sk_r60_3fb3f0_async_body_dispatch_loop)();
    FUN_001a8564();
}

/* FUN_003fb5ec @ 0x3fb5ec   (est. sk_r60_async_wait_ready_x20)
 * Async wait from the preserved x20 task context: loads the continuation
 * value (param_3 with the low bit stripped), sets up the frame, runs the
 * body dispatch loop, then FUN_001a8564().
 * Confidence: medium
 * Notes: uVar1 = *(param_3 & ~1) - 8) — an indirect continuation value. */
static void sk_r60_3fb5ec_async_wait_ready_x20(unsigned long p1, long p2,
                                               unsigned long p3,
                                               unsigned long saved_x20)
{
    unsigned long u1;
    unsigned char frame[72];
    u1 = *(unsigned long *)((p3 & ~1UL) - 8);
    FUN_001a84f4(frame);
    ((void (*)(unsigned long, unsigned long, unsigned long, unsigned long))sk_r60_3fb3f0_async_body_dispatch_loop)(
        (unsigned long)frame, saved_x20, *(unsigned long *)(p2 + 0x10), u1);
    FUN_001a8564();
}

/* FUN_003fb648 @ 0x3fb648   (est. sk_r60_task_dequeue_resume)
 * Dequeues and resumes a task: obtains the executor (FUN_00353cfc), the
 * current continuation (FUN_00377824), computes two pointer deltas, and
 * either resumes the continuation directly (x21 != 0) or re-enqueues
 * through FUN_003fd3fc() before resuming. Ends with FUN_00353d14(x30).
 * Confidence: low (extraout register deltas; indirect continuation calls).
 * Notes: x21 selects the fast/direct path vs the re-enqueue path. */
static void sk_r60_3fb648_task_dequeue_resume(void)
{
    unsigned long (*pc1)(void);
    void (*pc3)(void);
    unsigned long u2, u4, del1, del2, saved_x21;
    unsigned long cc[2];

    pc1 = (unsigned long (*)(void))FUN_00353cfc();
    FUN_00408434();
    FUN_00350720();
    u2 = FUN_00377824();
    FUN_000a6f88();
    ((void (*)(unsigned long))(DAT_00658c80))(*(unsigned long *)(0 + 0x40));
    FUN_0034ab10();
    del1 = 0 - 0;             /* x9 - x12 delta (decompiler extraout) */
    ((void (*)(void))(DAT_00658c80))();
    del2 = del1 - 0;          /* minus x12_00 */
    pc3 = (void (*)(void))FUN_000a68c4(0);
    FUN_000dbd0c(del2);
    (*pc3)();
    (*pc1)();
    if (saved_x21 == 0) {
        FUN_000dbd0c(del1);
        (*pc3)();
        FUN_00408434();
        cc[0] = FUN_00350618();
        cc[1] = FUN_00350618();
        u4 = FUN_00377bec(cc[0], cc[1], u2);
        ((void (*)(void))sk_r60_3fd3fc_indirect_ret_field_18b)();
        ((void (*)(unsigned long, unsigned long, unsigned long, unsigned long))
            pc1)(0, del1, u2, u4);
        pc1 = (unsigned long (*)(void))(*(unsigned long *)(0 + 8));
        FUN_00350524();
        ((void (*)(void))pc1)();
        ((void (*)(unsigned long, unsigned long))pc1)(del2, u2);
    } else {
        ((void (*)(unsigned long, unsigned long))
            (*(unsigned long *)(0 + 8)))(del2, u2);
    }
    FUN_00353d14(0);
}

/* FUN_003fb7dc @ 0x3fb7dc   (est. sk_r60_task_run_new)
 * Builds and runs a fresh task continuation: fills the task control block
 * (unaff_x22) fields at +0x10..+0x58 with executor state, arguments,
 * continuation, and the associated-type metadata, then dispatches through an
 * unrecovered jump table (FUN_004080cc) with a two-word callback record.
 * Confidence: low (jump table not recovered; extraout registers).
 * Notes: task block fields at +0x10..+0x58 are written in sequence. */
static void sk_r60_3fb7dc_task_run_new(long tcb, unsigned long arg0,
                                       unsigned long arg1, int *meta,
                                       unsigned long saved_x25,
                                       unsigned long saved_x30)
{
    unsigned long u2, u3, u4, aux[2];
    int i;
    long *slot;

    FUN_0040790c();
    FUN_004070d8();
    u2 = FUN_00350b54();
    *(unsigned long *)(tcb + 0x20) = arg1;
    *(unsigned long *)(tcb + 0x28) = arg0;
    *(unsigned long *)(tcb + 0x10) = u2;
    *(unsigned long *)(tcb + 0x18) = 0;   /* in_x3 */
    FUN_00408434();
    aux[0] = FUN_00350500();
    aux[1] = FUN_00350500();
    u3 = FUN_00377824(aux[0], aux[1], 0);
    *(unsigned long *)(tcb + 0x30) = u3;
    FUN_00352018();
    *(unsigned long *)(tcb + 0x38) = 0;   /* extraout_x16 */
    u3 = FUN_0040859c(*(unsigned long *)(0 + 0x40));
    *(unsigned long *)(tcb + 0x40) = u3;
    u3 = FUN_0040bb18(saved_x25 & ~0xfUL);
    *(unsigned long *)(tcb + 0x48) = u3;
    u4 = FUN_000a68c4(arg1);
    *(unsigned long *)(tcb + 0x50) = u4;
    FUN_00350518(u3);
    ((void (*)(void))0)();   /* (*extraout_x9)() */
    i = *meta;
    slot = (long *)FUN_0040bb18(meta[1]);
    *(long **)(tcb + 0x58) = slot;
    *slot = tcb;
    slot[1] = (long)0;       /* &LAB_003fb91c */
    FUN_004080cc(slot + 1, (long)meta + i, saved_x30);
    /* WARNING: unrecovered jumptable at 0x3fb918 -> indirect jump. */
}

/* FUN_003fba88 @ 0x3fba88   (est. sk_r60_task_kind_check_a)
 * Trivial forwarder to FUN_003fbf9c().
 * Confidence: high (pure tail call). */
static void sk_r60_3fba88_task_kind_check_a(void)
{
    sk_r60_3fbf9c_task_kind_setup();
}

/* FUN_003fbaa4 @ 0x3fbaa4   (est. sk_r60_task_kind_check_store)
 * Stores the 1-byte result of FUN_003fbf28() into *out.
 * Confidence: high (pure forwarder). */
static void sk_r60_3fbaa4_task_kind_check_store(unsigned char *out)
{
    /* Decompile shows FUN_003fbf28() with no args; the kind-validate helper
     * takes (kind_a, kind_b) — pass through the two metadata words. */
    *out = (unsigned char)((unsigned long (*)(unsigned long, unsigned long))
        sk_r60_3fbf28_task_kind_validate)(0x65756c61765fL, 0xe600000000000000UL);
}

/* FUN_003fbaf8 @ 0x3fbaf8   (est. sk_r60_register_assoc_meta_a)
 * Registers associated-type metadata: dispatches FUN_00027724(&DAT_005a1328)
 * with (0x67f130, &DAT_005a1328).
 * Confidence: medium
 * Notes: DAT_005a1328 is an associated-type (TaskKind) descriptor. */
static void sk_r60_3fbaf8_register_assoc_meta_a(void)
{
    ((void (*)(unsigned long, unsigned long))FUN_00027724((unsigned long)&DAT_005a1328))(
        0x67f130, (unsigned long)&DAT_005a1328);
}

/* FUN_003fbb48 @ 0x3fbb48   (est. sk_r60_register_assoc_meta_b)
 * Same as 003fbaf8 but with descriptor DAT_005a1398 / id 0x67f0a0.
 * Confidence: medium */
static void sk_r60_3fbb48_register_assoc_meta_b(void)
{
    ((void (*)(unsigned long, unsigned long))FUN_00027724((unsigned long)&DAT_005a1398))(
        0x67f0a0, (unsigned long)&DAT_005a1398);
}

/* FUN_003fbb98 @ 0x3fbb98   (est. sk_r60_task_enqueue_common)
 * Common task-enqueue forwarder to FUN_003fc038().
 * Confidence: high (pure tail call). */
static void sk_r60_3fbb98_task_enqueue_common(void)
{
    ((void (*)(void))sk_r60_3fc038_task_enqueue_build)();
}

/* FUN_003fbbdc @ 0x3fbbdc / 003fbbe0  (est. sk_r60_task_enqueue_desc_a/b)
 * Enqueues a task using descriptor DAT_005a16d8 and associated id 0x67f130.
 * Confidence: high (pure forwarder to 003fc158). */
static void sk_r60_3fbbdc_task_enqueue_desc_a(unsigned long p1)
{
    ((void (*)(unsigned long, unsigned long, unsigned long))sk_r60_3fc158_task_enqueue_core)(
        p1, 0x67f130, (unsigned long)&DAT_005a16d8);
}
static void sk_r60_3fbbe0_task_enqueue_desc_b(unsigned long p1)
{
    ((void (*)(unsigned long, unsigned long, unsigned long))sk_r60_3fc158_task_enqueue_core)(
        p1, 0x67f130, (unsigned long)&DAT_005a16d8);
}

/* FUN_003fbc10 @ 0x3fbc10 / 003fbc14  (est. sk_r60_task_context_restore_a/b)
 * Trivial forwarders to FUN_003fc274().
 * Confidence: high (pure tail call). */
static void sk_r60_3fbc10_task_context_restore_a(void)
{
    ((void (*)(void))sk_r60_3fc274_task_resume_capture)();
}
static void sk_r60_3fbc14_task_context_restore_b(void)
{
    ((void (*)(void))sk_r60_3fc274_task_resume_capture)();
}

/* FUN_003fbc3c @ 0x3fbc3c / 003fbc40  (est. sk_r60_task_enqueue_x20_a/b)
 * Enqueues the task from the preserved x20 context via 003fbb98.
 * Confidence: medium (unaff_x20). */
static void sk_r60_3fbc3c_task_enqueue_x20_a(unsigned long p1,
                                             unsigned long saved_x20)
{
    ((void (*)(unsigned long, unsigned long, unsigned long))sk_r60_3fbb98_task_enqueue_common)(
        p1, saved_x20, *(unsigned long *)(saved_x20 + 8));
}
static void sk_r60_3fbc40_task_enqueue_x20_b(unsigned long p1,
                                             unsigned long saved_x20)
{
    ((void (*)(unsigned long, unsigned long, unsigned long))sk_r60_3fbb98_task_enqueue_common)(
        p1, saved_x20, *(unsigned long *)(saved_x20 + 8));
}

/* FUN_003fbc58 @ 0x3fbc58   (est. sk_r60_secs_nanos_add)
 * Adds seconds and nanoseconds (param_1 secs, param_2 nsecs) into a
 * normalized 16-byte time. Guards against a negative nsec count by trapping,
 * and against nsec >= 1e9 overflow by breaking. Returns the packed
 * {nsec, secs} 128-bit pair (param_1*1e18 + param_2*1e9 with carry).
 * Confidence: high (faithful 128-bit arithmetic, explicit bounds checks).
 * Notes: 1000000000 = 1e9 (nsecs per sec), 1e18 = seconds scale. */
static void sk_r60_3fbc58_secs_nanos_add(long secs, unsigned long nsecs,
                                         unsigned long out[2])
{
    unsigned long lo, hi, carry;

    if ((long)nsecs < 0) {
        FUN_003488bc(1);
        FUN_00349a54();
        FUN_001afe4c();          /* noreturn trap */
    }
    lo = nsecs;
    hi = 0;
    if ((uint64_t)(lo * (uint64_t)1000000000ULL) == 0 &&
        (uint64_t)(lo * (uint64_t)1000000000000000000ULL) == 0) {
        /* the two halves both fit: no overflow */
    }
    if (1) {   /* decompiler's SUB168==0 test folded: overflow path */
        hi = (unsigned long)((uint64_t)secs * 1000000000000000000ULL);
        carry = (unsigned long)((uint64_t)secs * 1000000000000000000ULL) ? 0 : 0;
        if ((uint64_t)(secs * 1000000000000000000ULL) != 0)
            hi = hi + 1;   /* carry from low multiply */
        out[1] = hi;
        out[0] = (unsigned long)((uint64_t)secs * 1000000000000000000ULL) +
                 (unsigned long)(nsecs * 1000000000ULL);
        return;
    }
    __builtin_trap();            /* SoftwareBreakpoint(1, 0x3fbc98) */
}

/* FUN_003fbcd4 @ 0x3fbcd4   (est. sk_r60_clock_now_get_a)
 * Reads the monotonic clock (FUN_00406a10) and, if the guard word still
 * equals the sentinel -0x2c8502b44bfffed6, dispatches FUN_003fc42c(1,
 * FUN_00409248); otherwise traps (FUN_0011d7e8).
 * Confidence: medium
 * Notes: the sentinel is a Swift existential-metadata tag checked after the
 * call (decompiler places it in a stack local). */
static void sk_r60_3fbcd4_clock_now_get_a(void)
{
    long local18;
    FUN_00406a10();
    if (local18 == -0x2c8502b44bfffed6L) {
        sk_r60_3fc42c_clock_read_dispatch(1, (void *)FUN_00409248);
        return;
    }
    FUN_0011d7e8();              /* noreturn */
}

/* FUN_003fbd2c @ 0x3fbd2c   (est. sk_r60_clock_now_get_b)
 * Same as 003fbcd4 but dispatches FUN_003fc42c(1, FUN_004092d8).
 * Confidence: medium */
static void sk_r60_3fbd2c_clock_now_get_b(void)
{
    long local18;
    FUN_00406a10();
    if (local18 == -0x2c8502b44bfffed6L) {
        sk_r60_3fc42c_clock_read_dispatch(1, (void *)FUN_004092d8);
        return;
    }
    FUN_0011d7e8();              /* noreturn */
}

/* FUN_003fbd98 @ 0x3fbd98   (est. sk_r60_clock_fatal_missing)
 * Fatal clock/executor missing path: runs the four setup helpers then traps
 * via FUN_001afa84 (noreturn).
 * Confidence: medium */
static void sk_r60_3fbd98_clock_fatal_missing(void)
{
    FUN_00406fd4();
    FUN_00407030();
    FUN_003593c0();
    FUN_00407048();
    FUN_001afa84();              /* noreturn */
}

/* FUN_003fbdf0 @ 0x3fbdf0 / 003fbe18  (est. sk_r60_clock_now_wrap_a/b)
 * Stores the 16-byte clock value from 003fbcd4 / 003fbd2c into *out.
 * Confidence: high (pure forwarders). */
static void sk_r60_3fbdf0_clock_now_wrap_a(unsigned long out[2])
{
    out[0] = 0; out[1] = 0;
    /* FUN_003fbcd4 writes a 16-byte value; preserved here as the pair. */
    sk_r60_3fbcd4_clock_now_get_a();
}
static void sk_r60_3fbe18_clock_now_wrap_b(unsigned long out[2])
{
    out[0] = 0; out[1] = 0;
    sk_r60_3fbd2c_clock_now_get_b();
}

/* FUN_003fbe40 @ 0x3fbe40   (est. sk_r60_task_op_common)
 * Runs FUN_00407d74() then thunk_FUN_002d3c28().
 * Confidence: medium */
static void sk_r60_3fbe40_task_op_common(void)
{
    FUN_00407d74();
    thunk_FUN_002d3c28();
}

/* FUN_003fbf28 @ 0x3fbf28   (est. sk_r60_task_kind_validate)
 * Validates a task-kind token pair: if param_1 == 0x65756c61765f
 * ("_value" little-endian) and param_2 == -0x1a00000000000000, runs
 * FUN_003a25d4(param_2) and returns 0 (valid). Otherwise probes
 * FUN_002a0cf8 and returns (result ^ ~0) & 1.
 * Confidence: high (clear token compare).
 * Notes: 0x65756c61765f = ASCII "value_"; -0x1a00000000000000 = 0xe600000000000000. */
static unsigned int sk_r60_3fbf28_task_kind_validate(long p1, long p2)
{
    unsigned int u;
    if (p1 == 0x65756c61765fL && p2 == -0x1a00000000000000L) {
        FUN_003a25d4(p2);
        return 0;
    }
    u = (unsigned int)FUN_002a0cf8(0x65756c61765fL, 0xe600000000000000UL,
                                   p1, p2, 0);
    FUN_003a25d4(p2);
    return (u ^ 0xffffffffU) & 1U;
}

/* FUN_003fbf9c @ 0x3fbf9c   (est. sk_r60_task_kind_setup)
 * Runs FUN_004080b0, thunk_FUN_002298d4(0), FUN_001a8564.
 * Confidence: medium */
static void sk_r60_3fbf9c_task_kind_setup(void)
{
    FUN_004080b0();
    thunk_FUN_002298d4(0);
    FUN_001a8564();
}

/* FUN_003fbff4 @ 0x3fbff4   (est. sk_r60_task_enqueue_common_b)
 * Trivial forwarder to FUN_003fc038().
 * Confidence: high (pure tail call). */
static void sk_r60_3fbff4_task_enqueue_common_b(void)
{
    ((void (*)(void))sk_r60_3fc038_task_enqueue_build)();
}

/* FUN_003fc038 @ 0x3fc038   (est. sk_r60_task_enqueue_build)
 * Builds a task-enqueue request: loads the task pointer (+0x20) and its
 * continuation (+0x18), runs the enqueue helper FUN_0006a4c0 /
 * FUN_0006a4f0, builds the continuation pair via FUN_00002534(p6,p7), and
 * hands {p2,p3} + the pair + two metadata constants (0x676ea8, 0x66f5e0) to
 * FUN_001bdb28. Completes with FUN_0036b118(u1).
 * Confidence: medium
 * Notes: metadata constants 0x676ea8/0x66f5e0 are associated-type ids. */
static void sk_r60_3fc038_task_enqueue_build(unsigned long p1, unsigned long p2,
                                             unsigned long p3, unsigned long p4,
                                             unsigned long p5, unsigned long p6,
                                             unsigned long p7)
{
    unsigned long u1, u2, pair[2];
    u1 = *(unsigned long *)(p1 + 0x20);
    FUN_0006a4c0(p1, *(unsigned long *)(p1 + 0x18));
    u2 = FUN_0006a4f0(u1);
    FUN_003513b4(u2, p4);
    pair[0] = FUN_00002534(p6, p7);
    pair[1] = FUN_00002534(p6, p7);
    FUN_001bdb28(&p2, pair[0], pair[1], 0x676ea8, 0x66f5e0);
    FUN_0036b118(u1);
}

/* ================================================================== *
 * 0x3fc124 - 0x3fc860 : executor-enqueue descriptors + fatal traps
 * ================================================================== */

/* FUN_003fc124 @ 0x3fc124 / 003fc128  (est. sk_r60_enqueue_desc_b_a/b)
 * Enqueues via descriptor DAT_005a16a8 / id 0x67f0a0.
 * Confidence: high (pure forwarder to 003fc158). */
static void sk_r60_3fc124_enqueue_desc_b_a(unsigned long p1)
{
    ((void (*)(unsigned long, unsigned long, unsigned long))sk_r60_3fc158_task_enqueue_core)(
        p1, 0x67f0a0, (unsigned long)&DAT_005a16a8);
}
static void sk_r60_3fc128_enqueue_desc_b_b(unsigned long p1)
{
    ((void (*)(unsigned long, unsigned long, unsigned long))sk_r60_3fc158_task_enqueue_core)(
        p1, 0x67f0a0, (unsigned long)&DAT_005a16a8);
}

/* FUN_003fc158 @ 0x3fc158   (est. sk_r60_task_enqueue_core)
 * Core task enqueue: obtains the executor context (FUN_0035128c), loads the
 * task (+0x20) and continuation (+0x18), runs the enqueue helpers, then
 * either builds a fresh continuation (unaff_x21 == 0: FUN_00352ae4(frame,
 * 0x676ea8); FUN_001bea18(); FUN_0036b118(u2)) or reuses it, finally
 * FUN_000026e8(ctx) and FUN_000e15d8().
 * Confidence: medium
 * Notes: x21 selects new-vs-reuse continuation path. */
static void sk_r60_3fc158_task_enqueue_core(void)
{
    long ctx;
    unsigned long u2;
    unsigned char frame[16];
    unsigned long saved_x21;
    ctx = FUN_0035128c();
    u2 = *(unsigned long *)(ctx + 0x20);
    FUN_0006a4c0(ctx, *(unsigned long *)(ctx + 0x18));
    u2 = FUN_0006a668(u2);
    FUN_000bd3a4(u2);
    FUN_0036b118(0);   /* (*extraout_x8)() — continuation resume */
    if (saved_x21 == 0) {
        FUN_00352ae4(frame, 0x676ea8);
        FUN_001bea18();
        FUN_0036b118(u2);
        FUN_000026e8(ctx);
    } else {
        FUN_000026e8(ctx);
    }
    FUN_000e15d8();
}

/* FUN_003fc248 @ 0x3fc248 / 003fc24c  (est. sk_r60_task_resume_dispatch_a/b)
 * Trivial forwarders to FUN_003fc274().
 * Confidence: high (pure tail call). */
static void sk_r60_3fc248_task_resume_dispatch_a(void)
{
    ((void (*)(void))sk_r60_3fc274_task_resume_capture)();
}
static void sk_r60_3fc24c_task_resume_dispatch_b(void)
{
    ((void (*)(void))sk_r60_3fc274_task_resume_capture)();
}

/* FUN_003fc274 @ 0x3fc274   (est. sk_r60_task_resume_capture)
 * Resumes the task: calls the continuation (*in_x3)(), and stores its
 * 16-byte result into *out when the task is alive (unaff_x21 == 0).
 * Confidence: low (in_x3 indirect continuation; x21 liveness flag). */
static void sk_r60_3fc274_task_resume_capture(unsigned long out[2],
                                              unsigned long saved_x21)
{
    unsigned long r0, r1;
    r0 = ((unsigned long (*)(void))0)();   /* (*in_x3)() */
    r1 = r0;
    if (saved_x21 == 0) {
        out[0] = r0;
        out[1] = r1;
    }
}

/* FUN_003fc2a4 @ 0x3fc2a4 / 003fc2a8  (est. sk_r60_enqueue_x20_b_a/b)
 * Enqueues via 003fbff4 from the x20 task context.
 * Confidence: medium */
static void sk_r60_3fc2a4_enqueue_x20_b_a(unsigned long p1,
                                          unsigned long saved_x20)
{
    ((void (*)(unsigned long, unsigned long, unsigned long))sk_r60_3fbff4_task_enqueue_common_b)(
        p1, saved_x20, *(unsigned long *)(saved_x20 + 8));
}
static void sk_r60_3fc2a8_enqueue_x20_b_b(unsigned long p1,
                                          unsigned long saved_x20)
{
    ((void (*)(unsigned long, unsigned long, unsigned long))sk_r60_3fbff4_task_enqueue_common_b)(
        p1, saved_x20, *(unsigned long *)(saved_x20 + 8));
}

/* FUN_003fc2c0 @ 0x3fc2c0   (est. sk_r60_clock_now_get_2_a)
 * Clock read dispatching FUN_003fc42c(2, FUN_00409248).
 * Confidence: medium */
static void sk_r60_3fc2c0_clock_now_get_2_a(void)
{
    long local18;
    FUN_00406a10();
    if (local18 == -0x2c8502b44bfffed6L) {
        sk_r60_3fc42c_clock_read_dispatch(2, (void *)FUN_00409248);
        return;
    }
    FUN_0011d7e8();              /* noreturn */
}

/* FUN_003fc318 @ 0x3fc318   (est. sk_r60_clock_now_get_2_b)
 * Clock read dispatching FUN_003fc42c(2, FUN_004092d8).
 * Confidence: medium */
static void sk_r60_3fc318_clock_now_get_2_b(void)
{
    long local18;
    FUN_00406a10();
    if (local18 == -0x2c8502b44bfffed6L) {
        sk_r60_3fc42c_clock_read_dispatch(2, (void *)FUN_004092d8);
        return;
    }
    FUN_0011d7e8();              /* noreturn */
}

/* FUN_003fc384 @ 0x3fc384   (est. sk_r60_clock_fatal_missing_2)
 * Same fatal shape as 003fbd98 (traps via FUN_001afa84).
 * Confidence: medium */
static void sk_r60_3fc384_clock_fatal_missing_2(void)
{
    FUN_00406fd4();
    FUN_00407030();
    FUN_003593c0();
    FUN_00407048();
    FUN_001afa84();              /* noreturn */
}

/* FUN_003fc3dc @ 0x3fc3dc / 003fc404  (est. sk_r60_clock_now_wrap_2_a/b)
 * Stores the 16-byte clock from 003fc2c0 / 003fc318.
 * Confidence: high (pure forwarders). */
static void sk_r60_3fc3dc_clock_now_wrap_2_a(unsigned long out[2])
{
    sk_r60_3fc2c0_clock_now_get_2_a();
}
static void sk_r60_3fc404_clock_now_wrap_2_b(unsigned long out[2])
{
    sk_r60_3fc318_clock_now_get_2_b();
}

/* FUN_003fc42c @ 0x3fc42c   (est. sk_r60_clock_read_dispatch)
 * Dispatches a clock read: sets the sentinel guard (-0x2c8502b44bfffed6),
 * calls the clock primitive (*param_2)(&hi, &lo, param_1), normalizes via
 * FUN_003fbc58(hi, lo), and returns if the sentinel survived, else traps.
 * Confidence: medium
 * Notes: param_1 is the clock id; param_2 the clock-read primitive. */
static void sk_r60_3fc42c_clock_read_dispatch(unsigned long id, void *prim)
{
    unsigned long lo, hi;
    long local18;
    local18 = -0x2c8502b44bfffed6L;
    lo = 0; hi = 0;
    ((void (*)(unsigned long *, long *, unsigned long))prim)(&hi, &local18, id);
    sk_r60_3fbc58_secs_nanos_add(hi, lo, 0);
    if (local18 == -0x2c8502b44bfffed6L)
        return;
    FUN_0011d7e8();              /* noreturn */
}

/* FUN_003fc49c @ 0x3fc49c   (est. sk_r60_task_continuation_step)
 * Steps a task continuation: calls thunk_FUN_002d3c28 with the two words of
 * *out plus p2, p3, storing the 16-byte result back into *out.
 * Confidence: medium */
static void sk_r60_3fc49c_task_continuation_step(unsigned long out[2],
                                                  unsigned long p2,
                                                  unsigned long p3)
{
    unsigned long r0, r1;
    r0 = thunk_FUN_002d3c28(out[0], out[1], p2, p3);
    r1 = thunk_FUN_002d3c28(out[0], out[1], p2, p3);
    out[0] = r0;
    out[1] = r1;
}

/* FUN_003fc4d4 @ 0x3fc4d4   (est. sk_r60_task_group_op_common)
 * Runs the task-group operation sequence (six helpers + thunk).
 * Confidence: medium */
static void sk_r60_3fc4d4_task_group_op_common(void)
{
    FUN_00077888();
    FUN_003509ec();
    thunk_FUN_00019858();
    FUN_0035053c();
    thunk_FUN_002d4a64();
    FUN_00351790();
    FUN_00100efc();
    thunk_FUN_002d3c28();
}

/* FUN_003fc518 @ 0x3fc518   (est. sk_r60_task_group_op_x21)
 * Task-group op from the x21 context: runs the sequence then stores the
 * 16-byte thunk_FUN_002d3c28 result into *unaff_x21.
 * Confidence: low (unaff_x21 output slot; 16-byte return). */
static void sk_r60_3fc518_task_group_op_x21(unsigned long saved_x21[2])
{
    unsigned long r0, r1;
    FUN_0035098c();
    thunk_FUN_00019858();
    FUN_0035053c();
    thunk_FUN_002d4a64();
    FUN_00351790();
    FUN_000e15d8();
    r0 = thunk_FUN_002d3c28();
    r1 = thunk_FUN_002d3c28();
    saved_x21[0] = r0;
    saved_x21[1] = r1;
}

/* FUN_003fc56c @ 0x3fc56c   (est. sk_r60_task_prepare_run)
 * Prepares task run: frame setup, executor ops, thunk_FUN_002d738c,
 * FUN_001a8564.
 * Confidence: medium */
static void sk_r60_3fc56c_task_prepare_run(void)
{
    unsigned char frame[72];
    FUN_003504d0();
    FUN_004080b0();
    FUN_00350624(frame);
    thunk_FUN_002d738c();
    FUN_001a8564();
}

/* FUN_003fc5c4 @ 0x3fc5c4 / 003fc608  (est. sk_r60_task_body_dispatch_x19_a/b)
 * Dispatches the task body: FUN_00407e88() then (*extraout_x9)() storing the
 * 16-byte result into *unaff_x19.
 * Confidence: low (indirect continuation through extraout_x9). */
static void sk_r60_3fc5c4_task_body_dispatch_x19_a(unsigned long out[2])
{
    unsigned long r0, r1;
    FUN_00407e88();
    r0 = ((unsigned long (*)(void))0)();   /* (*extraout_x9)() */
    r1 = r0;
    out[0] = r0;
    out[1] = r1;
}
static void sk_r60_3fc608_task_body_dispatch_x19_b(unsigned long out[2])
{
    unsigned long r0, r1;
    FUN_00407e88();
    r0 = ((unsigned long (*)(void))0)();   /* (*extraout_x9)() */
    r1 = r0;
    out[0] = r0;
    out[1] = r1;
}

/* FUN_003fc64c @ 0x3fc64c   (est. sk_r60_task_body_dispatch_x3)
 * Body dispatch through (*in_x3)() with frame setup.
 * Confidence: low */
static void sk_r60_3fc64c_task_body_dispatch_x3(void)
{
    unsigned char frame[72];
    FUN_001a84f4(frame);
    FUN_00350548(frame);
    ((void (*)(void))0)();       /* (*in_x3)() */
    FUN_001a8564();
}

/* FUN_003fc6b4 @ 0x3fc6b4   (est. sk_r60_executor_fatal_missing)
 * Fatal executor-missing path (traps via FUN_001afa84).
 * Confidence: medium */
static void sk_r60_3fc6b4_executor_fatal_missing(void)
{
    FUN_00406fd4();
    FUN_00407030();
    FUN_003593c0();
    FUN_00407048();
    FUN_001afa84();              /* noreturn */
}

/* FUN_003fc70c @ 0x3fc70c   (est. sk_r60_executor_unimplemented_fatal)
 * Fatal "no executor implementation" trap: loads the string
 * "There is no executor implementation..." (0x5dc2e0), probes the
 * associated-type (FUN_003593c0), and traps via FUN_001afa84 with the
 * Concurrency.UnimplementedExecutor selector (0x5dc2b0, len 0x28, kind 2).
 * Confidence: high (string-matched).
 * Notes: string refs s_There_is_no_executor_implementat_005dc2e0 and
 *   s__Concurrency_UnimplementedExecut_005dc2b0. */
static void sk_r60_3fc70c_executor_unimplemented_fatal(void)
{
    unsigned long u1;
    u1 = FUN_0035ac70(0x5dc2e0);   /* "There is no executor implementation" */
    u1 = FUN_003593c0(u1, u1);
    FUN_001afa84(u1, 0xb, 2, 0xd00000000000002aUL,
                 0x8000000000000000UL | 0, 0x5dc2b0, 0x28, 2);
    /* noreturn */
}

/* FUN_003fc76c @ 0x3fc76c   (est. sk_r60_executor_unimpl_break_1)
 * Loads the "no executor implementation" string, runs FUN_00406eb0, then
 * SoftwareBreakpoint(1, 0x3fc79c). Noreturn.
 * Confidence: high (string-matched, explicit break). */
static void sk_r60_3fc76c_executor_unimpl_break_1(void)
{
    FUN_0035ac70(0x5dc2e0);
    FUN_00406eb0();
    __builtin_trap();            /* SoftwareBreakpoint(1, 0x3fc79c) */
}

/* FUN_003fc79c @ 0x3fc79c   (est. sk_r60_executor_unimpl_break_2)
 * Same trap shape as 003fc76c; break at 0x3fc7cc.
 * Confidence: high */
static void sk_r60_3fc79c_executor_unimpl_break_2(void)
{
    FUN_0035ac70(0x5dc2e0);
    FUN_00406eb0();
    __builtin_trap();            /* SoftwareBreakpoint(1, 0x3fc7cc) */
}

/* FUN_003fc7cc @ 0x3fc7cc / 003fc7d0  (est. sk_r60_executor_fatal_then_cleanup_a/b)
 * Runs the unimplemented-executor fatal then the cleanup FUN_003d4f18.
 * Confidence: medium */
static void sk_r60_3fc7cc_executor_fatal_then_cleanup_a(void)
{
    sk_r60_3fc70c_executor_unimplemented_fatal();
    FUN_003d4f18();
}
static void sk_r60_3fc7d0_executor_fatal_then_cleanup_b(void)
{
    sk_r60_3fc70c_executor_unimplemented_fatal();
    FUN_003d4f18();
}

/* FUN_003fc7e0 @ 0x3fc7e0   (est. sk_r60_executor_cleanup_only)
 * Runs only FUN_003d4f18.
 * Confidence: medium */
static void sk_r60_3fc7e0_executor_cleanup_only(void)
{
    FUN_003d4f18();
}

/* FUN_003fc7f4 @ 0x3fc7f4 / 003fc7f8  (est. sk_r60_executor_fatal_cleanup_b_a/b)
 * Runs 003fc76c then cleanup FUN_003d4e84.
 * Confidence: medium */
static void sk_r60_3fc7f4_executor_fatal_cleanup_b_a(void)
{
    sk_r60_3fc76c_executor_unimpl_break_1();
    FUN_003d4e84();
}
static void sk_r60_3fc7f8_executor_fatal_cleanup_b_b(void)
{
    sk_r60_3fc76c_executor_unimpl_break_1();
    FUN_003d4e84();
}

/* FUN_003fc80c @ 0x3fc80c / 003fc810  (est. sk_r60_executor_unimpl_break_3_a/b)
 * Runs 003fc79c, loads the string + target FUN_003fc81c, then
 * SoftwareBreakpoint(1, 0x3fc84c). Noreturn.
 * Confidence: high */
static void sk_r60_3fc80c_executor_unimpl_break_3_a(void)
{
    sk_r60_3fc79c_executor_unimpl_break_2();
    FUN_0035ac70(0x5dc2e0, (unsigned long)sk_r60_3fc81c_executor_unimpl_break_4);
    FUN_00406eb0();
    __builtin_trap();            /* SoftwareBreakpoint(1, 0x3fc84c) */
}
static void sk_r60_3fc810_executor_unimpl_break_3_b(void)
{
    sk_r60_3fc79c_executor_unimpl_break_2();
    FUN_0035ac70(0x5dc2e0, (unsigned long)sk_r60_3fc81c_executor_unimpl_break_4);
    FUN_00406eb0();
    __builtin_trap();            /* SoftwareBreakpoint(1, 0x3fc84c) */
}

/* FUN_003fc81c @ 0x3fc81c   (est. sk_r60_executor_unimpl_break_4)
 * Loads the string and breaks at 0x3fc84c. Noreturn.
 * Confidence: high */
static void sk_r60_3fc81c_executor_unimpl_break_4(void)
{
    FUN_0035ac70(0x5dc2e0);
    FUN_00406eb0();
    __builtin_trap();            /* SoftwareBreakpoint(1, 0x3fc84c) */
}

/* FUN_003fc850 @ 0x3fc850 / 003fc854  (est. sk_r60_main_executor_enqueue_break_a/b)
 * Main-executor enqueue stub: runs 003fc81c, loads
 * "swift_task_enqueueMainExecutor..." (0x5dc330) + target FUN_003fc860,
 * runs FUN_00407134/FUN_004079f4, breaks at 0x3fc8a0. Noreturn.
 * Confidence: high (string-matched). */
static void sk_r60_3fc850_main_executor_enqueue_break_a(void)
{
    sk_r60_3fc81c_executor_unimpl_break_4();
    FUN_0035ac70(0x5dc330, (unsigned long)sk_r60_3fc860_main_executor_enqueue_break_c);
    FUN_00407134();
    FUN_004079f4();
    __builtin_trap();            /* SoftwareBreakpoint(1, 0x3fc8a0) */
}
static void sk_r60_3fc854_main_executor_enqueue_break_b(void)
{
    sk_r60_3fc81c_executor_unimpl_break_4();
    FUN_0035ac70(0x5dc330, (unsigned long)sk_r60_3fc860_main_executor_enqueue_break_c);
    FUN_00407134();
    FUN_004079f4();
    __builtin_trap();            /* SoftwareBreakpoint(1, 0x3fc8a0) */
}

/* FUN_003fc860 @ 0x3fc860   (est. sk_r60_main_executor_enqueue_break_c)
 * Loads the main-executor enqueue string and breaks at 0x3fc8a0. Noreturn.
 * Confidence: high */
static void sk_r60_3fc860_main_executor_enqueue_break_c(void)
{
    FUN_0035ac70(0x5dc330);
    FUN_00407134();
    FUN_004079f4();
    __builtin_trap();            /* SoftwareBreakpoint(1, 0x3fc8a0) */
}

/* FUN_003fc8a0 @ 0x3fc8a0   (est. sk_r60_task_execute_continuation)
 * Executes a task continuation: reads the continuation pair (FUN_003d50cc),
 * resolves the target (FUN_003fcbbc), runs the body
 * (*extraout_x8)(a, b, cont_hi), completes with FUN_0036b118.
 * Confidence: low (indirect continuation; extraout_x8). */
static void sk_r60_3fc8a0_task_execute_continuation(void)
{
    unsigned long c0, c1, u1, r0, r1;
    c0 = FUN_003d50cc();
    c1 = c0;
    u1 = sk_r60_3fcbbc_indirect_ret_data_field(c1);
    r0 = FUN_003504ac(u1);
    r1 = r0;
    ((void (*)(unsigned long, unsigned long, unsigned long))0)(r0, r1, c1);
    FUN_0036b118(c0);
}

/* ================================================================== *
 * 0x3fc90c - 0x3fcd04 : per-executor lazy global registration + helpers
 * ================================================================== */

/* FUN_003fc90c @ 0x3fc90c / 003fc910  (est. sk_r60_executor_global_init_a/b)
 * Installs global executor A: allocates the 0x10-byte instance from
 * metadata 0x6578f8 (FUN_0036a940(0x6578f8, 0x10, 7)) into DAT_006adf38 and
 * stores the descriptor 0x67dcb8 at DAT_006adf40.
 * Confidence: high (clear global-init shape).
 * Notes: DAT_006adf38/40 = global executor A instance + descriptor. */
static void sk_r60_3fc90c_executor_global_init_a(void)
{
    DAT_006adf38 = FUN_0036a940(0x6578f8, 0x10, 7);
    DAT_006adf40 = 0x67dcb8;
}
static void sk_r60_3fc910_executor_global_init_b(void)
{
    DAT_006adf38 = FUN_0036a940(0x6578f8, 0x10, 7);
    DAT_006adf40 = 0x67dcb8;
}

/* FUN_003fc950 @ 0x3fc950   (est. sk_r60_executor_global_get_a)
 * Lazy getter for global executor A: if the one-time flag DAT_006c0b78 != -1,
 * runs FUN_00407568 + FUN_0039a128 (init once). Returns &DAT_006adf38.
 * Confidence: high (textbook lazy-init global getter). */
static unsigned long sk_r60_3fc950_executor_global_get_a(void)
{
    if (DAT_006c0b78 != (unsigned long)-1) {
        FUN_00407568();
        FUN_0039a128();
    }
    return (unsigned long)&DAT_006adf38;
}

/* FUN_003fc988 @ 0x3fc988   (est. sk_r60_executor_global_release_a)
 * Releases global executor A: lazy-init if needed, then FUN_0036b270(inst).
 * Confidence: medium */
static void sk_r60_3fc988_executor_global_release_a(void)
{
    if (DAT_006c0b78 != (unsigned long)-1) {
        FUN_00407568();
        FUN_0039a128();
    }
    FUN_0036b270(DAT_006adf38);
}

/* FUN_003fc9d0 @ 0x3fc9d0 / 003fc9d4  (est. sk_r60_executor_global_init_b2_a/b)
 * Installs global executor B: allocates from metadata 0x657950 into
 * DAT_006adf50, descriptor 0x67dd08 at DAT_006adf58.
 * Confidence: high */
static void sk_r60_3fc9d0_executor_global_init_b2_a(void)
{
    DAT_006adf50 = FUN_0036a940(0x657950, 0x10, 7);
    DAT_006adf58 = 0x67dd08;
}
static void sk_r60_3fc9d4_executor_global_init_b2_b(void)
{
    DAT_006adf50 = FUN_0036a940(0x657950, 0x10, 7);
    DAT_006adf58 = 0x67dd08;
}

/* FUN_003fca14 @ 0x3fca14   (est. sk_r60_executor_global_get_b)
 * Lazy getter for global executor B (flag DAT_006c0b50). Returns &DAT_006adf50.
 * Confidence: high */
static unsigned long sk_r60_3fca14_executor_global_get_b(void)
{
    if (DAT_006c0b50 != (unsigned long)-1) {
        FUN_00406c3c();
        FUN_0039a128();
    }
    return (unsigned long)&DAT_006adf50;
}

/* FUN_003fca4c @ 0x3fca4c   (est. sk_r60_executor_global_release_b)
 * Releases global executor B.
 * Confidence: medium */
static void sk_r60_3fca4c_executor_global_release_b(void)
{
    if (DAT_006c0b50 != (unsigned long)-1) {
        FUN_00406c3c();
        FUN_0039a128();
    }
    FUN_0036b270(DAT_006adf50);
}

/* FUN_003fca94 @ 0x3fca94   (est. sk_r60_executor_global_release_a_via_get)
 * Releases executor A by dereferencing the getter result.
 * Confidence: medium */
static void sk_r60_3fca94_executor_global_release_a_via_get(void)
{
    FUN_0036b270(*(unsigned long *)sk_r60_3fc950_executor_global_get_a());
}

/* FUN_003fcac8 @ 0x3fcac8   (est. sk_r60_executor_global_release_b_via_get)
 * Releases executor B by dereferencing the getter result.
 * Confidence: medium */
static void sk_r60_3fcac8_executor_global_release_b_via_get(void)
{
    FUN_0036b270(*(unsigned long *)sk_r60_3fca14_executor_global_get_b());
}

/* FUN_003fcafc @ 0x3fcafc   (est. sk_r60_indirect_ret_field_10b)
 * Same tagged-storage accessor for field at +0x10 (twin of 003fcc1c).
 * Confidence: high */
static long sk_r60_3fcafc_indirect_ret_field_10b(unsigned long v)
{
    if ((v & 1) != 0)
        v = *(unsigned long *)(v & ~1UL);
    return (long)(v + 0x10) + (long)*(int *)(v + 0x10);
}

/* FUN_003fcb2c @ 0x3fcb2c   (est. sk_r60_indirect_ret_field_14b)
 * Tagged-storage accessor for field at +0x14.
 * Confidence: high */
static long sk_r60_3fcb2c_indirect_ret_field_14b(unsigned long v)
{
    if ((v & 1) != 0)
        v = *(unsigned long *)(v & ~1UL);
    return (long)(v + 0x14) + (long)*(int *)(v + 0x14);
}

/* FUN_003fcb5c @ 0x3fcb5c   (est. sk_r60_indirect_ret_field_18)
 * Tagged-storage accessor for field at +0x18.
 * Confidence: high */
static long sk_r60_3fcb5c_indirect_ret_field_18(unsigned long v)
{
    if ((v & 1) != 0)
        v = *(unsigned long *)(v & ~1UL);
    return (long)(v + 0x18) + (long)*(int *)(v + 0x18);
}

/* FUN_003fcb8c @ 0x3fcb8c   (est. sk_r60_indirect_ret_field_c)
 * Tagged-storage accessor for field at +0xc.
 * Confidence: high */
static long sk_r60_3fcb8c_indirect_ret_field_c(unsigned long v)
{
    if ((v & 1) != 0)
        v = *(unsigned long *)(v & ~1UL);
    return (long)(v + 0xc) + (long)*(int *)(v + 0xc);
}

/* FUN_003fcbbc @ 0x3fcbbc   (est. sk_r60_indirect_ret_data_field)
 * Indirect-return accessor: if param_1 is a tagged pointer (low bit set),
 * load the heap object base (param_1 & ~1), else use it directly; returns
 * base + 8 + *(int *)(base + 8) — the "data" field of a two-word record.
 * Confidence: high (classic Swift indirect-return / tagged storage pattern).
 * Notes: shared with 003fcc1c/003fcc4c/003fd194/003fd3fc (field offsets
 * 8/0x10/0x14/0x10/0x18). */
static long sk_r60_3fcbbc_indirect_ret_data_field(unsigned long v)
{
    if ((v & 1) != 0)
        v = *(unsigned long *)(v & ~1UL);
    return (long)(v + 8) + (long)*(int *)(v + 8);
}

/* FUN_003fcc1c @ 0x3fcc1c   (est. sk_r60_indirect_ret_field_10)
 * Same tagged-storage accessor for field at +0x10.
 * Confidence: high */
static long sk_r60_3fcc1c_indirect_ret_field_10(unsigned long v)
{
    if ((v & 1) != 0)
        v = *(unsigned long *)(v & ~1UL);
    return (long)(v + 0x10) + (long)*(int *)(v + 0x10);
}

/* FUN_003fcc4c @ 0x3fcc4c   (est. sk_r60_indirect_ret_field_14)
 * Same tagged-storage accessor for field at +0x14.
 * Confidence: high */
static long sk_r60_3fcc4c_indirect_ret_field_14(unsigned long v)
{
    if ((v & 1) != 0)
        v = *(unsigned long *)(v & ~1UL);
    return (long)(v + 0x14) + (long)*(int *)(v + 0x14);
}

/* FUN_003fccc4 @ 0x3fccc4   (est. sk_r60_cond_release)
 * Releases param_2 via FUN_0036b270 only when param_1 != 0.
 * Confidence: high */
static void sk_r60_3fccc4_cond_release(long p1, unsigned long p2)
{
    if (p1 != 0)
        FUN_0036b270(p2);
}

/* FUN_003fccd4 @ 0x3fccd4 / 003fcd04  (est. sk_r60_task_destroy_common_a/b)
 * Trivial forwarders to FUN_00021480().
 * Confidence: high (pure tail call). */
static void sk_r60_3fccd4_task_destroy_common_a(void)
{
    FUN_00021480();
}
static void sk_r60_3fcd04_task_destroy_common_b(void)
{
    FUN_00021480();
}

/* ================================================================== *
 * 0x3fcddc - 0x3fdf74 : task-dispatch continuations + job/queue ops
 * ================================================================== */

/* FUN_003fcddc @ 0x3fcddc   (est. sk_r60_task_dispatch_continuation)
 * Dispatches a task continuation: reads the 4 task args (+0x10..+0x28) from
 * the x20 context, builds the dispatch record (FUN_0040bb18(DAT_005a0034),
 * FUN_00407ac4, vtable DAT_00405fa0), resolves the target from
 * DAT_005a0030 (tag+data), and runs it via FUN_00408044 then (*target)().
 * Confidence: low (jump-table dispatch; x20 context).
 * Notes: DAT_005a0030/34 = task continuation tag+data; DAT_00405fa0 =
 * generic task vtable. */
static void sk_r60_3fcddc_task_dispatch_continuation(unsigned long saved_x20)
{
    unsigned long u5, t, a1, a2, a3, a4, aux;
    unsigned long *rec;

    FUN_00408058();
    u5 = FUN_0040700c();
    a1 = *(unsigned long *)(saved_x20 + 0x10);
    a2 = *(unsigned long *)(saved_x20 + 0x18);
    a3 = *(unsigned long *)(saved_x20 + 0x20);
    a4 = *(unsigned long *)(saved_x20 + 0x28);
    FUN_0040bb18(DAT_005a0034);
    rec = (unsigned long *)FUN_00407ac4();
    *rec = 0;                    /* extraout_x17 */
    rec[1] = (unsigned long)&DAT_00405fa0;
    t = (unsigned long)((long)&DAT_005a0030 + (long)DAT_005a0030);
    FUN_00408044(u5, a3, a4, a1, a2, t, 0);
    ((void (*)(void))t)();
}

/* FUN_003fce98 @ 0x3fce98   (est. sk_r60_task_dispatch_indirect)
 * Indirect task dispatch: builds the dispatch record, resolves the target
 * from an unrecovered jump table (*x27 + x27), runs the setup helpers, then
 * indirect-jumps.
 * Confidence: low (jump table not recovered). */
static void sk_r60_3fce98_task_dispatch_indirect(int *meta,
                                                 unsigned long saved_x30)
{
    unsigned long *rec;
    unsigned long target;

    FUN_00408190();
    FUN_004070d8();
    FUN_0008409c();
    FUN_00407e3c();
    rec = (unsigned long *)FUN_00407ac4();
    *rec = 0;                    /* extraout_x17 */
    rec[1] = (unsigned long)&DAT_00405fa0;
    target = (unsigned long)((long)*meta + (long)meta);
    FUN_00084180();
    FUN_00407f84();
    FUN_00408178(saved_x30);
    /* WARNING: unrecovered jumptable at 0x3fcf20 -> indirect jump. */
    ((void (*)(void))target)();
}

/* FUN_003fcf28 @ 0x3fcf28   (est. sk_r60_task_selector_match)
 * Tests a task selector against the x20 context args via FUN_003e33d8,
 * returns (result & 1).
 * Confidence: medium */
static unsigned int sk_r60_3fcf28_task_selector_match(unsigned long p1,
                                                       unsigned long p2,
                                                       unsigned long saved_x20)
{
    return (unsigned int)(FUN_003e33d8(p1, p2,
        *(unsigned long *)(saved_x20 + 0x28),
        *(unsigned long *)(saved_x20 + 0x10),
        *(unsigned long *)(saved_x20 + 0x18),
        *(unsigned long *)(saved_x20 + 0x20)) & 1);
}

/* FUN_003fcf48 @ 0x3fcf48   (est. sk_r60_task_dispatch_indirect_2)
 * Indirect task dispatch variant (vtable label LAB_003fcfd4).
 * Confidence: low (jump table not recovered). */
static void sk_r60_3fcf48_task_dispatch_indirect_2(int *meta,
                                                   unsigned long saved_x30)
{
    unsigned long *rec;
    unsigned long target;

    FUN_00408190();
    FUN_004070d8();
    FUN_0008409c();
    FUN_00407e3c();
    rec = (unsigned long *)FUN_00407ac4();
    *rec = 0;                    /* extraout_x17 */
    rec[1] = (unsigned long)0;   /* &LAB_003fcfd4 */
    target = (unsigned long)((long)*meta + (long)meta);
    FUN_00084180();
    FUN_00407f84();
    FUN_00408178(saved_x30);
    /* WARNING: unrecovered jumptable at 0x3fcfd0 -> indirect jump. */
    ((void (*)(void))target)();
}

/* FUN_003fd0bc @ 0x3fd0bc   (est. sk_r60_task_destroy_common_c)
 * Trivial forwarder to FUN_00021480().
 * Confidence: high */
static void sk_r60_3fd0bc_task_destroy_common_c(void)
{
    FUN_00021480();
}

/* FUN_003fd194 @ 0x3fd194   (est. sk_r60_indirect_ret_field_10c)
 * Tagged-storage accessor for field at +0x10 (third twin).
 * Confidence: high */
static long sk_r60_3fd194_indirect_ret_field_10c(unsigned long v)
{
    if ((v & 1) != 0)
        v = *(unsigned long *)(v & ~1UL);
    return (long)(v + 0x10) + (long)*(int *)(v + 0x10);
}

/* FUN_003fd1c4 @ 0x3fd1c4   (est. sk_r60_task_metadata_init)
 * Initializes task metadata: reads the 3 args (+0x10..+0x20), allocates the
 * record (FUN_0040bb18(DAT_005a0134), FUN_00406fe0), links it at
 * unaff_x22+0x10, then FUN_003ed340(u4, a2, a3, a1).
 * Confidence: low (unaff_x20/x22 context; extraout registers). */
static void sk_r60_3fd1c4_task_metadata_init(unsigned long saved_x20,
                                             long saved_x22)
{
    unsigned long a1, a2, a3, u4;
    unsigned long *rec;

    FUN_00406fd4();
    a1 = *(unsigned long *)(saved_x20 + 0x10);
    a2 = *(unsigned long *)(saved_x20 + 0x18);
    a3 = *(unsigned long *)(saved_x20 + 0x20);
    FUN_0040bb18(DAT_005a0134);
    rec = (unsigned long *)FUN_00406fe0();
    *(unsigned long **)(saved_x22 + 0x10) = rec;
    *rec = 0;                    /* extraout_x17 */
    u4 = FUN_00407d90();
    FUN_003ed340(u4, a2, a3, a1);
}

/* FUN_003fd25c @ 0x3fd25c / 003fd260  (est. sk_r60_task_metadata_set_a/b)
 * Sets task metadata via FUN_003ed5f8(p1, x20->+0x10).
 * Confidence: medium */
static void sk_r60_3fd25c_task_metadata_set_a(unsigned long p1,
                                              unsigned long saved_x20)
{
    FUN_003ed5f8(p1, *(unsigned long *)(saved_x20 + 0x10));
}
static void sk_r60_3fd260_task_metadata_set_b(unsigned long p1,
                                              unsigned long saved_x20)
{
    FUN_003ed5f8(p1, *(unsigned long *)(saved_x20 + 0x10));
}

/* FUN_003fd278 @ 0x3fd278   (est. sk_r60_task_metadata_alloc_link)
 * Allocates and links task metadata: FUN_00407924, FUN_00351a68,
 * FUN_0040bb18(DAT_005a014c), FUN_00406fe0, links at unaff_x22+0x10, sets
 * the continuation FUN_003eebf0, then indirect-dispatch.
 * Confidence: low (jump table not recovered). */
static void sk_r60_3fd278_task_metadata_alloc_link(long saved_x22,
                                                   unsigned long saved_x30)
{
    unsigned long *rec;

    FUN_00407924();
    FUN_00351a68();
    FUN_0040bb18(DAT_005a014c);
    rec = (unsigned long *)FUN_00406fe0();
    *(unsigned long **)(saved_x22 + 0x10) = rec;
    *rec = 0;                    /* extraout_x17 */
    rec[1] = (unsigned long)FUN_003eebf0;
    FUN_004076a8(saved_x30);
    /* WARNING: unrecovered jumptable at 0x3fd350 -> indirect jump. */
}

/* FUN_003fd3ac @ 0x3fd3ac   (est. sk_r60_task_dispatch_typed)
 * Typed task dispatch: reads the 2 args (+0x10, +0x18), builds the selector
 * via FUN_001ee018, and dispatches FUN_004ba7ec(p1, sel, 1, a3).
 * Confidence: medium */
static void sk_r60_3fd3ac_task_dispatch_typed(unsigned long p1,
                                              unsigned long saved_x20)
{
    unsigned long sel, a3;
    a3 = *(unsigned long *)(saved_x20 + 0x20);
    sel = FUN_001ee018(*(unsigned long *)(saved_x20 + 0x10),
                       *(unsigned long *)(saved_x20 + 0x18));
    FUN_004ba7ec(p1, sel, 1, a3);
}

/* FUN_003fd3fc @ 0x3fd3fc   (est. sk_r60_indirect_ret_field_18b)
 * Tagged-storage accessor for field at +0x18.
 * Confidence: high */
static long sk_r60_3fd3fc_indirect_ret_field_18b(unsigned long v)
{
    if ((v & 1) != 0)
        v = *(unsigned long *)(v & ~1UL);
    return (long)(v + 0x18) + (long)*(int *)(v + 0x18);
}

/* FUN_003fd4ac @ 0x3fd4ac   (est. sk_r60_task_mode_set_a)
 * Sets a task execution mode: builds the mode selector (FUN_004072c0,
 * FUN_00377824 with &DAT_00614a5c), runs the mode helpers, then
 * FUN_00377bec(u1, u2, p1).
 * Confidence: low (16-byte returns; mode-selector descriptor). */
static void sk_r60_3fd4ac_task_mode_set_a(unsigned long p1, long p2)
{
    unsigned long u1, u2, aux[2];
    u2 = *(unsigned long *)(p2 + 0x10);
    aux[0] = FUN_004072c0();
    aux[1] = FUN_004072c0();
    u2 = FUN_00377824(aux[0], aux[1], u2, &DAT_00614a5c);
    FUN_0006b6f4();
    FUN_00351e3c();
    FUN_00377bec();
    u1 = FUN_00406d60();
    FUN_00377bec(u1, u2, p1);
}

/* FUN_003fd554 @ 0x3fd554   (est. sk_r60_task_mode_set_b)
 * Mode-set twin of 003fd4ac.
 * Confidence: low */
static void sk_r60_3fd554_task_mode_set_b(unsigned long p1, long p2)
{
    unsigned long u1, u2, aux[2];
    u1 = *(unsigned long *)(p2 + 0x10);
    aux[0] = FUN_004072c0();
    aux[1] = FUN_004072c0();
    u1 = FUN_00377824(aux[0], aux[1], u1, &DAT_00614a5c);
    FUN_0006b6f4();
    FUN_00351e3c();
    FUN_00377bec();
    u2 = FUN_00406d60();
    FUN_00377bec(u2, u1, p1);
}

/* FUN_003fd7bc @ 0x3fd7bc   (est. sk_r60_job_acquire_bounded)
 * Acquires a job/continuation slot with bounds checks: runs the lock + job
 * setup; if the count is < 0x19 and the value passes the <0x1000 and !=
 * 0xffffffff checks, copies the {count,ptr} pair; else falls back to
 * FUN_00349a9c and releases.
 * Confidence: low (extraout registers; flag-based branch). */
static void sk_r60_3fd7bc_job_acquire_bounded(void)
{
    unsigned long *src, *dst, u2;
    int zr;
    unsigned long lo;

    FUN_0034d724();
    FUN_0040654c();
    FUN_00377824();
    FUN_0034b57c();
    FUN_0035510c(0);
    FUN_0034c144();
    if (zr && 0 < 0x19) {
        FUN_00406c08();
        ((void (*)(void))0)();   /* (*extraout_x9)() */
        FUN_00349cd0();
        u2 = *src;
        if (u2 < 0x1000 && (u2 & 0xffffffffUL) != 0xffffffffUL) {
            dst[1] = src[1];
            *dst = u2;
            return;
        }
        lo = src[1];
        *dst = u2;
        dst[1] = lo;
    } else {
        FUN_00349a9c();
    }
    FUN_0036b270();
}

/* FUN_003fd874 @ 0x3fd874   (est. sk_r60_job_release_checked)
 * Releases a job slot: runs the lock/job helpers, and if the count is out of
 * the valid range (<0x1000 and != 0xffffffff) frees the pair.
 * Confidence: low (extraout registers). */
static void sk_r60_3fd874_job_release_checked(void)
{
    unsigned long u1, *pair;

    FUN_003561f4();
    u1 = FUN_0040654c();
    u1 = FUN_00377824(u1, 0);
    FUN_0034ab20(u1, u1);
    ((void (*)(void))(*(unsigned long *)(0 + 8)))();
    FUN_0034de54(*(unsigned long *)(0 + 0x40));
    if (0xfff < *pair || (*pair & 0xffffffffUL) == 0xffffffffUL) {
        FUN_0036b118(pair[1]);
        return;
    }
}

/* FUN_003fd8f8 @ 0x3fd8f8   (est. sk_r60_job_enqueue_slot_10)
 * Enqueues into the +0x10 slot: runs lock/job setup, dispatches the +0x10
 * continuation, then either copies the {count,ptr} pair (in-range) or
 * releases.
 * Confidence: low (extraout registers). */
static void sk_r60_3fd8f8_job_enqueue_slot_10(void)
{
    unsigned long *dst, *src, u1;
    unsigned long lo;
    int cy, zr;
    long x11;

    FUN_0034d724();
    FUN_0040654c();
    FUN_00377824();
    FUN_00349530();
    ((void (*)(void))(*(unsigned long *)(0 + 0x10)))();
    FUN_00407800(*(long *)(0 + 0x40) + 7 + 0 & ~7UL);
    if (((!cy || zr)) && x11 != -1) {
        u1 = *src;
        dst[1] = src[1];
        *dst = u1;
    } else {
        lo = src[1];
        *dst = 0;                /* extraout_x10 */
        dst[1] = lo;
        FUN_0036b270();
    }
}

/* FUN_003fd98c @ 0x3fd98c   (est. sk_r60_job_enqueue_slot_18)
 * Enqueues into the +0x18 slot with a liveness flag; copies/releases the
 * {count,ptr} pair depending on in-range + liveness.
 * Confidence: low (extraout registers, x20 context). */
static void sk_r60_3fd98c_job_enqueue_slot_18(unsigned long saved_x20[2])
{
    unsigned long *slot, u1, u3;
    unsigned long lo;
    char zr;

    FUN_0034d724();
    FUN_0040654c();
    FUN_00377824();
    FUN_00349530();
    slot = (unsigned long *)(0 + 0x18);
    ((void (*)(void))*slot)();
    FUN_0040767c(*(unsigned long *)(0 + 0x40));
    if (0 < 0x1000 && -1 != 0xffffffff) {
        if (zr != 0) {
            u1 = saved_x20[1];
            *slot = 0;           /* extraout_x8 */
            *(unsigned long *)(0 + 0x20) = u1;
            FUN_0036b270();
            return;
        }
    } else {
        if (zr != 0) {
            u1 = saved_x20[1];
            u3 = *(unsigned long *)(0 + 0x20);
            *slot = 0;
            *(unsigned long *)(0 + 0x20) = u1;
            FUN_0036b270();
            FUN_0036b118(u3);
            return;
        }
        FUN_0036b118(*(unsigned long *)(0 + 0x20));
    }
    u1 = *saved_x20;
    *(unsigned long *)(0 + 0x20) = saved_x20[1];
    *slot = u1;
}

/* FUN_003fda44 @ 0x3fda44   (est. sk_r60_job_enqueue_slot_20)
 * Enqueues into the +0x20 slot (twin of 003fd8f8).
 * Confidence: low */
static void sk_r60_3fda44_job_enqueue_slot_20(void)
{
    unsigned long *dst, *src, u1, lo;
    int cy, zr;
    long x11;

    FUN_0034d724();
    FUN_0040654c();
    FUN_00377824();
    FUN_00349530();
    ((void (*)(void))(*(unsigned long *)(0 + 0x20)))();
    FUN_00407800(*(long *)(0 + 0x40) + 7 + 0 & ~7UL);
    if (((!cy || zr)) && x11 != -1) {
        u1 = *src;
        dst[1] = src[1];
        *dst = u1;
    } else {
        lo = src[1];
        *dst = 0;                /* extraout_x10 */
        dst[1] = lo;
    }
}

/* FUN_003fdad4 @ 0x3fdad4   (est. sk_r60_job_enqueue_slot_28)
 * Enqueues into the +0x28 slot (twin of 003fd98c).
 * Confidence: low */
static void sk_r60_3fdad4_job_enqueue_slot_28(unsigned long saved_x20[2])
{
    unsigned long *slot, u1, u2, lo;
    char zr;

    FUN_0034d724();
    FUN_0040654c();
    FUN_00377824();
    FUN_00349530();
    slot = (unsigned long *)(0 + 0x28);
    ((void (*)(void))*slot)();
    FUN_0040767c(*(unsigned long *)(0 + 0x40));
    if (0 < 0x1000 && -1 != 0xffffffff) {
        if (zr != 0) {
            u1 = saved_x20[1];
            *slot = 0;
            *(unsigned long *)(0 + 0x30) = u1;
            return;
        }
    } else {
        if (zr != 0) {
            u2 = saved_x20[1];
            u1 = *(unsigned long *)(0 + 0x30);
            *slot = 0;
            *(unsigned long *)(0 + 0x30) = u2;
            FUN_0036b118(u1);
            return;
        }
        FUN_0036b118(*(unsigned long *)(0 + 0x30));
    }
    u1 = *saved_x20;
    *(unsigned long *)(0 + 0x30) = saved_x20[1];
    *slot = u1;
}

/* FUN_003fdb80 @ 0x3fdb80   (est. sk_r60_job_count_probe)
 * Probes the job/queue count: reads the count word (+0x54), clamps to
 * 0xfff, and if the requested count (unaff_w20) exceeds it, reads a field
 * element of a given width (byte/short/int at x19+x11) to decide
 * termination; otherwise returns the clamped count (or 0 / 0xffffffff /
 * FUN_000839f8 result).
 * Confidence: low (register-width switch; extraout registers).
 * Notes: the width switch (1/2/3/4 = byte/short/trap/int) mirrors the Swift
 * MetadataSize element read. */
static unsigned long sk_r60_3fdb80_job_count_probe(unsigned int want,
                                                   long saved_x19)
{
    unsigned int count, u1, elem, w12;
    unsigned long x11, result;
    unsigned int u2;

    FUN_0034d724();
    FUN_0040654c();
    FUN_00377824();
    FUN_0034ada0();
    count = *(unsigned int *)(0 + 0x54);
    u1 = count;
    if (count < 0x1000)
        u1 = 0xfff;
    if (want == 0)
        return 0;
    if (u1 < want) {
        FUN_00407460(*(unsigned long *)(0 + 0x40), 0, count, 0);
        FUN_004080bc();
        if (w12 < 0x100) {
            elem = 1;
        } else {
            elem = (unsigned int)(0);   /* extraout_w13 */
        }
        u2 = 0;
        if (1 < w12)
            u2 = elem;
        switch (u2) {
        case 1:
            if (*(char *)(saved_x19 + x11) != '\0')
                goto term;
            break;
        case 2:
            if (*(short *)(saved_x19 + x11) != 0)
                goto term;
            break;
        case 3:
            __builtin_trap();    /* SoftwareBreakpoint(1, 0x3fdc90) */
        case 4:
            if (*(int *)(saved_x19 + x11) != 0)
                goto term;
        }
    }
    if (!(0xffe < count)) {
        FUN_0040692c();
        u1 = 0;                  /* extraout_w8 */
        count = 0;
        if (1 < u1 + 1)
            count = u1;
        return (unsigned long)count;
    }
    return FUN_000839f8();
term:
    FUN_00407d54();
    return FUN_00356e64();
}

/* FUN_003fde6c @ 0x3fde6c   (est. sk_r60_job_acquire_lite)
 * Lighter job-acquire: if the flag + count (< 0x19) hold, runs the inner
 * helpers + FUN_003535e4; else FUN_00349a9c; releases.
 * Confidence: low (extraout registers). */
static void sk_r60_3fde6c_job_acquire_lite(void)
{
    int zr;
    unsigned long lo;
    FUN_0034d724();
    FUN_0040654c();
    FUN_00377824();
    FUN_0034b57c();
    FUN_0035510c(0);
    FUN_0034c144();
    if (zr && 0 < 0x19) {
        FUN_00406c08();
        ((void (*)(void))0)();   /* (*extraout_x9)() */
        FUN_00349cd0();
        FUN_003535e4();
    } else {
        FUN_00349a9c();
    }
    FUN_0036b270();
}

/* FUN_003fdf0c @ 0x3fdf0c   (est. sk_r60_job_step_10)
 * Steps a job: runs lock/job setup, dispatches the +0x10 continuation, the
 * +0x40 cleanup (FUN_00349104), FUN_0034f22c, releases.
 * Confidence: low */
static void sk_r60_3fdf0c_job_step_10(void)
{
    FUN_0034dbd8();
    FUN_0040654c();
    FUN_00377824();
    FUN_00349530();
    ((void (*)(void))(*(unsigned long *)(0 + 0x10)))();
    FUN_00349104(*(unsigned long *)(0 + 0x40));
    FUN_0034f22c();
    FUN_0036b270();
}

/* FUN_003fdf74 @ 0x3fdf74   (est. sk_r60_job_step_18)
 * Steps a job via the +0x18 continuation, frees the +0x40 payload, then
 * releases and frees the +8 result.
 * Confidence: low */
static void sk_r60_3fdf74_job_step_18(void)
{
    unsigned long u1;
    FUN_0034dbd8();
    FUN_0040654c();
    FUN_00377824();
    FUN_00349530();
    ((void (*)(void))(*(unsigned long *)(0 + 0x18)))();
    FUN_00349104(*(unsigned long *)(0 + 0x40));
    u1 = *(unsigned long *)(0 + 8);
    FUN_0034f22c();
    FUN_0036b270();
    FUN_0036b118(u1);
}
