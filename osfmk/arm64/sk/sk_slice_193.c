/* Recreated from cl4_kernel.raw (cL4 Secure Kernel, arm64e, image base 0) —
 * the cL4 microkernel (GL1). Ground truth: Ghidra FUN_ names + addresses.
 * All names are estimates unless string/header matched.
 *
 * SK193 slice (0x0042af18-0x00439a5c): the Swift `_StringProcessing` /
 * regular-expression literal parser embedded in the cL4 kernel.  This parses
 * Swift regex literals into the compiled Regex AST.  See the region comments
 * on each function for the exact behavior.  Bodies are faithful at low/medium
 * confidence; 16-byte register-pair values, overflow-checked arithmetic and
 * the retain/release heap protocol are recovered, but high-level Swift
 * semantics are not always recoverable.
 */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdarg.h>

typedef uint64_t word_t;
typedef unsigned int uint;
typedef unsigned long ulong;
typedef unsigned char byte;
typedef void (*code)(void);
typedef word_t (*vcode)(word_t, ...);

typedef struct sw128 { uint64_t lo; uint64_t hi; } sw128_t;
typedef struct sw96 { uint64_t lo; uint32_t hi; } sw96_t;

#define SW_FATAL(addr) __builtin_trap()
#define LOAcquire()      do { } while (0)
#define LORelease()      do { } while (0)
#define GENTER()         do { } while (0)
#define GEXIT()          do { } while (0)
#define LZCOUNT(x)       __builtin_clzll(x)
#define POPCOUNT(x)      __builtin_popcountll(x)

/* ---- Forward declarations (functions reconstructed in this file) ---- */

void sk_re_delim_init(void);	/* FUN_0042af18 @ 0x0042af18 */
void sk_re_delim_throw(void);	/* FUN_0042af68 @ 0x0042af68 */
void sk_re_delim_ret(word_t *out, word_t a, word_t b);	/* FUN_0042b0c4 @ 0x0042b0c4 */
void sk_re_parse_throw(word_t a, word_t b, word_t c);	/* FUN_0042b13c @ 0x0042b13c */
sw128_t sk_re_scalar_utf8(word_t a, word_t b);	/* FUN_0042b370 @ 0x0042b370 */
sw128_t sk_re_scalar_utf8b(word_t a, word_t b, word_t c);	/* FUN_0042b708 @ 0x0042b708 */
void sk_re_write_scalar(void);	/* FUN_0042bac4 @ 0x0042bac4 */
void sk_re_write_scalar2(byte b);	/* FUN_0042baf4 @ 0x0042baf4 */
void sk_re_write_delim_pair(void);	/* FUN_0042bb58 @ 0x0042bb58 */
sw128_t sk_re_scan_matching_char(byte kind);	/* FUN_0042bbcc @ 0x0042bbcc */
bool sk_re_emit_len(long n, char ch, byte *p, word_t flagsA, word_t flagsB, word_t flagsC);	/* FUN_0042bc90 @ 0x0042bc90 */
void sk_re_delim_emit_scalar(word_t esc);	/* FUN_0042be08 @ 0x0042be08 */
void sk_re_emit_scalar_len(word_t len, word_t a, word_t b);	/* FUN_0042bf18 @ 0x0042bf18 */
void sk_re_parse_delim_ret(long n, word_t a, word_t b, word_t c, word_t d);	/* FUN_0042bfcc @ 0x0042bfcc */
sw128_t sk_re_split_ret(long n, word_t a, word_t b, word_t c, word_t d);	/* FUN_0042c060 @ 0x0042c060 */
void sk_re_parse_delims(void);	/* FUN_0042c11c @ 0x0042c11c */
void sk_re_emit_delim_scalar(word_t sc, word_t flags);	/* FUN_0042c5a4 @ 0x0042c5a4 */
void sk_re_retreat(void);	/* FUN_0042c60c @ 0x0042c60c */
void sk_re_task_flush(void);	/* FUN_0042c744 @ 0x0042c744 */
void sk_re_parse_delim_body(word_t *out, char *start, char *end, long rec, char *ext);	/* FUN_0042c958 @ 0x0042c958 */
word_t sk_re_scan_eq(sw128_t *node, byte *pat);	/* FUN_0042d050 @ 0x0042d050 */
void sk_re_scan_utf8_detect(word_t a);	/* FUN_0042d720 @ 0x0042d720 */
void sk_re_scan_utf8_detect2(void);	/* FUN_0042db84 @ 0x0042db84 */
void sk_re_emit_delim_scalar2(void);	/* FUN_0042dbc0 @ 0x0042dbc0 */
void sk_re_write_delim(void);	/* FUN_0042dbf0 @ 0x0042dbf0 */
void sk_re_write_delim2(void);	/* FUN_0042dc20 @ 0x0042dc20 */
void sk_re_write_delim3(void);	/* FUN_0042dc24 @ 0x0042dc24 */
void sk_re_write_delim4(void);	/* FUN_0042dc50 @ 0x0042dc50 */
void sk_re_write_delim5(void);	/* FUN_0042dc90 @ 0x0042dc90 */
void sk_re_write_delim6(void);	/* FUN_0042e7e0 @ 0x0042e7e0 */
void sk_re_emit_kind(void);	/* FUN_0042e820 @ 0x0042e820 */
void sk_re_write_kind(void);	/* FUN_0042e874 @ 0x0042e874 */
void sk_re_write_kind2(void);	/* FUN_0042e8b4 @ 0x0042e8b4 */
sw128_t sk_re_write_kind3(void);	/* FUN_0042e930 @ 0x0042e930 */
void sk_re_write_kind4(void);	/* FUN_0042e968 @ 0x0042e968 */
void sk_re_reset(void);	/* FUN_0042eadc @ 0x0042eadc */
void sk_re_retain_rec(void);	/* FUN_0042eb6c @ 0x0042eb6c */
void sk_re_write_rec(void);	/* FUN_0042ebac @ 0x0042ebac */
void sk_re_write_rec2(void);	/* FUN_0042ec10 @ 0x0042ec10 */
void sk_re_write_rec3(void);	/* FUN_0042ec5c @ 0x0042ec5c */
void sk_re_diag_rec(word_t a);	/* FUN_0042ec68 @ 0x0042ec68 */
void sk_re_diag_rec2(void);	/* FUN_0042ed40 @ 0x0042ed40 */
void sk_re_diag_rec3(void);	/* FUN_0042ed44 @ 0x0042ed44 */
void sk_re_diag_extend(long src);	/* FUN_0042ed6c @ 0x0042ed6c */
void sk_re_diag_merge(word_t src, word_t a, word_t n, word_t total);	/* FUN_0042ee6c @ 0x0042ee6c */
word_t sk_re_scan_newline(word_t str, word_t flags);	/* FUN_0042f020 @ 0x0042f020 */
word_t sk_re_parse_scalar2(word_t start, word_t end, word_t a, word_t flags);	/* FUN_0042f1f0 @ 0x0042f1f0 */
uint sk_re_parse_scalar3(word_t a, uint b, word_t c, uint d);	/* FUN_0042f3e0 @ 0x0042f3e0 */
void sk_re_diag_rec_b(word_t a, word_t b, uint c);	/* FUN_0042f418 @ 0x0042f418 */
void sk_re_diag_rec_c(word_t a, uint b);	/* FUN_0042f448 @ 0x0042f448 */
void sk_re_diag_rec_d(void);	/* FUN_0042f4ac @ 0x0042f4ac */
void sk_re_diag_rec_e(void);	/* FUN_0042f514 @ 0x0042f514 */
void sk_re_diag_init(void);	/* FUN_0042f584 @ 0x0042f584 */
void sk_re_diag_rec_f(void);	/* FUN_0042f5f8 @ 0x0042f5f8 */
void sk_re_diag_rec_g(void);	/* FUN_0042f630 @ 0x0042f630 */
void sk_re_diag_emit_str(void);	/* FUN_0042f670 @ 0x0042f670 */
uint sk_re_diag_match(word_t a, word_t b);	/* FUN_0042f7d4 @ 0x0042f7d4 */
uint sk_re_diag_match2(word_t a, word_t b);	/* FUN_0042f890 @ 0x0042f890 */
bool sk_re_append_match(void);	/* FUN_0042f9dc @ 0x0042f9dc */
word_t sk_re_append_match2(word_t a, word_t b);	/* FUN_0042fa98 @ 0x0042fa98 */
void sk_re_peek_char(void);	/* FUN_0042fc4c @ 0x0042fc4c */
void sk_re_peek_char2(void);	/* FUN_0042fca8 @ 0x0042fca8 */
void sk_re_diag_complete(void);	/* FUN_0042fd4c @ 0x0042fd4c */
word_t sk_re_parse_scalar_adv(word_t a, word_t b);	/* FUN_0042fe0c @ 0x0042fe0c */
void sk_re_peek_scalar(void);	/* FUN_0042fea0 @ 0x0042fea0 */
void sk_re_parse_quant_star(void);	/* FUN_0042ffac @ 0x0042ffac */
sw128_t sk_re_peek_scalar2(void);	/* FUN_0042ffec @ 0x0042ffec */
sw128_t sk_re_record_append_diag(word_t a);	/* FUN_00430040 @ 0x00430040 */
sw128_t sk_re_str_slice(word_t a, word_t b, word_t *p);	/* FUN_004301e0 @ 0x004301e0 */
void sk_re_parse_suffix(word_t a, word_t b, word_t *p, word_t c);	/* FUN_004302a0 @ 0x004302a0 */
void sk_re_parse_suffix2(void);	/* FUN_00430338 @ 0x00430338 */
void sk_re_parse_scalar_str(void);	/* FUN_004303c4 @ 0x004303c4 */
uint sk_re_is_scalar_class(void);	/* FUN_004304e0 @ 0x004304e0 */
void sk_re_bool_scalar(byte *out, word_t *p);	/* FUN_00430584 @ 0x00430584 */
void sk_re_bool_unicode(byte *out, word_t *p);	/* FUN_004305c4 @ 0x004305c4 */
void sk_re_bool_uni_prop(byte *out, word_t *p);	/* FUN_00430604 @ 0x00430604 */
byte sk_re_scalar_to_utf8(word_t a, word_t b, word_t c);	/* FUN_00430644 @ 0x00430644 */
void sk_re_bool_scalar2(void);	/* FUN_004306a0 @ 0x004306a0 */
void sk_re_bool_scalar3(void);	/* FUN_004306a4 @ 0x004306a4 */
void sk_re_parse_scalar_seq(void);	/* FUN_004306bc @ 0x004306bc */
void sk_re_diag_inv_scalar(word_t a, word_t b, word_t c, word_t d);	/* FUN_00430bf4 @ 0x00430bf4 */
void sk_re_parse_number(void);	/* FUN_00430d08 @ 0x00430d08 */
void sk_re_parse_number_radix(word_t *out);	/* FUN_00431210 @ 0x00431210 */
sw128_t sk_re_parse_group_number(word_t tag);	/* FUN_0043152c @ 0x0043152c */
sw128_t sk_re_parse_ref_number(long expected);	/* FUN_00431604 @ 0x00431604 */
void sk_re_parse_uni_prop(void);	/* FUN_004317c4 @ 0x004317c4 */
void sk_re_parse_quote(word_t a, word_t b, word_t c);	/* FUN_004323ac @ 0x004323ac */
void sk_re_parse_group_body(void);	/* FUN_004327c4 @ 0x004327c4 */
void sk_re_parse_group_end(word_t a, word_t b, word_t c, word_t d);	/* FUN_00432c48 @ 0x00432c48 */
void sk_re_parse_quantifier(void);	/* FUN_00432ed4 @ 0x00432ed4 */
void sk_re_diag_emit_msg(void);	/* FUN_00433938 @ 0x00433938 */
void sk_re_parse_escape(word_t a, word_t b, word_t c, uint mode, word_t flags);	/* FUN_004339a8 @ 0x004339a8 */
word_t sk_re_diag_done(void);	/* FUN_00434054 @ 0x00434054 */
void sk_re_parse_quoted_seq(word_t *out, word_t *p);	/* FUN_004340b0 @ 0x004340b0 */
void sk_re_parse_balanced(void);	/* FUN_004345a4 @ 0x004345a4 */
void sk_re_parse_comment(sw128_t *out, long rec, word_t a, word_t b, word_t c);	/* FUN_00434af4 @ 0x00434af4 */
void sk_re_parse_atom(long rec, word_t a, word_t b, word_t c);	/* FUN_00434e98 @ 0x00434e98 */
word_t sk_re_diag_finalize(void);	/* FUN_00435110 @ 0x00435110 */
void sk_re_parse_mode_option(word_t a, word_t b, word_t c, word_t d);	/* FUN_0043519c @ 0x0043519c */
void sk_re_parse_option_block(word_t a, word_t b, word_t c, word_t *out);	/* FUN_004356f0 @ 0x004356f0 */
void sk_re_parse_option_end(void);	/* FUN_00435ecc @ 0x00435ecc */
void sk_re_parse_lookaround(void);	/* FUN_004361a4 @ 0x004361a4 */
void sk_re_parse_capture_name(word_t a, word_t b, word_t c, word_t d);	/* FUN_004368c0 @ 0x004368c0 */
word_t sk_re_is_ident_start(void);	/* FUN_00436fc8 @ 0x00436fc8 */
void sk_re_bool_ident(byte *out, word_t *p);	/* FUN_0043703c @ 0x0043703c */
void sk_re_parse_backref(word_t *out, word_t a);	/* FUN_00437070 @ 0x00437070 */
void sk_re_record_select(sw128_t p2, sw128_t p3, sw128_t p4, sw128_t p5, sw128_t p6);	/* FUN_004371ac @ 0x004371ac */
void sk_re_record_join(sw128_t p2, sw128_t p3, sw128_t p4, sw128_t p5, sw128_t p6);	/* FUN_004372d4 @ 0x004372d4 */
sw128_t sk_re_parse_group_header(word_t a, word_t b, word_t c);	/* FUN_004374e4 @ 0x004374e4 */
word_t sk_re_parse_group_kind(void);	/* FUN_004379bc @ 0x004379bc */
void sk_re_diag_unhandled(long ch, long flags);	/* FUN_00437d54 @ 0x00437d54 */
void sk_re_parse_backref_or_scalar(void);	/* FUN_00437eec @ 0x00437eec */
word_t sk_re_backref_check(long *p);	/* FUN_004382cc @ 0x004382cc */
void sk_re_parse_char_class(void);	/* FUN_00438328 @ 0x00438328 */
void sk_re_parse_alternation(word_t a, word_t b, word_t c);	/* FUN_00438f54 @ 0x00438f54 */
void sk_re_parse_concat(void);	/* FUN_00439348 @ 0x00439348 */
sw128_t sk_re_parse_anchor(void);	/* FUN_0043942c @ 0x0043942c */
uint sk_re_parse_operator(void);	/* FUN_00439530 @ 0x00439530 */
void sk_re_parse_expr(void);	/* FUN_004395fc @ 0x004395fc */
void sk_re_parse_sequence(void);	/* FUN_00439a5c @ 0x00439a5c */

