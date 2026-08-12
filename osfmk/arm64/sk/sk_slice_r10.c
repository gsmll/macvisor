/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel, GL1,
 * arm64e, image base 0) — the cL4 microkernel. Ground truth: Ghidra FUN_ names +
 * addresses in the cl4_kernel.raw program. Names use seL4/cL4 vocabulary; all
 * are estimates unless string/header matched.
 *
 * Slice 0x003eefc0-0x003f4164 (worker SKR10): the operation-dispatch /
 * continuation subsystem of the cap-invocation machinery. Each handler opens
 * the running op context (x22), seeds its per-invocation fields, allocates a
 * per-op frame via the frame allocator, links a continuation (vtable or code
 * label) into it, and tail-dispatches through the context's reply dispatch.
 * The slice also contains the abort/trap chains (SoftwareBreakpoint spin
 * entries) and several trace-record builders used by the debug log.
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
static inline void sk_break(uint64_t a, uint64_t b) __attribute__((noreturn))
{ (void)a; (void)b; __asm__ volatile("brk #1"); }
#define SoftwareBreakpoint(a,b) sk_break((uint64_t)(a),(uint64_t)(b))
/* Signed carry-out of (a+b) / borrow-out of (a-b), mirroring Ghidra SCARRY8 /
 * SBORROW8 used as the bounds checks on the descriptor advance arithmetic. */
static inline int sk_scarry8(int64_t a, int64_t b) { int64_t r; return __builtin_add_overflow(a, b, &r); }
static inline int sk_sborrow8(int64_t a, int64_t b) { int64_t r; return __builtin_sub_overflow(a, b, &r); }
#define SCARRY8(a,b) sk_scarry8((int64_t)(a),(int64_t)(b))
#define SBORROW8(a,b) sk_sborrow8((int64_t)(a),(int64_t)(b))
/* Concatenate a 7-byte value with an 8-bit value into a full word (Ghidra
 * CONCAT71), used when packing a trace record's tail field. */
#define CONCAT71(hi7, lo1) (((uint64_t)(hi7) << 8) | (uint64_t)(uint8_t)(lo1))
#define SK_CANARY (-0x2c8502b44bfffed6LL)

/* ------------------------------------------------------------------ *
 * Globals referenced by this slice (image-base addresses are the Ghidra
 * ground truth).
 * ------------------------------------------------------------------ */
extern uint32_t sk_g_005a01dc;   /* DAT_005a01dc: op-frame size class */
extern uint32_t sk_g_005a0234;   /* DAT_005a0234: op-frame size class */
extern uint64_t sk_g_00405fec;   /* DAT_00405fec: reply vtable */
extern uint64_t sk_g_004edcd0;   /* DAT_004edcd0: string/descriptor table */
extern uint64_t sk_g_005a16f8;   /* DAT_005a16f8: size/alloc table */
extern uint64_t sk_g_006adf70;   /* _DAT_006adf70: global object pointer */
extern uint64_t sk_g_00658c80;   /* DAT_00658c80: function pointer (trap hook) */
extern uint8_t  sk_g_005dc160[]; /* s_Illegal_attempt_to_set_a_TaskLoc_005dc160 */
extern uint8_t  sk_g_005dc140[]; /* s__Concurrency_TaskLocal_swift_005dc140 */

/* ------------------------------------------------------------------ *
 * Out-of-slice callees (reconstructed by other slice workers). The
 * sk_x_XXXXXXXX names encode the Ghidra FUN_ address. Functions that Ghidra
 * shows returning a 16-byte register pair are typed cl4_result_t.
 * ------------------------------------------------------------------ */
extern unsigned long sk_x_00002534();
extern unsigned long sk_x_000027e8();
extern unsigned long sk_x_0001a1c8();
extern unsigned long sk_x_00027724();
extern unsigned long sk_x_0007c028();
extern cl4_result_t sk_x_0007c1c4();
extern unsigned long sk_x_000839d8();
extern unsigned long sk_x_000839f8();
extern unsigned long sk_x_0008409c();
extern unsigned long sk_x_00084180();
extern unsigned long sk_x_0008e1ec();
extern unsigned long sk_x_000b430c();
extern unsigned long sk_x_000e15d8();
extern unsigned long sk_x_000e46d0();
extern unsigned long sk_x_000e72d4();
extern unsigned long sk_x_00100c04();
extern unsigned long sk_x_0011aa70();
extern unsigned long sk_x_0019cb68();
extern unsigned long sk_x_001a26e0();
extern unsigned long sk_x_001a8564();
extern unsigned long sk_x_001afa84();
extern unsigned long sk_x_001b1780();
extern cl4_result_t sk_x_001d88fc();
extern unsigned long sk_x_001ee018();
extern unsigned long sk_x_00208418();
extern unsigned long sk_x_00213834();
extern unsigned long sk_x_002298d4();
extern unsigned long sk_x_0022b584();
extern unsigned long sk_x_00251758();
extern unsigned long sk_x_00251820();
extern unsigned long sk_x_0028c754();
extern unsigned long sk_x_002a4468();
extern unsigned long sk_x_002a4ab4();
extern unsigned long sk_x_002acbb8();
extern unsigned long sk_x_002d49f4();
extern unsigned long sk_x_00310d68();
extern unsigned long sk_x_0031b080();
extern unsigned long sk_x_0031b37c();
extern unsigned long sk_x_0031dc0c();
extern unsigned long sk_x_0031de7c();
extern unsigned long sk_x_0034bcf0();
extern unsigned long sk_x_0034c2e8();
extern unsigned long sk_x_003504a0();
extern unsigned long sk_x_003504ac();
extern unsigned long sk_x_003504c4();
extern unsigned long sk_x_003504e8();
extern unsigned long sk_x_00350738();
extern unsigned long sk_x_00350744();
extern unsigned long sk_x_00350750();
extern unsigned long sk_x_00350798();
extern unsigned long sk_x_00350884();
extern unsigned long sk_x_0035098c();
extern unsigned long sk_x_003509c8();
extern unsigned long sk_x_00350b54();
extern unsigned long sk_x_003510c4();
extern unsigned long sk_x_00351124();
extern cl4_result_t sk_x_00351330();
extern unsigned long sk_x_0035136c();
extern unsigned long sk_x_00351384();
extern unsigned long sk_x_00351790();
extern unsigned long sk_x_00351d24();
extern unsigned long sk_x_00352018();
extern cl4_result_t sk_x_003522b8();
extern unsigned long sk_x_00352efc();
extern unsigned long sk_x_00353080();
extern unsigned long sk_x_00353498();
extern unsigned long sk_x_003539e4();
extern unsigned long sk_x_00353c00();
extern unsigned long sk_x_00356590();
extern unsigned long sk_x_003565a8();
extern unsigned long sk_x_00359024();
extern unsigned long sk_x_003593c0();
extern unsigned long sk_x_0035ac70();
extern cl4_result_t sk_x_00369340();
extern unsigned long sk_x_0036986c();
extern unsigned long sk_x_0036a940();
extern unsigned long sk_x_0036b118();
extern unsigned long sk_x_0036b270();
extern unsigned long sk_x_0036b6ac();
extern unsigned long sk_x_003f3960();
extern cl4_result_t sk_x_00376820();
extern unsigned long sk_x_003a25d4();
extern unsigned long sk_x_003d4658();
extern unsigned long sk_x_003eeb6c();
extern unsigned long sk_x_003f41b8();
extern unsigned long sk_x_003fd3ac();
extern unsigned long sk_x_00404f60();
extern unsigned long sk_x_0040633c();
extern unsigned long sk_x_00406394();
extern unsigned long sk_x_00406444();
extern unsigned long sk_x_004064c4();
extern unsigned long sk_x_00406518();
extern unsigned long sk_x_00406590();
extern unsigned long sk_x_00406734();
extern unsigned long sk_x_0040676c();
extern unsigned long sk_x_0040677c();
extern cl4_result_t sk_x_0040678c();
extern unsigned long sk_x_0040683c();
extern unsigned long sk_x_0040686c();
extern unsigned long sk_x_00406894();
extern unsigned long sk_x_0040691c();
extern unsigned long sk_x_00406a94();
extern unsigned long sk_x_00406af4();
extern unsigned long sk_x_00406c5c();
extern unsigned long sk_x_00406c98();
extern cl4_result_t sk_x_00406fd4();
extern unsigned long sk_x_00406fe0();
extern cl4_result_t sk_x_00407000();
extern unsigned long sk_x_0040700c();
extern unsigned long sk_x_00407018();
extern unsigned long sk_x_00407024();
extern unsigned long sk_x_00407030();
extern unsigned long sk_x_00407048();
extern unsigned long sk_x_004070cc();
extern unsigned long sk_x_004070d8();
extern unsigned long sk_x_0040711c();
extern cl4_result_t sk_x_00407128();
extern unsigned long sk_x_00407158();
extern unsigned long sk_x_004071d0();
extern unsigned long sk_x_0040723c();
extern unsigned long sk_x_00407248();
extern unsigned long sk_x_004072c0();
extern unsigned long sk_x_00407374();
extern unsigned long sk_x_00407444();
extern cl4_result_t sk_x_00407484();
extern unsigned long sk_x_00407520();
extern unsigned long sk_x_0040752c();
extern unsigned long sk_x_0040755c();
extern unsigned long sk_x_00407588();
extern unsigned long sk_x_00407594();
extern unsigned long sk_x_004075a4();
extern unsigned long sk_x_004075c4();
extern unsigned long sk_x_00407610();
extern unsigned long sk_x_00407824();
extern unsigned long sk_x_004078d4();
extern unsigned long sk_x_004078e8();
extern cl4_result_t sk_x_004078f4();
extern unsigned long sk_x_00407924();
extern unsigned long sk_x_00407954();
extern unsigned long sk_x_004079cc();
extern unsigned long sk_x_00407aa0();
extern unsigned long sk_x_00407ac4();
extern unsigned long sk_x_00407ca0();
extern unsigned long sk_x_00407d74();
extern unsigned long sk_x_00407f48();
extern unsigned long sk_x_00408044();
extern unsigned long sk_x_00408058();
extern unsigned long sk_x_00408094();
extern unsigned long sk_x_004080b0();
extern unsigned long sk_x_00408108();
extern unsigned long sk_x_00408130();
extern unsigned long sk_x_00408148();
extern unsigned long sk_x_004081a8();
extern unsigned long sk_x_004081cc();
extern cl4_result_t sk_x_0040833c();
extern unsigned long sk_x_004083e4();
extern unsigned long sk_x_004084a4();
extern unsigned long sk_x_004085a8();
extern unsigned long sk_x_00408db8();
extern unsigned long sk_x_0040bb18();
extern unsigned long sk_x_0040bd24();
extern unsigned long sk_x_0040c9d0();
extern unsigned long sk_x_0040d068();
extern unsigned long sk_x_0040d07c();
extern unsigned long sk_x_0040d99c();
extern unsigned long sk_x_0040f434();
extern unsigned long sk_x_0040f4c8();
extern unsigned long sk_x_0040f524();
extern unsigned long sk_x_004ba7ec();

/* ------------------------------------------------------------------ *
 * In-slice (internal) functions — forward declarations.
 * ------------------------------------------------------------------ */
static void sk_op_003eefc0(void);
static void sk_op_003ef0ac(void);
static void sk_op_003ef178(void);
static void sk_op_003ef3e8(void);
static void sk_op_003ef544(uint64_t p1, uint64_t p2, uint64_t p3);
static void sk_op_003ef6b0(void);
static void sk_op_003ef754(void);
static void sk_op_003ef848(void);
static void sk_op_003ef924(void);
static void sk_op_003ef9b0(void);
static void sk_op_003efb08(void);
static void sk_op_003efbc4(void);
static void sk_op_003efc1c(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4);
static void sk_op_003efcd0(void);
static void sk_op_003efd60(void);
static void sk_op_003efe7c(void);
static void sk_op_003f0054(void);
static void sk_op_003f0110(void);
static void sk_op_003f01c4(void);
static void sk_op_003f0268(void);
static void sk_op_003f0444(void);
static void sk_op_003f0508(void);
static void sk_op_003f05d4(void);
static void sk_op_003f06c0(uint64_t p1, uint64_t p2);
static void sk_op_003f075c(void);
static void sk_helper_003f08ac(uint64_t *param_1);
static void sk_op_003f08dc(void);
static void sk_op_003f099c(void);
static void sk_op_003f0a5c(void);
static void sk_op_003f0b18(void);
static void sk_op_003f0d70(void);
static void sk_op_003f0e4c(void);
static void sk_op_003f0f34(void);
static void sk_op_003f1158(void);
static void sk_op_003f1310(void);
static void sk_op_003f1454(void);
static void sk_op_003f1534(void);
static void sk_op_003f1744(uint64_t p1, uint64_t p2, uint64_t p3);
static void sk_op_003f1990(void);
static void sk_op_003f1a98(void);
static void sk_op_003f1c40(void);
static void sk_op_003f1cb8(void);
static void sk_op_003f1d58(void);
static void sk_op_003f1de8(void);
static void sk_op_003f1ec4(void);
static void sk_op_003f1f5c(void);
static void sk_op_003f1fec(void);
static void sk_op_003f2270(void);
static void sk_op_003f22f4(void);
static void sk_op_003f244c(void);
static void sk_helper_003f256c(uint64_t p1);
static void sk_helper_003f2570(uint64_t p1);
static void sk_helper_003f25d4(uint64_t p1);
static void sk_op_003f274c(void);
static void sk_op_003f27f8(void);
static void sk_op_003f2918(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4, long p5);
static void sk_op_003f29f0(void);
static void sk_op_003f2bb8(void);
static void sk_op_003f2d58(uint64_t p1, uint64_t p2, int *p3);
static void sk_trace_003f3058(void);
static void sk_helper_003f30b8(uint64_t *param_1);
static void sk_helper_003f3108(uint64_t *param_1, uint32_t param_2);
static void sk_helper_003f310c(uint64_t *param_1, uint32_t param_2);
static cl4_result_t sk_trace_003f312c(void);
static void sk_helper_003f3218(void);
static void sk_helper_003f327c(void);
static void sk_helper_003f3280(void);
static void sk_helper_003f32b4(void);
static void sk_trace_003f32d8(uint64_t p1, uint64_t p2, uint64_t p3);
static void sk_abort_003f33f0(void);
static void sk_abort_003f345c(void);
static void sk_helper_003f34b4(uint8_t p1);
static void sk_abort_003f34fc(void);
static void sk_abort_003f3524(void);
static void sk_abort_003f354c(void);
static void sk_abort_003f3574(void);
static void sk_abort_003f359c(void);
static void sk_abort_003f35a0(void);
static void sk_abort_003f35ac(void);
static void sk_abort_003f35d4(void);
static void sk_abort_003f3610(void);
static void sk_op_003f3650(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4);
static void sk_abort_003f36dc(void);
static void sk_abort_003f371c(void);
static void sk_abort_003f3744(void);
static void sk_abort_003f376c(void);
static void sk_abort_003f3794(void);
static void sk_abort_003f37bc(void);
static void sk_abort_003f37e4(void);
static void sk_abort_003f380c(void);
static void sk_abort_003f3834(void);
static void sk_abort_003f3838(void);
static void sk_abort_003f3844(void);
static void sk_abort_003f386c(void);
static void sk_abort_003f38a8(void);
static void sk_abort_003f38e8(void);
static void sk_abort_003f3910(void);
static void sk_abort_003f3938(void);
static void sk_helper_003f3960(void);
static void sk_helper_003f3a34(void);
static void sk_helper_003f3a38(void);
static cl4_result_t sk_trace_003f3a58(void);
static void sk_helper_003f3b34(void);
static void sk_helper_003f3b58(void);
static void sk_helper_003f3b5c(void);
static cl4_result_t sk_trace_003f3b9c(void);
static long sk_helper_003f3cfc(long param_1, long param_2);
static cl4_result_t sk_trace_003f3d34(void);
static uint32_t sk_helper_003f3db8(void);
static uint32_t sk_helper_003f3dbc(void);
static uint32_t sk_helper_003f3ddc(void);
static uint32_t sk_helper_003f3de0(void);
static void sk_helper_003f3dfc(void);
static void sk_abort_003f3e34(void);
static void sk_op_003f3e64(uint64_t *param_1, uint64_t param_2, long param_3, uint64_t param_4, long param_5, char param_6);
static void sk_op_003f3ecc(void);
static void sk_op_003f3f50(void);
static long sk_helper_003f4040(void);
static void sk_op_003f406c(void);
static void sk_helper_003f4164(long param_1);

/* ------------------------------------------------------------------ *
 * Function bodies.
 * ------------------------------------------------------------------ */

/* FUN_003eefc0 @ 0x003eefc0   (est. sk_op_003eefc0)
 * Ghidra: void FUN_003eefc0(void)
 * Opens the running op context (x22), registers the per-op frame with the
 * context-frame binder (FUN_0040d07c), and tail-dispatches through an
 * unrecovered jumptable (the op's continuation table).
 * Confidence: low
 * Notes: UNRECOVERED_JUMPTABLE at 0x003ef008 ("Too many branches"); unaff_x22
 *   is the current op context; FUN_00407000/FUN_0040678c open helpers,
 *   FUN_0040d07c binds the frame. */
static void sk_op_003eefc0(void)
{
    uint8_t *ctx = /* unaff_x22: current op context */ 0;

    sk_x_00407000();
    sk_x_0040d07c(ctx + 0x10);
    sk_x_0040678c();
    /* UNRECOVERED_JUMPTABLE at 0x003ef008: tail-dispatch into continuation table */
    __builtin_unreachable();
}

/* FUN_003ef0ac @ 0x003ef0ac   (est. sk_op_003ef0ac)
 * Ghidra: void FUN_003ef0ac(void)
 * Opens the op context, releases the current per-op frame, and continues
 * execution at the nested continuation FUN_003ef178 with the frame's two
 * context pointers.
 * Confidence: low
 * Notes: unaff_x20 is the op frame; frame[0x138] and frame[0x140] are the
 *   continuation arguments; the stack-slot constant is masked then ORed with
 *   the 0xc31a… tag (Ghidra artifact of an untagged stack address). */
