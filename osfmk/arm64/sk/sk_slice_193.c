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

/* ---- Out-of-region helper externs (FUN_ addr in comment) ---- */
extern word_t sw_002534(...);  /* FUN_00002534 */
extern word_t sw_0026e8(...);  /* FUN_000026e8 */
extern word_t sw_002818(...);  /* FUN_00002818 */
extern word_t sw_002834(...);  /* FUN_00002834 */
extern word_t sw_002850(...);  /* FUN_00002850 */
extern word_t sw_002874(...);  /* FUN_00002874 */
extern word_t sw_01a1c8(...);  /* FUN_0001a1c8 */
extern word_t sw_01d7a0(...);  /* FUN_0001d7a0 */
extern word_t sw_01da84(...);  /* FUN_0001da84 */
extern word_t sw_027724(...);  /* FUN_00027724 */
extern word_t sw_027754(...);  /* FUN_00027754 */
extern word_t sw_027788(...);  /* FUN_00027788 */
extern word_t sw_068e14(...);  /* FUN_00068e14 */
extern word_t sw_06a4c0(...);  /* FUN_0006a4c0 */
extern word_t sw_06b3f4(...);  /* FUN_0006b3f4 */
extern word_t sw_06b42c(...);  /* FUN_0006b42c */
extern word_t sw_06b6a0(...);  /* FUN_0006b6a0 */
extern word_t sw_06b6f4(...);  /* FUN_0006b6f4 */
extern word_t sw_072178(...);  /* FUN_00072178 */
extern word_t sw_0776cc(...);  /* FUN_000776cc */
extern word_t sw_077888(...);  /* FUN_00077888 */
extern word_t sw_077894(...);  /* FUN_00077894 */
extern word_t sw_0778b4(...);  /* FUN_000778b4 */
extern word_t sw_07c028(...);  /* FUN_0007c028 */
extern word_t sw_07c1a4(...);  /* FUN_0007c1a4 */
extern word_t sw_07c1c4(...);  /* FUN_0007c1c4 */
extern word_t sw_0839d8(...);  /* FUN_000839d8 */
extern word_t sw_084000(...);  /* FUN_00084000 */
extern word_t sw_08409c(...);  /* FUN_0008409c */
extern word_t sw_084174(...);  /* FUN_00084174 */
extern word_t sw_084180(...);  /* FUN_00084180 */
extern word_t sw_084220(...);  /* FUN_00084220 */
extern word_t sw_084234(...);  /* FUN_00084234 */
extern word_t sw_0863bc(...);  /* FUN_000863bc */
extern word_t sw_086840(...);  /* FUN_00086840 */
extern word_t sw_08e388(...);  /* FUN_0008e388 */
extern word_t sw_08e500(...);  /* FUN_0008e500 */
extern word_t sw_08e518(...);  /* FUN_0008e518 */
extern word_t sw_09461c(...);  /* FUN_0009461c */
extern word_t sw_09e218(...);  /* FUN_0009e218 */
extern word_t sw_0a6f68(...);  /* FUN_000a6f68 */
extern word_t sw_0a6f88(...);  /* FUN_000a6f88 */
extern word_t sw_0aa4ec(...);  /* FUN_000aa4ec */
extern word_t sw_0abad0(...);  /* FUN_000abad0 */
extern word_t sw_0ac00c(...);  /* FUN_000ac00c */
extern word_t sw_0b03cc(...);  /* FUN_000b03cc */
extern word_t sw_0b05bc(...);  /* FUN_000b05bc */
extern word_t sw_0b077c(...);  /* FUN_000b077c */
extern word_t sw_0b430c(...);  /* FUN_000b430c */
extern word_t sw_0b4390(...);  /* FUN_000b4390 */
extern word_t sw_0b43e8(...);  /* FUN_000b43e8 */
extern word_t sw_0b4528(...);  /* FUN_000b4528 */
extern word_t sw_0b4594(...);  /* FUN_000b4594 */
extern word_t sw_0b45b0(...);  /* FUN_000b45b0 */
extern word_t sw_0dbc98(...);  /* FUN_000dbc98 */
extern word_t sw_0dbed0(...);  /* FUN_000dbed0 */
extern word_t sw_0e15d8(...);  /* FUN_000e15d8 */
extern word_t sw_0e46d0(...);  /* FUN_000e46d0 */
extern word_t sw_0f4ae8(...);  /* FUN_000f4ae8 */
extern word_t sw_100e34(...);  /* FUN_00100e34 */
extern word_t sw_100efc(...);  /* FUN_00100efc */
extern word_t sw_117cc4(...);  /* FUN_00117cc4 */
extern word_t sw_15e4f8(...);  /* FUN_0015e4f8 */
extern word_t sw_16749c(...);  /* FUN_0016749c */
extern word_t sw_1676cc(...);  /* FUN_001676cc */
extern word_t sw_1a84f4(...);  /* FUN_001a84f4 */
extern word_t sw_1a8564(...);  /* FUN_001a8564 */
extern word_t sw_1ae8a8(...);  /* FUN_001ae8a8 */
extern word_t sw_1afa84(...);  /* FUN_001afa84 */
extern word_t sw_1b28d4(...);  /* FUN_001b28d4 */
extern word_t sw_1b798c(...);  /* FUN_001b798c */
extern word_t sw_1b9084(...);  /* FUN_001b9084 */
extern word_t sw_1e9c78(...);  /* FUN_001e9c78 */
extern word_t sw_1ebfb0(...);  /* FUN_001ebfb0 */
extern word_t sw_1ed960(...);  /* FUN_001ed960 */
extern word_t sw_1ee018(...);  /* FUN_001ee018 */
extern word_t sw_1fcefc(...);  /* FUN_001fcefc */
extern word_t sw_205844(...);  /* FUN_00205844 */
extern word_t sw_2298d4(...);  /* FUN_002298d4 */
extern word_t sw_229a3c(...);  /* FUN_00229a3c */
extern word_t sw_22d2f4(...);  /* FUN_0022d2f4 */
extern word_t sw_24917c(...);  /* FUN_0024917c */
extern word_t sw_24d9ac(...);  /* FUN_0024d9ac */
extern word_t sw_299540(...);  /* FUN_00299540 */
extern word_t sw_29e8dc(...);  /* FUN_0029e8dc */
extern word_t sw_29f0b0(...);  /* FUN_0029f0b0 */
extern word_t sw_29fa0c(...);  /* FUN_0029fa0c */
extern word_t sw_29fb80(...);  /* FUN_0029fb80 */
extern word_t sw_2a0cf8(...);  /* FUN_002a0cf8 */
extern word_t sw_2a3e64(...);  /* FUN_002a3e64 */
extern word_t sw_2a49a8(...);  /* FUN_002a49a8 */
extern word_t sw_2a4ab4(...);  /* FUN_002a4ab4 */
extern word_t sw_2a9ba8(...);  /* FUN_002a9ba8 */
extern word_t sw_2a9d64(...);  /* FUN_002a9d64 */
extern word_t sw_2ab388(...);  /* FUN_002ab388 */
extern word_t sw_2aca00(...);  /* FUN_002aca00 */
extern word_t sw_2acbb8(...);  /* FUN_002acbb8 */
extern word_t sw_2b141c(...);  /* FUN_002b141c */
extern word_t sw_2b24b8(...);  /* FUN_002b24b8 */
extern word_t sw_2b3b50(...);  /* FUN_002b3b50 */
extern word_t sw_2b3f40(...);  /* FUN_002b3f40 */
extern word_t sw_2b4120(...);  /* FUN_002b4120 */
extern word_t sw_2b439c(...);  /* FUN_002b439c */
extern word_t sw_2b5ba0(...);  /* FUN_002b5ba0 */
extern word_t sw_2b5e10(...);  /* FUN_002b5e10 */
extern word_t sw_2b5ed4(...);  /* FUN_002b5ed4 */
extern word_t sw_2b7088(...);  /* FUN_002b7088 */
extern word_t sw_2b74c0(...);  /* FUN_002b74c0 */
extern word_t sw_2bc2dc(...);  /* FUN_002bc2dc */
extern word_t sw_2bd724(...);  /* FUN_002bd724 */
extern word_t sw_2bd8f0(...);  /* FUN_002bd8f0 */
extern word_t sw_2bd9cc(...);  /* FUN_002bd9cc */
extern word_t sw_2bda40(...);  /* FUN_002bda40 */
extern word_t sw_2bdb90(...);  /* FUN_002bdb90 */
extern word_t sw_2bdc7c(...);  /* FUN_002bdc7c */
extern word_t sw_31b46c(...);  /* FUN_0031b46c */
extern word_t sw_31b49c(...);  /* FUN_0031b49c */
extern word_t sw_31e030(...);  /* FUN_0031e030 */
extern word_t sw_34a210(...);  /* FUN_0034a210 */
extern word_t sw_34bd90(...);  /* FUN_0034bd90 */
extern word_t sw_34c444(...);  /* FUN_0034c444 */
extern word_t sw_34d868(...);  /* FUN_0034d868 */
extern word_t sw_34db28(...);  /* FUN_0034db28 */
extern word_t sw_34e1ec(...);  /* FUN_0034e1ec */
extern word_t sw_34ecc8(...);  /* FUN_0034ecc8 */
extern word_t sw_34ede8(...);  /* FUN_0034ede8 */
extern word_t sw_34f3b4(...);  /* FUN_0034f3b4 */
extern word_t sw_34fe80(...);  /* FUN_0034fe80 */
extern word_t sw_350470(...);  /* FUN_00350470 */
extern word_t sw_3504a0(...);  /* FUN_003504a0 */
extern word_t sw_3504ac(...);  /* FUN_003504ac */
extern word_t sw_3504c4(...);  /* FUN_003504c4 */
extern word_t sw_3504d0(...);  /* FUN_003504d0 */
extern word_t sw_350518(...);  /* FUN_00350518 */
extern word_t sw_350530(...);  /* FUN_00350530 */
extern word_t sw_35053c(...);  /* FUN_0035053c */
extern word_t sw_350560(...);  /* FUN_00350560 */
extern word_t sw_3505c4(...);  /* FUN_003505c4 */
extern word_t sw_3505e8(...);  /* FUN_003505e8 */
extern word_t sw_350618(...);  /* FUN_00350618 */
extern word_t sw_35063c(...);  /* FUN_0035063c */
extern word_t sw_350738(...);  /* FUN_00350738 */
extern word_t sw_3507e0(...);  /* FUN_003507e0 */
extern word_t sw_350878(...);  /* FUN_00350878 */
extern word_t sw_3508fc(...);  /* FUN_003508fc */
extern word_t sw_350914(...);  /* FUN_00350914 */
extern word_t sw_350944(...);  /* FUN_00350944 */
extern word_t sw_350980(...);  /* FUN_00350980 */
extern word_t sw_350998(...);  /* FUN_00350998 */
extern word_t sw_3509bc(...);  /* FUN_003509bc */
extern word_t sw_3509c8(...);  /* FUN_003509c8 */
extern word_t sw_350a04(...);  /* FUN_00350a04 */
extern word_t sw_350a88(...);  /* FUN_00350a88 */
extern word_t sw_350b54(...);  /* FUN_00350b54 */
extern word_t sw_350b90(...);  /* FUN_00350b90 */
extern word_t sw_350bf0(...);  /* FUN_00350bf0 */
extern word_t sw_350bfc(...);  /* FUN_00350bfc */
extern word_t sw_3510b8(...);  /* FUN_003510b8 */
extern word_t sw_3511a8(...);  /* FUN_003511a8 */
extern word_t sw_3511cc(...);  /* FUN_003511cc */
extern word_t sw_3511d8(...);  /* FUN_003511d8 */
extern word_t sw_351238(...);  /* FUN_00351238 */
extern word_t sw_351274(...);  /* FUN_00351274 */
extern word_t sw_351354(...);  /* FUN_00351354 */
extern word_t sw_3514d0(...);  /* FUN_003514d0 */
extern word_t sw_3516d8(...);  /* FUN_003516d8 */
extern word_t sw_351714(...);  /* FUN_00351714 */
extern word_t sw_351744(...);  /* FUN_00351744 */
extern word_t sw_351790(...);  /* FUN_00351790 */
extern word_t sw_3517c0(...);  /* FUN_003517c0 */
extern word_t sw_35187c(...);  /* FUN_0035187c */
extern word_t sw_35199c(...);  /* FUN_0035199c */
extern word_t sw_3519a8(...);  /* FUN_003519a8 */
extern word_t sw_351a44(...);  /* FUN_00351a44 */
extern word_t sw_351a50(...);  /* FUN_00351a50 */
extern word_t sw_351a5c(...);  /* FUN_00351a5c */
extern word_t sw_351aec(...);  /* FUN_00351aec */
extern word_t sw_351c7c(...);  /* FUN_00351c7c */
extern word_t sw_351cd0(...);  /* FUN_00351cd0 */
extern word_t sw_351d18(...);  /* FUN_00351d18 */
extern word_t sw_351d30(...);  /* FUN_00351d30 */
extern word_t sw_351dc0(...);  /* FUN_00351dc0 */
extern word_t sw_351e08(...);  /* FUN_00351e08 */
extern word_t sw_351e20(...);  /* FUN_00351e20 */
extern word_t sw_351e3c(...);  /* FUN_00351e3c */
extern word_t sw_351f28(...);  /* FUN_00351f28 */
extern word_t sw_352290(...);  /* FUN_00352290 */
extern word_t sw_352480(...);  /* FUN_00352480 */
extern word_t sw_352498(...);  /* FUN_00352498 */
extern word_t sw_3524a4(...);  /* FUN_003524a4 */
extern word_t sw_3524b0(...);  /* FUN_003524b0 */
extern word_t sw_35292c(...);  /* FUN_0035292c */
extern word_t sw_352c4c(...);  /* FUN_00352c4c */
extern word_t sw_352c80(...);  /* FUN_00352c80 */
extern word_t sw_3534e0(...);  /* FUN_003534e0 */
extern word_t sw_3535a8(...);  /* FUN_003535a8 */
extern word_t sw_353abc(...);  /* FUN_00353abc */
extern word_t sw_353b10(...);  /* FUN_00353b10 */
extern word_t sw_353bc4(...);  /* FUN_00353bc4 */
extern word_t sw_353c30(...);  /* FUN_00353c30 */
extern word_t sw_354ca8(...);  /* FUN_00354ca8 */
extern word_t sw_356110(...);  /* FUN_00356110 */
extern word_t sw_3562d4(...);  /* FUN_003562d4 */
extern word_t sw_356328(...);  /* FUN_00356328 */
extern word_t sw_3567c8(...);  /* FUN_003567c8 */
extern word_t sw_356b5c(...);  /* FUN_00356b5c */
extern word_t sw_356f80(...);  /* FUN_00356f80 */
extern word_t sw_356f9c(...);  /* FUN_00356f9c */
extern word_t sw_3593c0(...);  /* FUN_003593c0 */
extern word_t sw_35aba4(...);  /* FUN_0035aba4 */
extern word_t sw_365b6c(...);  /* FUN_00365b6c */
extern word_t sw_36986c(...);  /* FUN_0036986c */
extern word_t sw_36993c(...);  /* FUN_0036993c */
extern word_t sw_369a30(...);  /* FUN_00369a30 */
extern word_t sw_369efc(...);  /* FUN_00369efc */
extern word_t sw_36a940(...);  /* FUN_0036a940 */
extern word_t sw_36a9a0(...);  /* FUN_0036a9a0 */
extern word_t sw_36b118(...);  /* FUN_0036b118 */
extern word_t sw_36b270(...);  /* FUN_0036b270 */
extern word_t sw_36b588(...);  /* FUN_0036b588 */
extern word_t sw_36b6ac(...);  /* FUN_0036b6ac */
extern word_t sw_377824(...);  /* FUN_00377824 */
extern word_t sw_377bec(...);  /* FUN_00377bec */
extern word_t sw_3a25d4(...);  /* FUN_003a25d4 */
extern word_t sw_3a2610(...);  /* FUN_003a2610 */
extern word_t sw_3a261c(...);  /* FUN_003a261c */
extern word_t sw_3f34b4(...);  /* FUN_003f34b4 */
extern word_t sw_4080b0(...);  /* FUN_004080b0 */
extern word_t sw_40ff40(...);  /* FUN_0040ff40 */
extern word_t sw_411624(...);  /* FUN_00411624 */
extern word_t sw_412d5c(...);  /* FUN_00412d5c */
extern word_t sw_41ca38(...);  /* FUN_0041ca38 */
extern word_t sw_41d070(...);  /* FUN_0041d070 */
extern word_t sw_41d8f4(...);  /* FUN_0041d8f4 */
extern word_t sw_41e0a0(...);  /* FUN_0041e0a0 */
extern word_t sw_41e188(...);  /* FUN_0041e188 */
extern word_t sw_41e21c(...);  /* FUN_0041e21c */
extern word_t sw_429398(...);  /* FUN_00429398 */
extern word_t sw_429430(...);  /* FUN_00429430 */
extern word_t sw_429984(...);  /* FUN_00429984 */
extern word_t sw_42aca4(...);  /* FUN_0042aca4 */
extern word_t sw_42acc4(...);  /* FUN_0042acc4 */
extern word_t sw_42ade4(...);  /* FUN_0042ade4 */
extern word_t sw_42ae78(...);  /* FUN_0042ae78 */
extern word_t sw_439d74(...);  /* FUN_00439d74 */
extern word_t sw_43a478(...);  /* FUN_0043a478 */
extern word_t sw_4455f8(...);  /* FUN_004455f8 */
extern word_t sw_4460cc(...);  /* FUN_004460cc */
extern word_t sw_4461bc(...);  /* FUN_004461bc */
extern word_t sw_448758(...);  /* FUN_00448758 */
extern word_t sw_448934(...);  /* FUN_00448934 */
extern word_t sw_448aac(...);  /* FUN_00448aac */
extern word_t sw_455db8(...);  /* FUN_00455db8 */
extern word_t sw_455fe4(...);  /* FUN_00455fe4 */
extern word_t sw_45636c(...);  /* FUN_0045636c */
extern word_t sw_4564e4(...);  /* FUN_004564e4 */
extern word_t sw_456650(...);  /* FUN_00456650 */
extern word_t sw_456714(...);  /* FUN_00456714 */
extern word_t sw_45694c(...);  /* FUN_0045694c */
extern word_t sw_456d50(...);  /* FUN_00456d50 */
extern word_t sw_456fa8(...);  /* FUN_00456fa8 */
extern word_t sw_4571b0(...);  /* FUN_004571b0 */
extern word_t sw_4573b0(...);  /* FUN_004573b0 */
extern word_t sw_457650(...);  /* FUN_00457650 */
extern word_t sw_4578dc(...);  /* FUN_004578dc */
extern word_t sw_457994(...);  /* FUN_00457994 */
extern word_t sw_457e80(...);  /* FUN_00457e80 */
extern word_t sw_457ed8(...);  /* FUN_00457ed8 */
extern word_t sw_458780(...);  /* FUN_00458780 */
extern word_t sw_458cd4(...);  /* FUN_00458cd4 */
extern word_t sw_458d68(...);  /* FUN_00458d68 */
extern word_t sw_458d78(...);  /* FUN_00458d78 */
extern word_t sw_458e50(...);  /* FUN_00458e50 */
extern word_t sw_458e80(...);  /* FUN_00458e80 */
extern word_t sw_458ea8(...);  /* FUN_00458ea8 */
extern word_t sw_458ebc(...);  /* FUN_00458ebc */
extern word_t sw_459024(...);  /* FUN_00459024 */
extern word_t sw_459034(...);  /* FUN_00459034 */
extern word_t sw_45904c(...);  /* FUN_0045904c */
extern word_t sw_460dbc(...);  /* FUN_00460dbc */
extern word_t sw_460e68(...);  /* FUN_00460e68 */
extern word_t sw_460e78(...);  /* FUN_00460e78 */
extern word_t sw_460ff4(...);  /* FUN_00460ff4 */
extern word_t sw_461430(...);  /* FUN_00461430 */
extern word_t sw_4614cc(...);  /* FUN_004614cc */
extern word_t sw_4618f4(...);  /* FUN_004618f4 */
extern word_t sw_461aec(...);  /* FUN_00461aec */
extern word_t sw_461b50(...);  /* FUN_00461b50 */
extern word_t sw_461b64(...);  /* FUN_00461b64 */
extern word_t sw_461b8c(...);  /* FUN_00461b8c */
extern word_t sw_461ba0(...);  /* FUN_00461ba0 */
extern word_t sw_461bb4(...);  /* FUN_00461bb4 */
extern word_t sw_461bd4(...);  /* FUN_00461bd4 */
extern word_t sw_461bf4(...);  /* FUN_00461bf4 */
extern word_t sw_461c1c(...);  /* FUN_00461c1c */
extern word_t sw_461c3c(...);  /* FUN_00461c3c */
extern word_t sw_461c70(...);  /* FUN_00461c70 */
extern word_t sw_461c90(...);  /* FUN_00461c90 */
extern word_t sw_461ca4(...);  /* FUN_00461ca4 */
extern word_t sw_461cb8(...);  /* FUN_00461cb8 */
extern word_t sw_462710(...);  /* FUN_00462710 */
extern word_t sw_462770(...);  /* FUN_00462770 */
extern word_t sw_462788(...);  /* FUN_00462788 */
extern word_t sw_4627b8(...);  /* FUN_004627b8 */
extern word_t sw_4627f4(...);  /* FUN_004627f4 */
extern word_t sw_462810(...);  /* FUN_00462810 */
extern word_t sw_46282c(...);  /* FUN_0046282c */
extern word_t sw_462870(...);  /* FUN_00462870 */
extern word_t sw_462884(...);  /* FUN_00462884 */
extern word_t sw_4628c4(...);  /* FUN_004628c4 */
extern word_t sw_4628f4(...);  /* FUN_004628f4 */
extern word_t sw_462974(...);  /* FUN_00462974 */
extern word_t sw_462988(...);  /* FUN_00462988 */
extern word_t sw_46299c(...);  /* FUN_0046299c */
extern word_t sw_4629b4(...);  /* FUN_004629b4 */
extern word_t sw_4629cc(...);  /* FUN_004629cc */
extern word_t sw_462a08(...);  /* FUN_00462a08 */
extern word_t sw_462a1c(...);  /* FUN_00462a1c */
extern word_t sw_462a34(...);  /* FUN_00462a34 */
extern word_t sw_462a48(...);  /* FUN_00462a48 */
extern word_t sw_462a5c(...);  /* FUN_00462a5c */
extern word_t sw_462a84(...);  /* FUN_00462a84 */
extern word_t sw_462a98(...);  /* FUN_00462a98 */
extern word_t sw_462aac(...);  /* FUN_00462aac */
extern word_t sw_462abc(...);  /* FUN_00462abc */
extern word_t sw_462af0(...);  /* FUN_00462af0 */
extern word_t sw_462b00(...);  /* FUN_00462b00 */
extern word_t sw_462b10(...);  /* FUN_00462b10 */
extern word_t sw_462b2c(...);  /* FUN_00462b2c */
extern word_t sw_462b40(...);  /* FUN_00462b40 */
extern word_t sw_462b54(...);  /* FUN_00462b54 */
extern word_t sw_462b6c(...);  /* FUN_00462b6c */
extern word_t sw_462b80(...);  /* FUN_00462b80 */
extern word_t sw_462ba8(...);  /* FUN_00462ba8 */
extern word_t sw_462c7c(...);  /* FUN_00462c7c */
extern word_t sw_462ce8(...);  /* FUN_00462ce8 */
extern word_t sw_462d0c(...);  /* FUN_00462d0c */
extern word_t sw_462d20(...);  /* FUN_00462d20 */
extern word_t sw_462d48(...);  /* FUN_00462d48 */
extern word_t sw_462d88(...);  /* FUN_00462d88 */
extern word_t sw_462d98(...);  /* FUN_00462d98 */
extern word_t sw_462e44(...);  /* FUN_00462e44 */
extern word_t sw_462ed8(...);  /* FUN_00462ed8 */
extern word_t sw_462f24(...);  /* FUN_00462f24 */
extern word_t sw_462f3c(...);  /* FUN_00462f3c */
extern word_t sw_462f5c(...);  /* FUN_00462f5c */
extern word_t sw_462f6c(...);  /* FUN_00462f6c */
extern word_t sw_462f7c(...);  /* FUN_00462f7c */
extern word_t sw_462fac(...);  /* FUN_00462fac */
extern word_t sw_462fbc(...);  /* FUN_00462fbc */
extern word_t sw_463000(...);  /* FUN_00463000 */
extern word_t sw_463014(...);  /* FUN_00463014 */
extern word_t sw_4630b0(...);  /* FUN_004630b0 */
extern word_t sw_4630c4(...);  /* FUN_004630c4 */
extern word_t sw_463130(...);  /* FUN_00463130 */
extern word_t sw_4631a8(...);  /* FUN_004631a8 */
extern word_t sw_46322c(...);  /* FUN_0046322c */
extern word_t sw_463280(...);  /* FUN_00463280 */
extern word_t sw_463290(...);  /* FUN_00463290 */
extern word_t sw_4632cc(...);  /* FUN_004632cc */
extern word_t sw_4632e0(...);  /* FUN_004632e0 */
extern word_t sw_463394(...);  /* FUN_00463394 */
extern word_t sw_463404(...);  /* FUN_00463404 */
extern word_t sw_463444(...);  /* FUN_00463444 */
extern word_t sw_4634b4(...);  /* FUN_004634b4 */
extern word_t sw_4634f4(...);  /* FUN_004634f4 */
extern word_t sw_463514(...);  /* FUN_00463514 */
extern word_t sw_463534(...);  /* FUN_00463534 */
extern word_t sw_463540(...);  /* FUN_00463540 */
extern word_t sw_463590(...);  /* FUN_00463590 */
extern word_t sw_4635c8(...);  /* FUN_004635c8 */
extern word_t sw_4635d4(...);  /* FUN_004635d4 */
extern word_t sw_4635e0(...);  /* FUN_004635e0 */
extern word_t sw_46361c(...);  /* FUN_0046361c */
extern word_t sw_463648(...);  /* FUN_00463648 */
extern word_t sw_463684(...);  /* FUN_00463684 */
extern word_t sw_4636a0(...);  /* FUN_004636a0 */
extern word_t sw_4636e8(...);  /* FUN_004636e8 */
extern word_t sw_4636f8(...);  /* FUN_004636f8 */
extern word_t sw_463708(...);  /* FUN_00463708 */
extern word_t sw_463728(...);  /* FUN_00463728 */
extern word_t sw_463764(...);  /* FUN_00463764 */
extern word_t sw_4637f0(...);  /* FUN_004637f0 */
extern word_t sw_463824(...);  /* FUN_00463824 */
extern word_t sw_463830(...);  /* FUN_00463830 */
extern word_t sw_463878(...);  /* FUN_00463878 */
extern word_t sw_463884(...);  /* FUN_00463884 */
extern word_t sw_46389c(...);  /* FUN_0046389c */
extern word_t sw_4638c0(...);  /* FUN_004638c0 */
extern word_t sw_463944(...);  /* FUN_00463944 */
extern word_t sw_463970(...);  /* FUN_00463970 */
extern word_t sw_46397c(...);  /* FUN_0046397c */
extern word_t sw_4639d8(...);  /* FUN_004639d8 */
extern word_t sw_463a38(...);  /* FUN_00463a38 */
extern word_t sw_463a58(...);  /* FUN_00463a58 */
extern word_t sw_463a68(...);  /* FUN_00463a68 */
extern word_t sw_463a78(...);  /* FUN_00463a78 */
extern word_t sw_463bbc(...);  /* FUN_00463bbc */
extern word_t sw_463bc8(...);  /* FUN_00463bc8 */
extern word_t sw_463c0c(...);  /* FUN_00463c0c */
extern word_t sw_463cb8(...);  /* FUN_00463cb8 */
extern word_t sw_463dbc(...);  /* FUN_00463dbc */
extern word_t sw_463de0(...);  /* FUN_00463de0 */
extern word_t sw_463e04(...);  /* FUN_00463e04 */
extern word_t sw_463e10(...);  /* FUN_00463e10 */
extern word_t sw_463f34(...);  /* FUN_00463f34 */
extern word_t sw_463f40(...);  /* FUN_00463f40 */
extern word_t sw_463f4c(...);  /* FUN_00463f4c */
extern word_t sw_463f74(...);  /* FUN_00463f74 */
extern word_t sw_463f80(...);  /* FUN_00463f80 */
extern word_t sw_463f94(...);  /* FUN_00463f94 */
extern word_t sw_463fac(...);  /* FUN_00463fac */
extern word_t sw_463fd0(...);  /* FUN_00463fd0 */
extern word_t sw_464000(...);  /* FUN_00464000 */
extern word_t sw_46400c(...);  /* FUN_0046400c */
extern word_t sw_464040(...);  /* FUN_00464040 */
extern word_t sw_464058(...);  /* FUN_00464058 */
extern word_t sw_464090(...);  /* FUN_00464090 */
extern word_t sw_464134(...);  /* FUN_00464134 */
extern word_t sw_46418c(...);  /* FUN_0046418c */
extern word_t sw_464234(...);  /* FUN_00464234 */
extern word_t sw_464268(...);  /* FUN_00464268 */
extern word_t sw_4642a8(...);  /* FUN_004642a8 */
extern word_t sw_4642e8(...);  /* FUN_004642e8 */
extern word_t sw_4642f8(...);  /* FUN_004642f8 */
extern word_t sw_464364(...);  /* FUN_00464364 */
extern word_t sw_4643cc(...);  /* FUN_004643cc */
extern word_t sw_4644dc(...);  /* FUN_004644dc */
extern word_t sw_464568(...);  /* FUN_00464568 */
extern word_t sw_464588(...);  /* FUN_00464588 */
extern word_t sw_464608(...);  /* FUN_00464608 */
extern word_t sw_46461c(...);  /* FUN_0046461c */
extern word_t sw_4647c0(...);  /* FUN_004647c0 */
extern word_t sw_4647f4(...);  /* FUN_004647f4 */
extern word_t sw_464818(...);  /* FUN_00464818 */
extern word_t sw_464854(...);  /* FUN_00464854 */
extern word_t sw_4648fc(...);  /* FUN_004648fc */
extern word_t sw_46490c(...);  /* FUN_0046490c */
extern word_t sw_464918(...);  /* FUN_00464918 */
extern word_t sw_464948(...);  /* FUN_00464948 */
extern word_t sw_4649c0(...);  /* FUN_004649c0 */
extern word_t sw_4649cc(...);  /* FUN_004649cc */
extern word_t sw_4649fc(...);  /* FUN_004649fc */
extern word_t sw_464a14(...);  /* FUN_00464a14 */
extern word_t sw_464a44(...);  /* FUN_00464a44 */
extern word_t sw_464a8c(...);  /* FUN_00464a8c */
extern word_t sw_464aac(...);  /* FUN_00464aac */
extern word_t sw_464ab8(...);  /* FUN_00464ab8 */
extern word_t sw_464ac4(...);  /* FUN_00464ac4 */
extern word_t sw_464adc(...);  /* FUN_00464adc */
extern word_t sw_464b20(...);  /* FUN_00464b20 */
extern word_t sw_464cf4(...);  /* FUN_00464cf4 */
extern word_t sw_464d18(...);  /* FUN_00464d18 */
extern word_t sw_464d24(...);  /* FUN_00464d24 */
extern word_t sw_464d50(...);  /* FUN_00464d50 */
extern word_t sw_464d5c(...);  /* FUN_00464d5c */
extern word_t sw_464d74(...);  /* FUN_00464d74 */
extern word_t sw_464d80(...);  /* FUN_00464d80 */
extern word_t sw_464da0(...);  /* FUN_00464da0 */
extern word_t sw_464dfc(...);  /* FUN_00464dfc */
extern word_t sw_464e28(...);  /* FUN_00464e28 */
extern word_t sw_464e34(...);  /* FUN_00464e34 */
extern word_t sw_464e64(...);  /* FUN_00464e64 */
extern word_t sw_464e70(...);  /* FUN_00464e70 */
extern word_t sw_464e7c(...);  /* FUN_00464e7c */
extern word_t sw_464ebc(...);  /* FUN_00464ebc */
extern word_t sw_464f84(...);  /* FUN_00464f84 */
extern word_t sw_46507c(...);  /* FUN_0046507c */
extern word_t sw_4650a0(...);  /* FUN_004650a0 */
extern word_t sw_4650ac(...);  /* FUN_004650ac */
extern word_t sw_4650e4(...);  /* FUN_004650e4 */
extern word_t sw_46511c(...);  /* FUN_0046511c */
extern word_t sw_465134(...);  /* FUN_00465134 */
extern word_t sw_465144(...);  /* FUN_00465144 */
extern word_t sw_465150(...);  /* FUN_00465150 */
extern word_t sw_4651b8(...);  /* FUN_004651b8 */
extern word_t sw_465240(...);  /* FUN_00465240 */
extern word_t sw_46527c(...);  /* FUN_0046527c */
extern word_t sw_465288(...);  /* FUN_00465288 */
extern word_t sw_4652c4(...);  /* FUN_004652c4 */
extern word_t sw_465304(...);  /* FUN_00465304 */
extern word_t sw_465314(...);  /* FUN_00465314 */
extern word_t sw_465340(...);  /* FUN_00465340 */
extern word_t sw_465380(...);  /* FUN_00465380 */
extern word_t sw_4653b0(...);  /* FUN_004653b0 */
extern word_t sw_4653ec(...);  /* FUN_004653ec */
extern word_t sw_4653fc(...);  /* FUN_004653fc */
extern word_t sw_465488(...);  /* FUN_00465488 */
extern word_t sw_4654b4(...);  /* FUN_004654b4 */
extern word_t sw_4654d0(...);  /* FUN_004654d0 */
extern word_t sw_465524(...);  /* FUN_00465524 */
extern word_t sw_465540(...);  /* FUN_00465540 */
extern word_t sw_465584(...);  /* FUN_00465584 */
extern word_t sw_4655f0(...);  /* FUN_004655f0 */
extern word_t sw_4655fc(...);  /* FUN_004655fc */
extern word_t sw_465644(...);  /* FUN_00465644 */
extern word_t sw_4656a4(...);  /* FUN_004656a4 */
extern word_t sw_4656d4(...);  /* FUN_004656d4 */
extern word_t sw_465740(...);  /* FUN_00465740 */
extern word_t sw_4657ac(...);  /* FUN_004657ac */
extern word_t sw_4657d0(...);  /* FUN_004657d0 */
extern word_t sw_46580c(...);  /* FUN_0046580c */
extern word_t sw_465830(...);  /* FUN_00465830 */
extern word_t sw_465890(...);  /* FUN_00465890 */
extern word_t sw_4658fc(...);  /* FUN_004658fc */
extern word_t sw_465908(...);  /* FUN_00465908 */
extern word_t sw_465920(...);  /* FUN_00465920 */
extern word_t sw_46592c(...);  /* FUN_0046592c */
extern word_t sw_465938(...);  /* FUN_00465938 */
extern word_t sw_46598c(...);  /* FUN_0046598c */
extern word_t sw_465998(...);  /* FUN_00465998 */
extern word_t sw_4659b0(...);  /* FUN_004659b0 */
extern word_t sw_4659bc(...);  /* FUN_004659bc */
extern word_t sw_4659c8(...);  /* FUN_004659c8 */
extern word_t sw_465ac0(...);  /* FUN_00465ac0 */
extern word_t sw_465adc(...);  /* FUN_00465adc */
extern word_t sw_465b6c(...);  /* FUN_00465b6c */
extern word_t sw_465c5c(...);  /* FUN_00465c5c */
extern word_t sw_465c68(...);  /* FUN_00465c68 */
extern word_t sw_465d08(...);  /* FUN_00465d08 */
extern word_t sw_465d70(...);  /* FUN_00465d70 */
extern word_t sw_465da4(...);  /* FUN_00465da4 */
extern word_t sw_465db0(...);  /* FUN_00465db0 */
extern word_t sw_465dbc(...);  /* FUN_00465dbc */
extern word_t sw_465df0(...);  /* FUN_00465df0 */
extern word_t sw_465e04(...);  /* FUN_00465e04 */
extern word_t sw_465e40(...);  /* FUN_00465e40 */
extern word_t sw_465e60(...);  /* FUN_00465e60 */
extern word_t sw_465e74(...);  /* FUN_00465e74 */
extern word_t sw_465eac(...);  /* FUN_00465eac */
extern word_t sw_465ec0(...);  /* FUN_00465ec0 */
extern word_t sw_465ed4(...);  /* FUN_00465ed4 */
extern word_t sw_465f14(...);  /* FUN_00465f14 */
extern word_t sw_465f48(...);  /* FUN_00465f48 */
extern word_t sw_465f5c(...);  /* FUN_00465f5c */
extern word_t sw_465f7c(...);  /* FUN_00465f7c */
extern word_t sw_465f9c(...);  /* FUN_00465f9c */
extern word_t sw_465fa8(...);  /* FUN_00465fa8 */
extern word_t sw_465fd4(...);  /* FUN_00465fd4 */
extern word_t sw_466028(...);  /* FUN_00466028 */
extern word_t sw_466048(...);  /* FUN_00466048 */
extern word_t sw_466054(...);  /* FUN_00466054 */
extern word_t sw_466068(...);  /* FUN_00466068 */
extern word_t sw_466074(...);  /* FUN_00466074 */
extern word_t sw_4660c0(...);  /* FUN_004660c0 */
extern word_t sw_4660cc(...);  /* FUN_004660cc */
extern word_t sw_46615c(...);  /* FUN_0046615c */
extern word_t sw_46617c(...);  /* FUN_0046617c */
extern word_t sw_466190(...);  /* FUN_00466190 */
extern word_t sw_4662a4(...);  /* FUN_004662a4 */
extern word_t sw_4662f4(...);  /* FUN_004662f4 */
extern word_t sw_46633c(...);  /* FUN_0046633c */
extern word_t sw_46635c(...);  /* FUN_0046635c */
extern word_t sw_4663ec(...);  /* FUN_004663ec */
extern word_t sw_466408(...);  /* FUN_00466408 */
extern word_t sw_466490(...);  /* FUN_00466490 */
extern word_t sw_4664a4(...);  /* FUN_004664a4 */
extern word_t sw_466510(...);  /* FUN_00466510 */
extern word_t sw_466528(...);  /* FUN_00466528 */
extern word_t sw_466568(...);  /* FUN_00466568 */
extern word_t sw_466600(...);  /* FUN_00466600 */
extern word_t sw_466630(...);  /* FUN_00466630 */
extern word_t sw_466648(...);  /* FUN_00466648 */
extern word_t sw_466678(...);  /* FUN_00466678 */
extern word_t sw_466684(...);  /* FUN_00466684 */
extern word_t sw_466690(...);  /* FUN_00466690 */
extern word_t sw_4666a8(...);  /* FUN_004666a8 */
extern word_t sw_4666e4(...);  /* FUN_004666e4 */
extern word_t sw_4666f8(...);  /* FUN_004666f8 */
extern word_t sw_466730(...);  /* FUN_00466730 */

