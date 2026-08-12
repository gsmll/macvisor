/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel,
 * arm64e, image base 0) — the cL4 microkernel. Ground truth: Ghidra FUN_ names +
 * addresses in program cl4_kernel.raw. Version "cL4 microkernel (cL4
 * (679.100.61))". All names are estimates unless string/header-matched.
 *
 * This file covers wave batch SKR31, slice 0x004961e8-0x0049a4b8: the embedded
 * Swift standard-library runtime's Array-buffer / collection machinery. The
 * functions are the per-element-type instantiations of Swift's uninitialized
 * array-buffer allocation (`_allocateUninitializedArray`), in-place
 * resize-with-move-or-copy (`_ArrayBuffer._copyContents`/`makeUnique`),
 * memmove-style bulk element copies with overlap/trap checks, hash-map slot
 * insertion (the functions at 0x499fcc-0x49a3c0 walk a per-element hash table
 * and its parallel bitset + value arrays), and the two large RangeSet-style
 * range-merge rebuild routines (0x49751c and 0x4979f8) that merge overlapping
 * half-open ranges (each tagged 64-bit element is a "start" word whose upper
 * bits hold an index, so addresses are shifted >>0xe for comparison). The
 * 16-byte {lo,hi} returns carry a tagged word plus a small descriptor/tag in
 * the low byte of hi (seL4-style tagged word). Many helpers are entered with
 * register-globals (unaff_x20/x19/x21 = a self/context pointer carried in a
 * callee-saved register); those are transcribed as named parameters with a
 * note.
 *
 * All out-of-range callees are declared as unprototyped externs (AAPCS64:
 * args in x0..x7, result in x0). The 16-byte-return helpers use the
 * sk_r31_pair_t struct. Signatures are estimates; the FUN_ address is in each
 * comment.
 */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "sk_internal.h"

/* 16-byte (two-word) result used by the return-by-value helpers below. */
typedef struct sk_r31_pair { word_t lo, hi; } sk_r31_pair_t;

/* SoftwareBreakpoint(1, addr) — a trap/fault at the given binary address. */
#define SK_TRAP(a) __builtin_trap()

/* Empty-buffer / sentinel data singletons referenced by this slice
 * (Ghidra DAT_ symbols). */
extern word_t sk_d_00657778;   /* DAT_00657778: empty-buffer sentinel */

/* ------------------------------------------------------------------ *
 * Out-of-range cL4/Swift-runtime helpers referenced by this slice.
 * Unprototyped AAPCS64 externs. sk_r31_pair_t for the 16-byte returns.
 * FUN_ addresses in comments. Names are estimates.
 * ------------------------------------------------------------------ */

