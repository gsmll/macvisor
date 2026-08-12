/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel,
 * arm64e, image base 0) — the cL4 microkernel (GL1), "cL4 (679.100.61)".
 * Ground truth: Ghidra FUN_ names + addresses in program cl4_kernel.raw.
 * Slice GAP07: 0x0034f22c-0x0034fb14 (120 functions). All names are estimates
 * unless string/header-matched. Uses seL4/cL4 vocabulary (TCB, cap, CNode, IPC,
 * notification, endpoint, vspace, sched, object, slot).
 *
 * This region is a dense table of tiny Swift-runtime / Swift standard-library
 * stubs: trivial protocol-witness no-ops and identity/return-0 shims, word/16-
 * byte copy helpers, Swift opaque-metadata descriptor getters (16-byte
 * {address, discriminator} pairs), bit-vector manipulation primitives, and a
 * few noreturn fatal-error / precondition-failure trampolines (string
 * grapheme-break and FloatingPointToString precondition paths).
 *
 * Calling-convention note (as in the sibling slices): the decompiler shows most
 * of these as `void FUN(void)` because arguments are passed in registers and not
 * modelled as formal parameters. Where a body reads an `unaff_xNN`/`in_xNN`
 * register, we model that register as an explicit parameter (named for its
 * purpose) with a comment noting the source register, so the body compiles
 * while staying faithful to the observed register usage.
 */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>

typedef uint64_t word_t;
typedef uint64_t cptr_t;
typedef uint32_t seL4_Word;
typedef unsigned long ulong;

/* 16-byte (two-word) Swift value returns. */
typedef struct { uint64_t lo, hi; } reg16;

/* ---- shared kernel/Swift-runtime helpers (extern; bodies live in sibling slices) ---- */

/* FUN_001afa84 — Swift string fatal-precondition path (noreturn). Passes the
 * message/type strings + lengths + a discriminator; traps with the fatal text. */
extern void swift_string_fatal_precondition(uint64_t, uint64_t, uint64_t,
                                            uint64_t, uint64_t, ...)
    __attribute__((noreturn));

/* FUN_001a89a8 — Swift small-string encode helper; returns the packed word. */
extern uint64_t swift_small_string_encode(uint64_t p1, uint64_t count, uint32_t flags);

/* FUN_00376820 — object-service forward-resolve on a global slot. */
extern void sk_obj_resolve_forward(uint64_t slot);

/* FUN_001fab14 — scheduler capacity growth; returns the new capacity. */
extern long cl4_sched_grow_capacity(unsigned long n);

/* Out-of-range / shared helpers whose bodies live in sibling slices. */
extern uint64_t FUN_00002534(uint64_t, uint64_t);  /* 0x00002534 */
extern uint64_t FUN_0006a4c0(void);                 /* 0x0006a4c0 */
extern uint64_t FUN_003246ec(uint64_t);             /* 0x003246ec */
extern uint64_t FUN_003722e4(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t); /* 0x003722e4 */
extern uint64_t FUN_0036a940(uint64_t, uint64_t, uint64_t); /* 0x0036a940 */

/* Globals referenced (string/data literals; addresses are Ghidra DAT_/s_ refs). */
extern uint64_t DAT_004eb948;  /* object slot @ 0x004eb948 */
extern uint64_t DAT_004ead58;  /* object slot @ 0x004ead58 */
extern uint64_t DAT_004e7ed0;  /* data @ 0x004e7ed0 */

/* ============================================================================
 * Function bodies, in address order.
 * ========================================================================== */

/* FUN_0034f22c @ 0x0034f22c
 * Ghidra: undefined8 FUN_0034f22c(undefined8 *param_1)
 * Copies the 16 bytes at src into the register-passed destination (in_x9) and
 * returns the second word (src[1]).
 * Confidence: medium
 * Notes: word-pair copy; destination is register-passed. */
uint64_t FUN_0034f22c(uint64_t *src, uint64_t *dst /* in_x9 */)
{
    uint64_t hi = src[1];
    uint64_t lo = src[0];
    dst[1] = hi;
    dst[0] = lo;
    return hi;
}

/* FUN_0034f23c @ 0x0034f23c
 * Ghidra: void FUN_0034f23c(undefined4 param_1)
 * Spills three register-passed values into the caller's stack frame: two words
 * (x5, x21) and a 32-bit value (param_1).
 * Confidence: medium
 * Notes: register-passed args; frame base is unaff_x29. */