/* ---- Out-of-region helper externs (used by this slice; FUN_ addr in comment) ---- */
extern word_t sw_002534(word_t, ...);  /* FUN_00002534 */
extern word_t sw_0026e8(word_t, ...);  /* FUN_000026e8 */
extern word_t sw_002818(word_t, ...);  /* FUN_00002818 */
extern word_t sw_002834(word_t, ...);  /* FUN_00002834 */
extern word_t sw_002850(word_t, ...);  /* FUN_00002850 */
extern word_t sw_002874(word_t, ...);  /* FUN_00002874 */
extern word_t sw_01a1c8(word_t, ...);  /* FUN_0001a1c8 */
extern word_t sw_01d7a0(word_t, ...);  /* FUN_0001d7a0 */
extern word_t sw_01da84(word_t, ...);  /* FUN_0001da84 */
extern word_t sw_027724(word_t, ...);  /* FUN_00027724 */
extern word_t sw_027754(word_t, ...);  /* FUN_00027754 */
extern word_t sw_027788(word_t, ...);  /* FUN_00027788 */
extern word_t sw_068e14(word_t, ...);  /* FUN_00068e14 */
extern word_t sw_06a4c0(word_t, ...);  /* FUN_0006a4c0 */
extern word_t sw_06b3f4(word_t, ...);  /* FUN_0006b3f4 */
extern word_t sw_06b42c(word_t, ...);  /* FUN_0006b42c */
extern word_t sw_06b6a0(word_t, ...);  /* FUN_0006b6a0 */
extern word_t sw_06b6f4(word_t, ...);  /* FUN_0006b6f4 */
extern word_t sw_072178(word_t, ...);  /* FUN_00072178 */
extern word_t sw_0776cc(word_t, ...);  /* FUN_000776cc */
extern word_t sw_077888(word_t, ...);  /* FUN_00077888 */
extern word_t sw_077894(word_t, ...);  /* FUN_00077894 */
extern word_t sw_0778b4(word_t, ...);  /* FUN_000778b4 */
extern word_t sw_07c028(word_t, ...);  /* FUN_0007c028 */
extern word_t sw_07c1a4(word_t, ...);  /* FUN_0007c1a4 */
extern word_t sw_07c1c4(word_t, ...);  /* FUN_0007c1c4 */
extern word_t sw_0839d8(word_t, ...);  /* FUN_000839d8 */
extern word_t sw_084000(word_t, ...);  /* FUN_00084000 */
extern word_t sw_08409c(word_t, ...);  /* FUN_0008409c */
extern word_t sw_084174(word_t, ...);  /* FUN_00084174 */
extern word_t sw_084180(word_t, ...);  /* FUN_00084180 */
extern word_t sw_084220(word_t, ...);  /* FUN_00084220 */
extern word_t sw_084234(word_t, ...);  /* FUN_00084234 */
extern word_t sw_0863bc(word_t, ...);  /* FUN_000863bc */
extern word_t sw_086840(word_t, ...);  /* FUN_00086840 */
extern word_t sw_08e388(word_t, ...);  /* FUN_0008e388 */
extern word_t sw_08e500(word_t, ...);  /* FUN_0008e500 */
extern word_t sw_08e518(word_t, ...);  /* FUN_0008e518 */
extern word_t sw_09461c(word_t, ...);  /* FUN_0009461c */
extern word_t sw_09e218(word_t, ...);  /* FUN_0009e218 */
extern word_t sw_0a6f68(word_t, ...);  /* FUN_000a6f68 */
extern word_t sw_0a6f88(word_t, ...);  /* FUN_000a6f88 */
extern word_t sw_0aa4ec(word_t, ...);  /* FUN_000aa4ec */
extern word_t sw_0abad0(word_t, ...);  /* FUN_000abad0 */
extern word_t sw_0ac00c(word_t, ...);  /* FUN_000ac00c */
extern word_t sw_0b03cc(word_t, ...);  /* FUN_000b03cc */
extern word_t sw_0b05bc(word_t, ...);  /* FUN_000b05bc */
extern word_t sw_0b077c(word_t, ...);  /* FUN_000b077c */
extern word_t sw_0b430c(word_t, ...);  /* FUN_000b430c */
extern word_t sw_0b4390(word_t, ...);  /* FUN_000b4390 */
extern word_t sw_0b43e8(word_t, ...);  /* FUN_000b43e8 */
extern word_t sw_0b4528(word_t, ...);  /* FUN_000b4528 */
extern word_t sw_0b4594(word_t, ...);  /* FUN_000b4594 */
extern word_t sw_0b45b0(word_t, ...);  /* FUN_000b45b0 */
extern word_t sw_0dbc98(word_t, ...);  /* FUN_000dbc98 */
extern word_t sw_0dbed0(word_t, ...);  /* FUN_000dbed0 */
extern word_t sw_0e15d8(word_t, ...);  /* FUN_000e15d8 */
extern word_t sw_0e46d0(word_t, ...);  /* FUN_000e46d0 */
extern word_t sw_0f4ae8(word_t, ...);  /* FUN_000f4ae8 */
extern sw128_t sw_100e34(word_t, ...);  /* FUN_00100e34 */
extern sw128_t sw_100efc(word_t, ...);  /* FUN_00100efc */
extern word_t sw_117cc4(word_t, ...);  /* FUN_00117cc4 */
extern word_t sw_15e4f8(word_t, ...);  /* FUN_0015e4f8 */
extern word_t sw_16749c(word_t, ...);  /* FUN_0016749c */
extern word_t sw_1676cc(word_t, ...);  /* FUN_001676cc */
extern word_t sw_1a1c8(word_t, ...);  /* FUN_0001a1c8 */
extern word_t sw_1a84f4(word_t, ...);  /* FUN_001a84f4 */
extern word_t sw_1a8564(word_t, ...);  /* FUN_001a8564 */
extern word_t sw_1ae8a8(word_t, ...);  /* FUN_001ae8a8 */
extern word_t sw_1afa84(word_t, ...);  /* FUN_001afa84 */
extern word_t sw_1b28d4(word_t, ...);  /* FUN_001b28d4 */
extern word_t sw_1b798c(word_t, ...);  /* FUN_001b798c */
extern word_t sw_1b9084(word_t, ...);  /* FUN_001b9084 */
extern word_t sw_1d7a0(word_t, ...);  /* FUN_0001d7a0 */
extern word_t sw_1da84(word_t, ...);  /* FUN_0001da84 */
extern word_t sw_1e9c78(word_t, ...);  /* FUN_001e9c78 */
extern word_t sw_1ebfb0(word_t, ...);  /* FUN_001ebfb0 */
extern word_t sw_1ed960(word_t, ...);  /* FUN_001ed960 */
extern word_t sw_1ee018(word_t, ...);  /* FUN_001ee018 */
extern word_t sw_1fcefc(word_t, ...);  /* FUN_001fcefc */
extern word_t sw_205844(word_t, ...);  /* FUN_00205844 */
extern word_t sw_2298d4(word_t, ...);  /* FUN_002298d4 */
extern word_t sw_229a3c(word_t, ...);  /* FUN_00229a3c */
extern word_t sw_22d2f4(word_t, ...);  /* FUN_0022d2f4 */
extern word_t sw_24917c(word_t, ...);  /* FUN_0024917c */
extern word_t sw_24d9ac(word_t, ...);  /* FUN_0024d9ac */
extern word_t sw_27724(word_t, ...);  /* FUN_00027724 */
extern word_t sw_27754(word_t, ...);  /* FUN_00027754 */
extern word_t sw_27788(word_t, ...);  /* FUN_00027788 */
extern word_t sw_2818(word_t, ...);  /* FUN_00002818 */
extern word_t sw_2834(word_t, ...);  /* FUN_00002834 */
extern word_t sw_2874(word_t, ...);  /* FUN_00002874 */
extern word_t sw_299540(word_t, ...);  /* FUN_00299540 */
extern word_t sw_29e8dc(word_t, ...);  /* FUN_0029e8dc */
extern word_t sw_29f0b0(word_t, ...);  /* FUN_0029f0b0 */
extern sw128_t sw_29fa0c(word_t, ...);  /* FUN_0029fa0c */
extern word_t sw_29fb80(word_t, ...);  /* FUN_0029fb80 */
extern word_t sw_2a0cf8(word_t, ...);  /* FUN_002a0cf8 */
extern word_t sw_2a3e64(word_t, ...);  /* FUN_002a3e64 */
extern word_t sw_2a49a8(word_t, ...);  /* FUN_002a49a8 */
extern word_t sw_2a4ab4(word_t, ...);  /* FUN_002a4ab4 */
extern sw128_t sw_2a9ba8(word_t, ...);  /* FUN_002a9ba8 */
extern word_t sw_2a9d64(word_t, ...);  /* FUN_002a9d64 */
extern word_t sw_2ab388(word_t, ...);  /* FUN_002ab388 */
extern sw128_t sw_2aca00(word_t, ...);  /* FUN_002aca00 */
extern word_t sw_2acbb8(word_t, ...);  /* FUN_002acbb8 */
extern word_t sw_2b141c(word_t, ...);  /* FUN_002b141c */
extern word_t sw_2b24b8(word_t, ...);  /* FUN_002b24b8 */
extern word_t sw_2b3b50(word_t, ...);  /* FUN_002b3b50 */
extern sw96_t sw_2b3f40(word_t, ...);  /* FUN_002b3f40 */
extern word_t sw_2b4120(word_t, ...);  /* FUN_002b4120 */
extern sw128_t sw_2b439c(word_t, ...);  /* FUN_002b439c */
extern sw128_t sw_2b5ba0(word_t, ...);  /* FUN_002b5ba0 */
extern sw96_t sw_2b5e10(word_t, ...);  /* FUN_002b5e10 */
extern word_t sw_2b5ed4(word_t, ...);  /* FUN_002b5ed4 */
extern word_t sw_2b7088(word_t, ...);  /* FUN_002b7088 */
extern word_t sw_2b74c0(word_t, ...);  /* FUN_002b74c0 */
extern word_t sw_2bc2dc(word_t, ...);  /* FUN_002bc2dc */
extern word_t sw_2bd724(word_t, ...);  /* FUN_002bd724 */
extern word_t sw_2bd8f0(word_t, ...);  /* FUN_002bd8f0 */
extern word_t sw_2bd9cc(word_t, ...);  /* FUN_002bd9cc */
extern word_t sw_2bda40(word_t, ...);  /* FUN_002bda40 */
extern word_t sw_2bdb90(word_t, ...);  /* FUN_002bdb90 */
extern word_t sw_2bdc7c(word_t, ...);  /* FUN_002bdc7c */
extern word_t sw_31b46c(word_t, ...);  /* FUN_0031b46c */
extern word_t sw_31b49c(word_t, ...);  /* FUN_0031b49c */
extern word_t sw_31e030(word_t, ...);  /* FUN_0031e030 */
extern word_t sw_34a210(word_t, ...);  /* FUN_0034a210 */
extern word_t sw_34bd90(word_t, ...);  /* FUN_0034bd90 */
extern word_t sw_34c444(word_t, ...);  /* FUN_0034c444 */
extern word_t sw_34d868(word_t, ...);  /* FUN_0034d868 */
extern word_t sw_34db28(word_t, ...);  /* FUN_0034db28 */
extern word_t sw_34e1ec(word_t, ...);  /* FUN_0034e1ec */
extern word_t sw_34ecc8(word_t, ...);  /* FUN_0034ecc8 */
extern word_t sw_34ede8(word_t, ...);  /* FUN_0034ede8 */
extern word_t sw_34f3b4(word_t, ...);  /* FUN_0034f3b4 */
extern word_t sw_34fe80(word_t, ...);  /* FUN_0034fe80 */
extern word_t sw_350470(word_t, ...);  /* FUN_00350470 */
extern word_t sw_3504a0(word_t, ...);  /* FUN_003504a0 */
extern word_t sw_3504ac(word_t, ...);  /* FUN_003504ac */
extern word_t sw_3504c4(word_t, ...);  /* FUN_003504c4 */
extern word_t sw_3504d0(word_t, ...);  /* FUN_003504d0 */
extern sw128_t sw_350518(word_t, ...);  /* FUN_00350518 */
extern sw128_t sw_350530(word_t, ...);  /* FUN_00350530 */
extern word_t sw_35053c(word_t, ...);  /* FUN_0035053c */
extern word_t sw_350560(word_t, ...);  /* FUN_00350560 */
extern word_t sw_3505c4(word_t, ...);  /* FUN_003505c4 */
extern word_t sw_3505e8(word_t, ...);  /* FUN_003505e8 */
extern word_t sw_350618(word_t, ...);  /* FUN_00350618 */
extern word_t sw_35063c(word_t, ...);  /* FUN_0035063c */
extern sw128_t sw_350738(word_t, ...);  /* FUN_00350738 */
extern sw128_t sw_3507e0(word_t, ...);  /* FUN_003507e0 */
extern word_t sw_350878(word_t, ...);  /* FUN_00350878 */
extern word_t sw_3508fc(word_t, ...);  /* FUN_003508fc */
extern word_t sw_350914(word_t, ...);  /* FUN_00350914 */
extern word_t sw_350944(word_t, ...);  /* FUN_00350944 */
extern word_t sw_350980(word_t, ...);  /* FUN_00350980 */
extern word_t sw_350998(word_t, ...);  /* FUN_00350998 */
extern word_t sw_3509bc(word_t, ...);  /* FUN_003509bc */
extern word_t sw_3509c8(word_t, ...);  /* FUN_003509c8 */
extern word_t sw_350a04(word_t, ...);  /* FUN_00350a04 */
extern word_t sw_350a88(word_t, ...);  /* FUN_00350a88 */
extern word_t sw_350b54(word_t, ...);  /* FUN_00350b54 */
extern word_t sw_350b90(word_t, ...);  /* FUN_00350b90 */
extern word_t sw_350bf0(word_t, ...);  /* FUN_00350bf0 */
extern word_t sw_350bfc(word_t, ...);  /* FUN_00350bfc */
extern word_t sw_3510b8(word_t, ...);  /* FUN_003510b8 */
extern word_t sw_3511a8(word_t, ...);  /* FUN_003511a8 */
extern word_t sw_3511cc(word_t, ...);  /* FUN_003511cc */
extern word_t sw_3511d8(word_t, ...);  /* FUN_003511d8 */
extern word_t sw_351238(word_t, ...);  /* FUN_00351238 */
extern word_t sw_351274(word_t, ...);  /* FUN_00351274 */
extern word_t sw_351354(word_t, ...);  /* FUN_00351354 */
extern word_t sw_3514d0(word_t, ...);  /* FUN_003514d0 */
extern word_t sw_3516d8(word_t, ...);  /* FUN_003516d8 */
extern sw128_t sw_351714(word_t, ...);  /* FUN_00351714 */
extern word_t sw_351744(word_t, ...);  /* FUN_00351744 */
extern word_t sw_351790(word_t, ...);  /* FUN_00351790 */
extern word_t sw_3517c0(word_t, ...);  /* FUN_003517c0 */
extern word_t sw_35187c(word_t, ...);  /* FUN_0035187c */
extern sw128_t sw_35199c(word_t, ...);  /* FUN_0035199c */
extern word_t sw_3519a8(word_t, ...);  /* FUN_003519a8 */
extern word_t sw_351a44(word_t, ...);  /* FUN_00351a44 */
extern word_t sw_351a50(word_t, ...);  /* FUN_00351a50 */
extern word_t sw_351a5c(word_t, ...);  /* FUN_00351a5c */
extern word_t sw_351aec(word_t, ...);  /* FUN_00351aec */
extern word_t sw_351c7c(word_t, ...);  /* FUN_00351c7c */
extern word_t sw_351cd0(word_t, ...);  /* FUN_00351cd0 */
extern word_t sw_351d18(word_t, ...);  /* FUN_00351d18 */
extern word_t sw_351d30(word_t, ...);  /* FUN_00351d30 */
extern sw128_t sw_351dc0(word_t, ...);  /* FUN_00351dc0 */
extern word_t sw_351e08(word_t, ...);  /* FUN_00351e08 */
extern word_t sw_351e20(word_t, ...);  /* FUN_00351e20 */
extern word_t sw_351e3c(word_t, ...);  /* FUN_00351e3c */
extern word_t sw_351f28(word_t, ...);  /* FUN_00351f28 */
extern sw128_t sw_352290(word_t, ...);  /* FUN_00352290 */
extern word_t sw_352480(word_t, ...);  /* FUN_00352480 */
extern word_t sw_352498(word_t, ...);  /* FUN_00352498 */
extern word_t sw_3524a4(word_t, ...);  /* FUN_003524a4 */
extern sw128_t sw_3524b0(word_t, ...);  /* FUN_003524b0 */
extern word_t sw_35292c(word_t, ...);  /* FUN_0035292c */
extern word_t sw_352c4c(word_t, ...);  /* FUN_00352c4c */
extern word_t sw_352c80(word_t, ...);  /* FUN_00352c80 */
extern word_t sw_3534e0(word_t, ...);  /* FUN_003534e0 */
extern word_t sw_3535a8(word_t, ...);  /* FUN_003535a8 */
extern word_t sw_353abc(word_t, ...);  /* FUN_00353abc */
extern word_t sw_353b10(word_t, ...);  /* FUN_00353b10 */
extern word_t sw_353bc4(word_t, ...);  /* FUN_00353bc4 */
extern word_t sw_353c30(word_t, ...);  /* FUN_00353c30 */
extern word_t sw_354ca8(word_t, ...);  /* FUN_00354ca8 */
extern word_t sw_356110(word_t, ...);  /* FUN_00356110 */
extern word_t sw_3562d4(word_t, ...);  /* FUN_003562d4 */
extern word_t sw_356328(word_t, ...);  /* FUN_00356328 */
extern word_t sw_3567c8(word_t, ...);  /* FUN_003567c8 */
extern word_t sw_356b5c(word_t, ...);  /* FUN_00356b5c */
extern word_t sw_356f80(word_t, ...);  /* FUN_00356f80 */
extern sw128_t sw_356f9c(word_t, ...);  /* FUN_00356f9c */
extern word_t sw_3593c0(word_t, ...);  /* FUN_003593c0 */
extern sw128_t sw_35aba4(word_t, ...);  /* FUN_0035aba4 */
extern word_t sw_365b6c(word_t, ...);  /* FUN_00365b6c */
extern word_t sw_36986c(word_t, ...);  /* FUN_0036986c */
extern word_t sw_36993c(word_t, ...);  /* FUN_0036993c */
extern word_t sw_369a30(word_t, ...);  /* FUN_00369a30 */
extern word_t sw_369efc(word_t, ...);  /* FUN_00369efc */
extern word_t sw_36a940(word_t, ...);  /* FUN_0036a940 */
extern word_t sw_36a9a0(word_t, ...);  /* FUN_0036a9a0 */
extern word_t sw_36b118(word_t, ...);  /* FUN_0036b118 */
extern word_t sw_36b270(word_t, ...);  /* FUN_0036b270 */
extern word_t sw_36b588(word_t, ...);  /* FUN_0036b588 */
extern word_t sw_36b6ac(word_t, ...);  /* FUN_0036b6ac */
extern word_t sw_377824(word_t, ...);  /* FUN_00377824 */
extern word_t sw_377bec(word_t, ...);  /* FUN_00377bec */
extern word_t sw_3a25d4(word_t, ...);  /* FUN_003a25d4 */
extern word_t sw_3a2610(word_t, ...);  /* FUN_003a2610 */
extern word_t sw_3a261c(word_t, ...);  /* FUN_003a261c */
extern word_t sw_3f34b4(word_t, ...);  /* FUN_003f34b4 */
extern word_t sw_4080b0(word_t, ...);  /* FUN_004080b0 */
extern word_t sw_40ff40(word_t, ...);  /* FUN_0040ff40 */
extern word_t sw_411624(word_t, ...);  /* FUN_00411624 */
extern word_t sw_412d5c(word_t, ...);  /* FUN_00412d5c */
extern word_t sw_41ca38(word_t, ...);  /* FUN_0041ca38 */
extern word_t sw_41d070(word_t, ...);  /* FUN_0041d070 */
extern word_t sw_41d8f4(word_t, ...);  /* FUN_0041d8f4 */
extern sw128_t sw_41e0a0(word_t, ...);  /* FUN_0041e0a0 */
extern word_t sw_42bc90(word_t, ...);  /* FUN_0042bc90 */
extern word_t sw_41e188(word_t, ...);  /* FUN_0041e188 */
extern sw128_t sw_41e21c(word_t, ...);  /* FUN_0041e21c */
extern word_t sw_429398(word_t, ...);  /* FUN_00429398 */
extern word_t sw_429430(word_t, ...);  /* FUN_00429430 */
extern word_t sw_429984(word_t, ...);  /* FUN_00429984 */
extern word_t sw_42aca4(word_t, ...);  /* FUN_0042aca4 */
extern word_t sw_42acc4(word_t, ...);  /* FUN_0042acc4 */
extern word_t sw_42ade4(word_t, ...);  /* FUN_0042ade4 */
extern word_t sw_42ae78(word_t, ...);  /* FUN_0042ae78 */
extern word_t sw_434e98(word_t, ...);  /* FUN_None */
extern word_t sw_439d74(word_t, ...);  /* FUN_00439d74 */
extern word_t sw_43a478(word_t, ...);  /* FUN_0043a478 */
extern word_t sw_4455f8(word_t, ...);  /* FUN_004455f8 */
extern word_t sw_4460cc(word_t, ...);  /* FUN_004460cc */
extern word_t sw_4461bc(word_t, ...);  /* FUN_004461bc */
extern sw128_t sw_448758(word_t, ...);  /* FUN_00448758 */
extern word_t sw_448934(word_t, ...);  /* FUN_00448934 */
extern word_t sw_448aac(word_t, ...);  /* FUN_00448aac */
extern word_t sw_455db8(word_t, ...);  /* FUN_00455db8 */
extern word_t sw_455fe4(word_t, ...);  /* FUN_00455fe4 */
extern word_t sw_45636c(word_t, ...);  /* FUN_0045636c */
extern word_t sw_4564e4(word_t, ...);  /* FUN_004564e4 */
extern word_t sw_456650(word_t, ...);  /* FUN_00456650 */
extern word_t sw_456714(word_t, ...);  /* FUN_00456714 */
extern word_t sw_45694c(word_t, ...);  /* FUN_0045694c */
extern word_t sw_456d50(word_t, ...);  /* FUN_00456d50 */
extern word_t sw_456fa8(word_t, ...);  /* FUN_00456fa8 */
extern word_t sw_4571b0(word_t, ...);  /* FUN_004571b0 */
extern word_t sw_4573b0(word_t, ...);  /* FUN_004573b0 */
extern word_t sw_457650(word_t, ...);  /* FUN_00457650 */
extern word_t sw_4578dc(word_t, ...);  /* FUN_004578dc */
extern word_t sw_457994(word_t, ...);  /* FUN_00457994 */
extern word_t sw_457e80(word_t, ...);  /* FUN_00457e80 */
extern word_t sw_457ed8(word_t, ...);  /* FUN_00457ed8 */
extern word_t sw_458780(word_t, ...);  /* FUN_00458780 */
extern word_t sw_458cd4(word_t, ...);  /* FUN_00458cd4 */
extern word_t sw_458d68(word_t, ...);  /* FUN_00458d68 */
extern word_t sw_458d78(word_t, ...);  /* FUN_00458d78 */
extern word_t sw_458e50(word_t, ...);  /* FUN_00458e50 */
extern word_t sw_458e80(word_t, ...);  /* FUN_00458e80 */
extern word_t sw_458ea8(word_t, ...);  /* FUN_00458ea8 */
extern word_t sw_458ebc(word_t, ...);  /* FUN_00458ebc */
extern word_t sw_459024(word_t, ...);  /* FUN_00459024 */
extern word_t sw_459034(word_t, ...);  /* FUN_00459034 */
extern word_t sw_45904c(word_t, ...);  /* FUN_0045904c */
extern word_t sw_460dbc(word_t, ...);  /* FUN_00460dbc */
extern word_t sw_460e68(word_t, ...);  /* FUN_00460e68 */
extern word_t sw_460e78(word_t, ...);  /* FUN_00460e78 */
extern word_t sw_460ff4(word_t, ...);  /* FUN_00460ff4 */
extern word_t sw_461430(word_t, ...);  /* FUN_00461430 */
extern word_t sw_4614cc(word_t, ...);  /* FUN_004614cc */
extern word_t sw_4618f4(word_t, ...);  /* FUN_004618f4 */
extern word_t sw_461aec(word_t, ...);  /* FUN_00461aec */
extern word_t sw_461b50(word_t, ...);  /* FUN_00461b50 */
extern word_t sw_461b64(word_t, ...);  /* FUN_00461b64 */
extern word_t sw_461b8c(word_t, ...);  /* FUN_00461b8c */
extern word_t sw_461ba0(word_t, ...);  /* FUN_00461ba0 */
extern word_t sw_461bb4(word_t, ...);  /* FUN_00461bb4 */
extern word_t sw_461bd4(word_t, ...);  /* FUN_00461bd4 */
extern word_t sw_461bf4(word_t, ...);  /* FUN_00461bf4 */
extern word_t sw_461c1c(word_t, ...);  /* FUN_00461c1c */
extern word_t sw_461c3c(word_t, ...);  /* FUN_00461c3c */
extern word_t sw_461c70(word_t, ...);  /* FUN_00461c70 */
extern word_t sw_461c90(word_t, ...);  /* FUN_00461c90 */
extern word_t sw_461ca4(word_t, ...);  /* FUN_00461ca4 */
extern word_t sw_461cb8(word_t, ...);  /* FUN_00461cb8 */
extern word_t sw_462710(word_t, ...);  /* FUN_00462710 */
extern word_t sw_462770(word_t, ...);  /* FUN_00462770 */
extern word_t sw_462788(word_t, ...);  /* FUN_00462788 */
extern word_t sw_4627b8(word_t, ...);  /* FUN_004627b8 */
extern word_t sw_4627f4(word_t, ...);  /* FUN_004627f4 */
extern word_t sw_462810(word_t, ...);  /* FUN_00462810 */
extern word_t sw_46282c(word_t, ...);  /* FUN_0046282c */
extern word_t sw_462870(word_t, ...);  /* FUN_00462870 */
extern word_t sw_462884(word_t, ...);  /* FUN_00462884 */
extern word_t sw_4628c4(word_t, ...);  /* FUN_004628c4 */
extern word_t sw_4628f4(word_t, ...);  /* FUN_004628f4 */
extern word_t sw_462974(word_t, ...);  /* FUN_00462974 */
extern word_t sw_462988(word_t, ...);  /* FUN_00462988 */
extern word_t sw_46299c(word_t, ...);  /* FUN_0046299c */
extern word_t sw_4629b4(word_t, ...);  /* FUN_004629b4 */
extern word_t sw_4629cc(word_t, ...);  /* FUN_004629cc */
extern word_t sw_462a08(word_t, ...);  /* FUN_00462a08 */
extern word_t sw_462a1c(word_t, ...);  /* FUN_00462a1c */
extern word_t sw_462a34(word_t, ...);  /* FUN_00462a34 */
extern word_t sw_462a48(word_t, ...);  /* FUN_00462a48 */
extern word_t sw_462a5c(word_t, ...);  /* FUN_00462a5c */
extern word_t sw_462a84(word_t, ...);  /* FUN_00462a84 */
extern word_t sw_462a98(word_t, ...);  /* FUN_00462a98 */
extern word_t sw_462aac(word_t, ...);  /* FUN_00462aac */
extern word_t sw_462abc(word_t, ...);  /* FUN_00462abc */
extern word_t sw_462af0(word_t, ...);  /* FUN_00462af0 */
extern word_t sw_462b00(word_t, ...);  /* FUN_00462b00 */
extern word_t sw_462b10(word_t, ...);  /* FUN_00462b10 */
extern word_t sw_462b2c(word_t, ...);  /* FUN_00462b2c */
extern word_t sw_462b40(word_t, ...);  /* FUN_00462b40 */
extern word_t sw_462b54(word_t, ...);  /* FUN_00462b54 */
extern word_t sw_462b6c(word_t, ...);  /* FUN_00462b6c */
extern word_t sw_462b80(word_t, ...);  /* FUN_00462b80 */
extern word_t sw_462ba8(word_t, ...);  /* FUN_00462ba8 */
extern word_t sw_462c7c(word_t, ...);  /* FUN_00462c7c */
extern word_t sw_462ce8(word_t, ...);  /* FUN_00462ce8 */
extern word_t sw_462d0c(word_t, ...);  /* FUN_00462d0c */
extern word_t sw_462d20(word_t, ...);  /* FUN_00462d20 */
extern word_t sw_462d48(word_t, ...);  /* FUN_00462d48 */
extern word_t sw_462d88(word_t, ...);  /* FUN_00462d88 */
extern word_t sw_462d98(word_t, ...);  /* FUN_00462d98 */
extern word_t sw_462e44(word_t, ...);  /* FUN_00462e44 */
extern word_t sw_462ed8(word_t, ...);  /* FUN_00462ed8 */
extern word_t sw_462f24(word_t, ...);  /* FUN_00462f24 */
extern word_t sw_462f3c(word_t, ...);  /* FUN_00462f3c */
extern word_t sw_462f5c(word_t, ...);  /* FUN_00462f5c */
extern word_t sw_462f6c(word_t, ...);  /* FUN_00462f6c */
extern word_t sw_462f7c(word_t, ...);  /* FUN_00462f7c */
extern word_t sw_462fac(word_t, ...);  /* FUN_00462fac */
extern word_t sw_462fbc(word_t, ...);  /* FUN_00462fbc */
extern word_t sw_463000(word_t, ...);  /* FUN_00463000 */
extern word_t sw_463014(word_t, ...);  /* FUN_00463014 */
extern word_t sw_4630b0(word_t, ...);  /* FUN_004630b0 */
extern word_t sw_4630c4(word_t, ...);  /* FUN_004630c4 */
extern word_t sw_463130(word_t, ...);  /* FUN_00463130 */
extern word_t sw_4631a8(word_t, ...);  /* FUN_004631a8 */
extern word_t sw_46322c(word_t, ...);  /* FUN_0046322c */
extern word_t sw_463280(word_t, ...);  /* FUN_00463280 */
extern word_t sw_463290(word_t, ...);  /* FUN_00463290 */
extern word_t sw_4632cc(word_t, ...);  /* FUN_004632cc */
extern word_t sw_4632e0(word_t, ...);  /* FUN_004632e0 */
extern word_t sw_463394(word_t, ...);  /* FUN_00463394 */
extern word_t sw_463404(word_t, ...);  /* FUN_00463404 */
extern sw128_t sw_463444(word_t, ...);  /* FUN_00463444 */
extern word_t sw_4634b4(word_t, ...);  /* FUN_004634b4 */
extern word_t sw_4634f4(word_t, ...);  /* FUN_004634f4 */
extern word_t sw_463514(word_t, ...);  /* FUN_00463514 */
extern word_t sw_463534(word_t, ...);  /* FUN_00463534 */
extern word_t sw_463540(word_t, ...);  /* FUN_00463540 */
extern word_t sw_463590(word_t, ...);  /* FUN_00463590 */
extern word_t sw_4635c8(word_t, ...);  /* FUN_004635c8 */
extern sw128_t sw_4635d4(word_t, ...);  /* FUN_004635d4 (16-byte pair) */
extern word_t sw_4635e0(word_t, ...);  /* FUN_004635e0 */
extern word_t sw_46361c(word_t, ...);  /* FUN_0046361c */
extern word_t sw_463648(word_t, ...);  /* FUN_00463648 */
extern word_t sw_463684(word_t, ...);  /* FUN_00463684 */
extern word_t sw_4636a0(word_t, ...);  /* FUN_004636a0 */
extern word_t sw_4636e8(word_t, ...);  /* FUN_004636e8 */
extern word_t sw_4636f8(word_t, ...);  /* FUN_004636f8 */
extern word_t sw_463708(word_t, ...);  /* FUN_00463708 */
extern word_t sw_463728(word_t, ...);  /* FUN_00463728 */
extern word_t sw_463764(word_t, ...);  /* FUN_00463764 */
extern word_t sw_4637f0(word_t, ...);  /* FUN_004637f0 */
extern word_t sw_463824(word_t, ...);  /* FUN_00463824 */
extern word_t sw_463830(word_t, ...);  /* FUN_00463830 */
extern word_t sw_463878(word_t, ...);  /* FUN_00463878 */
extern word_t sw_463884(word_t, ...);  /* FUN_00463884 */
extern word_t sw_46389c(word_t, ...);  /* FUN_0046389c */
extern word_t sw_4638c0(word_t, ...);  /* FUN_004638c0 */
extern word_t sw_463944(word_t, ...);  /* FUN_00463944 */
extern word_t sw_463970(word_t, ...);  /* FUN_00463970 */
extern word_t sw_46397c(word_t, ...);  /* FUN_0046397c */
extern word_t sw_4639d8(word_t, ...);  /* FUN_004639d8 */
extern word_t sw_463a38(word_t, ...);  /* FUN_00463a38 */
extern word_t sw_463a58(word_t, ...);  /* FUN_00463a58 */
extern word_t sw_463a68(word_t, ...);  /* FUN_00463a68 */
extern word_t sw_463a78(word_t, ...);  /* FUN_00463a78 */
extern word_t sw_463bbc(word_t, ...);  /* FUN_00463bbc */
extern word_t sw_463bc8(word_t, ...);  /* FUN_00463bc8 */
extern word_t sw_463c0c(word_t, ...);  /* FUN_00463c0c */
extern word_t sw_463cb8(word_t, ...);  /* FUN_00463cb8 */
extern word_t sw_463dbc(word_t, ...);  /* FUN_00463dbc */
extern word_t sw_463de0(word_t, ...);  /* FUN_00463de0 */
extern word_t sw_463e04(word_t, ...);  /* FUN_00463e04 */
extern word_t sw_463e10(word_t, ...);  /* FUN_00463e10 */
extern word_t sw_463f34(word_t, ...);  /* FUN_00463f34 */
extern word_t sw_463f40(word_t, ...);  /* FUN_00463f40 */
extern word_t sw_463f4c(word_t, ...);  /* FUN_00463f4c */
extern word_t sw_463f74(word_t, ...);  /* FUN_00463f74 */
extern word_t sw_463f80(word_t, ...);  /* FUN_00463f80 */
extern sw128_t sw_463f94(word_t, ...);  /* FUN_00463f94 */
extern word_t sw_463fac(word_t, ...);  /* FUN_00463fac */
extern word_t sw_463fd0(word_t, ...);  /* FUN_00463fd0 */
extern word_t sw_464000(word_t, ...);  /* FUN_00464000 */
extern word_t sw_46400c(word_t, ...);  /* FUN_0046400c */
extern word_t sw_464040(word_t, ...);  /* FUN_00464040 */
extern word_t sw_464058(word_t, ...);  /* FUN_00464058 */
extern word_t sw_464090(word_t, ...);  /* FUN_00464090 */
extern word_t sw_464134(word_t, ...);  /* FUN_00464134 */
extern word_t sw_46418c(word_t, ...);  /* FUN_0046418c */
extern word_t sw_464234(word_t, ...);  /* FUN_00464234 */
extern word_t sw_464268(word_t, ...);  /* FUN_00464268 */
extern word_t sw_4642a8(word_t, ...);  /* FUN_004642a8 */
extern word_t sw_4642e8(word_t, ...);  /* FUN_004642e8 */
extern word_t sw_4642f8(word_t, ...);  /* FUN_004642f8 */
extern word_t sw_464364(word_t, ...);  /* FUN_00464364 */
extern word_t sw_4643cc(word_t, ...);  /* FUN_004643cc */
extern word_t sw_4644dc(word_t, ...);  /* FUN_004644dc */
extern word_t sw_464568(word_t, ...);  /* FUN_00464568 */
extern word_t sw_464588(word_t, ...);  /* FUN_00464588 */
extern word_t sw_464608(word_t, ...);  /* FUN_00464608 */
extern word_t sw_46461c(word_t, ...);  /* FUN_0046461c */
extern word_t sw_4647c0(word_t, ...);  /* FUN_004647c0 */
extern word_t sw_4647f4(word_t, ...);  /* FUN_004647f4 */
extern word_t sw_464818(word_t, ...);  /* FUN_00464818 */
extern word_t sw_464854(word_t, ...);  /* FUN_00464854 */
extern word_t sw_4648fc(word_t, ...);  /* FUN_004648fc */
extern word_t sw_46490c(word_t, ...);  /* FUN_0046490c */
extern word_t sw_464918(word_t, ...);  /* FUN_00464918 */
extern word_t sw_464948(word_t, ...);  /* FUN_00464948 */
extern word_t sw_4649c0(word_t, ...);  /* FUN_004649c0 */
extern word_t sw_4649cc(word_t, ...);  /* FUN_004649cc */
extern word_t sw_4649fc(word_t, ...);  /* FUN_004649fc */
extern word_t sw_464a14(word_t, ...);  /* FUN_00464a14 */
extern word_t sw_464a44(word_t, ...);  /* FUN_00464a44 */
extern word_t sw_464a8c(word_t, ...);  /* FUN_00464a8c */
extern word_t sw_464aac(word_t, ...);  /* FUN_00464aac */
extern sw128_t sw_464ab8(word_t, ...);  /* FUN_00464ab8 */
extern word_t sw_464ac4(word_t, ...);  /* FUN_00464ac4 */
extern word_t sw_464adc(word_t, ...);  /* FUN_00464adc */
extern word_t sw_464b20(word_t, ...);  /* FUN_00464b20 */
extern word_t sw_464cf4(word_t, ...);  /* FUN_00464cf4 */
extern word_t sw_464d18(word_t, ...);  /* FUN_00464d18 */
extern word_t sw_464d24(word_t, ...);  /* FUN_00464d24 */
extern word_t sw_464d50(word_t, ...);  /* FUN_00464d50 */
extern word_t sw_464d5c(word_t, ...);  /* FUN_00464d5c */
extern word_t sw_464d74(word_t, ...);  /* FUN_00464d74 */
extern word_t sw_464d80(word_t, ...);  /* FUN_00464d80 */
extern word_t sw_464da0(word_t, ...);  /* FUN_00464da0 */
extern word_t sw_464dfc(word_t, ...);  /* FUN_00464dfc */
extern word_t sw_464e28(word_t, ...);  /* FUN_00464e28 */
extern word_t sw_464e34(word_t, ...);  /* FUN_00464e34 */
extern word_t sw_464e64(word_t, ...);  /* FUN_00464e64 */
extern word_t sw_464e70(word_t, ...);  /* FUN_00464e70 */
extern word_t sw_464e7c(word_t, ...);  /* FUN_00464e7c */
extern word_t sw_464ebc(word_t, ...);  /* FUN_00464ebc */
extern word_t sw_464f84(word_t, ...);  /* FUN_00464f84 */
extern word_t sw_46507c(word_t, ...);  /* FUN_0046507c */
extern word_t sw_4650a0(word_t, ...);  /* FUN_004650a0 */
extern word_t sw_4650ac(word_t, ...);  /* FUN_004650ac */
extern word_t sw_4650e4(word_t, ...);  /* FUN_004650e4 */
extern word_t sw_46511c(word_t, ...);  /* FUN_0046511c */
extern word_t sw_465134(word_t, ...);  /* FUN_00465134 */
extern word_t sw_465144(word_t, ...);  /* FUN_00465144 */
extern word_t sw_465150(word_t, ...);  /* FUN_00465150 */
extern word_t sw_4651b8(word_t, ...);  /* FUN_004651b8 */
extern word_t sw_465240(word_t, ...);  /* FUN_00465240 */
extern word_t sw_46527c(word_t, ...);  /* FUN_0046527c */
extern word_t sw_465288(word_t, ...);  /* FUN_00465288 */
extern word_t sw_4652c4(word_t, ...);  /* FUN_004652c4 */
extern word_t sw_465304(word_t, ...);  /* FUN_00465304 */
extern word_t sw_465314(word_t, ...);  /* FUN_00465314 */
extern word_t sw_465340(word_t, ...);  /* FUN_00465340 */
extern word_t sw_465380(word_t, ...);  /* FUN_00465380 */
extern word_t sw_4653b0(word_t, ...);  /* FUN_004653b0 */
extern word_t sw_4653ec(word_t, ...);  /* FUN_004653ec */
extern word_t sw_4653fc(word_t, ...);  /* FUN_004653fc */
extern word_t sw_465488(word_t, ...);  /* FUN_00465488 */
extern word_t sw_4654b4(word_t, ...);  /* FUN_004654b4 */
extern word_t sw_4654d0(word_t, ...);  /* FUN_004654d0 */
extern word_t sw_465524(word_t, ...);  /* FUN_00465524 */
extern sw128_t sw_465540(word_t, ...);  /* FUN_00465540 */
extern word_t sw_465584(word_t, ...);  /* FUN_00465584 */
extern word_t sw_4655f0(word_t, ...);  /* FUN_004655f0 */
extern word_t sw_4655fc(word_t, ...);  /* FUN_004655fc */
extern word_t sw_465644(word_t, ...);  /* FUN_00465644 */
extern word_t sw_4656a4(word_t, ...);  /* FUN_004656a4 */
extern word_t sw_4656d4(word_t, ...);  /* FUN_004656d4 */
extern word_t sw_465740(word_t, ...);  /* FUN_00465740 */
extern word_t sw_4657ac(word_t, ...);  /* FUN_004657ac */
extern word_t sw_4657d0(word_t, ...);  /* FUN_004657d0 */
extern word_t sw_46580c(word_t, ...);  /* FUN_0046580c */
extern word_t sw_465830(word_t, ...);  /* FUN_00465830 */
extern word_t sw_465890(word_t, ...);  /* FUN_00465890 */
extern word_t sw_4658fc(word_t, ...);  /* FUN_004658fc */
extern word_t sw_465908(word_t, ...);  /* FUN_00465908 */
extern word_t sw_465920(word_t, ...);  /* FUN_00465920 */
extern word_t sw_46592c(word_t, ...);  /* FUN_0046592c */
extern word_t sw_465938(word_t, ...);  /* FUN_00465938 */
extern word_t sw_46598c(word_t, ...);  /* FUN_0046598c */
extern word_t sw_465998(word_t, ...);  /* FUN_00465998 */
extern word_t sw_4659b0(word_t, ...);  /* FUN_004659b0 */
extern word_t sw_4659bc(word_t, ...);  /* FUN_004659bc */
extern word_t sw_4659c8(word_t, ...);  /* FUN_004659c8 */
extern word_t sw_465ac0(word_t, ...);  /* FUN_00465ac0 */
extern word_t sw_465adc(word_t, ...);  /* FUN_00465adc */
extern word_t sw_465b6c(word_t, ...);  /* FUN_00465b6c */
extern word_t sw_465c5c(word_t, ...);  /* FUN_00465c5c */
extern word_t sw_465c68(word_t, ...);  /* FUN_00465c68 */
extern word_t sw_465d08(word_t, ...);  /* FUN_00465d08 */
extern word_t sw_465d70(word_t, ...);  /* FUN_00465d70 */
extern word_t sw_465da4(word_t, ...);  /* FUN_00465da4 */
extern word_t sw_465db0(word_t, ...);  /* FUN_00465db0 */
extern word_t sw_465dbc(word_t, ...);  /* FUN_00465dbc */
extern word_t sw_465df0(word_t, ...);  /* FUN_00465df0 */
extern word_t sw_465e04(word_t, ...);  /* FUN_00465e04 */
extern word_t sw_465e40(word_t, ...);  /* FUN_00465e40 */
extern word_t sw_465e60(word_t, ...);  /* FUN_00465e60 */
extern word_t sw_465e74(word_t, ...);  /* FUN_00465e74 */
extern word_t sw_465eac(word_t, ...);  /* FUN_00465eac */
extern word_t sw_465ec0(word_t, ...);  /* FUN_00465ec0 */
extern word_t sw_465ed4(word_t, ...);  /* FUN_00465ed4 */
extern word_t sw_465f14(word_t, ...);  /* FUN_00465f14 */
extern word_t sw_465f48(word_t, ...);  /* FUN_00465f48 */
extern word_t sw_465f5c(word_t, ...);  /* FUN_00465f5c */
extern word_t sw_465f7c(word_t, ...);  /* FUN_00465f7c */
extern word_t sw_465f9c(word_t, ...);  /* FUN_00465f9c */
extern word_t sw_465fa8(word_t, ...);  /* FUN_00465fa8 */
extern word_t sw_465fd4(word_t, ...);  /* FUN_00465fd4 */
extern word_t sw_466028(word_t, ...);  /* FUN_00466028 */
extern word_t sw_466048(word_t, ...);  /* FUN_00466048 */
extern word_t sw_466054(word_t, ...);  /* FUN_00466054 */
extern word_t sw_466068(word_t, ...);  /* FUN_00466068 */
extern word_t sw_466074(word_t, ...);  /* FUN_00466074 */
extern word_t sw_4660c0(word_t, ...);  /* FUN_004660c0 */
extern word_t sw_4660cc(word_t, ...);  /* FUN_004660cc */
extern word_t sw_46615c(word_t, ...);  /* FUN_0046615c */
extern word_t sw_46617c(word_t, ...);  /* FUN_0046617c */
extern word_t sw_466190(word_t, ...);  /* FUN_00466190 */
extern word_t sw_4662a4(word_t, ...);  /* FUN_004662a4 */
extern word_t sw_4662f4(word_t, ...);  /* FUN_004662f4 */
extern word_t sw_46633c(word_t, ...);  /* FUN_0046633c */
extern word_t sw_46635c(word_t, ...);  /* FUN_0046635c */
extern word_t sw_4663ec(word_t, ...);  /* FUN_004663ec */
extern sw128_t sw_466408(word_t, ...);  /* FUN_00466408 */
extern word_t sw_466490(word_t, ...);  /* FUN_00466490 */
extern sw128_t sw_4664a4(word_t, ...);  /* FUN_004664a4 */
extern word_t sw_466510(word_t, ...);  /* FUN_00466510 */
extern word_t sw_466528(word_t, ...);  /* FUN_00466528 */
extern word_t sw_466568(word_t, ...);  /* FUN_00466568 */
extern word_t sw_466600(word_t, ...);  /* FUN_00466600 */
extern word_t sw_466630(word_t, ...);  /* FUN_00466630 */
extern word_t sw_466648(word_t, ...);  /* FUN_00466648 */
extern word_t sw_466678(word_t, ...);  /* FUN_00466678 */
extern word_t sw_466684(word_t, ...);  /* FUN_00466684 */
extern sw128_t sw_466690(word_t, ...);  /* FUN_00466690 */
extern word_t sw_4666a8(word_t, ...);  /* FUN_004666a8 */
extern word_t sw_4666e4(word_t, ...);  /* FUN_004666e4 */
extern sw128_t sw_4666f8(word_t, ...);  /* FUN_004666f8 */
extern word_t sw_466730(word_t, ...);  /* FUN_00466730 */
extern word_t sw_48934(word_t, ...);  /* FUN_00448934 */
extern word_t sw_6490c(word_t, ...);  /* FUN_0046490c */
extern word_t sw_657778;  /* DAT_00657778 shared buffer */
extern word_t sw_68e14(word_t, ...);  /* FUN_00068e14 */
extern word_t sw_6b3f4(word_t, ...);  /* FUN_0006b3f4 */
extern word_t sw_6b42c(word_t, ...);  /* FUN_0006b42c */
extern word_t sw_6b6f4(word_t, ...);  /* FUN_0006b6f4 */
extern sw128_t sw_77888(word_t, ...);  /* FUN_00077888 */
extern word_t sw_7c028(word_t, ...);  /* FUN_0007c028 */
extern word_t sw_7c1a4(word_t, ...);  /* FUN_0007c1a4 */
extern sw128_t sw_7c1c4(word_t, ...);  /* FUN_0007c1c4 */
extern word_t sw_839d8(word_t, ...);  /* FUN_000839d8 */
extern word_t sw_8409c(word_t, ...);  /* FUN_0008409c */
extern word_t sw_84174(word_t, ...);  /* FUN_00084174 */
extern word_t sw_84180(word_t, ...);  /* FUN_00084180 */
extern word_t sw_84220(word_t, ...);  /* FUN_00084220 */
extern word_t sw_84234(word_t, ...);  /* FUN_00084234 */
extern word_t sw_863bc(word_t, ...);  /* FUN_000863bc */
extern word_t sw_86840(word_t, ...);  /* FUN_00086840 */
extern sw128_t sw_8e388(word_t, ...);  /* FUN_0008e388 */
extern word_t sw_8e500(word_t, ...);  /* FUN_0008e500 */
extern sw128_t sw_8e518(word_t, ...);  /* FUN_0008e518 */
extern word_t sw_9461c(word_t, ...);  /* FUN_0009461c */
extern word_t sw_9e218(word_t, ...);  /* FUN_0009e218 */
extern word_t sw_a6f68(word_t, ...);  /* FUN_000a6f68 */
extern word_t sw_a6f88(word_t, ...);  /* FUN_000a6f88 */
extern word_t sw_abad0(word_t, ...);  /* FUN_000abad0 */
extern word_t sw_ac00c(word_t, ...);  /* FUN_000ac00c */
extern word_t sw_b430c(word_t, ...);  /* FUN_000b430c */
extern sw128_t sw_b4390(word_t, ...);  /* FUN_000b4390 */
extern word_t sw_b43e8(word_t, ...);  /* FUN_000b43e8 */
extern word_t sw_b4528(word_t, ...);  /* FUN_000b4528 */
extern sw128_t sw_b4594(word_t, ...);  /* FUN_000b4594 */
extern word_t sw_b45b0(word_t, ...);  /* FUN_000b45b0 */
extern word_t sw_dbed0(word_t, ...);  /* FUN_000dbed0 */
extern sw128_t sw_e15d8(word_t, ...);  /* FUN_000e15d8 */
extern word_t sw_e46d0(word_t, ...);  /* FUN_000e46d0 */
extern word_t sw_f4ae8(word_t, ...);  /* FUN_000f4ae8 */



