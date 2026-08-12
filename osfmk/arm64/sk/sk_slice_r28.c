/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel, GL1,
 * arm64e, image base 0) — the cL4 microkernel. Ground truth: Ghidra FUN_ names +
 * addresses in the cl4_kernel.raw program. Names use seL4/cL4 vocabulary; all
 * are estimates unless string/header matched.
 *
 * Slice 0x0047c528-0x004815cc (worker SKR28): the Swift standard-library
 * Unicode runtime leaves — scalar character-property test wrappers (each
 * forwards a caller scalar to an out-of-slice property bit-tester
 * FUN_002bxxxx and stores `result & 1`), UTF-8/UTF-16 scalar decode helpers
 * with continuation handling, case-insensitive scalar range membership
 * tests, regex parse-error string builders, L4 error-code → Swift error
 * object factories (FUN_0047fa44 / FUN_004801f8), and a message/op dispatch
 * switch. The `sk_r28_<addr>` names identify the slice-local functions; the
 * `unaff_*` register artifacts are described per-function in the notes.
 */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "sk_internal.h"

/* ------------------------------------------------------------------ *
 * Hardware / intrinsic helpers (same semantics as the Ghidra pseudo-ops).
 * ------------------------------------------------------------------ */
static inline unsigned sk_clz64(uint64_t x) { return (unsigned)__builtin_clzll(x); }
#define LZCOUNT(x) sk_clz64((uint64_t)(x))
static inline void sk_break(uint64_t a, uint64_t b) __attribute__((noreturn))
{ (void)a; (void)b; __asm__ volatile("brk #1"); }
#define SoftwareBreakpoint(a,b) sk_break((uint64_t)(a),(uint64_t)(b))
#define SK_CANARY (-0x2c8502b44bfffed6LL)
#define SK_TAG_MASK 0x0FFFFFFFFFFFFFFFULL

/* 16-byte result pair used by several out-of-slice helpers (lo = x0, hi = x1). */
typedef struct sk_pair { uint64_t lo; uint64_t hi; } sk_pair_t;

/* ------------------------------------------------------------------ *
 * Out-of-slice callees (reconstructed by other slice workers). K&R empty
 * prototypes accept the register-passed args per the decompiles.
 * ------------------------------------------------------------------ */
extern sk_pair_t sk_x_00002534();   /* FUN_00002534 */
extern unsigned long sk_x_000026e8();   /* FUN_000026e8 */
extern unsigned long sk_x_00002834();   /* FUN_00002834 */
extern unsigned long sk_x_0001a1c8();   /* FUN_0001a1c8 */
extern unsigned long sk_x_0001da84();   /* FUN_0001da84 */
extern unsigned long sk_x_00027724();   /* FUN_00027724 */
extern unsigned long sk_x_00068e14();   /* FUN_00068e14 */
extern unsigned long sk_x_0006a4c0();   /* FUN_0006a4c0 */
extern unsigned long sk_x_0006b3f4();   /* FUN_0006b3f4 */
extern unsigned long sk_x_0006b42c();   /* FUN_0006b42c */
extern unsigned long sk_x_0006b6f4();   /* FUN_0006b6f4 */
extern unsigned long sk_x_00077024();   /* FUN_00077024 */
extern unsigned long sk_x_0007767c();   /* FUN_0007767c */
extern unsigned long sk_x_00077698();   /* FUN_00077698 */
extern sk_pair_t sk_x_00077888();   /* FUN_00077888 */
extern unsigned long sk_x_0007c1c4();   /* FUN_0007c1c4 */
extern unsigned long sk_x_000839d8();   /* FUN_000839d8 */
extern unsigned long sk_x_0008409c();   /* FUN_0008409c */
extern unsigned long sk_x_00084180();   /* FUN_00084180 */
extern unsigned long sk_x_00086840();   /* FUN_00086840 */
extern unsigned long sk_x_0008e500();   /* FUN_0008e500 */
extern sk_pair_t sk_x_0008e518();   /* FUN_0008e518 */
extern unsigned long sk_x_0009461c();   /* FUN_0009461c */
extern unsigned long sk_x_000a6e14();   /* FUN_000a6e14 */
extern unsigned long sk_x_000a6fe0();   /* FUN_000a6fe0 */
extern unsigned long sk_x_000abbdc();   /* FUN_000abbdc */
extern unsigned long sk_x_000b430c();   /* FUN_000b430c */
extern sk_pair_t sk_x_000b4390();   /* FUN_000b4390 */
extern unsigned long sk_x_000b43e8();   /* FUN_000b43e8 */
extern unsigned long sk_x_000b44cc();   /* FUN_000b44cc */
extern unsigned long sk_x_000dce50();   /* FUN_000dce50 */
extern unsigned long sk_x_000ec004();   /* FUN_000ec004 */
extern unsigned long sk_x_000f4a9c();   /* FUN_000f4a9c */
extern unsigned long sk_x_00100c04();   /* FUN_00100c04 */
extern unsigned long sk_x_00100efc();   /* FUN_00100efc */
extern unsigned long sk_x_00117cc4();   /* FUN_00117cc4 */
extern unsigned long sk_x_0011d7e8();   /* FUN_0011d7e8 */
extern unsigned long sk_x_00167404();   /* FUN_00167404 */
extern unsigned long sk_x_0016749c();   /* FUN_0016749c */
extern unsigned long sk_x_001a0754();   /* FUN_001a0754 */
extern unsigned long sk_x_001a84f4();   /* FUN_001a84f4 */
extern unsigned long sk_x_001a8564();   /* FUN_001a8564 */
extern unsigned long sk_x_001ae8a8();   /* FUN_001ae8a8 */
extern unsigned long sk_x_001aea6c();   /* FUN_001aea6c */
extern unsigned long sk_x_001b798c();   /* FUN_001b798c */
extern unsigned long sk_x_001b9084();   /* FUN_001b9084 */
extern sk_pair_t sk_x_001f0130();   /* FUN_001f0130 */
extern unsigned long sk_x_00205844();   /* FUN_00205844 */
extern unsigned long sk_x_00208418();   /* FUN_00208418 */
extern unsigned long sk_x_002298d4();   /* FUN_002298d4 */
extern unsigned long sk_x_0024917c();   /* FUN_0024917c */
extern unsigned long sk_x_0024d9ac();   /* FUN_0024d9ac */
extern unsigned long sk_x_00254c7c();   /* FUN_00254c7c */
extern sk_pair_t sk_x_00255d4c();   /* FUN_00255d4c */
extern sk_pair_t sk_x_00267510();   /* FUN_00267510 */
extern unsigned long sk_x_00294cb4();   /* FUN_00294cb4 */
extern unsigned long sk_x_0029c058();   /* FUN_0029c058 */
extern sk_pair_t sk_x_0029d3d8();   /* FUN_0029d3d8 */
extern unsigned long sk_x_0029d560();   /* FUN_0029d560 */
extern unsigned long sk_x_0029da50();   /* FUN_0029da50 */
extern unsigned long sk_x_0029fa0c();   /* FUN_0029fa0c */
extern unsigned long sk_x_0029fb80();   /* FUN_0029fb80 */
extern unsigned long sk_x_002a0cf8();   /* FUN_002a0cf8 */
extern unsigned long sk_x_002a49a8();   /* FUN_002a49a8 */
extern unsigned long sk_x_002a4ab4();   /* FUN_002a4ab4 */
extern unsigned long sk_x_002a9ba8();   /* FUN_002a9ba8 */
extern unsigned long sk_x_002ab130();   /* FUN_002ab130 */
extern sk_pair_t sk_x_002acbb8();   /* FUN_002acbb8 */
extern unsigned long sk_x_002ae098();   /* FUN_002ae098 */
extern unsigned long sk_x_002b141c();   /* FUN_002b141c */
extern unsigned long sk_x_002bbf08();   /* FUN_002bbf08 */
extern unsigned long sk_x_002bbf24();   /* FUN_002bbf24 */
extern unsigned long sk_x_002bbf40();   /* FUN_002bbf40 */
extern unsigned long sk_x_002bbf5c();   /* FUN_002bbf5c */
extern unsigned long sk_x_002bbf78();   /* FUN_002bbf78 */
extern unsigned long sk_x_002bbf94();   /* FUN_002bbf94 */
extern unsigned long sk_x_002bbfb0();   /* FUN_002bbfb0 */
extern unsigned long sk_x_002bbfcc();   /* FUN_002bbfcc */
extern unsigned long sk_x_002bbfe8();   /* FUN_002bbfe8 */
extern unsigned long sk_x_002bc004();   /* FUN_002bc004 */
extern unsigned long sk_x_002bc020();   /* FUN_002bc020 */
extern unsigned long sk_x_002bc03c();   /* FUN_002bc03c */
extern unsigned long sk_x_002bc058();   /* FUN_002bc058 */
extern unsigned long sk_x_002bc074();   /* FUN_002bc074 */
extern unsigned long sk_x_002bc090();   /* FUN_002bc090 */
extern unsigned long sk_x_002bc0ac();   /* FUN_002bc0ac */
extern unsigned long sk_x_002bc0c8();   /* FUN_002bc0c8 */
extern unsigned long sk_x_002bc0e4();   /* FUN_002bc0e4 */
extern unsigned long sk_x_002bc100();   /* FUN_002bc100 */
extern unsigned long sk_x_002bc11c();   /* FUN_002bc11c */
extern unsigned long sk_x_002bc138();   /* FUN_002bc138 */
extern unsigned long sk_x_002bc154();   /* FUN_002bc154 */
extern unsigned long sk_x_002bc170();   /* FUN_002bc170 */
extern unsigned long sk_x_002bc18c();   /* FUN_002bc18c */
extern unsigned long sk_x_002bc1a8();   /* FUN_002bc1a8 */
extern unsigned long sk_x_002bc1c4();   /* FUN_002bc1c4 */
extern unsigned long sk_x_002bc1e0();   /* FUN_002bc1e0 */
extern unsigned long sk_x_002bc1fc();   /* FUN_002bc1fc */
extern unsigned long sk_x_002bc218();   /* FUN_002bc218 */
extern unsigned long sk_x_002bc234();   /* FUN_002bc234 */
extern unsigned long sk_x_002bc250();   /* FUN_002bc250 */
extern unsigned long sk_x_002bc26c();   /* FUN_002bc26c */
extern unsigned long sk_x_002bc288();   /* FUN_002bc288 */
extern unsigned long sk_x_002bc2a4();   /* FUN_002bc2a4 */
extern unsigned long sk_x_002bc2c0();   /* FUN_002bc2c0 */
extern unsigned long sk_x_002bc2dc();   /* FUN_002bc2dc */
extern unsigned long sk_x_002bc2f8();   /* FUN_002bc2f8 */
extern unsigned long sk_x_002bc314();   /* FUN_002bc314 */
extern unsigned long sk_x_002bc330();   /* FUN_002bc330 */
extern unsigned long sk_x_002bc34c();   /* FUN_002bc34c */
extern unsigned long sk_x_002bc368();   /* FUN_002bc368 */
extern unsigned long sk_x_002bc384();   /* FUN_002bc384 */
extern unsigned long sk_x_002bc3a0();   /* FUN_002bc3a0 */
extern unsigned long sk_x_002bc3bc();   /* FUN_002bc3bc */
extern unsigned long sk_x_002bc3d8();   /* FUN_002bc3d8 */
extern unsigned long sk_x_002bc3f4();   /* FUN_002bc3f4 */
extern unsigned long sk_x_002bc410();   /* FUN_002bc410 */
extern unsigned long sk_x_002bc42c();   /* FUN_002bc42c */
extern unsigned long sk_x_002bc5bc();   /* FUN_002bc5bc */
extern unsigned long sk_x_002bd724();   /* FUN_002bd724 */
extern unsigned long sk_x_002bd848();   /* FUN_002bd848 */
extern unsigned long sk_x_002bd8f0();   /* FUN_002bd8f0 */
extern unsigned long sk_x_002bd9ac();   /* FUN_002bd9ac */
extern unsigned long sk_x_002be12c();   /* FUN_002be12c */
extern unsigned long sk_x_002be23c();   /* FUN_002be23c */
extern unsigned long sk_x_002be300();   /* FUN_002be300 */
extern unsigned long sk_x_00310d68();   /* FUN_00310d68 */
extern unsigned long sk_x_00310d98();   /* FUN_00310d98 */
extern unsigned long sk_x_00319808();   /* FUN_00319808 */
extern unsigned long sk_x_00343c20();   /* FUN_00343c20 */
extern unsigned long sk_x_0034b3f8();   /* FUN_0034b3f8 */
extern unsigned long sk_x_0034c6d4();   /* FUN_0034c6d4 */
extern unsigned long sk_x_0034cc24();   /* FUN_0034cc24 */
extern unsigned long sk_x_0034ecc8();   /* FUN_0034ecc8 */
extern unsigned long sk_x_00350470();   /* FUN_00350470 */
extern unsigned long sk_x_003504a0();   /* FUN_003504a0 */
extern unsigned long sk_x_003504d0();   /* FUN_003504d0 */
extern unsigned long sk_x_003504e8();   /* FUN_003504e8 */
extern unsigned long sk_x_00350548();   /* FUN_00350548 */
extern unsigned long sk_x_0035056c();   /* FUN_0035056c */
extern unsigned long sk_x_00350600();   /* FUN_00350600 */
extern sk_pair_t sk_x_0035060c();   /* FUN_0035060c */
extern unsigned long sk_x_00350618();   /* FUN_00350618 */
extern unsigned long sk_x_00350624();   /* FUN_00350624 */
extern unsigned long sk_x_0035063c();   /* FUN_0035063c */
extern unsigned long sk_x_00350738();   /* FUN_00350738 */
extern unsigned long sk_x_00350774();   /* FUN_00350774 */
extern unsigned long sk_x_003507e0();   /* FUN_003507e0 */
extern unsigned long sk_x_00350878();   /* FUN_00350878 */
extern unsigned long sk_x_003509c8();   /* FUN_003509c8 */
extern unsigned long sk_x_003509ec();   /* FUN_003509ec */
extern unsigned long sk_x_00350a28();   /* FUN_00350a28 */
extern unsigned long sk_x_00350b54();   /* FUN_00350b54 */
extern unsigned long sk_x_00350b84();   /* FUN_00350b84 */
extern unsigned long sk_x_00351124();   /* FUN_00351124 */
extern unsigned long sk_x_003512c0();   /* FUN_003512c0 */
extern unsigned long sk_x_00351300();   /* FUN_00351300 */
extern unsigned long sk_x_00351450();   /* FUN_00351450 */
extern unsigned long sk_x_00351774();   /* FUN_00351774 */
extern unsigned long sk_x_0035193c();   /* FUN_0035193c */
extern unsigned long sk_x_00351a50();   /* FUN_00351a50 */
extern unsigned long sk_x_00351b78();   /* FUN_00351b78 */
extern unsigned long sk_x_00351d18();   /* FUN_00351d18 */
extern unsigned long sk_x_00351db4();   /* FUN_00351db4 */
extern unsigned long sk_x_00351f34();   /* FUN_00351f34 */
extern unsigned long sk_x_003527b8();   /* FUN_003527b8 */
extern unsigned long sk_x_00352800();   /* FUN_00352800 */
extern unsigned long sk_x_00352ae4();   /* FUN_00352ae4 */
extern unsigned long sk_x_00352af0();   /* FUN_00352af0 */
extern unsigned long sk_x_00352c68();   /* FUN_00352c68 */
extern unsigned long sk_x_00352e9c();   /* FUN_00352e9c */
extern unsigned long sk_x_003532b8();   /* FUN_003532b8 */
extern unsigned long sk_x_0035354c();   /* FUN_0035354c */
extern unsigned long sk_x_00353cfc();   /* FUN_00353cfc */
extern unsigned long sk_x_00353d14();   /* FUN_00353d14 */
extern unsigned long sk_x_00353ff4();   /* FUN_00353ff4 */
extern unsigned long sk_x_00354f1c();   /* FUN_00354f1c */
extern unsigned long sk_x_00355538();   /* FUN_00355538 */
extern unsigned long sk_x_00355d6c();   /* FUN_00355d6c */
extern unsigned long sk_x_00356364();   /* FUN_00356364 */
extern unsigned long sk_x_00356930();   /* FUN_00356930 */
extern unsigned long sk_x_00357c74();   /* FUN_00357c74 */
extern sk_pair_t sk_x_00357cb4();   /* FUN_00357cb4 */
extern unsigned long sk_x_00359018();   /* FUN_00359018 */
extern unsigned long sk_x_00365b6c();   /* FUN_00365b6c */
extern unsigned long sk_x_00369efc();   /* FUN_00369efc */
extern unsigned long sk_x_0036a940();   /* FUN_0036a940 */
extern unsigned long sk_x_0036b118();   /* FUN_0036b118 */
extern unsigned long sk_x_0036b270();   /* FUN_0036b270 */
extern unsigned long sk_x_0036b6ac();   /* FUN_0036b6ac */
extern unsigned long sk_x_003a25d4();   /* FUN_003a25d4 */
extern unsigned long sk_x_003a261c();   /* FUN_003a261c */
extern unsigned long sk_x_00407ab8();   /* FUN_00407ab8 */
extern unsigned long sk_x_004080b0();   /* FUN_004080b0 */
extern unsigned long sk_x_004176bc();   /* FUN_004176bc */
extern unsigned long sk_x_00417aa0();   /* FUN_00417aa0 */
extern unsigned long sk_x_0044f818();   /* FUN_0044f818 */
extern unsigned long sk_x_0045567c();   /* FUN_0045567c */
extern unsigned long sk_x_00455ac8();   /* FUN_00455ac8 */
extern unsigned long sk_x_00458af8();   /* FUN_00458af8 */
extern unsigned long sk_x_00458b14();   /* FUN_00458b14 */
extern sk_pair_t sk_x_00463f94();   /* FUN_00463f94 */
extern unsigned long sk_x_00464e64();   /* FUN_00464e64 */
extern unsigned long sk_x_0046511c();   /* FUN_0046511c */
extern unsigned long sk_x_00465294();   /* FUN_00465294 */
extern unsigned long sk_x_00466214();   /* FUN_00466214 */
extern unsigned long sk_x_00473244();   /* FUN_00473244 */
extern unsigned long sk_x_00474fe8();   /* FUN_00474fe8 */
extern unsigned long sk_x_00493354();   /* FUN_00493354 */
extern unsigned long sk_x_004934a8();   /* FUN_004934a8 */
extern unsigned long sk_x_004950f0();   /* FUN_004950f0 */
extern unsigned long sk_x_00498ad4();   /* FUN_00498ad4 */
extern unsigned long sk_x_00498b28();   /* FUN_00498b28 */
extern unsigned long sk_x_00498bdc();   /* FUN_00498bdc */
extern unsigned long sk_x_00499158();   /* FUN_00499158 */
extern unsigned long sk_x_00499468();   /* FUN_00499468 */
extern unsigned long sk_x_0049a604();   /* FUN_0049a604 */
extern unsigned long sk_x_0049c704();   /* FUN_0049c704 */
extern unsigned long sk_x_0049c714();   /* FUN_0049c714 */
extern unsigned long sk_x_0049df0c();   /* FUN_0049df0c */
extern unsigned long sk_x_0049df18();   /* FUN_0049df18 */
extern unsigned long sk_x_0049e2d4();   /* FUN_0049e2d4 */
extern unsigned long sk_x_0049e2f0();   /* FUN_0049e2f0 */
extern unsigned long sk_x_004a35b8();   /* FUN_004a35b8 */
extern unsigned long sk_x_004a363c();   /* FUN_004a363c */
extern unsigned long sk_x_004a364c();   /* FUN_004a364c */
extern unsigned long sk_x_004a3918();   /* FUN_004a3918 */
extern unsigned long sk_x_004a3d60();   /* FUN_004a3d60 */
extern unsigned long sk_x_004a3c94();   /* FUN_004a3c94 (code ptr) */
extern unsigned long sk_x_004a3cac();   /* FUN_004a3cac (code ptr) */
extern unsigned long sk_x_004a3d8c();   /* FUN_004a3d8c */
extern unsigned long sk_x_004a3dcc();   /* FUN_004a3dcc */
extern unsigned long sk_x_004a3e20();   /* FUN_004a3e20 */
extern unsigned long sk_x_004a3e68();   /* FUN_004a3e68 */
extern unsigned long sk_x_004a3eac();   /* FUN_004a3eac */
extern unsigned long sk_x_004a3f04();   /* FUN_004a3f04 */
extern unsigned long sk_x_004a40b8();   /* FUN_004a40b8 */
extern unsigned long sk_x_004a4158();   /* FUN_004a4158 */
extern unsigned long sk_x_004a42a0();   /* FUN_004a42a0 */
extern unsigned long sk_x_004a4ac4();   /* FUN_004a4ac4 */
extern unsigned long sk_x_004a4b14();   /* FUN_004a4b14 */
extern unsigned long sk_x_004aa370();   /* FUN_004aa370 */
extern unsigned long sk_x_004aa494();   /* FUN_004aa494 */
extern unsigned long sk_x_004aa4e0();   /* FUN_004aa4e0 */
extern unsigned long sk_x_004aa6a8();   /* FUN_004aa6a8 */
extern unsigned long sk_x_004aa734();   /* FUN_004aa734 */
extern unsigned long sk_x_004aa890();   /* FUN_004aa890 */
extern unsigned long sk_x_004aaa78();   /* FUN_004aaa78 */
extern unsigned long sk_x_004aaa88();   /* FUN_004aaa88 */
extern unsigned long sk_x_004aaccc();   /* FUN_004aaccc */
extern unsigned long sk_x_004aacf8();   /* FUN_004aacf8 */
extern unsigned long sk_x_004aad54();   /* FUN_004aad54 */
extern unsigned long sk_x_004aad94();   /* FUN_004aad94 */
extern unsigned long sk_x_004aaf58();   /* FUN_004aaf58 */
extern sk_pair_t sk_x_004aaf9c();   /* FUN_004aaf9c */
extern unsigned long sk_x_004ab044();   /* FUN_004ab044 */
extern unsigned long sk_x_004ab054();   /* FUN_004ab054 */
extern unsigned long sk_x_004ab0f0();   /* FUN_004ab0f0 */
extern unsigned long sk_x_004ab11c();   /* FUN_004ab11c */
extern unsigned long sk_x_004ab128();   /* FUN_004ab128 */
extern unsigned long sk_x_004ab1dc();   /* FUN_004ab1dc */
extern unsigned long sk_x_004ab1fc();   /* FUN_004ab1fc */
extern unsigned long sk_x_004ab224();   /* FUN_004ab224 */
extern unsigned long sk_x_004ab288();   /* FUN_004ab288 */
extern unsigned long sk_x_004ab31c();   /* FUN_004ab31c */
extern unsigned long sk_x_004ab430();   /* FUN_004ab430 */
extern unsigned long sk_x_004ab618();   /* FUN_004ab618 */
extern unsigned long sk_x_004ab650();   /* FUN_004ab650 */
extern unsigned long sk_x_004ab6ac();   /* FUN_004ab6ac */
extern unsigned long sk_x_004ab6b8();   /* FUN_004ab6b8 */
extern unsigned long sk_x_004ab968();   /* FUN_004ab968 */
extern unsigned long sk_x_004ab9e0();   /* FUN_004ab9e0 */
extern unsigned long sk_x_004abbb8();   /* FUN_004abbb8 */
extern unsigned long sk_x_004abc0c();   /* FUN_004abc0c */
extern unsigned long sk_x_004abcdc();   /* FUN_004abcdc */
extern unsigned long sk_x_004abd2c();   /* FUN_004abd2c */
extern unsigned long sk_x_004abdc4();   /* FUN_004abdc4 */
extern unsigned long sk_x_004abe68();   /* FUN_004abe68 */
extern unsigned long sk_x_004abf00();   /* FUN_004abf00 */
extern unsigned long sk_x_004abf50();   /* FUN_004abf50 */
extern unsigned long sk_x_004abf5c();   /* FUN_004abf5c */
extern unsigned long sk_x_004abfc8();   /* FUN_004abfc8 */
extern unsigned long sk_x_004abff8();   /* FUN_004abff8 */
extern unsigned long sk_x_004ac008();   /* FUN_004ac008 */
extern unsigned long sk_x_004ac034();   /* FUN_004ac034 */
extern unsigned long sk_x_004ac0cc();   /* FUN_004ac0cc */
extern unsigned long sk_x_004ac1a4();   /* FUN_004ac1a4 */
extern unsigned long sk_x_004ac210();   /* FUN_004ac210 */
extern unsigned long sk_x_004ac27c();   /* FUN_004ac27c */
extern unsigned long sk_x_004ac2d0();   /* FUN_004ac2d0 */
extern unsigned long sk_x_004ac318();   /* FUN_004ac318 */
extern unsigned long sk_x_004ac348();   /* FUN_004ac348 */
extern unsigned long sk_x_004ac3e4();   /* FUN_004ac3e4 */
extern unsigned long sk_x_004ac41c();   /* FUN_004ac41c */
extern unsigned long sk_x_004ac4e0();   /* FUN_004ac4e0 */
extern unsigned long sk_x_004ac52c();   /* FUN_004ac52c */
extern unsigned long sk_x_004ac584();   /* FUN_004ac584 */
extern unsigned long sk_x_004ac5b4();   /* FUN_004ac5b4 */
extern unsigned long sk_x_004ac7ec();   /* FUN_004ac7ec */
extern unsigned long sk_x_004ac93c();   /* FUN_004ac93c */
extern sk_pair_t sk_x_004ac960();   /* FUN_004ac960 */
extern unsigned long sk_x_004acb20();   /* FUN_004acb20 */
extern sk_pair_t sk_x_004acb3c();   /* FUN_004acb3c */
extern unsigned long sk_x_004ace08();   /* FUN_004ace08 */
extern unsigned long sk_x_004ace88();   /* FUN_004ace88 */