void FUN_0034f23c(uint32_t word /* x0 */, uint64_t a /* x5 */,
                  uint64_t b /* x21 */, uint64_t *sp /* x29 */)
{
    *(uint64_t *)(sp - 0x48) = a;
    *(uint64_t *)(sp - 0x58) = b;
    *(uint32_t *)(sp - 0x5c) = word;
}

/* FUN_0034f264 @ 0x0034f264  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_0034f264(void) { return; }

/* FUN_0034f274 @ 0x0034f274  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_0034f274(void) { return; }

/* FUN_0034f284 @ 0x0034f284  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_0034f284(void) { return; }

/* FUN_0034f294 @ 0x0034f294  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_0034f294(void) { return; }

/* FUN_0034f2a4 @ 0x0034f2a4  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_0034f2a4(void) { return; }

/* FUN_0034f2b4 @ 0x0034f2b4  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_0034f2b4(void) { return; }

/* FUN_0034f2c4 @ 0x0034f2c4  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_0034f2c4(void) { return; }

/* FUN_0034f2d4 @ 0x0034f2d4  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_0034f2d4(void) { return; }

/* FUN_0034f2e4 @ 0x0034f2e4
 * Ghidra: void FUN_0034f2e4(void)
 * Stores the top-bit-set sentinel (0x8000000000000000) into the register-passed
 * output word. Used to seed a "max"/high-water value.
 * Confidence: medium
 * Notes: destination word is register-passed (unaff_x19). */
void FUN_0034f2e4(uint64_t *out /* x19 */)
{
    *out = 0x8000000000000000ull;
}

/* FUN_0034f2f4 @ 0x0034f2f4
 * Ghidra: void FUN_0034f2f4(undefined8 *param_1,undefined8 *param_2)
 * Copies the single word *src into *dst.
 * Confidence: medium */
void FUN_0034f2f4(uint64_t *dst, uint64_t *src)
{
    *dst = *src;
}

/* FUN_0034f304 @ 0x0034f304  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_0034f304(void) { return; }

/* FUN_0034f314 @ 0x0034f314  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_0034f314(void) { return; }

/* FUN_0034f324 @ 0x0034f324  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_0034f324(void) { return; }

/* FUN_0034f334 @ 0x0034f334  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_0034f334(void) { return; }

/* FUN_0034f344 @ 0x0034f344  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_0034f344(void) { return; }

/* FUN_0034f354 @ 0x0034f354  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_0034f354(void) { return; }

/* FUN_0034f364 @ 0x0034f364  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_0034f364(void) { return; }

/* FUN_0034f374 @ 0x0034f374  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_0034f374(void) { return; }

/* FUN_0034f384 @ 0x0034f384  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_0034f384(void) { return; }

/* FUN_0034f394 @ 0x0034f394  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_0034f394(void) { return; }

/* FUN_0034f3a4 @ 0x0034f3a4  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_0034f3a4(void) { return; }

/* FUN_0034f3b4 @ 0x0034f3b4  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_0034f3b4(void) { return; }

/* FUN_0034f3c4 @ 0x0034f3c4
 * Ghidra: void FUN_0034f3c4(long param_1)
 * Computes the difference (in_x9 - param_1) and spills it into the caller's
 * stack frame at sp-0x58.
 * Confidence: medium
 * Notes: register-passed base (in_x9) and frame base (unaff_x29). */
void FUN_0034f3c4(uint64_t value /* x0 */, uint64_t base /* x9 */, uint64_t *sp /* x29 */)
{
    *(uint64_t *)(sp - 0x58) = base - value;
}

/* FUN_0034f3d4 @ 0x0034f3d4
 * Ghidra: void FUN_0034f3d4(long param_1)
 * As FUN_0034f3c4 but spills the difference at sp-0xa8.
 * Confidence: medium
 * Notes: register-passed base (in_x9) and frame base (unaff_x29). */
void FUN_0034f3d4(uint64_t value /* x0 */, uint64_t base /* x9 */, uint64_t *sp /* x29 */)
{
    *(uint64_t *)(sp - 0xa8) = base - value;
}

