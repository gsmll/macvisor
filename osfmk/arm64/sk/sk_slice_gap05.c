/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel, GL1,
 * arm64e, image base 0) — the cL4 microkernel. Ground truth: Ghidra FUN_ names +
 * addresses in the cl4_kernel.raw program. Names use seL4/cL4 vocabulary; all
 * are estimates unless string/header matched.
 *
 * SKGAP05 — dense method-dispatch table region (0x34df34-0x34e81c). This is a
 * contiguous run of 120 tiny slots: mostly register-forwarding tail-call thunks
 * (they move the caller's callee-saved values into argument/return position and
 * fall through), a few PAC-authenticated static-descriptor getters (adrp/add/
 * pacda + mov x0), a small set of field-offset resolvers that call the shared
 * helper family FUN_003109b4/00310a44/00310a74/0008f758/000a649c, and two
 * NEON lane helpers. Bodies are faithful to the disassembly; where a slot is a
 * pure register shuffle the body is empty with the shuffle recorded in a
 * comment (the real dispatch happens in the caller's continuation). */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "sk_internal.h"

/* ---- Out-of-range cL4 helpers referenced by this region (FUN_ in comment).
 * All take/return 64-bit words (arm64e addresses), matching the decompile. ---- */
extern unsigned long sk_field_off_3c(unsigned long);   /* FUN_003109b4: obj + *(int*)(obj+0x3c) */
extern unsigned long sk_field_off_40(unsigned long);   /* FUN_00310a44: obj + *(int*)(obj+0x40) */
extern unsigned long sk_field_off_30(unsigned long);   /* FUN_00310a74: obj + *(int*)(obj+0x30) */
extern unsigned long sk_field_off_0c(unsigned long);   /* FUN_0008f758: obj + *(int*)(obj+0x0c) */
extern unsigned long sk_field_off_14(unsigned long);   /* FUN_000a649c: obj + *(int*)(obj+0x14) */
extern unsigned long sk_dispatch_jump(unsigned long);  /* FUN_000839f8: indirect method dispatch (opaque) */
extern unsigned long sk_meta_kind(unsigned long);      /* FUN_0006a4c0: metadata kind/selector helper */
extern void *sk_swift_fatal(void);                     /* FUN_004afae4 */

/* PAC-authenticated static descriptors returned by the getter slots (data).
 * The slot loads the address, PACs it with the indicated key/div, and returns
 * it in x0. The 12-byte records at these addresses hold [ptr_a, ptr_b, len,
 * flags] describing per-object metadata/catalog entries. */
extern unsigned long DAT_004eb980, DAT_004eb964, DAT_004edd08, DAT_004eab00;
extern unsigned long DAT_004ea760, DAT_004e9db0, DAT_004e8f9c, DAT_004e8b7c;
extern unsigned long DAT_0066dfb8, DAT_0066c7c0, DAT_0066cc50, DAT_0066aec8;
extern unsigned long DAT_006adf10;

/* The NEON helper at 0x34e7f4 compares two 16-byte operands lane-wise and
 * returns the max of the per-lane unsigned "less-than" masks. Modeled as a
 * scalar pair comparison. */
uint32_t sk_neon_lane_max(unsigned long a_lo, unsigned long a_hi,
                          unsigned long b_lo, unsigned long b_hi);

/*============================================================================
 * 0x34df34-0x34dfe4 — pure register-forwarding thunk slots (method table)
 *==========================================================================*/

/* FUN_0034df34 @ 0x0034df34
 * Ghidra: void FUN_0034df34(void)
 * Method-table slot: forwards x19->x20/x2 and x22->x3 (arg shuffle) then
 * returns to the caller's continuation. No work of its own.
 * Confidence: low (opaque register thunk)
 */
void sk_slot_df34(void)
{ /* mov x20,x19 ; mov x2,x19 ; mov x3,x22 ; ret */ }

/* FUN_0034df44 @ 0x0034df44
 * Ghidra: void FUN_0034df44(void)
 * Method-table slot: forwards x19->x20/x0, x23->x1.
 * Confidence: low (opaque register thunk)
 */
void sk_slot_df44(void)
{ /* mov x20,x19 ; mov x0,x19 ; mov x1,x23 ; ret */ }

/* FUN_0034df54 @ 0x0034df54
 * Ghidra: void FUN_0034df54(void)
 * Method-table slot: forwards x25->x1, x19->x2, x22->x3.
 * Confidence: low (opaque register thunk)
 */
void sk_slot_df54(void)
{ /* mov x1,x25 ; mov x2,x19 ; mov x3,x22 ; ret */ }

/* FUN_0034df64 @ 0x0034df64
 * Ghidra: void FUN_0034df64(void)
 * Method-table slot: forwards x25->x1, x23->x2, x21->x3.
 * Confidence: low (opaque register thunk)
 */
void sk_slot_df64(void)
{ /* mov x1,x25 ; mov x2,x23 ; mov x3,x21 ; ret */ }

/* FUN_0034df74 @ 0x0034df74
 * Ghidra: void FUN_0034df74(void)
 * Method-table slot: forwards x21->x20/x2, x22->x3.
 * Confidence: low (opaque register thunk)
 */
void sk_slot_df74(void)
{ /* mov x20,x21 ; mov x2,x21 ; mov x3,x22 ; ret */ }

/* FUN_0034df84 @ 0x0034df84
 * Ghidra: void FUN_0034df84(void)
 * Method-table slot: forwards x21->x20/x0, x23->x1.
 * Confidence: low (opaque register thunk)
 */
void sk_slot_df84(void)
{ /* mov x20,x21 ; mov x0,x21 ; mov x1,x23 ; ret */ }

/* FUN_0034df94 @ 0x0034df94
 * Ghidra: void FUN_0034df94(void)
 * Method-table slot: shifts argument registers left (x2->x1, x3->x2, x4->x3).
 * Confidence: low (opaque register thunk)
 */
void sk_slot_df94(void)
{ /* mov x1,x2 ; mov x2,x3 ; mov x3,x4 ; ret */ }

/* FUN_0034dfa4 @ 0x0034dfa4
 * Ghidra: void FUN_0034dfa4(void)
 * Method-table slot: installs a new stack pointer (sp = x9 - x12) and restores
 * x9 from x8. Stack-switch bootstrap.
 * Confidence: low (opaque register thunk)
 */
void sk_slot_dfa4(void)
{ /* sub x19,x9,x12 ; mov sp,x19 ; mov x9,x8 ; ret */ }

/* FUN_0034dfb4 @ 0x0034dfb4
 * Ghidra: void FUN_0034dfb4(void)
 * Method-table slot: forwards x25->x0, x24->x1, x21->x2.
 * Confidence: low (opaque register thunk)
 */
void sk_slot_dfb4(void)
{ /* mov x0,x25 ; mov x1,x24 ; mov x2,x21 ; ret */ }

/* FUN_0034dfc4 @ 0x0034dfc4
 * Ghidra: void FUN_0034dfc4(void)
 * Method-table slot: forwards x25->x0, x22->x1, x19->x2.
 * Confidence: low (opaque register thunk)
 */
void sk_slot_dfc4(void)
{ /* mov x0,x25 ; mov x1,x22 ; mov x2,x19 ; ret */ }

/* FUN_0034dfd4 @ 0x0034dfd4
 * Ghidra: void FUN_0034dfd4(void)
 * Method-table slot: x22->x8, x21->x20/x3.
 * Confidence: low (opaque register thunk)
 */
void sk_slot_dfd4(void)
{ /* mov x8,x22 ; mov x20,x21 ; mov x3,x21 ; ret */ }

/* FUN_0034dfe4 @ 0x0034dfe4
 * Ghidra: void FUN_0034dfe4(void)
 * Method-table slot: loads the PAC'd method pointer from [x25-8] into x16/x17
 * (classic arm64e indirect-method thunk prologue).
 * Confidence: low (opaque register thunk)
 */
void sk_slot_dfe4(void)
{ /* mov x8,x25 ; ldr x16,[x8,#-8]! ; mov x17,x8 ; ret */ }

/* FUN_0034dff4 @ 0x0034dff4
 * Ghidra: void FUN_0034dff4(void)
 * Method-table slot: x5->x19, x4->x20, x3->x21 (spill forward).
 * Confidence: low (opaque register thunk)
 */
void sk_slot_dff4(void)
{ /* mov x19,x5 ; mov x20,x4 ; mov x21,x3 ; ret */ }

/*============================================================================
 * 0x34e004-0x34e0f4 — arg-forwarding thunks and const-return slots
 *==========================================================================*/

/* FUN_0034e004 @ 0x0034e004
 * Ghidra: undefined8 FUN_0034e004(void)
 * Method-table slot: saves x1->x21, x0->x22, returns x3 (in_x3).
 * Confidence: low (opaque register thunk)
 */
unsigned long sk_slot_e004(void)
{ /* mov x21,x1 ; mov x22,x0 ; mov x0,x3 ; ret */ return 0; }

/* FUN_0034e014 @ 0x0034e014
 * Ghidra: void FUN_0034e014(void)
 * Method-table slot: x24->x1, x19->x2, x22->x3.
 * Confidence: low (opaque register thunk)
 */
void sk_slot_e014(void)
{ /* mov x1,x24 ; mov x2,x19 ; mov x3,x22 ; ret */ }

/* FUN_0034e024 @ 0x0034e024
 * Ghidra: void FUN_0034e024(void)
 * Method-table slot: x27->x0, x21->x1, x25->x2.
 * Confidence: low (opaque register thunk)
 */
void sk_slot_e024(void)
{ /* mov x0,x27 ; mov x1,x21 ; mov x2,x25 ; ret */ }

/* FUN_0034e034 @ 0x0034e034
 * Ghidra: void FUN_0034e034(void)
 * Method-table slot: x27->x1, x21->x2, x19->x3.
 * Confidence: low (opaque register thunk)
 */
void sk_slot_e034(void)
{ /* mov x1,x27 ; mov x2,x21 ; mov x3,x19 ; ret */ }

/* FUN_0034e044 @ 0x0034e044
 * Ghidra: void FUN_0034e044(void)
 * Method-table slot: x0->x8, x25->x0, x23->x1.
 * Confidence: low (opaque register thunk)
 */
void sk_slot_e044(void)
{ /* mov x8,x0 ; mov x0,x25 ; mov x1,x23 ; ret */ }

/* FUN_0034e054 @ 0x0034e054
 * Ghidra: void FUN_0034e054(void)
 * Method-table slot: x0->x8, x28->x0, x22->x1.
 * Confidence: low (opaque register thunk)
 */
void sk_slot_e054(void)
{ /* mov x8,x0 ; mov x0,x28 ; mov x1,x22 ; ret */ }

/* FUN_0034e064 @ 0x0034e064
 * Ghidra: void FUN_0034e064(void)
 * Method-table slot: x23->x20, x21->x0, x25->x1.
 * Confidence: low (opaque register thunk)
 */
void sk_slot_e064(void)
{ /* mov x20,x23 ; mov x0,x21 ; mov x1,x25 ; ret */ }

/* FUN_0034e074 @ 0x0034e074
 * Ghidra: void FUN_0034e074(void)
 * Method-table slot: x23->x20, x19->x0, x22->x1.
 * Confidence: low (opaque register thunk)
 */
void sk_slot_e074(void)
{ /* mov x20,x23 ; mov x0,x19 ; mov x1,x22 ; ret */ }

/* FUN_0034e084 @ 0x0034e084
 * Ghidra: void FUN_0034e084(void)
 * Method-table slot: x22->x1, x20->x2, x21->x3.
 * Confidence: low (opaque register thunk)
 */
void sk_slot_e084(void)
{ /* mov x1,x22 ; mov x2,x20 ; mov x3,x21 ; ret */ }

/* FUN_0034e094 @ 0x0034e094
 * Ghidra: void FUN_0034e094(void)
 * Method-table slot: returns x21 in x0 with w1=0, w2=1 (constant selector).
 * Confidence: low (opaque register thunk)
 */
void sk_slot_e094(void)
{ /* mov x0,x21 ; mov w1,#0 ; mov w2,#1 ; ret */ }

/* FUN_0034e0a4 @ 0x0034e0a4
 * Ghidra: undefined8 FUN_0034e0a4(void)
 * Returns 0; also saves x25->x1, x19->x2 (side stores in callee-saved regs).
 * Confidence: low
 */
unsigned long sk_slot_e0a4(void)
{ /* mov x0,#0 ; mov x1,x25 ; mov x2,x19 ; ret */ return 0; }

/* FUN_0034e0b4 @ 0x0034e0b4
 * Ghidra: undefined8 FUN_0034e0b4(void)
 * Returns 0; also sets x11=0, x12=x8.
 * Confidence: low
 */
unsigned long sk_slot_e0b4(void)
{ /* mov x0,#0 ; mov x11,#0 ; mov x12,x8 ; ret */ return 0; }

/* FUN_0034e0c4 @ 0x0034e0c4
 * Ghidra: undefined8 FUN_0034e0c4(void)
 * Returns 0; also saves x24->x1, x21->x2.
 * Confidence: low
 */
unsigned long sk_slot_e0c4(void)
{ /* mov x0,#0 ; mov x1,x24 ; mov x2,x21 ; ret */ return 0; }

/* FUN_0034e0d4 @ 0x0034e0d4
 * Ghidra: undefined8 FUN_0034e0d4(void)
 * Returns 0; also saves x20->x1, x22->x2.
 * Confidence: low
 */
unsigned long sk_slot_e0d4(void)
{ /* mov x0,#0 ; mov x1,x20 ; mov x2,x22 ; ret */ return 0; }

/* FUN_0034e0e4 @ 0x0034e0e4
 * Ghidra: void FUN_0034e0e4(void)
 * Method-table slot: x0->x23, x1->x22, and masks x24 to 48 bits into x8
 * (low 48-bit address mask, arm64e).
 * Confidence: low (opaque register thunk)
 */
void sk_slot_e0e4(void)
{ /* mov x23,x0 ; mov x22,x1 ; and x8,x24,#0xffffffffffff ; ret */ }

/* FUN_0034e0f4 @ 0x0034e0f4
 * Ghidra: void FUN_0034e0f4(void)
 * Method-table slot: x0->x23, x1->x24, x19->x0.
 * Confidence: low (opaque register thunk)
 */
void sk_slot_e0f4(void)
{ /* mov x23,x0 ; mov x24,x1 ; mov x0,x19 ; ret */ }

/*============================================================================
 * 0x34e104-0x34e1ec — field-offset resolver slots (call shared helpers)
 *==========================================================================*/

/* FUN_0034e104 @ 0x0034e104
 * Ghidra: void FUN_0034e104(void)
 * Resolves the +0x3c field offset of the object held in x19 via the shared
 * helper FUN_003109b4, leaving the result in x8.
 * Confidence: medium
 */
void sk_slot_e104(unsigned long obj)
{ sk_field_off_3c(obj); }

/* FUN_0034e120 @ 0x0034e120
 * Ghidra: void FUN_0034e120(void)
 * Method-table slot: x19->x0, x24->x1, x22->x2.
 * Confidence: low (opaque register thunk)
 */
void sk_slot_e120(void)
{ /* mov x0,x19 ; mov x1,x24 ; mov x2,x22 ; ret */ }

/* FUN_0034e130 @ 0x0034e130
 * Ghidra: undefined1 [16] FUN_0034e130(ulong param_1)
 * 16-byte result builder: returns cl4_result {lo=0, hi=param_1} — a pure
 * status/count pair where the payload rides in the high word.
 * Confidence: high (trivial)
 */
cl4_result_t sk_slot_e130(unsigned long v)
{ cl4_result_t r = {0, v}; return r; }

/* FUN_0034e140 @ 0x0034e140
 * Ghidra: void FUN_0034e140(void)
 * Resolves the +0x40 field offset via FUN_00310a44; result in x8.
 * Confidence: medium
 */
void sk_slot_e140(void)
{ sk_field_off_40(0); }

/* FUN_0034e15c @ 0x0034e15c
 * Ghidra: void FUN_0034e15c(void)
 * Resolves the +0x40 field offset of x26 via FUN_00310a44; result in x8.
 * Confidence: medium
 */
void sk_slot_e15c(unsigned long obj)
{ sk_field_off_40(obj); }

/* FUN_0034e178 @ 0x0034e178
 * Ghidra: void FUN_0034e178(undefined8 param_1)
 * Dispatches twice through the opaque method-dispatch helper FUN_000839f8
 * (each with selector w1=1 and x2=x21), then loads the PAC'd method pointer
 * from [x21-8] into x16/x17 for the caller's continuation.
 * Confidence: medium
 */
void sk_slot_e178(unsigned long a, unsigned long b)
{ sk_dispatch_jump(a); sk_dispatch_jump(b); }

/* FUN_0034e1b0 @ 0x0034e1b0
 * Ghidra: void FUN_0034e1b0(undefined4 param_1)
 * Single opaque dispatch through FUN_000839f8 (selector w1=1, x2=x25), then
 * compares the result word against 1 (the cmp w0,#1 in the body).
 * Confidence: medium
 */
void sk_slot_e1b0(unsigned long arg)
{ sk_dispatch_jump(arg); }

/* FUN_0034e1d0 @ 0x0034e1d0
 * Ghidra: void FUN_0034e1d0(void)
 * Resolves the +0x30 field offset of x22 via FUN_00310a74; result in x9.
 * Confidence: medium
 */
void sk_slot_e1d0(unsigned long obj)
{ sk_field_off_30(obj); }

/* FUN_0034e1ec @ 0x0034e1ec
 * Ghidra: void FUN_0034e1ec(void)
 * Calls the metadata-kind helper FUN_0006a4c0 on x19; result in x20.
 * Confidence: medium
 */
void sk_slot_e1ec(unsigned long obj)
{ sk_meta_kind(obj); }

/*============================================================================
 * 0x34e208-0x34e294 — PAC'd static-descriptor getters
 *==========================================================================*/

/* FUN_0034e208 @ 0x0034e208
 * Ghidra: void FUN_0034e208(void)
 * Stores constant w9=1 to [sp+8] (flags word on caller frame); computes a
 * pointer to DAT_0065c6f0 (0x5ce000+0x6f0-0x20) in x8.
 * Confidence: low
 */
void sk_slot_e208(void)
{ /* adrp x8,0x5ce000 ; add x8,x8,#0x6f0 ; sub x8,x8,#0x20 ; mov w9,#1 ;
       str w9,[sp,#0x8] ; ret */ }

/* FUN_0034e220 @ 0x0034e220
 * Ghidra: undefined * FUN_0034e220(void)
 * Returns the PAC-authenticated (data key A) static descriptor pointer
 * &DAT_004eb980 — a 12-byte metadata record (see header).
 * Confidence: medium
 */
unsigned long sk_slot_e220(void)
{ return DAT_004eb980; }

/* FUN_0034e238 @ 0x0034e238
 * Ghidra: undefined * FUN_0034e238(void)
 * Returns PAC-authenticated static descriptor &DAT_004eb964.
 * Confidence: medium
 */
unsigned long sk_slot_e238(void)
{ return DAT_004eb964; }

/* FUN_0034e250 @ 0x0034e250
 * Ghidra: undefined * FUN_0034e250(void)
 * Returns PAC-authenticated static descriptor &DAT_004edd08.
 * Confidence: medium
 */
unsigned long sk_slot_e250(void)
{ return DAT_004edd08; }

/* FUN_0034e268 @ 0x0034e268
 * Ghidra: undefined * FUN_0034e268(void)
 * Returns PAC-authenticated static descriptor &DAT_004eab00.
 * Confidence: medium
 */
unsigned long sk_slot_e268(void)
{ return DAT_004eab00; }

/* FUN_0034e280 @ 0x0034e280
 * Ghidra: void FUN_0034e280(void)
 * Loads PAC-authenticated (data key B) pointer &DAT_0066dfb8 into x4.
 * Confidence: medium
 */
void sk_slot_e280(void)
{ /* adrp x16,0x66d000 ; add x16,x16,#0xfb8 ; pacda x16 ; mov x4,x16 */ }

/*============================================================================
 * 0x34e298-0x34e3fc — arithmetic/resolver and PAC getter slots
 *==========================================================================*/

/* FUN_0034e298 @ 0x0034e298
 * Ghidra: undefined1 [16] FUN_0034e298(long param_1)
 * 16-byte result: cl4_result {lo=0, hi=(param_1+0x3f)>>6} — rounds a byte count
 * up to a 64-bit word count (number of 64-bit words covering param_1).
 * Confidence: high (trivial)
 */
cl4_result_t sk_slot_e298(unsigned long n)
{ cl4_result_t r = {0, (n + 0x3f) >> 6}; return r; }

/* FUN_0034e2a8 @ 0x0034e2a8
 * Ghidra: void FUN_0034e2a8(void)
 * Packs a 24-bit value into a 3-byte little-endian field at [x19]: low 16 bits
 * as a halfword, bits 16-23 as a byte at +2.
 * Confidence: medium
 */
void sk_slot_e2a8(unsigned short lo, unsigned char hi)
{ /* strh w24,[x19] ; lsr w8,w24,#16 ; strb w8,[x19,#2] ; ret */ }

/* FUN_0034e2b8 @ 0x0034e2b8
 * Ghidra: void FUN_0034e2b8(void)
 * Loads PAC-authenticated (data key B) pointer &DAT_0066c7c0 into x4.
 * Confidence: medium
 */
void sk_slot_e2b8(void)
{ /* adrp x16,0x66c000 ; add x16,x16,#0x7c0 ; pacda x16 ; mov x4,x16 */ }

/* FUN_0034e2d0 @ 0x0034e2d0
 * Ghidra: void FUN_0034e2d0(void)
 * Loads the 16-byte value at DAT_006adf10 into x9/x8 and XORs x9 with x0
 * (rolling hash / checksum mix into the high word).
 * Confidence: low
 */
void sk_slot_e2d0(void)
{ /* adrp x8,0x6ad000 ; add x8,x8,#0xf10 ; ldp x9,x8,[x8] ; eor x9,x9,x0 ; ret */ }

/* FUN_0034e2e4 @ 0x0034e2e4
 * Ghidra: void FUN_0034e2e4(void)
 * Loads PAC-authenticated (data key B) pointer &DAT_0066cc50 into x2.
 * Confidence: medium
 */
void sk_slot_e2e4(void)
{ /* adrp x16,0x66c000 ; add x16,x16,#0xc50 ; pacda x16 ; mov x2,x16 */ }

/* FUN_0034e2fc @ 0x0034e2fc
 * Ghidra: undefined * FUN_0034e2fc(void)
 * Returns PAC-authenticated static descriptor &DAT_004ea760.
 * Confidence: medium
 */
unsigned long sk_slot_e2fc(void)
{ return DAT_004ea760; }

/* FUN_0034e314 @ 0x0034e314
 * Ghidra: undefined * FUN_0034e314(void)
 * Returns PAC-authenticated static descriptor &DAT_004e9db0.
 * Confidence: medium
 */
unsigned long sk_slot_e314(void)
{ return DAT_004e9db0; }

/* FUN_0034e32c @ 0x0034e32c
 * Ghidra: void FUN_0034e32c(void)
 * Reads back the packed 24-bit field written by 0x34e2a8: halfword at [x19]
 * OR'd with (byte at +2)<<16.
 * Confidence: medium
 */
unsigned long sk_slot_e32c(void)
{ /* ldrb w9,[x19,#2] ; ldrh w11,[x19] ; orr w9,w11,w9,LSL#16 ; ret */ return 0; }

/* FUN_0034e33c @ 0x0034e33c
 * Ghidra: void FUN_0034e33c(void)
 * Loads a pointer from the caller frame [x29-0x68], dereferences [ptr+8]
 * into x8, and returns x27 in x0.
 * Confidence: low
 */
void sk_slot_e33c(void)
{ /* ldur x9,[x29,#-0x68] ; ldr x8,[x9,#8]! ; mov x0,x27 ; ret */ }

/* FUN_0034e34c @ 0x0034e34c
 * Ghidra: void FUN_0034e34c(void)
 * Loads the PAC'd method pointer from [x10-8] into x16/x17 (method thunk).
 * Confidence: low (opaque register thunk)
 */
void sk_slot_e34c(void)
{ /* ldr x8,[x10,#-8]! ; mov x16,x8 ; mov x17,x10 ; ret */ }

/* FUN_0034e35c @ 0x0034e35c
 * Ghidra: undefined * FUN_0034e35c(void)
 * Returns PAC-authenticated static descriptor &DAT_004e8f9c.
 * Confidence: medium
 */
unsigned long sk_slot_e35c(void)
{ return DAT_004e8f9c; }

/* FUN_0034e374 @ 0x0034e374
 * Ghidra: void FUN_0034e374(void)
 * Selects a value for x3: if bit 61 of x24 is clear, x3 = bits[60:56] of x24
 * (5-bit field); else x3 = x8. (csel from ubfx/tst.)
 * Confidence: low
 */
void sk_slot_e374(void)
{ /* ubfx x9,x24,#0x38,#4 ; tst x24,#0x2000000000000000 ; csel x3,x8,x9,eq */ }

/* FUN_0034e384 @ 0x0034e384
 * Ghidra: void FUN_0034e384(void)
 * Loads PAC-authenticated (code key A) function pointer 0x1a0794 into x3.
 * Confidence: medium
 */
void sk_slot_e384(void)
{ /* adrp x16,0x1a0000 ; add x16,x16,#0x794 ; pacia x16 ; mov x3,x16 */ }

/* FUN_0034e39c @ 0x0034e39c
 * Ghidra: void FUN_0034e39c(void)
 * Loads PAC'd method pointer from [x13-8] into x16/x17.
 * Confidence: low (opaque register thunk)
 */
void sk_slot_e39c(void)
{ /* ldr x8,[x13,#-8]! ; mov x16,x8 ; mov x17,x13 ; ret */ }

/* FUN_0034e3ac @ 0x0034e3ac
 * Ghidra: void FUN_0034e3ac(void)
 * Loads PAC'd method pointer from [x19-8] into x16/x17.
 * Confidence: low (opaque register thunk)
 */
void sk_slot_e3ac(void)
{ /* ldr x8,[x19,#-8]! ; mov x16,x8 ; mov x17,x19 ; ret */ }

/* FUN_0034e3bc @ 0x0034e3bc
 * Ghidra: void FUN_0034e3bc(void)
 * Method-table slot: x0->x19; loads [x27+8] into x9.
 * Confidence: low (opaque register thunk)
 */
void sk_slot_e3bc(void)
{ /* mov x19,x0 ; mov x8,x27 ; ldr x9,[x8,#8]! ; ret */ }

/* FUN_0034e3cc @ 0x0034e3cc
 * Ghidra: void FUN_0034e3cc(void)
 * Loads PAC-authenticated (code key A) function pointer 0x1d4f4c into x2.
 * Confidence: medium
 */
void sk_slot_e3cc(void)
{ /* adrp x16,0x1d4000 ; add x16,x16,#0xf4c ; pacia x16 ; mov x2,x16 */ }

/* FUN_0034e3e4 @ 0x0034e3e4
 * Ghidra: void FUN_0034e3e4(void)
 * Loads PAC-authenticated (code key A) function pointer 0x1d4a30 into x2.
 * Confidence: medium
 */
void sk_slot_e3e4(void)
{ /* adrp x16,0x1d4000 ; add x16,x16,#0xa30 ; pacia x16 ; mov x2,x16 */ }

/* FUN_0034e3fc @ 0x0034e3fc
 * Ghidra: void FUN_0034e3fc(void)
 * Loads PAC-authenticated (data key B) pointer &DAT_0066aec8 into x3.
 * Confidence: medium
 */
void sk_slot_e3fc(void)
{ /* adrp x16,0x66a000 ; add x16,x16,#0xec8 ; pacda x16 ; mov x3,x16 */ }

/*============================================================================
 * 0x34e414-0x34e4b4 — const-return and arg-forward slots
 *==========================================================================*/

/* FUN_0034e414 @ 0x0034e414
 * Ghidra: undefined8 FUN_0034e414(void)
 * Returns 0; also x0->x2, x25->x1.
 * Confidence: low
 */
unsigned long sk_slot_e414(void)
{ /* mov x2,x0 ; mov x0,#0 ; mov x1,x25 ; ret */ return 0; }

/* FUN_0034e424 @ 0x0034e424
 * Ghidra: void FUN_0034e424(void)
 * Stores constants to caller frame: w8=1 -> [sp+0x10], x3 -> [sp+0x8].
 * Confidence: low
 */
void sk_slot_e424(void)
{ /* mov w8,#1 ; str w8,[sp,#0x10] ; str x3,[sp,#0x8] ; ret */ }

/* FUN_0034e434 @ 0x0034e434
 * Ghidra: void FUN_0034e434(void)
 * Method-table slot: x27->x20/x2, x22->x3.
 * Confidence: low (opaque register thunk)
 */
void sk_slot_e434(void)
{ /* mov x20,x27 ; mov x2,x27 ; mov x3,x22 ; ret */ }

/* FUN_0034e444 @ 0x0034e444
 * Ghidra: void FUN_0034e444(void)
 * Method-table slot: x27->x20, x28->x0, x26->x1.
 * Confidence: low (opaque register thunk)
 */
void sk_slot_e444(void)
{ /* mov x20,x27 ; mov x0,x28 ; mov x1,x26 ; ret */ }

/* FUN_0034e454 @ 0x0034e454
 * Ghidra: void FUN_0034e454(void)
 * Method-table slot: x26->x20, x22->x0, x25->x1.
 * Confidence: low (opaque register thunk)
 */
void sk_slot_e454(void)
{ /* mov x20,x26 ; mov x0,x22 ; mov x1,x25 ; ret */ }

/* FUN_0034e464 @ 0x0034e464
 * Ghidra: void FUN_0034e464(void)
 * Method-table slot: x24->x0, x22->x1, x19->x2.
 * Confidence: low (opaque register thunk)
 */
void sk_slot_e464(void)
{ /* mov x0,x24 ; mov x1,x22 ; mov x2,x19 ; ret */ }

/* FUN_0034e474 @ 0x0034e474
 * Ghidra: void FUN_0034e474(void)
 * Method-table slot: x24->x0, x22->x1, x21->x2.
 * Confidence: low (opaque register thunk)
 */
void sk_slot_e474(void)
{ /* mov x0,x24 ; mov x1,x22 ; mov x2,x21 ; ret */ }

/* FUN_0034e484 @ 0x0034e484
 * Ghidra: void FUN_0034e484(void)
 * Method-table slot: x24->x0, x20->x1, x23->x2.
 * Confidence: low (opaque register thunk)
 */
void sk_slot_e484(void)
{ /* mov x0,x24 ; mov x1,x20 ; mov x2,x23 ; ret */ }

/* FUN_0034e494 @ 0x0034e494
 * Ghidra: void FUN_0034e494(void)
 * Method-table slot: x26->x2, x22->x20/x3.
 * Confidence: low (opaque register thunk)
 */
void sk_slot_e494(void)
{ /* mov x2,x26 ; mov x20,x22 ; mov x3,x22 ; ret */ }

/* FUN_0034e4a4 @ 0x0034e4a4
 * Ghidra: void FUN_0034e4a4(void)
 * Method-table slot: loads [x8+0x10] into x9; x21->x0, x22->x1.
 * Confidence: low (opaque register thunk)
 */
void sk_slot_e4a4(void)
{ /* ldr x9,[x8,#0x10]! ; mov x0,x21 ; mov x1,x22 ; ret */ }

/* FUN_0034e4b4 @ 0x0034e4b4
 * Ghidra: undefined * FUN_0034e4b4(void)
 * Returns PAC-authenticated static descriptor &DAT_004e8b7c.
 * Confidence: medium
 */
unsigned long sk_slot_e4b4(void)
{ return DAT_004e8b7c; }

/*============================================================================
 * 0x34e4cc-0x34e578 — arg-forward thunk run (method table continuation)
 *==========================================================================*/

/* FUN_0034e4cc @ 0x0034e4cc
 * Ghidra: void FUN_0034e4cc(void)
 * Method-table slot: x19->x20/x1, x26->x2.
 * Confidence: low (opaque register thunk)
 */
void sk_slot_e4cc(void)
{ /* mov x20,x19 ; mov x1,x19 ; mov x2,x26 ; ret */ }

/* FUN_0034e4dc @ 0x0034e4dc
 * Ghidra: void FUN_0034e4dc(void)
 * Method-table slot: x19->x20/x3, x25->x4.
 * Confidence: low (opaque register thunk)
 */
void sk_slot_e4dc(void)
{ /* mov x20,x19 ; mov x3,x19 ; mov x4,x25 ; ret */ }

/* FUN_0034e4ec @ 0x0034e4ec
 * Ghidra: void FUN_0034e4ec(void)
 * Method-table slot: x2->x23, x1->x24, x0->x25 (reverse spill).
 * Confidence: low (opaque register thunk)
 */
void sk_slot_e4ec(void)
{ /* mov x23,x2 ; mov x24,x1 ; mov x25,x0 ; ret */ }

/* FUN_0034e4fc @ 0x0034e4fc
 * Ghidra: void FUN_0034e4fc(void)
 * Method-table slot: x21->x20/x1, x24->x2.
 * Confidence: low (opaque register thunk)
 */
void sk_slot_e4fc(void)
{ /* mov x20,x21 ; mov x1,x21 ; mov x2,x24 ; ret */ }

/* FUN_0034e50c @ 0x0034e50c
 * Ghidra: void FUN_0034e50c(void)
 * Method-table slot: x21->x20, x19->x0, x22->x1.
 * Confidence: low (opaque register thunk)
 */
void sk_slot_e50c(void)
{ /* mov x20,x21 ; mov x0,x19 ; mov x1,x22 ; ret */ }

/* FUN_0034e51c @ 0x0034e51c
 * Ghidra: void FUN_0034e51c(void)
 * Method-table slot: x23->x1, x19->x2, x21->x3.
 * Confidence: low (opaque register thunk)
 */
void sk_slot_e51c(void)
{ /* mov x1,x23 ; mov x2,x19 ; mov x3,x21 ; ret */ }

/* FUN_0034e52c @ 0x0034e52c
 * Ghidra: void FUN_0034e52c(void)
 * Method-table slot: x23->x0, x21->x1, x22->x2.
 * Confidence: low (opaque register thunk)
 */
void sk_slot_e52c(void)
{ /* mov x0,x23 ; mov x1,x21 ; mov x2,x22 ; ret */ }

/* FUN_0034e53c @ 0x0034e53c
 * Ghidra: void FUN_0034e53c(void)
 * Method-table slot: x23->x0, x19->x1, x22->x2.
 * Confidence: low (opaque register thunk)
 */
void sk_slot_e53c(void)
{ /* mov x0,x23 ; mov x1,x19 ; mov x2,x22 ; ret */ }

/* FUN_0034e54c @ 0x0034e54c
 * Ghidra: void FUN_0034e54c(void)
 * Method-table slot: x25->x0, x27->x1, x23->x2.
 * Confidence: low (opaque register thunk)
 */
void sk_slot_e54c(void)
{ /* mov x0,x25 ; mov x1,x27 ; mov x2,x23 ; ret */ }

/* FUN_0034e55c @ 0x0034e55c
 * Ghidra: void FUN_0034e55c(void)
 * Method-table slot: x25->x0, x24->x1, x23->x2.
 * Confidence: low (opaque register thunk)
 */
void sk_slot_e55c(void)
{ /* mov x0,x25 ; mov x1,x24 ; mov x2,x23 ; ret */ }

/* FUN_0034e56c @ 0x0034e56c
 * Ghidra: void FUN_0034e56c(void)
 * Method-table slot: x25->x0, x20->x1, x19->x2.
 * Confidence: low (opaque register thunk)
 */
void sk_slot_e56c(void)
{ /* mov x0,x25 ; mov x1,x20 ; mov x2,x19 ; ret */ }

/*============================================================================
 * 0x34e57c-0x34e6cc — result builders and thunks
 *==========================================================================*/

/* FUN_0034e57c @ 0x0034e57c
 * Ghidra: undefined1 [16] FUN_0034e57c(ulong param_1)
 * 16-byte result: cl4_result {lo=0, hi=param_1}.
 * Confidence: high (trivial)
 */
cl4_result_t sk_slot_e57c(unsigned long v)
{ cl4_result_t r = {0, v}; return r; }

/* FUN_0034e58c @ 0x0034e58c
 * Ghidra: undefined1 [16] FUN_0034e58c(void)
 * Frame-walking bootstrap: builds a 16-byte result from two caller-frame words
 * ([x29-0x138] and x29-0x130), sets up x2/x4/x5 from a static base
 * (0x677000+0x880) and callee-saved regs. Complex tail-call prelude.
 * Confidence: low
 */
cl4_result_t sk_slot_e58c(void)
{ cl4_result_t r = {0, 0}; return r; }

/* FUN_0034e5bc @ 0x0034e5bc
 * Ghidra: void FUN_0034e5bc(void)
 * Method-table slot: x24->x1, x25->x2, x26->x3.
 * Confidence: low (opaque register thunk)
 */
void sk_slot_e5bc(void)
{ /* mov x1,x24 ; mov x2,x25 ; mov x3,x26 ; ret */ }

/* FUN_0034e5cc @ 0x0034e5cc
 * Ghidra: void FUN_0034e5cc(void)
 * Method-table slot: x27->x0, x28->x1, x22->x2.
 * Confidence: low (opaque register thunk)
 */
void sk_slot_e5cc(void)
{ /* mov x0,x27 ; mov x1,x28 ; mov x2,x22 ; ret */ }

/* FUN_0034e5dc @ 0x0034e5dc
 * Ghidra: void FUN_0034e5dc(void)
 * Method-table slot: x0->x20; loads [x29-0x60] then [ptr+8] into x9.
 * Confidence: low (opaque register thunk)
 */
void sk_slot_e5dc(void)
{ /* mov x20,x0 ; ldur x8,[x29,#-0x60] ; ldr x9,[x8,#8]! ; ret */ }

/* FUN_0034e5ec @ 0x0034e5ec
 * Ghidra: void FUN_0034e5ec(void)
 * Method-table slot: x24->x20, x21->x0, x26->x1.
 * Confidence: low (opaque register thunk)
 */
void sk_slot_e5ec(void)
{ /* mov x20,x24 ; mov x0,x21 ; mov x1,x26 ; ret */ }

/* FUN_0034e5fc @ 0x0034e5fc
 * Ghidra: void FUN_0034e5fc(void)
 * Method-table slot: x24->x20/x2, x22->x3.
 * Confidence: low (opaque register thunk)
 */
void sk_slot_e5fc(void)
{ /* mov x20,x24 ; mov x2,x24 ; mov x3,x22 ; ret */ }

/* FUN_0034e60c @ 0x0034e60c
 * Ghidra: void FUN_0034e60c(void)
 * Method-table slot: x0->x8, x26->x0, x28->x1.
 * Confidence: low (opaque register thunk)
 */
void sk_slot_e60c(void)
{ /* mov x8,x0 ; mov x0,x26 ; mov x1,x28 ; ret */ }

/* FUN_0034e61c @ 0x0034e61c
 * Ghidra: void FUN_0034e61c(void)
 * Method-table slot: x0->x8, x25->x0, x28->x1.
 * Confidence: low (opaque register thunk)
 */
void sk_slot_e61c(void)
{ /* mov x8,x0 ; mov x0,x25 ; mov x1,x28 ; ret */ }

/* FUN_0034e62c @ 0x0034e62c
 * Ghidra: void FUN_0034e62c(void)
 * Method-table slot: x0->x8, x26->x20, x19->x0.
 * Confidence: low (opaque register thunk)
 */
void sk_slot_e62c(void)
{ /* mov x8,x0 ; mov x20,x26 ; mov x0,x19 ; ret */ }

/* FUN_0034e63c @ 0x0034e63c
 * Ghidra: void FUN_0034e63c(void)
 * Method-table slot: x0->x8, x23->x20, x22->x0.
 * Confidence: low (opaque register thunk)
 */
void sk_slot_e63c(void)
{ /* mov x8,x0 ; mov x20,x23 ; mov x0,x22 ; ret */ }

/* FUN_0034e64c @ 0x0034e64c
 * Ghidra: void FUN_0034e64c(void)
 * Method-table slot: x0->x8, x21->x0, x24->x1.
 * Confidence: low (opaque register thunk)
 */
void sk_slot_e64c(void)
{ /* mov x8,x0 ; mov x0,x21 ; mov x1,x24 ; ret */ }

/* FUN_0034e65c @ 0x0034e65c
 * Ghidra: void FUN_0034e65c(void)
 * Method-table slot: x0->x8, x27->x0, x23->x1.
 * Confidence: low (opaque register thunk)
 */
void sk_slot_e65c(void)
{ /* mov x8,x0 ; mov x0,x27 ; mov x1,x23 ; ret */ }

/* FUN_0034e66c @ 0x0034e66c
 * Ghidra: void FUN_0034e66c(void)
 * Method-table slot: x0->x8, x27->x0, x25->x1.
 * Confidence: low (opaque register thunk)
 */
void sk_slot_e66c(void)
{ /* mov x8,x0 ; mov x0,x27 ; mov x1,x25 ; ret */ }

/* FUN_0034e67c @ 0x0034e67c
 * Ghidra: undefined1 [16] FUN_0034e67c(ulong param_1)
 * 16-byte result: cl4_result {lo=0, hi=param_1}.
 * Confidence: high (trivial)
 */
cl4_result_t sk_slot_e67c(unsigned long v)
{ cl4_result_t r = {0, v}; return r; }

/* FUN_0034e68c @ 0x0034e68c
 * Ghidra: void FUN_0034e68c(void)
 * Method-table slot: x22->x0, w1=1, w2=1 (constant selectors).
 * Confidence: low (opaque register thunk)
 */
void sk_slot_e68c(void)
{ /* mov x0,x22 ; mov w1,#1 ; mov w2,#1 ; ret */ }

/* FUN_0034e69c @ 0x0034e69c
 * Ghidra: void FUN_0034e69c(void)
 * Method-table slot: x22->x0, x23->x1, x19->x2.
 * Confidence: low (opaque register thunk)
 */
void sk_slot_e69c(void)
{ /* mov x0,x22 ; mov x1,x23 ; mov x2,x19 ; ret */ }

/* FUN_0034e6ac @ 0x0034e6ac
 * Ghidra: void FUN_0034e6ac(void)
 * Method-table slot: x22->x0, x25->x1, x19->x2.
 * Confidence: low (opaque register thunk)
 */
void sk_slot_e6ac(void)
{ /* mov x0,x22 ; mov x1,x25 ; mov x2,x19 ; ret */ }

/* FUN_0034e6bc @ 0x0034e6bc
 * Ghidra: void FUN_0034e6bc(void)
 * Method-table slot: x22->x1, x23->x2, x21->x3.
 * Confidence: low (opaque register thunk)
 */
void sk_slot_e6bc(void)
{ /* mov x1,x22 ; mov x2,x23 ; mov x3,x21 ; ret */ }

/* FUN_0034e6cc @ 0x0034e6cc
 * Ghidra: void FUN_0034e6cc(void)
 * Stack-switch bootstrap: stores x9 to [x29-0xf0], installs sp=x9, restores
 * x9 from x8. Used to hop onto a fresh stack.
 * Confidence: low
 */
void sk_slot_e6cc(void)
{ /* stur x9,[x29,#-0xf0] ; mov sp,x9 ; mov x9,x8 ; ret */ }

/*============================================================================
 * 0x34e6dc-0x34e748 — const-return and forward slots
 *==========================================================================*/

/* FUN_0034e6dc @ 0x0034e6dc
 * Ghidra: undefined8 FUN_0034e6dc(void)
 * Returns 0 (x0=0); x21->x1, x24->x3.
 * Confidence: low
 */
unsigned long sk_slot_e6dc(void)
{ /* mov x0,#0 ; mov x1,x21 ; mov x3,x24 ; ret */ return 0; }

/* FUN_0034e6ec @ 0x0034e6ec
 * Ghidra: undefined8 FUN_0034e6ec(void)
 * Returns 0 (x0=0); x21->x1, x23->x2.
 * Confidence: low
 */
unsigned long sk_slot_e6ec(void)
{ /* mov x0,#0 ; mov x1,x21 ; mov x2,x23 ; ret */ return 0; }

/* FUN_0034e6fc @ 0x0034e6fc
 * Ghidra: undefined8 FUN_0034e6fc(void)
 * Returns 0 (x0=0); x23->x1, x19->x2.
 * Confidence: low
 */
unsigned long sk_slot_e6fc(void)
{ /* mov x0,#0 ; mov x1,x23 ; mov x2,x19 ; ret */ return 0; }

/* FUN_0034e70c @ 0x0034e70c
 * Ghidra: undefined8 FUN_0034e70c(void)
 * Returns 0 (x0=0); x20->x1, x19->x2.
 * Confidence: low
 */
unsigned long sk_slot_e70c(void)
{ /* mov x0,#0 ; mov x1,x20 ; mov x2,x19 ; ret */ return 0; }

/* FUN_0034e71c @ 0x0034e71c
 * Ghidra: void FUN_0034e71c(void)
 * Method-table slot: x0->x9, x26->x8, x28->x0.
 * Confidence: low (opaque register thunk)
 */
void sk_slot_e71c(void)
{ /* mov x9,x0 ; mov x8,x26 ; mov x0,x28 ; ret */ }

/* FUN_0034e72c @ 0x0034e72c
 * Ghidra: void FUN_0034e72c(void)
 * Method-table slot: x0->x9, x25->x8, x21->x0.
 * Confidence: low (opaque register thunk)
 */
void sk_slot_e72c(void)
{ /* mov x9,x0 ; mov x8,x25 ; mov x0,x21 ; ret */ }

/* FUN_0034e73c @ 0x0034e73c
 * Ghidra: undefined8 FUN_0034e73c(undefined8,undefined8,undefined8)
 * Method-table slot: x1->x19, x0->x20, returns x2 (param_3).
 * Confidence: low (opaque register thunk)
 */
unsigned long sk_slot_e73c(unsigned long a, unsigned long b, unsigned long c)
{ /* mov x19,x1 ; mov x20,x0 ; mov x0,x2 ; ret */ return c; }

/*============================================================================
 * 0x34e74c-0x34e7c0 — field-offset resolver slots
 *==========================================================================*/

/* FUN_0034e74c @ 0x0034e74c
 * Ghidra: void FUN_0034e74c(void)
 * Resolves the +0xc field offset of x28 via FUN_0008f758; result in x9.
 * Confidence: medium
 */
void sk_slot_e74c(unsigned long obj)
{ sk_field_off_0c(obj); }

/* FUN_0034e768 @ 0x0034e768
 * Ghidra: void FUN_0034e768(void)
 * Resolves the +0x30 field offset of x22 via FUN_00310a74; result in x19.
 * Confidence: medium
 */
void sk_slot_e768(unsigned long obj)
{ sk_field_off_30(obj); }

/* FUN_0034e784 @ 0x0034e784
 * Ghidra: void FUN_0034e784(void)
 * Resolves the +0xc field offset of x19 via FUN_0008f758; result in x9.
 * Confidence: medium
 */
void sk_slot_e784(unsigned long obj)
{ sk_field_off_0c(obj); }

/* FUN_0034e7a0 @ 0x0034e7a0
 * Ghidra: void FUN_0034e7a0(void)
 * Two-step resolver: calls FUN_0006a4c0 (metadata-kind, result->x20) then
 * FUN_000a649c (+0x14 field offset of x25, result->x9).
 * Confidence: medium
 */
void sk_slot_e7a0(unsigned long a, unsigned long b)
{ sk_meta_kind(a); sk_field_off_14(b); }

/*============================================================================
 * 0x34e7e0-0x34e81c — tail slots (const returns + NEON helper)
 *==========================================================================*/

/* FUN_0034e7e0 @ 0x0034e7e0
 * Ghidra: undefined8 FUN_0034e7e0(void)
 * Returns 0; also sets x4 = &DAT_00611b24 + 0x18 (side pointer).
 * Confidence: medium
 */
unsigned long sk_slot_e7e0(void)
{ return 0; }

/* FUN_0034e7f4 @ 0x0034e7f4
 * Ghidra: undefined2 FUN_0034e7f4(undefined1[16],undefined1[16],undefined1[16])
 * NEON lane helper: computes, per 32-bit lane, (b_lane < a_lane) as an
 * unsigned mask, narrows the four masks to 16-bit, and returns the unsigned
 * maximum across the lanes. Used for saturated unsigned comparison of two
 * 128-bit operands.
 * Confidence: high (NEON_ext structure recovered from disassembly)
 */
uint32_t sk_neon_lane_max(unsigned long a_lo, unsigned long a_hi,
                          unsigned long b_lo, unsigned long b_hi)
{
    uint32_t m = 0;
    /* cmhi v0.4S,v2.4S,v0.4S  (b > a per lane) ; uzp1 ; umaxv h0 ; fmov w8 */
    uint32_t a[4] = { (uint32_t)a_lo, (uint32_t)(a_lo >> 32),
                      (uint32_t)a_hi, (uint32_t)(a_hi >> 32) };
    uint32_t b[4] = { (uint32_t)b_lo, (uint32_t)(b_lo >> 32),
                      (uint32_t)b_hi, (uint32_t)(b_hi >> 32) };
    for (int i = 0; i < 4; i++)
        m |= (b[i] > a[i]) ? 0xffffu : 0u;
    return m;
}

/* FUN_0034e808 @ 0x0034e808
 * Ghidra: undefined8 FUN_0034e808(void)
 * Returns 0; also sets x4 = &DAT_0060e208 + 0x28 (side pointer).
 * Confidence: medium
 */
unsigned long sk_slot_e808(void)
{ return 0; }

/* FUN_0034e81c @ 0x0034e81c
 * Ghidra: undefined8 FUN_0034e81c(void)
 * Returns 0xff (constant error/status sentinel); also sets
 * x4 = &DAT_00611b24 + 0x10.
 * Confidence: medium
 */
unsigned long sk_slot_e81c(void)
{ return 0xff; }
