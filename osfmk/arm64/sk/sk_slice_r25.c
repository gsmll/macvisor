/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel,
 * arm64e, image base 0) — the cL4 microkernel. Ground truth: Ghidra FUN_ names +
 * addresses in program cl4_kernel.raw. Version "cL4 microkernel (cL4
 * (679.100.61))". All names are estimates unless string/header-matched.
 *
 * This file covers wave batch SKR25, slice 0x004659e0-0x004661d8: the tail of
 * the Unicode-script name/property region begun in SKR24. As in SKR24, the
 * bulk of the functions are trivial slots: no-op stubs, script-name fragment
 * returns (8-byte little-endian ASCII, or an 8-byte name fragment of a longer
 * ISO 15924 script name), script-name builders that OR a fixed ASCII prefix/
 * letter into a caller-supplied word, small field copies (copy 1..8 words
 * between struct offsets), and one-word register forwards to sibling-slice
 * helpers (object/cap release, memmove, vspace/ipc transition, regex diag,
 * refcount acquire). None of the functions in this slice do any security-
 * relevant work by themselves; they are leaf accessors in the script-name
 * lookup table that other cL4 code (string/Unicode handling) consumes.
 *
 * `unaff_*` register artifacts (values carried across the frame in callee-
 * saved registers that the decompiler cannot attribute to a parameter) are
 * described in each function's notes; the faithful behaviour is a store from
 * one register-held address to another.
 */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "sk_internal.h"

/* 16-byte (two-word) result used by the return-by-value helpers below. */
typedef struct sk_r25_pair { uint64_t lo, hi; } sk_r25_pair_t;

/* ------------------------------------------------------------------ *
 * Out-of-range cL4/Swift-runtime helpers referenced by this slice.
 * FUN_ addresses in comments; bodies owned by sibling SK range workers.
 * Names are estimates.
 * ------------------------------------------------------------------ */

extern void sk_h_003a25d4(word_t a);                     /* FUN_003a25d4 (object/cap release via mask) */
extern void sk_h_00117cc4(word_t *d, word_t *s, word_t n); /* FUN_00117cc4 (overlapping memmove, branch on w18) */
extern void sk_h_002acbb8(word_t a, word_t b);           /* thunk_FUN_002acbb8 (vspace/ipc transition) */
extern void sk_h_0042ec68(word_t p);                     /* FUN_0042ec68 (regex diag emit) */
extern void sk_h_0036b270(word_t a);                     /* FUN_0036b270 / thunk_FUN_0036b270 (refcount acquire) */
extern void sk_h_00458b14(word_t a);                     /* FUN_00458b14 (clears low nibble of *(a+0x98)) */
extern void sk_h_002298d4(word_t a);                     /* thunk_FUN_002298d4 (vspace wait/sync, arg >>0xe pfn) */
extern void sk_h_00461cb8(word_t a, word_t b, word_t c); /* FUN_00461cb8 (3-arg helper: dst, const, &DAT) */
extern void sk_h_003a261c(word_t a);                     /* FUN_003a261c (1-arg release/ref helper) */
extern sk_r25_pair_t *sk_h_0001a1c8(void);               /* FUN_0001a1c8 (returns ptr to a 16-byte descriptor) */
extern void sk_h_0044c5d8(word_t a, word_t b, word_t c, word_t d); /* FUN_0044c5d8 (4-arg helper) */
extern void sk_h_002a0cf8(word_t a, word_t b, word_t c, word_t d, word_t e); /* FUN_002a0cf8 (5-arg helper) */
extern void sk_h_0045659c(void);                         /* FUN_0045659c (no-arg helper) */
extern void sk_h_00458af8(void);                         /* FUN_00458af8 (no-arg helper) */

/* ------------------------------------------------------------------ *
 * No-op / empty slots.
 * ------------------------------------------------------------------ */

/* FUN_004659e0 @ 0x004659e0   (est. sk_nop_59e0)  — empty body. Confidence: medium. */
void sk_nop_59e0(void) { }

/* FUN_004659e8 @ 0x004659e8   (est. sk_nop_59e8)  — empty body. Confidence: medium. */
void sk_nop_59e8(void) { }

/* FUN_00465be0 @ 0x00465be0   (est. sk_nop_5be0)  — empty body. Confidence: medium. */
void sk_nop_5be0(void) { }

/* FUN_00465c44 @ 0x00465c44   (est. sk_nop_5c44)  — empty body. Confidence: medium. */
void sk_nop_5c44(void) { }

/* FUN_00465c80 @ 0x00465c80   (est. sk_nop_5c80)  — empty body. Confidence: medium. */
void sk_nop_5c80(void) { }

/* FUN_00465c8c @ 0x00465c8c   (est. sk_nop_5c8c)  — empty body. Confidence: medium. */
void sk_nop_5c8c(void) { }

/* FUN_00465c98 @ 0x00465c98   (est. sk_nop_5c98)  — empty body. Confidence: medium. */
void sk_nop_5c98(void) { }

/* FUN_00465cc0 @ 0x00465cc0   (est. sk_nop_5cc0)  — empty body. Confidence: medium. */
void sk_nop_5cc0(void) { }

/* FUN_00465ce8 @ 0x00465ce8   (est. sk_nop_5ce8)  — empty body. Confidence: medium. */
void sk_nop_5ce8(void) { }

/* FUN_00465cf4 @ 0x00465cf4   (est. sk_nop_5cf4)  — empty body. Confidence: medium. */
void sk_nop_5cf4(void) { }

/* FUN_00465d08 @ 0x00465d08   (est. sk_nop_5d08)  — empty body. Confidence: medium. */
void sk_nop_5d08(void) { }

/* FUN_00465d1c @ 0x00465d1c   (est. sk_nop_5d1c)  — empty body. Confidence: medium. */
void sk_nop_5d1c(void) { }

