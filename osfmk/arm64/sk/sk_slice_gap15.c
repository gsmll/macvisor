/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel,
 * arm64e, image base 0) — the cL4 microkernel (GL1), "cL4 (679.100.61)".
 * Ground truth: Ghidra FUN_ names + addresses in program cl4_kernel.raw.
 * Slice GAP15: 0x00354828-0x00354fc0 (120 functions). All names are estimates
 * unless string/header-matched. Uses seL4/cL4 vocabulary (TCB, cap, CNode, IPC,
 * notification, endpoint, vspace, sched, object, slot).
 *
 * This region is a dense table of tiny Swift-runtime / Swift standard-library
 * stubs (as in sibling slices GAP07/GAP08): trivial protocol-witness no-ops
 * (79 of the 120 are empty `return;` bodies), identity / return-0 shims, frame
 * local getter/setters via the caller's frame pointer, 16-byte {lo,hi} word-pair
 * returns, lazy-global initializers, object-service forward-resolves, and a few
 * noreturn Swift precondition-failure trampolines (integer range-check fatal
 * paths). Addresses that return a 16-byte value are modelled with the `reg16`
 * {lo,hi} struct.
 *
 * Calling-convention note (as in the sibling slices): the decompiler shows most
 * of these as `void FUN(void)` because arguments are passed in registers and not
 * modelled as formal parameters. Where a body reads an `unaff_xNN`/`in_xNN`
 * register or the frame pointer `unaff_x29`, we model that register as an
 * explicit parameter (named for its purpose) with a comment noting the source
 * register, so the body compiles while staying faithful to the observed
 * register usage.
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

/* FUN_0031e104 — cL4 pointer decode helper (est. sk_decode_ptr_10_e104). */
extern void FUN_0031e104(void);

/* FUN_002b81b4 — object-service helper. */
extern void FUN_002b81b4(void);

/* FUN_002a4b90 — object allocation/insert (4 args); returns object pointer. */
extern long FUN_002a4b90(uint64_t, uint64_t, uint64_t, uint32_t);

/* FUN_00310a14 — Swift type-metadata field accessor (est. swift_type_metadata_field_20). */
extern void FUN_00310a14(void);

/* FUN_00027754 — boot/init helper. */
extern void FUN_00027754(void);

/* FUN_00002534 — lazy-global initializer: installs the resolved value into the
 * global slot `*param_1` (using `param_2` as the lazy-metadata record). */
extern void FUN_00002534(ulong *, long *);

/* FUN_001a89a8 — Swift small-string encode helper; returns the packed word. */
extern uint64_t swift_small_string_encode(uint64_t p1, uint64_t count, uint32_t flags);

/* FUN_00376820 — object-service forward-resolve on a global slot. */
extern void sk_obj_resolve_forward(uint64_t slot);

/* FUN_0031b900 — object-service end-of-slice marker helper (est. sk_obj_end_0xc). */
extern void FUN_0031b900(void);

/* FUN_000a6894 — extent descriptor helper (est. exclave_extent_d). */
extern void FUN_000a6894(void);

/* FUN_00310ca4 — Swift type-metadata field accessor (est. swift_type_metadata_field_18b). */
extern void FUN_00310ca4(void);

/* FUN_001a157c — scheduler queue iterator that invokes a callback per element
 * (est. sk_sched_queue_foreach); the callback is passed via x19. */
extern void sk_sched_queue_foreach(void (*fn)(void));

/* Callback targets handed to sk_sched_queue_foreach. */
extern void FUN_001a0908(void);   /* swift_array_reserve_variant  @0x001a0908 */
extern void FUN_001a0be4(void);   /* swift_array_reserve_variant5 @0x001a0be4 */

/* Globals referenced (string/data literals; addresses are Ghidra DAT_/s_ refs). */
extern uint64_t DAT_004e7ed8;   /* lazy-metadata record @ 0x004e7ed8 */
extern uint64_t DAT_004e7fd8;   /* lazy-metadata record @ 0x004e7fd8 */
extern uint64_t DAT_004e7fc0;   /* lazy-metadata record @ 0x004e7fc0 */
extern uint64_t DAT_004e80a0;   /* lazy-metadata record @ 0x004e80a0 */
extern uint64_t DAT_005d3bb9;   /* 2-byte string literal @ 0x005d3bb9 */
extern uint64_t DAT_004ea794;   /* object slot @ 0x004ea794 */
extern uint64_t DAT_004eac00;   /* object slot @ 0x004eac00 */
extern uint64_t DAT_004f0e1c;   /* object slot @ 0x004f0e1c */
extern uint64_t DAT_004ec318;   /* object slot @ 0x004ec318 */
extern uint64_t DAT_004e9d3c;   /* object slot @ 0x004e9d3c */
extern uint64_t DAT_004eddb0;   /* object slot @ 0x004eddb0 */

/* Swift integer-range-check precondition message:
 * "... because it is outside the representable range of type 'Int'" (0x2e chars). */
extern const char s_because_it_is_outside_the_repres_005cfbd0[];

/* ============================================================================
 * Function bodies, in address order.
 * ========================================================================== */

/* FUN_00354828 @ 0x00354828
 * Ghidra: void FUN_00354828(void)
 * Empty protocol-witness / metadata no-op stub.
 * Confidence: medium
 * Notes: trivial `return;` body. */
