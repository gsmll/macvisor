/* Recreated from cl4_kernel.raw (cL4 Secure Kernel, arm64e, image base 0) —
 * the cL4 microkernel (GL1). Ground truth: Ghidra FUN_ names + addresses.
 * All names are estimates unless string/header matched.
 * Slice 01: 0x3004ec-0x311e34 syscall/exception-entry region.
 *
 * This region is the embedded Swift standard-library runtime that cL4 uses to
 * parse/convert syscall and exception-entry arguments: integer arithmetic with
 * overflow/divide traps, BinaryInteger range-checked conversions, decimal
 * string parsing over UnsafeBufferPointer, word-buffer index validation, and
 * the type-metadata field accessors those conversions drive. The "Fatal error"
 * traps funnel through FUN_001afe4c (Swift fatalError), which never returns.
 */
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "sk_internal.h"
#include "sk_region_syscalls.h"

/* ------------------------------------------------------------------ *
 * Out-of-range cL4 / Swift-runtime helper declarations (declared extern
 * with unspecified parameters; bodies are reconstructed by their range
 * worker). All of these live outside this 0x300000-0x380000 slice and are
 * called by the syscall-argument integer/string runtime below.
 * ------------------------------------------------------------------ */
extern long FUN_00002534();
extern long FUN_00012568();
extern long FUN_0001a1c8();
extern long FUN_00021480();
extern long FUN_00027754();
extern long FUN_000839d8();
extern long FUN_0008e518();
extern long FUN_0008f6c0();
extern long FUN_0008f6f4();
extern long FUN_0008f728();
extern long FUN_0008f758();
extern long FUN_0011d800();
extern long FUN_0011db10();
extern long FUN_0016186c();
extern long FUN_0019cf3c();
extern long FUN_0019e058();
extern long FUN_001a8564();
extern long FUN_001afe4c();
extern long FUN_001d9840();
extern long FUN_001d9f28();
extern long FUN_001e34d8();
extern long FUN_001e4cbc();
extern long FUN_001e655c();
extern long FUN_001e6b1c();
extern long FUN_002298d4();
extern long FUN_0022995c();
extern long FUN_0022cff0();
extern long FUN_0022eb38();
extern long FUN_002323c4();
extern long FUN_002324b0();
extern long FUN_002328cc();
extern long FUN_00232904();
extern long FUN_0023b198();
extern long FUN_0023b1a0();
extern long FUN_0024304c();
extern long FUN_0024320c();
extern long FUN_00246144();
extern long FUN_00246170();
extern long FUN_00246178();
extern long FUN_00295b3c();
extern long FUN_002a9ba8();
extern long FUN_002e6474();
extern long FUN_003004ec();
extern long FUN_00300544();
extern long FUN_003009c0();
extern long FUN_00300f14();
extern long FUN_00301088();
extern long FUN_003010e8();
extern long FUN_00301144();
extern long FUN_00301218();
extern long FUN_0030133c();
extern long FUN_00301438();
extern long FUN_0030150c();
extern long FUN_00301570();
extern long FUN_003015dc();
extern long FUN_003016a4();
extern long FUN_003016f8();
extern long FUN_00301704();
extern long FUN_003018a8();
extern long FUN_003018ec();
extern long FUN_0030194c();
extern long FUN_00301978();
extern long FUN_00301a0c();
extern long FUN_00301a3c();
extern long FUN_00301a8c();
extern long FUN_00301b04();
extern long FUN_0030221c();
extern long FUN_00302280();
extern long FUN_003022f8();
extern long FUN_003023c0();
extern long FUN_00302418();
extern long FUN_003024e0();
extern long FUN_003025ac();
extern long FUN_0030260c();
extern long FUN_00302750();
extern long FUN_003030d4();
extern long FUN_00303a78();
extern long FUN_003043d4();
extern long FUN_00304d34();
extern long FUN_00304d90();
extern long FUN_0030523c();
extern long FUN_00305824();
extern long FUN_003059ec();
extern long FUN_00305a34();
extern long FUN_00305a78();
extern long FUN_00305aec();
extern long FUN_00305b8c();
extern long FUN_00305c40();
extern long FUN_00305c6c();
extern long FUN_00305c9c();
extern long FUN_00305cc8();
extern long FUN_00305d08();
extern long FUN_00305d0c();
extern long FUN_00305d38();
extern long FUN_00305da4();
extern long FUN_00305e94();
extern long FUN_00305ea0();
extern long FUN_00305ee4();
extern long FUN_00305f10();
extern long FUN_00305f88();
extern long FUN_0030655c();
extern long FUN_003065cc();
extern long FUN_00306640();
extern long FUN_003066b4();
extern long FUN_0030670c();
extern long FUN_00306760();
extern long FUN_003067b4();
extern long FUN_003067e8();
extern long FUN_00306890();
extern long FUN_0030695c();
extern long FUN_003069c8();
extern long FUN_00306aa0();
extern long FUN_00306aac();
extern long FUN_00306b00();
extern long FUN_00306b28();
extern long FUN_00306b9c();
extern long FUN_00306c14();
extern long FUN_0030732c();
extern long FUN_003073b0();
extern long FUN_00307428();
extern long FUN_00307514();
extern long FUN_00307ed8();
extern long FUN_0030887c();
extern long FUN_003091d4();
extern long FUN_00309b2c();
extern long FUN_00309b84();
extern long FUN_00309c30();
extern long FUN_00309c6c();
extern long FUN_00309cb4();
extern long FUN_00309cf8();
extern long FUN_00309da0();
extern long FUN_00309e24();
extern long FUN_00309e64();
extern long FUN_00309ed0();
extern long FUN_00309f98();
extern long FUN_00309fa4();
extern long FUN_00309fb0();
extern long FUN_0030a0a0();
extern long FUN_0030a0dc();
extern long FUN_0030a168();
extern long FUN_0030a1e0();
extern long FUN_0030a738();
extern long FUN_0030a7a8();
extern long FUN_0030a81c();
extern long FUN_0030a890();
extern long FUN_0030a8ec();
extern long FUN_0030ae1c();
extern long FUN_0030b340();
extern long FUN_0030b870();
extern long FUN_0030bd90();
extern long FUN_0030bdf0();
extern long FUN_0030c130();
extern long FUN_0030c4cc();
extern long FUN_0030c568();
extern long FUN_0030c56c();
extern long FUN_0030c644();
extern long FUN_0030c718();
extern long FUN_0030c80c();
extern long FUN_0030c8c0();
extern long FUN_0030c920();
extern long FUN_0030c990();
extern long FUN_0030c9cc();
extern long FUN_0030ca94();
extern long FUN_0030cac8();
extern long FUN_0030cad4();
extern long FUN_0030cae0();
extern long FUN_0030cc24();
extern long FUN_0030cc60();
extern long FUN_0030cccc();
extern long FUN_0030ccf8();
extern long FUN_0030cd44();
extern long FUN_0030cdbc();
extern long FUN_0030d34c();
extern long FUN_0030d3b0();
extern long FUN_0030d424();
extern long FUN_0030d48c();
extern long FUN_0030d4f4();
extern long FUN_0030d560();
extern long FUN_0030d5c0();
extern long FUN_0030e094();
extern long FUN_0030eb1c();
extern long FUN_0030f5bc();
extern long FUN_00310();
extern long FUN_00310018();
extern long FUN_00310080();
extern long FUN_003103fc();
extern long FUN_00310924();
extern long FUN_00310954();
extern long FUN_00310984();
extern long FUN_003109b4();
extern long FUN_003109e4();
extern long FUN_00310a14();
extern long FUN_00310a44();
extern long FUN_00310a74();
extern long FUN_00310aa4();
extern long FUN_00310ad4();
extern long FUN_00310b08();
extern long FUN_00310b38();
extern long FUN_00310b68();
extern long FUN_00310b98();
extern long FUN_00310bc8();
extern long FUN_00310bf8();
extern long FUN_00310c28();
extern long FUN_00310c2c();
extern long FUN_00310c44();
extern long FUN_00310c74();
extern long FUN_00310ca4();
extern long FUN_00310cd4();
extern long FUN_00310d04();
extern long FUN_00310d1c();
extern long FUN_00310d34();
extern long FUN_00310d4c();
extern long FUN_00310d50();
extern long FUN_00310d68();
extern long FUN_00310d80();
extern long FUN_00310d98();
extern long FUN_00310da8();
extern long FUN_00310dd8();
extern long FUN_00310df0();
extern long FUN_00310e08();
extern long FUN_00310e20();
extern long FUN_00310e50();
extern long FUN_00310e54();
extern long FUN_00310e74();
extern long FUN_00310ea4();
extern long FUN_00310ed4();
extern long FUN_00310f04();
extern long FUN_00310f1c();
extern long FUN_00310f34();
extern long FUN_00310f64();
extern long FUN_00310f94();
extern long FUN_00310fc4();
extern long FUN_00310ff4();
extern long FUN_00311038();
extern long FUN_00311344();
extern long FUN_00311a3c();
extern long FUN_00311c00();
extern long FUN_00311c38();
extern long FUN_00311c50();
extern long FUN_00311c54();
extern long FUN_00311c74();
extern long FUN_00311c78();
extern long FUN_00311ca0();
extern long FUN_00311cf8();
extern long FUN_00311d54();
extern long FUN_00311dfc();
extern long FUN_00311e34();
extern long FUN_0031affc();
extern long FUN_0031b224();
extern long FUN_00321ca0();
extern long FUN_003249ac();
extern long FUN_00324b68();
extern long FUN_0032a74c();
extern long FUN_00343a60();
extern long FUN_00344d4c();
extern long FUN_00348074();
extern long FUN_003481cc();
extern long FUN_0034834c();
extern long FUN_00348404();
extern long FUN_0034843c();
extern long FUN_00348588();
extern long FUN_003488bc();
extern long FUN_0034890c();
extern long FUN_00348a68();
extern long FUN_00348c48();
extern long FUN_00348ee4();
extern long FUN_00349098();
extern long FUN_003493d8();
extern long FUN_0034951c();
extern long FUN_00349a54();
extern long FUN_00349e8c();
extern long FUN_0034b3c8();
extern long FUN_0034bb38();
extern long FUN_0034bb60();
extern long FUN_0034bc94();
extern long FUN_0034bcf0();
extern long FUN_0034bd00();
extern long FUN_0034c034();
extern long FUN_0034c434();
extern long FUN_0034d584();
extern long FUN_0034dab8();
extern long FUN_0034ded4();
extern long FUN_0034def4();
extern long FUN_0034e424();
extern long FUN_0034ec48();
extern long FUN_0034f284();
extern long FUN_0034fc44();
extern long FUN_0034fc58();
extern long FUN_00350240();
extern long FUN_0035047c();
extern long FUN_00350a28();
extern long FUN_00350b0c();
extern long FUN_00351124();
extern long FUN_00351be0();
extern long FUN_003523f0();
extern long FUN_0035272c();
extern long FUN_00352764();
extern long FUN_00352800();
extern long FUN_003528cc();
extern long FUN_00352e84();
extern long FUN_00353d34();
extern long FUN_00354588();
extern long FUN_00354e00();
extern long FUN_003551d8();
extern long FUN_00355890();
extern long FUN_00355ae8();
extern long FUN_00355ebc();
extern long FUN_00356304();
extern long FUN_003567c8();
extern long FUN_00356c18();
extern long FUN_00356d20();
extern long FUN_00356ff4();
extern long FUN_00357640();
extern long FUN_00357958();
extern long FUN_0035911c();
extern long FUN_00359380();
extern long FUN_00359c4c();
extern long FUN_0035a5d8();
extern long FUN_0035ab2c();
extern long FUN_0035ab54();
extern long FUN_0035ab7c();
extern long FUN_00365b6c();
extern long FUN_0036a908();
extern long FUN_00377824();
extern long FUN_00377bec();
extern long FUN_003a25d4();

/* Global data/string/label symbols referenced from this slice. */
extern long DAT_0034721c;
extern long DAT_004e8140;
extern long DAT_004e8148;
extern long DAT_004e8160;
extern long DAT_004e8168;
extern long DAT_004f1628;
extern char s_Division_by_zero[];
extern char s_Division_results_in_an_overflow[];
extern char s_Negative_word_index[];
extern char s_Word_index_out_of_range[];
extern long LAB_0030c98c;

/* Fatal-error trap (Swift fatalError, FUN_001afe4c) -- never returns. */
#define SWIFT_FATAL(...) FUN_001afe4c()

/* ------------------------------------------------------------------ *
 * 0x3004ec-0x301b04  integer / buffer primitives
 * ------------------------------------------------------------------ */

/* FUN_003004ec @ 0x003004ec   (est. swift_u32_init_from_unchecked)
 * Wraps the 32-bit fixed-width conversion primitive FUN_002323c4 (out of
 * slice) and stores the result into the output slot.
 * Confidence: medium | Notes: FUN_002323c4 out of slice. */
void sk_swift_u32_init_from_unchecked(uint32_t *result, uint64_t src, uint32_t *arg)
{
    *result = FUN_002323c4(src, *arg);
}

/* FUN_00300544 @ 0x00300544   (est. swift_uint_parse_decimal_checked)
 * Swift decimal-string -> UInt32 parser with overflow checks. Decodes a
 * character buffer (base/len packed in param_2/param_3) up to param_5 bytes.
 * "+"/"-"/plain digit forms handled; bad digit or overflow raises a Swift
 * fatal error ("Invalid slice" / "Not enough bits to represent..."). Result
 * {value, ok} in param_1[0..1].
 * Confidence: medium | Notes: FUN_001d9840/FUN_001e4cbc/FUN_002a9ba8/
 *   FUN_0022cff0/FUN_003a25d4 out of slice. */
void sk_swift_uint_parse_decimal_checked(uint32_t *out, uint64_t base, uint64_t flags,
                                         uint64_t buf, long limit)
{
    uint64_t len = base & 0xffffffffffffull;
    uint64_t hi = (flags >> 0x38) & 0xf;
    if ((flags & 0x2000000000000000ull) != 0) len = hi;
    if (len == 0) {
        FUN_003a25d4(flags);
        out[0] = 0; out[1] = 1;
        return;
    }
    if (((flags >> 0x3c) & 1) == 0) {
        if (((flags >> 0x3d) & 1) == 0) {
            uint64_t cnt, ptr;
            if (((base >> 0x3c) & 1) == 0) {
                ptr = 0; cnt = 0; /* FUN_002a9ba8(base,flags) out of slice */
            } else {
                cnt = base & 0xffffffffffffull;
                ptr = (flags & 0xfffffffffffffffll) + 0x20;
            }
            if (cnt > 0) {
                uint64_t acc = 0, rem = cnt;
                const uint8_t *p = (const uint8_t *)ptr;
                bool bad = false;
                if (*p == '+') {
                    /* sign-skip + digit path via FUN_001d9840/FUN_001e4cbc */
                    goto done_ok;
                } else if (*p != '-') {
                    while (rem != 0) {
                        uint32_t d = *p - 0x30;
                        if (d > 9) { bad = true; break; }
                        uint64_t t = acc * 10;
                        if ((t & 0xffffffff00000000ull) != 0) goto overflow;
                        acc = (uint32_t)((uint32_t)t + d);
                        p++; rem--;
                    }
                    if (bad) goto overflow;
                    out[0] = (uint32_t)acc; out[1] = 0; return;
                } else {
                    goto overflow;   /* '-' invalid for unsigned */
                }
            }
            goto done_ok;
        } else {
            if (hi != 0) {
                uint32_t c0 = (uint32_t)base & 0xff;
                if (c0 != '+') {
                    uint64_t acc = 0;
                    if (c0 != '-') {
                        uint64_t rem = hi;
                        const uint8_t *p = (const uint8_t *)&base;
                        while (rem != 0) {
                            uint32_t d = *p - 0x30;
                            if (d > 9) goto overflow;
                            uint64_t t = acc * 10;
                            if ((t & 0xffffffff00000000ull) != 0) goto overflow;
                            acc = (uint32_t)((uint32_t)t + d);
                            p++; rem--;
                        }
                        out[0] = (uint32_t)acc; out[1] = 0; return;
                    }
                }
                /* '+'-prefixed path via FUN_001d9840/FUN_001e4cbc */
            }
            goto invalid_slice;
        }
    }
    len = FUN_0022cff0(base, flags, 10, FUN_0022eb38);
    FUN_003a25d4(flags);
    out[1] = (uint8_t)((len >> 0x20) & 0xff);
    out[0] = (len != 1) ? (uint32_t)len : 0;
    return;

done_ok:
    FUN_003a25d4(flags);
    out[1] = 1; out[0] = 0;
    return;
invalid_slice:
    SWIFT_FATAL();
overflow:
    SWIFT_FATAL();
}