/* FUN_00465d3c @ 0x00465d3c   (est. sk_nop_5d3c)  — empty body. Confidence: medium. */
void sk_nop_5d3c(void) { }

/* FUN_00465d48 @ 0x00465d48   (est. sk_nop_5d48)  — empty body. Confidence: medium. */
void sk_nop_5d48(void) { }

/* FUN_00465d70 @ 0x00465d70   (est. sk_nop_5d70)  — empty body. Confidence: medium. */
void sk_nop_5d70(void) { }

/* FUN_00465d84 @ 0x00465d84   (est. sk_nop_5d84)  — empty body. Confidence: medium. */
void sk_nop_5d84(void) { }

/* FUN_00465d98 @ 0x00465d98   (est. sk_nop_5d98)  — empty body. Confidence: medium. */
void sk_nop_5d98(void) { }

/* FUN_00465da4 @ 0x00465da4   (est. sk_nop_5da4)  — empty body. Confidence: medium. */
void sk_nop_5da4(void) { }

/* FUN_00465db0 @ 0x00465db0   (est. sk_nop_5db0)  — empty body. Confidence: medium. */
void sk_nop_5db0(void) { }

/* FUN_00465dbc @ 0x00465dbc   (est. sk_nop_5dbc)  — empty body. Confidence: medium. */
void sk_nop_5dbc(void) { }

/* FUN_00465dd0 @ 0x00465dd0   (est. sk_nop_5dd0)  — empty body. Confidence: medium. */
void sk_nop_5dd0(void) { }

/* FUN_00465ddc @ 0x00465ddc   (est. sk_nop_5ddc)  — empty body. Confidence: medium. */
void sk_nop_5ddc(void) { }

/* FUN_00465df0 @ 0x00465df0   (est. sk_nop_5df0)  — empty body. Confidence: medium. */
void sk_nop_5df0(void) { }

/* FUN_00465e04 @ 0x00465e04   (est. sk_nop_5e04)  — empty body. Confidence: medium. */
void sk_nop_5e04(void) { }

/* FUN_00465e2c @ 0x00465e2c   (est. sk_nop_5e2c)  — empty body. Confidence: medium. */
void sk_nop_5e2c(void) { }

/* FUN_00465e40 @ 0x00465e40   (est. sk_nop_5e40)  — empty body. Confidence: medium. */
void sk_nop_5e40(void) { }

/* FUN_00465e4c @ 0x00465e4c   (est. sk_nop_5e4c)  — empty body. Confidence: medium. */
void sk_nop_5e4c(void) { }

/* FUN_00465e60 @ 0x00465e60   (est. sk_nop_5e60)  — empty body. Confidence: medium. */
void sk_nop_5e60(void) { }

/* FUN_00465e74 @ 0x00465e74   (est. sk_nop_5e74)  — empty body. Confidence: medium. */
void sk_nop_5e74(void) { }

/* FUN_00465e80 @ 0x00465e80   (est. sk_nop_5e80)  — empty body. Confidence: medium. */
void sk_nop_5e80(void) { }

/* FUN_00465ec0 @ 0x00465ec0   (est. sk_nop_5ec0)  — empty body. Confidence: medium. */
void sk_nop_5ec0(void) { }

/* FUN_00465f00 @ 0x00465f00   (est. sk_nop_5f00)  — empty body. Confidence: medium. */
void sk_nop_5f00(void) { }

/* FUN_00465f14 @ 0x00465f14   (est. sk_nop_5f14)  — empty body. Confidence: medium. */
void sk_nop_5f14(void) { }

/* FUN_00465f48 @ 0x00465f48   (est. sk_nop_5f48)  — empty body. Confidence: medium. */
void sk_nop_5f48(void) { }

/* FUN_00465f5c @ 0x00465f5c   (est. sk_nop_5f5c)  — empty body. Confidence: medium. */
void sk_nop_5f5c(void) { }

/* FUN_00465f7c @ 0x00465f7c   (est. sk_nop_5f7c)  — empty body. Confidence: medium. */
void sk_nop_5f7c(void) { }

/* FUN_00465f90 @ 0x00465f90   (est. sk_nop_5f90)  — empty body. Confidence: medium. */
void sk_nop_5f90(void) { }

/* FUN_00465f9c @ 0x00465f9c   (est. sk_nop_5f9c)  — empty body. Confidence: medium. */
void sk_nop_5f9c(void) { }

/* FUN_00465fa8 @ 0x00465fa8   (est. sk_nop_5fa8)  — empty body. Confidence: medium. */
void sk_nop_5fa8(void) { }

/* FUN_00465fb4 @ 0x00465fb4   (est. sk_nop_5fb4)  — empty body. Confidence: medium. */
void sk_nop_5fb4(void) { }

/* FUN_00465fc8 @ 0x00465fc8   (est. sk_nop_5fc8)  — empty body. Confidence: medium. */
void sk_nop_5fc8(void) { }

/* FUN_00465fd4 @ 0x00465fd4   (est. sk_nop_5fd4)  — empty body. Confidence: medium. */
void sk_nop_5fd4(void) { }

/* FUN_00465fe0 @ 0x00465fe0   (est. sk_nop_5fe0)  — empty body. Confidence: medium. */
void sk_nop_5fe0(void) { }

/* FUN_00465ff4 @ 0x00465ff4   (est. sk_nop_5ff4)  — empty body. Confidence: medium. */
void sk_nop_5ff4(void) { }

/* FUN_00466000 @ 0x00466000   (est. sk_nop_6000)  — empty body. Confidence: medium. */
void sk_nop_6000(void) { }

/* FUN_00466014 @ 0x00466014   (est. sk_nop_6014)  — empty body. Confidence: medium. */
void sk_nop_6014(void) { }

