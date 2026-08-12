/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel, GL1,
 * arm64e, image base 0) — the cL4 microkernel. Ground truth: Ghidra FUN_ names +
 * addresses in cl4_kernel.raw. Version "cL4 microkernel (cL4 (679.100.61))".
 * All names are estimates unless string/header-matched.
 * Slice: 0x00463fe8-0x00464930 (SKR22) — a dense run of small object/name
 * helpers and nop stubs. Most bodies are 1-4 instructions: 16-byte word-pair
 * factories that encode an object-type tag + small constant or an ASCII name
 * (several Unicode script names), register/stack fragments that copy a few
 * fields between structs, and single helper calls. */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>

#include "sk_internal.h"

/* ------------------------------------------------------------------ *
 * Out-of-range cL4 helpers called from this slice (declared extern with a
 * one-line note; bodies are reconstructed by the range workers that own them).
 * Ground truth FUN_ address in comment.
 * ------------------------------------------------------------------ */

extern void FUN_0029fa0c(void);                              /* FUN_0029fa0c obj_slice_02 */
extern void FUN_00457994(word_t a, word_t b, word_t c);      /* FUN_00457994 */
extern void FUN_00002534(const void *a, const void *b);      /* FUN_00002534 boot */
extern void thunk_FUN_002acbb8(word_t a, word_t b);          /* FUN_002acbb8 obj_slice_11 report emit */
extern void FUN_0042ec68(void *frame);                       /* FUN_0042ec68 */
extern void thunk_FUN_0001a1c8(word_t a, word_t b);          /* FUN_0001a1c8 boot helper */
extern void FUN_001a84f4(void *p, int v);                    /* FUN_001a84f4 */
extern void FUN_002a4ab4(word_t v);                          /* FUN_002a4ab4 obj_slice_03 */
extern void thunk_FUN_0036b270(void);                        /* FUN_0036b270 refcount acquire */
extern void FUN_00117cc4(void *dst, ...);                    /* FUN_00117cc4 memcpy-like */
extern void FUN_00461894(void);                              /* FUN_00461894 */

/* Data constants referenced by this slice (Ghidra DAT_ artifacts). */
extern unsigned char DAT_006575f0;
extern unsigned char DAT_005a19e0;
extern unsigned char DAT_005a19f0;

/* ------------------------------------------------------------------ *
 * Shared 16-byte word pair. Many functions in this slice return a 16-byte
 * object in x0:x1 (aarch64e ABI). lo lands in x0, hi in x1. The hi word usually
 * carries an object-type tag in its top byte plus a value/pointer; the lo word
 * is a small constant or an ASCII name (decoded in per-function notes).
 * ------------------------------------------------------------------ */
typedef struct {
    uint64_t lo;   /* x0 */
    uint64_t hi;   /* x1 */
} cl4_pair_t;

/* ================================================================== *
 * SKR22 function bodies (address order)
 * ================================================================== */

/* FUN_00463fe8 @ 0x00463fe8   (est. sk_wp_63fe8)
 * Ghidra: undefined1 [16] FUN_00463fe8(void)
 * Returns the 16-byte pair { lo=0x20, hi=0xe1... }: hi carries object-type tag
 * 0xe1 with zero payload, lo is the small constant 0x20. Likely a canonical
 * capability/name descriptor for an object kind.
 * Confidence: medium
 * Notes: 16-byte return in x0:x1. */
cl4_pair_t FUN_00463fe8(void)
{
    return (cl4_pair_t){ .lo = 0x20, .hi = 0xe100000000000000 };
}

/* FUN_00463ff4 @ 0x00463ff4   (est. sk_nop_63ff4)
 * Ghidra: void FUN_00463ff4(void)
 * Empty stub — performs no work. One of many placeholder entry points in this
 * region.
 * Confidence: high
 * Notes: empty body. */
void FUN_00463ff4(void)
{
    return;
}

/* FUN_00464000 @ 0x00464000   (est. sk_nop_64000)
 * Ghidra: void FUN_00464000(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_00464000(void)
{
    return;
}

/* FUN_0046400c @ 0x0046400c   (est. sk_nop_6400c)
 * Ghidra: void FUN_0046400c(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_0046400c(void)
{
    return;
}

/* FUN_00464034 @ 0x00464034   (est. sk_nop_64034)
 * Ghidra: void FUN_00464034(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_00464034(void)
{
    return;
}

/* FUN_00464040 @ 0x00464040   (est. sk_nop_64040)
 * Ghidra: void FUN_00464040(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_00464040(void)
{
    return;
}

/* FUN_0046404c @ 0x0046404c   (est. sk_copy_byte_6404c)
 * Ghidra: void FUN_0046404c(undefined1 *param_1, undefined1 *param_2)
 * Copies a single byte from the source object to the destination object.
 * Confidence: medium
 * Notes: trivial single-byte load/store. */
void FUN_0046404c(uint8_t *dst, const uint8_t *src)
{
    *dst = *src;
}

/* FUN_00464058 @ 0x00464058   (est. sk_nop_64058)
 * Ghidra: void FUN_00464058(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_00464058(void)
{
    return;
}

/* FUN_00464064 @ 0x00464064   (est. sk_copy_wordpair_64064)
 * Ghidra: void FUN_00464064(void)
 * Register fragment: reads four 8-byte words at +0x130..+0x148 of the object
 * held in callee-saved x20 and writes them to four consecutive stack slots
 * (dead stores — never consumed). Reconstructed as copying to a local buffer.
 * Confidence: low
 * Notes: register fragment (unaff x20, x29). */
void FUN_00464064(word_t obj)
{
    word_t buf[4];
    buf[0] = *(word_t *)(obj + 0x130);
    buf[1] = *(word_t *)(obj + 0x138);
    buf[2] = *(word_t *)(obj + 0x140);
    buf[3] = *(word_t *)(obj + 0x148);
}

/* FUN_00464090 @ 0x00464090   (est. sk_call_64090)
 * Ghidra: void FUN_00464090(void)
 * Tail-calls the helper FUN_0029fa0c (vspace/page-walk step) and returns.
 * Confidence: low
 * Notes: single call, no args visible to the decompiler. */
void FUN_00464090(void)
{
    FUN_0029fa0c();
}

/* FUN_004640a4 @ 0x004640a4   (est. sk_call_640a4)
 * Ghidra: void FUN_004640a4(undefined8 param_1)
 * Forwards three arguments (the explicit first param plus two stack-passed
 * values) to FUN_00457994 and returns.
 * Confidence: low
 * Notes: two stack args (in_stack_00000010/00000008) folded into params. */
void FUN_004640a4(word_t a, word_t b, word_t c)
{
    FUN_00457994(a, b, c);
}

/* FUN_004640b8 @ 0x004640b8   (est. sk_copy_word_640b8)
 * Ghidra: void FUN_004640b8(long param_1,long param_2)
 * Copies the 8-byte word at offset +8 of the source struct to the same offset
 * of the destination struct.
 * Confidence: high (verified 1:1 vs decompile; single word copy, no opaque items)
 * Notes: single word copy. */
