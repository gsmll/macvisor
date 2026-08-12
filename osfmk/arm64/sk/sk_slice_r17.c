/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel, GL1,
 * arm64e, image base 0) — the cL4 microkernel. Ground truth: Ghidra FUN_ names +
 * addresses in the cl4_kernel.raw program. Names use seL4/cL4 vocabulary; all
 * are estimates unless string/header matched.
 *
 * Slice 0x00458d68-0x0045bcb0 (worker SKR17): the syscall/trap dispatch and
 * register-fragment marshaling layer — the per-vector shims that capture the
 * caller's register window (x19-x28) plus a small type/selector byte on the
 * stack and forward it into a shared message/dispatch helper, the register-
 * fragment store helpers that append one or more saved registers to the
 * in-flight syscall frame, the pair of operation-frame copy / swap functions,
 * and the message-buffer address walking helpers.
 */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "sk_internal.h"

/* ------------------------------------------------------------------ *
 * Hardware / intrinsic helpers (same semantics as the Ghidra pseudo-ops
 * used in the decompiles).
 * ------------------------------------------------------------------ */
static inline unsigned sk_clz64(uint64_t x) { return (unsigned)__builtin_clzll(x); }
#define LZCOUNT(x) sk_clz64((uint64_t)(x))
static inline void sk_callsup(uint64_t kind)
{ __asm__ volatile("svc %0" : : "i"(0)); (void)kind; }
#define CallSupervisor(k) sk_callsup((uint64_t)(k))
static inline void sk_break(uint64_t a, uint64_t b) __attribute__((noreturn))
{ (void)a; (void)b; __asm__ volatile("brk #1"); }
#define SoftwareBreakpoint(a,b) sk_break((uint64_t)(a),(uint64_t)(b))
#define SK_CANARY (-0x2c8502b44bfffed6LL)

/* 16-byte result pair used by several out-of-slice helpers (lo = x0, hi = x1). */
typedef struct sk_pair { uint64_t lo; uint64_t hi; } sk_pair_t;

/* Low-60-bit pointer tag mask (used to strip capability/tag bits). */
#define SK_TAG_MASK 0x0FFFFFFFFFFFFFFFULL

/* ------------------------------------------------------------------ *
 * Shared globals referenced by this slice (image-base addresses are the
 * Ghidra ground truth).
 * ------------------------------------------------------------------ */
extern uint8_t  sk_g_005a2018;          /* DAT_005a2018 (message/string area) */
extern uint8_t  sk_g_005a26cc;          /* DAT_005a26cc */
extern uint8_t  sk_g_004ea7c8;          /* DAT_004ea7c8 */
extern uint8_t  sk_g_0045961c;          /* DAT_0045961c */
extern uint8_t  sk_g_004eb078;          /* DAT_004eb078 */
extern uint8_t  sk_g_005a2cb0;          /* DAT_005a2cb0 */
extern uint8_t  sk_g_004ea794;          /* DAT_004ea794 */
extern uint8_t  sk_g_004eb028;          /* DAT_004eb028 */
extern uint8_t  sk_g_005a2ca8;          /* DAT_005a2ca8 */
extern uint8_t  sk_g_0064c2e0;          /* DAT_0064c2e0 */
extern uint8_t  sk_g_004ea760;          /* DAT_004ea760 */
extern uint8_t  sk_g_0064c2d8;          /* DAT_0064c2d8 */
extern uint8_t  sk_g_004bbe30;          /* DAT_004bbe30 */
extern uint8_t  sk_g_005a2db0;          /* DAT_005a2db0 */
extern uint8_t  sk_g_005a2e08;          /* DAT_005a2e08 */
extern uint8_t  sk_g_005a2e60;          /* DAT_005a2e60 */
extern uint8_t  sk_g_005a2eb8;          /* DAT_005a2eb8 */
extern uint8_t  sk_g_005a2f10;          /* DAT_005a2f10 */
extern uint64_t sk_g_00657a60;          /* uRam 0x00657a60 (written) */
extern uint64_t sk_g_00657a68;          /* uRam 0x00657a68 (written) */
extern uint64_t sk_g_00657a78;          /* uRam 0x00657a78 (written) */

/* ------------------------------------------------------------------ *
 * Out-of-slice callees (reconstructed by other slice workers). The
 * sk_x_XXXXXXXX names encode the Ghidra FUN_ address. Functions that
 * return a 16-byte pair are declared as sk_pair_t.
 * ------------------------------------------------------------------ */
extern unsigned long sk_x_0001a1cc();   /* FUN_0001a1cc */
extern unsigned long sk_x_00021480();   /* FUN_00021480 */
extern sk_pair_t     sk_x_00002534();   /* FUN_00002534 */
extern unsigned long sk_x_00002834();   /* FUN_00002834 */
extern unsigned long sk_x_00002850();   /* FUN_00002850 */
extern unsigned long sk_x_00027614();   /* FUN_00027614 */
extern sk_pair_t     sk_x_00027670();   /* FUN_00027670 */
extern unsigned long sk_x_00027754();   /* FUN_00027754 */
extern unsigned long sk_x_0006b6f4();   /* FUN_0006b6f4 */
extern unsigned long sk_x_00084220();   /* FUN_00084220 */
extern unsigned long sk_x_00084234();   /* FUN_00084234 */
extern unsigned long sk_x_0010a9f8();   /* FUN_0010a9f8 */
extern unsigned long sk_x_00114330();   /* thunk_FUN_00114330 */
extern unsigned long sk_x_0034b264();   /* FUN_0034b264 */
extern unsigned long sk_x_0034c444();   /* FUN_0034c444 */
extern unsigned long sk_x_0034d454();   /* FUN_0034d454 */
extern unsigned long sk_x_0034db28();   /* FUN_0034db28 */
extern sk_pair_t     sk_x_0034f2f4();   /* FUN_0034f2f4 (16-byte result) */
extern unsigned long sk_x_0034f3b4();   /* FUN_0034f3b4 */
extern unsigned long sk_x_0034f8e4();   /* FUN_0034f8e4 */
extern unsigned long sk_x_00350af4();   /* FUN_00350af4 */
extern unsigned long sk_x_003509c8();   /* FUN_003509c8 */
extern unsigned long sk_x_00350c5c();   /* FUN_00350c5c */
extern unsigned long sk_x_00350e04();   /* FUN_00350e04 */
extern unsigned long sk_x_003504d0();   /* FUN_003504d0 */
extern sk_pair_t     sk_x_00352b20();   /* FUN_00352b20 (16-byte result) */
extern unsigned long sk_x_00355538();   /* FUN_00355538 */
extern unsigned long sk_x_00355938();   /* FUN_00355938 */
extern unsigned long sk_x_00355968();   /* FUN_00355968 */
extern unsigned long sk_x_0036b118();   /* FUN_0036b118 */
extern unsigned long sk_x_0036b21c();   /* FUN_0036b21c */
extern unsigned long sk_x_0036b270();   /* FUN_0036b270 */
extern unsigned long sk_x_00376820();   /* FUN_00376820 */
extern unsigned long sk_x_003a25d4();   /* FUN_003a25d4 */
extern unsigned long sk_x_00455574();   /* FUN_00455574 */
extern unsigned long sk_x_00458940();   /* FUN_00458940 */
extern unsigned long sk_x_00458bac();   /* FUN_00458bac */
extern unsigned long sk_x_00458b94();   /* FUN_00458b94 */
extern unsigned long sk_x_0045e45c();   /* FUN_0045e45c */
extern unsigned long sk_x_0045e484();   /* FUN_0045e484 */
extern unsigned long sk_x_0045ee90();   /* FUN_0045ee90 */
extern unsigned long sk_x_0045fc8c();   /* FUN_0045fc8c */
extern unsigned long sk_x_004607c4();   /* FUN_004607c4 */
extern unsigned long sk_x_00460ae4();   /* FUN_00460ae4 */
extern unsigned long sk_x_00460d50();   /* FUN_00460d50 */
extern unsigned long sk_x_00461dc4();   /* thunk_FUN_00461dc4 */
extern unsigned long sk_x_00462758();   /* FUN_00462758 */
extern unsigned long sk_x_004627d0();   /* FUN_004627d0 */
extern unsigned long sk_x_00462848();   /* FUN_00462848 */
extern unsigned long sk_x_00462948();   /* FUN_00462948 */
extern unsigned long sk_x_00462b90();   /* FUN_00462b90 */
extern unsigned long sk_x_00462bd8();   /* FUN_00462bd8 */
extern unsigned long sk_x_00462e54();   /* FUN_00462e54 */
extern unsigned long sk_x_00462e88();   /* FUN_00462e88 */
extern unsigned long sk_x_00462fec();   /* FUN_00462fec */
extern sk_pair_t     sk_x_00463028();   /* FUN_00463028 (16-byte result) */
extern unsigned long sk_x_0046303c();   /* FUN_0046303c */
extern unsigned long sk_x_00463058();   /* FUN_00463058 */
extern sk_pair_t     sk_x_0046306c();   /* FUN_0046306c (16-byte result) */
extern unsigned long sk_x_00463080();   /* FUN_00463080 */
extern unsigned long sk_x_00463154();   /* FUN_00463154 */
extern unsigned long sk_x_004632b8();   /* FUN_004632b8 */
extern unsigned long sk_x_00463358();   /* FUN_00463358 */
extern unsigned long sk_x_0046337c();   /* FUN_0046337c */
extern unsigned long sk_x_00463484();   /* FUN_00463484 */
extern unsigned long sk_x_00463504();   /* FUN_00463504 */
extern unsigned long sk_x_00463750();   /* FUN_00463750 */
extern unsigned long sk_x_004638d8();   /* FUN_004638d8 */
extern unsigned long sk_x_00463a10();   /* FUN_00463a10 */
extern unsigned long sk_x_00463a48();   /* FUN_00463a48 */
extern unsigned long sk_x_00463aa0();   /* FUN_00463aa0 */
extern unsigned long sk_x_004640b8();   /* FUN_004640b8 */
extern unsigned long sk_x_004640d0();   /* FUN_004640d0 */
extern unsigned long sk_x_004644cc();   /* FUN_004644cc */
extern unsigned long sk_x_00464504();   /* FUN_00464504 */
extern unsigned long sk_x_004645d8();   /* FUN_004645d8 */
extern unsigned long sk_x_00464ae8();   /* FUN_00464ae8 */
extern unsigned long sk_x_00464b04();   /* FUN_00464b04 */
extern unsigned long sk_x_00464dcc();   /* FUN_00464dcc */
extern unsigned long sk_x_00464e9c();   /* FUN_00464e9c */
extern unsigned long sk_x_00464f40();   /* FUN_00464f40 */
extern unsigned long sk_x_004653cc();   /* FUN_004653cc */
extern unsigned long sk_x_004654ec();   /* FUN_004654ec */
extern unsigned long sk_x_004656e0();   /* FUN_004656e0 */
extern unsigned long sk_x_00465770();   /* FUN_00465770 */
extern unsigned long sk_x_00465884();   /* FUN_00465884 */
extern unsigned long sk_x_00465a50();   /* FUN_00465a50 */
extern unsigned long sk_x_00465b1c();   /* FUN_00465b1c */
extern unsigned long sk_x_00465d28();   /* FUN_00465d28 */
extern unsigned long sk_x_00465eec();   /* FUN_00465eec */
extern unsigned long sk_x_00465f20();   /* FUN_00465f20 */
extern unsigned long sk_x_00465f68();   /* FUN_00465f68 */
extern unsigned long sk_x_00466034();   /* FUN_00466034 */
extern unsigned long sk_x_004661a4();   /* FUN_004661a4 */
extern unsigned long sk_x_004661fc();   /* FUN_004661fc */
extern unsigned long sk_x_00466220();   /* FUN_00466220 */
extern unsigned long sk_x_00466374();   /* FUN_00466374 */
extern unsigned long sk_x_004663ec();   /* FUN_004663ec */
extern sk_pair_t     sk_x_00466408();   /* FUN_00466408 (16-byte result) */
extern unsigned long sk_x_004666c0();   /* FUN_004666c0 */
extern unsigned long sk_x_004588cc();   /* FUN_004588cc */
extern void          sk_x_0045c89c();   /* FUN_0045c89c */

/* ------------------------------------------------------------------ *
 * Local forward declarations (defined later in this slice).
 * ------------------------------------------------------------------ */
static void sk_dispatch_00458f00(uint64_t arg0, uint64_t arg1, uint64_t arg2,
                                 uint64_t arg3, uint64_t sel);
static void sk_dispatch_00458f9c(uint64_t arg0, uint64_t arg1, uint64_t arg2,
                                 uint64_t arg3, uint64_t sel);
static void sk_dispatch_00459280(uint64_t arg0, uint64_t arg1, uint64_t arg2,
                                 uint64_t arg3, uint64_t mode);
static void sk_dispatch_004592dc(uint64_t arg0, uint64_t arg1, uint64_t arg2,
                                 uint64_t arg3, uint64_t mode);
static void sk_dispatch_004592f4(uint64_t arg0, uint64_t arg1, uint64_t arg2,
                                 uint64_t arg3, uint64_t x7, uint64_t st18,
                                 uint64_t st30, uint64_t mode);
static uint64_t sk_dispatch_00459698(void);
static void sk_dispatch_00459768(uint64_t key, uint64_t *producer, uint64_t *area);
static uint64_t sk_dispatch_00459800(void);
static void sk_dispatch_00459888(uint64_t *key, uint64_t *area);
static void sk_dispatch_0045a5fc(uint64_t arg0, uint64_t arg1, uint64_t arg2,
                                 uint64_t arg3, uint64_t mode);
static void sk_dispatch_0045a658(uint64_t arg0, uint64_t arg1, uint64_t arg2,
                                 uint64_t arg3, uint64_t x7, uint64_t st18,
                                 uint64_t st30, uint64_t mode);
static void sk_dispatch_0045b1a0(uint64_t arg0, uint64_t arg1, uint64_t handler);

/* ------------------------------------------------------------------ *
 * Register-fragment marshaling shims (first block).
 * ------------------------------------------------------------------ */

/* FUN_00458d68 @ 0x00458d68   (est. sk_dispatch_00458d68)
 * Ghidra: void FUN_00458d68(undefined8 param_1, undefined8 param_2)
 * Argument-swapping thunk: forwards the two caller words to the shared
 * dispatch helper with their order reversed.
 * Confidence: low
 * Notes: pure arg-reorder shim; callee 0045e484 out-of-slice. */
static void sk_dispatch_00458d68(uint64_t arg0, uint64_t arg1)
{
    sk_x_0045e484(arg1, arg0);
}

/* FUN_00458d78 @ 0x00458d78   (est. sk_dispatch_00458d78)
 * Ghidra: undefined8 FUN_00458d78(undefined8 param_1)
 * Calls the shared dispatch helper with no arguments, then returns its own
 * first argument unchanged (a pass-through of the leading register).
 * Confidence: low
 * Notes: callee 0045e45c out-of-slice. */
