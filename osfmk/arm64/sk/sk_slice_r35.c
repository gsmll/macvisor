/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel,
 * arm64e, image base 0) - the cL4 microkernel. Ground truth: Ghidra FUN_ names +
 * addresses in program cl4_kernel.raw. Version "cL4 microkernel (cL4
 * (679.100.61))". All names are estimates unless string/header-matched.
 *
 * This file covers wave batch SKR35, slice 0x004aa1e4-0x004aaee8: the Swift
 * _StringProcessing / regex engine method-dispatch table region that continues
 * the layer transcribed in slice r34. The functions here are the vtable method
 * entries of the regex/AST node object: mostly trivial dispatch stubs, empty
 * no-op methods, constant-returning descriptors, 16-byte (pointer,size) pair
 * returns, and short forwarding thunks into shared helper routines. The
 * entries that store `*(*(ctx+8)+0x10) = counter+1` are retain/enumeration
 * counter bumps against a context carried in a callee-saved register
 * (unaff_x19/x20/x22), exactly as in the neighbouring slices.
 *
 * All out-of-range callees are declared as externs. Pair-returning (16-byte)
 * helpers use the cl4_result_t struct {lo,hi}. The `<< 0x40` pair returns
 * (decompiler artifact) place the significant word in the hi half.
 */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "sk_internal.h"

/* 16-byte (two-word) result used by the return-by-value helpers below. */
typedef cl4_result_t sk_r35_pair_t;

/* ------------------------------------------------------------------ *
 * Out-of-range cL4/Swift-runtime helpers referenced by this slice.
 * Unprototyped AAPCS64 externs. cl4_result_t for the 16-byte returns.
 * FUN_ addresses in comments. Names are estimates.
 * ------------------------------------------------------------------ */
extern unsigned long sk_x_003580e4(void);  /* FUN_003580e4 */
extern unsigned long sk_x_001b58b0(void);  /* FUN_001b58b0 */
extern unsigned long sk_x_004a3458(void);  /* FUN_004a3458 */
extern long          sk_x_00377824(unsigned long, unsigned long, unsigned long, long, long); /* FUN_00377824 */
extern void          sk_x_00498c84(unsigned long); /* FUN_00498c84 */
extern void          sk_x_00498c1c(unsigned long, unsigned long); /* FUN_00498c1c */
extern cl4_result_t  sk_x_0046c4e0(unsigned long, unsigned long, unsigned long,
                                   unsigned long, unsigned long, unsigned long,
                                   unsigned long); /* FUN_0046c4e0 */
extern cl4_result_t  sk_x_0036993c(long, unsigned long, long, unsigned long); /* FUN_0036993c */
extern void          sk_x_004a4ac4(unsigned long, unsigned long, unsigned long,
                                   unsigned long); /* FUN_004a4ac4 */
extern void          sk_x_0048c718(unsigned long, unsigned long, unsigned long,
                                   unsigned long); /* FUN_0048c718 */
extern unsigned long sk_x_0036b270(unsigned long); /* FUN_0036b270 */
extern unsigned long sk_x_00365b6c(unsigned long, unsigned long, unsigned long *,
                                   long, unsigned long); /* FUN_00365b6c */
extern void          sk_x_00377bec(unsigned long, unsigned long, unsigned long,
                                   long, long); /* FUN_00377bec */
extern void          sk_x_000839f8(unsigned long, unsigned long, long); /* FUN_000839f8 */

/* ------------------------------------------------------------------ *
 * Method-dispatch table entries.
 * ------------------------------------------------------------------ */

/* FUN_004aa1e4 @ 0x004aa1e4
 * Ghidra: void FUN_004aa1e4(void)
 * Empty vtable slot forwarding to the shared dispatch routine FUN_00469f58
 * (which itself runs the FUN_003580e4 + FUN_001b58b0 pair).
 * Confidence: medium
 * Notes: identical body to the 004aa1e8 neighbour (duplicated table slots). */
static void sk_r35_004aa1e4(void)
{
    sk_x_003580e4();
    sk_x_001b58b0();
}

/* FUN_004aa1e8 @ 0x004aa1e8
 * Ghidra: void FUN_004aa1e8(void)
 * Duplicate vtable slot with the same body as 004aa1e4.
 * Confidence: medium */
static void sk_r35_004aa1e8(void)
{
    sk_x_003580e4();
    sk_x_001b58b0();
}

/* FUN_004aa2a8 @ 0x004aa2a8
 * Ghidra: void FUN_004aa2a8(void)
 * Vtable slot forwarding to FUN_004a3400 (which tail-calls FUN_004a3458).
 * Confidence: medium */
static void sk_r35_004aa2a8(void)
{
    sk_x_004a3458();
}

/* FUN_004aa2ac @ 0x004aa2ac
 * Ghidra: void FUN_004aa2ac(void)
 * Duplicate vtable slot, same body as 004aa2a8.
 * Confidence: medium */
static void sk_r35_004aa2ac(void)
{
    sk_x_004a3458();
}

/* FUN_004aa370 @ 0x004aa370
 * Ghidra: undefined8 FUN_004aa370(void)
 * Returns the fixed method-implementation address 0x6854f0 (a code pointer).
 * Confidence: medium */
static unsigned long sk_r35_004aa370(void)
{
    return 0x6854f0UL;
}

/* FUN_004aa38c @ 0x004aa38c
 * Ghidra: void FUN_004aa38c(void)
 * Empty no-op method.
 * Confidence: high */
static void sk_r35_004aa38c(void)
{
}

