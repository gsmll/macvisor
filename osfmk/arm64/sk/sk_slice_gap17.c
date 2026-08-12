/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel,
 * arm64e, image base 0) — the cL4 microkernel (GL1), "cL4 (679.100.61)".
 * Ground truth: Ghidra FUN_ names + addresses in program cl4_kernel.raw.
 * Slice GAP17: 0x00355868-0x00357bec (120 functions). All names are estimates
 * unless string/header-matched. Uses seL4/cL4 vocabulary (TCB, cap, CNode, IPC,
 * notification, endpoint, vspace, sched, object, slot).
 *
 * This region is a dense table of tiny Swift-runtime / Swift standard-library
 * stubs: trivial protocol-witness no-ops, register-passed identity/return-0
 * shims, spill/forward thunks that read or write the caller's frame, Swift
 * opaque-metadata descriptor getters (16-byte {address, discriminator} pairs),
 * a byte-swap / endianness primitive, and a few noreturn fatal-error /
 * precondition-failure trampolines.
 *
 * Calling-convention note (as in the sibling slices): the decompiler shows most
 * of these as `void FUN(void)` because arguments are passed in registers and not
 * modelled as formal parameters. Where a body reads an `unaff_xNN`/`in_xNN`
 * register or the caller's frame pointer (`unaff_x29`), we model that register
 * as an explicit parameter (named for its purpose) with a comment noting the
 * source register, so the body compiles while staying faithful to the observed
 * register usage. The Ghidra names stay in comments only.
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

/* FUN_0031a29c — Swift runtime helper; invoked by a protocol-witness thunk. */
extern void swift_runtime_call_31a29c(void);

/* FUN_0024a428 — Swift contiguous-array/range update helper; three args. */
extern void swift_range_update_24a428(uint64_t dst, uint64_t src, uint64_t end);

/* FUN_001679fc — Swift runtime helper; invoked by a protocol-witness thunk. */
extern void swift_runtime_call_1679fc(void);

/* FUN_0031d6d8 — Swift runtime helper; invoked by a protocol-witness thunk. */
extern void swift_runtime_call_31d6d8(void);

/* FUN_001f99f4 — Swift tuple/selector helper; three of the five args used. */
extern void swift_tuple_call_1f99f4(uint64_t a, uint64_t b, uint64_t c);

/* FUN_00258c60 — Swift runtime helper; invoked by a protocol-witness thunk. */
extern void swift_runtime_call_258c60(void);

/* FUN_001ef804 — Swift runtime helper; invoked by a protocol-witness thunk. */
extern void swift_runtime_call_1ef804(void);