static uint64_t sk_dispatch_00458d78(uint64_t arg0)
{
    sk_x_0045e45c();
    return arg0;
}

/* FUN_00458da0 @ 0x00458da0   (est. sk_dispatch_00458da0)
 * Ghidra: void FUN_00458da0(undefined8 param_1, undefined8 param_2)
 * Argument-swapping thunk forwarding to 0045ee90 (mirror of 00458d68).
 * Confidence: low */
static void sk_dispatch_00458da0(uint64_t arg0, uint64_t arg1)
{
    sk_x_0045ee90(arg1, arg0);
}

/* FUN_00458db4 @ 0x00458db4   (est. sk_dispatch_00458db4)
 * Ghidra: void FUN_00458db4(undefined8 param_1..4, char in_stack_00000010)
 * Dispatches on a 1-byte mode word in the caller's stack frame (x7 and the
 * stack word are the raw caller registers): mode 2 forwards both x7 and
 * param_4 to the "push message word" helper; mode 1 forwards x7; mode 0
 * forwards param_2. Any other mode is ignored.
 * Confidence: low
 * Notes: in_x7/in_stack_00000010 are register/stack artifacts of the
 *   caller's window; helpers 0036b118 / 003a25d4 out-of-slice. */
static void sk_dispatch_00458db4(uint64_t arg0, uint64_t arg1, uint64_t arg2,
                                 uint64_t arg3, uint64_t x7, uint64_t stack_word)
{
    uint64_t mode = stack_word & 0xff;

    if (mode == 2) {
        sk_x_0036b118(arg3);
        sk_x_0036b118(x7);
        return;
    }
    if (mode == 1) {
        sk_x_003a25d4(x7);
    } else if (mode != 0) {
        return;
    }
    sk_x_003a25d4(arg1);
}

/* FUN_00458e28 @ 0x00458e28   (est. sk_dispatch_00458e28)
 * Ghidra: undefined8 FUN_00458e28(undefined8 param_1)
 * Pass-through shim: runs the 0045c89c helper (no args) and returns param_1.
 * Confidence: low
 * Notes: callee is a thunk target. */
static uint64_t sk_dispatch_00458e28(uint64_t arg0)
{
    sk_x_0045c89c();
    return arg0;
}

/* FUN_00458e50 @ 0x00458e50   (est. sk_list_next_00458e50)
 * Ghidra: long FUN_00458e50(ulong param_1)
 * Walks a tagged linked node: if the low bit is set the pointer is indirect
 * (the tag stores the next pointer at the cleared address); returns
 * node + 8 + 4-byte length field at +8, i.e. the first element after an
 * 8-byte header with a 4-byte count. Classic cL4 list/message-buffer walk.
 * Confidence: medium
 * Notes: pointer-tag decode (param_1 & ~1). */
static uint64_t sk_list_next_00458e50(uint64_t node)
{
    if ((node & 1) != 0) {
        node = *(uint64_t *)(node & ~1ULL);
    }
    return (uint64_t)(node + 8) + (uint64_t)*(int32_t *)(node + 8);
}

/* FUN_00458e80 @ 0x00458e80   (est. sk_dispatch_00458e80)
 * Ghidra: void FUN_00458e80(undefined8 param_1..3, char param_4)
 * Mode switch on a 1-byte word: mode 1 or 2 pushes no argument into the
 * message helper (0036b118); mode 0 pushes param_2; any other mode is
 * ignored. Complement of 00458db4.
 * Confidence: low
 * Notes: helpers out-of-slice. */
static void sk_dispatch_00458e80(uint64_t arg0, uint64_t arg1, uint64_t arg2,
                                 uint64_t mode)
{
    if ((mode != 2) && (mode != 1)) {
        if (mode == 0) {
            sk_x_003a25d4(arg1);
            return;
        }
        return;
    }
    sk_x_0036b118();
}

/* FUN_00458ea8 @ 0x00458ea8   (est. sk_frame_copy_00458ea8)
 * Ghidra: void FUN_00458ea8(undefined8 *param_1, undefined8 *param_2)
 * Copies a 5-word (40-byte) message/context frame from param_1 to param_2
 * word-for-word, then runs the 0001a1cc epilogue helper.
 * Confidence: low
 * Notes: callee 0001a1cc out-of-slice. */
static void sk_frame_copy_00458ea8(uint64_t *src, uint64_t *dst)
{
    uint64_t w1, w2, w3, w4;

    w2 = src[1];
    w1 = src[0];
    w4 = src[3];
    w3 = src[2];
    dst[4] = src[4];
    dst[1] = w2;
    dst[0] = w1;
    dst[3] = w4;
    dst[2] = w3;
    sk_x_0001a1cc();
}

/* FUN_00458ebc @ 0x00458ebc   (est. sk_list_next_00458ebc)
 * Ghidra: long FUN_00458ebc(ulong param_1)
 * Same tagged-node walk as 00458e50 but with a 12-byte header: returns
 * node + 0xc + 4-byte count at +0xc.
 * Confidence: medium */
static uint64_t sk_list_next_00458ebc(uint64_t node)
{
    if ((node & 1) != 0) {
        node = *(uint64_t *)(node & ~1ULL);
    }
    return (uint64_t)(node + 0xc) + (uint64_t)*(int32_t *)(node + 0xc);
}

/* FUN_00458eec @ 0x00458eec   (est. sk_dispatch_00458eec)
 * Ghidra: void FUN_00458eec(void)
 * Entry gate: if the caller's w4 (mode byte) is not 0xffffffff (-1) it
 * forwards into the 00458f00 mode dispatcher, otherwise returns immediately.
 * Confidence: low
 * Notes: in_w4 register artifact. */
static void sk_dispatch_00458eec(void)
{
    uint32_t mode = 0;   /* in_w4 register artifact */

    if (mode != 0xffffffffu) {
        sk_dispatch_00458f00(0, 0, 0, 0, 0);
        return;
    }
}

/* FUN_00458f00 @ 0x00458f00   (est. sk_dispatch_00458f00)
 * Ghidra: void FUN_00458f00(undefined8 param_1..4, uint param_5)
 * Mode dispatcher: for a selector < 0x24, checks bitmask 0x363fbff5f of the
 * selector to pick the register-forwarding path, and pushes either param_2
 * (default) or param_4 (when bit 0x800040000 is set) through 0036b270.
 * Selectors >= 0x24 are ignored.
 * Confidence: low
 * Notes: bitmask dispatch of syscall-mode bits; helper 0036b270 thunked. */
static void sk_dispatch_00458f00(uint64_t arg0, uint64_t arg1, uint64_t arg2,
                                 uint64_t arg3, uint64_t sel)
{
    if (0x23 < (sel & 0xff)) {
        return;
    }
    if (((1ULL << (sel & 0x3f)) & 0x363fbff5fULL) == 0) {
        if (((1ULL << (sel & 0x3f)) & 0x800040000ULL) == 0) {
            return;
        }
        sk_x_0036b270(arg1);
        arg1 = arg3;
    }
    sk_x_0036b270(arg1);
}

/* FUN_00458f88 @ 0x00458f88   (est. sk_dispatch_00458f88)
 * Ghidra: void FUN_00458f88(void)
 * Entry gate (mirror of 00458eec) forwarding to 00458f9c when w4 != -1.
 * Confidence: low */
static void sk_dispatch_00458f88(void)
{
    uint32_t mode = 0;   /* in_w4 register artifact */

    if (mode != 0xffffffffu) {
        sk_dispatch_00458f9c(0, 0, 0, 0, 0);
        return;
    }
}

/* FUN_00458f9c @ 0x00458f9c   (est. sk_dispatch_00458f9c)
 * Ghidra: void FUN_00458f9c(undefined8 param_1..4, uint param_5)
 * Selector dispatch (mirror of 00458f00 with a different fallback): for
 * selectors < 0x24 outside bitmask 0x363fbff5f, only selectors 0x12 and
 * 0x23 forward the swapped argument (param_4) through 003a25d4; the default
 * path forwards param_2. Selectors >= 0x24 ignored.
 * Confidence: low */
static void sk_dispatch_00458f9c(uint64_t arg0, uint64_t arg1, uint64_t arg2,
                                 uint64_t arg3, uint64_t sel)
{
    uint64_t u;
    uint64_t s;

    if (0x23 < (sel & 0xff)) {
        return;
    }
    s = sel & 0xff;
    if (((1ULL << (sel & 0x3f)) & 0x363fbff5fULL) == 0) {
        u = arg3;
        if ((s != 0x12) && (u = arg1, arg1 = arg3, s != 0x23)) {
            return;
        }
        sk_x_003a25d4(u);
    }
    sk_x_003a25d4(arg1);
}

/* FUN_00459024 @ 0x00459024   (est. sk_dispatch_00459024)
 * Ghidra: void FUN_00459024(undefined8 param_1, undefined8 param_2)
 * Argument-swapping thunk forwarding to 00461dc4.
 * Confidence: low */
static void sk_dispatch_00459024(uint64_t arg0, uint64_t arg1)
{
    sk_x_00461dc4(arg1, arg0);
}

/* FUN_00459034 @ 0x00459034   (est. sk_dispatch_00459034)
 * Ghidra: void FUN_00459034(void)
 * Trivial thunk: calls the 00021480 helper with no arguments.
 * Confidence: low */
static void sk_dispatch_00459034(void)
{
    sk_x_00021480();
}

/* FUN_0045904c @ 0x0045904c   (est. sk_dispatch_0045904c)
 * Ghidra: undefined8 FUN_0045904c(undefined8 param_1)
 * Pass-through: runs 00460ae4 (no args), returns param_1 unchanged.
 * Confidence: low */
static uint64_t sk_dispatch_0045904c(uint64_t arg0)
{
    sk_x_00460ae4();
    return arg0;
}

/* FUN_00459074 @ 0x00459074   (est. sk_dispatch_00459074)
 * Ghidra: void FUN_00459074(void)
 * Trivial thunk to 00021480 (identical to 00459034; paired copy).
 * Confidence: low */
static void sk_dispatch_00459074(void)
{
    sk_x_00021480();
}

/* FUN_0045908c @ 0x0045908c   (est. sk_dispatch_0045908c)
 * Ghidra: void FUN_0045908c(void)
 * Composite dispatch: runs 003504d0 and 00355968 setup helpers, obtains a
 * 16-byte descriptor from 00002534, forwards all halves plus the descriptor
 * pointer into 003509c8, then tail-calls the recovered function pointer at
 * offset +0x10 of the extraout_x16 vtable.
 * Confidence: low
 * Notes: extraout_x16 is a function-pointer vtable artifact; the tail call
 *   is an unrecovered indirect branch. */
static void sk_dispatch_0045908c(void)
{
    uint64_t u;
    void (*tail_fn)(void) = 0;  /* extraout_x16 + 0x10 */
    sk_pair_t d;

    sk_x_003504d0();
    sk_x_00355968();
    d = sk_x_00002534();
    u = d.lo;
    sk_x_003509c8(u, u, d.hi, u);
    tail_fn = (void (*)(void))0;  /* (**(code **)(extraout_x16 + 0x10))() unrecovered */
}

/* FUN_004590e0 @ 0x004590e0   (est. sk_dispatch_004590e0)
 * Ghidra: undefined8 FUN_004590e0(undefined8 param_1)
 * Pass-through: runs 0045fc8c (no args), returns param_1.
 * Confidence: low */
static uint64_t sk_dispatch_004590e0(uint64_t arg0)
{
    sk_x_0045fc8c();
    return arg0;
}

/* FUN_0045910c @ 0x0045910c   (est. sk_dispatch_0045910c)
 * Ghidra: void FUN_0045910c(void)
 * Register-fragment shim: pushes the word at x20+0x28 (the current context
 * register window) through 0036b118, runs 00002850, then the 0036b21c
 * frame-completion helper.
 * Confidence: low
 * Notes: unaff_x20 = running context; paired copy is 00459110. */
static void sk_dispatch_0045910c(void)
{
    uint64_t x20 = 0;   /* unaff_x20: running context */

    sk_x_0036b118(*(uint64_t *)(x20 + 0x28));
    sk_x_00002850();
    sk_x_0036b21c();
}

/* FUN_00459110 @ 0x00459110   (est. sk_dispatch_00459110)
 * Ghidra: void FUN_00459110(void)
 * Identical copy of 0045910c (paired duplicate vector).
 * Confidence: low */
static void sk_dispatch_00459110(void)
{
    uint64_t x20 = 0;   /* unaff_x20: running context */

    sk_x_0036b118(*(uint64_t *)(x20 + 0x28));
    sk_x_00002850();
    sk_x_0036b21c();
}

/* FUN_00459138 @ 0x00459138   (est. sk_dispatch_00459138)
 * Ghidra: void FUN_00459138(undefined8 param_1..8, byte in_stack_00000058)
 * Master syscall-frame dispatcher: switches on the high nibble of a mode byte
 * in the caller's stack frame. 0 = push param_5 (or param_2); 2 = push no
 * args via 0036b118; 3 = 00459280; 9/10 = 004592dc; 0xb = 004592f4;
 * 0xd = push param_4 then param_8; 1/4 = ignored. Frames > 0xd ignored.
 * Confidence: low
 * Notes: in_stack_00000058 >> 4 is the frame-selector nibble. */
static void sk_dispatch_00459138(uint64_t arg0, uint64_t arg1, uint64_t arg2,
                                 uint64_t arg3, uint64_t arg4, uint64_t arg5,
                                 uint64_t arg6, uint64_t arg7, uint64_t mode_word)
{
    uint64_t sel = (mode_word >> 4) & 0xff;

    if (0xd < sel) {
        return;
    }
    switch (sel) {
    default:
        arg4 = arg1;
        break;
    case 1:
    case 4:
        return;
    case 2:
        sk_x_0036b118();
        goto push_arg1;
    case 3:
        sk_dispatch_00459280(arg0, arg1, 0, 0, 0);
        return;
    case 9:
    case 10:
        sk_dispatch_004592dc(arg0, arg1, 0, 0, 0);
        return;
    case 0xb:
        sk_dispatch_004592f4(arg0, arg1, 0, 0, 0, 0, 0, 0);
        return;
    case 0xc:
        break;
    case 0xd:
        sk_x_0036b118(arg3);
        arg1 = arg7;
push_arg1:
        sk_x_0036b118(arg1);
        return;
    }
    sk_x_003a25d4(arg4);
}

/* FUN_00459280 @ 0x00459280   (est. sk_dispatch_00459280)
 * Ghidra: void FUN_00459280(undefined8 param_1..4, char param_5)
 * Nested mode switch for frame selector 3: mode 4 pushes param_2; mode 0xe
 * pushes param_4; mode 7 pushes param_3; any other mode ignored.
 * Confidence: low
 * Notes: pushed via 003a25d4. */
