/* Recreated from ringminus1/sk/cl4_kernel.raw (cL4 Secure Kernel, arm64e,
 * image base 0) — the cL4 microkernel (GL1), "cL4 (679.100.61)".
 * Ground truth: Ghidra FUN_ names + addresses in program cl4_kernel.raw.
 * Slice 12: 0x34af04-0x34c034 syscall/exception-entry region — a dense table
 * of small per-syscall stub/handler entry points. Most slots are no-ops or thin
 * wrappers around out-of-slice helpers; the bodies are faithful to the decompile.
 * All names are estimates unless string/header-matched. Uses seL4/cL4 vocabulary. */

#include <stdint.h>
#include <stddef.h>
#include "sk_internal.h"

/* 16-byte (lo,hi) vector used by the double-register (x0/x1) returns. */
typedef struct { uint64_t lo; uint64_t hi; } sk_u128_t;

/* ------------------------------------------------------------------ *
 * Out-of-slice cL4 helper declarations (bodies reconstructed by the range
 * worker that owns each address; declared here for linkage).
 * ------------------------------------------------------------------ */
extern void sk_tagged_deref_lo(uint64_t);   /* FUN_00310ad4 — tagged-pointer deref resolver (arg dropped) */
extern void sk_tagged_deref_hi(uint64_t);   /* FUN_00027754 — tagged-pointer deref resolver (arg dropped) */
extern void sk_callee_0016186c(uint64_t);   /* FUN_0016186c — out-of-slice helper */
extern void sk_callee_003109b4(uint64_t);   /* FUN_003109b4 — out-of-slice helper */
extern void sk_callee_00291ee0(uint64_t);   /* FUN_00291ee0 — out-of-slice helper */
extern void sk_callee_000839f8(uint64_t, ...);   /* FUN_000839f8 — out-of-slice helper (variadic: args dropped at one site) */
extern void sk_callee_0006a4c0(uint64_t);   /* FUN_0006a4c0 — out-of-slice helper */
extern void sk_callee_0008f728(uint64_t);   /* FUN_0008f728 — out-of-slice helper */
extern void sk_callee_0008f6c0(uint64_t);   /* FUN_0008f6c0 — out-of-slice helper */
extern uint64_t sk_callee_0008f6f4(uint64_t);   /* FUN_0008f6f4 — out-of-slice helper (returns a value) */
extern void sk_callee_0031a60c(uint64_t);   /* FUN_0031a60c — out-of-slice helper */
extern void sk_callee_0031a17c(uint64_t);   /* FUN_0031a17c — out-of-slice helper */
extern void sk_callee_00377824(uint64_t, uint64_t, uint64_t, void (*)(void), void (*)(void));   /* FUN_00377824 — out-of-slice register/callback helper */
extern void sk_callee_000839d8(uint64_t);   /* FUN_000839d8 — out-of-slice helper */
extern void sk_callee_00310a44(uint64_t);   /* FUN_00310a44 — out-of-slice helper */
extern void sk_callee_00310a74(uint64_t);   /* FUN_00310a74 — out-of-slice helper */
extern void sk_callee_0001df60(uint64_t);   /* FUN_0001df60 — out-of-slice helper */
extern void sk_callee_0017e880(uint64_t);   /* FUN_0017e880 — out-of-slice helper */
extern void sk_callee_0008e5d8(uint64_t);   /* FUN_0008e5d8 — out-of-slice helper */
extern void sk_callee_0060e3fc(void);   /* FUN_0060e3fc — out-of-slice callback (passed as fn ptr) */
extern void sk_callee_0060e40c(void);   /* FUN_0060e40c — out-of-slice callback (passed as fn ptr) */

/* Out-of-slice global data tables referenced by getters below. */
extern uint8_t sk_data_004c1010[];   /* DAT_004c1010 — FUN region data table */
extern uint8_t sk_data_004e4980[];   /* DAT_004e4980 — global data */
extern uint8_t sk_data_004e8c24[];   /* DAT_004e8c24 — global data */
extern uint8_t sk_data_004e8f64[];   /* DAT_004e8f64 — global data */
extern uint8_t sk_data_004e9d20[];   /* DAT_004e9d20 — global data */
extern uint8_t sk_data_004ec2e0[];   /* DAT_004ec2e0 — global data */
extern uint8_t sk_data_004edcd0[];   /* DAT_004edcd0 — global data */
extern uint8_t sk_data_004edd94[];   /* DAT_004edd94 — global data */
extern uint8_t sk_data_004f1754[];   /* DAT_004f1754 — global data */
extern uint8_t sk_data_005ce788[];   /* DAT_005ce788 — global data */

/* FUN_0034af04(void) @ 0x0034af04   (est. sk_callee_call_00310ad4)
 * Ghidra: FUN_0034af04(void)
 * Thin wrapper invoking out-of-slice helper(s); args dropped by decompiler where empty.
 * Confidence: medium
 * Notes: Thin wrapper invoking out-of-slice helper(s); args dropped by decompiler where empty. */
void sk_callee_call_00310ad4_af04(void)
{
    sk_tagged_deref_lo(0);
    sk_tagged_deref_hi(0);
    return;
}

/* FUN_0034af20(void) @ 0x0034af20   (est. sk_noop_handler)
 * Ghidra: FUN_0034af20(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_af20(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034af30(void) @ 0x0034af30   (est. sk_noop_handler)
 * Ghidra: FUN_0034af30(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_af30(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034af48(void) @ 0x0034af48   (est. sk_noop_handler)
 * Ghidra: FUN_0034af48(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_af48(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034af60(undefined8 param_1,undefined8 param_2,undefined8 param_3) @ 0x0034af60   (est. sk_u128_builder)
 * Ghidra: FUN_0034af60(undefined8 param_1,undefined8 param_2,undefined8 param_3)
 * Builds and returns a 16-byte (lo,hi) vector (data pointer + length/flag).
 * Confidence: medium
 * Notes: Builds a 16-byte (lo,hi) result from data pointer and length. */
sk_u128_t sk_u128_builder_af60(uint64_t arg1, uint64_t arg2, uint64_t arg3)
{
    sk_callee_0031a60c(arg3);
    sk_u128_t r;
    r.lo = (uint64_t)(arg1);
    r.hi = (uint64_t)(arg2);
    return r;
}

/* FUN_0034afa0(void) @ 0x0034afa0   (est. sk_callee_call_0016186c)
 * Ghidra: FUN_0034afa0(void)
 * Thin wrapper invoking out-of-slice helper(s); args dropped by decompiler where empty.
 * Confidence: medium
 * Notes: Thin wrapper invoking out-of-slice helper(s); args dropped by decompiler where empty. */
void sk_callee_call_0016186c_afa0(void)
{
    sk_callee_0016186c(0);
    return;
}

/* FUN_0034afc0(void) @ 0x0034afc0   (est. sk_callee_call_00310ad4)
 * Ghidra: FUN_0034afc0(void)
 * Thin wrapper invoking out-of-slice helper(s); args dropped by decompiler where empty.
 * Confidence: medium
 * Notes: Thin wrapper invoking out-of-slice helper(s); args dropped by decompiler where empty. */