void FUN_004640b8(word_t dst, word_t src)
{
    *(word_t *)(dst + 8) = *(word_t *)(src + 8);
}

/* FUN_004640c4 @ 0x004640c4   (est. sk_wp_640c4)
 * Ghidra: undefined1 [16] FUN_004640c4(void)
 * Returns the 16-byte pair { lo=0x5d, hi=0xe1... }: tag 0xe1 with lo constant
 * 0x5d. Same shape as FUN_00463fe8, different value.
 * Confidence: medium
 * Notes: 16-byte return in x0:x1. */
cl4_pair_t FUN_004640c4(void)
{
    return (cl4_pair_t){ .lo = 0x5d, .hi = 0xe100000000000000 };
}

/* FUN_004640d0 @ 0x004640d0   (est. sk_store_regs_640d0)
 * Ghidra: void FUN_004640d0(void)
 * Register fragment: stores four callee-saved register values (x21..x24) into
 * four consecutive words at the address held in x20.
 * Confidence: low
 * Notes: register fragment (unaff x20..x24); values folded into params. */
void FUN_004640d0(word_t *dst, word_t a, word_t b, word_t c, word_t d)
{
    dst[0] = a;
    dst[1] = b;
    dst[2] = c;
    dst[3] = d;
}

/* FUN_004640dc @ 0x004640dc   (est. sk_call_640dc)
 * Ghidra: void FUN_004640dc(void)
 * Calls FUN_00002534 with two global-data addresses (DAT_006575f0,
 * DAT_005a19e0) and returns.
 * Confidence: low
 * Notes: references two global buffers. */
void FUN_004640dc(void)
{
    FUN_00002534(&DAT_006575f0, &DAT_005a19e0);
}

/* FUN_004640f0 @ 0x004640f0   (est. sk_nop_640f0)
 * Ghidra: void FUN_004640f0(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_004640f0(void)
{
    return;
}

/* FUN_0046411c @ 0x0046411c   (est. sk_encode_6411c)
 * Ghidra: ulong FUN_0046411c(ulong param_1)
 * Masks the argument to its low 48 bits and ORs in the constant tag
 * 0x61000000000000, producing a tagged (type-tag + address) word.
 * Confidence: medium
 * Notes: tag/address packing. */
word_t FUN_0046411c(word_t v)
{
    return (v & 0xffffffffffff) | 0x61000000000000;
}

/* FUN_00464128 @ 0x00464128   (est. sk_nop_64128)
 * Ghidra: void FUN_00464128(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_00464128(void)
{
    return;
}

/* FUN_00464134 @ 0x00464134   (est. sk_const_one_64134)
 * Ghidra: undefined8 FUN_00464134(void)
 * Returns the constant 1 (boolean true / single element).
 * Confidence: medium
 * Notes: returns literal 1. */
word_t FUN_00464134(void)
{
    return 1;
}

/* FUN_00464140 @ 0x00464140   (est. sk_stack_ptr_64140)
 * Ghidra: undefined1 * FUN_00464140(void)
 * Returns a pointer into the caller's stack frame (address of a local slot).
 * Register fragment: the returned pointer is the address of a stack local.
 * Confidence: low
 * Notes: returns &stack0x00000008 (dead stack reference). */
uint8_t *FUN_00464140(void)
{
    uint8_t local[8];
    return local;
}

/* FUN_0046414c @ 0x0046414c   (est. sk_nop_6414c)
 * Ghidra: void FUN_0046414c(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_0046414c(void)
{
    return;
}

/* FUN_00464158 @ 0x00464158   (est. sk_script_name_64158)
 * Ghidra: undefined1 [16] FUN_00464158(void)
 * Returns a 16-byte name descriptor: lo carries 8 ASCII bytes "zanabaza", hi
 * carries "rsquare" plus tag 0xef. The tag byte encodes a script/name table
 * kind (0xef family used by the adjacent name factories).
 * Confidence: medium
 * Notes: lo decoded "zanabaza", hi "rsquare"+0xef tag. */
cl4_pair_t FUN_00464158(void)
{
    return (cl4_pair_t){ .lo = 0x617a6162616e617a, .hi = 0xef65726175717372 };
}

/* FUN_00464180 @ 0x00464180   (est. sk_script_name_64180)
 * Ghidra: undefined1 [16] FUN_00464180(void)
 * Returns a name descriptor: lo carries the 2 ASCII bytes "si", hi carries tag
 * 0xe2 with zero payload.
 * Confidence: medium
 * Notes: lo decoded "si", hi tag 0xe2. */
cl4_pair_t FUN_00464180(void)
{
    return (cl4_pair_t){ .lo = 0x7369, .hi = 0xe200000000000000 };
}

/* FUN_0046418c @ 0x0046418c   (est. sk_inc_field_6418c)
 * Ghidra: void FUN_0046418c(void)
 * Register fragment: stores (value + 1) into the word at +0x10 of the object
 * held in x19; the addend comes from callee-saved x26.
 * Confidence: low
 * Notes: register fragment (unaff x19, x26). */
void FUN_0046418c(word_t obj, word_t v)
{
    *(word_t *)(obj + 0x10) = v + 1;
}

/* FUN_004641a0 @ 0x004641a0   (est. sk_script_name_641a0)
 * Ghidra: undefined1 [16] FUN_004641a0(void)
 * Returns a name descriptor for the script "Siddham": lo carries 7 ASCII bytes
 * "Siddham", hi carries tag 0xe7.
 * Confidence: medium
 * Notes: lo decoded "Siddham", hi tag 0xe7. */
cl4_pair_t FUN_004641a0(void)
{
    return (cl4_pair_t){ .lo = 0x6d616864646953, .hi = 0xe700000000000000 };
}

/* FUN_004641b8 @ 0x004641b8   (est. sk_script_name_641b8)
 * Ghidra: undefined1 [16] FUN_004641b8(void)
 * Returns a name descriptor for the script "Tagalog": lo carries 7 ASCII bytes
 * "Tagalog", hi carries tag 0xe7.
 * Confidence: medium
 * Notes: lo decoded "Tagalog", hi tag 0xe7. */
cl4_pair_t FUN_004641b8(void)
{
    return (cl4_pair_t){ .lo = 0x676f6c61676154, .hi = 0xe700000000000000 };
}

/* FUN_004641d0 @ 0x004641d0   (est. sk_script_name_641d0)
 * Ghidra: undefined1 [16] FUN_004641d0(void)
 * Returns a name descriptor for the script "Deseret": lo carries 7 ASCII bytes
 * "Deseret", hi carries tag 0xe7.
 * Confidence: medium
 * Notes: lo decoded "Deseret", hi tag 0xe7. */
cl4_pair_t FUN_004641d0(void)
{
    return (cl4_pair_t){ .lo = 0x74657265736544, .hi = 0xe700000000000000 };
}

