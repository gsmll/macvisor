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
 * All out-of-range callees are declared as unprototyped externs (AAPCS64:
 * args in x0..x7, result in x0). The 16-byte-return helpers use the
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

/* ------------------------------------------------------------------ *
 * Out-of-range cL4/Swift-runtime helpers referenced by this slice.
 * Unprototyped AAPCS64 externs. sk_r29_pair_t for the 16-byte returns.
 * FUN_ addresses in comments. Names are estimates.
 * ------------------------------------------------------------------ */

extern word_t sk_h_00002534(); /* FUN_00002534 */
extern word_t sk_h_000026e8(); /* FUN_000026e8 */
extern word_t sk_h_00002818(); /* FUN_00002818 */
extern word_t sk_h_00002834(); /* FUN_00002834 */
extern word_t sk_h_00002874(); /* FUN_00002874 */
extern word_t sk_h_00019858(); /* FUN_00019858 */
extern word_t sk_h_0001da84(); /* FUN_0001da84 */
extern word_t sk_h_0001e790(); /* FUN_0001e790 */
extern word_t sk_h_00027724(); /* FUN_00027724 */
extern word_t sk_h_00041138(); /* FUN_00041138 */
extern word_t sk_h_00068e14(); /* FUN_00068e14 */
extern word_t sk_h_0006a374(); /* FUN_0006a374 */
extern sk_r29_pair_t sk_h_0006ae9c(); /* FUN_0006ae9c */
extern word_t sk_h_0006b3f4(); /* FUN_0006b3f4 */
extern word_t sk_h_0006b42c(); /* FUN_0006b42c */
extern word_t sk_h_0006b6f4(); /* FUN_0006b6f4 */
extern word_t sk_h_0006f768(); /* FUN_0006f768 */
extern word_t sk_h_00070594(); /* FUN_00070594 */
extern word_t sk_h_00072c0c(); /* FUN_00072c0c */
extern word_t sk_h_00073524(); /* FUN_00073524 */
extern word_t sk_h_0007767c(); /* FUN_0007767c */
extern sk_r29_pair_t sk_h_00077698(); /* FUN_00077698 */
extern word_t sk_h_000776cc(); /* FUN_000776cc */
extern word_t sk_h_00077888(); /* FUN_00077888 */
extern word_t sk_h_00077894(); /* FUN_00077894 */
extern sk_r29_pair_t sk_h_0007c1c4(); /* FUN_0007c1c4 */
extern sk_r29_pair_t sk_h_0008409c(); /* FUN_0008409c */
extern word_t sk_h_00084174(); /* FUN_00084174 */
extern word_t sk_h_00084180(); /* FUN_00084180 */
extern sk_r29_pair_t sk_h_00084220(); /* FUN_00084220 */
extern word_t sk_h_00084234(); /* FUN_00084234 */
extern word_t sk_h_00084cc4(); /* FUN_00084cc4 */
extern word_t sk_h_00085754(); /* FUN_00085754 */
extern word_t sk_h_000863bc(); /* FUN_000863bc */
extern word_t sk_h_000867ec(); /* FUN_000867ec */
extern word_t sk_h_00086840(); /* FUN_00086840 */
extern word_t sk_h_0008cc7c(); /* FUN_0008cc7c */
extern word_t sk_h_0008e160(); /* FUN_0008e160 */
extern word_t sk_h_0008e388(); /* FUN_0008e388 */
extern word_t sk_h_0008e488(); /* FUN_0008e488 */
extern word_t sk_h_0008e500(); /* FUN_0008e500 */
extern sk_r29_pair_t sk_h_0008e518(); /* FUN_0008e518 */
extern word_t sk_h_00092d40(); /* FUN_00092d40 */
extern word_t sk_h_0009461c(); /* FUN_0009461c */
extern word_t sk_h_000a6e14(); /* FUN_000a6e14 */
extern sk_r29_pair_t sk_h_000a6f68(); /* FUN_000a6f68 */
extern word_t sk_h_000a6fe0(); /* FUN_000a6fe0 */
extern word_t sk_h_000ac00c(); /* FUN_000ac00c */
extern word_t sk_h_000af4d8(); /* FUN_000af4d8 */
extern word_t sk_h_000b430c(); /* FUN_000b430c */
extern word_t sk_h_000b4390(); /* FUN_000b4390 */
extern word_t sk_h_000b43d0(); /* FUN_000b43d0 */
extern word_t sk_h_000b43e8(); /* FUN_000b43e8 */
extern word_t sk_h_000b4594(); /* FUN_000b4594 */
extern word_t sk_h_000b45b0(); /* FUN_000b45b0 */
extern word_t sk_h_000bd3a4(); /* FUN_000bd3a4 */
extern word_t sk_h_000dbbe0(); /* FUN_000dbbe0 */
extern word_t sk_h_000dbc98(); /* FUN_000dbc98 */
extern word_t sk_h_000e0654(); /* FUN_000e0654 */
extern word_t sk_h_000e15d8(); /* FUN_000e15d8 */
extern word_t sk_h_000ec004(); /* FUN_000ec004 */
extern word_t sk_h_000f4a9c(); /* FUN_000f4a9c */
extern word_t sk_h_000f4ae8(); /* FUN_000f4ae8 */
extern word_t sk_h_000f5d30(); /* FUN_000f5d30 */
extern word_t sk_h_000f5e5c(); /* FUN_000f5e5c */
extern word_t sk_h_00100e34(); /* FUN_00100e34 */
extern word_t sk_h_00100efc(); /* FUN_00100efc */
extern word_t sk_h_00106e3c(); /* FUN_00106e3c */
extern word_t sk_h_00117cc4(); /* FUN_00117cc4 */
extern word_t sk_h_0011aa70(); /* FUN_0011aa70 */
extern sk_r29_pair_t sk_h_0011e71c(); /* FUN_0011e71c */
extern word_t sk_h_00136bf8(); /* FUN_00136bf8 */
extern word_t sk_h_00167404(); /* FUN_00167404 */
extern word_t sk_h_0016749c(); /* FUN_0016749c */
extern word_t sk_h_001676cc(); /* FUN_001676cc */
extern word_t sk_h_001a6a8c(); /* FUN_001a6a8c */
extern word_t sk_h_001a84f4(); /* FUN_001a84f4 */
extern word_t sk_h_001a8564(); /* FUN_001a8564 */
extern word_t sk_h_001ae8a8(); /* FUN_001ae8a8 */
extern word_t sk_h_001afa84(); /* FUN_001afa84 */
extern word_t sk_h_001b798c(); /* FUN_001b798c */
extern word_t sk_h_001b9084(); /* FUN_001b9084 */
extern word_t sk_h_001ba7d4(); /* FUN_001ba7d4 */
extern sk_r29_pair_t sk_h_001bc440(); /* FUN_001bc440 */
extern word_t sk_h_001ebfb0(); /* FUN_001ebfb0 */
extern word_t sk_h_001ed960(); /* FUN_001ed960 */
extern word_t sk_h_001ee018(); /* FUN_001ee018 */
extern word_t sk_h_001ee9f4(); /* FUN_001ee9f4 */
extern word_t sk_h_00205844(); /* FUN_00205844 */
extern word_t sk_h_002298d4(); /* FUN_002298d4 */
extern word_t sk_h_0024917c(); /* FUN_0024917c */
extern word_t sk_h_0024d9ac(); /* FUN_0024d9ac */
extern word_t sk_h_00255d4c(); /* FUN_00255d4c */
extern word_t sk_h_0025a094(); /* FUN_0025a094 */
extern word_t sk_h_00267510(); /* FUN_00267510 */
extern word_t sk_h_00267914(); /* FUN_00267914 */
extern word_t sk_h_00294cb4(); /* FUN_00294cb4 */
extern word_t sk_h_0029c058(); /* FUN_0029c058 */
extern sk_r29_pair_t sk_h_0029d3d8(); /* FUN_0029d3d8 */
extern sk_r29_pair_t sk_h_0029d560(); /* FUN_0029d560 */
extern word_t sk_h_0029f368(); /* FUN_0029f368 */
extern sk_r29_pair_t sk_h_0029fa0c(); /* FUN_0029fa0c */
extern sk_r29_pair_t sk_h_0029fb80(); /* FUN_0029fb80 */
extern word_t sk_h_002a0cf8(); /* FUN_002a0cf8 */
extern word_t sk_h_002a49a8(); /* FUN_002a49a8 */
extern word_t sk_h_002a4ab4(); /* FUN_002a4ab4 */
extern word_t sk_h_002a8870(); /* FUN_002a8870 */
extern word_t sk_h_002a9ba8(); /* FUN_002a9ba8 */
extern word_t sk_h_002ab130(); /* FUN_002ab130 */
extern word_t sk_h_002acbb8(); /* FUN_002acbb8 */
extern word_t sk_h_002ace24(); /* FUN_002ace24 */
extern word_t sk_h_002ae098(); /* FUN_002ae098 */
extern word_t sk_h_002ae2c0(); /* FUN_002ae2c0 */
extern word_t sk_h_002b141c(); /* FUN_002b141c */
extern word_t sk_h_002b14c8(); /* FUN_002b14c8 */
extern word_t sk_h_002b3670(); /* FUN_002b3670 */
extern word_t sk_h_002b3b50(); /* FUN_002b3b50 */
extern sk_r29_pair_t sk_h_002b439c(); /* FUN_002b439c */
extern word_t sk_h_002b7088(); /* FUN_002b7088 */
extern word_t sk_h_002b723c(); /* FUN_002b723c */
extern word_t sk_h_002bbf08(); /* FUN_002bbf08 */
extern word_t sk_h_002bc234(); /* FUN_002bc234 */
extern word_t sk_h_002bc5bc(); /* FUN_002bc5bc */
extern word_t sk_h_002bd724(); /* FUN_002bd724 */
extern word_t sk_h_002bd8f0(); /* FUN_002bd8f0 */
extern word_t sk_h_002bd9ac(); /* FUN_002bd9ac */
extern word_t sk_h_002bd9cc(); /* FUN_002bd9cc */
extern word_t sk_h_00310d98(); /* FUN_00310d98 */
extern word_t sk_h_00319808(); /* FUN_00319808 */
extern word_t sk_h_0032b65c(); /* FUN_0032b65c */
extern word_t sk_h_0034a018(); /* FUN_0034a018 */
extern word_t sk_h_0034a3b0(); /* FUN_0034a3b0 */
extern word_t sk_h_0034b3f8(); /* FUN_0034b3f8 */
extern word_t sk_h_0034b848(); /* FUN_0034b848 */
extern word_t sk_h_0034c6d4(); /* FUN_0034c6d4 */
extern word_t sk_h_0034cb88(); /* FUN_0034cb88 */
extern word_t sk_h_0034cc24(); /* FUN_0034cc24 */
extern word_t sk_h_0034cec4(); /* FUN_0034cec4 */
extern word_t sk_h_0034d3d4(); /* FUN_0034d3d4 */
extern word_t sk_h_0034db28(); /* FUN_0034db28 */
extern word_t sk_h_0034eb74(); /* FUN_0034eb74 */
extern word_t sk_h_0034ecc8(); /* FUN_0034ecc8 */
extern word_t sk_h_0034fbb0(); /* FUN_0034fbb0 */
extern word_t sk_h_00350470(); /* FUN_00350470 */
extern word_t sk_h_00350494(); /* FUN_00350494 */
extern word_t sk_h_003504a0(); /* FUN_003504a0 */
extern word_t sk_h_003504ac(); /* FUN_003504ac */
extern word_t sk_h_003504c4(); /* FUN_003504c4 */
extern word_t sk_h_003504d0(); /* FUN_003504d0 */
extern sk_r29_pair_t sk_h_00350518(); /* FUN_00350518 */
extern word_t sk_h_0035053c(); /* FUN_0035053c */
extern word_t sk_h_00350548(); /* FUN_00350548 */
extern word_t sk_h_003505c4(); /* FUN_003505c4 */
extern word_t sk_h_00350600(); /* FUN_00350600 */
extern sk_r29_pair_t sk_h_0035060c(); /* FUN_0035060c */
extern word_t sk_h_00350618(); /* FUN_00350618 */
extern word_t sk_h_00350624(); /* FUN_00350624 */
extern word_t sk_h_00350774(); /* FUN_00350774 */
extern sk_r29_pair_t sk_h_003507e0(); /* FUN_003507e0 */
extern word_t sk_h_0035084c(); /* FUN_0035084c */
extern word_t sk_h_0035089c(); /* FUN_0035089c */
extern word_t sk_h_003508cc(); /* FUN_003508cc */
extern word_t sk_h_003508fc(); /* FUN_003508fc */
extern word_t sk_h_00350914(); /* FUN_00350914 */
extern word_t sk_h_00350968(); /* FUN_00350968 */
extern word_t sk_h_003509b0(); /* FUN_003509b0 */
extern word_t sk_h_003509bc(); /* FUN_003509bc */
extern word_t sk_h_003509c8(); /* FUN_003509c8 */
extern word_t sk_h_003509ec(); /* FUN_003509ec */
extern word_t sk_h_00350af4(); /* FUN_00350af4 */
extern word_t sk_h_00350b18(); /* FUN_00350b18 */
extern word_t sk_h_00350b48(); /* FUN_00350b48 */
extern word_t sk_h_00350bfc(); /* FUN_00350bfc */
extern word_t sk_h_00350c20(); /* FUN_00350c20 */
extern word_t sk_h_00350d94(); /* FUN_00350d94 */
extern word_t sk_h_003510c4(); /* FUN_003510c4 */
extern word_t sk_h_00351124(); /* FUN_00351124 */
extern word_t sk_h_00351130(); /* FUN_00351130 */
extern word_t sk_h_00351178(); /* FUN_00351178 */
extern word_t sk_h_003511a8(); /* FUN_003511a8 */
extern word_t sk_h_003511cc(); /* FUN_003511cc */
extern word_t sk_h_003511f0(); /* FUN_003511f0 */
extern word_t sk_h_00351214(); /* FUN_00351214 */
extern word_t sk_h_00351244(); /* FUN_00351244 */
extern word_t sk_h_00351274(); /* FUN_00351274 */
extern word_t sk_h_00351354(); /* FUN_00351354 */
extern word_t sk_h_0035136c(); /* FUN_0035136c */
extern sk_r29_pair_t sk_h_00351384(); /* FUN_00351384 */
extern word_t sk_h_003513a8(); /* FUN_003513a8 */
extern word_t sk_h_003513b4(); /* FUN_003513b4 */
extern word_t sk_h_00351414(); /* FUN_00351414 */
extern word_t sk_h_00351450(); /* FUN_00351450 */
extern word_t sk_h_00351488(); /* FUN_00351488 */
extern word_t sk_h_00351584(); /* FUN_00351584 */
extern word_t sk_h_003515fc(); /* FUN_003515fc */
extern word_t sk_h_00351774(); /* FUN_00351774 */
extern word_t sk_h_003517c0(); /* FUN_003517c0 */
extern sk_r29_pair_t sk_h_0035193c(); /* FUN_0035193c */
extern word_t sk_h_00351a50(); /* FUN_00351a50 */
extern word_t sk_h_00351aec(); /* FUN_00351aec */
extern word_t sk_h_00351b78(); /* FUN_00351b78 */
extern word_t sk_h_00351bd4(); /* FUN_00351bd4 */
extern word_t sk_h_00351c7c(); /* FUN_00351c7c */
extern word_t sk_h_00351cd0(); /* FUN_00351cd0 */
extern word_t sk_h_00351d18(); /* FUN_00351d18 */
extern word_t sk_h_00351d30(); /* FUN_00351d30 */
extern word_t sk_h_00351db4(); /* FUN_00351db4 */
extern word_t sk_h_00351dfc(); /* FUN_00351dfc */
extern word_t sk_h_00351e08(); /* FUN_00351e08 */
extern sk_r29_pair_t sk_h_00351e20(); /* FUN_00351e20 */
extern word_t sk_h_00351e3c(); /* FUN_00351e3c */
extern word_t sk_h_00351f34(); /* FUN_00351f34 */
extern word_t sk_h_003522c8(); /* FUN_003522c8 */
extern word_t sk_h_00352800(); /* FUN_00352800 */
extern word_t sk_h_00352840(); /* FUN_00352840 */
extern word_t sk_h_00352af0(); /* FUN_00352af0 */
extern word_t sk_h_00352c40(); /* FUN_00352c40 */
extern word_t sk_h_00352c4c(); /* FUN_00352c4c */
extern word_t sk_h_00352c68(); /* FUN_00352c68 */
extern word_t sk_h_00352c80(); /* FUN_00352c80 */
extern word_t sk_h_00352e9c(); /* FUN_00352e9c */
extern word_t sk_h_0035310c(); /* FUN_0035310c */
extern word_t sk_h_003532b8(); /* FUN_003532b8 */
extern word_t sk_h_003535a8(); /* FUN_003535a8 */
extern sk_r29_pair_t sk_h_00353cfc(); /* FUN_00353cfc */
extern word_t sk_h_00353d14(); /* FUN_00353d14 */
extern word_t sk_h_00353ff4(); /* FUN_00353ff4 */
extern word_t sk_h_00354410(); /* FUN_00354410 */
extern word_t sk_h_003544c8(); /* FUN_003544c8 */
extern sk_r29_pair_t sk_h_00354744(); /* FUN_00354744 */
extern word_t sk_h_003548dc(); /* FUN_003548dc */
extern word_t sk_h_00354998(); /* FUN_00354998 */
extern sk_r29_pair_t sk_h_00354a34(); /* FUN_00354a34 */
extern word_t sk_h_00354d5c(); /* FUN_00354d5c */
extern word_t sk_h_00354e0c(); /* FUN_00354e0c */
extern word_t sk_h_00354ef8(); /* FUN_00354ef8 */
extern word_t sk_h_00355754(); /* FUN_00355754 */
extern word_t sk_h_00355da8(); /* FUN_00355da8 */
extern word_t sk_h_00356364(); /* FUN_00356364 */
extern word_t sk_h_00356370(); /* FUN_00356370 */
extern sk_r29_pair_t sk_h_0035638c(); /* FUN_0035638c */
extern word_t sk_h_00356930(); /* FUN_00356930 */
extern word_t sk_h_003577a0(); /* FUN_003577a0 */
extern word_t sk_h_00357c74(); /* FUN_00357c74 */
extern sk_r29_pair_t sk_h_00357cb4(); /* FUN_00357cb4 */
extern word_t sk_h_0035847c(); /* FUN_0035847c */
extern word_t sk_h_003593c0(); /* FUN_003593c0 */
extern word_t sk_h_0035a8d0(); /* FUN_0035a8d0 */
extern sk_r29_pair_t sk_h_0035a9b0(); /* FUN_0035a9b0 */
extern word_t sk_h_0035b67c(); /* FUN_0035b67c */
extern word_t sk_h_00365b6c(); /* FUN_00365b6c */
extern word_t sk_h_0036986c(); /* FUN_0036986c */
extern word_t sk_h_0036a940(); /* FUN_0036a940 */
extern word_t sk_h_0036a9a0(); /* FUN_0036a9a0 */
extern word_t sk_h_0036b118(); /* FUN_0036b118 */
extern word_t sk_h_0036b270(); /* FUN_0036b270 */
extern sk_r29_pair_t sk_h_0039a128(); /* FUN_0039a128 */
extern word_t sk_h_003a25d4(); /* FUN_003a25d4 */
extern word_t sk_h_003a2610(); /* FUN_003a2610 */
extern word_t sk_h_003a261c(); /* FUN_003a261c */
extern word_t sk_h_004080b0(); /* FUN_004080b0 */
extern word_t sk_h_0040fbc0(); /* FUN_0040fbc0 */
extern word_t sk_h_00410e78(); /* FUN_00410e78 */
extern word_t sk_h_0041449c(); /* FUN_0041449c */
extern word_t sk_h_00414644(); /* FUN_00414644 */
extern word_t sk_h_004176bc(); /* FUN_004176bc */
extern sk_r29_pair_t sk_h_00417b60(); /* FUN_00417b60 */
extern word_t sk_h_0041ae04(); /* FUN_0041ae04 */
extern word_t sk_h_0041d778(); /* FUN_0041d778 */
extern word_t sk_h_0041d788(); /* FUN_0041d788 */
extern word_t sk_h_0041d7dc(); /* FUN_0041d7dc */
extern sk_r29_pair_t sk_h_0042ec5c(); /* FUN_0042ec5c */
extern word_t sk_h_00436fc8(); /* FUN_00436fc8 */
extern word_t sk_h_0043f454(); /* FUN_0043f454 */
extern word_t sk_h_00447144(); /* FUN_00447144 */
extern word_t sk_h_0044c9c4(); /* FUN_0044c9c4 */
extern word_t sk_h_0044ca08(); /* FUN_0044ca08 */
extern word_t sk_h_0044ca2c(); /* FUN_0044ca2c */
extern word_t sk_h_0044ca60(); /* FUN_0044ca60 */
extern word_t sk_h_0044cb38(); /* FUN_0044cb38 */
extern word_t sk_h_0044cb90(); /* FUN_0044cb90 */
extern word_t sk_h_0044cc6c(); /* FUN_0044cc6c */
extern word_t sk_h_0044cda0(); /* FUN_0044cda0 */
extern word_t sk_h_0044f098(); /* FUN_0044f098 */
extern word_t sk_h_0044f818(); /* FUN_0044f818 */
extern word_t sk_h_00450878(); /* FUN_00450878 */
extern word_t sk_h_00450adc(); /* FUN_00450adc */
extern word_t sk_h_00451894(); /* FUN_00451894 */
extern word_t sk_h_00451a64(); /* FUN_00451a64 */
extern word_t sk_h_004588cc(); /* FUN_004588cc */
extern word_t sk_h_004589bc(); /* FUN_004589bc */
extern word_t sk_h_004589e8(); /* FUN_004589e8 */
extern word_t sk_h_004589f8(); /* FUN_004589f8 */
extern sk_r29_pair_t sk_h_00458af8(); /* FUN_00458af8 */
extern sk_r29_pair_t sk_h_00458b14(); /* FUN_00458b14 */
extern word_t sk_h_00458c98(); /* FUN_00458c98 */
extern word_t sk_h_004590e0(); /* FUN_004590e0 */
extern word_t sk_h_004629b4(); /* FUN_004629b4 */
extern word_t sk_h_00462aac(); /* FUN_00462aac */
extern word_t sk_h_00462abc(); /* FUN_00462abc */
extern word_t sk_h_00462b6c(); /* FUN_00462b6c */
extern word_t sk_h_00462e9c(); /* FUN_00462e9c */
extern word_t sk_h_00463878(); /* FUN_00463878 */
extern word_t sk_h_00463e04(); /* FUN_00463e04 */
extern sk_r29_pair_t sk_h_00463f94(); /* FUN_00463f94 */
extern word_t sk_h_00464a44(); /* FUN_00464a44 */
extern sk_r29_pair_t sk_h_00464e34(); /* FUN_00464e34 */
extern word_t sk_h_0046511c(); /* FUN_0046511c */
extern word_t sk_h_00465258(); /* FUN_00465258 */
extern word_t sk_h_00465294(); /* FUN_00465294 */
extern word_t sk_h_004657ac(); /* FUN_004657ac */
extern word_t sk_h_00466104(); /* FUN_00466104 */
extern word_t sk_h_00466214(); /* FUN_00466214 */
extern word_t sk_h_00468ee4(); /* FUN_00468ee4 */
extern word_t sk_h_00469c50(); /* FUN_00469c50 */
extern word_t sk_h_00469dc4(); /* FUN_00469dc4 */
extern word_t sk_h_0046a368(); /* FUN_0046a368 */
extern word_t sk_h_0046c4e0(); /* FUN_0046c4e0 */
extern word_t sk_h_004730f0(); /* FUN_004730f0 */
extern word_t sk_h_004731b8(); /* FUN_004731b8 */
extern word_t sk_h_004766ec(); /* FUN_004766ec */
extern word_t sk_h_004769a4(); /* FUN_004769a4 */
extern word_t sk_h_004775d0(); /* FUN_004775d0 */
extern word_t sk_h_004776c4(); /* FUN_004776c4 */
extern word_t sk_h_004811e8(); /* FUN_004811e8 */
extern word_t sk_h_00481510(); /* FUN_00481510 */
extern word_t sk_h_004815ac(); /* FUN_004815ac */
extern sk_r29_pair_t sk_h_004815cc(); /* FUN_004815cc */
extern word_t sk_h_00490174(); /* FUN_00490174 */
extern word_t sk_h_00490600(); /* FUN_00490600 */
extern word_t sk_h_00492704(); /* FUN_00492704 */
extern word_t sk_h_00494ea8(); /* FUN_00494ea8 */
extern word_t sk_h_00494f3c(); /* FUN_00494f3c */
extern word_t sk_h_0049513c(); /* FUN_0049513c */
extern word_t sk_h_00496ef0(); /* FUN_00496ef0 */
extern word_t sk_h_00497224(); /* FUN_00497224 */
extern word_t sk_h_004981d8(); /* FUN_004981d8 */
extern word_t sk_h_00498228(); /* FUN_00498228 */
extern word_t sk_h_00498500(); /* FUN_00498500 */
extern word_t sk_h_00498ad4(); /* FUN_00498ad4 */
extern word_t sk_h_00498b28(); /* FUN_00498b28 */
extern word_t sk_h_00498b7c(); /* FUN_00498b7c */
extern word_t sk_h_00498bdc(); /* FUN_00498bdc */
extern word_t sk_h_00498c1c(); /* FUN_00498c1c */
extern word_t sk_h_00498c84(); /* FUN_00498c84 */
extern word_t sk_h_00498cc8(); /* FUN_00498cc8 */
extern word_t sk_h_00498e50(); /* FUN_00498e50 */
extern word_t sk_h_00499094(); /* FUN_00499094 */
extern word_t sk_h_0049952c(); /* FUN_0049952c */
extern word_t sk_h_00499918(); /* FUN_00499918 */
extern word_t sk_h_00499dbc(); /* FUN_00499dbc */
extern word_t sk_h_00499e1c(); /* FUN_00499e1c */
extern word_t sk_h_00499e94(); /* FUN_00499e94 */
extern sk_r29_pair_t sk_h_00499f6c(); /* FUN_00499f6c */
extern word_t sk_h_0049a058(); /* FUN_0049a058 */
extern word_t sk_h_0049a184(); /* FUN_0049a184 */
extern word_t sk_h_0049a440(); /* FUN_0049a440 */
extern word_t sk_h_0049a454(); /* FUN_0049a454 */
extern word_t sk_h_0049a468(); /* FUN_0049a468 */
extern word_t sk_h_0049a47c(); /* FUN_0049a47c */
extern word_t sk_h_0049a490(); /* FUN_0049a490 */
extern word_t sk_h_0049a530(); /* FUN_0049a530 */
extern word_t sk_h_0049a550(); /* FUN_0049a550 */
extern word_t sk_h_0049a5ac(); /* FUN_0049a5ac */
extern word_t sk_h_0049a82c(); /* FUN_0049a82c */
extern word_t sk_h_0049a91c(); /* FUN_0049a91c */
extern word_t sk_h_0049ab00(); /* FUN_0049ab00 */
extern word_t sk_h_0049c200(); /* FUN_0049c200 */
extern word_t sk_h_0049c4b4(); /* FUN_0049c4b4 */
extern word_t sk_h_0049c52c(); /* FUN_0049c52c */
extern word_t sk_h_0049c5a0(); /* FUN_0049c5a0 */
extern word_t sk_h_0049c5f8(); /* FUN_0049c5f8 */
extern word_t sk_h_0049c838(); /* FUN_0049c838 */
extern word_t sk_h_0049c9fc(); /* FUN_0049c9fc */
extern word_t sk_h_0049ca14(); /* FUN_0049ca14 */
extern word_t sk_h_0049ca2c(); /* FUN_0049ca2c */
extern word_t sk_h_0049ca44(); /* FUN_0049ca44 */
extern word_t sk_h_0049df0c(); /* FUN_0049df0c */
extern word_t sk_h_0049df18(); /* FUN_0049df18 */
extern word_t sk_h_0049e2d4(); /* FUN_0049e2d4 */
extern word_t sk_h_0049e2f0(); /* FUN_0049e2f0 */
extern word_t sk_h_004a31ec(); /* FUN_004a31ec */
extern word_t sk_h_004a31fc(); /* FUN_004a31fc */
extern word_t sk_h_004a3214(); /* FUN_004a3214 */
extern word_t sk_h_004a322c(); /* FUN_004a322c */
extern word_t sk_h_004a34f0(); /* FUN_004a34f0 */
extern word_t sk_h_004a3500(); /* FUN_004a3500 */
extern word_t sk_h_004a3528(); /* FUN_004a3528 */
extern word_t sk_h_004a3550(); /* FUN_004a3550 */
extern word_t sk_h_004a3560(); /* FUN_004a3560 */
extern word_t sk_h_004a36c4(); /* FUN_004a36c4 */
extern word_t sk_h_004a36d4(); /* FUN_004a36d4 */
extern word_t sk_h_004a3918(); /* FUN_004a3918 */
extern word_t sk_h_004a3940(); /* FUN_004a3940 */
extern word_t sk_h_004a42a0(); /* FUN_004a42a0 */
extern word_t sk_h_004a4310(); /* FUN_004a4310 */
extern word_t sk_h_004a463c(); /* FUN_004a463c */
extern word_t sk_h_004a46f0(); /* FUN_004a46f0 */
extern word_t sk_h_004a4724(); /* FUN_004a4724 */
extern word_t sk_h_004a487c(); /* FUN_004a487c */
extern word_t sk_h_004a49a0(); /* FUN_004a49a0 */
extern word_t sk_h_004a49c0(); /* FUN_004a49c0 */
extern word_t sk_h_004a4a34(); /* FUN_004a4a34 */
extern word_t sk_h_004a4aa4(); /* FUN_004a4aa4 */
extern word_t sk_h_004a4ac4(); /* FUN_004a4ac4 */
extern word_t sk_h_004a4b14(); /* FUN_004a4b14 */
extern word_t sk_h_004aa370(); /* FUN_004aa370 */
extern word_t sk_h_004aa38c(); /* FUN_004aa38c */
extern word_t sk_h_004aa3bc(); /* FUN_004aa3bc */
extern word_t sk_h_004aa3fc(); /* FUN_004aa3fc */
extern word_t sk_h_004aa42c(); /* FUN_004aa42c */
extern word_t sk_h_004aa494(); /* FUN_004aa494 */
extern word_t sk_h_004aa4c4(); /* FUN_004aa4c4 */
extern word_t sk_h_004aa514(); /* FUN_004aa514 */
extern word_t sk_h_004aa52c(); /* FUN_004aa52c */
extern word_t sk_h_004aa580(); /* FUN_004aa580 */
extern word_t sk_h_004aa5f8(); /* FUN_004aa5f8 */
extern word_t sk_h_004aa694(); /* FUN_004aa694 */
extern word_t sk_h_004aa6a8(); /* FUN_004aa6a8 */
extern word_t sk_h_004aa794(); /* FUN_004aa794 */
extern word_t sk_h_004aa7a8(); /* FUN_004aa7a8 */
extern word_t sk_h_004aa7bc(); /* FUN_004aa7bc */
extern word_t sk_h_004aa7d0(); /* FUN_004aa7d0 */
extern word_t sk_h_004aa7fc(); /* FUN_004aa7fc */
extern word_t sk_h_004aa824(); /* FUN_004aa824 */
extern word_t sk_h_004aa83c(); /* FUN_004aa83c */
extern word_t sk_h_004aa850(); /* FUN_004aa850 */
extern word_t sk_h_004aa864(); /* FUN_004aa864 */
extern word_t sk_h_004aa890(); /* FUN_004aa890 */
extern word_t sk_h_004aa8f0(); /* FUN_004aa8f0 */
extern word_t sk_h_004aa904(); /* FUN_004aa904 */
extern word_t sk_h_004aa938(); /* FUN_004aa938 */
extern word_t sk_h_004aa990(); /* FUN_004aa990 */
extern word_t sk_h_004aa9a8(); /* FUN_004aa9a8 */
extern word_t sk_h_004aa9f8(); /* FUN_004aa9f8 */
extern word_t sk_h_004aaa20(); /* FUN_004aaa20 */
extern word_t sk_h_004aaa78(); /* FUN_004aaa78 */
extern word_t sk_h_004aaab0(); /* FUN_004aaab0 */
extern word_t sk_h_004aaacc(); /* FUN_004aaacc */
extern word_t sk_h_004aab08(); /* FUN_004aab08 */
extern word_t sk_h_004aab1c(); /* FUN_004aab1c */
extern word_t sk_h_004aab4c(); /* FUN_004aab4c */
extern word_t sk_h_004aab60(); /* FUN_004aab60 */
extern word_t sk_h_004aab74(); /* FUN_004aab74 */
extern word_t sk_h_004aac40(); /* FUN_004aac40 */
extern word_t sk_h_004aacf8(); /* FUN_004aacf8 */
extern word_t sk_h_004aad30(); /* FUN_004aad30 */
extern word_t sk_h_004aad54(); /* FUN_004aad54 */
extern word_t sk_h_004aad94(); /* FUN_004aad94 */
extern word_t sk_h_004aada4(); /* FUN_004aada4 */
extern word_t sk_h_004aadcc(); /* FUN_004aadcc */
extern word_t sk_h_004aade4(); /* FUN_004aade4 */
extern word_t sk_h_004aadfc(); /* FUN_004aadfc */
extern word_t sk_h_004aae2c(); /* FUN_004aae2c */
extern word_t sk_h_004aae64(); /* FUN_004aae64 */
extern word_t sk_h_004aae98(); /* FUN_004aae98 */
extern word_t sk_h_004aaf28(); /* FUN_004aaf28 */
extern word_t sk_h_004aaf58(); /* FUN_004aaf58 */
extern word_t sk_h_004aaf9c(); /* FUN_004aaf9c */
extern word_t sk_h_004aafac(); /* FUN_004aafac */
extern word_t sk_h_004aafd8(); /* FUN_004aafd8 */
extern word_t sk_h_004ab034(); /* FUN_004ab034 */
extern word_t sk_h_004ab044(); /* FUN_004ab044 */
extern word_t sk_h_004ab054(); /* FUN_004ab054 */
extern word_t sk_h_004ab064(); /* FUN_004ab064 */
extern word_t sk_h_004ab080(); /* FUN_004ab080 */
extern word_t sk_h_004ab0ac(); /* FUN_004ab0ac */
extern word_t sk_h_004ab0bc(); /* FUN_004ab0bc */
extern word_t sk_h_004ab0e0(); /* FUN_004ab0e0 */
extern word_t sk_h_004ab0f0(); /* FUN_004ab0f0 */
extern word_t sk_h_004ab178(); /* FUN_004ab178 */
extern word_t sk_h_004ab1a0(); /* FUN_004ab1a0 */
extern word_t sk_h_004ab208(); /* FUN_004ab208 */
extern word_t sk_h_004ab224(); /* FUN_004ab224 */
extern word_t sk_h_004ab260(); /* FUN_004ab260 */
extern word_t sk_h_004ab26c(); /* FUN_004ab26c */
extern word_t sk_h_004ab2a0(); /* FUN_004ab2a0 */
extern word_t sk_h_004ab2d0(); /* FUN_004ab2d0 */
extern word_t sk_h_004ab304(); /* FUN_004ab304 */
extern word_t sk_h_004ab35c(); /* FUN_004ab35c */
extern word_t sk_h_004ab3c4(); /* FUN_004ab3c4 */
extern word_t sk_h_004ab3dc(); /* FUN_004ab3dc */
extern word_t sk_h_004ab408(); /* FUN_004ab408 */
extern word_t sk_h_004ab448(); /* FUN_004ab448 */
extern word_t sk_h_004ab458(); /* FUN_004ab458 */
extern word_t sk_h_004ab468(); /* FUN_004ab468 */
extern word_t sk_h_004ab4a8(); /* FUN_004ab4a8 */
extern word_t sk_h_004ab4e8(); /* FUN_004ab4e8 */
extern word_t sk_h_004ab4f4(); /* FUN_004ab4f4 */
extern word_t sk_h_004ab520(); /* FUN_004ab520 */
extern word_t sk_h_004ab530(); /* FUN_004ab530 */
extern word_t sk_h_004ab55c(); /* FUN_004ab55c */
extern word_t sk_h_004ab568(); /* FUN_004ab568 */
extern word_t sk_h_004ab58c(); /* FUN_004ab58c */
extern word_t sk_h_004ab5a4(); /* FUN_004ab5a4 */
extern word_t sk_h_004ab5c8(); /* FUN_004ab5c8 */
extern sk_r29_pair_t sk_h_004ab60c(); /* FUN_004ab60c */
extern word_t sk_h_004ab618(); /* FUN_004ab618 */
extern word_t sk_h_004ab650(); /* FUN_004ab650 */
extern word_t sk_h_004ab68c(); /* FUN_004ab68c */
extern word_t sk_h_004ab6c4(); /* FUN_004ab6c4 */
extern word_t sk_h_004ab6d8(); /* FUN_004ab6d8 */
extern word_t sk_h_004ab6e8(); /* FUN_004ab6e8 */
extern word_t sk_h_004ab700(); /* FUN_004ab700 */
extern word_t sk_h_004ab724(); /* FUN_004ab724 */
extern word_t sk_h_004ab760(); /* FUN_004ab760 */
extern word_t sk_h_004ab784(); /* FUN_004ab784 */
extern word_t sk_h_004ab798(); /* FUN_004ab798 */
extern word_t sk_h_004ab7b8(); /* FUN_004ab7b8 */
extern word_t sk_h_004ab7cc(); /* FUN_004ab7cc */
extern word_t sk_h_004ab810(); /* FUN_004ab810 */
extern word_t sk_h_004ab820(); /* FUN_004ab820 */
extern word_t sk_h_004ab834(); /* FUN_004ab834 */
extern word_t sk_h_004ab844(); /* FUN_004ab844 */
extern word_t sk_h_004ab858(); /* FUN_004ab858 */
extern word_t sk_h_004ab89c(); /* FUN_004ab89c */
extern word_t sk_h_004ab8c8(); /* FUN_004ab8c8 */
extern word_t sk_h_004ab8dc(); /* FUN_004ab8dc */
extern word_t sk_h_004ab8e8(); /* FUN_004ab8e8 */
extern word_t sk_h_004ab930(); /* FUN_004ab930 */
extern word_t sk_h_004ab944(); /* FUN_004ab944 */
extern word_t sk_h_004ab968(); /* FUN_004ab968 */
extern sk_r29_pair_t sk_h_004ab974(); /* FUN_004ab974 */
extern word_t sk_h_004ab98c(); /* FUN_004ab98c */
extern word_t sk_h_004ab9bc(); /* FUN_004ab9bc */
extern word_t sk_h_004ab9e0(); /* FUN_004ab9e0 */
extern word_t sk_h_004ab9f8(); /* FUN_004ab9f8 */
extern sk_r29_pair_t sk_h_004aba34(); /* FUN_004aba34 */
extern word_t sk_h_004aba88(); /* FUN_004aba88 */
extern word_t sk_h_004abad8(); /* FUN_004abad8 */
extern word_t sk_h_004abaf0(); /* FUN_004abaf0 */
extern word_t sk_h_004abb1c(); /* FUN_004abb1c */
extern word_t sk_h_004abb28(); /* FUN_004abb28 */
extern word_t sk_h_004abb58(); /* FUN_004abb58 */
extern word_t sk_h_004abbac(); /* FUN_004abbac */
extern word_t sk_h_004abbd4(); /* FUN_004abbd4 */
extern word_t sk_h_004abc28(); /* FUN_004abc28 */
extern word_t sk_h_004abc38(); /* FUN_004abc38 */
extern word_t sk_h_004abc78(); /* FUN_004abc78 */
extern sk_r29_pair_t sk_h_004abcb4(); /* FUN_004abcb4 */
extern word_t sk_h_004abcdc(); /* FUN_004abcdc */
extern sk_r29_pair_t sk_h_004abcf8(); /* FUN_004abcf8 */
extern word_t sk_h_004abd20(); /* FUN_004abd20 */
extern word_t sk_h_004abd2c(); /* FUN_004abd2c */
extern word_t sk_h_004abd38(); /* FUN_004abd38 */
extern word_t sk_h_004abd9c(); /* FUN_004abd9c */
extern word_t sk_h_004abdc4(); /* FUN_004abdc4 */
extern word_t sk_h_004abe24(); /* FUN_004abe24 */
extern word_t sk_h_004abe5c(); /* FUN_004abe5c */
extern word_t sk_h_004abe68(); /* FUN_004abe68 */
extern word_t sk_h_004abe74(); /* FUN_004abe74 */
extern word_t sk_h_004abeb0(); /* FUN_004abeb0 */
extern word_t sk_h_004abed0(); /* FUN_004abed0 */
extern word_t sk_h_004abf00(); /* FUN_004abf00 */
extern word_t sk_h_004abf10(); /* FUN_004abf10 */
extern word_t sk_h_004abf20(); /* FUN_004abf20 */
extern word_t sk_h_004abf30(); /* FUN_004abf30 */
extern word_t sk_h_004abf40(); /* FUN_004abf40 */
extern word_t sk_h_004abf5c(); /* FUN_004abf5c */
extern word_t sk_h_004abfa8(); /* FUN_004abfa8 */
extern word_t sk_h_004abfd8(); /* FUN_004abfd8 */
extern word_t sk_h_004abfe8(); /* FUN_004abfe8 */
extern word_t sk_h_004abff8(); /* FUN_004abff8 */
extern word_t sk_h_004ac008(); /* FUN_004ac008 */
extern word_t sk_h_004ac034(); /* FUN_004ac034 */
extern word_t sk_h_004ac0cc(); /* FUN_004ac0cc */
extern word_t sk_h_004ac108(); /* FUN_004ac108 */
extern word_t sk_h_004ac114(); /* FUN_004ac114 */
extern word_t sk_h_004ac120(); /* FUN_004ac120 */
extern word_t sk_h_004ac12c(); /* FUN_004ac12c */
extern sk_r29_pair_t sk_h_004ac144(); /* FUN_004ac144 */
extern word_t sk_h_004ac15c(); /* FUN_004ac15c */
extern word_t sk_h_004ac198(); /* FUN_004ac198 */
extern word_t sk_h_004ac1a4(); /* FUN_004ac1a4 */
extern word_t sk_h_004ac210(); /* FUN_004ac210 */
extern word_t sk_h_004ac258(); /* FUN_004ac258 */
extern word_t sk_h_004ac27c(); /* FUN_004ac27c */
extern word_t sk_h_004ac294(); /* FUN_004ac294 */
extern word_t sk_h_004ac2a0(); /* FUN_004ac2a0 */
extern word_t sk_h_004ac2c4(); /* FUN_004ac2c4 */
extern word_t sk_h_004ac2f4(); /* FUN_004ac2f4 */
extern sk_r29_pair_t sk_h_004ac30c(); /* FUN_004ac30c */
extern word_t sk_h_004ac360(); /* FUN_004ac360 */
extern word_t sk_h_004ac3e4(); /* FUN_004ac3e4 */
extern word_t sk_h_004ac3f0(); /* FUN_004ac3f0 */
extern word_t sk_h_004ac4f0(); /* FUN_004ac4f0 */
extern word_t sk_h_004ac518(); /* FUN_004ac518 */
extern word_t sk_h_004ac52c(); /* FUN_004ac52c */
extern word_t sk_h_004ac55c(); /* FUN_004ac55c */
extern word_t sk_h_004ac574(); /* FUN_004ac574 */
extern word_t sk_h_004ac5a4(); /* FUN_004ac5a4 */
extern word_t sk_h_004ac5b4(); /* FUN_004ac5b4 */
extern word_t sk_h_004ac5c4(); /* FUN_004ac5c4 */
extern word_t sk_h_004ac5ec(); /* FUN_004ac5ec */
extern word_t sk_h_004ac5fc(); /* FUN_004ac5fc */
extern word_t sk_h_004ac634(); /* FUN_004ac634 */
extern word_t sk_h_004ac654(); /* FUN_004ac654 */
extern word_t sk_h_004ac66c(); /* FUN_004ac66c */
extern word_t sk_h_004ac680(); /* FUN_004ac680 */
extern word_t sk_h_004ac698(); /* FUN_004ac698 */
extern word_t sk_h_004ac6f8(); /* FUN_004ac6f8 */
extern word_t sk_h_004ac70c(); /* FUN_004ac70c */
extern word_t sk_h_004ac738(); /* FUN_004ac738 */
extern word_t sk_h_004ac758(); /* FUN_004ac758 */
extern word_t sk_h_004ac76c(); /* FUN_004ac76c */
extern word_t sk_h_004ac778(); /* FUN_004ac778 */
extern word_t sk_h_004ac7b0(); /* FUN_004ac7b0 */
extern sk_r29_pair_t sk_h_004ac7bc(); /* FUN_004ac7bc */
extern word_t sk_h_004ac844(); /* FUN_004ac844 */
extern word_t sk_h_004ac850(); /* FUN_004ac850 */
extern word_t sk_h_004ac8a8(); /* FUN_004ac8a8 */
extern word_t sk_h_004ac8d4(); /* FUN_004ac8d4 */
extern word_t sk_h_004ac8fc(); /* FUN_004ac8fc */
extern word_t sk_h_004ac91c(); /* FUN_004ac91c */
extern word_t sk_h_004ac960(); /* FUN_004ac960 */
extern word_t sk_h_004ac96c(); /* FUN_004ac96c */
extern word_t sk_h_004ac98c(); /* FUN_004ac98c */
extern word_t sk_h_004ac9ac(); /* FUN_004ac9ac */
extern word_t sk_h_004ac9cc(); /* FUN_004ac9cc */
extern word_t sk_h_004ac9f8(); /* FUN_004ac9f8 */
extern word_t sk_h_004aca2c(); /* FUN_004aca2c */
extern word_t sk_h_004aca4c(); /* FUN_004aca4c */
extern word_t sk_h_004aca94(); /* FUN_004aca94 */
extern word_t sk_h_004acb04(); /* FUN_004acb04 */
extern word_t sk_h_004acb58(); /* FUN_004acb58 */
extern word_t sk_h_004acba8(); /* FUN_004acba8 */
extern word_t sk_h_004acbbc(); /* FUN_004acbbc */
extern word_t sk_h_004acc34(); /* FUN_004acc34 */
extern word_t sk_h_004acc5c(); /* FUN_004acc5c */
extern word_t sk_h_004acc84(); /* FUN_004acc84 */
extern word_t sk_h_004acc90(); /* FUN_004acc90 */
extern word_t sk_h_004accb4(); /* FUN_004accb4 */
extern word_t sk_h_004accc0(); /* FUN_004accc0 */
extern word_t sk_h_004accd8(); /* FUN_004accd8 */
extern word_t sk_h_004accfc(); /* FUN_004accfc */
extern word_t sk_h_004acd14(); /* FUN_004acd14 */

