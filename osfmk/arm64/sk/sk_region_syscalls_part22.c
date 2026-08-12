/* Recreated from cl4_kernel.raw (cL4 Secure Kernel, arm64e, image base 0) —
 * the cL4 microkernel (GL1). Ground truth: Ghidra FUN_ names + addresses.
 * All names are estimates unless string/header matched.
 * Slice 22: 0x353dc4-0x354b20 syscall/exception-entry region — a table of
 * tiny leaf/accessor helpers plus Swift-runtime-style metadata accessors
 * (type-name tables at 0x4e7ed8, metadata fn pointers, tagged-object ctors).
 * The kernel embeds a Swift runtime: "Bool"/"String"/"Double" type-name
 * strings, a "pointerValue" tagged object, and "representable range" /
 * "Should be overridden" precondition traps. */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "sk_internal.h"
#include "sk_region_syscalls.h"

/* ------------------------------------------------------------------ *
 * Out-of-range cL4 / Swift-runtime helper declarations (their bodies are
 * reconstructed by the range workers that own them).
 * ------------------------------------------------------------------ */
extern void FUN_00027788(void);
extern void FUN_00114330(und8_t);
extern void FUN_00310a74(void);
extern void FUN_000a68f4(void);
extern void FUN_0037233c(und8_t, und8_t, und8_t, und8_t, und8_t, und8_t);
extern void FUN_000026e8(void);
extern void FUN_00310a44(void);
extern void FUN_0031e104(void);
extern void FUN_002b81b4(void);
extern void FUN_002a4b90(und8_t, und8_t, und8_t, und8_t);
extern void FUN_00310a14(void);
extern void FUN_00027754(void);
extern void FUN_00002534(und8_t, und8_t);
extern void FUN_001a89a8(const char *, und8_t, und8_t);

extern und8_t DAT_004f1660;   /* Swift type metadata table */
extern und8_t DAT_004f17e0;   /* Swift type metadata table */
extern und8_t DAT_004f1628;   /* Swift type metadata table */
extern und8_t DAT_004edcec;   /* Swift type metadata table */
extern und8_t DAT_004e8230;   /* Swift type metadata table */
extern und8_t DAT_004e9d58;   /* Swift type metadata table */
extern und8_t DAT_004e7ed8;   /* Swift builtin type-name table (Bool/String/Double) */
extern und8_t DAT_005d3bb9;   /* Swift diagnostic string ("Should be overridden...") */

/* FUN_00353dc4 — word_pair_copy (medium confidence).
 * copies *x20..[1] into *x19..[1]; callee-saved regs, struct copy */
static void FUN_00353dc4(und8_t *dst, const und8_t *src)
{
    /* copy two words (16 bytes) */
    dst[0] = src[0];
    dst[1] = src[1];
}

/* FUN_00353dd0 — swift_metadata_addr (low confidence).
 * returns constant 0x6561d8 (runtime metadata table) */
static und8_t FUN_00353dd0(void)
{
    /* Swift runtime metadata table address */
    return 0x6561d8;
}

/* FUN_00353df0 — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_00353df0(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_00353dfc — frame_word_load (low confidence).
 * unaff_x29 frame-relative load fp-0x78 */
static und8_t FUN_00353dfc(und8_t *fp)
{
    /* caller-frame spill at fp-0x78 */
    return fp[-15];
}

/* FUN_00353e08 — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_00353e08(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_00353e14 — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_00353e14(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_00353e20 — frame_word_load_2 (low confidence).
 * frame-relative load fp-0x90 */
static und8_t FUN_00353e20(und8_t *fp)
{
    /* caller-frame spill at fp-0x90 */
    return fp[-18];
}

/* FUN_00353e2c — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_00353e2c(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_00353e38 — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_00353e38(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_00353e44 — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_00353e44(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_00353e50 — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_00353e50(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_00353e5c — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_00353e5c(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_00353e7c — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_00353e7c(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_00353e88 — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_00353e88(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_00353e94 — frame_word_store (low confidence).
 * frame-relative store fp-0xd8 */