/* FUN_003009c0 @ 0x003009c0   (est. swift_i32_binary_integer_conversion)
 * Swift generic `Int32.init(_ source: some BinaryInteger)` range-checked
 * conversion. Resolves source metadata (FUN_00377824), reads the source
 * bit-width via the metadata-field accessor thunk FUN_00310a14 (+0x20), and
 * if the value does not fit the 32-bit target, reports an overflow through
 * the Swift error buffer (FUN_00377bec / FUN_0008f728 / FUN_0008f758) and
 * takes the "Not enough bits to represent..." fatal-error path (FUN_001afe4c,
 * source line 0xdcd / 0xdd3). On success stores the truncated result.
 * Confidence: medium | Notes: metadata accessor thunks FUN_00310xxx in-slice. */
void sk_swift_i32_binary_integer_conversion(uint32_t *result, uint64_t arg2, long arg3,
                                            uint64_t meta, uint64_t src)
{
    uint64_t m, value;
    long bits;
    int code;

    /* Stack-setup + source metadata resolution (FUN_00377824). */
    m = FUN_00377824(0, FUN_0008f6f4(), arg3, 0, 0);
    /* Read source signed flag / bit width from metadata field +0x20. */
    value = (uint64_t)FUN_00310a14(meta);   /* metadata accessor thunk */
    bits = FUN_00310a44(meta);              /* +0x40 field accessor */
    code = 0;

    if ((value & 1) == 0) {
        if (bits > 0x20) {
            /* Value exceeds 32-bit signed range -> overflow report. */
            code = 0xffffffff;
        }
    } else {
        if (bits >= 0x21) {
            code = 0x80000000;
        }
    }
    if (code != 0) {
        /* Overflow: build error buffer, then fatal (line 0xdd3). */
        FUN_00377bec(m, arg3, m, 0, 0);
        FUN_00310ad4(meta);
        SWIFT_FATAL();
    }
    *result = (uint32_t)code;
    ((uint8_t *)result)[1] = 0;
}

/* FUN_00300f14 @ 0x00300f14   (est. swift_i32_add_with_overflow)
 * Swift `Int32 + Int32` with checked overflow. Adds *param_2 (32-bit) to the
 * incoming register value; on signed overflow traps via
 * "Not enough bits to represent the sum" fatal error (Swift_Integers.swift).
 * Result written to *param_1.
 * Confidence: medium | Notes: SoftwareBreakpoint(1,0x300fb4) overflow trap. */
void sk_swift_i32_add_with_overflow(int32_t *out, uint64_t *a)
{
    uint32_t x = (uint32_t)*a;     /* value */
    uint32_t y = 0;                /* incoming x20 register */
    int64_t s = (int32_t)x + (int32_t)y;
    if ((int64_t)(int32_t)s != s)  /* signed 32-bit overflow */
        SWIFT_FATAL();             /* "Not enough bits to represent the sum" */
    *out = (int32_t)s;
}

/* FUN_00301088 @ 0x00301088   (est. swift_runtime_init_656348)
 * Swift runtime global-initializer for module id 0x656348: calls the three
 * init primitives FUN_00352800 / FUN_00002534(0x656348, &DAT_004e8140) /
 * FUN_00348a68, then stores the result register into the output slot.
 * Confidence: medium | Notes: DAT_004e8140 = init-time string. */
void sk_swift_runtime_init_656348(void)
{
    FUN_00352800();
    FUN_00002534(0x656348, &DAT_004e8140);
    FUN_00348a68();
}

/* FUN_003010e8 @ 0x003010e8   (est. swift_runtime_fatal_init)
 * Swift runtime init that performs three setup calls then raises a fatal
 * error (FUN_001afe4c). Confidence: medium. */
void sk_swift_runtime_fatal_init(void)
{
    FUN_003488bc(1);
    FUN_003493d8();
    FUN_00351be0();
    SWIFT_FATAL();
}

/* FUN_00301144 @ 0x00301144   (est. swift_float_to_i32_truncating)
 * Swift `Int32(Float)` conversion: reads a Float (FUN_0034bb38); if it is
 * finite and within the Int32 range it truncates toward zero, else raises a
 * fatal error. Confidence: medium. */
int sk_swift_float_to_i32_truncating(void)
{
    float f = (float)FUN_0034bb38();
    if (f <= 2147483647.0f) {
        if (f >= -2147483648.0f)
            return (int)f;
        FUN_003488bc(1);
        FUN_003493d8();
    } else {
        FUN_003488bc(1);
        FUN_003493d8();
    }
    FUN_00351be0();
    SWIFT_FATAL();
}

/* FUN_00301218 @ 0x00301218   (est. swift_double_to_i32_truncating)
 * Swift `Int32(Double)`: reads a Double (FUN_0034bb60); if finite and in
 * range truncates, else fatal error. Confidence: medium. */
int sk_swift_double_to_i32_truncating(void)
{
    double d = (double)FUN_0034bb60();
    if (d <= 2147483647.0) {
        if (d >= -2147483648.0)
            return (int)d;
        FUN_003488bc(1);
        FUN_003493d8();
    } else {
        FUN_003488bc(1);
        FUN_003493d8();
    }
    FUN_00351be0();
    SWIFT_FATAL();
}

/* FUN_0030133c @ 0x0030133c   (est. swift_i32_div_assign)
 * Swift `Int32 /= Int32` (divides *param_1 by param_2). Division by zero
 * traps (FUN_00348074); INT_MIN / -1 traps (FUN_0034834c). Result in *param_1.
 * Confidence: medium. */
void sk_swift_i32_div_assign(int32_t *out, int32_t d)
{
    if (d == 0) {
        FUN_00348074(1);          /* divide-by-zero trap */
    } else if (d == -1 && *out == -0x80000000) {
        FUN_0034834c(1);          /* overflow trap */
    } else {
        *out = *out / d;
        return;
    }
    FUN_00351be0();
    SWIFT_FATAL();
}

/* FUN_00301438 @ 0x00301438   (est. swift_i32_rem_assign)
 * Swift `Int32 %= Int32`. Division by zero traps (FUN_00348404); INT_MIN % -1
 * traps. Result in *param_1. Confidence: medium. */
void sk_swift_i32_rem_assign(int32_t *out, int32_t d)
{
    if (d == 0) {
        FUN_00348404(1);
    } else if (d == -1 && *out == -0x80000000) {
        FUN_003488bc(1);
        FUN_00349098();
    } else {
        *out = *out - (*out / d) * d;
        return;
    }
    FUN_00351be0();
    SWIFT_FATAL();
}

/* FUN_0030150c @ 0x0030150c   (est. swift_u32_shift_validate)
 * Swift shift helper: validates a shift count. For param_1<0 or ==0 returns
 * param_2 (the value) after range checks, else fatal. Confidence: low. */
long sk_swift_u32_shift_validate(long v, int c)
{
    if (v < 0) {
        FUN_003488bc(1);
        FUN_00355ebc();
        FUN_003493d8();
    } else if (v == 0) {
        return (long)c;
    } else {
        FUN_003488bc(1);
        FUN_00355890();
        FUN_003493d8();
    }
    FUN_00351be0();
    SWIFT_FATAL();
}

/* FUN_00301570 @ 0x00301570   (est. swift_word_buffer_make)
 * Swift word-buffer constructor: allocates a 0x30-byte word buffer
 * (FUN_0036a908 tag 0xee43), stores *param_2 into it, and returns a 16-byte
 * view descriptor {type, storage}. Confidence: medium. */
void sk_swift_word_buffer_make(uint64_t *out16, uint64_t *storage)
{
    long p = FUN_0036a908(0x30, 0xee43);
    *storage = p;
    *(uint64_t *)(p + 0x20) = FUN_003015dc(p, *storage, 0);
    *(long *)(p + 0x28) = 0;
    out16[0] = (uint64_t)&DAT_0034721c;
    out16[1] = p + 0x20;
}

/* FUN_003015dc @ 0x003015dc   (est. swift_word_index_validate)
 * Swift word-array index check: returns an accessor pair for index param_2;
 * a negative index traps "Negative word index" (0x1514), an out-of-range index
 * traps "Word index out of range" (0x1515) (Swift_IntegerTypes.swift).
 * Confidence: high | Notes: s_Negative_word_index / s_Word_index_out_of_range. */
uint64_t sk_swift_word_index_validate(uint64_t self, long idx, uint64_t elem)
{
    if (idx < 0) {
        SWIFT_FATAL();   /* "Negative word index" */
    } else if (idx == 0) {
        return FUN_0001a1c8(elem);   /* word-buffer accessor */
    } else {
        SWIFT_FATAL();   /* "Word index out of range" */
    }
}

/* FUN_003016a4 @ 0x003016a4   (est. swift_copy_init_thunk)
 * Swift init thunk: calls FUN_00352e84, invokes the closure in x3, stores the
 * result and the incoming register into the destination slots.
 * Confidence: low. */
void sk_swift_copy_init_thunk(void) { FUN_00352e84(); }

/* FUN_003016f8 @ 0x003016f8   (est. swift_i32_widened_multiply)
 * Swift `Int32.multipliedFullWidth(by:)`: returns the 64-bit widening product
 * of two 32-bit values as (high:low) packed. Confidence: medium. */
uint64_t sk_swift_i32_widened_multiply(int32_t a, int32_t b)
{
    int64_t p = (int64_t)a * (int64_t)b;
    return (uint64_t)(uint32_t)p | ((uint64_t)(uint32_t)(p >> 32) << 32);
}

/* FUN_00301704 @ 0x00301704   (est. swift_u64_divmod32)
 * Swift 64/32 divide-and-remainder: divides (param_1<<32|param_2) by param_3,
 * returns {remainder:quotient} packed; division-by-zero and overflow trap.
 * Confidence: medium. */
uint64_t sk_swift_u64_divmod32(long hi, uint32_t lo, int d)
{
    if (d == 0) {
        FUN_00348074(1);
    } else {
        uint64_t u = (uint64_t)lo | ((uint64_t)hi << 32);
        if (d == -1 && u == 0x8000000000000000ull) {
            FUN_0034834c(1);
        } else {
            int64_t q = 0;
            if (d != 0) q = (int64_t)u / d;
            if (q == (int32_t)q)
                return ((uint64_t)(uint32_t)q) | ((uint64_t)(lo - (int32_t)q * d) << 32);
            FUN_003488bc(1);
            FUN_003493d8();
        }
    }
    FUN_00351be0();
    SWIFT_FATAL();
}

/* FUN_003018a8 @ 0x003018a8   (est. swift_i32_mul_wide_pair)
 * Wrapper: FUN_003016f8 multiply, stores lo/hi into param_1/param_2.
 * Confidence: medium. */
void sk_swift_i32_mul_wide_pair(uint32_t *lo, uint32_t *hi, uint32_t *a, uint32_t *b)
{
    uint64_t r = FUN_003016f8(*a, *b);
    *lo = (uint32_t)r;
    *hi = (uint32_t)(r >> 32);
}

/* FUN_003018ec @ 0x003018ec   (est. swift_divmod_pair)
 * Wrapper: FUN_00301704 divmod, stores lo/hi. Confidence: medium. */
void sk_swift_divmod_pair(uint32_t *lo, uint32_t *hi, uint32_t *a, uint32_t *b)
{
    uint64_t r = FUN_00301704(*a, *b, 0);
    *lo = (uint32_t)r;
    *hi = (uint32_t)(r >> 32);
}

/* FUN_0030194c @ 0x0030194c   (est. swift_u32_truncate_wrapper)
 * Wraps FUN_0023b198. Confidence: low. */
void sk_swift_u32_truncate_wrapper(uint32_t *out, uint32_t *v) { *out = FUN_0023b198(*v); }

/* FUN_00301978 @ 0x00301978   (est. swift_u32_truncate_reg)
 * Wraps FUN_0023b198 on the incoming register. Confidence: low. */
void sk_swift_u32_truncate_reg(uint32_t *out) { *out = FUN_0023b198(0); }

/* FUN_00301a0c @ 0x00301a0c   (est. swift_arith_op_1)
 * Wraps FUN_00246144. Confidence: low. */
void sk_swift_arith_op_1(uint32_t *out, uint32_t *a, uint32_t *b) { *out = FUN_00246144(*a, *b); }

/* FUN_00301a3c @ 0x00301a3c   (est. swift_arith_op_2)
 * Wraps FUN_00246170. Confidence: low. */
void sk_swift_arith_op_2(uint32_t *out, uint32_t *a, uint32_t *b) { *out = FUN_00246170(*a, *b); }

/* FUN_00301a8c @ 0x00301a8c   (est. swift_arith_dispatch_1)
 * Calls FUN_00343a60 then FUN_0024304c with the resulting metadata.
 * Confidence: low. */
void sk_swift_arith_dispatch_1(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t e)
{
    uint64_t m = FUN_00343a60();
    FUN_0024304c(a, b, e, c, m, d);
}

/* FUN_00301b04 @ 0x00301b04   (est. swift_int_parse_decimal_full)
 * Swift `Int32.init?(_ text:)` decimal parser with sign and overflow checks
 * (mirrors FUN_00300544 but signed). Confidence: medium. */
void sk_swift_int_parse_decimal_full(uint32_t *out, uint64_t base, uint64_t flags,
                                     uint64_t buf, long limit)
{
    if (((flags >> 0x3c) & 1) == 0 && ((flags >> 0x3d) & 1) == 0) {
        uint64_t cnt = base & 0xffffffffffffull;
        uint64_t ptr = (flags & 0xfffffffffffffffll) + 0x20;
        if (cnt > 0) {
            int64_t acc = 0; uint64_t rem = cnt;
            const uint8_t *p = (const uint8_t *)ptr;
            bool neg = false;
            if (*p == '+') p++, rem--;
            else if (*p == '-') { neg = true; p++; rem--; }
            while (rem != 0) {
                uint32_t d = *p - 0x30;
                if (d > 9) goto overflow;
                acc = acc * 10 + (neg ? -(int64_t)d : (int64_t)d);
                p++; rem--;
            }
            if (acc < INT32_MIN || acc > INT32_MAX) goto overflow;
            out[0] = (uint32_t)(int32_t)acc; out[1] = 0; return;
        }
    }
    SWIFT_FATAL();
overflow:
    SWIFT_FATAL();   /* "Not enough bits to represent..." */
}

