/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel,
 * arm64e, image base 0) — the cL4 microkernel (GL1), "cL4 (679.100.61)".
 * Ground truth: Ghidra FUN_ names + addresses in the cl4_kernel.raw program.
 * All names are estimates unless string/header matched.
 * Range: 0x00353960 - 0x0035401c (SK gap slice 13).
 *
 * This region is a dense run of tiny Swift-runtime / protocol-witness thunks:
 * the overwhelming majority are no-op witness stubs (the compiler emitted a
 * bare `ret` for default protocol requirements that the type does not
 * implement), and the remainder are one-or-two-instruction register-forwarding
 * shims that move a value between a caller's stack slot and a callee's
 * register (the decompiler loses the linkage and reports `unaff_x29` reads /
 * writes). Bodies are kept faithful to the decompile. */

#include <stdint.h>
#include <stddef.h>
#include <string.h>

typedef uint64_t word_t;
typedef uint64_t cptr_t;
typedef uint32_t seL4_Word;
typedef unsigned long ulong;

/* 16-byte (two-word) Swift value returns. */
typedef struct { uint64_t lo, hi; } reg16;

/* ---- Shared kernel/Swift-runtime helpers (extern; bodies live in sibling
 * slices). Each notes its Ghidra FUN_ address. ---- */

/* FUN_00310a74 — resolves a (possibly pointer-tagged) object reference and
 * returns base + 0x30 + the signed int field at +0x30. */
extern uint64_t sk_obj_field0x30(uint64_t obj);

/* FUN_0001df60 — lazy-initialises the global at DAT_0064c0f8 via an
 * object-service forward resolve (FUN_00376820 on &DAT_004edbe8). */
extern void sk_obj_resolve_lazy(void);

/* FUN_003a25d4 — forwards to FUN_0036b118 with the tagged pointer masked to
 * its object payload (0x8ffffffffffffff8). */
extern void sk_obj_forward_masked(uint64_t obj);

/* FUN_002a4c98 — dense method-dispatch entry (large body); invoked here as
 * sk_dispatch_entry(a,b,c,d). */
extern void sk_dispatch_entry(uint64_t a, uint64_t b, uint64_t c, uint64_t d);

/* FUN_0008e5d8 — object field getter at +4 (base + 4 + signed int at +4). */
extern uint64_t sk_obj_field0x04(uint64_t obj);

/* FUN_00319658 — object field getter at +0x5c. */
extern uint64_t sk_obj_field0x5c(uint64_t obj);

/* FUN_00027788 — object field getter at +0x38. */
extern uint64_t sk_obj_field0x38(uint64_t obj);

/* FUN_00114330 — block/closure buffer zero-fill (param_1 = buffer, param_2 =
 * size); invokes a slow path when in_w18 bit 0 is set. */
extern void sk_buffer_zero(void *buf, uint64_t size);

/* ============================================================================
 * Function bodies, in address order.
 * ========================================================================== */

/* FUN_00353960 @ 0x00353960
 * Ghidra: undefined FUN_00353960(void)
 * No-op protocol-witness stub — returns immediately.
 * Confidence: high */
void FUN_00353960(void) { return; }

/* FUN_0035396c @ 0x0035396c
 * Ghidra: undefined FUN_0035396c(void)  [uint FUN_0035396c(uint param_1)]
 * Returns the low bit of its argument — the Swift pointer/Int tag test
 * (distinguishes small integers from object references).
 * Confidence: high */
uint32_t FUN_0035396c(uint32_t value)
{
    return value & 1u;
}

/* FUN_00353978 @ 0x00353978  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00353978(void) { return; }

/* FUN_00353984 @ 0x00353984  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00353984(void) { return; }

/* FUN_00353990 @ 0x00353990  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00353990(void) { return; }

/* FUN_0035399c @ 0x0035399c  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_0035399c(void) { return; }

/* FUN_003539a8 @ 0x003539a8
 * Ghidra: void FUN_003539a8(void)
 * Resolves an object reference and ensures the lazy global is initialised.
 * Confidence: medium
 * Notes: calls FUN_00310a74() then FUN_0001df60(); operands register-passed. */
void FUN_003539a8(uint64_t obj /* x19 */)
{
    sk_obj_field0x30(obj);
    sk_obj_resolve_lazy();
}

