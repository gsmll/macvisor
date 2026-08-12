/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel, GL1,
 * arm64e, image base 0) — the cL4 microkernel. Ground truth: Ghidra FUN_ names +
 * addresses in the cl4_kernel.raw program. Names use seL4/cL4 vocabulary; all
 * are estimates unless string/header matched.
 *
 * Slice 0x0046493c-0x004651d4 (worker SKR23): a block of small constant-returning
 * helpers that produce Swift-style tagged string descriptors — a Unicode script
 * name table (Telugu, Thaana, Brahmi, Yezidi, Chakma, Tai_Le, Kaithi, Lepcha,
 * Syriac, Hebrew, Rejang, Khojki, Lao, Batak, Runic, Takri, Tamil, Khmer, Osage,
 * Buhid, Bassa Vah, Cuneiform, Sundanese, Palmyrene, Medefaidrin, Malayalam,
 * Old Hungarian, Mende Kikakui, Thai, ...) plus a few error-message descriptors
 * ("<invalid", "character '", " digits ", "( *", "(?") and thin forwarders into
 * the memory-copy / object-retain helpers. Each 16-byte result is a pair whose
 * low word holds the ASCII payload and whose high word carries a small-string
 * tag (0xe1/0xe2/0xe3/0xe6/0xec ...); single-word results are 8-byte constants.
 */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "sk_internal.h"

/* 16-byte result pair (lo = x0, hi = x1) used by the string-descriptor helpers. */
typedef struct sk_w16 { uint64_t lo; uint64_t hi; } sk_w16_t;

/* ------------------------------------------------------------------ *
 * Out-of-slice callees (reconstructed by other slice workers).
 * ------------------------------------------------------------------ */
extern unsigned long sk_x_00117cc4(void *dst, const void *src, unsigned long n); /* FUN_00117cc4 (memcpy) */
extern void          sk_x_0036b270(unsigned long v);    /* FUN_0036b270 (retain) */
extern void          sk_x_003a25d4(unsigned long v);    /* FUN_003a25d4 */
extern void          sk_x_002a4ab4(unsigned long v);    /* FUN_002a4ab4 */
extern void          sk_x_002298d4(unsigned long v);    /* thunk_FUN_002298d4 */
extern void          sk_x_0045636c(unsigned long a, unsigned long b, unsigned long c); /* FUN_0045636c */
extern void          sk_x_00458b14(void);               /* FUN_00458b14 */
extern void          sk_x_0042f584(unsigned long a, unsigned long b); /* FUN_0042f584 */
extern void          sk_x_0045a4b4(void);               /* FUN_0045a4b4 */
extern void          sk_x_004614cc(void);               /* FUN_004614cc */
extern void          sk_x_0029fa0c(unsigned long a, unsigned long b,
                                   unsigned long c, unsigned long d); /* FUN_0029fa0c */
extern void          sk_x_0044b000(void);               /* FUN_0044b000 */
extern void          sk_x_0042ec68(unsigned long a);    /* FUN_0042ec68 */
extern void          sk_x_0006a374(unsigned long a);    /* FUN_0006a374 */

/* ------------------------------------------------------------------ *
 * Script-name string descriptors (return an 8-byte ASCII payload word).
 * ------------------------------------------------------------------ */

/* FUN_0046493c @ 0x0046493c   (est. sk_script_word_46493c)
 * Ghidra: undefined8 FUN_0046493c(void)
 * Returns the 8-byte little-endian ASCII payload "othe" (a script-name
 * fragment; possibly the leading bytes of "Other"/"Othe...").
 * Confidence: low
 * Notes: constant 0x6568746f = bytes 6f 74 68 65 = "othe". */
static uint64_t sk_script_word_46493c(void)
{
    return 0x6568746fULL;   /* "othe" */
}

/* FUN_00464948 @ 0x00464948   (est. sk_nop_464948)
 * Ghidra: void FUN_00464948(void)
 * Empty placeholder: returns immediately with no effect.
 * Confidence: medium
 * Notes: empty body. */
static void sk_nop_464948(void)
{
}

/* FUN_00464954 @ 0x00464954   (est. sk_load_field_10_464954)
 * Ghidra: undefined8 FUN_00464954(long param_1)
 * Loads and returns the 8-byte word at offset 0x10 of the given object.
 * Confidence: medium
 * Notes: simple field load. */
static uint64_t sk_load_field_10_464954(uint64_t obj)
{
    return *(uint64_t *)(obj + 0x10);
}

/* FUN_00464978 @ 0x00464978   (est. sk_script_word_464978)
 * Ghidra: undefined8 FUN_00464978(void)
 * Returns the 8-byte little-endian ASCII payload "nandinag" (a script-name
 * fragment).
 * Confidence: low
 * Notes: constant 0x67616e69646e616e = bytes 6e 61 6e 64 69 6e 61 67. */
static uint64_t sk_script_word_464978(void)
{
    return 0x67616e69646e616eULL;   /* "nandinag" */
}

/* FUN_0046499c @ 0x0046499c   (est. sk_script_mende_kikakui)
 * Ghidra: undefined1 [16] FUN_0046499c(void)
 * Returns the 16-byte tagged descriptor for the script name "Mende Kikakui":
 * low word "mendekik" (0x6b696b65646e656d), high word "akui" with tag 0xec.
 * Confidence: low
 * Notes: tag 0xec is a small-string discriminator; payload "mendekikakui". */
static sk_w16_t sk_script_mende_kikakui(void)
{
    sk_w16_t r;
    r.lo = 0x6b696b65646e656dULL;      /* "mendekik" */
    r.hi = 0xec00000069756b61ULL;      /* "akui" + tag 0xec */
    return r;
}

/* FUN_004649c0 @ 0x004649c0   (est. sk_nop_4649c0)
 * Ghidra: void FUN_004649c0(void)
 * Empty placeholder: returns immediately with no effect.
 * Confidence: medium
 * Notes: empty body. */
static void sk_nop_4649c0(void)
{
}

/* FUN_004649cc @ 0x004649cc   (est. sk_dot_desc)
 * Ghidra: undefined1 [16] FUN_004649cc(void)
 * Returns the 16-byte tagged descriptor for the single character "." :
 * low word 0x2e ('.'), high word 0xe1 tag.
 * Confidence: low
 * Notes: tag 0xe1; payload "." */
static sk_w16_t sk_dot_desc(void)
{
    sk_w16_t r;
    r.lo = 0x2eULL;                    /* "." */
    r.hi = 0xe100000000000000ULL;      /* tag 0xe1 */
    return r;
}

/* FUN_004649d8 @ 0x004649d8   (est. sk_script_old_hungarian)
 * Ghidra: undefined1 [16] FUN_004649d8(void)
 * Returns the 16-byte tagged descriptor for the script name "Old Hungarian":
 * low word "oldhunga" (0x61676e7568646c6f), high word "rian" + tag 0xec.
 * Confidence: low
 * Notes: tag 0xec; payload "oldhungarian". */
static sk_w16_t sk_script_old_hungarian(void)
{
    sk_w16_t r;
    r.lo = 0x61676e7568646c6fULL;      /* "oldhunga" */
    r.hi = 0xec0000006e616972ULL;      /* "rian" + tag 0xec */
    return r;
}

/* FUN_004649fc @ 0x004649fc   (est. sk_nop_4649fc)
 * Ghidra: void FUN_004649fc(void)
 * Empty placeholder: returns immediately with no effect.
 * Confidence: medium
 * Notes: empty body. */
