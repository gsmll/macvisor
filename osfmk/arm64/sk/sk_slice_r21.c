/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel,
 * arm64e, image base 0) — the cL4 microkernel (GL1), "cL4 (679.100.61)".
 * Ground truth: Ghidra FUN_ names + addresses. All names are estimates unless
 * header-matched. This is the SKR21 true-gap slice (0x004635a4-0x00463fd0):
 * a dense run of small runtime/Unicode thunks — Swift-string inline constants
 * (Unicode script names), register-save/copy fragments, tail-calls into the
 * shared runtime, and no-op stubs. */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

typedef uint64_t word_t;
typedef uint32_t seL4_Word;
typedef unsigned char byte;

/* cL4 returns many values as a 16-byte pair (two 64-bit words in x0/x1). */
typedef struct { unsigned long lo, hi; } cL4_w16_t;

/* ------------------------------------------------------------------ *
 * Out-of-slice helper declarations (extern; bodies reconstructed by the
 * range worker that owns them). Signatures reflect observed register use.
 * ------------------------------------------------------------------ */
extern void cL4_fwd_29fa0c(word_t, word_t, word_t, word_t);    /* FUN_0029fa0c */
extern void cL4_call_2a0cf8(void);                              /* FUN_002a0cf8 */
extern void cL4_memcpy_to_stack(word_t dst);                    /* FUN_00117cc4 (cL4 memcpy) */
extern void cL4_call_2a4ab4(word_t);                            /* FUN_002a4ab4 */
extern void cL4_case_transform(word_t, word_t, word_t, const void *, word_t); /* FUN_003722e4 */
extern void cL4_call_2534(word_t, void *);                      /* FUN_00002534 */
extern void cL4_call_2acbb8(word_t, word_t);                    /* thunk_FUN_002acbb8 */
extern void cL4_call_3a25d4(void);                              /* FUN_003a25d4 */

/* ================================================================== *
 * No-op / empty stubs. Ghidra reports a body of `return;` only — these are
 * true-gap fragments (likely tail-passed register thunks whose callers
 * reconstruct the real work, or cold-outlined dead slots). Kept faithful.
 * ================================================================== */