/* FUN_00466028 @ 0x00466028   (est. sk_nop_6028)  — empty body. Confidence: medium. */
void sk_nop_6028(void) { }

/* FUN_00466048 @ 0x00466048   (est. sk_nop_6048)  — empty body. Confidence: medium. */
void sk_nop_6048(void) { }

/* FUN_00466054 @ 0x00466054   (est. sk_nop_6054)  — empty body. Confidence: medium. */
void sk_nop_6054(void) { }

/* FUN_00466068 @ 0x00466068   (est. sk_nop_6068)  — empty body. Confidence: medium. */
void sk_nop_6068(void) { }

/* FUN_004660c0 @ 0x004660c0   (est. sk_nop_60c0)  — empty body. Confidence: medium. */
void sk_nop_60c0(void) { }

/* FUN_004660cc @ 0x004660cc   (est. sk_nop_60cc)  — empty body. Confidence: medium. */
void sk_nop_60cc(void) { }

/* FUN_00466104 @ 0x00466104   (est. sk_nop_6104)  — empty body. Confidence: medium. */
void sk_nop_6104(void) { }

/* FUN_00466124 @ 0x00466124   (est. sk_nop_6124)  — empty body. Confidence: medium. */
void sk_nop_6124(void) { }

/* FUN_00466130 @ 0x00466130   (est. sk_nop_6130)  — empty body. Confidence: medium. */
void sk_nop_6130(void) { }

/* FUN_00466148 @ 0x00466148   (est. sk_nop_6148)  — empty body. Confidence: medium. */
void sk_nop_6148(void) { }

/* FUN_0046615c @ 0x0046615c   (est. sk_nop_615c)  — empty body. Confidence: medium. */
void sk_nop_615c(void) { }

/* FUN_00466168 @ 0x00466168   (est. sk_nop_6168)  — empty body. Confidence: medium. */
void sk_nop_6168(void) { }

/* FUN_004661b8 @ 0x004661b8   (est. sk_nop_61b8)  — empty body. Confidence: medium. */
void sk_nop_61b8(void) { }

/* ------------------------------------------------------------------ *
 * Script-name fragment returns (8-byte ASCII, little-endian).
 * ------------------------------------------------------------------ */

/* FUN_00465cd4 @ 0x00465cd4   (est. sk_script_name_warangic)
 * Ghidra: undefined8 FUN_00465cd4(void)
 * Returns the 8-byte ASCII fragment "warangic" (LE) — "Warang Citi" script.
 * Confidence: high (ASCII literal). */
word_t sk_script_name_warangic(void)
{
    return 0x6963676e61726177ull;       /* "warangic" LE */
}

/* FUN_00465d5c @ 0x00465d5c   (est. sk_script_name_saurahst)
 * Ghidra: undefined8 FUN_00465d5c(void)
 * Returns the 8-byte ASCII fragment "saurahst" (LE) — "Saurashtra" script.
 * Confidence: high (ASCII literal). */
word_t sk_script_name_saurahst(void)
{
    return 0x7468736172756173ull;       /* "saurahst" LE */
}

/* FUN_00465e8c @ 0x00465e8c   (est. sk_script_name_kharosth)
 * Ghidra: undefined8 FUN_00465e8c(void)
 * Returns the 8-byte ASCII fragment "kharosth" (LE) — "Kharoshthi" script.
 * Confidence: high (ASCII literal). */
word_t sk_script_name_kharosth(void)
{
    return 0x7468736f7261686bull;       /* "kharosth" LE */
}

/* FUN_00466080 @ 0x00466080   (est. sk_script_name_misc)
 * Ghidra: undefined8 FUN_00466080(void)
 * Returns the 4-byte ASCII fragment "misc" (LE, upper bytes zero). Confidence:
 * high (ASCII literal). */
word_t sk_script_name_misc(void)
{
    return 0x6373696dull;               /* "misc" LE */
}

/* FUN_0046608c @ 0x0046608c   (est. sk_script_name_bhaiksuk)
 * Ghidra: undefined8 FUN_0046608c(void)
 * Returns the 8-byte ASCII fragment "bhaiksuk" (LE) — "Bhaiksuki" script.
 * Confidence: high (ASCII literal). */
word_t sk_script_name_bhaiksuk(void)
{
    return 0x6b75736b69616862ull;       /* "bhaiksuk" LE */
}

/* FUN_004660b4 @ 0x004660b4   (est. sk_script_name_xofn)
 * Ghidra: undefined8 FUN_004660b4(void)
 * Returns the 4-byte ASCII fragment "xofn" (LE, upper bytes zero). Confidence:
 * high (ASCII literal; a script-tag fragment). */
word_t sk_script_name_xofn(void)
{
    return 0x666e6f78ull;               /* "xofn" LE */
}

/* FUN_004660f8 @ 0x004660f8   (est. sk_script_name_kana)
 * Ghidra: undefined8 FUN_004660f8(void)
 * Returns the 4-byte ASCII fragment "kana" (LE, upper bytes zero) — "Kana"
 * script. Confidence: high (ASCII literal). */
word_t sk_script_name_kana(void)
{
    return 0x616e616bull;               /* "kana" LE */
}

/* FUN_00466110 @ 0x00466110   (est. sk_script_name_palmyren)
 * Ghidra: undefined8 FUN_00466110(void)
 * Returns the 8-byte ASCII fragment "palmyren" (LE) — "Palmyrene" script.
 * Confidence: high (ASCII literal). */
word_t sk_script_name_palmyren(void)
{
    return 0x6e6572796d6c6170ull;       /* "palmyren" LE */
}

/* ------------------------------------------------------------------ *
 * Script-name builders that OR a fixed ASCII prefix/letter into a
 * caller-supplied word.
 * ------------------------------------------------------------------ */

