/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel,
 * arm64e, image base 0) — the cL4 (Apple seL4-derived) microkernel (GL1).
 * Ground truth: Ghidra FUN_ names + addresses in program cl4_kernel.raw.
 * All names are estimates unless string/header-matched.
 *
 * This file covers slice 11 of the object/string-machinery region:
 * 0x2eb94c - 0x2ffb78.
 *
 * SeL4/cL4 vocabulary is used for naming: TCB, cap, CNode, IPC, notification,
 * endpoint, vspace, sched, etc. Confidence is medium unless a string matches.
 *
 * The region is dominated by the embedded Swift standard-library runtime:
 * fixed-width integer arithmetic with overflow trapping (Int8/Int16/Int32/
 * Int64/Int128 divide, remainder, shifts, rotate, word-index and
 * double-width div/mod decomposition), float/Double-to-integer conversions
 * with range checks, and integer string parsing (decimal). Such functions are
 * named sk_swift_* accordingly. The Int128 shift/rotate wrappers all share one
 * structural skeleton that walks the operand's bit-width via the
 * FUN_00310a14/00310a44/003109b4/00310a74 method getters and performs a masked
 * shift of the low word at the tail; they differ only in element width and
 * shift direction.
 */

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

/* ================================================================== *
 * Out-of-range cL4/Swift-runtime helpers referenced by this region.
 * FUN_ addresses in comments; bodies owned by sibling SK range workers.
 * ================================================================== */

/* Swift runtime fatal-error trampoline (noreturn). */
extern void sk_fatal_error(unsigned long, unsigned long, ...) __attribute__((noreturn)); /* FUN_001afe4c */

/* Core alloc / lock primitives. */
extern void *sk_alloc(unsigned long size, unsigned long tag);          /* FUN_0036a908 */
extern void *sk_alloc_pages(unsigned long size, unsigned long tag);    /* FUN_0036b270 */
extern void sk_free(void *ptr);                                        /* FUN_0036b118 */
extern void sk_swift_release(unsigned long, ...);                      /* FUN_003a25d4 */
extern unsigned long sk_swift_retain(unsigned long, ...);              /* FUN_0036b270 */
extern unsigned long sk_object_lock(unsigned long, unsigned long,
                                    unsigned long, void *, void *);    /* FUN_00377824 */
extern unsigned long sk_lock_ref(unsigned long, ...);                  /* FUN_00377bec */
extern void sk_lock_release(unsigned long, ...);                       /* FUN_00377dcc */
extern void *sk_current_tcb(void);                                     /* FUN_000867ec */
extern void *sk_cpu(void);                                             /* FUN_0008e518 */
extern void *sk_cpu_curr(void);                                        /* FUN_0008e500 */
extern unsigned long sk_thread_epilogue(unsigned long, ...);           /* FUN_0008e500 */

/* Method-table dispatch slot (global jump indirection). */
extern unsigned long sk_dispatch_slot(void);                           /* DAT_00658c00 */

/* Swift Int128 / fixed-width introspection and shift-with-overflow method
 * getters. Each returns a *method pointer* that the caller then invokes
 * with (value, metadata). Declared variadic to match the observed call
 * shapes. */
extern unsigned long FUN_00310a14(unsigned long _a, ...);   /* isNegative/sign probe  */
extern unsigned long FUN_00310a44(unsigned long _a, ...);   /* bit-width probe        */
extern unsigned long FUN_00310a74(unsigned long _a, ...);   /* shift-with-overflow    */
extern unsigned long FUN_003109b4(unsigned long _a, ...);   /* masked/truncated shift */
extern void          FUN_00310ad4(unsigned long _a, ...);   /* shift completion       */
extern unsigned long FUN_00027754(unsigned long _a, ...);   /* bounds/ub check        */
extern unsigned long FUN_0001df60(unsigned long _a, ...);   /* alloc tag helper       */
extern unsigned long FUN_0008f6c0(unsigned long _a, ...);   /* stack frame push       */
extern unsigned long FUN_0008f6f4(unsigned long _a, ...);   /* stack frame token      */
extern unsigned long FUN_0008f728(unsigned long _a, ...);   /* Int128 copy-into       */
extern unsigned long FUN_0008f758(unsigned long _a, ...);   /* Int128 copy-out        */
extern unsigned long FUN_0016186c(unsigned long _a, ...);   /* Int128 element copy    */
extern unsigned long FUN_0006e778(unsigned long _a, ...);   /* stack alloc            */

/* Swift runtime overflow/div-zero trap helpers (each sets up a fatal). */
extern void FUN_00348074(unsigned long _a, ...);   /* divide-by-zero trap   */
extern void FUN_0034834c(unsigned long _a, ...);   /* div-overflow trap     */
extern void FUN_00348404(unsigned long _a, ...);   /* div-by-zero (rem) trap*/
extern void FUN_003488bc(unsigned long _a, ...);   /* overflow trap         */
extern void FUN_00349098(unsigned long _a, ...);   /* overflow trap (rem)   */
extern void FUN_003493d8(unsigned long _a, ...);   /* overflow trap         */
extern void FUN_00351be0(unsigned long _a, ...);   /* epilogue fatal tail   */
extern void FUN_00355ebc(unsigned long _a, ...);   /* negative-index fatal  */
extern void FUN_00355890(unsigned long _a, ...);   /* out-of-range fatal    */

/* Swift Float / Double -> Int conversion runtime. */
extern unsigned long FUN_0034d584(unsigned long _a, ...);
extern unsigned long FUN_0034bb38(unsigned long _a, ...);
extern unsigned long FUN_0034bb60(unsigned long _a, ...);
extern unsigned long FUN_0035ab7c(unsigned long _a, ...);
extern unsigned long FUN_0035ab54(unsigned long _a, ...);
extern unsigned long FUN_0035ab2c(unsigned long _a, ...);
extern unsigned long FUN_00357958(unsigned long _a, ...);
extern unsigned long FUN_00354588(unsigned long _a, ...);

/* Fixed-width arithmetic primitives. */
extern unsigned long FUN_00324ac0(unsigned long _a, ...);   /* shift op selector   */
extern unsigned long FUN_00343b08(unsigned long _a, ...);   /* shift op selector   */
extern unsigned long FUN_00324d30(unsigned long _a, ...);   /* shift op selector   */
extern unsigned long FUN_00343ab4(unsigned long _a, ...);   /* shift op selector   */
extern unsigned long FUN_0002142c(unsigned long _a, ...);   /* shift op selector   */
extern void          FUN_0024304c(unsigned long _a, ...);   /* Int128 shift/rotate */
extern void          FUN_0024320c(unsigned long _a, ...);   /* Int128 shift/rotate */
extern unsigned long FUN_00232774(unsigned long _a, ...);   /* rotate combine      */
extern unsigned long FUN_002327f0(unsigned long _a, ...);   /* rotate combine      */
extern unsigned long FUN_00232434(unsigned long _a, ...);   /* rotate combine      */
extern unsigned long FUN_00232578(unsigned long _a, ...);   /* rotate combine      */
extern unsigned long FUN_00246144(unsigned long _a, ...);   /* add/rotate pair     */
extern unsigned long FUN_00246170(unsigned long _a, ...);   /* add/rotate pair     */
extern unsigned long FUN_0001a1c8(unsigned long _a, ...);   /* word-index base     */
extern unsigned long FUN_0023b190(unsigned long _a, ...);   /* word-index base     */
extern unsigned long FUN_0035922c(unsigned long _a, ...);   /* low-word div helper */
extern unsigned long FUN_00359238(unsigned long _a, ...);   /* low-word div helper */
extern unsigned long FUN_0022ceac(unsigned long _a, ...);   /* Int8 parse driver   */
extern unsigned long FUN_0022dc54(unsigned long _a, ...);   /* Int8 digit fn       */
extern unsigned long FUN_0022cf60(unsigned long _a, ...);   /* Int16 parse driver  */
extern unsigned long FUN_0022e018(unsigned long _a, ...);   /* Int16 digit fn      */
extern unsigned long FUN_002a9ba8(unsigned long _a, ...);   /* String buffer       */
extern unsigned long FUN_001d9840(unsigned long _a, ...);   /* slice dropFirst     */
extern unsigned long FUN_001e4cbc(unsigned long _a, ...);   /* slice prefix        */

/* Object / string service helpers. */
extern unsigned long FUN_00351124(unsigned long _a, ...);
extern unsigned long FUN_001e655c(unsigned long _a, ...);
extern unsigned long FUN_0034c434(unsigned long _a, ...);
extern unsigned long FUN_001e3600(unsigned long _a, ...);
extern unsigned long FUN_001e3568(unsigned long _a, ...);
extern unsigned long FUN_0035272c(unsigned long _a, ...);
extern unsigned long FUN_001e69f8(unsigned long _a, ...);
extern unsigned long FUN_001e69a8(unsigned long _a, ...);
extern unsigned long FUN_00352e84(unsigned long _a, ...);
extern unsigned long FUN_00352800(unsigned long _a, ...);
extern unsigned long FUN_00002534(unsigned long _a, ...);
extern unsigned long FUN_00348a68(unsigned long _a, ...);
extern unsigned long FUN_003528cc(unsigned long _a, ...);
extern unsigned long FUN_002299cc(unsigned long _a, ...);
extern unsigned long FUN_0034c034(unsigned long _a, ...);
extern unsigned long FUN_00354e00(unsigned long _a, ...);
extern unsigned long FUN_0034bcf0(unsigned long _a, ...);
extern unsigned long FUN_0034b3c8(unsigned long _a, ...);
extern unsigned long FUN_00357ca0(unsigned long _a, ...);
extern unsigned long FUN_0034c7a8(unsigned long _a, ...);
extern unsigned long FUN_0035732c(unsigned long _a, ...);
extern unsigned long FUN_00350230(unsigned long _a, ...);
extern unsigned long FUN_002412d4(unsigned long _a, ...);
extern unsigned long FUN_0034b518(unsigned long _a, ...);
extern unsigned long FUN_00357c44(unsigned long _a, ...);
extern unsigned long FUN_00352c68(unsigned long _a, ...);
extern unsigned long FUN_00208418(unsigned long _a, ...);
extern unsigned long FUN_002acbb8(unsigned long _a, ...);   /* debug print (thunk) */
extern unsigned long FUN_0034c738(unsigned long _a, ...);
extern unsigned long FUN_00357244(unsigned long _a, ...);
extern unsigned long FUN_0035354c(unsigned long _a, ...);
extern unsigned long FUN_0034dc6c(unsigned long _a, ...);
extern unsigned long FUN_00357c38(unsigned long _a, ...);
extern unsigned long FUN_00348dac(unsigned long _a, ...);
extern unsigned long FUN_00356ea8(unsigned long _a, ...);

/* ------------------------------------------------------------------ *
 * Swift fatal-error shorthand used throughout the slice.
 * ------------------------------------------------------------------ */
static inline void sk_swift_trap(void) { __builtin_trap(); }

/* Concatenate two 32-bit words into a 64-bit word (high << 32 | low). */
static inline unsigned long sk_concat44(unsigned long hi, unsigned long lo)
{
    return (hi << 32) | (lo & 0xffffffff);
}
#define CONCAT44(h, l) sk_concat44((unsigned long)(h), (unsigned long)(l))

/* ------------------------------------------------------------------ *
 * In-slice / global data symbols referenced by the bodies.
 * ------------------------------------------------------------------ */
extern unsigned char _DAT_004e8120[];   /* DAT_004e8120 */
extern unsigned char _DAT_004e8128[];   /* DAT_004e8128 */
extern unsigned char _DAT_004e8130[];   /* DAT_004e8130 */
extern unsigned char _DAT_004e8138[];   /* DAT_004e8138 */
extern unsigned char _DAT_0034721c[];   /* DAT_0034721c (vtable sentinel) */
extern void _LAB_00346840(void);        /* LAB_00346840 (dispatch thunk) */


/* 16-byte pair returned by the Int128 word-index builders. */
typedef struct sk_i128 { unsigned long lo, hi; } sk_i128_t;

/* Forward declarations (mutually-referencing word-index builders). */
static sk_i128_t sk_swift_int8_word_index(unsigned long self, long idx, char low);
static sk_i128_t sk_swift_int16_word_index(unsigned long self, long idx, unsigned long low);
static sk_i128_t sk_swift_int16_word_index_b(unsigned long self, long idx, short low);
static sk_i128_t sk_swift_int32_word_index(unsigned long self, long idx, unsigned long low);


/* ------------------------------------------------------------------ *
 * In-slice forward references.
 * ------------------------------------------------------------------ */
extern unsigned long FUN_002efa80(unsigned long _a, ...);   /* low-word div (byte)  */
extern unsigned long FUN_002efa8c(unsigned long _a, ...);   /* byte divmod          */
extern unsigned long FUN_002f4550(unsigned long _a, ...);   /* low-word div (short) */
extern unsigned long FUN_002f455c(unsigned long _a, ...);   /* short divmod         */
extern unsigned long FUN_002fd4b0(unsigned long _a, ...);   /* low-word mul (word)  */
extern unsigned long FUN_002fd4bc(unsigned long _a, ...);   /* word divmod          */
extern unsigned long FUN_002ef948(unsigned long _a, ...);   /* Int8 word index      */
extern unsigned long FUN_002f4450(unsigned long _a, ...);   /* Int16 word index     */
extern unsigned long FUN_002f88ec(unsigned long _a, ...);   /* Int16 word index     */
extern unsigned long FUN_002fd3b8(unsigned long _a, ...);   /* Int32 word index     */

/* ================================================================== *
 * 1. Pure noreturn fatal-error thunks (division-by-zero / overflow).
 * ================================================================== */

/* FUN_002ebfa0 / 0x2ebfa0  (est. sk_swift_divzero_fatal_8a)
 * Fatal "Division by zero" for an Int8/Int128 operation (Swift.Integers,
 * line 0x19d). Confidence: high (string-matched). */
static void sk_swift_divzero_fatal_8a(void)
{
    sk_fatal_error(0xb, 2, "Division by zero", 0x10, 2,
                   "Swift.IntegerTypes", 0x18, 2, 0x19d, 1);
    __builtin_trap();
}

/* FUN_002ec010 @ 0x2ec010  (est. sk_swift_divzero_fatal_8b)
 * Fatal "Division by zero" (same Swift.Integers line 0x19d). High. */
static void sk_swift_divzero_fatal_8b(void)
{
    sk_fatal_error(0xb, 2, "Division by zero", 0x10, 2,
                   "Swift.IntegerTypes", 0x18, 2, 0x19d, 1);
    __builtin_trap();
}

/* FUN_002ec084 @ 0x2ec084  (est. sk_swift_divzero_rem_fatal_8a)
 * Fatal "Division by zero in remainder operation" (Swift.Integers line
 * 0x215). High. */
static void sk_swift_divzero_rem_fatal_8a(void)
{
    sk_fatal_error(0xb, 2, "Division by zero in remainder operation", 0x27, 2,
                   "Swift.IntegerTypes", 0x18, 2, 0x215, 1);
    __builtin_trap();
}

/* FUN_002ec0f8 @ 0x2ec0f8  (est. sk_swift_divzero_rem_fatal_8b)
 * Fatal "Division by zero in remainder operation" (same line 0x215). High. */
static void sk_swift_divzero_rem_fatal_8b(void)
{
    sk_fatal_error(0xb, 2, "Division by zero in remainder operation", 0x27, 2,
                   "Swift.IntegerTypes", 0x18, 2, 0x215, 1);
    __builtin_trap();
}

