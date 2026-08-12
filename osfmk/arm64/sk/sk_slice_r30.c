/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel,
 * arm64e, image base 0) - the cL4 microkernel (GL1), "cL4 (679.100.61)".
 * Ground truth: Ghidra FUN_ names + addresses in program cl4_kernel.raw.
 * Slice R30: addresses 0x00490174 - 0x004961a0. This is the embedded Swift
 * runtime / _StringProcessing regex-matcher region (strings:
 * _StringProcessing_Match_swift, L4_ErrorCodeCapInvalid). The functions are
 * small fragments of the Swift runtime: boxed-value helpers, collection
 * growth, string/regex primitives, and shared strong retain/release/emplace
 * trampolines (FUN_0036b118/0036b270/0036a940 = Swift retain/release;
 * FUN_00117cc4 = memcpy). All names are estimates unless string-matched.
 *
 * Conventions: out-of-slice callees keep their FUN_ names as extern
 * identifiers (unprototyped, word_t result = x0); in-slice functions use
 * sk_r30_<addr> names. Decompiler register artifacts (extraout_xN, unaff_xN)
 * are modelled as locals/params. SoftwareBreakpoint fail-closed checks are
 * rendered as CL4_SWBP(addr). Confidence: medium unless a header says
 * otherwise. True-gap slice: most callees are out of range; every body ends
 * with a word_t return (0 for void semantics). */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>

typedef uint64_t word_t;
typedef uint32_t seL4_Word;
typedef unsigned char byte;
typedef unsigned long ulong;   /* Ghidra ulong -> used in a few bodies */
typedef unsigned int uint;     /* Ghidra uint  -> used in a few bodies */
typedef struct { uint64_t lo, hi; } wpair_t;   /* 16-byte (x0:x1) returns */
typedef uint64_t (*code)();

#define LZCOUNT(x)     ((unsigned long)__builtin_clzll((unsigned long)(x)))
#define CL4_FATAL()    __builtin_trap()
#define SCARRY8(a, b)  (__builtin_add_overflow((a), (b), &(unsigned long){0}))
#define SBORROW8(a, b) (__builtin_sub_overflow((a), (b), &(unsigned long){0}))

/* Ghidra SoftwareBreakpoint(1, addr) - fail-closed trap, does not return. */
static inline unsigned long CL4_SWBP(unsigned long addr)
{ (void)addr; __builtin_trap(); }

/* ------------------------------------------------------------------ *
 * String literals referenced by this slice (addresses of cL4 strings).
 * ------------------------------------------------------------------ */
extern char s_L4_ErrorCodeCapInvalid_006886c8[];
extern char s__StringProcessing_Match_swift_005e1fe0[];
extern char s_lower_upper_005e1f90[];
extern char s_upperBound_output_005e2540[];

/* ------------------------------------------------------------------ *
 * Data singletons referenced by this slice. `&DAT_x` = address; the
 * decompiler's `_DAT_x` (value read) is written `DAT_x`.
 * ------------------------------------------------------------------ */
extern word_t DAT_004baeb0;
extern word_t DAT_004bbf40;
extern word_t DAT_004c2450;
extern word_t DAT_005a3640;
extern word_t DAT_005a3c68;
extern word_t DAT_005a3c88;
extern word_t DAT_005a3c90;
extern word_t DAT_005a3ca0;
extern word_t DAT_005a3cc0;
extern word_t DAT_005a3cc8;
extern word_t DAT_005a5eba;
extern word_t DAT_005a5ec8;
extern word_t DAT_0060e208;
extern word_t DAT_0060e230;
extern word_t DAT_0064c040;
extern word_t DAT_00657778;
extern word_t DAT_00687c08;
extern word_t DAT_00687c30;
extern word_t DAT_00687c58;
extern word_t DAT_00687c80;
extern word_t DAT_00687ca8;
extern word_t DAT_00687cd0;
extern word_t DAT_00688700;

/* ------------------------------------------------------------------ *
 * Out-of-slice callees (bodies reconstructed by their range workers).
 * Unprototyped AAPCS64 externs; word_t result = x0.
 * ------------------------------------------------------------------ */
extern word_t FUN_00002534();
extern word_t FUN_000026e8();
extern word_t FUN_00002804();
extern word_t FUN_00002818();
extern word_t FUN_00002834();
extern word_t FUN_00012568();
extern word_t FUN_00019850();
extern word_t FUN_00019858();
extern word_t FUN_0001a1c8();
extern word_t FUN_00027754();
extern word_t FUN_00027788();
extern word_t FUN_000277b8();
extern word_t FUN_00041138();
extern word_t FUN_0006a4c0();
extern word_t FUN_0006b3f4();
extern word_t FUN_0006b42c();
extern word_t FUN_0006b6f4();
extern word_t FUN_0006f6b4();
extern word_t FUN_00077024();
extern word_t FUN_000776cc();
extern word_t FUN_0007c028();
extern word_t FUN_0007c1a4();
extern word_t FUN_0007c1c4();
extern word_t FUN_000839d8();
extern word_t FUN_000839f8();
extern word_t FUN_0008409c();
extern word_t FUN_000840b8();
extern word_t FUN_00084180();
extern word_t FUN_00084220();
extern word_t FUN_00084234();
extern word_t FUN_000867ec();
extern word_t FUN_00086840();
extern word_t FUN_0008e388();
extern word_t FUN_0008e500();
extern word_t FUN_0008e518();
extern word_t FUN_0009461c();
extern word_t FUN_000a6e14();
extern word_t FUN_000a6f88();
extern word_t FUN_000aa4ec();
extern word_t FUN_000b4390();
extern word_t FUN_000b43d0();
extern word_t FUN_000b44cc();
extern word_t FUN_000b4594();
extern word_t FUN_000b45b0();
extern word_t FUN_000dbc98();
extern word_t FUN_000dbed0();
extern word_t FUN_000dce50();
extern word_t FUN_000e15d8();
extern word_t FUN_000e72b0();
extern word_t FUN_000f5d84();
extern word_t FUN_000f5e08();
extern word_t FUN_00100c04();
extern word_t FUN_00100c38();
extern word_t FUN_00100efc();
extern word_t FUN_00117cc4();
extern word_t FUN_00167404();
extern word_t FUN_0019e93c();
extern word_t FUN_001a0754();
extern word_t FUN_001a84f4();
extern word_t FUN_001a8564();
extern word_t FUN_001afa84();
extern word_t FUN_001d3fd0();
extern word_t FUN_00208418();
extern word_t FUN_0024c9c0();
extern word_t FUN_00267510();
extern word_t FUN_00270c08();
extern word_t FUN_0029c014();
extern word_t FUN_0029fa0c();
extern word_t FUN_0029fb80();
extern word_t FUN_002a0cf8();
extern word_t FUN_002a49a8();
extern word_t FUN_002a4ab4();
extern word_t FUN_002a9ba8();
extern word_t FUN_002acbb8();
extern word_t FUN_002bbf08();
extern word_t FUN_002bd8f0();
extern word_t FUN_00310924();
extern word_t FUN_00310d68();
extern word_t FUN_00310d98();
extern word_t FUN_00310e08();
extern word_t FUN_00310e20();
extern word_t FUN_003192d8();
extern word_t FUN_00319808();
extern word_t FUN_0031b050();
extern word_t FUN_00349a18();
extern word_t FUN_0034aee4();
extern word_t FUN_0034b0c4();
extern word_t FUN_0034b318();
extern word_t FUN_0034c6d4();
extern word_t FUN_0034cb88();
extern word_t FUN_0034cc24();
extern word_t FUN_0034cff4();
extern word_t FUN_0034d090();
extern word_t FUN_003504a0();
extern word_t FUN_003504ac();
extern word_t FUN_003504c4();
extern word_t FUN_003504d0();
extern word_t FUN_003504e8();
extern word_t FUN_00350518();
extern word_t FUN_0035053c();
extern word_t FUN_00350548();
extern word_t FUN_0035056c();
extern word_t FUN_003505c4();
extern word_t FUN_00350618();
extern word_t FUN_00350774();
extern word_t FUN_003507e0();
extern word_t FUN_00350878();
extern word_t FUN_003508b4();
extern word_t FUN_003508e4();
extern word_t FUN_003508fc();
extern word_t FUN_00350968();
extern word_t FUN_00350980();
extern word_t FUN_003509a4();
extern word_t FUN_003509b0();
extern word_t FUN_003509ec();
extern word_t FUN_00350a04();
extern word_t FUN_00350a28();
extern word_t FUN_00350af4();
extern word_t FUN_00350b54();
extern word_t FUN_00350b9c();
extern word_t FUN_00350bc0();
extern word_t FUN_00350c5c();
extern word_t FUN_00350d94();
extern word_t FUN_00351124();
extern word_t FUN_00351274();
extern word_t FUN_00351354();
extern word_t FUN_00351384();
extern word_t FUN_00351390();
extern word_t FUN_0035139c();
extern word_t FUN_00351450();
extern word_t FUN_00351488();
extern word_t FUN_003515d8();
extern word_t FUN_00351790();
extern word_t FUN_0035199c();
extern word_t FUN_00351aec();
extern word_t FUN_00351b78();
extern word_t FUN_00351d18();
extern word_t FUN_00351db4();
extern word_t FUN_00351dfc();
extern word_t FUN_00351e3c();
extern word_t FUN_00351f34();
extern word_t FUN_00352290();
extern word_t FUN_003527b8();
extern word_t FUN_00352840();
extern word_t FUN_00352c68();
extern word_t FUN_00352e9c();
extern word_t FUN_00352ea8();
extern word_t FUN_0035300c();
extern word_t FUN_0035310c();
extern word_t FUN_00353238();
extern word_t FUN_0035354c();
extern word_t FUN_003535a8();
extern word_t FUN_00353cfc();
extern word_t FUN_00353d14();
extern word_t FUN_00353ff4();
extern word_t FUN_00354a34();
extern word_t FUN_00354d5c();
extern word_t FUN_00354e0c();
extern word_t FUN_00354ef8();
extern word_t FUN_00354f1c();
extern word_t FUN_00355538();
extern word_t FUN_00356370();
extern word_t FUN_0035638c();
extern word_t FUN_00356bb0();
extern word_t FUN_00357c74();
extern word_t FUN_00357cb4();
extern word_t FUN_003583e8();
extern word_t FUN_00358454();
extern word_t FUN_0035847c();
extern word_t FUN_00359018();
extern word_t FUN_003593c0();
extern word_t FUN_003625e4();
extern word_t FUN_00362acc();
extern word_t FUN_00365b6c();
extern word_t FUN_0036986c();
extern word_t FUN_0036a908();
extern word_t FUN_0036a940();
extern word_t FUN_0036a9a0();
extern word_t FUN_0036b118();
extern word_t FUN_0036b270();
extern word_t FUN_0036b6ac();
extern word_t FUN_00370538();
extern word_t FUN_003722e4();
extern word_t FUN_003743d0();
extern word_t FUN_00377824();
extern word_t FUN_00377bec();
extern word_t FUN_003a25d4();
extern word_t FUN_003a261c();
extern word_t FUN_00407ab8();
extern word_t FUN_004080b0();
extern word_t FUN_00412eec();
extern word_t FUN_00412fe4();
extern word_t FUN_00414bd8();
extern word_t FUN_00419c78();
extern word_t FUN_0041a0dc();
extern word_t FUN_0041afc8();
extern word_t FUN_0041aff0();
extern word_t FUN_0041bfb4();
extern word_t FUN_0041c0c0();
extern word_t FUN_0041c190();
extern word_t FUN_0041c1c4();
extern word_t FUN_0041c28c();
extern word_t FUN_0041c29c();
extern word_t FUN_0041c2ac();
extern word_t FUN_0041c2c8();
extern word_t FUN_0041c2e4();
extern word_t FUN_0041cb78();
extern word_t FUN_0042b708();
extern word_t FUN_00436fc8();
extern word_t FUN_00445e64();
extern word_t FUN_00455438();
extern word_t FUN_0045567c();
extern word_t FUN_00455abc();
extern word_t FUN_00455ac8();
extern word_t FUN_00455b88();
extern word_t FUN_004588cc();
extern word_t FUN_00458940();
extern word_t FUN_00458a90();
extern word_t FUN_00458cb8();
extern word_t FUN_00458cd4();
extern word_t FUN_00458d04();
extern word_t FUN_00458d10();
extern word_t FUN_00458d30();
extern word_t FUN_00458d40();
extern word_t FUN_00460e20();
extern word_t FUN_00460e30();
extern word_t FUN_004619fc();
extern word_t FUN_004630c4();
extern word_t FUN_00465294();
extern word_t FUN_00466244();
extern word_t FUN_00469918();
extern word_t FUN_004730e4();
extern word_t FUN_004766ec();
extern word_t FUN_004775d0();
extern word_t FUN_0047c62c();
extern word_t FUN_0047cdbc();
extern word_t FUN_0047ce4c();
extern word_t FUN_0047cf0c();
extern word_t FUN_0047d358();
extern word_t FUN_004816a8();
extern word_t FUN_0048525c();
extern word_t FUN_0048f61c();
extern word_t FUN_0048fe4c();
extern word_t FUN_0049747c();
extern word_t FUN_004974c4();
extern word_t FUN_004995e4();
extern word_t FUN_0049a530();
extern word_t FUN_0049a550();
extern word_t FUN_0049a624();
extern word_t FUN_0049a758();
extern word_t FUN_0049c35c();
extern word_t FUN_0049c704();
extern word_t FUN_0049c714();
extern word_t FUN_0049c7fc();
extern word_t FUN_0049c838();
extern word_t FUN_0049c850();
extern word_t FUN_0049c874();
extern word_t FUN_0049ca14();
extern word_t FUN_0049ca44();
extern word_t FUN_0049ca58();
extern word_t FUN_0049d1ec();
extern word_t FUN_0049d248();
extern word_t FUN_0049e2d4();
extern word_t FUN_0049e2f0();
extern word_t FUN_004a3268();
extern word_t FUN_004a32c4();
extern word_t FUN_004a32ec();
extern word_t FUN_004a3318();
extern word_t FUN_004a3340();
extern word_t FUN_004a3368();
extern word_t FUN_004a3390();
extern word_t FUN_004a34b4();
extern word_t FUN_004a3588();
extern word_t FUN_004a4214();
extern word_t FUN_004a42a0();
extern word_t FUN_004a4ab4();
extern word_t FUN_004a4ac4();
extern word_t FUN_004a4b14();
extern word_t FUN_004a4b70();
extern word_t FUN_004aa5f8();
extern word_t FUN_004aa610();
extern word_t FUN_004aa6c4();
extern word_t FUN_004aa794();
extern word_t FUN_004aa7bc();
extern word_t FUN_004aa83c();
extern word_t FUN_004aa95c();
extern word_t FUN_004aab60();
extern word_t FUN_004aab98();
extern word_t FUN_004aac40();
extern word_t FUN_004aaccc();
extern word_t FUN_004aad30();
extern word_t FUN_004aada4();
extern word_t FUN_004aafc8();
extern word_t FUN_004ab034();
extern word_t FUN_004ab090();
extern word_t FUN_004ab0f0();
extern word_t FUN_004ab128();
extern word_t FUN_004ab18c();
extern word_t FUN_004ab1b4();
extern word_t FUN_004ab260();
extern word_t FUN_004ab26c();
extern word_t FUN_004ab304();
extern word_t FUN_004ab448();
extern word_t FUN_004ab55c();
extern word_t FUN_004ab5d4();
extern word_t FUN_004ab618();
extern word_t FUN_004ab630();
extern word_t FUN_004ab65c();
extern word_t FUN_004ab800();
extern word_t FUN_004ab8c8();
extern word_t FUN_004ab920();
extern word_t FUN_004ab9e0();
extern word_t FUN_004aba28();
extern word_t FUN_004aba88();
extern word_t FUN_004abacc();
extern word_t FUN_004abb1c();
extern word_t FUN_004abb28();
extern word_t FUN_004abb34();
extern word_t FUN_004abbb8();
extern word_t FUN_004abc6c();
extern word_t FUN_004abdb8();
extern word_t FUN_004abdc4();
extern word_t FUN_004abef0();
extern word_t FUN_004abf50();
extern word_t FUN_004abfa8();
extern word_t FUN_004abfc8();
extern word_t FUN_004ac0c0();
extern word_t FUN_004ac114();
extern word_t FUN_004ac120();
extern word_t FUN_004ac15c();
extern word_t FUN_004ac198();
extern word_t FUN_004ac228();
extern word_t FUN_004ac240();
extern word_t FUN_004ac2d0();
extern word_t FUN_004ac318();
extern word_t FUN_004ac324();
extern word_t FUN_004ac41c();
extern word_t FUN_004ac538();
extern word_t FUN_004ac61c();
extern word_t FUN_004ac7b0();
extern word_t FUN_004ac810();
extern word_t FUN_004ac824();
extern word_t FUN_004ac830();
extern word_t FUN_004ac8e8();
extern word_t FUN_004ac8fc();
extern word_t FUN_004ac91c();
extern word_t FUN_004ac9e4();
extern word_t FUN_004aca18();
extern word_t FUN_004acab4();
extern word_t FUN_004acb20();
extern word_t FUN_004acb3c();
extern word_t FUN_004acbe4();
extern word_t FUN_004acc9c();
extern word_t FUN_004acccc();

/* ------------------------------------------------------------------ *
 * In-slice forward declarations (defined below in sk_slice_r30.c).
 * ------------------------------------------------------------------ */
static word_t sk_r30_00490174(word_t unaff_x20, word_t unaff_x22 /* unaff_x22: dest array register-global */);
static word_t sk_r30_00490268(word_t arg_a, word_t arg_b);
static word_t sk_r30_00490600(char kind);
static word_t sk_r30_0049063c(word_t param_1, word_t param_2, word_t param_3, word_t param_4,
                              long param_5, word_t param_6, long unaff_x25 /* self register-global */);
static word_t sk_r30_00490970(word_t unaff_x20 /* unaff_x20: self/context register-global */);
static word_t sk_r30_00490a04(word_t *unaff_x20 /* unaff_x20: self/context register-global */);
static word_t sk_r30_00490ae0(word_t *unaff_x20 /* unaff_x20: self/context */);
static word_t sk_r30_00490b0c(word_t self, word_t param_2, long value);
static word_t sk_r30_00490b14(word_t element, word_t index, word_t param_3, word_t param_4,
                              word_t collection, word_t unaff_x19, word_t unaff_x20 /* register-globals */);
static word_t sk_r30_00490b78(word_t param_1, word_t param_2,
                              word_t param_3, word_t param_4, word_t param_5);
static word_t sk_r30_00490b98(word_t base, word_t count, word_t cand_end,
                              word_t arg4, word_t arg5, long ctx,
                              word_t *out_hi /* upper word of 16-byte result */);
static word_t sk_r30_00490c18(word_t *param_1);
static word_t sk_r30_00490c44(word_t unaff_x19 /* unaff_x19: store pointer register-global */,
                              word_t unaff_x20 /* unaff_x20: key/value context register-global */);
static word_t sk_r30_00490c8c(word_t *param_1, word_t param_2, word_t param_3,
                              word_t unaff_x20 /* unaff_x20: self/context register-global */);
static word_t sk_r30_00490cb8(word_t *param_1, word_t *param_2, word_t *unaff_x20 /* unaff_x20: self */);
static word_t sk_r30_00490d28(word_t *obj);
static word_t sk_r30_00490d58(word_t *param_1, word_t *param_2, word_t *unaff_x20 /* unaff_x20: context register-global */);
static word_t sk_r30_00490dac(word_t *param_1, word_t param_2, word_t param_3,
                              word_t param_4, word_t param_5, word_t param_6);
static word_t sk_r30_00490dfc(wpair_t *out, word_t *ctx /* unaff_x20 */);
static word_t sk_r30_00490e40(word_t param_1, word_t param_2, word_t *param_3,
                              word_t *unaff_x19 /* self register-global */,
                              word_t *unaff_x20 /* context register-global */);
static word_t sk_r30_00490ea8(word_t param_1, word_t param_2, word_t param_3);
static word_t sk_r30_00490efc(word_t param_1,
                              word_t in_x3 /* register-global */,
                              long in_x4 /* register-global */,
                              long unaff_x22 /* register-global */,
                              long unaff_x23 /* register-global */);
static word_t sk_r30_00490fe0(word_t param_1, word_t *unaff_x20 /* unaff_x20: self */,
                              word_t unaff_x21 /* unaff_x21 */, word_t unaff_x22 /* unaff_x22 */);
static word_t sk_r30_004910bc(word_t param_1, word_t param_2, word_t param_3,
                              long unaff_x21 /* unaff_x21: self/context register-global */,
                              uint unaff_w24 /* unaff_w24: self/context register-global */);
static word_t sk_r30_0049115c(word_t param_1, word_t param_2, word_t param_3, word_t param_4, word_t param_5);
static word_t sk_r30_004911b0(word_t param_1, word_t param_2, word_t param_3,
                              word_t param_4, word_t *out /* extraout_x1 */,
                              word_t unaff_x21 /* context register-global */);
static word_t sk_r30_00491288(word_t unaff_x30 /* context register-global */);
static word_t sk_r30_0049153c(void);
static word_t sk_r30_0049156c(word_t param_1, word_t param_2, word_t param_3,
                              word_t unaff_x19 /* unaff_x19: value key register-global */,
                              word_t unaff_x20 /* unaff_x20: key register-global */);
static word_t sk_r30_00491600(word_t unaff_x20 /* unaff_x20: self/context register-global */);
static word_t sk_r30_00491644(word_t param_1);
static word_t sk_r30_00491688(long param_1, word_t param_2, word_t param_3);
static word_t sk_r30_004916f4(word_t *param_1, word_t param_2);
static word_t sk_r30_00491704(void);
static word_t sk_r30_0049174c(word_t unaff_x30 /* context register-global */);
static word_t sk_r30_004917d8(word_t unaff_x30 /* register-global */);
static word_t sk_r30_00491864(word_t unaff_x20 /* unaff_x20: element value register-global */);
static word_t sk_r30_004918ac(void);
static word_t sk_r30_004918ec(word_t *unaff_x20 /* unaff_x20: self */);
static word_t sk_r30_004918f0(long unaff_x20 /* unaff_x20: self/context register-global */);
static word_t sk_r30_00491914(word_t param_1, word_t *param_2);
static word_t sk_r30_004919f0(word_t param_1, word_t param_2, word_t param_3,
                              word_t unaff_x20 /* self/context */);
static word_t sk_r30_00491abc(word_t param_1, word_t param_2, word_t param_3,
                              long ctx /* unaff_x20 */);
static word_t sk_r30_00491b58(word_t param_1);
static word_t sk_r30_00491b88(word_t unaff_x20 /* unaff_x20: container register-global */);
static word_t sk_r30_00491bb4(void);
static word_t sk_r30_00491bb8(void);
static word_t sk_r30_00491bd4(ulong param_1, char param_2,
                              long *unaff_x20 /* unaff_x20: self/context register-global */);
static word_t sk_r30_00491c84(word_t in_x8, word_t in_x9, word_t in_x16,
                              word_t unaff_x19, word_t unaff_x20,
                              word_t unaff_x25, word_t unaff_x30 /* register-globals */);
static word_t sk_r30_00491db4(word_t param_1, word_t param_2, word_t param_3,
                              word_t param_4, word_t param_5, word_t param_6,
                              word_t param_7, word_t param_8,
                              word_t *out_x8, word_t reg_x9, word_t reg_x16,
                              word_t unaff_x21, word_t *unaff_x24);
static word_t sk_r30_00491f48(void);
static word_t sk_r30_00492038(ulong param_1);
static word_t sk_r30_0049204c(void);
static word_t sk_r30_00492078(unsigned char *param_1, word_t *param_2);
static word_t sk_r30_0049214c(void);
static word_t sk_r30_004921bc(long param_1);
static word_t sk_r30_004922d8(word_t param_1, word_t unaff_x20, word_t unaff_x29, word_t unaff_x30 /* register-globals */);
static word_t sk_r30_00492614(word_t reg_x19, uint reg_w20, word_t reg_x24,
                              word_t reg_x30, word_t reg_40a4);
static word_t sk_r30_00492704(code unaff_x19 /* context code pointer */);
static word_t sk_r30_00492758(word_t unaff_x30 /* register-global */);
static word_t sk_r30_00492850(word_t param_1,
                              word_t in_x4 /* in_x4: indirect callback fn pointer */,
                              word_t in_x7 /* in_x7: context pointer */,
                              word_t extraout_x8 /* extraout_x8: stack offset carried from prior call */,
                              word_t unaff_x21 /* unaff_x21: guard register-global */);
static word_t sk_r30_00492920(long param_1, word_t param_2, code *param_3,
                              word_t param_4, word_t param_5, word_t param_6,
                              long extraout_x8_00 /* register carry-over */,
                              long extraout_x8_01 /* register carry-over */,
                              long extraout_x9 /* register carry-over */,
                              long extraout_x16 /* register carry-over */,
                              code *extraout_x8_02 /* register carry-over */,
                              long unaff_x21 /* register-global */);
static word_t sk_r30_00492a2c(word_t in_x3, word_t unaff_x30);
static word_t sk_r30_00492b3c(word_t *param_1, word_t param_2, word_t param_3, word_t param_4,
                              word_t param_5, code *param_6, word_t param_7, word_t param_8,
                              long param_9,
                              long unaff_x21 /* unaff_x21: self/context register-global */);
static word_t sk_r30_00492c6c(word_t in_x3, word_t in_x4, word_t unaff_x21, word_t unaff_x30 /* register-globals */);
static word_t sk_r30_00492e18(word_t *pair_out /* 16-byte result buffer */,
                              word_t unaff_x20 /* context */);
static word_t sk_r30_00492eec(word_t param_1, word_t param_2, word_t param_3,
                              word_t unaff_x19 /* tag mask */,
                              word_t unaff_x30 /* context register-global */);
static word_t sk_r30_00493354(word_t param_1);
static word_t sk_r30_0049341c(word_t param_1, word_t unaff_x21 /* unaff_x21: mask register-global */);
static word_t sk_r30_004934a8(word_t param_1, ulong param_2,
                              ulong extraout_x1 /* register carry-over */,
                              long extraout_x1_00 /* register carry-over */,
                              ulong extraout_x8 /* register carry-over */,
                              long extraout_x9 /* register carry-over */,
                              ulong unaff_x21 /* register-global */,
                              ulong unaff_x22 /* register-global */);
static word_t sk_r30_00493d30(word_t param_1, word_t param_2, word_t param_3, word_t param_4,
                              word_t unaff_x19 /* unaff_x19 */);
static word_t sk_r30_00493d7c(word_t param_1, word_t param_2, word_t param_3, word_t param_4);
static word_t sk_r30_00493dfc(word_t param_1, word_t param_2, word_t param_3, word_t param_4,
                              word_t unaff_x30 /* register-global */);
static word_t sk_r30_00493fa0(word_t unaff_x20 /* context */, word_t reg_x8,
                              word_t reg_x16);
static word_t sk_r30_00494240(word_t *unaff_x20 /* context array */,
                              word_t unaff_x30 /* context register-global */);
static word_t sk_r30_0049466c(word_t param_1, long param_2, word_t param_3, word_t param_4,
                              word_t *unaff_x20 /* context register-global */);
static word_t sk_r30_0049478c(void);
static word_t sk_r30_00494790(void);
static word_t sk_r30_004947b8(void);
static word_t sk_r30_004947bc(void);
static word_t sk_r30_004947e4(void);
static word_t sk_r30_004947e8(void);
static word_t sk_r30_00494810(code in_x4 /* x4 callback */,
                              word_t *extraout_x8 /* result buffer */,
                              long unaff_x21 /* context register-global */,
                              word_t unaff_x30 /* context register-global */,
                              word_t in_98, word_t in_a0, word_t in_a8,
                              word_t in_b0, word_t in_b8);
static word_t sk_r30_004948e0(void);
static word_t sk_r30_004948e4(void);
static word_t sk_r30_0049490c(code *in_x6 /* register-global */,
                              word_t *extraout_x8 /* register carry-over */,
                              long unaff_x21 /* register-global */,
                              word_t unaff_x30 /* register-global */,
                              word_t in_stack_00000090, word_t in_stack_00000098,
                              word_t in_stack_000000a0, word_t in_stack_000000a8,
                              word_t in_stack_000000b0);
static word_t sk_r30_00494a1c(word_t param_1, word_t param_2, word_t param_3, word_t param_4,
                              word_t param_5, word_t param_6, code *param_7,
                              word_t *extraout_x8 /* caller buffer */, word_t unaff_x30);
static word_t sk_r30_00494b44(word_t param_1, word_t param_2, word_t param_3,
                              word_t unaff_x30 /* unaff_x30: link/self register-global */);
static word_t sk_r30_00494cc4(byte param_1);
static word_t sk_r30_00494d1c(word_t param_1, word_t param_2,
                              word_t param_3, word_t param_4);
static word_t sk_r30_00494d68(char kind);
static word_t sk_r30_00494dd0(char param_1);
static word_t sk_r30_00494e2c(void);
static word_t sk_r30_00494ea8(unsigned char param_1, code *param_2);
static word_t sk_r30_00494ef0(code *in_x3, word_t *unaff_x20 /* unaff_x20: self */);
static word_t sk_r30_00494f3c(word_t param_1, char param_2, ulong *param_3, byte param_4);
static word_t sk_r30_004950f0(uint32_t param_1, word_t unaff_x20 /* unaff_x20: bitmap base register-global */);
static word_t sk_r30_0049513c(word_t param_1, word_t param_2, word_t param_3);
static word_t sk_r30_0049516c(word_t param_1, word_t param_2, word_t param_3,
                              word_t unaff_x19 /* context register-global */);
static word_t sk_r30_00495298(word_t in_x5 /* register */, word_t in_x6 /* register */,
                              word_t in_x7 /* register: code * */);
static word_t sk_r30_00495388(uint param_1, word_t param_2);
static word_t sk_r30_00495400(code *unaff_x19 /* unaff_x19: callback register-global */);
static word_t sk_r30_00495464(void);
static word_t sk_r30_004954d0(void);
static word_t sk_r30_0049552c(word_t param_1, byte param_2, word_t param_3);
static word_t sk_r30_00495598(word_t unaff_x20 /* self/context */, word_t in_x4,
                              word_t reg_x8, uint extraout_w8, uint extraout_w9);
static word_t sk_r30_00495634(word_t unaff_x20 /* context register-global */,
                              word_t unaff_x24 /* context register-global */,
                              uint extraout_w8, uint extraout_w9,
                              code extraout_x8);
static word_t sk_r30_004956c0(word_t param_1, word_t param_2, word_t param_3, word_t param_4,
                              word_t param_5);
static word_t sk_r30_00495768(word_t param_1, word_t param_2, word_t param_3,
                              word_t param_4, word_t param_5, word_t param_6,
                              word_t param_7,
                              word_t unaff_x30 /* unaff_x30: context register-global */);
static word_t sk_r30_00495810(code *extraout_x8 /* register carry-over */,
                              ulong unaff_x24 /* register-global */,
                              word_t extraout_d0 /* register carry-over */,
                              word_t extraout_var /* register carry-over */);
static word_t sk_r30_004958a8(word_t in_x3);
static word_t sk_r30_00495940(word_t in_x3 /* in_x3: input register x3 */);
static word_t sk_r30_004959d8(void);
static word_t sk_r30_00495a74(void);
static word_t sk_r30_00495ab0(void);
static word_t sk_r30_00495aec(word_t param_1, word_t param_2, uint param_3, word_t param_4,
                              word_t param_5, word_t param_6, word_t param_7, word_t param_8,
                              word_t param_9, word_t param_10, word_t param_11, word_t param_12,
                              word_t param_13, word_t param_14, unsigned char param_15,
                              word_t in_stack_000000a8 /* stack-passed register */,
                              word_t in_stack_000000b0 /* stack-passed register: code * */);