/* FUN_004641e8 @ 0x004641e8   (est. sk_copy_fields_641e8)
 * Ghidra: void FUN_004641e8(void)
 * Register fragment: copies the word at +0x40 and the byte at +0x48 of the
 * source struct (x19) into the same offsets of the destination (x20).
 * Confidence: low
 * Notes: register fragment (unaff x19, x20). */
void FUN_004641e8(word_t dst, word_t src)
{
    *(word_t *)(dst + 0x40) = *(word_t *)(src + 0x40);
    *(uint8_t *)(dst + 0x48) = *(uint8_t *)(src + 0x48);
}

/* FUN_004641fc @ 0x004641fc   (est. sk_script_name_641fc)
 * Ghidra: undefined1 [16] FUN_004641fc(void)
 * Returns a name descriptor: lo carries 8 ASCII bytes "sylotina", hi carries
 * "gri" plus tag 0xeb. Together spells the script "Syloti Nagri" split across
 * the two words with the tag in the top byte of hi.
 * Confidence: medium
 * Notes: lo decoded "sylotina", hi "gri"+0xeb tag -> "Syloti Nagri". */
cl4_pair_t FUN_004641fc(void)
{
    return (cl4_pair_t){ .lo = 0x616e69746f6c7973, .hi = 0xeb00000000697267 };
}

/* FUN_00464224 @ 0x00464224   (est. sk_report_64224)
 * Ghidra: void FUN_00464224(void)
 * Emits a report/trace record: calls thunk_FUN_002acbb8 (report emit) with a
 * small selector (0x7c) and a type tag word (0xe1...).
 * Confidence: low
 * Notes: report emit call with (0x7c, 0xe1...). */
void FUN_00464224(void)
{
    thunk_FUN_002acbb8(0x7c, 0xe100000000000000);
}

/* FUN_00464234 @ 0x00464234   (est. sk_wp_64234)
 * Ghidra: undefined1 [16] FUN_00464234(void)
 * Returns a 16-byte pair: lo = constant 0x657a08, hi = address of the global
 * DAT_005a19f0. A descriptor coupling a small constant with a data pointer.
 * Confidence: low
 * Notes: hi = &DAT_005a19f0. */
cl4_pair_t FUN_00464234(void)
{
    return (cl4_pair_t){ .lo = 0x657a08, .hi = (word_t)(uintptr_t)&DAT_005a19f0 };
}

/* FUN_00464248 @ 0x00464248   (est. sk_nop_64248)
 * Ghidra: void FUN_00464248(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_00464248(void)
{
    return;
}

/* FUN_00464258 @ 0x00464258   (est. sk_store_word_64258)
 * Ghidra: void FUN_00464258(ulong param_1)
 * Register fragment: stores (param_1 & 0xff) into the first word of the object
 * held in x19, and zeroes the following three words. Initializes a small
 * byte-valued header field plus a zeroed tail.
 * Confidence: low
 * Notes: register fragment (unaff x19). */
void FUN_00464258(word_t obj, word_t v)
{
    word_t *p = (word_t *)obj;
    p[0] = v & 0xff;
    p[1] = 0;
    p[2] = 0;
    p[3] = 0;
}

/* FUN_00464268 @ 0x00464268   (est. sk_frame_call_64268)
 * Ghidra: void FUN_00464268(void)
 * Builds a small local frame with type/state fields {w0=0, w1=0, tag=3} at the
 * expected offsets and passes the frame base to FUN_0042ec68. (Mirror of
 * FUN_004642a8 which performs the same init.)
 * Confidence: low
 * Notes: local frame init {0,0,3}; stack offsets from x29. */
void FUN_00464268(void)
{
    uint8_t frame[0xb0];
    *(word_t *)(frame + 0x38) = 0;
    *(word_t *)(frame + 0x40) = 0;
    *(uint8_t *)(frame + 0x48) = 3;
    FUN_0042ec68(frame);
}

/* FUN_00464280 @ 0x00464280   (est. sk_script_name_64280)
 * Ghidra: undefined1 [16] FUN_00464280(void)
 * Returns a name descriptor for the script "Psalter Pahlavi": lo carries 8
 * ASCII bytes, hi carries the tail plus tag 0xee.
 * Confidence: medium
 * Notes: decoded "psalterpahlavi", hi tag 0xee. */
cl4_pair_t FUN_00464280(void)
{
    return (cl4_pair_t){ .lo = 0x707265746c617370, .hi = 0xee006976616c6861 };
}

/* FUN_004642a8 @ 0x004642a8   (est. sk_frame_call_642a8)
 * Ghidra: void FUN_004642a8(void)
 * Builds a small local frame with type/state fields {w0=0, w1=0, tag=3} and
 * passes its base to FUN_0042ec68. Same init as FUN_00464268.
 * Confidence: low
 * Notes: local frame init {0,0,3}; stack offsets. */
void FUN_004642a8(void)
{
    uint8_t frame[0xa0];
    *(word_t *)(frame + 0x38) = 0;
    *(word_t *)(frame + 0x40) = 0;
    *(uint8_t *)(frame + 0x48) = 3;
    FUN_0042ec68(frame);
}

/* FUN_004642c0 @ 0x004642c0   (est. sk_nop_642c0)
 * Ghidra: void FUN_004642c0(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_004642c0(void)
{
    return;
}

/* FUN_004642d4 @ 0x004642d4   (est. sk_nop_642d4)
 * Ghidra: void FUN_004642d4(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_004642d4(void)
{
    return;
}

/* FUN_004642e8 @ 0x004642e8   (est. sk_frame_store_642e8)
 * Ghidra: void FUN_004642e8(undefined8 param_1)
 * Register fragment: writes a three-field record into a local frame: type tag
 * 1 at offset 0, then the two word values (param_1 and callee-saved x9) at +8
 * and +0x10.
 * Confidence: low
 * Notes: register fragment (unaff x9); frame offset -0xa8. */
void FUN_004642e8(word_t a, word_t b)
{
    uint8_t frame[0xb0];
    *(uint8_t *)(frame + 0) = 1;
    *(word_t *)(frame + 8) = a;
    *(word_t *)(frame + 0x10) = b;
}

/* FUN_004642f8 @ 0x004642f8   (est. sk_nop_642f8)
 * Ghidra: void FUN_004642f8(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_004642f8(void)
{
    return;
}

/* FUN_00464308 @ 0x00464308   (est. sk_nop_64308)
 * Ghidra: void FUN_00464308(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_00464308(void)
{
    return;
}

/* FUN_00464318 @ 0x00464318   (est. sk_script_name_64318)
 * Ghidra: undefined1 [16] FUN_00464318(void)
 * Returns a name descriptor for the script "Meroitic Cursive": lo carries 8
 * ASCII bytes, hi carries the tail plus tag 0xef.
 * Confidence: medium
 * Notes: decoded "meroiticursive", hi tag 0xef. */
cl4_pair_t FUN_00464318(void)
{
    return (cl4_pair_t){ .lo = 0x636974696f72656d, .hi = 0xef65766973727563 };
}

