/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel,
 * arm64e, image base 0) — the cL4 (Apple seL4-derived) microkernel (GL1).
 * Ground truth: Ghidra FUN_ names + addresses in program cl4_kernel.raw.
 * All names are estimates unless string/header-matched.
 *
 * Slice 10: addresses 0x2e6e88 - 0x2eb8d4 (157 functions). This region is the
 * Swift stdlib floating-point layer: Float80 (extended precision), Float and
 * Double conversions (string parsing, integer conversion with range/NaN
 * trapping, exponent/bitPattern extraction, scalbn/ldexp, is-signaling-NaN),
 * the Float80/Double `%`/`%=` operator-availability fatal stubs, small-integer
 * (UInt16/UInt8) division-with-remainder helpers, the obfuscated XOR'd float
 * debug-emit routines, and the generic `Comparable` comparison wrappers.
 */

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <math.h>

typedef unsigned long sk_word;                 /* universal word (undefined8) */
typedef unsigned long (*sk_fn)();              /* Swift method slot / `code *` */
typedef long double sk_f80;                    /* Swift Float80 (x87 80-bit)  */
typedef struct { unsigned long lo, hi; } sk_pair;   /* 16-byte (undefined1[16]) return */

/* Noreturn Swift fatal-error raiser (module/message/file/line encoded). */
extern void sk_fatal_error(unsigned long, unsigned long, ...) __attribute__((noreturn)); /* FUN_001afe4c */
extern void sk_fatal_unavail(unsigned long, unsigned long, ...) __attribute__((noreturn)); /* FUN_001afa84 */

/* Out-of-range kernel/Swift helpers referenced by this region (FUN_ addr in
 * comment; reconstructed by sibling SK range workers). Declared variadic
 * since exact prototypes vary; call sites cast as needed. */
extern unsigned long sk_h_00223960();  /* FUN_00223960 */
extern unsigned long sk_h_00224134();  /* FUN_00224134 */
extern unsigned long sk_h_00224154();  /* FUN_00224154 */
extern unsigned long sk_h_00224180();  /* FUN_00224180 */
extern unsigned long sk_h_0022a644();  /* FUN_0022a644 */
extern unsigned long sk_h_0022aaac();  /* FUN_0022aaac */
extern unsigned long sk_h_0002142c();  /* FUN_0002142c */
extern unsigned long sk_h_00002534();  /* FUN_00002534 */
extern unsigned long sk_h_000651bc();  /* FUN_000651bc */
extern unsigned long sk_h_0006b2ec();  /* FUN_0006b2ec */
extern unsigned long sk_h_0006f768();  /* FUN_0006f768 */
extern unsigned long sk_h_0007c1a4();  /* FUN_0007c1a4 */
extern unsigned long sk_h_000839d8();  /* FUN_000839d8 */
extern unsigned long sk_h_0001a1c8();  /* FUN_0001a1c8 */
extern unsigned long sk_h_0011d7e8();  /* FUN_0011d7e8 */
extern unsigned long sk_h_0011e71c();  /* FUN_0011e71c */
extern unsigned long sk_h_00149368();  /* FUN_00149368 */
extern unsigned long sk_h_001a842c();  /* FUN_001a842c */
extern unsigned long sk_h_001e3698();  /* FUN_001e3698 */
extern unsigned long sk_h_001e655c();  /* FUN_001e655c */
extern unsigned long sk_h_001e6a48();  /* FUN_001e6a48 */

extern unsigned long sk_h_002e507c();  /* FUN_002e507c */
extern unsigned long sk_h_002e5118();  /* FUN_002e5118 */
extern unsigned long sk_h_002e53cc();  /* FUN_002e53cc (returns 16-byte pair) */
extern unsigned long sk_h_002e57b0();  /* FUN_002e57b0 */
extern unsigned long sk_h_002e57e0();  /* FUN_002e57e0 */
extern unsigned long sk_h_002e5a78();  /* FUN_002e5a78 (returns 16-byte pair) */
extern unsigned long sk_h_002e62a0();  /* FUN_002e62a0 */
extern unsigned long sk_h_002e62c4();  /* FUN_002e62c4 */
extern unsigned long sk_h_002e62d0();  /* FUN_002e62d0 */
extern unsigned long sk_h_002e64f0();  /* FUN_002e64f0 */
extern unsigned long sk_h_002e68dc();  /* FUN_002e68dc */
extern unsigned long sk_h_002e68e4();  /* FUN_002e68e4 */
extern unsigned long sk_h_002e694c();  /* FUN_002e694c */
extern unsigned long sk_h_002e6954();  /* FUN_002e6954 */
extern unsigned long sk_h_002e6964();  /* FUN_002e6964 */
extern unsigned long sk_h_002e69e8();  /* FUN_002e69e8 */
extern unsigned long sk_h_002e6a58();  /* FUN_002e6a58 */
extern unsigned long sk_h_002e6af0();  /* FUN_002e6af0 */
extern unsigned long sk_h_002e6bac();  /* FUN_002e6bac */
extern unsigned long sk_h_002e6d80();  /* FUN_002e6d80 */
extern unsigned long sk_h_00267820();  /* FUN_00267820 */

extern unsigned long sk_h_0010d2a8();  /* FUN_0010d2a8 */
extern unsigned long sk_h_0010d44c();  /* FUN_0010d44c */
extern unsigned long sk_h_0010d6b4();  /* FUN_0010d6b4 */
extern unsigned long sk_h_0011169c();  /* FUN_0011169c */

extern unsigned long sk_h_0021ef30();  /* FUN_0021ef30 (16-bit cmp) */
extern unsigned long sk_h_0021ef5c();  /* FUN_0021ef5c (32-bit cmp) */
extern unsigned long sk_h_0021ef80();  /* FUN_0021ef80 (64-bit cmp) */
extern unsigned long sk_h_0021efbc();  /* FUN_0021efbc (16-bit cmp) */
extern unsigned long sk_h_0021efe8();  /* FUN_0021efe8 (32-bit cmp) */
extern unsigned long sk_h_0021f00c();  /* FUN_0021f00c (64-bit cmp) */
extern unsigned long sk_h_0021f104();  /* FUN_0021f104 (16-bit cmp) */
extern unsigned long sk_h_0021f138();  /* FUN_0021f138 (32-bit cmp) */
extern unsigned long sk_h_0021f164();  /* FUN_0021f164 (64-bit cmp) */
extern unsigned long sk_h_0021f1a8();  /* FUN_0021f1a8 (16-bit cmp) */
extern unsigned long sk_h_0021f1dc();  /* FUN_0021f1dc (32-bit cmp) */
extern unsigned long sk_h_0021f208();  /* FUN_0021f208 (64-bit cmp) */

extern unsigned long sk_h_00226320();  /* FUN_00226320 (general string->float parse) */
extern unsigned long sk_h_002298d4();  /* FUN_002298d4 */
extern unsigned long sk_h_0022995c();  /* FUN_0022995c */
extern unsigned long sk_h_002299cc();  /* FUN_002299cc */

extern unsigned long sk_h_00310a14();  /* FUN_00310a14 */
extern unsigned long sk_h_00310a44();  /* FUN_00310a44 */
extern unsigned long sk_h_00310d68();  /* FUN_00310d68 */
extern unsigned long sk_h_003109b4();  /* FUN_003109b4 */
extern unsigned long sk_h_00324958();  /* FUN_00324958 */
extern unsigned long sk_h_003249ac();  /* FUN_003249ac */
extern unsigned long sk_h_00324ca0();  /* FUN_00324ca0 */
extern unsigned long sk_h_00324cd4();  /* FUN_00324cd4 */
extern unsigned long sk_h_00324cdc();  /* FUN_00324cdc */
extern unsigned long sk_h_00324d30();  /* FUN_00324d30 */
extern unsigned long sk_h_00324d84();  /* FUN_00324d84 */
extern unsigned long sk_h_00324ddc();  /* FUN_00324ddc */

extern unsigned long sk_h_00344d4c();  /* FUN_00344d4c */
extern unsigned long sk_h_00347da8();  /* FUN_00347da8 */
extern unsigned long sk_h_00348034();  /* FUN_00348034 */
extern unsigned long sk_h_00348074();  /* FUN_00348074 */
extern unsigned long sk_h_00348404();  /* FUN_00348404 */
extern unsigned long sk_h_003488bc();  /* FUN_003488bc */
extern unsigned long sk_h_00348e00();  /* FUN_00348e00 */
extern unsigned long sk_h_00348f68();  /* FUN_00348f68 */
extern unsigned long sk_h_00349068();  /* FUN_00349068 (returns 16-byte pair) */
extern unsigned long sk_h_0034924c();  /* FUN_0034924c */
extern unsigned long sk_h_003493d8();  /* FUN_003493d8 */
extern unsigned long sk_h_003496b0();  /* FUN_003496b0 */
extern unsigned long sk_h_0034987c();  /* FUN_0034987c */
extern unsigned long sk_h_00349c58();  /* FUN_00349c58 */
extern unsigned long sk_h_00349d14();  /* FUN_00349d14 */
extern unsigned long sk_h_0034acd0();  /* FUN_0034acd0 */
extern unsigned long sk_h_0034b4d0();  /* FUN_0034b4d0 */
extern unsigned long sk_h_0034b918();  /* FUN_0034b918 */
extern unsigned long sk_h_0034bb38();  /* FUN_0034bb38 */
extern unsigned long sk_h_0034bb60();  /* FUN_0034bb60 */
extern unsigned long sk_h_0034bc94();  /* FUN_0034bc94 */
extern unsigned long sk_h_0034bd00();  /* FUN_0034bd00 */
extern unsigned long sk_h_0034c034();  /* FUN_0034c034 */
extern unsigned long sk_h_0034c434();  /* FUN_0034c434 */
extern unsigned long sk_h_0034c5ac();  /* FUN_0034c5ac */
extern unsigned long sk_h_0034d584();  /* FUN_0034d584 */
extern unsigned long sk_h_0034da18();  /* FUN_0034da18 */
extern unsigned long sk_h_0034e0b4();  /* FUN_0034e0b4 */
extern unsigned long sk_h_0034e50c();  /* FUN_0034e50c */
extern unsigned long sk_h_0034ec0c();  /* FUN_0034ec0c */
extern unsigned long sk_h_0034f414();  /* FUN_0034f414 */
extern unsigned long sk_h_0034fc44();  /* FUN_0034fc44 */
extern unsigned long sk_h_0034fc58();  /* FUN_0034fc58 */
extern unsigned long sk_h_0034fef4();  /* FUN_0034fef4 */
extern unsigned long sk_h_0034ff18();  /* FUN_0034ff18 */
extern unsigned long sk_h_00350268();  /* FUN_00350268 */
extern unsigned long sk_h_003504b8();  /* FUN_003504b8 */
extern unsigned long sk_h_0035056c();  /* FUN_0035056c */
extern unsigned long sk_h_003507a4();  /* FUN_003507a4 */
extern unsigned long sk_h_00350c68();  /* FUN_00350c68 */
extern unsigned long sk_h_00351124();  /* FUN_00351124 (returns 16-byte pair) */
extern unsigned long sk_h_003517b4();  /* FUN_003517b4 */
extern unsigned long sk_h_003519c0();  /* FUN_003519c0 */
extern unsigned long sk_h_00351be0();  /* FUN_00351be0 */
extern unsigned long sk_h_00351fc0();  /* FUN_00351fc0 */
extern unsigned long sk_h_0035272c();  /* FUN_0035272c */
extern unsigned long sk_h_00352800();  /* FUN_00352800 */
extern unsigned long sk_h_00354348();  /* FUN_00354348 */
extern unsigned long sk_h_00354588();  /* FUN_00354588 */
extern unsigned long sk_h_0035472c();  /* FUN_0035472c */
extern unsigned long sk_h_00354988();  /* FUN_00354988 */
extern unsigned long sk_h_00354b38();  /* FUN_00354b38 */
extern unsigned long sk_h_00354dc4();  /* FUN_00354dc4 */
extern unsigned long sk_h_00355890();  /* FUN_00355890 */
extern unsigned long sk_h_00355b58();  /* FUN_00355b58 */
extern unsigned long sk_h_00355c10();  /* FUN_00355c10 */
extern unsigned long sk_h_00355ebc();  /* FUN_00355ebc */
extern unsigned long sk_h_00356704();  /* FUN_00356704 */
extern unsigned long sk_h_00356b2c();  /* FUN_00356b2c */
extern unsigned long sk_h_003572b8();  /* FUN_003572b8 */
extern unsigned long sk_h_003572d4();  /* FUN_003572d4 */
extern unsigned long sk_h_00357bd0();  /* FUN_00357bd0 */
extern unsigned long sk_h_00357c74();  /* FUN_00357c74 */
extern unsigned long sk_h_00357cb4();  /* FUN_00357cb4 */
extern unsigned long sk_h_00357958();  /* FUN_00357958 */
extern unsigned long sk_h_00358768();  /* FUN_00358768 */
extern unsigned long sk_h_0035922c();  /* FUN_0035922c */
extern unsigned long sk_h_003592d4();  /* FUN_003592d4 */
extern unsigned long sk_h_00359308();  /* FUN_00359308 */
extern unsigned long sk_h_003593c0();  /* FUN_003593c0 */
extern unsigned long sk_h_0035992c();  /* FUN_0035992c */
extern unsigned long sk_h_0035a690();  /* FUN_0035a690 */
extern unsigned long sk_h_0035ab2c();  /* FUN_0035ab2c */
extern unsigned long sk_h_0035ab54();  /* FUN_0035ab54 */
extern unsigned long sk_h_0035ab7c();  /* FUN_0035ab7c */
extern unsigned long sk_h_0035ac70();  /* FUN_0035ac70 */
extern unsigned long sk_h_00365b6c();  /* FUN_00365b6c */
extern unsigned long sk_h_0036a908();  /* FUN_0036a908 */
extern unsigned long sk_h_0039a030();  /* FUN_0039a030 */
extern unsigned long sk_h_0039a0ac();  /* FUN_0039a0ac */

/* Swift shared method-dispatch slot (DAT_00658c00) and referenced data. */
extern sk_fn sk_g_dispatch;            /* DAT_00658c00 */
extern unsigned long sk_dat_0034721c;  /* DAT_0034721c */
extern unsigned long sk_dat_004f1698;  /* DAT_004f1698 */

/* Pack the low word of an opaque 16-byte helper return into a sk_pair. The
 * pair-returning helpers return in x0/x1; our variadic externs expose only
 * the low word, so the hi word is treated as 0. */
static inline sk_pair sk_pair_from(unsigned long lo)
{
    sk_pair p;
    p.lo = lo;
    p.hi = 0;
    return p;
}

/* Local canary read helper used by the string-build routines. */
static unsigned long local_canary(void) { return 0; }

/* In-slice forward declarations (defined below). */
static sk_f80 sk_swift_f64_to_f80_bits(unsigned long);
static unsigned int sk_swift_u16_divrem(unsigned int a, unsigned int b, unsigned int c);
static unsigned long sk_swift_u16_div_hi(unsigned long a, unsigned char b);
static sk_pair sk_swift_f80_word_box_fill(sk_word box, long idx, unsigned long val);
static void sk_swift_f80_str_idx_loop(void);
static void sk_swift_f80_mod_unavailable(void);
static void sk_swift_f80_modassign_unavailable(void);
static float sk_swift_f32_str_parse(sk_word p1, long str_storage, sk_word str_meta);
static unsigned long sk_swift_f32_to_uint(sk_word p1, long str_storage, sk_word str_meta);
static double sk_swift_f64_from_str_word(sk_word p1, long str_storage, sk_word str_meta);

/* Int64 bounds as floating-point (DAT_004e7d78 / DAT_004e7cd0: the memory at
 * those addresses is an indirect constant slot whose byte is 0x01; the value
 * is the representable Int64.min bound used by the integer-conversion traps). */
static const double sk_dbl_i64_min = -9.223372036854776e18; /* DAT_004e7d78 */
static const double sk_dbl_i64_min_b = -9.223372036854776e18; /* DAT_004e7cd0 */

/* Release a boxed Swift value via its vtable slot:
 *   (**(code **)(*(long *)(box + -8) + 8))(self, box)                        */
static inline void sk_rel_box(unsigned long self, unsigned long box)
{
    ((sk_fn)*(void **)(*(unsigned long *)(box - 8) + 8))(self, box);
}

/* ------------------------------------------------------------------ *
 * 5-arg string/character forwarders (thunks to shared compare helpers).
 * ------------------------------------------------------------------ */

/* FUN_002e6e88 @ 0x002e6e88   (est. sk_swift_str_cmp_thunk_a)
 * Ghidra: void FUN_002e6e88(undefined8,undefined8,undefined8,undefined8,undefined8)
 * Forwards five args to the shared 5-arg compare helper FUN_00223960 after
 * reordering them (1,4,2,5,3). Thin out-of-line thunk in the String
 * comparison / hash-equality chain.
 * Confidence: medium
 * Notes: arg permutation preserved verbatim. */
void sk_swift_str_cmp_thunk_a(sk_word p1, sk_word p2, sk_word p3, sk_word p4, sk_word p5)
{
    sk_h_00223960(p1, p4, p2, p5, p3);
}

/* FUN_002e6eb0 @ 0x002e6eb0   (est. sk_swift_str_cmp_thunk_b)
 * Ghidra: void FUN_002e6eb0(undefined8,undefined8,undefined8,undefined8,undefined8)
 * Forwards five args to the shared compare helper FUN_00224180 reordered
 * (1,4,2,5,3). Thin out-of-line thunk.
 * Confidence: medium
 * Notes: arg permutation preserved verbatim. */
void sk_swift_str_cmp_thunk_b(sk_word p1, sk_word p2, sk_word p3, sk_word p4, sk_word p5)
{
    sk_h_00224180(p1, p4, p2, p5, p3);
}

/* FUN_002e6eb4 @ 0x002e6eb4   (est. sk_swift_str_cmp_thunk_b2)
 * Ghidra: void FUN_002e6eb4(undefined8,undefined8,undefined8,undefined8,undefined8)
 * Identical to sk_swift_str_cmp_thunk_b: reordered forward to FUN_00224180.
 * A duplicate out-of-line thunk in the same compare chain.
 * Confidence: medium
 * Notes: arg permutation preserved verbatim. */
void sk_swift_str_cmp_thunk_b2(sk_word p1, sk_word p2, sk_word p3, sk_word p4, sk_word p5)
{
    sk_h_00224180(p1, p4, p2, p5, p3);
}

