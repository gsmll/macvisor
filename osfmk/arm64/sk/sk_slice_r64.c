/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel, GL1,
 * arm64e, image base 0) — the cL4 microkernel. Ground truth: Ghidra FUN_ names +
 * addresses in cl4_kernel.raw. Version "cL4 microkernel (cL4 (679.100.61))".
 * All names are estimates unless string/header-matched.
 * Slice 0x451a10-0x458d40 (SKR64): the embedded Swift-runtime Character / string
 * / Unicode layer. The head (0x451a10-0x4540xx) is the Character.Unicode.Script
 * and GeneralCategory enum-description layer: it maps the small Unicode
 * "General Category" codes (Cc, Cf, Cn, ...) to their 16-byte small-string
 * names (0x451a64), builds the static Unicode Block-name lookup table
 * (0x451f24), and provides the Script-name accessor (0x45399c) plus the Swift
 * Collection/Sequence conformance witnesses (0x451d30/0x451e84 ...). The tail
 * (0x455xxx-0x458d40) is the Array/String buffer layer: reserve-capacity
 * helpers for every element stride (0x455de4..0x4561cc), the buffer "copy /
 * release / retain" closures (0x4567d8..0x456d50), the String equality /
 * hasPrefix / hasSuffix / isEqual primitives (0x456d90, 0x456fa8, 0x4571b0,
 * 0x4573b0, 0x457650), an integer-from-string parser with radix and sign
 * (0x457bec), the array-element release/dealloc destructors (0x4580b4..0x4587
 * 80), and the small enum-boxing retain/release helpers (0x4588cc/0x458940).
 */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "sk_internal.h"

typedef uint64_t word_t;
typedef int64_t  sword_t;
typedef unsigned char byte;

/* 16-byte value returned in x0/x1 by many Swift helpers. */
typedef struct { unsigned long lo, hi; } cl4_pair_t;

/* SoftwareBreakpoint(1, addr) fail-closed trap. */
#define CL4_SW_BP(addr)  __asm__ volatile("brk #1" ::: "memory")

/* ---- Out-of-range cL4 helpers referenced by this region (FUN_ in comment).
 * Declared with unspecified-argument prototype (matching slice conventions);
 * their bodies are reconstructed by the range worker that owns them. ---- */
extern unsigned long sk_x_00002534();   /* FUN_00002534 (type metadata) */
extern unsigned long sk_x_000026e8();   /* FUN_000026e8 (dealloc) */
extern unsigned long sk_x_00002818();   /* FUN_00002818 */
extern unsigned long sk_x_00002874();   /* FUN_00002874 (fatal msg) */
extern unsigned long sk_x_000126e8();   /* FUN_000126e8 (thunk alloc) */
extern cl4_pair_t sk_x_0001d4a0();      /* FUN_0001d4a0 (16-byte) */
extern unsigned long sk_x_0001d648();   /* FUN_0001d648 */
extern unsigned long sk_x_0001da84();   /* FUN_0001da84 (string iter) */
extern unsigned long sk_x_000262fc();   /* FUN_000262fc */
extern unsigned long sk_x_00027754();   /* FUN_00027754 */
extern unsigned long sk_x_00027788();   /* FUN_00027788 */
extern unsigned long sk_x_00069770();   /* FUN_00069770 */
extern unsigned long sk_x_00069970();   /* FUN_00069970 */
extern unsigned long sk_x_000699a4();   /* FUN_000699a4 */
extern unsigned long sk_x_000699d8();   /* FUN_000699d8 */
extern unsigned long sk_x_0006a4c0();   /* FUN_0006a4c0 */
extern unsigned long sk_x_0006b3f4();   /* FUN_0006b3f4 */
extern unsigned long sk_x_0006b42c();   /* FUN_0006b42c (16-byte) */
extern unsigned long sk_x_0006b6e0();   /* FUN_0006b6e0 */
extern unsigned long sk_x_00077024();   /* FUN_00077024 */
extern unsigned long sk_x_000776cc();   /* FUN_000776cc */
extern unsigned long sk_x_0007c028();   /* FUN_0007c028 */
extern unsigned long sk_x_0007c1a4();   /* FUN_0007c1a4 */
extern cl4_pair_t sk_x_0007c1c4();      /* FUN_0007c1c4 (16-byte) */
extern unsigned long sk_x_00084174();   /* FUN_00084174 */
extern unsigned long sk_x_00084220();   /* FUN_00084220 */
extern unsigned long sk_x_00084234();   /* FUN_00084234 */
extern unsigned long sk_x_0008e500();   /* FUN_0008e500 */
extern cl4_pair_t sk_x_0008e518();      /* FUN_0008e518 (16-byte) */
extern unsigned long sk_x_000a68c4();   /* FUN_000a68c4 */
extern unsigned long sk_x_000a68f4();   /* FUN_000a68f4 */
extern unsigned long sk_x_000a6f88();   /* FUN_000a6f88 */
extern unsigned long sk_x_000aa4ec();   /* FUN_000aa4ec */
extern unsigned long sk_x_000b43d0();   /* FUN_000b43d0 */
extern unsigned long sk_x_000b43f4();   /* FUN_000b43f4 */
extern unsigned long sk_x_00100efc();   /* FUN_00100efc */
extern unsigned long sk_x_00117cc4();   /* FUN_00117cc4 (memcpy) */
extern unsigned long sk_x_00117d14();   /* FUN_00117d14 (memmove) */
extern unsigned long sk_x_001a29a0();   /* FUN_001a29a0 (thunk) */
extern unsigned long sk_x_001afa84();   /* FUN_001afa84 (noreturn trap) */
extern unsigned long sk_x_001b9084();   /* FUN_001b9084 (msg) */
extern cl4_pair_t sk_x_001e9c78();      /* FUN_001e9c78 (16-byte) */
extern unsigned long sk_x_00200b38();   /* FUN_00200b38 */
extern unsigned long sk_x_00200bd0();   /* FUN_00200bd0 */
extern unsigned long sk_x_00200bf4();   /* FUN_00200bf4 */
extern unsigned long sk_x_002298d4();   /* FUN_002298d4 (dealloc) */
extern unsigned long sk_x_0022995c();   /* FUN_0022995c */
extern unsigned long sk_x_00229a3c();   /* FUN_00229a3c */
extern cl4_pair_t sk_x_0022d2f4();      /* FUN_0022d2f4 (16-byte) */
extern unsigned long sk_x_002a4468();   /* FUN_002a4468 */
extern cl4_pair_t sk_x_002a9ba8();      /* FUN_002a9ba8 (16-byte) */
extern unsigned long sk_x_002ad78c();   /* FUN_002ad78c */
extern unsigned long sk_x_002ad95c();   /* FUN_002ad95c */
extern unsigned long sk_x_002b141c();   /* FUN_002b141c (string deref) */
extern unsigned long sk_x_002b5ba0();   /* FUN_002b5ba0 (string read) */
extern unsigned long sk_x_002b8444();   /* FUN_002b8444 */
extern unsigned long sk_x_00310c44();   /* FUN_00310c44 */
extern cl4_pair_t sk_x_00310d68();      /* FUN_00310d68 (16-byte) */
extern unsigned long sk_x_00310d98();   /* FUN_00310d98 */
extern unsigned long sk_x_0031b760();   /* FUN_0031b760 */
extern unsigned long sk_x_0031b778();   /* FUN_0031b778 */
extern unsigned long sk_x_00349a18();   /* FUN_00349a18 */
extern unsigned long sk_x_0034b05c();   /* FUN_0034b05c */
extern cl4_pair_t sk_x_003504d0();      /* FUN_003504d0 (16-byte) */
extern cl4_pair_t sk_x_00350530();      /* FUN_00350530 (16-byte) */
extern unsigned long sk_x_00350560();   /* FUN_00350560 */
extern cl4_pair_t sk_x_00350618();      /* FUN_00350618 (16-byte) */
extern cl4_pair_t sk_x_003507bc();      /* FUN_003507bc (16-byte) */
extern unsigned long sk_x_00350980();   /* FUN_00350980 */
extern unsigned long sk_x_0035098c();   /* FUN_0035098c */
extern unsigned long sk_x_003509c8();   /* FUN_003509c8 */
extern unsigned long sk_x_00350a04();   /* FUN_00350a04 */
extern unsigned long sk_x_003514e8();   /* FUN_003514e8 */
extern cl4_pair_t sk_x_0035199c();      /* FUN_0035199c (16-byte) */
extern unsigned long sk_x_00351db4();   /* FUN_00351db4 */
extern cl4_pair_t sk_x_00351e3c();      /* FUN_00351e3c (16-byte) */
extern unsigned long sk_x_00352840();   /* FUN_00352840 */
extern unsigned long sk_x_00354828();   /* FUN_00354828 */
extern unsigned long sk_x_00355968();   /* FUN_00355968 */
extern unsigned long sk_x_00356c6c();   /* FUN_00356c6c */
extern unsigned long sk_x_00359208();   /* FUN_00359208 */
extern unsigned long sk_x_003593c0();   /* FUN_003593c0 */
extern unsigned long sk_x_0035b67c();   /* FUN_0035b67c (memcpy) */
extern unsigned long sk_x_0035bc70();   /* FUN_0035bc70 */
extern unsigned long sk_x_003625e4();   /* FUN_003625e4 */
extern unsigned long sk_x_0036a940();   /* FUN_0036a940 (buffer alloc) */
extern unsigned long sk_x_0036b118();   /* FUN_0036b118 (release) */
extern unsigned long sk_x_0036b270();   /* FUN_0036b270 (retain) */
extern cl4_pair_t sk_x_00371950();      /* FUN_00371950 (16-byte) */
extern unsigned long sk_x_00377824();   /* FUN_00377824 */
extern unsigned long sk_x_00377bec();   /* FUN_00377bec */
extern unsigned long sk_x_003a25d4();   /* FUN_003a25d4 (release) */
extern unsigned long sk_x_003a261c();   /* FUN_003a261c */
extern unsigned long sk_x_00410414();   /* FUN_00410414 */
extern unsigned long sk_x_0041360c();   /* FUN_0041360c */
extern unsigned long sk_x_00415570();   /* FUN_00415570 */
extern unsigned long sk_x_0041577c();   /* FUN_0041577c */
extern unsigned long sk_x_00415aa4();   /* FUN_00415aa4 */
extern unsigned long sk_x_0041b3d4();   /* FUN_0041b3d4 */
extern unsigned long sk_x_0042d720();   /* FUN_0042d720 */
extern cl4_pair_t sk_x_00447144();      /* FUN_00447144 (16-byte) */
extern unsigned long sk_x_0044f298();   /* FUN_0044f298 */
extern cl4_pair_t sk_x_00450848();      /* FUN_00450848 (16-byte) */
extern unsigned long sk_x_00458eec();   /* FUN_00458eec */
extern unsigned long sk_x_00458f88();   /* FUN_00458f88 */
extern unsigned long sk_x_004594f4();   /* FUN_004594f4 */
extern unsigned long sk_x_0045a6f4();   /* FUN_0045a6f4 */
extern unsigned long sk_x_0045a980();   /* FUN_0045a980 */
extern unsigned long sk_x_0045b7f4();   /* FUN_0045b7f4 */
extern unsigned long sk_x_0045b824();   /* FUN_0045b824 */
extern unsigned long sk_x_0045bb84();   /* FUN_0045bb84 */
extern unsigned long sk_x_0045bbb4();   /* FUN_0045bbb4 */
extern unsigned long sk_x_0045be8c();   /* FUN_0045be8c */
extern unsigned long sk_x_0045c258();   /* FUN_0045c258 */
extern unsigned long sk_x_0045c2a8();   /* FUN_0045c2a8 */
extern unsigned long sk_x_0045c61c();   /* FUN_0045c61c */
extern unsigned long sk_x_0045d028();   /* FUN_0045d028 */
extern unsigned long sk_x_0045d2e4();   /* FUN_0045d2e4 */
extern unsigned long sk_x_0045df3c();   /* FUN_0045df3c */
extern unsigned long sk_x_0045df90();   /* FUN_0045df90 */
extern unsigned long sk_x_0045eb38();   /* FUN_0045eb38 */
extern unsigned long sk_x_0045eb6c();   /* FUN_0045eb6c */
extern unsigned long sk_x_00460ddc();   /* FUN_00460ddc */
extern unsigned long sk_x_00461d68();   /* FUN_00461d68 */
extern unsigned long sk_x_00462ee8();   /* FUN_00462ee8 */
extern unsigned long sk_x_00463ad4();   /* FUN_00463ad4 */
extern unsigned long sk_x_00463b08();   /* FUN_00463b08 */
extern unsigned long sk_x_00463b2c();   /* FUN_00463b2c */
extern unsigned long sk_x_00463b50();   /* FUN_00463b50 */
extern unsigned long sk_x_00463b98();   /* FUN_00463b98 */
extern unsigned long sk_x_00463c18();   /* FUN_00463c18 */
extern unsigned long sk_x_00463c38();   /* FUN_00463c38 */
extern unsigned long sk_x_00463c58();   /* FUN_00463c58 */
extern unsigned long sk_x_00463c78();   /* FUN_00463c78 */
extern unsigned long sk_x_00463c98();   /* FUN_00463c98 */
extern unsigned long sk_x_00463cfc();   /* FUN_00463cfc */
extern unsigned long sk_x_00463d1c();   /* FUN_00463d1c */
extern unsigned long sk_x_00463d3c();   /* FUN_00463d3c */
extern unsigned long sk_x_00463d5c();   /* FUN_00463d5c */
extern unsigned long sk_x_00463d7c();   /* FUN_00463d7c */
extern unsigned long sk_x_00463d9c();   /* FUN_00463d9c */
extern unsigned long sk_x_00464000();   /* FUN_00464000 */
extern unsigned long sk_x_0046414c();   /* FUN_0046414c */
extern unsigned long sk_x_004641a0();   /* FUN_004641a0 */
extern unsigned long sk_x_004641b8();   /* FUN_004641b8 */
extern unsigned long sk_x_004641d0();   /* FUN_004641d0 */
extern unsigned long sk_x_004643cc();   /* FUN_004643cc */
extern unsigned long sk_x_004643d8();   /* FUN_004643d8 */
extern unsigned long sk_x_004643f0();   /* FUN_004643f0 */
extern unsigned long sk_x_00464408();   /* FUN_00464408 */
extern unsigned long sk_x_00464420();   /* FUN_00464420 */
extern unsigned long sk_x_00464438();   /* FUN_00464438 */
extern unsigned long sk_x_00464450();   /* FUN_00464450 */
extern unsigned long sk_x_00464468();   /* FUN_00464468 */
extern unsigned long sk_x_00464480();   /* FUN_00464480 */
extern unsigned long sk_x_00464688();   /* FUN_00464688 */
extern unsigned long sk_x_00464694();   /* FUN_00464694 */
extern unsigned long sk_x_004646ac();   /* FUN_004646ac */
extern unsigned long sk_x_004646c4();   /* FUN_004646c4 */
extern unsigned long sk_x_004646dc();   /* FUN_004646dc */
extern unsigned long sk_x_004646f4();   /* FUN_004646f4 */
extern unsigned long sk_x_0046470c();   /* FUN_0046470c */
extern unsigned long sk_x_00464724();   /* FUN_00464724 */
extern unsigned long sk_x_0046473c();   /* FUN_0046473c */
extern unsigned long sk_x_00464754();   /* FUN_00464754 */
extern unsigned long sk_x_0046476c();   /* FUN_0046476c */
extern unsigned long sk_x_00464784();   /* FUN_00464784 */
extern unsigned long sk_x_0046479c();   /* FUN_0046479c */
extern unsigned long sk_x_00464b40();   /* FUN_00464b40 */
extern unsigned long sk_x_00464b54();   /* FUN_00464b54 */
extern unsigned long sk_x_00464b68();   /* FUN_00464b68 */
extern unsigned long sk_x_00464b7c();   /* FUN_00464b7c */
extern unsigned long sk_x_00464b90();   /* FUN_00464b90 */
extern unsigned long sk_x_00464ba4();   /* FUN_00464ba4 */
extern unsigned long sk_x_00464bf4();   /* FUN_00464bf4 */
extern unsigned long sk_x_00464c08();   /* FUN_00464c08 */
extern unsigned long sk_x_00464c1c();   /* FUN_00464c1c */
extern unsigned long sk_x_00464c30();   /* FUN_00464c30 */
extern unsigned long sk_x_00464c44();   /* FUN_00464c44 */
extern unsigned long sk_x_00464c58();   /* FUN_00464c58 */
extern unsigned long sk_x_00464c6c();   /* FUN_00464c6c */
extern unsigned long sk_x_00464c80();   /* FUN_00464c80 */
extern unsigned long sk_x_00464c94();   /* FUN_00464c94 */
extern unsigned long sk_x_00464ca8();   /* FUN_00464ca8 */
extern unsigned long sk_x_00464cbc();   /* FUN_00464cbc */
extern unsigned long sk_x_00464cd0();   /* FUN_00464cd0 */
extern unsigned long sk_x_00464ee4();   /* FUN_00464ee4 */
extern unsigned long sk_x_00464f04();   /* FUN_00464f04 */
extern unsigned long sk_x_00464f14();   /* FUN_00464f14 */
extern unsigned long sk_x_00464f64();   /* FUN_00464f64 */
extern unsigned long sk_x_00464f74();   /* FUN_00464f74 */
extern unsigned long sk_x_00464fa4();   /* FUN_00464fa4 */
extern unsigned long sk_x_00464fb4();   /* FUN_00464fb4 */
extern unsigned long sk_x_00464fe0();   /* FUN_00464fe0 */
extern unsigned long sk_x_00464ff0();   /* FUN_00464ff0 */
extern unsigned long sk_x_00465000();   /* FUN_00465000 */
extern unsigned long sk_x_00465028();   /* FUN_00465028 */
extern unsigned long sk_x_004651d4();   /* FUN_004651d4 */
extern unsigned long sk_x_004651e4();   /* FUN_004651e4 */
extern unsigned long sk_x_004651f4();   /* FUN_004651f4 */
extern unsigned long sk_x_00465204();   /* FUN_00465204 */
extern unsigned long sk_x_00465214();   /* FUN_00465214 */
extern unsigned long sk_x_00465224();   /* FUN_00465224 */
extern unsigned long sk_x_00465240();   /* FUN_00465240 */
extern unsigned long sk_x_004652d4();   /* FUN_004652d4 */
extern unsigned long sk_x_00465428();   /* FUN_00465428 */
extern unsigned long sk_x_004659e0();   /* FUN_004659e0 */
extern unsigned long sk_x_004659e8();   /* FUN_004659e8 */
extern unsigned long sk_x_00465a38();   /* FUN_00465a38 */
extern unsigned long sk_x_00465ab8();   /* FUN_00465ab8 */
extern unsigned long sk_x_00465b64();   /* FUN_00465b64 */
extern unsigned long sk_x_00465b98();   /* FUN_00465b98 */
extern unsigned long sk_x_00465be0();   /* FUN_00465be0 */
extern unsigned long sk_x_00465bf4();   /* FUN_00465bf4 */
extern cl4_pair_t sk_x_00465ed4();      /* FUN_00465ed4 (16-byte) */
extern unsigned long sk_x_004661b8();   /* FUN_004661b8 */
extern unsigned long sk_x_004662b8();   /* FUN_004662b8 */
extern unsigned long sk_x_004663e0();   /* FUN_004663e0 */
extern unsigned long sk_x_0046647c();   /* FUN_0046647c */
extern unsigned long sk_x_004665bc();   /* FUN_004665bc */
extern cl4_pair_t sk_x_004665e8();      /* FUN_004665e8 (16-byte) */
extern unsigned long sk_x_006850c8();   /* FUN_006850c8 */

