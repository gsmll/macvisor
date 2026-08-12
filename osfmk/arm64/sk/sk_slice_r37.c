/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel,
 * arm64e, image base 0) — the cL4 microkernel (GL1), "cL4 (679.100.61)".
 * Ground truth: Ghidra FUN_ names + addresses in program cl4_kernel.raw.
 * Slice R37: 0x4ab7f0-0x4ac088. This is a dense region of tiny runtime
 * helpers in cL4's embedded Swift support: value-witness copy/init
 * witnesses (struct field copies of fixed sizes), tagged-pointer helpers,
 * stack-slot / field getters and setters, fatal-error trampolines, and a
 * cluster of no-op `return;` thunk slots. A source-location string
 * "  // TODO: Atom \xef..." (FUN_004ab9f8) and a " in range" fatal message
 * (FUN_004abb8c) confirm Swift-runtime provenance. All names are estimates
 * unless string-matched. Ghidra FUN_ names are kept only in comments.
 */

#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdbool.h>

typedef uint64_t word_t;
typedef uint32_t seL4_Word;
typedef unsigned char byte;

/* cL4 returns many 16-byte values as a pair of words (lo in x0, hi in x1). */
typedef struct { word_t lo, hi; } sk_val16_t;

/* ------------------------------------------------------------------ *
 * Out-of-slice helper externs (bodies reconstructed by the range workers
 * that own them). Signatures reflect observed register use.
 * ------------------------------------------------------------------ */
extern word_t cL4_ref_retain(word_t obj);                  /* FUN_0036b270 */
extern void   cL4_memcpy_v(word_t dst, word_t src, word_t n); /* FUN_00117cc4 */
extern void   cL4_fatal_44ca08(word_t a, word_t b);        /* FUN_0044ca08 fatal trap */
extern void   cL4_fatal_2acbb8(word_t a, word_t b);        /* thunk_FUN_002acbb8 fatal */
extern void   cL4_reinit_460e20(word_t *dst, word_t *src); /* FUN_00460e20 */
extern void   cL4_call_6862a0(void);                       /* FUN_006862a0 */
extern void   cL4_call_1d4f4(word_t a);                    /* FUN_0001d4f4 */
extern void   cL4_call_36986c(void);                       /* FUN_0036986c */
extern void   cL4_call_46c4e0(void);                       /* FUN_0046c4e0 */
extern word_t cL4_49952c(word_t a, word_t b, word_t c, word_t d,
                         word_t e, word_t f);              /* FUN_0049952c */
extern void   cL4_call_46e6b0(word_t a, word_t b, int flag, word_t d); /* FUN_0046e6b0 */
extern word_t cL4_call_49df18(void);                       /* FUN_0049df18 */
extern void   cL4_call_114330(int a);                      /* thunk_FUN_00114330 */
extern void   cL4_call_498b28(word_t fn);                  /* FUN_00498b28 */
extern void   cL4_call_4a4b14(word_t a, word_t b, word_t c); /* FUN_004a4b14 */

/* ------------------------------------------------------------------ *
 * No-op / witness thunk slots (decompiler collapses these to `return;`).
 * Confidence low; they are empty value-witness or dispatch-table slots.
 * ------------------------------------------------------------------ */

/* FUN_004ab800 @ 0x4ab800  no-op witness slot. Confidence: low */
static void sk_noop_800(void) { (void)0; }

/* FUN_004ab810 @ 0x4ab810  no-op witness slot. Confidence: low */
static void sk_noop_810(void) { (void)0; }

/* FUN_004ab820 @ 0x4ab820  no-op witness slot. Confidence: low */
static void sk_noop_820(void) { (void)0; }

/* FUN_004ab844 @ 0x4ab844  no-op witness slot. Confidence: low */
static void sk_noop_844(void) { (void)0; }

/* FUN_004ab890 @ 0x4ab890  no-op witness slot. Confidence: low */
static void sk_noop_890(void) { (void)0; }

/* FUN_004ab89c @ 0x4ab89c  no-op witness slot. Confidence: low */
static void sk_noop_89c(void) { (void)0; }

/* FUN_004ab8dc @ 0x4ab8dc  no-op witness slot. Confidence: low */
static void sk_noop_8dc(void) { (void)0; }

/* FUN_004ab8e8 @ 0x4ab8e8  no-op witness slot. Confidence: low */
static void sk_noop_8e8(void) { (void)0; }

/* FUN_004ab910 @ 0x4ab910  no-op witness slot. Confidence: low */
static void sk_noop_910(void) { (void)0; }

/* FUN_004ab920 @ 0x4ab920  no-op witness slot. Confidence: low */
static void sk_noop_920(void) { (void)0; }

/* FUN_004ab930 @ 0x4ab930  no-op witness slot. Confidence: low */
static void sk_noop_930(void) { (void)0; }

/* FUN_004ab968 @ 0x4ab968  no-op witness slot. Confidence: low */
static void sk_noop_968(void) { (void)0; }