/* Data symbols and function-pointer callees. */
extern word_t sk_h_00010004; /* DAT_00010004 data symbol */
extern word_t sk_h_00657728; /* DAT_00657728 data symbol */
extern word_t sk_h_00657d68; /* DAT_00657d68 data symbol */
extern word_t sk_h_00657e58; /* DAT_00657e58 data symbol */
extern word_t sk_h_00657e60; /* DAT_00657e60 data symbol */
extern word_t sk_h_00657e68; /* DAT_00657e68 data symbol */
extern word_t sk_h_00657e70; /* DAT_00657e70 data symbol */
extern word_t sk_h_006888f0; /* DAT_006888f0 data symbol */
extern word_t sk_h_00688af0; /* DAT_00688af0 data symbol */
extern word_t sk_h_00657d20; /* DAT_00657d20 data symbol */
extern word_t sk_h_00657d48; /* DAT_00657d48 data symbol */
extern word_t sk_h_00657d58; /* DAT_00657d58 data symbol */
extern word_t sk_h_00657d78; /* DAT_00657d78 data symbol */
extern word_t sk_h_00657e48; /* DAT_00657e48 data symbol */
extern word_t sk_h_00657e50; /* DAT_00657e50 data symbol */
extern word_t sk_h_006c10b0; /* DAT_006c10b0 data symbol */
extern word_t sk_h_006c10b8; /* DAT_006c10b8 data symbol */
extern word_t sk_h_004a4914(); /* FUN_004a4914 (function pointer callee) */
extern word_t sk_h_000722e8(); /* FUN_000722e8 (function pointer callee) */
extern word_t sk_h_00452c00(); /* FUN_00452c00 (function pointer callee) */
extern word_t sk_h_004a4310(); /* FUN_004a4310 (function pointer callee) */
extern word_t sk_h_004a4724(); /* FUN_004a4724 (function pointer callee) */
extern word_t sk_h_004a4874(); /* FUN_004a4874 (function pointer callee) */
extern word_t sk_h_004a48f0(); /* FUN_004a48f0 (function pointer callee) */
extern word_t sk_h_004a487c(); /* FUN_004a487c (function pointer callee) */
extern word_t sk_h_004a4328(); /* FUN_004a4328 (function pointer callee) */

/* Forward declarations for in-slice helpers (return types match the definitions). */
word_t sk_h_481600();
void sk_h_48169c();
word_t sk_h_4816a8();
word_t sk_h_4816b4();
void sk_h_4816c0();
void sk_h_481700();
void sk_h_481704();
void sk_h_481738();
void sk_h_48173c();
void sk_h_481754();
word_t sk_h_481780();
word_t sk_h_48185c();
void sk_h_4818d8();
void sk_h_481918();
void sk_h_4819ac();
void sk_h_481a38();
word_t sk_h_481ac4();
word_t sk_h_481b40();
word_t sk_h_481b9c();
bool sk_h_481c18();
word_t sk_h_481c60();
bool sk_h_481c90();
void sk_h_481cc0();
word_t sk_h_481f0c();
word_t sk_h_4820f8();
word_t sk_h_482254();
word_t sk_h_4825e4();
void sk_h_48273c();
void sk_h_48285c();
void sk_h_482a84();
void sk_h_482d18();
sk_r29_pair_t sk_h_4832a4();
void sk_h_483490();
void sk_h_483530();
void sk_h_4836a8();
void sk_h_484374();
void sk_h_4846dc();
void sk_h_484910();
void sk_h_484a3c();
word_t sk_h_484aa8();
void sk_h_484b34();
void sk_h_484ca8();
void sk_h_485010();
word_t sk_h_4851b4();
void sk_h_48525c();
void sk_h_4852ac();
word_t sk_h_485ffc();
word_t sk_h_48603c();
sk_r29_pair_t sk_h_4860bc();
void sk_h_4860d8();
word_t sk_h_48610c();
word_t sk_h_486110();
void sk_h_48612c();
void sk_h_4861a0();
void sk_h_48622c();
sk_r29_pair_t sk_h_4862a0();
long sk_h_4863d8();
sk_r29_pair_t sk_h_4867a4();
void sk_h_4870b4();
void sk_h_4870f4();
void sk_h_487210();
void sk_h_487250();
void sk_h_48736c();
void sk_h_4875c8();
void sk_h_487700();
void sk_h_487734();
void sk_h_4877a0();
void sk_h_48788c();
void sk_h_487960();
void sk_h_488828();
void sk_h_488ec8();
bool sk_h_489938();
sk_r29_pair_t sk_h_489ac4();
sk_r29_pair_t sk_h_489b5c();
void sk_h_489c84();
void sk_h_48a0f4();
word_t sk_h_48a110();
sk_r29_pair_t sk_h_48a244();
void sk_h_48a590();
sk_r29_pair_t sk_h_48a670();
void sk_h_48a81c();
void sk_h_48a84c();
bool sk_h_48a8ac();
void sk_h_48a95c();
void sk_h_48a988();
void sk_h_48aa38();
void sk_h_48aa3c();
void sk_h_48aa68();
void sk_h_48aa90();
void sk_h_48aab8();
void sk_h_48aae0();
void sk_h_48ab08();
void sk_h_48abc4();
void sk_h_48ad50();
word_t sk_h_48addc();
void sk_h_48ba64();
void sk_h_48bb04();
void sk_h_48c284();
void sk_h_48c564();
void sk_h_48c644();
void sk_h_48c718();
word_t sk_h_48ce80();
void sk_h_48d400();
bool sk_h_48d554();
long sk_h_48d694();
sk_r29_pair_t sk_h_48d990();
word_t sk_h_48d9f8();
void sk_h_48dddc();
void sk_h_48deb0();
sk_r29_pair_t sk_h_48e570();
void sk_h_48e76c();
void sk_h_48ebd8();
sk_r29_pair_t sk_h_48ee54();
word_t sk_h_48ee9c();
void sk_h_48ef24();
word_t sk_h_48f61c();
void sk_h_48fe4c();
void sk_h_4816c4();
void sk_h_48afec();
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
word_t sk_h_4816a8(word_t p) { return sk_h_004ac518(0xd); }

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

/* FUN_00481cc0 @ 0x00481cc0   (est. sk_regex_advance_cursor)
 * Ghidra: void FUN_00481cc0(void)
 * Advances the regex match cursor (state at unaff_x20+0xb8): if the work
 * vector is empty it flags the "done" marker at +200; otherwise it pops one
 * 0x48-byte record (performing a lookup/traversal, retaining the three
 * referenced objects) and commits the new cursor/range into the state slots at
 * +0x58/+0x60/+0xa0/+0xb0/+0xc0. Two symmetric paths handle tag==1 vs tag==0
 * records. Confidence: medium (register-global state pointer). */