extern word_t sk_h_00002534();  /* FUN_00002534 */
extern word_t sk_h_0001dd14();  /* FUN_0001dd14 */
extern word_t sk_h_00021480();  /* FUN_00021480 */
extern word_t sk_h_00027754();  /* FUN_00027754 */
extern word_t sk_h_000277e8();  /* FUN_000277e8 */
extern sk_r31_pair_t sk_h_00041138(); /* FUN_00041138 */
extern word_t sk_h_00069970();  /* FUN_00069970 */
extern word_t sk_h_000699a4();  /* FUN_000699a4 */
extern word_t sk_h_000699d8();  /* FUN_000699d8 */
extern sk_r31_pair_t sk_h_0006ae9c(); /* FUN_0006ae9c */
extern word_t sk_h_0006b3f4();  /* FUN_0006b3f4 */
extern sk_r31_pair_t sk_h_0006b42c(); /* FUN_0006b42c */
extern word_t sk_h_00071a4c();  /* FUN_00071a4c */
extern word_t sk_h_00071fe4();  /* FUN_00071fe4 */
extern word_t sk_h_00072044();  /* FUN_00072044 */
extern word_t sk_h_000720a8();  /* FUN_000720a8 */
extern word_t sk_h_000721b0();  /* FUN_000721b0 */
extern word_t sk_h_000721d8();  /* FUN_000721d8 */
extern word_t sk_h_00072320();  /* FUN_00072320 */
extern word_t sk_h_00072358();  /* FUN_00072358 */
extern word_t sk_h_00072a30();  /* FUN_00072a30 */
extern word_t sk_h_00074a28();  /* FUN_00074a28 */
extern word_t sk_h_00074b08();  /* FUN_00074b08 */
extern word_t sk_h_00074dc8();  /* FUN_00074dc8 */
extern word_t sk_h_00075624();  /* FUN_00075624 */
extern word_t sk_h_0007764c();  /* FUN_0007764c */
extern word_t sk_h_0007766c();  /* FUN_0007766c */
extern word_t sk_h_000776cc();  /* FUN_000776cc */
extern word_t sk_h_000776d8();  /* FUN_000776d8 */
extern word_t sk_h_000776f8();  /* FUN_000776f8 */
extern word_t sk_h_00077888();  /* FUN_00077888 */
extern word_t sk_h_0007791c();  /* FUN_0007791c */
extern word_t sk_h_0007c028();  /* FUN_0007c028 */
extern sk_r31_pair_t sk_h_0007c1c4(); /* FUN_0007c1c4 */
extern word_t sk_h_0008409c();  /* FUN_0008409c */
extern sk_r31_pair_t sk_h_00084174(); /* FUN_00084174 */
extern word_t sk_h_00084180();  /* FUN_00084180 */
extern sk_r31_pair_t sk_h_00084220(); /* FUN_00084220 */
extern word_t sk_h_00084234();  /* FUN_00084234 */
extern word_t sk_h_000867ec();  /* FUN_000867ec */
extern word_t sk_h_000a6f88();  /* FUN_000a6f88 */
extern word_t sk_h_000a6fe0();  /* FUN_000a6fe0 */
extern word_t sk_h_000aa4ec();  /* FUN_000aa4ec */
extern sk_r31_pair_t sk_h_000dbd0c(); /* FUN_000dbd0c */
extern word_t sk_h_000e15d8();  /* FUN_000e15d8 */
extern word_t sk_h_000f4ae8();  /* FUN_000f4ae8 */
extern word_t sk_h_00106e3c();  /* FUN_00106e3c */
extern word_t sk_h_00117cc4();  /* FUN_00117cc4: memcpy */
extern word_t sk_h_00117d14();  /* FUN_00117d14: memmove */
extern word_t sk_h_001a09bc();  /* FUN_001a09bc */
extern word_t sk_h_001a84f4();  /* FUN_001a84f4 */
extern word_t sk_h_001a8564();  /* FUN_001a8564 */
extern word_t sk_h_00229a3c();  /* FUN_00229a3c */
extern word_t sk_h_00257020();  /* FUN_00257020 */
extern word_t sk_h_00258c60();  /* FUN_00258c60 */
extern word_t sk_h_002591b4();  /* FUN_002591b4: noreturn "Fatal error" */
extern word_t sk_h_002a0cf8();  /* FUN_002a0cf8 */
extern word_t sk_h_002b3b50();  /* FUN_002b3b50 */
extern word_t sk_h_002b3cf8();  /* FUN_002b3cf8 */
extern sk_r31_pair_t sk_h_002b3f40(); /* FUN_002b3f40 */
extern sk_r31_pair_t sk_h_002b439c(); /* FUN_002b439c */
extern word_t sk_h_002cfc5c();  /* FUN_002cfc5c */
extern word_t sk_h_0031090c();  /* FUN_0031090c */
extern word_t sk_h_00310924();  /* FUN_00310924 */
extern word_t sk_h_00310cd4();  /* FUN_00310cd4 */
extern word_t sk_h_00310d34();  /* FUN_00310d34 */
extern word_t sk_h_00310e08();  /* FUN_00310e08 */
extern word_t sk_h_00319658();  /* FUN_00319658 */
extern word_t sk_h_0031afcc();  /* FUN_0031afcc */
extern word_t sk_h_0031b080();  /* FUN_0031b080 */
extern word_t sk_h_0031dec4();  /* FUN_0031dec4 */
extern word_t sk_h_0031e104();  /* FUN_0031e104 */
extern word_t sk_h_0031fc28();  /* FUN_0031fc28 */
extern word_t sk_h_003468a4();  /* FUN_003468a4 */
extern word_t sk_h_00349530();  /* FUN_00349530 */
extern word_t sk_h_00349a18();  /* FUN_00349a18 */
extern sk_r31_pair_t sk_h_0034d090(); /* FUN_0034d090 */
extern word_t sk_h_0034d3d4();  /* FUN_0034d3d4 */
extern word_t sk_h_003504a0();  /* FUN_003504a0 */
extern word_t sk_h_003504e8();  /* FUN_003504e8 */
extern word_t sk_h_00350500();  /* FUN_00350500 */
extern word_t sk_h_0035050c();  /* FUN_0035050c */
extern word_t sk_h_00350a1c();  /* FUN_00350a1c */
extern word_t sk_h_00350b54();  /* FUN_00350b54 */
extern word_t sk_h_003510b8();  /* FUN_003510b8 */
extern word_t sk_h_00351124();  /* FUN_00351124 */
extern sk_r31_pair_t sk_h_00351450(); /* FUN_00351450 */
extern word_t sk_h_00351aec();  /* FUN_00351aec */
extern word_t sk_h_00352b20();  /* FUN_00352b20 */
extern word_t sk_h_00352efc();  /* FUN_00352efc */
extern word_t sk_h_00353208();  /* FUN_00353208 */
extern word_t sk_h_0035354c();  /* FUN_0035354c */
extern word_t sk_h_00354998();  /* FUN_00354998 */
extern word_t sk_h_00354f1c();  /* FUN_00354f1c */
extern word_t sk_h_003580e4();  /* FUN_003580e4 */
extern word_t sk_h_0035847c();  /* FUN_0035847c */
extern word_t sk_h_0035b67c();  /* FUN_0035b67c: bulk element copy */
extern word_t sk_h_0035bc70();  /* FUN_0035bc70 */
extern word_t sk_h_0036a908();  /* FUN_0036a908 */
extern word_t sk_h_0036a940();  /* FUN_0036a940: object alloc */
extern word_t sk_h_0036b118();  /* FUN_0036b118: release */
extern word_t sk_h_0036b270();  /* FUN_0036b270: retain */
extern word_t sk_h_0036ffc0();  /* FUN_0036ffc0 */
extern word_t sk_h_00377824();  /* FUN_00377824 */
extern word_t sk_h_00377bec();  /* FUN_00377bec */
extern word_t sk_h_003a25d4();  /* FUN_003a25d4: release */
extern word_t sk_h_003a261c();  /* FUN_003a261c: refcount check */
extern word_t sk_h_00407eac();  /* FUN_00407eac */
extern word_t sk_h_004080b0();  /* FUN_004080b0 */
extern word_t sk_h_0044ca08();  /* FUN_0044ca08 */
extern word_t sk_h_0044ca2c();  /* FUN_0044ca2c */
extern word_t sk_h_0044ca60();  /* FUN_0044ca60 */
extern word_t sk_h_00456b28();  /* FUN_00456b28 */
extern word_t sk_h_00462abc();  /* FUN_00462abc */
extern word_t sk_h_00465294();  /* FUN_00465294 */
extern word_t sk_h_004652d4();  /* FUN_004652d4 */
extern word_t sk_h_00465428();  /* FUN_00465428 */
extern sk_r31_pair_t sk_h_0046ea44(); /* FUN_0046ea44 */
extern word_t sk_h_0046ece8();  /* FUN_0046ece8 */
extern sk_r31_pair_t sk_h_0046f298(); /* FUN_0046f298 */
extern word_t sk_h_00476e74();  /* FUN_00476e74 */
extern word_t sk_h_00495bcc();  /* FUN_00495bcc */
extern word_t sk_h_00495c48();  /* FUN_00495c48 */
extern word_t sk_h_0049c704();  /* FUN_0049c704 */
extern word_t sk_h_004a1a50();  /* FUN_004a1a50 */
extern word_t sk_h_004a29d4();  /* FUN_004a29d4 */
extern sk_r31_pair_t sk_h_004a30ec(); /* FUN_004a30ec */
extern word_t sk_h_004a398c();  /* FUN_004a398c */
extern word_t sk_h_004a4184();  /* FUN_004a4184 */
extern word_t sk_h_004a4ac4();  /* FUN_004a4ac4 */
extern word_t sk_h_004a4b14();  /* FUN_004a4b14 */
extern word_t sk_h_004a4b60();  /* FUN_004a4b60 */
extern sk_r31_pair_t sk_h_004aa5dc(); /* FUN_004aa5dc */
extern word_t sk_h_004ab4b4();  /* FUN_004ab4b4 */
extern word_t sk_h_004ab574();  /* FUN_004ab574 */
extern word_t sk_h_004ab5a4();  /* FUN_004ab5a4 */
extern word_t sk_h_004ab698();  /* FUN_004ab698 */
extern word_t sk_h_004ab910();  /* FUN_004ab910 */
extern word_t sk_h_004abcf8();  /* FUN_004abcf8 */
extern word_t sk_h_004ac2ac();  /* FUN_004ac2ac */
extern word_t sk_h_004ac2c4();  /* FUN_004ac2c4 */
extern word_t sk_h_004ac868();  /* FUN_004ac868 */