static word_t sk_r30_00495bcc(word_t param_1, word_t param_2, word_t param_3, word_t param_4);
static word_t sk_r30_00495c48(long param_1, code *param_2);
static word_t sk_r30_00495ca4(word_t param_1, word_t param_2, word_t param_3, word_t param_4,
                              word_t unaff_x20 /* unaff_x20 */);
static word_t sk_r30_004961a0(long param_1);

/* In-slice FUN_ aliases: a few bodies call a sibling by its Ghidra FUN_<addr>
 * name; these macros route them to the in-slice definition. */
#define FUN_00490174 sk_r30_00490174
#define FUN_00490268 sk_r30_00490268
#define FUN_00490600 sk_r30_00490600
#define FUN_0049063c sk_r30_0049063c
#define FUN_00490970 sk_r30_00490970
#define FUN_00490a04 sk_r30_00490a04
#define FUN_00490ae0 sk_r30_00490ae0
#define FUN_00490b0c sk_r30_00490b0c
#define FUN_00490b14 sk_r30_00490b14
#define FUN_00490b78 sk_r30_00490b78
#define FUN_00490b98 sk_r30_00490b98
#define FUN_00490c18 sk_r30_00490c18
#define FUN_00490c44 sk_r30_00490c44
#define FUN_00490c8c sk_r30_00490c8c
#define FUN_00490cb8 sk_r30_00490cb8
#define FUN_00490d28 sk_r30_00490d28
#define FUN_00490d58 sk_r30_00490d58
#define FUN_00490dac sk_r30_00490dac
#define FUN_00490dfc sk_r30_00490dfc
#define FUN_00490e40 sk_r30_00490e40
#define FUN_00490ea8 sk_r30_00490ea8
#define FUN_00490efc sk_r30_00490efc
#define FUN_00490fe0 sk_r30_00490fe0
#define FUN_004910bc sk_r30_004910bc
#define FUN_0049115c sk_r30_0049115c
#define FUN_004911b0 sk_r30_004911b0
#define FUN_00491288 sk_r30_00491288
#define FUN_0049153c sk_r30_0049153c
#define FUN_0049156c sk_r30_0049156c
#define FUN_00491600 sk_r30_00491600
#define FUN_00491644 sk_r30_00491644
#define FUN_00491688 sk_r30_00491688
#define FUN_004916f4 sk_r30_004916f4
#define FUN_00491704 sk_r30_00491704
#define FUN_0049174c sk_r30_0049174c
#define FUN_004917d8 sk_r30_004917d8
#define FUN_00491864 sk_r30_00491864
#define FUN_004918ac sk_r30_004918ac
#define FUN_004918ec sk_r30_004918ec
#define FUN_004918f0 sk_r30_004918f0
#define FUN_00491914 sk_r30_00491914
#define FUN_004919f0 sk_r30_004919f0
#define FUN_00491abc sk_r30_00491abc
#define FUN_00491b58 sk_r30_00491b58
#define FUN_00491b88 sk_r30_00491b88
#define FUN_00491bb4 sk_r30_00491bb4
#define FUN_00491bb8 sk_r30_00491bb8
#define FUN_00491bd4 sk_r30_00491bd4
#define FUN_00491c84 sk_r30_00491c84
#define FUN_00491db4 sk_r30_00491db4
#define FUN_00491f48 sk_r30_00491f48
#define FUN_00492038 sk_r30_00492038
#define FUN_0049204c sk_r30_0049204c
#define FUN_00492078 sk_r30_00492078
#define FUN_0049214c sk_r30_0049214c
#define FUN_004921bc sk_r30_004921bc
#define FUN_004922d8 sk_r30_004922d8
#define FUN_00492614 sk_r30_00492614
#define FUN_00492704 sk_r30_00492704
#define FUN_00492758 sk_r30_00492758
#define FUN_00492850 sk_r30_00492850
#define FUN_00492920 sk_r30_00492920
#define FUN_00492a2c sk_r30_00492a2c
#define FUN_00492b3c sk_r30_00492b3c
#define FUN_00492c6c sk_r30_00492c6c
#define FUN_00492e18 sk_r30_00492e18
#define FUN_00492eec sk_r30_00492eec
#define FUN_00493354 sk_r30_00493354
#define FUN_0049341c sk_r30_0049341c
#define FUN_004934a8 sk_r30_004934a8
#define FUN_00493d30 sk_r30_00493d30
#define FUN_00493d7c sk_r30_00493d7c
#define FUN_00493dfc sk_r30_00493dfc
#define FUN_00493fa0 sk_r30_00493fa0
#define FUN_00494240 sk_r30_00494240
#define FUN_0049466c sk_r30_0049466c
#define FUN_0049478c sk_r30_0049478c
#define FUN_00494790 sk_r30_00494790
#define FUN_004947b8 sk_r30_004947b8
#define FUN_004947bc sk_r30_004947bc
#define FUN_004947e4 sk_r30_004947e4
#define FUN_004947e8 sk_r30_004947e8
#define FUN_00494810 sk_r30_00494810
#define FUN_004948e0 sk_r30_004948e0
#define FUN_004948e4 sk_r30_004948e4
#define FUN_0049490c sk_r30_0049490c
#define FUN_00494a1c sk_r30_00494a1c
#define FUN_00494b44 sk_r30_00494b44
#define FUN_00494cc4 sk_r30_00494cc4
#define FUN_00494d1c sk_r30_00494d1c
#define FUN_00494d68 sk_r30_00494d68
#define FUN_00494dd0 sk_r30_00494dd0
#define FUN_00494e2c sk_r30_00494e2c
#define FUN_00494ea8 sk_r30_00494ea8
#define FUN_00494ef0 sk_r30_00494ef0
#define FUN_00494f3c sk_r30_00494f3c
#define FUN_004950f0 sk_r30_004950f0
#define FUN_0049513c sk_r30_0049513c
#define FUN_0049516c sk_r30_0049516c
#define FUN_00495298 sk_r30_00495298
#define FUN_00495388 sk_r30_00495388
#define FUN_00495400 sk_r30_00495400
#define FUN_00495464 sk_r30_00495464
#define FUN_004954d0 sk_r30_004954d0
#define FUN_0049552c sk_r30_0049552c
#define FUN_00495598 sk_r30_00495598
#define FUN_00495634 sk_r30_00495634
#define FUN_004956c0 sk_r30_004956c0
#define FUN_00495768 sk_r30_00495768
#define FUN_00495810 sk_r30_00495810
#define FUN_004958a8 sk_r30_004958a8
#define FUN_00495940 sk_r30_00495940
#define FUN_004959d8 sk_r30_004959d8
#define FUN_00495a74 sk_r30_00495a74
#define FUN_00495ab0 sk_r30_00495ab0
#define FUN_00495aec sk_r30_00495aec
#define FUN_00495bcc sk_r30_00495bcc
#define FUN_00495c48 sk_r30_00495c48
#define FUN_00495ca4 sk_r30_00495ca4
#define FUN_004961a0 sk_r30_004961a0
/* Part 0: SKR30 chunk 0 transcription.
 * Each body is a faithful English C rendering of the pre-fetched Ghidra
 * decompile. Confidence: medium unless noted. */

/* FUN_00490174 @ 0x00490174  (est. sk_r30_grow_collection_copy)
 * Ghidra: void FUN_00490174(void)
 * Iterates the element collection rooted at unaff_x20+0x18 (stride 0x178),
 * copies each element through a box/unbox pipeline (00458d30/00490268/
 * 00458d40), and appends 0x160-byte records into the growing output buffer
 * at unaff_x22 (grown via 0049a550 when capacity is exhausted). Finalizes
 * with 00419c78/0008e500. unaff_x20 = source collection register-global,
 * unaff_x22 = destination array register-global.
 * Confidence: medium */
static word_t sk_r30_00490174(word_t unaff_x20, word_t unaff_x22 /* unaff_x22: dest array register-global */)
{
    word_t uVar1;
    uint32_t uVar2;
    word_t uVar3;
    word_t uVar4;
    word_t lVar5;
    word_t lVar6;
    byte auStack_458[376];
    byte auStack_2d8[352];
    byte auStack_178[376];

    uVar3 = FUN_0008e518();
    lVar6 = *(word_t *)(unaff_x20 + 0x18);
    lVar5 = *(word_t *)(lVar6 + 0x10);
    FUN_00466244();
    if (lVar5 != 0) {
        FUN_000840b8();
        FUN_0049a550();
        lVar6 = lVar6 + 0x20;
        do {
            FUN_00117cc4(auStack_178, lVar6, 0x178);
            FUN_00458d30(auStack_178, auStack_458);
            FUN_00490268((word_t)auStack_2d8, (word_t)auStack_178);
            FUN_00458d40(auStack_178);
            uVar1 = *(word_t *)(unaff_x22 + 0x10);
            if (*(word_t *)(unaff_x22 + 0x18) >> 1 <= uVar1) {
                uVar4 = FUN_0006b42c();
                FUN_0049a550(uVar4, uVar1 + 1, 1);
            }
            *(word_t *)(unaff_x22 + 0x10) = uVar1 + 1;
            FUN_00117cc4(unaff_x22 + uVar1 * 0x160 + 0x20, auStack_2d8, 0x160);
            lVar6 = lVar6 + 0x178;
            lVar5 = lVar5 + -1;
        } while (lVar5 != 0);
    }
    uVar2 = FUN_00419c78();
    FUN_0008e500(unaff_x22, uVar2 & 1, uVar3);
    return 0;
}

/* FUN_00490b14 @ 0x00490b14  (est. sk_r30_emplace_element_at)
 * Ghidra: void FUN_00490b14(long param_1,ulong param_2,undefined8 param_3,undefined8 param_4,long param_5)
 * Inserts `element` (param_1) at computed index into the collection at
 * param_5 (count at +0x10, stride 0x58), stamping the element's +0x58/+0x60
 * fields with the caller's register-globals (unaff_x20/unaff_x19). Traps
 * fail-closed on negative index (0x490b74) or index past the count
 * (0x490b78). unaff_x19/unaff_x20 = context register-globals.
 * Confidence: medium */
static word_t sk_r30_00490b14(word_t element, word_t index, word_t param_3, word_t param_4,
                              word_t collection, word_t unaff_x19, word_t unaff_x20 /* register-globals */)
{
    word_t lVar2;

    if ((word_t)index >> 63 != 0) {   /* (long)param_2 < 0 */
        CL4_SWBP(0x490b74);
    }
    if (index < *(word_t *)(collection + 0x10)) {
        lVar2 = FUN_00350a28();
        FUN_0049c704(collection + lVar2 * 0x58 + 0x20, element);
        *(word_t *)(element + 0x58) = unaff_x20;
        *(word_t *)(element + 0x60) = unaff_x19;
        FUN_0036b270();
        return 0;
    }
    CL4_SWBP(0x490b78);
}

/* FUN_00490d58 @ 0x00490d58  (est. sk_r30_boxed_value_copy)
 * Ghidra: void FUN_00490d58(undefined8 *param_1,undefined8 *param_2)
 * Builds a boxed value via 00490dac from the 2 words at *param_2 plus the
 * 3 context words at *unaff_x20, then stores the resulting 5 words into
 * param_1. unaff_x20 = self/context register-global.
 * Confidence: medium */
static word_t sk_r30_00490d58(word_t *param_1, word_t *param_2, word_t *unaff_x20 /* unaff_x20: context register-global */)
{
    word_t local_48, uStack_40, local_38, uStack_30, local_28;

    FUN_00490dac(&local_48, *param_2, param_2[1], *unaff_x20, unaff_x20[1], unaff_x20[2]);
    param_1[1] = uStack_40;
    param_1[0] = local_48;
    param_1[3] = uStack_30;
    param_1[2] = local_38;
    param_1[4] = local_28;
    return 0;
}

/* FUN_0049115c @ 0x0049115c  (est. sk_r30_string_builder_emit)
 * Ghidra: void FUN_0049115c(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,undefined8 param_5)
 * Emits into the string builder: prepares (003509ec), notifies 0049d1ec,
 * computes a 16-byte payload via 00100efc, and hands the two words plus
 * param_3/param_4 to 00491704 for append.
 * Confidence: medium */
static word_t sk_r30_0049115c(word_t param_1, word_t param_2, word_t param_3, word_t param_4, word_t param_5)
{
    byte auVar1[16];

    FUN_003509ec();
    FUN_0049d1ec(0, param_5);
    auVar1[0] = 0;
    auVar1[1] = 0;
    auVar1[2] = 0;
    auVar1[3] = 0;
    auVar1[4] = 0;
    auVar1[5] = 0;
    auVar1[6] = 0;
    auVar1[7] = 0;
    auVar1[8] = 0;
    auVar1[9] = 0;
    auVar1[10] = 0;
    auVar1[11] = 0;
    auVar1[12] = 0;
    auVar1[13] = 0;
    auVar1[14] = 0;
    auVar1[15] = 0;
    /* 00100efc returns 16 bytes (x0:x1); split into two words */
    *(word_t *)auVar1 = FUN_00100efc();
    FUN_00491704();
    return 0;
}

/* FUN_004916f4 @ 0x004916f4  (est. sk_r30_value_release)
 * Ghidra: void FUN_004916f4(undefined8 *param_1,undefined8 param_2)
 * Releases the value: passes param_2 and the first word of *param_1 to
 * 00455ac8 (a retain/release trampoline).
 * Confidence: medium */
static word_t sk_r30_004916f4(word_t *param_1, word_t param_2)
{
    FUN_00455ac8(param_2, *param_1);
    return 0;
}

/* FUN_00491914 @ 0x00491914  (est. sk_r30_box_copy_or_init)
 * Ghidra: void FUN_00491914(undefined8 param_1,long *param_2)
 * Builds a boxed value at param_1. If param_2[2] (a target object) is null,
 * initializes via 004a4b70; otherwise locates the target through
 * 0049d248/0036b270/00362acc (trapping 0x4919f0 on failure), copies its
 * 0x90-byte metadata into the box via 004a4ab4, and runs the standard
 * retain/release/copy dance before copying the 0x90-byte box out.
 * Confidence: medium */
static word_t sk_r30_00491914(word_t param_1, word_t *param_2)
{
    word_t lVar5;
    word_t uVar2, uVar3, lVar4;
    byte auStack_1e0[144];
    byte auStack_150[144];
    byte auStack_c0[144];

    lVar5 = param_2[2];
    if (lVar5 == 0) {
        FUN_004a4b70(auStack_c0);
    } else {
        uVar2 = FUN_0049d248(0, *(word_t *)(*param_2 + 0x38));
        uVar3 = FUN_0036b270(lVar5);
        lVar4 = FUN_00362acc(uVar3, uVar2);
        if (lVar4 == 0) {
            CL4_SWBP(0x4919f0);
        }
        FUN_00117cc4(auStack_1e0, lVar5 + 0x10, 0x90);
        FUN_004a4ab4(auStack_1e0, auStack_c0);
        FUN_0036b118(lVar5);
        FUN_00117cc4(auStack_150, auStack_1e0, 0x90);
        FUN_0001a1c8(auStack_150);
        FUN_00117cc4(auStack_c0, auStack_150, 0x90);
    }
    FUN_00117cc4(param_1, auStack_c0, 0x90);
    return 0;
}

/* FUN_00491c84 @ 0x00491c84  (est. sk_r30_context_switch_setup)
 * Ghidra: void FUN_00491c84(void)
 * Heavily register-global-driven context setup: allocates/retains objects
 * (0036a940/0036b270/0036b118 Swift runtime trampolines), computes an
 * allocation length from a capability byte at in_x16+0x50
 * (uVar2+0x20 & ~uVar2), stores unaff_x19/unaff_x20 into the new object,
 * installs a handler at unaff_x25+0x18, and transitions via 0049153c.
 * Several calls are indirect through unresolved symbols (SUB_54ffff60f100041f,
 * extraout_x9/extraout_x8_00) — modelled as raw indirect calls.
 * Confidence: low   Notes: many register-artifact params; indirect calls. */
static word_t sk_r30_00491c84(word_t in_x8, word_t in_x9, word_t in_x16,
                              word_t unaff_x19, word_t unaff_x20,
                              word_t unaff_x25, word_t unaff_x30 /* register-globals */)
{
    word_t uVar1;
    word_t uVar2;
    word_t lVar3;
    word_t uVar4;

    FUN_0008e518();
    FUN_00350c5c();
    FUN_000a6f88();
    lVar3 = *(word_t *)(in_x8 + 0x40);
    ((code)0x54ffff60f100041f)();              /* indirect call through unresolved SUB_54ffff60f100041f */
    FUN_00359018(0x6861b0);
    FUN_0036a940();
    FUN_004ac2d0();
    uVar1 = FUN_00027754();
    FUN_004aa95c(uVar1, uVar1);
    uVar1 = FUN_00377824();
    *(word_t *)(unaff_x25 + 0x10) = uVar1;
    FUN_000e15d8();
    ((code)in_x9)();                           /* indirect call through extraout_x9 */
    uVar2 = (word_t)*(byte *)(in_x16 + 0x50);
    uVar4 = uVar2 + 0x20 & (uVar2 ^ 0xffffffffffffffff);
    lVar3 = FUN_0036a940(0x6861d8, uVar4 + lVar3, uVar2 | 7);
    *(word_t *)(lVar3 + 0x10) = unaff_x19;
    *(word_t *)(lVar3 + 0x18) = unaff_x20;
    FUN_0035056c(*(word_t *)(in_x16 + 0x20), lVar3 + uVar4);
    ((code)in_x8)();                           /* indirect call through extraout_x8_00 */
    *(word_t *)(unaff_x25 + 0x18) = (word_t)FUN_0049c7fc;
    *(word_t *)(unaff_x25 + 0x20) = lVar3;
    uVar1 = FUN_0049153c();
    FUN_0008e500(uVar1, unaff_x30);
    return 0;
}

/* FUN_004922d8 @ 0x004922d8  (est. sk_r30_dispatch_switch)
 * Ghidra: void FUN_004922d8(undefined8 param_1)
 * A large switch-driven dispatch. Reads a discriminator (extraout_w16 /
 * lVar3 from 004ac198) and dispatches across ~0x11 cases that build boxed
 * values (0036a940 + field stores), grow an output array (0006b42c/
 * 004abb28/0049a530), retain/release elements (0036b270/0036b118), and
 * finally emit via 00358454. case 0xb walks a 0x20-stride element list,
 * and case 0xc recurses back into the dispatcher (goto code_r0x004922dc).
 * DAT_004c2450/DAT_004baeb0 are 16-byte pair reads (low word + next word).
 * Confidence: low   Notes: heavy register-artifact locals; switch state machine. */
static word_t sk_r30_004922d8(word_t param_1, word_t unaff_x20, word_t unaff_x29, word_t unaff_x30 /* register-globals */)
{
    word_t uVar1;
    word_t lVar3;
    byte *puVar4;
    word_t uVar5;
    word_t uVar6;
    word_t extraout_x1;
    word_t extraout_x8_00, extraout_x8_01, extraout_x8_02, extraout_x8_03, extraout_x8_04, extraout_x8_05;
    uint32_t extraout_w16;
    uint32_t extraout_w8;
    byte *puVar7;
    word_t *puVar8;
    word_t *puVar9;
    word_t puVar10;
    byte auVar11[16];
    byte *in_stack_00000010;
    word_t in_stack_000000e0;
    word_t in_stack_000000e8;
    byte stack0x00000010[8];
    byte stack0x00000030[8];

    *(word_t *)(auVar11 + 8) = unaff_x30;
    *(word_t *)auVar11 = param_1;

code_r0x004922dc:
    FUN_003583e8(*(word_t *)auVar11, *(word_t *)(auVar11 + 8));
    in_stack_000000e0 = unaff_x29;
    in_stack_000000e8 = extraout_x1;
    lVar3 = FUN_004ac198();
    puVar4 = (byte *)&DAT_00657778;
    switch (extraout_w16 & 0xfffffffe | (uint32_t)lVar3 >> 2 & 1) {
    default:
        puVar7 = *(byte **)(lVar3 + 0x10);
        puVar4 = puVar7;
    LAB_004923ac:
        FUN_0036b270(puVar7);
    case 7:
    case 8:
    case 9:
    case 10:
    case 0xd:
    case 0xe:
    case 0xf:
    case 0x10:
    switchD_0049231c_caseD_7:
        FUN_00358454(puVar4, in_stack_000000e8);
        return 0;
    case 1:
        FUN_004ab260();
        puVar7 = *(byte **)(extraout_x8_04 + 0x10);
        puVar4 = puVar7;
        goto LAB_004923ac;
    case 2:
        FUN_004aab98();
        uVar5 = *(word_t *)(extraout_x8_00 + 0x30);
        break;
    case 3:
        FUN_004aab98();
        uVar5 = *(word_t *)(extraout_x8_02 + 0x68);
        break;
    case 4:
        FUN_004aab98();
        uVar5 = *(word_t *)(extraout_x8_03 + 0x10);
        break;
    case 5:
        FUN_004aab98();
        uVar5 = *(word_t *)(extraout_x8_05 + 0x90);
        uVar6 = *(word_t *)(extraout_x8_05 + 0x98);
        FUN_004aa6c4();
        FUN_00002534();
        FUN_00355538();
        puVar4 = (byte *)FUN_0036a940();
        uVar1 = DAT_004c2450;
        *(word_t *)(puVar4 + 0x18) = *((word_t *)&DAT_004c2450 + 1);
        *(word_t *)(puVar4 + 0x10) = uVar1;
        *(word_t *)(puVar4 + 0x20) = uVar5;
        *(word_t *)(puVar4 + 0x28) = uVar6;
        FUN_0036b270(uVar6 & unaff_x20);
        goto LAB_00492398;
    case 6:
        FUN_004aab98();
        uVar5 = *(word_t *)(extraout_x8_01 + 0x58);
        break;
    case 0xb:
        FUN_004ab260();
        FUN_004abb34();
        lVar3 = FUN_00412eec();
        FUN_00460e30(&stack0x00000030);
        puVar9 = *(word_t **)(lVar3 + 0x10);
        if (puVar9 == (word_t *)0x0) {
            FUN_0036b118(lVar3);
        } else {
            in_stack_00000010 = (byte *)&DAT_00657778;
            FUN_004abfa8();
            FUN_0049a530();
            puVar10 = 0;
            do {
                puVar4 = in_stack_00000010;
                if (*(word_t **)(lVar3 + 0x10) <= (word_t *)puVar10) {
                    CL4_SWBP(0x492504);
                }
                puVar8 = *(word_t **)(lVar3 + puVar10 * 8 + 0x20);
                FUN_0036b270((word_t)puVar8 & 0xfffffffffffffff);
                uVar5 = FUN_0048f61c(puVar8);
                FUN_004ab26c();
                if ((extraout_w8 & 0xfffffffe | (uint32_t)uVar5 >> 2 & 1) == 0xc) {
                    FUN_0036b118((word_t)puVar8 & 0xfffffffffffffff);
                } else {
                    FUN_00002834(0x687b68);
                    uVar6 = FUN_0036a940();
                    *(word_t *)(uVar6 + 0x10) = uVar5;
                    *(word_t **)(uVar6 + 0x18) = puVar8;
                    uVar5 = uVar6 | 0x6000000000000000;
                }
                uVar6 = *(word_t *)(puVar4 + 0x10);
                in_stack_00000010 = puVar4;
                if (*(word_t *)(puVar4 + 0x18) >> 1 <= uVar6) {
                    FUN_0006b42c();
                    puVar8 = (word_t *)&stack0x00000010;
                    FUN_004abb28();
                    FUN_0049a530();
                }
                puVar4 = in_stack_00000010;
                puVar10 = puVar10 + 1;
                *(word_t *)(in_stack_00000010 + 0x10) = uVar6 + 1;
                *(word_t *)(in_stack_00000010 + uVar6 * 8 + 0x20) = uVar5;
            } while (puVar9 != (word_t *)puVar10);
            FUN_004acc9c();
            if (puVar9 != puVar8) {
                CL4_SWBP(0x4924bc);
            }
        }
        goto switchD_0049231c_caseD_7;
    case 0xc:
        goto switchD_0049231c_caseD_c;
    }
    FUN_004aa6c4();
    FUN_00002534();
    FUN_00359018();
    puVar4 = (byte *)FUN_0036a940();
    uVar1 = DAT_004baeb0;
    *(word_t *)(puVar4 + 0x18) = *((word_t *)&DAT_004baeb0 + 1);
    *(word_t *)(puVar4 + 0x10) = uVar1;
    *(word_t *)(puVar4 + 0x20) = uVar5;
LAB_00492398:
    puVar7 = (byte *)(uVar5 & unaff_x20);
    goto LAB_004923ac;
switchD_0049231c_caseD_c:
    FUN_004ab260();
    unaff_x29 = in_stack_000000e0;
    *(word_t *)auVar11 = FUN_00358454(*(word_t *)(extraout_x8_00 + 0x10) /* extraout_x8 */, in_stack_000000e8);
    goto code_r0x004922dc;
}

/* FUN_00492c6c @ 0x00492c6c  (est. sk_r30_context_entry_setup)
 * Ghidra: void FUN_00492c6c(void)
 * Entry/teardown setup: reads a 16-byte descriptor from 00353cfc, calls into
 * 00310d68/00319808, runs a descriptor function pointer (auVar3+8), and
 * conditionally (unaff_x21 == 0) clears an output word-pair or performs a
 * dispatch via 00077024 on an indirect vtable call. Finishes with
 * 00353d14(unaff_x30). Several calls are indirect through unresolved symbols.
 * Confidence: low   Notes: register-artifact locals; indirect calls. */
static word_t sk_r30_00492c6c(word_t in_x3, word_t in_x4, word_t unaff_x21, word_t unaff_x30 /* register-globals */)
{
    int32_t iVar1;
    word_t lVar2;
    word_t *extraout_x8;
    word_t extraout_x8_00, extraout_x8_01, extraout_x8_02;
    code *extraout_x8_03, *extraout_x8_04;
    word_t extraout_x9, extraout_x16, extraout_x16_00;
    byte auVar3[16];
    byte auStack_20[32];

    auVar3[0] = 0; auVar3[1] = 0; auVar3[2] = 0; auVar3[3] = 0;
    auVar3[4] = 0; auVar3[5] = 0; auVar3[6] = 0; auVar3[7] = 0;
    auVar3[8] = 0; auVar3[9] = 0; auVar3[10] = 0; auVar3[11] = 0;
    auVar3[12] = 0; auVar3[13] = 0; auVar3[14] = 0; auVar3[15] = 0;
    /* 00353cfc returns 16 bytes (x0:x1) */
    *(word_t *)auVar3 = FUN_00353cfc();
    lVar2 = in_x4;
    FUN_0007c028();
    ((code)0x54ffff60f100041f)(*(word_t *)(extraout_x8_00 + 0x40)); /* indirect call through unresolved SUB */
    FUN_000aa4ec();
    FUN_00310d68(0, lVar2);
    FUN_000a6f88();
    FUN_0007c1a4();
    ((code)0x54ffff60f100041f)();            /* indirect call through unresolved SUB */
    FUN_0034aee4();
    FUN_00319808(*(word_t *)auVar3, auStack_20);
    FUN_00351f34();
    FUN_00365b6c(extraout_x9 - extraout_x8_01, auStack_20, extraout_x8_02 + 8, in_x3, 7);
    (*(code *)(auVar3 + 8))(extraout_x9 - extraout_x8_01);
    FUN_000e15d8(*(word_t *)(extraout_x16 + 8));
    (*extraout_x8_03)();
    if (unaff_x21 == 0) {
        FUN_00351390();
        iVar1 = FUN_000839f8();
        if (iVar1 == 1) {
            FUN_00100c38(*(word_t *)(extraout_x16_00 + 8));
            (*extraout_x8_04)();
            extraout_x8[1] = 0;
            extraout_x8[0] = 0;
            extraout_x8[3] = 0;
            extraout_x8[2] = 0;
        } else {
            extraout_x8[3] = in_x4;
            FUN_00077024(extraout_x8);
            (**(code **)(*(word_t *)(in_x4 + -8) + 0x20))();
        }
    }
    FUN_00353d14(unaff_x30);
    return 0;
}

/* FUN_00493dfc @ 0x00493dfc  (est. sk_r30_box_create)
 * Ghidra: void FUN_00493dfc(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)
 * Creates a boxed value. Reads a range descriptor from 00084220
 * (low = lVar4, high = lVar6), traps on invalid ranges (0x493f98/0x493f9c/
 * 0x493fa0), then branches on the descriptor upper bound:
 *  - 0x7fffffffffffffff: fixed-size boxes for length 0/1/other, stamping
 *    the 0x10..0x48 fields and a discriminant byte 0x80020100>>(flag<<3).
 *  - otherwise: computes lVar6-lVar4, and for count==1 marks +0x50=0x80,
 *    else builds a two-part box (auVar12/auVar13 splits) with 0x6000... tag.
 * Finishes by 004acccc/00084234 with the box OR-tagged 0x3000000000000000.
 * Confidence: medium */