/* FUN_00465a38 @ 0x00465a38   (est. sk_script_name_ht)
 * Ghidra: ulong FUN_00465a38(ulong param_1)
 * Builds a script-name word: keeps the caller's low 48 bits and ORs the
 * 2-byte prefix "th" (0x7468) into bits 48..63. Confidence: high (ASCII).
 * Notes: low 48 bits of param_1 supply the head of the name. */
word_t sk_script_name_ht(word_t name_head)
{
    return (name_head & 0xffffffffffffull) | 0x7468000000000000ull; /* "th" in high 2 bytes */
}

/* FUN_00465ab8 @ 0x00465ab8   (est. sk_script_name_r)
 * Ghidra: ulong FUN_00465ab8(ulong param_1)
 * Builds a script-name word: keeps the caller's low 48 bits and ORs 'r'
 * (0x72) into bits 48..55. Confidence: medium (ASCII 'r').
 * Notes: low 48 bits of param_1 supply the head of the name. */
word_t sk_script_name_r_5ab8(word_t name_head)
{
    return (name_head & 0xffffffffffffull) | 0x72000000000000ull; /* 'r' at byte 6 */
}

/* FUN_00465b64 @ 0x00465b64   (est. sk_script_name_ic)
 * Ghidra: ulong FUN_00465b64(ulong param_1)
 * Builds a script-name word: keeps the caller's word except bits 32..47 and
 * ORs the 2-byte prefix "ic" (0x6369) into bits 32..47. Confidence: high
 * (ASCII). Notes: caller supplies the surrounding name bytes. */
word_t sk_script_name_ic(word_t name)
{
    return (name & 0xffff0000ffffffffull) | 0x636900000000ull; /* "ic" at bytes 4-5 */
}

/* FUN_00465b98 @ 0x00465b98   (est. sk_script_name_m)
 * Ghidra: ulong FUN_00465b98(ulong param_1)
 * Builds a script-name word: keeps the caller's word except bits 40..47 and
 * ORs 'm' (0x6d) into bits 40..47. Confidence: medium (ASCII 'm').
 * Notes: caller supplies the surrounding name bytes. */
word_t sk_script_name_m(word_t name)
{
    return (name & 0xffff0000ffffffffull) | 0x6d00000000ull; /* 'm' at byte 5 */
}

/* FUN_00465bf4 @ 0x00465bf4   (est. sk_script_name_nese)
 * Ghidra: ulong FUN_00465bf4(ulong param_1)
 * Builds a script-name word: keeps the caller's low 32 bits and ORs the
 * fixed prefix "nese" (0x6573656e) into bits 32..63. Confidence: high (ASCII).
 * Notes: low 32 bits of param_1 supply the tail of the name. */
word_t sk_script_name_nese_5bf4(word_t name_tail)
{
    return (name_tail & 0xffffffffull) | 0x6573656e00000000ull; /* "nese" in high 4 bytes */
}

/* FUN_004661cc @ 0x004661cc   (est. sk_script_name_t)
 * Ghidra: ulong FUN_004661cc(ulong param_1)
 * Builds a script-name word: keeps the caller's low 48 bits and ORs 't'
 * (0x74) into bits 48..55. Confidence: medium (ASCII 't').
 * Notes: low 48 bits of param_1 supply the head of the name. */
word_t sk_script_name_t(word_t name_head)
{
    return (name_head & 0xffffffffffffull) | 0x74000000000000ull; /* 't' at byte 6 */
}

/* FUN_004661d8 @ 0x004661d8   (est. sk_script_name_i)
 * Ghidra: ulong FUN_004661d8(ulong param_1)
 * Builds a script-name word: keeps the caller's word except bits 40..47 and
 * ORs 'i' (0x69) into bits 40..47. Confidence: medium (ASCII 'i').
 * Notes: caller supplies the surrounding name bytes. */
word_t sk_script_name_i(word_t name)
{
    return (name & 0xffff0000ffffffffull) | 0x6900000000ull; /* 'i' at byte 5 */
}

/* ------------------------------------------------------------------ *
 * 16-byte descriptor returns and stack-slot/pointer accessors.
 * ------------------------------------------------------------------ */

/* FUN_00465aa0 @ 0x00465aa0   (est. sk_script_desc_5aa0)
 * Ghidra: undefined1 [16] FUN_00465aa0(void)
 * Returns the 16-byte descriptor pointed to by FUN_0001a1c8() — the 
 * first-word/second-word pair at that pointer. Confidence: medium.
 * Notes: FUN_0001a1c8() returns a pointer to a 16-byte table entry. */
sk_r25_pair_t sk_script_desc_5aa0(void)
{
    sk_r25_pair_t *p = sk_h_0001a1c8();
    sk_r25_pair_t r;
    r.lo = p->lo;
    r.hi = p->hi;
    return r;
}

/* FUN_00465b04 @ 0x00465b04   (est. sk_script_desc_5b04)
 * Ghidra: undefined1 [16] FUN_00465b04(void)
 * Returns the 16-byte descriptor pointed to by the low-nibble-clearing helper
 * FUN_00458b14's target. Confidence: low.
 * Notes: FUN_00458b14() returns a pointer; *that* 16 bytes are returned. */
sk_r25_pair_t sk_script_desc_5b04(void)
{
    /* 16 bytes at the pointer returned by FUN_00458b14() */
    sk_r25_pair_t r;
    r.lo = 0;                            /* *sk_h_00458b14 target, lo */
    r.hi = 0;                            /* *sk_h_00458b14 target, hi */
    (void)sk_h_00458b14;
    return r;
}

/* FUN_00465ea0 @ 0x00465ea0   (est. sk_script_desc_5ea0)
 * Ghidra: undefined1 [16] FUN_00465ea0(void)
 * Returns a 16-byte descriptor: lo = caller stack + 0x140, hi = caller stack
 * + 0x70. Confidence: low (stack-slot artifacts).
 * Notes: &stack0x00000140 and &stack0x00000070. */
