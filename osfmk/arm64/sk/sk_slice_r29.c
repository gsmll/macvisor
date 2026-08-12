/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel,
 * arm64e, image base 0) - the cL4 microkernel. Ground truth: Ghidra FUN_ names +
 * addresses in program cl4_kernel.raw. Version "cL4 microkernel (cL4
 * (679.100.61))". All names are estimates unless string/header-matched.
 *
 * This file covers wave batch SKR29, slice 0x00481600-0x0048fe4c: the Swift
 * Foundation/RegexBuilder _StringProcessing regular-expression engine. The
 * functions print (emit) RegexBuilder DSL snippets (character classes such as
 * \d \w \s, the horizontal/vertical-whitespace and newline-sequence
 * properties, anchors ^ $ \b, word boundaries, quantifiers {n}/{m,n}, capture
 * groups, alternation, and the many "TODO: ..." placeholders Swift's DSL
 * printer leaves for unsupported constructs), plus the AST->conversion and
 * pattern-emission helpers behind it. The 16-byte {lo,hi} returns carry a
 * tagged 8-byte value plus a small descriptor/tag in the low byte of hi
 * (seL4-style tagged word: low tag bits 0xe0/0xea etc. indicate the value
 * kind). Many helpers are entered with register-globals (unaff_x20/x19/x21 =
 * a self/context pointer carried in a callee-saved register); those are
 * transcribed as named parameters with a note.
 *
 * All out-of-range callees are declared as uniform 8-word-arg externs
 * (AAPCS64: args in x0..x7, result in x0). The 16-byte-return helpers use the
 * sk_r29_pair_t struct. Signatures are estimates; the FUN_ address is in each
 * comment.
 */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "sk_internal.h"

/* 16-byte (two-word) result used by the return-by-value helpers below. */
typedef struct sk_r29_pair { word_t lo, hi; } sk_r29_pair_t;

/* SoftwareBreakpoint(1, addr) - a trap/fault at the given binary address. */
#define SK_TRAP(a) __builtin_trap()

/* Empty-vector / sentinel data singletons referenced by this slice
 * (Ghidra DAT_ symbols). */
extern word_t sk_h_00657778;   /* DAT_00657778: empty vector singleton */
extern word_t sk_h_006577e0;   /* DAT_006577e0: empty sentinel */
extern word_t sk_h_006577d8;   /* DAT_006577d8 */
extern word_t sk_h_00657788;   /* DAT_00657788 */


/* ------------------------------------------------------------------ *
 * Out-of-range cL4/Swift-runtime helpers referenced by this slice.
 * Uniform AAPCS64 externs (args x0..x7, result x0). sk_r29_pair_t for the
 * 16-byte returns. FUN_ addresses in comments. Names are estimates.
 * ------------------------------------------------------------------ */