/* FUN_004aa3bc @ 0x004aa3bc
 * Ghidra: void FUN_004aa3bc(void)
 * Empty no-op method.
 * Confidence: high */
static void sk_r35_004aa3bc(void)
{
}

/* FUN_004aa3e4 @ 0x004aa3e4
 * Ghidra: void FUN_004aa3e4(void)
 * Empty no-op method.
 * Confidence: high */
static void sk_r35_004aa3e4(void)
{
}

/* FUN_004aa3fc @ 0x004aa3fc
 * Ghidra: void FUN_004aa3fc(void)
 * Empty no-op method.
 * Confidence: high */
static void sk_r35_004aa3fc(void)
{
}

/* FUN_004aa42c @ 0x004aa42c
 * Ghidra: void FUN_004aa42c(void)
 * Empty no-op method.
 * Confidence: high */
static void sk_r35_004aa42c(void)
{
}

/* FUN_004aa44c @ 0x004aa44c
 * Ghidra: void FUN_004aa44c(void)
 * Empty no-op method.
 * Confidence: high */
static void sk_r35_004aa44c(void)
{
}

/* FUN_004aa464 @ 0x004aa464
 * Ghidra: void FUN_004aa464(void)
 * Empty no-op method.
 * Confidence: high */
static void sk_r35_004aa464(void)
{
}

/* FUN_004aa47c @ 0x004aa47c
 * Ghidra: undefined8 FUN_004aa47c(void)
 * Returns zero.
 * Confidence: high */
static unsigned long sk_r35_004aa47c(void)
{
    return 0;
}

/* FUN_004aa494 @ 0x004aa494
 * Ghidra: void FUN_004aa494(void)
 * Empty no-op method.
 * Confidence: high */
static void sk_r35_004aa494(void)
{
}

/* FUN_004aa4ac @ 0x004aa4ac
 * Ghidra: void FUN_004aa4ac(void)
 * Empty no-op method.
 * Confidence: high */
static void sk_r35_004aa4ac(void)
{
}

/* FUN_004aa4c4 @ 0x004aa4c4
 * Ghidra: void FUN_004aa4c4(void)
 * Empty no-op method.
 * Confidence: high */
static void sk_r35_004aa4c4(void)
{
}

/* FUN_004aa4e0 @ 0x004aa4e0
 * Ghidra: undefined8 FUN_004aa4e0(void)
 * Returns the fixed method-implementation address 0x685578 (a code pointer).
 * Confidence: medium */
static unsigned long sk_r35_004aa4e0(void)
{
    return 0x685578UL;
}

/* FUN_004aa4fc @ 0x004aa4fc
 * Ghidra: undefined8 FUN_004aa4fc(void)
 * Returns zero.
 * Confidence: high */
static unsigned long sk_r35_004aa4fc(void)
{
    return 0;
}

/* FUN_004aa514 @ 0x004aa514
 * Ghidra: void FUN_004aa514(void)
 * Bumps the enumeration/retain counter at ctx->+0x10: writes (x25+1) into
 * *(*(x19+8)+0x10), where x19 is a self/context register and x25 an
 * incoming counter register.
 * Confidence: medium */
static void sk_r35_004aa514(long ctx, long counter)
{
    *(long *)(*(long *)(ctx + 8) + 0x10) = counter + 1;
}

/* FUN_004aa52c @ 0x004aa52c
 * Ghidra: void FUN_004aa52c(void)
 * Calls FUN_00498c84 with the counter value read from *(*(x19+8)+0x10).
 * Confidence: medium */
static void sk_r35_004aa52c(long ctx)
{
    sk_x_00498c84(*(unsigned long *)(*(long *)(ctx + 8) + 0x10));
}

/* FUN_004aa550 @ 0x004aa550
 * Ghidra: void FUN_004aa550(param_1,param_2,param_3)
 * Builds a message via FUN_00377824 with two descriptor words from param_3
 * (+0x10, +0x18) and the table pointers 0x61628c / 0x61629c.
 * Confidence: low
 * Notes: DAT_0061628c / LAB_0061629c are the message-encode metadata. */
static void sk_r35_004aa550(unsigned long p1, unsigned long p2, long p3)
{
    sk_x_00377824(0, *(unsigned long *)(p3 + 0x18),
                  *(unsigned long *)(p3 + 0x10), 0x61628cL, 0x61629cL);
}

/* FUN_004aa580 @ 0x004aa580
 * Ghidra: void FUN_004aa580(param_1)
 * Bumps the counter at param_1+0x10 to (x25+1).
 * Confidence: medium */
static void sk_r35_004aa580(long p, long counter)
{
    *(long *)(p + 0x10) = counter + 1;
}

/* FUN_004aa594 @ 0x004aa594
 * Ghidra: void FUN_004aa594(void)
 * Empty no-op method.
 * Confidence: high */
static void sk_r35_004aa594(void)
{
}

/* FUN_004aa5ac @ 0x004aa5ac
 * Ghidra: void FUN_004aa5ac(void)
 * Empty no-op method.
 * Confidence: high */
static void sk_r35_004aa5ac(void)
{
}

/* FUN_004aa5c4 @ 0x004aa5c4
 * Ghidra: undefined1 [16] FUN_004aa5c4(void)
 * Returns a {lo=0, hi=*(x20+0x10)+1} pair (significant word in hi).
 * Confidence: medium */
static sk_r35_pair_t sk_r35_004aa5c4(long ctx)
{
    sk_r35_pair_t r;
    r.lo = 0;
    r.hi = *(long *)(ctx + 0x10) + 1;
    return r;
}