void FUN_00354828(void) { return; }

/* FUN_00354834 @ 0x00354834
 * Ghidra: void FUN_00354834(void)
 * Empty protocol-witness / metadata no-op stub.
 * Confidence: medium */
void FUN_00354834(void) { return; }

/* FUN_00354840 @ 0x00354840
 * Ghidra: void FUN_00354840(void)
 * Empty protocol-witness / metadata no-op stub.
 * Confidence: medium */
void FUN_00354840(void) { return; }

/* FUN_0035484c @ 0x0035484c
 * Ghidra: void FUN_0035484c(void)
 * Empty protocol-witness / metadata no-op stub.
 * Confidence: medium */
void FUN_0035484c(void) { return; }

/* FUN_00354858 @ 0x00354858
 * Ghidra: void FUN_00354858(void)
 * Empty protocol-witness / metadata no-op stub.
 * Confidence: medium */
void FUN_00354858(void) { return; }

/* FUN_00354864 @ 0x00354864
 * Ghidra: void FUN_00354864(void)
 * Empty protocol-witness / metadata no-op stub.
 * Confidence: medium */
void FUN_00354864(void) { return; }

/* FUN_00354870 @ 0x00354870
 * Ghidra: void FUN_00354870(void)
 * Empty protocol-witness / metadata no-op stub.
 * Confidence: medium */
void FUN_00354870(void) { return; }

/* FUN_00354888 @ 0x00354888
 * Ghidra: void FUN_00354888(void)
 * Empty protocol-witness / metadata no-op stub.
 * Confidence: medium */
void FUN_00354888(void) { return; }

/* FUN_003548a0 @ 0x003548a0
 * Ghidra: void FUN_003548a0(void)
 * Empty protocol-witness / metadata no-op stub.
 * Confidence: medium */
void FUN_003548a0(void) { return; }

/* FUN_003548ac @ 0x003548ac
 * Ghidra: void FUN_003548ac(void)
 * Empty protocol-witness / metadata no-op stub.
 * Confidence: medium */
void FUN_003548ac(void) { return; }

/* FUN_003548b8 @ 0x003548b8
 * Ghidra: void FUN_003548b8(void)
 * Empty protocol-witness / metadata no-op stub.
 * Confidence: medium */
void FUN_003548b8(void) { return; }

/* FUN_003548c4 @ 0x003548c4
 * Ghidra: void FUN_003548c4(void)
 * Empty protocol-witness / metadata no-op stub.
 * Confidence: medium */
void FUN_003548c4(void) { return; }

/* FUN_003548d0 @ 0x003548d0
 * Ghidra: undefined1 [16] FUN_003548d0(void)
 * Returns a 16-byte word pair {hi = in_x5, lo = 0}: the register-passed value is
 * promoted into the upper word of a two-word Swift value.
 * Confidence: medium
 * Notes: modelled as `auVar1 {lo=x5,hi=0} << 64` == {lo=0, hi=x5}; x5 register-passed. */
reg16 FUN_003548d0(uint64_t value /* in_x5 */)
{
    return (reg16){ .lo = 0, .hi = value };
}

/* FUN_003548dc @ 0x003548dc
 * Ghidra: void FUN_003548dc(void)
 * Empty protocol-witness / metadata no-op stub.
 * Confidence: medium */
void FUN_003548dc(void) { return; }

/* FUN_003548e8 @ 0x003548e8
 * Ghidra: void FUN_003548e8(void)
 * Empty protocol-witness / metadata no-op stub.
 * Confidence: medium */
void FUN_003548e8(void) { return; }

/* FUN_003548f4 @ 0x003548f4
 * Ghidra: void FUN_003548f4(undefined8 *param_1)
 * Copies a 5-word struct from the register-passed source (x20) into the caller's
 * destination array, stashes the source pointer + first word at dst[5..6], and
 * stores the destination pointer into the register-passed out-slot (x19).
 * Confidence: medium
 * Notes: unaff_x19 (out), unaff_x20 (src) are register-passed. */
void FUN_003548f4(uint64_t *dst, uint64_t *src /* in_x20 */, uint64_t **out /* in_x19 */)
{
    *out = dst;
    dst[5] = (uint64_t)src;
    uint64_t w0 = src[0];
    dst[6] = w0;
    uint64_t w1 = src[1];
    uint64_t w4 = src[4];
    uint64_t w3 = src[3];
    uint64_t w2 = src[2];
    dst[0] = w0;
    dst[1] = w1;
    dst[3] = w3;
    dst[2] = w2;
    dst[4] = w4;
}

/* FUN_00354924 @ 0x00354924
 * Ghidra: void FUN_00354924(void)
 * Empty protocol-witness / metadata no-op stub.
 * Confidence: medium */
void FUN_00354924(void) { return; }

/* FUN_00354930 @ 0x00354930
 * Ghidra: void FUN_00354930(void)
 * Trampoline to the cL4 pointer-decode helper (sk_decode_ptr_10_e104).
 * Confidence: medium
 * Notes: calls FUN_0031e104 (est. sk_decode_ptr_10_e104). */
void FUN_00354930(void) { FUN_0031e104(); }

/* FUN_00354948 @ 0x00354948
 * Ghidra: void FUN_00354948(void)
 * Empty protocol-witness / metadata no-op stub.
 * Confidence: medium */