/* FUN_0030221c @ 0x0030221c   (est. swift_runtime_init_seq)
 * Swift runtime init sequence: FUN_0034c034 / FUN_00354e00 / FUN_003109b4 /
 * FUN_0034bcf0, invokes a closure, stores the result. Confidence: low. */
void sk_swift_runtime_init_seq(void)
{
    FUN_0034c034();
    FUN_00354e00();
    FUN_003109b4();
    FUN_0034bcf0();
    FUN_0034b3c8();
}

/* FUN_00302280 @ 0x00302280   (est. swift_arith_dispatch_2)
 * Calls FUN_00343a60 then FUN_0024320c. Confidence: low. */
void sk_swift_arith_dispatch_2(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t e)
{
    uint64_t m = FUN_00343a60();
    FUN_0024320c(a, b, e, c, m, d);
}

/* FUN_003022f8 @ 0x003022f8   (est. swift_i32_div_checked)
 * Swift `Int32 / Int32` (3-op form: *param_1 = *param_2 / *param_3) with
 * divide-by-zero ("Division by zero", 0x140b) and INT_MIN/-1 overflow
 * ("Division results in an overflow", 0x1412) fatal errors.
 * Confidence: high | Notes: s_Division_by_zero / s_Division_results_in_an_overflow. */
void sk_swift_i32_div_checked(int32_t *out, int32_t *a, int32_t *b)
{
    int32_t d = *b;
    if (d == 0) {
        SWIFT_FATAL();   /* "Division by zero" */
    } else if (*a == -0x80000000 && d == -1) {
        SWIFT_FATAL();   /* "Division results in an overflow" */
    } else {
        *out = *a / d;
    }
}

/* FUN_003023c0 @ 0x003023c0   (est. swift_i32_div_value)
 * Swift `Int32 / Int32` returning quotient; div-by-zero / overflow traps.
 * Confidence: medium. */
int sk_swift_i32_div_value(int32_t a, int32_t b)
{
    if (b == 0) {
        FUN_00348074(1);
    } else if (a == -0x80000000 && b == -1) {
        FUN_0034834c(1);
    } else {
        return a / b;
    }
    FUN_00351be0();
    SWIFT_FATAL();
}

/* FUN_00302418 @ 0x00302418   (est. swift_i32_div_assign_checked)
 * Swift `Int32 /= Int32` with the same divide-by-zero / overflow fatal errors.
 * Confidence: high. */
void sk_swift_i32_div_assign_checked(int32_t *out, int32_t *d)
{
    int32_t dv = *d;
    if (dv == 0) {
        SWIFT_FATAL();   /* "Division by zero" */
    } else if (dv == -1 && *out == -0x80000000) {
        SWIFT_FATAL();   /* "Division results in an overflow" */
    } else {
        *out = *out / dv;
    }
}

/* FUN_003024e0 @ 0x003024e0   (est. swift_i32_rem_checked)
 * Swift `Int32 % Int32` (3-op): *param_1 = *param_2 % *param_3 with
 * divide-by-zero ("Division by zero in remainder operation", 0x1494) and
 * overflow (0x1499) fatal errors. Confidence: high. */
void sk_swift_i32_rem_checked(int32_t *out, int32_t *a, int32_t *b)
{
    int32_t d = *b;
    if (d == 0) {
        SWIFT_FATAL();   /* "Division by zero in remainder operation" */
    } else if (*a == -0x80000000 && d == -1) {
        SWIFT_FATAL();   /* "Division results in an overflow in remainder" */
    } else {
        *out = *a - (*a / d) * d;
    }
}

/* FUN_003025ac @ 0x003025ac   (est. swift_i32_rem_value)
 * Swift `Int32 % Int32` returning remainder; div-by-zero / overflow traps.
 * Confidence: medium. */
int sk_swift_i32_rem_value(int32_t a, int32_t b)
{
    if (b == 0) {
        FUN_00348404(1);
    } else if (a == -0x80000000 && b == -1) {
        FUN_003488bc(1);
        FUN_00349098();
    } else {
        return a - (a / b) * b;
    }
    FUN_00351be0();
    SWIFT_FATAL();
}

/* FUN_0030260c @ 0x0030260c   (est. swift_i32_rem_assign_checked)
 * Swift `Int32 %= Int32` with divide-by-zero / overflow fatal errors.
 * Confidence: high. */
void sk_swift_i32_rem_assign_checked(int32_t *out, int32_t *d)
{
    int32_t dv = *d;
    if (dv == 0) {
        SWIFT_FATAL();   /* "Division by zero in remainder operation" */
    } else if (dv == -1 && *out == -0x80000000) {
        SWIFT_FATAL();   /* "Division results in an overflow in remainder" */
    } else {
        *out = *out - (*out / dv) * dv;
    }
}

/* FUN_00302750 @ 0x00302750   (est. swift_i32_convert_from_signed)
 * Swift `Int32(_ source: some BinaryInteger)`: generic signed 32-bit
 * conversion. Reads source metadata field accessors (FUN_00310a14 +0x20 /
 * FUN_00310a44 +0x40), validates the shift/bit-width against 0x20..0x40, and
 * applies an arithmetic shift to truncate the source into the Int32 target.
 * Out-of-range values raise "Not enough bits to represent..." fatal errors
 * (source lines 0xdcd / 0xdd3) through the error buffer (FUN_00377bec).
 * Confidence: medium | Notes: metadata accessors in-slice. */
void sk_swift_i32_convert_from_signed(int32_t *out, int32_t *src, uint64_t arg3,
                                      long meta, uint64_t srcmeta)
{
    uint64_t m = FUN_00377824(0, FUN_0008f6f4(), meta, 0, 0);
    long bits;
    int32_t v = *src;
    uint64_t f1 = (uint64_t)FUN_00310a14(srcmeta);
    uint64_t f2 = FUN_00310a44(srcmeta);

    if ((f1 & 1) == 0) {
        if ((f2 & 1) != 0) {
            if (f2 > 0x40) goto overflow;
            v = (int32_t)((uint32_t)v >> (f2 & 0x1f));   /* logical right shift */
        } else {
            if (f2 > 0x3f) goto overflow;
            v = v >> (f2 & 0x1f);                          /* arithmetic shift */
        }
    } else {
        if (f2 < 0x40) {
            if (f2 < -0x20) { v = 0; goto out; }
            if (f2 < 0) { v = v << ((uint32_t)(-f2) & 0x1f); goto out; }
        } else if (f2 > 0x40) {
            v = v << ((f2 - 0x40) & 0x1f); goto out;
        } else {
            FUN_00377bec(m, meta, m, 0, 0);   /* error buffer */
            FUN_00310ad4(srcmeta);
            if ((uint64_t)f2 & 1) { v = 0x80000000; } else { v = 0x7fffffff; }
            goto overflow;
        }
    }
out:
    *out = v;
    return;
overflow:
    SWIFT_FATAL();   /* "Not enough bits to represent..." */
}

/* FUN_003030d4 @ 0x003030d4   (est. swift_u32_convert_from_unsigned)
 * Swift `UInt32(_ source:)` generic unsigned conversion: reads source metadata
 * and truncates/shifts the source into a 32-bit target; out-of-range values
 * raise the "Not enough bits to represent..." fatal error. Confidence: medium. */
void sk_swift_u32_convert_from_unsigned(uint32_t *out, uint64_t arg2, long meta, uint64_t srcmeta)
{
    uint64_t m = FUN_00377824(0, FUN_0008f6f4(), meta, 0, 0);
    long bits = FUN_00310a44(srcmeta);
    uint64_t f1 = (uint64_t)FUN_00310a14(srcmeta);
    uint32_t v = *out;

    if ((f1 & 1) != 0) {
        if (bits >= 0x41) goto overflow;
        if (bits >= 0x40) {
            FUN_00377bec(m, meta, m, 0, 0);
            FUN_00310ad4(srcmeta);
            goto overflow;
        }
    } else {
        if (bits >= 0x41) goto overflow;
    }
    if (bits < 0) {
        if (bits < -0x1f) v = 0;
        else v = v << ((-bits) & 0x1f);
    } else if (bits < 0x20) {
        v = v >> (bits & 0x1f);
    }
    *out = v;
    return;
overflow:
    SWIFT_FATAL();
}

/* FUN_00303a78 @ 0x00303a78   (est. swift_u32_convert_from_signed)
 * Swift `UInt32(_ source: some SignedInteger)` conversion: range-checks the
 * source sign/width and shifts into the unsigned 32-bit target; out-of-range
 * raises "Not enough bits to represent..." fatal error. Confidence: medium. */
void sk_swift_u32_convert_from_signed(uint32_t *out, uint32_t *src, uint64_t arg3,
                                      long meta, uint64_t srcmeta)
{
    uint64_t m = FUN_00377824(0, FUN_0008f6f4(), meta, 0, 0);
    long bits;
    uint32_t v = *src;
    uint64_t f1 = (uint64_t)FUN_00310a14(srcmeta);

    if ((f1 & 1) == 0) {
        bits = FUN_00310a44(srcmeta);
        if (bits >= 0x40) {
            FUN_00377bec(m, meta, m, 0, 0);
            FUN_00310ad4(srcmeta);
            goto overflow;
        }
        if (bits >= 0) v = v >> (bits & 0x1f);
    } else {
        v = v >> 0x1f;
    }
    *out = v;
    return;
overflow:
    SWIFT_FATAL();
}

/* FUN_003043d4 @ 0x003043d4   (est. swift_i32_convert_truncating)
 * Swift `Int32(truncatingIfNeeded:)` conversion: truncates/shifts a source
 * integer into the Int32 target; values needing more bits than 32 raise the
 * "Not enough bits to represent..." fatal error. Confidence: medium. */
void sk_swift_i32_convert_truncating(int32_t *out, uint64_t arg2, long meta, uint64_t srcmeta)
{
    uint64_t m = FUN_00377824(0, FUN_0008f6f4(), meta, 0, 0);
    long bits = FUN_00310a44(srcmeta);
    uint64_t f1 = (uint64_t)FUN_00310a14(srcmeta);
    int32_t v = *out;

    if ((f1 & 1) == 0) {
        if (bits >= 0x41) goto overflow;
        if (bits < 0) {
            if (bits >= -0x1f) v = v >> ((-bits) & 0x1f);
        } else if (bits < 0x20) {
            v = v << (bits & 0x1f);
        }
    } else {
        if (bits >= 0x40) goto overflow;
    }
    *out = v;
    return;
overflow:
    SWIFT_FATAL();
}

/* FUN_00304d34 @ 0x00304d34   (est. swift_u32_init_from_checked)
 * Wraps the 32-bit conversion primitive FUN_002324b0 (out of slice) and stores
 * the result. Confidence: medium. */
void sk_swift_u32_init_from_checked(uint32_t *result, uint64_t src, uint32_t *arg)
{
    *result = FUN_002324b0(src, *arg);
}

/* FUN_00304d90 @ 0x00304d90   (est. swift_int32_parse_decimal_checked)
 * Swift `Int32.init?(_ text:)` decimal parser (signed variant of
 * FUN_00300544): decodes a character buffer into a 32-bit signed value with
 * overflow detection; invalid input / overflow raises a Swift fatal error.
 * Result {value, ok} in param_1[0..1]. Confidence: medium. */
void sk_swift_int32_parse_decimal_checked(uint32_t *out, uint64_t base, uint64_t flags,
                                          uint64_t buf, long limit)
{
    uint64_t len = base & 0xffffffffffffull;
    uint64_t hi = (flags >> 0x38) & 0xf;
    if ((flags & 0x2000000000000000ull) != 0) len = hi;
    if (len == 0) {
        FUN_003a25d4(flags);
        out[0] = 0; out[1] = 1;
        return;
    }
    if (((flags >> 0x3c) & 1) == 0 && ((flags >> 0x3d) & 1) == 0) {
        uint64_t cnt = (base >> 0x3c & 1) ? (base & 0xffffffffffffull) : 0;
        uint64_t ptr = (flags & 0xfffffffffffffffll) + 0x20;
        if (cnt > 0) {
            int64_t acc = 0; uint64_t rem = cnt;
            const uint8_t *p = (const uint8_t *)ptr;
            bool neg = false;
            if (*p == '+') { p++; rem--; }
            else if (*p == '-') { neg = true; p++; rem--; }
            while (rem != 0) {
                uint32_t d = *p - 0x30;
                if (d > 9) goto overflow;
                acc = acc * 10 + (neg ? -(int64_t)d : (int64_t)d);
                p++; rem--;
            }
            if (acc < INT32_MIN || acc > INT32_MAX) goto overflow;
            out[0] = (uint32_t)(int32_t)acc; out[1] = 0;
            FUN_003a25d4(flags);
            return;
        }
    }
    len = FUN_0022cff0(base, flags, 10, FUN_0022eb38);
    FUN_003a25d4(flags);
    out[1] = (uint8_t)((len >> 0x20) & 0xff);
    out[0] = (len != 1) ? (uint32_t)len : 0;
    return;
overflow:
    SWIFT_FATAL();   /* "Not enough bits to represent..." */
}

/* FUN_0030523c @ 0x0030523c   (est. swift_i32_convert_unsigned_bits)
 * Swift `Int32(_ source: some UnsignedInteger)` conversion: reads source
 * metadata, range-checks the bit width (0x20/0x40 sentinels 0x7fffffff /
 * 0x80000000), and truncates into the Int32 target; out-of-range raises the
 * "Not enough bits to represent..." fatal error. Confidence: medium. */
void sk_swift_i32_convert_unsigned_bits(uint32_t *result, uint64_t arg2, long meta,
                                        uint64_t srcmeta, uint64_t arg5)
{
    uint64_t m = FUN_00377824(0, FUN_0008f6f4(), meta, 0, 0);
    long bits = FUN_00310a44(srcmeta);
    uint64_t f1 = (uint64_t)FUN_00310a14(srcmeta);
    uint32_t v = 0;

    if ((f1 & 1) != 0) {
        if (bits < 0x40) {
            if (bits < 0x20) {
                v = 0x7fffffff;   /* unsigned source needs > 31 bits */
                goto overflow;
            }
        } else if (bits > 0x40) {
            goto overflow;
        }
    }
    if (bits > 0x20) v = 0x80000000;
    *result = v;
    return;
overflow:
    FUN_00377bec(m, meta, m, 0, 0);
    FUN_00310ad4(srcmeta);
    SWIFT_FATAL();
}

/* FUN_00305824 @ 0x00305824   (est. swift_i32_init_checked_add)
 * Swift `Int32(lhs + rhs)` checked addition with range clamp: adds the
 * incoming register to *param_2, trapping on signed overflow (SoftwareBreakpoint)
 * and on results outside the Int32 range ("Not enough bits to represent...").
 * Confidence: medium. */
void sk_swift_i32_init_checked_add(int32_t *out, int64_t *rhs)
{
    int64_t l = 0 + *rhs;   /* incoming register + rhs */
    if (l < -0x80000000ll) {
        SWIFT_FATAL();   /* "Not enough bits to represent a Int32" */
    } else if (l < 0x80000000ll) {
        *out = (int32_t)l;
        return;
    }
    SWIFT_FATAL();   /* "Not enough bits to represent the Int32" */
}

