/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel,
 * arm64e, image base 0) — the cL4 microkernel (GL1), "cL4 (679.100.61)".
 * Ground truth: Ghidra FUN_ names + addresses in program cl4_kernel.raw.
 * Slice 191: 0x415928-0x41a044. All names are estimates unless string/header
 * matched. Uses seL4/cL4 + Java-runtime vocabulary.
 *
 * This region is the cL4 kernel's embedded Java class-file / reflection
 * structure library: the java.lang.Character method-reference table
 * (FUN_00415b54), method/field/signature descriptor comparison predicates
 * (FUN_004165ec, FUN_00416ad0, FUN_00417454, FUN_00418378, FUN_00418d88,
 * FUN_0041913c, ...), constant-pool entry decode/build walkers
 * (FUN_004176ec, FUN_00417b60, FUN_00419d98, FUN_00419f24) and a large family
 * of debug-print routines that dump tagged words via thunk_FUN_002298d4.
 *
 * Calling convention: the decompiler shows most of these as `void FUN(void)`
 * because every argument (including the C++ `this` pointer, `unaff_x20`) is
 * passed in registers and not modelled as a formal parameter. We model the
 * container `this` pointer as the explicit first parameter `thisp`. Many
 * helpers read/write a 16-byte tagged reference {lo,hi} (the cL4 String /
 * object reference pair); we model that as `cl4_pair_t`. Ghidra FUN_ names
 * are kept only in comments.
 */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

typedef uint64_t word_t;
typedef unsigned int uint;
typedef unsigned char byte;
typedef uint32_t seL4_Word;

/* 16-byte tagged reference: {lo,hi} packed string/object ref pair used
 * throughout the Java class-file library (matches auVar._0_8_/_8_8_). */
typedef struct {
    uint64_t lo;
    uint64_t hi;
} cl4_pair_t;

#define CL4_FATAL() __builtin_trap()   /* SoftwareBreakpoint(1,<addr>) path */

/* ------------------------------------------------------------------ *
 * Out-of-slice helper declarations (bodies reconstructed by the range
 * workers that own them). Signatures are empty-parameter (old-style) for
 * helpers whose register-argument count varies across call sites; this
 * matches the convention used by the other sk_region_* slices.
 * ------------------------------------------------------------------ */
extern word_t       FUN_0001a1c8();/* classfile buffer wrap (0x88/0x98) */
extern word_t       FUN_0006a374();
extern word_t       FUN_0006b42c();/* vec growth probe */
extern void         FUN_0006b674();/* vec/span commit */
extern void         FUN_0006b6f4();
extern void         FUN_000776cc();
extern void         FUN_000778b4();
extern cl4_pair_t   FUN_0007c1c4();/* alloc tagged pair (build string) */
extern cl4_pair_t FUN_00084180();/* allocator/lock enter */
extern word_t       FUN_00084220();/* lock/vector acquire */
extern void         FUN_00084234();/* lock/vector acquire done */
extern word_t       FUN_000863bc();/* allocator domain lookup */
extern void         FUN_0008e500();/* region guard exit (flags) */
extern word_t       FUN_0008e518();/* region guard enter */
extern void         FUN_0009461c();
extern word_t       FUN_000a6fe0();
extern void         FUN_000b4390();/* debug string emit */
extern void         FUN_000b43e8();
extern cl4_pair_t   FUN_000b43f4();
extern word_t       FUN_000dbbe0();/* vec index alloc */
extern void         sk_memcpy();/* FUN_00117cc4 */
extern word_t       FUN_00167404();
extern void         sk_ctx_save();/* FUN_001a84f4 */
extern void         sk_ctx_restore();/* FUN_001a8564 */
extern void         sk_ctx_pair();/* FUN_001b9084 */
extern void         FUN_001bc440();
extern void         FUN_001ebfb0();
extern void         FUN_00205844();
extern void         sk_log_word();/* thunk_FUN_002298d4 */
extern void         FUN_00229a3c();/* print bool/flag marker */
extern cl4_pair_t   FUN_00255d4c();
extern void         FUN_00294cb4();
extern word_t       FUN_0029dac0();
extern word_t       FUN_002a0cf8();/* pair/word compare (0-5 args) */
extern word_t       FUN_002a49a8();
extern void         FUN_002a4ab4();
extern word_t       FUN_002a9ba8();
extern void         sk_printf_str();/* thunk_FUN_002acbb8 (0-2 args) */
extern void         FUN_002ad78c();
extern void         FUN_002ad95c();
extern void         FUN_002bd8f0();
extern void         FUN_00349a18();/* lock enter */
extern void         FUN_0034bd90();/* span commit */
extern void         FUN_003504ac();
extern word_t       FUN_003504d0();/* allocator base probe */
extern void         FUN_003505c4();
extern word_t       FUN_00350624();/* bitset/bitfield (0-1 args) */
extern void         FUN_003507e0();/* scope exit */
extern word_t       FUN_00350968();/* vec elem get/build */
extern word_t       FUN_00350980();
extern word_t       FUN_00350a28();
extern cl4_pair_t   FUN_00350af4();
extern word_t       FUN_00350c5c();
extern void         FUN_003511cc();
extern void         FUN_003511d8();
extern void         FUN_003511f0();
extern void         FUN_003513fc();
extern cl4_pair_t   FUN_0035199c();
extern void         FUN_00351a44();
extern void         FUN_00351a50();
extern void         FUN_00351a5c();
extern void         FUN_00351d30();
extern void         FUN_00351da8();
extern cl4_pair_t   FUN_00351e20();
extern void         FUN_00352c80();
extern void         FUN_003552a0();/* lock/save */
extern void         FUN_00356110();
extern word_t       FUN_00356c6c();/* syscall context read */
extern word_t       FUN_0036a9a0();/* object alloc */
extern void         FUN_0036b118();/* obj ref release */
extern word_t       FUN_0036b270();/* obj ref retain */
extern void         FUN_0036b588();
extern void         FUN_003a25d4();/* token/ref release */
extern word_t       FUN_003a261c();/* allocator probe */
extern void         FUN_004080b0();/* frame guard variant */
extern word_t       FUN_0041001c();/* type pair compare (0-2 args) */
extern void         FUN_00410414();
extern word_t       FUN_004111b0();/* attr pair compare (0-2 args) */
extern word_t       FUN_00411308();/* field pair compare (0-2 args) */
extern void         FUN_00412bb0();
extern void         FUN_00412d5c();
extern word_t       FUN_00413024();/* struct tag compare (0-2 args) */
extern void         FUN_0041360c();
extern word_t       FUN_00413a0c();/* struct tail compare (0-2 args) */
extern word_t       FUN_0041449c();
extern word_t       FUN_00415470();
extern void         FUN_00415570();
extern void         FUN_0041577c();
extern word_t       FUN_0041a0dc();
extern void         FUN_0041a3ec();
extern word_t       FUN_00448fd0();
extern word_t       FUN_00449034();
extern void         FUN_004491c4();
extern void         FUN_0044948c();
extern cl4_pair_t   FUN_0045399c();
extern void         FUN_00456238();
extern void         FUN_00456d90();
extern void         FUN_0045811c();/* print (0-2 args) */
extern void         FUN_004582e8();
extern void         FUN_004589e8();/* dump (0-2 args) */
extern void         FUN_004589f8();
extern word_t       FUN_00458af8();
extern word_t       FUN_00458b14();
extern word_t       FUN_00458b6c();
extern void         FUN_00458b94();
extern void         FUN_00458bac();
extern void         FUN_00458bc4();
extern void         FUN_00458c18();
extern void         FUN_00458c28();
extern void         FUN_00458c50();
extern void         FUN_00458c60();
extern word_t       FUN_00458c88();/* string build (0-2 args) */
extern word_t       FUN_00458cb8();
extern word_t       FUN_00458cd4();
extern word_t       FUN_00458d04();
extern word_t       FUN_00458d10();
extern word_t       FUN_00458d30();/* kind walk (0-2 args) */
extern word_t       FUN_00458d40();
extern void         FUN_0045908c();/* field set/clear (0-1 args) */
extern void         FUN_00461cb8();/* vec append (0-1 args) */
extern void         FUN_00462728();
extern void         FUN_00462898();
extern void         FUN_00462948();
extern void         FUN_00462d5c();
extern word_t       FUN_00462eac();/* field resolve (0-2 args) */
extern void         FUN_00463094();
extern void         FUN_00463210();
extern void         FUN_004637b4();
extern word_t       FUN_004637dc();
extern void         FUN_00463878();
extern void         FUN_00463bd4();
extern cl4_pair_t   FUN_00463dec();
extern void         FUN_00463df8();
extern void         FUN_00463f80();
extern cl4_pair_t   FUN_00463fe8();
extern void         FUN_00464000();
extern word_t       FUN_004640dc();
extern cl4_pair_t   FUN_00464140();
extern void         FUN_004642c0();
extern void         FUN_004642d4();
extern cl4_pair_t   FUN_00464388();
extern cl4_pair_t   FUN_004643a0();
extern cl4_pair_t   FUN_004643cc();
extern void         FUN_004644ac();
extern void         FUN_004644e8();
extern void         FUN_004645a4();/* struct decode enter */
extern void         FUN_00464630();/* struct decode enter */
extern void         FUN_004647b4();/* print string word */
extern void         FUN_004647d4();
extern void         FUN_00464804();
extern cl4_pair_t   FUN_004648ec();
extern void         FUN_004648fc();
extern void         FUN_004649fc();
extern word_t       FUN_00464a08();
extern void         FUN_00464a38();
extern void         FUN_00464a44();
extern word_t       FUN_00464a80();
extern void         FUN_00464aac();
extern void         FUN_00464ac4();
extern word_t       FUN_00464ad0();
extern void         FUN_00464d00();
extern word_t       FUN_00464d0c();/* non-null/kind check (0-2 args) */
extern void         FUN_00464e1c();
extern void         FUN_00464e28();
extern void         FUN_00464eb0();
extern void         FUN_004650e4();
extern void         FUN_00465110();
extern void         FUN_004651a8();
extern void         FUN_004651c8();
extern void         FUN_00465234();
extern void         FUN_00465240();
extern void         FUN_00465258();
extern word_t       FUN_00465264();/* null check (1-2 args) */
extern void         FUN_004652a0();
extern word_t       FUN_004652ac();/* kind check */
extern void         FUN_004653c0();
extern void         FUN_004654a8();
extern void         FUN_00465584();
extern word_t       FUN_004656d4();
extern word_t       FUN_00465728();
extern void         FUN_00465788();
extern word_t       FUN_00465818();
extern void         FUN_00465830();
extern word_t       FUN_00465890();
extern void         FUN_004658a8();
extern word_t       FUN_00465968();
extern cl4_pair_t   FUN_004659d4();
extern word_t       FUN_00465aa0();
extern void         FUN_00465b58();
extern void         FUN_00465bbc();
extern void         FUN_00465c00();
extern void         FUN_00466028();
extern word_t       FUN_004660e0();
extern void         FUN_00466214();
extern word_t       FUN_0046622c();
extern word_t       FUN_004663c0();/* field resolve variant (0-2 args) */
extern void         FUN_00466528();
extern void         FUN_00466568();
extern void         FUN_0046660c();
extern void         FUN_0046663c();
extern void         FUN_00466654();
extern void         FUN_00466660();
extern void         FUN_0046666c();
extern void         FUN_004666b4();
extern void         FUN_004666cc();
extern word_t       FUN_00466730();/* region guard exit + return */
extern word_t       thunk_FUN_0036b270();/* obj ref retain thunk */

/* java.lang.Character static-method name table (packed ASCII string words),
 * indexed by method ordinal. DAT_005a3a50 / DAT_005a3958. */

/* Forward declarations for the in-batch (this-slice) functions so that
 * cross-references can appear before their defining bodies. */
static void sk_java_methref_indexed(word_t thisp, word_t idx);
static void sk_java_methref_bool(word_t thisp, word_t sel);
static void sk_java_methref_resolve(word_t thisp, word_t param_2);
static void sk_java_methref_from_pair(word_t thisp, word_t param_2);
static void sk_java_method_invoke_fn(word_t thisp, word_t param_2, word_t (*param_3)(word_t));
static word_t sk_java_syscall_level(void);
static cl4_pair_t sk_java_character_methref(word_t ordinal);
static void sk_java_char_ref_0(cl4_pair_t *param_1);
static void sk_java_char_ref_1(void);
static void sk_java_char_ref_2(void);
static void sk_java_char_ref_3(word_t param_1);
static void sk_java_char_ref_4(word_t param_1);
static void sk_java_char_ref_5(word_t param_1);
static void sk_java_char_ref_6(word_t param_1);
static void sk_java_dump_words(void);
static void sk_java_vtable_dispatch(void);
static void sk_java_obj_copy_fields(void);
static void sk_java_obj_copy_fields_back(word_t *param_1);
static uint sk_java_pair_cmp_7(word_t *a, word_t *b);
static void sk_java_dump_word30(void);
static void sk_java_dump_guard1(void);
static word_t sk_java_kind_compare(word_t *param_1, word_t pad);
static void sk_java_dump_words4(void);
static void sk_java_dump_guard2(void);
static void sk_java_dump_wrapper1(void);
static void sk_java_retain_field8(void);
static void sk_java_store_fields(void);
static void sk_java_set_field_pair_b(word_t param_1, word_t param_2);
static void sk_java_set_field_pair_b2(word_t param_1, word_t param_2);
static void sk_java_get_field_pair_b(void);
static void sk_java_get_field_pair_b2(void);
static void sk_java_set_field_pair_c(word_t param_1, word_t param_2);
static void sk_java_set_field_pair_c2(word_t param_1, word_t param_2);
static void sk_java_get_field_pair_c(void);
static void sk_java_get_field_pair_c2(void);
static void sk_java_build_methodref_7(word_t *param_1, word_t param_2, word_t param_3,
                                      word_t param_4, word_t param_5, word_t param_6,
                                      word_t *param_7);
static word_t sk_java_method_eq(word_t a0, word_t b0);
static void sk_java_dump_method(void);
static void sk_java_retain_field18(void);
static void sk_java_store_fields_2(void);
static void sk_java_set_field_pair_a(word_t param_1, word_t param_2);
static void sk_java_set_field_pair_a2(word_t param_1, word_t param_2);
static void sk_java_get_field_pair_a(void);
static void sk_java_get_field_pair_a2(void);
static void sk_java_build_methodref_9(word_t *param_1, word_t param_2, word_t param_3,
                                      word_t param_4, word_t param_5, word_t param_6,
                                      word_t param_7, word_t param_8, word_t param_9,
                                      word_t param_10, word_t param_11, word_t param_12,
                                      word_t param_13);
