/* Recreated from cl4_kernel.raw (cL4 Secure Kernel, arm64e, image base 0) —
 * the cL4 microkernel (GL1). Ground truth: Ghidra FUN_ names + addresses.
 * All names are estimates unless string/header matched.
 *
 * SKGAP08 slice (0x0034fb28-0x00350404): a dense run of small leaf/thunk
 * functions in the cL4 binary. The majority are empty no-op stubs (likely
 * placeholder/weak symbols or inline-asm trampolines that the decompiler
 * reduces to a bare return). A few pack/unpack bits into 16-byte values or
 * return small 16-byte tag/value pairs; several reference unaff_* registers
 * or the stack frame (frame-size / spill computations) that the decompiler
 * could not fully resolve — those are marked low confidence.
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

#define SKGAP08_FATAL(a) __builtin_trap()

/* Called helpers (ground-truth FUN_ addresses). Variadic so the reconstructed
 * call sites type-check under -fsyntax-only. */
extern word_t sk_h_0008f6f4(void);
extern void sk_h_00310a44(void);
extern void sk_h_000277b8(void);
extern void sk_h_00310a74(void);
extern void sk_h_0001df60(void);

/* Opaque data symbol referenced by FUN_0034fb28 (DAT_005d0ce6). */
extern byte sk_d_005d0ce6;

/* FUN_0034fb28 @ 0x0034fb28   (est. sk_f_0034fb28)
 * Ghidra: undefined1[16] FUN_0034fb28(void)
 * Returns a 16-byte pair: the address of a data symbol (DAT_005d0ce6) in the
 * low word and the constant 1 in the high word.
 * Confidence: low
 * Notes: DAT_005d0ce6 referenced as the low word; the 1 in the high word is
 *   likely a tag/count. */
sk16_t sk_f_0034fb28(void){
  sk16_t result;
  result.lo = (word_t)&sk_d_005d0ce6;   /* DAT_005d0ce6 */
  result.hi = 1;
  return result;
}

/* FUN_0034fb3c @ 0x0034fb3c   (est. sk_f_0034fb3c)
 * Ghidra: void FUN_0034fb3c(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_0034fb3c(void){ return; }

/* FUN_0034fb60 @ 0x0034fb60   (est. sk_f_0034fb60)
 * Ghidra: void FUN_0034fb60(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_0034fb60(void){ return; }

/* FUN_0034fb74 @ 0x0034fb74   (est. sk_f_0034fb74)
 * Ghidra: void FUN_0034fb74(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_0034fb74(void){ return; }

/* FUN_0034fb88 @ 0x0034fb88   (est. sk_f_0034fb88)
 * Ghidra: void FUN_0034fb88(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_0034fb88(void){ return; }

/* FUN_0034fb9c @ 0x0034fb9c   (est. sk_f_0034fb9c)
 * Ghidra: void FUN_0034fb9c(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_0034fb9c(void){ return; }

/* FUN_0034fbb0 @ 0x0034fbb0   (est. sk_f_0034fbb0)
 * Ghidra: uint FUN_0034fbb0(long param_1,uint param_2)
 * Packs a flag/field from byte [param_1+1] (low 6 bits) with a 5-bit field of
 * param_2 shifted into bits 6-10. A small bit-packing helper.
 * Confidence: medium
 * Notes: bit extract/or; no string refs. */
uint sk_f_0034fbb0(long* param_1, uint param_2){
  return (uint)(*(byte *)((char*)param_1 + 1) & 0x3f) | ((param_2 & 0x1f) << 6);
}