/* FUN_002e6edc @ 0x002e6edc   (est. sk_swift_f80_read_word)
 * Ghidra: void FUN_002e6edc(undefined8 *param_1)
 * Reads the Float80 self value held in the x20 register, passes it through
 * the Float80 conversion helper FUN_002e507c, and stores the resulting word
 * to *param_1. The x20 self register is unrecovered.
 * Confidence: low
 * Notes: unaff_x20 self register not recovered. */
void sk_swift_f80_read_word(sk_word *out)
{
    sk_word self = 0;  /* unaff_x20 (unrecovered) */
    *out = (sk_word)sk_h_002e507c(self);
}

/* FUN_002e6f08 @ 0x002e6f08   (est. sk_swift_f80_read_word_2e5118)
 * Ghidra: void FUN_002e6f08(undefined2 *param_1)
 * Stores the result of the Float80 helper FUN_002e5118 applied to the x20
 * self value. Output is the low 16 bits (undefined2).
 * Confidence: low
 * Notes: unaff_x20 self register not recovered. */
void sk_swift_f80_read_word_2e5118(unsigned short *out)
{
    sk_word self = 0;  /* unaff_x20 */
    *out = (unsigned short)sk_h_002e5118(self);
}

/* FUN_002e6f38 @ 0x002e6f38   (est. sk_swift_f80_read_word_2e6d80)
 * Ghidra: void FUN_002e6f38(undefined2 *param_1)
 * Stores the result of the Float80 helper FUN_002e6d80 applied to the x20
 * self value as the low 16 bits.
 * Confidence: low
 * Notes: unaff_x20 self register not recovered. */
void sk_swift_f80_read_word_2e6d80(unsigned short *out)
{
    sk_word self = 0;  /* unaff_x20 */
    *out = (unsigned short)sk_h_002e6d80(self);
}

/* FUN_002e6f6c @ 0x002e6f6c   (est. sk_swift_f80_binop_thunk)
 * Ghidra: void FUN_002e6f6c(undefined2 *param_1,undefined8 param_2,
 *        undefined8 *param_3,undefined2 *param_4)
 * Applies the Float80 binary helper FUN_002e6af0 to the two operands
 * *param_4 and param_2 plus the dereferenced *param_3, storing the low
 * 16-bit result to *param_1. Thin Float80 arithmetic thunk.
 * Confidence: low
 * Notes: operand order and widths follow the decompile. */
void sk_swift_f80_binop_thunk(unsigned short *out, sk_word b, sk_word *c, unsigned short *d)
{
    *out = (unsigned short)sk_h_002e6af0((sk_word)*d, b, (sk_word)*c);
}

/* FUN_002e6fc0 @ 0x002e6fc0   (est. sk_swift_f80_str_parse)
 * Ghidra: void FUN_002e6fc0(float2 *param_1,undefined8 param_2,long param_3,
 *        undefined8 param_4, undefined8 param_5)
 * Parses a Swift String {param_3,param_4} into a Float80 (extended) value and
 * stores it to *param_1. Fast path: when the string byte-count (read through
 * the FUN_00310a44 / 00310a14 / 003109b4 witness slots) is < 0x41, the small
 * inline buffer's payload bits are reinterpreted as the value; otherwise the
 * general parser FUN_00226320 is used. The boxed string is released via its
 * vtable slot on both paths.
 * Confidence: medium
 * Notes: Swift string-witness indirect calls via sk_fn casts. */
void sk_swift_f80_str_parse(sk_f80 *out, sk_word p2, long str_storage, sk_word str_meta, sk_word p5)
{
    sk_f80 local;
    long cnt = ((sk_fn)(sk_word)sk_h_00310a44(str_meta))(str_storage, str_meta);
    if (cnt < 0x41) {
        sk_word bits = ((sk_fn)(sk_word)sk_h_00310a14(str_meta))(str_storage, str_meta);
        sk_word payload = ((sk_fn)(sk_word)sk_h_003109b4(str_meta))(str_storage, str_meta);
        sk_rel_box(p2, str_storage);
        local = (bits & 1) ? (sk_f80)(long)payload : (sk_f80)(sk_word)payload;
    } else {
        sk_word a = (sk_word)sk_h_00324cdc();
        sk_word b = (sk_word)sk_h_00324d30();
        sk_h_00226320(&local, p2, p5, str_storage, a, str_meta, b);
        sk_rel_box(p2, str_storage);
    }
    *out = local;
}

/* FUN_002e7114 @ 0x002e7114   (est. sk_swift_f80_str_parse_out)
 * Ghidra: void FUN_002e7114(undefined8,undefined8,undefined8)
 * Out-of-line Float80-from-string parser: runs the fixed Swift runtime
 * sequence (FUN_00357cb4/0034f414/003507a4/0034e50c), then dispatches either
 * the small-buffer fast path (via FUN_0034acd0/0034b4d0/0034e50c witness
 * reads) or the general parser FUN_00226320 with the Float80 runtime tokens,
 * finally handing the resulting value to FUN_00357c74. The condition-code /
 * method-slot pointers from the runtime calls are unrecovered.
 * Confidence: low
 * Notes: extraout_* CC/method-slot artifacts not fully recoverable. */
void sk_swift_f80_str_parse_out(sk_word p1, sk_word p2, sk_word p3)
{
    sk_f80 val = 0;
    sk_h_00357cb4();
    sk_h_0034f414();
    sk_h_003507a4(p3);
    sk_h_0034e50c();
    long cnt = ((sk_fn)(sk_word)sk_h_00310a44(p3))(0, p3);
    if (cnt < 0x41) {
        sk_h_0034acd0();
        sk_word bits = ((sk_fn)(sk_word)sk_h_00310a14(p3))(0, p3);
        sk_h_0034b4d0();
        sk_h_0034e50c();
        sk_word payload = ((sk_fn)(sk_word)sk_h_003109b4(p3))(0, p3);
        sk_h_003572b8();
        val = (bits & 1) ? (sk_f80)(long)payload : (sk_f80)(sk_word)payload;
    } else {
        sk_word a = (sk_word)sk_h_00324cdc();
        sk_word b = (sk_word)sk_h_00324d30();
        sk_h_00355b58(&val);
        sk_h_00226320();
        sk_h_003572b8();
    }
    sk_h_00357c74(val, p1);
}

/* FUN_002e7210 @ 0x002e7210   (est. sk_swift_f80_str_parse_split16)
 * Ghidra: void FUN_002e7210(undefined2 *param_1)
 * Calls the Float-from-string parser FUN_002e7240 (0x002e7240, in slice),
 * splits the returned 32-bit float word into a low 16-bit short (written to
 * param_1[0]) and its byte-16 value (written to param_1[1]). Odd split that
 * Ghidra decoded from a wider store; kept verbatim.
 * Confidence: low
 * Notes: Ghidra split of the store is preserved literally. */
void sk_swift_f80_str_parse_split16(unsigned short *out)
{
    sk_word u = (sk_word)sk_swift_f32_str_parse(0, 0, 0);
    *out = (unsigned short)u;
    *(char *)(out + 1) = (char)((unsigned)u >> 0x10);
}

/* FUN_002e7240 @ 0x002e7240   (est. sk_swift_f32_str_parse)
 * Ghidra: float FUN_002e7240(undefined8,long,undefined8)
 * Parses a Swift String {param_2,param_3} into a Float value. Fast path reads
 * the string's byte-count and payload through the FUN_00310a44/00310a14/
 * 003109b4 witness slots (count < 0x41); the Float80-vs-constant NaN checks
 * and the integrality check (`payload == (long)local`) mirror the decompile.
 * The slow path uses the general parser FUN_00226320. Returns the Float (or a
 * subnormal NaN sentinel on failure).
 * Confidence: low
 * Notes: Float80 NaN bit-pattern constants preserved structurally. */
float sk_swift_f32_str_parse(sk_word p1, long str_storage, sk_word str_meta)
{
    sk_f80 local = 0;
    sk_f80 sentinel = (sk_f80)9.18355e-41f;
    sk_f80 nanpat = (sk_f80)4.44828e-41f;
    long cnt = ((sk_fn)(sk_word)sk_h_00310a44(str_meta))(str_storage, str_meta);
    if (cnt < 0x41) {
        sk_word bits = ((sk_fn)(sk_word)sk_h_00310a14(str_meta))(str_storage, str_meta);
        sk_word payload = ((sk_fn)(sk_word)sk_h_003109b4(str_meta))(str_storage, str_meta);
        if ((bits & 1) == 0) {
            sk_f80 v = (sk_f80)(sk_word)payload;
            sk_rel_box(p1, str_storage);
            if (v == nanpat || isnan(v) || isnan(nanpat)) return (float)sentinel;
            local = v;
            if (payload != (sk_word)local) return (float)sentinel;
        } else {
            sk_f80 v = (sk_f80)(long)payload;
            sk_rel_box(p1, str_storage);
            if (v == nanpat || isnan(v) || isnan(nanpat)) return (float)sentinel;
            local = (sk_f80)(long)payload;
            if (payload != (sk_word)local) return (float)sentinel;
        }
    } else {
        sk_word a = (sk_word)sk_h_00324cdc();
        sk_word b = (sk_word)sk_h_00324d30();
        sk_word r = (sk_word)sk_h_00226320(&local, p1, 0x677518, str_storage, a, str_meta, b);
        sk_rel_box(p1, str_storage);
        if ((r & 1) == 0) return (float)sentinel;
    }
    return (float)local;
}

/* ------------------------------------------------------------------ *
 * Float80 property getters (negate/abs/etc. wrappers over in-region helpers).
 * ------------------------------------------------------------------ */

/* FUN_002e7410 @ 0x002e7410   (est. sk_swift_f80_prop_2e68e4)
 * Ghidra: void FUN_002e7410(undefined2 *param_1)
 * Stores the low 16 bits of the Float80 property helper FUN_002e68e4 result.
 * Confidence: low
 * Notes: result truncated to 16 bits per decompile. */
void sk_swift_f80_prop_2e68e4(unsigned short *out)
{
    *out = (unsigned short)sk_h_002e68e4();
}

/* FUN_002e7438 @ 0x002e7438   (est. sk_swift_f80_prop_2e694c)
 * Ghidra: void FUN_002e7438(undefined2 *param_1)
 * Stores the low 16 bits of the Float80 property helper FUN_002e694c result.
 * Confidence: low
 * Notes: result truncated to 16 bits per decompile. */
void sk_swift_f80_prop_2e694c(unsigned short *out)
{
    *out = (unsigned short)sk_h_002e694c();
}

/* FUN_002e7460 @ 0x002e7460   (est. sk_swift_f80_prop_2e68dc)
 * Ghidra: void FUN_002e7460(undefined2 *param_1)
 * Stores the low 16 bits of the Float80 property helper FUN_002e68dc result.
 * Confidence: low
 * Notes: result truncated to 16 bits per decompile. */
void sk_swift_f80_prop_2e68dc(unsigned short *out)
{
    *out = (unsigned short)sk_h_002e68dc();
}

/* FUN_002e7488 @ 0x002e7488   (est. sk_swift_f80_prop_2e6954)
 * Ghidra: void FUN_002e7488(undefined2 *param_1)
 * Stores the low 16 bits of the Float80 property helper FUN_002e6954 result.
 * Confidence: low
 * Notes: result truncated to 16 bits per decompile. */
void sk_swift_f80_prop_2e6954(unsigned short *out)
{
    *out = (unsigned short)sk_h_002e6954();
}

/* FUN_002e74c0 @ 0x002e74c0   (est. sk_swift_f80_prop_self_2e6964)
 * Ghidra: void FUN_002e74c0(undefined2 *param_1)
 * Applies the Float80 property helper FUN_002e6964 to the x20 self value and
 * stores the low 16 bits.
 * Confidence: low
 * Notes: unaff_x20 self register not recovered. */
void sk_swift_f80_prop_self_2e6964(unsigned short *out)
{
    sk_word self = 0;  /* unaff_x20 */
    *out = (unsigned short)sk_h_002e6964(self);
}

/* FUN_002e7524 @ 0x002e7524   (est. sk_swift_f80_prop_self_2e69e8)
 * Ghidra: void FUN_002e7524(undefined8 *param_1)
 * Applies the Float80 property helper FUN_002e69e8 to the x20 self value and
 * stores the resulting word.
 * Confidence: low
 * Notes: unaff_x20 self register not recovered. */
void sk_swift_f80_prop_self_2e69e8(sk_word *out)
{
    sk_word self = 0;  /* unaff_x20 */
    *out = (sk_word)sk_h_002e69e8(self);
}

/* FUN_002e7550 @ 0x002e7550   (est. sk_swift_f80_prop_self_2e6a58)
 * Ghidra: void FUN_002e7550(undefined2 *param_1)
 * Applies the Float80 property helper FUN_002e6a58 to the x20 self value and
 * stores the low 16 bits.
 * Confidence: low
 * Notes: unaff_x20 self register not recovered. */
void sk_swift_f80_prop_self_2e6a58(unsigned short *out)
{
    sk_word self = 0;  /* unaff_x20 */
    *out = (unsigned short)sk_h_002e6a58(self);
}

/* ------------------------------------------------------------------ *
 * Float80/Float binary & unary arithmetic thunks.
 * ------------------------------------------------------------------ */

/* FUN_002e75ac @ 0x002e75ac   (est. sk_swift_f80_binop_a_store)
 * Ghidra: void FUN_002e75ac(float2 *param_1,float2 *param_2)
 * Computes a Float80 binary operation (via FUN_0010d6b4) on the low Float
 * halves of the two Float80 operands and stores the widened result.
 * Confidence: low
 * Notes: operands read as Float (SUB42), result widened to Float80. */
void sk_swift_f80_binop_a_store(sk_f80 *out, sk_f80 *b)
{
    float r = (float)sk_h_0010d6b4(*(float *)out, *(float *)b);
    *out = (sk_f80)r;
}

/* FUN_002e75e8 @ 0x002e75e8   (est. sk_swift_f80_binop_a_mutate)
 * Ghidra: void FUN_002e75e8(float2 *param_1)
 * In-place Float80 binary operation (FUN_0010d6b4) on the low Float halves of
 * the self (x20) and *param_1; stores back into the self slot.
 * Confidence: low
 * Notes: operands read as Float; in-place update. */
void sk_swift_f80_binop_a_mutate(sk_f80 *b)
{
    sk_f80 self = 0;  /* unaff_x20 */
    float r = (float)sk_h_0010d6b4(*(float *)&self, *(float *)b);
    self = (sk_f80)r;
    *(float *)b = *(float *)&self;  /* store back through self slot (approx) */
}

/* FUN_002e75ec @ 0x002e75ec   (est. sk_swift_f80_binop_a_mutate2)
 * Ghidra: void FUN_002e75ec(float2 *param_1)
 * Same in-place Float80 binary operation as FUN_002e75e8 (duplicate thunk).
 * Confidence: low
 * Notes: operands read as Float; in-place update. */
void sk_swift_f80_binop_a_mutate2(sk_f80 *b)
{
    sk_f80 self = 0;  /* unaff_x20 */
    float r = (float)sk_h_0010d6b4(*(float *)&self, *(float *)b);
    self = (sk_f80)r;
    *(float *)b = *(float *)&self;  /* store back through self slot (approx) */
}

/* FUN_002e7618 @ 0x002e7618   (est. sk_swift_f80_binop_b_store)
 * Ghidra: void FUN_002e7618(float2 *param_1,float2 *param_2)
 * Computes a Float80 binary operation (via FUN_0010d2a8) on the low Float
 * halves of the two operands and stores the widened result.
 * Confidence: low
 * Notes: operands read as Float (SUB42), result widened to Float80. */
void sk_swift_f80_binop_b_store(sk_f80 *out, sk_f80 *b)
{
    float r = (float)sk_h_0010d2a8(*(float *)out, *(float *)b);
    *out = (sk_f80)r;
}

/* FUN_002e7654 @ 0x002e7654   (est. sk_swift_f80_binop_b_mutate)
 * Ghidra: void FUN_002e7654(float2 *param_1)
 * In-place Float80 binary operation (FUN_0010d2a8) on the low Float halves of
 * self and *param_1; stores back into the self slot.
 * Confidence: low
 * Notes: operands read as Float; in-place update. */
void sk_swift_f80_binop_b_mutate(sk_f80 *b)
{
    sk_f80 self = 0;  /* unaff_x20 */
    float r = (float)sk_h_0010d2a8(*(float *)&self, *(float *)b);
    self = (sk_f80)r;
    *(float *)b = *(float *)&self;  /* store back through self slot (approx) */
}

/* FUN_002e7658 @ 0x002e7658   (est. sk_swift_f80_binop_b_mutate2)
 * Ghidra: void FUN_002e7658(float2 *param_1)
 * Same in-place Float80 binary operation as FUN_002e7654 (duplicate thunk).
 * Confidence: low
 * Notes: operands read as Float; in-place update. */
void sk_swift_f80_binop_b_mutate2(sk_f80 *b)
{
    sk_f80 self = 0;  /* unaff_x20 */
    float r = (float)sk_h_0010d2a8(*(float *)&self, *(float *)b);
    self = (sk_f80)r;
    *(float *)b = *(float *)&self;  /* store back through self slot (approx) */
}

/* FUN_002e7684 @ 0x002e7684   (est. sk_swift_f80_unop_store)
 * Ghidra: void FUN_002e7684(float2 *param_1)
 * Applies the Float unary helper FUN_00324cd4 to the low Float half of the
 * x20 self and stores the widened Float80 result.
 * Confidence: low
 * Notes: operand read as Float; result widened to Float80. */
void sk_swift_f80_unop_store(sk_f80 *out)
{
    sk_f80 self = 0;  /* unaff_x20 */
    *out = (sk_f80)(float)sk_h_00324cd4(*(float *)&self);
}

/* FUN_002e76b8 @ 0x002e76b8   (est. sk_swift_f80_unop_mutate)
 * Ghidra: void FUN_002e76b8(void)
 * In-place Float unary operation (FUN_00324cd4) on the low Float half of the
 * x20 self; result widened and stored back through the self slot.
 * Confidence: low
 * Notes: unaff_x20 self register not recovered. */
void sk_swift_f80_unop_mutate(void)
{
    sk_f80 self = 0;  /* unaff_x20 */
    float r = (float)sk_h_00324cd4(*(float *)&self);
    self = (sk_f80)r;
}

/* FUN_002e76bc @ 0x002e76bc   (est. sk_swift_f80_unop_mutate2)
 * Ghidra: void FUN_002e76bc(void)
 * Duplicate of FUN_002e76b8 (in-place Float unary on x20 self).
 * Confidence: low
 * Notes: unaff_x20 self register not recovered. */