/* ------------------------------------------------------------------ *
 * Shared globals referenced by this slice (image-base DAT_ ground truth).
 * ------------------------------------------------------------------ */
extern uint64_t sk_g_006881d8;   /* DAT_006881d8 */
extern uint64_t sk_g_0047f34c;   /* DAT_0047f34c */
extern uint64_t sk_g_0047f3f4;   /* DAT_0047f3f4 */
extern uint64_t sk_g_0047f3d0;   /* DAT_0047f3d0 */
extern uint64_t sk_g_0047f328;   /* DAT_0047f328 */
extern uint64_t sk_g_0047f430;   /* DAT_0047f430 */
extern uint64_t sk_g_006898b0;   /* DAT_006898b0 */
extern uint64_t sk_g_0047f304;   /* DAT_0047f304 */
extern uint64_t sk_g_004e824c;   /* DAT_004e824c */
extern uint64_t sk_g_005a3c88;   /* DAT_005a3c88 */
extern uint64_t sk_g_00688430;   /* DAT_00688430 */
extern uint64_t sk_g_00010004;   /* DAT_00010004 */
extern uint64_t sk_g_0047f394;   /* DAT_0047f394 */
extern uint64_t sk_g_0047f418;   /* DAT_0047f418 */
extern uint64_t sk_g_004a3cc4;   /* DAT_004a3cc4 */
extern uint64_t sk_g_00657da0;   /* DAT_00657da0 */
extern uint64_t sk_g_0047f220;   /* DAT_0047f220 */
extern uint64_t sk_g_004aa2c4;   /* DAT_004aa2c4 */
extern uint64_t sk_g_0047f424;   /* DAT_0047f424 */
extern uint64_t sk_g_005a3c98;   /* DAT_005a3c98 */
extern uint64_t sk_g_005a4b78;   /* DAT_005a4b78 */
extern uint64_t sk_g_004a3c94;   /* DAT_004a3c94 */
extern uint64_t sk_g_005a4b88;   /* DAT_005a4b88 */
extern uint64_t sk_g_0047f298;   /* DAT_0047f298 */
extern uint64_t sk_g_0047f2b0;   /* DAT_0047f2b0 */
extern uint64_t sk_g_006881b0;   /* DAT_006881b0 */
extern uint64_t sk_g_00688368;   /* DAT_00688368 */
extern uint64_t sk_g_0047f3b8;   /* DAT_0047f3b8 */
extern uint64_t sk_g_005a4b50;   /* DAT_005a4b50 */
extern uint64_t sk_g_0047f334;   /* DAT_0047f334 */
extern uint64_t sk_g_006884d0;   /* DAT_006884d0 */
extern uint64_t sk_g_0047f250;   /* DAT_0047f250 */
extern uint64_t sk_g_0047f244;   /* DAT_0047f244 */
extern uint64_t sk_g_005a5530;   /* DAT_005a5530 */
extern uint64_t sk_g_00688250;   /* DAT_00688250 */
extern uint64_t sk_g_004a3bcc;   /* DAT_004a3bcc */
extern uint64_t sk_g_0047f43c;   /* DAT_0047f43c */
extern uint64_t sk_g_0047f25c;   /* DAT_0047f25c */
extern uint64_t sk_g_0047f2ec;   /* DAT_0047f2ec */
extern uint64_t sk_g_004a3cac;   /* DAT_004a3cac */
extern uint64_t sk_g_00657778;   /* DAT_00657778 */
extern uint64_t sk_g_0047f3ac;   /* DAT_0047f3ac */
extern uint64_t sk_g_0047f310;   /* DAT_0047f310 */
extern uint64_t sk_g_00688390;   /* DAT_00688390 */
extern uint64_t sk_g_0047f2d4;   /* DAT_0047f2d4 */
extern uint64_t sk_g_0047f388;   /* DAT_0047f388 */
extern uint64_t sk_g_004baeb0;   /* DAT_004baeb0 */
extern uint64_t sk_g_0047f370;   /* DAT_0047f370 */
extern uint64_t sk_g_0047f3e8;   /* DAT_0047f3e8 */
extern uint64_t sk_g_0047f3a0;   /* DAT_0047f3a0 */
extern uint64_t sk_g_00657d90;   /* DAT_00657d90 */
extern uint64_t sk_g_00657e20;   /* DAT_00657e20 */
extern uint64_t sk_g_00688638;   /* DAT_00688638 */
extern uint64_t sk_g_0047f2c8;   /* DAT_0047f2c8 */
extern uint64_t sk_g_00688200;   /* DAT_00688200 */
extern uint64_t sk_g_0047f22c;   /* DAT_0047f22c */
extern uint64_t sk_g_0047f280;   /* DAT_0047f280 */
extern uint64_t sk_g_006775b0;   /* DAT_006775b0 */
extern uint64_t sk_g_00688660;   /* DAT_00688660 */
extern uint64_t sk_g_005a5e90;   /* DAT_005a5e90 */
extern uint64_t sk_g_0047f364;   /* DAT_0047f364 */
extern uint64_t sk_g_0047f2a4;   /* DAT_0047f2a4 */
extern uint64_t sk_g_0047f31c;   /* DAT_0047f31c */
extern uint64_t sk_g_004aa204;   /* DAT_004aa204 */
extern uint64_t sk_g_005a4c30;   /* DAT_005a4c30 */
extern uint64_t sk_g_0047f358;   /* DAT_0047f358 */
extern uint64_t sk_g_0047f340;   /* DAT_0047f340 */
extern uint64_t sk_g_0047f2e0;   /* DAT_0047f2e0 */
extern uint64_t sk_g_00688510;   /* DAT_00688510 */
extern uint64_t sk_g_005a4b90;   /* DAT_005a4b90 */
extern uint64_t sk_g_0047f28c;   /* DAT_0047f28c */
extern uint64_t sk_g_0047f40c;   /* DAT_0047f40c */
extern uint64_t sk_g_0047f238;   /* DAT_0047f238 */
extern uint64_t sk_g_0047f400;   /* DAT_0047f400 */
extern uint64_t sk_g_005a5538;   /* DAT_005a5538 */
extern uint64_t sk_g_0047f2bc;   /* DAT_0047f2bc */
extern uint64_t sk_g_0047f274;   /* DAT_0047f274 */
extern uint64_t sk_g_005a3ca0;   /* DAT_005a3ca0 */
extern uint64_t sk_g_0047f268;   /* DAT_0047f268 */
extern uint64_t sk_g_005a3c90;   /* DAT_005a3c90 */
extern uint64_t sk_g_0047f3dc;   /* DAT_0047f3dc */
extern uint64_t sk_g_004aa240;   /* DAT_004aa240 */
extern uint64_t sk_g_00657d88;   /* DAT_00657d88 */
extern uint64_t sk_g_005a4b80;   /* DAT_005a4b80 */
extern uint64_t sk_g_0047f37c;   /* DAT_0047f37c */
extern uint64_t sk_g_0047f2f8;   /* DAT_0047f2f8 */
extern uint64_t sk_g_005a4990;   /* DAT_005a4990 */
extern uint64_t sk_g_0047f3c4;   /* DAT_0047f3c4 */

/* ------------------------------------------------------------------ *
 * Slice-local function forward declarations (they cross-call each other).
 * ------------------------------------------------------------------ */
/* Slice-local cross-call forward declarations. */
void sk_r28_0047c528(uint64_t,uint64_t,uint64_t,uint64_t);
void sk_r28_0047c62c(void);
void sk_r28_0047c7b0(uint64_t *,uint64_t);
void sk_r28_0047c948(void);
void sk_r28_0047c9d4(uint64_t,int64_t);
bool sk_r28_0047ca18(int64_t);
bool sk_r28_0047cadc(uint64_t,uint64_t);
uint32_t sk_r28_0047cc98(int64_t);
void sk_r28_0047cdbc(uint64_t,uint64_t,uint64_t);
void sk_r28_0047ce4c(void);
void sk_r28_0047ce8c(void);
void sk_r28_0047cf0c(uint64_t,uint64_t,uint64_t,uint64_t,uint64_t,int64_t);
void sk_r28_0047d358(void);
void sk_r28_0047d6e0(void);
void sk_r28_0047d70c(void);
void sk_r28_0047d710(void);
sk_pair_t sk_r28_0047d73c(uint64_t,uint64_t,uint32_t);
void sk_r28_0047d8ec(void);
void sk_r28_0047d96c(void);
void sk_r28_0047d9e8(uint64_t,uint64_t,uint8_t);
void sk_r28_0047da48(void);
uint32_t sk_r28_0047dac4(void);
void sk_r28_0047dc1c(uint64_t,uint64_t,uint64_t,uint64_t);
void sk_r28_0047dee8();
void sk_r28_0047dfc4(void);
void sk_r28_0047e5dc(void);
uint8_t sk_r28_0047e8ec(uint32_t,uint8_t,uint64_t);
uint32_t sk_r28_0047e96c(uint8_t,uint8_t,uint32_t);
bool sk_r28_0047ea18(uint32_t);
void sk_r28_0047ead4(uint64_t,uint64_t,uint64_t,uint64_t,uint32_t,uint32_t,uint64_t,uint64_t,uint64_t);
void sk_r28_0047ed40();
uint64_t sk_r28_0047edf4(void);
uint64_t sk_r28_0047ee98(void);
uint64_t sk_r28_0047ef1c(void);
uint64_t sk_r28_0047eff4();
void sk_r28_0047f0a8(void);
void sk_r28_0047f1b4(uint64_t,uint64_t);
uint64_t sk_r28_0047f1e0(uint64_t);
bool sk_r28_0047f448(uint64_t);
bool sk_r28_0047f488(uint64_t);
bool sk_r28_0047f4f4(void);
bool sk_r28_0047f4f8(void);
uint64_t sk_r28_0047f518(uint64_t);
uint8_t sk_r28_0047f580(uint32_t,uint64_t);
void sk_r28_0047f5d0(void);
void sk_r28_0047f630(uint64_t,uint64_t,uint64_t);
void sk_r28_0047f808(void);
void sk_r28_0047f868(uint64_t,uint64_t,uint64_t);
void sk_r28_0047f944(uint64_t,uint64_t,uint64_t,uint64_t,uint64_t,uint64_t,int64_t);
void sk_r28_0047f9c4(uint64_t,uint64_t,uint64_t);
void sk_r28_0047f9c8(uint64_t,uint64_t,uint64_t);
bool sk_r28_0047f9f0(void);
bool sk_r28_0047f9f4(void);
void sk_r28_0047fa14(uint8_t *,uint32_t *);
void sk_r28_0047fa44(int64_t);
void sk_r28_004801f8(int64_t);
void sk_r28_00480864(int64_t,uint64_t);
bool sk_r28_004811b4(int);
void sk_r28_004811e8(uint64_t,uint64_t);
uint64_t sk_r28_00481320(uint32_t);
uint32_t sk_r28_00481354(uint64_t);
uint64_t sk_r28_00481378(uint64_t);
void sk_r28_00481394(uint64_t);
void sk_r28_004813f0(uint64_t,uint8_t);
void sk_r28_00481418(uint64_t,uint64_t);
void sk_r28_0048144c(uint64_t,uint64_t);
void sk_r28_0048147c(uint64_t,uint64_t);
void sk_r28_004814c0(uint64_t,uint64_t);
void sk_r28_00481510(uint64_t,uint8_t);
void sk_r28_00481554(void);
void sk_r28_00481580(uint64_t *);
int64_t sk_r28_004815ac(uint64_t);
uint64_t sk_r28_004815cc(uint64_t);

/* FUN_0047c528 @ 0x0047c528   (est. sk_r28_op_dispatch)
 * Ghidra: void FUN_0047c528(undefined8,undefined8,undefined8,undefined8,undefined8)
 * Reads the method pointer at self+0x10 and a kind byte at self+0x20. On the
 * default path builds a 5-word message (arg2..arg5 into a fresh object at
 * 0x686160), refs arg5, invokes the method, then releases the message. On
 * kinds 1 and 3 releases arg1 and invokes the method with no message.
 * Confidence: medium.
 * Notes: unaff_x20 = self (method-table owner); FUN_000026e8 = msg release;
 *   FUN_0036a940 = alloc; thunk_FUN_0036b270 = refcount acquire. */
void sk_r28_0047c528(uint64_t a2, uint64_t a3, uint64_t a4, uint64_t a5)
{
    uint64_t self = 0;                 /* unaff_x20: method-table owner */
    uint64_t (*method)() = *(uint64_t (**)())(self + 0x10);
    uint64_t kind = *(uint8_t *)(self + 0x20);
    switch (kind) {
    case 1:
    case 3:
        sk_x_000a6e14(a2);
        sk_x_00352ae4();
        (*method)();
        break;
    default: {
        uint64_t msg = sk_x_0036a940();
        *(uint64_t *)(msg + 0x10) = a2;
        *(uint64_t *)(msg + 0x18) = a3;
        *(uint64_t *)(msg + 0x20) = a4;
        *(uint64_t *)(msg + 0x28) = a5;
        sk_x_0036b270(a5);
        (*method)(a2, msg);
        sk_x_000026e8(msg);
        break;
    }
    }
}

/* FUN_0047c62c @ 0x0047c62c   (est. sk_r28_utf8_iter_setup)
 * Ghidra: void FUN_0047c62c(void)
 * Reads a string/error box; if its kind (lStack_78) is 1 (owned/ascii) it
 * validates a count in_x3 and, if the count is underflowed, traps; otherwise
 * forwards (count-1) to an append helper. Else copies the box words to the
 * caller frame and builds a UTF-8 view descriptor.
 * Confidence: low (register-heavy: unaff_x21/x22, in_x3).
 * Notes: SoftwareBreakpoint(1,0x47c7ac). */
void sk_r28_0047c62c(void)
{
    int64_t in_x3 = 0;                 /* unmodeled caller count register */
    uint64_t unaff_x21 = 0, unaff_x22 = 0;
    sk_x_003509ec();
    sk_x_004ab128();
    sk_x_004a4ac4(&unaff_x22, &unaff_x21);
    if (/* lStack_78 == 1 */ 1) {
        sk_x_004aaccc();
        uint64_t v = sk_x_004a4b14(&unaff_x21);
        if (in_x3 < 1) {
            SoftwareBreakpoint(1, 0x47c7ac);
        }
        sk_x_004ac41c(v, in_x3 - 1);
        sk_r28_0047ce4c();
    } else {
        sk_x_004a4ac4(&unaff_x22, &unaff_x21);
        sk_x_004a4b14(&unaff_x21);
    }
}

/* FUN_0047c7b0 @ 0x0047c7b0   (est. sk_r28_value_read)
 * Ghidra: void FUN_0047c7b0(undefined8 *out, undefined8)
 * Reads a value box via the method at self+0x10 keyed on the kind byte at
 * self+0x20: kind 1/3 copy a UTF-8 scalar and ref it; kind 2 reads directly;
 * otherwise moves the box contents into out with refcount bookkeeping.
 * Confidence: low (register-heavy: unaff_x20/x21).
 * Notes: FUN_00319808 value copy; FUN_003a25d4 release. */