/* FUN_0034fbc4 @ 0x0034fbc4   (est. sk_f_0034fbc4)
 * Ghidra: void FUN_0034fbc4(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_0034fbc4(void){ return; }

/* FUN_0034fbd4 @ 0x0034fbd4   (est. sk_f_0034fbd4)
 * Ghidra: void FUN_0034fbd4(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_0034fbd4(void){ return; }

/* FUN_0034fbe4 @ 0x0034fbe4   (est. sk_f_0034fbe4)
 * Ghidra: void FUN_0034fbe4(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_0034fbe4(void){ return; }

/* FUN_0034fbf4 @ 0x0034fbf4   (est. sk_f_0034fbf4)
 * Ghidra: void FUN_0034fbf4(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_0034fbf4(void){ return; }

/* FUN_0034fc34 @ 0x0034fc34   (est. sk_f_0034fc34)
 * Ghidra: void FUN_0034fc34(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_0034fc34(void){ return; }

/* FUN_0034fc44 @ 0x0034fc44   (est. sk_f_0034fc44)
 * Ghidra: undefined1[16] FUN_0034fc44(void)
 * Returns a 16-byte pair of two static data addresses: low = 0x656358,
 * high = 0x4e8150. Likely a constant object/pair descriptor.
 * Confidence: low
 * Notes: raw addresses 0x656358 / 0x4e8150 (static data); identity unknown. */
sk16_t sk_f_0034fc44(void){
  sk16_t result;
  result.lo = 0x656358;
  result.hi = 0x4e8150;
  return result;
}

/* FUN_0034fc58 @ 0x0034fc58   (est. sk_f_0034fc58)
 * Ghidra: undefined1[16] FUN_0034fc58(void)
 * Returns a 16-byte pair of two static data addresses: low = 0x656360,
 * high = 0x4e8158. Likely a constant object/pair descriptor (adjacent to
 * FUN_0034fc44's pair).
 * Confidence: low
 * Notes: raw addresses 0x656360 / 0x4e8158 (static data); identity unknown. */
sk16_t sk_f_0034fc58(void){
  sk16_t result;
  result.lo = 0x656360;
  result.hi = 0x4e8158;
  return result;
}

/* FUN_0034fc6c @ 0x0034fc6c   (est. sk_f_0034fc6c)
 * Ghidra: void FUN_0034fc6c(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_0034fc6c(void){ return; }

/* FUN_0034fc7c @ 0x0034fc7c   (est. sk_f_0034fc7c)
 * Ghidra: void FUN_0034fc7c(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_0034fc7c(void){ return; }

/* FUN_0034fc8c @ 0x0034fc8c   (est. sk_f_0034fc8c)
 * Ghidra: undefined1[16] FUN_0034fc8c(p1,p2,p3,p4)
 * Packs two of its four arguments (the third and fourth) into a 16-byte pair:
 * low = arg3, high = arg4. A value-combining thunk.
 * Confidence: medium
 * Notes: arguments 1 and 2 are ignored. */
sk16_t sk_f_0034fc8c(word_t arg1, word_t arg2, word_t arg3, word_t arg4){
  sk16_t result;
  (void)arg1; (void)arg2;
  result.lo = arg3;
  result.hi = arg4;
  return result;
}

/* FUN_0034fc9c @ 0x0034fc9c   (est. sk_f_0034fc9c)
 * Ghidra: void FUN_0034fc9c(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_0034fc9c(void){ return; }

/* FUN_0034fcac @ 0x0034fcac   (est. sk_f_0034fcac)
 * Ghidra: void FUN_0034fcac(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_0034fcac(void){ return; }

/* FUN_0034fcc0 @ 0x0034fcc0   (est. sk_f_0034fcc0)
 * Ghidra: undefined1[16] FUN_0034fcc0(void)
 * Returns a 16-byte pair: low word = (frame pointer - 0x5a), high word =
 * 0x677650. The low word is a stack-derived address the decompiler could not
 * fully resolve (unaff_x29).
 * Confidence: low
 * Notes: unaff_x29; 0x677650 constant (static data). */
sk16_t sk_f_0034fcc0(void){
  sk16_t result;
  result.lo = 0;              /* unaff_x29 - 0x5a (unresolved frame ptr) */
  result.hi = 0x677650;
  return result;
}

/* FUN_0034fce4 @ 0x0034fce4   (est. sk_f_0034fce4)
 * Ghidra: undefined8 FUN_0034fce4(void)
 * Returns constant 0.
 * Confidence: medium
 * Notes: constant return. */
word_t sk_f_0034fce4(void){ return 0; }

/* FUN_0034fcf4 @ 0x0034fcf4   (est. sk_f_0034fcf4)
 * Ghidra: undefined8 FUN_0034fcf4(void)
 * Returns constant 0.
 * Confidence: medium
 * Notes: constant return. */
word_t sk_f_0034fcf4(void){ return 0; }