/* FUN_004635c8 @ 0x4635c8  (est. sk_nop) — empty body. Confidence: low */
static void sk_nop_4635c8(void) { }
/* FUN_004635f0 @ 0x4635f0  (est. sk_nop) — empty body. Confidence: low */
static void sk_nop_4635f0(void) { }
/* FUN_00463600 @ 0x463600  (est. sk_nop) — empty body. Confidence: low */
static void sk_nop_463600(void) { }
/* FUN_00463638 @ 0x463638  (est. sk_nop) — empty body. Confidence: low */
static void sk_nop_463638(void) { }
/* FUN_00463648 @ 0x463648  (est. sk_nop) — empty body. Confidence: low */
static void sk_nop_463648(void) { }
/* FUN_00463668 @ 0x463668  (est. sk_nop) — empty body. Confidence: low */
static void sk_nop_463668(void) { }
/* FUN_004636a0 @ 0x4636a0  (est. sk_nop) — empty body. Confidence: low */
static void sk_nop_4636a0(void) { }
/* FUN_004636cc @ 0x4636cc  (est. sk_nop) — empty body. Confidence: low */
static void sk_nop_4636cc(void) { }
/* FUN_004636e8 @ 0x4636e8  (est. sk_nop) — empty body. Confidence: low */
static void sk_nop_4636e8(void) { }
/* FUN_004636f8 @ 0x4636f8  (est. sk_nop) — empty body. Confidence: low */
static void sk_nop_4636f8(void) { }
/* FUN_00463728 @ 0x463728  (est. sk_nop) — empty body. Confidence: low */
static void sk_nop_463728(void) { }
/* FUN_0046373c @ 0x46373c  (est. sk_nop) — empty body. Confidence: low */
static void sk_nop_46373c(void) { }
/* FUN_00463764 @ 0x463764  (est. sk_nop) — empty body. Confidence: low */
static void sk_nop_463764(void) { }
/* FUN_00463778 @ 0x463778  (est. sk_nop) — empty body. Confidence: low */
static void sk_nop_463778(void) { }
/* FUN_0046378c @ 0x46378c  (est. sk_nop) — empty body. Confidence: low */
static void sk_nop_46378c(void) { }
/* FUN_004637a0 @ 0x4637a0  (est. sk_nop) — empty body. Confidence: low */
static void sk_nop_4637a0(void) { }
/* FUN_004637b4 @ 0x4637b4  (est. sk_nop) — empty body. Confidence: low */
static void sk_nop_4637b4(void) { }
/* FUN_004637c8 @ 0x4637c8  (est. sk_nop) — empty body. Confidence: low */
static void sk_nop_4637c8(void) { }
/* FUN_004637dc @ 0x4637dc  (est. sk_nop) — empty body. Confidence: low */
static void sk_nop_4637dc(void) { }
/* FUN_004637f0 @ 0x4637f0  (est. sk_nop) — empty body. Confidence: low */
static void sk_nop_4637f0(void) { }
/* FUN_004637fc @ 0x4637fc  (est. sk_nop) — empty body. Confidence: low */
static void sk_nop_4637fc(void) { }
/* FUN_00463824 @ 0x463824  (est. sk_nop) — empty body. Confidence: low */
static void sk_nop_463824(void) { }
/* FUN_00463830 @ 0x463830  (est. sk_nop) — empty body. Confidence: low */
static void sk_nop_463830(void) { }
/* FUN_00463858 @ 0x463858  (est. sk_nop) — empty body. Confidence: low */
static void sk_nop_463858(void) { }
/* FUN_00463884 @ 0x463884  (est. sk_nop) — empty body. Confidence: low */
static void sk_nop_463884(void) { }
/* FUN_00463890 @ 0x463890  (est. sk_nop) — empty body. Confidence: low */
static void sk_nop_463890(void) { }
/* FUN_0046389c @ 0x46389c  (est. sk_nop) — empty body. Confidence: low */
static void sk_nop_46389c(void) { }
/* FUN_004638c0 @ 0x4638c0  (est. sk_nop) — empty body. Confidence: low */
static void sk_nop_4638c0(void) { }
/* FUN_00463944 @ 0x463944  (est. sk_nop) — empty body. Confidence: low */
static void sk_nop_463944(void) { }
/* FUN_00463970 @ 0x463970  (est. sk_nop) — empty body. Confidence: low */
static void sk_nop_463970(void) { }
/* FUN_0046397c @ 0x46397c  (est. sk_nop) — empty body. Confidence: low */
static void sk_nop_46397c(void) { }
/* FUN_00463988 @ 0x463988  (est. sk_nop) — empty body. Confidence: low */
static void sk_nop_463988(void) { }
/* FUN_00463998 @ 0x463998  (est. sk_nop) — empty body. Confidence: low */
static void sk_nop_463998(void) { }
/* FUN_004639b0 @ 0x4639b0  (est. sk_nop) — empty body. Confidence: low */
static void sk_nop_4639b0(void) { }
/* FUN_004639d8 @ 0x4639d8  (est. sk_nop) — empty body. Confidence: low */
static void sk_nop_4639d8(void) { }
/* FUN_004639e4 @ 0x4639e4  (est. sk_nop) — empty body. Confidence: low */
static void sk_nop_4639e4(void) { }
/* FUN_00463a28 @ 0x463a28  (est. sk_nop) — empty body. Confidence: low */
static void sk_nop_463a28(void) { }
/* FUN_00463a38 @ 0x463a38  (est. sk_nop) — empty body. Confidence: low */
static void sk_nop_463a38(void) { }
/* FUN_00463a58 @ 0x463a58  (est. sk_nop) — empty body. Confidence: low */
static void sk_nop_463a58(void) { }
/* FUN_00463a68 @ 0x463a68  (est. sk_nop) — empty body. Confidence: low */
static void sk_nop_463a68(void) { }
/* FUN_00463a78 @ 0x463a78  (est. sk_nop) — empty body. Confidence: low */
static void sk_nop_463a78(void) { }
/* FUN_00463a88 @ 0x463a88  (est. sk_nop) — empty body. Confidence: low */
static void sk_nop_463a88(void) { }
/* FUN_00463ac8 @ 0x463ac8  (est. sk_nop) — empty body. Confidence: low */
static void sk_nop_463ac8(void) { }
/* FUN_00463bbc @ 0x463bbc  (est. sk_nop) — empty body. Confidence: low */
static void sk_nop_463bbc(void) { }
/* FUN_00463bd4 @ 0x463bd4  (est. sk_nop) — empty body. Confidence: low */
static void sk_nop_463bd4(void) { }
/* FUN_00463c0c @ 0x463c0c  (est. sk_nop) — empty body. Confidence: low */
static void sk_nop_463c0c(void) { }
/* FUN_00463cc8 @ 0x463cc8  (est. sk_nop) — empty body. Confidence: low */
static void sk_nop_463cc8(void) { }
/* FUN_00463dbc @ 0x463dbc  (est. sk_nop) — empty body. Confidence: low */
static void sk_nop_463dbc(void) { }
/* FUN_00463dc8 @ 0x463dc8  (est. sk_nop) — empty body. Confidence: low */
static void sk_nop_463dc8(void) { }
/* FUN_00463dd4 @ 0x463dd4  (est. sk_nop) — empty body. Confidence: low */
static void sk_nop_463dd4(void) { }
/* FUN_00463df8 @ 0x463df8  (est. sk_nop) — empty body. Confidence: low */
static void sk_nop_463df8(void) { }
/* FUN_00463e04 @ 0x463e04  (est. sk_nop) — empty body. Confidence: low */
static void sk_nop_463e04(void) { }
/* FUN_00463e1c @ 0x463e1c  (est. sk_nop) — empty body. Confidence: low */
static void sk_nop_463e1c(void) { }
/* FUN_00463e38 @ 0x463e38  (est. sk_nop) — empty body. Confidence: low */
static void sk_nop_463e38(void) { }
/* FUN_00463e54 @ 0x463e54  (est. sk_nop) — empty body. Confidence: low */
static void sk_nop_463e54(void) { }
/* FUN_00463e70 @ 0x463e70  (est. sk_nop) — empty body. Confidence: low */
static void sk_nop_463e70(void) { }
/* FUN_00463e8c @ 0x463e8c  (est. sk_nop) — empty body. Confidence: low */
static void sk_nop_463e8c(void) { }
/* FUN_00463ea8 @ 0x463ea8  (est. sk_nop) — empty body. Confidence: low */
static void sk_nop_463ea8(void) { }
/* FUN_00463ec4 @ 0x463ec4  (est. sk_nop) — empty body. Confidence: low */
static void sk_nop_463ec4(void) { }
/* FUN_00463ee0 @ 0x463ee0  (est. sk_nop) — empty body. Confidence: low */
static void sk_nop_463ee0(void) { }
/* FUN_00463efc @ 0x463efc  (est. sk_nop) — empty body. Confidence: low */
static void sk_nop_463efc(void) { }
/* FUN_00463f18 @ 0x463f18  (est. sk_nop) — empty body. Confidence: low */
static void sk_nop_463f18(void) { }
/* FUN_00463f34 @ 0x463f34  (est. sk_nop) — empty body. Confidence: low */
static void sk_nop_463f34(void) { }
/* FUN_00463f40 @ 0x463f40  (est. sk_nop) — empty body. Confidence: low */
static void sk_nop_463f40(void) { }
/* FUN_00463f4c @ 0x463f4c  (est. sk_nop) — empty body. Confidence: low */
static void sk_nop_463f4c(void) { }
/* FUN_00463f58 @ 0x463f58  (est. sk_nop) — empty body. Confidence: low */
static void sk_nop_463f58(void) { }
/* FUN_00463f74 @ 0x463f74  (est. sk_nop) — empty body. Confidence: low */
static void sk_nop_463f74(void) { }
/* FUN_00463f94 @ 0x463f94  (est. sk_nop) — empty body. Confidence: low */
static void sk_nop_463f94(void) { }
/* FUN_00463fa0 @ 0x463fa0  (est. sk_nop) — empty body. Confidence: low */
static void sk_nop_463fa0(void) { }
/* FUN_00463fb8 @ 0x463fb8  (est. sk_nop) — empty body. Confidence: low */
static void sk_nop_463fb8(void) { }
/* FUN_00463fd0 @ 0x463fd0  (est. sk_nop) — empty body. Confidence: low */
static void sk_nop_463fd0(void) { }