static void sk_op_003ef0ac(void)
{
    uint64_t extraout_x16 = 0;   /* extraout_x16 */
    uint8_t *x20 = /* unaff_x20: op frame */ 0;
    uint64_t stack_slot = (uint64_t)&x20;

    sk_x_00407000();
    sk_x_00407520();
    sk_x_0040bd24((stack_slot & 0xffffffffffffULL) | 0xc31a000000000000ULL,
                  *(uint64_t *)(x20 + 0x168));
    sk_x_00407444();
    sk_x_00408db8((uint64_t)sk_op_003ef178, *(uint64_t *)(x20 + 0x138),
                  *(uint64_t *)(extraout_x16 + 0x140));
}

/* FUN_003ef178 @ 0x003ef178   (est. sk_op_003ef178)
 * Ghidra: void FUN_003ef178(void)
 * Continuation entry: opens the op context, binds the per-op frame, and
 * tail-dispatches through the unrecovered continuation jumptable.
 * Confidence: low
 * Notes: UNRECOVERED_JUMPTABLE at 0x003ef1d4. */
static void sk_op_003ef178(void)
{
    uint8_t *ctx = /* unaff_x22 */ 0;

    sk_x_00406fd4();
    sk_x_0040d07c(ctx + 0x10);
    sk_x_0036986c();
    sk_x_00407128();
    /* UNRECOVERED_JUMPTABLE at 0x003ef1d4 */
    __builtin_unreachable();
}

/* FUN_003ef3e8 @ 0x003ef3e8   (est. sk_op_003ef3e8)
 * Ghidra: void FUN_003ef3e8(void)
 * Opens the op context, stores a register pair into a frame slot, releases
 * the current frame, re-binds the context frame, and tail-dispatches.
 * Confidence: low
 * Notes: UNRECOVERED_JUMPTABLE at 0x003ef480; extraout_x8/extraout_x9 are the
 *   register pair produced by FUN_0040676c. */
static void sk_op_003ef3e8(void)
{
    uint64_t extraout_x8 = 0;    /* extraout_x8 */
    uint64_t extraout_x8_00 = 0; /* extraout_x8_00 */
    uint64_t *extraout_x9 = 0;   /* extraout_x9 */

    sk_x_00407000();
    sk_x_00407018();
    sk_x_0040676c();
    *extraout_x9 = extraout_x8;
    sk_x_0040bd24(*(uint64_t *)(extraout_x8_00 + 0x138));
    sk_x_0040d07c(extraout_x8 + 0x10);
    sk_x_0040678c();
    /* UNRECOVERED_JUMPTABLE at 0x003ef480 */
    __builtin_unreachable();
}

/* FUN_003ef544 @ 0x003ef544   (est. sk_op_003ef544)
 * Ghidra: void FUN_003ef544(undefined8 param_1, undefined8 param_2, undefined8 param_3)
 * Opens the op context and seeds its 0x38/0x40 fields from the context-open
 * result. Depending on the high half of that result, either runs a fast
 * continuation or the full reply/completion sequence; stores the completion
 * value at 0x48 and the parameter at 0x50, then tail-dispatches.
 * Confidence: low
 * Notes: auVar2 = FUN_00406fd4() is a 16-byte register pair; the 0x38 field is
 *   seeded from pair.lo, 0x40 from unaff_x20 (op frame). */
static void sk_op_003ef544(uint64_t p1, uint64_t p2, uint64_t p3)
{
    (void)p1; (void)p2;
    cl4_result_t pair;
    uint64_t uVar1;
    uint64_t x20 = /* unaff_x20 */ 0;
    uint8_t *ctx = /* unaff_x22 */ 0;

    pair = sk_x_00406fd4();
    *(uint64_t *)(ctx + 0x38) = pair.lo;
    *(uint64_t *)(ctx + 0x40) = x20;
    if (pair.hi == 0) {
        sk_x_00407248();
        uVar1 = /* extraout_x8_01 */ 0;
    } else {
        sk_x_00350b54();
        sk_x_003d4658(p3);
        sk_x_00406734();
        /* (*extraout_x8)(); unrecovered continuation call */
        sk_x_0008e1ec();
        uVar1 = /* extraout_x8_00 */ 0;
    }
    *(uint64_t *)(ctx + 0x48) = uVar1;
    *(uint64_t *)(ctx + 0x50) = p3;
    sk_x_00353080();
    sk_x_00408db8();
}

/* FUN_003ef6b0 @ 0x003ef6b0   (est. sk_op_003ef6b0)
 * Ghidra: void FUN_003ef6b0(void)
 * Opens the op context, resolves a capability/descriptor word (FUN_00408130),
 * allocates a per-op frame, and continues into the common op sequencer
 * FUN_003ef544.
 * Confidence: low
 * Notes: extraout_x16/extraout_x17 are register fragments from the frame
 *   allocator; frame slot 0x50 links the continuation. */
static void sk_op_003ef6b0(void)
{
    uint64_t uVar1;
    uint64_t *frame;
    uint64_t extraout_x8 = 0;    /* extraout_x8 */
    uint64_t extraout_x16 = 0;   /* extraout_x16 */
    uint64_t extraout_x17 = 0;   /* extraout_x17 */
    uint8_t *ctx = /* unaff_x22 */ 0;

    sk_x_00407000();
    uVar1 = sk_x_00408130();
    *(uint64_t *)(ctx + 0x38) = uVar1;
    sk_x_00352018();
    *(uint64_t *)(ctx + 0x40) = extraout_x16;
    uVar1 = sk_x_004078e8(*(uint64_t *)(extraout_x8 + 0x40));
    *(uint64_t *)(ctx + 0x48) = uVar1;
    sk_x_00408094();
    frame = (uint64_t *)sk_x_00406fe0();
    *(uint64_t **)(ctx + 0x50) = frame;
    *frame = extraout_x17;
    sk_x_00406c98();
    sk_op_003ef544(0, 0, 0);
}

/* FUN_003ef754 @ 0x003ef754   (est. sk_op_003ef754)
 * Ghidra: void FUN_003ef754(void)
 * Opens the op context and, based on a field at frame+0x10, either takes the
 * idle path or runs the full completion sequence; then continues at
 * FUN_003ef848.
 * Confidence: low
 * Notes: extraout_x8/extraout_x9 are the register pair from FUN_0040676c;
 *   in_x3 is carried into the continuation dispatch. */
static void sk_op_003ef754(void)
{
    uint64_t uVar1;
    uint64_t in_x3 = /* in_x3 */ 0;
    uint64_t extraout_x8 = 0;    /* extraout_x8 */
    uint64_t extraout_x8_00 = 0; /* extraout_x8_00 */
    uint64_t *extraout_x9 = 0;   /* extraout_x9 */
    long lVar2;

    sk_x_00406fd4();
    sk_x_00407018();
    sk_x_0040676c();
    *extraout_x9 = extraout_x8;
    lVar2 = *(long *)(extraout_x8_00 + 0x10);
    sk_x_0040bd24(*(uint64_t *)(extraout_x8_00 + 0x50));
    if (lVar2 == 0) {
        sk_x_004075c4();
    } else {
        uVar1 = *(uint64_t *)(extraout_x8 + 0x18);
        sk_x_000027e8();
        sk_x_003d4658(uVar1);
        sk_x_0034bcf0();
        /* (*extraout_x8_01)(); unrecovered continuation call */
        sk_x_00407588();
    }
    sk_x_00408db8((uint64_t)sk_op_003ef848, in_x3);
}

/* FUN_003ef848 @ 0x003ef848   (est. sk_op_003ef848)
 * Ghidra: void FUN_003ef848(void)
 * Op completion handler: resolves a status word and, based on the zero flag
 * left by the resolver, either finishes the op (releasing the frame and
 * tail-dispatched) or allocates a new op frame and continues into the
 * sequencer FUN_003ef544.
 * Confidence: low
 * Notes: UNRECOVERED_JUMPTABLE at 0x003ef8b8; in_ZR is the Z flag of
 *   FUN_00350884 (modelled as "status==0"). */
static void sk_op_003ef848(void)
{
    cl4_result_t pair;
    uint64_t uVar1;
    uint64_t *frame;
    uint64_t extraout_x17 = 0;   /* extraout_x17 */
    uint64_t uVar3;
    uint8_t *ctx = /* unaff_x22 */ 0;
    int zflag;

    pair = sk_x_00407000();
    uVar3 = *(uint64_t *)(ctx + 0x48);
    sk_x_00351d24(pair.lo, pair.hi, *(uint64_t *)(ctx + 0x30));
    uVar1 = sk_x_00350884();
    zflag = (int)(uVar1 == 0);   /* in_ZR */
    sk_x_0040711c(*(uint64_t *)(ctx + 0x40), uVar1, *(uint64_t *)(ctx + 0x38));
    if (zflag) {
        /* fast path: release frame and tail-dispatch */
        sk_x_0040bd24(uVar3);
        sk_x_00407128();
        /* UNRECOVERED_JUMPTABLE at 0x003ef8b8 */
        __builtin_unreachable();
    }
    /* completion path: allocate a fresh op frame and continue the sequencer */
    sk_x_00408094();
    frame = (uint64_t *)sk_x_00406fe0();
    *(uint64_t **)(ctx + 0x50) = frame;
    *frame = extraout_x17;
    sk_x_00406c98();
    sk_op_003ef544(0, 0, 0);
}

/* FUN_003ef924 @ 0x003ef924   (est. sk_op_003ef924)
 * Ghidra: void FUN_003ef924(void)
 * Opens the op context, resolves a capability word, allocates a per-op frame,
 * and continues into the sequencer FUN_003efc1c.
 * Confidence: low
 * Notes: mirror of FUN_003ef6b0 but continuing at FUN_003efc1c. */
static void sk_op_003ef924(void)
{
    uint64_t uVar1;
    uint64_t *frame;
    uint64_t extraout_x8 = 0;    /* extraout_x8 */
    uint64_t extraout_x16 = 0;   /* extraout_x16 */
    uint64_t extraout_x17 = 0;   /* extraout_x17 */
    uint8_t *ctx = /* unaff_x22 */ 0;

    sk_x_00407000();
    uVar1 = sk_x_00408130();
    *(uint64_t *)(ctx + 0x38) = uVar1;
    sk_x_00352018();
    *(uint64_t *)(ctx + 0x40) = extraout_x16;
    uVar1 = sk_x_004078e8(*(uint64_t *)(extraout_x8 + 0x40));
    *(uint64_t *)(ctx + 0x48) = uVar1;
    sk_x_004081cc();
    frame = (uint64_t *)sk_x_00406fe0();
    *(uint64_t **)(ctx + 0x50) = frame;
    *frame = extraout_x17;
    sk_x_00406af4();
    sk_op_003efc1c(0, 0, 0, 0);
}

/* FUN_003ef9b0 @ 0x003ef9b0   (est. sk_op_003ef9b0)
 * Ghidra: void FUN_003ef9b0(void)
 * Op dispatch that branches on an incoming frame pointer (unaff_x20): each
 * path runs an open/completion sequence and continues at a different
 * continuation (FUN_003efb08 or FUN_003efbc4).
 * Confidence: low
 * Notes: in_x3 carried into the continuation dispatch; unaff_x21 is the op
 *   frame whose 0x50 slot is released. */
static void sk_op_003ef9b0(void)
{
    uint64_t uVar1;
    uint64_t in_x3 = /* in_x3 */ 0;
    uint64_t *extraout_x8 = 0;   /* extraout_x8 */
    uint64_t extraout_x16 = 0;   /* extraout_x16 */
    uint8_t *x20 = /* unaff_x20 */ 0;
    uint8_t *x21 = /* unaff_x21: op frame */ 0;
    long lVar3;
    uint64_t cont;

    sk_x_00406fd4();
    sk_x_0040723c();
    sk_x_00407024(&x20);
    *extraout_x8 = (uint64_t)x21;
    sk_x_0040bd24(*(uint64_t *)(x21 + 0x50));
    sk_x_00407158();
    lVar3 = *(long *)(extraout_x16 + 0x10);
    if (x20 == 0) {
        if (lVar3 == 0) {
            sk_x_004075c4();
        } else {
            sk_x_00407374(*(uint64_t *)(x21 + 0x18));
            sk_x_003504ac();
            /* (*extraout_x8_01)(); unrecovered continuation call */
            sk_x_00407588();
        }
        cont = (uint64_t)sk_op_003efb08;
    } else {
        sk_x_0036b118();
        if (lVar3 == 0) {
            sk_x_004075c4();
        } else {
            uVar1 = *(uint64_t *)(x21 + 0x18);
            sk_x_000027e8();
            sk_x_00407374(uVar1);
            sk_x_003504ac();
            /* (*extraout_x8_00)(); unrecovered continuation call */
            sk_x_00407588();
        }
        cont = (uint64_t)sk_op_003efbc4;
    }
    sk_x_00408db8(cont, in_x3);
}

/* FUN_003efb08 @ 0x003efb08   (est. sk_op_003efb08)
 * Ghidra: void FUN_003efb08(void)
 * Op completion handler: resolves a status word and either finishes (release
 * frame + tail-dispatch) or allocates a fresh frame and continues the
 * sequencer FUN_003efc1c. Mirror of FUN_003ef848.
 * Confidence: low
 * Notes: UNRECOVERED_JUMPTABLE at 0x003efb78; in_ZR from FUN_00350884. */
static void sk_op_003efb08(void)
{
    cl4_result_t pair;
    uint64_t uVar1;
    uint64_t *frame;
    uint64_t extraout_x17 = 0;   /* extraout_x17 */
    uint64_t uVar3;
    uint8_t *ctx = /* unaff_x22 */ 0;
    int zflag;

    pair = sk_x_00407000();
    uVar3 = *(uint64_t *)(ctx + 0x48);
    sk_x_00351d24(pair.lo, pair.hi, *(uint64_t *)(ctx + 0x30));
    uVar1 = sk_x_00350884();
    zflag = (int)(uVar1 == 0);   /* in_ZR */
    sk_x_0040711c(*(uint64_t *)(ctx + 0x40), uVar1, *(uint64_t *)(ctx + 0x38));
    if (zflag) {
        sk_x_0040bd24(uVar3);
        sk_x_00407128();
        /* UNRECOVERED_JUMPTABLE at 0x003efb78 */
        __builtin_unreachable();
    }
    sk_x_004081cc();
    frame = (uint64_t *)sk_x_00406fe0();
    *(uint64_t **)(ctx + 0x50) = frame;
    *frame = extraout_x17;
    sk_x_00406af4();
    sk_op_003efc1c(0, 0, 0, 0);
}

/* FUN_003efbc4 @ 0x003efbc4   (est. sk_op_003efbc4)
 * Ghidra: void FUN_003efbc4(void)
 * Short op continuation: opens the context, allocates a per-op frame, links it
 * at 0x50, and continues into the sequencer FUN_003efc1c.
 * Confidence: low
 * Notes: extraout_x17 is the frame backlink register fragment. */
static void sk_op_003efbc4(void)
{
    uint64_t *frame;
    uint64_t extraout_x17 = 0;   /* extraout_x17 */
    uint8_t *ctx = /* unaff_x22 */ 0;

    sk_x_00407000();
    sk_x_004081cc();
    frame = (uint64_t *)sk_x_00406fe0();
    *(uint64_t **)(ctx + 0x50) = frame;
    *frame = extraout_x17;
    sk_x_00406af4();
    sk_op_003efc1c(0, 0, 0, 0);
}

/* FUN_003efc1c @ 0x003efc1c   (est. sk_op_003efc1c)
 * Ghidra: void FUN_003efc1c(undefined8, undefined8, undefined8, undefined8)
 * Op sequencer: opens the context, seeds 0x38/0x40, and runs either the idle
 * path or the full completion sequence based on the context-open high half;
 * then continues at an internal label.
 * Confidence: low
 * Notes: param_4 is carried into the continuation dispatch; the continuation
 *   target is the internal label LAB_003efcb4. */
static void sk_op_003efc1c(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4)
{
    (void)p1; (void)p2;
    cl4_result_t pair;
    uint64_t x20 = /* unaff_x20 */ 0;
    uint8_t *ctx = /* unaff_x22 */ 0;

    pair = sk_x_00406fd4();
    *(uint64_t *)(ctx + 0x38) = pair.lo;
    *(uint64_t *)(ctx + 0x40) = x20;
    if (pair.hi == 0) {
        sk_x_004075c4();
    } else {
        sk_x_00350b54();
        sk_x_003d4658(p3);
        sk_x_00406734();
        /* (*extraout_x8)(); unrecovered continuation call */
        sk_x_00407588();
    }
    sk_x_00408db8(0x003efcb4 /* internal continuation label */, p4);
}

/* FUN_003efcd0 @ 0x003efcd0   (est. sk_op_003efcd0)
 * Ghidra: void FUN_003efcd0(void)
 * Opens the op context, allocates a two-word frame, seeds the second word with
 * the reply vtable DAT_00405fec, and hands it to the nested sequencer
 * FUN_003eeb6c along with the context-open value.
 * Confidence: low
 * Notes: extraout_x17 is the frame backlink; the reply vtable is
 *   sk_g_00405fec. */
static void sk_op_003efcd0(void)
{
    uint64_t uVar1;
    uint64_t *frame;
    uint64_t extraout_x17 = 0;   /* extraout_x17 */

    uVar1 = sk_x_00407000().lo;
    sk_x_004081a8();
    frame = (uint64_t *)sk_x_00407ac4();
    *frame = extraout_x17;
    frame[1] = sk_g_00405fec;
    sk_x_003eeb6c(frame + 1, uVar1);
}

/* FUN_003efd60 @ 0x003efd60   (est. sk_op_003efd60)
 * Ghidra: void FUN_003efd60(void)
 * Opens the op context and seeds a run of 0x48..0x80 fields: the context-open
 * pair, a word from the descriptor, two resolved capability words, and two
 * status words; then tail-dispatches.
 * Confidence: low
 * Notes: two FUN_004078e8 resolution sites reading frame+0x40. */
