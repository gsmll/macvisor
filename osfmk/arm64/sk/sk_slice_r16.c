/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel, GL1,
 * arm64e, image base 0) — the cL4 microkernel. Ground truth: Ghidra FUN_ names +
 * addresses in cl4_kernel.raw. Version "cL4 microkernel (cL4 (679.100.61))".
 * All names are estimates unless string/header-matched.
 * Slice 0x451a10-0x458d40 (SKR16): a Unicode/string-encoding library layer —
 * Unicode block/category name tables (0x451a64, 0x451f24, 0x45399c), character
 * /codepoint class comparison and string scanning (0x456d90-0x457650), generic
 * growable array containers and their move/copy/release helpers (0x455de4-
 * 0x456c3c, 0x4580b4-0x458780), a base-N integer parser (0x457bec), and small
 * type-helper/refcount shims (0x4588cc-0x458d40). */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "sk_internal.h"

/* ---- Out-of-range cL4 helpers referenced by this region (FUN_ in comment).
 * Declared with unspecified-argument prototype (matching slice conventions);
 * their bodies are reconstructed by the range worker that owns them. ---- */
extern unsigned long sk_x_001e9c78();  /* FUN_001e9c78 */
extern unsigned long sk_x_0022d2f4();  /* FUN_0022d2f4 */
extern unsigned long sk_x_0029ba8();   /* FUN_002a9ba8 */
extern unsigned long sk_x_002b141c();  /* FUN_002b141c */
extern unsigned long sk_x_002b5ba0();  /* FUN_002b5ba0 */
extern unsigned long sk_x_002298d4();  /* FUN_002298d4 (release/mark) */
extern unsigned long sk_x_0022995c();  /* FUN_0022995c */
extern unsigned long sk_x_00229a3c();  /* FUN_00229a3c */
extern unsigned long sk_x_00117cc4();  /* FUN_00117cc4 (memcpy) */
extern unsigned long sk_x_00117d14();  /* FUN_00117d14 */
extern unsigned long sk_x_001b9084();  /* FUN_001b9084 (emit token) */
extern unsigned long sk_x_002ad95c();  /* FUN_002ad95c */
extern unsigned long sk_x_002ad78c();  /* FUN_002ad78c */
extern unsigned long sk_x_0035b67c();  /* FUN_0035b67c (memmove) */
extern unsigned long sk_x_0035bc70();  /* FUN_0035bc70 */
extern unsigned long sk_x_0036a940();  /* FUN_0036a940 (alloc) */
extern unsigned long sk_x_0036b118();  /* FUN_0036b118 (release) */
extern unsigned long sk_x_0036b270();  /* FUN_0036b270 (retain) */
extern unsigned long sk_x_003a25d4();  /* FUN_003a25d4 (release) */
extern unsigned long sk_x_003a261c();  /* FUN_003a261c */
extern unsigned long sk_x_00356c6c();  /* FUN_00356c6c */
extern unsigned long sk_x_003504d0();  /* FUN_003504d0 */
extern unsigned long sk_x_00355968();  /* FUN_00355968 */
extern unsigned long sk_x_003593c0();  /* FUN_003593c0 */
extern unsigned long sk_x_00349a18();  /* FUN_00349a18 */
extern unsigned long sk_x_0035199c();  /* FUN_0035199c */
extern unsigned long sk_x_00350980();  /* FUN_00350980 */
extern unsigned long sk_x_0035098c();  /* FUN_0035098c */
extern unsigned long sk_x_003509c8();  /* FUN_003509c8 */
extern unsigned long sk_x_00350a04();  /* FUN_00350a04 */
extern unsigned long sk_x_00350530();  /* FUN_00350530 */
extern unsigned long sk_x_00350560();  /* FUN_00350560 */
extern unsigned long sk_x_00350618();  /* FUN_00350618 */
extern unsigned long sk_x_003507bc();  /* FUN_003507bc */
extern unsigned long sk_x_003514e8();  /* FUN_003514e8 */
extern unsigned long sk_x_00351db4();  /* FUN_00351db4 */
extern unsigned long sk_x_00351e3c();  /* FUN_00351e3c */
extern unsigned long sk_x_00352840();  /* FUN_00352840 */
extern unsigned long sk_x_00354828();  /* FUN_00354828 */
extern unsigned long sk_x_00310c44();  /* FUN_00310c44 */
extern unsigned long sk_x_0031b760();  /* FUN_0031b760 */
extern unsigned long sk_x_0031b778();  /* FUN_0031b778 */
extern unsigned long sk_x_0034b05c();  /* FUN_0034b05c */
extern unsigned long sk_x_000026e8();  /* FUN_000026e8 */
extern unsigned long sk_x_0006a4c0();  /* FUN_0006a4c0 */extern unsigned long sk_x_00310d68();  /* FUN_00310d68 */
extern unsigned long sk_x_00310d98();  /* FUN_00310d98 */
extern unsigned long sk_x_003625e4();  /* FUN_003625e4 */
extern unsigned long sk_x_00371950();  /* FUN_00371950 */
extern unsigned long sk_x_00377824();  /* FUN_00377824 */
extern unsigned long sk_x_00377bec();  /* FUN_00377bec */
extern unsigned long sk_x_00002534();  /* FUN_00002534 */
extern unsigned long sk_x_00002818();  /* FUN_00002818 */
extern unsigned long sk_x_00002874();  /* FUN_00002874 */
extern unsigned long sk_x_00027754();  /* FUN_00027754 */
extern unsigned long sk_x_00027788();  /* FUN_00027788 */
extern unsigned long sk_x_000262fc();  /* FUN_000262fc */
extern unsigned long sk_x_0006a4c0();  /* FUN_0006a4c0 */
extern unsigned long sk_x_0006b3f4();  /* FUN_0006b3f4 */
extern unsigned long sk_x_0006b42c();  /* FUN_0006b42c */
extern unsigned long sk_x_0006b6e0();  /* FUN_0006b6e0 */
extern unsigned long sk_x_00069970();  /* FUN_00069970 */
extern unsigned long sk_x_000699a4();  /* FUN_000699a4 */
extern unsigned long sk_x_000699d8();  /* FUN_000699d8 */
extern unsigned long sk_x_00069770();  /* FUN_00069770 */
extern unsigned long sk_x_0007c028();  /* FUN_0007c028 */
extern unsigned long sk_x_0007c1a4();  /* FUN_0007c1a4 */
extern unsigned long sk_x_0007c1c4();  /* FUN_0007c1c4 */
extern unsigned long sk_x_00077024();  /* FUN_00077024 */
extern unsigned long sk_x_000776cc();  /* FUN_000776cc */
extern unsigned long sk_x_00084174();  /* FUN_00084174 */
extern unsigned long sk_x_00084220();  /* FUN_00084220 */
extern unsigned long sk_x_00084234();  /* FUN_00084234 */
extern unsigned long sk_x_0008e518();  /* FUN_0008e518 */
extern unsigned long sk_x_0008e500();  /* FUN_0008e500 */
extern unsigned long sk_x_000aa4ec();  /* FUN_000aa4ec */
extern unsigned long sk_x_000a6f88();  /* FUN_000a6f88 */
extern unsigned long sk_x_000a68c4();  /* FUN_000a68c4 */
extern unsigned long sk_x_000a68f4();  /* FUN_000a68f4 */
extern unsigned long sk_x_000b43d0();  /* FUN_000b43d0 */
extern unsigned long sk_x_000b43f4();  /* FUN_000b43f4 */
extern unsigned long sk_x_001afa84();  /* FUN_001afa84 (noreturn) */
extern unsigned long sk_x_001a29a0();  /* FUN_001a29a0 */
extern unsigned long sk_x_00100efc();  /* FUN_00100efc */
extern unsigned long sk_x_002a4468();  /* FUN_002a4468 */
extern unsigned long sk_x_002b8444();  /* FUN_002b8444 */
extern unsigned long sk_x_00200b38();  /* FUN_00200b38 */
extern unsigned long sk_x_00200bd0();  /* FUN_00200bd0 */
extern unsigned long sk_x_00200bf4();  /* FUN_00200bf4 */
extern unsigned long sk_x_0001d648();  /* FUN_0001d648 */
extern unsigned long sk_x_0001d4a0();  /* FUN_0001d4a0 */
extern unsigned long sk_x_0001da84();  /* FUN_0001da84 */
extern unsigned long sk_x_00465240();  /* FUN_00465240 */
extern unsigned long sk_x_004652d4();  /* FUN_004652d4 */
extern unsigned long sk_x_00465428();  /* FUN_00465428 */
extern unsigned long sk_x_00464000();  /* FUN_00464000 */
extern unsigned long sk_x_004661b8();  /* FUN_004661b8 */
extern unsigned long sk_x_004662b8();  /* FUN_004662b8 */
extern unsigned long sk_x_004663e0();  /* FUN_004663e0 */
extern unsigned long sk_x_0046647c();  /* FUN_0046647c */
extern unsigned long sk_x_004665bc();  /* FUN_004665bc */
extern unsigned long sk_x_004665e8();  /* FUN_004665e8 */
extern unsigned long sk_x_00465ed4();  /* FUN_00465ed4 */
extern unsigned long sk_x_00410414();  /* FUN_00410414 */
extern unsigned long sk_x_0041360c();  /* FUN_0041360c */
extern unsigned long sk_x_00415570();  /* FUN_00415570 */
extern unsigned long sk_x_0041577c();  /* FUN_0041577c */
extern unsigned long sk_x_00415aa4();  /* FUN_00415aa4 */
extern unsigned long sk_x_0041b3d4();  /* FUN_0041b3d4 */
extern unsigned long sk_x_0042d720();  /* FUN_0042d720 */
extern unsigned long sk_x_00447144();  /* FUN_00447144 */
extern unsigned long sk_x_0044f298();  /* FUN_0044f298 */
extern unsigned long sk_x_00450848();  /* FUN_00450848 */
extern unsigned long sk_x_00455990();  /* FUN_00455990 */
extern unsigned long sk_x_0045636c();  /* FUN_0045636c */
extern unsigned long sk_x_00456420();  /* FUN_00456420 */
extern unsigned long sk_x_000126e8();  /* FUN_000126e8 */extern unsigned long sk_x_0045a6f4();  /* FUN_0045a6f4 */
extern unsigned long sk_x_0045a980();  /* FUN_0045a980 */
extern unsigned long sk_x_0045eb6c();  /* FUN_0045eb6c */
extern unsigned long sk_x_0045eb38();  /* FUN_0045eb38 */
extern unsigned long sk_x_0045c2a8();  /* FUN_0045c2a8 */
extern unsigned long sk_x_0045c258();  /* FUN_0045c258 */
extern unsigned long sk_x_0045df90();  /* FUN_0045df90 */
extern unsigned long sk_x_0045df3c();  /* FUN_0045df3c */
extern unsigned long sk_x_0045b824();  /* FUN_0045b824 */
extern unsigned long sk_x_0045b7f4();  /* FUN_0045b7f4 */
extern unsigned long sk_x_0045bbb4();  /* FUN_0045bbb4 */
extern unsigned long sk_x_0045bb84();  /* FUN_0045bb84 */
extern unsigned long sk_x_0045be8c();  /* FUN_0045be8c */
extern unsigned long sk_x_0045c61c();  /* FUN_0045c61c */
extern unsigned long sk_x_0045d2e4();  /* FUN_0045d2e4 */
extern unsigned long sk_x_0045d028();  /* FUN_0045d028 */
extern unsigned long sk_x_00458eec();  /* FUN_00458eec */
extern unsigned long sk_x_00458f88();  /* FUN_00458f88 */
extern unsigned long sk_x_00460ddc();  /* FUN_00460ddc */
extern unsigned long sk_x_00461d68();  /* FUN_00461d68 */
extern unsigned long sk_x_00462ee8();  /* FUN_00462ee8 */
extern unsigned long sk_x_0045d2e4();  /* FUN_0045d2e4 */