/* Global data slots referenced by this slice (Ghidra names in comments). */
extern word_t DAT_00658cf0;   /* Swift runtime dispatch slot */
extern word_t DAT_00611b24;   /* element tag / metadata word */
extern word_t DAT_00657778;   /* empty-buffer sentinel */
extern word_t DAT_00697261;   /* raw string bytes ("ira" tag) */
extern word_t DAT_005a3a50;   /* operator-name table base */
extern word_t DAT_0010f800;   /* scalar UTF-32 range table */

/* Retain/release of the (Swift) object at a given address. */
#define CL4_OBJ_RETAIN(p)  sk_x_0036b270((unsigned long)(p))
#define CL4_OBJ_RELEASE(p) sk_x_0036b118((unsigned long)(p))
#define CL4_RELEASE(p)     sk_x_003a25d4((unsigned long)(p))

/* ---- In-slice forward declarations (bodies follow in address order). ---- */
static cl4_pair_t sk_gencat_name_00451a64(word_t param_1);
static cl4_pair_t sk_script_name_0045399c(word_t param_1);
static long sk_arr_reserve_00455de4(long param_1, long param_2);
static long sk_arr_reserve_00455e60(long param_1, long param_2);
static long sk_arr_reserve_00455ee4(long param_1, long param_2);
static long sk_arr_reserve_00455f60(long param_1, long param_2);
static long sk_arr_reserve_00455fe4(long param_1, long param_2);
static long sk_arr_reserve_00456068(long param_1, long param_2);
static long sk_arr_reserve_004560ec(long param_1, long param_2);
static long sk_arr_reserve_00456158(long param_1, long param_2);
static long sk_arr_reserve_004561cc(long param_1, long param_2);
static long sk_arr_ensure_0045636c(word_t param_1, long param_2, word_t param_3, long param_4);
static long sk_arr_grow_00456420(word_t param_1, word_t param_2, word_t param_3, long param_4);
static long sk_arr_ensure2_004564e4(word_t param_1, long param_2, word_t param_3, long param_4);
static long sk_arr_ensure3_0045659c(word_t param_1, long param_2, word_t param_3, long param_4);
static long sk_arr_grow2_00456650(word_t param_1, word_t param_2, word_t param_3, long param_4);
static long sk_arr_grow3_00456714(word_t param_1, word_t param_2, word_t param_3, long param_4);
static cl4_pair_t sk_str_parse_int_00457bec(byte *param_1, long param_2, long param_3);
static bool sk_str_eql_00456d90(word_t param_1, word_t param_2, long param_3);

/* ===================================================================== *
 * Function bodies (address order)
 * ===================================================================== */
/* String constants (Unicode block / script names). The literal text is the
 * block name; the symbol keeps the Ghidra s_ name + address. */