static void sk_op_003efd60(void)
{
    cl4_result_t pair;
    uint64_t uVar1;
    uint64_t extraout_x8 = 0;    /* extraout_x8 */
    uint64_t extraout_x8_00 = 0; /* extraout_x8_00 */
    uint64_t extraout_x16 = 0;   /* extraout_x16 */
    uint64_t extraout_x16_00 = 0;/* extraout_x16_00 */
    uint64_t x20 = /* unaff_x20 */ 0;
    uint8_t *ctx = /* unaff_x22 */ 0;

    pair = sk_x_00407000();
    *(uint64_t *)(ctx + 0x48) = pair.hi;
    *(uint64_t *)(ctx + 0x50) = x20;
    *(uint64_t *)(ctx + 0x40) = pair.lo;
    *(uint64_t *)(ctx + 0x58) = *(uint64_t *)(pair.hi + 0x10);
    sk_x_00350798();
    uVar1 = sk_x_00310d68();
    *(uint64_t *)(ctx + 0x60) = uVar1;
    sk_x_00352018();
    *(uint64_t *)(ctx + 0x68) = extraout_x16;
    uVar1 = sk_x_004078e8(*(uint64_t *)(extraout_x8 + 0x40));
    *(uint64_t *)(ctx + 0x70) = uVar1;
    sk_x_0040683c();
    *(uint64_t *)(ctx + 0x78) = extraout_x16_00;
    uVar1 = sk_x_004078e8(*(uint64_t *)(extraout_x8_00 + 0x40));
    *(uint64_t *)(ctx + 0x80) = uVar1;
    sk_x_00407594();
    sk_x_00408db8();
}

/* FUN_003efe7c @ 0x003efe7c   (est. sk_op_003efe7c)
 * Ghidra: void FUN_003efe7c(void)
 * Op completion dispatcher: resolves a status word via FUN_000839f8 and
 * branches on its low word. The ==1 path runs a capability reply sequence;
 * the other path invokes a vtable method, releases two frames, and
 * tail-dispatches through the unrecovered continuation table.
 * Confidence: low
 * Notes: UNRECOVERED_JUMPTABLE at 0x003eff8c; vtable dispatch via
 *   *(frame+0x78)->0x20; FUN_0040bd24 releases frame 0x70 and 0x80. */
static void sk_op_003efe7c(void)
{
    long lVar1;
    uint64_t uVar2, uVar3, uVar4, uVar5;
    cl4_result_t pair;
    uint8_t *ctx = /* unaff_x22 */ 0;

    uVar2 = sk_x_004079cc();
    sk_x_004070d8();
    uVar4 = *(uint64_t *)(ctx + 0x58);
    uVar3 = sk_x_000839f8(*(uint64_t *)(ctx + 0x70), 1, uVar4);
    uVar5 = *(uint64_t *)(ctx + 0x40);
    lVar1 = *(long *)(ctx + 0x48);
    if ((int)uVar3 == 1) {
        sk_x_00407f48(*(uint64_t *)(ctx + 0x68), uVar3, *(uint64_t *)(ctx + 0x60));
        pair = /* (*extraout_x9)() */ (cl4_result_t){0,0};
        sk_x_003504e8(pair.lo, pair.hi, *(uint64_t *)(lVar1 + 0x18),
                      *(uint64_t *)(lVar1 + 0x20));
        sk_x_0031dc0c();
        sk_x_00350744(uVar5);
    } else {
        uVar3 = *(uint64_t *)(ctx + 0x80);
        {
            uint64_t (*pcVar6)(uint64_t, uint64_t, uint64_t) =
                (uint64_t (*)(uint64_t, uint64_t, uint64_t))(*(uint64_t *)(*(long *)(ctx + 0x78) + 0x20));
            sk_x_003504a0(uVar3);
            pcVar6(0, 0, 0);
            pair = (cl4_result_t){0,0};
            sk_x_003504e8(pair.lo, pair.hi, *(uint64_t *)(lVar1 + 0x18),
                          *(uint64_t *)(lVar1 + 0x20));
            sk_x_0031dc0c();
            pair = sk_x_0007c1c4();
            sk_x_00369340(pair.lo, pair.hi, 0);
            sk_x_00350750(uVar5);
        }
    }
    sk_x_000839d8();
    uVar5 = *(uint64_t *)(ctx + 0x70);
    sk_x_0040bd24(*(uint64_t *)(ctx + 0x80));
    sk_x_0040bd24(uVar5);
    pair = sk_x_0040678c();
    sk_x_004078f4(pair.lo, pair.hi, uVar2);
    /* UNRECOVERED_JUMPTABLE at 0x003eff8c */
    __builtin_unreachable();
}

/* FUN_003f0054 @ 0x003f0054   (est. sk_op_003f0054)
 * Ghidra: void FUN_003f0054(void)
 * Opens the op context and seeds a run of 0x10..0x48 fields (context-open
 * pair, descriptor word, two resolved capability words, two status words),
 * then tail-dispatches. Offset-shifted sibling of FUN_003efd60.
 * Confidence: low
 * Notes: fields seeded at +0x10 instead of +0x48. */
static void sk_op_003f0054(void)
{
    cl4_result_t pair;
    uint64_t uVar1;
    uint64_t extraout_x8 = 0;    /* extraout_x8 */
    uint64_t extraout_x8_00 = 0; /* extraout_x8_00 */
    uint64_t extraout_x16 = 0;   /* extraout_x16 */
    uint64_t extraout_x16_00 = 0;/* extraout_x16_00 */
    uint64_t x20 = /* unaff_x20 */ 0;
    uint8_t *ctx = /* unaff_x22 */ 0;

    pair = sk_x_00407000();
    *(uint64_t *)(ctx + 0x10) = pair.lo;
    *(uint64_t *)(ctx + 0x18) = x20;
    *(uint64_t *)(ctx + 0x20) = *(uint64_t *)(pair.hi + 0x10);
    sk_x_00350798();
    uVar1 = sk_x_00310d68();
    *(uint64_t *)(ctx + 0x28) = uVar1;
    sk_x_00352018();
    *(uint64_t *)(ctx + 0x30) = extraout_x16;
    uVar1 = sk_x_004078e8(*(uint64_t *)(extraout_x8 + 0x40));
    *(uint64_t *)(ctx + 0x38) = uVar1;
    sk_x_0040683c();
    *(uint64_t *)(ctx + 0x40) = extraout_x16_00;
    uVar1 = sk_x_004078e8(*(uint64_t *)(extraout_x8_00 + 0x40));
    *(uint64_t *)(ctx + 0x48) = uVar1;
    sk_x_00407594();
    sk_x_00408db8();
}

/* FUN_003f0110 @ 0x003f0110   (est. sk_op_003f0110)
 * Ghidra: void FUN_003f0110(void)
 * Opens the op context. If the "done" flag (bit 0 of byte at frame+8) is set,
 * releases the frame at 0x38 and tail-dispatches; otherwise allocates a new
 * op frame and continues into the sequencer FUN_003ef544.
 * Confidence: low
 * Notes: UNRECOVERED_JUMPTABLE at 0x003f0174. */
static void sk_op_003f0110(void)
{
    uint64_t *frame;
    uint64_t extraout_x17 = 0;   /* extraout_x17 */
    uint64_t uVar2;
    uint8_t *ctx = /* unaff_x22 */ 0;

    sk_x_00407000();
    if ((*(uint8_t *)(*(long *)(ctx + 0x18) + 8) & 1) != 0) {
        uVar2 = *(uint64_t *)(ctx + 0x38);
        sk_x_0040686c();
        sk_x_0040bd24(uVar2);
        sk_x_00407128();
        /* UNRECOVERED_JUMPTABLE at 0x003f0174 */
        __builtin_unreachable();
    }
    sk_x_00408094();
    frame = (uint64_t *)sk_x_00406fe0();
    *(uint64_t **)(ctx + 0x50) = frame;
    *frame = extraout_x17;
    sk_x_004071d0();
    sk_op_003ef544(0, 0, 0);
}

/* FUN_003f01c4 @ 0x003f01c4   (est. sk_op_003f01c4)
 * Ghidra: void FUN_003f01c4(void)
 * Opens the op context, releases the current per-op frame, and tail-dispatches.
 * Confidence: low
 * Notes: extraout_x8 points at the frame whose 0x50 slot is released. */
static void sk_op_003f01c4(void)
{
    uint64_t extraout_x8 = 0;    /* extraout_x8 */

    sk_x_00407000();
    sk_x_00407018();
    sk_x_0040bd24(*(uint64_t *)(extraout_x8 + 0x50));
    sk_x_00407594();
    sk_x_00408db8();
}

/* FUN_003f0268 @ 0x003f0268   (est. sk_op_003f0268)
 * Ghidra: void FUN_003f0268(void)
 * Op completion handler: resolves a capability word (FUN_00351330 +
 * FUN_00350884). On failure (nonzero status) it runs a notification-handler
 * sequence; on success it marks the "done" flag at frame+8. Either way it
 * releases the frame at 0x38 and tail-dispatches through the continuation
 * table, recording the outcome flag.
 * Confidence: low
 * Notes: UNRECOVERED_JUMPTABLE at 0x003f0340; in_ZR modelled as
 *   (status==0); unaff_x25 is a notification handler function pointer. */
static void sk_op_003f0268(void)
{
    cl4_result_t pair;
    uint64_t uVar1, uVar2, uVar3;
    uint8_t *ctx = /* unaff_x22 */ 0;
    uint64_t x25 = /* unaff_x25: handler fn ptr */ 0;
    int failed;
    long lVar4;

    uVar1 = sk_x_00408058();
    sk_x_0040700c();
    uVar3 = *(uint64_t *)(ctx + 0x20);
    pair = sk_x_00351330();
    uVar2 = sk_x_00350884(pair.lo, pair.hi, uVar3);
    failed = (int)(uVar2 != 0);   /* !in_ZR */
    if (failed) {
        sk_x_00407aa0();
        pair = sk_x_0007c1c4();
        ((void (*)(uint64_t, uint64_t, uint64_t))x25)(pair.lo, pair.hi, uVar3);
        sk_x_003510c4();
        ((void (*)(void))x25)();
    } else {
        lVar4 = *(long *)(ctx + 0x18);
        sk_x_00353c00(*(uint64_t *)(ctx + 0x30), uVar2, *(uint64_t *)(ctx + 0x28));
        /* (*extraout_x9)(); unrecovered continuation call */
        *(uint8_t *)(lVar4 + 8) = 1;   /* mark done */
    }
    uVar2 = *(uint64_t *)(ctx + 0x38);
    sk_x_004075a4(*(uint64_t *)(ctx + 0x10), failed);
    sk_x_0040bd24(uVar2);
    pair = sk_x_00407128();
    sk_x_00408044(pair.lo, pair.hi, uVar1);
    /* UNRECOVERED_JUMPTABLE at 0x003f0340 */
    __builtin_unreachable();
}

/* FUN_003f0444 @ 0x003f0444   (est. sk_op_003f0444)
 * Ghidra: void FUN_003f0444(void)
 * Opens the op context. If the "done" flag at frame+8 is set, releases the
 * frame at 0x48 and tail-dispatches; otherwise allocates a new op frame, links
 * the continuation FUN_003f0508, and continues into the sequencer
 * FUN_003ef544. Offset-shifted sibling of FUN_003f0110.
 * Confidence: low
 * Notes: UNRECOVERED_JUMPTABLE at 0x003f04a8. */
static void sk_op_003f0444(void)
{
    uint64_t *frame;
    uint64_t extraout_x17 = 0;   /* extraout_x17 */
    uint64_t uVar2;
    uint8_t *ctx = /* unaff_x22 */ 0;

    sk_x_00407000();
    if ((*(uint8_t *)(*(long *)(ctx + 0x28) + 8) & 1) != 0) {
        uVar2 = *(uint64_t *)(ctx + 0x48);
        sk_x_0040686c();
        sk_x_0040bd24(uVar2);
        sk_x_00407128();
        /* UNRECOVERED_JUMPTABLE at 0x003f04a8 */
        __builtin_unreachable();
    }
    sk_x_00408094();
    frame = (uint64_t *)sk_x_00406fe0();
    *(uint64_t **)(ctx + 0x70) = frame;
    *frame = extraout_x17;
    frame[1] = (uint64_t)sk_op_003f0508;
    sk_op_003ef544(*(uint64_t *)(ctx + 0x48), *(uint64_t *)(ctx + 0x18),
                   *(uint64_t *)(ctx + 0x20));
}

/* FUN_003f0508 @ 0x003f0508   (est. sk_op_003f0508)
 * Ghidra: void FUN_003f0508(void)
 * Continuation: releases the per-op frame and continues at FUN_003f05d4 with
 * two context pointers from the frame.
 * Confidence: low
 * Notes: unaff_x20 is the op frame; the stack-slot constant is masked/ORed as
 *   in FUN_003ef0ac. */
static void sk_op_003f0508(void)
{
    uint64_t extraout_x16 = 0;   /* extraout_x16 */
    uint8_t *x20 = /* unaff_x20: op frame */ 0;
    uint64_t stack_slot = (uint64_t)&x20;

    sk_x_00407000();
    sk_x_00407520();
    sk_x_0040bd24((stack_slot & 0xffffffffffffULL) | 0xc31a000000000000ULL,
                  *(uint64_t *)(x20 + 0x70));
    sk_x_00407444();
    sk_x_00408db8((uint64_t)sk_op_003f05d4, *(uint64_t *)(x20 + 0x60),
                  *(uint64_t *)(extraout_x16 + 0x68));
}

/* FUN_003f05d4 @ 0x003f05d4   (est. sk_op_003f05d4)
 * Ghidra: void FUN_003f05d4(void)
 * Op completion handler, structurally identical to FUN_003f0268 but reading
 * its fields at +0x28/+0x30/+0x38/+0x40/+0x48. On failure runs the
 * notification-handler sequence; on success marks "done" at frame+8; then
 * releases frame 0x48 and tail-dispatches.
 * Confidence: low
 * Notes: UNRECOVERED_JUMPTABLE at 0x003f06ac; in_ZR = (status==0). */
static void sk_op_003f05d4(void)
{
    cl4_result_t pair;
    uint64_t uVar1, uVar2, uVar3;
    uint8_t *ctx = /* unaff_x22 */ 0;
    uint64_t x25 = /* unaff_x25: handler fn ptr */ 0;
    int failed;
    long lVar4;

    uVar1 = sk_x_00408058();
    sk_x_0040700c();
    uVar3 = *(uint64_t *)(ctx + 0x30);
    pair = sk_x_00351330();
    uVar2 = sk_x_00350884(pair.lo, pair.hi, uVar3);
    failed = (int)(uVar2 != 0);   /* !in_ZR */
    if (failed) {
        sk_x_00407aa0();
        pair = sk_x_0007c1c4();
        ((void (*)(uint64_t, uint64_t, uint64_t))x25)(pair.lo, pair.hi, uVar3);
        sk_x_003510c4();
        ((void (*)(void))x25)();
    } else {
        lVar4 = *(long *)(ctx + 0x28);
        sk_x_00353c00(*(uint64_t *)(ctx + 0x40), uVar2, *(uint64_t *)(ctx + 0x38));
        /* (*extraout_x9)(); unrecovered continuation call */
        *(uint8_t *)(lVar4 + 8) = 1;   /* mark done */
    }
    uVar2 = *(uint64_t *)(ctx + 0x48);
    sk_x_004075a4(*(uint64_t *)(ctx + 0x10), failed);
    sk_x_0040bd24(uVar2);
    pair = sk_x_00407128();
    sk_x_00408044(pair.lo, pair.hi, uVar1);
    /* UNRECOVERED_JUMPTABLE at 0x003f06ac */
    __builtin_unreachable();
}

/* FUN_003f06c0 @ 0x003f06c0   (est. sk_op_003f06c0)
 * Ghidra: void FUN_003f06c0(undefined8, undefined8)
 * Allocates a two-word op frame, seeds the backlink with the current context
 * and the continuation with FUN_003f075c, then continues into the sequencer
 * FUN_003f0054.
 * Confidence: low
 * Notes: size class DAT_005a01dc (sk_g_005a01dc). */
static void sk_op_003f06c0(uint64_t p1, uint64_t p2)
{
    long *frame;
    uint8_t *ctx = /* unaff_x22 */ 0;

    frame = (long *)sk_x_0040bb18(sk_g_005a01dc);
    *(long **)(ctx + 0x10) = frame;
    *frame = (long)ctx;
    frame[1] = (long)sk_op_003f075c;
    sk_op_003f0054();
    (void)p1; (void)p2;
}

/* FUN_003f075c @ 0x003f075c   (est. sk_op_003f075c)
 * Ghidra: void FUN_003f075c(void)
 * Continuation: opens the context, releases the per-op frame, and
 * tail-dispatches through the unrecovered continuation table.
 * Confidence: low
 * Notes: UNRECOVERED_JUMPTABLE at 0x003f07f4. */
static void sk_op_003f075c(void)
{
    uint64_t extraout_x8 = 0;    /* extraout_x8 */

    sk_x_00407000();
    sk_x_00407018();
    sk_x_0040bd24(*(uint64_t *)(extraout_x8 + 0x10));
    sk_x_0040678c();
    /* UNRECOVERED_JUMPTABLE at 0x003f07f4 */
    __builtin_unreachable();
}

/* FUN_003f08ac @ 0x003f08ac   (est. sk_helper_003f08ac)
 * Ghidra: void FUN_003f08ac(undefined8 *param_1)
 * Resolves a capability word from the object at unaff_x20 (via the thunk of
 * FUN_000e46d0) and stores it into param_1[0] with a zero status byte.
 * Confidence: low
 * Notes: thunk_FUN_000e46d0 reads the object at *unaff_x20. */
static void sk_helper_003f08ac(uint64_t *param_1)
{
    uint64_t uVar1;
    uint64_t *x20 = /* unaff_x20 */ 0;

    uVar1 = sk_x_000e46d0(*x20);
    param_1[0] = uVar1;
    *(uint8_t *)(param_1 + 1) = 0;
}

/* FUN_003f08dc @ 0x003f08dc   (est. sk_op_003f08dc)
 * Ghidra: void FUN_003f08dc(void)
 * Opens the op context and seeds the 0x10..0x50 field run (mirror of
 * FUN_003f0054 with the resolved words at +0x40/+0x50), then tail-dispatches.
 * Confidence: low */
static void sk_op_003f08dc(void)
{
    cl4_result_t pair;
    uint64_t uVar1;
    uint64_t extraout_x8 = 0;    /* extraout_x8 */
    uint64_t extraout_x8_00 = 0; /* extraout_x8_00 */
    uint64_t extraout_x16 = 0;   /* extraout_x16 */
    uint64_t extraout_x16_00 = 0;/* extraout_x16_00 */
    uint64_t x20 = /* unaff_x20 */ 0;
    uint8_t *ctx = /* unaff_x22 */ 0;

    pair = sk_x_00407000();
    *(uint64_t *)(ctx + 0x18) = pair.hi;
    *(uint64_t *)(ctx + 0x20) = x20;
    *(uint64_t *)(ctx + 0x10) = pair.lo;
    *(uint64_t *)(ctx + 0x28) = *(uint64_t *)(pair.hi + 0x10);
    sk_x_00350798();
    uVar1 = sk_x_00310d68();
    *(uint64_t *)(ctx + 0x30) = uVar1;
    sk_x_00352018();
    *(uint64_t *)(ctx + 0x38) = extraout_x16;
    uVar1 = sk_x_004078e8(*(uint64_t *)(extraout_x8 + 0x40));
    *(uint64_t *)(ctx + 0x40) = uVar1;
    sk_x_0040683c();
    *(uint64_t *)(ctx + 0x48) = extraout_x16_00;
    uVar1 = sk_x_004078e8(*(uint64_t *)(extraout_x8_00 + 0x40));
    *(uint64_t *)(ctx + 0x50) = uVar1;
    sk_x_00407594();
    sk_x_00408db8();
}