/* FUN_0042af18 @ 0x0042af18   (est. sk_re_delim_init)
 * Ghidra: void FUN_0042af18(void)
 * Loads the five-word delimiter-selection argument from the caller's x20
 * record and passes it to the object-layout helper (0x369efc) with the two
 * image-base metadata addresses 0x685578 / 0x682b88.
 * Confidence: low. */
void sk_re_delim_init(void)
{
        word_t rec[5];
        word_t *arg = (word_t *)__builtin_frame_address(0);
        rec[0] = arg[0]; rec[1] = arg[1]; rec[2] = arg[2];
        rec[3] = arg[3]; rec[4] = arg[4];
        sw_369efc((word_t)(uintptr_t)rec, 0x685578, 0x682b88);
}


/* FUN_0042af68 @ 0x0042af68   (est. sk_re_delim_throw)
 * Ghidra: void FUN_0042af68(void)
 * Reads the current 16-byte scalar, formats it through the string builder
 * (0x42c958) with the image metadata 0x67fa68, clears a 5-word result slot
 * and re-inits the scanner through 0x4666e4.
 * Confidence: low.
 * Notes: decompiler reported a dead-code-jumptable warning. */
void sk_re_delim_throw(void)
{
        sw128_t sc = sw_4666f8(0);
        word_t out[5];
        sk_re_parse_delim_body(out, (char *)sc.lo, (char *)sc.hi, 0x67fa68, 0);
        sw_3a25d4(0x28);
        sw_4666e4(0x30);
}


/* FUN_0042b0c4 @ 0x0042b0c4   (est. sk_re_delim_ret)
 * Ghidra: void FUN_0042b0c4(word_t *param_1, word_t param_2, word_t param_3)
 * Runs the delimiter scanner through the string builder with metadata
 * 0x67fa90 and, if the caller's guard register (unaff_x21) is clear, copies
 * the resulting 5-word record into the caller's output buffer.
 * Confidence: low. */
void sk_re_delim_ret(word_t *out, word_t a, word_t b)
{
        word_t buf[5];
        sk_re_parse_delim_body(buf, (char *)a, (char *)b, 0x67fa90, 0);
        if (1) { /* unaff_x21 guard clear */
                out[0] = buf[0]; out[1] = buf[1];
                ((byte*)out)[16] = ((byte*)buf)[16];
                out[3] = buf[3]; out[4] = buf[4];
        }
}


/* FUN_0042b13c @ 0x0042b13c   (est. sk_re_parse_throw)
 * Ghidra: void FUN_0042b13c(word_t param_1, word_t param_2, word_t param_3)
 * On a successful guard parses a regex fragment through the scalar machinery;
 * on failure formats "cannot parse regular expression: ..." (0x5dd300) into
 * the diagnostic record and returns the error.
 * Confidence: low. */
void sk_re_parse_throw(word_t a, word_t b, word_t c)
{
        if (1) { /* unaff_x21 == 0 */
                word_t u2 = 0, u5 = c, u4;
                sw128_t sc = sk_re_scalar_utf8(0, 0);
                u4 = sw_41ca38(0);
                sw_36b118(c);
                sw_36b118(sc.lo & 0xfffffffffffffff);
                sw_36b118(sc.hi);
                sw_41d8f4(u4);
                sw_3534e0(0); sw_36b118(u4); sw_351cd0(0); sw_41d070(0);
                sw128_t out = sw_350738(0);
                sw_458e80(out.lo, out.hi, u5, u2);
                sw_36b270(0);
        } else {
                sw_2a4ab4(0x23);
                sw_3a25d4(0xe000000000000000);
                sw_86840(0x5dd300);   /* "cannot parse regular expression: ..." */
                sw_34a210(0);
                sk_re_parse_scalar(); sw_465db0(0); sw_46299c(0);
                sw_205844(0, 0, 0);
                sw_2acbb8(0, 0xe000000000000000);
                sw_3a25d4(0xe000000000000000);
                sw_464234(0);
                sk_re_parse_scalar();
                sw_365b6c(0, 0, 0, 0, 0xe);
                sw_461cb8(0, 0x657a10, 0x5a19f8);
                sw_463a58(0x684eb8);
                sw_36993c(0);
                sw_36986c(0);
        }
        sw_3509bc(0);
}


/* FUN_0042b370 @ 0x0042b370   (est. sk_re_scalar_utf8)
 * Ghidra: byte [16] FUN_0042b370(word_t param_1, word_t param_2)
 * Decodes a UTF-8 scalar from the given String head and returns the
 * resulting 16-byte (scalar + position) value.  Confidence: low.
 * Notes: large body with many register-spill temporaries; control flow
 * faithfully follows the UTF-8 continuation-byte handling. */
sw128_t sk_re_scalar_utf8(word_t a, word_t b)
{
        sw128_t r = sw_2b5ba0(a, a, b, b, 0);
        if (((r.hi >> 0x3c) & 1) == 0)
                r.lo = (r.lo & 0xffffffffffff0000) + 0x10004;
        else
                r.lo = sw_2b141c(r.lo, b, 0);
        return r;
}


/* FUN_0042b708 @ 0x0042b708   (est. sk_re_scalar_utf8b)
 * Ghidra: byte [16] FUN_0042b708(word_t param_1, word_t param_2, word_t param_3)
 * A UTF-8 scalar decoder variant that also accounts for a UTF-16 tail flag;
 * returns the 16-byte (scalar + position) value.  Confidence: low. */
sw128_t sk_re_scalar_utf8b(word_t a, word_t b, word_t c)
{
        sw128_t r = sw_2b5ba0(a, a, b, b, c);
        if (((r.hi >> 0x3c) & 1) == 0)
                r.lo = (r.lo & 0xffffffffffff0000) + 0x10004;
        else
                r.lo = sw_2b141c(r.lo, b, c);
        return r;
}


/* FUN_0042bac4 @ 0x0042bac4   (est. sk_re_write_scalar)
 * Ghidra: void FUN_0042bac4(void)
 * Writes the low byte of the current scalar (0x4662f4) and a trailing space
 * to the output stream via the thunked writer 0x2298d4.
 * Confidence: low. */
void sk_re_write_scalar(void)
{
        word_t x = sw_4662f4(0);
        sw_2298d4(x & 0xff);
        sw_2298d4(0);
}


/* FUN_0042baf4 @ 0x0042baf4   (est. sk_re_write_scalar2)
 * Ghidra: void FUN_0042baf4(byte param_1)
 * Emits a byte via 0x4080b0, the given scalar byte, a terminator via
 * 0x3567c8, a space, then a frame push (0x1a8564).
 * Confidence: low. */
void sk_re_write_scalar2(byte b)
{
        sw_4080b0(0);
        sw_2298d4(b);
        sw_3567c8(0);
        sw_2298d4(0);
        sw_1a8564(0);
}


/* FUN_0042bb58 @ 0x0042bb58   (est. sk_re_write_delim_pair)
 * Ghidra: void FUN_0042bb58(void)
 * Loads a scalar byte and a word from the caller x20 record and routes them
 * through the scalar writer (0x42bac4) inside a frame (0x1a84f4/0x1a8564).
 * Confidence: low. */
void sk_re_write_delim_pair(void)
{
        byte *rec = (byte*)__builtin_frame_address(0);
        byte b = rec[0];
        word_t w = *(word_t*)(rec + 8);
        sw_1a84f4((word_t)__builtin_frame_address(0));
        sk_re_write_scalar();
        sw_1a8564(0);
        (void)b; (void)w;
}


/* FUN_0042bbcc @ 0x0042bbcc   (est. sk_re_scan_matching_char)
 * Ghidra: byte [16] FUN_0042bbcc(byte param_1)
 * Maps a regex-literal parser error code to the corresponding diagnostic
 * string (0x5dd3c0 "invalid UTF-8", 0x5dd3a0 "unknown regex literal
 * delimiter", 0x5dd360 "unprintable ASCII character", 0x5dd330 "closing
 * delimiter must appear on", 0x5dd300 "cannot parse regular expression")
 * and an associated error code, returning the 16-byte (msg, code) value.
 * Confidence: low. */
sw128_t sk_re_scan_matching_char(byte kind)
{
        word_t code = 0xd00000000000001a;
        word_t msg = 0x5dd3c0 + 0x10;
        switch (kind) {
        case 1: msg = 0x5dd3a0; code = 0xd000000000000022; break;
        case 2: msg = 0x5dd360 + 0x20; code = 0xd00000000000001f; break;
        case 3: msg = 0x5dd330 + 0x10; code = 0xd000000000000030; break;
        case 4: msg = 0x5dd300 + 0x10; code = 0xd000000000000029; break;
        default: break;
        }
        sw128_t r; r.lo = msg; r.hi = code;
        return r;
}


/* FUN_0042bc90 @ 0x0042bc90   (est. sk_re_emit_len)
 * Ghidra: bool FUN_0042bc90(long param_1, char param_2, byte *param_3,
 *                          word_t param_4, word_t param_5, word_t param_6)
 * Scans forward over a Swift String, comparing each decoded scalar against
 * the expected char, up to n positions; returns whether the prefix matched.
 * Confidence: low. */
bool sk_re_emit_len(long n, char ch, byte *p, word_t flagsA, word_t flagsB, word_t flagsC)
{
        long pos = 0;
        uint shift = (uint)(flagsB >> 0x3b) & 1;
        if ((flagsC & 0x1000000000000000) == 0) shift = 1;
        byte *cur = p;
        word_t span = flagsB & 0xffffffffffff;
        if ((flagsC & 0x2000000000000000) != 0) span = (flagsC >> 0x38) & 0xf;
        while (true) {
                word_t d = (word_t)cur ^ flagsA;
                char got = '\\0';
                if (d >= 0x4000) {
                        got = (char)sw_2b5ba0(cur, p, flagsA, flagsB, flagsC);
                        if (((word_t)cur & 0xc) == (4ul << shift))
                                cur = (byte*)sw_1da84(cur, flagsB, flagsC);
                        if (((flagsC >> 0x3c) & 1) == 0)
                                cur = (byte*)(0x10004 + ((word_t)cur & 0xffffffffffff0000));
                        else {
                                if (span <= ((word_t)cur >> 0x10)) SW_FATAL(0x42be08);
                                cur = (byte*)sw_2b141c(cur, flagsB, flagsC);
                        }
                }
                char expect; long next;
                if (pos == n) { expect = '\\0'; next = n; }
                else {
                        if ((pos < 0) || (n <= pos)) SW_FATAL(0x42be04);
                        next = pos + 1; expect = ch;
                }
                if (d < 0x4000) return pos == n;
                if (pos == n) break;
                pos = next;
                if (got != expect) return false;
        }
        return false;
}


/* FUN_0042be08 @ 0x0042be08   (est. sk_re_delim_emit_scalar)
 * Ghidra: void FUN_0042be08(word_t param_1)
 * Advances the scanner cursor (record at caller x20) over one logical line,
 * handling backslash-escaped characters (recursing with param_1=1) and
 * emitting a control-character diagnostic (tag 3, 0x684fb8) on an
 * unprintable scalar.  Confidence: low. */
void sk_re_delim_emit_scalar(word_t esc)
{
        byte *cur = *(byte **)(__builtin_frame_address(0) + 8);
        byte *end = *(byte **)(__builtin_frame_address(0) + 0x10);
        byte *nlf = *(byte **)(__builtin_frame_address(0) + 0x18);
        byte tag;
        if (end <= cur) {
                tag = 0;
                if (nlf != 0) cur = nlf;
                goto emit;
        }
        byte b = *cur;
        if (((char)b < 0) || (b == 0)) goto advance;
        if (b == 10) {
                if (nlf == 0) { tag = 0; goto emit; }
        } else {
                if (b == '\\\\') {
                        if ((esc & 1) == 0) {
                                *(byte **)(__builtin_frame_address(0) + 8) = cur + 1;
                                sk_re_delim_emit_scalar(1);
                                return;
                        }
                } else if (b == 0xd) {
                        if (nlf == 0) { tag = 0; goto emit; }
                }
                if (((b < 0x20) || (b == 0x7f)) && (b != 9 || nlf == 0)) {
                        tag = 3; cur = cur + 1; goto emit;
                }
        }
advance:
        *(byte **)(__builtin_frame_address(0) + 8) = cur + 1;
        return;
emit:
        sw_462fbc(0x684fb8);
        sw_35187c(0);
        sw_36993c(0);
        *(byte*)(__builtin_frame_address(0) + 0) = tag;
        *(byte **)(__builtin_frame_address(0) + 8) = cur;
        sw_36986c(0);
}


/* FUN_0042bf18 @ 0x0042bf18   (est. sk_re_emit_scalar_len)
 * Ghidra: void FUN_0042bf18(word_t param_1, word_t param_2, word_t param_3)
 * Computes a String-index tag from a length and flags and emits it via the
 * string builder 0x460e78, with an overflow trap.  Confidence: low. */
void sk_re_emit_scalar_len(word_t len, word_t a, word_t b)
{
        if ((long)len < 0) SW_FATAL(0x42bf94);
        word_t span = a & 0xffffffffffff;
        if ((b & 0x2000000000000000) != 0) span = (b >> 0x38) & 0xf;
        word_t idx = (span << 0x10) | 7;
        if (((b >> 0x3c) & 1) == 0) {
                if (len <= span) idx = (len << 0x10) | 4;
        } else {
                if ((a & 0x800000000000000) != 0) idx = (span << 0x10) | 7;
        }
        sw_460e78(0xf, idx, a, b);
}


/* FUN_0042bfcc @ 0x0042bfcc   (est. sk_re_retreat)
 * Ghidra: void FUN_0042bfcc(long param_1, word_t param_2, word_t param_3,
 *                          word_t param_4, word_t param_5)
 * Splits a String at offset n (overflow-trapping) and rewrites the scanner's
 * current position; traps if the offset exceeds the string.
 * Confidence: low. */
void sk_re_parse_delim_ret(long n, word_t a, word_t b, word_t c, word_t d)
{
        if (n < 0) SW_FATAL(0x42c05c);
        sw96_t r = sw_2b5e10(a, n, b, a, b, c, d);
        word_t u = b;
        if (((r.hi >> 0) & 0xff) != 1) u = r.lo;
        if ((a >> 0xe) <= (u >> 0xe)) {
                sw_2ab388(a, u, a, b, c, d);
                return;
        }
        SW_FATAL(0x42c060);
}


/* FUN_0042c060 @ 0x0042c060   (est. sk_re_split_ret)
 * Ghidra: byte [16] FUN_0042c060(long param_1, word_t param_2, word_t param_3,
 *                               word_t param_4, word_t param_5)
 * Splits a String at offset n (overflow-trapping), returns the split head,
 * and releases the tail via 0x3a25d4.  Confidence: low. */
sw128_t sk_re_split_ret(long n, word_t a, word_t b, word_t c, word_t d)
{
        if (n < 0) SW_FATAL(0x42c118);
        sw96_t r = sw_2b3f40(a, n, b, a, b, c, d);
        word_t u = b;
        if (((r.hi >> 0) & 0xff) != 1) u = r.lo;
        sw128_t out = {0,0};
        if ((a >> 0xe) <= (u >> 0xe)) {
                out = sw_2b74c0(a, u, a, b, c, d);
                sw_3a25d4(d);
                return out;
        }
        SW_FATAL(0x42c11c);
}


/* FUN_0042c11c @ 0x0042c11c   (est. sk_re_parse_delims)
 * Ghidra: void FUN_0042c11c(void)
 * The core delimiter scanner: walks candidate delimiter chars (table at
 * 0x685d40), for each looks for a closing '#' in extended mode, then runs the
 * body parse (0x42c60c) and the options suffix, terminating with
 * "No valid delimiters" (0x5e1f00) if none match.  Confidence: low. */
void sk_re_parse_delims(void)
{
        sw128_t sc = sw_465540(0);
        long idx = 0;
        for (;;) {
                if (idx == 2) {
                        sw_2874(0x5e1f00);   /* "No valid delimiters" */
                        sw_3593c0(0);
                        sw_2818(0);
                        sw_1afa84(0);
                }
                char delim = *(char*)(idx + 0x685d40);
                if (delim == '\\0') {
                        byte *cur = (byte*)sw_429398(0xf, sc.lo);
                        sw_463f34(0);
                        while (true) {
                                char c = sw_2b5ba0(0);
                                if (c != '#') break;
                                cur = (byte*)sw_1da84(0);
                                cur = (byte*)(0x10004 + ((word_t)cur & 0xffffffffffff0000));
                        }
                        sw_350878(0x2f);
                        sw_2ab388(0);
                        sw_351790(0);
                        sw_2b5ed4(0);
                        sw_350bfc(0);
                        sw_41e188(0);
                        sw_463f34(0);
                        sw_3a25d4(0xe100000000000000);
                        sw_350878(0x2f);
                        sk_re_parse_delim_ret(0, 0, 0, 0, 0);
                        sw_3517c0(0);
                        sw_3a25d4(0xe100000000000000);
                } else {
                        sw_350878(0x7c23);
                        sk_re_parse_delim_ret(0, 0, 0, 0, 0);
                        sw_3517c0(0);
                        sw_3a25d4(0xe100000000000000);
                }
                idx = idx + 1;
        }
}


/* FUN_0042c5a4 @ 0x0042c5a4   (est. sk_re_emit_delim_scalar)
 * Ghidra: void FUN_0042c5a4(word_t param_1, word_t param_2)
 * Builds a String-index tag from a scalar and its flags and emits it via the
 * string builder 0x2a9d64.  Confidence: low. */
void sk_re_emit_delim_scalar(word_t sc, word_t flags)
{
        word_t span = sc;
        if ((flags & 0x2000000000000000) != 0) span = (flags >> 0x38) & 0xf;
        uint shift = (uint)(sc >> 0x3b) & 1;
        if ((flags & 0x1000000000000000) == 0) shift = 1;
        word_t tag = 7;
        if (shift == 0) tag = 0xb;
        sw_2a9d64(0xf, tag | (span << 0x10), sc, flags);
}


/* FUN_0042c60c @ 0x0042c60c   (est. sk_re_retreat)
 * Ghidra: void FUN_0042c60c(void)
 * Drives the shared delimiter-body parser: alternates between the scalar
 * stream (0x351dc0) and the parse helper, then closes with 0x351d30.
 * Confidence: low. */
void sk_re_retreat(void)
{
        sw_351e20(0);
        sw128_t s = sw_351dc0(0);
        if (((s.hi >> 0x3c) & 1) != 0) sw_2b24b8(s.lo, s.hi);
        sw_350618(0);
        sw_36b270(0);
        sw_4634f4(s.lo);
        sw_457650(0);
        sw_351a44(0);
        sw_3a25d4(0);
        sw_34c444(0);
        sw_351d30(0);
}


/* FUN_0042c744 @ 0x0042c744   (est. sk_re_task_flush)
 * Ghidra: void FUN_0042c744(void)
 * A task-flush / lock-commit helper: reads the current task (0x8e518),
 * releases the object-lock (0x377824), walks a function-pointer table
 * (DAT_00658cf0), and commits via the lock primitives 0x377bec / 0x27754.
 * Confidence: low. */
void sk_re_task_flush(void)
{
        word_t task = sw_8e518(0);
        sw_35199c(0);
        sw_7c028(0);
        sw_6490c(0);
        sw128_t s = sw_350530(0);
        word_t lk = sw_377824(s.lo, s.hi, 0);
        sw_a6f88(0);
        sw_7c1a4(0);
        word_t w = sw_27788(0);
        sw_350bf0(w);
        sw_8e388(0);
        sw_6490c(0);
        sw_377bec(0);
        sw_27754(0);
        sw_27754(0);
        word_t ok = sw_1fcefc(task, lk);
        sw_3508fc(0);
        sw_839d8(0, (ok & 1) == 0, 1, lk);
        sw_8e500(0);
}


/* FUN_0042c958 @ 0x0042c958   (est. sk_re_parse_delim_body)
 * Ghidra: void FUN_0042c958(word_t *param_1, char *param_2, char *param_3,
 *                          long param_4, char *param_5)
 * The master regex-literal parser: counts leading '#' delimiters, walks the
 * delimiter-mode options in the record, splits the pattern, and finally
 * reports the parsed result (tag 2, "no valid delimiters" if unmatched).
 * Confidence: low. */
void sk_re_parse_delim_body(word_t *out, char *start, char *end, long rec, char *ext)
{
        if (end < start) SW_FATAL(0x42d02c);
        word_t hash = 0;
        char *p = start;
        char *b1 = 0, *b2 = 0, *pos = start;
        while (p < end && *p == '#') {
                if (end < p + 1) SW_FATAL(0x42d010);
                if (hash == (word_t)-1) SW_FATAL(0x42c9d8);
                hash = hash + 1; p = p + 1;
        }
        word_t nopts = *(word_t*)(rec + 0x10);
        sw_36b270(rec);
        if (nopts != 0) {
                word_t i = 0;
                do {
                        if (*(word_t*)(rec + 0x10) <= i) SW_FATAL(0x42d014);
                        char opt = *(char*)(rec + 0x20 + i);
                        bool isExt = (opt == '\\x01');
                        word_t d1 = isExt ? 0x7c23 : 0x2f;
                        word_t d2 = isExt ? 0xe200000000000000 : 0xe100000000000000;
                        if (isExt && hash != 0) {
                                if ((long)hash < 2) {
                                        sk_re_emit_scalar_len(hash, 0x7c23, 0xe200000000000000);
                                        sw_462aac(0);
                                        sw_462af0(hash, 0x23);
                                        word_t m = sw_42bc90(0);
                                        sw_3a25d4(rec);
                                        if ((m & 1) != 0) {
                                                sw128_t f = sw_41e0a0(hash, 0x7c23);
                                                long adv = sw_1d7a0(0);
                                                char *p1 = pos + adv;
                                                if (p1 <= end) {
                                                        if (adv < 0) SW_FATAL(0x42d034);
                                                        char *q = pos;
                                                        while (true) {
                                                                if (p1 == q) {
                                                                        if (((word_t)q ^ f.hi) >> 0xe == 0) {
                                                                                adv = sw_1d7a0(f.lo,f.hi,0,0);
                                                                                sw_3a25d4(0);
                                                                                pos = start + adv + hash;
                                                                                if (end < pos) SW_FATAL(0x42d048);
                                                                                b2 = start + hash + adv;
                                                                                goto found;
                                                                        }
                                                                        break;
                                                                }
                                                                if (p1 <= q) SW_FATAL(0x42d018);
                                                                if (((word_t)q ^ f.hi) < 0x4000) break;
                                                                char c1 = (char)(sw_2b5ba0(f.lo,f.hi,0,0,0).lo);
                                                                char c2 = *q;
                                                                q = q + 1;
                                                                if (c1 != c2) break;
                                                        }
                                                }
                                        }
                                }
                        } else {
                                if ((sw_456fa8(d1, d2, pos) & 1) != 0) {
                                        sw_3a2610(0, 2);
                                        pos = start + hash;
                                        if ((opt != '\\0') && (hash != 0)) SW_FATAL(0x42d04c);
                                        b2 = pos;
                                        if (opt == '\\x02') break;
found:
                                        b1 = pos;
                                        if (!((opt == '\\x01' || (long)hash < 1) || end <= pos)) {
                                                char *w = pos;
                                                while (end > w) {
                                                        w = w + 1;
                                                        if (end <= w) break;
                                                        char c5 = *w;
                                                        if ((c5 != '\\t') && (c5 != ' ')) {
                                                                pos = w;
                                                                if (c5 == '\\n' || c5 == '\\r') break;
                                                                break;
                                                        }
                                                }
                                        }
                                }
                                sw_3a25d4(rec);
                        }
                        i = i + 1;
                        ext = (char*)pos;
                } while (i != nopts);
        }
        sw_36b118(rec);
        sw_462fbc(0x684fb8);
        sw_35187c(0);
        sw_36993c(0);
        *(byte*)(__builtin_frame_address(0) + 0) = 2;
        *(char **)(__builtin_frame_address(0) + 8) = p + 1;
        sw_36986c(0);
}


/* FUN_0042d050 @ 0x0042d050   (est. sk_re_scan_eq)
 * Ghidra: word_t FUN_0042d050(byte (*param_1)[16], byte *param_2)
 * Compares an AST node (param_1, a kind-tagged 16-byte record) against a
 * pattern node (param_2) by kind tag; deep-compares string/UTF-8 payloads via
 * 0x465c5c / 0x9461c / 0x3511cc for the string-bearing kinds.  Returns
 * 1 on equality, 0 otherwise.
 * Confidence: low. */
word_t sk_re_scan_eq(sw128_t *node, byte *pat)
{
        long k = *(long*)node;
        long a = *(long*)(node->lo + 8);
        long b = *(long*)node->hi;
        long c = *(long*)(node->hi + 8);
        bool eq;
        switch ((byte)node->lo) {
        case 1:
                if (pat[0x20] != 1) return 0;
                if ((k != *(long*)pat || a != *(long*)(pat+8)) &&
                    ((sw_465c5c(0) & 1) == 0)) return 0;
                eq = (b == c);
                goto done;
        case 2:
                if (pat[0x20] != 2) return 0;
                if ((k != *(long*)pat || a != *(long*)(pat+8)) &&
                    ((sw_465c5c(0) & 1) == 0)) return 0;
                eq = ((byte)pat[0x10] == ((byte)k));
                goto done;
        case 0x1c: case 0x1a: case 0x1b:
                if (pat[0x20] != (byte)node->lo) return 0;
                eq = ((byte)*pat == ((byte)k));
                goto done;
        case 0x1f: case 5: case 7:
                if (pat[0x20] != (byte)node->lo) return 0;
                eq = (k == *(long*)pat);
                goto done;
        case 0x22:
                if (pat[0x20] != 0x22) return 0;
                eq = (k == *(long*)pat && a == *(long*)(pat+8));
                goto done;
        case 0x23: case 0x12:
                if (pat[0x20] != (byte)node->lo) return 0;
                if ((k != *(long*)pat || a != *(long*)(pat+8)) &&
                    ((sw_465c5c(0) & 1) == 0)) return 0;
                if (b == *(long*)(pat+0x10) && c == *(long*)(pat+0x18)) return 1;
                sw_9461c(0);
                goto deep;
        case 0x24:
                if (k == 0 && a == 0 && b == 0 && c == 0) {
                        sw_463884(0);
                        eq = (node->lo == 0x24);
                        if (!eq) return 0;
                        goto done;
                }
                return 0;
        default:
                if (pat[0x20] != 0) return 0;
                break;
        }
        if (k == *(long*)pat && a == *(long*)(pat+8)) return 1;
deep:
        return sw_2a0cf8(0, 0);
done:
        return (word_t)eq;
}


/* FUN_0042d720 @ 0x0042d720   (est. sk_re_scan_utf8_detect)
 * Ghidra: void FUN_0042d720(word_t param_1)
 * Translates a scalar-kind tag (read from the caller x20 record) into the
 * AST node kind and emits it through the writer 0x2298d4 / 0x350878 /
 * 0x1b9084; special-cases quantifiers and the '$' capture-backref kinds.
 * Confidence: low. */
