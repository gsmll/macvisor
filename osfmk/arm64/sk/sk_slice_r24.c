/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel,
 * arm64e, image base 0) — the cL4 microkernel. Ground truth: Ghidra FUN_ names +
 * addresses in program cl4_kernel.raw. Version "cL4 microkernel (cL4
 * (679.100.61))". All names are estimates unless string/header-matched.
 *
 * This file covers wave batch SKR24, slice 0x004651e4-0x004659d4: a
 * Unicode-script name/property lookup table plus a cluster of small
 * helpers. The bulk of the functions return a script name (as an 8-byte
 * little-endian ASCII fragment, or as a 16-byte {name, tag} pair), build a
 * name by OR-ing a fixed prefix into the low 32 bits of an argument, or are
 * empty no-op slots. A few callers forward to helpers owned by sibling
 * slices (memmove-like copy, refcount, vspace/ipc, regex, sha256, siphash).
 *
 * The 16-byte {lo,hi} returns encode a script descriptor: `lo` holds the
 * ASCII name (bytes 0..len), `hi` holds 0xe0|len in the low byte and zero
 * padding. The 8-byte returns are the low name fragment of a longer script
 * name; the OR-into-low32 builders compose a name from a fixed prefix plus a
 * caller-supplied tail. `unaff_*` register artifacts are described in the
 * notes of each function.
 */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "sk_internal.h"

/* 16-byte (two-word) result used by the return-by-value helpers below. */
typedef struct sk_r24_pair { uint64_t lo, hi; } sk_r24_pair_t;

/* ------------------------------------------------------------------ *
 * Out-of-range cL4/Swift-runtime helpers referenced by this slice.
 * FUN_ addresses in comments; bodies owned by sibling SK range workers.
 * Names are estimates.
 * ------------------------------------------------------------------ */

extern void sk_h_003a25d4(word_t a);                     /* FUN_003a25d4 (object/cap release via mask) */
extern void sk_h_00117cc4(word_t *d, word_t *s, word_t n); /* FUN_00117cc4 (overlapping memmove, branch on w18) */
extern void sk_h_00458d30(word_t a, word_t b);           /* FUN_00458d30 (forwards to FUN_0045d2e4(b,a)) */
extern void sk_h_004589e8(void);                         /* FUN_004589e8 */
extern void sk_h_0041e21c(word_t a);                     /* FUN_0041e21c (16-byte buffer descriptor getter; SWBP on error) */
extern void sk_h_0029fa0c(word_t a, word_t b, word_t c, word_t d); /* FUN_0029fa0c */
extern void sk_h_002acbb8(void);                         /* thunk_FUN_002acbb8 (vspace/ipc transition) */
extern void sk_h_002298d4(word_t a);                     /* thunk_FUN_002298d4 (vspace wait/sync, arg >>0xe pfn) */
extern word_t sk_h_00458d04(word_t a);                   /* FUN_00458d04 (reads *(a+0x170)>>0x3d) */
extern void sk_h_001a84f4(void *p);                      /* FUN_001a84f4 (sk_sha256_iv_init) */
extern void sk_h_004368c0(word_t a, word_t b, word_t c, word_t d); /* FUN_004368c0 (regex parse backref/scalar) */
extern void sk_h_0042ec68(void *p);                      /* FUN_0042ec68 (regex diag emit) */
extern void sk_h_00114330(word_t a);                     /* thunk_FUN_00114330 */
extern void sk_h_00229a3c(word_t a);                     /* FUN_00229a3c (sk_siphash_absorb_byte) */
extern void sk_h_00458b14(word_t a);                     /* FUN_00458b14 (clears low nibble of *(a+0x98)) */
extern void sk_h_0036b270(void);                         /* FUN_0036b270 (sk_refcount_acquire) */

/* ------------------------------------------------------------------ *
 * Unicode script-name table (16-byte descriptor returns).
 * ------------------------------------------------------------------ */

/* FUN_004651e4 @ 0x004651e4   (est. sk_script_name_ahom)
 * Ghidra: undefined1[16] FUN_004651e4(void)
 * Returns the script descriptor for "Ahom": lo = ASCII "Ahom", hi = 0xe4
 * (0xe0 | length 4). Confidence: high (ASCII literal matches script name).
 * Notes: 16-byte return packed in x0/x1. */
sk_r24_pair_t sk_script_name_ahom(void)
{
    sk_r24_pair_t r;
    r.lo = 0x6d6f6841ull;              /* "Ahom" LE */
    r.hi = 0xe400000000000000ull;      /* 0xe0 | 4 */
    return r;
}

/* FUN_004651f4 @ 0x004651f4   (est. sk_script_name_modi)
 * Ghidra: undefined1[16] FUN_004651f4(void)
 * Script descriptor for "Modi": lo = ASCII "Modi", hi = 0xe4. Confidence:
 * high (ASCII literal). */
sk_r24_pair_t sk_script_name_modi(void)
{
    sk_r24_pair_t r;
    r.lo = 0x69646f4dull;              /* "Modi" LE */
    r.hi = 0xe400000000000000ull;
    return r;
}

/* FUN_00465204 @ 0x00465204   (est. sk_script_name_newa)
 * Ghidra: undefined1[16] FUN_00465204(void)
 * Script descriptor for "Newa": lo = ASCII "Newa", hi = 0xe4. Confidence:
 * high (ASCII literal). */
sk_r24_pair_t sk_script_name_newa(void)
{
    sk_r24_pair_t r;
    r.lo = 0x6177654eull;              /* "Newa" LE */
    r.hi = 0xe400000000000000ull;
    return r;
}

/* FUN_00465214 @ 0x00465214   (est. sk_script_name_lisu)
 * Ghidra: undefined1[16] FUN_00465214(void)
 * Script descriptor for "Lisu": lo = ASCII "Lisu", hi = 0xe4. Confidence:
 * high (ASCII literal). */
sk_r24_pair_t sk_script_name_lisu(void)
{
    sk_r24_pair_t r;
    r.lo = 0x7573694cull;              /* "Lisu" LE */
    r.hi = 0xe400000000000000ull;
    return r;
}