/* FUN_002f4e40 / 0x2f4e40  (est. sk_swift_divzero_fatal_32a)
 * Fatal "Division by zero" (Swift.Integers line 0x903) for Int32. High. */
static void sk_swift_divzero_fatal_32a(void)
{
    sk_fatal_error(0xb, 2, "Division by zero", 0x10, 2,
                   "Swift.IntegerTypes", 0x18, 2, 0x903, 1);
    __builtin_trap();
}

/* FUN_002f4eec @ 0x2f4eec  (est. sk_swift_divzero_fatal_32b)
 * Fatal "Division by zero" (same line 0x903). High. */
static void sk_swift_divzero_fatal_32b(void)
{
    sk_fatal_error(0xb, 2, "Division by zero", 0x10, 2,
                   "Swift.IntegerTypes", 0x18, 2, 0x903, 1);
    __builtin_trap();
}

/* FUN_002f4f60 @ 0x2f4f60  (est. sk_swift_divzero_rem_fatal_32a)
 * Fatal "Division by zero in remainder operation" (line 0x97b). High. */
static void sk_swift_divzero_rem_fatal_32a(void)
{
    sk_fatal_error(0xb, 2, "Division by zero in remainder operation", 0x27, 2,
                   "Swift.IntegerTypes", 0x18, 2, 0x97b, 1);
    __builtin_trap();
}

/* FUN_002f5014 @ 0x2f5014  (est. sk_swift_divzero_rem_fatal_32b)
 * Fatal "Division by zero in remainder operation" (same line 0x97b). High. */
static void sk_swift_divzero_rem_fatal_32b(void)
{
    sk_fatal_error(0xb, 2, "Division by zero in remainder operation", 0x27, 2,
                   "Swift.IntegerTypes", 0x18, 2, 0x97b, 1);
    __builtin_trap();
}

/* FUN_002fdd44 / 0x2fdd44  (est. sk_swift_divzero_fatal_64a)
 * Fatal "Division by zero" (Swift.Integers line 0x1069) for Int64. High. */
static void sk_swift_divzero_fatal_64a(void)
{
    sk_fatal_error(0xb, 2, "Division by zero", 0x10, 2,
                   "Swift.IntegerTypes", 0x18, 2, 0x1069, 1);
    __builtin_trap();
}

/* FUN_002fddb4 @ 0x2fddb4  (est. sk_swift_divzero_fatal_64b)
 * Fatal "Division by zero" (same line 0x1069). High. */
static void sk_swift_divzero_fatal_64b(void)
{
    sk_fatal_error(0xb, 2, "Division by zero", 0x10, 2,
                   "Swift.IntegerTypes", 0x18, 2, 0x1069, 1);
    __builtin_trap();
}

/* FUN_002fde28 @ 0x2fde28  (est. sk_swift_divzero_rem_fatal_64a)
 * Fatal "Division by zero in remainder operation" (line 0x10e1). High. */
static void sk_swift_divzero_rem_fatal_64a(void)
{
    sk_fatal_error(0xb, 2, "Division by zero in remainder operation", 0x27, 2,
                   "Swift.IntegerTypes", 0x18, 2, 0x10e1, 1);
    __builtin_trap();
}

/* FUN_002fde9c @ 0x2fde9c  (est. sk_swift_divzero_rem_fatal_64b)
 * Fatal "Division by zero in remainder operation" (same line 0x10e1). High. */
static void sk_swift_divzero_rem_fatal_64b(void)
{
    sk_fatal_error(0xb, 2, "Division by zero in remainder operation", 0x27, 2,
                   "Swift.IntegerTypes", 0x18, 2, 0x10e1, 1);
    __builtin_trap();
}

/* ================================================================== *
 * 2. Swift runtime trap calls that end in the generic noreturn fatal.
 * ================================================================== */

/* FUN_002f41cc @ 0x2f41cc  (est. sk_swift_divzero_runtime_trap)
 * Trap: divide-by-zero runtime helper FUN_00348074(1), then noreturn.
 * Confidence: high. */
static void sk_swift_divzero_runtime_trap(void)
{
    FUN_00348074(1);
    FUN_00351be0(0);
    __builtin_trap();
}

/* FUN_002f42b0 @ 0x2f42b0  (est. sk_swift_divzero_rem_runtime_trap)
 * Trap: remainder divide-by-zero helper FUN_00348404(1), then noreturn.
 * Confidence: high. */
static void sk_swift_divzero_rem_runtime_trap(void)
{
    FUN_00348404(1);
    FUN_00351be0(0);
    __builtin_trap();
}

/* FUN_002f4eb0 @ 0x2f4eb0  (est. sk_swift_divzero_runtime_trap_b)
 * Trap: divide-by-zero runtime helper FUN_00348074(1). High. */
static void sk_swift_divzero_runtime_trap_b(void)
{
    FUN_00348074(1);
    FUN_00351be0(0);
    __builtin_trap();
}

/* FUN_002f4fd4 @ 0x2f4fd4  (est. sk_swift_divzero_rem_runtime_trap_b)
 * Trap: remainder divide-by-zero helper FUN_00348404(1). High. */
static void sk_swift_divzero_rem_runtime_trap_b(void)
{
    FUN_00348404(1);
    FUN_00351be0(0);
    __builtin_trap();
}

/* FUN_002fd220 @ 0x2fd220  (est. sk_swift_divzero_rem_runtime_trap_32)
 * Trap: remainder divide-by-zero helper FUN_00348404(1) for Int32. High. */
static void sk_swift_divzero_rem_runtime_trap_32(void)
{
    FUN_00348404(1);
    FUN_00351be0(0);
    __builtin_trap();
}

/* ================================================================== *
 * 3. Int8 fixed-width divide / remainder with overflow trapping.
 * ================================================================== */

/* FUN_002ef628 @ 0x2ef628  (est. sk_swift_divmod_int8)
 * In-place Int8 division *param_1 /= param_2. Traps on divide-by-zero and on
 * the INT8_MIN / -1 overflow case. Confidence: high (textbook Swift trap
 * div). */
static void sk_swift_div_int8(char *self, char divisor)
{
    char q;
    if (divisor == '\0') {
        FUN_00348074(1);
    } else {
        if ((divisor != -1) || (*self != -0x80)) {
            q = '\0';
            if (divisor != '\0') q = *self / divisor;
            *self = q;
            return;
        }
        FUN_0034834c(1);
    }
    FUN_00351be0(0);
    __builtin_trap();
}

/* FUN_002ef770 @ 0x2ef770  (est. sk_swift_rem_int8)
 * In-place Int8 remainder *self %= divisor. Traps on zero divisor and on
 * INT8_MIN / -1. Confidence: high. */
static void sk_swift_rem_int8(char *self, char divisor)
{
    char v, q;
    if (divisor == '\0') {
        FUN_00348404(1);
    } else {
        v = *self;
        if ((divisor != -1) || (v != -0x80)) {
            q = '\0';
            if (divisor != '\0') q = v / divisor;
            *self = v - q * divisor;
            return;
        }
        FUN_003488bc(1);
        FUN_00349098(0);
    }
    FUN_00351be0(0);
    __builtin_trap();
}

/* FUN_002f0690 @ 0x2f0690  (est. sk_swift_div_int8_inout)
 * Int8 division storing to *out: *out = *lhs / *rhs. Fatal-errors on zero
 * divisor or overflow. Confidence: high. */
static void sk_swift_div_int8_inout(char *out, char *lhs, char *rhs)
{
    char v, q;
    v = *rhs;
    if (v == '\0') {
        sk_fatal_error(0xb, 2, "Division by zero", 0x10, 2,
                       "Swift.IntegerTypes", 0x18, 2, 0x53a, 1);
        __builtin_trap();
    }
    if ((*lhs != -0x80) || (v != -1)) {
        q = '\0';
        if (v != '\0') q = *lhs / v;
        *out = q;
        return;
    }
    sk_fatal_error(0xb, 2, "Division results in an overflow", 0x1f, 2,
                   "Swift.IntegerTypes", 0x18, 2, 0x541, 1);
    __builtin_trap();
}

/* FUN_002f0760 @ 0x2f0760  (est. sk_swift_div_int8_return)
 * Int8 division returning the quotient. Traps on zero divisor / overflow.
 * Confidence: high. */
static int sk_swift_div_int8_return(char lhs, char rhs)
{
    int q;
    if (rhs == '\0') {
        FUN_00348074(1);
    } else {
        if ((lhs != -0x80) || (rhs != -1)) {
            q = 0;
            if (rhs != 0) q = (int)lhs / (int)rhs;
            return q;
        }
        FUN_0034834c(1);
    }
    FUN_00351be0(0);
    __builtin_trap();
}

/* FUN_002f07cc @ 0x2f07cc  (est. sk_swift_div_int8_inout_b)
 * In-place Int8 division *self /= *rhs. Fatal-errors on zero/overflow.
 * Confidence: high. */
static void sk_swift_div_int8_inout_b(char *self, char *rhs)
{
    char v, q;
    v = *rhs;
    if (v == '\0') {
        sk_fatal_error(0xb, 2, "Division by zero", 0x10, 2,
                       "Swift.IntegerTypes", 0x18, 2, 0x53a, 1);
        __builtin_trap();
    }
    if ((v != -1) || (*self != -0x80)) {
        q = '\0';
        if (v != '\0') q = *self / v;
        *self = q;
        return;
    }
    sk_fatal_error(0xb, 2, "Division results in an overflow", 0x1f, 2,
                   "Swift.IntegerTypes", 0x18, 2, 0x541, 1);
    __builtin_trap();
}

/* FUN_002f089c @ 0x2f089c  (est. sk_swift_rem_int8_inout)
 * Int8 remainder: *out = *lhs % *rhs. Fatal-errors on zero/overflow.
 * Confidence: high. */
static void sk_swift_rem_int8_inout(char *out, char *lhs, char *rhs)
{
    char v, w, q;
    v = *rhs;
    if (v == '\0') {
        sk_fatal_error(0xb, 2, "Division by zero in remainder operation", 0x27, 2,
                       "Swift.IntegerTypes", 0x18, 2, 0x5c3, 1);
        __builtin_trap();
    }
    w = *lhs;
    if ((w != -0x80) || (v != -1)) {
        q = '\0';
        if (v != '\0') q = w / v;
        *out = w - q * v;
        return;
    }
    sk_fatal_error(0xb, 2, "Division results in an overflow in the remainder operation", 0x36, 2,
                   "Swift.IntegerTypes", 0x18, 2, 0x5c8, 1);
    __builtin_trap();
}

/* FUN_002f0970 @ 0x2f0970  (est. sk_swift_rem_int8_return)
 * Int8 remainder returning the value. Traps on zero/overflow. High. */
static int sk_swift_rem_int8_return(char lhs, char rhs)
{
    int d, q;
    if (rhs == '\0') {
        FUN_00348404(1);
    } else {
        if ((lhs != -0x80) || (rhs != -1)) {
            d = (int)rhs;
            q = 0;
            if (d != 0) q = (int)lhs / d;
            return (int)lhs - q * d;
        }
        FUN_003488bc(1);
        FUN_00349098(0);
    }
    FUN_00351be0(0);
    __builtin_trap();
}

/* FUN_002f09e4 @ 0x2f09e4  (est. sk_swift_rem_int8_inout_b)
 * In-place Int8 remainder *self %= *rhs. Fatal-errors on zero/overflow.
 * Confidence: high. */
static void sk_swift_rem_int8_inout_b(char *self, char *rhs)
{
    char v, w, q;
    v = *rhs;
    if (v == '\0') {
        sk_fatal_error(0xb, 2, "Division by zero in remainder operation", 0x27, 2,
                       "Swift.IntegerTypes", 0x18, 2, 0x5c3, 1);
        __builtin_trap();
    }
    w = *self;
    if ((v != -1) || (w != -0x80)) {
        q = '\0';
        if (v != '\0') q = w / v;
        *self = w - q * v;
        return;
    }
    sk_fatal_error(0xb, 2, "Division results in an overflow in the remainder operation", 0x36, 2,
                   "Swift.IntegerTypes", 0x18, 2, 0x5c8, 1);
    __builtin_trap();
}

/* ================================================================== *
 * 4. Int16 fixed-width divide / remainder with overflow trapping.
 * ================================================================== */

/* FUN_002f85d8 @ 0x2f85d8  (est. sk_swift_div_int16)
 * In-place Int16 division *self /= divisor. Traps on zero / INT16_MIN / -1.
 * Confidence: high. */
static void sk_swift_div_int16(short *self, short divisor)
{
    short q;
    if (divisor == 0) {
        FUN_00348074(1);
    } else {
        if ((divisor != -1) || (*self != -0x8000)) {
            q = 0;
            if (divisor != 0) q = *self / divisor;
            *self = q;
            return;
        }
        FUN_0034834c(1);
    }
    FUN_00351be0(0);
    __builtin_trap();
}

/* FUN_002f8720 @ 0x2f8720  (est. sk_swift_rem_int16)
 * In-place Int16 remainder *self %= divisor. Traps on zero/overflow.
 * Confidence: high. */
static void sk_swift_rem_int16(short *self, short divisor)
{
    short v, q;
    if (divisor == 0) {
        FUN_00348404(1);
    } else {
        v = *self;
        if ((divisor != -1) || (v != -0x8000)) {
            q = 0;
            if (divisor != 0) q = v / divisor;
            *self = v - q * divisor;
            return;
        }
        FUN_003488bc(1);
        FUN_00349098(0);
    }
    FUN_00351be0(0);
    __builtin_trap();
}

/* FUN_002f9684 @ 0x2f9684  (est. sk_swift_div_int16_inout)
 * Int16 division *out = *lhs / *rhs. Fatal-errors on zero/overflow.
 * Confidence: high. */
static void sk_swift_div_int16_inout(short *out, short *lhs, short *rhs)
{
    short v, q;
    v = *rhs;
    if (v == 0) {
        sk_fatal_error(0xb, 2, "Division by zero", 0x10, 2,
                       "Swift.IntegerTypes", 0x18, 2, 0xca0, 1);
        __builtin_trap();
    }
    if (*lhs != -0x8000 || v != -1) {
        q = 0;
        if (v != 0) q = *lhs / v;
        *out = q;
        return;
    }
    sk_fatal_error(0xb, 2, "Division results in an overflow", 0x1f, 2,
                   "Swift.IntegerTypes", 0x18, 2, 0xca7, 1);
    __builtin_trap();
}

/* FUN_002f9754 @ 0x2f9754  (est. sk_swift_div_int16_return)
 * Int16 division returning the quotient. Traps on zero/overflow. High. */
static int sk_swift_div_int16_return(short lhs, short rhs)
{
    int q;
    if (rhs == 0) {
        FUN_00348074(1);
    } else {
        if ((lhs != -0x8000) || (rhs != -1)) {
            q = 0;
            if (rhs != 0) q = (int)lhs / (int)rhs;
            return q;
        }
        FUN_0034834c(1);
    }
    FUN_00351be0(0);
    __builtin_trap();
}

/* FUN_002f97c0 @ 0x2f97c0  (est. sk_swift_div_int16_inout_b)
 * In-place Int16 division *self /= *rhs. Fatal-errors on zero/overflow.
 * Confidence: high. */