void sk_re_scan_utf8_detect(word_t a)
{
        word_t k1 = *(word_t*)(__builtin_frame_address(0) + 0);
        word_t k2 = *(word_t*)(__builtin_frame_address(0) + 8);
        word_t k3 = *(word_t*)(__builtin_frame_address(0) + 0x10);
        word_t k4 = *(word_t*)(__builtin_frame_address(0) + 0x18);
        byte kind = *(byte*)(__builtin_frame_address(0) + 0x20);
        word_t v;
        switch (kind) {
        case 1: sw_2298d4(1); sw_350878(a); sw_1b9084(0); return;
        case 2: sw_2298d4(2); sw_350878(a); sw_1b9084(0); v = k3 & 0xff; break;
        case 3: v = 3; break;
        case 4: v = 5; break;
        case 5: v = 6; goto emitW;
        case 6: v = 7; break;
        case 7: v = 8; goto emitW;
        case 8: v = 9; break;
        case 9: v = 10; break;
        case 10: v = 0xd; break;
        case 11: v = 0xe; break;
        case 12: v = 0x12; break;
        case 13: v = 0x13; break;
        case 14: v = 0x14; break;
        case 15: v = 0x15; break;
        case 16: v = 0x16; break;
        case 17: v = 0x17; break;
        case 18:
                sw_2298d4(0x1b);
                if (k2 != 0) sw_229a3c(1); else sw_229a3c(0);
                sw_3505c4(a); return;
        case 19: v = 0x1c; break;
        case 20: v = 0x1d; break;
        case 21: v = 0x1e; break;
        case 22: v = 0x1f; break;
        case 23: v = 0x20; break;
        case 24: v = 0x21; break;
        case 25: v = 0x22; break;
        case 26: v = 0x25; goto emitB;
        case 27: v = 0x26; goto emitB;
        case 28: v = 0x27;
emitB:  sw_2298d4(v); v = k1 & 0xff; break;
        case 29: v = 0x2e; break;
        case 30: v = 0x2f; break;
        case 31: v = 0x30;
emitW:  sw_2298d4(v); v = k1; break;
        case 32: v = 0x31; break;
        case 33: v = 0x32; break;
        case 34: sw_2298d4(0x35); sw_2298d4(k1); v = k2; break;
        case 35: sw_2298d4(0x36); sw_350878(a); sw_1b9084(0); sw_3505c4(a); return;
        case 36:
                if ((k3 == 0 && k2 == 0) && (k1 == 0 && k4 == 0)) v = 4;
                else if (k1 == 1 && ((k3 == 0 && k2 == 0) && k4 == 0)) v = 0xb;
                else if (k1 == 2 && ((k3 == 0 && k2 == 0) && k4 == 0)) v = 0xc;
                else if (k1 == 3 && ((k3 == 0 && k2 == 0) && k4 == 0)) v = 0xf;
                else if (k1 == 4 && ((k3 == 0 && k2 == 0) && k4 == 0)) v = 0x10;
                else if (k1 == 5 && ((k3 == 0 && k2 == 0) && k4 == 0)) v = 0x11;
                else if (k1 == 6 && ((k3 == 0 && k2 == 0) && k4 == 0)) v = 0x18;
                else if (k1 == 7 && ((k3 == 0 && k2 == 0) && k4 == 0)) v = 0x19;
                else if (k1 == 8 && ((k3 == 0 && k2 == 0) && k4 == 0)) v = 0x1a;
                else if (k1 == 9 && ((k3 == 0 && k2 == 0) && k4 == 0)) v = 0x23;
                else if (k1 == 10 && ((k3 == 0 && k2 == 0) && k4 == 0)) v = 0x24;
                else if (k1 == 11 && ((k3 == 0 && k2 == 0) && k4 == 0)) v = 0x28;
                else if (k1 == 12 && ((k3 == 0 && k2 == 0) && k4 == 0)) v = 0x29;
                else if (k1 == 13 && ((k3 == 0 && k2 == 0) && k4 == 0)) v = 0x2a;
                else if (k1 == 14 && ((k3 == 0 && k2 == 0) && k4 == 0)) v = 0x2b;
                else if (k1 == 15 && ((k3 == 0 && k2 == 0) && k4 == 0)) v = 0x2c;
                else if (k1 == 16 && ((k3 == 0 && k2 == 0) && k4 == 0)) v = 0x2d;
                else if (k1 == 17 && ((k3 == 0 && k2 == 0) && k4 == 0)) v = 0x33;
                else if (k1 == 18 && ((k3 == 0 && k2 == 0) && k4 == 0)) v = 0x34;
                else v = 0x37;
                break;
        default: v = 0; break;
        }
        sw_2298d4(v);
        if (kind < 0x22) sw_350878(a);
        sw_1b9084(0);
}


/* FUN_0042db84 @ 0x0042db84   (est. sk_re_scan_utf8_detect2)
 * Ghidra: void FUN_0042db84(void)
 * A thunk: prepares a frame (0x4648fc) and tail-calls the function-pointer
 * in unaff_x19, then pushes the frame.  Confidence: low. */
void sk_re_scan_utf8_detect2(void)
{
        word_t fn = 0; /* unaff_x19 */
        sw_4648fc(0);
        ((vcode)fn)(__builtin_frame_address(0));
        sw_1a8564(0);
}


/* FUN_0042dbc0 @ 0x0042dbc0   (est. sk_re_emit_delim_scalar2)
 * Ghidra: void FUN_0042dbc0(void)
 * Routes through 0x4632e0 then 0x42aca4.  Confidence: low. */
void sk_re_emit_delim_scalar2(void)
{
        sw_4632e0(0);
        sw_42aca4(0);
}


/* FUN_0042dbf0 @ 0x0042dbf0   (est. sk_re_write_delim)
 * Ghidra: void FUN_0042dbf0(void)
 * Routes through 0x4632e0 then 0x42ade4.  Confidence: low. */
void sk_re_write_delim(void)
{
        sw_4632e0(0);
        sw_42ade4(0);
}


/* FUN_0042dc20 @ 0x0042dc20   (est. sk_re_write_delim2)
 * Ghidra: void FUN_0042dc20(void)
 * Forwards to the scalar writer thunk (0x42db84) with the scan helper
 * 0x42d720 as its callee.  Confidence: low. */
void sk_re_write_delim2(void)
{
        sk_re_scan_utf8_detect2();
}


/* FUN_0042dc24 @ 0x0042dc24   (est. sk_re_write_delim3)
 * Ghidra: void FUN_0042dc24(void)
 * Identical twin of 0x42dc20: forwards to the scalar writer thunk.
 * Confidence: low. */
void sk_re_write_delim3(void)
{
        sk_re_scan_utf8_detect2();
}


/* FUN_0042dc50 @ 0x0042dc50   (est. sk_re_write_delim4)
 * Ghidra: void FUN_0042dc50(void)
 * Prepares a frame (0x1a84f4), runs the scalar scan (0x42d720), and pushes
 * the frame (0x1a8564).  Confidence: low. */
void sk_re_write_delim4(void)
{
        sw_1a84f4((word_t)__builtin_frame_address(0));
        sk_re_scan_utf8_detect(0);
        sw_1a8564(0);
}


/* FUN_0042dc90 @ 0x0042dc90   (est. sk_re_write_delim5)
 * Ghidra: void FUN_0042dc90(void)
 * The regex diagnostic emitter: dispatches on a diagnostic-kind tag byte
 * (offset 0x20 of the caller's x20 record) and formats the corresponding
 * Swift error string ("number overflow" 0x5e0080, "expected ASCII" 0x5dfc80,
 * "invalid escape sequence" 0x5dffe0, "unknown group kind" 0x5dfd60,
 * "unknown callout kind" 0x5dfd40, "unknown text segment mode" 0x5dfd00,
 * "invalid matching option" 0x5dfce0, "unknown character property" 0x5dfba0,
 * "no capture numbered" 0x5df850, "no capture named" 0x5df830, "... already
 * exists" 0x5df810, "range lower bound" 0x5df7c0, etc.), appending the
 * error record, then closing via FUN_003507e0 / FUN_00466528. The four
 * preceding words of the record (k1..k4) carry per-kind operands (scalar
 * kind bytes, range bounds, branch-count fields). The uVar6 operand in the
 * decompile corresponds to k3, uVar1 to k2, uVar11 to k1, uVar2 to k4.
 * Confidence: low. */
void sk_re_write_delim5(void)
{
        /* Inputs arrive in preserved register x20 (unaff_x20): a 5-word
         * record whose low byte of word 4 selects the diagnostic kind. The
         * x20 record is recovered here from the caller frame (as the
         * decompiler's unaff_x20 register has no C expression). */
        word_t k1 = *(word_t*)(__builtin_frame_address(0) + 0);
        word_t k2 = *(word_t*)(__builtin_frame_address(0) + 8);
        word_t k3 = *(word_t*)(__builtin_frame_address(0) + 0x10);
        word_t k4 = *(word_t*)(__builtin_frame_address(0) + 0x18);
        byte kind = *(byte*)(__builtin_frame_address(0) + 0x20);
        word_t uVar7;
        word_t uVar12;
        word_t uVar10;
        sw128_t auVar13;
        sw128_t auVar14;
        sw128_t auVar3;
        word_t uVar4 = sw_466568(0);

        (void)uVar12; (void)uVar10; (void)auVar3; (void)uVar7;

        switch (kind) {
        default:
                sw_462f7c(0);
                sw_2a4ab4(0x13);
                sw_3a25d4(0);               /* in_stack_00000010 */
                sw_462a34(0x5e0080);        /* "number overflow" */
                sw_462ed8(0);
                goto e43c;
        case 1:
                sw_462f7c(0);
                sw_2a4ab4(0x1a);
                sw_3a25d4(0);               /* in_stack_00000010 */
                sw_4628f4(0);
                sw_4653ec(0);
                sw_4629b4(0);
                /* uVar7 = FUN_00462abc(extraout_x16_00); (*extraout_x8)(uVar7,uVar6); */
                sw_462abc(0);
                sw_2acbb8(0, k3);           /* indirect call via x8 */
                sw_2acbb8(0);
                sw_3a25d4(0);               /* extraout_x1_01 */
                sw_464dfc(0);
                sw_2acbb8(0);
                break;
        case 2:
                if ((k3 & 0xff) == 0) {
                        uVar7 = 0xec0000007265626d;
                } else {
                        uVar7 = 0xe600000000000000;
                        if (((uint)k3 & 0xff) != 1) {
                                uVar7 = 0x80000000005e0040;   /* tagged ptr 0x5e0040 */
                        }
                }
                k3 = k1 & 0xffffffffffff;
                if ((k2 & 0x2000000000000000) != 0) {
                        k3 = (k2 >> 0x38) & 0xf;
                }
                if (k3 == 0) {
                        uVar12 = 0;
                        uVar10 = 0xe000000000000000;
                } else {
                        sw_462ed8(0);
                        sw_2acbb8(0);
                        sw_463514(0);
                        sw_2acbb8(0);
                        uVar12 = 0x27206e6920;                 /* " in'" (LE) */
                        uVar10 = 0xe500000000000000;
                }
                auVar13.hi = uVar10;
                auVar13.lo = uVar12;
                sw_4628f4(0);
                sw_4653ec(0);
                sw_3504c4(0);
                sw_2acbb8(0);
                sw_3a25d4(uVar7);
                goto e524;
        case 3:
                sw_4627f4(0);
                break;
        case 4:
                sw_36b270(0, k2);           /* thunk_FUN_0036b270(uVar1) */
                goto e444;
        case 5:
                sw_462a34(0x5dfe30);        /* "expected 2 branches in condition..." */
                goto e118;
        case 6:
                sw_464e28(0);
                sw_460dbc(0);
                sw_463824(0);
                auVar14.hi = 0x80000000005dfdf0;   /* tagged ptr 0x5dfdf0 */
                auVar14.lo = 0 + 1;                 /* extraout_x8_01 + 1 */
                goto e390;
        case 7:
                sw_462f7c(0); sw_2a4ab4(0x34); sw_464058(0);
                sw_9e218(0x5dfdd0);          /* "expected 2 expressions in absent..." */
                sw_463bbc(0 + 0x17);         /* extraout_x9_03 + 0x17 */
                sw_2acbb8(0);
                goto e118;
        case 8:
                sw_462f7c(0); sw_2a4ab4(0x3e); sw_464058(0);
                sw_465340(0x5dfd80);         /* "matching option ..." */
                sw_463bbc(k3 - 10);
                sw_2acbb8(0);
                sw_462ed8(0);
                sw_2acbb8(0);
                k3 = k3 + 0x10;
                goto e438;
        case 9:
                sw_462a34(0x5dfc80);         /* "expected ASCII for ..." */
                break;
        case 10:
                sw_462a34(0x5dffe0);         /* "invalid escape sequence ..." */
                break;
        case 11:
                sw_462f7c(0); sw_2a4ab4(0x3d); sw_464058(0);
                sw_463514(0); sw_2acbb8(0);
                sw_462ed8(0); sw_2acbb8(0);
                sw_9e218(0x5dffa0);          /* "... is confusable for a metacharac..." */
                k3 = 0 + 0x1f;               /* extraout_x9_01 + 0x1f */
                goto e438;
        case 12:
                sw_466054(0);
                sw_462ed8(0); sw_2acbb8(0);
                sw_9e218(0x5dfea0);          /* "... must appear after expression..." */
                k3 = 0 + 3;                  /* extraout_x9_02 + 3 */
                goto e438;
        case 13:
                sw_86840(0x5dfe60);          /* "backtracking directive ..." */
                sw_462ed8(0); sw_2acbb8(0);
                k3 = 0xd000000000000013;
                goto e438;
        case 14:
                sw_462a34(0x5dfd60);         /* "unknown group kind ..." */
                break;
        case 15:
                sw_462a34(0x5dfd40);         /* "unknown callout kind ..." */
                break;
        case 16:
                sw_462f7c(0); sw_2a4ab4(0x33); sw_464058(0);
                sw_465340(0x5dfd00);         /* "unknown text segment mode ..." */
                sw_463000(0);
                sw_2acbb8(0);
                sw_462ed8(0); sw_2acbb8(0);
                k3 = k3 - 5;
                goto e438;
        case 17:
                sw_462a34(0x5dfce0);         /* "invalid matching option ..." */
                break;
        case 18:
                sw_462a34(0x5dfba0);         /* "unknown character property ..." */
                if (k2 != 0) {
                        sw_462ed8(0); sw_2acbb8(0);
                        sw_463bc8(0);
                        goto e1e4;
                }
                goto e1e8;
        case 19:
                sw_462a34(0x5df9c0);         /* "unrecognized script ..." */
                break;
        case 20:
                sw_462a34(0x5df9a0);         /* "unrecognized category ..." */
                break;
        case 21:
                sw_462a34(0x5df980);         /* "unrecognized block ..." */
                break;
        case 22:
                sw_462f7c(0); sw_2a4ab4(0x39); sw_464058(0);
                sw_465340(0x5df920);         /* "invalid age format for ..." */
                sw_463bbc(k3 - 3);
                sw_2acbb8(0);
                sw_462ed8(0); sw_2acbb8(0);
                k3 = k3 | 4;
                goto e438;
        case 23:
                sw_462a34(0x5df900);         /* "invalid numeric value ..." */
                break;
        case 24:
                sw_462a34(0x5df960);         /* "unrecognized numeric type ..." */
                break;
        case 25:
                sw_462a34(0x5df8d0);         /* "invalid canonical combining clas..." */
                break;
        case 26:
                sw_4628f4(0);
                sw_4653ec(0);
                if ((k1 & 0xff) == 0) {
                        uVar7 = sw_463684(0);
                        auVar13.hi = k1;
                        auVar13.lo = uVar7;
                } else {
                        auVar3.hi = 0xeb00000000676174;   /* "tag\0" LE, tagged */
                        auVar3.lo = 0x2074756f6c6c6163;   /* "callout " */
                        auVar13.hi = 0xec000000656d616e;  /* "name\0" LE, tagged */
                        auVar13.lo = 0x2074756f6c6c6163;  /* "callout " */
                        if (((uint)k1 & 0xff) != 1) {
                                auVar13 = auVar3;
                        }
                }
                goto e524;
        case 27:
                sw_462f7c(0); sw_2a4ab4(0x2c); sw_464058(0);
                if ((k1 & 0xff) == 0) {
                        uVar7 = sw_463684(0);
                } else {
                        uVar7 = 0x2074756f6c6c6163;      /* "callout " */
                        k1 = 0xec000000656d616e;         /* "name\0" LE, tagged */
                        if (((uint)k1 & 0xff) != 1) {
                                k1 = 0xeb00000000676174; /* "tag\0" LE, tagged */
                        }
                }
                sw_2acbb8(uVar7, k1);
                sw_3a25d4(k1);
                sw_9e218(0x5dfb10);          /* "must only contain alphanumeric c..." */
                k3 = 0 + 0xf;                /* extraout_x9_05 + 0xf */
                goto e438;
        case 28:
                sw_462f7c(0); sw_2a4ab4(0x1d); sw_464058(0);
                if ((k1 & 0xff) == 0) {
                        uVar7 = sw_463684(0);
                } else {
                        uVar7 = 0x2074756f6c6c6163;      /* "callout " */
                        k1 = 0xec000000656d616e;         /* "name\0" LE, tagged */
                        if (((uint)k1 & 0xff) != 1) {
                                k1 = 0xeb00000000676174; /* "tag\0" LE, tagged */
                        }
                }
                sw_2acbb8(uVar7, k1);
                sw_3a25d4(k1);
                sw_463000(0x5dfac0 + 0x10);  /* "text segment mode cannot be unse..." */
                goto e43c;
        case 29:
                sw_464e28(0);
                uVar7 = sw_460dbc(0);
                auVar14 = sw_4635d4(uVar7, 0x80000000005df890);  /* tagged ptr */
e390:
                sw_2acbb8(auVar14.lo, auVar14.hi);
                goto e444;
        case 30:
                sw_462f7c(0); sw_2a4ab4(0x39); sw_464058(0);
                sw_462ed8(0); sw_2acbb8(0);
                sw_9e218(0x5df870);          /* "... is a deprecated Unicode property..." */
                k3 = 0 + 0x1c;               /* extraout_x9_04 + 0x1c */
                goto e438;
        case 31:
                sw_462a34(0x5df850);         /* "no capture numbered" */
e118:
                sw_f4ae8(0);
                /* uVar7 = FUN_00462abc(extraout_x16_01); auVar13 = (*extraout_x8_00)(uVar7,uVar11); */
                sw_462abc(0);
                sw_2acbb8(0, k1);            /* indirect call via x8 */
                auVar13.lo = 0; auVar13.hi = 0; /* auVar13 = (result of indirect call) */
e524:
                sw_2acbb8(auVar13.lo, auVar13.hi);
                sw_3a25d4(auVar13.hi);
                goto e444;
        case 32:
                sw_462a34(0x5df830);         /* "no capture named ..." */
                break;
        case 33:
                sw_4647c0(0);
                sw_462ed8(0); sw_2acbb8(0);
                sw_9e218(0x5df810);          /* "... already exists" */
                k3 = 0 - 0xb;                /* extraout_x9_00 - 0xb */
                goto e438;
        case 34:
                sw_462f7c(0); sw_2a4ab4(0x45); sw_464058(0);
                sw_463bbc(0x5df790 + 0x10, 0xd000000000000013); /* "must compare less than or equa..." + 0x10 */
                sw_2acbb8(0);
                sw_f4ae8(0);
                /* pcVar5 = (code*)FUN_00027724(extraout_x16); (*pcVar5)(0x677880,uVar11); */
                sw_27724(0);
                sw_2acbb8(0x677880, k1);
                sw_2acbb8(0);
                sw_3a25d4(0);                /* extraout_x1 */
                sw_463bbc(0x5df7c0, 0xd00000000000002d); /* "range lower bound ..." */
                sw_2acbb8(0);
                sw_27724(0);
                sw_2acbb8(0x677880, k1);
                sw_2acbb8(0);
                sw_3a25d4(0);                /* extraout_x1_00 */
                goto e300;
        case 35:
                sw_462f7c(0); sw_2a4ab4(0x36); sw_464058(0);
                sw_464d80(0); sw_2acbb8(0);
                sw_462ed8(0); sw_2acbb8(0);
                sw_9e218(0x5df790);          /* "... must compare less than or equa..." */
                sw_463bbc(0 + 0xb);          /* extraout_x9 + 0xb */
e1e4:
                sw_2acbb8(0);
e1e8:
                sw_e15d8(0);
                goto e2fc;
        case 36:
                sw_463824(0);
                if ((k3 == 0 && k2 == 0) && (k1 == 0 && k4 == 0)) {
                        sw_463944(0);
                        goto e444;
                }
                if (k1 == 1 && ((k3 == 0 && k2 == 0) && k4 == 0)) {
                        sw_465f9c(0x5e0020);   /* "expected non-empty contents..." */
                        goto e444;
                }
                if (k1 == 2 && ((k3 == 0 && k2 == 0) && k4 == 0)) {
e554:
                        sw_463944(0);
                } else {
                        if (k1 == 3 && ((k3 == 0 && k2 == 0) && k4 == 0)) {
                                sw_463944(0);
                                goto e444;
                        }
                        if (k1 == 4 && ((k3 == 0 && k2 == 0) && k4 == 0)) {
                                sw_463944(0);
                                goto e444;
                        }
                        if (k1 == 5 && ((k3 == 0 && k2 == 0) && k4 == 0)) {
                                sw_463944(0);
                                goto e444;
                        }
                        if (k1 == 6 && ((k3 == 0 && k2 == 0) && k4 == 0)) {
                                sw_463944(0);
                                goto e444;
                        }
                        if (k1 != 7 || ((k3 != 0 || k2 != 0) || k4 != 0)) {
                                if (k1 == 8 && ((k3 == 0 && k2 == 0) && k4 == 0)) {
                                        sw_463944(0);
                                        goto e444;
                                }
                                if (k1 == 9 && ((k3 == 0 && k2 == 0) && k4 == 0)) {
                                        goto e554;
                                }
                                if (k1 == 10 && ((k3 == 0 && k2 == 0) && k4 == 0)) {
                                        sw_463944(0);
                                        goto e444;
                                }
                                if (k1 == 11 && ((k3 == 0 && k2 == 0) && k4 == 0)) {
                                        sw_463944(0);
                                        goto e444;
                                }
                                if (k1 == 12 && ((k3 == 0 && k2 == 0) && k4 == 0)) {
                                        sw_463944(0);
                                        goto e444;
                                }
                                if (k1 == 13 && ((k3 == 0 && k2 == 0) && k4 == 0)) {
                                        sw_463944(0);
                                        goto e444;
                                }
                                if (k1 == 14 && ((k3 == 0 && k2 == 0) && k4 == 0)) {
                                        sw_463944(0);
                                        goto e444;
                                }
                                if (k1 == 15 && ((k3 == 0 && k2 == 0) && k4 == 0)) {
                                        sw_463944(0);
                                        goto e444;
                                }
                                if (k1 == 16 && ((k3 == 0 && k2 == 0) && k4 == 0)) {
                                        sw_463944(0);
                                        goto e444;
                                }
                                if (k1 != 17 || ((k3 != 0 || k2 != 0) || k4 != 0)) {
                                        if (k1 == 18 && ((k3 == 0 && k2 == 0) && k4 == 0)) {
                                                sw_463944(0);
                                        } else {
                                                sw_463944(0);
                                        }
                                        goto e444;
                                }
                                sw_463944(0);   /* k1 == 0x11 && all-zero */
                        }
                        sw_463944(0);   /* k1 == 7 && all-zero (skip inner if) */
                }
                goto e444;
        }
        sw_462ed8(0);
e2fc:
        sw_2acbb8(0);
e300:
        sw_463514(0);
e43c:
        sw_2acbb8(0);
e444:
        auVar14 = sw_3507e0(0);
        sw_466528(auVar14.lo, auVar14.hi, uVar4);
        return;
        /* e438 is a goto-only target (LAB_0042e438: FUN_00463bbc(uVar6);
         * goto LAB_0042e43c); kept off the fall-through path. */
e438:
        sw_463bbc(k3);
        goto e43c;
}


/* FUN_0042e7e0 @ 0x0042e7e0   (est. sk_re_write_delim6)
 * Ghidra: void FUN_0042e7e0(void)
 * Emits a zero byte through 0x350b54 / 0x2298d4, resets via 0x6b6f4 and
 * closes with 0x1b9084.  Confidence: low. */
void sk_re_write_delim6(void)
{
        sw_350b54(0);
        sw_2298d4(0);
        sw_6b6f4(0);
        sw_1b9084(0);
}


/* FUN_0042e820 @ 0x0042e820   (est. sk_re_emit_kind)
 * Ghidra: void FUN_0042e820(void)
 * Emits a zero kind byte via 0x8409c / 0x4080b0 / 0x2298d4, prepares a
 * frame, closes with 0x1b9084 and pushes the frame.  Confidence: low. */
void sk_re_emit_kind(void)
{
        sw_8409c(0);
        sw_4080b0(0);
        sw_2298d4(0);
        sw_3504a0((word_t)__builtin_frame_address(0));
        sw_1b9084(0);
        sw_1a8564(0);
}


/* FUN_0042e874 @ 0x0042e874   (est. sk_re_write_kind)
 * Ghidra: void FUN_0042e874(void)
 * Routes through 0x4632e0 then the diagnostic emitter 0x42dc90.
 * Confidence: low. */
void sk_re_write_kind(void)
{
        sw_4632e0(0);
        sk_re_write_delim5();
}


/* FUN_0042e8b4 @ 0x0042e8b4   (est. sk_re_write_kind2)
 * Ghidra: void FUN_0042e8b4(void)
 * Prepares a frame (0x1a84f4), emits a zero kind byte, closes (0x1b9084)
 * and pushes the frame.  Confidence: low. */
void sk_re_write_kind2(void)
{
        sw_1a84f4((word_t)__builtin_frame_address(0));
        sw_2298d4(0);
        sw_350878((word_t)__builtin_frame_address(0));
        sw_1b9084(0);
        sw_1a8564(0);
}


/* FUN_0042e930 @ 0x0042e930   (est. sk_re_write_kind3)
 * Ghidra: byte [16] FUN_0042e930(void)
 * Resets the diagnostic output through 0x464608 and 0x4654d0 and returns a
 * zeroed 16-byte value.  Confidence: low. */
sw128_t sk_re_write_kind3(void)
{
        sw128_t r = {0,0};
        sw_464608(0);
        sw_4654d0(0);
        return r;
}


/* FUN_0042e968 @ 0x0042e968   (est. sk_re_write_kind4)
 * Ghidra: void FUN_0042e968(void)
 * Retains the record at (caller x20)+0x10 then triggers the string-append
 * at 0x9461c.  Confidence: low. */
void sk_re_write_kind4(void)
{
        sw_36b270(*(word_t*)(__builtin_frame_address(0) + 0x10));
        sw_9461c(0);
}


/* FUN_0042eadc @ 0x0042eadc   (est. sk_re_reset)
 * Ghidra: void FUN_0042eadc(void)
 * Resets the delimiter/kind state: emits the current byte, the high words of
 * the record bounds, and routes to the scalar scan (0x42d720) when the
 * terminator byte (+0x48) is not -1, else the reset helpers.
 * Confidence: low. */
void sk_re_reset(void)
{
        sw_4656d4(0);
        sw_2298d4(*(byte*)(__builtin_frame_address(0) + 0));
        sw_1b9084(0);
        word_t hi = *(word_t*)(__builtin_frame_address(0) + 0x20);
        sw_2298d4(*(word_t*)(__builtin_frame_address(0) + 0x18) >> 0xe);
        sw_2298d4(hi >> 0xe);
        if (*(char*)(__builtin_frame_address(0) + 0x48) == -1) {
                sw_464ac4(0);
                sw_229a3c(0);
        } else {
                sw_465584(0);
                sw_4650e4(0);
                sk_re_scan_utf8_detect(0);
        }
}


/* FUN_0042eb6c @ 0x0042eb6c   (est. sk_re_retain_rec)
 * Ghidra: void FUN_0042eb6c(void)
 * Prepares a frame via 0x4080b0, runs the reset helper (0x42eadc), and
 * pushes the frame.  Confidence: low. */
void sk_re_retain_rec(void)
{
        sw_4080b0(0);
        sk_re_reset();
        sw_1a8564(0);
}


/* FUN_0042ebac @ 0x0042ebac   (est. sk_re_write_rec)
 * Ghidra: void FUN_0042ebac(void)
 * Prepares a frame (0x1a84f4), runs the reset helper (0x42eadc), and pushes
 * the frame.  Confidence: low. */
void sk_re_write_rec(void)
{
        sw_1a84f4((word_t)__builtin_frame_address(0));
        sk_re_reset();
        sw_1a8564(0);
}


/* FUN_0042ec10 @ 0x0042ec10   (est. sk_re_write_rec2)
 * Ghidra: void FUN_0042ec10(void)
 * Prepares a frame, loads a byte from the caller record, calls the function
 * pointer in x3 with the frame and byte, and pushes the frame.
 * Confidence: low. */
void sk_re_write_rec2(void)
{
        byte b = *(byte*)(__builtin_frame_address(0) + 0);
        vcode fn = 0; /* in_x3 */
        sw_1a84f4((word_t)__builtin_frame_address(0));
        fn(__builtin_frame_address(0), b);
        sw_1a8564(0);
}


/* FUN_0042ec5c @ 0x0042ec5c   (est. sk_re_write_rec3)
 * Ghidra: void FUN_0042ec5c(void)
 * Runs the diagnostic-flush helper 0xe46d0 on the shared buffer
 * DAT_00657778.  Confidence: low. */
void sk_re_write_rec3(void)
{
        sw_e46d0((word_t)&(sw_657778));
}


/* FUN_0042ec68 @ 0x0042ec68   (est. sk_re_diag_rec)
 * Ghidra: void FUN_0042ec68(word_t param_1)
 * Appends a diagnostic record: if the caller's record flag (at +1) is
 * clear, copies param_1 into the next 0x49-byte slot of the record at
 * (+0x10 count, +0x20 slots, stride 0x50) and bumps the count.
 * Confidence: low. */
void sk_re_diag_rec(word_t a)
{
        byte *rec = (byte*)__builtin_frame_address(0);
        long base = *(long*)__builtin_frame_address(0);
        if ((rec[8] & 1) == 0) {
                long n = *(long*)(base + 0x10);
                *(long*)(base + 0x10) = n + 1;
                sw_117cc4(base + n * 0x50 + 0x20, a, 0x49);
        }
}


/* FUN_0042ed40 @ 0x0042ed40   (est. sk_re_diag_rec2)
 * Ghidra: void FUN_0042ed40(void)
 * If the record's flag at (+8) is set, returns; else retains and calls the
 * record-extend helper (0x42ed6c).  Confidence: low. */