void sk_h_481cc0(word_t x20)
{
    sk_r29_pair_t d = sk_h_0035638c();
    word_t tag = d.lo;
    long *vp = (long *)(x20 + 0xb8);
    long vec = *vp;
    word_t n = *(word_t *)(vec + 0x10);
    if (n == 0) {
        *(unsigned char *)(x20 + 200) = 1;
    } else {
        if (*(char *)(vec + n * 0x48) == 1) {
            sk_h_0049c52c(&(long){0});
            long keep = 0, v10 = 0, v11 = 0, v15 = 0, v16 = 0; char c3 = 0;
            /* reconstructed from the tagged-stack spill below */
            if (1) {
                sk_h_004ab7b8();
                sk_h_004a4b14((word_t)&(long){0});
                long v13 = *vp;
                long total = *(long *)(v13 + 0x10);
                word_t f = sk_h_003a261c(v13);
                if ((f & 1) == 0) v13 = (long)sk_h_0049a468(v13);
                word_t cnt = *(word_t *)(v13 + 0x10);
                if (cnt <= total - 1U) SK_TRAP(0x481f0c);
                unsigned char *slot = (unsigned char *)(v13 + total * 0x48);
                v11 = *(word_t *)(slot + 0x10);
                v10 = *(word_t *)(slot + 0x18);
                keep = *(long *)(slot + 8);
                c3 = slot[1];
                v16 = *(word_t *)(slot - 8);
                v15 = *(word_t *)(slot - 0x10);
                sk_h_00498500(slot + 0x20, cnt - total);
                *(word_t *)(v13 + 0x10) = cnt - 1;
                *vp = v13;
            }
            sk_h_0036b270(keep);
            sk_h_0036b270(v11);
            sk_h_0036b270(v10);
            sk_h_004a3560((word_t)&(long){0});
        } else {
            word_t f = sk_h_003a261c(vec);
            if ((f & 1) == 0) vec = (long)sk_h_0049a468(vec);
            word_t cnt = *(word_t *)(vec + 0x10);
            if (cnt < n) SK_TRAP(0x481f04);
            long slot = vec + (n - 1) * 0x48;
            sk_h_003511a8();
            sk_h_004811e8();
            *vp = vec;
            if (*(word_t *)(vec + 0x10) < n) SK_TRAP(0x481f08);
            word_t v16 = *(word_t *)(slot + 0x20);
            word_t v15 = *(word_t *)(slot + 0x28);
            char c3 = *(char *)(slot + 0x30);
            long keep = *(long *)(slot + 0x50);
            word_t v11 = *(word_t *)(slot + 0x58);
            word_t v10 = *(word_t *)(slot + 0x60);
            sk_h_0036b270(keep);
            sk_h_0036b270(v11);
            sk_h_0036b270(v10);
            tag = tag & 0xffffffff;
            *(word_t *)(x20 + 0x60) = v16;
            if (c3 == 1) v15 = *(word_t *)(x20 + 0x58);
            *(word_t *)(x20 + 0x58) = v15;
            sk_h_0036b118(*(word_t *)(x20 + 0xa0));
            *(word_t *)(x20 + 0xa0) = v11;
            sk_h_0036b118(*(word_t *)(x20 + 0xb0));
            *(word_t *)(x20 + 0xb0) = v10;
            if ((tag & 1) == 0) {
                sk_h_0036b118(*(word_t *)(x20 + 0xc0));
                *(long *)(x20 + 0xc0) = keep;
            } else {
                sk_h_0036b118(keep);
            }
        }
    }
    sk_h_00356370(d.hi);
}

/* FUN_00481f0c @ 0x00481f0c   (est. sk_regex_match_charset_eval)
 * Ghidra: ulong FUN_00481f0c(undefined8 param_1)
 * Evaluates whether the tagged input param_1 matches a character-set. If the
 * "safe-zone" guard ((*x20[2] ^ *x20[0xb]) < 0x4000) holds, returns 1. It then
 * computes a candidate via an address-translation walk (FUN_003504a0 +
 * boundary/table helpers) and classifies it with FUN_00481c90. Confidence:
 * low (register-global + extraout artifacts). */
word_t sk_h_481f0c(word_t p, word_t *x20)
{
    if ((x20[2] ^ x20[0xb]) < 0x4000) return 1;
    word_t base = *x20, k = x20[1];
    sk_h_003504a0(p);
    if (((0) >> 0x34 & 1) == 0) {
        sk_h_0029c058();
        sk_h_003504a0();
        sk_h_00267510();
        sk_h_002bd9cc();
        sk_h_00351d18();
        sk_h_003a25d4();
        return (word_t)((word_t)x20 & 1);
    }
    word_t v = sk_h_002ab130();
    if (v < 0x4000) SK_TRAP(0x4820a8);
    word_t r;
    if ((k >> 0x3c & 1) == 0) {
        if ((k >> 0x3d & 1) == 0) {
            long off;
            if ((base >> 0x3c & 1) == 0) { sk_h_00084180(); off = (long)sk_h_002a9ba8(); }
            else off = (long)((k & 0xfffffffffffffff) + 0x20);
            sk_h_004ab054(off, v);
            if (v == 0x4000 || (long)(v - 0x4000) >= 0) { sk_h_004ab044(); r = -1; }
            else r = (word_t)sk_h_004abf00(-1);
        } else {
            sk_h_004ab0ac();
            sk_h_004ab054();
            if (!(v == 0x4000) && (long)(v - 0x4000) < 0) { r = -1; }
            else { sk_h_004ab044(); r = (word_t)sk_h_004abf00(0); }
        }
    } else {
        sk_h_003504a0();
        sk_h_002ae098();
        r = 0;
    }
    sk_h_003504a0();
    word_t u = sk_h_00167404();
    if ((k >> 0x3c & 1) != 0) {
        sk_h_003504a0(u & 0xffffffffffff0000);
        r = sk_h_002a49a8();
    } else if ((k >> 0x3d & 1) != 0) {
        sk_h_004ab0ac();
        r = sk_h_00355da8((u >> 0x10));
        if (0 <= 0) return sk_h_481c90(r);
        r = sk_h_0034b848();
    } else {
        long off;
        if ((base >> 0x3c & 1) == 0) { sk_h_00084180(); off = (long)sk_h_002a9ba8(); }
        else off = (long)sk_h_00356364();
        r = sk_h_00355da8(off + (u >> 0x10));
        if (0 <= 0) return sk_h_481c90(r);
        r = sk_h_0034b848();
    }
    return sk_h_481c90(r);
}

/* FUN_004820f8 @ 0x004820f8   (est. sk_regex_match_charset_eval2)
 * Ghidra: ulong FUN_004820f8(ulong param_1)
 * Second charset-evaluation entry (mirrors FUN_00481f0c but keys the guard off
 * x20[3] and checks bit 0x34 of param_1 directly). Confidence: low. */
word_t sk_h_4820f8(word_t p, word_t *x20)
{
    if ((x20[3] ^ x20[0xb]) < 0x4000) return 1;
    word_t base = *x20, k = x20[1];
    if ((p >> 0x34 & 1) == 0) {
        sk_h_003504a0();
        sk_h_00267510();
        sk_h_002bd9cc();
        sk_h_00351d18();
        sk_h_003a25d4();
        return (word_t)((word_t)x20 & 1);
    }
    sk_h_003504a0();
    word_t u = sk_h_00167404();
    word_t r;
    if ((k >> 0x3c & 1) != 0) {
        sk_h_003504a0(u & 0xffffffffffff0000);
        r = sk_h_002a49a8();
    } else if ((k >> 0x3d & 1) != 0) {
        sk_h_004ab0ac();
        r = sk_h_00355da8((u >> 0x10));
        if (0 < 0) r = sk_h_0034b848();
    } else {
        long off;
        if ((base >> 0x3c & 1) == 0) { sk_h_00084180(); off = (long)sk_h_002a9ba8(); }
        else off = (long)sk_h_00356364();
        r = sk_h_00355da8(off + (u >> 0x10));
        if (0 < 0) r = sk_h_0034b848();
    }
    return sk_h_481c90(r);
}

/* FUN_00482254 @ 0x00482254   (est. sk_regex_match_alternation)
 * Ghidra: byte FUN_00482254(ulong param_1)
 * Dispatches a match on the alternation/character-class kind selected by
 * FUN_004816a8(param_1 & 0xff). Case 1 performs the charset walk
 * (sk_h_481f0c/4820f8) on the tagged value; cases 4/9/11/12 compare two
 * cursor words; case 5/6 call sk_h_00450878. Illegal kind 0xd traps.
 * Confidence: low (register-global context). */
word_t sk_h_482254(word_t p, word_t *x20)
{
    word_t kind = sk_h_4816a8(p & 0xff);
    switch (kind) {
    case 1: {
        if (x20[3] >> 0xe == x20[0xb] >> 0xe) return 1;
        word_t base = *x20, k = x20[1];
        sk_h_00351384();
        if ((p >> 0x34 & 1) == 0) {
            word_t u = sk_h_001b798c();
            if (x20[3] >> 0xe == u >> 0xe) {
                sk_r29_pair_t q = sk_h_00351384();
                sk_h_00267510(q.lo, q.hi, k);
                word_t r = sk_h_002bd9cc();
                sk_h_003a25d4(0);
                return r & 1;
            }
            return 0;
        }
        word_t v = sk_h_00167404(0, 0, k);
        if ((k >> 0x3c & 1) == 0) {
            v >>= 0x10;
            if ((k >> 0x3d & 1) == 0) {
                long off;
                if ((base >> 0x3c & 1) == 0) { sk_h_003509bc(); off = (long)sk_h_002a9ba8(); }
                else off = (long)((k & 0xfffffffffffffff) + 0x20);
                sk_h_0034b3f8((word_t)*(unsigned char *)(off + v));
                v = (v + 0) * 0x10000;
            } else {
                v = sk_h_002a49a8(0, base, k);
            }
        } else {
            v = sk_h_002a49a8(v, base, k);
        }
        if (x20[3] >> 0xe != v >> 0xe) return 0;
        sk_r29_pair_t q = sk_h_00351384();
        word_t r = sk_h_00167404(q.lo, q.hi, k);
        if ((k >> 0x3c & 1) != 0) r = sk_h_002a49a8(r & 0xffffffffffff0000, base, k);
        return sk_h_481c90(r) & 1;
    }
    case 2: return (x20[3] ^ x20[0xb]) < 0x4000;
    case 3:
        sk_h_00002874(0);  /* s_Unreachable__we_should_have_thro_005e24a0 */
        sk_h_003593c0();
        sk_h_00002818();
        sk_h_001afa84();
    case 4:
        return (x20[0xb] ^ x20[9]) < 0x4000;
    case 5: return sk_h_00450878(x20[0xb], *x20, x20[1]) & 1;
    case 6: return sk_h_00450878(x20[0xb], *x20, x20[1]) ^ 1;
    case 7: sk_h_004abcb4(); sk_h_00117cc4(0, 0, 0xd8); return sk_h_481f0c(p, x20) & 1;
    case 8: sk_h_004abcb4(); sk_h_00117cc4(0, 0, 0xd8); return sk_h_4820f8(p, x20) & 1;
    case 9:
        if ((p >> 0x37 & 1) != 0) { sk_h_004abcb4(); sk_h_00117cc4(0, 0, 0xd8); return sk_h_481f0c(p, x20) & 1; }
        return (x20[0xb] ^ x20[2]) < 0x4000;
    case 10:
        if ((p >> 0x37 & 1) != 0) { sk_h_004abcb4(); sk_h_00117cc4(0, 0, 0xd8); return sk_h_4820f8(p, x20) & 1; }
        return (x20[3] ^ x20[0xb]) < 0x4000;
    case 11: case 12: {
        word_t r;
        if ((p >> 0x36 & 1) == 0) r = sk_h_004ac4f0();
        else { sk_h_004abcb4(); sk_h_00117cc4(0, 0, 0xd8); r = sk_h_4825e4(0, 0, x20); }
        if (kind == 12) r ^= 1;
        return r & 1;
    }
    default:
        SK_TRAP(0x482554);
    }
    return 0;
}

/* FUN_004825e4 @ 0x004825e4   (est. sk_regex_compare_cursors)
 * Ghidra: void FUN_004825e4(void)
 * Compares two cursor words (x20[2] vs x20[3], else the work cursor) and
 * reports equality of their page-frame bits to the trailing FUN_00354ef8.
 * Confidence: low (register-global cursors). */
word_t sk_h_4825e4(word_t p1, word_t p2, word_t *x20)
{
    sk_h_00354a34();
    word_t a = x20[3];
    if (x20[2] >> 0xe == a >> 0xe) { sk_h_00354ef8(0, 0); return 0; }
    word_t cur = x20[0xb];
    if (cur >> 0xe == x20[2] >> 0xe) { sk_h_004ac758(); sk_h_00354ef8(); sk_h_00494f3c(); return 0; }
    sk_h_00350b48(cur);
    word_t r = sk_h_0029c058();
    word_t out = sk_h_00494f3c(r, 0);
    if (cur >> 0xe != a >> 0xe) { sk_h_004ac758(); out ^= sk_h_00494f3c(); }
    sk_h_00354ef8(out & 1, 0);
}

/* FUN_0048273c @ 0x0048273c   (est. sk_regex_advance_range)
 * Ghidra: void FUN_0048273c(...7 args)
 * Advances a (start,end) cursor pair toward param_3: walks the frame table at
 * *param_4 (faulting if exhausted) until the range covers param_3, then writes
 * the new pair through param_5. Confidence: low (complex bounds walk). */
void sk_h_48273c(word_t p1, word_t p2, word_t p3, long *p4, word_t *p5, word_t p6, word_t p7)
{
    sk_r29_pair_t d = sk_h_00077698();
    word_t lo = d.lo >> 0xe;
    if (lo != d.hi >> 0xe && lo != p3 >> 0xe) {
        long l = *p4;
        if (l != 0) { sk_h_003508fc(); if ((sk_h_48a8ac(0, 0) & 1) != 0) goto done1; }
        word_t cur = *p5, flag = p5[1];
        if ((char)flag != 1 && lo < cur >> 0xe) { sk_h_0007767c(0, 0); return; }
        if (l == 0) *p4 = (long)&sk_h_006577e0;
        if ((char)flag == 1) cur = d.hi;
        for (;;) {
            if (p3 >> 0xe <= cur >> 0xe || lo < cur >> 0xe) {
                *p5 = cur;
                *(unsigned char *)(p5 + 1) = 0;
                if (*p4 != 0) { sk_h_0007767c(d.lo, *p4); sk_h_48a8ac(0, 0); return; }
                SK_TRAP(0x48285c);
            }
            if (*p4 == 0) SK_TRAP(0x482858);
            word_t f = sk_h_0049a91c((word_t)&(long){0}, cur);
            if ((f & 1) == 0) break;
            sk_r29_pair_t q = sk_h_00350518();
            cur = sk_h_002b3670(q.lo, q.hi, p7);
        }
    }
done1:
    sk_h_0007767c(1, 0);
}

/* FUN_0048285c @ 0x0048285c   (est. sk_regex_lookup_forward)
 * Ghidra: void FUN_0048285c(...5 args)
 * Performs a forward lookup of the range at param_3..(cursor) using the tagged
 * parameters param_4/param_5 (address translation). On the non-annotation
 * path it walks the frame table; on the annotated path it decodes a scalar and
 * reports whether the cursor moved. Confidence: low (register-global extras). */
void sk_h_48285c(word_t p1, word_t p2, word_t p3, word_t p4, word_t p5)
{
    sk_r29_pair_t d = sk_h_00357cb4();
    word_t lo = d.lo >> 0xe, hi = d.hi >> 0xe;
    word_t out = 0, flag = 1;
    if ((p3 & 1) == 0) {
        if (lo < hi) {
            word_t u = p4;
            sk_h_0011aa70();
            word_t v = sk_h_001b798c();
            if (hi < v >> 0xe) {
                sk_h_0008e388(); sk_h_0035053c(); sk_h_0029fa0c(); sk_h_004ac76c();
                if (0 == 0) {
                    sk_h_003a25d4(u);
                    out = 0; flag = 1;
                } else {
                    sk_r29_pair_t q = sk_h_004ac30c();
                    sk_h_002b439c(q.lo, q.hi, 0, p5, u);
                    sk_h_00352c80();
                    sk_h_003a25d4(u);
                    sk_h_0011aa70();
                    sk_h_00267510();
                    sk_h_00352c80();
                    sk_h_00084180();
                    sk_h_002bd9cc();
                    sk_h_00351d18();
                    sk_h_003a25d4();
                    if ((p4 & 1) != 0) { out = 0; flag = 1; }
                    else { out = 0; flag = 0; }
                }
            } else {
                sk_h_0011aa70(); sk_h_00267510(); sk_h_00352c80();
                out = 0; flag = 0;
            }
        } else { out = 0; flag = 1; }
    } else {
        if (hi <= lo) { out = 0; flag = 1; }
        else {
            sk_h_0011aa70();
            word_t u = sk_h_00167404();
            word_t r;
            if ((p5 >> 0x3c & 1) != 0) { sk_h_00350624(u & 0xffffffffffff0000); r = sk_h_002a49a8(); }
            else if ((p5 >> 0x3d & 1) != 0) { sk_h_004aad94(); r = sk_h_00355da8((u >> 0x10)); }
            else {
                long off;
                if ((p4 >> 0x3c & 1) == 0) { sk_h_0007c1c4(); off = (long)sk_h_002a9ba8(); }
                else off = (long)sk_h_00356364();
                r = sk_h_00355da8(off + (u >> 0x10));
            }
            r = sk_h_481c90(r);
            if ((r & 1) == 0) {
                sk_h_0011aa70();
                word_t u2 = sk_h_00167404();
                word_t off;
                if ((p5 >> 0x3c & 1) == 0) {
                    u2 >>= 0x10;
                    if ((p5 >> 0x3d & 1) == 0) {
                        long o;
                        if ((p4 >> 0x3c & 1) == 0) { sk_h_0007c1c4(); o = (long)sk_h_002a9ba8(); }
                        else o = (long)sk_h_00356364();
                        sk_h_0034b3f8((word_t)*(unsigned char *)(o + u2));
                        out = (u2 + 0) * 0x10000 | 5;
                    } else {
                        sk_h_00350624();
                        out = sk_h_002a49a8();
                    }
                    flag = 0;
                } else {
                    sk_h_00350624();
                    out = sk_h_002a49a8();
                    flag = 0;
                }
            } else { out = 0; flag = 1; }
        }
    }
    sk_h_00357c74(out, flag, 0);
}

/* FUN_00482a84 @ 0x00482a84   (est. sk_regex_parse_escape)
 * Ghidra: void FUN_00482a84(...4 args)
 * Parses an escape sequence beginning at the cursor: reads a byte, follows
 * frame translation, and recognises escape/continuation pairs (e.g. \r\n) and
 * property lookups, reporting the matched scalar and count to FUN_00354ef8.
 * Confidence: low (register-global + carry artifacts). */
void sk_h_482a84(word_t p1, word_t p2, word_t p3, word_t p4)
{
    sk_r29_pair_t d = sk_h_00354a34();
    word_t hi = d.hi >> 0xe;
    word_t out = 0, cnt = 2;
    if (hi != d.lo >> 0xe) {
        word_t flags = sk_h_00077888();
        word_t sel = (p3 >> 0x20) >> 0x1b & 1;
        if ((p4 & 0x1000000000000000) == 0) sel = 1;
        word_t mask = (word_t)4 << sel;
        word_t is4 = (flags & 0xc) == mask;
        if (is4) { sk_h_0011aa70(); sk_h_0001da84(); }
        word_t cap = sk_h_004abed0();
        word_t lim = is4 ? 0 : 0;
        cap >>= 0x10;
        if (lim <= cap) SK_TRAP(0x482b3c);
        word_t b = *(unsigned char *)(0 + cap);
        word_t first = b;
        if (0 < (char)b) {
            long p;
            if ((flags & 0xc) == mask) { sk_h_0011aa70(); p = (long)sk_h_0001da84(); }
            else p = (long)&sk_h_00010004 + (flags & 0xffffffffffff0000);
            if (hi == (word_t)p >> 0xe) { out = 0; cnt = 2; }
            else {
                word_t c2 = *(unsigned char *)(0 + ((word_t)p >> 0x10));
                if ((first & 0xff) == 0xd && c2 == 10) {
                    long q;
                    if ((flags & 0xc) == mask) { sk_h_0011aa70(); q = (long)sk_h_0001da84(); }
                    else q = (long)&sk_h_00010004 + ((word_t)p & 0xffffffffffff0000);
                    if (hi != (word_t)q >> 0xe) {
                        word_t c3 = *(unsigned char *)(0 + ((word_t)q >> 0x10));
                        if (c3 > 0xcb) { out = 0; cnt = 2; }
                        else { out = 1; cnt = 0xd; }
                    } else { out = 1; cnt = 0xd; }
                } else if (c2 > 0xcb) { out = 0; cnt = 2; }
                else { out = 0; cnt = 2; }
            }
        } else {
            out = 0; cnt = 0;  /* high-bit byte: continuation */
        }
    } else { out = 0; cnt = 2; }
    sk_h_00354ef8(out & 0xff, 0, cnt, 0);
}

/* FUN_00482d18 @ 0x00482d18   (est. sk_regex_decode_utf8_seq)
 * Ghidra: void FUN_00482d18(...8 args)
 * Decodes a multi-byte UTF-8 sequence at the cursor: reads the lead byte,
 * selects the 2/3/4-byte continuation based on its tag bits, combines the
 * continuation bytes into a scalar, and reports it. Confidence: low (carry
 * artifacts). */
void sk_h_482d18(word_t p1, word_t p2, word_t p3, word_t p4, word_t p5, word_t p6, word_t p7, word_t p8)
{
    sk_r29_pair_t d = sk_h_00351e20();
    word_t hi = d.hi;
    word_t end = p3 >> 0xe;
    if (end <= hi >> 0xe) { sk_h_00351d30(0, 1, 0); return; }
    word_t u = p4, v = p5;
    word_t cap = sk_h_001b798c(hi, p7, p8);
    if (end < cap >> 0xe) {
        sk_h_00351414(); sk_h_00351b78(); sk_h_0029fa0c(); sk_h_004ac76c();
        if (0 == 0) { sk_h_003a25d4(u); sk_h_00351d30(0, 1, 0); return; }
        sk_r29_pair_t q = sk_h_004ac30c();
        sk_h_002b439c(q.lo, q.hi, 0, v, u);
        sk_h_003a25d4(u);
    } else {
        sk_h_00077894(hi); sk_h_00267510();
    }
    sk_h_00077894(hi);
    word_t b = sk_h_00167404();
    word_t r;
    if ((p8 >> 0x3c & 1) != 0) { sk_h_00077894(b & 0xffffffffffff0000); r = sk_h_002a49a8(); }
    else if ((p8 >> 0x3d & 1) != 0) {
        unsigned char by = *(unsigned char *)(0 + (b >> 0x10));
        r = (word_t)by;
    } else {
        long off;
        if ((p7 >> 0x3c & 1) == 0) { sk_h_00100efc(); off = (long)sk_h_002a9ba8(); }
        else off = (long)sk_h_003577a0();
        r = (word_t)*(unsigned char *)(off + (b >> 0x10));
    }
    /* select continuation length from the lead byte's top bits */
    if (r < 0x80) { /* 1-byte */ }
    else if (r < 0xe0) { r = ((r & 0x1f) << 6) | 0; }
    else if (r < 0xf0) { r = ((r & 0xf) << 0xc) | 0; }
    else { r = ((r & 0xf) << 0x12) | 0; }
    if ((p6 & 1) == 0) {
        /* continuation capture path */
        r = sk_h_481c90(r);
    }
    if ((p5 & 1) != 0) {
        r = sk_h_481c90(r);
    }
    sk_h_00351d30(r, 0, 0);
}

/* FUN_004832a4 @ 0x004832a4   (est. sk_regex_classify_char)
 * Ghidra: undefined1[16] FUN_004832a4(char param_1, ...)
 * Classifies a character into a regex class: 2=digit, 3=whitespace (space/tab),
 * 4/5=word/identifier (alphanumeric/underscore), 6=extended-class, 7=ASCII
 * identifier. Returns {class-result, scalar}. Confidence: high (classical
 * classifier). */
sk_r29_pair_t sk_h_4832a4(word_t c, word_t p2, word_t p3, word_t p4, word_t p5, word_t p6)
{
    sk_h_00106e3c();
    sk_h_482a84(0, 0, 0, 0);
    sk_r29_pair_t d = sk_h_004ac144();
    word_t scalar = d.lo, cls = d.hi;
    word_t out = 1;
    switch (c) {
    case 2: out = (scalar - 0x30 < 10); break;
    case 3: out = (scalar == 0x20 || scalar == 9); break;
    case 4: case 5:
        if (d.lo - 10 < 4) { out = 0; break; }
        if (!((p4 & 1) && (p5 & 1)) || c != 5) break;
        out = 1;
        break;
    case 6:
        out = 0;
        if (0x20 < d.lo || (1L << (scalar & 0x3f) & 0x100003e00) == 0 || !(p4 & 1) || !(p5 & 1))
            break;
        out = 1;
        break;
    case 7: {
        word_t v = (scalar == 0x5f || scalar - 0x41 < 0x1a);
        if (scalar - 0x30 < 10 || scalar - 0x61 < 0x1a) v = 1;
        out = v;
        break;
    }
    }
    d.hi = out;
    d.lo = scalar;
    return d;
}

/* FUN_00483490 @ 0x00483490   (est. sk_regex_store_capture_result)
 * Ghidra: void FUN_00483490(ulong param_1)
 * Stores the result of a capture: asserts the invariant flag (x20[8]) is clear,
 * then if param_1 is within the cap at x20[7] records the range {x20[7],
 * param_1} and resets the 8-slot capture state, marking done at x20[8]=1.
 * Confidence: medium. */
void sk_h_483490(word_t p1, word_t *x20)
{
    if ((char)x20[8] == 1) { sk_h_00002874(0); sk_h_003593c0(); sk_h_00002818(); sk_h_001afa84(); }
    if (x20[7] >> 0xe <= p1 >> 0xe) {
        *x20 = x20[7];
        x20[1] = p1;
        *(unsigned char *)(x20 + 2) = 0;
        sk_h_0034cc24();
        sk_h_004a4b14((word_t)(x20 + 3));
        x20[4] = 0; x20[3] = 0; x20[6] = 0; x20[5] = 0; x20[7] = 0;
        *(unsigned char *)(x20 + 8) = 1;
        return;
    }
    SK_TRAP(0x4834f8);
}

/* FUN_00483530 @ 0x00483530   (est. sk_regex_dump_subpatterns)
 * Ghidra: void FUN_00483530(void)
 * Prints the subpattern/group list held at *x20+0x20: iterates the entries,
 * emitting "--" + a kind tag, and for tagged entries prints the referenced
 * subpattern recursively. Confidence: low (register-global list). */
void sk_h_483530(word_t *x20)
{
    word_t u4 = sk_h_0035193c().lo;
    word_t i = 0;
    word_t total = *(word_t *)(*x20 + 0x10);
    long base = *x20 + 0x20;
    for (;;) {
        if (total == i) { sk_h_00351774(0, 0xe000000000000000, u4); return; }
        word_t e = *(word_t *)(base + i * 8);
        sk_h_004629b4();
        word_t s = sk_h_00027724(0);
        sk_h_003504ac(s);
        sk_h_4867a4(e);
        word_t kind = sk_h_4816b4() & 0xff;
        if (kind - 0x11 < 2 || kind == 4) {
            if (total <= (e & 0xffffffffffffff)) SK_TRAP(0x4836a0);
            sk_h_4867a4(*(word_t *)(base + (e & 0xffffffffffffff) * 8));
            sk_h_004ac0cc();
            sk_h_003a25d4(e);
        } else if (kind == 0x1e) {
            SK_TRAP(0x4836a4);
        }
        i++;
    }
}

/* FUN_004836a8 @ 0x004836a8   (est. sk_regex_scan_alternation_branch)
 * Ghidra: void FUN_004836a8(void)
 * Scans the current alternation branch: decodes the tag byte at x20[0xf] to
 * pick a scanning strategy (boundary walk vs. charset match vs. UTF-8 decode),
 * iterates the cursor forward through the region [x20[0xb], x20[0xc]) until a
 * terminator, and commits a 0x50-byte result record when the branch matched.
 * Confidence: low (large register-global state machine). */