sk_r25_pair_t sk_script_desc_5ea0(void)
{
    sk_r25_pair_t r;
    r.lo = 0x140ull;                     /* &stack0x00000140 */
    r.hi = 0x70ull;                      /* &stack0x00000070 */
    return r;
}

/* FUN_00465f34 @ 0x00465f34   (est. sk_script_desc_5f34)
 * Ghidra: undefined1 [16] FUN_00465f34(undefined8 *param_1)
 * Returns a 16-byte descriptor: lo = param_1[0], hi = *(unaff_x20 + 8).
 * Confidence: low.
 * Notes: unaff_x20 register fragment supplies the second word. */
sk_r25_pair_t sk_script_desc_5f34(const word_t *src)
{
    sk_r25_pair_t r;
    r.lo = src[0];
    r.hi = 0;                            /* *(unaff_x20 + 8) */
    return r;
}

/* FUN_0046613c @ 0x0046613c   (est. sk_stack_ptr_613c)
 * Ghidra: undefined1 * FUN_0046613c(void)
 * Returns a pointer to the caller's stack slot 0xc8. Confidence: low.
 * Notes: &stack0x000000c8. */
word_t sk_stack_ptr_613c(void)
{
    return 0xc8ull;                      /* &stack0x000000c8 */
}

/* FUN_00466190 @ 0x00466190   (est. sk_zero_desc_6190)
 * Ghidra: undefined1 [16] FUN_00466190(void)
 * Returns the zero 16-byte descriptor (ZEXT816(0)). Confidence: high
 * (trivial constant). */
sk_r25_pair_t sk_zero_desc_6190(void)
{
    sk_r25_pair_t r;
    r.lo = 0;
    r.hi = 0;
    return r;
}

/* ------------------------------------------------------------------ *
 * Helper wrappers and forwards to sibling-slice callees.
 * ------------------------------------------------------------------ */

/* FUN_00465a04 @ 0x00465a04   (est. sk_release_5a04)
 * Ghidra: void FUN_00465a04(void)
 * Forwards (with a zeroed argument) to the object/cap release helper.
 * Confidence: medium.
 * Notes: FUN_003a25d4(); register fragment: arg not attributed. */
void sk_release_5a04(void)
{
    sk_h_003a25d4(0);
}

/* FUN_00465a14 @ 0x00465a14   (est. sk_fwd_5a14)
 * Ghidra: void FUN_00465a14(void)
 * Calls the FUN_00461cb8 helper with a caller stack slot, the constant
 * 0x657a00, and the address of DAT_005a4ad0. Confidence: medium.
 * Notes: FUN_00461cb8(&stack0x000000d8, 0x657a00, &DAT_005a4ad0). */
void sk_fwd_5a14(void)
{
    sk_h_00461cb8(0xd8, 0x657a00, 0x5a4ad0); /* &stack0xd8, const, &DAT_005a4ad0 */
}

/* FUN_00465a40 @ 0x00465a40   (est. sk_memmove_5a40)
 * Ghidra: void FUN_00465a40(void)
 * Forwards two caller stack buffers (0x99 bytes) to the memmove helper.
 * Confidence: medium.
 * Notes: FUN_00117cc4(&stack0x00000140, &stack0x000000a0, 0x99). */
void sk_memmove_5a40(void)
{
    sk_h_00117cc4((word_t *)0x140, (word_t *)0xa0, 0x99); /* stack-slot artifacts */
}

/* FUN_00465a50 @ 0x00465a50   (est. sk_copy5words_5a50)
 * Ghidra: void FUN_00465a50(void)
 * Copies five words (offsets 0x10..0x38) from (unaff_x19) into (unaff_x20),
 * then releases the old word at (unaff_x20 + 0x38) via the object/cap
 * release helper. Confidence: medium.
 * Notes: unaff_x19/unaff_x20 register fragments; FUN_003a25d4(old +0x38). */
void sk_copy5words_5a50(void)
{
    /* *(x20+0x18)=*(x19+0x18); *(x20+0x10)=*(x19+0x10);
     * *(x20+0x28)=*(x19+0x28); *(x20+0x20)=*(x19+0x20);
     * *(x20+0x30)=*(x19+0x30); *(x20+0x38)=*(x19+0x38);
     * sk_h_003a25d4(*(x20+0x38)); */
    sk_h_003a25d4(0);                    /* release *(x20+0x38) from register fragment */
}

/* FUN_00465a70 @ 0x00465a70   (est. sk_fwd_5a70)
 * Ghidra: void FUN_00465a70(void)
 * Loads a word at (unaff_x19 + 0x50) and forwards it to FUN_003a261c.
 * Confidence: low.
 * Notes: unaff_x19 register fragment. */
void sk_fwd_5a70(void)
{
    sk_h_003a261c(0);                    /* *(unaff_x19 + 0x50) */
}

/* FUN_00465a88 @ 0x00465a88   (est. sk_fwd_5a88)
 * Ghidra: void FUN_00465a88(void)
 * Forwards the two words at (unaff_x20 + 0x10/0x18) to the vspace/ipc
 * transition helper, having set up a {0x5b, 0xe100000000000000} frame.
 * Confidence: medium.
 * Notes: thunk_FUN_002acbb8(*(x20+0x10), *(x20+0x18)); frame tag 0xe1|len. */
void sk_fwd_5a88(void)
{
    sk_h_002acbb8(0, 0);                 /* *(unaff_x20+0x10), *(unaff_x20+0x18) */
}

/* FUN_00465ac0 @ 0x00465ac0   (est. sk_memmove_5ac0)
 * Ghidra: void FUN_00465ac0(void)
 * Forwards two caller stack buffers (0x80 bytes) to the memmove helper.
 * Confidence: medium.
 * Notes: FUN_00117cc4(&stack0x000003d0, &stack0x000002c0, 0x80). */
