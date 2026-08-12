/* Recreated from cl4_kernel.raw (cL4 Secure Kernel, arm64e, image base 0) —
 * the cL4 microkernel (GL1), "cL4 (679.100.61)". Ground truth: Ghidra FUN_
 * names + addresses in program cl4_kernel.raw.
 * Slice 11: 0x349ae0-0x34aef4 — a pool of shared Swift-runtime glue and
 * small utility stubs (no-op stubs, constant-return stubs, pointer getters,
 * frame-bias stores, Swift fatalError traps, and 9-byte copying helpers).
 * All names are estimates unless string/header-matched.
 * NOTE: this region is NOT the cL4 syscall dispatch table; it is mostly
 * compiler-emitted runtime helpers shared across the whole kernel. */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "sk_internal.h"

/* ------------------------------------------------------------------ *
 * Out-of-range cL4/Swift helper declarations (declared extern with a
 * one-line note; their bodies are reconstructed by the range worker that
 * owns them).
 * ------------------------------------------------------------------ */
extern uint64_t FUN_0008f6c0(void);    /* runtime helper (returns a word) */
extern uint64_t FUN_0008f6f4(void);    /* runtime helper (returns a word) */
extern void     FUN_00027754(void);    /* runtime helper */
extern void     FUN_0014ae44(void);    /* runtime helper */
extern void     FUN_0036993c(uint64_t, uint64_t, uint64_t, uint64_t); /* runtime helper */
extern void     FUN_001afe4c(uint64_t, uint64_t, uint64_t, const char *, uint64_t,
                             uint64_t, const char *, uint64_t); /* noreturn Swift fatal trap emitter */
extern void     FUN_000839f8(uint32_t, uint64_t); /* runtime helper */
extern void     FUN_00291ee0(void);    /* runtime helper */
extern void     FUN_003109b4(void);    /* runtime helper */
extern void     FUN_00310a44(void);    /* runtime helper */
extern void     FUN_00310ad4(void);    /* runtime helper */
extern void     FUN_00310a14(void);    /* runtime helper */
extern void     FUN_0016186c(void);    /* runtime helper */
extern void     FUN_003722e4(uint64_t, uint64_t, uint64_t, const char *, uint64_t); /* runtime helper */
extern void     FUN_003698b0(void *, uint64_t, void *); /* runtime helper */
extern void     FUN_00377824(uint64_t, uint64_t, uint64_t, void *, void *); /* runtime helper */
extern void     FUN_0006a4c0(uint64_t, uint64_t); /* runtime helper */
extern void     FUN_000a649c(uint64_t);  /* runtime helper */

/* 16-byte value-returning pair used by the metadata getters below. */
typedef struct sk_pair16 { uint64_t a, b; } sk_pair16_t;

/* ================================================================== *
 * FUN_00349ae0 @ 0x00349ae0   (est. sk_noop_stub)
 * Ghidra: void FUN_00349ae0(void)
 * Empty stub; performs no work.
 * Confidence: medium   Notes: -
 */
void FUN_00349ae0(void)
{
    return;
}

/* FUN_00349b00 @ 0x00349b00   (est. sk_noop_stub)
 * Ghidra: void FUN_00349b00(void)
 * Empty stub; performs no work.
 * Confidence: medium   Notes: -
 */
void FUN_00349b00(void)
{
    return;
}

/* FUN_00349b14 @ 0x00349b14   (est. sk_return_constant_0xff)
 * Ghidra: undefined8 FUN_00349b14(void)
 * Returns the constant 0xff.
 * Confidence: medium   Notes: -
 */
uint64_t FUN_00349b14(void)
{
    return 0xff;
}

/* FUN_00349b28 @ 0x00349b28   (est. sk_metadata_pair_getter)
 * Ghidra: undefined1[16] FUN_00349b28(void)
 * Returns a 16-byte pair {0x6560f8, 0x4e7ee0} (two data/pointer constants).
 * Confidence: medium   Notes: refs DAT 0x6560f8, 0x4e7ee0
 */
sk_pair16_t FUN_00349b28(void)
{
    sk_pair16_t r;
    r.a = 0x6560f8;
    r.b = 0x4e7ee0;
    return r;
}

/* FUN_00349b3c @ 0x00349b3c   (est. sk_noop_stub)
 * Empty stub.
 * Confidence: medium   Notes: -
 */
void FUN_00349b3c(void)
{
    return;
}

/* FUN_00349b50 @ 0x00349b50   (est. sk_noop_stub)
 * Empty stub.
 * Confidence: medium   Notes: -
 */
void FUN_00349b50(void)
{
    return;
}

/* FUN_00349b64 @ 0x00349b64   (est. sk_runtime_init3)
 * Ghidra: void FUN_00349b64(void)
 * Calls three runtime helpers in sequence (init/top-level calls).
 * Confidence: medium   Notes: calls FUN_0008f6f4, FUN_00027754, FUN_0014ae44
 */
void FUN_00349b64(void)
{
    FUN_0008f6f4();
    FUN_00027754();
    FUN_0014ae44();
}

/* FUN_00349b88 @ 0x00349b88   (est. sk_runtime_call_const)
 * Ghidra: void FUN_00349b88(void)
 * Calls FUN_0036993c with two data constants and two zeros.
 * Confidence: medium   Notes: calls FUN_0036993c(0x672a08, 0x66b2d0, 0, 0)
 */
void FUN_00349b88(void)
{
    FUN_0036993c(0x672a08, 0x66b2d0, 0, 0);
}

/* FUN_00349bb0 @ 0x00349bb0   (est. sk_noop_stub)
 * Empty stub.
 * Confidence: medium   Notes: -
 */
void FUN_00349bb0(void)
{
    return;
}

/* FUN_00349bc4 @ 0x00349bc4   (est. sk_noop_stub)
 * Empty stub.
 * Confidence: medium   Notes: Ghidra warns globals overlap smaller symbols here
 */
void FUN_00349bc4(void)
{
    return;
}

/* FUN_00349bfc @ 0x00349bfc   (est. sk_read_frame_slot)
 * Ghidra: undefined8 FUN_00349bfc(void)
 * Returns the 8-byte value saved in the caller frame at x29-0x68.
 * Confidence: medium   Notes: frame access via unaff_x29
 */
uint64_t FUN_00349bfc(void)
{
    return 0; /* reads *(frame - 0x68); frame not modeled */
}

/* FUN_00349c14 @ 0x00349c14   (est. sk_noop_stub)
 * Empty stub.
 * Confidence: medium   Notes: -
 */
void FUN_00349c14(void)
{
    return;
}

/* FUN_00349c2c @ 0x00349c2c   (est. sk_frame_bias_store)
 * Ghidra: void FUN_00349c2c(void)
 * Stores (frame base - x12) into the frame slot at x29-0x90 (stack depth
 * bookkeeping).
 * Confidence: medium   Notes: in_x12, unaff_x29
 */
void FUN_00349c2c(void)
{
    /* *(frame - 0x90) = (frame_top - x12); frame not modeled */
}

/* FUN_00349c44 @ 0x00349c44   (est. sk_store_offset_field)
 * Ghidra: void FUN_00349c44(long param_1, undefined8 param_2)
 * Stores param_2 into *(param_1 - 0x100) (writes an 8-byte field below an
 * object pointer).
 * Confidence: medium   Notes: param_1 + -0x100
 */
void FUN_00349c44(uint64_t obj, uint64_t value)
{
    *(uint64_t *)(obj - 0x100) = value;
}

/* FUN_00349c58 @ 0x00349c58   (est. sk_noop_stub)
 * Empty stub.
 * Confidence: medium   Notes: -
 */
void FUN_00349c58(void)
{
    return;
}

/* FUN_00349c70 @ 0x00349c70   (est. sk_noop_stub)
 * Empty stub.
 * Confidence: medium   Notes: -
 */
void FUN_00349c70(void)
{
    return;
}

/* FUN_00349c84 @ 0x00349c84   (est. sk_frame_bias_store)
 * Ghidra: void FUN_00349c84(void)
 * Stores (x9 - x12) into the frame slot at x29-0xa0 (stack depth bookkeeping).
 * Confidence: medium   Notes: in_x9, in_x12, unaff_x29
 */
void FUN_00349c84(void)
{
    /* *(frame - 0xa0) = x9 - x12; frame not modeled */
}

/* FUN_00349c98 @ 0x00349c98   (est. sk_runtime_call2)
 * Ghidra: void FUN_00349c98(void)
 * Calls runtime helper FUN_00291ee0.
 * Confidence: medium   Notes: calls FUN_00291ee0
 */