static void sk_nop_4649fc(void)
{
}

/* FUN_00464a08 @ 0x00464a08   (est. sk_return_zero_464a08)
 * Ghidra: undefined8 FUN_00464a08(void)
 * Returns the constant 0.
 * Confidence: medium
 * Notes: literal 0. */
static uint64_t sk_return_zero_464a08(void)
{
    return 0;
}

/* FUN_00464a14 @ 0x00464a14   (est. sk_nop_464a14)
 * Ghidra: void FUN_00464a14(void)
 * Empty placeholder: returns immediately with no effect.
 * Confidence: medium
 * Notes: empty body. */
static void sk_nop_464a14(void)
{
}

/* FUN_00464a38 @ 0x00464a38   (est. sk_nop_464a38)
 * Ghidra: void FUN_00464a38(void)
 * Empty placeholder: returns immediately with no effect.
 * Confidence: medium
 * Notes: empty body. */
static void sk_nop_464a38(void)
{
}

/* FUN_00464a44 @ 0x00464a44   (est. sk_nop_464a44)
 * Ghidra: void FUN_00464a44(void)
 * Empty placeholder: returns immediately with no effect.
 * Confidence: medium
 * Notes: empty body. */
static void sk_nop_464a44(void)
{
}

/* FUN_00464a50 @ 0x00464a50   (est. sk_copy_struct_464a50)
 * Ghidra: void FUN_00464a50(long param_1,long param_2)
 * Copies a small struct from src to dst: byte at +8, word at +0x10, byte at
 * +0x18, word at +0x28, word at +0x20. The +0x20/+0x28 words are copied as a
 * pair (high at +0x20 read first into a temp, then both stored).
 * Confidence: medium
 * Notes: field offsets faithful to decompile. */
static void sk_copy_struct_464a50(uint64_t dst, uint64_t src)
{
    uint64_t tmp;

    *(unsigned char *)(dst + 0x08) = *(unsigned char *)(src + 0x08);
    *(uint64_t *)(dst + 0x10)      = *(uint64_t *)(src + 0x10);
    *(unsigned char *)(dst + 0x18) = *(unsigned char *)(src + 0x18);
    tmp = *(uint64_t *)(src + 0x20);
    *(uint64_t *)(dst + 0x28)      = *(uint64_t *)(src + 0x28);
    *(uint64_t *)(dst + 0x20)      = tmp;
}

/* FUN_00464a74 @ 0x00464a74   (est. sk_nop_464a74)
 * Ghidra: void FUN_00464a74(void)
 * Empty placeholder: returns immediately with no effect.
 * Confidence: medium
 * Notes: empty body. */
static void sk_nop_464a74(void)
{
}

/* FUN_00464a80 @ 0x00464a80   (est. sk_nop_464a80)
 * Ghidra: void FUN_00464a80(void)
 * Empty placeholder: returns immediately with no effect.
 * Confidence: medium
 * Notes: empty body. */
static void sk_nop_464a80(void)
{
}

/* FUN_00464a8c @ 0x00464a8c   (est. sk_desc_paren_star)
 * Ghidra: undefined1 [16] FUN_00464a8c(void)
 * Returns the 16-byte tagged descriptor for the operator string "( *":
 * low word 0x2a28 = bytes 28 2a = "(*", high word tag 0xe2.
 * Confidence: low
 * Notes: tag 0xe2; payload "(*". */
static sk_w16_t sk_desc_paren_star(void)
{
    sk_w16_t r;
    r.lo = 0x2a28ULL;                  /* "(*" */
    r.hi = 0xe200000000000000ULL;      /* tag 0xe2 */
    return r;
}

/* FUN_00464a98 @ 0x00464a98   (est. sk_desc_invalid)
 * Ghidra: undefined8 FUN_00464a98(void)
 * Returns the 8-byte little-endian ASCII payload "<invalid".
 * Confidence: low
 * Notes: constant 0x64696c61766e693c = bytes 3c 69 6e 76 61 6c 69 64. */
static uint64_t sk_desc_invalid(void)
{
    return 0x64696c61766e693cULL;      /* "<invalid" */
}

/* FUN_00464aac @ 0x00464aac   (est. sk_frame_addr_464aac)
 * Ghidra: long FUN_00464aac(void)
 * Returns the caller's frame pointer minus 0x80 (an address into the caller's
 * stack frame). Represented via the builtin frame address; the decompiler
 * reported the fragment as unaff_x29.
 * Confidence: low
 * Notes: register fragment (unaff_x29); offset -0x80. */
static uint64_t sk_frame_addr_464aac(void)
{
    return (uint64_t)__builtin_frame_address(0) - 0x80;
}

/* FUN_00464ab8 @ 0x00464ab8   (est. sk_desc_paren_q)
 * Ghidra: undefined1 [16] FUN_00464ab8(void)
 * Returns the 16-byte tagged descriptor for the operator string "(?":
 * low word 0x3f28 = bytes 28 3f = "(?", high word tag 0xe2.
 * Confidence: low
 * Notes: tag 0xe2; payload "(?". */
static sk_w16_t sk_desc_paren_q(void)
{
    sk_w16_t r;
    r.lo = 0x3f28ULL;                  /* "(?" */
    r.hi = 0xe200000000000000ULL;      /* tag 0xe2 */
    return r;
}

/* FUN_00464ac4 @ 0x00464ac4   (est. sk_return_zero_464ac4)
 * Ghidra: undefined8 FUN_00464ac4(void)
 * Returns the constant 0.
 * Confidence: medium
 * Notes: literal 0. */
static uint64_t sk_return_zero_464ac4(void)
{
    return 0;
}

/* FUN_00464ad0 @ 0x00464ad0   (est. sk_nop_464ad0)
 * Ghidra: void FUN_00464ad0(void)
 * Empty placeholder: returns immediately with no effect.
 * Confidence: medium
 * Notes: empty body. */
static void sk_nop_464ad0(void)
{
}

/* FUN_00464adc @ 0x00464adc   (est. sk_memcpy_fwd_464adc)
 * Ghidra: void FUN_00464adc(void)
 * Forwards to the shared memory-copy helper FUN_00117cc4 (register pass-through;
 * the destination/source/length are carried in registers to the callee).
 * Confidence: low
 * Notes: tail-forward to FUN_00117cc4. */
static void sk_memcpy_fwd_464adc(void)
{
    sk_x_00117cc4(0, 0, 0);
}

/* FUN_00464ae8 @ 0x00464ae8   (est. sk_nop_464ae8)
 * Ghidra: void FUN_00464ae8(void)
 * Empty placeholder: returns immediately with no effect.
 * Confidence: medium
 * Notes: empty body. */
static void sk_nop_464ae8(void)
{
}

/* FUN_00464b04 @ 0x00464b04   (est. sk_nop_464b04)
 * Ghidra: void FUN_00464b04(void)
 * Empty placeholder: returns immediately with no effect.
 * Confidence: medium
 * Notes: empty body. */
static void sk_nop_464b04(void)
{
}

/* FUN_00464b20 @ 0x00464b20   (est. sk_memcpy_fwd_464b20)
 * Ghidra: void FUN_00464b20(void)
 * Forwards to the shared memory-copy helper FUN_00117cc4 (register pass-through).
 * Confidence: low
 * Notes: tail-forward to FUN_00117cc4. */
