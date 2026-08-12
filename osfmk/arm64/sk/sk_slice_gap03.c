/* Recreated from cl4_kernel.raw (cL4 Secure Kernel, arm64e, image base 0) —
 * the cL4 microkernel (GL1). Ground truth: Ghidra FUN_ names + addresses.
 * All names are estimates unless string/header matched.
 *
 * SKGAP03 slice (0x0034aac4-0x0034d5d8): a dense run of small leaf/thunk
 * functions in the cL4 binary. The run is dominated by three families:
 *   (1) argument-marshalling thunks that only shuffle callee-saved registers
 *       (x19-x28) into argument registers and return — likely tail-call
 *       trampolines / function-pointer casts whose real target was inlined;
 *   (2) PAC (pointer-authentication) / tagged-pointer decode stubs that read
 *       an "object header" word at [obj-8] or select between a 48-bit field
 *       and a 4-bit tag based on a flag bit in a metadata word; and
 *   (3) static-data reference stubs that materialise a pointer to a global
 *       (type descriptor / message table) via adrp+add.
 * A handful adjust the stack frame (mov sp, …; stur to [x29-#off]) — those
 * reference unaff_* registers the decompiler could not resolve and are marked
 * low confidence. The register-only thunks are given low/medium confidence:
 * the exact register moves are ground truth, but the intended high-level
 * operation is inferred.
 */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

typedef uint64_t word_t;
typedef unsigned int uint;
typedef unsigned short ushort;
typedef unsigned char byte;
typedef void (*code_t)(void);

/* 16-byte value (a 128-bit register / pair of words). lo = low 64 bits,
 * hi = high 64 bits. */
typedef struct { word_t lo, hi; } sk16_t;

#define SKGAP03_FATAL(a) __builtin_trap()

/* ---- Called helpers (ground-truth FUN_ addresses) ---- */
extern word_t sk_h_0006a4c0(word_t, word_t);   /* frame/header walker */
extern word_t sk_h_000a649c(word_t);           /* tagged-ptr field offset */
extern word_t sk_h_0016186c(word_t);           /* tagged-ptr field offset */
extern word_t sk_h_00310a14(word_t);           /* tagged-ptr field offset */
extern word_t sk_h_00310a74(word_t);           /* tagged-ptr field offset */
extern word_t sk_h_003109b4(word_t);           /* tagged-ptr field offset */
extern word_t sk_h_0014ae44(word_t);           /* tagged-ptr field offset */
extern word_t sk_h_0008f728(word_t);           /* tagged-ptr field offset */
extern word_t sk_h_0008f758(word_t);           /* tagged-ptr field offset */
extern word_t sk_h_000839f8(word_t, word_t, word_t); /* jumptable dispatch */
extern void  sk_h_00310d68(void);              /* helper -> 0x21480 */
extern void  sk_h_001afa84(word_t, long, long, word_t, word_t, word_t,
                           long, long);        /* fatal error printer (noreturn) */

/* ---- Opaque data symbols referenced by data-ref thunks ---- */
extern byte sk_d_006c0150;                     /* DAT_006c0150 */
extern byte sk_d_006c0158;                     /* DAT_006c0158 */
extern byte sk_d_004ec590;                     /* DAT_004ec590 */
extern byte sk_d_005cee60;                     /* DAT_005cee60 (0x5ce000+0xe60) */
extern byte sk_d_005cecd0;                     /* DAT_005cecd0 (0x5ce000+0xcd0) */
extern byte sk_d_005cf790;                     /* DAT_005cf790 (0x5cf000+0x7b0-0x20) */
extern byte sk_d_0060e3fc;                     /* DAT_0060e3fc */
extern byte sk_d_0060e230;                     /* DAT_0060e230 (0x60e000+0x208+0x28) */
extern byte sk_d_00677a60;                     /* DAT_00677a60 (0x677000+0x7e0+0x880-0x60) */
extern byte sk_d_0067b1e0;                     /* DAT_0067b1e0 (0x67b000+0x1e0) */
extern byte sk_d_00611b24;                     /* DAT_00611b24 */
extern byte sk_d_00611b3c;                     /* DAT_00611b3c */

/* ==================================================================== *
 * Family (1): frame-adjust thunks — compute sp-offset, store to the
 * caller's frame slot [x29-#off], move sp, copy x8->x9 and return.
 * These are the tail of coroutine/stack-switch stubs; low confidence.
 * ==================================================================== */

/* FUN_0034aac4 @ 0x0034aac4   (est. sk_stack_adjust_100)
 * Ghidra: void FUN_0034aac4(void)
 * Adjusts the stack pointer down by x12 (unaff), stores the new SP into the
 * caller's frame slot at [x29-0x100], then returns with x9 = x8 (pass-through).
 * Confidence: low
 * Notes: uses unaff_x12 / unaff_x29; decompiler could not resolve. */
void sk_f_0034aac4(void){ return; }

/* FUN_0034aadc @ 0x0034aadc   (est. sk_stack_adjust_e8)
 * Ghidra: void FUN_0034aadc(void)
 * Same as 0x34aac4 but stores the new SP at [x29-0xe8].
 * Confidence: low
 * Notes: unaff_x12 / unaff_x29. */
void sk_f_0034aadc(void){ return; }

/* FUN_0034abec @ 0x0034abec   (est. sk_stack_adjust_c8)
 * Ghidra: void FUN_0034abec(void)
 * Same family: sub x9,x9,x12; stur [x29,-0xc8]; mov sp,x9; mov x9,x8; ret.
 * Confidence: low
 * Notes: unaff_x9 / x12 / x29. */
void sk_f_0034abec(void){ return; }