/* FUN_003f099c @ 0x003f099c   (est. sk_op_003f099c)
 * Ghidra: void FUN_003f099c(void)
 * Opens the op context. If the "done" flag at frame+8 is set, runs a cleanup
 * sequence and tail-dispatches; otherwise allocates a new op frame, links the
 * continuation FUN_003f0a5c, runs the resolver FUN_00353498, and continues
 * into the sequencer FUN_003efc1c.
 * Confidence: low
 * Notes: UNRECOVERED_JUMPTABLE at 0x003f09fc. */
static void sk_op_003f099c(void)
{
    uint64_t *frame;
    uint64_t extraout_x17 = 0;   /* extraout_x17 */
    uint8_t *ctx = /* unaff_x22 */ 0;

    sk_x_00407000();
    if ((*(uint8_t *)(*(long *)(ctx + 0x20) + 8) & 1) != 0) {
        sk_x_00407954();
        sk_x_0040686c();
        sk_x_0040bd24();
        sk_x_0040678c();
        /* UNRECOVERED_JUMPTABLE at 0x003f09fc */
        __builtin_unreachable();
    }
    sk_x_004081cc();
    frame = (uint64_t *)sk_x_00406fe0();
    *(uint64_t **)(ctx + 0x58) = frame;
    *frame = extraout_x17;
    frame[1] = (uint64_t)sk_op_003f0a5c;
    sk_x_00353498(*(uint64_t *)(ctx + 0x40));
    sk_op_003efc1c(0, 0, 0, 0);
}

/* FUN_003f0a5c @ 0x003f0a5c   (est. sk_op_003f0a5c)
 * Ghidra: void FUN_003f0a5c(void)
 * Continuation: stores the incoming frame pointer at frame+0x60, releases the
 * per-op frame, and continues at FUN_003f0b18 (or an internal label) through
 * the resolver FUN_00353498.
 * Confidence: low
 * Notes: LAB_003f0bf4 is the non-null continuation; unaff_x20 selects the
 *   branch. */
static void sk_op_003f0a5c(void)
{
    uint64_t uVar1;
    uint64_t extraout_x8 = 0;    /* extraout_x8 */
    uint64_t extraout_x9 = 0;    /* extraout_x9 */
    uint64_t *extraout_x10 = 0;  /* extraout_x10 */
    uint8_t *x20 = /* unaff_x20 */ 0;
    uint64_t cont;

    sk_x_00407000();
    sk_x_00407018();
    sk_x_0040691c();
    *extraout_x10 = extraout_x9;
    uVar1 = *(uint64_t *)(extraout_x8 + 0x58);
    *(uint64_t *)(extraout_x9 + 0x60) = (uint64_t)x20;
    sk_x_0040bd24(uVar1);
    if (x20 == 0) {
        cont = (uint64_t)sk_op_003f0b18;
    } else {
        cont = 0x003f0bf4;   /* internal continuation label */
    }
    sk_x_00353498(cont);
    sk_x_00408db8();
}

/* FUN_003f0b18 @ 0x003f0b18   (est. sk_op_003f0b18)
 * Ghidra: void FUN_003f0b18(void)
 * Op completion handler, structurally identical to FUN_003f0268 but reading
 * fields at +0x20/+0x28/+0x30/+0x38/+0x40; uses the FUN_0040678c close path.
 * Confidence: low
 * Notes: UNRECOVERED_JUMPTABLE at 0x003f0bf0. */
static void sk_op_003f0b18(void)
{
    cl4_result_t pair;
    uint64_t uVar1, uVar2, uVar3;
    uint8_t *ctx = /* unaff_x22 */ 0;
    uint64_t x25 = /* unaff_x25: handler fn ptr */ 0;
    int failed;
    long lVar4;

    uVar1 = sk_x_00408058();
    sk_x_0040700c();
    uVar3 = *(uint64_t *)(ctx + 0x28);
    pair = sk_x_00351330();
    uVar2 = sk_x_00350884(pair.lo, pair.hi, uVar3);
    failed = (int)(uVar2 != 0);   /* !in_ZR */
    if (failed) {
        sk_x_00407aa0();
        pair = sk_x_0007c1c4();
        ((void (*)(uint64_t, uint64_t, uint64_t))x25)(pair.lo, pair.hi, uVar3);
        sk_x_003510c4();
        ((void (*)(void))x25)();
    } else {
        lVar4 = *(long *)(ctx + 0x20);
        sk_x_00353c00(*(uint64_t *)(ctx + 0x38), uVar2, *(uint64_t *)(ctx + 0x30));
        /* (*extraout_x9)(); unrecovered continuation call */
        *(uint8_t *)(lVar4 + 8) = 1;   /* mark done */
    }
    uVar2 = *(uint64_t *)(ctx + 0x40);
    sk_x_004075a4(*(uint64_t *)(ctx + 0x10), failed);
    sk_x_0040bd24(uVar2);
    pair = sk_x_0040678c();
    sk_x_00408044(pair.lo, pair.hi, uVar1);
    /* UNRECOVERED_JUMPTABLE at 0x003f0bf0 */
    __builtin_unreachable();
}

/* FUN_003f0d70 @ 0x003f0d70   (est. sk_op_003f0d70)
 * Ghidra: void FUN_003f0d70(void)
 * Opens the op context. If the "done" flag at frame+8 is set, releases the
 * frame at 0x60 and tail-dispatches; otherwise allocates a new op frame,
 * copies two words from the descriptor into it, links the continuation
 * FUN_003f0e4c, and continues into the sequencer FUN_003efc1c.
 * Confidence: low
 * Notes: UNRECOVERED_JUMPTABLE at 0x003f0dd8. */
static void sk_op_003f0d70(void)
{
    uint64_t *frame;
    uint64_t extraout_x17 = 0;   /* extraout_x17 */
    uint64_t uVar2;
    long lVar3;
    uint8_t *ctx = /* unaff_x22 */ 0;

    sk_x_00407000();
    if ((*(uint8_t *)(*(long *)(ctx + 0x38) + 8) & 1) != 0) {
        uVar2 = *(uint64_t *)(ctx + 0x60);
        sk_x_00406c5c(*(uint64_t *)(ctx + 0x18));
        sk_x_0040bd24(uVar2);
        sk_x_0040678c();
        /* UNRECOVERED_JUMPTABLE at 0x003f0dd8 */
        __builtin_unreachable();
    }
    lVar3 = *(long *)(ctx + 0x30);
    sk_x_004081cc();
    frame = (uint64_t *)sk_x_00406fe0();
    *(uint64_t **)(ctx + 0x88) = frame;
    *(uint64_t *)(ctx + 0x90) = *(uint64_t *)(lVar3 + 0x18);
    *(uint64_t *)(ctx + 0x98) = *(uint64_t *)(lVar3 + 0x20);
    *frame = extraout_x17;
    frame[1] = (uint64_t)sk_op_003f0e4c;
    sk_op_003efc1c(*(uint64_t *)(ctx + 0x60), *(uint64_t *)(ctx + 0x20),
                   *(uint64_t *)(ctx + 0x28), /* param_4 (register-forwarded) */ 0);
}

/* FUN_003f0e4c @ 0x003f0e4c   (est. sk_op_003f0e4c)
 * Ghidra: void FUN_003f0e4c(void)
 * Continuation: stores the incoming frame pointer at frame+0xa0, releases the
 * per-op frame, and continues at FUN_003f0f34 (or an internal label) with two
 * context pointers from the frame.
 * Confidence: low
 * Notes: LAB_003f1014 is the non-null continuation; unaff_x21 is the op frame. */
static void sk_op_003f0e4c(void)
{
    uint64_t uVar1;
    uint64_t extraout_x8 = 0;    /* extraout_x8 */
    uint64_t *extraout_x9 = 0;   /* extraout_x9 */
    uint64_t extraout_x16 = 0;   /* extraout_x16 */
    uint8_t *x20 = /* unaff_x20 */ 0;
    uint8_t *x21 = /* unaff_x21: op frame */ 0;
    uint64_t cont;

    sk_x_00406fd4();
    sk_x_0040723c();
    sk_x_0040676c();
    *extraout_x9 = extraout_x8;
    uVar1 = *(uint64_t *)(x21 + 0x88);
    *(uint64_t *)(extraout_x8 + 0xa0) = (uint64_t)x20;
    sk_x_0040bd24(uVar1);
    sk_x_00407158();
    if (x20 == 0) {
        cont = (uint64_t)sk_op_003f0f34;
    } else {
        cont = 0x003f1014;   /* internal continuation label */
    }
    sk_x_00408db8(cont, *(uint64_t *)(x21 + 0x78), *(uint64_t *)(extraout_x16 + 0x80));
}

/* FUN_003f0f34 @ 0x003f0f34   (est. sk_op_003f0f34)
 * Ghidra: void FUN_003f0f34(void)
 * Op completion handler, structurally identical to FUN_003f0b18 but reading
 * fields at +0x38..+0x60 and dispatching the failure path through a vtable
 * method at frame+0x68 -> +0x20. On success marks "done" at frame+8; then
 * releases frame 0x60 and tail-dispatches.
 * Confidence: low
 * Notes: UNRECOVERED_JUMPTABLE at 0x003f1010. */
static void sk_op_003f0f34(void)
{
    cl4_result_t pair;
    uint64_t uVar1, uVar2, uVar3;
    uint8_t *ctx = /* unaff_x22 */ 0;
    int failed;
    long lVar4;

    uVar1 = sk_x_00408058();
    sk_x_0040700c();
    uVar3 = *(uint64_t *)(ctx + 0x48);
    pair = sk_x_00351330();
    uVar2 = sk_x_00350884(pair.lo, pair.hi, uVar3);
    failed = (int)(uVar2 != 0);   /* !in_ZR */
    if (failed) {
        uint64_t (*pcVar5)(uint64_t, uint64_t, uint64_t) =
            (uint64_t (*)(uint64_t, uint64_t, uint64_t))(*(uint64_t *)(*(long *)(ctx + 0x68) + 0x20));
        pair = sk_x_0007c1c4();
        pcVar5(pair.lo, pair.hi, uVar3);
        sk_x_003510c4(*(uint64_t *)(ctx + 0x18));
        pcVar5(0, 0, 0);
    } else {
        lVar4 = *(long *)(ctx + 0x38);
        sk_x_00353c00(*(uint64_t *)(ctx + 0x58), uVar2, *(uint64_t *)(ctx + 0x50));
        /* (*extraout_x9)(); unrecovered continuation call */
        *(uint8_t *)(lVar4 + 8) = 1;   /* mark done */
    }
    uVar2 = *(uint64_t *)(ctx + 0x60);
    sk_x_004075a4(*(uint64_t *)(ctx + 0x18), failed);
    sk_x_0040bd24(uVar2);
    pair = sk_x_0040678c();
    sk_x_00408044(pair.lo, pair.hi, uVar1);
    /* UNRECOVERED_JUMPTABLE at 0x003f1010 */
    __builtin_unreachable();
}

/* FUN_003f1158 @ 0x003f1158   (est. sk_op_003f1158)
 * Ghidra: void FUN_003f1158(void)
 * Opens the op context, reads the continuation vtable from the context,
 * releases a per-op frame, and jumps through the vtable method at vtable+8.
 * Confidence: low
 * Notes: UNRECOVERED_JUMPTABLE at 0x003f1208; unaff_x22 points at the context
 *   whose first word is the vtable pointer. */
static void sk_op_003f1158(void)
{
    uint64_t extraout_x8 = 0;    /* extraout_x8 */
    uint8_t *ctx = /* unaff_x22 */ 0;
    uint64_t vtable;

    sk_x_00406fd4();
    sk_x_00407018();
    vtable = *(uint64_t *)ctx;
    sk_x_00407158(*(uint64_t *)(extraout_x8 + 0x10));
    sk_x_0040bd24();
    /* (**(code **)(vtable + 8))(); unrecovered jumptable at 0x003f1208 */
    ((void (*)(void))(*(uint64_t *)(vtable + 8)))();
}

/* FUN_003f1310 @ 0x003f1310   (est. sk_op_003f1310)
 * Ghidra: void FUN_003f1310(void)
 * Opens the op context. If the incoming frame pointer is null, releases both
 * per-op frames and tail-dispatches; otherwise invokes a vtable method at
 * frame+0x20 -> +0x20 with three frame words, releases the frame, and
 * tail-dispatches through the alternate continuation.
 * Confidence: low
 * Notes: UNRECOVERED_JUMPTABLE at 0x003f13d8; unaff_x20 selects the branch. */
static void sk_op_003f1310(void)
{
    uint64_t uVar1;
    uint64_t extraout_x8 = 0;    /* extraout_x8 */
    uint64_t extraout_x8_00 = 0; /* extraout_x8_00 */
    uint64_t *extraout_x9 = 0;   /* extraout_x9 */
    uint8_t *x20 = /* unaff_x20 */ 0;

    sk_x_00407000();
    sk_x_00407018();
    sk_x_0040676c();
    *extraout_x9 = extraout_x8;
    sk_x_0040bd24(*(uint64_t *)(extraout_x8_00 + 0x30));
    if (x20 == 0) {
        sk_x_0040bd24(*(uint64_t *)(extraout_x8 + 0x28));
        sk_x_00407128();
        /* UNRECOVERED_JUMPTABLE (extraout_x1_00) */
        __builtin_unreachable();
    }
    uVar1 = *(uint64_t *)(extraout_x8 + 0x28);
    ((void (*)(uint64_t, uint64_t, uint64_t))(*(uint64_t *)(*(long *)(extraout_x8 + 0x20) + 0x20)))
        (*(uint64_t *)(extraout_x8 + 0x10), uVar1, *(uint64_t *)(extraout_x8 + 0x18));
    sk_x_0040bd24(uVar1);
    sk_x_00406a94();
    /* UNRECOVERED_JUMPTABLE (extraout_x1) */
    __builtin_unreachable();
}

/* FUN_003f1454 @ 0x003f1454   (est. sk_op_003f1454)
 * Ghidra: void FUN_003f1454(void)
 * Pure continuation stub: closes the op context and tail-dispatches through
 * the unrecovered continuation table.
 * Confidence: low
 * Notes: UNRECOVERED_JUMPTABLE at 0x003f1470. */
static void sk_op_003f1454(void)
{
    sk_x_0040678c();
    /* UNRECOVERED_JUMPTABLE at 0x003f1470 */
    __builtin_unreachable();
}

/* FUN_003f1534 @ 0x003f1534   (est. sk_op_003f1534)
 * Ghidra: void FUN_003f1534(void)
 * Opens the op context, sets up a frame-binder descriptor at ctx+0x10,
 * allocates a per-op frame, links the continuation LAB_003f15f4, and
 * tail-dispatches with two context pointers.
 * Confidence: low
 * Notes: UNRECOVERED_JUMPTABLE at 0x003f15f0; unaff_x22 is the context whose
 *   0x148 word carries the frame length. */
static void sk_op_003f1534(void)
{
    uint64_t uVar1;
    uint64_t *frame;
    uint64_t extraout_x17 = 0;   /* extraout_x17 */
    long lVar3;
    uint8_t *ctx = /* unaff_x22 */ 0;

    sk_x_00406fd4();
    lVar3 = *(long *)(ctx + 0x148);
    sk_x_00359024();
    uVar1 = sk_x_004083e4();
    sk_x_0040d068(uVar1, ctx + 0x10);
    *(uint64_t *)(ctx + 0x138) = (uint64_t)(ctx + 0x10);
    sk_x_00406394();
    sk_x_0040bb18(*(uint32_t *)(lVar3 + 4));
    frame = (uint64_t *)sk_x_00406fe0();
    *(uint64_t **)(ctx + 0x168) = frame;
    *frame = extraout_x17;
    frame[1] = 0x003f15f4;   /* internal continuation label */
    /* UNRECOVERED_JUMPTABLE at 0x003f15f0 */
    __builtin_unreachable();
}

/* FUN_003f1744 @ 0x003f1744   (est. sk_op_003f1744)
 * Ghidra: void FUN_003f1744(undefined8, undefined8, code *param_3)
 * Continuation that takes a vtable/code pointer (param_3): sets up a frame
 * binder descriptor, allocates a per-op frame, links the continuation
 * LAB_003f1808, and tail-dispatches through the unrecovered table after a
 * context re-register.
 * Confidence: low
 * Notes: UNRECOVERED_JUMPTABLE at 0x003f1804; param_3's second word holds the
 *   frame length. */
static void sk_op_003f1744(uint64_t p1, uint64_t p2, uint64_t p3)
{
    (void)p1; (void)p2;
    uint64_t uVar1, uVar2;
    uint64_t *frame;
    uint64_t extraout_x17 = 0;   /* extraout_x17 */
    uint8_t *ctx = /* unaff_x22 */ 0;

    sk_x_00407ca0();
    uVar1 = sk_x_0040700c();
    sk_x_00359024();
    uVar2 = sk_x_004083e4();
    sk_x_0040d068(uVar2, ctx + 0x10);
    *(uint64_t *)(ctx + 0x138) = (uint64_t)(ctx + 0x10);
    sk_x_00406394();
    sk_x_0040bb18(*(uint32_t *)(p3 + 4));
    frame = (uint64_t *)sk_x_00406fe0();
    *(uint64_t **)(ctx + 0x140) = frame;
    *frame = extraout_x17;
    frame[1] = 0x003f1808;   /* internal continuation label */
    sk_x_00407824(uVar1, ctx + 0x138);
    /* UNRECOVERED_JUMPTABLE at 0x003f1804 */
    __builtin_unreachable();
}

/* FUN_003f1990 @ 0x003f1990   (est. sk_op_003f1990)
 * Ghidra: void FUN_003f1990(void)
 * Pure continuation stub: closes the op context and tail-dispatches through
 * the unrecovered continuation table.
 * Confidence: low
 * Notes: UNRECOVERED_JUMPTABLE at 0x003f19b0. */