static void FUN_00353e94(und8_t *fp, und8_t value)
{
    /* spill to caller-frame slot fp-0xd8 */
    fp[-27] = value;
}

/* FUN_00353ea0 — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_00353ea0(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_00353eac — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_00353eac(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_00353ecc — frame_word_store_2 (low confidence).
 * frame-relative store fp-0x58 */
static void FUN_00353ecc(und8_t *fp, und8_t value)
{
    /* spill to caller-frame slot fp-0x58 */
    fp[-11] = value;
}

/* FUN_00353ed8 — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_00353ed8(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_00353ee4 — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_00353ee4(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_00353ef0 — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_00353ef0(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_00353efc — call_leaf_00027788 (low confidence).
 * bare call FUN_00027788 */
static void FUN_00353efc(void)
{
    FUN_00027788();
}

/* FUN_00353f14 — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_00353f14(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_00353f20 — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_00353f20(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_00353f2c — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_00353f2c(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_00353f38 — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_00353f38(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_00353f44 — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_00353f44(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_00353f50 — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_00353f50(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_00353f5c — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_00353f5c(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_00353f68 — pack_u128_hi (medium confidence).
 * 128-bit pack into hi half (auVar1._8_8_=0; _0_8_=param; <<0x40) */
static __uint128_t FUN_00353f68(und8_t value)
{
    /* 128-bit result: hi=value, lo=0 */
    return (__uint128_t)value << 64;
}

/* FUN_00353f88 — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_00353f88(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_00353f94 — return_zero_8 (low confidence).
 * returns 0 */
static und8_t FUN_00353f94(void)
{
    return 0;
}

/* FUN_00353fa0 — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_00353fa0(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_00353fac — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_00353fac(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_00353fb8 — dispatch_00114330_4 (low confidence).
 * thunk dispatch arg 4 through FUN_00114330 */
static void FUN_00353fb8(void)
{
    FUN_00114330(4);
}

/* FUN_00353fd4 — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_00353fd4(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_00353ff4 — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_00353ff4(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_00354000 — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_00354000(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_00354010 — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_00354010(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_0035401c — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_0035401c(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_00354028 — frame_word_store_3 (low confidence).
 * frame-relative store fp-0xe0 */
static void FUN_00354028(und8_t *fp, und8_t value)
{
    /* spill to caller-frame slot fp-0xe0 */
    fp[-28] = value;
}

/* FUN_00354034 — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_00354034(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_00354040 — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_00354040(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_0035404c — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_0035404c(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_00354058 — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_00354058(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_00354064 — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_00354064(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_00354070 — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_00354070(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_0035407c — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_0035407c(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_00354088 — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_00354088(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_00354094 — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_00354094(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_003540a0 — frame_word_load_3 (low confidence).
 * frame-relative load fp-0x70 */
static und8_t FUN_003540a0(und8_t *fp)
{
    /* caller-frame spill at fp-0x70 */
    return fp[-14];
}

/* FUN_003540ac — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_003540ac(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_003540c4 — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_003540c4(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_003540d0 — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_003540d0(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_003540dc — frame_word_load_4 (low confidence).
 * frame-relative load fp-0xb0 */
static und8_t FUN_003540dc(und8_t *fp)
{
    /* caller-frame spill at fp-0xb0 */
    return fp[-22];
}

/* FUN_003540e8 — frame_const_store_0x40 (low confidence).
 * frame-relative const store 0x40 */
static void FUN_003540e8(und8_t *fp)
{
    /* store 0x40 to caller-frame slot fp-0x58 */
    fp[-11] = 0x40;
}

/* FUN_003540f4 — swift_obj_init_pointervalue (high confidence).
 * embedded 'pointerValue' string + metadata fn 0x677790; Swift tagged ctor */