void sk_r28_0047c7b0(uint64_t *out, uint64_t a2)
{
    uint64_t self = 0;                 /* unaff_x20 */
    int64_t unaff_x21 = 0;             /* unaff_x21: caller flag */
    uint64_t flag = (uint64_t)unaff_x21;
    uint64_t (*method)() = *(uint64_t (**)())(self + 0x10);
    uint64_t kind = *(uint8_t *)(self + 0x20);
    uint64_t buf[4];
    switch (kind) {
    case 1:
        sk_x_00319808(a2, buf);
        sk_x_00351f34();
        sk_x_004ab1dc();
        sk_x_00365b6c(buf);
        (*method)(buf);
        sk_x_003a25d4(buf[3]);
        break;
    case 2:
        (*method)(out);
        break;
    case 3:
        sk_x_00319808(a2, buf);
        sk_x_00351f34();
        sk_x_004ab1dc();
        sk_x_00365b6c(buf);
        (*method)(out, buf[0], buf[1], buf[2], buf[3]);
        sk_x_003a25d4(buf[3]);
        if (flag != 0) return;
        out[1] = buf[1]; out[0] = buf[0]; out[3] = buf[3]; out[2] = buf[2];
        return;
    default:
        break;
    }
    if (flag == 0) {
        sk_x_0034cc24();
        sk_x_004a4b14(buf);
        out[0] = out[1] = out[2] = out[3] = 0;
    }
}

/* FUN_0047c948 @ 0x0047c948   (est. sk_r28_log_start)
 * Ghidra: void FUN_0047c948(void)
 * Starts a log/report record: reads a message tag, allocates a record object,
 * then chains a series of report-field appends. Confidence: medium.
 * Notes: unaff_x20 = self; FUN_00002834 tag load; FUN_0036a940 alloc. */
void sk_r28_0047c948(void)
{
    uint64_t self = 0;                 /* unaff_x20 */
    sk_x_0008409c();
    sk_x_00002834(0x687d98);
    sk_x_0036a940();
    sk_x_004ac5b4();
    sk_x_003507e0();
    sk_x_00498ad4();
    sk_x_004aad54();
    sk_x_00498bdc();
    sk_x_004ab224(*(uint64_t *)(self + 0x40));
    sk_x_004abf5c();
}

/* FUN_0047c9d4 @ 0x0047c9d4   (est. sk_r28_log_args)
 * Ghidra: void FUN_0047c9d4(ulong,long)
 * Folds arg1 and arg2<<16 into a packed argument word and appends it to the
 * in-flight report record. Confidence: medium. */
void sk_r28_0047c9d4(uint64_t a1, int64_t a2)
{
    sk_x_004aa494(a1 | (uint64_t)a2 << 0x10);
    sk_x_00498b28(0);
    sk_x_004aaf58();
    sk_x_004aa6a8();
}

/* FUN_0047ca18 @ 0x0047ca18   (est. sk_r28_parse_group)
 * Ghidra: bool FUN_0047ca18(long)
 * Recursive regex group parser: walks the token stream at param+0x10 and
 * handles alternation/open groups, recursing into FUN_0047ca18 for nested
 * groups. Returns whether a group matched. Confidence: medium. */
bool sk_r28_0047ca18(int64_t a1)
{
    int64_t n = *(int64_t *)(a1 + 0x10);
    uint8_t s1[352], s2[352], s3[352];
    uint64_t r;
    do {
        while (1) {
            int64_t save = n;
            n = save - 1;
            if (save == 0) goto done;
            sk_x_004ac3e4(s2);
            sk_x_004ac3e4(s3);
            int k = sk_x_0049df0c(s2);
            if (k == 2) break;
            if (k == 0) {
                sk_x_0049df18(s3);
                int k2 = sk_x_0049e2d4();
                if (k2 == 10) goto done;
            }
        }
        sk_x_0049df18(s3);
        sk_x_004ac4e0();
        sk_x_004ac034(s1);
        sk_x_00352c68();
        r = (uint64_t)sk_r28_0047ca18(0);
        sk_x_004a3918(s2);
    } while ((r & 1) == 0);
done:
    return n != 0;
}

/* FUN_0047cadc @ 0x0047cadc   (est. sk_r28_string_scan)
 * Ghidra: bool FUN_0047cadc(ulong,ulong)
 * Unicode scalar scan/compare of a UTF-8 string (params = {buf, len}-packed
 * words). Walks the string by 16-byte page, decoding each scalar, comparing
 * against a 2-char target, and returns whether the first mismatch / end
 * matched. Traps on page overflow. Confidence: low.
 * Notes: unaff_x20 = page cursor; FUN_002b141c utf8 decode; FUN_0001da84
 *   page advance; SoftwareBreakpoint(1,0x47cc94). */
bool sk_r28_0047cadc(uint64_t a1, uint64_t a2)
{
    uint64_t len = a1 & 0xffffffffffff;
    if ((a2 & 0x2000000000000000) != 0)
        len = a2 >> 0x38 & 0xf;
    uint32_t big = (uint32_t)(a1 >> 0x3b) & 1;
    if ((a2 & 0x1000000000000000) == 0)
        big = 1;
    sk_x_0036b270(a2);
    uint64_t page = 0xf;
    uint64_t idx = 0;
    uint64_t target;
    uint8_t c = 0;
    do {
        idx = page >> 0xe;
        if (idx == len * 4) break;
        uint64_t p = page;
        if ((page & 0xc) == (4ULL << big))
            p = sk_x_0001da84(page, a1, a2);
        uint64_t off = p >> 0x10;
        if (len <= off)
            SoftwareBreakpoint(1, 0x47cc94);
        if ((a2 >> 0x3c & 1) == 0) {
            if ((a2 >> 0x3d & 1) == 0) {
                int64_t base = (a2 & 0xfffffffffffffff) + 0x20;
                if ((a1 >> 0x3c & 1) == 0)
                    base = sk_x_002a9ba8(a1, a2);
                c = *(uint8_t *)(base + off);
            } else {
                uint64_t w0 = a1, w1 = a2 & 0xffffffffffffff;
                c = *(uint8_t *)((uint64_t)&w0 + off);
            }
        } else {
            c = sk_x_002b141c(p, a1, a2);
        }
        if ((page & 0xc) == (4ULL << big)) {
            page = sk_x_0001da84(page, a1, a2);
            if ((a2 >> 0x3c & 1) != 0) goto again;
            page = (page & 0xffffffffffff0000) + 0x10004;
        } else {
            if ((a2 >> 0x3c & 1) == 0) {
                page = (page & 0xffffffffffff0000) + 0x10004;
            } else {
again:
                if (len <= page >> 0x10)
                    SoftwareBreakpoint(1, 0x47cc98);
                page = sk_x_002b141c(page, a1, a2);
            }
        }
        uint64_t v = sk_x_0024d9ac(&sk_g_005a5538);
        uint8_t c1 = c;
        sk_x_0024917c(&target, &c1);
        sk_x_0036b118(v);
    } while ((target & 1) != 0);
    sk_x_003a25d4(a2);
    return idx != len * 4;
}

/* FUN_0047cc98 @ 0x0047cc98   (est. sk_r28_parse_alternation)
 * Ghidra: uint FUN_0047cc98(long)
 * Recursive regex alternation parser over the token stream at param+0x10;
 * dispatches on token kinds 5/6/7 (open/close/pipe) and recurses.
 * Confidence: medium. */
uint32_t sk_r28_0047cc98(int64_t a1)
{
    int64_t n = *(int64_t *)(a1 + 0x10);
    uint8_t s1[352], s2[352], s3[352];
    uint32_t r = 0;
    uint64_t rr;
loop:
    if (n == 0) { r = 0; goto ret; }
    sk_x_004ac3e4(s1);
    sk_x_004ac3e4(s2);
    int k = sk_x_0049df0c(s1);
    if ((uint32_t)(k - 4) > 3) { r = 1; goto ret; }
    switch (k) {
    case 5:
    case 7:
        sk_x_0049df18(s2);
        sk_x_004ac4e0();
        sk_x_004ac034(s3);
        sk_x_00352c68();
        rr = (uint64_t)sk_r28_0047cc98(0);
        if ((rr & 1) == 0) { sk_x_004a3918(s1); r = 0; goto ret; }
        break;
    case 6:
        sk_x_0049df18(s2);
        sk_x_004ac4e0();
        sk_x_004ac034(s3);
        break;
    default:
        n = n - 1;
        goto loop;
    }
    sk_x_0035354c();
    r = (uint32_t)sk_r28_0047cc98(0);
    sk_x_004a3918(s1);
ret:
    return r & 1;
}

/* FUN_0047cdbc @ 0x0047cdbc   (est. sk_r28_string_init)
 * Ghidra: void FUN_0047cdbc(undefined8,undefined8,undefined8)
 * Builds a string/error box: reads a scalar/char, allocates a descriptor,
 * then invokes the method with the packed value and tears the box down.
 * Confidence: low (extraout_x16 = method owner, unmodeled). */
void sk_r28_0047cdbc(uint64_t a1, uint64_t a2, uint64_t a3)
{
    uint64_t owner = 0;                /* extraout_x16: method owner */
    uint64_t u1 = sk_x_00350a28();
    uint64_t box = sk_x_00310d68(0, a3);
    uint8_t buf[24];
    sk_x_00077024(buf);
    uint64_t u2 = sk_x_003509c8();
    (*(uint64_t (**)())(owner + 0x10))(u2, u1);
    sk_x_004ab9e0();
    sk_x_00350774();
    sk_x_000839d8();
    sk_x_000026e8();
    sk_x_004ab618();
    sk_x_00310d98();
}

/* FUN_0047ce4c @ 0x0047ce4c   (est. sk_r28_string_finish)
 * Ghidra: void FUN_0047ce4c(void)
 * Finalizes a string record: stores the boxed value into self+0x18, marks
 * ownership, and emits the report close. Confidence: medium.
 * Notes: unaff_x20 = self; FUN_000839d8 report. */
void sk_r28_0047ce4c(void)
{
    uint64_t self = 0;                 /* unaff_x20 */
    sk_x_00352800();
    sk_x_003504e8();
    uint64_t v = sk_x_00310d68();
    *(uint64_t *)(self + 0x18) = v;
    v = sk_x_00077024();
    sk_x_00350774(v, 1);
    sk_x_000839d8();
}

/* FUN_0047ce8c @ 0x0047ce8c   (est. sk_r28_string_compare)
 * Ghidra: void FUN_0047ce8c(void)
 * Compares two strings via the shared error/string box and reports the
 * result. Confidence: low (unaff_x20 = self). */
void sk_r28_0047ce8c(void)
{
    uint64_t self = 0;                 /* unaff_x20 */
    uint64_t kind = 0;                 /* lStack_38 local kind */
    uint8_t out[16], tmp[24];
    sk_x_004ab128();
    sk_x_004a4ac4(self + 8, out);
    if (kind != 1) {
        sk_x_0034cc24();
        sk_x_004a4b14(tmp);
    } else {
        sk_x_004aaccc();
        sk_x_004a4b14(out);
    }
    sk_x_0009461c();
}

/* FUN_0047cf0c @ 0x0047cf0c   (est. sk_r28_array_append)
 * Ghidra: void FUN_0047cf0c(undefined8 x 6)
 * Bulk-appends param_6 records (each 0x58 bytes) read at param_6+0x20 into
 * the global array DAT_00657778, decoding each record, growing the array as
 * needed. Then drains the appended records building result objects.
 * Confidence: low (large; SoftwareBreakpoint(1,0x47d348)).
 * Notes: heavy use of thunk_FUN_0024d9ac iterator, FUN_00117cc4 memmove. */
void sk_r28_0047cf0c(uint64_t a1, uint64_t a2, uint64_t a3, uint64_t a4, uint64_t a5, int64_t a6)
{
    uint64_t kind2 = 0;                /* local box-kind flag (lStack_110) */
    uint64_t it = sk_x_0024d9ac(&sk_g_005a4b50);
    int64_t base = a6 + 0x20;
    uint64_t arr = 0x657778;   /* DAT_00657778 (array header) */
    int64_t i;
    for (i = *(int64_t *)(a6 + 0x10); i != 0; i = i - 1) {
        uint8_t rec[0x68];
        uint8_t tag;
        uint64_t box[2] = { a4, a5 };
        sk_x_0049c704(base, &rec);
        sk_x_00117cc4(&rec, &box, 0x68);
        sk_x_0036b270(a5);
        sk_x_0024917c(&tag, &rec);
        if (tag == 0x01) {
            uint64_t n;
            sk_x_003a261c(&arr);
            n = *(uint64_t *)(arr + 0x10);
            if (*(uint64_t *)(arr + 0x18) >> 1 <= n)
                sk_x_0049a604(1 < *(uint64_t *)(arr + 0x18), n + 1, 1);
            *(uint64_t *)(arr + 0x10) = n + 1;
            sk_x_00117cc4(arr + n * 0x68 + 0x20, &rec, 0x68);
        } else {
            sk_x_0049c714(&rec);
        }
        base += 0x58;
    }
    sk_x_0036b118(it);
    /* drain phase */
    int64_t cnt = *(int64_t *)(arr + 0x10);
    uint64_t out = 0x657778;
    if (cnt == 0) {
        sk_x_0036b118(arr);
    } else {
        int64_t j;
        sk_x_001a0754(0, cnt, 0);
        for (j = 0; j != cnt; j++) {
            uint64_t v = *(uint64_t *)(arr + j * 0x68 + 0x20);
            uint8_t rbox[8];
            sk_x_004a4ac4(arr + j * 0x68 + 0x20 + 8, &rbox, 0x657be0, &sk_g_005a3c88);
            if (kind2 == 1) {
                sk_x_004a4b14(&rbox, 0x657be0, &sk_g_005a3c88);
                if ((int64_t)v < 1)
                    SoftwareBreakpoint(1, 0x47d348);
                sk_x_00455ac8(0x675c68, v - 1, 0x675c68);
                sk_r28_0047ce4c();
            } else {
                int64_t k = (int64_t)v;
                for (; k != 0; k = k - 1) {
                    uint8_t rr[8];
                    sk_x_00319808(out, &rr);
                    uint64_t w = sk_x_0006a4c0(&rr);
                    sk_r28_0047cdbc(w, out, 0);
                    sk_x_000026e8(&rr);
                }
            }
            uint64_t n2 = *(uint64_t *)(out + 0x10);
            if (*(uint64_t *)(out + 0x18) >> 1 <= n2)
                sk_x_001a0754(1 < *(uint64_t *)(out + 0x18), n2 + 1, 1);
            *(uint64_t *)(out + 0x10) = n2 + 1;
            sk_x_00310d98(out, out + n2 * 0x20 + 0x20);
        }
        int64_t n3 = *(int64_t *)(arr + 0x10);
        sk_x_0036b118(arr);
        if (cnt != n3)
            SoftwareBreakpoint(1, 0x47d290);
    }
    /* final: if single element, copy it out; else build an error object */
    if (*(int64_t *)(out + 0x10) == 1) {
        sk_x_00319808(out + 0x20, a1);
        sk_x_0036b118(out);
    } else {
        uint64_t u2 = sk_x_00002534(0x657be8, &sk_g_005a3c98).lo;
        uint64_t u4 = sk_x_004a42a0(0x657bf0, 0x657be8, &sk_g_005a3c98, &sk_g_004e824c);
        sk_x_0045567c(a1, &out, u2, u4);
    }
}

/* FUN_0047d358 @ 0x0047d358   (est. sk_r28_cap_capture)
 * Ghidra: void FUN_0047d358(void)
 * Captures a capability/context: reads two words from self, refs them, builds
 * an error context object (0x30 bytes, kind 7), records a tag word, and
 * either commits to a report frame (0x90 bytes) or tears down. Confidence: low.
 * Notes: unaff_x20/x21 = self/flag; FUN_0036a940 alloc; DAT_00687d10 label. */
void sk_r28_0047d358(void)
{
    uint64_t self = 0;                 /* unaff_x20 */
    int64_t unaff_x21 = 0;             /* unaff_x21: commit flag */
    uint64_t frame[16] = {0};
    uint8_t rep[0x90] = {0};
    uint64_t slot = 0;
    uint64_t u2 = sk_x_00353cfc();
    uint64_t w1 = *(uint64_t *)(self + 0x18);
    uint64_t w0 = *(uint64_t *)(self + 0x10);
    sk_x_0036b270(w1);
    sk_x_00493354(w0);
    sk_pair_t p0 = sk_x_00002534(&sk_g_00657d88, &sk_g_005a4b78);
    uint64_t v = sk_x_004abdc4(p0.lo, p0.hi, p0.lo);
    sk_x_004ab288(v, 0x6728f0);
    sk_x_001f0130();
    sk_x_00002534(0x64e078, &sk_g_005a4b80);
    sk_pair_t p1 = sk_x_00002534(&sk_g_00657d90, &sk_g_005a4b88);
    sk_x_004a35b8();
    sk_pair_t p2 = sk_x_0035060c();
    sk_x_001f0130(p2.lo, p2.hi, p1.lo);
    uint64_t h = sk_x_0001a1c8();
    sk_x_00002534(&sk_g_00657da0, &sk_g_005a4b90);
    sk_pair_t p3 = sk_x_001f0130();
    sk_x_0035060c(p3.lo, p3.hi, 0x677880);
    sk_x_001f0130();
    sk_x_0036b118(h);
    uint64_t f1 = w1, f2 = w1;
    uint8_t stack[0xe0];
    sk_x_004a363c(&f1, frame);
    sk_x_004a364c(&f2);
    sk_x_00117cc4(stack, &f1, 0xe0);
    uint64_t w = *(uint64_t *)(self + 0x10);
    if ((((uint32_t)(w >> 0x3b) & 0x1e) | (uint32_t)w >> 2 & 1) == 0xe) {
        /* zero local_2b8/local_2b0 */
    }
    sk_x_00473244(w);
    if (unaff_x21 == 0) {
        frame[0] = 0x687d10;
        uint8_t b = sk_x_004934a8(frame, w);
        sk_x_0036b118(frame[0]);
        uint8_t tag = b & 0xfd;
        uint64_t n;
        sk_x_003a261c(slot);
        n = *(uint64_t *)(slot + 0x10);
        if (*(uint64_t *)(slot + 0x18) >> 1 <= n) {
            sk_x_000ec004();
            slot = sk_x_00499158();
        }
        *(uint64_t *)(slot + 0x10) = n + 1;
        *(uint64_t *)(slot + n * 8 + 0x20) = 0x1c00000000000000;
        sk_x_00474fe8(rep);
        sk_x_0036b118();
        sk_x_004a364c(stack);
        sk_x_00117cc4(rep, rep, 0x90);
    } else {
        sk_x_0036b118();
        sk_x_004a364c(stack);
    }
    sk_x_00353d14(u2);
}
/* FUN_0047d6e0 @ 0x0047d6e0   (est. sk_r28_release_self_words)
 * Ghidra: void FUN_0047d6e0(void)
 * Releases the two self-owned words at self+0x10 and self+0x18 via the shared
 * refcount-release helper. Confidence: medium.
 * Notes: unaff_x20 = self; FUN_0036b118 = refcount release. */
void sk_r28_0047d6e0(void)
{
    uint64_t self = 0;                 /* unaff_x20 */
    sk_x_004abf50(*(uint64_t *)(self + 0x10));
    sk_x_0036b118();
    sk_x_0036b118(*(uint64_t *)(self + 0x18));
}

/* FUN_0047d70c @ 0x0047d70c   (est. sk_r28_dtor_70c)
 * Ghidra: void FUN_0047d70c(void)
 * Destructor thunk: releases the self words then runs two cleanup helpers.
 * Confidence: medium. Notes: unaff_x20 = self. */
void sk_r28_0047d70c(void)
{
    sk_r28_0047d6e0();
    sk_x_000dce50();
    sk_x_0036b6ac();
}

/* FUN_0047d710 @ 0x0047d710   (est. sk_r28_dtor_710)
 * Ghidra: void FUN_0047d710(void)
 * Destructor thunk (identical to 0047d70c). Confidence: medium. */
void sk_r28_0047d710(void)
{
    sk_r28_0047d6e0();
    sk_x_000dce50();
    sk_x_0036b6ac();
}

/* FUN_0047d73c @ 0x0047d73c   (est. sk_r28_regex_err_string)
 * Ghidra: undefined1[16] FUN_0047d73c(undefined8,undefined8,uint)
 * Builds a 16-byte Swift error/description descriptor for a regex parse
 * error kind (param_3 low byte): kind 0 → "> expected Regex<…", kind 1 →
 * a compacted tag pair; otherwise a generic failure descriptor.
 * Confidence: medium.
 * Notes: thunk_FUN_002acbb8 dispatch; string constant 0x5e2180. */