/* FUN_004ab998 @ 0x4ab998  no-op witness slot. Confidence: low */
static void sk_noop_998(void) { (void)0; }

/* FUN_004ab9bc @ 0x4ab9bc  no-op witness slot. Confidence: low */
static void sk_noop_9bc(void) { (void)0; }

/* FUN_004ab9e0 @ 0x4ab9e0  no-op witness slot. Confidence: low */
static void sk_noop_9e0(void) { (void)0; }

/* FUN_004ab9ec @ 0x4ab9ec  no-op witness slot. Confidence: low */
static void sk_noop_9ec(void) { (void)0; }

/* FUN_004aba28 @ 0x4aba28  no-op witness slot. Confidence: low */
static void sk_noop_a28(void) { (void)0; }

/* FUN_004aba34 @ 0x4aba34  no-op witness slot. Confidence: low */
static void sk_noop_a34(void) { (void)0; }

/* FUN_004aba88 @ 0x4aba88  no-op witness slot. Confidence: low */
static void sk_noop_a88(void) { (void)0; }

/* FUN_004aba94 @ 0x4aba94  no-op witness slot. Confidence: low */
static void sk_noop_a94(void) { (void)0; }

/* FUN_004abacc @ 0x4abacc  no-op witness slot. Confidence: low */
static void sk_noop_acc(void) { (void)0; }

/* FUN_004abad8 @ 0x4abad8  no-op witness slot. Confidence: low */
static void sk_noop_ad8(void) { (void)0; }

/* FUN_004abb1c @ 0x4abb1c  no-op witness slot. Confidence: low */
static void sk_noop_b1c(void) { (void)0; }

/* FUN_004abb28 @ 0x4abb28  no-op witness slot. Confidence: low */
static void sk_noop_b28(void) { (void)0; }

/* FUN_004abbac @ 0x4abbac  no-op witness slot. Confidence: low */
static void sk_noop_bac(void) { (void)0; }

/* FUN_004abbb8 @ 0x4abbb8  no-op witness slot. Confidence: low */
static void sk_noop_bb8(void) { (void)0; }

/* FUN_004abbd4 @ 0x4abbd4  no-op witness slot. Confidence: low */
static void sk_noop_bd4(void) { (void)0; }

/* FUN_004abc0c @ 0x4abc0c  no-op witness slot. Confidence: low */
static void sk_noop_c0c(void) { (void)0; }

/* FUN_004abc50 @ 0x4abc50  no-op witness slot. Confidence: low */
static void sk_noop_c50(void) { (void)0; }

/* FUN_004abc6c @ 0x4abc6c  no-op witness slot. Confidence: low */
static void sk_noop_c6c(void) { (void)0; }

/* FUN_004abcdc @ 0x4abcdc  no-op witness slot. Confidence: low */
static void sk_noop_cdc(void) { (void)0; }

/* FUN_004abcf8 @ 0x4abcf8  no-op witness slot. Confidence: low */
static void sk_noop_cf8(void) { (void)0; }

/* FUN_004abd04 @ 0x4abd04  no-op witness slot. Confidence: low */
static void sk_noop_d04(void) { (void)0; }

/* FUN_004abd20 @ 0x4abd20  no-op witness slot. Confidence: low */
static void sk_noop_d20(void) { (void)0; }

/* FUN_004abd38 @ 0x4abd38  no-op witness slot. Confidence: low */
static void sk_noop_d38(void) { (void)0; }

/* FUN_004abd90 @ 0x4abd90  no-op witness slot. Confidence: low */
static void sk_noop_d90(void) { (void)0; }

/* FUN_004abd9c @ 0x4abd9c  no-op witness slot. Confidence: low */
static void sk_noop_d9c(void) { (void)0; }

/* FUN_004abdb8 @ 0x4abdb8  no-op witness slot. Confidence: low */
static void sk_noop_db8(void) { (void)0; }

/* FUN_004abdc4 @ 0x4abdc4  no-op witness slot. Confidence: low */
static void sk_noop_dc4(void) { (void)0; }

/* FUN_004abe24 @ 0x4abe24  no-op witness slot. Confidence: low */
static void sk_noop_e24(void) { (void)0; }

/* FUN_004abe74 @ 0x4abe74  no-op witness slot. Confidence: low */
static void sk_noop_e74(void) { (void)0; }

/* FUN_004abe90 @ 0x4abe90  no-op witness slot. Confidence: low */
static void sk_noop_e90(void) { (void)0; }

/* FUN_004abea0 @ 0x4abea0  no-op witness slot. Confidence: low */
static void sk_noop_ea0(void) { (void)0; }

/* FUN_004abeb0 @ 0x4abeb0  no-op witness slot. Confidence: low */
static void sk_noop_eb0(void) { (void)0; }