/* FUN_0034fd04 @ 0x0034fd04   (est. sk_f_0034fd04)
 * Ghidra: void FUN_0034fd04(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_0034fd04(void){ return; }

/* FUN_0034fd14 @ 0x0034fd14   (est. sk_f_0034fd14)
 * Ghidra: void FUN_0034fd14(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_0034fd14(void){ return; }

/* FUN_0034fd24 @ 0x0034fd24   (est. sk_f_0034fd24)
 * Ghidra: void FUN_0034fd24(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_0034fd24(void){ return; }

/* FUN_0034fd3c @ 0x0034fd3c   (est. sk_f_0034fd3c)
 * Ghidra: void FUN_0034fd3c(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_0034fd3c(void){ return; }

/* FUN_0034fd4c @ 0x0034fd4c   (est. sk_f_0034fd4c)
 * Ghidra: void FUN_0034fd4c(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_0034fd4c(void){ return; }

/* FUN_0034fd5c @ 0x0034fd5c   (est. sk_f_0034fd5c)
 * Ghidra: void FUN_0034fd5c(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_0034fd5c(void){ return; }

/* FUN_0034fd6c @ 0x0034fd6c   (est. sk_f_0034fd6c)
 * Ghidra: void FUN_0034fd6c(void)
 * Zeroes five 64-bit stack slots (offsets -0x90, -0xa8, -0xb0, -0x98, -0xa0
 * from the frame pointer). Local-storage initialization.
 * Confidence: low
 * Notes: unaff_x29 (frame pointer); slots only partially resolved. */
void sk_f_0034fd6c(void){
  byte* fp = 0;   /* unaff_x29 */
  *(word_t *)(fp - 0x90) = 0;
  *(word_t *)(fp - 0xa8) = 0;
  *(word_t *)(fp - 0xb0) = 0;
  *(word_t *)(fp - 0x98) = 0;
  *(word_t *)(fp - 0xa0) = 0;
  return;
}

/* FUN_0034fd7c @ 0x0034fd7c   (est. sk_f_0034fd7c)
 * Ghidra: void FUN_0034fd7c(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_0034fd7c(void){ return; }

/* FUN_0034fd8c @ 0x0034fd8c   (est. sk_f_0034fd8c)
 * Ghidra: void FUN_0034fd8c(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_0034fd8c(void){ return; }

/* FUN_0034fd9c @ 0x0034fd9c   (est. sk_f_0034fd9c)
 * Ghidra: void FUN_0034fd9c(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_0034fd9c(void){ return; }

/* FUN_0034fdac @ 0x0034fdac   (est. sk_f_0034fdac)
 * Ghidra: void FUN_0034fdac(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_0034fdac(void){ return; }

/* FUN_0034fdbc @ 0x0034fdbc   (est. sk_f_0034fdbc)
 * Ghidra: void FUN_0034fdbc(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_0034fdbc(void){ return; }

/* FUN_0034fdcc @ 0x0034fdcc   (est. sk_f_0034fdcc)
 * Ghidra: void FUN_0034fdcc(long param_1)
 * Stores the difference (in_x9 - param_1) into a stack slot at offset -0x138
 * from the frame pointer. A frame/pointer-arithmetic fragment.
 * Confidence: low
 * Notes: unaff_x29, in_x9 (unresolved register inputs). */
void sk_f_0034fdcc(long param_1){
  byte* fp = 0;   /* unaff_x29 */
  long in_x9 = 0;
  *(long *)(fp - 0x138) = in_x9 - param_1;
  return;
}

/* FUN_0034fde0 @ 0x0034fde0   (est. sk_f_0034fde0)
 * Ghidra: void FUN_0034fde0(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_0034fde0(void){ return; }

/* FUN_0034fdf8 @ 0x0034fdf8   (est. sk_f_0034fdf8)
 * Ghidra: undefined8 FUN_0034fdf8(void)
 * Returns constant 0.
 * Confidence: medium
 * Notes: constant return. */
word_t sk_f_0034fdf8(void){ return 0; }

