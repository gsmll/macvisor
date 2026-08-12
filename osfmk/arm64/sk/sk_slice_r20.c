/* Recreated from cl4_kernel.raw (cL4 microkernel, arm64e, image base 0).
 * Ground truth: Ghidra FUN_ names + addresses. Names use cL4/seL4 vocabulary; estimates unless matched.
 *
 * Slice R20: 0x00462ba8-0x00463590 (120 functions). A dense run of tiny cL4
 * object/string-service leaf routines. Most are one-line Swift-runtime string
 * tag/compare dispatch wrappers that forward into the shared runtime helpers
 * sk_swift_str_cmp_ci (002a0cf8) / sk_swift_str_flush (0029fa0c) / the UTF-16
 * view advance loop (002b4120) / the Swift string emit helper (002a4ab4), plus
 * a large number of true no-ops and small fixed-offset field copy/read leaves.
 *
 * Many of these functions were disassembled with the callee's frame pointer in
 * the unaff_xNN / in_stack registers because they are tail helpers that read
 * the caller's saved message words off the stack (the cL4 message-passing-on-
 * stack idiom). Where the decompiler recovered only register artifacts the
 * signature is reconstructed with a best-effort context pointer and marked
 * confidence low; the exact offsets are preserved.
 *
 * Confidence: low-medium (Swift-runtime string/object tag glue; no
 * string/header matches in this slice). */
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include "sk_internal.h"

/* 128-bit word-pair used by the 16-byte-return runtime helpers. */
typedef struct sk_u128 { word_t lo; word_t hi; } sk_u128_t;

/* ---- shared runtime helpers referenced by this slice (all defined elsewhere
 * in the cL4 tree; FUN_ address preserved in the trailing comment) ---- */
extern word_t sk_swift_str_cmp_ci();                              /* 002a0cf8: Swift ci string compare (variadic here) */
extern void   sk_swift_str_flush();                               /* 0029fa0c: Swift string buffer flush (variadic here) */
extern void   sk_swift_string_utf16_view_advance_loop_c();        /* 002b4120: UTF-16 view advance loop (variadic here) */
extern void   sk_rt_002a4ab4();                                   /* 002a4ab4: Swift string emit/append (variadic here) */
extern void   sk_boot_strmap(unsigned long *name, long *def);     /* 00002534 */
extern uint64_t sk_refcount_acquire_c(uint64_t obj);              /* 0036b270 */
extern void   sk_rt_003a25d4();                                   /* 003a25d4 (claimed/deferred elsewhere) */
extern void   fn_0064e030();                                      /* FUN_0064e030 (code target passed as data) */
extern void   fn_0064e890();                                      /* FUN_0064e890 (code target passed as data) */
extern unsigned char DAT_004be900[];                              /* &DAT_004be900 */
extern unsigned char DAT_004f1980[];                              /* &DAT_004f1980 */

/*--------------------------------------------------------------------*/
/* FUN_00462ba8 @ 0x00462ba8
 * Ghidra: void FUN_00462ba8(undefined8 p1,undefined8 p2,undefined8 p3,undefined8 p4)
 * Thin forwarder into the UTF-16 view advance loop, passing the two leading
 * arguments twice (loop bounds + scratch) along with two trailing words.
 * Confidence: low
 * Notes: tail call FUN_002b4120(p1,p2,p1,p2,p3,p4). */
void sk_cmp_462ba8(word_t p1, word_t p2, word_t p3, word_t p4)
{
    sk_swift_string_utf16_view_advance_loop_c(p1, p2, p1, p2, p3, p4);
}

/*--------------------------------------------------------------------*/
/* FUN_00462bc0 @ 0x00462bc0
 * Ghidra: void FUN_00462bc0(void)
 * Compares the fixed tagged Swift-string word 0xd000000000000010 against the
 * (recovered) current string word via sk_swift_str_cmp_ci.
 * Confidence: low
 * Notes: calls FUN_002a0cf8(0xd000000000000010). */
void sk_cmp_462bc0(void)
{
    sk_swift_str_cmp_ci(0xd000000000000010);
}

/*--------------------------------------------------------------------*/
/* FUN_00462bd8 @ 0x00462bd8
 * Ghidra: void FUN_00462bd8(undefined8 p1,long src)
 * Copies the four 8-byte words at src+0x70..0x88 into four caller-frame stack
 * slots at -0x88..-0x70 (message/scratch spill for a following dispatch).
 * Confidence: low
 * Notes: register-artifact function (writes to unaff_x29 frame slots). */
void sk_cmp_462bd8(word_t p1, word_t *src)
{
    word_t v0 = *(word_t *)((char *)src + 0x78);
    *(word_t *)((char *)src - 0x88) = *(word_t *)((char *)src + 0x70);
    *(word_t *)((char *)src - 0x80) = v0;
    v0 = *(word_t *)((char *)src + 0x88);
    *(word_t *)((char *)src - 0x78) = *(word_t *)((char *)src + 0x80);
    *(word_t *)((char *)src - 0x70) = v0;
}

/*--------------------------------------------------------------------*/
/* FUN_00462c04 @ 0x00462c04
 * Ghidra: void FUN_00462c04(void)
 * Zeroes the four 8-byte words at ctx+0x28..0x40.
 * Confidence: low
 * Notes: register-artifact (in_x9 = context pointer). */
void sk_cmp_462c04(void *ctx)
{
    *(word_t *)((char *)ctx + 0x28) = 0;
    *(word_t *)((char *)ctx + 0x40) = 0;
    *(word_t *)((char *)ctx + 0x30) = 0;
    *(word_t *)((char *)ctx + 0x38) = 0;
}

/*--------------------------------------------------------------------*/
/* FUN_00462c18 @ 0x00462c18
 * Ghidra: void FUN_00462c18(void)
 * No-argument dispatch into the Swift ci string compare helper.
 * Confidence: low
 * Notes: calls FUN_002a0cf8() with no recovered args. */
void sk_cmp_462c18(void)
{
    sk_swift_str_cmp_ci();
}