/* FUN_0034ac00 @ 0x0034ac00   (est. sk_stack_adjust_70)
 * Ghidra: void FUN_0034ac00(void)
 * Same family: sub x9,x9,x12; stur [x29,-0x70]; mov sp,x9; mov x9,x8; ret.
 * Confidence: low
 * Notes: unaff_x9 / x12 / x29. */
void sk_f_0034ac00(void){ return; }

/* FUN_0034ac14 @ 0x0034ac14   (est. sk_stack_adjust_b8)
 * Ghidra: void FUN_0034ac14(void)
 * Same family: sub x9,x9,x12; stur [x29,-0xb8]; mov sp,x9; mov x9,x8; ret.
 * Confidence: low
 * Notes: unaff_x9 / x12 / x29. */
void sk_f_0034ac14(void){ return; }

/* FUN_0034ac28 @ 0x0034ac28   (est. sk_stack_adjust_68)
 * Ghidra: void FUN_0034ac28(void)
 * Same family: sub x9,x9,x12; stur [x29,-0x68]; mov sp,x9; mov x9,x8; ret.
 * Confidence: low
 * Notes: unaff_x9 / x12 / x29. */
void sk_f_0034ac28(void){ return; }

/* FUN_0034ac3c @ 0x0034ac3c   (est. sk_stack_adjust_70b)
 * Ghidra: void FUN_0034ac3c(void)
 * Same family via x8: mov x8,sp; sub x8,x8,x12; stur [x29,-0x70]; mov sp,x8; ret.
 * Confidence: low
 * Notes: unaff_x12 / x29. */
void sk_f_0034ac3c(void){ return; }

/* FUN_0034ac50 @ 0x0034ac50   (est. sk_stack_adjust_98)
 * Ghidra: void FUN_0034ac50(void)
 * Same family via x8: mov x8,sp; sub x8,x8,x12; stur [x29,-0x98]; mov sp,x8; ret.
 * Confidence: low
 * Notes: unaff_x12 / x29. */
void sk_f_0034ac50(void){ return; }

/* FUN_0034acf0 @ 0x0034acf0   (est. sk_stack_adjust_indirect)
 * Ghidra: void FUN_0034acf0(void)
 * stur x9,[x10,-0x100]; mov sp,x9; mov x9,x8; ret. Stores SP-derived value at
 * [x10-0x100] (x10 unaff) instead of [x29-…].
 * Confidence: low
 * Notes: unaff_x9 / x10 / x8. */
void sk_f_0034acf0(void){ return; }

/* FUN_0034ae44 @ 0x0034ae44   (est. sk_stack_adjust_f8)
 * Ghidra: void FUN_0034ae44(void)
 * sub x9,x9,x12; stur [x29,-0xf8]; mov sp,x9; mov x9,x8; ret.
 * Confidence: low
 * Notes: unaff_x9 / x12 / x29. */
void sk_f_0034ae44(void){ return; }

/* FUN_0034ae58 @ 0x0034ae58   (est. sk_stack_adjust_a0)
 * Ghidra: void FUN_0034ae58(void)
 * mov x8,sp; sub x8,x8,x12; stur [x29,-0xa0]; mov sp,x8; ret.
 * Confidence: low
 * Notes: unaff_x12 / x29. */
void sk_f_0034ae58(void){ return; }

/* FUN_0034ae94 @ 0x0034ae94   (est. sk_stack_adjust_sp24)
 * Ghidra: void FUN_0034ae94(void)
 * mov x9,sp; sub x24,x9,x12; mov sp,x24; mov x9,x8; ret.
 * Confidence: low
 * Notes: unaff_x12 / x8 / x29. */
void sk_f_0034ae94(void){ return; }

/* FUN_0034aea8 @ 0x0034aea8   (est. sk_stack_adjust_sp25)
 * Ghidra: void FUN_0034aea8(void)
 * mov x9,sp; sub x25,x9,x12; mov sp,x25; mov x9,x8; ret.
 * Confidence: low
 * Notes: unaff_x12 / x8 / x29. */
void sk_f_0034aea8(void){ return; }

/* FUN_0034aee4 @ 0x0034aee4   (est. sk_stack_adjust_sp26)
 * Ghidra: void FUN_0034aee4(void)
 * mov x9,sp; sub x26,x9,x8; mov sp,x26; ret. (subtracts x8, not x12.)
 * Confidence: low
 * Notes: unaff_x9 / x8. */
void sk_f_0034aee4(void){ return; }

/* FUN_0034d234 @ 0x0034d234   (est. sk_stack_adjust_d8)
 * Ghidra: void FUN_0034d234(void)
 * stur x9,[x29,-0xd8]; mov sp,x9; mov x9,x8; ret.
 * Confidence: low
 * Notes: unaff_x9 / x8 / x29. */
void sk_f_0034d234(void){ return; }

/* FUN_0034d244 @ 0x0034d244   (est. sk_stack_adjust_b8b)
 * Ghidra: void FUN_0034d244(void)
 * stur x9,[x29,-0xb8]; mov sp,x9; mov x9,x8; ret.
 * Confidence: low
 * Notes: unaff_x9 / x8 / x29. */
void sk_f_0034d244(void){ return; }

/* FUN_0034d254 @ 0x0034d254   (est. sk_stack_adjust_e0)
 * Ghidra: void FUN_0034d254(void)
 * stur x9,[x29,-0xe0]; mov sp,x9; mov x9,x8; ret.
 * Confidence: low
 * Notes: unaff_x9 / x8 / x29. */
void sk_f_0034d254(void){ return; }