void sk_h_4836a8(word_t p1, word_t *x20)
{
    sk_r29_pair_t d = sk_h_0035638c();
    word_t tag = d.lo;
    word_t sel = tag >> 0x1b & 0xff;
    word_t limit = sk_h_004815ac();
    word_t kind = sk_h_481600(tag);
    word_t hascc = tag & 0x4000000000;
    word_t ok = 0;
    word_t cur = 0, keep = 0;
    /* single-letter scan loop following the decompiler's cursor-advance pattern */
    word_t s = (tag & 0x7fc0000) == 0x40000;
    word_t sel0 = (sel & 0xff) != 0, sel1 = (sel & 0xff) == 1;
    word_t selm = 0;
    if (sel1) selm = 1; else if (!sel0) selm = 0;
    switch (sk_h_004815cc(tag).lo) {
    case 1:
        keep = x20[0xb];
        cur = sk_h_004ab8dc(keep);
        for (;;) {
            word_t c2 = cur;
            if (0 <= (long)(word_t)0) { if (limit <= (word_t)0) goto done1; }
            sk_h_004aafd8();
            cur = sk_h_00351db4();
            break;
        }
        ok = 1;
        break;
    case 2:
        keep = sk_h_0034eb74(*x20 & 0xffffffffffff, x20[0xb]);
        cur = keep;
        for (;;) {
            word_t c2 = cur;
            if (c2 >> 0xe <= (x20[10] >> 0xe)) break;
            if ((tag & 1) == 0) {
                sk_h_003511f0(c2, x20[10]);
                sk_h_482a84(0, 0, 0, 0);
                sk_r29_pair_t q = sk_h_004ac144();
                cur = q.hi;
                if (q.lo - 10 < 4) break;
            } else if (hascc == 0) {
                sk_h_0034d3d4();
                cur = sk_h_001b798c();
            } else {
                cur = c2;
            }
        }
        ok = 1;
        break;
    case 3:
        if (kind == 8) SK_TRAP(0x48435c + 0);  /* unused variant guard */
        keep = x20[10];
        cur = sk_h_004ab8dc(x20[0xb]);
        for (;;) {
            word_t c2 = cur;
            if (c2 >> 0xe < keep >> 0xe) {
                sk_h_4832a4(0,0,0,0,0,0);
                cur = sk_h_004ac7bc().lo;
            } else break;
        }
        ok = 1;
        break;
    default:
        ok = 0;
    }
done1:
    if (!ok) { sk_h_481cc0(0); }
    x20[0xb] = cur;
    sk_h_00356370(ok, d.hi);
}

/* FUN_00484374 @ 0x00484374   (est. sk_regex_match_scalar_or_escape)
 * Ghidra: void FUN_00484374(...8 args)
 * Matches a scalar/escape at the cursor. When the class kind is 2 it walks the
 * frame table; otherwise it decodes the scalar, applies the case-insensitive
 * matcher FUN_00485ffc, and reports the consumed range. Confidence: low. */
void sk_h_484374(word_t p1, word_t p2, word_t p3, word_t p4, word_t p5, word_t p6, word_t p7, word_t p8)
{
    sk_r29_pair_t d = sk_h_00077698();
    word_t u7 = p7, u8 = p8, u5 = p5;
    sk_h_482a84(p4, p5, p7, p8);
    word_t kind = d.lo;
    word_t out = 0, flag = 1;
    if ((u7 & 0xff) != 2) {
        word_t r = sk_h_0049513c();
        flag = (kind ^ r) & 1;
        if (!((kind ^ r) & 1) || (u7 & 1) == 0) {
            /* match failed */
            out = 0; flag = 1;
        }
    } else {
        word_t end = p5 >> 0xe;
        if (end <= p4 >> 0xe) { out = 0; flag = 1; }
        else {
            word_t v = sk_h_00167404();
            word_t r;
            if ((p8 >> 0x3c & 1) != 0) { sk_h_00350624(v & 0xffffffffffff0000); r = sk_h_002a49a8(); }
            else if ((p8 >> 0x3d & 1) != 0) { sk_h_004aad94(); r = sk_h_00355da8((v >> 0x10)); }
            else {
                long off;
                if ((p7 >> 0x3c & 1) == 0) { sk_h_0007c1c4(); off = (long)sk_h_002a9ba8(); }
                else off = (long)sk_h_00356364();
                r = sk_h_00355da8(off + (v >> 0x10));
            }
            r = sk_h_485ffc(r, kind & 1, d.hi, p3);
            if ((r & 1) == 0) { out = 0; flag = 1; }
            else { out = 5; flag = 0; }
        }
    }
    sk_h_0007767c(out, flag & 1, 0);
}

/* FUN_004846dc @ 0x004846dc   (est. sk_regex_consume_capture)
 * Ghidra: void FUN_004846dc(...7 args)
 * Consumes a capture reference: computes the target frame via address
 * translation and, when the capture list matches (or after advancing the
 * capture index), emits the matched subrange. Confidence: low. */
void sk_h_4846dc(word_t p1, word_t p2, word_t p3, word_t p4, word_t p5, word_t p6, word_t p7)
{
    sk_r29_pair_t d = sk_h_00354744();
    word_t hi = d.hi;
    word_t out = 0, flag = 1;
    if (p3 >> 0xe <= hi >> 0xe) { sk_h_003544c8(out, flag, 0); return; }
    word_t v = sk_h_00167404(hi, p6, p7);
    word_t r;
    if ((p7 >> 0x3c & 1) != 0) { sk_h_00350624(v & 0xffffffffffff0000); r = sk_h_002a49a8(); }
    else if ((p7 >> 0x3d & 1) != 0) { sk_h_004aad94(); r = sk_h_00355da8((v >> 0x10)); }
    else {
        long off;
        if ((p6 >> 0x3c & 1) == 0) { sk_h_0007c1c4(); off = (long)sk_h_002a9ba8(); }
        else off = (long)sk_h_00356364();
        r = sk_h_00355da8(off + (v >> 0x10));
    }
    if ((p5 & 1) == 0) {
        if (r == d.lo) { flag = 0; }
        else { out = 0; flag = 1; }
    } else {
        sk_r29_pair_t a = sk_h_0029d560();
        sk_r29_pair_t b = sk_h_0029d560(d.lo);
        word_t bh = b.hi;
        if (a.lo == b.lo && a.hi == b.hi) {
            sk_h_003a25d4(a.hi);
            sk_h_003a25d4(bh);
        } else {
            sk_h_00350618(b.lo, bh, b.lo);
            word_t m = sk_h_002a0cf8();
            sk_h_003a25d4(a.hi);
            sk_h_003a25d4(bh);
            if ((m & 1) == 0) { out = 0; flag = 1; goto fin; }
        }
        sk_h_00350624(d.lo);
        word_t u = sk_h_00167404();
        word_t off;
        if ((p7 >> 0x3c & 1) == 0) {
            u >>= 0x10;
            if ((p7 >> 0x3d & 1) == 0) {
                long o;
                if ((p6 >> 0x3c & 1) == 0) { sk_h_0007c1c4(); o = (long)sk_h_002a9ba8(); }
                else o = (long)sk_h_00356364();
                sk_h_0034b3f8((word_t)*(unsigned char *)(o + u));
                out = (u + 0) * 0x10000 | 5;
            } else { sk_h_004aad94(); out = (u + 0) * 0x10000 | 5; }
        } else { sk_h_00350624(); out = sk_h_002a49a8(); }
        if ((p4 & 1) != 0) {
            sk_h_00350624(out);
            word_t chk = sk_h_00450878();
            if ((chk & 1) == 0) { out = 0; flag = 1; goto fin; }
        }
        flag = 0;
    }
fin:
    sk_h_003544c8(out, flag, 0);
}

/* FUN_00484910 @ 0x00484910   (est. sk_regex_commit_match)
 * Ghidra: void FUN_00484910(...3 args)
 * Commits a completed match into the state at unaff_x20: stores the tag values,
 * prunes the hash-table work vector at +0xb8 (either rehashing or trimming),
 * drains the 0x48-element record vector at +0xc0 via FUN_004a4aa4, and clears
 * the done flag. Confidence: low. */
void sk_h_484910(word_t p1, word_t p2, word_t p3, word_t x20)
{
    sk_r29_pair_t d = sk_h_0035a9b0();
    *(long *)(x20 + 0x48) = d.hi;
    *(word_t *)(x20 + 0x50) = p3;
    *(long *)(x20 + 0x58) = d.lo;
    *(word_t *)(x20 + 0x60) = 0;
    sk_h_484a3c(x20);
    long *vp = (long *)(x20 + 0xb8);
    if (*(long *)(*vp + 0x10) != 0) {
        word_t f = sk_h_003a261c();
        long vec = *vp;
        if (f == 0) {
            long nb = (long)sk_h_004981d8(0, *(word_t *)(vec + 0x18) >> 1, (word_t)&sk_h_00657d68, 0);
            sk_h_0036b118(vec);
            *vp = nb;
        } else {
            sk_h_0049c200(0, *(word_t *)(vec + 0x10));
        }
    }
    long vec2 = *(long *)(x20 + 0xc0);
    word_t n2 = *(word_t *)(vec2 + 0x10);
    if (n2 != 0) {
        word_t f = sk_h_003a261c(vec2);
        if ((f & 1) == 0) vec2 = (long)sk_h_0049a490(vec2);
        word_t i = 0;
        long e = vec2 + 0x20;
        do {
            if (*(word_t *)(vec2 + 0x10) <= i) SK_TRAP(0x484a3c);
            i++;
            sk_h_004a4aa4(e);
            e += 0x48;
        } while (n2 != i);
        *(long *)(x20 + 0xc0) = vec2;
    }
    *(unsigned char *)(x20 + 200) = 0;
    sk_h_0036b118(*(word_t *)(x20 + 0xd0));
    *(word_t *)(x20 + 0xd0) = 0;
    sk_h_0035a8d0(0);
}

/* FUN_00484a3c @ 0x00484a3c   (est. sk_regex_flush_if_done)
 * Ghidra: void FUN_00484a3c(void)
 * If the done flag at +0x30 is set, flushes the pending capture. Confidence: low. */
void sk_h_484a3c(word_t x20)
{
    if (*(char *)(x20 + 0x30) == 1) {
        sk_h_48612c(0);
        sk_h_4861a0((word_t)&sk_h_00688af0);
        sk_h_000026e8((word_t)&sk_h_00688af0);
        sk_h_48622c(0xf);
    }
}

/* FUN_00484aa8 @ 0x00484aa8   (est. sk_regex_advance_capture_idx)
 * Ghidra: undefined8 FUN_00484aa8(long param_1)
 * Advances the capture index stored at +0x58, returning 1 on success or 0
 * (after flushing) when the range is exhausted. Confidence: low. */
word_t sk_h_484aa8(word_t p1, word_t x20)
{
    word_t cur = *(word_t *)(x20 + 0x58);
    sk_h_00350470(); sk_h_003515fc(); sk_h_0029f368();
    word_t nxt = sk_h_00351db4();
    if (p1 == 1) {
        sk_h_003515fc(cur, 1);
        sk_h_002ae2c0();
        nxt = sk_h_00351db4();
    }
    *(word_t *)(x20 + 0x58) = nxt;
    return 1;
}

/* FUN_00484b34 @ 0x00484b34   (est. sk_regex_consume_capture_range)
 * Ghidra: void FUN_00484b34(...5 args)
 * Consumes the next capture range: advances the cursor at +0x58 toward the
 * limit at +0x50, growing/merging the range vector, and reports success.
 * Confidence: low. */
void sk_h_484b34(word_t p1, word_t p2, word_t p3, word_t p4, word_t p5, word_t x20)
{
    sk_h_0008e518();
    word_t cur = *(word_t *)(x20 + 0x58);
    word_t lim = *(word_t *)(x20 + 0x50) >> 0xe;
    word_t flag = 0;
    if (cur >> 0xe < lim) {
        sk_h_003509ec();
        word_t u3 = *(word_t *)(x20 + 8);
        sk_h_00352840(cur);
        word_t cap = sk_h_001b798c();
        if (lim < cap >> 0xe) {
            sk_h_00351214(cur); sk_h_0029fa0c(); sk_h_004ac76c();
            if (0 != 0) {
                sk_r29_pair_t q = sk_h_004ac30c();
                sk_h_002b439c(q.lo, q.hi, 0, p5, u3);
                sk_h_003a25d4(u3);
                flag = 1;
                goto fin;
            }
            sk_h_003a25d4(u3);
        } else {
            sk_h_00352840(cur);
            sk_h_00267510();
        }
    }
    sk_h_481cc0(0);
    flag = 0;
fin:
    sk_h_0008e500(flag, 0);
}

/* FUN_00484ca8 @ 0x00484ca8   (est. sk_regex_iterate_token_tree)
 * Ghidra: void FUN_00484ca8(void)
 * Iterates a token tree: while the "safe zone" (x22^x23 < 0x4000) is not
 * entered, decodes the next token and either follows a frame reference or
 * recurses via FUN_00068e14/FUN_0048d9f8-style traversal. Confidence: low
 * (register-global iteration). */
void sk_h_484ca8(word_t x3, word_t x4, word_t x5, word_t w6, word_t x7, word_t x22, word_t x23)
{
    sk_h_000b4594();
    word_t u7 = sk_h_0035089c();
    word_t end = x5 >> 0xe;
    if ((w6 & 1) == 0) {
        while ((x23 ^ x22) >= 0x4000) {
            sk_r29_pair_t d = sk_h_002b439c(x23, u7);
            word_t dh = d.hi;
            sk_h_003508cc(); sk_h_003511f0();
            x23 = sk_h_002b3b50();
            if (end <= x4 >> 0xe) { sk_h_003a25d4(dh); break; }
            sk_h_00350c20(x4);
            word_t cap = sk_h_001b798c();
            if (end < cap >> 0xe) {
                sk_r29_pair_t q = sk_h_0029fa0c(x4, x5, x7, 0);
                word_t qh = q.hi;
                if ((q.lo ^ qh) < 0x4000) { sk_h_003a25d4(0); break; }
                sk_r29_pair_t r = sk_h_004ac30c();
                sk_h_002b439c(r.lo, r.hi, qh, x3, 0);
                sk_h_00354e0c(); sk_h_003a25d4(0);
            } else {
                sk_r29_pair_t r = sk_h_0035060c();
                sk_h_00267510(r.lo, r.hi, 0);
                sk_h_00354e0c();
            }
            x4 = 0;
            break;
        }
    } else {
        long l1 = (0 & 0xfffffffffffffff) + 0x20;
        while (0x3fff < (x23 ^ x22)) {
            sk_h_000bd3a4();
            word_t a = sk_h_002b7088();
            sk_h_000bd3a4(0);
            sk_h_002b723c();
            if (end <= x4 >> 0xe) break;
            sk_h_003513b4(x4);
            word_t u = sk_h_00167404();
            word_t r;
            if ((0 >> 0x3c & 1) != 0) { sk_h_003513b4(u & 0xffffffffffff0000); r = sk_h_002a49a8(); }
            else if ((0 >> 0x3d & 1) != 0) { r = sk_h_00355da8((u >> 0x10)); }
            else { long o = l1; if ((x7 >> 0x3c & 1) == 0) { sk_h_00350470(); o = (long)sk_h_002a9ba8(); } r = sk_h_00355da8(o + (u >> 0x10)); }
            if (r != a) break;
            break;
        }
    }
    sk_h_000b45b0(0, 0, 0);
}

/* FUN_00485010 @ 0x00485010   (est. sk_regex_match_literal)
 * Ghidra: void FUN_00485010(...6 args)
 * Matches a literal byte string at the cursor: iterates the pattern bytes,
 * follows the input cursor through frame translation, and returns the matched
 * end cursor (or null + fail). Confidence: medium. */
void sk_h_485010(word_t p1, word_t p2, word_t p3, word_t p4, word_t p5, word_t p6)
{
    sk_r29_pair_t d = sk_h_0035193c();
    word_t cur = d.hi;
    long l11 = *(long *)(d.lo + 0x10);
    char *pat = (char *)(d.lo + 0x20);
    word_t sel = (p5 >> 0x3b) & 1;
    if ((p6 & 0x1000000000000000) == 0) sel = 1;
    word_t u7 = p5 & 0xffffffffffff;
    if ((p6 & 0x2000000000000000) != 0) u7 = p6 >> 0x38 & 0xf;
    for (; l11 != 0; l11--) {
        if (p3 >> 0xe <= cur >> 0xe) goto fail;
        char pc = *pat;
        word_t p = cur;
        if ((cur & 0xc) == (word_t)4 << sel) { d = sk_h_003507e0(); p = sk_h_0001da84(d.lo, d.hi, p6); }
        word_t off = p >> 0x10;
        if (u7 <= off) SK_TRAP(0x4851b0);
        char cc;
        if ((p6 >> 0x3c & 1) == 0) {
            if ((p6 >> 0x3d & 1) == 0) {
                long o = (long)((p6 & 0xfffffffffffffff) + 0x20);
                if ((p5 >> 0x3c & 1) == 0) { sk_h_000b43d0(); o = (long)sk_h_002a9ba8(); }
                cc = *(char *)(o + off);
            } else { cc = *(char *)(0 + off); }
        } else { cc = (char)sk_h_002b141c(); }
        if (pc != cc) goto fail;
        if ((cur & 0xc) == (word_t)4 << sel) {
            d = sk_h_003507e0();
            cur = sk_h_0001da84(d.lo, d.hi, p6);
            if ((p6 >> 0x3c & 1) == 0) { cur = (word_t)&sk_h_00010004 + (cur & 0xffffffffffff0000); }
            else { sk_h_003507e0(); cur = sk_h_002b141c(); }
        } else {
            if ((p6 >> 0x3c & 1) != 0) { sk_h_003507e0(); cur = sk_h_002b141c(); }
            else cur = (word_t)&sk_h_00010004 + (cur & 0xffffffffffff0000);
        }
        pat++;
    }
    if (p3 >> 0xe < cur >> 0xe) { fail: cur = 0; sk_h_00351774(cur, 1, 0); return; }
    if ((p4 & 1) != 0) {
        sk_r29_pair_t q = sk_h_003507e0();
        word_t chk = sk_h_00450878(q.lo, q.hi, p6);
        if ((chk & 1) == 0) { cur = 0; sk_h_00351774(cur, 1, 0); return; }
    }
    sk_h_00351774(cur, 0, 0);
}

/* FUN_004851b4 @ 0x004851b4   (est. sk_regex_advance_utf8_scalar)
 * Ghidra: undefined8 FUN_004851b4(uint param_1)
 * Advances the cursor at +0x58 one UTF-8 scalar toward +0x50, returning 1 on
 * success (or 0 after flushing when exhausted). Confidence: low. */
word_t sk_h_4851b4(word_t p1, word_t x20)
{
    word_t cur = *(word_t *)(x20 + 0x58) >> 0xe;
    word_t lim = *(word_t *)(x20 + 0x50) >> 0xe;
    if (cur < lim) {
        sk_h_003507e0(); sk_h_00350bfc(); sk_h_482a84(0, 0, 0, 0);
        word_t r = sk_h_004ac144().lo;
        if (r - 10 < 4) { sk_h_481cc0(0); return 0; }
        *(word_t *)(x20 + 0x58) = r;
        return 1;
    }
    sk_h_481cc0(0);
    return 0;
}

/* FUN_0048525c @ 0x0048525c   (est. sk_regex_finish_capture)
 * Ghidra: void FUN_0048525c(void)
 * Completes a capture when the work vector is non-empty; trims one entry if a
 * special marker (0x100000000) is present. Confidence: low. */
void sk_h_48525c(word_t *x20)
{
    if (*(long *)(*x20 + 0x10) == 0) SK_TRAP(0x4852ac);
    word_t r = sk_h_0049c5a0();
    if ((r & 0xff00000000) == 0x100000000) { sk_h_0049c4b4(*(long *)(*x20 + 0x10) - 1); }
}

/* FUN_004852ac @ 0x004852ac   (est. sk_regex_emit_capture_index)
 * Ghidra: void FUN_004852ac(void)
 * Emits a capture index reference: derives the index from the tagged cursor
 * (low 48 bits or the 4-bit tag), validates it, and emits the index token.
 * Confidence: low. */
void sk_h_4852ac(word_t *x20)
{
    word_t k = x20[1];
    word_t idx;
    if ((k >> 0x3d & 1) == 0) { idx = *x20 & 0xffffffffffff; if (idx == 0) SK_TRAP(0x4852cc); }
    else { idx = k >> 0x38 & 0xf; if (idx == 0) SK_TRAP(0x485308); }
    word_t sel = (*x20 >> 0x3b) & 1;
    if ((k & 0x1000000000000000) == 0) sel = 1;
    word_t tag = (sel == 0) ? 0xb : 7;
    sk_h_0029c058(tag | idx << 0x10);
    sk_h_002ace24();
}

/* FUN_00485ffc @ 0x00485ffc   (est. sk_regex_case_insensitive_match)
 * Ghidra: uint FUN_00485ffc(uint param_1, uint param_2)
 * Case-insensitive single-scalar match: ASCII (<0x80) goes through the
 * lowercasing helper FUN_0049513c; the result is XORed with the flag.
 * Confidence: high. */
word_t sk_h_485ffc(word_t p1, word_t p2)
{
    word_t r;
    if (p1 < 0x80) { sk_h_00351488(); r = sk_h_0049513c(); }
    else r = 0;
    return (p2 ^ r) & 1;
}

/* FUN_0048603c @ 0x0048603c   (est. sk_regex_is_scalar_char)
 * Ghidra: uint FUN_0048603c(long param_1, long param_2, uint param_3)
 * True when param_1/param_2 is the CR/LF pair (0xa0d / -0x1e00...) or the
 * scalar check FUN_002a0cf8 passes; result XORed with the flag. Confidence:
 * low (tag constants). */
word_t sk_h_48603c(long p1, long p2, word_t p3)
{
    int iscrlf = (p1 == 0xa0d && p2 == -0x1e00000000000000);
    word_t r;
    if (p1 != 0xa0d || p2 != -0x1e00000000000000) {
        sk_h_0035089c(); sk_h_004aa890();
        word_t m = sk_h_002a0cf8();
        if ((m & 1) == 0) {
            sk_h_003504c4(); sk_h_002bd8f0(); sk_h_00466214();
            if (!iscrlf) { sk_h_00350548(); r = sk_h_0049513c(); }
            else r = 0;
        } else r = 0;
    } else r = 0;
    return (p3 ^ r) & 1;
}

/* FUN_004860bc @ 0x004860bc   (est. sk_regex_char_set_anchor)
 * Ghidra: undefined1[16] FUN_004860bc(void)
 * Returns the fixed anchor descriptor {lo=0xd000000000000010, hi=...5e3160}.
 * Confidence: medium. */
sk_r29_pair_t sk_h_4860bc(void)
{
    sk_r29_pair_t r;
    r.hi = 0x80000000005e3160;
    r.lo = 0xd000000000000010;
    return r;
}

/* FUN_004860d8 @ 0x004860d8   (est. sk_regex_init_charset)
 * Ghidra: void FUN_004860d8(void)
 * Initialises a character set: two helper calls. Confidence: low. */
void sk_h_4860d8(void) { sk_h_004080b0(); sk_h_001a8564(); }

/* FUN_0048610c / 00486110 @ 0x0048610c / 0x00486110   (est. sk_regex_char_set_anchor_value)
 * Ghidra: undefined8 FUN_0048610c(void) / FUN_00486110(void)
 * Returns the fixed scalar part of the anchor descriptor. Confidence: medium. */
word_t sk_h_48610c(void) { sk_h_4860bc(); return 0xd000000000000010; }
word_t sk_h_486110(void) { sk_h_4860bc(); return 0xd000000000000010; }

/* FUN_0048612c @ 0x0048612c   (est. sk_regex_fill_pointer_vec)
 * Ghidra: void FUN_0048612c(undefined8 param_1)
 * Fills the vector at *x20 with param_1 repeated over its current length
 * (growing on demand). Confidence: low. */
void sk_h_48612c(word_t p1, word_t *x20)
{
    long vec = *x20;
    word_t n = *(word_t *)(vec + 0x10);
    if (n != 0) {
        word_t f = sk_h_003a261c(vec);
        if ((f & 1) == 0) vec = (long)sk_h_0049a440(vec);
        if (*(word_t *)(vec + 0x10) < n) SK_TRAP(0x4861a0);
        long off = 0x20;
        do { *(word_t *)(vec + off) = p1; off += 8; n--; } while (n != 0);
        *x20 = vec;
    }
}

/* FUN_004861a0 @ 0x004861a0   (est. sk_regex_init_pointer_vec)
 * Ghidra: void FUN_004861a0(undefined8 param_1)
 * Initialises each slot of the vector at *x20 via FUN_0032b65c. Confidence: low. */
void sk_h_4861a0(word_t p1, word_t *x20)
{
    long vec = *x20;
    word_t n = *(word_t *)(vec + 0x10);
    if (n != 0) {
        word_t f = sk_h_003a261c(vec);
        if ((f & 1) == 0) vec = (long)sk_h_0049a47c(vec);
        word_t i = 0;
        long e = vec;
        do {
            e += 0x20;
            if (*(word_t *)(vec + 0x10) <= i) SK_TRAP(0x48622c);
            i++;
            sk_h_0032b65c(e, p1);
        } while (n != i);
        *x20 = vec;
    }
}

/* FUN_0048622c @ 0x0048622c   (est. sk_regex_fill_word_vec)
 * Ghidra: void FUN_0048622c(undefined8 param_1)
 * Fills the vector at *x20 with param_1 over its length (like 48612c but via
 * the 0x454 grow helper). Confidence: low. */
void sk_h_48622c(word_t p1, word_t *x20)
{
    long vec = *x20;
    word_t n = *(word_t *)(vec + 0x10);
    if (n != 0) {
        word_t f = sk_h_003a261c(vec);
        if ((f & 1) == 0) vec = (long)sk_h_0049a454(vec);
        if (*(word_t *)(vec + 0x10) < n) SK_TRAP(0x4862a0);
        long off = 0x20;
        do { *(word_t *)(vec + off) = p1; off += 8; n--; } while (n != 0);
        *x20 = vec;
    }
}

/* FUN_004862a0 @ 0x004862a0   (est. sk_regex_emit_capture_summary)
 * Ghidra: undefined1[16] FUN_004862a0(void)
 * Emits the capture summary: for each of the two capture groups (at *x20 and
 * x20[7]) prints "element<count>:" (or "ints<count>:") via the string emitter
 * FUN_001a6a8c. Confidence: medium (string literals decoded). */