/* ================================================================== *
 * Forwarding / tail-call thunks.
 * ================================================================== */

/* FUN_004635a4 @ 0x4635a4  (est. sk_forward_4word_29fa0c)
 * Read four consecutive words of the object pointed to by the callee-saved
 * x19 and forward them in order to the shared runtime helper FUN_0029fa0c.
 * Confidence: low */
static void sk_forward_4word_29fa0c(word_t *obj)
{
    cL4_fwd_29fa0c(obj[2], obj[3], obj[0], obj[1]);
}

/* FUN_004635b8 @ 0x4635b8  (est. sk_tail_2a0cf8)
 * Tail-call the no-argument runtime routine FUN_002a0cf8.
 * Confidence: low */
static void sk_tail_2a0cf8(void)
{
    cL4_call_2a0cf8();
}

/* FUN_004639fc @ 0x4639fc  (est. sk_init_2534)
 * Call FUN_00002534 with the constant 0x6579c8 and the address of global
 * DAT_005a19a0 — a one-shot registration/init of a runtime table.
 * Confidence: low */
static void sk_init_2534(void)
{
    /* DAT_005a19a0: global descriptor table; 0x6579c8: selector constant. */
    cL4_call_2534(0x6579c8, (void *)0x5a19a0);
}

/* FUN_00463af8 @ 0x463af8  (est. sk_tail_2acbb8_10)
 * Tail-call the runtime routine thunk_FUN_002acbb8 with (10, tag 0xe1...0).
 * Confidence: low */