/* FUN_003539c8 @ 0x003539c8  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_003539c8(void) { return; }

/* FUN_003539d8 @ 0x003539d8  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_003539d8(void) { return; }

/* FUN_003539e4 @ 0x003539e4  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_003539e4(void) { return; }

/* FUN_003539f4 @ 0x003539f4  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_003539f4(void) { return; }

/* FUN_00353a00 @ 0x00353a00  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00353a00(void) { return; }

/* FUN_00353a0c @ 0x00353a0c  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00353a0c(void) { return; }

/* FUN_00353a18 @ 0x00353a18  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00353a18(void) { return; }

/* FUN_00353a24 @ 0x00353a24  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00353a24(void) { return; }

/* FUN_00353a30 @ 0x00353a30  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00353a30(void) { return; }

/* FUN_00353a3c @ 0x00353a3c
 * Ghidra: void FUN_00353a3c(undefined8 param_1,undefined8 param_2,ulong param_3)
 * Loads the 16-byte value at (param_3 & ~1) - 0x10 and extracts an 8-byte
 * element (bytes 1..8) via NEON, discarding the result — a Swift boxed-field
 * load whose result is unused at this call site.
 * Confidence: low
 * Notes: NEON_ext(...,8,1); the tagged third argument indexes a box. */
void FUN_00353a3c(uint64_t a, uint64_t b, uint64_t box)
{
    (void)a; (void)b;
    (void)*(const reg16 *)((box & ~1ull) - 0x10);
}

/* FUN_00353a54 @ 0x00353a54  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00353a54(void) { return; }

/* FUN_00353a6c @ 0x00353a6c  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00353a6c(void) { return; }

/* FUN_00353a78 @ 0x00353a78  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00353a78(void) { return; }

/* FUN_00353a84 @ 0x00353a84  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00353a84(void) { return; }

/* FUN_00353a90 @ 0x00353a90
 * Ghidra: void FUN_00353a90(void)
 * Forwards the (register-passed) object to the masked forward helper.
 * Confidence: medium
 * Notes: calls FUN_003a25d4(). */
void FUN_00353a90(uint64_t obj /* x19 */)
{
    sk_obj_forward_masked(obj);
}

/* FUN_00353aa0 @ 0x00353aa0  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00353aa0(void) { return; }

/* FUN_00353aac @ 0x00353aac  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00353aac(void) { return; }

/* FUN_00353abc @ 0x00353abc  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00353abc(void) { return; }

/* FUN_00353ac8 @ 0x00353ac8
 * Ghidra: undefined FUN_00353ac8(void)  [long FUN_00353ac8(long param_1)]
 * Reads the caller's stack slot at sp-0x58 and adds the signed int field at
 * param_1 + 0x24 — a partially-projected Swift value (base + offset).
 * Confidence: low
 * Notes: unaff_x29 frame base. */
int64_t FUN_00353ac8(int64_t *base /* x29 */, int32_t *obj /* param_1 */)
{
    return (int64_t)*(uint64_t *)((uint8_t *)base - 0x58) + (int64_t)*(int32_t *)((uint8_t *)obj + 0x24);
}

/* FUN_00353ad8 @ 0x00353ad8
 * Ghidra: void FUN_00353ad8(void)
 * Invokes the dense method-dispatch entry with the given constants.
 * Confidence: medium
 * Notes: FUN_002a4c98(0, 0xe000000000000000, 0, 0). */
void FUN_00353ad8(void)
{
    sk_dispatch_entry(0, 0xe000000000000000ull, 0, 0);
}

/* FUN_00353aec @ 0x00353aec  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00353aec(void) { return; }

/* FUN_00353af8 @ 0x00353af8  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00353af8(void) { return; }

/* FUN_00353b04 @ 0x00353b04  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00353b04(void) { return; }

/* FUN_00353b10 @ 0x00353b10  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00353b10(void) { return; }

/* FUN_00353b1c @ 0x00353b1c
 * Ghidra: void FUN_00353b1c(void)
 * Reads the object's +4 field (base + 4 + signed int at +4) and discards it —
 * a witness that computes but drops the value.
 * Confidence: medium
 * Notes: calls FUN_0008e5d8(). */
void FUN_00353b1c(uint64_t obj /* x19 */)
{
    (void)sk_obj_field0x04(obj);
}

/* FUN_00353b34 @ 0x00353b34  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00353b34(void) { return; }

/* FUN_00353b40 @ 0x00353b40  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00353b40(void) { return; }

/* FUN_00353b4c @ 0x00353b4c  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00353b4c(void) { return; }

/* FUN_00353b58 @ 0x00353b58  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00353b58(void) { return; }

/* FUN_00353b64 @ 0x00353b64
 * Ghidra: void FUN_00353b64(undefined8 param_1)
 * Stores its argument into the caller's stack slot at sp-0x130 — a
 * register-to-stack spill forwarding shim.
 * Confidence: medium
 * Notes: unaff_x29 frame base. */