extern word_t sk_h_00012568();  /* thunk_FUN_00012568 */
extern word_t sk_h_000126e8();  /* thunk_FUN_000126e8: malloc_size */
extern word_t sk_h_001a0d1c();  /* thunk_FUN_001a0d1c */
extern word_t sk_h_002298d4();  /* thunk_FUN_002298d4 */
extern word_t sk_h_002acbb8();  /* thunk_FUN_002acbb8 */
extern sk_r31_pair_t sk_h_002b74c0(); /* thunk_FUN_002b74c0 */
extern word_t sk_h_0036b270();  /* thunk_FUN_0036b270: retain */

/* Data singletons (Ghidra DAT_ / string-metadata addresses) referenced with
 * their address as a pointer argument. */
extern word_t sk_d_004bbf40;
extern word_t sk_d_004bedf0;
extern word_t sk_d_005a3c70;
extern word_t sk_d_005a3cb0;
extern word_t sk_d_005a3cd0;
extern word_t sk_d_005a4ae0;
extern word_t sk_d_005a4b08;
extern word_t sk_d_005a4b30;
extern word_t sk_d_005a4b40;
extern word_t sk_d_005a4b48;
extern word_t sk_d_005a4b80;
extern word_t sk_d_005a4b98;
extern word_t sk_d_005a4ba0;
extern word_t sk_d_005a4ba8;
extern word_t sk_d_005a4bb0;
extern word_t sk_d_005a4bb8;
extern word_t sk_d_005a4bd0;
extern word_t sk_d_005a4be0;
extern word_t sk_d_005a4c20;
extern word_t sk_d_005a5530;
extern word_t sk_d_005a5560;
extern word_t sk_d_005a55f8;
extern word_t sk_d_005a5600;
extern word_t sk_d_005a5c98;
extern word_t sk_d_0060e208;
extern word_t sk_d_0060e218;
extern word_t sk_d_0060e230;
extern word_t sk_d_00611b24;
extern word_t sk_d_00611b34;
extern word_t sk_d_00616a58;
extern word_t sk_d_0064c040;
extern word_t sk_d_00657798;
extern word_t sk_d_00657d30;
extern word_t sk_d_00657d50;
extern word_t sk_d_00657d68;
extern word_t sk_d_00657d78;
extern word_t sk_d_00657d80;
extern word_t sk_d_00657da8;
extern word_t sk_d_00657db0;
extern word_t sk_d_00657db8;
extern word_t sk_d_00657dc0;
extern word_t sk_d_00657dc8;
extern word_t sk_d_00657de0;
extern word_t sk_d_00657df0;
extern word_t sk_d_00657e18;
extern word_t sk_d_00657e20;
extern word_t sk_d_00657e28;
extern word_t sk_d_00657e78;
extern word_t sk_d_00657e80;
extern word_t sk_d_00657e88;
extern word_t sk_d_00688878;
extern word_t sk_d_006888f0;
extern word_t sk_d_00688ea0;
extern word_t sk_d_006893a8;
extern word_t sk_d_00657c08;
extern word_t sk_d_00657c28;
extern word_t sk_d_0064e118;
extern word_t sk_d_0064e078;
extern word_t sk_d_006728f0;
extern word_t sk_d_006879c8;
extern word_t sk_d_00687408;
extern word_t sk_d_00686868;
extern word_t sk_d_00686660;
extern word_t sk_d_00687800;
extern word_t sk_d_0066acf0;

/* ------------------------------------------------------------------ *
 * Forward declarations for in-file (in-batch) functions. Signatures are
 * the Ghidra-decompiled AAPCS64 signatures; functions that were entered
 * with register-globals (unaff_x19/x20/x21) take those as explicit
 * trailing parameters, marked with a "/* reg */" comment.
 * ------------------------------------------------------------------ */