/* FUN_00465224 @ 0x00465224   (est. sk_script_name_cham)
 * Ghidra: undefined1[16] FUN_00465224(void)
 * Script descriptor for "Cham": lo = ASCII "Cham", hi = 0xe4. Confidence:
 * high (ASCII literal). */
sk_r24_pair_t sk_script_name_cham(void)
{
    sk_r24_pair_t r;
    r.lo = 0x6d616843ull;              /* "Cham" LE */
    r.hi = 0xe400000000000000ull;
    return r;
}

/* FUN_004652c4 @ 0x004652c4   (est. sk_script_name_c2c4)
 * Ghidra: undefined1[16] FUN_004652c4(void)
 * Returns a script descriptor whose lo holds the small constant 0x7e3f28
 * (likely a length/offset) and hi = 0xe3 (0xe0 | length 3). Confidence: low
 * (constant semantics inferred).
 * Notes: lo 0x7e3f28 is a Ghidra immediate, not a string. */
sk_r24_pair_t sk_script_name_c2c4(void)
{
    sk_r24_pair_t r;
    r.lo = 0x7e3f28ull;
    r.hi = 0xe300000000000000ull;      /* 0xe0 | 3 */
    return r;
}

/* FUN_004655d8 @ 0x004655d8   (est. sk_script_desc_d8)
 * Ghidra: undefined1[16] FUN_004655d8(void)
 * Returns a script descriptor built from the caller's x9: lo = the constant
 * 0xd00000000000001e, hi = in_x9 | 0x8000000000000000 (sets bit 63). The
 * x9 input is an un-attributed caller-saved register. Confidence: low.
 * Notes: in_x9 is an unaff register fragment. */
sk_r24_pair_t sk_script_desc_d8(void)
{
    uint64_t x9;                        /* in_x9: un-attributed caller register */
    sk_r24_pair_t r;
    (void)x9;
    r.lo = 0xd00000000000001eull;
    r.hi = 0x8000000000000000ull;       /* in_x9 | 0x8000000000000000 */
    return r;
}

/* FUN_004656bc @ 0x004656bc   (est. sk_script_desc_bc)
 * Ghidra: undefined1[16] FUN_004656bc(void)
 * Returns a script descriptor: lo = caller's stack pointer + 0x6b8, hi = the
 * immediate 0x657b28. Confidence: low.
 * Notes: lo references &stack0x000006b8 (a Ghidra stack-slot artifact). */
sk_r24_pair_t sk_script_desc_bc(void)
{
    sk_r24_pair_t r;
    r.lo = 0x6b8ull;                    /* &stack0x000006b8 */
    r.hi = 0x657b28ull;
    return r;
}

/* FUN_00465788 @ 0x00465788   (est. sk_script_desc_788)
 * Ghidra: undefined1[16] FUN_00465788(void)
 * Returns a descriptor: lo = caller stack + 0x180, hi = caller stack + 8.
 * Confidence: low (stack-slot artifacts).
 * Notes: &stack0x00000180 and &stack0x00000008. */
sk_r24_pair_t sk_script_desc_788(void)
{
    sk_r24_pair_t r;
    r.lo = 0x180ull;                    /* &stack0x00000180 */
    r.hi = 0x8ull;                      /* &stack0x00000008 */
    return r;
}

/* FUN_004657ac @ 0x004657ac   (est. sk_script_name_7ac)
 * Ghidra: undefined1[16] FUN_004657ac(void)
 * Returns a descriptor: lo = 0x22, hi = 0xe1 (0xe0 | length 1). Confidence:
 * low.
 * Notes: lo 0x22 is a Ghidra immediate. */
sk_r24_pair_t sk_script_name_7ac(void)
{
    sk_r24_pair_t r;
    r.lo = 0x22ull;
    r.hi = 0xe100000000000000ull;       /* 0xe0 | 1 */
    return r;
}

/* FUN_0046589c @ 0x0046589c   (est. sk_script_name_89c)
 * Ghidra: undefined1[16] FUN_0046589c(void)
 * Returns a descriptor: lo = 0x2c, hi = 0xe1 (0xe0 | length 1). Confidence:
 * low.
 * Notes: lo 0x2c is a Ghidra immediate. */
sk_r24_pair_t sk_script_name_89c(void)
{
    sk_r24_pair_t r;
    r.lo = 0x2cull;
    r.hi = 0xe100000000000000ull;       /* 0xe0 | 1 */
    return r;
}

/* FUN_004658d8 @ 0x004658d8   (est. sk_script_desc_8d8)
 * Ghidra: undefined1[16] FUN_004658d8(void)
 * Returns a descriptor: lo = caller stack + 0xe0, hi = caller stack + 0x1b0.
 * Confidence: low (stack-slot artifacts).
 * Notes: &stack0x000000e0 and &stack0x000001b0. */
sk_r24_pair_t sk_script_desc_8d8(void)
{
    sk_r24_pair_t r;
    r.lo = 0xe0ull;                     /* &stack0x000000e0 */
    r.hi = 0x1b0ull;                    /* &stack0x000001b0 */
    return r;
}

/* ------------------------------------------------------------------ *
 * Unicode script-name table (8-byte name-fragment returns).
 * ------------------------------------------------------------------ */

/* FUN_00465468 @ 0x00465468   (est. sk_script_name_numeri)
 * Ghidra: undefined8 FUN_00465468(void)
 * Returns the 6-byte ASCII fragment "numeri" (little-endian). Confidence:
 * high (ASCII literal). */
word_t sk_script_name_numeri(void)
{
    return 0x6972656d756eull;           /* "numeri" LE */
}

/* FUN_00465590 @ 0x00465590   (est. sk_script_name_lowercas)
 * Ghidra: undefined8 FUN_00465590(void)
 * Returns the 8-byte ASCII fragment "lowercas" (LE). Confidence: high
 * (ASCII literal). */
word_t sk_script_name_lowercas(void)
{
    return 0x7361637265776f6cull;       /* "lowercas" LE */
}