void FUN_00354948(void) { return; }

/* FUN_00354954 @ 0x00354954
 * Ghidra: void FUN_00354954(void)
 * Empty protocol-witness / metadata no-op stub.
 * Confidence: medium */
void FUN_00354954(void) { return; }

/* FUN_00354960 @ 0x00354960
 * Ghidra: uint FUN_00354960(uint param_1)
 * Replaces the low byte of `value` with the register-passed byte (w8); returns
 * the merged word. Used to patch a low-byte discriminator into a word.
 * Confidence: medium
 * Notes: in_w8 register-passed. */
uint32_t FUN_00354960(uint32_t value, uint8_t low_byte /* in_w8 */)
{
    return (value & 0xffffff00u) | (uint32_t)(low_byte & 0xffu);
}

/* FUN_00354968 @ 0x00354968
 * Ghidra: void FUN_00354968(void)
 * Trampoline to the object-service helper FUN_002b81b4.
 * Confidence: medium
 * Notes: calls FUN_002b81b4. */
void FUN_00354968(void) { FUN_002b81b4(); }

/* FUN_00354988 @ 0x00354988
 * Ghidra: void FUN_00354988(undefined8, undefined8, undefined8)
 * Inserts an object into a container: forwards (p1, p3, p3) to the object
 * allocation/insert helper with the set-flags bit (1) cleared from the last arg.
 * Confidence: high (verified against decompile, body matches exactly)
 * Notes: calls FUN_002a4b90(p1, p3, p3, 1). */
void FUN_00354988(uint64_t p1, uint64_t p2, uint64_t p3)
{
    (void)p2;
    FUN_002a4b90(p1, p3, p3, 1);
}

/* FUN_00354998 @ 0x00354998
 * Ghidra: bool FUN_00354998(void)
 * Returns the logical negation of the register-passed zero flag (ZR): true when
 * the prior comparison was not equal. A witness for a predicate wrapper.
 * Confidence: medium
 * Notes: in_ZR register-passed. */
bool FUN_00354998(bool zero_flag /* in_ZR */)
{
    return !zero_flag;
}

/* FUN_003549a8 @ 0x003549a8
 * Ghidra: void FUN_003549a8(void)
 * Trampoline to the Swift type-metadata field accessor (swift_type_metadata_field_20).
 * Confidence: medium
 * Notes: calls FUN_00310a14. */
void FUN_003549a8(void) { FUN_00310a14(); }

/* FUN_003549c0 @ 0x003549c0
 * Ghidra: void FUN_003549c0(void)
 * Trampoline to the boot/init helper FUN_00027754.
 * Confidence: medium
 * Notes: calls FUN_00027754. */
void FUN_003549c0(void) { FUN_00027754(); }

/* FUN_003549d8 @ 0x003549d8
 * Ghidra: void FUN_003549d8(void)
 * Empty protocol-witness / metadata no-op stub.
 * Confidence: medium */
void FUN_003549d8(void) { return; }

/* FUN_003549e4 @ 0x003549e4
 * Ghidra: void FUN_003549e4(void)
 * Empty protocol-witness / metadata no-op stub.
 * Confidence: medium */
void FUN_003549e4(void) { return; }

/* FUN_00354a00 @ 0x00354a00
 * Ghidra: void FUN_00354a00(void)
 * Empty protocol-witness / metadata no-op stub.
 * Confidence: medium */
void FUN_00354a00(void) { return; }

/* FUN_00354a0c @ 0x00354a0c
 * Ghidra: void FUN_00354a0c(void)
 * Empty protocol-witness / metadata no-op stub.
 * Confidence: medium */
void FUN_00354a0c(void) { return; }

/* FUN_00354a28 @ 0x00354a28
 * Ghidra: void FUN_00354a28(void)
 * Empty protocol-witness / metadata no-op stub.
 * Confidence: medium */
void FUN_00354a28(void) { return; }

/* FUN_00354a34 @ 0x00354a34
 * Ghidra: void FUN_00354a34(void)
 * Empty protocol-witness / metadata no-op stub.
 * Confidence: medium */
void FUN_00354a34(void) { return; }

/* FUN_00354a4c @ 0x00354a4c
 * Ghidra: void FUN_00354a4c(void)
 * Empty protocol-witness / metadata no-op stub.
 * Confidence: medium */
void FUN_00354a4c(void) { return; }

/* FUN_00354a58 @ 0x00354a58
 * Ghidra: void FUN_00354a58(void)
 * Lazy-global initializer: installs the resolved value at the global slot
 * 0x6560f0 using the lazy-metadata record DAT_004e7ed8.
 * Confidence: medium
 * Notes: calls FUN_00002534((ulong*)0x6560f0, &DAT_004e7ed8). */
void FUN_00354a58(void)
{
    FUN_00002534((ulong *)0x6560f0, (long *)&DAT_004e7ed8);
}

/* FUN_00354a6c @ 0x00354a6c
 * Ghidra: void FUN_00354a6c(void)
 * Empty protocol-witness / metadata no-op stub.
 * Confidence: medium */
void FUN_00354a6c(void) { return; }