static void sk_dispatch_00459280(uint64_t arg0, uint64_t arg1, uint64_t arg2,
                                 uint64_t arg3, uint64_t mode)
{
    if (mode != 4) {
        if (mode == 0xe) {
            sk_x_003a25d4(arg3);
        } else {
            arg1 = arg2;
            if (mode != 7) {
                return;
            }
        }
    }
    sk_x_003a25d4(arg1);
}

/* FUN_004592dc @ 0x004592dc   (est. sk_dispatch_004592dc)
 * Ghidra: void FUN_004592dc(undefined8 param_1..4, char param_5)
 * Frame selector 9/10 handler: mode 2 pushes param_2 through 003a25d4;
 * all other modes ignored.
 * Confidence: low */
static void sk_dispatch_004592dc(uint64_t arg0, uint64_t arg1, uint64_t arg2,
                                 uint64_t arg3, uint64_t mode)
{
    if (mode == 2) {
        sk_x_003a25d4(arg1);
        return;
    }
}

/* FUN_004592f4 @ 0x004592f4   (est. sk_dispatch_004592f4)
 * Ghidra: void FUN_004592f4(undefined8 param_1..4, ...)
 * Frame selector 0xb handler: mode 2 pushes param_4 then the stack word at
 * +0x18; mode 1 pushes param_2, x7, then pushes the +0x30 stack word via
 * 0036b118; mode 0 dispatches through 00458bac. Other modes ignored.
 * Confidence: low
 * Notes: in_x7 / in_stack artifacts of the caller's window. */
static void sk_dispatch_004592f4(uint64_t arg0, uint64_t arg1, uint64_t arg2,
                                 uint64_t arg3, uint64_t x7, uint64_t st18,
                                 uint64_t st30, uint64_t mode)
{
    if (mode == 2) {
        sk_x_003a25d4(arg3);
        sk_x_003a25d4(st18);
        return;
    }
    if (mode != 1) {
        if (mode == 0) {
            sk_x_00458bac();
            return;
        }
        return;
    }
    sk_x_003a25d4(arg1);
    sk_x_003a25d4(x7);
    sk_x_0036b118(st30);
}

/* FUN_00459384 @ 0x00459384   (est. sk_dispatch_00459384)
 * Ghidra: void FUN_00459384(void)
 * Register-fragment shim: pushes the context word at x20+0x18 via 003a25d4,
 * runs 00355538, then the 0036b21c frame-completion helper.
 * Confidence: low
 * Notes: unaff_x20; paired copy is 00459388. */
static void sk_dispatch_00459384(void)
{
    uint64_t x20 = 0;   /* unaff_x20: running context */

    sk_x_003a25d4(*(uint64_t *)(x20 + 0x18));
    sk_x_00355538();
    sk_x_0036b21c();
}

/* FUN_00459388 @ 0x00459388   (est. sk_dispatch_00459388)
 * Ghidra: void FUN_00459388(void)
 * Identical copy of 00459384 (paired duplicate vector).
 * Confidence: low */
static void sk_dispatch_00459388(void)
{
    uint64_t x20 = 0;   /* unaff_x20: running context */

    sk_x_003a25d4(*(uint64_t *)(x20 + 0x18));
    sk_x_00355538();
    sk_x_0036b21c();
}

/* FUN_004593ac @ 0x004593ac   (est. sk_dispatch_004593ac)
 * Ghidra: void FUN_004593ac(void)
 * Dispatches on the low 3 bits of a stack mode word: mode 3 runs 00458db4
 * then pushes the cleared (tag-stripped) word via 0036b118; modes 1 and 0
 * run 004592dc; any other mode ignored.
 * Confidence: low
 * Notes: in_stack_00000028 register artifact. */
static void sk_dispatch_004593ac(void)
{
    uint64_t mode_word = 0;   /* in_stack_00000028 */
    uint64_t mode = mode_word & 7;

    if (mode == 3) {
        sk_dispatch_00458db4(0, 0, 0, 0, 0, 0);
        sk_x_0036b118(mode_word & ~7ULL);
        return;
    }
    if ((mode != 1) && ((mode_word & 7) != 0)) {
        return;
    }
    sk_dispatch_004592dc(0, 0, 0, 0, 0);
}

/* FUN_0045942c @ 0x0045942c   (est. sk_dispatch_0045942c)
 * Ghidra: void FUN_0045942c(void)
 * Composite register-fragment shim: runs 0010a9f8, pushes the x20+0x50
 * context word via 00464f40, runs 00458db4 (mode gate), pushes the tagged
 * word at x20+0x78 (low 60 bits) via 0036b118, runs 00465884, then the
 * 0036b21c frame-completion helper.
 * Confidence: low
 * Notes: unaff_x20 = running context. */
static void sk_dispatch_0045942c(void)
{
    uint64_t x20 = 0;   /* unaff_x20: running context */

    sk_x_0010a9f8();
    sk_x_00464f40(*(uint64_t *)(x20 + 0x50));
    sk_dispatch_00458db4(0, 0, 0, 0, 0, 0);
    sk_x_0036b118(*(uint64_t *)(x20 + 0x78) & SK_TAG_MASK);
    sk_x_00465884();
    sk_x_0036b21c();
}

/* FUN_0045947c @ 0x0045947c   (est. sk_list_next_0045947c)
 * Ghidra: long FUN_0045947c(ulong param_1)
 * Tagged-node walk (like 00458e50) with a 4-byte header: returns
 * node + 4 + 4-byte count at +4.
 * Confidence: medium */
static uint64_t sk_list_next_0045947c(uint64_t node)
{
    if ((node & 1) != 0) {
        node = *(uint64_t *)(node & ~1ULL);
    }
    return (uint64_t)(node + 4) + (uint64_t)*(int32_t *)(node + 4);
}

/* FUN_004594c4 @ 0x004594c4   (est. sk_dispatch_004594c4)
 * Ghidra: void FUN_004594c4(void)
 * Register-fragment shim: pushes x20+0x18 via 0036b118, runs 00002834, then
 * 0036b21c. Paired copy is 004594c8.
 * Confidence: low
 * Notes: unaff_x20. */
static void sk_dispatch_004594c4(void)
{
    uint64_t x20 = 0;   /* unaff_x20: running context */

    sk_x_0036b118(*(uint64_t *)(x20 + 0x18));
    sk_x_00002834();
    sk_x_0036b21c();
}

/* FUN_004594c8 @ 0x004594c8   (est. sk_dispatch_004594c8)
 * Ghidra: void FUN_004594c8(void)
 * Identical copy of 004594c4 (paired duplicate vector).
 * Confidence: low */
static void sk_dispatch_004594c8(void)
{
    uint64_t x20 = 0;   /* unaff_x20: running context */

    sk_x_0036b118(*(uint64_t *)(x20 + 0x18));
    sk_x_00002834();
    sk_x_0036b21c();
}

/* FUN_004594f4 @ 0x004594f4   (est. sk_dispatch_004594f4)
 * Ghidra: void FUN_004594f4(undefined8 param_1, undefined8 param_2)
 * Forwards the two caller words plus three context words at x20+0x10/+0x18/
 * +0x20 into 00455574. Paired copy is 004594f8.
 * Confidence: low
 * Notes: unaff_x20. */
static void sk_dispatch_004594f4(uint64_t arg0, uint64_t arg1)
{
    uint64_t x20 = 0;   /* unaff_x20: running context */

    sk_x_00455574(arg0, arg1, *(uint64_t *)(x20 + 0x10),
                  *(uint64_t *)(x20 + 0x18), *(uint64_t *)(x20 + 0x20));
}

/* FUN_004594f8 @ 0x004594f8   (est. sk_dispatch_004594f8)
 * Ghidra: void FUN_004594f8(undefined8 param_1, undefined8 param_2)
 * Identical copy of 004594f4 (paired duplicate vector).
 * Confidence: low */
static void sk_dispatch_004594f8(uint64_t arg0, uint64_t arg1)
{
    uint64_t x20 = 0;   /* unaff_x20: running context */

    sk_x_00455574(arg0, arg1, *(uint64_t *)(x20 + 0x10),
                  *(uint64_t *)(x20 + 0x18), *(uint64_t *)(x20 + 0x20));
}

/* FUN_00459514 @ 0x00459514   (est. sk_dispatch_00459514)
 * Ghidra: void FUN_00459514(void)
 * Registers a descriptor-constructor pair: calls 00462758 with the addresses
 * 0x657a40/0x657a48 and the 005a2018 data area, then 00460d50. Paired copy
 * is 00459518.
 * Confidence: low
 * Notes: pair of adjacent image addresses likely a {getter,setter} vtable. */
static void sk_dispatch_00459514(void)
{
    sk_x_00462758(0x657a40, 0x657a48, &sk_g_005a2018);
    sk_x_00460d50();
}

/* FUN_00459518 @ 0x00459518   (est. sk_dispatch_00459518)
 * Ghidra: void FUN_00459518(void)
 * Identical copy of 00459514 (paired duplicate vector).
 * Confidence: low */
static void sk_dispatch_00459518(void)
{
    sk_x_00462758(0x657a40, 0x657a48, &sk_g_005a2018);
    sk_x_00460d50();
}

/* FUN_00459548 @ 0x00459548   (est. sk_dispatch_00459548)
 * Ghidra: void FUN_00459548(undefined8 param_1, undefined8 param_2,
 *                           undefined8 *param_3)
 * Setter shim: runs 003504d0, calls 00027754 with *param_3, resolves the
 * 005a26cc data address through 00376820 and stores the result into the
 * running context at x20+8.
 * Confidence: low
 * Notes: unaff_x20; 00376820 is an address-resolution helper. */
static void sk_dispatch_00459548(uint64_t arg0, uint64_t arg1, uint64_t *arg2)
{
    uint64_t u;
    uint64_t x20 = 0;   /* unaff_x20 */

    sk_x_003504d0();
    sk_x_00027754(*arg2);
    u = sk_x_00376820(&sk_g_005a26cc);
    *(uint64_t *)(x20 + 8) = u;
}

/* FUN_004595a0 @ 0x004595a0   (est. sk_dispatch_004595a0)
 * Ghidra: void FUN_004595a0(void)
 * Forwards the (0x656378, 004ea7c8) pair into 00459888. Paired copy 004595a4.
 * Confidence: low */
static void sk_dispatch_004595a0(void)
{
    sk_dispatch_00459888((uint64_t *)0x656378, &sk_g_004ea7c8);
}

/* FUN_004595a4 @ 0x004595a4   (est. sk_dispatch_004595a4)
 * Ghidra: void FUN_004595a4(void)
 * Identical copy of 004595a0 (paired duplicate vector).
 * Confidence: low */
static void sk_dispatch_004595a4(void)
{
    sk_dispatch_00459888((uint64_t *)0x656378, &sk_g_004ea7c8);
}

/* FUN_004595d4 @ 0x004595d4   (est. sk_dispatch_004595d4)
 * Ghidra: void FUN_004595d4(void)
 * Forwards (0x657a50, 0045961c, 004eb078) into 00459768. Paired copy 004595d8.
 * Confidence: low */
static void sk_dispatch_004595d4(void)
{
    sk_dispatch_00459768(0x657a50, &sk_g_0045961c, &sk_g_004eb078);
}

/* FUN_004595d8 @ 0x004595d8   (est. sk_dispatch_004595d8)
 * Ghidra: void FUN_004595d8(void)
 * Identical copy of 004595d4 (paired duplicate vector).
 * Confidence: low */
static void sk_dispatch_004595d8(void)
{
    sk_dispatch_00459768(0x657a50, &sk_g_0045961c, &sk_g_004eb078);
}

/* FUN_0045962c @ 0x0045962c   (est. sk_dispatch_0045962c)
 * Ghidra: void FUN_0045962c(void)
 * Stores into the 0x657a60 global the resolved address of 005a2cb0 produced
 * by 00376820 (with the 0x685478 selector constant). Paired copy 00459630.
 * Confidence: low
 * Notes: Ghidra warns the 0x657a60 address is written (RO-data area). */
static void sk_dispatch_0045962c(void)
{
    sk_g_00657a60 = (uint64_t)sk_x_00376820(&sk_g_005a2cb0, 0x685478);
}

/* FUN_00459630 @ 0x00459630   (est. sk_dispatch_00459630)
 * Ghidra: void FUN_00459630(void)
 * Identical copy of 0045962c (paired duplicate vector).
 * Confidence: low */
static void sk_dispatch_00459630(void)
{
    sk_g_00657a60 = (uint64_t)sk_x_00376820(&sk_g_005a2cb0, 0x685478);
}

/* FUN_00459670 @ 0x00459670   (est. sk_dispatch_00459670)
 * Ghidra: void FUN_00459670(long param_1)
 * Stores the result of 00459698 into param_1+8.
 * Confidence: low */
static void sk_dispatch_00459670(uint64_t base)
{
    uint64_t u = sk_dispatch_00459698();
    *(uint64_t *)(base + 8) = u;
}

/* FUN_00459698 @ 0x00459698   (est. sk_branch_00459698)
 * Ghidra: void FUN_00459698(void)
 * Write-only fragment: stores the 64-bit constant 0xf9004030dac10230 into
 * the 0x657a68 global (the decompiler dropped the trailing block, marked
 * unreachable at 0x004596ac). The constant decodes as two arm64
 * instructions (isb; str x16,[x1,#8]-style), i.e. this is a code-patch
 * stub, not a data store.
 * Confidence: low
 * Notes: 'Removing unreachable block (ram,0x004596ac)'; raw instruction
 *   bytes written, so the "value" is actually an instruction stream. */
static uint64_t sk_dispatch_00459698(void)
{
    sk_g_00657a68 = 0xf9004030dac10230ULL;
    return 0;
}

/* FUN_004596ec @ 0x004596ec   (est. sk_dispatch_004596ec)
 * Ghidra: void FUN_004596ec(void)
 * Forwards (0x656380, 004ea794) into 00459888. Paired copy 004596f0.
 * Confidence: low */
static void sk_dispatch_004596ec(void)
{
    sk_dispatch_00459888((uint64_t *)0x656380, &sk_g_004ea794);
}

/* FUN_004596f0 @ 0x004596f0   (est. sk_dispatch_004596f0)
 * Ghidra: void FUN_004596f0(void)
 * Identical copy of 004596ec (paired duplicate vector).
 * Confidence: low */
static void sk_dispatch_004596f0(void)
{
    sk_dispatch_00459888((uint64_t *)0x656380, &sk_g_004ea794);
}

/* FUN_00459720 @ 0x00459720   (est. sk_dispatch_00459720)
 * Ghidra: void FUN_00459720(void)
 * Forwards (0x657a70, 00459698, 004eb028) into 00459768 (registering the
 * 00459698 patch stub as the value producer). Paired copy 00459724.
 * Confidence: low */
static void sk_dispatch_00459720(void)
{
    sk_dispatch_00459768(0x657a70, &sk_dispatch_00459698, &sk_g_004eb028);
}

/* FUN_00459724 @ 0x00459724   (est. sk_dispatch_00459724)
 * Ghidra: void FUN_00459724(void)
 * Identical copy of 00459720 (paired duplicate vector).
 * Confidence: low */