static word_t sk_java_method_eq_full(word_t *param_1, word_t param_2, word_t param_3, word_t param_4);
static void sk_java_dump_method2(void);
static void sk_java_dump_guard3(void);
static void sk_java_dump_guard4(void);
static uint sk_java_descriptor_eq(cl4_pair_t param_1, cl4_pair_t param_2);
static void sk_java_dump_descriptor(cl4_pair_t param_1, word_t param_2);
static void sk_java_dump_descriptor2(cl4_pair_t param_1, word_t param_2);
static void sk_java_vtable_dispatch2(void);
static word_t sk_java_kind_compare_small(word_t *param_1, word_t param_2, word_t param_3, word_t param_4);
static void sk_java_dump_words6(void);
static void sk_java_dump_guard5(void);
static void sk_java_noop_call(void);
static void sk_java_retain_field20(void);
static void sk_java_store_fields_3(void);
static word_t sk_java_sig_eq(char *param_1, char *param_2);
static void sk_java_dump_sig(void);
static void sk_java_dump_guard6(void);
static void sk_java_vtable_dispatch3(void);
static uint sk_java_sig_eq_wrapper(word_t *a, word_t *b);
static word_t sk_java_table_lookup_byte(word_t param_1);
static void sk_java_cp_decode(void);
static uint sk_java_parse_verify(void);
static bool sk_java_bitfield_check(void);
static void sk_java_cp_build(void);
static void sk_java_cp_emit(void);
static void sk_java_cp_wrapper(word_t param_1);
static word_t sk_java_get_ref_a0(void);
static void sk_java_set_ref_a0(word_t param_1);
static word_t sk_java_get_ref_c0(void);
static void sk_java_set_ref_c0(word_t param_1);
static void sk_java_ctor_fields(void);
static word_t sk_java_class_eq(word_t *param_1);
static void sk_java_dump_class(void);
static void sk_java_dump_guard7(void);
static void sk_java_dump_guard8(void);
static cl4_pair_t sk_java_to_string(void);
static void sk_java_to_string_guard(void);
static word_t sk_java_annot_eq(void);
static void sk_java_dump_kind(void);
static void sk_java_dump_guard9(void);
static void sk_java_ctor_simple(void);
static word_t sk_java_annot_eq_wrapper(void);
static void sk_java_dump_attr(void);
static void sk_java_dump_attr2(void);
static void sk_java_dump_attr3(void);
static word_t sk_java_field_sig_eq(long *param_1, long *param_2);
static void sk_java_dump_words8(word_t pad);
static void sk_java_dump_words9(void);
static void sk_java_dump_words10(void);
static void sk_java_dump_wrapper2(void);
static void sk_java_struct_eq_full(void);
static void sk_java_set_field170(word_t param_1);
static void sk_java_ctor_big(void);
static word_t sk_java_class_eq2(void);
static void sk_java_dump_class2(void);
static void sk_java_vtable_dispatch4(void);
static void sk_java_vtable_dispatch5(void);
static word_t sk_java_meth_kind(void);
static cl4_pair_t sk_java_methref_indexed_pair(word_t param_1);
static void sk_java_meth_kind_out(word_t *param_1, word_t *param_2);
static void sk_java_methref_out(word_t *param_1);
static word_t sk_java_meth_ordinal(void);
static cl4_pair_t sk_java_methref_bool_pair(char param_1);
static void sk_java_meth_ordinal_out(word_t *param_1, word_t *param_2);
static void sk_java_methref_bool_out(cl4_pair_t *param_1);
static word_t sk_java_sig_eq2(byte *param_1, byte *param_2);
static void sk_java_dump_ref(word_t param_1);
static void sk_java_dump_ref_guard(void);
static bool sk_java_is_marked(void);
static word_t sk_java_build_check(void);
static void sk_java_struct_walk(void);
static bool sk_java_build_check2(void);
static void sk_java_struct_validate(void);
static void sk_java_struct_grow(void);
static void sk_java_release_pair(void);

static word_t java_char_method_table[256] = {0}; /* ground truth DAT_005a3a50 */

/* ------------------------------------------------------------------ *
 * Simple method-reference dispatch wrappers (frame-guard pattern:
 * save frame -> build/print a tagged pair -> release token -> restore).
 * ------------------------------------------------------------------ */

/* FUN_00415928 @ 0x415928  (est. sk_java_methref_indexed)
 * Resolve the java.lang.Character method named by the byte (param_2 & 0xff)
 * from the name table and emit its tagged reference pair (name + 0xe200 tag).
 * Confidence: medium */
static void sk_java_methref_indexed(word_t thisp, word_t idx)
{
    word_t frame[9];
    sk_ctx_save(frame);
    sk_ctx_pair(frame, java_char_method_table[(idx & 0xff)], 0xe200000000000000);
    FUN_003a25d4(0xe200000000000000);
    sk_ctx_restore();
}

/* FUN_00415984 @ 0x415984  (est. sk_java_methref_bool)
 * Emit a tagged reference whose name is "]" (0x5b) or "[^" (0x5e5b) and tag
 * 0xe100/0xe200 depending on whether param_2 == 1 (a boolean selector).
 * Confidence: medium */
static void sk_java_methref_bool(word_t thisp, word_t sel)
{
    word_t frame[9];
    word_t name = 0x5e5b;
    word_t tag  = 0xe200000000000000;
    if (sel != 1) { name = 0x5b; tag = 0xe100000000000000; }
    sk_ctx_save(frame);
    sk_ctx_pair(frame, name, tag);
    FUN_003a25d4(tag);
    sk_ctx_restore();
}

/* FUN_004159ec @ 0x4159ec  (est. sk_java_methref_resolve)
 * Resolve a method reference from param_2 (via FUN_00415470) and emit it as a
 * tagged pair with the 0xe300 tag, then release the token.
 * Confidence: medium */
static void sk_java_methref_resolve(word_t thisp, word_t param_2)
{
    word_t frame[9];
    word_t resolved;
    sk_ctx_save(frame);
    resolved = FUN_00415470(param_2);
    sk_ctx_pair(frame, resolved, 0xe300000000000000);
    FUN_003a25d4(0xe300000000000000);
    sk_ctx_restore();
}

/* FUN_00415a44 @ 0x415a44  (est. sk_java_methref_from_pair)
 * Build a tagged pair from the {lo,hi} reference returned by FUN_0045399c
 * and emit it; release the hi (token) half.
 * Confidence: medium */
static void sk_java_methref_from_pair(word_t thisp, word_t param_2)
{
    word_t frame[9];
    cl4_pair_t p = FUN_0045399c(param_2);
    sk_ctx_save(frame);
    sk_ctx_pair(frame, p.lo, p.hi);
    FUN_003a25d4(p.hi);
    sk_ctx_restore();
}

/* FUN_00415aa4 @ 0x415aa4  (est. sk_java_method_invoke_fn)
 * Invoke the method thunk param_3 with argument param_2, then run the
 * post-call hooks FUN_00465830 / FUN_0046663c and release the thunk token.
 * Confidence: medium */
static void sk_java_method_invoke_fn(word_t thisp, word_t param_2, word_t (*param_3)(word_t))
{
    word_t frame[9];
    sk_ctx_save(frame);
    (*param_3)(param_2);
    FUN_00465830();
    FUN_0046663c((word_t)frame);
    FUN_003a25d4((word_t)param_3);
    sk_ctx_restore();
}

/* FUN_00415b00 @ 0x415b00  (est. sk_java_syscall_level)
 * Read the current syscall/privilege level (FUN_00356c6c), resolve a name
 * (FUN_002ad95c), and clamp the register-carried level to at most 0x12.
 * Confidence: low */
static word_t sk_java_syscall_level(void)
{
    word_t level;
    FUN_00356c6c();
    FUN_002ad95c(0x67f668);
    FUN_00465240();
    if (0x11 < level) level = 0x12;
    return level;
}

/* FUN_00415b54 @ 0x415b54  (est. sk_java_character_methref)
 * Return the bound method reference (a 16-byte tagged pair) for the
 * java.lang.Character static method selected by the ordinal param_1
 * (javaLowerCase, javaMirrored, javaSpaceChar, ...). The string fragments are
 * packed ASCII in little-endian words with a length/tag byte in the top octet.
 * Confidence: high (string-matched: javaIdentifierIgnorable_005dd110,
 *   javaJavaIdentifierPart_005dd150, javaJavaIdentifierStart_005dd170,
 *   javaLetterOrDigit_005dd1a0, javaUnicodeIdentifierPart_005dd1f0,
 *   javaUnicodeIdentifierStart_005dd210) */
static cl4_pair_t sk_java_character_methref(word_t ordinal)
{
    cl4_pair_t out;
    switch (ordinal) {
    case 1:
        out.hi = 0xeb0000000064656e; out.lo = 0x696665446176616a; return out; /* "javaDefi..end" */
    case 2:
        return FUN_004659d4(0x6176616a, 0xe900000000000074);                 /* "java..t" */
    case 3:
        out = FUN_004643cc((word_t)"javaIdentifierIgnorable\0" /* s_..._005dd110 */, 0xd000000000000017);
        return out;
    case 4:
        out.hi = 0xef63696870617267; out.lo = 0x6f6564496176616a; return out; /* "javaIdeo..grap" */
    case 5:
        out.hi = 0xee006c6f72746e6f; out.lo = 0x434f53496176616a; return out; /* "javaISOC..rotnol" */
    case 6:
        out = FUN_004643cc((word_t)"javaJavaIdentifierPart\0" /* s_..._005dd150 */, 0xd000000000000016);
        return out;
    case 7:
        out = FUN_004643cc((word_t)"javaJavaIdentifierStart\0" /* s_..._005dd170 */, 0xd000000000000017);
        return out;
    case 8:
        out.hi = 0xea00000000007265; out.lo = 0x7474654c6176616a; return out; /* "javaLett..re" */
    case 9:
        return FUN_004643a0((word_t)"javaLetterOrDigit\0" /* s_..._005dd1a0 */);
    case 10:
        return FUN_000b43f4(0x65776f4c6176616a, 0x6573614372);               /* "javaLowe..rCase" */
    case 0xb:
        out.hi = 0xec0000006465726f; out.lo = 0x7272694d6176616a; return out; /* "javaMirr..ored" */
    case 0xc:
        out.hi = 0xed00007261684365; out.lo = 0x636170536176616a; return out; /* "javaSpaCeChar" */
    case 0xd:
        out.hi = 0xed00006573614365; out.lo = 0x6c7469546176616a; return out; /* "javaTitlCase" */
    case 0xe:
        out = FUN_004643cc((word_t)"javaUnicodeIdentifierPart\0" /* s_..._005dd1f0 */, 0xd000000000000019);
        return out;
    case 0xf:
        return FUN_00464388((word_t)"javaUnicodeIdentifierStart\0" /* s_..._005dd210 */,
                            0x68706c4176616a, 0xee00636974656261);
    case 0x10:
        return FUN_000b43f4(0x657070556176616a, 0x6573614372);               /* "javaUppe..rCase" */
    case 0x11:
        out.hi = 0xee00656361707365; out.lo = 0x746968576176616a; return out; /* "javaWhi..espace" */
    default:
        out.hi = 0xee00636974656261; out.lo = 0x68706c416176616a; return out; /* "javaA..ebitac" */
    }
}

/* FUN_00415e0c @ 0x415e0c  (est. sk_java_char_ref_0)
 * Copy the java.lang.Character method reference (from the ordinal in *thisp)
 * into the caller's 16-byte output slot param_1.
 * Confidence: medium */
static void sk_java_char_ref_0(cl4_pair_t *param_1)
{
    cl4_pair_t p = sk_java_character_methref(*((word_t *)0)); /* *unaff_x20 */
    *param_1 = p;
}

/* FUN_00415e38 / 00415e3c  (est. sk_java_char_ref_dispatch)
 * Dispatch the method-reference builder (FUN_00415b54) on the ordinal in
 * *thisp via the FUN_00415570 binder. Two near-identical thunks.
 * Confidence: medium */
static void sk_java_char_ref_1(void)
{
    FUN_00415570(*(word_t *)0, (word_t)sk_java_character_methref);
}
static void sk_java_char_ref_2(void)
{
    FUN_00415570(*(word_t *)0, (word_t)sk_java_character_methref);
}

/* FUN_00415e68 / 00415e6c  (est. sk_java_char_ref_bind)
 * Bind the method-reference builder with argument param_1 via FUN_0041577c.
 * Two near-identical thunks.
 * Confidence: medium */
static void sk_java_char_ref_3(word_t param_1)
{
    FUN_0041577c(param_1, *(word_t *)0, (word_t)sk_java_character_methref);
}
static void sk_java_char_ref_4(word_t param_1)
{
    FUN_0041577c(param_1, *(word_t *)0, (word_t)sk_java_character_methref);
}

/* FUN_00415e98 / 00415e9c  (est. sk_java_char_ref_invoke)
 * Invoke the method-reference builder via sk_java_method_invoke_fn with the
 * ordinal in *thisp. Two near-identical thunks.
 * Confidence: medium */
static void sk_java_char_ref_5(word_t param_1)
{
    sk_java_method_invoke_fn(param_1, *(word_t *)0, (word_t (*)(word_t))sk_java_character_methref);
}
static void sk_java_char_ref_6(word_t param_1)
{
    sk_java_method_invoke_fn(param_1, *(word_t *)0, (word_t (*)(word_t))sk_java_character_methref);
}

/* ------------------------------------------------------------------ *
 * Debug-print routines: dump tagged words (each shifted >>0xe to expose the
 * payload) via sk_log_word (thunk_FUN_002298d4).
 * ------------------------------------------------------------------ */

/* FUN_00415f84 @ 0x415f84  (est. sk_java_dump_words)
 * Dump the words of a 5-word record at *thisp: prints the kind flag
 * (thunk_FUN_002298d4(1)/FUN_00229a3c) and the four data words shifted >>0xe.
 * Confidence: medium */
static void sk_java_dump_words(void)
{
    word_t a = *(word_t *)((word_t *)0);     /* *unaff_x20 */
    word_t b = ((word_t *)0)[1];
    if (*(char *)((word_t *)0 + 4) == 1) {
        sk_log_word(1);
        cl4_pair_t p = FUN_0007c1c4();
        sk_ctx_pair((word_t *)p.lo, p.hi, b);
        return;
    }
    word_t c = ((word_t *)0)[2];
    word_t d = ((word_t *)0)[3];
    sk_log_word(0);
    if ((b & 0xff) == 1) { FUN_00229a3c(0); }
    else { FUN_00229a3c(1); sk_log_word(a); }
    sk_log_word(c >> 0xe);
    sk_log_word(d >> 0xe);
}

/* FUN_0041606c @ 0x41606c  (est. sk_java_vtable_dispatch)
 * Enter the vtable dispatch frame (FUN_004653c0), invoke the vtable thunk
 * in x19 with the frame, then restore.
 * Confidence: medium */
static void sk_java_vtable_dispatch(void)
{
    word_t frame[9];
    FUN_004653c0();
    (*(word_t (*)(word_t *))((word_t *)0))(frame);   /* (*unaff_x19)(frame) */
    sk_ctx_restore();
}

/* FUN_004160ac @ 0x4160ac  (est. sk_java_obj_copy_fields)
 * Allocate/enter a new record (FUN_00084220) and copy the 7 fields
 * {kind byte, lo, hi, ...} from the source *thisp into the fresh object.
 * Confidence: low */
static void sk_java_obj_copy_fields(void)
{
    word_t rec = FUN_00084220();
    FUN_00466028();
    word_t f1 = *(word_t *)((word_t *)0 + 0x28);
    word_t f2 = *(word_t *)((word_t *)0 + 0x30);
    char   kind = *(char *)((word_t *)0 + 0x20);
    FUN_00462948();
    FUN_00458b94();
    ((word_t *)rec)[0] = ((word_t *)0)[0];    /* extraout_x8 dst */
    ((word_t *)rec)[1] = ((word_t *)0)[1];
    ((word_t *)rec)[2] = ((word_t *)0)[2];
    ((word_t *)rec)[3] = ((word_t *)0)[3];
    *(char *)((word_t *)rec + 4) = kind;
    ((word_t *)rec)[5] = f1;
    ((word_t *)rec)[6] = f2;
    FUN_00084234(rec);
}

/* FUN_00416104 @ 0x416104  (est. sk_java_obj_copy_fields_back)
 * Copy the 7 fields of the record pointed to by param_1 back into the
 * destination *thisp, after validating via FUN_00458bac.
 * Confidence: low */
static void sk_java_obj_copy_fields_back(word_t *param_1)
{
    char  kind = *(char *)(param_1 + 4);
    word_t f1 = param_1[5];
    word_t f2 = param_1[6];
    FUN_00458bac(((word_t *)0)[0], ((word_t *)0)[1], ((word_t *)0)[2], ((word_t *)0)[3],
                 *(char *)((word_t *)0 + 4));
    word_t v0 = param_1[0];
    word_t v3 = param_1[3];
    word_t v2 = param_1[2];
    ((word_t *)0)[1] = param_1[1];
    ((word_t *)0)[0] = v0;
    ((word_t *)0)[3] = v3;
    ((word_t *)0)[2] = v2;
    *(char *)((word_t *)0 + 4) = kind;
    ((word_t *)0)[5] = f1;
    ((word_t *)0)[6] = f2;
}

/* FUN_00416198 @ 0x416198  (est. sk_java_pair_cmp_7)
 * Compare two 7-word records for equality via FUN_00449034; return bool.
 * Confidence: medium */