/* FUN_004aa5dc @ 0x004aa5dc
 * Ghidra: undefined1 [16] FUN_004aa5dc(param_1)
 * Returns {lo=0, hi=param_1}.
 * Confidence: high */
static sk_r35_pair_t sk_r35_004aa5dc(unsigned long v)
{
    sk_r35_pair_t r;
    r.lo = 0;
    r.hi = v;
    return r;
}

/* FUN_004aa5f8 @ 0x004aa5f8
 * Ghidra: void FUN_004aa5f8(void)
 * Empty no-op method.
 * Confidence: high */
static void sk_r35_004aa5f8(void)
{
}

/* FUN_004aa610 @ 0x004aa610
 * Ghidra: void FUN_004aa610(void)
 * Calls the message builder FUN_0036993c with fixed args (0x687498, 0x5a4990,
 * 0, 0).
 * Confidence: medium */
static void sk_r35_004aa610(void)
{
    sk_x_0036993c(0x687498L, 0x5a4990UL, 0, 0);
}

/* FUN_004aa638 @ 0x004aa638
 * Ghidra: void FUN_004aa638(param_1)
 * Copies an 18-byte aligned record: two words + two tail bytes at +0x10/+0x11,
 * from (param_1+7+x22)&~7 to (param_1+7+x20)&~7.
 * Confidence: medium */
static void sk_r35_004aa638(long p, long src_off, long dst_off)
{
    uint64_t *src = (uint64_t *)((p + 7 + src_off) & ~0x7UL);
    uint64_t *dst = (uint64_t *)((p + 7 + dst_off) & ~0x7UL);
    *dst = *src;
    dst[1] = src[1];
    *(uint8_t *)(dst + 2) = *(uint8_t *)(src + 2);
    *(uint8_t *)((long)dst + 0x11) = *(uint8_t *)((long)src + 0x11);
}

/* FUN_004aa67c @ 0x004aa67c
 * Ghidra: undefined8 FUN_004aa67c(void)
 * Returns 0xff.
 * Confidence: high */
static unsigned long sk_r35_004aa67c(void)
{
    return 0xffUL;
}

/* FUN_004aa694 @ 0x004aa694
 * Ghidra: void FUN_004aa694(void)
 * Empty no-op method.
 * Confidence: high */
static void sk_r35_004aa694(void)
{
}

/* FUN_004aa6a8 @ 0x004aa6a8
 * Ghidra: void FUN_004aa6a8(void)
 * Appends a word: bumps counter at *x20+0x10, stores x22 at *x20+x21*8+0x20.
 * Confidence: medium */
static void sk_r35_004aa6a8(long *list, long index, unsigned long value)
{
    long head = *list;
    *(long *)(head + 0x10) = index + 1;
    *(unsigned long *)(head + index * 8 + 0x20) = value;
    *list = head;
}

/* FUN_004aa6c4 @ 0x004aa6c4
 * Ghidra: undefined1 [16] FUN_004aa6c4(void)
 * Returns {lo=0x657c28, hi=0x5a3cd0}.
 * Confidence: medium */
static sk_r35_pair_t sk_r35_004aa6c4(void)
{
    sk_r35_pair_t r;
    r.lo = 0x657c28UL;
    r.hi = 0x5a3cd0UL;
    return r;
}

/* FUN_004aa6d8 @ 0x004aa6d8
 * Ghidra: void FUN_004aa6d8(void)
 * Empty no-op method.
 * Confidence: high */
static void sk_r35_004aa6d8(void)
{
}

/* FUN_004aa6f0 @ 0x004aa6f0
 * Ghidra: void FUN_004aa6f0(param_1)
 * Copies a 9-byte aligned record (one word + one tail byte at +8) from
 * (param_1+7+in_x9+x19)&~7 to (param_1+7+in_x9+x20)&~7.
 * Confidence: medium */
static void sk_r35_004aa6f0(long p, long in_x9, long src_off, long dst_off)
{
    uint64_t *src = (uint64_t *)((p + in_x9 + 7 + src_off) & ~0x7UL);
    uint64_t *dst = (uint64_t *)((p + in_x9 + 7 + dst_off) & ~0x7UL);
    *dst = *src;
    *(uint8_t *)(dst + 1) = *(uint8_t *)(src + 1);
}

/* FUN_004aa720 @ 0x004aa720
 * Ghidra: bool FUN_004aa720(param_1)
 * Returns param_1 > 1.
 * Confidence: high */
static bool sk_r35_004aa720(unsigned long v)
{
    return 1 < v;
}

/* FUN_004aa734 @ 0x004aa734
 * Ghidra: void FUN_004aa734(void)
 * Empty no-op method.
 * Confidence: high */
static void sk_r35_004aa734(void)
{
}

/* FUN_004aa74c @ 0x004aa74c
 * Ghidra: undefined8 FUN_004aa74c(void)
 * Returns zero.
 * Confidence: high */
static unsigned long sk_r35_004aa74c(void)
{
    return 0;
}

/* FUN_004aa75c @ 0x004aa75c
 * Ghidra: void FUN_004aa75c(void)
 * Empty no-op method.
 * Confidence: high */
static void sk_r35_004aa75c(void)
{
}

/* FUN_004aa770 @ 0x004aa770
 * Ghidra: undefined8 FUN_004aa770(void)
 * Returns 0xff.
 * Confidence: high */
static unsigned long sk_r35_004aa770(void)
{
    return 0xffUL;
}

/* FUN_004aa780 @ 0x004aa780
 * Ghidra: void FUN_004aa780(void)
 * Bumps the counter at *(x22+8)+0x10 to (x23+1).
 * Confidence: medium */