sk_pair_t sk_r28_0047d73c(uint64_t a1, uint64_t a2, uint32_t a3)
{
    sk_x_0008409c();
    if ((a3 & 0xff) == 0) {
        sk_x_00100c04();
        sk_x_002a4ab4(0x38);
        sk_x_002acbb8(0xd00000000000001e, 0x80000000005e2140);
        sk_x_004ac318();
        sk_x_00208418();
        sk_x_002acbb8();
        sk_x_003a25d4(0);
        sk_x_004ac348((uint64_t)"s_>___expected__Regex<_005e2180");
        sk_x_002acbb8();
        sk_x_0035354c();
        sk_x_00208418();
        sk_x_00465294();
        sk_x_003a25d4();
        return (sk_pair_t){ 0x273e, 0xe200000000000000 };
    }
    if ((a3 & 0xff) != 1) {
        return (sk_pair_t){ 0x80000000005e2180, 0xd000000000000034 };
    }
    sk_x_00100c04();
    sk_x_002a4ab4(0x32);
    sk_x_003a25d4(0);
    sk_x_004ab968(0x27);
    sk_x_00084180();
    sk_x_002acbb8();
    sk_x_002acbb8(0xd00000000000002f, 0x80000000005e2110);
    return (sk_pair_t){ 0x80000000005e2110, 0xd00000000000002f };
}

/* FUN_0047d8ec @ 0x0047d8ec   (est. sk_r28_regex_flag_apply)
 * Ghidra: void FUN_0047d8ec(void)
 * Applies a regex flag kind (in_w3 low byte): 0 enables a default flag;
 * 1 enables a second flag; otherwise no-op. Confidence: medium.
 * Notes: thunk_FUN_002298d4 = vspace wait/sync; in_w3 = flag byte. */
void sk_r28_0047d8ec(void)
{
    uint32_t in_w3 = 0;                /* unmodeled flag-byte register */
    uint64_t u = sk_x_00350b54();
    if ((in_w3 & 0xff) == 0) {
        sk_x_002298d4(1);
        sk_x_002298d4();
    } else if ((in_w3 & 0xff) == 1) {
        sk_x_002298d4(2);
        sk_x_003504a0(u);
        sk_x_001b9084();
        return;
    }
    sk_x_002298d4();
}

/* FUN_0047d96c @ 0x0047d96c   (est. sk_r28_regex_flag_run)
 * Ghidra: void FUN_0047d96c(void)
 * Runs a regex flag-setup pass: hashes the options, applies flags.
 * Confidence: medium. Notes: FUN_001a84f4/001a8564 hash pair. */
void sk_r28_0047d96c(void)
{
    uint8_t st[72];
    sk_x_004080b0();
    sk_x_00350548(st);
    sk_r28_0047d8ec();
    sk_x_001a8564();
}

/* FUN_0047d9e8 @ 0x0047d9e8   (est. sk_r28_str_build)
 * Ghidra: void FUN_0047d9e8(undefined8,undefined8,undefined1)
 * Packs two words + a tag byte into a string descriptor and hands it to a
 * shared string-builder helper. Confidence: medium.
 * Notes: FUN_00369efc build; tag constant DAT_005a4990. */
void sk_r28_0047d9e8(uint64_t a1, uint64_t a2, uint8_t a3)
{
    uint64_t w[2]; uint8_t b;
    w[0] = a1; w[1] = a2; b = a3;
    sk_x_00369efc(&w, 0x687498, &sk_g_005a4990);
}

/* FUN_0047da48 @ 0x0047da48   (est. sk_r28_regex_flag_run2)
 * Ghidra: void FUN_0047da48(void)
 * Regex flag-setup pass variant (hash + apply), like 0047d96c.
 * Confidence: medium. */
void sk_r28_0047da48(void)
{
    uint8_t st[72];
    sk_x_001a84f4(st);
    sk_x_00350878(st);
    sk_r28_0047d8ec();
    sk_x_001a8564();
}

/* FUN_0047dac4 @ 0x0047dac4   (est. sk_r28_prop_decode)
 * Ghidra: uint FUN_0047dac4(void)
 * Decodes a scalar-property token: parses a 0xb0-byte string view, reads its
 * kind via FUN_0049e2f0/FUN_00458af8, and classifies it (0x2d/0x5f special
 * tokens, leading-byte width decode). Returns {value, flag} packed as
 * value & 0xff | flag<<8. Confidence: low.
 * Notes: FUN_002a0cf8 string compare; DAT_005a5538; register-heavy. */
uint32_t sk_r28_0047dac4(void)
{
    bool flag_ZR = false;              /* carry/zero flag artifact */
    uint64_t x26 = 0;
    sk_pair_t p = sk_x_00463f94();
    uint8_t v[0xb0];
    sk_x_00117cc4(p.lo, p.hi, 0xb0);
    int k = sk_x_004ac210(v);
    uint8_t s1[0x99], s2[0x99], s3[0x99];
    uint32_t value = 0, flag = 0;
    if (flag_ZR) {
        uint64_t w = sk_x_0049e2f0(v);
        sk_x_00117cc4(s1, w, 0x99);
        sk_x_00117cc4(s2, w, 0x99);
        int k2 = sk_x_00458af8(s2);
        if (k2 == 4) {
            sk_x_00458b14(s2);
            sk_x_004176bc();
            value = sk_x_0034ecc8();
            if (flag_ZR) goto wide;
            if (value < 0x80) { flag = 0; goto ret; }
        } else if (k2 == 1) {
            uint32_t *p8 = (uint32_t *)sk_x_00458b14(s2);
            value = *p8;
            if (value < 0x80) { flag = 0; goto ret; }
        }
        sk_x_00117cc4(s3, s1, 0x99);
        int k3 = sk_x_00458af8(s3);
        if (k3 == 0) {
            int64_t *pl = (int64_t *)sk_x_00458b14(s3);
            if (*pl != 0xa0d || pl[1] != (int64_t)-0x1e00000000000000) {
                sk_x_0009461c();
                sk_x_004aa890();
                uint64_t c = sk_x_002a0cf8();
                if ((c & 1) == 0) {
                    sk_x_0009461c();
                    value = sk_x_002bd8f0();
                    flag = value >> 8 & 0xff;
                    goto ret;
                }
            }
        }
    } else {
        if (k == 1) {
            sk_x_0049e2f0(v);
            sk_x_004abc0c();
            value = 0;
            flag = 1;
            goto ret;
        }
        if (k == 0) {
            int64_t *pl = (int64_t *)sk_x_0049e2f0(v);
            if (*pl != 0xa0d || pl[1] != (int64_t)-0x1e00000000000000) {
                sk_x_0009461c();
                sk_x_004aa890();
                uint64_t c = sk_x_002a0cf8();
                if ((c & 1) == 0) {
                    sk_x_0009461c();
                    value = sk_x_002bd8f0();
                    flag = value >> 8 & 0xff;
                    goto ret;
                }
            }
        }
    }
wide:
    value = 0; flag = 1;
ret:
    return value & 0xff | flag << 8;
}

/* FUN_0047dc1c @ 0x0047dc1c   (est. sk_r28_identifier_scan)
 * Ghidra: void FUN_0047dc1c(undefined8,undefined8,ulong,ulong)
 * Scans an identifier/operator token stream: walks scalar-by-scalar,
 * handling `-`/`_` continuations and comparison operators, and commits the
 * result (equal/not) via the shared helper. Confidence: low.
 * Notes: register-heavy (unaff_x26/x30); FUN_00267510 scalar parse;
 *   FUN_001b798c advance; SoftwareBreakpoint-free. */
void sk_r28_0047dc1c(uint64_t a1, uint64_t a2, uint64_t a3, uint64_t a4)
{
    uint64_t x26 = 0;                  /* unaff_x26: continuation flag */
    uint64_t x30 = 0;                  /* unaff_x30: caller result slot */
    sk_x_0035193c();
    sk_pair_t av = sk_x_00077888();
    bool b3 = (a4 & 0x2000000000000000) == 0;
    uint64_t len = a3 & 0xffffffffffff;
    if (!b3) len = a4 >> 0x38 & 0xf;
    sk_x_003532b8();
    uint64_t u5 = 0xf, u6 = 0;
    bool result = false;
    do {
        if (len * 4 <= u6 >> 0xe) { result = false; goto commit; }
        sk_x_004aaa78();
        sk_x_00267510();
        sk_x_002bd9ac();
        sk_x_00464e64();
        if ((x26 & 1) == 0) {
            sk_x_004aaa78();
            sk_pair_t t = sk_x_00267510();
            int64_t t8 = t.hi;
            if (t.lo == 0x2d && t8 == (int64_t)-0x1f00000000000000) {
                sk_x_003a25d4(t8);
            } else {
                sk_x_000b44cc(t.lo, t8, 0x2d);
                sk_x_00464e64();
                if ((x26 & 1) == 0) {
                    sk_x_004aaa78();
                    t = sk_x_00267510();
                    t8 = t.hi;
                    if (t.lo == 0x5f && t8 == (int64_t)-0x1f00000000000000) {
                        sk_x_003a25d4(t8);
                    } else {
                        sk_x_000b44cc(t.lo, t8, 0x5f);
                        sk_x_00464e64();
                        if ((x26 & 1) == 0) break;
                    }
                }
            }
        }
        sk_x_004aaa78();
        u6 = sk_x_001b798c();
    } while (1);
    u6 = sk_x_001b798c();
commit:
    sk_x_00351774(result, x30);
}

/* FUN_0047dee8 @ 0x0047dee8   (est. sk_r28_err_canceled)
 * Ghidra: void FUN_0047dee8(undefined8,undefined8,long)
 * Builds a "L4ErrorCode.canceled" error object when param_3 has pending
 * work: allocates an error context (string "L4_ErrorCodeCanceled"),
 * chains it and dispatches. Traps if param_3 is empty. Confidence: medium.
 * Notes: SoftwareBreakpoint(1,0x47dfc4); DAT_00688688 string. */
void sk_r28_0047dee8()
{
    int64_t a3 = 0;                    /* unmodeled 3rd register arg */
    uint64_t x16 = 0, x19 = 0, x20 = 0; /* unaff_x16/x19/x20 */
    int64_t x8 = 0;                    /* extraout_x8 */
    bool ZR = false;
    if (*(int64_t *)(a3 + 0x10) != 0) {
        sk_x_003504d0();
        sk_x_004aa734(*(uint32_t *)(a3 + x8 * 4 + 0x1c));
        uint64_t (*fn)() = (void*)sk_r28_0047f5d0;
        if (!ZR) fn = (void*)x16;
        sk_x_00002834((uint64_t)"s_L4_ErrorCodeCanceled_00688688");
        int64_t e = sk_x_0036a940();
        *(uint64_t *)(e + 0x10) = x20;
        *(uint64_t *)(e + 0x18) = x19;
        sk_x_0036b270();
        (*fn)((uint64_t)sk_x_004a4158, e);
        sk_x_00351a50();
        sk_x_0036b118(e);
        sk_x_0009461c();
        return;
    }
    SoftwareBreakpoint(1, 0x47dfc4);
}

/* FUN_0047dfc4 @ 0x0047dfc4   (est. sk_r28_op_dispatch2)
 * Ghidra: void FUN_0047dfc4(void)
 * Large op-dispatch switch on self kind byte (self+0x20): handles message
 * op kinds 0..0xf — error-code mapping, regex/unicode metadata builds,
 * cancellation, TODO-flag reports — constructing the matching error/context
 * object and committing it. Confidence: low.
 * Notes: heavy switch; unaff_x20 = self; thunk_FUN_0044f818 dispatch. */
void sk_r28_0047dfc4(void)
{
    uint64_t *x20 = 0;                 /* unaff_x20: self word array */
    uint64_t x16 = 0;
    sk_pair_t au = sk_x_004acb3c();
    int64_t obj = au.lo;
    if (*(int64_t *)(obj + 0x10) == 0)
        SoftwareBreakpoint(1, 0x47e59c);
    uint32_t u1 = *(uint32_t *)(obj + *(int64_t *)(obj + 0x10) * 4 + 0x1c);
    uint64_t (*fn)() = (void*)sk_r28_0047f5d0;
    if ((u1 & 0x10000) != 0) fn = (void*)sk_r28_0047f808;
    uint64_t w0 = x20[0], f1 = x20[1], f2 = x20[2];
    switch ((char)x20[4]) {
    case 0: /* default */
        sk_r28_0047fa44(obj);
        goto commit;
    case 1:
        sk_r28_004801f8(obj);
        sk_x_00355d6c();
        goto commit;
    case 2:
        sk_x_004ab1fc(0x687ff8);
        sk_x_0036a940();
        sk_x_004ac93c();
        fn = (void*)sk_x_004a3eac;
        break;
    case 3:
        sk_x_004ab1fc(0x687fd0);
        sk_x_0036a940();
        sk_x_004ac93c();
        fn = (void*)sk_x_004a3e68;
        break;
    case 4:
        sk_x_00350624(w0);
        sk_r28_0047dee8();
        goto commit2;
    case 5:
        sk_x_004ab1fc(0x687f58);
        sk_x_0036a940();
        sk_x_004ac93c();
        fn = (void*)sk_x_004a3d8c;
        break;
    case 6:
        sk_x_0036a940(0x687f80, 0x18, 7);
        fn = (void*)sk_x_004a3dcc;
        break;
    case 7:
        sk_x_0036a940();
        sk_x_004ac584();
        fn = (void*)sk_x_004a3c94;
        break;
    case 8:
        sk_x_004ab1fc(0x687f30);
        sk_x_0036a940();
        sk_x_004ac93c();
        fn = (void*)sk_x_004a3d60;
        break;
    case 9:
        sk_x_00002834(0x687fa8);
        sk_x_0036a940();
        fn = (void*)sk_x_004a3e20;
        break;
    case 10:
        sk_x_000b430c();
        sk_x_002a4ab4(0x13);
        sk_x_004ab650();
        sk_x_002acbb8(0xd000000000000011, 0x80000000005e2e90);
        goto commit2;
    case 11:
        sk_r28_00480864(obj, w0);
        goto commit2;
    case 12:
        sk_x_000b430c();
        sk_x_002a4ab4(0x1a);
        sk_x_004ab650();
        sk_x_004ac008((uint64_t)"s_TODO__map_PCRE_special__005e2e90");
        goto commit2;
    case 13:
        sk_x_000b430c();
        sk_x_002a4ab4(0x1a);
        sk_x_004ab650();
        sk_x_004ac008((uint64_t)"s_TODO__map_Java_special__005e2e70");
        goto commit2;
    case 14:
        sk_x_004ab6b8(0xd000000000000017);
        goto commit2;
    case 15:
        if ((f1 == 0 && x20[3] == 0) && f2 == 0 && w0 == 0) {
            f2 = 0; f1 = (uint64_t)sk_r28_0047f9c4;
        } else if (w0 == 1 && (f1 == 0 && x20[3] == 0) && f2 == 0) {
            (*fn)((uint64_t)sk_r28_0047f9f0, 0);
            goto commit2;
        } else {
            f2 = 0;
            f1 = (uint64_t)sk_r28_0047f630;
            if ((u1 & 0x10000) != 0) f1 = (uint64_t)sk_r28_0047f868;
        }
        goto commit;
    default:
        goto commit;
    }
    (*fn)((uint64_t)fn, 0);
commit:
    sk_x_00355d6c();
commit2:
    sk_x_004acb20(f1, f2, au.hi);
}

/* FUN_0047e5dc @ 0x0047e5dc   (est. sk_r28_regex_loop)
 * Ghidra: void FUN_0047e5dc(void)
 * Regex match loop: iterates the token stream, decoding scalars, and
 * compares against anchor tokens (0x2d/0x5f), a CRLF pair (0xa0d), and
 * character classes; recurses into 0047dac4/0047e96c/0047e8ec. Confidence: low.
 * Notes: SoftwareBreakpoint on overflow; unaff_w25. */
void sk_r28_0047e5dc(void)
{
    uint32_t w25 = 0;                  /* unaff_w25 */
    uint64_t x1 = 0;                   /* extraout_x1 */
    sk_pair_t au = sk_x_0008e518();
    int64_t obj = au.lo;
    uint8_t b1[360], b2[352], b3[352];
    sk_x_004ab31c(b1);
    sk_x_00117cc4();
    sk_x_004ab31c(b2);
    sk_x_00117cc4();
    int k = sk_x_0049df0c(b2);
    uint64_t res = 2;
    if (k == 3) {
        sk_x_0049df18(b2);
        sk_x_004ab430();
        sk_x_00117cc4(b3, b1, 0x160);
        int64_t l8 = sk_x_0049df18(b3);
        sk_x_0036b270(*(uint64_t *)(l8 + 8));
        for (;;) {
            sk_x_0029fb80();
            if (x1 == 0) { res = au.hi & 1; break; }
            sk_pair_t t = sk_x_004ac960();
            if (t.lo == 0xa0d && t.hi == (int64_t)-0x1e00000000000000) {
                sk_x_004a3918();
                sk_x_003a25d4();
                res = 2; break;
            }
            sk_x_003512c0();
            sk_x_004aa890();
            uint64_t c = sk_x_002a0cf8();
            if ((c & 1) != 0) { res = 2; break; }
            sk_x_003512c0();
            sk_x_004aa890();
            c = sk_x_002a0cf8();
            if ((c & 1) == 0) {
                sk_x_003512c0();
                c = sk_x_002bd848();
                if ((c & 1) != 0) {
                    sk_x_003512c0();
                    c = sk_x_0016749c();
                    if ((c & 0xff00000000) == 0x100000000)
                        SoftwareBreakpoint(1, 0x47e8e0);
                    if ((c & 0xffffff80) == 0) {
                        sk_x_003512c0();
                        c = sk_x_0016749c();
                        if ((c & 0xff00000000) == 0x100000000)
                            SoftwareBreakpoint(1, 0x47e8e4);
                        sk_x_004ac2d0();
                        sk_x_003a25d4();
                        if ((w25 & 0xffffff00) != 0)
                            SoftwareBreakpoint(1, 0x47e8dc);
                        continue;
                    }
                }
                sk_x_003a25d4();
                res = 2; break;
            }
            sk_x_003a25d4();
            w25 = 0;
        }
    } else if (k == 1) {
        res = sk_r28_0047dac4() & 1;
    } else if (k == 0) {
        sk_x_0049df18(b2);
        res = sk_r28_0047dac4() & 1;
    }
    sk_x_00350b84(res);
    sk_x_0008e500();
}
/* FUN_0047e8ec @ 0x0047e8ec   (est. sk_r28_case_fold)
 * Ghidra: undefined1 FUN_0047e8ec(uint,undefined1,ulong)
 * ASCII case-folding helper: if param_3 flag set, folds an ASCII letter
 * (uppercase<->lowercase) by the standard +/-0x20 delta; leaves param_2
 * unchanged and returns it. Confidence: medium.
 * Notes: FUN_004950f0 = scalar emit; in_CY/in_ZR = flag bits. */
uint8_t sk_r28_0047e8ec(uint32_t a1, uint8_t a2, uint64_t a3)
{
    bool CY = false, ZR = false;       /* flag-bits artifacts */
    sk_x_004950f0(a1);
    if ((a3 & 1) != 0) {
        sk_x_004ac7ec(a1 - 0x40);
        if (CY && !ZR) {
            if (0x19 < (a1 - 0x61 & 0xff)) return a2;
            a1 = a1 - 0x20;
        } else {
            a1 = a1 | 0x20;
        }
        sk_x_004950f0(a1);
    }
    return a2;
}

/* FUN_0047e96c @ 0x0047e96c   (est. sk_r28_range_contains)
 * Ghidra: uint FUN_0047e96c(byte,byte,uint)
 * Scans the inclusive range [param_1, param_2] and returns param_3&1 if any
 * value equals the loop counter (i.e. tests range membership of the counter);
 * traps if param_2 < param_1 or the scan overflows past 0xff. Confidence: medium.
 * Notes: SoftwareBreakpoint(1,0x47ea18) / (1,0x47ea08). */
uint32_t sk_r28_0047e96c(uint8_t a1, uint8_t a2, uint32_t a3)
{
    if (a2 < a1)
        SoftwareBreakpoint(1, 0x47ea18);
    uint64_t i = a1;
    for (;;) {
        uint32_t lo = (uint32_t)i;
        if (a2 == i) return a3 & 1;
        i = i + 1;
        if ((lo & 0xff) == 0xff)
            SoftwareBreakpoint(1, 0x47ea08);
    }
}

/* FUN_0047ea18 @ 0x0047ea18   (est. sk_r28_scalar_validate)
 * Ghidra: bool FUN_0047ea18(uint)
 * Validates that a scalar encodes/round-trips: builds the UTF-8 sequence for
 * param_1 (1/2/3-byte by magnitude), decodes it back, and reports whether the
 * original scalar equals the decoded value. Traps on invalid continuation.
 * Confidence: medium.
 * Notes: FUN_00255d4c utf8 encode; FUN_00294cb4 decode; SWBP(1,0x47eaa8). */