void sk_swift_f80_unop_mutate2(void)
{
    sk_f80 self = 0;  /* unaff_x20 */
    float r = (float)sk_h_00324cd4(*(float *)&self);
    self = (sk_f80)r;
}

/* FUN_002e7710 @ 0x002e7710   (est. sk_swift_cmp16_a)
 * Ghidra: void FUN_002e7710(undefined2 *param_1,undefined2 *param_2,undefined2 *param_3)
 * 16-bit Comparable helper: stores FUN_0021ef30(*param_2,*param_3) to
 * *param_1. One of the UInt16 comparison operator thunks.
 * Confidence: medium
 * Notes: comparison operator identity (==,<,<=,>) not resolvable. */
void sk_swift_cmp16_a(unsigned short *out, unsigned short *a, unsigned short *b)
{
    *out = (unsigned short)sk_h_0021ef30((sk_word)*a, (sk_word)*b);
}

/* FUN_002e7740 @ 0x002e7740   (est. sk_swift_cmp16_b)
 * Ghidra: void FUN_002e7740(undefined2 *param_1,undefined2 *param_2,undefined2 *param_3)
 * 16-bit Comparable helper via FUN_0021efbc.
 * Confidence: medium
 * Notes: comparison operator identity not resolvable. */
void sk_swift_cmp16_b(unsigned short *out, unsigned short *a, unsigned short *b)
{
    *out = (unsigned short)sk_h_0021efbc((sk_word)*a, (sk_word)*b);
}

/* FUN_002e7770 @ 0x002e7770   (est. sk_swift_cmp16_c)
 * Ghidra: void FUN_002e7770(undefined2 *param_1,undefined2 *param_2,undefined2 *param_3)
 * 16-bit Comparable helper via FUN_0021f104.
 * Confidence: medium
 * Notes: comparison operator identity not resolvable. */
void sk_swift_cmp16_c(unsigned short *out, unsigned short *a, unsigned short *b)
{
    *out = (unsigned short)sk_h_0021f104((sk_word)*a, (sk_word)*b);
}

/* FUN_002e77a0 @ 0x002e77a0   (est. sk_swift_cmp16_d)
 * Ghidra: void FUN_002e77a0(undefined2 *param_1,undefined2 *param_2,undefined2 *param_3)
 * 16-bit Comparable helper via FUN_0021f1a8.
 * Confidence: medium
 * Notes: comparison operator identity not resolvable. */
void sk_swift_cmp16_d(unsigned short *out, unsigned short *a, unsigned short *b)
{
    *out = (unsigned short)sk_h_0021f1a8((sk_word)*a, (sk_word)*b);
}

/* FUN_002e7920 @ 0x002e7920   (est. sk_swift_f80_negate)
 * Ghidra: void FUN_002e7920(float2 *param_1)
 * Float80 negation: applies FUN_002e6bac to the negated self and stores the
 * negated result.
 * Confidence: low
 * Notes: unaff_x20 self register not recovered. */
void sk_swift_f80_negate(sk_f80 *out)
{
    sk_f80 self = 0;  /* unaff_x20 */
    sk_f80 r = (sk_f80)sk_h_002e6bac(-self);
    *out = -r;
}

/* FUN_002e7b38 @ 0x002e7b38   (est. sk_swift_f32_ulp_round)
 * Ghidra: void FUN_002e7b38(float2 *param_1)
 * Stores the Float produced by the round/ulp helper FUN_0039a030 widened to
 * a Float80.
 * Confidence: low
 * Notes: result widened to Float80. */
void sk_swift_f32_ulp_round(sk_f80 *out)
{
    *out = (sk_f80)(float)sk_h_0039a030();
}

/* FUN_002e7b74 @ 0x002e7b74   (est. sk_swift_f32_emit_if_nonzero)
 * Ghidra: void FUN_002e7b74(float2 param_1)
 * Emits the low Float of param_1 through FUN_002299cc, substituting 0.0 when
 * the value is zero. A Float debug/description emit helper.
 * Confidence: low
 * Notes: Float80 arg read; zero is suppressed. */
void sk_swift_f32_emit_if_nonzero(sk_f80 v)
{
    float f = 0.0f;
    if ((float)v != 0.0f) f = (float)v;
    sk_h_002299cc(f);
}

/* FUN_002e7c1c @ 0x002e7c1c   (est. sk_swift_trap_f80_div)
 * Ghidra: void FUN_002e7c1c(void)
 * Division-by-zero / overflow trap for the Float80 arithmetic path: calls the
 * trap runtime (FUN_003488bc(1), FUN_003493d8, FUN_00351be0) then the noreturn
 * fatal FUN_001afe4c.
 * Confidence: medium
 * Notes: noreturn. */
void sk_swift_trap_f80_div(void)
{
    sk_h_003488bc(1);
    sk_h_003493d8();
    sk_h_00351be0();
    sk_fatal_error(0, 0);
    __builtin_unreachable();
}

/* FUN_002e7c50 @ 0x002e7c50   (est. sk_swift_f80_to_int)
 * Ghidra: long FUN_002e7c50(void)
 * Converts the Float80 self (module-global, read via FUN_0035ab7c) to Int.
 * The FP-compare condition-code flags from FUN_0034d584 gate the truncation;
 * NaN or out-of-range values fall through to the noreturn overflow trap.
 * Reconstructed at low confidence: the CC flags are not recoverable, so the
 * finite in-range path is assumed and NaN traps.
 * Confidence: low
 * Notes: CC (Z/N/V) flags from FUN_0034d584 unrecovered. */
long sk_swift_f80_to_int(void)
{
    sk_h_0034d584();
    sk_f80 v = (sk_f80)sk_h_0035ab7c();
    if (!isnan((double)v)) return (long)v;
    sk_h_003488bc(1);
    sk_h_003493d8();
    sk_h_00351be0();
    sk_fatal_error(0, 0);
    __builtin_unreachable();
}

/* ------------------------------------------------------------------ *
 * String index / range iteration helpers (Float80 string formatting).
 * ------------------------------------------------------------------ */

/* FUN_002e7db0 @ 0x002e7db0   (est. sk_swift_f80_str_idx_enter)
 * Ghidra: void FUN_002e7db0(void)
 * Thin forwarder to FUN_002e7dd8 (in slice): enters the Float80 string index
 * iteration with the bound check.
 * Confidence: medium
 * Notes: pure forward. */
void sk_swift_f80_str_idx_enter(void)
{
    sk_swift_f80_str_idx_loop();
}

/* FUN_002e7dd8 @ 0x002e7dd8   (est. sk_swift_f80_str_idx_loop)
 * Ghidra: void FUN_002e7dd8(void)
 * Float80 string index iteration loop. Reads the current string range from
 * FUN_002e53cc (in-region pair helper), traps via SoftwareBreakpoint on a
 * borrow during the range subtraction, and walks the encoded characters with
 * the Swift runtime digit/decode helpers (FUN_003496b0 etc.), assembling a
 * 0xe000000000000000-tagged value handed to FUN_00354b38. On success the
 * frame is released through FUN_000651bc; the "object reused" check passes
 * via FUN_0011d7e8 when the range was not empty.
 * Confidence: low
 * Notes: dense Swift runtime sequence; digit helpers un-named. */
void sk_swift_f80_str_idx_loop(void)
{
    sk_word self = 0;  /* unaff */
    sk_word n = 0;
    sk_word m = 0;
    sk_word flags = 0;
    sk_h_0006b2ec();
    sk_h_0034ff18();
    sk_pair r = sk_pair_from(sk_h_002e53cc());
    sk_word hi = r.hi, lo = r.lo;
    int borrow = (hi < lo);
    if (borrow) {
        __builtin_trap();  /* SoftwareBreakpoint(1,0x2e7e98) */
    }
    if (hi == lo) {
        sk_h_0011e71c();
    } else {
        sk_h_00356704();
        if (flags || 1) {   /* (uVar5 || cVar4 != cVar3): branch taken */
            sk_h_00358768();
            if (sk_h_00347da8()) {
                sk_h_003504b8();
                sk_fatal_error(0, 0);
                __builtin_unreachable();
            }
            sk_h_0034e0b4();
            do { sk_h_003496b0(); } while (flags);
            flags = (sk_h_0034da18() == 9);
            if (8 < (long)sk_h_0034da18()) {
                if (sk_h_00348034()) goto fail;
                sk_h_0034da18();
                do { sk_h_0034b918(); } while (flags);
            }
            sk_h_0034ec0c();
            sk_word tag = 0xe000000000000000;
            if (!flags) tag = (sk_word)sk_h_00354b38(tag);
            sk_h_00354b38(tag);
        } else {
            sk_h_00354988();
            sk_h_00355c10();
        }
    }
    sk_h_000651bc(n);
    if (flags) return;
fail:
    sk_h_003504b8();
    sk_fatal_error(0, 0);
    __builtin_unreachable();
}

/* FUN_002e7eb4 @ 0x002e7eb4   (est. sk_swift_str_build_bytes)
 * Ghidra: void FUN_002e7eb4(void)
 * Builds a byte string from the in-region range helper FUN_002e53cc applied
 * to a stack buffer filled with '0' characters (0x30), then hands the tagged
 * slice to FUN_00267820. A Swift String/collection construction helper with
 * the "object reused" canary check (local_28) leading to the noreturn
 * FUN_0011d7e8 on reuse.
 * Confidence: low
 * Notes: stack canary + reuse check; byte string built from '0' fill. */
void sk_swift_str_build_bytes(void)
{
    sk_word canary = (sk_word)(long)-0x2c8502b44bfffed6;   /* local_28 */
    unsigned long buf[8];
    for (int i = 0; i < 8; i++) buf[i] = 0x3030303030303030;
    unsigned long *head = &buf[0];
    unsigned long len_slot = 0x40;
    sk_pair r = sk_pair_from(sk_h_002e53cc(&head));
    unsigned long off = r.lo;
    if (r.hi < off) {
        __builtin_trap();  /* SoftwareBreakpoint(1,0x2e7f4c) */
    }
    sk_h_00267820((r.hi - off) | 0xd000000000000000,
                  ((unsigned long)(buf + 0) + off) | 0x8000000000000000);
    if ((sk_word)(long)local_canary() == canary) return;
    sk_fatal_error(0, 0);
    __builtin_unreachable();
}

/* FUN_002e7f50 @ 0x002e7f50   (est. sk_swift_str_emit_empty_check)
 * Ghidra: void FUN_002e7f50(void)
 * Emits a string whose emptiness is determined by the range helper
 * FUN_002e53cc; traps on a borrow in the range subtraction. Runs the Swift
 * runtime emission sequence (FUN_0034c034/0006b2ec/0034fef4 then the
 * dispatch-slot calls) and releases the frame via FUN_000651bc; on a non-empty
 * range the "object reused" noreturn FUN_0011d7e8 is taken.
 * Confidence: low
 * Notes: dense runtime emission; range from FUN_002e53cc. */
void sk_swift_str_emit_empty_check(void)
{
    sk_word flags = 0;
    sk_h_0034c034();
    sk_h_0006b2ec();
    sk_h_0034fef4();
    sk_pair r = sk_pair_from(sk_h_002e53cc());
    flags = (r.hi == r.lo);
    if (r.hi < r.lo) {
        __builtin_trap();  /* SoftwareBreakpoint(1,0x2e7fc4) */
    }
    sk_h_00354dc4();
    sk_h_00324ca0();
    sk_h_0035a690();
    sk_h_0034c5ac();
    ((sk_fn)(sk_word)sk_g_dispatch)();
    sk_h_000651bc(0);
    if (flags) return;
    sk_fatal_error(0, 0);
    __builtin_unreachable();
}

/* ------------------------------------------------------------------ *
 * Float bitPattern / exponent / normalize helpers.
 * ------------------------------------------------------------------ */

/* FUN_002e8010 @ 0x002e8010   (est. sk_swift_f32_nan_bits)
 * Ghidra: undefined4 FUN_002e8010(void)
 * Returns the constant Float NaN bit pattern 0x7fa00000 (a signaling-NaN
 * word). Used to materialize Float.nan.
 * Confidence: high
 * Notes: constant-return leaf. */
unsigned int sk_swift_f32_nan_bits(void)
{
    return 0x7fa00000u;
}

/* FUN_002e8040 @ 0x002e8040   (est. sk_swift_trap_f32_range)
 * Ghidra: void FUN_002e8040(void)
 * Floating-point range / overflow trap: calls FUN_003488bc(1), FUN_0034987c
 * then the noreturn fatal FUN_001afe4c.
 * Confidence: medium
 * Notes: noreturn. */
void sk_swift_trap_f32_range(void)
{
    sk_h_003488bc(1);
    sk_h_0034987c();
    sk_fatal_error(0, 0);
    __builtin_unreachable();
}

/* FUN_002e8090 @ 0x002e8090   (est. sk_swift_f32_to_f80)
 * Ghidra: undefined1[16] FUN_002e8090(uint param_1)
 * Widens a Float bit pattern (param_1) to a Float80 value. For a zero
 * exponent the subnormal path goes through FUN_00359308; otherwise the
 * value is (mantissa-exponent bits) scaled by 2^-23. Returns the widened
 * Float80 (built into a 16-byte slot by the caller).
 * Confidence: low
 * Notes: returned as sk_f80; subnormal path via FUN_00359308. */
sk_f80 sk_swift_f32_to_f80(unsigned int bits)
{
    unsigned int exp = (bits >> 0x17) & 0xff;
    if (exp != 0) {
        if (exp == 0xff) return NAN;
        return (sk_f80)((bits & 0x7f800000u) * 1.1920929e-07f);
    }
    sk_h_00359308();
    return 0.0L;
}

/* FUN_002e80e8 @ 0x002e80e8   (est. sk_swift_f32_exponent)
 * Ghidra: long FUN_002e80e8(uint param_1)
 * Returns the binary exponent of the Float bit pattern param_1 as an Int
 * (Swift `Float.exponent`). Handles NaN/Inf (0x7fffffffffffffff), normal
 * (exp-127), and subnormal (leading-zero-count via FUN_0022a644) cases with
 * SoftwareBreakpoint traps on the borrow edges.
 * Confidence: medium
 * Notes: exponent of a float bit pattern. */
long sk_swift_f32_exponent(unsigned int bits)
{
    unsigned int exp = (bits >> 0x17) & 0xff;
    if (exp == 0xff) return 0x7fffffffffffffffL;
    if (exp != 0) return (long)exp - 0x7f;
    if ((bits & 0x7fffff) == 0) return -0x8000000000000000L;
    long lz = (long)sk_h_0022a644(bits & 0x7fffff);
    if (!__builtin_sub_overflow((long)0x17, lz, &lz)) {
        if (!__builtin_sub_overflow((long)-0x7e, lz, &lz)) return lz;
        __builtin_trap();  /* SoftwareBreakpoint(1,0x2e8158) */
    }
    __builtin_trap();      /* SoftwareBreakpoint(1,0x2e8154) */
}

/* FUN_002e8158 @ 0x002e8158   (est. sk_swift_f32_normalize)
 * Ghidra: uint FUN_002e8158(uint param_1)
 * Normalizes a Float bit pattern: subnormals are scaled up by the leading
 * zero count (via FUN_0022a644) to a normal with exponent 0x7f; zero and
 * special values pass through. Returns the normalized bit pattern.
 * Confidence: medium
 * Notes: SoftwareBreakpoint trap on the shift borrow edge. */
unsigned int sk_swift_f32_normalize(unsigned int bits)
{
    unsigned int exp = (bits >> 0x17) & 0xff;
    unsigned int mant = bits & 0x7fffff;
    if ((mant == 0) || (exp != 0xff)) {
        if (exp == 0) {
            if (mant != 0) {
                long lz = (long)sk_h_0022a644(mant);
                if (!__builtin_sub_overflow((long)0x17, lz, &lz))
                    return (bits << (0x17U - (unsigned)lz) & 0x7fffff) | 0x3f800000u;
                __builtin_trap();  /* SoftwareBreakpoint(1,0x2e81d4) */
            }
        } else if (exp != 0xff) {
            return mant | 0x3f800000u;
        }
        bits = exp << 0x17;
    }
    return bits;
}

/* FUN_002e81ec @ 0x002e81ec   (est. sk_swift_f32_scalbn)
 * Ghidra: float FUN_002e81ec(float param_1,char param_2,ulong param_3)
 * Float `ldexp`/`scalbn`: scales param_1 by 2^param_3. Negates first when the
 * sign flag param_2 == 0. Subnormal/normal exponent bounds are handled by
 * repeated multiply by 2^-126 / 2^127 with clamping, then the residual
 * exponent is folded in via a single exponent-bits multiply.
 * Confidence: high
 * Notes: pure leaf; matches Swift Float `* (1<<n)` scaling. */
float sk_swift_f32_scalbn(float value, char neg, unsigned long e)
{
    float v = (neg == 1) ? -value : value;
    unsigned int exp = ((unsigned int)value >> 0x17) & 0xff;
    if ((exp != 0xff) && (exp != 0 || ((unsigned int)value & 0x7fffff) != 0)) {
        if ((long)e < -0x7e) {
            unsigned long t = e;
            if (e < 0xfffffffffffffe87) t = 0xfffffffffffffe86;
            do {
                e = t + 0x7e;
                v = v * 1.1754944e-38f;
                int again = (t < 0xffffffffffffff04);
                t = e;
                if (!again) break;
            } while (1);
        } else if (0x7f < (long)e) {
            if (0x17c < e) e = 0x17d;
            do {
                e = e - 0x7f;
                v = v * 1.7014118e+38f;
            } while (0x7f < e);
        }
        v = v * (float)((unsigned int)((long)e * 0x800000 + 0x3f800000U) & 0x7f800000);
    }
    return v;
}

/* ------------------------------------------------------------------ *
 * Float (32-bit) property & comparison wrappers.
 * ------------------------------------------------------------------ */

/* FUN_002e83ac @ 0x002e83ac   (est. sk_swift_f32_binop_a_inplace)
 * Ghidra: void FUN_002e83ac(undefined8 param_1)
 * In-place Float binary operation (FUN_0010d6b4) on the x20 self and param_1,
 * storing back to the self slot.
 * Confidence: low
 * Notes: operands are Float words; in-place update. */
void sk_swift_f32_binop_a_inplace(sk_word b)
{
    sk_word self = 0;  /* unaff_x20 */
    self = (sk_word)sk_h_0010d6b4(self, b);
    sk_h_0010d6b4(0, 0);  /* store-back marker (approx) */
}

