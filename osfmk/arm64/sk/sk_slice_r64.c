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
typedef unsigned int uint;

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
extern cl4_pair_t sk_x_0006b42c();      /* FUN_0006b42c (16-byte) */
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
extern cl4_pair_t sk_x_000b43f4();   /* FUN_000b43f4 */
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
extern cl4_pair_t sk_x_00463ad4();   /* FUN_00463ad4 */
extern cl4_pair_t sk_x_00463b08();   /* FUN_00463b08 */
extern cl4_pair_t sk_x_00463b2c();   /* FUN_00463b2c */
extern cl4_pair_t sk_x_00463b50();   /* FUN_00463b50 */
extern cl4_pair_t sk_x_00463b98();   /* FUN_00463b98 */
extern cl4_pair_t sk_x_00463c18();   /* FUN_00463c18 */
extern cl4_pair_t sk_x_00463c38();   /* FUN_00463c38 */
extern cl4_pair_t sk_x_00463c58();   /* FUN_00463c58 */
extern cl4_pair_t sk_x_00463c78();   /* FUN_00463c78 */
extern cl4_pair_t sk_x_00463c98();   /* FUN_00463c98 */
extern cl4_pair_t sk_x_00463cfc();   /* FUN_00463cfc */
extern cl4_pair_t sk_x_00463d1c();   /* FUN_00463d1c */
extern cl4_pair_t sk_x_00463d3c();   /* FUN_00463d3c */
extern cl4_pair_t sk_x_00463d5c();   /* FUN_00463d5c */
extern cl4_pair_t sk_x_00463d7c();   /* FUN_00463d7c */
extern cl4_pair_t sk_x_00463d9c();   /* FUN_00463d9c */
extern cl4_pair_t sk_x_00464000();   /* FUN_00464000 */
extern cl4_pair_t sk_x_0046414c();   /* FUN_0046414c */
extern cl4_pair_t sk_x_004641a0();   /* FUN_004641a0 */
extern cl4_pair_t sk_x_004641b8();   /* FUN_004641b8 */
extern cl4_pair_t sk_x_004641d0();   /* FUN_004641d0 */
extern cl4_pair_t sk_x_004643cc();   /* FUN_004643cc */
extern cl4_pair_t sk_x_004643d8();   /* FUN_004643d8 */
extern cl4_pair_t sk_x_004643f0();   /* FUN_004643f0 */
extern cl4_pair_t sk_x_00464408();   /* FUN_00464408 */
extern cl4_pair_t sk_x_00464420();   /* FUN_00464420 */
extern cl4_pair_t sk_x_00464438();   /* FUN_00464438 */
extern cl4_pair_t sk_x_00464450();   /* FUN_00464450 */
extern cl4_pair_t sk_x_00464468();   /* FUN_00464468 */
extern cl4_pair_t sk_x_00464480();   /* FUN_00464480 */
extern cl4_pair_t sk_x_00464688();   /* FUN_00464688 */
extern cl4_pair_t sk_x_00464694();   /* FUN_00464694 */
extern cl4_pair_t sk_x_004646ac();   /* FUN_004646ac */
extern cl4_pair_t sk_x_004646c4();   /* FUN_004646c4 */
extern cl4_pair_t sk_x_004646dc();   /* FUN_004646dc */
extern cl4_pair_t sk_x_004646f4();   /* FUN_004646f4 */
extern cl4_pair_t sk_x_0046470c();   /* FUN_0046470c */
extern cl4_pair_t sk_x_00464724();   /* FUN_00464724 */
extern cl4_pair_t sk_x_0046473c();   /* FUN_0046473c */
extern cl4_pair_t sk_x_00464754();   /* FUN_00464754 */
extern cl4_pair_t sk_x_0046476c();   /* FUN_0046476c */
extern cl4_pair_t sk_x_00464784();   /* FUN_00464784 */
extern cl4_pair_t sk_x_0046479c();   /* FUN_0046479c */
extern cl4_pair_t sk_x_00464b40();   /* FUN_00464b40 */
extern cl4_pair_t sk_x_00464b54();   /* FUN_00464b54 */
extern cl4_pair_t sk_x_00464b68();   /* FUN_00464b68 */
extern cl4_pair_t sk_x_00464b7c();   /* FUN_00464b7c */
extern cl4_pair_t sk_x_00464b90();   /* FUN_00464b90 */
extern cl4_pair_t sk_x_00464ba4();   /* FUN_00464ba4 */
extern cl4_pair_t sk_x_00464bf4();   /* FUN_00464bf4 */
extern cl4_pair_t sk_x_00464c08();   /* FUN_00464c08 */
extern cl4_pair_t sk_x_00464c1c();   /* FUN_00464c1c */
extern cl4_pair_t sk_x_00464c30();   /* FUN_00464c30 */
extern cl4_pair_t sk_x_00464c44();   /* FUN_00464c44 */
extern cl4_pair_t sk_x_00464c58();   /* FUN_00464c58 */
extern cl4_pair_t sk_x_00464c6c();   /* FUN_00464c6c */
extern cl4_pair_t sk_x_00464c80();   /* FUN_00464c80 */
extern cl4_pair_t sk_x_00464c94();   /* FUN_00464c94 */
extern cl4_pair_t sk_x_00464ca8();   /* FUN_00464ca8 */
extern cl4_pair_t sk_x_00464cbc();   /* FUN_00464cbc */
extern cl4_pair_t sk_x_00464cd0();   /* FUN_00464cd0 */
extern cl4_pair_t sk_x_00464ee4();   /* FUN_00464ee4 */
extern cl4_pair_t sk_x_00464f04();   /* FUN_00464f04 */
extern cl4_pair_t sk_x_00464f14();   /* FUN_00464f14 */
extern cl4_pair_t sk_x_00464f64();   /* FUN_00464f64 */
extern cl4_pair_t sk_x_00464f74();   /* FUN_00464f74 */
extern cl4_pair_t sk_x_00464fa4();   /* FUN_00464fa4 */
extern cl4_pair_t sk_x_00464fb4();   /* FUN_00464fb4 */
extern cl4_pair_t sk_x_00464fe0();   /* FUN_00464fe0 */
extern cl4_pair_t sk_x_00464ff0();   /* FUN_00464ff0 */
extern cl4_pair_t sk_x_00465000();   /* FUN_00465000 */
extern cl4_pair_t sk_x_00465028();   /* FUN_00465028 */
extern cl4_pair_t sk_x_004651d4();   /* FUN_004651d4 */
extern cl4_pair_t sk_x_004651e4();   /* FUN_004651e4 */
extern cl4_pair_t sk_x_004651f4();   /* FUN_004651f4 */
extern cl4_pair_t sk_x_00465204();   /* FUN_00465204 */
extern cl4_pair_t sk_x_00465214();   /* FUN_00465214 */
extern cl4_pair_t sk_x_00465224();   /* FUN_00465224 */
extern unsigned long sk_x_00465240();   /* FUN_00465240 */
extern unsigned long sk_x_004652d4();   /* FUN_004652d4 */
extern unsigned long sk_x_00465428();   /* FUN_00465428 */
extern cl4_pair_t sk_x_004659e0();   /* FUN_004659e0 */
extern cl4_pair_t sk_x_004659e8();   /* FUN_004659e8 */
extern cl4_pair_t sk_x_00465a38();   /* FUN_00465a38 */
extern cl4_pair_t sk_x_00465ab8();   /* FUN_00465ab8 */
extern cl4_pair_t sk_x_00465b64();   /* FUN_00465b64 */
extern cl4_pair_t sk_x_00465b98();   /* FUN_00465b98 */
extern cl4_pair_t sk_x_00465be0();   /* FUN_00465be0 */
extern cl4_pair_t sk_x_00465bf4();   /* FUN_00465bf4 */
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
static long sk_arr_ensure2_004564e4(word_t param_1, long param_2, word_t param_3, long param_4,
                                    word_t param_5, word_t param_6, word_t param_7);
static long sk_arr_ensure3_0045659c(word_t param_1, long param_2, word_t param_3, long param_4,
                                    word_t param_5, word_t param_6, word_t param_7, word_t param_8);
static long sk_arr_grow2_00456650(word_t param_1, word_t param_2, word_t param_3, long param_4);
static long sk_arr_grow3_00456714(word_t param_1, word_t param_2, word_t param_3, long param_4);
static cl4_pair_t sk_str_parse_int_00457bec(byte *param_1, long param_2, long param_3);
static bool sk_str_eql_00456d90(word_t param_1, word_t param_2, long param_3);
static void sk_str_guts_init_full_00455778(word_t param_1, word_t param_2, word_t param_3, word_t param_4);
static void sk_str_elem_append_00455990(word_t param_1, word_t param_2, word_t param_3);
static word_t sk_tag_read_45_00458d04(long param_1);
static void sk_tag_clear_45_00458d10(long param_1);
static void sk_script_wit_apply5_00458d30(word_t param_1, word_t param_2);
static word_t sk_script_wit_run5_00458d40(word_t param_1);
static void sk_script_wit_apply_004589e8(word_t param_1, word_t param_2);
static word_t sk_buf_copy_020_004568d8(long param_1, long param_2, word_t param_3, long param_4);
static word_t sk_buf_copy_018_00456b28(long param_1, long param_2, word_t param_3, long param_4);
static word_t sk_utf32_scalar_fill_00458018(word_t *param_1, long param_2, word_t param_3);
static long sk_utf32_range_table_00457f5c(void);
static void sk_str_elem_type_00455a68(word_t *param_1, long param_2);

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
/* FUN_0045399c @ 0x0045399c   (est. sk_script_name_0045399c)
 * Ghidra: undefined1[16] FUN_0045399c(undefined2 param_1)
 * Maps the Character.Unicode.Script / Block enum value to its 16-byte
 * small-string name. Each case returns either a packed small-string
 * (the {length<<56|bytes} pair), a helper-built pair (004643d8 / 00464408 /
 * ... script-name builders), or a name assembled from raw UTF-16 words
 * (e.g. 0x614c5f6369736142 = "Basic_Latin" tag). Fall-through cases
 * (those ending in break) use the post-switch builder 004643cc(pcVar4,
 * 0xd000000000000010). Unknown/default enums yield the 0x42-tagged pair.
 * Confidence: high (full switch transcribed; every case preserved)
 * Notes: extraout_x1 words capture the x1 half of the prior 16-byte call. */