static void sk_r35_004aa780(long ctx, long counter)
{
    *(long *)(*(long *)(ctx + 8) + 0x10) = counter + 1;
}

/* FUN_004aa794 @ 0x004aa794
 * Ghidra: undefined1 [16] FUN_004aa794(void)
 * Returns {lo=0x687b68, hi=0x20}.
 * Confidence: medium */
static sk_r35_pair_t sk_r35_004aa794(void)
{
    sk_r35_pair_t r;
    r.lo = 0x687b68UL;
    r.hi = 0x20UL;
    return r;
}

/* FUN_004aa7a8 @ 0x004aa7a8
 * Ghidra: undefined8 FUN_004aa7a8(void)
 * Returns *(*(x19+8)+0x10).
 * Confidence: medium */
static unsigned long sk_r35_004aa7a8(long ctx)
{
    return *(unsigned long *)(*(long *)(ctx + 8) + 0x10);
}

/* FUN_004aa7bc @ 0x004aa7bc
 * Ghidra: undefined1 [16] FUN_004aa7bc(void)
 * Returns {lo=0x686228, hi=0xc0}.
 * Confidence: medium */
static sk_r35_pair_t sk_r35_004aa7bc(void)
{
    sk_r35_pair_t r;
    r.lo = 0x686228UL;
    r.hi = 0xc0UL;
    return r;
}

/* FUN_004aa7d0 @ 0x004aa7d0
 * Ghidra: void FUN_004aa7d0(void)
 * Empty no-op method.
 * Confidence: high */
static void sk_r35_004aa7d0(void)
{
}

/* FUN_004aa7fc @ 0x004aa7fc
 * Ghidra: undefined8 FUN_004aa7fc(param_1)
 * Returns *(param_1+0x10).
 * Confidence: high */
static unsigned long sk_r35_004aa7fc(long p)
{
    return *(unsigned long *)(p + 0x10);
}

/* FUN_004aa80c @ 0x004aa80c
 * Ghidra: undefined8 FUN_004aa80c(void)
 * Returns zero.
 * Confidence: high */
static unsigned long sk_r35_004aa80c(void)
{
    return 0;
}

/* FUN_004aa824 @ 0x004aa824
 * Ghidra: void FUN_004aa824(void)
 * Empty no-op method.
 * Confidence: high */
static void sk_r35_004aa824(void)
{
}

/* FUN_004aa83c @ 0x004aa83c
 * Ghidra: undefined1 [16] FUN_004aa83c(void)
 * Returns {lo=0x6862c8, hi=0x18}.
 * Confidence: medium */
static sk_r35_pair_t sk_r35_004aa83c(void)
{
    sk_r35_pair_t r;
    r.lo = 0x6862c8UL;
    r.hi = 0x18UL;
    return r;
}

/* FUN_004aa850 @ 0x004aa850
 * Ghidra: void FUN_004aa850(void)
 * Empty no-op method.
 * Confidence: high */
static void sk_r35_004aa850(void)
{
}

/* FUN_004aa864 @ 0x004aa864
 * Ghidra: void FUN_004aa864(void)
 * Empty no-op method.
 * Confidence: high */
static void sk_r35_004aa864(void)
{
}

/* FUN_004aa878 @ 0x004aa878
 * Ghidra: void FUN_004aa878(void)
 * Empty no-op method.
 * Confidence: high */
static void sk_r35_004aa878(void)
{
}

/* FUN_004aa890 @ 0x004aa890
 * Ghidra: void FUN_004aa890(void)
 * Empty no-op method.
 * Confidence: high */
static void sk_r35_004aa890(void)
{
}

/* FUN_004aa8a0 @ 0x004aa8a0
 * Ghidra: undefined8 FUN_004aa8a0(void)
 * Returns zero.
 * Confidence: high */
static unsigned long sk_r35_004aa8a0(void)
{
    return 0;
}

/* FUN_004aa8b0 @ 0x004aa8b0
 * Ghidra: void FUN_004aa8b0(void)
 * Calls FUN_000839f8 twice (indirect dispatch through vtable slot +0x30).
 * Confidence: medium */
static void sk_r35_004aa8b0(void)
{
    sk_x_000839f8(0, 0, 0);
    sk_x_000839f8(0, 0, 0);
}

/* FUN_004aa8f0 @ 0x004aa8f0
 * Ghidra: void FUN_004aa8f0(void)
 * Empty no-op method.
 * Confidence: high */
static void sk_r35_004aa8f0(void)
{
}

/* FUN_004aa904 @ 0x004aa904
 * Ghidra: void FUN_004aa904(void)
 * Empty no-op method.
 * Confidence: high */
static void sk_r35_004aa904(void)
{
}

/* FUN_004aa914 @ 0x004aa914
 * Ghidra: void FUN_004aa914(void)
 * Calls FUN_000839f8 once (indirect dispatch through vtable slot +0x30).
 * Confidence: medium */
static void sk_r35_004aa914(void)
{
    sk_x_000839f8(0, 0, 0);
}

/* FUN_004aa938 @ 0x004aa938
 * Ghidra: void FUN_004aa938(void)
 * Empty no-op method.
 * Confidence: high */
static void sk_r35_004aa938(void)
{
}

/* FUN_004aa94c @ 0x004aa94c
 * Ghidra: undefined8 FUN_004aa94c(void)
 * Returns zero.
 * Confidence: high */
static unsigned long sk_r35_004aa94c(void)
{
    return 0;
}

/* FUN_004aa95c @ 0x004aa95c
 * Ghidra: undefined8 FUN_004aa95c(void)
 * Returns zero.
 * Confidence: high */