/* FUN_002e83b0 @ 0x002e83b0   (est. sk_swift_f32_binop_a_inplace2)
 * Ghidra: void FUN_002e83b0(undefined8 param_1)
 * Duplicate of FUN_002e83ac (in-place Float binary op FUN_0010d6b4).
 * Confidence: low
 * Notes: operands are Float words; in-place update. */
void sk_swift_f32_binop_a_inplace2(sk_word b)
{
    sk_word self = 0;  /* unaff_x20 */
    self = (sk_word)sk_h_0010d6b4(self, b);
    sk_h_0010d6b4(0, 0);  /* store-back marker (approx) */
}

/* FUN_002e83d0 @ 0x002e83d0   (est. sk_swift_f32_binop_b_inplace)
 * Ghidra: void FUN_002e83d0(undefined8 param_1)
 * In-place Float binary operation (FUN_0010d2a8) on the x20 self and param_1.
 * Confidence: low
 * Notes: operands are Float words; in-place update. */
void sk_swift_f32_binop_b_inplace(sk_word b)
{
    sk_word self = 0;  /* unaff_x20 */
    self = (sk_word)sk_h_0010d2a8(self, b);
    sk_h_0010d2a8(0, 0);  /* store-back marker (approx) */
}

/* FUN_002e83d4 @ 0x002e83d4   (est. sk_swift_f32_binop_b_inplace2)
 * Ghidra: void FUN_002e83d4(undefined8 param_1)
 * Duplicate of FUN_002e83d0 (in-place Float binary op FUN_0010d2a8).
 * Confidence: low
 * Notes: operands are Float words; in-place update. */
void sk_swift_f32_binop_b_inplace2(sk_word b)
{
    sk_word self = 0;  /* unaff_x20 */
    self = (sk_word)sk_h_0010d2a8(self, b);
    sk_h_0010d2a8(0, 0);  /* store-back marker (approx) */
}

/* FUN_002e8444 @ 0x002e8444   (est. sk_swift_f32_exp_only)
 * Ghidra: float FUN_002e8444(float param_1)
 * Returns the Float with the mantissa cleared, keeping only the sign and
 * exponent bits (the "exponent-only" / next-ulp step). Subnormals are scaled
 * by 2^23 first; NaN/Inf pass through their exponent pattern; zero yields the
 * bare exponent field.
 * Confidence: high
 * Notes: pure leaf; IEEE-754 exponent extraction. */
float sk_swift_f32_exp_only(float v)
{
    unsigned int exp = ((unsigned int)v >> 0x17) & 0xff;
    if (exp == 0) {
        if (((unsigned int)v & 0x7fffff) != 0)
            return (float)(((unsigned int)(v * 8388608.0f) & 0xff800000u) * 1.1920929e-07f);
    } else if (exp == 0xff) {
        return NAN;
    }
    return (float)((unsigned int)v & 0xff800000u);
}

/* FUN_002e84f4 @ 0x002e84f4   (est. sk_swift_f80_str_parse_2e24134)
 * Ghidra: void FUN_002e84f4(undefined4 *param_1,undefined8 param_2,
 *        undefined8 *param_3,undefined4 *param_4)
 * Stores the result of the Float80-from-string helper FUN_00224134 applied to
 * param_2 and the dereferenced *param_3/*param_4 as a Float word.
 * Confidence: low
 * Notes: operand widths follow the decompile. */
void sk_swift_f80_str_parse_2e24134(unsigned int *out, sk_word b, sk_word *c, unsigned int *d)
{
    *out = (unsigned int)sk_h_00224134(b, (sk_word)*c, (sk_word)*d);
}

/* FUN_002e8534 @ 0x002e8534   (est. sk_swift_f32_prop_self_2e57b0)
 * Ghidra: void FUN_002e8534(undefined8 *param_1)
 * Applies the Float property helper FUN_002e57b0 to the x20 self and stores
 * the resulting word.
 * Confidence: low
 * Notes: unaff_x20 self register not recovered. */
void sk_swift_f32_prop_self_2e57b0(sk_word *out)
{
    sk_word self = 0;  /* unaff_x20 */
    *out = (sk_word)sk_h_002e57b0(self);
}

/* FUN_002e8560 @ 0x002e8560   (est. sk_swift_f32_prop_self_2e57e0)
 * Ghidra: void FUN_002e8560(undefined4 *param_1)
 * Applies the Float property helper FUN_002e57e0 to the x20 self and stores
 * the resulting Float word.
 * Confidence: low
 * Notes: unaff_x20 self register not recovered. */
void sk_swift_f32_prop_self_2e57e0(unsigned int *out)
{
    sk_word self = 0;  /* unaff_x20 */
    *out = (unsigned int)sk_h_002e57e0(self);
}

/* FUN_002e858c @ 0x002e858c   (est. sk_swift_f32_exp_only_wrap)
 * Ghidra: void FUN_002e858c(undefined4 *param_1)
 * Wraps FUN_002e8444 (in slice, exponent-only) applied to the x20 self and
 * stores the resulting Float word.
 * Confidence: medium
 * Notes: unaff_x20 self register not recovered. */
void sk_swift_f32_exp_only_wrap(unsigned int *out)
{
    sk_word self = 0;  /* unaff_x20 */
    *out = (unsigned int)sk_swift_f32_exp_only((float)self);
}

/* FUN_002e85c0 @ 0x002e85c0   (est. sk_swift_f32_scalbn_wrap)
 * Ghidra: void FUN_002e85c0(undefined4 *param_1,undefined8 param_2,
 *        undefined8 *param_3,undefined4 *param_4)
 * Wraps FUN_002e81ec (in slice, scalbn) on the dereferenced operands and
 * stores the resulting Float word.
 * Confidence: medium
 * Notes: operand widths follow the decompile. */
void sk_swift_f32_scalbn_wrap(unsigned int *out, sk_word b, sk_word *c, unsigned int *d)
{
    *out = (unsigned int)sk_swift_f32_scalbn(*(float *)d, (char)b, (unsigned long)*c);
}

/* FUN_002e8614 @ 0x002e8614   (est. sk_swift_f32_str_parse_b)
 * Ghidra: void FUN_002e8614(float *param_1,undefined8 param_2,long param_3,
 *        undefined8 param_4, undefined8 param_5)
 * Parses a Swift String {param_3,param_4} into a Float and stores it to
 * *param_1. Fast path reinterprets the small-buffer payload as Float; slow
 * path uses the general parser FUN_00226320 with the Float runtime tokens
 * FUN_00324d84 / 0002142c. Boxed string released on both paths.
 * Confidence: medium
 * Notes: Swift string-witness indirect calls via sk_fn casts. */
void sk_swift_f32_str_parse_b(float *out, sk_word p2, long str_storage, sk_word str_meta, sk_word p5)
{
    float local;
    long cnt = ((sk_fn)(sk_word)sk_h_00310a44(str_meta))(str_storage, str_meta);
    if (cnt < 0x41) {
        sk_word bits = ((sk_fn)(sk_word)sk_h_00310a14(str_meta))(str_storage, str_meta);
        sk_word payload = ((sk_fn)(sk_word)sk_h_003109b4(str_meta))(str_storage, str_meta);
        sk_rel_box(p2, str_storage);
        local = (bits & 1) ? (float)(long)payload : (float)(sk_word)payload;
    } else {
        sk_word a = (sk_word)sk_h_00324d84();
        sk_word b = (sk_word)sk_h_0002142c();
        sk_h_00226320(&local, p2, p5, str_storage, a, str_meta, b);
        sk_rel_box(p2, str_storage);
    }
    *out = local;
}

/* FUN_002e8768 @ 0x002e8768   (est. sk_swift_f32_str_parse_out)
 * Ghidra: void FUN_002e8768(undefined8,undefined8,undefined8)
 * Out-of-line Float-from-string parser: runs the fixed runtime sequence then
 * dispatches the small-buffer fast path or general parser FUN_00226320,
 * handing the result to FUN_00357c74. Condition-code / method-slot pointers
 * from the runtime calls are unrecovered.
 * Confidence: low
 * Notes: extraout_* CC/method-slot artifacts not fully recoverable. */
void sk_swift_f32_str_parse_out(sk_word p1, sk_word p2, sk_word p3)
{
    float val = 0;
    sk_h_00357cb4();
    sk_h_0034f414();
    sk_h_003507a4(p3);
    sk_h_0034e50c();
    long cnt = ((sk_fn)(sk_word)sk_h_00310a44(p3))(0, p3);
    if (cnt < 0x41) {
        sk_h_0034acd0();
        sk_word bits = ((sk_fn)(sk_word)sk_h_00310a14(p3))(0, p3);
        sk_h_0034b4d0();
        sk_h_0034e50c();
        sk_word payload = ((sk_fn)(sk_word)sk_h_003109b4(p3))(0, p3);
        sk_h_003572b8();
        val = (bits & 1) ? (float)(long)payload : (float)(sk_word)payload;
    } else {
        sk_word a = (sk_word)sk_h_00324d84();
        sk_word b = (sk_word)sk_h_0002142c();
        sk_h_00355b58(&val);
        sk_h_00226320();
        sk_h_003572b8();
    }
    sk_h_00357c74(val, p1);
}

/* FUN_002e8864 @ 0x002e8864   (est. sk_swift_f32_to_uint_wrap)
 * Ghidra: void FUN_002e8864(void)
 * Calls FUN_002e888c (in slice, Float->UInt conversion) then FUN_00351fc0.
 * A Float-to-unsigned wrapper with a trailing runtime cleanup.
 * Confidence: medium
 * Notes: forward + runtime tail. */
void sk_swift_f32_to_uint_wrap(void)
{
    sk_swift_f32_to_uint(0, 0, 0);
    sk_h_00351fc0();
}

/* FUN_002e888c @ 0x002e888c   (est. sk_swift_f32_to_uint)
 * Ghidra: ulong FUN_002e888c(undefined8,long,undefined8)
 * Converts the Float parsed from the Swift String {param_2,param_3} to an
 * unsigned word. Fast path reinterprets the small-buffer payload and checks
 * the value against the 2^64 / 2^63 bounds, raising the noreturn
 * "Float value cannot be converted to Int..." fatal (0x005d0760, Swift/
 * IntegerTypes.swift 0x223e) when out of range; slow path uses the general
 * parser. Returns 0x100000000 on a failed (non-integral) conversion.
 * Confidence: high
 * Notes: string-matched fatal (0x005d0760/0x005cd6f0/0x223e). */
unsigned long sk_swift_f32_to_uint(sk_word p1, long str_storage, sk_word str_meta)
{
    float local;
    long cnt = ((sk_fn)(sk_word)sk_h_00310a44(str_meta))(str_storage, str_meta);
    if (cnt < 0x41) {
        sk_word bits = ((sk_fn)(sk_word)sk_h_00310a14(str_meta))(str_storage, str_meta);
        sk_word payload = ((sk_fn)(sk_word)sk_h_003109b4(str_meta))(str_storage, str_meta);
        if ((bits & 1) == 0) {
            float v = (float)(sk_word)payload;
            sk_rel_box(p1, str_storage);
            local = v;
            if (v < 1.8446744e19f && payload == (sk_word)v) goto done;
        } else {
            float v = (float)(long)payload;
            if (9.223372e18f <= v) {
                sk_rel_box(p1, str_storage);
            } else {
                if (v <= (float)sk_dbl_i64_min) {
                    sk_fatal_error(0xb, 2, "Float value cannot be converted to Int because the result would be less than Int.min",
                                   0x54, 2, "Swift/IntegerTypes.swift", 0x18, 2, 0x223e, 1);
                    __builtin_unreachable();
                }
                sk_rel_box(p1, str_storage);
                local = v;
                if (payload == (sk_word)v) goto done;
            }
        }
    } else {
        sk_word a = (sk_word)sk_h_00324d84();
        sk_word b = (sk_word)sk_h_0002142c();
        sk_word r = (sk_word)sk_h_00226320(&local, p1, 0x677540, str_storage, a, str_meta, b);
        sk_rel_box(p1, str_storage);
        if ((r & 1) != 0) {
done:
            return (unsigned long)(unsigned int)local;
        }
    }
    return 0x100000000;
}

/* FUN_002e8ad4 @ 0x002e8ad4   (est. sk_swift_f32_nan_store)
 * Ghidra: void FUN_002e8ad4(undefined4 *param_1)
 * Stores the constant Float NaN bit pattern from FUN_002e8010 (in slice).
 * Confidence: high
 * Notes: pure forward. */
void sk_swift_f32_nan_store(unsigned int *out)
{
    *out = sk_swift_f32_nan_bits();
}

/* FUN_002e8b24 @ 0x002e8b24   (est. sk_swift_f32_to_f80_store)
 * Ghidra: void FUN_002e8b24(undefined4 *param_1)
 * Widens the x20 self Float to a Float80 via FUN_002e8090 (in slice) and
 * stores the low Float word.
 * Confidence: low
 * Notes: unaff_x20 self register not recovered. */
void sk_swift_f32_to_f80_store(unsigned int *out)
{
    sk_word self = 0;  /* unaff_x20 */
    *out = (unsigned int)sk_swift_f32_to_f80((unsigned int)self);
}

/* FUN_002e8b70 @ 0x002e8b70   (est. sk_swift_f32_exponent_store)
 * Ghidra: void FUN_002e8b70(undefined8 *param_1)
 * Stores the exponent (Int) of the x20 self Float via FUN_002e80e8 (in slice).
 * Confidence: medium
 * Notes: unaff_x20 self register not recovered. */
void sk_swift_f32_exponent_store(sk_word *out)
{
    sk_word self = 0;  /* unaff_x20 */
    *out = (sk_word)sk_swift_f32_exponent((unsigned int)self);
}

/* FUN_002e8b9c @ 0x002e8b9c   (est. sk_swift_f32_normalize_store)
 * Ghidra: void FUN_002e8b9c(undefined4 *param_1)
 * Normalizes the x20 self Float via FUN_002e8158 (in slice) and stores the
 * resulting bit pattern.
 * Confidence: medium
 * Notes: unaff_x20 self register not recovered. */
void sk_swift_f32_normalize_store(unsigned int *out)
{
    sk_word self = 0;  /* unaff_x20 */
    *out = sk_swift_f32_normalize((unsigned int)self);
}

/* FUN_002e8bf8 @ 0x002e8bf8   (est. sk_swift_f32_binop_a_store2)
 * Ghidra: void FUN_002e8bf8(undefined4 *param_1,undefined4 *param_2)
 * Float binary operation (FUN_0010d6b4) on the x20 self and *param_2, storing
 * to *param_1.
 * Confidence: low
 * Notes: operands are Float words. */
void sk_swift_f32_binop_a_store2(unsigned int *out, unsigned int *b)
{
    sk_word self = 0;  /* unaff_x20 */
    *out = (unsigned int)sk_h_0010d6b4(self, (sk_word)*b);
}

/* FUN_002e8c28 @ 0x002e8c28   (est. sk_swift_f32_binop_a_inplace3)
 * Ghidra: void FUN_002e8c28(undefined4 *param_1)
 * In-place Float binary operation (FUN_0010d6b4) on the x20 self and *param_1.
 * Confidence: low
 * Notes: operands are Float words; in-place update. */
void sk_swift_f32_binop_a_inplace3(unsigned int *b)
{
    sk_word self = 0;  /* unaff_x20 */
    self = (sk_word)sk_h_0010d6b4(self, (sk_word)*b);
    sk_h_0010d6b4(0, 0);  /* store-back marker (approx) */
}

/* FUN_002e8c2c @ 0x002e8c2c   (est. sk_swift_f32_binop_a_inplace4)
 * Ghidra: void FUN_002e8c2c(undefined4 *param_1)
 * Duplicate of FUN_002e8c28 (in-place Float binary op FUN_0010d6b4).
 * Confidence: low
 * Notes: operands are Float words; in-place update. */
void sk_swift_f32_binop_a_inplace4(unsigned int *b)
{
    sk_word self = 0;  /* unaff_x20 */
    self = (sk_word)sk_h_0010d6b4(self, (sk_word)*b);
    sk_h_0010d6b4(0, 0);  /* store-back marker (approx) */
}

/* FUN_002e8c4c @ 0x002e8c4c   (est. sk_swift_f32_binop_b_store2)
 * Ghidra: void FUN_002e8c4c(undefined4 *param_1,undefined4 *param_2)
 * Float binary operation (FUN_0010d2a8) on the x20 self and *param_2, storing
 * to *param_1.
 * Confidence: low
 * Notes: operands are Float words. */
void sk_swift_f32_binop_b_store2(unsigned int *out, unsigned int *b)
{
    sk_word self = 0;  /* unaff_x20 */
    *out = (unsigned int)sk_h_0010d2a8(self, (sk_word)*b);
}

/* FUN_002e8c7c @ 0x002e8c7c   (est. sk_swift_f32_binop_b_inplace3)
 * Ghidra: void FUN_002e8c7c(undefined4 *param_1)
 * In-place Float binary operation (FUN_0010d2a8) on the x20 self and *param_1.
 * Confidence: low
 * Notes: operands are Float words; in-place update. */
void sk_swift_f32_binop_b_inplace3(unsigned int *b)
{
    sk_word self = 0;  /* unaff_x20 */
    self = (sk_word)sk_h_0010d2a8(self, (sk_word)*b);
    sk_h_0010d2a8(0, 0);  /* store-back marker (approx) */
}

/* FUN_002e8c80 @ 0x002e8c80   (est. sk_swift_f32_binop_b_inplace4)
 * Ghidra: void FUN_002e8c80(undefined4 *param_1)
 * Duplicate of FUN_002e8c7c (in-place Float binary op FUN_0010d2a8).
 * Confidence: low
 * Notes: operands are Float words; in-place update. */
void sk_swift_f32_binop_b_inplace4(unsigned int *b)
{
    sk_word self = 0;  /* unaff_x20 */
    self = (sk_word)sk_h_0010d2a8(self, (sk_word)*b);
    sk_h_0010d2a8(0, 0);  /* store-back marker (approx) */
}

/* FUN_002e8ca0 @ 0x002e8ca0   (est. sk_swift_f32_unop_store)
 * Ghidra: void FUN_002e8ca0(undefined4 *param_1)
 * Applies the Float unary helper FUN_00324cd4 to the x20 self and stores the
 * resulting Float word.
 * Confidence: low
 * Notes: unaff_x20 self register not recovered. */