/* FUN_0034fe08 @ 0x0034fe08   (est. sk_f_0034fe08)
 * Ghidra: undefined1[16] FUN_0034fe08(void)
 * Calls FUN_0008f6f4() and returns its 64-bit result placed in the HIGH word
 * of a 16-byte value (low word 0). A value-promotion/positioning thunk.
 * Confidence: medium
 * Notes: FUN_0008f6f4 call; result << 64 (Ghidra << 0x40 artifact). */
sk16_t sk_f_0034fe08(void){
  sk16_t result;
  result.lo = 0;
  result.hi = sk_h_0008f6f4();   /* FUN_0008f6f4 */
  return result;
}

/* FUN_0034fe28 @ 0x0034fe28   (est. sk_f_0034fe28)
 * Ghidra: void FUN_0034fe28(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_0034fe28(void){ return; }

/* FUN_0034fe38 @ 0x0034fe38   (est. sk_f_0034fe38)
 * Ghidra: void FUN_0034fe38(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_0034fe38(void){ return; }

/* FUN_0034fe48 @ 0x0034fe48   (est. sk_f_0034fe48)
 * Ghidra: void FUN_0034fe48(void)
 * Calls FUN_00310a44() and returns. A forwarding thunk.
 * Confidence: medium
 * Notes: forwards to FUN_00310a44. */
void sk_f_0034fe48(void){ sk_h_00310a44(); return; }

/* FUN_0034fe64 @ 0x0034fe64   (est. sk_f_0034fe64)
 * Ghidra: void FUN_0034fe64(void)
 * Calls FUN_000277b8() and returns. A forwarding thunk.
 * Confidence: medium
 * Notes: forwards to FUN_000277b8. */
void sk_f_0034fe64(void){ sk_h_000277b8(); return; }

/* FUN_0034fe80 @ 0x0034fe80   (est. sk_f_0034fe80)
 * Ghidra: void FUN_0034fe80(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_0034fe80(void){ return; }

/* FUN_0034fe90 @ 0x0034fe90   (est. sk_f_0034fe90)
 * Ghidra: void FUN_0034fe90(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_0034fe90(void){ return; }

/* FUN_0034fea0 @ 0x0034fea0   (est. sk_f_0034fea0)
 * Ghidra: void FUN_0034fea0(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_0034fea0(void){ return; }

/* FUN_0034feb0 @ 0x0034feb0   (est. sk_f_0034feb0)
 * Ghidra: void FUN_0034feb0(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_0034feb0(void){ return; }

/* FUN_0034fec0 @ 0x0034fec0   (est. sk_f_0034fec0)
 * Ghidra: void FUN_0034fec0(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_0034fec0(void){ return; }

/* FUN_0034fed0 @ 0x0034fed0   (est. sk_f_0034fed0)
 * Ghidra: void FUN_0034fed0(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_0034fed0(void){ return; }

/* FUN_0034fee0 @ 0x0034fee0   (est. sk_f_0034fee0)
 * Ghidra: void FUN_0034fee0(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_0034fee0(void){ return; }

/* FUN_0034fef4 @ 0x0034fef4   (est. sk_f_0034fef4)
 * Ghidra: void FUN_0034fef4(undefined8 param_1)
 * Stores its argument into a stack slot at offset -0x38 from the frame
 * pointer. A spill/parameter-save fragment.
 * Confidence: low
 * Notes: unaff_x29 (frame pointer). */
void sk_f_0034fef4(word_t param_1){
  byte* fp = 0;   /* unaff_x29 */
  *(word_t *)(fp - 0x38) = param_1;
  return;
}

/* FUN_0034ff18 @ 0x0034ff18   (est. sk_f_0034ff18)
 * Ghidra: undefined1 * FUN_0034ff18(undefined8 param_1)
 * Stores its argument into a stack slot at offset -0x18 from the frame
 * pointer and returns a pointer to a stack location (0x20).
 * Confidence: low
 * Notes: unaff_x29; returns &stack0x00000020. */
word_t sk_f_0034ff18(word_t param_1){
  byte* fp = 0;   /* unaff_x29 */
  *(word_t *)(fp - 0x18) = param_1;
  return (word_t)fp + 0x20;   /* &stack0x00000020 */
}