static unsigned long sk_r35_004aa95c(void)
{
    return 0;
}

/* FUN_004aa970 @ 0x004aa970
 * Ghidra: undefined1 [16] FUN_004aa970(param_1)
 * Returns {lo=0, hi=param_1}.
 * Confidence: high */
static sk_r35_pair_t sk_r35_004aa970(unsigned long v)
{
    sk_r35_pair_t r;
    r.lo = 0;
    r.hi = v;
    return r;
}

/* FUN_004aa990 @ 0x004aa990
 * Ghidra: undefined1 [16] FUN_004aa990(void)
 * Returns {lo=0x5c, hi=0xe100000000000000}.
 * Confidence: medium */
static sk_r35_pair_t sk_r35_004aa990(void)
{
    sk_r35_pair_t r;
    r.lo = 0x5cUL;
    r.hi = 0xe100000000000000UL;
    return r;
}

/* FUN_004aa9a8 @ 0x004aa9a8
 * Ghidra: void FUN_004aa9a8(void)
 * Bumps the counter at *(x19+8)+0x10 to (x27+1).
 * Confidence: medium */
static void sk_r35_004aa9a8(long ctx, long counter)
{
    *(long *)(*(long *)(ctx + 8) + 0x10) = counter + 1;
}

/* FUN_004aa9c0 @ 0x004aa9c0
 * Ghidra: void FUN_004aa9c0(param_1)
 * Bumps the counter at param_1+0x10 to (x24+1).
 * Confidence: medium */
static void sk_r35_004aa9c0(long p, long counter)
{
    *(long *)(p + 0x10) = counter + 1;
}

/* FUN_004aa9d0 @ 0x004aa9d0
 * Ghidra: void FUN_004aa9d0(void)
 * Calls FUN_00498c1c with the counter value read from *(*(x22+8)+0x10).
 * Confidence: medium */
static void sk_r35_004aa9d0(long ctx)
{
    sk_x_00498c1c(*(unsigned long *)(*(long *)(ctx + 8) + 0x10), 0);
}

/* FUN_004aa9e8 @ 0x004aa9e8
 * Ghidra: void FUN_004aa9e8(param_1)
 * Bumps the counter at param_1+0x10 to (x26+1).
 * Confidence: medium */
static void sk_r35_004aa9e8(long p, long counter)
{
    *(long *)(p + 0x10) = counter + 1;
}

/* FUN_004aa9f8 @ 0x004aa9f8
 * Ghidra: void FUN_004aa9f8(param_1,param_2)
 * Invokes the typed-message send FUN_0046c4e0 with the fixed selector/type
 * words (0x22, 0xe1..., 0x225c, 0xe2..., 0x7fffffffffffffff) and the two
 * caller arguments.
 * Confidence: medium */
static void sk_r35_004aa9f8(unsigned long p1, unsigned long p2)
{
    sk_x_0046c4e0(0x22UL, 0xe100000000000000UL, 0x225cUL,
                  0xe200000000000000UL, 0x7fffffffffffffffUL, p1, p2);
}

/* FUN_004aaa20 @ 0x004aaa20
 * Ghidra: void FUN_004aaa20(void)
 * Empty no-op method.
 * Confidence: high */
static void sk_r35_004aaa20(void)
{
}

/* FUN_004aaa38 @ 0x004aaa38
 * Ghidra: void FUN_004aaa38(param_1)
 * Stores in_x10 at in_x9+0x20 and param_1 at x22+8.
 * Confidence: low
 * Notes: register-global forwarding entry. */
static void sk_r35_004aaa38(unsigned long p, unsigned long in_x9,
                             unsigned long in_x10, long ctx)
{
    *(unsigned long *)(in_x9 + 0x20) = in_x10;
    *(unsigned long *)(ctx + 8) = p;
}

/* FUN_004aaa48 @ 0x004aaa48
 * Ghidra: void FUN_004aaa48(void)
 * Empty no-op method.
 * Confidence: high */
static void sk_r35_004aaa48(void)
{
}

/* FUN_004aaa78 @ 0x004aaa78
 * Ghidra: void FUN_004aaa78(void)
 * Empty no-op method.
 * Confidence: high */
static void sk_r35_004aaa78(void)
{
}

/* FUN_004aaa88 @ 0x004aaa88
 * Ghidra: void FUN_004aaa88(void)
 * Empty no-op method.
 * Confidence: high */
static void sk_r35_004aaa88(void)
{
}

/* FUN_004aaa9c @ 0x004aaa9c
 * Ghidra: void FUN_004aaa9c(void)
 * Empty no-op method.
 * Confidence: high */
static void sk_r35_004aaa9c(void)
{
}

/* FUN_004aaab0 @ 0x004aaab0
 * Ghidra: void FUN_004aaab0(void)
 * Empty no-op method.
 * Confidence: high */
static void sk_r35_004aaab0(void)
{
}

/* FUN_004aaacc @ 0x004aaacc
 * Ghidra: void FUN_004aaacc(void)
 * Bumps the counter at x20+0x10 to (x26+1).
 * Confidence: medium */
static void sk_r35_004aaacc(long ctx, long counter)
{
    *(long *)(ctx + 0x10) = counter + 1;
}

/* FUN_004aaae0 @ 0x004aaae0
 * Ghidra: void FUN_004aaae0(void)
 * Empty no-op method.
 * Confidence: high */
static void sk_r35_004aaae0(void)
{
}

/* FUN_004aaaf4 @ 0x004aaaf4
 * Ghidra: void FUN_004aaaf4(void)
 * Copies two tail bytes at +0x11 and +0x12 from x20 to x19.
 * Confidence: medium */