void FUN_00349c98(void)
{
    FUN_00291ee0();
}

/* FUN_00349cbc @ 0x00349cbc   (est. sk_noop_stub)
 * Empty stub.
 * Confidence: medium   Notes: -
 */
void FUN_00349cbc(void)
{
    return;
}

/* FUN_00349cd0 @ 0x00349cd0   (est. sk_noop_stub)
 * Empty stub.
 * Confidence: medium   Notes: -
 */
void FUN_00349cd0(void)
{
    return;
}

/* FUN_00349cec @ 0x00349cec   (est. sk_noop_stub)
 * Empty stub.
 * Confidence: medium   Notes: -
 */
void FUN_00349cec(void)
{
    return;
}

/* FUN_00349d14 @ 0x00349d14   (est. sk_noop_stub)
 * Empty stub.
 * Confidence: medium   Notes: Ghidra warns globals overlap smaller symbols here
 */
void FUN_00349d14(void)
{
    return;
}

/* FUN_00349d3c @ 0x00349d3c   (est. sk_noop_stub)
 * Empty stub.
 * Confidence: medium   Notes: -
 */
void FUN_00349d3c(void)
{
    return;
}

/* FUN_00349d58 @ 0x00349d58   (est. sk_noop_stub)
 * Empty stub.
 * Confidence: medium   Notes: -
 */
void FUN_00349d58(void)
{
    return;
}

/* FUN_00349d80 @ 0x00349d80   (est. sk_return_zero)
 * Ghidra: undefined8 FUN_00349d80(void)
 * Returns 0.
 * Confidence: medium   Notes: -
 */
uint64_t FUN_00349d80(void)
{
    return 0;
}

/* FUN_00349d94 @ 0x00349d94   (est. sk_noop_stub)
 * Empty stub.
 * Confidence: medium   Notes: -
 */
void FUN_00349d94(void)
{
    return;
}

/* FUN_00349db0 @ 0x00349db0   (est. sk_noop_stub)
 * Empty stub.
 * Confidence: medium   Notes: -
 */
void FUN_00349db0(void)
{
    return;
}

/* FUN_00349dcc @ 0x00349dcc   (est. sk_noop_stub)
 * Empty stub.
 * Confidence: medium   Notes: -
 */
void FUN_00349dcc(void)
{
    return;
}

/* FUN_00349de8 @ 0x00349de8   (est. sk_noop_stub)
 * Empty stub.
 * Confidence: medium   Notes: -
 */
void FUN_00349de8(void)
{
    return;
}

/* FUN_00349dfc @ 0x00349dfc   (est. sk_return_zero)
 * Ghidra: undefined8 FUN_00349dfc(void)
 * Returns 0.
 * Confidence: medium   Notes: -
 */
uint64_t FUN_00349dfc(void)
{
    return 0;
}

/* FUN_00349e10 @ 0x00349e10   (est. sk_noop_stub)
 * Empty stub.
 * Confidence: medium   Notes: -
 */
void FUN_00349e10(void)
{
    return;
}

/* FUN_00349e24 @ 0x00349e24   (est. sk_noop_stub)
 * Empty stub.
 * Confidence: medium   Notes: -
 */
void FUN_00349e24(void)
{
    return;
}

/* FUN_00349e38 @ 0x00349e38   (est. sk_global_pointer_getter)
 * Ghidra: undefined* FUN_00349e38(void)
 * Returns a pointer to the global DAT_004eb050.
 * Confidence: medium   Notes: DAT_004eb050
 */
void *FUN_00349e38(void)
{
    return (void *)0x004eb050;
}

/* FUN_00349e54 @ 0x00349e54   (est. sk_noop_stub)
 * Empty stub.
 * Confidence: medium   Notes: -
 */
void FUN_00349e54(void)
{
    return;
}

/* FUN_00349e70 @ 0x00349e70   (est. sk_global_pointer_getter)
 * Ghidra: undefined* FUN_00349e70(void)
 * Returns a pointer to the global DAT_004e9c1c.
 * Confidence: medium   Notes: DAT_004e9c1c
 */
void *FUN_00349e70(void)
{
    return (void *)0x004e9c1c;
}

/* FUN_00349e8c @ 0x00349e8c   (est. sk_noop_stub)
 * Empty stub.
 * Confidence: medium   Notes: -
 */
void FUN_00349e8c(void)
{
    return;
}

/* FUN_00349ea0 @ 0x00349ea0   (est. sk_return_zero)
 * Ghidra: undefined8 FUN_00349ea0(void)
 * Returns 0.
 * Confidence: medium   Notes: -
 */
uint64_t FUN_00349ea0(void)
{
    return 0;
}

/* FUN_00349eb8 @ 0x00349eb8   (est. sk_swift_fatal_misaligned_load)
 * Ghidra: void FUN_00349eb8(undefined8 param_1)
 * Swift fatalError trap: "load from misaligned raw pointer" on UnsafeRawPointer.
 * Does not return; calls FUN_001afe4c to emit the trap message.
 * Confidence: high   Notes: strings s_load_from_misaligned_raw_pointer_005cf180,
 *   s_Swift_UnsafeRawPointer_swift_005cf1b0; calls FUN_001afe4c; noreturn
 */
void FUN_00349eb8(uint64_t ptr)
{
    FUN_001afe4c(ptr, 0xb, 2,
                 "load from misaligned raw pointer", 0x20, 2,
                 "Swift UnsafeRawPointer", 0x1c);
    /* does not return */
}

/* FUN_00349ee0 @ 0x00349ee0   (est. sk_noop_stub)
 * Empty stub.
 * Confidence: medium   Notes: -
 */
void FUN_00349ee0(void)
{
    return;
}

/* FUN_00349ef4 @ 0x00349ef4   (est. sk_noop_stub)
 * Empty stub.
 * Confidence: medium   Notes: -
 */
void FUN_00349ef4(void)
{
    return;
}

/* FUN_00349f08 @ 0x00349f08   (est. sk_noop_stub)
 * Empty stub.
 * Confidence: medium   Notes: -
 */
void FUN_00349f08(void)
{
    return;
}

/* FUN_00349f24 @ 0x00349f24   (est. sk_frame_bias_store)
 * Ghidra: void FUN_00349f24(void)
 * Stores (x9 - x12) into the frame slot at x29-0x108.
 * Confidence: medium   Notes: in_x9, in_x12, unaff_x29
 */
void FUN_00349f24(void)
{
    /* *(frame - 0x108) = x9 - x12; frame not modeled */
}

/* FUN_00349f3c @ 0x00349f3c   (est. sk_runtime_call1)
 * Ghidra: void FUN_00349f3c(undefined4 param_1)
 * Calls FUN_000839f8(param_1, 1).
 * Confidence: medium   Notes: calls FUN_000839f8
 */
void FUN_00349f3c(uint32_t value)
{
    FUN_000839f8(value, 1);
}

/* FUN_00349f5c @ 0x00349f5c   (est. sk_frame_bias_store)
 * Ghidra: void FUN_00349f5c(void)
 * Stores (frame base - x12) into the frame slot at x29-0x98.
 * Confidence: medium   Notes: in_x12, unaff_x29
 */
void FUN_00349f5c(void)
{
    /* *(frame - 0x98) = (frame_top - x12); frame not modeled */
}

/* FUN_00349f74 @ 0x00349f74   (est. sk_noop_stub)
 * Empty stub.
 * Confidence: medium   Notes: -
 */
void FUN_00349f74(void)
{
    return;
}

/* FUN_00349f8c @ 0x00349f8c   (est. sk_noop_stub)
 * Empty stub.
 * Confidence: medium   Notes: -
 */
void FUN_00349f8c(void)
{
    return;
}

/* FUN_00349fa4 @ 0x00349fa4   (est. sk_noop_stub)
 * Empty stub.
 * Confidence: medium   Notes: -
 */
void FUN_00349fa4(void)
{
    return;
}

/* FUN_00349fb8 @ 0x00349fb8   (est. sk_frame_bias_store)
 * Ghidra: void FUN_00349fb8(void)
 * Stores (x9 - x12) into the frame slot at x29-0x78.
 * Confidence: medium   Notes: in_x9, in_x12, unaff_x29
 */
void FUN_00349fb8(void)
{
    /* *(frame - 0x78) = x9 - x12; frame not modeled */
}

/* FUN_00349fcc @ 0x00349fcc   (est. sk_noop_stub)
 * Empty stub.
 * Confidence: medium   Notes: -
 */
void FUN_00349fcc(void)
{
    return;
}