/* FUN_0034ff3c @ 0x0034ff3c   (est. sk_f_0034ff3c)
 * Ghidra: void FUN_0034ff3c(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_0034ff3c(void){ return; }

/* FUN_0034ff4c @ 0x0034ff4c   (est. sk_f_0034ff4c)
 * Ghidra: void FUN_0034ff4c(void)
 * Spills two callee-saved registers (x19, x22) to stack slots, calling
 * FUN_00310a74() and FUN_0001df60() in between. A setup/forwarding fragment
 * with unresolved register inputs.
 * Confidence: low
 * Notes: unaff_x19, unaff_x22; calls FUN_00310a74, FUN_0001df60. */
void sk_f_0034ff4c(void){
  byte* fp = 0;   /* unaff_x29 */
  word_t x19 = 0, x22 = 0;
  *(word_t *)(fp - 0x58) = x19;
  sk_h_00310a74();           /* FUN_00310a74 */
  *(word_t *)(fp - 0x78) = x22;
  sk_h_0001df60();           /* FUN_0001df60 */
  return;
}

/* FUN_0034ff78 @ 0x0034ff78   (est. sk_f_0034ff78)
 * Ghidra: void FUN_0034ff78(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_0034ff78(void){ return; }

/* FUN_0034ff88 @ 0x0034ff88   (est. sk_f_0034ff88)
 * Ghidra: void FUN_0034ff88(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_0034ff88(void){ return; }

/* FUN_0034ff98 @ 0x0034ff98   (est. sk_f_0034ff98)
 * Ghidra: void FUN_0034ff98(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_0034ff98(void){ return; }

/* FUN_0034ffa8 @ 0x0034ffa8   (est. sk_f_0034ffa8)
 * Ghidra: void FUN_0034ffa8(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_0034ffa8(void){ return; }

/* FUN_0034ffb8 @ 0x0034ffb8   (est. sk_f_0034ffb8)
 * Ghidra: void FUN_0034ffb8(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_0034ffb8(void){ return; }

/* FUN_0034ffc8 @ 0x0034ffc8   (est. sk_f_0034ffc8)
 * Ghidra: void FUN_0034ffc8(void)
 * Stores (frame top - in_x12) into a stack slot at -0xd0; a frame-size
 * computation fragment with an unresolved register input.
 * Confidence: low
 * Notes: in_x12 (unresolved); stack-frame size math. */
void sk_f_0034ffc8(void){
  byte* fp = 0;   /* unaff_x29 */
  long stack_top = 0;   /* &stack0x00000000 */
  long in_x12 = 0;
  *(long *)(fp - 0xd0) = stack_top - in_x12;
  return;
}

/* FUN_0034ffdc @ 0x0034ffdc   (est. sk_f_0034ffdc)
 * Ghidra: void FUN_0034ffdc(void)
 * Stores (frame top - in_x12) into a stack slot at -0xc0; a frame-size
 * computation fragment with an unresolved register input.
 * Confidence: low
 * Notes: in_x12 (unresolved); stack-frame size math. */
void sk_f_0034ffdc(void){
  byte* fp = 0;   /* unaff_x29 */
  long stack_top = 0;   /* &stack0x00000000 */
  long in_x12 = 0;
  *(long *)(fp - 0xc0) = stack_top - in_x12;
  return;
}