static cl4_pair_t sk_script_name_0045399c(word_t param_1)
{
    cl4_pair_t au;
    const char *pcVar4;
    word_t uVar1 = 0x614c5f6369736142;  /* "Basic_Latin" low tag */
    word_t uVar2 = 0xe100000000000000;
    word_t uVar3 = 0xeb000000006e6974;  /* high tag */
    switch (param_1) {
    default:
        au.hi = uVar3;
        au.lo = uVar1;
        return au;
    case 1:
        pcVar4 = s_Latin_1_Supplement_005de210;
        au = sk_x_004643d8(pcVar4);
        return au;
    case 2:
        pcVar4 = s_Latin_Extended_A_005de230;
        break;
    case 3:
        pcVar4 = s_Latin_Extended_B_005de250;
        break;
    case 4:
        au.hi = 0xee00736e6f69736e;
        au.lo = 0x657478455f415049;
        return au;
    case 5:
        pcVar4 = s_Spacing_Modifier_Letters_005de270;
        au = sk_x_00464480(pcVar4);
        return au;
    case 6:
        pcVar4 = s_Combining_Diacritical_Marks_005de290;
        au = sk_x_004643cc(pcVar4);
        uVar3 = 0xb;
        au = sk_x_00465028(uVar3);
        return au;
    case 7:
        pcVar4 = s_Greek_and_Coptic_005de2b0;
        break;
    case 8:
        uVar3 = 0xe800000000000000;
        uVar2 = 0x6c6c69727943;
        au.lo = uVar2 | 0x6369000000000000;
        au.hi = uVar3;
        return au;
    case 9:
        pcVar4 = s_Cyrillic_Supplement_005de2d0;
        au = sk_x_00464408(pcVar4);
        return au;
    case 10:
        uVar2 = 0x696e656d7241;
        au.lo = uVar2 | 0x6e61000000000000;
        au.hi = 0xe800000000000000;
        return au;
    case 0xb:
        au = sk_x_00464ca8();
        return au;
    case 0xc:
        uVar3 = 0x62617241;
        au = sk_x_00465b64(uVar3,0xe600000000000000);
        return au;
    case 0xd:
        au = sk_x_00464c94();
        return au;
    case 0xe:
        pcVar4 = s_Arabic_Supplement_005de2f0;
        au = sk_x_00464438(pcVar4);
        return au;
    case 0xf:
        au = sk_x_00464c08();
        return au;
    case 0x10:
        au.hi = 0xe300000000000000;
        au.lo = 0x6f4b4e;
        return au;
    case 0x11:
        uVar3 = 0x61746972616d6153;
        au = sk_x_00464ee4(uVar3,0x6e);
        return au;
    case 0x12:
        uVar3 = 0x646e614d;
        au = sk_x_00464688(uVar3,0xe700000000000000);
        return au;
    case 0x13:
        pcVar4 = s_Syriac_Supplement_005de310;
        au = sk_x_00464438(pcVar4);
        return au;
    case 0x14:
        pcVar4 = s_Arabic_Extended_B_005de330;
        au = sk_x_00464438(pcVar4);
        return au;
    case 0x15:
        pcVar4 = s_Arabic_Extended_A_005de350;
        au = sk_x_00464438(pcVar4);
        return au;
    case 0x16:
        au = sk_x_00463c98();
        return au;
    case 0x17:
        uVar2 = 0x6c61676e6542;
        au.lo = uVar2 | 0x69000000000000;
        au.hi = 0xe700000000000000;
        return au;
    case 0x18:
        au = sk_x_004646ac();
        return au;
    case 0x19:
        au = sk_x_004646c4();
        return au;
    case 0x1a:
        uVar2 = 0x7969724f;
        au.lo = uVar2 | 0x6100000000;
        au.hi = 0xe500000000000000;
        return au;
    case 0x1b:
        au = sk_x_00464fb4(0x614c5f6369736142,0xe500000000000000);
        return au;
    case 0x1c:
        au = sk_x_00464bf4();
        return au;
    case 0x1d:
        uVar2 = 0x6e6e614b;
        uVar2 = uVar2 | 0x646100000000;
        au.lo = uVar2 | 0x61000000000000;
        au.hi = 0xe700000000000000;
        return au;
    case 0x1e:
        au = sk_x_00464ba4(0x614c5f6369736142,0xe90000000000006d);
        return au;
    case 0x1f:
        uVar2 = 0x6c61686e6953;
        au.lo = uVar2 | 0x61000000000000;
        au.hi = 0xe700000000000000;
        return au;
    case 0x20:
        au = sk_x_004651d4();
        return au;
    case 0x21:
        au = sk_x_00464f14();
        return au;
    case 0x22:
        uVar2 = 0x617465626954;
        au.lo = uVar2 | 0x6e000000000000;
        au.hi = 0xe700000000000000;
        return au;
    case 0x23:
        uVar3 = 0x616d6e61794d;
        au = sk_x_00465ab8(uVar3,0xe700000000000000);
        return au;
    case 0x24:
        uVar2 = 0x6967726f6547;
        LAB_00454d70:
        au.lo = uVar2 | 0x6e61000000000000;
        au.hi = 0xe800000000000000;
        return au;
    case 0x25:
        au.hi = 0xeb000000006f6d61;
        au.lo = 0x4a5f6c75676e6148;
        return au;
    case 0x26:
        uVar3 = 0xe800000000000000;
        uVar2 = 0x706f69687445;
        au.lo = uVar2 | 0x6369000000000000;
        au.hi = uVar3;
        return au;
    case 0x27:
        pcVar4 = s_Ethiopic_Supplement_005de370;
        au = sk_x_00464408(pcVar4);
        return au;
    case 0x28:
        au = sk_x_004646dc();
        return au;
    case 0x29:
        au = sk_x_00464420(s_Unified_Canadian_Aboriginal_Syll_005de390);
        return au;
    case 0x2a:
        uVar3 = 0x6168674f;
        au = sk_x_00465b98(uVar3,0xe500000000000000);
        return au;
    case 0x2b:
        au = sk_x_00464f74(0x614c5f6369736142,0xe500000000000000);
        return au;
    case 0x2c:
        au = sk_x_004641b8();
        return au;
    case 0x2d:
        uVar2 = 0x6f6e756e6148;
        au.lo = uVar2 | 0x6f000000000000;
        au.hi = 0xe700000000000000;
        return au;
    case 0x2e:
        au = sk_x_00465000(0x614c5f6369736142,0xe500000000000000);
        return au;
    case 0x2f:
        au = sk_x_00464724();
        return au;
    case 0x30:
        au = sk_x_00464fe0(0x614c5f6369736142,0xe500000000000000);
        return au;
    case 0x31:
        uVar3 = 0x61696c6f676e6f4d;
        au = sk_x_00464ee4(uVar3,0x6e);
        return au;
    case 0x32:
        au = sk_x_004643cc(s_Unified_Canadian_Aboriginal_Syll_005de3c0);
        au.lo = 0xd00000000000002e;
        return au;
    case 0x33:
        au.hi = 0xe500000000000000;
        au.lo = 0x75626d694c;
        return au;
    case 0x34:
        au = sk_x_00464c58();
        return au;
    case 0x35:
        au = sk_x_00463d7c();
        return au;
    case 0x36:
        uVar2 = 0x5f72656d684b;
        uVar2 = uVar2 | 0x7953000000000000;
        uVar3 = 0x736c6f626d;
    case 0x37:
        uVar3 = 0x69677542;
        au = sk_x_00465bf4(uVar3,0xe800000000000000);
        return au;
    case 0x38:
        au = sk_x_00464754();
        return au;
    case 0x39:
        pcVar4 = s_Combining_Diacritical_Marks_Exte_005de400;
        au = sk_x_004643cc(pcVar4);
        au.lo = 0xd000000000000024;
        return au;
    case 0x3a:
        uVar3 = 0x696c6142;
        au = sk_x_00465bf4(uVar3,0xe800000000000000);
        return au;
    case 0x3b:
        au = sk_x_00464b68(0x614c5f6369736142,0xe900000000000065);
        return au;
    case 0x3c:
        au = sk_x_00464f64(0x614c5f6369736142,0xe500000000000000);
        return au;
    case 0x3d:
        au = sk_x_00464c80();
        return au;
    case 0x3e:
        au = sk_x_004646f4();
        return au;
    case 0x3f:
        pcVar4 = s_Cyrillic_Extended_C_005de430;
        au = sk_x_00464408(pcVar4);
        return au;
    case 0x40:
        pcVar4 = s_Georgian_Extended_005de450;
        au = sk_x_00464438(pcVar4);
        return au;
    case 0x41:
        pcVar4 = s_Sundanese_Supplement_005de470;
        au = sk_x_00464468(pcVar4);
        return au;
    case 0x42:
        pcVar4 = s_Vedic_Extensions_005de490;
        break;
    case 0x43:
        pcVar4 = s_Phonetic_Extensions_005de4b0;
        au = sk_x_00464408(pcVar4);
        return au;
    case 0x44:
        pcVar4 = s_Phonetic_Extensions_Supplement_005de4d0;
        au = sk_x_004643cc(pcVar4);
        au.lo = 0xd00000000000001e;
        return au;
    case 0x45:
        pcVar4 = s_Combining_Diacritical_Marks_Supp_005de4f0;
        au = sk_x_004643cc(pcVar4);
        au.lo = 0xd000000000000026;
        return au;
    case 0x46:
        pcVar4 = s_Latin_Extended_Additional_005de520;
        au = sk_x_004643cc(pcVar4);
        uVar3 = 9;
        au = sk_x_00465028(uVar3);
        return au;
    case 0x47:
        au.hi = 0xee006465646e6574;
        au.lo = 0x78455f6b65657247;
        return au;
    case 0x48:
        pcVar4 = s_General_Punctuation_005de550;
        au = sk_x_00464408(pcVar4);
        return au;
    case 0x49:
        pcVar4 = s_Superscripts_and_Subscripts_005de570;
        au = sk_x_004643cc(pcVar4);
        uVar3 = 0xb;
        au = sk_x_00465028(uVar3);
        return au;
    case 0x4a:
        pcVar4 = s_Currency_Symbols_005de590;
        break;
    case 0x4b:
        au = sk_x_00464450(s_Combining_Diacritical_Marks_for__005de5b0,0x614c5f6369736142,
        0xeb000000006e6974);
        return au;
    case 0x4c:
        pcVar4 = s_Letterlike_Symbols_005de5e0;
        au = sk_x_004643d8(pcVar4);
        return au;
    case 0x4d:
        au.hi = 0xec000000736d726f;
        au.lo = 0x465f7265626d754e;
        return au;
    case 0x4e:
        au.hi = 0xe600000000000000;
        au.lo = 0x73776f727241;
        return au;
    case 0x4f:
        pcVar4 = s_Mathematical_Operators_005de610;
        au = sk_x_004643f0(pcVar4);
        return au;
    case 0x50:
        pcVar4 = s_Miscellaneous_Technical_005de630;
        au = sk_x_004643cc(pcVar4);
        au.lo = 0xd000000000000017;
        return au;
    case 0x51:
        pcVar4 = s_Control_Pictures_005de650;
        break;
    case 0x52:
        pcVar4 = s_Optical_Character_Recognition_005de670;
        au = sk_x_004643cc(pcVar4);
        uVar3 = 0xd;
        au = sk_x_00465028(uVar3);
        return au;
    case 0x53:
        pcVar4 = s_Enclosed_Alphanumerics_005de690;
        au = sk_x_004643f0(pcVar4);
        return au;
    case 0x54:
        au.hi = 0xeb00000000676e69;
        au.lo = 0x776172445f786f42;
        return au;
    case 0x55:
        au.hi = 0xee0073746e656d65;
        au.lo = 0x6c455f6b636f6c42;
        return au;
    case 0x56:
        pcVar4 = s_Geometric_Shapes_005de6d0;
        break;
    case 0x57:
        pcVar4 = s_Miscellaneous_Symbols_005de6f0;
        au = sk_x_004643cc(pcVar4);
        uVar3 = 5;
    case 0x58:
        au.hi = 0xe800000000000000;
        au.lo = 0x73746162676e6944;
        return au;
    case 0x59:
        pcVar4 = s_Miscellaneous_Mathematical_Symbo_005de710;
        au = sk_x_004643cc(pcVar4);
        au.lo = 0xd000000000000024;
        return au;
    case 0x5a:
        pcVar4 = s_Supplemental_Arrows_A_005de740;
        au = sk_x_004643cc(pcVar4);
        uVar3 = 5;
    case 0x5b:
        pcVar4 = s_Braille_Patterns_005de760;
        break;
    case 0x5c:
        pcVar4 = s_Supplemental_Arrows_B_005de780;
        au = sk_x_004643cc(pcVar4);
        uVar3 = 5;
    case 0x5d:
        pcVar4 = s_Miscellaneous_Mathematical_Symbo_005de7a0;
        au = sk_x_004643cc(pcVar4);
        au.lo = 0xd000000000000024;
        return au;
    case 0x5e:
        pcVar4 = s_Supplemental_Mathematical_Operat_005de7d0;
        au = sk_x_004643cc(pcVar4);
        au.lo = 0xd000000000000023;
        return au;
    case 0x5f:
        pcVar4 = s_Miscellaneous_Symbols_and_Arrows_005de800;
        au = sk_x_004643cc(pcVar4);
        au.lo = 0xd000000000000020;
        return au;
    case 0x60:
        uVar3 = 0x74696c6f67616c47;
        au = sk_x_0046414c(uVar3);
        return au;
    case 0x61:
        pcVar4 = s_Latin_Extended_C_005de830;
        break;
    case 0x62:
        au = sk_x_00465b64(0x74706f43,0xe600000000000000);
        return au;
    case 99:
        pcVar4 = s_Georgian_Supplement_005de850;
        au = sk_x_00464408(pcVar4);
        return au;
    case 100:
        uVar3 = 0xe800000000000000;
        uVar2 = 0x616e69666954;
        au.lo = uVar2 | 0x6867000000000000;
        au.hi = uVar3;
        return au;
    case 0x65:
        pcVar4 = s_Ethiopic_Extended_005de870;
        au = sk_x_00464438(pcVar4);
        return au;
    case 0x66:
        pcVar4 = s_Cyrillic_Extended_A_005de890;
        au = sk_x_00464408(pcVar4);
        return au;
    case 0x67:
        pcVar4 = s_Supplemental_Punctuation_005de8b0;
        LAB_00454db4:
        au = sk_x_00464480(pcVar4);
        return au;
    case 0x68:
        pcVar4 = s_CJK_Radicals_Supplement_005de8d0;
        au = sk_x_004643cc(pcVar4);
        au.lo = 0xd000000000000017;
        return au;
    case 0x69:
        uVar3 = 0xef736c6163696461;
        uVar2 = 0x6978676e614b;
        au.lo = uVar2 | 0x525f000000000000;
        au.hi = uVar3;
        return au;
    case 0x6a:
        pcVar4 = s_Ideographic_Description_Characte_005de900;
        au = sk_x_004643cc(pcVar4);
        au.lo = 0xd000000000000022;
        return au;
    case 0x6b:
        pcVar4 = s_CJK_Symbols_and_Punctuation_005de930;
        au = sk_x_004643cc(pcVar4);
        uVar3 = 0xb;
        au = sk_x_00465028(uVar3);
        return au;
    case 0x6c:
        uVar2 = 0x616761726948;
        au.lo = uVar2 | 0x616e000000000000;
        au.hi = 0xe800000000000000;
        return au;
    case 0x6d:
        uVar2 = 0x616b6174614b;
        LAB_00453de0:
        au.lo = uVar2 | 0x616e000000000000;
        au.hi = 0xe800000000000000;
        return au;
    case 0x6e:
        au = sk_x_00464694();
        return au;
    case 0x6f:
        pcVar4 = s_Hangul_Compatibility_Jamo_005de950;
        au = sk_x_004643cc(pcVar4);
        uVar3 = 9;
        au = sk_x_00465028(uVar3);
        return au;
    case 0x70:
        au.hi = 0xe600000000000000;
        au.lo = 0x6e75626e614b;
        return au;
    case 0x71:
        pcVar4 = s_Bopomofo_Extended_005de980;
        au = sk_x_00464438(pcVar4);
        return au;
    case 0x72:
        au = sk_x_004659e0(0x6f7274535f4b4a43,0x73656b);
        return au;
    case 0x73:
        pcVar4 = s_Katakana_Phonetic_Extensions_005de9a0;
        au = sk_x_004643cc(pcVar4);
        au.lo = 0xd00000000000001c;
        return au;
    case 0x74:
        pcVar4 = s_Enclosed_CJK_Letters_and_Months_005de9c0;
        au = sk_x_004643cc(pcVar4);
        au.lo = 0xd00000000000001f;
        return au;
    case 0x75:
        pcVar4 = s_CJK_Compatibility_005de9e0;
        au = sk_x_00464438(pcVar4);
        return au;
    case 0x76:
        pcVar4 = s_CJK_Unified_Ideographs_Extension_005dea00;
        au = sk_x_004643cc(pcVar4);
        au.lo = 0xd000000000000022;
        return au;
    case 0x77:
        pcVar4 = s_Yijing_Hexagram_Symbols_005dea30;
        au = sk_x_004643cc(pcVar4);
        au.lo = 0xd000000000000017;
        return au;
    case 0x78:
        pcVar4 = s_CJK_Unified_Ideographs_005dea50;
        au = sk_x_004643f0(pcVar4);
        return au;
    case 0x79:
        au.hi = 0xec00000073656c62;
        au.lo = 0x616c6c79535f6959;
        return au;
    case 0x7a:
        uVar3 = 0xeb00000000736c61;
        uVar2 = 0x6461525f6959;
        au.lo = uVar2 | 0x6369000000000000;
        au.hi = uVar3;
        return au;
    case 0x7b:
        au = sk_x_00465214();
        return au;
    case 0x7c:
        au = sk_x_00464f04();
        return au;
    case 0x7d:
        pcVar4 = s_Cyrillic_Extended_B_005dea80;
        au = sk_x_00464408(pcVar4);
        return au;
    case 0x7e:
        uVar3 = 0x756d6142;
        LAB_00454274:
        au = sk_x_00465b98(uVar3,0xe500000000000000);
        return au;
    case 0x7f:
        pcVar4 = s_Modifier_Tone_Letters_005deaa0;
        au = sk_x_004643cc(pcVar4);
        uVar3 = 5;
    case 0x80:
        pcVar4 = s_Latin_Extended_D_005deac0;
        break;
    case 0x81:
        au = sk_x_00463d3c();
        return au;
    case 0x82:
        pcVar4 = s_Common_Indic_Number_Forms_005deae0;
        au = sk_x_004643cc(pcVar4);
        uVar3 = 9;
        au = sk_x_00465028(uVar3);
        return au;
    case 0x83:
        au.hi = 0xe800000000000000;
        au.lo = 0x61705f7367616850;
        return au;
    case 0x84:
        au = sk_x_00465a38(0x736172756153,0xea00000000006172);
        return au;
    case 0x85:
        pcVar4 = s_Devanagari_Extended_005deb10;
        au = sk_x_00464408(pcVar4);
        return au;
    case 0x86:
        au = sk_x_0046476c();
        return au;
    case 0x87:
        au = sk_x_00464cbc();
        return au;
    case 0x88:
        pcVar4 = s_Hangul_Jamo_Extended_A_005deb30;
        au = sk_x_004643f0(pcVar4);
        return au;
    case 0x89:
        uVar3 = 0x6176614a;
        LAB_004547c4:
        au = sk_x_00465bf4(uVar3,0xe800000000000000);
        return au;
    case 0x8a:
        pcVar4 = s_Myanmar_Extended_B_005deb50;
        au = sk_x_004643d8(pcVar4);
        return au;
    case 0x8b:
        au = sk_x_00465224();
        return au;
    case 0x8c:
        pcVar4 = s_Myanmar_Extended_A_005deb70;
        au = sk_x_004643d8(pcVar4);
        return au;
    case 0x8d:
        au = sk_x_0046473c();
        return au;
    case 0x8e:
        pcVar4 = s_Meetei_Mayek_Extensions_005deb90;
        au = sk_x_004643cc(pcVar4);
        au.lo = 0xd000000000000017;
        return au;
    case 0x8f:
        pcVar4 = s_Ethiopic_Extended_A_005debb0;
        au = sk_x_00464408(pcVar4);
        return au;
    case 0x90:
        pcVar4 = s_Latin_Extended_E_005debd0;
        break;
    case 0x91:
        pcVar4 = s_Cherokee_Supplement_005debf0;
        au = sk_x_00464408(pcVar4);
        return au;
    case 0x92:
        au = sk_x_00463d5c();
        return au;
    case 0x93:
        pcVar4 = s_Hangul_Syllables_005dec10;
        break;
    case 0x94:
        pcVar4 = s_Hangul_Jamo_Extended_B_005dec30;
        au = sk_x_004643f0(pcVar4);
        return au;
    case 0x95:
        au.hi = 0xef73657461676f72;
        au.lo = 0x7275535f68676948;
        return au;
    case 0x96:
        pcVar4 = s_High_Private_Use_Surrogates_005dec60;
        au = sk_x_004643cc(pcVar4);
        uVar3 = 0xb;
        au = sk_x_00465028(uVar3);
        return au;
    case 0x97:
        au.hi = 0xee0073657461676f;
        au.lo = 0x727275535f776f4c;
        return au;
    case 0x98:
        pcVar4 = s_Private_Use_Area_005dec90;
        break;
    case 0x99:
        pcVar4 = s_CJK_Compatibility_Ideographs_005decb0;
        au = sk_x_004643cc(pcVar4);
        au.lo = 0xd00000000000001c;
        return au;
    case 0x9a:
        pcVar4 = s_Alphabetic_Presentation_Forms_005decd0;
        au = sk_x_004643cc(pcVar4);
        uVar3 = 0xd;
        au = sk_x_00465028(uVar3);
        return au;
    case 0x9b:
        pcVar4 = s_Arabic_Presentation_Forms_A_005decf0;
        au = sk_x_004643cc(pcVar4);
        uVar3 = 0xb;
        au = sk_x_00465028(uVar3);
        return au;
    case 0x9c:
        pcVar4 = s_Variation_Selectors_005ded10;
        au = sk_x_00464408(pcVar4);
        return au;
    case 0x9d:
        au.hi = 0xee00736d726f465f;
        au.lo = 0x6c61636974726556;
        return au;
    case 0x9e:
        pcVar4 = s_Combining_Half_Marks_005ded40;
        au = sk_x_00464468(pcVar4);
        return au;
    case 0x9f:
        pcVar4 = s_CJK_Compatibility_Forms_005ded60;
        au = sk_x_004643cc(pcVar4);
        au.lo = 0xd000000000000017;
        return au;
    case 0xa0:
        pcVar4 = s_Small_Form_Variants_005ded80;
        au = sk_x_00464408(pcVar4);
        return au;
    case 0xa1:
        pcVar4 = s_Arabic_Presentation_Forms_B_005deda0;
        code_r0x00454e90:
        au = sk_x_004643cc(pcVar4);
        uVar3 = 0xb;
        au = sk_x_00465028(uVar3);
        return au;
    case 0xa2:
        pcVar4 = s_Halfwidth_and_Fullwidth_Forms_005dedc0;
        code_r0x00454c5c:
        au = sk_x_004643cc(pcVar4);
        uVar3 = 0xd;
        au = sk_x_00465028(uVar3);
        return au;
    case 0xa3:
        au.hi = 0xe800000000000000;
        au.lo = 0x736c616963657053;
        return au;
    case 0xa4:
        pcVar4 = s_Linear_B_Syllabary_005dedf0;
        au = sk_x_004643d8(pcVar4);
        return au;
    case 0xa5:
        pcVar4 = s_Linear_B_Ideograms_005dee10;
        au = sk_x_004643d8(pcVar4);
        return au;
    case 0xa6:
        au.hi = 0xee00737265626d75;
        au.lo = 0x4e5f6e6165676541;
        return au;
    case 0xa7:
        pcVar4 = s_Ancient_Greek_Numbers_005dee40;
        au = sk_x_004643cc(pcVar4);
        uVar3 = 5;
    case 0xa8:
        uVar3 = 0x5f746e6569636e41;
        au.hi = 0xef736c6f626d7953;
        au.lo = uVar3;
        return au;
    case 0xa9:
        au.hi = 0xed0000637369445f;
        au.lo = 0x736f747369616850;
        return au;
    case 0xaa:
        uVar2 = 0x6963794c;
        au.lo = uVar2 | 0x6e6100000000;
        au.hi = 0xe600000000000000;
        return au;
    case 0xab:
        uVar2 = 0x69726143;
        au.lo = uVar2 | 0x6e6100000000;
        au.hi = 0xe600000000000000;
        return au;
    case 0xac:
        pcVar4 = s_Coptic_Epact_Numbers_005dee80;
        au = sk_x_00464468(pcVar4);
        return au;
    case 0xad:
        uVar3 = 0x6c6174495f646c4f;
        au = sk_x_0046414c(uVar3);
        return au;
    case 0xae:
        uVar3 = 0x68746f47;
        LAB_00454cf4:
        au = sk_x_00465b64(uVar3,0xe600000000000000);
        return au;
    case 0xaf:
        uVar3 = 0x6d7265505f646c4f;
        au = sk_x_0046414c(uVar3);
        return au;
    case 0xb0:
        uVar3 = 0xe800000000000000;
        uVar2 = 0x746972616755;
        LAB_00454e3c:
        au.lo = uVar2 | 0x6369000000000000;
        au.hi = uVar3;
        return au;
    case 0xb1:
        uVar3 = 0x737265505f646c4f;
        au.hi = 0xeb000000006e6169;
        au.lo = uVar3;
        return au;
    case 0xb2:
        au = sk_x_004641d0();
        return au;
    case 0xb3:
        uVar2 = 0x616976616853;
        au.lo = uVar2 | 0x6e000000000000;
        au.hi = 0xe700000000000000;
        return au;
    case 0xb4:
        uVar2 = 0x796e616d734f;
        au.lo = uVar2 | 0x61000000000000;
        au.hi = 0xe700000000000000;
        return au;
    case 0xb5:
        au = sk_x_00464ff0(0x614c5f6369736142,0xe500000000000000);
        return au;
    case 0xb6:
        uVar2 = 0x617361626c45;
        au.lo = uVar2 | 0x6e000000000000;
        au.hi = 0xe700000000000000;
        return au;
    case 0xb7:
        pcVar4 = s_Caucasian_Albanian_005dd990;
        au = sk_x_004643d8(pcVar4);
        return au;
    case 0xb8:
        au = sk_x_0046479c();
        return au;
    case 0xb9:
        au = sk_x_0046470c();
        return au;
    case 0xba:
        pcVar4 = s_Latin_Extended_F_005deea0;
        break;
    case 0xbb:
        pcVar4 = s_Cypriot_Syllabary_005deec0;
        au = sk_x_00464438(pcVar4);
        return au;
    case 0xbc:
        pcVar4 = s_Imperial_Aramaic_005ddb00;
        break;
    case 0xbd:
        au = sk_x_00464b7c(0x614c5f6369736142,0xe900000000000065);
        return au;
    case 0xbe:
        uVar3 = 0x616561746162614e;
        LAB_00454e54:
        au = sk_x_00464ee4(uVar3,0x6e);
        return au;
    case 0xbf:
        uVar2 = 0x72746148;
        LAB_004543a4:
        au.lo = uVar2 | 0x6e6100000000;
        au.hi = 0xe600000000000000;
        return au;
    case 0xc0:
        au = sk_x_00463c78();
        return au;
    case 0xc1:
        uVar3 = 0x6e616964794c;
        au.hi = 0xe600000000000000;
        au.lo = uVar3;
        return au;
    case 0xc2:
        pcVar4 = s_Meroitic_Hieroglyphs_005ddcb0;
        au = sk_x_00464468(pcVar4);
        return au;
    case 0xc3:
        pcVar4 = s_Meroitic_Cursive_005ddc90;
        break;
    case 0xc4:
        au = sk_x_00465a38(0x736f7261684b,0xea00000000006968);
        return au;
    case 0xc5:
        pcVar4 = s_Old_South_Arabian_005dddb0;
        au = sk_x_00464438(pcVar4);
        return au;
    case 0xc6:
        pcVar4 = s_Old_North_Arabian_005ddd70;
        au = sk_x_00464438(pcVar4);
        return au;
    case 199:
        au = sk_x_00463c58();
        return au;
    case 200:
        uVar2 = 0x617473657641;
        au.lo = uVar2 | 0x6e000000000000;
        au.hi = 0xe700000000000000;
        return au;
    case 0xc9:
        pcVar4 = s_Inscriptional_Parthian_005ddb40;
        au = sk_x_004643f0(pcVar4);
        return au;
    case 0xca:
        pcVar4 = s_Inscriptional_Pahlavi_005ddb20;
        au = sk_x_004643cc(pcVar4);
        uVar3 = 5;
    case 0xcb:
        au = sk_x_00463b50();
        return au;
    case 0xcc:
        uVar3 = 0x6b7275545f646c4f;
        LAB_004547fc:
        au = sk_x_0046414c(uVar3);
        return au;
    case 0xcd:
        au = sk_x_00463b98();
        return au;
    case 0xce:
        uVar3 = 0xef6179676e69686f;
        uVar2 = 0x6966696e6148;
        LAB_00453fd8:
        au.lo = uVar2 | 0x525f000000000000;
        au.hi = uVar3;
        return au;
    case 0xcf:
        pcVar4 = s_Rumi_Numeral_Symbols_005deee0;
        au = sk_x_00464468(pcVar4);
        return au;
    case 0xd0:
        au = sk_x_00464c30();
        return au;
    case 0xd1:
        uVar3 = 0x64676f535f646c4f;
        LAB_00454810:
        au.hi = 0xeb000000006e6169;
        au.lo = uVar3;
        return au;
    case 0xd2:
        uVar2 = 0x616964676f53;
        au.lo = uVar2 | 0x6e000000000000;
        au.hi = 0xe700000000000000;
        return au;
    case 0xd3:
        uVar3 = 0xea00000000007275;
        uVar2 = 0x79555f646c4f;
        LAB_00453d44:
        au.lo = uVar2 | 0x6867000000000000;
        au.hi = uVar3;
        return au;
    case 0xd4:
        au = sk_x_00463c38();
        return au;
    case 0xd5:
        uVar3 = 0x6d796c45;
        LAB_00454068:
        au = sk_x_00464688(uVar3,0xe700000000000000);
        return au;
    case 0xd6:
        au = sk_x_00464c1c();
        return au;
    case 0xd7:
        au = sk_x_00464c6c();
        return au;
    case 0xd8:
        au = sk_x_00463c18();
        return au;
    case 0xd9:
        au = sk_x_00464c44();
        return au;
    case 0xda:
        au = sk_x_00464784();
        return au;
    case 0xdb:
        uVar2 = 0x72616853;
        LAB_0045495c:
        uVar2 = uVar2 | 0x646100000000;
        au.lo = uVar2 | 0x61000000000000;
        au.hi = 0xe700000000000000;
        return au;
    case 0xdc:
        pcVar4 = s_Sinhala_Archaic_Numbers_005def00;
        code_r0x00454b68:
        au = sk_x_004643cc(pcVar4);
        au.lo = 0xd000000000000017;
        return au;
    case 0xdd:
        au = sk_x_00464cd0();
        return au;
    case 0xde:
        uVar2 = 0x6e61746c754d;
        LAB_00454464:
        au.lo = uVar2 | 0x69000000000000;
        au.hi = 0xe700000000000000;
        return au;
    case 0xdf:
        au.hi = 0xe900000000000069;
        au.lo = 0x646177616475684b;
        return au;
    case 0xe0:
        uVar2 = 0x68746e617247;
        au.lo = uVar2 | 0x61000000000000;
        au.hi = 0xe700000000000000;
        return au;
    case 0xe1:
        au = sk_x_00465204();
        return au;
    case 0xe2:
        uVar2 = 0x747568726954;
        LAB_00454c30:
        au.lo = uVar2 | 0x61000000000000;
        au.hi = 0xe700000000000000;
        return au;
    case 0xe3:
        au = sk_x_004641a0();
        return au;
    case 0xe4:
        au = sk_x_004651f4();
        return au;
    case 0xe5:
        pcVar4 = s_Mongolian_Supplement_005def20;
        au = sk_x_00464468(pcVar4);
        return au;
    case 0xe6:
        au = sk_x_00464fa4(0x614c5f6369736142,0xe500000000000000);
        return au;
    case 0xe7:
        au = sk_x_004651e4();
        return au;
    case 0xe8:
        uVar2 = 0x72676f44;
        LAB_00453f04:
        au.lo = uVar2 | 0x6100000000;
        au.hi = 0xe500000000000000;
        return au;
    case 0xe9:
        au = sk_x_00463b08();
        return au;
    case 0xea:
        au = sk_x_00463d9c();
        return au;
    case 0xeb:
        au = sk_x_004659e0(0x67616e69646e614e,&DAT_00697261);
        return au;
    case 0xec:
        pcVar4 = s_Zanabazar_Square_005ddfa0;
        break;
    case 0xed:
        uVar2 = 0x626d6f796f53;
        LAB_00453d74:
        au.lo = uVar2 | 0x6f000000000000;
        au.hi = 0xe700000000000000;
        return au;
    case 0xee:
        au = sk_x_004643cc(s_Unified_Canadian_Aboriginal_Syll_005def40);
        au.lo = 0xd000000000000030;
        return au;
    case 0xef:
        au = sk_x_00463d1c();
        return au;
    case 0xf0:
        au.hi = 0xe900000000000069;
        au.lo = 0x6b75736b69616842;
        return au;
    case 0xf1:
        uVar2 = 0x65686372614d;
        LAB_00454e0c:
        au.lo = uVar2 | 0x6e000000000000;
        au.hi = 0xe700000000000000;
        return au;
    case 0xf2:
        uVar2 = 0x5f6d61726173614d;
        uVar3 = 0x69646e6f47;
        au = sk_x_000b43f4(uVar2,uVar3);
        return au;
    case 0xf3:
        uVar2 = 0x5f616c616a6e7547;
        LAB_00454940:
        uVar3 = 0x69646e6f47;
        au = sk_x_000b43f4(uVar2,uVar3);
        return au;
    case 0xf4:
        uVar3 = 0x6173616b614d;
        LAB_00454884:
        au = sk_x_00465ab8(uVar3,0xe700000000000000);
        return au;
    case 0xf5:
        uVar2 = 0x7573694c;
        au = sk_x_00465be0(uVar2 | 0x7075535f00000000);
        return au;
    case 0xf6:
        pcVar4 = s_Tamil_Supplement_005def90;
        break;
    case 0xf7:
        au = sk_x_00464b54(0x614c5f6369736142,0xe90000000000006d);
        return au;
    case 0xf8:
        pcVar4 = s_Cuneiform_Numbers_and_Punctuatio_005defb0;
        au = sk_x_004643cc(pcVar4);
        au.lo = 0xd000000000000021;
        return au;
    case 0xf9:
        au = sk_x_00464480(s_Early_Dynastic_Cuneiform_005defe0);
        return au;
    case 0xfa:
        au = sk_x_00463cfc();
        return au;
    case 0xfb:
        pcVar4 = s_Egyptian_Hieroglyphs_005dda30;
        au = sk_x_00464468(pcVar4);
        return au;
    case 0xfc:
        pcVar4 = s_Egyptian_Hieroglyph_Format_Contr_005df000;
        au = sk_x_004643cc(pcVar4);
        au.lo = 0xd000000000000023;
        return au;
    case 0xfd:
        pcVar4 = s_Anatolian_Hieroglyphs_005dd8e0;
        au = sk_x_004643cc(pcVar4);
        uVar3 = 5;
    case 0xfe:
        pcVar4 = s_Bamum_Supplement_005df030;
        break;
    case 0xff:
        au = sk_x_004659e8(0x6f724d);
        return au;
    case 0x100:
        uVar3 = 0x6173676e6154;
        au.hi = 0xe600000000000000;
        au.lo = uVar3;
        return au;
    case 0x101:
        au = sk_x_00464b40(0x614c5f6369736142,0xe900000000000068);
        return au;
    case 0x102:
        au = sk_x_00463ad4();
        return au;
    case 0x103:
        au = sk_x_00464b90(0x614c5f6369736142,0xeb000000006e6972);
        return au;
    case 0x104:
        uVar3 = 0x6f61694d;
        au.hi = 0xe400000000000000;
        au.lo = uVar3;
        return au;
    case 0x105:
        pcVar4 = s_Ideographic_Symbols_and_Punctuat_005df050;
        code_r0x00454d04:
        au = sk_x_004643cc(pcVar4);
        au.lo = 0xd000000000000023;
        return au;
    case 0x106:
        uVar3 = 0x7475676e6154;
        au.hi = 0xe600000000000000;
        au.lo = uVar3;
        return au;
    case 0x107:
        pcVar4 = s_Tangut_Components_005df080;
        au = sk_x_00464438(pcVar4);
        return au;
    case 0x108:
        pcVar4 = s_Khitan_Small_Script_005ddbb0;
        au = sk_x_00464408(pcVar4);
        return au;
    case 0x109:
        pcVar4 = s_Tangut_Supplement_005df0a0;
        LAB_00454c40:
        au = sk_x_00464438(pcVar4);
        return au;
    case 0x10a:
        uVar3 = 0xef425f6465646e65;
        au.hi = uVar3;
        au.lo = 0x7478455f616e614b;
        return au;
    case 0x10b:
        uVar2 = 0x616e614b;
        LAB_0045408c:
        au = sk_x_00465be0(uVar2 | 0x7075535f00000000);
        return au;
    case 0x10c:
        uVar3 = 0xef415f6465646e65;
        LAB_004548b8:
        au.hi = uVar3;
        au.lo = 0x7478455f616e614b;
        return au;
    case 0x10d:
        pcVar4 = s_Small_Kana_Extension_005df0f0;
        LAB_00454b04:
        au = sk_x_00464468(pcVar4);
        return au;
    case 0x10e:
        uVar3 = 0x756873754e;
        au.hi = 0xe500000000000000;
        au.lo = uVar3;
        return au;
    case 0x10f:
        uVar1 = 0x6e61796f6c707544;
        uVar3 = 0xe800000000000000;
    case 0x110:
        pcVar4 = s_Shorthand_Format_Controls_005df110;
        au = sk_x_004643cc(pcVar4);
        uVar3 = 9;
        au = sk_x_00465028(uVar3);
        return au;
    case 0x111:
        pcVar4 = s_Znamenny_Musical_Notation_005df130;
        au = sk_x_004643cc(pcVar4);
        uVar3 = 9;
        au = sk_x_00465028(uVar3);
        return au;
    case 0x112:
        pcVar4 = s_Byzantine_Musical_Symbols_005df150;
        au = sk_x_004643cc(pcVar4);
        uVar3 = 9;
        au = sk_x_00465028(uVar3);
        return au;
    case 0x113:
        uVar3 = 0x5f6c61636973754d;
        LAB_00454620:
        au.hi = 0xef736c6f626d7953;
        au.lo = uVar3;
        return au;
    case 0x114:
        pcVar4 = s_Ancient_Greek_Musical_Notation_005df180;
        au = sk_x_004643cc(pcVar4);
        au.lo = 0xd00000000000001e;
        return au;
    case 0x115:
        au.hi = 0xee00736c6172656d;
        au.lo = 0x754e5f6e6179614d;
        return au;
    case 0x116:
        pcVar4 = s_Tai_Xuan_Jing_Symbols_005df1b0;
        au = sk_x_004643cc(pcVar4);
        uVar3 = 5;
    case 0x117:
        pcVar4 = s_Counting_Rod_Numerals_005df1d0;
        au = sk_x_004643cc(pcVar4);
        uVar3 = 5;
    case 0x118:
        pcVar4 = s_Mathematical_Alphanumeric_Symbol_005df1f0;
        code_r0x00454828:
        au = sk_x_004643cc(pcVar4);
        au.lo = 0xd000000000000021;
        return au;
    case 0x119:
        pcVar4 = s_Sutton_SignWriting_005df220;
        au = sk_x_004643d8(pcVar4);
        return au;
    case 0x11a:
        au = sk_x_004643cc(s_Latin_Extended_G_005df240);
        au.lo = 0xd000000000000010;
        return au;
    case 0x11b:
        pcVar4 = s_Glagolitic_Supplement_005df260;
        au = sk_x_004643cc(pcVar4);
        uVar3 = 5;
    case 0x11c:
        pcVar4 = s_Nyiakeng_Puachue_Hmong_005ddd30;
        LAB_00454d34:
        au = sk_x_004643f0(pcVar4);
        return au;
    case 0x11d:
        uVar3 = 0x6f746f54;
        au.hi = 0xe400000000000000;
        au.lo = uVar3;
        return au;
    case 0x11e:
        uVar3 = 0x6f68636e6157;
        LAB_004542d8:
        au.hi = 0xe600000000000000;
        au.lo = uVar3;
        return au;
    case 0x11f:
        pcVar4 = s_Ethiopic_Extended_B_005df280;
        au = sk_x_00464408(pcVar4);
        return au;
    case 0x120:
        au = sk_x_00463b2c();
        return au;
    case 0x121:
        uVar3 = 0x6d616c6441;
        LAB_00454478:
        au.hi = 0xe500000000000000;
        au.lo = uVar3;
        return au;
    case 0x122:
        pcVar4 = s_Indic_Siyaq_Numbers_005df2a0;
        au = sk_x_00464408(pcVar4);
        return au;
    case 0x123:
        pcVar4 = s_Ottoman_Siyaq_Numbers_005df2c0;
        au = sk_x_004643cc(pcVar4);
        uVar3 = 5;
    case 0x124:
        pcVar4 = s_Arabic_Mathematical_Alphabetic_S_005df2e0;
        code_r0x0045472c:
        au = sk_x_004643cc(pcVar4);
        au.lo = 0xd000000000000026;
        return au;
    case 0x125:
        sk_x_004663e0();
        uVar2 = 0x6e6f6a68614d;
        uVar3 = au.hi;
        au.lo = uVar2 | 0x5f67000000000000;
        au.hi = uVar3;
        return au;
    case 0x126:
        au.hi = 0xec00000073656c69;
        au.lo = 0x545f6f6e696d6f44;
        return au;
    case 0x127:
        sk_x_004663e0();
        uVar2 = 0x6e6979616c50;
        uVar3 = au.hi;
        LAB_00454368:
        au.lo = uVar2 | 0x5f67000000000000;
        au.hi = uVar3;
        return au;
    case 0x128:
        pcVar4 = s_Enclosed_Alphanumeric_Supplement_005df330;
        au = sk_x_004643cc(pcVar4);
        au.lo = 0xd000000000000020;
        return au;
    case 0x129:
        pcVar4 = s_Enclosed_Ideographic_Supplement_005df360;
        code_r0x00454700:
        au = sk_x_004643cc(pcVar4);
        au.lo = 0xd00000000000001f;
        return au;
    case 0x12a:
        au = sk_x_00464420(s_Miscellaneous_Symbols_and_Pictog_005df380);
        return au;
    case 299:
        au.hi = 0xe900000000000073;
        au.lo = 0x6e6f6369746f6d45;
        return au;
    case 300:
        pcVar4 = s_Ornamental_Dingbats_005df3b0;
        LAB_00454e7c:
        au = sk_x_00464408(pcVar4);
        return au;
    case 0x12d:
        pcVar4 = s_Transport_and_Map_Symbols_005df3d0;
        au = sk_x_004643cc(pcVar4);
        uVar3 = 9;
        au = sk_x_00465028(uVar3);
        return au;
    case 0x12e:
        pcVar4 = s_Alchemical_Symbols_005df3f0;
        LAB_00454d58:
        au = sk_x_004643d8(pcVar4);
        return au;
    case 0x12f:
        pcVar4 = s_Geometric_Shapes_Extended_005df410;
        code_r0x004548d8:
        au = sk_x_004643cc(pcVar4);
        uVar3 = 9;
        au = sk_x_00465028(uVar3);
        return au;
    case 0x130:
        pcVar4 = s_Supplemental_Arrows_C_005df430;
        code_r0x00454bd0:
        au = sk_x_004643cc(pcVar4);
        uVar3 = 5;
        LAB_00454ea4:
        au = sk_x_00465028(uVar3);
        return au;
    case 0x131:
        pcVar4 = s_Supplemental_Symbols_and_Pictogr_005df450;
        code_r0x004545ac:
        au = sk_x_004643cc(pcVar4);
        au.lo = 0xd000000000000024;
        return au;
    case 0x132:
        uVar2 = 0x5f7373656843;
        LAB_004541a0:
        uVar2 = uVar2 | 0x7953000000000000;
        uVar3 = 0x736c6f626d;
        LAB_0045494c:
        au = sk_x_000b43f4(uVar2,uVar3);
        return au;
    case 0x133:
        pcVar4 = s_Symbols_and_Pictographs_Extended_005df490;
        au = sk_x_004643cc(pcVar4);
        au.lo = 0xd000000000000022;
        return au;
    case 0x134:
        pcVar4 = s_Symbols_for_Legacy_Computing_005df4c0;
        code_r0x004542ec:
        au = sk_x_004643cc(pcVar4);
        au.lo = 0xd00000000000001c;
        return au;
    case 0x135:
        pcVar4 = s_CJK_Unified_Ideographs_Extension_005df4e0;
        au = sk_x_004643cc(pcVar4);
        au.lo = 0xd000000000000022;
        return au;
    case 0x136:
        pcVar4 = s_CJK_Unified_Ideographs_Extension_005df510;
        au = sk_x_004643cc(pcVar4);
        au.lo = 0xd000000000000022;
        return au;
    case 0x137:
        pcVar4 = s_CJK_Unified_Ideographs_Extension_005df540;
        au = sk_x_004643cc(pcVar4);
        au.lo = 0xd000000000000022;
        return au;
    case 0x138:
        pcVar4 = s_CJK_Unified_Ideographs_Extension_005df570;
        au = sk_x_004643cc(pcVar4);
        au.lo = 0xd000000000000022;
        return au;
    case 0x139:
        pcVar4 = s_CJK_Unified_Ideographs_Extension_005df5a0;
        au = sk_x_004643cc(pcVar4);
        au.lo = 0xd000000000000022;
        return au;
    case 0x13a:
        au = sk_x_00464450(s_CJK_Compatibility_Ideographs_Sup_005df5d0,0x614c5f6369736142,
        0xeb000000006e6974);
        return au;
    case 0x13b:
        pcVar4 = s_CJK_Unified_Ideographs_Extension_005df600;
        code_r0x00454a14:
        au = sk_x_004643cc(pcVar4);
        au.lo = 0xd000000000000022;
        return au;
    case 0x13c:
        uVar3 = 0x73676154;
        LAB_004542c4:
        au.hi = 0xe400000000000000;
        au.lo = uVar3;
        return au;
    case 0x13d:
        pcVar4 = s_Variation_Selectors_Supplement_005df630;
        code_r0x004543e8:
        au = sk_x_004643cc(pcVar4);
        au.lo = 0xd00000000000001e;
        return au;
    case 0x13e:
        pcVar4 = s_Supplementary_Private_Use_Area_A_005df650;
        au = sk_x_004643cc(pcVar4);
        au.lo = 0xd000000000000020;
        return au;
    case 0x13f:
        pcVar4 = s_Supplementary_Private_Use_Area_B_005df680;
        code_r0x00454574:
        au = sk_x_004643cc(pcVar4);
        au.lo = 0xd000000000000020;
        return au;
    case 0x140:
        uVar1 = 0x6b636f6c425f6f4e;
        LAB_00454448:
        uVar3 = 0xe800000000000000;
        switchD_004539e0_caseD_0:
        au.hi = uVar3;
        au.lo = uVar1;
        return au;
    }
    au = sk_x_004643cc((word_t)pcVar4, 0xd000000000000010);
    return au;
}
/* FUN_004553e4 @ 0x004553e4   (est. sk_script_name_store2)
 * Ghidra: void FUN_004553e4(undefined1 (*param_1)[16])
 * Stores the Script name (0x45399c) for the enum in x20 into the 16-byte
 * out-param.
 * Confidence: medium */