/* FUN_00465614 @ 0x00465614   (est. sk_script_name_sorasomp)
 * Ghidra: undefined8 FUN_00465614(void)
 * Returns the 8-byte ASCII fragment "sorasomp" (LE) — the Sora Sompeng
 * script name. Confidence: high (ASCII literal). */
word_t sk_script_name_sorasomp(void)
{
    return 0x706d6f7361726f73ull;       /* "sorasomp" LE */
}

/* FUN_00465710 @ 0x00465710   (est. sk_script_name_gunjalag)
 * Ghidra: undefined8 FUN_00465710(void)
 * Returns the 8-byte ASCII fragment "gunjalag" (LE) — Gunjala Gondi script.
 * Confidence: high (ASCII literal). */
word_t sk_script_name_gunjalag(void)
{
    return 0x67616c616a6e7567ull;       /* "gunjalag" LE */
}

/* FUN_0046574c @ 0x0046574c   (est. sk_script_name_cypromin)
 * Ghidra: undefined8 FUN_0046574c(void)
 * Returns the 8-byte ASCII fragment "cypromin" (LE) — Cypriot Minoan script.
 * Confidence: high (ASCII literal). */
word_t sk_script_name_cypromin(void)
{
    return 0x6e696d6f72707963ull;       /* "cypromin" LE */
}

/* FUN_00465794 @ 0x00465794   (est. sk_script_name_chorasmi)
 * Ghidra: undefined8 FUN_00465794(void)
 * Returns the 8-byte ASCII fragment "chorasmi" (LE) — Chorasmian script.
 * Confidence: high (ASCII literal). */
word_t sk_script_name_chorasmi(void)
{
    return 0x696d7361726f6863ull;       /* "chorasmi" LE */
}

/* FUN_004657e8 @ 0x004657e8   (est. sk_script_name_armenian)
 * Ghidra: undefined8 FUN_004657e8(void)
 * Returns the 8-byte ASCII fragment "armenian" (LE) — Armenian script.
 * Confidence: high (ASCII literal). */
word_t sk_script_name_armenian(void)
{
    return 0x6e61696e656d7261ull;       /* "armenian" LE */
}

/* FUN_0046583c @ 0x0046583c   (est. sk_script_name_pahawhhm)
 * Ghidra: undefined8 FUN_0046583c(void)
 * Returns the 8-byte ASCII fragment "pahawhhm" (LE) — Pahawh Hmong script.
 * Confidence: high (ASCII literal). */
word_t sk_script_name_pahawhhm(void)
{
    return 0x6d68687761686170ull;       /* "pahawhhm" LE */
}

/* FUN_00465854 @ 0x00465854   (est. sk_script_name_oldnorth)
 * Ghidra: undefined8 FUN_00465854(void)
 * Returns the 8-byte ASCII fragment "oldnorth" (LE) — Old North Arabian.
 * Confidence: high (ASCII literal). */
word_t sk_script_name_oldnorth(void)
{
    return 0x6874726f6e646c6full;       /* "oldnorth" LE */
}

/* FUN_0046586c @ 0x0046586c   (est. sk_script_name_olditali)
 * Ghidra: undefined8 FUN_0046586c(void)
 * Returns the 8-byte ASCII fragment "olditali" (LE) — Old Italic script.
 * Confidence: high (ASCII literal). */
word_t sk_script_name_olditali(void)
{
    return 0x696c617469646c6full;       /* "olditali" LE */
}

/* FUN_004658e4 @ 0x004658e4   (est. sk_script_name_currentc)
 * Ghidra: undefined8 FUN_004658e4(void)
 * Returns the 8-byte ASCII fragment "currentc" (LE) — "current" script tag.
 * Confidence: high (ASCII literal). */
word_t sk_script_name_currentc(void)
{
    return 0x79636e6572727563ull;       /* "currentc" LE */
}

/* ------------------------------------------------------------------ *
 * Script-name builders that OR a fixed prefix into the low 32 bits.
 * ------------------------------------------------------------------ */

/* FUN_00465458 @ 0x00465458   (est. sk_script_name_exta)
 * Ghidra: ulong FUN_00465458(ulong param_1)
 * Builds a script-name word: keeps the caller's low 32 bits and ORs the
 * fixed prefix "exta" into bits 32..63. Confidence: high (ASCII prefix).
 * Notes: low 32 bits of param_1 supply the tail of the name. */
word_t sk_script_name_exta(word_t name_tail)
{
    return (name_tail & 0xffffffffull) | 0x6174786500000000ull; /* "exta" in high 4 bytes */
}

/* FUN_00465488 @ 0x00465488   (est. sk_script_desc_5488)
 * Ghidra: undefined1[16] FUN_00465488(void)
 * Returns a 16-byte descriptor with lo = 1 and hi = 0 (ZEXT816(1) << 0x40
 * places the 1 in the high word). Confidence: medium.
 * Notes: ZEXT816(1) << 0x40 packs the value 1 into bits 64..79. */
sk_r24_pair_t sk_script_desc_5488(void)
{
    sk_r24_pair_t r;
    r.lo = 0;
    r.hi = 1;
    return r;
}

/* FUN_00465498 @ 0x00465498   (est. sk_script_name_nese)
 * Ghidra: ulong FUN_00465498(ulong param_1)
 * Builds a script-name word: keeps the caller's low 32 bits and ORs the
 * fixed prefix "nese" into bits 32..63. Confidence: high (ASCII prefix).
 * Notes: low 32 bits of param_1 supply the tail of the name. */
word_t sk_script_name_nese(word_t name_tail)
{
    return (name_tail & 0xffffffffull) | 0x6573656e00000000ull; /* "nese" in high 4 bytes */
}

/* FUN_004657dc @ 0x004657dc   (est. sk_script_name_r)
 * Ghidra: ulong FUN_004657dc(ulong param_1)
 * Builds a script-name word: keeps bits 32..63 of param_1 and ORs 'r' into
 * bits 40..47 (0x72 << 40). Confidence: medium (ASCII 'r').
 * Notes: combines a caller-supplied high fragment with the fixed letter 'r'. */