/* FUN_0034fff0 @ 0x0034fff0   (est. sk_f_0034fff0)
 * Ghidra: void FUN_0034fff0(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_0034fff0(void){ return; }

/* FUN_00350000 @ 0x00350000   (est. sk_f_00350000)
 * Ghidra: void FUN_00350000(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_00350000(void){ return; }

/* FUN_00350018 @ 0x00350018   (est. sk_f_00350018)
 * Ghidra: void FUN_00350018(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_00350018(void){ return; }

/* FUN_00350028 @ 0x00350028   (est. sk_f_00350028)
 * Ghidra: void FUN_00350028(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_00350028(void){ return; }

/* FUN_00350038 @ 0x00350038   (est. sk_f_00350038)
 * Ghidra: void FUN_00350038(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_00350038(void){ return; }

/* FUN_00350048 @ 0x00350048   (est. sk_f_00350048)
 * Ghidra: void FUN_00350048(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_00350048(void){ return; }

/* FUN_00350058 @ 0x00350058   (est. sk_f_00350058)
 * Ghidra: void FUN_00350058(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_00350058(void){ return; }

/* FUN_00350068 @ 0x00350068   (est. sk_f_00350068)
 * Ghidra: void FUN_00350068(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_00350068(void){ return; }

/* FUN_00350078 @ 0x00350078   (est. sk_f_00350078)
 * Ghidra: void FUN_00350078(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_00350078(void){ return; }

/* FUN_00350088 @ 0x00350088   (est. sk_f_00350088)
 * Ghidra: void FUN_00350088(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_00350088(void){ return; }

/* FUN_00350098 @ 0x00350098   (est. sk_f_00350098)
 * Ghidra: void FUN_00350098(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_00350098(void){ return; }

/* FUN_003500b0 @ 0x003500b0   (est. sk_f_003500b0)
 * Ghidra: void FUN_003500b0(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_003500b0(void){ return; }

/* FUN_003500c0 @ 0x003500c0   (est. sk_f_003500c0)
 * Ghidra: void FUN_003500c0(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_003500c0(void){ return; }

/* FUN_003500d4 @ 0x003500d4   (est. sk_f_003500d4)
 * Ghidra: void FUN_003500d4(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_003500d4(void){ return; }

/* FUN_003500e4 @ 0x003500e4   (est. sk_f_003500e4)
 * Ghidra: void FUN_003500e4(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_003500e4(void){ return; }

/* FUN_003500f4 @ 0x003500f4   (est. sk_f_003500f4)
 * Ghidra: void FUN_003500f4(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_003500f4(void){ return; }

/* FUN_00350104 @ 0x00350104   (est. sk_f_00350104)
 * Ghidra: void FUN_00350104(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_00350104(void){ return; }

/* FUN_00350114 @ 0x00350114   (est. sk_f_00350114)
 * Ghidra: long FUN_00350114(void)
 * Returns the sum of two callee-saved registers (x24 + x20). An arithmetic
 * fragment with unresolved register inputs.
 * Confidence: low
 * Notes: unaff_x20, unaff_x24. */
long sk_f_00350114(void){
  long x20 = 0, x24 = 0;
  return x24 + x20;
}

/* FUN_0035012c @ 0x0035012c   (est. sk_f_0035012c)
 * Ghidra: void FUN_0035012c(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_0035012c(void){ return; }

/* FUN_0035013c @ 0x0035013c   (est. sk_f_0035013c)
 * Ghidra: void FUN_0035013c(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_0035013c(void){ return; }

/* FUN_0035014c @ 0x0035014c   (est. sk_f_0035014c)
 * Ghidra: void FUN_0035014c(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_0035014c(void){ return; }

/* FUN_00350164 @ 0x00350164   (est. sk_f_00350164)
 * Ghidra: void FUN_00350164(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_00350164(void){ return; }

/* FUN_00350198 @ 0x00350198   (est. sk_f_00350198)
 * Ghidra: void FUN_00350198(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_00350198(void){ return; }

/* FUN_003501a8 @ 0x003501a8   (est. sk_f_003501a8)
 * Ghidra: void FUN_003501a8(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_003501a8(void){ return; }

/* FUN_003501b8 @ 0x003501b8   (est. sk_f_003501b8)
 * Ghidra: void FUN_003501b8(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_003501b8(void){ return; }

/* FUN_003501d0 @ 0x003501d0   (est. sk_f_003501d0)
 * Ghidra: void FUN_003501d0(long param_1)
 * Stores (frame top - param_1) into a stack slot at -0xf0; a frame-size
 * computation fragment.
 * Confidence: low
 * Notes: stack-frame size math. */
void sk_f_003501d0(long param_1){
  byte* fp = 0;   /* unaff_x29 */
  long stack_top = 0;   /* &stack0x00000000 */
  *(long *)(fp - 0xf0) = stack_top - param_1;
  return;
}

/* FUN_003501e4 @ 0x003501e4   (est. sk_f_003501e4)
 * Ghidra: void FUN_003501e4(long param_1)
 * Stores (frame top - param_1) into a stack slot at -0x148; a frame-size
 * computation fragment.
 * Confidence: low
 * Notes: stack-frame size math. */
void sk_f_003501e4(long param_1){
  byte* fp = 0;   /* unaff_x29 */
  long stack_top = 0;   /* &stack0x00000000 */
  *(long *)(fp - 0x148) = stack_top - param_1;
  return;
}