void sk_swift_f32_unop_store(unsigned int *out)
{
    sk_word self = 0;  /* unaff_x20 */
    *out = (unsigned int)sk_h_00324cd4(self);
}

/* FUN_002e8ccc @ 0x002e8ccc   (est. sk_swift_f32_unop_inplace)
 * Ghidra: void FUN_002e8ccc(void)
 * In-place Float unary operation (FUN_00324cd4) on the x20 self.
 * Confidence: low
 * Notes: unaff_x20 self register not recovered. */
void sk_swift_f32_unop_inplace(void)
{
    sk_word self = 0;  /* unaff_x20 */
    self = (sk_word)sk_h_00324cd4(self);
}

/* FUN_002e8cd0 @ 0x002e8cd0   (est. sk_swift_f32_unop_inplace2)
 * Ghidra: void FUN_002e8cd0(void)
 * Duplicate of FUN_002e8ccc (in-place Float unary op FUN_00324cd4).
 * Confidence: low
 * Notes: unaff_x20 self register not recovered. */
void sk_swift_f32_unop_inplace2(void)
{
    sk_word self = 0;  /* unaff_x20 */
    self = (sk_word)sk_h_00324cd4(self);
}

/* FUN_002e8d1c @ 0x002e8d1c   (est. sk_swift_cmp32_a)
 * Ghidra: void FUN_002e8d1c(undefined4 *param_1,undefined4 *param_2,undefined4 *param_3)
 * 32-bit Comparable helper via FUN_0021ef5c.
 * Confidence: medium
 * Notes: comparison operator identity not resolvable. */
void sk_swift_cmp32_a(unsigned int *out, unsigned int *a, unsigned int *b)
{
    *out = (unsigned int)sk_h_0021ef5c((sk_word)*a, (sk_word)*b);
}

/* FUN_002e8d4c @ 0x002e8d4c   (est. sk_swift_cmp32_b)
 * Ghidra: void FUN_002e8d4c(undefined4 *param_1,undefined4 *param_2,undefined4 *param_3)
 * 32-bit Comparable helper via FUN_0021efe8.
 * Confidence: medium
 * Notes: comparison operator identity not resolvable. */
void sk_swift_cmp32_b(unsigned int *out, unsigned int *a, unsigned int *b)
{
    *out = (unsigned int)sk_h_0021efe8((sk_word)*a, (sk_word)*b);
}

/* FUN_002e8d7c @ 0x002e8d7c   (est. sk_swift_cmp32_c)
 * Ghidra: void FUN_002e8d7c(undefined4 *param_1,undefined4 *param_2,undefined4 *param_3)
 * 32-bit Comparable helper via FUN_0021f138.
 * Confidence: medium
 * Notes: comparison operator identity not resolvable. */
void sk_swift_cmp32_c(unsigned int *out, unsigned int *a, unsigned int *b)
{
    *out = (unsigned int)sk_h_0021f138((sk_word)*a, (sk_word)*b);
}

/* FUN_002e8dac @ 0x002e8dac   (est. sk_swift_cmp32_d)
 * Ghidra: void FUN_002e8dac(undefined4 *param_1,undefined4 *param_2,undefined4 *param_3)
 * 32-bit Comparable helper via FUN_0021f1dc.
 * Confidence: medium
 * Notes: comparison operator identity not resolvable. */
void sk_swift_cmp32_d(unsigned int *out, unsigned int *a, unsigned int *b)
{
    *out = (unsigned int)sk_h_0021f1dc((sk_word)*a, (sk_word)*b);
}

/* ------------------------------------------------------------------ *
 * Float->integer conversion, print/compare and (XOR-obfuscated) emit.
 * ------------------------------------------------------------------ */

/* FUN_002e9160 @ 0x002e9160   (est. sk_swift_f32_ulp_round_store)
 * Ghidra: void FUN_002e9160(undefined4 *param_1)
 * Stores the Float produced by FUN_0039a030 as a word.
 * Confidence: low
 * Notes: pure forward to FUN_0039a030. */
void sk_swift_f32_ulp_round_store(unsigned int *out)
{
    *out = (unsigned int)sk_h_0039a030();
}

/* FUN_002e9198 @ 0x002e9198   (est. sk_swift_f32_emit)
 * Ghidra: void FUN_002e9198(float param_1)
 * Emits a Float via FUN_0022995c, substituting 0.0 when the value is zero.
 * A Float description/debug-print helper (sibling of the Float80 FUN_002e7b74
 * path).
 * Confidence: low
 * Notes: zero value suppressed. */
void sk_swift_f32_emit(float v)
{
    float f = 0.0f;
    if (v != 0.0f) f = v;
    sk_h_0022995c(f);
}

/* FUN_002e924c @ 0x002e924c   (est. sk_swift_f32_to_int2)
 * Ghidra: long FUN_002e924c(void)
 * Converts the Float self (read via FUN_0035ab54 / FUN_00357958 at the
 * bound 0x5f800000 = 2^64) to Int, trapping on NaN / out-of-range through the
 * noreturn overflow trap. Reconstructed at low confidence: the FP-compare CC
 * flags from FUN_0034bb38 are unrecovered; the finite in-range path is taken.
 * Confidence: low
 * Notes: CC (Z/N/V) flags from FUN_0034bb38 unrecovered. */
long sk_swift_f32_to_int2(void)
{
    sk_h_0034bb38();
    float v = (float)sk_h_00357958(0x5f800000);  /* bound 2^64 */
    if (!isnan(v)) return (long)v;
    sk_h_003488bc(1);
    sk_h_003493d8();
    sk_h_00351be0();
    sk_fatal_error(0, 0);
    __builtin_unreachable();
}

/* FUN_002e93bc @ 0x002e93bc   (est. sk_swift_f32_to_int_store)
 * Ghidra: void FUN_002e93bc(float *param_1,float param_2)
 * Converts the Float param_2 to an Int, storing the integer into the first
 * 8 bytes of the *param_1 boxed slot. When the value is exactly integral and
 * within the Int64 range it is stored after the FUN_0034fc44/0034fc58 + 00002534
 * + 0035472c runtime sequence; a NaN stores a tagged NaN representation
 * (mantissa fields + type pointer DAT_004f1698); a non-integral in-range value
 * falls to the FUN_00354348 out-of-range fatal.
 * Confidence: medium
 * Notes: boxed Int64 slot; NaN tagging via DAT_004f1698. */
void sk_swift_f32_to_int_store(float *box, float v)
{
    float iv = (float)(long)v;
    if (v >= 0.0f) {
        bool ok = !isnan(v) && (v < 1.8446744e19f);
        bool exact = ok && !isnan(iv) && (v == iv);
        if (!exact) goto fail;
        sk_h_0034fc44();
    } else {
        bool ok = !isnan(v) && (sk_dbl_i64_min < (double)v) && (v < 9.223372e18f);
        bool exact = ok && !isnan(iv) && (v == iv);
        if (!exact) {
fail:
            if (isnan(v)) {
                box[6] = 9.505445e-39f;
                box[7] = 0.0f;
                *(void **)(box + 8) = &sk_dat_004f1698;
                box[0] = v;
                return;
            }
            sk_h_00354348(0x678128, (double)v);
            return;
        }
        sk_h_0034fc58();
    }
    sk_h_00002534();
    sk_h_0035472c();
    *(long *)box = (long)v;
}

/* FUN_002e9498 @ 0x002e9498   (est. sk_swift_f32_str_eq)
 * Ghidra: undefined1 FUN_002e9498(float param_1,undefined8 param_2)
 * Compares the Float param_1 against the value parsed from the Swift String
 * param_2 (via FUN_00344d4c buffer + FUN_00365b6c parse at format 0x678150,
 * radix 6). Returns 2 when parsing fails, else 1/0 for equality.
 * Confidence: medium
 * Notes: parse-and-compare; format token 0x678150. */
unsigned char sk_swift_f32_str_eq(float v, sk_word str)
{
    float parsed;
    unsigned char buf[40];
    sk_h_00344d4c(str, buf);
    sk_word tok = (sk_word)sk_h_003519c0();
    int r = (int)sk_h_00365b6c(&parsed, buf, tok, 0x678150, 6);
    if (r == 0) return 2;
    return (v == parsed) ? 1 : 0;
}

/* FUN_002e9500 @ 0x002e9500   (est. sk_swift_f32_xor_debug_emit)
 * Ghidra: void FUN_002e9500(undefined1 param_1[16],undefined1 param_2[16])
 * Obfuscated Float debug-emit: XORs the 16 input bytes against the 32-byte
 * constant key (bytes 0-31 of s_uespemos..._004e7a30 = "uespemosmodnarodarenegylsetybdet"),
 * building four 8-byte words (low8^key[0..7], high8^key[8..15], low8^key[16..23],
 * high8^key[24..31]), then emits via FUN_002e9198 (in slice) and FUN_001a842c.
 * The obfuscation hides the formatted value from static analysis.
 * Confidence: low
 * Notes: XOR key read from the binary; emit arg decoded through buffer. */
void sk_swift_f32_xor_debug_emit(unsigned char in16[16], unsigned char key32[32])
{
    const unsigned char key[32] = "uespemosmodnarodarenegylsetybdet";
    unsigned long low, high;
    unsigned long A, B, C, D;
    low = 0; high = 0;
    for (int i = 0; i < 8; i++) { low |= (unsigned long)in16[i] << (8*i); high |= (unsigned long)in16[8+i] << (8*i); }
    A = 0; B = 0; C = 0; D = 0;
    for (int i = 0; i < 8; i++) {
        A |= (unsigned long)(((low >> (8*i)) & 0xff) ^ key[i]) << (8*i);       /* local_60: low8 ^ key[0..7]  */
        B |= (unsigned long)(((high >> (8*i)) & 0xff) ^ key[8+i]) << (8*i);    /* uStack_58: high8 ^ key[8..15] */
        C |= (unsigned long)(((low >> (8*i)) & 0xff) ^ key[16+i]) << (8*i);    /* uStack_50: low8 ^ key[16..23] */
        D |= (unsigned long)(((high >> (8*i)) & 0xff) ^ key[24+i]) << (8*i);   /* uStack_48: high8 ^ key[24..31] */
    }
    float emit = (float)(low ^ (A ^ B));  /* representative value feed (approx) */
    sk_h_003572d4();
    sk_swift_f32_emit(emit);
    sk_h_001a842c();
}

/* FUN_002e9554 @ 0x002e9554   (est. sk_swift_f32_xor_debug_emit_default)
 * Ghidra: void FUN_002e9554(void)
 * Default (all-zero) variant of the obfuscated Float debug-emit: zeroes a
 * 32-byte buffer, runs FUN_00349d14/00348f68, then emits via FUN_002e9198
 * (in slice) and FUN_001a842c.
 * Confidence: low
 * Notes: zero-filled buffer; emit via FUN_002e9198. */
void sk_swift_f32_xor_debug_emit_default(void)
{
    unsigned long buf[4] = {0, 0, 0, 0};
    sk_h_00349d14();
    sk_swift_f32_emit(0.0f);
    sk_h_001a842c();
}

/* FUN_002e95a8 @ 0x002e95a8   (est. sk_swift_f32_desc_parse)
 * Ghidra: void FUN_002e95a8(void)
 * Parses the Float description: reads the current value via FUN_00352800,
 * runs the parse FUN_00356b2c (format 0x677540), XOR-inverts the status via
 * FUN_00350268, and calls FUN_000839d8.
 * Confidence: low
 * Notes: description parse + status invert. */
void sk_swift_f32_desc_parse(void)
{
    sk_word local;
    local = (sk_word)sk_h_00352800();
    sk_word r = (sk_word)sk_h_00356b2c(0, &local, 0x677540);
    sk_h_00350268(r, (unsigned)r ^ 1);
    sk_h_000839d8();
}

/* FUN_002e95f4 @ 0x002e95f4   (est. sk_swift_f32_desc_emit)
 * Ghidra: undefined8 FUN_002e95f4(void)
 * Emits the Float description through the shared dispatch slot DAT_00658c00:
 * runs the runtime prologue (FUN_003517b4/00310d68/00348e00/0007c1a4), calls
 * the slot with the self and its +0x40 field, then dispatches on the parse
 * status FUN_00356b2c to either the success path (FUN_0034bd00) or the
 * overflow path (FUN_0034bc94/000839d8 plus the +0x20 vtable slot calls).
 * Returns the parse status.
 * Confidence: low
 * Notes: dispatch-slot + vtable slot indirect calls. */
sk_word sk_swift_f32_desc_emit(void)
{
    sk_word self = 0;  /* unaff */
    sk_h_003517b4();
    sk_h_00310d68();
    sk_h_00348e00();
    sk_h_0007c1a4();
    sk_g_dispatch();
    sk_h_0034924c();
    sk_g_dispatch(*(sk_word *)(self + 0x40));
    sk_h_00349068();
    sk_word r = (sk_word)sk_h_00356b2c();
    if ((int)r == 0) {
        sk_h_0034bd00();
        ((sk_fn)0)();
    } else {
        sk_h_0034bc94();
        sk_h_000839d8();
        sk_h_0035056c();
        ((sk_fn)0)();
        sk_h_00350c68();
        ((sk_fn)0)();
    }
    return r;
}

/* ------------------------------------------------------------------ *
 * String index iteration (Float80 path, second variant) and Double layer.
 * ------------------------------------------------------------------ */

/* FUN_002e9774 @ 0x002e9774   (est. sk_swift_f80_str_idx_loop_b)
 * Ghidra: void FUN_002e9774(void)
 * Second Float80 string-index iteration loop, sibling of FUN_002e7dd8 but
 * using the range helper FUN_002e5a78. Same bound-check/trap, digit decode,
 * tagged-value assembly and release/object-reuse structure.
 * Confidence: low
 * Notes: dense Swift runtime sequence; digit helpers un-named. */
void sk_swift_f80_str_idx_loop_b(void)
{
    sk_word flags = 0;
    sk_h_0006b2ec();
    sk_h_0034ff18();
    sk_pair r = sk_pair_from(sk_h_002e5a78());
    sk_word hi = r.hi, lo = r.lo;
    if (hi < lo) {
        __builtin_trap();  /* SoftwareBreakpoint(1,0x2e9834) */
    }
    if (hi == lo) {
        sk_h_0011e71c();
    } else {
        sk_h_00356704();
        if (flags || 1) {
            sk_h_00358768();
            if (sk_h_00347da8()) {
                sk_h_003504b8();
                sk_fatal_error(0, 0);
                __builtin_unreachable();
            }
            sk_h_0034e0b4();
            do { sk_h_003496b0(); } while (flags);
            flags = (sk_h_0034da18() == 9);
            if (8 < (long)sk_h_0034da18()) {
                if (sk_h_00348034()) goto fail;
                sk_h_0034da18();
                do { sk_h_0034b918(); } while (flags);
            }
            sk_h_0034ec0c();
            sk_word tag = 0xe000000000000000;
            if (!flags) tag = (sk_word)sk_h_00354b38(tag);
            sk_h_00354b38(tag);
        } else {
            sk_h_00354988();
            sk_h_00355c10();
        }
    }
    sk_h_000651bc(0);
    if (flags) return;
fail:
    sk_h_003504b8();
    sk_fatal_error(0, 0);
    __builtin_unreachable();
}

/* FUN_002e9850 @ 0x002e9850   (est. sk_swift_str_build_bytes_b)
 * Ghidra: void FUN_002e9850(void)
 * Sibling of FUN_002e7eb4 using the range helper FUN_002e5a78: builds a byte
 * string from a '0'-filled stack buffer and hands the tagged slice to
 * FUN_00267820 with the "object reused" canary check.
 * Confidence: low
 * Notes: stack canary + reuse check. */
void sk_swift_str_build_bytes_b(void)
{
    sk_word canary = (sk_word)(long)-0x2c8502b44bfffed6;
    unsigned long buf[8];
    for (int i = 0; i < 8; i++) buf[i] = 0x3030303030303030;
    unsigned long *head = &buf[0];
    unsigned long len_slot = 0x40;
    sk_pair r = sk_pair_from(sk_h_002e5a78(&head));
    unsigned long off = r.lo;
    if (r.hi < off) {
        __builtin_trap();  /* SoftwareBreakpoint(1,0x2e98e8) */
    }
    sk_h_00267820((r.hi - off) | 0xd000000000000000,
                  ((unsigned long)(buf + 0) + off) | 0x8000000000000000);
    if ((sk_word)(long)local_canary() == canary) return;
    sk_fatal_error(0, 0);
    __builtin_unreachable();
}

/* FUN_002e98ec @ 0x002e98ec   (est. sk_swift_str_emit_empty_check_b)
 * Ghidra: void FUN_002e98ec(void)
 * Sibling of FUN_002e7f50 using the range helper FUN_002e5a78: emits a string
 * whose emptiness is decided by the range, with a borrow trap, the runtime
 * emission sequence, frame release and the "object reused" noreturn.
 * Confidence: low
 * Notes: dense runtime emission; range from FUN_002e5a78. */
void sk_swift_str_emit_empty_check_b(void)
{
    sk_word flags = 0;
    sk_h_0034c034();
    sk_h_0006b2ec();
    sk_h_0034fef4();
    sk_pair r = sk_pair_from(sk_h_002e5a78());
    flags = (r.hi == r.lo);
    if (r.hi < r.lo) {
        __builtin_trap();  /* SoftwareBreakpoint(1,0x2e9960) */
    }
    sk_h_00354dc4();
    sk_h_00324ca0();
    sk_h_0035a690();
    sk_h_0034c5ac();
    ((sk_fn)(sk_word)sk_g_dispatch)();
    sk_h_000651bc(0);
    if (flags) return;
    sk_fatal_error(0, 0);
    __builtin_unreachable();
}

/* FUN_002e99bc @ 0x002e99bc   (est. sk_swift_f80_nan_value)
 * Ghidra: undefined1[16] FUN_002e99bc(void)
 * Returns the Float80 NaN constant (16-byte value whose high word is
 * 0x7ff4000000000000, an extended-precision NaN pattern). Materializes
 * Float80.nan.
 * Confidence: high
 * Notes: constant-return leaf. */
sk_f80 sk_swift_f80_nan_value(void)
{
    return NAN;
}

/* FUN_002e99ec @ 0x002e99ec   (est. sk_swift_trap_f64_range)
 * Ghidra: void FUN_002e99ec(void)
 * Double floating-point range / overflow trap: FUN_003488bc(1), FUN_0034987c
 * then the noreturn fatal FUN_001afe4c. Sibling of the Float trap FUN_002e8040.
 * Confidence: medium
 * Notes: noreturn. */