/* FUN_0034f3e4 @ 0x0034f3e4  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_0034f3e4(void) { return; }

/* FUN_0034f3f4 @ 0x0034f3f4  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_0034f3f4(void) { return; }

/* FUN_0034f404 @ 0x0034f404  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_0034f404(void) { return; }

/* FUN_0034f414 @ 0x0034f414  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_0034f414(void) { return; }

/* FUN_0034f424 @ 0x0034f424  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_0034f424(void) { return; }

/* FUN_0034f434 @ 0x0034f434  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_0034f434(void) { return; }

/* FUN_0034f444 @ 0x0034f444  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_0034f444(void) { return; }

/* FUN_0034f454 @ 0x0034f454  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_0034f454(void) { return; }

/* FUN_0034f464 @ 0x0034f464  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_0034f464(void) { return; }

/* FUN_0034f474 @ 0x0034f474  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_0034f474(void) { return; }

/* FUN_0034f484 @ 0x0034f484  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_0034f484(void) { return; }

/* FUN_0034f494 @ 0x0034f494  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_0034f494(void) { return; }

/* FUN_0034f4a4 @ 0x0034f4a4  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_0034f4a4(void) { return; }

/* FUN_0034f4b4 @ 0x0034f4b4  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_0034f4b4(void) { return; }

/* FUN_0034f4c4 @ 0x0034f4c4  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_0034f4c4(void) { return; }

/* FUN_0034f4d4 @ 0x0034f4d4  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_0034f4d4(void) { return; }

/* FUN_0034f4e4 @ 0x0034f4e4  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_0034f4e4(void) { return; }

/* FUN_0034f4f4 @ 0x0034f4f4  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_0034f4f4(void) { return; }

/* FUN_0034f504 @ 0x0034f504  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_0034f504(void) { return; }

/* FUN_0034f514 @ 0x0034f514  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_0034f514(void) { return; }

/* FUN_0034f524 @ 0x0034f524  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_0034f524(void) { return; }

/* FUN_0034f534 @ 0x0034f534  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_0034f534(void) { return; }

/* FUN_0034f544 @ 0x0034f544  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_0034f544(void) { return; }

/* FUN_0034f554 @ 0x0034f554
 * Ghidra: undefined1 [16] FUN_0034f554(ulong param_1)
 * Builds a 16-byte word pair {lo: value, hi: 0} then shifts it left 64 bits,
 * yielding {lo: 0, hi: value}. Swift "shift a value up into the high word"
 * descriptor/identifier idiom.
 * Confidence: medium
 * Notes: `return auVar1 << 0x40` (128-bit shift of the pair). */
reg16 FUN_0034f554(uint64_t value)
{
    /* {lo: value, hi: 0} << 64  ==  {lo: 0, hi: value} */
    return (reg16){ .lo = 0, .hi = value };
}

/* FUN_0034f564 @ 0x0034f564  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_0034f564(void) { return; }

/* FUN_0034f574 @ 0x0034f574  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_0034f574(void) { return; }

/* FUN_0034f584 @ 0x0034f584  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_0034f584(void) { return; }

/* FUN_0034f594 @ 0x0034f594  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_0034f594(void) { return; }

/* FUN_0034f5a4 @ 0x0034f5a4  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_0034f5a4(void) { return; }

/* FUN_0034f5b4 @ 0x0034f5b4  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_0034f5b4(void) { return; }

/* FUN_0034f5c4 @ 0x0034f5c4  — returns constant 0. */
uint64_t FUN_0034f5c4(void) { return 0; }

/* FUN_0034f5d4 @ 0x0034f5d4  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_0034f5d4(void) { return; }

/* FUN_0034f5e4 @ 0x0034f5e4  — returns constant 0. */
uint64_t FUN_0034f5e4(void) { return 0; }

/* FUN_0034f5f4 @ 0x0034f5f4  — returns constant 0. */
uint64_t FUN_0034f5f4(void) { return 0; }

/* FUN_0034f604 @ 0x0034f604  — returns constant 0. */
uint64_t FUN_0034f604(void) { return 0; }

/* FUN_0034f614 @ 0x0034f614  — returns constant 0. */
uint64_t FUN_0034f614(void) { return 0; }

/* FUN_0034f624 @ 0x0034f624
 * Ghidra: undefined1 [16] FUN_0034f624(ulong param_1)
 * As FUN_0034f554: builds {lo: value, hi: 0} and shifts it left 64 to give
 * {lo: 0, hi: value}. Swift descriptor/identifier high-word idiom.
 * Confidence: medium
 * Notes: `return auVar1 << 0x40`. */