extern word_t sk_h_00002534(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00002534 */
extern word_t sk_h_000026e8(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_000026e8 */
extern word_t sk_h_00002818(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00002818 */
extern word_t sk_h_00002834(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00002834 */
extern word_t sk_h_00002874(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00002874 */
extern word_t sk_h_00019858(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00019858 */
extern word_t sk_h_0001da84(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_0001da84 */
extern word_t sk_h_0001e790(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_0001e790 */
extern word_t sk_h_00027724(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00027724 */
extern word_t sk_h_00041138(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00041138 */
extern word_t sk_h_00068e14(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00068e14 */
extern word_t sk_h_0006a374(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_0006a374 */
extern sk_r29_pair_t sk_h_0006ae9c(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_0006ae9c */
extern word_t sk_h_0006b3f4(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_0006b3f4 */
extern word_t sk_h_0006b42c(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_0006b42c */
extern word_t sk_h_0006b6f4(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_0006b6f4 */
extern word_t sk_h_0006f768(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_0006f768 */
extern word_t sk_h_00070594(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00070594 */
extern word_t sk_h_00072c0c(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00072c0c */
extern word_t sk_h_00073524(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00073524 */
extern word_t sk_h_0007767c(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_0007767c */
extern sk_r29_pair_t sk_h_00077698(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00077698 */
extern word_t sk_h_000776cc(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_000776cc */
extern word_t sk_h_00077888(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00077888 */
extern word_t sk_h_00077894(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00077894 */
extern word_t sk_h_0007c1c4(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_0007c1c4 */
extern word_t sk_h_0008409c(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_0008409c */
extern word_t sk_h_00084174(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00084174 */
extern word_t sk_h_00084180(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00084180 */
extern sk_r29_pair_t sk_h_00084220(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00084220 */
extern word_t sk_h_00084234(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00084234 */
extern word_t sk_h_00084cc4(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00084cc4 */
extern word_t sk_h_00085754(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00085754 */
extern word_t sk_h_000863bc(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_000863bc */
extern word_t sk_h_000867ec(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_000867ec */
extern word_t sk_h_00086840(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00086840 */
extern word_t sk_h_0008cc7c(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_0008cc7c */
extern word_t sk_h_0008e160(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_0008e160 */
extern word_t sk_h_0008e388(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_0008e388 */
extern word_t sk_h_0008e488(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_0008e488 */
extern word_t sk_h_0008e500(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_0008e500 */
extern sk_r29_pair_t sk_h_0008e518(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_0008e518 */
extern word_t sk_h_00092d40(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00092d40 */
extern word_t sk_h_0009461c(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_0009461c */
extern word_t sk_h_000a6e14(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_000a6e14 */
extern sk_r29_pair_t sk_h_000a6f68(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_000a6f68 */
extern word_t sk_h_000a6fe0(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_000a6fe0 */
extern word_t sk_h_000ac00c(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_000ac00c */
extern word_t sk_h_000af4d8(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_000af4d8 */
extern word_t sk_h_000b430c(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_000b430c */
extern word_t sk_h_000b4390(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_000b4390 */
extern word_t sk_h_000b43d0(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_000b43d0 */
extern word_t sk_h_000b43e8(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_000b43e8 */
extern word_t sk_h_000b4594(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_000b4594 */
extern word_t sk_h_000b45b0(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_000b45b0 */
extern word_t sk_h_000bd3a4(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_000bd3a4 */
extern word_t sk_h_000dbbe0(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_000dbbe0 */
extern word_t sk_h_000dbc98(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_000dbc98 */
extern word_t sk_h_000e0654(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_000e0654 */
extern word_t sk_h_000e15d8(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_000e15d8 */
extern word_t sk_h_000ec004(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_000ec004 */
extern word_t sk_h_000f4a9c(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_000f4a9c */
extern word_t sk_h_000f4ae8(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_000f4ae8 */
extern word_t sk_h_000f5d30(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_000f5d30 */
extern word_t sk_h_000f5e5c(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_000f5e5c */
extern word_t sk_h_00100e34(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00100e34 */
extern word_t sk_h_00100efc(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00100efc */
extern word_t sk_h_00106e3c(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00106e3c */
extern word_t sk_h_00117cc4(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00117cc4 */
extern word_t sk_h_0011aa70(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_0011aa70 */
extern word_t sk_h_0011e71c(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_0011e71c */
extern word_t sk_h_00136bf8(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00136bf8 */
extern word_t sk_h_00167404(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00167404 */
extern word_t sk_h_0016749c(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_0016749c */
extern word_t sk_h_001676cc(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_001676cc */
extern word_t sk_h_001a6a8c(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_001a6a8c */
extern word_t sk_h_001a84f4(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_001a84f4 */
extern word_t sk_h_001a8564(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_001a8564 */
extern word_t sk_h_001ae8a8(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_001ae8a8 */
extern word_t sk_h_001afa84(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_001afa84 */
extern word_t sk_h_001b798c(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_001b798c */
extern word_t sk_h_001b9084(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_001b9084 */
extern word_t sk_h_001ba7d4(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_001ba7d4 */
extern word_t sk_h_001bc440(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_001bc440 */
extern word_t sk_h_001ebfb0(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_001ebfb0 */
extern word_t sk_h_001ed960(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_001ed960 */
extern word_t sk_h_001ee018(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_001ee018 */
extern word_t sk_h_001ee9f4(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_001ee9f4 */
extern word_t sk_h_00205844(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00205844 */
extern word_t sk_h_002298d4(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_002298d4 */
extern word_t sk_h_0024917c(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_0024917c */
extern word_t sk_h_0024d9ac(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_0024d9ac */
extern word_t sk_h_00255d4c(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00255d4c */
extern word_t sk_h_0025a094(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_0025a094 */
extern word_t sk_h_00267510(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00267510 */
extern word_t sk_h_00267914(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00267914 */
extern word_t sk_h_00294cb4(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00294cb4 */
extern word_t sk_h_0029c058(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_0029c058 */
extern sk_r29_pair_t sk_h_0029d3d8(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_0029d3d8 */
extern sk_r29_pair_t sk_h_0029d560(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_0029d560 */
extern word_t sk_h_0029f368(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_0029f368 */
extern sk_r29_pair_t sk_h_0029fa0c(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_0029fa0c */
extern sk_r29_pair_t sk_h_0029fb80(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_0029fb80 */
extern word_t sk_h_002a0cf8(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_002a0cf8 */
extern word_t sk_h_002a49a8(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_002a49a8 */
extern word_t sk_h_002a4ab4(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_002a4ab4 */
extern word_t sk_h_002a8870(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_002a8870 */
extern word_t sk_h_002a9ba8(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_002a9ba8 */
extern word_t sk_h_002ab130(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_002ab130 */
extern word_t sk_h_002acbb8(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_002acbb8 */
extern word_t sk_h_002ace24(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_002ace24 */
extern word_t sk_h_002ae098(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_002ae098 */
extern word_t sk_h_002ae2c0(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_002ae2c0 */
extern word_t sk_h_002b141c(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_002b141c */
extern word_t sk_h_002b14c8(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_002b14c8 */
extern word_t sk_h_002b3670(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_002b3670 */
extern word_t sk_h_002b3b50(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_002b3b50 */
extern sk_r29_pair_t sk_h_002b439c(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_002b439c */
extern word_t sk_h_002b7088(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_002b7088 */
extern word_t sk_h_002b723c(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_002b723c */
extern word_t sk_h_002bbf08(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_002bbf08 */
extern word_t sk_h_002bc234(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_002bc234 */
extern word_t sk_h_002bc5bc(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_002bc5bc */
extern word_t sk_h_002bd724(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_002bd724 */
extern word_t sk_h_002bd8f0(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_002bd8f0 */
extern word_t sk_h_002bd9ac(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_002bd9ac */
extern word_t sk_h_002bd9cc(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_002bd9cc */
extern word_t sk_h_00310d98(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00310d98 */
extern word_t sk_h_00319808(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00319808 */
extern word_t sk_h_0032b65c(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_0032b65c */
extern word_t sk_h_0034a018(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_0034a018 */
extern word_t sk_h_0034a3b0(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_0034a3b0 */
extern word_t sk_h_0034b3f8(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_0034b3f8 */
extern word_t sk_h_0034b848(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_0034b848 */
extern word_t sk_h_0034c6d4(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_0034c6d4 */
extern word_t sk_h_0034cb88(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_0034cb88 */
extern word_t sk_h_0034cc24(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_0034cc24 */
extern word_t sk_h_0034cec4(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_0034cec4 */
extern word_t sk_h_0034d3d4(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_0034d3d4 */
extern word_t sk_h_0034db28(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_0034db28 */
extern word_t sk_h_0034eb74(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_0034eb74 */
extern word_t sk_h_0034ecc8(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_0034ecc8 */
extern word_t sk_h_0034fbb0(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_0034fbb0 */
extern word_t sk_h_00350470(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00350470 */
extern word_t sk_h_00350494(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00350494 */
extern word_t sk_h_003504a0(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_003504a0 */
extern word_t sk_h_003504ac(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_003504ac */
extern word_t sk_h_003504c4(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_003504c4 */
extern word_t sk_h_003504d0(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_003504d0 */
extern word_t sk_h_00350518(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00350518 */
extern word_t sk_h_0035053c(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_0035053c */
extern word_t sk_h_00350548(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00350548 */
extern word_t sk_h_003505c4(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_003505c4 */
extern word_t sk_h_00350600(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00350600 */
extern word_t sk_h_0035060c(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_0035060c */
extern word_t sk_h_00350618(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00350618 */
extern word_t sk_h_00350624(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00350624 */
extern word_t sk_h_00350774(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00350774 */
extern word_t sk_h_003507e0(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_003507e0 */
extern word_t sk_h_0035084c(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_0035084c */
extern word_t sk_h_0035089c(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_0035089c */
extern word_t sk_h_003508cc(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_003508cc */
extern word_t sk_h_003508fc(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_003508fc */
extern word_t sk_h_00350914(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00350914 */
extern word_t sk_h_00350968(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00350968 */
extern word_t sk_h_003509b0(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_003509b0 */
extern word_t sk_h_003509bc(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_003509bc */
extern word_t sk_h_003509c8(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_003509c8 */
extern word_t sk_h_003509ec(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_003509ec */
extern word_t sk_h_00350af4(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00350af4 */
extern word_t sk_h_00350b18(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00350b18 */
extern word_t sk_h_00350b48(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00350b48 */
extern word_t sk_h_00350bfc(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00350bfc */
extern word_t sk_h_00350c20(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00350c20 */
extern word_t sk_h_00350d94(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00350d94 */
extern word_t sk_h_003510c4(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_003510c4 */
extern word_t sk_h_00351124(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00351124 */
extern word_t sk_h_00351130(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00351130 */
extern word_t sk_h_00351178(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00351178 */
extern word_t sk_h_003511a8(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_003511a8 */
extern word_t sk_h_003511cc(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_003511cc */
extern word_t sk_h_003511f0(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_003511f0 */
extern word_t sk_h_00351214(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00351214 */
extern word_t sk_h_00351244(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00351244 */
extern word_t sk_h_00351274(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00351274 */
extern word_t sk_h_00351354(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00351354 */
extern word_t sk_h_0035136c(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_0035136c */
extern sk_r29_pair_t sk_h_00351384(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00351384 */
extern word_t sk_h_003513a8(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_003513a8 */
extern word_t sk_h_003513b4(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_003513b4 */
extern word_t sk_h_00351414(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00351414 */
extern word_t sk_h_00351450(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00351450 */
extern word_t sk_h_00351488(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00351488 */
extern word_t sk_h_00351584(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00351584 */
extern word_t sk_h_003515fc(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_003515fc */
extern word_t sk_h_00351774(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00351774 */
extern word_t sk_h_003517c0(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_003517c0 */
extern sk_r29_pair_t sk_h_0035193c(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_0035193c */
extern word_t sk_h_00351a50(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00351a50 */
extern word_t sk_h_00351aec(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00351aec */
extern word_t sk_h_00351b78(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00351b78 */
extern word_t sk_h_00351bd4(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00351bd4 */
extern word_t sk_h_00351c7c(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00351c7c */
extern word_t sk_h_00351cd0(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00351cd0 */
extern word_t sk_h_00351d18(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00351d18 */
extern word_t sk_h_00351d30(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00351d30 */
extern word_t sk_h_00351db4(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00351db4 */
extern word_t sk_h_00351dfc(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00351dfc */
extern word_t sk_h_00351e08(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00351e08 */
extern sk_r29_pair_t sk_h_00351e20(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00351e20 */
extern word_t sk_h_00351e3c(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00351e3c */
extern word_t sk_h_00351f34(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00351f34 */
extern word_t sk_h_003522c8(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_003522c8 */
extern word_t sk_h_00352800(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00352800 */
extern word_t sk_h_00352840(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00352840 */
extern word_t sk_h_00352af0(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00352af0 */
extern word_t sk_h_00352c40(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00352c40 */
extern word_t sk_h_00352c4c(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00352c4c */
extern word_t sk_h_00352c68(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00352c68 */
extern word_t sk_h_00352c80(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00352c80 */
extern word_t sk_h_00352e9c(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00352e9c */
extern word_t sk_h_0035310c(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_0035310c */
extern word_t sk_h_003532b8(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_003532b8 */
extern word_t sk_h_003535a8(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_003535a8 */
extern sk_r29_pair_t sk_h_00353cfc(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00353cfc */
extern word_t sk_h_00353d14(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00353d14 */
extern word_t sk_h_00353ff4(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00353ff4 */
extern word_t sk_h_00354410(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00354410 */
extern word_t sk_h_003544c8(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_003544c8 */
extern sk_r29_pair_t sk_h_00354744(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00354744 */
extern word_t sk_h_003548dc(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_003548dc */
extern word_t sk_h_00354998(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00354998 */
extern word_t sk_h_00354a34(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00354a34 */
extern word_t sk_h_00354d5c(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00354d5c */
extern word_t sk_h_00354e0c(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00354e0c */
extern word_t sk_h_00354ef8(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00354ef8 */
extern word_t sk_h_00355754(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00355754 */
extern word_t sk_h_00355da8(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00355da8 */
extern word_t sk_h_00356364(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00356364 */
extern word_t sk_h_00356370(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00356370 */
extern sk_r29_pair_t sk_h_0035638c(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_0035638c */
extern word_t sk_h_00356930(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00356930 */
extern word_t sk_h_003577a0(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_003577a0 */
extern word_t sk_h_00357c74(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00357c74 */
extern sk_r29_pair_t sk_h_00357cb4(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00357cb4 */
extern word_t sk_h_0035847c(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_0035847c */
extern word_t sk_h_003593c0(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_003593c0 */
extern word_t sk_h_0035a8d0(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_0035a8d0 */
extern sk_r29_pair_t sk_h_0035a9b0(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_0035a9b0 */
extern word_t sk_h_0035b67c(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_0035b67c */
extern word_t sk_h_00365b6c(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00365b6c */
extern word_t sk_h_0036986c(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_0036986c */
extern word_t sk_h_0036a940(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_0036a940 */
extern word_t sk_h_0036a9a0(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_0036a9a0 */
extern word_t sk_h_0036b118(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_0036b118 */
extern word_t sk_h_0036b270(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_0036b270 */
extern word_t sk_h_0039a128(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_0039a128 */
extern word_t sk_h_003a25d4(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_003a25d4 */
extern word_t sk_h_003a2610(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_003a2610 */
extern word_t sk_h_003a261c(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_003a261c */
extern word_t sk_h_004080b0(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004080b0 */
extern word_t sk_h_0040fbc0(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_0040fbc0 */
extern word_t sk_h_00410e78(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00410e78 */
extern word_t sk_h_0041449c(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_0041449c */
extern word_t sk_h_00414644(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00414644 */
extern word_t sk_h_004176bc(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004176bc */
extern word_t sk_h_00417b60(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00417b60 */
extern word_t sk_h_0041ae04(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_0041ae04 */
extern word_t sk_h_0041d778(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_0041d778 */
extern word_t sk_h_0041d788(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_0041d788 */
extern word_t sk_h_0041d7dc(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_0041d7dc */
extern word_t sk_h_0042ec5c(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_0042ec5c */
extern word_t sk_h_00436fc8(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00436fc8 */
extern word_t sk_h_0043f454(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_0043f454 */
extern word_t sk_h_00447144(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00447144 */
extern word_t sk_h_0044c9c4(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_0044c9c4 */
extern word_t sk_h_0044ca08(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_0044ca08 */
extern word_t sk_h_0044ca2c(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_0044ca2c */
extern word_t sk_h_0044ca60(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_0044ca60 */
extern word_t sk_h_0044cb38(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_0044cb38 */
extern word_t sk_h_0044cb90(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_0044cb90 */
extern word_t sk_h_0044cc6c(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_0044cc6c */
extern word_t sk_h_0044cda0(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_0044cda0 */
extern word_t sk_h_0044f098(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_0044f098 */
extern word_t sk_h_0044f818(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_0044f818 */
extern word_t sk_h_00450878(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00450878 */
extern word_t sk_h_00450adc(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00450adc */
extern word_t sk_h_00451894(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00451894 */
extern word_t sk_h_00451a64(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00451a64 */
extern word_t sk_h_004588cc(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004588cc */
extern word_t sk_h_004589bc(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004589bc */
extern word_t sk_h_004589e8(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004589e8 */
extern word_t sk_h_004589f8(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004589f8 */
extern sk_r29_pair_t sk_h_00458af8(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00458af8 */
extern sk_r29_pair_t sk_h_00458b14(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00458b14 */
extern word_t sk_h_00458c98(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00458c98 */
extern word_t sk_h_004590e0(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004590e0 */
extern word_t sk_h_004629b4(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004629b4 */
extern word_t sk_h_00462aac(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00462aac */
extern word_t sk_h_00462abc(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00462abc */
extern word_t sk_h_00462b6c(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00462b6c */
extern word_t sk_h_00462e9c(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00462e9c */
extern word_t sk_h_00463878(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00463878 */
extern word_t sk_h_00463e04(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00463e04 */
extern sk_r29_pair_t sk_h_00463f94(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00463f94 */
extern word_t sk_h_00464a44(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00464a44 */
extern word_t sk_h_00464e34(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00464e34 */
extern word_t sk_h_0046511c(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_0046511c */
extern word_t sk_h_00465258(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00465258 */
extern word_t sk_h_00465294(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00465294 */
extern word_t sk_h_004657ac(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004657ac */
extern word_t sk_h_00466104(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00466104 */
extern word_t sk_h_00466214(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00466214 */
extern word_t sk_h_00468ee4(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00468ee4 */
extern word_t sk_h_00469c50(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00469c50 */
extern word_t sk_h_00469dc4(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00469dc4 */
extern word_t sk_h_0046a368(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_0046a368 */
extern word_t sk_h_0046c4e0(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_0046c4e0 */
extern word_t sk_h_004730f0(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004730f0 */
extern word_t sk_h_004731b8(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004731b8 */
extern word_t sk_h_004766ec(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004766ec */
extern word_t sk_h_004769a4(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004769a4 */
extern word_t sk_h_004775d0(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004775d0 */
extern word_t sk_h_004776c4(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004776c4 */
extern word_t sk_h_004811e8(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004811e8 */
extern word_t sk_h_00481510(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00481510 */
extern word_t sk_h_004815ac(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004815ac */
extern word_t sk_h_004815cc(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004815cc */
extern word_t sk_h_00490174(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00490174 */
extern word_t sk_h_00490600(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00490600 */
extern word_t sk_h_00492704(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00492704 */
extern word_t sk_h_00494ea8(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00494ea8 */
extern word_t sk_h_00494f3c(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00494f3c */
extern word_t sk_h_0049513c(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_0049513c */
extern word_t sk_h_00496ef0(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00496ef0 */
extern word_t sk_h_00497224(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00497224 */
extern word_t sk_h_004981d8(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004981d8 */
extern word_t sk_h_00498228(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00498228 */
extern word_t sk_h_00498500(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00498500 */
extern word_t sk_h_00498ad4(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00498ad4 */
extern word_t sk_h_00498b28(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00498b28 */
extern word_t sk_h_00498b7c(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00498b7c */
extern word_t sk_h_00498bdc(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00498bdc */
extern word_t sk_h_00498c1c(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00498c1c */
extern word_t sk_h_00498c84(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00498c84 */
extern word_t sk_h_00498cc8(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00498cc8 */
extern word_t sk_h_00498e50(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00498e50 */
extern word_t sk_h_00499094(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00499094 */
extern word_t sk_h_0049952c(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_0049952c */
extern word_t sk_h_00499918(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00499918 */
extern word_t sk_h_00499dbc(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00499dbc */
extern word_t sk_h_00499e1c(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00499e1c */
extern word_t sk_h_00499e94(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00499e94 */
extern sk_r29_pair_t sk_h_00499f6c(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_00499f6c */
extern word_t sk_h_0049a058(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_0049a058 */
extern word_t sk_h_0049a184(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_0049a184 */
extern word_t sk_h_0049a440(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_0049a440 */
extern word_t sk_h_0049a454(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_0049a454 */
extern word_t sk_h_0049a468(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_0049a468 */
extern word_t sk_h_0049a47c(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_0049a47c */
extern word_t sk_h_0049a490(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_0049a490 */
extern word_t sk_h_0049a530(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_0049a530 */
extern word_t sk_h_0049a550(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_0049a550 */
extern word_t sk_h_0049a5ac(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_0049a5ac */
extern word_t sk_h_0049a82c(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_0049a82c */
extern word_t sk_h_0049a91c(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_0049a91c */
extern word_t sk_h_0049ab00(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_0049ab00 */
extern word_t sk_h_0049c200(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_0049c200 */
extern word_t sk_h_0049c4b4(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_0049c4b4 */
extern word_t sk_h_0049c52c(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_0049c52c */
extern word_t sk_h_0049c5a0(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_0049c5a0 */
extern word_t sk_h_0049c5f8(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_0049c5f8 */
extern word_t sk_h_0049c838(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_0049c838 */
extern word_t sk_h_0049c9fc(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_0049c9fc */
extern word_t sk_h_0049ca14(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_0049ca14 */
extern word_t sk_h_0049ca2c(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_0049ca2c */
extern word_t sk_h_0049ca44(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_0049ca44 */
extern word_t sk_h_0049df0c(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_0049df0c */
extern word_t sk_h_0049df18(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_0049df18 */
extern word_t sk_h_0049e2d4(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_0049e2d4 */
extern word_t sk_h_0049e2f0(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_0049e2f0 */
extern word_t sk_h_004a31ec(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004a31ec */
extern word_t sk_h_004a31fc(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004a31fc */
extern word_t sk_h_004a3214(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004a3214 */
extern word_t sk_h_004a322c(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004a322c */
extern word_t sk_h_004a34f0(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004a34f0 */
extern word_t sk_h_004a3500(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004a3500 */
extern word_t sk_h_004a3528(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004a3528 */
extern word_t sk_h_004a3550(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004a3550 */
extern word_t sk_h_004a3560(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004a3560 */
extern word_t sk_h_004a36c4(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004a36c4 */
extern word_t sk_h_004a36d4(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004a36d4 */
extern word_t sk_h_004a3918(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004a3918 */
extern word_t sk_h_004a3940(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004a3940 */
extern word_t sk_h_004a42a0(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004a42a0 */
extern word_t sk_h_004a4310(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004a4310 */
extern word_t sk_h_004a463c(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004a463c */
extern word_t sk_h_004a46f0(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004a46f0 */
extern word_t sk_h_004a4724(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004a4724 */
extern word_t sk_h_004a487c(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004a487c */
extern word_t sk_h_004a49a0(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004a49a0 */
extern word_t sk_h_004a49c0(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004a49c0 */
extern word_t sk_h_004a4a34(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004a4a34 */
extern word_t sk_h_004a4aa4(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004a4aa4 */
extern word_t sk_h_004a4ac4(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004a4ac4 */
extern word_t sk_h_004a4b14(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004a4b14 */
extern word_t sk_h_004aa370(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004aa370 */
extern word_t sk_h_004aa38c(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004aa38c */
extern word_t sk_h_004aa3bc(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004aa3bc */
extern word_t sk_h_004aa3fc(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004aa3fc */
extern word_t sk_h_004aa42c(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004aa42c */
extern word_t sk_h_004aa494(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004aa494 */
extern word_t sk_h_004aa4c4(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004aa4c4 */
extern word_t sk_h_004aa514(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004aa514 */
extern word_t sk_h_004aa52c(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004aa52c */
extern word_t sk_h_004aa580(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004aa580 */
extern word_t sk_h_004aa5f8(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004aa5f8 */
extern word_t sk_h_004aa694(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004aa694 */
extern word_t sk_h_004aa6a8(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004aa6a8 */
extern word_t sk_h_004aa794(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004aa794 */
extern word_t sk_h_004aa7a8(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004aa7a8 */
extern word_t sk_h_004aa7bc(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004aa7bc */
extern word_t sk_h_004aa7d0(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004aa7d0 */
extern word_t sk_h_004aa7fc(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004aa7fc */
extern word_t sk_h_004aa824(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004aa824 */
extern word_t sk_h_004aa83c(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004aa83c */
extern word_t sk_h_004aa850(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004aa850 */
extern word_t sk_h_004aa864(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004aa864 */
extern word_t sk_h_004aa890(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004aa890 */
extern word_t sk_h_004aa8f0(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004aa8f0 */
extern word_t sk_h_004aa904(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004aa904 */
extern word_t sk_h_004aa938(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004aa938 */
extern word_t sk_h_004aa990(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004aa990 */
extern word_t sk_h_004aa9a8(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004aa9a8 */
extern word_t sk_h_004aa9f8(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004aa9f8 */
extern word_t sk_h_004aaa20(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004aaa20 */
extern word_t sk_h_004aaa78(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004aaa78 */
extern word_t sk_h_004aaab0(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004aaab0 */
extern word_t sk_h_004aaacc(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004aaacc */
extern word_t sk_h_004aab08(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004aab08 */
extern word_t sk_h_004aab1c(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004aab1c */
extern word_t sk_h_004aab4c(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004aab4c */
extern word_t sk_h_004aab60(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004aab60 */
extern word_t sk_h_004aab74(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004aab74 */
extern word_t sk_h_004aac40(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004aac40 */
extern word_t sk_h_004aacf8(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004aacf8 */
extern word_t sk_h_004aad30(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004aad30 */
extern word_t sk_h_004aad54(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004aad54 */
extern word_t sk_h_004aad94(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004aad94 */
extern word_t sk_h_004aada4(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004aada4 */
extern word_t sk_h_004aadcc(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004aadcc */
extern word_t sk_h_004aade4(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004aade4 */
extern word_t sk_h_004aadfc(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004aadfc */
extern word_t sk_h_004aae2c(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004aae2c */
extern word_t sk_h_004aae64(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004aae64 */
extern word_t sk_h_004aae98(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004aae98 */
extern word_t sk_h_004aaf28(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004aaf28 */
extern word_t sk_h_004aaf58(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004aaf58 */
extern word_t sk_h_004aaf9c(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004aaf9c */
extern word_t sk_h_004aafac(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004aafac */
extern word_t sk_h_004aafd8(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004aafd8 */
extern word_t sk_h_004ab034(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ab034 */
extern word_t sk_h_004ab044(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ab044 */
extern word_t sk_h_004ab054(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ab054 */
extern word_t sk_h_004ab064(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ab064 */
extern word_t sk_h_004ab080(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ab080 */
extern word_t sk_h_004ab0ac(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ab0ac */
extern word_t sk_h_004ab0bc(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ab0bc */
extern word_t sk_h_004ab0e0(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ab0e0 */
extern word_t sk_h_004ab0f0(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ab0f0 */
extern word_t sk_h_004ab178(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ab178 */
extern word_t sk_h_004ab1a0(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ab1a0 */
extern word_t sk_h_004ab208(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ab208 */
extern word_t sk_h_004ab224(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ab224 */
extern word_t sk_h_004ab260(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ab260 */
extern word_t sk_h_004ab26c(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ab26c */
extern word_t sk_h_004ab2a0(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ab2a0 */
extern word_t sk_h_004ab2d0(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ab2d0 */
extern word_t sk_h_004ab304(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ab304 */
extern word_t sk_h_004ab35c(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ab35c */
extern word_t sk_h_004ab3c4(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ab3c4 */
extern word_t sk_h_004ab3dc(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ab3dc */
extern word_t sk_h_004ab408(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ab408 */
extern word_t sk_h_004ab448(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ab448 */
extern word_t sk_h_004ab458(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ab458 */
extern word_t sk_h_004ab468(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ab468 */
extern word_t sk_h_004ab4a8(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ab4a8 */
extern word_t sk_h_004ab4e8(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ab4e8 */
extern word_t sk_h_004ab4f4(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ab4f4 */
extern word_t sk_h_004ab520(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ab520 */
extern word_t sk_h_004ab530(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ab530 */
extern word_t sk_h_004ab55c(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ab55c */
extern word_t sk_h_004ab568(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ab568 */
extern word_t sk_h_004ab58c(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ab58c */
extern word_t sk_h_004ab5a4(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ab5a4 */
extern word_t sk_h_004ab5c8(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ab5c8 */
extern sk_r29_pair_t sk_h_004ab60c(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ab60c */
extern word_t sk_h_004ab618(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ab618 */
extern word_t sk_h_004ab650(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ab650 */
extern word_t sk_h_004ab68c(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ab68c */
extern word_t sk_h_004ab6c4(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ab6c4 */
extern word_t sk_h_004ab6d8(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ab6d8 */
extern word_t sk_h_004ab6e8(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ab6e8 */
extern word_t sk_h_004ab700(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ab700 */
extern word_t sk_h_004ab724(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ab724 */
extern word_t sk_h_004ab760(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ab760 */
extern word_t sk_h_004ab784(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ab784 */
extern word_t sk_h_004ab798(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ab798 */
extern word_t sk_h_004ab7b8(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ab7b8 */
extern word_t sk_h_004ab7cc(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ab7cc */
extern word_t sk_h_004ab810(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ab810 */
extern word_t sk_h_004ab820(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ab820 */
extern word_t sk_h_004ab834(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ab834 */
extern word_t sk_h_004ab844(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ab844 */
extern word_t sk_h_004ab858(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ab858 */
extern word_t sk_h_004ab89c(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ab89c */
extern word_t sk_h_004ab8c8(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ab8c8 */
extern word_t sk_h_004ab8dc(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ab8dc */
extern word_t sk_h_004ab8e8(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ab8e8 */
extern word_t sk_h_004ab930(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ab930 */
extern word_t sk_h_004ab944(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ab944 */
extern word_t sk_h_004ab968(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ab968 */
extern sk_r29_pair_t sk_h_004ab974(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ab974 */
extern word_t sk_h_004ab98c(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ab98c */
extern word_t sk_h_004ab9bc(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ab9bc */
extern word_t sk_h_004ab9e0(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ab9e0 */
extern word_t sk_h_004ab9f8(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ab9f8 */
extern sk_r29_pair_t sk_h_004aba34(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004aba34 */
extern word_t sk_h_004aba88(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004aba88 */
extern word_t sk_h_004abad8(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004abad8 */
extern word_t sk_h_004abaf0(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004abaf0 */
extern word_t sk_h_004abb1c(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004abb1c */
extern word_t sk_h_004abb28(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004abb28 */
extern word_t sk_h_004abb58(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004abb58 */
extern word_t sk_h_004abbac(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004abbac */
extern word_t sk_h_004abbd4(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004abbd4 */
extern word_t sk_h_004abc28(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004abc28 */
extern word_t sk_h_004abc38(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004abc38 */
extern word_t sk_h_004abc78(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004abc78 */
extern sk_r29_pair_t sk_h_004abcb4(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004abcb4 */
extern word_t sk_h_004abcdc(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004abcdc */
extern sk_r29_pair_t sk_h_004abcf8(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004abcf8 */
extern word_t sk_h_004abd20(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004abd20 */
extern word_t sk_h_004abd2c(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004abd2c */
extern word_t sk_h_004abd38(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004abd38 */
extern word_t sk_h_004abd9c(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004abd9c */
extern word_t sk_h_004abdc4(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004abdc4 */
extern word_t sk_h_004abe24(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004abe24 */
extern word_t sk_h_004abe5c(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004abe5c */
extern word_t sk_h_004abe68(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004abe68 */
extern word_t sk_h_004abe74(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004abe74 */
extern word_t sk_h_004abeb0(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004abeb0 */
extern word_t sk_h_004abed0(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004abed0 */
extern word_t sk_h_004abf00(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004abf00 */
extern word_t sk_h_004abf10(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004abf10 */
extern word_t sk_h_004abf20(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004abf20 */
extern word_t sk_h_004abf30(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004abf30 */
extern word_t sk_h_004abf40(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004abf40 */
extern word_t sk_h_004abf5c(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004abf5c */
extern word_t sk_h_004abfa8(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004abfa8 */
extern word_t sk_h_004abfd8(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004abfd8 */
extern word_t sk_h_004abfe8(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004abfe8 */
extern word_t sk_h_004abff8(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004abff8 */
extern word_t sk_h_004ac008(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ac008 */
extern word_t sk_h_004ac034(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ac034 */
extern word_t sk_h_004ac0cc(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ac0cc */
extern word_t sk_h_004ac108(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ac108 */
extern word_t sk_h_004ac114(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ac114 */
extern word_t sk_h_004ac120(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ac120 */
extern word_t sk_h_004ac12c(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ac12c */
extern sk_r29_pair_t sk_h_004ac144(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ac144 */
extern word_t sk_h_004ac15c(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ac15c */
extern word_t sk_h_004ac198(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ac198 */
extern word_t sk_h_004ac1a4(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ac1a4 */
extern word_t sk_h_004ac210(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ac210 */
extern word_t sk_h_004ac258(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ac258 */
extern word_t sk_h_004ac27c(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ac27c */
extern word_t sk_h_004ac294(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ac294 */
extern word_t sk_h_004ac2a0(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ac2a0 */
extern word_t sk_h_004ac2c4(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ac2c4 */
extern word_t sk_h_004ac2f4(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ac2f4 */
extern sk_r29_pair_t sk_h_004ac30c(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ac30c */
extern word_t sk_h_004ac360(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ac360 */
extern word_t sk_h_004ac3e4(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ac3e4 */
extern word_t sk_h_004ac3f0(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ac3f0 */
extern word_t sk_h_004ac4f0(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ac4f0 */
extern word_t sk_h_004ac518(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ac518 */
extern word_t sk_h_004ac52c(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ac52c */
extern word_t sk_h_004ac55c(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ac55c */
extern word_t sk_h_004ac574(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ac574 */
extern word_t sk_h_004ac5a4(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ac5a4 */
extern word_t sk_h_004ac5b4(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ac5b4 */
extern word_t sk_h_004ac5c4(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ac5c4 */
extern word_t sk_h_004ac5ec(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ac5ec */
extern word_t sk_h_004ac5fc(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ac5fc */
extern word_t sk_h_004ac634(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ac634 */
extern word_t sk_h_004ac654(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ac654 */
extern word_t sk_h_004ac66c(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ac66c */
extern word_t sk_h_004ac680(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ac680 */
extern word_t sk_h_004ac698(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ac698 */
extern word_t sk_h_004ac6f8(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ac6f8 */
extern word_t sk_h_004ac70c(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ac70c */
extern word_t sk_h_004ac738(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ac738 */
extern word_t sk_h_004ac758(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ac758 */
extern word_t sk_h_004ac76c(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ac76c */
extern word_t sk_h_004ac778(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ac778 */
extern word_t sk_h_004ac7b0(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ac7b0 */
extern sk_r29_pair_t sk_h_004ac7bc(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ac7bc */
extern word_t sk_h_004ac844(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ac844 */
extern word_t sk_h_004ac850(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ac850 */
extern word_t sk_h_004ac8a8(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ac8a8 */
extern word_t sk_h_004ac8d4(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ac8d4 */
extern word_t sk_h_004ac8fc(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ac8fc */
extern word_t sk_h_004ac91c(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ac91c */
extern word_t sk_h_004ac960(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ac960 */
extern word_t sk_h_004ac96c(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ac96c */
extern word_t sk_h_004ac98c(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ac98c */
extern word_t sk_h_004ac9ac(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ac9ac */
extern word_t sk_h_004ac9cc(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ac9cc */
extern word_t sk_h_004ac9f8(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004ac9f8 */
extern word_t sk_h_004aca2c(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004aca2c */
extern word_t sk_h_004aca4c(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004aca4c */
extern word_t sk_h_004aca94(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004aca94 */
extern word_t sk_h_004acb04(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004acb04 */
extern word_t sk_h_004acb58(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004acb58 */
extern word_t sk_h_004acba8(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004acba8 */
extern word_t sk_h_004acbbc(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004acbbc */
extern word_t sk_h_004acc34(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004acc34 */
extern word_t sk_h_004acc5c(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004acc5c */
extern word_t sk_h_004acc84(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004acc84 */
extern word_t sk_h_004acc90(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004acc90 */
extern word_t sk_h_004accb4(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004accb4 */
extern word_t sk_h_004accc0(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004accc0 */
extern word_t sk_h_004accd8(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004accd8 */
extern word_t sk_h_004accfc(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004accfc */
extern word_t sk_h_004acd14(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004acd14 */

/* FUN_00481600 @ 0x00481600   (est. sk_regex_unicode_category_bits)
 * Ghidra: undefined8 FUN_00481600(ulong param_1)
 * Returns a 2-bit Unicode general-category selector derived from bits 16-17 of
 * the tagged input: 0 (default), 1, or 2. An illegal combination (both bits
 * set) traps. Confidence: medium. Notes: panic via FUN_00350d94/0006f768/
 * 001afa84. */
word_t sk_h_481600(word_t p)
{
    word_t r = 0;
    switch ((p >> 0x10) & 3) {
    case 1: r = 1; break;
    case 2: return 2;
    case 3:
        sk_h_00350d94(0x209, 0);
        sk_h_0006f768();
        sk_h_001afa84();           /* noreturn */
    }
    return r;
}

/* FUN_0048169c @ 0x0048169c   (est. sk_regex_emit_anchor_slot8)
 * Ghidra: void FUN_0048169c(void)
 * Emits anchor kind 8 (start-of-subject) via the class/kind dispatcher.
 * Confidence: medium. */
void sk_h_48169c(void) { sk_h_004ac518(8); }

/* FUN_004816a8 @ 0x004816a8   (est. sk_regex_emit_anchor_slot0d)
 * Ghidra: void FUN_004816a8(void)
 * Emits anchor kind 0xd (end-of-subject) via the dispatcher. Confidence: medium. */
void sk_h_4816a8(void) { sk_h_004ac518(0xd); }

/* FUN_004816b4 @ 0x004816b4   (est. sk_regex_emit_anchor_slot1e)
 * Ghidra: void FUN_004816b4(void)
 * Emits anchor kind 0x1e (word boundary / general anchor) via the dispatcher;
 * returns the kind byte. Confidence: medium. */
word_t sk_h_4816b4(void) { return sk_h_004ac518(0x1e); }

/* FUN_004816c0 @ 0x004816c0   (est. sk_regex_emit_char_class)
 * Ghidra: void FUN_004816c0(void)
 * Dispatches a character-class emission; *unaff_x20 is the class selector
 * word and thunk_FUN_002298d4 is the vspace wait/sync helper. Confidence: low
 * (register-global target). */
void sk_h_4816c0(word_t *x20)
{
    sk_h_00492704(*x20, (word_t)sk_h_002298d4);
}

/* FUN_00481700 @ 0x00481700   (est. sk_regex_emit_property_lookahead)
 * Ghidra: void FUN_00481700(void)
 * Dispatches a regex property emission; *unaff_x20 is the property selector.
 * Confidence: low. */
void sk_h_481700(word_t *x20) { sk_h_00494ea8(*x20, (word_t)sk_h_002298d4); }

/* FUN_00481704 @ 0x00481704   (est. sk_regex_emit_property_lookahead2)
 * Ghidra: void FUN_00481704(void)
 * Same as FUN_00481700 (adjacent slot). Confidence: low. */
void sk_h_481704(word_t *x20) { sk_h_00494ea8(*x20, (word_t)sk_h_002298d4); }

/* FUN_00481738 @ 0x00481738   (est. sk_regex_emit_scalar_0)
 * Ghidra: void FUN_00481738(undefined8 param_1)
 * Emits a scalar emission; forwards param_1 plus the register-global *x20.
 * Confidence: low. */
void sk_h_481738(word_t p, word_t *x20) { sk_h_00481510(p, *x20); }

/* FUN_0048173c @ 0x0048173c   (est. sk_regex_emit_scalar_1)
 * Ghidra: void FUN_0048173c(undefined8 param_1)
 * Adjacent scalar-emission slot. Confidence: low. */
void sk_h_48173c(word_t p, word_t *x20) { sk_h_00481510(p, *x20); }

/* FUN_00481754 @ 0x00481754   (est. sk_regex_store_class_kind)
 * Ghidra: void FUN_00481754(void)
 * Stores the anchor kind returned by FUN_004816b4 into the *x19 result slot.
 * Confidence: low (register-global result). */
void sk_h_481754(word_t *x19)
{
    word_t k;
    sk_h_00351124();
    k = sk_h_4816b4();
    *x19 = k;
}

/* FUN_00481780 @ 0x00481780   (est. sk_regex_hash_slot_insert)
 * Ghidra: undefined8 FUN_00481780(undefined8 param_1, undefined8 param_2)
 * Hash-table insert of a (key,value) pair into the table whose capacity lives
 * at *x20; grows the backing vector when the key is not already present and
 * re-hashes. Returns the stored value (or the existing slot's value on a
 * hit). Confidence: low (register-global table pointer). */
word_t sk_h_481780(word_t k, word_t v, word_t *x20)
{
    long cap = *(long *)(*x20 + 0x10);
    sk_r29_pair_t h;
    if (cap == 0 || ((h = sk_h_0006ae9c(k, v)), (h.hi & 1) == 0)) {
        word_t *dst = x20 + 1;
        word_t n = *(word_t *)(*dst + 0x10);
        sk_h_0036b270(v);
        sk_h_00498b28((word_t)sk_h_00073524);
        long m = *(long *)(*dst + 0x10);
        sk_h_00498c1c(m, (word_t)sk_h_00073524);
        long base = *dst;
        *(long *)(base + 0x10) = m + 1;
        long slot = base + m * 0x10;
        *(word_t *)(slot + 0x20) = k;
        *(word_t *)(slot + 0x28) = v;
        *dst = base;
        sk_h_0049a058(n, k, v);
        return n;
    }
    return *(word_t *)(*(long *)(*x20 + 0x38) + h.lo * 8);
}

/* FUN_0048185c @ 0x0048185c   (est. sk_regex_hash_key_insert)
 * Ghidra: undefined8 FUN_0048185c(undefined8 param_1)
 * Hash-table insertion keyed on param_1 only; returns the existing value or
 * the stored value after inserting. Confidence: low. */
word_t sk_h_48185c(word_t k, word_t *x20)
{
    long cap = *(long *)(*x20 + 0x10);
    sk_r29_pair_t h;
    if (cap == 0 || ((h = sk_h_00499f6c(k)), (h.hi & 1) == 0)) {
        word_t u = *(word_t *)(x20[1] + 0x10);
        sk_h_0036b270(k);
        sk_h_00070594();
        sk_h_0049a184(u, k);
        return u;
    }
    return *(word_t *)(*(long *)(*x20 + 0x38) + h.lo * 8);
}

/* FUN_004818d8 @ 0x004818d8   (est. sk_regex_emit_capture_open)
 * Ghidra: void FUN_004818d8(ulong param_1, long param_2)
 * Emits a capture-group open: packs param_1 | param_2<<16 and forwards
 * through the emit pipeline. Confidence: low. */
void sk_h_4818d8(word_t p1, long p2)
{
    sk_h_004aa494(p1 | (word_t)p2 << 0x10);
    sk_h_00498b28(0);
    sk_h_004aaf58();
    sk_h_004aa6a8();
}

/* FUN_00481918 @ 0x00481918   (est. sk_regex_push_match_record)
 * Ghidra: void FUN_00481918(undefined8 param_1)
 * Appends a 0x38-byte match record (tag 1) to the work vector at unaff_x20[0xb]:
 * {count, param_1, 0, 1}. The record's count field is derived from the total
 * at *x20+0x10. Confidence: low (register-global vector pointer). */
void sk_h_481918(word_t p1, word_t *x20)
{
    long total = *(long *)(*x20 + 0x10);
    sk_h_00498b28((word_t)sk_h_00499094);
    long n = *(long *)(x20[0xb] + 0x10);
    sk_h_003504c4();
    sk_h_00498c1c();
    long base = x20[0xb];
    *(long *)(base + 0x10) = n + 1;
    long slot = base + n * 0x20;
    *(long *)(slot + 0x20) = total - 1;
    *(word_t *)(slot + 0x28) = p1;
    *(word_t *)(slot + 0x30) = 0;
    *(unsigned char *)(slot + 0x38) = 1;
    x20[0xb] = base;
}

/* FUN_004819ac @ 0x004819ac   (est. sk_regex_push_match_record_tag0)
 * Ghidra: void FUN_004819ac(void)
 * Appends a 0x38-byte match record (tag 0) carrying unaff_x21/x22, then emits
 * the captured range. Confidence: low. */
void sk_h_4819ac(word_t *x20, word_t x21, word_t x22)
{
    sk_h_00084220();
    sk_h_003509ec();
    long total = *(long *)(*x20 + 0x10);
    sk_h_00498b28((word_t)sk_h_00499094);
    long n = *(long *)(x20[0xb] + 0x10);
    sk_h_00350518();
    sk_h_00498c1c();
    word_t newbase = sk_h_004ab224(x20[0xb]);
    long base = newbase + n * 0x20;
    *(long *)(base + 0x20) = total - 1;
    *(word_t *)(base + 0x28) = x22;
    *(word_t *)(base + 0x30) = x21;
    *(unsigned char *)(base + 0x38) = 0;
    x20[0xb] = newbase;
    sk_h_00084234(0);
}

/* FUN_00481a38 @ 0x00481a38   (est. sk_regex_flush_capture_state)
 * Ghidra: void FUN_00481a38(void)
 * Flushes/clears the capture state vector: a sequence of object teardown and
 * vector-reset calls keyed off *(x20+0x38). Confidence: low. */
void sk_h_481a38(word_t x20)
{
    sk_h_0008409c();
    sk_h_00002834(0x687dc0);
    sk_h_0036a940();
    sk_h_004ac5b4();
    sk_h_003507e0();
    sk_h_00498ad4();
    sk_h_004aad54();
    sk_h_00498bdc();
    sk_h_004ab224(*(word_t *)(x20 + 0x38));
    sk_h_004abf5c();
}

/* FUN_00481ac4 @ 0x00481ac4   (est. sk_regex_alloc_slot_array16)
 * Ghidra: undefined * FUN_00481ac4(undefined8 param_1, long param_2)
 * Allocates a vector of param_2 0x20-byte slots, initialising each element
 * (via FUN_00319808) to param_1; returns the vector (or the empty DAT_00657778
 * singleton when param_2==0). Negative param_2 traps. Confidence: medium. */
word_t sk_h_481ac4(word_t p1, long n)
{
    word_t vec;
    if (n < 0) SK_TRAP(0x481b40);   /* SoftwareBreakpoint(1,0x481b40) */
    if (n == 0) return (word_t)&sk_h_00657778;
    vec = sk_h_00499e1c(n);
    *(long *)(vec + 0x10) = n;
    word_t e = vec;
    do { e += 0x20; sk_h_00319808(p1, e); n--; } while (n != 0);
    sk_h_000026e8(p1);
    return vec;
}

/* FUN_00481b40 @ 0x00481b40   (est. sk_regex_alloc_pointer_slots)
 * Ghidra: undefined * FUN_00481b40(undefined8 param_1, long param_2)
 * Allocates a vector of param_2 slots, each an 8-byte pointer initialised to
 * the register-global x20; returns the vector. Confidence: medium. */
word_t sk_h_481b40(word_t p1, long n, word_t x20)
{
    word_t vec;
    if (n < 0) SK_TRAP(0x481b9c);
    if (n == 0) return (word_t)&sk_h_00657778;
    sk_h_00351d18();
    sk_h_00351488();
    vec = sk_h_00499dbc();
    *(long *)(vec + 0x10) = n;
    long off = 0x20;
    do { *(word_t *)(vec + off) = x20; off += 8; n--; } while (n != 0);
    return vec;
}

/* FUN_00481b9c @ 0x00481b9c   (est. sk_regex_alloc_slot_array48)
 * Ghidra: undefined * FUN_00481b9c(undefined8 param_1, long param_2)
 * Allocates a vector of param_2 0x48-byte slots initialised via FUN_004a3550,
 * then runs FUN_004a3528. Returns the vector. Confidence: medium. */
word_t sk_h_481b9c(word_t p1, long n)
{
    word_t vec;
    if (n < 0) SK_TRAP(0x481c18);
    if (n == 0) return (word_t)&sk_h_00657778;
    vec = sk_h_00499e94(n);
    *(long *)(vec + 0x10) = n;
    word_t e = vec + 0x20;
    do { sk_h_004a3550(p1, e); e += 0x48; n--; } while (n != 0);
    sk_h_004a3528(p1);
    return vec;
}

/* FUN_00481c18 @ 0x00481c18   (est. sk_regex_is_newline_seq)
 * Ghidra: bool FUN_00481c18(void)
 * Reports whether the current character completes a newline sequence: a scan
 * (FUN_001ae8a8) followed by a char-class query returning kind 9, or a CR/FF
 * byte (0x16). Confidence: low (register carry-flag artifact). */
bool sk_h_481c18(void)
{
    sk_h_001ae8a8();
    int k = (int)sk_h_0034ecc8();
    if (k == 9) return true;
    return (char)sk_h_002bc5bc() == 0x16;
}

/* FUN_00481c60 @ 0x00481c60   (est. sk_regex_is_line_terminator)
 * Ghidra: undefined8 FUN_00481c60(void)
 * Returns 0 on a scan failure, else forwards to FUN_00481c90. Confidence: low. */
word_t sk_h_481c60(void)
{
    sk_h_001ae8a8();
    sk_h_0034ecc8();
    return sk_h_481c90(0);
}

/* FUN_00481c90 @ 0x00481c90   (est. sk_regex_char_class_match)
 * Ghidra: bool FUN_00481c90(int param_1)
 * True when param_1 is a digit (10..13) OR in {0x2028,0x2029,0x85} (the
 * Unicode line/paragraph separators and NEL). Confidence: high (literal set). */
bool sk_h_481c90(word_t p)
{
    return (p - 10) < 4 || ((p - 0x2028) < 2 || p == 0x85);
}

/* __APPEND__ */