static uint sk_java_pair_cmp_7(word_t *a, word_t *b)
{
    word_t la[7], lb[7];
    for (int i = 0; i < 7; i++) { la[i] = a[i]; lb[i] = b[i]; }
    return FUN_00449034((word_t)&la, (word_t)&lb) & 1;
}

/* FUN_004161f4 @ 0x4161f4  (est. sk_java_dump_word30)
 * Dump the record (sk_java_dump_words) then print the word at *thisp+0x30.
 * Confidence: medium */
static void sk_java_dump_word30(void)
{
    word_t v = *(word_t *)((word_t *)0 + 0x30);
    sk_java_dump_words();
    FUN_0046666c();
    sk_log_word(v >> 0xe);
}

/* FUN_00416230 @ 0x416230  (est. sk_java_dump_guard1)
 * Frame-guarded dump: enter, dump via sk_java_dump_words, post-hooks, restore.
 * Confidence: medium */
static void sk_java_dump_guard1(void)
{
    word_t frame[9];
    FUN_004080b0();
    sk_java_dump_words();
    FUN_00464eb0();
    FUN_004652a0();
    sk_ctx_restore();
}

/* FUN_004162a8 @ 0x4162a8  (est. sk_java_kind_compare)
 * Compare two structural records of a given kind: both non-null, same tag and
 * field pairs (FUN_00411308), kind flags equal. Returns 0/1.
 * Confidence: low */
static word_t sk_java_kind_compare(word_t *param_1, word_t pad)
{
    if (FUN_00464d0c(*param_1) == 0) {
        FUN_00463094();
        if (((FUN_00465264(((word_t *)0)[0]) != 0) ||
             ((FUN_00411308(((word_t *)0)[0x10], ((word_t *)0)[0x10]) & 1) == 0)) ||
            (FUN_00464d0c(((word_t *)0)[0x18]) != 0) ||
            FUN_00465264(((word_t *)0)[0x20]) != 0) {
            return 0;
        }
        return 1;
    }
    return 0;
}

/* FUN_0041632c @ 0x41632c  (est. sk_java_dump_words4)
 * Dump four tagged words from the record at x19 (two pairs), shifted >>0xe.
 * Confidence: medium */
static void sk_java_dump_words4(void)
{
    word_t *rec = (word_t *)0;   /* unaff_x19 */
    FUN_00464a44();
    word_t w1 = rec[1];
    sk_log_word(rec[0] >> 0xe);
    sk_log_word(w1 >> 0xe);
    FUN_0045811c();
    word_t w4 = rec[4];
    sk_log_word(rec[3] >> 0xe);
    sk_log_word(w4 >> 0xe);
}

/* FUN_00416388 @ 0x416388  (est. sk_java_dump_guard2)
 * Dump the fields of the record at x19 (kind, word, two pairs) with guards.
 * Confidence: medium */
static void sk_java_dump_guard2(void)
{
    word_t frame[9];
    FUN_004644e8();
    FUN_00465234(((word_t *)0)[0]);
    FUN_004652a0();
    FUN_0045811c(frame, ((word_t *)0)[0x10]);
    FUN_00465234(((word_t *)0)[0x18]);
    FUN_00464eb0();
    sk_ctx_restore();
}

/* FUN_004163ec @ 0x4163ec  (est. sk_java_dump_wrapper1)
 * Frame-guarded dump of sk_java_dump_words4.
 * Confidence: medium */
static void sk_java_dump_wrapper1(void)
{
    word_t frame[9];
    sk_ctx_save(frame);
    sk_java_dump_words4();
    sk_ctx_restore();
}

/* FUN_0041642c @ 0x41642c  (est. sk_java_retain_field8)
 * Retain the capability/object at *thisp+8 then run the post-hook FUN_00462d5c.
 * Confidence: medium */
static void sk_java_retain_field8(void)
{
    thunk_FUN_0036b270(((word_t *)0)[1]);
    FUN_00462d5c();
}

/* FUN_00416464 @ 0x416464  (est. sk_java_store_fields)
 * Release the token at *thisp[1], then overwrite the 4 words of *thisp with
 * the four register-carried values (x23,x22,x21,x19).
 * Confidence: medium */
static void sk_java_store_fields(void)
{
    word_t w = ((word_t *)0)[1];
    FUN_00349a18();
    FUN_003a25d4(w);
    ((word_t *)0)[0] = 0;  /* x23 */
    ((word_t *)0)[1] = 0;  /* x22 */
    ((word_t *)0)[2] = 0;  /* x21 */
    ((word_t *)0)[3] = 0;  /* x19 */
}

/* FUN_004164b4 / 004164b8  (est. sk_java_set_field_pair_b)
 * Store the {param_2,param_1} pair into the *thisp+0x20 field slot.
 * Two near-identical thunks.
 * Confidence: medium */
static void sk_java_set_field_pair_b(word_t param_1, word_t param_2)
{
    FUN_00462eac(param_2, param_1);
    FUN_0045908c(0x20);
}
static void sk_java_set_field_pair_b2(word_t param_1, word_t param_2)
{
    FUN_00462eac(param_2, param_1);
    FUN_0045908c(0x20);
}

/* FUN_004164d8 / 004164dc  (est. sk_java_get_field_pair_b)
 * Read the pair from *thisp+0x20 via FUN_00462eac / FUN_00458bc4.
 * Two near-identical thunks.
 * Confidence: medium */
static void sk_java_get_field_pair_b(void)
{
    word_t v = FUN_00462eac();
    FUN_00458bc4(v, ((word_t *)0) + 0x20);
}
static void sk_java_get_field_pair_b2(void)
{
    word_t v = FUN_00462eac();
    FUN_00458bc4(v, ((word_t *)0) + 0x20);
}

/* FUN_004164f8 / 004164fc  (est. sk_java_set_field_pair_c)
 * Store the {param_2,param_1} pair into the *thisp+0x60 field slot.
 * Confidence: medium */
static void sk_java_set_field_pair_c(word_t param_1, word_t param_2)
{
    FUN_004663c0(param_2, param_1);
    FUN_0045908c(0x60);
}
static void sk_java_set_field_pair_c2(word_t param_1, word_t param_2)
{
    FUN_004663c0(param_2, param_1);
    FUN_0045908c(0x60);
}

/* FUN_0041651c / 00416520  (est. sk_java_get_field_pair_c)
 * Read the pair from *thisp+0x60 via FUN_004663c0 / FUN_00458bc4.
 * Confidence: medium */
static void sk_java_get_field_pair_c(void)
{
    word_t v = FUN_004663c0();
    FUN_00458bc4(v, ((word_t *)0) + 0x60);
}
static void sk_java_get_field_pair_c2(void)
{
    word_t v = FUN_004663c0();
    FUN_00458bc4(v, ((word_t *)0) + 0x60);
}

/* FUN_0041653c @ 0x41653c  (est. sk_java_build_methodref_7)
 * Build a 0x88-byte method-reference record from the 7 register args
 * (param_2..param_5 plus a pair from param_7), validating via FUN_00458c18
 * and FUN_00458c28, and copy the result into param_1.
 * Confidence: low */
static void sk_java_build_methodref_7(word_t *param_1, word_t param_2, word_t param_3,
                                      word_t param_4, word_t param_5, word_t param_6,
                                      word_t *param_7)
{
    word_t src[0x11];    /* 0x88 bytes */
    word_t bufA[0x11];
    word_t bufB[0x11];
    for (int i = 0; i < 0x11; i++) src[i] = 0;
    src[0] = param_2; src[1] = param_3; src[2] = param_4; src[3] = param_5;
    FUN_00462eac();
    FUN_00458bc4(param_6, (word_t *)&src[4]);
    src[5] = param_7[1];
    src[4] = *param_7;
    src[7] = param_7[3];
    src[6] = param_7[2];
    src[8] = param_7[4];
    sk_memcpy(bufA, src, 0x88);
    sk_memcpy(bufB, src, 0x88);
    FUN_00458c18(bufA, bufA);
    FUN_00458c28(bufB);
    sk_memcpy(param_1, bufA, 0x88);
}

/* FUN_004165ec @ 0x4165ec  (est. sk_java_method_eq)
 * Structural equality of two method descriptors (the *thisp and x19 records):
 * compares kind tags, parameter type lists and the return type, descending
 * through the shared classfile compare helpers (FUN_00464aac/FUN_003511cc/
 * FUN_003511d8/..., FUN_004171f8). Returns bool via FUN_00466730.
 * Confidence: medium */
static word_t sk_java_method_eq(word_t a0, word_t b0)
{
    word_t *a = (word_t *)0;   /* unaff_x20 */
    word_t *b = (word_t *)0;   /* unaff_x19 */
    word_t *probe = (word_t *)FUN_003504d0();
    word_t result;
    bool match = (*probe == *b && (word_t)b[1] <= (word_t)a[1]);
    if (*probe == *b && (word_t)a[1] == b[1]) {
        FUN_00464ad0();
        if (0 == 0) goto done_eq;
    } else {
        FUN_002a0cf8();
        FUN_00464a08();
        if ((0 & 1) == 0) goto return_zero;
        FUN_00465968();
        match = false;
        if (match) goto return_zero;
        goto deep;
    }
deep:
    FUN_004658a8();
    if (!match) {
        /* compare parameter lists (indices 4..0xb) and return type */
        word_t bp[8], ap[8], bt[3], at[3];
        for (int i = 0; i < 8; i++) { ap[i] = a[4 + i]; bp[i] = b[4 + i]; }
        if (b[6] == 0) {                    /* local_138 (a[6]) */
            if (b[8] != 0) goto build_mixed;
            FUN_00464aac(); FUN_003511cc(); FUN_0045908c(); FUN_004651c8();
            FUN_003511cc(); FUN_0045908c(); FUN_003511d8(&ap[0]); FUN_00461cb8();
            result = 1;
        } else if (b[8] == 0) {
build_mixed:
            sk_memcpy(&ap[0], &bp[0], 0x80);
            FUN_00464aac(); FUN_003513fc(); FUN_0045908c(); FUN_004651c8();
            FUN_003513fc(); FUN_0045908c(); FUN_00465bbc();
            result = 0;
        } else {
            word_t m = sk_java_kind_compare_small(0, 0, 0, 0);
            FUN_00464aac(); FUN_003511f0(); FUN_0045908c(); FUN_004651c8();
            FUN_003511f0(); FUN_0045908c(); FUN_003505c4(&ap[0]); FUN_00461cb8();
            FUN_003505c4(&bp[0]); FUN_00461cb8();
            if ((m & 1) != 0) goto tail_eq;
        }
        result = 0;
        goto out;
    }
    result = 0;
    goto out;
tail_eq:
    if ((word_t)a[0xe] == 0) {
        if (b[0xe] == 0) { result = 1; goto out; }
    } else if (b[0xe] != 0) {
        word_t cmp = sk_java_kind_compare(0, 0);
        if ((cmp & 1) != 0) { result = 1; goto out; }
    }
    result = 0;
    goto out;
done_eq:
    result = (b[0x80] == a[0x80]) && ((a[0x88] ^ b[0x88]) < 0x4000 && (a[0x90] ^ b[0x90]) < 0x4000);
    goto out;
return_zero:
    result = 0;
out:
    return FUN_00466730(result, 0);
}

/* FUN_0041680c @ 0x41680c  (est. sk_java_dump_method)
 * Dump a method record: name pair, kind words, and (if present) the method
 * body / exception tables at +0x38 and +0x70 via FUN_004172ac.
 * Confidence: medium */
static void sk_java_dump_method(void)
{
    FUN_00466568();
    word_t base = FUN_004656d4();
    word_t *a = (word_t *)0;    /* unaff_x20 */
    word_t *m = (word_t *)0;    /* unaff_x21 */
    sk_ctx_pair(base, a[0], a[1]);
    sk_log_word(a[2] >> 0xe);
    sk_log_word(((word_t *)(m + 0x18))[0] >> 0xe);
    if (*(long *)(m + 0x38) == 0) {
        FUN_00464ac4(); FUN_00229a3c();
    } else {
        FUN_00465584(); FUN_004650e4(); sk_java_dump_words6();
    }
    if (*(long *)(m + 0x70) == 0) {
        FUN_00464ac4(); FUN_00229a3c();
    } else {
        word_t e0 = *(word_t *)(m + 0x78);
        word_t e1 = *(word_t *)(m + 0x80);
        word_t t0 = *(word_t *)(m + 0x60);
        word_t t1 = *(word_t *)(m + 0x68);
        FUN_00465584();
        sk_log_word(t0 >> 0xe);
        sk_log_word(t1 >> 0xe);
        FUN_003504ac();
        FUN_0045811c();
        sk_log_word(e0 >> 0xe);
        sk_log_word(e1 >> 0xe);
    }
    FUN_00466528(0);
}

/* FUN_0041691c @ 0x41691c  (est. sk_java_retain_field18)
 * Retain the object at *thisp+0x18 then run FUN_00462d5c.
 * Confidence: medium */
static void sk_java_retain_field18(void)
{
    thunk_FUN_0036b270(((word_t *)0)[3]);
    FUN_00462d5c();
}

/* FUN_00416954 @ 0x416954  (est. sk_java_store_fields_2)
 * Release the token at *thisp+0x18, then overwrite the 4 words at
 * *thisp+0x10..+0x28 with the four register-carried values.
 * Confidence: medium */
static void sk_java_store_fields_2(void)
{
    FUN_00349a18();
    FUN_003a25d4(((word_t *)0)[3]);
    ((word_t *)0)[2] = 0;  /* x23 */
    ((word_t *)0)[3] = 0;  /* x22 */
    ((word_t *)0)[4] = 0;  /* x21 */
    ((word_t *)0)[5] = 0;  /* x19 */
}

/* FUN_00416994 / 00416998  (est. sk_java_set_field_pair_a)
 * Store the {param_2,param_1} pair into the *thisp+0x40 field slot.
 * Confidence: medium */
static void sk_java_set_field_pair_a(word_t param_1, word_t param_2)
{
    FUN_00462eac(param_2, param_1);
    FUN_0045908c(0x40);
}
static void sk_java_set_field_pair_a2(word_t param_1, word_t param_2)
{
    FUN_00462eac(param_2, param_1);
    FUN_0045908c(0x40);
}

/* FUN_004169b8 / 004169bc  (est. sk_java_get_field_pair_a)
 * Read the pair from *thisp+0x40 via FUN_00462eac / FUN_00458bc4.
 * Confidence: medium */
static void sk_java_get_field_pair_a(void)
{
    word_t v = FUN_00462eac();
    FUN_00458bc4(v, ((word_t *)0) + 0x40);
}
static void sk_java_get_field_pair_a2(void)
{
    word_t v = FUN_00462eac();
    FUN_00458bc4(v, ((word_t *)0) + 0x40);
}

/* FUN_004169f0 @ 0x4169f0  (est. sk_java_build_methodref_9)
 * Build a 0x98-byte method-reference record from the 9 register args
 * (param_2..param_9 plus a pair from param_11..param_13), validating via
 * FUN_00458c50 / FUN_00458c60, and copy the result into param_1.
 * Confidence: low */
static void sk_java_build_methodref_9(word_t *param_1, word_t param_2, word_t param_3,
                                      word_t param_4, word_t param_5, word_t param_6,
                                      word_t param_7, word_t param_8, word_t param_9,
                                      word_t param_10, word_t param_11, word_t param_12,
                                      word_t param_13)
{
    word_t src[0x13];   /* 0x98 bytes */
    word_t bufA[0x13];
    word_t bufB[0x13];
    for (int i = 0; i < 0x13; i++) src[i] = 0;
    src[0] = param_2; src[1] = param_3; src[2] = param_4; src[3] = param_5;
    src[4] = param_6; src[5] = param_7; src[6] = param_8; src[7] = param_9;
    FUN_00462eac(param_10);
    FUN_00458bc4(FUN_00462eac(), (word_t *)(0 + 0x40));
    src[8] = param_11; src[9] = param_12; src[10] = param_13;
    sk_memcpy(bufA, src, 0x98);
    sk_memcpy(bufB, src, 0x98);
    FUN_00458c50(bufA, bufA);
    FUN_00458c60(bufB);
    sk_memcpy(param_1, bufA, 0x98);
}