static void sk_script_name_store2_004553e4(cl4_pair_t *param_1, word_t self)
{
    *param_1 = sk_script_name_0045399c(self);
}

/* FUN_00455438 @ 0x00455438   (est. sk_collection_element_types_check)
 * Ghidra: long FUN_00455438(void)
 * Builds and validates the "collection of element types" diagnostic. Calls the
 * element-type provider (00350980, 00027754/00027788), runs the build closure
 * (004662b8 + 00002534 + 00310c44 + 004594f4 through the 004662b8 runtime),
 * and if the produced element count is non-zero returns it; otherwise raises
 * the "The collection of element types..." precondition-failure fatal
 * (00002874 + 003593c0 + 00002818 -> noreturn 001afa84).
 * Confidence: low (register/closure-fragment heavy)
 * Notes: s_The_collection_of_element_types_d_005df6e0. */
static long sk_collection_element_types_check_00455438(void)
{
    word_t uVar1, uVar2, uVar3;
    word_t local_58[2], local_48;
    word_t in_x3, in_x4;
    long unaff_x21;

    uVar1 = sk_x_00350980();
    uVar2 = sk_x_00027754(in_x4);
    uVar3 = sk_x_00027788();
    sk_x_00084174(uVar3);
    local_48 = 0;   /* (*extraout_x8)() - closure result */
    if (unaff_x21 != 0) {
        local_48 |= 0x10000;
    }
    uVar2 = sk_x_00027754(uVar2);
    sk_x_004662b8();
    uVar3 = sk_x_00002534();
    {
        /* 00310c44 yields a closure; invoke it with the element-type pieces. */
        word_t (*fn)(word_t, word_t, word_t, word_t, word_t, word_t) =
            (word_t (*)(word_t, word_t, word_t, word_t, word_t, word_t))sk_x_00310c44();
        fn(0, 0, 0, uVar3, in_x3, uVar2);
    }
    if (local_58[0] != 0) {
        sk_x_003509c8(in_x3);
        return local_58[0];
    }
    sk_x_00002874((word_t)s_The_collection_of_element_types_d_005df6e0);
    sk_x_003593c0();
    sk_x_00002818();
    sk_x_001afa84();   /* does not return */
    return 0;
}