static word_t sk_r30_00493dfc(word_t param_1, word_t param_2, word_t param_3, word_t param_4,
                              word_t unaff_x30 /* register-global */)
{
    word_t uVar1;
    uint32_t uVar2;
    word_t lVar4;
    word_t uVar5;
    word_t lVar6;
    uint32_t uVar7;
    uint32_t uVar8;
    word_t uVar9;
    word_t uVar10;
    byte auVar11[16];
    byte auVar12[12];
    byte auVar13[12];
    word_t extraout_x8;

    uVar8 = (uint32_t)(param_3 >> 0x20);
    uVar7 = (uint32_t)param_3;
    auVar11[0] = 0; auVar11[1] = 0; auVar11[2] = 0; auVar11[3] = 0;
    auVar11[4] = 0; auVar11[5] = 0; auVar11[6] = 0; auVar11[7] = 0;
    auVar11[8] = 0; auVar11[9] = 0; auVar11[10] = 0; auVar11[11] = 0;
    auVar11[12] = 0; auVar11[13] = 0; auVar11[14] = 0; auVar11[15] = 0;
    /* 00084220 returns 16 bytes (x0:x1) */
    *(word_t *)auVar11 = FUN_00084220();
    lVar6 = *(word_t *)(auVar11 + 8);
    lVar4 = *(word_t *)auVar11;
    if ((lVar4 >> 63) || (lVar4 == lVar6)) {
        CL4_SWBP(0x493f98);
    }
    if (__builtin_sub_overflow(lVar6, 1, &(word_t){0})) {
        CL4_SWBP(0x493f9c);
    }
    uVar2 = uVar7 & 3;
    if (lVar6 == 0x7fffffffffffffff) {
        FUN_004aab60();
        uVar5 = FUN_0036a940();
        if (lVar4 == 1) {
            *(word_t *)(uVar5 + 0x10) = 1;
            *(word_t *)(uVar5 + 0x20) = 0;
            *(word_t *)(uVar5 + 0x18) = 0;
            *(word_t *)(uVar5 + 0x30) = 0;
            *(word_t *)(uVar5 + 0x28) = 0;
            *(word_t *)(uVar5 + 0x48) = 0;
            *(word_t *)(uVar5 + 0x38) = 0x8000000000000000;
        } else {
            if (lVar4 != 0) {
                FUN_0041cb78();
                FUN_00351790();
                FUN_004ac318();
                FUN_0001a1c8();
                FUN_004abef0();
                uVar10 = 0x2000000000000000;
                goto LAB_00493f6c;
            }
            *(word_t *)(uVar5 + 0x18) = 0;
            *(word_t *)(uVar5 + 0x10) = 0;
            *(word_t *)(uVar5 + 0x28) = 0;
            *(word_t *)(uVar5 + 0x20) = 0;
            *(word_t *)(uVar5 + 0x30) = 0;
            *(word_t *)(uVar5 + 0x38) = 0x8000000000000000;
            *(word_t *)(uVar5 + 0x48) = 0;
        }
        *(word_t *)(uVar5 + 0x40) = 0;
    } else {
        if (__builtin_sub_overflow(lVar6, lVar4, &(word_t){0})) {
            CL4_SWBP(0x493fa0);
        }
        uVar10 = param_4;
        FUN_004aab60(lVar6 - lVar4);
        if (extraout_x8 == 1) {
            uVar5 = FUN_0036a940();
            FUN_0041cb78();
            FUN_00351790();
            FUN_004ac318();
            FUN_0001a1c8();
            FUN_004abef0();
            *(word_t *)(uVar5 + 0x38) = 0;
            *(byte *)(uVar5 + 0x50) = 0x80;
            goto LAB_00493f74;
        }
        uVar5 = FUN_0036a940();
        FUN_0041cb78();
        FUN_00351790();
        if (lVar4 == 0) {
            FUN_004ab9e0();
            FUN_0001a1c8();
            FUN_004abef0();
            uVar10 = 0x4000000000000000;
            goto LAB_00493f6c;
        }
        FUN_004ac318();
        auVar12[0] = 0; auVar12[1] = 0; auVar12[2] = 0; auVar12[3] = 0;
        auVar12[4] = 0; auVar12[5] = 0; auVar12[6] = 0; auVar12[7] = 0;
        auVar12[8] = 0; auVar12[9] = 0; auVar12[10] = 0; auVar12[11] = 0;
        *(word_t *)auVar12 = FUN_0001a1c8();
        uVar1 = ((word_t)uVar8 << 32) | (word_t)uVar7;   /* CONCAT44(uVar8,uVar7) */
        uVar9 = uVar10;
        FUN_0041cb78();
        FUN_00351790();
        FUN_004ab9e0();
        auVar13[0] = 0; auVar13[1] = 0; auVar13[2] = 0; auVar13[3] = 0;
        auVar13[4] = 0; auVar13[5] = 0; auVar13[6] = 0; auVar13[7] = 0;
        auVar13[8] = 0; auVar13[9] = 0; auVar13[10] = 0; auVar13[11] = 0;
        *(word_t *)auVar13 = FUN_0001a1c8();
        *(word_t *)(uVar5 + 0x10) = *(word_t *)auVar12;
        *(word_t *)(uVar5 + 0x18) = (word_t)(*(uint32_t *)(auVar12 + 8) & 1);
        *(word_t *)(uVar5 + 0x20) = uVar1;
        *(word_t *)(uVar5 + 0x28) = uVar10;
        *(word_t *)(uVar5 + 0x30) = *(word_t *)auVar13;
        *(word_t *)(uVar5 + 0x38) = (word_t)(*(uint32_t *)(auVar13 + 8) & 1) | 0x6000000000000000;
        *(word_t *)(uVar5 + 0x40) = ((word_t)uVar8 << 32) | (word_t)uVar7;
        *(word_t *)(uVar5 + 0x48) = uVar9;
    }
LAB_00493f6c:
    *(word_t *)(uVar5 + 0x38) = uVar10;
    goto LAB_00493f70;
LAB_00493f70:
    *(byte *)(uVar5 + 0x50) = (byte)(0x80020100 >> (word_t)(uVar2 << 3));
LAB_00493f74:
    *(word_t *)(uVar5 + 0x58) = param_4;
    FUN_004acccc();
    FUN_00084234(uVar5 | 0x3000000000000000, unaff_x30);
    return 0;
}

/* FUN_004947e4 @ 0x004947e4  (est. sk_r30_box_destroy_thunk)
 * Ghidra: void FUN_004947e4(void)
 * Thin wrapper that delegates entirely to 00494810 (in-slice teardown).
 * Confidence: high */
static word_t sk_r30_004947e4(void)
{
    /* Delegates to the 9-param in-slice teardown; register/stack artifacts
     * (callback, buffers, context) are undefined in this thin wrapper. */
    FUN_00494810(0, 0, 0, 0, 0, 0, 0, 0, 0);
    return 0;
}

/* FUN_00494cc4 @ 0x00494cc4  (est. sk_r30_finalize_kind)
 * Ghidra: void FUN_00494cc4(char param_1)
 * Runs 004ab65c then 00494b44 with kind=8 and a boolean derived from
 * param_1 == 1 (marks whether the value is a singleton/unique box).
 * Confidence: medium */
static word_t sk_r30_00494cc4(byte param_1)
{
    FUN_004ab65c();
    FUN_00494b44(8, param_1 == 0x01, 0, 0);
    return 0;
}

/* FUN_004950f0 @ 0x004950f0  (est. sk_r30_bitmap_set)
 * Ghidra: void FUN_004950f0(uint param_1)
 * Sets one bit in a two-word bitmap at unaff_x20: bit < 0x40 sets the low
 * word (+8), bit >= 0x40 (up to 0x7f) sets the high word (+0x10). unaff_x20
 * = bitmap base register-global.
 * Confidence: high */
static word_t sk_r30_004950f0(uint32_t param_1, word_t unaff_x20 /* unaff_x20: bitmap base register-global */)
{
    word_t uVar1;

    if ((param_1 & 0xff) < 0x40) {
        *(word_t *)(unaff_x20 + 8) = *(word_t *)(unaff_x20 + 8) | (word_t)1 << ((word_t)param_1 & 0x3f);
        return 0;
    }
    uVar1 = 0;
    if ('?' < (char)param_1) {
        uVar1 = (word_t)1 << ((word_t)(param_1 - 0x40) & 0x3f);
    }
    *(word_t *)(unaff_x20 + 0x10) = *(word_t *)(unaff_x20 + 0x10) | uVar1;
    return 0;
}

/* FUN_0049552c @ 0x0049552c  (est. sk_r30_box_create_small)
 * Ghidra: undefined8 FUN_0049552c(undefined8 param_1,undefined1 param_2,undefined8 param_3)
 * Allocates a small box via 0036a940, stores param_1 and the byte param_2,
 * transitions through 0049153c with the box OR-tagged 0x3000000000000004,
 * and releases param_1 (0036b270). Returns the transition result.
 * Confidence: medium */
static word_t sk_r30_0049552c(word_t param_1, byte param_2, word_t param_3)
{
    word_t uVar1;
    word_t uVar2;

    FUN_004ac91c();
    uVar1 = FUN_0036a940();
    *(word_t *)(uVar1 + 0x10) = param_1;
    *(byte *)(uVar1 + 0x18) = param_2;
    uVar2 = FUN_0049153c();
    FUN_0036b270(param_1);
    return uVar2;
}

/* FUN_004959d8 @ 0x004959d8  (est. sk_r30_regex_state_init)
 * Ghidra: void FUN_004959d8(void)
 * Initializes a regex-matcher state object allocated via 0036a940: pulls a
 * 16-byte descriptor from 0035199c (split into two words stored at +0x20
 * and +0x30), zeroes most fields, runs 004ab5d4/00084180/00491644/00351d18,
 * releases via 0036b118, and transitions via 0049153c with the object
 * OR-tagged 0x1000000000000000. in_x4 is a register-global arg.
 * Confidence: low   Notes: one register-global (in_x4); indirect call. */
static word_t sk_r30_004959d8(void)
{
    word_t in_x4;
    word_t uVar1;
    byte auVar2[16];

    auVar2[0] = 0; auVar2[1] = 0; auVar2[2] = 0; auVar2[3] = 0;
    auVar2[4] = 0; auVar2[5] = 0; auVar2[6] = 0; auVar2[7] = 0;
    auVar2[8] = 0; auVar2[9] = 0; auVar2[10] = 0; auVar2[11] = 0;
    auVar2[12] = 0; auVar2[13] = 0; auVar2[14] = 0; auVar2[15] = 0;
    /* 0035199c returns 16 bytes (x0:x1) */
    *(word_t *)auVar2 = FUN_0035199c();
    FUN_004aada4();
    uVar1 = FUN_0036a940();
    *(word_t *)(uVar1 + 0x10) = 0;
    *(word_t *)(uVar1 + 0x18) = 0;
    *(word_t *)(uVar1 + 0x20) = *(word_t *)(auVar2 + 8);
    *(byte *)(uVar1 + 0x28) = 0;
    FUN_004ab5d4(in_x4);
    FUN_00084180();
    ((code)in_x4)();                          /* indirect call through extraout_x8 */
    FUN_00491644(0);
    FUN_00351d18();
    FUN_0036b118();
    *(word_t *)(uVar1 + 0x30) = *(word_t *)auVar2;
    *(word_t *)(uVar1 + 0x40) = 0;
    *(word_t *)(uVar1 + 0x38) = 0;
    *(word_t *)(uVar1 + 0x50) = 0;
    *(word_t *)(uVar1 + 0x48) = 0;
    *(byte *)(uVar1 + 0x58) = 0;
    FUN_0049153c();
    return 0;
}
/* ==================== SKR30 chunk 1 (part_1.c) ==================== */

/* FUN_00490268 @ 0x00490268  (est. sk_r30_collection_copy_elements)
 * Ghidra: void FUN_00490268(void)
 * Copies a collection/element payload from a source descriptor into target
 * backing storage, dispatching on 6 representation cases; recursively copies
 * nested element arrays, growing backing buffers (stride 0x160 elems, header
 * +0x10 count/+0x18 capacity) as capacity is exceeded and retaining objects.
 * Confidence: low   Notes: heavy register-global/buffer artifacts; the
 *   recursive call carries two implicit args (auStack_738, &local_180) that
 *   the void signature hides; extraout_x1/extraout_x8 are register leftovers. */
static word_t sk_r30_00490268(word_t arg_a, word_t arg_b)
{
    word_t uVar1, lVar2, lVar8, lVar9, lVar11, uVar6;
    word_t puVar4, puVar10;
    word_t *ppuVar7;   /* decompile: undefined **ppuVar7 (pointer into local_8b0/local_a10) */
    uint uVar3;
    byte extraout_w1;             /* low byte carried from FUN_00490174 */
    word_t extraout_x8;           /* pointer leftover from a prior call */
    wpair_t auVar12, auVar13;
    word_t auStack_478[0x178 / 8];
    word_t auStack_738[0x178 / 8];
    word_t auStack_5d8[0x160 / 8];
    word_t auStack_528[0x160 / 8];
    word_t auStack_c0[0xb0 / 8];
    word_t local_300[0x178 / 8];
    word_t local_180[0x178 / 8];
    unsigned char *local_8b0[47];
    word_t **local_a10[44];
    byte local_178;

    auVar12 = ((wpair_t (*)())&FUN_0008e518)();
    ppuVar7 = (word_t *)auVar12.lo;
    FUN_00117cc4(auStack_478, ppuVar7, 0x178);
    uVar3 = FUN_00458d04(auStack_478);
    switch (uVar3) {
    default:
        puVar4 = FUN_00458d10(auStack_478);
        local_300[1] = *(word_t *)((char *)puVar4 + 8);
        local_300[0] = *(word_t *)puVar4;
        local_300[3] = *(word_t *)((char *)puVar4 + 24);
        local_300[2] = *(word_t *)((char *)puVar4 + 16);
        local_300[5] = *(word_t *)((char *)puVar4 + 40);
        local_300[4] = *(word_t *)((char *)puVar4 + 32);
        local_180[0] = sk_r30_00490174(arg_a, arg_b);
        local_178 = extraout_w1 & 1;
        FUN_004a3390(&local_180);
        goto LAB_00490348;
    case 1:
        uVar6 = FUN_00458d10(auStack_478);
        FUN_00117cc4(&local_180, uVar6, 0x178);
        FUN_004ab0f0(auStack_738);
        FUN_00117cc4();
        FUN_0048fe4c(auStack_5d8);
        FUN_00117cc4(local_a10, auStack_c0, 0xb0);
        FUN_0048fe4c(auStack_528);
        FUN_00117cc4(&local_300, auStack_5d8, 0x160);
        FUN_004a3368(&local_300);
        auVar13.hi = (word_t)&local_300;
        auVar13.lo = (word_t)local_8b0;
        break;
    case 2:
        uVar6 = FUN_00458d10(auStack_478);
        FUN_00117cc4(&local_300, uVar6, 0xb0);
        FUN_0048fe4c(&local_180);
        FUN_0049c850(&local_180);
LAB_00490348:
        auVar13.hi = (word_t)&local_180;
        auVar13.lo = (word_t)local_8b0;
        break;
    case 3:
        FUN_00458d10(auStack_478);
        FUN_004ac8e8();
        FUN_004a3340();
        goto LAB_00490364;
    case 4:
        FUN_00458d10(auStack_478);
        FUN_004ac8e8();
        FUN_004a3268();
LAB_00490364:
        FUN_00117cc4(&local_180, ppuVar7, 0x178);
        lVar9 = FUN_00458d10(&local_180);
        uVar6 = *(word_t *)(lVar9 + 8);
        FUN_00117cc4(local_8b0, &local_300, 0x160);
        FUN_0036b270(uVar6);
        goto LAB_004905c0;
    case 5: {
        word_t *plVar5 = (word_t *)FUN_00458d10(auStack_478);
        lVar9 = plVar5[0];
        lVar2 = plVar5[1];
        lVar11 = plVar5[4];
        lVar8 = *(word_t *)(lVar9 + 0x10);
        if (lVar8 != 0) {
            local_8b0[0] = (unsigned char *)&DAT_00657778;
            FUN_000840b8();
            FUN_0049a550();
            lVar9 = lVar9 + 0x20;
            puVar10 = (word_t)local_8b0[0];
            do {
                FUN_00117cc4(&local_180, lVar9, 0x178);
                FUN_00458d30(&local_180, &local_300);
                sk_r30_00490268((word_t)auStack_738, (word_t)&local_180);
                FUN_00458d40(&local_180);
                uVar1 = *(word_t *)((char *)puVar10 + 0x10);
                local_8b0[0] = (unsigned char *)puVar10;
                if (*(word_t *)((char *)puVar10 + 0x18) >> 1 <= uVar1) {
                    FUN_0006b42c();
                    FUN_000dbed0();
                    FUN_0049a550();
                }
                puVar10 = (word_t)local_8b0[0];
                ppuVar7 = (word_t *)local_8b0;
                *(word_t *)((char *)puVar10 + 0x10) = uVar1 + 1;
                FUN_00117cc4(local_8b0[0] + uVar1 * 0x160 + 0x20, auStack_738, 0x160);
                lVar9 = lVar9 + 0x178;
                lVar8 = lVar8 - 1;
            } while (lVar8 != 0);
        }
        lVar9 = *(word_t *)(lVar11 + 0x10);
        FUN_000776cc();
        if (lVar9 != 0) {
            local_a10[0] = (word_t **)ppuVar7;
            FUN_000840b8();
            FUN_0049a550();
            lVar11 = lVar11 + 0x20;
            ppuVar7 = (word_t *)local_a10[0];
            do {
                FUN_00117cc4(&local_300, lVar11, 0x178);
                FUN_00458d30(&local_300, local_8b0);
                sk_r30_00490268((word_t)auStack_5d8, (word_t)&local_300);
                FUN_00458d40(&local_300);
                puVar10 = ppuVar7[2];
                local_a10[0] = (word_t **)ppuVar7;
                if ((word_t)((ulong)ppuVar7[3] >> 1) <= puVar10) {
                    FUN_0006b42c();
                    FUN_000dbed0();
                    FUN_0049a550();
                }
                ppuVar7 = (word_t *)local_a10[0];
                local_a10[0][2] = (word_t *)(puVar10 + 1);
                FUN_00117cc4(local_a10[0] + puVar10 * 0x2c + 4, auStack_5d8, 0x160);
                lVar11 = lVar11 + 0x178;
                lVar9 = lVar9 - 1;
            } while (lVar9 != 0);
        }
        FUN_004ab18c();
        if ((char)lVar2 == '\0') {
            FUN_0036a940();
            FUN_004ab090();
            FUN_004a3318();
        } else if ((char)lVar2 == '\x01') {
            FUN_0036a940();
            FUN_004ab090();
            FUN_004a32ec();
        } else {
            FUN_0036a940();
            FUN_004ab090();
            FUN_004a32c4();
        }
        auVar13 = ((wpair_t (*)())&FUN_004ac7b0)();
        break;
    }
    }
    FUN_00117cc4(auVar13.lo, auVar13.hi, 0x160);
LAB_004905c0:
    FUN_00117cc4(extraout_x8, local_8b0, 0x160);
    FUN_0008e500(auVar12.hi);
    return 0;
}

/* FUN_00490b78 @ 0x00490b78  (est. sk_r30_array_capacity_check)
 * Ghidra: void FUN_00490b78(long param_1,long param_2,undefined8 param_3,undefined8 param_4,long param_5)
 * Range/capacity bounds check: traps if (param_1 + param_2) overflows or
 * exceeds the capacity stored at param_5+0x10; returns silently otherwise.
 * Confidence: medium   Notes: param_3/param_4 unused; fail-closed SWBP traps. */
static word_t sk_r30_00490b78(word_t param_1, word_t param_2,
                              word_t param_3, word_t param_4, word_t param_5)
{
    if (SCARRY8(param_1, param_2)) {
        CL4_SWBP(0x490b94);
    }
    if ((ulong)(param_1 + param_2) <= *(ulong *)(param_5 + 0x10)) {
        return 0;
    }
    CL4_SWBP(0x490b98);
}

/* FUN_00490dac @ 0x00490dac  (est. sk_r30_range_descriptor_store)
 * Ghidra: void FUN_00490dac(long *param_1,long param_2,long param_3,long param_4,long param_5,long param_6)
 * Stores a (lower,upper,stride,context,capacity-owner) range descriptor into
 * param_1[0..4] after validating lower>=0 and upper<=capacity at param_6+0x10,
 * retaining param_5 and param_6; traps on invalid bounds.
 * Confidence: medium   Notes: retains the two owner objects after the store. */
static word_t sk_r30_00490dac(word_t *param_1, word_t param_2, word_t param_3,
                              word_t param_4, word_t param_5, word_t param_6)
{
    if ((-1 < param_2) && (param_3 <= *(word_t *)(param_6 + 0x10))) {
        param_1[0] = param_2;
        param_1[1] = param_3;
        param_1[2] = param_4;
        param_1[3] = param_5;
        param_1[4] = param_6;
        FUN_0036b270(param_5);
        FUN_0036b270(param_6);
        return 0;
    }
    CL4_SWBP(0x490dfc);
}

/* FUN_004911b0 @ 0x004911b0  (est. sk_r30_string_process_desc)
 * Ghidra: undefined8 FUN_004911b0(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)
 * Processes a string/collection descriptor (param_1/param_2 as an 8-byte-pair
 * header) through the Match.NSString machinery; on the non-exception path
 * builds an output box (param_4 + hi) and flags it unboxed.
 * Confidence: low   Notes: unaff_x21 is a context register-global; the two
 *   wpair_t returns (FUN_000e15d8 / FUN_00491288) arrive in x0:x1. */
static word_t sk_r30_004911b0(word_t param_1, word_t param_2, word_t param_3,
                              word_t param_4, word_t *out /* extraout_x1 */,
                              word_t unaff_x21 /* context register-global */)
{
    word_t uVar1;
    word_t unaff_x23 = 0;
    wpair_t auVar2;
    word_t local_60 = param_1;
    word_t local_58 = param_2;

    uVar1 = FUN_00019850();
    FUN_000f5e08();
    FUN_004ab920();
    FUN_00445e64(&local_60, uVar1);
    FUN_003535a8();
    FUN_003a25d4(param_2);
    if (unaff_x21 == 0) {
        auVar2 = ((wpair_t (*)())&FUN_000e15d8)();
        unaff_x23 = sk_r30_0049115c(auVar2.lo, auVar2.hi, param_3, param_4, 0);
        auVar2 = ((wpair_t (*)())&FUN_00491288)(unaff_x23, param_4);
        if ((auVar2.lo & 1) == 0) {
            FUN_0036b118(unaff_x23);
            FUN_004aa610();
            out[0] = param_4;
            out[1] = auVar2.hi;
            *(unsigned char *)(out + 2) = 0;
            FUN_0036986c();
        }
    }
    return unaff_x23;
}

/* FUN_00491704 @ 0x00491704  (est. sk_r30_teardown_prologue)
 * Ghidra: undefined8 FUN_00491704(void)
 * Runs a fixed sequence of teardown/notify helpers and forwards the result of
 * FUN_0036a940() (an alloc/context probe) to sk_r30_00491abc.
 * Confidence: medium   Notes: result of FUN_0036a940 captured as the return. */
static word_t sk_r30_00491704(void)
{
    word_t uVar1;

    FUN_000867ec();
    FUN_000dce50();
    uVar1 = FUN_0036a940();
    FUN_00100efc();
    sk_r30_00491abc(0, 0, 0, uVar1);
    return uVar1;
}

/* FUN_004919f0 @ 0x004919f0  (est. sk_r30_box_value)
 * Ghidra: void FUN_004919f0(ulong param_1,undefined8 param_2,undefined8 param_3)
 * Boxes a value: stores it into a fresh box object allocated with tag
 * 0x6000000000000000 (heap pointer), zeroing slots 0x10/0x20 of the context
 * (unaff_x20); if the type tag already matches the `heapObject` representation
 * it releases the tag bits instead of re-boxing.
 * Confidence: medium   Notes: unaff_x20 is a self/context register-global. */
static word_t sk_r30_004919f0(word_t param_1, word_t param_2, word_t param_3,
                              word_t unaff_x20 /* self/context */)
{
    word_t uVar1;
    word_t uVar2;

    *(word_t *)(unaff_x20 + 0x10) = 0;
    *(word_t *)(unaff_x20 + 0x20) = 0;
    uVar1 = FUN_0048f61c();
    if ((((uint)(uVar1 >> 0x3b) & 0x1e) | ((uint)uVar1 >> 2 & 1)) == 0xc) {
        FUN_0036b118(param_1 & 0xfffffffffffffff);
    } else {
        uVar2 = FUN_0036a940(0x687b68, 0x20, 7);
        *(word_t *)(uVar2 + 0x10) = uVar1;
        *(word_t *)(uVar2 + 0x18) = param_1;
        uVar1 = uVar2 | 0x6000000000000000;
    }
    FUN_0036b118(param_3);
    FUN_0036b118(param_2);
    *(word_t *)(unaff_x20 + 0x18) = uVar1;
    return 0;
}

/* FUN_00491db4 @ 0x00491db4  (est. sk_r30_string_upper_bound_match)
 * Ghidra: void FUN_00491db4(undefined8 param_1..param_8)
 * String match helper: builds an "upperBound output" closure (s_upperBound_output
 * at 0x5e2540) via FUN_003722e4, runs the Match machinery through a code pointer,
 * then either zeroes the result box (match=1) or writes {*unaff_x24, bound}
 * into the output box and dispatches through the closure's witness table.
 * Confidence: low   Notes: heavy extraout register artifacts; the indirect call
 *   target SUB_54ffff60f100041f is an opaque constant; several extraout_xN and
 *   unaff_xN register-globals are modeled as trailing params. */
static word_t sk_r30_00491db4(word_t param_1, word_t param_2, word_t param_3,
                              word_t param_4, word_t param_5, word_t param_6,
                              word_t param_7, word_t param_8,
                              word_t *out_x8, word_t reg_x9, word_t reg_x16,
                              word_t unaff_x21, word_t *unaff_x24)
{
    int iVar1;
    word_t uVar2;
    word_t lVar3;
    word_t lVar4;
    wpair_t auVar5;
    word_t lVar3_prev;

    FUN_00353cfc();
    uVar2 = param_8;
    FUN_003504d0();
    uVar2 = FUN_00027754(uVar2);
    FUN_004ac810(uVar2, uVar2);
    lVar3 = FUN_00377824(0xff, reg_x9, param_7);
    lVar3_prev = lVar3;
    lVar4 = FUN_003722e4(0xff, 0x675628, lVar3, (word_t)s_upperBound_output_005e2540, 0);
    FUN_003508e4();
    FUN_00310d68();
    FUN_000a6f88();
    FUN_0007c1a4();
    ((word_t (*)())0x54ffff60f100041f)();
    FUN_0034b0c4();
    FUN_004a3588(param_8);
    auVar5 = ((wpair_t (*)())&FUN_0007c1c4)();
    ((word_t (*)(word_t, word_t, word_t, word_t, word_t, word_t, word_t))reg_x9)(
        auVar5.lo, auVar5.hi, param_3, param_4, param_5, param_7, param_8);
    if (unaff_x21 == 0) {
        auVar5 = ((wpair_t (*)())&FUN_00352290)();
        iVar1 = FUN_000839f8(auVar5.lo, auVar5.hi, lVar4);
        if (iVar1 == 1) {
            FUN_00351354(*(word_t *)(reg_x16 + 8));
            ((word_t (*)())reg_x9)();
            out_x8[4] = 0;
            out_x8[1] = 0;
            out_x8[0] = 0;
            out_x8[3] = 0;
            out_x8[2] = 0;
        } else {
            iVar1 = *(int *)(lVar4 + 0x30);
            out_x8[0] = *unaff_x24;
            out_x8[4] = lVar3_prev;
            uVar2 = FUN_00077024(out_x8 + 1);
            (**(word_t (**)(word_t, word_t, word_t))(*(word_t *)(lVar3_prev + -8) + 0x20))(
                uVar2, (word_t)unaff_x24 + (word_t)iVar1, lVar3_prev);
        }
    }
    FUN_00353d14(reg_x9);
    return 0;
}

/* FUN_00492614 @ 0x00492614  (est. sk_r30_retain_or_box)
 * Ghidra: void FUN_00492614(void)
 * Conditionally retains/boxes a value based on representation flags: on the
 * non-heap path wraps it in a fresh box tagged 0x6000000000000000 and stores the
 * owner; otherwise releases tag bits of (unaff_x19 & unaff_x24) and records a
 * different datum. Both paths finish with FUN_0035847c(uVar1, unaff_x30).
 * Confidence: low   Notes: condition flags (extraout_var) from FUN_004aba88;
 *   unaff_000040a4/unaff_w20 form a CONCAT44 address; &stack0x00000008 is a
 *   scratch stack slot. */
static word_t sk_r30_00492614(word_t reg_x19, uint reg_w20, word_t reg_x24,
                              word_t reg_x30, word_t reg_40a4)
{
    word_t uVar1;
    word_t uVar2;
    word_t uVar3;
    word_t stack_slot;                       /* &stack0x00000008 scratch */
    uint extraout_var;                       /* condition flags from FUN_004aba88 */
    word_t w20_hi_lo = ((word_t)reg_40a4 << 32) | reg_w20;

    FUN_00041138();
    FUN_00350c5c();
    FUN_004aba88();
    if ((extraout_var >> 0x1b & 0x1e) == 0 && (reg_w20 >> 2 & 1) == 0) {
        uVar3 = *(word_t *)(w20_hi_lo + 0x10);
        FUN_004aa83c();
        uVar1 = FUN_0036a940();
        FUN_004aa6c4();
        uVar2 = FUN_00002534();
        uVar2 = FUN_0036a9a0(uVar2, &stack_slot);
        FUN_004ac538(DAT_004baeb0);
        FUN_0036b270(uVar3);
        FUN_0049a758(uVar2);
    } else {
        FUN_004aa83c();
        uVar1 = FUN_0036a940();
        FUN_004aa6c4();
        FUN_00002534();
        FUN_00355538();
        FUN_0036a940();
        FUN_004acbe4(DAT_004c2450);
        FUN_0036b270(reg_x19 & reg_x24);
    }
    FUN_0035847c(uVar1, reg_x30);
    return 0;
}

/* FUN_00492e18 @ 0x00492e18  (est. sk_r30_debug_desc_user_type)
 * Ghidra: undefined1 [16] FUN_00492e18(void)
 * Formats a debug description fragment: emits the "<transform_argument_type_"
 * prefix (string at 0x5e31a0, not declared in the prelude so referenced by
 * address), appends " userType=" (immediates 0x5f746c7573657220 / 0xed00003d65707974)
 * and a '>' terminator, returning the 16-byte tagged pair {0xd000000000000019, hi}.
 * Confidence: low   Notes: the prelude declares word_t return; the real result
 *   is a 16-byte pair, so the hi word is written to pair_out[1] and the lo
 *   returned; extraout_x1/extraout_x8 are register leftovers. */
static word_t sk_r30_00492e18(word_t *pair_out /* 16-byte result buffer */,
                              word_t unaff_x20 /* context */)
{
    wpair_t auVar1;
    word_t extraout_x1;
    word_t extraout_x8;
    word_t local_38;

    FUN_00100c04();
    FUN_002a4ab4(0x2b);
    FUN_003a25d4(local_38);
    FUN_00086840((word_t)(char *)0x5e31a0);      /* s_<transform_argument_type_ */
    FUN_00208418(*(word_t *)unaff_x20, 0);
    FUN_002acbb8();
    FUN_003a25d4(extraout_x1);
    FUN_002acbb8(0x5f746c7573657220, 0xed00003d65707974);   /* " user" / "type=" */
    FUN_00208418(*(word_t *)(unaff_x20 + 8), 0);
    FUN_00465294();
    FUN_003a25d4();
    FUN_002acbb8(0x3e, 0xe100000000000000);      /* ">" */
    auVar1.hi = extraout_x8;
    auVar1.lo = 0xd000000000000019;
    pair_out[0] = auVar1.lo;
    pair_out[1] = auVar1.hi;
    return auVar1.lo;
}

/* FUN_00493fa0 @ 0x00493fa0  (est. sk_r30_string_match_dispatch)
 * Ghidra: void FUN_00493fa0(void)
 * String/Match dispatcher: reads the source descriptor from FUN_0008e518's
 * buffer, and if the type metadata matches 0x6865e0 builds a value via
 * FUN_004a4ac4 with the 0x657bc0 type & 0x5a3c68 witness; otherwise falls into
 * a Match path that on success builds a boxed pair {1,2} and calls the Swift
 * "StringProcessing.Match" failure trap (FUN_001afa84), else emits the result
 * through the closure witness.
 * Confidence: low   Notes: heavy extraout/unaff register artifacts; indirect
 *   call target SUB_54ffff60f100041f is opaque; unaff_x20 is a context array. */