/* FUN_00416ad0 @ 0x416ad0  (est. sk_java_method_eq_full)
 * Full structural equality of two 0x80-byte method/field descriptors
 * (x19 vs x20): kind, flags (char at +0x80), tag pairs (XOR < 0x4000),
 * parameter type lists and return types. Returns bool.
 * Confidence: medium */
static word_t sk_java_method_eq_full(word_t *param_1, word_t param_2, word_t param_3, word_t param_4)
{
    word_t *a = (word_t *)0;   /* unaff_x20 */
    word_t *b = (word_t *)0;   /* unaff_x19 */
    word_t result;
    if (FUN_00464d0c(*param_1) != 0) return 0;
    FUN_00463094();
    if (0 == 0) {
        FUN_00465728();
        bool le = (bool)0 && param_4 <= 0;
        if ((bool)0 && 0 == param_4) {
            FUN_00464ad0();
            if (0 != 0) goto ret_zero;
        } else {
            FUN_002a0cf8();
            word_t t = FUN_00464a08();
            if ((0 & 1) == 0) goto ret_zero;
            FUN_00465968();
            if (le) goto ret_zero;
        }
        FUN_004658a8();
        if ((1 && (FUN_004644ac(), 0 == 0)) &&
            (FUN_00464d0c(a[0x38]), 0 == 0)) {
            word_t ap[8], bp[8];
            for (int i = 0; i < 8; i++) { ap[i] = a[0x40 / 8 + i]; bp[i] = b[0x40 / 8 + i]; }
            if (a[0x58/8] == 0) {           /* local_138 = a[0x58/8] */
                if (a[0x68/8] != 0) goto build_mixed;
                FUN_00464aac(); FUN_003511cc(); FUN_0045908c(); FUN_004651c8();
                FUN_003511cc(); FUN_0045908c(); FUN_003511d8(&ap[0]); FUN_00461cb8();
                goto tail_cmp;
            } else if (a[0x68/8] == 0) {
build_mixed:
                sk_memcpy(&ap[0], &bp[0], 0x80);
                FUN_00464aac(); FUN_003513fc(); FUN_0045908c(); FUN_004651c8();
                FUN_003513fc(); FUN_0045908c(); FUN_00465bbc();
            } else {
                word_t m = sk_java_kind_compare_small(0, 0, 0, 0);
                FUN_00464aac(); FUN_003511f0(); FUN_0045908c(); FUN_004651c8();
                FUN_003511f0(); FUN_0045908c(); FUN_003505c4(&ap[0]); FUN_00461cb8();
                FUN_003505c4(&bp[0]); FUN_00461cb8();
                if ((m & 1) != 0) goto tail_cmp;
            }
            result = 0;
            goto out;
tail_cmp:
            if (*(char *)(b + 0x80/8) == *(char *)(a + 0x80/8)) {
                result = (word_t)((a[0x88/8] ^ b[0x88/8]) < 0x4000 &&
                                  (a[0x90/8] ^ b[0x90/8]) < 0x4000);
                goto out;
            }
        }
    }
ret_zero:
    result = 0;
out:
    return FUN_00466730(result, 0);
}

/* FUN_00416cfc @ 0x416cfc  (est. sk_java_dump_method2)
 * Dump a method record: name pair, descriptor words, exception-table flag
 * (FUN_004172ac), and the method body region at +0x80/+0x88/+0x90.
 * Confidence: medium */
static void sk_java_dump_method2(void)
{
    word_t *a = (word_t *)0;    /* unaff_x20 */
    word_t *m = (word_t *)0;    /* unaff_x21 */
    FUN_004656d4();
    word_t w1 = a[1];
    FUN_004647b4(a[0]);
    sk_log_word(0);
    sk_log_word(w1 >> 0xe);
    word_t d0 = *(word_t *)(m + 0x20);
    word_t d1 = *(word_t *)(m + 0x28);
    sk_ctx_pair(0, 0, 0);
    sk_log_word(d0 >> 0xe);
    sk_log_word(d1 >> 0xe);
    word_t e1 = *(word_t *)(m + 0x38);
    sk_log_word(*(word_t *)(m + 0x30) >> 0xe);
    sk_log_word(e1 >> 0xe);
    if (*(long *)(m + 0x58) == 0) {
        FUN_00464ac4(); FUN_00229a3c();
    } else {
        FUN_00465584(); FUN_004650e4(); sk_java_dump_words6();
    }
    word_t b0 = *(word_t *)(m + 0x88);
    word_t b1 = *(word_t *)(m + 0x90);
    sk_log_word(*(char *)(m + 0x80));
    sk_log_word(b0 >> 0xe);
    sk_log_word(b1 >> 0xe);
}

/* FUN_00416dd0 @ 0x416dd0  (est. sk_java_dump_guard3)
 * Frame-guarded dump of sk_java_dump_method2 (FUN_004080b0 variant).
 * Confidence: medium */
static void sk_java_dump_guard3(void)
{
    word_t frame[9];
    FUN_004080b0();
    sk_java_dump_method2();
    sk_ctx_restore();
}

/* FUN_00416e10 @ 0x416e10  (est. sk_java_dump_guard4)
 * Frame-guarded dump of sk_java_dump_method2 (sk_ctx_save variant).
 * Confidence: medium */
static void sk_java_dump_guard4(void)
{
    word_t frame[9];
    sk_ctx_save(frame);
    sk_java_dump_method2();
    sk_ctx_restore();
}

/* FUN_00416e50 @ 0x416e50  (est. sk_java_descriptor_eq)
 * Compare two class-file descriptors (param_1 vs param_2, each a tagged pair)
 * for equality. Decodes each descriptor's kind tag (0/1/2), builds the
 * corresponding 0x88/0x98-byte record and runs the matching structural
 * compare (sk_java_method_eq for methods, sk_java_method_eq_full for fields).
 * Returns bool.
 * Confidence: medium */
static uint sk_java_descriptor_eq(cl4_pair_t param_1, cl4_pair_t param_2)
{
    word_t frameA[20];
    word_t frameB[20];
    word_t recA[0x13];
    word_t recB[0x13];
    word_t kind;
    word_t p2_lo = param_2.lo, p2_hi = param_2.hi;
    FUN_00356c6c();
    sk_memcpy(frameA, 0, 0x99);
    kind = FUN_00458b6c(frameA);
    if (kind == 0) {
        word_t base = FUN_00465aa0(frameA);
        recA[4] = *(word_t *)(base + 0x28);
        recA[3] = *(word_t *)(base + 0x20);
        recA[5] = *(word_t *)(base + 0x30);
        recA[0] = 0; recA[1] = 0; recA[2] = p2_lo; recA[6] = p2_hi;
        FUN_00464d00(frameB);
        kind = FUN_00458b6c(frameB);
        if (kind == 0) {
            word_t base2 = FUN_00465aa0(frameB);
            recB[4] = *(word_t *)(base2 + 0x28);
            recB[3] = *(word_t *)(base2 + 0x20);
            recB[5] = *(word_t *)(base2 + 0x30);
            recA[8] = recA[1];
            recA[7] = recA[0];
            recA[10] = recA[6];
            recA[9] = recA[2];
            recA[12] = recA[4];
            recA[11] = recA[3];
            recA[13] = recA[5];
            recB[0] = 0; recB[1] = 0; recB[2] = p2_lo;
            return FUN_00449034((word_t)&recA[7], (word_t)&recB[0]) & 1;
        }
    } else if (kind == 1) {
        word_t p = FUN_0001a1c8(frameA);
        sk_memcpy(&recB[0], p, 0x88);
        FUN_00464d00(frameB);
        kind = FUN_00458b6c(frameB);
        if (kind == 1) {
            FUN_0001a1c8(frameB);
            cl4_pair_t q = FUN_00463dec();
            sk_memcpy(q.lo, q.hi, 0x88);
            return sk_java_method_eq((word_t)&recB[0], (word_t)&recA[7]) & 1;
        }
    } else {
        word_t p = FUN_0001a1c8(frameA);
        sk_memcpy(&recB[0], p, 0x98);
        FUN_00464d00(frameB);
        kind = FUN_00458b6c(frameB);
        if (kind == 2) {
            FUN_0001a1c8(frameB);
            cl4_pair_t q = FUN_00463dec();
            sk_memcpy(q.lo, q.hi, 0x98);
            return sk_java_method_eq_full((word_t *)&recB[0], (word_t)&recA[7], 0, 0) & 1;
        }
    }
    return 0;
}

/* FUN_00416fbc @ 0x416fbc  (est. sk_java_dump_descriptor)
 * Dump a descriptor: decode its kind and print the corresponding record
 * (0x20-word via sk_java_dump_words, 0x88 via sk_java_dump_method,
 * 0x98 via sk_java_dump_method2).
 * Confidence: medium */
static void sk_java_dump_descriptor(cl4_pair_t param_1, word_t param_2)
{
    word_t frame[20];
    word_t kind;
    cl4_pair_t ref = FUN_004648ec();
    sk_memcpy(frame, ref.lo, 0x99);
    kind = FUN_00458b6c(frame);
    if (kind == 0) {
        word_t base = FUN_00465aa0(frame);
        word_t v = *(word_t *)(base + 0x30);
        FUN_004666b4();
        FUN_00465110();
        sk_java_dump_words();
        FUN_0046666c();
        sk_log_word(v >> 0xe);
    } else if (kind == 1) {
        FUN_0001a1c8(frame);
        ref = FUN_00463dec();
        sk_memcpy(ref.lo, ref.hi, 0x88);
        FUN_00464e1c();
        sk_log_word(0);
        FUN_00465110();
        sk_java_dump_method();
    } else {
        FUN_0001a1c8(frame);
        ref = FUN_00463dec();
        sk_memcpy(ref.lo, ref.hi, 0x98);
        FUN_00465b58();
        FUN_00465110();
        sk_java_dump_method2();
    }
}

/* FUN_0041708c @ 0x41708c  (est. sk_java_dump_descriptor2)
 * Frame-guarded descriptor dump: decode kind and dispatch to the matching
 * dump routine, printing the kind ordinal (0/1/2) first.
 * Confidence: medium */
static void sk_java_dump_descriptor2(cl4_pair_t param_1, word_t param_2)
{
    word_t frame[9];
    word_t buf[20];
    word_t kind;
    FUN_004080b0();
    FUN_00465258(buf);
    kind = FUN_00458b6c(buf);
    if (kind == 0) {
        FUN_00465aa0(buf);
        sk_log_word(0);
        sk_java_dump_words();
        FUN_00464eb0();
        FUN_004652a0();
    } else if (kind == 1) {
        word_t p = FUN_0001a1c8(buf);
        sk_memcpy(&buf[0], p, 0x88);
        sk_log_word(1);
        sk_java_dump_method();
    } else {
        word_t p = FUN_0001a1c8(buf);
        sk_memcpy(&buf[0], p, 0x98);
        sk_log_word(2);
        sk_java_dump_method2();
    }
    sk_ctx_restore();
}

/* FUN_004171a4 @ 0x4171a4  (est. sk_java_vtable_dispatch2)
 * vtable dispatch: enter frame (FUN_004653c0), invoke thunk in x19, restore.
 * Confidence: medium */
static void sk_java_vtable_dispatch2(void)
{
    word_t frame[9];
    FUN_004653c0();
    (*(word_t (*)(word_t *))((word_t *)0))(frame);
    sk_ctx_restore();
}

/* FUN_004171f8 @ 0x4171f8  (est. sk_java_kind_compare_small)
 * Compare two descriptor lists of a given kind (non-null, same tag count,
 * matching tail words). Returns 0/1.
 * Confidence: low */
static word_t sk_java_kind_compare_small(word_t *param_1, word_t param_2, word_t param_3, word_t param_4)
{
    word_t *a = (word_t *)0;   /* unaff_x20 */
    if (FUN_00464d0c(*param_1) != 0) return 0;
    FUN_00463094();
    if (0 == 0) {
        FUN_00465728();
        bool le = (bool)0 && param_4 <= 0;
        if ((bool)0 && 0 == param_4) {
            FUN_00464ad0();
            if (0 != 0) return 0;
        } else {
            FUN_002a0cf8();
            word_t t = FUN_00464a08();
            if ((0 & 1) == 0) return t;
            FUN_00465968();
            if (le) return 0;
        }
        FUN_004658a8();
        if ((1 && (FUN_004644ac(), 0 == 0)) &&
            (FUN_00465264(a[0x38]), 1)) {
            return 1;
        }
    }
    return 0;
}

/* FUN_004172ac @ 0x4172ac  (est. sk_java_dump_words6)
 * Dump six tagged words (three pairs) from the record at x19, shifted >>0xe.
 * Confidence: medium */
static void sk_java_dump_words6(void)
{
    word_t *rec = (word_t *)0;  /* unaff_x19 */
    FUN_00464a44();
    word_t w1 = rec[1];
    sk_log_word(rec[0] >> 0xe);
    sk_log_word(w1 >> 0xe);
    word_t w4 = rec[4];
    word_t w5 = rec[5];
    sk_ctx_pair(0, 0, 0);
    sk_log_word(w4 >> 0xe);
    sk_log_word(w5 >> 0xe);
    word_t w7 = rec[7];
    sk_log_word(rec[6] >> 0xe);
    sk_log_word(w7 >> 0xe);
}

/* FUN_0041731c @ 0x41731c  (est. sk_java_dump_guard5)
 * Dump the record at x20 and the two pairs at x19+0x10/+0x18/+0x30.
 * Confidence: medium */
static void sk_java_dump_guard5(void)
{
    word_t frame[9];
    FUN_004644e8();
    FUN_00465234(((word_t *)0)[0]);
    FUN_004652a0();
    sk_ctx_pair(frame, ((word_t *)0)[0x10], ((word_t *)0)[0x18]);
    FUN_0046660c();
    FUN_004652a0();
    FUN_00465234(((word_t *)0)[0x30]);
    FUN_00464eb0();
    sk_ctx_restore();
}

/* FUN_004173b0 @ 0x4173b0  (est. sk_java_noop_call)
 * Forward to FUN_00463f80 (a no-op/placeholder helper).
 * Confidence: low */
static void sk_java_noop_call(void)
{
    FUN_00463f80();
}

/* FUN_004173c8 @ 0x4173c8  (est. sk_java_retain_field20)
 * Retain the object at *thisp+0x20 then run FUN_00462d5c.
 * Confidence: medium */
static void sk_java_retain_field20(void)
{
    thunk_FUN_0036b270(((word_t *)0)[4]);
    FUN_00462d5c();
}

/* FUN_00417400 @ 0x417400  (est. sk_java_store_fields_3)
 * Release the token at *thisp+0x20, then overwrite the 4 words at
 * *thisp+0x18..+0x30 with the four register-carried values.
 * Confidence: medium */
static void sk_java_store_fields_3(void)
{
    FUN_00349a18();
    FUN_003a25d4(((word_t *)0)[4]);
    ((word_t *)0)[3] = 0;  /* x23 */
    ((word_t *)0)[4] = 0;  /* x22 */
    ((word_t *)0)[5] = 0;  /* x21 */
    ((word_t *)0)[6] = 0;  /* x19 */
}

/* FUN_00417454 @ 0x417454  (est. sk_java_sig_eq)
 * Structural equality of two type signatures (param_1 vs param_2): compares
 * the name char, the packed tag words (XOR >> 0xe == 0), and the parameter
 * list (FUN_00448fd0). Returns bool.
 * Confidence: medium */