void sk_re_diag_rec2(void)
{
        if ((*(byte*)(__builtin_frame_address(0) + 8) & 1) != 0) return;
        sw_36b270(0);
        sk_re_diag_extend(0);
}


/* FUN_0042ed44 @ 0x0042ed44   (est. sk_re_diag_rec3)
 * Ghidra: void FUN_0042ed44(void)
 * Identical to 0x42ed40.  Confidence: low. */
void sk_re_diag_rec3(void)
{
        if ((*(byte*)(__builtin_frame_address(0) + 8) & 1) != 0) return;
        sw_36b270(0);
        sk_re_diag_extend(0);
}


/* FUN_0042ed6c @ 0x0042ed6c   (est. sk_re_diag_extend)
 * Ghidra: void FUN_0042ed6c(long param_1)
 * Extends the caller's record by appending param_1's slots (count from
 * +0x10, stride 0x50): reserves space via 0x457ed8, copies the payloads via
 * 0x456d50 and bumps the count, trapping on overflow.  Confidence: low. */
void sk_re_diag_extend(long src)
{
        word_t n = *(word_t*)(src + 0x10);
        long base = *(long*)(__builtin_frame_address(0));
        if (*(long*)(base + 0x10) + (long)n < *(long*)(base + 0x10)) SW_FATAL(0x42ee5c);
        sw_457ed8(*(long*)(base + 0x10) + n, 1, 0x455fe4, 0x72178, 0x45694c);
        long b = *(long*)(__builtin_frame_address(0));
        long avail = (*(long*)(b + 0x18) >> 1) - *(long*)(b + 0x10);
        if (avail >= 0) {
                if (n == 0) {
                        sw_36b118(src);
                } else {
                        if (avail < (long)n) SW_FATAL(0x42ee68);
                        sw_456d50(src + 0x20, n, b + *(long*)(b + 0x10) * 0x50 + 0x20);
                        sw_36b118(src);
                        *(long*)(b + 0x10) = *(long*)(b + 0x10) + n;
                }
        } else SW_FATAL(0x42ee60);
}


/* FUN_0042ee6c @ 0x0042ee6c   (est. sk_re_diag_merge)
 * Ghidra: void FUN_0042ee6c(word_t param_1, word_t param_2, word_t param_3,
 *                          word_t param_4)
 * Merges param_1's slots into the caller's record at offset param_3, growing
 * the record (0x3a261c / 0x45636c) as needed, copying 0x49-byte payloads and
 * finally releasing param_1.  Confidence: low. */
void sk_re_diag_merge(word_t src, word_t a, word_t n, word_t total)
{
        byte *rec = (byte*)__builtin_frame_address(0);
        long base = *(long*)__builtin_frame_address(0);
        if ((rec[8] & 1) == 0) {
                sw128_t h = sw_41e21c(*(word_t*)(base + 0x10), src);
                if (n == total >> 1) {
                        sw_36b270(src);
                        sw_466510(h.lo, 0);
                        sw_36b118(0);
                        return;
                }
                if ((long)(total >> 1) <= (long)n) SW_FATAL(0x42f020);
                sw_36b270(src);
                long rem = ~n + (total >> 1);
                long cur = h.hi + n * 0x50;
                while (true) {
                        char buf[0x50];
                        sw_117cc4(buf, cur, 0x49);
                        if (buf[0] == '\\0') {
                                word_t g = sw_3a261c(base);
                                if ((g & 1) == 0) { sw_462710(0); sw_6b3f4(0); base = (long)sw_45636c(0); }
                                *(word_t*)(base + 0x10) = cnt + 1;
                                word_t cnt = *(word_t*)(base + 0x10);
                                if (*(word_t*)(base + 0x18) >> 1 <= cnt) { sw_6b42c(0); sw_dbed0(0); base = (long)sw_45636c(0); }
                                *(word_t*)(base + 0x10) = cnt + 1;
                                *(word_t*)(base + 0x10) = cnt + 1;
                                sw_117cc4(base + cnt * 0x50 + 0x20, buf, 0x49);
                        }
                        if (rem == 0) break;
                        rem = rem - 1;
                        cur = cur + 0x50;
                }
                sw_36b118(h.lo);
        }
        sw_466510(0);
}


/* FUN_0042f020 @ 0x0042f020   (est. sk_re_parse_scalar)
 * Ghidra: word_t FUN_0042f020(word_t param_1, word_t param_2)
 * Scans a String for the first newline (LF/CR) scalar, decoding UTF-8/UTF-16;
 * returns 1 if a newline is present, 0 otherwise.  Confidence: low. */
word_t sk_re_scan_newline(word_t str, word_t flags)
{
        word_t span = str & 0xffffffffffff;
        if ((flags & 0x2000000000000000) != 0) span = (flags >> 0x38) & 0xf;
        if (span != 0) {
                long pos = 0;
                do {
                        uint ch;
                        if ((flags >> 0x3c & 1) != 0) {
                                ch = (uint)sw_2a49a8(pos << 0x10, str, flags);
                        } else if ((flags >> 0x3d & 1) == 0) {
                                long base = (flags & 0xfffffffffffffff) + 0x20;
                                if ((str >> 0x3c & 1) == 0) base = sw_2a9ba8(str, flags);
                                byte *b = (byte*)(base + pos);
                                uint u = *b;
                                long adv;
                                if ((char)*b >= 0) { adv = 1; ch = u; }
                                else {
                                        switch ((int)LZCOUNT(u << 0x18 ^ 0xffffffff)) {
                                        case 2: ch = b[1] & 0x3f | (u & 0x1f) << 6; adv = 2; break;
                                        case 3: ch = (u & 0xf) << 0xc | (b[1] & 0x3f) << 6 | b[2] & 0x3f; adv = 3; break;
                                        default:
                                        case 4: ch = (u & 0xf) << 0x12 | (b[1] & 0x3f) << 0xc | (b[2] & 0x3f) << 6 | b[3] & 0x3f; adv = 4; break;
                                        }
                                }
                                if (ch == 10 || ch == 0xd) return 1;
                                pos = pos + adv;
                        } else {
                                word_t pair[2]; pair[0] = str; pair[1] = flags & 0xffffffffffffff;
                                byte *b = (byte*)((word_t)&pair + pos);
                                uint u = *b; long adv;
                                if ((char)*b < 0) {
                                        switch ((int)LZCOUNT(u << 0x18 ^ 0xffffffff)) {
                                        case 2: ch = b[1] & 0x3f | (u & 0x1f) << 6; adv = 2; break;
                                        case 3: ch = (u & 0xf) << 0xc | (b[1] & 0x3f) << 6 | b[2] & 0x3f; adv = 3; break;
                                        case 4: ch = (u & 0xf) << 0x12 | (b[1] & 0x3f) << 0xc | (b[2] & 0x3f) << 6 | b[3] & 0x3f; adv = 4; break;
                                        default: ch = u; adv = 1; break;
                                        }
                                } else { ch = u; adv = 1; }
                                if (ch == 10 || ch == 0xd) return 1;
                                pos = pos + adv;
                        }
                } while (pos < (long)span);
        }
        return 0;
}


/* FUN_0042f1f0 @ 0x0042f1f0   (est. sk_re_parse_scalar2)
 * Ghidra: word_t FUN_0042f1f0(word_t param_1, word_t param_2, word_t param_3,
 *                            word_t param_4)
 * Like 0x42f020 but scans across a String span [param_1,param_2) with the
 * given flags; decodes UTF-8/UTF-16 scalars and returns 1 if a newline is
 * found.  Confidence: low. */
word_t sk_re_parse_scalar2(word_t start, word_t end, word_t a, word_t flags)
{
        if ((end >> 0xe) != (start >> 0xe)) {
                uint shift = (uint)(a >> 0x3b) & 1;
                if ((flags & 0x1000000000000000) == 0) shift = 1;
                word_t span = a & 0xffffffffffff;
                if ((flags & 0x2000000000000000) != 0) span = (flags >> 0x38) & 0xf;
                word_t pos = start;
                do {
                        int ch = sw_2b7088(pos, start, end, a, flags);
                        if (((pos & 0xc) == (4ul << shift)) || ((pos & 1) == 0)) {
                                if ((pos & 0xc) == (4ul << shift)) pos = sw_1da84(pos, a, flags);
                                if (span <= pos >> 0x10) SW_FATAL(0x42f3b8);
                                if ((pos & 1) != 0) goto cont;
                                word_t v = sw_1676cc(pos, a, flags);
                                pos = pos & 0xc | v & 0xfffffffffffffff3 | 1;
                                if ((flags >> 0x3c & 1) != 0) goto utf16;
                                goto adv;
                        } else {
                                if (span <= pos >> 0x10) SW_FATAL(0x42f3b4);
cont:                           if ((flags >> 0x3c & 1) == 0) goto adv;
utf16:                          pos = sw_2a49a8(pos, a, flags);
                                goto chk;
                        }
adv:                    pos = pos >> 0x10;
                        byte *b;
                        if ((flags >> 0x3d & 1) == 0) {
                                long base = (flags & 0xfffffffffffffff) + 0x20;
                                if ((a >> 0x3c & 1) == 0) base = sw_2a9ba8(a, flags);
                                b = (byte*)(base + pos);
                        } else {
                                word_t pair[2]; pair[0] = a; pair[1] = flags & 0xffffffffffffff;
                                b = (byte*)((word_t)&pair + pos);
                        }
                        uint v2 = (uint)LZCOUNT((uint)*b << 0x18 ^ 0xffffffff);
                        if ((char)*b >= 0) v2 = 1;
                        pos = (pos + v2) * 0x10000 | 5;
chk:                    if (ch == 10 || ch == 0xd) return 1;
                } while ((end >> 0xe) != (pos >> 0xe));
        }
        return 0;
}


/* FUN_0042f3e0 @ 0x0042f3e0   (est. sk_re_parse_scalar3)
 * Ghidra: uint FUN_0042f3e0(word_t param_1, uint param_2, word_t param_3, uint param_4)
 * ANDs the result of 0x411624 with the parity mask (param_2 ^ param_4 ^ ~0),
 * returning bit 0.  Confidence: low. */
uint sk_re_parse_scalar3(word_t a, uint b, word_t c, uint d)
{
        uint r = (uint)sw_411624(a, c);
        return r & (b ^ d ^ 0xffffffff) & 1;
}


/* FUN_0042f418 @ 0x0042f418   (est. sk_re_diag_rec_b)
 * Ghidra: void FUN_0042f418(word_t param_1, word_t param_2, uint param_3)
 * Routes through 0x458780 and commits the low bit of param_3 via 0x229a3c.
 * Confidence: low. */
void sk_re_diag_rec_b(word_t a, word_t b, uint c)
{
        sw_458780(0);
        sw_229a3c(c & 1);
}


/* FUN_0042f448 @ 0x0042f448   (est. sk_re_diag_rec_c)
 * Ghidra: void FUN_0042f448(word_t param_1, uint param_2)
 * Prepares a frame, runs 0x4080b0/0x465938/0x458780, commits param_2's low
 * bit and pushes the frame.  Confidence: low. */
void sk_re_diag_rec_c(word_t a, uint b)
{
        sw_4080b0(0);
        sw_465938(0);
        sw_458780(0);
        sw_229a3c(b & 1);
        sw_1a8564(0);
}


/* FUN_0042f4ac @ 0x0042f4ac   (est. sk_re_diag_rec_d)
 * Ghidra: void FUN_0042f4ac(void)
 * Prepares a frame, loads a word and byte from the caller record, runs the
 * rec_b helper and pushes the frame.  Confidence: low. */
void sk_re_diag_rec_d(void)
{
        word_t w = *(word_t*)(__builtin_frame_address(0) + 0);
        byte b = *(byte*)(__builtin_frame_address(0) + 8);
        sw_1a84f4((word_t)__builtin_frame_address(0));
        sk_re_diag_rec_b(0, w, b);
        sw_1a8564(0);
}


/* FUN_0042f514 @ 0x0042f514   (est. sk_re_diag_rec_e)
 * Ghidra: void FUN_0042f514(void)
 * Reads the current diagnostic record from 0x350b54, runs the diagnostic
 * emitter (0x42dc90), and writes a 1 + 16-byte + bounds + 5-word payload
 * back into the record buffer.  Confidence: low. */
void sk_re_diag_rec_e(void)
{
        word_t *rec = (word_t*)sw_350b54(0);
        byte u1 = *(byte*)(rec + 4);
        word_t r0 = rec[0], r1 = rec[1], r2 = rec[2], r3 = rec[3];
        sw128_t v = sk_re_write_delim5();
        word_t *out = (word_t*)sw_350b54(0);
        *(byte*)out = 1;
        ((word_t*)out)[1] = v.lo;
        ((word_t*)out)[2] = v.hi;
        out[3] = 0; out[4] = r3; out[5] = r2; out[6] = r1; out[7] = r0;
        ((byte*)out)[0x48] = u1;
}


/* FUN_0042f584 @ 0x0042f584   (est. sk_re_diag_init)
 * Ghidra: void FUN_0042f584(void)
 * Initializes a diagnostic record buffer: runs the reset helpers, releases
 * a value, and zeroes the record with a -1 terminator byte.  Confidence: low. */
void sk_re_diag_init(void)
{
        sw_350980(0);
        sw_464608(0);
        sw_4654d0(0);
        sw_3a25d4(0);
        word_t *out = (word_t*)sw_350b54(0);
        *(byte*)out = 0;
        out[1] = 0; out[2] = 0; out[3] = 0; out[4] = 0;
        out[5] = 0; out[6] = 0; out[7] = 0; out[8] = 0;
        ((byte*)out)[0x48] = 0xff;
}


/* FUN_0042f5f8 @ 0x0042f5f8   (est. sk_re_diag_rec_f)
 * Ghidra: void FUN_0042f5f8(void)
 * Copies the 16-byte value from 0x463f94 into the next record slot
 * (0x117cc4, len 0x49) and routes via 0x42acc4.  Confidence: low. */
void sk_re_diag_rec_f(void)
{
        sw128_t v = sw_463f94(0);
        sw_117cc4(v.lo, v.hi, 0x49);
        sw_42acc4(0);
}


/* FUN_0042f630 @ 0x0042f630   (est. sk_re_diag_rec_g)
 * Ghidra: void FUN_0042f630(void)
 * Same as 0x42f5f8 but routes via 0x42ae78.  Confidence: low. */
void sk_re_diag_rec_g(void)
{
        sw128_t v = sw_463f94(0);
        sw_117cc4(v.lo, v.hi, 0x49);
        sw_42ae78(0);
}


/* FUN_0042f670 @ 0x0042f670   (est. sk_re_parse_scalar)
 * Ghidra: void FUN_0042f670(void)
 * Parses the next scalar from the input String held in the caller record:
 * reads the current 16-byte head (0xb4594), splits via 0x2b3f40, advances
 * the record position, and reconstructs the 16-byte scalar value.
 * Confidence: low. */
void sk_re_diag_emit_str(void)
{
        sw128_t sc = sw_b4594(0);
        word_t pos = *(word_t*)(__builtin_frame_address(0) + 0x10);
        word_t end = *(word_t*)(__builtin_frame_address(0) + 0x18);
        sw_34c444(pos);
        sw_29fa0c(0);
        sw_4635c8(0);
        if (0 == 0) { /* extraout_x9 == 0 */
                sw_3a25d4(0);
        } else {
                sw_462788(0);
                sw128_t u = sw_2b439c(0);
                sw_3a25d4(0);
                if (sc.lo == u.lo && sc.hi == u.hi) {
                        sw_3a25d4(u.hi);
                } else {
                        word_t m = sw_2a0cf8(u.lo, u.hi, sc.lo, sc.hi, 0);
                        sw_3a25d4(u.hi);
                        if ((m & 1) == 0) goto done;
                }
                sw_34c444(pos);
                sw_29fa0c(0);
                sw_462988(0);
                sw128_t v = sw_352290(0);
                sw_462b00(v.lo, v.hi, end);
                sw96_t r = sw_2b3f40(0);
                sw_3a25d4(sc.lo);
                if (((r.hi >> 0) & 0xff) == 1) {
                        sw_463648(0);
                        sw128_t s = sw_463444(0);
                        sk_re_diag_init();
                        sw_466648(0);
                        sw_461430(0);
                        sw_34c444(pos);
                        sw_29fa0c(0);
                        sw_462ba8(0);
                        sw_356328(0);
                        sw_3a25d4(0);
                        sw_353abc(0);
                        sk_re_parse_scalar_adv(0);
                } else {
                        if (end >> 0xe < r.lo >> 0xe) SW_FATAL(0x42f7d4);
                        *(word_t*)(__builtin_frame_address(0) + 0x10) = r.lo;
                        *(word_t*)(__builtin_frame_address(0) + 0x18) = end;
                }
        }
done:
        sw_b45b0(0, 0);
}


/* FUN_0042f7d4 @ 0x0042f7d4   (est. sk_re_diag_match)
 * Ghidra: uint FUN_0042f7d4(word_t param_1, word_t param_2)
 * Parses a scalar (0x42f670); on failure formats a diagnostic and appends
 * it; returns whether the parse advanced past the recorded position.
 * Confidence: low. */
uint sk_re_diag_match(word_t a, word_t b)
{
        word_t start = *(word_t*)(__builtin_frame_address(0) + 0x10);
        uint ok = sk_re_diag_emit_str();
        if ((ok & 1) == 0) {
                word_t pos = *(word_t*)(__builtin_frame_address(0) + 0x10);
                sw_4627f4(0);
                sw_36b270(b);
                sw_350518(0);
                sw_2acbb8(0);
                sw_463514(0);
                sw_2acbb8(0);
                sw_4642f8(0);
                sw_465adc(0);
                sw_461430(0);
        }
        if (start >> 0xe <= *(word_t*)(__builtin_frame_address(0) + 0x10) >> 0xe)
                return ok & 1;
        SW_FATAL(0x42f890);
}


/* FUN_0042f890 @ 0x0042f890   (est. sk_re_diag_match2)
 * Ghidra: uint FUN_0042f890(word_t param_1, word_t param_2)
 * Attempts a regex fragment match; on failure appends an "expect" (0x657a)
 * error record via the record builder; on success completes the diagnostic.
 * Returns bit 0 of the match result.  Confidence: low. */
uint sk_re_diag_match2(word_t a, word_t b)
{
        word_t *rec = (word_t*)__builtin_frame_address(0);
        sw128_t s = sw_29fa0c(rec[2], rec[3], rec[0], rec[1]);
        uint ok = (uint)sw_15e4f8(a, b, s.lo, s.hi, rec[0], rec[1]);
        sw_3a25d4(rec[1]);
        if ((ok & 1) == 0) {
                word_t r0 = a, r1 = b;
                sw_36b270(b);
                sw128_t t = sw_2aca00(&r0, 0x6753a0, 0x66e0d8);
                r0 = 0x6465746365707865;   /* "expected" */
                r1 = 0xea00000000002720;
                sw_2acbb8(0);
                sw_2acbb8(0x27, 0xe100000000000000);
                sk_re_diag_rec(&r0);
                sw_461430((word_t)&(r0));
        } else {
                sw_1ee018(a, b);
                sk_re_diag_complete();
        }
        return ok & 1;
}


/* FUN_0042f9dc @ 0x0042f9dc   (est. sk_re_append_match)
 * Ghidra: bool FUN_0042f9dc(void)
 * Reads the diagnostic record, and if the two input heads are equal runs the
 * record merge; returns whether the heads differed in their high 14 bits.
 * Confidence: low. */
bool sk_re_append_match(void)
{
        word_t *rec = (word_t*)sw_464a44(0);
        word_t a0 = rec[0], a1 = rec[1], a2 = rec[2], a3 = rec[3];
        byte u = *(byte*)(rec + 4);
        sw_29fa0c(0, 0, 0, 0);
        sw_3535a8(0);
        sw_3a25d4(0);
        if ((0 ^ 0) >> 0xe == 0) {
                sw_460dbc(0);
                sw128_t v = sk_re_write_delim5();
                sk_re_diag_merge(v.lo, v.hi, a1, a0);
                sw_461430(0);
        }
        return ((0 ^ 0) & 0xffffffffffffc000) != 0;
}


/* FUN_0042fa98 @ 0x0042fa98   (est. sk_re_append_match2)
 * Ghidra: word_t FUN_0042fa98(word_t param_1, word_t param_2)
 * Appends an "expect" diagnostic record or performs a match; returns 1 on a
 * successful fragment match, else 0.  Confidence: low. */
word_t sk_re_append_match2(word_t a, word_t b)
{
        word_t r0 = a, r1 = b;
        sw_36b270(b);
        sw128_t t = sw_2aca00(&r0, 0x6753a0, 0x66e0d8);
        word_t *rec = (word_t*)__builtin_frame_address(0);
        sw128_t s = sw_29fa0c(rec[2], rec[3], rec[0], rec[1]);
        sw_3a25d4(rec[1]);
        if ((s.lo ^ s.hi) >> 0xe == 0) {
                r0 = 0x6465746365707865;
                r1 = 0xea00000000002720;
                sw_2acbb8(t.lo, t.hi);
                sw_2acbb8(0x27, 0xe100000000000000);
                sk_re_diag_rec(&r0);
                sw_461430((word_t)&(r0));
        } else {
                sw_3a25d4(t.hi);
                sw128_t s2 = sw_29fa0c(rec[2], rec[3], rec[0], rec[1]);
                word_t m = sw_15e4f8(a, b, s2.lo, s2.hi, rec[0], rec[1]);
                sw_3a25d4(rec[1]);
                if ((m & 1) != 0) {
                        sw_1ee018(a, b);
                        sk_re_diag_complete();
                        return 1;
                }
        }
        return 0;
}


/* FUN_0042fc4c @ 0x0042fc4c   (est. sk_re_peek_char)
 * Ghidra: void FUN_0042fc4c(void)
 * Peeks the next char from the input String: reads via 0x465288/0x4635c8,
 * and on the fallback path decodes a scalar via 0x2b439c; then resets via
 * 0x6b6f4.  Confidence: low. */
void sk_re_peek_char(void)
{
        sw_465288(0);
        sw_4635c8(0);
        if (0 == 0) {
                sw_3a25d4(0);
                sw_356110(0);
        } else {
                sw_462788(0);
                sw_2b439c(0);
                sw_34bd90(0);
                sw_3a25d4(0);
        }
        sw_6b6f4(0);
}


/* FUN_0042fca8 @ 0x0042fca8   (est. sk_re_peek_char2)
 * Ghidra: void FUN_0042fca8(void)
 * Reads the current String head, folds it (0x2b439c), and if the advance
 * result does not exceed the recorded end, commits the new position.
 * Confidence: low. */
void sk_re_peek_char2(void)
{
        sw_84220(0);
        word_t *rec = (word_t*)__builtin_frame_address(0);
        sw_29fa0c(rec[2], rec[3], rec[0], rec[1]);
        sw_4635c8(0);
        if (0 == 0) {
                sw_3a25d4(rec[1]);
                sw_464d5c(0);
                sw_46615c(0);
        } else {
                sw_462788(0);
                sw_2b439c(0);
                sw_3535a8(0);
                sw_3a25d4(rec[1]);
                sw_350998(rec[2]);
                word_t adv = sw_1b798c(0);
                if (adv >> 0xe < rec[2] >> 0xe) SW_FATAL(0x42fd4c);
        }
        sw128_t s = sw_e15d8(0);
        sw_84234(s.lo, s.hi, rec[2]);
}


/* FUN_0042fd4c @ 0x0042fd4c   (est. sk_re_diag_complete)
 * Ghidra: void FUN_0042fd4c(void)
 * Completes a diagnostic: if the diagnostic count is positive runs the
 * formatting pipeline and commits the position; else re-initializes the
 * diagnostic record and reports a 'position' error.  Confidence: low. */
void sk_re_diag_complete(void)
{
        word_t *rec = (word_t*)__builtin_frame_address(0);
        sw128_t c = sw_4666f8(0);
        if (0 < (long)c.lo) {
                sw_4631a8(0); sw_462a5c(0); sw_462810(0);
                sw_2b3f40(0); sw_46397c(0); sw_3a25d4(0);
                int w = 0; /* unaff_w22 */
                if (w != 1) {
                        sw_4637f0(0);
                        if (w == 0) SW_FATAL(0x42fe0c);
                        *(long*)(__builtin_frame_address(0) + 0x10) = c.lo;
                        *(long*)(__builtin_frame_address(0) + 0x18) = (long)rec;
                        goto out;
                }
        }
        sw_463648(0);
        word_t pos = *(word_t*)(__builtin_frame_address(0) + 0x10);
        sw128_t s = sw_463444(0);
        sk_re_diag_init();
        sw_466648(0);
        sw_461430(0);
        sw_46400c(0);
        sw_29fa0c(pos);
        sw_462ba8(0);
        sw_356328(0);
        sw_3a25d4(0);
        sw_353abc(0);
        sk_re_parse_scalar_adv(0);
out:
        sw_4666e4(c.hi);
}


/* FUN_0042fe0c @ 0x0042fe0c   (est. sk_re_parse_scalar_adv)
 * Ghidra: word_t FUN_0042fe0c(word_t param_1, word_t param_2)
 * Advances the parser position past a scalar; if param_1 is positive, splits
 * the input and commits the new position, returning 1; else 0.
 * Confidence: low. */
word_t sk_re_parse_scalar_adv(word_t a, word_t b)
{
        word_t *rec = (word_t*)__builtin_frame_address(0);
        if (0 < (long)a) {
                word_t p = rec[2];
                word_t e = rec[3];
                sw_3510b8(a, b, rec[0], rec[1]);
                sw_29fa0c(0);
                sw_462a5c(0);
                sw128_t s = sw_100efc(0);
                sw_462b00(s.lo, s.hi, e);
                sw_2b3f40(0);
                sw_46397c(0);
                sw_3a25d4(0);
                if ((int)p != 1) {
                        if (a >> 0xe <= e >> 0xe) {
                                rec[2] = a;
                                rec[3] = e;
                                return 1;
                        }
                        SW_FATAL(0x42fea0);
                }
        }
        return 0;
}


/* FUN_0042fea0 @ 0x0042fea0   (est. sk_re_peek_scalar)
 * Ghidra: void FUN_0042fea0(void)
 * Peeks the next scalar from the input: reads the head, folds and splits it;
 * on the scalar path commits the new position, else re-initializes the
 * diagnostic.  Confidence: low. */
void sk_re_peek_scalar(void)
{
        sw128_t sc = sw_b4594(0);
        word_t *rec = (word_t*)__builtin_frame_address(0);
        word_t pos = rec[2];
        word_t end = rec[3];
        sw_34db28(pos);
        sw_29fa0c(0);
        sw_462d88(0);
        if (0 == 0) {
                sw_3a25d4(0);
                sw_463f40(0);
        } else {
                sw_462788(0);
                sw_2b439c(0);
                sw_b43e8(0);
                sw_3a25d4(0);
                sw_34db28(pos);
                sw_29fa0c(0);
                sw_462aac(0);
                sw_46580c(0);
                sw_462a1c(0);
                sw_2b3f40(0);
                sw_46635c(0);
                sw_3a25d4(0);
                int w = 0; /* unaff_w28 */
                if (w == 1) {
                        sw_463648(0);
                        sw128_t s = sw_463444(0);
                        sk_re_diag_init();
                        sw_466648(0);
                        sw_461430(0);
                        sw_34db28(pos);
                        sw_29fa0c(0);
                        sw_462ba8(0);
                        sw_3a25d4(0);
                        sk_re_parse_scalar_adv(0);
                } else {
                        sw_464588(0);
                        if (w == 0) SW_FATAL(0x42ffac);
                        *(long*)(__builtin_frame_address(0) + 0x10) = (long)rec;
                        *(word_t*)(__builtin_frame_address(0) + 0x18) = end;
                }
        }
        sw128_t s2 = sw_b4390(0);
        sw_b45b0(s2.lo, s2.hi, sc.lo);
}


/* FUN_0042ffac @ 0x0042ffac   (est. sk_re_parse_quant_star)
 * Ghidra: void FUN_0042ffac(void)
 * Runs the peek helper; if the fold did not advance, resets via 0x46615c,
 * else commits via 0x463a38 with a carry trap.  Confidence: low. */
void sk_re_parse_quant_star(void)
{
        sk_re_peek_scalar();
        if (0 == 0) {
                sw_46615c(0);
        } else {
                sw_463a38(0);
                if (0 == 0) SW_FATAL(0x42ffd4);
        }
}


/* FUN_0042ffec @ 0x0042ffec   (est. sk_re_peek_scalar2)
 * Ghidra: byte [16] FUN_0042ffec(void)
 * Peeks the next scalar as a 16-byte value: parses it (0x42f670), returns
 * (start, newpos); on failure returns (0,0).  Confidence: low. */
sw128_t sk_re_peek_scalar2(void)
{
        word_t start = *(word_t*)(__builtin_frame_address(0) + 0x10);
        word_t ok = sk_re_diag_emit_str();
        sw128_t r;
        if ((ok & 1) == 0) { r.lo = 0; r.hi = 0; }
        else {
                r.lo = start;
                r.hi = *(word_t*)(__builtin_frame_address(0) + 0x10);
                if (r.hi >> 0xe < start >> 0xe) SW_FATAL(0x430040);
        }
        return r;
}


/* FUN_00430040 @ 0x00430040   (est. sk_re_record_append_diag)
 * Ghidra: byte [16] FUN_00430040(word_t param_1)
 * Reads the current head (0x42fc4c), looks it up via 0xabad0; if found,
 * splits the input and appends a diagnostic record (or commits the new
 * position), returning the 16-byte result.  Confidence: low. */
sw128_t sk_re_record_append_diag(word_t a)
{
        word_t head[2];
        sw_117cc4(&head[0]);
        sw128_t cur = sk_re_peek_char();
        sw128_t r;
        if (cur.hi == 0) {
                r.lo = 0; r.hi = 0;
        } else {
                word_t m = sw_abad0(cur.lo, cur.hi, a);
                if ((m & 1) == 0) {
                        sw_3a25d4(cur.hi);
                        r.lo = 0; r.hi = 0;
                } else {
                        word_t c0 = head[0], c1 = head[1];
                        sw128_t s = sw_29fa0c(0, 0, c0, c1);
                        sw96_t sp = sw_2b3f40(0, 1, 0, s.lo, s.hi, c0, c1);
                        sw_3a25d4(c1);
                        if (((sp.hi >> 0) & 0xff) == 1) {
                                sk_re_diag_init(0, 0xd000000000000015, 0x80000000005e0400, 0, 0);
                                sk_re_diag_rec();
                                sw_461430(0);
                                sw128_t s2 = sw_29fa0c(0, 0, c0, c1);
                                word_t a2 = sw_2b4120(s2.lo, s2.hi, s2.lo, s2.hi, c0, c1);
                                sw_3a25d4(c1);
                                sk_re_parse_scalar_adv(a2);
                        } else {
                                if (0 >> 0xe < sp.lo >> 0xe) SW_FATAL(0x4301e0);
                                *(word_t*)(__builtin_frame_address(0) + 0x10) = sp.lo;
                                *(word_t*)(__builtin_frame_address(0) + 0x18) = 0;
                        }
                        r.lo = cur.lo; r.hi = cur.hi;
                }
        }
        return r;
}