/* Software breakpoint for guard-rail traps (Ghidra SoftwareBreakpoint(1, addr)). */
extern void sk_sw_breakpoint(unsigned long, unsigned long); /* brk #imm */

/* ===================================================================== *
 * 0x451a10-0x451f24 — Unicode general-category / block-name table layer.
 * ===================================================================== */

/* FUN_00451a10 @ 0x00451a10   (est. sk_unicode_cat_count)
 * Ghidra: ulong FUN_00451a10(void)
 * Returns the number of Unicode general categories (0x26 = 38). Reaches the
 * count via a helper chain; clamps an uninitialised x20 counter to 0x26.
 * Confidence: low (register-fragment heavy)
 */
unsigned long sk_unicode_cat_count(void)
{
    unsigned long n;

    sk_x_00356c6c();
    sk_x_002ad95c(0x680d80);
    sk_x_00465240();
    if (0x25 < n) {
        n = 0x26;
    }
    return n;
}

/* FUN_00451a64 @ 0x00451a64   (est. sk_unicode_cat_name)
 * Ghidra: undefined1 [16] FUN_00451a64(undefined1 param_1)
 * Returns the two-letter Unicode general-category name for the category index
 * param_1 (e.g. "Cc", "Cf", "Cn", "Co", "Cs", "L", "Ll", "Lu", "Mc", "Nd",
 * "Pc", "So", "Zl", ...). The result is a 16-byte pair: the low 8 bytes hold
 * the big-endian category letters, the high 8 bytes carry the class tag
 * (0xe1 for single-letter majors, 0xe2 for two-letter). Index 0 is the
 * default/unknown ("\0\0") entry.
 * Confidence: high (pattern matches the standard Unicode category table)
 */
cl4_result_t sk_unicode_cat_name(unsigned int idx)
{
    uint64_t lo, hi;

    lo = 0x6343; hi = 0xe200000000000000;
    switch (idx) {
    case 1:  lo = 0x6343; hi = 0xe200000000000000; break; /* Cc */
    case 2:  lo = 0x6643; hi = 0xe200000000000000; break; /* Cf */
    case 3:  lo = 0x6e43; hi = 0xe200000000000000; break; /* Cn */
    case 4:  lo = 0x6f43; hi = 0xe200000000000000; break; /* Co */
    case 5:  lo = 0x7343; hi = 0xe200000000000000; break; /* Cs */
    case 6:  lo = 0x4c;   hi = 0xe100000000000000; break; /* L  */
    case 7:  lo = 0x634c; hi = 0xe200000000000000; break; /* Lc */
    case 8:  lo = 0x6c4c; hi = 0xe200000000000000; break; /* Ll */
    case 9:  lo = 0x6d4c; hi = 0xe200000000000000; break; /* Lm */
    case 10: lo = 0x6f4c; hi = 0xe200000000000000; break; /* Lo */
    case 11: lo = 0x744c; hi = 0xe200000000000000; break; /* Lt */
    case 12: lo = 0x754c; hi = 0xe200000000000000; break; /* Lu */
    case 13: lo = 0x4d;   hi = 0xe100000000000000; break; /* M  */
    case 14: lo = 0x634d; hi = 0xe200000000000000; break; /* Mc */
    case 15: lo = 0x654d; hi = 0xe200000000000000; break; /* Me */
    case 16: lo = 0x6e4d; hi = 0xe200000000000000; break; /* Mn */
    case 17: lo = 0x4e;   hi = 0xe100000000000000; break; /* N  */
    case 18: lo = 0x644e; hi = 0xe200000000000000; break; /* Nd */
    case 19: lo = 0x6c4e; hi = 0xe200000000000000; break; /* Nl */
    case 20: lo = 0x6f4e; hi = 0xe200000000000000; break; /* No */
    case 21: lo = 0x50;   hi = 0xe100000000000000; break; /* P  */
    case 22: lo = 0x6350; hi = 0xe200000000000000; break; /* Pc */
    case 23: lo = 0x6450; hi = 0xe200000000000000; break; /* Pd */
    case 24: lo = 0x6550; hi = 0xe200000000000000; break; /* Pe */
    case 25: lo = 0x6650; hi = 0xe200000000000000; break; /* Pf */
    case 26: lo = 0x6950; hi = 0xe200000000000000; break; /* Pi */
    case 27: lo = 0x6f50; hi = 0xe200000000000000; break; /* Po */
    case 28: lo = 0x7350; hi = 0xe200000000000000; break; /* Ps */
    case 29: lo = 0x53;   hi = 0xe100000000000000; break; /* S  */
    case 30: lo = 0x6353; hi = 0xe200000000000000; break; /* Sc */
    case 31: lo = 0x6b53; hi = 0xe200000000000000; break; /* Sk */
    case 32: lo = 0x6d53; hi = 0xe200000000000000; break; /* Sm */
    case 33: lo = 0x6f53; hi = 0xe200000000000000; break; /* So */
    case 34: lo = 0x5a;   hi = 0xe100000000000000; break; /* Z  */
    case 35: lo = 0x6c5a; hi = 0xe200000000000000; break; /* Zl */
    case 36: lo = 0x705a; hi = 0xe200000000000000; break; /* Zp */
    case 37: lo = 0x735a; hi = 0xe200000000000000; break; /* Zs */
    }
    return (cl4_result_t){ .lo = lo, .hi = hi };
}

/* FUN_00451dd0 @ 0x00451dd0   (est. sk_unicode_script_count)
 * Ghidra: ulong FUN_00451dd0(void)
 * Returns the number of Unicode scripts/blocks (0x43 = 67). Same helper shape
 * as sk_unicode_cat_count with a different data address.
 * Confidence: low (register-fragment heavy)
 */
unsigned long sk_unicode_script_count(void)
{
    unsigned long n;

    sk_x_00356c6c();
    sk_x_002ad95c(0x681178);
    sk_x_00465240();
    if (0x42 < n) {
        n = 0x43;
    }
    return n;
}

/* FUN_00451d04 @ 0x00451d04   (est. sk_cat_table_store)
 * Ghidra: void FUN_00451d04(undefined1 (*param_1) [16])
 * Stores the category name for the current category index (x20) into the
 * 16-byte out buffer at param_1.
 * Confidence: low (uses caller-register x20)
 */
void sk_cat_table_store(cl4_result_t *out)
{
    cl4_result_t v;
    v = sk_unicode_cat_name(0);           /* index comes from x20 (omitted) */
    *out = v;
}

/* FUN_00451d30 / d34 / d60 / d64 / d90 / d94 — table-registration wrappers.
 * Ghidra: void FUN_00451dXX(void) / (undefined8 param_1)
 * Register the Unicode category name table with a shared table builder
 * (FUN_00415570 / FUN_0041577c / FUN_00415aa4). Pairs differ only in whether
 * the table carries per-row data. */
void sk_cat_reg_1(void) { sk_x_00415570(0, sk_unicode_cat_name); }
void sk_cat_reg_2(void) { sk_x_00415570(0, sk_unicode_cat_name); }
void sk_cat_reg_3(unsigned long a) { sk_x_0041577c(a, 0, sk_unicode_cat_name); }
void sk_cat_reg_4(unsigned long a) { sk_x_0041577c(a, 0, sk_unicode_cat_name); }
void sk_cat_reg_5(unsigned long a) { sk_x_00415aa4(a, 0, sk_unicode_cat_name); }
void sk_cat_reg_6(unsigned long a) { sk_x_00415aa4(a, 0, sk_unicode_cat_name); }

/* FUN_00451e24 @ 0x00451e24   (est. sk_script_count_store)
 * Ghidra: void FUN_00451e24(undefined1 *param_1,undefined8 *param_2)
 * Stores the low byte of sk_unicode_script_count (a byte-alias store).
 * Confidence: medium
 */
void sk_script_count_store(unsigned char *out, unsigned long *args)
{
    unsigned char v;
    v = (unsigned char)sk_unicode_script_count();
    *out = v;
}

/* FUN_00451e58 / e84 / e88 / eb4 / eb8 / ee4 / ee8 — Unicode script-table
 * registration wrappers (same shape, using FUN_00447144 as the name source). */
/* FUN_00447144 @ out-of-range  — script/block name lookup shared helper. */
extern cl4_result_t sk_x_00447144(unsigned long idx);
void sk_script_store(cl4_result_t *out) { cl4_result_t v; v = sk_x_00447144(0); *out = v; }
void sk_script_reg_1(void) { sk_x_00415570(0, sk_x_00447144); }
void sk_script_reg_2(void) { sk_x_00415570(0, sk_x_00447144); }
void sk_script_reg_3(unsigned long a) { sk_x_0041577c(a, 0, sk_x_00447144); }
void sk_script_reg_4(unsigned long a) { sk_x_0041577c(a, 0, sk_x_00447144); }
void sk_script_reg_5(unsigned long a) { sk_x_00415aa4(a, 0, sk_x_00447144); }
void sk_script_reg_6(unsigned long a) { sk_x_00415aa4(a, 0, sk_x_00447144); }

/* ---- Unicode block-name table (shared by 0x451f24 init and 0x45399c
 * lookup). Condensed faithfully from the decompile's literal string writes:
 * each entry is {name, tag}. tag encodes the block's category/format flags
 * (Ghidra values: e1/e2/e3 single/multi-letter, d000...00xx count field,
 * e400..ef tags for special blocks). The exact first-codepoint ranges live in
 * the 0x45399c case bodies / 0x451f24 writes. ---- */
typedef struct sk_unicode_block {
    const char *name;
    unsigned long tag;
} sk_unicode_block_t;