/* FUN_00349fe0 @ 0x00349fe0   (est. sk_runtime_init2)
 * Ghidra: void FUN_00349fe0(void)
 * Calls two runtime helpers: FUN_00027754, FUN_0014ae44.
 * Confidence: medium   Notes: calls FUN_00027754, FUN_0014ae44
 */
void FUN_00349fe0(void)
{
    FUN_00027754();
    FUN_0014ae44();
}

/* FUN_0034a000 @ 0x0034a000   (est. sk_global_pointer_getter)
 * Ghidra: undefined* FUN_0034a000(void)
 * Returns a pointer to the global DAT_004ec5ac.
 * Confidence: medium   Notes: DAT_004ec5ac
 */
void *FUN_0034a000(void)
{
    return (void *)0x004ec5ac;
}

/* FUN_0034a018 @ 0x0034a018   (est. sk_insn_bitfield_builder)
 * Ghidra: uint FUN_0034a018(long param_1, uint param_2)
 * Builds a 32-bit word from a 4-bit field in param_2 (shifted left 18) plus
 * two 6-bit fields taken from bytes 1 and 2 of param_1 (shifted left 12 and 6).
 * Classic instruction/descriptor field packing helper.
 * Confidence: medium   Notes: (param_2&0xf)<<18 | (byte1&0x3f)<<12 | (byte2&0x3f)<<6
 */
uint32_t FUN_0034a018(uint64_t p, uint32_t hi4)
{
    return ((hi4 & 0xf) << 0x12) |
           ((*(const uint8_t *)(p + 1) & 0x3f) << 0xc) |
           ((*(const uint8_t *)(p + 2) & 0x3f) << 6);
}

/* FUN_0034a034 @ 0x0034a034   (est. sk_runtime_call3)
 * Ghidra: void FUN_0034a034(void)
 * Calls runtime helper FUN_003109b4.
 * Confidence: medium   Notes: calls FUN_003109b4
 */
void FUN_0034a034(void)
{
    FUN_003109b4();
}

/* FUN_0034a054 @ 0x0034a054   (est. sk_noop_stub)
 * Empty stub.
 * Confidence: medium   Notes: -
 */
void FUN_0034a054(void)
{
    return;
}

/* FUN_0034a068 @ 0x0034a068   (est. sk_noop_stub)
 * Empty stub.
 * Confidence: medium   Notes: -
 */
void FUN_0034a068(void)
{
    return;
}

/* FUN_0034a07c @ 0x0034a07c   (est. sk_stack_ref_pair)
 * Ghidra: undefined1[16] FUN_0034a07c(void)
 * Returns {frame-0x60, 0x677880} — a frame pointer and a code/data constant.
 * Confidence: medium   Notes: unaff_x29 + -0x60, 0x677880
 */
sk_pair16_t FUN_0034a07c(void)
{
    sk_pair16_t r;
    r.a = 0;              /* frame - 0x60; frame not modeled */
    r.b = 0x677880;
    return r;
}

/* FUN_0034a090 @ 0x0034a090   (est. sk_runtime_call4)
 * Ghidra: void FUN_0034a090(void)
 * Calls runtime helper FUN_00310a44.
 * Confidence: medium   Notes: calls FUN_00310a44
 */
void FUN_0034a090(void)
{
    FUN_00310a44();
}

/* FUN_0034a0b8 @ 0x0034a0b8   (est. sk_runtime_init3b)
 * Ghidra: void FUN_0034a0b8(void)
 * Calls three runtime helpers: FUN_00310ad4, FUN_00027754, FUN_0016186c.
 * Confidence: medium   Notes: calls FUN_00310ad4, FUN_00027754, FUN_0016186c
 */
void FUN_0034a0b8(void)
{
    FUN_00310ad4();
    FUN_00027754();
    FUN_0016186c();
}

/* FUN_0034a0e0 @ 0x0034a0e0   (est. sk_noop_stub)
 * Empty stub.
 * Confidence: medium   Notes: -
 */
void FUN_0034a0e0(void)
{
    return;
}

/* FUN_0034a100 @ 0x0034a100   (est. sk_noop_stub)
 * Empty stub.
 * Confidence: medium   Notes: -
 */
void FUN_0034a100(void)
{
    return;
}

/* FUN_0034a120 @ 0x0034a120   (est. sk_frame_bias_store)
 * Ghidra: void FUN_0034a120(void)
 * Stores (x9 - x12) into the frame slot at x29-0x80.
 * Confidence: medium   Notes: in_x9, in_x12, unaff_x29
 */
void FUN_0034a120(void)
{
    /* *(frame - 0x80) = x9 - x12; frame not modeled */
}

/* FUN_0034a134 @ 0x0034a134   (est. sk_noop_stub)
 * Empty stub.
 * Confidence: medium   Notes: -
 */
void FUN_0034a134(void)
{
    return;
}

/* FUN_0034a148 @ 0x0034a148   (est. sk_runtime_call2)
 * Ghidra: void FUN_0034a148(void)
 * Calls runtime helper FUN_00291ee0.
 * Confidence: medium   Notes: calls FUN_00291ee0
 */
void FUN_0034a148(void)
{
    FUN_00291ee0();
}

/* FUN_0034a168 @ 0x0034a168   (est. sk_global_pointer_getter)
 * Ghidra: undefined* FUN_0034a168(void)
 * Returns a pointer to the global DAT_004eabe4.
 * Confidence: medium   Notes: DAT_004eabe4
 */
void *FUN_0034a168(void)
{
    return (void *)0x004eabe4;
}

/* FUN_0034a180 @ 0x0034a180   (est. sk_global_pointer_getter)
 * Ghidra: undefined* FUN_0034a180(void)
 * Returns a pointer to the global DAT_004e9f64.
 * Confidence: medium   Notes: DAT_004e9f64
 */
void *FUN_0034a180(void)
{
    return (void *)0x004e9f64;
}

/* FUN_0034a198 @ 0x0034a198   (est. sk_noop_stub)
 * Empty stub.
 * Confidence: medium   Notes: -
 */
void FUN_0034a198(void)
{
    return;
}

/* FUN_0034a1b0 @ 0x0034a1b0   (est. sk_frame_bias_store)
 * Ghidra: void FUN_0034a1b0(void)
 * Stores (x9 - x12) into the frame slot at x29-0x118.
 * Confidence: medium   Notes: in_x9, in_x12, unaff_x29
 */
void FUN_0034a1b0(void)
{
    /* *(frame - 0x118) = x9 - x12; frame not modeled */
}

/* FUN_0034a1c8 @ 0x0034a1c8   (est. sk_frame_bias_store)
 * Ghidra: void FUN_0034a1c8(void)
 * Stores (x9 - x12) into the frame slot at x29-0x128.
 * Confidence: medium   Notes: in_x9, in_x12, unaff_x29
 */
void FUN_0034a1c8(void)
{
    /* *(frame - 0x128) = x9 - x12; frame not modeled */
}

/* FUN_0034a1e0 @ 0x0034a1e0   (est. sk_noop_stub)
 * Empty stub.
 * Confidence: medium   Notes: -
 */
void FUN_0034a1e0(void)
{
    return;
}

/* FUN_0034a1f8 @ 0x0034a1f8   (est. sk_noop_stub)
 * Empty stub.
 * Confidence: medium   Notes: -
 */
void FUN_0034a1f8(void)
{
    return;
}

/* FUN_0034a210 @ 0x0034a210   (est. sk_metadata_pair_getter)
 * Ghidra: undefined1[16] FUN_0034a210(void)
 * Returns {0x64c260, &DAT_004bbc30} — a data pointer and a metadata pointer.
 * Confidence: medium   Notes: DAT_0064c260, DAT_004bbc30
 */
sk_pair16_t FUN_0034a210(void)
{
    sk_pair16_t r;
    r.a = 0x64c260;
    r.b = 0x004bbc30;
    return r;
}

/* FUN_0034a224 @ 0x0034a224   (est. sk_copy_stack_args_to_struct)
 * Ghidra: void FUN_0034a224(void)
 * Copies eight stack-passed words (x19 target struct) from the incoming
 * stack slots into a structure, including a 1-byte + 7-byte tail field.
 * Used to materialize a struct from variadic-style stack arguments.
 * Confidence: medium   Notes: unaff_x19 (struct base); stack args
 */
void FUN_0034a224(void)
{
    /* Copies 8 words + 9-byte tail from stack into *(x19). Struct/frame not modeled. */
}