static void sk_memcpy_fwd_464b20(void)
{
    sk_x_00117cc4(0, 0, 0);
}

/* FUN_00464b40 @ 0x00464b40   (est. sk_script_bassa_vah)
 * Ghidra: undefined8 FUN_00464b40(void)
 * Returns the 8-byte little-endian ASCII payload "Bassa_Va" (Bassa Vah script).
 * Confidence: low
 * Notes: constant 0x61565f6173736142 = bytes 42 61 73 73 5f 56 61. */
static uint64_t sk_script_bassa_vah(void)
{
    return 0x61565f6173736142ULL;      /* "Bassa_Va" */
}

/* FUN_00464b54 @ 0x00464b54   (est. sk_script_cuneiform)
 * Ghidra: undefined8 FUN_00464b54(void)
 * Returns the 8-byte little-endian ASCII payload "Cuneifor" (Cuneiform script).
 * Confidence: low
 * Notes: constant 0x726f6669656e7543 = bytes 43 75 6e 65 69 66 6f 72. */
static uint64_t sk_script_cuneiform(void)
{
    return 0x726f6669656e7543ULL;      /* "Cuneifor" */
}

/* FUN_00464b68 @ 0x00464b68   (est. sk_script_sundanese)
 * Ghidra: undefined8 FUN_00464b68(void)
 * Returns the 8-byte little-endian ASCII payload "Sundanes" (Sundanese script).
 * Confidence: low
 * Notes: constant 0x73656e61646e7553 = bytes 53 75 6e 64 61 6e 65 73. */
static uint64_t sk_script_sundanese(void)
{
    return 0x73656e61646e7553ULL;      /* "Sundanes" */
}

/* FUN_00464b7c @ 0x00464b7c   (est. sk_script_palmyrene)
 * Ghidra: undefined8 FUN_00464b7c(void)
 * Returns the 8-byte little-endian ASCII payload "Palmyren" (Palmyrene script).
 * Confidence: low
 * Notes: constant 0x6e6572796d6c6150 = bytes 50 61 6c 6d 79 72 65 6e. */
static uint64_t sk_script_palmyrene(void)
{
    return 0x6e6572796d6c6150ULL;      /* "Palmyren" */
}

/* FUN_00464b90 @ 0x00464b90   (est. sk_script_medefaidrin)
 * Ghidra: undefined8 FUN_00464b90(void)
 * Returns the 8-byte little-endian ASCII payload "Medefaid" (Medefaidrin script).
 * Confidence: low
 * Notes: constant 0x646961666564654d = bytes 4d 65 64 65 66 61 69 64. */
static uint64_t sk_script_medefaidrin(void)
{
    return 0x646961666564654dULL;      /* "Medefaid" */
}

/* FUN_00464ba4 @ 0x00464ba4   (est. sk_script_malayalam)
 * Ghidra: undefined8 FUN_00464ba4(void)
 * Returns the 8-byte little-endian ASCII payload "Malayala" (Malayalam script).
 * Confidence: low
 * Notes: constant 0x616c6179616c614d = bytes 4d 61 6c 61 79 61 6c 61. */
static uint64_t sk_script_malayalam(void)
{
    return 0x616c6179616c614dULL;      /* "Malayala" */
}

/* FUN_00464bb8 @ 0x00464bb8   (est. sk_desc_build_retain_464bb8)
 * Ghidra: void FUN_00464bb8(void)
 * Builds a 16-byte descriptor on the stack — low word is x23&0xffffffffffff
 * (or bits 56-59 of x21 when bit 0x2000000000000000 is set), high word 0xe0
 * tag — then forwards it to the retain helper FUN_0036b270.
 * Confidence: low
 * Notes: register fragments (unaff_x21/unaff_x23); calls thunk_FUN_0036b270. */
static void sk_desc_build_retain_464bb8(void)
{
    uint64_t lo, hi;

    lo = 0;
    hi = 0xe000000000000000ULL;        /* tag 0xe0 */
    /* lo below is assembled from unaff_x23/unaff_x21 register fragments. */
    (void)lo; (void)hi;
    sk_x_0036b270(0);
}

/* FUN_00464bf4 @ 0x00464bf4   (est. sk_script_telugu)
 * Ghidra: undefined1 [16] FUN_00464bf4(void)
 * Returns the 16-byte tagged descriptor for the script name "Telugu":
 * low word 0x7567756c6554 = "Telugu", high word tag 0xe6.
 * Confidence: low
 * Notes: tag 0xe6. */
static sk_w16_t sk_script_telugu(void)
{
    sk_w16_t r;
    r.lo = 0x7567756c6554ULL;          /* "Telugu" */
    r.hi = 0xe600000000000000ULL;      /* tag 0xe6 */
    return r;
}

/* FUN_00464c08 @ 0x00464c08   (est. sk_script_thaana)
 * Ghidra: undefined1 [16] FUN_00464c08(void)
 * Returns the 16-byte tagged descriptor for the script name "Thaana":
 * low word 0x616e61616854 = "Thaana", high word tag 0xe6.
 * Confidence: low
 * Notes: tag 0xe6. */
static sk_w16_t sk_script_thaana(void)
{
    sk_w16_t r;
    r.lo = 0x616e61616854ULL;          /* "Thaana" */
    r.hi = 0xe600000000000000ULL;      /* tag 0xe6 */
    return r;
}

/* FUN_00464c1c @ 0x00464c1c   (est. sk_script_brahmi)
 * Ghidra: undefined1 [16] FUN_00464c1c(void)
 * Returns the 16-byte tagged descriptor for the script name "Brahmi":
 * low word 0x696d68617242 = "Brahmi", high word tag 0xe6.
 * Confidence: low
 * Notes: tag 0xe6. */
static sk_w16_t sk_script_brahmi(void)
{
    sk_w16_t r;
    r.lo = 0x696d68617242ULL;          /* "Brahmi" */
    r.hi = 0xe600000000000000ULL;      /* tag 0xe6 */
    return r;
}

/* FUN_00464c30 @ 0x00464c30   (est. sk_script_yezidi)
 * Ghidra: undefined1 [16] FUN_00464c30(void)
 * Returns the 16-byte tagged descriptor for the script name "Yezidi":
 * low word 0x6964697a6559 = "Yezidi", high word tag 0xe6.
 * Confidence: low
 * Notes: tag 0xe6. */
static sk_w16_t sk_script_yezidi(void)
{
    sk_w16_t r;
    r.lo = 0x6964697a6559ULL;          /* "Yezidi" */
    r.hi = 0xe600000000000000ULL;      /* tag 0xe6 */
    return r;
}

/* FUN_00464c44 @ 0x00464c44   (est. sk_script_chakma)
 * Ghidra: undefined1 [16] FUN_00464c44(void)
 * Returns the 16-byte tagged descriptor for the script name "Chakma":
 * low word 0x616d6b616843 = "Chakma", high word tag 0xe6.
 * Confidence: low
 * Notes: tag 0xe6. */
static sk_w16_t sk_script_chakma(void)
{
    sk_w16_t r;
    r.lo = 0x616d6b616843ULL;          /* "Chakma" */
    r.hi = 0xe600000000000000ULL;      /* tag 0xe6 */
    return r;
}