reg16 FUN_0034f624(uint64_t value)
{
    return (reg16){ .lo = 0, .hi = value };
}

/* FUN_0034f634 @ 0x0034f634  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_0034f634(void) { return; }

/* FUN_0034f644 @ 0x0034f644  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_0034f644(void) { return; }

/* FUN_0034f654 @ 0x0034f654  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_0034f654(void) { return; }

/* FUN_0034f664 @ 0x0034f664
 * Ghidra: undefined8 FUN_0034f664(undefined8 param_1,undefined8 param_2)
 * Identity shim: returns its second argument unchanged.
 * Confidence: medium */
uint64_t FUN_0034f664(uint64_t a, uint64_t b) { return b; }

/* FUN_0034f674 @ 0x0034f674  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_0034f674(void) { return; }

/* FUN_0034f688 @ 0x0034f688  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_0034f688(void) { return; }

/* FUN_0034f6a8 @ 0x0034f6a8
 * Ghidra: void FUN_0034f6a8(ulong param_1)
 * Swift String.GraphemeBreaking fatal-error path: traps with the message
 * "Fatal error" (string s_Fatal_error @ 0x005accd0), discriminator
 * 0xd000000000000034, and a grapheme index with the top bit set
 * (param | 0x8000000000000000), naming Swift.StringGraphemeBreaking.swift
 * (string @ 0x005d3570). Does not return.
 * Confidence: high (Swift fatal message construction)
 * Notes: swift_string_fatal_precondition(FUN_001afa84), noreturn. */
void FUN_0034f6a8(uint64_t grapheme_index /* x0 */)
{
    swift_string_fatal_precondition(
        (uint64_t)(uintptr_t)"Fatal error", 0xb, 2,
        0xd000000000000034ull,
        grapheme_index | 0x8000000000000000ull,
        (uint64_t)(uintptr_t)"Swift.StringGraphemeBreaking.swift", 0x22, 2);
}

/* FUN_0034f6dc @ 0x0034f6dc
 * Ghidra: void FUN_0034f6dc(void)
 * Forwards an object-service resolve on the global slot at 0x004eb948.
 * Confidence: medium
 * Notes: calls sk_obj_resolve_forward(FUN_00376820) with &DAT_004eb948. */
void FUN_0034f6dc(void)
{
    sk_obj_resolve_forward((uint64_t)&DAT_004eb948);
    return;
}

/* FUN_0034f6f8 @ 0x0034f6f8
 * Ghidra: void FUN_0034f6f8(void)
 * Forwards an object-service resolve on the global slot at 0x004ead58.
 * Confidence: medium
 * Notes: calls sk_obj_resolve_forward(FUN_00376820) with &DAT_004ead58. */
void FUN_0034f6f8(void)
{
    sk_obj_resolve_forward((uint64_t)&DAT_004ead58);
    return;
}

/* FUN_0034f714 @ 0x0034f714
 * Ghidra: void FUN_0034f714(void)
 * Thin trampoline: calls the out-of-range helper FUN_0006a4c0() and returns.
 * Confidence: medium
 * Notes: FUN_0006a4c0 shared helper. */
void FUN_0034f714(void)
{
    FUN_0006a4c0();
    return;
}

/* FUN_0034f730 @ 0x0034f730  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_0034f730(void) { return; }

/* FUN_0034f740 @ 0x0034f740
 * Ghidra: undefined1 [16] FUN_0034f740(void)
 * Returns a 16-byte Swift opaque descriptor: lo holds the address of the
 * caller's spilled word, hi holds a 4-bit discriminator extracted from the
 * register-passed tag ((tag >> 56) & 0xf).
 * Confidence: medium
 * Notes: tag is unaff_x19; the exact spilled-word address is unrepresentable,
 *   modelled as a caller-passed stack address. */
reg16 FUN_0034f740(uint64_t tag /* x19 */, uint64_t spill_addr /* &stack0x8 */)
{
    return (reg16){ .lo = spill_addr, .hi = (tag >> 0x38) & 0xf };
}

/* FUN_0034f754 @ 0x0034f754  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_0034f754(void) { return; }

/* FUN_0034f764 @ 0x0034f764  — returns constant 0. */
uint64_t FUN_0034f764(void) { return 0; }