static void sk_dispatch_00459724(void)
{
    sk_dispatch_00459768(0x657a70, &sk_dispatch_00459698, &sk_g_004eb028);
}

/* FUN_00459768 @ 0x00459768   (est. sk_dispatch_00459768)
 * Ghidra: void FUN_00459768(void)
 * Constructor template: queries 00352b20 for a 16-byte descriptor; when the
 * lo half is non-zero it logs (00027614) with the 657a58/005a2ca8 pair, calls
 * the descriptor's code pointer (hi half) to obtain a fresh value pair, saves
 * it into a local, resolves 00376820, and stores the result through the
 * x19 context slot. Used with an explicit (key, producer, area) set by the
 * callers above.
 * Confidence: low
 * Notes: unaff_x19; 00352b20/00027614/00350af4/00376820 out-of-slice. */
static void sk_dispatch_00459768(uint64_t key, uint64_t *producer, uint64_t *area)
{
    uint64_t u;
    uint64_t *x19 = 0;   /* unaff_x19 */
    sk_pair_t d;
    uint64_t local;

    d = sk_x_00352b20();
    if (d.lo == 0) {
        sk_x_00027614(0x657a58, &sk_g_005a2ca8);
        {
            sk_pair_t v = ((sk_pair_t (*)(void))(d.hi))();
            local = v.lo;
            sk_x_00350af4(local, v.hi, &local);
        }
        u = sk_x_00376820();
        *x19 = u;
    }
}

/* FUN_004597d8 @ 0x004597d8   (est. sk_dispatch_004597d8)
 * Ghidra: void FUN_004597d8(long param_1)
 * Stores the result of 00459800 into param_1+8.
 * Confidence: low */
static void sk_dispatch_004597d8(uint64_t base)
{
    uint64_t u = sk_dispatch_00459800();
    *(uint64_t *)(base + 8) = u;
}

/* FUN_00459800 @ 0x00459800   (est. sk_branch_00459800)
 * Ghidra: void FUN_00459800(void)
 * Write-only fragment storing the 64-bit constant 0xdac10230d29170b1 into
 * the 0x657a78 global (trailing block dropped, unreachable at 0x00459814).
 * The constant decodes as two arm64 instructions (isb; autia/mov) — a code
 * patch stub, not a plain data store.
 * Confidence: low
 * Notes: 'Removing unreachable block (ram,0x00459814)'. */
static uint64_t sk_dispatch_00459800(void)
{
    sk_g_00657a78 = 0xdac10230d29170b1ULL;
    return 0;
}

/* FUN_00459854 @ 0x00459854   (est. sk_dispatch_00459854)
 * Ghidra: void FUN_00459854(void)
 * Forwards (0064c2e0, 004ea760) into 00459888. Paired copy 00459858.
 * Confidence: low */
static void sk_dispatch_00459854(void)
{
    sk_dispatch_00459888(&sk_g_0064c2e0, &sk_g_004ea760);
}

/* FUN_00459858 @ 0x00459858   (est. sk_dispatch_00459858)
 * Ghidra: void FUN_00459858(void)
 * Identical copy of 00459854 (paired duplicate vector).
 * Confidence: low */
static void sk_dispatch_00459858(void)
{
    sk_dispatch_00459888(&sk_g_0064c2e0, &sk_g_004ea760);
}

/* FUN_00459888 @ 0x00459888   (est. sk_dispatch_00459888)
 * Ghidra: void FUN_00459888(void)
 * Constructor template (mirror of 00459768): queries 00352b20; on a zero lo
 * half logs via 00027614 with the (0064c2d8, 004bbe30) pair, builds a local
 * descriptor (16-byte result of 00027670 with a 0x6720e8 key passed through
 * 0006b6f4), resolves 00376820 and stores through the x19 context slot.
 * Confidence: low
 * Notes: unaff_x19; Ghidra local_40/uStack_38 artifacts. */
static void sk_dispatch_00459888(uint64_t *key, uint64_t *area)
{
    uint64_t u;
    uint64_t *x19 = 0;   /* unaff_x19 */
    sk_pair_t d;
    uint64_t local_40;
    uint64_t stack_38;

    d = sk_x_00352b20();
    if (d.lo == 0) {
        sk_x_00027614(&sk_g_0064c2d8, &sk_g_004bbe30);
        {
            sk_pair_t v = sk_x_00027670();
            stack_38 = v.lo;
            local_40 = 0x6720e8;
            sk_x_0006b6f4(stack_38, v.hi, &local_40);
        }
        u = sk_x_00376820();
        *x19 = u;
    }
}

/* FUN_00459900 @ 0x00459900   (est. sk_dispatch_00459900)
 * Ghidra: void FUN_00459900(void)
 * Registers a descriptor-constructor pair: 00462758 with (0x657a80, 0x657a88,
 * 005a2db0), then 00460d50. Paired copy 00459904.
 * Confidence: low */
static void sk_dispatch_00459900(void)
{
    sk_x_00462758(0x657a80, 0x657a88, &sk_g_005a2db0);
    sk_x_00460d50();
}

/* FUN_00459904 @ 0x00459904   (est. sk_dispatch_00459904)
 * Ghidra: void FUN_00459904(void)
 * Identical copy of 00459900 (paired duplicate vector).
 * Confidence: low */
static void sk_dispatch_00459904(void)
{
    sk_x_00462758(0x657a80, 0x657a88, &sk_g_005a2db0);
    sk_x_00460d50();
}

/* FUN_00459934 @ 0x00459934   (est. sk_dispatch_00459934)
 * Ghidra: void FUN_00459934(void)
 * Registers (0x657a90, 0x657a98, 005a2e08) then 00460d50. Paired copy 00459938.
 * Confidence: low */
static void sk_dispatch_00459934(void)
{
    sk_x_00462758(0x657a90, 0x657a98, &sk_g_005a2e08);
    sk_x_00460d50();
}

/* FUN_00459938 @ 0x00459938   (est. sk_dispatch_00459938)
 * Ghidra: void FUN_00459938(void)
 * Identical copy of 00459934 (paired duplicate vector).
 * Confidence: low */
static void sk_dispatch_00459938(void)
{
    sk_x_00462758(0x657a90, 0x657a98, &sk_g_005a2e08);
    sk_x_00460d50();
}

/* FUN_00459968 @ 0x00459968   (est. sk_dispatch_00459968)
 * Ghidra: void FUN_00459968(void)
 * Registers (0x657aa0, 0x657aa8, 005a2e60) then 00460d50. Paired copy 0045996c.
 * Confidence: low */
static void sk_dispatch_00459968(void)
{
    sk_x_00462758(0x657aa0, 0x657aa8, &sk_g_005a2e60);
    sk_x_00460d50();
}

/* FUN_0045996c @ 0x0045996c   (est. sk_dispatch_0045996c)
 * Ghidra: void FUN_0045996c(void)
 * Identical copy of 00459968 (paired duplicate vector).
 * Confidence: low */
static void sk_dispatch_0045996c(void)
{
    sk_x_00462758(0x657aa0, 0x657aa8, &sk_g_005a2e60);
    sk_x_00460d50();
}

/* FUN_0045999c @ 0x0045999c   (est. sk_dispatch_0045999c)
 * Ghidra: void FUN_0045999c(void)
 * Registers (0x657ab0, 0x657ab8, 005a2eb8) then 00460d50. Paired copy 004599a0.
 * Confidence: low */
static void sk_dispatch_0045999c(void)
{
    sk_x_00462758(0x657ab0, 0x657ab8, &sk_g_005a2eb8);
    sk_x_00460d50();
}

/* FUN_004599a0 @ 0x004599a0   (est. sk_dispatch_004599a0)
 * Ghidra: void FUN_004599a0(void)
 * Identical copy of 0045999c (paired duplicate vector).
 * Confidence: low */
static void sk_dispatch_004599a0(void)
{
    sk_x_00462758(0x657ab0, 0x657ab8, &sk_g_005a2eb8);
    sk_x_00460d50();
}

/* FUN_004599d0 @ 0x004599d0   (est. sk_dispatch_004599d0)
 * Ghidra: void FUN_004599d0(void)
 * Registers (0x657ac0, 0x657ac8, 005a2f10) then 00460d50. Paired copy 004599d4.
 * Confidence: low */
static void sk_dispatch_004599d0(void)
{
    sk_x_00462758(0x657ac0, 0x657ac8, &sk_g_005a2f10);
    sk_x_00460d50();
}

/* FUN_004599d4 @ 0x004599d4   (est. sk_dispatch_004599d4)
 * Ghidra: void FUN_004599d4(void)
 * Identical copy of 004599d0 (paired duplicate vector).
 * Confidence: low */
static void sk_dispatch_004599d4(void)
{
    sk_x_00462758(0x657ac0, 0x657ac8, &sk_g_005a2f10);
    sk_x_00460d50();
}

/* FUN_00459a04 @ 0x00459a04   (est. sk_dispatch_00459a04)
 * Ghidra: void FUN_00459a04(ulong *param_1)
 * Register-fragment store: pushes the tagged word at param_1[0] (low 60
 * bits), then param_1[1] and param_1[2], all via 0036b118.
 * Confidence: low */
static void sk_dispatch_00459a04(uint64_t *frame)
{
    sk_x_0036b118(frame[0] & SK_TAG_MASK);
    sk_x_0036b118(frame[1]);
    sk_x_0036b118(frame[2]);
}

/* FUN_00459a40 @ 0x00459a40   (est. sk_frame_copy_00459a40)
 * Ghidra: void FUN_00459a40(void)
 * Copies a 3-word+byte context block from the 0034f2f4 source to the
 * 0034f2f4 target (lo/hi of the returned pair), then pushes the tagged
 * extraout_x8 and the two copied words through 0036b270.
 * Confidence: low
 * Notes: extraout_x8 register artifact; 0034f2f4 returns a (src,dst) pair. */
static void sk_frame_copy_00459a40(void)
{
    uint64_t dst, src;
    uint64_t w3, w4;
    uint64_t extraout_x8 = 0;   /* register artifact */
    sk_pair_t p;

    p = sk_x_0034f2f4();
    src = p.hi;
    dst = p.lo;
    w3 = *(uint64_t *)(src + 0x10);
    w4 = *(uint64_t *)(src + 8);
    *(uint64_t *)(dst + 0x10) = *(uint64_t *)(src + 0x10);
    *(uint64_t *)(dst + 8) = w4;
    *(uint8_t *)(dst + 0x18) = *(uint8_t *)(src + 0x18);
    sk_x_0036b270(extraout_x8 & SK_TAG_MASK);
    sk_x_0036b270(w4);
    sk_x_0036b270(w3);
}

/* FUN_00459aa0 @ 0x00459aa0   (est. sk_frame_swap_00459aa0)
 * Ghidra: void FUN_00459aa0(void)
 * Swaps the tagged head word of the 0034d454 frame with extraout_x8 (pushing
 * both through 0036b270/0036b118), then swaps the x20+8 and x20+0x10 words
 * against the x19 context words (each with a push of the evicted value).
 * Confidence: low
 * Notes: unaff_x19/x20; 0034d454 returns a frame pointer. */
static void sk_frame_swap_00459aa0(void)
{
    uint64_t *slot;
    uint64_t u;
    uint64_t extraout_x8 = 0;   /* register artifact */
    uint64_t x19 = 0, x20 = 0;  /* unaff registers */
    uint64_t v;

    slot = (uint64_t *)sk_x_0034d454();
    u = *slot;
    *slot = extraout_x8;
    sk_x_0036b270(extraout_x8 & SK_TAG_MASK);
    sk_x_0036b118(u & SK_TAG_MASK);
    v = *(uint64_t *)(x20 + 8);
    *(uint64_t *)(x20 + 8) = *(uint64_t *)(x19 + 8);
    sk_x_0036b270();
    sk_x_0036b118(v);
    v = *(uint64_t *)(x20 + 0x10);
    *(uint64_t *)(x20 + 0x10) = *(uint64_t *)(x19 + 0x10);
    sk_x_0036b270();
    sk_x_0036b118(v);
    sk_x_00463a48();
}

/* FUN_00459b14 @ 0x00459b14   (est. sk_frame_swap_00459b14)
 * Ghidra: void FUN_00459b14(void)
 * Swaps the tagged head word of the 0034d454 frame (push via 0036b118),
 * pushes x20+8, then swaps x20+8/+0x10 against the x19 context words and
 * pushes the evicted x20+0x10 value. Epilogue via 00463a48.
 * Confidence: low
 * Notes: unaff_x19/x20. */
static void sk_frame_swap_00459b14(void)
{
    uint64_t *slot;
    uint64_t u, v;
    uint64_t extraout_x8 = 0;   /* register artifact */
    uint64_t x19 = 0, x20 = 0;  /* unaff registers */

    slot = (uint64_t *)sk_x_0034d454();
    u = *slot;
    *slot = extraout_x8;
    sk_x_0036b118(u & SK_TAG_MASK);
    sk_x_0036b118(*(uint64_t *)(x20 + 8));
    v = *(uint64_t *)(x20 + 0x10);
    *(uint64_t *)(x20 + 0x10) = *(uint64_t *)(x19 + 0x10);
    *(uint64_t *)(x20 + 8) = *(uint64_t *)(x19 + 8);
    sk_x_0036b118(v);
    sk_x_00463a48();
}

/* FUN_00459b6c @ 0x00459b6c   (est. sk_frame_copy_00459b6c)
 * Ghidra: void FUN_00459b6c(void)
 * Runs 0034f2f4 (frame pair) then pushes the tagged extraout_x8 via
 * 0036b270. No other local state.
 * Confidence: low
 * Notes: extraout_x8 register artifact. */
static void sk_frame_copy_00459b6c(void)
{
    uint64_t extraout_x8 = 0;   /* register artifact */

    sk_x_0034f2f4();
    sk_x_0036b270(extraout_x8 & SK_TAG_MASK);
}

/* FUN_00459ba4 @ 0x00459ba4   (est. sk_word_swap_00459ba4)
 * Ghidra: ulong *FUN_00459ba4(ulong *param_1, ulong *param_2)
 * Swaps *param_1 and *param_2, pushing both tagged words through the
 * 0036b270/0036b118 helpers, and returns param_1.
 * Confidence: low */
static uint64_t *sk_word_swap_00459ba4(uint64_t *a, uint64_t *b)
{
    uint64_t u, v;

    u = *b;
    v = *a;
    *a = u;
    sk_x_0036b270(u & SK_TAG_MASK);
    sk_x_0036b118(v & SK_TAG_MASK);
    return a;
}

/* FUN_00459be4 @ 0x00459be4   (est. sk_word_copy_00459be4)
 * Ghidra: ulong *FUN_00459be4(ulong *param_1, ulong *param_2)
 * Copies *param_2 into *param_1, pushing the evicted tagged value via
 * 0036b118; returns param_1.
 * Confidence: low */