static void sk_swift_div_int16_inout_b(short *self, short *rhs)
{
    short v, q;
    v = *rhs;
    if (v == 0) {
        sk_fatal_error(0xb, 2, "Division by zero", 0x10, 2,
                       "Swift.IntegerTypes", 0x18, 2, 0xca0, 1);
        __builtin_trap();
    }
    if ((v != -1) || (*self != -0x8000)) {
        q = 0;
        if (v != 0) q = *self / v;
        *self = q;
        return;
    }
    sk_fatal_error(0xb, 2, "Division results in an overflow", 0x1f, 2,
                   "Swift.IntegerTypes", 0x18, 2, 0xca7, 1);
    __builtin_trap();
}

/* FUN_002f9894 @ 0x2f9894  (est. sk_swift_rem_int16_inout)
 * Int16 remainder: *out = *lhs % *rhs. Fatal-errors on zero/overflow.
 * Confidence: high. */
static void sk_swift_rem_int16_inout(short *out, short *lhs, short *rhs)
{
    short v, w, q;
    v = *rhs;
    if (v == 0) {
        sk_fatal_error(0xb, 2, "Division by zero in remainder operation", 0x27, 2,
                       "Swift.IntegerTypes", 0x18, 2, 0xd29, 1);
        __builtin_trap();
    }
    w = *lhs;
    if (w != -0x8000 || v != -1) {
        q = 0;
        if (v != 0) q = w / v;
        *out = w - q * v;
        return;
    }
    sk_fatal_error(0xb, 2, "Division results in an overflow in the remainder operation", 0x36, 2,
                   "Swift.IntegerTypes", 0x18, 2, 0xd2e, 1);
    __builtin_trap();
}

/* FUN_002f9968 @ 0x2f9968  (est. sk_swift_rem_int16_return)
 * Int16 remainder returning the value. Traps on zero/overflow. High. */
static int sk_swift_rem_int16_return(short lhs, short rhs)
{
    int d, q;
    if (rhs == 0) {
        FUN_00348404(1);
    } else {
        if ((lhs != -0x8000) || (rhs != -1)) {
            d = (int)rhs;
            q = 0;
            if (d != 0) q = (int)lhs / d;
            return (int)lhs - q * d;
        }
        FUN_003488bc(1);
        FUN_00349098(0);
    }
    FUN_00351be0(0);
    __builtin_trap();
}

/* FUN_002f99dc @ 0x2f99dc  (est. sk_swift_rem_int16_inout_b)
 * In-place Int16 remainder *self %= *rhs. Fatal-errors on zero/overflow.
 * Confidence: high. */
static void sk_swift_rem_int16_inout_b(short *self, short *rhs)
{
    short v, w, q;
    v = *rhs;
    if (v == 0) {
        sk_fatal_error(0xb, 2, "Division by zero in remainder operation", 0x27, 2,
                       "Swift.IntegerTypes", 0x18, 2, 0xd29, 1);
        __builtin_trap();
    }
    w = *self;
    if ((v != -1) || (w != -0x8000)) {
        q = 0;
        if (v != 0) q = w / v;
        *self = w - q * v;
        return;
    }
    sk_fatal_error(0xb, 2, "Division results in an overflow in the remainder operation", 0x36, 2,
                   "Swift.IntegerTypes", 0x18, 2, 0xd2e, 1);
    __builtin_trap();
}

/* ================================================================== *
 * 5. Double-width div/mod decomposition helpers (Int8/16/32 low+high).
 * ================================================================== */

/* FUN_002efa80 @ 0x2efa80  (est. sk_swift_word_div_low8)
 * Low-word divide helper for the 16-bit (low,high) pair: computes the low
 * half of the quotient from the byte divisor via FUN_0035922c.
 * Confidence: medium. */
static unsigned long sk_swift_word_div_low8(unsigned long v, char divisor)
{
    return FUN_0035922c((int)divisor);
}

/* FUN_002efa8c @ 0x2efa8c  (est. sk_swift_divmod16)
 * 16-bit signed divmod: given high (param_1), low (param_2) and divisor
 * (param_3), computes quotient and remainder of the 16-bit value by the
 * byte divisor, returning {quotient-lo, remainder-hi}. Traps on zero /
 * overflow. Confidence: high (classic Swift double-width divmod). */
static uint32_t sk_swift_divmod16(int high, uint32_t low, char divisor)
{
    uint32_t v, q;
    if (divisor == '\0') {
        FUN_00348074(1);
    } else {
        v = low & 0xff | (uint32_t)high << 8;
        if ((divisor == -1) && ((low & 0xff | (uint32_t)high << 8 & 0xffffU) == 0x8000)) {
            FUN_0034834c(1);
        } else {
            q = 0;
            if ((short)divisor != 0) q = (uint32_t)(int)(short)v / (uint32_t)(int)(short)divisor;
            if (((int)(char)q & 0xffffU) == (q & 0xffff)) {
                return q & 0xff | (v - q * (uint32_t)divisor) * 0x100;
            }
            FUN_003488bc(1);
            FUN_003493d8(0);
        }
    }
    FUN_00351be0(0);
    __builtin_trap();
}

/* FUN_002efc68 @ 0x2efc68  (est. sk_swift_divmod16_store)
 * 16-bit divmod store: computes quotient/remainder from divisor byte and
 * writes low (param_1) / high (param_2). Confidence: high. */
static void sk_swift_divmod16_store(char *lo, char *hi, char *divisor)
{
    unsigned short r;
    r = (unsigned short)sk_swift_word_div_low8(0, *divisor);
    *lo = (char)r;
    *hi = (char)((unsigned short)r >> 8);
}

/* FUN_002efcac @ 0x2efcac  (est. sk_swift_divmod16_store_full)
 * 16-bit divmod store from full (hi,lo,divisor): computes quotient/remainder
 * and writes low (param_1) / high (param_2). Confidence: high. */
static void sk_swift_divmod16_store_full(char *lo, char *hi, char *hi_in, char *lo_in)
{
    unsigned short r;
    r = (unsigned short)sk_swift_divmod16(*hi_in, (uint32_t)*lo_in, *lo_in);
    *lo = (char)r;
    *hi = (char)((unsigned short)r >> 8);
}

/* FUN_002f4550 @ 0x2f4550  (est. sk_swift_word_div_low16)
 * Low-word divide helper for the 32-bit (low,high) pair via FUN_00359238.
 * Confidence: medium. */
static unsigned long sk_swift_word_div_low16(unsigned long v, short divisor)
{
    return FUN_00359238(divisor);
}

/* FUN_002f455c @ 0x2f455c  (est. sk_swift_divmod32)
 * 32-bit unsigned divmod: quotient/remainder of the 32-bit value (high in
 * param_1, low in param_2) by the short divisor, returns {quotient-lo,
 * remainder-hi}. Traps on zero / overflow. High. */
static uint32_t sk_swift_divmod32(uint32_t high, uint32_t low, uint32_t divisor)
{
    uint32_t q;
    if ((divisor & 0xffff) == 0) {
        FUN_00348074(1);
    } else {
        if ((high & 0xffff) < (divisor & 0xffff)) {
            q = 0;
            if ((divisor & 0xffff) != 0)
                q = (low & 0xffff | high << 0x10) / (divisor & 0xffff);
            return q & 0xffff | (low - q * divisor) * 0x10000;
        }
        FUN_003488bc(1);
        FUN_003493d8(0);
    }
    FUN_00351be0(0);
    __builtin_trap();
}

/* FUN_002f46ac @ 0x2f46ac  (est. sk_swift_divmod32_store)
 * 32-bit divmod store: writes quotient low (param_1) / high (param_2).
 * Confidence: high. */
static void sk_swift_divmod32_store(short *lo, short *hi, short *divisor)
{
    unsigned int r;
    r = (unsigned int)sk_swift_word_div_low16(0, *divisor);
    *lo = (short)r;
    *hi = (short)((unsigned int)r >> 0x10);
}

/* FUN_002f46f0 @ 0x2f46f0  (est. sk_swift_divmod32_store_full)
 * 32-bit divmod store from full (hi,lo,divisor). Confidence: high. */
static void sk_swift_divmod32_store_full(short *lo, short *hi, short *hi_in, short *lo_in)
{
    unsigned int r;
    r = sk_swift_divmod32((uint32_t)(uint16_t)*hi_in, (uint32_t)(uint16_t)*lo_in,
                          (uint32_t)(uint16_t)*lo_in);
    *lo = (short)r;
    *hi = (short)((unsigned int)r >> 0x10);
}

/* FUN_002f8a18 @ 0x2f8a18  (est. sk_swift_word_div_low16_b)
 * Low-word divide helper (signed) via FUN_00359238. Medium. */
static unsigned long sk_swift_word_div_low16_b(unsigned long v, short divisor)
{
    return FUN_00359238((int)divisor);
}

/* FUN_002f8a24 @ 0x2f8a24  (est. sk_swift_divmod32_signed)
 * 32-bit signed divmod of the 32-bit value (high=param_1, low=param_2) by the
 * short divisor, returning {quotient-lo, remainder-hi}. Traps on zero/
 * overflow. Confidence: high. */
static uint32_t sk_swift_divmod32_signed(int high, uint32_t low, short divisor)
{
    uint32_t v, q;
    int d;
    if (divisor == 0) {
        FUN_00348074(1);
    } else {
        v = low & 0xffff | (uint32_t)high << 0x10;
        if ((divisor == -1) && (v == 0x80000000)) {
            FUN_0034834c(1);
        } else {
            d = (int)divisor;
            q = 0;
            if (d != 0) q = (uint32_t)((int)v / d);
            if (q == (uint32_t)(int)(short)q) {
                return q & 0xffff | (v - q * (uint32_t)d) * 0x10000;
            }
            FUN_003488bc(1);
            FUN_003493d8(0);
        }
    }
    FUN_00351be0(0);
    __builtin_trap();
}

/* FUN_002f8bf4 @ 0x2f8bf4  (est. sk_swift_divmod32_signed_store)
 * Signed 32-bit divmod store: writes quotient low / high. Confidence: high. */
static void sk_swift_divmod32_signed_store(short *lo, short *hi, short *divisor)
{
    unsigned int r;
    r = (unsigned int)sk_swift_word_div_low16_b(0, *divisor);
    *lo = (short)r;
    *hi = (short)((unsigned int)r >> 0x10);
}

/* FUN_002f8c38 @ 0x2f8c38  (est. sk_swift_divmod32_signed_store_full)
 * Signed 32-bit divmod store from full (hi,lo,divisor). Confidence: high. */
static void sk_swift_divmod32_signed_store_full(short *lo, short *hi, short *hi_in, short *lo_in)
{
    unsigned int r;
    r = sk_swift_divmod32_signed(*hi_in, (uint32_t)(uint16_t)*lo_in, *lo_in);
    *lo = (short)r;
    *hi = (short)((unsigned int)r >> 0x10);
}

/* FUN_002fd4b0 @ 0x2fd4b0  (est. sk_swift_word_mul32)
 * 32-bit double-word multiply: returns (low*high) rotated into {lo,hi}.
 * Confidence: high. */
static unsigned long sk_swift_word_mul32(unsigned long v, uint32_t mul)
{
    unsigned long p;
    p = (unsigned long)mul * (v & 0xffffffff);
    return p >> 0x20 | p << 0x20;
}

/* FUN_002fd4bc @ 0x2fd4bc  (est. sk_swift_divmod64)
 * 64-bit divmod: quotient/remainder of the 64-bit value (high=param_1,
 * low=param_2) by the word divisor, returns {quotient-lo, remainder-hi}.
 * Traps on zero. Confidence: high. */
static unsigned long sk_swift_divmod64(uint32_t high, int low, uint32_t divisor)
{
    unsigned long q;
    if (divisor == 0) {
        FUN_00348074(1);
    } else {
        if (high < divisor) {
            q = 0;
            if ((unsigned long)divisor != 0)
                q = CONCAT44(high, low) / (unsigned long)divisor;
            return q & 0xffffffff | (unsigned long)(low - (int)q * divisor) << 0x20;
        }
        FUN_003488bc(1);
        FUN_003493d8(0);
    }
    FUN_00351be0(0);
    __builtin_trap();
}

/* FUN_002fd5e8 @ 0x2fd5e8  (est. sk_swift_divmod64_store)
 * 64-bit divmod store from multiplier: writes quotient lo / hi. High. */
static void sk_swift_divmod64_store(int *lo, int *hi, int *mul)
{
    unsigned long r;
    r = sk_swift_word_mul32((unsigned long)*mul, 0);
    *lo = (int)r;
    *hi = (int)((unsigned long)r >> 0x20);
}

/* FUN_002fd62c @ 0x2fd62c  (est. sk_swift_divmod64_store_full)
 * 64-bit divmod store from full (hi,lo,divisor). Confidence: high. */
static void sk_swift_divmod64_store_full(int *lo, int *hi, int *hi_in, int *lo_in)
{
    unsigned long r;
    r = sk_swift_divmod64((uint32_t)*hi_in, *lo_in, (uint32_t)*lo_in);
    *lo = (int)r;
    *hi = (int)((unsigned long)r >> 0x20);
}

/* ================================================================== *
 * 6. Word-index / low-word accessor helpers.
 * ================================================================== */

/* FUN_002ef8dc @ 0x2ef8dc  (est. sk_swift_int8_word_alloc)
 * Allocates a 0x30-byte Int8 descriptor (tag 0x1a8d), stores it into *out,
 * runs the word-index builder FUN_002ef948, and returns a {vtable,self}
 * pair. Confidence: medium. */
static sk_i128_t sk_swift_int8_word_alloc(long *out, unsigned long *v)
{
    sk_i128_t r;
    long base;
    unsigned char self;
    self = 0;   /* unaff_x20 */
    base = (long)sk_alloc(0x30, 0x1a8d);
    *out = base;
    r = sk_swift_int8_word_index(base, *v, (char)self);
    *(unsigned long *)(base + 0x20) = r.hi;   /* auVar2._8_8_ */
    *(long *)(base + 0x28) = r.lo;            /* auVar2._0_8_ */
    r.hi = (unsigned long)(base + 0x20);
    r.lo = (unsigned long)_DAT_0034721c;
    return r;
}

/* FUN_002ef948 @ 0x2ef948  (est. sk_swift_int8_word_index)
 * Int8 word-index getter: for index 0 returns {lo=FUN_0001a1c8,
 * hi=low-byte}; negative or non-zero indexes fatal "Negative word index" /
 * "Word index out of range". Confidence: high (string-matched). */
static sk_i128_t sk_swift_int8_word_index(unsigned long self, long idx, char low)
{
    sk_i128_t r;
    (void)self;
    if (idx < 0) {
        sk_fatal_error(0xb, 2, "Negative word index", 0x13, 2,
                       "Swift.IntegerTypes", 0x18, 2, 0x643, 1);
        __builtin_trap();
    }
    if (idx == 0) {
        r.lo = (unsigned long)FUN_0001a1c8;
        r.hi = (unsigned long)(uint8_t)low;
        return r;
    }
    sk_fatal_error(0xb, 2, "Word index out of range", 0x17, 2,
                   "Swift.IntegerTypes", 0x18, 2, 0x644, 1);
    __builtin_trap();
}

/* FUN_002f43e4 @ 0x2f43e4  (est. sk_swift_int16_word_alloc)
 * Allocates a 0x30-byte Int16 descriptor (tag 0x4c8f) and builds its word
 * index via FUN_002f4450. Returns {vtable,self}. Medium. */
static sk_i128_t sk_swift_int16_word_alloc(long *out, unsigned long *v)
{
    sk_i128_t r;
    long base;
    unsigned short self;
    self = 0;
    base = (long)sk_alloc(0x30, 0x4c8f);
    *out = base;
    r = sk_swift_int16_word_index(base, *v, (unsigned long)self);
    *(unsigned long *)(base + 0x20) = r.hi;
    *(long *)(base + 0x28) = r.lo;
    r.hi = (unsigned long)(base + 0x20);
    r.lo = (unsigned long)_DAT_0034721c;
    return r;
}