/* FUN_0034f778 @ 0x0034f778  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_0034f778(void) { return; }

/* FUN_0034f788 @ 0x0034f788  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_0034f788(void) { return; }

/* FUN_0034f798 @ 0x0034f798  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_0034f798(void) { return; }

/* FUN_0034f7b0 @ 0x0034f7b0  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_0034f7b0(void) { return; }

/* FUN_0034f7c0 @ 0x0034f7c0  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_0034f7c0(void) { return; }

/* FUN_0034f7d8 @ 0x0034f7d8
 * Ghidra: void FUN_0034f7d8(long param_1,long param_2)
 * Copies the two words at src[1] and src[2] into dst[1] and dst[2].
 * Confidence: medium */
void FUN_0034f7d8(uint64_t *dst, uint64_t *src)
{
    dst[1] = src[1];
    dst[2] = src[2];
}

/* FUN_0034f7ec @ 0x0034f7ec
 * Ghidra: void FUN_0034f7ec(undefined8 param_1,undefined8 param_2,long param_3)
 * Stores param_1 into out[3], then calls the shared helper
 * FUN_0036a940(0x66aa10, 0x20, 0xf).
 * Confidence: medium
 * Notes: FUN_0036a940 shared helper; 0x66aa10 data ref. */
void FUN_0034f7ec(uint64_t value, uint64_t tag, uint64_t *out)
{
    out[3] = value;
    FUN_0036a940(0x66aa10, 0x20, 0xf);
}

/* FUN_0034f804 @ 0x0034f804  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_0034f804(void) { return; }

/* FUN_0034f818 @ 0x0034f818  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_0034f818(void) { return; }

/* FUN_0034f828 @ 0x0034f828
 * Ghidra: undefined1 [16] FUN_0034f828(void)
 * Returns a 16-byte pair: lo = (x24 & ~x23), hi = (x25 & ~x23). Bitwise
 * "clear masked bits" descriptor getter.
 * Confidence: medium
 * Notes: operands are register-passed (unaff_x23/x24/x25). */
reg16 FUN_0034f828(uint64_t m0 /* x24 */, uint64_t mask /* x23 */, uint64_t m1 /* x25 */)
{
    return (reg16){ .lo = m0 & ~mask, .hi = m1 & ~mask };
}

/* FUN_0034f838 @ 0x0034f838  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_0034f838(void) { return; }

/* FUN_0034f84c @ 0x0034f84c  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_0034f84c(void) { return; }

/* FUN_0034f860 @ 0x0034f860  — returns constant 0. */
uint64_t FUN_0034f860(void) { return 0; }

/* FUN_0034f874 @ 0x0034f874  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_0034f874(void) { return; }

/* FUN_0034f884 @ 0x0034f884  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_0034f884(void) { return; }

/* FUN_0034f8a8 @ 0x0034f8a8
 * Ghidra: undefined1 [16] FUN_0034f8a8(void)
 * Returns a constant 16-byte pair {lo: 0x66a9e8, hi: 0x29} — a Swift static
 * opaque-descriptor / type-metadata singleton.
 * Confidence: medium
 * Notes: constants from the body (DAT refs 0x66a9e8, literal 0x29). */
reg16 FUN_0034f8a8(void)
{
    return (reg16){ .lo = 0x66a9e8, .hi = 0x29 };
}

/* FUN_0034f8bc @ 0x0034f8bc
 * Ghidra: undefined1 [16] FUN_0034f8bc(void)
 * Returns a constant 16-byte pair {lo: 0x656250, hi: 0x4e80a8} — a Swift
 * static opaque-descriptor / type-metadata singleton.
 * Confidence: medium
 * Notes: constants from the body (DAT refs 0x656250, 0x4e80a8). */
reg16 FUN_0034f8bc(void)
{
    return (reg16){ .lo = 0x656250, .hi = 0x4e80a8 };
}

/* FUN_0034f8d0 @ 0x0034f8d0  — returns constant 0. */
uint64_t FUN_0034f8d0(void) { return 0; }

/* FUN_0034f8e4 @ 0x0034f8e4  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_0034f8e4(void) { return; }

/* FUN_0034f8f4 @ 0x0034f8f4
 * Ghidra: void FUN_0034f8f4(void)
 * Computes offset = (mask & ~inv) + index and copies one byte from
 * src[offset] to dst[offset]. Swift masked-array element copy primitive.
 * Confidence: medium
 * Notes: operands register-passed (unaff_x22/x23/x24/x26/x27). */