void sk_callee_call_00310ad4_afc0(void)
{
    sk_tagged_deref_lo(0);
    sk_tagged_deref_hi(0);
    sk_callee_0016186c(0);
    return;
}

/* FUN_0034afe4(void) @ 0x0034afe4   (est. sk_noop_handler)
 * Ghidra: FUN_0034afe4(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_afe4(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034affc(void) @ 0x0034affc   (est. sk_noop_handler)
 * Ghidra: FUN_0034affc(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_affc(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034b014(void) @ 0x0034b014   (est. sk_noop_handler)
 * Ghidra: FUN_0034b014(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_b014(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034b02c(void) @ 0x0034b02c   (est. sk_noop_handler)
 * Ghidra: FUN_0034b02c(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_b02c(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034b044(undefined8 *param_1,undefined8 *param_2) @ 0x0034b044   (est. sk_word_copy)
 * Ghidra: FUN_0034b044(undefined8 *param_1,undefined8 *param_2)
 * Copies one 8-byte word from the source to the destination pointer.
 * Confidence: medium
 * Notes: Word copy (8 bytes) from source to destination. */
void sk_word_copy_b044(uint64_t *dst, uint64_t *src)
{
    *dst = *src;    /* copy one 8-byte word */
    return;
}

/* FUN_0034b05c(void) @ 0x0034b05c   (est. sk_noop_handler)
 * Ghidra: FUN_0034b05c(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_b05c(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034b06c(void) @ 0x0034b06c   (est. sk_noop_handler)
 * Ghidra: FUN_0034b06c(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_b06c(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034b07c(void) @ 0x0034b07c   (est. sk_noop_handler)
 * Ghidra: FUN_0034b07c(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_b07c(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034b08c(void) @ 0x0034b08c   (est. sk_callee_call_003109b4)
 * Ghidra: FUN_0034b08c(void)
 * Thin wrapper invoking out-of-slice helper(s); args dropped by decompiler where empty.
 * Confidence: medium
 * Notes: Thin wrapper invoking out-of-slice helper(s); args dropped by decompiler where empty. */
void sk_callee_call_003109b4_b08c(void)
{
    sk_callee_003109b4(0);
    return;
}

/* FUN_0034b0b4(void) @ 0x0034b0b4   (est. sk_return_zero)
 * Ghidra: FUN_0034b0b4(void)
 * Returns the constant zero.
 * Confidence: medium
 * Notes: undefined8 constant-zero return. */
uint64_t sk_return_zero_b0b4(void)
{
    return 0;
}

/* FUN_0034b0c4(void) @ 0x0034b0c4   (est. sk_noop_handler)
 * Ghidra: FUN_0034b0c4(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_b0c4(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034b0d4(void) @ 0x0034b0d4   (est. sk_noop_handler)
 * Ghidra: FUN_0034b0d4(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_b0d4(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034b0e4(void) @ 0x0034b0e4   (est. sk_return_zero)
 * Ghidra: FUN_0034b0e4(void)
 * Returns the constant zero.
 * Confidence: medium
 * Notes: undefined8 constant-zero return. */
uint64_t sk_return_zero_b0e4(void)
{
    return 0;
}

/* FUN_0034b100(void) @ 0x0034b100   (est. sk_noop_handler)
 * Ghidra: FUN_0034b100(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_b100(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034b114(void) @ 0x0034b114   (est. sk_noop_handler)
 * Ghidra: FUN_0034b114(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_b114(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034b128(void) @ 0x0034b128   (est. sk_noop_handler)
 * Ghidra: FUN_0034b128(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_b128(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034b13c(void) @ 0x0034b13c   (est. sk_noop_handler)
 * Ghidra: FUN_0034b13c(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_b13c(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034b150(void) @ 0x0034b150   (est. sk_noop_handler)
 * Ghidra: FUN_0034b150(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_b150(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034b164(void) @ 0x0034b164   (est. sk_return_zero)
 * Ghidra: FUN_0034b164(void)
 * Returns the constant zero.
 * Confidence: medium
 * Notes: undefined8 constant-zero return. */
uint64_t sk_return_zero_b164(void)
{
    return 0;
}

/* FUN_0034b178(void) @ 0x0034b178   (est. sk_u128_builder)
 * Ghidra: FUN_0034b178(void)
 * Builds and returns a 16-byte (lo,hi) vector (data pointer + length/flag).
 * Confidence: medium
 * Notes: Builds a 16-byte (lo,hi) result from data pointer and length. */
sk_u128_t sk_u128_builder_b178(void)
{
    sk_u128_t r;
    r.lo = (uint64_t)(sk_data_005ce788);
    r.hi = (uint64_t)(1);
    return r;
}

/* FUN_0034b18c(void) @ 0x0034b18c   (est. sk_noop_handler)
 * Ghidra: FUN_0034b18c(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_b18c(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034b1a0(void) @ 0x0034b1a0   (est. sk_callee_call_00291ee0)
 * Ghidra: FUN_0034b1a0(void)
 * Thin wrapper invoking out-of-slice helper(s); args dropped by decompiler where empty.
 * Confidence: medium
 * Notes: Thin wrapper invoking out-of-slice helper(s); args dropped by decompiler where empty. */
void sk_callee_call_00291ee0_b1a0(void)
{
    sk_callee_00291ee0(0);
    return;
}

/* FUN_0034b1c0(void) @ 0x0034b1c0   (est. sk_data_getter_004f1754)
 * Ghidra: FUN_0034b1c0(void)
 * Returns address of global data DAT_004f1754.
 * Confidence: medium
 * Notes: Returns address of global data DAT_004f1754. */
uint8_t * sk_data_getter_004f1754_b1c0(void)
{
    return (uint8_t *)sk_data_004f1754;
}

/* FUN_0034b1dc(void) @ 0x0034b1dc   (est. sk_noop_handler)
 * Ghidra: FUN_0034b1dc(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_b1dc(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034b1f0(void) @ 0x0034b1f0   (est. sk_noop_handler)
 * Ghidra: FUN_0034b1f0(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_b1f0(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034b204(void) @ 0x0034b204   (est. sk_noop_handler)
 * Ghidra: FUN_0034b204(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_b204(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034b214(void) @ 0x0034b214   (est. sk_noop_handler)
 * Ghidra: FUN_0034b214(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_b214(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034b228(void) @ 0x0034b228   (est. sk_noop_handler)
 * Ghidra: FUN_0034b228(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_b228(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034b23c(void) @ 0x0034b23c   (est. sk_noop_handler)
 * Ghidra: FUN_0034b23c(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_b23c(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034b250(long param_1) @ 0x0034b250   (est. sk_degen_frame_op)
 * Ghidra: FUN_0034b250(long param_1)
 * Degenerate body: the decompiler lost register/stack flow (unaff_* / in_* operands); the raw decompile statements are preserved as comments.
 * Confidence: low
 * Notes: Decompiler lost register/stack flow (unaff_* / in_* operands); body rendered as annotation. */
void sk_degen_frame_op_b250(int64_t arg1)
{
    /* *(long *)(unaff_x29 + -200) = (long)&stack0x00000000 - arg1; */
    /* return; */
    return;
}