bool sk_r28_0047ea18(uint32_t a1)
{
    uint64_t v;
    if (a1 < 0x80) v = (uint64_t)(a1 + 1);
    else if (a1 < 0x800) v = sk_x_004abff8();
    else v = sk_x_004aacf8(((a1 & 0x3f) << 8 | a1 >> 6 & 0x3f) << 8);
    sk_pair_t au = sk_x_00255d4c(v);
    uint64_t box = au.lo;
    if (au.hi >= 0) {
        sk_x_00294cb4(&box);
        uint64_t r = sk_r28_0047edf4();
        sk_x_003a25d4(0);
        return r >> 0x20 == 0 && a1 == (uint32_t)r;
    }
    SoftwareBreakpoint(1, 0x47eaa8);
    return false;
}

/* FUN_0047ead4 @ 0x0047ead4   (est. sk_r28_range_ci)
 * Ghidra: void FUN_0047ead4(undefined8 x 9)
 * Case-insensitive scalar range test: decodes the next scalar from the UTF-8
 * stream (handling 1/2/3-byte continuations), optionally applies ASCII
 * case-fold, then tests membership in [param_5, param_6]; if the range is a
 * case pair it tries both cases via 0047ef1c/0047ee98. Commits result.
 * Confidence: low.
 * Notes: register-heavy (unaff_x24/x25/x30); SoftwareBreakpoint(1,0x47ed00). */
void sk_r28_0047ead4(uint64_t a1, uint64_t a2, uint64_t a3, uint64_t a4,
                     uint32_t a5, uint32_t a6, uint64_t a7, uint64_t a8, uint64_t a9)
{
    uint64_t x24 = 0, x25 = 0, x30 = 0;   /* unaff_x24/x25/x30 */
    uint64_t x8 = 0, x9 = 0, x10 = 0, x16 = 0;
    uint32_t x8_00 = 0;
    uint64_t stack0 = 0;
    sk_x_00077698();
    uint32_t u11 = (uint32_t)a4;
    uint64_t u5 = a3;
    sk_x_00407ab8();
    sk_r28_0047ed40(u5, (u11 ^ 0xffffffff) & 1);
    uint64_t scalar = 0;
    if ((~u11 & 1) == 0) {
        sk_x_00351300(a3);
        sk_x_00267510();
        scalar = sk_r28_0047edf4();
        sk_x_003a25d4(0);
        if (scalar >> 0x20 == 0) goto decode_done;
    } else {
        sk_x_00351300(a3);
        scalar = sk_x_00167404();
        if ((x24 >> 0x3c & 1) != 0) {
            sk_x_00351300(scalar & 0xffffffffffff0000);
            scalar = sk_x_002a49a8();
            goto decode_done;
        }
        if ((x24 >> 0x3d & 1) != 0) {
            uint8_t b = *(uint8_t *)((uint64_t)&stack0 + (scalar >> 0x10));
            scalar = (uint64_t)b; u11 = b; a9 = x25;
            if ((int8_t)b < 0) {
                sk_x_00352af0();
                switch (x16) {
                case 1: goto cont1;
                case 2: goto cont2;
                case 3: goto cont3;
                }
            }
            goto decode_done;
        }
        if ((x25 >> 0x3c & 1) == 0) {
            sk_x_00350618();
            x8 = (uint64_t)sk_x_002a9ba8();
        } else {
            x8 = (uint64_t)sk_x_002a9ba8();
        }
        uint8_t b = *(uint8_t *)(x8 + (scalar >> 0x10));
        scalar = (uint64_t)b; u11 = b;
        if ((int8_t)b >= 0) goto decode_done;
        sk_x_00352af0();
        switch (x16) {
cont1:
        case 1:
            sk_x_00353ff4();
            scalar = (uint64_t)(x8_00 & 0xfffff800 | x8_00 & 0x3f | (u11 & 0x1f) << 6);
            break;
cont2:
        case 2:
            sk_x_00352e9c();
            u11 = (u11 & 0xf) << 0xc | (x9 & 0x3f) << 6;
            scalar = (uint64_t)(u11 | x8 & 0x3f);
            break;
cont3:
        case 3:
            sk_x_0034c6d4();
            u11 = (u11 & 0xf) << 0x12 | (x9 & 0x3f) << 0xc | (x10 & 0x3f) << 6;
            scalar = (uint64_t)(u11 | x8 & 0x3f);
            break;
        }
    }
decode_done:
    if (a6 < a5)
        SoftwareBreakpoint(1, 0x47ed00);
    u11 = (uint32_t)scalar;
    bool u4 = a5 <= u11 && a6 == u11;
    uint64_t u9;
    if (a5 <= u11 && u11 <= a6) {
        u9 = 0;
    } else {
        if ((a7 & 1) != 0) {
            uint64_t c1 = sk_x_002bc330(scalar);
            if ((c1 & 1) != 0) {
                sk_x_0029d560(scalar);
                uint64_t r = (a4 & 1) == 0 ? sk_r28_0047ef1c() : sk_r28_0047ee98();
                sk_x_003a25d4(0);
                sk_x_004ab11c(r & 0xff00000000);
                u11 = (uint32_t)r;
                bool b2 = !u4;
                u4 = (!u4 && a5 <= u11) && a6 == u11;
                if ((b2 && a5 <= u11) && u11 <= a6) { u9 = 0; goto commit; }
            }
            uint64_t c2 = sk_x_002bc34c(scalar);
            if ((c2 & 1) != 0) {
                sk_x_0029da50(scalar);
                uint64_t r = (a4 & 1) == 0 ? sk_r28_0047ef1c() : sk_r28_0047ee98();
                sk_x_003a25d4(0);
                sk_x_004ab11c(r & 0xff00000000);
                if ((!u4 && a5 <= (uint32_t)r) && (uint32_t)r <= a6) { u9 = 0; goto commit; }
            }
        }
        u5 = 0; u9 = 1;
    }
commit:
    sk_x_0007767c(u5, u9, x30);
}

/* FUN_0047ed40 @ 0x0047ed40   (est. sk_r28_scalar_next)
 * Ghidra: void FUN_0047ed40(void)
 * Advances to the next scalar in a UTF-8 string: reads the next scalar,
 * handling the direct / table-indirect / inline-string storage forms.
 * Confidence: low. Notes: register-heavy; unaff_x19/x20 = string words. */
void sk_r28_0047ed40(void)
{
    uint64_t x1 = 0, x8 = 0, x9 = 0;   /* extraout registers */
    uint64_t x19 = 0, x20 = 0;         /* unaff_x19/x20 = string words */
    sk_x_00077888();
    if ((x1 & 1) == 0) {
        sk_x_00350624();
        sk_x_001b798c();
        return;
    }
    sk_x_00350624();
    sk_x_00167404();
    if ((x19 >> 0x3c & 1) != 0) {
        sk_x_00350624();
        sk_x_002a49a8();
        return;
    }
    if (((x19 >> 0x3d & 1) == 0) && ((x20 >> 0x3c & 1) == 0)) {
        sk_x_0007c1c4();
        x8 = (uint64_t)sk_x_002a9ba8();
    }
    sk_x_004abcdc();
    sk_x_004abd2c(x8 + x9);
}

/* FUN_0047edf4 @ 0x0047edf4   (est. sk_r28_utf16_decode)
 * Ghidra: ulong FUN_0047edf4(void)
 * Decodes a UTF-16 scalar: reads two 16-bit words and, if they form a
 * surrogate pair, combines them; returns {scalar, 0x100000000 flag}.
 * Confidence: medium.
 * Notes: FUN_002be300/002be23c/002be12c utf16 read; FUN_00343c20 finalize. */
uint64_t sk_r28_0047edf4(void)
{
    uint64_t x3 = 0;
    uint8_t st[104];
    sk_x_002be300();
    sk_x_002be23c(st);
    sk_x_003a25d4(x3);
    uint64_t v1 = sk_x_002be12c();
    uint64_t v2;
    if ((v1 & 0xff00000000) == 0x100000000) {
        sk_x_00343c20(st);
    } else {
        v2 = sk_x_002be12c();
        sk_x_00343c20(st);
        if ((v2 & 0xff00000000) == 0x100000000) {
            v2 = 0; v1 = 0;
            return 0x100000000;
        }
    }
    return 0x100000000;
}

/* FUN_0047ee98 @ 0x0047ee98   (est. sk_r28_utf8_decode_c)
 * Ghidra: ulong FUN_0047ee98(void)
 * Decodes the next scalar from a UTF-8 string, handling the inline-copy
 * storage form; returns {scalar, 0x100000000 flag}. Traps if the buffer is
 * exhausted. Confidence: low.
 * Notes: SoftwareBreakpoint(1,0x47ef1c); unaff_x20. */
uint64_t sk_r28_0047ee98(void)
{
    uint64_t x1 = 0, x8 = 0, x9 = 0;   /* extraout registers */
    uint64_t x20 = 0;                  /* unaff_x20 */
    bool ZR = false;
    sk_x_003532b8();
    int64_t len = x8;
    if (!ZR) len = x9;
    if (len != 0) {
        sk_x_003504d0();
        sk_x_00350624(0xf);
        uint64_t v = sk_x_001b798c();
        if (v >> 0xe == (uint64_t)len * 4) {
            sk_x_0007c1c4();
            sk_x_001aea6c();
            if (x1 == 0)
                SoftwareBreakpoint(1, 0x47ef1c);
            sk_r28_0047edf4();
            sk_x_00351d18();
            sk_x_003a25d4();
            return (x20 & 0xffffffff) | 0x100000000;
        }
    }
    return 0x100000000;
}

/* FUN_0047ef1c @ 0x0047ef1c   (est. sk_r28_utf8_decode)
 * Ghidra: ulong FUN_0047ef1c(void)
 * Decodes the next scalar from a UTF-8 string, handling both inline and
 * indirect buffer storage, with continuation-byte assembly; returns
 * {scalar, 0x100000000 flag}. Confidence: low.
 * Notes: SoftwareBreakpoint(1,0x47efb8); unaff_x19/x20. */
uint64_t sk_r28_0047ef1c(void)
{
    uint64_t x8 = 0, x9 = 0, x8_00 = 0, x8_01 = 0, x8_02 = 0;
    uint64_t x19 = 0, x20 = 0;         /* unaff_x19/x20 */
    bool ZR = false;
    sk_x_003532b8();
    int64_t len = x8;
    if (!ZR) len = x9;
    if (len == 0)
        return 0x100000000;
    sk_x_003504d0();
    sk_x_00350624(0xf);
    uint64_t v = sk_x_00167404();
    uint64_t r;
    if ((x19 >> 0x3c & 1) == 0) {
        v = v >> 0x10;
        int64_t base;
        if ((x19 >> 0x3d & 1) == 0) {
            if ((x20 >> 0x3c & 1) == 0) { sk_x_0007c1c4(); base = sk_x_002a9ba8(); }
            else base = sk_x_00356364();
        } else {
            sk_x_004aad94();
            base = x8_01;
        }
        uint8_t b = *(uint8_t *)(base + v);
        sk_x_0034b3f8(b);
        r = (v + x8_02) * 0x10000;
    } else {
        sk_x_00350624();
        r = sk_x_002a49a8();
    }
    if (x8_00 * 4 - (r >> 0xe) == 0) {
        sk_x_0007c1c4();
        r = sk_x_001ae8a8();
        if ((r & 0xff00000000) == 0x100000000)
            SoftwareBreakpoint(1, 0x47efb8);
        return r & 0xff00000000 | r & 0xffffffff;
    }
    return 0x100000000;
}

/* FUN_0047eff4 @ 0x0047eff4   (est. sk_r28_script_rawvalue)
 * Ghidra: undefined8 FUN_0047eff4(void)
 * Emits the "Unknown script rawValue" diagnostic: prints the message and
 * calls the rawValue getter, then returns the read scalar. Confidence: medium.
 * Notes: string s_Unknown_script_rawValue__005e2ef0; FUN_00027724 getter. */
uint64_t sk_r28_0047eff4()
{
    uint64_t x8 = 0;
    uint64_t r = sk_x_004ace08();
    sk_x_000b430c();
    sk_x_002a4ab4(0x1b);
    sk_x_003a25d4(0);
    sk_x_00086840((uint64_t)"s_Unknown_script_rawValue__005e2ef0");
    uint64_t (*fn)() = (void*)sk_x_00027724(0x670738);
    (*fn)(&sk_g_006775b0, 0x670738);
    sk_x_004ac0cc();
    sk_x_003a25d4(0x670738);
    sk_x_003a25d4(x8);
    return r;
}

/* FUN_0047f0a8 @ 0x0047f0a8   (est. sk_r28_capture_copy)
 * Ghidra: void FUN_0047f0a8(void)
 * Copies a captured byte sequence into a fresh buffer: reads the source via
 * FUN_00357cb4, allocates a tag object (0x21 bytes, kind 7) if the source is
 * a scalar, otherwise copies the byte run into an array (growing as needed).
 * Confidence: low.
 * Notes: unaff_x19 = dest; SK_CANARY stack check; DAT_00657e20. */
void sk_r28_0047f0a8(void)
{
    uint64_t x_bae8 = 0, x_beb0 = 0;   /* uRam 0x4baeb8 / _DAT_004baeb0 */
    sk_pair_t au = sk_x_00357cb4();
    int64_t canary = SK_CANARY;
    uint8_t tag = 0;
    uint8_t *src = (uint8_t *)sk_x_004ace88(au.lo, &tag);
    uint64_t dst;
    if (src == 0) {
        uint64_t u4 = sk_x_00002534(&sk_g_00657e20, &sk_g_005a5530).lo;
        dst = sk_x_0036a940(u4, 0x21, 7);
        *(uint64_t *)(dst + 0x18) = x_bae8;
        *(uint64_t *)(dst + 0x10) = x_beb0;
        *(uint8_t *)(dst + 0x20) = sk_r28_0047eff4(au.lo);
    } else {
        uint64_t n = (uint64_t)tag;
        if (n == 0) {
            sk_x_000a6fe0();
            dst = 0;
        } else {
            sk_x_004ac27c();
            dst = sk_x_00499468();
            do {
                uint8_t b = *src;
                uint64_t c = *(uint64_t *)(dst + 0x10);
                if (*(uint64_t *)(dst + 0x18) >> 1 <= c) {
                    uint64_t u4 = sk_x_0006b42c();
                    sk_x_00350774(u4, c + 1);
                    dst = sk_x_00499468();
                }
                *(uint64_t *)(dst + 0x10) = c + 1;
                *(uint8_t *)(dst + c + 0x20) = b;
                n = n - 1;
                src = src + 1;
            } while (n != 0);
        }
    }
    if (canary != SK_CANARY)
        sk_x_0011d7e8();
    sk_x_00357c74(dst, au.hi);
}
/* FUN_0047f1b4 @ 0x0047f1b4   (est. sk_r28_prop_test_b)
 * Ghidra: void FUN_0047f1b4(undefined8,undefined8)
 * Calls the general-category getter FUN_002bc5bc and forwards its result to a
 * shared test helper. Confidence: medium. */
void sk_r28_0047f1b4(uint64_t a1, uint64_t a2)
{
    uint64_t u = sk_x_002bc5bc();
    sk_x_000abbdc(u, a2);
}

/* FUN_0047f1e0 @ 0x0047f1e0   (est. sk_r28_prop_test_ci)
 * Ghidra: undefined8 FUN_0047f1e0(undefined8)
 * Tests property bit 18 (FUN_002bc058); if set returns the result of the
 * scalar case-fold helper FUN_002bbf24, else 0. Confidence: medium. */
uint64_t sk_r28_0047f1e0(uint64_t a1)
{
    uint64_t u = sk_x_002bc058();
    if ((u & 1) != 0)
        return sk_x_002bbf24(a1);
    return 0;
}

/* FUN_0047f448 @ 0x0047f448   (est. sk_r28_prop_test_d)
 * Ghidra: bool FUN_0047f448(undefined8)
 * If property bit 7 (FUN_002bbf08) is set returns true; else runs a
 * decompose pass and returns the negated carry flag. Confidence: medium. */
bool sk_r28_0047f448(uint64_t a1)
{
    bool ZR = false;
    uint64_t u = sk_x_002bbf08();
    if ((u & 1) == 0) {
        sk_x_002bd724(a1);
        sk_x_0046511c();
        return !ZR;
    }
    return true;
}

/* FUN_0047f488 @ 0x0047f488   (est. sk_r28_prop_test_e)
 * Ghidra: bool FUN_0047f488(undefined8)
 * True unless property bit 37 (FUN_002bc234) is clear AND the general
 * category is one of 0x19/0x1b/0x1d (punctuation classes). Confidence: medium. */
bool sk_r28_0047f488(uint64_t a1)
{
    uint64_t u = sk_x_002bc234();
    if ((u & 1) == 0) {
        char c = (char)sk_x_002bc5bc(a1);
        if (c != 0x19) {
            c = (char)sk_x_002bc5bc(a1);
            if (c != 0x1b) {
                c = (char)sk_x_002bc5bc(a1);
                return c != 0x1d;
            }
        }
    }
    return false;
}

/* FUN_0047f4f4 @ 0x0047f4f4   (est. sk_r28_prop_test_f)
 * Ghidra: bool FUN_0047f4f4(void)
 * Returns whether the general category is not 0x19. Confidence: medium. */
bool sk_r28_0047f4f4(void)
{
    return (char)sk_x_002bc5bc() != 0x19;
}

/* FUN_0047f4f8 @ 0x0047f4f8   (est. sk_r28_prop_test_f2)
 * Ghidra: bool FUN_0047f4f8(void)
 * Identical to 0047f4f4. Confidence: medium. */
bool sk_r28_0047f4f8(void)
{
    return (char)sk_x_002bc5bc() != 0x19;
}

/* FUN_0047f518 @ 0x0047f518   (est. sk_r28_prop_test_g)
 * Ghidra: undefined8 FUN_0047f518(undefined8)
 * If property bit 7 clear, runs a decompose pass and, if both flags set and
 * property bit 24 (FUN_002bc100) clear, returns the scalar-mapping helper
 * result; otherwise returns 1. Confidence: medium. */
uint64_t sk_r28_0047f518(uint64_t a1)
{
    bool ZR = false;
    uint64_t u = sk_x_002bbf08();
    if ((u & 1) == 0) {
        sk_x_002bd724(a1);
        sk_x_0046511c();
        if (ZR) {
            u = sk_x_002bc100(a1);
            if ((u & 1) == 0)
                return sk_x_002bbf78(a1);
        }
    }
    return 1;
}

/* FUN_0047f580 @ 0x0047f580   (est. sk_r28_prop_ret)
 * Ghidra: undefined1 FUN_0047f580(undefined4,undefined8)
 * Reads a 32-bit word through the property iterator, runs a predicate, and
 * returns the 1-byte predicate result. Confidence: medium.
 * Notes: thunk_FUN_0024d9ac iterator; FUN_0024917c predicate. */
uint8_t sk_r28_0047f580(uint32_t a1, uint64_t a2)
{
    uint64_t it = sk_x_0024d9ac(a2);
    uint32_t w = a1;
    uint8_t out;
    sk_x_0024917c(&out, &w);
    sk_x_0036b118(it);
    return out;
}

/* FUN_0047f5d0 @ 0x0047f5d0   (est. sk_r28_err_build)
 * Ghidra: void FUN_0047f5d0(void)
 * Builds an error object: reads a message tag (DAT_00688638), allocates an
 * error context, stores the two self words, refs them and commits.
 * Confidence: medium. Notes: unaff_x19/x20 = self words. */
void sk_r28_0047f5d0(void)
{
    uint64_t x19 = 0, x20 = 0;         /* unaff_x19/x20 = self words */
    sk_x_003504d0();
    sk_x_00002834((uint64_t)&sk_g_00688638);
    int64_t e = sk_x_0036a940();
    *(uint64_t *)(e + 0x10) = x20;
    *(uint64_t *)(e + 0x18) = x19;
    sk_x_0036b270();
    sk_x_0006b6f4();
}

/* FUN_0047f630 @ 0x0047f630   (est. sk_r28_utf8_decode_err)
 * Ghidra: void FUN_0047f630(undefined8,undefined8,undefined8)
 * Decodes the next scalar from a UTF-8 string and appends it to a string
 * builder, handling 1/2/3-byte continuations; emits a type-conversion report
 * on the decoded scalar. Confidence: low.
 * Notes: register-heavy (unaff_x19/x21); FUN_0034b3f8 scalar accumulate. */