/* FUN_00455574 @ 0x00455574   (est. sk_str_from_substring)
 * Ghidra: void FUN_00455574(undefined1 (*param_1)[16], ...)
 * Builds a 16-byte String from a substring view (param_5/param_6 slice into a
 * buffer whose words are in param_2/param_3). Handles the shared/owned small-
 * string and native-buffer cases; on the overflow/native path falls to the
 * 004662b8 builder with the 00460ddc element descriptor.
 * Confidence: low (string-layout fragment heavy) */
static void sk_str_from_substring_00455574(cl4_pair_t *param_1, word_t param_2,
                                           word_t param_3, word_t param_4,
                                           word_t param_5, word_t *param_6)
{
    cl4_pair_t au;
    word_t uVar1;
    if (param_5 == 0) {
        uVar1 = *param_6;
    } else {
        /* DAT_00658cf0 runtime dispatch */
        if ((param_5 >> 0x3c & 1) != 0) goto build;
        if ((param_5 >> 0x3d & 1) == 0) {
            if ((param_4 >> 0x3c & 1) == 0) goto build;
            uVar1 = *param_6;
        } else {
            uVar1 = *param_6;
        }
    }
    au = sk_x_00371950(0, uVar1);
    *param_1 = au;
    return;
build:
    sk_x_004662b8();
    sk_x_00002534();
    sk_x_00351e3c((word_t)param_1, (word_t)sk_x_00460ddc, (word_t)au.lo);
    sk_x_002a4468();
}

/* FUN_0045567c @ 0x0045567c   (est. sk_special_string_init)
 * Ghidra: void FUN_0045567c(undefined8 param_1,...)
 * Initializes a special String: builds the element-type collection (0046647c +
 * 00027754 + 000262fc) and a native-buffer string (00371950), then forwards
 * through 00455778. Ends with a virtual dispatch on the unaff_x19 witness.
 * Confidence: low */
static void sk_special_string_init_0045567c(word_t param_1, word_t param_2, word_t param_3)
{
    cl4_pair_t au;
    long lVar1;
    word_t uVar2;

    sk_x_003504d0();
    sk_x_0046647c();
    sk_x_00027754(param_3);
    lVar1 = sk_x_000262fc((word_t)sk_str_elem_type_00455a68, 0);
    uVar2 = sk_x_00371950(0, *(word_t *)(lVar1 + 0x10)).lo;
    sk_x_0036b118(lVar1);
    au = sk_x_0007c1c4(0);
    sk_str_guts_init_full_00455778(au.lo, au.hi, uVar2, param_3);
    /* virtual dispatch on unaff_x19 witness */
    return;
}

/* FUN_00455778 @ 0x00455778   (est. sk_str_guts_init_full)
 * Ghidra: void FUN_00455778(undefined8 param_1,...)
 * Full _StringGuts initializer: takes the substring pieces (param_3/param_4),
 * builds the native buffer via 0008e518/00350530/00377824, iterates the
 * element runs (00100efc loop) invoking 00455990 per element, then finalizes
 * (003514e8/001a29a0) and returns.
 * Confidence: low (heavy register/closure flow) */
static void sk_str_guts_init_full_00455778(word_t param_1, word_t param_2,
                                           word_t param_3, word_t param_4)
{
    cl4_pair_t au6, au7;
    word_t uVar1, uVar2, uVar4;

    au6 = sk_x_0008e518();
    uVar4 = au6.hi;
    sk_x_0007c028();
    sk_x_000aa4ec();
    sk_x_00027754(param_4);
    uVar1 = sk_x_00027754();
    au7 = sk_x_00350530();
    uVar2 = sk_x_00377824(au7.lo, au7.hi, uVar4);
    sk_x_000a6f88();
    sk_x_0007c1a4();
    sk_x_003509c8(param_3);
    sk_x_002b8444(0, param_3);
    /* element loop: while runs remain, build + 00455990 */
    while (1) {
        if (0) break;
        sk_str_elem_append_00455990(0, 0, 0);
        sk_x_000026e8(0);
    }
    sk_x_00077024();
    sk_x_003514e8(0);
    sk_x_001a29a0();
    sk_x_003514e8();
    sk_x_00359208();
    sk_x_0008e500(0);
}

/* FUN_00455990 @ 0x00455990   (est. sk_str_elem_append)
 * Ghidra: void FUN_00455990(undefined8 param_1,...)
 * Appends one string element run to the growing buffer: builds the run via
 * 00450848/003507bc/00350618 and writes the result into *unaff_x20, adding
 * the run length from the runtime.
 * Confidence: low */
static void sk_str_elem_append_00455990(word_t param_1, word_t param_2, word_t param_3)
{
    cl4_pair_t au;
    long lVar1, lVar2;
    long *unaff_x20;

    sk_x_00084220();
    sk_x_0035098c();
    sk_x_0007c028();
    lVar2 = 0;   /* *(extraout_x8 + 0x40) */
    au = sk_x_00450848(0, 0);
    lVar1 = au.lo;
    *unaff_x20 = lVar1;
    au = sk_x_003507bc();
    sk_x_003509c8(0);
    au = sk_x_00350618(0);
    *unaff_x20 = *unaff_x20 + lVar2;
    sk_x_00084234(0);
}

/* FUN_00455a68 @ 0x00455a68   (est. sk_str_elem_type)
 * Ghidra: void FUN_00455a68(undefined8 *param_1, long param_2)
 * Reads the element type from a buffer header (param_2+0x18) and builds the
 * owning collection (00464000 + 003625e4).
 * Confidence: low */
static void sk_str_elem_type_00455a68(word_t *param_1, long param_2)
{
    sk_x_0006a4c0(param_2, *(word_t *)(param_2 + 0x18));
    sk_x_00464000();
    *param_1 = sk_x_003625e4();
}

/* FUN_00455abc @ 0x00455abc   (est. sk_utf8_emit_byte)
 * Ghidra: void FUN_00455abc(undefined8 param_1)
 * Emits a single UTF-8 byte (0 + param_1) into the output via 00310d68.
 * Confidence: high */
static void sk_utf8_emit_byte_00455abc(word_t param_1)
{
    sk_x_00310d68(0, param_1);
}

/* FUN_00455ac8 @ 0x00455ac8   (est. sk_utf8_encode)
 * Ghidra: void FUN_00455ac8(undefined8 param_1, ulong param_2, undefined8 param_3)
 * UTF-8 encodes a scalar value (param_3) into the output, handling 1-4 byte
 * sequences via the 004665e8 emitter / 00310d68; the 4-byte tail splits into
 * two 3-byte halves and a final byte.
 * Confidence: medium */
static void sk_utf8_encode_00455ac8(word_t param_1, word_t param_2, word_t param_3)
{
    cl4_pair_t a, b;
    word_t cur = param_3;
    while (param_2 >= 4) {
        b.hi = a.hi;
        b.lo = param_1;
        cur = a.lo;
        if (param_2 < 5) {
            switch (param_2) {
            case 4: a = sk_x_004665e8(); cur = a.lo; /* fallthrough */
            case 3: a = sk_x_004665e8(b.lo, b.hi, cur); cur = a.lo; /* fallthrough */
            case 2: cur = sk_x_004665e8(b.lo, b.hi, cur).lo; /* fallthrough */
            case 1: sk_x_00310d68(0, cur); return;
            default: return;
            }
        }
        cur = sk_x_004665e8().lo;
        cur = sk_x_00310d68(0xff, cur).lo;
        cur = sk_x_00310d68(0xff, cur).lo;
        a = sk_x_00310d68(0, cur);
        param_1 = a.lo;
        param_2 -= 4;
    }
    /* param_2 < 4 tail: fall through the <5 switch */
    switch (param_2) {
    case 4: a = sk_x_004665e8(); cur = a.lo; /* fallthrough */
    case 3: a = sk_x_004665e8(a.lo, a.hi, cur); cur = a.lo; /* fallthrough */
    case 2: cur = sk_x_004665e8(a.lo, a.hi, cur).lo; /* fallthrough */
    case 1: sk_x_00310d68(0, cur); return;
    default: return;
    }
}

/* FUN_00455b88 @ 0x00455b88   (est. sk_str_run_iter)
 * Ghidra: void FUN_00455b88(void)
 * Iterates the string element runs, validating each against the count and
 * emitting them; traps (SoftwareBreakpoint) on count overflow.
 * Confidence: low (register/closure-fragment heavy) */
static void sk_str_run_iter_00455b88(void)
{
    cl4_pair_t au9;
    word_t uVar2, uVar3, uVar4;
    long lVar7, lVar8;
    long *unaff_x20;

    au9 = sk_x_0008e518();
    lVar7 = au9.lo;
    sk_x_00027754(0);
    sk_x_00352840(0);
    uVar2 = sk_x_0031b760();
    sk_x_003509c8(uVar2);
    sk_x_0007c1a4();
    sk_x_0034b05c();
    sk_x_00352840(0);
    uVar3 = sk_x_0031b778();
    sk_x_000a6f88();
    sk_x_0007c1a4();
    uVar4 = 0;
    sk_x_00351db4();
    /* element run loop with count-overflow traps */
    if (uVar4 == 0) {
        uVar2 = 0;
    } else {
        sk_x_00350a04();
        sk_x_00200b38();
        sk_x_00200bd0(0, uVar2);
        lVar8 = 0;
        while (0) {   /* 00200bf4 element scan */
            lVar8 += 0;
        }
        sk_x_00350560(0);
        sk_x_0008e500(0);
    }
}

/* FUN_00455d8c @ 0x00455d8c   (est. sk_buf_init_682e08)
 * Ghidra: void FUN_00455d8c(void)
 * Initializes a buffer at (x20+0x20) with element base *(x20+0x10) and the
 * 0x682e08 element-size tag via 0035bc70.
 * Confidence: high */
static void sk_buf_init_682e08_00455d8c(word_t self)
{
    sk_x_0035bc70(self + 0x20, *(word_t *)(self + 0x10), 0x682e08);
}

/* FUN_00455db8 @ 0x00455db8   (est. sk_buf_init_6728f0)
 * Ghidra: void FUN_00455db8(void)
 * Same buffer-init helper with the 0x6728f0 element-size tag.
 * Confidence: high */
static void sk_buf_init_6728f0_00455db8(word_t self)
{
    sk_x_0035bc70(self + 0x20, *(word_t *)(self + 0x10), 0x6728f0);
}

/* FUN_00455de4 @ 0x00455de4   (est. sk_arr_reserve_de4)
 * Ghidra: undefined * FUN_00455de4(long param_1, long param_2)
 * Reserve-capacity helper (8-byte stride): ensures param_2 >= param_1, and if
 * non-zero allocates a buffer (0036a940, 8-byte elements + 0x20 header)
 * returning the base with the count at +0x10 and the capacity (rounded to
 * even) at +0x18; empty requests return the 00657778 empty sentinel.
 * Confidence: high */
static long sk_arr_reserve_00455de4(long param_1, long param_2)
{
    if (param_2 <= param_1) param_2 = param_1;
    if (param_2 == 0) return 0x00657778;
    {
        word_t meta = sk_x_00002534(0x6579c8, 0x005a19a0);
        long buf = sk_x_0036a940(meta, param_2 * 8 + 0x20, 7);
        long cap = sk_x_000126e8();
        *(long *)(buf + 0x10) = param_1;
        *(long *)(buf + 0x18) = ((cap - 0x20) / 8) << 1;
        return buf;
    }
}

/* FUN_00455e60 @ 0x00455e60   (est. sk_arr_reserve_e60)
 * Reserve-capacity helper (0x178-byte stride).
 * Confidence: high */
static long sk_arr_reserve_00455e60(long param_1, long param_2)
{
    if (param_2 <= param_1) param_2 = param_1;
    if (param_2 == 0) return 0x00657778;
    {
        word_t meta = sk_x_00002534(0x657b20, 0x005a35c8);
        long buf = sk_x_0036a940(meta, param_2 * 0x178 + 0x20, 7);
        long cap = sk_x_000126e8();
        *(long *)(buf + 0x10) = param_1;
        *(long *)(buf + 0x18) = ((cap - 0x20) / 0x178) << 1;
        return buf;
    }
}

/* FUN_00455ee4 @ 0x00455ee4   (est. sk_arr_reserve_ee4)
 * Reserve-capacity helper (4-byte stride).
 * Confidence: high */
static long sk_arr_reserve_00455ee4(long param_1, long param_2)
{
    if (param_2 <= param_1) param_2 = param_1;
    if (param_2 == 0) return 0x00657778;
    {
        word_t meta = sk_x_00002534(0x006575f0, 0x005a19e0);
        long buf = sk_x_0036a940(meta, param_2 * 4 + 0x20, 7);
        long cap = sk_x_000126e8();
        *(long *)(buf + 0x10) = param_1;
        *(long *)(buf + 0x18) = ((cap - 0x20) / 4) << 1;
        return buf;
    }
}

/* FUN_00455f60 @ 0x00455f60   (est. sk_arr_reserve_f60)
 * Reserve-capacity helper (0x38-byte stride).
 * Confidence: high */
static long sk_arr_reserve_00455f60(long param_1, long param_2)
{
    if (param_2 <= param_1) param_2 = param_1;
    if (param_2 == 0) return 0x00657778;
    {
        word_t meta = sk_x_00002534(0x657ba8, 0x005a3690);
        long buf = sk_x_0036a940(meta, param_2 * 0x38 + 0x20, 7);
        long cap = sk_x_000126e8();
        *(long *)(buf + 0x10) = param_1;
        *(long *)(buf + 0x18) = ((cap - 0x20) / 0x38) << 1;
        return buf;
    }
}

/* FUN_00455fe4 @ 0x00455fe4   (est. sk_arr_reserve_fe4)
 * Reserve-capacity helper (0x50-byte stride).
 * Confidence: high */
static long sk_arr_reserve_00455fe4(long param_1, long param_2)
{
    if (param_2 <= param_1) param_2 = param_1;
    if (param_2 == 0) return 0x00657778;
    {
        word_t meta = sk_x_00002534(0x657b98, 0x005a3670);
        long buf = sk_x_0036a940(meta, param_2 * 0x50 + 0x20, 7);
        long cap = sk_x_000126e8();
        *(long *)(buf + 0x10) = param_1;
        *(long *)(buf + 0x18) = ((cap - 0x20) / 0x50) << 1;
        return buf;
    }
}

/* FUN_00456068 @ 0x00456068   (est. sk_arr_reserve_068)
 * Reserve-capacity helper (0x30-byte stride).
 * Confidence: high */
static long sk_arr_reserve_00456068(long param_1, long param_2)
{
    if (param_2 <= param_1) param_2 = param_1;
    if (param_2 == 0) return 0x00657778;
    {
        word_t meta = sk_x_00002534(0x657b90, 0x005a3668);
        long buf = sk_x_0036a940(meta, param_2 * 0x30 + 0x20, 7);
        long cap = sk_x_000126e8();
        *(long *)(buf + 0x10) = param_1;
        *(long *)(buf + 0x18) = ((cap - 0x20) / 0x30) << 1;
        return buf;
    }
}

/* FUN_004560ec @ 0x004560ec   (est. sk_arr_reserve_0ec)
 * Reserve-capacity helper (0x10-byte stride). Empty -> 0.
 * Confidence: high */
static long sk_arr_reserve_004560ec(long param_1, long param_2)
{
    if (param_2 <= param_1) param_2 = param_1;
    if (param_2 == 0) { sk_x_000776cc(); return 0; }
    sk_x_00355968();
    {
        word_t meta = sk_x_00002534();
        long buf = sk_x_0036a940(meta, param_2 * 0x10 + 0x20, 7);
        long cap = sk_x_000126e8();
        *(long *)(buf + 0x10) = param_1;
        *(long *)(buf + 0x18) = ((cap - 0x20) / 0x10) << 1;
        return buf;
    }
}

/* FUN_00456158 @ 0x00456158   (est. sk_arr_reserve_158)
 * Reserve-capacity helper (0x18-byte stride). Empty -> 0.
 * Confidence: high */
static long sk_arr_reserve_00456158(long param_1, long param_2)
{
    if (param_2 <= param_1) param_2 = param_1;
    if (param_2 == 0) { sk_x_000776cc(); return 0; }
    sk_x_00355968();
    {
        word_t meta = sk_x_00002534();
        long buf = sk_x_0036a940(meta, param_2 * 0x18 + 0x20, 7);
        long cap = sk_x_000126e8();
        *(long *)(buf + 0x10) = param_1;
        *(long *)(buf + 0x18) = ((cap - 0x20) / 0x18) << 1;
        return buf;
    }
}

/* FUN_004561cc @ 0x004561cc   (est. sk_arr_reserve_1cc)
 * Reserve-capacity helper (0x20-byte stride). Empty -> 0.
 * Confidence: high */
static long sk_arr_reserve_004561cc(long param_1, long param_2)
{
    if (param_2 <= param_1) param_2 = param_1;
    if (param_2 == 0) { sk_x_000776cc(); return 0; }
    sk_x_00355968();
    {
        word_t meta = sk_x_00002534();
        long buf = sk_x_0036a940(meta, param_2 * 0x20 + 0x20, 7);
        long cap = sk_x_000126e8();
        *(long *)(buf + 0x10) = param_1;
        *(long *)(buf + 0x18) = ((cap - 0x20) / 0x20) << 1;
        return buf;
    }
}

