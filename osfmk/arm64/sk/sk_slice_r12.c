/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel, GL1,
 * arm64e, image base 0) — the cL4 microkernel. Ground truth: Ghidra FUN_ names +
 * addresses in the cl4_kernel.raw program. Names use seL4/cL4 vocabulary; all
 * are estimates unless string/header matched.
 *
 * Slice 0x003fac14-0x003fdf74 (worker SKR12): the Swift Concurrency runtime and
 * VAS-core-operation machinery linked into the cL4 kernel. The Swift portions
 * are the task-executor/teardown stubs (which trap with "There is no executor
 * implementation" / "swift_task_enqueueMainExecutor" — see findings) and the
 * tagged-pointer field-offset accessors over Swift type metadata; the VAS
 * portions are the region-operation setup/teardown paths that build a
 * per-operation frame and drive it through a vtable.
 */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "sk_internal.h"

/* ------------------------------------------------------------------ *
 * Hardware / intrinsic helpers (same semantics as the Ghidra pseudo-ops
 * used in the decompiles).
 * ------------------------------------------------------------------ */
typedef void (*code)(void);   /* Ghidra "code *" — unspecified-args function ptr */

/* Ghidra renders a non-returning `brk` as `pcVar = SoftwareBreakpoint(n, pc);
 * (*pcVar)();`.  We collapse that to a single trapping call (never returns). */
static inline void *sk_brk_noret(void) __attribute__((noreturn));
static inline void *sk_brk_noret(void)
{
    __asm__ volatile("brk #1");
    __builtin_unreachable();
}
#define SoftwareBreakpoint(a, b) sk_brk_noret()

/* Stack canary slot value used by every guarded epilogue in this region. */
#define SK_CANARY (-0x2c8502b44bfffed6LL)

/* ------------------------------------------------------------------ *
 * Shared globals referenced by this slice (image-base addresses are the
 * Ghidra ground truth).
 * ------------------------------------------------------------------ */
extern uint64_t sk_g_00405fa0;          /* DAT_00405fa0 */
extern uint64_t sk_g_004e8268;          /* DAT_004e8268 */
extern uint64_t sk_g_005a0030;          /* DAT_005a0030 */
extern uint64_t sk_g_005a0034;          /* DAT_005a0034 */
extern uint64_t sk_g_005a0134;          /* DAT_005a0134 */
extern uint64_t sk_g_005a014c;          /* DAT_005a014c */
extern uint64_t sk_g_005a1328;          /* DAT_005a1328 */
extern uint64_t sk_g_005a1398;          /* DAT_005a1398 */
extern uint64_t sk_g_005a16a8;          /* DAT_005a16a8 */
extern uint64_t sk_g_005a16d8;          /* DAT_005a16d8 */
extern uint64_t sk_g_00614a5c;          /* DAT_00614a5c */
extern uint64_t sk_g_00658c80;          /* DAT_00658c80 */
extern uint64_t sk_g_006adf38;          /* DAT_006adf38 */
extern uint64_t sk_g_006adf40;          /* DAT_006adf40 */
extern uint64_t sk_g_006adf50;          /* DAT_006adf50 */
extern uint64_t sk_g_006adf58;          /* DAT_006adf58 */
extern uint64_t sk_g_006c0b50;          /* DAT_006c0b50 */
extern uint64_t sk_g_006c0b78;          /* DAT_006c0b78 */

/* ------------------------------------------------------------------ *
 * Out-of-slice cL4 helper declarations.  Bodies are reconstructed by the
 * range worker that owns each address; here they are declared extern with
 * an unspecified-arg prototype (Ghidra FUN_<addr> is the ground truth).
 * Functions that carry a 16-byte {lo,hi} return pair are typed cl4_result_t.
 * ------------------------------------------------------------------ */
extern cl4_result_t sk_x_00002534();   /* FUN_00002534 */
extern unsigned long sk_x_00002688();   /* FUN_00002688 */
extern unsigned long sk_x_000026e8();   /* FUN_000026e8 */
extern unsigned long sk_x_00019858();   /* FUN_00019858 */
extern unsigned long sk_x_00021480();   /* FUN_00021480 */
extern unsigned long sk_x_00027724();   /* FUN_00027724 */
extern unsigned long sk_x_0006a4c0();   /* FUN_0006a4c0 */
extern unsigned long sk_x_0006a4f0();   /* FUN_0006a4f0 */
extern unsigned long sk_x_0006a668();   /* FUN_0006a668 */
extern unsigned long sk_x_0006b6f4();   /* FUN_0006b6f4 */
extern unsigned long sk_x_00077888();   /* FUN_00077888 */
extern unsigned long sk_x_0007c028();   /* FUN_0007c028 */
extern unsigned long sk_x_0007c1a4();   /* FUN_0007c1a4 */
extern unsigned long sk_x_000839f8();   /* FUN_000839f8 */
extern unsigned long sk_x_0008409c();   /* FUN_0008409c */
extern unsigned long sk_x_00084180();   /* FUN_00084180 */
extern unsigned long sk_x_0008e0d4();   /* FUN_0008e0d4 */
extern unsigned long sk_x_0008e500();   /* FUN_0008e500 */
extern cl4_result_t sk_x_0008e518();   /* FUN_0008e518 */
extern unsigned long sk_x_000a68c4();   /* FUN_000a68c4 */
extern unsigned long sk_x_000a6f88();   /* FUN_000a6f88 */
extern unsigned long sk_x_000aa4ec();   /* FUN_000aa4ec */
extern cl4_result_t sk_x_000b4390();   /* FUN_000b4390 */
extern unsigned long sk_x_000bd3a4();   /* FUN_000bd3a4 */
extern unsigned long sk_x_000dbd0c();   /* FUN_000dbd0c */
extern unsigned long sk_x_000e15d8();   /* FUN_000e15d8 */
extern unsigned long sk_x_00100efc();   /* FUN_00100efc */
extern unsigned long sk_x_0011d7e8();   /* FUN_0011d7e8 */
extern unsigned long sk_x_001a5968();   /* FUN_001a5968 */
extern unsigned long sk_x_001a67bc();   /* FUN_001a67bc */
extern unsigned long sk_x_001a84f4();   /* FUN_001a84f4 */
extern unsigned long sk_x_001a8564();   /* FUN_001a8564 */
extern unsigned long sk_x_001a8b7c();   /* FUN_001a8b7c */
extern unsigned long sk_x_001afa84();   /* FUN_001afa84 */
extern unsigned long sk_x_001afe4c();   /* FUN_001afe4c */
extern unsigned long sk_x_001bdb28();   /* FUN_001bdb28 */
extern unsigned long sk_x_001bea18();   /* FUN_001bea18 */
extern unsigned long sk_x_001edad0();   /* FUN_001edad0 */
extern unsigned long sk_x_001ee018();   /* FUN_001ee018 */
extern unsigned long sk_x_001fcefc();   /* FUN_001fcefc */
extern unsigned long sk_x_00208418();   /* FUN_00208418 */
extern unsigned long sk_x_002298d4();   /* FUN_002298d4 */
extern unsigned long sk_x_002a0cf8();   /* FUN_002a0cf8 */
extern unsigned long sk_x_002acbb8();   /* FUN_002acbb8 */
extern cl4_result_t sk_x_002d3c28();   /* FUN_002d3c28 */
extern unsigned long sk_x_002d4a64();   /* FUN_002d4a64 */
extern unsigned long sk_x_002d738c();   /* FUN_002d738c */
extern unsigned long sk_x_00310d34();   /* FUN_00310d34 */
extern unsigned long sk_x_00310d68();   /* FUN_00310d68 */
extern unsigned long sk_x_0031945c();   /* FUN_0031945c */
extern unsigned long sk_x_003488bc();   /* FUN_003488bc */
extern unsigned long sk_x_00349104();   /* FUN_00349104 */
extern unsigned long sk_x_00349530();   /* FUN_00349530 */
extern unsigned long sk_x_00349a54();   /* FUN_00349a54 */
extern unsigned long sk_x_00349a9c();   /* FUN_00349a9c */
extern unsigned long sk_x_00349cd0();   /* FUN_00349cd0 */
extern unsigned long sk_x_00349f3c();   /* FUN_00349f3c */
extern unsigned long sk_x_0034ab10();   /* FUN_0034ab10 */
extern unsigned long sk_x_0034ab20();   /* FUN_0034ab20 */
extern unsigned long sk_x_0034ada0();   /* FUN_0034ada0 */
extern unsigned long sk_x_0034b460();   /* FUN_0034b460 */
extern unsigned long sk_x_0034b57c();   /* FUN_0034b57c */
extern unsigned long sk_x_0034c144();   /* FUN_0034c144 */
extern unsigned long sk_x_0034d724();   /* FUN_0034d724 */
extern unsigned long sk_x_0034dbd8();   /* FUN_0034dbd8 */
extern unsigned long sk_x_0034de54();   /* FUN_0034de54 */
extern unsigned long sk_x_0034f22c();   /* FUN_0034f22c */
extern unsigned long sk_x_00350470();   /* FUN_00350470 */
extern unsigned long sk_x_003504a0();   /* FUN_003504a0 */
extern unsigned long sk_x_003504ac();   /* FUN_003504ac */
extern unsigned long sk_x_003504d0();   /* FUN_003504d0 */
extern unsigned long sk_x_003504e8();   /* FUN_003504e8 */
extern unsigned long sk_x_00350500();   /* FUN_00350500 */
extern unsigned long sk_x_00350518();   /* FUN_00350518 */
extern unsigned long sk_x_00350524();   /* FUN_00350524 */
extern unsigned long sk_x_0035053c();   /* FUN_0035053c */
extern unsigned long sk_x_00350548();   /* FUN_00350548 */
extern unsigned long sk_x_00350560();   /* FUN_00350560 */
extern unsigned long sk_x_00350618();   /* FUN_00350618 */
extern unsigned long sk_x_00350624();   /* FUN_00350624 */
extern unsigned long sk_x_00350720();   /* FUN_00350720 */
extern unsigned long sk_x_00350884();   /* FUN_00350884 */
extern unsigned long sk_x_00350968();   /* FUN_00350968 */
extern unsigned long sk_x_0035098c();   /* FUN_0035098c */
extern unsigned long sk_x_003509ec();   /* FUN_003509ec */
extern unsigned long sk_x_00350a64();   /* FUN_00350a64 */
extern unsigned long sk_x_00350b54();   /* FUN_00350b54 */
extern unsigned long sk_x_0035128c();   /* FUN_0035128c */
extern unsigned long sk_x_003513b4();   /* FUN_003513b4 */
extern unsigned long sk_x_003515b4();   /* FUN_003515b4 */
extern unsigned long sk_x_00351790();   /* FUN_00351790 */
extern unsigned long sk_x_00351a68();   /* FUN_00351a68 */
extern unsigned long sk_x_00351e3c();   /* FUN_00351e3c */
extern unsigned long sk_x_00351f10();   /* FUN_00351f10 */
extern unsigned long sk_x_00352018();   /* FUN_00352018 */
extern unsigned long sk_x_00352ae4();   /* FUN_00352ae4 */
extern unsigned long sk_x_00353cfc();   /* FUN_00353cfc */
extern unsigned long sk_x_00353d14();   /* FUN_00353d14 */
extern unsigned long sk_x_003535e4();   /* FUN_003535e4 */
extern unsigned long sk_x_0035510c();   /* FUN_0035510c */
extern unsigned long sk_x_003561f4();   /* FUN_003561f4 */
extern unsigned long sk_x_00356e64();   /* FUN_00356e64 */
extern unsigned long sk_x_003593c0();   /* FUN_003593c0 */
extern unsigned long sk_x_0035ac70();   /* FUN_0035ac70 */
extern unsigned long sk_x_0036a9a0();   /* FUN_0036a9a0 */
extern unsigned long sk_x_0036a940();   /* FUN_0036a940 */
extern unsigned long sk_x_0036b118();   /* FUN_0036b118 */
extern unsigned long sk_x_0036b270();   /* FUN_0036b270 */
extern unsigned long sk_x_0036b2d0();   /* FUN_0036b2d0 */
extern unsigned long sk_x_0036b588();   /* FUN_0036b588 */
extern unsigned long sk_x_0036b6ac();   /* FUN_0036b6ac */
extern unsigned long sk_x_00376820();   /* FUN_00376820 */
extern unsigned long sk_x_00377824();   /* FUN_00377824 */
extern unsigned long sk_x_00377bec();   /* FUN_00377bec */
extern unsigned long sk_x_0039a128();   /* FUN_0039a128 */
extern unsigned long sk_x_003a25d4();   /* FUN_003a25d4 */
extern unsigned long sk_x_003d4e84();   /* FUN_003d4e84 */
extern unsigned long sk_x_003d4f18();   /* FUN_003d4f18 */
extern unsigned long sk_x_003d50cc();   /* FUN_003d50cc */
extern unsigned long sk_x_003e33d8();   /* FUN_003e33d8 */
extern cl4_result_t sk_x_003ed340();   /* FUN_003ed340 */
extern unsigned long sk_x_003ed5f8();   /* FUN_003ed5f8 */
extern unsigned long sk_x_003eebf0();   /* FUN_003eebf0 */
extern unsigned long sk_x_003f4e84();   /* FUN_003f4e84 */
extern unsigned long sk_x_003f5060();   /* FUN_003f5060 */
extern unsigned long sk_x_003f539c();   /* FUN_003f539c */
extern unsigned long sk_x_003f6a0c();   /* FUN_003f6a0c */
extern unsigned long sk_x_003f79d8();   /* FUN_003f79d8 */
extern cl4_result_t sk_x_003f761c();   /* FUN_003f761c */
extern unsigned long sk_x_003f7648();   /* FUN_003f7648 */
extern unsigned long sk_x_003f97bc();   /* FUN_003f97bc */
extern unsigned long sk_x_003f9bdc();   /* FUN_003f9bdc */
extern unsigned long sk_x_004040a8();   /* FUN_004040a8 */
extern unsigned long sk_x_00404900();   /* FUN_00404900 */
extern unsigned long sk_x_00404b8c();   /* FUN_00404b8c */
extern unsigned long sk_x_00404cf4();   /* FUN_00404cf4 */
extern unsigned long sk_x_00406478();   /* FUN_00406478 */
extern unsigned long sk_x_0040654c();   /* FUN_0040654c */
extern unsigned long sk_x_0040692c();   /* FUN_0040692c */
extern unsigned long sk_x_00406a10();   /* FUN_00406a10 */
extern unsigned long sk_x_00406c08();   /* FUN_00406c08 */
extern unsigned long sk_x_00406c3c();   /* FUN_00406c3c */
extern unsigned long sk_x_00406d60();   /* FUN_00406d60 */
extern unsigned long sk_x_00406eb0();   /* FUN_00406eb0 */
extern unsigned long sk_x_00406fd4();   /* FUN_00406fd4 */
extern unsigned long sk_x_00406fe0();   /* FUN_00406fe0 */
extern unsigned long sk_x_0040700c();   /* FUN_0040700c */
extern unsigned long sk_x_00407030();   /* FUN_00407030 */
extern unsigned long sk_x_00407048();   /* FUN_00407048 */
extern unsigned long sk_x_004070c0();   /* FUN_004070c0 */
extern unsigned long sk_x_004070d8();   /* FUN_004070d8 */
extern unsigned long sk_x_00407134();   /* FUN_00407134 */
extern unsigned long sk_x_004072c0();   /* FUN_004072c0 */
extern unsigned long sk_x_00407460();   /* FUN_00407460 */
extern unsigned long sk_x_00407568();   /* FUN_00407568 */
extern unsigned long sk_x_004075ec();   /* FUN_004075ec */
extern unsigned long sk_x_0040767c();   /* FUN_0040767c */
extern unsigned long sk_x_004076a8();   /* FUN_004076a8 */
extern unsigned long sk_x_00407800();   /* FUN_00407800 */
extern unsigned long sk_x_0040790c();   /* FUN_0040790c */
extern unsigned long sk_x_00407924();   /* FUN_00407924 */
extern unsigned long sk_x_004079f4();   /* FUN_004079f4 */
extern unsigned long sk_x_00407ab8();   /* FUN_00407ab8 */
extern unsigned long sk_x_00407ac4();   /* FUN_00407ac4 */
extern unsigned long sk_x_00407b80();   /* FUN_00407b80 */
extern unsigned long sk_x_00407d54();   /* FUN_00407d54 */
extern unsigned long sk_x_00407d74();   /* FUN_00407d74 */
extern unsigned long sk_x_00407d90();   /* FUN_00407d90 */
extern unsigned long sk_x_00407e3c();   /* FUN_00407e3c */
extern unsigned long sk_x_00407e88();   /* FUN_00407e88 */
extern unsigned long sk_x_00407f84();   /* FUN_00407f84 */
extern unsigned long sk_x_00408044();   /* FUN_00408044 */
extern unsigned long sk_x_00408058();   /* FUN_00408058 */
extern unsigned long sk_x_004080bc();   /* FUN_004080bc */
extern unsigned long sk_x_004080b0();   /* FUN_004080b0 */
extern unsigned long sk_x_00408160();   /* FUN_00408160 */
extern unsigned long sk_x_00408178();   /* FUN_00408178 */
extern unsigned long sk_x_00408190();   /* FUN_00408190 */
extern unsigned long sk_x_00408258();   /* FUN_00408258 */
extern unsigned long sk_x_0040841c();   /* FUN_0040841c */
extern unsigned long sk_x_00408434();   /* FUN_00408434 */
extern unsigned long sk_x_0040859c();   /* FUN_0040859c */
extern unsigned long sk_x_00409248();   /* FUN_00409248 */
extern unsigned long sk_x_004092d8();   /* FUN_004092d8 */
extern cl4_result_t sk_x_0040bb18();   /* FUN_0040bb18 */
extern unsigned long sk_x_004ba7ec();   /* FUN_004ba7ec */

/* String literals referenced by the Swift-runtime fatal stubs (Ghidra refs). */
extern const char sk_str_no_executor[];      /* s_There_is_no_executor_implementat_005dc2e0 */
extern const char sk_str_unimpl_executor[];  /* s__Concurrency_UnimplementedExecut_005dc2b0 */
extern const char sk_str_enqueue_main_exec[];/* s_swift_task_enqueueMainExecutor___005dc330 */

/* ================================================================== *
 * 0x003fac14 - 0x003fbf28 : VAS/region-operation dispatch wrappers
 * ================================================================== */

/* FUN_003fac14 @ 0x003fac14  (est. sk_vas_regstore2)
 * Runs a register-pair store: calls the shared VAS op runner FUN_003f97bc with
 * (param_2, *(param_5+0x10), param_3, param_4) and writes the 16-byte result
 * word (lo) into *param_1. A thin forwarder. Confidence: medium. */
static void sk_vas_regstore2(uint64_t *out, uint64_t a, uint64_t b, uint64_t c, uint64_t ctx)
{
    uint64_t lo = sk_x_003f97bc(a, *(uint64_t *)(ctx + 0x10), b, c);
    *out = lo;
}

/* FUN_003fac4c @ 0x003fac4c  (est. sk_vas_dispatch_indirect)
 * Resumes a VAS operation: calls FUN_0008409c and FUN_003f79d8, then performs an
 * indirect call through a two-level pointer read from (x19+0x10): target =
 * (*(long *)(*(long *)(x19 + 0x10) - 8) + 8). The jump table was not recovered
 * ("Too many branches"), so the call target is not statically resolvable.
 * Confidence: low. */
static void sk_vas_dispatch_indirect(uint64_t x19)
{
    sk_x_0008409c();
    sk_x_003f79d8();
    /* Indirect call through (*(long *)(*(long *)(x19 + 0x10) - 8) + 8) —
       Ghidra could not recover the jumptable at 0x003fac9c. */
    ((code) * (long **)(*(long *)(x19 + 0x10) - 8) + 8)();
}

/* FUN_003fad94 @ 0x003fad94  (est. sk_vas_op_finish_ok)
 * Runs the VAS op finisher FUN_003fa828 and returns success (1). Confidence: high. */
static unsigned long sk_vas_op_finish_ok(void)
{
    sk_x_003fa828();
    return 1;
}

/* FUN_003fad98 @ 0x003fad98  (est. sk_vas_op_finish_ok_b)
 * Duplicate of 0x003fad94: runs FUN_003fa828 and returns success (1). Confidence: high. */
static unsigned long sk_vas_op_finish_ok_b(void)
{
    sk_x_003fa828();
    return 1;
}

/* FUN_003fadbc @ 0x003fadbc  (est. sk_vas_op_bind_args)
 * Binds VAS-op arguments: calls FUN_00407ab8/FUN_004075ec, combines with the
 * third parameter through the 16-byte helper FUN_00376820, then pushes the
 * resulting pair into FUN_001a5968. Confidence: low (16-byte plumbing). */
static void sk_vas_op_bind_args(uint64_t a, uint64_t b, uint64_t arg3)
{
    uint64_t r1 = sk_x_004075ec();
    cl4_result_t pair = sk_x_00376820(r1, arg3);
    cl4_result_t r2 = sk_x_00350618();
    sk_x_001a5968(r2.lo, r2.hi, arg3);
}

/* FUN_003fae1c @ 0x003fae1c  (est. sk_vas_region_setup_loop)
 * Drives a VAS-core operation setup/prepare loop. Opens the region, then
 * repeatedly: steps the operation iterator (FUN_003f7648/FUN_00349f3c), and for
 * each page callback fetches a page pair (FUN_000b4390) and calls a vtable
 * entry (+0x20), accumulating into a 64-byte stack work area that is flushed
 * through FUN_004070c0 (range, 0x20, ...) and finalized per-iteration. On the
 * second iteration a 0x202c/"vas_core_operation_setup..." string is emitted.
 * Falls out to FUN_0008e500 when the iterator is exhausted.
 * Reference: s_vas_core_operation_setup_and_pre_005b281e. Confidence: low
 * (register-forwarded ABI; several callee results arrive via extraout_xN). */
static void sk_vas_region_setup_loop(void)
{
    uint64_t extraout_x8  = /* extraout_x8 */ 0;
    uint64_t extraout_x8_00 = /* extraout_x8_00 */ 0;
    uint64_t extraout_x9  = /* extraout_x9 */ 0;
    uint64_t extraout_x16 = /* extraout_x16 */ 0;
    uint64_t extraout_x1  = /* extraout_x1 */ 0;
    uint64_t extraout_x1_00 = /* extraout_x1_00 */ 0;
    bool in_ZR;
    uint64_t unaff_x30 = /* unaff_x30 */ 0;
    uint64_t local_10, uStack_8;
    cl4_result_t local_28, page;
    uint64_t op = 0;

    sk_x_0008e518();
    sk_x_0007c028();
    ((void (*)(void))sk_g_00658c80)(*(uint64_t *)(extraout_x8 + 0x40));
    sk_x_000aa4ec();
    sk_x_0040841c();
    sk_x_00310d68(0);
    sk_x_00351f10();
    sk_x_0007c1a4();
    ((void (*)(void))sk_g_00658c80)();
    sk_x_0034b460();
    sk_x_00408258();
    local_28.lo = extraout_x8_00;
    local_28.hi = extraout_x9;
    sk_x_00208418(extraout_x1, 0);
    sk_x_002acbb8();
    sk_x_003a25d4(extraout_x1_00);
    sk_x_002acbb8(/* s_vas_core_operation_setup_and_pre_005b281e + 0x20 */ 0, 0xe300000000000000ULL);
    local_10 = local_28.lo;
    uStack_8 = local_28.hi;
    sk_x_00350524();
    local_28 = sk_x_003f761c();
    sk_x_003504e8();
    op = sk_x_00404b8c();
    bool first = true;
    while (true) {
        sk_x_003f7648(op);
        sk_x_00349f3c();
        if (in_ZR) break;
        code step = (code)(uintptr_t)(extraout_x16 + 0x20);
        page = sk_x_000b4390();
        ((void (*)(uint64_t, uint64_t, uint64_t))step)(page.lo, page.hi, extraout_x1);
        if (!first) {
            sk_x_002acbb8(0x202c, 0xe200000000000000ULL);
        }
        uint64_t p = sk_x_0008e0d4();
        sk_x_0036a9a0(p, /* 64-byte work area */ 0);
        sk_x_00408160();
        sk_x_003504a0();
        ((void (*)(void))step)();
        sk_x_004070c0(/* stack base */ 0, 0x20, 0xe100000000000000ULL, 0, 0, &local_10);
        sk_x_001a8b7c();
        sk_x_0036b588(/* stack base */ 0);
        p = sk_x_00002688();
        sk_x_0036b6ac(p, 0x20, 7);
        first = false;
    }
    sk_x_0036b118(local_28.lo);
    sk_x_002acbb8(0x295d, 0xe200000000000000ULL);
    sk_x_0008e500(local_10, uStack_8, unaff_x30);
}

/* FUN_003fb028 @ 0x003fb028  (est. sk_vas_op_result_build)
 * Builds a 40-byte result record into param_1 from a single input word: reads a
 * fresh pair via FUN_00404cf4/FUN_00406478, combines through FUN_00376820 and
 * FUN_0036b2d0, then FUN_003515b4 assembles the 16-byte {local_60, uStack_58}
 * and packed trailing fields into *param_1. Confidence: low (packed layout). */
static void sk_vas_op_result_build(uint64_t *out, uint64_t w)
{
    uint64_t local_70 = w, uStack_68 = w, local_60, uStack_58, uStack_50, uStack_3f;
    uint8_t uStack_48; uint64_t local_47; uint8_t uStack_40;

    uint64_t r1 = sk_x_00404cf4(0);
    uint64_t r2 = sk_x_00406478();
    sk_x_00376820(r2, r1);
    sk_x_0036b2d0(w, 2);
    sk_x_003515b4(&local_60, &uStack_68, &local_70, 5);
    sk_x_001a67bc();
    out[1] = uStack_58;
    out[0] = local_60;
    out[3] = (uint64_t)((uint64_t)uStack_48 << 56) | local_47;
    out[2] = uStack_50;
    *(uint64_t *)((uint8_t *)out + 0x21) = uStack_3f;
    *(uint64_t *)((uint8_t *)out + 0x19) = ((uint64_t)uStack_40 << 8) | (local_47 & 0xff);
}

/* FUN_003fb0bc @ 0x003fb0bc  (est. sk_vas_op_result_ctx)
 * Like FUN_003fb028 but seeds the builder with the object at x20 and the word at
 * (param_2+0x10) before copying the packed result record into param_1.
 * Confidence: low (packed layout; x20 register artifact). */
static void sk_vas_op_result_ctx(uint64_t *out, uint64_t param_2)
{
    uint64_t x20 = /* unaff_x20 */ 0;
    uint64_t local_50, uStack_48, uStack_40, uStack_2f;
    uint8_t uStack_38; uint64_t local_37; uint8_t uStack_30;

    sk_vas_op_result_build(&local_50, *(uint64_t *)(x20 + 0));
    out[1] = uStack_48;
    out[0] = local_50;
    out[3] = (uint64_t)((uint64_t)uStack_38 << 56) | local_37;
    out[2] = uStack_40;
    *(uint64_t *)((uint8_t *)out + 0x21) = uStack_2f;
    *(uint64_t *)((uint8_t *)out + 0x19) = ((uint64_t)uStack_30 << 8) | (local_37 & 0xff);
}

/* FUN_003fb108 @ 0x003fb108  (est. sk_vas_region_setup_loop_sync)
 * Sibling of FUN_003fae1c: the same VAS region-operation setup/prepare loop but
 * seeded with the sync record {0x5b, 0xe100000000000000} and a 0x5d/0x202c
 * operation tag; otherwise identical iteration structure (per-page vtable call,
 * work-area flush, iterator finalize). Confidence: low (register-forwarded ABI). */
static void sk_vas_region_setup_loop_sync(void)
{
    uint64_t extraout_x8  = /* extraout_x8 */ 0;
    uint64_t extraout_x16 = /* extraout_x16 */ 0;
    uint64_t extraout_x1  = /* extraout_x1 */ 0;
    bool in_ZR;
    uint64_t unaff_x30 = /* unaff_x30 */ 0;
    uint64_t local_10 = 0x5b, uStack_8 = 0xe100000000000000ULL;
    cl4_result_t local_28, page;
    uint64_t op;

    sk_x_0008e518();
    sk_x_0007c028();
    ((void (*)(void))sk_g_00658c80)(*(uint64_t *)(extraout_x8 + 0x40));
    sk_x_000aa4ec();
    sk_x_0040841c();
    sk_x_00310d68(0);
    sk_x_00351f10();
    sk_x_0007c1a4();
    ((void (*)(void))sk_g_00658c80)();
    sk_x_0034b460();
    sk_x_00350524();
    local_28 = sk_x_003f761c();
    sk_x_003504e8();
    op = sk_x_00404b8c();
    bool first = true;
    while (true) {
        sk_x_003f7648(op);
        sk_x_00349f3c();
        if (in_ZR) break;
        code step = (code)(uintptr_t)(extraout_x16 + 0x20);
        page = sk_x_000b4390();
        ((void (*)(uint64_t, uint64_t, uint64_t))step)(page.lo, page.hi, extraout_x1);
        if (!first) {
            sk_x_002acbb8(0x202c, 0xe200000000000000ULL);
        }
        uint64_t p = sk_x_0008e0d4();
        sk_x_0036a9a0(p, /* work area */ 0);
        sk_x_00408160();
        sk_x_003504a0();
        ((void (*)(void))step)();
        sk_x_004070c0(0, 0x20, 0xe100000000000000ULL, 0, 0, &local_10);
        sk_x_001edad0();
        sk_x_0036b588(0);
        p = sk_x_00002688();
        sk_x_0036b6ac(p, 0x20, 7);
        first = false;
    }
    sk_x_0036b118(local_28.lo);
    sk_x_002acbb8(0x5d, 0xe100000000000000ULL);
    sk_x_0008e500(local_10, uStack_8, unaff_x30);
}

/* FUN_003fb2e0 @ 0x003fb2e0  (est. sk_vas_cmp)
 * Compares two words: calls the shared VAS compare FUN_001fcefc with the packed
 * local pair {param_2, param_1}, two copies of FUN_00404cf4() and the two type
 * tags 0x67f270, returning bit0 of the result. Confidence: medium. */
static unsigned int sk_vas_cmp(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4)
{
    uint64_t local_30 = p2, uStack_28 = p1;
    sk_x_00350a64();
    uint64_t w = sk_x_00404cf4();
    unsigned int r = sk_x_001fcefc(&local_30, w, w, 0x67f270, 0x67f270, p4);
    return r & 1;
}

/* FUN_003fb360 @ 0x003fb360  (est. sk_vas_op_setup3)
 * Sets up a 3-operand VAS op: calls FUN_00310d34(0), combines the metadata
 * DAT_004e8268 with it through FUN_00376820, then FUN_00350968 dispatches with
 * the local/param_3 and the returned pair; finishes with FUN_003f9bdc.
 * Confidence: low (16-byte pair plumbing). */
static void sk_vas_op_setup3(uint64_t p1, uint64_t p2, uint64_t p3)
{
    uint64_t local_28 = p1;
    uint64_t w = sk_x_00310d34(0);
    cl4_result_t pair = sk_x_00376820(&sk_g_004e8268, w);
    sk_x_00350968(&local_28, pair.hi, p3, pair.lo);
    sk_x_003f9bdc();
}

/* FUN_003fb3c4 @ 0x003fb3c4  (est. sk_vas_op_setup3_store)
 * Runs FUN_003fb360 with (param_2, *(param_3+0x10)) and stores the result into
 * *param_1. Thin forwarder. Confidence: medium. */
static void sk_vas_op_setup3_store(uint64_t *out, uint64_t p2, uint64_t p3)
{
    uint64_t r = sk_x_003fb360(p2, *(uint64_t *)(p3 + 0x10));
    *out = r;
}

/* FUN_003fb3f0 @ 0x003fb3f0  (est. sk_vas_op_iterate)
 * Iterates a VAS operation to completion: opens the region, seeds a work pair
 * via FUN_003f761c/FUN_00404b8c, then loops stepping FUN_003f7648/FUN_00350884;
 * for each element pulls a pair from FUN_00350470 (vtable +0x20), calls it,
 * classifies via FUN_0031945c/FUN_003504a0, and releases via FUN_00350560.
 * Finalizes the pair and falls to FUN_0008e500. Confidence: low
 * (register-forwarded ABI; jumptable at 0x003fb450 not recovered). */
static void sk_vas_op_iterate(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4)
{
    bool in_ZR;
    uint64_t extraout_x8  = /* extraout_x8 */ 0;
    uint64_t extraout_x16 = /* extraout_x16 */ 0;
    uint64_t unaff_x30 = /* unaff_x30 */ 0;
    cl4_result_t seed, elt;

    seed = sk_x_0008e518();
    sk_x_0007c028();
    ((void (*)(void))sk_g_00658c80)(*(uint64_t *)(extraout_x8 + 0x40));
    sk_x_000aa4ec();
    sk_x_00350a64();
    sk_x_00310d68();
    sk_x_00351f10();
    sk_x_0007c1a4();
    ((void (*)(void))sk_g_00658c80)();
    sk_x_00407b80();
    sk_x_003f539c(seed.hi, p3);
    sk_x_002298d4();
    uint64_t it = sk_x_003f761c(seed.hi, p3);
    uint64_t ctx = sk_x_00404b8c(0, p3);
    while (true) {
        sk_x_003f7648(ctx);
        sk_x_00350884();
        if (in_ZR) break;
        elt = sk_x_00350470(*(uint64_t *)(extraout_x16 + 0x20));
        ((void (*)(uint64_t, uint64_t, uint64_t))(uintptr_t)(extraout_x8))(elt.lo, elt.hi, p3);
        uint64_t v = sk_x_0031945c(p4);
        sk_x_003504a0(v, seed.lo);
        ((void (*)(void))(uintptr_t)(extraout_x8))();
        sk_x_00350560(*(uint64_t *)(extraout_x16 + 8));
        ((void (*)(void))(uintptr_t)(extraout_x8))();
    }
    sk_x_0036b118(it);
    sk_x_0008e500(unaff_x30);
}

/* FUN_003fb56c @ 0x003fb56c  (est. sk_vas_op_run0)
 * Runs a zero-argument VAS op: after the common preamble (FUN_0035098c /
 * FUN_004080b0 / FUN_00350548 into a 72-byte frame) it calls FUN_003fb3f0 then
 * FUN_001a8564. Confidence: medium. */
static void sk_vas_op_run0(void)
{
    uint8_t frame[72];
    sk_x_0035098c();
    sk_x_004080b0();
    sk_x_00350548(frame);
    sk_vas_op_iterate(0, 0, 0, 0);
    sk_x_001a8564();
}

/* FUN_003fb5ec @ 0x003fb5ec  (est. sk_vas_op_run1)
 * Runs a one-argument VAS op: reads a value from a tagged pointer
 * ((param_3 & ~1) - 8), seeds a 72-byte frame via FUN_001a84f4/FUN_003fb3f0 and
 * finishes with FUN_001a8564. Confidence: low (x20 register artifact). */
static void sk_vas_op_run1(uint64_t p1, uint64_t p2, uint64_t p3)
{
    uint64_t x20 = /* unaff_x20 */ 0;
    uint8_t frame[72];
    uint64_t v = *(uint64_t *)((p3 & 0xfffffffffffffffeULL) - 8);
    sk_x_001a84f4(frame);
    sk_vas_op_iterate(frame, *(uint64_t *)(x20 + 0), *(uint64_t *)(p2 + 0x10), v);
    sk_x_001a8564();
}

/* FUN_003fb648 @ 0x003fb648  (est. sk_vas_op_run2_cond)
 * Conditional two-branch VAS op: computes a range length (extraout_x9 - x12) and
 * a remainder, then either (when x21 == 0) runs a full teardown path that
 * rebuilds the op pair (FUN_00350618/FUN_00377bec) and invokes the op runner
 * FUN_003fd3fc with the saved args, or (else) just dispatches through vtable
 * entry +8. Releases the op context via FUN_00353d14 at the end.
 * Confidence: low (register-forwarded ABI; jumptable at 0x003fb644 not recovered). */
static void sk_vas_op_run2_cond(void)
{
    uint64_t extraout_x8  = /* extraout_x8 */ 0;
    uint64_t extraout_x16 = /* extraout_x16 */ 0;
    uint64_t extraout_x9  = /* extraout_x9 */ 0;
    uint64_t extraout_x12 = /* extraout_x12 */ 0;
    uint64_t extraout_x12_00 = /* extraout_x12_00 */ 0;
    uint64_t in_x3 = /* in_x3 */ 0;
    uint64_t x21 = /* unaff_x21 */ 0;
    uint64_t x30 = /* unaff_x30 */ 0;
    cl4_result_t pair;
    code open  = (code)(uintptr_t)sk_x_00353cfc();
    sk_x_00408434();
    sk_x_00350720();
    uint64_t k = sk_x_00377824();
    sk_x_000a6f88();
    ((void (*)(void))sk_g_00658c80)(*(uint64_t *)(extraout_x8 + 0x40));
    sk_x_0034ab10();
    uint64_t len = extraout_x9 - extraout_x12;
    ((void (*)(void))sk_g_00658c80)();
    uint64_t len2 = len - extraout_x12_00;
    code run = (code)(uintptr_t)sk_x_000a68c4(in_x3);
    sk_x_000dbd0c(len2);
    ((void (*)(void))run)();
    ((void (*)(void))open)();
    if (x21 == 0) {
        sk_x_000dbd0c(len);
        ((void (*)(void))run)();
        sk_x_00408434();
        pair = sk_x_00350618();
        uint64_t v = sk_x_00377bec(pair.lo, pair.hi, k);
        code op = (code)(uintptr_t)sk_x_003fd3fc();
        ((void (*)(uint64_t, uint64_t, uint64_t, uint64_t))op)(extraout_x8, len, k, v);
        code tail = (code)(uintptr_t)(extraout_x16 + 8);
        sk_x_00350524();
        ((void (*)(void))tail)();
        ((void (*)(uint64_t, uint64_t))tail)(len2, k);
    } else {
        ((void (*)(uint64_t, uint64_t))(uintptr_t)(extraout_x16 + 8))(len2, k);
    }
    sk_x_00353d14(x30);
}

/* FUN_003fb7dc @ 0x003fb7dc  (est. sk_vas_op_frame_push)
 * Allocates and initialises a VAS op frame: stores the incoming registers and a
 * fresh pair into the frame at x22 (+0x10..+0x50), allocates a stack chunk via
 * FUN_0040bb18 (0xfff0-aligned), links it back to the frame, and sets its
 * return address to 0x003fb91c before an unrecovered indirect jump (0x003fb918)
 * into the op runner. Confidence: low (register-forwarded ABI; jumptable not
 * recovered). */
static void sk_vas_op_frame_push(void)
{
    uint64_t extraout_x8  = /* extraout_x8 */ 0;
    uint64_t extraout_x9  = /* extraout_x9 */ 0;
    uint64_t extraout_x16 = /* extraout_x16 */ 0;
    uint64_t in_x3 = /* in_x3 */ 0, in_x4 = /* in_x4 */ 0;
    uint64_t x20 = /* unaff_x20 */ 0, x22 = /* unaff_x22 */ 0;
    uint64_t x25 = /* unaff_x25 */ 0, x30 = /* unaff_x30 */ 0;
    int *x21 = /* unaff_x21 */ 0;
    cl4_result_t pair;

    sk_x_0040790c();
    sk_x_004070d8();
    uint64_t r1 = in_x3, r2 = in_x4;
    uint64_t w = sk_x_00350b54();
    *(uint64_t *)(x22 + 0x20) = r2;
    *(uint64_t *)(x22 + 0x28) = x20;
    *(uint64_t *)(x22 + 0x10) = w;
    *(uint64_t *)(x22 + 0x18) = r1;
    sk_x_00408434();
    pair = sk_x_00350500();
    uint64_t v = sk_x_00377824(pair.lo, pair.hi, in_x3);
    *(uint64_t *)(x22 + 0x30) = v;
    sk_x_00352018();
    *(uint64_t *)(x22 + 0x38) = extraout_x16;
    uint64_t p = sk_x_0040859c(*(uint64_t *)(extraout_x8 + 0x40));
    *(uint64_t *)(x22 + 0x40) = p;
    uint64_t chunk = sk_x_0040bb18(x25 & 0xfffffffffffffff0ULL);
    *(uint64_t *)(x22 + 0x48) = chunk;
    uint64_t r4 = sk_x_000a68c4(in_x4);
    *(uint64_t *)(x22 + 0x50) = r4;
    sk_x_00350518(chunk);
    ((void (*)(void))(uintptr_t)extraout_x9)();
    int cnt = *x21;
    long *sl = (long *)sk_x_0040bb18(x21[1]);
    *(long **)(x22 + 0x58) = sl;
    sl[0] = (long)x22;
    sl[1] = (long)0x003fb91c;  /* LAB_003fb91c */
    code jump = (code)(uintptr_t)sk_x_004080cc(sl + 1, (long)x21 + cnt, x30);
    /* Unrecovered jumptable at 0x003fb918 — indirect call into op runner. */
    ((void (*)(void))jump)();
}