/* FUN_00464c58 @ 0x00464c58   (est. sk_script_tai_le)
 * Ghidra: undefined1 [16] FUN_00464c58(void)
 * Returns the 16-byte tagged descriptor for the script name "Tai_Le":
 * low word 0x654c5f696154 = "Tai_Le", high word tag 0xe6.
 * Confidence: low
 * Notes: tag 0xe6. */
static sk_w16_t sk_script_tai_le(void)
{
    sk_w16_t r;
    r.lo = 0x654c5f696154ULL;          /* "Tai_Le" */
    r.hi = 0xe600000000000000ULL;      /* tag 0xe6 */
    return r;
}

/* FUN_00464c6c @ 0x00464c6c   (est. sk_script_kaithi)
 * Ghidra: undefined1 [16] FUN_00464c6c(void)
 * Returns the 16-byte tagged descriptor for the script name "Kaithi":
 * low word 0x69687469614b = "Kaithi", high word tag 0xe6.
 * Confidence: low
 * Notes: tag 0xe6. */
static sk_w16_t sk_script_kaithi(void)
{
    sk_w16_t r;
    r.lo = 0x69687469614bULL;          /* "Kaithi" */
    r.hi = 0xe600000000000000ULL;      /* tag 0xe6 */
    return r;
}

/* FUN_00464c80 @ 0x00464c80   (est. sk_script_lepcha)
 * Ghidra: undefined1 [16] FUN_00464c80(void)
 * Returns the 16-byte tagged descriptor for the script name "Lepcha":
 * low word 0x61686370654c = "Lepcha", high word tag 0xe6.
 * Confidence: low
 * Notes: tag 0xe6. */
static sk_w16_t sk_script_lepcha(void)
{
    sk_w16_t r;
    r.lo = 0x61686370654cULL;          /* "Lepcha" */
    r.hi = 0xe600000000000000ULL;      /* tag 0xe6 */
    return r;
}

/* FUN_00464c94 @ 0x00464c94   (est. sk_script_syriac)
 * Ghidra: undefined1 [16] FUN_00464c94(void)
 * Returns the 16-byte tagged descriptor for the script name "Syriac":
 * low word 0x636169727953 = "Syriac", high word tag 0xe6.
 * Confidence: low
 * Notes: tag 0xe6. */
static sk_w16_t sk_script_syriac(void)
{
    sk_w16_t r;
    r.lo = 0x636169727953ULL;          /* "Syriac" */
    r.hi = 0xe600000000000000ULL;      /* tag 0xe6 */
    return r;
}

/* FUN_00464ca8 @ 0x00464ca8   (est. sk_script_hebrew)
 * Ghidra: undefined1 [16] FUN_00464ca8(void)
 * Returns the 16-byte tagged descriptor for the script name "Hebrew":
 * low word 0x776572626548 = "Hebrew", high word tag 0xe6.
 * Confidence: low
 * Notes: tag 0xe6. */
static sk_w16_t sk_script_hebrew(void)
{
    sk_w16_t r;
    r.lo = 0x776572626548ULL;          /* "Hebrew" */
    r.hi = 0xe600000000000000ULL;      /* tag 0xe6 */
    return r;
}

/* FUN_00464cbc @ 0x00464cbc   (est. sk_script_rejang)
 * Ghidra: undefined1 [16] FUN_00464cbc(void)
 * Returns the 16-byte tagged descriptor for the script name "Rejang":
 * low word 0x676e616a6552 = "Rejang", high word tag 0xe6.
 * Confidence: low
 * Notes: tag 0xe6. */
static sk_w16_t sk_script_rejang(void)
{
    sk_w16_t r;
    r.lo = 0x676e616a6552ULL;          /* "Rejang" */
    r.hi = 0xe600000000000000ULL;      /* tag 0xe6 */
    return r;
}

/* FUN_00464cd0 @ 0x00464cd0   (est. sk_script_khojki)
 * Ghidra: undefined1 [16] FUN_00464cd0(void)
 * Returns the 16-byte tagged descriptor for the script name "Khojki":
 * low word 0x696b6a6f684b = "Khojki", high word tag 0xe6.
 * Confidence: low
 * Notes: tag 0xe6. */
static sk_w16_t sk_script_khojki(void)
{
    sk_w16_t r;
    r.lo = 0x696b6a6f684bULL;          /* "Khojki" */
    r.hi = 0xe600000000000000ULL;      /* tag 0xe6 */
    return r;
}

/* FUN_00464ce4 @ 0x00464ce4   (est. sk_fwd_3a25d4_464ce4)
 * Ghidra: void FUN_00464ce4(void)
 * Forwards to the helper FUN_003a25d4 (register pass-through).
 * Confidence: low
 * Notes: tail-forward to FUN_003a25d4. */
static void sk_fwd_3a25d4_464ce4(void)
{
    sk_x_003a25d4(0);
}

/* FUN_00464cf4 @ 0x00464cf4   (est. sk_fwd_45636c_one_464cf4)
 * Ghidra: void FUN_00464cf4(undefined8 param_1,undefined8 param_2)
 * Forwards two caller words to FUN_0045636c with the constant selector 1.
 * Confidence: low
 * Notes: calls FUN_0045636c(param_1, param_2, 1). */
static void sk_fwd_45636c_one_464cf4(uint64_t a, uint64_t b)
{
    sk_x_0045636c(a, b, 1);
}

/* FUN_00464d00 @ 0x00464d00   (est. sk_memcpy_fwd_464d00)
 * Ghidra: void FUN_00464d00(void)
 * Forwards to the shared memory-copy helper FUN_00117cc4 (register pass-through).
 * Confidence: low
 * Notes: tail-forward to FUN_00117cc4. */
static void sk_memcpy_fwd_464d00(void)
{
    sk_x_00117cc4(0, 0, 0);
}

/* FUN_00464d0c @ 0x00464d0c   (est. sk_nop_464d0c)
 * Ghidra: void FUN_00464d0c(void)
 * Empty placeholder: returns immediately with no effect.
 * Confidence: medium
 * Notes: empty body. */
static void sk_nop_464d0c(void)
{
}

/* FUN_00464d18 @ 0x00464d18   (est. sk_nop_464d18)
 * Ghidra: void FUN_00464d18(void)
 * Empty placeholder: returns immediately with no effect.
 * Confidence: medium
 * Notes: empty body. */
static void sk_nop_464d18(void)
{
}

/* FUN_00464d24 @ 0x00464d24   (est. sk_zero_10_words_464d24)
 * Ghidra: void FUN_00464d24(undefined8 param_1)
 * Stores param_1 at the object's first word, then zeroes the following nine
 * words (offsets 0x08..0x48), for a total of ten 8-byte slots.
 * Confidence: medium
 * Notes: object pointer carried in x19 (unaff_x19). */
static void sk_zero_10_words_464d24(uint64_t val)
{
    uint64_t *obj;

    obj = (uint64_t *)__builtin_frame_address(0);  /* x19 fragment placeholder */
    obj[0] = val;
    obj[1] = 0; obj[2] = 0; obj[3] = 0; obj[4] = 0;
    obj[5] = 0; obj[6] = 0; obj[7] = 0; obj[8] = 0;
    obj[9] = 0;
}

/* FUN_00464d44 @ 0x00464d44   (est. sk_nop_464d44)
 * Ghidra: void FUN_00464d44(void)
 * Empty placeholder: returns immediately with no effect.
 * Confidence: medium
 * Notes: empty body. */
static void sk_nop_464d44(void)
{
}