/* FUN_004abed0 @ 0x4abed0  no-op witness slot. Confidence: low */
static void sk_noop_ed0(void) { (void)0; }

/* FUN_004abf10 @ 0x4abf10  no-op witness slot. Confidence: low */
static void sk_noop_f10(void) { (void)0; }

/* FUN_004abf20 @ 0x4abf20  no-op witness slot. Confidence: low */
static void sk_noop_f20(void) { (void)0; }

/* FUN_004abf30 @ 0x4abf30  no-op witness slot. Confidence: low */
static void sk_noop_f30(void) { (void)0; }

/* FUN_004abf40 @ 0x4abf40  no-op witness slot. Confidence: low */
static void sk_noop_f40(void) { (void)0; }

/* FUN_004abf6c @ 0x4abf6c  no-op witness slot. Confidence: low */
static void sk_noop_f6c(void) { (void)0; }

/* FUN_004abf7c @ 0x4abf7c  no-op witness slot. Confidence: low */
static void sk_noop_f7c(void) { (void)0; }

/* FUN_004abfb8 @ 0x4abfb8  no-op witness slot. Confidence: low */
static void sk_noop_fb8(void) { (void)0; }

/* FUN_004abfc8 @ 0x4abfc8  no-op witness slot. Confidence: low */
static void sk_noop_fc8(void) { (void)0; }

/* FUN_004abfd8 @ 0x4abfd8  no-op witness slot. Confidence: low */
static void sk_noop_fd8(void) { (void)0; }

/* FUN_004ac008 @ 0x4ac008  no-op witness slot. Confidence: low */
static void sk_noop_c008(void) { (void)0; }

/* ------------------------------------------------------------------ *
 * Simple getters / setters / field load-store helpers.
 * ------------------------------------------------------------------ */

/* FUN_004ab7f0 @ 0x4ab7f0  (est. sk_counter_bump_indirect)
 * Loads the object pointer stored at [base+8], then increments the
 * 64-bit counter field at [obj+0x10] by 1. Operates on caller-supplied
 * registers (x19 base, x27 delta) as a leaf helper.
 * Confidence: low */
static void sk_counter_bump_indirect(word_t base, word_t delta)
{
    word_t obj = *(word_t *)(base + 8);
    *(word_t *)(obj + 0x10) = delta + 1;
}

/* FUN_004ab834 @ 0x4ab834  (est. sk_load_word)
 * Returns the 64-bit word stored at *p. Value-load helper.
 * Confidence: medium (structural) */
static word_t sk_load_word(word_t *p) { return *p; }

/* FUN_004ab858 @ 0x4ab858  (est. sk_const_858)
 * Returns the tagged constant 0xd000000000000013.
 * Confidence: low */
static word_t sk_const_858(void) { return 0xd000000000000013ULL; }

/* FUN_004ab8ac @ 0x4ab8ac  (est. sk_init_flags)
 * Initializes a small control block: zeroes the word at +0x20 and sets
 * the byte at +0x28 to 1 (enabled/valid flag).
 * Confidence: medium (structural) */
static void sk_init_flags(word_t *p)
{
    *(word_t *)(p + 0x20) = 0;
    *(byte *)(p + 0x28) = 1;
}

/* FUN_004ab98c @ 0x4ab98c  (est. sk_load_field_tagged)
 * Strips the bit-2 tag from the address, then returns the word at
 * offset +0x10 of the resulting object.
 * Confidence: medium (structural) */
static word_t sk_load_field_tagged(word_t tagged)
{
    return *(word_t *)((tagged & ~0x4ULL) + 0x10);
}

/* FUN_004ab9a4 @ 0x4ab9a4  (est. sk_copy_byte_flag)
 * Copies the single byte at +0x10 from src to dst.
 * Confidence: low */
static void sk_copy_byte_flag(word_t *dst, word_t *src)
{
    *(byte *)(dst + 0x10) = *(byte *)(src + 0x10);
}

/* FUN_004ab9b0 @ 0x4ab9b0  (est. sk_prologue_store)
 * Stores an incoming register (x24) into the caller's stack slot at
 * frame-0x110. Decompiler artifact of a function prologue.
 * Confidence: low */
static void sk_prologue_store(word_t frame, word_t v)
{
    *(word_t *)(frame - 0x110) = v;
}

/* FUN_004abaf0 @ 0x4abaf0  (est. sk_store_field_10)
 * Stores v into the word at obj+0x10.
 * Confidence: low */
static void sk_store_field_10(word_t *obj, word_t v) { obj[2] = v; }

/* FUN_004abc44 @ 0x4abc44  (est. sk_store_field_08)
 * Stores v into the word at obj+8.
 * Confidence: low */
static void sk_store_field_08(word_t *obj, word_t v) { obj[1] = v; }

/* FUN_004abec0 @ 0x4abec0  (est. sk_copy_pair_return_old)
 * Copies the 0x18/0x20 word pair from src to dst and returns the value
 * previously held at dst+0x20.
 * Confidence: medium (structural) */