static const sk_unicode_block_t sk_unicode_blocks[] = {
    { "Basic Latin",                        0xeb000000006e6974 },
    { "Latin-1 Supplement",                 0x614c5f6369736142 },
    { "Latin Extended-A",                   0x614c5f6369736142 },
    { "Latin Extended-B",                   0x614c5f6369736142 },
    { "IPA Extensions",                     0x657478455f415049 },
    { "Spacing Modifier Letters",           0x614c5f6369736142 },
    { "Combining Diacritical Marks",        0x614c5f6369736142 },
    { "Greek and Coptic",                   0x614c5f6369736142 },
    { "Cyrillic",                           0x6c6c69727943 },
    { "Cyrillic Supplement",                0x614c5f6369736142 },
    { "Armenian",                           0x696e656d7241 },
    { "Hebrew",                             0x614c5f6369736142 },
    { "Arabic",                             0x62617241 },
    { "Syriac",                             0x614c5f6369736142 },
    { "Arabic Supplement",                  0x614c5f6369736142 },
    { "Thaana",                             0x614c5f6369736142 },
    { "NKo",                                0x6f4b4e },
    { "Samaritan",                          0x61746972616d6153 },
    { "Mandaic",                            0x646e614d },
    { "Syriac Supplement",                  0x614c5f6369736142 },
    { "Arabic Extended-B",                  0x614c5f6369736142 },
    { "Arabic Extended-A",                  0x614c5f6369736142 },
    { "Devanagari",                         0x614c5f6369736142 },
    { "Bengali",                            0x6c61676e6542 },
    { "Gurmukhi",                           0x614c5f6369736142 },
    { "Gujarati",                           0x614c5f6369736142 },
    { "Oriya",                              0x7969724f },
    { "Tamil",                              0x614c5f6369736142 },
    { "Telugu",                             0x614c5f6369736142 },
    { "Kannada",                            0x6e6e614b },
    { "Malayalam",                          0x614c5f6369736142 },
    { "Sinhala",                            0x6c61686e6953 },
    { "Thai",                               0x614c5f6369736142 },
    { "Lao",                                0x614c5f6369736142 },
    { "Tibetan",                            0x617465626954 },
    { "Myanmar",                            0x616d6e61794d },
    { "Georgian",                           0x6967726f6547 },
    { "Hangul Jamo",                        0x614c5f6369736142 },
    { "Ethiopic",                           0x706f69687445 },
    { "Ethiopic Supplement",                0x614c5f6369736142 },
    { "Cherokee",                           0x614c5f6369736142 },
    { "Unified Canadian Aboriginal Syllabics",0x614c5f6369736142 },
    { "Ogham",                              0x6168674f },
    { "Runic",                              0x614c5f6369736142 },
    { "Tagalog",                            0x614c5f6369736142 },
    { "Hanunoo",                            0x6f6e756e6148 },
    { "Buhid",                              0x614c5f6369736142 },
    { "Tagbanwa",                           0x614c5f6369736142 },
    { "Khmer",                              0x614c5f6369736142 },
    { "Mongolian",                          0x61696c6f676e6f4d },
    { "Unified Canadian Aboriginal Syllabics Extended", 0xd00000000000002e },
    { "Limbu",                              0x75626d694c },
    { "Tai Le",                             0x614c5f6369736142 },
    { "New Tai Lue",                        0x614c5f6369736142 },
    { "Khmer Symbols",                      0x614c5f6369736142 },
    { "Buginese",                           0x614c5f6369736142 },
    { "Tai Tham",                           0x614c5f6369736142 },
    { "Combining Diacritical Marks Extended",0x614c5f6369736142 },
    { "Balinese",                           0x614c5f6369736142 },
    { "Sundanese",                          0x614c5f6369736142 },
    { "Batak",                              0x614c5f6369736142 },
    { "Lepcha",                             0x614c5f6369736142 },
    { "Ol Chiki",                           0x614c5f6369736142 },
    { "Cyrillic Extended-C",                0x614c5f6369736142 },
    { "Georgian Extended",                  0x614c5f6369736142 },
    { "Sundanese Supplement",               0x614c5f6369736142 },
    { "Vedic Extensions",                   0x614c5f6369736142 },
    { "Phonetic Extensions",                0x614c5f6369736142 },
    { "Phonetic Extensions Supplement",     0x614c5f6369736142 },
    { "Combining Diacritical Marks Supplement",0x614c5f6369736142 },
    { "Latin Extended Additional",          0x614c5f6369736142 },
    { "Greek Extended",                     0x78455f6b65657247 },
    { "General Punctuation",                0x614c5f6369736142 },
    { "Superscripts and Subscripts",        0x614c5f6369736142 },
    { "Currency Symbols",                   0x614c5f6369736142 },
    { "Combining Diacritical Marks for Symbols",0x614c5f6369736142 },
    { "Letterlike Symbols",                 0x614c5f6369736142 },
    { "Number Forms",                       0x465f7265626d754e },
    { "Arrows",                             0x73776f727241 },
    { "Mathematical Operators",             0x614c5f6369736142 },
    { "Miscellaneous Technical",            0x614c5f6369736142 },
    { "Control Pictures",                   0x614c5f6369736142 },
    { "Optical Character Recognition",      0x614c5f6369736142 },
    { "Enclosed Alphanumerics",             0x614c5f6369736142 },
    { "Box Drawing",                        0x776172445f786f42 },
    { "Block Elements",                     0x6c455f6b636f6c42 },
    { "Geometric Shapes",                   0x614c5f6369736142 },
    { "Miscellaneous Symbols",              0x614c5f6369736142 },
    { "Dingbats",                           0x73746162676e6944 },
    { "Miscellaneous Mathematical Symbols-A",0x614c5f6369736142 },
    { "Supplemental Arrows-A",              0x614c5f6369736142 },
    { "Braille Patterns",                   0x614c5f6369736142 },
    { "Supplemental Arrows-B",              0x614c5f6369736142 },
    { "Miscellaneous Mathematical Symbols-B",0x614c5f6369736142 },
    { "Supplemental Mathematical Operators",0x614c5f6369736142 },
    { "Miscellaneous Symbols and Arrows",   0x614c5f6369736142 },
    { "Glagolitic",                         0x74696c6f67616c47 },
    { "Latin Extended-C",                   0x614c5f6369736142 },
    { "Coptic",                             0x74706f43 },
    { "Georgian Supplement",                0x614c5f6369736142 },
    { "Tifinagh",                           0x616e69666954 },
    { "Ethiopic Extended",                  0x614c5f6369736142 },
    { "Cyrillic Extended-A",                0x614c5f6369736142 },
    { "Supplemental Punctuation",           0x614c5f6369736142 },
    { "CJK Radicals Supplement",            0x614c5f6369736142 },
    { "Kangxi Radicals",                    0x6978676e614b },
    { "Ideographic Description Characters", 0x614c5f6369736142 },
    { "CJK Symbols and Punctuation",        0x614c5f6369736142 },
    { "Hiragana",                           0x616761726948 },
    { "Katakana",                           0x616b6174614b },
    { "Bopomofo",                           0x614c5f6369736142 },
    { "Hangul Compatibility Jamo",          0x614c5f6369736142 },
    { "Kanbun",                             0x6e75626e614b },
    { "Bopomofo Extended",                  0x614c5f6369736142 },
    { "CJK Strokes",                        0x73656b },
    { "Katakana Phonetic Extensions",       0x614c5f6369736142 },
    { "Enclosed CJK Letters and Months",    0x614c5f6369736142 },
    { "CJK Compatibility",                  0x614c5f6369736142 },
    { "CJK Unified Ideographs Extension A", 0x614c5f6369736142 },
    { "Yijing Hexagram Symbols",            0x614c5f6369736142 },
    { "CJK Unified Ideographs",             0x614c5f6369736142 },
    { "Yi Syllables",                       0x616c6c79535f6959 },
    { "Yi Radicals",                        0x6461525f6959 },
    { "Lisu",                               0x614c5f6369736142 },
    { "Vai",                                0x614c5f6369736142 },
    { "Cyrillic Extended-B",                0x614c5f6369736142 },
    { "Bamum",                              0x756d6142 },
    { "Modifier Tone Letters",              0x614c5f6369736142 },
    { "Latin Extended-D",                   0x614c5f6369736142 },
    { "Syloti Nagri",                       0x614c5f6369736142 },
    { "Common Indic Number Forms",          0x614c5f6369736142 },
    { "Phags-pa",                           0x61705f7367616850 },
    { "Saurashtra",                         0x736172756153 },
    { "Devanagari Extended",                0x614c5f6369736142 },
    { "Kayah Li",                           0x614c5f6369736142 },
    { "Rejang",                             0x614c5f6369736142 },
    { "Hangul Jamo Extended-A",             0x614c5f6369736142 },
    { "Javanese",                           0x6176614a },
    { "Myanmar Extended-B",                 0x614c5f6369736142 },
    { "Cham",                               0x614c5f6369736142 },
    { "Myanmar Extended-A",                 0x614c5f6369736142 },
    { "Tai Viet",                           0x614c5f6369736142 },
    { "Meetei Mayek Extensions",            0x614c5f6369736142 },
    { "Ethiopic Extended-A",                0x614c5f6369736142 },
    { "Latin Extended-E",                   0x614c5f6369736142 },
    { "Cherokee Supplement",                0x614c5f6369736142 },
    { "Meetei Mayek",                       0x614c5f6369736142 },
    { "Hangul Syllables",                   0x614c5f6369736142 },
    { "Hangul Jamo Extended-B",             0x614c5f6369736142 },
    { "High Surrogates",                    0x7275535f68676948 },
    { "High Private Use Surrogates",        0x614c5f6369736142 },
    { "Low Surrogates",                     0x727275535f776f4c },
    { "Private Use Area",                   0x614c5f6369736142 },
    { "CJK Compatibility Ideographs",       0x614c5f6369736142 },
    { "Alphabetic Presentation Forms",      0x614c5f6369736142 },
    { "Arabic Presentation Forms-A",        0x614c5f6369736142 },
    { "Variation Selectors",                0x614c5f6369736142 },
    { "Vertical Forms",                     0x6c61636974726556 },
    { "Combining Half Marks",               0x614c5f6369736142 },
    { "CJK Compatibility Forms",            0x614c5f6369736142 },
    { "Small Form Variants",                0x614c5f6369736142 },
    { "Arabic Presentation Forms-B",        0x614c5f6369736142 },
    { "Halfwidth and Fullwidth Forms",      0x614c5f6369736142 },
    { "Specials",                           0x736c616963657053 },
    { "Linear B Syllabary",                 0x614c5f6369736142 },
    { "Linear B Ideograms",                 0x614c5f6369736142 },
    { "Aegean Numbers",                     0x4e5f6e6165676541 },
    { "Ancient Greek Numbers",              0x614c5f6369736142 },
    { "Ancient Symbols",                    0x5f746e6569636e41 },
    { "Phaistos Disc",                      0x736f747369616850 },
    { "Lycian",                             0x6963794c },
    { "Carian",                             0x69726143 },
    { "Coptic Epact Numbers",               0x614c5f6369736142 },
    { "Old Italic",                         0x6c6174495f646c4f },
    { "Gothic",                             0x68746f47 },
    { "Old Permic",                         0x6d7265505f646c4f },
    { "Ugaritic",                           0x746972616755 },
    { "Old Persian",                        0x737265505f646c4f },
    { "Deseret",                            0x614c5f6369736142 },
    { "Shavian",                            0x616976616853 },
    { "Osmanya",                            0x796e616d734f },
    { "Osage",                              0x614c5f6369736142 },
    { "Elbasan",                            0x617361626c45 },
    { "Caucasian Albanian",                 0x614c5f6369736142 },
    { "Vithkuqi",                           0x614c5f6369736142 },
    { "Linear A",                           0x614c5f6369736142 },
    { "Latin Extended-F",                   0x614c5f6369736142 },
    { "Cypriot Syllabary",                  0x614c5f6369736142 },
    { "Imperial Aramaic",                   0x614c5f6369736142 },
    { "Palmyrene",                          0x614c5f6369736142 },
    { "Nabataean",                          0x614c5f6369736142 },
    { "Hatran",                             0x614c5f6369736142 },
    { "Phoenician",                         0x72746148 },
    { "Lydian",                             0x614c5f6369736142 },
    { "Meroitic Hieroglyphs",               0x614c5f6369736142 },
    { "Meroitic Cursive",                   0x614c5f6369736142 },
    { "Kharoshthi",                         0x736f7261684b },
    { "Old South Arabian",                  0x614c5f6369736142 },
    { "Old North Arabian",                  0x614c5f6369736142 },
    { "Manichaean",                         0x614c5f6369736142 },
    { "Avestan",                            0x617473657641 },
    { "Inscriptional Parthian",             0x614c5f6369736142 },
    { "Inscriptional Pahlavi",              0x614c5f6369736142 },
    { "Psalter Pahlavi",                    0x614c5f6369736142 },
    { "Old Turkic",                         0x6b7275545f646c4f },
    { "Old Hungarian",                      0x6966696e6148 },
    { "Hanifi Rohingya",                    0x6966696e6148 },
    { "Rumi Numeral Symbols",               0x614c5f6369736142 },
    { "Yezidi",                             0x614c5f6369736142 },
    { "Old Sogdian",                        0x64676f535f646c4f },
    { "Sogdian",                            0x616964676f53 },
    { "Old Uyghur",                         0x79555f646c4f },
    { "Chorasmian",                         0x614c5f6369736142 },
    { "Elymaic",                            0x6d796c45 },
    { "Brahmi",                             0x614c5f6369736142 },
    { "Kaithi",                             0x614c5f6369736142 },
    { "Sora Sompeng",                       0x614c5f6369736142 },
    { "Chakma",                             0x614c5f6369736142 },
    { "Mahajani",                           0x614c5f6369736142 },
    { "Sharada",                            0x72616853 },
    { "Sinhala Archaic Numbers",            0x614c5f6369736142 },
    { "Khojki",                             0x614c5f6369736142 },
    { "Multani",                            0x6e61746c754d },
    { "Khudawadi",                          0x646177616475684b },
    { "Grantha",                            0x68746e617247 },
    { "Newa",                               0x614c5f6369736142 },
    { "Tirhuta",                            0x747568726954 },
    { "Siddham",                            0x614c5f6369736142 },
    { "Modi",                               0x614c5f6369736142 },
    { "Mongolian Supplement",               0x614c5f6369736142 },
    { "Takri",                              0x614c5f6369736142 },
    { "Ahom",                               0x614c5f6369736142 },
    { "Dogra",                              0x72676f44 },
    { "Warang Citi",                        0x614c5f6369736142 },
    { "Nandinagari",                        0x616e69646e614e },
    { "Zanabazar Square",                   0x614c5f6369736142 },
    { "Soyombo",                            0x626d6f796f53 },
    { "Unified Canadian Aboriginal Syllabics Extended-A", 0xd000000000000030 },
    { "Pau Cin Hau",                        0x614c5f6369736142 },
    { "Bhaiksuki",                          0x6b75736b69616842 },
    { "Marchen",                            0x65686372614d },
    { "Masaram Gondi",                      0x5f6d61726173614d },
    { "Gunjala Gondi",                      0x5f616c616a6e7547 },
    { "Makasar",                            0x6173616b614d },
    { "Lisu Supplement",                    0x7573694c },
    { "Tamil Supplement",                   0x614c5f6369736142 },
    { "Cuneiform",                          0x614c5f6369736142 },
    { "Cuneiform Numbers and Punctuation",  0x614c5f6369736142 },
    { "Early Dynastic Cuneiform",           0x614c5f6369736142 },
    { "Egyptian Hieroglyphs",               0x614c5f6369736142 },
    { "Egyptian Hieroglyph Format Controls",0x614c5f6369736142 },
    { "Anatolian Hieroglyphs",              0x614c5f6369736142 },
    { "Bamum Supplement",                   0x614c5f6369736142 },
    { "Mro",                                0x6f724d },
    { "Tangsa",                             0x6173676e6154 },
    { "Bassa Vah",                          0x614c5f6369736142 },
    { "Pahawh Hmong",                       0x614c5f6369736142 },
    { "Medefaidrin",                        0x614c5f6369736142 },
    { "Miao",                               0x6f61694d },
    { "Ideographic Symbols and Punctuation",0x614c5f6369736142 },
    { "Tangut",                             0x7475676e6154 },
    { "Tangut Components",                  0x614c5f6369736142 },
    { "Khitan Small Script",                0x614c5f6369736142 },
    { "Tangut Supplement",                  0x614c5f6369736142 },
    { "Kana Extended-B",                    0x6e616e614b },
    { "Kana Extended-A",                    0x7478455f616e614b },
    { "Small Kana Extension",               0x614c5f6369736142 },
    { "Nushu",                              0x756873754e },
    { "Duplicate",                          0x6e61796f6c707544 },
    { "Shorthand Format Controls",          0x614c5f6369736142 },
    { "Znamenny Musical Notation",          0x614c5f6369736142 },
    { "Byzantine Musical Symbols",          0x614c5f6369736142 },
    { "Musical Symbols",                    0x5f6c61636973754d },
    { "Ancient Greek Musical Notation",     0x614c5f6369736142 },
    { "Mayan Numerals",                     0x754e5f6e6179614d },
    { "Tai Xuan Jing Symbols",              0x614c5f6369736142 },
    { "Counting Rod Numerals",              0x614c5f6369736142 },
    { "Mathematical Alphanumeric Symbols",  0x614c5f6369736142 },
    { "Sutton SignWriting",                 0x614c5f6369736142 },
    { "Latin Extended-G",                   0xd000000000000010 },
    { "Glagolitic Supplement",              0x614c5f6369736142 },
    { "Nyiakeng Puachue Hmong",             0x614c5f6369736142 },
    { "Toto",                               0x6f746f54 },
    { "Wancho",                             0x6f68636e6157 },
    { "Ethiopic Extended-B",                0x614c5f6369736142 },
    { "Mende Kikakui",                      0x614c5f6369736142 },
    { "Adlam",                              0x6d616c6441 },
    { "Indic Siyaq Numbers",                0x614c5f6369736142 },
    { "Ottoman Siyaq Numbers",              0x614c5f6369736142 },
    { "Arabic Mathematical Alphabetic Symbols",0x614c5f6369736142 },
    { "Mahjong Tiles",                      0x6e6f6a68614d },
    { "Domino Tiles",                       0x6e6979616c50 },
    { "Playing Cards",                      0x614c5f6369736142 },
    { "Enclosed Alphanumeric Supplement",   0x614c5f6369736142 },
    { "Enclosed Ideographic Supplement",    0x614c5f6369736142 },
    { "Miscellaneous Symbols and Pictographs",0x614c5f6369736142 },
    { "Emoticons",                          0x6e6f6369746f6d45 },
    { "Ornamental Dingbats",                0x614c5f6369736142 },
    { "Transport and Map Symbols",          0x614c5f6369736142 },
    { "Alchemical Symbols",                 0x614c5f6369736142 },
    { "Geometric Shapes Extended",          0x614c5f6369736142 },
    { "Supplemental Arrows-C",              0x614c5f6369736142 },
    { "Supplemental Symbols and Pictographs",0x614c5f6369736142 },
    { "Chess Symbols",                      0x5f7373656843 },
    { "Symbols and Pictographs Extended-A", 0x614c5f6369736142 },
    { "Symbols for Legacy Computing",       0x614c5f6369736142 },
    { "CJK Unified Ideographs Extension B", 0x614c5f6369736142 },
    { "CJK Unified Ideographs Extension C", 0x614c5f6369736142 },
    { "CJK Unified Ideographs Extension D", 0x614c5f6369736142 },
    { "CJK Unified Ideographs Extension E", 0x614c5f6369736142 },
    { "CJK Unified Ideographs Extension F", 0x614c5f6369736142 },
    { "CJK Compatibility Ideographs Supplement",0x614c5f6369736142 },
    { "CJK Unified Ideographs Extension G", 0x614c5f6369736142 },
    { "Tags",                               0x73676154 },
    { "Variation Selectors Supplement",     0x614c5f6369736142 },
    { "Supplementary Private Use Area-A",   0x614c5f6369736142 },
    { "Supplementary Private Use Area-B",   0x614c5f6369736142 },
    { "No_Block",                           0x6b636f6c425f6f4e },
};