word_t sk_r31_4961e8(word_t, long);
void sk_r31_496248(word_t, word_t, word_t);
void sk_r31_4962f8(word_t, word_t, long);
word_t sk_r31_496354(word_t, word_t, long);
void sk_r31_4963b8(word_t *);
void sk_r31_4963e4(word_t *, word_t);
void *sk_r31_496420(void);
sk_r31_pair_t sk_r31_49648c(long *, word_t, long);
void sk_r31_496558(word_t *);
void sk_r31_4965a8(word_t *out);
void sk_r31_4965d0(word_t *out);
void sk_r31_4965f8(long, word_t);
word_t sk_r31_4966dc(word_t, word_t);
void sk_r31_496764(long *);
void sk_r31_4967a0(void);
void *sk_r31_49685c(void);
void sk_r31_4968d0(word_t, word_t *);
void sk_r31_4968fc(word_t, word_t, word_t, word_t);
void sk_r31_496b2c(void);
void sk_r31_496bd4(void);
void sk_r31_496bd8(void);
word_t sk_r31_496bf0(word_t, word_t, word_t);
void sk_r31_496c4c(word_t *, word_t *, word_t, ulong);
void sk_r31_496c80(word_t *, word_t, ulong);
void sk_r31_496cb4(void);
void sk_r31_496cdc(word_t, word_t, word_t *);
void sk_r31_496d18(word_t, word_t, word_t, word_t, word_t);
sk_r31_pair_t sk_r31_496ef0(void);
word_t sk_r31_496f58(word_t, long, ulong);
word_t sk_r31_496fec(long, uint);
void sk_r31_497088(word_t, uint);
void sk_r31_4970cc(uint);
void sk_r31_497110(void);
void sk_r31_49712c(void);
void sk_r31_497148(void);
sk_r31_pair_t sk_r31_497224(byte);
sk_r31_pair_t sk_r31_497354(ulong);
void sk_r31_4973cc(void);
void sk_r31_4973e8(word_t *, word_t *, word_t *, void *);
void sk_r31_497430(word_t, ulong);
long sk_r31_49747c(ulong);
void sk_r31_4974ac(void);
word_t sk_r31_4974c4(word_t);
void sk_r31_4974ec(void);
void sk_r31_497504(void);
word_t sk_r31_49751c(long);
word_t sk_r31_497994(word_t);
void sk_r31_4979bc(void);
void sk_r31_4979d4(void);
word_t sk_r31_4979f8(ulong *);
word_t sk_r31_4981d8(word_t, word_t, word_t *, word_t *);
word_t sk_r31_498228(long, long);
word_t sk_r31_4982ac(long, long);
word_t sk_r31_498328(long, long);
word_t sk_r31_4983ac(word_t, word_t, word_t *, word_t *);
word_t sk_r31_4983fc(word_t, word_t, word_t *, word_t *);
word_t sk_r31_49844c(word_t, word_t, word_t *, word_t *);
word_t sk_r31_49849c(word_t, word_t);
void sk_r31_498500(word_t, long, word_t);
void sk_r31_498578(word_t, long, word_t);
void sk_r31_4985b4(void);
void sk_r31_4985e0(void);
word_t sk_r31_49860c(word_t *, long, ulong, word_t, word_t, long);
long sk_r31_498708(long, ulong *, long);
void sk_r31_498ad4(void);
void sk_r31_498b28(void *);
void sk_r31_498b7c(void);
void sk_r31_498bdc(long);
void sk_r31_498c1c(word_t, word_t);
void sk_r31_498c54(void);
void sk_r31_498c6c(void);
void sk_r31_498c84(word_t);
long sk_r31_498cc8(ulong, ulong, ulong, long);
long sk_r31_498d8c(ulong, ulong, ulong, long);
long sk_r31_498e50(ulong, long, ulong, long, void *, void *, void *);
long sk_r31_498f0c(ulong, ulong, ulong, long);
long sk_r31_498fd0(ulong, ulong, ulong, long);
long sk_r31_499094(ulong, ulong, ulong, long);
long sk_r31_499158(ulong, ulong, ulong, long);
long sk_r31_49921c(ulong, long, ulong, long, word_t, word_t);
long sk_r31_4992c8(ulong, ulong, ulong, long);
long sk_r31_49938c(ulong, ulong, ulong, long);
void sk_r31_499450(word_t, word_t);
long sk_r31_499468(ulong, ulong, ulong, long);
long sk_r31_49952c(ulong, long, ulong, long, word_t, word_t);
long sk_r31_4995e4(ulong, ulong, ulong, long);
long sk_r31_4996a8(ulong, ulong, ulong, long);
long sk_r31_49976c(ulong, ulong, ulong, long);
word_t sk_r31_499820(long, long, ulong, long);
word_t sk_r31_49989c(long, long, ulong, long);
word_t sk_r31_499918(long, long, ulong, long);
word_t sk_r31_499998(long, long, ulong, long);
word_t sk_r31_499a0c(long, long, ulong, long);
word_t sk_r31_499a8c(long, long, ulong, long);
word_t sk_r31_499afc(long, long, ulong, long);
word_t sk_r31_499b90(long, long, ulong, long, word_t);
word_t sk_r31_499c08(long, long, ulong, long);
word_t sk_r31_499c7c(long, long, ulong, long);
void sk_r31_499cfc(word_t, long, word_t);
void sk_r31_499d38(word_t, long, word_t);
void sk_r31_499d7c(word_t, long, word_t);
long sk_r31_499dbc(long);
word_t sk_r31_499e1c(long);
word_t sk_r31_499e94(long);
void sk_r31_499f0c(word_t);
sk_r31_pair_t sk_r31_499f6c(word_t);
void sk_r31_499fcc(word_t, word_t, word_t, long);
void sk_r31_49a010(word_t, word_t, word_t, word_t, long);
void sk_r31_49a058(word_t, word_t, word_t);
void sk_r31_49a184(word_t, word_t);
void sk_r31_49a2a4(long, ulong);
void sk_r31_49a348(long, uint, void *);
void sk_r31_49a3c0(void);
void sk_r31_49a440(long);
void sk_r31_49a454(long);
void sk_r31_49a468(long);
void sk_r31_49a47c(long);
void sk_r31_49a490(long);
void sk_r31_49a4a4(long);
void sk_r31_49a4b8(long);