static word_t sk_copy_pair_return_old(word_t *dst, word_t *src)
{
    word_t old = dst[4];
    dst[4] = src[4];
    dst[3] = src[3];
    return old;
}

/* FUN_004abf50 @ 0x4abf50  (est. sk_tag_strip_bit2)
 * Clears bit 2 of the tagged pointer, returning the aligned base.
 * Confidence: medium (structural) */
static word_t sk_tag_strip_bit2(word_t tagged)
{
    return tagged & ~0x4ULL;
}

/* FUN_004abfa8 @ 0x4abfa8  (est. sk_const_zero)
 * Returns 0.
 * Confidence: low */
static word_t sk_const_zero(void) { return 0; }

/* FUN_004abff8 @ 0x4abff8  (est. sk_checksum_add)
 * Returns w9 + w8 + 0x81c1 — a small additive checksum/fold helper over
 * two incoming registers.
 * Confidence: low */
static int sk_checksum_add(int a, int b)
{
    return b + a + 0x81c1;
}

/* FUN_004abd64 @ 0x4abd64  (est. sk_const_f)
 * Returns the constant 0xf.
 * Confidence: low */
static word_t sk_const_f(void) { return 0xf; }

/* FUN_004abd2c @ 0x4abd2c  (est. sk_tag_shift16)
 * Shifts the value left by 16 and tags it with the low bit pattern 5.
 * Tagged-pointer construction helper.
 * Confidence: medium (structural) */
static word_t sk_tag_shift16(word_t v) { return (v << 0x10) | 5; }

/* FUN_004abf00 @ 0x4abf00  (est. sk_tag_shift16_idx)
 * Constructs a tagged pointer from (index, base): base + idx*0x10000,
 * masked to 16-byte alignment, low tag bits set to 5.
 * Confidence: medium (structural) */
static word_t sk_tag_shift16_idx(word_t idx, word_t base)
{
    return ((base + idx * 0x10000) & 0xffffffffffff0000ULL) | 5;
}

/* FUN_004ab974 @ 0x4ab974  (est. sk_pair_tag)
 * Returns the 16-byte pair { 0xf, (incoming x9 | p << 16) }. The low
 * word is the fixed tag 0xf; the high word folds the shifted parameter
 * with an incoming register.
 * Confidence: low */
static sk_val16_t sk_pair_tag(word_t x9, word_t p)
{
    sk_val16_t r;
    r.lo = 0xf;
    r.hi = x9 | (p << 0x10);
    return r;
}

/* FUN_004abaac @ 0x4abaac  (est. sk_pair_swap)
 * Returns the 16-byte pair { param_4, param_1 } — the 1st and 4th
 * arguments reordered into lo/hi.
 * Confidence: low */
static sk_val16_t sk_pair_swap(word_t a, word_t b, word_t c, word_t d)
{
    sk_val16_t r;
    r.lo = d;
    r.hi = a;
    (void)b; (void)c;
    return r;
}

/* FUN_004ab8c8 @ 0x4ab8c8  (est. sk_metadata_pair)
 * Returns the 16-byte pair { FUN_006862a0 (method/impl pointer), 0x70 }.
 * A Swift metadata/method-descriptor pair: implementation address with
 * the descriptor size (0x70 = 112 bytes).
 * Confidence: medium (structural) */
static sk_val16_t sk_metadata_pair(void)
{
    sk_val16_t r;
    r.lo = (word_t)cL4_call_6862a0;
    r.hi = 0x70;
    return r;
}

/* FUN_004ab9f8 @ 0x4ab9f8  (est. sk_debug_str_todo_atom)
 * Returns the 16-byte literal of the source string "  // TODO: Atom \xef…"
 * (bytes 0x4f444f54202f2f20 / 0xef206d6f7441203a). This is a debug
 * source-location placeholder string embedded in generated metadata.
 * Confidence: high (string matched) */
static sk_val16_t sk_debug_str_todo_atom(void)
{
    sk_val16_t r;
    r.lo = 0x4f444f54202f2f20ULL;   /* "  // TODO" */
    r.hi = 0xef206d6f7441203aULL;   /* ": Atom \xef" (multi-byte tail) */
    return r;
}

/* FUN_004aba1c @ 0x4aba1c  (est. sk_ret_stack_arg)
 * Returns the first stack-passed argument unchanged.
 * Confidence: low */
static word_t sk_ret_stack_arg(word_t v) { return v; }

/* FUN_004abae4 @ 0x4abae4  (est. sk_ret_stack_arg2)
 * Returns the stack-passed argument at +0x10 unchanged.
 * Confidence: low */
static word_t sk_ret_stack_arg2(word_t v) { return v; }

/* FUN_004abb80 @ 0x4abb80  (est. sk_ret_stack_arg3)
 * Returns the stack-passed argument at +0x40 unchanged.
 * Confidence: low */