static void FUN_003540f4(und8_t *obj, und8_t payload_lo, und8_t payload_hi)
{
    /* Swift tagged-object ctor: copy payload + embed "pointerValue" */
    *(und8_t **)(obj + 0x10) = (und8_t *)payload_lo;
    *(und8_t **)(obj + 0x18) = (und8_t *)payload_hi;
    *(und8_t **)(obj + 0x20) = (und8_t *)0x567265746e696f70; /* "pointerV" */
    *(und8_t **)(obj + 0x28) = (und8_t *)0xec00000065756c61; /* "alue" */
    *(und8_t **)(obj + 0x48) = (und8_t *)0x677790;          /* metadata fn */
}

/* FUN_00354128 — frame_word_store_4 (low confidence).
 * frame-relative store fp-0x120 */
static void FUN_00354128(und8_t *fp, und8_t value)
{
    /* spill to caller-frame slot fp-0x120 */
    fp[-36] = value;
}

/* FUN_00354134 — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_00354134(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_00354140 — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_00354140(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_0035414c — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_0035414c(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_00354168 — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_00354168(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_00354184 — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_00354184(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_003541a0 — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_003541a0(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_003541bc — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_003541bc(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_003541d8 — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_003541d8(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_003541f4 — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_003541f4(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_00354210 — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_00354210(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_0035422c — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_0035422c(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_00354248 — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_00354248(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_00354264 — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_00354264(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_00354270 — frame_const_store_int64max (low confidence).
 * frame-relative const store INT64_MAX */
static void FUN_00354270(und8_t *fp)
{
    /* store INT64_MAX to caller-frame slot fp-0x60 */
    fp[-12] = 0x7fffffffffffffff;
}

/* FUN_0035427c — store_and_call_310a74 (low confidence).
 * const store + bare call FUN_00310a74 */
static void FUN_0035427c(und8_t *fp)
{
    fp[-11] = 0xffffffffffffff80;
    FUN_00310a74();
}

/* FUN_0035428c — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_0035428c(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_003542a8 — reg_word_store (low confidence).
 * store via callee-saved x20 */
static void FUN_003542a8(und8_t *dst, und8_t value)
{
    *dst = value;
}

/* FUN_003542b0 — carry_not (low confidence).
 * inverted carry flag */
static bool FUN_003542b0(bool carry_flag)
{
    /* inverted carry */
    return !carry_flag;
}

/* FUN_003542b8 — return_0xff (low confidence).
 * constant 0xff */
static und8_t FUN_003542b8(void)
{
    return 0xff;
}

/* FUN_003542c4 — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_003542c4(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_003542d0 — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_003542d0(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_003542dc — tagged_ptr_field (medium confidence).
 * mask high tag bits + 0x20 (Swift/obj tagged pointer field) */
static und8_t FUN_003542dc(und8_t ptr)
{
    /* unmask high tag bits, add 0x20 */
    return (ptr & 0xfffffffffffffff) + 0x20;
}

/* FUN_003542e8 — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_003542e8(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_003542f4 — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_003542f4(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_00354300 — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_00354300(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_0035430c — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_0035430c(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_00354318 — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_00354318(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_00354324 — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_00354324(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_00354330 — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_00354330(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_0035433c — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_0035433c(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_00354348 — metadata_slot_init_4f1660 (medium confidence).
 * Swift metadata/isa-slot init with table 0x4f1660 */
static void FUN_00354348(und8_t *obj, und8_t a, und8_t b)
{
    obj[3] = a;
    obj[4] = (und8_t)&DAT_004f1660;
    obj[0] = b;
}

/* FUN_00354364 — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_00354364(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_00354370 — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_00354370(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_0035437c — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_0035437c(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_00354388 — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_00354388(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_00354394 — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_00354394(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_003543a0 — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_003543a0(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_003543ac — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_003543ac(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_003543b8 — frame_word_load_5 (low confidence).
 * frame-relative load fp-0x80 */