/* FUN_00464340 @ 0x00464340   (est. sk_copy_quad_64340)
 * Ghidra: void FUN_00464340(void)
 * Register fragment: copies four consecutive words from +0x28..+0x40 of the
 * source struct (x20) into the same offsets of the destination (x19).
 * Confidence: low
 * Notes: register fragment (unaff x19, x20). */
void FUN_00464340(word_t dst, word_t src)
{
    word_t v1, v3;
    v1 = *(word_t *)(src + 0x30);
    *(word_t *)(dst + 0x30) = *(word_t *)(src + 0x30);
    *(word_t *)(dst + 0x28) = *(word_t *)(src + 0x28);
    v3 = *(word_t *)(src + 0x40);
    *(word_t *)(dst + 0x40) = *(word_t *)(src + 0x40);
    *(word_t *)(dst + 0x38) = *(word_t *)(src + 0x38);
}

/* FUN_00464354 @ 0x00464354   (est. sk_copy_and_acquire_64354)
 * Ghidra: void FUN_00464354(undefined8 param_1,long param_2)
 * Copies the word at +8 of the source struct into the destination held in x20,
 * then acquires a reference via thunk_FUN_0036b270 (refcount acquire).
 * Confidence: low
 * Notes: register fragment (unaff x20); then refcount acquire call. */
void FUN_00464354(word_t dst, word_t src)
{
    *(word_t *)(dst + 8) = *(word_t *)(src + 8);
    thunk_FUN_0036b270();
}

/* FUN_00464364 @ 0x00464364   (est. sk_nop_64364)
 * Ghidra: void FUN_00464364(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_00464364(void)
{
    return;
}

/* FUN_00464378 @ 0x00464378   (est. sk_call_64378)
 * Ghidra: void FUN_00464378(void)
 * Calls thunk_FUN_0001a1c8 (boot helper) with a constant tag word 0xd0...22
 * and one stack-passed value.
 * Confidence: low
 * Notes: stack arg in_stack_00000068 folded into param. */
void FUN_00464378(word_t v)
{
    thunk_FUN_0001a1c8(0xd000000000000022, v);
}

/* FUN_00464388 @ 0x00464388   (est. sk_tagged_ptr_64388)
 * Ghidra: undefined1 [16] FUN_00464388(long param_1)
 * Returns a tagged-pointer pair: lo = error/kind code 0xd0...1a, hi =
 * (param_1 - 0x20) with the high bit set (0x8000...). Constructs a capability
 * word from a raw pointer with an encoded kind tag.
 * Confidence: medium
 * Notes: hi sets top bit on (ptr - 0x20). */
cl4_pair_t FUN_00464388(word_t p)
{
    return (cl4_pair_t){ .lo = 0xd00000000000001a, .hi = (p - 0x20) | 0x8000000000000000 };
}

/* FUN_004643a0 @ 0x004643a0   (est. sk_tagged_ptr_643a0)
 * Ghidra: undefined1 [16] FUN_004643a0(long param_1)
 * Returns a tagged-pointer pair: lo = 0xd0...11, hi = (param_1 - 0x20) with the
 * high bit set. Same construction as FUN_00464388, different kind code.
 * Confidence: medium
 * Notes: hi sets top bit on (ptr - 0x20). */
cl4_pair_t FUN_004643a0(word_t p)
{
    return (cl4_pair_t){ .lo = 0xd000000000000011, .hi = (p - 0x20) | 0x8000000000000000 };
}

/* FUN_004643b8 @ 0x004643b8   (est. sk_nop_643b8)
 * Ghidra: void FUN_004643b8(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_004643b8(void)
{
    return;
}

/* FUN_004643cc @ 0x004643cc   (est. sk_nop_643cc)
 * Ghidra: void FUN_004643cc(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_004643cc(void)
{
    return;
}

/* FUN_004643d8 @ 0x004643d8   (est. sk_tagged_ptr_643d8)
 * Ghidra: undefined1 [16] FUN_004643d8(long param_1)
 * Returns a tagged-pointer pair: lo = 0xd0...12, hi = (param_1 - 0x20) with the
 * high bit set.
 * Confidence: medium
 * Notes: hi sets top bit on (ptr - 0x20). */
cl4_pair_t FUN_004643d8(word_t p)
{
    return (cl4_pair_t){ .lo = 0xd000000000000012, .hi = (p - 0x20) | 0x8000000000000000 };
}

/* FUN_004643f0 @ 0x004643f0   (est. sk_tagged_ptr_643f0)
 * Ghidra: undefined1 [16] FUN_004643f0(long param_1)
 * Returns a tagged-pointer pair: lo = 0xd0...16, hi = (param_1 - 0x20) with the
 * high bit set.
 * Confidence: medium
 * Notes: hi sets top bit on (ptr - 0x20). */
cl4_pair_t FUN_004643f0(word_t p)
{
    return (cl4_pair_t){ .lo = 0xd000000000000016, .hi = (p - 0x20) | 0x8000000000000000 };
}

/* FUN_00464408 @ 0x00464408   (est. sk_tagged_ptr_64408)
 * Ghidra: undefined1 [16] FUN_00464408(long param_1)
 * Returns a tagged-pointer pair: lo = 0xd0...13, hi = (param_1 - 0x20) with the
 * high bit set.
 * Confidence: medium
 * Notes: hi sets top bit on (ptr - 0x20). */
cl4_pair_t FUN_00464408(word_t p)
{
    return (cl4_pair_t){ .lo = 0xd000000000000013, .hi = (p - 0x20) | 0x8000000000000000 };
}

/* FUN_00464420 @ 0x00464420   (est. sk_tagged_ptr_64420)
 * Ghidra: undefined1 [16] FUN_00464420(long param_1)
 * Returns a tagged-pointer pair: lo = 0xd0...25, hi = (param_1 - 0x20) with the
 * high bit set.
 * Confidence: medium
 * Notes: hi sets top bit on (ptr - 0x20). */
cl4_pair_t FUN_00464420(word_t p)
{
    return (cl4_pair_t){ .lo = 0xd000000000000025, .hi = (p - 0x20) | 0x8000000000000000 };
}

/* FUN_00464438 @ 0x00464438   (est. sk_tagged_ptr_64438)
 * Ghidra: undefined1 [16] FUN_00464438(long param_1)
 * Returns a tagged-pointer pair: lo = 0xd0...11, hi = (param_1 - 0x20) with the
 * high bit set.
 * Confidence: medium
 * Notes: hi sets top bit on (ptr - 0x20). */
cl4_pair_t FUN_00464438(word_t p)
{
    return (cl4_pair_t){ .lo = 0xd000000000000011, .hi = (p - 0x20) | 0x8000000000000000 };
}

/* FUN_00464450 @ 0x00464450   (est. sk_tagged_ptr_64450)
 * Ghidra: undefined1 [16] FUN_00464450(long param_1)
 * Returns a tagged-pointer pair: lo = 0xd0...27, hi = (param_1 - 0x20) with the
 * high bit set.
 * Confidence: medium
 * Notes: hi sets top bit on (ptr - 0x20). */