static void sk_tail_2acbb8_10(void)
{
    cL4_call_2acbb8(10, 0xe100000000000000UL);
}

/* FUN_00463f64 @ 0x463f64  (est. sk_tail_3a25d4)
 * Tail-call the no-argument runtime routine FUN_003a25d4.
 * Confidence: low */
static void sk_tail_3a25d4(void)
{
    cL4_call_3a25d4();
}

/* ================================================================== *
 * 16-byte inline Swift-string constants (Unicode script names).
 * Each returns {lo, hi} where lo = first 8 string bytes, hi = remaining
 * bytes + the Swift small-string tag in the high byte.
 * ================================================================== */

/* FUN_004635e0 @ 0x4635e0  (est. sk_string_233f28)
 * Returns the small string {0x233f28, tag 0xe3...}: an 8-byte object
 * pointer at 0x233f28 packed with a 0xe3 tag. Confidence: low */
static cL4_w16_t sk_string_233f28(void)
{
    cL4_w16_t r; r.lo = 0x233f28; r.hi = 0xe300000000000000UL; return r;
}

/* FUN_00463864 @ 0x463864  (est. sk_load16_10)
 * Load and return the 16-byte value at the object + 0x10 (x19).
 * Confidence: low */
static cL4_w16_t sk_load16_10(word_t *obj)
{
    cL4_w16_t r; r.lo = obj[2]; r.hi = obj[3]; return r;
}

/* FUN_00463878 @ 0x463878  (est. sk_string_7d)
 * Returns the 1-char inline string "}" (0x7d) with tag 0xe1.
 * Confidence: low */
static cL4_w16_t sk_string_7d(void)
{
    cL4_w16_t r; r.lo = 0x7d; r.hi = 0xe100000000000000UL; return r;
}

/* FUN_00463aa0 @ 0x463aa0  (est. sk_load16_40)
 * Load and return the 16-byte value at the object + 0x40 (x19).
 * Confidence: low */
static cL4_w16_t sk_load16_40(word_t *obj)
{
    cL4_w16_t r; r.lo = obj[8]; r.hi = obj[9]; return r;
}

/* FUN_00463ad4 @ 0x463ad4  (est. sk_script_name_pahawh_hmong)
 * Returns the inline Swift string "Pahawh_Hmong" (Unicode script name).
 * Confidence: high (ASCII decode) */
static cL4_w16_t sk_script_name_pahawh_hmong(void)
{
    cL4_w16_t r; r.lo = 0x485f687761686150UL; r.hi = 0xec000000676e6f6dUL; return r; /* "Pahawh_Hmong" */
}

/* FUN_00463b08 @ 0x463b08  (est. sk_script_name_warang_citi)
 * Returns the inline Swift string "Warang_Citi" (Unicode script name).
 * Confidence: high (ASCII decode) */
static cL4_w16_t sk_script_name_warang_citi(void)
{
    cL4_w16_t r; r.lo = 0x435f676e61726157UL; r.hi = 0xeb00000000697469UL; return r; /* "Warang_Citi" */
}