/* FUN_00451f24 @ 0x00451f24   (est. sk_unicode_block_table_init)
 * Ghidra: void FUN_00451f24(void)
 * Builds and publishes the Unicode block-name table: allocates a block-name
 * descriptor array, fills each 0x18-byte entry with the block name pointer
 * (stride 0x18 from the entries' base) and a per-block code count at
 * entry+0x10 (stride fields), stores the block count and the "No_Block"
 * fallback, then records the effective block count. Data transcribed from the
 * decompile's literal writes.
 * Confidence: low (large literal data table; condensed here)
 */
void sk_unicode_block_table_init(void)
{
    unsigned long blocks, blk;

    sk_x_00084220();
    sk_x_003504d0();
    blk = sk_x_00002534(0x657a30, 0x5a1a48);
    blocks = sk_x_0036a940(blk, 0x1e38, 7);
    /* entries are 0x18-byte records: name at base, count at +0x10.
     * (transcribed: each write sets blocks[base + i*0x18] = &name,
     *  and blocks[base + i*0x18 + 0x10] = count) */
    for (blk = 0; blk < sizeof(sk_unicode_blocks)/sizeof(sk_unicode_blocks[0]); blk++) {
        *(const char **)((unsigned long)blocks + 0x38 + blk * 0x18) =
            sk_unicode_blocks[blk].name;
    }
    /* store block count + No_Block fallback; finalize */
    sk_x_000b43d0();
    blocks = sk_x_002ad78c();
    sk_x_0036b118(blocks);
    sk_x_003a25d4();
    sk_x_00084234(0, 0);
}

/* FUN_0045399c @ 0x0045399c   (est. sk_unicode_block_name)
 * Ghidra: undefined1 [16] FUN_0045399c(undefined2 param_1)
 * Returns the {name, tag} pair for the Unicode block at index param_1,
 * consulting the shared block-name table (some indices call per-block helper
 * FUN_00464xxx lookups for the "special" blocks — compressed here to the
 * shared table). Index 0 defaults to "Basic Latin".
 * Confidence: low (huge literal switch condensed to table lookup)
 */
cl4_result_t sk_unicode_block_name(unsigned int idx)
{
    cl4_result_t r;
    size_t n = sizeof(sk_unicode_blocks)/sizeof(sk_unicode_blocks[0]);
    if ((size_t)idx >= n) idx = 0;
    r.lo = (unsigned long)sk_unicode_blocks[idx].name;
    r.hi = sk_unicode_blocks[idx].tag;
    return r;
}

/* FUN_004553e4 @ 0x004553e4   (est. sk_block_name_store)
 * Ghidra: void FUN_004553e4(undefined1 (*param_1) [16])
 * Stores the block-name pair for the current block index (x20) into out.
 * Confidence: low
 */
void sk_block_name_store(cl4_result_t *out)
{
    *out = sk_unicode_block_name(0);
}

/* FUN_00455438 @ 0x00455438   (est. sk_unicode_language_regions_init)
 * Ghidra: long FUN_00455438(void)
 * Initialises the collection-of-element-types (language/region) table: builds
 * a lookup table via FUN_00310c44, on failure panics with the
 * "The collection of element types..." string (0x5df6e0).
 * Confidence: low (jump-table-heavy body, partially recovered)
 */
long sk_unicode_language_regions_init(void)
{
    unsigned long u1, u2, u3;
    long local58[2], result;
    unsigned long tmp;

    u1 = sk_x_00350980();
    u2 = sk_x_00027754(0);
    u3 = sk_x_00027788();
    sk_x_00084174(u3);
    tmp = u2;
    if (0 != 0) { /* unaff_x21 — caller-register, treated as 0 */
        tmp = tmp | 0x10000;
    }
    u2 = sk_x_00027754(u2);
    sk_x_00310c44();
    sk_x_004662b8();
    u3 = sk_x_00002534();
    sk_x_00310c44();
    sk_x_00310c44();   /* (*pcVar4)(local_58, ...) — callback via table */
    if (local58[0] != 0) {
        sk_x_003509c8(0);
        return local58[0];
    }
    sk_x_00002874(0x5df6e0);   /* "The collection of element types..." */
    sk_x_003593c0();
    sk_x_00002818();
    sk_x_001afa84();           /* noreturn */
    return 0;
}