void sk_swift_trap_f64_range(void)
{
    sk_h_003488bc(1);
    sk_h_0034987c();
    sk_fatal_error(0, 0);
    __builtin_unreachable();
}

/* FUN_002e9a3c @ 0x002e9a3c   (est. sk_swift_f64_to_f80_bits)
 * Ghidra: undefined1[16] FUN_002e9a3c(ulong param_1)
 * Widens a Double bit pattern (param_1) to a Float80. For a zero exponent the
 * subnormal path goes through FUN_003592d4; otherwise the value is the
 * mantissa/exponent bits scaled by 2^-52. Returns the widened value (packed
 * as a 16-byte {0, double} pair).
 * Confidence: low
 * Notes: subnormal path via FUN_003592d4; returned as sk_f80. */
sk_f80 sk_swift_f64_to_f80_bits(unsigned long bits)
{
    unsigned long exp = (bits >> 0x34) & 0x7ff;
    if (exp != 0) {
        if (exp == 0x7ff) return NAN;
        return (sk_f80)((double)(bits & 0x7ff0000000000000) * 2.220446049250313e-16);
    }
    sk_h_003592d4();
    return 0.0L;
}

/* FUN_002e9ab4 @ 0x002e9ab4   (est. sk_swift_f64_exponent)
 * Ghidra: long FUN_002e9ab4(ulong param_1)
 * Returns the binary exponent of the Double bit pattern param_1 (Swift
 * `Double.exponent`). Handles NaN/Inf (0x7fffffffffffffff), normal (exp-0x3ff),
 * and subnormal (leading-zero-count via FUN_0022aaac) cases with
 * SoftwareBreakpoint traps on the borrow edges.
 * Confidence: medium
 * Notes: exponent of a double bit pattern. */
long sk_swift_f64_exponent(unsigned long bits)
{
    unsigned long exp = (bits >> 0x34) & 0x7ff;
    if (exp == 0x7ff) return 0x7fffffffffffffffL;
    if (exp != 0) return (long)exp - 0x3ff;
    if ((bits & 0xfffffffffffff) == 0) return -0x8000000000000000L;
    long lz = (long)sk_h_0022aaac(bits & 0xfffffffffffff);
    if (!__builtin_sub_overflow((long)0x34, lz, &lz)) {
        if (!__builtin_sub_overflow((long)-0x3fe, lz, &lz)) return lz;
        __builtin_trap();  /* SoftwareBreakpoint(1,0x2e9b24) */
    }
    __builtin_trap();      /* SoftwareBreakpoint(1,0x2e9b20) */
}

/* FUN_002e9b3c @ 0x002e9b3c   (est. sk_swift_f64_scalbn)
 * Ghidra: undefined1[16] FUN_002e9b3c(double param_1,char param_2,ulong param_3)
 * Double `ldexp`/`scalbn`: scales param_1 by 2^param_3, negating first when
 * the sign flag param_2 == 0. Subnormal/normal exponent bounds are handled by
 * repeated multiply by 2^-1022 / 2^1023 with clamping, then the residual
 * exponent is folded in via a single exponent-bits multiply. Returns the
 * scaled value packed as a 16-byte {0, double} pair.
 * Confidence: high
 * Notes: pure leaf; matches Swift Double `* (1<<n)` scaling. */
sk_f80 sk_swift_f64_scalbn(double value, char neg, unsigned long e)
{
    double v = (neg == 1) ? -value : value;
    unsigned long exp = ((unsigned long)value >> 0x34) & 0x7ff;
    if ((exp != 0x7ff) && (exp != 0 || ((unsigned long)value & 0xfffffffffffff) != 0)) {
        if ((long)e < -0x3fe) {
            unsigned long t = e;
            if (e < 0xfffffffffffff407) t = 0xfffffffffffff406;
            do {
                e = t + 0x3fe;
                v = v * 2.2250738585072014e-308;
                int again = (t < 0xfffffffffffff804);
                t = e;
                if (!again) break;
            } while (1);
        } else if (0x3ff < (long)e) {
            if (0xbfc < e) e = 0xbfd;
            do {
                e = e - 0x3ff;
                v = v * 8.98846567431158e+307;
            } while (0x3ff < e);
        }
        v = v * (double)((e << 0x34) + 0x3ff0000000000000 & 0x7ff0000000000000);
    }
    return (sk_f80)v;
}

/* FUN_002e9cf8 @ 0x002e9cf8   (est. sk_swift_f64_binop_a_inplace)
 * Ghidra: void FUN_002e9cf8(undefined8 param_1)
 * In-place Double binary operation (FUN_0010d44c) on the x20 self and param_1.
 * Confidence: low
 * Notes: operands are Double words; in-place update. */
void sk_swift_f64_binop_a_inplace(sk_word b)
{
    sk_word self = 0;  /* unaff_x20 */
    self = (sk_word)sk_h_0010d44c(self, b);
    sk_h_0010d44c(0, 0);  /* store-back marker (approx) */
}

/* FUN_002e9cfc @ 0x002e9cfc   (est. sk_swift_f64_binop_a_inplace2)
 * Ghidra: void FUN_002e9cfc(undefined8 param_1)
 * Duplicate of FUN_002e9cf8 (in-place Double binary op FUN_0010d44c).
 * Confidence: low
 * Notes: operands are Double words; in-place update. */
void sk_swift_f64_binop_a_inplace2(sk_word b)
{
    sk_word self = 0;  /* unaff_x20 */
    self = (sk_word)sk_h_0010d44c(self, b);
    sk_h_0010d44c(0, 0);  /* store-back marker (approx) */
}

/* FUN_002e9d1c @ 0x002e9d1c   (est. sk_swift_f64_binop_b_inplace)
 * Ghidra: void FUN_002e9d1c(undefined8 param_1)
 * In-place Double binary operation (FUN_0011169c) on the x20 self and param_1.
 * Confidence: low
 * Notes: operands are Double words; in-place update. */
void sk_swift_f64_binop_b_inplace(sk_word b)
{
    sk_word self = 0;  /* unaff_x20 */
    self = (sk_word)sk_h_0011169c(self, b);
    sk_h_0011169c(0, 0);  /* store-back marker (approx) */
}

/* FUN_002e9d20 @ 0x002e9d20   (est. sk_swift_f64_binop_b_inplace2)
 * Ghidra: void FUN_002e9d20(undefined8 param_1)
 * Duplicate of FUN_002e9d1c (in-place Double binary op FUN_0011169c).
 * Confidence: low
 * Notes: operands are Double words; in-place update. */
void sk_swift_f64_binop_b_inplace2(sk_word b)
{
    sk_word self = 0;  /* unaff_x20 */
    self = (sk_word)sk_h_0011169c(self, b);
    sk_h_0011169c(0, 0);  /* store-back marker (approx) */
}

/* FUN_002e9d94 @ 0x002e9d94   (est. sk_swift_f64_exp_only)
 * Ghidra: undefined1[16] FUN_002e9d94(double param_1)
 * Returns the Double with the mantissa cleared, keeping only sign/exponent
 * bits (exponent-only step). Subnormals are scaled by 2^52 first; NaN/Inf
 * yield a 0x7ff8... NaN pattern. Returns a 16-byte {0, double} pair.
 * Confidence: high
 * Notes: pure leaf; IEEE-754 exponent extraction. */
sk_f80 sk_swift_f64_exp_only(double v)
{
    unsigned long exp = ((unsigned long)v >> 0x34) & 0x7ff;
    if (exp == 0) {
        if (((unsigned long)v & 0xfffffffffffff) != 0)
            return (sk_f80)(((unsigned long)(v * 4503599627370496.0) & 0xfff0000000000000) * 2.220446049250313e-16);
    } else if (exp == 0x7ff) {
        return (sk_f80)0x7ff8000000000000;
    }
    return (sk_f80)((unsigned long)v & 0xfff0000000000000);
}

/* FUN_002e9dec @ 0x002e9dec   (est. sk_swift_f64_mantissa_lz)
 * Ghidra: long FUN_002e9dec(ulong param_1)
 * Computes a leading-zero-count-derived value from the Double bit pattern
 * param_1: bit-reverses the mantissa, and for the exponent/mantissa fields
 * returns the effective binary exponent (0x34 - clz) for a normal, a
 * normalized-subnormal exponent otherwise, or -1 for a zero mantissa. This is
 * the Swift `Double.exponent`/normalization helper.
 * Confidence: medium
 * Notes: bit-reverse + leading-zero-count; LZCOUNT via __builtin_clzll. */
long sk_swift_f64_mantissa_lz(unsigned long bits)
{
    unsigned long mant = bits & 0xfffffffffffff;
    unsigned long x = (bits & 0xaaaaaaaaaaaaa) >> 1 | (bits & 0x5555555555555) << 1;
    x = (x & 0xcccccccccccccccc) >> 2 | (x & 0x3333333333333333) << 2;
    x = (x & 0xf0f0f0f0f0f0f0f0) >> 4 | (x & 0xf0f0f0f0f0f0f0f) << 4;
    x = (x & 0xff00ff00ff00ff00) >> 8 | (x & 0xff00ff00ff00ff) << 8;
    x = (x & 0xffff0000ffff0000) >> 0x10 | (x & 0xffff0000ffff) << 0x10;
    long rev = (long)(__builtin_clzll(x >> 0x20 | x << 0x20));
    unsigned long exp = bits >> 0x34 & 0x7ff;
    long r = -1;
    if (mant != 0) r = (long)(__builtin_clzll(mant) ^ 0x3fU) - rev;
    long n = 0;
    if (mant != 0) n = 0x34 - rev;
    long e = -1;
    if (exp != 0x7ff) e = n;
    if (exp != 0) r = e;
    return r;
}

/* FUN_002e9e40 @ 0x002e9e40   (est. sk_swift_f80_str_parse_2e24154)
 * Ghidra: void FUN_002e9e40(undefined8 *param_1,undefined8 param_2,
 *        undefined8 *param_3,undefined8 *param_4)
 * Stores the result of the Float80-from-string helper FUN_00224154 applied to
 * param_2 and the dereferenced *param_3/*param_4 as a word.
 * Confidence: low
 * Notes: operand widths follow the decompile. */
void sk_swift_f80_str_parse_2e24154(sk_word *out, sk_word b, sk_word *c, sk_word *d)
{
    *out = (sk_word)sk_h_00224154(b, (sk_word)*c, (sk_word)*d);
}

/* FUN_002e9e80 @ 0x002e9e80   (est. sk_swift_f64_prop_self_2e62a0)
 * Ghidra: void FUN_002e9e80(undefined8 *param_1)
 * Applies the Double property helper FUN_002e62a0 to the x20 self and stores
 * the resulting word.
 * Confidence: low
 * Notes: unaff_x20 self register not recovered. */
void sk_swift_f64_prop_self_2e62a0(sk_word *out)
{
    sk_word self = 0;  /* unaff_x20 */
    *out = (sk_word)sk_h_002e62a0(self);
}

/* FUN_002e9eac @ 0x002e9eac   (est. sk_swift_f64_prop_self_2e62d0)
 * Ghidra: void FUN_002e9eac(undefined8 *param_1)
 * Applies the Double property helper FUN_002e62d0 to the x20 self and stores
 * the resulting word.
 * Confidence: low
 * Notes: unaff_x20 self register not recovered. */
void sk_swift_f64_prop_self_2e62d0(sk_word *out)
{
    sk_word self = 0;  /* unaff_x20 */
    *out = (sk_word)sk_h_002e62d0(self);
}

/* FUN_002e9ed8 @ 0x002e9ed8   (est. sk_swift_f64_exp_only_wrap)
 * Ghidra: void FUN_002e9ed8(undefined8 *param_1)
 * Wraps FUN_002e9d94 (in slice, Double exponent-only) applied to the x20 self
 * and stores the low word.
 * Confidence: medium
 * Notes: unaff_x20 self register not recovered. */
void sk_swift_f64_exp_only_wrap(sk_word *out)
{
    sk_word self = 0;  /* unaff_x20 */
    *out = (sk_word)sk_swift_f64_exp_only(*(double *)&self);
}

/* FUN_002e9f0c @ 0x002e9f0c   (est. sk_swift_f64_scalbn_wrap)
 * Ghidra: void FUN_002e9f0c(undefined8 *param_1,undefined8 param_2,
 *        undefined8 *param_3,undefined8 *param_4)
 * Wraps FUN_002e9b3c (in slice, Double scalbn) on the dereferenced operands
 * and stores the low word.
 * Confidence: medium
 * Notes: operand widths follow the decompile. */
void sk_swift_f64_scalbn_wrap(sk_word *out, sk_word b, sk_word *c, sk_word *d)
{
    *out = (sk_word)sk_swift_f64_scalbn(*(double *)d, (char)b, (unsigned long)*c);
}

/* FUN_002e9f64 @ 0x002e9f64   (est. sk_swift_f64_str_parse)
 * Ghidra: void FUN_002e9f64(double *param_1,undefined8 param_2,long param_3,
 *        undefined8 param_4, undefined8 param_5)
 * Parses a Swift String {param_3,param_4} into a Double and stores it to
 * *param_1. Fast path reinterprets the small-buffer payload as Double; slow
 * path uses the general parser FUN_00226320 with the Double runtime tokens
 * FUN_00324958 / 003249ac. Boxed string released on both paths.
 * Confidence: medium
 * Notes: Swift string-witness indirect calls via sk_fn casts. */
void sk_swift_f64_str_parse(double *out, sk_word p2, long str_storage, sk_word str_meta, sk_word p5)
{
    double local;
    long cnt = ((sk_fn)(sk_word)sk_h_00310a44(str_meta))(str_storage, str_meta);
    if (cnt < 0x41) {
        sk_word bits = ((sk_fn)(sk_word)sk_h_00310a14(str_meta))(str_storage, str_meta);
        sk_word payload = ((sk_fn)(sk_word)sk_h_003109b4(str_meta))(str_storage, str_meta);
        sk_rel_box(p2, str_storage);
        local = (bits & 1) ? (double)(long)payload : (double)(sk_word)payload;
    } else {
        sk_word a = (sk_word)sk_h_00324958();
        sk_word b = (sk_word)sk_h_003249ac();
        sk_h_00226320(&local, p2, p5, str_storage, a, str_meta, b);
        sk_rel_box(p2, str_storage);
    }
    *out = local;
}

/* FUN_002ea0b8 @ 0x002ea0b8   (est. sk_swift_f64_to_word_wrap)
 * Ghidra: void FUN_002ea0b8(void)
 * Calls FUN_002ea0e0 (in slice, Double->word) then FUN_0035272c.
 * Confidence: medium
 * Notes: forward + runtime tail. */
void sk_swift_f64_to_word_wrap(void)
{
    sk_swift_f64_from_str_word(0, 0, 0);
    sk_h_0035272c();
}

/* FUN_002ea0e0 @ 0x002ea0e0   (est. sk_swift_f64_from_str_word)
 * Ghidra: double FUN_002ea0e0(undefined8,long,undefined8)
 * Converts the Double parsed from the Swift String {param_2,param_3} to a
 * value. Fast path reinterprets the small-buffer payload and checks against
 * the 2^64 / 2^63 bounds, raising the noreturn "Double value cannot be
 * converted..." fatal (0x005cf940, Swift/IntegerTypes.swift 0x2286) when out
 * of range; slow path uses the general parser. Returns 0.0 on a failed
 * (non-integral) conversion.
 * Confidence: high
 * Notes: string-matched fatal (0x005cf940/0x005cd6f0/0x2286). */
double sk_swift_f64_from_str_word(sk_word p1, long str_storage, sk_word str_meta)
{
    double local;
    long cnt = ((sk_fn)(sk_word)sk_h_00310a44(str_meta))(str_storage, str_meta);
    if (cnt < 0x41) {
        sk_word bits = ((sk_fn)(sk_word)sk_h_00310a14(str_meta))(str_storage, str_meta);
        sk_word payload = ((sk_fn)(sk_word)sk_h_003109b4(str_meta))(str_storage, str_meta);
        if ((bits & 1) == 0) {
            double v = (double)(sk_word)payload;
            sk_rel_box(p1, str_storage);
            if (v < 1.8446744073709552e+19 && payload == (unsigned long)v) return v;
        } else {
            double v = (double)(long)payload;
            if (9.223372036854776e+18 <= v) {
                sk_rel_box(p1, str_storage);
            } else {
                if (v <= sk_dbl_i64_min_b) {
                    sk_fatal_error(0xb, 2, "Double value cannot be converted to Int because the result would be less than Int.min",
                                   0x55, 2, "Swift/IntegerTypes.swift", 0x18, 2, 0x2286, 1);
                    __builtin_unreachable();
                }
                sk_rel_box(p1, str_storage);
                if (payload == (unsigned long)v) return v;
            }
        }
    } else {
        sk_word a = (sk_word)sk_h_00324958();
        sk_word b = (sk_word)sk_h_003249ac();
        sk_word r = (sk_word)sk_h_00226320(&local, p1, 0x677568, str_storage, a, str_meta, b);
        sk_rel_box(p1, str_storage);
        if ((r & 1) != 0) return local;
    }
    return 0.0;
}

/* FUN_002ea334 @ 0x002ea334   (est. sk_swift_f80_nan_store)
 * Ghidra: void FUN_002ea334(undefined8 *param_1)
 * Stores the Float80 NaN constant from FUN_002e99bc (in slice).
 * Confidence: high
 * Notes: pure forward. */
void sk_swift_f80_nan_store(sk_word *out)
{
    *out = (sk_word)sk_swift_f80_nan_value();
}

/* FUN_002ea38c @ 0x002ea38c   (est. sk_swift_f64_to_f80_store)
 * Ghidra: void FUN_002ea38c(undefined8 *param_1)
 * Widens the x20 self Double to a Float80 via FUN_002e9a3c (in slice) and
 * stores the low word.
 * Confidence: low
 * Notes: unaff_x20 self register not recovered. */
void sk_swift_f64_to_f80_store(sk_word *out)
{
    sk_word self = 0;  /* unaff_x20 */
    *out = (sk_word)sk_swift_f64_to_f80_bits(self);
}

/* FUN_002ea3d8 @ 0x002ea3d8   (est. sk_swift_f64_exponent_store)
 * Ghidra: void FUN_002ea3d8(undefined8 *param_1)
 * Stores the exponent (Int) of the x20 self Double via FUN_002e9ab4 (in slice).
 * Confidence: medium
 * Notes: unaff_x20 self register not recovered. */