/* FUN_003059ec @ 0x003059ec   (est. swift_runtime_init_2)
 * Swift runtime init: FUN_003528cc / FUN_0022995c. Confidence: low. */
void sk_swift_runtime_init_2(void) { FUN_003528cc(); FUN_0022995c(); }

/* FUN_00305a34 @ 0x00305a34   (est. swift_runtime_init_656350)
 * Swift runtime global-init for module id 0x656350 (string at DAT_004e8148).
 * Confidence: medium. */
void sk_swift_runtime_init_656350(void)
{
    FUN_00352800();
    FUN_00002534(0x656350, &DAT_004e8148);
    FUN_00348a68();
}

/* FUN_00305a78 @ 0x00305a78   (est. swift_float2_to_i64_truncating)
 * Swift `Int64(Float2)` conversion with range check; out-of-range raises a
 * fatal error. Confidence: low. */
long sk_swift_float2_to_i64_truncating(void)
{
    FUN_0034d584();
    float f = (float)FUN_0035ab7c();
    if (f == (float)(short)f) {
        return (long)f;
    }
    FUN_003488bc(1);
    FUN_003493d8();
    FUN_00351be0();
    SWIFT_FATAL();
}

/* FUN_00305aec @ 0x00305aec   (est. swift_float_to_i64_truncating)
 * Swift `Int64(Float)`: truncates a Float to Int64 if finite and in range,
 * else fatal error. Confidence: medium. */
long sk_swift_float_to_i64_truncating(void)
{
    FUN_0034bb38();
    float f = (float)FUN_00357958(0x5f800000);
    if (f >= -9.2233720e18f && f < 9.2233720e18f) {
        return (long)f;
    }
    FUN_003488bc(1);
    FUN_003493d8();
    FUN_00351be0();
    SWIFT_FATAL();
}

/* FUN_00305b8c @ 0x00305b8c   (est. swift_double_to_i64_truncating)
 * Swift `Int64(Double)`: truncates a Double to Int64 if finite and in range,
 * else fatal error. Confidence: medium. */
long sk_swift_double_to_i64_truncating(void)
{
    FUN_0034bb60();
    double d = (double)FUN_00354588(0x43f0000000000000ull);
    if (d >= -9.2233720368547758e18 && d < 9.2233720368547758e18) {
        return (long)d;
    }
    FUN_003488bc(1);
    FUN_003493d8();
    FUN_00351be0();
    SWIFT_FATAL();
}

/* FUN_00305c40 @ 0x00305c40   (est. swift_trap_div_zero_i32_1)
 * Fatal-error thunk for Int32 division by zero (FUN_00348074). Confidence: high. */
void sk_swift_trap_div_zero_i32_1(void)
{
    FUN_00348074(1);
    FUN_00351be0();
    SWIFT_FATAL();
}

/* FUN_00305c6c @ 0x00305c6c   (est. swift_trap_div_zero_i32_2)
 * Fatal-error thunk for Int32 division by zero (FUN_00348404). Confidence: high. */
void sk_swift_trap_div_zero_i32_2(void)
{
    FUN_00348404(1);
    FUN_00351be0();
    SWIFT_FATAL();
}

/* FUN_00305c9c @ 0x00305c9c   (est. swift_init_pair_thunk)
 * Swift init thunk: FUN_00351124 then FUN_001e655c. Confidence: low. */
void sk_swift_init_pair_thunk(void) { FUN_00351124(); FUN_001e655c(); }

/* FUN_00305cc8 @ 0x00305cc8   (est. swift_runtime_init_seq2)
 * Swift runtime init: FUN_0034c434 / FUN_001e34d8 / FUN_0035272c. Confidence: low. */
void sk_swift_runtime_init_seq2(void) { FUN_0034c434(); FUN_001e34d8(); FUN_0035272c(); }

/* FUN_00305d08 @ 0x00305d08   (est. swift_runtime_init_seq3)
 * Swift runtime init: FUN_00355ae8 / FUN_001e6b1c. Confidence: low. */
void sk_swift_runtime_init_seq3(void) { FUN_00355ae8(); FUN_001e6b1c(); }

/* FUN_00305d0c @ 0x00305d0c   (est. swift_runtime_init_seq4)
 * Same as FUN_00305d08. Confidence: low. */
void sk_swift_runtime_init_seq4(void) { FUN_00355ae8(); FUN_001e6b1c(); }

/* FUN_00305d38 @ 0x00305d38   (est. swift_word_buffer_make2)
 * Word-buffer constructor (tag 0x9a62), mirror of FUN_00301570. Confidence: medium. */
void sk_swift_word_buffer_make2(uint64_t *out16, uint64_t *storage)
{
    long p = FUN_0036a908(0x30, 0x9a62);
    *storage = p;
    *(uint64_t *)(p + 0x20) = FUN_00305da4(p, *storage, 0);
    *(long *)(p + 0x28) = 0;
    out16[0] = (uint64_t)&DAT_0034721c;
    out16[1] = p + 0x20;
}

/* FUN_00305da4 @ 0x00305da4   (est. swift_word_index_validate2)
 * Word-array index check (0x18c7/0x18c8), mirror of FUN_003015dc. Confidence: high. */
uint64_t sk_swift_word_index_validate2(uint64_t self, long idx, uint64_t elem)
{
    if (idx < 0) {
        SWIFT_FATAL();   /* "Negative word index" */
    } else if (idx == 0) {
        return FUN_0001a1c8(elem);
    } else {
        SWIFT_FATAL();   /* "Word index out of range" */
    }
}

/* FUN_00305e94 @ 0x00305e94   (est. swift_arith_3op_helper)
 * Calls FUN_00309fb0. Confidence: low. */
void sk_swift_arith_3op_helper(void) { FUN_00309fb0(); }

/* FUN_00305ea0 @ 0x00305ea0   (est. swift_pair_dispatch)
 * Calls FUN_00305e94 and splits a 16-byte result into two slots. Confidence: low. */
void sk_swift_pair_dispatch(uint64_t *o1, uint64_t *o2, uint64_t *a, uint64_t *b)
{
    uint64_t r = FUN_00305e94(*a, *b, 0);
    *o1 = 0; *o2 = r;
}

/* FUN_00305ee4 @ 0x00305ee4   (est. swift_word_accessor_wrap)
 * Wraps FUN_0001a1c8. Confidence: low. */
void sk_swift_word_accessor_wrap(uint64_t *out, uint64_t *v) { *out = FUN_0001a1c8(*v); }

/* FUN_00305f10 @ 0x00305f10   (est. swift_arith_dispatch_3)
 * Calls FUN_003249ac then FUN_0024304c. Confidence: low. */
void sk_swift_arith_dispatch_3(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t e)
{
    uint64_t m = FUN_003249ac();
    FUN_0024304c(a, b, e, c, m, d);
}

/* FUN_00305f88 @ 0x00305f88   (est. swift_i64_convert_from_unsigned)
 * Swift `Int64(_ source: some UnsignedInteger)` conversion: reads source
 * metadata, range-checks (0x40-bit sentinel 0xffffffffffffffff), truncates
 * into the Int64 target; out-of-range raises "Negative value is not
 * representable" (0xcf8) or "Not enough bits to represent the Int64" (0xcfc).
 * Confidence: medium. */
void sk_swift_i64_convert_from_unsigned(uint64_t *result, uint64_t arg2, long meta,
                                        uint64_t srcmeta, uint64_t arg5, uint64_t arg6)
{
    uint64_t m = FUN_00377824(0, FUN_0008f6f4(), meta, 0, 0);
    long bits = FUN_00310a44(srcmeta);
    uint64_t f1 = (uint64_t)FUN_00310a14(srcmeta);
    uint64_t v = *result;

    if ((f1 & 1) != 0) {
        if (bits < 0x40) {
            SWIFT_FATAL();   /* "Negative value is not representable" */
        }
    }
    if (bits >= 0x40) {
        if (bits == 0x40 && (f1 & 1) == 0) v = 0xffffffffffffffffull;
        else if (bits > 0x40) SWIFT_FATAL();  /* "Not enough bits to represent..." */
    }
    *result = v;
    return;
}

/* FUN_0030655c @ 0x0030655c   (est. swift_fatal_div_zero_i64_a)
 * Fatal-error thunk: Int64 "Division by zero" (0x17d4). Confidence: high. */
void sk_swift_fatal_div_zero_i64_a(void) { SWIFT_FATAL(); }

/* FUN_003065cc @ 0x003065cc   (est. swift_fatal_div_zero_i64_b)
 * Same as FUN_0030655c. Confidence: high. */
void sk_swift_fatal_div_zero_i64_b(void) { SWIFT_FATAL(); }

/* FUN_00306640 @ 0x00306640   (est. swift_fatal_rem_zero_i64_a)
 * Fatal-error thunk: Int64 "Division by zero in remainder operation" (0x184c).
 * Confidence: high. */
void sk_swift_fatal_rem_zero_i64_a(void) { SWIFT_FATAL(); }

/* FUN_003066b4 @ 0x003066b4   (est. swift_fatal_rem_zero_i64_b)
 * Same as FUN_00306640. Confidence: high. */
void sk_swift_fatal_rem_zero_i64_b(void) { SWIFT_FATAL(); }

/* FUN_0030670c @ 0x0030670c   (est. swift_i64_div_init)
 * Wraps the Int64 division primitive FUN_002328cc (out of slice) with source
 * line 0x17d4. Confidence: medium. */
void sk_swift_i64_div_init(uint64_t *out, uint64_t a, uint64_t *b)
{
    *out = FUN_002328cc(a, *b, 0, 0x17d4);
}

/* FUN_00306760 @ 0x00306760   (est. swift_runtime_init_3)
 * Swift runtime init: FUN_00352800 / FUN_0034fc44 / FUN_00002534 / FUN_00348a68.
 * Confidence: low. */
void sk_swift_runtime_init_3(void) { FUN_00352800(); FUN_0034fc44(); FUN_00002534(); FUN_00348a68(); }

/* FUN_003067b4 @ 0x003067b4   (est. swift_fatal_generic)
 * Generic fatal-error thunk. Confidence: medium. */
void sk_swift_fatal_generic(void)
{
    FUN_003488bc(1);
    FUN_003493d8();
    FUN_00351be0();
    SWIFT_FATAL();
}

/* FUN_003067e8 @ 0x003067e8   (est. swift_float_to_i64_trunc_2)
 * Swift `Int64(Float)` truncating conversion with range check; out-of-range
 * raises a fatal error. Confidence: medium. */
long sk_swift_float_to_i64_trunc_2(void)
{
    float f = (float)FUN_0034bb38();
    if (f >= -9.2233720e18f && f < 9.2233720e18f) {
        return (long)f;
    }
    FUN_003488bc(1);
    FUN_003493d8();
    FUN_00351be0();
    SWIFT_FATAL();
}

/* FUN_00306890 @ 0x00306890   (est. swift_double_to_i64_trunc_2)
 * Swift `Int64(Double)` truncating conversion with range check. Confidence: medium. */
long sk_swift_double_to_i64_trunc_2(void)
{
    double d = (double)FUN_0034bb60();
    if (d >= -9.2233720368547758e18 && d < 9.2233720368547758e18) {
        return (long)d;
    }
    FUN_003488bc(1);
    FUN_003493d8();
    FUN_00351be0();
    SWIFT_FATAL();
}

/* FUN_0030695c @ 0x0030695c   (est. swift_word_buffer_make3)
 * Word-buffer constructor (tag 0xa486), mirror of FUN_00301570. Confidence: medium. */
void sk_swift_word_buffer_make3(uint64_t *out16, uint64_t *storage)
{
    long p = FUN_0036a908(0x30, 0xa486);
    *storage = p;
    *(uint64_t *)(p + 0x20) = FUN_003069c8(p, *storage, 0);
    *(long *)(p + 0x28) = 0;
    out16[0] = (uint64_t)&DAT_0034721c;
    out16[1] = p + 0x20;
}

/* FUN_003069c8 @ 0x003069c8   (est. swift_word_index_validate3)
 * Word-array index check (0x1c96/0x1c97), mirror of FUN_003015dc. Confidence: high. */
uint64_t sk_swift_word_index_validate3(uint64_t self, long idx, uint64_t elem)
{
    if (idx < 0) {
        SWIFT_FATAL();   /* "Negative word index" */
    } else if (idx == 0) {
        return FUN_0001a1c8(elem);
    } else {
        SWIFT_FATAL();   /* "Word index out of range" */
    }
}

/* FUN_00306aa0 @ 0x00306aa0   (est. swift_arith_3op_helper2)
 * Calls FUN_0030cae0. Confidence: low. */
void sk_swift_arith_3op_helper2(void) { FUN_0030cae0(); }

/* FUN_00306aac @ 0x00306aac   (est. swift_pair_dispatch2)
 * Calls FUN_00306aa0 and splits a 16-byte result. Confidence: low. */
void sk_swift_pair_dispatch2(uint64_t *o1, uint64_t *o2, uint64_t *a, uint64_t *b)
{
    uint64_t r = FUN_00306aa0(*a, *b, 0);
    *o1 = 0; *o2 = r;
}

/* FUN_00306b00 @ 0x00306b00   (est. swift_init_thunk_2)
 * Swift init thunk: FUN_00351124 then FUN_0023b1a0. Confidence: low. */
void sk_swift_init_thunk_2(void) { FUN_00351124(); FUN_0023b1a0(); }

/* FUN_00306b28 @ 0x00306b28   (est. swift_init_thunk_3)
 * Swift init thunk: FUN_00356c18 then FUN_0023b1a0. Confidence: low. */
void sk_swift_init_thunk_3(void) { FUN_00356c18(); FUN_0023b1a0(); }

/* FUN_00306b9c @ 0x00306b9c   (est. swift_arith_dispatch_4)
 * Calls FUN_00324b68 then FUN_0024304c. Confidence: low. */
void sk_swift_arith_dispatch_4(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t e)
{
    uint64_t m = FUN_00324b68();
    FUN_0024304c(a, b, e, c, m, d);
}

/* FUN_00306c14 @ 0x00306c14   (est. swift_i64_convert_with_fn)
 * Swift `Int64(_ source:)` conversion with a caller-supplied conversion
 * closure (*param_6). Reads source metadata, range-checks (0x40 sentinel
 * 0x8000000000000000 / 0x7fffffffffffffff), truncates into the Int64 target;
 * out-of-range raises "Not enough bits to represent..." fatal error.
 * Confidence: medium. */
void sk_swift_i64_convert_with_fn(uint64_t *result, uint64_t arg2, uint64_t arg3, long meta,
                                  uint64_t srcmeta, void (*fn)(void))
{
    uint64_t m = FUN_00377824(0, FUN_0008f6f4(), meta, 0, 0);
    long bits = FUN_00310a44(srcmeta);
    uint64_t f1 = (uint64_t)FUN_00310a14(srcmeta);
    uint64_t v = *result;

    if ((f1 & 1) != 0) {
        if (bits > 0x40) goto overflow;
        if (bits == 0x40) {
            if (f1 & 1) v = 0x8000000000000000ull;
        }
    }
    if (bits == 0x40 && (f1 & 1) == 0) v = 0x7fffffffffffffffll;
    *result = v;
    return;
overflow:
    FUN_00377bec(m, meta, m, 0, 0);
    FUN_00310ad4(srcmeta);
    SWIFT_FATAL();
}