static void sk_op_003f1990(void)
{
    sk_x_00407128();
    /* UNRECOVERED_JUMPTABLE at 0x003f19b0 */
    __builtin_unreachable();
}

/* FUN_003f1a98 @ 0x003f1a98   (est. sk_op_003f1a98)
 * Ghidra: void FUN_003f1a98(void)
 * Opens the op context, sets up a frame-binder descriptor at ctx+0x10,
 * allocates a per-op frame, links the continuation LAB_003f1b58, and
 * tail-dispatches with the context pointer pair. Sibling of FUN_003f1534 at a
 * different context offset (0x170 / 0x1b0).
 * Confidence: low
 * Notes: UNRECOVERED_JUMPTABLE at 0x003f1b54. */
static void sk_op_003f1a98(void)
{
    uint64_t uVar1;
    uint64_t *frame;
    uint64_t extraout_x17 = 0;   /* extraout_x17 */
    long lVar3;
    uint8_t *ctx = /* unaff_x22 */ 0;

    sk_x_00406fd4();
    lVar3 = *(long *)(ctx + 0x170);
    sk_x_00359024();
    uVar1 = sk_x_004083e4();
    sk_x_0040d068(uVar1, ctx + 0x10);
    *(uint64_t *)(ctx + 0x138) = (uint64_t)(ctx + 0x10);
    sk_x_00406394();
    sk_x_0040bb18(*(uint32_t *)(lVar3 + 4));
    frame = (uint64_t *)sk_x_00406fe0();
    *(uint64_t **)(ctx + 0x1b0) = frame;
    *frame = extraout_x17;
    frame[1] = 0x003f1b58;   /* internal continuation label */
    /* UNRECOVERED_JUMPTABLE at 0x003f1b54 */
    __builtin_unreachable();
}

/* FUN_003f1c40 @ 0x003f1c40   (est. sk_op_003f1c40)
 * Ghidra: void FUN_003f1c40(void)
 * Opens the op context, invokes a four-word helper (FUN_00406894) with four
 * context fields, stores the produced code/value pair at ctx+0x1c0, calls the
 * produced code, and registers a continuation (FUN_003f1cb8) with the frame
 * binder FUN_0040d99c.
 * Confidence: low
 * Notes: FUN_0040d99c(ctx+0x1e1, ctx+0x138, 0, FUN_003f1cb8, ctx+0x140). */
static void sk_op_003f1c40(void)
{
    uint64_t extraout_x9 = 0;    /* extraout_x9 */
    uint64_t extraout_x10 = 0;   /* extraout_x10 */
    uint8_t *ctx = /* unaff_x22 */ 0;

    sk_x_00407000();
    sk_x_00406894(*(uint64_t *)(ctx + 0x188), *(uint64_t *)(ctx + 0x198),
                  *(uint64_t *)(ctx + 400), *(uint64_t *)(ctx + 0x180));
    *(uint64_t *)(ctx + 0x1c0) = extraout_x9;
    *(uint64_t *)(ctx + 0x1c8) = extraout_x10;
    ((void (*)(void))extraout_x9)();
    sk_x_0040d99c(ctx + 0x1e1, *(uint64_t *)(ctx + 0x138), 0,
                  (uint64_t)sk_op_003f1cb8, ctx + 0x140);
}

/* FUN_003f1cb8 @ 0x003f1cb8   (est. sk_op_003f1cb8)
 * Ghidra: void FUN_003f1cb8(void)
 * Continuation: stores the incoming frame pointer at ctx+0x1d0. If non-null it
 * invokes a vtable method at frame+0x188 -> +8, then continues through the
 * resolver FUN_00353498 at an internal label and tail-dispatches.
 * Confidence: low
 * Notes: LAB_003f1d3c (null) / LAB_003f1dcc (non-null); unaff_x20 is the
 *   incoming frame pointer. */
static void sk_op_003f1cb8(void)
{
    uint8_t *x20 = /* unaff_x20 */ 0;
    uint8_t *ctx = /* unaff_x22 */ 0;
    uint64_t cont;

    sk_x_00407000();
    *(uint64_t *)(ctx + 0x1d0) = (uint64_t)x20;
    if (x20 == 0) {
        cont = 0x003f1d3c;   /* internal continuation label */
    } else {
        ((void (*)(uint64_t, uint64_t))(*(uint64_t *)(*(long *)(ctx + 0x188) + 8)))
            (*(uint64_t *)(ctx + 0x198), *(uint64_t *)(ctx + 0x180));
        cont = 0x003f1dcc;   /* internal continuation label */
    }
    sk_x_00353498(cont);
    sk_x_00408db8();
}

/* FUN_003f1d58 @ 0x003f1d58   (est. sk_op_003f1d58)
 * Ghidra: void FUN_003f1d58(void)
 * Continuation: invokes a vtable method at ctx+0x1c0 with four context words,
 * unbinds the frame, releases two per-op frames, and tail-dispatches.
 * Confidence: low
 * Notes: UNRECOVERED_JUMPTABLE at 0x003f1dc8. */
static void sk_op_003f1d58(void)
{
    uint64_t uVar1, uVar2;
    uint8_t *ctx = /* unaff_x22 */ 0;

    sk_x_00407000();
    uVar1 = *(uint64_t *)(ctx + 400);
    uVar2 = *(uint64_t *)(ctx + 0x198);
    ((void (*)(uint64_t, uint64_t, uint64_t, uint64_t))*(uint64_t *)(ctx + 0x1c0))
        (*(uint64_t *)(ctx + 0x1c8), *(uint64_t *)(ctx + 0x168), uVar2,
         *(uint64_t *)(ctx + 0x180));
    sk_x_0040d07c(ctx + 0x10);
    sk_x_0040bd24(uVar2);
    sk_x_0040bd24(uVar1);
    sk_x_0040678c();
    /* UNRECOVERED_JUMPTABLE at 0x003f1dc8 */
    __builtin_unreachable();
}

/* FUN_003f1de8 @ 0x003f1de8   (est. sk_op_003f1de8)
 * Ghidra: void FUN_003f1de8(void)
 * Continuation: unbinds the frame, releases two per-op frames, and
 * tail-dispatches through the close path.
 * Confidence: low
 * Notes: UNRECOVERED_JUMPTABLE at 0x003f1e50. */
static void sk_op_003f1de8(void)
{
    uint64_t uVar1, uVar2;
    uint8_t *ctx = /* unaff_x22 */ 0;

    sk_x_00406fd4();
    uVar1 = *(uint64_t *)(ctx + 400);
    uVar2 = *(uint64_t *)(ctx + 0x198);
    sk_x_0040d07c(ctx + 0x10);
    sk_x_0040bd24(uVar2);
    sk_x_0040bd24(uVar1);
    sk_x_00407128();
    /* UNRECOVERED_JUMPTABLE at 0x003f1e50 */
    __builtin_unreachable();
}

/* FUN_003f1ec4 @ 0x003f1ec4   (est. sk_op_003f1ec4)
 * Ghidra: void FUN_003f1ec4(void)
 * Continuation: stores the incoming frame pointer at ctx+0x1d8, runs a
 * helper (FUN_0036b118) on a context word, and continues through the resolver
 * FUN_00353498 at an internal label.
 * Confidence: low
 * Notes: LAB_003f1f40 (null) / LAB_003f1fd0 (non-null); unaff_x20 selects. */
static void sk_op_003f1ec4(void)
{
    uint8_t *x20 = /* unaff_x20 */ 0;
    uint8_t *ctx = /* unaff_x22 */ 0;
    uint64_t cont;

    sk_x_00407000();
    *(uint64_t *)(ctx + 0x1d8) = (uint64_t)x20;
    sk_x_0036b118(*(uint64_t *)(ctx + 0x1b8));
    if (x20 == 0) {
        cont = 0x003f1f40;   /* internal continuation label */
    } else {
        sk_x_0036b118(*(uint64_t *)(ctx + 0x1b8));
        cont = 0x003f1fd0;   /* internal continuation label */
    }
    sk_x_00353498(cont);
    sk_x_00408db8();
}

/* FUN_003f1f5c @ 0x003f1f5c   (est. sk_op_003f1f5c)
 * Ghidra: void FUN_003f1f5c(void)
 * Continuation: opens the op context, unbinds the frame, releases two per-op
 * frames, and tail-dispatches. Sibling of FUN_003f1de8 with an extra
 * FUN_0036986c open call.
 * Confidence: low
 * Notes: UNRECOVERED_JUMPTABLE at 0x003f1fcc. */
static void sk_op_003f1f5c(void)
{
    uint64_t uVar1, uVar2;
    uint8_t *ctx = /* unaff_x22 */ 0;

    sk_x_00406fd4();
    sk_x_0036986c();
    uVar1 = *(uint64_t *)(ctx + 400);
    uVar2 = *(uint64_t *)(ctx + 0x198);
    sk_x_0040d07c(ctx + 0x10);
    sk_x_0040bd24(uVar2);
    sk_x_0040bd24(uVar1);
    sk_x_00407128();
    /* UNRECOVERED_JUMPTABLE at 0x003f1fcc */
    __builtin_unreachable();
}

/* FUN_003f1fec @ 0x003f1fec   (est. sk_op_003f1fec)
 * Ghidra: void FUN_003f1fec(void)
 * Continuation: opens the op context, unbinds the frame, releases two per-op
 * frames, and tail-dispatches. Mirror of FUN_003f1de8.
 * Confidence: low
 * Notes: UNRECOVERED_JUMPTABLE at 0x003f2054. */
static void sk_op_003f1fec(void)
{
    uint64_t uVar1, uVar2;
    uint8_t *ctx = /* unaff_x22 */ 0;

    sk_x_00406fd4();
    uVar1 = *(uint64_t *)(ctx + 400);
    uVar2 = *(uint64_t *)(ctx + 0x198);
    sk_x_0040d07c(ctx + 0x10);
    sk_x_0040bd24(uVar2);
    sk_x_0040bd24(uVar1);
    sk_x_00407128();
    /* UNRECOVERED_JUMPTABLE at 0x003f2054 */
    __builtin_unreachable();
}

/* FUN_003f2270 @ 0x003f2270   (est. sk_op_003f2270)
 * Ghidra: void FUN_003f2270(void)
 * Continuation: stores the incoming frame pointer at ctx+0x1b0. If non-null it
 * invokes a vtable method at frame+0x178 -> +8; then continues through the
 * resolver FUN_00353498 at FUN_003f22f4 (or an internal label).
 * Confidence: low
 * Notes: LAB_003f2364 is the non-null continuation; unaff_x20 selects. */
static void sk_op_003f2270(void)
{
    uint8_t *x20 = /* unaff_x20 */ 0;
    uint8_t *ctx = /* unaff_x22 */ 0;
    uint64_t cont;

    sk_x_00407000();
    *(uint64_t *)(ctx + 0x1b0) = (uint64_t)x20;
    if (x20 == 0) {
        cont = (uint64_t)sk_op_003f22f4;
    } else {
        ((void (*)(uint64_t, uint64_t))(*(uint64_t *)(*(long *)(ctx + 0x178) + 8)))
            (*(uint64_t *)(ctx + 0x188), *(uint64_t *)(ctx + 0x170));
        cont = 0x003f2364;   /* internal continuation label */
    }
    sk_x_00353498(cont);
    sk_x_00408db8();
}

/* FUN_003f22f4 @ 0x003f22f4   (est. sk_op_003f22f4)
 * Ghidra: void FUN_003f22f4(void)
 * Continuation: invokes a vtable method at ctx+0x1a0 with four context words,
 * unbinds the frame, releases two per-op frames, and tail-dispatches.
 * Confidence: low
 * Notes: UNRECOVERED_JUMPTABLE at 0x003f2360. */
static void sk_op_003f22f4(void)
{
    uint64_t uVar1, uVar2;
    uint8_t *ctx = /* unaff_x22 */ 0;

    sk_x_00407000();
    uVar1 = *(uint64_t *)(ctx + 0x180);
    uVar2 = *(uint64_t *)(ctx + 0x188);
    ((void (*)(uint64_t, uint64_t, uint64_t, uint64_t))*(uint64_t *)(ctx + 0x1a0))
        (*(uint64_t *)(ctx + 0x1a8), *(uint64_t *)(ctx + 0x168), uVar2,
         *(uint64_t *)(ctx + 0x170));
    sk_x_0040d07c(ctx + 0x10);
    sk_x_0040bd24(uVar2);
    sk_x_0040bd24(uVar1);
    sk_x_0040678c();
    /* UNRECOVERED_JUMPTABLE at 0x003f2360 */
    __builtin_unreachable();
}

/* FUN_003f244c @ 0x003f244c   (est. sk_op_003f244c)
 * Ghidra: void FUN_003f244c(void)
 * Continuation: opens the op context, unbinds the frame, releases two per-op
 * frames, and tail-dispatches. Mirror of FUN_003f1de8.
 * Confidence: low
 * Notes: UNRECOVERED_JUMPTABLE at 0x003f24bc. */
static void sk_op_003f244c(void)
{
    uint64_t uVar1, uVar2;
    uint8_t *ctx = /* unaff_x22 */ 0;

    sk_x_00406fd4();
    sk_x_0036986c();
    uVar1 = *(uint64_t *)(ctx + 0x180);
    uVar2 = *(uint64_t *)(ctx + 0x188);
    sk_x_0040d07c(ctx + 0x10);
    sk_x_0040bd24(uVar2);
    sk_x_0040bd24(uVar1);
    sk_x_00407128();
    /* UNRECOVERED_JUMPTABLE at 0x003f24bc */
    __builtin_unreachable();
}

/* FUN_003f256c @ 0x003f256c   (est. sk_helper_003f256c)
 * Ghidra: void FUN_003f256c(undefined8 param_1)
 * Capability helper: resolves param_1 against the object's cap slot
 * (FUN_003509c8) and dispatches through a vtable method at +0x20.
 * Confidence: low
 * Notes: unaff_x20 points at the object whose 0x38 word holds the slot; the
 *   vtable is carried in extraout_x16. */
static void sk_helper_003f256c(uint64_t p1)
{
    uint64_t extraout_x9 = 0;    /* extraout_x9 */
    uint64_t extraout_x16 = 0;   /* extraout_x16 */
    uint64_t *x20 = /* unaff_x20 */ 0;

    sk_x_003509c8(*(uint64_t *)(*x20 + 0x38), p1, p1);
    ((void (*)(uint64_t))*(uint64_t *)(extraout_x16 + 0x20))((uint64_t)x20 + extraout_x9);
}

/* FUN_003f2570 @ 0x003f2570   (est. sk_helper_003f2570)
 * Ghidra: void FUN_003f2570(undefined8 param_1)
 * Capability helper: identical body to FUN_003f256c (distinct code address).
 * Confidence: low
 * Notes: see FUN_003f256c. */
static void sk_helper_003f2570(uint64_t p1)
{
    uint64_t extraout_x9 = 0;    /* extraout_x9 */
    uint64_t extraout_x16 = 0;   /* extraout_x16 */
    uint64_t *x20 = /* unaff_x20 */ 0;

    sk_x_003509c8(*(uint64_t *)(*x20 + 0x38), p1, p1);
    ((void (*)(uint64_t))*(uint64_t *)(extraout_x16 + 0x20))((uint64_t)x20 + extraout_x9);
}

/* FUN_003f25d4 @ 0x003f25d4   (est. sk_helper_003f25d4)
 * Ghidra: void FUN_003f25d4(undefined8 param_1)
 * Helper: queries a state word (FUN_0040f4c8); if zero, derives a target from
 * the object at unaff_x20, then dispatches through a vtable method at
 * descriptor+0x10.
 * Confidence: low
 * Notes: UNRECOVERED_JUMPTABLE at 0x003f2660; extraout_x16 + 0x38 -> -8 is the
 *   vtable base. */
static void sk_helper_003f25d4(uint64_t p1)
{
    long lVar1;
    uint64_t extraout_x16 = 0;   /* extraout_x16 */
    uint64_t *x20 = /* unaff_x20 */ 0;

    sk_x_000027e8();
    lVar1 = (long)sk_x_0040f4c8();
    if (lVar1 == 0) {
        lVar1 = (long)x20 + *(long *)(*x20 + 0x40);
    }
    ((void (*)(uint64_t, long))*(uint64_t *)(*(long *)(*(long *)(extraout_x16 + 0x38) + -8) + 0x10))(p1, lVar1);
    /* UNRECOVERED_JUMPTABLE at 0x003f2660 (tail) */
}

/* FUN_003f274c @ 0x003f274c   (est. sk_op_003f274c)
 * Ghidra: void FUN_003f274c(void)
 * Opens the op context, invokes a vtable method at frame+0x70 -> +0x10 with
 * three context words, allocates a per-op frame, links the continuation
 * FUN_003f27f8, runs the frame binder FUN_00407610, and continues into the
 * sequencer FUN_003f2918.
 * Confidence: low
 * Notes: size class DAT_005a0234 (sk_g_005a0234). */
static void sk_op_003f274c(void)
{
    uint64_t *frame;
    uint64_t extraout_x17 = 0;   /* extraout_x17 */
    uint8_t *ctx = /* unaff_x22 */ 0;

    sk_x_00407000();
    ((void (*)(uint64_t, uint64_t, uint64_t))*(uint64_t *)(*(long *)(ctx + 0x70) + 0x10))
        (*(uint64_t *)(ctx + 0x78), *(uint64_t *)(ctx + 0x18), *(uint64_t *)(ctx + 0x68));
    sk_x_0040bb18(sk_g_005a0234);
    frame = (uint64_t *)sk_x_00406fe0();
    *(uint64_t **)(ctx + 0x90) = frame;
    *frame = extraout_x17;
    frame[1] = (uint64_t)sk_op_003f27f8;
    sk_x_00407610(frame, *(uint64_t *)(ctx + 0x78), *(uint64_t *)(ctx + 0x20),
                  *(uint64_t *)(ctx + 0x28), *(uint64_t *)(ctx + 0x30),
                  *(uint64_t *)(ctx + 0x38));
    sk_op_003f2918(0, 0, 0, 0, 0);
}

/* FUN_003f27f8 @ 0x003f27f8   (est. sk_op_003f27f8)
 * Ghidra: void FUN_003f27f8(void)
 * Continuation: stores the incoming frame pointer at frame+0x98, releases the
 * per-op frame, and either continues at an internal label with two context
 * pointers, or (when null) releases the frame at +0x78 and tail-dispatches.
 * Confidence: low
 * Notes: UNRECOVERED_JUMPTABLE at 0x003f28c4; LAB_003f28c8 non-null. */