cl4_pair_t FUN_00464450(word_t p)
{
    return (cl4_pair_t){ .lo = 0xd000000000000027, .hi = (p - 0x20) | 0x8000000000000000 };
}

/* FUN_00464468 @ 0x00464468   (est. sk_tagged_ptr_64468)
 * Ghidra: undefined1 [16] FUN_00464468(long param_1)
 * Returns a tagged-pointer pair: lo = 0xd0...14, hi = (param_1 - 0x20) with the
 * high bit set.
 * Confidence: medium
 * Notes: hi sets top bit on (ptr - 0x20). */
cl4_pair_t FUN_00464468(word_t p)
{
    return (cl4_pair_t){ .lo = 0xd000000000000014, .hi = (p - 0x20) | 0x8000000000000000 };
}

/* FUN_00464480 @ 0x00464480   (est. sk_tagged_ptr_64480)
 * Ghidra: undefined1 [16] FUN_00464480(long param_1)
 * Returns a tagged-pointer pair: lo = 0xd0...18, hi = (param_1 - 0x20) with the
 * high bit set.
 * Confidence: medium
 * Notes: hi sets top bit on (ptr - 0x20). */
cl4_pair_t FUN_00464480(word_t p)
{
    return (cl4_pair_t){ .lo = 0xd000000000000018, .hi = (p - 0x20) | 0x8000000000000000 };
}

/* FUN_00464498 @ 0x00464498   (est. sk_nop_64498)
 * Ghidra: void FUN_00464498(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_00464498(void)
{
    return;
}

/* FUN_004644ac @ 0x004644ac   (est. sk_nop_644ac)
 * Ghidra: void FUN_004644ac(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_004644ac(void)
{
    return;
}

/* FUN_004644c0 @ 0x004644c0   (est. sk_stack_ptr_644c0)
 * Ghidra: undefined1 * FUN_004644c0(void)
 * Returns a pointer into the caller's stack frame (a deep local slot). Register
 * fragment; the pointer is a stack address.
 * Confidence: low
 * Notes: returns &stack0x00001310 (dead stack reference). */
uint8_t *FUN_004644c0(void)
{
    uint8_t local[0x1310];
    return local;
}

/* FUN_004644cc @ 0x004644cc   (est. sk_nop_644cc)
 * Ghidra: void FUN_004644cc(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_004644cc(void)
{
    return;
}

/* FUN_004644dc @ 0x004644dc   (est. sk_nop_644dc)
 * Ghidra: void FUN_004644dc(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_004644dc(void)
{
    return;
}

/* FUN_004644e8 @ 0x004644e8   (est. sk_call_644e8)
 * Ghidra: void FUN_004644e8(void)
 * Calls FUN_001a84f4 with the address of a local buffer and the constant 0.
 * Confidence: low
 * Notes: buffer + 0 args. */
void FUN_004644e8(void)
{
    uint8_t buf[8];
    FUN_001a84f4(buf, 0);
}

/* FUN_004644f8 @ 0x004644f8   (est. sk_nop_644f8)
 * Ghidra: void FUN_004644f8(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_004644f8(void)
{
    return;
}

/* FUN_00464504 @ 0x00464504   (est. sk_copy_word_64504)
 * Ghidra: void FUN_00464504(void)
 * Register fragment: copies the word at +0x20 of the source struct (x19) into
 * the same offset of the destination (x20).
 * Confidence: low
 * Notes: register fragment (unaff x19, x20). */
void FUN_00464504(word_t dst, word_t src)
{
    *(word_t *)(dst + 0x20) = *(word_t *)(src + 0x20);
}

/* FUN_00464510 @ 0x00464510   (est. sk_pair_64510)
 * Ghidra: undefined1 [16] FUN_00464510(long param_1)
 * Returns a 16-byte pair: lo = param_1 + 0x10, hi = (callee-saved x26) + 0x10.
 * Also stores param_1 into a stack local (dead store). Pair of offset
 * pointers, likely capability/pointer arithmetic.
 * Confidence: low
 * Notes: register fragment (unaff x26); stores param_1 to stack first. */
cl4_pair_t FUN_00464510(word_t p, word_t q)
{
    return (cl4_pair_t){ .lo = p + 0x10, .hi = q + 0x10 };
}

/* FUN_00464520 @ 0x00464520   (est. sk_call_64520)
 * Ghidra: void FUN_00464520(void)
 * Initializes a two-word local pair {0, 0xe0...} and calls FUN_002a4ab4 with
 * selector 0x1d (a lock/report helper).
 * Confidence: low
 * Notes: local pair init {0, 0xe0...}; helper selector 0x1d. */
void FUN_00464520(void)
{
    word_t pair[2] = { 0, 0xe000000000000000 };
    FUN_002a4ab4(0x1d);
}

/* FUN_00464538 @ 0x00464538   (est. sk_call_64538)
 * Ghidra: void FUN_00464538(void)
 * Initializes a two-word local pair {0, 0xe0...} and calls FUN_002a4ab4 with
 * selector 0x1d. Identical to FUN_00464520.
 * Confidence: low
 * Notes: local pair init {0, 0xe0...}; helper selector 0x1d. */
void FUN_00464538(void)
{
    word_t pair[2] = { 0, 0xe000000000000000 };
    FUN_002a4ab4(0x1d);
}

/* FUN_00464550 @ 0x00464550   (est. sk_call_64550)
 * Ghidra: void FUN_00464550(void)
 * Initializes two local words {0, 0xe0...} plus a third zero, then calls
 * thunk_FUN_0036b270 (refcount acquire). The local state is set up for the
 * helper but not otherwise consumed here.
 * Confidence: low
 * Notes: locals {0, 0xe0...} + 0; refcount acquire call. */
void FUN_00464550(void)
{
    word_t a[2] = { 0, 0xe000000000000000 };
    word_t b = 0;
    thunk_FUN_0036b270();
}

/* FUN_00464568 @ 0x00464568   (est. sk_store_record_64568)
 * Ghidra: void FUN_00464568(undefined1 param_1 [16],undefined1 param_2 [16])
 * Register fragment: writes a 16-byte value (param_2) into the destination held
 * in x10 at offsets +0x38/+0x40, plus a 16-bit field at +0x25 and a 32-bit
 * field at +0x21 supplied from registers w8/w9. Reconstructed with the
 * register-supplied values folded in as parameters.
 * Confidence: low
 * Notes: register fragment (unaff w8, w9, x10). */
void FUN_00464568(word_t dst, uint16_t w8, uint32_t w9, word_t lo, word_t hi)
{
    *(uint16_t *)(dst + 0x25) = w8;
    *(uint32_t *)(dst + 0x21) = w9;
    *(word_t *)(dst + 0x40) = hi;
    *(word_t *)(dst + 0x38) = lo;
}