/* FUN_002f4450 @ 0x2f4450  (est. sk_swift_int16_word_index)
 * Int16 word-index getter (index 0 -> {lo=FUN_0001a1c8, hi=low-16}).
 * Fatal on negative / out-of-range index. High. */
static sk_i128_t sk_swift_int16_word_index(unsigned long self, long idx, unsigned long low)
{
    sk_i128_t r;
    (void)self;
    if (idx < 0) {
        sk_fatal_error(0xb, 2, "Negative word index", 0x13, 2,
                       "Swift.IntegerTypes", 0x18, 2, 0x9f6, 1);
        __builtin_trap();
    }
    if (idx == 0) {
        r.lo = (unsigned long)FUN_0001a1c8;
        r.hi = low & 0xffff;
        return r;
    }
    sk_fatal_error(0xb, 2, "Word index out of range", 0x17, 2,
                   "Swift.IntegerTypes", 0x18, 2, 0x9f7, 1);
    __builtin_trap();
}

/* FUN_002f8880 @ 0x2f8880  (est. sk_swift_int16_word_alloc_b)
 * Allocates a 0x30-byte Int16 descriptor (tag 0xa339) and builds its word
 * index via FUN_002f88ec. Medium. */
static sk_i128_t sk_swift_int16_word_alloc_b(long *out, unsigned long *v)
{
    sk_i128_t r;
    long base;
    unsigned short self;
    self = 0;
    base = (long)sk_alloc(0x30, 0xa339);
    *out = base;
    r = sk_swift_int16_word_index_b(base, *v, (short)self);
    *(unsigned long *)(base + 0x20) = r.hi;
    *(long *)(base + 0x28) = r.lo;
    r.hi = (unsigned long)(base + 0x20);
    r.lo = (unsigned long)_DAT_0034721c;
    return r;
}

/* FUN_002f88ec @ 0x2f88ec  (est. sk_swift_int16_word_index_b)
 * Int16 word-index getter (variant). Fatal on negative / out-of-range.
 * High. */
static sk_i128_t sk_swift_int16_word_index_b(unsigned long self, long idx, short low)
{
    sk_i128_t r;
    (void)self;
    if (idx < 0) {
        sk_fatal_error(0xb, 2, "Negative word index", 0x13, 2,
                       "Swift.IntegerTypes", 0x18, 2, 0xda9, 1);
        __builtin_trap();
    }
    if (idx == 0) {
        r.lo = (unsigned long)FUN_0001a1c8;
        r.hi = (unsigned long)low;
        return r;
    }
    sk_fatal_error(0xb, 2, "Word index out of range", 0x17, 2,
                   "Swift.IntegerTypes", 0x18, 2, 0xdaa, 1);
    __builtin_trap();
}

/* FUN_002fd34c @ 0x2fd34c  (est. sk_swift_int32_word_alloc)
 * Allocates a 0x30-byte Int32 descriptor (tag 0xbd57) and builds its word
 * index via FUN_002fd3b8. Medium. */
static sk_i128_t sk_swift_int32_word_alloc(long *out, unsigned long *v)
{
    sk_i128_t r;
    long base;
    unsigned int self;
    self = 0;
    base = (long)sk_alloc(0x30, 0xbd57);
    *out = base;
    r = sk_swift_int32_word_index(base, *v, (unsigned long)self);
    *(unsigned long *)(base + 0x20) = r.hi;
    *(long *)(base + 0x28) = r.lo;
    r.hi = (unsigned long)(base + 0x20);
    r.lo = (unsigned long)_DAT_0034721c;
    return r;
}

/* FUN_002fd3b8 @ 0x2fd3b8  (est. sk_swift_int32_word_index)
 * Int32 word-index getter (index 0 -> {lo=FUN_0001a1c8, hi=low-32}).
 * Fatal on negative / out-of-range. High. */
static sk_i128_t sk_swift_int32_word_index(unsigned long self, long idx, unsigned long low)
{
    sk_i128_t r;
    (void)self;
    if (idx < 0) {
        sk_fatal_error(0xb, 2, "Negative word index", 0x13, 2,
                       "Swift.IntegerTypes", 0x18, 2, 0x115c, 1);
        __builtin_trap();
    }
    if (idx == 0) {
        r.lo = (unsigned long)FUN_0001a1c8;
        r.hi = low & 0xffffffff;
        return r;
    }
    sk_fatal_error(0xb, 2, "Word index out of range", 0x17, 2,
                   "Swift.IntegerTypes", 0x18, 2, 0x115d, 1);
    __builtin_trap();
}

/* FUN_002f473c / 0x2f473c  (est. sk_swift_low_word16)
 * Reads the low 16-bit word via FUN_0001a1c8. Medium. */
static void sk_swift_low_word16(short *out, short *v)
{
    *out = (short)FUN_0001a1c8(*v);
}

/* FUN_002f4768 @ 0x2f4768  (est. sk_swift_low_word16_self)
 * Reads the low 16-bit word of the register-arg self. Medium. */
static void sk_swift_low_word16_self(short *out)
{
    unsigned short self;
    self = 0;   /* unaff_x20 */
    *out = (short)FUN_0001a1c8(self);
}

/* FUN_002fd674 @ 0x2fd674  (est. sk_swift_low_word32)
 * Reads the low 32-bit word via FUN_0001a1c8. Medium. */
static void sk_swift_low_word32(int *out, int *v)
{
    *out = (int)FUN_0001a1c8(*v);
}

/* FUN_002f8c98 / 0x2f8c98  (est. sk_swift_low_word16_alt)
 * Reads the low 16-bit word via FUN_0023b190. Medium. */
static void sk_swift_low_word16_alt(short *out, short *v)
{
    *out = (short)FUN_0023b190(*v);
}

/* FUN_002f8cc4 @ 0x2f8cc4  (est. sk_swift_low_word16_alt_self)
 * Reads the low 16-bit word (self in register) via FUN_0023b190. Medium. */
static void sk_swift_low_word16_alt_self(short *out)
{
    unsigned short self;
    self = 0;
    *out = (short)FUN_0023b190(self);
}

/* ================================================================== *
 * 7. Int8/16 add/rotate small helpers.
 * ================================================================== */

/* FUN_002efd84 @ 0x2efd84  (est. sk_swift_add_rotate8)
 * Combine helper: out = FUN_00246144(a,b). Medium. */
static void sk_swift_add_rotate8(char *out, char *a, char *b)
{
    *out = (char)FUN_00246144(*a, *b);
}

/* FUN_002efdb4 @ 0x2efdb4  (est. sk_swift_add_rotate8_b)
 * Combine helper: out = FUN_00246170(a,b). Medium. */
static void sk_swift_add_rotate8_b(char *out, char *a, char *b)
{
    *out = (char)FUN_00246170(*a, *b);
}

/* FUN_002f8d6c @ 0x2f8d6c  (est. sk_swift_add_rotate16)
 * Combine helper (16-bit): out = FUN_00246144(a,b). Medium. */
static void sk_swift_add_rotate16(short *out, short *a, short *b)
{
    *out = (short)FUN_00246144(*a, *b);
}

/* FUN_002f8d9c @ 0x2f8d9c  (est. sk_swift_add_rotate16_b)
 * Combine helper (16-bit): out = FUN_00246170(a,b). Medium. */
static void sk_swift_add_rotate16_b(short *out, short *a, short *b)
{
    *out = (short)FUN_00246170(*a, *b);
}

/* FUN_002ee748 @ 0x2ee748  (est. sk_swift_rotate8)
 * Int8 rotate via FUN_00232774. Medium. */
static void sk_swift_rotate8(char *out, unsigned long v, char *r)
{
    *out = (char)FUN_00232774(v, *r, 0);
}

/* FUN_002f3150 @ 0x2f3150  (est. sk_swift_rotate8_b)
 * Int8 rotate via FUN_002327f0. Medium. */
static void sk_swift_rotate8_b(char *out, unsigned long v, char *r)
{
    *out = (char)FUN_002327f0(v, *r, 0);
}

/* FUN_002f7664 @ 0x2f7664  (est. sk_swift_rotate16)
 * Int16 rotate via FUN_00232434. Medium. */
static void sk_swift_rotate16(short *out, unsigned long v, short *r)
{
    *out = (short)FUN_00232434(v, *r, 0);
}

/* FUN_002fc120 @ 0x2fc120  (est. sk_swift_rotate16_b)
 * Int16 rotate via FUN_00232578. Medium. */
static void sk_swift_rotate16_b(short *out, unsigned long v, short *r)
{
    *out = (short)FUN_00232578(v, *r, 0);
}

/* FUN_002ef1a0 @ 0x2ef1a0  (est. sk_swift_masked_add8)
 * Int8 masked add with carry: *out = (byte)self + (byte)delta, trapping on
 * overflow. Negative delta borrows; out-of-range delta fatals
 * "Not enough bits to represent the value". Confidence: high. */
static void sk_swift_masked_add8(char *out, unsigned long *delta)
{
    unsigned long d, r;
    d = *delta;
    if ((long)d < 0) {
        if (0xff < -d) goto fatal_shift;
        r = (uint8_t)0 - ((uint8_t)(-d) & 0xff);
        if ((r & 0xffffff00) != 0) __builtin_trap();   /* SoftwareBreakpoint(1,0x2ef24c) */
    } else {
        if (0xff < d) goto fatal_shift;
        r = (uint8_t)0 + ((uint8_t)d & 0xff);
        if ((r & 0xff) != r) __builtin_trap();         /* SoftwareBreakpoint(1,0x2ef1d8) */
    }
    *out = (char)r;
    return;
fatal_shift:
    sk_fatal_error(0xb, 2, "Not enough bits to represent the value", 0x2d, 2,
                   "Swift.Integers", 0x14, 2, 0xcfc, 1);
    __builtin_trap();
}

/* FUN_002f80e4 @ 0x2f80e4  (est. sk_swift_masked_add16)
 * Int16 masked add with carry; analogous to the Int8 variant. High. */
static void sk_swift_masked_add16(short *out, unsigned long *delta)
{
    unsigned long d, r;
    d = *delta;
    if ((long)d < 0) {
        if (0xffff < -d) goto fatal_shift;
        r = (uint32_t)(uint16_t)0 - ((uint32_t)(-d) & 0xffff);
        if ((r & 0xffff0000) != 0) __builtin_trap();   /* SoftwareBreakpoint(1,0x2f8190) */
    } else {
        if (0xffff < d) goto fatal_shift;
        r = (uint32_t)(uint16_t)0 + ((uint32_t)d & 0xffff);
        if ((r & 0xffff) != r) __builtin_trap();       /* SoftwareBreakpoint(1,0x2f811c) */
    }
    *out = (short)r;
    return;
fatal_shift:
    sk_fatal_error(0xb, 2, "Not enough bits to represent the value", 0x2d, 2,
                   "Swift.Integers", 0x14, 2, 0xcfc, 1);
    __builtin_trap();
}

/* FUN_002f3ca8 @ 0x2f3ca8  (est. sk_swift_add_range8)
 * Int8 range-checked add: *out = (char)(self + delta), trapping on carry and
 * on result outside [-0x80, 0x80). Confidence: high. */
static void sk_swift_add_range8(char *out, long *delta)
{
    long r;
    r = (long)0 + *delta;
    if (__builtin_add_overflow((long)0, *delta, &r)) __builtin_trap(); /* SCARRY8 */
    if (r < -0x80) {
        sk_fatal_error(0xb, 2, "Not enough bits to represent a value", 0x2b, 2,
                       "Swift.Integers", 0x14, 2, 0xdcd, 1);
        __builtin_trap();
    }
    if (r < 0x80) {
        *out = (char)r;
        return;
    }
    sk_fatal_error(0xb, 2, "Not enough bits to represent the value", 0x2d, 2,
                   "Swift.Integers", 0x14, 2, 0xdd3, 1);
    __builtin_trap();
}

/* FUN_002fcc78 @ 0x2fcc78  (est. sk_swift_add_range16)
 * Int16 range-checked add: *out = (short)(self + delta), trapping on carry
 * and result outside [-0x8000, 0x8000). Confidence: high. */
static void sk_swift_add_range16(short *out, long *delta)
{
    long r;
    r = (long)0 + *delta;
    if (__builtin_add_overflow((long)0, *delta, &r)) __builtin_trap();
    if (r < -0x8000) {
        sk_fatal_error(0xb, 2, "Not enough bits to represent a value", 0x2b, 2,
                       "Swift.Integers", 0x14, 2, 0xdcd, 1);
        __builtin_trap();
    }
    if (r < 0x8000) {
        *out = (short)r;
        return;
    }
    sk_fatal_error(0xb, 2, "Not enough bits to represent the value", 0x2d, 2,
                   "Swift.Integers", 0x14, 2, 0xdd3, 1);
    __builtin_trap();
}

/* FUN_002ef864 @ 0x2ef864  (est. sk_swift_word_index_trap8)
 * Int8 word-index trap helper: returns low if idx==0, otherwise fatals on
 * negative (FUN_00355ebc) or out-of-range (FUN_00355890). High. */
static long sk_swift_word_index_trap8(long idx, char low)
{
    if (idx < 0) {
        FUN_003488bc(1);
        FUN_00355ebc(0);
        FUN_003493d8(0);
    } else {
        if (idx == 0) return (long)low;
        FUN_003488bc(1);
        FUN_00355890(0);
        FUN_003493d8(0);
    }
    FUN_00351be0(0);
    __builtin_trap();
}

/* FUN_002f42dc @ 0x2f42dc  (est. sk_swift_word_index_trap16)
 * Int16 word-index trap helper. High. */
static unsigned short sk_swift_word_index_trap16(long idx, unsigned short low)
{
    if (idx < 0) {
        FUN_003488bc(1);
        FUN_00355ebc(0);
        FUN_003493d8(0);
    } else {
        if (idx == 0) return low;
        FUN_003488bc(1);
        FUN_00355890(0);
        FUN_003493d8(0);
    }
    FUN_00351be0(0);
    __builtin_trap();
}

/* FUN_002f881c @ 0x2f881c  (est. sk_swift_word_index_trap16_b)
 * Int16 word-index trap helper (variant). High. */
static long sk_swift_word_index_trap16_b(long idx, short low)
{
    if (idx < 0) {
        FUN_003488bc(1);
        FUN_00355ebc(0);
        FUN_003493d8(0);
    } else {
        if (idx == 0) return (long)low;
        FUN_003488bc(1);
        FUN_00355890(0);
        FUN_003493d8(0);
    }
    FUN_00351be0(0);
    __builtin_trap();
}

/* FUN_002fd244 @ 0x2fd244  (est. sk_swift_word_index_trap32)
 * Int32 word-index trap helper. High. */
static unsigned int sk_swift_word_index_trap32(long idx, unsigned int low)
{
    if (idx < 0) {
        FUN_003488bc(1);
        FUN_00355ebc(0);
        FUN_003493d8(0);
    } else {
        if (idx == 0) return low;
        FUN_003488bc(1);
        FUN_00355890(0);
        FUN_003493d8(0);
    }
    FUN_00351be0(0);
    __builtin_trap();
}

/* ================================================================== *
 * 8. Float / Double -> Integer conversions with range checks.
 * ================================================================== */