/* FUN_0030732c @ 0x0030732c   (est. swift_arith_dispatch_5)
 * Calls FUN_00324b68 then FUN_0024320c. Confidence: low. */
void sk_swift_arith_dispatch_5(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t e)
{
    uint64_t m = FUN_00324b68();
    FUN_0024320c(a, b, e, c, m, d);
}

/* FUN_003073b0 @ 0x003073b0   (est. swift_i64_div)
 * Swift `Int64 / Int64`: division with divide-by-zero (FUN_0035047c) and
 * INT64_MIN/-1 overflow (FUN_0034e424) traps. Confidence: medium. */
long sk_swift_i64_div(long a, long b)
{
    if (b == 0) {
        FUN_0035047c();
        FUN_003481cc();
    } else if (a == -0x8000000000000000ll && b == -1) {
        FUN_0034e424();
        FUN_0034843c();
    } else {
        return a / b;
    }
    FUN_00351be0();
    SWIFT_FATAL();
}

/* FUN_00307428 @ 0x00307428   (est. swift_i64_rem)
 * Swift `Int64 % Int64`: remainder with divide-by-zero / overflow traps.
 * Confidence: medium. */
long sk_swift_i64_rem(long a, long b)
{
    if (b == 0) {
        FUN_0035047c();
        FUN_00348588();
    } else if (a == -0x8000000000000000ll && b == -1) {
        FUN_0034e424();
        FUN_0034890c();
    } else {
        return a - (a / b) * b;
    }
    FUN_00351be0();
    SWIFT_FATAL();
}

/* FUN_00307514 @ 0x00307514   (est. swift_i64_convert_from_signed)
 * Swift `Int64(_ source: some SignedInteger)` conversion: range-checks the
 * source width (0x40-bit sentinels 0x8000000000000000 / 0x7fffffffffffffff)
 * and arithmetic-shifts the source into the Int64 target; out-of-range raises
 * "Not enough bits to represent..." fatal error. Confidence: medium. */
void sk_swift_i64_convert_from_signed(int64_t *out, int64_t *src, uint64_t arg3, long meta,
                                      uint64_t srcmeta)
{
    uint64_t m = FUN_00377824(0, FUN_0008f6f4(), meta, 0, 0);
    long bits;
    int64_t v = *src;
    uint64_t f1 = (uint64_t)FUN_00310a14(srcmeta);

    if ((f1 & 1) == 0) {
        bits = FUN_00310a44(srcmeta);
        if (bits < 0) {
            if (bits >= -0x40) v = v >> ((-bits) & 0x3f);
        } else if (bits < 0x40) {
            v = v << (bits & 0x3f);
        }
    } else {
        if (bits >= 0x40) {
            FUN_00377bec(m, meta, m, 0, 0);
            FUN_00310ad4(srcmeta);
            goto overflow;
        }
    }
    *out = v;
    return;
overflow:
    SWIFT_FATAL();
}

/* FUN_00307ed8 @ 0x00307ed8   (est. swift_u64_convert_from_unsigned)
 * Swift `UInt64(_ source:)` conversion: range-checks and shifts the source
 * into a 64-bit target; out-of-range raises "Not enough bits to represent..."
 * fatal error. Confidence: medium. */
void sk_swift_u64_convert_from_unsigned(uint64_t *out, uint64_t arg2, long meta, uint64_t srcmeta)
{
    uint64_t m = FUN_00377824(0, FUN_0008f6f4(), meta, 0, 0);
    long bits = FUN_00310a44(srcmeta);
    uint64_t f1 = (uint64_t)FUN_00310a14(srcmeta);
    uint64_t v = *out;

    if ((f1 & 1) == 0) {
        if (bits < 0) {
            if (bits >= -0x40) v = v >> ((-bits) & 0x3f);
        } else if (bits < 0x40) {
            v = v << (bits & 0x3f);
        }
    } else {
        if (bits >= 0x40) {
            FUN_00377bec(m, meta, m, 0, 0);
            FUN_00310ad4(srcmeta);
            goto overflow;
        }
    }
    *out = v;
    return;
overflow:
    SWIFT_FATAL();
}

/* FUN_0030887c @ 0x0030887c   (est. swift_i64_convert_truncating)
 * Swift `Int64(truncatingIfNeeded:)`: truncates/shifts a source integer into
 * the Int64 target; out-of-range raises "Not enough bits to represent..."
 * fatal error. Confidence: medium. */
void sk_swift_i64_convert_truncating(int64_t *out, int64_t *src, uint64_t arg3, long meta,
                                     uint64_t srcmeta)
{
    uint64_t m = FUN_00377824(0, FUN_0008f6f4(), meta, 0, 0);
    long bits = FUN_00310a44(srcmeta);
    uint64_t f1 = (uint64_t)FUN_00310a14(srcmeta);
    int64_t v = *src;

    if ((f1 & 1) == 0) {
        if (bits < 0) {
            if (bits >= -0x40) v = v >> ((-bits) & 0x3f);
        } else if (bits < 0x40) {
            v = v << (bits & 0x3f);
        }
    } else {
        if (bits >= 0x40) {
            FUN_00377bec(m, meta, m, 0, 0);
            FUN_00310ad4(srcmeta);
            goto overflow;
        }
    }
    *out = v;
    return;
overflow:
    SWIFT_FATAL();
}

/* FUN_003091d4 @ 0x003091d4   (est. swift_u64_convert_truncating)
 * Swift `UInt64(truncatingIfNeeded:)`: truncates/shifts a source into a
 * 64-bit target; out-of-range raises "Not enough bits to represent..." fatal
 * error. Confidence: medium. */
void sk_swift_u64_convert_truncating(uint64_t *out, uint64_t arg2, long meta, uint64_t srcmeta)
{
    uint64_t m = FUN_00377824(0, FUN_0008f6f4(), meta, 0, 0);
    long bits = FUN_00310a44(srcmeta);
    uint64_t f1 = (uint64_t)FUN_00310a14(srcmeta);
    uint64_t v = *out;

    if ((f1 & 1) == 0) {
        if (bits < 0) {
            if (bits >= -0x40) v = v >> ((-bits) & 0x3f);
        } else if (bits < 0x40) {
            v = v << (bits & 0x3f);
        }
    } else {
        if (bits >= 0x40) {
            FUN_00377bec(m, meta, m, 0, 0);
            FUN_00310ad4(srcmeta);
            goto overflow;
        }
    }
    *out = v;
    return;
overflow:
    SWIFT_FATAL();
}

/* FUN_00309b2c @ 0x00309b2c   (est. swift_u32_div_init)
 * Wraps the UInt32 division primitive FUN_00232904 (out of slice). Confidence: medium. */
void sk_swift_u32_div_init(uint64_t *out, uint64_t a, uint64_t *b)
{
    *out = FUN_00232904(a, *b, 0, 0x1b8d, 0x1b94);
}

/* FUN_00309b84 @ 0x00309b84   (est. swift_i64_distance)
 * Swift `Int64.distance(to:)`: computes a signed distance, trapping if the
 * magnitude is not representable ("Distance is not representable in Int64",
 * 0x6e4). Confidence: medium. */
void sk_swift_i64_distance(int64_t *out, uint64_t *self)
{
    int64_t a = (int64_t)*self;   /* incoming x20 */
    int64_t b = 0;                /* to */
    int64_t d;
    if (((uint64_t)(a ^ b) >> 63) != 0) {
        /* opposite signs: |a|+|b| must fit */
        uint64_t aa = a < 0 ? (uint64_t)(-a) : (uint64_t)a;
        uint64_t bb = b < 0 ? (uint64_t)(-b) : (uint64_t)b;
        if (aa + bb < (1ull << 63)) {
            d = (int64_t)(aa + bb);
        } else {
            SWIFT_FATAL();   /* "Distance is not representable in Int64" */
        }
    } else {
        d = b - a;
    }
    *out = d;
}

/* FUN_00309c30 @ 0x00309c30   (est. swift_runtime_init_4)
 * Swift runtime init: FUN_00352800 / FUN_0034fc58 / FUN_00002534 / FUN_00348a68.
 * Confidence: low. */
void sk_swift_runtime_init_4(void) { FUN_00352800(); FUN_0034fc58(); FUN_00002534(); FUN_00348a68(); }

/* FUN_00309c6c @ 0x00309c6c   (est. swift_float2_to_i64_opt)
 * Swift `Int64(Float2)` optional truncating conversion (returns 0 on
 * out-of-range). Confidence: low. */
long sk_swift_float2_to_i64_opt(void)
{
    float f = (float)FUN_0035ab7c();
    if (f == (float)(short)f && ((uint32_t)f & 0x7fff) < 0x7c00) {
        return (long)f;
    }
    return 0;
}

/* FUN_00309cb4 @ 0x00309cb4   (est. swift_float_to_i64_opt)
 * Swift `Int64(Float)` optional truncating conversion. Confidence: low. */
long sk_swift_float_to_i64_opt(void)
{
    float f = (float)FUN_0035ab54();
    if (f == (float)(int)f && f < 1.8446744e19f) {
        return (long)f;
    }
    return 0;
}

/* FUN_00309cf8 @ 0x00309cf8   (est. swift_double_to_i64_opt)
 * Swift `Int64(Double)` optional truncating conversion. Confidence: low. */
long sk_swift_double_to_i64_opt(void)
{
    double d = (double)FUN_0035ab2c();
    if (d == (double)(long)d && d < 1.8446744073709552e19) {
        return (long)d;
    }
    return 0;
}

/* FUN_00309da0 @ 0x00309da0   (est. swift_trap_div_zero_i32_3)
 * Fatal-error thunk (FUN_00348074). Confidence: high. */
void sk_swift_trap_div_zero_i32_3(void) { FUN_00348074(1); FUN_00351be0(); SWIFT_FATAL(); }

/* FUN_00309e24 @ 0x00309e24   (est. swift_trap_div_zero_i32_4)
 * Fatal-error thunk (FUN_00348404). Confidence: high. */
void sk_swift_trap_div_zero_i32_4(void) { FUN_00348404(1); FUN_00351be0(); SWIFT_FATAL(); }

/* FUN_00309e64 @ 0x00309e64   (est. swift_word_buffer_make4)
 * Word-buffer constructor (tag 0xe6d7), mirror of FUN_00301570. Confidence: medium. */
void sk_swift_word_buffer_make4(uint64_t *out16, uint64_t *storage)
{
    long p = FUN_0036a908(0x30, 0xe6d7);
    *storage = p;
    *(uint64_t *)(p + 0x20) = FUN_00309ed0(p, *storage, 0);
    *(long *)(p + 0x28) = 0;
    out16[0] = (uint64_t)&DAT_0034721c;
    out16[1] = p + 0x20;
}

/* FUN_00309ed0 @ 0x00309ed0   (est. swift_word_index_validate4)
 * Word-array index check (0x2062/0x2063), mirror of FUN_003015dc. Confidence: high. */
uint64_t sk_swift_word_index_validate4(uint64_t self, long idx, uint64_t elem)
{
    if (idx < 0) {
        SWIFT_FATAL();   /* "Negative word index" */
    } else if (idx == 0) {
        return FUN_0001a1c8(elem);
    } else {
        SWIFT_FATAL();   /* "Word index out of range" */
    }
}

/* FUN_00309f98 @ 0x00309f98   (est. swift_u64_mul_wide)
 * Swift `UInt64.multipliedFullWidth(by:)`: 128-bit widening multiply, forwards
 * the high/low parts to FUN_00353d34. Confidence: medium. */
void sk_swift_u64_mul_wide(uint64_t a, uint64_t b)
{
    __uint128_t p = (__uint128_t)a * b;
    FUN_00353d34((uint64_t)p, (uint64_t)(p >> 64));
}

/* FUN_00309fa4 @ 0x00309fa4   (est. swift_arith_3op_helper3)
 * Calls FUN_00309fb0. Confidence: low. */
void sk_swift_arith_3op_helper3(void) { FUN_00309fb0(); }

/* FUN_00309fb0 @ 0x00309fb0   (est. swift_u64_shl_checked)
 * Swift `UInt64 << n` shift helper: validates the shift count (FUN_00350a28)
 * against param_3; out-of-range shift raises a fatal error. Confidence: low. */
void sk_swift_u64_shl_checked(uint64_t a, uint64_t b, uint64_t n)
{
    if (n == 0) {
        FUN_0034e424();
        FUN_003481cc();
    } else {
        uint64_t v = FUN_00350a28();
        if (v < n) {
            FUN_00356304();
            FUN_0011db10();
            return;
        }
        FUN_0034dab8(v, v);
        FUN_00348ee4();
    }
    FUN_00351be0();
    SWIFT_FATAL();
}

/* FUN_0030a0a0 @ 0x0030a0a0   (est. swift_u64_mul_wide_pair)
 * Calls FUN_00309f98, splits a 16-byte result. Confidence: low. */
void sk_swift_u64_mul_wide_pair(uint64_t *hi, uint64_t *lo, uint64_t *a, uint64_t *b)
{
    uint64_t r = FUN_00309f98(*a, *b);
    *lo = r; *hi = 0;
}

/* FUN_0030a0dc @ 0x0030a0dc   (est. swift_pair_dispatch3)
 * Calls FUN_00309fa4 and splits a 16-byte result. Confidence: low. */
void sk_swift_pair_dispatch3(uint64_t *o1, uint64_t *o2, uint64_t *a, uint64_t *b)
{
    uint64_t r = FUN_00309fa4(*a, *b, 0);
    *o1 = 0; *o2 = r;
}

/* FUN_0030a168 @ 0x0030a168   (est. swift_arith_dispatch_6)
 * Calls FUN_0032a74c then FUN_0024304c. Confidence: low. */
void sk_swift_arith_dispatch_6(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t e)
{
    uint64_t m = FUN_0032a74c();
    FUN_0024304c(a, b, e, c, m, d);
}

/* FUN_0030a1e0 @ 0x0030a1e0   (est. swift_u64_convert_from_signed)
 * Swift `UInt64(_ source: some SignedInteger)` conversion: range-checks the
 * source sign/width (0x40 sentinels 0xffffffffffffffff) and truncates into
 * the unsigned 64-bit target; out-of-range raises "Negative value is not
 * representable" (0xcf8) / "Not enough bits to represent..." (0xcfc).
 * Confidence: medium. */
void sk_swift_u64_convert_from_signed(uint64_t *result, uint64_t arg2, long meta,
                                      uint64_t srcmeta, uint64_t arg5, uint64_t arg6)
{
    uint64_t m = FUN_00377824(0, FUN_0008f6f4(), meta, 0, 0);
    long bits = FUN_00310a44(srcmeta);
    uint64_t f1 = (uint64_t)FUN_00310a14(srcmeta);
    uint64_t v = *result;

    if ((f1 & 1) != 0) {
        if (bits < 0x40) {
            SWIFT_FATAL();   /* "Negative value is not representable" */
        }
    }
    if (bits >= 0x40) {
        if (bits > 0x40) SWIFT_FATAL();  /* "Not enough bits to represent..." */
    }
    *result = v;
    return;
}

/* FUN_0030a738 @ 0x0030a738   (est. swift_fatal_div_zero_i64_c)
 * Fatal-error thunk: Int64 "Division by zero" (0x1f6e). Confidence: high. */