/* FUN_00464578 @ 0x00464578   (est. sk_pair_stack_64578)
 * Ghidra: undefined1 [16] FUN_00464578(void)
 * Returns a 16-byte pair: lo = address of a stack local, hi = (value & 0x0fff...f)
 * + 0x10 from callee-saved x27. Pairs a stack pointer with a masked value.
 * Confidence: low
 * Notes: register fragment (unaff x27); lo = stack ptr. */
cl4_pair_t FUN_00464578(word_t v)
{
    uint8_t buf[0x140];
    return (cl4_pair_t){ .lo = (word_t)(uintptr_t)buf, .hi = (v & 0xfffffffffffffff) + 0x10 };
}

/* FUN_00464588 @ 0x00464588   (est. sk_nop_64588)
 * Ghidra: void FUN_00464588(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_00464588(void)
{
    return;
}

/* FUN_00464594 @ 0x00464594   (est. sk_ascii_64594)
 * Ghidra: undefined8 FUN_00464594(void)
 * Returns the 6 ASCII bytes 0x636962617261, decoding to "arabic" (a script
 * name constant) packed into a single word.
 * Confidence: medium
 * Notes: decoded "arabic". */
word_t FUN_00464594(void)
{
    return 0x636962617261;
}

/* FUN_004645a4 @ 0x004645a4   (est. sk_call_645a4)
 * Ghidra: void FUN_004645a4(void)
 * Calls FUN_00117cc4 (memcpy-like) with the address of a local buffer.
 * Confidence: low
 * Notes: single buffer arg. */
void FUN_004645a4(void)
{
    uint8_t buf[0x100];
    FUN_00117cc4(buf);
}

/* FUN_004645b4 @ 0x004645b4   (est. sk_nop_645b4)
 * Ghidra: void FUN_004645b4(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_004645b4(void)
{
    return;
}

/* FUN_004645c4 @ 0x004645c4   (est. sk_nop_645c4)
 * Ghidra: void FUN_004645c4(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_004645c4(void)
{
    return;
}

/* FUN_004645d8 @ 0x004645d8   (est. sk_copy_fields_645d8)
 * Ghidra: void FUN_004645d8(void)
 * Register fragment: copies the words at +0x38/+0x40 and the byte at +0x48 of
 * the source struct (x19) into the same offsets of the destination (x20).
 * Confidence: low
 * Notes: register fragment (unaff x19, x20). */
void FUN_004645d8(word_t dst, word_t src)
{
    word_t v1;
    v1 = *(word_t *)(src + 0x40);
    *(word_t *)(dst + 0x40) = *(word_t *)(src + 0x40);
    *(word_t *)(dst + 0x38) = *(word_t *)(src + 0x38);
    *(uint8_t *)(dst + 0x48) = *(uint8_t *)(src + 0x48);
}

/* FUN_004645ec @ 0x004645ec   (est. sk_set_flag_645ec)
 * Ghidra: void FUN_004645ec(void)
 * Register fragment: sets the byte at +0x38 of the object held in x19 to 1.
 * Confidence: low
 * Notes: register fragment (unaff x19). */
void FUN_004645ec(word_t obj)
{
    *(uint8_t *)(obj + 0x38) = 1;
}

/* FUN_004645f8 @ 0x004645f8   (est. sk_report_645f8)
 * Ghidra: void FUN_004645f8(void)
 * Emits a report/trace record: calls thunk_FUN_002acbb8 (report emit) with a
 * selector 0x2f2a20 and a type tag word 0xe3... .
 * Confidence: low
 * Notes: report emit call with (0x2f2a20, 0xe3...). */
void FUN_004645f8(void)
{
    thunk_FUN_002acbb8(0x2f2a20, 0xe300000000000000);
}

/* FUN_00464608 @ 0x00464608   (est. sk_nop_64608)
 * Ghidra: void FUN_00464608(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_00464608(void)
{
    return;
}

/* FUN_0046461c @ 0x0046461c   (est. sk_nop_6461c)
 * Ghidra: void FUN_0046461c(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_0046461c(void)
{
    return;
}

/* FUN_00464630 @ 0x00464630   (est. sk_call_64630)
 * Ghidra: void FUN_00464630(void)
 * Calls FUN_00117cc4 (memcpy-like) with the address of a local buffer.
 * Confidence: low
 * Notes: single buffer arg. */
void FUN_00464630(void)
{
    uint8_t buf[0x28];
    FUN_00117cc4(buf);
}

/* FUN_00464640 @ 0x00464640   (est. sk_pair_store_64640)
 * Ghidra: undefined1 [16] FUN_00464640(long param_1)
 * Stores param_1 into the first word of the object held in x19, then returns
 * the pair { lo = param_1 + 0x10, hi = (x20) + 0x10 }.
 * Confidence: low
 * Notes: register fragment (unaff x19, x20). */
cl4_pair_t FUN_00464640(word_t dst, word_t p, word_t q)
{
    *(word_t *)dst = p;
    return (cl4_pair_t){ .lo = p + 0x10, .hi = q + 0x10 };
}

/* FUN_00464650 @ 0x00464650   (est. sk_pair_stack_64650)
 * Ghidra: undefined1 [16] FUN_00464650(ulong param_1)
 * Returns a 16-byte pair: lo = address of a stack local, hi = (param_1 & 0x0fff...f)
 * + 0x10.
 * Confidence: low
 * Notes: lo = stack ptr. */
cl4_pair_t FUN_00464650(word_t v)
{
    uint8_t buf[0xc8];
    return (cl4_pair_t){ .lo = (word_t)(uintptr_t)buf, .hi = (v & 0xfffffffffffffff) + 0x10 };
}

/* FUN_00464660 @ 0x00464660   (est. sk_script_name_64660)
 * Ghidra: undefined1 [16] FUN_00464660(void)
 * Returns a name descriptor for the script "Hanifi Rohingya": lo carries 8
 * ASCII bytes, hi carries the tail plus tag 0xee.
 * Confidence: medium
 * Notes: decoded "hanifirohingya", hi tag 0xee. */
cl4_pair_t FUN_00464660(void)
{
    return (cl4_pair_t){ .lo = 0x6f726966696e6168, .hi = 0xee006179676e6968 };
}

/* FUN_00464688 @ 0x00464688   (est. sk_encode_64688)
 * Ghidra: ulong FUN_00464688(ulong param_1)
 * Masks the argument to its low 32 bits and ORs in the constant tag
 * 0x63696100000000, producing a tagged value (16-bit type + low address).
 * Confidence: medium
 * Notes: tag/address packing. */
word_t FUN_00464688(word_t v)
{
    return (v & 0xffffffff) | 0x63696100000000;
}

/* FUN_00464694 @ 0x00464694   (est. sk_script_name_64694)
 * Ghidra: undefined1 [16] FUN_00464694(void)
 * Returns a name descriptor for the script "Bopomofo": lo carries 8 ASCII
 * bytes, hi carries tag 0xe8.
 * Confidence: medium
 * Notes: decoded "Bopomofo", hi tag 0xe8. */