/* FUN_00456238 / 00456294 / 00456310   (est. sk_arr_ensure_delegates)
 * Ghidra: void FUN_00456238/94/310(void)
 * Delegates that store the 0045636c ensure-capacity result into *unaff_x20.
 * Confidence: low (thunk) */
static void sk_arr_ensure_dlg1_00456238(long *self)
{ *self = sk_arr_ensure_0045636c(0, 0, 0, 0); }
static void sk_arr_ensure_dlg2_00456294(long *self)
{ *self = sk_arr_ensure_0045636c(0, 0, 0, 0); }
static void sk_arr_ensure_dlg3_00456310(long *self)
{ *self = sk_arr_ensure_0045636c(0, 0, 0, 0); }

/* FUN_004562f0 @ 0x004562f0   (est. sk_arr_grow_delegate)
 * Ghidra: void FUN_004562f0(void)
 * Delegates that store the 00456420 grow result into *unaff_x20.
 * Confidence: low (thunk) */
static void sk_arr_grow_delegate_004562f0(long *self)
{ *self = sk_arr_grow_00456420(0, 0, 0, 0); }

/* FUN_0045636c @ 0x0045636c   (est. sk_arr_ensure_00636c)
 * Ghidra: long FUN_0045636c(ulong param_1, long param_2, ulong param_3, ...)
 * Ensures the array buffer has capacity for param_2 elements of the element
 * type at param_4+0x10. If the growth flag (param_3&1) is set it consults
 * 004652d4/00465428 for the 1.5x growth factor; then either reserves into a
 * fresh buffer (param_5) or rewrites in place (param_6/param_7), releasing the
 * old buffer. Traps on count overflow.
 * Confidence: medium */
static long sk_arr_ensure_0045636c(word_t param_1, long param_2, word_t param_3,
                                   long param_4)
{
    word_t elem;
    long result;
    if ((param_3 & 1) != 0) {
        sk_x_004652d4();
        param_2 = 0;
        if ((long)(0 + 0x4000000000000000) < 0) CL4_SW_BP(0x456420);
        sk_x_00465428();
        param_2 = 0;
    }
    elem = *(word_t *)(param_4 + 0x10);
    result = 0;   /* (*param_5)(elem, param_2) - reserve */
    if ((param_1 & 1) == 0) {
        sk_x_0006b6e0();
        return result;
    } else {
        /* (*param_6)(param_4 + 0x20, elem, result + 0x20) */
        *(word_t *)(param_4 + 0x10) = 0;
        sk_x_0036b118(param_4);
        return result;
    }
}

/* FUN_00456420 @ 0x00456420   (est. sk_arr_grow_0046420)
 * Ghidra: long FUN_00456420(ulong param_1,...)
 * Grows the array buffer to hold param_2 elements of the 0x20-stride type.
 * When the capacity flag (param_3&1) is set, doubles capacity; reserves via
 * 004561cc and either appends in place (004568d8) or builds fresh
 * (000699a4), releasing the old buffer. Traps on capacity overflow.
 * Confidence: medium */
static long sk_arr_grow_00456420(word_t param_1, word_t param_2, word_t param_3,
                                 long param_4)
{
    long result;
    word_t cap = param_2;
    word_t elem;
    if ((param_3 & 1) != 0) {
        cap = *(word_t *)(param_4 + 0x18) >> 1;
        if ((long)cap < (long)param_2) {
            if ((long)(cap + 0x4000000000000000) < 0) CL4_SW_BP(0x4564e4);
            cap = *(word_t *)(param_4 + 0x18) & 0xfffffffffffffffe;
            if ((long)cap <= (long)param_2) cap = param_2;
        }
    }
    elem = *(word_t *)(param_4 + 0x10);
    result = sk_arr_reserve_004561cc(elem, cap);
    if ((param_1 & 1) == 0) {
        sk_buf_copy_020_004568d8(0, elem, result + 0x20, param_4);
    } else {
        sk_x_000699a4(param_4 + 0x20, elem, result + 0x20);
        *(word_t *)(param_4 + 0x10) = 0;
        sk_x_0036b118(param_4);
    }
    return result;
}

/* FUN_004564e4 @ 0x004564e4   (est. sk_arr_ensure2_00464e4)
 * Ghidra: long FUN_004564e4(ulong param_1,...)
 * Ensure-capacity variant that copies via 00354828 and reserves through
 * 004561cc, then writes in place (param_7) or rebuilds (000699a4).
 * Confidence: medium */
static long sk_arr_ensure2_004564e4(word_t param_1, long param_2, word_t param_3,
                                    long param_4, word_t param_5, word_t param_6,
                                    word_t param_7)
{
    word_t elem;
    long result;
    if ((param_3 & 1) != 0) {
        sk_x_004652d4();
        if ((long)(0 + 0x4000000000000000) < 0) CL4_SW_BP(0x45659c);
        sk_x_00465428();
    }
    elem = *(word_t *)(param_4 + 0x10);
    sk_x_00354828(elem, param_2);
    result = sk_arr_reserve_004561cc(elem, 0);
    if ((param_1 & 1) == 0) {
        sk_buf_copy_020_004568d8(0, elem, result + 0x20, param_4);
    } else {
        sk_x_000699a4(param_4 + 0x20, elem, result + 0x20);
        *(word_t *)(param_4 + 0x10) = 0;
        sk_x_0036b118(param_4);
    }
    return result;
}

/* FUN_0045659c @ 0x0045659c   (est. sk_arr_ensure3_004659c)
 * Ghidra: long FUN_0045659c(ulong param_1,...)
 * Ensure-capacity variant reserving through 004560ec and rebuilding via
 * 0006b6e0 / param_8, or in-place via param_7.
 * Confidence: medium */
static long sk_arr_ensure3_0045659c(word_t param_1, long param_2, word_t param_3,
                                    long param_4, word_t param_5, word_t param_6,
                                    word_t param_7, word_t param_8)
{
    word_t elem;
    long result;
    if ((param_3 & 1) != 0) {
        sk_x_004652d4();
        if ((long)(0 + 0x4000000000000000) < 0) CL4_SW_BP(0x456650);
        sk_x_00465428();
    }
    elem = *(word_t *)(param_4 + 0x10);
    sk_x_00354828(elem, param_2);
    result = sk_arr_reserve_004560ec(elem, 0);
    if ((param_1 & 1) == 0) {
        sk_x_0006b6e0();
    } else {
        sk_x_000699a4(param_4 + 0x20, elem, result + 0x20);
        *(word_t *)(param_4 + 0x10) = 0;
        sk_x_0036b118(param_4);
    }
    return result;
}

/* FUN_00456650 @ 0x00456650   (est. sk_arr_grow2_0046650)
 * Ghidra: long FUN_00456650(ulong param_1,...)
 * Grow variant (0x18-stride) doubling capacity; reserves via 00456158 and
 * appends in place (00456b28) or rebuilds (000699d8).
 * Confidence: medium */
static long sk_arr_grow2_00456650(word_t param_1, word_t param_2, word_t param_3,
                                  long param_4)
{
    long result;
    word_t cap = param_2;
    word_t elem;
    if ((param_3 & 1) != 0) {
        cap = *(word_t *)(param_4 + 0x18) >> 1;
        if ((long)cap < (long)param_2) {
            if ((long)(cap + 0x4000000000000000) < 0) CL4_SW_BP(0x456714);
            cap = *(word_t *)(param_4 + 0x18) & 0xfffffffffffffffe;
            if ((long)cap <= (long)param_2) cap = param_2;
        }
    }
    elem = *(word_t *)(param_4 + 0x10);
    result = sk_arr_reserve_00456158(elem, cap);
    if ((param_1 & 1) == 0) {
        sk_buf_copy_018_00456b28(0, elem, result + 0x20, param_4);
    } else {
        sk_x_000699d8(param_4 + 0x20, elem, result + 0x20);
        *(word_t *)(param_4 + 0x10) = 0;
        sk_x_0036b118(param_4);
    }
    return result;
}

/* FUN_00456714 @ 0x00456714   (est. sk_arr_grow3_0046714)
 * Ghidra: long FUN_00456714(ulong param_1,...)
 * Grow variant (0x18-stride, 00456b28 copy) doubling capacity.
 * Confidence: medium */
static long sk_arr_grow3_00456714(word_t param_1, word_t param_2, word_t param_3,
                                  long param_4)
{
    long result;
    word_t cap = param_2;
    word_t elem;
    if ((param_3 & 1) != 0) {
        cap = *(word_t *)(param_4 + 0x18) >> 1;
        if ((long)cap < (long)param_2) {
            if ((long)(cap + 0x4000000000000000) < 0) CL4_SW_BP(0x4567d8);
            cap = *(word_t *)(param_4 + 0x18) & 0xfffffffffffffffe;
            if ((long)cap <= (long)param_2) cap = param_2;
        }
    }
    elem = *(word_t *)(param_4 + 0x10);
    result = sk_arr_reserve_00456158(elem, cap);
    if ((param_1 & 1) == 0) {
        sk_buf_copy_018_00456b28(0, elem, result + 0x20, param_4);
    } else {
        sk_x_000699d8(param_4 + 0x20, elem, result + 0x20);
        *(word_t *)(param_4 + 0x10) = 0;
        sk_x_0036b118(param_4);
    }
    return result;
}

/* FUN_004567d8 @ 0x004567d8   (est. sk_buf_copy_0178)
 * Ghidra: ulong FUN_004567d8(long param_1, long param_2, ulong param_3, long param_4)
 * Copies the [param_1, param_2) slice (0x178-stride elements) of buffer param_4
 * into destination param_3. Validates the range (trap on underflow), checks
 * for overlap, copies via 0035b67c and releases the source buffer. Returns the
 * end pointer.
 * Confidence: high */
static word_t sk_buf_copy_0178_004567d8(long param_1, long param_2, word_t param_3,
                                        long param_4)
{
    long n = param_2 - param_1;
    if (param_2 < param_1) CL4_SW_BP(0x456850);
    if (n >= 0) {
        word_t src = param_4 + param_1 * 0x178 + 0x20;
        word_t end = param_3 + n * 0x178;
        if (end <= src || src + n * 0x178 <= param_3) {
            sk_x_0035b67c(param_3, src, n, 0x684390);
            sk_x_0036b118(param_4);
            return end;
        }
        CL4_SW_BP(0x456858);
    }
    CL4_SW_BP(0x456854);
}

/* FUN_00456858 @ 0x00456858   (est. sk_buf_copy_038)
 * Copy helper (0x38-stride, 0035b67c). Confidence: high */
static word_t sk_buf_copy_038_00456858(long param_1, long param_2, word_t param_3,
                                       long param_4)
{
    long n = param_2 - param_1;
    if (param_2 < param_1) CL4_SW_BP(0x4568d0);
    if (n >= 0) {
        word_t src = param_4 + param_1 * 0x38 + 0x20;
        word_t end = param_3 + n * 0x38;
        if (end <= src || src + n * 0x38 <= param_3) {
            sk_x_0035b67c(param_3, src, n, 0x684cf0);
            sk_x_0036b118(param_4);
            return end;
        }
        CL4_SW_BP(0x4568d8);
    }
    CL4_SW_BP(0x4568d4);
}

/* FUN_004568d8 @ 0x004568d8   (est. sk_buf_copy_020)
 * Copy helper (0x20-stride, 0035b67c). Confidence: high */
static word_t sk_buf_copy_020_004568d8(long param_1, long param_2, word_t param_3,
                                       long param_4)
{
    long n = param_2 - param_1;
    if (param_2 < param_1) CL4_SW_BP(0x456944);
    if (n >= 0) {
        word_t src = param_4 + param_1 * 0x20 + 0x20;
        word_t end = param_3 + n * 0x20;
        if (end <= src || src + n * 0x20 <= param_3) {
            sk_x_0035b67c(param_3, src, n, 0x685e98);
            sk_x_0036b118(param_4);
            return end;
        }
        CL4_SW_BP(0x45694c);
    }
    CL4_SW_BP(0x456948);
}

/* FUN_0045694c @ 0x0045694c   (est. sk_buf_copy_050)
 * Copy helper (0x50-stride, 0035b67c, tag 006850c8). Confidence: high */
static word_t sk_buf_copy_050_0045694c(long param_1, long param_2, word_t param_3,
                                       long param_4)
{
    long n = param_2 - param_1;
    if (param_2 < param_1) CL4_SW_BP(0x4569c0);
    if (n >= 0) {
        word_t src = param_4 + param_1 * 0x50 + 0x20;
        word_t end = param_3 + n * 0x50;
        if (end <= src || src + n * 0x50 <= param_3) {
            sk_x_0035b67c(param_3, src, n, 0x006850c8);
            sk_x_0036b118(param_4);
            return end;
        }
        CL4_SW_BP(0x4569c8);
    }
    CL4_SW_BP(0x4569c4);
}

/* FUN_004569c8 @ 0x004569c8   (est. sk_buf_copy_030)
 * Copy helper (0x30-stride, 00117cc4 memcpy). Confidence: high */
static word_t sk_buf_copy_030_004569c8(long param_1, long param_2, word_t param_3,
                                       long param_4)
{
    long n = param_2 - param_1;
    if (param_2 < param_1) CL4_SW_BP(0x456a38);
    if (n >= 0) {
        word_t src = param_4 + param_1 * 0x30 + 0x20;
        word_t end = param_3 + n * 0x30;
        if (end <= src || src + n * 0x30 <= param_3) {
            sk_x_00117cc4(param_3, src, n * 0x30);
            sk_x_0036b118(param_4);
            return end;
        }
        CL4_SW_BP(0x456a40);
    }
    CL4_SW_BP(0x456a3c);
}

/* FUN_00456a40 @ 0x00456a40   (est. sk_buf_copy_020b)
 * Copy helper (0x20-stride, 0035b67c, tag 0x683000). Confidence: high */
static word_t sk_buf_copy_020b_00456a40(long param_1, long param_2, word_t param_3,
                                        long param_4)
{
    long n = param_2 - param_1;
    if (param_2 < param_1) CL4_SW_BP(0x456aac);
    if (n >= 0) {
        word_t src = param_4 + param_1 * 0x20 + 0x20;
        word_t end = param_3 + n * 0x20;
        if (end <= src || src + n * 0x20 <= param_3) {
            sk_x_0035b67c(param_3, src, n, 0x683000);
            sk_x_0036b118(param_4);
            return end;
        }
        CL4_SW_BP(0x456ab4);
    }
    CL4_SW_BP(0x456ab0);
}

/* FUN_00456ab4 @ 0x00456ab4   (est. sk_buf_copy_08)
 * Copy helper (8-stride, 0035b67c, tag 0x682e08). Confidence: high */
static word_t sk_buf_copy_08_00456ab4(long param_1, long param_2, word_t param_3,
                                      long param_4)
{
    long n = param_2 - param_1;
    if (param_2 < param_1) CL4_SW_BP(0x456b20);
    if (n >= 0) {
        word_t src = param_4 + param_1 * 8 + 0x20;
        word_t end = param_3 + n * 8;
        if (end <= src || src + n * 8 <= param_3) {
            sk_x_0035b67c(param_3, src, n, 0x682e08);
            sk_x_0036b118(param_4);
            return end;
        }
        CL4_SW_BP(0x456b28);
    }
    CL4_SW_BP(0x456b24);
}

/* FUN_00456b28 @ 0x00456b28   (est. sk_buf_copy_018)
 * Copy helper (0x18-stride, 00117cc4 memcpy). Confidence: high */
static word_t sk_buf_copy_018_00456b28(long param_1, long param_2, word_t param_3,
                                       long param_4)
{
    long n = param_2 - param_1;
    if (param_2 < param_1) CL4_SW_BP(0x456b98);
    if (n >= 0) {
        word_t src = param_4 + param_1 * 0x18 + 0x20;
        word_t end = param_3 + n * 0x18;
        if (end <= src || src + n * 0x18 <= param_3) {
            sk_x_00117cc4(param_3, src, n * 0x18);
            sk_x_0036b118(param_4);
            return end;
        }
        CL4_SW_BP(0x456ba0);
    }
    CL4_SW_BP(0x456b9c);
}

/* FUN_00456ba0 @ 0x00456ba0   (est. sk_buf_copy_020c)
 * Copy helper (0x20-stride, 0035b67c with 0x657b58 metadata). Confidence: high */
static word_t sk_buf_copy_020c_00456ba0(long param_1, long param_2, word_t param_3,
                                        long param_4)
{
    long n = param_2 - param_1;
    if (param_2 < param_1) CL4_SW_BP(0x456c34);
    if (n >= 0) {
        word_t src = param_4 + param_1 * 0x20 + 0x20;
        word_t end = param_3 + n * 0x20;
        if (end <= src || src + n * 0x20 <= param_3) {
            word_t meta = sk_x_00002534(0x657b58, 0x005a3630);
            sk_x_0035b67c(param_3, src, n, meta);
            sk_x_0036b118(param_4);
            return end;
        }
        CL4_SW_BP(0x456c3c);
    }
    CL4_SW_BP(0x456c38);
}

/* FUN_00456c3c @ 0x00456c3c   (est. sk_buf_copy_010)
 * Copy helper (0x10-stride, 0035b67c with 0x657ae8 metadata). Confidence: high */
static word_t sk_buf_copy_010_00456c3c(long param_1, long param_2, word_t param_3,
                                       long param_4)
{
    long n = param_2 - param_1;
    if (param_2 < param_1) CL4_SW_BP(0x456cd0);
    if (n >= 0) {
        word_t src = param_4 + param_1 * 0x10 + 0x20;
        word_t end = param_3 + n * 0x10;
        if (end <= src || src + n * 0x10 <= param_3) {
            word_t meta = sk_x_00002534(0x657ae8, 0x005a3528);
            sk_x_0035b67c(param_3, src, n, meta);
            sk_x_0036b118(param_4);
            return end;
        }
        CL4_SW_BP(0x456cd8);
    }
    CL4_SW_BP(0x456cd4);
}

/* FUN_00456cd8 @ 0x00456cd8   (est. sk_buf_move_0178)
 * Ghidra: void FUN_00456cd8(ulong param_1, long param_2, ulong param_3)
 * Moves param_2 elements (0x178-stride) from param_1 to param_3; validates the
 * count and uses 00117d14 memmove (no overlap check beyond the source range).
 * Confidence: high */
static void sk_buf_move_0178_00456cd8(word_t param_1, long param_2, word_t param_3)
{
    if (param_2 < 0) CL4_SW_BP(0x456d14);
    if (param_3 != param_1 || param_1 + param_2 * 0x178 <= param_3) {
        sk_x_00117d14(param_3, param_1, param_2 * 0x178);
    }
}

/* FUN_00456d50 @ 0x00456d50   (est. sk_buf_move_050)
 * Ghidra: void FUN_00456d50(ulong param_1, long param_2, ulong param_3)
 * Moves param_2 elements (0x50-stride) from param_1 to param_3 with overlap
 * check via 0035b67c; traps on overlap. Confidence: high */
static void sk_buf_move_050_00456d50(word_t param_1, long param_2, word_t param_3)
{
    if (param_2 < 0) CL4_SW_BP(0x456d8c);
    if (param_3 + param_2 * 0x50 <= param_1 || param_1 + param_2 * 0x50 <= param_3) {
        sk_x_0035b67c(param_3, param_1, param_2, 0x006850c8);
        return;
    }
    CL4_SW_BP(0x456d90);
}