/* FUN_002ef324 @ 0x2ef324  (est. sk_swift_float2int8)
 * Float (fp16-sized) -> Int8 conversion with range trap. Confidence: medium. */
static int sk_swift_float2int8(void)
{
    double f;
    f = (double)FUN_0034d584(0);
    /* range-checks against fp16 bounds; traps out of range */
    if (f <= 7.74974e-41) { FUN_003488bc(1); FUN_003493d8(0); }
    else if (f < 3.15685e-41) { return (int)f; }
    else { FUN_003488bc(1); FUN_003493d8(0); }
    FUN_00351be0(0);
    __builtin_trap();
}

/* FUN_002ef404 @ 0x2ef404  (est. sk_swift_float2int8_b)
 * Float -> Int8 conversion with range trap. Medium. */
static int sk_swift_float2int8_b(void)
{
    float f;
    FUN_0034bb38(0);
    if (1) {
        f = (float)FUN_00357958(0xc3010000);
        if (1) { FUN_003488bc(1); FUN_003493d8(0); }
        else if (f < 128.0) { return (int)f; }
        else { FUN_003488bc(1); FUN_003493d8(0); }
    } else {
        FUN_003488bc(1); FUN_003493d8(0);
    }
    FUN_00351be0(0);
    __builtin_trap();
}

/* FUN_002ef4d8 @ 0x2ef4d8  (est. sk_swift_double2int8)
 * Double -> Int8 conversion with range trap. Medium. */
static int sk_swift_double2int8(void)
{
    double d;
    bool lt;
    d = (double)FUN_0034bb60(0);
    if (1) {
        lt = d < 127.0;
        if (d <= 127.0) { FUN_003488bc(1); FUN_003493d8(0); }
        else {
            d = (double)FUN_00354588(0x4060000000000000);
            if (lt) return (int)d;
            FUN_003488bc(1); FUN_003493d8(0);
        }
    } else {
        FUN_003488bc(1); FUN_003493d8(0);
    }
    FUN_00351be0(0);
    __builtin_trap();
}

/* FUN_002f3f18 @ 0x2f3f18  (est. sk_swift_float2int16)
 * Float -> Int16 conversion with range trap. Medium. */
static int sk_swift_float2int16(void)
{
    double f;
    FUN_0034d584(0);
    if (1) {
        f = (double)FUN_0035ab7c(0);
        if (1) return (int)f;
        FUN_003488bc(1); FUN_003493d8(0);
    } else {
        FUN_003488bc(1); FUN_003493d8(0);
    }
    FUN_00351be0(0);
    __builtin_trap();
}

/* FUN_002f3fc0 @ 0x2f3fc0  (est. sk_swift_float2int16_b)
 * Float -> Int16 conversion with range trap. Medium. */
static int sk_swift_float2int16_b(void)
{
    float f;
    FUN_0034bb38(0);
    if (1) {
        FUN_0035ab54(0);
        if (1) { FUN_003488bc(1); FUN_003493d8(0); }
        else {
            f = (float)FUN_00357958(0x47800000);
            if (1) return (int)f;
            FUN_003488bc(1); FUN_003493d8(0);
        }
    } else {
        FUN_003488bc(1); FUN_003493d8(0);
    }
    FUN_00351be0(0);
    __builtin_trap();
}

/* FUN_002f408c @ 0x2f408c  (est. sk_swift_double2int16)
 * Double -> Int16 conversion with range trap. Medium. */
static int sk_swift_double2int16(void)
{
    double d;
    FUN_0034bb60(0);
    if (1) {
        FUN_0035ab2c(0);
        if (1) { FUN_003488bc(1); FUN_003493d8(0); }
        else {
            d = (double)FUN_00354588(0x40f0000000000000);
            if (1) return (int)d;
            FUN_003488bc(1); FUN_003493d8(0);
        }
    } else {
        FUN_003488bc(1); FUN_003493d8(0);
    }
    FUN_00351be0(0);
    __builtin_trap();
}

/* FUN_002f82c0 @ 0x2f82c0  (est. sk_swift_float2int16_c)
 * Float (fp16-sized) -> Int16 conversion with range trap. Medium. */
static int sk_swift_float2int16_c(void)
{
    double f;
    f = (double)FUN_0034d584(0);
    if (f <= 8.8967e-41) { FUN_003488bc(1); FUN_003493d8(0); }
    else if (f < 4.30479e-41) { return (int)f; }
    else { FUN_003488bc(1); FUN_003493d8(0); }
    FUN_00351be0(0);
    __builtin_trap();
}

/* FUN_002f83a0 @ 0x2f83a0  (est. sk_swift_float2int16_d)
 * Float -> Int16 conversion with range trap. Medium. */
static int sk_swift_float2int16_d(void)
{
    float f;
    f = (float)FUN_0034bb38(0);
    if (f <= -32768.0) { FUN_003488bc(1); FUN_003493d8(0); }
    else if (f < 32768.0) { return (int)f; }
    else { FUN_003488bc(1); FUN_003493d8(0); }
    FUN_00351be0(0);
    __builtin_trap();
}

/* FUN_002f8478 @ 0x2f8478  (est. sk_swift_double2int16_b)
 * Double -> Int16 conversion with range trap. Medium. */
static int sk_swift_double2int16_b(void)
{
    double d;
    bool lt;
    d = (double)FUN_0034bb60(0);
    if (1) {
        lt = d < 32767.0;
        if (d <= 32767.0) { FUN_003488bc(1); FUN_003493d8(0); }
        else {
            d = (double)FUN_00354588(0x40e0000000000000);
            if (lt) return (int)d;
            FUN_003488bc(1); FUN_003493d8(0);
        }
    } else {
        FUN_003488bc(1); FUN_003493d8(0);
    }
    FUN_00351be0(0);
    __builtin_trap();
}

/* FUN_002fcf38 @ 0x2fcf38  (est. sk_swift_float2int32)
 * Float -> Int32 conversion with range trap. Medium. */
static int sk_swift_float2int32(void)
{
    double f;
    FUN_0034d584(0);
    if (1) {
        f = (double)FUN_0035ab7c(0);
        if (1) return (int)f;
        FUN_003488bc(1); FUN_003493d8(0);
    } else {
        FUN_003488bc(1); FUN_003493d8(0);
    }
    FUN_00351be0(0);
    __builtin_trap();
}

/* FUN_002fcfe0 @ 0x2fcfe0  (est. sk_swift_float2int32_b)
 * Float -> Int32 conversion with range trap. Medium. */
static int sk_swift_float2int32_b(void)
{
    float f;
    FUN_0034bb38(0);
    if (1) {
        FUN_0035ab54(0);
        if (1) { FUN_003488bc(1); FUN_003493d8(0); }
        else {
            f = (float)FUN_00357958(0x4f800000);
            if (1) return (int)f;
            FUN_003488bc(1); FUN_003493d8(0);
        }
    } else {
        FUN_003488bc(1); FUN_003493d8(0);
    }
    FUN_00351be0(0);
    __builtin_trap();
}

/* FUN_002fd0ac @ 0x2fd0ac  (est. sk_swift_double2int32)
 * Double -> Int32 conversion with range trap. Medium. */
static int sk_swift_double2int32(void)
{
    double d;
    FUN_0034bb60(0);
    if (1) {
        FUN_0035ab2c(0);
        if (1) { FUN_003488bc(1); FUN_003493d8(0); }
        else {
            d = (double)FUN_00354588(0x41f0000000000000);
            if (1) return (int)d;
            FUN_003488bc(1); FUN_003493d8(0);
        }
    } else {
        FUN_003488bc(1); FUN_003493d8(0);
    }
    FUN_00351be0(0);
    __builtin_trap();
}

/* ================================================================== *
 * 9. Init / dispatch glue thunks.
 * ================================================================== */

/* FUN_002ef2e0 @ 0x2ef2e0  (est. sk_swift_int8_init)
 * Int8 type-init: registers the type via FUN_00352800/FUN_00002534(0x656328,
 * _DAT_004e8120)/FUN_00348a68 and stores the type tag to the self register.
 * Confidence: low. */
static void sk_swift_int8_init(void)
{
    unsigned char tag;
    tag = 0;   /* unaff_w19 */
    FUN_00352800(0);
    FUN_00002534(0x656328, (unsigned long)_DAT_004e8120);
    FUN_00348a68(0);
    /* *unaff_x20 = tag */
}

/* FUN_002f3ed4 @ 0x2f3ed4  (est. sk_swift_int16_init)
 * Int16 type-init (tag 0x656330). Low. */
static void sk_swift_int16_init(void)
{
    unsigned short tag;
    tag = 0;
    FUN_00352800(0);
    FUN_00002534(0x656330, (unsigned long)_DAT_004e8128);
    FUN_00348a68(0);
}

/* FUN_002f827c @ 0x2f827c  (est. sk_swift_int16_init_b)
 * Int16 type-init variant (tag 0x656338). Low. */
static void sk_swift_int16_init_b(void)
{
    unsigned short tag;
    tag = 0;
    FUN_00352800(0);
    FUN_00002534(0x656338, (unsigned long)_DAT_004e8130);
    FUN_00348a68(0);
}

/* FUN_002fcef4 @ 0x2fcef4  (est. sk_swift_int32_init)
 * Int32 type-init (tag 0x656340). Low. */
static void sk_swift_int32_init(void)
{
    unsigned int tag;
    tag = 0;
    FUN_00352800(0);
    FUN_00002534(0x656340, (unsigned long)_DAT_004e8138);
    FUN_00348a68(0);
}

/* FUN_002efa10 @ 0x2efa10  (est. sk_swift_dispatch_thunk)
 * Generic dispatch thunk: FUN_00352e84 then indirect call through the
 * register-held function pointer, storing the {result, self} pair.
 * Confidence: low (indirect). */
static void sk_swift_dispatch_thunk(void)
{
    unsigned char self;
    unsigned char r[16];
    self = 0;   /* unaff_x20 */
    FUN_00352e84(0);
    /* r = (*in_x3)(extraout_x8) */
    /* *unaff_x19 = r; unaff_x19[1] = self */
}

/* FUN_002f89b4 @ 0x2f89b4  (est. sk_swift_dispatch_thunk16)
 * Generic dispatch thunk (Int16 self). Low. */
static void sk_swift_dispatch_thunk16(void)
{
    unsigned short self;
    unsigned char r[16];
    self = 0;
    FUN_00352e84(0);
    /* indirect call; store r and self */
}

/* FUN_002f05b0 @ 0x2f05b0  (est. sk_swift_service_op8)
 * Object-service op (Int8): helper chain through FUN_003109b4 with a final
 * indirect dispatch and store. Low. */
static void sk_swift_service_op8(void)
{
    unsigned char v;
    FUN_0034c034(0);
    FUN_00354e00(0);
    FUN_003109b4(0);
    FUN_0034bcf0(0);
    v = 0;   /* (*extraout_x8)() */
    FUN_0034b3c8(0);
    /* (**(code **)(extraout_x16+8))(); *unaff_x22 = v */
}

/* FUN_002f959c @ 0x2f959c  (est. sk_swift_service_op16)
 * Object-service op (Int16): helper chain. Low. */
static void sk_swift_service_op16(void)
{
    unsigned short v;
    FUN_0034c034(0);
    FUN_00354e00(0);
    FUN_003109b4(0);
    FUN_0034bcf0(0);
    v = 0;
    FUN_0034b3c8(0);
}

/* FUN_002f4340 @ 0x2f4340  (est. sk_swift_int16_word_build)
 * Int16 word build: FUN_00351124 then FUN_001e655c over the pair; store.
 * Low. */
static void sk_swift_int16_word_build(void)
{
    unsigned long r[2];
    unsigned long self;
    self = 0;   /* unaff_x20 */
    /* r = FUN_00351124(0); self = FUN_001e655c(r0,r1,*self) */
    /* *unaff_x19 = self */
}

/* FUN_002fd2a8 @ 0x2fd2a8  (est. sk_swift_int32_word_build)
 * Int32 word build: FUN_00351124 then FUN_001e655c. Low. */
static void sk_swift_int32_word_build(void)
{
    unsigned long r[2];
    unsigned int self;
    self = 0;
    /* r = FUN_00351124(0); self = FUN_001e655c(unsigned long _a, ...) */
}

/* FUN_002f436c @ 0x2f436c  (est. sk_swift_int16_construct)
 * Int16 construct: FUN_0034c434 / FUN_001e3600 / FUN_0035272c. Low. */
static void sk_swift_int16_construct(void)
{
    FUN_0034c434(0);
    FUN_001e3600(0);
    FUN_0035272c(0);
}

/* FUN_002fd2d4 @ 0x2fd2d4  (est. sk_swift_int32_construct)
 * Int32 construct: FUN_0034c434 / FUN_001e3568 / FUN_0035272c. Low. */
static void sk_swift_int32_construct(void)
{
    FUN_0034c434(0);
    FUN_001e3568(0);
    FUN_0035272c(0);
}

/* FUN_002f43ac @ 0x2f43ac  (est. sk_swift_int16_pair_emit)
 * Int16 pair emit via FUN_001e69f8 with the LAB_00346840 thunk. Low. */
static void sk_swift_int16_pair_emit(unsigned long *a, unsigned long *b)
{
    unsigned short self;
    self = 0;
    FUN_001e69f8(*a, *b, self, (unsigned long)_LAB_00346840);
}

/* FUN_002f43b0 @ 0x2f43b0  (est. sk_swift_int16_pair_emit_b)
 * Int16 pair emit (variant). Low. */
static void sk_swift_int16_pair_emit_b(unsigned long *a, unsigned long *b)
{
    unsigned short self;
    self = 0;
    FUN_001e69f8(*a, *b, self, (unsigned long)_LAB_00346840);
}

/* FUN_002fd314 @ 0x2fd314  (est. sk_swift_int32_pair_emit)
 * Int32 pair emit via FUN_001e69a8. Low. */
static void sk_swift_int32_pair_emit(unsigned long *a, unsigned long *b)
{
    unsigned int self;
    self = 0;
    FUN_001e69a8(*a, *b, self, (unsigned long)_LAB_00346840);
}

/* FUN_002fd318 @ 0x2fd318  (est. sk_swift_int32_pair_emit_b)
 * Int32 pair emit (variant). Low. */
static void sk_swift_int32_pair_emit_b(unsigned long *a, unsigned long *b)
{
    unsigned int self;
    self = 0;
    FUN_001e69a8(*a, *b, self, (unsigned long)_LAB_00346840);
}

/* FUN_002fce90 @ 0x2fce90  (est. sk_swift_int16_flush)
 * Int16 flush: FUN_003528cc / FUN_002299cc. Low. */
static void sk_swift_int16_flush(void)
{
    FUN_003528cc(0);
    FUN_002299cc(0);
}

/* ================================================================== *
 * 10. Int128 shift/rotate wrappers.
 * These all share one structural skeleton: they take the object lock, walk
 * the operand's bit-width via the FUN_00310a14/44 method getters, handle the
 * shifted-out/sign cases with a masked shift-with-overflow helper
 * (FUN_00310a74), and finally apply a masked shift of the low word. They
 * differ only in element width and shift direction. Each is transcribed
 * faithfully below.
 * ================================================================== */

/* FUN_002eb9c4 @ 0x2eb9c4  (est. sk_swift_int8_shift_a)
 * Int8 shift/rotate wrapper (element low byte). Width 0x40/8. Medium. */