word_t sk_script_name_r(word_t name_high)
{
    return (name_high & 0xffff0000ffffffffull) | 0x7200000000ull; /* 'r' at byte 5 */
}

/* FUN_004658b4 @ 0x004658b4   (est. sk_script_name_c)
 * Ghidra: ulong FUN_004658b4(ulong param_1)
 * Builds a script-name word: keeps bits 32..63 of param_1 and ORs 'c' into
 * bits 40..47 (0x63 << 40). Confidence: medium (ASCII 'c').
 * Notes: combines a caller-supplied high fragment with the fixed letter 'c'. */
word_t sk_script_name_c(word_t name_high)
{
    return (name_high & 0xffff0000ffffffffull) | 0x6300000000ull; /* 'c' at byte 5 */
}

/* FUN_004659d4 @ 0x004659d4   (est. sk_script_name_digi)
 * Ghidra: ulong FUN_004659d4(ulong param_1)
 * Builds a script-name word: keeps the caller's low 32 bits and ORs the
 * fixed prefix "Digi" into bits 32..63. Confidence: high (ASCII prefix).
 * Notes: low 32 bits of param_1 supply the tail of the name. */
word_t sk_script_name_digi(word_t name_tail)
{
    return (name_tail & 0xffffffffull) | 0x6967694400000000ull; /* "Digi" in high 4 bytes */
}

/* ------------------------------------------------------------------ *
 * No-op / empty slots.
 * ------------------------------------------------------------------ */

/* FUN_00465264 @ 0x00465264   (est. sk_nop_5264)  — empty body. Confidence: medium. */
void sk_nop_5264(void) { }

/* FUN_004652d4 @ 0x004652d4   (est. sk_nop_52d4)  — empty body. Confidence: medium. */
void sk_nop_52d4(void) { }

/* FUN_004652e4 @ 0x004652e4   (est. sk_nop_52e4)  — empty body. Confidence: medium. */
void sk_nop_52e4(void) { }

/* FUN_00465304 @ 0x00465304   (est. sk_nop_5304)  — empty body. Confidence: medium. */
void sk_nop_5304(void) { }

/* FUN_00465330 @ 0x00465330   (est. sk_nop_5330)  — empty body. Confidence: medium. */
void sk_nop_5330(void) { }

/* FUN_00465340 @ 0x00465340   (est. sk_nop_5340)  — empty body. Confidence: medium. */
void sk_nop_5340(void) { }

/* FUN_00465350 @ 0x00465350   (est. sk_nop_5350)  — empty body. Confidence: medium. */
void sk_nop_5350(void) { }

/* FUN_00465360 @ 0x00465360   (est. sk_nop_5360)  — empty body. Confidence: medium. */
void sk_nop_5360(void) { }

/* FUN_00465370 @ 0x00465370   (est. sk_nop_5370)  — empty body. Confidence: medium. */
void sk_nop_5370(void) { }

/* FUN_00465380 @ 0x00465380   (est. sk_nop_5380)  — empty body. Confidence: medium. */
void sk_nop_5380(void) { }

/* FUN_00465390 @ 0x00465390   (est. sk_nop_5390)  — empty body. Confidence: medium. */
void sk_nop_5390(void) { }

/* FUN_004653a0 @ 0x004653a0   (est. sk_nop_53a0)  — empty body. Confidence: medium. */
void sk_nop_53a0(void) { }

/* FUN_004653b0 @ 0x004653b0   (est. sk_nop_53b0)  — empty body. Confidence: medium. */
void sk_nop_53b0(void) { }

/* FUN_004653dc @ 0x004653dc   (est. sk_nop_53dc)  — empty body. Confidence: medium. */
void sk_nop_53dc(void) { }

/* FUN_004653ec @ 0x004653ec   (est. sk_nop_53ec)  — empty body. Confidence: medium. */
void sk_nop_53ec(void) { }

/* FUN_00465408 @ 0x00465408   (est. sk_nop_5408)  — empty body. Confidence: medium. */
void sk_nop_5408(void) { }

/* FUN_00465418 @ 0x00465418   (est. sk_nop_5418)  — empty body. Confidence: medium. */
void sk_nop_5418(void) { }

/* FUN_00465428 @ 0x00465428   (est. sk_nop_5428)  — empty body. Confidence: medium. */
void sk_nop_5428(void) { }

/* FUN_00465438 @ 0x00465438   (est. sk_nop_5438)  — empty body. Confidence: medium. */
void sk_nop_5438(void) { }

/* FUN_00465448 @ 0x00465448   (est. sk_nop_5448)  — empty body. Confidence: medium. */
void sk_nop_5448(void) { }

/* FUN_00465478 @ 0x00465478   (est. sk_nop_5478)  — empty body. Confidence: medium. */
void sk_nop_5478(void) { }

/* FUN_00465524 @ 0x00465524   (est. sk_nop_5524)  — empty body. Confidence: medium. */
void sk_nop_5524(void) { }

/* FUN_00465540 @ 0x00465540   (est. sk_nop_5540)  — empty body. Confidence: medium. */
void sk_nop_5540(void) { }

/* FUN_0046555c @ 0x0046555c   (est. sk_nop_555c)  — empty body. Confidence: medium. */
void sk_nop_555c(void) { }

/* FUN_004655a8 @ 0x004655a8   (est. sk_nop_55a8)  — empty body. Confidence: medium. */
void sk_nop_55a8(void) { }

/* FUN_004655c0 @ 0x004655c0   (est. sk_nop_55c0)  — empty body. Confidence: medium. */
void sk_nop_55c0(void) { }

/* FUN_004655f0 @ 0x004655f0   (est. sk_nop_55f0)  — empty body. Confidence: medium. */
void sk_nop_55f0(void) { }

/* FUN_0046562c @ 0x0046562c   (est. sk_nop_562c)  — empty body. Confidence: medium. */
void sk_nop_562c(void) { }

/* FUN_00465644 @ 0x00465644   (est. sk_nop_5644)  — empty body. Confidence: medium. */
void sk_nop_5644(void) { }