static const char s_Adlam_005dd8cb[] = "Adlam";
static const char s_Aegean_Numbers_005dee23[] = "Aegean Numbers";
static const char s_Alchemical_Symbols_005df3f0[] = "Alchemical Symbols";
static const char s_Alphabetic_Presentation_Forms_005decd0[] = "Alphabetic Presentation Forms";
static const char s_Anatolian_Hieroglyphs_005dd8e0[] = "Anatolian Hieroglyphs";
static const char s_Ancient_Greek_Musical_Notation_005df180[] = "Ancient Greek Musical Notation";
static const char s_Ancient_Greek_Numbers_005dee40[] = "Ancient Greek Numbers";
static const char s_Ancient_Symbols_005dee56[] = "Ancient Symbols";
static const char s_Arabic_005dd8f6[] = "Arabic";
static const char s_Arabic_Extended_A_005de350[] = "Arabic Extended A";
static const char s_Arabic_Extended_B_005de330[] = "Arabic Extended B";
static const char s_Arabic_Mathematical_Alphabetic_S_005df2e0[] = "Arabic Mathematical Alphabetic S";
static const char s_Arabic_Presentation_Forms_A_005decf0[] = "Arabic Presentation Forms A";
static const char s_Arabic_Presentation_Forms_B_005deda0[] = "Arabic Presentation Forms B";
static const char s_Arabic_Supplement_005de2f0[] = "Arabic Supplement";
static const char s_Armenian_005dd8fd[] = "Armenian";
static const char s_Arrows_005de600[] = "Arrows";
static const char s_Avestan_005dd906[] = "Avestan";
static const char s_Balinese_005dd90e[] = "Balinese";
static const char s_Bamum_005dd917[] = "Bamum";
static const char s_Bamum_Supplement_005df030[] = "Bamum Supplement";
static const char s_Basic_Latin_005de200[] = "Basic Latin";
static const char s_Bassa_Vah_005dd91d[] = "Bassa Vah";
static const char s_Batak_005dd927[] = "Batak";
static const char s_Bengali_005dd92d[] = "Bengali";
static const char s_Bhaiksuki_005dd935[] = "Bhaiksuki";
static const char s_Block_Elements_005de6b3[] = "Block Elements";
static const char s_Bopomofo_005dd93f[] = "Bopomofo";
static const char s_Bopomofo_Extended_005de980[] = "Bopomofo Extended";
static const char s_Box_Drawing_005de6a7[] = "Box Drawing";
static const char s_Brahmi_005dd948[] = "Brahmi";
static const char s_Braille_Patterns_005de760[] = "Braille Patterns";
static const char s_Buginese_005dd957[] = "Buginese";
static const char s_Buhid_005dd960[] = "Buhid";
static const char s_Byzantine_Musical_Symbols_005df150[] = "Byzantine Musical Symbols";
static const char s_CJK_Compatibility_005de9e0[] = "CJK Compatibility";
static const char s_CJK_Compatibility_Forms_005ded60[] = "CJK Compatibility Forms";
static const char s_CJK_Compatibility_Ideographs_005decb0[] = "CJK Compatibility Ideographs";
static const char s_CJK_Compatibility_Ideographs_Sup_005df5d0[] = "CJK Compatibility Ideographs Sup";
static const char s_CJK_Radicals_Supplement_005de8d0[] = "CJK Radicals Supplement";
static const char s_CJK_Strokes_005de992[] = "CJK Strokes";
static const char s_CJK_Symbols_and_Punctuation_005de930[] = "CJK Symbols and Punctuation";
static const char s_CJK_Unified_Ideographs_005dea50[] = "CJK Unified Ideographs";
static const char s_CJK_Unified_Ideographs_Extension_005dea00[] = "CJK Unified Ideographs Extension";
static const char s_CJK_Unified_Ideographs_Extension_005df4e0[] = "CJK Unified Ideographs Extension";
static const char s_CJK_Unified_Ideographs_Extension_005df510[] = "CJK Unified Ideographs Extension";
static const char s_CJK_Unified_Ideographs_Extension_005df540[] = "CJK Unified Ideographs Extension";
static const char s_CJK_Unified_Ideographs_Extension_005df570[] = "CJK Unified Ideographs Extension";
static const char s_CJK_Unified_Ideographs_Extension_005df5a0[] = "CJK Unified Ideographs Extension";
static const char s_CJK_Unified_Ideographs_Extension_005df600[] = "CJK Unified Ideographs Extension";
static const char s_Carian_005dd984[] = "Carian";
static const char s_Caucasian_Albanian_005dd990[] = "Caucasian Albanian";
static const char s_Chakma_005dd9a3[] = "Chakma";
static const char s_Cherokee_005dd9af[] = "Cherokee";
static const char s_Cherokee_Supplement_005debf0[] = "Cherokee Supplement";
static const char s_Chess_Symbols_005df475[] = "Chess Symbols";
static const char s_Chorasmian_005dd9b8[] = "Chorasmian";
static const char s_Combining_Diacritical_Marks_005de290[] = "Combining Diacritical Marks";
static const char s_Combining_Diacritical_Marks_Exte_005de400[] = "Combining Diacritical Marks Exte";
static const char s_Combining_Diacritical_Marks_Supp_005de4f0[] = "Combining Diacritical Marks Supp";
static const char s_Combining_Diacritical_Marks_for__005de5b0[] = "Combining Diacritical Marks for ";
static const char s_Combining_Half_Marks_005ded40[] = "Combining Half Marks";
static const char s_Common_Indic_Number_Forms_005deae0[] = "Common Indic Number Forms";
static const char s_Control_Pictures_005de650[] = "Control Pictures";
static const char s_Coptic_005dd9ca[] = "Coptic";
static const char s_Coptic_Epact_Numbers_005dee80[] = "Coptic Epact Numbers";
static const char s_Counting_Rod_Numerals_005df1d0[] = "Counting Rod Numerals";
static const char s_Cuneiform_005dd9d1[] = "Cuneiform";
static const char s_Cuneiform_Numbers_and_Punctuatio_005defb0[] = "Cuneiform Numbers and Punctuatio";
static const char s_Currency_Symbols_005de590[] = "Currency Symbols";
static const char s_Cypriot_Syllabary_005deec0[] = "Cypriot Syllabary";
static const char s_Cypro_Minoan_005dd9ec[] = "Cypro Minoan";
static const char s_Cyrillic_005dd9e3[] = "Cyrillic";
static const char s_Cyrillic_Extended_A_005de890[] = "Cyrillic Extended A";
static const char s_Cyrillic_Extended_B_005dea80[] = "Cyrillic Extended B";
static const char s_Cyrillic_Extended_C_005de430[] = "Cyrillic Extended C";
static const char s_Cyrillic_Supplement_005de2d0[] = "Cyrillic Supplement";
static const char s_Deseret_005dd9f9[] = "Deseret";
static const char s_Devanagari_005dda01[] = "Devanagari";
static const char s_Devanagari_Extended_005deb10[] = "Devanagari Extended";
static const char s_Dingbats_005de706[] = "Dingbats";
static const char s_Dives_Akuru_005dda0c[] = "Dives Akuru";
static const char s_Dogra_005dda18[] = "Dogra";
static const char s_Domino_Tiles_005df315[] = "Domino Tiles";
static const char s_Duployan_005dda1e[] = "Duployan";
static const char s_Early_Dynastic_Cuneiform_005defe0[] = "Early Dynastic Cuneiform";
static const char s_Egyptian_Hieroglyph_Format_Contr_005df000[] = "Egyptian Hieroglyph Format Contr";
static const char s_Egyptian_Hieroglyphs_005dda30[] = "Egyptian Hieroglyphs";
static const char s_Elbasan_005dda45[] = "Elbasan";
static const char s_Elymaic_005dda4d[] = "Elymaic";
static const char s_Emoticons_005df3a6[] = "Emoticons";
static const char s_Enclosed_Alphanumeric_Supplement_005df330[] = "Enclosed Alphanumeric Supplement";
static const char s_Enclosed_Alphanumerics_005de690[] = "Enclosed Alphanumerics";
static const char s_Enclosed_CJK_Letters_and_Months_005de9c0[] = "Enclosed CJK Letters and Months";
static const char s_Enclosed_Ideographic_Supplement_005df360[] = "Enclosed Ideographic Supplement";
static const char s_Ethiopic_005dda55[] = "Ethiopic";
static const char s_Ethiopic_Extended_005de870[] = "Ethiopic Extended";
static const char s_Ethiopic_Extended_A_005debb0[] = "Ethiopic Extended A";
static const char s_Ethiopic_Extended_B_005df280[] = "Ethiopic Extended B";
static const char s_Ethiopic_Supplement_005de370[] = "Ethiopic Supplement";
static const char s_General_Punctuation_005de550[] = "General Punctuation";
static const char s_Geometric_Shapes_005de6d0[] = "Geometric Shapes";
static const char s_Geometric_Shapes_Extended_005df410[] = "Geometric Shapes Extended";
static const char s_Georgian_005dda64[] = "Georgian";
static const char s_Georgian_Extended_005de450[] = "Georgian Extended";
static const char s_Georgian_Supplement_005de850[] = "Georgian Supplement";
static const char s_Glagolitic_005dda6d[] = "Glagolitic";
static const char s_Glagolitic_Supplement_005df260[] = "Glagolitic Supplement";
static const char s_Gothic_005dda78[] = "Gothic";
static const char s_Grantha_005dda7f[] = "Grantha";
static const char s_Greek_Extended_005de53a[] = "Greek Extended";
static const char s_Greek_and_Coptic_005de2b0[] = "Greek and Coptic";
static const char s_Gujarati_005dda8d[] = "Gujarati";
static const char s_Gunjala_Gondi_005dda96[] = "Gunjala Gondi";
static const char s_Gurmukhi_005ddaa4[] = "Gurmukhi";
static const char s_Halfwidth_and_Fullwidth_Forms_005dedc0[] = "Halfwidth and Fullwidth Forms";
static const char s_Hangul_Compatibility_Jamo_005de950[] = "Hangul Compatibility Jamo";
static const char s_Hangul_Jamo_005de362[] = "Hangul Jamo";
static const char s_Hangul_Jamo_Extended_A_005deb30[] = "Hangul Jamo Extended A";
static const char s_Hangul_Jamo_Extended_B_005dec30[] = "Hangul Jamo Extended B";
static const char s_Hangul_Syllables_005dec10[] = "Hangul Syllables";
static const char s_Hanifi_Rohingya_005ddac5[] = "Hanifi Rohingya";
static const char s_Hanunoo_005ddad5[] = "Hanunoo";
static const char s_Hatran_005ddadd[] = "Hatran";
static const char s_Hebrew_005ddae4[] = "Hebrew";
static const char s_High_Private_Use_Surrogates_005dec60[] = "High Private Use Surrogates";
static const char s_High_Surrogates_005dec47[] = "High Surrogates";
static const char s_Hiragana_005ddaeb[] = "Hiragana";
static const char s_IPA_Extensions_005de261[] = "IPA Extensions";
static const char s_Ideographic_Description_Characte_005de900[] = "Ideographic Description Characte";
static const char s_Ideographic_Symbols_and_Punctuat_005df050[] = "Ideographic Symbols and Punctuat";
static const char s_Imperial_Aramaic_005ddb00[] = "Imperial Aramaic";
static const char s_Indic_Siyaq_Numbers_005df2a0[] = "Indic Siyaq Numbers";
static const char s_Inscriptional_Pahlavi_005ddb20[] = "Inscriptional Pahlavi";
static const char s_Inscriptional_Parthian_005ddb40[] = "Inscriptional Parthian";
static const char s_Javanese_005ddb57[] = "Javanese";
static const char s_Kaithi_005ddb60[] = "Kaithi";
static const char s_Kana_Extended_A_005df0d2[] = "Kana Extended A";
static const char s_Kana_Extended_B_005df0b2[] = "Kana Extended B";
static const char s_Kana_Supplement_005df0c2[] = "Kana Supplement";
static const char s_Kanbun_005de96a[] = "Kanbun";
static const char s_Kangxi_Radicals_005de8e8[] = "Kangxi Radicals";
static const char s_Kannada_005ddb67[] = "Kannada";
static const char s_Katakana_005ddb6f[] = "Katakana";
static const char s_Katakana_Phonetic_Extensions_005de9a0[] = "Katakana Phonetic Extensions";
static const char s_Kayah_Li_005ddb9a[] = "Kayah Li";
static const char s_Kharoshthi_005ddba3[] = "Kharoshthi";
static const char s_Khitan_Small_Script_005ddbb0[] = "Khitan Small Script";
static const char s_Khmer_005ddbc4[] = "Khmer";
static const char s_Khmer_Symbols_005de3ef[] = "Khmer Symbols";
static const char s_Khojki_005ddbca[] = "Khojki";
static const char s_Khudawadi_005ddbd1[] = "Khudawadi";
static const char s_Latin_1_Supplement_005de210[] = "Latin 1 Supplement";
static const char s_Latin_Extended_A_005de230[] = "Latin Extended A";
static const char s_Latin_Extended_Additional_005de520[] = "Latin Extended Additional";
static const char s_Latin_Extended_B_005de250[] = "Latin Extended B";
static const char s_Latin_Extended_C_005de830[] = "Latin Extended C";
static const char s_Latin_Extended_D_005deac0[] = "Latin Extended D";
static const char s_Latin_Extended_E_005debd0[] = "Latin Extended E";
static const char s_Latin_Extended_F_005deea0[] = "Latin Extended F";
static const char s_Latin_Extended_G_005df240[] = "Latin Extended G";
static const char s_Lepcha_005ddbe5[] = "Lepcha";
static const char s_Letterlike_Symbols_005de5e0[] = "Letterlike Symbols";
static const char s_Limbu_005ddbec[] = "Limbu";
static const char s_Linear_A_005ddbf2[] = "Linear A";
static const char s_Linear_B_Ideograms_005dee10[] = "Linear B Ideograms";
static const char s_Linear_B_Syllabary_005dedf0[] = "Linear B Syllabary";
static const char s_Lisu_Supplement_005def71[] = "Lisu Supplement";
static const char s_Low_Surrogates_005dec7c[] = "Low Surrogates";
static const char s_Lycian_005ddc09[] = "Lycian";
static const char s_Lydian_005ddc10[] = "Lydian";
static const char s_Mahajani_005ddc21[] = "Mahajani";
static const char s_Mahjong_Tiles_005df307[] = "Mahjong Tiles";
static const char s_Makasar_005ddc2a[] = "Makasar";
static const char s_Malayalam_005ddc32[] = "Malayalam";
static const char s_Mandaic_005ddc3c[] = "Mandaic";
static const char s_Manichaean_005ddc44[] = "Manichaean";
static const char s_Marchen_005ddc4f[] = "Marchen";
static const char s_Masaram_Gondi_005ddc57[] = "Masaram Gondi";
static const char s_Mathematical_Alphanumeric_Symbol_005df1f0[] = "Mathematical Alphanumeric Symbol";
static const char s_Mathematical_Operators_005de610[] = "Mathematical Operators";
static const char s_Mayan_Numerals_005df19f[] = "Mayan Numerals";
static const char s_Medefaidrin_005ddc65[] = "Medefaidrin";
static const char s_Meetei_Mayek_005ddc71[] = "Meetei Mayek";
static const char s_Meetei_Mayek_Extensions_005deb90[] = "Meetei Mayek Extensions";
static const char s_Mende_Kikakui_005ddc7e[] = "Mende Kikakui";
static const char s_Meroitic_Cursive_005ddc90[] = "Meroitic Cursive";
static const char s_Meroitic_Hieroglyphs_005ddcb0[] = "Meroitic Hieroglyphs";
static const char s_Miscellaneous_Mathematical_Symbo_005de710[] = "Miscellaneous Mathematical Symbo";
static const char s_Miscellaneous_Mathematical_Symbo_005de7a0[] = "Miscellaneous Mathematical Symbo";
static const char s_Miscellaneous_Symbols_005de6f0[] = "Miscellaneous Symbols";
static const char s_Miscellaneous_Symbols_and_Arrows_005de800[] = "Miscellaneous Symbols and Arrows";
static const char s_Miscellaneous_Symbols_and_Pictog_005df380[] = "Miscellaneous Symbols and Pictog";
static const char s_Miscellaneous_Technical_005de630[] = "Miscellaneous Technical";
static const char s_Modifier_Tone_Letters_005deaa0[] = "Modifier Tone Letters";
static const char s_Mongolian_005ddccf[] = "Mongolian";
static const char s_Mongolian_Supplement_005def20[] = "Mongolian Supplement";
static const char s_Multani_005ddcdd[] = "Multani";
static const char s_Musical_Symbols_005df16a[] = "Musical Symbols";
static const char s_Myanmar_005ddce5[] = "Myanmar";
static const char s_Myanmar_Extended_A_005deb70[] = "Myanmar Extended A";
static const char s_Myanmar_Extended_B_005deb50[] = "Myanmar Extended B";
static const char s_Nabataean_005ddced[] = "Nabataean";
static const char s_Nandinagari_005ddd03[] = "Nandinagari";
static const char s_New_Tai_Lue_005ddd14[] = "New Tai Lue";
static const char s_No_Block_005df6a1[] = "No Block";
static const char s_Number_Forms_005de5f3[] = "Number Forms";
static const char s_Nushu_005ddd24[] = "Nushu";
static const char s_Nyiakeng_Puachue_Hmong_005ddd30[] = "Nyiakeng Puachue Hmong";
static const char s_Ogham_005ddd47[] = "Ogham";
static const char s_Ol_Chiki_005ddd4d[] = "Ol Chiki";
static const char s_Old_Hungarian_005ddd56[] = "Old Hungarian";
static const char s_Old_Italic_005ddd64[] = "Old Italic";
static const char s_Old_North_Arabian_005ddd70[] = "Old North Arabian";
static const char s_Old_Permic_005ddd82[] = "Old Permic";
static const char s_Old_Persian_005ddd8d[] = "Old Persian";
static const char s_Old_Sogdian_005ddd99[] = "Old Sogdian";
static const char s_Old_South_Arabian_005dddb0[] = "Old South Arabian";
static const char s_Old_Turkic_005dddc2[] = "Old Turkic";
static const char s_Old_Uyghur_005dddcd[] = "Old Uyghur";
static const char s_Optical_Character_Recognition_005de670[] = "Optical Character Recognition";
static const char s_Oriya_005ddde0[] = "Oriya";
static const char s_Ornamental_Dingbats_005df3b0[] = "Ornamental Dingbats";
static const char s_Osage_005ddde6[] = "Osage";
static const char s_Osmanya_005dddec[] = "Osmanya";
static const char s_Ottoman_Siyaq_Numbers_005df2c0[] = "Ottoman Siyaq Numbers";
static const char s_Pahawh_Hmong_005dddf4[] = "Pahawh Hmong";
static const char s_Palmyrene_005dde01[] = "Palmyrene";
static const char s_Pau_Cin_Hau_005dde0b[] = "Pau Cin Hau";
static const char s_Phags_pa_005deafa[] = "Phags pa";
static const char s_Phaistos_Disc_005dee66[] = "Phaistos Disc";
static const char s_Phoenician_005dde20[] = "Phoenician";
static const char s_Phonetic_Extensions_005de4b0[] = "Phonetic Extensions";
static const char s_Phonetic_Extensions_Supplement_005de4d0[] = "Phonetic Extensions Supplement";
static const char s_Playing_Cards_005df322[] = "Playing Cards";
static const char s_Private_Use_Area_005dec90[] = "Private Use Area";
static const char s_Psalter_Pahlavi_005dde2b[] = "Psalter Pahlavi";
static const char s_Rejang_005dde3b[] = "Rejang";
static const char s_Rumi_Numeral_Symbols_005deee0[] = "Rumi Numeral Symbols";
static const char s_Runic_005dde42[] = "Runic";
static const char s_Samaritan_005dde48[] = "Samaritan";
static const char s_Saurashtra_005dde52[] = "Saurashtra";
static const char s_Sharada_005dde5d[] = "Sharada";
static const char s_Shavian_005dde65[] = "Shavian";
static const char s_Shorthand_Format_Controls_005df110[] = "Shorthand Format Controls";
static const char s_Siddham_005dde6d[] = "Siddham";
static const char s_Sinhala_005dde81[] = "Sinhala";
static const char s_Sinhala_Archaic_Numbers_005def00[] = "Sinhala Archaic Numbers";
static const char s_Small_Form_Variants_005ded80[] = "Small Form Variants";
static const char s_Small_Kana_Extension_005df0f0[] = "Small Kana Extension";
static const char s_Sogdian_005dde89[] = "Sogdian";
static const char s_Sora_Sompeng_005dde91[] = "Sora Sompeng";
static const char s_Soyombo_005dde9e[] = "Soyombo";
static const char s_Spacing_Modifier_Letters_005de270[] = "Spacing Modifier Letters";
static const char s_Specials_005dedde[] = "Specials";
static const char s_Sundanese_005ddea6[] = "Sundanese";
static const char s_Sundanese_Supplement_005de470[] = "Sundanese Supplement";
static const char s_Superscripts_and_Subscripts_005de570[] = "Superscripts and Subscripts";
static const char s_Supplemental_Arrows_A_005de740[] = "Supplemental Arrows A";
static const char s_Supplemental_Arrows_B_005de780[] = "Supplemental Arrows B";
static const char s_Supplemental_Arrows_C_005df430[] = "Supplemental Arrows C";
static const char s_Supplemental_Mathematical_Operat_005de7d0[] = "Supplemental Mathematical Operat";
static const char s_Supplemental_Punctuation_005de8b0[] = "Supplemental Punctuation";
static const char s_Supplemental_Symbols_and_Pictogr_005df450[] = "Supplemental Symbols and Pictogr";
static const char s_Supplementary_Private_Use_Area_A_005df650[] = "Supplementary Private Use Area A";
static const char s_Supplementary_Private_Use_Area_B_005df680[] = "Supplementary Private Use Area B";
static const char s_Sutton_SignWriting_005df220[] = "Sutton SignWriting";
static const char s_Syloti_Nagri_005ddeb8[] = "Syloti Nagri";
static const char s_Symbols_and_Pictographs_Extended_005df490[] = "Symbols and Pictographs Extended";
static const char s_Symbols_for_Legacy_Computing_005df4c0[] = "Symbols for Legacy Computing";
static const char s_Syriac_005ddec5[] = "Syriac";
static const char s_Syriac_Supplement_005de310[] = "Syriac Supplement";
static const char s_Tagalog_005ddecc[] = "Tagalog";
static const char s_Tagbanwa_005dded4[] = "Tagbanwa";
static const char s_Tai_Le_005ddedd[] = "Tai Le";
static const char s_Tai_Tham_005ddee4[] = "Tai Tham";
static const char s_Tai_Viet_005ddeed[] = "Tai Viet";
static const char s_Tai_Xuan_Jing_Symbols_005df1b0[] = "Tai Xuan Jing Symbols";
static const char s_Takri_005ddef6[] = "Takri";
static const char s_Tamil_005ddefc[] = "Tamil";
static const char s_Tamil_Supplement_005def90[] = "Tamil Supplement";
static const char s_Tangsa_005ddf02[] = "Tangsa";
static const char s_Tangut_005ddf09[] = "Tangut";
static const char s_Tangut_Components_005df080[] = "Tangut Components";
static const char s_Tangut_Supplement_005df0a0[] = "Tangut Supplement";
static const char s_Telugu_005ddf10[] = "Telugu";
static const char s_Thaana_005ddf17[] = "Thaana";
static const char s_The_collection_of_element_types_d_005df6e0[] = "The collection of element types d";
static const char s_Tibetan_005ddf23[] = "Tibetan";
static const char s_Tifinagh_005ddf2b[] = "Tifinagh";
static const char s_Tirhuta_005ddf34[] = "Tirhuta";
static const char s_Transport_and_Map_Symbols_005df3d0[] = "Transport and Map Symbols";
static const char s_Ugaritic_005ddf56[] = "Ugaritic";
static const char s_Unified_Canadian_Aboriginal_Syll_005de390[] = "Unified Canadian Aboriginal Syll";
static const char s_Unified_Canadian_Aboriginal_Syll_005de3c0[] = "Unified Canadian Aboriginal Syll";
static const char s_Unified_Canadian_Aboriginal_Syll_005def40[] = "Unified Canadian Aboriginal Syll";
static const char s_Variation_Selectors_005ded10[] = "Variation Selectors";
static const char s_Variation_Selectors_Supplement_005df630[] = "Variation Selectors Supplement";
static const char s_Vedic_Extensions_005de490[] = "Vedic Extensions";
static const char s_Vertical_Forms_005ded24[] = "Vertical Forms";
static const char s_Vithkuqi_005ddf6b[] = "Vithkuqi";
static const char s_Wancho_005ddf74[] = "Wancho";
static const char s_Warang_Citi_005ddf7b[] = "Warang Citi";
static const char s_Yezidi_005ddf87[] = "Yezidi";
static const char s_Yi_Radicals_005dea74[] = "Yi Radicals";
static const char s_Yi_Syllables_005dea67[] = "Yi Syllables";
static const char s_Yijing_Hexagram_Symbols_005dea30[] = "Yijing Hexagram Symbols";
static const char s_Zanabazar_Square_005ddfa0[] = "Zanabazar Square";
static const char s_Znamenny_Musical_Notation_005df130[] = "Znamenny Musical Notation";