/* FUN_00455574 @ 0x00455574   (est. sk_binary_lookup_or_default)
 * Ghidra: void FUN_00455574(out, a, b, c, d, p6)
 * Fetches a value from a table pointer p6, handling tagged/untagged pointer
 * forms; on the fault/invalid paths delegates to FUN_00351e3c /
 * FUN_002a4468. Writes the resulting {lo,hi} into out.
 * Confidence: low
 */
void sk_binary_lookup_or_default(cl4_result_t *out, unsigned long a, unsigned long b,
                                 unsigned long c, unsigned long d, unsigned long *p6)
{
    unsigned long v;
    cl4_result_t r;

    if (d == 0) {
        v = *p6;
    } else {
        sk_x_0036b270(d);
        if ((d >> 0x3c & 1) != 0) {
            sk_x_004662b8();
            sk_x_00002534();
            sk_x_00351e3c(out, 0, 0);
            sk_x_002a4468();
            return;
        }
        if ((d >> 0x3d & 1) == 0) {
            if ((c >> 0x3c & 1) != 0) v = *p6;
            else { sk_x_004662b8(); sk_x_00002534(); sk_x_00351e3c(out,0,0); sk_x_002a4468(); return; }
        } else {
            v = *p6;
        }
    }
    r = sk_x_00371950(0, v);
    *out = r;
}

/* FUN_0045567c @ 0x0045567c   (est. sk_language_lookup_launch)
 * Ghidra: void FUN_0045567c(a,b,c)
 * Looks up a language table (FUN_00455a68 callback) and drives the result
 * through FUN_0007c1c4 / FUN_00455778.
 * Confidence: low
 */
void sk_language_lookup_launch(unsigned long a, unsigned long b, unsigned long c)
{
    long t;
    cl4_result_t r, r2;

    sk_x_003504d0();
    sk_x_0046647c();
    sk_x_00027754(c);
    t = sk_x_000262fc(0);
    r = sk_x_00371950(0, *(unsigned long *)(t + 0x10), t + 0x20, 0, 0);
    sk_x_0036b118(t);
    r2 = sk_x_0007c1c4(0);
    sk_unicode_language_apply(r2.lo, r2.hi, r.lo, c);
    sk_x_00310d98(0);
}

/* FUN_00455778 @ 0x00455778   (est. sk_unicode_language_apply)
 * Ghidra: void FUN_00455778(a,b,c,d)
 * Applies a language/region table: walks the parsed element collection and
 * publishes it, iterating rows via FUN_00455990. Complex; partially
 * recovered from a failed jumptable.
 * Confidence: low
 */
void sk_unicode_language_apply(unsigned long a, unsigned long b, unsigned long c, unsigned long d)
{
    cl4_result_t v6;
    unsigned long u4, u1, u2, tmp;

    v6 = sk_x_0008e518();
    u4 = v6.hi;
    sk_x_0007c028();
    sk_x_0036b270(*(unsigned long *)(0 + 0x40));
    sk_x_000aa4ec();
    sk_x_00027754(d);
    u1 = sk_x_00027754();
    v6 = sk_x_00350530();
    u2 = sk_x_00377824(v6.lo, v6.hi, u4);
    sk_x_000a6f88();
    sk_x_0007c1a4();
    sk_x_0036b270(0);
    sk_x_003509c8(c);
    tmp = sk_x_002b8444(*(unsigned long *)(0 + 0x40), c);
    sk_x_000a68c4(u1);
    sk_x_00377bec(u1, u4, u2, 0, 0);
    sk_x_000a68f4();
    while (1) {
        sk_x_00100efc(0);
        sk_x_00310d98(0);
        u1 = 0;
        u4 = sk_x_0006a4c0(0, 0);
        sk_unicode_language_row(u4, &tmp, u1);
        sk_x_000026e8(0);
    }
}

/* FUN_00455990 @ 0x00455990   (est. sk_unicode_language_row)
 * Ghidra: void FUN_00455990(a,b,c)
 * Processes one language-row: accumulates size from a helper into the
 * current-register cursor (x20) and the row's byte count.
 * Confidence: low
 */
void sk_unicode_language_row(unsigned long a, unsigned long *b, unsigned long c)
{
    long l2, acc;

    sk_x_00084220();
    sk_x_0035098c();
    sk_x_0007c028();
    l2 = *(long *)(0 + 0x40);
    sk_x_0036b270(0);
    acc = sk_x_00450848(0, 0);
    *b = acc;
    sk_x_003507bc();
    sk_x_00350618(0);
    *b = *b + l2;
    sk_x_00084234(0);
}

/* FUN_00455a68 @ 0x00455a68   (est. sk_language_count_store)
 * Ghidra: void FUN_00455a68(undefined8 *param_1,long param_2)
 * Stores the count field of a language table row into *param_1.
 * Confidence: low
 */
void sk_language_count_store(unsigned long *out, long row)
{
    unsigned long v;
    sk_x_0006a4c0(row, *(unsigned long *)(row + 0x18));
    sk_x_00464000();
    v = sk_x_003625e4();
    *out = v;
}

/* FUN_00455abc @ 0x00455abc   (est. sk_encode_byte)
 * Ghidra: void FUN_00455abc(undefined8 param_1)
 * Encodes one byte via FUN_00310d68 with the given length/flag.
 * Confidence: medium
 */
void sk_encode_byte(unsigned long v) { sk_x_00310d68(0, v); }

/* FUN_00455ac8 @ 0x00455ac8   (est. sk_encode_utf8_len)
 * Ghidra: void FUN_00455ac8(a, len, b)
 * Encodes len bytes of UTF-8 (via FUN_004665e8 codepoint feed + FUN_00310d68
 * byte emission), handling lengths 1-4 and the multi-word tail loop.
 * Confidence: medium
 */
void sk_encode_utf8_len(unsigned long a, unsigned long len, unsigned long b)
{
    cl4_result_t cur, nxt;
    unsigned long u3;

    cur.lo = b; cur.hi = len;
    for (;;) {
        nxt.hi = cur.hi;
        nxt.lo = a;
        u3 = cur.lo;
        if (len < 5) {
            switch (len) {
            default: return;
            case 4: nxt = sk_x_004665e8(); u3 = nxt.lo;
            case 3: nxt = sk_x_004665e8(nxt.lo, nxt.hi, u3); u3 = nxt.lo;
            case 2: u3 = sk_x_004665e8(nxt.lo, nxt.hi, u3);
            case 1: sk_x_00310d68(0, u3); return;
            }
        }
        u3 = sk_x_004665e8();
        u3 = sk_x_00310d68(0xff, u3);
        u3 = sk_x_00310d68(0xff, u3);
        cur = sk_x_00310d68(0, u3);
        a = cur.lo;
        len = len - 4;
        if (len < 4) break;   /* SBORROW8(len,4) carries when len-4 <0 */
    }
    sk_sw_breakpoint(1, 0x455b74);
}

/* FUN_00455b88 @ 0x00455b88   (est. sk_unicode_encoding_dispatch)
 * Ghidra: void FUN_00455b88(void)
 * Enumerates and applies a character-encoding table: pulls the row count from
 * a vtable callback (offset +0x58), then iterates row entries accumulating a
 * byte offset with overflow checks (SoftwareBreakpoint on carry at 0x455d8c /
 * 0x455d38). Returns when the accumulated count matches.
 * Confidence: low (register-fragment / jumptable-heavy)
 */
void sk_unicode_encoding_dispatch(void)
{
    cl4_result_t v9;
    unsigned long l7, u2, u3, u4, acc, len, row;

    v9 = sk_x_0008e518();
    l7 = v9.lo;
    sk_x_00027754(0);
    sk_x_00352840(0);
    u2 = sk_x_0031b760();
    sk_x_003509c8(u2);
    sk_x_0007c1a4();
    sk_x_0036b270(0);
    sk_x_0034b05c();
    sk_x_00352840(0);
    u3 = sk_x_0031b778();
    sk_x_000a6f88();
    sk_x_0007c1a4();
    sk_x_0036b270(0);
    u4 = sk_x_00310d68(0, 0);   /* vtable call via *l7+0x58 */
    sk_x_00351db4();
    if (u4 == 0) {
        u2 = 0;
    } else {
        sk_x_00350a04();
        sk_x_00200b38();
        sk_x_00200bd0(0, u2);
        acc = 0;
        while (sk_x_00200bf4(0, u3) != 0 &&
               sk_x_003509c8(*(unsigned long *)(l7 + 0x60)) != 0) {
            len = *(unsigned char *)(0 + 0x50);
            row = *(long *)(0 + 0x40);
            if (acc + len < acc) { sk_sw_breakpoint(1, 0x455d8c); }
            acc = (acc + len) & ~len;
            if (acc == u4) { u2 = 0; break; }
            acc = acc + row;
            if (acc < (acc - row)) { sk_sw_breakpoint(1, 0x455d38); }
        }
        u2 = 1;
        sk_x_00350560(0);
    }
    sk_x_0008e500(u2, 0);
}

/* FUN_00455d8c / 0x455db8 — array-rebuild stubs. Ghidra: void FUN_00455dXX(void)
 * Rebuild an array container at x20+0x20 with the element count from +0x10,
 * using the tagged element-size/traits at 0x682e08 / 0x6728f0.
 * Confidence: low */
void sk_array_rebuild_a(void) { sk_x_0035bc70(0, 0, 0x682e08); }
void sk_array_rebuild_b(void) { sk_x_0035bc70(0, 0, 0x6728f0); }

/* ---- Growable array "ensure capacity" allocators.
 * Each allocates param_2*esize+0x20 bytes (0x20-byte header: count at +0x10,
 * capacity at +0x18), or returns the shared empty-array sentinel DAT_00657778
 * when the capacity request is zero. Only the element stride differs. ---- */

/* FUN_00455de4 @ 0x00455de4  (est. sk_arr_alloc_8)   stride 8   */
void *sk_arr_alloc_8(long cur, long want)
{
    unsigned long u1; void *p; long l3;
    if (want <= cur) want = cur;
    if (want == 0) return (void *)0x657778;
    u1 = sk_x_00002534(0x6579c8, 0x5a19a0);
    p = (void *)sk_x_0036a940(u1, want * 8 + 0x20, 7);
    l3 = sk_x_000126e8();
    *(long *)(p + 0x10) = cur;
    *(long *)(p + 0x18) = (l3 + -0x20) / 8 << 1;
    return p;
}

/* FUN_00455e60 @ 0x00455e60  (est. sk_arr_alloc_178)  stride 0x178 */
void *sk_arr_alloc_178(long cur, long want)
{
    unsigned long u1; void *p; long l3;
    if (want <= cur) want = cur;
    if (want == 0) return (void *)0x657778;
    u1 = sk_x_00002534(0x657b20, 0x5a35c8);
    p = (void *)sk_x_0036a940(u1, want * 0x178 + 0x20, 7);
    l3 = sk_x_000126e8();
    *(long *)(p + 0x10) = cur;
    *(long *)(p + 0x18) = (l3 + -0x20) / 0x178 << 1;
    return p;
}

/* FUN_00455ee4 @ 0x00455ee4  (est. sk_arr_alloc_4)   stride 4   */
void *sk_arr_alloc_4(long cur, long want)
{
    unsigned long u1; void *p; long l3;
    if (want <= cur) want = cur;
    if (want == 0) return (void *)0x657778;
    u1 = sk_x_00002534(0x6575f0, 0x5a19e0);
    p = (void *)sk_x_0036a940(u1, want * 4 + 0x20, 7);
    l3 = sk_x_000126e8();
    *(long *)(p + 0x10) = cur;
    *(long *)(p + 0x18) = (l3 + -0x20) / 4 << 1;
    return p;
}