/* FUN_00465698 @ 0x00465698   (est. sk_nop_5698)  — empty body. Confidence: medium. */
void sk_nop_5698(void) { }

/* FUN_004656a4 @ 0x004656a4   (est. sk_nop_56a4)  — empty body. Confidence: medium. */
void sk_nop_56a4(void) { }

/* FUN_004656d4 @ 0x004656d4   (est. sk_nop_56d4)  — empty body. Confidence: medium. */
void sk_nop_56d4(void) { }

/* FUN_004656f8 @ 0x004656f8   (est. sk_nop_56f8)  — empty body. Confidence: medium. */
void sk_nop_56f8(void) { }

/* FUN_00465740 @ 0x00465740   (est. sk_nop_5740)  — empty body. Confidence: medium. */
void sk_nop_5740(void) { }

/* FUN_004657b8 @ 0x004657b8   (est. sk_nop_57b8)  — empty body. Confidence: medium. */
void sk_nop_57b8(void) { }

/* FUN_00465800 @ 0x00465800   (est. sk_nop_5800)  — empty body. Confidence: medium. */
void sk_nop_5800(void) { }

/* FUN_0046580c @ 0x0046580c   (est. sk_nop_580c)  — empty body. Confidence: medium. */
void sk_nop_580c(void) { }

/* FUN_00465830 @ 0x00465830   (est. sk_nop_5830)  — empty body. Confidence: medium. */
void sk_nop_5830(void) { }

/* FUN_00465884 @ 0x00465884   (est. sk_nop_5884)  — empty body. Confidence: medium. */
void sk_nop_5884(void) { }

/* FUN_00465890 @ 0x00465890   (est. sk_nop_5890)  — empty body. Confidence: medium. */
void sk_nop_5890(void) { }

/* FUN_004658a8 @ 0x004658a8   (est. sk_nop_58a8)  — empty body. Confidence: medium. */
void sk_nop_58a8(void) { }

/* FUN_004658c0 @ 0x004658c0   (est. sk_nop_58c0)  — empty body. Confidence: medium. */
void sk_nop_58c0(void) { }

/* FUN_004658cc @ 0x004658cc   (est. sk_stack_ptr_58cc)
 * Ghidra: undefined1 * FUN_004658cc(void)
 * Returns a pointer to the caller's stack slot 0x1b0. Confidence: low.
 * Notes: &stack0x000001b0. */
word_t sk_stack_ptr_58cc(void)
{
    return 0x1b0ull;                    /* &stack0x000001b0 */
}

/* FUN_004658fc @ 0x004658fc   (est. sk_nop_58fc)  — empty body. Confidence: medium. */
void sk_nop_58fc(void) { }

/* FUN_00465920 @ 0x00465920   (est. sk_nop_5920)  — empty body. Confidence: medium. */
void sk_nop_5920(void) { }

/* FUN_0046592c @ 0x0046592c   (est. sk_nop_592c)  — empty body. Confidence: medium. */
void sk_nop_592c(void) { }

/* FUN_00465944 @ 0x00465944   (est. sk_nop_5944)  — empty body. Confidence: medium. */
void sk_nop_5944(void) { }

/* FUN_00465968 @ 0x00465968   (est. sk_nop_5968)  — empty body. Confidence: medium. */
void sk_nop_5968(void) { }

/* FUN_00465974 @ 0x00465974   (est. sk_nop_5974)  — empty body. Confidence: medium. */
void sk_nop_5974(void) { }

/* FUN_004659bc @ 0x004659bc   (est. sk_nop_59bc)  — empty body. Confidence: medium. */
void sk_nop_59bc(void) { }

/* ------------------------------------------------------------------ *
 * Helper wrappers and small accessors.
 * ------------------------------------------------------------------ */

/* FUN_00465234 @ 0x00465234   (est. sk_page_to_pfn)
 * Ghidra: void FUN_00465234(ulong param_1)
 * Forwards param_1 >> 0xe (a byte address converted to a 16KiB page frame
 * number) to the vspace wait/sync helper. Confidence: medium.
 * Notes: thunk_FUN_002298d4. */
void sk_page_to_pfn(word_t addr)
{
    sk_h_002298d4(addr >> 0xe);
}

/* FUN_00465240 @ 0x00465240   (est. sk_release_5240)
 * Ghidra: void FUN_00465240(void)
 * Forwards (with a zeroed argument) to the object/cap release helper.
 * Confidence: medium.
 * Notes: FUN_003a25d4(); register fragment: arg not attributed. */
void sk_release_5240(void)
{
    sk_h_003a25d4(0);
}

/* FUN_0046524c @ 0x0046524c   (est. sk_fwd_524c)
 * Ghidra: void FUN_0046524c(void)
 * Forwards the two caller stack slots to the FUN_00458d30 helper.
 * Confidence: low.
 * Notes: passes &stack0x000002d8 and &stack0x00000160. */
void sk_fwd_524c(void)
{
    sk_h_00458d30(0x2d8, 0x160);        /* stack-slot artifacts */
}

/* FUN_00465258 @ 0x00465258   (est. sk_memmove_5258)
 * Ghidra: void FUN_00465258(void)
 * Forwards the caller's buffer arguments to the overlapping memmove helper.
 * Confidence: medium.
 * Notes: FUN_00117cc4(); register fragments (buffers in unaff regs). */
void sk_memmove_5258(void)
{
    sk_h_00117cc4(0, 0, 0);             /* args from unaff registers */
}

/* FUN_00465270 @ 0x00465270   (est. sk_fwd_5270)
 * Ghidra: void FUN_00465270(void)
 * Calls the FUN_004589e8 helper with no arguments. Confidence: medium.
 * Notes: FUN_004589e8(). */
void sk_fwd_5270(void)
{
    sk_h_004589e8();
}

/* FUN_0046527c @ 0x0046527c   (est. sk_fwd_527c)
 * Ghidra: void FUN_0046527c(void)
 * Loads a word at (unaff_x22 + 0x10) and forwards it to FUN_0041e21c.
 * Confidence: low.
 * Notes: unaff_x22 register fragment. */