cl4_pair_t FUN_00464694(void)
{
    return (cl4_pair_t){ .lo = 0x6f666f6d6f706f42, .hi = 0xe800000000000000 };
}

/* FUN_004646ac @ 0x004646ac   (est. sk_script_name_646ac)
 * Ghidra: undefined1 [16] FUN_004646ac(void)
 * Returns a name descriptor for the script "Gurmukhi": lo carries 8 ASCII
 * bytes, hi carries tag 0xe8.
 * Confidence: medium
 * Notes: decoded "Gurmukhi", hi tag 0xe8. */
cl4_pair_t FUN_004646ac(void)
{
    return (cl4_pair_t){ .lo = 0x69686b756d727547, .hi = 0xe800000000000000 };
}

/* FUN_004646c4 @ 0x004646c4   (est. sk_script_name_646c4)
 * Ghidra: undefined1 [16] FUN_004646c4(void)
 * Returns a name descriptor for the script "Gujarati": lo carries 8 ASCII
 * bytes, hi carries tag 0xe8.
 * Confidence: medium
 * Notes: decoded "Gujarati", hi tag 0xe8. */
cl4_pair_t FUN_004646c4(void)
{
    return (cl4_pair_t){ .lo = 0x69746172616a7547, .hi = 0xe800000000000000 };
}

/* FUN_004646dc @ 0x004646dc   (est. sk_script_name_646dc)
 * Ghidra: undefined1 [16] FUN_004646dc(void)
 * Returns a name descriptor for the script "Cherokee": lo carries 8 ASCII
 * bytes, hi carries tag 0xe8.
 * Confidence: medium
 * Notes: decoded "Cherokee", hi tag 0xe8. */
cl4_pair_t FUN_004646dc(void)
{
    return (cl4_pair_t){ .lo = 0x65656b6f72656843, .hi = 0xe800000000000000 };
}

/* FUN_004646f4 @ 0x004646f4   (est. sk_script_name_646f4)
 * Ghidra: undefined1 [16] FUN_004646f4(void)
 * Returns a name descriptor for the script "Ol_Chiki": lo carries 8 ASCII
 * bytes, hi carries tag 0xe8.
 * Confidence: medium
 * Notes: decoded "Ol_Chiki", hi tag 0xe8. */
cl4_pair_t FUN_004646f4(void)
{
    return (cl4_pair_t){ .lo = 0x696b6968435f6c4f, .hi = 0xe800000000000000 };
}

/* FUN_0046470c @ 0x0046470c   (est. sk_script_name_6470c)
 * Ghidra: undefined1 [16] FUN_0046470c(void)
 * Returns a name descriptor for the script "Linear_A": lo carries 8 ASCII
 * bytes, hi carries tag 0xe8.
 * Confidence: medium
 * Notes: decoded "Linear_A", hi tag 0xe8. */
cl4_pair_t FUN_0046470c(void)
{
    return (cl4_pair_t){ .lo = 0x415f7261656e694c, .hi = 0xe800000000000000 };
}

/* FUN_00464724 @ 0x00464724   (est. sk_script_name_64724)
 * Ghidra: undefined1 [16] FUN_00464724(void)
 * Returns a name descriptor for the script "Tagbanwa": lo carries 8 ASCII
 * bytes, hi carries tag 0xe8.
 * Confidence: medium
 * Notes: decoded "Tagbanwa", hi tag 0xe8. */
cl4_pair_t FUN_00464724(void)
{
    return (cl4_pair_t){ .lo = 0x61776e6162676154, .hi = 0xe800000000000000 };
}

/* FUN_0046473c @ 0x0046473c   (est. sk_script_name_6473c)
 * Ghidra: undefined1 [16] FUN_0046473c(void)
 * Returns a name descriptor for the script "Tai_Viet": lo carries 8 ASCII
 * bytes, hi carries tag 0xe8.
 * Confidence: medium
 * Notes: decoded "Tai_Viet", hi tag 0xe8. */
cl4_pair_t FUN_0046473c(void)
{
    return (cl4_pair_t){ .lo = 0x746569565f696154, .hi = 0xe800000000000000 };
}

/* FUN_00464754 @ 0x00464754   (est. sk_script_name_64754)
 * Ghidra: undefined1 [16] FUN_00464754(void)
 * Returns a name descriptor for the script "Tai_Tham": lo carries 8 ASCII
 * bytes, hi carries tag 0xe8.
 * Confidence: medium
 * Notes: decoded "Tai_Tham", hi tag 0xe8. */
cl4_pair_t FUN_00464754(void)
{
    return (cl4_pair_t){ .lo = 0x6d6168545f696154, .hi = 0xe800000000000000 };
}

/* FUN_0046476c @ 0x0046476c   (est. sk_script_name_6476c)
 * Ghidra: undefined1 [16] FUN_0046476c(void)
 * Returns a name descriptor for the script "Kayah_Li": lo carries 8 ASCII
 * bytes, hi carries tag 0xe8.
 * Confidence: medium
 * Notes: decoded "Kayah_Li", hi tag 0xe8. */
cl4_pair_t FUN_0046476c(void)
{
    return (cl4_pair_t){ .lo = 0x694c5f686179614b, .hi = 0xe800000000000000 };
}

/* FUN_00464784 @ 0x00464784   (est. sk_script_name_64784)
 * Ghidra: undefined1 [16] FUN_00464784(void)
 * Returns a name descriptor for the script "Mahajani": lo carries 8 ASCII
 * bytes, hi carries tag 0xe8.
 * Confidence: medium
 * Notes: decoded "Mahajani", hi tag 0xe8. */
cl4_pair_t FUN_00464784(void)
{
    return (cl4_pair_t){ .lo = 0x696e616a6168614d, .hi = 0xe800000000000000 };
}

/* FUN_0046479c @ 0x0046479c   (est. sk_script_name_6479c)
 * Ghidra: undefined1 [16] FUN_0046479c(void)
 * Returns a name descriptor for the script "Vithkuqi": lo carries 8 ASCII
 * bytes, hi carries tag 0xe8.
 * Confidence: medium
 * Notes: decoded "Vithkuqi", hi tag 0xe8. */
cl4_pair_t FUN_0046479c(void)
{
    return (cl4_pair_t){ .lo = 0x6971756b68746956, .hi = 0xe800000000000000 };
}

/* FUN_004647b4 @ 0x004647b4   (est. sk_shift_647b4)
 * Ghidra: ulong FUN_004647b4(ulong param_1)
 * Returns the argument shifted right by 14 bits (a field extract / coarse
 * page-table index step).
 * Confidence: medium
 * Notes: arithmetic right shift by 14. */
word_t FUN_004647b4(word_t v)
{
    return v >> 0xe;
}

