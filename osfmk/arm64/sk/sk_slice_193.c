/* Recreated from cl4_kernel.raw (cL4 Secure Kernel, arm64e, image base 0) —
 * the cL4 microkernel (GL1). Ground truth: Ghidra FUN_ names + addresses.
 * All names are estimates unless string/header matched.
 *
 * SK193 slice (0x0042af18-0x00439a5c): the Swift `_StringProcessing` /
 * regular-expression literal parser embedded in the cL4 kernel.  This is the
 * code that parses Swift regex literals (`/pattern/`, `#/pattern/#`,
 * extended and semantic-level modes, capture groups, character classes,
 * lookarounds, backreferences, text-segment modes, etc.) into the compiled
 * Regex AST that the kernel's own Swift code uses.  Functionally the region
 * implements:
 *   - the regex-literal delimiters scanner and the opening/closing delimiter
 *     matcher (0x42af18-0x42d050),
 *   - the byte-stream / UTF-8 decode helpers and the 'no newline/quoted
 *     sequence' scanners (0x42f020-0x42f670),
 *   - the AST node construction and the 'record' list append primitives
 *     (0x42ec68, 0x42ed6c, 0x42ee6c),
 *   - the diagnostic/error path that formats a regex-parse failure into a
 *     Swift error and appends it to the diagnostic list (0x42dc90 etc.),
 *   - the multi-mode option parser ('i', 'J', 'm', 'n', 's', 'U', 'x',
 *     'w', 'D', 'P', 'S', 'W', 'y', 'X', 'u', 'b') with semantic-level /
 *     text-segment-mode handling (0x43519c),
 *   - the group/atom parser (0x434e98, 0x437eec, 0x438f54), the quantifier
 *     parser (0x432ed4), the character-class / scalar parser (0x4306bc,
 *     0x430d08, 0x431210, 0x43152c), and the lookaround/atomic-parser
 *     (0x4361a4).
 *
 * Most of the region is the Swift regex literal parser compiled to machine
 * code: 16-byte register-pair struct values (String / Character / Regex AST
 * fragments), overflow-checked arithmetic, CAS loops and the standard
 * retain/release heap protocol are rendered faithfully, but the high-level
 * Swift semantics cannot always be recovered.  Confidence is medium for the
 * scanner/state-machine helpers and low for the heavy AST-build functions.
 *
 * Anchoring ground-truth strings (in the binary):
 *   0x005dd3c0 "invalid UTF-8 found in source file..."
 *   0x005dd3a0 "unknown regex literal delimiter..."
 *   0x005dd360 "unprintable ASCII character found..."
 *   0x005dd330 "closing delimiter must appear on..."
 *   0x005dd300 "cannot parse regular expression: ..."
 *   0x005e1f00 "No valid delimiters"
 *   0x005dfc80 "expected ASCII for ..."
 *   0x005e0080 "number overflow"
 *   0x005dfd80 "matching option ..."
 *   0x005dfdd0 "expected 2 expressions in absent..."
 *   0x005dffa0 "... is confusable for a metacharac..."
 *   0x005dfea0 "... must appear after expression..."
 *   0x005dfe60 "backtracking directive ..."
 *   0x005dfd60 "unknown group kind ..."
 *   0x005dfd40 "unknown callout kind ..."
 *   0x005dfd00 "unknown text segment mode ..."
 *   0x005dfce0 "invalid matching option ..."
 *   0x005dfba0 "unknown character property ..."
 *   0x005df9c0 "unrecognized script ..."
 *   0x005df9a0 "unrecognized category ..."
 *   0x005df980 "unrecognized block ..."
 *   0x005df920 "invalid age format for ..."
 *   0x005df900 "invalid numeric value ..."
 *   0x005df960 "unrecognized numeric type ..."
 *   0x005df8d0 "invalid canonical combining clas..."
 *   0x005dfb10 "must only contain alphanumeric c..."
 *   0x005dfac0 "text segment mode cannot be unse..."
 *   0x005df870 "... is a deprecated Unicode property..."
 *   0x005df850 "no capture numbered"
 *   0x005df830 "no capture named ..."
 *   0x005df810 "... already exists"
 *   0x005df790 "... must compare less than or equa..."
 *   0x005df7c0 "range lower bound ..."
 *   0x005e0020 "expected non-empty contents..."
 *   0x005e0590 "Invalid scalar value U+..."
 *   0x005e0480 / 0x005e0450 / 0x005e0400 diagnostic string fragments
 *   0x005dff50 "quoted sequence may not span mul..."
 *   0x005e0000 "expected escape sequence..."
 *   0x005dfec0 "cannot refer to whole pattern he..."
 *   0x005dfca0 "cannot remove matching options w..."
 *   0x005dfa90 "semantic level cannot be unset...o..."
 *   0x005e1df0 "positive lookahead ..."
 *   0x005e1e10 "negative lookahead ..."
 *   0x005e1e30 "positive lookbehind ..."
 *   0x005e1e50 / 0x005e1e70 "non-atomic positive lookahead..."
 *   0x005e02d0 "text segment mode"
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

/* 16-byte Swift value returned/held in a register pair (String, Character,
 * or a 16-byte Regex AST fragment).  lo = x0/x8 half, hi = x1/x9 half. */