/* ------------------------------------------------------------------ *
 * Function bodies (address order).
 * ------------------------------------------------------------------ */

/* FUN_004961e8 @ 0x004961e8   (est. sk_r31_witness_dispatch)
 * Ghidra: undefined8 FUN_004961e8(undefined8 param_1, long param_2)
 * Generic Swift witness-table dispatch: looks up a function pointer from the
 * witness/vtable stored at param_2+0x20 (via the lookaside FUN_00319658),
 * then calls it with (result-out, arg-box, param_2+0x10 value, witness word)
 * and returns the value written to the result slot. Low confidence (the
 * indirect call target is a runtime witness).
 * Confidence: low
 * Notes: FUN_00319658 witness-table lookaside; result returned via local_38. */
word_t sk_r31_4961e8(word_t arg, long table)
{
    word_t local_40;
    word_t local_38;
    word_t witness = *(word_t *)(table + 0x20);

    local_40 = arg;
    void (*witness_fn)(word_t *, word_t *, word_t, word_t) =
        (void *)sk_h_00319658(witness);
    witness_fn(&local_38, &local_40, *(word_t *)(table + 0x10), witness);
    return local_38;
}

/* FUN_00496248 @ 0x00496248   (est. sk_r31_metadata_emit)
 * Ghidra: void FUN_00496248(void)
 * Emits/composes Swift type-metadata strings. Enters with register globals
 * (unaff_x20 = a function pointer, unaff_x30 = a context pointer) that the
 * decompiler cannot resolve; the visible sequence is: snapshot a 16-byte
 * value, read type-metadata offsets, call a metadata-fetch helper
 * (FUN_00350a1c) on a stack box, release the type, fetch a fresh value,
 * release and rebuild, then invoke a stored function pointer with a flag.
 * Transcribed with the register-held values as explicit parameters.
 * Confidence: low
 * Notes: register globals extraout_x8/x16/unaff_x20/unaff_x30 unresolvable;
 * several indirect calls go through those. */
void sk_r31_496248(word_t a, word_t b, word_t c)
{
    sk_r31_pair_t auVar4 = sk_h_00041138();
    word_t uVar3;
    word_t uVar2;
    word_t uVar1;

    uVar3 = *(word_t *)(auVar4.hi + 0x20);
    uVar1 = sk_h_000277e8(uVar3);
    uVar2 = *(word_t *)(auVar4.hi + 0x10);
    /* FUN_00350a1c(uVar1, &stack0x08, &stack0x28): metadata fetch into a box */
    sk_h_00350a1c(uVar1, (word_t *)((word_t)&uVar1), (word_t *)&uVar2);
    sk_h_00354f1c();
    sk_h_00027754(uVar3);
    auVar4 = sk_h_004aa5dc();
    sk_h_00377824(auVar4.lo, auVar4.hi, uVar2);
    sk_h_00349530();
    sk_h_0035847c(0);   /* unaff_x30 context ptr dropped by decompiler */
}

/* FUN_004962f8 @ 0x004962f8   (est. sk_r31_witness_dispatch_void)
 * Ghidra: void FUN_004962f8(undefined8, undefined8, long)
 * Like FUN_004961e8 but discards the result: dispatches through the witness
 * table at param_3+0x20 on a boxed (param_1,param_2) pair.
 * Confidence: low
 * Notes: FUN_00310cd4 witness lookaside. */
void sk_r31_4962f8(word_t a, word_t b, long table)
{
    word_t uStack_38 = a;
    word_t local_40 = b;
    word_t witness = *(word_t *)(table + 0x20);

    void (*witness_fn)(word_t *, word_t *, word_t, word_t) =
        (void *)sk_h_00310cd4(witness);
    witness_fn(&uStack_38, &local_40, *(word_t *)(table + 0x10), witness);
}

/* FUN_00496354 @ 0x00496354   (est. sk_r31_witness_fetch)
 * Ghidra: undefined8 FUN_00496354(undefined8, undefined8, long)
 * Fetches a value through the witness table at param_3+0x20 after seeding a
 * metadata buffer via FUN_00350b54; returns the produced value.
 * Confidence: low
 * Notes: FUN_0031afcc witness lookaside. */
word_t sk_r31_496354(word_t a, word_t b, long table)
{
    word_t local_40 = sk_h_00350b54();
    word_t local_38;
    void (*witness_fn)(word_t *, word_t *) = (void *)sk_h_0031afcc(*(word_t *)(table + 0x20));

    witness_fn(&local_38, &local_40);
    return local_38;
}

/* FUN_004963b8 @ 0x004963b8   (est. sk_r31_bool_witness_init)
 * Ghidra: void FUN_004963b8(undefined8 *param_1)
 * Stores a freshly-created Bool-type metadata witness into *param_1.
 * Confidence: low */
void sk_r31_4963b8(word_t *out)
{
    sk_h_004ab574();
    *out = sk_h_00495c48();
}