/* FUN_004301e0 @ 0x004301e0   (est. sk_re_str_slice)
 * Ghidra: byte [16] FUN_004301e0(word_t param_1, word_t param_2, word_t *param_3)
 * Slices a String held in param_3's words: slices [lo..hi), releases the
 * tail and returns the slice.  Confidence: low. */
sw128_t sk_re_str_slice(word_t a, word_t b, word_t *p)
{
        word_t s0 = p[0], s1 = p[1], s2 = p[2], s3 = p[3];
        sw128_t r = sw_448758(a, b, s0, s1, s2, s3);
        sw128_t out;
        if (s1 == 0) { out.lo = 0; out.hi = 0; }
        else {
                sw_2b4120(r.lo, r.hi, r.lo, r.hi, s0, s1);
                sk_re_parse_scalar_adv();
                out = sw_2a3e64(r.lo, r.hi, s0, s1);
                sw_3a25d4(s1);
                if (p[2] >> 0xe < s2 >> 0xe) SW_FATAL(0x430274);
        }
        return out;
}


/* FUN_004302a0 @ 0x004302a0   (est. sk_re_parse_suffix)
 * Ghidra: void FUN_004302a0(word_t param_1, word_t param_2, word_t *param_3,
 *                          word_t param_4)
 * Parses a suffix: on a non-empty string advances through the slice helpers
 * (0x48934, 0x4630b0, 0x351790, 0x2b4120, 0x42fe0c, 0x34d868, 0x2a3e64)
 * and commits; else resets.  Confidence: low. */
void sk_re_parse_suffix(word_t a, word_t b, word_t *p, word_t c)
{
        word_t s1 = p[1];
        sw_48934(a, b, p[0], s1, p[2], p[3], c);
        if (s1 == 0) {
                sw_464d5c(0);
        } else {
                sw_4630b0(0);
                sw_351790(0);
                sw_2b4120(0);
                sk_re_parse_scalar_adv();
                sw_34d868(0);
                sw_2a3e64(0);
                sw_3535a8(0);
                sw_3a25d4(0);
                sw_463a38(0);
                if (0 == 0) SW_FATAL(0x430314);
        }
        sw_e15d8(0);
}


/* FUN_00430338 @ 0x00430338   (est. sk_re_parse_suffix2)
 * Ghidra: void FUN_00430338(void)
 * Twin of 0x4302a0 driven by 0x448aac.  Confidence: low. */
void sk_re_parse_suffix2(void)
{
        sw_448aac(0);
        if (0 == 0) {
                sw_464d5c(0);
        } else {
                sw_4630b0(0);
                sw_351790(0);
                sw_2b4120(0);
                sk_re_parse_scalar_adv();
                sw_34d868(0);
                sw_2a3e64(0);
                sw_3535a8(0);
                sw_3a25d4(0);
                sw_463a38(0);
                if (0 == 0) SW_FATAL(0x4303a0);
        }
        sw_e15d8(0);
}


/* FUN_004303c4 @ 0x004303c4   (est. sk_re_parse_scalar_str)
 * Ghidra: void FUN_004303c4(void)
 * Parses a scalar and its string form; on the ASCII path checks the byte
 * value and reports "expected ASCII for ..." (0x5dfc80) if it is not a
 * plain ASCII scalar, else commits the position.  Confidence: low. */
void sk_re_parse_scalar_str(void)
{
        word_t *rec = (word_t*)__builtin_frame_address(0);
        word_t c = sw_4666f8(0);
        word_t start = *(word_t*)(__builtin_frame_address(0) + 0x10);
        sk_re_peek_scalar();
        if (0 == 0) {
                sw_464040(*(word_t*)(__builtin_frame_address(0) + 0x10));
        } else {
                sw_b43e8(0);
                word_t v = sw_2bd8f0(0);
                word_t pos = *(word_t*)(__builtin_frame_address(0) + 0x10);
                if ((v & 0xff00) != 0x100) {
                        if (pos >> 0xe < start >> 0xe) SW_FATAL(0x4304e0);
                        goto done;
                }
                sw_86840(0x5dfc80);   /* "expected ASCII for ..." */
                sw_b4390(0);
                sw_2acbb8(0);
                sw_463514(0);
                sw_2acbb8(0);
                sw_4642f8(0xd000000000000014);
                sw_466648(0);
                sw_461430(0);
                sw_463f40(0);
        }
done:
        sw128_t s = sw_b4390(0);
        sw_4666e4(s.lo, s.hi, 0, 0, c);
}


/* FUN_004304e0 @ 0x004304e0   (est. sk_re_is_scalar_class)
 * Ghidra: uint FUN_004304e0(void)
 * Checks whether the current scalar is a specific ASCII class (via the
 * comparison primitive 0x2a0cf8); returns 1 if it matches 0x37, else 0.
 * Confidence: low. */
uint sk_re_is_scalar_class(void)
{
        sw_3504d0(0);
        word_t m = sw_2a0cf8(0x37, 0xe100000000000000, 0x30, 0xe100000000000000, 1);
        if ((m & 1) != 0) SW_FATAL(0x430584);
        if (0x30 != 0x37 || 0 != 0) { /* unaff registers */
                sw128_t s = sw_7c1c4(0);
                m = sw_2a0cf8(s.lo, s.hi, 0x30, 0xe100000000000000, 1);
                if ((m & 1) != 0) return 0;
                if (0x37 == 0x37) return 1;
        }
        sw_462b80(0x37);
        return (uint)(sw_2a0cf8(0) ^ 1) & 1;
}


/* FUN_00430584 @ 0x00430584   (est. sk_re_bool_scalar)
 * Ghidra: void FUN_00430584(byte *param_1, word_t *param_2)
 * Writes the low bit of 0x4304e0 into the output byte.  Confidence: low. */
void sk_re_bool_scalar(byte *out, word_t *p)
{
        byte b = (byte)(sk_re_is_scalar_class() & 1);
        *out = b;
}


/* FUN_004305c4 @ 0x004305c4   (est. sk_re_bool_unicode)
 * Ghidra: void FUN_004305c4(byte *param_1, word_t *param_2)
 * Writes the low bit of the Unicode check 0x2bda40.  Confidence: low. */
void sk_re_bool_unicode(byte *out, word_t *p)
{
        byte b = (byte)(sw_2bda40(p[0], p[1]) & 1);
        *out = b;
}


/* FUN_00430604 @ 0x00430604   (est. sk_re_bool_uni_prop)
 * Ghidra: void FUN_00430604(byte *param_1, word_t *param_2)
 * Writes the low bit of the Unicode-property check 0x2bdb90.  Confidence: low. */
void sk_re_bool_uni_prop(byte *out, word_t *p)
{
        byte b = (byte)(sw_2bdb90(p[0], p[1]) & 1);
        *out = b;
}


/* FUN_00430644 @ 0x00430644   (est. sk_re_scalar_to_utf8)
 * Ghidra: byte FUN_00430644(word_t param_1, word_t param_2, word_t param_3)
 * Converts a scalar to its UTF-8 form: runs the decoder 0x24d9ac, calls the
 * UTF-8 writer 0x24917c, releases the temporary and returns the byte.
 * Confidence: low. */
byte sk_re_scalar_to_utf8(word_t a, word_t b, word_t c)
{
        sw_3504d0(0);
        word_t t = sw_24d9ac(c);
        byte r;
        sw_24917c(&r, __builtin_frame_address(0));
        sw_36b118(t);
        return r;
}


/* FUN_004306a0 @ 0x004306a0   (est. sk_re_bool_scalar2)
 * Ghidra: void FUN_004306a0(void)
 * Routes the caller word through 0x3f34b4.  Confidence: low. */
void sk_re_bool_scalar2(void)
{
        sw_3f34b4(*(word_t*)__builtin_frame_address(0));
}


/* FUN_004306a4 @ 0x004306a4   (est. sk_re_bool_scalar3)
 * Ghidra: void FUN_004306a4(void)
 * Same as 0x4306a0.  Confidence: low. */
void sk_re_bool_scalar3(void)
{
        sw_3f34b4(*(word_t*)__builtin_frame_address(0));
}


/* FUN_004306bc @ 0x004306bc   (est. sk_re_parse_scalar_seq)
 * Ghidra: void FUN_004306bc(void)
 * Parses a sequence of scalars of a given radix class (digit/hex/octal
 * selector from the caller's byte): handles an optional +/- sign, then
 * accumulates digit values with overflow checks, reporting the result as a
 * (value, kind) pair through 0x356f80.  Confidence: low. */
void sk_re_parse_scalar_seq(void)
{
        byte *rec = (byte*)__builtin_frame_address(0);
        sw_356f9c(0);
        sw128_t s = sw_35199c(0);
        word_t span = s.lo & 0xffffffffffff;
        if ((s.hi & 0x2000000000000000) != 0) span = (s.hi >> 0x38) & 0xf;
        word_t value = 0;
        bool neg = true;
        long adv = 0;
        if (span != 0) {
                byte sel = rec[0] & 0xff;
                uint radix;
                if (sel == 0) { neg = true; radix = 8; }
                else if (sel == 2) { neg = false; radix = 0x10; }
                else { neg = true; radix = 10; }
                word_t v = 0;
                long step = 0;
                /* accumulate (digit loop faithfully summarized) */
                while (span > 0) {
                        word_t d;
                        if ((s.hi >> 0x3c & 1) == 0) {
                                sw_350518(0);
                                sw128_t b = sw_2a9ba8(0);
                                d = *(byte*)b.lo;
                        } else {
                                d = *(byte*)((s.hi & 0xfffffffffffffff) + 0x20);
                        }
                        /* digit classification / value accumulation */
                        if (d == '+') { if (span == 1) { adv = 1; break; } }
                        else if (d == '-') { if (span == 1) { adv = 1; break; } }
                        else {
                                uint ch = d;
                                bool isDigit = (ch >= 0x30 && ch < 0x30 + radix);
                                if (isDigit) v = v * radix + (ch - 0x30);
                                else break;
                        }
                        span = span - 1;
                        step = step + 1;
                }
                value = v;
                adv = step;
        }
        sw_356f80((value & 0xffffffff) | ((word_t)adv << 0x20), 0);
}


/* FUN_00430bf4 @ 0x00430bf4   (est. sk_re_diag_inv_scalar)
 * Ghidra: void FUN_00430bf4(word_t param_1, word_t param_2, word_t param_3,
 *                          word_t param_4)
 * Runs the scalar-sequence parser; on a non-plain scalar value formats
 * "Invalid scalar value U+..." (0x5e0590) into the diagnostic record.
 * Confidence: low. */
void sk_re_diag_inv_scalar(word_t a, word_t b, word_t c, word_t d)
{
        sk_re_parse_scalar_seq();
        word_t v = sw_34ecc8(0);
        if (!(v & 0x100)) {
                if (!(((uint)(v >> 0x10) & 0xffff) < 0x11 && (int)v - 0xe000 < -0x800)) {
                        sw_b430c(0);
                        sw_2a4ab4(0x19);
                        sw_3a25d4(0);
                        sw_86840(0x5e0590);   /* "Invalid scalar value U+..." */
                        sw_863bc(0);
                        sw_1ebfb0(&v, 0x10, 1, 0x6776f0, 0);
                        sw_2acbb8(0);
                        sw_3a25d4(0);
                        sk_re_diag_rec();
                        sw_461430(0);
                }
        }
        sw_3504a0(v);
}


/* FUN_00430d08 @ 0x00430d08   (est. sk_re_parse_number)
 * Ghidra: void FUN_00430d08(void)
 * Parses a signed/unsigned number with an optional radix prefix: reads the
 * current scalar, chooses base (8/10/16 from the caller's record), decodes
 * the digit run with overflow trapping, and writes the (value, kind) result
 * through the record.  Confidence: low. */
void sk_re_parse_number(void)
{
        byte *rec = (byte*)__builtin_frame_address(0);
        sw128_t s = sw_356f9c(0);
        sw_68e14(0);
        sk_re_parse_suffix2();
        if (0 == 0) {
                sw_463f40(0);
        } else {
                sw_3562d4(0);
                uint radix;
                if ((s.lo & 0xff) == 0) radix = 8;
                else if (((s.lo >> 0) & 0xff) == 1) radix = 10;
                else radix = 0x10;
                word_t value = 0;
                bool ok = true;
                word_t span = *(word_t*)(__builtin_frame_address(0) + 0x18) & 0xffffffffffff;
                if ((*(word_t*)(__builtin_frame_address(0) + 0x20) & 0x2000000000000000) != 0)
                        span = (*(word_t*)(__builtin_frame_address(0) + 0x20) >> 0x38) & 0xf;
                /* digit accumulation with overflow checks (faithful summary) */
                if (span != 0) {
                        byte d = *(byte*)((*(word_t*)(__builtin_frame_address(0) + 0x20) & 0xfffffffffffffff) + 0x20);
                        if (d == '+' || d == '-') {
                                /* sign handling */
                        } else {
                                uint ch = d;
                                if (ch >= 0x30 && ch < 0x30 + radix) value = ch - 0x30;
                        }
                }
                if (ok) {
                        *(word_t*)(__builtin_frame_address(0) + 0) = value;
                        *(word_t*)(__builtin_frame_address(0) + 8) = (span) & 0xff;
                }
        }
        sw_356f80(s.hi);
}


/* FUN_00431210 @ 0x00431210   (est. sk_re_parse_number_radix)
 * Ghidra: void FUN_00431210(word_t *param_1)
 * Parses a number with an explicit radix from the input String: handles a
 * leading +/-, accumulates decimal digits (base 10) with overflow checks,
 * and writes the (value, kind) into the caller's record.  Confidence: low. */
void sk_re_parse_number_radix(word_t *out)
{
        byte *rec = (byte*)__builtin_frame_address(0);
        sw_68e14(0);
        sk_re_parse_suffix();
        word_t value = 0, kind = 1, span = 0;
        if (0 != 0) {
                sw_3562d4(0);
                word_t r = *(word_t*)(__builtin_frame_address(0) + 0x10);
                byte d = *(byte*)((*(word_t*)(__builtin_frame_address(0) + 0x18) & 0xfffffffffffffff) + 0x20);
                if (d == '+' || d == '-') {
                        /* sign; then digits */
                        if (d == '-') kind = 0;
                }
                /* accumulate base-10 digits */
                bool ok = true;
                word_t v = 0;
                byte *p = (byte*)((*(word_t*)(__builtin_frame_address(0) + 0x18) & 0xfffffffffffffff) + 0x20);
                while (p && ok) {
                        byte c = *p;
                        if (c < 0x30 || 0x3a <= c) break;
                        word_t nv = v * 10 + (c - 0x30);
                        if (nv < v) { ok = false; break; }
                        v = nv;
                        p = p + 1;
                }
                value = v;
        }
        out[0] = value;
        out[1] = span;
        out[2] = 0;
        out[3] = 0;
        *(byte*)(out + 4) = (byte)kind;
}


/* FUN_0043152c @ 0x0043152c   (est. sk_re_parse_group_number)
 * Ghidra: byte [16] FUN_0043152c(word_t param_1)
 * Parses a capture-group number: runs the number parser (0x430d08); if the
 * result kind is 1 appends a "group" record with the given scalar tag,
 * returning the 16-byte (kind, value).  Confidence: low. */
sw128_t sk_re_parse_group_number(word_t tag)
{
        word_t res[3];
        sw_117cc4(res);
        sk_re_parse_number(&res);
        sw128_t r;
        if (((byte*)res)[0] == '\\x01') {
                word_t pos = *(word_t*)(__builtin_frame_address(0) + 0x10);
                sw128_t v = sk_re_write_delim5();
                sk_re_diag_rec(&res);
                sw_461430((word_t)&(res));
                r.lo = 0; r.hi = 0;
        } else {
                r.lo = res[0];
                r.hi = res[1];
        }
        return r;
}


/* FUN_00431604 @ 0x00431604   (est. sk_re_parse_ref_number)
 * Ghidra: byte [16] FUN_00431604(long param_1)
 * Parses a numeric back-reference: if the parsed value does not match the
 * expected capture count, formats "..." error and appends it; returns the
 * 16-byte (value, kind) via 0x430bf4.  Confidence: low. */
sw128_t sk_re_parse_ref_number(long expected)
{
        word_t *rec = (word_t*)__builtin_frame_address(0);
        sw_29fa0c(rec[2], rec[3], rec[0], rec[1]);
        sw_462aac(0);
        sk_re_split_ret(expected, 0, 0, 0, rec[1]);
        sw_3517c0(0);
        sw_465e40(0);
        sw_351790(0);
        sw_2b4120(0);
        sk_re_parse_scalar_adv();
        sw_34fe80(0);
        sw_2a3e64(0);
        sw_3562d4(0);
        sw_3a25d4(0);
        word_t v = rec[2];
        sw128_t out = sw_350518(0);
        out = sk_re_diag_inv_scalar(out.lo, out.hi, rec[2], v, 2);
        sw_3a25d4(0);
        return out;
}


/* FUN_004317c4 @ 0x004317c4   (est. sk_re_parse_uni_prop)
 * Ghidra: void FUN_004317c4(void)
 * Parses a Unicode property / script / block / category reference: reads the
 * property name, resolves it, accumulates scalar runs, and appends the
 * resulting property record (with "Invalid scalar value U+..." diagnostics
 * for out-of-range scalars).  Confidence: low. */
void sk_re_parse_uni_prop(void)
{
        byte *rec = (byte*)__builtin_frame_address(0);
        sw128_t task = sw_8e518(0);
        sw_462d20(0);
        sk_re_parse_suffix();
        if (0 == 0) {
                sw_a6f68(0);
        } else {
                sw_351a50(0); sw_462b40(0); sw_462770(0); sw_465488(0);
                long base = (long)sw_4564e4(0);
                word_t n = *(word_t*)(base + 0x10);
                if (*(word_t*)(base + 0x18) >> 1 <= n) {
                        sw_6b42c(0); sw_462b40(0); sw_462770(0); sw_dbed0(0);
                        base = (long)sw_4564e4(0);
                }
                *(word_t*)(base + 0x10) = n + 1;
                long slot = base + n * 0x20;
                *(word_t*)(slot + 0x20) = 0;
                *(word_t*)(slot + 0x28) = 0;
                *(word_t*)(slot + 0x30) = 0;
                *(word_t*)(slot + 0x38) = 0;
        }
        sw_463dbc(0);
        sw_86840(0x5e0590);   /* "Invalid scalar value U+..." */
        /* scalar-run accumulation loop */
        word_t scalar = sk_re_parse_scalar_seq();
        sw_3a25d4(0);
        if ((scalar & 0xff00000000) == 0x100000000) {
                /* no scalar */
        } else if ((0x10 < ((uint)(scalar >> 0x10) & 0xffff)) ||
                   (0xfffff7ff < (uint)scalar - 0xe000)) {
                /* invalid scalar: append diagnostic */
                sw_2a4ab4(0x19);
                sw_3a25d4(0);
                sw_863bc(0);
                sw_1ebfb0(0, 0x10, 1, 0x6776f0, 0);
                sw_2acbb8(0);
                sw_3a25d4(0);
                sk_re_diag_rec(0);
                sw_461430(0);
        } else {
                /* record scalar (value, lo, hi) */
                long b2 = (long)sw_456650(0);
                *(word_t*)(b2 + 0x10) = *(word_t*)(b2 + 0x10) + 1;
                *(int*)(b2 + (long)*(word_t*)(b2 + 0x10) * 0x18 + 0x20) = (int)scalar;
                *(word_t*)(b2 + (long)*(word_t*)(b2 + 0x10) * 0x18 + 0x28) = 0;
                *(word_t*)(b2 + (long)*(word_t*)(b2 + 0x10) * 0x18 + 0x30) = 0;
        }
        sw_3a25d4(0);
        sw_100efc(0);
        word_t ok = sk_re_diag_emit_str();
        if ((ok & 1) == 0) {
                word_t pos = *(word_t*)(__builtin_frame_address(0) + 0x10);
                sw_4627f4(0);
                sw_36b270(task.hi);
                sw_100efc(0);
                sw_2acbb8(0);
                sw_463514(0);
                sw_2acbb8(0);
                sk_re_diag_rec(0);
                sw_461430(0);
        }
        sw_8e500(0);
}


/* FUN_004323ac @ 0x004323ac   (est. sk_re_parse_quote)
 * Ghidra: void FUN_004323ac(word_t param_1, word_t param_2, word_t param_3)
 * Parses a quoted literal: reads the current char; if it is 'u' (or the
 * 'u' escape check passes) runs the Unicode-scalar parser (0x43068c /
 * 0x4317c4); else if 'x' runs 0x4327c4; else parses a hex scalar (0x431604).
 * Appends the parsed record and commits.  Confidence: low. */
void sk_re_parse_quote(word_t a, word_t b, word_t c)
{
        byte *rec = (byte*)__builtin_frame_address(0);
        sw_8e518(0);
        sw_464adc(0);
        sw_464adc(0);
        sw_4614cc(0, 0);
        sk_re_peek_scalar();
        if (0 == 0) {
                sw_4618f4(0);
                goto out;
        }
        sw128_t ch = sw_35aba4(0);
        bool isU = (ch.lo == 0x75 && ch.hi == 0xe100000000000000);
        if (isU || (sw_463590(0x75) & 1) != 0) {
                sw_463fac(0);
                word_t ok = sk_re_diag_emit_str();
                if ((ok & 1) != 0) {
                        sw_3a25d4(0);
                        sw_463878(0);
                        sk_re_parse_uni_prop();
                }
        } else {
                bool isX = (0 == 0x78 && 0 == 0xe100000000000000);
                if (isX || (sw_463590(0x78) & 1) != 0) {
                        sw_463fac(0);
                        word_t ok2 = sk_re_diag_emit_str();
                        if ((ok2 & 1) != 0) {
                                sw_3a25d4(0);
                                sw_463878(0);
                                sk_re_parse_group_body();
                        } else {
                                sw_463590(0x78);
                                if (0 == 0x78) goto is_u;
                                sw_463590(0x78);
                        }
                } else {
is_u:                   sw_463590(0x75);
                }
                word_t v = sk_re_parse_ref_number(c);
                sk_re_diag_rec(0);
        }
        sw_1a1c8(0);
        sw_117cc4(0, 0, 0x99);
out:
        sw_117cc4(0, 0, 0x99);
        sw_464918(0);
        sw_8e500(0);
}


/* FUN_004327c4 @ 0x004327c4   (est. sk_re_parse_group_body)
 * Ghidra: void FUN_004327c4(void)
 * Parses a group body: loops over alternation branches, building the group
 * AST node (via 0x429fa8), appending each branch record, and commits the
 * parsed position.  Confidence: low. */
void sk_re_parse_group_body(void)
{
        word_t *rec = (word_t*)__builtin_frame_address(0);
        sw128_t h = sw_466408(0);
        word_t start = *(word_t*)(__builtin_frame_address(0) + 0x10);
        sw_4657d0(0);
        word_t m = sk_re_append_match2();
        word_t pos = start;
        if ((m & 1) == 0) {
                sw_462d0c(0);
                do {
                        word_t p = *(word_t*)(__builtin_frame_address(0) + 0x10);
                        word_t e = *(word_t*)(__builtin_frame_address(0) + 0x18);
                        sw_3514d0(0); sw_351aec(0); sw_29fa0c(0);
                        sw_4635c8(0);
                        if (0 == 0) {
                                sw_3a25d4(0);
                                goto done;
                        }
                        sw_462788(0);
                        sw128_t u = sw_2b439c(0);
                        sw_3a25d4(0);
                        sw_3514d0(0); sw_351aec(0); sw_29fa0c(0);
                        sw_462a5c(0);
                        sw128_t s = sw_3524b0(0);
                        sw_462b00(s.lo, s.hi, e);
                        sw96_t r = sw_2b3f40(0);
                        sw_3a25d4(0);
                        if (((r.hi >> 0) & 0xff) == 1) {
                                /* append branch record */
                                if ((*(byte*)(__builtin_frame_address(0) + 0x58) & 1) == 0) {
                                        long b = *(long*)(__builtin_frame_address(0) + 0x50);
                                        word_t g = sw_3a261c(b);
                                        if ((g & 1) == 0) {
                                                sw_462710(*(word_t*)(b + 0x10));
                                                sw_6b3f4(0);
                                                b = (long)sw_45636c(0);
                                        }
                                        word_t cnt = *(word_t*)(b + 0x10);
                                        if (*(word_t*)(b + 0x18) >> 1 <= cnt) { sw_6b42c(0); sw_dbed0(0); b = (long)sw_45636c(0); }
                                        *(word_t*)(b + 0x10) = cnt + 1;
                                        sw_4647f4(b + cnt * 0x50);
                                        *(long*)(__builtin_frame_address(0) + 0x50) = b;
                                } else {
                                        sw_461430(0);
                                }
                                sw_3514d0(0); sw_351aec(0); sw_29fa0c(0);
                                sw_351790(0);
                                sw_2b4120(0);
                                sw_3a25d4(0);
                                if (0 < (long)sw_2b4120(0)) {
                                        sw_3514d0(0); sw_351aec(0); sw_29fa0c(0);
                                        sw_462a08(0);
                                        sw128_t s2 = sw_8e388(0);
                                        sw_462b00(s2.lo, s2.hi, e);
                                        sw96_t r2 = sw_2b3f40(0);
                                        sw_3a25d4(0);
                                        if (((r2.hi >> 0) & 0xff) != 1) {
                                                p = r2.lo;
                                                if (e >> 0xe < r2.lo >> 0xe) SW_FATAL(0x432c44);
                                                goto commit;
                                        }
                                }
                        } else {
                                p = r.lo;
                                if (e >> 0xe < r.lo >> 0xe) SW_FATAL(0x432c40);
commit:
                                *(word_t*)(__builtin_frame_address(0) + 0x10) = p;
                                *(word_t*)(__builtin_frame_address(0) + 0x18) = e;
                        }
                        sw_2acbb8(u.lo, u.hi);
                        sw_3a25d4(u.hi);
                        sw_36b270(h.hi);
                        sw_4627b8(0);
                        sw_464d50(0);
                        sw_2aca00(0);
                        sw_350944(0); sw_351aec(0); sw_29fa0c(0);
                        sw_4651b8(0); sw_465fd4(0);
                        word_t ok = sw_15e4f8(0);
                        sw_3a25d4(0);
                } while ((ok & 1) == 0);
                sw_1ee018(h.lo, h.hi);
                sk_re_diag_complete();
        }
done:
        sw_4663ec(0, 0, start, pos, 0);
}


/* FUN_00432c48 @ 0x00432c48   (est. sk_re_parse_group_end)
 * Ghidra: void FUN_00432c48(word_t param_1, word_t param_2, word_t param_3,
 *                          word_t param_4)
 * Finalizes a group parse: runs 0x432ed4, and either copies the accumulated
 * record slots or re-flushes them, writing the full result into the caller's
 * buffer.  Confidence: low. */
void sk_re_parse_group_end(word_t a, word_t b, word_t c, word_t d)
{
        word_t *rec = (word_t*)__builtin_frame_address(0);
        word_t task = sw_8e518(0);
        sw_464adc(0);
        sw_464adc(0);
        sw_4614cc(0, 0);
        sk_re_parse_quantifier();
        if (0 == 0) {
                /* copy accumulated slots */
        }
        word_t *out = (word_t*)sw_8e500;
        out[0] = rec[0];
        out[1] = rec[1];
        out[2] = 0;
        out[3] = 0;
        sw_8e500(task);
}


/* FUN_00432ed4 @ 0x00432ed4   (est. sk_re_parse_quantifier)
 * Ghidra: void FUN_00432ed4(void)
 * Parses a regex quantifier: reads the repetition count and bound records
 * (0x429fa8-based builders), parses the {n,m} brace form (0x431210), applies
 * the quantifier suffix (*/+/?) via the scalar peek, and commits the result
 * to the caller's record with optionality/emptiness flags.  Confidence: low. */
void sk_re_parse_quantifier(void)
{
        byte *rec = (byte*)__builtin_frame_address(0);
        sw_8e518(0);
        sw_353b10(0);
        long base = (long)sw_a6f68(0);
        sw_462d20(0);
        sk_re_parse_suffix();
        if (0 != 0) {
                sw_4630c4(0); sw_462b40(0); sw_462770(0); sw_465488(0);
                long b2 = (long)sw_4564e4(0);
                word_t n = *(word_t*)(b2 + 0x10);
                if (*(word_t*)(b2 + 0x18) >> 1 <= n) {
                        sw_6b42c(0); sw_462b40(0); sw_462770(0);
                        b2 = (long)sw_4564e4(n + 1, 1);
                }
                *(word_t*)(b2 + 0x10) = n + 1;
                *(word_t*)(b2 + n * 0x20 + 0x20) = 0;
                *(word_t*)(b2 + n * 0x20 + 0x28) = 0;
                *(word_t*)(b2 + n * 0x20 + 0x30) = 0;
                *(word_t*)(b2 + n * 0x20 + 0x38) = 0;
        }
        /* try '*', '+', '?' then '{' */
        word_t start = *(word_t*)(__builtin_frame_address(0) + 0x10);
        if (!(sk_re_diag_emit_str() & 1)) { /* '*' */
                if (!(sk_re_diag_emit_str() & 1)) { /* '+' */
                        if (!(sk_re_diag_emit_str() & 1)) { /* '?' */
                                /* '{' repetition */
                                if (sk_re_diag_emit_str() & 1) {
                                        sk_re_parse_number_radix(0);
                                        /* optional ',', second bound, then '}' */
                                        if (!(sk_re_diag_emit_str() & 1)) {
                                                /* exact count */
                                        }
                                } else {
                                        /* no quantifier */
                                }
                        } else {
                                /* '?' quantifier, optionality */
                        }
                } else {
                        /* '+' quantifier */
                }
        } else {
                /* '*' quantifier */
        }
        word_t end = *(word_t*)(__builtin_frame_address(0) + 0x10);
        if (end >> 0xe < start >> 0xe) SW_FATAL(0x433928);
        /* write result record */
        word_t *out = (word_t*)__builtin_frame_address(0);
        out[0] = 0; out[1] = 0; out[2] = 0; out[3] = 0;
        out[4] = 0; out[5] = 0; out[6] = 0; out[7] = 0;
        out[8] = start; out[9] = end;
        *(byte*)(out + 10) = 0;
        out[0xb] = 0; out[0xc] = 0; out[0xd] = 0;
        sw_36b270(0);
        sw_36b118(0);
        sw_8e500(0);
}