/* FUN_00354a78 @ 0x00354a78
 * Ghidra: undefined8 FUN_00354a78(void)
 * Frame-local getter: returns the 8-byte slot at frame-0x98 (a captured local
 * in the caller's frame).
 * Confidence: medium
 * Notes: unaff_x29 (frame pointer) register-passed. */
uint64_t FUN_00354a78(uint8_t *frame /* in_x29 */)
{
    return *(uint64_t *)(frame - 0x98);
}

/* FUN_00354a84 @ 0x00354a84
 * Ghidra: void FUN_00354a84(void)
 * Empty protocol-witness / metadata no-op stub.
 * Confidence: medium */
void FUN_00354a84(void) { return; }

/* FUN_00354ab0 @ 0x00354ab0
 * Ghidra: void FUN_00354ab0(void)
 * Empty protocol-witness / metadata no-op stub.
 * Confidence: medium */
void FUN_00354ab0(void) { return; }

/* FUN_00354abc @ 0x00354abc
 * Ghidra: undefined8 FUN_00354abc(void)
 * Frame-local getter: returns the 8-byte slot at frame-0xb8 (a captured local
 * in the caller's frame).
 * Confidence: medium
 * Notes: unaff_x29 (frame pointer) register-passed. */
uint64_t FUN_00354abc(uint8_t *frame /* in_x29 */)
{
    return *(uint64_t *)(frame - 0xb8);
}

/* FUN_00354ac8 @ 0x00354ac8
 * Ghidra: void FUN_00354ac8(undefined8 param_1)
 * Frame-local setter: writes `value` into the slot at frame-0x148.
 * Confidence: medium
 * Notes: unaff_x29 (frame pointer) register-passed. */
void FUN_00354ac8(uint8_t *frame /* in_x29 */, uint64_t value)
{
    *(uint64_t *)(frame - 0x148) = value;
}

/* FUN_00354ad4 @ 0x00354ad4
 * Ghidra: void FUN_00354ad4(void)
 * Swift integer-range-check precondition trampoline: encodes the message
 * "because it is outside the representable range of type 'Int'" (0x2e bytes) via
 * the small-string encode helper, then fails fatally. Noreturn.
 * Confidence: high
 * Notes: string ref s_because_it_is_outside_the_repres_005cfbd0; calls
 *   FUN_001a89a8 (swift_small_string_encode). */
void FUN_00354ad4(void)
{
    (void)swift_small_string_encode((uint64_t)s_because_it_is_outside_the_repres_005cfbd0,
                                    0x2e, 1);
}

/* FUN_00354ae8 @ 0x00354ae8
 * Ghidra: void FUN_00354ae8(void)
 * Swift precondition-failure trampoline: encodes the 2-byte string literal at
 * DAT_005d3bb9 via the small-string encode helper, then fails fatally.
 * Confidence: medium
 * Notes: calls FUN_001a89a8(&DAT_005d3bb9, 2, 1). */
void FUN_00354ae8(void)
{
    (void)swift_small_string_encode((uint64_t)&DAT_005d3bb9, 2, 1);
}

/* FUN_00354afc @ 0x00354afc
 * Ghidra: void FUN_00354afc(void)
 * Empty protocol-witness / metadata no-op stub.
 * Confidence: medium */
void FUN_00354afc(void) { return; }

/* FUN_00354b08 @ 0x00354b08
 * Ghidra: void FUN_00354b08(void)
 * Empty protocol-witness / metadata no-op stub.
 * Confidence: medium */
void FUN_00354b08(void) { return; }

/* FUN_00354b14 @ 0x00354b14
 * Ghidra: void FUN_00354b14(void)
 * Empty protocol-witness / metadata no-op stub.
 * Confidence: medium */
void FUN_00354b14(void) { return; }

/* FUN_00354b20 @ 0x00354b20
 * Ghidra: undefined8 FUN_00354b20(void)
 * Returns 0 — a constant-zero identity/return shim (e.g. a nil / empty value).
 * Confidence: medium */
uint64_t FUN_00354b20(void) { return 0; }

/* FUN_00354b2c @ 0x00354b2c
 * Ghidra: void FUN_00354b2c(void)
 * Empty protocol-witness / metadata no-op stub.
 * Confidence: medium */
void FUN_00354b2c(void) { return; }

/* FUN_00354b38 @ 0x00354b38
 * Ghidra: void FUN_00354b38(void)
 * Empty protocol-witness / metadata no-op stub.
 * Confidence: medium */
void FUN_00354b38(void) { return; }

/* FUN_00354b44 @ 0x00354b44
 * Ghidra: void FUN_00354b44(undefined8 param_1)
 * Frame-local setter: writes `value` into the slot at frame-0x190 (-400).
 * Confidence: medium
 * Notes: unaff_x29 (frame pointer) register-passed. */
void FUN_00354b44(uint8_t *frame /* in_x29 */, uint64_t value)
{
    *(uint64_t *)(frame - 0x190) = value;
}

/* FUN_00354b50 @ 0x00354b50
 * Ghidra: undefined8 FUN_00354b50(long param_1)
 * Loads the 8-byte value at `base - 0x100` and returns it (a field accessor
 * through a self/context pointer with a negative offset).
 * Confidence: medium
 * Notes: offset -0x100 from the incoming pointer. */
uint64_t FUN_00354b50(uint8_t *base)
{
    return *(uint64_t *)(base - 0x100);
}