/* FUN_004647c0 @ 0x004647c0   (est. sk_nop_647c0)
 * Ghidra: void FUN_004647c0(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_004647c0(void)
{
    return;
}

/* FUN_004647d4 @ 0x004647d4   (est. sk_nop_647d4)
 * Ghidra: void FUN_004647d4(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_004647d4(void)
{
    return;
}

/* FUN_004647e4 @ 0x004647e4   (est. sk_pair_stack_647e4)
 * Ghidra: undefined1 [16] FUN_004647e4(undefined8 param_1,ulong param_2)
 * Returns a 16-byte pair: lo = address of a stack local, hi = (param_2 & 0x0fff...f)
 * + 0x10. First argument is unused.
 * Confidence: low
 * Notes: lo = stack ptr; param_1 unused. */
cl4_pair_t FUN_004647e4(word_t unused, word_t v)
{
    uint8_t buf[0xd0];
    return (cl4_pair_t){ .lo = (word_t)(uintptr_t)buf, .hi = (v & 0xfffffffffffffff) + 0x10 };
}

/* FUN_004647f4 @ 0x004647f4   (est. sk_call_647f4)
 * Ghidra: void FUN_004647f4(long param_1)
 * Calls FUN_00117cc4 (memcpy-like) with destination = param_1 + 0x20, a local
 * buffer as source, and length 0x49.
 * Confidence: low
 * Notes: 3-arg memcpy call (dst+0x20, local, 0x49). */
void FUN_004647f4(word_t dst)
{
    uint8_t buf[0x58];
    FUN_00117cc4((void *)(dst + 0x20), buf, 0x49);
}

/* FUN_00464804 @ 0x00464804   (est. sk_nop_64804)
 * Ghidra: void FUN_00464804(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_00464804(void)
{
    return;
}

/* FUN_00464818 @ 0x00464818   (est. sk_nop_64818)
 * Ghidra: void FUN_00464818(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_00464818(void)
{
    return;
}

/* FUN_0046482c @ 0x0046482c   (est. sk_pair_stack_6482c)
 * Ghidra: undefined1 [16] FUN_0046482c(void)
 * Returns a 16-byte pair: lo = address of a stack local, hi = (x19 & 0x0fff...f)
 * + 0x10 from callee-saved x19.
 * Confidence: low
 * Notes: register fragment (unaff x19); lo = stack ptr. */
cl4_pair_t FUN_0046482c(word_t v)
{
    uint8_t buf[0x1b0];
    return (cl4_pair_t){ .lo = (word_t)(uintptr_t)buf, .hi = (v & 0xfffffffffffffff) + 0x10 };
}

/* FUN_00464854 @ 0x00464854   (est. sk_tagged_ptr_64854)
 * Ghidra: undefined1 [16] FUN_00464854(void)
 * Returns a tagged pair: lo = 0xd0...13, hi = (x28) | 0x8000... from
 * callee-saved x28. Constructs a capability word with top bit set.
 * Confidence: low
 * Notes: register fragment (unaff x28). */
cl4_pair_t FUN_00464854(word_t v)
{
    return (cl4_pair_t){ .lo = 0xd000000000000013, .hi = v | 0x8000000000000000 };
}

/* FUN_00464864 @ 0x00464864   (est. sk_nop_64864)
 * Ghidra: void FUN_00464864(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_00464864(void)
{
    return;
}

/* FUN_00464874 @ 0x00464874   (est. sk_nop_64874)
 * Ghidra: void FUN_00464874(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_00464874(void)
{
    return;
}

/* FUN_00464880 @ 0x00464880   (est. sk_pair_stack_64880)
 * Ghidra: undefined1 [16] FUN_00464880(ulong param_1)
 * Returns a 16-byte pair: lo = address of a stack local, hi = (param_1 & 0x0fff...f)
 * + 0x10.
 * Confidence: low
 * Notes: lo = stack ptr. */
cl4_pair_t FUN_00464880(word_t v)
{
    uint8_t buf[0xe0];
    return (cl4_pair_t){ .lo = (word_t)(uintptr_t)buf, .hi = (v & 0xfffffffffffffff) + 0x10 };
}

/* FUN_00464890 @ 0x00464890   (est. sk_call_64890)
 * Ghidra: void FUN_00464890(void)
 * Calls FUN_00117cc4 (memcpy-like) with the address of a local buffer.
 * Confidence: low
 * Notes: single buffer arg. */
void FUN_00464890(void)
{
    uint8_t buf[0x160];
    FUN_00117cc4(buf);
}

/* FUN_004648a0 @ 0x004648a0   (est. sk_nop_648a0)
 * Ghidra: void FUN_004648a0(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_004648a0(void)
{
    return;
}

/* FUN_004648b0 @ 0x004648b0   (est. sk_store_record_648b0)
 * Ghidra: void FUN_004648b0(long param_1)
 * Register fragment: writes three fields into the object at param_1: two words
 * (stack-passed) at +0x10 and +0x18, and a 32-bit value (from w22) at +0x20.
 * Confidence: low
 * Notes: register fragment (unaff w22); two stack args folded in. */
void FUN_004648b0(word_t dst, word_t a, word_t b, uint32_t w)
{
    *(word_t *)(dst + 0x18) = b;
    *(word_t *)(dst + 0x10) = a;
    *(uint32_t *)(dst + 0x20) = w;
}

/* FUN_004648c4 @ 0x004648c4   (est. sk_script_name_648c4)
 * Ghidra: undefined1 [16] FUN_004648c4(void)
 * Returns a name descriptor for the script "Imperial Aramaic": lo carries 8
 * ASCII bytes, hi carries the tail plus tag 0xef.
 * Confidence: medium
 * Notes: decoded "imperialaramaic", hi tag 0xef. */
cl4_pair_t FUN_004648c4(void)
{
    return (cl4_pair_t){ .lo = 0x6c61697265706d69, .hi = 0xef6369616d617261 };
}

/* FUN_004648ec @ 0x004648ec   (est. sk_nop_648ec)
 * Ghidra: void FUN_004648ec(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_004648ec(void)
{
    return;
}

/* FUN_004648fc @ 0x004648fc   (est. sk_call_648fc)
 * Ghidra: void FUN_004648fc(void)
 * Calls FUN_001a84f4 with the address of a local buffer and the constant 0.
 * Confidence: low
 * Notes: buffer + 0 args. */
void FUN_004648fc(void)
{
    uint8_t buf[8];
    FUN_001a84f4(buf, 0);
}

/* FUN_0046490c @ 0x0046490c   (est. sk_nop_6490c)
 * Ghidra: void FUN_0046490c(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_0046490c(void)
{
    return;
}

/* FUN_00464918 @ 0x00464918   (est. sk_call_64918)
 * Ghidra: void FUN_00464918(void)
 * Tail-calls the helper FUN_00461894 and returns.
 * Confidence: low
 * Notes: single call, no args visible to the decompiler. */
void FUN_00464918(void)
{
    FUN_00461894();
}

/* FUN_00464930 @ 0x00464930   (est. sk_nop_64930)
 * Ghidra: void FUN_00464930(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_00464930(void)
{
    return;
}