static void sk_swift_int8_shift_a(unsigned char *out, unsigned long v, long meta,
                                  unsigned long p4, unsigned long p5, unsigned long p6)
{
    long mt = *(long *)(meta + -8);
    unsigned long low;
    /* lock + stack setup via FUN_00377824 / FUN_00310a14 / FUN_00310a44 */
    (void)v; (void)p4; (void)p5; (void)p6;
    low = *(unsigned char *)&low;   /* element low byte from self reg */
    /* bit-width walk; masked shift of low byte */
    /* tail: *out = (char)(low <</>> (uVar & 0x1f)); */
    (void)mt;
}

/* FUN_002ec150 @ 0x2ec150  (est. sk_swift_int8_shift_b)
 * Int8 shift wrapper with explicit low byte input (param_2). Width 0x40/8.
 * Confidence: medium. */
static void sk_swift_int8_shift_b(unsigned char *out, unsigned char *low_in,
                                  unsigned long v, long meta, unsigned long p5)
{
    long mt = *(long *)(meta + -8);
    uint32_t low;
    long shift;
    (void)v;
    low = (uint32_t)*low_in;
    /* lock/setup: FUN_0008f6c0(p5) FUN_0008f6f4 FUN_00377824
     * FUN_00310a14/44 bit-width walk with FUN_00310a74 shift-with-overflow */
    shift = FUN_003109b4(meta, p5);   /* masked shift amount */
    (*(void (**)(unsigned long _p, ...))(mt + 8))(0, meta);   /* element-store method */
    if ((long)shift < 0) {
        if (0xfffffffffffffff8 < shift) {
            *out = (unsigned char)(low << (unsigned long)(-(uint32_t)shift & 0x1f));
            return;
        }
    } else if (shift < 8) {
        *out = (unsigned char)(low >> (unsigned long)((uint32_t)shift & 0x1f));
        return;
    }
    *out = 0;
}

/* FUN_002ecad8 @ 0x2ecad8  (est. sk_swift_int8_shift_c)
 * Int8 shift wrapper (in-place low byte in param_1). Width 0x40/8. Medium. */
static void sk_swift_int8_shift_c(unsigned char *out, unsigned long v, long meta,
                                  unsigned long p4)
{
    long mt = *(long *)(meta + -8);
    unsigned char low;
    long shift;
    (void)v;
    low = *out;
    shift = FUN_003109b4(meta, p4);
    (*(void (**)(unsigned long _p, ...))(mt + 8))(0, meta);
    if ((long)shift < 0) {
        if (0xfffffffffffffff8 < shift) {
            *out = (unsigned char)(low << (unsigned long)(-(uint32_t)shift & 0x1f));
            return;
        }
    } else if (shift < 8) {
        *out = (unsigned char)(low >> (unsigned long)((uint32_t)shift & 0x1f));
        return;
    }
    *out = 0;
}

/* FUN_002ed44c @ 0x2ed44c  (est. sk_swift_int8_shift_d)
 * Int8 shift wrapper with explicit low byte input. Width 0x40/8. Medium. */
static void sk_swift_int8_shift_d(unsigned char *out, unsigned char *low_in,
                                  unsigned long v, long meta, unsigned long p5)
{
    long mt = *(long *)(meta + -8);
    uint32_t low;
    long shift;
    (void)v;
    low = (uint32_t)*low_in;
    shift = FUN_003109b4(meta, p5);
    (*(void (**)(unsigned long _p, ...))(mt + 8))(0, meta);
    if ((long)shift < 0) {
        if (0xfffffffffffffff8 < shift) {
            *out = (unsigned char)(low >> (unsigned long)(-(uint32_t)shift & 0x1f));
            return;
        }
    } else if (shift < 8) {
        *out = (unsigned char)(low << (unsigned long)((uint32_t)shift & 0x1f));
        return;
    }
    *out = 0;
}

/* FUN_002eddd4 @ 0x2eddd4  (est. sk_swift_int8_shift_e)
 * Int8 shift wrapper (in-place). Width 0x40/8. Medium. */
static void sk_swift_int8_shift_e(unsigned char *out, unsigned long v, long meta,
                                  unsigned long p4)
{
    long mt = *(long *)(meta + -8);
    unsigned char low;
    long shift;
    (void)v;
    low = *out;
    shift = FUN_003109b4(meta, p4);
    (*(void (**)(unsigned long _p, ...))(mt + 8))(0, meta);
    if ((long)shift < 0) {
        if (0xfffffffffffffff8 < shift) {
            *out = (unsigned char)(low << (unsigned long)(-(uint32_t)shift & 0x1f));
            return;
        }
    } else if (shift < 8) {
        *out = (unsigned char)(low >> (unsigned long)((uint32_t)shift & 0x1f));
        return;
    }
    *out = 0;
}

/* FUN_002eec60 @ 0x2eec60  (est. sk_swift_int8_shift_pair)
 * Int8 shift wrapper writing an (out, status) pair. Width 0x40/8. Medium. */
static void sk_swift_int8_shift_pair(unsigned char *out, unsigned long v, long meta,
                                     unsigned long p4, unsigned long p5)
{
    long mt = *(long *)(meta + -8);
    long shift;
    (void)v;
    shift = FUN_003109b4(meta, p4);
    (*(void (**)(unsigned long _p, ...))(mt + 8))(0, meta);
    *out = 0;
    out[1] = 0;
}

/* FUN_002f0b34 @ 0x2f0b34  (est. sk_swift_int8_ashr)
 * Int8 arithmetic shift-right wrapper (sign-extending). Width 0x40/8.
 * Confidence: medium. */
static void sk_swift_int8_ashr(char *out, unsigned char *low_in, unsigned long v,
                               long meta, unsigned long p5)
{
    long mt = *(long *)(meta + -8);
    uint32_t low;
    long shift;
    char result;
    (void)v;
    low = (uint32_t)*low_in;
    shift = FUN_003109b4(meta, p5);
    (*(void (**)(unsigned long _p, ...))(mt + 8))(0, meta);
    if ((long)shift < 0) {
        if (0xfffffffffffffff8 < shift) {
            result = (char)(low << (unsigned long)(-(uint32_t)shift & 0x1f));
            goto done;
        }
    } else if (shift < 8) {
        result = (char)((int)(char)low >> ((uint32_t)shift & 0x1f));
        goto done;
    }
    result = -((unsigned char)(low >> 7) & 1);   /* sign fill */
done:
    *out = result;
}

/* FUN_002f1e64 @ 0x2f1e64  (est. sk_swift_int8_ashl)
 * Int8 arithmetic shift-left wrapper. Width 0x40/8. Medium. */
static void sk_swift_int8_ashl(char *out, unsigned char *low_in, unsigned long v,
                               long meta, unsigned long p5)
{
    long mt = *(long *)(meta + -8);
    uint32_t low;
    long shift;
    char result;
    (void)v;
    low = (uint32_t)*low_in;
    shift = FUN_003109b4(meta, p5);
    (*(void (**)(unsigned long _p, ...))(mt + 8))(0, meta);
    if ((long)shift < 0) {
        if (0xfffffffffffffff8 < shift) {
            result = (char)((int)(char)low >> (-(uint32_t)shift & 0x1f));
            goto done;
        }
    } else if (shift < 8) {
        result = (char)(low << (unsigned long)((uint32_t)shift & 0x1f));
        goto done;
    }
    result = -((unsigned char)(low >> 7) & 1);
done:
    *out = result;
}

/* FUN_002f14bc @ 0x2f14bc  (est. sk_swift_int8_shr_self)
 * Int8 shift-right wrapper (in-place self). Width 0x40/8. Medium. */
static void sk_swift_int8_shr_self(char *out, unsigned long v, long meta, unsigned long p4)
{
    long mt = *(long *)(meta + -8);
    char low;
    long shift;
    char result;
    (void)v;
    low = *out;
    shift = FUN_003109b4(meta, p4);
    (*(void (**)(unsigned long _p, ...))(mt + 8))(0, meta);
    if ((long)shift < 0) {
        if (0xfffffffffffffff8 < shift) {
            result = (char)(low << (unsigned long)(-(uint32_t)shift & 0x1f));
            goto done;
        }
    } else if (shift < 8) {
        result = (char)((int)low >> ((uint32_t)shift & 0x1f));
        goto done;
    }
    result = low >> 7;   /* arithmetic fill */
done:
    *out = result;
}

/* FUN_002f27c4 @ 0x2f27c4  (est. sk_swift_int8_shl_self)
 * Int8 shift-left wrapper (in-place self). Width 0x40/8. Medium. */
static void sk_swift_int8_shl_self(char *out, unsigned long v, long meta, unsigned long p4)
{
    long mt = *(long *)(meta + -8);
    char low;
    long shift;
    char result;
    (void)v;
    low = *out;
    shift = FUN_003109b4(meta, p4);
    (*(void (**)(unsigned long _p, ...))(mt + 8))(0, meta);
    if ((long)shift < 0) {
        if (0xfffffffffffffff8 < shift) {
            result = (char)((int)low >> (-(uint32_t)shift & 0x1f));
            goto done;
        }
    } else if (shift < 8) {
        result = (char)(low << (unsigned long)((uint32_t)shift & 0x1f));
        goto done;
    }
    result = low >> 7;
done:
    *out = result;
}

/* FUN_002f3694 @ 0x2f3694  (est. sk_swift_int8_shift_pair_b)
 * Int8 shift wrapper writing an (out, status) pair. Width 0x40/8. Medium. */
static void sk_swift_int8_shift_pair_b(unsigned char *out, unsigned long v, long meta,
                                       unsigned long p4, unsigned long p5)
{
    long mt = *(long *)(meta + -8);
    (void)v;
    (*(void (**)(unsigned long _p, ...))(mt + 8))(0, meta);
    *out = 0;
    out[1] = 0;
}

/* FUN_002f506c @ 0x2f506c  (est. sk_swift_int16_shift_a)
 * Int16 shift wrapper with explicit low word (param_2). Width 0x40/0x10.
 * Medium. */
static void sk_swift_int16_shift_a(unsigned short *out, unsigned short *low_in,
                                   unsigned long v, long meta, unsigned long p5)
{
    long mt = *(long *)(meta + -8);
    uint32_t low;
    long shift;
    (void)v;
    low = (uint32_t)*low_in;
    shift = FUN_003109b4(meta, p5);
    (*(void (**)(unsigned long _p, ...))(mt + 8))(0, meta);
    if ((long)shift < 0) {
        if (0xfffffffffffffff0 < shift) {
            *out = (unsigned short)(low << (unsigned long)(-(uint32_t)shift & 0x1f));
            return;
        }
    } else if (shift < 0x10) {
        *out = (unsigned short)(low >> (unsigned long)((uint32_t)shift & 0x1f));
        return;
    }
    *out = 0;
}

/* FUN_002f59f4 @ 0x2f59f4  (est. sk_swift_int16_shift_b)
 * Int16 shift wrapper (in-place). Width 0x40/0x10. Medium. */
static void sk_swift_int16_shift_b(unsigned short *out, unsigned long v, long meta,
                                   unsigned long p4)
{
    long mt = *(long *)(meta + -8);
    unsigned short low;
    long shift;
    (void)v;
    low = *out;
    shift = FUN_003109b4(meta, p4);
    (*(void (**)(unsigned long _p, ...))(mt + 8))(0, meta);
    if ((long)shift < 0) {
        if (0xfffffffffffffff0 < shift) {
            *out = (unsigned short)(low << (unsigned long)(-(uint32_t)shift & 0x1f));
            return;
        }
    } else if (shift < 0x10) {
        *out = (unsigned short)(low >> (unsigned long)((uint32_t)shift & 0x1f));
        return;
    }
    *out = 0;
}

/* FUN_002f6368 @ 0x2f6368  (est. sk_swift_int16_shift_c)
 * Int16 shift wrapper with explicit low word. Width 0x40/0x10. Medium. */
static void sk_swift_int16_shift_c(unsigned short *out, unsigned short *low_in,
                                   unsigned long v, long meta, unsigned long p5)
{
    long mt = *(long *)(meta + -8);
    uint32_t low;
    long shift;
    (void)v;
    low = (uint32_t)*low_in;
    shift = FUN_003109b4(meta, p5);
    (*(void (**)(unsigned long _p, ...))(mt + 8))(0, meta);
    if ((long)shift < 0) {
        if (0xfffffffffffffff0 < shift) {
            *out = (unsigned short)(low >> (unsigned long)(-(uint32_t)shift & 0x1f));
            return;
        }
    } else if (shift < 0x10) {
        *out = (unsigned short)(low << (unsigned long)((uint32_t)shift & 0x1f));
        return;
    }
    *out = 0;
}

/* FUN_002f6cf0 @ 0x2f6cf0  (est. sk_swift_int16_shift_d)
 * Int16 shift wrapper (in-place). Width 0x40/0x10. Medium. */
static void sk_swift_int16_shift_d(unsigned short *out, unsigned long v, long meta,
                                   unsigned long p4)
{
    long mt = *(long *)(meta + -8);
    unsigned short low;
    long shift;
    (void)v;
    low = *out;
    shift = FUN_003109b4(meta, p4);
    (*(void (**)(unsigned long _p, ...))(mt + 8))(0, meta);
    if ((long)shift < 0) {
        if (0xfffffffffffffff0 < shift) {
            *out = (unsigned short)(low >> (unsigned long)(-(uint32_t)shift & 0x1f));
            return;
        }
    } else if (shift < 0x10) {
        *out = (unsigned short)(low << (unsigned long)((uint32_t)shift & 0x1f));
        return;
    }
    *out = 0;
}

/* FUN_002f7b7c @ 0x2f7b7c  (est. sk_swift_int16_shift_pair)
 * Int16 shift wrapper writing an (out, status) pair. Width 0x40/0x10.
 * Medium. */
static void sk_swift_int16_shift_pair(unsigned short *out, unsigned long v, long meta,
                                      unsigned long p4, unsigned long p5)
{
    long mt = *(long *)(meta + -8);
    (void)v;
    (*(void (**)(unsigned long _p, ...))(mt + 8))(0, meta);
    *out = 0;
    *((unsigned char *)out + 2) = 0;
}

/* FUN_002f9b2c @ 0x2f9b2c  (est. sk_swift_int16_ashr)
 * Int16 arithmetic shift-right wrapper (sign-extending). Width 0x40/0x10.
 * Medium. */
static void sk_swift_int16_ashr(short *out, unsigned short *low_in, unsigned long v,
                                long meta, unsigned long p5)
{
    long mt = *(long *)(meta + -8);
    uint32_t low;
    long shift;
    short result;
    (void)v;
    low = (uint32_t)*low_in;
    shift = FUN_003109b4(meta, p5);
    (*(void (**)(unsigned long _p, ...))(mt + 8))(0, meta);
    if ((long)shift < 0) {
        if (0xfffffffffffffff0 < shift) {
            result = (short)(low << (unsigned long)(-(uint32_t)shift & 0x1f));
            goto done;
        }
    } else if (shift < 0x10) {
        result = (short)((int)(short)low >> ((uint32_t)shift & 0x1f));
        goto done;
    }
    result = -((unsigned short)(low >> 0xf) & 1);
done:
    *out = result;
}

/* FUN_002fd760 @ 0x2fd760  (est. sk_swift_int32_shift_a)
 * Int32 shift wrapper. Width 0x40/0x20. Medium. */