/*--------------------------------------------------------------------*/
/* FUN_00462c30 @ 0x00462c30
 * Ghidra: void FUN_00462c30(void)
 * No-argument dispatch into the Swift ci string compare helper.
 * Confidence: low
 * Notes: calls FUN_002a0cf8() with no recovered args. */
void sk_cmp_462c30(void)
{
    sk_swift_str_cmp_ci();
}

/*--------------------------------------------------------------------*/
/* FUN_00462c48 @ 0x00462c48
 * Ghidra: void FUN_00462c48(void)
 * Empty stub / placeholder in the runtime glue table.
 * Confidence: low */
void sk_noop_462c48(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00462c58 @ 0x00462c58
 * Ghidra: void FUN_00462c58(void)
 * Empty stub / placeholder in the runtime glue table.
 * Confidence: low */
void sk_noop_462c58(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00462c6c @ 0x00462c6c
 * Ghidra: void FUN_00462c6c(void)
 * Empty stub / placeholder in the runtime glue table.
 * Confidence: low */
void sk_noop_462c6c(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00462c7c @ 0x00462c7c
 * Ghidra: void FUN_00462c7c(void)
 * Empty stub / placeholder in the runtime glue table.
 * Confidence: low */
void sk_noop_462c7c(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00462c98 @ 0x00462c98
 * Ghidra: void FUN_00462c98(void)
 * Empty stub / placeholder in the runtime glue table.
 * Confidence: low */
void sk_noop_462c98(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00462cb0 @ 0x00462cb0
 * Ghidra: void FUN_00462cb0(void)
 * Empty stub / placeholder in the runtime glue table.
 * Confidence: low */
void sk_noop_462cb0(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00462cc0 @ 0x00462cc0
 * Ghidra: void FUN_00462cc0(undefined8 p1)
 * Compares p1 against the fixed tagged word 0xe400000000000000.
 * Confidence: low
 * Notes: calls FUN_002a0cf8(p1,0xe400000000000000). */
void sk_cmp_462cc0(word_t p1)
{
    sk_swift_str_cmp_ci(p1, 0xe400000000000000);
}

/*--------------------------------------------------------------------*/
/* FUN_00462cd4 @ 0x00462cd4
 * Ghidra: undefined8 FUN_00462cd4(void)
 * Returns the word at ([[ctx+0x50]]+0x10): double-indirected field read.
 * Confidence: low
 * Notes: register-artifact (unaff_x19). */
word_t sk_rt_462cd4(void *ctx)
{
    return *(word_t *)(*(word_t **)((char *)ctx + 0x50) + 0x10);
}

/*--------------------------------------------------------------------*/
/* FUN_00462ce8 @ 0x00462ce8
 * Ghidra: undefined1[16] FUN_00462ce8(void)
 * Returns the 16-byte pair {lo = caller-stack word [0x10], hi = 0x657b08}.
 * Confidence: low
 * Notes: register-artifact (in_stack_00000230); hi is the tagged literal. */
sk_u128_t sk_rt_462ce8(word_t caller_word)
{
    sk_u128_t r;
    r.lo = caller_word;
    r.hi = 0x657b08;
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_00462d0c @ 0x00462d0c
 * Ghidra: void FUN_00462d0c(void)
 * Empty stub / placeholder in the runtime glue table.
 * Confidence: low */
void sk_noop_462d0c(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00462d20 @ 0x00462d20
 * Ghidra: undefined1[16] FUN_00462d20(void)
 * Returns the 128-bit constant 1 << 0x40 == {lo:0, hi:1}.
 * Confidence: medium
 * Notes: ZEXT816(1) << 0x40. */
sk_u128_t sk_rt_462d20(void)
{
    sk_u128_t r;
    r.lo = 0;
    r.hi = 1;
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_00462d34 @ 0x00462d34
 * Ghidra: void FUN_00462d34(void)
 * Empty stub / placeholder in the runtime glue table.
 * Confidence: low */
void sk_noop_462d34(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00462d48 @ 0x00462d48
 * Ghidra: void FUN_00462d48(void)
 * Empty stub / placeholder in the runtime glue table.
 * Confidence: low */
void sk_noop_462d48(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00462d5c @ 0x00462d5c
 * Ghidra: void FUN_00462d5c(void)
 * Empty stub / placeholder in the runtime glue table.
 * Confidence: low */
void sk_noop_462d5c(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00462d70 @ 0x00462d70
 * Ghidra: void FUN_00462d70(void)
 * No-argument dispatch into the Swift ci string compare helper.
 * Confidence: low
 * Notes: calls FUN_002a0cf8() with no recovered args. */
void sk_cmp_462d70(void)
{
    sk_swift_str_cmp_ci();
}

/*--------------------------------------------------------------------*/
/* FUN_00462d88 @ 0x00462d88
 * Ghidra: void FUN_00462d88(void)
 * Empty stub / placeholder in the runtime glue table.
 * Confidence: low */
void sk_noop_462d88(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00462d98 @ 0x00462d98
 * Ghidra: void FUN_00462d98(void)
 * Empty stub / placeholder in the runtime glue table.
 * Confidence: low */
void sk_noop_462d98(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00462da8 @ 0x00462da8
 * Ghidra: void FUN_00462da8(undefined8 p1)
 * Compares p1 against the fixed tagged word 0xe700000000000000.
 * Confidence: low
 * Notes: calls FUN_002a0cf8(p1,0xe700000000000000). */
void sk_cmp_462da8(word_t p1)
{
    sk_swift_str_cmp_ci(p1, 0xe700000000000000);
}

/*--------------------------------------------------------------------*/
/* FUN_00462dbc @ 0x00462dbc
 * Ghidra: void FUN_00462dbc(undefined8 p1)
 * Compares p1 against the fixed tagged word 0xe600000000000000.
 * Confidence: low
 * Notes: calls FUN_002a0cf8(p1,0xe600000000000000). */
void sk_cmp_462dbc(word_t p1)
{
    sk_swift_str_cmp_ci(p1, 0xe600000000000000);
}

/*--------------------------------------------------------------------*/
/* FUN_00462dd0 @ 0x00462dd0
 * Ghidra: void FUN_00462dd0(undefined8 p1)
 * Compares p1 against the fixed tagged word 0xe500000000000000.
 * Confidence: low
 * Notes: calls FUN_002a0cf8(p1,0xe500000000000000). */
void sk_cmp_462dd0(word_t p1)
{
    sk_swift_str_cmp_ci(p1, 0xe500000000000000);
}

/*--------------------------------------------------------------------*/
/* FUN_00462de4 @ 0x00462de4
 * Ghidra: void FUN_00462de4(undefined8 p1)
 * Compares p1 against the fixed tagged word 0xe800000000000000.
 * Confidence: low
 * Notes: calls FUN_002a0cf8(p1,0xe800000000000000). */
void sk_cmp_462de4(word_t p1)
{
    sk_swift_str_cmp_ci(p1, 0xe800000000000000);
}

/*--------------------------------------------------------------------*/
/* FUN_00462df8 @ 0x00462df8
 * Ghidra: void FUN_00462df8(void)
 * No-argument dispatch into the Swift ci string compare helper.
 * Confidence: low
 * Notes: calls FUN_002a0cf8() with no recovered args. */
void sk_cmp_462df8(void)
{
    sk_swift_str_cmp_ci();
}

/*--------------------------------------------------------------------*/
/* FUN_00462e0c @ 0x00462e0c
 * Ghidra: void FUN_00462e0c(void)
 * Empty stub / placeholder in the runtime glue table.
 * Confidence: low */
void sk_noop_462e0c(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00462e1c @ 0x00462e1c
 * Ghidra: void FUN_00462e1c(undefined8 p1)
 * Compares p1 against the fixed tagged word 0xe200000000000000.
 * Confidence: low
 * Notes: calls FUN_002a0cf8(p1,0xe200000000000000). */
void sk_cmp_462e1c(word_t p1)
{
    sk_swift_str_cmp_ci(p1, 0xe200000000000000);
}

/*--------------------------------------------------------------------*/
/* FUN_00462e30 @ 0x00462e30
 * Ghidra: void FUN_00462e30(ulong p1)
 * Compares the low 48 bits of p1 OR 0xd000000000000000 (a masked/tagged
 * descriptor) via the compare helper.
 * Confidence: low
 * Notes: calls FUN_002a0cf8((p1 & 0xffffffffffff) | 0xd000000000000000). */
void sk_cmp_462e30(word_t p1)
{
    sk_swift_str_cmp_ci((p1 & 0xffffffffffff) | 0xd000000000000000);
}

/*--------------------------------------------------------------------*/
/* FUN_00462e44 @ 0x00462e44
 * Ghidra: void FUN_00462e44(void)
 * Empty stub / placeholder in the runtime glue table.
 * Confidence: low */
void sk_noop_462e44(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00462e54 @ 0x00462e54
 * Ghidra: undefined8 FUN_00462e54(undefined8 *p1)
 * Returns the first 8-byte word of the pointed-to object.
 * Confidence: medium */
word_t sk_rt_462e54(word_t *p1)
{
    return *p1;
}

/*--------------------------------------------------------------------*/
/* FUN_00462e74 @ 0x00462e74
 * Ghidra: void FUN_00462e74(void)
 * Empty stub / placeholder in the runtime glue table.
 * Confidence: low */
void sk_noop_462e74(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00462e88 @ 0x00462e88
 * Ghidra: void FUN_00462e88(void)
 * Empty stub / placeholder in the runtime glue table.
 * Confidence: low */
void sk_noop_462e88(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00462e9c @ 0x00462e9c
 * Ghidra: void FUN_00462e9c(void)
 * Empty stub / placeholder in the runtime glue table.
 * Confidence: low */
void sk_noop_462e9c(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00462eac @ 0x00462eac
 * Ghidra: void FUN_00462eac(void)
 * Empty stub / placeholder in the runtime glue table.
 * Confidence: low */
void sk_noop_462eac(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00462ec0 @ 0x00462ec0
 * Ghidra: void FUN_00462ec0(undefined8 p1)
 * Compares p1 against the fixed tagged word 0xea00000000006e61.
 * Confidence: low
 * Notes: calls FUN_002a0cf8(p1,0xea00000000006e61). */
void sk_cmp_462ec0(word_t p1)
{
    sk_swift_str_cmp_ci(p1, 0xea00000000006e61);
}

/*--------------------------------------------------------------------*/
/* FUN_00462ed8 @ 0x00462ed8
 * Ghidra: void FUN_00462ed8(void)
 * Empty stub / placeholder in the runtime glue table.
 * Confidence: low */
void sk_noop_462ed8(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00462ee8 @ 0x00462ee8
 * Ghidra: void FUN_00462ee8(void)
 * Empty stub / placeholder in the runtime glue table.
 * Confidence: low */
void sk_noop_462ee8(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00462ef8 @ 0x00462ef8
 * Ghidra: void FUN_00462ef8(undefined8 p1)
 * Compares p1 against the fixed tagged word 0xe300000000000000.
 * Confidence: low
 * Notes: calls FUN_002a0cf8(p1,0xe300000000000000). */
void sk_cmp_462ef8(word_t p1)
{
    sk_swift_str_cmp_ci(p1, 0xe300000000000000);
}

/*--------------------------------------------------------------------*/
/* FUN_00462f0c @ 0x00462f0c
 * Ghidra: void FUN_00462f0c(void)
 * Empty stub / placeholder in the runtime glue table.
 * Confidence: low */
void sk_noop_462f0c(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00462f24 @ 0x00462f24
 * Ghidra: void FUN_00462f24(void)
 * Empty stub / placeholder in the runtime glue table.
 * Confidence: low */
void sk_noop_462f24(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00462f3c @ 0x00462f3c
 * Ghidra: undefined1[16] FUN_00462f3c(void)
 * Returns the constant 16-byte pair {lo:0x29, hi:0xe100000000000000}.
 * Confidence: medium */
sk_u128_t sk_rt_462f3c(void)
{
    sk_u128_t r;
    r.lo = 0x29;
    r.hi = 0xe100000000000000;
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_00462f4c @ 0x00462f4c
 * Ghidra: void FUN_00462f4c(void)
 * Empty stub / placeholder in the runtime glue table.
 * Confidence: low */
void sk_noop_462f4c(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00462f5c @ 0x00462f5c
 * Ghidra: void FUN_00462f5c(void)
 * Empty stub / placeholder in the runtime glue table.
 * Confidence: low */
void sk_noop_462f5c(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00462f6c @ 0x00462f6c
 * Ghidra: long FUN_00462f6c(void)
 * Stores v into base+0x10 and returns base + a*b + 0x20 (element-scaled tail
 * pointer).
 * Confidence: low
 * Notes: register-artifact (unaff_x22/x25/x27/x28). */
long sk_rt_462f6c(word_t *base, word_t v, word_t a, word_t b)
{
    *(word_t *)((char *)base + 0x10) = v;
    return (long)base + (long)(a * b) + 0x20;
}

/*--------------------------------------------------------------------*/
/* FUN_00462f7c @ 0x00462f7c
 * Ghidra: void FUN_00462f7c(void)
 * Empty stub / placeholder in the runtime glue table.
 * Confidence: low */
void sk_noop_462f7c(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00462f8c @ 0x00462f8c
 * Ghidra: void FUN_00462f8c(void)
 * Copies the two words at src+0xa0/0xa8 into dst+0x18/0x20, then lays a
 * two-word message {0, 0xe000000000000000} on the stack and dispatches the
 * Swift string emit helper with code 0x1d.
 * Confidence: low
 * Notes: register-artifact (unaff_x21/x23); calls FUN_002a4ab4(0x1d). */
void sk_cmp_462f8c(word_t *src, word_t *dst)
{
    word_t v = *(word_t *)((char *)src + 0xa0);
    *(word_t *)((char *)dst + 0x20) = *(word_t *)((char *)src + 0xa8);
    *(word_t *)((char *)dst + 0x18) = v;
    word_t msg[2] = { 0, 0xe000000000000000 };
    (void)msg;                       /* read by the dispatched callee from the frame */
    sk_rt_002a4ab4(0x1d);
}

/*--------------------------------------------------------------------*/
/* FUN_00462fac @ 0x00462fac
 * Ghidra: void FUN_00462fac(void)
 * Empty stub / placeholder in the runtime glue table.
 * Confidence: low */
void sk_noop_462fac(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00462fbc @ 0x00462fbc
 * Ghidra: void FUN_00462fbc(void)
 * Empty stub / placeholder in the runtime glue table.
 * Confidence: low */
void sk_noop_462fbc(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00462fd4 @ 0x00462fd4
 * Ghidra: void FUN_00462fd4(void)
 * Empty stub / placeholder in the runtime glue table.
 * Confidence: low */
void sk_noop_462fd4(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00462fec @ 0x00462fec
 * Ghidra: void FUN_00462fec(void)
 * Stores the eight recovered register words into dst[0..7] (object spill).
 * Confidence: low
 * Notes: register-artifact (unaff_x19..x28). */
void sk_rt_462fec(word_t *dst, word_t v0, word_t v1, word_t v2, word_t v3,
                  word_t v4, word_t v5, word_t v6, word_t v7)
{
    dst[0] = v0;
    dst[1] = v1;
    dst[2] = v2;
    dst[3] = v3;
    dst[4] = v4;
    dst[5] = v5;
    dst[6] = v6;
    dst[7] = v7;
}

/*--------------------------------------------------------------------*/
/* FUN_00463000 @ 0x00463000
 * Ghidra: undefined1[16] FUN_00463000(ulong p1)
 * Returns the 16-byte pair {lo:0xd00000000000001b, hi:p1|0x8000000000000000}.
 * Confidence: low */
sk_u128_t sk_rt_463000(word_t p1)
{
    sk_u128_t r;
    r.lo = 0xd00000000000001b;
    r.hi = p1 | 0x8000000000000000;
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_00463014 @ 0x00463014
 * Ghidra: void FUN_00463014(void)
 * Empty stub / placeholder in the runtime glue table.
 * Confidence: low */
void sk_noop_463014(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00463028 @ 0x00463028
 * Ghidra: undefined1[16] FUN_00463028(void)
 * Returns the 16-byte value at ctx+0x40.
 * Confidence: low
 * Notes: register-artifact (unaff_x19). */
sk_u128_t sk_rt_463028(void *ctx)
{
    return *(sk_u128_t *)((char *)ctx + 0x40);
}

/*--------------------------------------------------------------------*/
/* FUN_0046303c @ 0x0046303c
 * Ghidra: undefined1[16] FUN_0046303c(void)
 * Saves dst[0]; then overwrites dst[0] with {v0,v1}, dst[1] with {v2,v3},
 * dst[2]'s low byte with b, and returns the saved dst[0].
 * Confidence: low
 * Notes: register-artifact (unaff_x20/x21..x24/w25). */
sk_u128_t sk_rt_46303c(sk_u128_t *dst, word_t v0, word_t v1, word_t v2,
                       word_t v3, uint8_t b)
{
    sk_u128_t old = dst[0];
    dst[0].lo = v0;
    dst[0].hi = v1;
    dst[1].lo = v2;
    dst[1].hi = v3;
    dst[2].lo = (dst[2].lo & ~(word_t)0xff) | (word_t)b;
    return old;
}

/*--------------------------------------------------------------------*/
/* FUN_00463058 @ 0x00463058
 * Ghidra: void FUN_00463058(void)
 * Empty stub / placeholder in the runtime glue table.
 * Confidence: low */
void sk_noop_463058(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_0046306c @ 0x0046306c
 * Ghidra: void FUN_0046306c(undefined8 *dst,undefined8 *src)
 * Copies the two 8-byte words src[0],src[1] into dst[0],dst[1].
 * Confidence: medium */
void sk_rt_46306c(word_t *dst, word_t *src)
{
    word_t v = src[0];
    dst[1] = src[1];
    dst[0] = v;
}

/*--------------------------------------------------------------------*/
/* FUN_00463080 @ 0x00463080
 * Ghidra: undefined1[16] FUN_00463080(void)
 * Returns the 16-byte value pointed to by ctx.
 * Confidence: low
 * Notes: register-artifact (unaff_x19). */
sk_u128_t sk_rt_463080(void *ctx)
{
    return *(sk_u128_t *)ctx;
}

/*--------------------------------------------------------------------*/
/* FUN_00463094 @ 0x00463094
 * Ghidra: void FUN_00463094(void)
 * Empty stub / placeholder in the runtime glue table.
 * Confidence: low */
void sk_noop_463094(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_004630b0 @ 0x004630b0
 * Ghidra: void FUN_004630b0(void)
 * Empty stub / placeholder in the runtime glue table.
 * Confidence: low */
void sk_noop_4630b0(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_004630c4 @ 0x004630c4
 * Ghidra: void FUN_004630c4(void)
 * Empty stub / placeholder in the runtime glue table.
 * Confidence: low */
void sk_noop_4630c4(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_004630d8 @ 0x004630d8
 * Ghidra: void FUN_004630d8(void)
 * Empty stub / placeholder in the runtime glue table.
 * Confidence: low */
void sk_noop_4630d8(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_004630f4 @ 0x004630f4
 * Ghidra: void FUN_004630f4(undefined8 p1,ulong p2)
 * Compares p1 against the low-48-bits-masked p2 OR 0xeb00000000000000.
 * Confidence: low
 * Notes: calls FUN_002a0cf8(p1,(p2 & 0xffffffffffff) | 0xeb00000000000000). */
void sk_cmp_4630f4(word_t p1, word_t p2)
{
    sk_swift_str_cmp_ci(p1, (p2 & 0xffffffffffff) | 0xeb00000000000000);
}

/*--------------------------------------------------------------------*/
/* FUN_00463108 @ 0x00463108
 * Ghidra: void FUN_00463108(void)
 * Compares ctx+2 via the compare helper.
 * Confidence: low
 * Notes: register-artifact (unaff_x28); calls FUN_002a0cf8(ctx+2). */
void sk_cmp_463108(word_t ctx)
{
    sk_swift_str_cmp_ci(ctx + 2);
}

/*--------------------------------------------------------------------*/
/* FUN_0046311c @ 0x0046311c
 * Ghidra: void FUN_0046311c(undefined8 p1,ulong p2)
 * Compares p1 against the low-48-bits-masked p2 OR 0xea00000000000000.
 * Confidence: low
 * Notes: calls FUN_002a0cf8(p1,(p2 & 0xffffffffffff) | 0xea00000000000000). */
void sk_cmp_46311c(word_t p1, word_t p2)
{
    sk_swift_str_cmp_ci(p1, (p2 & 0xffffffffffff) | 0xea00000000000000);
}

/*--------------------------------------------------------------------*/
/* FUN_00463130 @ 0x00463130
 * Ghidra: void FUN_00463130(undefined8 p1)
 * Compares p1 against the fixed tagged word 0xe100000000000000.
 * Confidence: low
 * Notes: calls FUN_002a0cf8(p1,0xe100000000000000). */
void sk_cmp_463130(word_t p1)
{
    sk_swift_str_cmp_ci(p1, 0xe100000000000000);
}

/*--------------------------------------------------------------------*/
/* FUN_00463144 @ 0x00463144
 * Ghidra: void FUN_00463144(void)
 * Empty stub / placeholder in the runtime glue table.
 * Confidence: low */
void sk_noop_463144(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00463154 @ 0x00463154
 * Ghidra: undefined1[16] FUN_00463154(undefined1 (*dst)[16],undefined8 *src)
 * Saves dst[0]; then packs dst[0]={src[0],src[1]}, dst[1]={src[2],src[3]},
 * dst[2]'s low byte = low byte of src[4]; returns the saved dst[0].
 * Confidence: low */
sk_u128_t sk_rt_463154(sk_u128_t *dst, word_t *src)
{
    sk_u128_t old = dst[0];
    dst[0].lo = src[0];
    dst[0].hi = src[1];
    dst[1].lo = src[2];
    dst[1].hi = src[3];
    dst[2].lo = (dst[2].lo & ~(word_t)0xff) | ((word_t)src[4] & 0xff);
    return old;
}

/*--------------------------------------------------------------------*/
/* FUN_00463180 @ 0x00463180
 * Ghidra: void FUN_00463180(void)
 * No-argument dispatch into the Swift ci string compare helper.
 * Confidence: low
 * Notes: calls FUN_002a0cf8() with no recovered args. */
void sk_cmp_463180(void)
{
    sk_swift_str_cmp_ci();
}

/*--------------------------------------------------------------------*/
/* FUN_00463194 @ 0x00463194
 * Ghidra: void FUN_00463194(void)
 * No-argument dispatch into the Swift string flush helper.
 * Confidence: low
 * Notes: calls FUN_0029fa0c(). */
void sk_cmp_463194(void)
{
    sk_swift_str_flush();
}

/*--------------------------------------------------------------------*/
/* FUN_004631a8 @ 0x004631a8
 * Ghidra: void FUN_004631a8(void)
 * Flushes the Swift string buffer passing the four words recovered from the
 * object register (ctx[2],ctx[3],ctx[0],ctx[1]).
 * Confidence: low
 * Notes: register-artifact (unaff_x19); calls FUN_0029fa0c(4 args). */
void sk_cmp_4631a8(word_t *ctx)
{
    sk_swift_str_flush(ctx[2], ctx[3], ctx[0], ctx[1]);
}

/*--------------------------------------------------------------------*/
/* FUN_004631bc @ 0x004631bc
 * Ghidra: void FUN_004631bc(void)
 * Compares ctx+1 via the compare helper.
 * Confidence: low
 * Notes: register-artifact (unaff_x28); calls FUN_002a0cf8(ctx+1). */
void sk_cmp_4631bc(word_t ctx)
{
    sk_swift_str_cmp_ci(ctx + 1);
}

/*--------------------------------------------------------------------*/
/* FUN_004631d0 @ 0x004631d0
 * Ghidra: void FUN_004631d0(void)
 * Compares ctx+3 via the compare helper.
 * Confidence: low
 * Notes: register-artifact (unaff_x28); calls FUN_002a0cf8(ctx+3). */
void sk_cmp_4631d0(word_t ctx)
{
    sk_swift_str_cmp_ci(ctx + 3);
}

/*--------------------------------------------------------------------*/
/* FUN_004631e4 @ 0x004631e4
 * Ghidra: void FUN_004631e4(undefined8 p1)
 * Compares p1 against the fixed tagged word 0xe900000000000063.
 * Confidence: low
 * Notes: calls FUN_002a0cf8(p1,0xe900000000000063). */
void sk_cmp_4631e4(word_t p1)
{
    sk_swift_str_cmp_ci(p1, 0xe900000000000063);
}

/*--------------------------------------------------------------------*/
/* FUN_004631fc @ 0x004631fc
 * Ghidra: void FUN_004631fc(void)
 * Lays the two-word message {0, 0xe000000000000000} on the stack and dispatches
 * the Swift string emit helper with code 0x1d.
 * Confidence: low
 * Notes: calls FUN_002a4ab4(0x1d). */
void sk_cmp_4631fc(void)
{
    word_t msg[2] = { 0, 0xe000000000000000 };
    (void)msg;                       /* read by the dispatched callee from the frame */
    sk_rt_002a4ab4(0x1d);
}

/*--------------------------------------------------------------------*/
/* FUN_00463210 @ 0x00463210
 * Ghidra: void FUN_00463210(void)
 * Boot string-map dispatch: resolves the object table named by the code target
 * fn_0064e030 with definition DAT_004be900.
 * Confidence: low
 * Notes: calls FUN_00002534(FUN_0064e030,&DAT_004be900). */
void sk_rt_463210(void)
{
    sk_boot_strmap((unsigned long *)&fn_0064e030, (long *)DAT_004be900);
}

/*--------------------------------------------------------------------*/
/* FUN_0046322c @ 0x0046322c
 * Ghidra: void FUN_0046322c(void)
 * Boot string-map dispatch: resolves the object table named by DAT_0064e890
 * with definition DAT_004f1980.
 * Confidence: low
 * Notes: calls FUN_00002534(&DAT_0064e890,&DAT_004f1980). */
void sk_rt_46322c(void)
{
    sk_boot_strmap((unsigned long *)fn_0064e890, (long *)DAT_004f1980);
}

/*--------------------------------------------------------------------*/
/* FUN_00463240 @ 0x00463240
 * Ghidra: void FUN_00463240(undefined8 p1)
 * Compares p1 against the fixed tagged word 0xe100000000000000.
 * Confidence: low
 * Notes: calls FUN_002a0cf8(p1,0xe100000000000000). */
void sk_cmp_463240(word_t p1)
{
    sk_swift_str_cmp_ci(p1, 0xe100000000000000);
}

/*--------------------------------------------------------------------*/
/* FUN_00463254 @ 0x00463254
 * Ghidra: void FUN_00463254(undefined8 p1,ulong p2)
 * Compares p1 against the low-48-bits-masked p2 OR 0xe900000000000000.
 * Confidence: low
 * Notes: calls FUN_002a0cf8(p1,(p2 & 0xffffffffffff) | 0xe900000000000000). */
void sk_cmp_463254(word_t p1, word_t p2)
{
    sk_swift_str_cmp_ci(p1, (p2 & 0xffffffffffff) | 0xe900000000000000);
}

/*--------------------------------------------------------------------*/
/* FUN_00463268 @ 0x00463268
 * Ghidra: void FUN_00463268(void)
 * Empty stub / placeholder in the runtime glue table.
 * Confidence: low */
void sk_noop_463268(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00463280 @ 0x00463280
 * Ghidra: void FUN_00463280(void)
 * Empty stub / placeholder in the runtime glue table.
 * Confidence: low */
void sk_noop_463280(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00463290 @ 0x00463290
 * Ghidra: void FUN_00463290(void)
 * Empty stub / placeholder in the runtime glue table.
 * Confidence: low */
void sk_noop_463290(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_004632a4 @ 0x004632a4
 * Ghidra: void FUN_004632a4(void)
 * Empty stub / placeholder in the runtime glue table.
 * Confidence: low */
void sk_noop_4632a4(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_004632b8 @ 0x004632b8
 * Ghidra: void FUN_004632b8(void)
 * Copies the two words at src+0x28/0x30 into dst+0x28/0x30.
 * Confidence: low
 * Notes: register-artifact (unaff_x19/x20). */
void sk_cmp_4632b8(word_t *src, word_t *dst)
{
    *(word_t *)((char *)dst + 0x28) = *(word_t *)((char *)src + 0x28);
    *(word_t *)((char *)dst + 0x30) = *(word_t *)((char *)src + 0x30);
}

/*--------------------------------------------------------------------*/
/* FUN_004632cc @ 0x004632cc
 * Ghidra: void FUN_004632cc(void)
 * Empty stub / placeholder in the runtime glue table.
 * Confidence: low */
void sk_noop_4632cc(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_004632e0 @ 0x004632e0
 * Ghidra: void FUN_004632e0(void)
 * Empty stub / placeholder in the runtime glue table.
 * Confidence: low */
void sk_noop_4632e0(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_004632f4 @ 0x004632f4
 * Ghidra: void FUN_004632f4(void)
 * Empty stub / placeholder in the runtime glue table.
 * Confidence: low */
void sk_noop_4632f4(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_0046330c @ 0x0046330c
 * Ghidra: void FUN_0046330c(void)
 * Empty stub / placeholder in the runtime glue table.
 * Confidence: low */
void sk_noop_46330c(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00463320 @ 0x00463320
 * Ghidra: void FUN_00463320(void)
 * Empty stub / placeholder in the runtime glue table.
 * Confidence: low */
void sk_noop_463320(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00463334 @ 0x00463334
 * Ghidra: void FUN_00463334(void)
 * Empty stub / placeholder in the runtime glue table.
 * Confidence: low */
void sk_noop_463334(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00463344 @ 0x00463344
 * Ghidra: void FUN_00463344(void)
 * Copies the two words at src+0x20/0x28 into dst+0x20/0x28.
 * Confidence: low
 * Notes: register-artifact (unaff_x19/x20). */
void sk_cmp_463344(word_t *src, word_t *dst)
{
    *(word_t *)((char *)dst + 0x20) = *(word_t *)((char *)src + 0x20);
    *(word_t *)((char *)dst + 0x28) = *(word_t *)((char *)src + 0x28);
}

/*--------------------------------------------------------------------*/
/* FUN_00463358 @ 0x00463358
 * Ghidra: void FUN_00463358(undefined1 v[16])
 * Fills the eight 16-byte slots at dst+8 .. dst+0x80 with repetitions of the
 * input pair {v.lo, v.hi} (slot i at dst+8+16*i).
 * Confidence: low
 * Notes: register-artifact (unaff_x19 = dst). */
void sk_rt_463358(sk_u128_t v, void *dst)
{
    int i;
    sk_u128_t *slots = (sk_u128_t *)((char *)dst + 8);
    for (i = 0; i < 8; i++)
        slots[i] = v;
}

/*--------------------------------------------------------------------*/
/* FUN_0046337c @ 0x0046337c
 * Ghidra: void FUN_0046337c(undefined8 *dst,undefined8 *src)
 * Copies src[0],src[1] into dst[0],dst[1] (swapping the write order), then
 * releases the previous dst[1] word via sk_rt_003a25d4.
 * Confidence: low
 * Notes: calls FUN_003a25d4(saved dst[1]). */
void sk_rt_46337c(word_t *dst, word_t *src)
{
    word_t d1 = dst[1];
    word_t s1 = src[1];
    dst[0] = src[0];
    dst[1] = s1;
    sk_rt_003a25d4(d1);
}

/*--------------------------------------------------------------------*/
/* FUN_00463394 @ 0x00463394
 * Ghidra: void FUN_00463394(void)
 * Empty stub / placeholder in the runtime glue table.
 * Confidence: low */
void sk_noop_463394(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_004633b8 @ 0x004633b8
 * Ghidra: void FUN_004633b8(void)
 * No-argument dispatch into the Swift ci string compare helper.
 * Confidence: low
 * Notes: calls FUN_002a0cf8() with no recovered args. */
void sk_cmp_4633b8(void)
{
    sk_swift_str_cmp_ci();
}

/*--------------------------------------------------------------------*/
/* FUN_004633cc @ 0x004633cc
 * Ghidra: void FUN_004633cc(void)
 * No-argument dispatch into the Swift ci string compare helper.
 * Confidence: low
 * Notes: calls FUN_002a0cf8() with no recovered args. */
void sk_cmp_4633cc(void)
{
    sk_swift_str_cmp_ci();
}

/*--------------------------------------------------------------------*/
/* FUN_004633e0 @ 0x004633e0
 * Ghidra: void FUN_004633e0(void)
 * Empty stub / placeholder in the runtime glue table.
 * Confidence: low */
void sk_noop_4633e0(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_004633f4 @ 0x004633f4
 * Ghidra: void FUN_004633f4(void)
 * No-argument dispatch into the Swift ci string compare helper.
 * Confidence: low
 * Notes: calls FUN_002a0cf8() with no recovered args. */
void sk_cmp_4633f4(void)
{
    sk_swift_str_cmp_ci();
}

/*--------------------------------------------------------------------*/
/* FUN_00463404 @ 0x00463404
 * Ghidra: void FUN_00463404(undefined8 p1)
 * Compares p1 against the fixed tagged word 0xe100000000000000.
 * Confidence: low
 * Notes: calls FUN_002a0cf8(p1,0xe100000000000000). */
void sk_cmp_463404(word_t p1)
{
    sk_swift_str_cmp_ci(p1, 0xe100000000000000);
}

/*--------------------------------------------------------------------*/
/* FUN_00463418 @ 0x00463418
 * Ghidra: void FUN_00463418(ulong p1,ulong p2)
 * Builds a six-word message: [0x0]=p1, [0x8]=p2, [0x10]=0,
 * [0x18]=length (= p1&0xffffffffffff, or p2>>0x38 & 0xf when the p2 tag bit is
 * set), [0x20]=0, [0x28]=0xe000000000000000; then dispatches through the
 * refcount-acquire thunk with p2.
 * Confidence: low
 * Notes: calls thunk_FUN_0036b270(p2) (target FUN_0036b270 = sk_refcount_acquire_c). */
void sk_rt_463418(word_t p1, word_t p2)
{
    word_t msg[6];
    word_t length = p1 & 0xffffffffffff;
    if ((p2 & 0x2000000000000000) != 0)
        length = (p2 >> 0x38) & 0xf;
    msg[0] = p1;
    msg[1] = p2;
    msg[2] = 0;
    msg[3] = length;
    msg[4] = 0;
    msg[5] = 0xe000000000000000;
    (void)msg;                       /* message words consumed by the dispatched callee */
    sk_refcount_acquire_c(p2);
}

/*--------------------------------------------------------------------*/
/* FUN_00463444 @ 0x00463444
 * Ghidra: undefined1[16] FUN_00463444(void)
 * Returns the 16-byte pair {lo:0xd000000000000015, hi:ctx|0x8000000000000000}.
 * Confidence: low
 * Notes: register-artifact (in_x9). */
sk_u128_t sk_rt_463444(word_t ctx)
{
    sk_u128_t r;
    r.lo = 0xd000000000000015;
    r.hi = ctx | 0x8000000000000000;
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_00463454 @ 0x00463454
 * Ghidra: undefined8 FUN_00463454(void)
 * Returns the word at ctx+0xc0.
 * Confidence: low
 * Notes: register-artifact (unaff_x19). */
word_t sk_rt_463454(void *ctx)
{
    return *(word_t *)((char *)ctx + 0xc0);
}

/*--------------------------------------------------------------------*/
/* FUN_00463474 @ 0x00463474
 * Ghidra: void FUN_00463474(void)
 * Empty stub / placeholder in the runtime glue table.
 * Confidence: low */
void sk_noop_463474(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00463484 @ 0x00463484
 * Ghidra: void FUN_00463484(long p1,long p2)
 * Copies the three words at p2+8/0x10/0x18 into p1+8/0x10 and ctx+0x18.
 * Confidence: low
 * Notes: register-artifact (unaff_x20 = ctx). */
void sk_cmp_463484(word_t *p1, word_t *p2, void *ctx)
{
    *(word_t *)((char *)p1 + 8) = *(word_t *)((char *)p2 + 8);
    *(word_t *)((char *)p1 + 0x10) = *(word_t *)((char *)p2 + 0x10);
    *(word_t *)((char *)ctx + 0x18) = *(word_t *)((char *)p2 + 0x18);
}

/*--------------------------------------------------------------------*/
/* FUN_004634a4 @ 0x004634a4
 * Ghidra: void FUN_004634a4(void)
 * Empty stub / placeholder in the runtime glue table.
 * Confidence: low */
void sk_noop_4634a4(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_004634b4 @ 0x004634b4
 * Ghidra: void FUN_004634b4(void)
 * Empty stub / placeholder in the runtime glue table.
 * Confidence: low */
void sk_noop_4634b4(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_004634d4 @ 0x004634d4
 * Ghidra: undefined1[16] FUN_004634d4(long p1)
 * Returns the 16-byte pair {lo:p1+0x20, hi:&stack0x1310} (a caller-stack
 * buffer descriptor).
 * Confidence: low
 * Notes: hi is the recovered stack address 0x1310. */
sk_u128_t sk_rt_4634d4(word_t p1)
{
    sk_u128_t r;
    r.lo = p1 + 0x20;
    r.hi = 0;                        /* &stack0x00001310: caller-frame buffer address */
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_004634e4 @ 0x004634e4
 * Ghidra: undefined8 FUN_004634e4(void)
 * Returns the 6-byte ASCII tag constant 0x7478656b6a63 ("cjkext").
 * Confidence: low
 * Notes: 0x7478656b6a63 = bytes "c","j","k","e","x","t" little-endian. */
word_t sk_rt_4634e4(void)
{
    return 0x7478656b6a63;
}

/*--------------------------------------------------------------------*/
/* FUN_004634f4 @ 0x004634f4
 * Ghidra: void FUN_004634f4(void)
 * Empty stub / placeholder in the runtime glue table.
 * Confidence: low */
void sk_noop_4634f4(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00463504 @ 0x00463504
 * Ghidra: void FUN_00463504(void)
 * Empty stub / placeholder in the runtime glue table.
 * Confidence: low */
void sk_noop_463504(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00463514 @ 0x00463514
 * Ghidra: undefined1[16] FUN_00463514(void)
 * Returns the constant 16-byte pair {lo:0x27, hi:0xe100000000000000}.
 * Confidence: medium */
sk_u128_t sk_rt_463514(void)
{
    sk_u128_t r;
    r.lo = 0x27;
    r.hi = 0xe100000000000000;
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_00463520 @ 0x00463520
 * Ghidra: void FUN_00463520(undefined8 p1)
 * Compares p1 against the fixed tagged word 0xe100000000000000.
 * Confidence: low
 * Notes: calls FUN_002a0cf8(p1,0xe100000000000000). */
void sk_cmp_463520(word_t p1)
{
    sk_swift_str_cmp_ci(p1, 0xe100000000000000);
}

/*--------------------------------------------------------------------*/
/* FUN_00463534 @ 0x00463534
 * Ghidra: void FUN_00463534(void)
 * Empty stub / placeholder in the runtime glue table.
 * Confidence: low */
void sk_noop_463534(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00463540 @ 0x00463540
 * Ghidra: void FUN_00463540(void)
 * Empty stub / placeholder in the runtime glue table.
 * Confidence: low */
void sk_noop_463540(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00463558 @ 0x00463558
 * Ghidra: undefined1[16] FUN_00463558(undefined1 a[16],undefined1 b[16],
 *                          undefined1 c[16],undefined1 d[16])
 * Byte-wise ORs the four 16-byte inputs into `orr`. Returns an 8-byte packed
 * result (upper 8 bytes zero) where byte K = orr[K] | orr[K+1], i.e. the
 * overlap/adjoin detection of any two adjacent set bytes across the four
 * inputs (implemented via a 1-byte vector-ext on the OR result).
 * Confidence: low
 * Notes: NEON_ext(orr,orr,8,1) = rotate-left-by-1 byte of the OR; result is
 * the first 8 bytes of (orr | rotate1(orr)), upper half zeroed. */
sk_u128_t sk_rt_463558(const uint8_t a[16], const uint8_t b[16],
                       const uint8_t c[16], const uint8_t d[16])
{
    uint8_t orr[16];
    uint8_t res[16];
    int i;
    for (i = 0; i < 16; i++)
        orr[i] = a[i] | b[i] | c[i] | d[i];
    /* res[i] = orr[i] | orr[i+1] (ext-1 rotate, indices 0..7 used) */
    for (i = 0; i < 8; i++)
        res[i] = orr[i] | orr[i + 1];
    for (i = 8; i < 16; i++)
        res[i] = 0;
    {
        sk_u128_t r;
        memcpy(&r.lo, res, 8);
        r.hi = 0;
        return r;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_00463570 @ 0x00463570
 * Ghidra: void FUN_00463570(void)
 * Empty stub / placeholder in the runtime glue table.
 * Confidence: low */
void sk_noop_463570(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_0046357c @ 0x0046357c
 * Ghidra: void FUN_0046357c(undefined8 p1)
 * Compares p1 against the fixed tagged word 0xe300000000000000.
 * Confidence: low
 * Notes: calls FUN_002a0cf8(p1,0xe300000000000000). */
void sk_cmp_46357c(word_t p1)
{
    sk_swift_str_cmp_ci(p1, 0xe300000000000000);
}

/*--------------------------------------------------------------------*/
/* FUN_00463590 @ 0x00463590
 * Ghidra: void FUN_00463590(undefined8 p1)
 * Compares p1 against the fixed tagged word 0xe100000000000000.
 * Confidence: low
 * Notes: calls FUN_002a0cf8(p1,0xe100000000000000). */
void sk_cmp_463590(word_t p1)
{
    sk_swift_str_cmp_ci(p1, 0xe100000000000000);
}