/* FUN_00456d90 @ 0x00456d90   (est. sk_str_equal)
 * Ghidra: bool FUN_00456d90(ulong param_1, ulong param_2, long param_3)
 * String equality: compares the small-string (param_1/param_2) against the
 * native UTF-8 buffer at param_3 (count at +0x10, bytes at +0x20). Walks the
 * string via the _StringGuts iterator (0001da84/002a9ba8/002b141c), comparing
 * byte-by-byte. Returns true iff both are exhausted together.
 * Confidence: high */
static bool sk_str_equal_00456d90(word_t param_1, word_t param_2, long param_3)
{
    word_t count = *(word_t *)(param_3 + 0x10);
    word_t uVar1 = param_1 & 0xffffffffffff;
    if ((param_2 & 0x2000000000000000) != 0) uVar1 = (param_2 >> 0x38) & 0xf;
    word_t uVar14 = uVar1 * 4;
    int uVar6 = (int)(param_1 >> 0x3b) & 1;
    if ((param_2 & 0x1000000000000000) == 0) uVar6 = 1;
    word_t idx = 0;
    word_t iter = 0xf;
    while (1) {
        char c1, c2;
        word_t next;
        if (idx == count) { c1 = 0; next = count; }
        else {
            if (count <= idx) CL4_SW_BP(0x456fa0);
            c1 = *(char *)(param_3 + 0x20 + idx);
            next = idx + 1;
        }
        word_t uVar13 = iter >> 0xe;
        if (uVar13 == uVar14) {
            c2 = 0;
        } else {
            word_t p = iter;
            if ((iter & 0xc) == (word_t)(4L << uVar6)) p = sk_x_0001da84(iter, param_1, param_2);
            word_t uVar10 = p >> 0x10;
            if (uVar1 <= uVar10) CL4_SW_BP(0x456fa4);
            if ((param_2 >> 0x3c & 1) == 0) {
                if ((param_2 >> 0x3d & 1) == 0) {
                    word_t base = (param_2 & 0xfffffffffffffff) + 0x20;
                    if ((param_1 >> 0x3c & 1) == 0) base = sk_x_002a9ba8(param_1, param_2).lo;
                    c2 = *(char *)(base + uVar10);
                } else {
                    c2 = *(char *)((word_t)(param_1 & 0xffffffffffff) + uVar10);
                }
            } else {
                c2 = (char)sk_x_002b141c(p, param_1, param_2);
            }
            if ((iter & 0xc) == (word_t)(4L << uVar6)) iter = sk_x_0001da84(iter, param_1, param_2);
            if ((param_2 >> 0x3c & 1) == 0) {
                iter = (iter & 0xffffffffffff0000) + 0x10004;
            } else {
                if (uVar1 <= (iter >> 0x10)) CL4_SW_BP(0x456fa8);
                iter = sk_x_002b141c(iter, param_1, param_2);
            }
        }
        if (idx == count) return uVar13 == uVar14;
        if (uVar13 == uVar14) break;
        idx = next;
        if (c1 != c2) return false;
    }
    return false;
}

/* FUN_00456fa8 @ 0x00456fa8   (est. sk_str_equal_buf)
 * Ghidra: bool FUN_00456fa8(ulong param_1, ulong param_2, char *param_3, char *param_4)
 * String equality against a byte-range [param_3, param_4). Walks both sides
 * with the same small-string iterator; returns true iff both exhausted.
 * Confidence: high */
static bool sk_str_equal_buf_00456fa8(word_t param_1, word_t param_2, char *param_3,
                                      char *param_4)
{
    word_t uVar1 = param_1 & 0xffffffffffff;
    if ((param_2 & 0x2000000000000000) != 0) uVar1 = (param_2 >> 0x38) & 0xf;
    word_t uVar9 = uVar1 * 4;
    int uVar7 = (int)(param_1 >> 0x3b) & 1;
    if ((param_2 & 0x1000000000000000) == 0) uVar7 = 1;
    word_t iter = 0xf;
    while (1) {
        char c1, c2;
        bool done;
        if (param_3 == 0) { c1 = 0; done = true; }
        else {
            if (param_4 == 0) CL4_SW_BP(0x4571b0);
            if (param_3 == param_4) { c1 = 0; done = true; param_3 = param_4; }
            else {
                if (param_4 <= param_3) CL4_SW_BP(0x4571a8);
                done = false; c1 = *param_3; param_3++;
            }
        }
        word_t uVar8 = iter >> 0xe;
        if (uVar8 == uVar9) {
            c2 = 0;
        } else {
            word_t p = iter;
            if ((iter & 0xc) == (word_t)(4L << uVar7)) p = sk_x_0001da84(iter, param_1, param_2);
            word_t uVar11 = p >> 0x10;
            if (uVar1 <= uVar11) CL4_SW_BP(0x4571a4);
            if ((param_2 >> 0x3c & 1) == 0) {
                if ((param_2 >> 0x3d & 1) == 0) {
                    word_t base = (param_2 & 0xfffffffffffffff) + 0x20;
                    if ((param_1 >> 0x3c & 1) == 0) base = sk_x_002a9ba8(param_1).lo;
                    c2 = *(char *)(base + uVar11);
                } else {
                    c2 = *(char *)((word_t)(param_1 & 0xffffffffffff) + uVar11);
                }
            } else {
                c2 = (char)sk_x_002b141c(p, param_1, param_2);
            }
            if ((iter & 0xc) == (word_t)(4L << uVar7)) iter = sk_x_0001da84(iter, param_1, param_2);
            if ((param_2 >> 0x3c & 1) == 0) {
                iter = (iter & 0xffffffffffff0000) + 0x10004;
            } else {
                if (uVar1 <= (iter >> 0x10)) CL4_SW_BP(0x4571ac);
                iter = sk_x_002b141c(iter, param_1, param_2);
            }
        }
        if (done) return uVar8 == uVar9;
        if (uVar8 == uVar9) break;
        if (c1 != c2) return false;
    }
    return false;
}

/* FUN_004571b0 @ 0x004571b0   (est. sk_str_has_prefix)
 * Ghidra: undefined8 FUN_004571b0(char *param_1, char *param_2, ulong param_3, ulong param_4)
 * Returns 1 if the small-string [param_1, param_2) starts with the byte-range
 * prefix (param_3/param_4 string), 0 otherwise. Compares char-by-char.
 * Confidence: high */
static word_t sk_str_has_prefix_004571b0(char *param_1, char *param_2, word_t param_3,
                                         word_t param_4)
{
    word_t uVar2 = param_3 & 0xffffffffffff;
    if ((param_4 & 0x2000000000000000) != 0) uVar2 = (param_4 >> 0x38) & 0xf;
    int uVar9 = (int)(param_3 >> 0x3b) & 1;
    if ((param_4 & 0x1000000000000000) == 0) uVar9 = 1;
    word_t iter = 0xf;
    char *pc = param_1;
    do {
        word_t uVar14 = iter >> 0xe;
        char c1, c2;
        word_t result;
        char *next;
        if (uVar14 == uVar2 * 4) {
            c1 = 0;
            if (pc != 0) goto got1;
            goto empty;
        } else {
            word_t p = iter;
            if ((iter & 0xc) == (word_t)(4L << uVar9)) p = sk_x_0001da84(iter, param_3, param_4);
            word_t uVar13 = p >> 0x10;
            if (uVar2 <= uVar13) CL4_SW_BP(0x4573a4);
            if ((param_4 >> 0x3c & 1) == 0) {
                if ((param_4 >> 0x3d & 1) == 0) {
                    word_t base = (param_4 & 0xfffffffffffffff) + 0x20;
                    if ((param_3 >> 0x3c & 1) == 0) base = sk_x_002a9ba8(param_3, param_4).lo;
                    c1 = *(char *)(base + uVar13);
                } else {
                    c1 = *(char *)((word_t)(param_3 & 0xffffffffffff) + uVar13);
                }
            } else {
                c1 = (char)sk_x_002b141c(p, param_3, param_4);
            }
            if ((iter & 0xc) == (word_t)(4L << uVar9)) iter = sk_x_0001da84(iter, param_3, param_4);
            if ((param_4 >> 0x3c & 1) == 0) {
                iter = (iter & 0xffffffffffff0000) + 0x10004;
            } else {
                if (uVar2 <= (iter >> 0x10)) CL4_SW_BP(0x4573ac);
                iter = sk_x_002b141c(iter, param_3, param_4);
            }
            if (pc == 0) goto empty;
        got1:
            if (param_2 == 0) CL4_SW_BP(0x4573b0);
            if (pc == param_2) { c2 = 0; result = 1; next = param_2; }
            else {
                if (param_2 <= pc) CL4_SW_BP(0x4573a8);
                result = 0; next = pc + 1; c2 = *pc;
            }
        }
        if (uVar14 == uVar2 * 4) return result;
        if (c1 == c2) { pc = next; continue; }
        return 0;
    empty:
        c2 = 0;
        if (uVar14 == uVar2 * 4) return 1;
        return 0;
    } while (1);
}

/* FUN_004573b0 @ 0x004573b0   (est. sk_str_contains_equiv)
 * Ghidra: undefined8 FUN_004573b0(undefined *param_1, ...)
 * Equivalence / contains primitive: walks the small-string (param_1/param_2)
 * and the reference string (param_5/param_6), comparing runs; returns 1 when
 * the reference is exhausted within the subject, 0 otherwise. Retains the
 * reference (thunk 0036b270) and releases it (003a25d4) before returning.
 * Confidence: low (string-iterator fragment heavy) */
static word_t sk_str_contains_equiv_004573b0(byte *param_1, word_t param_2, word_t param_3,
                                             word_t param_4, word_t param_5, word_t param_6)
{
    word_t uVar1 = param_5 & 0xffffffffffff;
    if ((param_6 & 0x2000000000000000) != 0) uVar1 = (param_6 >> 0x38) & 0xf;
    int uVar9 = (int)(param_5 >> 0x3b) & 1;
    if ((param_6 & 0x1000000000000000) == 0) uVar9 = 1;
    int uVar10 = (int)(param_3 >> 0x3b) & 1;
    if ((param_4 & 0x1000000000000000) == 0) uVar10 = 1;
    word_t uVar2 = param_3 & 0xffffffffffff;
    if ((param_4 & 0x2000000000000000) != 0) uVar2 = (param_4 >> 0x38) & 0xf;
    word_t result;
    sk_x_0036b270(param_6);
    word_t iter = 0xf;
    byte *pc = param_1;
    do {
        word_t uVar12 = iter >> 0xe;
        char c1, c2;
        if (uVar12 == uVar1 * 4) {
            if (((word_t)pc ^ param_2) < 0x4000) { result = 1; goto ret; }
            c1 = 0;
        } else {
            word_t p = iter;
            if ((iter & 0xc) == (word_t)(4L << uVar9)) p = sk_x_0001da84(iter, param_5, param_6);
            word_t uVar11 = p >> 0x10;
            if (uVar1 <= uVar11) CL4_SW_BP(0x457648);
            if ((param_6 >> 0x3c & 1) == 0) {
                if ((param_6 >> 0x3d & 1) == 0) {
                    word_t base = (param_6 & 0xfffffffffffffff) + 0x20;
                    if ((param_5 >> 0x3c & 1) == 0) base = sk_x_002a9ba8(param_5, param_6).lo;
                    c1 = *(char *)(base + uVar11);
                } else {
                    c1 = *(char *)((word_t)(param_5 & 0xffffffffffff) + uVar11);
                }
            } else {
                c1 = (char)sk_x_002b141c(p, param_5, param_6);
            }
            if ((iter & 0xc) == (word_t)(4L << uVar9)) iter = sk_x_0001da84(iter, param_5, param_6);
            if ((param_6 >> 0x3c & 1) == 0) {
                iter = (iter & 0xffffffffffff0000) + 0x10004;
            } else {
                if (uVar1 <= (iter >> 0x10)) CL4_SW_BP(0x45764c);
                iter = sk_x_002b141c(iter, param_5, param_6);
            }
            if (((word_t)pc ^ param_2) < 0x4000) { result = 0; goto ret; }
        }
        c2 = (char)sk_x_002b5ba0((word_t)pc, (word_t)param_1, param_2, param_3, param_4);
        if (((word_t)pc & 0xc) == (word_t)(4L << uVar10)) {
            pc = (byte *)sk_x_0001da84((word_t)pc, param_3, param_4);
            if ((param_4 >> 0x3c & 1) == 0) {
                pc = (byte *)(((word_t)pc & 0xffffffffffff0000) + 0x10004);
            } else {
                if (uVar2 <= ((word_t)pc >> 0x10)) CL4_SW_BP(0x457650);
                pc = (byte *)sk_x_002b141c((word_t)pc, param_3, param_4);
            }
        } else {
            if ((param_4 >> 0x3c & 1) != 0) {
                if (uVar2 <= ((word_t)pc >> 0x10)) CL4_SW_BP(0x457650);
                pc = (byte *)sk_x_002b141c((word_t)pc, param_3, param_4);
            } else {
                pc = (byte *)(((word_t)pc & 0xffffffffffff0000) + 0x10004);
            }
        }
        result = 0;
        if (uVar12 == uVar1 * 4 || c1 != c2) goto ret;
    } while (1);
ret:
    sk_x_003a25d4(param_6);
    return result;
}

/* FUN_00457650 @ 0x00457650   (est. sk_str_suffix_equiv)
 * Ghidra: undefined8 FUN_00457650(ulong param_1,...)
 * Suffix-equivalence primitive: walks the subject (param_3/param_4) against
 * the reference (param_1/param_2), comparing runs; returns 1 on match.
 * Confidence: low (string-iterator fragment heavy) */
static word_t sk_str_suffix_equiv_00457650(word_t param_1, word_t param_2, byte *param_3,
                                           word_t param_4, word_t param_5, word_t param_6)
{
    int uVar9 = (int)(param_5 >> 0x3b) & 1;
    if ((param_6 & 0x1000000000000000) == 0) uVar9 = 1;
    word_t uVar1 = param_5 & 0xffffffffffff;
    if ((param_6 & 0x2000000000000000) != 0) uVar1 = (param_6 >> 0x38) & 0xf;
    word_t uVar2 = param_1 & 0xffffffffffff;
    if ((param_2 & 0x2000000000000000) != 0) uVar2 = (param_2 >> 0x38) & 0xf;
    int uVar10 = (int)(param_1 >> 0x3b) & 1;
    if ((param_2 & 0x1000000000000000) == 0) uVar10 = 1;
    word_t result;
    sk_x_0036b270(param_2);
    word_t iter = 0xf;
    byte *pc = param_3;
    do {
        word_t uVar13 = (word_t)pc ^ param_4;
        char c1, c2;
        if (uVar13 < 0x4000) {
            if (uVar2 * 4 == (iter >> 0xe)) { result = 1; goto ret; }
            c1 = 0;
        } else {
            c1 = (char)sk_x_002b5ba0((word_t)pc, (word_t)param_3, param_4, param_5, param_6);
            if (((word_t)pc & 0xc) == (word_t)(4L << uVar9)) pc = (byte *)sk_x_0001da84((word_t)pc, param_5, param_6);
            if ((param_6 >> 0x3c & 1) == 0) {
                pc = (byte *)(((word_t)pc & 0xffffffffffff0000) + 0x10004);
            } else {
                if (uVar1 <= ((word_t)pc >> 0x10)) CL4_SW_BP(0x4578dc);
                pc = (byte *)sk_x_002b141c((word_t)pc, param_5, param_6);
            }
            if (uVar2 * 4 == (iter >> 0xe)) { result = 0; goto ret; }
        }
        word_t p = iter;
        if ((iter & 0xc) == (word_t)(4L << uVar10)) p = sk_x_0001da84(iter, param_1, param_2);
        word_t uVar12 = p >> 0x10;
        if (uVar2 <= uVar12) CL4_SW_BP(0x4578d4);
        if ((param_2 >> 0x3c & 1) == 0) {
            if ((param_2 >> 0x3d & 1) == 0) {
                word_t base = (param_2 & 0xfffffffffffffff) + 0x20;
                if ((param_1 >> 0x3c & 1) == 0) base = sk_x_002a9ba8(param_1, param_2).lo;
                c2 = *(char *)(base + uVar12);
            } else {
                c2 = *(char *)((word_t)(param_1 & 0xffffffffffff) + uVar12);
            }
        } else {
            c2 = (char)sk_x_002b141c(p, param_1, param_2);
        }
        if ((iter & 0xc) == (word_t)(4L << uVar10)) iter = sk_x_0001da84(iter, param_1, param_2);
        if ((param_2 >> 0x3c & 1) == 0) {
            iter = (iter & 0xffffffffffff0000) + 0x10004;
        } else {
            if (uVar2 <= (iter >> 0x10)) CL4_SW_BP(0x4578d8);
            iter = sk_x_002b141c(iter, param_1, param_2);
        }
        result = 0;
        if (uVar13 < 0x4000 || c1 != c2) goto ret;
    } while (1);
ret:
    sk_x_003a25d4(param_2);
    return result;
}

/* FUN_004578dc @ 0x004578dc   (est. sk_arr_release_compact)
 * Ghidra: void FUN_004578dc(void)
 * Compacts the array buffer *unaff_x20: validates it (00349a18, 003a261c),
 * and if the buffer is shared (low bit clear) releases its element type
 * (0006b3f4), runs the 004661b8 destructor and rebuilds the buffer via the
 * unaff_x19 closure.
 * Confidence: low (closure-fragment heavy) */
static void sk_arr_release_compact_004578dc(long *self)
{
    word_t uVar1;
    long buf = *self;
    sk_x_00349a18();
    uVar1 = sk_x_003a261c(buf);
    *self = buf;
    if ((uVar1 & 1) == 0) {
        sk_x_0006b3f4(*(word_t *)(buf + 0x10));
        sk_x_004661b8();
        *self = 0;   /* (*unaff_x19)() */
    }
}

/* FUN_00457938 @ 0x00457938   (est. sk_arr_release_compact2)
 * Ghidra: void FUN_00457938(void)
 * Same compaction, rebuilding via the 0045659c ensure helper.
 * Confidence: low */
static void sk_arr_release_compact2_00457938(long *self)
{
    word_t uVar1;
    long buf = *self;
    sk_x_00349a18();
    uVar1 = sk_x_003a261c(buf);
    *self = buf;
    if ((uVar1 & 1) == 0) {
        sk_x_0006b3f4(*(word_t *)(buf + 0x10));
        sk_x_004661b8();
        *self = sk_arr_ensure3_0045659c(0, 0, 0, 0, 0, 0, 0, 0);
    }
}

/* FUN_00457994 @ 0x00457994   (est. sk_arr_reserve_1_elem)
 * Ghidra: void FUN_00457994(long param_1)
 * Ensures the buffer *unaff_x20 has room for param_1+1 elements of the
 * 0x20-stride type: if capacity (count>>1 at +0x18) is too small, grows via
 * 00465ed4 + the closure.
 * Confidence: medium */
static void sk_arr_reserve_1_elem_00457994(long param_1, long *self)
{
    if ((long)(*(word_t *)(*self + 0x18) >> 1) < param_1 + 1) {
        cl4_pair_t au = sk_x_00465ed4(0);
        *self = 0;   /* (*extraout_x8)(au.lo, au.hi, 1) */
    }
}

/* FUN_004579e0 @ 0x004579e0   (est. sk_arr_reserve_1_elem2)
 * Ghidra: void FUN_004579e0(long param_1)
 * Same reserve for param_1+1 elements, growing via 0006b42c + 0045659c.
 * Confidence: medium */