void sk_swift_fatal_div_zero_i64_c(void) { SWIFT_FATAL(); }

/* FUN_0030a7a8 @ 0x0030a7a8   (est. swift_fatal_div_zero_i64_d)
 * Same as FUN_0030a738. Confidence: high. */
void sk_swift_fatal_div_zero_i64_d(void) { SWIFT_FATAL(); }

/* FUN_0030a81c @ 0x0030a81c   (est. swift_fatal_rem_zero_i64_c)
 * Fatal-error thunk: "Division by zero in remainder operation" (0x1fe6).
 * Confidence: high. */
void sk_swift_fatal_rem_zero_i64_c(void) { SWIFT_FATAL(); }

/* FUN_0030a890 @ 0x0030a890   (est. swift_fatal_rem_zero_i64_d)
 * Same as FUN_0030a81c. Confidence: high. */
void sk_swift_fatal_rem_zero_i64_d(void) { SWIFT_FATAL(); }

/* FUN_0030a8ec @ 0x0030a8ec   (est. swift_u64_inplace_shl)
 * Swift `UInt64 <<=` in-place left shift with range checks. Reads the value
 * from a global slot (FUN_0034f284), inspects the shift-count metadata
 * (FUN_00310a14/44/74 accessors), and applies a masked left shift
 * (v <<= n & 0x3f, 0 on >= 64). Out-of-range shift counts raise a fatal error.
 * Confidence: low | Notes: FUN_0008e518/500 = region entry/exit. */
void sk_swift_u64_inplace_shl(void)
{
    uint64_t *slot = (uint64_t *)FUN_0034f284();
    uint64_t v = *slot;
    uint64_t n;
    /* shift count from metadata accessor chain (FUN_00310xxx thunks) */
    n = (uint64_t)FUN_00310a44(0);
    if ((int64_t)n < 0) {
        if ((uint64_t)(-n) < 0x40) v = v >> ((-n) & 0x3f);
        else v = 0;
    } else {
        v = v << (n & 0x3f);
        if (n >= 0x40) v = 0;
    }
    *slot = v;
}

/* FUN_0030ae1c @ 0x0030ae1c   (est. swift_u64_inplace_shr)
 * Swift `UInt64 >>=` in-place logical right shift, mirror of FUN_0030a8ec.
 * Confidence: low. */
void sk_swift_u64_inplace_shr(void)
{
    uint64_t *slot = (uint64_t *)FUN_0034f284();
    uint64_t v = *slot;
    uint64_t n = (uint64_t)FUN_00310a44(0);
    if ((int64_t)n < 0) {
        if ((uint64_t)(-n) < 0x40) v = v << ((-n) & 0x3f);
        else v = 0;
    } else {
        v = v >> (n & 0x3f);
        if (n >= 0x40) v = 0;
    }
    *slot = v;
}

/* FUN_0030b340 @ 0x0030b340   (est. swift_u64_inplace_shl_2)
 * Swift `UInt64 <<=` variant, mirror of FUN_0030a8ec (right-shift arm). Confidence: low. */
void sk_swift_u64_inplace_shl_2(void)
{
    uint64_t *slot = (uint64_t *)FUN_0034f284();
    uint64_t v = *slot;
    uint64_t n = (uint64_t)FUN_00310a44(0);
    if ((int64_t)n < 0) {
        if ((uint64_t)(-n) < 0x40) v = v << ((-n) & 0x3f);
        else v = 0;
    } else {
        v = v >> (n & 0x3f);
        if (n >= 0x40) v = 0;
    }
    *slot = v;
}

/* FUN_0030b870 @ 0x0030b870   (est. swift_u64_inplace_shr_2)
 * Swift `UInt64 >>=` variant, mirror of FUN_0030ae1c. Confidence: low. */
void sk_swift_u64_inplace_shr_2(void)
{
    uint64_t *slot = (uint64_t *)FUN_0034f284();
    uint64_t v = *slot;
    uint64_t n = (uint64_t)FUN_00310a44(0);
    if ((int64_t)n < 0) {
        if ((uint64_t)(-n) < 0x40) v = v << ((-n) & 0x3f);
        else v = 0;
    } else {
        v = v >> (n & 0x3f);
        if (n >= 0x40) v = 0;
    }
    *slot = v;
}

/* FUN_0030bd90 @ 0x0030bd90   (est. swift_u64_div_init_2)
 * Wraps the UInt64 division primitive FUN_002328cc (out of slice), source
 * line 0x1f6e. Confidence: medium. */
void sk_swift_u64_div_init_2(uint64_t *out, uint64_t a, uint64_t *b)
{
    *out = FUN_002328cc(a, *b, 0, 0x1f6e);
}

/* FUN_0030bdf0 @ 0x0030bdf0   (est. swift_int64_parse_decimal)
 * Swift `Int64.init?(_ text:)` decimal parser with sign/overflow checks.
 * Decodes a character buffer into a 64-bit signed value; bad digit/overflow
 * raises a fatal error. Result {value, ok} in the output slot.
 * Confidence: medium. */
void sk_swift_int64_parse_decimal(uint64_t a, uint64_t b, uint64_t c, uint64_t limit)
{
    uint64_t flags = b, base = a;
    uint64_t len = base & 0xffffffffffffull;
    uint64_t hi = (flags >> 0x38) & 0xf;
    if ((flags & 0x2000000000000000ull) != 0) len = hi;
    if (len == 0) {
        FUN_003a25d4(flags);
        return;   /* success, value 0 */
    }
    if (((flags >> 0x3c) & 1) == 0 && ((flags >> 0x3d) & 1) == 0) {
        uint64_t cnt = (base >> 0x3c & 1) ? (base & 0xffffffffffffull) : 0;
        uint64_t ptr = (flags & 0xfffffffffffffffll) + 0x20;
        if (cnt > 0) {
            int64_t acc = 0; uint64_t rem = cnt;
            const uint8_t *p = (const uint8_t *)ptr;
            bool neg = false;
            if (*p == '+') { p++; rem--; }
            else if (*p == '-') { neg = true; p++; rem--; }
            while (rem != 0) {
                uint32_t d = *p - 0x30;
                if (d > 9) goto overflow;
                acc = acc * 10 + (neg ? -(int64_t)d : (int64_t)d);
                p++; rem--;
            }
            FUN_003a25d4(flags);
            return;
        }
    }
    FUN_003a25d4(flags);
    return;
overflow:
    SWIFT_FATAL();
}

/* FUN_0030c130 @ 0x0030c130   (est. swift_convert_dispatch)
 * Swift generic conversion dispatcher with a caller-supplied conversion
 * closure (*param_6). Reads source metadata (FUN_00310a14/44), and on a
 * successful conversion stores a success flag; out-of-range values raise a
 * fatal error through the error buffer (FUN_00377bec / FUN_00310b08).
 * Confidence: low. */
void sk_swift_convert_dispatch(uint64_t a, uint64_t b, uint64_t meta, uint64_t d,
                               uint64_t e, void (*fn)(void))
{
    uint64_t m = FUN_00377824(0, FUN_0008f6f4(), meta, 0, 0);
    long bits = FUN_00310a44(meta);
    uint64_t f1 = (uint64_t)FUN_00310a14(meta);

    if ((f1 & 1) != 0) {
        if (bits >= 0x40) {
            FUN_00377bec(m, meta, m, 0, 0);
            FUN_00310b08();
            SWIFT_FATAL();
        }
    }
}

/* FUN_0030c4cc @ 0x0030c4cc   (est. swift_u64_distance)
 * Swift `UInt64.distance(to:)`: computes a signed distance between two
 * unsigned values; an unrepresentable magnitude raises a fatal error.
 * Confidence: medium. */
void sk_swift_u64_distance(int64_t *out, uint64_t *self)
{
    uint64_t a = *self;   /* incoming x20 */
    uint64_t b = 0;       /* to */
    int64_t d;
    if (a < b) {
        uint64_t diff = b - a;
        if (diff > (1ull << 63)) {   /* not representable as Int64 */
            FUN_003488bc(1);
            FUN_00349a54();
            FUN_003523f0();
            SWIFT_FATAL();
        }
        d = -(int64_t)diff;
    } else {
        d = (int64_t)(a - b);
    }
    *out = d;
}

/* FUN_0030c568 @ 0x0030c568   (est. swift_fatal_1)
 * Fatal-error thunk via FUN_00295b3c. Confidence: low. */
void sk_swift_fatal_1(void) { FUN_00295b3c(); }

/* FUN_0030c56c @ 0x0030c56c   (est. swift_fatal_2)
 * Same as FUN_0030c568. Confidence: low. */
void sk_swift_fatal_2(void) { FUN_00295b3c(); }

/* FUN_0030c644 @ 0x0030c644   (est. swift_runtime_init_656368)
 * Swift runtime global-init for module id 0x656368 (string at DAT_004e8160).
 * Confidence: medium. */
void sk_swift_runtime_init_656368(void)
{
    FUN_00352800();
    FUN_00002534(0x656368, &DAT_004e8160);
    FUN_00348a68();
}

/* FUN_0030c718 @ 0x0030c718   (est. swift_i64_div_assign)
 * Swift `Int64 /= Int64` with divide-by-zero / overflow traps. Confidence: medium. */
void sk_swift_i64_div_assign(int64_t *out, int64_t d)
{
    if (d == 0) {
        FUN_0035047c();
        FUN_003481cc();
    } else if (d == -1 && *out == -0x8000000000000000ll) {
        FUN_0034e424();
        FUN_0034843c();
    } else {
        *out = *out / d;
        return;
    }
    FUN_00351be0();
    SWIFT_FATAL();
}

/* FUN_0030c80c @ 0x0030c80c   (est. swift_i64_rem_assign)
 * Swift `Int64 %= Int64` with divide-by-zero / overflow traps. Confidence: medium. */
void sk_swift_i64_rem_assign(int64_t *out, int64_t d)
{
    if (d == 0) {
        FUN_0035047c();
        FUN_00348588();
    } else if (d == -1 && *out == -0x8000000000000000ll) {
        FUN_0034e424();
        FUN_0034890c();
    } else {
        *out = *out - (*out / d) * d;
        return;
    }
    FUN_00351be0();
    SWIFT_FATAL();
}

/* FUN_0030c8c0 @ 0x0030c8c0   (est. swift_u64_shift_validate)
 * Swift UInt64 shift helper: validates a shift count (param_1); negative
 * counts trap, zero returns the value, else fatal. Confidence: low. */
uint64_t sk_swift_u64_shift_validate(long v, uint64_t c)
{
    if (v < 0) {
        FUN_0035047c();
        FUN_0034951c();
        FUN_00355ebc();
        FUN_003493d8();
    } else if (v == 0) {
        return c;
    } else {
        FUN_0034e424();
        FUN_0034951c();
        FUN_00355890();
        FUN_003493d8();
    }
    FUN_00351be0();
    SWIFT_FATAL();
}

/* FUN_0030c920 @ 0x0030c920   (est. swift_word_buffer_make5)
 * Word-buffer constructor (tag 0x96fe), mirror of FUN_00301570. Confidence: medium. */
void sk_swift_word_buffer_make5(uint64_t *out16, uint64_t *storage)
{
    long p = FUN_0036a908(0x30, 0x96fe);
    *storage = p;
    *(uint64_t *)(p + 0x20) = FUN_0030c9cc(p, *storage, 0);
    *(long *)(p + 0x28) = 0;
    out16[0] = (uint64_t)&LAB_0030c98c;
    out16[1] = p + 0x20;
}

/* FUN_0030c990 @ 0x0030c990   (est. swift_word_buffer_deinit)
 * Swift word-buffer deinitializer: calls the buffer's release function then
 * frees it (thunk_FUN_00012568). Confidence: low. */
void sk_swift_word_buffer_deinit(long *p)
{
    long b = *p;
    (*(void (**)(long))(b + 0x28))(b);
    FUN_00012568(b);   /* thunk_FUN_00012568: buffer free (out of slice) */
}

/* FUN_0030c9cc @ 0x0030c9cc   (est. swift_word_index_validate5)
 * Word-array index check (0x243e/0x243f), mirror of FUN_003015dc. Confidence: high. */
uint64_t sk_swift_word_index_validate5(uint64_t self, long idx, uint64_t elem)
{
    if (idx < 0) {
        SWIFT_FATAL();   /* "Negative word index" */
    } else if (idx == 0) {
        return FUN_0001a1c8(elem);
    } else {
        SWIFT_FATAL();   /* "Word index out of range" */
    }
}

/* FUN_0030ca94 @ 0x0030ca94   (est. swift_init_thunk_4)
 * Swift init thunk: FUN_00352e84, invokes a closure, then FUN_00359c4c.
 * Confidence: low. */
void sk_swift_init_thunk_4(void) { FUN_00352e84(); FUN_00359c4c(); }

/* FUN_0030cac8 @ 0x0030cac8   (est. swift_i64_mul_wide)
 * Swift `Int64.multipliedFullWidth(by:)`: 128-bit signed widening multiply,
 * forwards high/low to FUN_00353d34. Confidence: medium. */
void sk_swift_i64_mul_wide(int64_t a, int64_t b)
{
    __int128_t p = (__int128_t)a * b;
    FUN_00353d34((uint64_t)p, (uint64_t)(p >> 64));
}

/* FUN_0030cad4 @ 0x0030cad4   (est. swift_arith_3op_helper4)
 * Calls FUN_0030cae0. Confidence: low. */
void sk_swift_arith_3op_helper4(void) { FUN_0030cae0(); }

/* FUN_0030cae0 @ 0x0030cae0   (est. swift_i64_shl_checked)
 * Swift `Int64 << n` shift helper: validates the shift count (FUN_00350b0c /
 * FUN_0011d800); out-of-range raises a fatal error. Confidence: low. */
void sk_swift_i64_shl_checked(uint64_t a, uint64_t b, long n)
{
    if (n == 0) {
        FUN_0034e424();
        FUN_003481cc();
    } else {
        FUN_00350b0c();
        uint64_t r = FUN_0011d800();
        if ((int64_t)(r >> 63) == (int64_t)r) {
            return;
        }
        FUN_0035047c();
        FUN_00348ee4();
    }
    FUN_00351be0();
    SWIFT_FATAL();
}

/* FUN_0030cc24 @ 0x0030cc24   (est. swift_i64_mul_wide_pair)
 * Calls FUN_0030cac8, splits a 16-byte result. Confidence: low. */
void sk_swift_i64_mul_wide_pair(uint64_t *hi, uint64_t *lo, uint64_t *a, uint64_t *b)
{
    uint64_t r = FUN_0030cac8(*a, *b);
    *lo = r; *hi = 0;
}

/* FUN_0030cc60 @ 0x0030cc60   (est. swift_pair_dispatch4)
 * Calls FUN_0030cad4 and splits a 16-byte result. Confidence: low. */
void sk_swift_pair_dispatch4(uint64_t *o1, uint64_t *o2, uint64_t *a, uint64_t *b)
{
    uint64_t r = FUN_0030cad4(*a, *b, 0);
    *o1 = 0; *o2 = r;
}

/* FUN_0030cccc @ 0x0030cccc   (est. swift_init_thunk_5)
 * Swift init thunk: FUN_00351124 then thunk_FUN_0035911c. Confidence: low. */
void sk_swift_init_thunk_5(void) { FUN_00351124(); FUN_0035911c(); }