/* FUN_0034d294 @ 0x0034d294   (est. sk_stack_adjust_b0)
 * Ghidra: void FUN_0034d294(void)
 * stur x9,[x29,-0xb0]; mov sp,x9; mov x9,x8; ret.
 * Confidence: low
 * Notes: unaff_x9 / x8 / x29. */
void sk_f_0034d294(void){ return; }

/* FUN_0034d444 @ 0x0034d444   (est. sk_stack_adjust_d0)
 * Ghidra: void FUN_0034d444(void)
 * stur x9,[x29,-0xd0]; mov sp,x9; mov x9,x8; ret.
 * Confidence: low
 * Notes: unaff_x9 / x8 / x29. */
void sk_f_0034d444(void){ return; }

/* FUN_0034d5a8 @ 0x0034d5a8   (est. sk_stack_adjust_c8b)
 * Ghidra: void FUN_0034d5a8(void)
 * stur x9,[x29,-0xc8]; mov sp,x9; mov x9,x8; ret.
 * Confidence: low
 * Notes: unaff_x9 / x8 / x29. */
void sk_f_0034d5a8(void){ return; }

/* FUN_0034d3c4 @ 0x0034d3c4   (est. sk_stack_adjust_sp20)
 * Ghidra: void FUN_0034d3c4(void)
 * mov x9,sp; sub x20,x9,x8; mov sp,x20; ret.
 * Confidence: low
 * Notes: unaff_x9 / x8. */
void sk_f_0034d3c4(void){ return; }

/* ==================================================================== *
 * Family (2): tagged-pointer / metadata decode. These select between a
 * 48-bit pointer field and a 4-bit tag (bits 0x38-0x3b) of a metadata word,
 * based on flag bit 0x2000000000000000. A PAC'd "object header" word is
 * often fetched with `ldr x16,[x8,#-8]!` (the header at [obj-8]).
 * ==================================================================== */

/* FUN_0034aaf4 @ 0x0034aaf4   (est. sk_tag_decode_1)
 * Ghidra: void FUN_0034aaf4(void)
 * Reads a metadata word (x20 unaff): if flag bit 0x2000000000000000 is clear,
 * result = x24 & 0xffffffffffff (48-bit field); else result = (x20>>0x38)&0xf
 * (4-bit tag). Result returned in x8. Also saves x0->x23, x1->x22.
 * Confidence: medium
 * Notes: unaff_x24 / x20 / x8. The two inputs are caller registers; the
 * selection is the classic cL4 tagged-captype discriminator. */
word_t sk_f_0034aaf4(word_t field_48, word_t tag_word){
  /* x8 = flag(x20).clear ? (x24 & 0xffffffffffff) : ((x20 >> 0x38) & 0xf) */
  if ((tag_word & 0x2000000000000000ull) == 0)
    return field_48 & 0xffffffffffffull;
  return (tag_word >> 0x38) & 0xf;
}

/* FUN_0034ab88 @ 0x0034ab88   (est. sk_tag_decode_2)
 * Ghidra: void FUN_0034ab88(void)
 * Same decode using x21 (field) and x19 (tag word): result in x8 =
 * flag-bit-clear ? x21 & 0xffffffffffff : (x19>>0x38)&0xf.
 * Confidence: medium
 * Notes: unaff_x21 / x19 / x8. */
word_t sk_f_0034ab88(word_t field_48, word_t tag_word){
  if ((tag_word & 0x2000000000000000ull) == 0)
    return field_48 & 0xffffffffffffull;
  return (tag_word >> 0x38) & 0xf;
}

/* FUN_0034d0e0 @ 0x0034d0e0   (est. sk_tag_decode_3)
 * Ghidra: void FUN_0034d0e0(void)
 * Same decode using x8 (field) and x26 (tag word): result in x8 =
 * flag-bit-clear ? x8 : (x26>>0x38)&0xf.
 * Confidence: medium
 * Notes: unaff_x26 / x8. */
word_t sk_f_0034d0e0(word_t field_48, word_t tag_word){
  if ((tag_word & 0x2000000000000000ull) == 0)
    return field_48 & 0xffffffffffffull;
  return (tag_word >> 0x38) & 0xf;
}

/* FUN_0034ab20 @ 0x0034ab20   (est. sk_object_header_fetch)
 * Ghidra: void FUN_0034ab20(void)
 * Fetch the object header: x8 = x0; x16 = *(x8-8) (post-index), x17 = x8.
 * Returns the header in x16/x17 (PAC'd object header at [obj-8]).
 * Confidence: medium
 * Notes: obj header / refcount / isa word at object-8. */
void sk_f_0034ab20(void){ return; }

/* FUN_0034ad10 @ 0x0034ad10   (est. sk_object_header_fetch_2)
 * Ghidra: void FUN_0034ad10(void)
 * x2 = x0; x8 = x0; x16 = *(x8-8) (post-index). Returns header in x16.
 * Confidence: medium
 * Notes: same header fetch as 0x34ab20. */
void sk_f_0034ad10(void){ return; }

/* FUN_0034ada0 @ 0x0034ada0   (est. sk_object_header_fetch_3)
 * Ghidra: void FUN_0034ada0(void)
 * x10 = x0; x8 = *(x10-8); x16 = x8; x17 = x10. Header fetch variant.
 * Confidence: medium
 * Notes: unaff. */
void sk_f_0034ada0(void){ return; }

/* FUN_0034d140 @ 0x0034d140   (est. sk_object_header_fetch_4)
 * Ghidra: void FUN_0034d140(void)
 * x8 = x24; x16 = *(x8-8); x17 = x8. Header fetch from x24.
 * Confidence: medium
 * Notes: unaff_x24. */