static word_t sk_r30_00493fa0(word_t unaff_x20 /* context */, word_t reg_x8,
                              word_t reg_x16)
{
    int iVar1;
    word_t uVar2;
    word_t lVar3;
    word_t lVar4;
    word_t pcVar5;
    wpair_t auVar6, auVar7;
    word_t uStack_48, local_50, local_20, local_30, uStack_28, local_8;
    word_t auStack_e0[16 / 8];
    word_t auStack_d0[64 / 8];
    word_t auStack_90[64 / 8];

    auVar6 = ((wpair_t (*)())&FUN_0008e518)();
    lVar4 = *(word_t *)(auVar6.lo + 0x10);
    FUN_003504e8();
    FUN_00310d68();
    FUN_000a6f88();
    FUN_0007c1a4();
    ((word_t (*)())0x54ffff60f100041f)();
    FUN_0034cff4();
    FUN_0007c028();
    ((word_t (*)(word_t))0x54ffff60f100041f)(*(word_t *)(reg_x8 + 0x40));
    FUN_000aa4ec();
    FUN_004aba28();
    if (lVar4 == 0x6865e0) {
        uStack_48 = unaff_x20 + 8;
        local_50 = *(word_t *)unaff_x20;
        local_20 = unaff_x20 + 0x10;
        local_30 = local_50;
        uStack_28 = uStack_48;
        local_8 = local_20;
        FUN_000f5d84(&local_50, auStack_e0);
        FUN_004a4ac4(&local_8, auStack_e0, 0x657bc0, &DAT_005a3c68);
        FUN_00365b6c(reg_x8, &local_30, 0x6865e0, 0x6865e0, 7);
    } else {
        FUN_00351790(&local_30, *(word_t *)unaff_x20, unaff_x20 + 8);
        FUN_0047cf0c();
        FUN_00319808(&local_30, &local_50);
        FUN_00351f34();
        iVar1 = FUN_00365b6c();
        if (iVar1 == 0) {
            FUN_00350774();
            FUN_000839d8();
            FUN_000b4390(*(word_t *)(reg_x16 + 8));
            ((word_t (*)())reg_x8)();
            uVar2 = FUN_00002534(&DAT_0064c040, &DAT_004bbf40);
            lVar3 = FUN_0036a9a0(uVar2, auStack_90);
            *(word_t *)(lVar3 + 0x10) = 1;
            *(word_t *)(lVar3 + 0x18) = 2;
            FUN_00319808(&local_30, lVar3 + 0x20);
            FUN_00002804(lVar3);
            FUN_0036b118(lVar3);
            lVar3 = FUN_0036a9a0(uVar2, auStack_d0);
            *(word_t *)(lVar3 + 0x10) = 1;
            *(word_t *)(lVar3 + 0x18) = 2;
            uVar2 = FUN_003743d0(lVar4);
            *(word_t *)(lVar3 + 0x38) = uVar2;
            *(word_t *)(lVar3 + 0x20) = lVar4;
            FUN_00002804(lVar3);
            FUN_0036b118(lVar3);
            FUN_003593c0(s__StringProcessing_Match_swift_005e1fe0);
            FUN_00002818();
            FUN_001afa84();          /* does not return */
        }
        FUN_000026e8(&local_30);
        FUN_004ac318();
        FUN_00350774();
        FUN_000839d8();
        pcVar5 = *(word_t *)(reg_x16 + 0x20);
        FUN_003504a0();
        ((word_t (*)())pcVar5)();
        auVar7 = ((wpair_t (*)())&FUN_000a6e14)();
        ((word_t (*)(word_t, word_t, word_t))pcVar5)(auVar7.lo, auVar7.hi, lVar4);
    }
    FUN_0008e500(auVar6.hi);
    return 0;
}

/* FUN_004947e8 @ 0x004947e8  (est. sk_r30_thunk_to_94810)
 * Ghidra: void FUN_004947e8(void)
 * Thin forwarder that immediately delegates to sk_r30_00494810.
 * Confidence: high   Notes: trivial tail forward. */
static word_t sk_r30_004947e8(void)
{
    sk_r30_00494810(0, 0, 0, 0, 0, 0, 0, 0, 0);
    return 0;
}

/* FUN_00494d1c @ 0x00494d1c  (est. sk_r30_release_after_94b44)
 * Ghidra: void FUN_00494d1c(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)
 * Runs FUN_004ab65c then forwards (param_4, param_1) to sk_r30_00494b44.
 * Confidence: medium   Notes: param_2/param_3 unused; arg order preserved. */
static word_t sk_r30_00494d1c(word_t param_1, word_t param_2,
                              word_t param_3, word_t param_4)
{
    FUN_004ab65c();
    sk_r30_00494b44(param_4, param_1, 0, 0);
    return 0;
}

/* FUN_0049513c @ 0x0049513c  (est. sk_r30_bit_range_test)
 * Ghidra: uint FUN_0049513c(ulong param_1,ulong param_2,ulong param_3)
 * Tests a bit of a 128-bit-style operand: for position >= 0x40 selects from
 * param_3 (high word) at (param_1-0x40); for position < 0x40 selects from
 * param_2 (low word) at param_1, masking shifts to 6 bits.
 * Confidence: medium   Notes: pure bit-selection helper; returns 0/1. */
static word_t sk_r30_0049513c(word_t param_1, word_t param_2, word_t param_3)
{
    uint uVar1 = 0;

    if ('?' < (char)param_1) {
        uVar1 = (uint)(param_3 >> ((ulong)((uint)param_1 - 0x40) & 0x3f)) & 1;
    }
    if (((uint)param_1 & 0xff) < 0x40) {
        uVar1 = (uint)(param_2 >> (param_1 & 0x3f)) & 1;
    }
    return uVar1;
}

/* FUN_00495598 @ 0x00495598  (est. sk_r30_collection_box_init)
 * Ghidra: void FUN_00495598(void)
 * Allocates a new box/collection object via FUN_0036a940, zeroes its 0x10-0x50
 * payload (seed 0x8000000000000000 in slot 0x38, derived flag byte in slot 0x50),
 * stashes the context pointer in slot 0x58, and registers the boxed (tagged
 * 0x3000000000000000) value with sk_r30_0049153c.
 * Confidence: low   Notes: unaff_x20 is a self/context register-global;
 *   extraout_w8/w9 (flag register leftovers) feed the 0x50 byte; in_x4 and
 *   extraout_x8 are register artifacts passed through. */
static word_t sk_r30_00495598(word_t unaff_x20 /* self/context */, word_t in_x4,
                              word_t reg_x8, uint extraout_w8, uint extraout_w9)
{
    word_t uVar1;

    FUN_0035199c();
    FUN_004aca18();
    FUN_004aab60();
    uVar1 = FUN_0036a940();
    *(word_t *)(uVar1 + 0x18) = 0;
    *(word_t *)(uVar1 + 0x10) = 0;
    *(word_t *)(uVar1 + 0x28) = 0;
    *(word_t *)(uVar1 + 0x20) = 0;
    *(word_t *)(uVar1 + 0x30) = 0;
    *(word_t *)(uVar1 + 0x38) = 0x8000000000000000;
    *(word_t *)(uVar1 + 0x40) = 0;
    *(word_t *)(uVar1 + 0x48) = 0;
    *(char *)(uVar1 + 0x50) = (char)(extraout_w9 >> (ulong)(extraout_w8 & 0x1f));
    FUN_004ab5d4(in_x4);
    FUN_00084180();
    ((word_t (*)())reg_x8)();
    sk_r30_00491644(uVar1);
    FUN_00351d18();
    FUN_0036b118();
    *(word_t *)(uVar1 + 0x58) = unaff_x20;
    sk_r30_0049153c();
    return 0;
}

/* FUN_00495a74 @ 0x00495a74  (est. sk_r30_thunk_to_95aec)
 * Ghidra: void FUN_00495a74(void)
 * Thin forwarder that immediately delegates to sk_r30_00495aec.
 * Confidence: high   Notes: trivial tail forward. */