/* FUN_00464d50 @ 0x00464d50   (est. sk_nop_464d50)
 * Ghidra: void FUN_00464d50(void)
 * Empty placeholder: returns immediately with no effect.
 * Confidence: medium
 * Notes: empty body. */
static void sk_nop_464d50(void)
{
}

/* FUN_00464d5c @ 0x00464d5c   (est. sk_nop_464d5c)
 * Ghidra: void FUN_00464d5c(void)
 * Empty placeholder: returns immediately with no effect.
 * Confidence: medium
 * Notes: empty body. */
static void sk_nop_464d5c(void)
{
}

/* FUN_00464d68 @ 0x00464d68   (est. sk_nop_464d68)
 * Ghidra: void FUN_00464d68(void)
 * Empty placeholder: returns immediately with no effect.
 * Confidence: medium
 * Notes: empty body. */
static void sk_nop_464d68(void)
{
}

/* FUN_00464d74 @ 0x00464d74   (est. sk_store_field_10_464d74)
 * Ghidra: void FUN_00464d74(undefined8 param_1)
 * Stores the given value into the word at offset 0x10 of the object (pointer in
 * unaff_x19).
 * Confidence: medium
 * Notes: object pointer carried in x19. */
static void sk_store_field_10_464d74(uint64_t val)
{
    *(uint64_t *)(__builtin_frame_address(0) + 0x10) = val;
}

/* FUN_00464d80 @ 0x00464d80   (est. sk_desc_character)
 * Ghidra: undefined1 [16] FUN_00464d80(void)
 * Returns the 16-byte tagged descriptor for the error-message prefix
 * "character '": low word 0x6574636172616863 = "characte", high word
 * "r '" with tag 0xeb.
 * Confidence: low
 * Notes: tag 0xeb; payload "character '". */
static sk_w16_t sk_desc_character(void)
{
    sk_w16_t r;
    r.lo = 0x6574636172616863ULL;      /* "characte" */
    r.hi = 0xeb00000000272072ULL;      /* "r '" + tag 0xeb */
    return r;
}

/* FUN_00464da0 @ 0x00464da0   (est. sk_nop_464da0)
 * Ghidra: void FUN_00464da0(void)
 * Empty placeholder: returns immediately with no effect.
 * Confidence: medium
 * Notes: empty body. */
static void sk_nop_464da0(void)
{
}

/* FUN_00464dc0 @ 0x00464dc0   (est. sk_nop_464dc0)
 * Ghidra: void FUN_00464dc0(void)
 * Empty placeholder: returns immediately with no effect.
 * Confidence: medium
 * Notes: empty body. */
static void sk_nop_464dc0(void)
{
}

/* FUN_00464dcc @ 0x00464dcc   (est. sk_copy_field_10_464dcc)
 * Ghidra: void FUN_00464dcc(void)
 * Copies the 8-byte word at offset 0x10 from the object in x19 to the object in
 * x20 (both register fragments).
 * Confidence: medium
 * Notes: register fragments (unaff_x19/unaff_x20). */
static void sk_copy_field_10_464dcc(void)
{
    uint64_t *dst, *src;

    dst = (uint64_t *)__builtin_frame_address(0);
    src = (uint64_t *)__builtin_frame_address(0);
    dst[2] = src[2];
}

/* FUN_00464dd8 @ 0x00464dd8   (est. sk_tag_word_6e_464dd8)
 * Ghidra: ulong FUN_00464dd8(ulong param_1)
 * Clears the low 48 bits of param_1 and sets them to 0x6e, yielding
 * (param_1 & 0xffff000000000000) | 0x6e000000000000. Produces a 0x6e-tagged
 * word.
 * Confidence: medium
 * Notes: bitfield combine. */
static uint64_t sk_tag_word_6e_464dd8(uint64_t param)
{
    return (param & 0xffff000000000000ULL) | 0x6e000000000000ULL;
}

/* FUN_00464de4 @ 0x00464de4   (est. sk_fwd_458b14_464de4)
 * Ghidra: void FUN_00464de4(void)
 * Forwards to the helper FUN_00458b14 (no arguments).
 * Confidence: low
 * Notes: tail-forward to FUN_00458b14. */
static void sk_fwd_458b14_464de4(void)
{
    sk_x_00458b14();
}

/* FUN_00464dfc @ 0x00464dfc   (est. sk_desc_digits_in)
 * Ghidra: undefined1 [16] FUN_00464dfc(void)
 * Returns the 16-byte tagged descriptor for the error-message fragment
 * " digits ... in '": low word 0x2073746967696420 = " digits ", high word
 * "in '" with tag 0xec.
 * Confidence: low
 * Notes: tag 0xec; payload " digits " + "in '". */
static sk_w16_t sk_desc_digits_in(void)
{
    sk_w16_t r;
    r.lo = 0x2073746967696420ULL;      /* " digits " */
    r.hi = 0xec00000027206e69ULL;      /* "in '" + tag 0xec */
    return r;
}

/* FUN_00464e1c @ 0x00464e1c   (est. sk_return_one_464e1c)
 * Ghidra: undefined8 FUN_00464e1c(void)
 * Returns the constant 1.
 * Confidence: medium
 * Notes: literal 1. */
static uint64_t sk_return_one_464e1c(void)
{
    return 1;
}

/* FUN_00464e28 @ 0x00464e28   (est. sk_nop_464e28)
 * Ghidra: void FUN_00464e28(void)
 * Empty placeholder: returns immediately with no effect.
 * Confidence: medium
 * Notes: empty body. */
static void sk_nop_464e28(void)
{
}

/* FUN_00464e34 @ 0x00464e34   (est. sk_desc_paren)
 * Ghidra: undefined1 [16] FUN_00464e34(void)
 * Returns the 16-byte tagged descriptor for the single character "(":
 * low word 0x28 = '(', high word tag 0xe1.
 * Confidence: low
 * Notes: tag 0xe1; payload "(". */
static sk_w16_t sk_desc_paren(void)
{
    sk_w16_t r;
    r.lo = 0x28ULL;                    /* "(" */
    r.hi = 0xe100000000000000ULL;      /* tag 0xe1 */
    return r;
}

/* FUN_00464e40 @ 0x00464e40   (est. sk_stack_addr_464e40)
 * Ghidra: undefined1 * FUN_00464e40(void)
 * Returns the address of a stack slot (the decompiler reported it as
 * &stack0x00000008). Represented via the builtin frame address.
 * Confidence: low
 * Notes: register/stack fragment. */
static uint64_t sk_stack_addr_464e40(void)
{
    return (uint64_t)__builtin_frame_address(0) + 0x8;
}

/* FUN_00464e64 @ 0x00464e64   (est. sk_fwd_3a25d4_464e64)
 * Ghidra: void FUN_00464e64(void)
 * Forwards to the helper FUN_003a25d4 (register pass-through).
 * Confidence: low
 * Notes: tail-forward to FUN_003a25d4. */
static void sk_fwd_3a25d4_464e64(void)
{
    sk_x_003a25d4(0);
}

/* FUN_00464e70 @ 0x00464e70   (est. sk_memcpy_fwd_464e70)
 * Ghidra: void FUN_00464e70(void)
 * Forwards to the shared memory-copy helper FUN_00117cc4 (register pass-through).
 * Confidence: low
 * Notes: tail-forward to FUN_00117cc4. */
static void sk_memcpy_fwd_464e70(void)
{
    sk_x_00117cc4(0, 0, 0);
}