/* FUN_0034b264(undefined8 *param_1,undefined8 *param_2) @ 0x0034b264   (est. sk_word_copy)
 * Ghidra: FUN_0034b264(undefined8 *param_1,undefined8 *param_2)
 * Copies one 8-byte word from the source to the destination pointer.
 * Confidence: medium
 * Notes: Word copy (8 bytes) from source to destination. */
void sk_word_copy_b264(uint64_t *dst, uint64_t *src)
{
    *dst = *src;    /* copy one 8-byte word */
    return;
}

/* FUN_0034b278(void) @ 0x0034b278   (est. sk_noop_handler)
 * Ghidra: FUN_0034b278(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_b278(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034b288(void) @ 0x0034b288   (est. sk_callee_call_00310ad4)
 * Ghidra: FUN_0034b288(void)
 * Thin wrapper invoking out-of-slice helper(s); args dropped by decompiler where empty.
 * Confidence: medium
 * Notes: Thin wrapper invoking out-of-slice helper(s); args dropped by decompiler where empty. */
void sk_callee_call_00310ad4_b288(void)
{
    sk_tagged_deref_lo(0);
    sk_tagged_deref_hi(0);
    return;
}

/* FUN_0034b2a8(undefined4 param_1) @ 0x0034b2a8   (est. sk_callee_call_000839f8)
 * Ghidra: FUN_0034b2a8(undefined4 param_1)
 * Thin wrapper invoking out-of-slice helper(s); args dropped by decompiler where empty.
 * Confidence: medium
 * Notes: Thin wrapper invoking out-of-slice helper(s); args dropped by decompiler where empty. */
void sk_callee_call_000839f8_b2a8(uint32_t arg1)
{
    sk_callee_000839f8(arg1,1);
    return;
}

/* FUN_0034b2c8(undefined4 param_1) @ 0x0034b2c8   (est. sk_callee_call_000839f8)
 * Ghidra: FUN_0034b2c8(undefined4 param_1)
 * Thin wrapper invoking out-of-slice helper(s); args dropped by decompiler where empty.
 * Confidence: medium
 * Notes: Thin wrapper invoking out-of-slice helper(s); args dropped by decompiler where empty. */
void sk_callee_call_000839f8_b2c8(uint32_t arg1)
{
    sk_callee_000839f8(arg1,1);
    return;
}

/* FUN_0034b2e8(void) @ 0x0034b2e8   (est. sk_return_zero)
 * Ghidra: FUN_0034b2e8(void)
 * Returns the constant zero.
 * Confidence: medium
 * Notes: undefined8 constant-zero return. */
uint64_t sk_return_zero_b2e8(void)
{
    return 0;
}

/* FUN_0034b2f8(void) @ 0x0034b2f8   (est. sk_noop_handler)
 * Ghidra: FUN_0034b2f8(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_b2f8(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034b308(void) @ 0x0034b308   (est. sk_noop_handler)
 * Ghidra: FUN_0034b308(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_b308(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034b318(void) @ 0x0034b318   (est. sk_noop_handler)
 * Ghidra: FUN_0034b318(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_b318(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034b328(void) @ 0x0034b328   (est. sk_noop_handler)
 * Ghidra: FUN_0034b328(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_b328(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034b338(void) @ 0x0034b338   (est. sk_noop_handler)
 * Ghidra: FUN_0034b338(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_b338(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034b348(void) @ 0x0034b348   (est. sk_noop_handler)
 * Ghidra: FUN_0034b348(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_b348(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034b358(void) @ 0x0034b358   (est. sk_noop_handler)
 * Ghidra: FUN_0034b358(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_b358(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034b368(void) @ 0x0034b368   (est. sk_callee_call_00310ad4)
 * Ghidra: FUN_0034b368(void)
 * Thin wrapper invoking out-of-slice helper(s); args dropped by decompiler where empty.
 * Confidence: medium
 * Notes: Thin wrapper invoking out-of-slice helper(s); args dropped by decompiler where empty. */
void sk_callee_call_00310ad4_b368(void)
{
    sk_tagged_deref_lo(0);
    sk_tagged_deref_hi(0);
    return;
}

/* FUN_0034b384(void) @ 0x0034b384   (est. sk_noop_handler)
 * Ghidra: FUN_0034b384(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_b384(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034b3c8(void) @ 0x0034b3c8   (est. sk_noop_handler)
 * Ghidra: FUN_0034b3c8(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_b3c8(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034b3d8(void) @ 0x0034b3d8   (est. sk_noop_handler)
 * Ghidra: FUN_0034b3d8(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_b3d8(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034b3e8(void) @ 0x0034b3e8   (est. sk_noop_handler)
 * Ghidra: FUN_0034b3e8(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_b3e8(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034b3f8(void) @ 0x0034b3f8   (est. sk_noop_handler)
 * Ghidra: FUN_0034b3f8(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_b3f8(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034b414(void) @ 0x0034b414   (est. sk_noop_handler)
 * Ghidra: FUN_0034b414(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_b414(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034b430(void) @ 0x0034b430   (est. sk_noop_handler)
 * Ghidra: FUN_0034b430(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_b430(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034b440(void) @ 0x0034b440   (est. sk_callee_call_0006a4c0)
 * Ghidra: FUN_0034b440(void)
 * Thin wrapper invoking out-of-slice helper(s); args dropped by decompiler where empty.
 * Confidence: medium
 * Notes: Thin wrapper invoking out-of-slice helper(s); args dropped by decompiler where empty. */
void sk_callee_call_0006a4c0_b440(void)
{
    sk_callee_0006a4c0(0);
    return;
}

/* FUN_0034b460(void) @ 0x0034b460   (est. sk_noop_handler)
 * Ghidra: FUN_0034b460(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_b460(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034b470(void) @ 0x0034b470   (est. sk_noop_handler)
 * Ghidra: FUN_0034b470(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_b470(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034b480(void) @ 0x0034b480   (est. sk_vec_addr_5be7c0)
 * Ghidra: FUN_0034b480(void)
 * Returns a 16-byte value whose low word is the constant address 0x5be7c0.
 * Confidence: medium
 * Notes: 16-byte zero-extended value of address 0x5be7c0 (ZEXT816). */
sk_u128_t sk_vec_addr_5be7c0_b480(void)
{
    sk_u128_t r;
    r.lo = 0x5be7c0; r.hi = 0;
    return r;
}

/* FUN_0034b490(void) @ 0x0034b490   (est. sk_noop_handler)
 * Ghidra: FUN_0034b490(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_b490(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034b4a0(void) @ 0x0034b4a0   (est. sk_noop_handler)
 * Ghidra: FUN_0034b4a0(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_b4a0(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034b4b0(void) @ 0x0034b4b0   (est. sk_noop_handler)
 * Ghidra: FUN_0034b4b0(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_b4b0(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034b4c0(void) @ 0x0034b4c0   (est. sk_noop_handler)
 * Ghidra: FUN_0034b4c0(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_b4c0(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034b4d0(void) @ 0x0034b4d0   (est. sk_callee_call_003109b4)
 * Ghidra: FUN_0034b4d0(void)
 * Thin wrapper invoking out-of-slice helper(s); args dropped by decompiler where empty.
 * Confidence: medium
 * Notes: Thin wrapper invoking out-of-slice helper(s); args dropped by decompiler where empty. */