static word_t sk_r30_00495a74(void)
{
    sk_r30_00495aec(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    return 0;
}
/* FUN_00490600 @ 0x00490600  (est. sk_r30_lookup_table_byte)
 * Ghidra: undefined1 FUN_00490600(char param_1)
 * Byte-valued lookup: returns the (byte)(kind-7)-th element of the DAT_005a5eba
 * table when kind-7 is in [0,0xe), else the default 0xe. A small classification
 * / case-select table probe (Swift runtime style).
 * Confidence: high   Notes: byte index into word_t table read as bytes. */
static word_t sk_r30_00490600(char kind)
{
    if ((byte)(kind - 7U) < 0xe) {
        return (word_t)(((unsigned char *)&DAT_005a5eba)[(byte)(kind - 7U)]);
    }
    return 0xe;
}

/* FUN_00490b98 @ 0x00490b98  (est. sk_r30_range_check_pair)
 * Ghidra: undefined1 [16] FUN_00490b98(ulong param_1,ulong param_2,ulong param_3,
 *         undefined8 param_4,undefined8 param_5,long param_6)
 * Bounds-checked range helper returning a 16-byte pair {lo,hi}. Validates that
 * ctx->+0x10 (an upper bound) covers both `base` and `cand_end`, subtracts base
 * from cand_end, and either returns the validated {base+count, 0} or the
 * fail sentinel {0,1} when the candidate end lies strictly inside (0,count).
 * Confidence: medium   Notes: 16-byte pair return modelled as word_t (x0) plus
 * a trailing *out_hi (x1) since the slice forward decl forces a word_t result. */
static word_t sk_r30_00490b98(word_t base, word_t count, word_t cand_end,
                              word_t arg4, word_t arg5, long ctx,
                              word_t *out_hi /* upper word of 16-byte result */)
{
    word_t bound;
    word_t hi;

    bound = *(word_t *)(ctx + 0x10);
    if (bound < base || bound < cand_end) {
        CL4_SWBP(0x490bf4);
    }
    cand_end = cand_end - base;
    if ((long)count < 1) {
        if (0 < (long)cand_end || (long)cand_end <= (long)count) {
            goto checked;
        }
    } else if (((long)cand_end < 0) || (count <= cand_end)) {
checked:
        if (SCARRY8(base, count)) {
            CL4_SWBP(0x490bf8);
        }
        if (base + count <= bound) {
            *out_hi = 0;
            return base + count;
        }
        CL4_SWBP(0x490bfc);
    }
    /* Fall-through: candidate end inside (0,count) -> {lo:0, hi:1}. */
    *out_hi = 1;
    return 0;
}

/* FUN_00490dfc @ 0x00490dfc  (est. sk_r30_query_pair_out)
 * Ghidra: void FUN_00490dfc(undefined1 (*param_1) [16])
 * Invokes FUN_004730e4 with three context words (unaff_x20[0..2]) and stores the
 * resulting 16-byte pair into the caller-provided *out buffer.
 * Confidence: low   Notes: unaff_x20 = self/context register-global (3rd party);
 * FUN_004730e4 is a 16-byte pair return of which only x0 (lo) is captured by the
 * extern shim, so the hi half is not reproduced. */
static word_t sk_r30_00490dfc(wpair_t *out, word_t *ctx /* unaff_x20 */)
{
    wpair_t pair;

    pair.lo = FUN_004730e4(ctx[0], ctx[1], ctx[2]);
    /* high half (x1) of the 16-byte FUN_004730e4 return is not captured by the
     * word_t extern shim; *out is written with the low word only. */
    *out = pair;
    return 0;
}

/* FUN_00491288 @ 0x00491288  (est. sk_r30_dispatch_handlers)
 * Ghidra: void FUN_00491288(void)
 * Builds/handles a collection from an in-slice handler table: iterates the
 * table rows (stride 0x38), runs FUN_00455abc over a sub-list, grows the
 * DAT_00657778-backed collection (FUN_003a261c/0006b3f4/004995e4),
 * then either completes a single-element fast path (FUN_0049341c/004ab034) or
 * drains a message queue (FUN_0029fb80/000b44cc) and reports via FUN_000b45b0.
 * Confidence: low   Notes: extraout_w8 (secondary reg of FUN_004ab034) and the
 * stack-passed in_stack_40/48/38 are not fully recoverable; LAB_00657e38 passed
 * as a literal code address 0x657e38. unaff_x30 = context register-global. */
static word_t sk_r30_00491288(word_t unaff_x30 /* context register-global */)
{
    long lVar6;
    word_t uVar2, uVar7, uVar9, uVar11, uVar12, uVar13, uVar14;
    byte uVar4;
    bool bVar5;
    long lVar1, lVar10;
    word_t *puVar8;
    int extraout_w8;
    wpair_t auVar15;
    word_t in40 = 0;                       /* in_stack_00000040 */
    word_t in48 = 0xe000000000000000;      /* in_stack_00000048 */
    word_t stack38 = 0;                    /* in_stack_00000038 */

    auVar15.lo = FUN_000b4594();
    uVar9 = auVar15.hi;   /* hi (x1) of the 16-byte FUN_000b4594 return, uncaptured */
    uVar13 = 0x6865e0;
    uVar4 = (byte)(0x6865df < uVar9);
    if (uVar9 == 0x6865e0) {
        bVar5 = true;
    } else {
        uVar12 = 0xe000000000000000;
        uVar11 = *(word_t *)(auVar15.lo + 0x18);
        lVar6 = FUN_00493354(uVar11);
        uVar13 = *(word_t *)(lVar6 + 0x10);
        if (uVar13 == 0) {
            puVar8 = &DAT_00657778;
        } else {
            uVar14 = 0;
            puVar8 = &DAT_00657778;
            do {
                FUN_004ac120();
                if ((bool)uVar4) {
                    CL4_SWBP(0x49153c);
                }
                lVar10 = lVar6 + 0x20 + (long)uVar14 * 0x38;
                lVar1 = *(long *)(lVar10 + 8);
                uVar12 = *(word_t *)(lVar10 + 0x10);
                lVar10 = *(long *)(lVar10 + 0x18);
                FUN_0036b270(lVar1);
                while (lVar10 != 0) {
                    uVar12 = FUN_00455abc(uVar12);
                    bVar5 = SBORROW8(lVar10, 1);
                    lVar10 = lVar10 + -1;
                    if (bVar5) {
                        CL4_SWBP(0x4914b0);
                    }
                }
                uVar7 = FUN_003a261c(puVar8);
                if ((uVar7 & 1) == 0) {
                    FUN_0006b3f4(*(word_t *)((byte *)puVar8 + 0x10));
                    puVar8 = (word_t *)FUN_004995e4();
                }
                uVar7 = *(word_t *)((byte *)puVar8 + 0x10);
                if (*(word_t *)((byte *)puVar8 + 0x18) >> 1 <= uVar7) {
                    FUN_0006b42c();
                    FUN_004abb28();
                    puVar8 = (word_t *)FUN_004995e4();
                }
                *(word_t *)((byte *)puVar8 + 0x10) = uVar7 + 1;
                *(word_t *)((byte *)puVar8 + uVar7 * 8 + 0x20) = uVar12;
                if (lVar1 != 0) {
                    FUN_00350618();
                    FUN_002acbb8();
                    FUN_003a25d4(lVar1);
                }
                uVar12 = in48;
                uVar2 = in40;
                uVar14 = uVar14 + 1;
                FUN_0029c014(0x20);
                uVar4 = (byte)(uVar13 <= uVar14);
                in40 = uVar2;
                in48 = uVar12;
            } while (uVar14 != uVar13);
        }
        FUN_0036b118(lVar6);
        if (*(long *)((byte *)puVar8 + 0x10) == 1) {
            FUN_003a25d4(uVar12);
            FUN_0049341c(uVar11, 0 /* uncaptured unaff_x21 mask register-global */);
            uVar13 = FUN_004ab034();
            if (extraout_w8 == 0xe) {
                uVar13 = *(word_t *)((uVar13 & 0xffffffffffffffb) + 0x10);
            } else {
                uVar13 = 0x675c68;
            }
            FUN_0036b118();
        } else {
            stack38 = (word_t)puVar8;
            FUN_0036b270(puVar8);
            FUN_0036b270(uVar12);
            do {
                while (true) {
                    auVar15.lo = FUN_0029fb80();
                    lVar6 = auVar15.hi;
                    if (lVar6 == 0) {
                        FUN_003a25d4(uVar12);
                        uVar11 = 0;
                        goto lab_4914b4;
                    }
                    if (auVar15.lo != 0x20 || lVar6 != -0x1f00000000000000) break;
                    FUN_003a25d4(lVar6);
                }
                uVar13 = FUN_000b44cc(auVar15.lo, lVar6, 0x20);
                FUN_003a25d4(lVar6);
                uVar11 = uVar12;
            } while ((uVar13 & 1) != 0);
lab_4914b4:
            FUN_003a25d4(uVar12);
            FUN_00351450();
            FUN_00002534();
            uVar12 = FUN_004aa5f8((word_t)0x657e38 /* &LAB_00657e38 */);
            FUN_004a42a0(uVar12, 0x657c10, &DAT_005a3cc0);
            FUN_0035139c(&stack38);
            uVar13 = FUN_00455438();
            FUN_003a25d4(uVar11);
        }
        FUN_0036b118(puVar8);
        bVar5 = uVar9 == uVar13;
    }
    FUN_000b45b0(bVar5, uVar13, unaff_x30);
    return 0;
}

/* FUN_0049174c @ 0x0049174c  (est. sk_r30_invoke_handler)
 * Ghidra: void FUN_0049174c(void)
 * Runs a short fixed sequence: queries a 16-byte pair (FUN_00354a34), calls a
 * thunked helper (FUN_00019850), registers it with FUN_00445e64, releases the
 * pair high word, then forwards the result of FUN_0049115c via FUN_00354ef8.
 * Confidence: low   Notes: unaff_x30 = context register-global; FUN_00354a34
 * 16-byte return only x0 (lo) captured, hi modelled as an uncaptured local. */
static word_t sk_r30_0049174c(word_t unaff_x30 /* context register-global */)
{
    word_t uVar1, uVar2;
    wpair_t stack10;

    stack10.lo = FUN_00354a34();   /* hi (x1) of the pair is not captured */
    uVar2 = stack10.hi;
    uVar1 = FUN_00019850();
    FUN_000f5e08();
    FUN_004ab920();
    FUN_00445e64(&stack10, uVar1);
    FUN_004630c4();
    FUN_003a25d4(uVar2);
    FUN_003505c4(uVar1);
    uVar1 = sk_r30_0049115c(0, 0, 0, 0, 0 /* params 1-5: uncaptured forwarder args */);
    FUN_00354ef8(uVar1, unaff_x30);
    return 0;
}

/* FUN_00491abc @ 0x00491abc  (est. sk_r30_emplace_result)
 * Ghidra: void FUN_00491abc(undefined8 param_1,undefined8 param_2,undefined8 param_3)
 * Classifies a status (FUN_0048f61c): on the 0xc case the low boxed word is
 * released; otherwise a fresh object is allocated (FUN_0036a940) and populated
 * with the status and boxed value, tagged 0x6000000000000000. The chosen value
 * is stored into ctx->+0x18 after releasing param_3 and the pair high word.
 * Confidence: medium   Notes: unaff_x20 = self/context register-global;
 * extraout_w8 (from FUN_004ab26c) is an uncaptured secondary register. */
static word_t sk_r30_00491abc(word_t param_1, word_t param_2, word_t param_3,
                              long ctx /* unaff_x20 */)
{
    word_t uVar1, uVar2;
    uint extraout_w8;
    wpair_t auVar3;

    auVar3.lo = FUN_00357cb4();
    *(word_t *)(ctx + 0x10) = 0;
    *(word_t *)(ctx + 0x20) = 0;
    uVar1 = FUN_0048f61c();
    FUN_004ab26c();
    if ((extraout_w8 & 0xfffffffe | (uint)uVar1 >> 2 & 1) == 0xc) {
        FUN_0036b118(auVar3.lo & 0xfffffffffffffff);
    } else {
        FUN_004aa794();
        uVar2 = FUN_0036a940();
        *(word_t *)(uVar2 + 0x10) = uVar1;
        *(word_t *)(uVar2 + 0x18) = auVar3.lo;
        uVar1 = uVar2 | 0x6000000000000000;
    }
    FUN_0036b118(param_3);
    FUN_0036b118(auVar3.hi);
    *(word_t *)(ctx + 0x18) = uVar1;
    FUN_00357c74();
    return 0;
}

/* FUN_00491f48 @ 0x00491f48  (est. sk_r30_box_string_metadata)
 * Ghidra: void FUN_00491f48(void)
 * Builds a tagged object: seeds a 4-word tag array from FUN_00492038, runs it
 * through FUN_00414bd8/FUN_004619fc, copies the 0x99-byte descriptor into a
 * scratch buffer, and allocates a 0x180-byte object (FUN_0036a940) whose header
 * is initialized from DAT_004baeb0/0x4baeb8, then memcpy-fills two payload
 * regions (0xb0 and 0x160 bytes) from the staged buffers.
 * Confidence: medium   Notes: uRam00000000004baeb8 is a raw read at 0x4baeb8;
 * struct-copy groups (local_110 / local_3c0) reproduced with named locals. */
static word_t sk_r30_00491f48(void)
{
    word_t uVar1;
    long lVar2;
    word_t local_110, uStack_108, uStack_100, uStack_f8;
    byte local_f0, local_ef, local_ee;
    word_t local_3c0, uStack_3b8, uStack_3b0, uStack_3a8;
    byte local_3a0, local_39f, local_39e;
    byte auStack_e8[160];
    byte auStack_320[176];
    byte auStack_270[352];
    word_t local_48[4];
    byte local_28;

    local_48[0] = FUN_00492038(0 /* uncaptured table index register arg */) & 0xff;
    local_48[1] = 0;
    local_48[2] = 0;
    local_48[3] = 0;
    local_28 = 0;
    FUN_00414bd8(&local_110, local_48, 0, 0);
    uStack_3b8 = uStack_108;
    local_3c0 = local_110;
    uStack_3a8 = uStack_f8;
    uStack_3b0 = uStack_100;
    local_3a0 = local_f0;
    local_39f = local_ef;
    local_39e = local_ee;
    FUN_004619fc(&local_3c0);
    FUN_00117cc4(auStack_e8, &local_3c0, 0x99);
    FUN_0041cb78();
    FUN_00351790();
    FUN_00351488(auStack_320, auStack_e8);
    FUN_00412fe4();
    uVar1 = FUN_004ab630();
    lVar2 = FUN_0036a940(uVar1, 0x180, 7);
    uVar1 = DAT_004baeb0;
    *(word_t *)(lVar2 + 0x18) = *(word_t *)0x4baeb8;   /* uRam...04baeb8 */
    *(word_t *)(lVar2 + 0x10) = uVar1;
    FUN_0049c838(auStack_320);
    FUN_00117cc4(auStack_270, auStack_320, 0xb0);
    FUN_0049c850(auStack_270);
    FUN_00117cc4(lVar2 + 0x20, auStack_270, 0x160);
    FUN_0035354c();
    return 0;
}

/* FUN_00492704 @ 0x00492704  (est. sk_r30_dispatch_thunk_guard)
 * Ghidra: void FUN_00492704(void)
 * Runs FUN_0008409c and FUN_004080b0, then invokes the context-held code
 * pointer (unaff_x19) and finally FUN_001a8564.
 * Confidence: medium   Notes: unaff_x19 = self/context code-pointer
 * register-global, invoked directly. */
static word_t sk_r30_00492704(code unaff_x19 /* context code pointer */)
{
    FUN_0008409c();
    FUN_004080b0();
    unaff_x19();
    FUN_001a8564();
    return 0;
}

/* FUN_00492eec @ 0x00492eec  (est. sk_r30_dispatch_switch)
 * Ghidra: void FUN_00492eec(undefined8 param_1,undefined8 param_2,undefined8 param_3)
 * Recursive tagged-value dispatch: decodes a value kind from FUN_004ac198 and
 * processes collections (kind 1/default), closures (2), tuples (3), boxed
 * payloads (4), strings (5), records (6), and special 0xb/0xc cases, recursing
 * into itself for elements and releasing/retaining boxes as it walks.
 * Confidence: low   Notes: extraout_w16 (FUN_004ac198), extraout_x8_0* (from
 * FUN_004ab800/FUN_004ab260), extraout_w8 are secondary registers not captured
 * by the word_t extern shims; unaff_x19 = tag mask, unaff_x30 = context
 * register-global. Recursion is faithful to the control flow. */
static word_t sk_r30_00492eec(word_t param_1, word_t param_2, word_t param_3,
                              word_t unaff_x19 /* tag mask */,
                              word_t unaff_x30 /* context register-global */)
{
    uint uVar1;
    word_t uVar2, uVar5, uVar6, uVar8, uVar9, uVar10;
    int iVar4;
    long lVar7, lVar11;
    byte uVar3;
    wpair_t auVar12;
    word_t local_90, uStack_88, uStack_80, uStack_78, uStack_68, local_70,
           uStack_60, uStack_58;
    byte auStack_210[128], auStack_190[128], auStack_110[128];
    uint extraout_w16;
    int extraout_w8;
    long extraout_x8, extraout_x8_00, extraout_x8_01, extraout_x8_02,
         extraout_x8_03, extraout_x8_04;

    do {
        FUN_0008e518();
        auVar12.lo = FUN_004ac198();          /* hi (x1) not captured */
        uVar8 = auVar12.hi;
        uVar9 = auVar12.lo;
        uVar1 = extraout_w16 & 0xfffffffe | (uint)(auVar12.lo >> 2) & 1;
        uVar3 = (byte)(uVar1 == 0x10);
        switch (uVar1) {
        default:
            uVar9 = *(word_t *)(uVar9 + 0x10);
            lVar11 = *(long *)(uVar9 + 0x10);
            if (lVar11 != 0) {
                FUN_0036b270(uVar9);
                lVar7 = 0x20;
                do {
                    uVar10 = *(word_t *)(uVar9 + lVar7);
                    FUN_0036b270(uVar10 & 0xffffffffffffffb);
                    FUN_004aafc8();
                    FUN_0041c2c8();
                    FUN_004ab1b4();
                    FUN_004acab4(uVar10);
                    sk_r30_00492eec(param_1, param_2, param_3, unaff_x19, unaff_x30);
                    FUN_0036b118(uVar10 & 0xffffffffffffffb);
                    lVar7 = lVar7 + 8;
                    lVar11 = lVar11 + -1;
                } while (lVar11 != 0);
                goto lab_4930f0;
            }
            goto caseD7;
        case 7:
        case 8:
        case 9:
        case 10:
        case 0xd:
        case 0xe:
        case 0xf:
        case 0x10:
caseD7:
            FUN_0008e500(unaff_x30);
            return 0;
        case 1:
            uVar9 = *(word_t *)((uVar9 & 0xffffffffffffffb) + 0x10);
            lVar11 = *(long *)(uVar9 + 0x10);
            if (lVar11 != 0) {
                FUN_0036b270(uVar9);
                lVar7 = 0x20;
                do {
                    uVar10 = *(word_t *)(uVar9 + lVar7);
                    FUN_0036b270(uVar10 & 0xffffffffffffffb);
                    FUN_004abc6c();
                    FUN_000e72b0();
                    sk_r30_00492eec(param_1, param_2, param_3, unaff_x19, unaff_x30);
                    FUN_0036b118(uVar10 & 0xffffffffffffffb);
                    lVar7 = lVar7 + 8;
                    lVar11 = lVar11 + -1;
                } while (lVar11 != 0);
                goto lab_4930f0;
            }
            goto caseD7;
        case 2:
            FUN_004ab800();
            uVar8 = *(word_t *)(extraout_x8_00 + 0x10);
            uVar5 = *(word_t *)(extraout_x8_00 + 0x30);
            if (*(long *)(extraout_x8_00 + 0x38) == 0) {
                FUN_0036b270(*(word_t *)(extraout_x8_00 + 0x18));
                FUN_0049341c(uVar5, 0 /* uncaptured unaff_x21 mask register-global */);
                FUN_004ab034();
                if (extraout_w8 == 0xe) {
                    FUN_0036b118();
                } else {
                    FUN_0036b118();
                }
            } else {
                FUN_0036b270(*(word_t *)(extraout_x8_00 + 0x18));
            }
            FUN_004aafc8();
            FUN_0041c29c();
            FUN_0041cb78();
            FUN_00352840(&local_90, uVar8);
            FUN_0041c1c4();
            FUN_0041c0c0(&local_90);
            FUN_004a4214(&local_90);
            FUN_004abc6c();
            FUN_00351274();
            goto lab_4932f4;
        case 3:
            FUN_004ab260();
            uVar5 = FUN_004abc6c(*(word_t *)(extraout_x8_02 + 0x68));
            auVar12.hi = uVar8;
            auVar12.lo = uVar5;
            break;
        case 4:
            FUN_004ab800();
            uVar9 = *(word_t *)(extraout_x8_03 + 0x10);
            auVar12.lo = FUN_0036b270(uVar9 & unaff_x19);
            FUN_0008e388(auVar12.lo, auVar12.hi, (uint)param_3 & 1);
            sk_r30_00492eec(param_1, param_2, param_3, unaff_x19, unaff_x30);
            uVar9 = uVar9 & unaff_x19;
            goto lab_4930f0;
        case 5:
            uVar9 = uVar9 & 0xffffffffffffffb;
            FUN_00117cc4(auStack_110, uVar9 + 0x10, 0x80);
            uVar5 = *(word_t *)(uVar9 + 0x90);
            uVar2 = *(word_t *)(uVar9 + 0x98);
            FUN_00117cc4(&local_90, uVar9 + 0x10, 0x80);
            iVar4 = FUN_00458cb8(auStack_110);
            if (iVar4 == 3) {
                uVar6 = FUN_00458cd4(&local_90);
                uVar9 = FUN_0036a940(&DAT_00688700, 0x90, 7);
                FUN_00117cc4(uVar9 + 0x10, uVar6, 0x80);
                FUN_00117cc4(auStack_190, auStack_110, 0x80);
                uVar6 = FUN_00458cd4(auStack_190);
                FUN_00458a90(uVar6, auStack_210);
                uVar6 = FUN_004abc6c(uVar9 | 0x2000000000000000);
                FUN_0041c2e4(uVar6, uVar8);
                FUN_0036b118(uVar9);
            }
            FUN_004aafc8();
            FUN_0041c2c8();
            FUN_004ab1b4();
            FUN_004acab4(uVar5);
            sk_r30_00492eec(param_1, param_2, param_3, unaff_x19, unaff_x30);
            FUN_004aafc8();
            FUN_0041c2c8();
            FUN_004ab1b4();
            FUN_004acab4(uVar2);
lab_4932f4:
            sk_r30_00492eec(param_1, param_2, param_3, unaff_x19, unaff_x30);
            goto caseD7;
        case 6:
            FUN_004ab260();
            uStack_88 = *(word_t *)(extraout_x8_01 + 0x18);
            local_90 = *(word_t *)(extraout_x8_01 + 0x10);
            uStack_78 = *(word_t *)(extraout_x8_01 + 0x28);
            uStack_80 = *(word_t *)(extraout_x8_01 + 0x20);
            uStack_68 = *(word_t *)(extraout_x8_01 + 0x38);
            local_70 = *(word_t *)(extraout_x8_01 + 0x30);
            uStack_58 = *(word_t *)(extraout_x8_01 + 0x48);
            uStack_60 = *(word_t *)(extraout_x8_01 + 0x40);
            uVar5 = *(word_t *)(extraout_x8_01 + 0x58);
            FUN_0041bfb4();
            lVar11 = FUN_00351db4();
            if ((!(bool)uVar3) && (lVar11 == 0)) {
                FUN_004aafc8();
                uVar8 = FUN_0041c2c8();
            }
            auVar12.hi = uVar8;
            auVar12.lo = uVar5;
            FUN_004abc6c();
            break;
        case 0xb:
            FUN_004ab800();
            uVar9 = *(word_t *)(extraout_x8_04 + 0x38);
            if ((uVar9 & 6) == 2) {
                FUN_003509b0();
                FUN_00352ea8();
                FUN_004588cc();
                FUN_0036b270(uVar9 & (unaff_x19 - 2));
                uVar5 = FUN_004abc6c(uVar9 & 0xfffffffffffffff9);
                FUN_0041c2e4(uVar5, uVar8);
                FUN_0036b118(uVar9 & (unaff_x19 - 2));
                FUN_003509b0();
                FUN_00352ea8();
                FUN_0008e500();
                FUN_00458940();
                return 0;
            }
            goto caseD7;
        case 0xc:
            FUN_004ab260();
            uVar8 = *(word_t *)(extraout_x8 + 0x10);
            FUN_004aafc8();
            FUN_0041c2ac();
            FUN_004ab1b4();
            auVar12.lo = FUN_004acab4(uVar8);
            break;
        }
        FUN_0008e500(auVar12.lo, auVar12.hi);
    } while (true);
lab_4930f0:
    FUN_0008e500(uVar9, unaff_x30);
    FUN_0036b118();
    return 0;
}

/* FUN_00494240 @ 0x00494240  (est. sk_r30_build_entries)
 * Ghidra: void FUN_00494240(void)
 * Iterates a table (stride 0x58) owned by unaff_x20[2], decoding each entry
 * (FUN_0049c704) and producing a result via one of two code paths
 * (FUN_00350b9c / FUN_00310d98+0006a4c0+003625e4), growing unaff_x20's backing
 * storage (FUN_0006b42c/0049a624) and appending. Then calls FUN_00455b88 to
 * validate the result: on success invokes a completion hook, else re-decodes the
 * matched entry and runs FUN_0047c62c.
 * Confidence: low   Notes: heavy extraout_x8_0 and extraout_x9 (from
 * FUN_0007c028/FUN_003509a4) and the SUB_54ffff60f100041f code-pointer artifact
 * are transcribed mechanically; unaff_x20 = context array register-global,
 * unaff_x30 = context. */
static word_t sk_r30_00494240(word_t *unaff_x20 /* context array */,
                              word_t unaff_x30 /* context register-global */)
{
    word_t uVar1, uVar2, uVar6, uVar7, uVar8;
    word_t *puVar3;
    long *plVar5;
    long extraout_x8, extraout_x9;
    long extraout_x8_00, extraout_x8_01;
    code extraout_x8_02;
    long lVar9, lVar10, lVar13;
    word_t uVar11, uVar12;
    long local_80, local_b0;
    word_t *local_78;
    wpair_t auVar14, auVar15;
    word_t auVar16_lo;         /* first 8 bytes of the 12-byte FUN_00455b88 result (x0) */
    byte auVar16_hi;           /* byte 8 (x1 low byte) of that result, uncaptured */
    word_t local_110;
    byte auStack_e8[24];
    word_t local_d0;
    byte auStack_c8[24];
    byte auStack_a8[16];
    byte auStack_98[24];
    byte auStack_70[80];
    word_t local_20, uStack_18;
    byte auStack_8[8];

    auVar14.lo = FUN_0008e518();
    plVar5 = (long *)auVar14.lo;
    lVar9 = *plVar5;
    FUN_0007c028();
    ((code)(word_t)0x54ffff60f100041f /* SUB_54ffff60f100041f */)(*(word_t *)(extraout_x8_00 + 0x40));
    FUN_000aa4ec();
    FUN_003509a4(extraout_x9 - extraout_x8_01);
    uVar8 = unaff_x20[0];
    uVar2 = unaff_x20[1];
    lVar10 = unaff_x20[2];
    uVar11 = *(word_t *)(lVar10 + 0x10);
    FUN_000776cc();
    if (uVar11 != 0) {
        FUN_004ab448();
        FUN_0049a624();
        lVar13 = lVar10 + 0x20;
        uVar12 = uVar11;
        do {
            FUN_0049c704(lVar13, &local_78);
            local_20 = uVar8;
            uStack_18 = uVar2;
            FUN_004a4ac4(auStack_70, auStack_a8, 0x657be0, &DAT_005a3c88);
            if (local_80 == 1) {
                FUN_0036b270(uVar2);
                auVar15.lo = FUN_00350b9c(auStack_a8);
lab_494454:
                FUN_004a4b14(auVar15.lo, auVar15.hi);
                puVar3 = local_78;
                FUN_0049c714(&local_78);
                uVar6 = FUN_00455ac8(0x675c68, puVar3, 0x675c68);
            } else {
                FUN_004a4ac4(auStack_98, auStack_c8, 0x656100, &DAT_005a3c90);
                if (local_b0 == 0) {
                    FUN_0036b270(uVar2);
                    auVar15.hi = 0x656100;
                    auVar15.lo = (word_t)auStack_98;
                    goto lab_494454;
                }
                FUN_00310d98(auStack_c8, auStack_e8);
                uVar6 = local_d0;
                uVar7 = FUN_0006a4c0(auStack_e8, local_d0);
                uVar6 = FUN_003625e4(uVar7, uVar6, 1);
                FUN_0036b270(uVar2);
                FUN_000026e8(auStack_e8);
                uVar6 = FUN_00455ac8(uVar6, local_78, uVar6);
                FUN_0049c714(&local_78);
                FUN_004a4b14(auStack_98, 0x656100, &DAT_005a3c90);
            }
            uVar1 = unaff_x20[2];
            if ((word_t)unaff_x20[3] >> 1 <= uVar1) {
                uVar7 = FUN_0006b42c();
                FUN_0049a624(uVar7, uVar1 + 1, 1);
            }
            unaff_x20[2] = uVar1 + 1;
            unaff_x20[uVar1 + 4] = uVar6;
            lVar13 = lVar13 + 0x58;
            uVar12 = uVar12 - 1;
        } while (uVar12 != 0);
    }
    local_78 = unaff_x20;
    FUN_003507e0();
    uVar6 = FUN_00002534();
    FUN_00350878(0x657c18);
    uVar7 = FUN_004a42a0();
    auVar16_lo = FUN_00455b88(plVar5, &local_78, uVar6, uVar7);
    /* auVar16_hi (byte 8 of the 12-byte return, x1) is not captured by the shim. */
    FUN_0036b118(unaff_x20);
    if ((auVar16_hi & 0xff) == 1) {   /* auVar16._8_4_ & 0xff */
        FUN_00493fa0(local_110, auVar14.hi, 0 /* uncaptured reg_x16 */);
        FUN_0024c9c0(extraout_x8, local_110, plVar5);
        FUN_00350bc0(auStack_8);
        FUN_003508fc();
        extraout_x8_02();
    } else {
        if (uVar11 <= auVar16_lo /* auVar16._0_8_ */) {
            CL4_SWBP(0x494664);
        }
        FUN_0049c704(lVar10 + auVar16_lo * 0x58 + 0x20, &local_78);
        local_20 = uVar8;
        uStack_18 = uVar2;
        FUN_0036b270(uVar2);
        FUN_0047c62c(auStack_a8, uVar8, uVar2, auStack_70, local_78);
        FUN_0049c714(&local_78);
        uVar8 = FUN_00002534(0x656100, &DAT_005a3c90);
        FUN_00365b6c(extraout_x8, auStack_a8, uVar8, *(word_t *)(lVar9 + 0x70), 7);
    }
    FUN_0008e500(unaff_x30);
    return 0;
}

/* FUN_00494810 @ 0x00494810  (est. sk_r30_result_store)
 * Ghidra: void FUN_00494810(void)
 * Runs a small sequence: FUN_004acb3c, fills a scratch via FUN_00469918,
 * resolves a 5-word block through FUN_003515d8, invokes the x4-held callback,
 * releases the scratch, and — when unaff_x21 is 0 — copies the 5 resolved
 * words into the extraout_x8 result buffer.
 * Confidence: low   Notes: in_x4 = x4-passed callback, extraout_x8 = result
 * buffer from a prior call, in_stack_98..b8 = 5 stack-passed words,
 * unaff_x21/unaff_x30 = context register-globals. */
static word_t sk_r30_00494810(code in_x4 /* x4 callback */,
                              word_t *extraout_x8 /* result buffer */,
                              long unaff_x21 /* context register-global */,
                              word_t unaff_x30 /* context register-global */,
                              word_t in_98, word_t in_a0, word_t in_a8,
                              word_t in_b0, word_t in_b8)
{
    byte scratch[8];

    FUN_004acb3c();
    FUN_00469918(&scratch);
    FUN_003515d8(&in_98, &scratch);
    in_x4();
    FUN_004974c4(&scratch);
    if (unaff_x21 == 0) {
        extraout_x8[1] = in_a0;
        extraout_x8[0] = in_98;
        extraout_x8[3] = in_b0;
        extraout_x8[2] = in_a8;
        extraout_x8[4] = in_b8;
    }
    FUN_004acb20(unaff_x30);
    return 0;
}

/* FUN_00494d68 @ 0x00494d68  (est. sk_r30_kind_emit)
 * Ghidra: void FUN_00494d68(char param_1)
 * Maps a kind byte to a selector: 0x12 when kind==0x02, else 5, and forwards
 * (selector, kind==0x02 || kind==0x01) to FUN_00494b44.
 * Confidence: medium   Notes: simple char-dispatch to in-slice FUN_00494b44. */
static word_t sk_r30_00494d68(char kind)
{
    word_t uVar1;

    if (kind != '\x02') {
        FUN_004ab65c();
        uVar1 = 5;
    } else {
        FUN_004ab65c();
        uVar1 = 0x12;
    }
    FUN_00494b44(uVar1, kind == '\x02' || kind == '\x01',
                 0, 0 /* uncaptured param_3 and unaff_x30 register-globals */);
    return 0;
}

/* FUN_0049516c @ 0x0049516c  (est. sk_r30_make_result_object)
 * Ghidra: void FUN_0049516c(undefined8 param_1,undefined8 param_2,undefined8 param_3)
 * Queries a callback object (FUN_00350b54/0049747c/00491644); on failure
 * (FUN_004921bc odd bit set) allocates a 0x18-byte tagged object
 * (FUN_0036a940, tag 0x2000000000000000) carrying the queried value, then
 * allocates a wrapper whose payload fields are set from that object.
 * Confidence: low   Notes: unaff_x19 = context register-global (carries the
 * constructed object); FUN_00491644/004921bc are in-slice siblings. */
static word_t sk_r30_0049516c(word_t param_1, word_t param_2, word_t param_3,
                              word_t unaff_x19 /* context register-global */)
{
    word_t uVar1, uVar3, uVar4, uVar5;
    long lVar6;
    code pcVar2;

    uVar1 = FUN_00350b54();
    pcVar2 = (code)FUN_0049747c(param_3);
    FUN_00084180();
    uVar3 = (*pcVar2)();
    uVar4 = FUN_00491644(unaff_x19 /* inferred self/context, uncaptured in decompile */);
    FUN_0036b118(uVar3);
    uVar5 = FUN_004921bc(uVar4);
    FUN_0036b118(uVar4 & 0xffffffffffffffb);
    if ((uVar5 & 1) == 0) {
        FUN_00084180();
        (*pcVar2)();
        FUN_00491644(unaff_x19 /* inferred self/context, uncaptured in decompile */);
        FUN_0035310c();
        FUN_0036b118();
    } else {
        uVar4 = FUN_0036a940(0x686200, 0x18, 7);
        FUN_00084180();
        (*pcVar2)();
        FUN_00491644(unaff_x19 /* inferred self/context, uncaptured in decompile */);
        FUN_00351d18();
        FUN_0036b118();
        *(word_t *)(uVar4 + 0x10) = uVar1;
        unaff_x19 = uVar4 | 0x2000000000000000;
    }
    FUN_00002534(0x657c20, &DAT_005a3cc8);
    FUN_00359018();
    lVar6 = FUN_0036a940();
    *(word_t *)(lVar6 + 0x18) = unaff_x19;
    *(word_t *)(lVar6 + 0x20) = 0;
    *(word_t *)(lVar6 + 0x10) = 0;
    return 0;
}

/* FUN_00495634 @ 0x00495634  (est. sk_r30_init_context_frame)
 * Ghidra: void FUN_00495634(void)
 * Allocates and initializes a context frame (FUN_004ac324): zeroes +0x40/+0x48,
 * sets +0x38 to 0x8000000000000000 and +0x50 from an extraout-derived shift,
 * invokes an x8-held callback, stores unaff_x20 into ctx->+0x58, and commits the
 * frame via FUN_00084234(FUN_00491644 tag 0x3000000000000000).
 * Confidence: low   Notes: extraout_w8/w9 (from FUN_004aca18/FUN_004aab60) and
 * extraout_x8 (code pointer from FUN_00100efc) are secondary registers of the
 * preceding calls, modelled as params; unaff_x20/unaff_x24 = context
 * register-globals. */
static word_t sk_r30_00495634(word_t unaff_x20 /* context register-global */,
                              word_t unaff_x24 /* context register-global */,
                              uint extraout_w8, uint extraout_w9,
                              code extraout_x8)
{
    long lVar1;

    FUN_00084220();
    FUN_0034d090();
    FUN_004aca18();
    FUN_004aab60();
    FUN_0036a940();
    lVar1 = FUN_004ac324();
    *(word_t *)(lVar1 + 0x40) = 0;
    *(word_t *)(lVar1 + 0x48) = 0;
    *(word_t *)(lVar1 + 0x38) = 0x8000000000000000;
    *(char *)(lVar1 + 0x50) = (char)(extraout_w9 >> (word_t)(extraout_w8 & 0x1f));
    FUN_004ab5d4();
    FUN_00100efc();
    extraout_x8();
    FUN_00491644(unaff_x20 /* inferred self/context, uncaptured in decompile */);
    FUN_00351d18();
    FUN_0036b118();
    *(word_t *)(unaff_x24 + 0x58) = unaff_x20;
    FUN_00084234(unaff_x24 | 0x3000000000000000);
    FUN_0049153c();
    return 0;
}

/* FUN_00495ab0 @ 0x00495ab0  (est. sk_r30_forward_95aec)
 * Ghidra: void FUN_00495ab0(void)
 * Thin forwarder: delegates straight to in-slice sibling FUN_00495aec.
 * Confidence: high   Notes: trivial one-call body. */
static word_t sk_r30_00495ab0(void)
{
    /* Void(void) forwarder: callee's 17 register/stack args are uncaptured in
     * the decompile; passed as 0 placeholders to satisfy the in-slice prototype. */
    sk_r30_00495aec(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    return 0;
}
/* ============================ part_3.c (SKR30 chunk 3) ============================ */
/* FUN_0049063c @ 0x0049063c  (est. sk_r30_process_fault_table)
 * Ghidra: void FUN_0049063c(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,long param_5,undefined8 param_6)
 * Iterates a table rooted at param_5+0x20 (0x58-byte entries, count at param_5+0x10) and,
 * per entry, tears down/re-appends the record via the collection-append helpers, then
 * reports success/failure back through FUN_00365b6c/FUN_000839d8.
 * Confidence: low   Notes: unaff_x25 self/context register-global; extraout_x1 carried
 * from FUN_0049c704; thunk_FUN_001a0754 rendered as FUN_001a0754. */
static word_t sk_r30_0049063c(word_t param_1, word_t param_2, word_t param_3, word_t param_4,
                              long param_5, word_t param_6, long unaff_x25 /* self register-global */)
{
    ulong uVar1;
    long lVar2;
    long lVar10;
    long lVar9;
    word_t extraout_x1;      /* carried from FUN_0049c704 (x1) */
    long extraout_x8;        /* carried value (x8) */
    char *puVar7;
    char *puVar8;
    unsigned char auVar11[16];
    word_t local_180;
    word_t uStack_178;
    word_t uStack_170;
    long local_168;
    word_t local_160;
    word_t uStack_158;
    word_t local_150;
    word_t uStack_148;
    word_t local_140;
    long lStack_138;
    word_t local_130;
    word_t uStack_128;
    word_t uStack_120;
    word_t uStack_118;
    word_t local_110;
    long lStack_108;
    long local_f8;
    unsigned char auStack_f0[80];
    word_t local_a0;
    word_t uStack_98;
    long local_90[3];
    word_t local_78;
    word_t uVar5, uVar6;

    lVar9 = *(long *)(param_5 + 0x10);
    FUN_004abdc4();
    if (lVar9 != 0) {
        FUN_001a0754(0, lVar9, 0);
        lVar10 = 0;
        do {
            FUN_0049c704(param_5 + 0x20 + lVar10 * 0x58, &local_f8);
            lVar2 = local_f8;
            local_a0 = extraout_x1;
            uStack_98 = param_4;
            FUN_004a4ac4(auStack_f0, &local_160, 0x657be0, &DAT_005a3c88);
            if (lStack_138 == 1) {
                FUN_0036b270(param_4);
                FUN_00350878(&local_160);
                uVar5 = FUN_004a4b14();
                if (lVar2 < 1) {
                    CL4_SWBP(0x49096c);
                }
                FUN_004ac41c(uVar5, lVar2 + -1);
                FUN_0047ce4c(local_90);
            } else {
                uStack_128 = uStack_158;
                local_130 = local_160;
                uStack_118 = uStack_148;
                uStack_120 = local_150;
                lStack_108 = lStack_138;
                local_110 = local_140;
                puVar8 = (char *)&DAT_005a3ca0;
                FUN_004a4ac4(&local_130, &local_160, 0x657bf8);
                uStack_178 = uStack_148;
                local_180 = local_150;
                local_168 = lStack_138;
                uStack_170 = local_140;
                if (lStack_138 == 0) {
                    FUN_0036b270(param_4);
                    puVar7 = (char *)&DAT_005a3ca0;
                    FUN_004a4b14(&local_130, 0x657bf8);
                    FUN_0006b6f4();
                    FUN_00351e3c();
                    /* 12-byte aggregate returned in auVar11 (x0:x1:low(w2)) */
                    auVar11[0] = (unsigned char)FUN_0029fa0c();
                    local_78 = 0x675c68;
                    FUN_00355538(0x686160);
                    local_90[0] = (long)FUN_0036a940();
                    {
                        /* 16-byte aggregate copy: arrays are not assignable in C */
                        unsigned char *dst = (unsigned char *)(local_90[0] + 0x10);
                        int copy_i;
                        for (copy_i = 0; copy_i < 16; copy_i++) {
                            dst[copy_i] = auVar11[copy_i];
                        }
                    }
                    *(char **)(local_90[0] + 0x20) = puVar7;
                    *(char **)(local_90[0] + 0x28) = puVar8;
                    if (local_168 != 0) {
                        FUN_0034cc24(&local_180);
                        FUN_004a4b14();
                    }
                } else {
                    FUN_0036b270(param_4);
                    FUN_00350878(&local_130);
                    FUN_004a4b14();
                    FUN_00310d98(&local_180, local_90);
                }
                if (lVar2 < 0) {
                    CL4_SWBP(0x490970);
                }
                for (; lVar2 != 0; lVar2 = lVar2 + -1) {
                    FUN_00319808(local_90, &local_160);
                    uVar5 = uStack_148;
                    uVar6 = FUN_0006a4c0(&local_160, uStack_148);
                    FUN_0047cdbc(uVar6, local_90, uVar5);
                    FUN_000026e8(&local_160);
                }
            }
            FUN_0049c714(&local_f8);
            uVar1 = *(ulong *)(unaff_x25 + 0x10);
            if (*(ulong *)(unaff_x25 + 0x18) >> 1 <= uVar1) {
                FUN_0006b42c();
                FUN_000dbc98();
                FUN_001a0754();
            }
            lVar10 = lVar10 + 1;
            *(ulong *)(unaff_x25 + 0x10) = uVar1 + 1;
            FUN_00310d98(local_90, unaff_x25 + uVar1 * 0x20 + 0x20);
        } while (lVar10 != lVar9);
    }
    FUN_0009461c();
    uVar5 = FUN_00002534();
    FUN_004aa5f8(0x657bf0);
    FUN_00350968();
    uVar6 = FUN_004a42a0();
    FUN_0045567c(&local_f8, &local_130, uVar5, uVar6);
    FUN_00351f34();
    uVar5 = FUN_00365b6c(param_1, &local_f8, extraout_x8 + 8, param_6, 6);
    FUN_000839d8(param_1, uVar5 ^ 1, 1, param_6);
    return 0;
}

/* FUN_00490c18 @ 0x00490c18  (est. sk_r30_transform_in_place)
 * Ghidra: void FUN_00490c18(undefined8 *param_1)
 * Replaces the word at *param_1 with FUN_0019e93c(*param_1) (a one-word transform).
 * Confidence: medium */
static word_t sk_r30_00490c18(word_t *param_1)
{
    word_t uVar1;

    uVar1 = FUN_0019e93c(*param_1);
    *param_1 = uVar1;
    return 0;
}

/* FUN_00490e40 @ 0x00490e40  (est. sk_r30_tail_call_build)
 * Ghidra: void FUN_00490e40(undefined8 param_1,undefined8 param_2,undefined8 *param_3)
 * Builds a 2-slot (12-byte) result via FUN_00490b98 from a 12-byte aggregate returned by
 * FUN_00351124 and a context word triple, then stores it at the register-global *unaff_x19.
 * Confidence: low   Notes: unaff_x19/unaff_x20 register-globals; 12-byte aggregate split
 * (x0 low 8, x1 high 4) with the high 4 modeled as extraout_x1. */
static word_t sk_r30_00490e40(word_t param_1, word_t param_2, word_t *param_3,
                              word_t *unaff_x19 /* self register-global */,
                              word_t *unaff_x20 /* context register-global */)
{
    word_t uVar1;
    word_t extraout_w1;   /* carried (w1) stored into *(unaff_x19+1) */
    word_t agg_lo;        /* FUN_00351124 x0 (auVar2._0_8_) */
    word_t agg_hi4;       /* FUN_00351124 x1 high 4 (auVar2._8_4_) */
    word_t out_hi;        /* upper word of 16-byte result (dropped by Ghidra) */

    agg_lo = FUN_00351124();
    uVar1 = FUN_00490b98(agg_lo, agg_hi4, *param_3, unaff_x20[0], unaff_x20[1], unaff_x20[2], &out_hi);
    *unaff_x19 = uVar1;
    *(unsigned char *)((char *)unaff_x19 + 8) = (unsigned char)extraout_w1;
    return 0;
}

/* FUN_0049153c @ 0x0049153c  (est. sk_r30_finalize_step)
 * Ghidra: void FUN_0049153c(void)
 * Runs a finalize/close step: seeds with 0, then drives FUN_00351d18 and sk_r30_00491b58.
 * Confidence: low */
static word_t sk_r30_0049153c(void)
{
    FUN_0049d1ec(0);
    FUN_00351d18();
    sk_r30_00491b58(FUN_00351d18());   /* param_1 = result of preceding FUN_00351d18 */
    return 0;
}

/* FUN_004917d8 @ 0x004917d8  (est. sk_r30_report_string)
 * Ghidra: void FUN_004917d8(void)
 * Builds a 16-byte stack pair from FUN_00354a34, formats a message string (0x6753a0) and
 * drives the reporting helpers with the carried value and register-global unaff_x30.
 * Confidence: low   Notes: 16-byte stack aggregate modeled as wpair_t; unaff_x30 register-global. */
static word_t sk_r30_004917d8(word_t unaff_x30 /* register-global */)
{
    word_t uVar1, uVar2;
    wpair_t pair;

    pair.lo = FUN_00354a34();
    uVar2 = pair.hi;
    uVar1 = FUN_000f5e08();
    FUN_0042b708(&pair, 0x6753a0, uVar1);
    FUN_004630c4();
    FUN_003a25d4(uVar2);
    FUN_003505c4();
    uVar1 = sk_r30_0049115c(0, 0, 0, 0, 0);   /* 5 args dropped by Ghidra (unmodeled regs) */
    FUN_00354ef8(uVar1, unaff_x30);
    return 0;
}

/* FUN_00491b58 @ 0x00491b58  (est. sk_r30_obj_init_value)
 * Ghidra: void FUN_00491b58(undefined8 param_1)
 * Allocates a fresh object via FUN_0036a940 and initializes its fields: +0x18=param_1,
 * +0x20=0, +0x10=0.
 * Confidence: medium */
static word_t sk_r30_00491b58(word_t param_1)
{
    long lVar1;

    FUN_000dce50();
    lVar1 = (long)FUN_0036a940();
    *(word_t *)(lVar1 + 0x18) = param_1;
    *(word_t *)(lVar1 + 0x20) = 0;
    *(word_t *)(lVar1 + 0x10) = 0;
    return 0;
}

/* FUN_00492038 @ 0x00492038  (est. sk_r30_lookup_byte)
 * Ghidra: undefined1 FUN_00492038(ulong param_1)
 * Returns the byte at DAT_005a5ec8[param_1 & 0xff] from a 256-entry lookup table.
 * Confidence: medium */
static word_t sk_r30_00492038(ulong param_1)
{
    return ((unsigned char *)&DAT_005a5ec8)[param_1 & 0xff];
}

/* FUN_00492758 @ 0x00492758  (est. sk_r30_init_report_chain)
 * Ghidra: void FUN_00492758(void)
 * Runs a long init/report chain; on FUN_00365b6c()==0 reports the string at DAT_00687c80,
 * otherwise reports DAT_00687cd0 (after building context via DAT_00687ca8).
 * Confidence: low   Notes: unaff_x30 register-global; DAT pointers used as string addresses. */
static word_t sk_r30_00492758(word_t unaff_x30 /* register-global */)
{
    int iVar1;
    char *puVar2;

    FUN_00354a34();
    FUN_00349a18();
    FUN_004ac824();
    FUN_00351488();
    FUN_00370538();
    FUN_004abdb8();
    FUN_004ac824();
    FUN_00370538();
    FUN_0036b270();
    FUN_004ab304();
    FUN_00351aec();
    iVar1 = (int)FUN_00365b6c();
    if (iVar1 == 0) {
        puVar2 = (char *)&DAT_00687c80;
    } else {
        FUN_0036b118();
        FUN_00355538((word_t)&DAT_00687ca8);
        FUN_0036a940();
        FUN_004ac9e4();
        puVar2 = (char *)&DAT_00687cd0;
    }
    FUN_00355538((word_t)puVar2);
    FUN_0036a940();
    FUN_004ac240();
    FUN_00354ef8(unaff_x30);
    return 0;
}

/* FUN_00493354 @ 0x00493354  (est. sk_r30_build_and_dispatch)
 * Ghidra: undefined8 FUN_00493354(undefined8 param_1)
 * Prepares param_1 (FUN_0049341c), selects a target (0x675c68 or the field at
 * (uVar2&0xffffffffffffffb)+0x10 based on the carried w8 from FUN_004ab034), builds and
 * dispatches a record via FUN_00492eec, returning the value captured up front.
 * Confidence: low   Notes: extraout_w8 carried from FUN_004ab034; 12-byte aggregate from
 * FUN_0041c28c split (x0 low 8, x1 high 4). */
static word_t sk_r30_00493354(word_t param_1)
{
    word_t uVar1, uVar3;
    ulong uVar2;
    int extraout_w8;      /* carried from FUN_004ab034 (w8) */
    wpair_t auVar4;       /* 16-byte aggregate from FUN_00019858 */
    word_t auVar5_lo;     /* FUN_0041c28c x0 (auVar5._0_8_) */
    word_t auVar5_hi4;    /* FUN_0041c28c x1 high 4 (auVar5._8_4_) */
    unsigned char auStack_58[56];

    uVar1 = FUN_0006f6b4();
    sk_r30_0049341c(param_1, 0);   /* unaff_x21 (mask register-global) unmodeled in caller */
    uVar2 = FUN_004ab034();
    if (extraout_w8 == 0xe) {
        uVar3 = *(word_t *)((uVar2 & 0xffffffffffffffb) + 0x10);
    } else {
        uVar3 = 0x675c68;
    }
    FUN_0036b118();
    FUN_0041cb78();
    auVar4.lo = FUN_00019858(auStack_58);
    FUN_0041c1c4(auVar4.lo, auVar4.hi, uVar3, 0, 1);
    FUN_0041c0c0(auStack_58);
    FUN_004a4214(auStack_58);
    auVar5_lo = FUN_0041c28c(1);
    sk_r30_00492eec(param_1, auVar5_lo, auVar5_hi4 & 1, uVar3, 1);
    return uVar1;
}

/* FUN_0049466c @ 0x0049466c  (est. sk_r30_scan_and_report)
 * Ghidra: void FUN_0049466c(undefined8 param_1,long param_2,undefined8 param_3,undefined8 param_4)
 * Walks a 0x58-stride table (count at *(unaff_x20[2]+0x10), entries at +0x20) until it finds
 * an entry whose (char local_148 != 1 && local_150 == param_2), then reports it. Traps if the
 * table is exhausted before a match.
 * Confidence: low   Notes: unaff_x20 register-global (word triple); extraout_x8 carried;
 * thunk_FUN_0036b270 rendered as FUN_0036b270; 16-byte aggregate auVar6 split as wpair. */
static word_t sk_r30_0049466c(word_t param_1, long param_2, word_t param_3, word_t param_4,
                              word_t *unaff_x20 /* context register-global */)
{
    long lVar1;
    word_t uVar2, uVar3;
    long extraout_x8;   /* carried value (x8) */
    long lVar5;
    wpair_t auVar6;     /* 16-byte aggregate from FUN_0036b270 */
    unsigned char auStack_198[72];
    long local_150;
    char local_148;
    unsigned char auStack_130[88];
    word_t local_d8;
    word_t uStack_d0;
    unsigned char local_c8[8];
    unsigned char auStack_c0[96];

    uVar2 = unaff_x20[0];
    uVar3 = unaff_x20[1];
    lVar5 = *(long *)(unaff_x20[2] + 0x10);
    lVar1 = unaff_x20[2] + 0x20;
    while (true) {
        if (lVar5 == 0) {
            CL4_SWBP(0x494704);
        }
        FUN_0049c704(lVar1, auStack_130);
        local_d8 = uVar2;
        uStack_d0 = uVar3;
        FUN_00117cc4(auStack_198, auStack_130, 0x68);
        if (local_148 != '\x01' && local_150 == param_2) break;
        FUN_0036b270(uVar3);
        FUN_0049c714(auStack_198);
        lVar1 = lVar1 + 0x58;
        lVar5 = lVar5 + -1;
    }
    FUN_00117cc4(local_c8, auStack_130, 0x68);
    FUN_0041c190();
    FUN_00354f1c();
    auVar6.lo = FUN_0036b270(uVar3);
    FUN_00351450(auStack_130, auVar6.lo, auVar6.hi, auStack_c0);
    FUN_0047c62c();
    FUN_003a25d4(param_2);
    FUN_0049c714(local_c8);
    FUN_00351f34();
    FUN_00365b6c(param_1, auStack_130, extraout_x8 + 8, param_4, 7);
    return 0;
}

/* FUN_004948e0 @ 0x004948e0  (est. sk_r30_forward_9490c)
 * Ghidra: void FUN_004948e0(void)
 * Thin wrapper that calls sk_r30_0049490c.
 * Confidence: low */
static word_t sk_r30_004948e0(void)
{
    /* 9 params (register-globals / stack-passed) all unmodeled in this thin forwarder */
    sk_r30_0049490c(0, 0, 0, 0, 0, 0, 0, 0, 0);
    return 0;
}

/* FUN_00494dd0 @ 0x00494dd0  (est. sk_r30_select_bits)
 * Ghidra: void FUN_00494dd0(char param_1)
 * Selects 0x10 (if param_1==1) or 0xf, then calls sk_r30_00494b44(sel, 1).
 * Confidence: medium */
static word_t sk_r30_00494dd0(char param_1)
{
    word_t uVar1;

    FUN_004ab65c();
    if (param_1 == '\x01') {
        uVar1 = 0x10;
    } else {
        uVar1 = 0xf;
    }
    sk_r30_00494b44(uVar1, 1, 0, 0);   /* param_3 + unaff_x30 dropped by Ghidra */
    return 0;
}

/* FUN_00495298 @ 0x00495298  (est. sk_r30_dispatch_dual_check)
 * Ghidra: void FUN_00495298(void)
 * Runs two alternate paths (each: indirect call via a carried code pointer, then
 * FUN_00491644 + FUN_0036b118), an indirect call via in_x7, then masks the two captured
 * values by in_x7 and reports through FUN_0049153c.
 * Confidence: low   Notes: in_x5/in_x6/in_x7 incoming registers; extraout_x8_00/01 carried
 * code pointers; 16-byte aggregate auVar4 split as wpair. */
static word_t sk_r30_00495298(word_t in_x5 /* register */, word_t in_x6 /* register */,
                              word_t in_x7 /* register: code * */)
{
    word_t uVar1;
    ulong uVar2, uVar3;
    word_t extraout_x8;    /* carried value (x8) */
    wpair_t auVar4;        /* 16-byte aggregate from FUN_0007c1c4 */

    FUN_00084220();
    FUN_004ab5d4(in_x5);
    FUN_00351274();
    uVar1 = (*((code *)0))();        /* (extraout_x8_00)() carried indirect target */
    uVar2 = FUN_00491644(uVar1);     /* param_1 = preceding indirect-call result */
    FUN_0036b118(uVar1);
    FUN_004ab5d4(in_x6);
    FUN_00351384();
    uVar1 = (*((code *)0))();        /* (extraout_x8_01)() carried indirect target */
    uVar3 = FUN_00491644(uVar1);     /* param_1 = preceding indirect-call result */
    FUN_0036b118(uVar1);
    FUN_000e15d8();
    (*((code *)in_x7))();
    FUN_004ac114();
    FUN_0036b118(uVar3 & (ulong)in_x7);
    FUN_0036b118(uVar2 & (ulong)in_x7);
    auVar4.lo = FUN_0007c1c4();
    FUN_00084234(auVar4.lo, auVar4.hi, extraout_x8);
    sk_r30_0049153c();
    return 0;
}

/* FUN_004956c0 @ 0x004956c0  (est. sk_r30_alloc_and_fill)
 * Ghidra: void FUN_004956c0(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,undefined8 param_5)
 * Allocates an object via FUN_0036a940, fills its fields (+0x10/+0x18 from a 12-byte
 * FUN_0001a1c8 result, +0x20=param_3, +0x28=param_4, +0x38=0, +0x50=0x80), captures a
 * computed value at +0x58, then finalizes with the tagged pointer uVar1|0x3000000000000000.
 * Confidence: low   Notes: extraout_x8 carried code pointer; 12-byte aggregate auVar4 split. */
static word_t sk_r30_004956c0(word_t param_1, word_t param_2, word_t param_3, word_t param_4,
                              word_t param_5)
{
    ulong uVar1;
    word_t uVar2, uVar3;
    word_t auVar4_lo;   /* FUN_0001a1c8 x0 (auVar4._0_8_) */
    word_t auVar4_hi4;  /* FUN_0001a1c8 x1 high 4 (auVar4._8_4_) */

    FUN_00350a28();
    FUN_004aab60();
    uVar1 = FUN_0036a940();
    FUN_0041cb78();
    FUN_00351790();
    FUN_00354d5c();
    auVar4_lo = FUN_0001a1c8();
    *(long *)(uVar1 + 0x10) = (long)auVar4_lo;
    *(ulong *)(uVar1 + 0x18) = (ulong)(auVar4_hi4 & 1);
    *(word_t *)(uVar1 + 0x20) = param_3;
    *(word_t *)(uVar1 + 0x28) = param_4;
    *(word_t *)(uVar1 + 0x38) = 0;
    *(unsigned char *)(uVar1 + 0x50) = 0x80;
    FUN_004ab5d4(param_5);
    FUN_00100efc();
    uVar2 = (*((code *)0))();        /* (extraout_x8)() carried indirect target */
    uVar3 = FUN_00491644(uVar2);     /* param_1 = preceding indirect-call result */
    FUN_0036b118(uVar2);
    *(word_t *)(uVar1 + 0x58) = uVar3;
    sk_r30_0049153c();               /* void signature; tagged-pointer arg dropped */
    return 0;
}

/* FUN_00495aec @ 0x00495aec  (est. sk_r30_collection_init_fill)
 * Ghidra: void FUN_00495aec(undefined8 param_1,undefined8 param_2,uint param_3,undefined8 param_4,undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,undefined8 param_9,undefined8 param_10,undefined8 param_11,undefined8 param_12,undefined8 param_13,undefined8 param_14,undefined1 param_15)
 * Allocates an object via FUN_0036a940, initializes a collection header (kind from
 * param_3&0xff, element/backing fields, 16-byte aggregate results from FUN_0035300c /
 * FUN_00350518), stores params 11-15, and finalizes with the tagged pointer
 * uVar3|0x1000000000000000.
 * Confidence: low   Notes: in_stack_000000a8/in_stack_000000b0 stack-passed register
 * artifacts modeled as trailing params; extraout_x8 carried; extraout_x8_00 carried code
 * pointer; 16-byte aggregates modeled as wpair_t. */
static word_t sk_r30_00495aec(word_t param_1, word_t param_2, uint param_3, word_t param_4,
                              word_t param_5, word_t param_6, word_t param_7, word_t param_8,
                              word_t param_9, word_t param_10, word_t param_11, word_t param_12,
                              word_t param_13, word_t param_14, unsigned char param_15,
                              word_t in_stack_000000a8 /* stack-passed register */,
                              word_t in_stack_000000b0 /* stack-passed register: code * */)
{
    word_t uVar1;
    bool bVar2;
    ulong uVar3;
    word_t extraout_x8;    /* carried value (x8) */
    wpair_t auVar4;        /* 16-byte aggregate from FUN_0035300c / FUN_00350518 */

    auVar4.lo = FUN_0035300c();
    FUN_004aada4();
    uVar3 = FUN_0036a940();
    bVar2 = (param_3 & 0xff) == 1;
    *(word_t *)(uVar3 + 0x10) = 0;
    *(word_t *)(uVar3 + 0x18) = 0;
    uVar1 = 0;
    if (!bVar2) {
        uVar1 = auVar4.hi;
    }
    *(word_t *)(uVar3 + 0x20) = uVar1;
    *(bool *)(uVar3 + 0x28) = bVar2;
    FUN_004ab5d4(in_stack_000000a8);
    FUN_00350a04();
    (*((code *)0))();        /* (extraout_x8_00)() carried indirect target */
    FUN_00491644((*((code *)0))());   /* param_1 = preceding indirect-call result */
    FUN_004ac2d0();
    FUN_0036b118();
    *(long *)(uVar3 + 0x30) = (long)auVar4.lo;
    FUN_0036b270(param_5);
    auVar4.lo = FUN_00350518(&param_11);
    (*((code *)in_stack_000000b0))(auVar4.lo, auVar4.hi, param_7, param_8);
    *(word_t *)(uVar3 + 0x40) = param_12;
    *(word_t *)(uVar3 + 0x38) = param_11;
    *(word_t *)(uVar3 + 0x50) = param_14;
    *(word_t *)(uVar3 + 0x48) = param_13;
    *(unsigned char *)(uVar3 + 0x58) = param_15;
    FUN_00353238(uVar3 | 0x1000000000000000, param_6, extraout_x8);
    sk_r30_0049153c();
    return 0;
}
/* FUN_00490970 @ 0x00490970  (est. sk_r30_box_value)
 * Ghidra: void FUN_00490970(void)
 * Initializes a local box, then either tears it down if the initialized
 * value is 1 (is-empty sentinel) or forwards it into a type-erased boxed
 * value slot at unaff_x20+0x58/0x60. unaff_x20 is a self/context pointer.
 * Confidence: low   Notes: unaff_x20 register-global modeled as trailing param */
static word_t sk_r30_00490970(word_t unaff_x20 /* unaff_x20: self/context register-global */)
{
    byte local_60[16];
    byte auStack_50[24];
    long local_38;
    wpair_t auVar1;

    FUN_004ab128();
    FUN_004a4ac4(unaff_x20 + 8, local_60);
    if (local_38 == 1) {
        FUN_004aaccc();
        FUN_004a4b14(local_60);
        FUN_00019858();
    } else {
        FUN_0034cc24();
        auVar1 = ((wpair_t (*)())&FUN_004a4b14)(auStack_50);
        FUN_003507e0(auVar1.lo, auVar1.hi,
                     *(word_t *)(unaff_x20 + 0x58),
                     *(word_t *)(unaff_x20 + 0x60));
        FUN_0029fa0c();
    }
    return 0;
}

/* FUN_00490c44 @ 0x00490c44  (est. sk_r30_string_hash_store)
 * Ghidra: void FUN_00490c44(void)
 * Builds a string key/value pair from a metadata/encoding call and stores
 * the resulting pair through unaff_x19 (a store pointer). unaff_x20 is a
 * key/value context pointer.
 * Confidence: low   Notes: unaff_x19/unaff_x20 register-globals as trailing params */
static word_t sk_r30_00490c44(word_t unaff_x19 /* unaff_x19: store pointer register-global */,
                              word_t unaff_x20 /* unaff_x20: key/value context register-global */)
{
    wpair_t auVar2;
    word_t uVar1;

    auVar2 = ((wpair_t (*)())&FUN_00351124)();
    uVar1 = sk_r30_00490b78(auVar2.lo, auVar2.hi,
                            *(word_t *)unaff_x20, *(word_t *)(unaff_x20 + 1),
                            *(word_t *)(unaff_x20 + 2));
    *(word_t *)unaff_x19 = uVar1;
    return 0;
}

/* FUN_00490ea8 @ 0x00490ea8  (est. sk_r30_emit_element)
 * Ghidra: undefined8 FUN_00490ea8(undefined8 param_1,undefined8 param_2,undefined8 param_3)
 * Emits one element into the collection: records a key param_1, then calls
 * into the element-append (param_3) and value-materialize (param_2) paths,
 * returning the prior metadata result.
 * Confidence: low   Notes: param meaning inferred from call sequence */
static word_t sk_r30_00490ea8(word_t param_1, word_t param_2, word_t param_3)
{
    word_t uVar1;

    uVar1 = FUN_0049c35c();
    FUN_0036b118(param_3);
    FUN_003a25d4(param_2);
    return uVar1;
}

/* FUN_0049156c @ 0x0049156c  (est. sk_r30_dictionary_contains)
 * Ghidra: bool FUN_0049156c(undefined8 param_1,undefined8 param_2,long param_3)
 * Searches the hash table of the storage object at param_3+0x18 for an entry
 * whose (key,value) pair equals (unaff_x20, unaff_x19); returns whether found.
 * Confidence: low   Notes: unaff_x19/unaff_x20 register-globals as trailing params */
static word_t sk_r30_0049156c(word_t param_1, word_t param_2, word_t param_3,
                              word_t unaff_x19 /* unaff_x19: value key register-global */,
                              word_t unaff_x20 /* unaff_x20: key register-global */)
{
    long lVar1;
    ulong uVar2;
    long *plVar3;
    long lVar4;

    FUN_003504d0();
    lVar1 = sk_r30_00493354(*(word_t *)(param_3 + 0x18));
    plVar3 = (long *)(lVar1 + 0x28);
    lVar4 = *(long *)(lVar1 + 0x10);
    while (lVar4 != 0) {
        if (*plVar3 != 0) {
            if (plVar3[-1] == unaff_x20 && *plVar3 == unaff_x19) break;
            FUN_0035053c();
            uVar2 = FUN_002a0cf8();
            if ((uVar2 & 1) != 0) break;
        }
        plVar3 = plVar3 + 7;
        lVar4 = lVar4 + -1;
    }
    FUN_0036b118(lVar1);
    return lVar4 != 0;
}

/* FUN_00491864 @ 0x00491864  (est. sk_r30_set_append_element)
 * Ghidra: void FUN_00491864(void)
 * Allocates a new bucket object, initializes its payload (data at +0x10 and
 * the unaff_x20 value), and appends it to the backing set storage via a
 * tagged insert call.
 * Confidence: low   Notes: unaff_x20 register-global as trailing param */
static word_t sk_r30_00491864(word_t unaff_x20 /* unaff_x20: element value register-global */)
{
    word_t uVar1;
    ulong uVar2;

    uVar1 = FUN_00350a28();
    FUN_004aad30();
    uVar2 = FUN_0036a940();
    *(word_t *)(uVar2 + 0x10) = uVar1;
    *(word_t *)(uVar2 + 0x18) = unaff_x20;
    sk_r30_0049153c();
    return 0;
}

/* FUN_00491b88 @ 0x00491b88  (est. sk_r30_set_destroy_bucket)

/* FUN_00491b88 @ 0x00491b88  (est. sk_r30_set_destroy_bucket)
 * Ghidra: void FUN_00491b88(void)
 * Releases the key and value stored at unaff_x20+0x10/+0x18, then releases
 * the container object itself.
 * Confidence: low   Notes: unaff_x20 register-global as trailing param */
static word_t sk_r30_00491b88(word_t unaff_x20 /* unaff_x20: container register-global */)
{
    FUN_0036b118(*(word_t *)(unaff_x20 + 0x10));
    FUN_004abf50(*(word_t *)(unaff_x20 + 0x18));
    FUN_0036b118();
    return 0;
}

/* FUN_0049204c @ 0x0049204c  (est. sk_r30_collection_release_backing)
 * Ghidra: void FUN_0049204c(void)
 * Releases the shared backing storage object for the collection.
 * Confidence: low   Notes: thunk-like body */
static word_t sk_r30_0049204c(void)
{
    FUN_0036b270();
    return 0;
}

/* FUN_00492850 @ 0x00492850  (est. sk_r30_register_closure_callback)
 * Ghidra: void FUN_00492850(long param_1)
 * Reads the closure context (via in_x7), invokes a pre-callback and then,
 * unless a guard (unaff_x21) is set, stores the context into param_1+0x18
 * and dispatches a chained callback via the vtable at context+0x20.
 * Confidence: low   Notes: decompiler artifacts (SUB_54ffff60f100041f placeholder,
 *   in_x4/in_x7/extraout_x8/unaff_x21) rendered mechanically */
static word_t sk_r30_00492850(word_t param_1,
                              word_t in_x4 /* in_x4: indirect callback fn pointer */,
                              word_t in_x7 /* in_x7: context pointer */,
                              word_t extraout_x8 /* extraout_x8: stack offset carried from prior call */,
                              word_t unaff_x21 /* unaff_x21: guard register-global */)
{
    word_t uVar1;
    long lVar2;

    lVar2 = *(long *)(in_x7 + -8);
    (*(code *)0x54ffff60f100041fULL)(*(word_t *)(lVar2 + 0x40));
    (*(code *)in_x4)(&((long *)0)[-1] - (extraout_x8 + 0xf & 0xfffffffffffffff0));
    if (unaff_x21 == 0) {
        *(long *)(param_1 + 0x18) = in_x7;
        uVar1 = FUN_00077024(param_1);
        (*(code *)(*(long *)(lVar2 + 0x20)))
            (uVar1, &((long *)0)[-1] - (extraout_x8 + 0xf & 0xfffffffffffffff0), in_x7);
    }
    return 0;
}

/* FUN_0049341c @ 0x0049341c  (est. sk_r30_array_get_elements)
 * Ghidra: undefined8 FUN_0049341c(undefined8 param_1)
 * Walks the element buffer of an array: validates the shape tag, and for a
 * non-empty inline store dereferences the buffer, recursively visiting the
 * tail element while releasing owned intermediate objects.
 * Confidence: low   Notes: recursion via self-call; SWBP fail-closed trap */
static word_t sk_r30_0049341c(word_t param_1, word_t unaff_x21 /* unaff_x21: mask register-global */)
{
    long lVar2;
    uint extraout_w8;
    ulong uVar3;

    FUN_004ab26c();
    if ((extraout_w8 & 0xfffffffe | (uint)param_1 >> 2 & 1) - 3 < 2) {
        lVar2 = sk_r30_004922d8(param_1, 0, 0, 0);
        if (*(long *)(lVar2 + 0x10) == 0) {
            CL4_SWBP(0x4934a8);
        }
        uVar3 = *(ulong *)(lVar2 + 0x20);
        FUN_004ac114();
        FUN_0036b270(uVar3 & unaff_x21);
        FUN_0036b118(lVar2);
        param_1 = sk_r30_0049341c(uVar3, unaff_x21);
        FUN_0036b118(uVar3 & unaff_x21);
    } else {
        FUN_004acccc();
    }
    return param_1;
}

/* FUN_0049478c @ 0x0049478c  (est. sk_r30_trailing_element_cleanup)
 * Ghidra: void FUN_0049478c(void)
 * Thin forwarder into the element-cleanup routine.
 * Confidence: low   Notes: trampoline body */
static word_t sk_r30_0049478c(void)
{
    sk_r30_00494810((code)0, NULL, 0, 0, 0, 0, 0, 0, 0);
    return 0;
}

/* FUN_004948e4 @ 0x004948e4  (est. sk_r30_concurrent_iterator_step)
 * Ghidra: void FUN_004948e4(void)
 * Thin forwarder into the iterator advance routine.
 * Confidence: low   Notes: trampoline body */
static word_t sk_r30_004948e4(void)
{
    sk_r30_0049490c(NULL, NULL, 0, 0, 0, 0, 0, 0, 0);
    return 0;
}

/* FUN_00494e2c @ 0x00494e2c  (est. sk_r30_range_compare_bounds)
 * Ghidra: undefined8 FUN_00494e2c(void)
 * Computes two bound metadata values by driving the metadata protocol
 * through two encoding phases and returns the second (upper) bound value,
 * releasing the first.
 * Confidence: low   Notes: sequence of metadata-encoding calls */
static word_t sk_r30_00494e2c(void)
{
    word_t uVar1;
    word_t uVar2;

    FUN_0049c874(0);
    FUN_00351390(0x13);
    uVar1 = sk_r30_00494b44(0, 0, 0, 0);
    FUN_00351390(0x10);
    uVar2 = sk_r30_00494b44(0, 0, 0, 0);
    FUN_0036b118(uVar1);
    return uVar2;
}

/* FUN_00495388 @ 0x00495388  (est. sk_r30_dictionary_store_key)
 * Ghidra: void FUN_00495388(undefined4 param_1,undefined8 param_2)
 * Allocates a storage object, seeds its hash seed with param_1, and inserts
 * param_2 as the tagged (key,value) pair into the dictionary backing store.
 * Confidence: low   Notes: param_1 is a 32-bit seed */
static word_t sk_r30_00495388(uint param_1, word_t param_2)
{
    ulong uVar1;
    uint local_e0[44];

    FUN_004aa7bc();
    uVar1 = FUN_0036a940();
    local_e0[0] = param_1;
    FUN_0049ca14(local_e0);
    FUN_004ac61c(uVar1 + 0x10);
    sk_r30_0049153c();
    return 0;
}

/* FUN_00495768 @ 0x00495768  (est. sk_r30_string_append_buffer)
 * Ghidra: void FUN_00495768(undefined8 param_1,...)
 * Appends one string buffer segment: initializes storage, forwards the
 * segment's data/size through the append machinery, and re-roots the
 * resulting tail into the string builder.
 * Confidence: low   Notes: extraout_x8/unaff_x30 decompiler artifacts modeled
 *   as locals/params; multiple re-rooting calls */
static word_t sk_r30_00495768(word_t param_1, word_t param_2, word_t param_3,
                              word_t param_4, word_t param_5, word_t param_6,
                              word_t param_7,
                              word_t unaff_x30 /* unaff_x30: context register-global */)
{
    code *extraout_x8;
    wpair_t auVar1;

    FUN_00084220();
    FUN_00407ab8();
    FUN_004ab5d4(param_7);
    FUN_00084180();
    (*extraout_x8)();
    sk_r30_00491644(0);
    FUN_00351d18();
    FUN_0036b118();
    auVar1 = ((wpair_t (*)())&FUN_00350618)();
    sk_r30_00493dfc(auVar1.lo, auVar1.hi, param_3, param_4, unaff_x30);
    FUN_0036b118(param_4 & 0xffffffffffffffb);
    auVar1 = ((wpair_t (*)())&FUN_003504ac)();
    FUN_00084234(auVar1.lo, auVar1.hi, unaff_x30);
    sk_r30_0049153c();
    return 0;
}

/* FUN_00495bcc @ 0x00495bcc  (est. sk_r30_closure_call_result)
 * Ghidra: undefined1 [16] FUN_00495bcc(undefined8 param_1,undefined8 param_2,undefined8 param_3,long param_4)
 * Invokes the closure function pointer at param_4+0x20 through the runtime
 * dispatch helper, passing the boxed arguments, and returns the 16-byte
 * result (value + a success/error flag byte).
 * Confidence: low   Notes: 16-byte (x0:x1) return modeled as wpair_t */
static word_t sk_r30_00495bcc(word_t param_1, word_t param_2, word_t param_3, word_t param_4)
{
    word_t uVar2;
    byte auVar3[16];
    word_t local_50;
    word_t uStack_48;
    word_t local_40;
    char local_38;

    uVar2 = *(word_t *)(param_4 + 0x20);
    local_50 = param_3;
    uStack_48 = param_1;
    {
        code *pcVar1;
        pcVar1 = (code *)FUN_003192d8(uVar2);
        (*pcVar1)(&local_40, &uStack_48, param_2, &local_50,
                  *(word_t *)(param_4 + 0x10), uVar2);
    }
    uVar2 = 0;
    if (local_38 != '\x01') {
        uVar2 = local_40;
    }
    auVar3[8] = local_38 == '\x01';
    /* auVar3._0_8_ holds the full 64-bit value = uVar2; the remaining 7 bytes
     * are zero-initialized per the decompile. word_t return = x0 = uVar2. */
    return uVar2;
}
/* ==================================================================== *
 * SKR30 chunk 5 transcription (15 addresses)
 * ==================================================================== */

/* FUN_00490a04 @ 0x00490a04  (est. sk_r30_box_value)
 * Ghidra: undefined8 FUN_00490a04(void)
 * Wraps a value into a Swift-style box: reads a type tag from the context object and,
 * depending on the tag, either promotes the direct value or initializes a boxed payload
 * through the string/alloc helpers before returning the boxed result.
 * Confidence: low   Notes: context register-global unaff_x20 used as base (+8 / *x20). */
static word_t sk_r30_00490a04(word_t *unaff_x20 /* unaff_x20: self/context register-global */)
{
    word_t uVar1;
    unsigned char auStack_a0[24];
    word_t local_88;
    unsigned char auStack_80[24];
    long local_68;
    unsigned char auStack_60[16];
    unsigned char auStack_50[24];
    long local_38;
    unsigned char *puVar2;

    FUN_004ab128();
    FUN_004a4ac4((word_t *)((char *)unaff_x20 + 8), auStack_60);
    if (local_38 == 1) {
        FUN_004aaccc();
        puVar2 = auStack_60;
    }
    else {
        FUN_0034cb88();
        FUN_004a4ac4(auStack_50, auStack_80);
        if (local_68 != 0) {
            FUN_00310d98(auStack_80, auStack_a0);
            uVar1 = FUN_0006a4c0(auStack_a0, local_88);
            FUN_003625e4(uVar1, local_88, 1);
            FUN_000026e8(auStack_a0);
            FUN_0007c1c4();
            uVar1 = FUN_004916f4(unaff_x20, 0);
            FUN_0034cc24();
            FUN_004a4b14(auStack_50);
            return uVar1;
        }
        FUN_0034cc24();
        puVar2 = auStack_50;
    }
    uVar1 = FUN_004a4b14(puVar2);
    uVar1 = FUN_004ac41c(uVar1, *unaff_x20);
    return uVar1;
}

/* FUN_00490c8c @ 0x00490c8c  (est. sk_r30_box_read)
 * Ghidra: void FUN_00490c8c(undefined8 *param_1,undefined8 param_2,undefined8 param_3)
 * Resolves a value through the sibling box decoder using the context's field at
 * unaff_x20+0x10 and stores the result into *param_1.
 * Confidence: low   Notes: returns through out param; context register-global unaff_x20. */
static word_t sk_r30_00490c8c(word_t *param_1, word_t param_2, word_t param_3,
                              word_t unaff_x20 /* unaff_x20: self/context register-global */)
{
    word_t uVar1;

    uVar1 = FUN_00490b0c(param_2, param_3, *(word_t *)(unaff_x20 + 0x10));
    *param_1 = uVar1;
    return 0;
}

/* FUN_00490efc @ 0x00490efc  (est. sk_r30_array_identity_find)
 * Ghidra: void FUN_00490efc(undefined8 param_1)
 * Walks an array of 0x58-byte element descriptors rooted at in_x4+0x20 (count in
 * in_x4+0x10), decoding each element and copying the one matching the (in_x23, in_x22)
 * identity pair into param_1; traps fail-closed if never found.
 * Confidence: low   Notes: in_x3/in_x4/in_x22/in_x23 register-globals; thunk call
 * rendered as FUN_0036b270. */
static word_t sk_r30_00490efc(word_t param_1,
                              word_t in_x3 /* register-global */,
                              long in_x4 /* register-global */,
                              long unaff_x22 /* register-global */,
                              long unaff_x23 /* register-global */)
{
    ulong uVar1;
    unsigned char auStack_120[56];
    long local_e8;
    long local_e0;
    unsigned char auStack_b8[88];
    long lVar2;

    lVar2 = *(long *)(in_x4 + 0x10);
    if (lVar2 != 0) {
        FUN_0034b318();
        in_x4 = in_x4 + 0x20;
        do {
            FUN_0049c704(in_x4, auStack_b8);
            FUN_00117cc4(auStack_120, auStack_b8, 0x68);
            if (local_e0 != 0) {
                if (local_e8 == unaff_x23 && local_e0 == unaff_x22) {
LAB_00490fa0:
                    FUN_00117cc4(param_1, auStack_120, 0x68);
                    FUN_0036b270(in_x3);
                    return 0;
                }
                FUN_00351e3c();
                uVar1 = FUN_002a0cf8();
                if ((uVar1 & 1) != 0) goto LAB_00490fa0;
            }
            FUN_0036b270(in_x3);
            FUN_0049c714(auStack_120);
            in_x4 = in_x4 + 0x58;
            lVar2 = lVar2 + -1;
        } while (lVar2 != 0);
    }
    FUN_004ac228();
    return 0;
}

/* FUN_00491600 @ 0x00491600  (est. sk_r30_context_alloc)
 * Ghidra: void FUN_00491600(void)
 * Allocates and initializes a fresh context/state object: runs several init/teardown
 * helpers, takes a new object from FUN_0036a940, stores the register-global context
 * pointer into +0x18 and zeroes the +0x10/+0x20 fields.
 * Confidence: low   Notes: unaff_x20 register-global stored as context pointer. */
static word_t sk_r30_00491600(word_t unaff_x20 /* unaff_x20: self/context register-global */)
{
    long lVar1;

    FUN_00491644(unaff_x20);
    FUN_00351d18();
    FUN_0036b118();
    FUN_004ac830();
    FUN_00002534();
    FUN_00359018();
    lVar1 = FUN_0036a940();
    *(word_t *)(lVar1 + 0x18) = unaff_x20;
    *(word_t *)(lVar1 + 0x20) = 0;
    *(word_t *)(lVar1 + 0x10) = 0;
    return 0;
}

/* FUN_004918ac @ 0x004918ac  (est. sk_r30_context_init_value)
 * Ghidra: long FUN_004918ac(void)
 * Runs the value-init helpers, allocates a fresh object, initializes its 0x10 header
 * region and returns the new object pointer.
 * Confidence: low */
static word_t sk_r30_004918ac(void)
{
    long lVar1;

    FUN_0035310c();
    FUN_004ac8fc();
    lVar1 = FUN_0036a940();
    FUN_00117cc4(lVar1 + 0x10);
    return lVar1;
}

/* FUN_00491bb4 @ 0x00491bb4  (est. sk_r30_teardown_chain)
 * Ghidra: void FUN_00491bb4(void)
 * Runs a short teardown sequence: sibling context teardown plus two runtime helpers.
 * Confidence: low */
static word_t sk_r30_00491bb4(void)
{
    FUN_00491b88(0);
    FUN_000dce50();
    FUN_0036b6ac();
    return 0;
}

/* FUN_00492078 @ 0x00492078  (est. sk_r30_box_byte_load)
 * Ghidra: void FUN_00492078(undefined1 *param_1,undefined8 *param_2)
 * Loads a byte-sized value via FUN_004816a8 of *param_2 and stores it into *param_1.
 * Confidence: low */
static word_t sk_r30_00492078(unsigned char *param_1, word_t *param_2)
{
    unsigned char uVar1;

    uVar1 = FUN_004816a8(*param_2);
    *param_1 = uVar1;
    return 0;
}

/* FUN_00492920 @ 0x00492920  (est. sk_r30_metadata_emit)
 * Ghidra: void FUN_00492920(long param_1,undefined8 param_2,code *param_3,undefined8 param_4,undefined8 param_5,undefined8 param_6)
 * Emits/records metadata through an indirect callback: computes a span
 * (extraout_x9 - extraout_x8_00), stores param_6 into param_1+0x18, invokes param_3
 * with the produced value and span, and conditionally finalizes param_1.
 * Confidence: low   Notes: multiple extraout register carry-overs and a direct call to
 * the raw address 0x54ffff60f100041f (decompiler artifact for a PAC/relocated pointer). */
static word_t sk_r30_00492920(long param_1, word_t param_2, code *param_3,
                              word_t param_4, word_t param_5, word_t param_6,
                              long extraout_x8_00 /* register carry-over */,
                              long extraout_x8_01 /* register carry-over */,
                              long extraout_x9 /* register carry-over */,
                              long extraout_x16 /* register carry-over */,
                              code *extraout_x8_02 /* register carry-over */,
                              long unaff_x21 /* register-global */)
{
    word_t uVar1;
    long extraout_x8;
    unsigned char auStack_70[32];

    extraout_x8 = FUN_0007c028();
    (*(code *)(uintptr_t)0x54ffff60f100041f)(*(word_t *)(extraout_x8 + 0x40));
    uVar1 = FUN_000aa4ec();
    FUN_00319808(uVar1, auStack_70);
    FUN_00351f34();
    FUN_00365b6c(extraout_x9 - extraout_x8_00, auStack_70, extraout_x8_01 + 8, param_5, 7);
    *(word_t *)(param_1 + 0x18) = param_6;
    uVar1 = FUN_00077024(param_1);
    (*param_3)(uVar1, extraout_x9 - extraout_x8_00);
    FUN_003508b4(*(word_t *)(extraout_x16 + 8));
    (*extraout_x8_02)();
    if (unaff_x21 != 0) {
        FUN_004a34b4(param_1);
    }
    return 0;
}

/* FUN_004934a8 @ 0x004934a8  (est. sk_r30_type_value_walk)
 * Ghidra: ulong FUN_004934a8(undefined8 param_1,ulong param_2)
 * Recursive dynamic-type / value-layout walker: decodes a type tag from param_2
 * (bits 61.. & 2), then either iterates element/field descriptors comparing identities,
 * recurses into nested values, or checks tagged-value bit patterns, returning a
 * classification (0/1/2). Traps on bounds violations / missing table entries.
 * Confidence: low   Notes: several recursive calls drop args in the decompile (modeled
 * here by re-passing the current register state); extraout/unaff register carry-overs
 * are trailing params; SoftwareBreakpoint sites rendered as CL4_SWBP. */
static word_t sk_r30_004934a8(word_t param_1, ulong param_2,
                              ulong extraout_x1 /* register carry-over */,
                              long extraout_x1_00 /* register carry-over */,
                              ulong extraout_x8 /* register carry-over */,
                              long extraout_x9 /* register carry-over */,
                              ulong unaff_x21 /* register-global */,
                              ulong unaff_x22 /* register-global */)
{
    code *pcVar1;
    int iVar2;
    uint uVar3;
    word_t *puVar4;
    char *pcVar5;
    ulong uVar6;
    ulong uVar7;
    ulong uVar8;
    long lVar9;
    ulong uVar10;
    word_t local_170;
    word_t local_168;
    word_t uStack_160;
    word_t local_158;
    word_t uStack_150;
    word_t local_148;
    word_t uStack_140;
    word_t local_138;
    word_t uStack_130;
    word_t local_128;
    unsigned char local_120;
    word_t local_c0;
    word_t uStack_b8;
    word_t uStack_b0;
    word_t uStack_a8;
    word_t local_a0;
    word_t uStack_98;
    word_t uStack_90;
    word_t uStack_88;
    char local_70;

code_r0x004934ac:
    uVar8 = 0;
    switch((uint)(param_2 >> 0x3b) & 0x1e | (uint)param_2 >> 2 & 1) {
    default:
        FUN_004ac15c();
        lVar9 = *(long *)(extraout_x1_00 + 0x10);
        uVar10 = *(ulong *)(lVar9 + 0x10);
        FUN_0036b270(lVar9);
        uVar8 = 0;
        goto LAB_004936d4;
    case 1:
        lVar9 = *(long *)((param_2 & 0xffffffffffffffb) + 0x10);
        uVar6 = *(ulong *)(lVar9 + 0x10);
        FUN_0036b270(lVar9);
        uVar10 = 0;
        do {
            if (uVar6 == uVar10) {
                FUN_0036b118(lVar9);
                return 0;
            }
            if (*(ulong *)(lVar9 + 0x10) <= uVar10) {
                CL4_SWBP(0x493878);
            }
            uVar7 = *(ulong *)(lVar9 + uVar10 * 8 + 0x20);
            FUN_0036b270(uVar7 & 0xffffffffffffffb);
            FUN_00350af4();
            uVar3 = sk_r30_004934a8(param_1, param_2, extraout_x1, extraout_x1_00,
                                    extraout_x8, extraout_x9, unaff_x21, unaff_x22);
            uVar8 = (ulong)(uVar3 & 0xff);
            FUN_0036b118(uVar7 & 0xffffffffffffffb);
            uVar10 = uVar10 + 1;
        } while ((uVar3 & 0xff) == 2);
        goto LAB_00493720;
    case 2:
        FUN_004775d0();
        break;
    case 3:
        FUN_00117cc4(&local_c0, (param_2 & 0xffffffffffffffb) + 0x10, 0x51);
        local_170 = 5;
        uStack_160 = 0;
        local_168 = 0;
        uStack_150 = 0;
        local_158 = 0;
        uStack_140 = 0;
        local_148 = 0;
        uStack_130 = 0;
        local_138 = 0;
        local_128 = 0;
        local_120 = 3;
        uVar8 = FUN_0041a0dc(&local_c0, &local_170);
        if ((uVar8 & 1) != 0) {
            return 2;
        }
        FUN_004775d0();
        if (local_70 == '\x02') {
            FUN_004766ec(&local_c0);
        }
        break;
    case 4:
    case 0xc:
        FUN_004ac114();
        uVar8 = *(ulong *)((extraout_x1 & unaff_x21) + 0x10);
        FUN_0036b270(uVar8 & unaff_x21);
        FUN_0007c1c4();
        uVar3 = sk_r30_004934a8(param_1, param_2, extraout_x1, extraout_x1_00,
                                extraout_x8, extraout_x9, unaff_x21, unaff_x22);
        FUN_0036b118(uVar8 & unaff_x21);
        return (ulong)(uVar3 & 0xff);
    case 5:
        uVar8 = sk_r30_004934a8(param_1, *(word_t *)((param_2 & 0xffffffffffffffb) + 0x90),
                                extraout_x1, extraout_x1_00, extraout_x8, extraout_x9,
                                unaff_x21, unaff_x22);
        if ((uVar8 & 0xfd) == 0) {
            return 0;
        }
        FUN_0007c1c4();
        uVar3 = sk_r30_004934a8(param_1, param_2, extraout_x1, extraout_x1_00,
                                extraout_x8, extraout_x9, unaff_x21, unaff_x22);
        return (ulong)(uVar3 & 0xfd);
    case 6:
        uVar7 = param_2 & 0xffffffffffffffb;
        lVar9 = *(long *)(uVar7 + 0x10);
        uVar10 = *(ulong *)(uVar7 + 0x18);
        uVar6 = *(ulong *)(uVar7 + 0x38);
        param_2 = *(ulong *)(uVar7 + 0x58);
        uVar8 = uVar6 >> 0x3d;
        switch(uVar8) {
        default:
            if ((uVar10 & 0xff) == 1 || lVar9 < 1) {
                return 2;
            }
            break;
        case 2:
            goto switchD_004934fc_caseD_7;
        case 4:
            goto switchD_00493764_caseD_4;
        }
        goto code_r0x004934ac;
    case 7:
    case 10:
    case 0xb:
    case 0xd:
    case 0xe:
    case 0xf:
        goto switchD_004934fc_caseD_7;
    case 8:
        FUN_00117cc4(&local_170, (param_2 & 0xffffffffffffffb) + 0x10, 0xb0);
        iVar2 = FUN_0049e2d4((param_2 & 0xffffffffffffffb) + 0x10);
        if (iVar2 != 3) {
            if (iVar2 != 6) {
                return 0;
            }
            puVar4 = (word_t *)FUN_0049e2f0(&local_170);
            uStack_b8 = puVar4[1];
            local_c0 = *puVar4;
            uStack_a8 = puVar4[3];
            uStack_b0 = puVar4[2];
            uStack_98 = puVar4[5];
            local_a0 = puVar4[4];
            uStack_88 = puVar4[7];
            uStack_90 = puVar4[6];
            FUN_004766ec(&local_c0);
            return 2;
        }
        pcVar5 = (char *)FUN_0049e2f0(&local_170);
        if (*pcVar5 != '\t') {
            return (ulong)(*pcVar5 == '\0');
        }
        FUN_004abacc();
        if (extraout_x9 == 0) {
            CL4_SWBP(0x493880);
        }
        FUN_004ab55c();
        return (ulong)((extraout_x8 & 4) == 0);
    case 9:
    case 0x10:
        return 2;
    }
    FUN_0007c1c4();
    uVar3 = sk_r30_004934a8(param_1, param_2, extraout_x1, extraout_x1_00,
                            extraout_x8, extraout_x9, unaff_x21, unaff_x22);
    FUN_0048525c();
    return (ulong)(uVar3 & 0xff);

switchD_00493764_caseD_4:
    if (uVar6 == 0x8000000000000000 &&
        (((uVar10 == 0 && lVar9 == 0) &&
         (*(long *)(uVar7 + 0x48) == 0 && *(long *)(uVar7 + 0x40) == 0)) &&
        ((*(long *)(uVar7 + 0x30) == 0 && *(long *)(uVar7 + 0x28) == 0) &&
        *(long *)(uVar7 + 0x20) == 0))) {
        return 2;
    }
    if (uVar6 != 0x8000000000000000 || lVar9 != 1) {
        return 2;
    }
    if (((*(long *)(uVar7 + 0x48) != 0 || uVar10 != 0) ||
        (*(long *)(uVar7 + 0x40) != 0 || *(long *)(uVar7 + 0x30) != 0)) ||
        (*(long *)(uVar7 + 0x28) != 0 || *(long *)(uVar7 + 0x20) != 0)) {
        return 2;
    }
    goto code_r0x004934ac;
    while (true) {
        if (*(ulong *)(lVar9 + 0x10) <= uVar6) {
            CL4_SWBP(0x49387c);
        }
        uVar8 = *(ulong *)(lVar9 + uVar6 * 8 + 0x20);
        FUN_0036b270(uVar8 & unaff_x22);
        FUN_0007c1c4();
        uVar3 = sk_r30_004934a8(param_1, param_2, extraout_x1, extraout_x1_00,
                                extraout_x8, extraout_x9, unaff_x21, unaff_x22);
        FUN_0036b118(uVar8 & unaff_x22);
        uVar8 = uVar6 + 1;
        if ((uVar3 & 1) == 0) break;
LAB_004936d4:
        uVar6 = uVar8;
        if (uVar10 == uVar6) break;
    }
    uVar8 = (ulong)(uVar10 == uVar6);
LAB_00493720:
    FUN_0036b118(lVar9);
switchD_004934fc_caseD_7:
    return uVar8;
}

/* FUN_00494790 @ 0x00494790  (est. sk_r30_hash_mixin)
 * Ghidra: void FUN_00494790(void)
 * Thin wrapper delegating to the sibling state-update helper.
 * Confidence: low */
static word_t sk_r30_00494790(void)
{
    FUN_00494810(0, 0, 0, 0, 0, 0, 0, 0, 0);
    return 0;
}

/* FUN_0049490c @ 0x0049490c  (est. sk_r30_range_union)
 * Ghidra: void FUN_0049490c(void)
 * Compares two range values (16-byte halves) by magnitude of their top fields; if the
 * lo half is not greater than the hi half, merges the stack-passed arguments into the
 * output buffer (extraout_x8) via the callback; otherwise traps fail-closed.
 * Confidence: low   Notes: 16-byte return from FUN_004acb3c (hi half not exposed by the
 * word_t extern); multiple stack-passed args; indirect callback in_x6. */
static word_t sk_r30_0049490c(code *in_x6 /* register-global */,
                              word_t *extraout_x8 /* register carry-over */,
                              long unaff_x21 /* register-global */,
                              word_t unaff_x30 /* register-global */,
                              word_t in_stack_00000090, word_t in_stack_00000098,
                              word_t in_stack_000000a0, word_t in_stack_000000a8,
                              word_t in_stack_000000b0)
{
    wpair_t auVar2;

    /* 16-byte (x0:x1) return of FUN_004acb3c; only lo (x0) is exposed by the word_t
       extern, so the hi half (x1) is modeled here as a carried local. */
    auVar2.lo = FUN_004acb3c();
    auVar2.hi = /* x1 half of the 16-byte return */ 0;
    if (auVar2.lo >> 0xe <= auVar2.hi >> 0xe) {
        FUN_00469918();
        FUN_004abb1c(&in_stack_00000090);
        (*in_x6)();
        FUN_004974c4();
        if (unaff_x21 == 0) {
            extraout_x8[1] = in_stack_00000098;
            *extraout_x8 = in_stack_00000090;
            extraout_x8[3] = in_stack_000000a8;
            extraout_x8[2] = in_stack_000000a0;
            extraout_x8[4] = in_stack_000000b0;
        }
        FUN_004acb20(unaff_x30);
        return 0;
    }
    CL4_SWBP(0x4949c4);
    return 0;   /* unreachable after trap */
}

/* FUN_00494ea8 @ 0x00494ea8  (est. sk_r30_box_retain_tag)
 * Ghidra: void FUN_00494ea8(undefined1 param_1,code *param_2)
 * Runs the retain-side helper, invokes the callback with a small tag value, then runs
 * the release-side cleanup.
 * Confidence: low */
static word_t sk_r30_00494ea8(unsigned char param_1, code *param_2)
{
    FUN_004080b0();
    (*param_2)(param_1);
    FUN_001a8564();
    return 0;
}

/* FUN_00495400 @ 0x00495400  (est. sk_r30_context_emit_init)
 * Ghidra: void FUN_00495400(void)
 * Builds a small byte value, allocates a fresh object, invokes the register-global
 * callback with a one-byte buffer, then initializes the object's 0x10 field and tags it.
 * Confidence: low   Notes: unaff_x19 callback register-global. */
static word_t sk_r30_00495400(code *unaff_x19 /* unaff_x19: callback register-global */)
{
    unsigned char uVar1;
    ulong uVar2;
    unsigned char local_e0[176];

    uVar1 = FUN_00350a28();
    FUN_004aa7bc();
    uVar2 = FUN_0036a940();
    local_e0[0] = uVar1;
    (*unaff_x19)(local_e0);
    FUN_004ac61c(uVar2 + 0x10);
    FUN_0049153c();
    return 0;
}

/* FUN_00495810 @ 0x00495810  (est. sk_r30_vtable_setup)
 * Ghidra: void FUN_00495810(void)
 * Allocates a fresh object, fills a 0x38-0x60 table block with register-carried pointer
 * pairs and a tag byte, runs init/teardown helpers, then stores a 16-byte hash into the
 * context at unaff_x24+0x68 and tags the pointer.
 * Confidence: low   Notes: 16-byte return from FUN_0035199c (only the lo half is used);
 * multiple extraout register carry-overs. */
static word_t sk_r30_00495810(code *extraout_x8 /* register carry-over */,
                              ulong unaff_x24 /* register-global */,
                              word_t extraout_d0 /* register carry-over */,
                              word_t extraout_var /* register carry-over */)
{
    long lVar1;
    wpair_t auVar2;

    /* 16-byte (x0:x1) return of FUN_0035199c; lo from x0, hi (x1) not exposed. */
    auVar2.lo = FUN_0035199c();
    auVar2.hi = /* x1 half of the 16-byte return */ 0;
    FUN_004ab8c8();
    FUN_0036a940();
    lVar1 = FUN_004ac324();
    *(word_t *)(lVar1 + 0x40) = extraout_var;
    *(word_t *)(lVar1 + 0x38) = extraout_d0;
    *(word_t *)(lVar1 + 0x50) = extraout_var;
    *(word_t *)(lVar1 + 0x48) = extraout_d0;
    *(word_t *)(lVar1 + 0x58) = 0;
    *(unsigned char *)(lVar1 + 0x60) = 3;
    FUN_004ab5d4();
    FUN_00100efc();
    (*extraout_x8)();
    FUN_00491644(unaff_x24);
    FUN_00351d18();
    FUN_0036b118();
    *(long *)(unaff_x24 + 0x68) = auVar2.lo;
    FUN_0049153c();
    return 0;
}

/* FUN_00495c48 @ 0x00495c48  (est. sk_r30_closure_call)
 * Ghidra: undefined8 FUN_00495c48(long param_1,code *param_2)
 * Through the callback param_2, resolves a function pointer from param_1+0x20 and
 * invokes it with (out-slot, param_1+0x10, that value), returning the out-slot.
 * Confidence: low */
static word_t sk_r30_00495c48(long param_1, code *param_2)
{
    code *pcVar1;
    word_t uVar2;
    word_t local_38;

    uVar2 = *(word_t *)(param_1 + 0x20);
    pcVar1 = (code *)(*param_2)(uVar2);
    (*pcVar1)(&local_38, *(word_t *)(param_1 + 0x10), uVar2);
    return local_38;
}
/* Part 6 of cL4 true-gap slice SKR30 (Swift runtime fragments).
 * English-first faithful transcriptions. */

/* FUN_00490ae0 @ 0x00490ae0  (est. sk_r30_deinit_self)
 * Ghidra: void FUN_00490ae0(void)
 * Calls the teardown thunk (0x36b270) for the object at self+0x40, then the 0x9461c helper.
 * Confidence: low   Notes: unaff_x20 = self register-global (word pointer); thunk callee 0x36b270. */
static word_t sk_r30_00490ae0(word_t *unaff_x20 /* unaff_x20: self/context */)
{
    FUN_0036b270(unaff_x20[8]);
    FUN_0009461c();
    return 0;
}

/* FUN_00490cb8 @ 0x00490cb8  (est. sk_r30_box_closure)
 * Ghidra: undefined1 [16] FUN_00490cb8(undefined8 *param_1,undefined8 *param_2)
 * Allocates a 0x68-byte closure box, stores it into *param_1, initializes it via
 * 0x490b14 with *param_2 and the self context, and returns the 16-byte closure pair
 * (function thunk 0x490d28, box).
 * Confidence: low   Notes: 16-byte pair return; per word_t contract we return the
 * function-thunk half, the box is retained in *param_1. x1 half of the pair is implicit. */
static word_t sk_r30_00490cb8(word_t *param_1, word_t *param_2, word_t *unaff_x20 /* unaff_x20: self */)
{
    word_t box;

    box = FUN_0036a908(0x68, 0xebae);
    *param_1 = box;
    sk_r30_00490b14(box, *param_2, unaff_x20[0], unaff_x20[1], unaff_x20[2],
                    0 /* unaff_x19 */, (word_t)unaff_x20 /* unaff_x20 */);
    return (word_t)sk_r30_00490d28;
}

/* FUN_00490fe0 @ 0x00490fe0  (est. sk_r30_grow_collection)
 * Ghidra: void FUN_00490fe0(undefined8 param_1)
 * Iterates a collection described by the count at (self[2]+0x10), rebuilding each
 * element buffer (0x58-stride slots) into a 0x68-byte box; when the rebuilt box's tag
 * words match (x22,x21) it is copied out to param_1 and released; otherwise it is
 * released and the slot advance continues. Falls to the 0x4ac228 failure path if the
 * collection is empty.
 * Confidence: low   Notes: unaff_x20 self, unaff_x21/x22 tag register-globals;
 * local_e8/local_e0 are the box tag words; extraout_x8 from a prior call. */
static word_t sk_r30_00490fe0(word_t param_1, word_t *unaff_x20 /* unaff_x20: self */,
                              word_t unaff_x21 /* unaff_x21 */, word_t unaff_x22 /* unaff_x22 */)
{
    word_t uVar1, uVar2, uVar3;
    long extraout_x8;          /* carried from a prior call */
    long lVar4, lVar5;
    char auStack_b8[0x58];     /* 88-byte scratch buffer */
    char auStack_120[0x68];    /* 104-byte box buffer */
    word_t local_e0, local_e8; /* box tag words */

    lVar5 = *(long *)((char *)unaff_x20[2] + 0x10);
    if (lVar5 != 0) {
        FUN_003509ec();
        uVar1 = unaff_x20[0];
        uVar2 = unaff_x20[1];
        lVar4 = extraout_x8 + 0x20;
        do {
            FUN_0049c704(lVar4, auStack_b8);
            FUN_00117cc4(auStack_120, auStack_b8, 0x68);
            if (local_e0 != 0) {
                if (local_e8 == unaff_x22 && local_e0 == unaff_x21) {
                    goto copy_out;
                }
                FUN_00351b78();
                uVar3 = FUN_002a0cf8();
                if ((uVar3 & 1) != 0) {
                    goto copy_out;
                }
            }
            FUN_0036b270(uVar2);
            FUN_0049c714(auStack_120);
            lVar4 = lVar4 + 0x58;
            lVar5 = lVar5 - 1;
        } while (lVar5 != 0);
    }
    FUN_004ac228();
    return 0;

copy_out:
    FUN_00117cc4(param_1, auStack_120, 0x68);
    FUN_0036b270(uVar2);
    return 0;
}

/* FUN_00491644 @ 0x00491644  (est. sk_r30_get_field_18)
 * Ghidra: undefined8 FUN_00491644(long param_1)
 * Reads the word at param_1+0x18, runs the 0x4acccc helper, and returns that word.
 * Confidence: medium   Notes: trivial field load + helper. */
static word_t sk_r30_00491644(word_t param_1)
{
    word_t uVar1;

    uVar1 = *(word_t *)(param_1 + 0x18);
    FUN_004acccc();
    return uVar1;
}

/* FUN_004918ec @ 0x004918ec  (est. sk_r30_finalize_slot)
 * Ghidra: void FUN_004918ec(void)
 * Finalizes the slot at self+0x10 via 0x4974c4, then runs the 0x4ac8fc and 0x36b6ac helpers.
 * Confidence: low   Notes: unaff_x20 = self register-global. */
static word_t sk_r30_004918ec(word_t *unaff_x20 /* unaff_x20: self */)
{
    FUN_004974c4(unaff_x20 + 2);
    FUN_004ac8fc();
    FUN_0036b6ac();
    return 0;
}

/* FUN_00491bb8 @ 0x00491bb8  (est. sk_r30_teardown_inner)
 * Ghidra: void FUN_00491bb8(void)
 * Runs the in-slice 0x491b88 teardown, the 0xdce50 helper, then the 0x36b6ac helper.
 * Confidence: low   Notes: chain of teardown helpers. */
static word_t sk_r30_00491bb8(void)
{
    sk_r30_00491b88(0 /* unaff_x20: not carried in this frame */);
    FUN_000dce50();
    FUN_0036b6ac();
    return 0;
}

/* FUN_0049214c @ 0x0049214c  (est. sk_r30_alloc_fatal)
 * Ghidra: void FUN_0049214c(void)
 * Allocates 0x130 via 0x350d94, runs 0x4aac40, then calls the noreturn 0x1afa84.
 * Confidence: low   Notes: FUN_001afa84 does not return; trailing return 0 is dead. */
static word_t sk_r30_0049214c(void)
{
    FUN_00350d94(0x130);
    FUN_004aac40();
    FUN_001afa84(); /* noreturn */
    return 0;
}

/* FUN_00492a2c @ 0x00492a2c  (est. sk_r30_dispatch_switch)
 * Ghidra: void FUN_00492a2c(void)
 * Dispatches through a sequence of lookup/compare helpers; depending on the 6-way
 * comparison result selects one of the error-class descriptors (DAT_00687c08 /
 * DAT_00687c58) to log via 0x355538/0x36a940, then finishes through 0x4ac240 and 0x354ef8.
 * Confidence: low   Notes: in_x3 passed through to 0x310d68; unaff_x30 to 0x354ef8;
 * auVar5 16-byte returns: x1 halves unavailable via word_t extern (modeled as 0). */
static word_t sk_r30_00492a2c(word_t in_x3, word_t unaff_x30)
{
    int iVar1;
    word_t uVar2, uVar3;
    word_t *puVar4;
    word_t auVar5_lo, auVar5_hi;

    FUN_00354a34();
    FUN_00349a18();
    uVar2 = FUN_00310d68(0xff, in_x3);
    FUN_004ac824();
    uVar3 = FUN_00370538();
    FUN_004abdb8();
    auVar5_lo = FUN_004ac824();
    auVar5_hi = 0; /* x1 half of 16-byte return not exposed by word_t extern */
    uVar2 = FUN_00370538(auVar5_lo, auVar5_hi, uVar2);
    FUN_0036b270();
    auVar5_lo = FUN_004ab304();
    auVar5_hi = 0; /* x1 half of 16-byte return not exposed by word_t extern */
    iVar1 = FUN_00365b6c(auVar5_lo, auVar5_hi, uVar3, uVar2, 6);
    if (iVar1 == 0) {
        puVar4 = &DAT_00687c08;
    } else {
        FUN_0036b118();
        FUN_00355538(&DAT_00687c30);
        FUN_0036a940();
        FUN_004ac9e4();
        puVar4 = &DAT_00687c58;
    }
    FUN_00355538(puVar4);
    FUN_0036a940();
    FUN_004ac240();
    FUN_00354ef8(unaff_x30);
    return 0;
}

/* FUN_00493d30 @ 0x00493d30  (est. sk_r30_fill_trap_record)
 * Ghidra: void FUN_00493d30(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)
 * Runs the 0x3504d0/0x41cb78/0x351790/0x352c68 prep helpers, builds a trap/record via
 * 0x1a1c8, and writes its 12-byte payload plus param_3/param_4 and the unaff_x19
 * context into the caller buffer (extraout_x8), leaving slot [4] unset.
 * Confidence: low   Notes: extraout_x8 = caller buffer from a prior call; unaff_x19
 * register-global; auVar1 12-byte return — x1 half not exposed by word_t extern
 * (modeled as 0). */
static word_t sk_r30_00493d30(word_t param_1, word_t param_2, word_t param_3, word_t param_4,
                              word_t unaff_x19 /* unaff_x19 */)
{
    word_t *extraout_x8; /* caller buffer, carried from a prior call */
    word_t lo, hi32;

    FUN_003504d0();
    FUN_0041cb78();
    FUN_00351790();
    FUN_00352c68();
    lo = FUN_0001a1c8();      /* x0 half of 12-byte return */
    hi32 = 0;                 /* x1 half not exposed by word_t extern */
    extraout_x8[0] = lo;
    extraout_x8[1] = (word_t)(hi32 & 1);
    extraout_x8[2] = param_3;
    extraout_x8[3] = param_4;
    extraout_x8[5] = unaff_x19;
    return 0;
}

/* FUN_004947b8 @ 0x004947b8  (est. sk_r30_thunk_4910)
 * Ghidra: void FUN_004947b8(void)
 * Thin forwarder to the in-slice 0x494810 body.
 * Confidence: medium   Notes: single in-slice call. */
static word_t sk_r30_004947b8(void)
{
    sk_r30_00494810(0 /* in_x4 */, 0 /* extraout_x8 */, 0 /* unaff_x21 */,
                    0 /* unaff_x30 */, 0 /* in_98 */, 0 /* in_a0 */, 0 /* in_a8 */,
                    0 /* in_b0 */, 0 /* in_b8 */);
    return 0;
}

/* FUN_00494a1c @ 0x00494a1c  (est. sk_r30_dispatch_closure)
 * Ghidra: void FUN_00494a1c(undefined8,undefined8,undefined8,undefined8,undefined8,undefined8,code *)
 * Runs 0x35638c, invokes a carried code pointer (extraout_x8_00) on (param_3,param_5),
 * stages a stack frame through 0x270c08 / 0x4aa95c / 0x377824 / 0x351dfc, invokes the
 * param_7 closure, then packages the resulting stack words into the caller buffer
 * (extraout_x8[0..4]) and runs 0x356370.
 * Confidence: low   Notes: in_stack_00000028..0x68 modeled as stack-slot locals;
 * extraout_x8_00 / extraout_x1 / unaff_x30 carried from prior calls. */
static word_t sk_r30_00494a1c(word_t param_1, word_t param_2, word_t param_3, word_t param_4,
                              word_t param_5, word_t param_6, code *param_7,
                              word_t *extraout_x8 /* caller buffer */, word_t unaff_x30)
{
    word_t uVar1, uVar2, uVar3, uVar4, uVar5, uVar6, uVar7;
    word_t extraout_x1;          /* carried from a prior call */
    code *extraout_x8_00;        /* carried code pointer from a prior call */
    word_t in28, in40, in48, in50, in58, in60, in68; /* stack slots */

    FUN_0035638c();
    FUN_004ab5d4(param_5);
    uVar6 = (*extraout_x8_00)(param_3, param_5);
    FUN_00356bb0(param_4);
    FUN_00270c08(&in28, param_6, 0, extraout_x1);
    uVar2 = in40;
    uVar1 = in28;
    uVar7 = FUN_004aa95c();
    FUN_00377824(uVar7, param_5, param_3);
    FUN_00351dfc(&in48, uVar1);
    (*param_7)();
    uVar5 = in68;
    uVar4 = in60;
    uVar3 = in58;
    uVar7 = in50;
    uVar1 = in48;
    FUN_0036b118(uVar6);
    FUN_003a25d4(uVar2);
    extraout_x8[1] = uVar7;
    extraout_x8[0] = uVar1;
    extraout_x8[3] = uVar4;
    extraout_x8[2] = uVar3;
    extraout_x8[4] = uVar5;
    FUN_00356370(unaff_x30);
    return 0;
}

/* FUN_00494ef0 @ 0x00494ef0  (est. sk_r30_call_handler)
 * Ghidra: void FUN_00494ef0(void)
 * Stashes *self (a word) into a 72-byte stack frame, invokes the in_x3 handler on
 * (frame, *self), then runs 0x1a8564.
 * Confidence: low   Notes: in_x3 = handler function pointer; unaff_x20 = self. */
static word_t sk_r30_00494ef0(code *in_x3, word_t *unaff_x20 /* unaff_x20: self */)
{
    word_t uVar1;
    char auStack_68[0x48]; /* 72-byte frame */

    uVar1 = *unaff_x20;
    FUN_001a84f4(auStack_68);
    (*in_x3)(auStack_68, uVar1);
    FUN_001a8564();
    return 0;
}

/* FUN_00495464 @ 0x00495464  (est. sk_r30_log_and_release)
 * Ghidra: void FUN_00495464(void)
 * Captures a value from 0x350a28, tags a context word with the 0x4000000000000000 bit,
 * feeds the value through 0x49ca44, then performs release/teardown helpers.
 * Confidence: low   Notes: local_e0 = captured value; thunk callee 0x36b270. */
static word_t sk_r30_00495464(void)
{
    word_t uVar1, uVar2;
    word_t local_e0;

    uVar1 = FUN_00350a28();
    FUN_004aa7bc();
    uVar2 = FUN_0036a940();
    local_e0 = uVar1;
    FUN_0049ca44(&local_e0);
    FUN_004ac61c(uVar2 + 0x10);
    FUN_0049153c();
    FUN_0035310c();
    FUN_0036b270();
    return 0;
}

/* FUN_004958a8 @ 0x004958a8  (est. sk_r30_publish_result)
 * Ghidra: void FUN_004958a8(void)
 * Gathers a value (0x350980) and context, writes the DAT_004baeb0 pair into a fresh
 * result object at lVar4 (+0x10/+0x18), stores a reference into lVar3+0x10, and
 * publishes through 0x491644 / 0x351d18 / 0x36b118.
 * Confidence: low   Notes: uRam_004baeb8 modeled as the word at &DAT_004baeb0+8;
 * in_x3 passed to 0x4ab5d4; extraout_x8 code pointer from a prior call. */
static word_t sk_r30_004958a8(word_t in_x3)
{
    word_t uVar1, uVar2;
    long lVar3, lVar4;
    code *extraout_x8; /* carried code pointer from a prior call */

    uVar2 = FUN_00350980();
    FUN_004aa83c();
    lVar3 = FUN_0036a940();
    FUN_004aa6c4();
    FUN_00002534();
    FUN_00359018();
    lVar4 = FUN_0036a940();
    uVar1 = DAT_004baeb0;
    *(word_t *)(lVar4 + 0x18) = *(word_t *)((char *)&DAT_004baeb0 + 8);
    *(word_t *)(lVar4 + 0x10) = uVar1;
    FUN_004ab5d4(in_x3);
    FUN_00084180();
    (*extraout_x8)();
    sk_r30_00491644(0 /* param_1: not carried in this frame */);
    FUN_00351d18();
    FUN_0036b118();
    *(word_t *)(lVar4 + 0x20) = uVar2;
    *(long *)(lVar3 + 0x10) = lVar4;
    FUN_003504c4();
    FUN_0049153c();
    return 0;
}

/* FUN_00495ca4 @ 0x00495ca4  (est. sk_r30_string_op)
 * Ghidra: void FUN_00495ca4(undefined8 param_1,undefined8 param_2,long param_3,undefined8 param_4)
 * Case-folded string/lower-upper compare-and-transform: reads the object method table
 * (param_3-8), builds frames through the PAC'd 0x54ffff60f100041f helper, sets up
 * lower/upper transforms (s_lower_upper_005e1f90, DAT_0060e208/DAT_0060e230,
 * LAB_0060e218), resolves function descriptors, and if the low-bit test succeeds runs
 * the assembled sequence of string transforms into param_1; otherwise traps at 0x496138.
 * Confidence: low   Notes: SUB_54ffff60f100041f modeled as an indirect call through
 * the literal PAC'd code address; dynamic frame sizing via extraout_* register
 * carry; LAB_0060e218 passed as the literal 0x0060e218 label address. */
static word_t sk_r30_00495ca4(word_t param_1, word_t param_2, word_t param_3, word_t param_4,
                              word_t unaff_x20 /* unaff_x20 */)
{
    long lVar1, lVar4, lVar5, lVar9, lVar10, lVar11, lVar13;
    word_t uVar3, uVar6, uVar8;
    long extraout_x8, extraout_x8_00, extraout_x8_01, extraout_x8_02;
    long extraout_x12, extraout_x12_00;
    code *pcVar7, *pcVar12;
    char auStack_d0[8];
    long local_c8, local_b8, local_b0, local_a8, local_a0, local_98, local_90;
    word_t local_c0;
    word_t *local_88;

    local_90 = *(long *)(param_3 - 8);
    ((code)0x54ffff60f100041f)(*(word_t *)(local_90 + 0x40));
    local_88 = (word_t *)(auStack_d0 + -(extraout_x8 + 0xfU & ~0xfU));
    uVar3 = FUN_00027754(param_4);
    lVar4 = FUN_00377824(0xff, uVar3, param_3, &DAT_0060e208, &DAT_0060e230);
    lVar5 = FUN_003722e4(0, lVar4, lVar4, s_lower_upper_005e1f90, 0);
    local_98 = *(long *)(lVar5 - 8);
    ((code)0x54ffff60f100041f)(*(word_t *)(local_98 + 0x40));
    lVar10 = (long)(auStack_d0 + -(extraout_x8 + 0xfU & ~0xfU)) -
             (extraout_x8_00 + 0xfU & ~0xfU);
    ((code)0x54ffff60f100041f)();
    lVar9 = lVar10 - extraout_x12;
    local_a0 = *(long *)(lVar4 - 8);
    ((code)0x54ffff60f100041f)(*(word_t *)(local_a0 + 0x40));
    lVar11 = lVar9 - (extraout_x8_01 + 0xfU & ~0xfU);
    ((code)0x54ffff60f100041f)();
    lVar13 = lVar11 - extraout_x12_00;
    uVar6 = FUN_00377bec(uVar3, param_3, lVar4, &DAT_0060e208, (word_t)0x0060e218);
    local_a8 = FUN_00310e08(0, lVar4, uVar6);
    local_b0 = *(long *)(local_a8 - 8);
    ((code)0x54ffff60f100041f)((*(long *)(local_b0 + 0x40) + 0xfU) & ~0xfU);
    local_b8 = lVar13 - extraout_x8_02;
    pcVar7 = (code *)FUN_000277b8(uVar3);
    (*pcVar7)(lVar13, param_3, uVar3);
    pcVar7 = (code *)FUN_00310924(uVar3);
    (*pcVar7)(lVar11, param_3, uVar3);
    pcVar7 = (code *)FUN_00310e20(uVar6);
    uVar8 = (*pcVar7)(lVar13, lVar11, lVar4, uVar6);
    lVar1 = local_a0;
    if ((uVar8 & 1) != 0) {
        pcVar12 = *(code **)(local_a0 + 0x20);
        local_c0 = uVar3;
        (*pcVar12)(lVar9, lVar13, lVar4);
        (*pcVar12)(lVar9 + *(int *)(lVar5 + 0x30), lVar11, lVar4);
        lVar13 = local_98;
        (**(code **)(local_98 + 0x10))(lVar10, lVar9, lVar5);
        lVar11 = local_b8;
        local_c8 = (long)*(int *)(lVar5 + 0x30);
        (*pcVar12)(local_b8, lVar10, lVar4);
        pcVar7 = *(code **)(lVar1 + 8);
        (*pcVar7)(lVar10 + local_c8, lVar4);
        (**(code **)(lVar13 + 0x20))(lVar10, lVar9, lVar5);
        lVar9 = local_a8;
        (*pcVar12)(lVar11 + *(int *)(local_a8 + 0x24), lVar10 + *(int *)(lVar5 + 0x30), lVar4);
        (*pcVar7)(lVar10, lVar4);
        uVar3 = local_c0;
        pcVar7 = (code *)FUN_0031b050(local_c0);
        (*pcVar7)(param_2, lVar11, param_3, uVar3);
        lVar1 = local_b0;
        (**(code **)(local_b0 + 8))(lVar11, lVar9);
        (**(code **)(local_90 + 0x10))(local_88, unaff_x20, param_3);
        (**(code **)(lVar1 + 0x10))(lVar11, param_2, lVar9);
        FUN_001d3fd0(param_1, local_88, lVar11, param_3, uVar3);
        return 0;
    }
    CL4_SWBP(0x496138);
    return 0;
}
/* ===================================================================== *
 * SKR30 chunk 7 transcriptions (Swift runtime fragments 0x490b0c-0x4961a0)
 * 15 functions. Prelude (concatenated before this part) provides all
 * externs / in-slice forward decls / macros. English-first bodies.
 * ===================================================================== */

/* FUN_00490b0c @ 0x00490b0c  (est. sk_r30_metadata_load)
 * Ghidra: undefined8 FUN_00490b0c(undefined8 param_1,undefined8 param_2,long param_3)
 * Loads and returns the metadata/type pointer stored at offset 0x10 of the
 * box in `value`. param_1/param_2 are unused (likely self/refcount).
 * Confidence: medium */
static word_t sk_r30_00490b0c(word_t self, word_t param_2, long value)
{
    return *(word_t *)(value + 0x10);
}

/* FUN_00490d28 @ 0x00490d28  (est. sk_r30_obj_release)
 * Ghidra: void FUN_00490d28(undefined8 *param_1)
 * Reads the first word of *obj, decrements its retain counter (FUN_0049c714)
 * then hands it to the free/teardown thunk (FUN_00012568). Classic Swift
 * object release sequence (refcount dec + dealloc).
 * Confidence: medium */
static word_t sk_r30_00490d28(word_t *obj)
{
    word_t uVar1;
    uVar1 = *obj;
    FUN_0049c714(uVar1);
    FUN_00012568(uVar1);
    return 0;
}

/* FUN_004910bc @ 0x004910bc  (est. sk_r30_dispatch_generic)
 * Ghidra: void FUN_004910bc(undefined8 param_1,undefined8 param_2,undefined8 param_3)
 * Runs a sequence of runtime/subscript setup calls, then when the context
 * register (unaff_x21) is zero allocates a box (FUN_0036a940) and dispatches
 * into FUN_003505c4 with the box halves, param_3 and a bit of unaff_w24.
 * Mostly a generic dispatch/boxing prologue.
 * Confidence: low   Notes: unaff_x21/unaff_w24 modeled as params; FUN_0036a940 returns x0:x1 pair. */
static word_t sk_r30_004910bc(word_t param_1, word_t param_2, word_t param_3,
                              long unaff_x21 /* unaff_x21: self/context register-global */,
                              uint unaff_w24 /* unaff_w24: self/context register-global */)
{
    word_t uVar1;
    word_t auVar2;   /* lo half of the 16-byte pair; hi not recoverable from word_t extern */
    uVar1 = FUN_00019850();
    FUN_000f5e08();
    FUN_004ab920();
    FUN_004ab618();
    FUN_00445e64();
    FUN_004630c4();
    FUN_003a25d4(param_2);
    if (unaff_x21 == 0) {
        FUN_004ac830();
        FUN_00002534();
        FUN_00359018();
        auVar2 = FUN_0036a940();
        /* hi word of the pair not independently recoverable from the word_t extern */
        FUN_003505c4(uVar1, 0, param_3, unaff_w24 & 1, auVar2);
        /* in-slice prototype demands 4 args; caller decompile shows none (register-passed,
           unobservable) — pass 0 placeholders */
        FUN_004919f0(0, 0, 0, 0);
    }
    return 0;
}

/* FUN_00491688 @ 0x00491688  (est. sk_r30_copy_or_retain)
 * Ghidra: undefined8 FUN_00491688(long param_1,undefined8 param_2,undefined8 param_3)
 * Touches a value/metadata (masked read of +0x18), releases param_1, then
 * allocates via FUN_0049153c and probes FUN_00491288. On failure (low bit of
 * the probe clear) the allocation is released and 0 returned.
 * Confidence: low */
static word_t sk_r30_00491688(long param_1, word_t param_2, word_t param_3)
{
    word_t uVar1;
    ulong uVar2;
    FUN_0036b270(*(ulong *)(param_1 + 0x18) & 0xffffffffffffffb);
    FUN_0036b118(param_1);
    FUN_000b43d0();
    uVar1 = FUN_0049153c();
    /* in-slice prototype sk_r30_00491288 takes a single arg (context register);
       decompile passes (uVar1, param_3) — param_3 dropped to match the 1-arg prototype */
    uVar2 = FUN_00491288(uVar1);
    if ((uVar2 & 1) == 0) {
        FUN_0036b118(uVar1);
        uVar1 = 0;
    }
    return uVar1;
}

/* FUN_004918f0 @ 0x004918f0  (est. sk_r30_deinit)
 * Ghidra: void FUN_004918f0(void)
 * Teardown helper: rebuilds/releases the object at context+0x10, then runs
 * two cleanup routines (FUN_004ac8fc, FUN_0036b6ac).
 * Confidence: low   Notes: unaff_x20 modeled as param. */
static word_t sk_r30_004918f0(long unaff_x20 /* unaff_x20: self/context register-global */)
{
    FUN_004974c4(unaff_x20 + 0x10);
    FUN_004ac8fc();
    FUN_0036b6ac();
    return 0;
}

/* FUN_00491bd4 @ 0x00491bd4  (est. sk_r30_cap_op_set)
 * Ghidra: undefined8 FUN_00491bd4(ulong param_1,char param_2)
 * Capability operation on the object pointed at by the context register.
 * When param_2 == 1 it builds a CapInvalid error box (string
 * s_L4_ErrorCodeCapInvalid_006886c8) and reports it; otherwise it ORs param_1
 * into the field at +0x20, clears +0x10 and releases the old field value.
 * Always returns 1.
 * Confidence: low   Notes: unaff_x20 modeled as param; unreachable block at 0x491c38 dropped. */
static word_t sk_r30_00491bd4(ulong param_1, char param_2,
                              long *unaff_x20 /* unaff_x20: self/context register-global */)
{
    word_t uVar1;
    word_t uVar2;
    long lVar3;
    unsigned char auStack_e8[40];
    unsigned char auStack_c0[144];
    lVar3 = *unaff_x20;
    if (param_2 == '\x01') {
        uVar2 = *(word_t *)(lVar3 + 0x18);
        uVar1 = *(word_t *)(lVar3 + 0x20);
        lVar3 = FUN_0036a9a0(0x657c78, auStack_e8);
        *(word_t *)(lVar3 + 0x10) = uVar2;
        *(char **)(lVar3 + 0x18) = s_L4_ErrorCodeCapInvalid_006886c8;
        *(word_t *)(lVar3 + 0x20) = uVar1;
        FUN_004acccc();
        FUN_0047d358(auStack_c0);
        FUN_004974c4(auStack_c0);
    }
    else {
        *(ulong *)(lVar3 + 0x20) = *(ulong *)(lVar3 + 0x20) | param_1;
        uVar2 = *(word_t *)(lVar3 + 0x10);
        *(word_t *)(lVar3 + 0x10) = 0;
        FUN_0036b118(uVar2);
    }
    return 1;
}

/* FUN_004921bc @ 0x004921bc  (est. sk_r30_string_is_known)
 * Ghidra: bool FUN_004921bc(long param_1)
 * Swift String representation dispatch: the top bits (param_1>>0x3b) select
 * the string kind. Most kinds return true (known/valid), several return
 * false, kind 0xb decodes a large bridged object and returns whether its
 * +0x10 field is nonzero, and the default inspects a nested pointer. The
 * `true`/`false` cases are the string-layout classification.
 * Confidence: low   Notes: extraout_x8 from FUN_004ac0c0 modeled via its return. */
static word_t sk_r30_004921bc(long param_1)
{
    long lVar1;
    long extraout_x8;
    long extraout_x8_00;
    long lVar2;
    unsigned char auStack_a0[32];
    word_t local_80;
    word_t uStack_78;
    word_t uStack_70;
    word_t uStack_68;
    word_t local_60;
    word_t uStack_58;
    word_t uStack_50;
    word_t uStack_48;
    word_t local_40;
    word_t uStack_38;
    word_t uStack_30;
    word_t uStack_28;
    switch (((uint)((ulong)param_1 >> 0x3b)) & 0x1e | ((uint)param_1 >> 2) & 1) {
    case 1:
        extraout_x8_00 = FUN_004ac0c0();   /* extraout x8 carried from call */
        param_1 = extraout_x8_00;
        break;
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 0xc:
        return 1;   /* true */
    case 7:
    case 8:
    case 9:
    case 10:
    case 0xd:
    case 0xe:
    case 0xf:
    case 0x10:
        return 0;   /* false */
    case 0xb:
        extraout_x8 = FUN_004ac0c0(0);   /* extraout x8 carried from call */
        uStack_78 = *(word_t *)(extraout_x8 + 0x18);
        local_80 = *(word_t *)(extraout_x8 + 0x10);
        uStack_68 = *(word_t *)(extraout_x8 + 0x28);
        uStack_70 = *(word_t *)(extraout_x8 + 0x20);
        uStack_58 = *(word_t *)(extraout_x8 + 0x38);
        local_60 = *(word_t *)(extraout_x8 + 0x30);
        uStack_48 = *(word_t *)(extraout_x8 + 0x48);
        uStack_50 = *(word_t *)(extraout_x8 + 0x40);
        uStack_38 = *(word_t *)(extraout_x8 + 0x28);
        local_40 = *(word_t *)(extraout_x8 + 0x20);
        uStack_28 = *(word_t *)(extraout_x8 + 0x38);
        uStack_30 = *(word_t *)(extraout_x8 + 0x30);
        FUN_00460e20(&local_40, auStack_a0);
        lVar1 = FUN_00412eec();
        FUN_00460e30(&local_80);
        lVar2 = *(long *)(lVar1 + 0x10);
        FUN_0036b118(lVar1);
        return lVar2 != 0;
    }
    return *(long *)(*(long *)(param_1 + 0x10) + 0x10) != 0;
}

/* FUN_00492b3c @ 0x00492b3c  (est. sk_r30_build_result)
 * Ghidra: void FUN_00492b3c(undefined8 *param_1,...)
 * Build-style routine: allocates a result area via FUN_00310d68, performs a
 * metadata-relative setup call, reserves stack for the payload, invokes the
 * caller-supplied callback (param_6) to fill it, then FUN_000839f8 parses it.
 * On success (return 1) the four result words are zeroed; otherwise the last
 * word is set to param_9 and a metadata-relative builder is invoked.
 * Confidence: low   Notes: unaff_x21 modeled as param; unrecoverable indirect
 *   call target rendered as literal 0x54ffff60f100041f; extraout stack
 *   allocation modeled as a fixed buffer. */
static word_t sk_r30_00492b3c(word_t *param_1, word_t param_2, word_t param_3, word_t param_4,
                              word_t param_5, code *param_6, word_t param_7, word_t param_8,
                              long param_9,
                              long unaff_x21 /* unaff_x21: self/context register-global */)
{
    int iVar1;
    long lVar2;
    word_t uVar3;
    long extraout_x8;
    unsigned char stack_buf[0x200];
    unsigned char *puVar4;
    lVar2 = FUN_00310d68(0, param_9);
    /* Unrecoverable indirect call; decompiler target SUB_54ffff60f100041f with
       argument (*(long *)(*(long *)(lVar2 + -8) + 0x40) + 0xfU & 0xfffffffffffffff0). */
    ((code)(word_t)0x54ffff60f100041f)(*(long *)(*(long *)(lVar2 + -8) + 0x40) + 0xfU & 0xfffffffffffffff0);
    /* decompile: puVar4 = &stack0x... + -extraout_x8 (allocates extraout_x8 bytes on
       the stack; extraout carried from the call above). Modeled as a fixed buffer. */
    extraout_x8 = 0;
    puVar4 = stack_buf;
    (*param_6)(puVar4, param_2, param_3, param_4, param_5);
    if (unaff_x21 == 0) {
        iVar1 = FUN_000839f8(puVar4, 1, param_9);
        if (iVar1 == 1) {
            param_1[1] = 0;
            *param_1 = 0;
            param_1[3] = 0;
            param_1[2] = 0;
        }
        else {
            param_1[3] = param_9;
            uVar3 = FUN_00077024(param_1);
            (**(code **)(*(long *)(param_9 + -8) + 0x20))(uVar3, puVar4, param_9);
        }
    }
    return 0;
}

/* FUN_00493d7c @ 0x00493d7c  (est. sk_r30_make_pair_box)
 * Ghidra: void FUN_00493d7c(undefined8 param_1,...)
 * Builds an 8-word box (destination carried in x8/extraout) containing two
 * tagged pair values (from FUN_0001a1c8), each with a 1-bit flag in the high
 * word, and the two caller params. Flag bit of the second value is ORed with
 * 0x6000000000000000 (pointer tag bits).
 * Confidence: low   Notes: extraout_x8 modeled from FUN_0035354c return;
 *   FUN_0001a1c8's high word not independently recoverable from word_t extern. */
static word_t sk_r30_00493d7c(word_t param_1, word_t param_2, word_t param_3, word_t param_4)
{
    word_t uVar1;
    word_t uVar2;
    word_t *extraout_x8;
    wpair_t auVar3;
    wpair_t auVar4;
    FUN_003504d0();
    FUN_0041cb78();
    FUN_00351790();
    FUN_00352c68();
    auVar3.lo = FUN_0001a1c8();   /* high word (flag) not recoverable from extern; kept as 0 */
    auVar3.hi = 0;
    uVar1 = param_3;
    uVar2 = param_4;
    FUN_0041cb78();
    FUN_00351790();
    FUN_0035354c();
    extraout_x8 = (word_t *)FUN_0035354c();   /* dest pointer carried in x8 */
    auVar4.lo = FUN_0001a1c8();   /* high word not recoverable; kept as 0 */
    auVar4.hi = 0;
    extraout_x8[0] = auVar3.lo;
    extraout_x8[1] = (ulong)(auVar3.hi & 1);
    extraout_x8[2] = param_3;
    extraout_x8[3] = param_4;
    extraout_x8[4] = auVar4.lo;
    extraout_x8[5] = (ulong)(auVar4.hi & 1) | 0x6000000000000000;
    extraout_x8[6] = uVar1;
    extraout_x8[7] = uVar2;
    return 0;
}

/* FUN_004947bc @ 0x004947bc  (est. sk_r30_thunk_494810)
 * Ghidra: void FUN_004947bc(void)
 * Trivial forwarder: invokes FUN_00494810 (an in-slice sibling).
 * Confidence: medium */
static word_t sk_r30_004947bc(void)
{
    /* in-slice prototype sk_r30_00494810 takes 9 args (x4 callback, result buffer,
       x21/x30 context regs, in_98..in_b8 stack args); caller decompile shows none
       (register/stack-passed, unobservable) — pass 0 placeholders */
    FUN_00494810(0, 0, 0, 0, 0, 0, 0, 0, 0);
    return 0;
}

/* FUN_00494b44 @ 0x00494b44  (est. sk_r30_build_box)
 * Ghidra: void FUN_00494b44(undefined8 param_1,undefined8 param_2,undefined8 param_3)
 * Builds a 0x38-byte box seeded from the 16-byte global at 0x4baeb0 and a
 * string/type value (FUN_00002534(0x657b68,&DAT_005a3640)), fills a second
 * child object from an 8-word stack payload produced by FUN_0041aff0 /
 * FUN_0041afc8 (branch on a flag), invokes a metadata-relative closure and
 * dispatches via FUN_000b45b0 with a tagged pointer.
 * Confidence: low   Notes: unaff_x30 and 16-byte global hi word modeled;
 *   in_stack_00000010..48 modeled as a stack-args array. */
static word_t sk_r30_00494b44(word_t param_1, word_t param_2, word_t param_3,
                              word_t unaff_x30 /* unaff_x30: link/self register-global */)
{
    word_t uVar1;
    word_t uVar2;
    word_t uVar3;
    unsigned char uVar4;
    word_t uVar5;
    unsigned char uVar6;
    word_t uVar7;
    long lVar8;
    ulong uVar9;
    word_t extraout_x1;
    code *extraout_x8;
    word_t uVar10;
    word_t auVar11;   /* lo half of the 16-byte pair; hi (flag) not recoverable from word_t extern */
    wpair_t r_1a1c8;
    word_t stack_args[8];
    auVar11 = FUN_000b4594();   /* 16-byte pair; hi word holds a flag */
    uVar7 = FUN_00002534(0x657b68, &DAT_005a3640);
    uVar10 = 7;
    lVar8 = FUN_0036a940(uVar7, 0x38);
    uVar7 = DAT_004baeb0;
    *(word_t *)(lVar8 + 0x18) = *(word_t *)((char *)&DAT_004baeb0 + 8);
    *(word_t *)(lVar8 + 0x10) = uVar7;
    FUN_0041cb78();
    FUN_00351790();
    FUN_00351488(auVar11);
    r_1a1c8.lo = FUN_0001a1c8();   /* hi word not recoverable; kept as 0 */
    r_1a1c8.hi = 0;
    uVar6 = r_1a1c8.lo;
    extraout_x1 = r_1a1c8.hi;   /* carried x1 from call */
    *(word_t *)(lVar8 + 0x20) = uVar6;
    *(word_t *)(lVar8 + 0x28) = extraout_x1;
    *(word_t *)(lVar8 + 0x30) = uVar10;
    /* hi (flag) word of the pair not recoverable from the word_t extern — modeled as 0 */
    if ((0 & 1) == 0) {
        FUN_0041aff0(&stack_args[0], lVar8);
    }
    else {
        FUN_0041afc8(&stack_args[0], lVar8);
    }
    uVar5 = stack_args[7];
    uVar4 = stack_args[6];
    uVar3 = stack_args[5];
    uVar2 = stack_args[4];
    uVar1 = stack_args[3];
    uVar6 = stack_args[2];
    uVar10 = stack_args[1];
    uVar7 = stack_args[0];
    FUN_004ab8c8();
    uVar9 = FUN_0036a940();
    *(word_t *)(uVar9 + 0x10) = uVar7;
    *(word_t *)(uVar9 + 0x18) = uVar10;
    *(unsigned char *)(uVar9 + 0x20) = uVar6;
    *(word_t *)(uVar9 + 0x30) = uVar2;
    *(word_t *)(uVar9 + 0x28) = uVar1;
    *(word_t *)(uVar9 + 0x38) = uVar3;
    *(unsigned char *)(uVar9 + 0x40) = uVar4;
    *(word_t *)(uVar9 + 0x48) = uVar5;
    *(unsigned char *)(uVar9 + 0x60) = 2;
    FUN_004ab5d4(0x686470);
    FUN_003504ac();
    extraout_x8 = (code)FUN_003504ac();   /* code pointer carried in x8 */
    uVar7 = (*extraout_x8)();
    FUN_004ac810();
    FUN_0035056c(0);
    FUN_00377824();
    FUN_0035310c();
    /* in-slice prototype sk_r30_00491644 takes 1 arg; caller decompile shows none
       (register-passed, unobservable) — pass 0 placeholder */
    uVar10 = FUN_00491644(0);
    FUN_0036b118(uVar7);
    *(word_t *)(uVar9 + 0x68) = uVar10;
    FUN_000b45b0(uVar9 | 0x1000000000000004, param_3, unaff_x30);
    FUN_0049153c();
    return 0;
}

/* FUN_00494f3c @ 0x00494f3c  (est. sk_r30_char_scan)
 * Ghidra: byte FUN_00494f3c(undefined8 param_1,char param_2,ulong *param_3,byte param_4)
 * Character/Unicode-scalar scan with several representations (selected by
 * param_2 and by high bits of the two input words). Decodes via FUN_004abbb8
 * (UTF-8/ASCII path), handles multi-byte continuation kinds (switch on a
 * decode kind 1/2/3 reassembling code points), then classifies the scalar
 * with FUN_002bbf08; returns (result & 1) where the flag is set unless the
 * scalar is > 0x7f and param_4 requests otherwise, or the scalar is '_'.
 * Confidence: low   Notes: extraout registers from FUN_004abbb8/FUN_003527b8
 *   modeled via the call returns (not independently recoverable). */
static word_t sk_r30_00494f3c(word_t param_1, char param_2, ulong *param_3, byte param_4)
{
    bool bVar1;
    uint uVar2;
    uint uVar8;
    ulong uVar3;
    ulong uVar4;
    ulong uVar5;
    long lVar6;
    byte bVar7;
    uint extraout_w8;
    uint extraout_w8_00;
    uint extraout_w8_01;
    int extraout_w9;
    int extraout_w9_00;
    int extraout_w9_01;
    word_t extraout_x8;
    word_t extraout_x16;
    word_t extraout_x16_00;
    long decode;
    ulong local_40;
    ulong uStack_38;
    uVar4 = *param_3;
    uVar5 = param_3[1];
    if (param_2 != '\x01') {
        FUN_00350548();
        FUN_00267510();
        FUN_00354e0c();
        uVar4 = FUN_00436fc8();
        if ((uVar4 & 1) != 0) {
            FUN_000b43d0();
            uVar2 = FUN_002bd8f0();
            FUN_003a25d4(uVar5);
            bVar1 = (uVar2 & 0xff00) == 0x100;
            goto LAB_00495088;
        }
        FUN_003a25d4(uVar5);
        goto LAB_00495078;
    }
    FUN_00350548();
    uVar3 = FUN_00167404();
    if (((uVar5 >> 0x3c) & 1) != 0) {
        FUN_00350548(uVar3 & 0xffffffffffff0000);
        uVar5 = FUN_002a49a8();
        goto switchD_00494fb4_caseD_0;
    }
    uVar3 = uVar3 >> 0x10;
    if (((uVar5 >> 0x3d) & 1) != 0) {
        uStack_38 = uVar5 & 0xffffffffffffff;
        local_40 = uVar4;
        extraout_w9_00 = (int)FUN_004abbb8((long)&local_40 + uVar3);
        if (extraout_w9_00 < 0) {
            FUN_003527b8();
            extraout_x16_00 = FUN_003527b8();   /* decode kind carried */
            switch ((uint)extraout_x16_00) {
            case 1:
                goto switchD_00494fb4_caseD_1;
            case 2:
                goto switchD_00494fb4_caseD_2;
            case 3:
                goto switchD_00494fb4_caseD_3;
            }
        }
        goto switchD_00494fb4_caseD_0;
    }
    if (((uVar4 >> 0x3c) & 1) == 0) {
        FUN_000b43d0();
        lVar6 = FUN_002a9ba8();
        extraout_x8 = lVar6;   /* carried x8 (not independently recoverable) */
        uVar3 = extraout_x8;
        uVar5 = extraout_x8;
    }
    else {
        lVar6 = (uVar5 & 0xfffffffffffffff) + 0x20;
    }
    extraout_w9 = (int)FUN_004abbb8(lVar6 + uVar3);
    if (-1 < extraout_w9) goto switchD_00494fb4_caseD_0;
    FUN_003527b8();
    extraout_x16 = FUN_003527b8();   /* decode kind carried */
    switch ((uint)extraout_x16) {
    case 1:
switchD_00494fb4_caseD_1:
        extraout_w8 = (uint)FUN_00353ff4();   /* carried w8 */
        uVar5 = (ulong)(extraout_w8 & 0xfffff800 | extraout_w8 & 0x3f | ((uint)uVar5 & 0x1f) << 6);
        break;
    case 2:
switchD_00494fb4_caseD_2:
        decode = FUN_00352e9c();
        extraout_w9_01 = (int)decode;
        extraout_w8_00 = (uint)decode;
        uVar2 = ((uint)uVar5 & 0xf) << 0xc | (extraout_w9_01 & 0x3f) << 6;
        uVar8 = extraout_w8_00;
        goto LAB_00495060;
    case 3:
switchD_00494fb4_caseD_3:
        uVar2 = (uint)uVar5;
        FUN_0034c6d4();
        FUN_004abfc8();
        extraout_w8_01 = (uint)FUN_004abfc8();   /* carried w8 */
        uVar8 = extraout_w8_01;
LAB_00495060:
        uVar5 = (ulong)(uVar2 & 0xffffffc0 | uVar8 & 0x3f);
    }
switchD_00494fb4_caseD_0:
    uVar4 = FUN_002bbf08(uVar5);
    if (((uVar4 & 1) == 0) && ((uint)uVar5 != 0x5f)) {
LAB_00495078:
        bVar7 = 0;
    }
    else {
        bVar1 = 0x7f < (uint)uVar5;
LAB_00495088:
        bVar7 = !bVar1 | param_4 ^ 1;
    }
    return bVar7 & 1;
}

/* FUN_004954d0 @ 0x004954d0  (est. sk_r30_make_box)
 * Ghidra: void FUN_004954d0(void)
 * Allocates a box (FUN_0036a940), invokes FUN_0049ca58 on a stack area,
 * registers/initializes the box body at +0x10, and dispatches it with the
 * tagged pointer flag 0x4000000000000000.
 * Confidence: low   Notes: stack pointer arg to FUN_0049ca58 modeled as buffer. */
static word_t sk_r30_004954d0(void)
{
    ulong uVar1;
    unsigned char stack_buf[0x20];
    FUN_003504d0();
    FUN_004aa7bc();
    uVar1 = FUN_0036a940();
    FUN_0049ca58(stack_buf);
    FUN_004ac61c(uVar1 + 0x10);
    /* in-slice prototype sk_r30_0049153c is void; tagged-arg dropped to match */
    FUN_0049153c();
    return 0;
}

/* FUN_00495940 @ 0x00495940  (est. sk_r30_make_closure)
 * Ghidra: void FUN_00495940(void)
 * Builds a closure/object: captures a function pointer (FUN_00350980), zeroes
 * and flags the new object (+0x28 = 1), performs setup calls including an
 * indirect call through a carried code pointer, stores the captured value at
 * +0x30, zeroes the remaining fields, and dispatches it with the tagged
 * pointer flag 0x1000000000000000.
 * Confidence: low   Notes: in_x3 modeled as param; extraout code pointer from
 *   FUN_00084180; FUN_0036b118() called with no captured arg. */
static word_t sk_r30_00495940(word_t in_x3 /* in_x3: input register x3 */)
{
    word_t uVar1;
    ulong uVar2;
    code *extraout_x8;
    uVar1 = FUN_00350980();
    FUN_004aada4();
    uVar2 = FUN_0036a940();
    *(word_t *)(uVar2 + 0x18) = 0;
    *(word_t *)(uVar2 + 0x20) = 0;
    *(word_t *)(uVar2 + 0x10) = 0;
    *(unsigned char *)(uVar2 + 0x28) = 1;
    FUN_004ab5d4(in_x3);
    FUN_00084180();
    extraout_x8 = (code)FUN_00084180();   /* code pointer carried in x8 */
    (*extraout_x8)();
    /* in-slice prototype sk_r30_00491644 takes 1 arg; caller decompile shows none
       (register-passed, unobservable) — pass 0 placeholder */
    FUN_00491644(0);
    FUN_00351d18();
    FUN_0036b118();
    *(word_t *)(uVar2 + 0x30) = uVar1;
    *(word_t *)(uVar2 + 0x40) = 0;
    *(word_t *)(uVar2 + 0x38) = 0;
    *(word_t *)(uVar2 + 0x50) = 0;
    *(word_t *)(uVar2 + 0x48) = 0;
    *(unsigned char *)(uVar2 + 0x58) = 0;
    /* in-slice prototype sk_r30_0049153c is void; tagged-arg dropped to match */
    FUN_0049153c();
    return 0;
}

/* FUN_004961a0 @ 0x004961a0  (est. sk_r30_witness_dispatch)
 * Ghidra: void FUN_004961a0(long param_1)
 * Loads the witness/selector word at param_1+0x20, resolves a function pointer
 * via FUN_00027788, and calls it with the operand at param_1+0x10 and the
 * witness word. Classic Swift protocol-witness / vtable dispatch tail.
 * Confidence: low   Notes: decompiler could not recover the jumptable; the
 *   indirect call is rendered through the resolved pointer. */
static word_t sk_r30_004961a0(long param_1)
{
    word_t uVar1;
    code *UNRECOVERED_JUMPTABLE;
    uVar1 = *(word_t *)(param_1 + 0x20);
    UNRECOVERED_JUMPTABLE = (code *)FUN_00027788(uVar1);
    (*UNRECOVERED_JUMPTABLE)(*(word_t *)(param_1 + 0x10), uVar1);
    return 0;
}