static void sk_op_003f27f8(void)
{
    uint64_t uVar1;
    uint64_t extraout_x8 = 0;    /* extraout_x8 */
    uint64_t extraout_x8_00 = 0; /* extraout_x8_00 */
    uint64_t *extraout_x9 = 0;   /* extraout_x9 */
    uint8_t *x20 = /* unaff_x20 */ 0;

    sk_x_00407000();
    sk_x_00407018();
    sk_x_0040676c();
    *extraout_x9 = extraout_x8;
    uVar1 = *(uint64_t *)(extraout_x8_00 + 0x90);
    *(uint64_t *)(extraout_x8 + 0x98) = (uint64_t)x20;
    sk_x_0040bd24(uVar1);
    if (x20 != 0) {
        sk_x_00408db8(0x003f28c8 /* internal continuation label */,
                      *(uint64_t *)(extraout_x8 + 0x80), *(uint64_t *)(extraout_x8 + 0x88));
        return;
    }
    sk_x_0040bd24(*(uint64_t *)(extraout_x8 + 0x78));
    sk_x_00407128();
    /* UNRECOVERED_JUMPTABLE at 0x003f28c4 */
    __builtin_unreachable();
}

/* FUN_003f2918 @ 0x003f2918   (est. sk_op_003f2918)
 * Ghidra: void FUN_003f2918(undefined8, undefined8, undefined8, undefined8, long)
 * Op sequencer: opens the context and seeds 0x38..0x58 fields (context word,
 * resolved capability, status). Depending on param_5 either runs a fast
 * completion or the full sequence; stores the completion value and param_3,
 * then tail-dispatches.
 * Confidence: low
 * Notes: extraout_x16 carries the context word; param_5 selects the path. */
static void sk_op_003f2918(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4, long p5)
{
    (void)p1; (void)p2; (void)p4;
    uint64_t uVar1;
    uint64_t extraout_x8 = 0;    /* extraout_x8 */
    uint64_t extraout_x16 = 0;   /* extraout_x16 */
    uint64_t extraout_x16_00 = 0;/* extraout_x16_00 */
    uint8_t *ctx = /* unaff_x22 */ 0;

    sk_x_00406fd4();
    sk_x_0040752c();
    sk_x_000027e8();
    *(uint64_t *)(ctx + 0x38) = *(uint64_t *)(extraout_x16 + 0x38);
    sk_x_0007c028();
    *(uint64_t *)(ctx + 0x40) = extraout_x16_00;
    uVar1 = sk_x_004078e8(*(uint64_t *)(extraout_x8 + 0x40));
    *(uint64_t *)(ctx + 0x48) = uVar1;
    if (p5 == 0) {
        sk_x_00407248();
        uVar1 = /* extraout_x8_02 */ 0;
    } else {
        sk_x_00406590();
        /* (*extraout_x8_00)(); unrecovered continuation call */
        sk_x_0008e1ec();
        uVar1 = /* extraout_x8_01 */ 0;
    }
    *(uint64_t *)(ctx + 0x50) = uVar1;
    *(uint64_t *)(ctx + 0x58) = p3;
    sk_x_00353080();
    sk_x_00408db8();
}

/* FUN_003f29f0 @ 0x003f29f0   (est. sk_op_003f29f0)
 * Ghidra: void FUN_003f29f0(void)
 * Op dispatcher: opens the context, resolves a capability table entry
 * (FUN_0040833c), runs a helper, allocates a per-op frame, links the
 * continuation LAB_003f2ad0, and tail-dispatches through an opcode-indexed
 * jump table at the frame.
 * Confidence: low
 * Notes: UNRECOVERED_JUMPTABLE at 0x003f2acc; the jump target is
 *   piVar2[iVar3] where iVar3 = *piVar2 (opcode). */
static void sk_op_003f29f0(void)
{
    cl4_result_t pair;
    uint64_t uVar1, uVar4;
    int *piVar2;
    int iVar3;
    uint64_t *frame;
    uint64_t extraout_x17 = 0;   /* extraout_x17 */
    uint8_t *ctx = /* unaff_x22 */ 0;

    sk_x_00407ca0();
    uVar4 = sk_x_0040700c();
    uVar1 = *(uint64_t *)(ctx + 0x38);
    piVar2 = *(int **)(ctx + 0x20);
    pair = sk_x_0040833c(*(uint64_t *)(ctx + 0x40), uVar4, *(uint64_t *)(ctx + 0x18));
    /* (*extraout_x9)(pair.lo, pair.hi, uVar1); unrecovered continuation call */
    sk_x_0011aa70();
    sk_x_0040f434();
    iVar3 = *piVar2;
    sk_x_0040bb18(piVar2[1]);
    frame = (uint64_t *)sk_x_00406fe0();
    *(uint64_t **)(ctx + 0x60) = frame;
    *frame = extraout_x17;
    frame[1] = 0x003f2ad0;   /* internal continuation label */
    sk_x_00407610();
    /* UNRECOVERED_JUMPTABLE at 0x003f2acc: (*(code *)((long)piVar2 + iVar3))() */
    ((void (*)(void))(*(uint64_t *)((uint64_t)piVar2 + (int64_t)iVar3)))();
}

/* FUN_003f2bb8 @ 0x003f2bb8   (est. sk_op_003f2bb8)
 * Ghidra: void FUN_003f2bb8(void)
 * Continuation: opens the op context, runs a close helper (FUN_0040f524),
 * releases the frame at 0x48, and tail-dispatches.
 * Confidence: low
 * Notes: UNRECOVERED_JUMPTABLE at 0x003f2c08. */
static void sk_op_003f2bb8(void)
{
    uint64_t uVar1;
    uint8_t *ctx = /* unaff_x22 */ 0;

    sk_x_00407000();
    uVar1 = *(uint64_t *)(ctx + 0x48);
    sk_x_0040f524();
    sk_x_0040bd24(uVar1);
    sk_x_0040678c();
    /* UNRECOVERED_JUMPTABLE at 0x003f2c08 */
    __builtin_unreachable();
}

/* FUN_003f2d58 @ 0x003f2d58   (est. sk_op_003f2d58)
 * Ghidra: void FUN_003f2d58(undefined8, undefined8, int *param_3)
 * Op entry: resolves a capability word, seeds the context, allocates a two-word
 * op frame, links the continuation LAB_003f2ea0, and tail-dispatches through
 * the opcode-indexed jump table with the frame and a resolved value.
 * Confidence: low
 * Notes: UNRECOVERED_JUMPTABLE at 0x003f2e9c; param_3 is an opcode/size table
 *   ([0]=opcode, [1]=size class). */
static void sk_op_003f2d58(uint64_t p1, uint64_t p2, int *param_3)
{
    (void)p1; (void)p2;
    int iVar1;
    uint64_t uVar2, uVar3;
    long *frame;
    uint64_t extraout_x8 = 0;    /* extraout_x8 */
    uint64_t extraout_x16 = 0;   /* extraout_x16 */
    uint8_t *ctx = /* unaff_x22 */ 0;

    sk_x_004084a4();
    uVar2 = sk_x_00407924();
    sk_x_0007c028();
    uVar3 = sk_x_004078e8(*(uint64_t *)(extraout_x8 + 0x40));
    *(uint64_t *)(ctx + 0x10) = uVar3;
    sk_x_0035136c(*(uint64_t *)(extraout_x16 + 0x20));
    /* (*extraout_x8_00)(); unrecovered continuation call */
    sk_x_0040f434();
    iVar1 = *param_3;
    frame = (long *)sk_x_0040bb18(param_3[1]);
    *(long **)(ctx + 0x18) = frame;
    *frame = (long)ctx;
    frame[1] = (long)0x003f2ea0;   /* internal continuation label */
    /* UNRECOVERED_JUMPTABLE at 0x003f2e9c */
    __builtin_unreachable();
}

/* FUN_003f3058 @ 0x003f3058   (est. sk_trace_003f3058)
 * Ghidra: void FUN_003f3058(void)
 * Fault/report helper: builds a "TaskLocal" concurrency violation message and
 * raises a fatal fault (FUN_001afa84, non-returning) with the "Illegal
 * attempt to set a TaskLocal" string and the "Concurrency.TaskLocal" scope.
 * Confidence: medium
 * Notes: s_Illegal_attempt_to_set_a_TaskLoc_005dc160 (sk_g_005dc160);
 *   s__Concurrency_TaskLocal_swift_005dc140 (sk_g_005dc140); FUN_001afa84 is
 *   noreturn; extraout_x8 supplies the fault code. */
static void sk_trace_003f3058(void)
{
    uint64_t uVar1;
    uint64_t extraout_x8 = 0;    /* extraout_x8 */

    uVar1 = sk_x_0035ac70((uint64_t)sk_g_005dc160);
    uVar1 = sk_x_003593c0(uVar1, uVar1);
    /* noreturn fault */
    sk_x_001afa84(uVar1, 0xb, 2, 0xd00000000000004f,
                  extraout_x8 | 0x8000000000000000ULL, (uint64_t)sk_g_005dc140, 0x1c, 2);
}

/* FUN_003f30b8 @ 0x003f30b8   (est. sk_helper_003f30b8)
 * Ghidra: void FUN_003f30b8(undefined8 *param_1)
 * Stores the object pointer from unaff_x20 into both words of param_1, then
 * runs two helpers (FUN_0036b270, FUN_00084180).
 * Confidence: low
 * Notes: writes param_1[0] and param_1[1] with the same value. */
static void sk_helper_003f30b8(uint64_t *param_1)
{
    uint64_t x20 = /* unaff_x20 */ 0;

    param_1[0] = x20;
    param_1[1] = x20;
    sk_x_0036b270();
    sk_x_00084180();
}

/* FUN_003f3108 @ 0x003f3108   (est. sk_helper_003f3108)
 * Ghidra: void FUN_003f3108(undefined8 *param_1, uint param_2)
 * Conditional helper: if the low bit of param_2 is set, runs FUN_0036b270 on
 * the object and the fatal TaskLocal helper; then always runs the TaskLocal
 * helper and the descriptor helper FUN_003f25d4.
 * Confidence: low */
static void sk_helper_003f3108(uint64_t *param_1, uint32_t param_2)
{
    if ((param_2 & 1) != 0) {
        sk_x_0036b270(*param_1);
        sk_trace_003f3058();
    }
    sk_trace_003f3058();
    sk_helper_003f25d4(0);
}

/* FUN_003f310c @ 0x003f310c   (est. sk_helper_003f310c)
 * Ghidra: void FUN_003f310c(undefined8 *param_1, uint param_2)
 * Conditional helper: identical body to FUN_003f3108 (distinct code address).
 * Confidence: low
 * Notes: see FUN_003f3108. */
static void sk_helper_003f310c(uint64_t *param_1, uint32_t param_2)
{
    if ((param_2 & 1) != 0) {
        sk_x_0036b270(*param_1);
        sk_trace_003f3058();
    }
    sk_trace_003f3058();
    sk_helper_003f25d4(0);
}

/* FUN_003f312c @ 0x003f312c   (est. sk_trace_003f312c)
 * Ghidra: undefined1 [16] FUN_003f312c(void)
 * Trace-record builder: walks the object at unaff_x20, emits a two-chunk
 * diagnostic header ("Valu", "e:"), runs an object-capability formatter, and
 * returns a 16-byte record built from the local/stack cells.
 * Confidence: low
 * Notes: FUN_002acbb8 writes 8-byte trace chunks (the constants are little-
 *   endian ASCII); FUN_002a4ab4 selects the trace entry type. */
static cl4_result_t sk_trace_003f312c(void)
{
    cl4_result_t result;
    uint64_t extraout_x1 = 0;    /* extraout_x1 */
    uint64_t *x20 = /* unaff_x20 */ 0;
    long lVar2;
    uint64_t local_40 = 0;
    uint64_t uStack_38 = 0;

    lVar2 = *x20;
    sk_x_00100c04();
    sk_x_002a4ab4(0x14);
    sk_x_00208418(lVar2, 0);
    sk_x_002acbb8();
    sk_x_003a25d4(extraout_x1);
    sk_x_002acbb8(0x746c756166656428ULL, 0xef203a65756c6156ULL);
    sk_x_001b1780((long)x20 + *(long *)(*x20 + 0x40), *(uint64_t *)(lVar2 + 0x38));
    sk_x_002acbb8(0x29, 0xe100000000000000ULL);
    result.hi = uStack_38;
    result.lo = local_40;
    return result;
}

/* FUN_003f3218 @ 0x003f3218   (est. sk_helper_003f3218)
 * Ghidra: void FUN_003f3218(void)
 * Capability helper: resolves the object's cap slot (FUN_003509c8) and
 * dispatches through a vtable method at +8.
 * Confidence: low
 * Notes: vtable carried in extraout_x16; offset added to unaff_x20. */
static void sk_helper_003f3218(void)
{
    uint64_t extraout_x9 = 0;    /* extraout_x9 */
    uint64_t extraout_x16 = 0;   /* extraout_x16 */
    uint64_t *x20 = /* unaff_x20 */ 0;

    sk_x_003509c8(*(uint64_t *)(*x20 + 0x38));
    ((void (*)(uint64_t))*(uint64_t *)(extraout_x16 + 8))((uint64_t)x20 + extraout_x9);
}

/* FUN_003f327c @ 0x003f327c   (est. sk_helper_003f327c)
 * Ghidra: void FUN_003f327c(void)
 * Helper: runs FUN_003f3218 then the object teardown FUN_0036b6ac.
 * Confidence: low */
static void sk_helper_003f327c(void)
{
    sk_helper_003f3218();
    sk_x_0036b6ac();
}

/* FUN_003f3280 @ 0x003f3280   (est. sk_helper_003f3280)
 * Ghidra: void FUN_003f3280(void)
 * Helper: identical body to FUN_003f327c (distinct code address).
 * Confidence: low
 * Notes: see FUN_003f327c. */
static void sk_helper_003f3280(void)
{
    sk_helper_003f3218();
    sk_x_0036b6ac();
}

/* FUN_003f32b4 @ 0x003f32b4   (est. sk_helper_003f32b4)
 * Ghidra: void FUN_003f32b4(void)
 * Helper: forwards to the trace-record builder FUN_003f312c.
 * Confidence: low */
static void sk_helper_003f32b4(void)
{
    sk_trace_003f312c();
}

/* FUN_003f32d8 @ 0x003f32d8   (est. sk_trace_003f32d8)
 * Ghidra: void FUN_003f32d8(undefined8, undefined8, undefined8)
 * Descriptor-advance helper: checks a state flag (FUN_0040c9d0); when set it
 * invokes a global trap hook, then classifies the incoming address words
 * (unaff_x21/unaff_x19) by their tag bits to select a physical or mapping
 * target before running the descriptor fix-up helpers.
 * Confidence: low
 * Notes: DAT_00658c80 (sk_g_00658c80) is a function pointer; bit 0x3c/0x3d
 *   tag checks select the target; FUN_004ba7ec is called with a target and the
 *   mode word. */
static void sk_trace_003f32d8(uint64_t p1, uint64_t p2, uint64_t p3)
{
    (void)p1; (void)p2;
    uint64_t uVar1, uVar2;
    uint64_t extraout_x8 = 0;    /* extraout_x8 */
    uint64_t x19 = /* unaff_x19 */ 0;
    uint64_t x21 = /* unaff_x21 */ 0;
    uint64_t stackcell = 0;

    sk_x_0008409c(); /* FUN_0008409c — first call of the decompile */
    (void)uVar1;
    uVar2 = 0;
    if (sk_x_0040c9d0() & 1) {
        ((void (*)(void))sk_g_00658c80)();
        sk_x_003539e4();
        *(uint64_t *)(extraout_x8 + -0x20) = x21;
        *(uint64_t *)(extraout_x8 + -0x18) = x19;
        *(uint64_t *)(extraout_x8 + -0x10) = p3;
        if ((x19 >> 0x3c & 1) == 0) {
            if ((x19 >> 0x3d & 1) != 0) {
                sk_x_00084180();
                uVar2 = sk_x_001ee018();
                sk_x_004ba7ec(&stackcell, uVar2, 1, p3);
                return;
            }
            if ((x21 >> 0x3c & 1) != 0) {
                sk_x_00084180();
                uVar2 = sk_x_001ee018();
                sk_x_004ba7ec((x19 & 0xfffffffffffffffULL) + 0x20, uVar2, 1, p3);
                return;
            }
        }
        sk_x_00359024();
        sk_x_0040755c((uint64_t)sk_x_003fd3ac);
        sk_x_002a4468();
    }
}

/* FUN_003f33f0 @ 0x003f33f0   (est. sk_abort_003f33f0)
 * Ghidra: void FUN_003f33f0(void)
 * Fatal-abort entry: opens the op context, runs the abort prelude
 * (FUN_00407030, FUN_003593c0, FUN_00407048), then raises a non-returning
 * fault (FUN_001afa84).
 * Confidence: low
 * Notes: FUN_001afa84 is noreturn. */
static void sk_abort_003f33f0(void)
{
    sk_x_00406fd4();
    sk_x_00407030();
    sk_x_003593c0();
    sk_x_00407048();
    sk_x_001afa84();   /* noreturn */
}

/* FUN_003f345c @ 0x003f345c   (est. sk_abort_003f345c)
 * Ghidra: void FUN_003f345c(void)
 * Fatal-abort entry: identical body to FUN_003f33f0 (distinct address).
 * Confidence: low
 * Notes: see FUN_003f33f0. */
static void sk_abort_003f345c(void)
{
    sk_x_00406fd4();
    sk_x_00407030();
    sk_x_003593c0();
    sk_x_00407048();
    sk_x_001afa84();   /* noreturn */
}

/* FUN_003f34b4 @ 0x003f34b4   (est. sk_helper_003f34b4)
 * Ghidra: void FUN_003f34b4(undefined1 param_1)
 * Helper: opens a context slot, passes param_1 to the trace logger
 * (thunk of FUN_002298d4), and runs FUN_001a8564.
 * Confidence: low
 * Notes: thunk_FUN_002298d4 logs a single-byte value. */
static void sk_helper_003f34b4(uint8_t p1)
{
    sk_x_004080b0();
    sk_x_002298d4(p1);
    sk_x_001a8564();
}