void sk_f_0034d140(void){ return; }

/* FUN_0034d170 @ 0x0034d170   (est. sk_object_field_fetch_8)
 * Ghidra: void FUN_0034d170(void)
 * x8 = x27; x9 = *(x8+8) (post-index); x0 = x21. Loads field at [obj+8].
 * Confidence: medium
 * Notes: unaff_x27 / x21. */
void sk_f_0034d170(void){ return; }

/* FUN_0034d384 @ 0x0034d384   (est. sk_object_field_fetch_10)
 * Ghidra: void FUN_0034d384(void)
 * x8 = x22; x9 = *(x8+0x10) (post-index); x0 = x25. Loads field at [obj+0x10].
 * Confidence: medium
 * Notes: unaff_x22 / x25. */
void sk_f_0034d384(void){ return; }

/* FUN_0034d2c4 @ 0x0034d2c4   (est. sk_object_field_fetch_8b)
 * Ghidra: void FUN_0034d2c4(void)
 * x9 = *(x8+8) (post-index); x0 = x25; x1 = x23. Loads [obj+8], marshals.
 * Confidence: medium
 * Notes: unaff_x8 / x25 / x23. */
void sk_f_0034d2c4(void){ return; }

/* FUN_0034d2d4 @ 0x0034d2d4   (est. sk_object_field_fetch_8c)
 * Ghidra: void FUN_0034d2d4(void)
 * x9 = *(x8+8) (post-index); x0 = x21; x1 = x22. Loads [obj+8], marshals.
 * Confidence: medium
 * Notes: unaff_x8 / x21 / x22. */
void sk_f_0034d2d4(void){ return; }

/* FUN_0034d454 @ 0x0034d454   (est. sk_object_field_fetch_0)
 * Ghidra: void FUN_0034d454(void)
 * x19 = x1; x20 = x0; x8 = *x1. Loads the word at [x1] (first field).
 * Confidence: medium
 * Notes: unaff_x0 / x1. */
void sk_f_0034d454(void){ return; }

/* ==================================================================== *
 * Family (3): static-data reference stubs — materialise a global pointer.
 * ==================================================================== */

/* FUN_0034ad60 @ 0x0034ad60   (est. sk_data_ref_4ec590)
 * Ghidra: undefined * FUN_0034ad60(void)
 * Returns a PAC'd (pacda) pointer to the data symbol at 0x4ec590.
 * Confidence: low
 * Notes: pacda x16,x17 with key 0xc6eb; addr 0x4ec590. */
word_t sk_f_0034ad60(void){
  return (word_t)&sk_d_004ec590;
}

/* FUN_0034aca0 @ 0x0034aca0   (est. sk_data_ref_677880)
 * Ghidra: void FUN_0034aca0(void)
 * x2 = x0; x1 = &DAT_00677a60 (0x677000+0x880). Marshals (data ptr, arg).
 * Confidence: low
 * Notes: unaff_x0. */
void sk_f_0034aca0(void){ return; }

/* FUN_0034aef4 @ 0x0034aef4   (est. sk_data_ref_677880b)
 * Ghidra: undefined1[16] FUN_0034aef4(void)
 * x1 = &DAT_00677a60 (0x677000+0x880); x0 = x29-0x58. Returns 16-byte pair
 * {frame-0x58, data ptr}.
 * Confidence: low
 * Notes: unaff_x29. */
sk16_t sk_f_0034aef4(void){
  sk16_t r; r.lo = 0; r.hi = (word_t)&sk_d_00677a60; return r;
}

/* FUN_0034adf4 @ 0x0034adf4   (est. sk_data_ref_6777e0)
 * Ghidra: undefined1[16] FUN_0034adf4(void)
 * x2 = x0; x1 = &DAT_00677a60-0xa0 (0x6777e0); x0 = x29-0x58.
 * Returns 16-byte pair {frame-0x58, data ptr}.
 * Confidence: low
 * Notes: unaff_x0 / x29. */
sk16_t sk_f_0034adf4(void){
  sk16_t r; r.lo = 0; r.hi = (word_t)&sk_d_00677a60 - 0xa0; return r;
}

/* FUN_0034abb0 @ 0x0034abb0   (est. sk_fatal_args_e60)
 * Ghidra: void FUN_0034abb0(void)
 * x6 = &DAT_005cee60 (0x5ce000+0xe60); w1 = 0xb; w2 = 0x2. Fatal-args setup.
 * Confidence: low
 * Notes: unaff. */
void sk_f_0034abb0(void){ return; }

/* FUN_0034ae30 @ 0x0034ae30   (est. sk_fatal_args_cd0)
 * Ghidra: void FUN_0034ae30(void)
 * x6 = &DAT_005cecd0 (0x5ce000+0xcd0); w1 = 0xb; w2 = 0x2. Fatal-args setup.
 * Confidence: low
 * Notes: unaff. */
void sk_f_0034ae30(void){ return; }

/* FUN_0034abc4 @ 0x0034abc4   (est. sk_data_ref_5cf790)
 * Ghidra: void FUN_0034abc4(void)
 * x8 = &DAT_005cf790 (0x5cf000+0x7b0-0x20); sub sp,sp,#0x10. Returns ptr.
 * Confidence: low
 * Notes: unaff. */
void sk_f_0034abc4(void){ return; }

/* FUN_0034ad00 @ 0x0034ad00   (est. sk_data_ref_60e3fc)
 * Ghidra: void FUN_0034ad00(void)
 * x3 = &DAT_0060e3fc (0x60e000+0x3fc); x4 = x3+8. Marshals two data ptrs.
 * Confidence: low
 * Notes: unaff. */