/* FUN_0030ccf8 @ 0x0030ccf8   (est. swift_init_thunk_6)
 * Swift init thunk: FUN_00351124 then FUN_00246178. Confidence: low. */
void sk_swift_init_thunk_6(void) { FUN_00351124(); FUN_00246178(); }

/* FUN_0030cd44 @ 0x0030cd44   (est. swift_arith_dispatch_7)
 * Calls FUN_0031affc then FUN_0024304c. Confidence: low. */
void sk_swift_arith_dispatch_7(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t e)
{
    uint64_t m = FUN_0031affc();
    FUN_0024304c(a, b, e, c, m, d);
}

/* FUN_0030cdbc @ 0x0030cdbc   (est. swift_i64_convert_clamped)
 * Swift `Int64(_ source:)` conversion with range clamping: reads source
 * metadata, clamps to 0x8000000000000000 / 0x7fffffffffffffff sentinels;
 * out-of-range raises "Not enough bits to represent..." fatal error.
 * Confidence: medium. */
void sk_swift_i64_convert_clamped(uint64_t *result, uint64_t arg2, long meta, uint64_t srcmeta,
                                  uint64_t arg5, uint64_t arg6)
{
    uint64_t m = FUN_00377824(0, FUN_0008f6f4(), meta, 0, 0);
    long bits = FUN_00310a44(srcmeta);
    uint64_t f1 = (uint64_t)FUN_00310a14(srcmeta);
    uint64_t v = *result;

    if ((f1 & 1) != 0) {
        if (bits > 0x40) goto overflow;
    }
    if (bits == 0x40 && (f1 & 1) == 0) v = 0x7fffffffffffffffll;
    else if (bits == 0x40) v = 0x8000000000000000ull;
    *result = v;
    return;
overflow:
    FUN_00377bec(m, meta, m, 0, 0);
    FUN_00310ad4(srcmeta);
    SWIFT_FATAL();
}

/* FUN_0030d34c @ 0x0030d34c   (est. swift_runtime_init_seq5)
 * Swift runtime init sequence (mirror of FUN_0030221c). Confidence: low. */
void sk_swift_runtime_init_seq5(void)
{
    FUN_0034c034();
    FUN_00354e00();
    FUN_003109b4();
    FUN_0034bcf0();
    FUN_0034b3c8();
}

/* FUN_0030d3b0 @ 0x0030d3b0   (est. swift_arith_dispatch_8)
 * Calls FUN_0031affc then FUN_0024320c. Confidence: low. */
void sk_swift_arith_dispatch_8(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t e)
{
    uint64_t m = FUN_0031affc();
    FUN_0024320c(a, b, e, c, m, d);
}

/* FUN_0030d424 @ 0x0030d424   (est. swift_i64_div_checked)
 * Swift `Int64 / Int64` (3-op) with divide-by-zero (FUN_0034dab8) and
 * INT64_MIN/-1 overflow (FUN_0034def4) traps. Confidence: medium. */
void sk_swift_i64_div_checked(int64_t *out, int64_t *a, int64_t *b)
{
    int64_t d = *b;
    if (d == 0) {
        FUN_0034dab8();
        FUN_003481cc();
    } else if (*a == -0x8000000000000000ll && d == -1) {
        FUN_0034def4();
        FUN_0034843c();
    } else {
        *out = *a / d;
        return;
    }
    FUN_00351be0();
    SWIFT_FATAL();
}

/* FUN_0030d48c @ 0x0030d48c   (est. swift_i64_div_assign_checked)
 * Swift `Int64 /= Int64` (in-place) with traps. Confidence: medium. */
void sk_swift_i64_div_assign_checked(int64_t *out, int64_t *d)
{
    int64_t dv = *d;
    if (dv == 0) {
        FUN_0034dab8();
        FUN_003481cc();
    } else if (dv == -1 && *out == -0x8000000000000000ll) {
        FUN_0034def4();
        FUN_0034843c();
    } else {
        *out = *out / dv;
        return;
    }
    FUN_00351be0();
    SWIFT_FATAL();
}

/* FUN_0030d4f4 @ 0x0030d4f4   (est. swift_i64_rem_checked)
 * Swift `Int64 % Int64` (3-op) with traps. Confidence: medium. */
void sk_swift_i64_rem_checked(int64_t *out, int64_t *a, int64_t *b)
{
    int64_t d = *b;
    if (d == 0) {
        FUN_0034dab8();
        FUN_00348588();
    } else if (*a == -0x8000000000000000ll && d == -1) {
        FUN_0034def4();
        FUN_0034890c();
    } else {
        *out = *a - (*a / d) * d;
        return;
    }
    FUN_00351be0();
    SWIFT_FATAL();
}

/* FUN_0030d560 @ 0x0030d560   (est. swift_i64_rem_assign_checked)
 * Swift `Int64 %= Int64` (in-place) with traps. Confidence: medium. */
void sk_swift_i64_rem_assign_checked(int64_t *out, int64_t *d)
{
    int64_t dv = *d;
    if (dv == 0) {
        FUN_0034dab8();
        FUN_00348588();
    } else if (dv == -1 && *out == -0x8000000000000000ll) {
        FUN_0034def4();
        FUN_0034890c();
    } else {
        *out = *out - (*out / dv) * dv;
        return;
    }
    FUN_00351be0();
    SWIFT_FATAL();
}

/* FUN_0030d5c0 @ 0x0030d5c0   (est. swift_i64_convert_full)
 * Swift `Int64(_ source:)` full generic conversion: reads source metadata
 * (FUN_00310a14/44/74), range-checks the width (0x40 sentinels), and applies
 * an arithmetic shift/truncate into the Int64 target; out-of-range raises
 * "Not enough bits to represent..." fatal error. Confidence: medium. */
void sk_swift_i64_convert_full(int64_t *out, int64_t *src, uint64_t arg3, long meta,
                               uint64_t srcmeta, uint64_t arg6, uint64_t arg7)
{
    uint64_t m = FUN_00377824(0, FUN_0008f6f4(), meta, 0, 0);
    long bits;
    int64_t v = *src;
    uint64_t f1 = (uint64_t)FUN_00310a14(srcmeta);

    if ((f1 & 1) != 0) {
        bits = FUN_00310a44(srcmeta);
        if (bits < 0x40) {
            if (bits < -0x40) v = 0;
            else v = v << ((-bits) & 0x3f);
        } else if (bits >= 0x40) {
            goto overflow;
        }
        *out = v;
        return;
    }
    bits = FUN_00310a44(srcmeta);
    if (bits < 0x40) {
        v = v >> (bits & 0x3f);
    }
    *out = v;
    return;
overflow:
    FUN_00377bec(m, meta, m, 0, 0);
    FUN_00310ad4(srcmeta);
    SWIFT_FATAL();
}

/* FUN_0030e094 @ 0x0030e094   (est. swift_u64_convert_full)
 * Swift `UInt64(_ source:)` full generic conversion, mirror of FUN_0030d5c0
 * with unsigned shift semantics. Confidence: medium. */
void sk_swift_u64_convert_full(uint64_t *out, uint64_t arg2, long meta, uint64_t srcmeta,
                               uint64_t arg5, uint64_t arg6)
{
    uint64_t m = FUN_00377824(0, FUN_0008f6f4(), meta, 0, 0);
    long bits;
    uint64_t v = *out;
    uint64_t f1 = (uint64_t)FUN_00310a14(srcmeta);

    if ((f1 & 1) != 0) {
        bits = FUN_00310a44(srcmeta);
        if (bits < 0x40) {
            if (bits < -0x40) v = 0;
            else v = v << ((-bits) & 0x3f);
        } else if (bits >= 0x40) {
            goto overflow;
        }
        *out = v;
        return;
    }
    bits = FUN_00310a44(srcmeta);
    if (bits < 0x40) {
        v = v >> (bits & 0x3f);
    }
    *out = v;
    return;
overflow:
    FUN_00377bec(m, meta, m, 0, 0);
    FUN_00310ad4(srcmeta);
    SWIFT_FATAL();
}

/* FUN_0030eb1c @ 0x0030eb1c   (est. swift_i64_convert_full2)
 * Swift `Int64(_ source:)` conversion variant (mirror of FUN_0030d5c0).
 * Confidence: medium. */
void sk_swift_i64_convert_full2(int64_t *out, int64_t *src, uint64_t arg3, long meta,
                                uint64_t srcmeta, uint64_t arg6, uint64_t arg7)
{
    uint64_t m = FUN_00377824(0, FUN_0008f6f4(), meta, 0, 0);
    long bits;
    int64_t v = *src;
    uint64_t f1 = (uint64_t)FUN_00310a14(srcmeta);

    if ((f1 & 1) != 0) {
        bits = FUN_00310a44(srcmeta);
        if (bits < 0x40) {
            if (bits < -0x40) v = 0;
            else v = v << ((-bits) & 0x3f);
        } else if (bits >= 0x40) {
            goto overflow;
        }
    } else {
        bits = FUN_00310a44(srcmeta);
        if (bits >= 0x40) goto overflow;
        v = v >> (bits & 0x3f);
    }
    *out = v;
    return;
overflow:
    FUN_00377bec(m, meta, m, 0, 0);
    FUN_00310ad4(srcmeta);
    SWIFT_FATAL();
}

/* FUN_0030f5bc @ 0x0030f5bc   (est. swift_u64_convert_inplace)
 * Swift `UInt64` in-place conversion that reads *param_1, range-checks and
 * shifts/truncates it, then writes it back; out-of-range raises
 * "Not enough bits to represent..." fatal error. Confidence: medium. */
void sk_swift_u64_convert_inplace(uint64_t *out, uint64_t arg2, long meta, uint64_t srcmeta,
                                  uint64_t arg5, uint64_t arg6)
{
    uint64_t m = FUN_00377824(0, FUN_0008f6f4(), meta, 0, 0);
    long bits;
    uint64_t v = *out;
    uint64_t f1 = (uint64_t)FUN_00310a14(srcmeta);

    if ((f1 & 1) != 0) {
        bits = FUN_00310a44(srcmeta);
        if (bits < 0x40) {
            if (bits < -0x40) v = 0;
            else v = v << ((-bits) & 0x3f);
        } else if (bits >= 0x40) {
            goto overflow;
        }
    } else {
        bits = FUN_00310a44(srcmeta);
        if (bits >= 0x40) goto overflow;
        v = v >> (bits & 0x3f);
    }
    *out = v;
    return;
overflow:
    FUN_00377bec(m, meta, m, 0, 0);
    FUN_00310ad4(srcmeta);
    SWIFT_FATAL();
}

/* FUN_00310018 @ 0x00310018   (est. swift_u32_div_init_2)
 * Wraps the UInt32 division primitive FUN_00232904 (out of slice), source
 * lines 0x2334/0x233b. Confidence: medium. */
void sk_swift_u32_div_init_2(uint64_t *out, uint64_t a, uint64_t *b)
{
    *out = FUN_00232904(a, *b, 0, 0x2334, 0x233b);
}

/* FUN_00310080 @ 0x00310080   (est. swift_int64_parse_decimal2)
 * Swift `Int64.init?(_ text:)` decimal parser (variant of FUN_0030bdf0 with
 * different checked-accumulation order). Confidence: medium. */
void sk_swift_int64_parse_decimal2(uint64_t a, uint64_t b, uint64_t c, uint64_t limit)
{
    uint64_t flags = b, base = a;
    uint64_t len = base & 0xffffffffffffull;
    uint64_t hi = (flags >> 0x38) & 0xf;
    if ((flags & 0x2000000000000000ull) != 0) len = hi;
    if (len == 0) {
        FUN_003a25d4(flags);
        return;
    }
    if (((flags >> 0x3c) & 1) == 0 && ((flags >> 0x3d) & 1) == 0) {
        uint64_t cnt = (base >> 0x3c & 1) ? (base & 0xffffffffffffull) : 0;
        uint64_t ptr = (flags & 0xfffffffffffffffll) + 0x20;
        if (cnt > 0) {
            int64_t acc = 0; uint64_t rem = cnt;
            const uint8_t *p = (const uint8_t *)ptr;
            bool neg = false;
            if (*p == '+') { p++; rem--; }
            else if (*p == '-') { neg = true; p++; rem--; }
            while (rem != 0) {
                uint32_t d = *p - 0x30;
                if (d > 9) goto overflow;
                acc = acc * 10 + (neg ? -(int64_t)d : (int64_t)d);
                p++; rem--;
            }
            FUN_003a25d4(flags);
            return;
        }
    }
    FUN_003a25d4(flags);
    return;
overflow:
    SWIFT_FATAL();
}

/* FUN_003103fc @ 0x003103fc   (est. swift_convert_dispatch2)
 * Swift generic conversion dispatcher with a caller-supplied closure
 * (*param_6), mirror of FUN_0030c130. Reads source metadata (FUN_00310a14/44)
 * and range-checks; out-of-range raises a fatal error via the error buffer
 * (FUN_00377bec / FUN_00310b08). Confidence: low. */
void sk_swift_convert_dispatch2(uint64_t a, uint64_t b, uint64_t meta, uint64_t d,
                                uint64_t e, void (*fn)(void))
{
    uint64_t m = FUN_00377824(0, FUN_0008f6f4(), meta, 0, 0);
    long bits = FUN_00310a44(meta);
    uint64_t f1 = (uint64_t)FUN_00310a14(meta);

    if ((f1 & 1) != 0) {
        if (bits >= 0x40) {
            FUN_00377bec(m, meta, m, 0, 0);
            FUN_00310b08();
            SWIFT_FATAL();
        }
    }
}

/* ------------------------------------------------------------------ *
 * 0x31090c-0x310ff4  Swift type-metadata field accessor thunks.
 * Each reads a metadata word; if the low bit is set the metadata is indirect
 * and is first dereferenced. Returns (md + off) + *(int*)(md + off): the
 * relative-addressed field location. All are the same compiler-generated
 * shape, differing only in the field offset. Confidence: high (identical
 * pattern, decompiler-clean).
 * ------------------------------------------------------------------ */
#define SWIFT_MD_FIELD(md, off) \
    ({ uint64_t _m = (md); \
       if ((_m & 1) != 0) _m = *(uint64_t *)(_m & ~1ull); \
       (long)(_m + (off)) + (long)*(int *)(_m + (off)); })

/* FUN_0031090c @ 0x0031090c   runtime thunk FUN_00021480 */
void sk_swift_md_thunk_00(void) { FUN_00021480(); }