void sk_r28_0047f630(uint64_t a1, uint64_t a2, uint64_t a3)
{
    uint64_t x16 = 0, x16_00 = 0, x8 = 0, x9 = 0;
    uint64_t x19 = 0, x21 = 0;
    uint8_t stack[0x80];
    sk_x_0008409c();
    sk_x_003504a0(a3);
    uint64_t v = sk_x_00167404();
    if ((x19 >> 0x3c & 1) != 0) {
        sk_x_003504a0(v & 0xffffffffffff0000);
        sk_x_002a49a8();
        goto done;
    }
    if ((x19 >> 0x3d & 1) == 0) {
        int64_t base;
        if ((x21 >> 0x3c & 1) == 0) { sk_x_00084180(); base = sk_x_002a9ba8(); }
        else base = sk_x_00356364();
        sk_x_004abbb8(base + (v >> 0x10));
        if (x9 >= 0) goto done;
        sk_x_003527b8();
        switch (x16) {
        case 1:
            sk_x_00353ff4();
            break;
        case 2:
            sk_x_00352e9c();
            break;
        case 3:
            sk_x_0034c6d4();
            sk_x_004abfc8();
            break;
        }
    } else {
        sk_x_004abbb8((uint64_t)stack + (v >> 0x10));
        if (x9 >= 0) goto done;
        sk_x_003527b8();
        switch (x16_00) {
        case 1: sk_x_00353ff4(); break;
        case 2: sk_x_00352e9c(); break;
        case 3: sk_x_0034c6d4(); sk_x_004abfc8(); break;
        }
    }
done:
    uint64_t it = sk_x_0024d9ac(&sk_g_005a4c30);
    uint8_t tag;
    sk_x_0024917c(&tag, &stack);
    sk_x_0036b118(it);
    if (tag == 0x01) {
        sk_x_00100efc();
        uint64_t v2 = sk_x_00167404();
        if ((x19 >> 0x3c & 1) == 0) {
            uint64_t off = v2 >> 0x10;
            int64_t base;
            if ((x19 >> 0x3d & 1) == 0) {
                if ((x21 >> 0x3c & 1) == 0) { sk_x_00084180(); base = sk_x_002a9ba8(); }
                else base = sk_x_00356364();
            } else {
                base = (int64_t)stack;
            }
            uint8_t b = *(uint8_t *)(base + off);
            sk_x_0034b3f8(b, 0, 0);
            sk_x_004abd2c(off + x8);
        } else {
            sk_x_003504a0();
            sk_x_002a49a8();
        }
    } else {
        sk_x_00068e14();
    }
}

/* FUN_0047f808 @ 0x0047f808   (est. sk_r28_err_build2)
 * Ghidra: void FUN_0047f808(void)
 * Error-object builder variant of 0047f5d0 with tag DAT_00688690.
 * Confidence: medium. Notes: unaff_x19/x20 = self words. */
void sk_r28_0047f808(void)
{
    uint64_t x19 = 0, x20 = 0;         /* unaff_x19/x20 = self words */
    sk_x_003504d0();
    sk_x_00002834((uint64_t)&sk_g_00688660);
    int64_t e = sk_x_0036a940();
    *(uint64_t *)(e + 0x10) = x20;
    *(uint64_t *)(e + 0x18) = x19;
    sk_x_0036b270();
    sk_x_0006b6f4();
}

/* FUN_0047f868 @ 0x0047f868   (est. sk_r28_utf8_decode_err2)
 * Ghidra: void FUN_0047f868(undefined8,undefined8,undefined8)
 * UTF-8 scalar decode variant that builds a string from the decoded scalar,
 * handling an ASCII literal fast path. Confidence: low.
 * Notes: unaff_x30; SoftwareBreakpoint(1,0x47f944). */
void sk_r28_0047f868(uint64_t a1, uint64_t a2, uint64_t a3)
{
    uint64_t x30 = 0;                  /* unaff_x30 */
    bool ZR = false;
    sk_x_00357cb4();
    sk_x_0035056c(a3);
    sk_x_00267510();
    uint64_t v = sk_x_00417aa0();
    sk_x_003a25d4(0);
    sk_pair_t r;
    if ((v & 1) != 0) {
        sk_pair_t av = sk_x_000b4390();
        sk_x_00267510(av.lo, av.hi, 0);
        v = sk_x_001ae8a8();
        sk_x_003a25d4(0);
        sk_x_004ab11c(v & 0xff00000000);
        if (ZR)
            SoftwareBreakpoint(1, 0x47f944);
        uint64_t it = sk_x_0024d9ac(&sk_g_005a4c30);
        uint32_t w = (uint32_t)v;
        uint8_t tag;
        sk_x_0024917c(&tag, &w);
        sk_x_0036b118(it);
        if (tag == 0x01) {
            sk_pair_t av2 = sk_x_000b4390();
            v = sk_x_001b798c(av2.lo, av2.hi, 0);
            r = (sk_pair_t){ v, 0 };
        } else {
            r = (sk_pair_t){ sk_x_00068e14(), 0 };
        }
    } else {
        r = (sk_pair_t){ sk_x_00068e14(), 0 };
    }
    sk_x_00357c74(r.lo, r.hi, x30);
}

/* FUN_0047f944 @ 0x0047f944   (est. sk_r28_dispatch_guard)
 * Ghidra: void FUN_0047f944(undefined8 x 7)
 * Dispatch guard: invokes param_5 (a function pointer) and, if the carry
 * flag is set, applies a flag transform and advances the scalar; else
 * reports failure. Confidence: low.
 * Notes: SoftwareBreakpoint(1,0x47f9c4). */
void sk_r28_0047f944(uint64_t a1, uint64_t a2, uint64_t a3, uint64_t a4,
                     uint64_t fn, uint64_t a6, int64_t a7)
{
    bool ZR = false;
    sk_x_0008409c();
    (*(void (*)(void))fn)();
    sk_x_00351db4();
    if (ZR) {
        if (*(int64_t *)(a7 + 0x10) == 0)
            SoftwareBreakpoint(1, 0x47f9c4);
        sk_x_0035063c(a3, (*(uint32_t *)(a7 + *(int64_t *)(a7 + 0x10) * 4 + 0x1c) & 0x10000) == 0);
        sk_r28_0047ed40();
    } else {
        sk_x_00068e14();
    }
}

/* FUN_0047f9c4 @ 0x0047f9c4   (est. sk_r28_forward)
 * Ghidra: void FUN_0047f9c4(undefined8,undefined8,undefined8)
 * Forwarding thunk: calls the shared advance helper with (a3, a1, a2).
 * Confidence: medium. */
void sk_r28_0047f9c4(uint64_t a1, uint64_t a2, uint64_t a3)
{
    sk_x_001b798c(a3, a1, a2);
}

/* FUN_0047f9c8 @ 0x0047f9c8   (est. sk_r28_forward2)
 * Ghidra: void FUN_0047f9c8(undefined8,undefined8,undefined8)
 * Identical forwarding thunk to 0047f9c4. Confidence: medium. */
void sk_r28_0047f9c8(uint64_t a1, uint64_t a2, uint64_t a3)
{
    sk_x_001b798c(a3, a1, a2);
}

/* FUN_0047f9f0 @ 0x0047f9f0   (est. sk_r28_prop_test_h)
 * Ghidra: bool FUN_0047f9f0(void)
 * Returns whether the general category is not 0x1d. Confidence: medium. */
bool sk_r28_0047f9f0(void)
{
    return (char)sk_x_002bc5bc() != 0x1d;
}

/* FUN_0047f9f4 @ 0x0047f9f4   (est. sk_r28_prop_test_h2)
 * Ghidra: bool FUN_0047f9f4(void)
 * Identical to 0047f9f0. Confidence: medium. */
bool sk_r28_0047f9f4(void)
{
    return (char)sk_x_002bc5bc() != 0x1d;
}

/* FUN_0047fa44 @ 0x0047fa44   (est. sk_r28_err_code)
 * Ghidra: void FUN_0047fa44(long)
 * L4 error-code → Swift error-object factory: reads the error code from the
 * box at param+0x10 and maps it (0..0x25) to the matching error message
 * string and constructor, allocating an error context object and dispatching.
 * Confidence: high (strings "L4_ErrorCode*" match the error enum).
 * Notes: DAT_006884xx string table; FUN_0036a940 alloc; SWBP-free. */
void sk_r28_0047fa44(int64_t box)
{
    uint64_t x1 = 0;                   /* extraout_x1: error code */
    uint64_t x16 = 0;                  /* extraout_x16 */
    uint8_t code_byte = (uint8_t)(x1 & 0xff);  /* packed error code */
    bool ZR = false;
    if (*(int64_t *)(box + 0x10) == 0)
        SoftwareBreakpoint(1, 0x480160);
    sk_x_004aa734(*(uint32_t *)(box + *(int64_t *)(box + 0x10) * 4 + 0x1c));
    uint64_t (*fn)() = (void*)sk_r28_0047f5d0;
    if (!ZR) fn = (void*)x16;
    uint64_t tag, ctor;
    switch (code_byte) {
    case 1: ctor = 0x004aa204; tag = 0x006884d0; sk_x_004ab1fc(&sk_g_006884d0); break;
    case 2: ctor = 0x004aa204; tag = 0x00688498; break;
    case 3: ctor = 0x004aa204; tag = 0x00688478; break;
    case 4: ctor = 0x004aa204; tag = 0x00688458; break;
    case 5: ctor = 0x004aa204; tag = 0x00688430; break;
    case 6: ctor = 0x004aa240; tag = 0x006885f8; break;
    case 7: ctor = 0x004a3f30; tag = 0x006884d8; break;
    case 8: ctor = 0x004aa204; tag = 0x006883f8; break;
    case 9: ctor = 0x004aa204; tag = 0x006883d8; break;
    case 10: ctor = 0x004aa204; tag = 0x006883b8; break;
    case 11: ctor = 0x004aa204; tag = 0x00688390; break;
    case 12: ctor = 0x004aa204; tag = 0x00688368; break;
    case 13: ctor = 0x004aa240; tag = 0x006885d8; break;
    case 14: ctor = 0x004aa204; tag = 0x00688338; break;
    case 15: ctor = 0x004aa204; tag = 0x00688318; break;
    case 16: ctor = 0x004aa204; tag = 0x006882d8; break;
    case 17: ctor = 0x004aa240; tag = 0x00688598; break;
    case 18: ctor = 0x004aa204; tag = 0x006882b8; break;
    case 19: ctor = 0x004aa204; tag = 0x00688298; break;
    case 20: ctor = 0x004aa204; tag = 0x00688278; break;
    case 21: ctor = 0x004aa240; tag = 0x00688558; break;
    case 22: ctor = 0x004aa204; tag = 0x00688250; break;
    case 23: ctor = 0x004aa204; tag = 0x00688218; break;
    case 24: ctor = 0x004aa204; tag = 0x00688200; break;
    case 25: ctor = 0x004aa204; tag = 0x006881d8; break;
    case 26: ctor = 0x004aa204; tag = 0x006881b0; break;
    case 27: ctor = 0x004aa204; tag = 0x00688188; break;
    case 28: ctor = 0x004aa204; tag = 0x00688160; break;
    case 29: ctor = 0x004aa240; tag = 0x00688578; break;
    case 30: ctor = 0x004aa204; tag = 0x00688138; break;
    case 31: ctor = 0x004aa204; tag = 0x00688110; break;
    case 32: ctor = 0x004aa204; tag = 0x006880e8; break;
    case 33: ctor = 0x004aa204; tag = 0x006880c0; break;
    case 34: ctor = 0x004aa240; tag = 0x00688538; break;
    case 35: ctor = 0x004aa204; tag = 0x00688098; break;
    case 36: ctor = 0x004aa204; tag = 0x00688070; break;
    case 37: ctor = 0x004aa204; tag = 0x00688048; break;
    default: ctor = 0x004aa240; tag = 0x00688510; break;
    }
    int64_t err = sk_x_0036a940();
    *(uint8_t *)(err + 0x10) = code_byte;
    (*fn)(ctor, tag);
    sk_x_00354f1c();
    sk_x_0036b118(tag);
    sk_x_00351450();
}

/* FUN_004801f8 @ 0x004801f8   (est. sk_r28_regex_err2)
 * Ghidra: void FUN_004801f8(long)
 * Regex/Unicode error-code factory: maps the error code from the box to the
 * matching property-test / TODO-report path (categories with dedicated
 * messages), else emits the "TODO: map <code>" report. Confidence: low.
 * Notes: SoftwareBreakpoint(1,0x480758); DAT_0047f2xx fn-ptr table. */
void sk_r28_004801f8(int64_t box)
{
    uint64_t x1 = 0;                   /* extraout_x1: error code */
    uint64_t x16 = 0;                  /* extraout_x16 */
    uint8_t code_byte = (uint8_t)(x1 & 0xff);  /* packed error code */
    uint8_t tag = 0;
    uint64_t outbox[4] = {0};
    bool ZR = false;
    if (*(int64_t *)(box + 0x10) == 0)
        SoftwareBreakpoint(1, 0x480758);
    sk_x_004aa734(*(uint32_t *)(box + *(int64_t *)(box + 0x10) * 4 + 0x1c));
    uint64_t (*fn)() = (void*)sk_r28_0047f5d0;
    if (!ZR) fn = (void*)x16;
    uint64_t target = (uint64_t)sk_r28_0047f1e0;
    switch (code_byte) {
    case 1: target = 0x0047f220; break;
    case 2: target = 0x0047f22c; break;
    case 3: target = 0x0047f238; break;
    case 4: target = 0x0047f244; break;
    case 6: target = 0x0047f250; break;
    case 7: target = 0x0047f25c; break;
    case 8: target = 0x0047f268; break;
    case 9: target = 0x0047f274; break;
    case 10: target = 0x0047f280; break;
    case 11: target = 0x0047f28c; break;
    case 12: target = 0x0047f298; break;
    case 13: target = 0x0047f2a4; break;
    case 14: target = 0x0047f2b0; break;
    case 15: target = 0x0047f2bc; break;
    case 16: target = 0x0047f2c8; break;
    case 17: target = 0x0047f2d4; break;
    case 19: target = 0x0047f2e0; break;
    case 20: target = 0x0047f2ec; break;
    case 21: target = 0x0047f2f8; break;
    case 22: target = 0x0047f304; break;
    case 24: target = 0x0047f310; break;
    case 25: target = 0x0047f31c; break;
    case 26: target = 0x0047f328; break;
    case 28: target = 0x004aa2c4; break;
    case 30: target = 0x0047f334; break;
    case 31: target = 0x0047f340; break;
    case 32: target = 0x0047f34c; break;
    case 33: target = 0x0047f358; break;
    case 34: target = 0x0047f364; break;
    case 35: target = 0x0047f370; break;
    case 36: target = 0x0047f37c; break;
    case 37: target = 0x0047f388; break;
    case 38: target = 0x0047f394; break;
    case 39: target = 0x0047f3a0; break;
    case 48: target = 0x0047f3ac; break;
    case 49: target = 0x0047f3b8; break;
    case 51: target = 0x0047f3c4; break;
    case 52: target = 0x0047f3d0; break;
    case 53: target = 0x00480ff0; break;
    case 54: target = 0x0047f3dc; break;
    case 55: target = 0x0047f3e8; break;
    case 56: target = 0x0047f3f4; break;
    case 57: target = 0x0047f400; break;
    case 58: target = 0x0047f40c; break;
    case 59: target = 0x0047f418; break;
    case 60: target = 0x0047f424; break;
    case 61: target = 0x0047f430; break;
    case 62: target = 0x0047f43c; break;
    case 5:
    case 18:
    case 23:
    case 27:
    case 29:
    case 40:
    case 41:
    case 42:
    case 43:
    case 44:
    case 45:
    case 46:
    case 47:
    case 50:
        sk_x_00100c04((uint64_t)sk_r28_0047f1e0);
        sk_x_002a4ab4(0x11);
        sk_pair_t av = sk_x_002acbb8(0x616d203a4f444f54, 0xef20706f72702070);
        sk_x_000f4a9c(av.lo, av.hi, 0x685848);
        sk_x_00205844(&tag, &outbox);
        sk_x_004ab6b8(outbox[0], outbox[1]);
        sk_x_004ab6ac(outbox);
        goto emit;
    case 63:
    case 64:
    case 65:
    case 66:
        sk_x_00100c04((uint64_t)sk_r28_0047f1e0);
        sk_x_002a4ab4(0x16);
        sk_x_004ac348((uint64_t)"s_Unicode_deprecated__005e2ed0");
        sk_pair_t av2 = sk_x_002acbb8();
        sk_x_000f4a9c(av2.lo, av2.hi, 0x685848);
        sk_x_00205844(&tag, &outbox);
        sk_x_004ab6b8(outbox[0], outbox[1]);
        sk_x_004ab6ac(outbox);
emit:
        sk_x_0044f818();
        sk_x_004aa370();
        sk_x_004aaf9c();
        sk_x_004abe68();
        return;
    default:
        break;
    }
    (*fn)(target, 0);
}

/* FUN_00480864 @ 0x00480864   (est. sk_r28_regex_kind)
 * Ghidra: void FUN_00480864(long,ulong)
 * Regex kind lookup: reads the kind code from the box and, when the box has
 * pending work, forwards it through the property test and error builder.
 * Confidence: medium. Notes: SoftwareBreakpoint(1,0x4808d0). */
void sk_r28_00480864(int64_t box, uint64_t a2)
{
    uint64_t x16 = 0;                  /* extraout_x16 */
    bool ZR = false;
    if (*(int64_t *)(box + 0x10) != 0) {
        uint64_t u = sk_x_004aa734(*(uint32_t *)(box + *(int64_t *)(box + 0x10) * 4 + 0x1c),
                                   *(uint64_t *)(&sk_g_006898b0 + (a2 & 0xff) * 8));
        uint64_t (*fn)() = (void*)sk_r28_0047f5d0;
        if (!ZR) fn = (void*)x16;
        (*fn)(u, 0);
        return;
    }
    SoftwareBreakpoint(1, 0x4808d0);
}
/* FUN_004811b4 @ 0x004811b4   (est. sk_r28_prop_test_j)
 * Ghidra: bool FUN_004811b4(int)
 * True if the general category (FUN_002bc5bc) is 0x16 (number) or the arg
 * equals 9. Confidence: medium. */
bool sk_r28_004811b4(int a1)
{
    char c = (char)sk_x_002bc5bc();
    return c == 0x16 || a1 == 9;
}

/* FUN_004811e8 @ 0x004811e8   (est. sk_r28_string_advance)
 * Ghidra: void FUN_004811e8(ulong,ulong)
 * String iterator advance: moves the cursor (self+0x18/+0x20) forward by one
 * scalar, handling the direct / table-indirect storage forms, and updates the
 * position + completion flag. Traps on invalid advance. Confidence: low.
 * Notes: unaff_x20 = self; SoftwareBreakpoint(1,0x481320). */
void sk_r28_004811e8(uint64_t a1, uint64_t a2)
{
    uint64_t self = 0;                 /* unaff_x20 */
    uint64_t x8 = 0;                   /* extraout_x8 */
    uint8_t stack0[8];                 /* inline scalar storage */
    bool u4 = false;
    if (*(char *)(self + 0x28) == 0x01)
        SoftwareBreakpoint(1, 0x481320);
    uint64_t cur = *(uint64_t *)(self + 0x18);
    *(uint64_t *)(self + 8) = *(uint64_t *)(self + 0x20);
    *(uint8_t *)(self + 0x10) = 0;
    uint64_t npos;
    if (cur >> 0xe == *(uint64_t *)(self + 0x20) >> 0xe) {
        npos = 0; cur = 0;
        *(uint64_t *)(self + 0x18) = cur;
        *(uint64_t *)(self + 0x20) = npos;
        *(uint8_t *)(self + 0x28) = 1;
        return;
    }
    if (*(char *)(self + 0x29) == 0x01) {
        sk_x_003504a0();
        npos = sk_x_002ab130();
        if ((int64_t)npos < 0x4000)
            SoftwareBreakpoint(1, 0x4812f8);
        int64_t base;
        if ((a2 >> 0x3c & 1) == 0) {
            if ((a2 >> 0x3d & 1) == 0) {
                if ((a1 >> 0x3c & 1) == 0) { sk_x_00084180(); base = sk_x_002a9ba8(); }
                else base = (a2 & 0xfffffffffffffff) + 0x20;
                sk_x_004ab054(base, npos);
                if (npos != 0x4000 && (int64_t)npos < 0x4000) goto skip;
                do { sk_x_00356930(); } while (0);
skip:
                npos = sk_x_004abf00(x8);
            } else {
                sk_x_004ab054(&stack0);
                npos = sk_x_004abf00(x8);
            }
        } else {
            sk_x_003504a0();
            npos = sk_x_002ae098();
        }
    } else {
        sk_x_003504a0();
        npos = sk_x_0029c058();
    }
    if (npos >> 0xe < cur >> 0xe)
        SoftwareBreakpoint(1, 0x4812f4);
    *(uint64_t *)(self + 0x18) = cur;
    *(uint64_t *)(self + 0x20) = npos;
    *(uint8_t *)(self + 0x28) = 0;
}