void FUN_00353b64(uint64_t value /* x0 */, uint64_t *sp /* x29 */)
{
    *(uint64_t *)((uint8_t *)sp - 0x130) = value;
}

/* FUN_00353b70 @ 0x00353b70
 * Ghidra: void FUN_00353b70(undefined8 param_1)
 * Stores its argument into the caller's stack slot at sp-0x138.
 * Confidence: medium
 * Notes: unaff_x29 frame base. */
void FUN_00353b70(uint64_t value /* x0 */, uint64_t *sp /* x29 */)
{
    *(uint64_t *)((uint8_t *)sp - 0x138) = value;
}

/* FUN_00353b7c @ 0x00353b7c  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00353b7c(void) { return; }

/* FUN_00353b88 @ 0x00353b88  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00353b88(void) { return; }

/* FUN_00353b94 @ 0x00353b94
 * Ghidra: undefined FUN_00353b94(void)
 * Returns the caller's stack slot at sp-0x60.
 * Confidence: medium
 * Notes: unaff_x29 frame base. */
uint64_t FUN_00353b94(uint64_t *sp /* x29 */)
{
    return *(uint64_t *)((uint8_t *)sp - 0x60);
}

/* FUN_00353ba0 @ 0x00353ba0  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00353ba0(void) { return; }

/* FUN_00353bac @ 0x00353bac  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00353bac(void) { return; }

/* FUN_00353bb8 @ 0x00353bb8
 * Ghidra: undefined FUN_00353bb8(void)
 * Returns the caller's stack slot at sp-0x70.
 * Confidence: medium
 * Notes: unaff_x29 frame base. */
uint64_t FUN_00353bb8(uint64_t *sp /* x29 */)
{
    return *(uint64_t *)((uint8_t *)sp - 0x70);
}

/* FUN_00353bc4 @ 0x00353bc4  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00353bc4(void) { return; }

/* FUN_00353bd0 @ 0x00353bd0  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00353bd0(void) { return; }

/* FUN_00353bdc @ 0x00353bdc  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00353bdc(void) { return; }

/* FUN_00353be8 @ 0x00353be8  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00353be8(void) { return; }

/* FUN_00353bf4 @ 0x00353bf4  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00353bf4(void) { return; }

/* FUN_00353c00 @ 0x00353c00  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00353c00(void) { return; }

/* FUN_00353c0c @ 0x00353c0c  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00353c0c(void) { return; }

/* FUN_00353c18 @ 0x00353c18  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00353c18(void) { return; }

/* FUN_00353c24 @ 0x00353c24  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00353c24(void) { return; }

/* FUN_00353c30 @ 0x00353c30  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00353c30(void) { return; }

/* FUN_00353c3c @ 0x00353c3c  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00353c3c(void) { return; }

/* FUN_00353c48 @ 0x00353c48  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00353c48(void) { return; }

/* FUN_00353c54 @ 0x00353c54  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00353c54(void) { return; }

/* FUN_00353c60 @ 0x00353c60  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00353c60(void) { return; }

/* FUN_00353c6c @ 0x00353c6c  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00353c6c(void) { return; }

/* FUN_00353c78 @ 0x00353c78  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00353c78(void) { return; }

/* FUN_00353c84 @ 0x00353c84  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00353c84(void) { return; }

/* FUN_00353c90 @ 0x00353c90
 * Ghidra: undefined1 [16] FUN_00353c90(void)
 * Returns a (pointer, value) pair: a data literal address (DAT_00344204) and
 * the caller's stack address sp-0xc0 — a Swift partial-application/closure
 * descriptor value.
 * Confidence: medium
 * Notes: DAT_00344204 data ref; unaff_x29 frame base. */
reg16 FUN_00353c90(uint64_t *sp /* x29 */)
{
    return (reg16){ .lo = 0x00344204, .hi = (uint64_t)((uint8_t *)sp - 0xc0) };
}

/* FUN_00353cb4 @ 0x00353cb4
 * Ghidra: undefined FUN_00353cb4(void)
 * Returns the caller's stack address sp-0x78.
 * Confidence: medium
 * Notes: unaff_x29 frame base. */
uint64_t FUN_00353cb4(uint64_t *sp /* x29 */)
{
    return (uint64_t)((uint8_t *)sp - 0x78);
}