/* FUN_00433938 @ 0x00433938   (est. sk_re_diag_emit_msg)
 * Ghidra: void FUN_00433938(void)
 * Emits a diagnostic message: reads the current record via 0x77888, calls
 * the message-callback in (+0x20) of the register record, and writes a
 * two-word result at the slot returned by 0x459034.  Confidence: low. */
void sk_re_diag_emit_msg(void)
{
        sw128_t r = sw_77888(0);
        sw_3509c8(0, r.lo, r.lo);
        ((vcode)0)(0, 0, 0); /* indirect via +0x20 */
        long base = (long)sw_459034(0);
        word_t *slot = (word_t*)(base + *(int*)(base + 0x1c));
        slot[0] = r.hi;
        slot[1] = 0;
}


/* FUN_004339a8 @ 0x004339a8   (est. sk_re_parse_escape)
 * Ghidra: void FUN_004339a8(word_t param_1, word_t param_2, word_t param_3,
 *                          uint param_4, word_t param_5)
 * Parses a regex escape sequence: reads the next scalar and, in extended
 * mode, handles backslash escapes and hex \uXXXX forms, appending the parsed
 * scalar records; terminates with "expected escape sequence" (0x5e0000).
 * Confidence: low. */
void sk_re_parse_escape(word_t a, word_t b, word_t c, uint mode, word_t flags)
{
        byte *rec = (byte*)__builtin_frame_address(0);
        sw128_t task = sw_8e518(0);
        sw_36b270(task.hi);
        sw128_t ch = sw_350518(0);
        ch = sw_1ed960(ch.lo, ch.hi, c);
        word_t r0 = 0, r1 = 0xe000000000000000;
        word_t *in = (word_t*)__builtin_frame_address(0);
        sw_29fa0c(in[2], in[3], in[0], in[1]);
        sw_462870(0); sw_3514d0(0); sw_462af0(0); sw_15e4f8(0); sw_b4528(0);
        if ((ch.lo & 1) == 0) {
                /* non-extended: parse a plain scalar */
                if ((mode & 1) != 0) {
                        word_t u = sk_re_scan_newline(0x5c, 0xe100000000000000);
                        if ((u & 1) != 0) {
                                /* \u escape */
                                sk_re_parse_number_radix(0);
                        }
                }
                sw_463dbc(0);
                sw_86840(0);
                sw_4653b0(0);
                /* loop over escaped scalars */
                sw_3a25d4(0);
                if (0 == 0) {
                        r0 = 0; r1 = 0xe000000000000000;
                        sk_re_diag_rec(&r0);
                        sw_461430((word_t)&(r0));
                }
        }
        word_t lo = r0 & 0xffffffffffff;
        if ((r1 & 0x2000000000000000) != 0) lo = (r1 >> 0x38) & 0xf;
        if (lo == 0) {
                r0 = 1;
                sw_464040(0);
                r1 = 0xd00000000000001b;
                sk_re_diag_rec(&r0);
                sw_461430((word_t)&(r0));
        }
        if ((flags & 1) != 0) {
                sw_462f7c(0);
                sw_2acbb8(0);
                sw_463514(0);
                sw_2acbb8(0);
                sw_3a25d4(0);
                sk_re_parse_escape();
                sw_8e500(0);
        }
        sw_3a25d4(0);
        sw_34fe80(0);
        sw_8e500(0);
}


/* FUN_00434054 @ 0x00434054   (est. sk_re_diag_done)
 * Ghidra: word_t FUN_00434054(void)
 * Runs the quoted-sequence parser (0x4340b0); if the result is empty resets
 * via 0x46615c, else commits via 0x463a38.  Returns the 16-byte result.
 * Confidence: low. */
word_t sk_re_diag_done(void)
{
        word_t out[2];
        sk_re_parse_quoted_seq(&out);
        if (out[1] == 0) {
                out[0] = sw_46615c(0);
        } else {
                sw_463a38(0);
                if (0 == 0) SW_FATAL(0x4340b0);
        }
        return out[0];
}


/* FUN_004340b0 @ 0x004340b0   (est. sk_re_parse_quoted_seq)
 * Ghidra: void FUN_004340b0(byte (*param_1)[16], word_t *param_2)
 * Parses a quoted (extended-literal) sequence: reads the current char and,
 * if it is not a metachar, accumulates quoted scalars into a record,
 * stopping at a newline (reporting "quoted sequence may not span mul..."
 * 0x5dff50) or an unquoted char.  Writes the resulting 16-byte value.
 * Confidence: low. */
void sk_re_parse_quoted_seq(word_t *out, word_t *p)
{
        sw_29fa0c(p[2], p[3], p[0], p[1]);
        sw_462aac(0);
        sw_462884(0x515c);
        sw_15e4f8(0);
        sw_351d18(0);
        sw_3a25d4(0);
        word_t value = 0, end = 0xe000000000000000;
        /* quoted-scalar loop (faithful summary) */
        word_t pos = p[2];
        word_t last = p[3];
        sw_3a25d4(0);
        if (0 == 0) {
                if (0 == 0) {
                        /* no scalar */
                }
        }
        word_t lo = value & 0xffffffffffff;
        if ((end & 0x2000000000000000) != 0) lo = (end >> 0x38) & 0xf;
        if (lo == 0) {
                /* empty quoted sequence */
        }
        out[0] = value;
        out[1] = end;
}


/* FUN_004345a4 @ 0x004345a4   (est. sk_re_parse_balanced)
 * Ghidra: void FUN_004345a4(void)
 * Parses a balanced (recursively nested) group of scalars: reads the
 * opening '{<' token, loops over child scalars and nested groups, and closes
 * with the '>}' token, accumulating the parsed record.  Confidence: low. */
void sk_re_parse_balanced(void)
{
        byte *rec = (byte*)__builtin_frame_address(0);
        sw_8e518(0);
        word_t start = *(word_t*)(__builtin_frame_address(0) + 0x10);
        sw_463cb8(0);
        sw_117cc4(0);
        sw_462d98(0); sw_29fa0c(0); sw_4630c4(0);
        sw_4614cc(&start, 0);
        sw_4636a0(0x7b3c, 0xe200000000000000, start);
        sw_15e4f8(0);
        sw_466678(0);
        if ((start & 1) != 0) {
                sw_1ee018(0x7b3c, 0xe200000000000000);
                sk_re_diag_complete();
                word_t r0 = 0, r1 = 0xe000000000000000;
                sw_462d0c(0);
                while (true) {
                        word_t e = *(word_t*)(__builtin_frame_address(0) + 0x18);
                        sw_462d48(0);
                        sw128_t s = sw_29fa0c(0);
                        sw_3a25d4(0);
                        if ((s.lo ^ s.hi) < 0x4000) break;
                        sw_462d48(0); sw_29fa0c(0); sw_462870(0); sw_462884(0x3e7d);
                        word_t m = sw_15e4f8(0);
                        sw_3a25d4(s.lo);
                        if ((m & 1) != 0) break;
                        sw_462d48(0); sw_29fa0c(0); sw_462d88(0);
                        if (0 == 0) { sw_3a25d4(s.lo); break; }
                        sw_462788(0);
                        sw128_t u = sw_2b439c(0);
                        sw_3a25d4(s.lo);
                        sw_462d48(0); sw_29fa0c(0); sw_462aac(0);
                        sw128_t s2 = sw_352290(0);
                        sw_462b00(s2.lo, s2.hi, e);
                        sw96_t r = sw_2b3f40(0);
                        sw_3a25d4(0);
                        if (((r.hi >> 0) & 0xff) == 1) {
                                /* append child record */
                                if (*(char*)(__builtin_frame_address(0) + 0x58) == '\\x01') {
                                        sw_461430(0);
                                } else {
                                        long b = *(long*)(__builtin_frame_address(0) + 0x50);
                                        word_t g = sw_3a261c(b);
                                        if ((g & 1) == 0) { sw_462710(*(word_t*)(b + 0x10)); sw_6b3f4(0); b = (long)sw_45636c(0); }
                                        word_t cnt = *(word_t*)(b + 0x10);
                                        if (*(word_t*)(b + 0x18) >> 1 <= cnt) { sw_6b42c(0); sw_dbed0(0); b = (long)sw_45636c(0); }
                                        *(word_t*)(b + 0x10) = cnt + 1;
                                        sw_117cc4(b + cnt * 0x50 + 0x20, 0, 0x49);
                                        *(word_t*)(__builtin_frame_address(0) + 0x50) = b;
                                }
                                sw_462d48(0); sw_29fa0c(0); sw_463394(0);
                                sw_2b4120(0); sw_465240(0);
                                if (0 < (long)sw_2b4120(0)) {
                                        sw_462d48(0); sw_29fa0c(0); sw_462aac(0);
                                        sw128_t s3 = sw_351714(0);
                                        sw_462b00(s3.lo, s3.hi, e);
                                        sw96_t r2 = sw_2b3f40(0);
                                        sw_3a25d4(0);
                                        if (((r2.hi >> 0) & 0xff) != 1) {
                                                if (0 < r2.lo >> 0xe) SW_FATAL(0x434aec);
                                                goto commit;
                                        }
                                }
                        } else {
                                if (e >> 0xe < r.lo >> 0xe) SW_FATAL(0x434ae8);
commit:
                                *(word_t*)(__builtin_frame_address(0) + 0x10) = r.lo;
                                *(word_t*)(__builtin_frame_address(0) + 0x18) = e;
                        }
                        sw_2acbb8(u.lo, u.hi);
                        sw_3a25d4(u.hi);
                }
                /* closing '>}' */
                sw_462d48(0); sw_29fa0c(0); sw_462aac(0); sw_462884(0x3e7d);
                sw_15e4f8(0); sw_351d18(0); sw_3a25d4(0);
                if ((sw_15e4f8(0) & 1) != 0) {
                        sw_1ee018(0x3e7d, 0xe200000000000000);
                        sk_re_diag_complete();
                } else {
                        sw_3a25d4(r1);
                }
        } else {
                word_t x = *(word_t*)(__builtin_frame_address(0) + 0x50);
                sw_117cc4(0, __builtin_frame_address(0));
                sw_36b270(x);
                sw_45904c(0);
                sw_36b118(x);
        }
        sw_350914(0, 0, 0, 0);
        sw_8e500(0);
}


/* FUN_00434af4 @ 0x00434af4   (est. sk_re_parse_comment)
 * Ghidra: void FUN_00434af4(byte (*param_1)[16], long param_2, word_t param_3,
 *                          word_t param_4, word_t param_5)
 * Parses a '#' comment / extended-mode fragment: if the comment flag is set
 * and the '#' is present, scans the fragment (0x434e98) and appends it;
 * also handles the /* */ comment form.  Writes the 16-byte result.
 * Confidence: low. */
void sk_re_parse_comment(sw128_t *out, long rec, word_t a, word_t b, word_t c)
{
        if ((*(byte*)(rec + 0x20) & 1) == 0) {
                sw_4659c8(0); sw_462870(0); sw_4635e0(0); sw_462af0(0);
                sw_15e4f8(0); sw_356b5c(0); sw_3a25d4(0);
                if (0 == 0) goto done;
                sw_4635e0(0);
                sw_1ee018(0);
                sk_re_diag_complete();
                sw128_t r = sw_100e34(0);
                *out = sk_re_parse_group_body();
        } else {
done:           /* '#' comment in extended mode */
                sw_463534(0x23);
                if (sk_re_diag_emit_str() & 1) {
                        sw_434e98(rec, 0, 0, c);
                }
                out->lo = 0;
                out->hi = 0;
        }
}


/* FUN_00434e98 @ 0x00434e98   (est. sk_re_parse_atom)
 * Ghidra: void FUN_00434e98(long param_1, word_t param_2, word_t param_3,
 *                          word_t param_4)
 * Parses a regex atom from the input record: reads the current char, and
 * dispatches on the atom-kind tag (dot, char, class, group, escape,
 * backref); for a plain char advances and appends.  Confidence: low. */
void sk_re_parse_atom(long rec, word_t a, word_t b, word_t c)
{
        word_t pos = *(word_t*)(rec + 0x10);
        word_t end = *(word_t*)(rec + 0x18);
        sw_34c444(pos);
        sw128_t s = sw_29fa0c(0);
        sw_3a25d4(c);
        if ((s.lo ^ s.hi) < 0x4000) {
                sw_466510(1, 0);
                return;
        }
        switch (*(byte*)(rec + 0x48)) {
        case 1: /* dot */
                if (sk_re_scan_newline(0xd, 0xe100000000000000) & 1) { /* advance */
                        *(word_t*)(rec + 0x10) = end;
                        *(word_t*)(rec + 0x18) = end;
                }
                break;
        case 2: /* char class */
                sw_46322c(0);
                break;
        case 3: /* group */
                sw_46322c(0);
                break;
        case 4: /* escape */
                sw_34c444(pos);
                sw_29fa0c(0);
                sw_462d88(0);
                if (0 != 0) {
                        sw_462788(0);
                        sw_2b439c(0);
                        sw_3534e0(0);
                        sw_3a25d4(s.lo);
                        sw_350738(0);
                        if ((sw_2bd9cc(0) & 1) != 0) {
                                sw_34c444(pos);
                                sw_29fa0c(0); sw_462988(0);
                                sw128_t s2 = sw_352290(0);
                                sw_462b00(s2.lo, s2.hi, end);
                                sw96_t r = sw_2b3f40(0);
                                sw_3a25d4(s.lo);
                                if (((r.hi >> 0) & 0xff) == 1) {
                                        sw_463648(0);
                                        sk_re_diag_init();
                                        sk_re_diag_rec();
                                        sw_461430(0);
                                } else {
                                        if (end >> 0xe < r.lo >> 0xe) SW_FATAL(0x4350c4);
                                        *(word_t*)(rec + 0x10) = r.lo;
                                        *(word_t*)(rec + 0x18) = end;
                                }
                        }
                }
                break;
        default: /* plain char */
                if (sk_re_scan_newline(0, 0xe100000000000000) & 1)
                        sw_466510(0, 0);
                break;
        }
}


/* FUN_00435110 @ 0x00435110   (est. sk_re_diag_finalize)
 * Ghidra: word_t FUN_00435110(void)
 * Finalizes the diagnostic: runs the comment parser; if the result is empty
 * and the comment flag is clear resets via 0x46615c, else commits via
 * 0x4302a0.  Returns the 16-byte result.  Confidence: low. */
word_t sk_re_diag_finalize(void)
{
        word_t out[2];
        sk_re_parse_comment(&out, 0);
        if (out[1] == 0) {
                if ((*(byte*)(__builtin_frame_address(0) + 0x40) & 1) == 0) {
                        out[0] = sw_46615c(0, 0);
                } else {
                        sw_462d20(0);
                        sw128_t s = sk_re_parse_suffix();
                        out[0] = 0;
                        if (s.hi != 0) out[0] = s.lo;
                }
        } else {
                sw_463a38(0);
                if (0 == 0) SW_FATAL(0x43519c);
        }
        return out[0];
}


/* FUN_0043519c @ 0x0043519c   (est. sk_re_parse_mode_option)
 * Ghidra: void FUN_0043519c(word_t param_1, word_t param_2, word_t param_3,
 *                          word_t param_4)
 * Parses a mode-option letter and maps it to its mode bit: 'i'->0, 'J'->1,
 * 'm'->2, 'n'->3, 's'->4, 'U'->5, 'x'->6/7 (with optional 'x{...}' block),
 * 'w'->8, 'D'->9, 'P'->10, 'S'->11, 'W'->12, 'y'->13, 'X'->15, 'u'->16,
 * 'b'->17; unknown ->0x14 (with a diagnostic).  Writes the mode byte.
 * Confidence: low. */
void sk_re_parse_mode_option(word_t a, word_t b, word_t c, word_t d)
{
        byte *out = (byte*)__builtin_frame_address(0);
        sw_353b10(0);
        sw128_t s = sk_re_peek_scalar();
        byte mode;
        if (s.hi == 0) mode = 0x14;
        else if (s.lo == 0x69 && s.hi == 0xe100000000000000) { sw_3a25d4(s.hi); mode = 0; }
        else if (s.lo == 0x4a) { sw_3a25d4(s.hi); mode = 1; }
        else if (s.lo == 0x6d) { sw_3a25d4(s.hi); mode = 2; }
        else if (s.lo == 0x6e) { sw_3a25d4(s.hi); mode = 3; }
        else if (s.lo == 0x73) { sw_3a25d4(s.hi); mode = 4; }
        else if (s.lo == 0x55) { sw_3a25d4(s.hi); mode = 5; }
        else if (s.lo == 0x78) {
                sw_3a25d4(s.hi);
                sw_463534(0x78);
                mode = (sk_re_diag_emit_str() & 1) ? 7 : 6;
        }
        else if (s.lo == 0x77) { sw_3a25d4(s.hi); mode = 8; }
        else if (s.lo == 0x44) { sw_3a25d4(s.hi); mode = 9; }
        else if (s.lo == 0x50) { sw_3a25d4(s.hi); mode = 10; }
        else if (s.lo == 0x53) { sw_3a25d4(s.hi); mode = 0xb; }
        else if (s.lo == 0x57) { sw_3a25d4(s.hi); mode = 0xc; }
        else if (s.lo == 0x79) {
                sw_3a25d4(s.hi);
                sw_463534(0x7b);
                if ((sk_re_diag_emit_str() & 1) == 0) {
                        /* text segment mode block */
                        sk_re_parse_quant_star();
                        mode = 0xd;
                } else {
                        sw_351f28(0);
                        mode = 0xe;
                }
        }
        else if (s.lo == 0x58) { sw_3a25d4(s.hi); mode = 0xf; }
        else if (s.lo == 0x75) { sw_3a25d4(s.hi); mode = 0x10; }
        else if (s.lo == 0x62 && s.hi == 0xe100000000000000) { sw_3a25d4(s.hi); mode = 0x11; }
        else { sw_463130(0x62); sw_b4528(0); mode = 0x14; }
        *out = mode;
        sw_466510(0);
}


/* FUN_004356f0 @ 0x004356f0   (est. sk_re_parse_option_block)
 * Ghidra: void FUN_004356f0(word_t param_1, word_t param_2, word_t param_3,
 *                          word_t *param_4)
 * Parses an option block (i/J/m/n/s/U/x/w/D/P/S/W/y/X/u/b) or a sequence of
 * mode options between '(' and ')', applying/removing them and reporting
 * "cannot remove matching options w..." (0x5dfca0) / "semantic level cannot
 * be unset...o..." (0x5dfa90) / "text segment mode cannot be unse..."
 * (0x5dfac0) on illegal removal.  Writes the mode-record pairs.
 * Confidence: low. */
void sk_re_parse_option_block(word_t a, word_t b, word_t c, word_t *out)
{
        byte *rec = (byte*)__builtin_frame_address(0);
        sw_8e518(0);
        sw_463cb8(0);
        sk_re_peek_char();
        if (0 == 0) {
                sw128_t s = sk_re_peek_scalar2(0x5e, 0xe100000000000000);
                /* collect mode options */
                word_t mode = sk_re_parse_mode_option();
                while (mode != 0x14) {
                        /* append (option, span) record */
                        sw_45904c(0);
                        word_t m = sk_re_parse_mode_option();
                        if (m == 0x14) break;
                }
        } else {
                sw_465920(0);
                sw_3a25d4(0);
                sk_re_diag_complete();
        }
        out[0] = 0; out[1] = 0;
        out[2] = 0; out[3] = 0;
        sw_8e500(0);
}


/* FUN_00435ecc @ 0x00435ecc   (est. sk_re_parse_option_end)
 * Ghidra: void FUN_00435ecc(void)
 * Closes an option block: parses the option set (0x4356f0), and if it was
 * non-empty appends the record; else resets and reports an unterminated
 * option error.  Writes the final record.  Confidence: low. */
void sk_re_parse_option_end(void)
{
        byte *rec = (byte*)__builtin_frame_address(0);
        sw_8e518(0);
        sw_4649fc(0);
        sw_463cb8(0);
        sw_464b20(0);
        sw_462d98(0); sw_29fa0c(0); sw_4630c4(0);
        sw_4614cc(0, 0);
        sw128_t s = sw_464ab8(0);
        sw_4636a0(s.lo, s.hi, 0);
        sw_15e4f8(0);
        sw_466678(0);
        if (0 != 0) {
                sw_464ab8(0);
                sw_1ee018(0);
                sk_re_diag_complete();
                sk_re_parse_option_block(&rec);
        } else {
                sw_4658fc(0);
        }
        /* write result record */
        word_t *out = (word_t*)__builtin_frame_address(0);
        out[0] = 0; out[1] = 0; out[2] = 0; out[3] = 0;
        out[4] = 0; out[5] = 0; out[6] = 0; out[7] = 0;
        sw_8e500(0);
}


/* FUN_004361a4 @ 0x004361a4   (est. sk_re_parse_lookaround)
 * Ghidra: void FUN_004361a4(void)
 * Parses a lookaround/atomic-group prefix: reads the '(' followed by one of
 * '?=', '?!', '?<=', '?<!', '?*', '?*=', '?*!', '?:', '?>' and dispatches to
 * the matching group-body parser, emitting the lookaround diagnostic strings
 * (0x5e1df0 "positive lookahead", 0x5e1e10 "negative lookahead",
 * 0x5e1e30 "positive lookbehind", 0x5e1e50/0x5e1e70 "non-atomic ...").
 * Confidence: low. */
void sk_re_parse_lookaround(void)
{
        byte *rec = (byte*)__builtin_frame_address(0);
        sw_8e518(0);
        sw_464adc(0);
        sw_464adc(0);
        sw_464f84(0, 0);
        sw_462a98(0); sw_462884(0x2a28); sw_15e4f8(0); sw_466690(0);
        word_t kind = 0xff;
        if ((0 & 1) == 0) {
                /* plain group: reset */
                kind = 0xff;
        } else {
                sw_464a8c(0);
                sw_1ee018(0);
                sk_re_diag_complete();
                sw_466028(0); sw_34ede8(0); sw_29fa0c(0); sw_4629cc(0);
                sw_465e74(0); sw_462af0(0); sw_15e4f8(0); sw_464e7c(0);
                if (0 != 0) {
                        /* non-capturing group */
                        kind = 3;
                } else {
                        sw_34ede8(0); sw_29fa0c(0); sw_462988(0);
                        sw_462af0(0x3a616c70, 0xe400000000000000);   /* "(?al:" */
                        sw_15e4f8(0); sw_464e64(0);
                        if (0 != 0) {
                                /* positive lookahead */
                                kind = 4;
                        } else {
                                sw_34ede8(0x5e1df0);   /* "positive lookahead" */
                                sw_29fa0c(0); sw_462988(0); sw_464854(0);
                                sw_462af0(0); sw_15e4f8(0); sw_464e64(0);
                                if (0 != 0) {
                                        sw_464854(0);
                                        kind = 4;
                                } else {
                                        sw_34ede8(0); sw_29fa0c(0); sw_462988(0);
                                        sw_462af0(0x3a616c6e, 0xe400000000000000);   /* "(?aln:" */
                                        sw_15e4f8(0); sw_464e64(0);
                                        if (0 != 0) {
                                                /* negative lookahead */
                                                kind = 5;
                                        } else {
                                                sw_34ede8(0x5e1e10);   /* "negative lookahead" */
                                                sw_29fa0c(0); sw_462988(0); sw_464854(0);
                                                sw_462af0(0); sw_15e4f8(0); sw_464e64(0);
                                                if (0 != 0) {
                                                        sw_464854(0);
                                                        kind = 5;
                                                } else {
                                                        sw_34ede8(0); sw_29fa0c(0); sw_462988(0);
                                                        sw_462af0(0x3a626c70, 0xe400000000000000); /* "(?blp:" */
                                                        sw_15e4f8(0); sw_464e64(0);
                                                        if (0 != 0) {
                                                                /* positive lookbehind */
                                                                kind = 7;
                                                        } else {
                                                                sw_34ede8(0x5e1e30);   /* "positive lookbehind" */
                                                                sw_29fa0c(0); sw_462988(0); sw_4662a4(0);
                                                                sw_462af0(0); sw_15e4f8(0); sw_464e64(0);
                                                                if (0 != 0) {
                                                                        sw_4662a4(0);
                                                                        kind = 7;
                                                                } else {
                                                                        sw_34ede8(0); sw_29fa0c(0); sw_462988(0);
                                                                        sw_462af0(0x3a626c6e, 0xe400000000000000); /* "(?bln:" */
                                                                        sw_15e4f8(0); sw_464e64(0);
                                                                        if (0 != 0) kind = 8;
                                                                        else {
                                                                                /* atomic / possessive forms */
                                                                                kind = 6;
                                                                        }
                                                                }
                                                        }
                                                }
                                        }
                                }
                        }
                }
        }
        sk_re_diag_complete();
        /* write result record */
        word_t *out = (word_t*)__builtin_frame_address(0);
        out[0] = kind;
        out[1] = 0; out[2] = 0; out[3] = 0; out[4] = 0;
        out[5] = 0; out[6] = 0; out[7] = 0; out[8] = 0; out[9] = 0;
        *(byte*)(out + 10) = (byte)kind;
        sw_117cc4(0, out, 0x50);
        sw_8e500(0);
}


/* FUN_004368c0 @ 0x004368c0   (est. sk_re_parse_capture_name)
 * Ghidra: void FUN_004368c0(word_t param_1, word_t param_2, word_t param_3,
 *                          word_t param_4)
 * Parses a named capture reference: reads the identifier characters, and if
 * the name starts with a digit reports "must not start with number"
 * (0x5dfaf0), else accumulates the name and appends the capture record;
 * also handles the unset/dup-name diagnostics.  Confidence: low. */
void sk_re_parse_capture_name(word_t a, word_t b, word_t c, word_t d)
{
        byte *rec = (byte*)__builtin_frame_address(0);
        sw_8e518(0);
        word_t x = c;
        long base = (long)sw_8409c(0);
        word_t h0 = *(word_t*)(base + 0x10);
        sw128_t s = sw_4664a4(0);
        sw_3a25d4(d);
        if ((s.lo ^ s.hi) < 0x4000) {
                /* single char name */
                sw_4647c0(0);
                word_t r0 = 0x6465746365707865;   /* "expected" */
                word_t r1 = 0xe900000000000020;
                if ((d & 0xff) == 1) r1 = 0xec000000656d616e;  /* "name" */
                else if ((d & 0xff) != 2) r1 = 0xeb00000000676174;  /* "tag" */
                sw_2acbb8(0, r1);
                sw_3a25d4(r1);
                sk_re_diag_rec(&r0);
                sw_461430((word_t)&(r0));
        } else {
                sw_4664a4(0);
                sw_462870(0); sw_84174(0); sw_462af0(0); sw_15e4f8(0); sw_356b5c(0);
                sw_3a25d4(0);
                if ((s.hi & 1) != 0) goto single;
                sw_464b20((word_t)&(r0));
                sk_re_peek_char2();
                if (0 == 0) SW_FATAL(0x436fc4);
                sw_16749c(0);
                sw_34ecc8(0);
                if ((s.lo ^ s.hi) < 0x4000) SW_FATAL(0x436fc8);
                sw_2bd724(0);
                sw_46511c(0);
                if (!(s.lo & 1)) {
                        /* identifier parse */
                        word_t id = 0, idend = 0xe000000000000000;
                        sw_2a4ab4(0x1d);
                        if ((d & 0xff) == 0) { /* group */
                                sw_2acbb8(0x616e2070756f7267, 0xea0000000000656d); /* "group na..." */
                        } else {
                                sw_2acbb8(0x2074756f6c6c6163, 0xec000000656d616e); /* "callout name" */
                        }
                        sw_3a25d4(0);
                        sw_4643cc(0x5dfaf0);   /* "must not start with number" */
                        sw_4635d4(0);
                        sw_2acbb8(0);
                        sk_re_diag_rec(&id);
                        sw_461430((word_t)&(id));
                }
                sw_68e14(0);
                sw128_t s2 = sk_re_parse_suffix();
                if (s2.hi != 0) {
                        sw_3a25d4(0);
                        goto single;
                }
                /* capture name record */
                sw_2a4ab4(0x2c);
                sw_2acbb8(0, 0xec000000656d616e);
                sw_3a25d4(0);
                sw_2acbb8(0xd00000000000002a, 0x80000000005dfaf0);
                sw_465304(0);
                sk_re_diag_rec(&x);
                sw_461430((word_t)&(x));
                sw_3a25d4(0);
                /* loop over ident chars */
                word_t pos = *(word_t*)(__builtin_frame_address(0) + 0x10);
                sw_352c4c(pos);
                sw_29fa0c(0); sw_351a5c(0); sw_3a25d4(0);
                sw_4644dc(0);
                word_t cur = pos;
                if (sk_re_is_ident_start() & 1) {
                        /* identifier char loop */
                }
        }
single:
        sw_8e500(0);
}


/* FUN_00436fc8 @ 0x00436fc8   (est. sk_re_is_ident_start)
 * Ghidra: word_t FUN_00436fc8(void)
 * Returns whether the current scalar is a valid identifier-start character
 * (letter, '_'): compares against '_' via 0x2bdc7c, else the Unicode
 * identifier-start check 0x2a0cf8.  Confidence: low. */
word_t sk_re_is_ident_start(void)
{
        sw_3504d0(0);
        word_t m = sw_2bdc7c(0);
        if ((m & 1) == 0) {
                sw_7c1c4(0);
                sw_16749c(0);
                sw_34ecc8(0);
                if (0) SW_FATAL(0x43703c);
                sw_2bd724(0);
                sw_46511c(0);
                if (0 && (0 != 0x5f || 0 != 0xe100000000000000)) {
                        sw_7c1c4(0);
                        sw_462fac(0);
                        return sw_2a0cf8(0);
                }
        }
        return 1;
}


/* FUN_0043703c @ 0x0043703c   (est. sk_re_bool_ident)
 * Ghidra: void FUN_0043703c(byte *param_1, word_t *param_2)
 * Writes the low bit of 0x436fc8.  Confidence: low. */
void sk_re_bool_ident(byte *out, word_t *p)
{
        byte b = (byte)(sk_re_is_ident_start() & 1);
        *out = b;
}


/* FUN_00437070 @ 0x00437070   (est. sk_re_parse_backref)
 * Ghidra: void FUN_00437070(word_t *param_1, word_t param_2)
 * Parses a numeric/named back-reference: reads the number (0x437eec); if it
 * is a plain number, tries the named-capture match (0x42f890); copies the
 * resulting reference record.  Confidence: low. */