static und8_t FUN_003543b8(und8_t *fp)
{
    /* caller-frame spill at fp-0x80 */
    return fp[-16];
}

/* FUN_003543c4 — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_003543c4(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_003543d0 — return_zero_8_2 (low confidence).
 * returns 0 */
static und8_t FUN_003543d0(void)
{
    return 0;
}

/* FUN_003543dc — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_003543dc(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_003543f8 — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_003543f8(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_00354404 — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_00354404(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_00354410 — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_00354410(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_0035441c — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_0035441c(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_00354428 — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_00354428(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_00354440 — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_00354440(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_00354458 — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_00354458(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_00354474 — call_leaf_000a68f4 (low confidence).
 * bare call FUN_000a68f4 */
static void FUN_00354474(void)
{
    FUN_000a68f4();
}

/* FUN_0035448c — dispatch_8arg_37233c (low confidence).
 * argument-forwarding stub through FUN_0037233c (Swift runtime callout) */
static void FUN_0035448c(und8_t *fp, und8_t arg3, und8_t arg4, und8_t arg5, und8_t arg6, und8_t arg7, und8_t arg8)
{
    fp[-17] = arg4;
    fp[-15] = arg5;
    fp[-16] = arg3;
    fp[-14] = fp[3];
    fp[-13] = arg6;
    FUN_0037233c(0, arg7, arg8, fp[2], 0, 0);
}

/* FUN_003544c8 — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_003544c8(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_003544e0 — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_003544e0(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_003544ec — metadata_addr_4edcec (medium confidence).
 * returns metadata table pointer */
static und8_t *FUN_003544ec(void)
{
    return &DAT_004edcec;
}

/* FUN_00354504 — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_00354504(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_00354534 — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_00354534(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_0035454c — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_0035454c(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_00354558 — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_00354558(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_00354570 — frame_word_store_5 (low confidence).
 * frame-relative store fp-0x150 */
static void FUN_00354570(und8_t *fp, und8_t value)
{
    /* spill to caller-frame slot fp-0x150 */
    fp[-42] = value;
}

/* FUN_0035457c — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_0035457c(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_00354588 — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_00354588(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_00354594 — frame_word_load_6 (low confidence).
 * frame-relative load fp-0x88 */
static und8_t FUN_00354594(und8_t *fp)
{
    /* caller-frame spill at fp-0x88 */
    return fp[-17];
}

/* FUN_003545a0 — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_003545a0(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_003545ac — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_003545ac(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_003545b8 — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_003545b8(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_003545d0 — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_003545d0(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_003545e8 — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_003545e8(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_003545f4 — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_003545f4(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_0035460c — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_0035460c(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_00354618 — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_00354618(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_00354624 — call_leaf_000026e8 (low confidence).
 * bare call FUN_000026e8 */
static void FUN_00354624(void)
{
    FUN_000026e8();
}

/* FUN_0035463c — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_0035463c(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_00354648 — frame_word_load_7 (low confidence).
 * frame-relative load fp-0x68 */
static und8_t FUN_00354648(und8_t *fp)
{
    /* caller-frame spill at fp-0x68 */
    return fp[-13];
}

/* FUN_00354654 — ret_sp_8 (low confidence).
 * returns stack pointer +8 (return-address slot) */
static und8_t *FUN_00354654(und8_t *fp)
{
    /* return pointer to caller return-address slot (fp+8) */
    return &fp[1];
}

/* FUN_00354660 — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_00354660(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_0035466c — frame_word_load_8 (low confidence).
 * frame-relative load fp-0x80 */
static und8_t FUN_0035466c(und8_t *fp)
{
    /* caller-frame spill at fp-0x80 */
    return fp[-16];
}

/* FUN_00354678 — metadata_slot_init_4f17e0 (medium confidence).
 * Swift metadata/isa init with table 0x4f17e0 */
static void FUN_00354678(und8_t *obj, und8_t value)
{
    *(und8_t **)(obj + 0x18) = (und8_t *)value;
    *(und8_t **)(obj + 0x20) = &DAT_004f17e0;
}