/* FUN_003501fc @ 0x003501fc   (est. sk_f_003501fc)
 * Ghidra: void FUN_003501fc(long param_1)
 * Writes param_1 through an unresolved pointer (x23) and then stores several
 * callee-saved registers into a record at param_1 (+0x20, +0x28, +0x30,
 * +0x38). A struct/record initializer fragment with unresolved register
 * inputs.
 * Confidence: low
 * Notes: unaff_x19/x20/x21/x22/x23 (register inputs). */
void sk_f_003501fc(long param_1){
  word_t x19 = 0, x20 = 0, x21 = 0, x22 = 0;
  volatile long **x23 = (volatile long **)0;   /* unaff_x23 store target */
  *x23 = (long*)param_1;
  *(word_t *)(param_1 + 0x30) = x19;
  *(word_t *)(param_1 + 0x38) = x20;
  *(word_t *)(param_1 + 0x20) = x22;
  *(word_t *)(param_1 + 0x28) = x21;
  return;
}

/* FUN_00350210 @ 0x00350210   (est. sk_f_00350210)
 * Ghidra: void FUN_00350210(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_00350210(void){ return; }

/* FUN_00350220 @ 0x00350220   (est. sk_f_00350220)
 * Ghidra: void FUN_00350220(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_00350220(void){ return; }

/* FUN_00350230 @ 0x00350230   (est. sk_f_00350230)
 * Ghidra: void FUN_00350230(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_00350230(void){ return; }

/* FUN_00350240 @ 0x00350240   (est. sk_f_00350240)
 * Ghidra: undefined1[16] FUN_00350240(undefined1 (*)[16])
 * Loads and returns the 16-byte value pointed to by its argument. A 16-byte
 * load/thunk.
 * Confidence: medium
 * Notes: dereferences the 16-byte pointer argument. */
sk16_t sk_f_00350240(sk16_t *param_1){
  return *param_1;
}

/* FUN_00350258 @ 0x00350258   (est. sk_f_00350258)
 * Ghidra: undefined8 FUN_00350258(undefined8 *param_1)
 * Loads and returns the 64-bit value pointed to by its argument. A load thunk.
 * Confidence: medium
 * Notes: dereferences the word pointer argument. */
word_t sk_f_00350258(word_t *param_1){
  return *param_1;
}

/* FUN_00350268 @ 0x00350268   (est. sk_f_00350268)
 * Ghidra: void FUN_00350268(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_00350268(void){ return; }

/* FUN_00350278 @ 0x00350278   (est. sk_f_00350278)
 * Ghidra: void FUN_00350278(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_00350278(void){ return; }

/* FUN_00350288 @ 0x00350288   (est. sk_f_00350288)
 * Ghidra: void FUN_00350288(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_00350288(void){ return; }

/* FUN_00350298 @ 0x00350298   (est. sk_f_00350298)
 * Ghidra: void FUN_00350298(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_00350298(void){ return; }

/* FUN_003502a8 @ 0x003502a8   (est. sk_f_003502a8)
 * Ghidra: void FUN_003502a8(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_003502a8(void){ return; }

/* FUN_003502b8 @ 0x003502b8   (est. sk_f_003502b8)
 * Ghidra: void FUN_003502b8(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_003502b8(void){ return; }

/* FUN_003502c8 @ 0x003502c8   (est. sk_f_003502c8)
 * Ghidra: void FUN_003502c8(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_003502c8(void){ return; }

/* FUN_003502d8 @ 0x003502d8   (est. sk_f_003502d8)
 * Ghidra: void FUN_003502d8(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_003502d8(void){ return; }

/* FUN_003502e8 @ 0x003502e8   (est. sk_f_003502e8)
 * Ghidra: undefined8 FUN_003502e8(void)
 * Returns constant 0.
 * Confidence: medium
 * Notes: constant return. */
word_t sk_f_003502e8(void){ return 0; }

/* FUN_003502f8 @ 0x003502f8   (est. sk_f_003502f8)
 * Ghidra: undefined8 FUN_003502f8(void)
 * Returns constant 0.
 * Confidence: medium
 * Notes: constant return. */