void sk_swift_f64_exponent_store(sk_word *out)
{
    sk_word self = 0;  /* unaff_x20 */
    *out = (sk_word)sk_swift_f64_exponent(self);
}

/* FUN_002ea404 @ 0x002ea404   (est. sk_swift_f64_prop_self_2e64f0)
 * Ghidra: void FUN_002ea404(undefined8 *param_1)
 * Applies the Double property helper FUN_002e64f0 to the x20 self and stores
 * the resulting word.
 * Confidence: low
 * Notes: unaff_x20 self register not recovered. */
void sk_swift_f64_prop_self_2e64f0(sk_word *out)
{
    sk_word self = 0;  /* unaff_x20 */
    *out = (sk_word)sk_h_002e64f0(self);
}

/* FUN_002ea458 @ 0x002ea458   (est. sk_swift_f64_binop_a_store2)
 * Ghidra: void FUN_002ea458(undefined8 *param_1,undefined8 *param_2)
 * Double binary operation (FUN_0010d44c) on the x20 self and *param_2, storing
 * to *param_1.
 * Confidence: low
 * Notes: operands are Double words. */
void sk_swift_f64_binop_a_store2(sk_word *out, sk_word *b)
{
    sk_word self = 0;  /* unaff_x20 */
    *out = (sk_word)sk_h_0010d44c(self, (sk_word)*b);
}

/* FUN_002ea488 @ 0x002ea488   (est. sk_swift_f64_binop_a_inplace3)
 * Ghidra: void FUN_002ea488(undefined8 *param_1)
 * In-place Double binary operation (FUN_0010d44c) on the x20 self and *param_1.
 * Confidence: low
 * Notes: operands are Double words; in-place update. */
void sk_swift_f64_binop_a_inplace3(sk_word *b)
{
    sk_word self = 0;  /* unaff_x20 */
    self = (sk_word)sk_h_0010d44c(self, (sk_word)*b);
    sk_h_0010d44c(0, 0);  /* store-back marker (approx) */
}

/* FUN_002ea48c @ 0x002ea48c   (est. sk_swift_f64_binop_a_inplace4)
 * Ghidra: void FUN_002ea48c(undefined8 *param_1)
 * Duplicate of FUN_002ea488 (in-place Double binary op FUN_0010d44c).
 * Confidence: low
 * Notes: operands are Double words; in-place update. */
void sk_swift_f64_binop_a_inplace4(sk_word *b)
{
    sk_word self = 0;  /* unaff_x20 */
    self = (sk_word)sk_h_0010d44c(self, (sk_word)*b);
    sk_h_0010d44c(0, 0);  /* store-back marker (approx) */
}

/* FUN_002ea4ac @ 0x002ea4ac   (est. sk_swift_f64_binop_b_store2)
 * Ghidra: void FUN_002ea4ac(undefined8 *param_1,undefined8 *param_2)
 * Double binary operation (FUN_0011169c) on the x20 self and *param_2, storing
 * to *param_1.
 * Confidence: low
 * Notes: operands are Double words. */
void sk_swift_f64_binop_b_store2(sk_word *out, sk_word *b)
{
    sk_word self = 0;  /* unaff_x20 */
    *out = (sk_word)sk_h_0011169c(self, (sk_word)*b);
}

/* FUN_002ea4dc @ 0x002ea4dc   (est. sk_swift_f64_binop_b_inplace3)
 * Ghidra: void FUN_002ea4dc(undefined8 *param_1)
 * In-place Double binary operation (FUN_0011169c) on the x20 self and *param_1.
 * Confidence: low
 * Notes: operands are Double words; in-place update. */
void sk_swift_f64_binop_b_inplace3(sk_word *b)
{
    sk_word self = 0;  /* unaff_x20 */
    self = (sk_word)sk_h_0011169c(self, (sk_word)*b);
    sk_h_0011169c(0, 0);  /* store-back marker (approx) */
}

/* FUN_002ea4e0 @ 0x002ea4e0   (est. sk_swift_f64_binop_b_inplace4)
 * Ghidra: void FUN_002ea4e0(undefined8 *param_1)
 * Duplicate of FUN_002ea4dc (in-place Double binary op FUN_0011169c).
 * Confidence: low
 * Notes: operands are Double words; in-place update. */
void sk_swift_f64_binop_b_inplace4(sk_word *b)
{
    sk_word self = 0;  /* unaff_x20 */
    self = (sk_word)sk_h_0011169c(self, (sk_word)*b);
    sk_h_0011169c(0, 0);  /* store-back marker (approx) */
}

/* FUN_002ea500 @ 0x002ea500   (est. sk_swift_f64_unop_store)
 * Ghidra: void FUN_002ea500(undefined8 *param_1)
 * Applies the Double unary helper FUN_00324ddc to the x20 self and stores the
 * resulting word.
 * Confidence: low
 * Notes: unaff_x20 self register not recovered. */
void sk_swift_f64_unop_store(sk_word *out)
{
    sk_word self = 0;  /* unaff_x20 */
    *out = (sk_word)sk_h_00324ddc(self);
}

/* FUN_002ea52c @ 0x002ea52c   (est. sk_swift_f64_unop_inplace)
 * Ghidra: void FUN_002ea52c(void)
 * In-place Double unary operation (FUN_00324ddc) on the x20 self.
 * Confidence: low
 * Notes: unaff_x20 self register not recovered. */
void sk_swift_f64_unop_inplace(void)
{
    sk_word self = 0;  /* unaff_x20 */
    self = (sk_word)sk_h_00324ddc(self);
}

/* FUN_002ea530 @ 0x002ea530   (est. sk_swift_f64_unop_inplace2)
 * Ghidra: void FUN_002ea530(void)
 * Duplicate of FUN_002ea52c (in-place Double unary op FUN_00324ddc).
 * Confidence: low
 * Notes: unaff_x20 self register not recovered. */
void sk_swift_f64_unop_inplace2(void)
{
    sk_word self = 0;  /* unaff_x20 */
    self = (sk_word)sk_h_00324ddc(self);
}

/* FUN_002ea57c @ 0x002ea57c   (est. sk_swift_cmp64_a)
 * Ghidra: void FUN_002ea57c(undefined8 *param_1,undefined8 *param_2,undefined8 *param_3)
 * 64-bit Comparable helper via FUN_0021ef80.
 * Confidence: medium
 * Notes: comparison operator identity not resolvable. */
void sk_swift_cmp64_a(sk_word *out, sk_word *a, sk_word *b)
{
    *out = (sk_word)sk_h_0021ef80((sk_word)*a, (sk_word)*b);
}

/* FUN_002ea5ac @ 0x002ea5ac   (est. sk_swift_cmp64_b)
 * Ghidra: void FUN_002ea5ac(undefined8 *param_1,undefined8 *param_2,undefined8 *param_3)
 * 64-bit Comparable helper via FUN_0021f00c.
 * Confidence: medium
 * Notes: comparison operator identity not resolvable. */
void sk_swift_cmp64_b(sk_word *out, sk_word *a, sk_word *b)
{
    *out = (sk_word)sk_h_0021f00c((sk_word)*a, (sk_word)*b);
}

/* FUN_002ea5dc @ 0x002ea5dc   (est. sk_swift_cmp64_c)
 * Ghidra: void FUN_002ea5dc(undefined8 *param_1,undefined8 *param_2,undefined8 *param_3)
 * 64-bit Comparable helper via FUN_0021f164.
 * Confidence: medium
 * Notes: comparison operator identity not resolvable. */
void sk_swift_cmp64_c(sk_word *out, sk_word *a, sk_word *b)
{
    *out = (sk_word)sk_h_0021f164((sk_word)*a, (sk_word)*b);
}

/* FUN_002ea60c @ 0x002ea60c   (est. sk_swift_cmp64_d)
 * Ghidra: void FUN_002ea60c(undefined8 *param_1,undefined8 *param_2,undefined8 *param_3)
 * 64-bit Comparable helper via FUN_0021f208.
 * Confidence: medium
 * Notes: comparison operator identity not resolvable. */
void sk_swift_cmp64_d(sk_word *out, sk_word *a, sk_word *b)
{
    *out = (sk_word)sk_h_0021f208((sk_word)*a, (sk_word)*b);
}

/* FUN_002ea63c @ 0x002ea63c   (est. sk_swift_f64_round_mode)
 * Ghidra: void FUN_002ea63c(long *param_1,undefined1 param_2)
 * Rounds the x20 self Double according to the mode param_2 and stores the
 * integer to *param_1. Only mode 5 triggers the rounding helper FUN_002e62c4
 * plus the two FUN_00149368 emit calls; other modes fall through and store the
 * truncated Double as a long.
 * Confidence: low
 * Notes: switch over rounding modes; x20 self unrecovered. */
void sk_swift_f64_round_mode(long *out, unsigned char mode)
{
    sk_word self = 0;  /* unaff_x20 */
    double d = *(double *)&self;
    switch (mode) {
    case 5:
        sk_word u = (sk_word)sk_h_002e62c4(d);
        sk_h_00149368(u);
        sk_h_00149368(1);
        break;
    default:
        break;
    }
    *out = (long)d;
}

/* FUN_002ea8f8 @ 0x002ea8f8   (est. sk_swift_f64_is_signaling_nan)
 * Ghidra: bool FUN_002ea8f8(void)
 * Returns true when the x20 self Double is a signaling NaN: the value is NaN
 * and its signaling bit (bit 0x33 of the bit pattern from FUN_002e62d0) is
 * clear.
 * Confidence: medium
 * Notes: unaff_x20 self register not recovered. */
bool sk_swift_f64_is_signaling_nan(void)
{
    sk_word self = 0;  /* unaff_x20 */
    double d = *(double *)&self;
    if (isnan(d)) {
        sk_word bits = (sk_word)sk_h_002e62d0(self);
        return ((bits >> 0x33) & 1) == 0;
    }
    return false;
}

/* FUN_002ea8fc @ 0x002ea8fc   (est. sk_swift_f64_is_signaling_nan2)
 * Ghidra: bool FUN_002ea8fc(void)
 * Duplicate of FUN_002ea8f8 (Double is-signaling-NaN test).
 * Confidence: medium
 * Notes: unaff_x20 self register not recovered. */
bool sk_swift_f64_is_signaling_nan2(void)
{
    sk_word self = 0;  /* unaff_x20 */
    double d = *(double *)&self;
    if (isnan(d)) {
        sk_word bits = (sk_word)sk_h_002e62d0(self);
        return ((bits >> 0x33) & 1) == 0;
    }
    return false;
}

/* FUN_002ea9fc @ 0x002ea9fc   (est. sk_swift_f64_ulp_round_store)
 * Ghidra: void FUN_002ea9fc(undefined8 *param_1)
 * Stores the Double produced by the round/ulp helper FUN_0039a0ac as a word.
 * Confidence: low
 * Notes: pure forward to FUN_0039a0ac. */
void sk_swift_f64_ulp_round_store(sk_word *out)
{
    *out = (sk_word)sk_h_0039a0ac();
}

/* FUN_002eaa34 @ 0x002eaa34   (est. sk_swift_f64_emit)
 * Ghidra: void FUN_002eaa34(double param_1)
 * Emits a Double via FUN_002298d4, substituting 0.0 when the value is zero.
 * A Double description/debug-print helper (sibling of the Float FUN_002e9198
 * path).
 * Confidence: low
 * Notes: zero value suppressed. */
void sk_swift_f64_emit(double v)
{
    double d = 0.0;
    if (v != 0.0) d = v;
    sk_h_002298d4(d);
}

/* FUN_002eaad8 @ 0x002eaad8   (est. sk_swift_f64_to_int2)
 * Ghidra: long FUN_002eaad8(void)
 * Converts the Double self (read via FUN_0035ab2c / FUN_00354588 at the bound
 * 0x43f0000000000000 = 2^63) to Int, trapping on NaN / out-of-range through
 * the noreturn overflow trap. Reconstructed at low confidence: the FP-compare
 * CC flags from FUN_0034bb60 are unrecovered; the finite in-range path is
 * taken.
 * Confidence: low
 * Notes: CC (Z/N/V) flags from FUN_0034bb60 unrecovered. */
long sk_swift_f64_to_int2(void)
{
    sk_h_0034bb60();
    double v = (double)sk_h_00354588(0x43f0000000000000);  /* bound 2^63 */
    if (!isnan(v)) return (long)v;
    sk_h_003488bc(1);
    sk_h_003493d8();
    sk_h_00351be0();
    sk_fatal_error(0, 0);
    __builtin_unreachable();
}

/* FUN_002eac2c @ 0x002eac2c   (est. sk_swift_f64_to_int_store)
 * Ghidra: void FUN_002eac2c(long *param_1,double param_2)
 * Converts the Double param_2 to an Int, storing the integer to *param_1.
 * When the value is exactly integral and within the Int64 range it is stored
 * after the FUN_0034fc44/0034fc58 + 00002534 + 0035472c runtime sequence; a
 * non-integral / out-of-range value falls to the FUN_00354348 fatal.
 * Confidence: medium
 * Notes: exact-integrality check; out-of-range fatal. */
void sk_swift_f64_to_int_store(long *out, double v)
{
    double iv = (double)(long)v;
    if (v >= 0.0) {
        bool ok = !isnan(v) && (v < 1.8446744073709552e+19);
        bool exact = ok && !isnan(iv) && (v == iv);
        if (!exact) goto fail;
        sk_h_0034fc44();
    } else {
        bool ok = !isnan(v) && (sk_dbl_i64_min_b < v) && (v < 9.223372036854776e+18);
        bool exact = ok && !isnan(iv) && (v == iv);
        if (!exact) {
fail:
            sk_h_00354348(0x678128);
            return;
        }
        sk_h_0034fc58();
    }
    sk_h_00002534();
    sk_h_0035472c();
    *out = (long)v;
}

/* FUN_002eacc4 @ 0x002eacc4   (est. sk_swift_f64_str_eq)
 * Ghidra: undefined1 FUN_002eacc4(double param_1,undefined8 param_2)
 * Compares the Double param_1 against the value parsed from the Swift String
 * param_2 (via FUN_00344d4c buffer + FUN_00365b6c parse at format 0x678128,
 * radix 6). Returns 2 when parsing fails, else 1/0 for equality.
 * Confidence: medium
 * Notes: parse-and-compare; format token 0x678128. */
unsigned char sk_swift_f64_str_eq(double v, sk_word str)
{
    double parsed;
    unsigned char buf[40];
    sk_h_00344d4c(str, buf);
    sk_word tok = (sk_word)sk_h_003519c0();
    int r = (int)sk_h_00365b6c(&parsed, buf, tok, 0x678128, 6);
    if (r == 0) return 2;
    return (v == parsed) ? 1 : 0;
}

/* FUN_002ead2c @ 0x002ead2c   (est. sk_swift_f64_xor_debug_emit)
 * Ghidra: void FUN_002ead2c(undefined1 param_1[16],undefined1 param_2[16])
 * Obfuscated Double debug-emit: XORs the 16 input bytes against the 32-byte
 * constant key (s_uespemos..._004e7a30) building four 8-byte words, then emits
 * via FUN_002eaa34 (in slice) and FUN_001a842c. Sibling of the Float
 * FUN_002e9500 routine.
 * Confidence: low
 * Notes: XOR key read from the binary; emit via FUN_002eaa34. */
void sk_swift_f64_xor_debug_emit(unsigned char in16[16], unsigned char key32[32])
{
    const unsigned char key[32] = "uespemosmodnarodarenegylsetybdet";
    unsigned long low, high, A, B, C, D;
    low = 0; high = 0;
    for (int i = 0; i < 8; i++) { low |= (unsigned long)in16[i] << (8*i); high |= (unsigned long)in16[8+i] << (8*i); }
    A = 0; B = 0; C = 0; D = 0;
    for (int i = 0; i < 8; i++) {
        A |= (unsigned long)(((low >> (8*i)) & 0xff) ^ key[i]) << (8*i);
        B |= (unsigned long)(((high >> (8*i)) & 0xff) ^ key[8+i]) << (8*i);
        C |= (unsigned long)(((low >> (8*i)) & 0xff) ^ key[16+i]) << (8*i);
        D |= (unsigned long)(((high >> (8*i)) & 0xff) ^ key[24+i]) << (8*i);
    }
    double emit = (double)(low ^ (A ^ B));  /* representative value feed (approx) */
    sk_h_003572d4();
    sk_swift_f64_emit(emit);
    sk_h_001a842c();
}

/* FUN_002ead80 @ 0x002ead80   (est. sk_swift_f64_xor_debug_emit_default)
 * Ghidra: void FUN_002ead80(void)
 * Default (all-zero) variant of the obfuscated Double debug-emit: zeroes a
 * 32-byte buffer, runs FUN_00349d14/00348f68, then emits via FUN_002eaa34
 * (in slice) and FUN_001a842c.
 * Confidence: low
 * Notes: zero-filled buffer; emit via FUN_002eaa34. */
void sk_swift_f64_xor_debug_emit_default(void)
{
    unsigned long buf[4] = {0, 0, 0, 0};
    sk_h_00349d14();
    sk_swift_f64_emit(0.0);
    sk_h_001a842c();
}

/* FUN_002eadd8 @ 0x002eadd8   (est. sk_swift_f64_desc_parse)
 * Ghidra: void FUN_002eadd8(void)
 * Parses the Double description: reads the current value via FUN_00352800,
 * runs the parse FUN_00356b2c (format 0x677568), XOR-inverts the status via
 * FUN_00350268, and calls FUN_000839d8.
 * Confidence: low
 * Notes: description parse + status invert. */
void sk_swift_f64_desc_parse(void)
{
    sk_word local;
    local = (sk_word)sk_h_00352800();
    sk_word r = (sk_word)sk_h_00356b2c(0, &local, 0x677568);
    sk_h_00350268(r, (unsigned)r ^ 1);
    sk_h_000839d8();
}

/* FUN_002eae24 @ 0x002eae24   (est. sk_swift_f64_desc_emit)
 * Ghidra: undefined8 FUN_002eae24(void)
 * Emits the Double description through the shared dispatch slot DAT_00658c00:
 * runs the runtime prologue, calls the slot with the self and its +0x40 field,
 * passes the FUN_00349068 pair to FUN_0035992c (format 0x677568), then
 * dispatches on the parse status FUN_00356b2c to the success (FUN_0034bd00) or
 * overflow (FUN_0034bc94/000839d8 + vtable-slot) path. Returns the status.
 * Confidence: low
 * Notes: dispatch-slot + vtable slot indirect calls. */