static void sk_arr_reserve_1_elem2_004579e0(long param_1, long *self)
{
    if ((long)(*(word_t *)(*self + 0x18) >> 1) < param_1 + 1) {
        cl4_pair_t au = sk_x_0006b42c();
        *self = sk_arr_ensure3_0045659c(au.lo, au.hi, 1, 0, 0, 0, 0, 0);
    }
}

/* FUN_00457a28 @ 0x00457a28   (est. sk_arr_ensure_param_28)
 * Ghidra: void FUN_00457a28(long param_1)
 * Ensure-capacity for the 0x10-stride buffer at param_1 via 0045659c with the
 * 0x657af0 metadata, 00069970 copy and 00456c3c reserve.
 * Confidence: medium */
static void sk_arr_ensure_param_28_00457a28(long param_1)
{
    sk_arr_ensure3_0045659c(0, *(word_t *)(param_1 + 0x10), 0, param_1,
                            0x657af0, 0x005a3530, (word_t)sk_x_00069970,
                            (word_t)sk_buf_copy_010_00456c3c);
}

/* FUN_00457a88 @ 0x00457a88   (est. sk_arr_ensure_param_88)
 * Ghidra: void FUN_00457a88(long param_1)
 * Ensure-capacity for the buffer at param_1 via 0045659c with 0x64e110
 * metadata and the 00069770 copy.
 * Confidence: medium */
static void sk_arr_ensure_param_88_00457a88(long param_1)
{
    sk_arr_ensure3_0045659c(0, *(word_t *)(param_1 + 0x10), 0, param_1,
                            0x64e110, 0x004c05b0, (word_t)sk_x_00069970,
                            (word_t)sk_x_00069770);
}

/* FUN_00457ae8 @ 0x00457ae8   (est. sk_str_init_from_substr)
 * Ghidra: undefined1[16] FUN_00457ae8(ulong param_1,...)
 * Builds a 16-byte String from a substring view: retains the view (0036b270),
 * builds the buffer descriptor via 0022d2f4, normalizes to a native small or
 * buffer-backed string, then invokes 00457bec to produce the final string.
 * Confidence: low (string-layout fragment heavy) */
static cl4_pair_t sk_str_init_from_substr_00457ae8(word_t param_1, word_t param_2,
                                                   word_t param_3, word_t param_4,
                                                   word_t param_5)
{
    cl4_pair_t au;
    word_t uVar1, uVar2;
    sk_x_0036b270(param_4);
    au = sk_x_0022d2f4((word_t)&param_1, 0x675c68, 0x66e720, 0x66e6e0);
    uVar2 = au.hi;
    if ((uVar2 >> 0x3c & 1) != 0) {
        au = sk_x_0001d4a0(au.lo, uVar2);
        sk_x_003a25d4(uVar2);
    }
    uVar1 = au.hi;
    uVar2 = au.lo;
    if ((uVar1 >> 0x3d & 1) == 0) {
        if ((uVar2 >> 0x3c & 1) == 0) {
            au = sk_x_002a9ba8(uVar2, uVar1);
        } else {
            au.hi = uVar2 & 0xffffffffffff;
            au.lo = (uVar1 & 0xfffffffffffffff) + 0x20;
        }
    } else {
        au.hi = uVar1 >> 0x38 & 0xf;
        au.lo = (word_t)&param_1;
    }
    au = sk_str_parse_int_00457bec((byte *)au.lo, (long)au.hi, (long)param_5);
    sk_x_003a25d4(uVar1);
    return au;
}

/* FUN_00457bec @ 0x00457bec   (est. sk_str_parse_int_00457bec)
 * Ghidra: undefined1[16] FUN_00457bec(byte *param_1, long param_2, long param_3)
 * Parses the byte-string [param_1, param_1+param_2) as an integer in the given
 * radix param_3 (2..36), honoring an optional leading '+'/'-' sign. Accumulates
 * digit-by-digit with overflow detection (traps into a saturating zero result).
 * Returns the 16-byte {value, error|sign} pair.
 * Confidence: high */
static cl4_pair_t sk_str_parse_int_00457bec(byte *param_1, long param_2, long param_3)
{
    cl4_pair_t au;
    long radix = (int)param_3;
    long result = 0;
    word_t neg = 1;   /* sign tag: 0 = ok */
    int iradix = (int)param_3;

    if (param_2 < 1) CL4_SW_BP(0x457e68);
    if (*param_1 == '+') {
        param_2--;
        if ((param_2 != 0) && (param_1 == 0)) CL4_SW_BP(0x457e70);
        if (param_2 == 0) goto zero;
        /* parse digits accumulating positively */
        while (param_2 != 0) {
            byte b = *++param_1;
            long d;
            if (b < 0x30 || (radix + 0x30) <= b) {
                if (b < 0x41 || (radix + 0x37) <= b) {
                    if (b < 0x61 || (radix + 0x57) <= b) { neg = 1; goto done; }
                    d = b - 0x57;
                } else d = b - 0x37;
            } else d = b - 0x30;
            if ((result * radix) < 0 || (long)((unsigned long)result * radix >> 8) != ((unsigned long)result * radix >> 0x3f)) goto zero;
            long prod = result * radix;
            result = prod + d;
            if (prod < 0 || result < 0 || (result < prod)) goto zero;
            param_2--;
        }
        neg = 0;
        goto done;
    }
    if (*param_1 == '-') {
        param_2--;
        if ((param_2 != 0) && (param_1 == 0)) CL4_SW_BP(0x457e6c);
        if (param_2 == 0) goto zero;
        while (param_2 != 0) {
            byte b = *++param_1;
            long d;
            if (b < 0x30 || (radix + 0x30) <= b) {
                if (b < 0x41 || (radix + 0x37) <= b) {
                    if (b < 0x61 || (radix + 0x57) <= b) { neg = 1; goto done; }
                    d = b - 0x57;
                } else d = b - 0x37;
            } else d = b - 0x30;
            if ((result * radix) < 0) goto zero;
            long prod = result * radix;
            result = prod - d;
            if (prod < 0 || result > prod) goto zero;
            param_2--;
        }
        neg = 0;
        goto done;
    }
    /* unsigned positive parse */
    while (param_2 != 0) {
        byte b = *param_1++;
        long d;
        if (b < 0x30 || (radix + 0x30) <= b) {
            if (b < 0x41 || (radix + 0x37) <= b) {
                if (b < 0x61 || (radix + 0x57) <= b) { neg = 1; goto done; }
                d = b - 0x57;
            } else d = b - 0x37;
        } else d = b - 0x30;
        if ((result * radix) < 0) goto zero;
        long prod = result * radix;
        result = prod + d;
        if (prod < 0 || result < prod) goto zero;
        param_2--;
    }
    neg = 0;
    goto done;
zero:
    result = 0;
    neg = 1;
done:
    au.lo = result;
    au.hi = neg;
    return au;
}

/* FUN_00457e70 @ 0x00457e70   (est. sk_range_check_le)
 * Ghidra: void FUN_00457e70(long param_1, long param_2)
 * Bounds check: traps if param_1 > param_2.
 * Confidence: high */
static void sk_range_check_le_00457e70(long param_1, long param_2)
{
    if (param_1 <= param_2) return;
    CL4_SW_BP(0x457e80);
}

/* FUN_00457e80 @ 0x00457e80   (est. sk_str_from_scalar)
 * Ghidra: undefined1[16] FUN_00457e80(void)
 * Builds a 16-byte String from a Unicode scalar: 0001d648 provides the scalar
 * metadata, 001e9c78 wraps it into the small-string descriptor, releasing the
 * temp.
 * Confidence: medium */
static cl4_pair_t sk_str_from_scalar_00457e80(void)
{
    cl4_pair_t au;
    long s = sk_x_0001d648();
    au = sk_x_001e9c78(s + 0x20, *(word_t *)(s + 0x10));
    sk_x_0036b118(s);
    return au;
}

/* FUN_00457ed8 @ 0x00457ed8   (est. sk_arr_ensure_from_elem)
 * Ghidra: void FUN_00457ed8(void)
 * Ensures the buffer *unaff_x20 has room for the element count reported by
 * 0035199c; if not, grows via 0045636c.
 * Confidence: medium */
static void sk_arr_ensure_from_elem_00457ed8(long *self)
{
    cl4_pair_t au;
    long buf;
    long elem_count;
    word_t uVar2;
    sk_x_00084220();
    au = sk_x_0035199c();
    elem_count = au.lo;
    buf = *self;
    uVar2 = sk_x_003a261c(buf);
    *self = buf;
    if ((int)uVar2 == 0 || (long)(*(word_t *)(buf + 0x18) >> 1) < elem_count) {
        long want = *(long *)(buf + 0x10);
        if (*(long *)(buf + 0x10) <= elem_count) want = elem_count;
        *self = sk_arr_ensure_0045636c(uVar2, want, au.hi & 1, buf);
    }
    sk_x_00084234(0);
}

/* FUN_00457f5c @ 0x00457f5c   (est. sk_utf32_range_table)
 * Ghidra: long FUN_00457f5c(void)
 * Builds the scalar-to-block range table (0x43e020 bytes, 4-byte entries):
 * allocates the buffer (0036a940 with 006575f0 metadata), fills it via
 * 00458018 over the 0010f800 scalar table, validating the produced pointer
 * equals the sentinel. Returns the buffer base.
 * Confidence: medium */
static long sk_utf32_range_table_00457f5c(void)
{
    word_t meta = sk_x_00002534(0x006575f0, 0x005a19e0);
    long buf = sk_x_0036a940(meta, 0x43e020, 7);
    long cap = sk_x_000126e8();
    word_t sentinel = 0x0010f800;
    *(long *)(buf + 0x10) = sentinel;
    *(long *)(buf + 0x18) = ((cap - 0x20) / 4) << 1;
    {
        byte *p = (byte *)sk_utf32_scalar_fill_00458018((word_t *)&sentinel, buf + 0x20, sentinel);
        if (sentinel == 0x0010f800) {
            if (p != (byte *)0x0010f800) CL4_SW_BP(0x457ff8);
            return buf;
        }
        sk_x_0044f298(sentinel);
        if ((byte *)0x10f7ff < (byte *)sentinel) CL4_SW_BP(0x458018);
        CL4_SW_BP(0x458014);
    }
}

/* FUN_00458018 @ 0x00458018   (est. sk_utf32_scalar_fill)
 * Ghidra: undefined * FUN_00458018(undefined8 *param_1, long param_2, undefined *param_3)
 * Fills param_3 32-bit scalar values into the table at param_2, validating each
 * scalar (surrogate / out-of-range checks, with the 0x800 surrogate-plane
 * adjustment) and stopping at the 0010f800 sentinel. Stores the count into
 * *param_1 and returns it.
 * Confidence: medium */
static word_t sk_utf32_scalar_fill_00458018(word_t *param_1, long param_2, word_t param_3)
{
    word_t sentinel = 0x0010f800;
    if (param_2 == 0) param_3 = 0;
    else {
        if ((long)param_3 < 0) CL4_SW_BP(0x4580b4);
        if (param_3 != 0) {
            word_t i = 0;
            do {
                word_t v;
                if (i == sentinel) { param_3 = sentinel; break; }
                v = i;
                if (0x1a < (i >> 0xb)) {
                    if ((word_t)0xfffff7ff < i) CL4_SW_BP(0x4580a8);
                    v = i + 0x800;
                }
                if ((v & 0xfffff800) == 0xd800) CL4_SW_BP(0x4580b0);
                if (0x10ffff < v) CL4_SW_BP(0x4580ac);
                *(int *)(param_2 + (long)i * 4) = (int)v;
                i++;
            } while (param_3 != i);
        }
    }
    *param_1 = param_3;
    return param_3;
}

/* FUN_004580b4 @ 0x004580b4   (est. sk_elem_release_0x10)
 * Ghidra: void FUN_004580b4(undefined8 param_1, long param_2)
 * Releases the elements of a 0x10-stride buffer: for each of the count
 * (+0x10) elements, retains/releases the embedded object word via
 * 0036b270/00410414/0036b118. Releases the buffer header (002298d4).
 * Confidence: high */
static void sk_elem_release_0x10_004580b4(word_t param_1, long param_2)
{
    long n = *(long *)(param_2 + 0x10);
    sk_x_002298d4(n);
    if (n != 0) {
        word_t *p = (word_t *)(param_2 + 0x20);
        do {
            word_t w = *p;
            sk_x_0036b270(w & 0xfffffffffffffff);
            sk_x_00410414(param_1, w);
            sk_x_0036b118(w & 0xfffffffffffffff);
            n--; p++;
        } while (n != 0);
    }
}

/* FUN_0045811c @ 0x0045811c   (est. sk_elem_release_0x20)
 * Ghidra: void FUN_0045811c(void)
 * Releases the elements of a 0x20-stride buffer (three words per element:
 * retain 0036b270, destructor 00462ee8, 001b9084, release 003a25d4, and two
 * nested object deallocs 002298d4). Releases the header.
 * Confidence: high */
static void sk_elem_release_0x20_0045811c(void)
{
    long n;
    word_t uVar1, uVar2, uVar3;
    word_t *p;
    sk_x_00084220();
    sk_x_004665bc();
    for (n = 0; n < 0; ) { ; }   /* register-fragment: count in unaff_x19 */
    sk_x_00084234(0);
}

/* FUN_00458190 @ 0x00458190   (est. sk_elem_release_0x18)
 * Ghidra: void FUN_00458190(undefined8 param_1, long param_2)
 * Releases the elements of a 0x18-stride buffer (three words per element: a
 * class 0022995c, then two nested object deallocs 002298d4). Releases header.
 * Confidence: high */
static void sk_elem_release_0x18_00458190(word_t param_1, long param_2)
{
    long n = *(long *)(param_2 + 0x10);
    sk_x_002298d4(n);
    if (n != 0) {
        word_t *p = (word_t *)(param_2 + 0x30);
        do {
            word_t a = p[-1], b = p[0];
            sk_x_0022995c((int)p[-2]);
            sk_x_002298d4(a >> 0xe);
            sk_x_002298d4(b >> 0xe);
            p += 3; n--;
        } while (n != 0);
    }
}

/* FUN_00458200 @ 0x00458200   (est. sk_elem_release_0x30)
 * Ghidra: void FUN_00458200(undefined8 param_1, long param_2)
 * Releases the elements of a 0x30-stride buffer (six words per element: a
 * 0041b3d4 destructor plus two nested object deallocs). Releases header.
 * Confidence: high */
static void sk_elem_release_0x30_00458200(word_t param_1, long param_2)
{
    long n = *(long *)(param_2 + 0x10);
    sk_x_002298d4(n);
    if (n != 0) {
        word_t *p = (word_t *)(param_2 + 0x28);
        do {
            word_t a = p[3], b = p[4];
            sk_x_0041b3d4(param_1, p[-1], p[0], p[1], p[2]);
            sk_x_002298d4(a >> 0xe);
            sk_x_002298d4(b >> 0xe);
            p += 6; n--;
        } while (n != 0);
    }
}

/* FUN_00458278 @ 0x00458278   (est. sk_elem_release_0x20c)
 * Ghidra: void FUN_00458278(undefined8 param_1, long param_2)
 * Releases the elements of a 0x20-stride buffer variant (three words per
 * element: class tag + two object deallocs). Releases header.
 * Confidence: high */
static void sk_elem_release_0x20c_00458278(word_t param_1, long param_2)
{
    long n = *(long *)(param_2 + 0x10);
    sk_x_002298d4(n);
    if (n != 0) {
        word_t *p = (word_t *)(param_2 + 0x30);
        do {
            word_t a = p[-1], b = p[0];
            sk_x_002298d4((byte)p[-2]);
            sk_x_002298d4(a >> 0xe);
            sk_x_002298d4(b >> 0xe);
            p += 3; n--;
        } while (n != 0);
    }
}

/* FUN_004582e8 @ 0x004582e8   (est. sk_elem_release_0x178)
 * Ghidra: void FUN_004582e8(undefined8 param_1, long param_2)
 * Releases the elements of a 0x178-stride buffer. Each element is a tagged
 * record (00458d04 reads its 0x3d-bit tag at +0x170); the tag selects the
 * release path: case 0 default (name+count pair release), 1 (0x99-byte
 * sub-record + nested array), 2 (0x99-byte sub-record), 3/4 (bare words),
 * 5 (array-of-strings). Emits '[' / '[...]' operator names (0x5b / 0x5e5b)
 * and releases nested buffers. Releases the header.
 * Confidence: medium (large switch faithfully transcribed) */