void FUN_0034f8f4(uint64_t dst /* x22 */, uint64_t src /* x23 */,
                  uint64_t index /* x26 */, uint64_t mask /* x24 */,
                  uint64_t inv /* x27 */)
{
    long off = (long)((mask & ~inv) + index);
    *(uint8_t *)(dst + off) = *(uint8_t *)(src + off);
}

/* FUN_0034f90c @ 0x0034f90c
 * Ghidra: undefined1 [16] FUN_0034f90c(void)
 * Loads and returns the 16 bytes at the caller's stack frame + 0x10.
 * Confidence: medium
 * Notes: frame base is unaff_x29. */
reg16 FUN_0034f90c(uint64_t *sp /* x29 */)
{
    return *(reg16 *)(sp + 0x10);
}

/* FUN_0034f924 @ 0x0034f924  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_0034f924(void) { return; }

/* FUN_0034f938 @ 0x0034f938
 * Ghidra: void FUN_0034f938(void)
 * Spills two register-passed words (x19, x20) into the caller's stack frame at
 * sp-0x78 and sp-0x70.
 * Confidence: medium
 * Notes: register-passed args; frame base is unaff_x29. */
void FUN_0034f938(uint64_t a /* x19 */, uint64_t b /* x20 */, uint64_t *sp /* x29 */)
{
    *(uint64_t *)(sp - 0x78) = a;
    *(uint64_t *)(sp - 0x70) = b;
}

/* FUN_0034f948 @ 0x0034f948
 * Ghidra: void FUN_0034f948(void)
 * Initializes an object header: stores value at obj+0x10, zeroes obj+0x18, and
 * writes the tag byte 3 at obj+0x48.
 * Confidence: medium
 * Notes: object pointer register-passed (unaff_x23); value is unaff_x19. */
void FUN_0034f948(uint64_t value /* x19 */, uint64_t *obj /* x23 */)
{
    *(uint64_t *)(obj + 0x10) = value;
    *(uint64_t *)(obj + 0x18) = 0;
    *(uint8_t *)(obj + 0x48) = 3;
}

/* FUN_0034f958 @ 0x0034f958
 * Ghidra: void FUN_0034f958(void)
 * Swift "Cannot initialize" small-string encode (string s_Cannot_initialize
 * @ 0x005ce9b0, length 0x12, flags 1) via swift_small_string_encode
 * (FUN_001a89a8). Result unused.
 * Confidence: high (Swift small-string encode)
 * Notes: swift_small_string_encode(FUN_001a89a8). */
void FUN_0034f958(void)
{
    swift_small_string_encode((uint64_t)(uintptr_t)"Cannot initialize", 0x12, 1);
}

/* FUN_0034f96c @ 0x0034f96c
 * Ghidra: undefined1 [16] FUN_0034f96c(void)
 * Returns a 16-byte Swift opaque descriptor: lo = address of the caller's
 * spilled word, hi = the register-passed value (in_stack_00000020).
 * Confidence: medium
 * Notes: value is in_stack_00000020; the spilled-word address is modelled as a
 *   caller-passed stack address. */
reg16 FUN_0034f96c(uint64_t value /* in_stack_00000020 */, uint64_t spill_addr /* &stack0x8 */)
{
    return (reg16){ .lo = spill_addr, .hi = value };
}

/* FUN_0034f97c @ 0x0034f97c  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_0034f97c(void) { return; }

/* FUN_0034f98c @ 0x0034f98c  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_0034f98c(void) { return; }

/* FUN_0034f99c @ 0x0034f99c  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_0034f99c(void) { return; }

/* FUN_0034f9b4 @ 0x0034f9b4
 * Ghidra: void FUN_0034f9b4(void)
 * Calls the shared helper FUN_00002534 with the literal 0x6560e8 and the
 * address of the global at 0x004e7ed0.
 * Confidence: medium
 * Notes: FUN_00002534 shared helper; DAT_004e7ed0. */
void FUN_0034f9b4(void)
{
    FUN_00002534(0x6560e8, (uint64_t)&DAT_004e7ed0);
    return;
}

/* FUN_0034f9c8 @ 0x0034f9c8  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_0034f9c8(void) { return; }

/* FUN_0034f9d8 @ 0x0034f9d8
 * Ghidra: undefined8 FUN_0034f9d8(void)
 * Loads and returns the word at the caller's stack frame - 0x118.
 * Confidence: medium
 * Notes: frame base is unaff_x29. */