static uint64_t *sk_word_copy_00459be4(uint64_t *a, uint64_t *b)
{
    uint64_t u = *a;

    *a = *b;
    sk_x_0036b118(u & SK_TAG_MASK);
    return a;
}

/* FUN_00459cfc @ 0x00459cfc   (est. sk_context_copy_00459cfc)
 * Ghidra: void FUN_00459cfc(void)
 * Copies one context word from x19+8 to x20+8: runs 003504d0, 00465b1c,
 * pushes via 0036b118, copies the word, then 00464dcc.
 * Confidence: low
 * Notes: unaff_x19/x20. */
static void sk_context_copy_00459cfc(void)
{
    uint64_t x19 = 0, x20 = 0;  /* unaff registers */

    sk_x_003504d0();
    sk_x_00465b1c();
    sk_x_0036b118();
    *(uint64_t *)(x20 + 8) = *(uint64_t *)(x19 + 8);
    sk_x_00464dcc();
}

/* FUN_00459d40 @ 0x00459d40   (est. sk_context_store_00459d40)
 * Ghidra: void FUN_00459d40(void)
 * Stores extraout_x8 into *x20 (pushing the old head word), then copies the
 * x19+8 and x19+0x10 context words into x20[1]/x20[2]. Frame from 0034d454.
 * Confidence: low
 * Notes: unaff_x19/x20; extraout_x8 register artifact. */
static void sk_context_store_00459d40(void)
{
    uint64_t *slot;
    uint64_t u;
    uint64_t extraout_x8 = 0;   /* register artifact */
    uint64_t x19 = 0;
    uint64_t *x20 = 0;          /* unaff registers */

    slot = (uint64_t *)sk_x_0034d454();
    u = *slot;
    *x20 = extraout_x8;
    sk_x_0036b118(u);
    u = *(uint64_t *)(x19 + 8);
    x20[2] = *(uint64_t *)(x19 + 0x10);
    x20[1] = u;
}

/* FUN_00459e14 @ 0x00459e14   (est. sk_context_forward_00459e14)
 * Ghidra: void FUN_00459e14(long param_1)
 * Forwards the four context words at param_1+0x10/+0x18/+0x20/+0x28 into
 * 00458940.
 * Confidence: low */
static void sk_context_forward_00459e14(uint64_t base)
{
    sk_x_00458940(*(uint64_t *)(base + 0x10), *(uint64_t *)(base + 0x18),
                  *(uint64_t *)(base + 0x20), *(uint64_t *)(base + 0x28));
}

/* FUN_00459e24 @ 0x00459e24   (est. sk_context_copy_00459e24)
 * Ghidra: void FUN_00459e24(void)
 * Copies the caller's register window into the x20 context: runs 0046306c,
 * 004661fc, 00462948, 004588cc; stores x21..x24 at x20+0x10..+0x28, and
 * copies x19+0x30/+0x38 words into x20.
 * Confidence: low
 * Notes: unaff_x19..x24 register artifacts. */
static void sk_context_copy_00459e24(void)
{
    uint64_t x19 = 0, x20 = 0;  /* unaff registers */
    uint64_t x21 = 0, x22 = 0, x23 = 0, x24 = 0;
    uint64_t u;

    sk_x_0046306c();
    sk_x_004661fc();
    sk_x_00462948();
    sk_x_004588cc();
    *(uint64_t *)(x20 + 0x10) = x21;
    *(uint64_t *)(x20 + 0x18) = x22;
    *(uint64_t *)(x20 + 0x20) = x23;
    *(uint64_t *)(x20 + 0x28) = x24;
    u = *(uint64_t *)(x19 + 0x30);
    *(uint64_t *)(x20 + 0x38) = *(uint64_t *)(x19 + 0x38);
    *(uint64_t *)(x20 + 0x30) = u;
}

/* FUN_00459e74 @ 0x00459e74   (est. sk_context_copy_00459e74)
 * Ghidra: void FUN_00459e74(void)
 * Fuller context capture than 00459e24: runs 0034b264, 004640b8, 004661fc,
 * 00462948, 004588cc, 0010a9f8; stores x21..x24 at x20+0x10..+0x28, calls
 * 00458940, copies x19+0x30, and runs 00466220.
 * Confidence: low
 * Notes: unaff_x19..x24 register artifacts. */
static void sk_context_copy_00459e74(void)
{
    uint64_t x19 = 0, x20 = 0;  /* unaff registers */
    uint64_t x21 = 0, x22 = 0, x23 = 0, x24 = 0;

    sk_x_0034b264();
    sk_x_004640b8();
    sk_x_004661fc();
    sk_x_00462948();
    sk_x_004588cc();
    sk_x_0010a9f8();
    *(uint64_t *)(x20 + 0x10) = x21;
    *(uint64_t *)(x20 + 0x18) = x22;
    *(uint64_t *)(x20 + 0x20) = x23;
    *(uint64_t *)(x20 + 0x28) = x24;
    sk_x_00458940();
    *(uint64_t *)(x20 + 0x30) = *(uint64_t *)(x19 + 0x30);
    sk_x_00466220();
}

/* FUN_00459ed4 @ 0x00459ed4   (est. sk_context_copy_00459ed4)
 * Ghidra: void FUN_00459ed4(void)
 * Captures the caller's register window (x19..) into the x20 context:
 * resolves the 003504d0 frame, copies x19 words [0..7] into x20, pushes the
 * prior x20[3..5] into 00458940, and copies the remaining x19[6]/x19[7].
 * Confidence: low
 * Notes: unaff_x19/x20; a register-window save helper. */
static void sk_context_copy_00459ed4(void)
{
    uint64_t *x19 = 0, *x20 = 0;  /* unaff registers */
    uint64_t u, w3, w4, w5;

    u = sk_x_003504d0();
    w3 = x20[3];
    w4 = x20[4];
    w5 = x20[5];
    x20[1] = x19[1];
    *x20 = *x19;
    x20[3] = x19[3];
    x20[2] = x19[2];
    x20[5] = x19[5];
    x20[4] = x19[4];
    sk_x_00458940(u, w3, w4, w5);
    x20[7] = x19[7];
    x20[6] = x19[6];
}

/* FUN_00459ffc @ 0x00459ffc   (est. sk_context_store_00459ffc)
 * Ghidra: void FUN_00459ffc(void)
 * Stores the caller's x20..x23 register window into the x19 context words
 * [0..3], after running 00463504, 0034c444, and 004588cc.
 * Confidence: low
 * Notes: unaff_x19..x23 register artifacts. */
static void sk_context_store_00459ffc(void)
{
    uint64_t *x19 = 0;  /* unaff register */
    uint64_t x20 = 0, x21 = 0, x22 = 0, x23 = 0;

    sk_x_00463504();
    sk_x_0034c444();
    sk_x_004588cc();
    *x19 = x20;
    x19[1] = x21;
    x19[2] = x22;
    x19[3] = x23;
}

/* FUN_0045a044 @ 0x0045a044   (est. sk_context_swap_0045a044)
 * Ghidra: void FUN_0045a044(void)
 * Swaps the caller's x20..x23 window into x19[0..3], pushing the evicted
 * x19 words through 00458940. Runs 00463504, 0034c444, 004588cc first.
 * Confidence: low
 * Notes: unaff_x19..x23 register artifacts. */
static void sk_context_swap_0045a044(void)
{
    uint64_t *x19 = 0;  /* unaff register */
    uint64_t x20 = 0, x21 = 0, x22 = 0, x23 = 0;
    uint64_t a, b, c, d;

    sk_x_00463504();
    sk_x_0034c444();
    sk_x_004588cc();
    a = *x19;
    c = x19[1];
    b = x19[2];
    d = x19[3];
    *x19 = x20;
    x19[1] = x21;
    x19[2] = x22;
    x19[3] = x23;
    sk_x_00458940(a, c, b, d);
}

/* FUN_0045a098 @ 0x0045a098   (est. sk_context_copy_0045a098)
 * Ghidra: void FUN_0045a098(void)
 * Copies the 16-byte descriptor (00352b20 lo/hi) frame words into x19[0..3]
 * after saving the evicted x19 words, then forwards them into 00458940.
 * Confidence: low
 * Notes: unaff_x19; 00352b20 returns a 16-byte pair. */
static void sk_context_copy_0045a098(void)
{
    uint64_t *x19 = 0;  /* unaff register */
    uint64_t a, b, c;
    uint64_t d1, d2, d3;
    sk_pair_t p;

    p = sk_x_00352b20();
    {
        uint64_t *src = (uint64_t *)p.hi;
        a = x19[1];
        b = x19[2];
        c = x19[3];
        d1 = *src;
        d3 = src[3];
        d2 = src[2];
        x19[1] = src[1];
        *x19 = d1;
        x19[3] = d3;
        x19[2] = d2;
    }
    sk_x_00458940(p.lo, a, b, c);
}

/* FUN_0045a1f8 @ 0x0045a1f8   (est. sk_dispatch_0045a1f8)
 * Ghidra: void FUN_0045a1f8(undefined8 param_1..4, char param_5)
 * Frame selector 9/10 handler: mode 2 pushes param_2 via 0036b270; all
 * other modes ignored. Pair of 004592dc but using the 0036b270 helper.
 * Confidence: low */
static void sk_dispatch_0045a1f8(uint64_t arg0, uint64_t arg1, uint64_t arg2,
                                 uint64_t arg3, uint64_t mode)
{
    if (mode == 2) {
        sk_x_0036b270(arg1);
        return;
    }
}

/* FUN_0045a210 @ 0x0045a210   (est. sk_dispatch_0045a210)
 * Ghidra: void FUN_0045a210(void)
 * Composite dispatch: runs 00084220, 00462848, 0045a1f8 (mode gate),
 * 004640d0; stores the w25 byte at x20+0x20, copies extraout_x1+0x28/+0x30
 * into x20, runs 004645d8, copies +0x50/+0x58, and 00084234.
 * Confidence: low
 * Notes: unaff_x20; extraout_x1 register artifact. */
static void sk_dispatch_0045a210(void)
{
    uint64_t extraout_x1 = 0;   /* register artifact */
    uint64_t x20 = 0;           /* unaff register */
    uint8_t w25 = 0;            /* unaff_w25 */
    uint64_t u;

    sk_x_00084220();
    sk_x_00462848();
    sk_dispatch_0045a1f8(0, 0, 0, 0, 0);
    sk_x_004640d0();
    *(uint8_t *)(x20 + 0x20) = w25;
    u = *(uint64_t *)(extraout_x1 + 0x28);
    *(uint64_t *)(x20 + 0x30) = *(uint64_t *)(extraout_x1 + 0x30);
    *(uint64_t *)(x20 + 0x28) = u;
    sk_x_004645d8();
    u = *(uint64_t *)(extraout_x1 + 0x50);
    *(uint64_t *)(x20 + 0x58) = *(uint64_t *)(extraout_x1 + 0x58);
    *(uint64_t *)(x20 + 0x50) = u;
    sk_x_00084234();
}

/* FUN_0045a268 @ 0x0045a268   (est. sk_dispatch_0045a268)
 * Ghidra: void FUN_0045a268(void)
 * Fuller capture than 0045a210: runs 00084220, 00462848, 0045a1f8, 0046303c,
 * 004592dc; copies extraout_x1 words at +0x28..+0x58 and byte +0x48 into
 * the x20 context; runs 00084234.
 * Confidence: low
 * Notes: unaff_x20; extraout_x1 register artifact. */
static void sk_dispatch_0045a268(void)
{
    uint64_t extraout_x1 = 0;   /* register artifact */
    uint64_t x20 = 0;           /* unaff register */
    uint64_t a, b, c, d;

    sk_x_00084220();
    sk_x_00462848();
    sk_dispatch_0045a1f8(0, 0, 0, 0, 0);
    sk_x_0046303c();
    sk_dispatch_004592dc(0, 0, 0, 0, 0);
    b = *(uint64_t *)(extraout_x1 + 0x30);
    a = *(uint64_t *)(extraout_x1 + 0x28);
    d = *(uint64_t *)(extraout_x1 + 0x40);
    c = *(uint64_t *)(extraout_x1 + 0x38);
    *(uint8_t *)(x20 + 0x48) = *(uint8_t *)(extraout_x1 + 0x48);
    *(uint64_t *)(x20 + 0x40) = d;
    *(uint64_t *)(x20 + 0x38) = c;
    *(uint64_t *)(x20 + 0x30) = b;
    *(uint64_t *)(x20 + 0x28) = a;
    *(uint64_t *)(x20 + 0x50) = *(uint64_t *)(extraout_x1 + 0x50);
    *(uint64_t *)(x20 + 0x58) = *(uint64_t *)(extraout_x1 + 0x58);
    sk_x_00084234();
}

/* FUN_0045a2d4 @ 0x0045a2d4   (est. sk_dispatch_0045a2d4)
 * Ghidra: void FUN_0045a2d4(void)
 * Composite capture: runs 00463154, 004592dc; copies x19+0x28/+0x30 into
 * x20, runs 004645d8, copies x19+0x50/+0x58.
 * Confidence: low
 * Notes: unaff_x19/x20. */
static void sk_dispatch_0045a2d4(void)
{
    uint64_t x19 = 0, x20 = 0;  /* unaff registers */
    uint64_t u;

    sk_x_00463154();
    sk_dispatch_004592dc(0, 0, 0, 0, 0);
    u = *(uint64_t *)(x19 + 0x28);
    *(uint64_t *)(x20 + 0x30) = *(uint64_t *)(x19 + 0x30);
    *(uint64_t *)(x20 + 0x28) = u;
    sk_x_004645d8();
    u = *(uint64_t *)(x19 + 0x50);
    *(uint64_t *)(x20 + 0x58) = *(uint64_t *)(x19 + 0x58);
    *(uint64_t *)(x20 + 0x50) = u;
}

/* FUN_0045a3ac @ 0x0045a3ac   (est. sk_dispatch_0045a3ac)
 * Ghidra: void FUN_0045a3ac(undefined8 param_1, undefined8 param_2)
 * Forwards the two caller words plus the 004592dc handler (as a function
 * pointer) into 004607c4.
 * Confidence: low */
static void sk_dispatch_0045a3ac(uint64_t arg0, uint64_t arg1)
{
    sk_x_004607c4(arg0, arg1, &sk_dispatch_004592dc);
}

/* FUN_0045a4b4 @ 0x0045a4b4   (est. sk_dispatch_0045a4b4)
 * Ghidra: void FUN_0045a4b4(undefined8 param_1..8, byte in_stack_00000058)
 * Master syscall-frame dispatcher (mirror of 00459138 using the 0036b270
 * push helper): switch on high nibble of the stack mode byte. 0 = push
 * param_5; 2 = push no args; 3 = 0045a5fc; 9/10 = 0045a1f8; 0xb = 0045a658;
 * 0xd = push param_4 then param_8; 1/4 ignored; > 0xd ignored.
 * Confidence: low
 * Notes: in_stack_00000058 >> 4 selector nibble. */