/* FUN_003f34fc @ 0x003f34fc   (est. sk_abort_003f34fc)
 * Ghidra: void FUN_003f34fc(void)
 * Abort-chain entry: runs the abort prelude then breaks to the next entry in
 * the chain (0x003f3524).
 * Confidence: low
 * Notes: SoftwareBreakpoint(1, 0x3f3524) is noreturn; the chained break
 *   addresses form a linked list of abort entries. */
static void sk_abort_003f34fc(void)
{
    sk_x_00407030();
    sk_x_00406444();
    sk_break(1, 0x3f3524);   /* noreturn: trap to next abort entry */
}

/* FUN_003f3524 @ 0x003f3524   (est. sk_abort_003f3524)
 * Ghidra: void FUN_003f3524(void)
 * Abort-chain entry: runs the abort prelude then breaks to the next entry
 * (0x003f354c).
 * Confidence: low */
static void sk_abort_003f3524(void)
{
    sk_x_00407030();
    sk_x_00406444();
    sk_break(1, 0x3f354c);   /* noreturn */
}

/* FUN_003f354c @ 0x003f354c   (est. sk_abort_003f354c)
 * Ghidra: void FUN_003f354c(void)
 * Abort-chain entry: runs the abort prelude then breaks to the next entry
 * (0x003f3574).
 * Confidence: low */
static void sk_abort_003f354c(void)
{
    sk_x_00407030();
    sk_x_00406444();
    sk_break(1, 0x3f3574);   /* noreturn */
}

/* FUN_003f3574 @ 0x003f3574   (est. sk_abort_003f3574)
 * Ghidra: void FUN_003f3574(void)
 * Abort-chain entry: runs the abort prelude then breaks to the next entry
 * (0x003f359c).
 * Confidence: low */
static void sk_abort_003f3574(void)
{
    sk_x_00407030();
    sk_x_00406444();
    sk_break(1, 0x3f359c);   /* noreturn */
}

/* FUN_003f359c @ 0x003f359c   (est. sk_abort_003f359c)
 * Ghidra: void FUN_003f359c(void)
 * Abort-chain entry: enters the chain from the previous entry (FUN_003f354c),
 * registers a continuation (FUN_003f35ac) with the abort prelude, then breaks
 * to the next entry (0x003f35d4).
 * Confidence: low
 * Notes: FUN_00407030(FUN_003f35ac) registers the continuation pointer. */
static void sk_abort_003f359c(void)
{
    sk_abort_003f354c();
    sk_x_00407030((uint64_t)sk_abort_003f35ac);
    sk_x_00406444();
    sk_break(1, 0x3f35d4);   /* noreturn */
}

/* FUN_003f35a0 @ 0x003f35a0   (est. sk_abort_003f35a0)
 * Ghidra: void FUN_003f35a0(void)
 * Abort-chain entry: identical body to FUN_003f359c (distinct address).
 * Confidence: low
 * Notes: see FUN_003f359c. */
static void sk_abort_003f35a0(void)
{
    sk_abort_003f354c();
    sk_x_00407030((uint64_t)sk_abort_003f35ac);
    sk_x_00406444();
    sk_break(1, 0x3f35d4);   /* noreturn */
}

/* FUN_003f35ac @ 0x003f35ac   (est. sk_abort_003f35ac)
 * Ghidra: void FUN_003f35ac(void)
 * Abort-chain entry: runs the abort prelude then breaks to the next entry
 * (0x003f35d4).
 * Confidence: low */
static void sk_abort_003f35ac(void)
{
    sk_x_00407030();
    sk_x_00406444();
    sk_break(1, 0x3f35d4);   /* noreturn */
}

/* FUN_003f35d4 @ 0x003f35d4   (est. sk_abort_003f35d4)
 * Ghidra: void FUN_003f35d4(void)
 * Abort-chain entry: runs the abort prelude then breaks to the next entry
 * (0x003f35fc).
 * Confidence: low */
static void sk_abort_003f35d4(void)
{
    sk_x_00407030();
    sk_x_00406444();
    sk_break(1, 0x3f35fc);   /* noreturn */
}

/* FUN_003f3610 @ 0x003f3610   (est. sk_abort_003f3610)
 * Ghidra: void FUN_003f3610(void)
 * Non-breaking abort entry: opens the op context, runs the abort prelude and
 * the close helper, and returns normally.
 * Confidence: low */
static void sk_abort_003f3610(void)
{
    sk_x_00406fd4();
    sk_x_00407030();
    sk_x_00406444();
}

/* FUN_003f3650 @ 0x003f3650   (est. sk_op_003f3650)
 * Ghidra: void FUN_003f3650(undefined8, undefined8, undefined8, undefined8)
 * Op sequencer: opens the context and, based on a carry flag, runs either the
 * idle path or the full completion sequence; then continues at FUN_003f36dc
 * with param_4.
 * Confidence: low
 * Notes: extraout_x1 is the register fragment selecting the path. */
static void sk_op_003f3650(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4)
{
    (void)p1; (void)p2;
    uint64_t extraout_x1 = 0;    /* extraout_x1 */

    sk_x_00406fd4();
    if (extraout_x1 == 0) {
        sk_x_004075c4();
    } else {
        sk_x_004078d4();
        sk_x_003d4658(p3);
        sk_x_0034bcf0();
        /* (*extraout_x8)(); unrecovered continuation call */
        sk_x_00407588();
    }
    sk_x_00408db8((uint64_t)sk_abort_003f36dc, p4);
}

/* FUN_003f36dc @ 0x003f36dc   (est. sk_abort_003f36dc)
 * Ghidra: void FUN_003f36dc(void)
 * Non-breaking abort entry: opens the op context, runs the abort prelude and
 * the close helper, and returns normally. Mirror of FUN_003f3610.
 * Confidence: low */
static void sk_abort_003f36dc(void)
{
    sk_x_00406fd4();
    sk_x_00407030();
    sk_x_00406444();
}

/* FUN_003f371c @ 0x003f371c   (est. sk_abort_003f371c)
 * Ghidra: void FUN_003f371c(void)
 * Abort-chain entry: runs the abort prelude then breaks to the next entry
 * (0x003f3744).
 * Confidence: low */
static void sk_abort_003f371c(void)
{
    sk_x_00407030();
    sk_x_00406444();
    sk_break(1, 0x3f3744);   /* noreturn */
}

/* FUN_003f3744 @ 0x003f3744   (est. sk_abort_003f3744)
 * Ghidra: void FUN_003f3744(void)
 * Abort-chain entry: runs the abort prelude then breaks to the next entry
 * (0x003f376c).
 * Confidence: low */
static void sk_abort_003f3744(void)
{
    sk_x_00407030();
    sk_x_00406444();
    sk_break(1, 0x3f376c);   /* noreturn */
}

/* FUN_003f376c @ 0x003f376c   (est. sk_abort_003f376c)
 * Ghidra: void FUN_003f376c(void)
 * Abort-chain entry: runs the abort prelude then breaks to the next entry
 * (0x003f3794).
 * Confidence: low */
static void sk_abort_003f376c(void)
{
    sk_x_00407030();
    sk_x_00406444();
    sk_break(1, 0x3f3794);   /* noreturn */
}

/* FUN_003f3794 @ 0x003f3794   (est. sk_abort_003f3794)
 * Ghidra: void FUN_003f3794(void)
 * Abort-chain entry (variant close helper FUN_004064c4): runs the abort
 * prelude then breaks to the next entry (0x003f37bc).
 * Confidence: low */
static void sk_abort_003f3794(void)
{
    sk_x_00407030();
    sk_x_004064c4();
    sk_break(1, 0x3f37bc);   /* noreturn */
}

/* FUN_003f37bc @ 0x003f37bc   (est. sk_abort_003f37bc)
 * Ghidra: void FUN_003f37bc(void)
 * Abort-chain entry (FUN_004064c4 close): breaks to the next entry
 * (0x003f37e4).
 * Confidence: low */
static void sk_abort_003f37bc(void)
{
    sk_x_00407030();
    sk_x_004064c4();
    sk_break(1, 0x3f37e4);   /* noreturn */
}

/* FUN_003f37e4 @ 0x003f37e4   (est. sk_abort_003f37e4)
 * Ghidra: void FUN_003f37e4(void)
 * Abort-chain entry (FUN_004064c4 close): breaks to the next entry
 * (0x003f380c).
 * Confidence: low */
static void sk_abort_003f37e4(void)
{
    sk_x_00407030();
    sk_x_004064c4();
    sk_break(1, 0x3f380c);   /* noreturn */
}

/* FUN_003f380c @ 0x003f380c   (est. sk_abort_003f380c)
 * Ghidra: void FUN_003f380c(void)
 * Abort-chain entry (FUN_004064c4 close): breaks to the next entry
 * (0x003f3834).
 * Confidence: low */
static void sk_abort_003f380c(void)
{
    sk_x_00407030();
    sk_x_004064c4();
    sk_break(1, 0x3f3834);   /* noreturn */
}

/* FUN_003f3834 @ 0x003f3834   (est. sk_abort_003f3834)
 * Ghidra: void FUN_003f3834(void)
 * Abort-chain entry: enters from the previous entry (FUN_003f37e4), registers
 * a continuation (FUN_003f3844) with the abort prelude, then breaks to the
 * next entry (0x003f386c).
 * Confidence: low */
static void sk_abort_003f3834(void)
{
    sk_abort_003f37e4();
    sk_x_00407030((uint64_t)sk_abort_003f3844);
    sk_x_004064c4();
    sk_break(1, 0x3f386c);   /* noreturn */
}

/* FUN_003f3838 @ 0x003f3838   (est. sk_abort_003f3838)
 * Ghidra: void FUN_003f3838(void)
 * Abort-chain entry: identical body to FUN_003f3834 (distinct address).
 * Confidence: low
 * Notes: see FUN_003f3834. */
static void sk_abort_003f3838(void)
{
    sk_abort_003f37e4();
    sk_x_00407030((uint64_t)sk_abort_003f3844);
    sk_x_004064c4();
    sk_break(1, 0x3f386c);   /* noreturn */
}

/* FUN_003f3844 @ 0x003f3844   (est. sk_abort_003f3844)
 * Ghidra: void FUN_003f3844(void)
 * Abort-chain entry (FUN_004064c4 close): breaks to the next entry
 * (0x003f386c).
 * Confidence: low */
static void sk_abort_003f3844(void)
{
    sk_x_00407030();
    sk_x_004064c4();
    sk_break(1, 0x3f386c);   /* noreturn */
}

/* FUN_003f386c @ 0x003f386c   (est. sk_abort_003f386c)
 * Ghidra: void FUN_003f386c(void)
 * Abort-chain entry (FUN_004064c4 close): breaks to the next entry
 * (0x003f3894).
 * Confidence: low */
static void sk_abort_003f386c(void)
{
    sk_x_00407030();
    sk_x_004064c4();
    sk_break(1, 0x3f3894);   /* noreturn */
}

/* FUN_003f38a8 @ 0x003f38a8   (est. sk_abort_003f38a8)
 * Ghidra: void FUN_003f38a8(void)
 * Non-breaking abort entry (FUN_004064c4 close): opens the op context, runs
 * the abort prelude and close helper, and returns normally.
 * Confidence: low */
static void sk_abort_003f38a8(void)
{
    sk_x_00406fd4();
    sk_x_00407030();
    sk_x_004064c4();
}

/* FUN_003f38e8 @ 0x003f38e8   (est. sk_abort_003f38e8)
 * Ghidra: void FUN_003f38e8(void)
 * Abort-chain entry (FUN_004064c4 close): breaks to the next entry
 * (0x003f3910).
 * Confidence: low */
static void sk_abort_003f38e8(void)
{
    sk_x_00407030();
    sk_x_004064c4();
    sk_break(1, 0x3f3910);   /* noreturn */
}

/* FUN_003f3910 @ 0x003f3910   (est. sk_abort_003f3910)
 * Ghidra: void FUN_003f3910(void)
 * Abort-chain entry (FUN_004064c4 close): breaks to the next entry
 * (0x003f3938).
 * Confidence: low */
static void sk_abort_003f3910(void)
{
    sk_x_00407030();
    sk_x_004064c4();
    sk_break(1, 0x3f3938);   /* noreturn */
}

/* FUN_003f3938 @ 0x003f3938   (est. sk_abort_003f3938)
 * Ghidra: void FUN_003f3938(void)
 * Abort-chain entry (FUN_004064c4 close): breaks to the next entry
 * (0x003f3960).
 * Confidence: low */
static void sk_abort_003f3938(void)
{
    sk_x_00407030();
    sk_x_004064c4();
    sk_break(1, 0x3f3960);   /* noreturn */
}

/* FUN_003f3960 @ 0x003f3960   (est. sk_helper_003f3960)
 * Ghidra: void FUN_003f3960(void)
 * Descriptor-buffer advance helper: reads a three-word descriptor from
 * FUN_00251758 and, with a base word from the object at unaff_x20, advances a
 * cursor into a descriptor array. It performs signed carry/borrow bounds
 * checks (aborting on overflow) and copies the advancing ranges through
 * FUN_0019cb68, adjusting the cursor by a per-entry stride.
 * Confidence: low
 * Notes: SCARRY8/SBORROW8 bound checks abort via SoftwareBreakpoint at
 *   0x3f3a2c/0x3f3a30/0x3f3a34; extraout_x16/extraout_x8 are the descriptor
 *   base/stride produced by FUN_003522b8. */
static void sk_helper_003f3960(void)
{
    long lVar1, lVar2, lVar6, lVar7, lVar8;
    long *plVar5;
    uint64_t uVar9;
    int bVar4;
    uint64_t *x20 = /* unaff_x20 */ 0;
    cl4_result_t adv;
    cl4_result_t adv2;

    lVar8 = (long)*x20;
    plVar5 = (long *)sk_x_00251758();
    lVar6 = (long)sk_x_00251820();
    uVar9 = *(uint64_t *)(lVar8 + 0x58);
    lVar8 = plVar5[1];
    lVar1 = plVar5[2];
    if (SCARRY8(lVar1, lVar8)) {
        sk_break(1, 0x3f3a2c);   /* noreturn: descriptor overflow */
    }
    lVar7 = *plVar5;
    if (lVar7 < lVar1 + lVar8) {
        lVar2 = lVar7 - lVar1;
        if (SBORROW8(lVar7, lVar1)) {
            sk_break(1, 0x3f3a30);   /* noreturn: borrow underflow */
        }
        adv = sk_x_003522b8();
        sk_x_0019cb68(lVar2, lVar6 + *(long *)(adv.hi + 0x48) * (long)adv.lo, uVar9);
        bVar4 = SBORROW8(lVar8, lVar2);
        lVar8 = lVar8 - lVar2;
        if (bVar4) {
            sk_break(1, 0x3f3a34);   /* noreturn: remainder underflow */
        }
    } else {
        adv2 = sk_x_003522b8();
        lVar6 = lVar6 + *(long *)(adv2.hi + 0x48) * (long)adv2.lo;
    }
    sk_x_0019cb68(lVar8, lVar6, uVar9);
    sk_x_00213834();
}

/* FUN_003f3a34 @ 0x003f3a34   (est. sk_helper_003f3a34)
 * Ghidra: void FUN_003f3a34(void)
 * Helper: runs the descriptor-advance helper FUN_003f3960 then allocates a
 * 0x28-byte object of tag 7 (FUN_0036b6ac).
 * Confidence: low */
static void sk_helper_003f3a34(void)
{
    uint64_t uVar1;

    uVar1 = sk_x_003f3960(); /* placeholder; see FUN_003f3960 */
    (void)uVar1;
    sk_x_0036b6ac(0, 0x28, 7);
}

/* FUN_003f3a38 @ 0x003f3a38   (est. sk_helper_003f3a38)
 * Ghidra: void FUN_003f3a38(void)
 * Helper: identical body to FUN_003f3a34 (distinct code address).
 * Confidence: low
 * Notes: see FUN_003f3a34. */
static void sk_helper_003f3a38(void)
{
    uint64_t uVar1;

    uVar1 = sk_x_003f3960(); /* placeholder; see FUN_003f3960 */
    (void)uVar1;
    sk_x_0036b6ac(0, 0x28, 7);
}

/* FUN_003f3a58 @ 0x003f3a58   (est. sk_trace_003f3a58)
 * Ghidra: undefined1 [16] FUN_003f3a58(void)
 * Trace-record builder: reads a three-word descriptor (FUN_00251758), emits a
 * "DequeSt…" header chunk, runs a sub-formatter FUN_003f3b9c, and returns a
 * 16-byte record whose lo word is the "D_equeSt" ASCII literal.
 * Confidence: low
 * Notes: the returned .lo = 0x745365757165445f ("DequeSt"), .hi =
 *   0xee003c656761726f ("orage<"); FUN_002acbb8 writes trace chunks. */
static cl4_result_t sk_trace_003f3a58(void)
{
    cl4_result_t result;
    uint64_t *puVar2;
    uint64_t extraout_x1 = 0;    /* extraout_x1 */
    uint64_t extraout_x1_00 = 0; /* extraout_x1_00 */
    uint64_t *x20 = /* unaff_x20 */ 0;
    long lVar3;
    uint64_t uVar4;
    uint64_t local_38 = 0;

    lVar3 = *x20;
    puVar2 = (uint64_t *)sk_x_00251758();
    sk_x_00251820();
    uVar4 = *(uint64_t *)(lVar3 + 0x58);
    sk_x_00100c04();
    sk_x_002a4ab4(0x13);
    sk_x_003a25d4(local_38);
    sk_x_00208418(uVar4, 0);
    sk_x_002acbb8();
    sk_x_003a25d4(extraout_x1);
    sk_x_002acbb8(0x3e, 0xe100000000000000ULL);
    sk_trace_003f3b9c();
    sk_x_002acbb8();
    sk_x_003a25d4(extraout_x1_00);
    result.hi = 0xee003c656761726fULL;
    result.lo = 0x745365757165445fULL;
    return result;
}

/* FUN_003f3b34 @ 0x003f3b34   (est. sk_helper_003f3b34)
 * Ghidra: void FUN_003f3b34(void)
 * Helper: forwards to the trace-record builder FUN_003f3a58.
 * Confidence: low */
static void sk_helper_003f3b34(void)
{
    sk_trace_003f3a58();
}