static void sk_r35_004aaaf4(long dst, long src)
{
    *(uint8_t *)(dst + 0x11) = *(uint8_t *)(src + 0x11);
    *(uint8_t *)(dst + 0x12) = *(uint8_t *)(src + 0x12);
}

/* FUN_004aab08 @ 0x004aab08
 * Ghidra: void FUN_004aab08(void)
 * Empty no-op method.
 * Confidence: high */
static void sk_r35_004aab08(void)
{
}

/* FUN_004aab1c @ 0x004aab1c
 * Ghidra: undefined8 FUN_004aab1c(void)
 * Returns *(*(x19+8)+0x10).
 * Confidence: medium */
static unsigned long sk_r35_004aab1c(long ctx)
{
    return *(unsigned long *)(*(long *)(ctx + 8) + 0x10);
}

/* FUN_004aab30 @ 0x004aab30
 * Ghidra: undefined1 [16] FUN_004aab30(void)
 * Returns a pair of masked additions {lo,hi} computed from register inputs.
 * Confidence: low
 * Notes: in_x9/in_x10/x19/x20 register-global address arithmetic. */
static sk_r35_pair_t sk_r35_004aab30(unsigned long in_x9, unsigned long in_x10,
                                     long ctx_lo, long ctx_hi)
{
    sk_r35_pair_t r;
    r.lo = (in_x9 + in_x10 + ctx_lo) & (in_x10 ^ 0xffffffffffffffffUL);
    r.hi = (in_x9 + in_x10 + ctx_hi) & (in_x10 ^ 0xffffffffffffffffUL);
    return r;
}

/* FUN_004aab4c @ 0x004aab4c
 * Ghidra: void FUN_004aab4c(void)
 * Empty no-op method.
 * Confidence: high */
static void sk_r35_004aab4c(void)
{
}

/* FUN_004aab60 @ 0x004aab60
 * Ghidra: undefined1 [16] FUN_004aab60(void)
 * Returns {lo=0x686278, hi=0x60}.
 * Confidence: medium */
static sk_r35_pair_t sk_r35_004aab60(void)
{
    sk_r35_pair_t r;
    r.lo = 0x686278UL;
    r.hi = 0x60UL;
    return r;
}

/* FUN_004aab74 @ 0x004aab74
 * Ghidra: undefined1 [16] FUN_004aab74(void)
 * Returns {lo=0x22, hi=0xe100000000000000}.
 * Confidence: medium */
static sk_r35_pair_t sk_r35_004aab74(void)
{
    sk_r35_pair_t r;
    r.lo = 0x22UL;
    r.hi = 0xe100000000000000UL;
    return r;
}

/* FUN_004aab88 @ 0x004aab88
 * Ghidra: void FUN_004aab88(param_1)
 * Bumps the counter at param_1+0x10 to (x25+1).
 * Confidence: medium */
static void sk_r35_004aab88(long p, long counter)
{
    *(long *)(p + 0x10) = counter + 1;
}

/* FUN_004aab98 @ 0x004aab98
 * Ghidra: void FUN_004aab98(void)
 * Empty no-op method.
 * Confidence: high */
static void sk_r35_004aab98(void)
{
}

/* FUN_004aaba8 @ 0x004aaba8
 * Ghidra: void FUN_004aaba8(void)
 * Empty no-op method.
 * Confidence: high */
static void sk_r35_004aaba8(void)
{
}

/* FUN_004aabb8 @ 0x004aabb8
 * Ghidra: void FUN_004aabb8(param_1[16])
 * Interleaved scatter-store of a 16-byte value (param_1) into 20 consecutive
 * 8-byte slots at x19+8 .. x19+0xa0, alternating hi and lo words.
 * Confidence: medium */
static void sk_r35_004aabb8(long dst, const uint64_t value[2])
{
    uint64_t lo = value[0];
    uint64_t hi = value[1];
    *(uint64_t *)(dst + 8)    = lo;
    *(uint64_t *)(dst + 0x10) = hi;
    *(uint64_t *)(dst + 0x18) = lo;
    *(uint64_t *)(dst + 0x20) = hi;
    *(uint64_t *)(dst + 0x28) = lo;
    *(uint64_t *)(dst + 0x30) = hi;
    *(uint64_t *)(dst + 0x38) = lo;
    *(uint64_t *)(dst + 0x40) = hi;
    *(uint64_t *)(dst + 0x48) = lo;
    *(uint64_t *)(dst + 0x50) = hi;
    *(uint64_t *)(dst + 0x58) = lo;
    *(uint64_t *)(dst + 0x60) = hi;
    *(uint64_t *)(dst + 0x68) = lo;
    *(uint64_t *)(dst + 0x70) = hi;
    *(uint64_t *)(dst + 0x78) = lo;
    *(uint64_t *)(dst + 0x80) = hi;
    *(uint64_t *)(dst + 0x88) = lo;
    *(uint64_t *)(dst + 0x90) = hi;
    *(uint64_t *)(dst + 0x98) = lo;
    *(uint64_t *)(dst + 0xa0) = hi;
}

/* FUN_004aabe4 @ 0x004aabe4
 * Ghidra: void FUN_004aabe4(void)
 * Empty no-op method.
 * Confidence: high */
static void sk_r35_004aabe4(void)
{
}

/* FUN_004aabf4 @ 0x004aabf4
 * Ghidra: void FUN_004aabf4(param_1)
 * Bumps the counter at param_1+0x10 to (x22+1).
 * Confidence: medium */