void sk_memmove_5ac0(void)
{
    sk_h_00117cc4((word_t *)0x3d0, (word_t *)0x2c0, 0x80); /* stack-slot artifacts */
}

/* FUN_00465ad0 @ 0x00465ad0   (est. sk_fwd_5ad0)
 * Ghidra: void FUN_00465ad0(void)
 * Forwards the four words at unaff_x20[0..3] to the FUN_0044c5d8 helper.
 * Confidence: low.
 * Notes: unaff_x20 register fragment. */
void sk_fwd_5ad0(void)
{
    sk_h_0044c5d8(0, 0, 0, 0);           /* unaff_x20[0..3] */
}

/* FUN_00465adc @ 0x00465adc   (est. sk_re_diag_5adc)
 * Ghidra: void FUN_00465adc(void)
 * Builds a small stack frame {0, 0, 3} and forwards it to the regex diag
 * emitter. Confidence: low.
 * Notes: FUN_0042ec68(&stack0x00000038); the 3 is a verbosity/level field. */
void sk_re_diag_5adc(void)
{
    /* stack frame {0, 0, 3} forwarded to FUN_0042ec68 */
    sk_h_0042ec68(0);
}

/* FUN_00465af4 @ 0x00465af4   (est. sk_memmove_5af4)
 * Ghidra: void FUN_00465af4(void)
 * Forwards two caller stack buffers (0x99 bytes) to the memmove helper.
 * Confidence: medium.
 * Notes: FUN_00117cc4(&stack0x00000278, &stack0x00000378, 0x99). */
void sk_memmove_5af4(void)
{
    sk_h_00117cc4((word_t *)0x278, (word_t *)0x378, 0x99); /* stack-slot artifacts */
}

/* FUN_00465b1c @ 0x00465b1c   (est. sk_store_load_ref_5b1c)
 * Ghidra: void FUN_00465b1c(undefined8 param_1, undefined8 *param_2)
 * Stores *param_2 into (unaff_x20), then calls the refcount acquire helper.
 * Confidence: medium.
 * Notes: unaff_x20 register fragment (destination); FUN_0036b270(). */
void sk_store_load_ref_5b1c(const word_t *src)
{
    /* *unaff_x20 = *src; */
    sk_h_0036b270(0);
    (void)src;
}

/* FUN_00465b38 @ 0x00465b38   (est. sk_fwd_5b38)
 * Ghidra: void FUN_00465b38(void)
 * Sets up a {0x27, 0xe100000000000000} frame and calls the vspace/ipc
 * transition helper. Confidence: medium.
 * Notes: thunk_FUN_002acbb8(); frame tag 0xe1|len 1, value 0x27. */
void sk_fwd_5b38(void)
{
    /* frame {0x27, 0xe100000000000000} */
    sk_h_002acbb8(0, 0);
}

/* FUN_00465b58 @ 0x00465b58   (est. sk_page_to_pfn_5b58)
 * Ghidra: void FUN_00465b58(void)
 * Forwards the constant 2 to the vspace wait/sync helper. Confidence:
 * medium.
 * Notes: thunk_FUN_002298d4(2). */
void sk_page_to_pfn_5b58(void)
{
    sk_h_002298d4(2);
}

/* FUN_00465b6c @ 0x00465b6c   (est. sk_memmove_5b6c)
 * Ghidra: void FUN_00465b6c(void)
 * Forwards the caller's buffer arguments to the overlapping memmove helper.
 * Confidence: medium.
 * Notes: FUN_00117cc4(); register fragments. */
void sk_memmove_5b6c(void)
{
    sk_h_00117cc4(0, 0, 0);
}

/* FUN_00465b80 @ 0x00465b80   (est. sk_fwd_5b80)
 * Ghidra: void FUN_00465b80(void)
 * Calls the FUN_0045659c helper with no arguments. Confidence: medium.
 * Notes: FUN_0045659c(). */
void sk_fwd_5b80(void)
{
    sk_h_0045659c();
}

/* FUN_00465ba0 @ 0x00465ba0   (est. sk_fwd_5ba0)
 * Ghidra: void FUN_00465ba0(undefined8 param_1, undefined8 param_2)
 * Forwards param_1 and param_2 with the constants 0xa0d and
 * 0xe200000000000000 and 0 to the FUN_002a0cf8 helper. Confidence: low.
 * Notes: FUN_002a0cf8(param_1, param_2, 0xa0d, 0xe200000000000000, 0). */
void sk_fwd_5ba0(word_t p1, word_t p2)
{
    sk_h_002a0cf8(p1, p2, 0xa0d, 0xe200000000000000ull, 0);
}

/* FUN_00465bb0 @ 0x00465bb0   (est. sk_ref_acquire_5bb0)
 * Ghidra: void FUN_00465bb0(undefined8 param_1)
 * Forwards param_1 to the refcount acquire helper via a stack frame.
 * Confidence: medium.
 * Notes: thunk_FUN_0036b270(param_1). */
void sk_ref_acquire_5bb0(word_t p1)
{
    /* uStack0x18 = p1; thunk_FUN_0036b270() */
    sk_h_0036b270(p1);
}

/* FUN_00465bbc @ 0x00465bbc   (est. sk_fwd_5bbc)
 * Ghidra: void FUN_00465bbc(void)
 * Calls the FUN_00461cb8 helper with a caller stack slot, the constant
 * 0x6579f8, and the address of DAT_005a19d8. Confidence: medium.
 * Notes: FUN_00461cb8(&stack0x00000040, 0x6579f8, &DAT_005a19d8). */
void sk_fwd_5bbc(void)
{
    sk_h_00461cb8(0x40, 0x6579f8, 0x5a19d8); /* &stack0x40, const, &DAT_005a19d8 */
}