static void sk_elem_release_0x178_004582e8(word_t param_1, long param_2)
{
    long n = *(long *)(param_2 + 0x10);
    word_t uVar16, uVar1, uVar11, uVar2, uVar15, uVar9;
    sk_x_002298d4(n);
    if (n != 0) {
        long idx = 0;
        do {
            byte rec538[376], rec3c0[376], rec6b0[376];
            byte sub[168];
            word_t lVar8 = param_2 + 0x20 + idx * 0x178;
            word_t tag;
            sk_x_00117cc4((word_t)rec538, lVar8, 0x178);
            sk_x_00117cc4((word_t)rec3c0, lVar8, 0x178);
            tag = sk_tag_read_45_00458d04((word_t)rec538);
            switch (tag) {
            default: {
                /* tagged name+count record release */
                char *pc = (char *)(word_t)rec3c0;   /* FUN_00458d10's x0 carries the buffer */
                char cVar3 = *pc;
                uVar16 = *(word_t *)(pc + 8);
                uVar1 = *(word_t *)(pc + 0x10);
                uVar11 = *(word_t *)(pc + 0x18);
                uVar2 = *(word_t *)(pc + 0x20);
                uVar15 = *(word_t *)(pc + 0x28);
                sk_x_002298d4(0);
                word_t op = (cVar3 == 1) ? 0x5e5b : 0x5b;
                word_t tagw = (cVar3 == 1) ? 0xe200000000000000 : 0xe100000000000000;
                sk_script_wit_apply5_00458d30((word_t)rec538, (word_t)rec6b0);
                sk_x_001b9084(param_1, op, tagw);
                sk_x_003a25d4(tagw);
                sk_x_002298d4(uVar16 >> 0xe);
                sk_x_002298d4(uVar1 >> 0xe);
                sk_elem_release_0x178_004582e8(param_1, uVar11);
                sk_x_002298d4(uVar2 >> 0xe);
                break;
            }
            case 1: {
                /* 0x99-byte sub-record + nested array release */
                byte sub2[160];
                word_t subptr = (word_t)rec3c0;   /* x0 after 00458d10 */
                sk_x_002298d4(1);
                sk_x_00117cc4((word_t)sub2, subptr, 0x99);
                sk_x_00117cc4((word_t)rec6b0, (word_t)rec538, 0x178);
                word_t uVar9 = (word_t)rec6b0;
                sk_x_00461d68(uVar9, 0);
                sk_x_0041360c(param_1);
                uVar16 = *(word_t *)(subptr + 0xa8);
                sk_x_002298d4(*(word_t *)(subptr + 0xa0) >> 0xe);
                sk_x_002298d4(uVar16 >> 0xe);
                uVar16 = *(word_t *)(subptr + 0xb8);
                sk_x_002298d4(*(word_t *)(subptr + 0xb0) >> 0xe);
                sk_x_002298d4(uVar16 >> 0xe);
                sk_x_00117cc4((word_t)sub, subptr + 0xc0, 0x99);
                sk_x_0041360c(param_1);
                uVar16 = *(word_t *)(subptr + 0x168);
                sk_x_002298d4(*(word_t *)(subptr + 0x160) >> 0xe);
                sk_x_002298d4(uVar16 >> 0xe);
                word_t inner = *(word_t *)(subptr + 0x170);
                long inner_n = *(long *)(inner + 0x10);
                sk_x_002298d4(inner_n);
                if (inner_n != 0) {
                    word_t *p = (word_t *)(inner + 0x38);
                    do {
                        word_t a = p[-3], b = p[-2], c = p[-1], d = p[0];
                        sk_x_0036b270(b);
                        sk_x_001b9084(param_1, a, b);
                        sk_x_003a25d4(b);
                        sk_x_002298d4(c >> 0xe);
                        sk_x_002298d4(d >> 0xe);
                        p += 4;
                        inner_n--;
                    } while (inner_n != 0);
                }
                sk_script_wit_run5_00458d40((word_t)rec538);
                break;
            }
            case 2: {
                /* 0x99-byte sub-record release */
                word_t subptr = (word_t)rec3c0;
                sk_x_002298d4(2);
                sk_x_00117cc4((word_t)sub, subptr, 0x99);
                sk_x_00117cc4((word_t)rec6b0, (word_t)rec538, 0x178);
                word_t uVar9 = (word_t)rec6b0;
                sk_script_wit_apply_004589e8(uVar9, 0);
                sk_x_0041360c(param_1);
                uVar15 = *(word_t *)(subptr + 0xa8);
                sk_x_002298d4(*(word_t *)(subptr + 0xa0) >> 0xe);
                break;
            }
            case 3:
            case 4: {
                word_t *p = (word_t *)(word_t)rec3c0;
                uVar9 = p[0]; uVar11 = p[1]; uVar16 = p[2]; uVar15 = p[3];
                word_t tagn = tag;   /* 3 or 4 */
                sk_x_002298d4(tagn);
                sk_x_00117cc4((word_t)rec6b0, (word_t)rec538, 0x178);
                word_t lVar8 = (word_t)rec6b0;
                sk_x_0036b270(*(word_t *)(lVar8 + 8));
                sk_x_001b9084(param_1, uVar9, uVar11);
                sk_x_002298d4(uVar16 >> 0xe);
                break;
            }
            case 5: {
                word_t *p = (word_t *)(word_t)rec3c0;
                uVar11 = p[0];
                byte bVar4 = *(byte *)(p + 1);
                uVar16 = p[2];
                uVar15 = p[3];
                word_t uVar13 = p[4];
                sk_x_002298d4(5);
                sk_x_00117cc4((word_t)rec6b0, (word_t)rec538, 0x178);
                word_t *q = (word_t *)(word_t)rec6b0;
                uVar9 = q[4];
                sk_x_0036b270(q[0]);
                sk_x_0036b270(uVar9);
                sk_elem_release_0x178_004582e8(param_1, uVar11);
                sk_x_001b9084(param_1, *(word_t *)((word_t)&DAT_005a3a50 + (word_t)bVar4 * 8), 0xe200000000000000);
                sk_x_003a25d4(0xe200000000000000);
                sk_x_002298d4(uVar16 >> 0xe);
                sk_x_002298d4(uVar15 >> 0xe);
                sk_elem_release_0x178_004582e8(param_1, uVar13);
                sk_script_wit_run5_00458d40((word_t)rec538);
                break;
            }
            }
            sk_script_wit_run5_00458d40((word_t)rec538);
            idx++;
        } while (idx != n);
    }
}

/* FUN_00458720 @ 0x00458720   (est. sk_elem_release_0x10b)
 * Ghidra: void FUN_00458720(undefined8 param_1, long param_2)
 * Releases the elements of a 0x10-stride buffer variant (two words per
 * element, both nested object deallocs). Releases header.
 * Confidence: high */
static void sk_elem_release_0x10b_00458720(word_t param_1, long param_2)
{
    long n = *(long *)(param_2 + 0x10);
    sk_x_002298d4(n);
    if (n != 0) {
        word_t *p = (word_t *)(param_2 + 0x28);
        do {
            word_t a = p[0];
            sk_x_002298d4(p[-1] >> 0xe);
            sk_x_002298d4(a >> 0xe);
            p += 2; n--;
        } while (n != 0);
    }
}

/* FUN_00458780 @ 0x00458780   (est. sk_elem_release_0x50)
 * Ghidra: void FUN_00458780(undefined8 param_1, long param_2)
 * Releases the elements of a 0x50-stride buffer (ten words per element): a
 * class tag, an owned object (0036b270/00458eec/001b9084/003a25d4), three
 * pairs of nested object deallocs, and a 'case' 00229a3c that conditionally
 * runs 0042d720/00458f88. Releases header.
 * Confidence: high */
static void sk_elem_release_0x50_00458780(word_t param_1, long param_2)
{
    long n = *(long *)(param_2 + 0x10);
    sk_x_002298d4(n);
    if (n != 0) {
        word_t *p = (word_t *)(param_2 + 0x38);
        do {
            word_t a = p[-2], owned = p[-1], b = p[0], c = p[1], d = p[2], e = p[3], f = p[4], g = p[5];
            char tag = (char)p[6];
            sk_x_002298d4((byte)p[-3]);
            sk_x_0036b270(owned);
            sk_x_00458eec(d, e, f, g, tag);
            sk_x_001b9084(param_1, a, owned);
            sk_x_003a25d4(owned);
            sk_x_002298d4(b >> 0xe);
            sk_x_002298d4(c >> 0xe);
            if (tag == -1) {
                sk_x_00229a3c(0);
            } else {
                sk_x_00229a3c(1);
                sk_x_0042d720(param_1);
                sk_x_00458f88(d, e, f, g, tag);
            }
            p += 10; n--;
        } while (n != 0);
    }
}

/* FUN_004588cc @ 0x004588cc   (est. sk_box_retain)
 * Ghidra: void FUN_004588cc(ulong param_1, undefined8 param_2, undefined8 param_3, ulong param_4)
 * Retains the boxed object: dispatch on the tag bits (param_4>>1 & 3); case 1
 * retains the param_4 object, case 3 is a no-op (shared sentinel), otherwise
 * retains param_1.
 * Confidence: high */
static void sk_box_retain_004588cc(word_t param_1, word_t param_2, word_t param_3,
                                   word_t param_4)
{
    switch ((param_4 >> 1) & 3) {
    case 1: sk_x_0036b270(param_4 & 0xffffffffffffff9); break;
    case 3: return;
    }
    sk_x_0036b270(param_1 & 0xfffffffffffffff);
}

/* FUN_00458940 @ 0x00458940   (est. sk_box_release)
 * Ghidra: void FUN_00458940(ulong param_1, undefined8 param_2, undefined8 param_3, ulong param_4)
 * Releases the boxed object: dispatch on the tag bits; case 1 releases the
 * param_4 object, case 3 is a no-op, otherwise releases param_1.
 * Confidence: high */
static void sk_box_release_00458940(word_t param_1, word_t param_2, word_t param_3,
                                    word_t param_4)
{
    switch ((param_4 >> 1) & 3) {
    case 1: sk_x_0036b118(param_1 & 0xfffffffffffffff);
            param_1 = param_4 & 0xffffffffffffff9; break;
    case 3: return;
    default: param_1 &= 0xfffffffffffffff; break;
    }
    sk_x_0036b118(param_1);
}

/* FUN_004589bc @ 0x004589bc   (est. sk_box_release_meta)
 * Ghidra: long FUN_004589bc(long param_1)
 * Releases the metadata word at param_1+0x18 and returns param_1.
 * Confidence: high */
static long sk_box_release_meta_004589bc(long param_1)
{
    sk_x_0036b118(*(word_t *)(param_1 + 0x18));
    return param_1;
}

/* FUN_004589e8 @ 0x004589e8   (est. sk_script_wit_apply)
 * Ghidra: void FUN_004589e8(undefined8 param_1, undefined8 param_2)
 * Applies the 0045a6f4 witness closure (param_2, param_1).
 * Confidence: low (thunk) */
static void sk_script_wit_apply_004589e8(word_t param_1, word_t param_2)
{
    sk_x_0045a6f4(param_2, param_1);
}

/* FUN_004589f8 @ 0x004589f8   (est. sk_script_wit_run)
 * Ghidra: undefined8 FUN_004589f8(undefined8 param_1)
 * Runs the 0045a980 witness closure and returns param_1.
 * Confidence: low (thunk) */
static word_t sk_script_wit_run_004589f8(word_t param_1)
{
    sk_x_0045a980();
    return param_1;
}

/* FUN_00458a20 @ 0x00458a20   (est. sk_script_wit_apply2)
 * Ghidra: void FUN_00458a20(undefined8 param_1, undefined8 param_2)
 * Applies the 0045eb6c witness closure. Confidence: low (thunk) */
static void sk_script_wit_apply2_00458a20(word_t param_1, word_t param_2)
{
    sk_x_0045eb6c(param_2, param_1);
}

/* FUN_00458a30 @ 0x00458a30   (est. sk_script_wit_run2)
 * Ghidra: undefined8 FUN_00458a30(undefined8 param_1)
 * Runs the 0045eb38 witness closure and returns param_1. Confidence: low */
static word_t sk_script_wit_run2_00458a30(word_t param_1)
{
    sk_x_0045eb38();
    return param_1;
}

/* FUN_00458a58 @ 0x00458a58   (est. sk_script_wit_apply3)
 * Ghidra: void FUN_00458a58(undefined8 param_1, undefined8 param_2)
 * Applies the 0045c2a8 witness closure. Confidence: low (thunk) */
static void sk_script_wit_apply3_00458a58(word_t param_1, word_t param_2)
{
    sk_x_0045c2a8(param_2, param_1);
}

/* FUN_00458a68 @ 0x00458a68   (est. sk_script_wit_run3)
 * Ghidra: undefined8 FUN_00458a68(undefined8 param_1)
 * Runs the 0045c258 witness closure and returns param_1. Confidence: low */
static word_t sk_script_wit_run3_00458a68(word_t param_1)
{
    sk_x_0045c258();
    return param_1;
}

/* FUN_00458a90 @ 0x00458a90   (est. sk_script_wit_apply4)
 * Ghidra: void FUN_00458a90(undefined8 param_1, undefined8 param_2)
 * Applies the 0045df90 witness closure. Confidence: low (thunk) */
static void sk_script_wit_apply4_00458a90(word_t param_1, word_t param_2)
{
    sk_x_0045df90(param_2, param_1);
}

/* FUN_00458aa0 @ 0x00458aa0   (est. sk_script_wit_run4)
 * Ghidra: undefined8 FUN_00458aa0(undefined8 param_1)
 * Runs the 0045df3c witness closure and returns param_1. Confidence: low */
static word_t sk_script_wit_run4_00458aa0(word_t param_1)
{
    sk_x_0045df3c();
    return param_1;
}

/* FUN_00458ac8 @ 0x00458ac8   (est. sk_box_sizeof)
 * Ghidra: long FUN_00458ac8(ulong param_1)
 * Computes the end of a tagged object: if the low bit is set, dereferences the
 * boxed pointer (param_1 & ~1) and returns its +8 length word; otherwise the
 * inline +8 field. Used for boxing-alloc sizing.
 * Confidence: high */
static long sk_box_sizeof_00458ac8(word_t param_1)
{
    if ((param_1 & 1) != 0) param_1 = *(word_t *)(param_1 & 0xfffffffffffffffe);
    return (long)(param_1 + 8) + (long)*(int *)(param_1 + 8);
}

/* FUN_00458af8 @ 0x00458af8   (est. sk_block_count)
 * Ghidra: uint FUN_00458af8(int *param_1)
 * Returns the block range count for a table record: default = *param_1 + 0xe,
 * but when the flag byte at +0x98 < 0xe0 uses the nibble (*param_1[0x26]>>4).
 * Confidence: medium */
static uint sk_block_count_00458af8(int *param_1)
{
    uint c = (uint)*param_1 + 0xe;
    if (*(byte *)(param_1 + 0x26) < 0xe0) c = (uint)(*(byte *)(param_1 + 0x26) >> 4);
    return c;
}

/* FUN_00458b14 @ 0x00458b14   (est. sk_block_clear_flags)
 * Ghidra: void FUN_00458b14(long param_1)
 * Clears the low nibble of the flag byte at param_1+0x98.
 * Confidence: high */
static void sk_block_clear_flags_00458b14(long param_1)
{
    *(byte *)(param_1 + 0x98) &= 0xf;
}

/* FUN_00458b24 @ 0x00458b24   (est. sk_box_release_if_owned)
 * Ghidra: void FUN_00458b24(ulong param_1)
 * Releases the boxed object unless it is the shared immutable sentinel
 * (0xf000000000000007-masked all-ones).
 * Confidence: high */
static void sk_box_release_if_owned_00458b24(word_t param_1)
{
    if (((param_1 ^ 0xffffffffffffffff) & 0xf000000000000007) == 0) return;
    sk_x_0036b118(param_1 & 0xfffffffffffffff);
}

/* FUN_00458b6c @ 0x00458b6c   (est. sk_block_flag)
 * Ghidra: undefined1 FUN_00458b6c(long param_1)
 * Returns the flag byte at param_1+0x98.
 * Confidence: high */
static byte sk_block_flag_00458b6c(long param_1)
{
    return *(byte *)(param_1 + 0x98);
}

/* FUN_00458b94 @ 0x00458b94   (est. sk_retain_if_tag1)
 * Ghidra: void FUN_00458b94(undefined8 param_1, undefined8 param_2, ...)
 * Retains param_2 when the tag param_5 == 1, else no-op.
 * Confidence: high */
static void sk_retain_if_tag1_00458b94(word_t param_1, word_t param_2, word_t param_3,
                                      word_t param_4, char param_5)
{
    if (param_5 == 1) sk_x_0036b270(param_2);
}

/* FUN_00458bac @ 0x00458bac   (est. sk_release_if_tag1)
 * Ghidra: void FUN_00458bac(undefined8 param_1, undefined8 param_2, ...)
 * Releases param_2 when the tag param_5 == 1, else no-op.
 * Confidence: high */
static void sk_release_if_tag1_00458bac(word_t param_1, word_t param_2, word_t param_3,
                                        word_t param_4, char param_5)
{
    if (param_5 == 1) sk_x_003a25d4(param_2);
}

/* FUN_00458bc4 @ 0x00458bc4   (est. sk_obj_emit_meta)
 * Ghidra: void FUN_00458bc4(void)
 * Emits the object metadata: 003504d0/00355968 build the type, 00002534 the
 * name, then 003509c8 runs the closure.
 * Confidence: low (closure-fragment heavy) */
static void sk_obj_emit_meta_00458bc4(void)
{
    cl4_pair_t au;
    word_t m;
    sk_x_003504d0();
    sk_x_00355968();
    m = sk_x_00002534();
    sk_x_003509c8(m, m, m, m);
}

/* FUN_00458c18 @ 0x00458c18   (est. sk_obj_wit_apply)
 * Ghidra: void FUN_00458c18(undefined8 param_1, undefined8 param_2)
 * Applies the 0045b824 witness closure. Confidence: low (thunk) */
static void sk_obj_wit_apply_00458c18(word_t param_1, word_t param_2)
{
    sk_x_0045b824(param_2, param_1);
}

/* FUN_00458c28 @ 0x00458c28   (est. sk_obj_wit_run)
 * Ghidra: undefined8 FUN_00458c28(undefined8 param_1)
 * Runs the 0045b7f4 witness closure and returns param_1. Confidence: low */
static word_t sk_obj_wit_run_00458c28(word_t param_1)
{
    sk_x_0045b7f4();
    return param_1;
}

/* FUN_00458c50 @ 0x00458c50   (est. sk_obj_wit_apply2)
 * Ghidra: void FUN_00458c50(undefined8 param_1, undefined8 param_2)
 * Applies the 0045bbb4 witness closure. Confidence: low (thunk) */
static void sk_obj_wit_apply2_00458c50(word_t param_1, word_t param_2)
{
    sk_x_0045bbb4(param_2, param_1);
}

/* FUN_00458c60 @ 0x00458c60   (est. sk_obj_wit_run2)
 * Ghidra: undefined8 FUN_00458c60(undefined8 param_1)
 * Runs the 0045bb84 witness closure and returns param_1. Confidence: low */
static word_t sk_obj_wit_run2_00458c60(word_t param_1)
{
    sk_x_0045bb84();
    return param_1;
}

/* FUN_00458c88 @ 0x00458c88   (est. sk_obj_wit_apply3)
 * Ghidra: void FUN_00458c88(undefined8 param_1, undefined8 param_2)
 * Applies the 0045be8c witness closure. Confidence: low (thunk) */
static void sk_obj_wit_apply3_00458c88(word_t param_1, word_t param_2)
{
    sk_x_0045be8c(param_2, param_1);
}

/* FUN_00458c98 @ 0x00458c98   (est. sk_obj_wit_apply4)
 * Ghidra: void FUN_00458c98(undefined8 param_1, undefined8 param_2)
 * Applies the 0045c61c witness closure. Confidence: low (thunk) */
static void sk_obj_wit_apply4_00458c98(word_t param_1, word_t param_2)
{
    sk_x_0045c61c(param_2, param_1);
}

/* FUN_00458cb8 @ 0x00458cb8   (est. sk_block_range_count)
 * Ghidra: uint FUN_00458cb8(int *param_1)
 * Returns the block range count for a record: default = *param_1 + 4, but when
 * the +0x68 word's low 3 bits are clear uses those bits (param_1[0x1a] & 7).
 * Confidence: medium */
static uint sk_block_range_count_00458cb8(int *param_1)
{
    uint c = (uint)*param_1 + 4;
    if ((param_1[0x1a] & 4U) == 0) c = param_1[0x1a] & 7;
    return c;
}

/* FUN_00458cd4 @ 0x00458cd4   (est. sk_block_clear_count_flags)
 * Ghidra: void FUN_00458cd4(long param_1)
 * Clears the low 3 bits of the range-count word at param_1+0x68.
 * Confidence: high */
static void sk_block_clear_count_flags_00458cd4(long param_1)
{
    *(word_t *)(param_1 + 0x68) &= 0xfffffffffffffff8;
}

/* FUN_00458d04 @ 0x00458d04   (est. sk_tag_read_45)
 * Ghidra: ulong FUN_00458d04(long param_1)
 * Reads the 0x3d-bit tag from the record at param_1+0x170.
 * Confidence: high */
static word_t sk_tag_read_45_00458d04(long param_1)
{
    return *(word_t *)(param_1 + 0x170) >> 0x3d;
}

/* FUN_00458d10 @ 0x00458d10   (est. sk_tag_clear_45)
 * Ghidra: void FUN_00458d10(long param_1)
 * Clears the 0x3d-bit tag at param_1+0x170.
 * Confidence: high */
static void sk_tag_clear_45_00458d10(long param_1)
{
    *(word_t *)(param_1 + 0x170) &= 0x1fffffffffffffff;
}

/* FUN_00458d30 @ 0x00458d30   (est. sk_script_wit_apply5)
 * Ghidra: void FUN_00458d30(undefined8 param_1, undefined8 param_2)
 * Applies the 0045d2e4 witness closure. Confidence: low (thunk) */
static void sk_script_wit_apply5_00458d30(word_t param_1, word_t param_2)
{
    sk_x_0045d2e4(param_2, param_1);
}

/* FUN_00458d40 @ 0x00458d40   (est. sk_script_wit_run5)
 * Ghidra: undefined8 FUN_00458d40(undefined8 param_1)
 * Runs the 0045d028 witness closure and returns param_1. Confidence: low */
static word_t sk_script_wit_run5_00458d40(word_t param_1)
{
    sk_x_0045d028();
    return param_1;
}