/* FUN_00455f60 @ 0x00455f60  (est. sk_arr_alloc_38)   stride 0x38 */
void *sk_arr_alloc_38(long cur, long want)
{
    unsigned long u1; void *p; long l3;
    if (want <= cur) want = cur;
    if (want == 0) return (void *)0x657778;
    u1 = sk_x_00002534(0x657ba8, 0x5a3690);
    p = (void *)sk_x_0036a940(u1, want * 0x38 + 0x20, 7);
    l3 = sk_x_000126e8();
    *(long *)(p + 0x10) = cur;
    *(long *)(p + 0x18) = (l3 + -0x20) / 0x38 << 1;
    return p;
}

/* FUN_00455fe4 @ 0x00455fe4  (est. sk_arr_alloc_50)   stride 0x50 */
void *sk_arr_alloc_50(long cur, long want)
{
    unsigned long u1; void *p; long l3;
    if (want <= cur) want = cur;
    if (want == 0) return (void *)0x657778;
    u1 = sk_x_00002534(0x657b98, 0x5a3670);
    p = (void *)sk_x_0036a940(u1, want * 0x50 + 0x20, 7);
    l3 = sk_x_000126e8();
    *(long *)(p + 0x10) = cur;
    *(long *)(p + 0x18) = (l3 + -0x20) / 0x50 << 1;
    return p;
}

/* FUN_00456068 @ 0x00456068  (est. sk_arr_alloc_30)   stride 0x30 */
void *sk_arr_alloc_30(long cur, long want)
{
    unsigned long u1; void *p; long l3;
    if (want <= cur) want = cur;
    if (want == 0) return (void *)0x657778;
    u1 = sk_x_00002534(0x657b90, 0x5a3668);
    p = (void *)sk_x_0036a940(u1, want * 0x30 + 0x20, 7);
    l3 = sk_x_000126e8();
    *(long *)(p + 0x10) = cur;
    *(long *)(p + 0x18) = (l3 + -0x20) / 0x30 << 1;
    return p;
}

/* FUN_004560ec @ 0x004560ec  (est. sk_arr_alloc_10)   stride 0x10, empty=0 */
long sk_arr_alloc_10(long cur, long want)
{
    unsigned long u1; long p; long l3;
    if (want <= cur) want = cur;
    if (want == 0) { sk_x_000776cc(); return 0; }
    sk_x_00355968();
    u1 = sk_x_00002534();
    p = sk_x_0036a940(u1, want * 0x10 + 0x20, 7);
    l3 = sk_x_000126e8();
    *(long *)(p + 0x10) = cur;
    *(long *)(p + 0x18) = (l3 + -0x20) / 0x10 << 1;
    return p;
}

/* FUN_00456158 @ 0x00456158  (est. sk_arr_alloc_18)   stride 0x18, empty=0 */
long sk_arr_alloc_18(long cur, long want)
{
    unsigned long u1; long p; long l3;
    if (want <= cur) want = cur;
    if (want == 0) { sk_x_000776cc(); return 0; }
    sk_x_00355968();
    u1 = sk_x_00002534();
    p = sk_x_0036a940(u1, want * 0x18 + 0x20, 7);
    l3 = sk_x_000126e8();
    *(long *)(p + 0x10) = cur;
    *(long *)(p + 0x18) = (l3 + -0x20) / 0x18 << 1;
    return p;
}

/* FUN_004561cc @ 0x004561cc  (est. sk_arr_alloc_20)   stride 0x20, empty=0 */
long sk_arr_alloc_20(long cur, long want)
{
    unsigned long u1; long p; long l3;
    if (want <= cur) want = cur;
    if (want == 0) { sk_x_000776cc(); return 0; }
    sk_x_00355968();
    u1 = sk_x_00002534();
    p = sk_x_0036a940(u1, want * 0x20 + 0x20, 7);
    l3 = sk_x_000126e8();
    *(long *)(p + 0x10) = cur;
    *(long *)(p + 0x18) = (l3 + -0x20) / 0x20 << 1;
    return p;
}

/* FUN_00456238 @ 0x00456238  (est. sk_arr_resize_01)
 * Ghidra: void FUN_00456238(void) — resize current array (x20) via generic
 * grow, store result into x20. */
void sk_arr_resize_01(void) { sk_x_0045636c(); }

/* FUN_00456294 @ 0x00456294  (est. sk_arr_resize_02) — same shape. */
void sk_arr_resize_02(void) { sk_x_0045636c(); }

/* FUN_004562f0 @ 0x004562f0  (est. sk_arr_resize_03) — via the 0x20-stride grow. */
void sk_arr_resize_03(void) { sk_x_00456420(); }

/* FUN_00456310 @ 0x00456310  (est. sk_arr_resize_04) — same as 01. */
void sk_arr_resize_04(void) { sk_x_0045636c(); }

/* FUN_0045636c @ 0x0045636c  (est. sk_arr_grow_gen)
 * Ghidra: long FUN_0045636c(flags, new_size, grow, arr, fn, fn, fn)
 * Generic array grow: when grow is set, consult the capacity
 * (extraout via FUN_004652d4) and double if needed, trapping on overflow
 * (SoftwareBreakpoint 0x456420). Calls fn5 to compute the new block size from
 * the current element count, then either commits into arr+0x20 (committed
 * path) or publishes via fn7 (the transient path). Returns the new capacity.
 * Confidence: low
 */
long sk_arr_grow_gen(unsigned long flags, long new_size, unsigned long grow, long arr,
                     void (*fn5)(void), void (*fn6)(void), void (*fn7)(void))
{
    long capacity, sz;

    if ((grow & 1) != 0) {
        sk_x_004652d4();
        capacity = new_size;
        if (new_size < 0) { sk_sw_breakpoint(1, 0x456420); }
        sk_x_00465428();
        new_size = capacity;
    }
    sz = *(long *)(arr + 0x10);
    capacity = sk_x_0036a940(sz, new_size, 7);   /* via fn5 */
    if ((flags & 1) == 0) {
        sk_x_0006b6e0();
        if (fn7) fn7();
    } else {
        if (fn6) fn6(arr + 0x20, sz, capacity + 0x20);
        *(long *)(arr + 0x10) = 0;
        sk_x_0036b118(arr);
    }
    return capacity;
}

/* FUN_00456420 @ 0x00456420  (est. sk_arr_grow_20)
 * Ghidra: long FUN_00456420(flags, want, grow, arr)
 * 0x20-stride array grow: when grow, capacity = (count>>1); if < want use
 * (count & ~1) rounded up to want. Allocates via sk_arr_alloc_20 and commits.
 * Confidence: low
 */
long sk_arr_grow_20(unsigned long flags, unsigned long want, unsigned long grow, long arr)
{
    unsigned long cap, cnt;
    long sz;

    cap = want;
    if ((grow & 1) != 0) {
        cap = *(unsigned long *)(arr + 0x18) >> 1;
        if ((long)cap < (long)want) {
            if ((long)(cap + 0x4000000000000000) < 0) { sk_sw_breakpoint(1, 0x4564e4); }
            cap = *(unsigned long *)(arr + 0x18) & 0xfffffffffffffffe;
            if ((long)cap <= (long)want) cap = want;
        }
    }
    cnt = *(unsigned long *)(arr + 0x10);
    sz = sk_arr_alloc_20(cnt, cap);
    if ((flags & 1) == 0) {
        sk_arr_move_20(0, cnt, sz + 0x20, arr);
    } else {
        sk_x_000699a4(arr + 0x20, cnt, sz + 0x20);
        *(long *)(arr + 0x10) = 0;
        sk_x_0036b118(arr);
    }
    return sz;
}

/* FUN_004564e4 @ 0x004564e4  (est. sk_arr_grow_10v)
 * Ghidra: long FUN_004564e4(flags, new_size, grow, arr, a, b, fn7)
 * 0x10-stride grow with a resize-fill helper (FUN_00354828) before the
 * 0x10-stride allocation. Commits via sk_x_000699a4 or fn7.
 * Confidence: low
 */
long sk_arr_grow_10v(unsigned long flags, long new_size, unsigned long grow, long arr,
                     unsigned long a, unsigned long b, void (*fn7)(void))
{
    long capacity, cnt;

    if ((grow & 1) != 0) {
        sk_x_004652d4();
        capacity = new_size;
        if (new_size < 0) { sk_sw_breakpoint(1, 0x45659c); }
        sk_x_00465428();
        new_size = capacity;
    }
    cnt = *(long *)(arr + 0x10);
    sk_x_00354828(cnt, new_size);
    capacity = sk_arr_alloc_10(0, 0);
    if ((flags & 1) == 0) {
        if (fn7) fn7(0, cnt, capacity + 0x20, arr);
    } else {
        sk_x_000699a4(arr + 0x20, cnt, capacity + 0x20);
        *(long *)(arr + 0x10) = 0;
        sk_x_0036b118(arr);
    }
    return capacity;
}

/* FUN_0045659c @ 0x0045659c  (est. sk_arr_grow_10)
 * Ghidra: long FUN_0045659c(flags, new_size, grow, arr, a, b, fn7, fn8)
 * 0x10-stride grow (matches FUN_004560ec allocator) with fill helper
 * FUN_00354828; commits via fn7 or fn8. This is the workhorse grow used by the
 * language/array wrappers above.
 * Confidence: low
 */
long sk_arr_grow_10(unsigned long flags, long new_size, unsigned long grow, long arr,
                    unsigned long a, unsigned long b, void (*fn7)(void), void (*fn8)(void))
{
    long capacity, cnt;

    if ((grow & 1) != 0) {
        sk_x_004652d4();
        capacity = new_size;
        if (new_size < 0) { sk_sw_breakpoint(1, 0x456650); }
        sk_x_00465428();
        new_size = capacity;
    }
    cnt = *(long *)(arr + 0x10);
    sk_x_00354828(cnt, new_size);
    capacity = sk_arr_alloc_10(0, 0);
    if ((flags & 1) == 0) {
        sk_x_0006b6e0();
        if (fn8) fn8();
    } else {
        if (fn7) fn7(arr + 0x20, cnt, capacity + 0x20);
        *(long *)(arr + 0x10) = 0;
        sk_x_0036b118(arr);
    }
    return capacity;
}

/* FUN_00456650 @ 0x00456650  (est. sk_arr_grow_18a)
 * Ghidra: long FUN_00456650(flags, want, grow, arr)
 * 0x18-stride grow (matches sk_arr_alloc_18); commit via sk_arr_move_18 or
 * sk_x_000699d8.
 * Confidence: low
 */
long sk_arr_grow_18a(unsigned long flags, unsigned long want, unsigned long grow, long arr)
{
    unsigned long cap, cnt;
    long sz;

    cap = want;
    if ((grow & 1) != 0) {
        cap = *(unsigned long *)(arr + 0x18) >> 1;
        if ((long)cap < (long)want) {
            if ((long)(cap + 0x4000000000000000) < 0) { sk_sw_breakpoint(1, 0x456714); }
            cap = *(unsigned long *)(arr + 0x18) & 0xfffffffffffffffe;
            if ((long)cap <= (long)want) cap = want;
        }
    }
    cnt = *(unsigned long *)(arr + 0x10);
    sz = sk_arr_alloc_18(cnt, cap);
    if ((flags & 1) == 0) {
        sk_arr_move_18(0, cnt, sz + 0x20, arr);
    } else {
        sk_x_000699d8(arr + 0x20, cnt, sz + 0x20);
        *(long *)(arr + 0x10) = 0;
        sk_x_0036b118(arr);
    }
    return sz;
}