/* FUN_00354690 — metadata_addr_4e8230 (medium confidence).
 * returns metadata table pointer */
static und8_t *FUN_00354690(void)
{
    return &DAT_004e8230;
}

/* FUN_003546a8 — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_003546a8(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_003546b4 — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_003546b4(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_003546c0 — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_003546c0(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_003546cc — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_003546cc(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_003546e4 — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_003546e4(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_003546fc — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_003546fc(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_00354708 — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_00354708(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_00354714 — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_00354714(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_00354720 — reg_word_store_2 (low confidence).
 * store via callee-saved regs (x21 -> *x19) */
static void FUN_00354720(und8_t *dst, und8_t value)
{
    *dst = value;
}

/* FUN_0035472c — metadata_slot_init_4f1628 (medium confidence).
 * Swift metadata/isa init with table 0x4f1628 */
static void FUN_0035472c(und8_t *obj, und8_t value)
{
    *(und8_t **)(obj + 0x18) = (und8_t *)value;
    *(und8_t **)(obj + 0x20) = &DAT_004f1628;
}

/* FUN_00354744 — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_00354744(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_0035475c — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_0035475c(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_00354774 — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_00354774(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_00354780 — frame_word_load_9 (low confidence).
 * frame-relative load fp-0xa0 */
static und8_t FUN_00354780(und8_t *fp)
{
    /* caller-frame spill at fp-0xa0 */
    return fp[-20];
}

/* FUN_0035478c — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_0035478c(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_00354798 — metadata_addr_4e9d58 (medium confidence).
 * returns metadata table pointer */
static und8_t *FUN_00354798(void)
{
    return &DAT_004e9d58;
}

/* FUN_003547b0 — call_leaf_310a44 (low confidence).
 * bare call FUN_00310a44 */
static void FUN_003547b0(void)
{
    FUN_00310a44();
}

/* FUN_003547c8 — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_003547c8(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_003547d4 — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_003547d4(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_003547ec — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_003547ec(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_003547f8 — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_003547f8(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_00354804 — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_00354804(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_00354810 — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_00354810(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_0035481c — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_0035481c(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_00354828 — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_00354828(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_00354834 — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_00354834(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_00354840 — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_00354840(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_0035484c — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_0035484c(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_00354858 — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_00354858(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_00354864 — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_00354864(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_00354870 — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_00354870(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_00354888 — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_00354888(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_003548a0 — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_003548a0(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_003548ac — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_003548ac(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_003548b8 — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_003548b8(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_003548c4 — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_003548c4(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_003548d0 — pack_u128_hi_2 (medium confidence).
 * 128-bit pack into hi half (auVar1._8_8_=0; _0_8_=x5; <<0x40) */
static __uint128_t FUN_003548d0(und8_t value)
{
    /* 128-bit result: hi=value, lo=0 */
    return (__uint128_t)value << 64;
}

/* FUN_003548dc — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_003548dc(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_003548e8 — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_003548e8(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_003548f4 — struct_copy_5 (medium confidence).
 * struct field copy incl nested pointer (5-word struct) */
static void FUN_003548f4(und8_t *dst, und8_t *src, und8_t *owner)
{
    /* copy 5-word struct, record src link */
    *owner = (und8_t)dst;
    dst[5] = (und8_t)src;
    dst[6] = src[0];
    dst[0] = src[0];
    dst[1] = src[1];
    dst[3] = src[3];
    dst[2] = src[2];
    dst[4] = src[4];
}

/* FUN_00354924 — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_00354924(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_00354930 — call_leaf_31e104 (low confidence).
 * bare call FUN_0031e104 */
static void FUN_00354930(void)
{
    FUN_0031e104();
}

/* FUN_00354948 — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_00354948(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_00354954 — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_00354954(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_00354960 — byte_merge (medium confidence).
 * replace low byte with in_w8 low byte */