/* FUN_00463b2c @ 0x463b2c  (est. sk_script_name_medefaidrin)
 * Returns the inline Swift string "MedefaidrinKakui" (Unicode script name,
 * alt. Kakui). Confidence: high (ASCII decode) */
static cL4_w16_t sk_script_name_medefaidrin(void)
{
    cL4_w16_t r; r.lo = 0x694b5f65646e654dUL; r.hi = 0xed000069756b616bUL; return r; /* "MedefaidrinKakui" */
}

/* FUN_00463b50 @ 0x463b50  (est. sk_script_name_psalter_pahlavi)
 * Returns the inline Swift string "Psalter_Pahlavi" (Unicode script name).
 * Confidence: high (ASCII decode) */
static cL4_w16_t sk_script_name_psalter_pahlavi(void)
{
    cL4_w16_t r; r.lo = 0x5f7265746c617350UL; r.hi = 0xef6976616c686150UL; return r; /* "Psalter_Pahlavi" */
}

/* FUN_00463b98 @ 0x463b98  (est. sk_script_name_old_hungarian)
 * Returns the inline Swift string "Old_Hungarian" (Unicode script name).
 * Confidence: high (ASCII decode) */
static cL4_w16_t sk_script_name_old_hungarian(void)
{
    cL4_w16_t r; r.lo = 0x676e75485f646c4fUL; r.hi = 0xed00006e61697261UL; return r; /* "Old_Hungarian" */
}

/* FUN_00463bc8 @ 0x463bc8  (est. sk_string_3d)
 * Returns the 1-char inline string "=" (0x3d) with tag 0xe1.
 * Confidence: low */
static cL4_w16_t sk_string_3d(void)
{
    cL4_w16_t r; r.lo = 0x3d; r.hi = 0xe100000000000000UL; return r;
}

/* FUN_00463c18 @ 0x463c18  (est. sk_script_name_sora_sompeng)
 * Returns the inline Swift string "Sora_Sompeng" (Unicode script name).
 * Confidence: high (ASCII decode) */
static cL4_w16_t sk_script_name_sora_sompeng(void)
{
    cL4_w16_t r; r.lo = 0x6d6f535f61726f53UL; r.hi = 0xec000000676e6570UL; return r; /* "Sora_Sompeng" */
}

/* FUN_00463c38 @ 0x463c38  (est. sk_script_name_chorasmian)
 * Returns the inline Swift string "Chorasmian" (Unicode script name).
 * Confidence: high (ASCII decode) */
static cL4_w16_t sk_script_name_chorasmian(void)
{
    cL4_w16_t r; r.lo = 0x696d7361726f6843UL; r.hi = 0xea00000000006e61UL; return r; /* "Chorasmian" */
}

/* FUN_00463c58 @ 0x463c58  (est. sk_script_name_manichaean)
 * Returns the inline Swift string "Manichaean" (Unicode script name).
 * Confidence: high (ASCII decode) */
static cL4_w16_t sk_script_name_manichaean(void)
{
    cL4_w16_t r; r.lo = 0x65616863696e614dUL; r.hi = 0xea00000000006e61UL; return r; /* "Manichaean" */
}

/* FUN_00463c78 @ 0x463c78  (est. sk_script_name_phoenician)
 * Returns the inline Swift string "Phoenician" (Unicode script name).
 * Confidence: high (ASCII decode) */
static cL4_w16_t sk_script_name_phoenician(void)
{
    cL4_w16_t r; r.lo = 0x6963696e656f6850UL; r.hi = 0xea00000000006e61UL; return r; /* "Phoenician" */
}

/* FUN_00463c98 @ 0x463c98  (est. sk_script_name_devanagari)
 * Returns the inline Swift string "Devanagari" (Unicode script name).
 * Confidence: high (ASCII decode) */
static cL4_w16_t sk_script_name_devanagari(void)
{
    cL4_w16_t r; r.lo = 0x6167616e61766544UL; r.hi = 0xea00000000006972UL; return r; /* "Devanagari" */
}

/* FUN_00463cfc @ 0x463cfc  (est. sk_script_name_cypriot_minoan)
 * Returns the inline Swift string "Cypriot_Minoan" (Unicode script name).
 * Confidence: high (ASCII decode) */