/* FUN_0034a238 @ 0x0034a238   (est. sk_swift_fatal_dictionary)
 * Ghidra: void FUN_0034a238(undefined8 param_1)
 * Swift fatalError trap: "Attempting to access Dictionary value with key of
 * incompatible type" on NativeDictionary. Does not return.
 * Confidence: high   Notes: strings s_Attempting_to_access_Dictionary_e_005cf210,
 *   s_Swift_NativeDictionary_swift_005be800; calls FUN_001afe4c; noreturn
 */
void FUN_0034a238(uint64_t key)
{
    FUN_001afe4c(key, 0xb, 2,
                 "Attempting to access Dictionary e", 0x3f, 2,
                 "Swift NativeDictionary", 0x1c);
    /* does not return */
}

/* FUN_0034a260 @ 0x0034a260   (est. sk_noop_stub)
 * Empty stub.
 * Confidence: medium   Notes: -
 */
void FUN_0034a260(void)
{
    return;
}

/* FUN_0034a274 @ 0x0034a274   (est. sk_noop_stub)
 * Empty stub.
 * Confidence: medium   Notes: -
 */
void FUN_0034a274(void)
{
    return;
}

/* FUN_0034a288 @ 0x0034a288   (est. sk_stack_ref_pair)
 * Ghidra: undefined1[16] FUN_0034a288(void)
 * Returns {frame-0x58, 0x6777e0} — a frame pointer and a code/data constant.
 * Confidence: medium   Notes: unaff_x29 + -0x58, 0x6777e0
 */
sk_pair16_t FUN_0034a288(void)
{
    sk_pair16_t r;
    r.a = 0;              /* frame - 0x58; frame not modeled */
    r.b = 0x6777e0;
    return r;
}

/* FUN_0034a2ac @ 0x0034a2ac   (est. sk_frame_bias_store)
 * Ghidra: void FUN_0034a2ac(long param_1)
 * Stores (frame base - param_1) into the frame slot at x29-0xb8.
 * Confidence: medium   Notes: param_1, unaff_x29
 */
void FUN_0034a2ac(uint64_t p)
{
    /* *(frame - 0xb8) = (frame_top - p); frame not modeled */
}

/* FUN_0034a2c0 @ 0x0034a2c0   (est. sk_stack_bias)
 * Ghidra: long FUN_0034a2c0(long param_1)
 * Returns (frame base - param_1); a stack-depth/bias computation.
 * Confidence: medium   Notes: &stack0x00000000 - param_1
 */
int64_t FUN_0034a2c0(int64_t p)
{
    return (int64_t)&p - p; /* frame base approximated by local address */
}

/* FUN_0034a2dc @ 0x0034a2dc   (est. sk_noop_stub)
 * Empty stub.
 * Confidence: medium   Notes: -
 */
void FUN_0034a2dc(void)
{
    return;
}

/* FUN_0034a2f8 @ 0x0034a2f8   (est. sk_noop_stub)
 * Empty stub.
 * Confidence: medium   Notes: -
 */
void FUN_0034a2f8(void)
{
    return;
}

/* FUN_0034a30c @ 0x0034a30c   (est. sk_runtime_init2)
 * Ghidra: void FUN_0034a30c(void)
 * Calls two runtime helpers: FUN_00027754, FUN_0014ae44.
 * Confidence: medium   Notes: calls FUN_00027754, FUN_0014ae44
 */
void FUN_0034a30c(void)
{
    FUN_00027754();
    FUN_0014ae44();
}

/* FUN_0034a32c @ 0x0034a32c   (est. sk_noop_stub)
 * Empty stub.
 * Confidence: medium   Notes: -
 */
void FUN_0034a32c(void)
{
    return;
}

/* FUN_0034a340 @ 0x0034a340   (est. sk_noop_stub)
 * Empty stub.
 * Confidence: medium   Notes: -
 */
void FUN_0034a340(void)
{
    return;
}

/* FUN_0034a354 @ 0x0034a354   (est. sk_noop_stub)
 * Empty stub.
 * Confidence: medium   Notes: -
 */
void FUN_0034a354(void)
{
    return;
}

/* FUN_0034a368 @ 0x0034a368   (est. sk_noop_stub)
 * Empty stub.
 * Confidence: medium   Notes: -
 */
void FUN_0034a368(void)
{
    return;
}

/* FUN_0034a37c @ 0x0034a37c   (est. sk_noop_stub)
 * Empty stub.
 * Confidence: medium   Notes: -
 */
void FUN_0034a37c(void)
{
    return;
}

/* FUN_0034a390 @ 0x0034a390   (est. sk_runtime_call2)
 * Ghidra: void FUN_0034a390(void)
 * Calls runtime helper FUN_00291ee0.
 * Confidence: medium   Notes: calls FUN_00291ee0
 */
void FUN_0034a390(void)
{
    FUN_00291ee0();
}

/* FUN_0034a3b0 @ 0x0034a3b0   (est. sk_noop_stub)
 * Empty stub.
 * Confidence: medium   Notes: -
 */
void FUN_0034a3b0(void)
{
    return;
}

/* FUN_0034a3c4 @ 0x0034a3c4   (est. sk_return_constant_0xff)
 * Ghidra: undefined8 FUN_0034a3c4(void)
 * Returns the constant 0xff.
 * Confidence: medium   Notes: -
 */
uint64_t FUN_0034a3c4(void)
{
    return 0xff;
}

/* FUN_0034a3d8 @ 0x0034a3d8   (est. sk_noop_stub)
 * Empty stub.
 * Confidence: medium   Notes: -
 */
void FUN_0034a3d8(void)
{
    return;
}

/* FUN_0034a3ec @ 0x0034a3ec   (est. sk_noop_stub)
 * Empty stub.
 * Confidence: medium   Notes: -
 */
void FUN_0034a3ec(void)
{
    return;
}

/* FUN_0034a400 @ 0x0034a400   (est. sk_frame_bias_store)
 * Ghidra: void FUN_0034a400(void)
 * Stores (x9 - x12) into the frame slot at x29-0xc0.
 * Confidence: medium   Notes: in_x9, in_x12, unaff_x29
 */
void FUN_0034a400(void)
{
    /* *(frame - 0xc0) = x9 - x12; frame not modeled */
}

/* FUN_0034a414 @ 0x0034a414   (est. sk_frame_bias_store)
 * Ghidra: void FUN_0034a414(void)
 * Stores (x9 - x12) into the frame slot at x29-0x88.
 * Confidence: medium   Notes: in_x9, in_x12, unaff_x29
 */
void FUN_0034a414(void)
{
    /* *(frame - 0x88) = x9 - x12; frame not modeled */
}

/* FUN_0034a428 @ 0x0034a428   (est. sk_noop_stub)
 * Empty stub.
 * Confidence: medium   Notes: -
 */
void FUN_0034a428(void)
{
    return;
}

/* FUN_0034a43c @ 0x0034a43c   (est. sk_noop_stub)
 * Empty stub.
 * Confidence: medium   Notes: -
 */
void FUN_0034a43c(void)
{
    return;
}

/* FUN_0034a450 @ 0x0034a450   (est. sk_noop_stub)
 * Empty stub.
 * Confidence: medium   Notes: -
 */
void FUN_0034a450(void)
{
    return;
}

/* FUN_0034a464 @ 0x0034a464   (est. sk_noop_stub)
 * Empty stub.
 * Confidence: medium   Notes: -
 */
void FUN_0034a464(void)
{
    return;
}

/* FUN_0034a478 @ 0x0034a478   (est. sk_noop_stub)
 * Empty stub.
 * Confidence: medium   Notes: -
 */
void FUN_0034a478(void)
{
    return;
}

/* FUN_0034a48c @ 0x0034a48c   (est. sk_noop_stub)
 * Empty stub.
 * Confidence: medium   Notes: -
 */
void FUN_0034a48c(void)
{
    return;
}

/* FUN_0034a4a4 @ 0x0034a4a4   (est. sk_noop_stub)
 * Empty stub.
 * Confidence: medium   Notes: -
 */
void FUN_0034a4a4(void)
{
    return;
}

/* FUN_0034a4bc @ 0x0034a4bc   (est. sk_runtime_init3b)
 * Ghidra: void FUN_0034a4bc(void)
 * Calls three runtime helpers: FUN_00310ad4, FUN_00027754, FUN_0016186c.
 * Confidence: medium   Notes: calls FUN_00310ad4, FUN_00027754, FUN_0016186c
 */
void FUN_0034a4bc(void)
{
    FUN_00310ad4();
    FUN_00027754();
    FUN_0016186c();
}

/* FUN_0034a4e0 @ 0x0034a4e0   (est. sk_frame_bias_store)
 * Ghidra: void FUN_0034a4e0(void)
 * Stores (x9 - x12) into the frame slot at x29-0x120.
 * Confidence: medium   Notes: in_x9, in_x12, unaff_x29
 */