void sk_callee_call_003109b4_b4d0(void)
{
    sk_callee_003109b4(0);
    return;
}

/* FUN_0034b4ec(void) @ 0x0034b4ec   (est. sk_callee_call_0016186c)
 * Ghidra: FUN_0034b4ec(void)
 * Thin wrapper invoking out-of-slice helper(s); args dropped by decompiler where empty.
 * Confidence: medium
 * Notes: Thin wrapper invoking out-of-slice helper(s); args dropped by decompiler where empty. */
void sk_callee_call_0016186c_b4ec(void)
{
    sk_callee_0016186c(0);
    return;
}

/* FUN_0034b508(void) @ 0x0034b508   (est. sk_noop_handler)
 * Ghidra: FUN_0034b508(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_b508(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034b518(void) @ 0x0034b518   (est. sk_noop_handler)
 * Ghidra: FUN_0034b518(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_b518(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034b528(void) @ 0x0034b528   (est. sk_data_getter_004edcd0)
 * Ghidra: FUN_0034b528(void)
 * Returns address of global data DAT_004edcd0.
 * Confidence: medium
 * Notes: Returns address of global data DAT_004edcd0. */
uint8_t * sk_data_getter_004edcd0_b528(void)
{
    return (uint8_t *)sk_data_004edcd0;
}

/* FUN_0034b540(void) @ 0x0034b540   (est. sk_noop_handler)
 * Ghidra: FUN_0034b540(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_b540(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034b550(void) @ 0x0034b550   (est. sk_data_getter_004ec2e0)
 * Ghidra: FUN_0034b550(void)
 * Returns address of global data DAT_004ec2e0.
 * Confidence: medium
 * Notes: Returns address of global data DAT_004ec2e0. */
uint8_t * sk_data_getter_004ec2e0_b550(void)
{
    return (uint8_t *)sk_data_004ec2e0;
}

/* FUN_0034b568(void) @ 0x0034b568   (est. sk_noop_handler)
 * Ghidra: FUN_0034b568(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_b568(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034b57c(void) @ 0x0034b57c   (est. sk_noop_handler)
 * Ghidra: FUN_0034b57c(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_b57c(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034b590(void) @ 0x0034b590   (est. sk_data_getter_004edd94)
 * Ghidra: FUN_0034b590(void)
 * Returns address of global data DAT_004edd94.
 * Confidence: medium
 * Notes: Returns address of global data DAT_004edd94. */
uint8_t * sk_data_getter_004edd94_b590(void)
{
    return (uint8_t *)sk_data_004edd94;
}

/* FUN_0034b5a8(void) @ 0x0034b5a8   (est. sk_noop_handler)
 * Ghidra: FUN_0034b5a8(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_b5a8(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034b5bc(void) @ 0x0034b5bc   (est. sk_noop_handler)
 * Ghidra: FUN_0034b5bc(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_b5bc(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034b5d0(void) @ 0x0034b5d0   (est. sk_data_getter_004e8f64)
 * Ghidra: FUN_0034b5d0(void)
 * Returns address of global data DAT_004e8f64.
 * Confidence: medium
 * Notes: Returns address of global data DAT_004e8f64. */
uint8_t * sk_data_getter_004e8f64_b5d0(void)
{
    return (uint8_t *)sk_data_004e8f64;
}

/* FUN_0034b5e8(void) @ 0x0034b5e8   (est. sk_noop_handler)
 * Ghidra: FUN_0034b5e8(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_b5e8(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034b5fc(void) @ 0x0034b5fc   (est. sk_data_getter_004e8c24)
 * Ghidra: FUN_0034b5fc(void)
 * Returns address of global data DAT_004e8c24.
 * Confidence: medium
 * Notes: Returns address of global data DAT_004e8c24. */
uint8_t * sk_data_getter_004e8c24_b5fc(void)
{
    return (uint8_t *)sk_data_004e8c24;
}

/* FUN_0034b614(void) @ 0x0034b614   (est. sk_u128_builder)
 * Ghidra: FUN_0034b614(void)
 * Builds and returns a 16-byte (lo,hi) vector (data pointer + length/flag).
 * Confidence: medium
 * Notes: Builds a 16-byte (lo,hi) result from data pointer and length. */
sk_u128_t sk_u128_builder_b614(void)
{
    sk_u128_t r;
    r.lo = (uint64_t)(sk_data_004c1010);
    r.hi = (uint64_t)(0x100);
    return r;
}

/* FUN_0034b628(void) @ 0x0034b628   (est. sk_data_getter_004e9d20)
 * Ghidra: FUN_0034b628(void)
 * Returns address of global data DAT_004e9d20.
 * Confidence: medium
 * Notes: Returns address of global data DAT_004e9d20. */
uint8_t * sk_data_getter_004e9d20_b628(void)
{
    return (uint8_t *)sk_data_004e9d20;
}

/* FUN_0034b640(void) @ 0x0034b640   (est. sk_degen_frame_op)
 * Ghidra: FUN_0034b640(void)
 * Degenerate body: the decompiler lost register/stack flow (unaff_* / in_* operands); the raw decompile statements are preserved as comments.
 * Confidence: low
 * Notes: Decompiler lost register/stack flow (unaff_* / in_* operands); body rendered as annotation. */
void sk_degen_frame_op_b640(void)
{
    /* *(long *)(unaff_x29 + -0xf0) = in_x9 - in_x12; */
    /* return; */
    return;
}

/* FUN_0034b654(void) @ 0x0034b654   (est. sk_noop_handler)
 * Ghidra: FUN_0034b654(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_b654(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034b668(void) @ 0x0034b668   (est. sk_noop_handler)
 * Ghidra: FUN_0034b668(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_b668(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034b67c(void) @ 0x0034b67c   (est. sk_noop_handler)
 * Ghidra: FUN_0034b67c(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_b67c(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034b690(void) @ 0x0034b690   (est. sk_noop_handler)
 * Ghidra: FUN_0034b690(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_b690(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034b6a4(void) @ 0x0034b6a4   (est. sk_noop_handler)
 * Ghidra: FUN_0034b6a4(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_b6a4(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034b6b8(void) @ 0x0034b6b8   (est. sk_noop_handler)
 * Ghidra: FUN_0034b6b8(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_b6b8(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034b6cc(void) @ 0x0034b6cc   (est. sk_noop_handler)
 * Ghidra: FUN_0034b6cc(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_b6cc(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034b6e0(long param_1) @ 0x0034b6e0   (est. sk_degen_frame_op)
 * Ghidra: FUN_0034b6e0(long param_1)
 * Degenerate body: the decompiler lost register/stack flow (unaff_* / in_* operands); the raw decompile statements are preserved as comments.
 * Confidence: low
 * Notes: Decompiler lost register/stack flow (unaff_* / in_* operands); body rendered as annotation. */
void sk_degen_frame_op_b6e0(int64_t arg1)
{
    /* *(long *)(unaff_x29 + -0x70) = (long)&stack0x00000000 - arg1; */
    /* return; */
    return;
}