/* FUN_00354b5c @ 0x00354b5c
 * Ghidra: void FUN_00354b5c(void)
 * Empty protocol-witness / metadata no-op stub.
 * Confidence: medium */
void FUN_00354b5c(void) { return; }

/* FUN_00354b68 @ 0x00354b68
 * Ghidra: void FUN_00354b68(void)
 * Empty protocol-witness / metadata no-op stub.
 * Confidence: medium */
void FUN_00354b68(void) { return; }

/* FUN_00354b74 @ 0x00354b74
 * Ghidra: void FUN_00354b74(void)
 * Empty protocol-witness / metadata no-op stub.
 * Confidence: medium */
void FUN_00354b74(void) { return; }

/* FUN_00354b80 @ 0x00354b80
 * Ghidra: void FUN_00354b80(void)
 * Empty protocol-witness / metadata no-op stub.
 * Confidence: medium */
void FUN_00354b80(void) { return; }

/* FUN_00354b8c @ 0x00354b8c
 * Ghidra: void FUN_00354b8c(void)
 * Empty protocol-witness / metadata no-op stub.
 * Confidence: medium */
void FUN_00354b8c(void) { return; }

/* FUN_00354b98 @ 0x00354b98
 * Ghidra: void FUN_00354b98(void)
 * Empty protocol-witness / metadata no-op stub.
 * Confidence: medium */
void FUN_00354b98(void) { return; }

/* FUN_00354ba4 @ 0x00354ba4
 * Ghidra: void FUN_00354ba4(void)
 * Empty protocol-witness / metadata no-op stub.
 * Confidence: medium */
void FUN_00354ba4(void) { return; }

/* FUN_00354bb0 @ 0x00354bb0
 * Ghidra: void FUN_00354bb0(void)
 * Empty protocol-witness / metadata no-op stub.
 * Confidence: medium */
void FUN_00354bb0(void) { return; }

/* FUN_00354bbc @ 0x00354bbc
 * Ghidra: void FUN_00354bbc(void)
 * Empty protocol-witness / metadata no-op stub.
 * Confidence: medium */
void FUN_00354bbc(void) { return; }

/* FUN_00354bc8 @ 0x00354bc8
 * Ghidra: undefined1 [16] FUN_00354bc8(undefined8 param_1)
 * Returns a 16-byte word pair {lo = 1, hi = value}: a tagged/option some-value
 * wrapper storing the payload in the upper word with a 1 discriminator in the
 * lower word.
 * Confidence: medium
 * Notes: 16-byte Swift value return. */
reg16 FUN_00354bc8(uint64_t value)
{
    return (reg16){ .lo = 1, .hi = value };
}

/* FUN_00354bd4 @ 0x00354bd4
 * Ghidra: void FUN_00354bd4(void)
 * Empty protocol-witness / metadata no-op stub.
 * Confidence: medium */
void FUN_00354bd4(void) { return; }

/* FUN_00354be0 @ 0x00354be0
 * Ghidra: void FUN_00354be0(void)
 * Empty protocol-witness / metadata no-op stub.
 * Confidence: medium */
void FUN_00354be0(void) { return; }

/* FUN_00354bec @ 0x00354bec
 * Ghidra: void FUN_00354bec(void)
 * Empty protocol-witness / metadata no-op stub.
 * Confidence: medium */
void FUN_00354bec(void) { return; }

/* FUN_00354bf8 @ 0x00354bf8
 * Ghidra: void FUN_00354bf8(void)
 * Lazy-global initializer: installs the resolved value at the global slot
 * 0x656180 using the lazy-metadata record DAT_004e7fd8.
 * Confidence: medium
 * Notes: calls FUN_00002534((ulong*)0x656180, &DAT_004e7fd8). */
void FUN_00354bf8(void)
{
    FUN_00002534((ulong *)0x656180, (long *)&DAT_004e7fd8);
}

/* FUN_00354c38 @ 0x00354c38
 * Ghidra: long FUN_00354c38(void)
 * Returns a pointer into the caller's frame at frame-0x78 (address of a local
 * buffer). Used as a metadata/context base accessor.
 * Confidence: medium
 * Notes: unaff_x29 (frame pointer) register-passed. */
uint8_t *FUN_00354c38(uint8_t *frame /* in_x29 */)
{
    return frame - 0x78;
}

/* FUN_00354c44 @ 0x00354c44
 * Ghidra: void FUN_00354c44(void)
 * Lazy-global initializer: installs the resolved value at the global slot
 * 0x64f3c0 using the lazy-metadata record DAT_004e7fc0.
 * Confidence: medium
 * Notes: calls FUN_00002534((ulong*)0x64f3c0, &DAT_004e7fc0). */
void FUN_00354c44(void)
{
    FUN_00002534((ulong *)0x64f3c0, (long *)&DAT_004e7fc0);
}

/* FUN_00354c58 @ 0x00354c58
 * Ghidra: long FUN_00354c58(long param_1)
 * Identity shim: the decompiler shows a redundant `if (value == 0) value = 0;`
 * branch; the effective behavior is to return the input unchanged.
 * Confidence: medium
 * Notes: decompiler artifacts of a trivial identity function. */
long FUN_00354c58(long value)
{
    return value;
}

/* FUN_00354c64 @ 0x00354c64
 * Ghidra: void FUN_00354c64(void)
 * Empty protocol-witness / metadata no-op stub.
 * Confidence: medium */
