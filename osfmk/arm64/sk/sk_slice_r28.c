/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel,
 * arm64e, image base 0) — the cL4 microkernel. Ground truth: Ghidra FUN_ names +
 * addresses in program cl4_kernel.raw. Version "cL4 microkernel (cL4
 * (679.100.61))". All names are estimates unless string/header-matched.
 *
 * This file covers wave batch SKR28, slice 0x0047c528-0x004815cc: a dense
 * run of Swift standard-library runtime leaves for Unicode scalar
 * classification, UTF-8/UTF-16 decoding, character-property tests, regex
 * parse error reporting, and L4 error-code → Swift error object
 * construction. The bulk are one-line wrappers that call a scalar-property
 * bit tester (FUN_002bxxxx, out of slice) and store `result & 1` into a bool
 * out-param. A few larger bodies build error objects (FUN_0047fa44,
 * FUN_004801f8), decode UTF-8 scalars with continuation handling
 * (FUN_0047ef1c / 0047ee98 / 0047edf4 / 0047f630), or perform
 * case-insensitive range membership tests over decoded scalars
 * (FUN_0047ead4). `unaff_*` register artifacts are described in the notes.
 */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "sk_internal.h"

typedef uint64_t word_t;

/* ------------------------------------------------------------------ *
 * Out-of-slice cL4/Swift-runtime helpers referenced by this slice.
 * FUN_ addresses in comments; bodies owned by sibling SK range workers.
 * Names are estimates.
 * ------------------------------------------------------------------ */