/* FUN_0034b6f4(long param_1) @ 0x0034b6f4   (est. sk_degen_frame_op)
 * Ghidra: FUN_0034b6f4(long param_1)
 * Degenerate body: the decompiler lost register/stack flow (unaff_* / in_* operands); the raw decompile statements are preserved as comments.
 * Confidence: low
 * Notes: Decompiler lost register/stack flow (unaff_* / in_* operands); body rendered as annotation. */
void sk_degen_frame_op_b6f4(int64_t arg1)
{
    /* *(long *)(unaff_x29 + -0x88) = (long)&stack0x00000000 - arg1; */
    /* return; */
    return;
}

/* FUN_0034b708(long param_1) @ 0x0034b708   (est. sk_degen_frame_op)
 * Ghidra: FUN_0034b708(long param_1)
 * Degenerate body: the decompiler lost register/stack flow (unaff_* / in_* operands); the raw decompile statements are preserved as comments.
 * Confidence: low
 * Notes: Decompiler lost register/stack flow (unaff_* / in_* operands); body rendered as annotation. */
void sk_degen_frame_op_b708(int64_t arg1)
{
    /* *(long *)(unaff_x29 + -0x98) = (long)&stack0x00000000 - arg1; */
    /* return; */
    return;
}

/* FUN_0034b71c(long param_1) @ 0x0034b71c   (est. sk_degen_frame_op)
 * Ghidra: FUN_0034b71c(long param_1)
 * Degenerate body: the decompiler lost register/stack flow (unaff_* / in_* operands); the raw decompile statements are preserved as comments.
 * Confidence: low
 * Notes: Decompiler lost register/stack flow (unaff_* / in_* operands); body rendered as annotation. */
void sk_degen_frame_op_b71c(int64_t arg1)
{
    /* *(long *)(unaff_x29 + -0x78) = (long)&stack0x00000000 - arg1; */
    /* return; */
    return;
}

/* FUN_0034b730(void) @ 0x0034b730   (est. sk_noop_handler)
 * Ghidra: FUN_0034b730(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_b730(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034b744(void) @ 0x0034b744   (est. sk_noop_handler)
 * Ghidra: FUN_0034b744(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_b744(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034b758(void) @ 0x0034b758   (est. sk_noop_handler)
 * Ghidra: FUN_0034b758(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_b758(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034b768(void) @ 0x0034b768   (est. sk_noop_handler)
 * Ghidra: FUN_0034b768(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_b768(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034b778(void) @ 0x0034b778   (est. sk_noop_handler)
 * Ghidra: FUN_0034b778(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_b778(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034b788(void) @ 0x0034b788   (est. sk_noop_handler)
 * Ghidra: FUN_0034b788(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_b788(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034b798(void) @ 0x0034b798   (est. sk_noop_handler)
 * Ghidra: FUN_0034b798(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_b798(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034b7a8(void) @ 0x0034b7a8   (est. sk_noop_handler)
 * Ghidra: FUN_0034b7a8(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_b7a8(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034b7b8(void) @ 0x0034b7b8   (est. sk_return_zero)
 * Ghidra: FUN_0034b7b8(void)
 * Returns the constant zero.
 * Confidence: medium
 * Notes: undefined8 constant-zero return. */
uint64_t sk_return_zero_b7b8(void)
{
    return 0;
}

/* FUN_0034b7c8(void) @ 0x0034b7c8   (est. sk_callee_call_00291ee0)
 * Ghidra: FUN_0034b7c8(void)
 * Thin wrapper invoking out-of-slice helper(s); args dropped by decompiler where empty.
 * Confidence: medium
 * Notes: Thin wrapper invoking out-of-slice helper(s); args dropped by decompiler where empty. */
void sk_callee_call_00291ee0_b7c8(void)
{
    sk_callee_00291ee0(0);
    return;
}

/* FUN_0034b7e4(void) @ 0x0034b7e4   (est. sk_noop_handler)
 * Ghidra: FUN_0034b7e4(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_b7e4(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034b7f4(void) @ 0x0034b7f4   (est. sk_noop_handler)
 * Ghidra: FUN_0034b7f4(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_b7f4(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034b804(void) @ 0x0034b804   (est. sk_noop_handler)
 * Ghidra: FUN_0034b804(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_b804(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034b814(void) @ 0x0034b814   (est. sk_noop_handler)
 * Ghidra: FUN_0034b814(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_b814(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034b824(void) @ 0x0034b824   (est. sk_noop_handler)
 * Ghidra: FUN_0034b824(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_b824(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034b848(void) @ 0x0034b848   (est. sk_noop_handler)
 * Ghidra: FUN_0034b848(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_b848(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034b85c(void) @ 0x0034b85c   (est. sk_noop_handler)
 * Ghidra: FUN_0034b85c(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_b85c(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034b86c(void) @ 0x0034b86c   (est. sk_noop_handler)
 * Ghidra: FUN_0034b86c(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_b86c(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034b87c(void) @ 0x0034b87c   (est. sk_noop_handler)
 * Ghidra: FUN_0034b87c(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_b87c(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034b88c(void) @ 0x0034b88c   (est. sk_noop_handler)
 * Ghidra: FUN_0034b88c(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_b88c(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034b89c(void) @ 0x0034b89c   (est. sk_callee_call_00291ee0)
 * Ghidra: FUN_0034b89c(void)
 * Thin wrapper invoking out-of-slice helper(s); args dropped by decompiler where empty.
 * Confidence: medium
 * Notes: Thin wrapper invoking out-of-slice helper(s); args dropped by decompiler where empty. */
void sk_callee_call_00291ee0_b89c(void)
{
    sk_callee_00291ee0(0);
    return;
}

/* FUN_0034b8bc(void) @ 0x0034b8bc   (est. sk_noop_handler)
 * Ghidra: FUN_0034b8bc(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_b8bc(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034b8cc(void) @ 0x0034b8cc   (est. sk_noop_handler)
 * Ghidra: FUN_0034b8cc(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_b8cc(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034b8dc(void) @ 0x0034b8dc   (est. sk_noop_handler)
 * Ghidra: FUN_0034b8dc(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_b8dc(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034b8ec(void) @ 0x0034b8ec   (est. sk_callee_call_0008f728)
 * Ghidra: FUN_0034b8ec(void)
 * Thin wrapper invoking out-of-slice helper(s); args dropped by decompiler where empty.
 * Confidence: medium
 * Notes: Thin wrapper invoking out-of-slice helper(s); args dropped by decompiler where empty. */
void sk_callee_call_0008f728_b8ec(void)
{
    sk_callee_0008f728(0);
    return;
}

/* FUN_0034b908(void) @ 0x0034b908   (est. sk_noop_handler)
 * Ghidra: FUN_0034b908(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_b908(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034b918(void) @ 0x0034b918   (est. sk_noop_handler)
 * Ghidra: FUN_0034b918(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_b918(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034b930(void) @ 0x0034b930   (est. sk_degen_frame_op)
 * Ghidra: FUN_0034b930(void)
 * Degenerate body: the decompiler lost register/stack flow (unaff_* / in_* operands); the raw decompile statements are preserved as comments.
 * Confidence: low
 * Notes: Decompiler lost register/stack flow (unaff_* / in_* operands); body rendered as annotation. */
uint8_t sk_degen_frame_op_b930(void)
{
    /* Ghidra: return *(undefined1 *)(*unaff_x20 + 0x20);  (pointer flow lost) */
    return 0;
}