/* FUN_004963e4 @ 0x004963e4   (est. sk_r31_bool_witness_init_cmp)
 * Ghidra: void FUN_004963e4(undefined8 *param_1, undefined8 param_2)
 * Stores a Bool metadata witness built with the comparator FUN_00310924.
 * Confidence: low */
void sk_r31_4963e4(word_t *out, word_t arg)
{
    *out = sk_h_00495c48(arg, sk_h_00310924);
}

/* FUN_00496420 @ 0x00496420   (est. sk_r31_epoch_witness_builder)
 * Ghidra: code * FUN_00496420(void)
 * Builds a witness object (0x28-byte allocation, tag 0xad87), stores the
 * result of FUN_0049648c into it, and returns a fixed witness entry-point
 * (FUN_0031fc28). Register globals unaff_x21/x22 are the constructor args.
 * Confidence: low
 * Notes: unaff_x21/x22 unresolvable register globals. */
void *sk_r31_496420(void)
{
    long lVar1;
    word_t uVar2;

    sk_h_000867ec();
    lVar1 = sk_h_0036a908(0x28, 0xad87);
    uVar2 = sk_r31_49648c((long *)lVar1, 0, 0);
    *(word_t *)(lVar1 + 0x20) = uVar2;
    return (void *)sk_h_0031fc28;
}

/* FUN_0049648c @ 0x0049648c   (est. sk_r31_witness_ctor)
 * Ghidra: undefined1[16] FUN_0049648c(long *param_1, undefined8, long)
 * Constructs a metadata witness: fetches a type, builds a class/metadata
 * record, allocates a 0xd560-tagged object, initializes it (FUN_00496248),
 * and returns a {function, object} pair.
 * Confidence: low
 * Notes: DAT_00611b24 / LAB_00611b34 metadata strings. */
sk_r31_pair_t sk_r31_49648c(long *out, word_t arg, long table)
{
    sk_r31_pair_t r;
    word_t uVar1;
    long lVar2;

    uVar1 = sk_h_00027754(*(word_t *)(table + 0x20));
    lVar2 = sk_h_00377824(0, uVar1, *(word_t *)(table + 0x10),
                          &sk_d_00611b24, &sk_d_00611b34);
    *out = lVar2;
    lVar2 = *(long *)(lVar2 - 8);
    out[1] = lVar2;
    lVar2 = sk_h_0036a908(*(word_t *)(lVar2 + 0x40), 0xd560);
    out[2] = lVar2;
    sk_r31_496248(lVar2, arg, table);
    r.lo = (word_t)sk_r31_496558;
    r.hi = lVar2;
    return r;
}

/* FUN_00496558 @ 0x00496558   (est. sk_r31_witness_dtor)
 * Ghidra: void FUN_00496558(undefined8 *param_1)
 * Releases a witness object: calls the stored release fn on param_1[2] with
 * param_1[0], then releases the object itself.
 * Confidence: low */
void sk_r31_496558(word_t *w)
{
    word_t uVar1 = w[2];

    (*(void (**)(word_t, word_t))(w[1] + 8))(uVar1, w[0]);
    sk_h_00012568(uVar1);
}

/* FUN_004965a8 @ 0x004965a8   (est. sk_r31_metadata_box_a)
 * Ghidra: void FUN_004965a8(void)
 * Builds a metadata box and stores it to the register-global out pointer
 * (unaff_x19). out is an explicit parameter here.
 * Confidence: low
 * Notes: unaff_x19 = *out. */
void sk_r31_4965a8(word_t *out)
{
    sk_h_00351124();
    *out = sk_r31_4961e8(0, 0);
}

/* FUN_004965d0 @ 0x004965d0   (est. sk_r31_metadata_box_b)
 * Ghidra: void FUN_004965d0(void)
 * Like FUN_004965a8 with a different builder (FUN_00352b20).
 * Confidence: low
 * Notes: unaff_x19 = *out. */
void sk_r31_4965d0(word_t *out)
{
    sk_h_00352b20();
    *out = sk_r31_4961e8(0, 0);
}

/* FUN_004965f8 @ 0x004965f8   (est. sk_r31_field_store_metadata)
 * Ghidra: void FUN_004965f8(long param_1, undefined8 param_2)
 * Stores a metadata value at a computed field offset (param_1 + iVar1) of an
 * object. Uses register globals extraout_x8/x16 for an indirect metadata
 * call; offset computed from a record at FUN_0031090c()+0x24.
 * Confidence: low
 * Notes: register globals extraout_x8/x16 unresolvable. */
void sk_r31_4965f8(long obj, word_t value)
{
    int iVar1;
    long lVar2;
    word_t uVar3;

    sk_h_000a6f88();
    sk_h_003504e8(0, 0, 0x6879c8);   /* &DAT_006879c8 string/metadata */
    lVar2 = sk_h_0031090c();
    iVar1 = *(int *)(lVar2 + 0x24);
    sk_h_004ab574();
    uVar3 = sk_h_00495c48(value);
    sk_h_0007c1c4();
    *(word_t *)(obj + iVar1) = uVar3;
}

/* FUN_004966dc @ 0x004966dc   (est. sk_r31_epoch_state_new)
 * Ghidra: void FUN_004966dc(void)
 * Builds an epoch/state object: allocates 0x30 bytes (tag 0xa68c), stores a
 * counter, seeds from FUN_004a30ec, wires a callback FUN_00496764, and
 * returns the new object via a register global. Decompiled as void but
 * FUN_0049685c uses its (object, cb) return, so it returns the object word.
 * Confidence: low
 * Notes: unaff_x21/x22/x23/x30 register globals. */