static cL4_w16_t sk_script_name_cypriot_minoan(void)
{
    cL4_w16_t r; r.lo = 0x694d5f6f72707943UL; r.hi = 0xec0000006e616f6eUL; return r; /* "Cypriot_Minoan" */
}

/* FUN_00463d1c @ 0x463d1c  (est. sk_script_name_pau_cin_hau)
 * Returns the inline Swift string "Pau_Cin_Hau" (Unicode script name).
 * Confidence: high (ASCII decode) */
static cL4_w16_t sk_script_name_pau_cin_hau(void)
{
    cL4_w16_t r; r.lo = 0x5f6e69435f756150UL; r.hi = 0xeb00000000756148UL; return r; /* "Pau_Cin_Hau" */
}

/* FUN_00463d3c @ 0x463d3c  (est. sk_script_name_syloti_nagri)
 * Returns the inline Swift string "Syloti_Nagri" (Unicode script name).
 * Confidence: high (ASCII decode) */
static cL4_w16_t sk_script_name_syloti_nagri(void)
{
    cL4_w16_t r; r.lo = 0x4e5f69746f6c7953UL; r.hi = 0xec00000069726761UL; return r; /* "Syloti_Nagri" */
}

/* FUN_00463d5c @ 0x463d5c  (est. sk_script_name_meeitei_mayek)
 * Returns the inline Swift string "Meeitei_Mayek" (Unicode script name).
 * Confidence: high (ASCII decode) */
static cL4_w16_t sk_script_name_meeitei_mayek(void)
{
    cL4_w16_t r; r.lo = 0x4d5f69657465654dUL; r.hi = 0xec0000006b657961UL; return r; /* "Meeitei_Mayek" */
}

/* FUN_00463d7c @ 0x463d7c  (est. sk_script_name_new_tai_lue)
 * Returns the inline Swift string "New_Tai_Lue" (Unicode script name).
 * Confidence: high (ASCII decode) */
static cL4_w16_t sk_script_name_new_tai_lue(void)
{
    cL4_w16_t r; r.lo = 0x5f6961545f77654eUL; r.hi = 0xeb0000000065754cUL; return r; /* "New_Tai_Lue" */
}

/* FUN_00463d9c @ 0x463d9c  (est. sk_script_name_dives_akuru)
 * Returns the inline Swift string "Dives_Akuru" (Unicode script name).
 * Confidence: high (ASCII decode) */
static cL4_w16_t sk_script_name_dives_akuru(void)
{
    cL4_w16_t r; r.lo = 0x6b415f7365766944UL; r.hi = 0xeb00000000757275UL; return r; /* "Dives_Akuru" */
}

/* FUN_00463de0 @ 0x463de0  (est. sk_string_2d)
 * Returns the 1-char inline string "-" (0x2d) with tag 0xe1.
 * Confidence: low */
static cL4_w16_t sk_string_2d(void)
{
    cL4_w16_t r; r.lo = 0x2d; r.hi = 0xe100000000000000UL; return r;
}

/* FUN_00463dec @ 0x463dec  (est. sk_string_stack_a0)
 * Returns a 16-byte pair: lo = the caller's stack pointer (&stack+0xa0),
 * hi = param_1. Confidence: low */
static cL4_w16_t sk_string_stack_a0(word_t param_1, void *stack_a0)
{
    cL4_w16_t r; r.lo = (unsigned long)stack_a0; r.hi = param_1; return r;
}

/* FUN_00463e10 @ 0x463e10  (est. sk_string_3e)
 * Returns the 1-char inline string ">" (0x3e) with tag 0xe1.
 * Confidence: low */
static cL4_w16_t sk_string_3e(void)
{
    cL4_w16_t r; r.lo = 0x3e; r.hi = 0xe100000000000000UL; return r;
}

/* FUN_00463f80 @ 0x463f80  (est. sk_string_zero)
 * Returns the zero 16-byte value {0,0}. Confidence: low */
static cL4_w16_t sk_string_zero(void)
{
    cL4_w16_t r; r.lo = 0; r.hi = 0; return r;
}

/* FUN_00463fac @ 0x463fac  (est. sk_string_7b)
 * Returns the 1-char inline string "{" (0x7b) with tag 0xe1.
 * Confidence: low */
static cL4_w16_t sk_string_7b(void)
{
    cL4_w16_t r; r.lo = 0x7b; r.hi = 0xe100000000000000UL; return r;
}