/* FUN_0034b948(void) @ 0x0034b948   (est. sk_noop_handler)
 * Ghidra: FUN_0034b948(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_b948(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034b960(undefined8 param_1) @ 0x0034b960   (est. sk_degen_frame_op)
 * Ghidra: FUN_0034b960(undefined8 param_1)
 * Degenerate body: the decompiler lost register/stack flow (unaff_* / in_* operands); the raw decompile statements are preserved as comments.
 * Confidence: low
 * Notes: Decompiler lost register/stack flow (unaff_* / in_* operands); body rendered as annotation. */
void sk_degen_frame_op_b960(uint64_t arg1)
{
    /* *(undefined8 *)(unaff_x26 + 0x38) = arg1; */
    /* return; */
    return;
}

/* FUN_0034b980(void) @ 0x0034b980   (est. sk_noop_handler)
 * Ghidra: FUN_0034b980(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_b980(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034b9a0(undefined8 param_1,undefined8 param_2,undefined8 param_3) @ 0x0034b9a0   (est. sk_callback_register)
 * Ghidra: FUN_0034b9a0(undefined8 param_1,undefined8 param_2,undefined8 param_3)
 * Registers two callbacks: resolves a value via the 8f6c0/8f6f4 helpers, then invokes the 377824 register helper with the resolved value and two function pointers.
 * Confidence: medium
 * Notes: Registers callbacks: resolves a value via 8f6c0/8f6f4 then calls 377824 passing two function pointers (0060e3fc/0060e40c). */
void sk_callback_register_b9a0(uint64_t arg1, uint64_t arg2, uint64_t arg3)
{
    uint64_t u;
    sk_callee_0008f6c0(arg3);
    u = (uint64_t)sk_callee_0008f6f4(0);
    sk_callee_00377824(0, u, arg2,
                       (void (*)(void))sk_callee_0060e3fc,
                       (void (*)(void))sk_callee_0060e40c);
    return;
}

/* FUN_0034b9e8(void) @ 0x0034b9e8   (est. sk_noop_handler)
 * Ghidra: FUN_0034b9e8(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_b9e8(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034b9f8(void) @ 0x0034b9f8   (est. sk_noop_handler)
 * Ghidra: FUN_0034b9f8(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_b9f8(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034ba08(void) @ 0x0034ba08   (est. sk_noop_handler)
 * Ghidra: FUN_0034ba08(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_ba08(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034ba18(void) @ 0x0034ba18   (est. sk_noop_handler)
 * Ghidra: FUN_0034ba18(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_ba18(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034ba28(void) @ 0x0034ba28   (est. sk_noop_handler)
 * Ghidra: FUN_0034ba28(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_ba28(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034ba38(void) @ 0x0034ba38   (est. sk_noop_handler)
 * Ghidra: FUN_0034ba38(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_ba38(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034ba48(void) @ 0x0034ba48   (est. sk_noop_handler)
 * Ghidra: FUN_0034ba48(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_ba48(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034ba58(void) @ 0x0034ba58   (est. sk_noop_handler)
 * Ghidra: FUN_0034ba58(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_ba58(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034ba68(void) @ 0x0034ba68   (est. sk_noop_handler)
 * Ghidra: FUN_0034ba68(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_ba68(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034ba78(void) @ 0x0034ba78   (est. sk_noop_handler)
 * Ghidra: FUN_0034ba78(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_ba78(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034ba88(void) @ 0x0034ba88   (est. sk_noop_handler)
 * Ghidra: FUN_0034ba88(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_ba88(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034ba98(void) @ 0x0034ba98   (est. sk_noop_handler)
 * Ghidra: FUN_0034ba98(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_ba98(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034baa8(void) @ 0x0034baa8   (est. sk_noop_handler)
 * Ghidra: FUN_0034baa8(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_baa8(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034bab8(void) @ 0x0034bab8   (est. sk_noop_handler)
 * Ghidra: FUN_0034bab8(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_bab8(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034bac8(void) @ 0x0034bac8   (est. sk_noop_handler)
 * Ghidra: FUN_0034bac8(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_bac8(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034badc(void) @ 0x0034badc   (est. sk_noop_handler)
 * Ghidra: FUN_0034badc(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_badc(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034baf0(void) @ 0x0034baf0   (est. sk_noop_handler)
 * Ghidra: FUN_0034baf0(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_baf0(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034bb04(void) @ 0x0034bb04   (est. sk_degen_frame_op)
 * Ghidra: FUN_0034bb04(void)
 * Degenerate body: the decompiler lost register/stack flow (unaff_* / in_* operands); the raw decompile statements are preserved as comments.
 * Confidence: low
 * Notes: Decompiler lost register/stack flow (unaff_* / in_* operands); body rendered as annotation. */
void sk_degen_frame_op_bb04(void)
{
    /* *(undefined8 *)(unaff_x29 + -0x58) = unaff_x27; */
    /* sk_callee_00310a74(); */
    /* *(undefined8 *)(unaff_x29 + -0x78) = unaff_x26; */
    /* sk_callee_0001df60(); */
    /* return; */
    return;
}

/* FUN_0034bb38(void) @ 0x0034bb38   (est. sk_noop_handler)
 * Ghidra: FUN_0034bb38(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_bb38(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034bb4c(void) @ 0x0034bb4c   (est. sk_noop_handler)
 * Ghidra: FUN_0034bb4c(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_bb4c(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034bb60(void) @ 0x0034bb60   (est. sk_noop_handler)
 * Ghidra: FUN_0034bb60(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_bb60(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034bb74(void) @ 0x0034bb74   (est. sk_noop_handler)
 * Ghidra: FUN_0034bb74(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_bb74(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034bb84(void) @ 0x0034bb84   (est. sk_noop_handler)
 * Ghidra: FUN_0034bb84(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_bb84(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034bb94(void) @ 0x0034bb94   (est. sk_callee_call_00310a44)
 * Ghidra: FUN_0034bb94(void)
 * Thin wrapper invoking out-of-slice helper(s); args dropped by decompiler where empty.
 * Confidence: medium
 * Notes: Thin wrapper invoking out-of-slice helper(s); args dropped by decompiler where empty. */
void sk_callee_call_00310a44_bb94(void)
{
    sk_callee_00310a44(0);
    return;
}

/* FUN_0034bbb4(void) @ 0x0034bbb4   (est. sk_noop_handler)
 * Ghidra: FUN_0034bbb4(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_bbb4(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034bbc8(void) @ 0x0034bbc8   (est. sk_noop_handler)
 * Ghidra: FUN_0034bbc8(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_bbc8(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034bbdc(void) @ 0x0034bbdc   (est. sk_noop_handler)
 * Ghidra: FUN_0034bbdc(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_bbdc(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034bbf0(void) @ 0x0034bbf0   (est. sk_u128_builder)
 * Ghidra: FUN_0034bbf0(void)
 * Builds and returns a 16-byte (lo,hi) vector (data pointer + length/flag).
 * Confidence: medium
 * Notes: Builds a 16-byte (lo,hi) result from data pointer and length. */