/* FUN_00481320 @ 0x00481320   (est. sk_r28_mask_bits)
 * Ghidra: ulong FUN_00481320(uint)
 * Packs a 32-bit arg's low byte plus two flag bits into a 64-bit value: if
 * (arg & 0xff00) == 0x100 sets bit 53, else 0; ORs in bit 54 from (arg>>16)&1
 * and bit 55 from (arg>>24)&1. Confidence: high (pure bit field combiner). */
uint64_t sk_r28_00481320(uint32_t a1)
{
    uint64_t v = 0x20000000000000;
    if ((a1 & 0xff00) != 0x100)
        v = 0;
    return v | (a1 & 0xff) | (uint64_t)((a1 & 0x10000) >> 0x10) << 0x36 |
           (uint64_t)((a1 & 0x1000000) >> 0x18) << 0x37;
}

/* FUN_00481354 @ 0x00481354   (est. sk_r28_shift_mask)
 * Ghidra: undefined4 FUN_00481354(ulong)
 * Selects a byte from the constant 0x304020100 by (arg & 7)<<3, clamped to 4
 * when arg > 4. Confidence: high. */
uint32_t sk_r28_00481354(uint64_t a1)
{
    uint32_t v = (uint32_t)(0x304020100 >> ((a1 & 7) << 3));
    if (4 < a1) v = 4;
    return v;
}

/* FUN_00481378 @ 0x00481378   (est. sk_r28_table_get)
 * Ghidra: undefined8 FUN_00481378(ulong)
 * Returns table entry DAT_005a5e90[(arg & 0xff) * 8]. Confidence: high. */
uint64_t sk_r28_00481378(uint64_t a1)
{
    return *(uint64_t *)(&sk_g_005a5e90 + (a1 & 0xff) * 8);
}

/* FUN_00481394 @ 0x00481394   (est. sk_r28_table_wait)
 * Ghidra: void FUN_00481394(ulong)
 * Hashes the table entry for (arg & 0xff) then waits/syncs on it.
 * Confidence: medium. Notes: FUN_001a84f4/001a8564 hash pair. */
void sk_r28_00481394(uint64_t a1)
{
    uint8_t st[72];
    sk_x_001a84f4(st, 0);
    sk_x_002298d4(*(uint64_t *)(&sk_g_005a5e90 + (a1 & 0xff) * 8));
    sk_x_001a8564();
}

/* FUN_004813f0 @ 0x004813f0   (est. sk_r28_wait_byte)
 * Ghidra: void FUN_004813f0(undefined8,undefined1)
 * Waits/syncs on the byte arg via the vspace sync helper. Confidence: medium. */
void sk_r28_004813f0(uint64_t a1, uint8_t a2)
{
    sk_x_002298d4(a2);
}

/* FUN_00481418 @ 0x00481418   (est. sk_r28_table_wait2)
 * Ghidra: void FUN_00481418(undefined8,ulong)
 * Waits/syncs on the table entry DAT_005a5e90[(arg & 0xff)*8].
 * Confidence: medium. */
void sk_r28_00481418(uint64_t a1, uint64_t a2)
{
    sk_x_002298d4(*(uint64_t *)(&sk_g_005a5e90 + (a2 & 0xff) * 8));
}

/* FUN_0048144c @ 0x0048144c   (est. sk_r28_wait2)
 * Ghidra: void FUN_0048144c(undefined8,undefined8)
 * Waits/syncs on arg2. Confidence: medium. */
void sk_r28_0048144c(uint64_t a1, uint64_t a2)
{
    sk_x_002298d4(a2);
}

/* FUN_0048147c @ 0x0048147c   (est. sk_r28_wait3)
 * Ghidra: void FUN_0048147c(undefined8,undefined8)
 * Hash-wrap: hashes a 72-byte frame then waits/syncs on arg2.
 * Confidence: medium. */
void sk_r28_0048147c(uint64_t a1, uint64_t a2)
{
    uint8_t st[72];
    sk_x_001a84f4(st);
    sk_x_002298d4(a2);
    sk_x_001a8564();
}

/* FUN_004814c0 @ 0x004814c0   (est. sk_r28_table_wait3)
 * Ghidra: void FUN_004814c0(undefined8,ulong)
 * Hash-wrap + wait/sync on table entry DAT_005a5e90[(arg & 0xff)*8].
 * Confidence: medium. */
void sk_r28_004814c0(uint64_t a1, uint64_t a2)
{
    uint8_t st[72];
    sk_x_001a84f4(st);
    sk_x_002298d4(*(uint64_t *)(&sk_g_005a5e90 + (a2 & 0xff) * 8));
    sk_x_001a8564();
}

/* FUN_00481510 @ 0x00481510   (est. sk_r28_wait4)
 * Ghidra: void FUN_00481510(undefined8,undefined1)
 * Hash-wrap + wait/sync on the byte arg. Confidence: medium. */
void sk_r28_00481510(uint64_t a1, uint8_t a2)
{
    uint8_t st[72];
    sk_x_001a84f4(st);
    sk_x_002298d4(a2);
    sk_x_001a8564();
}

/* FUN_00481554 @ 0x00481554   (est. sk_r28_store_byte)
 * Ghidra: void FUN_00481554(void)
 * Computes the shift-mask byte (FUN_00481354) and stores it through unaff_x19.
 * Confidence: medium. Notes: unaff_x19 = out slot. */
void sk_r28_00481554(void)
{
    uint8_t *x19 = 0;                  /* unaff_x19: out slot */
    sk_x_00351124();
    uint8_t v = (uint8_t)sk_r28_00481354(0);
    *x19 = v;
}

/* FUN_00481580 @ 0x00481580   (est. sk_r28_store_get)
 * Ghidra: void FUN_00481580(undefined8 *)
 * Reads the table entry for the byte at unaff_x20 and stores it into *out.
 * Confidence: medium. Notes: unaff_x20 = index byte. */
void sk_r28_00481580(uint64_t *out)
{
    uint8_t *x20 = 0;                  /* unaff_x20: index byte */
    uint64_t v = sk_r28_00481378(*x20);
    *out = v;
}

/* FUN_004815ac @ 0x004815ac   (est. sk_r28_index_calc)
 * Ghidra: long FUN_004815ac(ulong)
 * Computes an index: adds bits 19-26 and 27-34 of arg; returns -1 if bits
 * 18-26 equal 1, else the sum. Confidence: high (pure index computation). */
int64_t sk_r28_004815ac(uint64_t a1)
{
    int64_t v = (int64_t)((a1 >> 0x13 & 0xff) + (a1 >> 0x1b & 0xff));
    if ((a1 >> 0x12 & 0x1ff) == 1)
        v = -1;
    return v;
}

/* FUN_004815cc @ 0x004815cc   (est. sk_r28_lz_mask)
 * Ghidra: ulong FUN_004815cc(ulong)
 * Selects a byte from the packed constant 0x300020100 by bits 35-37 of arg,
 * but only if that 3-bit field is a valid index in {0..4}; otherwise traps.
 * Confidence: high. Notes: SoftwareBreakpoint(1,0x481600). */
uint64_t sk_r28_004815cc(uint64_t a1)
{
    uint64_t idx = a1 >> 0x23 & 7;
    if ((idx < 5) && ((0x17U >> idx & 1) != 0))
        return 0x300020100 >> (idx << 3);
    SoftwareBreakpoint(1, 0x481600);
    return 0;
}
/* FUN_0047fa14 @ 0x0047fa14   (est. sk_r28_prop_test_0047fa14)
 * Ghidra: void FUN_0047fa14(byte *out, undefined4 *scalar)
 * Calls the scalar property bit-tester sk_x_00254c7c (FUN_00254c7c) and
 * stores the low bit of its result into the caller's bool out-slot.
 * Confidence: medium (logic trivially faithful; property meaning owned by callee).
 * Notes: wrapper leaf; property identity is in FUN_00254c7c. */
void sk_r28_prop_test_0047fa14(uint8_t *out, uint32_t *scalar)
{
    uint8_t b = (uint8_t)sk_x_00254c7c(*scalar);
    *out = (uint8_t)(b & 1);
}

/* FUN_004808d0 @ 0x004808d0   (est. sk_r28_prop_test_004808d0)
 * Ghidra: void FUN_004808d0(byte *out, undefined4 *scalar)
 * Calls the scalar property bit-tester sk_x_002bbf08 (FUN_002bbf08) and
 * stores the low bit of its result into the caller's bool out-slot.
 * Confidence: medium (logic trivially faithful; property meaning owned by callee).
 * Notes: wrapper leaf; property identity is in FUN_002bbf08. */
void sk_r28_prop_test_004808d0(uint8_t *out, uint32_t *scalar)
{
    uint8_t b = (uint8_t)sk_x_002bbf08(*scalar);
    *out = (uint8_t)(b & 1);
}

/* FUN_00480900 @ 0x00480900   (est. sk_r28_prop_test_00480900)
 * Ghidra: void FUN_00480900(byte *out, undefined4 *scalar)
 * Calls the scalar property bit-tester sk_x_002bbf40 (FUN_002bbf40) and
 * stores the low bit of its result into the caller's bool out-slot.
 * Confidence: medium (logic trivially faithful; property meaning owned by callee).
 * Notes: wrapper leaf; property identity is in FUN_002bbf40. */
void sk_r28_prop_test_00480900(uint8_t *out, uint32_t *scalar)
{
    uint8_t b = (uint8_t)sk_x_002bbf40(*scalar);
    *out = (uint8_t)(b & 1);
}

/* FUN_00480930 @ 0x00480930   (est. sk_r28_prop_test_00480930)
 * Ghidra: void FUN_00480930(byte *out, undefined4 *scalar)
 * Calls the scalar property bit-tester sk_x_002bbf5c (FUN_002bbf5c) and
 * stores the low bit of its result into the caller's bool out-slot.
 * Confidence: medium (logic trivially faithful; property meaning owned by callee).
 * Notes: wrapper leaf; property identity is in FUN_002bbf5c. */
void sk_r28_prop_test_00480930(uint8_t *out, uint32_t *scalar)
{
    uint8_t b = (uint8_t)sk_x_002bbf5c(*scalar);
    *out = (uint8_t)(b & 1);
}

/* FUN_00480960 @ 0x00480960   (est. sk_r28_prop_test_00480960)
 * Ghidra: void FUN_00480960(byte *out, undefined4 *scalar)
 * Calls the scalar property bit-tester sk_x_002bc2f8 (FUN_002bc2f8) and
 * stores the low bit of its result into the caller's bool out-slot.
 * Confidence: medium (logic trivially faithful; property meaning owned by callee).
 * Notes: wrapper leaf; property identity is in FUN_002bc2f8. */
void sk_r28_prop_test_00480960(uint8_t *out, uint32_t *scalar)
{
    uint8_t b = (uint8_t)sk_x_002bc2f8(*scalar);
    *out = (uint8_t)(b & 1);
}

/* FUN_00480990 @ 0x00480990   (est. sk_r28_prop_test_00480990)
 * Ghidra: void FUN_00480990(byte *out, undefined4 *scalar)
 * Calls the scalar property bit-tester sk_x_002bc314 (FUN_002bc314) and
 * stores the low bit of its result into the caller's bool out-slot.
 * Confidence: medium (logic trivially faithful; property meaning owned by callee).
 * Notes: wrapper leaf; property identity is in FUN_002bc314. */
void sk_r28_prop_test_00480990(uint8_t *out, uint32_t *scalar)
{
    uint8_t b = (uint8_t)sk_x_002bc314(*scalar);
    *out = (uint8_t)(b & 1);
}

/* FUN_004809c0 @ 0x004809c0   (est. sk_r28_prop_test_004809c0)
 * Ghidra: void FUN_004809c0(byte *out, undefined4 *scalar)
 * Calls the scalar property bit-tester sk_x_002bc384 (FUN_002bc384) and
 * stores the low bit of its result into the caller's bool out-slot.
 * Confidence: medium (logic trivially faithful; property meaning owned by callee).
 * Notes: wrapper leaf; property identity is in FUN_002bc384. */
void sk_r28_prop_test_004809c0(uint8_t *out, uint32_t *scalar)
{
    uint8_t b = (uint8_t)sk_x_002bc384(*scalar);
    *out = (uint8_t)(b & 1);
}

/* FUN_004809f0 @ 0x004809f0   (est. sk_r28_prop_test_004809f0)
 * Ghidra: void FUN_004809f0(byte *out, undefined4 *scalar)
 * Calls the scalar property bit-tester sk_x_002bc3a0 (FUN_002bc3a0) and
 * stores the low bit of its result into the caller's bool out-slot.
 * Confidence: medium (logic trivially faithful; property meaning owned by callee).
 * Notes: wrapper leaf; property identity is in FUN_002bc3a0. */
void sk_r28_prop_test_004809f0(uint8_t *out, uint32_t *scalar)
{
    uint8_t b = (uint8_t)sk_x_002bc3a0(*scalar);
    *out = (uint8_t)(b & 1);
}

/* FUN_00480a20 @ 0x00480a20   (est. sk_r28_prop_test_00480a20)
 * Ghidra: void FUN_00480a20(byte *out, undefined4 *scalar)
 * Calls the scalar property bit-tester sk_x_002bc3bc (FUN_002bc3bc) and
 * stores the low bit of its result into the caller's bool out-slot.
 * Confidence: medium (logic trivially faithful; property meaning owned by callee).
 * Notes: wrapper leaf; property identity is in FUN_002bc3bc. */
void sk_r28_prop_test_00480a20(uint8_t *out, uint32_t *scalar)
{
    uint8_t b = (uint8_t)sk_x_002bc3bc(*scalar);
    *out = (uint8_t)(b & 1);
}

/* FUN_00480a50 @ 0x00480a50   (est. sk_r28_prop_test_00480a50)
 * Ghidra: void FUN_00480a50(byte *out, undefined4 *scalar)
 * Calls the scalar property bit-tester sk_x_002bc330 (FUN_002bc330) and
 * stores the low bit of its result into the caller's bool out-slot.
 * Confidence: medium (logic trivially faithful; property meaning owned by callee).
 * Notes: wrapper leaf; property identity is in FUN_002bc330. */
void sk_r28_prop_test_00480a50(uint8_t *out, uint32_t *scalar)
{
    uint8_t b = (uint8_t)sk_x_002bc330(*scalar);
    *out = (uint8_t)(b & 1);
}

/* FUN_00480a80 @ 0x00480a80   (est. sk_r28_prop_test_00480a80)
 * Ghidra: void FUN_00480a80(byte *out, undefined4 *scalar)
 * Calls the scalar property bit-tester sk_x_002bc368 (FUN_002bc368) and
 * stores the low bit of its result into the caller's bool out-slot.
 * Confidence: medium (logic trivially faithful; property meaning owned by callee).
 * Notes: wrapper leaf; property identity is in FUN_002bc368. */
void sk_r28_prop_test_00480a80(uint8_t *out, uint32_t *scalar)
{
    uint8_t b = (uint8_t)sk_x_002bc368(*scalar);
    *out = (uint8_t)(b & 1);
}

/* FUN_00480ab0 @ 0x00480ab0   (est. sk_r28_prop_test_00480ab0)
 * Ghidra: void FUN_00480ab0(byte *out, undefined4 *scalar)
 * Calls the scalar property bit-tester sk_x_002bc34c (FUN_002bc34c) and
 * stores the low bit of its result into the caller's bool out-slot.
 * Confidence: medium (logic trivially faithful; property meaning owned by callee).
 * Notes: wrapper leaf; property identity is in FUN_002bc34c. */
void sk_r28_prop_test_00480ab0(uint8_t *out, uint32_t *scalar)
{
    uint8_t b = (uint8_t)sk_x_002bc34c(*scalar);
    *out = (uint8_t)(b & 1);
}

/* FUN_00480ae0 @ 0x00480ae0   (est. sk_r28_prop_test_00480ae0)
 * Ghidra: void FUN_00480ae0(byte *out, undefined4 *scalar)
 * Calls the scalar property bit-tester sk_x_002bbf78 (FUN_002bbf78) and
 * stores the low bit of its result into the caller's bool out-slot.
 * Confidence: medium (logic trivially faithful; property meaning owned by callee).
 * Notes: wrapper leaf; property identity is in FUN_002bbf78. */
void sk_r28_prop_test_00480ae0(uint8_t *out, uint32_t *scalar)
{
    uint8_t b = (uint8_t)sk_x_002bbf78(*scalar);
    *out = (uint8_t)(b & 1);
}

/* FUN_00480b10 @ 0x00480b10   (est. sk_r28_prop_test_00480b10)
 * Ghidra: void FUN_00480b10(byte *out, undefined4 *scalar)
 * Calls the scalar property bit-tester sk_x_002bbfb0 (FUN_002bbfb0) and
 * stores the low bit of its result into the caller's bool out-slot.
 * Confidence: medium (logic trivially faithful; property meaning owned by callee).
 * Notes: wrapper leaf; property identity is in FUN_002bbfb0. */
void sk_r28_prop_test_00480b10(uint8_t *out, uint32_t *scalar)
{
    uint8_t b = (uint8_t)sk_x_002bbfb0(*scalar);
    *out = (uint8_t)(b & 1);
}

/* FUN_00480b40 @ 0x00480b40   (est. sk_r28_prop_test_00480b40)
 * Ghidra: void FUN_00480b40(byte *out, undefined4 *scalar)
 * Calls the scalar property bit-tester sk_x_002bbf94 (FUN_002bbf94) and
 * stores the low bit of its result into the caller's bool out-slot.
 * Confidence: medium (logic trivially faithful; property meaning owned by callee).
 * Notes: wrapper leaf; property identity is in FUN_002bbf94. */
void sk_r28_prop_test_00480b40(uint8_t *out, uint32_t *scalar)
{
    uint8_t b = (uint8_t)sk_x_002bbf94(*scalar);
    *out = (uint8_t)(b & 1);
}

/* FUN_00480b70 @ 0x00480b70   (est. sk_r28_prop_test_00480b70)
 * Ghidra: void FUN_00480b70(byte *out, undefined4 *scalar)
 * Calls the scalar property bit-tester sk_x_002bbfcc (FUN_002bbfcc) and
 * stores the low bit of its result into the caller's bool out-slot.
 * Confidence: medium (logic trivially faithful; property meaning owned by callee).
 * Notes: wrapper leaf; property identity is in FUN_002bbfcc. */
void sk_r28_prop_test_00480b70(uint8_t *out, uint32_t *scalar)
{
    uint8_t b = (uint8_t)sk_x_002bbfcc(*scalar);
    *out = (uint8_t)(b & 1);
}

/* FUN_00480ba0 @ 0x00480ba0   (est. sk_r28_prop_test_00480ba0)
 * Ghidra: void FUN_00480ba0(byte *out, undefined4 *scalar)
 * Calls the scalar property bit-tester sk_x_002bc42c (FUN_002bc42c) and
 * stores the low bit of its result into the caller's bool out-slot.
 * Confidence: medium (logic trivially faithful; property meaning owned by callee).
 * Notes: wrapper leaf; property identity is in FUN_002bc42c. */
void sk_r28_prop_test_00480ba0(uint8_t *out, uint32_t *scalar)
{
    uint8_t b = (uint8_t)sk_x_002bc42c(*scalar);
    *out = (uint8_t)(b & 1);
}

/* FUN_00480bd0 @ 0x00480bd0   (est. sk_r28_prop_test_00480bd0)
 * Ghidra: void FUN_00480bd0(byte *out, undefined4 *scalar)
 * Calls the scalar property bit-tester sk_x_002bc410 (FUN_002bc410) and
 * stores the low bit of its result into the caller's bool out-slot.
 * Confidence: medium (logic trivially faithful; property meaning owned by callee).
 * Notes: wrapper leaf; property identity is in FUN_002bc410. */
void sk_r28_prop_test_00480bd0(uint8_t *out, uint32_t *scalar)
{
    uint8_t b = (uint8_t)sk_x_002bc410(*scalar);
    *out = (uint8_t)(b & 1);
}

/* FUN_00480c00 @ 0x00480c00   (est. sk_r28_prop_test_00480c00)
 * Ghidra: void FUN_00480c00(byte *out, undefined4 *scalar)
 * Calls the scalar property bit-tester sk_x_002bc3d8 (FUN_002bc3d8) and
 * stores the low bit of its result into the caller's bool out-slot.
 * Confidence: medium (logic trivially faithful; property meaning owned by callee).
 * Notes: wrapper leaf; property identity is in FUN_002bc3d8. */