/* FUN_003722e4 — shared out-of-range helper (also referenced by slice GAP07). */
extern void FUN_003722e4(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

/* FUN_00310d68 — diagnostic/validation helper; takes a tag constant + arg. */
extern void swift_tag_diag_310d68(uint64_t tag, uint64_t arg);

/* FUN_000026e8 — object method-table / object dispatch helper (boot region). */
extern void swift_obj_dispatch_26e8(uint64_t obj);

/* FUN_001bcc18 — Swift runtime helper; two args, order swapped at the call. */
extern void swift_runtime_swap_1bcc18(uint64_t a, uint64_t b);

/* FUN_00310a74 — Swift runtime helper; invoked by a protocol-witness thunk. */
extern void swift_runtime_call_310a74(void);

/* FUN_0001df60 — Swift runtime helper; invoked after 310a74. */
extern void swift_runtime_call_1df60(void);

/* FUN_001afa84 — Swift string fatal-precondition path (noreturn). Traps with
 * the fatal text. */
extern void swift_string_fatal_precondition(void) __attribute__((noreturn));

/* Globals referenced (string/data literals; addresses are Ghidra DAT_/s_ refs). */
extern uint64_t DAT_004e7d40;  /* data @ 0x004e7d40 */
extern uint64_t DAT_004e7d48;  /* data @ 0x004e7d48 */

/* ============================================================================
 * Function bodies, in address order.
 * ========================================================================== */

/* FUN_00355868 @ 0x00355868
 * Ghidra: ulong FUN_00355868(void)
 * Returns `b & ~a` from the two register-passed words — a mask/clear-bit helper
 * (low bits of x24 masked by the complement of x23).
 * Confidence: medium
 * Notes: args register-passed (unaff_x23, unaff_x24). */
ulong FUN_00355868(ulong a /* x23 */, ulong b /* x24 */)
{
    return b & (a ^ 0xffffffffffffffffull);
}

/* FUN_00355878 @ 0x00355878  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00355878(void) { return; }

/* FUN_00355884 @ 0x00355884  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00355884(void) { return; }

/* FUN_00355890 @ 0x00355890  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00355890(void) { return; }

/* FUN_003558a8 @ 0x003558a8  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_003558a8(void) { return; }

/* FUN_003558b8 @ 0x003558b8  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_003558b8(void) { return; }

/* FUN_003558c4 @ 0x003558c4  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_003558c4(void) { return; }

/* FUN_003558d8 @ 0x003558d8
 * Ghidra: void FUN_003558d8(undefined8 param_1)
 * Spills the register-passed word into the caller's frame at offset -200
 * (i.e. a local-slot store before a subsequent reload/forward).
 * Confidence: medium
 * Notes: frame base is unaff_x29. */
void FUN_003558d8(uint64_t val, uint64_t *frame /* x29 */)
{
    *(uint64_t *)((char *)frame - 200) = val;
}

/* FUN_003558ec @ 0x003558ec  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_003558ec(void) { return; }

/* FUN_003558fc @ 0x003558fc  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_003558fc(void) { return; }

/* FUN_00355908 @ 0x00355908  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00355908(void) { return; }

/* FUN_00357440 @ 0x00357440  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00357440(void) { return; }

/* FUN_0035745c @ 0x0035745c  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_0035745c(void) { return; }

/* FUN_00357468 @ 0x00357468
 * Ghidra: void FUN_00357468(void)
 * Stores a register-passed word into the object at +0x10 and a decremented
 * byte into the indexed element (base + index + 0x20). A Swift Array
 * element-update helper writing an inlined element and its count/length byte.
 * Confidence: medium
 * Notes: register-passed (unaff_x19 base, unaff_x20 value, unaff_w23 byte,
 *   unaff_x24 index). */
void FUN_00357468(uint64_t *obj /* x19 */, uint64_t val /* x20 */,
                  char byte /* w23 */, long idx /* x24 */)
{
    obj[2] = val;                                   /* +0x10 */
    *(char *)((char *)obj + idx + 0x20) = byte - 1;
}

/* FUN_0035748c @ 0x0035748c  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_0035748c(void) { return; }

/* FUN_00357498 @ 0x00357498
 * Ghidra: undefined1 [16] FUN_00357498(void)
 * Builds a 16-byte descriptor: low word = base (x26) + the 32-bit field at
 * (x21)+0x50; high word = the caller's frame word at -0xb8. A Swift descriptor
 * getter that recomputes a derived address.
 * Confidence: medium
 * Notes: register-passed (unaff_x21, unaff_x26); frame unaff_x29. */
reg16 FUN_00357498(long base /* x26 */, long obj /* x21 */, uint64_t *frame /* x29 */)
{
    reg16 out;
    out.lo = (uint64_t)base + *(int *)(obj + 0x50);
    out.hi = *(uint64_t *)((char *)frame - 0xb8);
    return out;
}

/* FUN_003574b4 @ 0x003574b4
 * Ghidra: void FUN_003574b4(long param_1,long param_2)
 * Copies three byte fields from src (+1, +2, +8) to dst. A narrow struct
 * field-copy helper.
 * Confidence: medium */
void FUN_003574b4(char *dst, char *src)
{
    dst[1] = src[1];
    dst[2] = src[2];
    dst[8] = src[8];
}

/* FUN_003574d0 @ 0x003574d0  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_003574d0(void) { return; }

/* FUN_003574ec @ 0x003574ec  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_003574ec(void) { return; }

/* FUN_00357508 @ 0x00357508
 * Ghidra: undefined8 FUN_00357508(void)
 * Returns the caller's frame word at -0x68 — a spill reload / local forward.
 * Confidence: medium
 * Notes: frame base is unaff_x29. */
uint64_t FUN_00357508(uint64_t *frame /* x29 */)
{
    return *(uint64_t *)((char *)frame - 0x68);
}

/* FUN_00357514 @ 0x00357514
 * Ghidra: undefined1 [16] FUN_00357514(void)
 * Builds a 16-byte descriptor whose two words are pointers into the caller's
 * frame (0x140 and 0x170) — a Swift inout/indirect-argument descriptor pair.
 * Confidence: medium
 * Notes: frame base is unaff_x29. */
reg16 FUN_00357514(uint64_t *frame /* x29 */)
{
    reg16 out;
    out.lo = (uint64_t)((char *)frame - 0x170);
    out.hi = (uint64_t)((char *)frame - 0x140);
    return out;
}

/* FUN_00357540 @ 0x00357540  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00357540(void) { return; }

/* FUN_0035754c @ 0x0035754c  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_0035754c(void) { return; }

/* FUN_00357558 @ 0x00357558  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00357558(void) { return; }

/* FUN_00357564 @ 0x00357564
 * Ghidra: void FUN_00357564(void)
 * Forwards to the Swift runtime helper at 0x31a29c with no extra arguments.
 * Confidence: medium */
void FUN_00357564(void) { swift_runtime_call_31a29c(); }

/* FUN_00357584 @ 0x00357584
 * Ghidra: void FUN_00357584(long param_1)
 * Forwards a range update to 0x24a428: destination is the caller's frame slot
 * at -0xa0, source and end are param_1 and param_1 + (index in x26). A Swift
 * Array slice/replace helper.
 * Confidence: medium
 * Notes: register-passed (unaff_x26); frame unaff_x29. */
void FUN_00357584(uint64_t src /* x0 */, long idx /* x26 */, uint64_t *frame /* x29 */)
{
    swift_range_update_24a428((uint64_t)((char *)frame - 0xa0), src, src + (uint64_t)idx);
}

/* FUN_003575a4 @ 0x003575a4  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_003575a4(void) { return; }

/* FUN_003575b0 @ 0x003575b0
 * Ghidra: undefined * FUN_003575b0(void)
 * Returns the address of the global data object at 0x4e7d48 — a Swift opaque
 * metadata descriptor getter.
 * Confidence: medium
 * Notes: DAT_004e7d48. */
uint64_t *FUN_003575b0(void)
{
    return &DAT_004e7d48;
}

/* FUN_003575bc @ 0x003575bc
 * Ghidra: void FUN_003575bc(void)
 * Forwards to the Swift runtime helper at 0x1679fc with no extra arguments.
 * Confidence: medium */
void FUN_003575bc(void) { swift_runtime_call_1679fc(); }

/* FUN_003575d4 @ 0x003575d4
 * Ghidra: void FUN_003575d4(void)
 * Copies the word at (src)+0x28 into (dst)+0x28. A single-field struct copy.
 * Confidence: medium
 * Notes: register-passed (unaff_x19 dst, unaff_x20 src). */
void FUN_003575d4(uint64_t *dst /* x19 */, uint64_t *src /* x20 */)
{
    dst[5] = src[5];                                /* +0x28 */
}

/* FUN_003575f0 @ 0x003575f0
 * Ghidra: void FUN_003575f0(void)
 * Stores two spilled caller-frame values (a 32-bit word at frame -0x48 and a
 * byte at frame -0x4c) into the object: word at +0, byte at +4. A small struct
 * (init-from-locals) writer.
 * Confidence: medium
 * Notes: register-passed (unaff_x19 obj); frame-slot reads. */
void FUN_003575f0(uint32_t *obj /* x19 */, uint64_t *frame /* x29 */)
{
    obj[0] = *(uint32_t *)((char *)frame - 0x48);
    *(char *)((char *)obj + 4) = *(char *)((char *)frame - 0x4c);
}

/* FUN_0035760c @ 0x0035760c  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_0035760c(void) { return; }

/* FUN_00357628 @ 0x00357628
 * Ghidra: long FUN_00357628(void)
 * Returns `(x3 & 0x0fffffffffffffff) + 0x20` — a rounded-up buffer length /
 * capacity computation (mask to 60-bit object size, add header).
 * Confidence: medium
 * Notes: register-passed (in_x3). */
long FUN_00357628(ulong len /* x3 */)
{
    return (long)((len & 0x0fffffffffffffff) + 0x20);
}

/* FUN_00357634 @ 0x00357634
 * Ghidra: undefined8 FUN_00357634(void)
 * Returns the caller's frame word at -0x290 — a spill reload / local forward.
 * Confidence: medium
 * Notes: frame base is unaff_x29. */
uint64_t FUN_00357634(uint64_t *frame /* x29 */)
{
    return *(uint64_t *)((char *)frame - 0x290);
}

/* FUN_00357640 @ 0x00357640  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00357640(void) { return; }

/* FUN_0035764c @ 0x0035764c
 * Ghidra: void FUN_0035764c(void)
 * Forwards to the Swift runtime helper at 0x31d6d8 with no extra arguments.
 * Confidence: medium */
void FUN_0035764c(void) { swift_runtime_call_31d6d8(); }

/* FUN_00357664 @ 0x00357664
 * Ghidra: undefined8 FUN_00357664(void)
 * Returns the caller's frame word at -0x68 — a spill reload / local forward.
 * Confidence: medium
 * Notes: frame base is unaff_x29. */
uint64_t FUN_00357664(uint64_t *frame /* x29 */)
{
    return *(uint64_t *)((char *)frame - 0x68);
}

/* FUN_00357670 @ 0x00357670
 * Ghidra: void FUN_00357670(undefined8 param_1,undefined4 param_2)
 * Stores a word at obj+0 and a 32-bit value at obj+8. A small struct field
 * writer.
 * Confidence: medium
 * Notes: register-passed (unaff_x19 obj). */
void FUN_00357670(uint64_t *obj /* x19 */, uint64_t val, uint32_t tag)
{
    obj[0] = val;
    *(uint32_t *)((char *)obj + 8) = tag;
}

/* FUN_0035767c @ 0x0035767c  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_0035767c(void) { return; }

/* FUN_00357688 @ 0x00357688  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00357688(void) { return; }

/* FUN_00357694 @ 0x00357694
 * Ghidra: void FUN_00357694(undefined8,undefined8,undefined8,undefined8)
 * Stores four words at obj+0..+0x18. A 32-byte struct initializer.
 * Confidence: medium
 * Notes: register-passed (unaff_x24 obj). */
void FUN_00357694(uint64_t *obj /* x24 */, uint64_t w0, uint64_t w1,
                  uint64_t w2, uint64_t w3)
{
    obj[0] = w0;
    obj[1] = w1;
    obj[2] = w2;
    obj[3] = w3;
}

/* FUN_003576a0 @ 0x003576a0
 * Ghidra: void FUN_003576a0(void)
 * Same shape as FUN_003575f0: stores the 32-bit word at frame -0x48 into obj+0
 * and the byte at frame -0x4c into obj+4. A small struct (init-from-locals)
 * writer.
 * Confidence: medium
 * Notes: register-passed (unaff_x19 obj); frame-slot reads. */
void FUN_003576a0(uint32_t *obj /* x19 */, uint64_t *frame /* x29 */)
{
    obj[0] = *(uint32_t *)((char *)frame - 0x48);
    *(char *)((char *)obj + 4) = *(char *)((char *)frame - 0x4c);
}

/* FUN_003576bc @ 0x003576bc  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_003576bc(void) { return; }

/* FUN_003576c8 @ 0x003576c8
 * Ghidra: long FUN_003576c8(undefined8,undefined8,ulong param_3)
 * Returns `(param_3 & 0x0fffffffffffffff) + 0x20` — rounded-up object length /
 * capacity (mirror of FUN_00357628 with the count in param_3).
 * Confidence: medium */
long FUN_003576c8(ulong len /* p3 */)
{
    return (long)((len & 0x0fffffffffffffff) + 0x20);
}

/* FUN_003576dc @ 0x003576dc
 * Ghidra: undefined1 [16] FUN_003576dc(ulong,ulong)
 * Byte-swaps a 16-byte value: each word's bytes are reversed in 16-bit groups,
 * then the two words are swapped. A Swift endianness / hash-order primitive.
 * Confidence: medium */
reg16 FUN_003576dc(ulong hi, ulong lo)
{
    reg16 out;
    ulong v;

    v  = ((hi & 0xff00ff00ff00ff00) >> 8) | ((hi & 0x00ff00ff00ff00ff) << 8);
    v  = ((v  & 0xffff0000ffff0000) >> 16) | ((v & 0x0000ffff0000ffff) << 16);
    out.hi = (v >> 32) | (v << 32);

    v  = ((lo & 0xff00ff00ff00ff00) >> 8) | ((lo & 0x00ff00ff00ff00ff) << 8);
    v  = ((v  & 0xffff0000ffff0000) >> 16) | ((v & 0x0000ffff0000ffff) << 16);
    out.lo = (v >> 32) | (v << 32);

    return out;
}

/* FUN_003576ec @ 0x003576ec  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_003576ec(void) { return; }

/* FUN_00357710 @ 0x00357710
 * Ghidra: undefined8 FUN_00357710(void)
 * Returns the caller's frame word at -0x98 — a spill reload / local forward.
 * Confidence: medium
 * Notes: frame base is unaff_x29. */
uint64_t FUN_00357710(uint64_t *frame /* x29 */)
{
    return *(uint64_t *)((char *)frame - 0x98);
}

/* FUN_0035772c @ 0x0035772c  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_0035772c(void) { return; }

/* FUN_00357748 @ 0x00357748  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00357748(void) { return; }

/* FUN_00357754 @ 0x00357754
 * Ghidra: undefined * FUN_00357754(void)
 * Returns the address of the global data object at 0x4e7d40 — a Swift opaque
 * metadata descriptor getter.
 * Confidence: medium
 * Notes: DAT_004e7d40. */
uint64_t *FUN_00357754(void)
{
    return &DAT_004e7d40;
}

/* FUN_00357760 @ 0x00357760  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00357760(void) { return; }

/* FUN_0035776c @ 0x0035776c
 * Ghidra: undefined1 [16] FUN_0035776c(undefined8,undefined8,undefined8)
 * Builds a 16-byte descriptor from two of the three register-passed words
 * (param_2 -> lo, param_3 -> hi). A Swift value-pair getter.
 * Confidence: medium */
reg16 FUN_0035776c(reg16 *unused, uint64_t lo, uint64_t hi)
{
    reg16 out;
    (void)unused;
    out.lo = lo;
    out.hi = hi;
    return out;
}

/* FUN_00357788 @ 0x00357788  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00357788(void) { return; }

/* FUN_00357794 @ 0x00357794  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00357794(void) { return; }

/* FUN_003577a0 @ 0x003577a0
 * Ghidra: long FUN_003577a0(void)
 * Returns `(x21 & 0x0fffffffffffffff) + 0x20` — rounded-up object length /
 * capacity (count passed in x21).
 * Confidence: medium
 * Notes: register-passed (unaff_x21). */
long FUN_003577a0(ulong len /* x21 */)
{
    return (long)((len & 0x0fffffffffffffff) + 0x20);
}

/* FUN_003577b4 @ 0x003577b4  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_003577b4(void) { return; }

/* FUN_003577c0 @ 0x003577c0  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_003577c0(void) { return; }

/* FUN_003577cc @ 0x003577cc
 * Ghidra: void FUN_003577cc(undefined8,undefined8,undefined8,undefined8,undefined8)
 * Forwards the first, third and fifth register-passed args to the tuple helper
 * at 0x1f99f4 (the even-positioned words are dropped).
 * Confidence: medium */
void FUN_003577cc(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t e)
{
    (void)b; (void)d;
    swift_tuple_call_1f99f4(a, c, e);
}

/* FUN_003577e4 @ 0x003577e4  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_003577e4(void) { return; }

/* FUN_003577f0 @ 0x003577f0
 * Ghidra: void FUN_003577f0(undefined8,long param_2)
 * Copies four fields (+0x10, +0x18, +0x20, +0x28) from src to dst — a Swift
 * struct copy helper (5-word struct minus the leading word).
 * Confidence: medium
 * Notes: register-passed (unaff_x19 dst). */
void FUN_003577f0(uint64_t *dst /* x19 */, uint64_t *src)
{
    dst[2] = src[2];                                /* +0x10 */
    dst[3] = src[3];                                /* +0x18 */
    dst[4] = src[4];                                /* +0x20 */
    *(char *)((char *)dst + 0x28) = *(char *)((char *)src + 0x28);
}

/* FUN_0035780c @ 0x0035780c
 * Ghidra: long FUN_0035780c(void)
 * Returns the address of the caller's frame slot at -0xa8 — a Swift inout /
 * indirect-result pointer.
 * Confidence: medium
 * Notes: frame base is unaff_x29. */
long FUN_0035780c(uint64_t *frame /* x29 */)
{
    return (long)((char *)frame - 0xa8);
}

/* FUN_00357818 @ 0x00357818
 * Ghidra: undefined8 FUN_00357818(void)
 * Returns the caller's frame word at -0x60 — a spill reload / local forward.
 * Confidence: medium
 * Notes: frame base is unaff_x29. */
uint64_t FUN_00357818(uint64_t *frame /* x29 */)
{
    return *(uint64_t *)((char *)frame - 0x60);
}

/* FUN_00357850 @ 0x00357850
 * Ghidra: ulong FUN_00357850(long param_1)
 * Returns `(param_1 << 16) | 4` — packs a count/flag into the low bits of a
 * descriptor (a size/tag word builder).
 * Confidence: medium */
ulong FUN_00357850(ulong v)
{
    return (v << 0x10) | 4;
}

/* FUN_0035785c @ 0x0035785c  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_0035785c(void) { return; }

/* FUN_00357868 @ 0x00357868  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00357868(void) { return; }

/* FUN_00357874 @ 0x00357874
 * Ghidra: long FUN_00357874(ulong,long)
 * Returns `param_2 + ((param_1 + 0x20) & ~param_1)` — a pointer round-up to the
 * next multiple of the aligned region (masking the low alignment bits of the
 * base). A Swift allocator bump-alignment helper.
 * Confidence: medium */
long FUN_00357874(ulong base, long cur)
{
    return cur + (long)((base + 0x20) & (base ^ 0xffffffffffffffffull));
}

/* FUN_00357884 @ 0x00357884  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00357884(void) { return; }

/* FUN_00357898 @ 0x00357898
 * Ghidra: void FUN_00357898(void)
 * Forwards to the Swift runtime helper at 0x258c60 with no extra arguments.
 * Confidence: medium */
void FUN_00357898(void) { swift_runtime_call_258c60(); }

/* FUN_003578a8 @ 0x003578a8
 * Ghidra: undefined8 FUN_003578a8(void)
 * Returns the caller's frame word at -0x88 — a spill reload / local forward.
 * Confidence: medium
 * Notes: frame base is unaff_x29. */
uint64_t FUN_003578a8(uint64_t *frame /* x29 */)
{
    return *(uint64_t *)((char *)frame - 0x88);
}

/* FUN_003578b4 @ 0x003578b4  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_003578b4(void) { return; }

/* FUN_003578c0 @ 0x003578c0
 * Ghidra: undefined8 FUN_003578c0(void)
 * Returns the caller's frame word at -0x80 — a spill reload / local forward.
 * Confidence: medium
 * Notes: frame base is unaff_x29. */
uint64_t FUN_003578c0(uint64_t *frame /* x29 */)
{
    return *(uint64_t *)((char *)frame - 0x80);
}

/* FUN_003578cc @ 0x003578cc  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_003578cc(void) { return; }

/* FUN_003578d8 @ 0x003578d8  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_003578d8(void) { return; }

/* FUN_003578e4 @ 0x003578e4
 * Ghidra: void FUN_003578e4(void)
 * Forwards to the Swift runtime helper at 0x1ef804 with no extra arguments.
 * Confidence: medium */
void FUN_003578e4(void) { swift_runtime_call_1ef804(); }

/* FUN_00357904 @ 0x00357904  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00357904(void) { return; }

/* FUN_00357910 @ 0x00357910  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00357910(void) { return; }

/* FUN_0035792c @ 0x0035792c  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_0035792c(void) { return; }

/* FUN_00357938 @ 0x00357938
 * Ghidra: ulong FUN_00357938(ulong param_1)
 * Returns `in_x9 | param_1 | 1` — sets the low "occupied/inline" flag and ORs
 * in a register-passed tag. A Swift enum-tag merge helper.
 * Confidence: medium
 * Notes: register-passed (in_x9). */
ulong FUN_00357938(ulong v /* x0 */, ulong tag /* x9 */)
{
    return tag | v | 1;
}

/* FUN_00357944 @ 0x00357944  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00357944(void) { return; }

/* FUN_00357958 @ 0x00357958  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00357958(void) { return; }

/* FUN_00357964 @ 0x00357964  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00357964(void) { return; }

/* FUN_00357970 @ 0x00357970  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00357970(void) { return; }

/* FUN_0035798c @ 0x0035798c  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_0035798c(void) { return; }

/* FUN_00357998 @ 0x00357998  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00357998(void) { return; }

/* FUN_003579a4 @ 0x003579a4  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_003579a4(void) { return; }

/* FUN_003579c0 @ 0x003579c0
 * Ghidra: long FUN_003579c0(long param_1)
 * Returns `x19 + *(int *)(param_1 + 0x24)` — base plus a 32-bit element offset
 * at +0x24. An indexed-element address helper.
 * Confidence: medium
 * Notes: register-passed (unaff_x19 base). */
long FUN_003579c0(long base /* x19 */, long obj)
{
    return base + *(int *)(obj + 0x24);
}

/* FUN_003579cc @ 0x003579cc  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_003579cc(void) { return; }

/* FUN_003579d8 @ 0x003579d8
 * Ghidra: void FUN_003579d8(void)
 * Forwards to the shared helper at 0x3722e4 with no arguments.
 * Confidence: medium */
void FUN_003579d8(void) { FUN_003722e4(0, 0, 0, 0, 0); }

/* FUN_003579e8 @ 0x003579e8  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_003579e8(void) { return; }

/* FUN_003579f4 @ 0x003579f4  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_003579f4(void) { return; }

/* FUN_00357a00 @ 0x00357a00  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00357a00(void) { return; }

/* FUN_00357a0c @ 0x00357a0c  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00357a0c(void) { return; }

/* FUN_00357a18 @ 0x00357a18  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00357a18(void) { return; }

/* FUN_00357a34 @ 0x00357a34  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00357a34(void) { return; }

/* FUN_00357a5c @ 0x00357a5c
 * Ghidra: undefined8 FUN_00357a5c(void)
 * Returns the caller's frame word at -0x78 — a spill reload / local forward.
 * Confidence: medium
 * Notes: frame base is unaff_x29. */
uint64_t FUN_00357a5c(uint64_t *frame /* x29 */)
{
    return *(uint64_t *)((char *)frame - 0x78);
}

/* FUN_00357a68 @ 0x00357a68  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00357a68(void) { return; }

/* FUN_00357a84 @ 0x00357a84  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00357a84(void) { return; }

/* FUN_00357a90 @ 0x00357a90
 * Ghidra: undefined8 FUN_00357a90(void)
 * Returns the caller's frame word at -0xa0 — a spill reload / local forward.
 * Confidence: medium
 * Notes: frame base is unaff_x29. */
uint64_t FUN_00357a90(uint64_t *frame /* x29 */)
{
    return *(uint64_t *)((char *)frame - 0xa0);
}

/* FUN_00357a9c @ 0x00357a9c  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00357a9c(void) { return; }

/* FUN_00357aa8 @ 0x00357aa8  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00357aa8(void) { return; }

/* FUN_00357ab4 @ 0x00357ab4  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00357ab4(void) { return; }

/* FUN_00357ac0 @ 0x00357ac0  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00357ac0(void) { return; }

/* FUN_00357acc @ 0x00357acc
 * Ghidra: void FUN_00357acc(undefined8 param_1)
 * Forwards to the tag diagnostic helper at 0x310d68 with the constant tag
 * 0x13f and the register-passed argument. A Swift runtime validation/precond
 * check site.
 * Confidence: medium
 * Notes: tag constant 0x13f (319). */
void FUN_00357acc(uint64_t arg)
{
    swift_tag_diag_310d68(0x13f, arg);
}

/* FUN_00357aec @ 0x00357aec  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00357aec(void) { return; }

/* FUN_00357af8 @ 0x00357af8  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00357af8(void) { return; }

/* FUN_00357b04 @ 0x00357b04  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00357b04(void) { return; }

/* FUN_00357b10 @ 0x00357b10
 * Ghidra: void FUN_00357b10(void)
 * Forwards to the object-dispatch helper at 0x26e8 with the address of a stack
 * slot — an object-method-table access on a fresh local.
 * Confidence: medium
 * Notes: arg is a stack slot (stack0x00000008). */
void FUN_00357b10(void)
{
    uint64_t slot = 0;
    swift_obj_dispatch_26e8((uint64_t)&slot);
}

/* FUN_00357b20 @ 0x00357b20
 * Ghidra: undefined1 * FUN_00357b20(void)
 * Returns the address of the caller's stack slot (stack0x00000008) — a Swift
 * inout/indirect-result pointer.
 * Confidence: medium
 * Notes: stack-slot pointer return. */
uint64_t *FUN_00357b20(void)
{
    static uint64_t slot = 0;
    return &slot;
}

/* FUN_00357b2c @ 0x00357b2c
 * Ghidra: void FUN_00357b2c(undefined8,undefined8)
 * Forwards to the runtime helper at 0x1bcc18 with the two register-passed args
 * in swapped order.
 * Confidence: medium */
void FUN_00357b2c(uint64_t a, uint64_t b)
{
    swift_runtime_swap_1bcc18(b, a);
}

/* FUN_00357b3c @ 0x00357b3c  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00357b3c(void) { return; }

/* FUN_00357b48 @ 0x00357b48  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00357b48(void) { return; }

/* FUN_00357b54 @ 0x00357b54  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00357b54(void) { return; }

/* FUN_00357b60 @ 0x00357b60  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00357b60(void) { return; }

/* FUN_00357b7c @ 0x00357b7c  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00357b7c(void) { return; }

/* FUN_00357b88 @ 0x00357b88
 * Ghidra: undefined8 FUN_00357b88(void)
 * Returns zero — a constant-false / null-result stub.
 * Confidence: medium */
uint64_t FUN_00357b88(void) { return 0; }

/* FUN_00357ba4 @ 0x00357ba4
 * Ghidra: void FUN_00357ba4(void)
 * Invokes two Swift runtime helpers in sequence (0x310a74 then 0x1df60).
 * Confidence: medium */
void FUN_00357ba4(void)
{
    swift_runtime_call_310a74();
    swift_runtime_call_1df60();
}

/* FUN_00357bc4 @ 0x00357bc4
 * Ghidra: undefined8 FUN_00357bc4(void)
 * Returns the register-passed word unchanged (in_x3) — an identity shim.
 * Confidence: medium
 * Notes: register-passed (in_x3). */
uint64_t FUN_00357bc4(uint64_t v /* x3 */)
{
    return v;
}

/* FUN_00357bd0 @ 0x00357bd0
 * Ghidra: void FUN_00357bd0(void)
 * Forwards to the Swift string fatal-precondition path at 0x1afa84 (noreturn).
 * Traps with the fatal text.
 * Confidence: medium */
void FUN_00357bd0(void)
{
    swift_string_fatal_precondition();
}

/* FUN_00357be0 @ 0x00357be0  (est. protocol-witness no-op stub) — returns immediately. */
void FUN_00357be0(void) { return; }

/* FUN_00357bec @ 0x00357bec
 * Ghidra: void FUN_00357bec(void)
 * Forwards to the shared helper at 0x3722e4 with no arguments.
 * Confidence: medium */
void FUN_00357bec(void) { FUN_003722e4(0, 0, 0, 0, 0); }