void FUN_0034a4e0(void)
{
    /* *(frame - 0x120) = x9 - x12; frame not modeled */
}

/* FUN_0034a4f8 @ 0x0034a4f8   (est. sk_frame_bias_store)
 * Ghidra: void FUN_0034a4f8(void)
 * Stores (x9 - x12) into the frame slot at x29-0x150.
 * Confidence: medium   Notes: in_x9, in_x12, unaff_x29
 */
void FUN_0034a4f8(void)
{
    /* *(frame - 0x150) = x9 - x12; frame not modeled */
}

/* FUN_0034a510 @ 0x0034a510   (est. sk_frame_bias_store)
 * Ghidra: void FUN_0034a510(void)
 * Stores (x9 - x12) into the frame slot at x29-0x140.
 * Confidence: medium   Notes: in_x9, in_x12, unaff_x29
 */
void FUN_0034a510(void)
{
    /* *(frame - 0x140) = x9 - x12; frame not modeled */
}

/* FUN_0034a528 @ 0x0034a528   (est. sk_noop_stub)
 * Empty stub.
 * Confidence: medium   Notes: -
 */
void FUN_0034a528(void)
{
    return;
}

/* FUN_0034a540 @ 0x0034a540   (est. sk_noop_stub)
 * Empty stub.
 * Confidence: medium   Notes: -
 */
void FUN_0034a540(void)
{
    return;
}

/* FUN_0034a558 @ 0x0034a558   (est. sk_noop_stub)
 * Empty stub.
 * Confidence: medium   Notes: -
 */
void FUN_0034a558(void)
{
    return;
}

/* FUN_0034a570 @ 0x0034a570   (est. sk_noop_stub)
 * Empty stub.
 * Confidence: medium   Notes: -
 */
void FUN_0034a570(void)
{
    return;
}

/* FUN_0034a588 @ 0x0034a588   (est. sk_runtime_call4)
 * Ghidra: void FUN_0034a588(void)
 * Calls runtime helper FUN_00310a44.
 * Confidence: medium   Notes: calls FUN_00310a44
 */
void FUN_0034a588(void)
{
    FUN_00310a44();
}

/* FUN_0034a5a8 @ 0x0034a5a8   (est. sk_runtime_call3)
 * Ghidra: void FUN_0034a5a8(void)
 * Calls runtime helper FUN_003109b4.
 * Confidence: medium   Notes: calls FUN_003109b4
 */
void FUN_0034a5a8(void)
{
    FUN_003109b4();
}

/* FUN_0034a5c8 @ 0x0034a5c8   (est. sk_noop_stub)
 * Empty stub.
 * Confidence: medium   Notes: -
 */
void FUN_0034a5c8(void)
{
    return;
}

/* FUN_0034a5dc @ 0x0034a5dc   (est. sk_noop_stub)
 * Empty stub.
 * Confidence: medium   Notes: -
 */
void FUN_0034a5dc(void)
{
    return;
}

/* FUN_0034a5f0 @ 0x0034a5f0   (est. sk_noop_stub)
 * Empty stub.
 * Confidence: medium   Notes: -
 */
void FUN_0034a5f0(void)
{
    return;
}

/* FUN_0034a604 @ 0x0034a604   (est. sk_noop_stub)
 * Empty stub.
 * Confidence: medium   Notes: -
 */
void FUN_0034a604(void)
{
    return;
}

/* FUN_0034a618 @ 0x0034a618   (est. sk_noop_stub)
 * Empty stub.
 * Confidence: medium   Notes: -
 */
void FUN_0034a618(void)
{
    return;
}

/* FUN_0034a62c @ 0x0034a62c   (est. sk_frame_bias_store)
 * Ghidra: void FUN_0034a62c(void)
 * Stores (x9 - x12) into the frame slot at x29-0xa8.
 * Confidence: medium   Notes: in_x9, in_x12, unaff_x29
 */
void FUN_0034a62c(void)
{
    /* *(frame - 0xa8) = x9 - x12; frame not modeled */
}

/* FUN_0034a640 @ 0x0034a640   (est. sk_noop_stub)
 * Empty stub.
 * Confidence: medium   Notes: -
 */
void FUN_0034a640(void)
{
    return;
}

/* FUN_0034a654 @ 0x0034a654   (est. sk_runtime_assert_upper_lower)
 * Ghidra: void FUN_0034a654(undefined8 param_1)
 * Calls FUN_003722e4(0, param_1, param_1, "lower_upper", 0) — a bounds/
 * invariant check tagged "lower_upper" (range-marker assertion).
 * Confidence: medium   Notes: string s_lower_upper_005e1f90; calls FUN_003722e4
 */
void FUN_0034a654(uint64_t value)
{
    FUN_003722e4(0, value, value, "lower_upper", 0);
}

/* FUN_0034a674 @ 0x0034a674   (est. sk_store_frame_slot)
 * Ghidra: void FUN_0034a674(undefined8 param_1)
 * Stores param_1 into the frame slot at x29-0x68.
 * Confidence: medium   Notes: unaff_x29 + -0x68
 */
void FUN_0034a674(uint64_t value)
{
    /* *(frame - 0x68) = value; frame not modeled */
}

/* FUN_0034a688 @ 0x0034a688   (est. sk_noop_stub)
 * Empty stub.
 * Confidence: medium   Notes: -
 */
void FUN_0034a688(void)
{
    return;
}

/* FUN_0034a69c @ 0x0034a69c   (est. sk_noop_stub)
 * Empty stub.
 * Confidence: medium   Notes: -
 */
void FUN_0034a69c(void)
{
    return;
}

/* FUN_0034a6b0 @ 0x0034a6b0   (est. sk_noop_stub)
 * Empty stub.
 * Confidence: medium   Notes: -
 */
void FUN_0034a6b0(void)
{
    return;
}

/* FUN_0034a6c4 @ 0x0034a6c4   (est. sk_swift_retain_copy9)
 * Ghidra: undefined1[16] FUN_0034a6c4(long param_1)
 * Copies 9 bytes from one aligned location to another (Swift object header
 * move) and returns the pair of resulting pointers. Alignment mask comes
 * from an in-register high bit (x27|7); both source/dest derived from param_1
 * with two in-register offsets (x23, x24).
 * Confidence: medium   Notes: 9-byte copy, unaff_x23/x24/x27, alignment masks
 */
sk_pair16_t FUN_0034a6c4(uint64_t base)
{
    /* Copies 9 bytes between two aligned slots in base; returns both addresses.
     * Masks/offsets come from unmodelled registers x23/x24/x27. */
    sk_pair16_t r;
    r.a = 0;
    r.b = 0;
    return r;
}

/* FUN_0034a708 @ 0x0034a708   (est. sk_swift_retain_copy9b)
 * Ghidra: undefined1[16] FUN_0034a708(long param_1)
 * Same 9-byte aligned copy as FUN_0034a6c4, with offsets from x23/x24 and a
 * mask from x26. Returns the pair of resulting pointers.
 * Confidence: medium   Notes: 9-byte copy, unaff_x23/x24/x26, alignment masks
 */
sk_pair16_t FUN_0034a708(uint64_t base)
{
    /* Copies 9 bytes between two aligned slots in base; returns both addresses.
     * Masks/offsets come from unmodelled registers x23/x24/x26. */
    sk_pair16_t r;
    r.a = 0;
    r.b = 0;
    return r;
}

/* FUN_0034a74c @ 0x0034a74c   (est. sk_noop_stub)
 * Empty stub.
 * Confidence: medium   Notes: -
 */
void FUN_0034a74c(void)
{
    return;
}

/* FUN_0034a760 @ 0x0034a760   (est. sk_frame_bias_store)
 * Ghidra: void FUN_0034a760(long param_1)
 * Stores (frame base - param_1) into the frame slot at x29-0x90.
 * Confidence: medium   Notes: param_1, unaff_x29
 */
void FUN_0034a760(uint64_t p)
{
    /* *(frame - 0x90) = (frame_top - p); frame not modeled */
}

/* FUN_0034a774 @ 0x0034a774   (est. sk_runtime_word_pair)
 * Ghidra: undefined1[16] FUN_0034a774(void)
 * Calls FUN_0008f6c0 then FUN_0008f6f4, returning {result, 0} shifted into
 * the high word (auVar1 << 0x40). Pairs a runtime word with a zero low half.
 * Confidence: medium   Notes: calls FUN_0008f6c0, FUN_0008f6f4; << 0x40
 */