void FUN_00354c64(void) { return; }

/* FUN_00354c70 @ 0x00354c70
 * Ghidra: void FUN_00354c70(void)
 * Empty protocol-witness / metadata no-op stub.
 * Confidence: medium */
void FUN_00354c70(void) { return; }

/* FUN_00354c9c @ 0x00354c9c
 * Ghidra: void FUN_00354c9c(void)
 * Empty protocol-witness / metadata no-op stub.
 * Confidence: medium */
void FUN_00354c9c(void) { return; }

/* FUN_00354ca8 @ 0x00354ca8
 * Ghidra: void FUN_00354ca8(void)
 * Empty protocol-witness / metadata no-op stub.
 * Confidence: medium */
void FUN_00354ca8(void) { return; }

/* FUN_00354cb4 @ 0x00354cb4
 * Ghidra: undefined8 FUN_00354cb4(void)
 * Frame-local getter: returns the 8-byte slot at frame-0x58.
 * Confidence: medium
 * Notes: unaff_x29 (frame pointer) register-passed. */
uint64_t FUN_00354cb4(uint8_t *frame /* in_x29 */)
{
    return *(uint64_t *)(frame - 0x58);
}

/* FUN_00354cc0 @ 0x00354cc0
 * Ghidra: void FUN_00354cc0(void)
 * Empty protocol-witness / metadata no-op stub.
 * Confidence: medium */
void FUN_00354cc0(void) { return; }

/* FUN_00354ccc @ 0x00354ccc
 * Ghidra: void FUN_00354ccc(void)
 * Empty protocol-witness / metadata no-op stub.
 * Confidence: medium */
void FUN_00354ccc(void) { return; }

/* FUN_00354cd8 @ 0x00354cd8
 * Ghidra: void FUN_00354cd8(void)
 * Empty protocol-witness / metadata no-op stub.
 * Confidence: medium */
void FUN_00354cd8(void) { return; }

/* FUN_00354ce4 @ 0x00354ce4
 * Ghidra: void FUN_00354ce4(void)
 * Empty protocol-witness / metadata no-op stub.
 * Confidence: medium */
void FUN_00354ce4(void) { return; }

/* FUN_00354cf0 @ 0x00354cf0
 * Ghidra: void FUN_00354cf0(void)
 * Frame-local setter: writes the sentinel -1 (0xffffffffffffffff) into the slot
 * at frame-0x58 (resets a local "no value" index).
 * Confidence: medium
 * Notes: unaff_x29 (frame pointer) register-passed. */
void FUN_00354cf0(uint8_t *frame /* in_x29 */)
{
    *(uint64_t *)(frame - 0x58) = 0xffffffffffffffffULL;
}

/* FUN_00354cfc @ 0x00354cfc
 * Ghidra: void FUN_00354cfc(void)
 * Empty protocol-witness / metadata no-op stub.
 * Confidence: medium */
void FUN_00354cfc(void) { return; }

/* FUN_00354d08 @ 0x00354d08
 * Ghidra: undefined8 FUN_00354d08(void)
 * Frame-local getter: returns the 8-byte slot at frame-0x78.
 * Confidence: medium
 * Notes: unaff_x29 (frame pointer) register-passed. */
uint64_t FUN_00354d08(uint8_t *frame /* in_x29 */)
{
    return *(uint64_t *)(frame - 0x78);
}

/* FUN_00354d14 @ 0x00354d14
 * Ghidra: void FUN_00354d14(void)
 * Empty protocol-witness / metadata no-op stub.
 * Confidence: medium */
void FUN_00354d14(void) { return; }

/* FUN_00354d20 @ 0x00354d20
 * Ghidra: void FUN_00354d20(void)
 * Empty protocol-witness / metadata no-op stub.
 * Confidence: medium */
void FUN_00354d20(void) { return; }

/* FUN_00354d2c @ 0x00354d2c
 * Ghidra: void FUN_00354d2c(void)
 * Empty protocol-witness / metadata no-op stub.
 * Confidence: medium */
void FUN_00354d2c(void) { return; }

/* FUN_00354d38 @ 0x00354d38
 * Ghidra: void FUN_00354d38(void)
 * Empty protocol-witness / metadata no-op stub.
 * Confidence: medium */
void FUN_00354d38(void) { return; }

/* FUN_00354d44 @ 0x00354d44
 * Ghidra: void FUN_00354d44(void)
 * Empty protocol-witness / metadata no-op stub.
 * Confidence: medium */
void FUN_00354d44(void) { return; }

/* FUN_00354d50 @ 0x00354d50
 * Ghidra: void FUN_00354d50(void)
 * Empty protocol-witness / metadata no-op stub.
 * Confidence: medium */
void FUN_00354d50(void) { return; }

/* FUN_00354d5c @ 0x00354d5c
 * Ghidra: void FUN_00354d5c(void)
 * Empty protocol-witness / metadata no-op stub.
 * Confidence: medium */
void FUN_00354d5c(void) { return; }

/* FUN_00354d68 @ 0x00354d68
 * Ghidra: void FUN_00354d68(void)
 * Empty protocol-witness / metadata no-op stub.
 * Confidence: medium */
void FUN_00354d68(void) { return; }