sk_word sk_swift_f64_desc_emit(void)
{
    sk_word self = 0;  /* unaff */
    sk_h_003517b4();
    sk_h_00310d68();
    sk_h_00348e00();
    sk_h_0007c1a4();
    sk_g_dispatch();
    sk_h_0034924c();
    sk_g_dispatch(*(sk_word *)(self + 0x40));
    sk_pair r = sk_pair_from(sk_h_00349068());
    sk_h_0035992c(r.lo, r.hi, 0x677568);
    sk_word st = (sk_word)sk_h_00356b2c();
    if ((int)st == 0) {
        sk_h_0034bd00();
        ((sk_fn)0)();
    } else {
        sk_h_0034bc94();
        sk_h_000839d8();
        sk_h_0035056c();
        ((sk_fn)0)();
        sk_h_00350c68();
        ((sk_fn)0)();
    }
    return st;
}

/* ------------------------------------------------------------------ *
 * Float80/Double operator-availability fatal stubs and integer traps.
 * ------------------------------------------------------------------ */

/* FUN_002eaf98 @ 0x002eaf98   (est. sk_swift_f80_ops_unavailable)
 * Ghidra: void FUN_002eaf98(void)
 * noreturn availability stub for the Float80 `%` / `%=` operators: raises the
 * string-matched "Float80 is not available" / "% is not available." /
 * "%= is not available." fatal via FUN_003593c0 and FUN_001afa84, chaining
 * through the in-slice stubs FUN_002eafec / 002eb040.
 * Confidence: high
 * Notes: string-matched (0x005d1590/0x005d15b0/0x005d15d0); noreturn. */
void sk_swift_f80_ops_unavailable(void)
{
    sk_word a = (sk_word)sk_h_0035ac70(0x005d1590);  /* "Float80 is not available" */
    sk_h_003593c0(a, a);
    sk_h_0006f768();
    sk_h_00357bd0();
    sk_word b = (sk_word)sk_h_0035ac70(0x005d15b0, (sk_word)sk_swift_f80_mod_unavailable);  /* "% is not available." */
    sk_h_003593c0(b, b);
    sk_h_0006f768();
    sk_h_00357bd0();
    sk_word c = (sk_word)sk_h_0035ac70(0x005d15d0, (sk_word)sk_swift_f80_modassign_unavailable);  /* "%= is not available." */
    sk_h_003593c0(c, c);
    sk_h_00349c58();
    sk_fatal_unavail(0, 0);
    __builtin_unreachable();
}

/* FUN_002eafec @ 0x002eafec   (est. sk_swift_f80_mod_unavailable)
 * Ghidra: void FUN_002eafec(void)
 * noreturn stub for the Float80 `%` operator: raises "% is not available."
 * (0x005d15b0) then chains to the `%=` stub FUN_002eb040 and the fatal
 * FUN_001afa84.
 * Confidence: high
 * Notes: string-matched (0x005d15b0/0x005d15d0); noreturn. */
void sk_swift_f80_mod_unavailable(void)
{
    sk_word a = (sk_word)sk_h_0035ac70(0x005d15b0);  /* "% is not available." */
    sk_h_003593c0(a, a);
    sk_h_0006f768();
    sk_h_00357bd0();
    sk_word b = (sk_word)sk_h_0035ac70(0x005d15d0, (sk_word)sk_swift_f80_modassign_unavailable);  /* "%= is not available." */
    sk_h_003593c0(b, b);
    sk_h_00349c58();
    sk_fatal_unavail(0, 0);
    __builtin_unreachable();
}

/* FUN_002eb040 @ 0x002eb040   (est. sk_swift_f80_modassign_unavailable)
 * Ghidra: void FUN_002eb040(void)
 * noreturn stub for the Float80 `%=` operator: raises "%= is not available."
 * (0x005d15d0) and the fatal FUN_001afa84.
 * Confidence: high
 * Notes: string-matched (0x005d15d0); noreturn. */
void sk_swift_f80_modassign_unavailable(void)
{
    sk_word a = (sk_word)sk_h_0035ac70(0x005d15d0);  /* "%= is not available." */
    sk_h_003593c0(a, a);
    sk_h_00349c58();
    sk_fatal_unavail(0, 0);
    __builtin_unreachable();
}

/* FUN_002eb094 @ 0x002eb094   (est. sk_swift_f80_to_int32)
 * Ghidra: int FUN_002eb094(void)
 * Converts the Float80 self (read via FUN_0035ab7c) to Int32, trapping on
 * NaN / out-of-range through the noreturn overflow trap. Reconstructed at low
 * confidence: the FP-compare CC flags from FUN_0034d584 are unrecovered; the
 * finite in-range path is taken.
 * Confidence: low
 * Notes: CC (Z/N/V) flags from FUN_0034d584 unrecovered. */
int sk_swift_f80_to_int32(void)
{
    sk_h_0034d584();
    sk_f80 v = (sk_f80)sk_h_0035ab7c();
    if (!isnan((double)v)) return (int)v;
    sk_h_003488bc(1);
    sk_h_003493d8();
    sk_h_00351be0();
    sk_fatal_error(0, 0);
    __builtin_unreachable();
}

/* FUN_002eb164 @ 0x002eb164   (est. sk_swift_f32_to_int32)
 * Ghidra: int FUN_002eb164(void)
 * Converts the Float self (read via FUN_0035ab54 / FUN_00357958 at the bound
 * 0x43800000 = 2^32) to Int32, trapping on NaN / out-of-range. CC flags from
 * FUN_0034bb38 unrecovered; finite path assumed.
 * Confidence: low
 * Notes: CC (Z/N/V) flags from FUN_0034bb38 unrecovered. */
int sk_swift_f32_to_int32(void)
{
    sk_h_0034bb38();
    float v = (float)sk_h_00357958(0x43800000);  /* bound 2^32 */
    if (!isnan(v)) return (int)v;
    sk_h_003488bc(1);
    sk_h_003493d8();
    sk_h_00351be0();
    sk_fatal_error(0, 0);
    __builtin_unreachable();
}

/* FUN_002eb230 @ 0x002eb230   (est. sk_swift_f64_to_int32)
 * Ghidra: int FUN_002eb230(void)
 * Converts the Double self (read via FUN_0035ab2c / FUN_00354588 at the bound
 * 0x4070000000000000) to Int32, trapping on NaN / out-of-range. CC flags from
 * FUN_0034bb60 unrecovered; finite path assumed.
 * Confidence: low
 * Notes: CC (Z/N/V) flags from FUN_0034bb60 unrecovered. */
int sk_swift_f64_to_int32(void)
{
    sk_h_0034bb60();
    double v = (double)sk_h_00354588(0x4070000000000000);
    if (!isnan(v)) return (int)v;
    sk_h_003488bc(1);
    sk_h_003493d8();
    sk_h_00351be0();
    sk_fatal_error(0, 0);
    __builtin_unreachable();
}

/* FUN_002eb370 @ 0x002eb370   (est. sk_swift_trap_div_by_zero)
 * Ghidra: void FUN_002eb370(void)
 * Integer divide-by-zero trap: FUN_00348074(1), FUN_00351be0 then the noreturn
 * fatal FUN_001afe4c.
 * Confidence: medium
 * Notes: noreturn. */
void sk_swift_trap_div_by_zero(void)
{
    sk_h_00348074(1);
    sk_h_00351be0();
    sk_fatal_error(0, 0);
    __builtin_unreachable();
}

/* FUN_002eb454 @ 0x002eb454   (est. sk_swift_trap_int_overflow)
 * Ghidra: void FUN_002eb454(void)
 * Integer overflow trap: FUN_00348404(1), FUN_00351be0 then the noreturn
 * fatal FUN_001afe4c.
 * Confidence: medium
 * Notes: noreturn. */
void sk_swift_trap_int_overflow(void)
{
    sk_h_00348404(1);
    sk_h_00351be0();
    sk_fatal_error(0, 0);
    __builtin_unreachable();
}

/* FUN_002eb48c @ 0x002eb48c   (est. sk_swift_int_to_char_check)
 * Ghidra: undefined1 FUN_002eb48c(long param_1,undefined1 param_2)
 * Converts the Int param_1 to a byte, returning param_2 when the value is
 * exactly zero; a negative value hits the negative-overflow trap, a positive
 * value the positive-overflow trap (both noreturn).
 * Confidence: medium
 * Notes: range-checked narrow integer conversion. */
unsigned char sk_swift_int_to_char_check(long v, unsigned char fallback)
{
    if (v < 0) {
        sk_h_003488bc(1);
        sk_h_00355ebc();
        sk_h_003493d8();
    } else if (v == 0) {
        return fallback;
    } else {
        sk_h_003488bc(1);
        sk_h_00355890();
        sk_h_003493d8();
    }
    sk_h_00351be0();
    sk_fatal_error(0, 0);
    __builtin_unreachable();
}

/* FUN_002eb4f0 @ 0x002eb4f0   (est. sk_swift_f80_word_box)
 * Ghidra: void FUN_002eb4f0(void)
 * Boxes a word: reads the 16-byte pair from FUN_00351124 and stores the result
 * of FUN_001e655c(pair.lo, pair.hi, self) into the x19 output slot.
 * Confidence: low
 * Notes: unaff_x19/x20 registers not recovered. */
void sk_swift_f80_word_box(sk_word *out)
{
    sk_word self = 0;  /* unaff_x20 */
    sk_pair r = sk_pair_from(sk_h_00351124());
    *out = (sk_word)sk_h_001e655c(r.lo, r.hi, self);
}

/* FUN_002eb51c @ 0x002eb51c   (est. sk_swift_f80_desc_emit_wrap)
 * Ghidra: void FUN_002eb51c(void)
 * Runs FUN_0034c434, FUN_001e3698 and FUN_0035272c: a Float80 description/
 * representation emit wrapper.
 * Confidence: low
 * Notes: pure runtime sequence. */
void sk_swift_f80_desc_emit_wrap(void)
{
    sk_h_0034c434();
    sk_h_001e3698();
    sk_h_0035272c();
}

/* FUN_002eb55c @ 0x002eb55c   (est. sk_swift_f80_wb_store)
 * Ghidra: void FUN_002eb55c(undefined8 *param_1,undefined8 *param_2)
 * Stores the word-buffer pair via FUN_001e6a48(*param_1,*param_2,self,
 * &LAB_00346840), passing the code label 0x00346840 as a callback slot.
 * Confidence: low
 * Notes: label 0x00346840 passed as callback address. */
void sk_swift_f80_wb_store(sk_word *a, sk_word *b)
{
    sk_word self = 0;  /* unaff_x20 */
    sk_h_001e6a48((sk_word)*a, (sk_word)*b, self, 0x00346840);
}

/* FUN_002eb560 @ 0x002eb560   (est. sk_swift_f80_wb_store2)
 * Ghidra: void FUN_002eb560(undefined8 *param_1,undefined8 *param_2)
 * Duplicate of FUN_002eb55c (word-buffer store with label 0x00346840).
 * Confidence: low
 * Notes: label 0x00346840 passed as callback address. */
void sk_swift_f80_wb_store2(sk_word *a, sk_word *b)
{
    sk_word self = 0;  /* unaff_x20 */
    sk_h_001e6a48((sk_word)*a, (sk_word)*b, self, 0x00346840);
}

/* FUN_002eb594 @ 0x002eb594   (est. sk_swift_f80_word_box_alloc)
 * Ghidra: undefined1[16] FUN_002eb594(long *param_1,undefined8 *param_2)
 * Allocates a 0x30-byte word box (size class 0xda80 via FUN_0036a908), stores
 * its address to *param_1, fills the +0x20/+0x28 slots from the FUN_002eb600
 * (in slice) pair, and returns a 16-byte {pointer to +0x20, type DAT_0034721c}
 * pair describing the buffer.
 * Confidence: low
 * Notes: box allocation + metadata pair; DAT_0034721c type. */
sk_pair sk_swift_f80_word_box_alloc(long *out, sk_word *idx)
{
    long box = (long)sk_h_0036a908(0x30, 0xda80);
    *out = box;
    sk_pair p = sk_swift_f80_word_box_fill(box, *idx, 0);
    *(sk_word *)(box + 0x20) = p.hi;
    *(long *)(box + 0x28) = p.lo;
    p.hi = (sk_word)(box + 0x20);
    p.lo = (sk_word)&sk_dat_0034721c;
    return p;
}

/* FUN_002eb600 @ 0x002eb600   (est. sk_swift_f80_word_box_fill)
 * Ghidra: undefined1[16] FUN_002eb600(undefined8 param_1,long param_2,ulong param_3)
 * Fills a word box: for a zero index returns the {address of FUN_0001a1c8,
 * (param_3 & 0xff)} pair; a negative index raises the noreturn "Negative word
 * index" fatal (0x005d0f70, code 0x290) and a positive index the "Word index
 * out of range" fatal (0x005d1920, code 0x291) — both Swift/IntegerTypes.swift.
 * Confidence: high
 * Notes: string-matched fatals (0x005d0f70/0x005d1920/0x005cd6f0). */
sk_pair sk_swift_f80_word_box_fill(sk_word box, long idx, unsigned long val)
{
    if (idx < 0) {
        sk_fatal_error(0xb, 2, "Negative word index", 0x13, 2,
                       "Swift/IntegerTypes.swift", 0x18, 2, 0x290, 1);
        __builtin_unreachable();
    }
    if (idx == 0) {
        sk_pair p;
        p.hi = val & 0xff;
        p.lo = (sk_word)(void *)&sk_h_0001a1c8;
        return p;
    }
    sk_fatal_error(0xb, 2, "Word index out of range", 0x17, 2,
                   "Swift/IntegerTypes.swift", 0x18, 2, 0x291, 1);
    __builtin_unreachable();
}

/* FUN_002eb700 @ 0x002eb700   (est. sk_swift_u16_div_hi)
 * Ghidra: void FUN_002eb700(undefined8 param_1,undefined1 param_2)
 * 16-bit division/remainder helper: with a non-zero 16-bit divisor, computes
 * quotient and remainder of the 16-bit {param_1<<8|param_2&0xff} dividend and
 * packs them as {quotient in low byte, remainder<<8}; a zero divisor or a
 * dividend high-byte >= divisor hits the noreturn trap. FUN_002eb70c is the
 * three-operand sibling.
 * Confidence: medium
 * Notes: div-by-zero trap via FUN_00348074. */
unsigned long sk_swift_u16_div_hi(sk_word a, unsigned char b)
{
    unsigned int divisor = b & 0xff;
    if (divisor == 0) {
        sk_h_00348074(1);
        sk_h_00351be0();
        sk_fatal_error(0, 0);
        __builtin_unreachable();
    }
    if ((a & 0xff) < divisor) {
        unsigned int lo = (a & 0xff);
        unsigned int hi = (a >> 8) & 0xff;
        unsigned int dividend = lo | (hi << 8);
        unsigned int q = dividend / divisor;
        return (q & 0xff) | ((dividend - q * divisor) << 8);
    }
    sk_h_003488bc(1);
    sk_h_003493d8();
    sk_h_00351be0();
    sk_fatal_error(0, 0);
    __builtin_unreachable();
}

/* FUN_002eb70c @ 0x002eb70c   (est. sk_swift_u16_divrem)
 * Ghidra: uint FUN_002eb70c(uint param_1,uint param_2,uint param_3)
 * 16-bit division-with-remainder: divides the 16-bit {param_1<<8|param_2&0xff}
 * dividend by the 16-bit divisor param_3, returning {quotient in low byte,
 * remainder<<8}. A zero divisor traps; a dividend high byte >= divisor is an
 * overflow trap (noreturn).
 * Confidence: medium
 * Notes: div-by-zero trap via FUN_00348074; overflow trap via FUN_003488bc. */
unsigned int sk_swift_u16_divrem(unsigned int a, unsigned int b, unsigned int c)
{
    unsigned int divisor = c & 0xff;
    if (divisor == 0) {
        sk_h_00348074(1);
    } else if ((a & 0xff) < divisor) {
        unsigned int dividend = (b & 0xff) | ((a & 0xff) << 8);
        unsigned int q = dividend / divisor;
        return (q & 0xff) | ((dividend - q * divisor) << 8);
    } else {
        sk_h_003488bc(1);
        sk_h_003493d8();
    }
    sk_h_00351be0();
    sk_fatal_error(0, 0);
    __builtin_unreachable();
}

/* FUN_002eb844 @ 0x002eb844   (est. sk_swift_u16_div_store2)
 * Ghidra: void FUN_002eb844(undefined1 *param_1,undefined1 *param_2,
 *        undefined1 *param_3)
 * Stores the quotient and remainder bytes of the 16-bit division of *param_3
 * by the x20 self (via FUN_002eb700, in slice) into *param_1/*param_2.
 * Confidence: low
 * Notes: unaff_x20 self register not recovered. */
void sk_swift_u16_div_store2(unsigned char *q, unsigned char *r, unsigned char *hi)
{
    sk_word self = 0;  /* unaff_x20 */
    sk_word res = sk_swift_u16_div_hi((sk_word)*hi, (unsigned char)(self & 0xff));
    *q = (unsigned char)res;
    *r = (unsigned char)((unsigned short)res >> 8);
}

/* FUN_002eb888 @ 0x002eb888   (est. sk_swift_u16_divrem_store)
 * Ghidra: void FUN_002eb888(undefined1 *param_1,undefined1 *param_2,
 *        undefined1 *param_3,undefined1 *param_4)
 * Stores the quotient and remainder bytes of the 16-bit division of
 * {*param_3,*param_4} by the x20 self (via FUN_002eb70c, in slice) into
 * *param_1/*param_2.
 * Confidence: low
 * Notes: unaff_x20 self register not recovered. */
void sk_swift_u16_divrem_store(unsigned char *q, unsigned char *r, unsigned char *lo, unsigned char *hi)
{
    sk_word self = 0;  /* unaff_x20 */
    sk_word res = sk_swift_u16_divrem((sk_word)*lo, (sk_word)*hi, self & 0xff);
    *q = (unsigned char)res;
    *r = (unsigned char)((unsigned short)res >> 8);
}

/* FUN_002eb8d4 @ 0x002eb8d4   (est. sk_swift_byte_forward)
 * Ghidra: void FUN_002eb8d4(undefined1 *param_1,undefined1 *param_2)
 * Stores the result of FUN_0001a1c8(*param_2) (a byte helper) to *param_1.
 * Confidence: low
 * Notes: pure forward to FUN_0001a1c8. */
void sk_swift_byte_forward(unsigned char *out, unsigned char *in)
{
    *out = (unsigned char)sk_h_0001a1c8((sk_word)*in);
}