void sk_r28_prop_test_00480c00(uint8_t *out, uint32_t *scalar)
{
    uint8_t b = (uint8_t)sk_x_002bc3d8(*scalar);
    *out = (uint8_t)(b & 1);
}

/* FUN_00480c30 @ 0x00480c30   (est. sk_r28_prop_test_00480c30)
 * Ghidra: void FUN_00480c30(byte *out, undefined4 *scalar)
 * Calls the scalar property bit-tester sk_x_002bc3f4 (FUN_002bc3f4) and
 * stores the low bit of its result into the caller's bool out-slot.
 * Confidence: medium (logic trivially faithful; property meaning owned by callee).
 * Notes: wrapper leaf; property identity is in FUN_002bc3f4. */
void sk_r28_prop_test_00480c30(uint8_t *out, uint32_t *scalar)
{
    uint8_t b = (uint8_t)sk_x_002bc3f4(*scalar);
    *out = (uint8_t)(b & 1);
}

/* FUN_00480c60 @ 0x00480c60   (est. sk_r28_prop_test_00480c60)
 * Ghidra: void FUN_00480c60(byte *out, undefined4 *scalar)
 * Calls the scalar property bit-tester sk_x_002bbfe8 (FUN_002bbfe8) and
 * stores the low bit of its result into the caller's bool out-slot.
 * Confidence: medium (logic trivially faithful; property meaning owned by callee).
 * Notes: wrapper leaf; property identity is in FUN_002bbfe8. */
void sk_r28_prop_test_00480c60(uint8_t *out, uint32_t *scalar)
{
    uint8_t b = (uint8_t)sk_x_002bbfe8(*scalar);
    *out = (uint8_t)(b & 1);
}

/* FUN_00480c90 @ 0x00480c90   (est. sk_r28_prop_test_00480c90)
 * Ghidra: void FUN_00480c90(byte *out, undefined4 *scalar)
 * Calls the scalar property bit-tester sk_x_002bc004 (FUN_002bc004) and
 * stores the low bit of its result into the caller's bool out-slot.
 * Confidence: medium (logic trivially faithful; property meaning owned by callee).
 * Notes: wrapper leaf; property identity is in FUN_002bc004. */
void sk_r28_prop_test_00480c90(uint8_t *out, uint32_t *scalar)
{
    uint8_t b = (uint8_t)sk_x_002bc004(*scalar);
    *out = (uint8_t)(b & 1);
}

/* FUN_00480cc0 @ 0x00480cc0   (est. sk_r28_prop_test_00480cc0)
 * Ghidra: void FUN_00480cc0(byte *out, undefined4 *scalar)
 * Calls the scalar property bit-tester sk_x_002bc020 (FUN_002bc020) and
 * stores the low bit of its result into the caller's bool out-slot.
 * Confidence: medium (logic trivially faithful; property meaning owned by callee).
 * Notes: wrapper leaf; property identity is in FUN_002bc020. */
void sk_r28_prop_test_00480cc0(uint8_t *out, uint32_t *scalar)
{
    uint8_t b = (uint8_t)sk_x_002bc020(*scalar);
    *out = (uint8_t)(b & 1);
}

/* FUN_00480cf0 @ 0x00480cf0   (est. sk_r28_prop_test_00480cf0)
 * Ghidra: void FUN_00480cf0(byte *out, undefined4 *scalar)
 * Calls the scalar property bit-tester sk_x_002bc03c (FUN_002bc03c) and
 * stores the low bit of its result into the caller's bool out-slot.
 * Confidence: medium (logic trivially faithful; property meaning owned by callee).
 * Notes: wrapper leaf; property identity is in FUN_002bc03c. */
void sk_r28_prop_test_00480cf0(uint8_t *out, uint32_t *scalar)
{
    uint8_t b = (uint8_t)sk_x_002bc03c(*scalar);
    *out = (uint8_t)(b & 1);
}

/* FUN_00480d20 @ 0x00480d20   (est. sk_r28_prop_test_00480d20)
 * Ghidra: void FUN_00480d20(byte *out, undefined4 *scalar)
 * Calls the scalar property bit-tester sk_x_002bc058 (FUN_002bc058) and
 * stores the low bit of its result into the caller's bool out-slot.
 * Confidence: medium (logic trivially faithful; property meaning owned by callee).
 * Notes: wrapper leaf; property identity is in FUN_002bc058. */
void sk_r28_prop_test_00480d20(uint8_t *out, uint32_t *scalar)
{
    uint8_t b = (uint8_t)sk_x_002bc058(*scalar);
    *out = (uint8_t)(b & 1);
}

/* FUN_00480d50 @ 0x00480d50   (est. sk_r28_prop_test_00480d50)
 * Ghidra: void FUN_00480d50(byte *out, undefined4 *scalar)
 * Calls the scalar property bit-tester sk_x_002bc074 (FUN_002bc074) and
 * stores the low bit of its result into the caller's bool out-slot.
 * Confidence: medium (logic trivially faithful; property meaning owned by callee).
 * Notes: wrapper leaf; property identity is in FUN_002bc074. */
void sk_r28_prop_test_00480d50(uint8_t *out, uint32_t *scalar)
{
    uint8_t b = (uint8_t)sk_x_002bc074(*scalar);
    *out = (uint8_t)(b & 1);
}

/* FUN_00480d80 @ 0x00480d80   (est. sk_r28_prop_test_00480d80)
 * Ghidra: void FUN_00480d80(byte *out, undefined4 *scalar)
 * Calls the scalar property bit-tester sk_x_002bc0ac (FUN_002bc0ac) and
 * stores the low bit of its result into the caller's bool out-slot.
 * Confidence: medium (logic trivially faithful; property meaning owned by callee).
 * Notes: wrapper leaf; property identity is in FUN_002bc0ac. */
void sk_r28_prop_test_00480d80(uint8_t *out, uint32_t *scalar)
{
    uint8_t b = (uint8_t)sk_x_002bc0ac(*scalar);
    *out = (uint8_t)(b & 1);
}

/* FUN_00480db0 @ 0x00480db0   (est. sk_r28_prop_test_00480db0)
 * Ghidra: void FUN_00480db0(byte *out, undefined4 *scalar)
 * Calls the scalar property bit-tester sk_x_002bc090 (FUN_002bc090) and
 * stores the low bit of its result into the caller's bool out-slot.
 * Confidence: medium (logic trivially faithful; property meaning owned by callee).
 * Notes: wrapper leaf; property identity is in FUN_002bc090. */
void sk_r28_prop_test_00480db0(uint8_t *out, uint32_t *scalar)
{
    uint8_t b = (uint8_t)sk_x_002bc090(*scalar);
    *out = (uint8_t)(b & 1);
}

/* FUN_00480de0 @ 0x00480de0   (est. sk_r28_prop_test_00480de0)
 * Ghidra: void FUN_00480de0(byte *out, undefined4 *scalar)
 * Calls the scalar property bit-tester sk_x_002bc0c8 (FUN_002bc0c8) and
 * stores the low bit of its result into the caller's bool out-slot.
 * Confidence: medium (logic trivially faithful; property meaning owned by callee).
 * Notes: wrapper leaf; property identity is in FUN_002bc0c8. */
void sk_r28_prop_test_00480de0(uint8_t *out, uint32_t *scalar)
{
    uint8_t b = (uint8_t)sk_x_002bc0c8(*scalar);
    *out = (uint8_t)(b & 1);
}

/* FUN_00480e10 @ 0x00480e10   (est. sk_r28_prop_test_00480e10)
 * Ghidra: void FUN_00480e10(byte *out, undefined4 *scalar)
 * Calls the scalar property bit-tester sk_x_002bc0e4 (FUN_002bc0e4) and
 * stores the low bit of its result into the caller's bool out-slot.
 * Confidence: medium (logic trivially faithful; property meaning owned by callee).
 * Notes: wrapper leaf; property identity is in FUN_002bc0e4. */
void sk_r28_prop_test_00480e10(uint8_t *out, uint32_t *scalar)
{
    uint8_t b = (uint8_t)sk_x_002bc0e4(*scalar);
    *out = (uint8_t)(b & 1);
}

/* FUN_00480e40 @ 0x00480e40   (est. sk_r28_prop_test_00480e40)
 * Ghidra: void FUN_00480e40(byte *out, undefined4 *scalar)
 * Calls the scalar property bit-tester sk_x_002bc100 (FUN_002bc100) and
 * stores the low bit of its result into the caller's bool out-slot.
 * Confidence: medium (logic trivially faithful; property meaning owned by callee).
 * Notes: wrapper leaf; property identity is in FUN_002bc100. */
void sk_r28_prop_test_00480e40(uint8_t *out, uint32_t *scalar)
{
    uint8_t b = (uint8_t)sk_x_002bc100(*scalar);
    *out = (uint8_t)(b & 1);
}

/* FUN_00480e70 @ 0x00480e70   (est. sk_r28_prop_test_00480e70)
 * Ghidra: void FUN_00480e70(byte *out, undefined4 *scalar)
 * Calls the scalar property bit-tester sk_x_002bc11c (FUN_002bc11c) and
 * stores the low bit of its result into the caller's bool out-slot.
 * Confidence: medium (logic trivially faithful; property meaning owned by callee).
 * Notes: wrapper leaf; property identity is in FUN_002bc11c. */
void sk_r28_prop_test_00480e70(uint8_t *out, uint32_t *scalar)
{
    uint8_t b = (uint8_t)sk_x_002bc11c(*scalar);
    *out = (uint8_t)(b & 1);
}

/* FUN_00480ea0 @ 0x00480ea0   (est. sk_r28_prop_test_00480ea0)
 * Ghidra: void FUN_00480ea0(byte *out, undefined4 *scalar)
 * Calls the scalar property bit-tester sk_x_002bc138 (FUN_002bc138) and
 * stores the low bit of its result into the caller's bool out-slot.
 * Confidence: medium (logic trivially faithful; property meaning owned by callee).
 * Notes: wrapper leaf; property identity is in FUN_002bc138. */
void sk_r28_prop_test_00480ea0(uint8_t *out, uint32_t *scalar)
{
    uint8_t b = (uint8_t)sk_x_002bc138(*scalar);
    *out = (uint8_t)(b & 1);
}

/* FUN_00480ed0 @ 0x00480ed0   (est. sk_r28_prop_test_00480ed0)
 * Ghidra: void FUN_00480ed0(byte *out, undefined4 *scalar)
 * Calls the scalar property bit-tester sk_x_002bc154 (FUN_002bc154) and
 * stores the low bit of its result into the caller's bool out-slot.
 * Confidence: medium (logic trivially faithful; property meaning owned by callee).
 * Notes: wrapper leaf; property identity is in FUN_002bc154. */
void sk_r28_prop_test_00480ed0(uint8_t *out, uint32_t *scalar)
{
    uint8_t b = (uint8_t)sk_x_002bc154(*scalar);
    *out = (uint8_t)(b & 1);
}

/* FUN_00480f00 @ 0x00480f00   (est. sk_r28_prop_test_00480f00)
 * Ghidra: void FUN_00480f00(byte *out, undefined4 *scalar)
 * Calls the scalar property bit-tester sk_x_002bc170 (FUN_002bc170) and
 * stores the low bit of its result into the caller's bool out-slot.
 * Confidence: medium (logic trivially faithful; property meaning owned by callee).
 * Notes: wrapper leaf; property identity is in FUN_002bc170. */
void sk_r28_prop_test_00480f00(uint8_t *out, uint32_t *scalar)
{
    uint8_t b = (uint8_t)sk_x_002bc170(*scalar);
    *out = (uint8_t)(b & 1);
}

/* FUN_00480f30 @ 0x00480f30   (est. sk_r28_prop_test_00480f30)
 * Ghidra: void FUN_00480f30(byte *out, undefined4 *scalar)
 * Calls the scalar property bit-tester sk_x_002bc2c0 (FUN_002bc2c0) and
 * stores the low bit of its result into the caller's bool out-slot.
 * Confidence: medium (logic trivially faithful; property meaning owned by callee).
 * Notes: wrapper leaf; property identity is in FUN_002bc2c0. */
void sk_r28_prop_test_00480f30(uint8_t *out, uint32_t *scalar)
{
    uint8_t b = (uint8_t)sk_x_002bc2c0(*scalar);
    *out = (uint8_t)(b & 1);
}

/* FUN_00480f60 @ 0x00480f60   (est. sk_r28_prop_test_00480f60)
 * Ghidra: void FUN_00480f60(byte *out, undefined4 *scalar)
 * Calls the scalar property bit-tester sk_x_002bc2dc (FUN_002bc2dc) and
 * stores the low bit of its result into the caller's bool out-slot.
 * Confidence: medium (logic trivially faithful; property meaning owned by callee).
 * Notes: wrapper leaf; property identity is in FUN_002bc2dc. */
void sk_r28_prop_test_00480f60(uint8_t *out, uint32_t *scalar)
{
    uint8_t b = (uint8_t)sk_x_002bc2dc(*scalar);
    *out = (uint8_t)(b & 1);
}

/* FUN_00480f90 @ 0x00480f90   (est. sk_r28_prop_test_00480f90)
 * Ghidra: void FUN_00480f90(byte *out, undefined4 *scalar)
 * Calls the scalar property bit-tester sk_x_002bc18c (FUN_002bc18c) and
 * stores the low bit of its result into the caller's bool out-slot.
 * Confidence: medium (logic trivially faithful; property meaning owned by callee).
 * Notes: wrapper leaf; property identity is in FUN_002bc18c. */
void sk_r28_prop_test_00480f90(uint8_t *out, uint32_t *scalar)
{
    uint8_t b = (uint8_t)sk_x_002bc18c(*scalar);
    *out = (uint8_t)(b & 1);
}

/* FUN_00480fc0 @ 0x00480fc0   (est. sk_r28_prop_test_00480fc0)
 * Ghidra: void FUN_00480fc0(byte *out, undefined4 *scalar)
 * Calls the scalar property bit-tester sk_x_002bc1a8 (FUN_002bc1a8) and
 * stores the low bit of its result into the caller's bool out-slot.
 * Confidence: medium (logic trivially faithful; property meaning owned by callee).
 * Notes: wrapper leaf; property identity is in FUN_002bc1a8. */
void sk_r28_prop_test_00480fc0(uint8_t *out, uint32_t *scalar)
{
    uint8_t b = (uint8_t)sk_x_002bc1a8(*scalar);
    *out = (uint8_t)(b & 1);
}

/* FUN_00481004 @ 0x00481004   (est. sk_r28_prop_test_00481004)
 * Ghidra: void FUN_00481004(byte *out, undefined4 *scalar)
 * Calls the scalar property bit-tester sk_x_002bc1c4 (FUN_002bc1c4) and
 * stores the low bit of its result into the caller's bool out-slot.
 * Confidence: medium (logic trivially faithful; property meaning owned by callee).
 * Notes: wrapper leaf; property identity is in FUN_002bc1c4. */
void sk_r28_prop_test_00481004(uint8_t *out, uint32_t *scalar)
{
    uint8_t b = (uint8_t)sk_x_002bc1c4(*scalar);
    *out = (uint8_t)(b & 1);
}

/* FUN_00481034 @ 0x00481034   (est. sk_r28_prop_test_00481034)
 * Ghidra: void FUN_00481034(byte *out, undefined4 *scalar)
 * Calls the scalar property bit-tester sk_x_002bc288 (FUN_002bc288) and
 * stores the low bit of its result into the caller's bool out-slot.
 * Confidence: medium (logic trivially faithful; property meaning owned by callee).
 * Notes: wrapper leaf; property identity is in FUN_002bc288. */
void sk_r28_prop_test_00481034(uint8_t *out, uint32_t *scalar)
{
    uint8_t b = (uint8_t)sk_x_002bc288(*scalar);
    *out = (uint8_t)(b & 1);
}

/* FUN_00481064 @ 0x00481064   (est. sk_r28_prop_test_00481064)
 * Ghidra: void FUN_00481064(byte *out, undefined4 *scalar)
 * Calls the scalar property bit-tester sk_x_002bc1e0 (FUN_002bc1e0) and
 * stores the low bit of its result into the caller's bool out-slot.
 * Confidence: medium (logic trivially faithful; property meaning owned by callee).
 * Notes: wrapper leaf; property identity is in FUN_002bc1e0. */
void sk_r28_prop_test_00481064(uint8_t *out, uint32_t *scalar)
{
    uint8_t b = (uint8_t)sk_x_002bc1e0(*scalar);
    *out = (uint8_t)(b & 1);
}

/* FUN_00481094 @ 0x00481094   (est. sk_r28_prop_test_00481094)
 * Ghidra: void FUN_00481094(byte *out, undefined4 *scalar)
 * Calls the scalar property bit-tester sk_x_002bc1fc (FUN_002bc1fc) and
 * stores the low bit of its result into the caller's bool out-slot.
 * Confidence: medium (logic trivially faithful; property meaning owned by callee).
 * Notes: wrapper leaf; property identity is in FUN_002bc1fc. */
void sk_r28_prop_test_00481094(uint8_t *out, uint32_t *scalar)
{
    uint8_t b = (uint8_t)sk_x_002bc1fc(*scalar);
    *out = (uint8_t)(b & 1);
}

/* FUN_004810c4 @ 0x004810c4   (est. sk_r28_prop_test_004810c4)
 * Ghidra: void FUN_004810c4(byte *out, undefined4 *scalar)
 * Calls the scalar property bit-tester sk_x_002bc218 (FUN_002bc218) and
 * stores the low bit of its result into the caller's bool out-slot.
 * Confidence: medium (logic trivially faithful; property meaning owned by callee).
 * Notes: wrapper leaf; property identity is in FUN_002bc218. */
void sk_r28_prop_test_004810c4(uint8_t *out, uint32_t *scalar)
{
    uint8_t b = (uint8_t)sk_x_002bc218(*scalar);
    *out = (uint8_t)(b & 1);
}

/* FUN_004810f4 @ 0x004810f4   (est. sk_r28_prop_test_004810f4)
 * Ghidra: void FUN_004810f4(byte *out, undefined4 *scalar)
 * Calls the scalar property bit-tester sk_x_002bc2a4 (FUN_002bc2a4) and
 * stores the low bit of its result into the caller's bool out-slot.
 * Confidence: medium (logic trivially faithful; property meaning owned by callee).
 * Notes: wrapper leaf; property identity is in FUN_002bc2a4. */
void sk_r28_prop_test_004810f4(uint8_t *out, uint32_t *scalar)
{
    uint8_t b = (uint8_t)sk_x_002bc2a4(*scalar);
    *out = (uint8_t)(b & 1);
}

/* FUN_00481124 @ 0x00481124   (est. sk_r28_prop_test_00481124)
 * Ghidra: void FUN_00481124(byte *out, undefined4 *scalar)
 * Calls the scalar property bit-tester sk_x_002bc234 (FUN_002bc234) and
 * stores the low bit of its result into the caller's bool out-slot.
 * Confidence: medium (logic trivially faithful; property meaning owned by callee).
 * Notes: wrapper leaf; property identity is in FUN_002bc234. */
void sk_r28_prop_test_00481124(uint8_t *out, uint32_t *scalar)
{
    uint8_t b = (uint8_t)sk_x_002bc234(*scalar);
    *out = (uint8_t)(b & 1);
}

/* FUN_00481154 @ 0x00481154   (est. sk_r28_prop_test_00481154)
 * Ghidra: void FUN_00481154(byte *out, undefined4 *scalar)
 * Calls the scalar property bit-tester sk_x_002bc250 (FUN_002bc250) and
 * stores the low bit of its result into the caller's bool out-slot.
 * Confidence: medium (logic trivially faithful; property meaning owned by callee).
 * Notes: wrapper leaf; property identity is in FUN_002bc250. */
void sk_r28_prop_test_00481154(uint8_t *out, uint32_t *scalar)
{
    uint8_t b = (uint8_t)sk_x_002bc250(*scalar);
    *out = (uint8_t)(b & 1);
}

/* FUN_00481184 @ 0x00481184   (est. sk_r28_prop_test_00481184)
 * Ghidra: void FUN_00481184(byte *out, undefined4 *scalar)
 * Calls the scalar property bit-tester sk_x_002bc26c (FUN_002bc26c) and
 * stores the low bit of its result into the caller's bool out-slot.
 * Confidence: medium (logic trivially faithful; property meaning owned by callee).
 * Notes: wrapper leaf; property identity is in FUN_002bc26c. */
void sk_r28_prop_test_00481184(uint8_t *out, uint32_t *scalar)
{
    uint8_t b = (uint8_t)sk_x_002bc26c(*scalar);
    *out = (uint8_t)(b & 1);
}