/* FUN_00354d74 @ 0x00354d74
 * Ghidra: void FUN_00354d74(void)
 * Empty protocol-witness / metadata no-op stub.
 * Confidence: medium */
void FUN_00354d74(void) { return; }

/* FUN_00354d80 @ 0x00354d80
 * Ghidra: void FUN_00354d80(void)
 * Lazy-global initializer: installs the resolved value at the global slot
 * 0x656248 using the lazy-metadata record DAT_004e80a0.
 * Confidence: medium
 * Notes: calls FUN_00002534((ulong*)0x656248, &DAT_004e80a0). */
void FUN_00354d80(void)
{
    FUN_00002534((ulong *)0x656248, (long *)&DAT_004e80a0);
}

/* FUN_00354d94 @ 0x00354d94
 * Ghidra: void FUN_00354d94(void)
 * Empty protocol-witness / metadata no-op stub.
 * Confidence: medium */
void FUN_00354d94(void) { return; }

/* FUN_00354da0 @ 0x00354da0
 * Ghidra: void FUN_00354da0(void)
 * Trampoline to the object-service end-of-slice helper (sk_obj_end_0xc).
 * Confidence: medium
 * Notes: calls FUN_0031b900. */
void FUN_00354da0(void) { FUN_0031b900(); }

/* FUN_00354db8 @ 0x00354db8
 * Ghidra: undefined8 FUN_00354db8(void)
 * Returns the register-passed third argument (x3) unchanged — a passthrough
 * identity shim for a value carried in x3.
 * Confidence: medium
 * Notes: in_x3 register-passed. */
uint64_t FUN_00354db8(uint64_t value /* in_x3 */)
{
    return value;
}

/* FUN_00354dc4 @ 0x00354dc4
 * Ghidra: void FUN_00354dc4(void)
 * Empty protocol-witness / metadata no-op stub.
 * Confidence: medium */
void FUN_00354dc4(void) { return; }

/* FUN_00354dd0 @ 0x00354dd0
 * Ghidra: void FUN_00354dd0(void)
 * Empty protocol-witness / metadata no-op stub.
 * Confidence: medium */
void FUN_00354dd0(void) { return; }

/* FUN_00354ddc @ 0x00354ddc
 * Ghidra: void FUN_00354ddc(void)
 * Empty protocol-witness / metadata no-op stub.
 * Confidence: medium */
void FUN_00354ddc(void) { return; }

/* FUN_00354de8 @ 0x00354de8
 * Ghidra: void FUN_00354de8(void)
 * Empty protocol-witness / metadata no-op stub.
 * Confidence: medium */
void FUN_00354de8(void) { return; }

/* FUN_00354df4 @ 0x00354df4
 * Ghidra: void FUN_00354df4(void)
 * Empty protocol-witness / metadata no-op stub.
 * Confidence: medium */
void FUN_00354df4(void) { return; }

/* FUN_00354e00 @ 0x00354e00
 * Ghidra: undefined8 FUN_00354e00(undefined8, undefined8, undefined8)
 * Returns the third argument unchanged — an identity/passthrough shim.
 * Confidence: medium */
uint64_t FUN_00354e00(uint64_t p1, uint64_t p2, uint64_t p3)
{
    (void)p1;
    (void)p2;
    return p3;
}

/* FUN_00354e0c @ 0x00354e0c
 * Ghidra: void FUN_00354e0c(void)
 * Empty protocol-witness / metadata no-op stub.
 * Confidence: medium */
void FUN_00354e0c(void) { return; }

/* FUN_00354e18 @ 0x00354e18
 * Ghidra: void FUN_00354e18(void)
 * Object-service forward-resolve on the global slot DAT_004ea794.
 * Confidence: medium
 * Notes: calls FUN_00376820 (sk_obj_resolve_forward). */
void FUN_00354e18(void)
{
    sk_obj_resolve_forward((uint64_t)&DAT_004ea794);
}

/* FUN_00354e34 @ 0x00354e34
 * Ghidra: void FUN_00354e34(void)
 * Scheduler queue iteration witness: invokes the array-reserve callback
 * FUN_001a0908 per queue element.
 * Confidence: medium
 * Notes: calls FUN_001a157c (sk_sched_queue_foreach) with callback FUN_001a0908. */
void FUN_00354e34(void)
{
    sk_sched_queue_foreach(FUN_001a0908);
}

/* FUN_00354e50 @ 0x00354e50
 * Ghidra: void FUN_00354e50(void)
 * Object-service forward-resolve on the global slot DAT_004eac00.
 * Confidence: medium
 * Notes: calls FUN_00376820 (sk_obj_resolve_forward). */
void FUN_00354e50(void)
{
    sk_obj_resolve_forward((uint64_t)&DAT_004eac00);
}

/* FUN_00354e6c @ 0x00354e6c
 * Ghidra: void FUN_00354e6c(void)
 * Object-service forward-resolve on the global slot DAT_004f0e1c.
 * Confidence: medium
 * Notes: calls FUN_00376820 (sk_obj_resolve_forward). */
void FUN_00354e6c(void)
{
    sk_obj_resolve_forward((uint64_t)&DAT_004f0e1c);
}

/* FUN_00354e88 @ 0x00354e88
 * Ghidra: void FUN_00354e88(void)
 * Object-service forward-resolve on the global slot DAT_004ec318.
 * Confidence: medium
 * Notes: calls FUN_00376820 (sk_obj_resolve_forward). */