static word_t sk_ret_stack_arg3(word_t v) { return v; }

/* FUN_004abc38 @ 0x4abc38  (est. sk_ret_stack_arg4)
 * Returns the first stack-passed argument unchanged.
 * Confidence: low */
static word_t sk_ret_stack_arg4(word_t v) { return v; }

/* FUN_004ab980 @ 0x4ab980  (est. sk_ret_stack_addr)
 * Returns the address of a caller scratch stack slot (decompiler shows
 * &stack0x18e8 — a caller-provided buffer address).
 * Confidence: low */
static byte *sk_ret_stack_addr(void)
{
    static byte scratch[0x20];
    return scratch;
}

/* FUN_004abaa0 @ 0x4abaa0  (est. sk_ret_stack_addr2)
 * Returns the address of a caller scratch stack slot (&stack0x1a48).
 * Confidence: low */
static byte *sk_ret_stack_addr2(void)
{
    static byte scratch[0x20];
    return scratch;
}

/* FUN_004abcb4 @ 0x4abcb4  (est. sk_ret_stack_addr3)
 * Returns the address of a caller scratch stack slot (&stack0x18).
 * Confidence: low */
static byte *sk_ret_stack_addr3(void)
{
    static byte scratch[0x20];
    return scratch;
}

/* ------------------------------------------------------------------ *
 * Fixed-size value-witness copy witnesses. Each copies N struct fields
 * from source to destination (Ghida shows the two pointers in x19/x20
 * as "unaff" registers). These are Swift struct value-copy helpers.
 * ------------------------------------------------------------------ */

/* FUN_004ab868 @ 0x4ab868  (est. sk_valcopy_60)
 * Memberwise copy of a 0x60-byte struct: words at +0x28,+0x30,+0x38,
 * +0x40, byte at +0x48, words at +0x50,+0x58.
 * Confidence: medium (structural) */
static void sk_valcopy_60(word_t *dst, const word_t *src)
{
    dst[0x28/8] = src[0x28/8];
    dst[0x30/8] = src[0x30/8];
    dst[0x38/8] = src[0x38/8];
    dst[0x40/8] = src[0x40/8];
    *(byte *)(dst + 0x48) = *(byte *)(src + 0x48);
    dst[0x50/8] = src[0x50/8];
    dst[0x58/8] = src[0x58/8];
}

/* FUN_004ab8fc @ 0x4ab8fc  (est. sk_valcopy_partial)
 * Copies word at +0x38 and byte at +0x40 from src to dst.
 * Confidence: low */
static void sk_valcopy_partial(word_t *dst, word_t *src)
{
    *(word_t *)(dst + 0x38) = *(word_t *)(src + 0x38);
    *(byte *)(dst + 0x40) = *(byte *)(src + 0x40);
}

/* FUN_004ab954 @ 0x4ab954  (est. sk_valcopy_30)
 * Memberwise copy of a 0x30-byte struct: words at +0x18..+0x30.
 * Confidence: medium (structural) */
static void sk_valcopy_30(word_t *dst, const word_t *src)
{
    dst[0x30/8] = src[0x30/8];
    dst[0x28/8] = src[0x28/8];
    dst[0x20/8] = src[0x20/8];
    dst[0x18/8] = src[0x18/8];
}

/* FUN_004abb64 @ 0x4abb64  (est. sk_valcopy_38)
 * Memberwise copy of a 6-word struct: words at +8,+0x10,+0x18,+0x20,
 * +0x28,+0x30.
 * Confidence: medium (structural) */
static void sk_valcopy_38(word_t *dst, const word_t *src)
{
    dst[0x10/8] = src[0x10/8];
    dst[8/8]     = src[8/8];
    dst[0x20/8] = src[0x20/8];
    dst[0x18/8] = src[0x18/8];
    dst[0x30/8] = src[0x30/8];
    dst[0x28/8] = src[0x28/8];
}

/* FUN_004abe40 @ 0x4abe40  (est. sk_valcopy_38_b)
 * Memberwise copy of a 6-word struct: words at +8..+0x30 (variant of
 * sk_valcopy_38).
 * Confidence: medium (structural) */
static void sk_valcopy_38_b(word_t *dst, const word_t *src)
{
    dst[0x30/8] = src[0x30/8];
    dst[0x28/8] = src[0x28/8];
    dst[0x20/8] = src[0x20/8];
    dst[0x18/8] = src[0x18/8];
    dst[0x10/8] = src[0x10/8];
    dst[8/8]     = src[8/8];
}

/* FUN_004abcc0 @ 0x4abcc0  (est. sk_valcopy_partial2)
 * Copies byte at +0x30, words at +0x38 and +0x40 from src to dst.
 * Confidence: low */
static void sk_valcopy_partial2(word_t *dst, const word_t *src)
{
    *(byte *)(dst + 0x30) = *(byte *)(src + 0x30);
    *(word_t *)(dst + 0x40) = *(word_t *)(src + 0x40);
    *(word_t *)(dst + 0x38) = *(word_t *)(src + 0x38);
}