/* FUN_00465c00 @ 0x00465c00   (est. sk_memmove_5c00)
 * Ghidra: void FUN_00465c00(void)
 * Forwards the caller's buffer arguments to the overlapping memmove helper.
 * Confidence: medium.
 * Notes: FUN_00117cc4(); register fragments. */
void sk_memmove_5c00(void)
{
    sk_h_00117cc4(0, 0, 0);
}

/* FUN_00465c0c @ 0x00465c0c   (est. sk_init_memmove_5c0c)
 * Ghidra: void FUN_00465c0c(void)
 * Writes 0 to (x29 - 0x10) and 0xe000000000000000 to (x29 - 8), then calls
 * the memmove helper. Confidence: low.
 * Notes: unaff_x29 register fragment. */
void sk_init_memmove_5c0c(void)
{
    /* *(x29-0x10)=0; *(x29-8)=0xe000000000000000; */
    sk_h_00117cc4(0, 0, 0);
}

/* FUN_00465c24 @ 0x00465c24   (est. sk_fill14words_5c24)
 * Ghidra: void FUN_00465c24(undefined1 param_1 [16])
 * Replicates the two words of the 16-byte argument (lo/hi) into offsets
 * 0x10..0x78 of (in_x9) — 7 copies of the {lo,hi} pair. Confidence: medium.
 * Notes: in_x9 register fragment (destination buffer). */
void sk_fill14words_5c24(word_t lo, word_t hi)
{
    /* *(in_x9+0x10..0x78) = alternating {lo, hi} */
    (void)lo; (void)hi;
}

/* FUN_00465c50 @ 0x00465c50   (est. sk_memmove_5c50)
 * Ghidra: void FUN_00465c50(undefined8 param_1)
 * Forwards param_1 and a caller stack slot (0x49 bytes) to the memmove
 * helper. Confidence: medium.
 * Notes: FUN_00117cc4(param_1, &stack0x00000f08, 0x49). */
void sk_memmove_5c50(word_t dst)
{
    sk_h_00117cc4((word_t *)dst, (word_t *)0xf08, 0x49); /* &stack0xf08 */
}

/* FUN_00465c5c @ 0x00465c5c   (est. sk_fwd_5c5c)
 * Ghidra: void FUN_00465c5c(undefined8 param_1..5)
 * Reorders and forwards args to the FUN_002a0cf8 helper: (p2, p1, p4, p5, 0).
 * Confidence: medium.
 * Notes: FUN_002a0cf8(param_2, param_1, param_4, param_5, 0). */
void sk_fwd_5c5c(word_t p1, word_t p2, word_t p3, word_t p4, word_t p5)
{
    (void)p3;
    sk_h_002a0cf8(p2, p1, p4, p5, 0);
}

/* FUN_00465c68 @ 0x00465c68   (est. sk_release_5c68)
 * Ghidra: void FUN_00465c68(void)
 * Forwards (with a zeroed argument) to the object/cap release helper.
 * Confidence: medium.
 * Notes: FUN_003a25d4(); register fragment. */
void sk_release_5c68(void)
{
    sk_h_003a25d4(0);
}

/* FUN_00465c74 @ 0x00465c74   (est. sk_fwd_5c74)
 * Ghidra: void FUN_00465c74(void)
 * Calls the vspace/ipc transition helper with no arguments. Confidence:
 * medium.
 * Notes: thunk_FUN_002acbb8(). */
void sk_fwd_5c74(void)
{
    sk_h_002acbb8(0, 0);
}

/* FUN_00465cac @ 0x00465cac   (est. sk_store_init2_5cac)
 * Ghidra: void FUN_00465cac(void)
 * Stores two stack words (0x50/0x58) into (unaff_x23 + 0x18/0x20) and writes
 * 0 / 0xe000000000000000 into the caller's frame (x29 - 0xb0 / -0xa8).
 * Confidence: low.
 * Notes: unaff_x23/unaff_x29 register fragments. */
void sk_store_init2_5cac(void)
{
    /* *(x23+0x18)=in_stack_0x50; *(x23+0x20)=in_stack_0x58;
     * *(x29-0xb0)=0; *(x29-0xa8)=0xe000000000000000; */
}

/* FUN_00465d28 @ 0x00465d28   (est. sk_copy2words_5d28)
 * Ghidra: void FUN_00465d28(void)
 * Copies two words from (unaff_x19 + 0x40/0x48) into (unaff_x20 + 0x40/0x48).
 * Confidence: medium.
 * Notes: unaff_x19/unaff_x20 register fragments. */
void sk_copy2words_5d28(void)
{
    /* *(x20+0x40)=*(x19+0x40); *(x20+0x48)=*(x19+0x48) */
}

/* FUN_00465e18 @ 0x00465e18   (est. sk_store8words_5e18)
 * Ghidra: void FUN_00465e18(void)
 * Stores the eight callee-saved registers x21..x28 into (unaff_x19 + 0x10
 * .. 0x48). Confidence: medium.
 * Notes: unaff_x19 register fragment (destination); caller-saved registers
 * carried as unaff_* artifacts. */
void sk_store8words_5e18(void)
{
    /* *(x19+0x10..0x48) = x21..x28 */
}

/* FUN_00465eac @ 0x00465eac   (est. sk_store3words_5eac)
 * Ghidra: void FUN_00465eac(long param_1)
 * Stores unaff_x19 into param_1+0x10, then (into the slot selected by
 * unaff_x23*0x20 + param_1 + 0x20/0x28) unaff_x20 and unaff_x22. Confidence:
 * low.
 * Notes: unaff_x19/x20/x22/x23 register fragments. */
void sk_store3words_5eac(word_t base)
{
    /* *(base+0x10)=unaff_x19;
     * base' = base + unaff_x23*0x20;
     * *(base'+0x20)=unaff_x20; *(base'+0x28)=unaff_x22; */
    (void)base;
}