/* FUN_00464e7c @ 0x00464e7c   (est. sk_fwd_3a25d4_464e7c)
 * Ghidra: void FUN_00464e7c(void)
 * Forwards to the helper FUN_003a25d4 (register pass-through).
 * Confidence: low
 * Notes: tail-forward to FUN_003a25d4. */
static void sk_fwd_3a25d4_464e7c(void)
{
    sk_x_003a25d4(0);
}

/* FUN_00464e88 @ 0x00464e88   (est. sk_fwd_42f584_464e88)
 * Ghidra: void FUN_00464e88(undefined8 param_1)
 * Forwards param_1 and an in-register stack word (with the high bit set) to
 * FUN_0042f584.
 * Confidence: low
 * Notes: calls FUN_0042f584(param_1, in_stack | 0x8000000000000000). */
static void sk_fwd_42f584_464e88(uint64_t a)
{
    sk_x_0042f584(a, 0x8000000000000000ULL);
}

/* FUN_00464e9c @ 0x00464e9c   (est. sk_fwd_45a4b4_464e9c)
 * Ghidra: void FUN_00464e9c(void)
 * Forwards to the helper FUN_0045a4b4 (no arguments).
 * Confidence: low
 * Notes: tail-forward to FUN_0045a4b4. */
static void sk_fwd_45a4b4_464e9c(void)
{
    sk_x_0045a4b4();
}

/* FUN_00464eb0 @ 0x00464eb0   (est. sk_fwd_2298d4_464eb0)
 * Ghidra: void FUN_00464eb0(void)
 * Forwards x19 shifted right by 14 bits to the helper thunk_FUN_002298d4.
 * Confidence: low
 * Notes: register fragment (unaff_x19); calls FUN_002298d4(x19 >> 0xe). */
static void sk_fwd_2298d4_464eb0(void)
{
    uint64_t x19 = (uint64_t)__builtin_frame_address(0);
    sk_x_002298d4(x19 >> 0xe);
}

/* FUN_00464ebc @ 0x00464ebc   (est. sk_desc_zero_retain_464ebc)
 * Ghidra: void FUN_00464ebc(void)
 * Builds a zeroed 16-byte descriptor on the stack (three zero words) and
 * forwards it to the retain helper FUN_0036b270.
 * Confidence: low
 * Notes: calls thunk_FUN_0036b270 with a zeroed descriptor. */
static void sk_desc_zero_retain_464ebc(void)
{
    uint64_t desc[3] = { 0, 0, 0 };
    sk_x_0036b270((uint64_t)desc);
}

/* FUN_00464ed0 @ 0x00464ed0   (est. sk_desc_build_call_2a4ab4_464ed0)
 * Ghidra: void FUN_00464ed0(void)
 * Builds a 16-byte descriptor on the stack — low word 0, high word 0xe0 tag —
 * then calls FUN_002a4ab4 with the constant 0x1d.
 * Confidence: low
 * Notes: calls FUN_002a4ab4(0x1d). */
static void sk_desc_build_call_2a4ab4_464ed0(void)
{
    uint64_t lo = 0;
    uint64_t hi = 0xe000000000000000ULL;   /* tag 0xe0 */
    (void)lo; (void)hi;
    sk_x_002a4ab4(0x1d);
}

/* FUN_00464ee4 @ 0x00464ee4   (est. sk_nop_464ee4)
 * Ghidra: void FUN_00464ee4(void)
 * Empty placeholder: returns immediately with no effect.
 * Confidence: medium
 * Notes: empty body. */
static void sk_nop_464ee4(void)
{
}

/* FUN_00464eec @ 0x00464eec   (est. sk_nop_464eec)
 * Ghidra: void FUN_00464eec(void)
 * Empty placeholder: returns immediately with no effect.
 * Confidence: medium
 * Notes: empty body. */
static void sk_nop_464eec(void)
{
}

/* FUN_00464ef8 @ 0x00464ef8   (est. sk_nop_464ef8)
 * Ghidra: void FUN_00464ef8(void)
 * Empty placeholder: returns immediately with no effect.
 * Confidence: medium
 * Notes: empty body. */
static void sk_nop_464ef8(void)
{
}

/* FUN_00464f04 @ 0x00464f04   (est. sk_desc_ptr_464f04)
 * Ghidra: undefined1 [16] FUN_00464f04(void)
 * Returns a 16-byte descriptor whose low word is the address of the string
 * global DAT_00696156 and whose high word carries tag 0xe3.
 * Confidence: low
 * Notes: references DAT_00696156; tag 0xe3. */
static sk_w16_t sk_desc_ptr_464f04(void)
{
    extern uint8_t sk_g_00696156;   /* DAT_00696156 */
    sk_w16_t r;
    r.lo = (uint64_t)&sk_g_00696156;
    r.hi = 0xe300000000000000ULL;      /* tag 0xe3 */
    return r;
}

/* FUN_00464f14 @ 0x00464f14   (est. sk_script_lao)
 * Ghidra: undefined1 [16] FUN_00464f14(void)
 * Returns the 16-byte tagged descriptor for the script name "Lao":
 * low word 0x6f614c = "Lao", high word tag 0xe3.
 * Confidence: low
 * Notes: tag 0xe3. */
static sk_w16_t sk_script_lao(void)
{
    sk_w16_t r;
    r.lo = 0x6f614cULL;                /* "Lao" */
    r.hi = 0xe300000000000000ULL;      /* tag 0xe3 */
    return r;
}

/* FUN_00464f24 @ 0x00464f24   (est. sk_nop_464f24)
 * Ghidra: void FUN_00464f24(void)
 * Empty placeholder: returns immediately with no effect.
 * Confidence: medium
 * Notes: empty body. */
static void sk_nop_464f24(void)
{
}

/* FUN_00464f40 @ 0x00464f40   (est. sk_nop_464f40)
 * Ghidra: void FUN_00464f40(void)
 * Empty placeholder: returns immediately with no effect.
 * Confidence: medium
 * Notes: empty body. */
static void sk_nop_464f40(void)
{
}

/* FUN_00464f4c @ 0x00464f4c   (est. sk_nop_464f4c)
 * Ghidra: void FUN_00464f4c(void)
 * Empty placeholder: returns immediately with no effect.
 * Confidence: medium
 * Notes: empty body. */
static void sk_nop_464f4c(void)
{
}

/* FUN_00464f58 @ 0x00464f58   (est. sk_stack_pair_464f58)
 * Ghidra: undefined1 [16] FUN_00464f58(void)
 * Returns a 16-byte pair of two stack addresses (&stack0x00000048 and
 * &stack0x000000d8), per the decompiler's stack fragments.
 * Confidence: low
 * Notes: stack-fragment pair. */
static sk_w16_t sk_stack_pair_464f58(void)
{
    sk_w16_t r;
    r.lo = (uint64_t)__builtin_frame_address(0) + 0xd8;
    r.hi = (uint64_t)__builtin_frame_address(0) + 0x48;
    return r;
}

/* FUN_00464f64 @ 0x00464f64   (est. sk_script_batak)
 * Ghidra: undefined8 FUN_00464f64(void)
 * Returns the 8-byte little-endian ASCII payload "Batak" (Batak script).
 * Confidence: low
 * Notes: constant 0x6b61746142 = bytes 42 61 74 61 6b. */
static uint64_t sk_script_batak(void)
{
    return 0x6b61746142ULL;            /* "Batak" */
}