typedef struct sw128 {
    uint64_t lo;
    uint64_t hi;
} sw128_t;
typedef struct sw96 {
    uint64_t lo;
    uint32_t hi;
} sw96_t;

#define SW_FATAL(addr) __builtin_trap()   /* SoftwareBreakpoint(1,<addr>) path */

/* LOAcquire / LORelease / GENTER / GEXIT opaque primitives. */
#define LOAcquire()      do { } while (0)
#define LORelease()      do { } while (0)
#define GENTER()         do { } while (0)   /* GENTER opcode 0x00201420 */
#define GEXIT()          do { } while (0)   /* GEXIT opcode 0x00201400 */
#define LZCOUNT(x)       __builtin_clzll(x)
#define POPCOUNT(x)      __builtin_popcountll(x)

/* ---- Shared Swift-runtime / String-processing externs ---------------------
 * Out-of-region helpers called by this slice (FUN_ address in comment).
 * Names are estimates; the Swift `_StringProcessing`/runtime code they come
 * from is reconstructed by sibling SK slices.  Arity follows each decompile.
 * ---- */
extern word_t sk_swift_current_task();              /* FUN_0008e518 */
extern void   sk_swift_retain(word_t);              /* FUN_0036b270 */
extern void   sk_swift_release(word_t);             /* FUN_0036b118 */
extern void   sk_swift_release2(word_t);            /* FUN_003a25d4 */
extern word_t sk_str_subscript(word_t, word_t, word_t, word_t, word_t, word_t); /* FUN_002a9d64 */
extern word_t sk_str_compare(word_t, word_t, word_t, word_t, int); /* FUN_002a0cf8 */
extern void   sk_str_append(word_t, word_t);        /* FUN_002acbb8 thunk */
extern void   sk_alloc_report(void);                /* FUN_002a4ab4 */
extern word_t sk_chr_decode(word_t, word_t);        /* FUN_002a9ba8 */
extern word_t sk_str_slice(word_t, word_t, word_t, word_t); /* FUN_002a3e64 */
extern word_t sk_substring_of(word_t, word_t, word_t, word_t); /* FUN_002b4120 */
extern word_t sk_utf8_decode(word_t, word_t);       /* FUN_002b5ba0 */
extern word_t sk_utf8_decode_adv(word_t, word_t);   /* FUN_002b5e10 */
extern word_t sk_utf16_decode(word_t, word_t);      /* FUN_002b141c */
extern word_t sk_str_split(word_t, word_t);         /* FUN_002b3f40 */
extern word_t sk_str_index_after(word_t, word_t);   /* FUN_002b74c0 */
extern word_t sk_str_index_before(word_t, word_t);  /* FUN_002ab388 */
extern word_t sk_uni_fold(word_t, word_t);          /* FUN_002b439c */
extern void   sk_regex_run_diag(void);              /* FUN_00461cb8 */

/* The 'record'/'log' builder object accessed at +0x10 count and +0x20 first
 * 0x50-byte slot, with slots strided 0x50 (0x50 = 80 bytes).  Declared here
 * so the region's list-append helpers can build it. */
extern word_t sk_log_grow(word_t);                  /* FUN_003a261c */
extern word_t sk_log_grow2(word_t);                 /* FUN_0045636c */
extern word_t sk_log_bump(word_t);                  /* FUN_00456650 */
extern void   sk_log_set(word_t);                   /* FUN_00117cc4 */

/* UTF-8 / scalar utilities (region 0x0002xxxx-0x0001xxxx). */
extern word_t sk_utf8_len(word_t, word_t);          /* FUN_0001da84 */
extern word_t sk_utf8_advance(word_t, word_t, word_t); /* FUN_001676cc */
extern word_t sk_utf8_is_ascii(word_t);             /* FUN_002a49a8 */