sk_pair16_t FUN_0034a774(void)
{
    sk_pair16_t r;
    FUN_0008f6c0();
    r.a = FUN_0008f6f4();
    r.b = 0;
    return r;
}

/* FUN_0034a798 @ 0x0034a798   (est. sk_noop_stub)
 * Empty stub.
 * Confidence: medium   Notes: -
 */
void FUN_0034a798(void)
{
    return;
}

/* FUN_0034a7ac @ 0x0034a7ac   (est. sk_noop_stub)
 * Empty stub.
 * Confidence: medium   Notes: -
 */
void FUN_0034a7ac(void)
{
    return;
}

/* FUN_0034a7c0 @ 0x0034a7c0   (est. sk_runtime_init2b)
 * Ghidra: void FUN_0034a7c0(void)
 * Calls two runtime helpers: FUN_00310ad4, FUN_00027754.
 * Confidence: medium   Notes: calls FUN_00310ad4, FUN_00027754
 */
void FUN_0034a7c0(void)
{
    FUN_00310ad4();
    FUN_00027754();
}

/* FUN_0034a7e0 @ 0x0034a7e0   (est. sk_ptr_plus_0x40)
 * Ghidra: long FUN_0034a7e0(void)
 * Returns (x21 + 0x40) — a pointer advanced by 64 bytes from a callee-saved
 * register.
 * Confidence: medium   Notes: unaff_x21 + 0x40
 */
int64_t FUN_0034a7e0(void)
{
    /* returns x21 + 0x40; x21 not modeled */
    return 0;
}

/* FUN_0034a808 @ 0x0034a808   (est. sk_noop_stub)
 * Empty stub.
 * Confidence: medium   Notes: -
 */
void FUN_0034a808(void)
{
    return;
}

/* FUN_0034a820 @ 0x0034a820   (est. sk_noop_stub)
 * Empty stub.
 * Confidence: medium   Notes: -
 */
void FUN_0034a820(void)
{
    return;
}

/* FUN_0034a834 @ 0x0034a834   (est. sk_noop_stub)
 * Empty stub.
 * Confidence: medium   Notes: -
 */
void FUN_0034a834(void)
{
    return;
}

/* FUN_0034a848 @ 0x0034a848   (est. sk_noop_stub)
 * Empty stub.
 * Confidence: medium   Notes: -
 */
void FUN_0034a848(void)
{
    return;
}

/* FUN_0034a868 @ 0x0034a868   (est. sk_noop_stub)
 * Empty stub.
 * Confidence: medium   Notes: -
 */
void FUN_0034a868(void)
{
    return;
}

/* FUN_0034a880 @ 0x0034a880   (est. sk_runtime_call3c)
 * Ghidra: void FUN_0034a880(void)
 * Calls FUN_003698b0(stack-0x1f, 0x678da0, &DAT_004f2438).
 * Confidence: medium   Notes: calls FUN_003698b0; DAT_004f2438
 */
void FUN_0034a880(void)
{
    FUN_003698b0((void *)0, 0x678da0, (void *)0x004f2438);
}

/* FUN_0034a8a4 @ 0x0034a8a4   (est. sk_noop_stub)
 * Empty stub.
 * Confidence: medium   Notes: -
 */
void FUN_0034a8a4(void)
{
    return;
}

/* FUN_0034a8cc @ 0x0034a8cc   (est. sk_noop_stub)
 * Empty stub.
 * Confidence: medium   Notes: -
 */
void FUN_0034a8cc(void)
{
    return;
}

/* FUN_0034a8e8 @ 0x0034a8e8   (est. sk_noop_stub)
 * Empty stub.
 * Confidence: medium   Notes: -
 */
void FUN_0034a8e8(void)
{
    return;
}

/* FUN_0034a900 @ 0x0034a900   (est. sk_noop_stub)
 * Empty stub.
 * Confidence: medium   Notes: -
 */
void FUN_0034a900(void)
{
    return;
}

/* FUN_0034a914 @ 0x0034a914   (est. sk_runtime_call3d)
 * Ghidra: void FUN_0034a914(undefined8 param_1, undefined8 param_2, long param_3)
 * Calls FUN_00377824(0, *(param_3+0x18), *(param_3+0x10), &DAT_00611b24,
 * &DAT_00611b3c) — dispatches on two object fields with two data constants.
 * Confidence: medium   Notes: calls FUN_00377824; DAT_00611b24, DAT_00611b3c
 */
void FUN_0034a914(uint64_t a, uint64_t b, uint64_t obj)
{
    FUN_00377824(0, *(uint64_t *)(obj + 0x18), *(uint64_t *)(obj + 0x10),
                 (void *)0x00611b24, (void *)0x00611b3c);
}

/* FUN_0034a944 @ 0x0034a944   (est. sk_return_constant_0xff)
 * Ghidra: undefined8 FUN_0034a944(void)
 * Returns the constant 0xff.
 * Confidence: medium   Notes: -
 */
uint64_t FUN_0034a944(void)
{
    return 0xff;
}

/* FUN_0034a958 @ 0x0034a958   (est. sk_identity_pass_3rd)
 * Ghidra: undefined8 FUN_0034a958(undefined8 param_1, undefined8 param_2,
 *                                 undefined8 param_3)
 * Returns its third argument unchanged.
 * Confidence: medium   Notes: -
 */
uint64_t FUN_0034a958(uint64_t a, uint64_t b, uint64_t c)
{
    return c;
}

/* FUN_0034a96c @ 0x0034a96c   (est. sk_noop_stub)
 * Empty stub.
 * Confidence: medium   Notes: -
 */
void FUN_0034a96c(void)
{
    return;
}

/* FUN_0034a980 @ 0x0034a980   (est. sk_return_zero)
 * Ghidra: undefined8 FUN_0034a980(void)
 * Returns 0.
 * Confidence: medium   Notes: -
 */
uint64_t FUN_0034a980(void)
{
    return 0;
}

/* FUN_0034a9ac @ 0x0034a9ac   (est. sk_frame_bias_store)
 * Ghidra: void FUN_0034a9ac(void)
 * Stores (x9 - x12) into the frame slot at x29-0xb0.
 * Confidence: medium   Notes: in_x9, in_x12, unaff_x29
 */
void FUN_0034a9ac(void)
{
    /* *(frame - 0xb0) = x9 - x12; frame not modeled */
}

/* FUN_0034a9c0 @ 0x0034a9c0   (est. sk_frame_bias_store)
 * Ghidra: void FUN_0034a9c0(void)
 * Stores (x9 - x12) into the frame slot at x29-0xe0.
 * Confidence: medium   Notes: in_x9, in_x12, unaff_x29
 */
void FUN_0034a9c0(void)
{
    /* *(frame - 0xe0) = x9 - x12; frame not modeled */
}

/* FUN_0034a9d4 @ 0x0034a9d4   (est. sk_frame_bias_store)
 * Ghidra: void FUN_0034a9d4(void)
 * Stores (x9 - x12) into the frame slot at x29-0xd8.
 * Confidence: medium   Notes: in_x9, in_x12, unaff_x29
 */
void FUN_0034a9d4(void)
{
    /* *(frame - 0xd8) = x9 - x12; frame not modeled */
}

/* FUN_0034a9e8 @ 0x0034a9e8   (est. sk_frame_bias_store)
 * Ghidra: void FUN_0034a9e8(void)
 * Stores (x9 - x12) into the frame slot at x29-0xd0.
 * Confidence: medium   Notes: in_x9, in_x12, unaff_x29
 */
void FUN_0034a9e8(void)
{
    /* *(frame - 0xd0) = x9 - x12; frame not modeled */
}

/* FUN_0034a9fc @ 0x0034a9fc   (est. sk_noop_stub)
 * Empty stub.
 * Confidence: medium   Notes: -
 */
void FUN_0034a9fc(void)
{
    return;
}

/* FUN_0034aa14 @ 0x0034aa14   (est. sk_frame_bias_store)
 * Ghidra: void FUN_0034aa14(void)
 * Stores (frame base - x12) into the frame slot at x29-0xa8.
 * Confidence: medium   Notes: in_x12, unaff_x29
 */
void FUN_0034aa14(void)
{
    /* *(frame - 0xa8) = (frame_top - x12); frame not modeled */
}

/* FUN_0034aa28 @ 0x0034aa28   (est. sk_frame_bias_store)
 * Ghidra: void FUN_0034aa28(void)
 * Stores (frame base - x12) into the frame slot at x29-0x80.
 * Confidence: medium   Notes: in_x12, unaff_x29
 */
void FUN_0034aa28(void)
{
    /* *(frame - 0x80) = (frame_top - x12); frame not modeled */
}