word_t sk_f_003502f8(void){ return 0; }

/* FUN_00350308 @ 0x00350308   (est. sk_f_00350308)
 * Ghidra: undefined8 FUN_00350308(void)
 * Returns constant 0.
 * Confidence: medium
 * Notes: constant return. */
word_t sk_f_00350308(void){ return 0; }

/* FUN_00350318 @ 0x00350318   (est. sk_f_00350318)
 * Ghidra: undefined8 FUN_00350318(void)
 * Returns constant 0.
 * Confidence: medium
 * Notes: constant return. */
word_t sk_f_00350318(void){ return 0; }

/* FUN_00350328 @ 0x00350328   (est. sk_f_00350328)
 * Ghidra: undefined1[16] FUN_00350328(void)
 * Returns a 16-byte value with an unresolved register input (in_x4) placed in
 * the HIGH word (low word 0). A value-positioning thunk.
 * Confidence: low
 * Notes: in_x4 (unresolved); result << 64 (Ghidra << 0x40 artifact). */
sk16_t sk_f_00350328(void){
  sk16_t result;
  word_t in_x4 = 0;
  result.lo = 0;
  result.hi = in_x4;
  return result;
}

/* FUN_00350338 @ 0x00350338   (est. sk_f_00350338)
 * Ghidra: undefined8 FUN_00350338(void)
 * Returns the word stored at stack offset -0x70 from the frame pointer. A
 * load-from-local fragment with an unresolved frame pointer.
 * Confidence: low
 * Notes: unaff_x29 (frame pointer). */
word_t sk_f_00350338(void){
  byte* fp = 0;   /* unaff_x29 */
  return *(word_t *)(fp - 0x70);
}

/* FUN_0035034c @ 0x0035034c   (est. sk_f_0035034c)
 * Ghidra: void FUN_0035034c(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_0035034c(void){ return; }

/* FUN_0035035c @ 0x0035035c   (est. sk_f_0035035c)
 * Ghidra: void FUN_0035035c(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_0035035c(void){ return; }

/* FUN_0035036c @ 0x0035036c   (est. sk_f_0035036c)
 * Ghidra: void FUN_0035036c(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_0035036c(void){ return; }

/* FUN_0035037c @ 0x0035037c   (est. sk_f_0035037c)
 * Ghidra: void FUN_0035037c(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_0035037c(void){ return; }

/* FUN_00350390 @ 0x00350390   (est. sk_f_00350390)
 * Ghidra: void FUN_00350390(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_00350390(void){ return; }

/* FUN_003503a0 @ 0x003503a0   (est. sk_f_003503a0)
 * Ghidra: void FUN_003503a0(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_003503a0(void){ return; }

/* FUN_003503b0 @ 0x003503b0   (est. sk_f_003503b0)
 * Ghidra: void FUN_003503b0(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_003503b0(void){ return; }

/* FUN_003503c0 @ 0x003503c0   (est. sk_f_003503c0)
 * Ghidra: undefined8 FUN_003503c0(param_1,param_2)
 * Returns its second argument, ignoring the first. An identity-on-arg2 thunk.
 * Confidence: medium
 * Notes: passes through arg2. */
word_t sk_f_003503c0(word_t arg1, word_t arg2){
  (void)arg1;
  return arg2;
}

/* FUN_003503d0 @ 0x003503d0   (est. sk_f_003503d0)
 * Ghidra: void FUN_003503d0(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_003503d0(void){ return; }

/* FUN_003503e0 @ 0x003503e0   (est. sk_f_003503e0)
 * Ghidra: void FUN_003503e0(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_003503e0(void){ return; }

/* FUN_003503ec @ 0x003503ec   (est. sk_f_003503ec)
 * Ghidra: void FUN_003503ec(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_003503ec(void){ return; }

/* FUN_003503f8 @ 0x003503f8   (est. sk_f_003503f8)
 * Ghidra: void FUN_003503f8(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_003503f8(void){ return; }

/* FUN_00350404 @ 0x00350404   (est. sk_f_00350404)
 * Ghidra: void FUN_00350404(void)
 * No-op stub; returns immediately.
 * Confidence: medium
 * Notes: empty body (no-op/placeholder). */
void sk_f_00350404(void){ return; }