static word_t sk_java_sig_eq(char *param_1, char *param_2)
{
    if (*param_1 != *param_2) return 0;
    if ((*(word_t *)(param_1 + 8) ^ *(word_t *)(param_2 + 8)) >> 0xe != 0) return 0;
    if ((*(word_t *)(param_1 + 0x10) ^ *(word_t *)(param_2 + 0x10)) >> 0xe != 0) return 0;
    long c1 = *(long *)(param_1 + 0x20);
    long c2 = *(long *)(param_2 + 0x20);
    if (c1 == 0) {
        if (c2 == 0) {
            FUN_003552a0();
            FUN_00458c88();
            return 1;
        }
    } else if (c2 != 0) {
        word_t m = FUN_00448fd0(*(word_t *)(param_1 + 0x18), c1, *(word_t *)(param_1 + 0x28),
                                *(word_t *)(param_1 + 0x30), *(word_t *)(param_2 + 0x18), c2,
                                *(word_t *)(param_2 + 0x28), *(word_t *)(param_2 + 0x30));
        if ((m & 1) == 0) return 0;
        return 1;
    }
    FUN_00458c88(param_1, 0);
    FUN_003552a0();
    FUN_00458c88();
    FUN_003a25d4(c1);
    FUN_003a25d4(c2);
    return 0;
}

/* FUN_00417540 @ 0x417540  (est. sk_java_dump_sig)
 * Dump a type signature: name char, two tag words, and the parameter list
 * (via FUN_0007c1c4 if non-empty).
 * Confidence: medium */
static void sk_java_dump_sig(void)
{
    char *s = (char *)0;   /* unaff_x19 */
    FUN_00464a44();
    word_t w1 = *(word_t *)(s + 8);
    word_t w2 = *(word_t *)(s + 0x10);
    sk_log_word(*(word_t *)s);
    sk_log_word(w1 >> 0xe);
    sk_log_word(w2 >> 0xe);
    long count = *(long *)(s + 0x20);
    if (count == 0) {
        FUN_00229a3c(0);
    } else {
        word_t a0 = *(word_t *)(s + 0x28);
        word_t a1 = *(word_t *)(s + 0x30);
        FUN_00229a3c(1);
        cl4_pair_t p = FUN_0007c1c4();
        sk_ctx_pair((word_t *)p.lo, p.hi, count);
        sk_log_word(a0 >> 0xe);
        sk_log_word(a1 >> 0xe);
    }
}

/* FUN_004175cc @ 0x4175cc  (est. sk_java_dump_guard6)
 * Frame-guarded dump of sk_java_dump_sig.
 * Confidence: medium */
static void sk_java_dump_guard6(void)
{
    word_t frame[9];
    FUN_004080b0();
    sk_java_dump_sig();
    sk_ctx_restore();
}

/* FUN_00417624 @ 0x417624  (est. sk_java_vtable_dispatch3)
 * vtable dispatch: enter frame (FUN_004653c0), invoke thunk in x19, restore.
 * Confidence: medium */
static void sk_java_vtable_dispatch3(void)
{
    word_t frame[9];
    FUN_004653c0();
    (*(word_t (*)(word_t *))((word_t *)0))(frame);
    sk_ctx_restore();
}

/* FUN_00417660 @ 0x417660  (est. sk_java_sig_eq_wrapper)
 * Wrapper that loads two 7-word signatures and compares them via
 * sk_java_sig_eq; returns bool.
 * Confidence: medium */
static uint sk_java_sig_eq_wrapper(word_t *a, word_t *b)
{
    word_t la[7], lb[7];
    for (int i = 0; i < 7; i++) { la[i] = a[i]; lb[i] = b[i]; }
    return sk_java_sig_eq((char *)&la[0], (char *)&lb[0]) & 1;
}

/* FUN_004176bc @ 0x4176bc  (est. sk_java_table_lookup_byte)
 * Table lookup: return the word at DAT_005a3958 + (param_1 & 0xff) * 8.
 * Confidence: high (structural) */
static word_t sk_java_table_lookup_byte(word_t param_1)
{
    return *(word_t *)(&java_char_method_table[0] + (param_1 & 0xff));  /* DAT_005a3958 */
}

/* FUN_004176ec @ 0x4176ec  (est. sk_java_cp_decode)
 * Decode a constant-pool entry (kind selector in x16): dispatch over the
 * entry kinds (utf8/name/type/class/... , string, member ref, etc.), reading
 * the payload via FUN_00458b14 and emitting the decoded representation.
 * Confidence: low */
static void sk_java_cp_decode(void)
{
    word_t buf[20];
    word_t out[22];
    FUN_00465258(buf);
    word_t kind = FUN_004660e0(buf);
    switch (kind) {
    default:
        FUN_00458b14(buf);
        FUN_00464e28();
        FUN_004589e8();
        break;
    case 1:
    {   /* utf8 / name: pack the byte payload into a tagged string */
        word_t *p = (word_t *)FUN_00458b14(buf);
        uint v = (uint)*p;
        int i;
        if (v < 0x80) i = v + 1;
        else if (v < 0x800) i = (v >> 6) + (v & 0x3f) * 0x100 + 0x81c1;
        else { FUN_00463bd4(); i = 0; if (0 == 0) i = 0 + 0x8181e1; }
        cl4_pair_t p2 = FUN_00255d4c(i);
        out[0] = p2.lo;
        if (p2.hi < 0) CL4_FATAL();
        FUN_00294cb4(out);
        FUN_0006b674();
        break;
    }
    case 2:
    {   /* string: emit the string's {lo,hi} reference */
        word_t *p = (word_t *)FUN_00458b14(buf);
        word_t lo = *p;
        word_t hi = p[1];
        FUN_00464e28();
        FUN_004589e8();
        FUN_004642d4();
        FUN_00461cb8(&lo);
        out[0] = hi;
        FUN_004642c0();
        FUN_00461cb8(out);
        break;
    }
    case 3: case 5: case 6: case 7: case 8: case 9: case 10: case 0xb: case 0xc:
        FUN_00458b14(buf);
        break;
    case 4:
    {   /* member/class ref: map the tag byte to a kind ordinal and emit */
        char *p = (char *)FUN_00458b14(buf);
        word_t v = 9;
        switch (*p) {
        case 1: v = 0x1c; break;
        case 2: v = 0xd; break;
        case 3: v = 0xb; break;
        case 4: v = 0xe; break;
        case 5: v = 10; break;
        case 0x13: v = 9; break;   /* group */
        default: v = 8; break;
        }
        cl4_pair_t p2 = FUN_00255d4c(v);
        out[0] = p2.lo;
        if (p2.hi < 0) CL4_FATAL();
        FUN_00294cb4(out);
        FUN_0006b674();
        break;
    }
    case 0xd:
    {   /* method ref: emit the name and descriptor pair */
        word_t *p = (word_t *)FUN_00458b14(buf);
        word_t name = *(word_t *)((char *)p + 0x18);
        word_t desc = *(word_t *)((char *)p + 0x38);
        FUN_00464e28();
        FUN_004589e8();
        FUN_00464804();
        FUN_00350968(&name);
        FUN_00461cb8();
        out[0] = desc;
        FUN_00350968(out);
        FUN_00461cb8(out);
        break;
    }
    case 0xe: case 0xf: case 0x10: case 0x11:
        break;
    }
    FUN_003507e0();
}

/* FUN_00417998 @ 0x417998  (est. sk_java_parse_verify)
 * Verify a parsed structure: if the top-level parse (sk_java_cp_decode)
 * succeeds, read the kind and dispatch; otherwise run the fallback
 * verification path (FUN_00352c80 / FUN_00417aa0). Returns a bool.
 * Confidence: low */
static uint sk_java_parse_verify(void)
{
    word_t buf[20];
    sk_java_cp_decode();
    if (0 == 0) {
        FUN_00465258(buf);
        int k = FUN_00458af8(buf);
        if (6 < k - 2U) return 0;
        switch (k) {
        case 3: case 4: return 0;
        default: FUN_00458b14(buf); break;
        }
    } else {
        FUN_00352c80();
        word_t ok = sk_java_bitfield_check();
        if ((ok & 1) == 0) {
            FUN_003a25d4(0);
            return 0;
        }
        FUN_00084180();
        FUN_002bd8f0();
        FUN_00466214();
        if (0) {
            FUN_00084180();
            word_t v = FUN_0029dac0();
            cl4_pair_t p = FUN_00084180();
            FUN_00456d90(p.lo, p.hi, v);
            FUN_00351a44();
            FUN_0036b118(0);
            FUN_003a25d4(0);
            return 0;
        }
        FUN_003a25d4(0);
    }
    return 1;
}

/* FUN_00417aa0 @ 0x417aa0  (est. sk_java_bitfield_check)
 * Check a packed bitfield/descriptor encoding: extract the tag bits from the
 * register-carried words (x19/x20), index a byte table, count leading zero
 * bits (LZCOUNT) and compare the decoded offset against a stride multiple.
 * Returns bool.
 * Confidence: low */
static bool sk_java_bitfield_check(void)
{
    word_t x19 = 0, x20 = 0;   /* register-carried packed words */
    word_t v;
    word_t r;
    FUN_003504d0();
    FUN_00350624(0xf);
    v = FUN_00167404();
    if (((x19 >> 0x3c) & 1) == 0) {
        v = v >> 0x10;
        if (((x19 >> 0x3d) & 1) == 0) {
            word_t base;
            if (((x20 >> 0x3c) & 1) == 0) { FUN_0007c1c4(); base = FUN_002a9ba8(); }
            else { base = (x19 & 0xfffffffffffffff) + 0x20; }
            (void)base;  /* byte table index v */
        }
        /* bVar2 from table[v] */
        uint lz;
        lz = (uint)(((uint)((word_t)((uint)0 << 0x18) ^ 0xffffffffu)));
        (void)lz;
        v = (v + 1) * 0x10000;
    } else {
        FUN_00350624(0);
        v = FUN_002a49a8();
    }
    r = x20 & 0xffffffffffff;
    if ((x19 & 0x2000000000000000) != 0) r = (x19 >> 0x38) & 0xf;
    return (v >> 0xe) == r * 4;
}

/* FUN_00417b60 @ 0x417b60  (est. sk_java_cp_build)
 * Build a constant-pool entry from a decoded kind (x16): allocate an object
 * (FUN_0036a9a0), store the payload (int/name/desc), and run the emit helpers.
 * Confidence: low */
static void sk_java_cp_build(void)
{
    word_t buf[20];
    word_t out[22];
    FUN_00465258(buf);
    word_t kind = FUN_004660e0(buf);
    switch (kind) {
    default:
        FUN_004666cc(buf);
        FUN_00466654();
        break;
    case 1:
    {   /* int/utf8 entry */
        word_t *p = (word_t *)FUN_00458b14(buf);
        word_t val = *p;
        word_t tag = FUN_004640dc();
        word_t obj = FUN_0036a9a0(tag, (word_t *)0);
        *(word_t *)(obj + 0x18) = 0;   /* uRam00000000004baeb8 */
        *(word_t *)(obj + 0x10) = 0;   /* _DAT_004baeb0 */
        *(word_t *)(obj + 0x20) = val;
        sk_java_cp_emit();
        FUN_0034bd90();
        FUN_0036b588();
        break;
    }
    case 2:
        FUN_004666cc(buf);
        FUN_00466654();
        FUN_0041449c(0);
        FUN_0036b118(0);
        FUN_0036b118(0);
        sk_java_cp_emit();
        FUN_0034bd90();
        FUN_0036b118(0);
        break;
    case 3: case 4: case 8: case 9: case 10: case 0xb: case 0xc:
        FUN_00458b14(buf);
        break;
    case 5: case 6: case 7:
    {   /* name/type ref: load the name/desc words */
        word_t n0, n1;
        if (kind == 5) { FUN_00465818(buf); FUN_00464a80(); }
        else if (kind == 6) { FUN_00465818(buf); FUN_00464a80(); }
        else { FUN_00465818(buf); FUN_004647d4(); }
        out[0] = 0xe300000000000000;
        FUN_00466654();
        FUN_000b4390();
        sk_printf_str(0, 0);
        FUN_004589f8();
        break;
    }
    case 0xd:
    {   /* method/field ref */
        word_t *p = (word_t *)FUN_00458b14(buf);
        word_t name = *(word_t *)((char *)p + 0x18);
        word_t desc = *(word_t *)((char *)p + 0x38);
        FUN_00466654();
        FUN_00464804();
        FUN_00350968(&name);
        FUN_00461cb8();
        out[0] = desc;
        FUN_00350968(out);
        FUN_00461cb8();
        break;
    }
    case 0xe: case 0xf: case 0x10: case 0x11:
        break;
    }
    FUN_0006b6f4();
}

/* FUN_00417d48 @ 0x417d48  (est. sk_java_cp_emit)
 * Emit a constant-pool entry into the vector at x19: for each of the count
 * payload words, extend the vector (FUN_0006a374 / FUN_0006b42c) and store
 * the {x24,x25} pair, then finalize with the printer hooks.
 * Confidence: low */
static void sk_java_cp_emit(void)
{
    cl4_pair_t hdr = FUN_00351e20();
    long count = *(long *)(hdr.lo + 0x10);
    word_t vec = FUN_000a6fe0();
    if (count != 0) {
        FUN_004651a8();
        word_t base = FUN_000863bc();
        word_t *cur = (word_t *)(vec + 0x20);
        do {
            FUN_001ebfb0((word_t)(cur), 0x10, 1, 0x6776f0, base);
            FUN_000778b4();
            word_t idx = *(word_t *)(0 + 0x10);
            if (*(word_t *)(0 + 0x18) >> 1 <= idx) {
                FUN_0006b42c();
                FUN_0006a374(FUN_0006b42c(), idx + 1, 1);
            }
            *(word_t *)(0 + 0x10) = idx + 1;
            word_t slot = 0 + idx * 0x10;
            *(word_t *)(slot + 0x20) = 0;   /* x24 */
            *(word_t *)(slot + 0x28) = 0;   /* x25 */
            count = count - 1;
            cur = cur + 2;
        } while (count != 0);
    }
    FUN_00463210();
    FUN_00462898();
    cl4_pair_t tail = FUN_00463fe8();
    FUN_001bc440(tail.lo, tail.hi, 0); /* unaff_x22 */
    FUN_000b43e8();
    FUN_0036b118((word_t)0);   /* release x19 */
    FUN_000b4390();
    sk_printf_str(0, 0);
    FUN_003a25d4(0);           /* release x22 */
    FUN_00463878();
    sk_printf_str(0, 0);
    FUN_00351d30(0x7b755c, 0xe300000000000000, hdr.hi);
}

/* FUN_00417e6c @ 0x417e6c  (est. sk_java_cp_wrapper)
 * Guarded wrapper: if param_1 is a large (negative-tagged) reference, copy
 * 0xb0 bytes from the payload and run the constant-pool build + finalize.
 * Confidence: low */
static void sk_java_cp_wrapper(word_t param_1)
{
    word_t buf[22];
    word_t frame[22];
    if ((long)param_1 < -0x7000000000000000) {
        sk_memcpy(frame, (word_t *)((param_1 & 0xfffffffffffffff) + 0x10), 0xb0);
        FUN_004589e8(frame, buf);
        sk_java_cp_build();
        FUN_00351a50();
        FUN_004589f8(frame);
    }
    FUN_0009461c();
}

/* FUN_00417efc @ 0x417efc  (est. sk_java_get_ref_a0)
 * Retain and return the reference stored at *thisp+0xa0 (masked to the
 * 52-bit object pointer).
 * Confidence: high (structural) */
static word_t sk_java_get_ref_a0(void)
{
    word_t v = *(word_t *)((word_t *)0 + 0xa0);
    FUN_0036b270(v & 0xfffffffffffffff);
    return v;
}

/* FUN_00417f28 @ 0x417f28  (est. sk_java_set_ref_a0)
 * Release the reference at *thisp+0xa0 and store param_1 there.
 * Confidence: high (structural) */
static void sk_java_set_ref_a0(word_t param_1)
{
    FUN_0036b118(*(word_t *)((word_t *)0 + 0xa0) & 0xfffffffffffffff);
    *(word_t *)((word_t *)0 + 0xa0) = param_1;
}

/* FUN_00417f70 @ 0x417f70  (est. sk_java_get_ref_c0)
 * Retain and return the reference stored at *thisp+0xc0 (masked).
 * Confidence: high (structural) */
static word_t sk_java_get_ref_c0(void)
{
    word_t v = *(word_t *)((word_t *)0 + 0xc0);
    FUN_0036b270(v & 0xfffffffffffffff);
    return v;
}