sk_r29_pair_t sk_h_4862a0(word_t *x20)
{
    word_t hi, lo, hi2, lo2;
    long v = *x20;
    if (*(long *)(v + 0x10) == 0) { hi = 0xe000000000000000; lo = 0; }
    else {
        sk_h_0036b270(0xe800000000000000);
        sk_h_002acbb8(0x203a, 0xe200000000000000);
        sk_h_001a6a8c(v, 0x6728f0);
        sk_h_004ac0cc();
        sk_h_003a25d4(v);
        sk_h_002acbb8(10, 0xe100000000000000);
        lo = 0x73746e656d656c65;   /* "element" */
        hi = 0xe800000000000000;
    }
    long v2 = x20[7];
    if (*(long *)(v2 + 0x10) == 0) { lo2 = 0; hi2 = 0xe000000000000000; }
    else {
        sk_h_0036b270(0xe400000000000000);
        sk_h_002acbb8(0x203a, 0xe200000000000000);
        sk_h_001a6a8c(v2, 0x677880);
        sk_h_004ab5a4();
        sk_h_002acbb8(0, 0);
        sk_h_003a25d4(v2);
        sk_h_002acbb8(10, 0xe100000000000000);
        lo2 = 0x73746e69;           /* "ints" */
        hi2 = 0xe400000000000000;
    }
    sk_h_002acbb8(lo2, hi2);
    sk_h_003a25d4(hi2);
    sk_r29_pair_t r; r.hi = hi; r.lo = lo;
    return r;
}

/* FUN_004863d8 @ 0x004863d8   (est. sk_regex_run_matcher)
 * Ghidra: long FUN_004863d8(long param_1, undefined8 param_2, long param_3, ...)
 * Runs the main regex matcher over the subject. Builds a result vector from the
 * compiled instruction array at param_1+0x18/0x20 (a bit-set/decision tree with
 * an index table), walks the instruction stream, and appends a 0x58-byte match
 * record per step via FUN_00117cc4. Returns the result vector. Confidence:
 * medium (bit-twiddle instruction decode). */
long sk_h_4863d8(long p1, word_t p2, long p3, word_t p4, word_t p5)
{
    long instr = *(long *)(p1 + 0x18);
    long argptr = *(long *)(p1 + 0x20);
    long count = *(long *)(instr + 0x10);
    sk_h_0036b270(instr);
    word_t empty = (word_t)&sk_h_00657778;
    long vec = (long)sk_h_00498e50(0, count + 1, 0, empty, (word_t)sk_h_00498228, (word_t)sk_h_000722e8, (word_t)sk_h_00499918);
    word_t p2v = p2, p3v = (word_t)p3;
    sk_h_0034cb88();
    sk_h_004a4ac4(p5, (word_t)&(long[3]){0});
    if (count == 0) SK_TRAP(0x4867a4);
    word_t state = 0, e0 = 0, e1 = 0, e2 = 0;
    unsigned char tag = *(unsigned char *)(instr + 0x50);
    word_t n = *(word_t *)(vec + 0x10);
    if (*(word_t *)(vec + 0x18) >> 1 <= n) { sk_h_0006b42c(); sk_h_00350774(0, n + 1); vec = (long)sk_h_00498e50(); }
    *(word_t *)(vec + 0x10) = n + 1;
    sk_h_00117cc4(vec + n * 0x58 + 0x20, (word_t)&(word_t){0});
    long step = 0;
    for (;;) {
        word_t slot0 = 0, slot1 = 0, slot2 = 0;
        if (p3v == 0) {
            sk_h_004a4b14((word_t)&(word_t){0}, 0, 0);
            sk_h_0036b118(p4);
            return vec;
        }
        long step_next = step + 1;
        long wordbits = *(long *)(argptr + 0x20);
        long bitmask = 0xffffffffffffffff;
        if ((*(unsigned char *)(argptr + 0x20) & 0x3f) < 6) bitmask = ~(-1L << (wordbits & 0x3f));
        word_t bits = bitmask & *(word_t *)(argptr + 0x40);
        long sel = 0;
        word_t rb = 0;
        for (;;) {
            while (bits == 0) {
                sel++;
                if ((wordbits + 0x3f >> 6) <= sel) { slot0 = 1; slot1 = 0; goto emit; }
                bits = *(word_t *)(argptr + 0x40 + sel * 8);
            }
            rb = (bits & 0xaaaaaaaaaaaaaaaa) >> 1 | (bits & 0x5555555555555555) << 1;
            rb = (rb & 0xcccccccccccccccc) >> 2 | (rb & 0x3333333333333333) << 2;
            rb = (rb & 0xf0f0f0f0f0f0f0f0) >> 4 | (rb & 0x0f0f0f0f0f0f0f0f) << 4;
            rb = (rb & 0xff00ff00ff00ff00) >> 8 | (rb & 0x00ff00ff00ff00ff) << 8;
            rb = (rb & 0xffff0000ffff0000) >> 0x10 | (rb & 0x0000ffff0000ffff) << 0x10;
            bits = bits - 1 & bits;
            rb = 0 | sel << 6;   /* LZCOUNT-based bit index */
            if (*(long *)(*(long *)(argptr + 0x38) + rb * 8) == step) {
                slot0 = 0;
                slot1 = *(word_t *)(*(long *)(argptr + 0x30) + rb * 8);
                break;
            }
        }
emit:
        word_t nn = *(word_t *)(vec + 0x10);
        if (*(word_t *)(vec + 0x18) >> 1 <= nn) { sk_h_0006b42c(); sk_h_004ab0e0(); vec = (long)sk_h_00498e50(); }
        *(word_t *)(vec + 0x10) = nn + 1;
        sk_h_00117cc4(vec + nn * 0x58 + 0x20, (word_t)&(word_t){0}, 0x52);
        sk_h_004a3528(0);
        step = step_next;
    }
}

/* FUN_004867a4 @ 0x004867a4   (est. sk_regex_emit_construct)
 * Ghidra: undefined1[16] FUN_004867a4(ulong param_1)
 * Emits a regex construct description for the construct kind in the low byte of
 * param_1. Each kind prints a DSL snippet (e.g. "-> int", "[...]", "match
 * scalar case-insensitive", boundary checks, capture groups); several kinds
 * recurse through string-table lookups (0x677790 etc.). Confidence: high
 * (string literals decoded). */
sk_r29_pair_t sk_h_4867a4(word_t p1)
{
    word_t kind = sk_h_4816b4() & 0xff;
    word_t lo = 0, hi = 0xe000000000000000;
    if (0x1d < kind - 1) {
        sk_h_004aa904(); sk_h_000f4a9c(); sk_h_004ab304();
        sk_h_00205844();
        sk_r29_pair_t r; r.hi = hi; r.lo = lo; return r;
    }
    switch (kind) {
    case 1: case 4: case 5: case 0x11: case 0x12: case 0x19: case 0x1a:
        /* int/word/any/boundary construct printers */
        sk_h_000b430c(); sk_h_002a4ab4(0x10); sk_h_004ab650();
        sk_h_004aa904(kind); sk_h_000f4a9c(); sk_h_004ab304(); sk_h_00205844();
        sk_h_00496ef0(p1 & 0xffff);
        sk_h_004ab5a4(); sk_h_002acbb8(0, 0);
        sk_h_003a25d4(p1 & 0xffff);
        hi = 0x5d | 0xe100000000000000;  /* "]" terminator */
        break;
    case 2: case 3: case 0xd: case 0x13: case 0x14: case 0x1c: case 0x1d:
        /* scalar/anchor kinds -> generic descriptor */
        sk_h_00463e04(); sk_h_004aa904(kind); sk_h_000f4a9c(); sk_h_004ab304(); sk_h_00205844();
        lo = 0; hi = 0xe000000000000000;
        break;
    case 6: case 7: case 8: case 9: case 0xb: case 0xc: case 0xf: case 0x10:
    case 0x15: case 0x16: case 0x17: case 0x18: case 0x1b:
        /* property/class construct printers (string-emission variants) */
        sk_h_00463e04(); sk_h_004aa904(kind); sk_h_000f4a9c(); sk_h_004ab304();
        sk_h_00205844(); sk_h_004ab35c();
        sk_h_00496ef0(p1 & 0xffff);
        sk_h_004ab5a4(); sk_h_002acbb8(0, 0);
        sk_h_003a25d4(p1);
        lo = 0; hi = 0xe500000000000000;
        break;
    case 0xe:
        sk_h_00463e04(); sk_h_004aa904(0xe); sk_h_000f4a9c(); sk_h_004ab304(); sk_h_00205844();
        lo = 0x656d75736e6f6320; hi = 0xea00000000005b72;   /* "consume[r]" */
        break;
    case 0x1e: SK_TRAP(0x487034);
    default:
        sk_h_00496ef0(p1 >> 0x10 & 0xffff);
        sk_h_004ab5a4(); sk_h_002acbb8(0, 0); sk_h_003a25d4(p1);
        hi = 0x5d | 0xe100000000000000;
        break;
    }
    sk_r29_pair_t r; r.hi = hi; r.lo = lo; return r;
}

/* FUN_004870b4 @ 0x004870b4   (est. sk_regex_build_matcher)
 * Ghidra: void FUN_004870b4(void)
 * Builds a matcher: calls FUN_004870f4 into a stack buffer, then finalises.
 * Confidence: low. */
void sk_h_4870b4(word_t x21)
{
    sk_h_4870f4((word_t)&(word_t[5]){0}, 0,0,0,0,0,0,0,0);
    if (x21 == 0) sk_h_004aade4();
}

/* FUN_004870f4 @ 0x004870f4   (est. sk_regex_build_matcher_core)
 * Ghidra: void FUN_004870f4(...9 args)
 * Core matcher builder: snapshots the instruction state, clones the arg block,
 * runs the matcher FUN_004875c8, and writes the 5-word result into param_1.
 * Confidence: low. */
void sk_h_4870f4(word_t p1, long p2, word_t p3, word_t p4, word_t p5, word_t p6, word_t p7, word_t p8, word_t p9)
{
    sk_r29_pair_t d = sk_h_000a6f68();
    word_t r0 = *(word_t *)d.lo;
    sk_h_00117cc4(p2 + 0x38, p2 + 0x38, 0x50);
    sk_h_004ab7cc();
    sk_h_004a4ac4((word_t)&(word_t){r0}, (word_t)&(word_t[5]){0});
    sk_h_0036b270(p4);
    sk_h_004a34f0(p2 + 0x38, (word_t)&(word_t[5]){0});
    sk_h_004ab784();
    sk_h_004a4ac4((word_t)&(word_t){0}, (word_t)&(word_t[5]){0});
    sk_h_4875c8((word_t)&(word_t[5]){0}, p2, (word_t)&(word_t){d.hi});
    sk_h_004a3500((word_t)&(word_t){0});
    if (0 == 0) { *(word_t *)(p1 + 8) = 0; *(word_t *)p1 = 0; *(word_t *)(p1 + 0x18) = 0; *(word_t *)(p1 + 0x10) = 0; *(word_t *)(p1 + 0x20) = 0; }
}

/* FUN_00487210 @ 0x00487210   (est. sk_regex_build_matcher2)
 * Ghidra: void FUN_00487210(void)
 * Adjacent matcher builder (like 4870b4). Confidence: low. */
void sk_h_487210(word_t x21) { sk_h_4870f4((word_t)&(word_t[5]){0}, 0,0,0,0,0,0,0,0); if (x21 == 0) sk_h_004aade4(); }

/* FUN_00487250 @ 0x00487250   (est. sk_regex_build_matcher3)
 * Ghidra: void FUN_00487250(...8 args)
 * Third matcher builder: snapshots param_1's instruction state, clones the
 * arg block at param_1+7, runs FUN_0048736c. Confidence: low. */
void sk_h_487250(word_t p1, word_t p2, word_t p3, word_t p4, word_t p5, word_t p6, word_t p7, word_t p8)
{
    word_t r0 = *(word_t *)p1;
    sk_h_00117cc4(p1 + 0x38, p1 + 0x38, 0x50);
    sk_h_004ab7cc();
    sk_h_004a4ac4((word_t)&(word_t){r0}, (word_t)&(word_t[5]){0});
    sk_h_0036b270(p3);
    sk_h_004a34f0(p1 + 0x38, (word_t)&(word_t[5]){0});
    sk_h_004ab784();
    sk_h_004a4ac4((word_t)&(word_t){0}, (word_t)&(word_t[5]){0});
    sk_h_48736c((word_t)&(word_t[5]){0}, p1, (word_t)&(word_t[4]){0}, p8);
    sk_h_004a3500((word_t)&(word_t){0});
    if (0 == 0) sk_h_004aade4();
}

/* FUN_0048736c @ 0x0048736c   (est. sk_regex_iterate_match)
 * Ghidra: void FUN_0048736c(...3 args)
 * Iterates the matcher: walks the instruction list at param_2+0x28, following
 * frame translation for the current scalar, calling FUN_00484910 to commit each
 * match until the range is exhausted. Confidence: low. */
void sk_h_48736c(word_t p1, long p2, word_t *p3)
{
    long l10 = *(long *)(*(long *)(p2 + 0x28) + 0x10);
    if (l10 == 0) SK_TRAP(0x4875c8);
    word_t hi = p3[9], end = p3[10];
    word_t kind = *(word_t *)(*(long *)(p2 + 0x28) + l10 * 4 + 0x1c);
    for (;;) {
        sk_h_00350518((word_t)&(word_t){0});
        sk_h_4875c8();
        if (0 != 0) return;
        long cur = 0;
        if (cur != 0) break;
        word_t v0 = 0, v1 = 0, v2 = 0, v3 = 0;
        if ((*(unsigned char *)(p2 + 0x30) & 1) != 0) goto store;
        if (hi >> 0xe == end >> 0xe) goto store;
        word_t a = *p3, b = p3[1];
        word_t u12 = hi;
        if ((u12 & 1) == 0 || (u12 & 0xc) == (word_t)4 << (1)) {
            if ((u12 & 0xc) == (word_t)4 << (1)) { sk_h_00352c4c(u12); u12 = sk_h_0001da84(); }
            word_t lim = a & 0xffffffffffff;
            if ((b & 0x2000000000000000) != 0) lim = b >> 0x38 & 0xf;
            if (lim <= u12 >> 0x10) SK_TRAP(0x4875c0);
        } else {
            word_t lim = a & 0xffffffffffff;
            if ((b & 0x2000000000000000) != 0) lim = b >> 0x38 & 0xf;
            if (lim <= u12 >> 0x10) SK_TRAP(0x4875c4);
        }
        if ((b >> 0x3c & 1) == 0) {
            u12 >>= 0x10;
            if ((b >> 0x3d & 1) == 0) {
                long off;
                if ((a >> 0x3c & 1) == 0) { sk_h_00350914(); off = (long)sk_h_002a9ba8(); }
                else off = (long)((b & 0xfffffffffffffff) + 0x20);
                sk_h_0034b3f8((word_t)*(unsigned char *)(off + u12));
                u12 = (u12 + 0) * 0x10000 | 5;
            } else { u12 = (u12 + 0) * 0x10000 | 5; }
        } else { sk_h_00352c4c(u12); u12 = sk_h_002a49a8(); }
        if (end >> 0xe < u12 >> 0xe) goto store;
        sk_h_484910(u12, p3[9], p3[10], 0);
    }
    sk_h_0036b270(0); sk_h_0036b270(0);
    sk_h_000f5e5c((word_t)&(word_t){0});
    sk_h_004aa938(); sk_h_004a4b14((word_t)&(word_t){0});
store:
    *(word_t *)p1 = 0; *(word_t *)(p1 + 8) = 0; *(word_t *)(p1 + 0x10) = 0; *(word_t *)(p1 + 0x18) = 0; *(word_t *)(p1 + 0x20) = 0;
}

/* FUN_004875c8 @ 0x004875c8   (est. sk_regex_drive_matcher)
 * Ghidra: void FUN_004875c8(...4 args)
 * Drives the matcher to completion: repeatedly calls FUN_00485418 until the
 * done flag (param_3+0x19) is set, then materialises the match ranges.
 * Confidence: low. */
void sk_h_4875c8(word_t p1, long p2, word_t *p3, word_t p4)
{
    char c = *(char *)(p3 + 0x19);
    word_t v0 = 0, v1 = 0, v2 = 0, v3 = 0, v4 = 0;
    if (c != 1) {
        word_t start = p3[0xb];
        while (c == 0) {
            sk_h_485418();
            c = *(char *)(p3 + 0x19);
        }
        if (c != 1) {
            word_t cur = p3[0xb];
            if (cur >> 0xe < start >> 0xe) SK_TRAP(0x4876f8);
            if (*(char *)(p2 + 0x10) == 1) { /* empty capture */ }
            else {
                if (*(long *)(p2 + 8) < 0) SK_TRAP(0x4876fc);
                sk_h_004ab68c();
                sk_h_00319808(0, (word_t)&(word_t){0});
            }
            sk_h_003513b4(p2, 0, p4, p3[0x18], (word_t)&(word_t){0});
            v2 = sk_h_4863d8(0, 0, 0, 0, 0);
            sk_h_0034cc24();
            sk_h_004a4b14((word_t)&(word_t){0});
            v0 = *p3;
            v1 = sk_h_0036b270(p3[1]);
        }
    } else {
        if (p3[0x1a] != 0) { sk_h_0036b270(p3[0x1a]); sk_h_0036986c(); return; }
    }
    *(word_t *)p1 = v0; *(word_t *)(p1 + 8) = v1; *(word_t *)(p1 + 0x10) = v2; *(word_t *)(p1 + 0x18) = v3; *(word_t *)(p1 + 0x20) = v4;
}

/* FUN_00487700 @ 0x00487700   (est. sk_regex_finalize_matcher)
 * Ghidra: void FUN_00487700(void)
 * Finalises a matcher: FUN_00469c50 then finalise helper. Confidence: low. */
void sk_h_487700(void) { sk_h_00469c50((word_t)&(word_t[5]){0}); sk_h_004aade4(); }

/* FUN_00487734 @ 0x00487734   (est. sk_regex_compile)
 * Ghidra: void FUN_00487734(void)
 * Compiles a regex: calls FUN_004ac5c4 then FUN_00469dc4 into a 368-byte
 * scratch buffer and runs the trailing dispatch. Confidence: low (large
 * buffer, truncated body). */
void sk_h_487734(word_t p1)
{
    sk_h_004ac5c4();
    sk_h_00469dc4((word_t)&(word_t[46]){0});
    sk_h_003509c8();
    sk_h_004a4914();
}

/* FUN_004877a0 @ 0x004877a0   (est. sk_regex_compile_init)
 * Ghidra: void FUN_004877a0(void)
 * Initialises the compiler state. Confidence: low. */
void sk_h_4877a0(void) { sk_h_004abaf0(); sk_h_00498b28(0); }

/* FUN_0048788c @ 0x0048788c   (est. sk_regex_compile_finish)
 * Ghidra: void FUN_0048788c(void)
 * Finalises compilation: pushes the terminator and releases the temporaries.
 * Confidence: low. */
void sk_h_48788c(void) { sk_h_0036b270(0); sk_h_00498b7c(0); sk_h_00498c84(); sk_h_004aafac(0); }

/* FUN_00487960 @ 0x00487960   (est. sk_regex_emit_ast_node)
 * Ghidra: void FUN_00487960(void)
 * Emits a regex AST node into the pattern buffer at x20[1]. The node kind
 * (from the low byte of the tagged word at *x20) selects a printing strategy:
 * capture groups, alternations, quantifiers, anchors, class sets, lookarounds.
 * Appends a {value,tag} 0x18-byte record via sk_h_00498b7c/00498c84/004aaacc.
 * Confidence: low (large switch, register-global state). */
void sk_h_487960(word_t *x20, word_t x21, word_t x26)
{
    word_t w = *x20;
    word_t kind = w & 0x3f;
    long *pl = (long *)&x20[1];
    switch (kind) {
    case 0:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12: {
        /* leaf/value node */
        long n = *(long *)(*pl + 0x10);
        sk_h_0036b270(x21);
        sk_h_00498b7c(x21);
        sk_h_00498c84();
        long base = *pl;
        *(long *)(base + 0x10) = n + 1;
        long slot = base + n * 0x18;
        *(long *)(slot + 0x20) = (long)w;
        *(word_t *)(slot + 0x28) = x21;
        *(unsigned char *)(slot + 0x30) = 1;
        *pl = base;
        break;
    }
    case 2:
    case 3:
    case 4:
    case 5:
        /* group/alternation node */
        sk_h_004aa3fc();
        sk_h_00498b7c(0, 0, 0, 0);
        sk_h_00498c84();
        long base2 = *pl;
        sk_h_004aaacc();
        *(word_t *)(0 + 0x20) = 0;
        *(word_t *)(0 + 0x28) = 0;
        *(unsigned char *)(0 + 0x30) = 0;
        *pl = base2;
        break;
    default:
        /* quantifier node */
        sk_h_0036b270(w & 0xffffffffffffffb);
        sk_h_004aa38c();
        sk_h_00498b7c(x21);
        sk_h_004ab178();
        sk_h_00498c84();
        long n3 = *(long *)(*pl + 0x10);
        sk_h_004aafac(x20[1]);
        long slot3 = 0 + x26 * 0;
        *(word_t *)(slot3 + 0x20) = w;
        *(word_t *)(slot3 + 0x28) = 0;
        *(unsigned char *)(slot3 + 0x30) = 1;
        x20[1] = 0;
        break;
    }
}

/* FUN_00488828 @ 0x00488828   (est. sk_regex_parse_character_class)
 * Ghidra: void FUN_00488828(void)
 * Parses a character class: iterates the class item list at +0x10, classifies
 * each element via FUN_0049df0c, and emits the class set (single chars,
 * ranges, negations, properties) into the pattern buffer, emitting the "[" /
 * "^[" bracket and building the char-set descriptor. Confidence: low. */
void sk_h_488828(word_t *x20)
{
    sk_r29_pair_t d = sk_h_0008e518();
    long l17 = d.lo;
    if ((d.hi & 1) != 0) { sk_h_0036b270(0xe200000000000000); sk_h_00498b7c(0, 0, 0, 0); sk_h_004aa9a8(); return; }
    word_t i = 0;
    word_t total = *(word_t *)(l17 + 0x10);
    sk_h_000776cc();
    while (total != i) {
        if (total <= i) SK_TRAP(0x488ea4);
        word_t item = sk_h_0049df0c((word_t)&(word_t[44]){0});
        if (item == 4) { i++; }
        else {
            sk_h_004a3940((word_t)&(word_t[44]){0}, (word_t)&(word_t[44]){0});
            i++;
            sk_h_00117cc4(0, (word_t)&(word_t[44]){0}, 0x160);
        }
    }
    /* emit "[" */
    sk_h_0036b270(0xe100000000000000);
    sk_h_004aa42c();
    sk_h_00498b7c((word_t)&sk_h_00657e60, 0, 0, 0);
    sk_h_004aa7a8();
    sk_h_00351aec(0, (word_t)&sk_h_00657e60);
    sk_h_00498c84();
    sk_h_004aa9a8();
    *(word_t *)(0 + 0x20) = 0x5b;
    *(word_t *)(0 + 0x28) = 0xe100000000000000;
    *(unsigned char *)(0 + 0x30) = 0;
    sk_h_003a25d4(0xe100000000000000);
    x20[1] = (word_t)(x20 + 1);
}

/* FUN_00488ec8 @ 0x00488ec8   (est. sk_regex_emit_class_atom)
 * Ghidra: void FUN_00488ec8(void)
 * Emits a single class atom: reads the class element kind and prints the
 * appropriate regex text (escapes \\d \\D \\w \\s \\b etc., anchors, char
 * literals, properties), appending a 0x18-byte record. Confidence: low. */
void sk_h_488ec8(void)
{
    sk_h_0008e518();
    sk_h_00464a44();
    sk_h_004ab0f0((word_t)&(word_t[22]){0});
    sk_h_00117cc4();
    word_t kind = sk_h_0049e2d4((word_t)&(word_t[22]){0});
    switch (kind) {
    default:
        sk_h_0049e2f0((word_t)&(word_t[22]){0});
        sk_h_000e0654();
        sk_h_489ac4();
        break;
    case 1: { word_t c = sk_h_0049e2f0((word_t)&(word_t[22]){0}); sk_h_489b5c(c); break; }
    case 2: case 3: case 4: case 5: case 6:
        sk_h_0049e2f0((word_t)&(word_t[22]){0});
        break;
    }
    sk_h_000b43e8();
    sk_h_0036b270(0);
    sk_h_004aab4c(); sk_h_004aa42c();
    sk_h_00498b7c();
    sk_h_004aa7a8(); sk_h_004aa850(); sk_h_00498c84(); sk_h_004aa9a8();
    *(word_t *)(0 + 0x20) = 0; *(word_t *)(0 + 0x28) = 0;
    sk_h_004ac258();
    sk_h_0008e500(0);
}

/* FUN_00489938 @ 0x00489938   (est. sk_regex_has_capture)
 * Ghidra: bool FUN_00489938(undefined8 param_1, ulong param_2, undefined8 param_3)
 * Reports whether a capture group is present: an alternation (kind 10) walks
 * the tree FUN_0048a0f4; a single-capture node returns true; else false.
 * Confidence: low. */
bool sk_h_489938(word_t p1, word_t p2, word_t p3, word_t x21)
{
    sk_h_004ab034();
    word_t kind = 0;
    if (kind != 10) {
        if (kind == 1) {
            word_t v = sk_h_004ac114();
            long l = *(long *)((v & x21) + 0x10);
            long n = *(long *)(l + 0x10);
            if (n != 0) {
                if (n == 1) {
                    word_t u = *(word_t *)(l + 0x20);
                    sk_h_0036b270(u & x21);
                    sk_h_0009461c();
                    bool r = sk_h_489938(0, 0, 0, x21);
                    sk_h_0036b118(u & x21);
                    return r & 1;
                }
                return true;
            }
        }
        return false;
    }
    sk_h_004ab260();
    long l3 = *(long *)(0 + 0x18);
    sk_h_48a0f4(p2);
    sk_h_00351d18();
    sk_h_0036b270();
    if ((p2 & 1) == 0) {
        sk_h_00084180();
        word_t r = sk_h_48a110();
        if ((r & 1) == 0) {
            sk_h_0006b6f4(); sk_h_00002534();
            sk_h_003510c4((word_t)&sk_h_00657e58, 0, p3, 0);
            sk_h_004a49c0();
            sk_h_0036b270(l3);
            sk_h_0011e71c(); sk_h_00351b78(); sk_h_001bc440(); sk_h_00354e0c();
            sk_h_003a2610(l3, 2);
            sk_h_003a25d4(0xe000000000000000);
            return 1 < l3;
        }
    }
    sk_h_004ab89c(0x515c);
    sk_h_00084180(); sk_h_002acbb8(); sk_h_004accb4();
    sk_h_003a25d4(l3);
    sk_h_000b43d0(); sk_h_001ee018(); sk_h_0035310c(); sk_h_003a25d4();
    return 1 < l3;
}

/* FUN_00489ac4 @ 0x00489ac4   (est. sk_regex_escape_metachar)
 * Ghidra: undefined1[16] FUN_00489ac4(void)
 * Escapes a regex metacharacter: looks it up in the class table (DAT_006c10b0
 * key), returning the escaped form or a backslash + literal. Confidence: medium. */
sk_r29_pair_t sk_h_489ac4(void)
{
    sk_r29_pair_t d = sk_h_0008409c();
    if (0 != -1) { sk_h_004ab58c(0); d = sk_h_0039a128(); }
    sk_h_00084180(d.lo, d.hi, 0);
    word_t r = sk_h_000ac00c();
    if ((r & 1) != 0) { sk_h_004ab968(0x5c); sk_h_00084180(); sk_h_002acbb8(); return (sk_r29_pair_t){0, 0}; }
    sk_h_00084180();
    return sk_h_48a670();
}

