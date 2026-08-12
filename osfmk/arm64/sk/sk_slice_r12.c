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
extern cl4_result_t sk_x_00350470();   /* FUN_00350470 */
extern unsigned long sk_x_003504a0();   /* FUN_003504a0 */
extern cl4_result_t sk_x_003504ac();   /* FUN_003504ac */
extern unsigned long sk_x_003504d0();   /* FUN_003504d0 */
extern unsigned long sk_x_003504e8();   /* FUN_003504e8 */
extern cl4_result_t sk_x_00350500();   /* FUN_00350500 */
extern unsigned long sk_x_00350518();   /* FUN_00350518 */
extern unsigned long sk_x_00350524();   /* FUN_00350524 */
extern unsigned long sk_x_0035053c();   /* FUN_0035053c */
extern unsigned long sk_x_00350548();   /* FUN_00350548 */
extern unsigned long sk_x_00350560();   /* FUN_00350560 */
extern cl4_result_t sk_x_00350618();   /* FUN_00350618 */
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
extern cl4_result_t sk_x_00376820();   /* FUN_00376820 */
extern unsigned long sk_x_00377824();   /* FUN_00377824 */
extern unsigned long sk_x_00377bec();   /* FUN_00377bec */
extern unsigned long sk_x_0039a128();   /* FUN_0039a128 */
extern unsigned long sk_x_003a25d4();   /* FUN_003a25d4 */
extern unsigned long sk_x_003d4e84();   /* FUN_003d4e84 */
extern unsigned long sk_x_003d4f18();   /* FUN_003d4f18 */
extern cl4_result_t sk_x_003d50cc();   /* FUN_003d50cc */
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
extern unsigned long sk_x_003fa828();   /* FUN_003fa828 */
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
extern cl4_result_t sk_x_004072c0();   /* FUN_004072c0 */
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
extern unsigned long sk_x_004080cc();   /* FUN_004080cc */
extern unsigned long sk_x_00408160();   /* FUN_00408160 */
extern unsigned long sk_x_00408178();   /* FUN_00408178 */
extern unsigned long sk_x_00408190();   /* FUN_00408190 */
extern unsigned long sk_x_00408258();   /* FUN_00408258 */
extern unsigned long sk_x_0040841c();   /* FUN_0040841c */
extern unsigned long sk_x_00408434();   /* FUN_00408434 */
extern unsigned long sk_x_0040859c();   /* FUN_0040859c */
extern unsigned long sk_x_00409248();   /* FUN_00409248 */
extern unsigned long sk_x_004092d8();   /* FUN_004092d8 */
extern unsigned long sk_x_0040bb18();   /* FUN_0040bb18 */
extern unsigned long sk_x_004ba7ec();   /* FUN_004ba7ec */

/* String literals referenced by the Swift-runtime fatal stubs (Ghidra refs). */
extern const char sk_str_no_executor[];      /* s_There_is_no_executor_implementat_005dc2e0 */
extern const char sk_str_unimpl_executor[];  /* s__Concurrency_UnimplementedExecut_005dc2b0 */
extern const char sk_str_enqueue_main_exec[];/* s_swift_task_enqueueMainExecutor___005dc330 */

/* Forward declarations of the in-slice (batch) functions transcribed below.
 * Cross-references between them are forward; register-forwarded ABI means
 * several take/ignore extra args, so a few are prototype-less (). */
static void sk_x_003fba88(void);
static void sk_x_003fbaa4(uint8_t *param_1);
static void sk_x_003fbaf8(void);
static void sk_x_003fbb48(void);
static void sk_x_003fbb98();
static void sk_x_003fbbdc(uint64_t param_1);
static void sk_x_003fbbe0(uint64_t param_1);
static void sk_x_003fbc10(void);
static void sk_x_003fbc14(void);
static void sk_x_003fbc3c(uint64_t param_1);
static void sk_x_003fbc40(uint64_t param_1);
static cl4_result_t sk_x_003fbc58(int64_t param_1, uint64_t param_2);
static cl4_result_t sk_x_003fbcd4(void);
static cl4_result_t sk_x_003fbd2c(void);
static void sk_x_003fbd98(void);
static void sk_x_003fbdf0(cl4_result_t *param_1);
static void sk_x_003fbe18(cl4_result_t *param_1);
static void sk_x_003fbe40(void);
static unsigned int sk_x_003fbf28();
static void sk_x_003fbf9c(void);
static void sk_x_003fbff4();
static void sk_x_003fc038();
static void sk_x_003fc124(uint64_t param_1);
static void sk_x_003fc128(uint64_t param_1);
static void sk_x_003fc158();
static void sk_x_003fc248(void);
static void sk_x_003fc24c(void);
static void sk_x_003fc274();
static void sk_x_003fc2a4(uint64_t param_1);
static void sk_x_003fc2a8(uint64_t param_1);
static cl4_result_t sk_x_003fc2c0(void);
static cl4_result_t sk_x_003fc318(void);
static void sk_x_003fc384(void);
static void sk_x_003fc3dc(cl4_result_t *param_1);
static void sk_x_003fc404(cl4_result_t *param_1);
static void sk_x_003fc42c(uint64_t param_1, uint64_t param_2);
static void sk_x_003fc49c(cl4_result_t *param_1, uint64_t param_2, uint64_t param_3);
static void sk_x_003fc4d4(void);
static void sk_x_003fc518(void);
static void sk_x_003fc56c(void);
static void sk_x_003fc5c4(void);
static void sk_x_003fc608(void);
static void sk_x_003fc64c(void);
static void sk_x_003fc6b4(void);
static void sk_x_003fc70c(void);
static void sk_x_003fc76c(void);
static void sk_x_003fc79c(void);
static void sk_x_003fc7cc(void);
static void sk_x_003fc7d0(void);
static void sk_x_003fc7e0(void);
static void sk_x_003fc7f4(void);
static void sk_x_003fc7f8(void);
static void sk_x_003fc80c(void);
static void sk_x_003fc810(void);
static void sk_x_003fc81c(void);
static void sk_x_003fc850(void);
static void sk_x_003fc854(void);
static void sk_x_003fc860(void);
static void sk_x_003fc8a0(void);
static void sk_x_003fc90c(void);
static void sk_x_003fc910(void);
static uint64_t sk_x_003fc950(void);
static void sk_x_003fc988(void);
static void sk_x_003fc9d0(void);
static void sk_x_003fc9d4(void);
static uint64_t sk_x_003fca14(void);
static void sk_x_003fca4c(void);
static void sk_x_003fca94(void);
static void sk_x_003fcac8(void);
static long sk_x_003fcafc(uint64_t param_1);
static long sk_x_003fcb2c(uint64_t param_1);
static long sk_x_003fcb5c(uint64_t param_1);
static long sk_x_003fcb8c(uint64_t param_1);
static long sk_x_003fcbbc(uint64_t param_1);
static long sk_x_003fcc1c(uint64_t param_1);
static long sk_x_003fcc4c(uint64_t param_1);
static void sk_x_003fccc4(int64_t param_1, uint64_t param_2);
static void sk_x_003fccd4(void);
static void sk_x_003fcd04(void);
static void sk_x_003fcddc(void);
static void sk_x_003fce98(void);
static unsigned int sk_x_003fcf28(uint64_t param_1, uint64_t param_2);
static void sk_x_003fcf48(void);
static void sk_x_003fd0bc(void);
static long sk_x_003fd194(uint64_t param_1);
static void sk_x_003fd1c4(void);
static void sk_x_003fd25c(uint64_t param_1);
static void sk_x_003fd260(uint64_t param_1);
static void sk_x_003fd278(void);
static void sk_x_003fd3ac(uint64_t param_1);
static long sk_x_003fd3fc(uint64_t param_1);
static void sk_x_003fd4ac(uint64_t param_1, uint64_t param_2);
static void sk_x_003fd554(uint64_t param_1, uint64_t param_2);
static void sk_x_003fd7bc(void);
static void sk_x_003fd874(void);
static void sk_x_003fd8f8(void);
static void sk_x_003fd98c(void);
static void sk_x_003fda44(void);
static void sk_x_003fdad4(void);
static unsigned long sk_x_003fdb80(void);
static void sk_x_003fde6c(void);
static void sk_x_003fdf0c(void);
static void sk_x_003fdf74(void);

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
    ((void (*)(uint64_t))sk_g_00658c80)(*(uint64_t *)(extraout_x8 + 0x40));
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
    ((void (*)(uint64_t))sk_g_00658c80)(*(uint64_t *)(extraout_x8 + 0x40));
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
static unsigned long sk_vas_op_setup3(uint64_t p1, uint64_t p2, uint64_t p3)
{
    uint64_t local_28 = p1;
    uint64_t w = sk_x_00310d34(0);
    cl4_result_t pair = sk_x_00376820(&sk_g_004e8268, w);
    sk_x_00350968(&local_28, pair.hi, p3, pair.lo);
    return sk_x_003f9bdc();
}

/* FUN_003fb3c4 @ 0x003fb3c4  (est. sk_vas_op_setup3_store)
 * Runs FUN_003fb360 with (param_2, *(param_3+0x10)) and stores the result into
 * *param_1. Thin forwarder. Confidence: medium. */