extern void sk_alloc_obj(word_t a, word_t b, word_t c);  /* FUN_0036a940 (allocation + arg block) */
extern void sk_refcount_acquire(word_t a);               /* FUN_0036b270 (refcount acquire) */
extern void sk_refcount_release(word_t a);               /* FUN_0036b118 (refcount release) */
extern void sk_obj_release(word_t a);                    /* FUN_003a25d4 (object/cap release via mask) */
extern void sk_memmove(void *d, void *s, word_t n);      /* FUN_00117cc4 (overlapping memmove) */
extern word_t sk_unicode_prop_word(word_t a);            /* FUN_003d36b0 (scalar property bitmap getter) */
extern void sk_unicode_prop_002bbf08(word_t a);          /* FUN_002bbf08 (property bit 7) */
extern void sk_unicode_prop_002bbf40(word_t a);          /* FUN_002bbf40 (property bit 8) */
extern void sk_unicode_prop_002bbf5c(word_t a);          /* FUN_002bbf5c (property bit 9) */
extern void sk_unicode_prop_002bbf78(word_t a);          /* FUN_002bbf78 (property bit 10) */
extern void sk_unicode_prop_002bbf94(word_t a);          /* FUN_002bbf94 (property bit 11) */
extern void sk_unicode_prop_002bbfb0(word_t a);          /* FUN_002bbfb0 (property bit 12) */
extern void sk_unicode_prop_002bbfcc(word_t a);          /* FUN_002bbfcc (property bit 13) */
extern void sk_unicode_prop_002bbfe8(word_t a);          /* FUN_002bbfe8 (property bit 14) */
extern void sk_unicode_prop_002bc004(word_t a);          /* FUN_002bc004 (property bit 15) */
extern void sk_unicode_prop_002bc020(word_t a);          /* FUN_002bc020 (property bit 16) */
extern void sk_unicode_prop_002bc03c(word_t a);          /* FUN_002bc03c (property bit 17) */
extern void sk_unicode_prop_002bc058(word_t a);          /* FUN_002bc058 (property bit 18) */
extern void sk_unicode_prop_002bc074(word_t a);          /* FUN_002bc074 (property bit 19) */
extern void sk_unicode_prop_002bc090(word_t a);          /* FUN_002bc090 (property bit 20) */
extern void sk_unicode_prop_002bc0ac(word_t a);          /* FUN_002bc0ac (property bit 21) */
extern void sk_unicode_prop_002bc0c8(word_t a);          /* FUN_002bc0c8 (property bit 22) */
extern void sk_unicode_prop_002bc0e4(word_t a);          /* FUN_002bc0e4 (property bit 23) */
extern void sk_unicode_prop_002bc100(word_t a);          /* FUN_002bc100 (property bit 24) */
extern void sk_unicode_prop_002bc11c(word_t a);          /* FUN_002bc11c (property bit 25) */
extern void sk_unicode_prop_002bc138(word_t a);          /* FUN_002bc138 (property bit 26) */
extern void sk_unicode_prop_002bc154(word_t a);          /* FUN_002bc154 (property bit 27) */
extern void sk_unicode_prop_002bc170(word_t a);          /* FUN_002bc170 (property bit 28) */
extern void sk_unicode_prop_002bc18c(word_t a);          /* FUN_002bc18c (property bit 29) */
extern void sk_unicode_prop_002bc1a8(word_t a);          /* FUN_002bc1a8 (property bit 30) */
extern void sk_unicode_prop_002bc1c4(word_t a);          /* FUN_002bc1c4 (property bit 32) */
extern void sk_unicode_prop_002bc1e0(word_t a);          /* FUN_002bc1e0 (property bit 33) */
extern void sk_unicode_prop_002bc1fc(word_t a);          /* FUN_002bc1fc (property bit 34) */
extern void sk_unicode_prop_002bc218(word_t a);          /* FUN_002bc218 (property bit 35) */
extern void sk_unicode_prop_002bc234(word_t a);          /* FUN_002bc234 (property bit 37) */
extern void sk_unicode_prop_002bc250(word_t a);          /* FUN_002bc250 (property bit 38) */
extern void sk_unicode_prop_002bc26c(word_t a);          /* FUN_002bc26c (property bit 39) */
extern void sk_unicode_prop_002bc288(word_t a);          /* FUN_002bc288 (property bit 40) */
extern void sk_unicode_prop_002bc2a4(word_t a);          /* FUN_002bc2a4 (property bit 41) */
extern void sk_unicode_prop_002bc2c0(word_t a);          /* FUN_002bc2c0 (property bit 42) */
extern void sk_unicode_prop_002bc2dc(word_t a);          /* FUN_002bc2dc (property bit 43) */
extern void sk_unicode_prop_002bc2f8(word_t a);          /* FUN_002bc2f8 (property bit 44) */
extern void sk_unicode_prop_002bc314(word_t a);          /* FUN_002bc314 (property bit 45) */
extern void sk_unicode_prop_002bc330(word_t a);          /* FUN_002bc330 (property bit 46) */
extern void sk_unicode_prop_002bc34c(word_t a);          /* FUN_002bc34c (property bit 47) */
extern void sk_unicode_prop_002bc368(word_t a);          /* FUN_002bc368 (property bit 48) */
extern void sk_unicode_prop_002bc384(word_t a);          /* FUN_002bc384 (property bit 49) */
extern void sk_unicode_prop_002bc3a0(word_t a);          /* FUN_002bc3a0 (property bit 50) */
extern void sk_unicode_prop_002bc3bc(word_t a);          /* FUN_002bc3bc (property bit 51) */
extern void sk_unicode_prop_002bc3d8(word_t a);          /* FUN_002bc3d8 (property bit 52) */
extern void sk_unicode_prop_002bc3f4(word_t a);          /* FUN_002bc3f4 (property bit 53) */
extern void sk_unicode_prop_002bc410(word_t a);          /* FUN_002bc410 (property bit 54) */
extern void sk_unicode_prop_002bc42c(word_t a);          /* FUN_002bc42c (property bit 55) */
extern word_t sk_unicode_parse_00254c7c(word_t a);       /* FUN_00254c7c (scalar decode wrapper) */
extern word_t sk_unicode_general_002bc5bc(void);         /* FUN_002bc5bc (scalar general-category getter) */