void sk_f_0034ad00(void){ return; }

/* FUN_0034d070 @ 0x0034d070   (est. sk_data_ref_60e230)
 * Ghidra: void FUN_0034d070(void)
 * x21 = 0x60e208; x4 = x21+0x28 (0x60e230). Marshals data ptr.
 * Confidence: low
 * Notes: unaff. */
void sk_f_0034d070(void){ return; }

/* FUN_0034d2a4 @ 0x0034d2a4   (est. sk_data_ref_60e230b)
 * Ghidra: void FUN_0034d2a4(void)
 * x24 = 0x60e208; x4 = x24+0x28 (0x60e230). Same as 0x34d070 via x24.
 * Confidence: low
 * Notes: unaff. */
void sk_f_0034d2a4(void){ return; }

/* FUN_0034d574 @ 0x0034d574   (est. sk_data_ref_60e230c)
 * Ghidra: void FUN_0034d574(void)
 * x22 = 0x60e208; x4 = x22+0x28 (0x60e230). Same via x22.
 * Confidence: low
 * Notes: unaff. */
void sk_f_0034d574(void){ return; }

/* FUN_0034d598 @ 0x0034d598   (est. sk_data_ref_60e230d)
 * Ghidra: void FUN_0034d598(void)
 * x23 = 0x60e208; x4 = x23+0x28 (0x60e230). Same via x23.
 * Confidence: low
 * Notes: unaff. */
void sk_f_0034d598(void){ return; }

/* FUN_0034d274 @ 0x0034d274   (est. sk_data_ref_67b1e0)
 * Ghidra: void FUN_0034d274(void)
 * x8 = &DAT_0067b1e0 (0x67b000+0x1e0); x2 = x8+8. Marshals two data ptrs.
 * Confidence: low
 * Notes: unaff. */
void sk_f_0034d274(void){ return; }

/* FUN_0034d4d4 @ 0x0034d4d4   (est. sk_data_ref_611b24)
 * Ghidra: void FUN_0034d4d4(void)
 * x3 = &DAT_00611b24 (0x611000+0xb24); x4 = &DAT_00611b3c (0x611000+0xb3c).
 * Marshals two data ptrs.
 * Confidence: low
 * Notes: unaff. */
void sk_f_0034d4d4(void){ return; }

/* ==================================================================== *
 * Family (4): PAC'd function-pointer pair stubs — return {data, code}
 * pairs (16-byte). The code half is PAC-signed (pacia) with key 0x2abe.
 * ==================================================================== */

/* FUN_0034adb4 @ 0x0034adb4   (est. sk_pair_6c0158)
 * Ghidra: undefined1[16] FUN_0034adb4(void)
 * Returns {&DAT_006c0158, pacia(0x1b6734, 0x2abe)} — a data ptr + a PAC'd
 * code ptr (type metadata / witness table).
 * Confidence: low
 * Notes: pacia with key 0x2abe. */
sk16_t sk_f_0034adb4(void){
  sk16_t r; r.lo = (word_t)&sk_d_006c0158; r.hi = 0x1b6734; return r;
}

/* FUN_0034add4 @ 0x0034add4   (est. sk_pair_6c0150)
 * Ghidra: undefined1[16] FUN_0034add4(void)
 * Returns {&DAT_006c0150, pacia(0x1b60b8, 0x2abe)}.
 * Confidence: low
 * Notes: pacia with key 0x2abe. */
sk16_t sk_f_0034add4(void){
  sk16_t r; r.lo = (word_t)&sk_d_006c0150; r.hi = 0x1b60b8; return r;
}

/* ==================================================================== *
 * Family (5): single-helper wrapper stubs (pacibsp; bl; retab). Each calls
 * a small helper and forwards/marshals the result.
 * ==================================================================== */

/* FUN_0034ab30 @ 0x0034ab30   (est. sk_frame_walk_call)
 * Ghidra: void FUN_0034ab30(long param_1)
 * Loads [param_1+0x18] and [param_1+0x20]; calls helper 0x6a4c0 on the first
 * and 0xa649c on the second; result -> x9. Argument marshalling wrapper.
 * Confidence: medium
 * Notes: real two-call body. */
word_t sk_f_0034ab30(word_t param_1){
  word_t v18 = *(word_t *)(param_1 + 0x18);
  word_t v20 = *(word_t *)(param_1 + 0x20);
  word_t r1 = sk_h_0006a4c0(v18, v18);
  word_t r2 = sk_h_000a649c(v20);
  return r2;
}

/* FUN_0034acb0 @ 0x0034acb0   (est. sk_field_call_16186c)
 * Ghidra: void FUN_0034acb0(void)
 * Calls 0x16186c on x0 (saved to x19); result -> x8; x0 = x25.
 * Confidence: medium
 * Notes: unaff_x0 / x25. */
word_t sk_f_0034acb0(void){
  return 0; /* [bl 0x16186c; result in x8; unaff inputs] */
}

/* FUN_0034acd0 @ 0x0034acd0   (est. sk_field_call_310a14)
 * Ghidra: void FUN_0034acd0(void)
 * Calls 0x310a14; result -> x8; x0 = x19.
 * Confidence: medium
 * Notes: unaff. */
word_t sk_f_0034acd0(void){
  return 0; /* [bl 0x310a14; result in x8; unaff inputs] */
}

/* FUN_0034ad20 @ 0x0034ad20   (est. sk_field_call_6a4c0)
 * Ghidra: void FUN_0034ad20(void)
 * x1 = x25; calls 0x6a4c0; x0 = x26.
 * Confidence: medium
 * Notes: unaff_x25 / x26. */