/* FUN_00464f74 @ 0x00464f74   (est. sk_script_runic)
 * Ghidra: undefined8 FUN_00464f74(void)
 * Returns the 8-byte little-endian ASCII payload "Runic" (Runic script).
 * Confidence: low
 * Notes: constant 0x63696e7552 = bytes 52 75 6e 69 63. */
static uint64_t sk_script_runic(void)
{
    return 0x63696e7552ULL;            /* "Runic" */
}

/* FUN_00464f84 @ 0x00464f84   (est. sk_fwd_614cc_29fa0c_464f84)
 * Ghidra: void FUN_00464f84(void)
 * Calls FUN_004614cc, then forwards four words from the object (x20 fragment:
 * words 0,1,2,3) to FUN_0029fa0c in the order (2,3,0,1).
 * Confidence: low
 * Notes: register fragment (unaff_x20); calls FUN_0029fa0c(x20[2],x20[3],
 *   x20[0],x20[1]). */
static void sk_fwd_614cc_29fa0c_464f84(void)
{
    uint64_t *x20 = (uint64_t *)__builtin_frame_address(0);
    sk_x_004614cc();
    sk_x_0029fa0c(x20[2], x20[3], x20[0], x20[1]);
}

/* FUN_00464fa4 @ 0x00464fa4   (est. sk_script_takri)
 * Ghidra: undefined8 FUN_00464fa4(void)
 * Returns the 8-byte little-endian ASCII payload "Takri" (Takri script).
 * Confidence: low
 * Notes: constant 0x69726b6154 = bytes 54 61 6b 72 69. */
static uint64_t sk_script_takri(void)
{
    return 0x69726b6154ULL;            /* "Takri" */
}

/* FUN_00464fb4 @ 0x00464fb4   (est. sk_script_tamil)
 * Ghidra: undefined8 FUN_00464fb4(void)
 * Returns the 8-byte little-endian ASCII payload "Tamil" (Tamil script).
 * Confidence: low
 * Notes: constant 0x6c696d6154 = bytes 54 61 6d 69 6c. */
static uint64_t sk_script_tamil(void)
{
    return 0x6c696d6154ULL;            /* "Tamil" */
}

/* FUN_00464fc4 @ 0x00464fc4   (est. sk_nop_464fc4)
 * Ghidra: void FUN_00464fc4(void)
 * Empty placeholder: returns immediately with no effect.
 * Confidence: medium
 * Notes: empty body. */
static void sk_nop_464fc4(void)
{
}

/* FUN_00464fe0 @ 0x00464fe0   (est. sk_script_khmer)
 * Ghidra: undefined8 FUN_00464fe0(void)
 * Returns the 8-byte little-endian ASCII payload "Khmer" (Khmer script).
 * Confidence: low
 * Notes: constant 0x72656d684b = bytes 4b 68 6d 65 72. */
static uint64_t sk_script_khmer(void)
{
    return 0x72656d684bULL;            /* "Khmer" */
}

/* FUN_00464ff0 @ 0x00464ff0   (est. sk_script_osage)
 * Ghidra: undefined8 FUN_00464ff0(void)
 * Returns the 8-byte little-endian ASCII payload "Osage" (Osage script).
 * Confidence: low
 * Notes: constant 0x656761734f = bytes 4f 73 61 67 65. */
static uint64_t sk_script_osage(void)
{
    return 0x656761734fULL;            /* "Osage" */
}

/* FUN_00465000 @ 0x00465000   (est. sk_script_buhid)
 * Ghidra: undefined8 FUN_00465000(void)
 * Returns the 8-byte little-endian ASCII payload "Buhid" (Buhid script).
 * Confidence: low
 * Notes: constant 0x6469687542 = bytes 42 75 68 69 64. */
static uint64_t sk_script_buhid(void)
{
    return 0x6469687542ULL;            /* "Buhid" */
}

/* FUN_00465010 @ 0x00465010   (est. sk_memcpy_99_465010)
 * Ghidra: void FUN_00465010(void)
 * Copies 0x99 bytes between two stack buffers via FUN_00117cc4 (dst at
 * &stack0x00000378, src at &stack0x00000110).
 * Confidence: low
 * Notes: calls FUN_00117cc4(dst, src, 0x99). */
static void sk_memcpy_99_465010(void)
{
    uint64_t base = (uint64_t)__builtin_frame_address(0);
    sk_x_00117cc4((void *)(base + 0x378), (const void *)(base + 0x110), 0x99);
}

/* FUN_00465028 @ 0x00465028   (est. sk_tag_word_d0_465028)
 * Ghidra: ulong FUN_00465028(ulong param_1)
 * ORs the constant 0xd000000000000010 into param_1 (sets a high tag nibble
 * plus bit 4).
 * Confidence: medium
 * Notes: bitwise OR combine. */
static uint64_t sk_tag_word_d0_465028(uint64_t param)
{
    return param | 0xd000000000000010ULL;
}

/* FUN_00465038 @ 0x00465038   (est. sk_nop_465038)
 * Ghidra: void FUN_00465038(void)
 * Empty placeholder: returns immediately with no effect.
 * Confidence: medium
 * Notes: empty body. */
static void sk_nop_465038(void)
{
}

/* FUN_00465054 @ 0x00465054   (est. sk_nop_465054)
 * Ghidra: void FUN_00465054(void)
 * Empty placeholder: returns immediately with no effect.
 * Confidence: medium
 * Notes: empty body. */
static void sk_nop_465054(void)
{
}

/* FUN_00465070 @ 0x00465070   (est. sk_pass_stack_465070)
 * Ghidra: undefined8 FUN_00465070(void)
 * Returns the value passed on the stack at the caller's slot 0x08.
 * Confidence: low
 * Notes: stack-fragment read. */
static uint64_t sk_pass_stack_465070(void)
{
    return *(uint64_t *)((uint64_t)__builtin_frame_address(0) + 0x08);
}

/* FUN_0046507c @ 0x0046507c   (est. sk_nop_46507c)
 * Ghidra: void FUN_0046507c(void)
 * Empty placeholder: returns immediately with no effect.
 * Confidence: medium
 * Notes: empty body. */
static void sk_nop_46507c(void)
{
}

/* FUN_00465088 @ 0x00465088   (est. sk_nop_465088)
 * Ghidra: void FUN_00465088(void)
 * Empty placeholder: returns immediately with no effect.
 * Confidence: medium
 * Notes: empty body. */
static void sk_nop_465088(void)
{
}

/* FUN_00465094 @ 0x00465094   (est. sk_nop_465094)
 * Ghidra: void FUN_00465094(void)
 * Empty placeholder: returns immediately with no effect.
 * Confidence: medium
 * Notes: empty body. */
static void sk_nop_465094(void)
{
}

/* FUN_004650a0 @ 0x004650a0   (est. sk_nop_4650a0)
 * Ghidra: void FUN_004650a0(void)
 * Empty placeholder: returns immediately with no effect.
 * Confidence: medium
 * Notes: empty body. */
static void sk_nop_4650a0(void)
{
}

/* FUN_004650ac @ 0x004650ac   (est. sk_nop_4650ac)
 * Ghidra: void FUN_004650ac(void)
 * Empty placeholder: returns immediately with no effect.
 * Confidence: medium
 * Notes: empty body. */
static void sk_nop_4650ac(void)
{
}