/* FUN_00451a10 @ 0x00451a10   (est. sk_gencat_count_clamp)
 * Ghidra: ulong FUN_00451a10(void)
 * Returns the size of the Character.Unicode.GeneralCategory enum
 * (0x26 == 38 values), clamped to 0x26. Touches the runtime validation
 * (00356c6c, 002ad95c(0x680d80 type tag), 00465240) and clamps the
 * caller-preserved count in x20.
 * Confidence: medium
 * Notes: 0x680d80 is the GeneralCategory metadata tag. */
static word_t sk_gencat_count_clamp_00451a10(word_t self)
{
    sk_x_00356c6c();
    sk_x_002ad95c(0x680d80);
    sk_x_00465240();
    if (0x25 < self) {
        self = 0x26;
    }
    return self;
}

/* FUN_00451a64 @ 0x00451a64   (est. sk_gencat_name)
 * Ghidra: undefined1[16] FUN_00451a64(undefined1 param_1)
 * Maps the GeneralCategory code (1..0x25) to its 16-byte small-string name.
 * Each case returns the packed {length<<56|char-pair} small-string value: e.g.
 * case 1 -> "Cc", 2 -> "Cf", 3 -> "Cn", ... case 0x25 -> "Zs". Unknown codes
 * default to uVar1=0x43 / uVar2=0xe100000000000000 (a 0x43 tag).
 * Confidence: high (small-string encoding is the Swift _StringGuts layout) */
static cl4_pair_t sk_gencat_name_00451a64(word_t param_1)
{
    cl4_pair_t r;
    word_t hi = 0xe100000000000000;
    word_t lo = 0x43;
    switch (param_1) {
    case 1:  r.lo = 0x6343; r.hi = 0xe200000000000000; return r;  /* Cc */
    case 2:  r.lo = 0x6643; r.hi = 0xe200000000000000; return r;  /* Cf */
    case 3:  r.lo = 0x6e43; r.hi = 0xe200000000000000; return r;  /* Cn */
    case 4:  r.lo = 0x6f43; r.hi = 0xe200000000000000; return r;  /* Co */
    case 5:  r.lo = 0x7343; r.hi = 0xe200000000000000; return r;  /* Cs */
    case 6:  r.lo = 0x4c;   r.hi = 0xe100000000000000; return r;  /* L */
    case 7:  r.lo = 0x634c; r.hi = 0xe200000000000000; return r;  /* Lc */
    case 8:  r.lo = 0x6c4c; r.hi = 0xe200000000000000; return r;  /* Ll */
    case 9:  r.lo = 0x6d4c; r.hi = 0xe200000000000000; return r;  /* Lm */
    case 10: r.lo = 0x6f4c; r.hi = 0xe200000000000000; return r;  /* Lo */
    case 0xb: r.lo = 0x744c; r.hi = 0xe200000000000000; return r; /* Lt */
    case 0xc: r.lo = 0x754c; r.hi = 0xe200000000000000; return r; /* Lu */
    case 0xd: r.lo = 0x4d;   r.hi = 0xe100000000000000; return r; /* M */
    case 0xe: r.lo = 0x634d; r.hi = 0xe200000000000000; return r; /* Mc */
    case 0xf: r.lo = 0x654d; r.hi = 0xe200000000000000; return r; /* Me */
    case 0x10:r.lo = 0x6e4d; r.hi = 0xe200000000000000; return r; /* Mn */
    case 0x11:r.lo = 0x4e;   r.hi = 0xe100000000000000; return r; /* N */
    case 0x12:r.lo = 0x644e; r.hi = 0xe200000000000000; return r; /* Nd */
    case 0x13:r.lo = 0x6c4e; r.hi = 0xe200000000000000; return r; /* Nl */
    case 0x14:r.lo = 0x6f4e; r.hi = 0xe200000000000000; return r; /* No */
    case 0x15:r.lo = 0x50;   r.hi = 0xe100000000000000; return r; /* P */
    case 0x16:r.lo = 0x6350; r.hi = 0xe200000000000000; return r; /* Pc */
    case 0x17:r.lo = 0x6450; r.hi = 0xe200000000000000; return r; /* Pd */
    case 0x18:r.lo = 0x6550; r.hi = 0xe200000000000000; return r; /* Pe */
    case 0x19:r.lo = 0x6650; r.hi = 0xe200000000000000; return r; /* Pf */
    case 0x1a:r.lo = 0x6950; r.hi = 0xe200000000000000; return r; /* Pi */
    case 0x1b:r.lo = 0x6f50; r.hi = 0xe200000000000000; return r; /* Po */
    case 0x1c:r.lo = 0x7350; r.hi = 0xe200000000000000; return r; /* Ps */
    case 0x1d:r.lo = 0x53;   r.hi = 0xe100000000000000; return r; /* S */
    case 0x1e:r.lo = 0x6353; r.hi = 0xe200000000000000; return r; /* Sc */
    case 0x1f:r.lo = 0x6b53; r.hi = 0xe200000000000000; return r; /* Sk */
    case 0x20:r.lo = 0x6d53; r.hi = 0xe200000000000000; return r; /* Sm */
    case 0x21:r.lo = 0x6f53; r.hi = 0xe200000000000000; return r; /* So */
    case 0x22:r.lo = 0x5a;   r.hi = 0xe100000000000000; return r; /* Z */
    case 0x23:r.lo = 0x6c5a; r.hi = 0xe200000000000000; return r; /* Zl */
    case 0x24:r.lo = 0x705a; r.hi = 0xe200000000000000; return r; /* Zp */
    case 0x25:r.lo = 0x735a; r.hi = 0xe200000000000000; return r; /* Zs */
    default:  r.lo = 0x43;   r.hi = 0xe100000000000000; return r;
    }
}

/* FUN_00451d04 @ 0x00451d04   (est. sk_gencat_name_store)
 * Ghidra: void FUN_00451d04(undefined1 (*param_1)[16])
 * Stores the GeneralCategory name (0x451a64) for the enum in x20 into the
 * 16-byte out-param.
 * Confidence: medium */
static void sk_gencat_name_store_00451d04(cl4_pair_t *param_1, word_t self)
{
    *param_1 = sk_gencat_name_00451a64(self);
}

/* FUN_00451d30 / 00451d34   (est. sk_gencat_witness_*
 * Ghidra: void FUN_00451d30/34(void)
 * Collection/Sequence conformance witnesses: forward the boxed enum (x20)
 * through the 00415570 generic witness with the name fn 0x451a64.
 * Confidence: low (witness thunk) */
static void sk_gencat_wit1_00451d30(word_t self)
{
    sk_x_00415570(self, (unsigned long)sk_gencat_name_00451a64);
}
static void sk_gencat_wit2_00451d34(word_t self)
{
    sk_x_00415570(self, (unsigned long)sk_gencat_name_00451a64);
}

/* FUN_00451d60 / 00451d64   (est. sk_gencat_wit_with_arg_*)
 * Ghidra: void FUN_00451d60(undefined8 param_1)
 * Witness forwarding an argument through 0041577c plus the name fn.
 * Confidence: low */
static void sk_gencat_wit3_00451d60(word_t param_1, word_t self)
{
    sk_x_0041577c(param_1, self, (unsigned long)sk_gencat_name_00451a64);
}
static void sk_gencat_wit4_00451d64(word_t param_1, word_t self)
{
    sk_x_0041577c(param_1, self, (unsigned long)sk_gencat_name_00451a64);
}

/* FUN_00451d90 / 00451d94   (est. sk_gencat_wit_acc_*)
 * Ghidra: void FUN_00451d90(undefined8 param_1)
 * Witness forwarding through 00415aa4 with the name fn.
 * Confidence: low */
static void sk_gencat_wit5_00451d90(word_t param_1, word_t self)
{
    sk_x_00415aa4(param_1, self, (unsigned long)sk_gencat_name_00451a64);
}
static void sk_gencat_wit6_00451d94(word_t param_1, word_t self)
{
    sk_x_00415aa4(param_1, self, (unsigned long)sk_gencat_name_00451a64);
}

/* FUN_00451dd0 @ 0x00451dd0   (est. sk_script_count_clamp)
 * Ghidra: ulong FUN_00451dd0(void)
 * Returns the Character.Unicode.Script enum size (0x43 == 67), clamped.
 * Confidence: medium */
static word_t sk_script_count_clamp_00451dd0(word_t self)
{
    sk_x_00356c6c();
    sk_x_002ad95c(0x681178);
    sk_x_00465240();
    if (0x42 < self) {
        self = 0x43;
    }
    return self;
}