/* FUN_00456714 @ 0x00456714  (est. sk_arr_grow_18b)
 * Same as sk_arr_grow_18a with a distinct traits string (0x657b68/0x5a3640).
 * Confidence: low
 */
long sk_arr_grow_18b(unsigned long flags, unsigned long want, unsigned long grow, long arr)
{
    unsigned long cap, cnt;
    long sz;

    cap = want;
    if ((grow & 1) != 0) {
        cap = *(unsigned long *)(arr + 0x18) >> 1;
        if ((long)cap < (long)want) {
            if ((long)(cap + 0x4000000000000000) < 0) { sk_sw_breakpoint(1, 0x4567d8); }
            cap = *(unsigned long *)(arr + 0x18) & 0xfffffffffffffffe;
            if ((long)cap <= (long)want) cap = want;
        }
    }
    cnt = *(unsigned long *)(arr + 0x10);
    sz = sk_arr_alloc_18(cnt, cap);
    if ((flags & 1) == 0) {
        sk_arr_move_18(0, cnt, sz + 0x20, arr);
    } else {
        sk_x_000699d8(arr + 0x20, cnt, sz + 0x20);
        *(long *)(arr + 0x10) = 0;
        sk_x_0036b118(arr);
    }
    return sz;
}

/* ---- Array "move count elements into a new block" helpers.
 * Each computes (end - start) element count, validates it is non-negative and
 * non-overlapping, copies, and releases the source array. Stride varies. ---- */

/* FUN_004567d8  stride 0x178 */
unsigned long sk_arr_move_178(long start, long end, unsigned long dst, long arr)
{
    unsigned long n, src, sz;
    n = end - start;
    if (end < start) { sk_sw_breakpoint(1, 0x456850); }
    if (start > end) { sk_sw_breakpoint(1, 0x456854); }   /* -1 < lVar3 */
    src = arr + start * 0x178 + 0x20;
    sz = dst + n * 0x178;
    if (sz <= src || src + n * 0x178 <= dst) {
        sk_x_0035b67c(dst, src, n, 0x684390);
        sk_x_0036b118(arr);
        return sz;
    }
    sk_sw_breakpoint(1, 0x456858);
    return 0;
}

/* FUN_00456858  stride 0x38 */
unsigned long sk_arr_move_38(long start, long end, unsigned long dst, long arr)
{
    unsigned long n, src, sz;
    n = end - start;
    if (end < start) { sk_sw_breakpoint(1, 0x4568d0); }
    if (start > end) { sk_sw_breakpoint(1, 0x4568d4); }
    src = arr + start * 0x38 + 0x20;
    sz = dst + n * 0x38;
    if (sz <= src || src + n * 0x38 <= dst) {
        sk_x_0035b67c(dst, src, n, 0x684cf0);
        sk_x_0036b118(arr);
        return sz;
    }
    sk_sw_breakpoint(1, 0x4568d8);
    return 0;
}

/* FUN_004568d8  stride 0x20 */
unsigned long sk_arr_move_20(long start, long end, unsigned long dst, long arr)
{
    unsigned long n, src, sz;
    n = end - start;
    if (end < start) { sk_sw_breakpoint(1, 0x456944); }
    if (start > end) { sk_sw_breakpoint(1, 0x456948); }
    src = arr + start * 0x20 + 0x20;
    sz = dst + n * 0x20;
    if (sz <= src || src + n * 0x20 <= dst) {
        sk_x_0035b67c(dst, src, n, 0x685e98);
        sk_x_0036b118(arr);
        return sz;
    }
    sk_sw_breakpoint(1, 0x45694c);
    return 0;
}

/* FUN_0045694c  stride 0x50 */
unsigned long sk_arr_move_50(long start, long end, unsigned long dst, long arr)
{
    unsigned long n, src, sz;
    n = end - start;
    if (end < start) { sk_sw_breakpoint(1, 0x4569c0); }
    if (start > end) { sk_sw_breakpoint(1, 0x4569c4); }
    src = arr + start * 0x50 + 0x20;
    sz = dst + n * 0x50;
    if (sz <= src || src + n * 0x50 <= dst) {
        sk_x_0035b67c(dst, src, n, 0x6850c8);
        sk_x_0036b118(arr);
        return sz;
    }
    sk_sw_breakpoint(1, 0x4569c8);
    return 0;
}

/* FUN_004569c8  stride 0x30 (uses memcpy FUN_00117cc4) */
unsigned long sk_arr_move_30(long start, long end, unsigned long dst, long arr)
{
    unsigned long n, src, sz;
    n = end - start;
    if (end < start) { sk_sw_breakpoint(1, 0x456a38); }
    if (start > end) { sk_sw_breakpoint(1, 0x456a3c); }
    src = arr + start * 0x30 + 0x20;
    sz = dst + n * 0x30;
    if (sz <= src || src + n * 0x30 <= dst) {
        sk_x_00117cc4(dst, src, n * 0x30);
        sk_x_0036b118(arr);
        return sz;
    }
    sk_sw_breakpoint(1, 0x456a40);
    return 0;
}

/* FUN_00456a40  stride 0x20 (second copy of 0x20 with traits 0x683000) */
unsigned long sk_arr_move_20b(long start, long end, unsigned long dst, long arr)
{
    unsigned long n, src, sz;
    n = end - start;
    if (end < start) { sk_sw_breakpoint(1, 0x456aac); }
    if (start > end) { sk_sw_breakpoint(1, 0x456ab0); }
    src = arr + start * 0x20 + 0x20;
    sz = dst + n * 0x20;
    if (sz <= src || src + n * 0x20 <= dst) {
        sk_x_0035b67c(dst, src, n, 0x683000);
        sk_x_0036b118(arr);
        return sz;
    }
    sk_sw_breakpoint(1, 0x456ab4);
    return 0;
}

/* FUN_00456ab4  stride 8 */
unsigned long sk_arr_move_8(long start, long end, unsigned long dst, long arr)
{
    unsigned long n, src, sz;
    n = end - start;
    if (end < start) { sk_sw_breakpoint(1, 0x456b20); }
    if (start > end) { sk_sw_breakpoint(1, 0x456b24); }
    src = arr + start * 8 + 0x20;
    sz = dst + n * 8;
    if (sz <= src || src + n * 8 <= dst) {
        sk_x_0035b67c(dst, src, n, 0x682e08);
        sk_x_0036b118(arr);
        return sz;
    }
    sk_sw_breakpoint(1, 0x456b28);
    return 0;
}

/* FUN_00456b28  stride 0x18 (memcpy) */
unsigned long sk_arr_move_18(long start, long end, unsigned long dst, long arr)
{
    unsigned long n, src, sz;
    n = end - start;
    if (end < start) { sk_sw_breakpoint(1, 0x456b98); }
    if (start > end) { sk_sw_breakpoint(1, 0x456b9c); }
    src = arr + start * 0x18 + 0x20;
    sz = dst + n * 0x18;
    if (sz <= src || src + n * 0x18 <= dst) {
        sk_x_00117cc4(dst, src, n * 0x18);
        sk_x_0036b118(arr);
        return sz;
    }
    sk_sw_breakpoint(1, 0x456ba0);
    return 0;
}

/* FUN_00456ba0  stride 0x20 (with traits string) */
unsigned long sk_arr_move_20c(long start, long end, unsigned long dst, long arr)
{
    unsigned long n, src, sz, traits;
    n = end - start;
    if (end < start) { sk_sw_breakpoint(1, 0x456c34); }
    if (start > end) { sk_sw_breakpoint(1, 0x456c38); }
    src = arr + start * 0x20 + 0x20;
    sz = dst + n * 0x20;
    if (sz <= src || src + n * 0x20 <= dst) {
        traits = sk_x_00002534(0x657b58, 0x5a3630);
        sk_x_0035b67c(dst, src, n, traits);
        sk_x_0036b118(arr);
        return sz;
    }
    sk_sw_breakpoint(1, 0x456c3c);
    return 0;
}

/* FUN_00456c3c  stride 0x10 (with traits string) */
unsigned long sk_arr_move_10(long start, long end, unsigned long dst, long arr)
{
    unsigned long n, src, sz, traits;
    n = end - start;
    if (end < start) { sk_sw_breakpoint(1, 0x456cd0); }
    if (start > end) { sk_sw_breakpoint(1, 0x456cd4); }
    src = arr + start * 0x10 + 0x20;
    sz = dst + n * 0x10;
    if (sz <= src || src + n * 0x10 <= dst) {
        traits = sk_x_00002534(0x657ae8, 0x5a3528);
        sk_x_0035b67c(dst, src, n, traits);
        sk_x_0036b118(arr);
        return sz;
    }
    sk_sw_breakpoint(1, 0x456cd8);
    return 0;
}

/* FUN_00456cd8 @ 0x00456cd8  (est. sk_arr_copy_178)
 * Ghidra: void FUN_00456cd8(src, n, dst)
 * Copies n elements of stride 0x178 from src to dst when non-overlapping
 * (or same address); traps on negative n.
 * Confidence: low
 */
void sk_arr_copy_178(unsigned long src, long n, unsigned long dst)
{
    if (n < 0) { sk_sw_breakpoint(1, 0x456d14); }
    if (dst != src || src + n * 0x178 <= dst) {
        sk_x_00117d14(dst, src, n * 0x178);
    }
}

/* FUN_00456d50 @ 0x00456d50  (est. sk_arr_copy_50)
 * Ghidra: void FUN_00456d50(src, n, dst)
 * Copies n elements of stride 0x50 when ranges do not overlap.
 * Confidence: low
 */
void sk_arr_copy_50(unsigned long src, long n, unsigned long dst)
{
    if (n < 0) { sk_sw_breakpoint(1, 0x456d8c); }
    if (dst + n * 0x50 <= src || src + n * 0x50 <= dst) {
        sk_x_0035b67c(dst, src, n, 0x6850c8);
        return;
    }
    sk_sw_breakpoint(1, 0x456d90);
}

/* ---- Character-buffer access helper. The 0x456d90..0x457650 group compare a
 * byte stream (a tagged/codepoint-class buffer, param_1/param_2 with segment
 * tags) against a stored class string, byte by byte, using:
 *   - FUN_002a9ba8 / FUN_002b141c: resolve the segment base for a tagged ptr
 *   - FUN_0001da84: extract the low bits / pointer form
 *   - class value read via (base + idx) with 4-class bucket comparison.
 * The "0xf" cursor is the initial low nibble sentinel; uVar9/uVar10 select the
 * 4-bit class-width (param>>0x3b & 1, default 1). */

/* FUN_00456d90 @ 0x00456d90  (est. sk_class_str_contains)
 * Ghidra: bool FUN_00456d90(a,b,class_str)
 * Returns true if the stored class string (n bytes at class_str+0x20, count
 * at +0x10) is a prefix of the byte stream characterised by (a,b). Compares
 * each class byte in sequence, terminating on end-of-string.
 * Confidence: low
 */