/* FUN_004abdd0 @ 0x4abdd0  (est. sk_valcopy_partial3)
 * Copies word at +0x48, bytes at +0x50 and +0x51 from src to dst.
 * Confidence: low */
static void sk_valcopy_partial3(word_t *dst, const word_t *src)
{
    *(word_t *)(dst + 0x48) = *(word_t *)(src + 0x48);
    *(byte *)(dst + 0x50) = *(byte *)(src + 0x50);
    *(byte *)(dst + 0x51) = *(byte *)(src + 0x51);
}

/* FUN_004abdec @ 0x4abdec  (est. sk_valcopy_partial4)
 * Copies word at +0x48, bytes at +0x50 and +0x51 from src to dst
 * (reordered variant of sk_valcopy_partial3).
 * Confidence: low */
static void sk_valcopy_partial4(word_t *dst, const word_t *src)
{
    *(word_t *)(dst + 0x48) = *(word_t *)(src + 0x48);
    *(byte *)(dst + 0x50) = *(byte *)(src + 0x50);
    *(byte *)(dst + 0x51) = *(byte *)(src + 0x51);
}

/* FUN_004abe08 @ 0x4abe08  (est. sk_valcopy_partial5)
 * Copies words at +0x38,+0x40,+0x48 and a 16-bit half at +0x50 from
 * src to dst.
 * Confidence: low */
static void sk_valcopy_partial5(word_t *dst, const word_t *src)
{
    *(word_t *)(dst + 0x38) = *(word_t *)(src + 0x38);
    *(word_t *)(dst + 0x40) = *(word_t *)(src + 0x40);
    *(word_t *)(dst + 0x48) = *(word_t *)(src + 0x48);
    *(uint16_t *)(dst + 0x50) = *(uint16_t *)(src + 0x50);
}

/* FUN_004abee0 @ 0x4abee0  (est. sk_valcopy_pair_48)
 * Copies words at +0x48 and +0x50 from src to dst.
 * Confidence: low */
static void sk_valcopy_pair_48(word_t *dst, const word_t *src)
{
    *(word_t *)(dst + 0x48) = *(word_t *)(src + 0x48);
    *(word_t *)(dst + 0x50) = *(word_t *)(src + 0x50);
}

/* FUN_004abf98 @ 0x4abf98  (est. sk_valcopy_wide_b8)
 * Copies the single word at +0xb8 from src to dst (wide-struct member).
 * Confidence: low */
static void sk_valcopy_wide_b8(word_t *dst, const word_t *src)
{
    *(word_t *)(dst + 0xb8) = *(word_t *)(src + 0xb8);
}

/* ------------------------------------------------------------------ *
 * Copy-and-retain value witnesses: copy one field, then retain (the
 * runtime FUN_0036b270 refcount helper; decompiler drops its argument).
 * ------------------------------------------------------------------ */

/* FUN_004aba50 @ 0x4aba50  (est. sk_valcopy_retain_50) */
static void sk_valcopy_retain_50(word_t *dst, word_t *src)
{
    *(word_t *)(dst + 0x50) = *(word_t *)(src + 0x50);
    cL4_ref_retain(0);
}

/* FUN_004aba60 @ 0x4aba60  (est. sk_valcopy_retain_48) */
static void sk_valcopy_retain_48(word_t *dst, word_t *src)
{
    *(word_t *)(dst + 0x48) = *(word_t *)(src + 0x48);
    cL4_ref_retain(0);
}

/* FUN_004aba70 @ 0x4aba70  (est. sk_valcopy_retain_58) */
static void sk_valcopy_retain_58(word_t *dst, word_t *src)
{
    *(word_t *)(dst + 0x58) = *(word_t *)(src + 0x58);
    cL4_ref_retain(0);
}

/* FUN_004abbc4 @ 0x4abbc4  (est. sk_valcopy_retain_80) */
static void sk_valcopy_retain_80(word_t *dst, word_t *src)
{
    *(word_t *)(dst + 0x80) = *(word_t *)(src + 0x80);
    cL4_ref_retain(0);
}

/* FUN_004abbe0 @ 0x4abbe0  (est. sk_valcopy_retain_78) */
static void sk_valcopy_retain_78(word_t *dst, word_t *src)
{
    *(word_t *)(dst + 0x78) = *(word_t *)(src + 0x78);
    cL4_ref_retain(0);
}

/* FUN_004abda8 @ 0x4abda8  (est. sk_valcopy_retain_60) */
static void sk_valcopy_retain_60(word_t *dst, word_t *src)
{
    *(word_t *)(dst + 0x60) = *(word_t *)(src + 0x60);
    cL4_ref_retain(0);
}

/* ------------------------------------------------------------------ *
 * Struct init / re-init helpers and memcpy shims.
 * ------------------------------------------------------------------ */