extern word_t sk_runtime_003509ec(void);                 /* FUN_003509ec */
extern word_t sk_runtime_0036b6ac(void);                 /* FUN_0036b6ac */
extern word_t sk_runtime_004ab128(void);                 /* FUN_004ab128 */
extern word_t sk_runtime_004a4ac4(void);                 /* FUN_004a4ac4 (string/error box read) */
extern word_t sk_runtime_004a4b14(void);                 /* FUN_004a4b14 (string/error box unpack) */
extern word_t sk_runtime_004aaccc(void);                 /* FUN_004aaccc */
extern word_t sk_runtime_004abf50(word_t a);             /* FUN_004abf50 */
extern word_t sk_runtime_000dce50(void);                 /* FUN_000dce50 */
extern word_t sk_runtime_001b798c(word_t a, word_t b, word_t c); /* FUN_001b798c */
extern word_t sk_runtime_0036a940_alloc(word_t a);       /* FUN_0036a940 (allocator) */
extern word_t sk_runtime_0047d6e0(void);                 /* FUN_0047d6e0 (in-slice; declared in body) */
extern word_t sk_runtime_00002834(word_t a);             /* FUN_00002834 (msg/string load) */
extern word_t sk_runtime_0006b6f4(void);                 /* FUN_0006b6f4 (error commit) */
extern word_t sk_runtime_0006a4c0(void);                 /* FUN_0006a4c0 */
extern word_t sk_runtime_002a4ab4(word_t a);             /* FUN_002a4ab4 */
extern word_t sk_runtime_002acbb8(word_t a, word_t b);   /* thunk_FUN_002acbb8 (vspace/ipc transition) */
extern word_t sk_runtime_00355538(word_t a);             /* FUN_00355538 */
extern word_t sk_runtime_00352ae4(void);                 /* FUN_00352ae4 */
extern word_t sk_runtime_000a6e14(word_t a);             /* FUN_000a6e14 */
extern word_t sk_runtime_004ac41c(void);                 /* FUN_004ac41c */
extern word_t sk_runtime_004a4ac4_2(void);               /* FUN_004a4ac4 */
extern word_t sk_runtime_004a4b14_2(void);               /* FUN_004a4b14 */
extern word_t sk_runtime_0047ce4c(void);                 /* FUN_0047ce4c (in-slice; declared in body) */
extern word_t sk_runtime_0009461c(void);                 /* FUN_0009461c (trap/report) */
extern word_t sk_runtime_00365b6c(void);                 /* FUN_00365b6c */
extern word_t sk_runtime_00319808(word_t a, void *b);    /* FUN_00319808 (string/value copy) */
extern word_t sk_runtime_00351f34(void);                 /* FUN_00351f34 */
extern word_t sk_runtime_004ab1dc(void);                 /* FUN_004ab1dc */
extern word_t sk_runtime_0034cc24(void);                 /* FUN_0034cc24 */
extern word_t sk_runtime_00310d98(void *d, void *s);     /* FUN_00310d98 (value move/copy) */
extern word_t sk_runtime_00310d68(void);                 /* FUN_00310d68 */
extern word_t sk_runtime_0049c704(void);                 /* FUN_0049c704 */
extern word_t sk_runtime_0049c714(void);                 /* FUN_0049c714 */
extern word_t sk_runtime_003a261c(void *p);              /* FUN_003a261c (array capacity check) */
extern word_t sk_runtime_0049a604(word_t a, word_t b, word_t c); /* FUN_0049a604 (array grow) */
extern word_t sk_runtime_001a0754(word_t a, word_t b, word_t c); /* thunk_FUN_001a0754 (array realloc) */
extern word_t sk_runtime_00455ac8(word_t a, word_t b, word_t c); /* FUN_00455ac8 */
extern word_t sk_runtime_0029fa0c(void);                 /* FUN_0029fa0c */
extern word_t sk_runtime_0029d3d8(void);                 /* FUN_0029d3d8 */
extern word_t sk_runtime_002bd8f0(void);                 /* FUN_002bd8f0 */
extern word_t sk_runtime_002bd848(void);                 /* FUN_002bd848 */
extern word_t sk_runtime_0016749c(void);                 /* FUN_0016749c */
extern word_t sk_runtime_00167404(void);                 /* FUN_00167404 (scalar load) */
extern word_t sk_runtime_002a49a8(void);                 /* FUN_002a49a8 (scalar via table) */
extern word_t sk_runtime_002a9ba8(void);                 /* FUN_002a9ba8 (string buffer base) */
extern word_t sk_runtime_002ae098(void);                 /* FUN_002ae098 */
extern word_t sk_runtime_0029c058(void);                 /* FUN_0029c058 */
extern word_t sk_runtime_002ab130(void);                 /* FUN_002ab130 */
extern word_t sk_runtime_00255d4c(word_t a);             /* FUN_00255d4c (UTF-8 encode) */
extern word_t sk_runtime_00294cb4(word_t a);             /* FUN_00294cb4 */
extern word_t sk_runtime_003527b8(void);                 /* FUN_003527b8 */
extern word_t sk_runtime_00352af0(void);                 /* FUN_00352af0 */
extern word_t sk_runtime_00353ff4(void);                 /* FUN_00353ff4 */
extern word_t sk_runtime_00352e9c(void);                 /* FUN_00352e9c */
extern word_t sk_runtime_0034c6d4(void);                 /* FUN_0034c6d4 */
extern word_t sk_runtime_00350624(word_t a);             /* FUN_00350624 */
extern word_t sk_runtime_00350600(word_t a);             /* FUN_00350600 */
extern word_t sk_runtime_003504d0(void);                 /* FUN_003504d0 */
extern word_t sk_runtime_003504a0(word_t a);             /* FUN_003504a0 */
extern word_t sk_runtime_00351300(word_t a);             /* FUN_00351300 */
extern word_t sk_runtime_00350a28(void);                 /* FUN_00350a28 */
extern word_t sk_runtime_003509c8(void);                 /* FUN_003509c8 */
extern word_t sk_runtime_00350b54(void);                 /* FUN_00350b54 */
extern word_t sk_runtime_00350b84(word_t a);             /* FUN_00350b84 */
extern word_t sk_runtime_00350b84_2(word_t a);           /* FUN_00350b84 */
extern word_t sk_runtime_00350548(void *p);              /* FUN_00350548 */
extern word_t sk_runtime_00350878(void *p);              /* FUN_00350878 */
extern word_t sk_runtime_001a84f4(void *p);              /* FUN_001a84f4 (hash init) */
extern word_t sk_runtime_001a8564(void);                 /* FUN_001a8564 (hash final) */
extern word_t sk_runtime_00369efc(void);                 /* FUN_00369efc */
extern word_t sk_runtime_004080b0(void);                 /* FUN_004080b0 */
extern word_t sk_runtime_0047d8ec(void);                 /* FUN_0047d8ec (in-slice; declared in body) */
extern word_t sk_runtime_001b9084(void);                 /* FUN_001b9084 */
extern word_t sk_runtime_002298d4(word_t a);             /* thunk_FUN_002298d4 (vspace wait/sync) */
extern word_t sk_runtime_00463f94(void);                 /* FUN_00463f94 */
extern word_t sk_runtime_004ac210(void);                 /* FUN_004ac210 */
extern word_t sk_runtime_0049e2f0(void);                 /* FUN_0049e2f0 */
extern word_t sk_runtime_00458af8(void);                 /* FUN_00458af8 */
extern word_t sk_runtime_00458b14(void *p);              /* FUN_00458b14 */
extern word_t sk_runtime_004176bc(word_t a);             /* FUN_004176bc */
extern word_t sk_runtime_0034ecc8(void);                 /* FUN_0034ecc8 */
extern word_t sk_runtime_002a0cf8(void);                 /* FUN_002a0cf8 (string compare ci) */
extern word_t sk_runtime_004abc0c(void);                 /* FUN_004abc0c */
extern word_t sk_runtime_00267510(void);                 /* FUN_00267510 (scalar parse) */
extern word_t sk_runtime_002bd9ac(void);                 /* FUN_002bd9ac */
extern word_t sk_runtime_00464e64(void);                 /* FUN_00464e64 */
extern word_t sk_runtime_004aaa78(void);                 /* FUN_004aaa78 */
extern word_t sk_runtime_000b44cc(word_t a, word_t b, word_t c); /* FUN_000b44cc (scalar append) */
extern word_t sk_runtime_003532b8(void);                 /* FUN_003532b8 */
extern word_t sk_runtime_0035193c(void);                 /* FUN_0035193c */
extern word_t sk_runtime_00077888(void);                 /* FUN_00077888 */
extern word_t sk_runtime_00351774(word_t a, word_t b);   /* FUN_00351774 (bool result commit) */
extern word_t sk_runtime_00350738(void);                 /* FUN_00350738 */
extern word_t sk_runtime_00350618(void);                 /* FUN_00350618 */
extern word_t sk_runtime_0035063c(void);                 /* FUN_0035063c */
extern word_t sk_runtime_00351db4(void);                 /* FUN_00351db4 */
extern word_t sk_runtime_00068e14(void);                 /* FUN_00068e14 */
extern word_t sk_runtime_0006b3f4(word_t a);             /* FUN_0006b3f4 */
extern word_t sk_runtime_00499158(void);                 /* FUN_00499158 */
extern word_t sk_runtime_000ec004(void);                 /* FUN_000ec004 */
extern word_t sk_runtime_004934a8(void *p, word_t a);    /* FUN_004934a8 */
extern word_t sk_runtime_00473244(word_t a);             /* FUN_00473244 */
extern word_t sk_runtime_004a363c(void *p, void *q);     /* FUN_004a363c */
extern word_t sk_runtime_004a364c(void *p);              /* FUN_004a364c */
extern word_t sk_runtime_00474fe8(void *p);              /* FUN_00474fe8 */
extern word_t sk_runtime_00353cfc(void);                 /* FUN_00353cfc */
extern word_t sk_runtime_00353d14(word_t a);             /* FUN_00353d14 */
extern word_t sk_runtime_00493354(word_t a);             /* FUN_00493354 */
extern word_t sk_runtime_004abdc4(word_t a, word_t b, word_t c); /* FUN_004abdc4 */
extern word_t sk_runtime_004ab288(word_t a, word_t b);   /* FUN_004ab288 */
extern word_t sk_runtime_001f0130(void);                 /* FUN_001f0130 */
extern word_t sk_runtime_004a35b8(void);                 /* FUN_004a35b8 */
extern word_t sk_runtime_0035060c(void);                 /* FUN_0035060c */
extern word_t sk_runtime_0001a1c8(void);                 /* FUN_0001a1c8 */
extern word_t sk_runtime_004a42a0(word_t a, word_t b, word_t c, word_t d); /* FUN_004a42a0 */
extern word_t sk_runtime_0045567c(void *p, void *q, word_t a, word_t b); /* FUN_0045567c */
extern word_t sk_runtime_004a40b8(void);                 /* FUN_004a40b8 (error fn) */
extern word_t sk_runtime_004a4158(void);                 /* FUN_004a4158 */
extern word_t sk_runtime_00351a50(void);                 /* FUN_00351a50 */
extern word_t sk_runtime_004aa734(word_t a);             /* FUN_004aa734 */
extern word_t sk_runtime_0047f5d0(void);                 /* FUN_0047f5d0 (in-slice error build) */
extern word_t sk_runtime_0047f808(void);                 /* FUN_0047f808 (in-slice error build) */
extern word_t sk_runtime_00359018(word_t a);             /* FUN_00359018 */
extern word_t sk_runtime_004acb20(word_t a, word_t b, word_t c); /* FUN_004acb20 */
extern word_t sk_runtime_004acb3c(void);                 /* FUN_004acb3c */
extern word_t sk_runtime_004aaf9c(void);                 /* FUN_004aaf9c */
extern word_t sk_runtime_004abe68(word_t a);             /* FUN_004abe68 */
extern word_t sk_runtime_004ab1fc(word_t a);             /* FUN_004ab1fc */
extern word_t sk_runtime_004ac93c(void);                 /* FUN_004ac93c */
extern word_t sk_runtime_004a3eac(void);                 /* FUN_004a3eac */
extern word_t sk_runtime_004a3e68(void);                 /* FUN_004a3e68 */
extern word_t sk_runtime_004a3d8c(void);                 /* FUN_004a3d8c */
extern word_t sk_runtime_004a3dcc(void);                 /* FUN_004a3dcc */
extern word_t sk_runtime_004a3d60(void);                 /* FUN_004a3d60 */
extern word_t sk_runtime_004a3e20(void);                 /* FUN_004a3e20 */
extern word_t sk_runtime_004a3cc4(void);                 /* FUN_004a3cc4 */
extern word_t sk_runtime_004a3cac(void);                 /* FUN_004a3cac */
extern word_t sk_runtime_004a3c94(void);                 /* FUN_004a3c94 */
extern word_t sk_runtime_004a3f04(void);                 /* FUN_004a3f04 */
extern word_t sk_runtime_004a3f30(void);                 /* FUN_004a3f30 */
extern word_t sk_runtime_004aa240(void);                 /* FUN_004aa240 */
extern word_t sk_runtime_004aa204(void);                 /* FUN_004aa204 */
extern word_t sk_runtime_00355d6c(void);                 /* FUN_00355d6c */
extern word_t sk_runtime_000b430c(void);                 /* FUN_000b430c */
extern word_t sk_runtime_004ab650(void);                 /* FUN_004ab650 */
extern word_t sk_runtime_000f4a9c(word_t a, word_t b, word_t c); /* FUN_000f4a9c */
extern word_t sk_runtime_00205844(void *a, void *b);     /* FUN_00205844 */
extern word_t sk_runtime_004ab6b8(word_t a, word_t b);   /* FUN_004ab6b8 */
extern word_t sk_runtime_004ab6ac(void *a);              /* FUN_004ab6ac */
extern word_t sk_runtime_0044f818(void);                 /* thunk_FUN_0044f818 */
extern word_t sk_runtime_004aa370(void);                 /* FUN_004aa370 */
extern word_t sk_runtime_004ac008(word_t a);             /* FUN_004ac008 */
extern word_t sk_runtime_004aa4e0(void);                 /* FUN_004aa4e0 */
extern word_t sk_runtime_004ac0cc(void);                 /* FUN_004ac0cc */
extern word_t sk_runtime_00027724(word_t a);             /* FUN_00027724 */
extern word_t sk_runtime_00086840(word_t a);             /* FUN_00086840 */
extern word_t sk_runtime_004ace08(void);                 /* FUN_004ace08 */
extern word_t sk_runtime_00357cb4(void);                 /* FUN_00357cb4 */
extern word_t sk_runtime_00357c74(word_t a, word_t b);   /* FUN_00357c74 */
extern word_t sk_runtime_004ace88(word_t a, void *b);    /* FUN_004ace88 */
extern word_t sk_runtime_000a6fe0(void);                 /* FUN_000a6fe0 */
extern word_t sk_runtime_004ac27c(void);                 /* FUN_004ac27c */
extern word_t sk_runtime_00499468(void);                 /* FUN_00499468 */
extern word_t sk_runtime_0006b42c(void);                 /* FUN_0006b42c */
extern word_t sk_runtime_0011d7e8(void);                 /* FUN_0011d7e8 (stack canary check) */
extern word_t sk_runtime_002bbf24(word_t a);             /* FUN_002bbf24 */
extern word_t sk_runtime_002bd724(word_t a);             /* FUN_002bd724 */
extern word_t sk_runtime_0046511c(void);                 /* FUN_0046511c */
extern word_t sk_runtime_002bd8f0_2(void);               /* FUN_002bd8f0 */
extern word_t sk_runtime_0024d9ac(void *p);              /* thunk_FUN_0024d9ac */
extern word_t sk_runtime_0024917c(void *a, void *b);     /* FUN_0024917c */
extern word_t sk_runtime_00100c04(word_t a);             /* FUN_00100c04 */
extern word_t sk_runtime_004ac318(void);                 /* FUN_004ac318 */
extern word_t sk_runtime_00208418(void);                 /* FUN_00208418 */
extern word_t sk_runtime_004ac348(word_t a);             /* FUN_004ac348 */
extern word_t sk_runtime_00465294(void);                 /* FUN_00465294 */
extern word_t sk_runtime_004ab968(word_t a);             /* FUN_004ab968 */
extern word_t sk_runtime_00084180(void);                 /* FUN_00084180 */
extern word_t sk_runtime_00351124(void);                 /* FUN_00351124 */
extern word_t sk_runtime_0036b6ac_2(void);               /* FUN_0036b6ac */
extern word_t sk_runtime_0008409c(void);                 /* FUN_0008409c */
extern word_t sk_runtime_00077024(void);                 /* FUN_00077024 */
extern word_t sk_runtime_000839d8(void);                 /* FUN_000839d8 */
extern word_t sk_runtime_004ab618(void);                 /* FUN_004ab618 */
extern word_t sk_runtime_004ab9e0(void);                 /* FUN_004ab9e0 */
extern word_t sk_runtime_00350774(word_t a, word_t b);   /* FUN_00350774 */
extern word_t sk_runtime_003507e0(void);                 /* FUN_003507e0 */
extern word_t sk_runtime_00498ad4(void);                 /* FUN_00498ad4 */
extern word_t sk_runtime_004aad54(void);                 /* FUN_004aad54 */
extern word_t sk_runtime_00498bdc(void);                 /* FUN_00498bdc */
extern word_t sk_runtime_004ab224(word_t a);             /* FUN_004ab224 */
extern word_t sk_runtime_004abf5c(void);                 /* FUN_004abf5c */
extern word_t sk_runtime_004aa494(word_t a);             /* FUN_004aa494 */
extern word_t sk_runtime_00498b28(word_t a);             /* FUN_00498b28 */
extern word_t sk_runtime_004aaf58(void);                 /* FUN_004aaf58 */
extern word_t sk_runtime_004aa6a8(void);                 /* FUN_004aa6a8 */
extern word_t sk_runtime_004ac3e4(void *p);              /* FUN_004ac3e4 */
extern word_t sk_runtime_0049df0c(void *p);              /* FUN_0049df0c */
extern word_t sk_runtime_0049df18(void *p);              /* FUN_0049df18 */
extern word_t sk_runtime_0049e2d4(void);                 /* FUN_0049e2d4 */
extern word_t sk_runtime_004ac4e0(void);                 /* FUN_004ac4e0 */
extern word_t sk_runtime_004ac034(void *p);              /* FUN_004ac034 */
extern word_t sk_runtime_00352c68(void);                 /* FUN_00352c68 */
extern word_t sk_runtime_004a3918(void *p);              /* FUN_004a3918 */
extern word_t sk_runtime_0035354c(void);                 /* FUN_0035354c */
extern word_t sk_runtime_0001da84(word_t a, word_t b, word_t c); /* FUN_0001da84 */
extern word_t sk_runtime_002b141c(word_t a, word_t b, word_t c); /* FUN_002b141c (UTF-8 scalar decode) */
extern word_t sk_runtime_004ac7ec(word_t a);             /* FUN_004ac7ec */
extern word_t sk_runtime_004950f0(word_t a);             /* FUN_004950f0 */
extern word_t sk_runtime_004abff8(void);                 /* FUN_004abff8 */
extern word_t sk_runtime_004aacf8(word_t a);             /* FUN_004aacf8 */
extern word_t sk_runtime_00077698(void);                 /* FUN_00077698 */
extern word_t sk_runtime_00407ab8(void);                 /* FUN_00407ab8 */
extern word_t sk_runtime_002bc330_2(word_t a);           /* FUN_002bc330 (property bit 46) */
extern word_t sk_runtime_0029d560(word_t a);             /* FUN_0029d560 */
extern word_t sk_runtime_002bc34c_2(word_t a);           /* FUN_002bc34c (property bit 47) */
extern word_t sk_runtime_0029da50(word_t a);             /* FUN_0029da50 */
extern word_t sk_runtime_0047ef1c(void);                 /* FUN_0047ef1c (in-slice; declared in body) */
extern word_t sk_runtime_0047ee98(void);                 /* FUN_0047ee98 (in-slice; declared in body) */
extern word_t sk_runtime_004ab11c(word_t a);             /* FUN_004ab11c */
extern word_t sk_runtime_0007767c(word_t a, word_t b, word_t c); /* FUN_0007767c */
extern word_t sk_runtime_00077888_2(void);               /* FUN_00077888 */
extern word_t sk_runtime_004abcdc(void);                 /* FUN_004abcdc */
extern word_t sk_runtime_004abd2c(word_t a);             /* FUN_004abd2c */
extern word_t sk_runtime_0007c1c4(void);                 /* FUN_0007c1c4 */
extern word_t sk_runtime_001aea6c(void);                 /* FUN_001aea6c */
extern word_t sk_runtime_001ae8a8(void);                 /* FUN_001ae8a8 */
extern word_t sk_runtime_00351d18(void);                 /* FUN_00351d18 */
extern word_t sk_runtime_002be300(void);                 /* FUN_002be300 */
extern word_t sk_runtime_002be23c(void *p);              /* FUN_002be23c */
extern word_t sk_runtime_002be12c(void);                 /* FUN_002be12c */
extern word_t sk_runtime_00343c20(void *p);              /* FUN_00343c20 */
extern word_t sk_runtime_00356364(void);                 /* FUN_00356364 */
extern word_t sk_runtime_004aad94(void);                 /* FUN_004aad94 */
extern word_t sk_runtime_0034b3f8(word_t a, word_t b, word_t c); /* FUN_0034b3f8 (utf8 scalar accumulate) */
extern word_t sk_runtime_004abbb8(word_t a);             /* FUN_004abbb8 */
extern word_t sk_runtime_00417aa0(void);                 /* FUN_00417aa0 */
extern word_t sk_runtime_000b4390(void);                 /* FUN_000b4390 */
extern word_t sk_runtime_0035056c(word_t a);             /* FUN_0035056c */
extern word_t sk_runtime_0047f1e0(void);                 /* FUN_0047f1e0 (in-slice; declared in body) */
extern word_t sk_runtime_00353cfc_2(void);               /* FUN_00353cfc */
extern word_t sk_runtime_004aa890(void);                 /* FUN_004aa890 */
extern word_t sk_runtime_004ac1a4(void *p);              /* FUN_004ac1a4 */
extern word_t sk_runtime_004ab0f0(void *p);              /* FUN_004ab0f0 */
extern word_t sk_runtime_004ac52c(void *p);              /* FUN_004ac52c */
extern word_t sk_runtime_0047dac4(void);                 /* FUN_0047dac4 (in-slice; declared in body) */
extern word_t sk_runtime_00466214(void);                 /* FUN_00466214 */
extern word_t sk_runtime_0047e96c(void);                 /* FUN_0047e96c (in-slice; declared in body) */
extern word_t sk_runtime_0047e8ec(void);                 /* FUN_0047e8ec (in-slice; declared in body) */
extern word_t sk_runtime_0029fb80(void);                 /* FUN_0029fb80 */
extern word_t sk_runtime_004ac960(void);                 /* FUN_004ac960 */
extern word_t sk_runtime_003512c0(void);                 /* FUN_003512c0 */
extern word_t sk_runtime_004ac2d0(void);                 /* FUN_004ac2d0 */
extern word_t sk_runtime_004ab430(void);                 /* FUN_004ab430 */
extern word_t sk_runtime_004ab31c(void *p);              /* FUN_004ab31c */
extern word_t sk_runtime_0008e518(void);                 /* FUN_0008e518 */
extern word_t sk_runtime_0008e500(void);                 /* FUN_0008e500 */
extern word_t sk_runtime_0049df18_2(void *p);            /* FUN_0049df18 */
extern word_t sk_runtime_00350600_2(word_t a);           /* FUN_00350600 */

/* ------------------------------------------------------------------ *
 * 0x0047c528 — message dispatch switch on an op byte at obj+0x20.
 * ------------------------------------------------------------------ */

/* FUN_0047c528 @ 0x0047c528   (est. sk_r28_op_dispatch)
 * Ghidra: void FUN_0047c528(undefined8,undefined8,undefined8,undefined8,undefined8)
 * Reads the method pointer at obj+0x10 and a kind byte at obj+0x20; on the
 * default path builds a 5-word message (arg2..arg5 into a fresh object),
 * refs arg5, invokes the method, then tears the object down. On kinds 1/3
 * invokes the method with no message. Confidence: medium.
 * Notes: unaff_x20 = self (method-table owner); FUN_000026e8 releases the
 *   message object after the call. */
void sk_r28_0047c528(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5)
{
    word_t (*method)(void) = *(word_t (**)(void))(self + 0x10);
    (void)self;
}