/* FUN_00489b5c @ 0x00489b5c   (est. sk_regex_escape_control)
 * Ghidra: undefined1[16] FUN_00489b5c(int param_1)
 * Emits the escaped form of a control character: \\t (9), \\n (10), \\r (13),
 * else \\u{hhhh} / \\U{hhhhhhhh} with leading-zero padding. Confidence: high. */
sk_r29_pair_t sk_h_489b5c(word_t c)
{
    word_t lo, hi = 0xe200000000000000;
    if (c == 9) { lo = 0x745c; }
    else if (c == 10) { lo = 0x6e5c; }
    else if (c == 13) { lo = 0x725c; }
    else {
        sk_h_000863bc(); sk_h_004ab810(); sk_h_00355754((word_t)&(word_t){c});
        sk_h_001ebfb0(); sk_h_00352c80();
        long n = sk_h_001ee018();
        sk_h_00084180();
        long n2 = sk_h_001ee018();
        if (n < 5) { if ((4 - n2) < 0) SK_TRAP(0x489c80); sk_h_001ed960(0x30, 0xe100000000000000, 4 - n2); lo = 0x755c; }
        else { if ((8 - n2) < 0) SK_TRAP(0x489c84); sk_h_001ed960(0x30, 0xe100000000000000, 8 - n2); lo = 0x555c; }
        sk_h_004ab89c(lo);
        sk_h_002acbb8(); sk_h_003a25d4(0);
        hi = 0xe200000000000000;
    }
    sk_r29_pair_t r; r.hi = hi; r.lo = lo; return r;
}

/* FUN_00489c84 @ 0x00489c84   (est. sk_regex_dump_groups)
 * Ghidra: void FUN_00489c84(void)
 * Dumps the group/capture tables (at +0x18 and +0x38): for each group prints
 * its kind letter (i/J/m/n/s/U/x/xx/w/D/P/S/W/{gy}/{wy}/X/u/b), then a
 * separator, and clears the temporaries. Confidence: medium. */
void sk_h_489c84(word_t x20, word_t x25)
{
    sk_h_00351e20();
    long vec = *(long *)(x20 + 0x18);
    long n = *(long *)(vec + 0x10);
    if (n != 0) {
        sk_h_004abdc4();
        unsigned char *e = (unsigned char *)(vec + 0x20);
        do {
            word_t hi = 0xe100000000000000, c = 0x69;  /* 'i' */
            switch (*e) {
            case 1: c = 0x4a; break;      /* J */
            case 2: c = 0x6d; break;      /* m */
            case 3: c = 0x6e; break;      /* n */
            case 4: c = 0x73; break;      /* s */
            case 5: c = 0x55; break;      /* U */
            case 6: c = 0x78; break;      /* x */
            case 7: hi = 0xe200000000000000; c = 0x7878; break; /* xx */
            case 8: c = 0x77; break;      /* w */
            case 9: c = 0x44; break;      /* D */
            case 10: c = 0x50; break;     /* P */
            case 11: c = 0x53; break;     /* S */
            case 12: c = 0x57; break;     /* W */
            case 13: hi = 0xe400000000000000; c = 0x7d677b79; break; /* {yg} */
            case 14: c = 0x7d777b79; hi = 0xe400000000000000; break; /* {yw} */
            case 15: c = 0x58; break;     /* X */
            case 16: c = 0x75; break;     /* u */
            case 17: c = 0x62; break;     /* b */
            }
            word_t f = sk_h_003a261c(x25);
            if ((f & 1) == 0) { sk_h_0006b3f4(*(word_t *)(x25 + 0x10)); x25 = (word_t)sk_h_00072c0c(); }
            word_t idx = *(word_t *)(x25 + 0x10);
            if (*(word_t *)(x25 + 0x18) >> 1 <= idx) { sk_h_000ec004(); x25 = (word_t)sk_h_00072c0c(); }
            *(word_t *)(x25 + 0x10) = idx + 1;
            long slot = x25 + idx * 0x10;
            *(word_t *)(slot + 0x20) = c;
            *(word_t *)(slot + 0x28) = hi;
            n--; e += 0x18;
        } while (n != 0);
    }
    sk_h_0006b6f4(); sk_h_00002534(); sk_h_004aa5f8(0x64e038); sk_h_003510c4();
    sk_h_004a42a0(); sk_h_0011e71c(); sk_h_00350bfc(); sk_h_001bc440();
    sk_h_0036b118(x25);
    long vec2 = *(long *)(x20 + 0x38);
    long n2 = *(long *)(vec2 + 0x10);
    if (n2 != 0) {
        sk_h_004abdc4();
        unsigned char *e2 = (unsigned char *)(vec2 + 0x20);
        do {
            word_t hi = 0xe100000000000000, c = 0x69;
            switch (*e2) {
            case 1: c = 0x4a; break; case 2: c = 0x6d; break; case 3: c = 0x6e; break;
            case 4: c = 0x73; break; case 5: c = 0x55; break; case 6: c = 0x78; break;
            case 7: hi = 0xe200000000000000; c = 0x7878; break; case 8: c = 0x77; break;
            case 9: c = 0x44; break; case 10: c = 0x50; break; case 11: c = 0x53; break;
            case 12: c = 0x57; break; case 13: hi = 0xe400000000000000; c = 0x7d677b79; break;
            case 14: c = 0x7d777b79; hi = 0xe400000000000000; break; case 15: c = 0x58; break;
            case 16: c = 0x75; break; case 17: c = 0x62; break;
            }
            word_t f = sk_h_003a261c(x25);
            if ((f & 1) == 0) { sk_h_0006b3f4(*(word_t *)(x25 + 0x10)); x25 = (word_t)sk_h_00072c0c(); }
            word_t idx = *(word_t *)(x25 + 0x10);
            if (*(word_t *)(x25 + 0x18) >> 1 <= idx) { sk_h_000ec004(); x25 = (word_t)sk_h_00072c0c(); }
            *(word_t *)(x25 + 0x10) = idx + 1;
            long slot = x25 + idx * 0x10;
            *(word_t *)(slot + 0x20) = c;
            *(word_t *)(slot + 0x28) = hi;
            n2--; e2 += 0x18;
        } while (n2 != 0);
    }
    sk_h_0011e71c(); sk_h_00350bfc();
    sk_r29_pair_t au = sk_h_001bc440();
    sk_h_0036b118(x25);
    word_t chk = sk_h_0041ae04();
    if ((chk & 1) == 0) {
        sk_h_004acc5c(0x3f28); sk_h_003a25d4(0);
        sk_h_0034eb74(au.lo & 0xffffffffffff);
        if (0 == 0) { sk_h_003a25d4(au.hi); }
        else { sk_h_00350518(); sk_h_002acbb8(); sk_h_003a25d4(au.hi); }
        sk_h_0036b270(0); sk_h_00100efc(); sk_h_002acbb8(); sk_h_003a25d4(0);
    } else {
        sk_h_003a25d4(au.hi);
        sk_h_004acc5c(0);
    }
    sk_h_003a25d4(0);
    sk_h_00351d30(x25, 0, 0);
}

/* FUN_0048a0f4 @ 0x0048a0f4   (est. sk_regex_tree_entry)
 * Ghidra: void FUN_0048a0f4(long param_1)
 * Reads the last tree-entry kind at param_1 and passes it to the dispatcher
 * FUN_00354998; traps when the tree is empty. Confidence: medium. */
void sk_h_48a0f4(long p1)
{
    if (*(long *)(p1 + 0x10) != 0) {
        sk_h_00354998(*(word_t *)(p1 + *(long *)(p1 + 0x10) * 4 + 0x1c));
        return;
    }
    SK_TRAP(0x48a110);
}

/* FUN_0048a110 @ 0x0048a110   (est. sk_regex_lookup_char_class)
 * Ghidra: void FUN_0048a110(void)
 * Looks up the current character in the compiled class table (DAT_006c10b8):
 * hashes the scalar via FUN_001a84f4/001b9084/001a8564, probes the bit-set,
 * and forwards to FUN_0029fb80's match. Confidence: low. */
word_t sk_h_48a110(void)
{
    sk_h_0035638c();
    word_t seed = sk_h_003532b8();
    sk_h_0036b270(seed);
    sk_r29_pair_t d = sk_h_0029fb80();
    word_t l6 = d.hi;
    if (l6 == 0) { sk_h_003a25d4(0); sk_h_00356370(0, 0); return 0; }
    if (0 != -1) { sk_h_004ab58c(); sk_h_0039a128(0); }
    word_t found = 0;
    if (*(long *)(0 + 0x10) != 0) {
        sk_h_001a84f4((word_t)&(word_t){0}, 0);
        sk_h_00350600((word_t)&(word_t){0});
        sk_h_001b9084();
        word_t h = sk_h_001a8564();
        word_t mask = ~(-1L << ((word_t)*(unsigned char *)(0 + 0x20) & 0x3f));
        h &= mask;
        if (*(word_t *)(0 + 0x38 + (h >> 6) * 8) >> (h & 0x3f) & 1) {
            word_t *slot = (word_t *)(*(long *)(0 + 0x30) + h * 0x10);
            if (d.lo == *slot && d.hi == slot[1]) found = 1;
        }
    }
    sk_h_003a25d4(l6);
    sk_h_00356370(found, 0);
    return found;
}

/* FUN_0048a244 @ 0x0048a244   (est. sk_regex_emit_quantifier)
 * Ghidra: void FUN_0048a244(void)
 * Emits a quantifier description: reads the quantifier kind from the header at
 * unaff_x20, prints the appropriate DSL snippet ({n}, {n,}, {m,n}, the
 * case-insensitive \\p/\\P property escapes, and anchors \N), and emits the
 * descriptor. Confidence: low (register-global quantifier header). */
sk_r29_pair_t sk_h_48a244(void)
{
    sk_h_00357cb4();
    word_t ic = *(word_t *)(0 + 0x21) & 1;   /* case-insensitive flag */
    word_t kind = *(word_t *)(0 + 0x10) & 0xff;
    word_t lo = 0x505c, hi = 0xe200000000000000;   /* "\\P" */
    if (ic == 0) lo = 0x705c;   /* "\\p" */
    if (kind > 0xf) { sk_h_003a25d4(0xe200000000000000); sk_h_00452c00(); }
    else {
        switch (kind) {
        case 0: case 1: case 2: case 3:
            /* {n}, {n,}, {m,n} forms */
            sk_h_003a25d4(0xe200000000000000);
            sk_h_004ab820();
            sk_h_004abcf8(0);
            sk_h_002acbb8();
            sk_h_003a25d4(0xe100000000000000);
            lo = 0x3d747069726373; hi = 0xe700000000000000;   /* "scrip t=" */
            break;
        case 0xb: case 0xc: case 0xd: case 0xe:
            /* \p{...} / \P{...} property escapes */
            sk_h_003a25d4(0xe200000000000000);
            sk_h_004ab820();
            sk_h_004abcf8(0);
            sk_h_002acbb8();
            sk_h_003a25d4(0xe100000000000000);
            lo = 0x3d786373; hi = 0xe400000000000000;   /* "sc x=" */
            break;
        case 4:
            sk_h_003a25d4(0xe200000000000000);
            sk_h_004abad8(0x4e5c);
            sk_h_004ab968(); sk_h_000b4390(); sk_h_002acbb8();
            break;
        case 0xf: {
            /* named capture {Any} / {dissingne} / {acii} specials */
            long a = *(long *)(0 + 8), b = *(long *)(0 + 0xc);
            word_t v0 = *(word_t *)0, v1 = *(word_t *)(0 + 1);
            if (a == 0 && b == 0 && 0 == 0 && v0 == 0 && v1 == 0) { lo = 0x7d796e417b; hi = 0xe500000000000000; }
            else if (v0 == 1 && a == 0 && b == 0 && 0 == 0) { lo = 0x656e67697373417b; hi = 0xea00000000007d64; }
            else if (v0 == 2 && a == 0 && b == 0 && 0 == 0) { lo = 0x5d3a69636361; hi = 0xe700000000000000; }
            else { sk_h_003a25d4(0xe200000000000000); lo = 0; hi = 0xe000000000000000; }
            break;
        }
        default:
            sk_h_004ab89c();
            sk_h_002acbb8(0x7b, 0xe100000000000000);
            sk_h_00451a64(0);
            sk_h_00465294();
            lo = 0; hi = 0xe000000000000000;
            break;
        }
    }
    sk_h_00357c74(lo, hi, 0);
    { sk_r29_pair_t _r; _r.lo = lo; _r.hi = hi; return _r; }
}

/* FUN_0048a590 @ 0x0048a590   (est. sk_regex_init_class_table)
 * Ghidra: void FUN_0048a590(void)
 * Initialises the compiled character-class table: allocates a backing buffer of
 * the current size (FUN_001ee018), seeds the metacharacter set, and populates
 * it from the pattern string via FUN_0029fb80/FUN_0049ab00, storing the result
 * in DAT_006c10b8. Confidence: medium. */
void sk_h_48a590(void)
{
    sk_h_00084180();
    long n = sk_h_001ee018();
    word_t buf;
    if (n == 0) buf = (word_t)&sk_h_006577e0;
    else { word_t t = sk_h_00002534((word_t)&sk_h_00657728, 0); buf = sk_h_0025a094(n, t); }
    /* seed the metacharacter set "\\[](){}|.*+?^$" */
    for (;;) {
        sk_r29_pair_t d = sk_h_0029fb80();
        if (d.hi == 0) break;
        sk_h_0049ab00((word_t)&(word_t){0}, d.lo, d.hi);
        sk_h_003a25d4(0);
    }
    *(word_t *)&sk_h_006c10b8 = buf;
}

/* FUN_0048a670 @ 0x0048a670   (est. sk_regex_emit_unicode_scalar)
 * Ghidra: void FUN_0048a670(void)
 * Emits a Unicode scalar: classifies the current scalar (ASCII 1-byte,
 * 2-byte, or 3/4-byte via the UTF-8 length helpers), then prints it via
 * FUN_00255d4c and the string pipeline, and emits the trailing descriptor.
 * Confidence: low. */
sk_r29_pair_t sk_h_48a670(void)
{
    sk_h_00041138();
    sk_h_003504d0();
    word_t r = sk_h_0043f454();
    if ((r & 1) == 0) { sk_h_0036b270(); }
    else {
        sk_h_0007c1c4(); sk_h_001ae8a8();
        word_t c = sk_h_0034ecc8();
        word_t len;
        if (c < 0x80) len = c + 1;
        else if (c < 0x800) len = sk_h_004abff8();
        else { sk_h_004ab9bc((c & 0x3f) << 8); len = sk_h_004aacf8(); }
        sk_h_00255d4c(len);
        if (0 < 0) SK_TRAP(0x48a808);
        sk_h_0036b270();
        sk_h_00294cb4();
        sk_h_00350624(1);
        sk_h_004730f0(); sk_h_00351450();
        word_t t = sk_h_00002534();
        sk_h_004a49c0((word_t)&sk_h_00657e70, (word_t)&sk_h_00657e68, 0, 0);
        sk_r29_pair_t d = sk_h_0011e71c();
        sk_h_001bc440(d.lo, d.hi, t);
        sk_h_003517c0();
        sk_h_003a25d4(0);
        sk_h_003a25d4(0xe000000000000000);
        sk_h_0036b270(0);
        sk_h_00350470(); sk_h_002acbb8(); sk_h_003a25d4(0);
        sk_h_003a25d4(t);
    }
    sk_r29_pair_t d2 = sk_h_0007c1c4();
    sk_h_0035847c(d2.lo, d2.hi, 0);
}

/* FUN_0048a81c @ 0x0048a81c   (est. sk_regex_emit_scalar_wrapper)
 * Ghidra: void FUN_0048a81c(...2 args)
 * Wrapper: calls FUN_0048a670 into param_1. Confidence: low. */
void sk_h_48a81c(word_t p1, word_t *p2)
{ sk_r29_pair_t d = sk_h_48a670(); *(word_t *)p1 = d.lo; *(word_t *)(p1 + 8) = d.hi; }

/* FUN_0048a84c @ 0x0048a84c   (est. sk_regex_emit_property_wrapper)
 * Ghidra: void FUN_0048a84c(void)
 * Wrapper: prints the property at *x19 via the tokeniser FUN_0024917c.
 * Confidence: low. */
void sk_h_48a84c(word_t *x19)
{
    sk_h_00352800();
    word_t t = sk_h_0024d9ac(0);
    word_t v0 = *x19;
    sk_h_0024917c((word_t)&(word_t){v0});
    sk_h_0036b118(t);
}

/* FUN_0048a8ac @ 0x0048a8ac   (est. sk_regex_frame_contains)
 * Ghidra: bool FUN_0048a8ac(ulong param_1, long param_2)
 * Reports whether the frame table at param_2 contains the frame of param_1:
 * probes the table's bit-set using the hash from FUN_001a84f4/001a8564.
 * Confidence: medium. */
bool sk_h_48a8ac(word_t p1, long p2)
{
    bool found = false;
    if (*(long *)(p2 + 0x10) != 0) {
        sk_h_001a84f4((word_t)&(word_t){0}, *(word_t *)(p2 + 0x28));
        sk_h_002298d4(p1 >> 0xe);
        word_t h = sk_h_001a8564();
        word_t probe;
        do {
            probe = h & ~(-1L << ((word_t)*(unsigned char *)(p2 + 0x20) & 0x3f));
            h = 1L << (probe & 0x3f) & *(word_t *)(p2 + 0x38 + (probe >> 6) * 8);
            found = h != 0;
            if (h == 0) return false;
            h = probe + 1;
        } while (p1 >> 0xe != *(word_t *)(*(long *)(p2 + 0x30) + probe * 8) >> 0xe);
    }
    return found;
}

/* FUN_0048a95c @ 0x0048a95c   (est. sk_regex_escape_ctrl_wrapper)
 * Ghidra: void FUN_0048a95c(...2 args)
 * Wrapper: calls FUN_00489b5c into param_1. Confidence: low. */
void sk_h_48a95c(word_t p1, word_t *p2)
{ sk_r29_pair_t d = sk_h_489b5c(*p2); *(word_t *)p1 = d.lo; *(word_t *)(p1 + 8) = d.hi; }

/* FUN_0048a988 @ 0x0048a988   (est. sk_regex_emit_hex_wrapper)
 * Ghidra: void FUN_0048a988(void)
 * Wrapper: prints the hex value at *x19 via FUN_0024917c. Confidence: low. */
void sk_h_48a988(word_t *x19)
{
    sk_h_00352800();
    word_t t = sk_h_0024d9ac(0);
    word_t v0 = *x19;
    sk_h_0024917c((word_t)&(word_t){v0});
    sk_h_0036b118(t);
}

/* FUN_0048aa38 / 0048aa3c @ 0x0048aa38 / 0x0048aa3c   (est. sk_regex_prop_dispatch)
 * Ghidra: void FUN_0048aa38(void) / FUN_0048aa3c(void)
 * Property-dispatch stubs: forward *x20 plus the wait/sync helper. Confidence: low. */
void sk_h_48aa38(word_t *x20) { sk_h_00494ea8(*x20, (word_t)sk_h_002298d4); }
void sk_h_48aa3c(word_t *x20) { sk_h_00494ea8(*x20, (word_t)sk_h_002298d4); }

/* FUN_0048aa68 @ 0x0048aa68   (est. sk_regex_emit_flag_A)
 * Ghidra: void FUN_0048aa68(void)
 * Emits the "A" (start-of-subject) flag token into *x19. Confidence: low. */
void sk_h_48aa68(word_t *x19) { sk_h_004ab834(); word_t v = sk_h_00084cc4(); *x19 = v; }

/* FUN_0048aa90 @ 0x0048aa90   (est. sk_regex_emit_flag_D)
 * Ghidra: void FUN_0048aa90(void)
 * Emits the "D" flag token into *x19. Confidence: low. */
void sk_h_48aa90(word_t *x19) { sk_h_004ab834(); word_t v = sk_h_0008cc7c(); *x19 = v; }

/* FUN_0048aab8 @ 0x0048aab8   (est. sk_regex_emit_flag_M)
 * Ghidra: void FUN_0048aab8(void)
 * Emits the "M" flag token into *x19. Confidence: low. */
void sk_h_48aab8(word_t *x19) { sk_h_004ab834(); word_t v = sk_h_000af4d8(); *x19 = v; }

/* FUN_0048aae0 @ 0x0048aae0   (est. sk_regex_emit_flag_S)
 * Ghidra: void FUN_0048aae0(void)
 * Emits the "S" flag token into *x19. Confidence: low. */
void sk_h_48aae0(word_t *x19) { sk_h_004ab834(); word_t v = sk_h_00085754(); *x19 = v; }

/* FUN_0048ab08 @ 0x0048ab08   (est. sk_regex_format_error)
 * Ghidra: void FUN_0048ab08(...5 args)
 * Formats a regex error/offset: builds a description via FUN_0044c9c4 and
 * FUN_00365b6c (with tag 0x682d68/7), emits it via FUN_0048abc4, and releases
 * the temporaries. Confidence: low. */
void sk_h_48ab08(word_t p1, word_t p2, word_t p3, word_t p4, word_t p5)
{
    sk_h_0044c9c4((word_t)&(word_t[11]){0}, p2, p3, p4, p5);
    sk_h_00319808(p1, (word_t)&(word_t[4]){0});
    sk_h_00351f34();
    sk_h_00365b6c((word_t)&(word_t){0}, (word_t)&(word_t[4]){0}, 8, 0x682d68, 7);
    sk_h_48abc4(0);
    sk_h_0036b118(0);
    sk_h_0036b118(0 & 0xfffffffffffffff);
    sk_h_0036b118(0);
    sk_h_0041d778(); sk_h_00351a50(); sk_h_004590e0((word_t)&(word_t[11]){0});
    sk_h_0009461c();
}

/* FUN_0048abc4 @ 0x0048abc4   (est. sk_regex_print_error)
 * Ghidra: void FUN_0048abc4(void)
 * Prints a regex error: computes the error kind (FUN_0048f61c), emits the
 * "Regex<...>" prefix and the error list, then a trailing "}".
 * Confidence: low. */
void sk_h_48abc4(word_t p1)
{
    sk_h_0008e518();
    sk_h_00464a44();
    word_t kind = sk_h_48f61c();
    sk_h_004ab26c();
    word_t lv = 0;
    if ((0 & 0xfffffffe | (kind >> 2 & 1)) != 0xc) {
        sk_h_004aa794();
        word_t u = sk_h_0036a940();
        *(word_t *)(u + 0x10) = kind;
        *(word_t *)(u + 0x18) = p1;
        lv = u | 0x6000000000000000;
        sk_h_0036b270(p1 & 0xfffffffffffffff);
    }
    long l4 = (long)sk_h_48addc(lv);
    long n = *(long *)(l4 + 0x10);
    if (n != 0) {
        word_t *e = (word_t *)(l4 + 0x28);
        do {
            word_t s = *e;
            sk_h_0036b270(s);
            sk_h_002a4ab4(0x22);
            sk_h_003a25d4(0xe000000000000000);
            sk_h_00350470(); sk_h_002acbb8(); sk_h_003a25d4(s);
            sk_h_002acbb8(0xd00000000000001c, 0x80000000005e2ef0);
            sk_h_004aca4c(0x2074656c);
            sk_h_0041d788(); sk_h_003a25d4(0xe400000000000000);
            e += 2; n--;
        } while (n != 0);
    }
    sk_h_0036b118(l4);
    sk_h_004ab458();
    *(word_t *)(0 + -0x10) = lv;
    sk_h_004aab08(0x7865676552, 0xe500000000000000);   /* "Regex" */
    sk_h_0041d7dc();
    sk_h_0036b118(lv & 0xffffffffffffffb);
    sk_h_48ba64();
    sk_h_0008e500(0);
}

/* FUN_0048ad50 @ 0x0048ad50   (est. sk_regex_print_error_leaf)
 * Ghidra: void FUN_0048ad50(void)
 * Prints a leaf error (kind 0xc): retains the message object, prints it via
 * FUN_0042ec5c/00351244, and releases the temporaries. Confidence: low. */
void sk_h_48ad50(word_t p1)
{
    sk_h_004ab034();
    if (0xc == 0xc) {
        sk_h_004ab260();
        sk_h_0036b270(*(word_t *)(0 + 0x18) & 0xfffffffffffffff);
        sk_r29_pair_t d = sk_h_0042ec5c();
        sk_h_00351244(d.lo, d.hi & 0xffffffff, d.lo, d.hi & 1);
        word_t u = sk_h_0040fbc0();
        sk_h_0044cda0();
        sk_h_0036b118(d.lo);
        sk_h_0036b118(u & 0xfffffffffffffff);
        sk_h_0036b118(0);
        return;
    }
    SK_TRAP(0x48addc);
}

/* FUN_0048addc @ 0x0048addc   (est. sk_regex_flatten_error_tree)
 * Ghidra: void FUN_0048addc(void)
 * Flattens a regex error tree into a flat error list: recursively walks
 * alternations (kind 1) appending each child's message, and unwraps
 * group/leaf kinds (2/6/0xc). Confidence: low. */
word_t sk_h_48addc(word_t p1)
{
    sk_h_00077698();
    sk_h_000a6f68();
    sk_h_004ab034();
    long out = 0;
    if (1 == 1) {
        word_t v = sk_h_004aba88();
        long l6 = *(long *)((v & 0) + 0x10);
        long n = *(long *)(l6 + 0x10);
        if (n != 0) {
            sk_h_0036b270(l6);
            sk_h_000776cc();
            long off = 0x20;
            do {
                word_t u = *(word_t *)(l6 + off);
                sk_h_0036b270(u & 0);
                long sub = (long)sk_h_48addc(u);
                sk_h_0036b118(u & 0);
                word_t subn = *(word_t *)(sub + 0x10);
                word_t cur = *(word_t *)(out + 0x10);
                word_t n2 = cur + subn;
                if (0) { sk_h_00351c7c(0, n2); out = (long)sk_h_00072c0c(); }
                else { out = (long)sk_h_00072c0c(); }
                long dest = out + *(long *)(out + 0x10) * 0x10 + 0x20;
                sk_h_00351b78(); sk_h_0035b67c();
                sk_h_0036b118(sub);
                if (subn != 0) { *(word_t *)(out + 0x10) = *(long *)(out + 0x10) + subn; }
                off += 8; n--;
            } while (n != 0);
            sk_h_0036b118(l6);
            out = (long)0;
        }
    } else if (0xc == 0xc) {
        sk_h_004ab260();
        out = 0;
    } else if (6 == 6) {
        sk_h_004ab260();
        out = *(long *)(0 + 0x58);
        sk_h_48addc(out);
        sk_h_00136bf8();
    }
    sk_h_0007767c(out, 0);
    return out;
}

/* FUN_0048ba64 @ 0x0048ba64   (est. sk_regex_drain_error_queue)
 * Ghidra: void FUN_0048ba64(void)
 * Drains the error queue at +0x50: while non-empty, formats each entry via
 * FUN_0044cc6c/FUN_0044cb38 and releases it. Confidence: low. */
void sk_h_48ba64(word_t x20)
{
    while (*(long *)(*(long *)(x20 + 0x50) + 0x10) != 0) {
        word_t u = sk_h_0044cc6c();
        sk_h_0044cb38((word_t)sk_h_004a4310, (word_t)&(word_t){0});
        sk_h_0036b118(u);
        sk_h_00463878();
        sk_h_0041d788();
    }
}