static void sk_dispatch_0045a4b4(uint64_t arg0, uint64_t arg1, uint64_t arg2,
                                 uint64_t arg3, uint64_t arg4, uint64_t arg5,
                                 uint64_t arg6, uint64_t arg7, uint64_t mode_word)
{
    uint64_t sel = (mode_word >> 4) & 0xff;

    if (0xd < sel) {
        return;
    }
    switch (sel) {
    default:
        arg4 = arg1;
        break;
    case 1:
    case 4:
        return;
    case 2:
        sk_x_0036b270();
        goto push_arg1;
    case 3:
        sk_dispatch_0045a5fc(arg0, arg1, 0, 0, 0);
        return;
    case 9:
    case 10:
        sk_dispatch_0045a1f8(arg0, arg1, 0, 0, 0);
        return;
    case 0xb:
        sk_dispatch_0045a658(arg0, arg1, 0, 0, 0, 0, 0, 0);
        return;
    case 0xc:
        break;
    case 0xd:
        sk_x_0036b270(arg3);
        arg1 = arg7;
push_arg1:
        sk_x_0036b270(arg1);
        return;
    }
    sk_x_0036b270(arg4);
}

/* FUN_0045a5fc @ 0x0045a5fc   (est. sk_dispatch_0045a5fc)
 * Ghidra: void FUN_0045a5fc(undefined8 param_1..4, char param_5)
 * Frame selector 3 handler (mirror of 00459280 using 0036b270): mode 4
 * pushes param_2; mode 0xe pushes param_2 then param_4; mode 7 pushes
 * param_3; other modes ignored.
 * Confidence: low */
static void sk_dispatch_0045a5fc(uint64_t arg0, uint64_t arg1, uint64_t arg2,
                                 uint64_t arg3, uint64_t mode)
{
    if (mode != 4) {
        if (mode == 0xe) {
            sk_x_0036b270(arg1);
            arg1 = arg3;
        } else {
            arg1 = arg2;
            if (mode != 7) {
                return;
            }
        }
    }
    sk_x_0036b270(arg1);
}

/* FUN_0045a658 @ 0x0045a658   (est. sk_dispatch_0045a658)
 * Ghidra: void FUN_0045a658(undefined8 param_1..4, ...)
 * Frame selector 0xb handler (mirror of 004592f4 using 0036b270): mode 2
 * pushes the +0x18 stack word; mode 1 pushes the +0x30 word, param_2, then
 * x7; mode 0 dispatches through 00458b94; other modes ignored.
 * Confidence: low
 * Notes: in_x7 / in_stack artifacts. */
static void sk_dispatch_0045a658(uint64_t arg0, uint64_t arg1, uint64_t arg2,
                                 uint64_t arg3, uint64_t x7, uint64_t st18,
                                 uint64_t st30, uint64_t mode)
{
    if (mode == 2) {
        sk_x_0036b270(st18);
    } else {
        if (mode != 1) {
            if (mode == 0) {
                sk_x_00458b94(arg0, arg1, arg2, arg3);
                return;
            }
            return;
        }
        sk_x_0036b270(st30);
        sk_x_0036b270(arg1);
        arg3 = x7;
    }
    sk_x_0036b270(arg3);
}

/* FUN_0045a6f4 @ 0x0045a6f4   (est. sk_dispatch_0045a6f4)
 * Ghidra: void FUN_0045a6f4(void)
 * Composite capture: runs 00464b04, 00350c5c, 00462bd8 (on extraout_x1),
 * saves the byte at extraout_x1+0x98, runs 00463058, 0034db28, 00464e9c,
 * 004638d8, copies x20+0xa0/+0xa8 into x19, and 00464ae8.
 * Confidence: low
 * Notes: unaff_x19/x20; extraout_x1 register artifact. */
static void sk_dispatch_0045a6f4(void)
{
    uint64_t extraout_x1 = 0;   /* register artifact */
    uint64_t x19 = 0, x20 = 0;  /* unaff registers */
    uint32_t byte98 = 0;
    uint64_t u;

    sk_x_00464b04();
    sk_x_00350c5c();
    sk_x_00462bd8(*((uint64_t *)extraout_x1));
    byte98 = (uint32_t)*(uint8_t *)(extraout_x1 + 0x98);
    sk_x_00463058();
    sk_x_0034db28();
    sk_x_00464e9c();
    sk_x_004638d8();
    u = *(uint64_t *)(x20 + 0xa0);
    *(uint64_t *)(x19 + 0xa8) = *(uint64_t *)(x20 + 0xa8);
    *(uint64_t *)(x19 + 0xa0) = u;
    sk_x_00464ae8();
}

/* FUN_0045a774 @ 0x0045a774   (est. sk_dispatch_0045a774)
 * Ghidra: void FUN_0045a774(void)
 * Large capture: runs 00464b04, 00350c5c, 00462e88, 00462bd8; saves the
 * extraout_x1+0x90 word and +0x98 byte; runs 00463058, 004627d0, 0045a4b4,
 * 00463080, 00463aa0, 00462fec; stores the caller's stack window words
 * [0x68..0xb0] plus the saved word/byte into x19 at +0x40..+0x98; runs
 * 00462b90, 00459138, 004661a4, 00464ae8.
 * Confidence: low
 * Notes: unaff_x19; in_stack artifacts (the caller's saved register window). */
static void sk_dispatch_0045a774(void)
{
    uint64_t extraout_x1 = 0;   /* register artifact */
    uint64_t x19 = 0;           /* unaff register */
    uint64_t w90;
    uint32_t byte98 = 0;
    /* caller stack window (in_stack_00000068..0xb0 register artifacts) */
    uint64_t st68 = 0, st70 = 0, st78 = 0, st80 = 0, st88 = 0;
    uint64_t st90 = 0, st98 = 0, sta0 = 0, sta8 = 0, stb0 = 0;

    sk_x_00464b04();
    sk_x_00350c5c();
    sk_x_00462e88();
    sk_x_00462bd8();
    w90 = *(uint64_t *)(extraout_x1 + 0x90);
    byte98 = (uint32_t)*(uint8_t *)(extraout_x1 + 0x98);
    sk_x_00463058();
    sk_x_004627d0();
    sk_dispatch_0045a4b4(0, 0, 0, 0, 0, 0, 0, 0, 0);
    sk_x_00463080();
    sk_x_00463aa0();
    sk_x_00462fec();
    *(uint64_t *)(x19 + 0x40) = st68;
    *(uint64_t *)(x19 + 0x48) = st70;
    *(uint64_t *)(x19 + 0x50) = st78;
    *(uint64_t *)(x19 + 0x58) = st80;
    *(uint64_t *)(x19 + 0x60) = st88;
    *(uint64_t *)(x19 + 0x68) = st90;
    *(uint64_t *)(x19 + 0x70) = st98;
    *(uint64_t *)(x19 + 0x78) = sta0;
    *(uint64_t *)(x19 + 0x80) = sta8;
    *(uint64_t *)(x19 + 0x88) = stb0;
    *(uint64_t *)(x19 + 0x90) = w90;
    *(uint8_t *)(x19 + 0x98) = (uint8_t)byte98;
    sk_x_00462b90();
    sk_dispatch_00459138(0, 0, 0, 0, 0, 0, 0, 0, 0);
    sk_x_004661a4();
    sk_x_00464ae8();
}

/* FUN_0045a830 @ 0x0045a830   (est. sk_context_copy_0045a830)
 * Ghidra: void FUN_0045a830(void)
 * Copies a wide caller frame (x20 words [0..0x15]) into the x19 context:
 * runs 00350c5c, 00462e54 (on extraout_x1+0x90); copies 18+ words, stores
 * extraout_x8/extraout_w9 at x19[0x12]/+0x13; runs 0034f8e4, 00459138, then
 * copies the final x20[0x14].
 * Confidence: low
 * Notes: unaff_x19/x20; extraout_x1/x8/w9 register artifacts. */
static void sk_context_copy_0045a830(void)
{
    uint64_t extraout_x1 = 0;   /* register artifact */
    uint64_t extraout_x8 = 0;   /* register artifact */
    uint8_t extraout_w9 = 0;    /* register artifact */
    uint64_t *x19 = 0, *x20 = 0;/* unaff registers */
    uint64_t a, b, c;

    sk_x_00350c5c();
    sk_x_00462e54(*(uint64_t *)(extraout_x1 + 0x90));
    a = *x20;
    c = x20[3];
    b = x20[2];
    x19[1] = x20[1];
    *x19 = a;
    x19[3] = c;
    x19[2] = b;
    a = x20[4];
    c = x20[7];
    b = x20[6];
    x19[5] = x20[5];
    x19[4] = a;
    x19[7] = c;
    x19[6] = b;
    a = x20[8];
    c = x20[0xb];
    b = x20[10];
    x19[9] = x20[9];
    x19[8] = a;
    x19[0xb] = c;
    x19[10] = b;
    a = x20[0xc];
    c = x20[0xf];
    b = x20[0xe];
    x19[0xd] = x20[0xd];
    x19[0xc] = a;
    x19[0xf] = c;
    x19[0xe] = b;
    a = x20[0x10];
    x19[0x11] = x20[0x11];
    x19[0x10] = a;
    x19[0x12] = extraout_x8;
    *(uint8_t *)(x19 + 0x13) = extraout_w9;
    sk_x_0034f8e4();
    sk_dispatch_00459138(0, 0, 0, 0, 0, 0, 0, 0, 0);
    a = x20[0x14];
    x19[0x15] = x20[0x15];
    x19[0x14] = a;
}

/* FUN_0045a904 @ 0x0045a904   (est. sk_msg_grow_0045a904)
 * Ghidra: void FUN_0045a904(undefined8 *param_1, uint param_2, uint param_3)
 * Message-buffer grow/resize: for a requested size < 0x32, clears the byte at
 * param_1+0x16 (0x99-basis byte) when param_3 > 0x31 and, when param_2 != 0,
 * runs 004654ec and stores the w20 byte at param_1+0x13. Otherwise zeros the
 * 5-word region [param_1+0x11..0x15], runs 00463358(param_2-0x32), stores
 * extraout_x8 into *param_1, and sets the +0x16 byte to 1 when param_3>0x31.
 * Confidence: low
 * Notes: extraout_x8 / unaff_w20 register artifacts. */
static void sk_msg_grow_0045a904(uint64_t *frame, uint32_t sz, uint32_t flags)
{
    uint64_t extraout_x8 = 0;   /* register artifact */
    uint8_t w20 = 0;            /* unaff_w20 */

    if (sz < 0x32) {
        if (0x31 < flags) {
            *(uint8_t *)((uint64_t)frame + 0x16) = 0;
        }
        if (sz != 0) {
            sk_x_004654ec();
            *(uint8_t *)((uint64_t)frame + 0x13) = w20;
        }
    } else {
        frame[0x15] = 0;
        frame[0x14] = 0;
        frame[0x13] = 0;
        frame[0x12] = 0;
        frame[0x11] = 0;
        sk_x_00463358(sz - 0x32);
        *frame = extraout_x8;
        if (0x31 < flags) {
            *(uint8_t *)((uint64_t)frame + 0x16) = 1;
        }
    }
}

/* FUN_0045a980 @ 0x0045a980   (est. sk_dispatch_0045a980)
 * Ghidra: void FUN_0045a980(undefined8 param_1, undefined8 param_2)
 * Forwards the two caller words plus the 00459138 handler (function pointer)
 * into 0045b1a0.
 * Confidence: low */
static void sk_dispatch_0045a980(uint64_t arg0, uint64_t arg1)
{
    sk_dispatch_0045b1a0(arg0, arg1, (uint64_t)&sk_dispatch_00459138);
}

/* FUN_0045aa44 @ 0x0045aa44   (est. sk_msg_grow_0045aa44)
 * Ghidra: void FUN_0045aa44(undefined8 *param_1, uint param_2, uint param_3)
 * Message-buffer grow (compact variant of 0045a904): small path clears the
 * byte at param_1+0x99 when flags > 0x31 and stores w20 at +0x13 when sz!=0;
 * big path zeros [param_1+0x11..0x12], runs 00463358(sz-0x32), clears +0x13,
 * stores extraout_x8 into *param_1, and sets +0x99 when flags > 0x31.
 * Confidence: low
 * Notes: extraout_x8 / unaff_w20 register artifacts. */
static void sk_msg_grow_0045aa44(uint64_t *frame, uint32_t sz, uint32_t flags)
{
    uint64_t extraout_x8 = 0;   /* register artifact */
    uint8_t w20 = 0;            /* unaff_w20 */

    if (sz < 0x32) {
        if (0x31 < flags) {
            *(uint8_t *)((uint64_t)frame + 0x99) = 0;
        }
        if (sz != 0) {
            sk_x_004654ec();
            *(uint8_t *)((uint64_t)frame + 0x13) = w20;
        }
    } else {
        frame[0x12] = 0;
        frame[0x11] = 0;
        sk_x_00463358(sz - 0x32);
        *(uint8_t *)((uint64_t)frame + 0x13) = 0;
        *frame = extraout_x8;
        if (0x31 < flags) {
            *(uint8_t *)((uint64_t)frame + 0x99) = 1;
        }
    }
}

/* FUN_0045aab0 @ 0x0045aab0   (est. sk_msg_classify_0045aab0)
 * Ghidra: void FUN_0045aab0(ulong *param_1, uint param_2)
 * Message classifier: for a selector < 0xe packs (low 2 bits of byte at
 * param_1+0x13) OR (param_2 << 4) into the +0x13 byte; otherwise stores
 * (param_2-0xe) into *param_1, clears the 0x90-word region from param_1+1
 * via 00114330, and sets the +0x13 byte to 0xe0.
 * Confidence: low
 * Notes: 00114330 is a memset-style helper (thunked). */
static void sk_msg_classify_0045aab0(uint64_t *frame, uint32_t sel)
{
    uint8_t b;

    if (sel < 0xe) {
        b = (uint8_t)(frame[0x13] & 3) | (uint8_t)(sel << 4);
    } else {
        *frame = (uint64_t)(sel - 0xe);
        sk_x_00114330(frame + 1, 0x90);
        b = 0xe0;
    }
    *(uint8_t *)((uint64_t)frame + 0x13) = b;
}

/* FUN_0045ab5c @ 0x0045ab5c   (est. sk_word_copy_0045ab5c)
 * Ghidra: undefined8 *FUN_0045ab5c(undefined8 *param_1, undefined8 *param_2)
 * Copies the 2-word value at param_2 into param_1, pushing both copied words
 * through 0036b270; returns param_1.
 * Confidence: low */
static uint64_t *sk_word_copy_0045ab5c(uint64_t *dst, uint64_t *src)
{
    uint64_t a, b;

    a = src[1];
    b = *src;
    dst[1] = src[1];
    *dst = b;
    sk_x_0036b270(b);
    sk_x_0036b270(a);
    return dst;
}