word_t sk_f_0034ad20(void){
  return 0; /* [bl 0x6a4c0; unaff inputs] */
}

/* FUN_0034ad40 @ 0x0034ad40   (est. sk_dispatch_call_839f8)
 * Ghidra: void FUN_0034ad40(undefined4 param_1)
 * w1 = 1; x2 = x20; calls jumptable dispatcher 0x839f8; compares w0 with 1.
 * Confidence: medium
 * Notes: unaff_x20. */
void sk_f_0034ad40(word_t param_1){
  (void)param_1;
  sk_h_000839f8(param_1, 1, 0); /* w1=1, x2=x20 unaff */
}

/* FUN_0034d1e0 @ 0x0034d1e0   (est. sk_field_call_6a4c0b)
 * Ghidra: void FUN_0034d1e0(void)
 * Calls 0x6a4c0; x0 = x26.
 * Confidence: medium
 * Notes: unaff. */
word_t sk_f_0034d1e0(void){
  return 0; /* [bl 0x6a4c0; unaff inputs] */
}

/* FUN_0034d1fc @ 0x0034d1fc   (est. sk_field_call_310a74)
 * Ghidra: void FUN_0034d1fc(void)
 * x0 = x24; calls 0x310a74; result -> x9.
 * Confidence: medium
 * Notes: unaff_x24. */
word_t sk_f_0034d1fc(void){
  return 0; /* [bl 0x310a74; result in x9; unaff input] */
}

/* FUN_0034d218 @ 0x0034d218   (est. sk_field_call_3109b4)
 * Ghidra: void FUN_0034d218(void)
 * x0 = x21; calls 0x3109b4; result -> x8.
 * Confidence: medium
 * Notes: unaff_x21. */
word_t sk_f_0034d218(void){
  return 0; /* [bl 0x3109b4; result in x8; unaff input] */
}

/* FUN_0034d464 @ 0x0034d464   (est. sk_field_call_310d68)
 * Ghidra: void FUN_0034d464(void)
 * Calls 0x310d68; then x16 = *(x0-8) (post-index); x17 = x0. Header fetch
 * after helper call.
 * Confidence: medium
 * Notes: unaff. */
void sk_f_0034d464(void){ return; }

/* FUN_0034d480 @ 0x0034d480   (est. sk_dispatch_call_839f8b)
 * Ghidra: void FUN_0034d480(void)
 * x2 = x20; calls jumptable dispatcher 0x839f8; compares w0 with 1.
 * Confidence: medium
 * Notes: unaff_x20. */
void sk_f_0034d480(void){
  sk_h_000839f8(0, 0, 0); /* x2 = x20 unaff */
}

/* FUN_0034d49c @ 0x0034d49c   (est. sk_field_call_14ae44)
 * Ghidra: void FUN_0034d49c(void)
 * Calls 0x14ae44; result -> x8; x0 = x25.
 * Confidence: medium
 * Notes: unaff. */
word_t sk_f_0034d49c(void){
  return 0; /* [bl 0x14ae44; result in x8; unaff inputs] */
}

/* FUN_0034d4b8 @ 0x0034d4b8   (est. sk_field_call_8f728)
 * Ghidra: void FUN_0034d4b8(void)
 * x23 = x0; calls 0x8f728; result -> x9.
 * Confidence: medium
 * Notes: unaff. */
word_t sk_f_0034d4b8(void){
  return 0; /* [bl 0x8f728; result in x9; unaff input] */
}

/* FUN_0034d4e8 @ 0x0034d4e8   (est. sk_field_call_6a4c0c)
 * Ghidra: void FUN_0034d4e8(void)
 * x1 = x25; calls 0x6a4c0.
 * Confidence: medium
 * Notes: unaff_x25. */
word_t sk_f_0034d4e8(void){
  return 0; /* [bl 0x6a4c0; unaff input] */
}

/* FUN_0034d504 @ 0x0034d504   (est. sk_field_call_3109b4b)
 * Ghidra: void FUN_0034d504(void)
 * Calls 0x3109b4; result -> x8.
 * Confidence: medium
 * Notes: unaff. */
word_t sk_f_0034d504(void){
  return 0; /* [bl 0x3109b4; result in x8; unaff input] */
}

/* FUN_0034d520 @ 0x0034d520   (est. sk_field_call_3109b4c)
 * Ghidra: void FUN_0034d520(void)
 * Calls 0x3109b4; result -> x8.
 * Confidence: medium
 * Notes: unaff. */
word_t sk_f_0034d520(void){
  return 0; /* [bl 0x3109b4; result in x8; unaff input] */
}

/* FUN_0034d53c @ 0x0034d53c   (est. sk_field_call_310a74b)
 * Ghidra: void FUN_0034d53c(void)
 * x0 = x26; calls 0x310a74; result -> x9.
 * Confidence: medium
 * Notes: unaff_x26. */
word_t sk_f_0034d53c(void){
  return 0; /* [bl 0x310a74; result in x9; unaff input] */
}

/* FUN_0034d558 @ 0x0034d558   (est. sk_field_call_8f758)
 * Ghidra: void FUN_0034d558(void)
 * x0 = x25; calls 0x8f758; result -> x9.
 * Confidence: medium
 * Notes: unaff_x25. */
word_t sk_f_0034d558(void){
  return 0; /* [bl 0x8f758; result in x9; unaff input] */
}

/* ==================================================================== *
 * Family (6): pure argument-marshalling thunks. They only shuffle
 * callee-saved registers into argument registers (x0-x4) and return — the
 * typical tail-call trampoline whose target was inlined away.
 * Confidence: medium (register moves ground truth; intent inferred).
 * ==================================================================== */