/* FUN_00417f9c @ 0x417f9c  (est. sk_java_set_ref_c0)
 * Release the reference at *thisp+0xc0 and store param_1 there.
 * Confidence: high (structural) */
static void sk_java_set_ref_c0(word_t param_1)
{
    FUN_0036b118(*(word_t *)((word_t *)0 + 0xc0) & 0xfffffffffffffff);
    *(word_t *)((word_t *)0 + 0xc0) = param_1;
}

/* FUN_00417fec @ 0x417fec  (est. sk_java_ctor_fields)
 * Object constructor: allocate a fresh record (FUN_0035199c), then fill its
 * 0x90-byte payload plus the kind byte and trailing words from the
 * register-carried constructor arguments.
 * Confidence: low */
static void sk_java_ctor_fields(void)
{
    cl4_pair_t p = FUN_0035199c();
    word_t *dst = (word_t *)0;   /* extraout_x8 */
    dst[0] = 0;                  /* in_x6 */
    dst[1] = 0;                  /* in_x7 */
    sk_memcpy(&dst[2], p.lo, 0x90);
    dst[0x14] = p.hi;
    dst[0x15] = 0;               /* x22 */
    dst[0x16] = 0;               /* x21 */
    *(char *)(&dst[0x17]) = 0;   /* in_w4 */
    dst[0x18] = 0;               /* in_x5 */
}

/* FUN_00418050 @ 0x418050  (est. sk_java_class_eq)
 * Structural equality of two class records (x19 vs x20): both non-null, same
 * kind flags (char at +0xb8), same name/descriptor pairs (+0xa0/+0xc0).
 * Returns bool.
 * Confidence: medium */
static word_t sk_java_class_eq(word_t *param_1)
{
    if (FUN_00464d0c(*param_1) == 0) {
        FUN_003504d0();
        FUN_00464d0c(*(word_t *)(0 + 8));
        if ((0 == 0) &&
            (sk_java_annot_eq_wrapper() & 1) != 0 &&
            (FUN_0041001c(((word_t *)0)[0xa0], ((word_t *)0)[0xa0]) & 1) != 0) {
            char c = *(char *)(0 + 0xb8);
            if (*(char *)(0 + 0xb8) == 1) {
                if (c == 1) goto ret_pair;
            } else {
                if (((c != 1) &&
                    (FUN_00464d0c(*(word_t *)(0 + 0xa8)) == 0)) &&
                    (FUN_00465264(*(word_t *)(0 + 0xb0)) == 0)) goto ret_pair;
            }
        }
    }
    return 0;
ret_pair:
    return FUN_0041001c(((word_t *)0)[0xc0], ((word_t *)0)[0xc0]);
}

/* FUN_00418110 @ 0x418110  (est. sk_java_dump_class)
 * Dump a class record: name pair, descriptor pair (+0x90/+0x98), kind flag
 * (+0xb8) and the interface/supertype pair (+0xa8/+0xb0).
 * Confidence: medium */
static void sk_java_dump_class(void)
{
    word_t *a = (word_t *)0;    /* unaff_x20 */
    word_t *c = (word_t *)0;    /* unaff_x21 */
    FUN_004656d4();
    word_t w1 = a[1];
    FUN_004647b4(a[0]);
    sk_log_word(0);
    sk_log_word(w1 >> 0xe);
    word_t d0 = *(word_t *)(c + 0x90);
    word_t d1 = *(word_t *)(c + 0x98);
    sk_java_dump_kind();
    sk_log_word(d0 >> 0xe);
    sk_log_word(d1 >> 0xe);
    FUN_00410414();
    if (*(char *)(c + 0xb8) == 1) {
        FUN_00464ac4(); FUN_00229a3c();
    } else {
        word_t s0 = *(word_t *)(c + 0xa8);
        word_t s1 = *(word_t *)(c + 0xb0);
        FUN_00465584();
        sk_log_word(s0 >> 0xe);
        sk_log_word(s1 >> 0xe);
    }
    FUN_00410414();
}

/* FUN_004181c0 @ 0x4181c0  (est. sk_java_dump_guard7)
 * Frame-guarded dump of sk_java_dump_class (FUN_004080b0 variant).
 * Confidence: medium */
static void sk_java_dump_guard7(void)
{
    word_t frame[9];
    FUN_004080b0();
    sk_java_dump_class();
    sk_ctx_restore();
}

/* FUN_00418200 @ 0x418200  (est. sk_java_dump_guard8)
 * Frame-guarded dump of sk_java_dump_class (sk_ctx_save variant).
 * Confidence: medium */
static void sk_java_dump_guard8(void)
{
    word_t frame[9];
    sk_ctx_save(frame);
    sk_java_dump_class();
    sk_ctx_restore();
}

/* FUN_00418240 @ 0x418240  (est. sk_java_to_string)
 * Build the toString() representation of a class record: emits
 * "  if <name> ... else <super>" style text (packed string words + the
 * resolved name/super refs) and returns the trailing tagged pair.
 * Confidence: low */
static cl4_pair_t sk_java_to_string(void)
{
    word_t buf[0x10];
    word_t name_buf[2];
    word_t super_buf[2];
    buf[0] = 0;
    buf[1] = 0xe000000000000000;
    FUN_002a4ab4(0x15);
    FUN_003a25d4(0xe000000000000000);
    super_buf[0] = 0x206669;                    /* "if " */
    super_buf[1] = 0xe300000000000000;
    name_buf[0] = 0;
    name_buf[1] = 0xe000000000000000;
    cl4_pair_t p = (cl4_pair_t){ .lo = (word_t)buf, .hi = 0 };
    /* FUN_00117cc4(&local_d0, thisp+0x10, 0x80) */
    sk_memcpy(buf, ((word_t *)0) + 0x10, 0x80);
    FUN_00463df8(p.lo, p.hi, 0x6840e0);
    FUN_00462728();
    FUN_00205844(buf, name_buf);
    sk_printf_str(name_buf[0], name_buf[1]);
    FUN_003a25d4(name_buf[1]);
    sk_printf_str(0x206e65687420, 0xe600000000000000);   /* " the n" */
    FUN_0044948c(((word_t *)0)[0xa0]);
    sk_printf_str(0, 0);
    FUN_003a25d4(0);
    sk_printf_str(0x2065736c6520, 0xe600000000000000);   /* " else " */
    FUN_0044948c(((word_t *)0)[0xc0]);
    sk_printf_str(0, 0);
    FUN_003a25d4(0);
    return (cl4_pair_t){ .lo = super_buf[0], .hi = super_buf[1] };
}

/* FUN_00418340 @ 0x418340  (est. sk_java_to_string_guard)
 * Guarded toString: allocate a 200-byte frame (FUN_00464140) and dump it via
 * sk_java_to_string.
 * Confidence: low */
static void sk_java_to_string_guard(void)
{
    cl4_pair_t p = FUN_00464140();
    sk_memcpy(p.lo, p.hi, 200);
    sk_java_to_string();
}

/* FUN_00418378 @ 0x418378  (est. sk_java_annot_eq)
 * Structural equality of two annotation/attribute records (the 0x80-byte
 * records at *thisp vs x19): decodes both via FUN_00458cb8/FUN_00458cd4,
 * compares kind tags, name/desc words and nested element lists
 * (FUN_00418d88 / FUN_0041a0dc). Returns bool.
 * Confidence: medium */
static word_t sk_java_annot_eq(void)
{
    word_t bufA[0x80 / 8 + 4];
    word_t bufB[0x80 / 8 + 4];
    word_t result = 0;
    FUN_0008e518();
    FUN_00356c6c();
    sk_memcpy(bufB, 0, 0x80);
    word_t kind = FUN_00458cb8(bufB);
    switch (kind) {
    default:
    {   /* 12-word payload record */
        word_t *a = (word_t *)FUN_00458cd4(bufB);
        word_t a0 = a[0], a1 = a[1], a2 = a[2], a3 = a[3];
        char   k4  = (char)a[4];
        word_t a5 = a[5], a6 = a[6], a7 = a[7], a8 = a[8];
        char   k9  = (char)a[9];
        word_t a10 = a[10], a11 = a[11];
        FUN_00464630();
        word_t k2 = FUN_00458cb8(bufA);
        word_t *b; word_t b0,b1,b2,b3,b5,b6,b7,b8,b10,b11; char bk4, bk9;
        if (k2 == 0) {
            b = (word_t *)FUN_00458cd4(bufA);
            b0 = b[0]; b1 = b[1]; b2 = b[2]; b3 = b[3];
            bk4 = (char)b[4];
            b5 = b[5]; b6 = b[6]; b7 = b[7]; b8 = b[8];
            bk9 = (char)b[9];
            b10 = b[10]; b11 = b[11];
            if (k4 == 0) {
                if (bk4 == 0 && ((a1 & 0xff) == 1 ? (b1 & 0xff) == 1 : ((b1 & 0xff) != 1 && a0 == b0)) &&
                    ((a2 ^ b2) >> 0xe == 0) && ((a3 ^ b3) >> 0xe == 0)) {
                    goto attr_eq;
                }
            } else if (k4 == 1) {
                if (bk4 == 1 && ((a1 & 0xff) == 1 ? (b1 & 0xff) == 1 : ((b1 & 0xff) != 1 && a0 == b0)) &&
                    ((a2 ^ b2) >> 0xe == 0) && ((a3 ^ b3) < 0x4000)) {
                    goto attr_eq;
                }
            } else if (bk4 == 2 &&
                       ((a0 == b0 && a1 == b1) || (FUN_002a0cf8(a0) & 1) != 0)) {
                goto attr_eq;
            }
        }
        break;
attr_eq:
        if (k9 == 1) {
            if (bk9 == 1) {
                if ((a10 ^ b10) >> 0xe == 0) {
                    if (((a11 ^ b11) >> 0xe == 0)) goto matched;
                }
            }
        } else if (bk9 != 1) {
            word_t j = (word_t)a6 & 0xff;
            if (k9 /* a[6] kind */ == 1) {
                if (j == 1) {
                    if (((a7 ^ b7) >> 0xe == 0) && ((a8 ^ b8) >> 0xe == 0)) goto matched;
                }
            } else if (j != 1 && a5 == b5) {
                if (((a7 ^ b7) >> 0xe == 0) && ((a8 ^ b8) >> 0xe == 0)) goto matched;
            }
        }
        break;
    }
    case 1:
    {   /* variant with different list stride */
        word_t *a = (word_t *)FUN_00458cd4(bufB);
        word_t a0 = a[0], a1 = a[1], a2 = a[2], a3 = a[3];
        char   k4  = (char)a[4];
        word_t a5 = a[5], a6 = a[6], a7 = a[7], a8 = a[8];
        char   k9  = (char)a[9];
        word_t a10 = a[10], a11 = a[11];
        FUN_00464630();
        word_t k2 = FUN_00458cb8(bufA);
        word_t *b; word_t b0,b1,b2,b3,b5,b6,b7,b8,b10,b11; char bk4, bk9;
        if (k2 == 1) {
            b = (word_t *)FUN_00458cd4(bufA);
            b0 = b[0]; b1 = b[1]; b2 = b[2]; b3 = b[3];
            bk4 = (char)b[4];
            b5 = b[5]; b6 = b[6]; b7 = b[7]; b8 = b[8];
            bk9 = (char)b[9];
            b10 = b[10]; b11 = b[11];
            if (k4 == 0) {
                if (bk4 == 0 && ((a1 & 0xff) == 1 ? (b1 & 0xff) == 1 : ((b1 & 0xff) != 1 && a0 == b0)) &&
                    ((a2 ^ b2) >> 0xe == 0) && ((a3 ^ b3) >> 0xe == 0)) goto attr_eq1;
            } else if (k4 == 1) {
                if (bk4 == 1 && ((a1 & 0xff) == 1 ? (b1 & 0xff) == 1 : ((b1 & 0xff) != 1 && a0 == b0)) &&
                    ((a2 ^ b2) >> 0xe == 0) && ((a3 ^ b3) < 0x4000)) goto attr_eq1;
            } else if (bk4 == 2 &&
                       ((a0 == b0 && a1 == b1) || (FUN_002a0cf8(a0, a1, b0, b1, 0) & 1) != 0)) {
                goto attr_eq1;
            }
        }
        break;
attr_eq1:
        if (k9 == 1) {
            if (bk9 == 1) {
                if ((a10 ^ b10) >> 0xe == 0) {
                    if (((a11 ^ b11) >> 0xe == 0)) goto matched;
                }
            }
        } else if (bk9 != 1) {
            word_t j = (word_t)a6 & 0xff;
            if (k9 == 1) {
                if (j == 1) {
                    if (((a7 ^ b7) >> 0xe == 0) && ((a8 ^ b8) >> 0xe == 0)) goto matched;
                }
            } else if (j != 1 && a5 == b5) {
                if (((a7 ^ b7) >> 0xe == 0) && ((a8 ^ b8) >> 0xe == 0)) goto matched;
            }
        }
        break;
    }
    case 2:
    {   /* 0x50-byte payload with a 3-word header */
        char *a = (char *)FUN_00458cd4(bufB);
        char  h0 = *a;
        word_t h1 = *(word_t *)(a + 8);
        word_t h2 = *(word_t *)(a + 0x10);
        word_t pl[10];
        sk_memcpy(pl, a + 0x18, 0x50);
        FUN_00464630();
        word_t k2 = FUN_00458cb8(bufA);
        if (k2 == 2) {
            char *b = (char *)FUN_00458cd4(bufA);
            if (h0 == *b &&
                ((*(word_t *)(b + 8) ^ h1) >> 0xe == 0) &&
                ((*(word_t *)(b + 0x10) ^ h2) >> 0xe == 0) &&
                (sk_java_field_sig_eq((long *)pl, (long *)(b + 0x18)) & 1) != 0) goto matched;
        }
        break;
    }
    case 3:
    {   /* 0x58-byte header + 4 tail words */
        word_t base = FUN_00458cd4(bufB);
        word_t pl[11];
        sk_memcpy(pl, base, 0x58);
        word_t t0 = *(word_t *)(base + 0x58);
        word_t t1 = *(word_t *)(base + 0x60);
        word_t t2 = *(word_t *)(base + 0x70);
        word_t t3 = *(word_t *)(base + 0x78);
        FUN_00464630();
        word_t k2 = FUN_00458cb8(bufA);
        if (k2 == 3) {
            word_t bbase = FUN_00458cd4(bufA);
            word_t b0 = *(word_t *)(bbase + 0x58);
            word_t b1 = *(word_t *)(bbase + 0x60);
            word_t b2 = *(word_t *)(bbase + 0x70);
            word_t b3 = *(word_t *)(bbase + 0x78);
            word_t plb[11];
            sk_memcpy(plb, bbase, 0x51);
            word_t m = FUN_0041a0dc((word_t)&pl[0], (word_t)&plb[0]);
            if ((m & 1) != 0 && ((b0 ^ t0) >> 0xe == 0) && ((b1 ^ t1) >> 0xe == 0)) {
                FUN_0007c1c4();
                word_t r = FUN_0041001c();
                if ((r & 1) != 0 && ((b2 ^ t2) >> 0xe == 0)) {
                    if ((b3 ^ t3) < 0x4000) goto matched;
                }
            }
        }
        break;
    }
    case 4:
        FUN_00464630();
        if (FUN_00458cb8(bufA) == 4) goto matched;
        break;
    case 5:
        FUN_00464630();
        if (FUN_00458cb8(bufA) == 5) goto matched;
        break;
    }
    goto out;
matched:
    result = 1;
out:
    return result;
}

/* FUN_00418978 @ 0x418978  (est. sk_java_dump_kind)
 * Dump a kind-tagged record: decode the kind (FUN_00458cb8/FUN_00458cd4) and
 * print the corresponding header words or nested structure.
 * Confidence: medium */