/* FUN_0034aa3c @ 0x0034aa3c   (est. sk_noop_stub)
 * Empty stub.
 * Confidence: medium   Notes: -
 */
void FUN_0034aa3c(void)
{
    return;
}

/* FUN_0034aa54 @ 0x0034aa54   (est. sk_runtime_call1)
 * Ghidra: void FUN_0034aa54(undefined4 param_1)
 * Calls FUN_000839f8(param_1, 1).
 * Confidence: medium   Notes: calls FUN_000839f8
 */
void FUN_0034aa54(uint32_t value)
{
    FUN_000839f8(value, 1);
}

/* FUN_0034aa74 @ 0x0034aa74   (est. sk_store_frame_slot)
 * Ghidra: void FUN_0034aa74(void)
 * Stores x20 into the frame slot at x29-0x68.
 * Confidence: medium   Notes: unaff_x20, unaff_x29
 */
void FUN_0034aa74(void)
{
    /* *(frame - 0x68) = x20; frame not modeled */
}

/* FUN_0034aa9c @ 0x0034aa9c   (est. sk_frame_bias_store)
 * Ghidra: void FUN_0034aa9c(long param_1)
 * Stores (frame base - param_1) into the frame slot at x29-0xc0.
 * Confidence: medium   Notes: param_1, unaff_x29
 */
void FUN_0034aa9c(uint64_t p)
{
    /* *(frame - 0xc0) = (frame_top - p); frame not modeled */
}

/* FUN_0034aab0 @ 0x0034aab0   (est. sk_frame_bias_store)
 * Ghidra: void FUN_0034aab0(long param_1)
 * Stores (frame base - param_1) into the frame slot at x29-0x80.
 * Confidence: medium   Notes: param_1, unaff_x29
 */
void FUN_0034aab0(uint64_t p)
{
    /* *(frame - 0x80) = (frame_top - p); frame not modeled */
}

/* FUN_0034aac4 @ 0x0034aac4   (est. sk_frame_bias_store)
 * Ghidra: void FUN_0034aac4(void)
 * Stores (frame base - x12) into the frame slot at x29-0x100.
 * Confidence: medium   Notes: in_x12, unaff_x29
 */
void FUN_0034aac4(void)
{
    /* *(frame - 0x100) = (frame_top - x12); frame not modeled */
}

/* FUN_0034aadc @ 0x0034aadc   (est. sk_frame_bias_store)
 * Ghidra: void FUN_0034aadc(void)
 * Stores (frame base - x12) into the frame slot at x29-0xe8.
 * Confidence: medium   Notes: in_x12, unaff_x29
 */
void FUN_0034aadc(void)
{
    /* *(frame - 0xe8) = (frame_top - x12); frame not modeled */
}

/* FUN_0034aaf4 @ 0x0034aaf4   (est. sk_noop_stub)
 * Empty stub.
 * Confidence: medium   Notes: -
 */
void FUN_0034aaf4(void)
{
    return;
}

/* FUN_0034ab10 @ 0x0034ab10   (est. sk_noop_stub)
 * Empty stub.
 * Confidence: medium   Notes: -
 */
void FUN_0034ab10(void)
{
    return;
}

/* FUN_0034ab20 @ 0x0034ab20   (est. sk_noop_stub)
 * Empty stub.
 * Confidence: medium   Notes: -
 */
void FUN_0034ab20(void)
{
    return;
}

/* FUN_0034ab30 @ 0x0034ab30   (est. sk_runtime_release_dispatch)
 * Ghidra: void FUN_0034ab30(long param_1)
 * Reads uVar1 = *(param_1+0x20), calls FUN_0006a4c0(param_1, *(param_1+0x18)),
 * then FUN_000a649c(uVar1). Object teardown/relinquish of two object fields.
 * Confidence: medium   Notes: calls FUN_0006a4c0, FUN_000a649c
 */
void FUN_0034ab30(uint64_t obj)
{
    uint64_t field20 = *(uint64_t *)(obj + 0x20);
    FUN_0006a4c0(obj, *(uint64_t *)(obj + 0x18));
    FUN_000a649c(field20);
}

/* FUN_0034ab88 @ 0x0034ab88   (est. sk_noop_stub)
 * Empty stub.
 * Confidence: medium   Notes: -
 */
void FUN_0034ab88(void)
{
    return;
}

/* FUN_0034ab9c @ 0x0034ab9c   (est. sk_noop_stub)
 * Empty stub.
 * Confidence: medium   Notes: -
 */
void FUN_0034ab9c(void)
{
    return;
}

/* FUN_0034abb0 @ 0x0034abb0   (est. sk_noop_stub)
 * Empty stub.
 * Confidence: medium   Notes: -
 */
void FUN_0034abb0(void)
{
    return;
}

/* FUN_0034abc4 @ 0x0034abc4   (est. sk_noop_stub)
 * Empty stub.
 * Confidence: medium   Notes: -
 */
void FUN_0034abc4(void)
{
    return;
}

/* FUN_0034abd8 @ 0x0034abd8   (est. sk_noop_stub)
 * Empty stub.
 * Confidence: medium   Notes: -
 */
void FUN_0034abd8(void)
{
    return;
}

/* FUN_0034abec @ 0x0034abec   (est. sk_frame_bias_store)
 * Ghidra: void FUN_0034abec(void)
 * Stores (x9 - x12) into the frame slot at x29-0xc8.
 * Confidence: medium   Notes: in_x9, in_x12, unaff_x29
 */
void FUN_0034abec(void)
{
    /* *(frame - 0xc8) = x9 - x12; frame not modeled */
}

/* FUN_0034ac00 @ 0x0034ac00   (est. sk_frame_bias_store)
 * Ghidra: void FUN_0034ac00(void)
 * Stores (x9 - x12) into the frame slot at x29-0x70.
 * Confidence: medium   Notes: in_x9, in_x12, unaff_x29
 */
void FUN_0034ac00(void)
{
    /* *(frame - 0x70) = x9 - x12; frame not modeled */
}

/* FUN_0034ac14 @ 0x0034ac14   (est. sk_frame_bias_store)
 * Ghidra: void FUN_0034ac14(void)
 * Stores (x9 - x12) into the frame slot at x29-0xb8.
 * Confidence: medium   Notes: in_x9, in_x12, unaff_x29
 */
void FUN_0034ac14(void)
{
    /* *(frame - 0xb8) = x9 - x12; frame not modeled */
}

/* FUN_0034ac28 @ 0x0034ac28   (est. sk_frame_bias_store)
 * Ghidra: void FUN_0034ac28(void)
 * Stores (x9 - x12) into the frame slot at x29-0x68.
 * Confidence: medium   Notes: in_x9, in_x12, unaff_x29
 */
void FUN_0034ac28(void)
{
    /* *(frame - 0x68) = x9 - x12; frame not modeled */
}

/* FUN_0034ac3c @ 0x0034ac3c   (est. sk_frame_bias_store)
 * Ghidra: void FUN_0034ac3c(void)
 * Stores (frame base - x12) into the frame slot at x29-0x70.
 * Confidence: medium   Notes: in_x12, unaff_x29
 */
void FUN_0034ac3c(void)
{
    /* *(frame - 0x70) = (frame_top - x12); frame not modeled */
}

/* FUN_0034ac50 @ 0x0034ac50   (est. sk_frame_bias_store)
 * Ghidra: void FUN_0034ac50(void)
 * Stores (frame base - x12) into the frame slot at x29-0x98.
 * Confidence: medium   Notes: in_x12, unaff_x29
 */
void FUN_0034ac50(void)
{
    /* *(frame - 0x98) = (frame_top - x12); frame not modeled */
}

/* FUN_0034ac64 @ 0x0034ac64   (est. sk_noop_stub)
 * Empty stub.
 * Confidence: medium   Notes: -
 */
void FUN_0034ac64(void)
{
    return;
}

/* FUN_0034ac78 @ 0x0034ac78   (est. sk_noop_stub)
 * Empty stub.
 * Confidence: medium   Notes: -
 */
void FUN_0034ac78(void)
{
    return;
}

/* FUN_0034ac8c @ 0x0034ac8c   (est. sk_return_zero)
 * Ghidra: undefined8 FUN_0034ac8c(void)
 * Returns 0.
 * Confidence: medium   Notes: -
 */
uint64_t FUN_0034ac8c(void)
{
    return 0;
}

/* FUN_0034aca0 @ 0x0034aca0   (est. sk_noop_stub)
 * Empty stub.
 * Confidence: medium   Notes: -
 */
void FUN_0034aca0(void)
{
    return;
}

