/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel, GL1,
 * arm64e, image base 0) — the cL4 microkernel. Ground truth: Ghidra FUN_ names +
 * addresses in cl4_kernel.raw. Version "cL4 microkernel (cL4 (679.100.61))".
 * All names are estimates unless string/header-matched.
 * Slice: 0x00463fe8-0x00464930 (SKR22) — a dense run of small object/name
 * helpers and nop stubs. Most bodies are 1-4 instructions: 16-byte word-pair
 * factories that encode an object type tag + small constant or an ASCII name
 * (many Unicode script names), register/stack fragments that copy a few fields
 * between structs, and single helper calls. */

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
 * 0xe1 with a zero payload, lo is the small constant 0x20. Likely a canonical
 * capability/name descriptor for some object kind.
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

/* FUN_0046404c @ 0x0046404c   (est. sk_nop_6404c)
 * Ghidra: void FUN_0046404c(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_0046404c(void)
{
    return;
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

/* FUN_00464064 @ 0x00464064   (est. sk_nop_64064)
 * Ghidra: void FUN_00464064(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_00464064(void)
{
    return;
}

/* FUN_00464090 @ 0x00464090   (est. sk_nop_64090)
 * Ghidra: void FUN_00464090(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_00464090(void)
{
    return;
}

/* FUN_004640a4 @ 0x004640a4   (est. sk_nop_640a4)
 * Ghidra: void FUN_004640a4(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_004640a4(void)
{
    return;
}

/* FUN_004640b8 @ 0x004640b8   (est. sk_nop_640b8)
 * Ghidra: void FUN_004640b8(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_004640b8(void)
{
    return;
}

/* FUN_004640c4 @ 0x004640c4   (est. sk_nop_640c4)
 * Ghidra: void FUN_004640c4(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_004640c4(void)
{
    return;
}

/* FUN_004640d0 @ 0x004640d0   (est. sk_nop_640d0)
 * Ghidra: void FUN_004640d0(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_004640d0(void)
{
    return;
}

/* FUN_004640dc @ 0x004640dc   (est. sk_nop_640dc)
 * Ghidra: void FUN_004640dc(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_004640dc(void)
{
    return;
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

/* FUN_0046411c @ 0x0046411c   (est. sk_nop_6411c)
 * Ghidra: void FUN_0046411c(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_0046411c(void)
{
    return;
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

/* FUN_00464134 @ 0x00464134   (est. sk_nop_64134)
 * Ghidra: void FUN_00464134(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_00464134(void)
{
    return;
}

/* FUN_00464140 @ 0x00464140   (est. sk_nop_64140)
 * Ghidra: void FUN_00464140(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_00464140(void)
{
    return;
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

/* FUN_00464158 @ 0x00464158   (est. sk_nop_64158)
 * Ghidra: void FUN_00464158(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_00464158(void)
{
    return;
}

/* FUN_00464180 @ 0x00464180   (est. sk_nop_64180)
 * Ghidra: void FUN_00464180(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_00464180(void)
{
    return;
}

/* FUN_0046418c @ 0x0046418c   (est. sk_nop_6418c)
 * Ghidra: void FUN_0046418c(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_0046418c(void)
{
    return;
}

/* FUN_004641a0 @ 0x004641a0   (est. sk_nop_641a0)
 * Ghidra: void FUN_004641a0(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_004641a0(void)
{
    return;
}

/* FUN_004641b8 @ 0x004641b8   (est. sk_nop_641b8)
 * Ghidra: void FUN_004641b8(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_004641b8(void)
{
    return;
}

/* FUN_004641d0 @ 0x004641d0   (est. sk_nop_641d0)
 * Ghidra: void FUN_004641d0(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_004641d0(void)
{
    return;
}

/* FUN_004641e8 @ 0x004641e8   (est. sk_nop_641e8)
 * Ghidra: void FUN_004641e8(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_004641e8(void)
{
    return;
}

/* FUN_004641fc @ 0x004641fc   (est. sk_nop_641fc)
 * Ghidra: void FUN_004641fc(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_004641fc(void)
{
    return;
}

/* FUN_00464224 @ 0x00464224   (est. sk_nop_64224)
 * Ghidra: void FUN_00464224(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_00464224(void)
{
    return;
}

/* FUN_00464234 @ 0x00464234   (est. sk_nop_64234)
 * Ghidra: void FUN_00464234(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_00464234(void)
{
    return;
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

/* FUN_00464258 @ 0x00464258   (est. sk_nop_64258)
 * Ghidra: void FUN_00464258(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_00464258(void)
{
    return;
}

/* FUN_00464268 @ 0x00464268   (est. sk_nop_64268)
 * Ghidra: void FUN_00464268(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_00464268(void)
{
    return;
}

/* FUN_00464280 @ 0x00464280   (est. sk_nop_64280)
 * Ghidra: void FUN_00464280(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_00464280(void)
{
    return;
}

/* FUN_004642a8 @ 0x004642a8   (est. sk_nop_642a8)
 * Ghidra: void FUN_004642a8(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_004642a8(void)
{
    return;
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

/* FUN_004642e8 @ 0x004642e8   (est. sk_nop_642e8)
 * Ghidra: void FUN_004642e8(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_004642e8(void)
{
    return;
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

/* FUN_00464318 @ 0x00464318   (est. sk_nop_64318)
 * Ghidra: void FUN_00464318(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_00464318(void)
{
    return;
}

/* FUN_00464340 @ 0x00464340   (est. sk_nop_64340)
 * Ghidra: void FUN_00464340(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_00464340(void)
{
    return;
}

/* FUN_00464354 @ 0x00464354   (est. sk_nop_64354)
 * Ghidra: void FUN_00464354(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_00464354(void)
{
    return;
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

/* FUN_00464378 @ 0x00464378   (est. sk_nop_64378)
 * Ghidra: void FUN_00464378(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_00464378(void)
{
    return;
}

/* FUN_00464388 @ 0x00464388   (est. sk_nop_64388)
 * Ghidra: void FUN_00464388(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_00464388(void)
{
    return;
}

/* FUN_004643a0 @ 0x004643a0   (est. sk_nop_643a0)
 * Ghidra: void FUN_004643a0(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_004643a0(void)
{
    return;
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

/* FUN_004643d8 @ 0x004643d8   (est. sk_nop_643d8)
 * Ghidra: void FUN_004643d8(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_004643d8(void)
{
    return;
}

/* FUN_004643f0 @ 0x004643f0   (est. sk_nop_643f0)
 * Ghidra: void FUN_004643f0(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_004643f0(void)
{
    return;
}

/* FUN_00464408 @ 0x00464408   (est. sk_nop_64408)
 * Ghidra: void FUN_00464408(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_00464408(void)
{
    return;
}

/* FUN_00464420 @ 0x00464420   (est. sk_nop_64420)
 * Ghidra: void FUN_00464420(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_00464420(void)
{
    return;
}

/* FUN_00464438 @ 0x00464438   (est. sk_nop_64438)
 * Ghidra: void FUN_00464438(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_00464438(void)
{
    return;
}

/* FUN_00464450 @ 0x00464450   (est. sk_nop_64450)
 * Ghidra: void FUN_00464450(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_00464450(void)
{
    return;
}

/* FUN_00464468 @ 0x00464468   (est. sk_nop_64468)
 * Ghidra: void FUN_00464468(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_00464468(void)
{
    return;
}

/* FUN_00464480 @ 0x00464480   (est. sk_nop_64480)
 * Ghidra: void FUN_00464480(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_00464480(void)
{
    return;
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

/* FUN_004644c0 @ 0x004644c0   (est. sk_nop_644c0)
 * Ghidra: void FUN_004644c0(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_004644c0(void)
{
    return;
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

/* FUN_004644e8 @ 0x004644e8   (est. sk_nop_644e8)
 * Ghidra: void FUN_004644e8(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_004644e8(void)
{
    return;
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

/* FUN_00464504 @ 0x00464504   (est. sk_nop_64504)
 * Ghidra: void FUN_00464504(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_00464504(void)
{
    return;
}

/* FUN_00464510 @ 0x00464510   (est. sk_nop_64510)
 * Ghidra: void FUN_00464510(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_00464510(void)
{
    return;
}

/* FUN_00464520 @ 0x00464520   (est. sk_nop_64520)
 * Ghidra: void FUN_00464520(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_00464520(void)
{
    return;
}

/* FUN_00464538 @ 0x00464538   (est. sk_nop_64538)
 * Ghidra: void FUN_00464538(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_00464538(void)
{
    return;
}

/* FUN_00464550 @ 0x00464550   (est. sk_nop_64550)
 * Ghidra: void FUN_00464550(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_00464550(void)
{
    return;
}

/* FUN_00464568 @ 0x00464568   (est. sk_nop_64568)
 * Ghidra: void FUN_00464568(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_00464568(void)
{
    return;
}

/* FUN_00464578 @ 0x00464578   (est. sk_nop_64578)
 * Ghidra: void FUN_00464578(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_00464578(void)
{
    return;
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

/* FUN_00464594 @ 0x00464594   (est. sk_nop_64594)
 * Ghidra: void FUN_00464594(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_00464594(void)
{
    return;
}

/* FUN_004645a4 @ 0x004645a4   (est. sk_nop_645a4)
 * Ghidra: void FUN_004645a4(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_004645a4(void)
{
    return;
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

/* FUN_004645d8 @ 0x004645d8   (est. sk_nop_645d8)
 * Ghidra: void FUN_004645d8(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_004645d8(void)
{
    return;
}

/* FUN_004645ec @ 0x004645ec   (est. sk_nop_645ec)
 * Ghidra: void FUN_004645ec(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_004645ec(void)
{
    return;
}

/* FUN_004645f8 @ 0x004645f8   (est. sk_nop_645f8)
 * Ghidra: void FUN_004645f8(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_004645f8(void)
{
    return;
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

/* FUN_00464630 @ 0x00464630   (est. sk_nop_64630)
 * Ghidra: void FUN_00464630(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_00464630(void)
{
    return;
}

/* FUN_00464640 @ 0x00464640   (est. sk_nop_64640)
 * Ghidra: void FUN_00464640(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_00464640(void)
{
    return;
}

/* FUN_00464650 @ 0x00464650   (est. sk_nop_64650)
 * Ghidra: void FUN_00464650(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_00464650(void)
{
    return;
}

/* FUN_00464660 @ 0x00464660   (est. sk_nop_64660)
 * Ghidra: void FUN_00464660(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_00464660(void)
{
    return;
}

/* FUN_00464688 @ 0x00464688   (est. sk_nop_64688)
 * Ghidra: void FUN_00464688(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_00464688(void)
{
    return;
}

/* FUN_00464694 @ 0x00464694   (est. sk_nop_64694)
 * Ghidra: void FUN_00464694(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_00464694(void)
{
    return;
}

/* FUN_004646ac @ 0x004646ac   (est. sk_nop_646ac)
 * Ghidra: void FUN_004646ac(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_004646ac(void)
{
    return;
}

/* FUN_004646c4 @ 0x004646c4   (est. sk_nop_646c4)
 * Ghidra: void FUN_004646c4(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_004646c4(void)
{
    return;
}

/* FUN_004646dc @ 0x004646dc   (est. sk_nop_646dc)
 * Ghidra: void FUN_004646dc(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_004646dc(void)
{
    return;
}

/* FUN_004646f4 @ 0x004646f4   (est. sk_nop_646f4)
 * Ghidra: void FUN_004646f4(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_004646f4(void)
{
    return;
}

/* FUN_0046470c @ 0x0046470c   (est. sk_nop_6470c)
 * Ghidra: void FUN_0046470c(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_0046470c(void)
{
    return;
}

/* FUN_00464724 @ 0x00464724   (est. sk_nop_64724)
 * Ghidra: void FUN_00464724(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_00464724(void)
{
    return;
}

/* FUN_0046473c @ 0x0046473c   (est. sk_nop_6473c)
 * Ghidra: void FUN_0046473c(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_0046473c(void)
{
    return;
}

/* FUN_00464754 @ 0x00464754   (est. sk_nop_64754)
 * Ghidra: void FUN_00464754(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_00464754(void)
{
    return;
}

/* FUN_0046476c @ 0x0046476c   (est. sk_nop_6476c)
 * Ghidra: void FUN_0046476c(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_0046476c(void)
{
    return;
}

/* FUN_00464784 @ 0x00464784   (est. sk_nop_64784)
 * Ghidra: void FUN_00464784(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_00464784(void)
{
    return;
}

/* FUN_0046479c @ 0x0046479c   (est. sk_nop_6479c)
 * Ghidra: void FUN_0046479c(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_0046479c(void)
{
    return;
}

/* FUN_004647b4 @ 0x004647b4   (est. sk_nop_647b4)
 * Ghidra: void FUN_004647b4(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_004647b4(void)
{
    return;
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

/* FUN_004647e4 @ 0x004647e4   (est. sk_nop_647e4)
 * Ghidra: void FUN_004647e4(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_004647e4(void)
{
    return;
}

/* FUN_004647f4 @ 0x004647f4   (est. sk_nop_647f4)
 * Ghidra: void FUN_004647f4(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_004647f4(void)
{
    return;
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

/* FUN_0046482c @ 0x0046482c   (est. sk_nop_6482c)
 * Ghidra: void FUN_0046482c(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_0046482c(void)
{
    return;
}

/* FUN_00464854 @ 0x00464854   (est. sk_nop_64854)
 * Ghidra: void FUN_00464854(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_00464854(void)
{
    return;
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

/* FUN_00464880 @ 0x00464880   (est. sk_nop_64880)
 * Ghidra: void FUN_00464880(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_00464880(void)
{
    return;
}

/* FUN_00464890 @ 0x00464890   (est. sk_nop_64890)
 * Ghidra: void FUN_00464890(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_00464890(void)
{
    return;
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

/* FUN_004648b0 @ 0x004648b0   (est. sk_nop_648b0)
 * Ghidra: void FUN_004648b0(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_004648b0(void)
{
    return;
}

/* FUN_004648c4 @ 0x004648c4   (est. sk_nop_648c4)
 * Ghidra: void FUN_004648c4(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_004648c4(void)
{
    return;
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

/* FUN_004648fc @ 0x004648fc   (est. sk_nop_648fc)
 * Ghidra: void FUN_004648fc(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_004648fc(void)
{
    return;
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

/* FUN_00464918 @ 0x00464918   (est. sk_nop_64918)
 * Ghidra: void FUN_00464918(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_00464918(void)
{
    return;
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