/* FUN_0045ab9c @ 0x0045ab9c   (est. sk_context_copy_0045ab9c)
 * Ghidra: void FUN_0045ab9c(void)
 * Copies x19+8 into x20+8: runs 003504d0, 00465b1c, pushes via 0036b118,
 * swaps the word (pushing the evicted value through 0036b270).
 * Confidence: low
 * Notes: unaff_x19/x20. */
static void sk_context_copy_0045ab9c(void)
{
    uint64_t x19 = 0, x20 = 0;  /* unaff registers */
    uint64_t u;

    sk_x_003504d0();
    sk_x_00465b1c();
    sk_x_0036b118();
    u = *(uint64_t *)(x20 + 8);
    *(uint64_t *)(x20 + 8) = *(uint64_t *)(x19 + 8);
    sk_x_0036b270();
    sk_x_0036b118(u);
}

/* FUN_0045abec @ 0x0045abec   (est. sk_context_swap_0045abec)
 * Ghidra: void FUN_0045abec(void)
 * Pushes the 003504d0 frame head word, then swaps x20[1]/x20[0] against the
 * x19[1]/x19[0] words, pushing the evicted x20[1].
 * Confidence: low
 * Notes: unaff_x19/x20. */
static void sk_context_swap_0045abec(void)
{
    uint64_t *slot;
    uint64_t u, v;
    uint64_t *x19 = 0, *x20 = 0;  /* unaff registers */

    slot = (uint64_t *)sk_x_003504d0();
    sk_x_0036b118(*slot);
    u = x20[1];
    v = *x19;
    x20[1] = x19[1];
    *x20 = v;
    sk_x_0036b118(u);
}

/* FUN_0045ad90 @ 0x0045ad90   (est. sk_dispatch_0045ad90)
 * Ghidra: void FUN_0045ad90(void)
 * Composite capture: runs 00084220, 00462848, 0045a5fc (mode gate),
 * 004640d0; stores w25 at x20+0x20 and copies the half-word at
 * extraout_x1+0x21 into x20+0x21; runs 00084234.
 * Confidence: low
 * Notes: unaff_x20; extraout_x1 / unaff_w25 register artifacts. */
static void sk_dispatch_0045ad90(void)
{
    uint64_t extraout_x1 = 0;   /* register artifact */
    uint64_t x20 = 0;           /* unaff register */
    uint8_t w25 = 0;            /* unaff_w25 */

    sk_x_00084220();
    sk_x_00462848();
    sk_dispatch_0045a5fc(0, 0, 0, 0, 0);
    sk_x_004640d0();
    *(uint8_t *)(x20 + 0x20) = w25;
    *(uint16_t *)(x20 + 0x21) = *(uint16_t *)(extraout_x1 + 0x21);
    sk_x_00084234();
}

/* FUN_0045addc @ 0x0045addc   (est. sk_dispatch_0045addc)
 * Ghidra: void FUN_0045addc(void)
 * Composite capture: runs 00084220, 00462848, 0045a5fc, 0046303c, 00459280,
 * then 00465770, and finally 00084234 with the two results.
 * Confidence: low
 * Notes: unaff_x30 register artifact. */
static void sk_dispatch_0045addc(void)
{
    uint64_t u;
    uint64_t unaff_x30 = 0;     /* register artifact */

    sk_x_00084220();
    sk_x_00462848();
    sk_dispatch_0045a5fc(0, 0, 0, 0, 0);
    sk_x_0046303c();
    sk_dispatch_00459280(0, 0, 0, 0, 0);
    u = sk_x_00465770();
    sk_x_00084234(u, unaff_x30);
}

/* FUN_0045ae20 @ 0x0045ae20   (est. sk_dispatch_0045ae20)
 * Ghidra: void FUN_0045ae20(void)
 * Composite: runs 00463154, 00459280, then 00465770.
 * Confidence: low */
static void sk_dispatch_0045ae20(void)
{
    sk_x_00463154();
    sk_dispatch_00459280(0, 0, 0, 0, 0);
    sk_x_00465770();
}

/* FUN_0045b1a0 @ 0x0045b1a0   (est. sk_dispatch_0045b1a0)
 * Ghidra: void FUN_0045b1a0(long param_1, undefined8 param_2,
 *                           undefined8 param_3)
 * Dispatch driver: resolves the frame via 004644cc(param_3, param_1,
 * *(param_1+8)), forwards five words from the resolved frame (+0x40..+0x80)
 * into 0034f8e4, then tail-calls the recovered code pointer.
 * Confidence: low
 * Notes: extraout_x8/x9 register artifacts; indirect tail call. */
static void sk_dispatch_0045b1a0(uint64_t arg0, uint64_t arg1, uint64_t handler)
{
    uint64_t frame;
    void (*tail_fn)(uint64_t) = 0;  /* extraout_x8 */

    frame = sk_x_004644cc(handler, arg0, *(uint64_t *)(arg0 + 8));
    sk_x_0034f8e4(*(uint64_t *)(frame + 0x40), *(uint64_t *)(frame + 0x50),
                  *(uint64_t *)(frame + 0x60), *(uint64_t *)(frame + 0x70),
                  *(uint64_t *)(frame + 0x80));
    if (tail_fn) {
        tail_fn(0);
    }
}

/* FUN_0045b1f4 @ 0x0045b1f4   (est. sk_dispatch_0045b1f4)
 * Ghidra: void FUN_0045b1f4(void)
 * Dispatch driver: obtains a 16-byte descriptor from 00466408, captures the
 * frame words [8..0x13], calls 0034f3b4 with the 0045a658 handler and the
 * first two frame words, runs 00462fec, writes the captured words/byte into
 * the descriptor's lo frame at +0x40..+0x98, then 004663ec(frame, unaff_x30).
 * Confidence: low
 * Notes: unaff_x30; extraout_x8 register artifact. */
static void sk_dispatch_0045b1f4(void)
{
    uint64_t *frame;
    uint64_t base;
    uint64_t a, b, c, d, e, f, g, h, i, j, k;
    uint32_t byte13;
    uint64_t unaff_x30 = 0;     /* register artifact */
    sk_pair_t p;

    p = sk_x_00466408();
    frame = (uint64_t *)p.hi;
    base = p.lo;
    a = frame[8];
    b = frame[9];
    c = frame[10];
    d = frame[0xb];
    e = frame[0xc];
    f = frame[0xd];
    g = frame[0xe];
    h = frame[0xf];
    i = frame[0x10];
    j = frame[0x11];
    k = frame[0x12];
    byte13 = (uint32_t)*(uint8_t *)((uint64_t)frame + 0x13);
    sk_x_0034f3b4(&sk_dispatch_0045a658, *frame, frame[1]);
    sk_x_00462fec();
    *(uint64_t *)(base + 0x40) = a;
    *(uint64_t *)(base + 0x48) = b;
    *(uint64_t *)(base + 0x50) = c;
    *(uint64_t *)(base + 0x58) = d;
    *(uint64_t *)(base + 0x60) = e;
    *(uint64_t *)(base + 0x68) = f;
    *(uint64_t *)(base + 0x70) = g;
    *(uint64_t *)(base + 0x78) = h;
    *(uint64_t *)(base + 0x80) = i;
    *(uint64_t *)(base + 0x88) = j;
    *(uint64_t *)(base + 0x90) = k;
    *(uint8_t *)(base + 0x98) = (uint8_t)byte13;
    sk_x_004663ec(base, unaff_x30);
}

/* FUN_0045b330 @ 0x0045b330   (est. sk_dispatch_0045b330)
 * Ghidra: void FUN_0045b330(void)
 * Dispatch driver (capture variant): resolves 00464b04, runs 00462e88, saves
 * the extraout_x1 frame words [0x40..0x90] and +0x98 byte, runs 004627d0,
 * then 004640d0 with the raw frame words, writes the caller window (x25..x28)
 * and saved words into the frame, runs 00462b90, tail-calls in_x4, then
 * 00464ae8.
 * Confidence: low
 * Notes: unaff_x25..x28/x30; in_x3/in_x4/extraout_x1/x8 register artifacts. */
static void sk_dispatch_0045b330(void)
{
    uint64_t *frame;
    uint64_t a, b, c, d, e, f, g, h, i, j, k;
    uint64_t extraout_x1 = 0;   /* register artifact */
    uint64_t in_x3 = 0;
    void (*in_x4)(void) = 0;
    uint64_t unaff_x25 = 0, unaff_x26 = 0, unaff_x27 = 0, unaff_x28 = 0;
    uint64_t unaff_x30 = 0;
    uint32_t byte98;

    frame = (uint64_t *)sk_x_00464b04();
    sk_x_00462e88(in_x3);
    a = *(uint64_t *)(extraout_x1 + 0x40);
    b = *(uint64_t *)(extraout_x1 + 0x48);
    c = *(uint64_t *)(extraout_x1 + 0x50);
    d = *(uint64_t *)(extraout_x1 + 0x58);
    e = *(uint64_t *)(extraout_x1 + 0x60);
    f = *(uint64_t *)(extraout_x1 + 0x68);
    g = *(uint64_t *)(extraout_x1 + 0x70);
    h = *(uint64_t *)(extraout_x1 + 0x78);
    i = *(uint64_t *)(extraout_x1 + 0x80);
    j = *(uint64_t *)(extraout_x1 + 0x88);
    k = *(uint64_t *)(extraout_x1 + 0x90);
    byte98 = (uint32_t)*(uint8_t *)(extraout_x1 + 0x98);
    sk_x_004627d0();
    sk_x_004640d0(frame[0x12], frame[8], frame[10], frame[0xc], frame[0xe],
                  frame[0x10], frame[0], frame[1], frame[2], frame[3],
                  frame[4], frame[5], frame[6], frame[7]);
    frame[4] = unaff_x25;
    frame[5] = unaff_x26;
    frame[6] = unaff_x27;
    frame[7] = unaff_x28;
    frame[8] = a;
    frame[9] = b;
    frame[10] = c;
    frame[0xb] = d;
    frame[0xc] = e;
    frame[0xd] = f;
    frame[0xe] = g;
    frame[0xf] = h;
    frame[0x10] = i;
    frame[0x11] = j;
    frame[0x12] = k;
    *(uint8_t *)((uint64_t)frame + 0x13) = (uint8_t)byte98;
    sk_x_00462b90();
    if (in_x4) {
        in_x4();
    }
    sk_x_00464ae8(frame, unaff_x30);
}

/* FUN_0045b458 @ 0x0045b458   (est. sk_context_copy_0045b458)
 * Ghidra: undefined8 *FUN_0045b458(undefined1 param_1[16],
 *        undefined1 param_2[16], undefined8 *param_3, ...)
 * Wide context copy: builds a descriptor via 00463028, copies the extraout_x1
 * frame words [0..0x11] into param_3[0..0x11] (plus extraout_x10/+0x13 byte),
 * runs 0034f8e4 with the captured values, tail-calls extraout_x8, returns
 * param_3.
 * Confidence: low
 * Notes: extraout_x1/x8/x9/x10/w11 register artifacts. */
static uint64_t *sk_context_copy_0045b458(uint8_t param_a[16], uint8_t param_b[16],
                                          uint64_t *dst, uint64_t arg3,
                                          uint64_t arg4, uint64_t arg5)
{
    uint64_t *src;
    uint64_t extraout_x9 = 0, extraout_x10 = 0;
    uint8_t extraout_w11 = 0;
    void (*tail_fn)(uint64_t, uint64_t) = 0;  /* extraout_x8 */
    sk_pair_t d;
    uint64_t a, b, c;

    d = sk_x_00463028(arg5, *dst, arg3, dst[2]);
    a = dst[0xc];
    b = dst[0xe];
    c = dst[0x10];
    src = (uint64_t *)d.hi;
    dst[1] = src[1];
    *dst = *src;
    dst[3] = src[3];
    dst[2] = src[2];
    dst[5] = src[5];
    dst[4] = src[4];
    dst[7] = src[7];
    dst[6] = src[6];
    dst[9] = src[9];
    dst[8] = src[8];
    dst[0xb] = src[0xb];
    dst[10] = src[10];
    dst[0xd] = src[0xd];
    dst[0xc] = src[0xc];
    dst[0xf] = src[0xf];
    dst[0xe] = src[0xe];
    dst[0x11] = src[0x11];
    dst[0x10] = src[0x10];
    dst[0x12] = extraout_x10;
    *(uint8_t *)((uint64_t)dst + 0x13) = extraout_w11;
    sk_x_0034f8e4(d.lo, param_b, a, b, c);
    if (tail_fn) {
        tail_fn(0, extraout_x9);
    }
    return dst;
}

/* FUN_0045b5a8 @ 0x0045b5a8   (est. sk_dispatch_0045b5a8)
 * Ghidra: void FUN_0045b5a8(void)
 * Composite capture: runs 00084220, 00462848, 00458b94, 004640d0; stores
 * w25 at x20+0x20, runs 004653cc, then 00084234 with both.
 * Confidence: low
 * Notes: unaff_x20; extraout/unaff register artifacts. */
static void sk_dispatch_0045b5a8(void)
{
    uint64_t u;
    uint64_t x20 = 0;           /* unaff register */
    uint8_t w25 = 0;            /* unaff_w25 */
    uint64_t unaff_x30 = 0;     /* register artifact */

    sk_x_00084220();
    sk_x_00462848();
    sk_x_00458b94();
    sk_x_004640d0();
    *(uint8_t *)(x20 + 0x20) = w25;
    u = sk_x_004653cc();
    sk_x_00084234(u, unaff_x30);
}

/* FUN_0045b5ec @ 0x0045b5ec   (est. sk_dispatch_0045b5ec)
 * Ghidra: void FUN_0045b5ec(void)
 * Composite: runs 00084220, 00462848, 00458b94, 0046303c, 00458bac,
 * 004632b8, then 00084234.
 * Confidence: low */
static void sk_dispatch_0045b5ec(void)
{
    sk_x_00084220();
    sk_x_00462848();
    sk_x_00458b94();
    sk_x_0046303c();
    sk_x_00458bac();
    sk_x_004632b8();
    sk_x_00084234();
}

/* FUN_0045b634 @ 0x0045b634   (est. sk_dispatch_0045b634)
 * Ghidra: void FUN_0045b634(void)
 * Composite: runs 00463154, 00458bac, then 004653cc.
 * Confidence: low */
static void sk_dispatch_0045b634(void)
{
    sk_x_00463154();
    sk_x_00458bac();
    sk_x_004653cc();
}

/* FUN_0045b7f4 @ 0x0045b7f4   (est. sk_dispatch_0045b7f4)
 * Ghidra: void FUN_0045b7f4(void)
 * Release shim: runs 004666c0, pushes the x19+0x38 word via 003a25d4, and
 * pushes the x19+0x70 word via 0036b118.
 * Confidence: low
 * Notes: unaff_x19. */
static void sk_dispatch_0045b7f4(void)
{
    uint64_t x19 = 0;           /* unaff register */

    sk_x_004666c0();
    sk_x_003a25d4(*(uint64_t *)(x19 + 0x38));
    sk_x_0036b118(*(uint64_t *)(x19 + 0x70));
}