/* FUN_0034acb0 @ 0x0034acb0   (est. sk_runtime_call5)
 * Ghidra: void FUN_0034acb0(void)
 * Calls runtime helper FUN_0016186c.
 * Confidence: medium   Notes: calls FUN_0016186c
 */
void FUN_0034acb0(void)
{
    FUN_0016186c();
}

/* FUN_0034acd0 @ 0x0034acd0   (est. sk_runtime_call6)
 * Ghidra: void FUN_0034acd0(void)
 * Calls runtime helper FUN_00310a14.
 * Confidence: medium   Notes: calls FUN_00310a14
 */
void FUN_0034acd0(void)
{
    FUN_00310a14();
}

/* FUN_0034acf0 @ 0x0034acf0   (est. sk_store_field_below)
 * Ghidra: void FUN_0034acf0(void)
 * Stores x9 into *(x10 - 0x100) (writes an 8-byte field below an object
 * pointer held in x10).
 * Confidence: medium   Notes: in_x9, in_x10 + -0x100
 */
void FUN_0034acf0(void)
{
    /* *(x10 - 0x100) = x9; registers not modeled */
}

/* FUN_0034ad00 @ 0x0034ad00   (est. sk_noop_stub)
 * Empty stub.
 * Confidence: medium   Notes: -
 */
void FUN_0034ad00(void)
{
    return;
}

/* FUN_0034ad10 @ 0x0034ad10   (est. sk_noop_stub)
 * Empty stub.
 * Confidence: medium   Notes: -
 */
void FUN_0034ad10(void)
{
    return;
}

/* FUN_0034ad20 @ 0x0034ad20   (est. sk_runtime_call7)
 * Ghidra: void FUN_0034ad20(void)
 * Calls runtime helper FUN_0006a4c0.
 * Confidence: medium   Notes: calls FUN_0006a4c0
 */
void FUN_0034ad20(void)
{
    FUN_0006a4c0(0, 0);
}

/* FUN_0034ad40 @ 0x0034ad40   (est. sk_runtime_call1)
 * Ghidra: void FUN_0034ad40(undefined4 param_1)
 * Calls FUN_000839f8(param_1, 1).
 * Confidence: medium   Notes: calls FUN_000839f8
 */
void FUN_0034ad40(uint32_t value)
{
    FUN_000839f8(value, 1);
}

/* FUN_0034ad60 @ 0x0034ad60   (est. sk_global_pointer_getter)
 * Ghidra: undefined* FUN_0034ad60(void)
 * Returns a pointer to the global DAT_004ec590.
 * Confidence: medium   Notes: DAT_004ec590
 */
void *FUN_0034ad60(void)
{
    return (void *)0x004ec590;
}

/* FUN_0034ad78 @ 0x0034ad78   (est. sk_ptr_diff)
 * Ghidra: long FUN_0034ad78(long param_1)
 * Returns (x9 - param_1) — a pointer-difference computation.
 * Confidence: medium   Notes: in_x9 - param_1
 */
int64_t FUN_0034ad78(int64_t p)
{
    /* returns x9 - p; x9 not modeled */
    return 0;
}

/* FUN_0034ad8c @ 0x0034ad8c   (est. sk_noop_stub)
 * Empty stub.
 * Confidence: medium   Notes: -
 */
void FUN_0034ad8c(void)
{
    return;
}

/* FUN_0034ada0 @ 0x0034ada0   (est. sk_noop_stub)
 * Empty stub.
 * Confidence: medium   Notes: -
 */
void FUN_0034ada0(void)
{
    return;
}

/* FUN_0034adb4 @ 0x0034adb4   (est. sk_metadata_func_pair)
 * Ghidra: undefined1[16] FUN_0034adb4(void)
 * Returns {0x6c0158, FUN_001b6734} — a data pointer plus a code pointer
 * (function reference).
 * Confidence: medium   Notes: DAT_006c0158, FUN_001b6734
 */
sk_pair16_t FUN_0034adb4(void)
{
    sk_pair16_t r;
    r.a = 0x006c0158;
    r.b = 0x001b6734;
    return r;
}

/* FUN_0034add4 @ 0x0034add4   (est. sk_metadata_func_pair)
 * Ghidra: undefined1[16] FUN_0034add4(void)
 * Returns {0x6c0150, FUN_001b60b8} — a data pointer plus a code pointer.
 * Confidence: medium   Notes: DAT_006c0150, FUN_001b60b8
 */
sk_pair16_t FUN_0034add4(void)
{
    sk_pair16_t r;
    r.a = 0x006c0150;
    r.b = 0x001b60b8;
    return r;
}

/* FUN_0034adf4 @ 0x0034adf4   (est. sk_stack_ref_pair)
 * Ghidra: undefined1[16] FUN_0034adf4(void)
 * Returns {frame-0x58, 0x6777e0} — a frame pointer and a code/data constant.
 * Confidence: medium   Notes: unaff_x29 + -0x58, 0x6777e0
 */
sk_pair16_t FUN_0034adf4(void)
{
    sk_pair16_t r;
    r.a = 0;              /* frame - 0x58; frame not modeled */
    r.b = 0x6777e0;
    return r;
}

/* FUN_0034ae08 @ 0x0034ae08   (est. sk_noop_stub)
 * Empty stub.
 * Confidence: medium   Notes: -
 */
void FUN_0034ae08(void)
{
    return;
}

/* FUN_0034ae1c @ 0x0034ae1c   (est. sk_noop_stub)
 * Empty stub.
 * Confidence: medium   Notes: -
 */
void FUN_0034ae1c(void)
{
    return;
}

/* FUN_0034ae30 @ 0x0034ae30   (est. sk_noop_stub)
 * Empty stub.
 * Confidence: medium   Notes: -
 */
void FUN_0034ae30(void)
{
    return;
}

/* FUN_0034ae44 @ 0x0034ae44   (est. sk_frame_bias_store)
 * Ghidra: void FUN_0034ae44(void)
 * Stores (x9 - x12) into the frame slot at x29-0xf8.
 * Confidence: medium   Notes: in_x9, in_x12, unaff_x29
 */
void FUN_0034ae44(void)
{
    /* *(frame - 0xf8) = x9 - x12; frame not modeled */
}

/* FUN_0034ae58 @ 0x0034ae58   (est. sk_frame_bias_store)
 * Ghidra: void FUN_0034ae58(void)
 * Stores (frame base - x12) into the frame slot at x29-0xa0.
 * Confidence: medium   Notes: in_x12, unaff_x29
 */
void FUN_0034ae58(void)
{
    /* *(frame - 0xa0) = (frame_top - x12); frame not modeled */
}

/* FUN_0034ae6c @ 0x0034ae6c   (est. sk_noop_stub)
 * Empty stub.
 * Confidence: medium   Notes: -
 */
void FUN_0034ae6c(void)
{
    return;
}

/* FUN_0034ae80 @ 0x0034ae80   (est. sk_noop_stub)
 * Empty stub.
 * Confidence: medium   Notes: -
 */
void FUN_0034ae80(void)
{
    return;
}

/* FUN_0034ae94 @ 0x0034ae94   (est. sk_noop_stub)
 * Empty stub.
 * Confidence: medium   Notes: -
 */
void FUN_0034ae94(void)
{
    return;
}

/* FUN_0034aea8 @ 0x0034aea8   (est. sk_noop_stub)
 * Empty stub.
 * Confidence: medium   Notes: -
 */
void FUN_0034aea8(void)
{
    return;
}

/* FUN_0034aebc @ 0x0034aebc   (est. sk_noop_stub)
 * Empty stub.
 * Confidence: medium   Notes: -
 */
void FUN_0034aebc(void)
{
    return;
}

/* FUN_0034aed0 @ 0x0034aed0   (est. sk_noop_stub)
 * Empty stub.
 * Confidence: medium   Notes: -
 */
void FUN_0034aed0(void)
{
    return;
}

/* FUN_0034aee4 @ 0x0034aee4   (est. sk_noop_stub)
 * Empty stub.
 * Confidence: medium   Notes: -
 */
void FUN_0034aee4(void)
{
    return;
}

/* FUN_0034aef4 @ 0x0034aef4   (est. sk_stack_ref_pair)
 * Ghidra: undefined1[16] FUN_0034aef4(void)
 * Returns {frame-0x58, 0x677880} — a frame pointer and a code/data constant.
 * Confidence: medium   Notes: unaff_x29 + -0x58, 0x677880
 */
sk_pair16_t FUN_0034aef4(void)
{
    sk_pair16_t r;
    r.a = 0;              /* frame - 0x58; frame not modeled */
    r.b = 0x677880;
    return r;
}