void FUN_00354e88(void)
{
    sk_obj_resolve_forward((uint64_t)&DAT_004ec318);
}

/* FUN_00354ea4 @ 0x00354ea4
 * Ghidra: void FUN_00354ea4(void)
 * Object-service forward-resolve on the global slot DAT_004e9d3c.
 * Confidence: medium
 * Notes: calls FUN_00376820 (sk_obj_resolve_forward). */
void FUN_00354ea4(void)
{
    sk_obj_resolve_forward((uint64_t)&DAT_004e9d3c);
}

/* FUN_00354ec0 @ 0x00354ec0
 * Ghidra: void FUN_00354ec0(void)
 * Object-service forward-resolve on the global slot DAT_004eddb0.
 * Confidence: medium
 * Notes: calls FUN_00376820 (sk_obj_resolve_forward). */
void FUN_00354ec0(void)
{
    sk_obj_resolve_forward((uint64_t)&DAT_004eddb0);
}

/* FUN_00354edc @ 0x00354edc
 * Ghidra: void FUN_00354edc(void)
 * Scheduler queue iteration witness: invokes the array-reserve callback
 * FUN_001a0be4 per queue element.
 * Confidence: medium
 * Notes: calls FUN_001a157c (sk_sched_queue_foreach) with callback FUN_001a0be4. */
void FUN_00354edc(void)
{
    sk_sched_queue_foreach(FUN_001a0be4);
}

/* FUN_00354ef8 @ 0x00354ef8
 * Ghidra: void FUN_00354ef8(void)
 * Empty protocol-witness / metadata no-op stub.
 * Confidence: medium */
void FUN_00354ef8(void) { return; }

/* FUN_00354f10 @ 0x00354f10
 * Ghidra: void FUN_00354f10(void)
 * Empty protocol-witness / metadata no-op stub.
 * Confidence: medium */
void FUN_00354f10(void) { return; }

/* FUN_00354f1c @ 0x00354f1c
 * Ghidra: void FUN_00354f1c(void)
 * Empty protocol-witness / metadata no-op stub.
 * Confidence: medium */
void FUN_00354f1c(void) { return; }

/* FUN_00354f28 @ 0x00354f28
 * Ghidra: void FUN_00354f28(void)
 * Empty protocol-witness / metadata no-op stub.
 * Confidence: medium */
void FUN_00354f28(void) { return; }

/* FUN_00354f34 @ 0x00354f34
 * Ghidra: void FUN_00354f34(void)
 * Trampoline to the extent descriptor helper (exclave_extent_d).
 * Confidence: medium
 * Notes: calls FUN_000a6894. */
void FUN_00354f34(void) { FUN_000a6894(); }

/* FUN_00354f4c @ 0x00354f4c
 * Ghidra: void FUN_00354f4c(void)
 * Trampoline to the Swift type-metadata field accessor
 * (swift_type_metadata_field_18b).
 * Confidence: medium
 * Notes: calls FUN_00310ca4. */
void FUN_00354f4c(void) { FUN_00310ca4(); }

/* FUN_00354f64 @ 0x00354f64
 * Ghidra: void FUN_00354f64(void)
 * Empty protocol-witness / metadata no-op stub.
 * Confidence: medium */
void FUN_00354f64(void) { return; }

/* FUN_00354f70 @ 0x00354f70
 * Ghidra: void FUN_00354f70(void)
 * Empty protocol-witness / metadata no-op stub.
 * Confidence: medium */
void FUN_00354f70(void) { return; }

/* FUN_00354f80 @ 0x00354f80
 * Ghidra: void FUN_00354f80(void)
 * Empty protocol-witness / metadata no-op stub.
 * Confidence: medium */
void FUN_00354f80(void) { return; }

/* FUN_00354f8c @ 0x00354f8c
 * Ghidra: void FUN_00354f8c(void)
 * Empty protocol-witness / metadata no-op stub.
 * Confidence: medium */
void FUN_00354f8c(void) { return; }

/* FUN_00354f98 @ 0x00354f98
 * Ghidra: void FUN_00354f98(void)
 * Copies a (word + byte) tail of a struct from the register-passed source (x19)
 * to the register-passed destination (x20): dst[0x20]=src[0x20] and
 * dst[0x28]=src[0x28] (a short memcpy of the trailing 9 bytes of a struct).
 * Confidence: medium
 * Notes: unaff_x19 (src), unaff_x20 (dst) register-passed. */
void FUN_00354f98(uint8_t *dst /* in_x20 */, uint8_t *src /* in_x19 */)
{
    *(uint64_t *)(dst + 0x20) = *(uint64_t *)(src + 0x20);
    *(uint8_t *)(dst + 0x28)  = *(uint8_t *)(src + 0x28);
}

/* FUN_00354fac @ 0x00354fac
 * Ghidra: void FUN_00354fac(void)
 * Empty protocol-witness / metadata no-op stub.
 * Confidence: medium */
void FUN_00354fac(void) { return; }

/* FUN_00354fc0 @ 0x00354fc0
 * Ghidra: void FUN_00354fc0(void)
 * Empty protocol-witness / metadata no-op stub.
 * Confidence: medium */
void FUN_00354fc0(void) { return; }