/* FUN_00451e24 @ 0x00451e24   (est. sk_script_count_store)
 * Ghidra: void FUN_00451e24(undefined1 *param_1, undefined8 *param_2)
 * Stores the Script count (0x451dd0) into a byte out-param.
 * Confidence: medium */
static void sk_script_count_store_00451e24(byte *param_1, word_t *param_2)
{
    *param_1 = (byte)sk_script_count_clamp_00451dd0(*param_2);
}

/* FUN_00451e58 @ 0x00451e58   (est. sk_script_name_store)
 * Ghidra: void FUN_00451e58(undefined1 (*param_1)[16])
 * Stores the Script name (0x447144) for the enum in x20 into the 16-byte
 * out-param. 0x447144 is the out-of-range Script-name accessor.
 * Confidence: medium */
static void sk_script_name_store_00451e58(cl4_pair_t *param_1, word_t self)
{
    *param_1 = sk_x_00447144(self);
}

/* FUN_00451e84 / 00451e88   (est. sk_script_wit_*)
 * Ghidra: void FUN_00451e84/88(void)
 * Sequence witnesses forwarding the boxed Script enum through 00415570 with
 * the out-of-range Script-name fn 0x447144.
 * Confidence: low */
static void sk_script_wit1_00451e84(word_t self)
{
    sk_x_00415570(self, (unsigned long)sk_x_00447144);
}
static void sk_script_wit2_00451e88(word_t self)
{
    sk_x_00415570(self, (unsigned long)sk_x_00447144);
}

/* FUN_00451eb4 / 00451eb8   (est. sk_script_wit_arg_*)
 * Ghidra: void FUN_00451eb4(undefined8 param_1)
 * Witness forwarding an arg through 0041577c with the Script-name fn.
 * Confidence: low */
static void sk_script_wit3_00451eb4(word_t param_1, word_t self)
{
    sk_x_0041577c(param_1, self, (unsigned long)sk_x_00447144);
}
static void sk_script_wit4_00451eb8(word_t param_1, word_t self)
{
    sk_x_0041577c(param_1, self, (unsigned long)sk_x_00447144);
}

/* FUN_00451ee4 / 00451ee8   (est. sk_script_wit_acc_*)
 * Ghidra: void FUN_00451ee4(undefined8 param_1)
 * Witness forwarding through 00415aa4 with the Script-name fn.
 * Confidence: low */
static void sk_script_wit5_00451ee4(word_t param_1, word_t self)
{
    sk_x_00415aa4(param_1, self, (unsigned long)sk_x_00447144);
}
static void sk_script_wit6_00451ee8(word_t param_1, word_t self)
{
    sk_x_00415aa4(param_1, self, (unsigned long)sk_x_00447144);
}
/* FUN_00451f24 @ 0x00451f24   (est. sk_block_table_build_00451f24)
 * Ghidra: void FUN_00451f24(void)
 * Builds the Character.Unicode.Block lookup table: allocates a 0x1e38-byte
 * buffer (0036a940 with the 0x657a30 Block-table metadata) and fills it with
 * 299 {name, range-count, tag} records (0x18-stride) covering every Unicode
 * block (Basic Latin, Latin-1 Supplement, ..., No Block). The tag word at each
 * record +0x10 is 2 (the Swift small-string discriminator) and the +0x08 word
 * is the block's range count. Afterwards reports the table's record count
 * (002ad78c), releasing the temp refs (0036b118/003a25d4), rounding the count
 * up to the enclosing 0x40-bucket, and returning via 00084234.
 * Confidence: high (data table, fully transcribed)
 * Notes: DAT_005a1970/005a1978 type-metadata words loaded but elided (out of
 *   range); every (offset,value) pair in the decompile is preserved. */