static void sk_java_dump_kind(void)
{
    word_t buf[0x10];
    word_t pl[12];
    cl4_pair_t ref = FUN_004648ec();
    sk_memcpy(buf, ref.lo, 0x80);
    word_t kind = FUN_00458cb8(buf);
    switch (kind) {
    default:
        word_t base = FUN_00458cd4(buf);
        sk_memcpy(pl, base, 0x60);
        sk_log_word(0);
        break;
    case 1:
        base = FUN_00458cd4(buf);
        sk_memcpy(pl, base, 0x60);
        sk_log_word(2);
        break;
    case 2:
    {   /* 3-word header + 0x50 payload */
        char *p = (char *)FUN_00458cd4(buf);
        char  h0 = *p;
        word_t h1 = *(word_t *)(p + 8);
        word_t h2 = *(word_t *)(p + 0x10);
        sk_memcpy(pl, p + 0x18, 0x50);
        sk_log_word(4);
        sk_log_word(h0);
        sk_log_word(h1 >> 0xe);
        sk_log_word(h2 >> 0xe);
        sk_java_dump_words8(0);
        return;
    }
    case 3:
    {   /* 0x58 header + 4 tail words */
        word_t base = FUN_00458cd4(buf);
        sk_memcpy(pl, base, 0x58);
        word_t t0 = *(word_t *)(base + 0x58);
        word_t t1 = *(word_t *)(base + 0x60);
        word_t t2 = *(word_t *)(base + 0x70);
        word_t t3 = *(word_t *)(base + 0x78);
        sk_log_word(5);
        FUN_0041a3ec();
        sk_log_word(t0 >> 0xe);
        sk_log_word(t1 >> 0xe);
        FUN_003507e0();
        FUN_00410414();
        sk_log_word(t2 >> 0xe);
        sk_log_word(t3 >> 0xe);
        return;
    }
    case 4:
        sk_log_word(1);
        return;
    case 5:
        sk_log_word(3);
        return;
    }
    sk_log_word(0);
    FUN_00412bb0();
}

/* FUN_00418b34 @ 0x418b34  (est. sk_java_dump_guard9)
 * Frame-guarded dump of sk_java_dump_kind.
 * Confidence: medium */
static void sk_java_dump_guard9(void)
{
    word_t frame[9];
    FUN_004080b0();
    sk_java_dump_kind();
    sk_ctx_restore();
}

/* FUN_00418bb4 @ 0x418bb4  (est. sk_java_ctor_simple)
 * Simple constructor: allocate a 0x80-byte record (FUN_00350a28) and store
 * the two register-carried references at +0x80 and +0x88.
 * Confidence: medium */
static void sk_java_ctor_simple(void)
{
    word_t v = FUN_00350a28();
    word_t *dst = (word_t *)0;   /* extraout_x8 */
    sk_memcpy(dst, v, 0x80);
    *(word_t *)(dst + 0x80) = 0;   /* x20 */
    *(word_t *)(dst + 0x88) = 0;   /* x19 */
}

/* FUN_00418bf4 @ 0x418bf4  (est. sk_java_annot_eq_wrapper)
 * Wrapper for annotation equality: requires the base compare
 * (sk_java_annot_eq) to succeed, plus the two references at x19+0x80 and
 * x20+0x88 to be non-null. Returns bool.
 * Confidence: medium */
static word_t sk_java_annot_eq_wrapper(void)
{
    FUN_00350c5c();
    word_t m = sk_java_annot_eq();
    if (((m & 1) == 0) || (FUN_00464d0c(((word_t *)0)[0x80]) != 0) ||
        (FUN_00465264(((word_t *)0)[0x88]) != 0)) {
        return 0;
    }
    return 1;
}

/* FUN_00418c48 @ 0x418c48  (est. sk_java_dump_attr)
 * Dump an annotation record: the kind header plus the reference pair at
 * *thisp+0x80/+0x88.
 * Confidence: medium */
static void sk_java_dump_attr(void)
{
    sk_java_dump_kind();
    word_t v = *(word_t *)((word_t *)0 + 0x88);
    FUN_004647b4(((word_t *)0)[0x80]);
    sk_log_word(0);
    sk_log_word(v >> 0xe);
}

/* FUN_00418c88 @ 0x418c88  (est. sk_java_dump_attr2)
 * Frame-guarded dump of the annotation kind plus the reference at *thisp+0x80.
 * Confidence: medium */
static void sk_java_dump_attr2(void)
{
    word_t frame[9];
    FUN_004080b0();
    sk_java_dump_kind();
    FUN_00465234(((word_t *)0)[0x80]);
    FUN_00464eb0();
    sk_ctx_restore();
}

/* FUN_00418cd4 @ 0x418cd4  (est. sk_java_dump_attr3)
 * Frame-guarded dump of sk_java_dump_attr (sk_ctx_save variant).
 * Confidence: medium */
static void sk_java_dump_attr3(void)
{
    word_t frame[9];
    sk_ctx_save(frame);
    sk_java_dump_attr();
    sk_ctx_restore();
}

/* FUN_00418d88 @ 0x418d88  (est. sk_java_field_sig_eq)
 * Structural equality of two field/type-signature records (param_1 vs
 * param_2): compares kind flags, the packed tag words (XOR >> 0xe == 0),
 * the size/offset pair (indices 4,5), and the type reference (indices 6-8).
 * Returns bool.
 * Confidence: medium */
static word_t sk_java_field_sig_eq(long *param_1, long *param_2)
{
    char k1 = (char)param_1[1];
    char k2 = (char)param_2[1];
    if (k1 == 1) {
        if (k2 != 1) return 0;
    } else if (k2 == 1 || param_1[0] != param_2[0]) {
        return 0;
    }
    if (((word_t)(param_2[2] ^ param_1[2])) >> 0xe != 0) return 0;
    if (((word_t)(param_2[3] ^ param_1[3])) >> 0xe != 0) return 0;
    char s1 = (char)param_1[5];
    char s2 = (char)param_2[5];
    bool le;
    if (s1 == 1) {
        if (s2 != 1) return 0;
        le = true;
    } else {
        le = s2 != 1 && (word_t)param_2[4] <= (word_t)param_1[4];
        if (s2 == 1 || param_1[4] != param_2[4]) return 0;
    }
    if (((word_t)(param_2[6] ^ param_1[6])) >> 0xe == 0) {
        if (((word_t)(param_2[7] ^ param_1[7])) >> 0xe != 0) return 0;
        FUN_00464d0c(param_1[8]);
        if ((0 == 0) && (FUN_00465264(*(word_t *)(0 + 0x48), 0), !le)) return 1;
        return 0;
    }
    return 0;
}

/* FUN_00418e84 @ 0x418e84  (est. sk_java_dump_words8)
 * Dump eight tagged words (four pairs) from the record at x19, printing each
 * pair's kind flag via FUN_00229a3c and the two payload words shifted >>0xe.
 * Confidence: medium */
static void sk_java_dump_words8(word_t pad)
{
    word_t *rec = (word_t *)0;  /* unaff_x19 */
    FUN_00464a44();
    word_t w2 = rec[2];
    word_t w3 = rec[3];
    if (*(char *)(rec + 1) == 1) {
        FUN_00229a3c(0);
    } else {
        FUN_00229a3c(1);
        sk_log_word(rec[0]);
    }
    sk_log_word(w2 >> 0xe);
    sk_log_word(w3 >> 0xe);
    word_t w6 = rec[6];
    word_t w7 = rec[7];
    if (*(char *)(rec + 5) == 1) {
        FUN_00229a3c(0);
    } else {
        FUN_00229a3c(1);
        sk_log_word(rec[4]);
    }
    sk_log_word(w6 >> 0xe);
    sk_log_word(w7 >> 0xe);
    word_t w9 = rec[9];
    sk_log_word((word_t)rec[8] >> 0xe);
    sk_log_word(w9 >> 0xe);
}

/* FUN_0041901c @ 0x41901c  (est. sk_java_dump_words9)
 * Dump a 3-word record (name char + two tag words) then the inner
 * sk_java_dump_words8 list.
 * Confidence: medium */
static void sk_java_dump_words9(void)
{
    char *r = (char *)0;   /* unaff_x20 */
    FUN_00464a38();
    word_t w1 = *(word_t *)(r + 8);
    word_t w2 = *(word_t *)(r + 0x10);
    sk_log_word(*(word_t *)r);
    sk_log_word(w1 >> 0xe);
    sk_log_word(w2 >> 0xe);
    sk_java_dump_words8(0);
}

/* FUN_00419078 @ 0x419078  (est. sk_java_dump_words10)
 * Dump a record: name char, one tag word, then the nested sk_java_dump_words8.
 * Confidence: medium */
static void sk_java_dump_words10(void)
{
    char *r = (char *)0;   /* unaff_x20 */
    word_t frame[9];
    FUN_004644e8();
    word_t w1 = *(word_t *)(r + 0x10);
    sk_log_word(*(word_t *)r);
    FUN_004652a0();
    sk_log_word(w1 >> 0xe);
    sk_java_dump_words8((word_t)frame);
    sk_ctx_restore();
}

/* FUN_004190e4 @ 0x4190e4  (est. sk_java_dump_wrapper2)
 * Frame-guarded dump of sk_java_dump_words9.
 * Confidence: medium */
static void sk_java_dump_wrapper2(void)
{
    word_t frame[9];
    sk_ctx_save(frame);
    sk_java_dump_words9();
    sk_ctx_restore();
}

/* FUN_0041913c @ 0x41913c  (est. sk_java_struct_eq_full)
 * Full structural equality of two 0x178-byte class/method structures
 * (the *thisp vs x19 records): decodes each side's kind, compares the packed
 * tag words (XOR < 0x4000 masked by DAT_005a1810), and the nested
 * parameter/field lists (FUN_00413024 / FUN_00413a0c / FUN_00411308).
 * Returns bool.
 * Confidence: low */
static void sk_java_struct_eq_full(void)
{
    word_t bufA[0x178 / 8 + 8];
    word_t bufB[0x178 / 8 + 8];
    word_t frameA[0xa0 / 8];
    word_t frameB[0xb0 / 8];
    word_t result = 0;
    FUN_0008e518();
    FUN_00356c6c();
    sk_memcpy(bufB, 0, 0x178);
    word_t kind = FUN_00458d04(bufB);
    word_t *a = (word_t *)FUN_00458d10(bufB);
    switch (kind) {
    default:
    {   /* 6-word header */
        word_t a0 = a[0], a1 = a[1], a2 = a[2], a3 = a[3], a4 = a[4], a5 = a[5];
        FUN_004645a4();
        word_t k2 = FUN_00458d04(bufA);
        if (k2 == 0) {
            word_t *b = (word_t *)FUN_00458d10(bufA);
            result = sk_java_sig_eq2((byte *)&a0, (byte *)&b[0]);
            goto out;
        }
        break;
    }
    case 1:
    {   /* field/member list */
        word_t fa[0xa0/8];
        word_t *b;
        word_t a20 = a[0x14], a21 = a[0x15], a22 = a[0x16], a23 = a[0x17];
        sk_memcpy(fa, a, 0xa0);
        word_t tb[0xb0/8];
        sk_memcpy(tb, a + 0x18, 0xb0);
        FUN_004645a4();
        word_t k2 = FUN_00458d04(bufA);
        if (k2 == 1) {
            word_t bbase = FUN_00458d10(bufA);
            word_t bb[0xb0/8];
            word_t bh[0x99/8];
            sk_memcpy(bb, bbase + 0xc0, 0xb0);
            sk_memcpy(bh, bbase, 0x99);
            word_t b5 = *(word_t *)(bbase + 0xa8);
            word_t b4 = *(word_t *)(bbase + 0xa0);
            word_t b7 = *(word_t *)(bbase + 0xb8);
            word_t b6 = *(word_t *)(bbase + 0xb0);
            word_t m = FUN_00413024((word_t)&fa[0], (word_t)&bh[0]);
            if ((m & 1) != 0 &&
                ((word_t)((a20 ^ b4) & 0xffffffffffffffff & (word_t)0) == 0) &&
                (FUN_00413a0c((word_t)&tb[0], (word_t)&bb[0]) & 1) != 0) {
                FUN_0007c1c4();
                word_t r = FUN_00411308();
                if ((r & 1) != 0) { result = 1; goto out; }
            }
        }
        break;
    }
    case 2:
    {   /* 0xa0 header + 2 tail words */
        word_t *b;
        word_t a20 = a[0x14], a21 = a[0x15];
        sk_memcpy(&bufB[0], a, 0xa0);
        FUN_004645a4();
        word_t k2 = FUN_00458d04(bufA);
        if (k2 == 2) {
            word_t bbase = FUN_00458d10(bufA);
            word_t b4 = *(word_t *)(bbase + 0xa0);
            word_t b5 = *(word_t *)(bbase + 0xa8);
            word_t bh[0x99/8];
            sk_memcpy(&bh[0], bbase, 0x99);
            word_t m = FUN_00413024((word_t)&bufB[0], (word_t)&bh[0]);
            result = 0;
            if ((b5 ^ a21) < 0x4000) result = (m & 1) & ((b4 ^ a20) < 0x4000);
            goto out;
        }
        break;
    }
    case 3:
    {   /* 2-word scalar pair */
        word_t c0 = a[0], c1 = a[1];
        FUN_004645a4();
        word_t k2 = FUN_00458d04(bufA);
        if (k2 == 3) {
            word_t *b = (word_t *)FUN_00458d10(bufA);
            bool le = c0 == b[0] && (word_t)b[1] <= c1;
            if (c0 == b[0] && c1 == b[1]) {
                FUN_00464ad0();
                if (0 == 0) { result = 1; goto out; }
            } else {
                FUN_000b4390();
                FUN_002a0cf8();
                if (((FUN_002a0cf8() & 1) != 0) && (!le)) {
                    FUN_00465890();
                    if (!le) { result = 1; goto out; }
                }
            }
        }
        break;
    }
    case 4:
    {   /* pair + recursion into case 3 */
        word_t c0 = a[0], c1 = a[1];
        FUN_004645a4();
        FUN_004652ac(bufA);
        if (0) {
            word_t *b = (word_t *)FUN_00458d10(bufA);
            bool le = c0 == b[0] && (word_t)b[1] <= c1;
            if (c0 == b[0] && c1 == b[1]) {
                FUN_00464ad0();
                if (0 == 0) { result = 1; goto out; }
            } else {
                FUN_000b4390();
                FUN_002a0cf8();
                if (((FUN_002a0cf8() & 1) != 0) && (!le)) {
                    FUN_00465890();
                    if (!le) { result = 1; goto out; }
                }
            }
        }
        break;
    }
    case 5:
    {   /* 4-word record with a char flag */
        word_t a0 = a[0], a1 = a[1], a2 = a[2], a3 = a[3];
        char   k1 = (char)a[1];
        FUN_004645a4();
        word_t k2 = FUN_00458d04(bufA);
        if (k2 == 5) {
            word_t *b = (word_t *)FUN_00458d10(bufA);
            char  bk1 = *(char *)(b + 1);
            word_t b2 = b[2], b3 = b[3];
            FUN_004111b0(a0, b[0]);
            word_t r = FUN_00464a08();
            if (((r & 1) != 0) && ((char)a1 == bk1) && ((b2 ^ a2) >> 0xe == 0) &&
                ((b3 ^ a3) >> 0xe == 0)) {
                FUN_0007c1c4();
                result = FUN_004111b0();
            }
            goto out;
        }
        break;
    }
    }
    goto out;
out:
    FUN_0008e500(result & 1, 0);
}

/* FUN_004196a0 @ 0x4196a0  (est. sk_java_set_field170)
 * Release the reference at *thisp+0x170 and store param_1 there.
 * Confidence: high (structural) */
static void sk_java_set_field170(word_t param_1)
{
    FUN_0036b118(((word_t *)0)[0x170]);
    *(word_t *)((word_t *)0 + 0x170) = param_1;
}

/* FUN_004196ec @ 0x4196ec  (est. sk_java_ctor_big)
 * Big constructor: allocate a 0xb0-byte record (FUN_00350980), init the
 * trailing region (+0xc0 via FUN_00465c00) and store references at +0xb0,
 * +0xb8 and +0x170.
 * Confidence: low */