/* FUN_0048bb04 @ 0x0048bb04   (est. sk_regex_print_alternation)
 * Ghidra: void FUN_0048bb04(void)
 * Prints an alternation: walks the group list, reorders branches so a
 * single-element tail becomes the final branch, and emits each branch (with a
 * preceding "|" where needed). Confidence: low. */
void sk_h_48bb04(word_t p1, word_t p2)
{
    sk_r29_pair_t d = sk_h_0008e518();
    long total = *(long *)(d.lo + 0x10);
    sk_h_000a6fe0();
    word_t out = 0;
    if (total != 0) {
        sk_h_004abfa8(); sk_h_0049a5ac();
        word_t *e = (word_t *)(0 + 0x20);
        do {
            word_t w = *e;
            if (((w >> 0x3b) & 0x1e | (w >> 2) & 1) == 0xc) { sk_h_004ab4e8(); w = *(word_t *)((w & 0) + 0x10); }
            word_t n = *(word_t *)(0 + 0x10);
            word_t cap = *(word_t *)(0 + 0x18);
            sk_h_004ab4e8();
            sk_h_0036b270(w & 0);
            if (cap >> 1 <= n) { sk_h_004ac698(); sk_h_000dbc98(); sk_h_0049a5ac(); }
            *(word_t *)(0 + 0x10) = n + 1;
            *(word_t *)(0 + n * 0x18 + 0x20) = w;
            *(word_t *)(0 + n * 0x18 + 0x28) = 0;
            *(unsigned char *)(0 + n * 0x18 + 0x30) = 0;
            total--; e++;
        } while (total != 0);
    }
    sk_h_004acbbc(); sk_h_0036a9a0(0, (word_t)&(word_t[7]){0});
    sk_h_0036b118(0);
    sk_h_003a25d4(0xe000000000000000);
    sk_h_0008e500(0);
}

/* FUN_0048c284 @ 0x0048c284   (est. sk_regex_print_quantifier)
 * Ghidra: void FUN_0048c284(void)
 * Prints a quantifier: reads the min/max fields from the header at unaff_x20
 * and emits "{m,n}" / "{m,}" / "{n}" / "{n...}", or the "?..." lazy/possessive
 * suffix, or special-case forms (ZeRoOrMoRe / oNeOrMoRe / oPtionaL) when the
 * bounds are unbounded. Confidence: medium (tagged field decode). */
void sk_h_48c284(word_t *x20)
{
    word_t d = sk_h_00354a34().lo;
    long a = *x20, b = x20[1];
    long c = x20[4], e = x20[5];
    long lo = 0, hi = 0xe000000000000000;
    word_t kind = e >> 0x3d;
    switch (kind) {
    case 4: {
        long g = x20[6], h = x20[7];
        long c2 = x20[2], d2 = x20[3];
        if (e == 0x8000000000000000 && c == 0 && b == 0 && a == 0 && h == 0 && g == 0 && d2 == 0 && c2 == 0) {
            hi = 0xea00000000006572; lo = 0x6f4d724f6f72655a;  /* "ZeRoOrMo re" */
        } else {
            lo = 0x726f4d724f656e4f;  /* "oNeOrMo r" */
            if (e != 0x8000000000000000 || a != 1 || c != 0 || b != 0 || h != 0 || g != 0 || d2 != 0 || c2 != 0)
                lo = 0x6c616e6f6974704f;  /* "Optio nal" */
            hi = 0xe900000000000065;
            if (e != 0x8000000000000000 || a != 1 || c != 0 || b != 0 || h != 0 || g != 0 || d2 != 0 || c2 != 0)
                hi = 0xea0000000000796c;  /* "l y" */
        }
        break;
    }
    default: {
        sk_h_000b430c(); sk_h_002a4ab4(0x11);
        sk_h_003a25d4(0);
        sk_h_004ab6d8(); sk_h_004abfd8(0);
        sk_h_000f4ae8(); sk_h_00462abc(0); sk_h_004ac2c4();
        lo = 0; hi = 0xe000000000000000;
        break;
    }
    }
    sk_h_00354ef8(lo, hi, d);
}

/* FUN_0048c564 @ 0x0048c564   (est. sk_regex_print_capture_sep)
 * Ghidra: void FUN_0048c564(void)
 * Prints a capture separator: ", " (or the property form), then the capture
 * tag and range. Confidence: low. */
void sk_h_48c564(word_t x21, word_t x22, long x24, long *x3)
{
    sk_h_00354744();
    sk_h_000867ec(); sk_h_004acba8();
    sk_r29_pair_t d;
    if ((*x3 == x24 && x3[1] == -0x1a00000000000000) || ((sk_h_002a0cf8() & 1) != 0)) {
        sk_h_004acc90();
        d = sk_h_00464e34();
    } else {
        sk_h_4852ac((word_t *)&(word_t){0});
        sk_h_003a25d4(0);
        sk_h_004acc90();
        d.lo = 0x202c; d.hi = 0xe200000000000000;   /* ", " */
    }
    sk_h_002acbb8(d.lo, d.hi);
    sk_h_004aca4c(0);
    sk_h_0044ca08();
    sk_h_003a25d4(0);
    sk_h_0036b270();
    sk_h_00100e34(); sk_h_002acbb8();
    sk_h_0044ca08(x22, x21);
    sk_h_003a25d4(x21);
    sk_h_0044ca2c();
    sk_h_003544c8(0);
}

/* FUN_0048c644 @ 0x0048c644   (est. sk_regex_print_capture_sep2)
 * Ghidra: void FUN_0048c644(void)
 * Second capture-separator printer (like 48c564 but via sk_h_48c718).
 * Confidence: low. */
void sk_h_48c644(long x24, long *x3)
{
    sk_r29_pair_t d = sk_h_00354744();
    sk_h_004acba8();
    sk_r29_pair_t v;
    if ((*x3 == x24 && x3[1] == -0x1a00000000000000) || ((sk_h_002a0cf8() & 1) != 0)) {
        sk_h_004acc90();
        v = sk_h_00464e34();
    } else {
        sk_h_4852ac((word_t *)&(word_t){0});
        sk_h_003a25d4(0);
        sk_h_004acc90();
        v.lo = 0x202c; v.hi = 0xe200000000000000;
    }
    sk_h_002acbb8(v.lo, v.hi);
    sk_h_004aca4c(0);
    sk_h_0044ca08();
    sk_h_003a25d4(0);
    sk_h_48c718(d.lo, d.hi & 1, 0, 0);
    sk_h_00100e34(); sk_h_0044ca08(); sk_h_0044ca2c();
    sk_h_003544c8(0);
}

/* FUN_0048c718 @ 0x0048c718   (est. sk_regex_print_capture)
 * Ghidra: void FUN_0048c718(...4 args)
 * Prints a capture: reads the capture tag/name, emits the group marker, and
 * when the capture references a subpattern or character class, prints the
 * nested element (via sk_h_48d694 / the char-set printer). Confidence: low. */
void sk_h_48c718(word_t p1, word_t p2, word_t p3, word_t p4)
{
    sk_r29_pair_t d = sk_h_00354744();
    word_t lh = d.lo, flag = d.hi & 1;
    word_t lo = 0, hi = 0xe000000000000000;
    sk_h_0036b118(0);
    lo = 0; hi = 0xe000000000000000;
    sk_h_002a4ab4(0x18);
    sk_h_003a25d4(0xe000000000000000);
    sk_h_004aaab0();
    sk_h_004abbac(); sk_h_00351384(); sk_h_002acbb8();
    sk_h_004657ac(); sk_h_002acbb8();
    sk_h_00100e34(); sk_h_002acbb8();
    sk_h_0044ca60();
    if ((p3 & 1) != 0) { sk_h_00350618(); sk_h_002acbb8(); sk_h_003a25d4(0); sk_h_00100e34(); sk_h_002acbb8(); }
    sk_h_0044ca08(lo, hi);
    sk_h_003a25d4(hi);
    if ((p4 & 1) != 0) sk_h_0044ca2c();
    sk_h_003a25d4(0);
    sk_h_0008e500(0);
}

/* FUN_0048ce80 @ 0x0048ce80   (est. sk_regex_emit_class_property)
 * Ghidra: ulong FUN_0048ce80(long param_1)
 * Emits a character-class property/atom: decodes the class element kind and
 * prints the corresponding regex text (char literal, \\u{...}, the anchor
 * set ^/$, \\b/\\B, any-of-these classes, named groups, the "any" char, or a
 * "."). Returns the printed descriptor. Confidence: medium. */
word_t sk_h_48ce80(long p1)
{
    sk_h_00117cc4((word_t)&(word_t[22]){0});
    word_t kind = sk_h_0049e2d4((word_t)&(word_t[22]){0});
    word_t out = 0x796e612e;   /* ".any" */
    switch (kind) {
    default:
        sk_h_0049e2f0((word_t)&(word_t[22]){0}, 0xe400000000000000, 1);
        sk_r29_pair_t d = sk_h_004ab60c();
        sk_h_0046c4e0(d.lo, d.hi, 0x5c5c, 0xe200000000000000, 0x7fffffffffffffff);
        sk_h_004aab74(); sk_h_0046c4e0();
        sk_h_000b43e8(); sk_h_003a25d4(0);
        out = 0x22;
        break;
    case 1:
        sk_h_0049e2f0((word_t)&(word_t[22]){0}, 0xe400000000000000, 1);
        out = 0x22;
        break;
    case 2:
        out = sk_h_48e570(*(unsigned char *)(word_t)sk_h_0049e2f0((word_t)&(word_t[22]){0}, 0xe400000000000000, 1).lo).lo;
        break;
    case 3: {
        /* anchors ^ $ \\b \\B \\A \\z ... */
        word_t a = *(unsigned char *)sk_h_0049e2f0((word_t)&(word_t[22]){0}, 0xe400000000000000, 1);
        out = 0x2f5e2f;   /* "/^/" */
        switch (a) {
        case 2: case 10: case 11: out = 0x2f242f; break;  /* "/$/" */
        case 1: case 3: case 4: case 8: case 12:
            sk_h_004aa8f0(0, 0x2f5e2f, 0xe300000000000000, 0);
            out = 0x2f5e2f;
            break;
        case 5: case 6: case 7: case 9:
            out = 0x2f5e2f;
            break;
        }
        break;
    }
    case 4:
        sk_h_0049e2f0((word_t)&(word_t[22]){0}, 0xe400000000000000, 1);
        sk_h_004aa8f0();
        out = 7;
        break;
    case 5: case 6: case 7: case 8: case 9: case 10:
        sk_h_0049e2f0((word_t)&(word_t[22]){0}, 0xe400000000000000, 1);
        out = 0x2f2e2f;
        break;
    }
    return out;
}

/* FUN_0048d400 @ 0x0048d400   (est. sk_regex_has_multi_branch)
 * Ghidra: void FUN_0048d400(void)
 * Reports whether the alternation has more than one branch: a single tree
 * entry with kind not in the special set, else after draining the work vector,
 * whether any element remains. Confidence: low. */
void sk_h_48d400(void)
{
    sk_r29_pair_t d = sk_h_00084220();
    word_t n = *(word_t *)(d.lo + 0x10);
    bool multi = false;
    if (n == 1) {
        word_t k = sk_h_0049df0c((word_t)&(word_t[44]){0});
        multi = (k - 8) < 0xfffffffd;
    } else {
        word_t i = 0;
        sk_h_000776cc();
        while (n != i) {
            if (n <= i) SK_TRAP(0x48d554);
            word_t k = sk_h_0049df0c((word_t)&(word_t[44]){0});
            i++;
        }
        long l = *(long *)(0 + 0x10);
        sk_h_0036b118(0);
        multi = l == 0;
    }
    sk_h_00084234(multi, d.hi);
}

/* FUN_0048d554 @ 0x0048d554   (est. sk_regex_is_grouped_lookaround)
 * Ghidra: bool FUN_0048d554(void)
 * True when the current element is a lookaround/group construct: kind 4, or
 * kind in 5..8, or a named lookbehind/lookahead with matching tags.
 * Confidence: low. */
bool sk_h_48d554(void)
{
    sk_r29_pair_t d = sk_h_00463f94();
    sk_h_00117cc4(d.lo, d.hi, 0x99);
    int k = (int)sk_h_00458af8((word_t)&(word_t[20]){0}).lo;
    if (k == 4) return true;
    if (k >= 5 && k <= 8) { sk_h_00458b14((word_t)&(word_t[20]){0}); return true; }
    sk_h_00458b14((word_t)&(word_t[20]){0});
    sk_h_004ac2a0();
    return false;
}

/* FUN_0048d694 @ 0x0048d694   (est. sk_regex_emit_named_group)
 * Ghidra: long FUN_0048d694(void)
 * Emits a named group: decodes the group kind and prints the corresponding
 * regex text (char-class \\c, \\M-\\C-..., name references, subpattern/callout
 * TODO placeholders). Returns the printed descriptor. Confidence: medium. */
long sk_h_48d694(void)
{
    sk_h_00465258((word_t)&(word_t[20]){0});
    word_t k = sk_h_00458af8((word_t)&(word_t[20]){0}).lo;
    long out = 0x2365756c6176233c;   /* "<#value<#..." */
    switch (k & 0xffffffff) {
    case 3:
        sk_h_00458b14((word_t)&(word_t[20]){0});
        sk_r29_pair_t d = sk_h_48a244();
        out = d.lo;
        break;
    case 4:
        sk_h_00458b14((word_t)&(word_t[20]){0});
        out = 0x5c;
        break;
    case 5: case 6: case 7:
        sk_h_00458b14((word_t)&(word_t[20]){0});
        out = 0x635c;
        break;
    case 8:
        sk_h_00458b14((word_t)&(word_t[20]){0});
        sk_h_004ac8d4();
        out = 0;
        break;
    case 9: sk_h_00458b14((word_t)&(word_t[20]){0}); sk_h_004ab930(0); out = -8; break;
    case 10: sk_h_00458b14((word_t)&(word_t[20]){0}); sk_h_004ab930(0); out = -0xc; break;
    case 11: sk_h_00458b14((word_t)&(word_t[20]){0}); sk_h_004ab930(0); out = -0xf; break;
    case 12: case 13: sk_h_00458b14((word_t)&(word_t[20]){0}); out = -0x2fffffffffffffdd; break;
    case 14: out = 0x2e; break;
    case 15: case 16:
        sk_h_00350d94(0x471, k, 0xe90000000000003e);
        sk_h_004abe24(); sk_h_0006f768(); sk_h_001afa84();
    default:
        sk_h_00458b14((word_t)&(word_t[20]){0});
        sk_r29_pair_t e = sk_h_00417b60();
        out = e.lo;
        break;
    }
    return out;
}

/* FUN_0048d990 @ 0x0048d990   (est. sk_regex_emit_char_escape)
 * Ghidra: undefined1[16] FUN_0048d990(void)
 * Emits a character escape: prints "\\u{...}" via the hex formatter.
 * Confidence: medium. */
sk_r29_pair_t sk_h_48d990(void)
{
    word_t lo = sk_h_004abad8(0x755c);   /* "\\u" */
    word_t hi = 0;
    sk_h_000863bc(); sk_h_004ab810(); sk_h_00355754((word_t)&(word_t){lo});
    sk_h_001ebfb0(); sk_h_004ab5a4(); sk_h_002acbb8();
    sk_h_003a25d4(); sk_h_00463878(); sk_h_002acbb8();
    sk_r29_pair_t r; r.hi = hi; r.lo = lo; return r;
}

/* FUN_0048d9f8 @ 0x0048d9f8   (est. sk_regex_scan_branches)
 * Ghidra: void FUN_0048d9f8(void)
 * Scans the alternation branches: iterates the branch list, and for each
 * branch classifies it (quantifier/group/atom) via FUN_0049df0c and either
 * follows it or recurses. Returns whether any branch matched. Confidence: low. */
word_t sk_h_48d9f8(void)
{
    sk_r29_pair_t d = sk_h_00084220();
    long n = *(long *)(d.lo + 0x10);
    for (;;) {
        if (n == 0) { sk_h_00084234(0, d.hi); return 0; }
        word_t k = sk_h_0049df0c((word_t)&(word_t[44]){0});
        if (k > 7) { sk_h_00084234(1, d.hi); return 1; }
        switch (k) {
        case 1: case 2:
            sk_h_0049df18((word_t)&(word_t[44]){0});
            break;
        case 5: case 6: case 7:
            sk_h_0049df18((word_t)&(word_t[44]){0});
            if (sk_h_48d9f8() & 1) { sk_h_004a3918((word_t)&(word_t[44]){0}); sk_h_00084234(0, d.hi); return 0; }
            break;
        default:
            break;
        }
        n--;
    }
}

/* FUN_0048dddc @ 0x0048dddc   (est. sk_regex_print_class)
 * Ghidra: void FUN_0048dddc(long param_1, ulong param_2, ulong param_3, ulong param_4)
 * Prints a character-class group: "[", an optional "^" (param_2), each class
 * element via FUN_0048e76c, "]", and the closing tag ("]" or "/#").
 * Confidence: medium. */
void sk_h_48dddc(long p1, word_t p2, word_t p3, word_t p4)
{
    sk_h_0044ca60();
    if ((p3 & 1) != 0) sk_h_0044ca08(0x2f23, 0xe200000000000000);   /* "/#" */
    sk_h_004ac3f0();
    if ((p2 & 1) != 0) sk_h_0044ca08(0x5e, 0xe100000000000000);      /* "^" */
    long n = *(long *)(p1 + 0x10);
    if (n != 0) {
        p1 = p1 + 0x20;
        do {
            sk_h_00117cc4((word_t)&(word_t[44]){0}, p1, 0x160);
            sk_h_004ac7b0(); sk_h_004a3940();
            sk_h_48e76c((word_t)&(word_t[44]){0});
            sk_h_004a3918((word_t)&(word_t[44]){0});
            p1 = p1 + 0x160; n--;
        } while (n != 0);
    }
    sk_h_0044ca08(0x5d, 0xe100000000000000);   /* "]" */
    if ((p3 & 1) != 0) {
        if ((p4 & 1) == 0) sk_h_0044ca08(0x232f, 0xe200000000000000);   /* "/#" */
        else sk_h_0041d788();
    }
}

/* FUN_0048deb0 @ 0x0048deb0   (est. sk_regex_print_group)
 * Ghidra: void FUN_0048deb0(void)
 * Prints a regex group/atom: decodes the group kind and emits the DSL snippet
 * (quantifiers, captures, alternations, lookarounds). Confidence: low. */
void sk_h_48deb0(void)
{
    sk_r29_pair_t d = sk_h_0008e518();
    word_t flag = d.hi;
    sk_h_00117cc4((word_t)&(word_t[44]){0}, d.lo, 0x160);
    word_t kind = sk_h_0049df0c((word_t)&(word_t[44]){0});
    switch (kind) {
    case 1: case 2:
        sk_h_004ab0f0((word_t)&(word_t[22]){0});
        sk_h_00117cc4();
        sk_h_0044ca60();
        sk_h_48ce80((long)(word_t)&(word_t[22]){0});
        break;
    case 3:
        sk_h_004ac6f8();
        sk_h_48c718(0, 0, 0, 0);
        break;
    case 5: case 6: case 7:
        sk_h_004ab3c4();
        if (flag == 0) { sk_h_004aadfc(); sk_h_004abbd4(); sk_h_004aa824(); sk_h_0044cb38((word_t)sk_h_004a4914); }
        else { sk_h_00354d5c(); sk_h_48d400(); sk_h_004aadfc(); sk_h_004abbd4(); sk_h_004aa824(); sk_h_0044cb38((word_t)sk_h_004a4914); }
        break;
    default:
        sk_h_004ab0f0((word_t)&(word_t[22]){0});
        sk_h_00117cc4();
        sk_h_0044ca60();
        sk_h_004ac210((word_t)&(word_t[22]){0});
        break;
    }
    sk_h_00354d5c();
    sk_h_48d400();
    sk_h_0008e500(0);
}

/* FUN_0048e570 @ 0x0048e570   (est. sk_regex_char_property_name)
 * Ghidra: undefined1[16] FUN_0048e570(undefined1 param_1)
 * Returns the property-name string for a character-class property kind:
 * "digit", "verticalWhitespace", "horizontalWhitespace", "newlineSequence",
 * "anyGraphemeCluster", "any" etc. Confidence: high (string literals). */
sk_r29_pair_t sk_h_48e570(word_t p)
{
    word_t lo = 0x74696769642e, hi = 0xe600000000000000;   /* ".digit" */
    switch (p) {
    case 1: lo = 0x692e74696769642e; hi = 0xef6465747265766e; break;   /* "digit.e vnerted." */
    case 2: sk_h_004aa8f0(0); hi = 0; lo = 2; break;
    case 3: sk_h_004aa8f0(0); hi = 0; lo = 0xb; break;
    case 4: sk_h_004aa8f0(0); lo = -3; hi = 0; break;
    case 5: sk_h_004aa8f0(0); hi = 0; lo = 6; break;
    case 6: lo = 0x707365746968772e; hi = 0xeb00000000656361; break;   /* ".whitespace" */
    case 7: sk_h_004aa8f0(0); hi = 0; lo = 1; break;
    case 8: lo = 0xd000000000000013; hi = 0x80000000005e2d40; break;   /* vertical whitespace */
    case 9: sk_h_004aa8f0(0); hi = 0; lo = 9; break;
    case 10: lo = 0x64726f772e; hi = 0xe500000000000000; break;        /* ".word" */
    case 11: lo = 0x6e692e64726f772e; hi = 0xee00646574726576; break;  /* ".word.inverted" */
    case 12: lo = 0xd000000000000013; hi = 0x80000000005e2da0; break;  /* any grapheme cluster */
    case 13: sk_h_00350d94(0x341, 0x74696769642e, 0xe600000000000000); sk_h_004aac40(); sk_h_001afa84();
    }
    sk_r29_pair_t r; r.hi = hi; r.lo = lo; return r;
}

/* FUN_0048e76c @ 0x0048e76c   (est. sk_regex_print_class_element)
 * Ghidra: void FUN_0048e76c(undefined8 param_1)
 * Prints one character-class element: decodes its kind and emits the text
 * (char, range "a-z", negated, union, or a group via sk_h_48ebd8/48d694).
 * Confidence: low. */
void sk_h_48e76c(word_t p1)
{
    sk_h_00117cc4((word_t)&(word_t[44]){0}, p1, 0x160);
    word_t kind = sk_h_0049df0c((word_t)&(word_t[44]){0});
    switch (kind) {
    default:
        sk_h_004ab0f0((word_t)&(word_t[22]){0});
        sk_h_00117cc4();
        sk_h_004ab0f0((word_t)&(word_t[22]){0});
        sk_h_00117cc4();
        if (sk_h_004ac210((word_t)&(word_t[22]){0}) != 0) {
            sk_h_0049e2f0((word_t)&(word_t[22]){0});
            sk_h_000e0654();
        }
        break;
    case 1:
        sk_h_004ab0f0((word_t)&(word_t){0});
        sk_h_00117cc4();
        sk_h_004ac52c((word_t)&(word_t[22]){0});
        sk_h_48ebd8();
        sk_h_0044ca08();
        sk_h_003a25d4(0);
        sk_h_0044ca08(0x2d, 0xe100000000000000);   /* "-" */
        sk_h_48ebd8();
        break;
    case 2:
        sk_h_004ac6f8();
        sk_h_48dddc(0, 0, 0, 0);
        return;
    case 3:
        sk_h_0049df18((word_t)&(word_t[44]){0});
        sk_h_002acbb8(0, 0);
        sk_h_004accb4();
        sk_h_0044ca08(0x515c, 0xe200000000000000);
        break;
    case 5: case 6: case 7:
        sk_h_004ab4f4();
        sk_h_004ac3f0();
        sk_h_004abe5c(0x5d);
        sk_h_0044ca08(0x2626, 0xe200000000000000);   /* "&&" (union) */
        sk_h_0044ca60();
        sk_h_004ac3f0();
        break;
    }
    sk_h_0044ca08(0x5d, 0xe100000000000000);   /* "]" */
}

/* FUN_0048ebd8 @ 0x0048ebd8   (est. sk_regex_print_char_atom)
 * Ghidra: void FUN_0048ebd8(void)
 * Prints a single character atom: reads the atom kind and emits either a char
 * literal (escaped) or a TODO placeholder (character-class/assertion/
 * backreference/symbolic-reference). Confidence: medium. */
void sk_h_48ebd8(void)
{
    sk_h_004ab0f0((word_t)&(word_t[22]){0});
    sk_h_00117cc4();
    word_t kind = sk_h_0049e2d4((word_t)&(word_t[22]){0});
    switch (kind) {
    default:
        sk_h_0049e2f0((word_t)&(word_t[22]){0});
        sk_h_004accfc((word_t)&(word_t){0});
        sk_h_004acd14((word_t)&(word_t){0});
        break;
    case 1: {
        word_t c = *(word_t *)sk_h_0049e2f0((word_t)&(word_t[22]){0});
        sk_h_000863bc(); sk_h_004ab810(); sk_h_00355754((word_t)&(word_t){c});
        sk_h_001ebfb0();
        sk_h_004abad8(0x755c);   /* "\\u" */
        sk_h_002acbb8(); sk_h_003a25d4(0);
        sk_h_00463878(); sk_h_002acbb8();
        break;
    }
    case 2: sk_h_0049e2f0((word_t)&(word_t[22]){0}); sk_h_004ab2d0(0); break;  /* TODO: character classes */
    case 3: sk_h_0049e2f0((word_t)&(word_t[22]){0}); sk_h_004ab2d0(0); break;  /* TODO: assertions */
    case 4: sk_h_0049e2f0((word_t)&(word_t[22]){0}); sk_h_004ab2d0(0); break;  /* TODO: backreferences */
    case 5: sk_h_0049e2f0((word_t)&(word_t[22]){0}); sk_h_004ab2d0(0); break;  /* TODO: symbolic references */
    case 6: {
        long l4 = sk_h_0049e2f0((word_t)&(word_t[22]){0});
        long n = *(long *)(*(long *)(l4 + 0x18) + 0x10);
        if (n != 0) {
            unsigned char *e = (unsigned char *)(*(long *)(l4 + 0x18) + 0x20);
            do { if (*e == 5) sk_h_002acbb8(0x29553f28, 0xe400000000000000); n--; e += 0x18; } while (n != 0);
        }
        break;
    }
    case 7:
        sk_h_0049e2f0((word_t)&(word_t[22]){0});
        sk_h_00117cc4((word_t)&(word_t){0}, 0, 0xb0);
        sk_h_48d694();
        sk_h_00351e08();
        break;
    }
    sk_h_0007c1c4();
}

/* FUN_0048ee54 @ 0x0048ee54   (est. sk_regex_emit_range_sep)
 * Ghidra: undefined1[16] FUN_0048ee54(void)
 * Emits a range separator (the ".." / "-" span). Confidence: low. */
sk_r29_pair_t sk_h_48ee54(void)
{
    sk_h_004abbac(); sk_h_004ab968(); sk_h_002acbb8();
    sk_h_004657ac(); sk_h_002acbb8();
    return (sk_r29_pair_t){0, 0};
}