/* FUN_004abef0 @ 0x4abef0  (est. sk_init_struct_4)
 * Initializes a 4-field struct: word +0x10, bool flag +0x18 (param_2 & 1),
 * words +0x20 and +0x28.
 * Confidence: medium (structural) */
static void sk_init_struct_4(word_t *p, word_t a, word_t flag, word_t b, word_t c)
{
    p[0x10/8] = a;
    *(word_t *)(p + 0x18) = (word_t)(flag & 1);
    p[0x20/8] = b;
    p[0x28/8] = c;
}

/* FUN_004abafc @ 0x4abafc  (est. sk_indexed_init)
 * Initializes an element at base + idx*stride: byte flag +0x20 (=b&1),
 * words +0x28 and +0x30, and stores the base pointer through *out.
 * Stride comes in an incoming register (in_x9).
 * Confidence: low */
static void sk_indexed_init(word_t base, word_t idx, word_t stride,
                            byte b, word_t a, word_t c, word_t *out)
{
    word_t p = base + idx * stride;
    *(byte *)(p + 0x20) = b & 1;
    *(word_t *)(p + 0x28) = a;
    *(word_t *)(p + 0x30) = c;
    *out = base;
}

/* FUN_004abb34 @ 0x4abb34  (est. sk_struct_reinit_12w)
 * Loads 12 words from src at +0x10..+0x50 into a local staging array,
 * then calls cL4_reinit_460e20(local+8, local+0) to rebuild the struct.
 * The second half re-reads src words at +0x20,+0x28,+0x30,+0x38.
 * Confidence: low */
static void sk_struct_reinit_12w(word_t *src)
{
    word_t t[12];
    t[0] = src[0x10/8]; t[1] = src[0x18/8]; t[2] = src[0x20/8]; t[3] = src[0x28/8];
    t[4] = src[0x30/8]; t[5] = src[0x38/8]; t[6] = src[0x40/8]; t[7] = src[0x48/8];
    t[8] = src[0x20/8]; t[9] = src[0x28/8]; t[10] = src[0x30/8]; t[11] = src[0x38/8];
    cL4_reinit_460e20(&t[8], &t[0]);
}

/* FUN_004abb58 @ 0x4abb58  (est. sk_copy_160_to)
 * Copies 0x160 bytes from the caller stack scratch buffer to dst via
 * cL4_memcpy_v.
 * Confidence: low */
static void sk_copy_160_to(word_t *dst)
{
    byte scratch[0x160];
    cL4_memcpy_v((word_t)dst, (word_t)scratch, 0x160);
}

/* FUN_004abc18 @ 0x4abc18  (est. sk_copy_160_stack)
 * Copies 0x160 bytes between two caller stack scratch buffers via
 * cL4_memcpy_v.
 * Confidence: low */
static void sk_copy_160_stack(void)
{
    byte src[0x160], dst[0x160];
    cL4_memcpy_v((word_t)dst, (word_t)src, 0x160);
}

/* FUN_004abfe8 @ 0x4abfe8  (est. sk_init_struct_pair)
 * Initializes a struct from a 16-byte pair: +0x20 = pair.lo,
 * +0x28 = pair.hi, +0x30 = 0, then stores v into the word at obj+8.
 * Confidence: low */
static void sk_init_struct_pair(word_t *p, sk_val16_t pair, word_t v, word_t *obj)
{
    *(word_t *)(p + 0x20) = pair.lo;
    *(word_t *)(p + 0x28) = pair.hi;
    *(byte *)(p + 0x30) = 0;
    *(word_t *)(obj + 8) = v;
}

/* FUN_004abe68 @ 0x4abe68  (est. sk_init_field_and_call)
 * Stores v into the word at p+0x20, then calls the runtime helper
 * cL4_call_36986c.
 * Confidence: low */
static void sk_init_field_and_call(word_t v, word_t *p)
{
    *(word_t *)(p + 0x20) = v;
    cL4_call_36986c();
}

/* FUN_004abf5c @ 0x4abf5c  (est. sk_indexed_store2)
 * Stores two incoming-register words at (x9+0x20) and (x9+0x28), and
 * saves param_1 through *out (x20). Stride/pointer in incoming regs.
 * Confidence: low */
static void sk_indexed_store2(word_t base, word_t a, word_t b, word_t v, word_t *out)
{
    *(word_t *)(base + 0x20) = a;
    *(word_t *)(base + 0x28) = b;
    *out = v;
}

/* FUN_004abc98 @ 0x4abc98  (est. sk_prologue_store3)
 * Stores three parameters into caller frame slots at -0x130/-0x138/-0x140.
 * Decompiler artifact of a function prologue.
 * Confidence: low */
static void sk_prologue_store3(word_t frame, word_t a, word_t b, word_t c)
{
    *(word_t *)(frame - 0x130) = a;
    *(word_t *)(frame - 0x138) = b;
    *(word_t *)(frame - 0x140) = c;
}