/* @@BODIES@@ */

/* FUN_0042af18 @ 0x0042af18   (est. regex_parse_delim_init)
 * Ghidra: void FUN_0042af18(void)
 * Loads the five-word delimiter-selection argument (from unaff_x20) into a
 * local and passes it to the object-layout helper at 0x369efc with the two
 * image-base metadata addresses 0x685578 / 0x682b88.  Confidence: low.
 * Notes: unaff_x20 is the caller's x20; 0x369efc builds a Swift metadata record. */
void FUN_0042af18(void)
{
        word_t *arg = (word_t *)__builtin_frame_address(0); /* unaff_x20 */
        word_t sel[5];
        sel[0] = arg[0];
        sel[1] = arg[1];
        sel[2] = arg[2];
        sel[3] = arg[3];
        sel[4] = arg[4];
        sw_369efc(sel, 0x685578, 0x682b88);
}

/* FUN_0042af68 @ 0x0042af68   (est. regex_parse_throw_delim)
 * Ghidra: void FUN_0042af68(void)
 * Reads the current 16-byte scalar, formats it through the string builder
 * (0x42c958), then zeroes a 5-word result slot and re-inits the scanner.
 * Confidence: low.
 * Notes: dead-code-jumptable warning from the decompiler. */
void FUN_0042af68(void)
{
        sw128_t sc = sw_4666f8();
        FUN_0042c958(0x20, sc.lo, sc.hi, 0x67fa68, 0);
        sw_3a25d4(0x28);
        sw_4666e4(0x30);
}