bool sk_class_str_contains(unsigned long a, unsigned long b, long cls)
{
    unsigned long cnt, clen, ci, cur, idx, u1, u14;
    char c_cls, c_data;

    clen = *(unsigned long *)(cls + 0x10);
    u1 = a & 0xffffffffffff;
    if ((b & 0x2000000000000000) != 0) u1 = b >> 0x38 & 0xf;
    u14 = u1 * 4;
    cur = 0xf;
    ci = 0;
    for (;;) {
        if (ci == clen) { c_cls = '\0'; cur = clen; }
        else {
            if (clen <= ci) { sk_sw_breakpoint(1, 0x456fa0); }
            c_cls = *(char *)(cls + 0x20 + ci);
            cur = ci + 1;
        }
        idx = cur >> 0xe;
        if (idx == u14) {
            c_data = '\0';
        } else {
            /* read data byte at class index idx from the (a,b) stream */
            c_data = sk_class_byte(a, b, cur, idx);
            if ((cur & 0xc) == 4 << (cur >> 0x3b & 1)) cur = sk_x_0001da84(cur, a, b);
            if ((b >> 0x3c & 1) == 0) cur = 0x10004 + (cur & 0xffffffffffff0000);
            else { if (u1 <= (cur >> 0x10)) { sk_sw_breakpoint(1, 0x456fa8); } cur = sk_x_002b141c(cur, a, b); }
        }
        if (ci == clen) return idx == u14;
        if (idx == u14) break;
        ci = cur;
        if (c_cls != c_data) return false;
    }
    return false;
}

/* FUN_00456fa8 @ 0x00456fa8  (est. sk_class_range_contains)
 * Ghidra: bool FUN_00456fa8(a,b,p3,p4)
 * Same prefix-compare over the byte range [p3, p4) instead of a stored string.
 * Confidence: low
 */
bool sk_class_range_contains(unsigned long a, unsigned long b, char *p3, char *p4)
{
    unsigned long u1, u9, cur, idx, u11;
    char c_cls, c_data;
    bool done;

    u1 = a & 0xffffffffffff;
    if ((b & 0x2000000000000000) != 0) u1 = b >> 0x38 & 0xf;
    u9 = u1 * 4;
    cur = 0xf;
    for (;;) {
        if (p3 == 0) { c_cls = '\0'; done = true; }
        else {
            if (p4 == 0) { sk_sw_breakpoint(1, 0x4571b0); }
            if (p3 == p4) { c_cls = '\0'; done = true; p3 = p4; }
            else {
                if (p4 <= p3) { sk_sw_breakpoint(1, 0x4571a8); }
                done = false;
                c_cls = *p3;
                p3 = p3 + 1;
            }
        }
        idx = cur >> 0xe;
        if (idx == u9) {
            c_data = '\0';
        } else {
            c_data = sk_class_byte(a, b, cur, idx);
            if ((cur & 0xc) == 4 << (cur >> 0x3b & 1)) cur = sk_x_0001da84(cur, a, b);
            if ((b >> 0x3c & 1) == 0) cur = 0x10004 + (cur & 0xffffffffffff0000);
            else { if (u1 <= (cur >> 0x10)) { sk_sw_breakpoint(1, 0x4571ac); } cur = sk_x_002b141c(cur, a, b); }
        }
        if (done) return idx == u9;
        if (idx == u9) break;
        if (c_cls != c_data) return false;
    }
    return false;
}

/* FUN_004571b0 @ 0x004571b0  (est. sk_class_stream_eq)
 * Ghidra: undefined8 FUN_004571b0(p1, p2, a, b)
 * Compares the stream (a,b) against the byte range [p1,p2). Returns 1 on
 * equal, 0 on mismatch. Uses the same class-bucket reads.
 * Confidence: low
 */
unsigned long sk_class_stream_eq(char *p1, char *p2, unsigned long a, unsigned long b)
{
    unsigned long u2, cur, idx, u13, u14;
    char c_cls, c_data;
    bool got;
    char *pc;

    u2 = a & 0xffffffffffff;
    if ((b & 0x2000000000000000) != 0) u2 = b >> 0x38 & 0xf;
    cur = 0xf;
    for (;;) {
        u14 = cur >> 0xe;
        if (u14 == u2 * 4) {
            c_cls = '\0';
            if (p1 == 0) { c_data = '\0'; got = false; u13 = 1; pc = p1; }
            else {
                if (p2 == 0) { sk_sw_breakpoint(1, 0x4573b0); }
                if (p1 == p2) { c_data = '\0'; got = false; u13 = 1; pc = p2; }
                else {
                    if (p2 <= p1) { sk_sw_breakpoint(1, 0x4573a8); }
                    u13 = 0; pc = p1 + 1; c_data = *p1; got = true;
                }
            }
        } else {
            c_cls = sk_class_byte(a, b, cur, u14);
            if ((cur & 0xc) == 4 << (cur >> 0x3b & 1)) cur = sk_x_0001da84(cur, a, b);
            if ((b >> 0x3c & 1) == 0) cur = 0x10004 + (cur & 0xffffffffffff0000);
            else { if (u2 <= (cur >> 0x10)) { sk_sw_breakpoint(1, 0x4573ac); } cur = sk_x_002b141c(cur, a, b); }
            if (p1 == 0) { c_data = '\0'; got = false; u13 = 1; pc = p1; }
            else {
                if (p2 == 0) { sk_sw_breakpoint(1, 0x4573b0); }
                if (p1 == p2) { c_data = '\0'; got = false; u13 = 1; pc = p2; }
                else {
                    if (p2 <= p1) { sk_sw_breakpoint(1, 0x4573a8); }
                    u13 = 0; pc = p1 + 1; c_data = *p1; got = true;
                }
            }
        }
        if (u14 == u2 * 4) return u13;
        if (c_cls != c_data || !got) return 0;
        p1 = pc;
    }
}

/* sk_class_byte — local helper used by the class-comparison group: reads the
 * class byte at index idx of the stream (a,b). Faithful to the decompiled
 * shared sequence. */
static char sk_class_byte(unsigned long a, unsigned long b, unsigned long cur, unsigned long idx)
{
    unsigned long base;
    char c;

    if ((b >> 0x3c & 1) == 0) {
        if ((b >> 0x3d & 1) == 0) {
            base = (b & 0xfffffffffffffff) + 0x20;
            if ((a >> 0x3c & 1) == 0) base = sk_x_002a9ba8(a, b);
            c = *(char *)(base + idx);
        } else {
            base = (unsigned long)&a + (b & 0xffffffffffffff);
            c = *(char *)(base + idx);
        }
    } else {
        c = (char)sk_x_002b141c(idx, a, b);
    }
    return c;
}

/* FUN_004573b0 @ 0x004573b0  (est. sk_class2_range_eq)
 * Ghidra: undefined8 FUN_004573b0(p1,a,b,c,d,e,f)
 * Two-stream class comparison: compares stream (c,d) at cursor p1 against
 * stream (e,f), returning 1 when a 0x4000-aligned window matches and 0
 * otherwise. Uses FUN_002b5ba0 for the second stream's class fetch.
 * Confidence: low
 */
unsigned long sk_class2_range_eq(unsigned char *p1, unsigned long a, unsigned long b,
                                 unsigned long c, unsigned long d, unsigned long e, unsigned long f)
{
    unsigned long u1, u2, cur, idx, u12, u11;
    char c4, c5;
    unsigned long p8;

    u1 = e & 0xffffffffffff;
    if ((f & 0x2000000000000000) != 0) u1 = f >> 0x38 & 0xf;
    cur = 0xf;
    p8 = (unsigned long)p1;
    for (;;) {
        u12 = cur >> 0xe;
        if (u12 == u1 * 4) {
            if (((unsigned long)p8 ^ a) < 0x4000) return 1;
            c4 = '\0';
        } else {
            c4 = sk_class_byte(e, f, cur, u12);
            if ((cur & 0xc) == 4 << (cur >> 0x3b & 1)) { cur = sk_x_0001da84(cur, e, f); if ((f >> 0x3c & 1) != 0) { if (u1 <= (cur >> 0x10)) { sk_sw_breakpoint(1, 0x45764c); } cur = sk_x_002b141c(cur, e, f); } }
            else if ((f >> 0x3c & 1) != 0) { if (u1 <= (cur >> 0x10)) { sk_sw_breakpoint(1, 0x45764c); } cur = sk_x_002b141c(cur, e, f); }
            else cur = 0x10004 + (cur & 0xffffffffffff0000);
            if (((unsigned long)p8 ^ a) < 0x4000) { return 0; }
        }
        c5 = (char)sk_x_002b5ba0(p8, a, b, c, d);
        if ((p8 & 0xc) == 4 << (p8 >> 0x3b & 1)) { p8 = sk_x_0001da84(p8, c, d); if ((d >> 0x3c & 1) != 0) { if (u2 <= (p8 >> 0x10)) { sk_sw_breakpoint(1, 0x457650); } p8 = sk_x_002b141c(p8, c, d); } }
        else if ((d >> 0x3c & 1) != 0) { if (u2 <= (p8 >> 0x10)) { sk_sw_breakpoint(1, 0x457650); } p8 = sk_x_002b141c(p8, c, d); }
        else p8 = 0x10004 + (p8 & 0xffffffffffff0000);
        if ((u12 == u1 * 4) || (c4 != c5)) return 0;
    }
}

/* FUN_00457650 @ 0x00457650  (est. sk_class2_reverse_eq)
 * Ghidra: undefined8 FUN_00457650(a,b,p3,c,d,e,f)
 * Reverse two-stream class comparison over [p3..c): compares stream (a,b)
 * class against stream (e,f) class in the 0x4000 window.
 * Confidence: low
 */
unsigned long sk_class2_reverse_eq(unsigned long a, unsigned long b, unsigned char *p3,
                                   unsigned long c, unsigned long d, unsigned long e, unsigned long f)
{
    unsigned long u1, u2, cur, idx, u13, u12;
    char c4, c5;
    unsigned long p6;

    u1 = e & 0xffffffffffff;
    if ((f & 0x2000000000000000) != 0) u1 = f >> 0x38 & 0xf;
    u2 = a & 0xffffffffffff;
    if ((b & 0x2000000000000000) != 0) u2 = b >> 0x38 & 0xf;
    sk_x_0036b270(b);
    cur = 0xf;
    p6 = (unsigned long)p3;
    for (;;) {
        u13 = (unsigned long)p6 ^ c;
        if (u13 < 0x4000) {
            if (u2 << 2 == (cur >> 0xe)) return 1;
            c4 = '\0';
        } else {
            c4 = sk_class_byte(e, f, cur, cur >> 0xe);
            if ((p6 & 0xc) == 4 << (p6 >> 0x3b & 1)) p6 = sk_x_0001da84(p6, e, f);
            if ((f >> 0x3c & 1) == 0) p6 = 0x10004 + (p6 & 0xffffffffffff0000);
            else { if (u1 <= (p6 >> 0x10)) { sk_sw_breakpoint(1, 0x4578dc); } p6 = sk_x_002b141c(p6, e, f); }
            if (u2 << 2 == (cur >> 0xe)) return 0;
        }
        c5 = sk_class_byte(a, b, cur, cur >> 0x10);
        if ((cur & 0xc) == 4 << (cur >> 0x3b & 1)) { cur = sk_x_0001da84(cur, a, b); if ((b >> 0x3c & 1) != 0) { if (u2 <= (cur >> 0x10)) { sk_sw_breakpoint(1, 0x4578d8); } cur = sk_x_002b141c(cur, a, b); } }
        else if ((b >> 0x3c & 1) != 0) { if (u2 <= (cur >> 0x10)) { sk_sw_breakpoint(1, 0x4578d8); } cur = sk_x_002b141c(cur, a, b); }
        else cur = 0x10004 + (cur & 0xffffffffffff0000);
        if ((u13 < 0x4000) || (c4 != c5)) return 0;
    }
}