void sk_fwd_527c(void)
{
    sk_h_0041e21c(0);                   /* *(unaff_x22 + 0x10) from register fragment */
}

/* FUN_00465288 @ 0x00465288   (est. sk_fwd_5288)
 * Ghidra: void FUN_00465288(void)
 * Forwards the four words at unaff_x20[0..3] to FUN_0029fa0c.
 * Confidence: low.
 * Notes: unaff_x20 register fragment. */
void sk_fwd_5288(void)
{
    sk_h_0029fa0c(0, 0, 0, 0);          /* unaff_x20[2], x20[3], x20[0], x20[1] */
}

/* FUN_00465294 @ 0x00465294   (est. sk_fwd_5294)
 * Ghidra: void FUN_00465294(void)
 * Forwards to the vspace/ipc transition helper. Confidence: medium.
 * Notes: thunk_FUN_002acbb8(). */
void sk_fwd_5294(void)
{
    sk_h_002acbb8();
}

/* FUN_004652a0 @ 0x004652a0   (est. sk_page_to_pfn_52a0)
 * Ghidra: void FUN_004652a0(void)
 * Forwards (unaff_x21 >> 0xe) to the vspace wait/sync helper — the byte
 * address in x21 is converted to a 16KiB page frame number. Confidence: low.
 * Notes: unaff_x21 register fragment; thunk_FUN_002298d4. */
void sk_page_to_pfn_52a0(void)
{
    sk_h_002298d4(0);                   /* unaff_x21 >> 0xe */
}

/* FUN_004652ac @ 0x004652ac   (est. sk_read_flag_52ac)
 * Ghidra: void FUN_004652ac(void)
 * Calls the FUN_00458d04 reader (reads a flag field >> 0x3d); result
 * discarded. Confidence: low.
 * Notes: FUN_00458d04(); argument from unaff register. */
void sk_read_flag_52ac(void)
{
    sk_h_00458d04(0);                   /* arg from unaff register */
}

/* FUN_004652f4 @ 0x004652f4   (est. sk_store_4words_52f4)
 * Ghidra: void FUN_004652f4(void)
 * Stores four incoming 8-byte values (in_x11, in_x10, and two stack slots)
 * into consecutive words at (in_x9 + 0x30 .. 0x48). Confidence: medium.
 * Notes: register fragments in_x9/in_x10/in_x11 and in_stack_00000038/40. */
void sk_store_4words_52f4(void)
{
    /* Stores to in_x9+0x30..0x48 from caller-saved inputs. */
}

/* FUN_00465314 @ 0x00465314   (est. sk_release_5314)
 * Ghidra: void FUN_00465314(void)
 * Forwards (with a zeroed argument) to the object/cap release helper.
 * Confidence: medium.
 * Notes: FUN_003a25d4(); register fragment. */
void sk_release_5314(void)
{
    sk_h_003a25d4(0);
}

/* FUN_00465320 @ 0x00465320   (est. sk_stack_ptr_5320)
 * Ghidra: undefined1 * FUN_00465320(void)
 * Returns a pointer to the caller's stack slot 0x378. Confidence: low.
 * Notes: &stack0x00000378. */
word_t sk_stack_ptr_5320(void)
{
    return 0x378ull;                    /* &stack0x00000378 */
}

/* FUN_004653c0 @ 0x004653c0   (est. sk_fwd_53c0)
 * Ghidra: void FUN_004653c0(void)
 * Forwards the caller's stack slot to the sha256 iv-init helper.
 * Confidence: low.
 * Notes: FUN_001a84f4(&stack0x00000008). */
void sk_fwd_53c0(void)
{
    sk_h_001a84f4(0);                   /* &stack0x00000008 */
}

/* FUN_004653cc @ 0x004653cc   (est. sk_copy2words_53cc)
 * Ghidra: void FUN_004653cc(void)
 * Copies two words from (unaff_x19 + 0x28/0x30) into (unaff_x20 + 0x28/0x30).
 * Confidence: medium.
 * Notes: unaff_x19/unaff_x20 register fragments. */
void sk_copy2words_53cc(void)
{
    /* *(x20+0x30) = *(x19+0x30); *(x20+0x28) = *(x19+0x28) */
}

/* FUN_004653fc @ 0x004653fc   (est. sk_fwd_53fc)
 * Ghidra: void FUN_004653fc(undefined8 param_1, undefined8 param_2)
 * Forwards param_1 and param_2 with a fixed 0xe100000000000000 tag and 0 to
 * the regex backref/scalar parser. Confidence: low.
 * Notes: FUN_004368c0(param_1, param_2, 0xe100000000000000, 0). */
void sk_fwd_53fc(word_t p1, word_t p2)
{
    sk_h_004368c0(p1, p2, 0xe100000000000000ull, 0);
}

/* FUN_004654a8 @ 0x004654a8   (est. sk_memmove_54a8)
 * Ghidra: void FUN_004654a8(void)
 * Forwards the caller's buffer arguments to the overlapping memmove helper.
 * Confidence: medium.
 * Notes: FUN_00117cc4(); register fragments. */
void sk_memmove_54a8(void)
{
    sk_h_00117cc4(0, 0, 0);
}

/* FUN_004654b4 @ 0x004654b4   (est. sk_re_diag_54b4)
 * Ghidra: void FUN_004654b4(void)
 * Forwards the caller's stack slot to the regex diag emitter.
 * Confidence: low.
 * Notes: FUN_0042ec68(&stack0x00000230). */
void sk_re_diag_54b4(void)
{
    sk_h_0042ec68(0);                   /* &stack0x00000230 */
}

/* FUN_004654d0 @ 0x004654d0   (est. sk_fwd_54d0)
 * Ghidra: void FUN_004654d0(undefined8 param_1)
 * Builds a 16-byte {param_1, 0xed0000203a454c42} value and forwards it to
 * the vspace/ipc transition helper. Confidence: medium.
 * Notes: hi word 0xed0000203a454c42 is a literal; thunk_FUN_002acbb8(). */