/* FUN_0034ab9c @ 0x0034ab9c   (est. sk_marshal_3a) */
void sk_f_0034ab9c(void){ return; }
/* FUN_0034abd8 @ 0x0034abd8   (est. sk_marshal_4a) */
void sk_f_0034abd8(void){ return; }
/* FUN_0034ac64 @ 0x0034ac64   (est. sk_marshal_2a) */
void sk_f_0034ac64(void){ return; }
/* FUN_0034ac78 @ 0x0034ac78   (est. sk_marshal_4b) */
void sk_f_0034ac78(void){ return; }
/* FUN_0034ac8c @ 0x0034ac8c   (est. sk_zero_return_4) — x0=0; x1-x3=x22/x23/x24 */
void sk_f_0034ac8c(void){ return; }
/* FUN_0034ad78 @ 0x0034ad78   (est. sk_stack_sub_load) — sub x22,x9,x8; ldr x8,[x12,#0x10]! */
void sk_f_0034ad78(void){ return; }
/* FUN_0034ad8c @ 0x0034ad8c   (est. sk_marshal_3b) */
void sk_f_0034ad8c(void){ return; }
/* FUN_0034ae08 @ 0x0034ae08   (est. sk_fatal_args_2) — w1=0xb w2=0x2 w4=0x23 w5=0x2 */
void sk_f_0034ae08(void){ return; }
/* FUN_0034ae1c @ 0x0034ae1c   (est. sk_marshal_4c) */
void sk_f_0034ae1c(void){ return; }
/* FUN_0034ae6c @ 0x0034ae6c   (est. sk_marshal_2b) */
void sk_f_0034ae6c(void){ return; }
/* FUN_0034ae80 @ 0x0034ae80   (est. sk_marshal_4d) */
void sk_f_0034ae80(void){ return; }
/* FUN_0034aebc @ 0x0034aebc   (est. sk_marshal_4e) */
void sk_f_0034aebc(void){ return; }
/* FUN_0034aed0 @ 0x0034aed0   (est. sk_marshal_4f) — w1=0 w2=1 */
void sk_f_0034aed0(void){ return; }
/* FUN_0034d080 @ 0x0034d080   (est. sk_marshal_3c) */
void sk_f_0034d080(void){ return; }
/* FUN_0034d090 @ 0x0034d090   (est. sk_marshal_3d) */
void sk_f_0034d090(void){ return; }
/* FUN_0034d0d0 @ 0x0034d0d0   (est. sk_marshal_3e) */
void sk_f_0034d0d0(void){ return; }
/* FUN_0034d100 @ 0x0034d100   (est. sk_marshal_2c) */
void sk_f_0034d100(void){ return; }
/* FUN_0034d130 @ 0x0034d130   (est. sk_marshal_3f) */
void sk_f_0034d130(void){ return; }
/* FUN_0034d150 @ 0x0034d150   (est. sk_marshal_2d) */
void sk_f_0034d150(void){ return; }
/* FUN_0034d160 @ 0x0034d160   (est. sk_marshal_1a) */
void sk_f_0034d160(void){ return; }
/* FUN_0034d180 @ 0x0034d180   (est. sk_marshal_3g) */
void sk_f_0034d180(void){ return; }
/* FUN_0034d190 @ 0x0034d190   (est. sk_marshal_3h) */
void sk_f_0034d190(void){ return; }
/* FUN_0034d1a0 @ 0x0034d1a0   (est. sk_marshal_3i) */
void sk_f_0034d1a0(void){ return; }
/* FUN_0034d1b0 @ 0x0034d1b0   (est. sk_zero_return_3a) — x0=0; x1=x21 x2=x22 */
void sk_f_0034d1b0(void){ return; }
/* FUN_0034d1c0 @ 0x0034d1c0   (est. sk_marshal_3j) — x1=0 w2=2 */
void sk_f_0034d1c0(void){ return; }
/* FUN_0034d1d0 @ 0x0034d1d0   (est. sk_marshal_2e) */
void sk_f_0034d1d0(void){ return; }
/* FUN_0034d284 @ 0x0034d284   (est. sk_marshal_3k) */
void sk_f_0034d284(void){ return; }
/* FUN_0034d2b4 @ 0x0034d2b4   (est. sk_marshal_3l) */
void sk_f_0034d2b4(void){ return; }
/* FUN_0034d2e4 @ 0x0034d2e4   (est. sk_marshal_3m) */
void sk_f_0034d2e4(void){ return; }
/* FUN_0034d2f4 @ 0x0034d2f4   (est. sk_marshal_2f) */
void sk_f_0034d2f4(void){ return; }
/* FUN_0034d304 @ 0x0034d304   (est. sk_marshal_3n) */
void sk_f_0034d304(void){ return; }
/* FUN_0034d314 @ 0x0034d314   (est. sk_marshal_2g) */
void sk_f_0034d314(void){ return; }
/* FUN_0034d324 @ 0x0034d324   (est. sk_marshal_4g) */
void sk_f_0034d324(void){ return; }
/* FUN_0034d334 @ 0x0034d334   (est. sk_marshal_3o) */
void sk_f_0034d334(void){ return; }
/* FUN_0034d344 @ 0x0034d344   (est. sk_marshal_3p) */
void sk_f_0034d344(void){ return; }
/* FUN_0034d354 @ 0x0034d354   (est. sk_marshal_2h) */
void sk_f_0034d354(void){ return; }
/* FUN_0034d364 @ 0x0034d364   (est. sk_marshal_3q) */
void sk_f_0034d364(void){ return; }
/* FUN_0034d374 @ 0x0034d374   (est. sk_marshal_2i) */
void sk_f_0034d374(void){ return; }
/* FUN_0034d394 @ 0x0034d394   (est. sk_marshal_2j) */
void sk_f_0034d394(void){ return; }
/* FUN_0034d3a4 @ 0x0034d3a4   (est. sk_marshal_2k) */
void sk_f_0034d3a4(void){ return; }
/* FUN_0034d3d4 @ 0x0034d3d4   (est. sk_marshal_3r) */
void sk_f_0034d3d4(void){ return; }
/* FUN_0034d3e4 @ 0x0034d3e4   (est. sk_zero_return_3b) — x0=0; x1=x23 x2=x24 */
void sk_f_0034d3e4(void){ return; }
/* FUN_0034d3f4 @ 0x0034d3f4   (est. sk_zero_return_3c) — x0=0; x1=x23 x2=x22 */
void sk_f_0034d3f4(void){ return; }
/* FUN_0034d404 @ 0x0034d404   (est. sk_zero_return_3d) — x0=0; x1=x25 x2=x26 */
void sk_f_0034d404(void){ return; }
/* FUN_0034d414 @ 0x0034d414   (est. sk_zero_return_3e) — x0=0; x1=x19 x2=x19 */
void sk_f_0034d414(void){ return; }
/* FUN_0034d424 @ 0x0034d424   (est. sk_zero_return_3f) — x0=0; x1=x22 x2=x21 */
void sk_f_0034d424(void){ return; }
/* FUN_0034d434 @ 0x0034d434   (est. sk_marshal_2l) */
void sk_f_0034d434(void){ return; }