sk_u128_t sk_u128_builder_bbf0(void)
{
    sk_u128_t r;
    r.lo = (uint64_t)(sk_data_004c1010);
    r.hi = (uint64_t)(0x100);
    return r;
}

/* FUN_0034bc04(void) @ 0x0034bc04   (est. sk_data_getter_004e4980)
 * Ghidra: FUN_0034bc04(void)
 * Returns address of global data DAT_004e4980.
 * Confidence: medium
 * Notes: Returns address of global data DAT_004e4980. */
uint8_t * sk_data_getter_004e4980_bc04(void)
{
    return (uint8_t *)sk_data_004e4980;
}

/* FUN_0034bc24(void) @ 0x0034bc24   (est. sk_noop_handler)
 * Ghidra: FUN_0034bc24(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_bc24(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034bc38(void) @ 0x0034bc38   (est. sk_noop_handler)
 * Ghidra: FUN_0034bc38(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_bc38(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034bc58(void) @ 0x0034bc58   (est. sk_degen_frame_op)
 * Ghidra: FUN_0034bc58(void)
 * Degenerate body: the decompiler lost register/stack flow (unaff_* / in_* operands); the raw decompile statements are preserved as comments.
 * Confidence: low
 * Notes: Decompiler lost register/stack flow (unaff_* / in_* operands); body rendered as annotation. */
void sk_degen_frame_op_bc58(void)
{
    /* *(long *)(unaff_x29 + -0x88) = (long)&stack0x00000000 - in_x12; */
    /* return; */
    return;
}

/* FUN_0034bc6c(void) @ 0x0034bc6c   (est. sk_degen_frame_op)
 * Ghidra: FUN_0034bc6c(void)
 * Degenerate body: the decompiler lost register/stack flow (unaff_* / in_* operands); the raw decompile statements are preserved as comments.
 * Confidence: low
 * Notes: Decompiler lost register/stack flow (unaff_* / in_* operands); body rendered as annotation. */
void sk_degen_frame_op_bc6c(void)
{
    /* *(long *)(unaff_x29 + -0xb0) = (long)&stack0x00000000 - in_x12; */
    /* return; */
    return;
}

/* FUN_0034bc80(void) @ 0x0034bc80   (est. sk_degen_frame_op)
 * Ghidra: FUN_0034bc80(void)
 * Degenerate body: the decompiler lost register/stack flow (unaff_* / in_* operands); the raw decompile statements are preserved as comments.
 * Confidence: low
 * Notes: Decompiler lost register/stack flow (unaff_* / in_* operands); body rendered as annotation. */
void sk_degen_frame_op_bc80(void)
{
    /* *(long *)(unaff_x29 + -0x78) = (long)&stack0x00000000 - in_x12; */
    /* return; */
    return;
}

/* FUN_0034bc94(void) @ 0x0034bc94   (est. sk_noop_handler)
 * Ghidra: FUN_0034bc94(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_bc94(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034bca4(void) @ 0x0034bca4   (est. sk_callee_call_0006a4c0)
 * Ghidra: FUN_0034bca4(void)
 * Thin wrapper invoking out-of-slice helper(s); args dropped by decompiler where empty.
 * Confidence: medium
 * Notes: Thin wrapper invoking out-of-slice helper(s); args dropped by decompiler where empty. */
void sk_callee_call_0006a4c0_bca4(void)
{
    sk_callee_0006a4c0(0);
    sk_callee_0008e5d8(0);
    return;
}

/* FUN_0034bccc(void) @ 0x0034bccc   (est. sk_noop_handler)
 * Ghidra: FUN_0034bccc(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_bccc(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034bcdc(void) @ 0x0034bcdc   (est. sk_noop_handler)
 * Ghidra: FUN_0034bcdc(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_bcdc(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034bcf0(void) @ 0x0034bcf0   (est. sk_noop_handler)
 * Ghidra: FUN_0034bcf0(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_bcf0(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034bd00(void) @ 0x0034bd00   (est. sk_callee_call_000839d8)
 * Ghidra: FUN_0034bd00(void)
 * Thin wrapper invoking out-of-slice helper(s); args dropped by decompiler where empty.
 * Confidence: medium
 * Notes: Thin wrapper invoking out-of-slice helper(s); args dropped by decompiler where empty. */
void sk_callee_call_000839d8_bd00(void)
{
    sk_callee_000839d8(0);
    return;
}

/* FUN_0034bd30(void) @ 0x0034bd30   (est. sk_noop_handler)
 * Ghidra: FUN_0034bd30(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_bd30(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034bd44(void) @ 0x0034bd44   (est. sk_noop_handler)
 * Ghidra: FUN_0034bd44(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_bd44(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034bd58(void) @ 0x0034bd58   (est. sk_noop_handler)
 * Ghidra: FUN_0034bd58(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_bd58(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034bd6c(undefined8 param_1,undefined8 param_2) @ 0x0034bd6c   (est. sk_return_arg2)
 * Ghidra: FUN_0034bd6c(undefined8 param_1,undefined8 param_2)
 * Passes its second argument through unchanged (identity on arg2).
 * Confidence: medium
 * Notes: Returns its second parameter unchanged. */
uint64_t sk_return_arg2_bd6c(uint64_t arg1, uint64_t arg2)
{
    return arg2;
}

/* FUN_0034bd80(void) @ 0x0034bd80   (est. sk_return_zero)
 * Ghidra: FUN_0034bd80(void)
 * Returns the constant zero.
 * Confidence: medium
 * Notes: undefined8 constant-zero return. */
uint64_t sk_return_zero_bd80(void)
{
    return 0;
}

/* FUN_0034bd90(void) @ 0x0034bd90   (est. sk_noop_handler)
 * Ghidra: FUN_0034bd90(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_bd90(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034bda0(void) @ 0x0034bda0   (est. sk_callee_call_0016186c)
 * Ghidra: FUN_0034bda0(void)
 * Thin wrapper invoking out-of-slice helper(s); args dropped by decompiler where empty.
 * Confidence: medium
 * Notes: Thin wrapper invoking out-of-slice helper(s); args dropped by decompiler where empty. */
void sk_callee_call_0016186c_bda0(void)
{
    sk_callee_0016186c(0);
    return;
}

/* FUN_0034bdbc(void) @ 0x0034bdbc   (est. sk_noop_handler)
 * Ghidra: FUN_0034bdbc(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_bdbc(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034bdcc(void) @ 0x0034bdcc   (est. sk_noop_handler)
 * Ghidra: FUN_0034bdcc(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_bdcc(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034bddc(void) @ 0x0034bddc   (est. sk_noop_handler)
 * Ghidra: FUN_0034bddc(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_bddc(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034bdec(void) @ 0x0034bdec   (est. sk_noop_handler)
 * Ghidra: FUN_0034bdec(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_bdec(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034bdfc(void) @ 0x0034bdfc   (est. sk_noop_handler)
 * Ghidra: FUN_0034bdfc(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_bdfc(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034be0c(void) @ 0x0034be0c   (est. sk_noop_handler)
 * Ghidra: FUN_0034be0c(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_be0c(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034be1c(undefined8 param_1,undefined8 param_2) @ 0x0034be1c   (est. sk_u128_builder)
 * Ghidra: FUN_0034be1c(undefined8 param_1,undefined8 param_2)
 * Builds and returns a 16-byte (lo,hi) vector (data pointer + length/flag).
 * Confidence: medium
 * Notes: Builds a 16-byte (lo,hi) result from data pointer and length. */