/* FUN_004650c8 @ 0x004650c8   (est. sk_nop_4650c8)
 * Ghidra: void FUN_004650c8(void)
 * Empty placeholder: returns immediately with no effect.
 * Confidence: medium
 * Notes: empty body. */
static void sk_nop_4650c8(void)
{
}

/* FUN_004650e4 @ 0x004650e4   (est. sk_nop_4650e4)
 * Ghidra: void FUN_004650e4(void)
 * Empty placeholder: returns immediately with no effect.
 * Confidence: medium
 * Notes: empty body. */
static void sk_nop_4650e4(void)
{
}

/* FUN_004650f0 @ 0x004650f0   (est. sk_fwd_44b000_4650f0)
 * Ghidra: void FUN_004650f0(undefined8 *param_1)
 * Copies seven 8-byte words from param_1 onto the stack, then calls
 * FUN_0044b000 (register pass-through of the seven words).
 * Confidence: low
 * Notes: calls FUN_0044b000(). */
static void sk_fwd_44b000_4650f0(uint64_t *words)
{
    uint64_t w[7];

    w[0] = words[0]; w[1] = words[1]; w[2] = words[2]; w[3] = words[3];
    w[4] = words[4]; w[5] = words[5]; w[6] = words[6];
    (void)w;
    sk_x_0044b000();
}

/* FUN_00465110 @ 0x00465110   (est. sk_nop_465110)
 * Ghidra: void FUN_00465110(void)
 * Empty placeholder: returns immediately with no effect.
 * Confidence: medium
 * Notes: empty body. */
static void sk_nop_465110(void)
{
}

/* FUN_0046511c @ 0x0046511c   (est. sk_nop_46511c)
 * Ghidra: void FUN_0046511c(void)
 * Empty placeholder: returns immediately with no effect.
 * Confidence: medium
 * Notes: empty body. */
static void sk_nop_46511c(void)
{
}

/* FUN_00465128 @ 0x00465128   (est. sk_nop_465128)
 * Ghidra: void FUN_00465128(void)
 * Empty placeholder: returns immediately with no effect.
 * Confidence: medium
 * Notes: empty body. */
static void sk_nop_465128(void)
{
}

/* FUN_00465134 @ 0x00465134   (est. sk_fwd_42ec68_465134)
 * Ghidra: void FUN_00465134(void)
 * Forwards the address of a stack buffer (&stack0x000000a0) to FUN_0042ec68.
 * Confidence: low
 * Notes: calls FUN_0042ec68(&stack0xa0). */
static void sk_fwd_42ec68_465134(void)
{
    sk_x_0042ec68((uint64_t)__builtin_frame_address(0) + 0xa0);
}

/* FUN_00465144 @ 0x00465144   (est. sk_nop_465144)
 * Ghidra: void FUN_00465144(void)
 * Empty placeholder: returns immediately with no effect.
 * Confidence: medium
 * Notes: empty body. */
static void sk_nop_465144(void)
{
}

/* FUN_00465150 @ 0x00465150   (est. sk_memcpy_49_465150)
 * Ghidra: void FUN_00465150(long param_1)
 * Copies 0x49 bytes from a stack buffer (&stack0x00000088) into param_1+0x20
 * via FUN_00117cc4.
 * Confidence: low
 * Notes: calls FUN_00117cc4(param_1+0x20, &stack0x88, 0x49). */
static void sk_memcpy_49_465150(uint64_t dst)
{
    sk_x_00117cc4((void *)(dst + 0x20),
                  (const void *)((uint64_t)__builtin_frame_address(0) + 0x88),
                  0x49);
}

/* FUN_00465160 @ 0x00465160   (est. sk_memcpy_49_465160)
 * Ghidra: void FUN_00465160(long param_1)
 * Copies 0x49 bytes from a stack buffer (&stack0x00000078) into param_1+0x20
 * via FUN_00117cc4.
 * Confidence: low
 * Notes: calls FUN_00117cc4(param_1+0x20, &stack0x78, 0x49). */
static void sk_memcpy_49_465160(uint64_t dst)
{
    sk_x_00117cc4((void *)(dst + 0x20),
                  (const void *)((uint64_t)__builtin_frame_address(0) + 0x78),
                  0x49);
}

/* FUN_00465170 @ 0x00465170   (est. sk_nop_465170)
 * Ghidra: void FUN_00465170(void)
 * Empty placeholder: returns immediately with no effect.
 * Confidence: medium
 * Notes: empty body. */
static void sk_nop_465170(void)
{
}

/* FUN_0046518c @ 0x0046518c   (est. sk_tag_word_6d_46518c)
 * Ghidra: ulong FUN_0046518c(ulong param_1)
 * Sets bits 32-39 of param_1 to 0x6d while keeping the low 32 bits and the
 * high 24 bits: (param_1 & 0xffff0000ffffffff) | 0x6d00000000.
 * Confidence: medium
 * Notes: bitfield combine. */
static uint64_t sk_tag_word_6d_46518c(uint64_t param)
{
    return (param & 0xffff0000ffffffffULL) | 0x6d00000000ULL;
}

/* FUN_00465198 @ 0x00465198   (est. sk_fwd_3a25d4_465198)
 * Ghidra: void FUN_00465198(void)
 * Forwards an in-register x3 word to FUN_003a25d4.
 * Confidence: low
 * Notes: calls FUN_003a25d4(in_x3). */
static void sk_fwd_3a25d4_465198(void)
{
    sk_x_003a25d4(0);
}

/* FUN_004651a8 @ 0x004651a8   (est. sk_fwd_6a374_4651a8)
 * Ghidra: void FUN_004651a8(void)
 * Calls FUN_0006a374 with the constant 0.
 * Confidence: low
 * Notes: calls FUN_0006a374(0). */
static void sk_fwd_6a374_4651a8(void)
{
    sk_x_0006a374(0);
}

/* FUN_004651b8 @ 0x004651b8   (est. sk_fwd_3a25d4_4651b8)
 * Ghidra: void FUN_004651b8(void)
 * Forwards an in-register x3 word to FUN_003a25d4.
 * Confidence: low
 * Notes: calls FUN_003a25d4(in_x3). */
static void sk_fwd_3a25d4_4651b8(void)
{
    sk_x_003a25d4(0);
}

/* FUN_004651c8 @ 0x004651c8   (est. sk_frame_addr_4651c8)
 * Ghidra: long FUN_004651c8(void)
 * Returns the caller's frame pointer minus 0xc0 (an address into the caller's
 * stack frame). Represented via the builtin frame address; the decompiler
 * reported the fragment as unaff_x29.
 * Confidence: low
 * Notes: register fragment (unaff_x29); offset -0xc0. */
static uint64_t sk_frame_addr_4651c8(void)
{
    return (uint64_t)__builtin_frame_address(0) - 0xc0;
}

/* FUN_004651d4 @ 0x004651d4   (est. sk_script_thai)
 * Ghidra: undefined1 [16] FUN_004651d4(void)
 * Returns the 16-byte tagged descriptor for the script name "Thai":
 * low word 0x69616854 = "Thai", high word tag 0xe4.
 * Confidence: low
 * Notes: tag 0xe4. */
static sk_w16_t sk_script_thai(void)
{
    sk_w16_t r;
    r.lo = 0x69616854ULL;              /* "Thai" */
    r.hi = 0xe400000000000000ULL;      /* tag 0xe4 */
    return r;
}