/* FUN_00353cc0 @ 0x00353cc0  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00353cc0(void) { return; }

/* FUN_00353ccc @ 0x00353ccc  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00353ccc(void) { return; }

/* FUN_00353cd8 @ 0x00353cd8  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00353cd8(void) { return; }

/* FUN_00353ce4 @ 0x00353ce4  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00353ce4(void) { return; }

/* FUN_00353cf0 @ 0x00353cf0  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00353cf0(void) { return; }

/* FUN_00353cfc @ 0x00353cfc  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00353cfc(void) { return; }

/* FUN_00353d14 @ 0x00353d14  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00353d14(void) { return; }

/* FUN_00353d34 @ 0x00353d34  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00353d34(void) { return; }

/* FUN_00353d44 @ 0x00353d44
 * Ghidra: void FUN_00353d44(void)
 * Resolves an object reference (register-passed) and discards the result.
 * Confidence: medium
 * Notes: calls FUN_00310a74(). */
void FUN_00353d44(uint64_t obj /* x19 */)
{
    (void)sk_obj_field0x30(obj);
}

/* FUN_00353d5c @ 0x00353d5c
 * Ghidra: float2 FUN_00353d5c(void)
 * Returns the caller's w8 register as a 2-float (NEON) pair — a vector
 * forwarding shim.
 * Confidence: low
 * Notes: in_w8 register input. */
void FUN_00353d5c(void) { /* returns vector register w8 unchanged */ }

/* FUN_00353d64 @ 0x00353d64  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00353d64(void) { return; }

/* FUN_00353d70 @ 0x00353d70  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00353d70(void) { return; }

/* FUN_00353d7c @ 0x00353d7c
 * Ghidra: undefined FUN_00353d7c(void)
 * Returns the caller's stack slot at sp-0x78.
 * Confidence: medium
 * Notes: unaff_x29 frame base. */
uint64_t FUN_00353d7c(uint64_t *sp /* x29 */)
{
    return *(uint64_t *)((uint8_t *)sp - 0x78);
}

/* FUN_00353d88 @ 0x00353d88  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00353d88(void) { return; }

/* FUN_00353d94 @ 0x00353d94
 * Ghidra: void FUN_00353d94(void)
 * Reads the object's +0x5c field and discards it.
 * Confidence: medium
 * Notes: calls FUN_00319658(). */
void FUN_00353d94(uint64_t obj /* x19 */)
{
    (void)sk_obj_field0x5c(obj);
}

/* FUN_00353dac @ 0x00353dac
 * Ghidra: undefined FUN_00353dac(long param_1)
 * Returns the word at param_1 - 0x100 (a negative-offset field load).
 * Confidence: high */
uint64_t FUN_00353dac(uint64_t base)
{
    return *(uint64_t *)(base - 0x100);
}

/* FUN_00353db8 @ 0x00353db8  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00353db8(void) { return; }

/* FUN_00353dc4 @ 0x00353dc4
 * Ghidra: void FUN_00353dc4(void)
 * Copies the two-word value at src[0..1] into dst[0..1] — a 16-byte value
 * copy between register-passed buffers.
 * Confidence: high
 * Notes: unaff_x19/x20 register-passed. */
void FUN_00353dc4(uint64_t *dst /* x19 */, uint64_t *src /* x20 */)
{
    dst[0] = src[0];
    dst[1] = src[1];
}

/* FUN_00353dd0 @ 0x00353dd0
 * Ghidra: undefined FUN_00353dd0(void)
 * Returns the data-literal address 0x6561d8 — a witness returning a global
 * symbol (closure/box).
 * Confidence: high
 * Notes: data ref 0x6561d8. */
uint64_t FUN_00353dd0(void) { return 0x6561d8; }

/* FUN_00353df0 @ 0x00353df0  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00353df0(void) { return; }

/* FUN_00353dfc @ 0x00353dfc
 * Ghidra: undefined FUN_00353dfc(void)
 * Returns the caller's stack slot at sp-0x78.
 * Confidence: medium
 * Notes: unaff_x29 frame base. */
uint64_t FUN_00353dfc(uint64_t *sp /* x29 */)
{
    return *(uint64_t *)((uint8_t *)sp - 0x78);
}

/* FUN_00353e08 @ 0x00353e08  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00353e08(void) { return; }

/* FUN_00353e14 @ 0x00353e14  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00353e14(void) { return; }

/* FUN_00353e20 @ 0x00353e20
 * Ghidra: undefined FUN_00353e20(void)
 * Returns the caller's stack slot at sp-0x90.
 * Confidence: medium
 * Notes: unaff_x29 frame base. */
uint64_t FUN_00353e20(uint64_t *sp /* x29 */)
{
    return *(uint64_t *)((uint8_t *)sp - 0x90);
}