static void sk_java_ctor_big(void)
{
    FUN_00351da8();
    word_t v = FUN_00350980();
    word_t *dst = (word_t *)0;   /* extraout_x8 */
    sk_memcpy(dst, v, 0xb0);
    *(word_t *)(dst + 0xb0) = 0;   /* x22 */
    *(word_t *)(dst + 0xb8) = 0;   /* x21 */
    FUN_00465c00(dst + 0xc0);
    *(word_t *)(dst + 0x170) = 0;  /* x19 */
}

/* FUN_00419784 @ 0x419784  (est. sk_java_class_eq2)
 * Structural equality of two 0xb0+ class records (x19 vs x20): kind tags,
 * member/name pairs, the +0xc0 region (FUN_00413a0c) and the +0x170
 * reference (FUN_00411308). Returns bool.
 * Confidence: medium */
static word_t sk_java_class_eq2(void)
{
    FUN_003504d0();
    word_t m = FUN_00413024();
    if ((m & 1) != 0 && (FUN_00464ad0() == 0) && (FUN_0046622c() == 0) &&
        (FUN_00464d0c(((word_t *)0)[0xb0]) == 0 &&
         FUN_00464d0c(((word_t *)0)[0xb8]) == 0) &&
        (FUN_00413a0c(((word_t *)0) + 0xc0, ((word_t *)0) + 0xc0) & 1) != 0) {
        return FUN_00411308(((word_t *)0)[0x170], ((word_t *)0)[0x170]);
    }
    return 0;
}

/* FUN_00419828 @ 0x419828  (est. sk_java_dump_class2)
 * Dump a class record: name pair (+0xa8), member region (+0xb0/+0xb8), and
 * the +0x168 reference.
 * Confidence: medium */
static void sk_java_dump_class2(void)
{
    word_t *a = (word_t *)0;   /* unaff_x20 */
    word_t *c = (word_t *)0;   /* unaff_x19 */
    FUN_00464a38();
    word_t w = *(word_t *)(a + 0xa8);
    FUN_0041360c();
    FUN_00466660();
    sk_log_word(w >> 0xe);
    word_t m1 = *(word_t *)(c + 0xb8);
    sk_log_word(*(word_t *)(c + 0xb0) >> 0xe);
    sk_log_word(m1 >> 0xe);
    word_t r = *(word_t *)(c + 0x168);
    FUN_0041360c();
    FUN_00466660();
    sk_log_word(r >> 0xe);
    FUN_0045811c();
}

/* FUN_004198c0 @ 0x4198c0  (est. sk_java_vtable_dispatch4)
 * vtable dispatch: enter frame (FUN_004648fc), invoke thunk in x19, restore.
 * Confidence: medium */
static void sk_java_vtable_dispatch4(void)
{
    word_t frame[9];
    FUN_004648fc();
    (*(word_t (*)(word_t *))((word_t *)0))(frame);
    sk_ctx_restore();
}

/* FUN_0041991c @ 0x41991c  (est. sk_java_vtable_dispatch5)
 * vtable dispatch: enter frame (FUN_004653c0), invoke thunk in x19, restore.
 * Confidence: medium */
static void sk_java_vtable_dispatch5(void)
{
    word_t frame[9];
    FUN_004653c0();
    (*(word_t (*)(word_t *))((word_t *)0))(frame);
    sk_ctx_restore();
}

/* FUN_0041995c @ 0x41995c  (est. sk_java_meth_kind)
 * Read the current method kind (FUN_00356c6c), resolve a name
 * (FUN_002ad78c), and clamp the register-carried kind to at most 3.
 * Confidence: low */
static word_t sk_java_meth_kind(void)
{
    word_t kind;
    FUN_00356c6c();
    FUN_002ad78c(0x67f870);
    FUN_00465240();
    if (2 < kind) kind = 3;
    return kind;
}

/* FUN_0041999c @ 0x41999c  (est. sk_java_methref_indexed_pair)
 * Return the tagged reference {name, 0xe200} for the Character method
 * indexed by (param_1 & 0xff) from the name table.
 * Confidence: medium */
static cl4_pair_t sk_java_methref_indexed_pair(word_t param_1)
{
    cl4_pair_t p;
    p.lo = *(word_t *)(&java_char_method_table[0] + (param_1 & 0xff));  /* DAT_005a3a50 */
    p.hi = 0xe200000000000000;
    return p;
}

/* FUN_004199b4 @ 0x4199b4  (est. sk_java_meth_kind_out)
 * Write the method kind (sk_java_meth_kind) into the caller's output byte
 * slot param_1.
 * Confidence: low */
static void sk_java_meth_kind_out(word_t *param_1, word_t *param_2)
{
    *param_1 = sk_java_meth_kind();
}

/* FUN_004199e8 @ 0x4199e8  (est. sk_java_methref_out)
 * Write the indexed method reference pair into the caller's 16-byte output
 * slot param_1 (the tag half fixed to 0xe200).
 * Confidence: medium */
static void sk_java_methref_out(word_t *param_1)
{
    cl4_pair_t p = sk_java_methref_indexed_pair(((word_t *)0)[0]);
    *param_1 = p.lo;
    param_1[1] = 0xe200000000000000;
}

/* FUN_00419a30 @ 0x419a30  (est. sk_java_meth_ordinal)
 * Read the current method ordinal (FUN_00356c6c), resolve a name
 * (FUN_002ad78c) and map the register-carried ordinal to 0/1/2.
 * Confidence: low */
static word_t sk_java_meth_ordinal(void)
{
    word_t ordinal;
    FUN_00356c6c();
    FUN_002ad78c(0x67f8d8);
    FUN_00465240();
    if (ordinal == 0) return 0;
    return (ordinal == 1) ? 1 : 2;
}

/* FUN_00419a78 @ 0x419a78  (est. sk_java_methref_bool_pair)
 * Return the tagged reference for a boolean selector: name "]" or "[^" with
 * tag 0xe100/0xe200 depending on whether param_1 == 1.
 * Confidence: medium */
static cl4_pair_t sk_java_methref_bool_pair(char param_1)
{
    cl4_pair_t p;
    p.lo = (param_1 == 1) ? 0x5e5b : 0x5b;
    p.hi = (param_1 == 1) ? 0xe200000000000000 : 0xe100000000000000;
    return p;
}

/* FUN_00419a9c @ 0x419a9c  (est. sk_java_meth_ordinal_out)
 * Write the method ordinal (sk_java_meth_ordinal) into the caller's output
 * byte slot param_1.
 * Confidence: low */
static void sk_java_meth_ordinal_out(word_t *param_1, word_t *param_2)
{
    *param_1 = sk_java_meth_ordinal();
}

/* FUN_00419ad0 @ 0x419ad0  (est. sk_java_methref_bool_out)
 * Write the boolean-selector method reference into the caller's 16-byte
 * output slot param_1.
 * Confidence: medium */
static void sk_java_methref_bool_out(cl4_pair_t *param_1)
{
    *param_1 = sk_java_methref_bool_pair((char)((word_t *)0)[0]);
}

/* FUN_00419b14 @ 0x419b14  (est. sk_java_sig_eq2)
 * Equality of two signature records (param_1 vs param_2): length compare,
 * then the two packed tag words and the parameter list (FUN_004111b0).
 * Returns bool.
 * Confidence: medium */
static word_t sk_java_sig_eq2(byte *param_1, byte *param_2)
{
    bool le = *param_2 <= *param_1;
    if (*param_1 != *param_2) return 0;
    FUN_00350c5c();
    word_t r = FUN_00464d0c(*(word_t *)(0 + 8));
    if (0 == 0) {
        r = FUN_00464d0c(((word_t *)0)[0x10]);
        if (0 == 0) {
            word_t m = FUN_004111b0(((word_t *)0)[0x18], ((word_t *)0)[0x18]);
            if (((m & 1) == 0) || (FUN_004637dc() != 0 || FUN_00465264(((word_t *)0)[0x28]) != 0)) {
                return 0;
            }
            return 1;
        }
    }
    return r;
}

/* FUN_00419ba8 @ 0x419ba8  (est. sk_java_dump_ref)
 * Dump a class-file reference record (the *thisp fields): the 4-word
 * descriptor, the name word, and the tag pair at +0x20/+0x28.
 * Confidence: medium */
static void sk_java_dump_ref(word_t param_1)
{
    word_t *r = (word_t *)0;   /* unaff_x20 */
    FUN_004491c4(param_1, r[0], r[1], r[2]);
    FUN_004582e8(param_1, r[3]);
    word_t w = *(word_t *)(r + 0x28);
    FUN_004647b4(r[4]);
    sk_log_word(0);
    sk_log_word(w >> 0xe);
}

/* FUN_00419bfc @ 0x419bfc  (est. sk_java_dump_ref_guard)
 * Frame-guarded dump of sk_java_dump_ref.
 * Confidence: medium */
static void sk_java_dump_ref_guard(void)
{
    word_t frame[9];
    word_t *r = (word_t *)0;   /* unaff_x20 */
    FUN_004080b0();
    FUN_004491c4(frame, r[0], r[1], r[2]);
    FUN_004582e8(frame, r[3]);
    FUN_00465234(r[4]);
    FUN_00464eb0();
    sk_ctx_restore();
}

/* FUN_00419c78 @ 0x419c78  (est. sk_java_is_marked)
 * Return whether the marker byte at *thisp is set to 1.
 * Confidence: high (structural) */
static bool sk_java_is_marked(void)
{
    return *((char *)0) == 1;
}

/* FUN_00419c88 @ 0x419c88  (est. sk_java_build_check)
 * Allocate a 0x178-byte build frame (FUN_00464140) and run the kind check
 * FUN_004652ac; returns the carry flag (0/1).
 * Confidence: low */
static word_t sk_java_build_check(void)
{
    word_t buf[0x178 / 8];
    cl4_pair_t p = FUN_00464140();
    sk_memcpy(p.lo, p.hi, 0x178);
    FUN_004652ac(buf);
    return 0;
}

/* FUN_00419cc4 @ 0x419cc4  (est. sk_java_struct_walk)
 * Walk a 0x178-byte structure: run the kind check; if it passes, load the
 * sub-record and retain the reference at +8; otherwise run the empty-branch
 * helper FUN_00356110.
 * Confidence: low */
static void sk_java_struct_walk(void)
{
    word_t bufA[0x178 / 8];
    word_t bufB[0x178 / 8];
    FUN_004654a8(bufB);
    FUN_004652ac(bufB);
    if (0) {
        word_t base = FUN_00458d10(bufB);
        sk_memcpy(bufA, 0, 0);
        word_t b = FUN_00458d10(bufA);
        thunk_FUN_0036b270(*(word_t *)(b + 8));
    } else {
        FUN_00356110();
    }
    FUN_0009461c();
}

/* FUN_00419d5c @ 0x419d5c  (est. sk_java_build_check2)
 * Like sk_java_build_check but returns the negated carry flag.
 * Confidence: low */
static bool sk_java_build_check2(void)
{
    word_t buf[0x178 / 8];
    cl4_pair_t p = FUN_00464140();
    sk_memcpy(p.lo, p.hi, 0x178);
    FUN_004652ac(buf);
    return !0;
}

/* FUN_00419d98 @ 0x419d98  (est. sk_java_struct_validate)
 * Recursive validator for a 0x178-byte class-file structure: checks the kind
 * (0x14/0x15 bounds via SoftwareBreakpoint), then recursively walks the
 * member and superclass sub-records (indices 2..4) with the shared
 * FUN_00412d5c emit helper.
 * Confidence: low */
static void sk_java_struct_validate(void)
{
    word_t bufA[0x178 / 8];
    word_t bufB[0x178 / 8];
    word_t bufC[0x178 / 8];
    word_t bufD[0x178 / 8];
    sk_memcpy(bufD, 0, 0);
    word_t kind = FUN_00458d04(bufD);
    word_t *a = (word_t *)FUN_00458d10(bufD);
    switch (kind) {
    default:
        break;
    case 1:
    {   /* validate the (lo,hi) span ordering */
        word_t lo = a[0x2c], hi = a[0x2d];
        word_t m0 = a[0x14], m1 = a[0x15];
        if ((m0 >> 0xe) <= (lo >> 0xe)) lo = m0;
        if ((m1 >> 0xe) <= (hi >> 0xe)) hi = m1;
        if (hi >> 0xe < lo >> 0xe) CL4_FATAL();
        break;
    }
    case 2:
        break;
    case 3: case 4:
        break;
    case 5:
    {   /* recurse into member + superclass sub-records */
        word_t m0 = a[2], m1 = a[3], count = a[4];
        word_t base = (word_t)a[0];
        word_t *memb = (word_t *)(base + 0x10);
        if (memb[0] != 0) {
            sk_memcpy(bufD, (word_t *)(base + 0x20), 0x178);
            FUN_00458d30(bufD, bufC);
            sk_java_struct_validate();
            FUN_00351a5c();
            FUN_00458d40(bufD);
            cl4_pair_t p = FUN_00350af4();
            FUN_00412d5c(p.lo, p.hi, m0, m1);
            FUN_0006b674();
        }
        word_t n = *(word_t *)(count + 0x10);
        if (n != 0) {
            sk_memcpy(bufC, (word_t *)(count + n * 0x178 + -0x158), 0x178);
            FUN_00458d30(bufC, bufB);
            sk_java_struct_validate();
            FUN_00351a5c();
            FUN_00458d40(bufC);
            cl4_pair_t p = FUN_00350af4();
            FUN_00412d5c(p.lo, p.hi, m0, m1);
            FUN_0006b674();
        }
        break;
    }
    }
    FUN_003507e0();
}

/* FUN_00419f24 @ 0x419f24  (est. sk_java_struct_grow)
 * Grow a vector of 0x178-byte class-file structures: scan the existing
 * entries (skipping the one at index uVar7 that matches), and when the entry
 * is found copy its 6 fields into the destination *x19, set the back-pointer
 * at +0x18, and return via the region-guard exit.
 * Confidence: low */
static void sk_java_struct_grow(void)
{
    word_t frame[0x178 / 8];
    word_t guard_token = FUN_0008e518();
    FUN_004649fc();
    word_t i = 0;
    word_t *vecp = (word_t *)0;   /* unaff_x20 (byte-address vector) */
    word_t vec = (word_t)vecp;
    word_t base = *(word_t *)(vec + 0x18);
    word_t count = *(word_t *)(base + 0x10);
    FUN_000776cc();
    for (;;) {
        word_t slot = base + 0x20 + i * 0x178;
        for (;;) {
            if (count == i) {
                /* entry found: copy 6 fields + back-pointer */
                ((word_t *)0)[0] = ((word_t *)0)[0];         /* *x21 -> *x19 */
                ((word_t *)0)[2] = ((word_t *)0)[2];
                ((word_t *)0)[1] = ((word_t *)0)[1];
                *(long *)((word_t *)0 + 0x18) = (long)vec;
                ((word_t *)0)[4] = ((word_t *)0)[4];
                ((word_t *)0)[5] = ((word_t *)0)[5];
                FUN_0008e500(guard_token);
                return;
            }
            bool stop = i == count;
            if (count <= i) CL4_FATAL();
            sk_memcpy(frame, slot, 0x178);
            FUN_004652ac(frame);
            if (!stop) break;
            slot = slot + 0x178;
            i = i + 1;
        }
        FUN_00465788();
        FUN_00458d30();
        word_t ok = FUN_003a261c(vec);
        word_t vec2 = vec;
        if ((ok & 1) == 0) {
            FUN_000dbbe0(ok, *(long *)(vec + 0x10) + 1);
            FUN_00456238();
        }
        word_t n = *(word_t *)(vec2 + 0x10);
        if (*(word_t *)(vec2 + 0x18) >> 1 <= n) {
            FUN_0006b42c();
            FUN_00464000();
            FUN_00456238();
        }
        i = i + 1;
        *(word_t *)(vec2 + 0x10) = n + 1;
        sk_memcpy((word_t *)(vec2 + n * 0x178 + 0x20), frame, 0x178);
        vec = vec2;
    }
}

/* FUN_0041a044 @ 0x41a044  (est. sk_java_release_pair)
 * Run the release pair FUN_004637b4 + FUN_0045908c.
 * Confidence: low */
static void sk_java_release_pair(void)
{
    FUN_004637b4();
    FUN_0045908c();
}