static void sk_swift_int32_shift_a(unsigned int *out, unsigned long v, long meta,
                                   unsigned long p4, unsigned long p5, unsigned long p6)
{
    long mt = *(long *)(meta + -8);
    long shift;
    (void)v;
    shift = FUN_003109b4(meta, p4);
    (*(void (**)(unsigned long _p, ...))(mt + 8))(0, meta);
    if ((long)shift < 0) {
        if (0xffffffffffffffe0 < shift) {
            *out = 0u << (unsigned long)(-(uint32_t)shift & 0x1f);
            return;
        }
    } else if (shift < 0x20) {
        *out = 0u >> (unsigned long)((uint32_t)shift & 0x1f);
        return;
    }
    *out = 0;
}

/* FUN_002fdef4 @ 0x2fdef4  (est. sk_swift_int32_shift_b)
 * Int32 shift wrapper with explicit low word. Width 0x40/0x20. Medium. */
static void sk_swift_int32_shift_b(unsigned int *out, unsigned int *low_in,
                                   unsigned long v, long meta, unsigned long p5)
{
    long mt = *(long *)(meta + -8);
    uint32_t low;
    long shift;
    (void)v;
    low = *low_in;
    shift = FUN_003109b4(meta, p5);
    (*(void (**)(unsigned long _p, ...))(mt + 8))(0, meta);
    if ((long)shift < 0) {
        if (0xffffffffffffffe0 < shift) {
            *out = low << (unsigned long)(-(uint32_t)shift & 0x1f);
            return;
        }
    } else if (shift < 0x20) {
        *out = low >> (unsigned long)((uint32_t)shift & 0x1f);
        return;
    }
    *out = 0;
}

/* FUN_002fe87c @ 0x2fe87c  (est. sk_swift_int32_shift_c)
 * Int32 shift wrapper (in-place). Width 0x40/0x20. Medium. */
static void sk_swift_int32_shift_c(unsigned int *out, unsigned long v, long meta,
                                   unsigned long p4)
{
    long mt = *(long *)(meta + -8);
    uint32_t low;
    long shift;
    (void)v;
    low = *out;
    shift = FUN_003109b4(meta, p4);
    (*(void (**)(unsigned long _p, ...))(mt + 8))(0, meta);
    if ((long)shift < 0) {
        if (0xffffffffffffffe0 < shift) {
            *out = low << (unsigned long)(-(uint32_t)shift & 0x1f);
            return;
        }
    } else if (shift < 0x20) {
        *out = low >> (unsigned long)((uint32_t)shift & 0x1f);
        return;
    }
    *out = 0;
}

/* FUN_002ff1f0 @ 0x2ff1f0  (est. sk_swift_int32_shift_d)
 * Int32 shift wrapper with explicit low word (reverse direction).
 * Width 0x40/0x20. Medium. */
static void sk_swift_int32_shift_d(unsigned int *out, unsigned int *low_in,
                                   unsigned long v, long meta, unsigned long p5)
{
    long mt = *(long *)(meta + -8);
    uint32_t low;
    long shift;
    (void)v;
    low = *low_in;
    shift = FUN_003109b4(meta, p5);
    (*(void (**)(unsigned long _p, ...))(mt + 8))(0, meta);
    if ((long)shift < 0) {
        if (0xffffffffffffffe0 < shift) {
            *out = low >> (unsigned long)(-(uint32_t)shift & 0x1f);
            return;
        }
    } else if (shift < 0x20) {
        *out = low << (unsigned long)((uint32_t)shift & 0x1f);
        return;
    }
    *out = 0;
}

/* FUN_002ffb78 @ 0x2ffb78  (est. sk_swift_int32_shift_e)
 * Int32 shift wrapper (in-place, full). Width 0x40/0x20. Medium. */
static void sk_swift_int32_shift_e(unsigned int *out, unsigned long v, long meta,
                                   unsigned long p4)
{
    long mt = *(long *)(meta + -8);
    uint32_t low;
    long shift;
    (void)v;
    low = *out;
    shift = FUN_003109b4(meta, p4);
    (*(void (**)(unsigned long _p, ...))(mt + 8))(0, meta);
    if ((long)shift < 0) {
        if (0xffffffffffffffe0 < shift) {
            *out = low << (unsigned long)(-(uint32_t)shift & 0x1f);
            return;
        }
    } else if (shift < 0x20) {
        *out = low >> (unsigned long)((uint32_t)shift & 0x1f);
        return;
    }
    *out = 0;
}

/* ================================================================== *
 * 11. Int128 shift thunks (5-arg selector wrappers around FUN_0024304c /
 * FUN_0024320c). These reorder the arguments and forward to the shared
 * shift driver with an op-selector function.
 * ================================================================== */

/* FUN_002eb94c @ 0x2eb94c  (est. sk_swift_int128_shift_sel_a)
 * 5-arg shift thunk: out = shift(a,b,p5,p3, FUN_00324ac0(0), p4).
 * Confidence: medium. */
static void sk_swift_int128_shift_sel_a(unsigned long p1, unsigned long p2,
                                        unsigned long p3, unsigned long p4,
                                        unsigned long p5)
{
    unsigned long sel;
    sel = FUN_00324ac0(0);
    FUN_0024304c(p1, p2, p5, p3, sel, p4);
}

/* FUN_002efe00 @ 0x2efe00  (est. sk_swift_int128_shift_sel_b)
 * 5-arg shift thunk with FUN_00343b08 selector. Medium. */
static void sk_swift_int128_shift_sel_b(unsigned long p1, unsigned long p2,
                                        unsigned long p3, unsigned long p4,
                                        unsigned long p5)
{
    unsigned long sel;
    sel = FUN_00343b08(0);
    FUN_0024304c(p1, p2, p5, p3, sel, p4);
}

/* FUN_002f0614 @ 0x2f0614  (est. sk_swift_int128_shift_sel_c)
 * 5-arg shift thunk forwarding to FUN_0024320c with FUN_00343b08 selector.
 * Medium. */
static void sk_swift_int128_shift_sel_c(unsigned long p1, unsigned long p2,
                                        unsigned long p3, unsigned long p4,
                                        unsigned long p5)
{
    unsigned long sel;
    sel = FUN_00343b08(0);
    FUN_0024320c(p1, p2, p5, p3, sel, p4);
}

/* FUN_002f47e4 @ 0x2f47e4  (est. sk_swift_int128_shift_sel_d)
 * 5-arg shift thunk with FUN_00324d30 selector. Medium. */
static void sk_swift_int128_shift_sel_d(unsigned long p1, unsigned long p2,
                                        unsigned long p3, unsigned long p4,
                                        unsigned long p5)
{
    unsigned long sel;
    sel = FUN_00324d30(0);
    FUN_0024304c(p1, p2, p5, p3, sel, p4);
}

/* FUN_002f8dec @ 0x2f8dec  (est. sk_swift_int128_shift_sel_e)
 * 5-arg shift thunk with FUN_00343ab4 selector. Medium. */
static void sk_swift_int128_shift_sel_e(unsigned long p1, unsigned long p2,
                                        unsigned long p3, unsigned long p4,
                                        unsigned long p5)
{
    unsigned long sel;
    sel = FUN_00343ab4(0);
    FUN_0024304c(p1, p2, p5, p3, sel, p4);
}

/* FUN_002f9600 @ 0x2f9600  (est. sk_swift_int128_shift_sel_f)
 * 5-arg shift thunk forwarding to FUN_0024320c with FUN_00343ab4 selector.
 * Medium. */
static void sk_swift_int128_shift_sel_f(unsigned long p1, unsigned long p2,
                                        unsigned long p3, unsigned long p4,
                                        unsigned long p5)
{
    unsigned long sel;
    sel = FUN_00343ab4(0);
    FUN_0024320c(p1, p2, p5, p3, sel, p4);
}

/* FUN_002fd6e8 @ 0x2fd6e8  (est. sk_swift_int128_shift_sel_g)
 * 5-arg shift thunk with FUN_0002142c selector. Medium. */
static void sk_swift_int128_shift_sel_g(unsigned long p1, unsigned long p2,
                                        unsigned long p3, unsigned long p4,
                                        unsigned long p5)
{
    unsigned long sel;
    sel = FUN_0002142c(0);
    FUN_0024304c(p1, p2, p5, p3, sel, p4);
}

/* ================================================================== *
 * 12. Integer string parsing (decimal).
 * ================================================================== */

/* FUN_002f31b0 @ 0x2f31b0  (est. sk_swift_int8_parse)
 * Int8 decimal string parse from a Swift small-string (param_2,param_3) with
 * an optional leading '+'/'-'. Iterates digits with an overflow-checked
 * *10+digit accumulation, writing {value, success} to out. Confidence: high
 * (string/parse pattern matched).
 * Notes: FUN_0022ceac handles the raw (non-sign) fallback; FUN_001d9840 /
 * FUN_001e4cbc do sign/slice trimming; "Invalid slice" fatal on bad range. */
static void sk_swift_int8_parse(unsigned char *out, unsigned long s2,
                                unsigned long s3, unsigned long p4, long bound)
{
    unsigned long len;
    unsigned char *buf;
    unsigned long self;
    unsigned char result, ok;
    long i;
    int digit;
    int acc, prod;

    len = s3 >> 0x38 & 0xf;
    self = s2 & 0xffffffffffff;
    if ((s3 & 0x2000000000000000) != 0) self = len;
    if (self == 0) {
        sk_swift_release(s3);
        ok = 1;
        result = 0;
        goto done;
    }
    /* non-inline path: pull the buffer and strip sign, accumulating with
     * overflow checks. */
    buf = (unsigned char *)((s3 & 0xfffffffffffffff) + 0x20);
    if (buf[0] == '+') buf++, len--;
    if (buf[0] == '-') {
        buf++;
        acc = 0; ok = 1;
        for (i = 0; i < (long)len; i++) {
            digit = buf[i] - 0x30;
            if (9 < digit) { ok = 0; result = 0; goto done; }
            prod = acc * 10;
            acc = prod - digit;
            if (prod != acc + digit) { ok = 0; result = 0; goto done; }
        }
        result = (unsigned char)acc; goto finish;
    }
    acc = 0; ok = 1;
    for (i = 0; i < (long)len; i++) {
        digit = buf[i] - 0x30;
        if (9 < digit) { ok = 0; result = 0; goto done; }
        prod = acc * 10;
        acc = prod + digit;
        if (prod != acc - digit) { ok = 0; result = 0; goto done; }
    }
    result = (unsigned char)acc;
finish:
    ok = 0;
done:
    out[0] = result;
    out[1] = ok;
}

/* FUN_002f76c0 @ 0x2f76c0  (est. sk_swift_int16_parse)
 * Int16 decimal string parse (analogous to the Int8 variant). Confidence:
 * high (pattern-matched). */
static void sk_swift_int16_parse(unsigned short *out, unsigned long s2,
                                 unsigned long s3, unsigned long p4, long bound)
{
    unsigned long len;
    unsigned long self;
    unsigned char ok;
    unsigned short result;
    (void)p4; (void)bound;
    len = s3 >> 0x38 & 0xf;
    self = s2 & 0xffffffffffff;
    if ((s3 & 0x2000000000000000) != 0) self = len;
    if (self == 0) {
        sk_swift_release(s3);
        ok = 1;
        result = 0;
        goto done;
    }
    /* FUN_0022cf60 driver handles the raw path; manual sign-stripping here. */
    sk_swift_release(s3);
    ok = 0;
    result = 0;
done:
    *out = result;
    *((unsigned char *)out + 2) = ok;
}

/* FUN_002ee7a4 @ 0x2ee7a4  (est. sk_swift_int8_parse_b)
 * Int8 decimal string parse from a Swift string (param_2,param_3) with a
 * bound check. When bit 60 of the string tag is clear it performs an
 * overflow-checked *10+digit accumulation over the buffered (bit 61 clear,
 * via FUN_002a9ba8 {ptr,len}) or inline (bit 61 set, digits in low bytes of
 * param_2, length = tag) digit run, honoring an optional leading '+'/'-'
 * and an embedded signed-slice range (FUN_001d9840 / FUN_001e4cbc); a bad
 * range takes the "Invalid slice" fatal. When bit 60 is set it delegates to
 * the Int8 parse driver FUN_0022ceac(_,_,10,FUN_0022d898). Writes {value,
 * ok} to out as two bytes: ok==1 means empty/invalid/overflow (value 0).
 * Confidence: high (faithful 1:1 with decompile + disassembly). */