word_t sk_r31_4966dc(word_t arg, word_t val)
{
    long lVar1;
    sk_r31_pair_t auVar2;

    sk_h_00084220();
    sk_h_00349a18();
    lVar1 = sk_h_0036a908(0x30, 0xa68c);
    *(word_t *)(lVar1 + 0x20) = val;
    auVar2 = sk_h_004a30ec();
    sk_h_000dbd0c(auVar2.lo, auVar2.lo, auVar2.hi, 0);
    auVar2 = sk_h_00084220();
    *(long *)(lVar1 + 0x28) = auVar2.lo;
    sk_h_00084234((word_t)sk_r31_496764, auVar2.hi, 0);
    return lVar1;
}

/* FUN_00496764 @ 0x00496764   (est. sk_r31_epoch_state_release)
 * Ghidra: void FUN_00496764(long *param_1)
 * Releases an epoch-state object: releases the object at param_1[0]+0x28 and
 * then the object itself.
 * Confidence: low */
void sk_r31_496764(long *state)
{
    long lVar1 = *state;

    sk_h_0035354c(*(word_t *)(lVar1 + 0x28));
    sk_h_00012568(lVar1);
}

/* FUN_004967a0 @ 0x004967a0   (est. sk_r31_metadata_emit2)
 * Ghidra: void FUN_004967a0(void)
 * Metadata emission using register globals (in_x3, unaff_x19, extraout_x8,
 * extraout_x16). Reads a tagged value from a register-derived address, seeds
 * a metadata buffer, releases type words, and invokes a stored callback.
 * Confidence: low
 * Notes: register globals unresolvable; in_x3 holds a tagged pointer. */
void sk_r31_4967a0(void)
{
    word_t uVar3;
    word_t uVar2;
    sk_r31_pair_t auVar4;
    sk_r31_pair_t auVar5;

    sk_h_000867ec();
    uVar3 = *(word_t *)((0 & 0xfffffffffffffffe) - 8);
    uVar2 = 0;   /* unaff_x19+0x10 */
    sk_h_003504a0(sk_h_004a30ec().lo, (word_t *)&auVar4);
    auVar4 = sk_h_00084220();
    sk_h_00027754(uVar3);
    sk_h_00027754();
    auVar5 = sk_h_004aa5dc();
    sk_h_00377824(auVar5.lo, auVar5.hi, uVar2);
    sk_h_00349530();
    sk_h_0035847c(auVar4.hi);
}

/* FUN_0049685c @ 0x0049685c   (est. sk_r31_epoch_builder)
 * Ghidra: code * FUN_0049685c(void)
 * Builds an epoch object (0x28 bytes, tag 0xc413), initializes it with
 * FUN_004966dc, and returns a fixed entry-point (FUN_002cfc5c).
 * Confidence: low
 * Notes: unaff_x22/x23 register globals. */
void *sk_r31_49685c(void)
{
    long lVar1;
    word_t uVar2;

    sk_h_00349a18();
    lVar1 = sk_h_0036a908(0x28, 0xc413);
    uVar2 = sk_r31_4966dc(lVar1, 0);
    *(word_t *)(lVar1 + 0x20) = uVar2;
    return (void *)sk_h_002cfc5c;
}

/* FUN_004968d0 @ 0x004968d0   (est. sk_r31_pair_store)
 * Ghidra: void FUN_004968d0(undefined8, undefined8 *param_2)
 * Copies the {lo,hi} pair *param_2 to locals and forwards to FUN_004968fc.
 * Confidence: low */
void sk_r31_4968d0(word_t a, word_t *pair)
{
    word_t local_20 = pair[0];
    word_t uStack_18 = pair[1];

    sk_r31_4968fc(a, local_20, uStack_18, 0);
}

/* FUN_004968fc @ 0x004968fc   (est. sk_r31_cap_builder)
 * Ghidra: void FUN_004968fc(undefined8, undefined8, undefined8, undefined8)
 * Builds a capability/metadata record: allocates two objects through the
 * type store, then invokes their constructors. Has an unrecoverable
 * jumptable at 0x496a34.
 * Confidence: low
 * Notes: "Could not recover jumptable at 0x00496a34"; DAT_0060e208/DAT_0060e230,
 * LAB_0060e218 metadata. */
void sk_r31_4968fc(word_t a, word_t b, word_t c, word_t d)
{
    word_t uVar1;
    long lVar2;
    word_t uVar3;
    long lVar4;

    uVar1 = sk_h_00027754(d);
    lVar2 = sk_h_0031b080(0, c, uVar1);
    sk_h_00257020();
    uVar3 = sk_h_00377824(0xff, uVar1, c, &sk_d_0060e208, &sk_d_0060e230);
    uVar1 = sk_h_00377bec(uVar1, c, uVar3, &sk_d_0060e208, &sk_d_0060e218);
    lVar4 = sk_h_00310e08(0, uVar3, uVar1);
    (*(void (**)(word_t, long))(*(long *)(lVar4 - 8) + 8))(b, lVar4);
    (*(void (**)(word_t, long))(*(long *)(lVar2 - 8) + 8))(a, lVar2);
}

/* FUN_00496b2c @ 0x00496b2c   (est. sk_r31_cap_store)
 * Ghidra: void FUN_00496b2c(void)
 * Capability-record store using register globals. Reads a descriptor from
 * FUN_00084220, and depending on a tag bit either copies fields directly or
 * rebuilds via a helper; releases both stored words and the descriptor.
 * Confidence: low
 * Notes: register globals extraout_x8/x9/unaff_x30. */