static void sk_r35_004aabf4(long p, long counter)
{
    *(long *)(p + 0x10) = counter + 1;
}

/* FUN_004aac04 @ 0x004aac04
 * Ghidra: long FUN_004aac04(void)
 * Returns a stack-frame address (fp - 0x78).
 * Confidence: medium
 * Notes: decompiler artifact of a stack pointer return. */
static long sk_r35_004aac04(long fp)
{
    return fp + -0x78;
}

/* FUN_004aac14 @ 0x004aac14
 * Ghidra: void FUN_004aac14(param_1,param_2)
 * Copies a 26-byte record (2 words + tail bytes at +0x10/+0x11 + 2 more
 * words) from param_2 to param_1.
 * Confidence: medium */
static void sk_r35_004aac14(uint64_t *dst, uint64_t *src)
{
    dst[0] = src[0];
    dst[1] = src[1];
    *(uint8_t *)(dst + 2) = *(uint8_t *)(src + 2);
    *(uint16_t *)((long)dst + 0x11) = *(uint16_t *)((long)src + 0x11);
    dst[3] = src[3];
    dst[4] = src[4];
}

/* FUN_004aac40 @ 0x004aac40
 * Ghidra: void FUN_004aac40(void)
 * Empty no-op method.
 * Confidence: high */
static void sk_r35_004aac40(void)
{
}

/* FUN_004aac68 @ 0x004aac68
 * Ghidra: undefined8 FUN_004aac68(void)
 * Returns zero.
 * Confidence: high */
static unsigned long sk_r35_004aac68(void)
{
    return 0;
}

/* FUN_004aac78 @ 0x004aac78
 * Ghidra: long FUN_004aac78(void)
 * Returns a stack-frame address (fp - 0x98).
 * Confidence: medium
 * Notes: decompiler artifact of a stack pointer return. */
static long sk_r35_004aac78(long fp)
{
    return fp + -0x98;
}

/* FUN_004aac88 @ 0x004aac88
 * Ghidra: void FUN_004aac88(void)
 * Empty no-op method.
 * Confidence: high */
static void sk_r35_004aac88(void)
{
}

/* FUN_004aacb0 @ 0x004aacb0
 * Ghidra: void FUN_004aacb0(void)
 * Calls FUN_00377bec (jump-table dispatch).
 * Confidence: low */
static void sk_r35_004aacb0(void)
{
    sk_x_00377bec(0, 0, 0, 0, 0);
}

/* FUN_004aaccc @ 0x004aaccc
 * Ghidra: void FUN_004aaccc(void)
 * Empty no-op method.
 * Confidence: high */
static void sk_r35_004aaccc(void)
{
}

/* FUN_004aace0 @ 0x004aace0
 * Ghidra: void FUN_004aace0(void)
 * Empty no-op method.
 * Confidence: high */
static void sk_r35_004aace0(void)
{
}

/* FUN_004aacf8 @ 0x004aacf8
 * Ghidra: int FUN_004aacf8(void)
 * Returns (w11 - 0x7e7e7e0f), or (w9 + w8 + 0x8181e1) if w10 == 0.
 * Confidence: low
 * Notes: register-global arithmetic entry (unusual constants). */
static int sk_r35_004aacf8(int w8, int w9, int w10, int w11)
{
    int r = w11 + -0x7e7e7e0f;
    if (w10 == 0) {
        r = w9 + w8 + 0x8181e1;
    }
    return r;
}

/* FUN_004aad1c @ 0x004aad1c
 * Ghidra: void FUN_004aad1c(void)
 * Copies two tail bytes at +0x10 and +0x11 from x20 to x19.
 * Confidence: medium */
static void sk_r35_004aad1c(long dst, long src)
{
    *(uint8_t *)(dst + 0x10) = *(uint8_t *)(src + 0x10);
    *(uint8_t *)(dst + 0x11) = *(uint8_t *)(src + 0x11);
}

/* FUN_004aad30 @ 0x004aad30
 * Ghidra: undefined1 [16] FUN_004aad30(void)
 * Returns {lo=0x686188, hi=0x20}.
 * Confidence: medium */
static sk_r35_pair_t sk_r35_004aad30(void)
{
    sk_r35_pair_t r;
    r.lo = 0x686188UL;
    r.hi = 0x20UL;
    return r;
}

/* FUN_004aad44 @ 0x004aad44
 * Ghidra: undefined8 FUN_004aad44(param_1)
 * Returns *(param_1+0x10).
 * Confidence: high */
static unsigned long sk_r35_004aad44(long p)
{
    return *(unsigned long *)(p + 0x10);
}

/* FUN_004aad54 @ 0x004aad54
 * Ghidra: undefined8 FUN_004aad54(void)
 * Returns *(*x20 + 0x10).
 * Confidence: medium */
static unsigned long sk_r35_004aad54(long *ctx)
{
    return *(unsigned long *)(*ctx + 0x10);
}

/* FUN_004aad6c @ 0x004aad6c
 * Ghidra: void FUN_004aad6c(param_1)
 * Calls FUN_004a4ac4 with the stack pointer and two table pointers
 * (0x657de8, 0x5a4bd8).
 * Confidence: low
 * Notes: passes &stack0x188 (a register-relative address). */
static void sk_r35_004aad6c(unsigned long p, unsigned long stack_ptr)
{
    sk_x_004a4ac4(p, stack_ptr, 0x657de8UL, 0x5a4bd8UL);
}

/* FUN_004aad84 @ 0x004aad84
 * Ghidra: undefined8 FUN_004aad84(void)
 * Returns 0xff.
 * Confidence: high */