uint64_t FUN_0034f9d8(uint64_t *sp /* x29 */)
{
    return *(uint64_t *)(sp - 0x118);
}

/* FUN_0034f9ec @ 0x0034f9ec  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_0034f9ec(void) { return; }

/* FUN_0034f9fc @ 0x0034f9fc  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_0034f9fc(void) { return; }

/* FUN_0034fa0c @ 0x0034fa0c
 * Ghidra: void FUN_0034fa0c(undefined8 *param_1)
 * Copies the word *src into the register-passed destination (in_x9).
 * Confidence: medium
 * Notes: destination word is register-passed. */
void FUN_0034fa0c(uint64_t *src, uint64_t *dst /* x9 */)
{
    *dst = *src;
}

/* FUN_0034fa1c @ 0x0034fa1c
 * Ghidra: undefined8 FUN_0034fa1c(void)
 * Loads and returns the word at the caller's stack frame - 0xa8.
 * Confidence: medium
 * Notes: frame base is unaff_x29. */
uint64_t FUN_0034fa1c(uint64_t *sp /* x29 */)
{
    return *(uint64_t *)(sp - 0xa8);
}

/* FUN_0034fa34 @ 0x0034fa34  — returns constant 0. */
uint64_t FUN_0034fa34(void) { return 0; }

/* FUN_0034fa4c @ 0x0034fa4c  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_0034fa4c(void) { return; }

/* FUN_0034fa78 @ 0x0034fa78
 * Ghidra: void FUN_0034fa78(void)
 * Clears a single bit in a bitmap word: word index (index >> 3) & ~7 selects
 * the 64-bit slot; within it the bit at (index & 0x3f) is cleared via
 * `&= (-1 << (index & 0x3f)) - 1`. Swift bit-vector clear primitive.
 * Confidence: medium
 * Notes: bitmap pointer is unaff_x19, bit index is unaff_x21. */
void FUN_0034fa78(uint64_t *bitmap /* x19 */, uint64_t index /* x21 */)
{
    ulong word_off = (index >> 3) & 0x1ffffffffffffff8ull;
    *(ulong *)((uint8_t *)bitmap + word_off) &=
        (-1L << (index & 0x3f)) - 1;
}

/* FUN_0034fa9c @ 0x0034fa9c
 * Ghidra: void FUN_0034fa9c(undefined8 param_1)
 * Swift FloatingPointToString precondition-failed path: traps with the message
 * "Precondition failed" (string s_Precondition_failed @ 0x005ce2d0), payload 0
 * and discriminator 0xe000000000000000, naming
 * Swift.FloatingPointToString.swift (string @ 0x005d33c0). Does not return.
 * Confidence: high (Swift fatal message construction)
 * Notes: swift_string_fatal_precondition(FUN_001afa84), noreturn. */
void FUN_0034fa9c(uint64_t detail /* x0 */)
{
    swift_string_fatal_precondition(
        (uint64_t)(uintptr_t)"Precondition failed", 0x13, 2,
        0, 0xe000000000000000ull,
        (uint64_t)(uintptr_t)"Swift.FloatingPointToString.swift", 0x21, 2);
}

/* FUN_0034facc @ 0x0034facc  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_0034facc(void) { return; }

/* FUN_0034fadc @ 0x0034fadc
 * Ghidra: void FUN_0034fadc(void)
 * Fetches a word via the shared helper FUN_003246ec(0xff) and passes it to
 * FUN_003722e4(0, word, 0x678ff0, 0, 0).
 * Confidence: medium
 * Notes: FUN_003246ec / FUN_003722e4 shared helpers; 0x678ff0 data ref. */
void FUN_0034fadc(void)
{
    uint64_t word = FUN_003246ec(0xff);
    FUN_003722e4(0, word, 0x678ff0, 0, 0);
}

/* FUN_0034fb14 @ 0x0034fb14
 * Ghidra: void FUN_0034fb14(long param_1)
 * Grows the scheduler capacity to at least param_1: reads the current capacity
 * from (*state)+0x18, takes the max with param_1, and calls
 * cl4_sched_grow_capacity (FUN_001fab14) with the larger value.
 * Confidence: medium
 * Notes: state pointer is register-passed (unaff_x20). */
void FUN_0034fb14(long param, long **state /* x20 */)
{
    long cur = *(*state + 0x18);
    if (cur <= param) {
        cur = param;
    }
    cl4_sched_grow_capacity((unsigned long)cur);
}