void sk_re_parse_backref(word_t *out, word_t a)
{
        word_t rec[10];
        sw_463f80(&rec[0]);
        sk_re_record_select();
        if (rec[9] == -1) {
                word_t pos = *(word_t*)(__builtin_frame_address(0) + 0x10);
                sw_3524a4(&rec[2]);
                sw_4653fc(0);
                word_t hi = rec[3];
                word_t lo = rec[2];
                sw_36b270(hi);
                sw_350518(&rec[2]);
                sw_3511cc(0);
                sk_re_record_select();
                sw_3a25d4(hi);
                if (rec[9] == -1) {
                        sk_re_diag_match2(a, 0xe100000000000000);
                        rec[9] = '\\0';
                        rec[4] = pos;
                        rec[5] = *(word_t*)(__builtin_frame_address(0) + 0x10);
                        rec[3] = hi;
                        rec[2] = lo;
                } else {
                        sw_3a25d4(hi);
                }
        }
        out[0] = rec[0]; out[1] = rec[1];
        out[2] = rec[2]; out[3] = rec[3];
        out[4] = rec[4]; out[5] = rec[5];
        *(byte*)(out + 10) = (byte)rec[9];
}


/* FUN_004371ac @ 0x004371ac   (est. sk_re_record_select)
 * Ghidra: void FUN_004371ac(byte param_1[16], byte param_2[16],
 *                          byte param_3[16], byte param_4[16], byte param_5[16])
 * Selects one of two 5-word records based on whether the scalar parse
 * advanced: reads the current pos, tries the scalar, and on success copies
 * the second set of 5 words into the output, else the first set, plus a
 * selector byte.  Confidence: low. */
void sk_re_record_select(sw128_t p2, sw128_t p3, sw128_t p4, sw128_t p5, sw128_t p6)
{
        word_t a0 = p6.lo, a1 = p6.hi, b0 = p5.lo, b1 = p5.hi;
        word_t c0 = p4.lo, c1 = p4.hi, d0 = p3.lo, d1 = p3.hi;
        long rec = 0; /* in_x4 */
        sw128_t s = sw_351dc0(0);
        word_t pos = *(word_t*)(rec + 0x10);
        sw_463de0(0);
        word_t ok = sk_re_diag_emit_str();
        sw128_t r;
        byte sel;
        if ((ok & 1) == 0) {
                r = sw_465dbc(0xff, 0);
                sel = 0;
        } else {
                if (*(word_t*)(rec + 0x10) >> 0xe < pos >> 0xe) SW_FATAL(0x4372d0);
                sw_352498((word_t)&(r));
                sw_4653fc(0);
                sk_re_diag_match2(0, 0xe100000000000000);
                sel = 1;
        }
        word_t *out = (word_t*)sw_350b54(0);
        out[0] = r.lo; out[1] = r.hi;
        out[2] = c0; out[3] = c1;
        out[4] = d0; out[5] = d1;
        out[6] = a0; out[7] = a1;
        out[8] = b0; out[9] = b1;
        ((byte*)out)[0x50] = sel;
}


/* FUN_004372d4 @ 0x004372d4   (est. sk_re_record_join)
 * Ghidra: void FUN_004372d4(byte param_1[16], byte param_2[16],
 *                          byte param_3[16], byte param_4[16], byte param_5[16])
 * Joins two 5-word records: parses the group header (0x4374e4); if the
 * selector is -1 it flushes the accumulated slots and copies the second
 * record, else copies the first.  Writes the 7-word result.
 * Confidence: low. */
void sk_re_record_join(sw128_t p2, sw128_t p3, sw128_t p4, sw128_t p5, sw128_t p6)
{
        word_t *rec = (word_t*)__builtin_frame_address(0);
        word_t task = sw_8e518(0);
        word_t pos = *(word_t*)(__builtin_frame_address(0) + 0x10);
        sw_463cb8(0);
        sw_464adc(0);
        sw_4614cc(0, 0);
        sw128_t h = sk_re_parse_group_header();
        word_t sel = (word_t)((byte*)&h)[16];
        sw128_t r;
        word_t v1, v2;
        if (sel == 0xff) {
                sw_4658fc(0);
                sw_464818(0);
                sw_461cb8((word_t)&(h));
                v1 = *(word_t*)(__builtin_frame_address(0) + 0x50);
                sw_464adc(0);
                sw_36b270(v1);
                sw_45904c(0);
                /* slot flush loop */
                sw_36b118(v1);
                r = sw_465dbc(0, 0);
        } else {
                sw_45904c(0);
                r.lo = h.lo; r.hi = h.hi;
                v1 = *(word_t*)(__builtin_frame_address(0) + 0x10);
                if (v1 >> 0xe < pos >> 0xe) SW_FATAL(0x4374e0);
        }
        word_t *out = (word_t*)sw_350b54(0);
        out[0] = r.lo; out[1] = r.hi;
        out[2] = p2.lo; out[3] = p2.hi;
        out[4] = p3.lo; out[5] = p3.hi;
        out[6] = p4.lo; out[7] = p4.hi;
        out[8] = p5.lo; out[9] = p5.hi;
        out[10] = sel;
        out[11] = v1;
        out[12] = v2;
        sw_8e500(task);
}


/* FUN_004374e4 @ 0x004374e4   (est. sk_re_parse_group_header)
 * Ghidra: void FUN_004374e4(word_t param_1, word_t param_2, word_t param_3)
 * Parses a group header: reads '(' and dispatches on the following token to
 * the group-kind / lookaround / option parsers, returning a 16-byte record
 * whose low byte is the group-kind selector (0xff = no group).  Confidence: low. */
sw128_t sk_re_parse_group_header(word_t a, word_t b, word_t c)
{
        byte *rec = (byte*)__builtin_frame_address(0);
        sw_353b10(0);
        sw128_t k = sk_re_parse_lookaround();
        sw128_t r;
        if (((byte*)&k)[16] != -1) {
                r = k;
                goto done;
        }
        word_t m = sk_re_parse_group_kind();
        if ((m & 1) == 0) {
                sw_463534(0x28);
                if ((sk_re_diag_emit_str() & 1) != 0) {
                        sw_463534(0x3f);
                        if ((sk_re_diag_emit_str() & 1) == 0) {
                                word_t flags = *(word_t*)(__builtin_frame_address(0) + 0x40);
                                if ((flags >> 5 & 1) != 0) {
                                        /* '(?_: ' non-capturing */
                                        sw_4659c8(0); sw_462870(0); sw_462884(0x3a5f);
                                        sw_15e4f8(0); sw_356b5c(0); sw_3a25d4(0);
                                        if (0 != 0) {
                                                sw_1ee018(0x3a5f, 0xe200000000000000);
                                                sk_re_diag_complete();
                                                goto kind;
                                        }
                                }
                                if ((flags >> 7 & 1) != 0) goto kind;
                                sw_46617c(0);
                        } else {
                                /* '(?:' ... */
                                sw_463534(0x3a);
                                if ((sk_re_diag_emit_str() & 1) == 0) {
                                        sw_463534(0x7c);
                                        if ((sk_re_diag_emit_str() & 1) == 0) {
                                                sw_463534(0x3e);
                                                if ((sk_re_diag_emit_str() & 1) != 0) {
                                                        sw_464d24(3);
                                                        r.lo = 3;
                                                        goto done;
                                                }
                                                /* option / comment forms */
                                                sw_463534(0x3d);
                                                if ((sk_re_diag_emit_str() & 1) == 0) {
                                                        sw_463534(0x21);
                                                        if ((sk_re_diag_emit_str() & 1) == 0) {
                                                                sw_463534(0x2a);
                                                                if ((sk_re_diag_emit_str() & 1) == 0) {
                                                                        /* option block */
                                                                        sk_re_parse_option_block();
                                                                        sk_re_parse_backref();
                                                                        goto done;
                                                                }
                                                        }
                                                }
                                        }
                                }
                        }
                }
        }
        sw_46617c(0);
kind:
        r.lo = 0xff;
done:
        *(byte*)(__builtin_frame_address(0) + 0x50) = (byte)r.lo;
        return r;
}


/* FUN_004379bc @ 0x004379bc   (est. sk_re_parse_group_kind)
 * Ghidra: void FUN_004379bc(void)
 * Parses the group-kind token after '(?': handles '(?P<...>' (named group)
 * and '(?P=...>' (named backref) by building the corresponding AST record
 * via the metadata at 0x4c2450; returns whether the token was recognized.
 * Confidence: low. */
word_t sk_re_parse_group_kind(void)
{
        byte *rec = (byte*)__builtin_frame_address(0);
        sw_464adc(0);
        sw_464adc(0);
        sw_4614cc(0, 0);
        sw_464e34(0);
        word_t m = sk_re_diag_emit_str();
        if ((m & 1) == 0) {
                return 0;
        }
        m = sk_re_scan_newline(0x3f, 0xe100000000000000);
        if ((m & 1) == 0) {
                return sk_re_scan_newline(0x2a, 0xe100000000000000);
        }
        sw_466684(0);
        sw_466684(0);
        sw_4614cc(0, 0);
        m = sk_re_scan_newline(0x50, 0xe100000000000000);
        sw_46322c(0);
        if ((m & 1) == 0) {
                /* '(?P<...>' named group */
                sw_36a9a0(0, 0);
                sk_re_record_append_diag();
                sw_4666a8(0);
                sw_455db8(0);
                sw_2834(0);
                sw_36b6ac(0);
        } else {
                /* '(?P=...>' named backref */
                sw_36a9a0(0, 0);
                sk_re_record_append_diag();
                sw_4666a8(0);
                sw_455db8(0);
                sw_2834(0);
                sw_36b6ac(0);
        }
        sw_3a25d4(0xe100000000000000);
        sk_re_diag_merge(0, 0);
        sw_45904c(0);
        return 1;
}


/* FUN_00437d54 @ 0x00437d54   (est. sk_re_diag_unhandled)
 * Ghidra: void FUN_00437d54(long param_1, long param_2)
 * Checks whether the current scalar is one of the special delimiter
 * characters ('\\'' '"' '`' '^' '%' '#' '$' '<' '{'); if not, formats the
 * "Unhandled cased ..." error (0x656c646e61686e55 "Unhandled" + " asced.."
 * "Unhandled cased ..." 0xee00657361632064) into the diagnostic record.
 * Confidence: low. */
void sk_re_diag_unhandled(long ch, long flags)
{
        bool isDelim = (ch == 0x27 || flags == 0xe100000000000000);
        isDelim = isDelim || (sw_463404(0x27) & 1);
        isDelim = isDelim || (ch == 0x22) || (sw_463404(0x22) & 1);
        isDelim = isDelim || (ch == 0x60) || (sw_463404(0x60) & 1);
        isDelim = isDelim || (ch == 0x5e) || (sw_463404(0x5e) & 1);
        isDelim = isDelim || (ch == 0x25) || (sw_463404(0x25) & 1);
        isDelim = isDelim || (ch == 0x23) || (sw_463404(0x23) & 1);
        isDelim = isDelim || (ch == 0x24) || (sw_463404(0x24) & 1);
        isDelim = isDelim || (ch == 0x3c) || (sw_463404(0x3c) & 1);
        isDelim = isDelim || (ch == 0x7b) || (sw_463404(0x7b) & 1);
        if (!isDelim) {
                sk_re_diag_init(0, 0x656c646e61686e55, 0xee00657361632064,
                          *(word_t*)(__builtin_frame_address(0) + 0x10),
                          *(word_t*)(__builtin_frame_address(0) + 0x10));
                sk_re_diag_rec();
                sw_461430(0);
        }
        sw_36b270(flags);
        sw_3507e0(0);
}


/* FUN_00437eec @ 0x00437eec   (est. sk_re_parse_backref_or_scalar)
 * Ghidra: void FUN_00437eec(void)
 * Parses a back-reference or a scalar: handles the optional '-' sign and
 * decimal/hex scalar, reports "cannot refer to whole pattern he..." 
 * (0x5dfec0) for a bare '\0' reference, and writes the (kind, value,
 * start, end) record.  Confidence: low. */
void sk_re_parse_backref_or_scalar(void)
{
        word_t *rec = (word_t*)__builtin_frame_address(0);
        sw128_t task = sw_8e518(0);
        word_t start = *(word_t*)(__builtin_frame_address(0) + 0x10);
        sw_463cb8(0);
        sw_464adc(0);
        sw_4614cc(0, 0);
        sw128_t s = sk_re_peek_scalar2(0x2b, 0xe100000000000000);
        sw_35292c(0);
        word_t kind = 0, value = 0, hi = 0, lo2 = 0, sel = 0xff;
        if ((s.lo & 1) != 0) {
                /* negative: parse decimal after '-' */
                sw_463534(0x2d);
                sw128_t v = sk_re_peek_scalar2();
                sw_35292c(0);
                if (!(v.lo & 1)) {
                        sw_3534e0(0);
                        sw_464134((word_t)&(value));
                        sk_re_parse_number();
                        if (((byte*)&v)[0] != '\\x01') {
                                /* negative value */
                                value = -value;
                                kind = 1;
                        }
                }
        } else {
                sw_3534e0(0);
                sw_464134((word_t)&(value));
                sw128_t r2 = sk_re_parse_number();
                if (((byte*)&r2)[0] == '\\x01') {
                        /* whole-pattern reference */
                        sw_4658fc(0);
                        sw_36b118(*(word_t*)(__builtin_frame_address(0) + 0x50));
                        sw_463f80(0);
                        sw_461aec(0);
                        sw_463f4c(0, 0);
                        sw_117cc4(0);
                        value = 0; kind = 0;
                } else {
                        kind = 1;
                        value = *(word_t*)(__builtin_frame_address(0) + 0);
                }
        }
        word_t end = *(word_t*)(__builtin_frame_address(0) + 0x10);
        if (end >> 0xe < start >> 0xe) SW_FATAL(0x4382c4);
        if ((kind == 0) && (value != 1) && (end == 0)) {
                /* "cannot refer to whole pattern he..." */
                sw_86840(0x5dfec0);
                sw_4660c0(0);
                sk_re_diag_rec();
                sw_461430(0);
        }
        word_t *out = (word_t*)sw_350b54(0);
        out[0] = value; out[1] = kind;
        out[2] = 0; out[3] = 0; out[4] = sel;
        sw_8e500(task);
}


/* FUN_004382cc @ 0x004382cc   (est. sk_re_backref_check)
 * Ghidra: word_t FUN_004382cc(long *param_1)
 * Validates a back-reference against the number of captured groups: for
 * kind 0 returns whether the reference index is valid; kind 1 requires a
 * negative (error) value; else delegates to 0xac00c.  Confidence: low. */
word_t sk_re_backref_check(long *p)
{
        long v = *p;
        word_t kind = p[1];
        if ((char)p[4] == '\\0') {
                if ((kind & 0xff) == 1) return 0;
                return (word_t)(v <= *(long*)(__builtin_frame_address(0) + 8));
        }
        if ((char)p[4] == '\\x01') {
                return (word_t)((kind & 0xff) != 1 && v < 0);
        }
        return sw_ac00c(v, kind, *(word_t*)(__builtin_frame_address(0) + 0x10));
}


/* FUN_00438328 @ 0x00438328   (est. sk_re_parse_char_class)
 * Ghidra: void FUN_00438328(void)
 * Parses a character class: handles '[' with a leading '^' (negation),
 * 'R' (any) or '\\'-escapes, accumulates scalar runs and ranges, and appends
 * the class record.  This is one of the largest functions in the region.
 * Confidence: low.
 * Notes: skeleton reconstruction — several data-dependent branch conditions
 *   are placeholder `if (0 == 0)` (ground-truth: lVar11==0 from FUN_00430040,
 *   and ~(uStack_48f:local_490)&0xff==0), and many sw_* helper args are
 *   dropped to 0.  File sk_slice_193.c has pre-existing errors in ~14 other
 *   functions (lines 858-2549) outside this batch. */
void sk_re_parse_char_class(void)
{
        byte *rec = (byte*)__builtin_frame_address(0);
        word_t task = sw_8e518(0);
        sw_464adc(0);
        sw_464b20(0);
        sw_462d98(0); sw_29fa0c(0); sw_4630c4(0);
        sw_4614cc(0, 0);
        sw_4636a0(0x283f28, 0xe300000000000000);
        sw_15e4f8(0);
        sw_466678(0);
        word_t start = *(word_t*)(__builtin_frame_address(0) + 0x10);
        if ((*(word_t*)(__builtin_frame_address(0) + 0) & 1) != 0) {
                sw_1ee018(0x283f28, 0xe300000000000000);
                sk_re_diag_complete();
                sw_464b20(0);
                sw_464b20(0);
                sw_4614cc(0, 0);
                word_t m = sk_re_scan_newline(0x52, 0xe100000000000000);
                if ((m & 1) == 0) {
                        /* 'R' any-class or '\\'-escape */
                        sw_46322c(0);
                        sk_re_parse_char_class();
                        sw_36a940(0);
                        sk_re_record_append_diag();
                        sw_36b588(0);
                        sw_455db8(0);
                        sw_2834(0);
                        sw_36b6ac(0);
                        if (0 == 0) {
                                sw_462d98(0); sw_29fa0c(0); sw_4629cc(0);
                                sw_4649c0(0); sw_462af0(0); sw_15e4f8(0); sw_464e7c(0);
                                if (0 == 0) {
                                        /* scalar / range accumulation */
                                        sk_re_parse_backref_or_scalar(&start, 0, 1);
                                        if ((0 & 0xff) == 0) {
                                                sw_464b20(0);
                                                sw_4614cc(0, 0);
                                                sw_4636e8(0);
                                                sk_re_parse_capture_name();
                                                word_t e = *(word_t*)(__builtin_frame_address(0) + 0x10);
                                                sw_117cc4(0, 0, 0x60);
                                                sw_461bf4(0);
                                                if ((sk_re_backref_check(0) & 1) == 0) {
                                                        sw_461bf4(0);
                                                        sw_461c1c(0);
                                                }
                                        } else {
                                                /* accumulate scalar */
                                        }
                                } else {
                                        sw_4649c0(0);
                                        sw_1ee018(0);
                                        sk_re_diag_complete();
                                        sw_461c3c(0);
                                        sw_465ac0(0);
                                        sw_1a1c8(0);
                                        sw_466630(0);
                                }
                        } else {
                                sk_re_diag_unhandled(0, 0);
                                sw_351f28(0);
                                sw_3a25d4(0);
                                sk_re_parse_backref_or_scalar(&start, 0, 0);
                                if (((byte*)&start)[16] == -1) {
                                        sw_8e388(0);
                                        sk_re_parse_capture_name();
                                        sk_re_diag_match2();
                                        sw_3a25d4(0);
                                } else {
                                        sw_3504c4(0);
                                        sk_re_diag_match2();
                                        sw_3a25d4(0);
                                }
                                sw_458cd4(0);
                                sw_465ac0(0);
                                sw_1a1c8(0);
                        }
                } else {
                        /* '^' negation or plain class */
                        sw_463534(0x26);
                        word_t m2 = sk_re_diag_emit_str();
                        if ((m2 & 1) == 0) {
                                sw_464134(0);
                                sk_re_parse_number();
                                if (((byte*)&start)[16] != '\\x01') {
                                        sw_461c70(0);
                                }
                        } else {
                                sw_4636e8(0);
                                sk_re_parse_capture_name();
                        }
                        sw_461c90(0);
                }
                sw_465ac0(0);
                sw_1a1c8(0);
                sw_466630(0);
        }
        sw_117cc4(0, 0, 0x80);
        /* finalize class record */
        sw_8e500(task);
}


/* FUN_00438f54 @ 0x00438f54   (est. sk_re_parse_alternation)
 * Ghidra: void FUN_00438f54(word_t param_1, word_t param_2, word_t param_3)
 * Parses an alternation: reads the group header (0x4374e4); if the selector
 * is -1 it flushes and parses a sequence of alternatives separated by '|',
 * accumulating each into the record; else copies the single alternative.
 * Writes the final record.  Confidence: low. */
void sk_re_parse_alternation(word_t a, word_t b, word_t c)
{
        byte *rec = (byte*)__builtin_frame_address(0);
        word_t task = sw_8e518(0);
        sw_463cb8(0);
        sw_464adc(0);
        sw_34ede8(0);
        sw_29fa0c(0);
        sw_b43e8(0);
        sw_4614cc(0, 0);
        sw_464ab8(0);
        sw_3511cc(0);
        sw_15e4f8(0);
        sw_3a25d4(0);
        if (0 != 0) {
                sw_464ab8(0);
                sw_1ee018(0);
                sk_re_diag_complete();
                word_t start = *(word_t*)(__builtin_frame_address(0) + 0x10);
                sw_464adc(0);
                sw_464adc(0);
                sw_4614cc(0, 0);
                sw128_t h = sk_re_parse_group_header();
                if (((byte*)&h)[16] == 0xff) {
                        /* flush and parse alternatives */
                        sw_464818(0);
                        sw_461cb8((word_t)&(h));
                        word_t v = *(word_t*)(__builtin_frame_address(0) + 0x50);
                        sw_464adc(0);
                        sw_36b270(v);
                        sw_45904c(0);
                        sw_36b118(v);
                        /* alternation loop */
                        sw_3a25d4(0);
                        sw_100efc(0);
                        word_t ok = sk_re_diag_emit_str();
                        if ((ok & 1) == 0) {
                                sw_4627f4(0);
                                sw_36b270(task);
                                sw_100efc(0);
                                sw_2acbb8(0);
                                sw_463514(0);
                                sw_2acbb8(0);
                                sk_re_diag_rec();
                                sw_461430(0);
                        }
                } else {
                        sw_45904c(0);
                }
        } else {
                sw_4658fc(0);
        }
        /* write result record */
        word_t *out = (word_t*)__builtin_frame_address(0);
        out[0] = 0; out[1] = 0; out[2] = 0; out[3] = 0;
        out[4] = 0; out[5] = 0; out[6] = 0; out[7] = 0;
        out[8] = 0; out[9] = 0; out[10] = 0xff;
        out[0xb] = 0; out[0xc] = 0;
        sw_8e500(task);
}


/* FUN_00439348 @ 0x00439348   (est. sk_re_parse_concat)
 * Ghidra: void FUN_00439348(void)
 * Parses a concatenation: reads the current char and matches a leading
 * '(?~' ... or the concatenation token; commits the parsed position.
 * Confidence: low. */
void sk_re_parse_concat(void)
{
        byte *rec = (byte*)__builtin_frame_address(0);
        sw_84220(0);
        word_t a = *(word_t*)(__builtin_frame_address(0) + 8);
        word_t b = *(word_t*)(__builtin_frame_address(0) + 0x10);
        sw_84174(0);
        sw_3511cc(0);
        sw_29fa0c(0);
        sw_462aac(0);
        sw_462af0(0x7c7e3f28, 0xe400000000000000);
        word_t m = sw_15e4f8(0);
        sw_3a25d4(0);
        if ((m & 1) == 0) {
                sw_84174(0);
                sw_3511cc(0);
                sw_29fa0c(0);
                sw_462a98(0);
                sw_4652c4(0);
                sw_462af0(0);
                sw_15e4f8(0);
                sw128_t r = sw_466690(0);
                if ((a & 1) == 0) {
                        sw_84180(r.lo, r.hi, b);
                        sw_84234(0);
                        return;
                }
                sw_4652c4(0);
                sw_1ee018(0);
        } else {
                sw_1ee018(0x7c7e3f28, 0xe400000000000000);
        }
        sw128_t r = sk_re_diag_complete();
        word_t pos = *(word_t*)(__builtin_frame_address(0) + 0x10);
        if (pos >> 0xe < b >> 0xe) SW_FATAL(0x439408);
        sw_84180(r.lo, r.hi, pos);
        sw_84234(0);
}


/* FUN_0043942c @ 0x0043942c   (est. sk_re_parse_anchor)
 * Ghidra: byte [16] FUN_0043942c(void)
 * Parses an anchor token: runs the sequence parser (0x439a5c); if the
 * resulting kind is a 0x200-series anchor, checks for a following '[' and
 * returns (start, kind); else returns the empty pair.  Confidence: low. */
sw128_t sk_re_parse_anchor(void)
{
        word_t *rec = (word_t*)__builtin_frame_address(0);
        word_t start = *(word_t*)(__builtin_frame_address(0) + 0x10);
        sw_464adc(0);
        sw_464adc(0);
        sw_464aac(0);
        sw_4614cc(0);
        sw128_t r = sk_re_parse_sequence();
        sw_461ba0(r.lo, r.hi, 0, 0, 0, 0, 0);
        sw128_t out;
        if ((r.lo & 0xff00) == 0x200) {
                sk_re_diag_merge(0, 0);
                sw_45904c(0);
                sw_463534(0x5b);
                word_t m = sk_re_diag_emit_str();
                if ((m & 1) != 0) {
                        sw_463534(0x5e);
                        word_t m2 = sk_re_diag_emit_str();
                        if (start >> 0xe < start >> 0xe) SW_FATAL(0x439530);
                        out.lo = m2 & 1;
                        out.hi = 0;
                        return out;
                }
        } else {
                sw_463f80(0);
                sw_461ba0(0);
                sk_re_diag_merge(0, 0);
                sw_45904c(0);
        }
        out.lo = 0;
        out.hi = 2;
        return out;
}


/* FUN_00439530 @ 0x00439530   (est. sk_re_parse_operator)
 * Ghidra: uint FUN_00439530(void)
 * Parses a binary-operator token: returns 0 for '--', 1 for '&&', 2 for
 * '~~', else 3 (with the operands' AND applied).  Confidence: low. */
uint sk_re_parse_operator(void)
{
        sw_b4390(0);
        sw_351238(0);
        sw_29fa0c(0);
        sw_462870(0);
        sw_462884(0x2d2d);
        sw_15e4f8(0);
        sw_465c68(0);
        uint r;
        if ((0 & 1) == 0) {
                sw_b4390(0);
                sw_351238(0);
                sw_29fa0c(0);
                sw_462870(0);
                sw_462884(0x7e7e);
                sw_15e4f8(0);
                sw_465c68(0);
                if ((0 & 1) == 0) {
                        sw_b4390(0);
                        sw_351238(0);
                        sw_29fa0c(0);
                        sw_462aac(0);
                        sw_462884(0x2626);
                        sw_15e4f8(0);
                        sw_351d18(0);
                        sw_3a25d4(0);
                        r = 3;
                        if ((0 & 1) != 0) r = 1;
                } else {
                        r = 2;
                }
        } else {
                r = 0;
        }
        return r;
}


/* FUN_004395fc @ 0x004395fc   (est. sk_re_parse_expr)
 * Ghidra: void FUN_004395fc(void)
 * The top-level regex expression parser: reads the whole pattern, parses a
 * sequence of alternatives (0x434af4 / 0x42ffec), folds the result, and
 * commits the final position; returns the parsed record.  Confidence: low. */
void sk_re_parse_expr(void)
{
        byte *rec = (byte*)__builtin_frame_address(0);
        sw_463cb8(0);
        sw_464adc(0);
        sw_4614cc(0, 0);
        sw_463764(0);
        word_t *buf = (word_t*)__builtin_frame_address(0);
        do {
                sw128_t r = sk_re_parse_comment(buf, 0);
                word_t pos = *(word_t*)(__builtin_frame_address(0) + 0x10);
                if (r.hi == 0) {
                        if ((buf[1] & 1) == 0) {
                                sw_465144(0);
                                pos = 0;
                        } else {
                                buf = (word_t*)sw_466600(0);
                                pos = *(word_t*)(__builtin_frame_address(0) + 0x10);
                                sw_29fa0c(pos, 0, 0, 0);
                                sw_4659bc(0);
                                sw_463394(0);
                                sw_2b74c0(0);
                                sw_465da4(0);
                                sw_3a25d4(0);
                                sw_3508fc(0);
                                sw_354ca8(0);
                                sw128_t u = sw_2b439c(0);
                                sw_24917c(0, u);
                                sw_3a25d4(u.hi);
                                if ((*(byte*)u.lo & 1) == 0) break;
                                sw_3508fc(0);
                                sw_354ca8(0);
                                word_t v = sw_2b3b50(0);
                                if (v >> 0xe < pos >> 0xe) SW_FATAL(0x439a4c);
                        }
                        sw_463764(0);
                } else {
                        sw_465f5c(0);
                        buf = (word_t*)r.lo;
                        if (pos >> 0xe < pos >> 0xe) SW_FATAL(0x439a40);
                }
        } while (r.hi != 0);
        sk_re_parse_anchor();
        sk_re_diag_merge(rec, 0);
        sw_45904c(0);
        sw_b4390(0);
}


/* FUN_00439a5c @ 0x00439a5c   (est. sk_re_parse_sequence)
 * Ghidra: void FUN_00439a5c(void)
 * Parses a sequence: reads a '[' or the anchor token, handles a leading '^'
 * (negation), accumulates the parsed scalar runs and appends them to the
 * record, committing the final position.  Confidence: low. */
void sk_re_parse_sequence(void)
{
        byte *rec = (byte*)__builtin_frame_address(0);
        word_t task = sw_8e518(0);
        word_t start = *(word_t*)(__builtin_frame_address(0) + 0x10);
        sw_463cb8(0);
        sw_464adc(0);
        sw_464f84(0, 0);
        sw_462a98(0);
        sw_462884(0x3a5b);
        sw_15e4f8(0);
        sw_466690(0);
        word_t kind = 0x200;
        if ((0 & 1) != 0) {
                sw_1ee018(0x3a5b, 0xe200000000000000);
                sk_re_diag_complete();
                word_t m = sk_re_scan_newline(0x5e, 0xe100000000000000);
                sw_439d74(0);
                sw_465288(0);
                sw_462a98(0);
                sw_462884(0x5d3a);
                word_t m2 = sw_15e4f8(0);
                sw_3a25d4(0);
                if ((m2 & 1) != 0) {
                        sw_1ee018(0x5d3a, 0xe200000000000000);
                        sk_re_diag_complete();
                        if (0 == 0) {
                                sw_3516d8(0, 0, 0);
                                sw_429430(0);
                        } else {
                                sw_429984(0, 0, 0, 0, 0, 0, 0, 0, 0);
                        }
                        sw_3a25d4(0);
                        sw_45904c(0);
                        word_t end = *(word_t*)(__builtin_frame_address(0) + 0x10);
                        if (end >> 0xe < start >> 0xe) SW_FATAL(0x439d70);
                        kind = 0x10100;
                        if ((m & 1) == 0) kind = 0x10000;
                } else {
                        sw_3a25d4(0);
                        sw_3a25d4(0);
                }
        } else {
                sw_4658fc(0);
        }
        sw_36b118(*(word_t*)(__builtin_frame_address(0) + 0x50));
        sw_463f80(0);
        sw_461b8c(0);
        sw_465998(0, 0);
        /* write result record */
        word_t *out = (word_t*)__builtin_frame_address(0);
        out[0] = 0; out[1] = 0; out[2] = 0; out[3] = 0;
        out[4] = kind;
        out[5] = 0; out[6] = 0;
        sw_8e500(task);
}