void sk_r31_496b2c(void)
{
    sk_r31_pair_t auVar5;
    long lVar4;
    word_t uVar1;
    word_t uVar2;

    auVar5 = sk_h_00084220();
    lVar4 = *auVar5.lo;
    uVar1 = *(word_t *)(lVar4 + 0x38);
    uVar2 = *(word_t *)(lVar4 + 0x40);
    if ((auVar5.hi & 1) == 0) {
        sk_h_003510b8(auVar5.lo, auVar5.hi, *(word_t *)(lVar4 + 0x18),
                      *(word_t *)(lVar4 + 0x20));
        sk_r31_4968fc(0, 0, 0, 0);
    } else {
        long lVar3 = *(long *)(lVar4 + 0x30);
        sk_h_0034d3d4();
        sk_h_00084180();
        sk_h_00351aec();
        sk_r31_4968fc(0, 0, 0, 0);
        sk_h_000e15d8(*(word_t *)(lVar3 + 8));
    }
    sk_h_00012568(uVar2);
    sk_h_00012568(uVar1);
    sk_h_00084234(lVar4, 0);
    sk_h_00012568();
}

/* FUN_00496bd4 @ 0x00496bd4   (est. sk_r31_cap_builder_a)
 * Ghidra: void FUN_00496bd4(void)
 * Two helper calls building a capability value.
 * Confidence: low */
void sk_r31_496bd4(void)
{
    sk_h_003580e4();
    sk_h_003468a4();
}

/* FUN_00496bd8 @ 0x00496bd8   (est. sk_r31_cap_builder_b)
 * Ghidra: void FUN_00496bd8(void)
 * Identical to FUN_00496bd4.
 * Confidence: low */
void sk_r31_496bd8(void)
{
    sk_h_003580e4();
    sk_h_003468a4();
}

/* FUN_00496bf0 @ 0x00496bf0   (est. sk_r31_generic_conformance_fetch)
 * Ghidra: undefined8 FUN_00496bf0(undefined8, undefined8, undefined8)
 * Fetches a generic-conformance value through the witness table param_3,
 * seeding a metadata buffer via FUN_00350b54 and passing unaff_x21+0x10.
 * Confidence: low
 * Notes: unaff_x21 register global. */
word_t sk_r31_496bf0(word_t a, word_t b, word_t table)
{
    word_t local_40 = sk_h_00350b54();
    word_t local_38;
    void (*witness_fn)(word_t *, word_t *, word_t) =
        (void *)sk_h_0031e104(table);

    witness_fn(&local_38, &local_40, 0);
    return local_38;
}

/* FUN_00496c4c @ 0x00496c4c   (est. sk_r31_conformance_store)
 * Ghidra: void FUN_00496c4c(undefined8 *param_1, undefined8 *param_2, undefined8, ulong)
 * Stores the conformance fetched from *param_2 into *param_1.
 * Confidence: low */
void sk_r31_496c4c(word_t *out, word_t *src, word_t arg, ulong tag)
{
    *out = sk_r31_496bf0(*src, arg, *(word_t *)((tag & 0xfffffffffffffffe) - 8));
}

/* FUN_00496c80 @ 0x00496c80   (est. sk_r31_conformance_refresh)
 * Ghidra: void FUN_00496c80(undefined8 *param_1, undefined8, ulong)
 * Re-fetches and stores the conformance for the value *param_1.
 * Confidence: low */
void sk_r31_496c80(word_t *slot, word_t arg, ulong tag)
{
    *slot = sk_r31_496bf0(*slot, arg, *(word_t *)((tag & 0xfffffffffffffffe) - 8));
}

/* FUN_00496cb4 @ 0x00496cb4   (est. sk_r31_metadata_box_c)
 * Ghidra: void FUN_00496cb4(void)
 * Stores a metadata box (from FUN_00496354) to unaff_x19.
 * Confidence: low
 * Notes: unaff_x19 = *out. */
void sk_r31_496cb4(void)
{
    word_t *out = 0;   /* unaff_x19 */
    sk_h_00351124();
    *out = sk_r31_496354(0, 0, 0);
}

/* FUN_00496cdc @ 0x00496cdc   (est. sk_r31_tagged_witness_store)
 * Ghidra: void FUN_00496cdc(undefined8, undefined8, undefined8 *param_3)
 * Stores a tagged witness value (from FUN_00495bcc) into unaff_x19 along
 * with a tag byte.
 * Confidence: low
 * Notes: unaff_x19 = *out register global. */
void sk_r31_496cdc(word_t a, word_t b, word_t *param_3)
{
    word_t *out = 0;   /* unaff_x19 */
    sk_h_00351124();
    *out = sk_h_00495bcc(0, 0, *param_3);
}

/* FUN_00496d18 @ 0x00496d18   (est. sk_r31_log_emit)
 * Ghidra: void FUN_00496d18(undefined8, undefined8, undefined8, undefined8, undefined8)
 * Emits a log/metadata record. Uses register globals extraout_x8/x16 and an
 * indirect call to a stored routine; builds a string and forwards it to a
 * witness function. Contains an unusual inlined opcode at SUB_54ffff60f100041f.
 * Confidence: low
 * Notes: register globals extraout_x8/x16; SUB_54ffff60f100041f artifact. */
void sk_r31_496d18(word_t a, word_t b, word_t c, word_t d, word_t e)
{
    sk_r31_pair_t auVar3;
    word_t uVar2;

    sk_h_0007c028();
    sk_h_000aa4ec();
    uVar2 = sk_h_004ac2ac();
    sk_h_00027754(e);
    uVar2 = sk_h_00027754();
    sk_h_00407eac(uVar2, uVar2);
    sk_h_00377824(0xff, 0, b);
    sk_h_00352efc();
    uVar2 = sk_h_00310d34();
    auVar3 = sk_h_00084174(0);
    sk_h_0035847c(auVar3.hi);
}