static uint32_t FUN_00354960(uint32_t value, uint32_t low_byte)
{
    /* replace low byte */
    return (value & 0xffffff00) | (low_byte & 0xff);
}

/* FUN_00354968 — call_leaf_2b81b4 (low confidence).
 * bare call FUN_002b81b4 */
static void FUN_00354968(void)
{
    FUN_002b81b4();
}

/* FUN_00354988 — triple_call_2a4b90 (low confidence).
 * forwarding stub FUN_002a4b90(a,c,c,1) */
static void FUN_00354988(und8_t a, und8_t b, und8_t c)
{
    FUN_002a4b90(a, c, c, 1);
}

/* FUN_00354998 — zero_flag_not (low confidence).
 * inverted zero flag */
static bool FUN_00354998(bool zero_flag)
{
    /* inverted zero flag */
    return !zero_flag;
}

/* FUN_003549a8 — call_leaf_310a14 (low confidence).
 * bare call FUN_00310a14 */
static void FUN_003549a8(void)
{
    FUN_00310a14();
}

/* FUN_003549c0 — call_leaf_00027754 (low confidence).
 * bare call FUN_00027754 */
static void FUN_003549c0(void)
{
    FUN_00027754();
}

/* FUN_003549d8 — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_003549d8(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_003549e4 — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_003549e4(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_00354a00 — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_00354a00(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_00354a0c — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_00354a0c(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_00354a28 — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_00354a28(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_00354a34 — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_00354a34(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_00354a4c — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_00354a4c(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_00354a58 — swift_runtime_boot (high confidence).
 * 0x4e7ed8 holds Bool/String/Double type names -> Swift runtime type-table registration */
static void FUN_00354a58(void)
{
    /* register Swift builtin type-name table at 0x4e7ed8 */
    FUN_00002534(0x6560f0, (und8_t)&DAT_004e7ed8);
}

/* FUN_00354a6c — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_00354a6c(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_00354a78 — frame_word_load_a (low confidence).
 * frame-relative load fp-0x98 */
static und8_t FUN_00354a78(und8_t *fp)
{
    /* caller-frame spill at fp-0x98 */
    return fp[-19];
}

/* FUN_00354a84 — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_00354a84(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_00354ab0 — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_00354ab0(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_00354abc — frame_word_load_b (low confidence).
 * frame-relative load fp-0xb8 */
static und8_t FUN_00354abc(und8_t *fp)
{
    /* caller-frame spill at fp-0xb8 */
    return fp[-23];
}

/* FUN_00354ac8 — frame_word_store_6 (low confidence).
 * frame-relative store fp-0x148 */
static void FUN_00354ac8(und8_t *fp, und8_t value)
{
    /* spill to caller-frame slot fp-0x148 */
    fp[-41] = value;
}

/* FUN_00354ad4 — swift_precond_out_of_range (high confidence).
 * Swift 'representable range' fatalError/precondition — integer overflow trap */
static void FUN_00354ad4(void)
{
    /* Swift integer-conversion precondition failure */
    FUN_001a89a8("because it is outside the representable range", 0x2e, 1);
}

/* FUN_00354ae8 — swift_precond_abstract (high confidence).
 * 0x5d3bb9 'Should be overridden...' -> Swift abstract-method trap */
static void FUN_00354ae8(void)
{
    /* Swift generic/abstract-method precondition failure */
    FUN_001a89a8((const char *)&DAT_005d3bb9, 2, 1);
}

/* FUN_00354afc — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_00354afc(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_00354b08 — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_00354b08(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_00354b14 — empty leaf stub. No modeled body: the decompiler collapses
 * callee-saved-register traffic (unaff_x19..x29) to an empty return. */
void FUN_00354b14(void)
{
    /* no-op leaf stub */
    return;
}

/* FUN_00354b20 — return_zero_8_3 (low confidence).
 * returns 0 */
static und8_t FUN_00354b20(void)
{
    return 0;
}