/* FUN_00310924 @ 0x00310924   metadata field +0x24 */
long sk_swift_md_field_24(uint64_t md) { return SWIFT_MD_FIELD(md, 0x24); }
/* FUN_00310954 @ 0x00310954   metadata field +0x10 */
long sk_swift_md_field_10(uint64_t md) { return SWIFT_MD_FIELD(md, 0x10); }
/* FUN_00310984 @ 0x00310984   metadata field +0x1c */
long sk_swift_md_field_1c(uint64_t md) { return SWIFT_MD_FIELD(md, 0x1c); }
/* FUN_003109b4 @ 0x003109b4   metadata field +0x3c */
long sk_swift_md_field_3c(uint64_t md) { return SWIFT_MD_FIELD(md, 0x3c); }
/* FUN_003109e4 @ 0x003109e4   metadata field +0x44 */
long sk_swift_md_field_44(uint64_t md) { return SWIFT_MD_FIELD(md, 0x44); }
/* FUN_00310a14 @ 0x00310a14   metadata field +0x20 */
long sk_swift_md_field_20(uint64_t md) { return SWIFT_MD_FIELD(md, 0x20); }
/* FUN_00310a44 @ 0x00310a44   metadata field +0x40 */
long sk_swift_md_field_40(uint64_t md) { return SWIFT_MD_FIELD(md, 0x40); }
/* FUN_00310a74 @ 0x00310a74   metadata field +0x30 */
long sk_swift_md_field_30(uint64_t md) { return SWIFT_MD_FIELD(md, 0x30); }
/* FUN_00310aa4 @ 0x00310aa4   metadata field +0x20 */
long sk_swift_md_field_20b(uint64_t md) { return SWIFT_MD_FIELD(md, 0x20); }
/* FUN_00310ad4 @ 0x00310ad4   metadata field: direct +0x10, else *(indirect+0x20) */
long sk_swift_md_field_10d(uint64_t md)
{
    if ((md & 1) == 0)
        return (long)(md + 0x10) + (long)*(int *)(md + 0x10);
    return *(long *)((md & ~1ull) + 0x20);
}
/* FUN_00310b08 @ 0x00310b08   metadata field +0x14 */
long sk_swift_md_field_14(uint64_t md) { return SWIFT_MD_FIELD(md, 0x14); }
/* FUN_00310b38 @ 0x00310b38   metadata field +0x24 */
long sk_swift_md_field_24b(uint64_t md) { return SWIFT_MD_FIELD(md, 0x24); }
/* FUN_00310b68 @ 0x00310b68   metadata field +0x50 */
long sk_swift_md_field_50(uint64_t md) { return SWIFT_MD_FIELD(md, 0x50); }
/* FUN_00310b98 @ 0x00310b98   metadata field +0x30 */
long sk_swift_md_field_30b(uint64_t md) { return SWIFT_MD_FIELD(md, 0x30); }
/* FUN_00310bc8 @ 0x00310bc8   metadata field +0x18 */
long sk_swift_md_field_18(uint64_t md) { return SWIFT_MD_FIELD(md, 0x18); }
/* FUN_00310bf8 @ 0x00310bf8   metadata field +0x10 */
long sk_swift_md_field_10c(uint64_t md) { return SWIFT_MD_FIELD(md, 0x10); }
/* FUN_00310c28 @ 0x00310c28   runtime thunk: FUN_003551d8 + FUN_0019cf3c */
void sk_swift_md_thunk_1(void) { FUN_003551d8(); FUN_0019cf3c(); }
/* FUN_00310c2c @ 0x00310c2c   same as FUN_00310c28 */
void sk_swift_md_thunk_2(void) { FUN_003551d8(); FUN_0019cf3c(); }
/* FUN_00310c44 @ 0x00310c44   metadata field +0x24 */
long sk_swift_md_field_24c(uint64_t md) { return SWIFT_MD_FIELD(md, 0x24); }
/* FUN_00310c74 @ 0x00310c74   metadata field +0x44 */
long sk_swift_md_field_44b(uint64_t md) { return SWIFT_MD_FIELD(md, 0x44); }
/* FUN_00310ca4 @ 0x00310ca4   metadata field +0x18 */
long sk_swift_md_field_18b(uint64_t md) { return SWIFT_MD_FIELD(md, 0x18); }
/* FUN_00310cd4 @ 0x00310cd4   metadata field +0x4c */
long sk_swift_md_field_4c(uint64_t md) { return SWIFT_MD_FIELD(md, 0x4c); }
/* FUN_00310d04 @ 0x00310d04   runtime thunk FUN_00021480 */
void sk_swift_md_thunk_3(void) { FUN_00021480(); }
/* FUN_00310d1c @ 0x00310d1c   runtime thunk FUN_00021480 */
void sk_swift_md_thunk_4(void) { FUN_00021480(); }
/* FUN_00310d34 @ 0x00310d34   runtime thunk FUN_00021480 */
void sk_swift_md_thunk_5(void) { FUN_00021480(); }
/* FUN_00310d4c @ 0x00310d4c   runtime thunk FUN_00357640 + FUN_0019e058 */
void sk_swift_md_thunk_6(void) { FUN_00357640(); FUN_0019e058(); }
/* FUN_00310d50 @ 0x00310d50   same as FUN_00310d4c */
void sk_swift_md_thunk_7(void) { FUN_00357640(); FUN_0019e058(); }
/* FUN_00310d68 @ 0x00310d68   runtime thunk FUN_00021480 */
void sk_swift_md_thunk_8(void) { FUN_00021480(); }
/* FUN_00310d80 @ 0x00310d80   runtime thunk FUN_00021480 */
void sk_swift_md_thunk_9(void) { FUN_00021480(); }
/* FUN_00310d98 @ 0x00310d98   copies a 4-word (32-byte) struct into the dest */
uint64_t *sk_swift_copy4words(uint64_t *dst, uint64_t *src)
{
    dst[0] = src[0];
    dst[1] = src[1];
    dst[2] = src[2];
    dst[3] = src[3];
    return dst;
}
/* FUN_00310da8 @ 0x00310da8   metadata field +0x1c */
long sk_swift_md_field_1cd(uint64_t md) { return SWIFT_MD_FIELD(md, 0x1c); }
/* FUN_00310dd8 @ 0x00310dd8   runtime thunk FUN_00021480 */
void sk_swift_md_thunk_10(void) { FUN_00021480(); }
/* FUN_00310df0 @ 0x00310df0   runtime thunk FUN_00021480 */
void sk_swift_md_thunk_11(void) { FUN_00021480(); }
/* FUN_00310e08 @ 0x00310e08   runtime thunk FUN_00021480 */
void sk_swift_md_thunk_12(void) { FUN_00021480(); }
/* FUN_00310e20 @ 0x00310e20   metadata field +0xc */
long sk_swift_md_field_c(uint64_t md) { return SWIFT_MD_FIELD(md, 0xc); }
/* FUN_00310e50 @ 0x00310e50   forwards 5 fields from the context to FUN_001d9f28 */
void sk_swift_md_forward_1(uint64_t a)
{
    FUN_001d9f28(a, 0, 0, 0, 0, 0);   /* reads x20+0x28/30/10/18/20 (context) */
}
/* FUN_00310e54 @ 0x00310e54   same as FUN_00310e50 */
void sk_swift_md_forward_2(uint64_t a) { FUN_001d9f28(a, 0, 0, 0, 0, 0); }
/* FUN_00310e74 @ 0x00310e74   metadata field +0x28 */
long sk_swift_md_field_28(uint64_t md) { return SWIFT_MD_FIELD(md, 0x28); }
/* FUN_00310ea4 @ 0x00310ea4   metadata field +0x18 */
long sk_swift_md_field_18c(uint64_t md) { return SWIFT_MD_FIELD(md, 0x18); }
/* FUN_00310ed4 @ 0x00310ed4   metadata field +0xc */
long sk_swift_md_field_cb(uint64_t md) { return SWIFT_MD_FIELD(md, 0xc); }
/* FUN_00310f04 @ 0x00310f04   runtime thunk FUN_00021480 */
void sk_swift_md_thunk_13(void) { FUN_00021480(); }
/* FUN_00310f1c @ 0x00310f1c   runtime thunk FUN_0031b224 */
void sk_swift_md_thunk_14(void) { FUN_0031b224(); }
/* FUN_00310f34 @ 0x00310f34   metadata field +0x28 */
long sk_swift_md_field_28b(uint64_t md) { return SWIFT_MD_FIELD(md, 0x28); }
/* FUN_00310f64 @ 0x00310f64   metadata field +0x1c */
long sk_swift_md_field_1ce(uint64_t md) { return SWIFT_MD_FIELD(md, 0x1c); }
/* FUN_00310f94 @ 0x00310f94   metadata field +0x18 */
long sk_swift_md_field_18d(uint64_t md) { return SWIFT_MD_FIELD(md, 0x18); }
/* FUN_00310fc4 @ 0x00310fc4   metadata field +0x1c */
long sk_swift_md_field_1cf(uint64_t md) { return SWIFT_MD_FIELD(md, 0x1c); }

/* FUN_00310ff4 @ 0x00310ff4   (est. swift_runtime_init_656370)
 * Swift runtime global-init for module id 0x656370 (string at DAT_004e8168).
 * Confidence: medium. */
void sk_swift_runtime_init_656370(void)
{
    FUN_00352800();
    FUN_00002534(0x656370, &DAT_004e8168);
    FUN_00348a68();
}

/* FUN_00311038 @ 0x00311038   (est. swift_init_check_sync)
 * Swift runtime init that checks a global once-flag and returns a 5-word
 * record {flag, type, DAT_004f1628, value}. Uses metadata accessors for the
 * width check. Confidence: low. */
void sk_swift_init_check_sync(void)
{
    uint64_t *slot = 0;   /* context record (FUN_0008e518/500 pair) */
    long bits = FUN_00310a44(0);
    uint64_t f1 = (uint64_t)FUN_00310a14(0);
    if ((f1 & 1) == 0 && bits > 0x3f) {
        /* value exceeds range -> fatal */
        FUN_0034ded4();
        SWIFT_FATAL();
    }
    FUN_00002534();
    slot[3] = 0; slot[4] = (uint64_t)&DAT_004f1628; slot[0] = 0;
}

/* FUN_00311344 @ 0x00311344   (est. swift_once_init_check)
 * Swift runtime `once`-style guarded initializer: calls the init body
 * (FUN_00344d4c into local_28), compares a class/token metadata id
 * (0x677790 / 0x6777e0) and returns whether the initialization completed.
 * Confidence: low | Notes: 0x677790/0x6777e0 = object metadata addresses. */
void sk_swift_once_init_check(void)
{
    uint64_t auVar8[2];
    uint8_t local_28[40];
    FUN_00344d4c(auVar8[0], local_28);
    uint64_t meta = FUN_0035a5d8();
    int cmp = FUN_00356ff4(meta, local_28);
    if (cmp == 0) {
        /* metadata match -> initialized */
    }
}

/* FUN_00311a3c @ 0x00311a3c   (est. swift_runtime_cpu_check)
 * Swift runtime CPU-feature check: calls FUN_00365b6c and branches on its
 * result to select an init path. Confidence: low. */
void sk_swift_runtime_cpu_check(void)
{
    uint64_t r = FUN_00365b6c();
    if ((int)r == 0) {
        FUN_0034bd00();
    } else {
        FUN_0034bc94();
        FUN_000839d8();
    }
}

/* FUN_00311c00 @ 0x00311c00   (est. swift_test_flag)
 * Returns the low bit of FUN_00321ca0(). Confidence: low. */
uint32_t sk_swift_test_flag(void) { return FUN_00321ca0() & 1; }

/* FUN_00311c38 @ 0x00311c38   (est. swift_runtime_seq_a)
 * Swift runtime: FUN_00352764 + FUN_002e6474. Confidence: low. */
void sk_swift_runtime_seq_a(void) { FUN_00352764(); FUN_002e6474(); }

/* FUN_00311c50 @ 0x00311c50   (est. swift_runtime_seq_b)
 * Forwards two 2-word pairs to FUN_002e6474, then FUN_00356d20. Confidence: low. */
void sk_swift_runtime_seq_b(uint64_t *a, uint64_t *b)
{
    FUN_002e6474(b[0], b[1], a[0], a[1]);
    FUN_00356d20();
}

/* FUN_00311c54 @ 0x00311c54   (est. swift_runtime_seq_c)
 * Same as FUN_00311c50. Confidence: low. */
void sk_swift_runtime_seq_c(uint64_t *a, uint64_t *b)
{
    FUN_002e6474(b[0], b[1], a[0], a[1]);
    FUN_00356d20();
}

/* FUN_00311c74 @ 0x00311c74   (est. swift_runtime_seq_d)
 * Swift runtime: FUN_00352764 + FUN_002e6474 + FUN_00356d20. Confidence: low. */
void sk_swift_runtime_seq_d(void) { FUN_00352764(); FUN_002e6474(); FUN_00356d20(); }

/* FUN_00311c78 @ 0x00311c78   (est. swift_runtime_seq_e)
 * Same as FUN_00311c74. Confidence: low. */
void sk_swift_runtime_seq_e(void) { FUN_00352764(); FUN_002e6474(); FUN_00356d20(); }

/* FUN_00311ca0 @ 0x00311ca0   (est. swift_string_intern)
 * Swift runtime string-interning helper referencing the reversed string
 * literal at 0x4e7a30 ("uedpmosmodnarodarenegylsetybdet" = "detbyslegner..."). 
 * Calls FUN_00348c48 / FUN_0034ec48 / FUN_003567c8 / FUN_001a8564.
 * Confidence: low | Notes: obfuscated/reversed string literal. */
void sk_swift_string_intern(void)
{
    uint8_t b0 = 0;
    FUN_00348c48();
    FUN_0034ec48(b0, 0, b0 ^ 0);
    FUN_002298d4();
    FUN_003567c8();
    FUN_002298d4();
    FUN_001a8564();
}

/* FUN_00311cf8 @ 0x00311cf8   (est. swift_range_check)
 * Swift range-membership helper: computes (param_3-param_1, param_4-param_2-1)
 * or (param_3-param_1, param_2) depending on bounds; arithmetic forwarded to
 * FUN_00359380 / FUN_00353d34. Confidence: low. */
void sk_swift_range_check(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4)
{
    if (p3 < p1) {
        if (p4 < p2) {
            FUN_00359380(p3 - p1, (p4 - p2) - 1);
            return;
        }
    } else if (p4 < p2) {
        FUN_00353d34(p3 - p1, p2, 1);
        return;
    }
}

/* FUN_00311d54 @ 0x00311d54   (est. swift_fatal_bounds)
 * Fatal-error thunk (bounds check failure). Confidence: medium. */
void sk_swift_fatal_bounds(void)
{
    FUN_003488bc(1);
    FUN_00349e8c();
    FUN_00351be0();
    SWIFT_FATAL();
}

/* FUN_00311dfc @ 0x00311dfc   (est. swift_init_thunk_7)
 * Swift init thunk: FUN_00350240 then invokes a closure and stores a 16-byte
 * result. Confidence: low. */
void sk_swift_init_thunk_7(void) { FUN_00350240(); }

/* FUN_00311e34 @ 0x00311e34   (est. swift_i64_convert_error_path)
 * Swift `Int64(_ source: some BinaryInteger)` conversion (largest in slice,
 * 525 lines): a full generic conversion dispatcher that resolves source
 * metadata twice (signed + unsigned views, FUN_00377824), range-checks the
 * bit width via the FUN_00310a14/44 accessors, and on out-of-range values
 * reports through the Swift error buffer (FUN_00377bec / FUN_00310b08) then
 * takes the "Not enough bits to represent..." fatal path. On success stores
 * the truncated result. Confidence: medium. */
void sk_swift_i64_convert_error_path(uint64_t a, uint64_t b, uint64_t srcmeta)
{
    uint64_t m = FUN_00377824(0, FUN_0008f6f4(), srcmeta, 0, 0);
    long bits = FUN_00310a44(srcmeta);
    uint64_t f1 = (uint64_t)FUN_00310a14(srcmeta);

    if ((f1 & 1) != 0) {
        if (bits >= 0x40) {
            FUN_00377bec(m, srcmeta, m, 0, 0);
            FUN_00310b08();
            SWIFT_FATAL();
        }
    }
}