/* ---- Region-internal forward declarations (defined in this file) ---------- */
void FUN_0042c958(word_t *out, char *start, char *end, word_t rec, char *ext); /* est. regex_parse_delimited */
void FUN_0042be08(word_t mode);                     /* est. scan_next_escaped_char */
void FUN_0042c60c(void);                            /* est. parse_delimiter */
void FUN_0042dc90(void);                            /* est. diag_emit */
void FUN_0042f584(void);                            /* est. diag_init */
void FUN_0042f670(void);                            /* est. parse_scalar */
void FUN_0042fc4c(void);                            /* est. next_char */
void FUN_0042fe0c(word_t pos, word_t x);            /* est. advance_pos */
void FUN_0042fea0(void);                            /* est. peek_char */
void FUN_0042ffec(void);                            /* est. peek_char_pair */
void FUN_0042ec68(word_t sel, word_t a, word_t b, word_t c, word_t d); /* est. record_append */
void FUN_0042ed6c(word_t src);                      /* est. record_extend */
void FUN_0042ee6c(word_t a, word_t b, word_t c, word_t d); /* est. record_merge */
void FUN_0042f514(void);                            /* est. diag_append_record */
void FUN_0042ec5c(void);                            /* est. diag_flush */
void FUN_0042e930(void);                            /* est. diag_reset */
void FUN_0042f890(void);                            /* est. diag_report_match */
void FUN_0042f7d4(void);                            /* est. diag_report_match2 */
void FUN_0042f9dc(void);                            /* est. diag_append_match */
void FUN_0042fa98(void);                            /* est. diag_append_match2 */
void FUN_0042fca8(void);                            /* est. record_release */
void FUN_0042fd4c(void);                            /* est. diag_complete */
void FUN_0042ffac(void);                            /* est. parse_quantifier_star */
void FUN_00430040(void);                            /* est. record_append_diag */
void FUN_004301e0(void);                            /* est. str_slice_of */
void FUN_004302a0(void);                            /* est. parse_expr_suffix */
void FUN_00430338(void);                            /* est. parse_expr_suffix2 */
void FUN_004303c4(void);                            /* est. parse_scalar_str */
void FUN_004304e0(void);                            /* est. is_scalar_class */
void FUN_00430584(void);                            /* est. bool_sink_scalar */
void FUN_004305c4(void);                            /* est. bool_sink_unicode */
void FUN_00430604(void);                            /* est. bool_sink_uni_prop */
void FUN_00430644(void);                            /* est. scalar_to_utf8 */
void FUN_004306bc(void);                            /* est. parse_scalar_seq */
void FUN_00430bf4(void);                            /* est. diag_invalid_scalar */
void FUN_00430d08(void);                            /* est. parse_number */
void FUN_00431210(void);                            /* est. parse_number_radix */
void FUN_0043152c(void);                            /* est. parse_group_number */
void FUN_00431604(void);                            /* est. parse_ref_number */
void FUN_004317c4(void);                            /* est. parse_unicode_property */
void FUN_004323ac(void);                            /* est. parse_quote */
void FUN_004327c4(void);                            /* est. parse_group_body */
void FUN_00432c48(void);                            /* est. parse_group_end */
void FUN_00432ed4(void);                            /* est. parse_quantifier */
void FUN_00433938(void);                            /* est. diag_emit_msg */
void FUN_004339a8(void);                            /* est. parse_escape */
void FUN_00434054(void);                            /* est. diag_done */
void FUN_004340b0(void);                            /* est. parse_quoted_seq */
void FUN_004345a4(void);                            /* est. parse_balanced_group */
void FUN_00434af4(void);                            /* est. parse_comment */
void FUN_00434e98(void);                            /* est. parse_atom */
void FUN_00435110(void);                            /* est. diag_finalize */
void FUN_0043519c(void);                            /* est. parse_mode_option */
void FUN_004356f0(void);                            /* est. parse_option_block */
void FUN_00435ecc(void);                            /* est. parse_option_end */
void FUN_004361a4(void);                            /* est. parse_lookaround */
void FUN_004368c0(void);                            /* est. parse_capture_name */
void FUN_00436fc8(void);                            /* est. is_ident_start */
void FUN_0043703c(void);                            /* est. bool_sink_ident */
void FUN_00437070(void);                            /* est. parse_backref */
void FUN_004371ac(void);                            /* est. record_select */
void FUN_004372d4(void);                            /* est. record_join */
void FUN_004374e4(void);                            /* est. parse_group_header */
void FUN_004379bc(void);                            /* est. parse_group_kind */
void FUN_00437d54(void);                            /* est. diag_unhandled_delim */
void FUN_00437eec(void);                            /* est. parse_backref_or_scalar */
void FUN_004382cc(void);                            /* est. backref_check */
void FUN_00438328(void);                            /* est. parse_char_class */
void FUN_00438f54(void);                            /* est. parse_alternation */
void FUN_00439348(void);                            /* est. parse_concatenation */
void FUN_0043942c(void);                            /* est. parse_anchor */
void FUN_00439530(void);                            /* est. parse_operator */
void FUN_004395fc(void);                            /* est. parse_expr */
void FUN_00439a5c(void);                            /* est. parse_sequence */