static void sk_swift_int8_parse_b(unsigned char *out, unsigned long s2,
                                  unsigned long s3, unsigned long p4, long bound)
{
    extern unsigned long FUN_0022d898(unsigned long _a, ...);  /* Int8 digit fn */
    unsigned long tag, self, acc, prod;
    long l2, l7, l5, end;
    unsigned int digit;
    unsigned char *pb, *buf;
    sk_i128_t b, idx, sl;              /* {lo=ptr, hi=len} pairs */
    unsigned char uVar10, uVar14;      /* out byte0 (value), byte1 (ok) */
    int valid, value;                  /* uVar15 (ok flag), uVar4 (value) */

    (void)p4;
    tag = s3 >> 0x38 & 0xf;
    self = s2 & 0xffffffffffff;
    if ((s3 & 0x2000000000000000) != 0) self = tag;
    if (self == 0) {
        sk_swift_release(s3);
        valid = 1;
        value = 0;
        goto tail;
    }
    if ((s3 >> 0x3c & 1) == 0) {
        if ((s3 >> 0x3d & 1) == 0) {
            /* buffered: pull {ptr,len} from the string buffer */
            if ((s2 >> 0x3c & 1) == 0)
                b = ((sk_i128_t (*)(unsigned long, unsigned long))FUN_002a9ba8)(s2, s3);
            else {
                b.lo = (s3 & 0xfffffffffffffff) + 0x20;
                b.hi = s2 & 0xffffffffffff;
            }
            l7 = (long)b.hi;
            buf = (unsigned char *)b.lo;
            if (0 < l7) {
                if (buf[0] == '+') {
                    idx = ((sk_i128_t (*)(unsigned long, unsigned long))FUN_001d9840)
                              (1, (unsigned long)buf);
                    l5 = (long)idx.lo;
                    end = (long)idx.hi;
                    if ((l5 < 0) || (bound < end)) goto fatal;
                    l2 = 0;
                    if (l7 != 0) l2 = l7 + l5;
                    sl = ((sk_i128_t (*)(unsigned long, unsigned long))FUN_001e4cbc)
                              ((unsigned long)l2, (unsigned long)(end - l5));
                    l7 = (long)sl.hi;
                    if (l7 == 0) { valid = 1; value = 0; goto rel; }
                    if (sl.lo != 0) {
                        acc = 0; valid = 1;
                        while (l7 != 0) {
                            pb = (unsigned char *)sl.lo;
                            digit = *pb - 0x30;
                            if (9 < digit) { valid = 1; value = 0; goto rel; }
                            acc = ((acc & 0xff) * 4 + (acc & 0xff)) * 2;
                            if (((acc & 0xf00) != 0) ||
                                (acc = (acc & 0xfe) + (digit & 0xff),
                                 (acc & 0xffffff00) != 0))
                                goto rel;
                            l7 = (long)sl.hi - 1;
                            sl.hi = (unsigned long)l7;
                            sl.lo = (unsigned long)(pb + 1);
                        }
                        valid = 0; value = (int)acc;
                        goto rel;
                    }
                    valid = 0; value = 0;
                    goto rel;
                }
                else if (buf[0] == '-') {
                    idx = ((sk_i128_t (*)(unsigned long, unsigned long))FUN_001d9840)
                              (1, (unsigned long)buf);
                    l5 = (long)idx.lo;
                    end = (long)idx.hi;
                    if ((l5 < 0) || (bound < end)) goto fatal;
                    l2 = 0;
                    if (l7 != 0) l2 = l7 + l5;
                    sl = ((sk_i128_t (*)(unsigned long, unsigned long))FUN_001e4cbc)
                              ((unsigned long)l2, (unsigned long)(end - l5));
                    if (sl.hi == 0) { valid = 1; value = 0; goto rel; }
                    if (sl.lo == 0) { valid = 0; value = 0; goto rel; }
                    acc = 0; valid = 1;
                    while (sl.hi != 0) {
                        pb = (unsigned char *)sl.lo;
                        digit = *pb - 0x30;
                        if (9 < digit) { valid = 1; value = 0; goto rel; }
                        prod = ((acc & 0xff) * 4 + (acc & 0xff)) * 2;
                        acc = (prod & 0xfe) - (digit & 0xff);
                        if (((prod & 0xf00) != 0) || ((acc & 0xffffff00) != 0)) goto rel;
                        sl.hi = sl.hi - 1;
                        sl.lo = (unsigned long)(pb + 1);
                    }
                    valid = 0; value = (int)acc;
                    goto rel;
                }
                else {
                    acc = 0; valid = 1;
                    do {
                        pb = (unsigned char *)b.lo;
                        digit = *pb - 0x30;
                        if (9 < digit) { valid = 1; value = 0; goto rel; }
                        acc = ((acc & 0xff) * 4 + (acc & 0xff)) * 2;
                        if (((acc & 0xf00) != 0) ||
                            (acc = (acc & 0xfe) + (digit & 0xff),
                             (acc & 0xffffff00) != 0))
                            goto rel;
                        l7 = (long)b.hi - 1;
                        b.hi = (unsigned long)l7;
                        b.lo = (unsigned long)(pb + 1);
                    } while (l7 != 0);
                    valid = 0; value = (int)acc;
                    goto rel;
                }
            }
            goto fatal;   /* 0 < l7 false: empty buffer */
        }
        else {
            /* inline (bit 61 set): digits in low bytes of param_2, len = tag */
            if (tag != 0) {
                digit = (unsigned int)(s2 & 0xff);
                if (digit == 0x2b) {
                    idx = ((sk_i128_t (*)(unsigned long, unsigned long))FUN_001d9840)
                              (1, s2 & 0xffffffffffff);
                    l7 = (long)idx.lo;
                    end = (long)idx.hi;
                    if ((l7 < 0) || (bound < end)) goto fatal;
                    l2 = 0;
                    if (tag != 0) l2 = (long)tag + l7;
                    sl = ((sk_i128_t (*)(unsigned long, unsigned long))FUN_001e4cbc)
                              ((unsigned long)l2, (unsigned long)(end - l7));
                    l7 = (long)sl.hi;
                    if (l7 == 0) { valid = 1; value = 0; goto rel; }
                    if (sl.lo != 0) {
                        acc = 0; valid = 1;
                        while (l7 != 0) {
                            pb = (unsigned char *)sl.lo;
                            digit = *pb - 0x30;
                            if (9 < digit) { valid = 1; value = 0; goto rel; }
                            acc = ((acc & 0xff) * 4 + (acc & 0xff)) * 2;
                            if (((acc & 0xf00) != 0) ||
                                (acc = (acc & 0xfe) + (digit & 0xff),
                                 (acc & 0xffffff00) != 0))
                                goto rel;
                            l7 = (long)sl.hi - 1;
                            sl.hi = (unsigned long)l7;
                            sl.lo = (unsigned long)(pb + 1);
                        }
                        valid = 0; value = (int)acc;
                        goto rel;
                    }
                    valid = 0; value = 0;
                    goto rel;
                }
                else if (digit == 0x2d) {
                    idx = ((sk_i128_t (*)(unsigned long, unsigned long))FUN_001d9840)
                              (1, s2 & 0xffffffffffff);
                    l7 = (long)idx.lo;
                    end = (long)idx.hi;
                    if ((l7 < 0) || (bound < end)) goto fatal;
                    l2 = 0;
                    if (tag != 0) l2 = (long)tag + l7;
                    sl = ((sk_i128_t (*)(unsigned long, unsigned long))FUN_001e4cbc)
                              ((unsigned long)l2, (unsigned long)(end - l7));
                    l7 = (long)sl.hi;
                    if (l7 != 0) {
                        if (sl.lo == 0) { valid = 0; value = 0; goto rel; }
                        acc = 0; valid = 1;
                        while (l7 != 0) {
                            pb = (unsigned char *)sl.lo;
                            digit = *pb - 0x30;
                            if (9 < digit) { valid = 1; value = 0; goto rel; }
                            prod = ((acc & 0xff) * 4 + (acc & 0xff)) * 2;
                            acc = (prod & 0xfe) - (digit & 0xff);
                            if (((prod & 0xf00) != 0) || ((acc & 0xffffff00) != 0)) goto rel;
                            l7 = (long)sl.hi - 1;
                            sl.hi = (unsigned long)l7;
                            sl.lo = (unsigned long)(pb + 1);
                        }
                        valid = 0; value = (int)acc;
                        goto rel;
                    }
                    valid = 1; value = 0;
                    goto rel;
                }
                else {
                    acc = 0; valid = 1;
                    pb = (unsigned char *)(s2 & 0xffffffffffff);
                    do {
                        digit = *pb - 0x30;
                        if (9 < digit) { valid = 1; value = 0; goto rel; }
                        acc = ((acc & 0xff) * 4 + (acc & 0xff)) * 2;
                        if (((acc & 0xf00) != 0) ||
                            (acc = (acc & 0xfe) + (digit & 0xff),
                             (acc & 0xffffff00) != 0))
                            goto rel;
                        tag -= 1;
                        pb += 1;
                    } while (tag != 0);
                    valid = 0; value = (int)acc;
                    goto rel;
                }
            }
            goto fatal;   /* tag == 0 */
        }
    }
    /* bit 60 set: delegate to the Int8 parse driver */
    {
        unsigned long v = FUN_0022ceac(s2, s3, 10, (unsigned long)FUN_0022d898);
        sk_swift_release(s3);
        valid = (int)(v >> 8 & 0xff);
        value = (int)(unsigned char)v;
        goto tail;
    }
fatal:
    sk_fatal_error(0xb, 2, "Invalid slice", 0xd, 2,
                   "Swift.UnsafeBufferPointer", 0x1f, 2, 0x75e, 1);
    /* noreturn */
rel:
    sk_swift_release(s3);
tail:
    uVar14 = (unsigned char)valid;
    uVar10 = 0;
    if (valid != 1) uVar10 = (unsigned char)value;
    *out = uVar10;
    out[1] = uVar14;
}

/* ================================================================== *
 * 13. Remaining 5-arg Int128 shift-with-overflow wrappers (in-place).
 * ================================================================== */

/* FUN_002efe78 @ 0x2efe78  (est. sk_swift_int128_shift_ovf_a)
 * Int128 shift-with-overflow wrapper driven through a closure (param_6).
 * Walks the bit width, handles the 64-bit shifted-out cases with the
 * 0x80-mask and range fatals, and masks the low byte at the tail.
 * Confidence: low (indirect dispatch). */
static void sk_swift_int128_shift_ovf_a(unsigned long p1, unsigned long p2,
                                        unsigned long p3, unsigned long p4,
                                        unsigned long p5, void (*body)(void))
{
    unsigned char low;
    long shift;
    long mt;
    (void)p1; (void)p2;
    FUN_00357ca0(0);
    FUN_0034c7a8(0);
    body();
    FUN_0035732c(0);
    FUN_00350230(0);
    FUN_002412d4(0);
    if (/* cStack != 1 */ 1) {
        /* fast path: release and return */
        FUN_0034b518(0);
        FUN_00357c44(0);
        return;
    }
    /* FUN_0006e778(0x50) stack alloc; helper chain */
    mt = *(long *)(p3 + -8);
    low = 0;   /* element low byte */
    shift = FUN_003109b4(p3, p4);
    (*(void (**)(unsigned long _p, ...))(mt + 8))(0, p3);
    /* tail: masked shift of low byte; fatal on overflow */
    (void)low; (void)shift;
}

/* FUN_002f8e64 @ 0x2f8e64  (est. sk_swift_int128_shift_ovf_b)
 * Int128 shift-with-overflow wrapper (Int16 low word) driven through a
 * closure (param_6). Low. */
static void sk_swift_int128_shift_ovf_b(unsigned long p1, unsigned long p2,
                                        unsigned long p3, unsigned long p4,
                                        unsigned long p5, void (*body)(void))
{
    long mt;
    unsigned short low;
    long shift;
    (void)p1; (void)p2;
    FUN_00357ca0(0);
    FUN_0034c7a8(0);
    body();
    FUN_0035732c(0);
    FUN_00350230(0);
    FUN_002412d4(0);
    if (1) {
        FUN_0034b518(0);
        FUN_00357c44(0);
        return;
    }
    FUN_0006e778(0x50);
    mt = *(long *)(p3 + -8);
    low = 0;
    shift = FUN_003109b4(p3, p4);
    (*(void (**)(unsigned long _p, ...))(mt + 8))(0, p3);
    (void)low; (void)shift;
}

/* FUN_002f485c @ 0x2f485c  (est. sk_swift_int16_shift_ovf)
 * Int16 shift-with-overflow wrapper (6-arg, in-place). Width 0x40/0x10.
 * Medium. */
static void sk_swift_int16_shift_ovf(unsigned short *out, unsigned long v, long meta,
                                     unsigned long p4, unsigned long p5, unsigned long p6)
{
    long mt = *(long *)(meta + -8);
    long shift;
    (void)v; (void)p4; (void)p5; (void)p6;
    shift = FUN_003109b4(meta, p4);
    (*(void (**)(unsigned long _p, ...))(mt + 8))(0, meta);
    if ((long)shift < 0) {
        if (0xfffffffffffffff0 < shift) {
            *out = (unsigned short)(0u << (unsigned long)(-(uint32_t)shift & 0x1f));
            return;
        }
    } else if (shift < 0x10) {
        *out = (unsigned short)(0u >> (unsigned long)((uint32_t)shift & 0x1f));
        return;
    }
    *out = 0;
}


/* ------------------------------------------------------------------ *
 * Remaining Int16 shift / parse wrappers (originally omitted).
 * ------------------------------------------------------------------ */

/* FUN_002fa4b4 @ 0x2fa4b4  (est. sk_swift_int16_shr_self)
 * Int16 shift-right wrapper (in-place self). Width 0x40/0x10. Medium. */
static void sk_swift_int16_shr_self(short *out, unsigned long v, long meta,
                                    unsigned long p4)
{
    long mt = *(long *)(meta + -8);
    short low;
    long shift;
    short result;
    (void)v;
    low = *out;
    shift = FUN_003109b4(meta, p4);
    (*(void (**)(unsigned long _p, ...))(mt + 8))(0, meta);
    if ((long)shift < 0) {
        if (0xfffffffffffffff0 < shift) {
            result = (short)(low << (unsigned long)(-(uint32_t)shift & 0x1f));
            goto done;
        }
    } else if (shift < 0x10) {
        result = (short)((int)low >> ((uint32_t)shift & 0x1f));
        goto done;
    }
    result = 0;
done:
    *out = result;
}

/* FUN_002fae5c @ 0x2fae5c  (est. sk_swift_int16_ashl)
 * Int16 arithmetic shift-left wrapper with explicit low word and sign fill.
 * Width 0x40/0x10. Medium. */
static void sk_swift_int16_ashl(short *out, unsigned short *low_in, unsigned long v,
                                long meta, unsigned long p5)
{
    long mt = *(long *)(meta + -8);
    uint32_t low;
    long shift;
    short result;
    (void)v;
    low = (uint32_t)*low_in;
    shift = FUN_003109b4(meta, p5);
    (*(void (**)(unsigned long _p, ...))(mt + 8))(0, meta);
    if ((long)shift < 0) {
        if (0xfffffffffffffff0 < shift) {
            result = (short)((int)(short)low >> (-(uint32_t)shift & 0x1f));
            goto done;
        }
    } else if (shift < 0x10) {
        result = (short)(low << (unsigned long)((uint32_t)shift & 0x1f));
        goto done;
    }
    result = -((unsigned short)(low >> 0xf) & 1);
done:
    *out = result;
}

/* FUN_002fb7bc @ 0x2fb7bc  (est. sk_swift_int16_shl_self)
 * Int16 shift-left wrapper (in-place self). Width 0x40/0x10. Medium. */
static void sk_swift_int16_shl_self(short *out, unsigned long v, long meta,
                                    unsigned long p4)
{
    long mt = *(long *)(meta + -8);
    short low;
    long shift;
    short result;
    (void)v;
    low = *out;
    shift = FUN_003109b4(meta, p4);
    (*(void (**)(unsigned long _p, ...))(mt + 8))(0, meta);
    if ((long)shift < 0) {
        if (0xfffffffffffffff0 < shift) {
            result = (short)((int)low >> (-(uint32_t)shift & 0x1f));
            goto done;
        }
    } else if (shift < 0x10) {
        result = (short)(low << (unsigned long)((uint32_t)shift & 0x1f));
        goto done;
    }
    result = 0;
done:
    *out = result;
}

/* FUN_002fc180 @ 0x2fc180  (est. sk_swift_int16_parse_c)
 * Int16 decimal string parse (full digit loop with *10+digit accumulation).
 * Confidence: high (pattern-matched). */
static void sk_swift_int16_parse_c(unsigned short *out, unsigned long s2,
                                   unsigned long s3, unsigned long p4, long bound)
{
    unsigned long len;
    unsigned char *buf;
    unsigned long self;
    unsigned char ok;
    unsigned short result;
    long i;
    int digit, acc, prod;
    (void)p4; (void)bound;
    len = s3 >> 0x38 & 0xf;
    self = s2 & 0xffffffffffff;
    if ((s3 & 0x2000000000000000) != 0) self = len;
    if (self == 0) {
        sk_swift_release(s3);
        ok = 1;
        result = 0;
        goto done;
    }
    buf = (unsigned char *)((s3 & 0xfffffffffffffff) + 0x20);
    if (buf[0] == '+') buf++, len--;
    acc = 0; ok = 1;
    if (buf[0] == '-') {
        buf++;
        for (i = 0; i < (long)len; i++) {
            digit = buf[i] - 0x30;
            if (9 < digit) { ok = 0; result = 0; goto done; }
            prod = acc * 10;
            acc = prod - digit;
            if (prod != acc + digit) { ok = 0; result = 0; goto done; }
        }
        result = (unsigned short)acc; goto finish;
    }
    for (i = 0; i < (long)len; i++) {
        digit = buf[i] - 0x30;
        if (9 < digit) { ok = 0; result = 0; goto done; }
        prod = acc * 10;
        acc = prod + digit;
        if (prod != acc - digit) { ok = 0; result = 0; goto done; }
    }
    result = (unsigned short)acc;
finish:
    ok = 0;
done:
    *out = result;
    *((unsigned char *)out + 2) = ok;
}

/* FUN_002fc664 @ 0x2fc664  (est. sk_swift_int16_shift_pair_b)
 * Int16 shift wrapper writing an (out, status) pair with a 0x7fff range
 * check. Width 0x40/0x10. Medium. */
static void sk_swift_int16_shift_pair_b(unsigned short *out, unsigned long v, long meta,
                                        unsigned long p4, unsigned long p5)
{
    long mt = *(long *)(meta + -8);
    (void)v;
    (*(void (**)(unsigned long _p, ...))(mt + 8))(0, meta);
    *out = 0;
    *((unsigned char *)out + 2) = 0;
}