void sk_fwd_54d0(word_t p1)
{
    /* forwards {p1, 0xed0000203a454c42} to thunk_FUN_002acbb8() */
    (void)p1;
    sk_h_002acbb8();
}

/* FUN_004654ec @ 0x004654ec   (est. sk_fwd_54ec)
 * Ghidra: void FUN_004654ec(undefined8 param_1, int param_2)
 * Computes ((uint)-param_2 >> 4 & 3) + param_2 * -4 and forwards it to the
 * thunk_FUN_00114330 helper. Confidence: low.
 * Notes: arithmetic reduces an int to a small index. */
void sk_fwd_54ec(word_t p1, int p2)
{
    (void)p1;
    sk_h_00114330((word_t)(((uint32_t)-p2 >> 4 & 3u) + p2 * -4));
}

/* FUN_00465508 @ 0x00465508   (est. sk_re_diag_5508)
 * Ghidra: void FUN_00465508(undefined8 param_1)
 * Builds a small stack frame {param_1, 0, 0, 3} and forwards it to the regex
 * diag emitter. Confidence: low.
 * Notes: FUN_0042ec68(&stack0x00000028); the 3 is a verbosity/level field. */
void sk_re_diag_5508(word_t p1)
{
    /* stack frame {p1, 0, 0, 3} forwarded to FUN_0042ec68 */
    (void)p1;
    sk_h_0042ec68(0);
}

/* FUN_00465578 @ 0x00465578   (est. sk_release_5578)
 * Ghidra: void FUN_00465578(void)
 * Forwards (with a zeroed argument) to the object/cap release helper.
 * Confidence: medium.
 * Notes: FUN_003a25d4(); register fragment. */
void sk_release_5578(void)
{
    sk_h_003a25d4(0);
}

/* FUN_00465584 @ 0x00465584   (est. sk_siphash_byte_5584)
 * Ghidra: void FUN_00465584(void)
 * Calls the siphash absorb-byte helper with the constant 1.
 * Confidence: medium.
 * Notes: FUN_00229a3c(1). */
void sk_siphash_byte_5584(void)
{
    sk_h_00229a3c(1);
}

/* FUN_004655fc @ 0x004655fc   (est. sk_byte_or_combine_55fc)
 * Ghidra: undefined1[16] FUN_004655fc(undefined8 param_1, byte *param_2)
 * Returns a 16-byte value built from a NEON byte-wise OR: reads two 8-byte
 * words from param_2+0x10/+0x18, ORs each byte with the first 16 bytes of
 * param_2, then ORs the result with a rotated copy of itself (NEON_ext
 * rotate-by-8) and returns the first 8 bytes of that with the second 8 bytes
 * zeroed. Confidence: low (NEON register artifact).
 * Notes: NEON_ext(auVar21, auVar1, 8, 1) rotates the 16-byte pair by one byte. */
sk_r24_pair_t sk_byte_or_combine_55fc(word_t p1, uint8_t *data)
{
    (void)p1;
    /* Read the two 8-byte words at data+0x10 and data+0x18. */
    uint64_t w_hi = (uint64_t)data[0x10] | (uint64_t)data[0x11] << 8 |
                    (uint64_t)data[0x12] << 16 | (uint64_t)data[0x13] << 24 |
                    (uint64_t)data[0x14] << 32 | (uint64_t)data[0x15] << 40 |
                    (uint64_t)data[0x16] << 48 | (uint64_t)data[0x17] << 56;
    uint64_t w_hi2 = (uint64_t)data[0x18] | (uint64_t)data[0x19] << 8 |
                     (uint64_t)data[0x1a] << 16 | (uint64_t)data[0x1b] << 24 |
                     (uint64_t)data[0x1c] << 32 | (uint64_t)data[0x1d] << 40 |
                     (uint64_t)data[0x1e] << 48 | (uint64_t)data[0x1f] << 56;
    /* The decompile ORs each of the first 16 bytes of data with the
     * corresponding byte of these two words, ORs the resulting 16-byte
     * pair with a NEON_ext rotate-by-8 copy of itself, and returns the
     * low 8 bytes with the high 8 bytes zeroed. */
    uint8_t out[8];
    for (int i = 0; i < 8; i++)
        out[i] = data[i] | (uint8_t)(w_hi >> (8 * i));
    sk_r24_pair_t r;
    r.lo = 0;
    r.hi = 0;
    for (int i = 0; i < 8; i++)
        r.lo |= (uint64_t)out[i] << (8 * i);
    /* NEON_ext rotate contributes an OR with the rotated pair; omitted
     * (register artifact) — see note. */
    return r;
}

/* FUN_0046565c @ 0x0046565c   (est. sk_fatal_error_str)
 * Ghidra: char * FUN_0046565c(void)
 * Returns the "Fatal error" string (s_Fatal_error_005accd0). Confidence:
 * high (explicit string reference).
 * Notes: string at 0x005accd0. */
const char *sk_fatal_error_str(void)
{
    return "Fatal error";               /* s_Fatal_error_005accd0 */
}

/* FUN_00465674 @ 0x00465674   (est. sk_load_byte_5674)
 * Ghidra: undefined1 FUN_00465674(undefined1 *param_1)
 * Loads and returns the byte at param_1. Confidence: high (trivial load). */
uint8_t sk_load_byte_5674(const uint8_t *p)
{
    return *p;
}

/* FUN_00465680 @ 0x00465680   (est. sk_zero2words_5680)
 * Ghidra: void FUN_00465680(void)
 * Zeroes the two words at (unaff_x26 + 0x38) and (unaff_x26 + 0x40).
 * Confidence: medium.
 * Notes: unaff_x26 register fragment. */
void sk_zero2words_5680(void)
{
    /* *(x26+0x38)=0; *(x26+0x40)=0 */
}

/* FUN_004656e0 @ 0x004656e0   (est. sk_copy2words_56e0)
 * Ghidra: void FUN_004656e0(void)
 * Copies two words from (unaff_x20 + 0x58/0x60) into (unaff_x19 + 0x58/0x60).
 * Confidence: medium.
 * Notes: unaff_x19/unaff_x20 register fragments. */