/* ================================================================== *
 * Constant / expression fragments.
 * ================================================================== */

/* FUN_004635d4 @ 0x4635d4  (est. sk_const_1b)
 * Returns the constant 0xd00000000000001b (a tagged error/selector value).
 * Confidence: low */
static word_t sk_const_1b(void)
{
    return 0xd00000000000001bUL;
}

/* FUN_00463658 @ 0x463658  (est. sk_elem_offset_50)
 * Returns base + idx*0x50 + 0x20 — the byte offset of element `idx` in a
 * stride-0x50 (10-word) element array plus an 0x20 field offset.
 * Confidence: low */
static word_t sk_elem_offset_50(word_t base, word_t idx)
{
    return base + idx * 0x50 + 0x20;
}

/* FUN_00463684 @ 0x463684  (est. sk_string_group_na)
 * Returns the ASCII fragment "group na" (0x616e2070756f7267) — the head of
 * "group name", a Swift runtime error/description string.
 * Confidence: medium (ASCII decode) */
static word_t sk_string_group_na(void)
{
    return 0x616e2070756f7267UL; /* "group na" */
}

/* FUN_004636b0 @ 0x4636b0  (est. sk_string_number_placeholder)
 * Returns the ASCII fragment "<#number" (0x7265626d756e233c) — a Swift
 * mirror placeholder prefix. Confidence: medium (ASCII decode) */
static word_t sk_string_number_placeholder(void)
{
    return 0x7265626d756e233cUL; /* "<#number" */
}

/* FUN_00463708 @ 0x463708  (est. sk_load_word_10)
 * Returns the word at (*obj + 0x10): dereference the pointer stored at
 * obj[0], then load the word at +0x10.
 * Confidence: low */
static word_t sk_load_word_10(word_t **obj)
{
    return (word_t)(*(uint64_t *)((char *)*obj + 0x10));
}

/* FUN_00463844 @ 0x463844  (est. sk_store_word_and_offset)
 * Stores word at obj+0x10 and returns base + idx*0x50 + 0x20 (same stride
 * geometry as FUN_00463658). Confidence: low */
static word_t sk_store_word_and_offset(word_t *obj, word_t val, word_t base, word_t idx)
{
    obj[2] = val;
    return base + idx * 0x50 + 0x20;
}

/* FUN_004639c8 @ 0x4639c8  (est. sk_const_15)
 * Returns the constant 0xd000000000000015 (a tagged error/selector value).
 * Confidence: low */
static word_t sk_const_15(void)
{
    return 0xd000000000000015UL;
}

/* FUN_00463ab8 @ 0x463ab8  (est. sk_inc_global_field)
 * Increments the word at (*obj + 0x10): reads the pointer stored at obj[0],
 * then stores x25+1 into the field at +0x10 (a reference/use counter).
 * Confidence: low */
static void sk_inc_global_field(word_t **obj, word_t delta)
{
    *(uint64_t *)((char *)*obj + 0x10) = delta + 1;
}

/* ================================================================== *
 * Register-save / copy fragments.
 * ================================================================== */

/* FUN_0046361c @ 0x46361c  (est. sk_frame_push_regs)
 * Record four callee-saved words (x22..x25) into a stack frame: bumps the
 * count word at frame+0x10 by one, then stores the four values at the
 * frame base + count*0x20. A register spill into an argument-recording area.
 * Confidence: low */
static void sk_frame_push_regs(word_t *frame, word_t count, word_t a, word_t b, word_t c, word_t d)
{
    long base;
    frame[2] = count + 1;
    base = (long)frame + count * 0x20;
    *(word_t *)(base + 0x20) = a;
    *(word_t *)(base + 0x28) = b;
    *(word_t *)(base + 0x30) = c;
    *(word_t *)(base + 0x38) = d;
}

/* FUN_00463718 @ 0x463718  (est. sk_memcpy_3f0_to_stack)
 * Copy 0x3f0 bytes onto the caller's stack frame via the cL4 memcpy helper
 * (FUN_00117cc4) with the destination at &stack+0x3f0.
 * Confidence: low */
static void sk_memcpy_3f0_to_stack(void *dst)
{
    cL4_memcpy_to_stack((word_t)dst);
}