/* FUN_00353e2c @ 0x00353e2c  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00353e2c(void) { return; }

/* FUN_00353e38 @ 0x00353e38  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00353e38(void) { return; }

/* FUN_00353e44 @ 0x00353e44  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00353e44(void) { return; }

/* FUN_00353e50 @ 0x00353e50  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00353e50(void) { return; }

/* FUN_00353e5c @ 0x00353e5c  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00353e5c(void) { return; }

/* FUN_00353e7c @ 0x00353e7c  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00353e7c(void) { return; }

/* FUN_00353e88 @ 0x00353e88  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00353e88(void) { return; }

/* FUN_00353e94 @ 0x00353e94
 * Ghidra: void FUN_00353e94(undefined8 param_1)
 * Stores its argument into the caller's stack slot at sp-0xd8.
 * Confidence: medium
 * Notes: unaff_x29 frame base. */
void FUN_00353e94(uint64_t value /* x0 */, uint64_t *sp /* x29 */)
{
    *(uint64_t *)((uint8_t *)sp - 0xd8) = value;
}

/* FUN_00353ea0 @ 0x00353ea0  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00353ea0(void) { return; }

/* FUN_00353eac @ 0x00353eac  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00353eac(void) { return; }

/* FUN_00353ecc @ 0x00353ecc
 * Ghidra: void FUN_00353ecc(undefined8 param_1)
 * Stores its argument into the caller's stack slot at sp-0x58.
 * Confidence: medium
 * Notes: unaff_x29 frame base. */
void FUN_00353ecc(uint64_t value /* x0 */, uint64_t *sp /* x29 */)
{
    *(uint64_t *)((uint8_t *)sp - 0x58) = value;
}

/* FUN_00353ed8 @ 0x00353ed8  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00353ed8(void) { return; }

/* FUN_00353ee4 @ 0x00353ee4  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00353ee4(void) { return; }

/* FUN_00353ef0 @ 0x00353ef0  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00353ef0(void) { return; }

/* FUN_00353efc @ 0x00353efc
 * Ghidra: void FUN_00353efc(void)
 * Reads the object's +0x38 field and discards it.
 * Confidence: medium
 * Notes: calls FUN_00027788(). */
void FUN_00353efc(uint64_t obj /* x19 */)
{
    (void)sk_obj_field0x38(obj);
}

/* FUN_00353f14 @ 0x00353f14  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00353f14(void) { return; }

/* FUN_00353f20 @ 0x00353f20  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00353f20(void) { return; }

/* FUN_00353f2c @ 0x00353f2c  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00353f2c(void) { return; }

/* FUN_00353f38 @ 0x00353f38  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00353f38(void) { return; }

/* FUN_00353f44 @ 0x00353f44  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00353f44(void) { return; }

/* FUN_00353f50 @ 0x00353f50  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00353f50(void) { return; }

/* FUN_00353f5c @ 0x00353f5c  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00353f5c(void) { return; }

/* FUN_00353f68 @ 0x00353f68
 * Ghidra: undefined1 [16] FUN_00353f68(ulong param_1)
 * Returns the 16-byte pair { hi=param_1, lo=0 } — a 128-bit value built by
 * shifting the argument up into the high word.
 * Confidence: high
 * Notes: `return auVar1 << 0x40`. */
reg16 FUN_00353f68(uint64_t value)
{
    return (reg16){ .lo = 0, .hi = value };
}

/* FUN_00353f88 @ 0x00353f88  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00353f88(void) { return; }

/* FUN_00353f94 @ 0x00353f94  — returns constant 0. */
uint64_t FUN_00353f94(void) { return 0; }

/* FUN_00353fa0 @ 0x00353fa0  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00353fa0(void) { return; }

/* FUN_00353fac @ 0x00353fac  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00353fac(void) { return; }

/* FUN_00353fb8 @ 0x00353fb8
 * Ghidra: void FUN_00353fb8(void)
 * Zero-fills a block buffer of size 4 bytes (register-passed buffer).
 * Confidence: medium
 * Notes: thunk_FUN_00114330(4). */
void FUN_00353fb8(uint64_t *buf /* x19 */)
{
    sk_buffer_zero(buf, 4);
}

/* FUN_00353fd4 @ 0x00353fd4  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00353fd4(void) { return; }

/* FUN_00353ff4 @ 0x00353ff4  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00353ff4(void) { return; }

/* FUN_00354000 @ 0x00354000  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00354000(void) { return; }

/* FUN_00354010 @ 0x00354010  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00354010(void) { return; }

/* FUN_0035401c @ 0x0035401c  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_0035401c(void) { return; }