static unsigned long sk_r35_004aad84(void)
{
    return 0xffUL;
}

/* FUN_004aad94 @ 0x004aad94
 * Ghidra: void FUN_004aad94(void)
 * Empty no-op method.
 * Confidence: high */
static void sk_r35_004aad94(void)
{
}

/* FUN_004aada4 @ 0x004aada4
 * Ghidra: undefined1 [16] FUN_004aada4(void)
 * Returns {lo=0x6862f0, hi=0x59}.
 * Confidence: medium */
static sk_r35_pair_t sk_r35_004aada4(void)
{
    sk_r35_pair_t r;
    r.lo = 0x6862f0UL;
    r.hi = 0x59UL;
    return r;
}

/* FUN_004aadb8 @ 0x004aadb8
 * Ghidra: void FUN_004aadb8(void)
 * Empty no-op method.
 * Confidence: high */
static void sk_r35_004aadb8(void)
{
}

/* FUN_004aadcc @ 0x004aadcc
 * Ghidra: undefined1 [16] FUN_004aadcc(void)
 * Returns {lo=0x22, hi=0xe100000000000000}.
 * Confidence: medium */
static sk_r35_pair_t sk_r35_004aadcc(void)
{
    sk_r35_pair_t r;
    r.lo = 0x22UL;
    r.hi = 0xe100000000000000UL;
    return r;
}

/* FUN_004aade4 @ 0x004aade4
 * Ghidra: void FUN_004aade4(void)
 * Scatter-stores five stack words into x19[0..4].
 * Confidence: medium
 * Notes: copies the incoming stack spill region. */
static void sk_r35_004aade4(unsigned long *dst, unsigned long s0,
                            unsigned long s1, unsigned long s2,
                            unsigned long s3, unsigned long s4)
{
    dst[1] = s1;
    dst[0] = s0;
    dst[3] = s3;
    dst[2] = s2;
    dst[4] = s4;
}

/* FUN_004aadfc @ 0x004aadfc
 * Ghidra: void FUN_004aadfc(void)
 * Calls FUN_0048c718 (complex buffer walker).
 * Confidence: low */
static void sk_r35_004aadfc(void)
{
    sk_x_0048c718(0, 0, 0, 0);
}

/* FUN_004aae14 @ 0x004aae14
 * Ghidra: void FUN_004aae14(param_1,param_2)
 * Copies one word from param_2 to param_1, then calls FUN_0036b270.
 * Confidence: medium */
static void sk_r35_004aae14(unsigned long *dst, unsigned long *src)
{
    *dst = *src;
    sk_x_0036b270(0);
}

/* FUN_004aae2c @ 0x004aae2c
 * Ghidra: void FUN_004aae2c(void)
 * Empty no-op method.
 * Confidence: high */
static void sk_r35_004aae2c(void)
{
}

/* FUN_004aae44 @ 0x004aae44
 * Ghidra: void FUN_004aae44(void)
 * Calls FUN_00365b6c with the value at fp-0xb0 and the address fp-0xa8.
 * Confidence: medium */
static void sk_r35_004aae44(long fp)
{
    sk_x_00365b6c(*(unsigned long *)(fp + -0xb0), (unsigned long)(fp + -0xa8),
                  0, 0, 0);
}

/* FUN_004aae64 @ 0x004aae64
 * Ghidra: void FUN_004aae64(void)
 * Writes two tag words to fp-0x100 and fp-0xf8: "One(any." big-endian byte
 * pattern with a 0xeb tag tail.
 * Confidence: low
 * Notes: constant tag construction on the stack (DAT_0061... pattern). */
static void sk_r35_004aae64(long fp)
{
    *(uint64_t *)(fp + -0x100) = 0x796e612e28656e4fUL; /* "One(any." */
    *(uint64_t *)(fp + -0xf8)  = 0xeb0000000028664fUL;
}

/* FUN_004aae88 @ 0x004aae88
 * Ghidra: void FUN_004aae88(void)
 * Copies one word at +0x40 from x20 to x19.
 * Confidence: high */
static void sk_r35_004aae88(long dst, long src)
{
    *(unsigned long *)(dst + 0x40) = *(unsigned long *)(src + 0x40);
}

/* FUN_004aae98 @ 0x004aae98
 * Ghidra: void FUN_004aae98(param_1,param_2)
 * Calls FUN_004a4ac4 with the two args and the table pointers (0x657de8,
 * 0x5a4bd8).
 * Confidence: low */
static void sk_r35_004aae98(unsigned long p1, unsigned long p2)
{
    sk_x_004a4ac4(p1, p2, 0x657de8UL, 0x5a4bd8UL);
}

/* FUN_004aaed8 @ 0x004aaed8
 * Ghidra: void FUN_004aaed8(void)
 * Copies one word at +0x28 from x20 to x19.
 * Confidence: high */
static void sk_r35_004aaed8(long dst, long src)
{
    *(unsigned long *)(dst + 0x28) = *(unsigned long *)(src + 0x28);
}

/* FUN_004aaee8 @ 0x004aaee8
 * Ghidra: undefined1 [16] FUN_004aaee8(void)
 * Returns a 16-byte ASCII tag {lo="TODO: re" (+0x6572...), hi="aso".}.
 * Confidence: low
 * Notes: bytes "TODO: re" followed by "aso". tag; likely a placeholder string. */
static sk_r35_pair_t sk_r35_004aaee8(void)
{
    sk_r35_pair_t r;
    r.lo = 0x6572203a4f444f54UL; /* "TODO: re" */
    r.hi = 0xec0000006e6f7361UL;
    return r;
}