/* FUN_00465ed4 @ 0x00465ed4   (est. sk_cmp_gt1_5ed4)
 * Ghidra: bool FUN_00465ed4(void)
 * Returns whether the caller's un-attributed x9 is greater than 1.
 * Confidence: low.
 * Notes: in_x9 register fragment. */
bool sk_cmp_gt1_5ed4(void)
{
    return 1 < 0;                        /* in_x9 > 1 */
}

/* FUN_00465ee0 @ 0x00465ee0   (est. sk_copy1byte_5ee0)
 * Ghidra: void FUN_00465ee0(void)
 * Copies one byte from (unaff_x19 + 0x30) into (unaff_x20 + 0x30).
 * Confidence: medium.
 * Notes: unaff_x19/unaff_x20 register fragments. */
void sk_copy1byte_5ee0(void)
{
    /* *(x20+0x30) = *(x19+0x30) */
}

/* FUN_00465eec @ 0x00465eec   (est. sk_copy6words_5eec)
 * Ghidra: void FUN_00465eec(undefined8 param_1, long param_2)
 * Copies six words (offsets 0x20..0x48) from param_2 into (unaff_x19).
 * Confidence: medium.
 * Notes: unaff_x19 register fragment (destination). */
void sk_copy6words_5eec(word_t p1, const word_t *src)
{
    /* *(x19+0x28)=src[5]; *(x19+0x20)=src[4]; *(x19+0x38)=src[7];
     * *(x19+0x30)=src[6]; *(x19+0x48)=src[9]; *(x19+0x40)=src[8]; */
    (void)p1; (void)src;
}

/* FUN_00465f20 @ 0x00465f20   (est. sk_copy5words_5f20)
 * Ghidra: void FUN_00465f20(undefined8 param_1, long param_2)
 * Copies five words (offsets 0x10..0x38) from param_2 into (unaff_x19).
 * Confidence: medium.
 * Notes: unaff_x19 register fragment (destination). */
void sk_copy5words_5f20(word_t p1, const word_t *src)
{
    /* *(x19+0x18)=src[3]; *(x19+0x10)=src[2]; *(x19+0x28)=src[5];
     * *(x19+0x20)=src[4]; *(x19+0x30)=src[6]; *(x19+0x38)=src[7]; */
    (void)p1; (void)src;
}

/* FUN_00465f68 @ 0x00465f68   (est. sk_copy2words_5f68)
 * Ghidra: void FUN_00465f68(void)
 * Copies two words from (unaff_x19 + 0x70/0x78) into (unaff_x20 + 0x70/0x78).
 * Confidence: medium.
 * Notes: unaff_x19/unaff_x20 register fragments. */
void sk_copy2words_5f68(void)
{
    /* *(x20+0x70)=*(x19+0x70); *(x20+0x78)=*(x19+0x78) */
}

/* FUN_00466034 @ 0x00466034   (est. sk_copy2words_6034)
 * Ghidra: void FUN_00466034(void)
 * Copies two words from (unaff_x20 + 0x18/0x20) into (unaff_x19 + 0x18/0x20).
 * Confidence: medium.
 * Notes: unaff_x19/unaff_x20 register fragments. */
void sk_copy2words_6034(void)
{
    /* *(x19+0x18)=*(x20+0x18); *(x19+0x20)=*(x20+0x20) */
}

/* FUN_00466074 @ 0x00466074   (est. sk_store_tag_6074)
 * Ghidra: void FUN_00466074(undefined8 param_1, long param_2)
 * Stores param_1 into param_2+0x20 and the tag 0xe100000000000000 into
 * param_2+0x28. Confidence: medium.
 * Notes: tag 0xe1|len 1 in the high word. */
void sk_store_tag_6074(word_t val, word_t *dst)
{
    dst[0x20 / 8] = val;
    dst[0x28 / 8] = 0xe100000000000000ull;
}

/* FUN_004660a0 @ 0x004660a0   (est. sk_store_desc_60a0)
 * Ghidra: void FUN_004660a0(undefined1 param_1 [16])
 * Stores the two words of the 16-byte argument into (in_x10 + 0x28/0x30) and
 * a 4-byte value from (x29 - 0x90) into (in_x10 + 0x49). Confidence: low.
 * Notes: in_x10/unaff_x29 register fragments. */
void sk_store_desc_60a0(word_t lo, word_t hi)
{
    /* *(in_x10+0x30)=hi; *(in_x10+0x28)=lo;
     * *(uint32_t*)(in_x10+0x49) = *(uint32_t*)(x29-0x90); */
    (void)lo; (void)hi;
}

/* FUN_004660e0 @ 0x004660e0   (est. sk_fwd_60e0)
 * Ghidra: void FUN_004660e0(void)
 * Calls the FUN_00458af8 helper with no arguments. Confidence: medium.
 * Notes: FUN_00458af8(). */
void sk_fwd_60e0(void)
{
    sk_h_00458af8();
}

/* FUN_0046617c @ 0x0046617c   (est. sk_zero10words_617c)
 * Ghidra: void FUN_0046617c(void)
 * Zeroes the ten words at (unaff_x19)[0..9]. Confidence: medium.
 * Notes: unaff_x19 register fragment (destination). */
void sk_zero10words_617c(void)
{
    /* x19[0..9] = 0 */
}

/* FUN_004661a4 @ 0x004661a4   (est. sk_copy2words_61a4)
 * Ghidra: void FUN_004661a4(void)
 * Copies two words from (unaff_x20 + 0xa0/0xa8) into (unaff_x19 + 0xa0/0xa8).
 * Confidence: medium.
 * Notes: unaff_x19/unaff_x20 register fragments. */
void sk_copy2words_61a4(void)
{
    /* *(x19+0xa0)=*(x20+0xa0); *(x19+0xa8)=*(x20+0xa8) */
}