/* FUN_0048ee9c @ 0x0048ee9c   (est. sk_regex_class_kind_byte)
 * Ghidra: undefined1 FUN_0048ee9c(void)
 * Returns the class-kind byte for the current element: 0xd for unknown, 10 for
 * a 0x10-kind, 9 for kind 0xf, else a lookup into the DAT_005a5eb0 table for
 * kinds 0x15..0x1e. Confidence: medium. */
word_t sk_h_48ee9c(void)
{
    sk_r29_pair_t d = sk_h_00463f94();
    sk_h_00117cc4(d.lo, d.hi, 0x99);
    int k = (int)sk_h_00458af8((word_t)&(word_t[20]){0}).lo;
    if (k == 4) {
        word_t b = *(unsigned char *)(word_t)sk_h_00458b14((word_t)&(word_t[20]){0}).lo;
        if (b - 0x15 < 10) return 0xd;   /* DAT_005a5eb0[b-0x15] */
        return 0xd;
    }
    if (k == 0x10) return 10;
    if (k == 0xf) return 9;
    return 9;
}

/* FUN_0048ef24 @ 0x0048ef24   (est. sk_regex_print_property)
 * Ghidra: void FUN_0048ef24(void)
 * Prints a regex property/atom by kind: scalar, string, char-class properties
 * (\\h \\H \\R \\N \\v \\V \\s \\S \\w \\W ...), anchors, back-reference and
 * subpattern TODO placeholders. Confidence: medium. */
void sk_h_48ef24(void)
{
    sk_h_00465258((word_t)&(word_t[20]){0});
    sk_r29_pair_t d = sk_h_00458af8((word_t)&(word_t[20]){0});
    if (d.lo > 0x10) goto done;
    switch (d.lo) {
    default: sk_h_00458b14((word_t)&(word_t[20]){0}); sk_h_004589e8(); break;
    case 1: { word_t c = *(word_t *)sk_h_00458b14((word_t)&(word_t[20]){0}); sk_h_48d990(); sk_h_00351e08(); break; }
    case 2:
        sk_h_00458b14((word_t)&(word_t[20]){0});
        sk_h_000e0654();
        sk_h_0041449c();
        sk_h_0036b118(0);
        break;
    case 3: sk_h_00458b14((word_t)&(word_t[20]){0}); break;
    case 4: {
        sk_r29_pair_t v = sk_h_00458b14((word_t)&(word_t[20]){0});
        word_t b = *(unsigned char *)v.lo;
        if (b - 7 > 0x17) {
            sk_h_002a4ab4(0x10);
            sk_h_002acbb8(0x7365203a4f444f54, 0xee00206465706163);  /* "TODO: escape" */
            sk_h_000f4a9c(0, 0, 0x683710);
            sk_h_00205844((word_t)&(word_t){b}, (word_t)&(word_t){0});
        } else {
            switch (b) {
            case 8: break;
            case 9: sk_h_004abf10(); sk_h_004aa694(); break;
            case 10: sk_h_004aa694(0); break;   /* \h */
            case 11: sk_h_004aa694(0); break;   /* \H */
            case 12: sk_h_004aa694(0); break;   /* \R */
            case 13: sk_h_004aa694(0); break;   /* \N */
            case 14: sk_h_004ac98c(); sk_h_004ab2d0(0); break;  /* \s */
            case 15: sk_h_004ac98c(); sk_h_004ab2d0(0); break;  /* \S */
            case 16: sk_h_004abf30(); sk_h_004aa694(); break;   /* \v */
            case 17: sk_h_004abf10(); sk_h_004aa694(); break;   /* \V */
            case 18: sk_h_004aa694(0); break;   /* \w */
            case 19: sk_h_004aa694(0); break;   /* \W */
            case 20: sk_h_004ac98c(); sk_h_004ab2d0(0); break;  /* \b */
            case 21: sk_h_004aa694(0); break;   /* \A */
            case 22: sk_h_004aa694(0); break;   /* \z */
            case 24: sk_h_004ac98c(); sk_h_004ab2d0(0); break;  /* \B */
            case 25: sk_h_004aa694(0); break;   /* \G */
            case 29: sk_h_004abf40(); sk_h_004aa694(); break;  /* \X */
            case 30: sk_h_004abf20(0, 0, 1); sk_h_004aa694(); break;  /* \C */
            default: sk_h_004aa694(); break;
            }
        }
        break;
    }
    case 5: case 6: case 7:
        sk_h_00458b14((word_t)&(word_t[20]){0});
        sk_h_004589e8();
        break;
    case 8: sk_h_00458b14((word_t)&(word_t[20]){0}); sk_h_004abf30(); sk_h_004aa694(); break;
    case 9: sk_h_00458b14((word_t)&(word_t[20]){0}); sk_h_004aa694(0); break;   /* TODO: back reference */
    case 10: sk_h_00458b14((word_t)&(word_t[20]){0}); sk_h_004aa694(0); break;  /* TODO: subpattern */
    case 11: sk_h_00458b14((word_t)&(word_t[20]){0}); sk_h_004aa694(0); break;  /* TODO: callout */
    case 12: sk_h_00458b14((word_t)&(word_t[20]){0}); sk_h_004aa694(); break;
    case 13: sk_h_00458b14((word_t)&(word_t[20]){0}); sk_h_004aa694(); break;
    case 14: break;
    case 15: case 16:
        sk_h_004abe24(0xeb00000000656361, 0, 0, 0);
        sk_h_0006f768(); sk_h_001afa84();
    }
done:
    sk_h_0007c1c4();
}

/* FUN_0048f61c @ 0x0048f61c   (est. sk_regex_ast_to_dsl)
 * Ghidra: void FUN_0048f61c(void)
 * Converts a regex AST node into a RegexBuilder DSL representation. The node
 * kind (tag >> 0x3c) selects the converter:
 *   0/1  alternation of child nodes (walked, recursing into each child)
 *   2    capture/group (optionally a named group)
 *   3    conditional/quantifier pair
 *   4    alternation of scalar lists
 *   5/6  word/any atom
 *   7    anchored scalar (with the AppleInternal build-suffix string)
 *   8    char-class list
 *   9/10 lookaround/capture references
 *   0xb  empty node
 * Each builder allocates a 0x10+ node object via FUN_0036a940 (tagged
 * 0x6000000000000000) carrying {value, child}. Confidence: low (large
 * register-global AST state machine). */
word_t sk_h_48f61c(word_t p1, word_t p2, word_t x21)
{
    sk_r29_pair_t d = sk_h_00353cfc();
    word_t node = d.lo;
    word_t kind = node >> 0x3c;
    word_t child = 0x8000000000000000;
    word_t out = 0;
    switch (kind) {
    case 0: case 1: {
        long l18 = *(long *)(node + 0x10);
        long n = *(long *)(l18 + 0x10);
        if (n != 0) {
            sk_h_0036b270(l18);
            sk_h_004ab448();
            sk_h_0049a530();
            do {
                sk_h_004ac120();
                if (kind > 10) SK_TRAP(0x48fdf4);
                sk_h_004ac574(); sk_h_004aca94();
                word_t r = sk_h_48f61c(0, 0, x21);
                if (x21 != 0) goto trap;
                sk_h_004ab26c();
                word_t k = 0 & 0xfffffffe | (r >> 2 & 1);
                if (k > 0xb) SK_TRAP(0x48fdf4);
                if (k == 0xc) { sk_h_0036b118(0); }
                else { sk_h_004aa794(); word_t u = sk_h_0036a940(); *(word_t *)(u + 0x10) = r; *(word_t *)(u + 0x18) = 0; }
                sk_h_004ac96c();
                if (k > 0xb) { sk_h_0006b42c(); sk_h_004abb28(); sk_h_0049a530(); }
                sk_h_004ac2f4();
            } while (1);
        }
        sk_h_004aa83c();
        long lv = (long)sk_h_0036a940();
        *(word_t *)(lv + 0x10) = 0;
        break;
    }
    case 2:
        sk_h_00117cc4((word_t)&(word_t){0}, (node & 0xfffffffffffffff) + 0x10, 0x68);
        child = *(word_t *)((node & 0xfffffffffffffff) + 0x78);
        sk_h_004a4ac4((word_t)&(word_t){0}, (word_t)&(long[18]){0}, 0x657a00, 0);
        sk_h_0036b270(child & 0xfffffffffffffff);
        sk_h_004ac9f8();
        sk_h_48f61c(0, 0, x21);
        if (x21 != 0) goto trap;
        sk_h_004aae2c();
        if (child >> 0x3c == 0xb) { sk_h_0036b118(child & 0xfffffffffffffff); }
        else { sk_h_004aa794(); word_t u = sk_h_0036a940(); *(word_t *)(u + 0x10) = node & 0xfffffffffffffff; *(word_t *)(u + 0x18) = child; out = u | 0x6000000000000000; }
        sk_h_004aada4();
        long nv_a = (long)sk_h_0036a940();
        *(word_t *)(nv + 0x10) = 0;
        *(word_t *)(nv + 0x18) = 0;
        *(word_t *)(nv + 0x20) = 0;
        *(word_t *)(nv + 0x28) = 1;
        *(word_t *)(nv + 0x30) = out;
        *(word_t *)(nv + 0x38) = 0;
        *(word_t *)(nv + 0x40) = 0;
        *(word_t *)(nv + 0x48) = 0;
        *(word_t *)(nv + 0x50) = 0;
        *(unsigned char *)(nv + 0x58) = 0;
        break;
    case 3:
        sk_h_00117cc4((word_t)&(word_t){0}, (node & 0xfffffffffffffff) + 0x20, 0x90);
        child = *(word_t *)((node & 0xfffffffffffffff) + 0xb0);
        word_t c2 = *(word_t *)((node & 0xfffffffffffffff) + 0xd0);
        sk_h_00458c98((word_t)&(word_t){0}, (word_t)&(long[18]){0});
        sk_h_0036b270(c2 & 0xfffffffffffffff);
        sk_h_0036b270(child & 0xfffffffffffffff);
        sk_h_48f61c(child, 0, x21);
        if (x21 != 0) goto trap;
        sk_h_004aae2c();
        sk_h_004ac9f8();
        sk_h_48f61c(0, 0, x21);
        sk_h_004ab26c();
        if ((0 & 0xfffffffe | 0) == 0xc) { sk_h_0036b118(c2 & 0xfffffffffffffff); }
        else { sk_h_004aa794(); word_t u = sk_h_0036a940(); *(word_t *)(u + 0x10) = 0; *(word_t *)(u + 0x18) = c2; }
        sk_h_004ac8fc(0x687bb8);
        long nv_b = (long)sk_h_0036a940();
        sk_h_00117cc4(nv + 0x10, (word_t)&(word_t){0}, 0x80);
        *(word_t *)(nv + 0x90) = node & 0xfffffffffffffff;
        *(word_t *)(nv + 0x98) = 0;
        break;
    case 4:
        sk_h_0036b270(child & 0xfffffffffffffff);
        sk_h_004ac9f8();
        sk_h_48f61c(0, 0, x21);
        if (x21 != 0) goto trap;
        sk_h_004aae2c();
        sk_h_004aab60();
        long nv2 = (long)sk_h_0036a940();
        *(word_t *)(nv2 + 0x18) = 0;
        *(word_t *)(nv2 + 0x10) = 0;
        *(word_t *)(nv2 + 0x20) = 0;
        *(word_t *)(nv2 + 0x28) = 0;
        *(word_t *)(nv2 + 0x30) = 0;
        *(word_t *)(nv2 + 0x38) = 0;
        *(word_t *)(nv2 + 0x40) = 0;
        *(word_t *)(nv2 + 0x48) = 0;
        *(word_t *)(nv2 + 0x50) = 0x40;
        *(word_t *)(nv2 + 0x58) = 0;
        break;
    case 5: case 6: {
        word_t a = *(word_t *)((node & 0xfffffffffffffff) + 0x10);
        word_t b = *(word_t *)((node & 0xfffffffffffffff) + 0x18);
        sk_h_004aad30();
        long nv_c = (long)sk_h_0036a940();
        *(word_t *)(nv + 0x10) = a;
        *(word_t *)(nv + 0x18) = b;
        child = (kind == 5) ? 0x5000000000000000 : 0x4000000000000004;
        sk_h_0036b270(child, b);
        break;
    }
    case 7:
        sk_h_004aa370(); sk_h_004aaf9c();
        sk_h_004abe68(0);
        break;
    case 8:
        sk_h_00117cc4((word_t)&(word_t[22]){0}, (node & 0xfffffffffffffff) + 0x10, 0xb0);
        sk_h_00117cc4((word_t)&(word_t[20]){0}, (node & 0xfffffffffffffff) + 0x10, 0x99);
        if ((int)sk_h_00458af8((word_t)&(word_t[20]){0}).lo == 2) {
            sk_h_004589e8((word_t)&(word_t[22]){0}, (word_t)&(word_t){0});
            sk_h_00350af4();
            long l18 = sk_h_0041449c();
            long n = *(long *)(l18 + 0x10);
            if (n == 0) { sk_h_0036b118(l18); sk_h_004589f8((word_t)&(word_t[22]){0}); sk_h_000776cc(); }
            else {
                sk_h_000a6f68();
                word_t *outv = (word_t *)0;
                long i = 0;
                while (1) {
                    word_t c = *(word_t *)(l18 + i * 4 + 0x20);
                    sk_h_00466104(0x686228);
                    word_t u = sk_h_0036a940();
                    sk_h_0049ca14((word_t)&(word_t){c});
                    sk_h_00117cc4(u + 0x10, (word_t)&(word_t){0}, 0xb0);
                    word_t idx = *(word_t *)(0 + 0x10);
                    if (*(word_t *)(0 + 0x18) >> 1 <= idx) { sk_h_0006b42c(); sk_h_004abb28(); sk_h_0049a530(); }
                    *(word_t *)(0 + 0x10) = idx + 1;
                    *(word_t *)(0 + idx * 8 + 0x20) = u | 0x4000000000000000;
                    if (n - 1 == i) break;
                    i++;
                }
                sk_h_004589f8((word_t)&(word_t[22]){0});
                long m = *(long *)(l18 + 0x10);
                sk_h_0036b118(l18);
                if (n != m) SK_TRAP(0x48fcf4);
            }
            sk_h_004aa83c();
            long nv_d = (long)sk_h_0036a940();
            *(word_t *)(nv + 0x10) = 0;
        } else {
            sk_h_004aa7bc();
            long nv_e = (long)sk_h_0036a940();
            sk_h_004589e8((word_t)&(word_t[22]){0}, (word_t)&(word_t){0});
            sk_h_48fe4c((word_t)&(word_t[22]){0});
            sk_h_004589f8((word_t)&(word_t[22]){0});
            sk_h_00117cc4(nv + 0x10, (word_t)&(word_t[22]){0}, 0xb0);
        }
        break;
    case 9:
        sk_h_004ac91c();
        long nv3 = (long)sk_h_0036a940();
        sk_h_0036b270(0);
        sk_h_00490174();
        sk_h_004589bc((word_t)&(word_t){0});
        *(word_t *)(nv3 + 0x10) = 0;
        *(unsigned char *)(nv3 + 0x18) = 0 & 1;
        break;
    case 10:
        sk_h_0034db28(0x5000000000000004, 0);
        sk_h_004588cc();
        break;
    case 0xb:
        break;
    }
    sk_h_00353d14(sk_h_004aca94(), d.hi);
    return;
trap:
    sk_h_001ee9f4(x21, 0, 0x25, 1, 0x6d);   /* s_StringProcessing_ASTConversion__005e21e0 */
}

/* FUN_0048fe4c @ 0x0048fe4c   (est. sk_regex_flatten_atom)
 * Ghidra: void FUN_0048fe4c(undefined8 param_1)
 * Flattens a regex atom/group into a char-class list: reads the element kind
 * via FUN_0048ee9c and copies the 0xb0-byte descriptor into param_1, following
 * group/lookaround references recursively. Confidence: low. */
void sk_h_48fe4c(word_t p1)
{
    word_t k = sk_h_48ee9c();
    word_t d0 = k, d1 = 0xe000000000000000;
    if (k != 13) {
        sk_h_0049c9fc((word_t)&(word_t){k});
        sk_h_00117cc4(p1, (word_t)&(word_t){0}, 0xb0);
        return;
    }
    sk_h_00117cc4((word_t)&(word_t[20]){0}, (word_t)&(word_t[20]){0}, 0x99);
    int kind = (int)sk_h_00458af8((word_t)&(word_t[20]){0}).lo;
    if (kind == 4) {
        sk_h_00458b14((word_t)&(word_t[20]){0});
        sk_h_004176bc(*(unsigned char *)0);
        word_t s = sk_h_0034ecc8();
        sk_h_0049ca14((word_t)&(word_t){s});
        sk_h_00117cc4(p1, (word_t)&(word_t){0}, 0xb0);
        return;
    }
    sk_h_00117cc4((word_t)&(long[20]){0}, (word_t)&(word_t[20]){0}, 0x99);
    word_t k2 = sk_h_00458af8((word_t)&(word_t[20]){0});
    if (k2 > 0xe) { sk_h_004accfc((word_t)&(word_t[22]){0}); sk_h_004accfc((word_t)&(word_t){0}); sk_h_0049c838((word_t)&(word_t){0}); sk_h_004a31ec((word_t)&(word_t[22]){0}, (word_t)&(word_t){0}); }
    else {
        switch (k2) {
        case 1: { word_t c = *(word_t *)sk_h_00458b14((word_t)&(long[20]){0}); sk_h_0049ca44((word_t)&(word_t){c}); break; }
        case 4: { sk_r29_pair_t v = sk_h_00458b14((word_t)&(long[20]){0}); d0 = v.lo; break; }
        case 9: { word_t *src = (word_t *)sk_h_00458b14((word_t)&(long[20]){0}); sk_h_00117cc4((word_t)&(word_t){0}, (word_t)src, 0x60); sk_h_004a3214((word_t)&(word_t){0}); break; }
        case 13: { word_t *src = (word_t *)sk_h_00458b14((word_t)&(long[20]){0}); word_t v = src[3]; word_t w = src[7]; sk_h_004a31fc((word_t)&(word_t){0}); sk_h_00117cc4((word_t)&(word_t){0}, (word_t)&(word_t){0}, 0xb0); sk_h_0036b270(v); sk_h_0036b270(w); break; }
        case 14: sk_h_004a322c((word_t)&(word_t){0}); break;
        default: sk_h_004589e8(); break;
        }
    }
    sk_h_00117cc4((word_t)&(word_t){0}, (word_t)&(word_t){0}, 0xb0);
    sk_h_00117cc4(p1, (word_t)&(word_t){0}, 0xb0);
}

extern sk_r29_pair_t sk_h_004815cc(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6, word_t a7, word_t a8); /* FUN_004815cc */

/* FUN_004816c4 @ 0x004816c4   (est. sk_regex_emit_property_class)
 * Ghidra: void FUN_004816c4(void)
 * Dispatches a regex property emission; *unaff_x20 is the property selector
 * word. Adjacent to FUN_004816c0. Confidence: low. */
void sk_h_4816c4(word_t *x20) { sk_h_00492704(*x20, (word_t)sk_h_002298d4); }

/* FUN_0048afec @ 0x0048afec   (est. sk_regex_print_captured_value)
 * Ghidra: void FUN_0048afec(void)
 * Prints a captured/match value expression. The kind (from the tagged node in
 * auVar21) selects the printer:
 *   0/1    capture / alternation lists (sk_h_48bb04)
 *   2      a capture "C" reference
 *   3      a conditional expression (Local/ok/koo, or "TODO: conditional")
 *   4/0xc  nested value (recursion via sk_h_48afec)
 *   5/0xd/0xe/0xf  TODO placeholders (conditional/consumers/validators/
 *          character-predicates)
 *   6      a quantifier/expression with a range (sk_h_48c284)
 *   7      a character class (sk_h_48c718)
 *   8      a class set / property (sk_h_48ce80)
 *   10     an "expression" string
 * The defaults print the "Regex" / value string via sk_h_004aab08.
 * Confidence: low (register-global value node + carry artifacts). */
void sk_h_48afec(word_t u10, word_t u14, word_t *x20)
{
    sk_r29_pair_t d = sk_h_0008e518();
    word_t flag = d.hi & 0xffffffff;
    word_t node = d.lo;
    if ((char)x20[1] != 1) {
        word_t lim = *x20;
        sk_h_00117cc4((word_t)&(word_t[11]){0});
        long chk = sk_h_00092d40();
        if (chk >= (long)lim) { sk_h_48ad50(node); goto fin; }
    }
    if ((char)x20[3] != 1) {
        word_t lim = x20[2];
        long chk = sk_h_0044f098((word_t)&sk_h_006888f0, 0);
        if (chk <= (long)lim) { sk_h_48ad50(node); goto fin; }
    }
    {
        word_t kind = (d.hi >> 0x1b) & 0x1e | (d.lo >> 2) & 1;
        word_t is16 = kind == 0x10;
        switch (kind) {
        case 1: {
            word_t c = *(word_t *)((node & 0xffffffffffffffb) + 0x10);
            word_t ref = sk_h_0036b270(c);
            sk_h_48bb04(ref, flag & 1);
            sk_h_0036b118(c);
            goto fin;
        }
        case 2: {
            node &= 0xffffffffffffffb;
            word_t ref = *(word_t *)(node + 0x30);
            if (*(long *)(node + 0x18) != 0) {
                sk_h_002acbb8(*(word_t *)(node + 0x10));
                sk_h_00100e34(); sk_h_002acbb8();
            }
            sk_h_0041d788((word_t)&(word_t){0x65727574706143});   /* "Captur" */
            word_t out = sk_h_004ab458();
            *(word_t *)(0 + -0x10) = ref;
            sk_h_004aab08(out, 0xe700000000000000);
            sk_h_0041d7dc();
            sk_h_003a25d4(0xe700000000000000);
            goto fin;
        }
        case 3: {
            node &= 0xffffffffffffffb;
            word_t c = *(word_t *)(node + 0x68);
            if (*(char *)(node + 0x60) == 3) {
                sk_h_004ab064(*(word_t *)(node + 0x10), *(word_t *)(node + 0x40),
                              *(word_t *)(node + 0x50), *(word_t *)(node + 0x20),
                              *(word_t *)(node + 0x30), c);
                if (3 == 3 && 0 == 0 && 0 == 0) {
                    word_t o = sk_h_004ab458();
                    *(word_t *)(0 + -0x10) = o;
                    sk_h_004aab08(0x6c61636f4c, 0xe500000000000000);   /* "Local" */
                    sk_h_0041d7dc();
                    goto fin;
                } else if (4 == 4 && 0 == 0 && 0 == 0) {
                    word_t o = sk_h_004ab458();
                    *(word_t *)(0 + -0x10) = o;
                    sk_h_004aab08(0x616568616b6f6f4c, 0xe900000000000064);   /* "Lookahea" */
                    sk_h_0041d7dc();
                    goto fin;
                } else if (5 != 5 || 0 != 0 || 0 != 0) { }
                else {
                    sk_h_004aab08(0xd000000000000011, 0x8000000000000000 | 0);
                    sk_h_0041d7dc();
                    goto fin;
                }
            }
            sk_h_48afec(0, 0, x20);
            goto fin;
        }
        case 4: case 0xc: {
            word_t c = *(word_t *)((node & 0xffffffffffffffb) + 0x10);
            word_t ref = sk_h_0036b270(c & 0xffffffffffffffb);
            sk_h_48afec(ref, flag & 1, x20);
            sk_h_0036b118(c & 0xffffffffffffffb);
            goto fin;
        }
        case 5: case 0xd: case 0xe: case 0xf:
            sk_h_004ab468(0);   /* TODO: conditional/consumers/validators/predicates */
            break;
        case 6: {
            sk_h_004ab4e8();
            node &= 0;
            sk_h_48c284();
            sk_h_0036b270(0);
            sk_h_00464e34(); sk_h_002acbb8();
            sk_h_0035084c(); sk_h_002acbb8();
            sk_h_00100e34(); sk_h_002acbb8();
            if ((0x72656761652e != 0) || 0 != -0x1a00000000000000) {
                sk_h_0035084c();
                word_t m = sk_h_002a0cf8();
                if ((m & 1) == 0) sk_h_003a25d4(0);
            } else sk_h_003a25d4(0);
            if (!(-0x6000000000000001 < 0)) {
                word_t k = (0 >> 0x3b) & 0x1e | (0 >> 2) & 1;
                if (k == 7) { word_t c = *(word_t *)(0 + 0x10); word_t f = *(word_t *)(0 + 0x18); word_t ref = sk_h_0036b270(c); if (sk_h_48d400(ref, 0) & 1) { sk_h_48c644(c, f); sk_h_0036b118(c); } }
                else if (k == 8) { sk_h_004ac12c(0, (word_t)&(word_t){0}); sk_h_00117cc4(); sk_h_004a36c4((word_t)&(word_t){0}, (word_t)&(word_t){0}); sk_h_48ce80(); sk_h_004ac960(); sk_h_004a36d4((word_t)&(word_t){0}); }
                else if (k == 0xc) { sk_h_004ab4e8(); word_t c = *(word_t *)(0 + 0x10); if (((c >> 0x3b) & 0x1e | (c >> 2) & 1) == 7) sk_h_48c718(*(word_t *)(c + 0x10), *(word_t *)(c + 0x18), 1, 1); }
                sk_h_003a25d4(0);
            }
            break;
        }
        case 7: {
            word_t c = *(word_t *)((node & 0xffffffffffffffb) + 0x10);
            word_t f = *(word_t *)((node & 0xffffffffffffffb) + 0x18);
            word_t ref = sk_h_0036b270(c);
            sk_h_48c718(ref, f, 1, 1);
            sk_h_0036b118(c);
            goto fin;
        }
        case 8: {
            sk_h_00117cc4((word_t)&(word_t){0}, (node & 0xffffffffffffffb) + 0x10, 0xb0);
            sk_h_00117cc4((word_t)&(word_t){0}, (node & 0xffffffffffffffb) + 0x10);
            sk_h_004ac210((word_t)&(word_t){0});
            if (is16) {
                if (sk_h_48d554() & 1) { sk_h_004a36c4((word_t)&(word_t){0}, (word_t)&(word_t){0}); sk_h_48d694(); sk_h_003535a8(); sk_h_004a36d4((word_t)&(word_t){0}); }
            }
            sk_h_004a36c4((word_t)&(word_t){0}, (word_t)&(word_t){0});
            sk_r29_pair_t q = sk_h_48ce80();
            sk_h_004a36d4((word_t)&(word_t){0});
            if (q.hi != 0) { sk_h_003a25d4(0); sk_h_003a25d4(q.hi); }
            break;
        }
        case 10:
            sk_h_0036b270(*(word_t *)((node & 0xffffffffffffffb) + 0x18));
            sk_h_004aa990(); sk_h_0046c4e0(); sk_h_004aab74(); sk_h_0046c4e0();
            sk_h_003517c0(); sk_h_003a25d4(0);
            sk_h_00350470(); sk_h_002acbb8(); sk_h_004657ac(); sk_h_002acbb8();
            sk_h_003a25d4(*x20);
            break;
        default:
            sk_h_0036b270(*(word_t *)(node + 0x10));
            sk_h_004aab08(0x664f6563696f6843, 0xe800000000000000);   /* "ChoiceOf" */
            sk_h_0041d7dc();
            sk_h_0036b118(*(word_t *)(node + 0x10));
            goto fin;
        }
    }
fin:
    sk_h_0008e500(0);
}