/* FUN_003f3b58 @ 0x003f3b58   (est. sk_helper_003f3b58)
 * Ghidra: void FUN_003f3b58(void)
 * Object-init helper: allocates a 0x28-byte object of tag 7 from a size
 * table (FUN_00002534 + FUN_0036a940), stores it into the global
 * sk_g_006adf70, and zeroes its 0x10/0x18/0x20 fields.
 * Confidence: low
 * Notes: _DAT_006adf70 is a writable global; FUN_00002534(0x657990,
 *   &DAT_005a16f8) selects the size/alloc entry. */
static void sk_helper_003f3b58(void)
{
    uint64_t uVar1;

    uVar1 = sk_x_00002534(0x657990, (uint64_t)&sk_g_005a16f8);
    sk_g_006adf70 = sk_x_0036a940(uVar1, 0x28, 7);
    *(uint64_t *)(sk_g_006adf70 + 0x18) = 0;
    *(uint64_t *)(sk_g_006adf70 + 0x20) = 0;
    *(uint64_t *)(sk_g_006adf70 + 0x10) = 0;
}

/* FUN_003f3b5c @ 0x003f3b5c   (est. sk_helper_003f3b5c)
 * Ghidra: void FUN_003f3b5c(void)
 * Object-init helper: identical body to FUN_003f3b58 (distinct address).
 * Confidence: low
 * Notes: see FUN_003f3b58. */
static void sk_helper_003f3b5c(void)
{
    uint64_t uVar1;

    uVar1 = sk_x_00002534(0x657990, (uint64_t)&sk_g_005a16f8);
    sk_g_006adf70 = sk_x_0036a940(uVar1, 0x28, 7);
    *(uint64_t *)(sk_g_006adf70 + 0x18) = 0;
    *(uint64_t *)(sk_g_006adf70 + 0x20) = 0;
    *(uint64_t *)(sk_g_006adf70 + 0x10) = 0;
}

/* FUN_003f3b9c @ 0x003f3b9c   (est. sk_trace_003f3b9c)
 * Ghidra: undefined1 [16] FUN_003f3b9c(void)
 * Trace-record builder: formats a capability/statistics record ("(capacit:
 *   count, Status: x, Stats: x)"). Emits several two-chunk trace lines and a
 *   two-value tail, then returns a 16-byte record whose lo word is the
 *   "(capacit" ASCII literal.
 * Confidence: low
 * Notes: FUN_00027724(0x6720e0) resolves a format token used across the
 *   lines; returned .lo = 0x7469636170616328 ("(capacit"). */
static cl4_result_t sk_trace_003f3b9c(void)
{
    cl4_result_t result;
    uint64_t extraout_x1 = 0;    /* extraout_x1 */
    uint64_t extraout_x1_00 = 0; /* extraout_x1_00 */
    uint64_t local_58 = 0;

    sk_x_00350b54();
    sk_x_000b430c();
    sk_x_002a4ab4(0x28);
    sk_x_003a25d4(local_58);
    {
        void (*pcVar2)(uint64_t, uint64_t) = (void (*)(uint64_t, uint64_t))sk_x_00027724(0x6720e0);
        sk_x_00351384();
        pcVar2(0, 0);
        sk_x_002acbb8();
        sk_x_003a25d4(extraout_x1);
        sk_x_002acbb8(0x3a746e756f63202cULL, 0xe900000000000020ULL);
        sk_x_00351384();
        pcVar2(0, 0);
        sk_x_002acbb8();
        sk_x_003a25d4(extraout_x1_00);
        sk_x_002acbb8(0x537472617473202cULL, 0xed0000203a746f6cULL);
    }
    sk_trace_003f3d34();
    sk_x_000e72d4();
    sk_x_003a25d4();
    sk_x_00408108();
    result.hi = 0xeb00000000203a79ULL;
    result.lo = 0x7469636170616328ULL;
    return result;
}

/* FUN_003f3cfc @ 0x003f3cfc   (est. sk_helper_003f3cfc)
 * Ghidra: long FUN_003f3cfc(long param_1, long param_2)
 * Range helper: validates that param_2 is non-negative (or, when param_2<1,
 * that param_1 is non-negative). On a negative value it runs a check helper
 * and raises a non-returning fault.
 * Confidence: medium
 * Notes: FUN_001afa84 is noreturn; returns the validated value (param_2 or the
 *   copied param_1). */
static long sk_helper_003f3cfc(long param_1, long param_2)
{
    if ((param_2 < 1) && (param_2 = param_1, param_1 < 0)) {
        sk_x_0040633c();
        sk_x_001afa84();   /* noreturn */
    }
    return param_2;
}

/* FUN_003f3d34 @ 0x003f3d34   (est. sk_trace_003f3d34)
 * Ghidra: undefined1 [16] FUN_003f3d34(void)
 * Trace-record helper: resolves a format token (FUN_00027724), calls it with
 * two format addresses, emits a trace chunk, and returns a 16-byte record
 * (lo=0x40, hi=0).
 * Confidence: low
 * Notes: FUN_002acbb8 writes the trace chunk. */
static cl4_result_t sk_trace_003f3d34(void)
{
    cl4_result_t result;
    void (*pcVar2)(uint64_t, uint64_t);

    pcVar2 = (void (*)(uint64_t, uint64_t))sk_x_00027724(0x6720e0);
    pcVar2(0x677880, 0x6720e0);
    sk_x_000e72d4();
    sk_x_003a25d4(0x6720e0);
    result.hi = 0xe100000000000000ULL;
    result.lo = 0x40;
    return result;
}

/* FUN_003f3db8 @ 0x003f3db8   (est. sk_helper_003f3db8)
 * Ghidra: uint FUN_003f3db8(void)
 * Boolean helper: opens a context slot (FUN_00407d74), reads a flag word from
 * the thunk of FUN_002d49f4, and returns its inverted low bit (NOT(flag) & 1).
 * Confidence: low
 * Notes: thunk_FUN_002d49f4 returns a status word. */
static uint32_t sk_helper_003f3db8(void)
{
    uint32_t uVar1;

    sk_x_00407d74();
    uVar1 = (uint32_t)sk_x_002d49f4();
    return (uVar1 ^ 0xffffffffu) & 1;
}

/* FUN_003f3dbc @ 0x003f3dbc   (est. sk_helper_003f3dbc)
 * Ghidra: uint FUN_003f3dbc(void)
 * Boolean helper: identical body to FUN_003f3db8 (distinct address).
 * Confidence: low
 * Notes: see FUN_003f3db8. */
static uint32_t sk_helper_003f3dbc(void)
{
    uint32_t uVar1;

    sk_x_00407d74();
    uVar1 = (uint32_t)sk_x_002d49f4();
    return (uVar1 ^ 0xffffffffu) & 1;
}

/* FUN_003f3ddc @ 0x003f3ddc   (est. sk_helper_003f3ddc)
 * Ghidra: uint FUN_003f3ddc(void)
 * Boolean helper: reads a flag word from the thunk of FUN_002d49f4 and returns
 * its inverted low bit (no context-open prelude).
 * Confidence: low */
static uint32_t sk_helper_003f3ddc(void)
{
    uint32_t uVar1;

    uVar1 = (uint32_t)sk_x_002d49f4();
    return (uVar1 ^ 0xffffffffu) & 1;
}

/* FUN_003f3de0 @ 0x003f3de0   (est. sk_helper_003f3de0)
 * Ghidra: uint FUN_003f3de0(void)
 * Boolean helper: identical body to FUN_003f3ddc (distinct address).
 * Confidence: low
 * Notes: see FUN_003f3ddc. */
static uint32_t sk_helper_003f3de0(void)
{
    uint32_t uVar1;

    uVar1 = (uint32_t)sk_x_002d49f4();
    return (uVar1 ^ 0xffffffffu) & 1;
}

/* FUN_003f3dfc @ 0x003f3dfc   (est. sk_helper_003f3dfc)
 * Ghidra: void FUN_003f3dfc(void)
 * Helper: opens a context slot (FUN_00407d74) and reads a flag word from the
 * thunk of FUN_002d49f4, discarding it.
 * Confidence: low */
static void sk_helper_003f3dfc(void)
{
    sk_x_00407d74();
    sk_x_002d49f4();
}

/* FUN_003f3e34 @ 0x003f3e34   (est. sk_abort_003f3e34)
 * Ghidra: void FUN_003f3e34(void)
 * Abort entry: runs the abort prelude (FUN_004070cc, FUN_0040677c with tag
 * 0x1d, FUN_00406518, FUN_004085a8) then breaks to the next entry
 * (0x003f3e64).
 * Confidence: low
 * Notes: SoftwareBreakpoint(1, 0x3f3e64) is noreturn. */
static void sk_abort_003f3e34(void)
{
    sk_x_004070cc();
    sk_x_0040677c(0x1d);
    sk_x_00406518();
    sk_x_004085a8();
    sk_break(1, 0x3f3e64);   /* noreturn */
}

/* FUN_003f3e64 @ 0x003f3e64   (est. sk_op_003f3e64)
 * Ghidra: void FUN_003f3e64(undefined8 *param_1, undefined8, long, undefined8,
 *                           long, char)
 * Record builder: validates a length (aborting if negative and not exempt),
 * then packs a 6-word/byte record into param_1: object, length, an optional
 * value (selected by param_5), param_5 itself, and a flag byte. If param_5 is
 * zero (or the flag is set) the value field is forced to the 'done' marker.
 * Confidence: medium
 * Notes: abort at 0x003f3ecc on a negative length with param_6 != 1. */
static void sk_op_003f3e64(uint64_t *param_1, uint64_t param_2, long param_3,
                           uint64_t param_4, long param_5, char param_6)
{
    char cVar1;
    uint64_t uVar2;

    if (param_3 < 1 && param_6 != '\x01') {
        sk_x_004070cc();
        sk_x_0040677c(0x40);
        sk_x_00406518();
        sk_x_004085a8();
        sk_break(1, 0x3f3ecc);   /* noreturn */
    }
    uVar2 = 0;
    if (param_5 != 0) {
        uVar2 = param_4;
    }
    cVar1 = param_6;
    if (param_5 == 0 || param_6 == '\x01') {
        cVar1 = '\x01';
    }
    param_1[0] = param_2;
    param_1[1] = (uint64_t)param_3;
    if (param_6 != '\x01') {
        param_4 = uVar2;
    }
    param_1[2] = param_4;
    param_1[3] = (uint64_t)param_5;
    *(char *)(param_1 + 4) = cVar1;
}

/* FUN_003f3ecc @ 0x003f3ecc   (est. sk_op_003f3ecc)
 * Ghidra: void FUN_003f3ecc(void)
 * Op continuation (register-fragment heavy): runs a helper, invokes a handler
 * with the pair from FUN_00407484 plus an incoming argument, then runs a
 * sequence of continuation helpers and repacks a record into the frame whose
 * base is extraout_x8 using incoming stack words and a status byte.
 * Confidence: low
 * Notes: in_x4/in_x5/in_stack_* are incoming registers/stack args; unaff_x19/
 *   unaff_x20 are handler pointers; FUN_00356590 re-registers unaff_x30. */
static void sk_op_003f3ecc(void)
{
    cl4_result_t pair;
    uint64_t in_x4 = /* in_x4 */ 0;
    uint64_t in_stack_00000008 = 0;
    uint64_t in_stack_00000010 = 0;
    uint64_t in_stack_00000018 = 0;
    uint64_t in_stack_00000020 = 0;
    uint8_t  in_stack_00000028 = 0;
    uint64_t *extraout_x8 = 0;   /* extraout_x8: frame base */
    uint64_t x19 = /* unaff_x19: handler */ 0;
    uint64_t x20 = /* unaff_x20: handler */ 0;
    uint64_t x30 = /* unaff_x30 */ 0;

    sk_x_003565a8();
    pair = sk_x_00407484();
    ((void (*)(uint64_t, uint64_t, uint64_t))x20)(pair.lo, pair.hi, in_x4);
    sk_x_003504c4();
    ((void (*)(void))x20)();
    sk_x_00351790();
    sk_x_00350738((uint64_t)&in_stack_00000008);
    ((void (*)(void))x19)();
    extraout_x8[1] = in_stack_00000010;
    extraout_x8[0] = in_stack_00000008;
    extraout_x8[3] = in_stack_00000020;
    extraout_x8[2] = in_stack_00000018;
    *(uint8_t *)(extraout_x8 + 4) = in_stack_00000028;
    sk_x_00356590(x30);
}

/* FUN_003f3f50 @ 0x003f3f50   (est. sk_op_003f3f50)
 * Ghidra: void FUN_003f3f50(void)
 * Record-builder op: assembles a capability record from context fields
 * (unaff_x21), formats it through a trace formatter (FUN_001d88fc), packs the
 * tail words/byte into the frame at unaff_x19, and finishes with the record
 * packer FUN_003f3e64.
 * Confidence: low
 * Notes: unaff_x21 is the source context; unaff_x19 is the destination frame;
 *   FUN_001d88fc + FUN_000e15d8 build the formatted record. */
static void sk_op_003f3f50(void)
{
    cl4_result_t pair;
    uint64_t uVar1, uVar2;
    uint64_t *x19 = /* unaff_x19: dest frame */ 0;
    uint8_t *x21 = /* unaff_x21: source context */ 0;
    uint64_t local_88 = 0, uStack_80 = 0;
    uint8_t  local_78 = 0;
    uint64_t local_70 = 0, uStack_68 = 0;
    uint8_t  local_60 = 0;
    uint64_t uStack_5f = 0, uStack_58 = 0;
    uint8_t  local_50 = 0;
    uint64_t auStack_b0[2] = {0, 0};

    sk_x_0035098c();
    uVar1 = sk_x_00351124();
    sk_x_0001a1c8(uVar1, *(uint64_t *)(x21 + 8));
    uStack_68 = *(uint64_t *)(x21 + 0x18);
    local_70 = *(uint64_t *)(x21 + 0x10);
    local_60 = *(uint8_t *)(x21 + 0x20);
    sk_x_004072c0();
    sk_x_0031b37c();
    sk_x_00352efc();
    uVar1 = sk_x_00310d68();
    sk_x_00350798();
    uVar2 = sk_x_0031de7c();
    pair = sk_x_001d88fc(&local_88, (uint64_t)sk_x_00404f60, (uint64_t)auStack_b0,
                         uVar1, 0x674330, uVar2, 0x66d208);
    sk_x_000e15d8(&local_70, pair.lo, pair.hi, local_88, uStack_80, local_78);
    sk_op_003f3e64(0, 0, 0, 0, 0, 0);
    x19[1] = uStack_68;
    x19[0] = local_70;
    x19[3] = uStack_58;
    x19[2] = CONCAT71(uStack_5f, local_60);
    *(uint8_t *)(x19 + 4) = local_50;
}

/* FUN_003f4040 @ 0x003f4040   (est. sk_helper_003f4040)
 * Ghidra: long FUN_003f4040(void)
 * Range-end helper: computes base+length for the object at unaff_x20. If the
 * "done" byte at +0x20 is set, the length is treated as zero. Returns the sum,
 * aborting if the signed addition overflows.
 * Confidence: medium
 * Notes: abort at 0x003f406c on SCARRY8 overflow of *(x20+8)+length. */
static long sk_helper_003f4040(void)
{
    long lVar2;
    uint8_t *x20 = /* unaff_x20 */ 0;

    if (*(uint8_t *)(x20 + 0x20) == '\x01') {
        lVar2 = 0;
    } else {
        lVar2 = *(long *)(x20 + 0x18);
    }
    if (!SCARRY8(*(long *)(x20 + 8), lVar2)) {
        return *(long *)(x20 + 8) + lVar2;
    }
    sk_break(1, 0x3f406c);   /* noreturn */
    return 0;
}

/* FUN_003f406c @ 0x003f406c   (est. sk_op_003f406c)
 * Ghidra: void FUN_003f406c(void)
 * Op continuation: resolves a capability word, formats a descriptor
 * (FUN_00376820), re-resolves a second word, reads a two-word descriptor via
 * the thunk of FUN_0028c754, advances the cursor by a per-entry stride, and
 * copies the range through FUN_001a26e0.
 * Confidence: low
 * Notes: in_x4 is an incoming argument; DAT_004edcd0 (sk_g_004edcd0) is the
 *   descriptor table; extraout_x16/extraout_x8 are the descriptor base/stride
 *   from FUN_003522b8. */
static void sk_op_003f406c(void)
{
    cl4_result_t pair;
    uint64_t uVar1, uVar2;
    uint64_t in_x4 = /* in_x4 */ 0;
    uint64_t extraout_x8 = 0;    /* extraout_x8 */
    uint64_t extraout_x16 = 0;   /* extraout_x16 */
    long lVar3;
    long local_b8 = 0;
    long local_90[2] = {0, 0};
    uint64_t local_80 = 0;

    uVar2 = in_x4;
    uVar1 = sk_x_0034c2e8();
    local_80 = uVar1;
    uVar2 = sk_x_0031de7c(0xff, uVar2);
    pair = sk_x_00376820(&sk_g_004edcd0, uVar2);
    sk_x_00350798(pair.lo, pair.hi, pair.lo);
    uVar2 = sk_x_0031b080();
    sk_x_0028c754(local_90);
    lVar3 = local_90[0];
    if (local_90[0] != 0) {
        cl4_result_t adv;
        sk_x_00408148();
        adv = sk_x_003522b8(&local_b8);
        lVar3 = lVar3 + *(long *)(adv.hi + 0x48) * (long)adv.lo;
    }
    local_80 = uVar1;
    sk_x_0022b584(local_90, uVar2);
    sk_x_00408148();
    sk_x_001a26e0(lVar3, local_90[0] - local_b8, in_x4);
}

/* FUN_003f4164 @ 0x003f4164   (est. sk_helper_003f4164)
 * Ghidra: void FUN_003f4164(long param_1)
 * Helper: resolves a word from param_1+0x10 and passes it (plus the two words
 * at unaff_x20) to FUN_003f41b8. Unless the flag byte at unaff_x20+4 is set,
 * it repeats with the next two words (unaff_x20[2], unaff_x20[3]).
 * Confidence: low
 * Notes: FUN_003f41b8 is an out-of-slice resolver; the byte at +4 gates the
 *   second pass. */
static void sk_helper_003f4164(long param_1)
{
    uint64_t uVar1;
    uint64_t *x20 = /* unaff_x20 */ 0;

    uVar1 = *(uint64_t *)(param_1 + 0x10);
    sk_x_003f41b8(*x20, x20[1], uVar1);
    if (*(char *)(x20 + 4) == '\x01') {
        return;
    }
    sk_x_003f41b8(x20[2], x20[3], uVar1);
}