static void sk_vas_op_setup3_store(uint64_t *out, uint64_t p2, uint64_t p3)
{
    uint64_t r = sk_vas_op_setup3(p2, *(uint64_t *)(p3 + 0x10), /* param_3 */ 0);
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
    ((void (*)(uint64_t))sk_g_00658c80)(*(uint64_t *)(extraout_x8 + 0x40));
    sk_x_000aa4ec();
    sk_x_00350a64();
    sk_x_00310d68();
    sk_x_00351f10();
    sk_x_0007c1a4();
    ((void (*)(void))sk_g_00658c80)();
    sk_x_00407b80();
    sk_x_003f539c(seed.hi, p3);
    sk_x_002298d4();
    uint64_t it = sk_x_003f761c(seed.hi, p3).lo;
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
    sk_vas_op_iterate((uint64_t)(uintptr_t)frame, *(uint64_t *)(x20 + 0), *(uint64_t *)(p2 + 0x10), v);
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
    ((void (*)(uint64_t))sk_g_00658c80)(*(uint64_t *)(extraout_x8 + 0x40));
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
        code op = (code)(uintptr_t)sk_x_003fd3fc(/* in_x3 */ 0);
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

/* ================================================================== *
 * 0x003fba88 - 0x003fc8a0 : Swift Concurrency executor / region-op
 *   helpers (worker SKR12 remainder).  All function names are estimates;
 *   register-forwarded arguments are modelled as commented locals.
 * ================================================================== */

/* FUN_003fba88 @ 0x003fba88  (est. sk_ret_thunk_ba88)
 * Ghidra: void FUN_003fba88(void)
 * Thin forwarder to FUN_003fbf9c. Confidence: low. */
static void sk_x_003fba88(void)
{
    sk_x_003fbf9c();
}

/* FUN_003fbaa4 @ 0x003fbaa4  (est. sk_x_003fbaa4)
 * Ghidra: void FUN_003fbaa4(undefined1 *param_1)
 * Stores the low byte of FUN_003fbf28() into *param_1. Confidence: low. */
static void sk_x_003fbaa4(uint8_t *param_1)
{
    *param_1 = (uint8_t)sk_x_003fbf28();
}

/* FUN_003fbaf8 @ 0x003fbaf8  (est. sk_register_region_005a1328)
 * Ghidra: void FUN_003fbaf8(void)
 * Resolves a code pointer via FUN_00027724(&DAT_005a1328) and dispatches a
 * two-word "register region" call. Confidence: low. */
static void sk_x_003fbaf8(void)
{
    code fn = (code)(uintptr_t)sk_x_00027724((uint64_t)&sk_g_005a1328);
    ((void (*)(uint64_t, uint64_t))fn)(0x67f130, (uint64_t)&sk_g_005a1328);
}

/* FUN_003fbb48 @ 0x003fbb48  (est. sk_register_region_005a1398)
 * Ghidra: void FUN_003fbb48(void)
 * Resolves a code pointer via FUN_00027724(&DAT_005a1398) and dispatches a
 * two-word "register region" call. Confidence: low. */
static void sk_x_003fbb48(void)
{
    code fn = (code)(uintptr_t)sk_x_00027724((uint64_t)&sk_g_005a1398);
    ((void (*)(uint64_t, uint64_t))fn)(0x67f0a0, (uint64_t)&sk_g_005a1398);
}

/* FUN_003fbb98 @ 0x003fbb98  (est. sk_x_003fbb98)
 * Ghidra: void FUN_003fbb98(void)
 * Forwarder to FUN_003fc038 (register-forwarded arguments are dropped; the
 * callee re-derives them from registers). Confidence: low. */
static void sk_x_003fbb98()
{
    sk_x_003fc038();
}

/* FUN_003fbbdc @ 0x003fbbdc  (est. sk_vas_region_setup_tag_16d8)
 * Ghidra: void FUN_003fbbdc(undefined8 param_1)
 * Forwards (param_1, 0x67f130, &DAT_005a16d8) to FUN_003fc158.
 * Confidence: low. */
static void sk_x_003fbbdc(uint64_t param_1)
{
    sk_x_003fc158(param_1, 0x67f130, (uint64_t)&sk_g_005a16d8);
}

/* FUN_003fbbe0 @ 0x003fbbe0  (est. sk_vas_region_setup_tag_16d8_b)
 * Ghidra: void FUN_003fbbe0(undefined8 param_1)
 * Identical body to FUN_003fbbdc (distinct code address). Confidence: low. */
static void sk_x_003fbbe0(uint64_t param_1)
{
    sk_x_003fc158(param_1, 0x67f130, (uint64_t)&sk_g_005a16d8);
}

/* FUN_003fbc10 @ 0x003fbc10  (est. sk_x_003fbc10)
 * Ghidra: void FUN_003fbc10(void)
 * Forwarder to FUN_003fc274. Confidence: low. */
static void sk_x_003fbc10(void)
{
    sk_x_003fc274();
}

/* FUN_003fbc14 @ 0x003fbc14  (est. sk_x_003fbc14)
 * Ghidra: void FUN_003fbc14(void)
 * Identical body to FUN_003fbc10 (distinct code address). Confidence: low. */
static void sk_x_003fbc14(void)
{
    sk_x_003fc274();
}

/* FUN_003fbc3c @ 0x003fbc3c  (est. sk_x_003fbc3c)
 * Ghidra: void FUN_003fbc3c(undefined8 param_1)
 * Forwards (param_1, *unaff_x20, unaff_x20[1]) to FUN_003fbb98.
 * Confidence: low (register-forwarded x20). */
static void sk_x_003fbc3c(uint64_t param_1)
{
    uint64_t *x20 = /* unaff_x20 */ 0;
    sk_x_003fbb98(param_1, *x20, x20[1]);
}

/* FUN_003fbc40 @ 0x003fbc40  (est. sk_x_003fbc40)
 * Ghidra: void FUN_003fbc40(undefined8 param_1)
 * Identical body to FUN_003fbc3c (distinct code address). Confidence: low. */
static void sk_x_003fbc40(uint64_t param_1)
{
    uint64_t *x20 = /* unaff_x20 */ 0;
    sk_x_003fbb98(param_1, *x20, x20[1]);
}

/* FUN_003fbc58 @ 0x003fbc58  (est. sk_ns_scale128)
 * Ghidra: undefined1 [16] FUN_003fbc58(long param_1, ulong param_2)
 * Scales a (param_1, param_2) pair by 10^9/10^18 into a 128-bit result
 * (result = param_1*10^18 + param_2*10^9).  Aborts (brk) on 64-bit overflow
 * of param_2*10^9. Confidence: medium. */
static cl4_result_t sk_x_003fbc58(int64_t param_1, uint64_t param_2)
{
    cl4_result_t result;

    /* 128-bit product of param_2 * 10^9 (auVar1 = 0:param_2 zero-extended). */
    __uint128_t p2 = (__uint128_t)param_2 * 1000000000ULL;
    if ((uint64_t)(p2 >> 64) == 0) {
        /* 128-bit signed product of param_1 * 10^18. */
        __int128_t p1 = (__int128_t)(int64_t)param_1 * (__int128_t)1000000000000000000LL;
        uint64_t hi = (uint64_t)((__uint128_t)p1 >> 64);
        uint64_t a  = (uint64_t)p1;      /* low 64 of param_1*10^18 */
        uint64_t b  = (uint64_t)p2;      /* low 64 of param_2*10^9 */
        uint64_t lo = a + b;
        if (lo < a) {                    /* CARRY8(a, b) */
            hi += 1;
        }
        result.lo = lo;
        result.hi = hi;
        return result;
    }
    /* WARNING: Does not return */
    sk_brk_noret();
    return result;
}

/* FUN_003fbcd4 @ 0x003fbcd4  (est. sk_canary_clock_09248)
 * Ghidra: void FUN_003fbcd4(void)
 * Canary-guarded helper: runs the guarded prelude (FUN_00406a10) and, when the
 * canary slot matches, performs a clock read via FUN_003fc42c(1, FUN_00409248)
 * whose register pair is the 16-byte result. On canary mismatch it aborts
 * through FUN_0011d7e8 (non-returning). Confidence: low. */
static cl4_result_t sk_x_003fbcd4(void)
{
    uint64_t local_18 = SK_CANARY;

    sk_x_00406a10();
    if (local_18 == (uint64_t)SK_CANARY) {
        sk_x_003fc42c(1, (uint64_t)sk_x_00409248);
        return (cl4_result_t){ /* lo (register-forwarded) */ 0,
                               /* hi (register-forwarded) */ 0 };
    }
    /* WARNING: Subroutine does not return */
    sk_x_0011d7e8();
    return (cl4_result_t){0, 0};
}

/* FUN_003fbd2c @ 0x003fbd2c  (est. sk_canary_clock_092d8)
 * Ghidra: void FUN_003fbd2c(void)
 * Identical to FUN_003fbcd4 but reads via FUN_003fc42c(1, FUN_004092d8).
 * Confidence: low. */
static cl4_result_t sk_x_003fbd2c(void)
{
    uint64_t local_18 = SK_CANARY;

    sk_x_00406a10();
    if (local_18 == (uint64_t)SK_CANARY) {
        sk_x_003fc42c(1, (uint64_t)sk_x_004092d8);
        return (cl4_result_t){ 0, 0 };
    }
    /* WARNING: Subroutine does not return */
    sk_x_0011d7e8();
    return (cl4_result_t){0, 0};
}

/* FUN_003fbd98 @ 0x003fbd98  (est. sk_abort_prelude_003fbd98)
 * Ghidra: void FUN_003fbd98(void)
 * Runs the abort prelude (FUN_00406fd4/FUN_00407030/FUN_003593c0/FUN_00407048)
 * then raises a non-returning fault (FUN_001afa84). Confidence: low. */
static void sk_x_003fbd98(void)
{
    sk_x_00406fd4();
    sk_x_00407030();
    sk_x_003593c0();
    sk_x_00407048();
    /* WARNING: Subroutine does not return */
    sk_x_001afa84();
}

/* FUN_003fbdf0 @ 0x003fbdf0  (est. sk_clock_read_003fbdf0)
 * Ghidra: void FUN_003fbdf0(undefined1 (*param_1)[16])
 * Copies the 16-byte result of FUN_003fbcd4() into *param_1. Confidence: low. */
static void sk_x_003fbdf0(cl4_result_t *param_1)
{
    *param_1 = sk_x_003fbcd4();
}

/* FUN_003fbe18 @ 0x003fbe18  (est. sk_clock_read_003fbe18)
 * Ghidra: void FUN_003fbe18(undefined1 (*param_1)[16])
 * Copies the 16-byte result of FUN_003fbd2c() into *param_1. Confidence: low. */
static void sk_x_003fbe18(cl4_result_t *param_1)
{
    *param_1 = sk_x_003fbd2c();
}

/* FUN_003fbe40 @ 0x003fbe40  (est. sk_vas_ret_thunk_003fbe40)
 * Ghidra: void FUN_003fbe40(void)
 * Runs FUN_00407d74 then the FUN_002d3c28 thunk. Confidence: low. */
static void sk_x_003fbe40(void)
{
    sk_x_00407d74();
    sk_x_002d3c28();
}

/* FUN_003fbf28 @ 0x003fbf28  (est. sk_validate_region_type)
 * Ghidra: unsigned int FUN_003fbf28(long param_1, long param_2)
 * Validates a region type tag pair; returns 0 when the pair matches the
 * "vale_" signature, else a folded result of FUN_002a0cf8.  Arguments arrive
 * register-forwarded (modelled here as commented locals). Confidence: low. */
static unsigned int sk_x_003fbf28()
{
    long param_1 = /* param_1 (register-forwarded) */ 0;
    long param_2 = /* param_2 (register-forwarded) */ 0;
    unsigned int uVar1;

    if (param_1 == 0x65756c61765f && param_2 == -0x1a00000000000000LL) {
        sk_x_003a25d4(param_2);
        uVar1 = 0;
    }
    else {
        uVar1 = sk_x_002a0cf8(0x65756c61765f, 0xe600000000000000ULL, param_1, param_2, 0);
        sk_x_003a25d4(param_2);
        uVar1 = (uVar1 ^ 0xffffffff) & 1;
    }
    return uVar1;
}

/* FUN_003fbf9c @ 0x003fbf9c  (est. sk_vas_op_prelude_003fbf9c)
 * Ghidra: void FUN_003fbf9c(void)
 * Runs the VAS-op prelude (FUN_004080b0 / FUN_002298d4(0)) and the finisher
 * FUN_001a8564. Confidence: low. */
static void sk_x_003fbf9c(void)
{
    sk_x_004080b0();
    sk_x_002298d4(0);
    sk_x_001a8564();
}

/* FUN_003fbff4 @ 0x003fbff4  (est. sk_x_003fbff4)
 * Ghidra: void FUN_003fbff4(void)
 * Forwarder to FUN_003fc038. Confidence: low. */
static void sk_x_003fbff4()
{
    sk_x_003fc038();
}

/* FUN_003fc038 @ 0x003fc038  (est. sk_vas_region_setup_003fc038)
 * Ghidra: void FUN_003fc038(long param_1, undefined8 param_2, ... , undefined8 param_7)
 * Region-setup body: dereferences param_1, runs FUN_0006a4c0/FUN_0006a4f0,
 * forwards to FUN_003513b4, packs a two-word pair and funnels it through
 * FUN_00002534/FUN_001bdb28.  All parameters are register-forwarded (modelled
 * as commented locals). Confidence: low. */
static void sk_x_003fc038()
{
    uint64_t param_1 = /* param_1 (register-forwarded) */ 0;
    uint64_t param_2 = /* param_2 (register-forwarded) */ 0;
    uint64_t param_3 = /* param_3 (register-forwarded) */ 0;
    uint64_t param_4 = /* param_4 (register-forwarded) */ 0;
    uint64_t param_5 = /* param_5 (register-forwarded) */ 0;
    uint64_t param_6 = /* param_6 (register-forwarded) */ 0;
    uint64_t param_7 = /* param_7 (register-forwarded) */ 0;
    uint64_t uVar1;
    code *extraout_x8;
    cl4_result_t auVar2;
    uint64_t local_70 = param_2, uStack_68 = param_3;

    uVar1 = *(uint64_t *)(param_1 + 0x20);
    sk_x_0006a4c0(param_1, *(uint64_t *)(param_1 + 0x18));
    uVar1 = sk_x_0006a4f0(uVar1);
    sk_x_003513b4(uVar1, param_4);
    uVar1 = ((uint64_t (*)(void))(uintptr_t)(extraout_x8 = 0))();
    auVar2 = sk_x_00002534(param_6, param_7);
    sk_x_001bdb28(&local_70, auVar2.hi, auVar2.lo, 0x676ea8, 0x66f5e0);
    sk_x_0036b118(uVar1);
}

/* FUN_003fc124 @ 0x003fc124  (est. sk_vas_region_setup_a16a8)
 * Ghidra: void FUN_003fc124(undefined8 param_1)
 * Forwards (param_1, 0x67f0a0, &DAT_005a16a8) to FUN_003fc158. Confidence: low. */
static void sk_x_003fc124(uint64_t param_1)
{
    sk_x_003fc158(param_1, 0x67f0a0, (uint64_t)&sk_g_005a16a8);
}

/* FUN_003fc128 @ 0x003fc128  (est. sk_vas_region_setup_a16a8_b)
 * Ghidra: void FUN_003fc128(undefined8 param_1)
 * Identical body to FUN_003fc124 (distinct code address). Confidence: low. */
static void sk_x_003fc128(uint64_t param_1)
{
    sk_x_003fc158(param_1, 0x67f0a0, (uint64_t)&sk_g_005a16a8);
}

/* FUN_003fc158 @ 0x003fc158  (est. sk_vas_region_teardown_003fc158)
 * Ghidra: void FUN_003fc158(void)
 * Region-teardown path: resolves the region's continuation, runs
 * FUN_0006a4c0/FUN_0006a668/FUN_000bd3a4, then either completes the pair via
 * FUN_00352ae4/FUN_001bea18 or just releases the object (FUN_000026e8);
 * always ends with FUN_000e15d8.  Called with three register-forwarded args
 * (tag, DAT pointer) that the body ignores. Confidence: low. */
static void sk_x_003fc158()
{
    long lVar1;
    uint64_t uVar2;
    code *extraout_x8;
    long unaff_x21 = /* unaff_x21 */ 0;
    uint64_t local_60[2];

    lVar1 = sk_x_0035128c();
    uVar2 = *(uint64_t *)(lVar1 + 0x20);
    sk_x_0006a4c0(lVar1, *(uint64_t *)(lVar1 + 0x18));
    uVar2 = sk_x_0006a668(uVar2);
    sk_x_000bd3a4(uVar2);
    uVar2 = ((uint64_t (*)(void))(uintptr_t)(extraout_x8 = 0))();
    if (unaff_x21 == 0) {
        sk_x_00352ae4(local_60, 0x676ea8);
        sk_x_001bea18();
        sk_x_0036b118(uVar2);
        sk_x_000026e8(lVar1);
    }
    else {
        sk_x_000026e8(lVar1);
    }
    sk_x_000e15d8();
}

/* FUN_003fc248 @ 0x003fc248  (est. sk_x_003fc248)
 * Ghidra: void FUN_003fc248(void)
 * Forwarder to FUN_003fc274. Confidence: low. */
static void sk_x_003fc248(void)
{
    sk_x_003fc274();
}

/* FUN_003fc24c @ 0x003fc24c  (est. sk_x_003fc24c)
 * Ghidra: void FUN_003fc24c(void)
 * Identical body to FUN_003fc248 (distinct code address). Confidence: low. */
static void sk_x_003fc24c(void)
{
    sk_x_003fc274();
}

/* FUN_003fc274 @ 0x003fc274  (est. sk_vas_op_result_probe)
 * Ghidra: void FUN_003fc274(undefined1 (*param_1)[16])
 * Probes the in_x3 code pointer; when unaff_x21 == 0 it stores the 16-byte
 * result into *param_1.  param_1 arrives register-forwarded. Confidence: low. */
static void sk_x_003fc274()
{
    cl4_result_t *param_1 = /* param_1 (register-forwarded) */ 0;
    uint64_t in_x3 = /* in_x3 (register-forwarded) */ 0;
    long unaff_x21 = /* unaff_x21 */ 0;
    cl4_result_t auVar1;

    auVar1 = ((cl4_result_t (*)(void))(uintptr_t)in_x3)();
    if (unaff_x21 == 0) {
        *param_1 = auVar1;
    }
}

/* FUN_003fc2a4 @ 0x003fc2a4  (est. sk_x_003fc2a4)
 * Ghidra: void FUN_003fc2a4(undefined8 param_1)
 * Forwards (param_1, *unaff_x20, unaff_x20[1]) to FUN_003fbff4.
 * Confidence: low (register-forwarded x20). */
static void sk_x_003fc2a4(uint64_t param_1)
{
    uint64_t *x20 = /* unaff_x20 */ 0;
    sk_x_003fbff4(param_1, *x20, x20[1]);
}

/* FUN_003fc2a8 @ 0x003fc2a8  (est. sk_x_003fc2a8)
 * Ghidra: void FUN_003fc2a8(undefined8 param_1)
 * Identical body to FUN_003fc2a4 (distinct code address). Confidence: low. */
static void sk_x_003fc2a8(uint64_t param_1)
{
    uint64_t *x20 = /* unaff_x20 */ 0;
    sk_x_003fbff4(param_1, *x20, x20[1]);
}

/* FUN_003fc2c0 @ 0x003fc2c0  (est. sk_canary_clock_09248_2)
 * Ghidra: void FUN_003fc2c0(void)
 * Canary-guarded clock read via FUN_003fc42c(2, FUN_00409248). Confidence: low. */
static cl4_result_t sk_x_003fc2c0(void)
{
    uint64_t local_18 = SK_CANARY;

    sk_x_00406a10();
    if (local_18 == (uint64_t)SK_CANARY) {
        sk_x_003fc42c(2, (uint64_t)sk_x_00409248);
        return (cl4_result_t){ 0, 0 };
    }
    /* WARNING: Subroutine does not return */
    sk_x_0011d7e8();
    return (cl4_result_t){0, 0};
}

/* FUN_003fc318 @ 0x003fc318  (est. sk_canary_clock_092d8_2)
 * Ghidra: void FUN_003fc318(void)
 * Canary-guarded clock read via FUN_003fc42c(2, FUN_004092d8). Confidence: low. */
static cl4_result_t sk_x_003fc318(void)
{
    uint64_t local_18 = SK_CANARY;

    sk_x_00406a10();
    if (local_18 == (uint64_t)SK_CANARY) {
        sk_x_003fc42c(2, (uint64_t)sk_x_004092d8);
        return (cl4_result_t){ 0, 0 };
    }
    /* WARNING: Subroutine does not return */
    sk_x_0011d7e8();
    return (cl4_result_t){0, 0};
}

/* FUN_003fc384 @ 0x003fc384  (est. sk_abort_prelude_003fc384)
 * Ghidra: void FUN_003fc384(void)
 * Identical to FUN_003fbd98 (abort prelude + non-returning fault). */
static void sk_x_003fc384(void)
{
    sk_x_00406fd4();
    sk_x_00407030();
    sk_x_003593c0();
    sk_x_00407048();
    /* WARNING: Subroutine does not return */
    sk_x_001afa84();
}

/* FUN_003fc3dc @ 0x003fc3dc  (est. sk_clock_read_003fc3dc)
 * Ghidra: void FUN_003fc3dc(undefined1 (*param_1)[16])
 * Copies the 16-byte result of FUN_003fc2c0() into *param_1. Confidence: low. */
static void sk_x_003fc3dc(cl4_result_t *param_1)
{
    *param_1 = sk_x_003fc2c0();
}

/* FUN_003fc404 @ 0x003fc404  (est. sk_clock_read_003fc404)
 * Ghidra: void FUN_003fc404(undefined1 (*param_1)[16])
 * Copies the 16-byte result of FUN_003fc318() into *param_1. Confidence: low. */
static void sk_x_003fc404(cl4_result_t *param_1)
{
    *param_1 = sk_x_003fc318();
}

/* FUN_003fc42c @ 0x003fc42c  (est. sk_clock_read_pair)
 * Ghidra: void FUN_003fc42c(undefined8 param_1, code *param_2)
 * Invokes the clock-read callback param_2 with a two-word out buffer, scales
 * the result via FUN_003fbc58, and checks the stack canary (aborting through
 * FUN_0011d7e8 on mismatch).  param_2 is a function pointer passed as a word.
 * Confidence: medium. */
static void sk_x_003fc42c(uint64_t param_1, uint64_t param_2)
{
    uint64_t local_28 = 0, uStack_20 = 0;
    uint64_t local_18 = SK_CANARY;

    ((void (*)(uint64_t *, uint64_t *, uint64_t))(uintptr_t)param_2)(&uStack_20, &local_28, param_1);
    sk_x_003fbc58(uStack_20, local_28);
    if (local_18 == (uint64_t)SK_CANARY) {
        return;
    }
    /* WARNING: Subroutine does not return */
    sk_x_0011d7e8();
}

/* FUN_003fc49c @ 0x003fc49c  (est. sk_x_003fc49c)
 * Ghidra: void FUN_003fc49c(undefined1 (*param_1)[16], undefined8 param_2, undefined8 param_3)
 * Replaces the 16-byte record at *param_1 with the FUN_002d3c28 thunk result.
 * Confidence: low. */
static void sk_x_003fc49c(cl4_result_t *param_1, uint64_t param_2, uint64_t param_3)
{
    cl4_result_t auVar1;

    auVar1 = sk_x_002d3c28(param_1->lo, param_1->hi, param_2, param_3);
    *param_1 = auVar1;
}

/* FUN_003fc4d4 @ 0x003fc4d4  (est. sk_vas_op_teardown_seq)
 * Ghidra: void FUN_003fc4d4(void)
 * Sequential teardown prelude: runs a chain of op teardown helpers and the
 * FUN_002d3c28 thunk. Confidence: low. */
static void sk_x_003fc4d4(void)
{
    sk_x_00077888();
    sk_x_003509ec();
    sk_x_00019858();
    sk_x_0035053c();
    sk_x_002d4a64();
    sk_x_00351790();
    sk_x_00100efc();
    sk_x_002d3c28();
}

/* FUN_003fc518 @ 0x003fc518  (est. sk_vas_op_teardown_store)
 * Ghidra: void FUN_003fc518(void)
 * Runs the teardown prelude and stores the FUN_002d3c28 thunk result into the
 * register-forwarded unaff_x21 record. Confidence: low. */
static void sk_x_003fc518(void)
{
    cl4_result_t *unaff_x21 = /* unaff_x21 (register-forwarded) */ 0;
    cl4_result_t auVar1;

    sk_x_0035098c();
    sk_x_00019858();
    sk_x_0035053c();
    sk_x_002d4a64();
    sk_x_00351790();
    sk_x_000e15d8();
    auVar1 = sk_x_002d3c28();
    *unaff_x21 = auVar1;
}

/* FUN_003fc56c @ 0x003fc56c  (est. sk_vas_op_run_teardown)
 * Ghidra: void FUN_003fc56c(void)
 * Runs a VAS-op teardown: prelude into a 72-byte frame, then FUN_002d738c and
 * FUN_001a8564. Confidence: low. */
static void sk_x_003fc56c(void)
{
    uint8_t frame[72];

    sk_x_003504d0();
    sk_x_004080b0();
    sk_x_00350624(frame);
    sk_x_002d738c();
    sk_x_001a8564();
}

/* FUN_003fc5c4 @ 0x003fc5c4  (est. sk_x_003fc5c4)
 * Ghidra: void FUN_003fc5c4(void)
 * Runs FUN_00407e88 then stores the extraout_x9 result into *unaff_x19.
 * Confidence: low (register-forwarded x9/x19). */
static void sk_x_003fc5c4(void)
{
    code *extraout_x9 = /* extraout_x9 */ 0;
    cl4_result_t *unaff_x19 = /* unaff_x19 (register-forwarded) */ 0;
    cl4_result_t auVar1;

    sk_x_00407e88();
    auVar1 = ((cl4_result_t (*)(void))(uintptr_t)extraout_x9)();
    *unaff_x19 = auVar1;
}

/* FUN_003fc608 @ 0x003fc608  (est. sk_x_003fc608)
 * Ghidra: void FUN_003fc608(void)
 * Identical body to FUN_003fc5c4 (distinct code address). Confidence: low. */
static void sk_x_003fc608(void)
{
    code *extraout_x9 = /* extraout_x9 */ 0;
    cl4_result_t *unaff_x19 = /* unaff_x19 (register-forwarded) */ 0;
    cl4_result_t auVar1;

    sk_x_00407e88();
    auVar1 = ((cl4_result_t (*)(void))(uintptr_t)extraout_x9)();
    *unaff_x19 = auVar1;
}

/* FUN_003fc64c @ 0x003fc64c  (est. sk_vas_op_frame_run)
 * Ghidra: void FUN_003fc64c(void)
 * Seeds a 72-byte frame (FUN_001a84f4/FUN_00350548), invokes the in_x3 code
 * pointer, and finishes with FUN_001a8564. Confidence: low. */
static void sk_x_003fc64c(void)
{
    uint64_t in_x3 = /* in_x3 (register-forwarded) */ 0;
    uint8_t frame[72];

    sk_x_001a84f4(frame);
    sk_x_00350548(frame);
    ((void (*)(void))(uintptr_t)in_x3)();
    sk_x_001a8564();
}

/* FUN_003fc6b4 @ 0x003fc6b4  (est. sk_abort_prelude_003fc6b4)
 * Ghidra: void FUN_003fc6b4(void)
 * Identical to FUN_003fbd98 (abort prelude + non-returning fault). */
static void sk_x_003fc6b4(void)
{
    sk_x_00406fd4();
    sk_x_00407030();
    sk_x_003593c0();
    sk_x_00407048();
    /* WARNING: Subroutine does not return */
    sk_x_001afa84();
}

/* FUN_003fc70c @ 0x003fc70c  (est. sk_executor_no_executor_fatal)
 * Ghidra: void FUN_003fc70c(void)
 * Swift-runtime fatal stub: builds a "There is no executor implementation"
 * message and raises a non-returning fault (FUN_001afa84). Confidence: high
 * (string matched). */
static void sk_x_003fc70c(void)
{
    uint64_t uVar1;
    uint64_t extraout_x8 = /* extraout_x8 */ 0;

    uVar1 = sk_x_0035ac70((uint64_t)sk_str_no_executor);
    uVar1 = sk_x_003593c0(uVar1, uVar1);
    /* WARNING: Subroutine does not return */
    sk_x_001afa84(uVar1, 0xb, 2, 0xd00000000000002aULL,
                  extraout_x8 | 0x8000000000000000ULL,
                  (uint64_t)sk_str_unimpl_executor, 0x28, 2);
}

/* FUN_003fc76c @ 0x003fc76c  (est. sk_executor_no_executor_brk)
 * Ghidra: void FUN_003fc76c(void)
 * Swift executor stub: opens the "no executor" message and traps (brk).
 * Confidence: high (string matched). */
static void sk_x_003fc76c(void)
{
    sk_x_0035ac70((uint64_t)sk_str_no_executor);
    sk_x_00406eb0();
    /* WARNING: Does not return */
    sk_brk_noret();
}

/* FUN_003fc79c @ 0x003fc79c  (est. sk_executor_no_executor_brk_b)
 * Ghidra: void FUN_003fc79c(void)
 * Identical to FUN_003fc76c (distinct code address). Confidence: high. */
static void sk_x_003fc79c(void)
{
    sk_x_0035ac70((uint64_t)sk_str_no_executor);
    sk_x_00406eb0();
    /* WARNING: Does not return */
    sk_brk_noret();
}

/* FUN_003fc7cc @ 0x003fc7cc  (est. sk_executor_dispatch_fatal)
 * Ghidra: void FUN_003fc7cc(void)
 * Runs FUN_003fc70c then FUN_003d4f18 (non-returning fatal). Confidence: low. */
static void sk_x_003fc7cc(void)
{
    sk_x_003fc70c();
    sk_x_003d4f18();
}

/* FUN_003fc7d0 @ 0x003fc7d0  (est. sk_executor_dispatch_fatal_b)
 * Ghidra: void FUN_003fc7d0(void)
 * Identical body to FUN_003fc7cc (distinct code address). Confidence: low. */
static void sk_x_003fc7d0(void)
{
    sk_x_003fc70c();
    sk_x_003d4f18();
}

/* FUN_003fc7e0 @ 0x003fc7e0  (est. sk_executor_dispatch_fatal_c)
 * Ghidra: void FUN_003fc7e0(void)
 * Runs FUN_003d4f18 (non-returning fatal). Confidence: low. */
static void sk_x_003fc7e0(void)
{
    sk_x_003d4f18();
}

/* FUN_003fc7f4 @ 0x003fc7f4  (est. sk_executor_dispatch_brk)
 * Ghidra: void FUN_003fc7f4(void)
 * Runs FUN_003fc76c then FUN_003d4e84. Confidence: low. */
static void sk_x_003fc7f4(void)
{
    sk_x_003fc76c();
    sk_x_003d4e84();
}

/* FUN_003fc7f8 @ 0x003fc7f8  (est. sk_executor_dispatch_brk_b)
 * Ghidra: void FUN_003fc7f8(void)
 * Identical body to FUN_003fc7f4 (distinct code address). Confidence: low. */
static void sk_x_003fc7f8(void)
{
    sk_x_003fc76c();
    sk_x_003d4e84();
}

/* FUN_003fc80c @ 0x003fc80c  (est. sk_executor_dispatch_brk_c)
 * Ghidra: void FUN_003fc80c(void)
 * Runs FUN_003fc79c, opens the "no executor" message with FUN_003fc81c, then
 * traps (brk). Confidence: low. */
static void sk_x_003fc80c(void)
{
    sk_x_003fc79c();
    sk_x_0035ac70((uint64_t)sk_str_no_executor, (uint64_t)sk_x_003fc81c);
    sk_x_00406eb0();
    /* WARNING: Does not return */
    sk_brk_noret();
}

/* FUN_003fc810 @ 0x003fc810  (est. sk_executor_dispatch_brk_d)
 * Ghidra: void FUN_003fc810(void)
 * Identical body to FUN_003fc80c (distinct code address). Confidence: low. */
static void sk_x_003fc810(void)
{
    sk_x_003fc79c();
    sk_x_0035ac70((uint64_t)sk_str_no_executor, (uint64_t)sk_x_003fc81c);
    sk_x_00406eb0();
    /* WARNING: Does not return */
    sk_brk_noret();
}

/* FUN_003fc81c @ 0x003fc81c  (est. sk_executor_dispatch_brk_e)
 * Ghidra: void FUN_003fc81c(void)
 * Opens the "no executor" message then traps (brk). Confidence: low. */
static void sk_x_003fc81c(void)
{
    sk_x_0035ac70((uint64_t)sk_str_no_executor);
    sk_x_00406eb0();
    /* WARNING: Does not return */
    sk_brk_noret();
}

/* FUN_003fc850 @ 0x003fc850  (est. sk_executor_enqueue_main_fatal)
 * Ghidra: void FUN_003fc850(void)
 * Swift enqueueMainExecutor stub: opens the "swift_task_enqueueMainExecutor"
 * message and traps (brk). Confidence: high (string matched). */
static void sk_x_003fc850(void)
{
    sk_x_003fc81c();
    sk_x_0035ac70((uint64_t)sk_str_enqueue_main_exec, (uint64_t)sk_x_003fc860);
    sk_x_00407134();
    sk_x_004079f4();
    /* WARNING: Does not return */
    sk_brk_noret();
}

/* FUN_003fc854 @ 0x003fc854  (est. sk_executor_enqueue_main_fatal_b)
 * Ghidra: void FUN_003fc854(void)
 * Identical body to FUN_003fc850 (distinct code address). Confidence: high. */
static void sk_x_003fc854(void)
{
    sk_x_003fc81c();
    sk_x_0035ac70((uint64_t)sk_str_enqueue_main_exec, (uint64_t)sk_x_003fc860);
    sk_x_00407134();
    sk_x_004079f4();
    /* WARNING: Does not return */
    sk_brk_noret();
}

/* FUN_003fc860 @ 0x003fc860  (est. sk_executor_enqueue_main_brk)
 * Ghidra: void FUN_003fc860(void)
 * Opens the enqueueMainExecutor message then traps (brk). Confidence: high. */
static void sk_x_003fc860(void)
{
    sk_x_0035ac70((uint64_t)sk_str_enqueue_main_exec);
    sk_x_00407134();
    sk_x_004079f4();
    /* WARNING: Does not return */
    sk_brk_noret();
}

/* FUN_003fc8a0 @ 0x003fc8a0  (est. sk_swift_retry_dispatch)
 * Ghidra: void FUN_003fc8a0(void)
 * Builds a result via FUN_003d50cc/FUN_003fcbbc/FUN_003504ac, invokes the
 * extraout_x8 continuation, and releases the pair. Confidence: low. */
static void sk_x_003fc8a0(void)
{
    code *extraout_x8 = /* extraout_x8 */ 0;
    cl4_result_t auVar2, auVar3;
    uint64_t uVar1;

    auVar2 = sk_x_003d50cc();
    uVar1 = sk_x_003fcbbc(auVar2.hi);
    auVar3 = sk_x_003504ac(uVar1);
    ((void (*)(uint64_t, uint64_t, uint64_t))(uintptr_t)extraout_x8)(auVar3.lo, auVar3.hi, auVar2.hi);
    sk_x_0036b118(auVar2.lo);
}

/* ================================================================== *
 * 0x003fc90c - 0x003fdf74 : executor dispatch / tagged-metadata accessors
 *   (worker SKR12 remainder).
 * ================================================================== */

/* FUN_003fc90c @ 0x003fc90c  (est. sk_executor_core_init)
 * Ghidra: void FUN_003fc90c(void)
 * Initialises the executor core globals: DAT_006adf38 = FUN_0036a940(0x6578f8,
 * 0x10, 7); DAT_006adf40 = 0x67dcb8. Confidence: low. */
static void sk_x_003fc90c(void)
{
    sk_g_006adf38 = sk_x_0036a940(0x6578f8, 0x10, 7);
    sk_g_006adf40 = 0x67dcb8;
}

/* FUN_003fc910 @ 0x003fc910  (est. sk_executor_core_init_b)
 * Ghidra: void FUN_003fc910(void)
 * Identical body to FUN_003fc90c (distinct code address). Confidence: low. */
static void sk_x_003fc910(void)
{
    sk_g_006adf38 = sk_x_0036a940(0x6578f8, 0x10, 7);
    sk_g_006adf40 = 0x67dcb8;
}

/* FUN_003fc950 @ 0x003fc950  (est. sk_executor_core_get)
 * Ghidra: undefined1 * FUN_003fc950(void)
 * Lazily initialises the executor core (when DAT_006c0b78 != -1) and returns
 * &DAT_006adf38. Confidence: low. */
static uint64_t sk_x_003fc950(void)
{
    if (sk_g_006c0b78 != (uint64_t)-1) {
        sk_x_00407568();
        sk_x_0039a128();
    }
    return (uint64_t)&sk_g_006adf38;
}

/* FUN_003fc988 @ 0x003fc988  (est. sk_executor_core_release)
 * Ghidra: void FUN_003fc988(void)
 * Lazily initialises the executor core then releases DAT_006adf38 via
 * FUN_0036b270. Confidence: low. */
static void sk_x_003fc988(void)
{
    if (sk_g_006c0b78 != (uint64_t)-1) {
        sk_x_00407568();
        sk_x_0039a128();
    }
    sk_x_0036b270(sk_g_006adf38);
}

/* FUN_003fc9d0 @ 0x003fc9d0  (est. sk_executor_deq_init)
 * Ghidra: void FUN_003fc9d0(void)
 * Initialises the executor dequeue globals: DAT_006adf50 = FUN_0036a940(
 * 0x657950, 0x10, 7); DAT_006adf58 = 0x67dd08. Confidence: low. */
static void sk_x_003fc9d0(void)
{
    sk_g_006adf50 = sk_x_0036a940(0x657950, 0x10, 7);
    sk_g_006adf58 = 0x67dd08;
}

/* FUN_003fc9d4 @ 0x003fc9d4  (est. sk_executor_deq_init_b)
 * Ghidra: void FUN_003fc9d4(void)
 * Identical body to FUN_003fc9d0 (distinct code address). Confidence: low. */
static void sk_x_003fc9d4(void)
{
    sk_g_006adf50 = sk_x_0036a940(0x657950, 0x10, 7);
    sk_g_006adf58 = 0x67dd08;
}

/* FUN_003fca14 @ 0x003fca14  (est. sk_executor_deq_get)
 * Ghidra: undefined1 * FUN_003fca14(void)
 * Lazily initialises the executor dequeue (when DAT_006c0b50 != -1) and
 * returns &DAT_006adf50. Confidence: low. */
static uint64_t sk_x_003fca14(void)
{
    if (sk_g_006c0b50 != (uint64_t)-1) {
        sk_x_00406c3c();
        sk_x_0039a128();
    }
    return (uint64_t)&sk_g_006adf50;
}

/* FUN_003fca4c @ 0x003fca4c  (est. sk_executor_deq_release)
 * Ghidra: void FUN_003fca4c(void)
 * Lazily initialises the executor dequeue then releases DAT_006adf50 via
 * FUN_0036b270. Confidence: low. */
static void sk_x_003fca4c(void)
{
    if (sk_g_006c0b50 != (uint64_t)-1) {
        sk_x_00406c3c();
        sk_x_0039a128();
    }
    sk_x_0036b270(sk_g_006adf50);
}

/* FUN_003fca94 @ 0x003fca94  (est. sk_executor_core_release_indirect)
 * Ghidra: void FUN_003fca94(void)
 * Dereferences the core pointer from FUN_003fc950() and releases the word via
 * FUN_0036b270. Confidence: low. */
static void sk_x_003fca94(void)
{
    uint64_t *puVar1 = (uint64_t *)(uintptr_t)sk_x_003fc950();
    sk_x_0036b270(*puVar1);
}

/* FUN_003fcac8 @ 0x003fcac8  (est. sk_executor_deq_release_indirect)
 * Ghidra: void FUN_003fcac8(void)
 * Dereferences the dequeue pointer from FUN_003fca14() and releases the word
 * via FUN_0036b270. Confidence: low. */
static void sk_x_003fcac8(void)
{
    uint64_t *puVar1 = (uint64_t *)(uintptr_t)sk_x_003fca14();
    sk_x_0036b270(*puVar1);
}

/* FUN_003fcafc @ 0x003fcafc  (est. sk_meta_field_10)
 * Ghidra: long FUN_003fcafc(ulong param_1)
 * Tagged-pointer metadata field accessor at offset +0x10: follows the tagged
 * pointer when bit0 is set, then returns (p+0x10) + *(int*)(p+0x10).
 * Confidence: medium (Swift type-metadata pattern). */
static long sk_x_003fcafc(uint64_t param_1)
{
    if ((param_1 & 1) != 0) {
        param_1 = *(uint64_t *)(param_1 & 0xfffffffffffffffeULL);
    }
    return (long)(param_1 + 0x10) + (long)*(int *)(uintptr_t)(param_1 + 0x10);
}

/* FUN_003fcb2c @ 0x003fcb2c  (est. sk_meta_field_14)
 * Ghidra: long FUN_003fcb2c(ulong param_1)
 * Tagged-pointer metadata field accessor at offset +0x14. Confidence: medium. */
static long sk_x_003fcb2c(uint64_t param_1)
{
    if ((param_1 & 1) != 0) {
        param_1 = *(uint64_t *)(param_1 & 0xfffffffffffffffeULL);
    }
    return (long)(param_1 + 0x14) + (long)*(int *)(uintptr_t)(param_1 + 0x14);
}

/* FUN_003fcb5c @ 0x003fcb5c  (est. sk_meta_field_18)
 * Ghidra: long FUN_003fcb5c(ulong param_1)
 * Tagged-pointer metadata field accessor at offset +0x18. Confidence: medium. */
static long sk_x_003fcb5c(uint64_t param_1)
{
    if ((param_1 & 1) != 0) {
        param_1 = *(uint64_t *)(param_1 & 0xfffffffffffffffeULL);
    }
    return (long)(param_1 + 0x18) + (long)*(int *)(uintptr_t)(param_1 + 0x18);
}

/* FUN_003fcb8c @ 0x003fcb8c  (est. sk_meta_field_c)
 * Ghidra: long FUN_003fcb8c(ulong param_1)
 * Tagged-pointer metadata field accessor at offset +0xc. Confidence: medium. */
static long sk_x_003fcb8c(uint64_t param_1)
{
    if ((param_1 & 1) != 0) {
        param_1 = *(uint64_t *)(param_1 & 0xfffffffffffffffeULL);
    }
    return (long)(param_1 + 0xc) + (long)*(int *)(uintptr_t)(param_1 + 0xc);
}

/* FUN_003fcbbc @ 0x003fcbbc  (est. sk_meta_field_8)
 * Ghidra: long FUN_003fcbbc(ulong param_1)
 * Tagged-pointer metadata field accessor at offset +8. Confidence: medium. */
static long sk_x_003fcbbc(uint64_t param_1)
{
    if ((param_1 & 1) != 0) {
        param_1 = *(uint64_t *)(param_1 & 0xfffffffffffffffeULL);
    }
    return (long)(param_1 + 8) + (long)*(int *)(uintptr_t)(param_1 + 8);
}

/* FUN_003fcc1c @ 0x003fcc1c  (est. sk_meta_field_10_b)
 * Ghidra: long FUN_003fcc1c(ulong param_1)
 * Tagged-pointer metadata field accessor at offset +0x10. Confidence: medium. */
static long sk_x_003fcc1c(uint64_t param_1)
{
    if ((param_1 & 1) != 0) {
        param_1 = *(uint64_t *)(param_1 & 0xfffffffffffffffeULL);
    }
    return (long)(param_1 + 0x10) + (long)*(int *)(uintptr_t)(param_1 + 0x10);
}

/* FUN_003fcc4c @ 0x003fcc4c  (est. sk_meta_field_14_b)
 * Ghidra: long FUN_003fcc4c(ulong param_1)
 * Tagged-pointer metadata field accessor at offset +0x14. Confidence: medium. */
static long sk_x_003fcc4c(uint64_t param_1)
{
    if ((param_1 & 1) != 0) {
        param_1 = *(uint64_t *)(param_1 & 0xfffffffffffffffeULL);
    }
    return (long)(param_1 + 0x14) + (long)*(int *)(uintptr_t)(param_1 + 0x14);
}

/* FUN_003fccc4 @ 0x003fccc4  (est. sk_x_003fccc4)
 * Ghidra: void FUN_003fccc4(long param_1, undefined8 param_2)
 * Releases param_2 via FUN_0036b270 when param_1 != 0. Confidence: low. */
static void sk_x_003fccc4(int64_t param_1, uint64_t param_2)
{
    if (param_1 != 0) {
        sk_x_0036b270(param_2);
    }
}

/* FUN_003fccd4 @ 0x003fccd4  (est. sk_x_003fccd4)
 * Ghidra: void FUN_003fccd4(void)
 * Forwarder to FUN_00021480. Confidence: low. */
static void sk_x_003fccd4(void)
{
    sk_x_00021480();
}

/* FUN_003fcd04 @ 0x003fcd04  (est. sk_x_003fcd04)
 * Ghidra: void FUN_003fcd04(void)
 * Identical body to FUN_003fccd4 (distinct code address). Confidence: low. */
static void sk_x_003fcd04(void)
{
    sk_x_00021480();
}

/* FUN_003fcddc @ 0x003fcddc  (est. sk_vas_op_dispatch_cddc)
 * Ghidra: void FUN_003fcddc(void)
 * VAS dispatch: reads a five-word context, allocates a frame pair (backlinked
 * to DAT_00405fa0), resolves the dispatch target from DAT_005a0030 and runs it.
 * Confidence: low (register-forwarded ABI). */
static void sk_x_003fcddc(void)
{
    uint64_t uVar1, uVar2, uVar3, uVar4, uVar5;
    uint64_t *puVar6;
    uint64_t extraout_x1 = /* extraout_x1 */ 0;
    code *pcVar7;
    uint64_t extraout_x17 = /* extraout_x17 */ 0;
    long unaff_x20 = /* unaff_x20 */ 0;

    sk_x_00408058();
    uVar5 = sk_x_0040700c();
    uVar1 = *(uint64_t *)(unaff_x20 + 0x10);
    uVar3 = *(uint64_t *)(unaff_x20 + 0x18);
    uVar2 = *(uint64_t *)(unaff_x20 + 0x20);
    uVar4 = *(uint64_t *)(unaff_x20 + 0x28);
    sk_x_0040bb18(sk_g_005a0034);
    puVar6 = (uint64_t *)sk_x_00407ac4();
    *puVar6 = extraout_x17;
    puVar6[1] = (uint64_t)&sk_g_00405fa0;
    pcVar7 = (code *)(uintptr_t)((uint64_t)&sk_g_005a0030 + sk_g_005a0030);
    sk_x_00408044(uVar5, uVar2, uVar4, uVar1, uVar3, (uint64_t)(uintptr_t)pcVar7, extraout_x1);
    ((void (*)(void))(uintptr_t)pcVar7)();
}

/* FUN_003fce98 @ 0x003fce98  (est. sk_vas_op_dispatch_ce98)
 * Ghidra: void FUN_003fce98(void)
 * VAS dispatch via jumptable: sets up a frame pair (backlinked to DAT_00405fa0),
 * resolves the jump target from unaff_x27, then performs an unrecovered
 * indirect jump. Confidence: low. */
static void sk_x_003fce98(void)
{
    uint64_t *puVar1;
    code *UNRECOVERED_JUMPTABLE;
    uint64_t extraout_x17 = /* extraout_x17 */ 0;
    int *unaff_x27 = /* unaff_x27 */ 0;
    uint64_t unaff_x30 = /* unaff_x30 */ 0;

    sk_x_00408190();
    sk_x_004070d8();
    sk_x_0008409c();
    sk_x_00407e3c();
    puVar1 = (uint64_t *)sk_x_00407ac4();
    *puVar1 = extraout_x17;
    puVar1[1] = (uint64_t)&sk_g_00405fa0;
    UNRECOVERED_JUMPTABLE = (code *)(uintptr_t)((long)*unaff_x27 + (long)unaff_x27);
    sk_x_00084180();
    sk_x_00407f84();
    sk_x_00408178(unaff_x30);
    /* WARNING: jumptable at 0x003fcf20 unrecovered; indirect jump as call. */
    ((void (*)(void))(uintptr_t)UNRECOVERED_JUMPTABLE)();
}

/* FUN_003fcf28 @ 0x003fcf28  (est. sk_vas_op_accept)
 * Ghidra: unsigned int FUN_003fcf28(undefined8 param_1, undefined8 param_2)
 * Classifies a VAS op via FUN_003e33d8 over the unaff_x20 context; returns
 * bit0 of the result. Confidence: low. */
static unsigned int sk_x_003fcf28(uint64_t param_1, uint64_t param_2)
{
    unsigned int uVar1;
    long unaff_x20 = /* unaff_x20 */ 0;

    uVar1 = sk_x_003e33d8(param_1, param_2, *(uint64_t *)(unaff_x20 + 0x28),
                          *(uint64_t *)(unaff_x20 + 0x10), *(uint64_t *)(unaff_x20 + 0x18),
                          *(uint64_t *)(unaff_x20 + 0x20));
    return uVar1 & 1;
}

/* FUN_003fcf48 @ 0x003fcf48  (est. sk_vas_op_dispatch_cf48)
 * Ghidra: void FUN_003fcf48(void)
 * VAS dispatch via jumptable; frame pair backlinked to LAB_003fcfd4, target
 * resolved from unaff_x27. Confidence: low. */
static void sk_x_003fcf48(void)
{
    uint64_t *puVar1;
    code *UNRECOVERED_JUMPTABLE;
    uint64_t extraout_x17 = /* extraout_x17 */ 0;
    int *unaff_x27 = /* unaff_x27 */ 0;
    uint64_t unaff_x30 = /* unaff_x30 */ 0;

    sk_x_00408190();
    sk_x_004070d8();
    sk_x_0008409c();
    sk_x_00407e3c();
    puVar1 = (uint64_t *)sk_x_00407ac4();
    *puVar1 = extraout_x17;
    puVar1[1] = 0x003fcfd4;   /* LAB_003fcfd4 */
    UNRECOVERED_JUMPTABLE = (code *)(uintptr_t)((long)*unaff_x27 + (long)unaff_x27);
    sk_x_00084180();
    sk_x_00407f84();
    sk_x_00408178(unaff_x30);
    /* WARNING: jumptable at 0x003fcfd0 unrecovered; indirect jump as call. */
    ((void (*)(void))(uintptr_t)UNRECOVERED_JUMPTABLE)();
}

/* FUN_003fd0bc @ 0x003fd0bc  (est. sk_x_003fd0bc)
 * Ghidra: void FUN_003fd0bc(void)
 * Forwarder to FUN_00021480. Confidence: low. */
static void sk_x_003fd0bc(void)
{
    sk_x_00021480();
}

/* FUN_003fd194 @ 0x003fd194  (est. sk_meta_field_10_c)
 * Ghidra: long FUN_003fd194(ulong param_1)
 * Tagged-pointer metadata field accessor at offset +0x10. Confidence: medium. */
static long sk_x_003fd194(uint64_t param_1)
{
    if ((param_1 & 1) != 0) {
        param_1 = *(uint64_t *)(param_1 & 0xfffffffffffffffeULL);
    }
    return (long)(param_1 + 0x10) + (long)*(int *)(uintptr_t)(param_1 + 0x10);
}

/* FUN_003fd1c4 @ 0x003fd1c4  (est. sk_vas_op_dispatch_d1c4)
 * Ghidra: void FUN_003fd1c4(void)
 * VAS dispatch: allocates a frame pair at x22 (backlinked to extraout_x17),
 * reads a four-word context and forwards it to FUN_003ed340. Confidence: low. */
static void sk_x_003fd1c4(void)
{
    uint64_t uVar1, uVar2, uVar4, uVar5;
    uint64_t *puVar3;
    uint64_t extraout_x17 = /* extraout_x17 */ 0;
    long unaff_x20 = /* unaff_x20 */ 0;
    long unaff_x22 = /* unaff_x22 */ 0;

    sk_x_00406fd4();
    uVar1 = *(uint64_t *)(unaff_x20 + 0x10);
    uVar2 = *(uint64_t *)(unaff_x20 + 0x18);
    uVar5 = *(uint64_t *)(unaff_x20 + 0x20);
    sk_x_0040bb18(sk_g_005a0134);
    puVar3 = (uint64_t *)sk_x_00406fe0();
    *(uint64_t **)(unaff_x22 + 0x10) = puVar3;
    *puVar3 = extraout_x17;
    uVar4 = sk_x_00407d90();
    sk_x_003ed340(uVar4, uVar2, uVar5, uVar1);
}

/* FUN_003fd25c @ 0x003fd25c  (est. sk_vas_op_forward_d25c)
 * Ghidra: void FUN_003fd25c(undefined8 param_1)
 * Forwards (param_1, *(unaff_x20+0x10)) to FUN_003ed5f8. Confidence: low. */
static void sk_x_003fd25c(uint64_t param_1)
{
    long unaff_x20 = /* unaff_x20 */ 0;

    sk_x_003ed5f8(param_1, *(uint64_t *)(unaff_x20 + 0x10));
}

/* FUN_003fd260 @ 0x003fd260  (est. sk_vas_op_forward_d260)
 * Ghidra: void FUN_003fd260(undefined8 param_1)
 * Identical body to FUN_003fd25c (distinct code address). Confidence: low. */
static void sk_x_003fd260(uint64_t param_1)
{
    long unaff_x20 = /* unaff_x20 */ 0;

    sk_x_003ed5f8(param_1, *(uint64_t *)(unaff_x20 + 0x10));
}

/* FUN_003fd278 @ 0x003fd278  (est. sk_vas_op_dispatch_d278)
 * Ghidra: void FUN_003fd278(void)
 * VAS dispatch via jumptable: allocates a frame pair at x22 (second word =
 * FUN_003eebf0) and performs an unrecovered indirect jump. Confidence: low. */
static void sk_x_003fd278(void)
{
    uint64_t *puVar1;
    code *UNRECOVERED_JUMPTABLE;
    uint64_t extraout_x17 = /* extraout_x17 */ 0;
    long unaff_x22 = /* unaff_x22 */ 0;
    uint64_t unaff_x30 = /* unaff_x30 */ 0;

    sk_x_00407924();
    sk_x_00351a68();
    sk_x_0040bb18(sk_g_005a014c);
    puVar1 = (uint64_t *)sk_x_00406fe0();
    *(uint64_t **)(unaff_x22 + 0x10) = puVar1;
    *puVar1 = extraout_x17;
    puVar1[1] = (uint64_t)sk_x_003eebf0;
    sk_x_004076a8(unaff_x30);
    /* WARNING: jumptable at 0x003fd350 unrecovered; indirect jump as call. */
    ((void (*)(void))(uintptr_t)UNRECOVERED_JUMPTABLE)();
}

/* FUN_003fd3ac @ 0x003fd3ac  (est. sk_vas_op_dispatch_d3ac)
 * Ghidra: void FUN_003fd3ac(undefined8 param_1)
 * VAS dispatch: resolves a target via FUN_001ee018 and forwards to
 * FUN_004ba7ec. Confidence: low. */
static void sk_x_003fd3ac(uint64_t param_1)
{
    uint64_t uVar1, uVar2;
    long unaff_x20 = /* unaff_x20 */ 0;

    uVar2 = *(uint64_t *)(unaff_x20 + 0x20);
    uVar1 = sk_x_001ee018(*(uint64_t *)(unaff_x20 + 0x10), *(uint64_t *)(unaff_x20 + 0x18));
    sk_x_004ba7ec(param_1, uVar1, 1, uVar2);
}

/* FUN_003fd3fc @ 0x003fd3fc  (est. sk_meta_field_18_b)
 * Ghidra: long FUN_003fd3fc(ulong param_1)
 * Tagged-pointer metadata field accessor at offset +0x18. Confidence: medium. */
static long sk_x_003fd3fc(uint64_t param_1)
{
    if ((param_1 & 1) != 0) {
        param_1 = *(uint64_t *)(param_1 & 0xfffffffffffffffeULL);
    }
    return (long)(param_1 + 0x18) + (long)*(int *)(uintptr_t)(param_1 + 0x18);
}

/* FUN_003fd4ac @ 0x003fd4ac  (est. sk_vas_op_pair_d4ac)
 * Ghidra: void FUN_003fd4ac(undefined8 param_1, long param_2)
 * Combines a fresh pair (FUN_004072c0) with param_2 via FUN_00377824, then
 * funnels through FUN_0006b6f4/FUN_00351e3c/FUN_00377bec and FUN_00406d60.
 * Confidence: low. */
static void sk_x_003fd4ac(uint64_t param_1, uint64_t param_2)
{
    uint64_t uVar1, uVar2;
    cl4_result_t auVar3;

    uVar2 = *(uint64_t *)(param_2 + 0x10);
    auVar3 = sk_x_004072c0();
    uVar2 = sk_x_00377824(auVar3.lo, auVar3.hi, uVar2, (uint64_t)&sk_g_00614a5c);
    sk_x_0006b6f4();
    sk_x_00351e3c();
    sk_x_00377bec();
    uVar1 = sk_x_00406d60();
    sk_x_00377bec(uVar1, uVar2, param_1);
}

/* FUN_003fd554 @ 0x003fd554  (est. sk_vas_op_pair_d554)
 * Ghidra: void FUN_003fd554(undefined8 param_1, long param_2)
 * Identical structure to FUN_003fd4ac (register-renamed locals). Confidence: low. */
static void sk_x_003fd554(uint64_t param_1, uint64_t param_2)
{
    uint64_t uVar1, uVar2;
    cl4_result_t auVar3;

    uVar1 = *(uint64_t *)(param_2 + 0x10);
    auVar3 = sk_x_004072c0();
    uVar1 = sk_x_00377824(auVar3.lo, auVar3.hi, uVar1, (uint64_t)&sk_g_00614a5c);
    sk_x_0006b6f4();
    sk_x_00351e3c();
    sk_x_00377bec();
    uVar2 = sk_x_00406d60();
    sk_x_00377bec(uVar2, uVar1, param_1);
}

/* FUN_003fd7bc @ 0x003fd7bc  (est. sk_vas_op_advance_d7bc)
 * Ghidra: void FUN_003fd7bc(void)
 * VAS op advance: steps the descriptor and, on the carry path, copies a
 * two-word pair out of the extraout_x9_00 descriptor into extraout_x8;
 * otherwise releases through FUN_0036b270. Confidence: low. */
static void sk_x_003fd7bc(void)
{
    bool in_ZR;
    uint64_t uVar1, uVar2;
    uint64_t *extraout_x8 = /* extraout_x8 */ 0;
    code *extraout_x9 = /* extraout_x9 */ 0;
    uint64_t *extraout_x9_00 = /* extraout_x9_00 */ 0;
    uint64_t extraout_x10 = /* extraout_x10 */ 0;
    uint64_t extraout_x16 = /* extraout_x16 */ 0;

    sk_x_0034d724();
    sk_x_0040654c();
    sk_x_00377824();
    sk_x_0034b57c();
    sk_x_0035510c(extraout_x16);
    sk_x_0034c144();
    if (in_ZR && extraout_x10 < 0x19) {
        sk_x_00406c08();
        ((void (*)(void))(uintptr_t)extraout_x9)();
        sk_x_00349cd0();
        uVar2 = *extraout_x9_00;
        if (uVar2 < 0x1000 && (uVar2 & 0xffffffff) != 0xffffffff) {
            uVar2 = *extraout_x9_00;
            extraout_x8[1] = extraout_x9_00[1];
            *extraout_x8 = uVar2;
            return;
        }
        uVar1 = extraout_x9_00[1];
        *extraout_x8 = uVar2;
        extraout_x8[1] = uVar1;
    }
    else {
        sk_x_00349a9c();
    }
    sk_x_0036b270();
}

/* FUN_003fd874 @ 0x003fd874  (est. sk_vas_op_advance_d874)
 * Ghidra: void FUN_003fd874(void)
 * VAS op advance: runs the vtable continuation (+8), finalizes, and checks the
 * descriptor bounds. Confidence: low. */
static void sk_x_003fd874(void)
{
    uint64_t uVar1;
    uint64_t extraout_x8 = /* extraout_x8 */ 0;
    uint64_t *extraout_x8_00 = /* extraout_x8_00 */ 0;
    long extraout_x16 = /* extraout_x16 */ 0;

    sk_x_003561f4();
    uVar1 = sk_x_0040654c();
    uVar1 = sk_x_00377824(uVar1, extraout_x8);
    sk_x_0034ab20(uVar1, uVar1);
    ((void (*)(void))(uintptr_t)(*(uint64_t *)(extraout_x16 + 8)))();
    sk_x_0034de54(*(uint64_t *)(extraout_x16 + 0x40));
    if (0xfff < *extraout_x8_00 || (*extraout_x8_00 & 0xffffffff) == 0xffffffff) {
        sk_x_0036b118(extraout_x8_00[1]);
    }
}

/* FUN_003fd8f8 @ 0x003fd8f8  (est. sk_vas_op_advance_d8f8)
 * Ghidra: void FUN_003fd8f8(void)
 * VAS op advance: runs the vtable continuation (+0x10), and selects one of two
 * two-word descriptor copies based on the carry/zero flags. Confidence: low. */
static void sk_x_003fd8f8(void)
{
    bool in_ZR, in_CY;
    uint64_t uVar1;
    uint64_t *extraout_x8 = /* extraout_x8 */ 0;
    uint64_t *extraout_x9 = /* extraout_x9 */ 0;
    uint64_t extraout_x10 = /* extraout_x10 */ 0;
    long extraout_x11 = /* extraout_x11 */ 0;
    long extraout_x16 = /* extraout_x16 */ 0;
    long unaff_x19 = /* unaff_x19 */ 0;

    sk_x_0034d724();
    sk_x_0040654c();
    sk_x_00377824();
    sk_x_00349530();
    ((void (*)(void))(uintptr_t)(*(uint64_t *)(extraout_x16 + 0x10)))();
    sk_x_00407800(*(long *)(extraout_x16 + 0x40) + 7 + unaff_x19 & 0xfffffffffffffff8LL);
    if ((!in_CY || in_ZR) && extraout_x11 != 0xffffffff) {
        uVar1 = *extraout_x9;
        extraout_x8[1] = extraout_x9[1];
        *extraout_x8 = uVar1;
    }
    else {
        uVar1 = extraout_x9[1];
        *extraout_x8 = extraout_x10;
        extraout_x8[1] = uVar1;
        sk_x_0036b270();
    }
}

/* FUN_003fd98c @ 0x003fd98c  (est. sk_vas_op_advance_d98c)
 * Ghidra: void FUN_003fd98c(void)
 * VAS op advance: runs the vtable continuation (+0x18) and conditionally
 * releases/re-copies the two-word descriptor. Confidence: low. */
static void sk_x_003fd98c(void)
{
    bool in_ZR;
    uint64_t uVar1, uVar3;
    uint64_t extraout_x8 = /* extraout_x8 */ 0;
    uint64_t extraout_x10 = /* extraout_x10 */ 0;
    long extraout_x11 = /* extraout_x11 */ 0;
    long extraout_x16 = /* extraout_x16 */ 0;
    uint64_t *puVar2;
    uint64_t *unaff_x20 = /* unaff_x20 */ 0;

    sk_x_0034d724();
    sk_x_0040654c();
    sk_x_00377824();
    sk_x_00349530();
    puVar2 = (uint64_t *)(extraout_x16 + 0x18);
    ((void (*)(void))(uintptr_t)(*puVar2))();
    sk_x_0040767c(*(uint64_t *)(extraout_x16 + 0x40));
    if (extraout_x10 < 0x1000 && extraout_x11 != 0xffffffff) {
        if (in_ZR) {
            uVar1 = unaff_x20[1];
            *puVar2 = extraout_x8;
            *(uint64_t *)(extraout_x16 + 0x20) = uVar1;
            sk_x_0036b270();
            return;
        }
    }
    else {
        if (in_ZR) {
            uVar1 = unaff_x20[1];
            uVar3 = *(uint64_t *)(extraout_x16 + 0x20);
            *puVar2 = extraout_x8;
            *(uint64_t *)(extraout_x16 + 0x20) = uVar1;
            sk_x_0036b270();
            sk_x_0036b118(uVar3);
            return;
        }
        sk_x_0036b118(*(uint64_t *)(extraout_x16 + 0x20));
    }
    uVar1 = *unaff_x20;
    *(uint64_t *)(extraout_x16 + 0x20) = unaff_x20[1];
    *puVar2 = uVar1;
}

/* FUN_003fda44 @ 0x003fda44  (est. sk_vas_op_advance_da44)
 * Ghidra: void FUN_003fda44(void)
 * VAS op advance: runs the vtable continuation (+0x20) and selects one of two
 * two-word descriptor copies based on the carry/zero flags. Confidence: low. */
static void sk_x_003fda44(void)
{
    bool in_ZR, in_CY;
    uint64_t uVar1;
    uint64_t *extraout_x8 = /* extraout_x8 */ 0;
    uint64_t *extraout_x9 = /* extraout_x9 */ 0;
    uint64_t extraout_x10 = /* extraout_x10 */ 0;
    long extraout_x11 = /* extraout_x11 */ 0;
    long extraout_x16 = /* extraout_x16 */ 0;
    long unaff_x19 = /* unaff_x19 */ 0;

    sk_x_0034d724();
    sk_x_0040654c();
    sk_x_00377824();
    sk_x_00349530();
    ((void (*)(void))(uintptr_t)(*(uint64_t *)(extraout_x16 + 0x20)))();
    sk_x_00407800(*(long *)(extraout_x16 + 0x40) + 7 + unaff_x19 & 0xfffffffffffffff8LL);
    if ((!in_CY || in_ZR) && extraout_x11 != 0xffffffff) {
        uVar1 = *extraout_x9;
        extraout_x8[1] = extraout_x9[1];
        *extraout_x8 = uVar1;
    }
    else {
        uVar1 = extraout_x9[1];
        *extraout_x8 = extraout_x10;
        extraout_x8[1] = uVar1;
    }
}

/* FUN_003fdad4 @ 0x003fdad4  (est. sk_vas_op_advance_dad4)
 * Ghidra: void FUN_003fdad4(void)
 * VAS op advance: runs the vtable continuation (+0x28) and conditionally
 * releases/re-copies the two-word descriptor. Confidence: low. */
static void sk_x_003fdad4(void)
{
    bool in_ZR;
    uint64_t uVar1, uVar2;
    uint64_t extraout_x8 = /* extraout_x8 */ 0;
    uint64_t extraout_x10 = /* extraout_x10 */ 0;
    long extraout_x11 = /* extraout_x11 */ 0;
    long extraout_x16 = /* extraout_x16 */ 0;
    uint64_t *puVar3;
    uint64_t *unaff_x20 = /* unaff_x20 */ 0;

    sk_x_0034d724();
    sk_x_0040654c();
    sk_x_00377824();
    sk_x_00349530();
    puVar3 = (uint64_t *)(extraout_x16 + 0x28);
    ((void (*)(void))(uintptr_t)(*puVar3))();
    sk_x_0040767c(*(uint64_t *)(extraout_x16 + 0x40));
    if (extraout_x10 < 0x1000 && extraout_x11 != 0xffffffff) {
        if (in_ZR) {
            uVar1 = unaff_x20[1];
            *puVar3 = extraout_x8;
            *(uint64_t *)(extraout_x16 + 0x30) = uVar1;
            return;
        }
    }
    else {
        if (in_ZR) {
            uVar2 = unaff_x20[1];
            uVar1 = *(uint64_t *)(extraout_x16 + 0x30);
            *puVar3 = extraout_x8;
            *(uint64_t *)(extraout_x16 + 0x30) = uVar2;
            sk_x_0036b118(uVar1);
            return;
        }
        sk_x_0036b118(*(uint64_t *)(extraout_x16 + 0x30));
    }
    uVar1 = *unaff_x20;
    *(uint64_t *)(extraout_x16 + 0x30) = unaff_x20[1];
    *puVar3 = uVar1;
}

/* FUN_003fdb80 @ 0x003fdb80  (est. sk_vas_op_classify)
 * Ghidra: ulong FUN_003fdb80(void)
 * VAS op classifier: bounds-checks the descriptor, then returns the object
 * size/state based on the (register-forwarded) op word, branching on the
 * element width (1/2/4 bytes). Confidence: low. */
static unsigned long sk_x_003fdb80(void)
{
    unsigned int uVar1, uVar9, uVar2, uVar3;
    code *pcVar4;
    bool bVar5, bVar6;
    uint64_t uVar7, uVar8;
    unsigned int extraout_w1 = /* extraout_w1 */ 0;
    unsigned int extraout_w8 = /* extraout_w8 */ 0;
    unsigned int extraout_w12 = /* extraout_w12 */ 0;
    unsigned int extraout_w13 = /* extraout_w13 */ 0;
    long extraout_x8 = /* extraout_x8 */ 0;
    long extraout_x11 = /* extraout_x11 */ 0;
    long extraout_x16 = /* extraout_x16 */ 0;
    long unaff_x19 = /* unaff_x19 */ 0;
    unsigned int unaff_w20 = /* unaff_w20 */ 0;

    sk_x_0034d724();
    sk_x_0040654c();
    sk_x_00377824();
    uVar7 = sk_x_0034ada0();
    uVar9 = *(unsigned int *)(extraout_x16 + 0x54);
    uVar1 = uVar9;
    if (uVar9 < 0x1000) {
        uVar1 = 0xfff;
    }
    if (unaff_w20 == 0) {
        return 0;
    }
    if (uVar1 < unaff_w20) {
        sk_x_00407460(*(uint64_t *)(extraout_x8 + 0x40), uVar7, uVar9, uVar7);
        sk_x_004080bc();
        uVar3 = extraout_w13;
        if (extraout_w12 < 0x100) {
            uVar3 = 1;
        }
        uVar2 = 0;
        if (1 < extraout_w12) {
            uVar2 = uVar3;
        }
        uVar9 = extraout_w1;
        switch (uVar2) {
        case 1:
            if (*(char *)(unaff_x19 + extraout_x11) != '\0') {
LAB_003fdc34:
                sk_x_00407d54();
                uVar8 = sk_x_00356e64();
                return uVar8;
            }
            break;
        case 2:
            if (*(short *)(unaff_x19 + extraout_x11) != 0) goto LAB_003fdc34;
            break;
        case 3:
            /* WARNING: Does not return */
            sk_brk_noret();
        case 4:
            if (*(int *)(unaff_x19 + extraout_x11) != 0) goto LAB_003fdc34;
        }
    }
    bVar5 = 0xffe < uVar9;
    bVar6 = uVar9 == 0xfff;
    if (!bVar5) {
        sk_x_0040692c();
        uVar1 = extraout_w8;
        if (bVar5 && !bVar6) {
            uVar1 = 0xffffffff;
        }
        uVar9 = 0;
        if (1 < uVar1 + 1) {
            uVar9 = uVar1;
        }
        return (unsigned long)uVar9;
    }
    uVar8 = sk_x_000839f8();
    return uVar8;
}

/* FUN_003fde6c @ 0x003fde6c  (est. sk_vas_op_advance_de6c)
 * Ghidra: void FUN_003fde6c(void)
 * VAS op advance: steps the descriptor and, on the carry path, runs the
 * continuation; otherwise releases through FUN_0036b270. Confidence: low. */
static void sk_x_003fde6c(void)
{
    bool in_ZR;
    code *extraout_x9 = /* extraout_x9 */ 0;
    uint64_t extraout_x10 = /* extraout_x10 */ 0;
    uint64_t extraout_x16 = /* extraout_x16 */ 0;

    sk_x_0034d724();
    sk_x_0040654c();
    sk_x_00377824();
    sk_x_0034b57c();
    sk_x_0035510c(extraout_x16);
    sk_x_0034c144();
    if (in_ZR && extraout_x10 < 0x19) {
        sk_x_00406c08();
        ((void (*)(void))(uintptr_t)extraout_x9)();
        sk_x_00349cd0();
        sk_x_003535e4();
    }
    else {
        sk_x_00349a9c();
    }
    sk_x_0036b270();
}

/* FUN_003fdf0c @ 0x003fdf0c  (est. sk_vas_op_advance_df0c)
 * Ghidra: void FUN_003fdf0c(void)
 * VAS op advance: runs the vtable continuation (+0x10) and finalizes.
 * Confidence: low. */
static void sk_x_003fdf0c(void)
{
    long extraout_x16 = /* extraout_x16 */ 0;

    sk_x_0034dbd8();
    sk_x_0040654c();
    sk_x_00377824();
    sk_x_00349530();
    ((void (*)(void))(uintptr_t)(*(uint64_t *)(extraout_x16 + 0x10)))();
    sk_x_00349104(*(uint64_t *)(extraout_x16 + 0x40));
    sk_x_0034f22c();
    sk_x_0036b270();
}

/* FUN_003fdf74 @ 0x003fdf74  (est. sk_vas_op_advance_df74)
 * Ghidra: void FUN_003fdf74(void)
 * VAS op advance: runs the vtable continuation (+0x18) and finalizes.
 * Confidence: low. */
static void sk_x_003fdf74(void)
{
    long extraout_x9 = /* extraout_x9 */ 0;
    long extraout_x16 = /* extraout_x16 */ 0;
    uint64_t uVar1;

    sk_x_0034dbd8();
    sk_x_0040654c();
    sk_x_00377824();
    sk_x_00349530();
    ((void (*)(void))(uintptr_t)(*(uint64_t *)(extraout_x16 + 0x18)))();
    sk_x_00349104(*(uint64_t *)(extraout_x16 + 0x40));
    uVar1 = *(uint64_t *)(extraout_x9 + 8);
    sk_x_0034f22c();
    sk_x_0036b270();
    sk_x_0036b118(uVar1);
}