/* ==================================================================== *
 * Family (7): no-op stubs / align stubs / bit-twiddle / arithmetic.
 * ==================================================================== */

/* FUN_0034ab10 @ 0x0034ab10   (est. sk_align16)
 * Ghidra: void FUN_0034ab10(void)
 * x9 = sp; x10 = x8+0xf; x12 = x10 & ~0xf. 16-byte round-up of x8.
 * Confidence: low
 * Notes: unaff_x8. */
void sk_f_0034ab10(void){ return; }

/* FUN_0034d3b4 @ 0x0034d3b4   (est. sk_align16b)
 * Ghidra: void FUN_0034d3b4(void)
 * x9 = sp; x10 = x12+0xf; x10 &= ~0xf. 16-byte round-up of x12.
 * Confidence: low
 * Notes: unaff_x12. */
void sk_f_0034d3b4(void){ return; }

/* FUN_0034d264 @ 0x0034d264   (est. sk_xor128_stack)
 * Ghidra: undefined1 * FUN_0034d264(void)
 * v0 = v0 XOR v1 (128-bit); store {q2, v0} at [sp+0x10]; return sp+0x8.
 * Returns a pointer to the stack-resident 32-byte result.
 * Confidence: low
 * Notes: vector ops; unaff. */
word_t sk_f_0034d264(void){
  return 0; /* [stack 128-bit xor result; pointer return] */
}

/* FUN_0034d584 @ 0x0034d584   (est. sk_half_isnan)
 * Ghidra: void FUN_0034d584(void)
 * w8 = h0; w8 &= 0x7fff; compares against 0x7bff — tests the exponent bits of
 * an IEEE-754 half value (NaN/Inf detection). Sets flags only.
 * Confidence: low
 * Notes: half-float exponent check. */
void sk_f_0034d584(void){ return; }

/* FUN_0034d5b8 @ 0x0034d5b8   (est. sk_round_div)
 * Ghidra: void FUN_0034d5b8(void)
 * w15 = ~(0xffffffff << w13); w14 = (w14 + w15) >> w13; w14 += 1; cmp 0xff.
 * Round-up division / alignment with a shift count w13.
 * Confidence: low
 * Notes: unaff_w13 / w14. */
void sk_f_0034d5b8(void){ return; }

/* FUN_0034d5d8 @ 0x0034d5d8   (est. sk_bit_twiddle)
 * Ghidra: void FUN_0034d5d8(void)
 * w10 = w9|w10; w9 = w10 & 0xff; w10 = w10 & 0x100000; cmp w9, 0x7.
 * Bit merge / flag test on low byte vs 0x7.
 * Confidence: low
 * Notes: unaff_w9 / w10. */
void sk_f_0034d5d8(void){ return; }

/* FUN_0034aaf0 @ 0x0034aaf0 (no func) placeholder not in batch */

/* ==================================================================== *
 * No-op / placeholder stubs (bare `ret` in the binary). These are the
 * bulk of the remaining addresses: pure register shuffles or empties.
 * ==================================================================== */

/* ==================================================================== *
 * Family (8): fatal-error path. Calls the Swift fatal-error printer with a
 * message + severity + a Swift source location (file "Fatal error", etc.).
 * ==================================================================== */

/* FUN_0034d0a0 @ 0x0034d0a0   (est. sk_fatal_duration)
 * Ghidra: void FUN_0034d0a0(undefined8 param_1)
 * Noreturn fatal path: calls the fatal-error printer (0x1afa84) with the
 * "Fatal error" message, severity 0xb/2, flags, a Swift/Duration source
 * location and arg counts. Used to trap on an invalid Duration value.
 * Confidence: high
 * Notes: string refs s_Fatal_error_005accd0 / s_Swift_Duration_swift_005d0db0. */
void sk_f_0034d0a0(void){
  sk_h_001afa84((word_t)"Fatal error", 0xb, 2, 0,
                (word_t)0xe000000000000000ull, (word_t)"Swift/Duration.swift",
                0x14, 2);
  SKGAP03_FATAL(0x34d0a0);
}