/* FUN_004ac06c @ 0x4ac06c  (est. sk_struct_init_60)
 * Writes the tagged constant 0xd000000000000014 into the caller frame
 * slot at -200, stores param_1 at -0xc0, then copies 0x60 bytes between
 * two stack scratch buffers via cL4_memcpy_v.
 * Confidence: low */
static void sk_struct_init_60(word_t frame, word_t v)
{
    *(word_t *)(frame - 200) = 0xd000000000000014ULL;
    *(word_t *)(frame - 0xc0) = v;
    byte src[0x60], dst[0x60];
    cL4_memcpy_v((word_t)dst, (word_t)src, 0x60);
}

/* ------------------------------------------------------------------ *
 * Fatal-error trampolines and runtime call shims.
 * ------------------------------------------------------------------ */

/* FUN_004ab944 @ 0x4ab944  (est. sk_fatal_944)
 * Triggers the runtime fatal trap cL4_fatal_44ca08 with the fixed tag
 * 0x5e and the constant 0xe100000000000000.
 * Confidence: medium (structural) */
static void sk_fatal_944(void)
{
    cL4_fatal_44ca08(0x5e, 0xe100000000000000ULL);
}

/* FUN_004abe5c @ 0x4abe5c  (est. sk_fatal_parameterized)
 * Triggers the runtime fatal trap cL4_fatal_44ca08 with a caller-supplied
 * tag and the constant 0xe100000000000000.
 * Confidence: medium (structural) */
static void sk_fatal_parameterized(word_t tag)
{
    cL4_fatal_44ca08(tag, 0xe100000000000000ULL);
}

/* FUN_004abb8c @ 0x4abb8c  (est. sk_range_check_fail)
 * Invokes the fatal-error helper cL4_fatal_2acbb8 with the string
 * literal " in range" (bytes 0x676e6172206e6920 / 0xe900000000000065).
 * A Swift range-bounds-check failure trap.
 * Confidence: high (string matched) */
static void sk_range_check_fail(void)
{
    cL4_fatal_2acbb8(0x676e6172206e6920ULL, 0xe900000000000065ULL);
}

/* FUN_004abc28 @ 0x4abc28  (est. sk_call_46c4e0)
 * Calls the runtime helper cL4_call_46c4e0 with no arguments.
 * Confidence: low */
static void sk_call_46c4e0(void) { cL4_call_46c4e0(); }

/* FUN_004abc78 @ 0x4abc78  (est. sk_call_49952c)
 * Calls the runtime helper cL4_49952c (no captured arguments).
 * Confidence: low */
static void sk_call_49952c(void) { (void)cL4_49952c(0,0,0,0,0,0); }

/* FUN_004abd44 @ 0x4abd44  (est. sk_call_1d4f4)
 * Calls the runtime helper cL4_call_1d4f4 with the constant 0xf.
 * Confidence: low */
static void sk_call_1d4f4(void) { cL4_call_1d4f4(0xf); }

/* FUN_004abd70 @ 0x4abd70  (est. sk_call_46e6b0)
 * Calls the runtime helper cL4_call_46e6b0 with a parameter, two stack
 * scratch buffers, and a bool flag (param & 1).
 * Confidence: low */
static void sk_call_46e6b0(word_t a, word_t flag)
{
    byte b0[0x20], b1[0x20];
    cL4_call_46e6b0(a, (word_t)b0, (int)(flag & 1), (word_t)b1);
}

/* FUN_004abe84 @ 0x4abe84  (est. sk_call_498b28)
 * Calls the runtime helper cL4_call_498b28 with a null function pointer.
 * Confidence: low */
static void sk_call_498b28(void) { cL4_call_498b28(0); }

/* FUN_004ac034 @ 0x4ac034  (est. sk_load_retain)
 * Calls cL4_call_49df18 to obtain a pointer, loads the word it points at,
 * and retains it via cL4_ref_retain.
 * Confidence: medium (structural) */
static void sk_load_retain(void)
{
    word_t *p = (word_t *)cL4_call_49df18();
    cL4_ref_retain(*p);
}

/* FUN_004ac050 @ 0x4ac050  (est. sk_call_neg)
 * Calls the runtime helper cL4_call_114330 with the negated parameter.
 * Confidence: low */
static void sk_call_neg(int x) { cL4_call_114330(-x); }

/* FUN_004ac088 @ 0x4ac088  (est. sk_call_4a4b14)
 * Calls the runtime helper cL4_call_4a4b14 with a stack scratch buffer,
 * the constant 0x657bc8, and the global DAT_005a3c70.
 * Confidence: low */
static void sk_call_4a4b14(void)
{
    extern word_t _DAT_005a3c70;
    byte scratch[0x20];
    cL4_call_4a4b14((word_t)scratch, 0x657bc8, (word_t)&_DAT_005a3c70);
}