static void sk_block_table_build_00451f24(word_t self)
{
    word_t uVar1, uVar2;
    long table;
    word_t uVar4;

    sk_x_00084220();
    sk_x_003504d0();
    uVar2 = sk_x_00002534(0x657a30, 0x005a1a48);
    table = sk_x_0036a940(uVar2, 0x1e38, 7);
    /* DAT_005a1970 / DAT_005a1978 are the type-metadata header words. */
    uVar1 = 0;   /* uRam00000000005a1978 - out of range load, elided */
    uVar2 = 0;   /* _DAT_005a1970 - out of range load, elided */

    *(const char **)(table + 0x020) = s_Basic_Latin_005de200;
    *(word_t *)(table + 0x028) = 0xb;
    *(byte *)(table + 0x030) = 2;
    *(const char **)(table + 0x038) = s_Latin_1_Supplement_005de210;
    *(word_t *)(table + 0x040) = 0x12;
    *(byte *)(table + 0x048) = 2;
    *(const char **)(table + 0x050) = s_Latin_Extended_A_005de230;
    *(word_t *)(table + 0x058) = 0x10;
    *(byte *)(table + 0x060) = 2;
    *(const char **)(table + 0x068) = s_Latin_Extended_B_005de250;
    *(word_t *)(table + 0x070) = 0x10;
    *(byte *)(table + 0x078) = 2;
    *(const char **)(table + 0x080) = s_IPA_Extensions_005de261;
    *(word_t *)(table + 0x088) = 0xe;
    *(byte *)(table + 0x090) = 2;
    *(const char **)(table + 0x098) = s_Spacing_Modifier_Letters_005de270;
    *(word_t *)(table + 0x0a0) = 0x18;
    *(byte *)(table + 0x0a8) = 2;
    *(const char **)(table + 0x0b0) = s_Combining_Diacritical_Marks_005de290;
    *(word_t *)(table + 0x0b8) = 0x1b;
    *(byte *)(table + 0x0c0) = 2;
    *(const char **)(table + 0x0c8) = s_Greek_and_Coptic_005de2b0;
    *(word_t *)(table + 0x0d0) = 0x10;
    *(byte *)(table + 0x0d8) = 2;
    *(const char **)(table + 0x0e0) = s_Cyrillic_005dd9e3;
    *(byte *)(table + 0x0f0) = 2;
    *(const char **)(table + 0x0f8) = s_Cyrillic_Supplement_005de2d0;
    *(word_t *)(table + 0x100) = 0x13;
    *(byte *)(table + 0x108) = 2;
    *(const char **)(table + 0x110) = s_Armenian_005dd8fd;
    *(byte *)(table + 0x120) = 2;
    *(const char **)(table + 0x128) = s_Hebrew_005ddae4;
    *(byte *)(table + 0x138) = 2;
    *(const char **)(table + 0x140) = s_Arabic_005dd8f6;
    *(byte *)(table + 0x150) = 2;
    *(const char **)(table + 0x158) = s_Syriac_005ddec5;
    *(byte *)(table + 0x168) = 2;
    *(const char **)(table + 0x170) = s_Arabic_Supplement_005de2f0;
    *(word_t *)(table + 0x178) = 0x11;
    *(byte *)(table + 0x180) = 2;
    *(const char **)(table + 0x188) = s_Thaana_005ddf17;
    *(byte *)(table + 0x198) = 2;
    *(byte *)(table + 0x1b0) = 2;
    *(const char **)(table + 0x1b8) = s_Samaritan_005dde48;
    *(byte *)(table + 0x1c8) = 2;
    *(const char **)(table + 0x1d0) = s_Mandaic_005ddc3c;
    *(byte *)(table + 0x1e0) = 2;
    *(const char **)(table + 0x1e8) = s_Syriac_Supplement_005de310;
    *(word_t *)(table + 0x1f0) = 0x11;
    *(byte *)(table + 0x1f8) = 2;
    *(const char **)(table + 0x200) = s_Arabic_Extended_B_005de330;
    *(word_t *)(table + 0x208) = 0x11;
    *(byte *)(table + 0x210) = 2;
    *(const char **)(table + 0x218) = s_Arabic_Extended_A_005de350;
    *(word_t *)(table + 0x220) = 0x11;
    *(byte *)(table + 0x228) = 2;
    *(const char **)(table + 0x230) = s_Devanagari_005dda01;
    *(byte *)(table + 0x240) = 2;
    *(const char **)(table + 0x248) = s_Bengali_005dd92d;
    *(byte *)(table + 0x258) = 2;
    *(const char **)(table + 0x260) = s_Gurmukhi_005ddaa4;
    *(byte *)(table + 0x270) = 2;
    *(const char **)(table + 0x278) = s_Gujarati_005dda8d;
    *(byte *)(table + 0x288) = 2;
    *(const char **)(table + 0x290) = s_Oriya_005ddde0;
    *(byte *)(table + 0x2a0) = 2;
    *(const char **)(table + 0x2a8) = s_Tamil_005ddefc;
    *(byte *)(table + 0x2b8) = 2;
    *(const char **)(table + 0x2c0) = s_Telugu_005ddf10;
    *(byte *)(table + 0x2d0) = 2;
    *(const char **)(table + 0x2d8) = s_Kannada_005ddb67;
    *(byte *)(table + 0x2e8) = 2;
    *(const char **)(table + 0x2f0) = s_Malayalam_005ddc32;
    *(byte *)(table + 0x300) = 2;
    *(const char **)(table + 0x308) = s_Sinhala_005dde81;
    *(byte *)(table + 0x318) = 2;
    *(byte *)(table + 0x330) = 2;
    *(byte *)(table + 0x348) = 2;
    *(const char **)(table + 0x350) = s_Tibetan_005ddf23;
    *(byte *)(table + 0x360) = 2;
    *(const char **)(table + 0x368) = s_Myanmar_005ddce5;
    *(byte *)(table + 0x378) = 2;
    *(const char **)(table + 0x380) = s_Georgian_005dda64;
    *(byte *)(table + 0x390) = 2;
    *(const char **)(table + 0x398) = s_Hangul_Jamo_005de362;
    *(word_t *)(table + 0x3a0) = 0xb;
    *(byte *)(table + 0x3a8) = 2;
    *(const char **)(table + 0x3b0) = s_Ethiopic_005dda55;
    *(byte *)(table + 0x3c0) = 2;
    *(const char **)(table + 0x3c8) = s_Ethiopic_Supplement_005de370;
    *(word_t *)(table + 0x3d0) = 0x13;
    *(byte *)(table + 0x3d8) = 2;
    *(const char **)(table + 0x3e0) = s_Cherokee_005dd9af;
    *(byte *)(table + 0x3f0) = 2;
    *(const char **)(table + 0x3f8) = s_Unified_Canadian_Aboriginal_Syll_005de390;
    *(word_t *)(table + 0x400) = 0x25;
    *(byte *)(table + 0x408) = 2;
    *(const char **)(table + 0x410) = s_Ogham_005ddd47;
    *(byte *)(table + 0x420) = 2;
    *(const char **)(table + 0x428) = s_Runic_005dde42;
    *(byte *)(table + 0x438) = 2;
    *(const char **)(table + 0x440) = s_Tagalog_005ddecc;
    *(byte *)(table + 0x450) = 2;
    *(const char **)(table + 0x458) = s_Hanunoo_005ddad5;
    *(byte *)(table + 0x468) = 2;
    *(const char **)(table + 0x470) = s_Buhid_005dd960;
    *(byte *)(table + 0x480) = 2;
    *(const char **)(table + 0x488) = s_Tagbanwa_005dded4;
    *(byte *)(table + 0x498) = 2;
    *(const char **)(table + 0x4a0) = s_Khmer_005ddbc4;
    *(byte *)(table + 0x4b0) = 2;
    *(const char **)(table + 0x4b8) = s_Mongolian_005ddccf;
    *(byte *)(table + 0x4c8) = 2;
    *(const char **)(table + 0x4d0) = s_Unified_Canadian_Aboriginal_Syll_005de3c0;
    *(word_t *)(table + 0x4d8) = 0x2e;
    *(byte *)(table + 0x4e0) = 2;
    *(const char **)(table + 0x4e8) = s_Limbu_005ddbec;
    *(byte *)(table + 0x4f8) = 2;
    *(const char **)(table + 0x500) = s_Tai_Le_005ddedd;
    *(byte *)(table + 0x510) = 2;
    *(const char **)(table + 0x518) = s_New_Tai_Lue_005ddd14;
    *(word_t *)(table + 0x520) = 0xb;
    *(byte *)(table + 0x528) = 2;
    *(const char **)(table + 0x530) = s_Khmer_Symbols_005de3ef;
    *(word_t *)(table + 0x538) = 0xd;
    *(byte *)(table + 0x540) = 2;
    *(const char **)(table + 0x548) = s_Buginese_005dd957;
    *(byte *)(table + 0x558) = 2;
    *(const char **)(table + 0x560) = s_Tai_Tham_005ddee4;
    *(byte *)(table + 0x570) = 2;
    *(const char **)(table + 0x578) = s_Combining_Diacritical_Marks_Exte_005de400;
    *(word_t *)(table + 0x580) = 0x24;
    *(byte *)(table + 0x588) = 2;
    *(const char **)(table + 0x590) = s_Balinese_005dd90e;
    *(byte *)(table + 0x5a0) = 2;
    *(const char **)(table + 0x5a8) = s_Sundanese_005ddea6;
    *(byte *)(table + 0x5b8) = 2;
    *(const char **)(table + 0x5c0) = s_Batak_005dd927;
    *(byte *)(table + 0x5d0) = 2;
    *(const char **)(table + 0x5d8) = s_Lepcha_005ddbe5;
    *(byte *)(table + 0x5e8) = 2;
    *(const char **)(table + 0x5f0) = s_Ol_Chiki_005ddd4d;
    *(byte *)(table + 0x600) = 2;
    *(const char **)(table + 0x608) = s_Cyrillic_Extended_C_005de430;
    *(word_t *)(table + 0x610) = 0x13;
    *(byte *)(table + 0x618) = 2;
    *(const char **)(table + 0x620) = s_Georgian_Extended_005de450;
    *(word_t *)(table + 0x628) = 0x11;
    *(byte *)(table + 0x630) = 2;
    *(const char **)(table + 0x638) = s_Sundanese_Supplement_005de470;
    *(word_t *)(table + 0x640) = 0x14;
    *(byte *)(table + 0x648) = 2;
    *(const char **)(table + 0x650) = s_Vedic_Extensions_005de490;
    *(word_t *)(table + 0x658) = 0x10;
    *(byte *)(table + 0x660) = 2;
    *(const char **)(table + 0x668) = s_Phonetic_Extensions_005de4b0;
    *(word_t *)(table + 0x670) = 0x13;
    *(byte *)(table + 0x678) = 2;
    *(const char **)(table + 0x680) = s_Phonetic_Extensions_Supplement_005de4d0;
    *(word_t *)(table + 0x688) = 0x1e;
    *(byte *)(table + 0x690) = 2;
    *(const char **)(table + 0x698) = s_Combining_Diacritical_Marks_Supp_005de4f0;
    *(word_t *)(table + 0x6a0) = 0x26;
    *(byte *)(table + 0x6a8) = 2;
    *(const char **)(table + 0x6b0) = s_Latin_Extended_Additional_005de520;
    *(word_t *)(table + 0x6b8) = 0x19;
    *(byte *)(table + 0x6c0) = 2;
    *(const char **)(table + 0x6c8) = s_Greek_Extended_005de53a;
    *(word_t *)(table + 0x6d0) = 0xe;
    *(byte *)(table + 0x6d8) = 2;
    *(const char **)(table + 0x6e0) = s_General_Punctuation_005de550;
    *(word_t *)(table + 0x6e8) = 0x13;
    *(byte *)(table + 0x6f0) = 2;
    *(const char **)(table + 0x6f8) = s_Superscripts_and_Subscripts_005de570;
    *(word_t *)(table + 0x700) = 0x1b;
    *(byte *)(table + 0x708) = 2;
    *(const char **)(table + 0x710) = s_Currency_Symbols_005de590;
    *(word_t *)(table + 0x718) = 0x10;
    *(byte *)(table + 0x720) = 2;
    *(const char **)(table + 0x728) = s_Combining_Diacritical_Marks_for__005de5b0;
    *(word_t *)(table + 0x730) = 0x27;
    *(byte *)(table + 0x738) = 2;
    *(const char **)(table + 0x740) = s_Letterlike_Symbols_005de5e0;
    *(word_t *)(table + 0x748) = 0x12;
    *(byte *)(table + 0x750) = 2;
    *(const char **)(table + 0x758) = s_Number_Forms_005de5f3;
    *(word_t *)(table + 0x760) = 0xc;
    *(byte *)(table + 0x768) = 2;
    *(const char **)(table + 0x770) = s_Arrows_005de600;
    *(byte *)(table + 0x780) = 2;
    *(const char **)(table + 0x788) = s_Mathematical_Operators_005de610;
    *(word_t *)(table + 0x790) = 0x16;
    *(byte *)(table + 0x798) = 2;
    *(const char **)(table + 0x7a0) = s_Miscellaneous_Technical_005de630;
    *(word_t *)(table + 0x7a8) = 0x17;
    *(byte *)(table + 0x7b0) = 2;
    *(const char **)(table + 0x7b8) = s_Control_Pictures_005de650;
    *(word_t *)(table + 0x7c0) = 0x10;
    *(byte *)(table + 0x7c8) = 2;
    *(const char **)(table + 0x7d0) = s_Optical_Character_Recognition_005de670;
    *(word_t *)(table + 0x7d8) = 0x1d;
    *(byte *)(table + 0x7e0) = 2;
    *(const char **)(table + 0x7e8) = s_Enclosed_Alphanumerics_005de690;
    *(word_t *)(table + 0x7f0) = 0x16;
    *(byte *)(table + 0x7f8) = 2;
    *(const char **)(table + 0x800) = s_Box_Drawing_005de6a7;
    *(word_t *)(table + 0x808) = 0xb;
    *(byte *)(table + 0x810) = 2;
    *(const char **)(table + 0x818) = s_Block_Elements_005de6b3;
    *(word_t *)(table + 0x820) = 0xe;
    *(byte *)(table + 0x828) = 2;
    *(const char **)(table + 0x830) = s_Geometric_Shapes_005de6d0;
    *(word_t *)(table + 0x838) = 0x10;
    *(byte *)(table + 0x840) = 2;
    *(const char **)(table + 0x848) = s_Miscellaneous_Symbols_005de6f0;
    *(word_t *)(table + 0x850) = 0x15;
    *(byte *)(table + 0x858) = 2;
    *(const char **)(table + 0x860) = s_Dingbats_005de706;
    *(byte *)(table + 0x870) = 2;
    *(const char **)(table + 0x878) = s_Miscellaneous_Mathematical_Symbo_005de710;
    *(word_t *)(table + 0x880) = 0x24;
    *(byte *)(table + 0x888) = 2;
    *(const char **)(table + 0x890) = s_Supplemental_Arrows_A_005de740;
    *(word_t *)(table + 0x898) = 0x15;
    *(byte *)(table + 0x8a0) = 2;
    *(const char **)(table + 0x8a8) = s_Braille_Patterns_005de760;
    *(word_t *)(table + 0x8b0) = 0x10;
    *(byte *)(table + 0x8b8) = 2;
    *(const char **)(table + 0x8c0) = s_Supplemental_Arrows_B_005de780;
    *(word_t *)(table + 0x8c8) = 0x15;
    *(byte *)(table + 0x8d0) = 2;
    *(const char **)(table + 0x8d8) = s_Miscellaneous_Mathematical_Symbo_005de7a0;
    *(word_t *)(table + 0x8e0) = 0x24;
    *(byte *)(table + 0x8e8) = 2;
    *(const char **)(table + 0x8f0) = s_Supplemental_Mathematical_Operat_005de7d0;
    *(word_t *)(table + 0x8f8) = 0x23;
    *(byte *)(table + 0x900) = 2;
    *(const char **)(table + 0x908) = s_Miscellaneous_Symbols_and_Arrows_005de800;
    *(word_t *)(table + 0x910) = 0x20;
    *(byte *)(table + 0x918) = 2;
    *(const char **)(table + 0x920) = s_Glagolitic_005dda6d;
    *(byte *)(table + 0x930) = 2;
    *(const char **)(table + 0x938) = s_Latin_Extended_C_005de830;
    *(word_t *)(table + 0x940) = 0x10;
    *(byte *)(table + 0x948) = 2;
    *(const char **)(table + 0x950) = s_Coptic_005dd9ca;
    *(byte *)(table + 0x960) = 2;
    *(const char **)(table + 0x968) = s_Georgian_Supplement_005de850;
    *(word_t *)(table + 0x970) = 0x13;
    *(byte *)(table + 0x978) = 2;
    *(const char **)(table + 0x980) = s_Tifinagh_005ddf2b;
    *(byte *)(table + 0x990) = 2;
    *(const char **)(table + 0x998) = s_Ethiopic_Extended_005de870;
    *(word_t *)(table + 0x9a0) = 0x11;
    *(byte *)(table + 0x9a8) = 2;
    *(const char **)(table + 0x9b0) = s_Cyrillic_Extended_A_005de890;
    *(word_t *)(table + 0x9b8) = 0x13;
    *(byte *)(table + 0x9c0) = 2;
    *(const char **)(table + 0x9c8) = s_Supplemental_Punctuation_005de8b0;
    *(word_t *)(table + 0x9d0) = 0x18;
    *(byte *)(table + 0x9d8) = 2;
    *(const char **)(table + 0x9e0) = s_CJK_Radicals_Supplement_005de8d0;
    *(word_t *)(table + 0x9e8) = 0x17;
    *(byte *)(table + 0x9f0) = 2;
    *(const char **)(table + 0x9f8) = s_Kangxi_Radicals_005de8e8;
    *(word_t *)(table + 0xa00) = 0xf;
    *(byte *)(table + 0xa08) = 2;
    *(const char **)(table + 0xa10) = s_Ideographic_Description_Characte_005de900;
    *(word_t *)(table + 0xa18) = 0x22;
    *(byte *)(table + 0xa20) = 2;
    *(const char **)(table + 0xa28) = s_CJK_Symbols_and_Punctuation_005de930;
    *(word_t *)(table + 0xa30) = 0x1b;
    *(byte *)(table + 0xa38) = 2;
    *(const char **)(table + 0xa40) = s_Hiragana_005ddaeb;
    *(byte *)(table + 0xa50) = 2;
    *(const char **)(table + 0xa58) = s_Katakana_005ddb6f;
    *(byte *)(table + 0xa68) = 2;
    *(const char **)(table + 0xa70) = s_Bopomofo_005dd93f;
    *(byte *)(table + 0xa80) = 2;
    *(const char **)(table + 0xa88) = s_Hangul_Compatibility_Jamo_005de950;
    *(word_t *)(table + 0xa90) = 0x19;
    *(byte *)(table + 0xa98) = 2;
    *(const char **)(table + 0xaa0) = s_Kanbun_005de96a;
    *(byte *)(table + 0xab0) = 2;
    *(const char **)(table + 0xab8) = s_Bopomofo_Extended_005de980;
    *(word_t *)(table + 0xac0) = 0x11;
    *(byte *)(table + 0xac8) = 2;
    *(const char **)(table + 0xad0) = s_CJK_Strokes_005de992;
    *(word_t *)(table + 0xad8) = 0xb;
    *(byte *)(table + 0xae0) = 2;
    *(const char **)(table + 0xae8) = s_Katakana_Phonetic_Extensions_005de9a0;
    *(word_t *)(table + 0xaf0) = 0x1c;
    *(byte *)(table + 0xaf8) = 2;
    *(const char **)(table + 0xb00) = s_Enclosed_CJK_Letters_and_Months_005de9c0;
    *(word_t *)(table + 0xb08) = 0x1f;
    *(byte *)(table + 0xb10) = 2;
    *(const char **)(table + 0xb18) = s_CJK_Compatibility_005de9e0;
    *(word_t *)(table + 0xb20) = 0x11;
    *(byte *)(table + 0xb28) = 2;
    *(const char **)(table + 0xb30) = s_CJK_Unified_Ideographs_Extension_005dea00;
    *(word_t *)(table + 0xb38) = 0x22;
    *(byte *)(table + 0xb40) = 2;
    *(const char **)(table + 0xb48) = s_Yijing_Hexagram_Symbols_005dea30;
    *(word_t *)(table + 0xb50) = 0x17;
    *(byte *)(table + 0xb58) = 2;
    *(const char **)(table + 0xb60) = s_CJK_Unified_Ideographs_005dea50;
    *(word_t *)(table + 0xb68) = 0x16;
    *(byte *)(table + 0xb70) = 2;
    *(const char **)(table + 0xb78) = s_Yi_Syllables_005dea67;
    *(word_t *)(table + 0xb80) = 0xc;
    *(byte *)(table + 0xb88) = 2;
    *(const char **)(table + 0xb90) = s_Yi_Radicals_005dea74;
    *(word_t *)(table + 0xb98) = 0xb;
    *(byte *)(table + 0xba0) = 2;
    *(byte *)(table + 0xbb8) = 2;
    *(byte *)(table + 0xbd0) = 2;
    *(const char **)(table + 0xbd8) = s_Cyrillic_Extended_B_005dea80;
    *(word_t *)(table + 0xbe0) = 0x13;
    *(byte *)(table + 0xbe8) = 2;
    *(const char **)(table + 0xbf0) = s_Bamum_005dd917;
    *(byte *)(table + 0xc00) = 2;
    *(const char **)(table + 0xc08) = s_Modifier_Tone_Letters_005deaa0;
    *(word_t *)(table + 0xc10) = 0x15;
    *(byte *)(table + 0xc18) = 2;
    *(const char **)(table + 0xc20) = s_Latin_Extended_D_005deac0;
    *(word_t *)(table + 0xc28) = 0x10;
    *(byte *)(table + 0xc30) = 2;
    *(const char **)(table + 0xc38) = s_Syloti_Nagri_005ddeb8;
    *(word_t *)(table + 0xc40) = 0xc;
    *(byte *)(table + 0xc48) = 2;
    *(const char **)(table + 0xc50) = s_Common_Indic_Number_Forms_005deae0;
    *(word_t *)(table + 0xc58) = 0x19;
    *(byte *)(table + 0xc60) = 2;
    *(const char **)(table + 0xc68) = s_Phags_pa_005deafa;
    *(byte *)(table + 0xc78) = 2;
    *(const char **)(table + 0xc80) = s_Saurashtra_005dde52;
    *(byte *)(table + 0xc90) = 2;
    *(const char **)(table + 0xc98) = s_Devanagari_Extended_005deb10;
    *(word_t *)(table + 0xca0) = 0x13;
    *(byte *)(table + 0xca8) = 2;
    *(const char **)(table + 0xcb0) = s_Kayah_Li_005ddb9a;
    *(byte *)(table + 0xcc0) = 2;
    *(const char **)(table + 0xcc8) = s_Rejang_005dde3b;
    *(byte *)(table + 0xcd8) = 2;
    *(const char **)(table + 0xce0) = s_Hangul_Jamo_Extended_A_005deb30;
    *(word_t *)(table + 0xce8) = 0x16;
    *(byte *)(table + 0xcf0) = 2;
    *(const char **)(table + 0xcf8) = s_Javanese_005ddb57;
    *(byte *)(table + 0xd08) = 2;
    *(const char **)(table + 0xd10) = s_Myanmar_Extended_B_005deb50;
    *(word_t *)(table + 0xd18) = 0x12;
    *(byte *)(table + 0xd20) = 2;
    *(byte *)(table + 0xd38) = 2;
    *(const char **)(table + 0xd40) = s_Myanmar_Extended_A_005deb70;
    *(word_t *)(table + 0xd48) = 0x12;
    *(byte *)(table + 0xd50) = 2;
    *(const char **)(table + 0xd58) = s_Tai_Viet_005ddeed;
    *(byte *)(table + 0xd68) = 2;
    *(const char **)(table + 0xd70) = s_Meetei_Mayek_Extensions_005deb90;
    *(word_t *)(table + 0xd78) = 0x17;
    *(byte *)(table + 0xd80) = 2;
    *(const char **)(table + 0xd88) = s_Ethiopic_Extended_A_005debb0;
    *(word_t *)(table + 0xd90) = 0x13;
    *(byte *)(table + 0xd98) = 2;
    *(const char **)(table + 0xda0) = s_Latin_Extended_E_005debd0;
    *(word_t *)(table + 0xda8) = 0x10;
    *(byte *)(table + 0xdb0) = 2;
    *(const char **)(table + 0xdb8) = s_Cherokee_Supplement_005debf0;
    *(word_t *)(table + 0xdc0) = 0x13;
    *(byte *)(table + 0xdc8) = 2;
    *(const char **)(table + 0xdd0) = s_Meetei_Mayek_005ddc71;
    *(word_t *)(table + 0xdd8) = 0xc;
    *(byte *)(table + 0xde0) = 2;
    *(const char **)(table + 0xde8) = s_Hangul_Syllables_005dec10;
    *(word_t *)(table + 0xdf0) = 0x10;
    *(byte *)(table + 0xdf8) = 2;
    *(const char **)(table + 0xe00) = s_Hangul_Jamo_Extended_B_005dec30;
    *(word_t *)(table + 0xe08) = 0x16;
    *(byte *)(table + 0xe10) = 2;
    *(const char **)(table + 0xe18) = s_High_Surrogates_005dec47;
    *(word_t *)(table + 0xe20) = 0xf;
    *(byte *)(table + 0xe28) = 2;
    *(const char **)(table + 0xe30) = s_High_Private_Use_Surrogates_005dec60;
    *(word_t *)(table + 0xe38) = 0x1b;
    *(byte *)(table + 0xe40) = 2;
    *(const char **)(table + 0xe48) = s_Low_Surrogates_005dec7c;
    *(word_t *)(table + 0xe50) = 0xe;
    *(byte *)(table + 0xe58) = 2;
    *(const char **)(table + 0xe60) = s_Private_Use_Area_005dec90;
    *(word_t *)(table + 0xe68) = 0x10;
    *(byte *)(table + 0xe70) = 2;
    *(const char **)(table + 0xe78) = s_CJK_Compatibility_Ideographs_005decb0;
    *(word_t *)(table + 0xe80) = 0x1c;
    *(byte *)(table + 0xe88) = 2;
    *(const char **)(table + 0xe90) = s_Alphabetic_Presentation_Forms_005decd0;
    *(word_t *)(table + 0xe98) = 0x1d;
    *(byte *)(table + 0xea0) = 2;
    *(const char **)(table + 0xea8) = s_Arabic_Presentation_Forms_A_005decf0;
    *(word_t *)(table + 0xeb0) = 0x1b;
    *(byte *)(table + 0xeb8) = 2;
    *(const char **)(table + 0xec0) = s_Variation_Selectors_005ded10;
    *(word_t *)(table + 0xec8) = 0x13;
    *(byte *)(table + 0xed0) = 2;
    *(const char **)(table + 0xed8) = s_Vertical_Forms_005ded24;
    *(word_t *)(table + 0xee0) = 0xe;
    *(byte *)(table + 0xee8) = 2;
    *(const char **)(table + 0xef0) = s_Combining_Half_Marks_005ded40;
    *(word_t *)(table + 0xef8) = 0x14;
    *(byte *)(table + 0xf00) = 2;
    *(const char **)(table + 0xf08) = s_CJK_Compatibility_Forms_005ded60;
    *(word_t *)(table + 0xf10) = 0x17;
    *(byte *)(table + 0xf18) = 2;
    *(const char **)(table + 0xf20) = s_Small_Form_Variants_005ded80;
    *(word_t *)(table + 0xf28) = 0x13;
    *(byte *)(table + 0xf30) = 2;
    *(const char **)(table + 0xf38) = s_Arabic_Presentation_Forms_B_005deda0;
    *(word_t *)(table + 0xf40) = 0x1b;
    *(byte *)(table + 0xf48) = 2;
    *(const char **)(table + 0xf50) = s_Halfwidth_and_Fullwidth_Forms_005dedc0;
    *(word_t *)(table + 0xf58) = 0x1d;
    *(byte *)(table + 0xf60) = 2;
    *(const char **)(table + 0xf68) = s_Specials_005dedde;
    *(byte *)(table + 0xf78) = 2;
    *(const char **)(table + 0xf80) = s_Linear_B_Syllabary_005dedf0;
    *(word_t *)(table + 0xf88) = 0x12;
    *(byte *)(table + 0xf90) = 2;
    *(const char **)(table + 0xf98) = s_Linear_B_Ideograms_005dee10;
    *(word_t *)(table + 0xfa0) = 0x12;
    *(byte *)(table + 0xfa8) = 2;
    *(const char **)(table + 0xfb0) = s_Aegean_Numbers_005dee23;
    *(word_t *)(table + 0xfb8) = 0xe;
    *(byte *)(table + 0xfc0) = 2;
    *(const char **)(table + 0xfc8) = s_Ancient_Greek_Numbers_005dee40;
    *(word_t *)(table + 0xfd0) = 0x15;
    *(byte *)(table + 0xfd8) = 2;
    *(const char **)(table + 0xfe0) = s_Ancient_Symbols_005dee56;
    *(word_t *)(table + 0xfe8) = 0xf;
    *(byte *)(table + 0xff0) = 2;
    *(const char **)(table + 0xff8) = s_Phaistos_Disc_005dee66;
    *(word_t *)(table + 0x1000) = 0xd;
    *(word_t *)(table + 0x11c8) = 0x10;
    *(byte *)(table + 0x11d0) = 2;
    *(const char **)(table + 0x11d8) = s_Palmyrene_005dde01;
    *(byte *)(table + 0x11e8) = 2;
    *(const char **)(table + 0x11f0) = s_Nabataean_005ddced;
    *(byte *)(table + 0x1200) = 2;
    *(const char **)(table + 0x1208) = s_Hatran_005ddadd;
    *(byte *)(table + 0x1218) = 2;
    *(const char **)(table + 0x1220) = s_Phoenician_005dde20;
    *(byte *)(table + 0x1230) = 2;
    *(const char **)(table + 0x1238) = s_Lydian_005ddc10;
    *(byte *)(table + 0x1248) = 2;
    *(const char **)(table + 0x1250) = s_Meroitic_Hieroglyphs_005ddcb0;
    *(word_t *)(table + 0x1258) = 0x14;
    *(byte *)(table + 0x1260) = 2;
    *(const char **)(table + 0x1268) = s_Meroitic_Cursive_005ddc90;
    *(word_t *)(table + 0x1270) = 0x10;
    *(byte *)(table + 0x1278) = 2;
    *(const char **)(table + 0x1280) = s_Kharoshthi_005ddba3;
    *(byte *)(table + 0x1290) = 2;
    *(const char **)(table + 0x1298) = s_Old_South_Arabian_005dddb0;
    *(word_t *)(table + 0x12a0) = 0x11;
    *(byte *)(table + 0x12a8) = 2;
    *(const char **)(table + 0x12e0) = s_Avestan_005dd906;
    *(byte *)(table + 0x12f0) = 2;
    *(const char **)(table + 0x12f8) = s_Inscriptional_Parthian_005ddb40;
    *(word_t *)(table + 0x1300) = 0x16;
    *(byte *)(table + 0x1308) = 2;
    *(const char **)(table + 0x1310) = s_Inscriptional_Pahlavi_005ddb20;
    *(word_t *)(table + 0x1318) = 0x15;
    *(byte *)(table + 0x1320) = 2;
    *(const char **)(table + 0x1328) = s_Psalter_Pahlavi_005dde2b;
    *(word_t *)(table + 0x1330) = 0xf;
    *(byte *)(table + 0x1338) = 2;
    *(const char **)(table + 0x1340) = s_Old_Turkic_005dddc2;
    *(byte *)(table + 0x1350) = 2;
    *(const char **)(table + 0x1358) = s_Old_Hungarian_005ddd56;
    *(word_t *)(table + 0x1360) = 0xd;
    *(byte *)(table + 0x1368) = 2;
    *(const char **)(table + 0x1370) = s_Hanifi_Rohingya_005ddac5;
    *(byte *)(table + 0x1380) = 2;
    *(const char **)(table + 0x1388) = s_Rumi_Numeral_Symbols_005deee0;
    *(word_t *)(table + 0x1390) = 0x14;
    *(byte *)(table + 0x1398) = 2;
    *(const char **)(table + 0x13a0) = s_Yezidi_005ddf87;
    *(byte *)(table + 0x13b0) = 2;
    *(const char **)(table + 0x13b8) = s_Old_Sogdian_005ddd99;
    *(word_t *)(table + 0x13c0) = 0xb;
    *(byte *)(table + 0x13c8) = 2;
    *(const char **)(table + 0x13d0) = s_Sogdian_005dde89;
    *(byte *)(table + 0x13e0) = 2;
    *(const char **)(table + 0x13e8) = s_Old_Uyghur_005dddcd;
    *(byte *)(table + 0x13f8) = 2;
    *(const char **)(table + 0x1400) = s_Chorasmian_005dd9b8;
    *(byte *)(table + 0x1410) = 2;
    *(const char **)(table + 0x1418) = s_Elymaic_005dda4d;
    *(byte *)(table + 0x1428) = 2;
    *(const char **)(table + 0x1430) = s_Brahmi_005dd948;
    *(byte *)(table + 0x1440) = 2;
    *(const char **)(table + 0x1448) = s_Kaithi_005ddb60;
    *(byte *)(table + 0x1458) = 2;
    *(const char **)(table + 0x1460) = s_Sora_Sompeng_005dde91;
    *(word_t *)(table + 0x1468) = 0xc;
    *(byte *)(table + 0x1470) = 2;
    *(const char **)(table + 0x1478) = s_Chakma_005dd9a3;
    *(byte *)(table + 0x1488) = 2;
    *(const char **)(table + 0x1490) = s_Mahajani_005ddc21;
    *(byte *)(table + 0x14a0) = 2;
    *(const char **)(table + 0x14a8) = s_Sharada_005dde5d;
    *(byte *)(table + 0x14b8) = 2;
    *(const char **)(table + 0x14c0) = s_Sinhala_Archaic_Numbers_005def00;
    *(word_t *)(table + 0x14c8) = 0x17;
    *(byte *)(table + 0x14d0) = 2;
    *(const char **)(table + 0x14d8) = s_Khojki_005ddbca;
    *(byte *)(table + 0x14e8) = 2;
    *(const char **)(table + 0x14f0) = s_Multani_005ddcdd;
    *(byte *)(table + 0x1500) = 2;
    *(const char **)(table + 0x1508) = s_Khudawadi_005ddbd1;
    *(byte *)(table + 0x1518) = 2;
    *(const char **)(table + 0x1520) = s_Grantha_005dda7f;
    *(byte *)(table + 0x1530) = 2;
    *(byte *)(table + 0x1548) = 2;
    *(const char **)(table + 0x1550) = s_Tirhuta_005ddf34;
    *(byte *)(table + 0x1560) = 2;
    *(const char **)(table + 0x1568) = s_Siddham_005dde6d;
    *(byte *)(table + 0x1578) = 2;
    *(byte *)(table + 0x1590) = 2;
    *(const char **)(table + 0x1598) = s_Mongolian_Supplement_005def20;
    *(word_t *)(table + 0x15a0) = 0x14;
    *(byte *)(table + 0x15a8) = 2;
    *(const char **)(table + 0x15b0) = s_Takri_005ddef6;
    *(byte *)(table + 0x15c0) = 2;
    *(byte *)(table + 0x15d8) = 2;
    *(const char **)(table + 0x15e0) = s_Dogra_005dda18;
    *(byte *)(table + 0x15f0) = 2;
    *(const char **)(table + 0x15f8) = s_Warang_Citi_005ddf7b;
    *(word_t *)(table + 0x1600) = 0xb;
    *(byte *)(table + 0x1608) = 2;
    *(const char **)(table + 0x1610) = s_Dives_Akuru_005dda0c;
    *(word_t *)(table + 0x1618) = 0xb;
    *(byte *)(table + 0x1620) = 2;
    *(const char **)(table + 0x1628) = s_Nandinagari_005ddd03;
    *(word_t *)(table + 0x1630) = 0xb;
    *(byte *)(table + 0x1638) = 2;
    *(const char **)(table + 0x1640) = s_Zanabazar_Square_005ddfa0;
    *(word_t *)(table + 0x1648) = 0x10;
    *(byte *)(table + 0x1650) = 2;
    *(const char **)(table + 0x1658) = s_Soyombo_005dde9e;
    *(byte *)(table + 0x1668) = 2;
    *(const char **)(table + 0x1670) = s_Unified_Canadian_Aboriginal_Syll_005def40;
    *(word_t *)(table + 0x1678) = 0x30;
    *(byte *)(table + 0x1680) = 2;
    *(byte *)(table + 0x16c8) = 2;
    *(const char **)(table + 0x16d0) = s_Masaram_Gondi_005ddc57;
    *(word_t *)(table + 0x16d8) = 0xd;
    *(byte *)(table + 0x16e0) = 2;
    *(const char **)(table + 0x16e8) = s_Gunjala_Gondi_005dda96;
    *(word_t *)(table + 0x16f0) = 0xd;
    *(byte *)(table + 0x16f8) = 2;
    *(const char **)(table + 0x1700) = s_Makasar_005ddc2a;
    *(byte *)(table + 0x1710) = 2;
    *(const char **)(table + 0x1718) = s_Lisu_Supplement_005def71;
    *(word_t *)(table + 0x1720) = 0xf;
    *(byte *)(table + 0x1728) = 2;
    *(const char **)(table + 0x1730) = s_Tamil_Supplement_005def90;
    *(word_t *)(table + 0x1738) = 0x10;
    *(byte *)(table + 0x1740) = 2;
    *(const char **)(table + 0x1748) = s_Cuneiform_005dd9d1;
    *(byte *)(table + 0x1758) = 2;
    *(const char **)(table + 0x1760) = s_Cuneiform_Numbers_and_Punctuatio_005defb0;
    *(word_t *)(table + 0x1768) = 0x21;
    *(byte *)(table + 0x1770) = 2;
    *(const char **)(table + 0x1778) = s_Early_Dynastic_Cuneiform_005defe0;
    *(word_t *)(table + 0x1780) = 0x18;
    *(byte *)(table + 0x1788) = 2;
    *(word_t *)(table + 0x1798) = 0xc;
    *(byte *)(table + 0x17a0) = 2;
    *(const char **)(table + 0x17a8) = s_Egyptian_Hieroglyphs_005dda30;
    *(word_t *)(table + 0x17b0) = 0x14;
    *(byte *)(table + 0x17b8) = 2;
    *(const char **)(table + 0x17c0) = s_Egyptian_Hieroglyph_Format_Contr_005df000;
    *(word_t *)(table + 0x17c8) = 0x23;
    *(const char **)(table + 0x17d8) = s_Anatolian_Hieroglyphs_005dd8e0;
    *(word_t *)(table + 0x17e0) = 0x15;
    *(byte *)(table + 0x17e8) = 2;
    *(byte *)(table + 0x1800) = 2;
    *(byte *)(table + 0x1818) = 2;
    *(const char **)(table + 0x1820) = s_Tangsa_005ddf02;
    *(byte *)(table + 0x1830) = 2;
    *(const char **)(table + 0x1838) = s_Bassa_Vah_005dd91d;
    *(byte *)(table + 0x1848) = 2;
    *(const char **)(table + 0x1850) = s_Pahawh_Hmong_005dddf4;
    *(word_t *)(table + 0x1858) = 0xc;
    *(byte *)(table + 0x1860) = 2;
    *(const char **)(table + 0x1868) = s_Medefaidrin_005ddc65;
    *(word_t *)(table + 0x1870) = 0xb;
    *(byte *)(table + 0x1878) = 2;
    *(byte *)(table + 0x1890) = 2;
    *(const char **)(table + 0x1898) = s_Ideographic_Symbols_and_Punctuat_005df050;
    *(word_t *)(table + 0x18a0) = 0x23;
    *(byte *)(table + 0x18a8) = 2;
    *(const char **)(table + 0x18b0) = s_Tangut_005ddf09;
    *(byte *)(table + 0x18c0) = 2;
    *(const char **)(table + 0x18c8) = s_Tangut_Components_005df080;
    *(word_t *)(table + 0x18d0) = 0x11;
    *(byte *)(table + 0x18d8) = 2;
    *(const char **)(table + 0x18e0) = s_Khitan_Small_Script_005ddbb0;
    *(word_t *)(table + 0x18e8) = 0x13;
    *(byte *)(table + 0x18f0) = 2;
    *(const char **)(table + 0x18f8) = s_Tangut_Supplement_005df0a0;
    *(word_t *)(table + 0x1900) = 0x11;
    *(byte *)(table + 0x1908) = 2;
    *(const char **)(table + 0x1910) = s_Kana_Extended_B_005df0b2;
    *(word_t *)(table + 0x1918) = 0xf;
    *(byte *)(table + 0x1920) = 2;
    *(const char **)(table + 0x1928) = s_Kana_Supplement_005df0c2;
    *(word_t *)(table + 0x1930) = 0xf;
    *(byte *)(table + 0x1938) = 2;
    *(const char **)(table + 0x1940) = s_Kana_Extended_A_005df0d2;
    *(word_t *)(table + 0x1948) = 0xf;
    *(byte *)(table + 0x1950) = 2;
    *(const char **)(table + 0x1958) = s_Small_Kana_Extension_005df0f0;
    *(word_t *)(table + 0x1960) = 0x14;
    *(byte *)(table + 0x1968) = 2;
    *(const char **)(table + 0x1970) = s_Nushu_005ddd24;
    *(byte *)(table + 0x1980) = 2;
    *(const char **)(table + 0x1988) = s_Duployan_005dda1e;
    *(byte *)(table + 0x1998) = 2;
    *(const char **)(table + 0x19a0) = s_Shorthand_Format_Controls_005df110;
    *(word_t *)(table + 0x19a8) = 0x19;
    *(byte *)(table + 0x19b0) = 2;
    *(const char **)(table + 0x19b8) = s_Znamenny_Musical_Notation_005df130;
    *(word_t *)(table + 0x19c0) = 0x19;
    *(byte *)(table + 0x19c8) = 2;
    *(const char **)(table + 0x19d0) = s_Byzantine_Musical_Symbols_005df150;
    *(word_t *)(table + 0x19d8) = 0x19;
    *(byte *)(table + 0x19e0) = 2;
    *(const char **)(table + 0x19e8) = s_Musical_Symbols_005df16a;
    *(word_t *)(table + 0x19f0) = 0xf;
    *(byte *)(table + 0x19f8) = 2;
    *(const char **)(table + 0x1a00) = s_Ancient_Greek_Musical_Notation_005df180;
    *(word_t *)(table + 0x1a08) = 0x1e;
    *(byte *)(table + 0x1a10) = 2;
    *(const char **)(table + 0x1a18) = s_Mayan_Numerals_005df19f;
    *(word_t *)(table + 0x1a20) = 0xe;
    *(byte *)(table + 0x1a28) = 2;
    *(const char **)(table + 0x1a30) = s_Tai_Xuan_Jing_Symbols_005df1b0;
    *(word_t *)(table + 0x1a38) = 0x15;
    *(byte *)(table + 0x1a40) = 2;
    *(const char **)(table + 0x1a48) = s_Counting_Rod_Numerals_005df1d0;
    *(word_t *)(table + 0x1a50) = 0x15;
    *(byte *)(table + 0x1a58) = 2;
    *(const char **)(table + 0x1a60) = s_Mathematical_Alphanumeric_Symbol_005df1f0;
    *(word_t *)(table + 0x1a68) = 0x21;
    *(byte *)(table + 0x1a70) = 2;
    *(const char **)(table + 0x1a78) = s_Sutton_SignWriting_005df220;
    *(word_t *)(table + 0x1a80) = 0x12;
    *(byte *)(table + 0x1a88) = 2;
    *(const char **)(table + 0x1a90) = s_Latin_Extended_G_005df240;
    *(word_t *)(table + 0x1a98) = 0x10;
    *(byte *)(table + 0x1aa0) = 2;
    *(const char **)(table + 0x1aa8) = s_Glagolitic_Supplement_005df260;
    *(word_t *)(table + 0x1ab0) = 0x15;
    *(byte *)(table + 0x1ab8) = 2;
    *(const char **)(table + 0x1ac0) = s_Nyiakeng_Puachue_Hmong_005ddd30;
    *(word_t *)(table + 0x1ac8) = 0x16;
    *(byte *)(table + 0x1ad0) = 2;
    *(byte *)(table + 0x1ae8) = 2;
    *(const char **)(table + 0x1af0) = s_Wancho_005ddf74;
    *(byte *)(table + 0x1b00) = 2;
    *(const char **)(table + 0x1b08) = s_Ethiopic_Extended_B_005df280;
    *(word_t *)(table + 0x1b10) = 0x13;
    *(byte *)(table + 0x1b18) = 2;
    *(const char **)(table + 0x1b20) = s_Mende_Kikakui_005ddc7e;
    *(word_t *)(table + 0x1b28) = 0xd;
    *(byte *)(table + 0x1b30) = 2;
    *(const char **)(table + 0x1b38) = s_Adlam_005dd8cb;
    *(byte *)(table + 0x1b48) = 2;
    *(const char **)(table + 0x1b50) = s_Indic_Siyaq_Numbers_005df2a0;
    *(word_t *)(table + 0x1b58) = 0x13;
    *(byte *)(table + 0x1b60) = 2;
    *(const char **)(table + 0x1b68) = s_Ottoman_Siyaq_Numbers_005df2c0;
    *(word_t *)(table + 0x1b70) = 0x15;
    *(byte *)(table + 0x1b78) = 2;
    *(const char **)(table + 0x1b80) = s_Arabic_Mathematical_Alphabetic_S_005df2e0;
    *(word_t *)(table + 0x1b88) = 0x26;
    *(byte *)(table + 0x1b90) = 2;
    *(const char **)(table + 0x1b98) = s_Mahjong_Tiles_005df307;
    *(word_t *)(table + 0x1ba0) = 0xd;
    *(byte *)(table + 0x1ba8) = 2;
    *(const char **)(table + 0x1bb0) = s_Domino_Tiles_005df315;
    *(word_t *)(table + 0x1bb8) = 0xc;
    *(byte *)(table + 0x1bc0) = 2;
    *(const char **)(table + 0x1bc8) = s_Playing_Cards_005df322;
    *(word_t *)(table + 0x1bd0) = 0xd;
    *(byte *)(table + 0x1bd8) = 2;
    *(const char **)(table + 0x1be0) = s_Enclosed_Alphanumeric_Supplement_005df330;
    *(word_t *)(table + 0x1be8) = 0x20;
    *(byte *)(table + 0x1bf0) = 2;
    *(const char **)(table + 0x1bf8) = s_Enclosed_Ideographic_Supplement_005df360;
    *(word_t *)(table + 0x1c00) = 0x1f;
    *(byte *)(table + 0x1c08) = 2;
    *(const char **)(table + 0x1c10) = s_Miscellaneous_Symbols_and_Pictog_005df380;
    *(word_t *)(table + 0x1c18) = 0x25;
    *(byte *)(table + 0x1c20) = 2;
    *(const char **)(table + 0x1c28) = s_Emoticons_005df3a6;
    *(byte *)(table + 0x1c38) = 2;
    *(const char **)(table + 0x1c40) = s_Ornamental_Dingbats_005df3b0;
    *(word_t *)(table + 0x1c48) = 0x13;
    *(byte *)(table + 0x1c50) = 2;
    *(const char **)(table + 0x1c58) = s_Transport_and_Map_Symbols_005df3d0;
    *(word_t *)(table + 0x1c60) = 0x19;
    *(byte *)(table + 0x1c68) = 2;
    *(const char **)(table + 0x1c70) = s_Alchemical_Symbols_005df3f0;
    *(word_t *)(table + 0x1c78) = 0x12;
    *(byte *)(table + 0x1c80) = 2;
    *(const char **)(table + 0x1c88) = s_Geometric_Shapes_Extended_005df410;
    *(word_t *)(table + 0x1c90) = 0x19;
    *(byte *)(table + 0x1c98) = 2;
    *(const char **)(table + 0x1ca0) = s_Supplemental_Arrows_C_005df430;
    *(word_t *)(table + 0x1ca8) = 0x15;
    *(byte *)(table + 0x1cb0) = 2;
    *(const char **)(table + 0x1cb8) = s_Supplemental_Symbols_and_Pictogr_005df450;
    *(word_t *)(table + 0x1cc0) = 0x24;
    *(byte *)(table + 0x1cc8) = 2;
    *(const char **)(table + 0x1cd0) = s_Chess_Symbols_005df475;
    *(word_t *)(table + 0x1cd8) = 0xd;
    *(byte *)(table + 0x1ce0) = 2;
    *(const char **)(table + 0x1ce8) = s_Symbols_and_Pictographs_Extended_005df490;
    *(word_t *)(table + 0x1cf0) = 0x22;
    *(byte *)(table + 0x1cf8) = 2;
    *(const char **)(table + 0x1d00) = s_Symbols_for_Legacy_Computing_005df4c0;
    *(word_t *)(table + 0x1d08) = 0x1c;
    *(byte *)(table + 0x1d10) = 2;
    *(const char **)(table + 0x1d18) = s_CJK_Unified_Ideographs_Extension_005df4e0;
    *(word_t *)(table + 0x1d20) = 0x22;
    *(byte *)(table + 0x1d28) = 2;
    *(const char **)(table + 0x1d30) = s_CJK_Unified_Ideographs_Extension_005df510;
    *(word_t *)(table + 0x1d38) = 0x22;
    *(byte *)(table + 0x1d40) = 2;
    *(const char **)(table + 0x1d48) = s_CJK_Unified_Ideographs_Extension_005df540;
    *(word_t *)(table + 0x1d50) = 0x22;
    *(byte *)(table + 0x1d58) = 2;
    *(const char **)(table + 0x1d60) = s_CJK_Unified_Ideographs_Extension_005df570;
    *(word_t *)(table + 0x1d68) = 0x22;
    *(byte *)(table + 0x1d70) = 2;
    *(const char **)(table + 0x1d78) = s_CJK_Unified_Ideographs_Extension_005df5a0;
    *(word_t *)(table + 0x1d80) = 0x22;
    *(byte *)(table + 0x1d88) = 2;
    *(const char **)(table + 0x1d90) = s_CJK_Compatibility_Ideographs_Sup_005df5d0;
    *(word_t *)(table + 0x1d98) = 0x27;
    *(byte *)(table + 0x1da0) = 2;
    *(const char **)(table + 0x1da8) = s_CJK_Unified_Ideographs_Extension_005df600;
    *(word_t *)(table + 0x1db0) = 0x22;
    *(byte *)(table + 0x1db8) = 2;
    *(byte *)(table + 0x1dd0) = 2;
    *(const char **)(table + 0x1dd8) = s_Variation_Selectors_Supplement_005df630;
    *(word_t *)(table + 0x1de0) = 0x1e;
    *(byte *)(table + 0x1de8) = 2;
    *(const char **)(table + 0x1df0) = s_Supplementary_Private_Use_Area_A_005df650;
    *(word_t *)(table + 0x1df8) = 0x20;
    *(byte *)(table + 0x1e00) = 2;
    *(const char **)(table + 0x1e08) = s_Supplementary_Private_Use_Area_B_005df680;
    *(word_t *)(table + 0x1e10) = 0x20;
    *(byte *)(table + 0x1e18) = 2;
    *(const char **)(table + 0x1e20) = s_No_Block_005df6a1;
    *(byte *)(table + 0x1e30) = 2;
    /* 000b43d0 (retain/release), 002ad78c returns the count to report. */
    sk_x_000b43d0();
    uVar4 = sk_x_002ad78c();
    sk_x_0036b118(table);
    sk_x_003a25d4();
    /* Round the reported block count up to the enclosing 0x40-boundary bucket. */
    if (0x7f < uVar4) {
        if (uVar4 - 0x80 < 0x40) {
            uVar4 = (uVar4 - 0x80) | 0x80;
        } else if (uVar4 - 0xc0 < 0x40) {
            uVar4 = (uVar4 - 0xc0) | 0xc0;
        } else if (uVar4 - 0x100 < 0x40) {
            uVar4 = (uVar4 - 0x100) | 0x100;
        } else {
            uVar4 = (uVar4 != 0x140) ? 0x141 : 0x140;
        }
    }
    sk_x_00084234(uVar4, self);
}