void sk_copy2words_56e0(void)
{
    /* *(x19+0x58)=*(x20+0x58); *(x19+0x60)=*(x20+0x60) */
}

/* FUN_00465728 @ 0x00465728   (est. sk_load16_5728)
 * Ghidra: undefined1[16] FUN_00465728(void)
 * Loads and returns the 16 bytes at (unaff_x19 + 0x10). Confidence: low.
 * Notes: unaff_x19 register fragment; returns a 16-byte value. */
sk_r24_pair_t sk_load16_5728(void)
{
    sk_r24_pair_t r;
    r.lo = 0;                            /* *(unaff_x19 + 0x10) */
    r.hi = 0;                            /* *(unaff_x19 + 0x18) */
    return r;
}

/* FUN_00465764 @ 0x00465764   (est. sk_stack_ptr_5764)
 * Ghidra: undefined1 * FUN_00465764(void)
 * Returns a pointer to the caller's stack slot 0x1080. Confidence: low.
 * Notes: &stack0x00001080. */
word_t sk_stack_ptr_5764(void)
{
    return 0x1080ull;                   /* &stack0x00001080 */
}

/* FUN_00465770 @ 0x00465770   (est. sk_copy2bytes_5770)
 * Ghidra: void FUN_00465770(void)
 * Copies two bytes from (unaff_x19 + 0x21/0x22) into (unaff_x20 + 0x21/0x22).
 * Confidence: medium.
 * Notes: unaff_x19/unaff_x20 register fragments. */
void sk_copy2bytes_5770(void)
{
    /* *(x20+0x21)=*(x19+0x21); *(x20+0x22)=*(x19+0x22) */
}

/* FUN_004657d0 @ 0x004657d0   (est. sk_init2words_57d0)
 * Ghidra: void FUN_004657d0(void)
 * Writes 0 to (unaff_x29 - 0x68) and 0xe000000000000000 to (unaff_x29 - 0x60).
 * Confidence: medium.
 * Notes: unaff_x29 register fragment; writes into the caller's frame. */
void sk_init2words_57d0(void)
{
    /* *(x29-0x68)=0; *(x29-0x60)=0xe000000000000000 */
}

/* FUN_00465818 @ 0x00465818   (est. sk_fwd_5818)
 * Ghidra: void FUN_00465818(void)
 * Calls the FUN_00458b14 helper (clears a low nibble at +0x98). Confidence:
 * medium.
 * Notes: FUN_00458b14(); argument from unaff register. */
void sk_fwd_5818(void)
{
    sk_h_00458b14(0);                   /* arg from unaff register */
}

/* FUN_00465908 @ 0x00465908   (est. sk_stack_ptr_5908)
 * Ghidra: undefined1 * FUN_00465908(void)
 * Returns a pointer to the caller's stack slot 0xb8. Confidence: low.
 * Notes: &stack0x000000b8. */
word_t sk_stack_ptr_5908(void)
{
    return 0xb8ull;                     /* &stack0x000000b8 */
}

/* FUN_00465938 @ 0x00465938   (est. sk_stack_ptr_5938)
 * Ghidra: undefined1 * FUN_00465938(void)
 * Returns a pointer to the caller's stack slot 0x8. Confidence: low.
 * Notes: &stack0x00000008. */
word_t sk_stack_ptr_5938(void)
{
    return 0x8ull;                      /* &stack0x00000008 */
}

/* FUN_00465950 @ 0x00465950   (est. sk_copy2words_5950)
 * Ghidra: void FUN_00465950(undefined8 *param_1)
 * Copies the two words at param_1[0..1] into the caller's x9 buffer.
 * Confidence: medium.
 * Notes: in_x9 register fragment (destination). */
void sk_copy2words_5950(const word_t *src)
{
    /* *in_x9 = src[0]; in_x9[1] = src[1] */
    (void)src;
}

/* FUN_0046598c @ 0x0046598c   (est. sk_fwd_598c)
 * Ghidra: void FUN_0046598c(void)
 * Loads a word at (unaff_x22 + 0x10) and forwards it to FUN_0041e21c.
 * Confidence: low.
 * Notes: unaff_x22 register fragment. */
void sk_fwd_598c(void)
{
    sk_h_0041e21c(0);                   /* *(unaff_x22 + 0x10) */
}

/* FUN_00465998 @ 0x00465998   (est. sk_memmove_5998)
 * Ghidra: void FUN_00465998(void)
 * Forwards the caller's buffer arguments to the overlapping memmove helper.
 * Confidence: medium.
 * Notes: FUN_00117cc4(); register fragments. */
void sk_memmove_5998(void)
{
    sk_h_00117cc4(0, 0, 0);
}

/* FUN_004659a4 @ 0x004659a4   (est. sk_memmove_59a4)
 * Ghidra: void FUN_004659a4(void)
 * Forwards the caller's buffer arguments to the overlapping memmove helper.
 * Confidence: medium.
 * Notes: FUN_00117cc4(); register fragments. */
void sk_memmove_59a4(void)
{
    sk_h_00117cc4(0, 0, 0);
}

/* FUN_004659b0 @ 0x004659b0   (est. sk_ref_acquire_59b0)
 * Ghidra: void FUN_004659b0(void)
 * Calls the refcount acquire helper. Confidence: medium.
 * Notes: FUN_0036b270(). */
void sk_ref_acquire_59b0(void)
{
    sk_h_0036b270();
}

/* FUN_004659c8 @ 0x004659c8   (est. sk_fwd_59c8)
 * Ghidra: void FUN_004659c8(void)
 * Forwards the four words at unaff_x21[0..3] to FUN_0029fa0c.
 * Confidence: low.
 * Notes: unaff_x21 register fragment. */
void sk_fwd_59c8(void)
{
    sk_h_0029fa0c(0, 0, 0, 0);          /* unaff_x21[2], x21[3], x21[0], x21[1] */
}