/* FUN_00463750 @ 0x463750  (est. sk_copy_words_18_20)
 * Copy the two words at src+0x18 and src+0x20 into dst+0x18 and dst+0x20.
 * Confidence: low */
static void sk_copy_words_18_20(word_t *dst, word_t *src)
{
    dst[3] = src[3];
    dst[4] = src[4];
}

/* FUN_00463810 @ 0x463810  (est. sk_store8_words)
 * Store eight words (from x20..x27) into the word array at *dst.
 * Confidence: low */
static void sk_store8_words(word_t *dst, word_t w0, word_t w1, word_t w2, word_t w3,
                            word_t w4, word_t w5, word_t w6, word_t w7)
{
    dst[0] = w0; dst[1] = w1; dst[2] = w2; dst[3] = w3;
    dst[4] = w4; dst[5] = w5; dst[6] = w6; dst[7] = w7;
}

/* FUN_004638a8 @ 0x4638a8  (est. sk_setup_stack_1d)
 * Push a 16-byte {0, tag 0xe0...0} value onto the stack, then call
 * FUN_002a4ab4(0x1d). Confidence: low */
static void sk_setup_stack_1d(void)
{
    volatile word_t slot[2];
    slot[0] = 0;
    slot[1] = 0xe000000000000000UL;
    cL4_call_2a4ab4(0x1d);
}

/* FUN_004638d8 @ 0x4638d8  (est. sk_store19_words)
 * Store nineteen words into the word array at *dst: eight from registers
 * (x21..x28), six from stack slots (+0x68..+0x90), two pairs read from the
 * caller frame (x29-0x88/-0x80 and x29-0x78/-0x70), one from x29-0x68, and
 * a final byte from x29-0x5c. A register/arg block snapshot.
 * Confidence: low */
static void sk_store19_words(word_t *dst, word_t r0, word_t r1, word_t r2, word_t r3,
                             word_t r4, word_t r5, word_t r6, word_t r7,
                             word_t s0, word_t s1, word_t s2, word_t s3, word_t s4, word_t s5,
                             word_t f0, word_t f1, word_t f2, word_t f3, word_t f4, byte last)
{
    dst[0] = r0; dst[1] = r1; dst[2] = r2; dst[3] = r3; dst[4] = r4;
    dst[5] = r5; dst[6] = r6; dst[7] = r7;
    dst[8] = s0; dst[9] = s1; dst[10] = s2; dst[11] = s3; dst[12] = s4; dst[13] = s5;
    dst[14] = f0; dst[15] = f1;
    dst[16] = f2; dst[17] = f3;
    dst[18] = f4;
    ((byte *)dst)[0x13] = last;
}

/* FUN_00463a10 @ 0x463a10  (est. sk_copy_field_pair)
 * Copy the word at src+8 into dst+8, and the word at src+0x10 into the
 * caller's x20+0x10. Confidence: low */
static void sk_copy_field_pair(word_t *dst, word_t *src, word_t *caller)
{
    dst[1] = src[1];
    caller[2] = src[2];
}

/* FUN_00463a48 @ 0x463a48  (est. sk_copy_byte_18)
 * Copy the byte at src+0x18 into dst+0x18. Confidence: low */
static void sk_copy_byte_18(byte *dst, byte *src)
{
    dst[0x18] = src[0x18];
}

/* FUN_00463cb8 @ 0x463cb8  (est. sk_memcpy_b8_to_stack)
 * Copy 0xb8 bytes onto the caller's stack frame via the cL4 memcpy helper
 * (FUN_00117cc4) with the destination at &stack-0xb8 (x29 base).
 * Confidence: low */
static void sk_memcpy_b8_to_stack(void *dst)
{
    cL4_memcpy_to_stack((word_t)dst);
}

/* ================================================================== *
 * Case-transform dispatch (Swift string lower/upper).
 * ================================================================== */

/* FUN_00463924 @ 0x463924  (est. sk_case_transform_lower_upper)
 * Dispatch a lower/upper-case transformation of `s` through the runtime
 * FUN_003722e4 with the literal option string "lower_upper" (at 0x5e1f90).
 * Confidence: low */
static void sk_case_transform_lower_upper(word_t s)
{
    /* 0x5e1f90: "lower_upper" option string literal. */
    cL4_case_transform(0, s, s, (const void *)0x5e1f90, 0);
}