/* FUN_0045b824 @ 0x0045b824   (est. sk_context_copy_0045b824)
 * Ghidra: void FUN_0045b824(void)
 * Copies the extraout_x1 context words at +0x40..+0x80 into the x19 frame
 * (with 0036b270 pushes of the evicted values): runs 00355938, 00465f20.
 * Confidence: low
 * Notes: unaff_x19; extraout_x1 register artifact. */
static void sk_context_copy_0045b824(void)
{
    uint64_t extraout_x1 = 0;   /* register artifact */
    uint64_t x19 = 0;           /* unaff register */
    uint64_t a, b, c;

    sk_x_00355938();
    sk_x_00465f20();
    a = *(uint64_t *)(extraout_x1 + 0x40);
    c = *(uint64_t *)(extraout_x1 + 0x58);
    b = *(uint64_t *)(extraout_x1 + 0x50);
    *(uint64_t *)(x19 + 0x48) = *(uint64_t *)(extraout_x1 + 0x48);
    *(uint64_t *)(x19 + 0x40) = a;
    *(uint64_t *)(x19 + 0x58) = c;
    *(uint64_t *)(x19 + 0x50) = b;
    a = *(uint64_t *)(extraout_x1 + 0x60);
    *(uint64_t *)(x19 + 0x68) = *(uint64_t *)(extraout_x1 + 0x68);
    *(uint64_t *)(x19 + 0x60) = a;
    a = *(uint64_t *)(extraout_x1 + 0x70);
    *(uint64_t *)(x19 + 0x70) = a;
    b = *(uint64_t *)(extraout_x1 + 0x78);
    *(uint64_t *)(x19 + 0x80) = *(uint64_t *)(extraout_x1 + 0x80);
    *(uint64_t *)(x19 + 0x78) = b;
    sk_x_0036b270();
    sk_x_0036b270();
    sk_x_0036b270(a);
}

/* FUN_0045b888 @ 0x0045b888   (est. sk_context_copy_0045b888)
 * Ghidra: void FUN_0045b888(undefined8 param_1, long param_2)
 * Copies a source context (param_2) into the x19 frame: runs 0034f2f4;
 * copies words at +8, +0x10, +0x28..+0x50, +0x68 (from 004656e0),
 * +0x70, +0x78, +0x80, pushing evicted values through 0036b270/003a25d4.
 * Confidence: low
 * Notes: unaff_x19; extraout_x1/x8 register artifacts. */
static void sk_context_copy_0045b888(uint64_t arg0, uint64_t src)
{
    uint64_t extraout_x1 = 0;   /* register artifact */
    uint64_t extraout_x8 = 0;   /* register artifact */
    uint64_t x19 = 0;           /* unaff register */
    uint64_t u;

    sk_x_0034f2f4();
    u = *(uint64_t *)(x19 + 8);
    *(uint64_t *)(x19 + 8) = *(uint64_t *)(extraout_x1 + 8);
    sk_x_0036b270();
    sk_x_003a25d4(u);
    *(uint64_t *)(x19 + 0x10) = *(uint64_t *)(src + 0x10);
    sk_x_00466034();
    *(uint64_t *)(x19 + 0x28) = *(uint64_t *)(src + 0x28);
    *(uint64_t *)(x19 + 0x30) = *(uint64_t *)(src + 0x30);
    u = *(uint64_t *)(x19 + 0x38);
    *(uint64_t *)(x19 + 0x38) = *(uint64_t *)(src + 0x38);
    sk_x_0036b270();
    sk_x_003a25d4(u);
    *(uint64_t *)(x19 + 0x40) = *(uint64_t *)(src + 0x40);
    *(uint64_t *)(x19 + 0x48) = *(uint64_t *)(src + 0x48);
    *(uint64_t *)(x19 + 0x50) = *(uint64_t *)(src + 0x50);
    sk_x_004656e0();
    *(uint64_t *)(x19 + 0x68) = extraout_x8;
    u = *(uint64_t *)(x19 + 0x70);
    *(uint64_t *)(x19 + 0x70) = *(uint64_t *)(src + 0x70);
    sk_x_0036b270();
    sk_x_0036b118(u);
    *(uint64_t *)(x19 + 0x78) = *(uint64_t *)(src + 0x78);
    *(uint64_t *)(x19 + 0x80) = *(uint64_t *)(src + 0x80);
}

/* FUN_0045b954 @ 0x0045b954   (est. sk_context_copy_0045b954)
 * Ghidra: void FUN_0045b954(void)
 * Copies x19 context words into the x20 frame: runs 0046337c, 00465a50;
 * copies +0x40..+0x80, pushing evicted values via 0036b118.
 * Confidence: low
 * Notes: unaff_x19/x20. */
static void sk_context_copy_0045b954(void)
{
    uint64_t x19 = 0, x20 = 0;  /* unaff registers */
    uint64_t a, b, c;

    sk_x_0046337c();
    sk_x_00465a50();
    a = *(uint64_t *)(x19 + 0x40);
    c = *(uint64_t *)(x19 + 0x58);
    b = *(uint64_t *)(x19 + 0x50);
    *(uint64_t *)(x20 + 0x48) = *(uint64_t *)(x19 + 0x48);
    *(uint64_t *)(x20 + 0x40) = a;
    *(uint64_t *)(x20 + 0x58) = c;
    *(uint64_t *)(x20 + 0x50) = b;
    a = *(uint64_t *)(x19 + 0x60);
    *(uint64_t *)(x20 + 0x68) = *(uint64_t *)(x19 + 0x68);
    *(uint64_t *)(x20 + 0x60) = a;
    a = *(uint64_t *)(x20 + 0x70);
    *(uint64_t *)(x20 + 0x70) = *(uint64_t *)(x19 + 0x70);
    sk_x_0036b118(a);
    a = *(uint64_t *)(x19 + 0x78);
    *(uint64_t *)(x20 + 0x80) = *(uint64_t *)(x19 + 0x80);
    *(uint64_t *)(x20 + 0x78) = a;
}

/* FUN_0045ba44 @ 0x0045ba44   (est. sk_context_copy_0045ba44)
 * Ghidra: void FUN_0045ba44(void)
 * Copies extraout_x1+0x10/+0x18/+0x20 into x19, then pushes via 0036b270.
 * Runs 00350e04.
 * Confidence: low
 * Notes: unaff_x19; extraout_x1 register artifact. */
static void sk_context_copy_0045ba44(void)
{
    uint64_t extraout_x1 = 0;   /* register artifact */
    uint64_t x19 = 0;           /* unaff register */
    uint64_t u;

    sk_x_00350e04();
    *(uint64_t *)(x19 + 0x10) = *(uint64_t *)(extraout_x1 + 0x10);
    u = *(uint64_t *)(extraout_x1 + 0x18);
    *(uint64_t *)(x19 + 0x20) = *(uint64_t *)(extraout_x1 + 0x20);
    *(uint64_t *)(x19 + 0x18) = u;
    sk_x_0036b270();
}

/* FUN_0045ba7c @ 0x0045ba7c   (est. sk_dispatch_0045ba7c)
 * Ghidra: void FUN_0045ba7c(void)
 * Composite: runs 0034b264, 00463a10, pushes via 0036b270 and 0036b118,
 * then 00463750.
 * Confidence: low */
static void sk_dispatch_0045ba7c(void)
{
    sk_x_0034b264();
    sk_x_00463a10();
    sk_x_0036b270();
    sk_x_0036b118();
    sk_x_00463750();
}

/* FUN_0045babc @ 0x0045babc   (est. sk_context_copy_0045babc)
 * Ghidra: void FUN_0045babc(void)
 * Copies the 16-byte descriptor (0046306c) frames' +0x10 word and the
 * x19+0x18/+0x20 words into x20, pushing the evicted +0x10 value via
 * 0036b118.
 * Confidence: low
 * Notes: unaff_x19/x20. */
static void sk_context_copy_0045babc(void)
{
    uint64_t x19 = 0, x20 = 0;  /* unaff registers */
    uint64_t u;
    sk_pair_t p;

    p = sk_x_0046306c();
    u = *(uint64_t *)(p.lo + 0x10);
    *(uint64_t *)(x20 + 0x10) = *(uint64_t *)(p.hi + 0x10);
    sk_x_0036b118(u);
    u = *(uint64_t *)(x19 + 0x18);
    *(uint64_t *)(x20 + 0x20) = *(uint64_t *)(x19 + 0x20);
    *(uint64_t *)(x20 + 0x18) = u;
}

/* FUN_0045bb84 @ 0x0045bb84   (est. sk_release_0045bb84)
 * Ghidra: void FUN_0045bb84(long param_1)
 * Release shim: pushes the words at param_1+0x18 and param_1+0x58 via
 * 003a25d4.
 * Confidence: low */
static void sk_release_0045bb84(uint64_t base)
{
    sk_x_003a25d4(*(uint64_t *)(base + 0x18));
    sk_x_003a25d4(*(uint64_t *)(base + 0x58));
}

/* FUN_0045bbb4 @ 0x0045bbb4   (est. sk_context_copy_0045bbb4)
 * Ghidra: void FUN_0045bbb4(void)
 * Two-stage context copy into x19: runs 00350e04 then copies the
 * extraout_x1 words +0x10..+0x18; runs 00465eec then copies the
 * extraout_x1_00 words +0x50..+0x90; pushes via 0036b270/003a25d4.
 * Confidence: low
 * Notes: unaff_x19; extraout_x1/extraout_x1_00 register artifacts. */
static void sk_context_copy_0045bbb4(void)
{
    uint64_t extraout_x1 = 0;   /* register artifact (first stage) */
    uint64_t extraout_x1_00 = 0;/* register artifact (second stage) */
    uint64_t x19 = 0;           /* unaff register */
    uint64_t u, a, b, c;

    sk_x_00350e04();
    u = *(uint64_t *)(extraout_x1 + 0x18);
    *(uint64_t *)(x19 + 0x10) = *(uint64_t *)(extraout_x1 + 0x10);
    *(uint64_t *)(x19 + 0x18) = u;
    sk_x_00465eec();
    u = *(uint64_t *)(extraout_x1_00 + 0x58);
    *(uint64_t *)(x19 + 0x50) = *(uint64_t *)(extraout_x1_00 + 0x50);
    *(uint64_t *)(x19 + 0x58) = u;
    a = *(uint64_t *)(extraout_x1_00 + 0x60);
    c = *(uint64_t *)(extraout_x1_00 + 0x78);
    b = *(uint64_t *)(extraout_x1_00 + 0x70);
    *(uint64_t *)(x19 + 0x68) = *(uint64_t *)(extraout_x1_00 + 0x68);
    *(uint64_t *)(x19 + 0x60) = a;
    *(uint64_t *)(x19 + 0x78) = c;
    *(uint64_t *)(x19 + 0x70) = b;
    *(uint64_t *)(x19 + 0x90) = *(uint64_t *)(extraout_x1_00 + 0x90);
    a = *(uint64_t *)(extraout_x1_00 + 0x80);
    *(uint64_t *)(x19 + 0x88) = *(uint64_t *)(extraout_x1_00 + 0x88);
    *(uint64_t *)(x19 + 0x80) = a;
    sk_x_0036b270();
    sk_x_0036b270(u);
}

/* FUN_0045bc10 @ 0x0045bc10   (est. sk_context_copy_0045bc10)
 * Ghidra: void FUN_0045bc10(void)
 * Wide context copy into x20: runs 0034b264, 00463484, 00464504, 004632b8,
 * 00466220, 00465d28; copies x19 words +0x50..+0x90 and byte +0x80, pushing
 * evicted values.
 * Confidence: low
 * Notes: unaff_x19/x20. */
static void sk_context_copy_0045bc10(void)
{
    uint64_t x19 = 0, x20 = 0;  /* unaff registers */
    uint64_t u;

    sk_x_0034b264();
    sk_x_00463484();
    sk_x_0036b270();
    sk_x_003a25d4();
    sk_x_00464504();
    sk_x_004632b8();
    sk_x_00466220();
    sk_x_00465d28();
    *(uint64_t *)(x20 + 0x50) = *(uint64_t *)(x19 + 0x50);
    u = *(uint64_t *)(x20 + 0x58);
    *(uint64_t *)(x20 + 0x58) = *(uint64_t *)(x19 + 0x58);
    sk_x_0036b270();
    sk_x_003a25d4(u);
    *(uint64_t *)(x20 + 0x60) = *(uint64_t *)(x19 + 0x60);
    *(uint64_t *)(x20 + 0x68) = *(uint64_t *)(x19 + 0x68);
    sk_x_00465f68();
    *(uint8_t *)(x20 + 0x80) = *(uint8_t *)(x19 + 0x80);
    *(uint64_t *)(x20 + 0x88) = *(uint64_t *)(x19 + 0x88);
    *(uint64_t *)(x20 + 0x90) = *(uint64_t *)(x19 + 0x90);
}

/* FUN_0045bcb0 @ 0x0045bcb0   (est. sk_context_copy_0045bcb0)
 * Ghidra: void FUN_0045bcb0(void)
 * Wide context copy into x20: copies the 0046306c descriptor frames' +0x10/
 * +0x18 words (pushing evicted +0x18), runs 00466374, copies x19 words
 * +0x50..+0x90 and byte +0x80.
 * Confidence: low
 * Notes: unaff_x19/x20. */
static void sk_context_copy_0045bcb0(void)
{
    uint64_t x19 = 0, x20 = 0;  /* unaff registers */
    uint64_t a, b, c;
    sk_pair_t p;

    p = sk_x_0046306c();
    a = *(uint64_t *)(p.hi + 0x18);
    b = *(uint64_t *)(p.lo + 0x18);
    *(uint64_t *)(x20 + 0x10) = *(uint64_t *)(p.hi + 0x10);
    *(uint64_t *)(x20 + 0x18) = a;
    sk_x_003a25d4(b);
    sk_x_00466374();
    a = *(uint64_t *)(x19 + 0x58);
    b = *(uint64_t *)(x20 + 0x58);
    *(uint64_t *)(x20 + 0x50) = *(uint64_t *)(x19 + 0x50);
    *(uint64_t *)(x20 + 0x58) = a;
    sk_x_003a25d4(b);
    a = *(uint64_t *)(x19 + 0x60);
    c = *(uint64_t *)(x19 + 0x78);
    b = *(uint64_t *)(x19 + 0x70);
    *(uint64_t *)(x20 + 0x68) = *(uint64_t *)(x19 + 0x68);
    *(uint64_t *)(x20 + 0x60) = a;
    *(uint64_t *)(x20 + 0x78) = c;
    *(uint64_t *)(x20 + 0x70) = b;
    *(uint8_t *)(x20 + 0x80) = *(uint8_t *)(x19 + 0x80);
    a = *(uint64_t *)(x19 + 0x88);
    *(uint64_t *)(x20 + 0x90) = *(uint64_t *)(x19 + 0x90);
    *(uint64_t *)(x20 + 0x88) = a;
}