sk_u128_t sk_u128_builder_be1c(uint64_t arg1, uint64_t arg2)
{
    sk_callee_0031a17c(arg2);
    sk_u128_t r;
    r.lo = (uint64_t)(arg1);
    r.hi = (uint64_t)(arg2);
    return r;
}

/* FUN_0034be54(void) @ 0x0034be54   (est. sk_callee_call_0008f6c0)
 * Ghidra: FUN_0034be54(void)
 * Thin wrapper invoking out-of-slice helper(s); args dropped by decompiler where empty.
 * Confidence: medium
 * Notes: Thin wrapper invoking out-of-slice helper(s); args dropped by decompiler where empty. */
void sk_callee_call_0008f6c0_be54(void)
{
    sk_callee_0008f6c0(0);
    sk_callee_0008f6f4(0);
    return;
}

/* FUN_0034be70(void) @ 0x0034be70   (est. sk_callee_call_0017e880)
 * Ghidra: FUN_0034be70(void)
 * Thin wrapper invoking out-of-slice helper(s); args dropped by decompiler where empty.
 * Confidence: medium
 * Notes: Thin wrapper invoking out-of-slice helper(s); args dropped by decompiler where empty. */
void sk_callee_call_0017e880_be70(void)
{
    sk_callee_0017e880(0);
    return;
}

/* FUN_0034be94(void) @ 0x0034be94   (est. sk_noop_handler)
 * Ghidra: FUN_0034be94(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_be94(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034bea4(void) @ 0x0034bea4   (est. sk_noop_handler)
 * Ghidra: FUN_0034bea4(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_bea4(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034beb4(void) @ 0x0034beb4   (est. sk_noop_handler)
 * Ghidra: FUN_0034beb4(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_beb4(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034bec4(void) @ 0x0034bec4   (est. sk_return_zero)
 * Ghidra: FUN_0034bec4(void)
 * Returns the constant zero.
 * Confidence: medium
 * Notes: undefined8 constant-zero return. */
uint64_t sk_return_zero_bec4(void)
{
    return 0;
}

/* FUN_0034bed4(void) @ 0x0034bed4   (est. sk_noop_handler)
 * Ghidra: FUN_0034bed4(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_bed4(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034beec(void) @ 0x0034beec   (est. sk_noop_handler)
 * Ghidra: FUN_0034beec(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_beec(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034befc(void) @ 0x0034befc   (est. sk_noop_handler)
 * Ghidra: FUN_0034befc(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_befc(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034bf0c(void) @ 0x0034bf0c   (est. sk_noop_handler)
 * Ghidra: FUN_0034bf0c(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_bf0c(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034bf1c(void) @ 0x0034bf1c   (est. sk_noop_handler)
 * Ghidra: FUN_0034bf1c(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_bf1c(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034bf2c(void) @ 0x0034bf2c   (est. sk_callee_call_003109b4)
 * Ghidra: FUN_0034bf2c(void)
 * Thin wrapper invoking out-of-slice helper(s); args dropped by decompiler where empty.
 * Confidence: medium
 * Notes: Thin wrapper invoking out-of-slice helper(s); args dropped by decompiler where empty. */
void sk_callee_call_003109b4_bf2c(void)
{
    sk_callee_003109b4(0);
    return;
}

/* FUN_0034bf48(void) @ 0x0034bf48   (est. sk_callee_call_00310ad4)
 * Ghidra: FUN_0034bf48(void)
 * Thin wrapper invoking out-of-slice helper(s); args dropped by decompiler where empty.
 * Confidence: medium
 * Notes: Thin wrapper invoking out-of-slice helper(s); args dropped by decompiler where empty. */
void sk_callee_call_00310ad4_bf48(void)
{
    sk_tagged_deref_lo(0);
    sk_tagged_deref_hi(0);
    return;
}

/* FUN_0034bf64(void) @ 0x0034bf64   (est. sk_noop_handler)
 * Ghidra: FUN_0034bf64(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_bf64(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034bf74(void) @ 0x0034bf74   (est. sk_noop_handler)
 * Ghidra: FUN_0034bf74(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_bf74(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034bf84(void) @ 0x0034bf84   (est. sk_noop_handler)
 * Ghidra: FUN_0034bf84(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_bf84(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034bf94(void) @ 0x0034bf94   (est. sk_noop_handler)
 * Ghidra: FUN_0034bf94(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_bf94(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034bfa4(void) @ 0x0034bfa4   (est. sk_noop_handler)
 * Ghidra: FUN_0034bfa4(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_bfa4(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034bfb4(void) @ 0x0034bfb4   (est. sk_noop_handler)
 * Ghidra: FUN_0034bfb4(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_bfb4(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}

/* FUN_0034bfc4(void) @ 0x0034bfc4   (est. sk_callee_call_003109b4)
 * Ghidra: FUN_0034bfc4(void)
 * Thin wrapper invoking out-of-slice helper(s); args dropped by decompiler where empty.
 * Confidence: medium
 * Notes: Thin wrapper invoking out-of-slice helper(s); args dropped by decompiler where empty. */
void sk_callee_call_003109b4_bfc4(void)
{
    sk_callee_003109b4(0);
    return;
}

/* FUN_0034bfe0(void) @ 0x0034bfe0   (est. sk_callee_call_003109b4)
 * Ghidra: FUN_0034bfe0(void)
 * Thin wrapper invoking out-of-slice helper(s); args dropped by decompiler where empty.
 * Confidence: medium
 * Notes: Thin wrapper invoking out-of-slice helper(s); args dropped by decompiler where empty. */
void sk_callee_call_003109b4_bfe0(void)
{
    sk_callee_003109b4(0);
    return;
}

/* FUN_0034bffc(void) @ 0x0034bffc   (est. sk_callee_call_000839f8)
 * Ghidra: FUN_0034bffc(void)
 * Thin wrapper invoking out-of-slice helper(s); args dropped by decompiler where empty.
 * Confidence: medium
 * Notes: Thin wrapper invoking out-of-slice helper(s); args dropped by decompiler where empty. */
void sk_callee_call_000839f8_bffc(void)
{
    sk_callee_000839f8(0);
    return;
}

/* FUN_0034c018(void) @ 0x0034c018   (est. sk_callee_call_0016186c)
 * Ghidra: FUN_0034c018(void)
 * Thin wrapper invoking out-of-slice helper(s); args dropped by decompiler where empty.
 * Confidence: medium
 * Notes: Thin wrapper invoking out-of-slice helper(s); args dropped by decompiler where empty. */
void sk_callee_call_0016186c_c018(void)
{
    sk_callee_0016186c(0);
    return;
}

/* FUN_0034c034(void) @ 0x0034c034   (est. sk_noop_handler)
 * Ghidra: FUN_0034c034(void)
 * No-op entry point: the decompiler shows no observable side effect (empty body).
 * Confidence: low
 * Notes: Empty body — syscall-handler table slot with no decompiled work. */
void sk_noop_handler_c034(void)
{
    /* No-op: no observable side effect in the decompile. */
    return;
}
