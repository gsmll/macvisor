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
#include <string.h>

#include "sk_internal.h"

/* 16-byte (two-word) result used by the return-by-value helpers below. */
typedef struct sk_r31_pair { word_t lo, hi; } sk_r31_pair_t;

/* cL4 Swift-runtime scalar aliases. */
typedef unsigned char byte;
typedef unsigned int uint;
typedef unsigned long ulong;

/* SoftwareBreakpoint(1, addr) — a trap/fault at the given binary address. */
#define SK_TRAP(a) __builtin_trap()

/* Unsigned subtract-with-borrow / add-with-carry detection used by the
 * RangeSet overflow checks (Ghidra SBORROW8/SCARRY8). */
#define SBORROW8(a, b) ((ulong)(a) < (ulong)(b))
#define SCARRY8(a, b)  ((ulong)((a) + (b)) < (ulong)(a))

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
extern word_t sk_d_00657bc8;
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
 * trailing parameters, marked with a (reg) note.
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
void sk_r31_497148(byte *src);
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
    uVar2 = sk_r31_49648c((long *)lVar1, 0, 0).lo;
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
    lVar4 = *(long *)auVar5.lo;
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

/* FUN_00496ef0 @ 0x00496ef0   (est. sk_r31_void_metadata)
 * Ghidra: undefined1[16] FUN_00496ef0(void)
 * Produces the Swift `Void`/empty type metadata {0x23, 0xe100000000000000}
 * after running several runtime setup helpers (release/teardown of a prior
 * context). The literal pair is the tagged Void metadata.
 * Confidence: low
 * Notes: 0x23 word + 0xe1 tag kind. */
sk_r31_pair_t sk_r31_496ef0(void)
{
    sk_r31_pair_t r;

    sk_h_000f4ae8();
    sk_h_00462abc(0);
    sk_h_004ac2c4();
    sk_h_004ab5a4();
    sk_h_002acbb8();
    sk_h_003a25d4();
    r.lo = 0x23;
    r.hi = 0xe100000000000000;
    return r;
}

/* FUN_00496f58 @ 0x00496f58   (est. sk_r31_field_offset_get)
 * Ghidra: uint FUN_00496f58(undefined8, long, ulong)
 * Computes a field/member offset for a type metadata record. When the
 * metadata has a field descriptor (meta+0x10 != 0), reads the field-offset
 * word at meta + count*4 + 0x1c, queries the kind via FUN_00496fec, and
 * composes an access-flags word (containment/presence bits, low byte of the
 * value, and the record kind). Trap-fails if no field descriptor exists.
 * Confidence: medium
 * Notes: SoftwareBreakpoint(1,0x496fec) on empty descriptor. */
word_t sk_r31_496f58(word_t value, long meta, ulong flags)
{
    uint uVar1;
    word_t uVar3;
    uint uVar4;
    uint uVar5;

    if (*(long *)(meta + 0x10) != 0) {
        uVar1 = *(uint *)(meta + *(long *)(meta + 0x10) * 4 + 0x1c);
        uVar3 = sk_r31_496fec(meta, value);
        sk_h_0036b118(meta);
        uVar4 = 0x1000000;
        if ((flags & 1) == 0) {
            uVar4 = 0;
        }
        uVar5 = 0x10000;
        if ((uVar3 & 1) == 0) {
            uVar5 = 0;
        }
        return (word_t)((uVar4 | (uint)value & 0xff | uVar5 | uVar1 >> 8 & 0x100) ^ 0x100);
    }
    SK_TRAP(0x496fec);
    return 0;
}

/* FUN_00496fec @ 0x00496fec   (est. sk_r31_kind_field_offset)
 * Ghidra: undefined8 FUN_00496fec(long param_1, uint param_2)
 * Returns the reserved field offset for a type-metadata kind. Kinds 3-6
 * read a 32-bit word out of the metadata's field-offset array
 * (meta + count*4 + 0x1c) via the record-offset helper FUN_00354998; kind 7
 * returns a fixed offset; any other kind (0-2) also reads the field-offset
 * array. Trap-fails when the array is empty.
 * Confidence: medium
 * Notes: SoftwareBreakpoint at 0x48aa20 (kinds 3-6) and 0x48aa04 (others). */
word_t sk_r31_496fec(long meta, uint kind)
{
    word_t uVar2;

    if (5 < (kind & 0xff) - 2) {
        return 0;
    }
    switch (kind & 0xff) {
    case 3:
    case 4:
    case 5:
    case 6:
        if (*(long *)(meta + 0x10) == 0) {
            SK_TRAP(0x48aa20);
        }
        uVar2 = sk_h_00354998(*(uint *)(meta + *(long *)(meta + 0x10) * 4 + 0x1c));
        return uVar2;
    case 7:
        return sk_h_00476e74();
    }
    if (*(long *)(meta + 0x10) == 0) {
        SK_TRAP(0x48aa04);
    }
    uVar2 = sk_h_00354998(*(uint *)(meta + *(long *)(meta + 0x10) * 4 + 0x1c));
    return uVar2;
}

/* FUN_00497088 @ 0x00497088   (est. sk_r31_diag_flags_write)
 * Ghidra: void FUN_00497088(undefined8, uint)
 * Writes a 32-bit diagnostic/flags value to the serial/debug stream: two
 * byte writes (low byte, next byte) via FUN_002298d4 and two bit writes
 * (bit 16, bit 24) via FUN_00229a3c.
 * Confidence: medium
 * Notes: FUN_002298d4/FUN_00229a3c are the cL4 debug-output primitives. */
void sk_r31_497088(word_t ctx, uint v)
{
    sk_h_002298d4(v & 0xff);
    sk_h_002298d4(v >> 8 & 0xff);
    sk_h_00229a3c(v >> 0x10 & 1);
    sk_h_00229a3c(v >> 0x18 & 1);
}

/* FUN_004970cc @ 0x004970cc   (est. sk_r31_diag_flags_flush)
 * Ghidra: void FUN_004970cc(uint)
 * Emits a masked 32-bit diagnostic value (mask 0x101ffff) to the debug
 * stream and flushes it.
 * Confidence: low
 * Notes: 72-byte stack scratch buffer; FUN_001a8564 flushes. */
void sk_r31_4970cc(uint v)
{
    word_t buf[9];

    sk_h_004080b0();
    sk_r31_497088((word_t)buf, v & 0x101ffff);
    sk_h_001a8564();
}

/* FUN_00497110 @ 0x00497110   (est. sk_r31_diag_flags_state_a)
 * Ghidra: void FUN_00497110(void)
 * Reads a state word (extraout_w8|extraout_w9 from register globals) and
 * emits it. Register globals unresolvable.
 * Confidence: low
 * Notes: extraout_w8/w9 register globals dropped. */
void sk_r31_497110(void)
{
    sk_h_004ab4b4();
    sk_r31_4970cc(0);
}

/* FUN_0049712c @ 0x0049712c   (est. sk_r31_diag_flags_state_b)
 * Ghidra: void FUN_0049712c(void)
 * Reads a state word and writes it as a flags value.
 * Confidence: low
 * Notes: extraout_w8/w9 register globals dropped. */
void sk_r31_49712c(void)
{
    word_t uVar1 = sk_h_004ab4b4();
    sk_r31_497088(uVar1, 0);
}

/* FUN_00497148 @ 0x00497148   (est. sk_r31_diag_byte_flags)
 * Ghidra: void FUN_00497148(void)
 * Reads four bytes from a register-held buffer (unaff_x20) and emits them
 * as a 32-bit diagnostic flags word (each byte a set bit when non-zero).
 * Confidence: low
 * Notes: unaff_x20 = byte buffer. */
void sk_r31_497148(byte *src)
{
    byte b1 = src[0], b2 = src[1], b3 = src[2], b4 = src[3];
    word_t buf[9];
    uint uVar5;
    uint uVar6;

    sk_h_001a84f4((word_t)buf, 0);
    uVar5 = 0x1000000;
    if (b4 == 0) {
        uVar5 = 0;
    }
    uVar6 = 0x10000;
    if (b3 == 0) {
        uVar6 = 0;
    }
    sk_r31_497088((word_t)buf, uVar6 | uVar5 | (uint)b2 << 8 | (uint)b1);
    sk_h_001a8564();
}

/* FUN_00497224 @ 0x00497224   (est. sk_r31_type_metadata_names)
 * Ghidra: undefined1[16] FUN_00497224(undefined1)
 * Returns the type-metadata {word, tag} pairs for the Swift existential/
 * Any metatypes: 0 -> `<any>`, 1 -> `<any some AnyObject>`, 2 -> `<id>`,
 * 3-5 -> tagged opaque metadata singletons, 6 -> `<which>...`, 7 -> `<word>`.
 * The low byte of each returned hi word is the value-kind tag.
 * Confidence: medium
 * Notes: string words are little-endian Swift String encodings; the
 * 0x5e20b0/d0/f0 addresses are opaque metadata singletons. */
sk_r31_pair_t sk_r31_497224(byte which)
{
    word_t uVar1 = 0x3e796e613c;             /* "<any>" */
    word_t uVar2 = 0xe500000000000000;
    sk_r31_pair_t out;

    switch (which) {
    case 1:
        out.lo = 0x61726720796e613c;         /* "<any gra" */
        out.hi = 0xee003e656d656870;         /* "heme>" kind ee */
        return out;
    case 2:
        out.lo = 0x3e74696769643c;           /* "<digit>" */
        out.hi = 0xe700000000000000;
        return out;
    case 3:
        out.lo = 0xd000000000000017;
        out.hi = 0x80000000005e20f0;         /* DAT_005e20f0 */
        return out;
    case 4:
        out.lo = 0xd000000000000012;
        out.hi = 0x80000000005e20d0;         /* DAT_005e20d0 */
        return out;
    case 5:
        out.lo = 0xd000000000000013;
        out.hi = 0x80000000005e20b0;         /* DAT_005e20b0 */
        return out;
    case 6:
        out.lo = 0x707365746968773c;         /* "<white sp" */
        out.hi = 0xec0000003e656361;         /* "ace>" kind ec */
        return out;
    case 7:
        uVar2 = 0xe600000000000000;
        uVar1 = 0x3e64726f773c;              /* "<word>" */
        break;
    }
    out.lo = uVar1;
    out.hi = uVar2;
    return out;
}

/* FUN_00497354 @ 0x00497354   (est. sk_r31_not_metadata)
 * Ghidra: undefined1[16] FUN_00497354(ulong)
 * Builds the Swift `~`/`not` type metadata for a kind: if the high
 * presence bit (0x1000000) is set the display word is "not " (0x20746f6e)
 * with tag 0xe4, else the empty word with tag 0xe0. Emits the underlying
 * kind metadata via FUN_00497224 and returns the {0, 0xe000000000000000}
 * pair.
 * Confidence: low
 * Notes: FUN_004abcf8/FUN_002acbb8/FUN_003a25d4 emit helpers. */
sk_r31_pair_t sk_r31_497354(ulong kind)
{
    bool bVar3 = (kind & 0x1000000) != 0;
    word_t uVar1 = 0;
    word_t uVar2 = 0xe000000000000000;

    if (bVar3) {
        uVar1 = 0x20746f6e;                  /* "not " */
        uVar2 = 0xe400000000000000;
    }
    sk_h_004abcf8(uVar1);
    sk_h_002acbb8();
    sk_h_003a25d4(uVar2);
    sk_r31_497224(kind);
    sk_h_00465294();
    sk_h_003a25d4(kind);
    return (sk_r31_pair_t){ .lo = 0, .hi = 0xe000000000000000 };
}

/* FUN_004973cc @ 0x004973cc   (est. sk_r31_not_metadata_a)
 * Ghidra: void FUN_004973cc(void)
 * Emits the `not` metadata for a register-held kind word.
 * Confidence: low
 * Notes: extraout_w8/w9 register globals dropped. */
void sk_r31_4973cc(void)
{
    sk_h_004ab4b4();
    sk_r31_497354(0);
}

/* FUN_004973e8 @ 0x004973e8   (est. sk_r31_pair_apply)
 * Ghidra: void FUN_004973e8(undefined8*, undefined8*, undefined8*, code*)
 * Applies a 4-word function to the two {lo,hi} pairs at *param_2 and
 * *param_3 and stores the result to *param_1 (plus a tag byte from the
 * return's carry register, dropped by the decompiler).
 * Confidence: low
 * Notes: extraout_w1 tag byte not captured. */
void sk_r31_4973e8(word_t *out, word_t *a, word_t *b, void *fn)
{
    word_t (*apply)(word_t, word_t, word_t, word_t) = (word_t (*)(word_t, word_t, word_t, word_t))fn;

    *out = apply(a[0], a[1], b[0], b[1]);
}

/* FUN_00497430 @ 0x00497430   (est. sk_r31_invert_str)
 * Ghidra: void FUN_00497430(undefined8, ulong)
 * Emits a string with the "invert." marker (0x65747265766e692e little-endian
 * string "invert." + tag 0xe9) and, when the flag bit is set, an extra
 * marker.
 * Confidence: low
 * Notes: FUN_0044ca08/FUN_0044ca2c/FUN_0044ca60 emit helpers. */
void sk_r31_497430(word_t ctx, ulong flag)
{
    sk_h_0044ca60();
    sk_h_0044ca08(0x65747265766e692e, 0xe900000000000064); /* "invert." */
    if ((flag & 1) != 0) {
        sk_h_0044ca2c();
    }
}

/* FUN_0049747c @ 0x0049747c   (est. sk_r31_length_field)
 * Ghidra: long FUN_0049747c(ulong)
 * Unboxes a tagged pointer (clear bit 0, load the target) and returns the
 * end address of a length-prefixed region: (ptr+8) + *((int*)ptr+8).
 * Confidence: medium */
long sk_r31_49747c(ulong p)
{
    if ((p & 1) != 0) {
        p = *(ulong *)(p & 0xfffffffffffffffe);
    }
    return (long)(p + 8) + (long)*(int *)(p + 8);
}

/* FUN_004974ac @ 0x004974ac   (est. sk_r31_fatal_abort)
 * Ghidra: void FUN_004974ac(void)
 * Calls the fatal abort helper.
 * Confidence: low */
void sk_r31_4974ac(void)
{
    sk_h_00021480();
}

/* FUN_004974c4 @ 0x004974c4   (est. sk_r31_identity_ret)
 * Ghidra: undefined8 FUN_004974c4(undefined8)
 * Runs a setup helper and returns its argument unchanged.
 * Confidence: low */
word_t sk_r31_4974c4(word_t v)
{
    sk_h_004a29d4();
    return v;
}

/* FUN_004974ec @ 0x004974ec   (est. sk_r31_fatal_abort_b)
 * Ghidra: void FUN_004974ec(void)
 * Fatal abort.
 * Confidence: low */
void sk_r31_4974ec(void)
{
    sk_h_00021480();
}

/* FUN_00497504 @ 0x00497504   (est. sk_r31_fatal_abort_c)
 * Ghidra: void FUN_00497504(void)
 * Fatal abort.
 * Confidence: low */
void sk_r31_497504(void)
{
    sk_h_00021480();
}

/* Tagged 16-byte value accessors: lo = 8-byte word, low byte of hi = the
 * value-kind tag; bytes 9-15 are normally zero. */
#define SW_TAG(p)  ((word_t)((p).hi & 0xff))
#define SW_TAG4(p) ((word_t)((p).hi & 0xffffffff))

/* FUN_0049751c @ 0x0049751c   (est. sk_r31_range_set_merge)
 * Ghidra: undefined * FUN_0049751c(long param_1)
 * RangeSet-style merge/rebuild of a sorted, non-overlapping set of half-open
 * ranges. param_1 is a 0x59-byte struct: ten 8-byte fields (two "collections"
 * at +0x40/+0x48 being merged, a current start word and shift/limit words in
 * the lower fields) followed by a 9-byte tagged word at +0x50 (a range cursor
 * with a done tag byte at +0x58). It walks both collections with the
 * 16-byte-range helpers FUN_002b3cf8/FUN_002b439c/FUN_002b3f40 (advance,
 * peek, and split-range), merging overlapping ranges (comparisons on
 * word>>0xe) into a freshly-grown output buffer (empty sentinel
 * DAT_00657778; growth via FUN_0036a940 + thunk_FUN_000126e8 malloc_size).
 * Trap-fails on any index overflow/underflow.
 * Confidence: low
 * Notes: input-struct field offsets per Ghidra field order; FUN_004a4b60
 * fills the local work pair; DAT_00657798 is a secondary cursor table. */
word_t sk_r31_49751c(long param_1)
{
    word_t local_c8, uStack_c0, local_b8, uStack_b0, local_a8, uStack_a0;
    word_t local_98, uStack_90, local_88, local_80;
    word_t local_128, uStack_120, local_110, local_108;
    byte local_118;
    word_t local_78;
    byte local_70;
    sk_r31_pair_t auVar29, auVar31, auVar30, auVar29b;
    long lVar25 = 0;
    word_t *puVar27;
    word_t *puVar28 = &sk_d_00657778;
    word_t *puVar17;
    word_t uVar13, uVar23, uVar16, uVar22, uVar24, uVar20, uVar21;
    word_t uVar3, uVar5, uVar6, uVar7, uVar8;
    long lVar10, lVar9, lVar26, lVar4, lVar2;
    word_t uVar14, uVar15, uVar18, uVar19;
    long lVar25_2;

    uint8_t inbuf[0x59];

    auVar29.lo = *(word_t *)(param_1 + 0x50);
    auVar29.hi = (word_t)*(byte *)(param_1 + 0x58);   /* 9-byte tagged cursor */
    /* FUN_00117cc4(&local_c8, param_1, 0x59): copy the 0x59-byte input struct.
     * Field offsets per the Ghidra stack layout (10 words then a 9-byte tag). */
    memcpy(inbuf, (void *)param_1, 0x59);
    local_c8 = *(word_t *)(inbuf + 0x00);
    uStack_c0 = *(word_t *)(inbuf + 0x08);
    local_b8 = *(word_t *)(inbuf + 0x10);
    uStack_b0 = *(word_t *)(inbuf + 0x18);
    local_a8 = *(word_t *)(inbuf + 0x20);
    uStack_a0 = *(word_t *)(inbuf + 0x28);
    local_98 = *(word_t *)(inbuf + 0x30);
    uStack_90 = *(word_t *)(inbuf + 0x38);
    local_88 = *(word_t *)(inbuf + 0x40);
    local_80 = *(word_t *)(inbuf + 0x48);
    sk_h_004a4b60(param_1, (word_t *)&local_128);
    lVar25 = 0;
    puVar27 = &sk_d_00657798;
    puVar28 = &sk_d_00657778;

LAB_00497578:
    lVar10 = local_80;
    lVar9 = local_88;
    uVar8 = uStack_90;
    uVar7 = local_98;
    uVar6 = uStack_a0;
    uVar3 = local_a8;
    uVar5 = uStack_b0;
    uVar16 = local_b8;
    uVar24 = uStack_c0;
    uVar22 = local_c8;
    uVar23 = auVar29.lo;
    if (SW_TAG(auVar29) != 1) {
        uVar13 = uVar23;
        if (local_80 == 0) {
            bool bVar12 = 0x3fff < (uStack_c0 ^ uVar23);
            if (bVar12) {
                uVar16 = sk_h_002b3b50(uVar23, local_c8, uStack_c0, local_b8, uStack_b0);
            } else {
                uVar16 = 0;
            }
            auVar29.hi = (auVar29.hi & 0xffffffffffffff00) | (word_t)(!bVar12);
            auVar29.lo = uVar16;
            auVar29.hi &= 0xff;
            goto LAB_0049784c;
        }
        if (*(long *)(local_88 + 0x10) != 0) {
            if (SBORROW8(local_80, 1)) {
                SK_TRAP(0x497988);
            }
            uVar20 = local_a8 >> 0xe;
            uVar21 = local_c8 >> 0xe;
            uVar14 = uVar6;
            lVar26 = lVar10;
            do {
                while (true) {
                    lVar26 = lVar26 - 1;
                    uVar13 = sk_h_002b3cf8(uVar13, uVar22, uVar24, uVar16, uVar5);
                    uVar14 = sk_h_002b3cf8(uVar14, uVar3, uVar6, uVar7, uVar8);
                    if (uVar20 <= uVar14 >> 0xe) break;
LAB_00497710:
                    auVar29b = sk_h_002b439c(uVar13, uVar22, uVar24, uVar16, uVar5);
                    auVar31 = sk_h_0046f298(auVar29b.lo, auVar29b.hi, lVar9);
                    sk_h_003a25d4(auVar29b.hi);
                    lVar2 = 0;
                    if (SW_TAG(auVar31) != 1) {
                        lVar2 = auVar31.lo;
                    }
                    lVar4 = lVar26 - lVar2;
                    if (SBORROW8(lVar26, lVar2)) {
                        SK_TRAP(0x497984);
                    }
                    if (lVar4 < 2) {
                        lVar4 = 1;
                    }
                    auVar31 = sk_h_002b3f40(uVar23, lVar4, uVar24, uVar22, uVar24, uVar16, uVar5);
                    uVar13 = auVar31.lo;
                    uVar14 = uVar6;
                    lVar26 = lVar10;
                    uVar23 = uVar13;
                    if (SW_TAG(auVar31) == 1) {
                        local_70 = (byte)auVar31.hi;
                        local_78 = uVar13;
                        goto LAB_0049792c;
                    }
                }
                auVar29b = sk_h_002b439c(uVar14, uVar3, uVar6, uVar7, uVar8);
                uVar18 = auVar29b.hi;
                auVar30 = sk_h_002b439c(uVar13, uVar22, uVar24, uVar16, uVar5);
                uVar19 = auVar30.hi;
                if (auVar29b.lo == auVar30.lo && auVar29b.hi == auVar30.hi) {
                    sk_h_003a25d4(uVar18);
                    sk_h_003a25d4(uVar19);
                } else {
                    uVar15 = sk_h_002a0cf8(auVar29b.lo, uVar18, auVar30.lo, uVar19, 0);
                    sk_h_003a25d4(uVar18);
                    sk_h_003a25d4(uVar19);
                    if ((uVar15 & 1) == 0) goto LAB_00497710;
                }
                if (SBORROW8(lVar26, 1)) {
                    SK_TRAP(0x497978);
                }
                if (uVar14 >> 0xe == uVar20) goto LAB_004977a8;
                if (uVar13 >> 0xe <= uVar21) {
                    SK_TRAP(0x49797c);
                }
            } while (true);
        }
        sk_h_0046ece8((word_t *)&local_128, local_c8, uStack_c0, local_b8, uStack_b0, uVar23);
        auVar29.hi = (auVar29.hi & 0xffffffffffffff00) | (word_t)local_108;
        auVar29.lo = local_110;
        auVar29.hi &= 0xff;
        local_78 = local_110;
        local_70 = local_108;
        uVar23 = uStack_120;
        uVar13 = local_128;
        if (local_118 != 1) goto joined_r0x0049785c;
    }
LAB_0049792c:
    sk_r31_497994((word_t)&local_c8);
    if (1 < *(ulong *)(puVar28 + 0x18)) {
        uVar23 = *(ulong *)(puVar28 + 0x18) >> 1;
        if (SBORROW8(uVar23, lVar25)) {
            SK_TRAP(0x497994);
        }
        *(ulong *)(puVar28 + 0x10) = uVar23 - lVar25;
    }
    return (word_t)puVar28;

LAB_004977a8:
    if (uVar23 >> 0xe < uVar13 >> 0xe) {
        SK_TRAP(0x49798c);
    }
    auVar29 = sk_h_002b3f40(uVar23, lVar10, uVar24, uVar22, uVar24, uVar16, uVar5);

LAB_0049784c:
    local_78 = auVar29.lo;
    local_70 = (byte)auVar29.hi;

joined_r0x0049785c:
    puVar17 = puVar28;
    if (lVar25 == 0) {
        word_t uVar22b;
        word_t uVar16b;
        word_t *puVar1;
        long lVar25_new;

        local_78 = auVar29.lo;
        uVar22b = *(ulong *)(puVar28 + 0x18);
        if ((long)((uVar22b >> 1) + 0x4000000000000000) < 0) {
            SK_TRAP(0x497990);
        }
        uVar24 = uVar22b & 0xfffffffffffffffe;
        if ((long)uVar22b < 2) {
            uVar24 = 1;
        }
        uVar16b = sk_h_00002534((word_t)&sk_d_00657e80, (word_t)&sk_d_005a5600);
        puVar17 = (word_t *)sk_h_0036a940(uVar16b, uVar24 * 0x10 + 0x20, 7);
        lVar25_new = sk_h_000126e8();
        uVar3 = (lVar25_new - 0x20) / 0x10;
        *(ulong *)(puVar17 + 0x10) = uVar24;
        *(ulong *)(puVar17 + 0x18) = uVar3 << 1;
        puVar1 = puVar17 + 0x20;
        uVar22b = *(ulong *)(puVar28 + 0x18);
        uVar24 = uVar22b >> 1;
        if (*(long *)(puVar28 + 0x10) != 0) {
            if (puVar17 != puVar28 || puVar28 + 0x20 + uVar24 * 0x10 <= puVar1) {
                sk_h_00117d14((word_t)puVar1, (word_t)(puVar28 + 0x20), uVar24 << 4);
            }
            *(word_t *)(puVar28 + 0x10) = 0;
        }
        puVar27 = (word_t *)(puVar1 + uVar24 * 0x10);
        lVar25 = (uVar3 & 0x7fffffffffffffff) - (uVar22b >> 1);
        sk_h_0036b118((word_t)puVar28);
        puVar28 = puVar17;
        lVar25_2 = lVar25;
    } else {
        lVar25_2 = lVar25;
    }
    bool bVar12 = SBORROW8(lVar25_2, 1);
    lVar25 = lVar25_2 - 1;
    if (bVar12) {
        SK_TRAP(0x497980);
    }
    *puVar27 = uVar13;
    puVar27[1] = uVar23;
    puVar27 = puVar27 + 2;
    puVar28 = puVar17;
    goto LAB_00497578;
}

/* FUN_00497994 @ 0x00497994   (est. sk_r31_identity_ret2)
 * Ghidra: undefined8 FUN_00497994(undefined8)
 * Runs a helper and returns its argument unchanged.
 * Confidence: low */
word_t sk_r31_497994(word_t v)
{
    sk_h_004a1a50();
    return v;
}

/* FUN_004979bc @ 0x004979bc   (est. sk_r31_fatal_abort_d)
 * Ghidra: void FUN_004979bc(void)
 * Fatal abort.
 * Confidence: low */
void sk_r31_4979bc(void)
{
    sk_h_00021480();
}

/* FUN_004979d4 @ 0x004979d4   (est. sk_r31_fatal_abort_e)
 * Ghidra: void FUN_004979d4(void)
 * Fatal abort.
 * Confidence: low */
void sk_r31_4979d4(void)
{
    sk_h_00021480();
}

/* FUN_004979f8 @ 0x004979f8   (est. sk_r31_range_set_merge2)
 * Ghidra: undefined * FUN_004979f8(ulong *param_1)
 * RangeSet-style merge/rebuild (variant of FUN_0049751c) operating on a
 * 0x118-byte struct and emitting 0x20-byte output records. The input
 * carries two start words (uVar25/uVar3), limit words (uVar2/uVar4), a
 * "current" cursor (uVar28), a collection descriptor (local_c8), two
 * out-of-line key arrays (param_1+0x69/+0x71 as tagged 7+1 and 8-byte words),
 * a count (uVar29), and a done byte (bVar6). It walks two sorted range
 * collections with the 16-byte range helpers FUN_002b3cf8/002b439c/002b3f40,
 * resolving duplicate keys via FUN_0006ae9c against the collection's hash
 * array (uVar11+0x38), and appends merged 0x20-byte records into a freshly
 * grown buffer (sentinel DAT_00657778; growth at LAB_0049801c). Trap-fails on
 * any index overflow.
 * Confidence: low
 * Notes: 0x657bc8/0x5a3c70 metadata strings; DAT_00657e78/DAT_005a55f8
 * finalize strings. */
word_t sk_r31_4979f8(ulong *param_1)
{
    word_t uVar25 = param_1[0];
    word_t uVar3 = param_1[1];
    word_t uVar2 = param_1[2];
    word_t uVar4 = param_1[3];
    word_t uStack_100 = param_1[5];
    word_t local_108 = param_1[4];
    word_t uStack_f0 = param_1[7];
    word_t local_f8 = param_1[6];
    word_t uVar28 = param_1[8];
    word_t uVar26 = param_1[9];
    word_t uVar24 = param_1[10];
    word_t uVar5 = param_1[0xb];
    word_t local_c8 = param_1[0xc];
    word_t uStack_c0 = (word_t)param_1[0xd];
    word_t uStack_b7 = *(word_t *)((long)param_1 + 0x71);
    word_t uStack_bf = (word_t)((ulong)*(word_t *)((long)param_1 + 0x69) & 0xffffffffffffff);
    word_t uStack_b8 = (word_t)((ulong)*(word_t *)((long)param_1 + 0x69) >> 0x38);
    word_t uVar29 = param_1[0x10];
    byte bVar6 = (byte)param_1[0x11];
    byte local_6f = 0;
    word_t local_78 = 0;
    word_t uVar31 = uVar3 >> 0xe;
    word_t local_128 = uVar25;
    word_t uStack_120 = uVar3;
    word_t local_118 = uVar2;
    word_t uStack_110 = uVar4;
    word_t local_e8 = uVar28;
    word_t uStack_e0 = uVar26;
    word_t local_d8 = uVar24;
    word_t uStack_d0 = uVar5;
    word_t local_88 = uVar25;
    word_t local_1f8, local_1d0, uVar20, uVar22, uVar33, uVar34;
    word_t uVar11, uVar10, uVar15, uVar17, uVar16, uVar19;
    long lVar8, lVar36, lVar7, lVar23, lVar32 = 0, local_240 = 0;
    word_t local_1b8, uStack_1b0, local_1a0, uStack_120b;
    byte local_1a8, local_198, local_90, local_70;
    word_t local_220, local_98, local_80;
    word_t uVar35 = 0, uVar21;
    byte bVar27, bVar9, bVar6copy;
    byte bVar14;
    sk_r31_pair_t auVar38, auVar39, auVar40, ea;
    word_t *puVar37;
    sk_r31_pair_t *pauVar30;
    word_t *puVar18, *puVar1;
    byte bVar13;

    if (uVar31 < uVar25 >> 0xe) {
        SK_TRAP(0x4981cc);
    }
    local_1f8 = uVar25;
    local_1d0 = uVar3;
    auVar38 = sk_h_002b74c0(uVar25);
    sk_h_004a4ac4((word_t)param_1, &local_1b8, (word_t)&sk_d_00657bc8, (word_t)&sk_d_005a3c70);
    sk_h_0036b270(uVar5);
    ea = sk_h_0046ea44(auVar38.lo, auVar38.hi, local_1f8, local_1d0,
                       uVar28, uVar26, uVar24, uVar5);
    lVar32 = 0;
    local_240 = 0;
    uVar35 = 0;
    local_90 = (byte)local_1d0;
    puVar37 = &sk_d_00657778;
    pauVar30 = (sk_r31_pair_t *)&sk_d_00657798;
    uVar28 = uVar25;
    local_220 = uVar25;
    local_98 = local_1f8;
    local_80 = uVar29;
    local_70 = bVar6;
    bVar27 = bVar6;
    bVar9 = bVar6;

LAB_00497b6c:
    uVar11 = local_c8;
    uVar10 = uStack_d0;
    uVar5 = local_d8;
    uVar26 = uStack_e0;
    uVar24 = local_e8;
    auVar38.hi = local_1d0;
    auVar38.lo = local_1f8;
    uVar20 = uVar25;
    uVar22 = uVar3;
    if (uVar28 >> 0xe != uVar31) {
        if (local_240 < (long)uVar29) {
            lVar8 = (word_t)((uStack_bf << 8) | uStack_c0);   /* CONCAT71 */
            uVar33 = local_e8 >> 0xe;
            uVar34 = uVar28;
LAB_00497c14:
            uVar28 = uVar34;
            local_1f8 = auVar38.lo;
            if (SW_TAG(auVar38) != 1) {
                uVar34 = local_1f8;
                if (lVar8 == 0) {
                    bool bv = 0x3fff < (local_1f8 ^ uVar3);
                    if (bv) {
                        uVar17 = sk_h_002b3b50(local_1f8, uVar25, uVar3, uVar2, uVar4);
                    } else {
                        uVar17 = 0;
                    }
                    auVar38.hi = (auVar38.hi & 0xffffffffffffff00) | (word_t)(!bv);
                    auVar38.lo = uVar17;
                    auVar38.hi &= 0xff;
                    goto LAB_00497ebc;
                }
                if (*(long *)(uVar11 + 0x10) != 0) {
                    uVar15 = uVar26;
                    lVar36 = lVar8;
                    if (SBORROW8(lVar8, 1)) {
                        SK_TRAP(0x4981b4);
                    }
                    do {
                        while (true) {
                            lVar36 = lVar36 - 1;
                            local_1f8 = sk_h_002b3cf8(local_1f8, uVar25, uVar3, uVar2, uVar4);
                            uVar15 = sk_h_002b3cf8(uVar15, uVar24, uVar26, uVar5, uVar10);
                            if (uVar33 <= uVar15 >> 0xe) break;
LAB_00497d48:
                            auVar38 = sk_h_002b439c(local_1f8, uVar25, uVar3, uVar2, uVar4);
                            uVar17 = auVar38.hi;
                            if (*(long *)(uVar11 + 0x10) == 0) {
                                sk_h_003a25d4(uVar17);
                                lVar23 = 0;
                            } else {
                                sk_r31_pair_t hv = sk_h_0006ae9c(auVar38.lo, uVar17);
                                sk_h_003a25d4(uVar17);
                                if ((hv.hi & 1) == 0) {
                                    lVar23 = 0;
                                } else {
                                    lVar23 = *(long *)(*(long *)(uVar11 + 0x38) + hv.lo * 8);
                                }
                            }
                            lVar7 = lVar36 - lVar23;
                            if (SBORROW8(lVar36, lVar23)) {
                                SK_TRAP(0x4981b0);
                            }
                            if (lVar7 < 2) {
                                lVar7 = 1;
                            }
                            auVar40 = sk_h_002b3f40(uVar34, lVar7, uVar3, uVar25, uVar3, uVar2, uVar4);
                            local_1f8 = auVar40.lo;
                            uVar15 = uVar26;
                            lVar36 = lVar8;
                            uVar34 = local_1f8;
                            if (SW_TAG(auVar40) == 1) {
                                uVar21 = 1;
                                local_90 = 1;
                                local_98 = local_1f8;
                                goto LAB_00497fb0;
                            }
                        }
                        auVar38 = sk_h_002b439c(uVar15, uVar24, uVar26, uVar5, uVar10);
                        uVar17 = auVar38.hi;
                        auVar39 = sk_h_002b439c(local_1f8, uVar25, uVar3, uVar2, uVar4);
                        uVar19 = auVar39.hi;
                        if (auVar38.lo == auVar39.lo && auVar38.hi == auVar39.hi) {
                            sk_h_003a25d4(uVar17);
                            sk_h_003a25d4(uVar19);
                        } else {
                            uVar16 = sk_h_002a0cf8(auVar38.lo, uVar17, auVar39.lo, uVar19, 0);
                            sk_h_003a25d4(uVar17);
                            sk_h_003a25d4(uVar19);
                            if ((uVar16 & 1) == 0) goto LAB_00497d48;
                        }
                        if (SBORROW8(lVar36, 1)) {
                            SK_TRAP(0x49813c);
                        }
                        if (uVar15 >> 0xe == uVar33) goto LAB_00497e14;
                        if (local_1f8 >> 0xe <= uVar25 >> 0xe) {
                            SK_TRAP(0x498140);
                        }
                    } while (true);
                }
                sk_h_0046ece8((word_t *)&local_1b8, uVar25, uVar3, uVar2, uVar4, local_1f8);
                auVar38.hi = (auVar38.hi & 0xffffffffffffff00) | (word_t)local_198;
                auVar38.lo = local_1a0;
                auVar38.hi &= 0xff;
                uVar21 = (word_t)local_198;
                local_98 = local_1a0;
                local_90 = local_198;
                uVar34 = uStack_1b0;
                uVar15 = local_1b8;
                local_1f8 = local_1a0;
                if (local_1a8 == 1) goto LAB_00497fb0;
                goto LAB_00497ecc;
            }
            uVar21 = 1;
LAB_00497fb0:
            uVar24 = local_220;
            if ((uVar28 >> 0xe == uVar31 && (bVar27 & 1)) == 1) goto LAB_00498144;
            if (uVar31 < uVar28 >> 0xe) {
                SK_TRAP(0x4981c8);
            }
            local_1d0 = (word_t)uVar21;
            goto LAB_00497fe4;
        }
        if (uVar31 < uVar28 >> 0xe) {
            SK_TRAP(0x4981c4);
        }
        local_1d0 = local_1d0 & 0xffffffff;
LAB_00497fe4:
        auVar38 = sk_h_002b74c0(uVar28, uVar3, uVar25, uVar3, uVar2, uVar4);
        bVar13 = true;
        uVar35 = 1;
        if (lVar32 != 0) goto LAB_00498014;
        goto LAB_0049801c;
    }
    if ((bVar6 & 1) == 0) {
        local_1d0 = local_1d0 & 0xffffffff;
        auVar38 = sk_h_002b74c0(uVar28);
        bVar27 = 0;
        bVar13 = true;
        bVar9 = 0;
        uVar35 = 1;
        if (lVar32 == 0) goto LAB_0049801c;
        bVar9 = 0;
LAB_00498014:
        uVar35 = 1;
        bVar13 = true;
        goto LAB_004980f8;
    }
    local_88 = local_220;
    uVar24 = local_88;
LAB_00498144:
    local_88 = uVar24;
    local_6f = 1;
    goto LAB_00498150;
LAB_00497e14:
    if (uVar34 >> 0xe < local_1f8 >> 0xe) {
        SK_TRAP(0x4981bc);
    }
    auVar38 = sk_h_002b3f40(uVar34, lVar8, uVar3, uVar25, uVar3, uVar2, uVar4);
LAB_00497ebc:
    local_90 = (byte)auVar38.hi;
    uVar15 = local_1f8;
LAB_00497ecc:
    local_220 = uVar34;
    local_1f8 = auVar38.lo;
    bVar27 = 1;
    uVar34 = local_220;
    local_98 = local_1f8;
    if ((bVar9 & ((uVar15 ^ uVar28) < 0x4000)) == 0) goto code_r0x00497eec;
    goto LAB_00497c14;
code_r0x00497eec:
    bVar13 = SCARRY8(local_240, 1);
    local_240 = local_240 + 1;
    if (bVar13) {
        SK_TRAP(0x4981d0);
    }
    if (uVar15 >> 0xe < uVar28 >> 0xe) {
        SK_TRAP(0x4981d4);
    }
    local_1d0 = auVar38.hi & 0xffffffff;
    auVar38 = sk_h_002b74c0(uVar28, uVar15, uVar25, uVar3, uVar2, uVar4);
    bVar13 = false;
    uVar28 = local_220;
    bVar27 = bVar9;
    if (lVar32 == 0) {
        word_t uVar24b, uVar26b;
LAB_0049801c:
        uVar24b = *(ulong *)(puVar37 + 0x18);
        if ((long)((uVar24b >> 1) + 0x4000000000000000) < 0) {
            SK_TRAP(0x4981c0);
        }
        uVar26b = uVar24b & 0xfffffffffffffffe;
        if ((long)uVar24b < 2) {
            uVar26b = 1;
        }
        uVar17 = sk_h_00002534((word_t)&sk_d_0064e118, (word_t)&sk_d_004bedf0);
        puVar18 = (word_t *)sk_h_0036a940(uVar17, uVar26b * 0x20 + 0x20, 7);
        lVar32 = sk_h_000126e8();
        uVar5 = (lVar32 - 0x20) / 0x20;
        *(ulong *)(puVar18 + 0x10) = uVar26b;
        *(ulong *)(puVar18 + 0x18) = uVar5 << 1;
        puVar1 = puVar18 + 0x20;
        uVar24b = *(ulong *)(puVar37 + 0x18);
        uVar26b = uVar24b >> 1;
        if (*(long *)(puVar37 + 0x10) != 0) {
            if (puVar18 != puVar37 || puVar37 + 0x20 + uVar26b * 0x20 <= puVar1) {
                sk_h_00117d14((word_t)puVar1, (word_t)(puVar37 + 0x20), uVar26b << 5);
            }
            *(word_t *)(puVar37 + 0x10) = 0;
        }
        pauVar30 = (sk_r31_pair_t *)(puVar1 + uVar26b * 0x20);
        lVar32 = (uVar5 & 0x7fffffffffffffff) - (uVar24b >> 1);
        sk_h_0036b118((word_t)puVar37);
        puVar37 = puVar18;
    }
LAB_004980f8:
    bVar14 = SBORROW8(lVar32, 1);
    lVar32 = lVar32 - 1;
    if (bVar14) {
        SK_TRAP(0x4981b8);
    }
    *pauVar30 = auVar38;
    *(ulong *)pauVar30[1].lo = uVar20;
    *(ulong *)((long)pauVar30[1].lo + 8) = uVar22;
    pauVar30 = pauVar30 + 2;
    if (bVar13) {
        local_88 = local_220;
        local_6f = uVar35;
LAB_00498150:
        local_78 = local_240;
        sk_h_004a4b14((word_t *)&local_128, (word_t)&sk_d_00657e78, (word_t)&sk_d_005a55f8);
        if (1 < *(ulong *)(puVar37 + 0x18)) {
            uVar25 = *(ulong *)(puVar37 + 0x18) >> 1;
            if (SBORROW8(uVar25, lVar32)) {
                SK_TRAP(0x4981d8);
            }
            *(ulong *)(puVar37 + 0x10) = uVar25 - lVar32;
        }
        return (word_t)puVar37;
    }
    goto LAB_00497b6c;
}

/* FUN_004981d8 @ 0x004981d8   (est. sk_r31_alloc_uninit_array)
 * Ghidra: undefined8 FUN_004981d8(void)
 * Swift `_allocateUninitializedArray`-style: returns an uninitialized array
 * buffer of `count` elements, or 0 / the empty sentinel when count is 0.
 * The capacity/type-name args (cap, meta, name) are the caller-provided
 * reserve/metadata registers; only the count (unaff_x20) is used here.
 * Confidence: low
 * Notes: FUN_000776d8/776cc/7764c/776f8 are the allocator primitives. */
word_t sk_r31_4981d8(word_t count, word_t cap, word_t *meta, word_t *name)
{
    word_t uVar1;

    sk_h_000776d8();
    if (count == 0) {
        sk_h_000776cc();
        uVar1 = 0;
    } else {
        sk_h_0007764c();
        uVar1 = sk_h_000776f8();
        sk_h_00012568();
        sk_h_004ab698();
    }
    return uVar1;
}

/* FUN_00498228 @ 0x00498228   (est. sk_r31_alloc_array_0x58)
 * Ghidra: undefined * FUN_00498228(long, long)
 * Allocates an array buffer with 0x58-byte elements, growing to at least
 * `count`; empty when capacity rounds to 0.
 * Confidence: low
 * Notes: DAT_00657d50/DAT_005a4b08 element metadata. */
word_t sk_r31_498228(long count, long cap)
{
    word_t uVar1;
    word_t *puVar2;
    long lVar3;

    if (cap <= count) {
        cap = count;
    }
    if (cap == 0) {
        puVar2 = &sk_d_00657778;
    } else {
        uVar1 = sk_h_00002534((word_t)&sk_d_00657d50, (word_t)&sk_d_005a4b08);
        puVar2 = (word_t *)sk_h_0036a940(uVar1, cap * 0x58 + 0x20, 7);
        lVar3 = sk_h_000126e8();
        *(long *)(puVar2 + 0x10) = count;
        *(long *)(puVar2 + 0x18) = (lVar3 - 0x20) / 0x58 << 1;
    }
    return (word_t)puVar2;
}

/* FUN_004982ac @ 0x004982ac   (est. sk_r31_alloc_array_4)
 * Ghidra: undefined * FUN_004982ac(long, long)
 * Allocates an array buffer with 4-byte elements.
 * Confidence: low
 * Notes: DAT_00657db8/DAT_005a4ba8 element metadata. */
word_t sk_r31_4982ac(long count, long cap)
{
    word_t uVar1;
    word_t *puVar2;
    long lVar3;

    if (cap <= count) {
        cap = count;
    }
    if (cap == 0) {
        puVar2 = &sk_d_00657778;
    } else {
        uVar1 = sk_h_00002534((word_t)&sk_d_00657db8, (word_t)&sk_d_005a4ba8);
        puVar2 = (word_t *)sk_h_0036a940(uVar1, cap * 4 + 0x20, 7);
        lVar3 = sk_h_000126e8();
        *(long *)(puVar2 + 0x10) = count;
        *(long *)(puVar2 + 0x18) = (lVar3 - 0x20) / 4 << 1;
    }
    return (word_t)puVar2;
}

/* FUN_00498328 @ 0x00498328   (est. sk_r31_alloc_array_0x160)
 * Ghidra: undefined * FUN_00498328(long, long)
 * Allocates an array buffer with 0x160-byte elements.
 * Confidence: low
 * Notes: DAT_00657c08/DAT_005a3cb0 element metadata. */
word_t sk_r31_498328(long count, long cap)
{
    word_t uVar1;
    word_t *puVar2;
    long lVar3;

    if (cap <= count) {
        cap = count;
    }
    if (cap == 0) {
        puVar2 = &sk_d_00657778;
    } else {
        uVar1 = sk_h_00002534((word_t)&sk_d_00657c08, (word_t)&sk_d_005a3cb0);
        puVar2 = (word_t *)sk_h_0036a940(uVar1, cap * 0x160 + 0x20, 7);
        lVar3 = sk_h_000126e8();
        *(long *)(puVar2 + 0x10) = count;
        *(long *)(puVar2 + 0x18) = (lVar3 - 0x20) / 0x160 << 1;
    }
    return (word_t)puVar2;
}

/* FUN_004983ac @ 0x004983ac   (est. sk_r31_alloc_uninit_array_0x20)
 * Ghidra: undefined8 FUN_004983ac(void)
 * Allocates an uninitialized array buffer of count*0x20 bytes; 0 when count
 * is 0. Only the count register (unaff_x20) is consumed.
 * Confidence: low */
word_t sk_r31_4983ac(word_t count, word_t cap, word_t *meta, word_t *name)
{
    word_t uVar1;
    long lVar2;

    sk_h_000776d8();
    if (count == 0) {
        sk_h_000776cc();
        uVar1 = 0;
    } else {
        sk_h_0007764c();
        uVar1 = sk_h_0007791c(count << 5);
        lVar2 = sk_h_000126e8();
        sk_h_0007766c(lVar2 - 0x20);
    }
    return uVar1;
}

/* FUN_004983fc @ 0x004983fc   (est. sk_r31_alloc_uninit_array_std)
 * Ghidra: undefined8 FUN_004983fc(void)
 * Allocates an uninitialized array buffer of `count` elements (std stride);
 * 0 when count is 0.
 * Confidence: low */
word_t sk_r31_4983fc(word_t count, word_t cap, word_t *meta, word_t *name)
{
    word_t uVar1;

    sk_h_000776d8();
    if (count == 0) {
        sk_h_000776cc();
        uVar1 = 0;
    } else {
        sk_h_0007764c();
        uVar1 = sk_h_000776f8();
        sk_h_00012568();
        sk_h_004ab698();
    }
    return uVar1;
}

/* FUN_0049844c @ 0x0049844c   (est. sk_r31_alloc_uninit_array_8)
 * Ghidra: undefined8 FUN_0049844c(void)
 * Allocates an uninitialized array buffer of count*8 bytes; 0 when count 0.
 * Confidence: low */
word_t sk_r31_49844c(word_t count, word_t cap, word_t *meta, word_t *name)
{
    word_t uVar1;
    long lVar2;

    sk_h_000776d8();
    if (count == 0) {
        sk_h_000776cc();
        uVar1 = 0;
    } else {
        sk_h_0007764c();
        uVar1 = sk_h_0007791c(count << 3);
        lVar2 = sk_h_000126e8();
        sk_h_0007766c(lVar2 - 0x20);
    }
    return uVar1;
}

/* FUN_0049849c @ 0x0049849c   (est. sk_r31_alloc_uninit_array_named)
 * Ghidra: undefined8 FUN_0049849c(void)
 * Allocates an uninitialized array buffer of `count` elements using the
 * named metadata (LAB_00657d30/DAT_005a4ae0); 0 when count is 0.
 * Confidence: low */
word_t sk_r31_49849c(word_t count, word_t cap)
{
    word_t uVar1;

    sk_h_000776d8();
    if (count == 0) {
        sk_h_000776cc();
        uVar1 = 0;
    } else {
        sk_h_00002534((word_t)&sk_d_00657d30, (word_t)&sk_d_005a4ae0);
        uVar1 = sk_h_000776f8();
        sk_h_00012568();
        sk_h_004ab698();
    }
    return uVar1;
}

/* FUN_00498500 @ 0x00498500   (est. sk_r31_copy_move_0x48)
 * Ghidra: void FUN_00498500(ulong, long, ulong)
 * Moves `n` 0x48-byte elements from src to dst, allowing overlap (memmove).
 * Trap-fails on negative count.
 * Confidence: medium
 * Notes: SoftwareBreakpoint(1,0x49853c) on negative n. */
void sk_r31_498500(word_t src, long n, word_t dst)
{
    if (n < 0) {
        SK_TRAP(0x49853c);
    }
    if (dst != src || src + n * 0x48 <= dst) {
        sk_h_00117d14(dst, src, (word_t)(n * 0x48));
    }
}

/* FUN_00498578 @ 0x00498578   (est. sk_r31_copy_move_0x68)
 * Ghidra: void FUN_00498578(ulong, long, ulong)
 * Moves `n` 0x68-byte elements from src to dst (memmove).
 * Confidence: medium
 * Notes: SoftwareBreakpoint(1,0x4985b4) on negative n. */
void sk_r31_498578(word_t src, long n, word_t dst)
{
    if (n < 0) {
        SK_TRAP(0x4985b4);
    }
    if (dst != src || src + n * 0x68 <= dst) {
        sk_h_00117d14(dst, src, (word_t)(n * 0x68));
    }
}

/* FUN_004985b4 @ 0x004985b4   (est. sk_r31_release_elems_0x160)
 * Ghidra: void FUN_004985b4(void)
 * Releases `count` 0x160-byte elements (tag 0x686868) at a buffer pointed
 * to by register global unaff_x20.
 * Confidence: low
 * Notes: unaff_x20 = buffer. */
void sk_r31_4985b4(void)
{
    sk_h_0035bc70((word_t)0 + 0x20, *(word_t *)(0 + 0x10), 0x686868);
}

/* FUN_004985e0 @ 0x004985e0   (est. sk_r31_release_elems_8)
 * Ghidra: void FUN_004985e0(void)
 * Releases `count` 8-byte elements (tag 0x687408) of a register-global
 * buffer.
 * Confidence: low
 * Notes: unaff_x20 = buffer. */
void sk_r31_4985e0(void)
{
    sk_h_0035bc70((word_t)0 + 0x20, *(word_t *)(0 + 0x10), 0x687408);
}

/* FUN_0049860c @ 0x0049860c   (est. sk_r31_copy_into_buffer)
 * Ghidra: ulong FUN_0049860c(undefined8*, long, ulong, undefined8, undefined8, long)
 * Copies up to `n` elements out of the buffer at param_6 into the destination
 * at param_2, walking 0x58-byte source slots and 0x68-byte destination slots.
 * On the last element it retains the trailing value and stops. Returns the
 * number of elements copied and stores {param_4,param_5,param_6,count} into
 * param_1. Trap-fails on negative n or an overrun index.
 * Confidence: low
 * Notes: FUN_0049c704 reads a source slot; FUN_00117cc4 memcpy. */
word_t sk_r31_49860c(word_t *out, long dst, ulong n, word_t a, word_t b, long src)
{
    word_t uVar2;
    long lVar3;
    word_t local_d8;
    word_t uStack_d0;
    byte auStack_130[88];
    byte auStack_c8[104];

    if (dst == 0) {
        uVar2 = 0;
    } else {
        if ((long)n < 0) {
            SK_TRAP(0x498708);
        }
        uVar2 = n;
        if (n != 0) {
            lVar3 = src + 0x20;
            for (uVar2 = 0; uVar2 != *(ulong *)(src + 0x10); uVar2 = uVar2 + 1) {
                if (*(ulong *)(src + 0x10) <= uVar2) {
                    SK_TRAP(0x498704);
                }
                sk_h_0049c704(lVar3, (word_t *)auStack_130);
                local_d8 = a;
                uStack_d0 = b;
                sk_h_00117cc4((word_t)auStack_c8, (word_t)auStack_130, 0x68);
                sk_h_00117cc4(dst, (word_t)auStack_c8, 0x68);
                if (n - 1 == uVar2) {
                    sk_h_0036b270(b);
                    uVar2 = n;
                    break;
                }
                dst = dst + 0x68;
                sk_h_0036b270(b);
                lVar3 = lVar3 + 0x58;
            }
        }
    }
    out[0] = a;
    out[1] = b;
    out[2] = src;
    out[3] = uVar2;
    return uVar2;
}

/* FUN_00498708 @ 0x00498708   (est. sk_r31_range_set_split)
 * Ghidra: long FUN_00498708(long, ulong*, long)
 * RangeSet merge variant that writes merged range pairs into the caller's
 * param_2 array (two words per entry), returning the number written. The
 * context struct at unaff_x20+0x50 holds a 9-byte tagged cursor and a tag
 * byte at +0x58; the loop (LAB_0049875c) walks two collections with the
 * 16-byte range helpers, and the result cursor/state is written back through
 * param_1 (0x50 bytes copied plus +0x50/+0x58 words). Trap-fails on any
 * index overflow.
 * Confidence: low
 * Notes: unaff_x20 = context pointer (explicit param here). */
long sk_r31_498708(long ctx, ulong *out, long count)
{
    word_t uVar21;
    word_t uVar20;
    long lVar25, lVar24;
    sk_r31_pair_t auVar27;
    long lVar10, lVar9, lVar22, lVar1, lVar2;
    word_t uVar8, uVar7, uVar6, uVar5, uVar4, uVar23, uVar3, uVar26;
    word_t uVar19, uVar17, uVar18, uVar16, uVar15, uVar13, uVar14;
    word_t local_c8, uStack_c0, local_b8, uStack_b0, local_a8, uStack_a0;
    word_t local_98, uStack_90, local_88, local_80;
    word_t local_f0, uStack_e8, local_d8, local_d0;
    byte local_e0, local_70;
    word_t local_78;

    uVar21 = *(ulong *)(ctx + 0x50);
    auVar27.lo = *(word_t *)(ctx + 0x50);
    auVar27.hi = (word_t)*(byte *)(ctx + 0x58);
    uVar20 = *(byte *)(ctx + 0x58);
    if (out == (ulong *)0) {
        lVar25 = 0;
    } else {
        if (count < 0) {
            SK_TRAP(0x498ad4);
        }
        lVar25 = count;
        if (count != 0) {
            lVar24 = 0;
LAB_0049875c:
            uVar21 = auVar27.lo;
            lVar25 = lVar24;
            if (SW_TAG(auVar27) == 1) {
                uVar20 = 1;
                goto LAB_00498a80;
            }
            sk_h_00117cc4((word_t)&local_c8, ctx, 0x50);
            lVar10 = local_80;
            lVar9 = local_88;
            uVar8 = uStack_90;
            uVar7 = local_98;
            uVar6 = uStack_a0;
            uVar5 = local_a8;
            uVar4 = uStack_b0;
            uVar23 = local_b8;
            uVar3 = uStack_c0;
            uVar26 = local_c8;
            local_70 = (byte)auVar27.hi;
            uVar19 = uVar21;
            local_78 = uVar21;
            if (local_80 != 0) {
                if (*(long *)(local_88 + 0x10) != 0) {
                    if (SBORROW8(local_80, 1)) {
                        SK_TRAP(0x498acc);
                    }
                    uVar17 = local_a8 >> 0xe;
                    uVar18 = local_c8 >> 0xe;
                    uVar13 = uVar6;
                    lVar22 = lVar10;
                    do {
                        while (true) {
                            lVar22 = lVar22 - 1;
                            uVar21 = sk_h_002b3cf8(uVar21, uVar26, uVar3, uVar23, uVar4);
                            uVar13 = sk_h_002b3cf8(uVar13, uVar5, uVar6, uVar7, uVar8);
                            if (uVar17 <= uVar13 >> 0xe) break;
LAB_00498900:
                            auVar27 = sk_h_002b439c(uVar21, uVar26, uVar3, uVar23, uVar4);
                            sk_r31_pair_t r = sk_h_0046f298(auVar27.lo, auVar27.hi, lVar9);
                            sk_h_003a25d4(auVar27.hi);
                            lVar1 = 0;
                            if (SW_TAG(r) != 1) {
                                lVar1 = r.lo;
                            }
                            lVar2 = lVar22 - lVar1;
                            if (SBORROW8(lVar22, lVar1)) {
                                SK_TRAP(0x498ac8);
                            }
                            if (lVar2 < 2) {
                                lVar2 = 1;
                            }
                            sk_r31_pair_t r2 = sk_h_002b3f40(uVar19, lVar2, uVar3, uVar26, uVar3, uVar23, uVar4);
                            uVar21 = r2.lo;
                            uVar13 = uVar6;
                            lVar22 = lVar10;
                            uVar19 = uVar21;
                            if (SW_TAG(r2) == 1) {
                                uVar20 = 1;
                                goto LAB_00498a80;
                            }
                        }
                        auVar27 = sk_h_002b439c(uVar13, uVar5, uVar6, uVar7, uVar8);
                        uVar15 = auVar27.hi;
                        sk_r31_pair_t r3 = sk_h_002b439c(uVar21, uVar26, uVar3, uVar23, uVar4);
                        uVar16 = r3.hi;
                        if (auVar27.lo == r3.lo && auVar27.hi == r3.hi) {
                            sk_h_003a25d4(uVar15);
                            sk_h_003a25d4(uVar16);
                        } else {
                            uVar14 = sk_h_002a0cf8(auVar27.lo, uVar15, r3.lo, uVar16, 0);
                            sk_h_003a25d4(uVar15);
                            sk_h_003a25d4(uVar16);
                            if ((uVar14 & 1) == 0) goto LAB_00498900;
                        }
                        if (SBORROW8(lVar22, 1)) {
                            SK_TRAP(0x498ac0);
                        }
                        if (uVar13 >> 0xe == uVar17) goto LAB_00498994;
                        if (uVar21 >> 0xe <= uVar18) {
                            SK_TRAP(0x498ac4);
                        }
                    } while (true);
                }
                sk_h_0046ece8((word_t *)&local_f0, local_c8, uStack_c0, local_b8, uStack_b0, uVar21);
                auVar27.hi = (auVar27.hi & 0xffffffffffffff00) | (word_t)local_d0;
                auVar27.lo = local_d8;
                auVar27.hi &= 0xff;
                uVar19 = uStack_e8;
                uVar21 = local_d8;
                uVar26 = local_f0;
                uVar20 = local_d0;
                if (local_e0 != 1) goto LAB_00498a34;
                goto LAB_00498a80;
            }
            {
                bool bv = 0x3fff < (uStack_c0 ^ uVar21);
                uVar23 = bv ? sk_h_002b3b50(uVar21, local_c8, uStack_c0, local_b8, uStack_b0) : 0;
                auVar27.hi = (auVar27.hi & 0xffffffffffffff00) | (word_t)(!bv);
                auVar27.lo = uVar23;
                auVar27.hi &= 0xff;
                uVar26 = uVar21;
                goto LAB_00498a34;
            }
        }
    }
LAB_00498a80:
    sk_h_00117cc4((word_t)out, ctx, 0x50);
    *(ulong *)(out + 0x50) = uVar21;
    *(byte *)(out + 0x58) = (byte)uVar20;
    return lVar25;
LAB_00498994:
    if (uVar19 >> 0xe < uVar21 >> 0xe) {
        SK_TRAP(0x498ad0);
    }
    auVar27 = sk_h_002b3f40(uVar19, lVar10, uVar3, uVar26, uVar3, uVar23, uVar4);
    uVar26 = uVar21;
LAB_00498a34:
    uVar21 = auVar27.lo;
    uVar20 = (byte)auVar27.hi;
    lVar24 = lVar24 + 1;
    *out = uVar26;
    out[1] = uVar19;
    lVar25 = count;
    out = out + 2;
    if (lVar24 == count) goto LAB_00498a80;
    goto LAB_0049875c;
}

/* FUN_00498ad4 @ 0x00498ad4   (est. sk_r31_buffer_ensure_unique)
 * Ghidra: void FUN_00498ad4(void)
 * Ensures a buffer (register global *unaff_x20) is uniquely referenced:
 * checks the refcount via FUN_003a261c; if not unique, drops the old
 * contents (FUN_0006b3f4 on +0x10), runs a teardown helper, and replaces the
 * buffer with a fresh one from FUN_0049921c.
 * Confidence: low
 * Notes: unaff_x20 = *buffer register global. */
void sk_r31_498ad4(void)
{
    ulong uVar1;
    long *unaff_x20;
    long lVar2;

    sk_h_0008409c();
    lVar2 = *unaff_x20;
    uVar1 = sk_h_003a261c(lVar2);
    *unaff_x20 = lVar2;
    if ((uVar1 & 1) == 0) {
        sk_h_0006b3f4(*(word_t *)(lVar2 + 0x10));
        sk_h_00353208();
        lVar2 = sk_r31_49921c(0, 0, 0, lVar2, 0, 0);
        *unaff_x20 = lVar2;
    }
}

/* FUN_00498b28 @ 0x00498b28   (est. sk_r31_buffer_ensure_unique_fn)
 * Ghidra: void FUN_00498b28(code *param_1)
 * Like FUN_00498ad4 but rebuilds via the supplied function pointer when not
 * unique.
 * Confidence: low
 * Notes: unaff_x20 = *buffer register global. */
void sk_r31_498b28(void *rebuild_fn)
{
    ulong uVar1;
    long *unaff_x20;
    long lVar2;

    lVar2 = *unaff_x20;
    uVar1 = sk_h_003a261c(lVar2);
    *unaff_x20 = lVar2;
    if ((uVar1 & 1) == 0) {
        sk_h_0006b3f4(*(word_t *)(lVar2 + 0x10));
        lVar2 = ((long (*)(void))rebuild_fn)();
        *unaff_x20 = lVar2;
    }
}

/* FUN_00498b7c @ 0x00498b7c   (est. sk_r31_buffer_ensure_unique_reg)
 * Ghidra: void FUN_00498b7c(void)
 * Like FUN_00498ad4 but the rebuild function pointer is held in a register
 * global (unaff_x19).
 * Confidence: low
 * Notes: unaff_x19/unaff_x20 register globals. */
void sk_r31_498b7c(void)
{
    ulong uVar1;
    long *unaff_x20;
    long lVar2;

    sk_h_00349a18();
    lVar2 = *unaff_x20;
    uVar1 = sk_h_003a261c(lVar2);
    *unaff_x20 = lVar2;
    if ((uVar1 & 1) == 0) {
        sk_h_0006b3f4(*(word_t *)(lVar2 + 0x10));
        sk_h_004ab910();
        /* (*unaff_x19)() register-global rebuild fn: dropped by decompiler */
        *unaff_x20 = lVar2;
    }
}

/* FUN_00498bdc @ 0x00498bdc   (est. sk_r31_buffer_reserve)
 * Ghidra: void FUN_00498bdc(long param_1)
 * Grows the buffer at *unaff_x20 so it can hold at least param_1+1 elements
 * (reserves via FUN_0049921c when the current capacity is too small).
 * Confidence: low
 * Notes: unaff_x20 = *buffer register global. */
void sk_r31_498bdc(long need)
{
    long lVar1;
    long *unaff_x20;
    sk_r31_pair_t auVar2;

    if ((long)(*(ulong *)(*unaff_x20 + 0x18) >> 1) < need + 1) {
        auVar2 = sk_h_0006b42c();
        lVar1 = sk_r31_49921c(auVar2.lo, auVar2.hi, 1, *unaff_x20, 0, 0);
        *unaff_x20 = lVar1;
    }
}

/* FUN_00498c1c @ 0x00498c1c   (est. sk_r31_buffer_reserve_flag)
 * Ghidra: void FUN_00498c1c(undefined8, undefined8)
 * Reserves capacity (FUN_004ac868) and, when the overflow condition flags
 * indicate success, grows via a register-global function pointer.
 * Confidence: low
 * Notes: register-global condition flags and function pointer dropped. */
void sk_r31_498c1c(word_t a, word_t b)
{
    word_t uVar1;
    word_t *unaff_x20;

    sk_h_004ac868(b);
    if (true) {
        /* (*extraout_x8)(1 < extraout_x9, extraout_x1, 1) register-global grow */
        *unaff_x20 = uVar1;
    }
}

/* FUN_00498c54 @ 0x00498c54   (est. sk_r31_fatal_abort_f)
 * Ghidra: void FUN_00498c54(void)
 * Fatal abort.
 * Confidence: low */
void sk_r31_498c54(void)
{
    sk_h_00021480();
}

/* FUN_00498c6c @ 0x00498c6c   (est. sk_r31_fatal_abort_g)
 * Ghidra: void FUN_00498c6c(void)
 * Fatal abort.
 * Confidence: low */
void sk_r31_498c6c(void)
{
    sk_h_00021480();
}

/* FUN_00498c84 @ 0x00498c84   (est. sk_r31_buffer_reserve_flag2)
 * Ghidra: void FUN_00498c84(void)
 * Like FUN_00498c1c, with the capacity passed in a register (in_x4).
 * Confidence: low
 * Notes: register globals dropped. */
void sk_r31_498c84(word_t cap)
{
    word_t uVar1;
    word_t *unaff_x20;

    sk_h_004ac868(cap);
    if (true) {
        *unaff_x20 = uVar1;
    }
}

/* FUN_00498cc8 @ 0x00498cc8   (est. sk_r31_buffer_resize_0x48)
 * Ghidra: long FUN_00498cc8(ulong, ulong, ulong, long)
 * Swift `_ArrayBuffer._reserveCapacityAndUniquelyReferencing`-style resize:
 * ensures the buffer can hold `count` elements of 0x48-byte stride, growing
 * to the reserve capacity when `reserve`'s bit 0 is set. When the buffer is
 * not uniquely referenced (bit 0 of `isUnique` clear) the old elements are
 * copied into the new allocation; otherwise the old storage is stolen and the
 * buffer released. Returns the new buffer.
 * Confidence: medium
 * Notes: SoftwareBreakpoint(1,0x498d8c) on reserve overflow. */
long sk_r31_498cc8(ulong isUnique, ulong count, ulong reserve, long buf)
{
    ulong uVar3;
    word_t uVar4;
    long lVar2;

    uVar3 = count;
    if ((reserve & 1) != 0) {
        uVar3 = *(ulong *)(buf + 0x18) >> 1;
        if ((long)uVar3 < (long)count) {
            if ((long)(uVar3 + 0x4000000000000000) < 0) {
                SK_TRAP(0x498d8c);
            }
            uVar3 = *(ulong *)(buf + 0x18) & 0xfffffffffffffffe;
            if ((long)uVar3 <= (long)count) {
                uVar3 = count;
            }
        }
    }
    uVar4 = *(word_t *)(buf + 0x10);
    lVar2 = sk_r31_4981d8(uVar4, uVar3, &sk_d_00657d68, &sk_d_005a4b30);
    if ((isUnique & 1) == 0) {
        sk_r31_499820(0, uVar4, lVar2 + 0x20, buf);
    } else {
        sk_r31_498500(buf + 0x20, uVar4, lVar2 + 0x20);
        *(word_t *)(buf + 0x10) = 0;
        sk_h_0036b118(buf);
    }
    return lVar2;
}

/* FUN_00498d8c @ 0x00498d8c   (est. sk_r31_buffer_resize_0x48b)
 * Ghidra: long FUN_00498d8c(ulong, ulong, ulong, long)
 * Resize to `count` 0x48-byte elements (variant B).
 * Confidence: medium
 * Notes: SoftwareBreakpoint(1,0x498e50). */
long sk_r31_498d8c(ulong isUnique, ulong count, ulong reserve, long buf)
{
    ulong uVar3;
    word_t uVar4;
    long lVar2;

    uVar3 = count;
    if ((reserve & 1) != 0) {
        uVar3 = *(ulong *)(buf + 0x18) >> 1;
        if ((long)uVar3 < (long)count) {
            if ((long)(uVar3 + 0x4000000000000000) < 0) {
                SK_TRAP(0x498e50);
            }
            uVar3 = *(ulong *)(buf + 0x18) & 0xfffffffffffffffe;
            if ((long)uVar3 <= (long)count) {
                uVar3 = count;
            }
        }
    }
    uVar4 = *(word_t *)(buf + 0x10);
    lVar2 = sk_r31_4981d8(uVar4, uVar3, &sk_d_00657d78, &sk_d_005a4b40);
    if ((isUnique & 1) == 0) {
        sk_r31_49989c(0, uVar4, lVar2 + 0x20, buf);
    } else {
        sk_h_00072320(buf + 0x20, uVar4, lVar2 + 0x20);
        *(word_t *)(buf + 0x10) = 0;
        sk_h_0036b118(buf);
    }
    return lVar2;
}

/* FUN_00498e50 @ 0x00498e50   (est. sk_r31_buffer_resize_generic)
 * Ghidra: long FUN_00498e50(ulong, long, ulong, long, code*, code*, code*)
 * Generic buffer resize with caller-supplied allocation (param_5), move
 * (param_6) and completion (param_7) function pointers. Handles the reserve
 * overflow path via FUN_004652d4/FUN_00465428.
 * Confidence: medium
 * Notes: SoftwareBreakpoint(1,0x498f0c); fn pointers are caller-provided
 * element-type instantiations. */
long sk_r31_498e50(ulong isUnique, long count, ulong reserve, long buf,
                   void *alloc_fn, void *move_fn, void *done_fn)
{
    word_t uVar3;
    sk_r31_pair_t auVar4;
    long lVar2;

    if (((reserve & 1) != 0) && (sk_h_004652d4() != 0)) {
        if ((long)(count + 0x4000000000000000) < 0) {
            SK_TRAP(0x498f0c);
        }
        sk_h_00465428();
    }
    uVar3 = *(word_t *)(buf + 0x10);
    auVar4 = ((sk_r31_pair_t (*)(word_t, long))alloc_fn)(uVar3, count);
    lVar2 = auVar4.lo;
    if ((isUnique & 1) == 0) {
        sk_h_0035050c(lVar2, auVar4.hi, lVar2 + 0x20);
        ((void (*)(void))done_fn)();
    } else {
        ((void (*)(long, word_t, long))move_fn)(buf + 0x20, uVar3, lVar2 + 0x20);
        *(word_t *)(buf + 0x10) = 0;
        sk_h_0036b118(buf);
    }
    return lVar2;
}

/* FUN_00498f0c @ 0x00498f0c   (est. sk_r31_buffer_resize_8a)
 * Ghidra: long FUN_00498f0c(ulong, ulong, ulong, long)
 * Resize to `count` 8-byte elements (variant A).
 * Confidence: medium
 * Notes: SoftwareBreakpoint(1,0x498fd0). */
long sk_r31_498f0c(ulong isUnique, ulong count, ulong reserve, long buf)
{
    ulong uVar3;
    word_t uVar4;
    long lVar2;

    uVar3 = count;
    if ((reserve & 1) != 0) {
        uVar3 = *(ulong *)(buf + 0x18) >> 1;
        if ((long)uVar3 < (long)count) {
            if ((long)(uVar3 + 0x4000000000000000) < 0) {
                SK_TRAP(0x498fd0);
            }
            uVar3 = *(ulong *)(buf + 0x18) & 0xfffffffffffffffe;
            if ((long)uVar3 <= (long)count) {
                uVar3 = count;
            }
        }
    }
    uVar4 = *(word_t *)(buf + 0x10);
    lVar2 = sk_r31_49844c(uVar4, uVar3, &sk_d_00657c28, &sk_d_005a3cd0);
    if ((isUnique & 1) == 0) {
        sk_r31_499998(0, uVar4, lVar2 + 0x20, buf);
    } else {
        sk_h_000721d8(buf + 0x20, uVar4, lVar2 + 0x20);
        *(word_t *)(buf + 0x10) = 0;
        sk_h_0036b118(buf);
    }
    return lVar2;
}

/* FUN_00498fd0 @ 0x00498fd0   (est. sk_r31_buffer_resize_meta)
 * Ghidra: long FUN_00498fd0(ulong, ulong, ulong, long)
 * Resize to `count` elements with the DAT_00657da8/DAT_005a4b98 metadata.
 * Confidence: medium
 * Notes: SoftwareBreakpoint(1,0x499094). */
long sk_r31_498fd0(ulong isUnique, ulong count, ulong reserve, long buf)
{
    ulong uVar3;
    word_t uVar4;
    long lVar2;

    uVar3 = count;
    if ((reserve & 1) != 0) {
        uVar3 = *(ulong *)(buf + 0x18) >> 1;
        if ((long)uVar3 < (long)count) {
            if ((long)(uVar3 + 0x4000000000000000) < 0) {
                SK_TRAP(0x499094);
            }
            uVar3 = *(ulong *)(buf + 0x18) & 0xfffffffffffffffe;
            if ((long)uVar3 <= (long)count) {
                uVar3 = count;
            }
        }
    }
    uVar4 = *(word_t *)(buf + 0x10);
    lVar2 = sk_h_004a398c(uVar4, uVar3, &sk_d_00657da8, &sk_d_005a4b98);
    if ((isUnique & 1) == 0) {
        sk_h_00075624(0, uVar4, lVar2 + 0x20, buf);
    } else {
        sk_h_00069970(buf + 0x20, uVar4, lVar2 + 0x20);
        *(word_t *)(buf + 0x10) = 0;
        sk_h_0036b118(buf);
    }
    return lVar2;
}

/* FUN_00499094 @ 0x00499094   (est. sk_r31_buffer_resize_0x20)
 * Ghidra: long FUN_00499094(ulong, ulong, ulong, long)
 * Resize to `count` 0x20-byte elements.
 * Confidence: medium
 * Notes: SoftwareBreakpoint(1,0x499158). */
long sk_r31_499094(ulong isUnique, ulong count, ulong reserve, long buf)
{
    ulong uVar3;
    word_t uVar4;
    long lVar2;

    uVar3 = count;
    if ((reserve & 1) != 0) {
        uVar3 = *(ulong *)(buf + 0x18) >> 1;
        if ((long)uVar3 < (long)count) {
            if ((long)(uVar3 + 0x4000000000000000) < 0) {
                SK_TRAP(0x499158);
            }
            uVar3 = *(ulong *)(buf + 0x18) & 0xfffffffffffffffe;
            if ((long)uVar3 <= (long)count) {
                uVar3 = count;
            }
        }
    }
    uVar4 = *(word_t *)(buf + 0x10);
    lVar2 = sk_r31_4983ac(uVar4, uVar3, &sk_d_00657dc0, &sk_d_005a4bb0);
    if ((isUnique & 1) == 0) {
        sk_h_00074b08(0, uVar4, lVar2 + 0x20, buf);
    } else {
        sk_h_000699a4(buf + 0x20, uVar4, lVar2 + 0x20);
        *(word_t *)(buf + 0x10) = 0;
        sk_h_0036b118(buf);
    }
    return lVar2;
}

/* FUN_00499158 @ 0x00499158   (est. sk_r31_buffer_resize_8b)
 * Ghidra: long FUN_00499158(ulong, ulong, ulong, long)
 * Resize to `count` 8-byte elements (variant B).
 * Confidence: medium
 * Notes: SoftwareBreakpoint(1,0x49921c); LAB_00657db0 metadata. */
long sk_r31_499158(ulong isUnique, ulong count, ulong reserve, long buf)
{
    ulong uVar3;
    word_t uVar4;
    long lVar2;

    uVar3 = count;
    if ((reserve & 1) != 0) {
        uVar3 = *(ulong *)(buf + 0x18) >> 1;
        if ((long)uVar3 < (long)count) {
            if ((long)(uVar3 + 0x4000000000000000) < 0) {
                SK_TRAP(0x49921c);
            }
            uVar3 = *(ulong *)(buf + 0x18) & 0xfffffffffffffffe;
            if ((long)uVar3 <= (long)count) {
                uVar3 = count;
            }
        }
    }
    uVar4 = *(word_t *)(buf + 0x10);
    lVar2 = sk_r31_49844c(uVar4, uVar3, &sk_d_00657db0, &sk_d_005a4ba0);
    if ((isUnique & 1) == 0) {
        sk_r31_499a8c(0, uVar4, lVar2 + 0x20, buf);
    } else {
        sk_h_000721b0(buf + 0x20, uVar4, lVar2 + 0x20);
        *(word_t *)(buf + 0x10) = 0;
        sk_h_0036b118(buf);
    }
    return lVar2;
}

/* FUN_0049921c @ 0x0049921c   (est. sk_r31_buffer_resize_meta2)
 * Ghidra: long FUN_0049921c(ulong, long, ulong, long, undefined8, undefined8)
 * Resize with the DAT_00657df0/DAT_005a4be0 metadata family and reserve
 * overflow handling. Variants call this with 0 or 3 register-provided args;
 * the extra register args are elided.
 * Confidence: medium
 * Notes: SoftwareBreakpoint(1,0x4992c8). */
long sk_r31_49921c(ulong isUnique, long count, ulong reserve, long buf,
                   word_t meta, word_t name)
{
    word_t uVar3;
    long lVar2;

    if (((reserve & 1) != 0) && (sk_h_004652d4() != 0)) {
        if ((long)(count + 0x4000000000000000) < 0) {
            SK_TRAP(0x4992c8);
        }
        sk_h_00465428();
    }
    uVar3 = *(word_t *)(buf + 0x10);
    lVar2 = sk_h_004a398c(uVar3, count, meta, name);
    if ((isUnique & 1) == 0) {
        sk_r31_499afc(0, uVar3, lVar2 + 0x20, buf);
    } else {
        sk_h_00072044(buf + 0x20, uVar3, lVar2 + 0x20);
        *(word_t *)(buf + 0x10) = 0;
        sk_h_0036b118(buf);
    }
    return lVar2;
}

/* FUN_004992c8 @ 0x004992c8   (est. sk_r31_buffer_resize_std)
 * Ghidra: long FUN_004992c8(ulong, ulong, ulong, long)
 * Resize to `count` std-stride elements.
 * Confidence: medium
 * Notes: SoftwareBreakpoint(1,0x49938c). */
long sk_r31_4992c8(ulong isUnique, ulong count, ulong reserve, long buf)
{
    ulong uVar3;
    word_t uVar4;
    long lVar2;

    uVar3 = count;
    if ((reserve & 1) != 0) {
        uVar3 = *(ulong *)(buf + 0x18) >> 1;
        if ((long)uVar3 < (long)count) {
            if ((long)(uVar3 + 0x4000000000000000) < 0) {
                SK_TRAP(0x49938c);
            }
            uVar3 = *(ulong *)(buf + 0x18) & 0xfffffffffffffffe;
            if ((long)uVar3 <= (long)count) {
                uVar3 = count;
            }
        }
    }
    uVar4 = *(word_t *)(buf + 0x10);
    lVar2 = sk_r31_4983fc(uVar4, uVar3, &sk_d_00657de0, &sk_d_005a4bd0);
    if ((isUnique & 1) == 0) {
        sk_h_00456b28(0, uVar4, lVar2 + 0x20, buf);
    } else {
        sk_h_000699d8(buf + 0x20, uVar4, lVar2 + 0x20);
        *(word_t *)(buf + 0x10) = 0;
        sk_h_0036b118(buf);
    }
    return lVar2;
}

/* FUN_0049938c @ 0x0049938c   (est. sk_r31_buffer_resize_8c)
 * Ghidra: long FUN_0049938c(ulong, ulong, ulong, long)
 * Resize to `count` 8-byte elements (variant C).
 * Confidence: medium
 * Notes: SoftwareBreakpoint(1,0x499450); LAB_00657e18 metadata. */
long sk_r31_49938c(ulong isUnique, ulong count, ulong reserve, long buf)
{
    ulong uVar3;
    word_t uVar4;
    long lVar2;

    uVar3 = count;
    if ((reserve & 1) != 0) {
        uVar3 = *(ulong *)(buf + 0x18) >> 1;
        if ((long)uVar3 < (long)count) {
            if ((long)(uVar3 + 0x4000000000000000) < 0) {
                SK_TRAP(0x499450);
            }
            uVar3 = *(ulong *)(buf + 0x18) & 0xfffffffffffffffe;
            if ((long)uVar3 <= (long)count) {
                uVar3 = count;
            }
        }
    }
    uVar4 = *(word_t *)(buf + 0x10);
    lVar2 = sk_r31_49844c(uVar4, uVar3, &sk_d_00657e18, &sk_d_005a4c20);
    if ((isUnique & 1) == 0) {
        sk_r31_499a8c(0, uVar4, lVar2 + 0x20, buf);
    } else {
        sk_h_000721b0(buf + 0x20, uVar4, lVar2 + 0x20);
        *(word_t *)(buf + 0x10) = 0;
        sk_h_0036b118(buf);
    }
    return lVar2;
}

/* FUN_00499450 @ 0x00499450   (est. sk_r31_emit_field)
 * Ghidra: void FUN_00499450(undefined8, undefined8)
 * Emits a field/value through the DAT_00616a58 formatter.
 * Confidence: low */
void sk_r31_499450(word_t a, word_t b)
{
    sk_h_0036ffc0(a, b, &sk_d_00616a58);
}

/* FUN_00499468 @ 0x00499468   (est. sk_r31_buffer_resize_d)
 * Ghidra: long FUN_00499468(ulong, ulong, ulong, long)
 * Resize to `count` elements (variant D).
 * Confidence: medium
 * Notes: SoftwareBreakpoint(1,0x49952c); LAB_00657e20 metadata. */
long sk_r31_499468(ulong isUnique, ulong count, ulong reserve, long buf)
{
    ulong uVar3;
    word_t uVar4;
    long lVar2;

    uVar3 = count;
    if ((reserve & 1) != 0) {
        uVar3 = *(ulong *)(buf + 0x18) >> 1;
        if ((long)uVar3 < (long)count) {
            if ((long)(uVar3 + 0x4000000000000000) < 0) {
                SK_TRAP(0x49952c);
            }
            uVar3 = *(ulong *)(buf + 0x18) & 0xfffffffffffffffe;
            if ((long)uVar3 <= (long)count) {
                uVar3 = count;
            }
        }
    }
    uVar4 = *(word_t *)(buf + 0x10);
    lVar2 = sk_h_00071a4c(uVar4, uVar3, &sk_d_00657e20, &sk_d_005a5530);
    if ((isUnique & 1) == 0) {
        sk_h_00074dc8(0, uVar4, lVar2 + 0x20, buf);
    } else {
        sk_h_000720a8(buf + 0x20, uVar4, lVar2 + 0x20);
        *(word_t *)(buf + 0x10) = 0;
        sk_h_0036b118(buf);
    }
    return lVar2;
}

/* FUN_0049952c @ 0x0049952c   (est. sk_r31_buffer_resize_std2)
 * Ghidra: long FUN_0049952c(ulong, long, ulong, long, undefined8, undefined8)
 * Resize with reserve overflow handling and a completion helper
 * (sk_r31_499b90).
 * Confidence: medium
 * Notes: SoftwareBreakpoint(1,0x4995e4). */
long sk_r31_49952c(ulong isUnique, long count, ulong reserve, long buf,
                   word_t meta, word_t name)
{
    word_t uVar3;
    long lVar2;

    if (((reserve & 1) != 0) && (sk_h_004652d4() != 0)) {
        if ((long)(count + 0x4000000000000000) < 0) {
            SK_TRAP(0x4995e4);
        }
        sk_h_00465428();
    }
    uVar3 = *(word_t *)(buf + 0x10);
    lVar2 = sk_r31_4983fc(uVar3, count, (word_t *)meta, (word_t *)name);
    if ((isUnique & 1) == 0) {
        sk_h_00350500(lVar2, 0, lVar2 + 0x20);   /* decompiler's x1 leftover = 0 */
        sk_r31_499b90(0, 0, 0, 0, 0);
    } else {
        sk_h_00072358(buf + 0x20, uVar3, lVar2 + 0x20);
        *(word_t *)(buf + 0x10) = 0;
        sk_h_0036b118(buf);
    }
    return lVar2;
}

/* FUN_004995e4 @ 0x004995e4   (est. sk_r31_buffer_resize_8d)
 * Ghidra: long FUN_004995e4(ulong, ulong, ulong, long)
 * Resize to `count` 8-byte elements (variant D).
 * Confidence: medium
 * Notes: SoftwareBreakpoint(1,0x4996a8). */
long sk_r31_4995e4(ulong isUnique, ulong count, ulong reserve, long buf)
{
    ulong uVar3;
    word_t uVar4;
    long lVar2;

    uVar3 = count;
    if ((reserve & 1) != 0) {
        uVar3 = *(ulong *)(buf + 0x18) >> 1;
        if ((long)uVar3 < (long)count) {
            if ((long)(uVar3 + 0x4000000000000000) < 0) {
                SK_TRAP(0x4996a8);
            }
            uVar3 = *(ulong *)(buf + 0x18) & 0xfffffffffffffffe;
            if ((long)uVar3 <= (long)count) {
                uVar3 = count;
            }
        }
    }
    uVar4 = *(word_t *)(buf + 0x10);
    lVar2 = sk_r31_49844c(uVar4, uVar3, &sk_d_00657d80, &sk_d_005a4b48);
    if ((isUnique & 1) == 0) {
        sk_r31_499a8c(0, uVar4, lVar2 + 0x20, buf);
    } else {
        sk_h_000721d8(buf + 0x20, uVar4, lVar2 + 0x20);
        *(word_t *)(buf + 0x10) = 0;
        sk_h_0036b118(buf);
    }
    return lVar2;
}

/* FUN_004996a8 @ 0x004996a8   (est. sk_r31_buffer_resize_8e)
 * Ghidra: long FUN_004996a8(ulong, ulong, ulong, long)
 * Resize to `count` 8-byte elements (variant E).
 * Confidence: medium
 * Notes: SoftwareBreakpoint(1,0x49976c). */
long sk_r31_4996a8(ulong isUnique, ulong count, ulong reserve, long buf)
{
    ulong uVar3;
    word_t uVar4;
    long lVar2;

    uVar3 = count;
    if ((reserve & 1) != 0) {
        uVar3 = *(ulong *)(buf + 0x18) >> 1;
        if ((long)uVar3 < (long)count) {
            if ((long)(uVar3 + 0x4000000000000000) < 0) {
                SK_TRAP(0x49976c);
            }
            uVar3 = *(ulong *)(buf + 0x18) & 0xfffffffffffffffe;
            if ((long)uVar3 <= (long)count) {
                uVar3 = count;
            }
        }
    }
    uVar4 = *(word_t *)(buf + 0x10);
    lVar2 = sk_r31_49844c(uVar4, uVar3, &sk_d_00657e88, &sk_d_005a5c98);
    if ((isUnique & 1) == 0) {
        sk_r31_499c08(0, uVar4, lVar2 + 0x20, buf);
    } else {
        sk_h_000721d8(buf + 0x20, uVar4, lVar2 + 0x20);
        *(word_t *)(buf + 0x10) = 0;
        sk_h_0036b118(buf);
    }
    return lVar2;
}

/* FUN_0049976c @ 0x0049976c   (est. sk_r31_buffer_resize_0x68)
 * Ghidra: long FUN_0049976c(ulong, ulong, ulong, long)
 * Resize to `count` 0x68-byte elements.
 * Confidence: medium
 * Notes: SoftwareBreakpoint(1,0x499820). */
long sk_r31_49976c(ulong isUnique, ulong count, ulong reserve, long buf)
{
    ulong uVar3;
    word_t uVar4;
    long lVar2;

    uVar3 = count;
    if ((reserve & 1) != 0) {
        uVar3 = *(ulong *)(buf + 0x18) >> 1;
        if ((long)uVar3 < (long)count) {
            if ((long)(uVar3 + 0x4000000000000000) < 0) {
                SK_TRAP(0x499820);
            }
            uVar3 = *(ulong *)(buf + 0x18) & 0xfffffffffffffffe;
            if ((long)uVar3 <= (long)count) {
                uVar3 = count;
            }
        }
    }
    uVar4 = *(word_t *)(buf + 0x10);
    lVar2 = sk_r31_49849c(uVar4, uVar3);
    if ((isUnique & 1) == 0) {
        sk_r31_499c7c(0, uVar4, lVar2 + 0x20, buf);
    } else {
        sk_r31_498578(buf + 0x20, uVar4, lVar2 + 0x20);
        *(word_t *)(buf + 0x10) = 0;
        sk_h_0036b118(buf);
    }
    return lVar2;
}

/* The following are the per-stride "copy N elements into a fresh buffer"
 * helpers: copy `to-from` 0x48/0x58/8/0x160/0x18/0x68/0x10-byte elements from
 * buf+(from*stride)+0x20 to dst, releasing the old buffer. Each traps on a
 * negative or overlapping range. */

/* FUN_00499820 @ 0x00499820   (est. sk_r31_copy_elems_0x48)
 * Ghidra: ulong FUN_00499820(long, long, ulong, long)
 * Copy 0x48-byte elements [from,to) out of buf into dst; release buf.
 * Confidence: medium */
word_t sk_r31_499820(long from, long to, ulong dst, long buf)
{
    ulong uVar1, uVar2;
    long lVar3;

    lVar3 = to - from;
    if (SBORROW8(to, from)) {
        SK_TRAP(0x499894);
    }
    if (-1 < lVar3) {
        uVar1 = buf + from * 0x48 + 0x20;
        uVar2 = dst + lVar3 * 0x48;
        if (uVar2 <= uVar1 || uVar1 + lVar3 * 0x48 <= dst) {
            sk_h_0035b67c(dst, uVar1, lVar3, &sk_d_00688ea0);
            sk_h_0036b118(buf);
            return uVar2;
        }
        SK_TRAP(0x49989c);
    }
    SK_TRAP(0x499898);
    return 0;
}

/* FUN_0049989c @ 0x0049989c   (est. sk_r31_copy_elems_0x48b)
 * Ghidra: ulong FUN_0049989c(long, long, ulong, long)
 * Copy 0x48-byte elements (variant B).
 * Confidence: medium */
word_t sk_r31_49989c(long from, long to, ulong dst, long buf)
{
    ulong uVar1, uVar2;
    long lVar3;

    lVar3 = to - from;
    if (SBORROW8(to, from)) {
        SK_TRAP(0x499910);
    }
    if (-1 < lVar3) {
        uVar1 = buf + from * 0x48 + 0x20;
        uVar2 = dst + lVar3 * 0x48;
        if (uVar2 <= uVar1 || uVar1 + lVar3 * 0x48 <= dst) {
            sk_h_0035b67c(dst, uVar1, lVar3, &sk_d_006893a8);
            sk_h_0036b118(buf);
            return uVar2;
        }
        SK_TRAP(0x499918);
    }
    SK_TRAP(0x499914);
    return 0;
}

/* FUN_00499918 @ 0x00499918   (est. sk_r31_copy_elems_0x58)
 * Ghidra: ulong FUN_00499918(long, long, ulong, long)
 * Copy 0x58-byte elements (tag 0x687800).
 * Confidence: medium */
word_t sk_r31_499918(long from, long to, ulong dst, long buf)
{
    ulong uVar1, uVar2;
    long lVar3;

    lVar3 = to - from;
    if (SBORROW8(to, from)) {
        SK_TRAP(0x499990);
    }
    if (-1 < lVar3) {
        uVar1 = buf + from * 0x58 + 0x20;
        uVar2 = dst + lVar3 * 0x58;
        if (uVar2 <= uVar1 || uVar1 + lVar3 * 0x58 <= dst) {
            sk_h_0035b67c(dst, uVar1, lVar3, 0x687800);
            sk_h_0036b118(buf);
            return uVar2;
        }
        SK_TRAP(0x499998);
    }
    SK_TRAP(0x499994);
    return 0;
}

/* FUN_00499998 @ 0x00499998   (est. sk_r31_copy_elems_8)
 * Ghidra: ulong FUN_00499998(long, long, ulong, long)
 * Copy 8-byte elements (tag 0x687408).
 * Confidence: medium */
word_t sk_r31_499998(long from, long to, ulong dst, long buf)
{
    ulong uVar1, uVar2;
    long lVar3;

    lVar3 = to - from;
    if (SBORROW8(to, from)) {
        SK_TRAP(0x499a04);
    }
    if (-1 < lVar3) {
        uVar1 = buf + from * 8 + 0x20;
        uVar2 = dst + lVar3 * 8;
        if (uVar2 <= uVar1 || uVar1 + lVar3 * 8 <= dst) {
            sk_h_0035b67c(dst, uVar1, lVar3, 0x687408);
            sk_h_0036b118(buf);
            return uVar2;
        }
        SK_TRAP(0x499a0c);
    }
    SK_TRAP(0x499a08);
    return 0;
}

/* FUN_00499a0c @ 0x00499a0c   (est. sk_r31_copy_elems_0x160)
 * Ghidra: ulong FUN_00499a0c(long, long, ulong, long)
 * Copy 0x160-byte elements (tag 0x686868).
 * Confidence: medium */
word_t sk_r31_499a0c(long from, long to, ulong dst, long buf)
{
    ulong uVar1, uVar2;
    long lVar3;

    lVar3 = to - from;
    if (SBORROW8(to, from)) {
        SK_TRAP(0x499a84);
    }
    if (-1 < lVar3) {
        uVar1 = buf + from * 0x160 + 0x20;
        uVar2 = dst + lVar3 * 0x160;
        if (uVar2 <= uVar1 || uVar1 + lVar3 * 0x160 <= dst) {
            sk_h_0035b67c(dst, uVar1, lVar3, 0x686868);
            sk_h_0036b118(buf);
            return uVar2;
        }
        SK_TRAP(0x499a8c);
    }
    SK_TRAP(0x499a88);
    return 0;
}

/* FUN_00499a8c @ 0x00499a8c   (est. sk_r31_copy_elems_8b)
 * Ghidra: ulong FUN_00499a8c(long, long, ulong, long)
 * Copy 8-byte elements (memcpy via FUN_00117cc4).
 * Confidence: medium */
word_t sk_r31_499a8c(long from, long to, ulong dst, long buf)
{
    ulong uVar1, uVar2;
    long lVar3;

    lVar3 = to - from;
    if (SBORROW8(to, from)) {
        SK_TRAP(0x499af4);
    }
    if (-1 < lVar3) {
        uVar1 = buf + from * 8 + 0x20;
        uVar2 = dst + lVar3 * 8;
        if (uVar2 <= uVar1 || uVar1 + lVar3 * 8 <= dst) {
            sk_h_00117cc4(dst, uVar1, lVar3 * 8);
            sk_h_0036b118(buf);
            return uVar2;
        }
        SK_TRAP(0x499afc);
    }
    SK_TRAP(0x499af8);
    return 0;
}

/* FUN_00499afc @ 0x00499afc   (est. sk_r31_copy_elems_0x10)
 * Ghidra: ulong FUN_00499afc(long, long, ulong, long)
 * Copy 0x10-byte elements through the boxed-copy helper FUN_00351450
 * (elements are reference-counted pairs).
 * Confidence: medium */
word_t sk_r31_499afc(long from, long to, ulong dst, long buf)
{
    ulong uVar1, uVar2;
    long lVar3;
    long lVar5;
    sk_r31_pair_t auVar6;

    lVar3 = to - from;
    if (SBORROW8(to, from)) {
        SK_TRAP(0x499b88);
    }
    if (-1 < lVar3) {
        lVar5 = sk_h_00077888();
        uVar1 = buf + lVar5 * 0x10 + 0x20;
        uVar2 = dst + lVar3 * 0x10;
        if (uVar2 <= uVar1 || uVar1 + lVar3 * 0x10 <= dst) {
            sk_h_00002534((word_t)&sk_d_00657dc8, (word_t)&sk_d_005a4bb8);
            auVar6 = sk_h_00351450();
            sk_h_0035b67c(auVar6.lo, auVar6.hi, lVar3);
            sk_h_0036b118();
            return uVar2;
        }
        SK_TRAP(0x499b90);
    }
    SK_TRAP(0x499b8c);
    return 0;
}

/* FUN_00499b90 @ 0x00499b90   (est. sk_r31_copy_elems_0x18)
 * Ghidra: ulong FUN_00499b90(long, long, ulong, long, undefined8)
 * Copy 0x18-byte elements with the tag in param_5.
 * Confidence: medium */
word_t sk_r31_499b90(long from, long to, ulong dst, long buf, word_t tag)
{
    ulong uVar1, uVar2;
    long lVar3;

    lVar3 = to - from;
    if (SBORROW8(to, from)) {
        SK_TRAP(0x499c00);
    }
    if (-1 < lVar3) {
        uVar1 = buf + from * 0x18 + 0x20;
        uVar2 = dst + lVar3 * 0x18;
        if (uVar2 <= uVar1 || uVar1 + lVar3 * 0x18 <= dst) {
            sk_h_0035b67c(dst, uVar1, lVar3, tag);
            sk_h_0036b118(buf);
            return uVar2;
        }
        SK_TRAP(0x499c08);
    }
    SK_TRAP(0x499c04);
    return 0;
}

/* FUN_00499c08 @ 0x00499c08   (est. sk_r31_copy_elems_8c)
 * Ghidra: ulong FUN_00499c08(long, long, ulong, long)
 * Copy 8-byte elements (tag DAT_006888f0).
 * Confidence: medium */
word_t sk_r31_499c08(long from, long to, ulong dst, long buf)
{
    ulong uVar1, uVar2;
    long lVar3;

    lVar3 = to - from;
    if (SBORROW8(to, from)) {
        SK_TRAP(0x499c74);
    }
    if (-1 < lVar3) {
        uVar1 = buf + from * 8 + 0x20;
        uVar2 = dst + lVar3 * 8;
        if (uVar2 <= uVar1 || uVar1 + lVar3 * 8 <= dst) {
            sk_h_0035b67c(dst, uVar1, lVar3, &sk_d_006888f0);
            sk_h_0036b118(buf);
            return uVar2;
        }
        SK_TRAP(0x499c7c);
    }
    SK_TRAP(0x499c78);
    return 0;
}

/* FUN_00499c7c @ 0x00499c7c   (est. sk_r31_copy_elems_0x68)
 * Ghidra: ulong FUN_00499c7c(long, long, ulong, long)
 * Copy 0x68-byte elements (tag 0x686660).
 * Confidence: medium */
word_t sk_r31_499c7c(long from, long to, ulong dst, long buf)
{
    ulong uVar1, uVar2;
    long lVar3;

    lVar3 = to - from;
    if (SBORROW8(to, from)) {
        SK_TRAP(0x499cf4);
    }
    if (-1 < lVar3) {
        uVar1 = buf + from * 0x68 + 0x20;
        uVar2 = dst + lVar3 * 0x68;
        if (uVar2 <= uVar1 || uVar1 + lVar3 * 0x68 <= dst) {
            sk_h_0035b67c(dst, uVar1, lVar3, 0x686660);
            sk_h_0036b118(buf);
            return uVar2;
        }
        SK_TRAP(0x499cfc);
    }
    SK_TRAP(0x499cf8);
    return 0;
}

/* FUN_00499cfc @ 0x00499cfc   (est. sk_r31_swap_elems_8)
 * Ghidra: void FUN_00499cfc(ulong, long, ulong)
 * Overlap-checked swap/move of `n` 8-byte elements from src to dst (tag
 * 0x687408). Trap-fails on negative n or overlap.
 * Confidence: medium */
void sk_r31_499cfc(word_t src, long n, word_t dst)
{
    if (n < 0) {
        SK_TRAP(0x499d34);
    }
    if (dst + n * 8 <= src || src + n * 8 <= dst) {
        sk_h_0035b67c(dst, src, n, 0x687408);
        return;
    }
    SK_TRAP(0x499d38);
}

/* FUN_00499d38 @ 0x00499d38   (est. sk_r31_swap_elems_0x160)
 * Ghidra: void FUN_00499d38(ulong, long, ulong)
 * Overlap-checked swap/move of `n` 0x160-byte elements (tag 0x686868).
 * Confidence: medium */
void sk_r31_499d38(word_t src, long n, word_t dst)
{
    if (n < 0) {
        SK_TRAP(0x499d78);
    }
    if (dst + n * 0x160 <= src || src + n * 0x160 <= dst) {
        sk_h_0035b67c(dst, src, n, 0x686868);
        return;
    }
    SK_TRAP(0x499d7c);
}

/* FUN_00499d7c @ 0x00499d7c   (est. sk_r31_swap_elems_0x18)
 * Ghidra: void FUN_00499d7c(ulong, long, ulong)
 * Overlap-checked swap/move of `n` 0x18-byte elements (tag DAT_00688878).
 * Confidence: medium */
void sk_r31_499d7c(word_t src, long n, word_t dst)
{
    if (n < 0) {
        SK_TRAP(0x499db8);
    }
    if (dst + n * 0x18 <= src || src + n * 0x18 <= dst) {
        sk_h_0035b67c(dst, src, n, &sk_d_00688878);
        return;
    }
    SK_TRAP(0x499dbc);
}

/* FUN_00499dbc @ 0x00499dbc   (est. sk_r31_alloc_array_8_cap)
 * Ghidra: long FUN_00499dbc(long)
 * Allocates an 8-byte-element array buffer of at least `count` slots,
 * zero-initialized (+0x10 = 0). Trap-fails (FUN_000a6fe0) when count < 1.
 * Confidence: low */
long sk_r31_499dbc(long count)
{
    long lVar1;
    word_t buf;

    if (count < 1) {
        sk_h_000a6fe0();
    } else {
        sk_h_00106e3c();
        sk_h_00002534(0, 0);
        buf = sk_h_0007791c(count << 3);
        lVar1 = sk_h_000126e8();
        *(word_t *)(buf + 0x10) = 0;
        *(long *)(buf + 0x18) = (lVar1 - 0x20) / 8 << 1;
    }
    return buf;
}

/* FUN_00499e1c @ 0x00499e1c   (est. sk_r31_alloc_array_0x20)
 * Ghidra: undefined * FUN_00499e1c(long)
 * Allocates a 0x20-byte-element array buffer of `count` slots; empty sentinel
 * when count < 1.
 * Confidence: low */
word_t sk_r31_499e1c(long count)
{
    word_t uVar1;
    word_t *puVar2;
    long lVar3;

    if (count < 1) {
        puVar2 = &sk_d_00657778;
    } else {
        uVar1 = sk_h_00002534((word_t)&sk_d_0064c040, (word_t)&sk_d_004bbf40);
        puVar2 = (word_t *)sk_h_0036a940(uVar1, count * 0x20 + 0x20, 7);
        lVar3 = sk_h_000126e8();
        *(word_t *)(puVar2 + 0x10) = 0;
        *(long *)(puVar2 + 0x18) = (lVar3 - 0x20) / 0x20 << 1;
    }
    return (word_t)puVar2;
}

/* FUN_00499e94 @ 0x00499e94   (est. sk_r31_alloc_array_0x48)
 * Ghidra: undefined * FUN_00499e94(long)
 * Allocates a 0x48-byte-element array buffer of `count` slots; empty sentinel
 * when count < 1.
 * Confidence: low */
word_t sk_r31_499e94(long count)
{
    word_t uVar1;
    word_t *puVar2;
    long lVar3;

    if (count < 1) {
        puVar2 = &sk_d_00657778;
    } else {
        uVar1 = sk_h_00002534((word_t)&sk_d_00657d78, (word_t)&sk_d_005a4b40);
        puVar2 = (word_t *)sk_h_0036a940(uVar1, count * 0x48 + 0x20, 7);
        lVar3 = sk_h_000126e8();
        *(word_t *)(puVar2 + 0x10) = 0;
        *(long *)(puVar2 + 0x18) = (lVar3 - 0x20) / 0x48 << 1;
    }
    return (word_t)puVar2;
}

/* FUN_00499f0c @ 0x00499f0c   (est. sk_r31_diag_emit)
 * Ghidra: void FUN_00499f0c(undefined8)
 * Emits a diagnostic value to the debug stream with the context string from
 * register global unaff_x20+0x28, then forwards via FUN_00072a30.
 * Confidence: low
 * Notes: unaff_x20 register global. */
void sk_r31_499f0c(word_t v)
{
    word_t buf[9];
    word_t uVar1;

    sk_h_001a84f4((word_t)buf, *(word_t *)(0 + 0x28));
    sk_h_002298d4(v);
    uVar1 = sk_h_001a8564();
    sk_h_00072a30(v, uVar1);
}

/* FUN_00499f6c @ 0x00499f6c   (est. sk_r31_hash_probe)
 * Ghidra: void FUN_00499f6c(undefined8)
 * Hash-probe helper used by FUN_0049a184: seeds a scratch buffer with the
 * context string, hashes the value, flushes, and probes the table. The
 * decompiler dropped the 16-byte {slot,found} return that callers consume;
 * transcribed as returning sk_r31_pair_t (best-effort from the probe call).
 * Confidence: low
 * Notes: unaff_x20 register global; return reconstructed. */
sk_r31_pair_t sk_r31_499f6c(word_t v)
{
    word_t buf[9];
    word_t uVar1;
    sk_r31_pair_t r;

    sk_h_001a84f4((word_t)buf, *(word_t *)(0 + 0x28));
    sk_h_004a4184((word_t)buf, v);
    uVar1 = sk_h_001a8564();
    sk_r31_49a2a4(v, uVar1);
    r.lo = uVar1;
    r.hi = 0;
    return r;
}

/* FUN_00499fcc @ 0x00499fcc   (est. sk_r31_hashmap_insert_8)
 * Ghidra: void FUN_00499fcc(ulong, undefined8, undefined8, long)
 * Inserts (key -> v1, v2) into a hash map: sets the presence bit in the
 * parallel bitset at map+0x40 (word key>>6, bit key&0x3f), stores v1 at
 * map+0x30[key] and v2 at map+0x38[key], and increments the count at map+0x10.
 * Trap-fails on count overflow.
 * Confidence: medium
 * Notes: SoftwareBreakpoint(1,0x49a010). */
void sk_r31_499fcc(word_t key, word_t v1, word_t v2, long map)
{
    long lVar1;

    lVar1 = map + (key >> 6) * 8;
    *(ulong *)(lVar1 + 0x40) = *(ulong *)(lVar1 + 0x40) | (ulong)1 << (key & 0x3f);
    *(word_t *)(*(long *)(map + 0x30) + key * 8) = v1;
    *(word_t *)(*(long *)(map + 0x38) + key * 8) = v2;
    if (!SCARRY8(*(long *)(map + 0x10), 1)) {
        *(long *)(map + 0x10) = *(long *)(map + 0x10) + 1;
        return;
    }
    SK_TRAP(0x49a010);
}

/* FUN_0049a010 @ 0x0049a010   (est. sk_r31_hashmap_insert_16)
 * Ghidra: void FUN_0049a010(ulong, undefined8, undefined8, undefined8, long)
 * Inserts (key -> {v1,v2}, v3) into a hash map, storing the {v1,v2} pair as
 * a 16-byte value at map+0x30[key]. Trap-fails on count overflow.
 * Confidence: medium
 * Notes: SoftwareBreakpoint(1,0x49a058). */
void sk_r31_49a010(word_t key, word_t v1, word_t v2, word_t v3, long map)
{
    long lVar1;
    word_t *puVar2;

    lVar1 = map + (key >> 6) * 8;
    *(ulong *)(lVar1 + 0x40) = *(ulong *)(lVar1 + 0x40) | (ulong)1 << (key & 0x3f);
    puVar2 = (word_t *)(*(long *)(map + 0x30) + key * 0x10);
    puVar2[0] = v1;
    puVar2[1] = v2;
    *(word_t *)(*(long *)(map + 0x38) + key * 8) = v3;
    if (!SCARRY8(*(long *)(map + 0x10), 1)) {
        *(long *)(map + 0x10) = *(long *)(map + 0x10) + 1;
        return;
    }
    SK_TRAP(0x49a058);
}

/* FUN_0049a058 @ 0x0049a058   (est. sk_r31_hashmap_upsert_16)
 * Ghidra: void FUN_0049a058(undefined8, undefined8, undefined8)
 * Upserts a key into a hash map held at *unaff_x20. If the key's hash lookup
 * (FUN_0006ae9c) misses, grows the table if needed and inserts {v1,v2,key}
 * via FUN_0049a010, retaining the key; if present, overwrites the stored
 * value. Trap-fails on growth overflow or a hash-stability mismatch.
 * Confidence: medium
 * Notes: unaff_x20 = *map register global; FUN_002591b4 is a noreturn fatal
 * on hash instability. */
void sk_r31_49a058(word_t v1, word_t v2, word_t key)
{
    word_t uVar2, uVar3;
    long lVar4;
    ulong uVar5;
    long *unaff_x20;
    long lVar6;
    long lVar7;
    sk_r31_pair_t auVar8;
    sk_r31_pair_t auVar9;

    uVar2 = sk_h_003a261c(*unaff_x20);
    lVar6 = *unaff_x20;
    auVar8 = sk_h_0006ae9c(v2, key);
    lVar7 = auVar8.lo;
    lVar4 = *(long *)(lVar6 + 0x10);
    uVar5 = (ulong)(~auVar8.hi & 1);
    if (SCARRY8(lVar4, uVar5)) {
        SK_TRAP(0x49a174);
    }
    uVar3 = sk_h_00002534((word_t)&sk_d_00657df0, (word_t)&sk_d_005a4be0);
    uVar5 = sk_h_00258c60(uVar2, lVar4 + uVar5, uVar3);
    if ((uVar5 & 1) != 0) {
        auVar9 = sk_h_0006ae9c(v2, key);
        lVar7 = auVar9.lo;
        if ((auVar8.hi & 1) != (auVar9.hi & 1)) {
            sk_h_002591b4(0x6728f0);
        }
    }
    if ((auVar8.hi & 1) == 0) {
        sk_r31_49a010(lVar7, v1, v2, key, lVar6);
        sk_h_0036b270(key);
    } else {
        *(word_t *)(*(long *)(lVar6 + 0x38) + lVar7 * 8) = v1;
    }
    *unaff_x20 = lVar6;
}

/* FUN_0049a184 @ 0x0049a184   (est. sk_r31_hashmap_upsert_8)
 * Ghidra: void FUN_0049a184(undefined8, undefined8)
 * Upserts a key into a hash map held at *unaff_x20 using the FUN_00499f6c
 * probe; inserts {v2,v1} (with retain) via FUN_00499fcc when absent, else
 * overwrites. Fatal on hash instability.
 * Confidence: medium
 * Notes: unaff_x20 = *map register global. */
void sk_r31_49a184(word_t v1, word_t v2)
{
    word_t uVar2, uVar3;
    long lVar4;
    ulong uVar5;
    long *unaff_x20;
    long lVar6;
    long lVar7;
    sk_r31_pair_t auVar8;
    sk_r31_pair_t auVar9;

    uVar2 = sk_h_003a261c(*unaff_x20);
    lVar6 = *unaff_x20;
    auVar8 = sk_r31_499f6c(v2);
    lVar7 = auVar8.lo;
    lVar4 = *(long *)(lVar6 + 0x10);
    uVar5 = (ulong)(~auVar8.hi & 1);
    if (SCARRY8(lVar4, uVar5)) {
        SK_TRAP(0x49a288);
    }
    uVar3 = sk_h_00002534((word_t)&sk_d_00657e28, (word_t)&sk_d_005a5560);
    uVar5 = sk_h_00258c60(uVar2, lVar4 + uVar5, uVar3);
    if ((uVar5 & 1) != 0) {
        auVar9 = sk_r31_499f6c(v2);
        lVar7 = auVar9.lo;
        if ((auVar8.hi & 1) != (auVar9.hi & 1)) {
            sk_h_00002534((word_t)&sk_d_0064e078, (word_t)&sk_d_005a4b80);
            sk_h_002591b4(0, 0);
        }
    }
    if ((auVar8.hi & 1) == 0) {
        sk_r31_499fcc(lVar7, v2, v1, lVar6);
        sk_h_0036b270(v2);
    } else {
        *(word_t *)(*(long *)(lVar6 + 0x38) + lVar7 * 8) = v1;
    }
    *unaff_x20 = lVar6;
}

/* FUN_0049a2a4 @ 0x0049a2a4   (est. sk_r31_hashmap_lookup)
 * Ghidra: void FUN_0049a2a4(long, ulong)
 * Looks up a key in the hash map at register global unaff_x20 by probing the
 * bitset; when a slot is occupied, compares the key bytes (length at
 * key+0x10, payload at key+0x20) and stops at the first match or when the
 * probe chain ends.
 * Confidence: medium
 * Notes: unaff_x20 = map register global. */
void sk_r31_49a2a4(long key_ptr, ulong hash)
{
    ulong uVar1;
    long lVar2;
    long lVar3;
    char *pcVar4;
    char *pcVar5;

    uVar1 = (ulong)-1 << ((ulong)*(byte *)(0 + 0x20) & 0x3f);
    hash = hash & (uVar1 ^ 0xffffffffffffffff);
    if ((*(ulong *)(0 + 0x40 + (hash >> 6) * 8) >> (hash & 0x3f) & 1) != 0) {
        lVar2 = *(long *)(key_ptr + 0x10);
        do {
            lVar3 = *(long *)(*(long *)(0 + 0x30) + hash * 8);
            if (*(long *)(lVar3 + 0x10) == lVar2) {
                if ((lVar2 == 0) || (lVar3 == key_ptr)) {
                    return;
                }
                pcVar4 = (char *)(lVar3 + 0x20);
                pcVar5 = (char *)(key_ptr + 0x20);
                lVar3 = lVar2;
                while (true) {
                    if (*pcVar4 != *pcVar5) break;
                    lVar3 = lVar3 - 1;
                    pcVar4 = pcVar4 + 1;
                    pcVar5 = pcVar5 + 1;
                    if (lVar3 == 0) {
                        return;
                    }
                }
            }
            hash = hash + 1 & ~uVar1;
        } while ((*(ulong *)(0 + 0x40 + (hash >> 6) * 8) >> (hash & 0x3f) & 1) != 0);
    }
}

/* FUN_0049a348 @ 0x0049a348   (est. sk_r31_buffer_ensure_capacity)
 * Ghidra: void FUN_0049a348(long, uint, code *param_3)
 * Grows the buffer at *unaff_x20 via the supplied grow function when it is
 * not uniquely referenced or its capacity is below `count`.
 * Confidence: medium
 * Notes: unaff_x20 = *buffer register global. */
void sk_r31_49a348(long count, uint flag, void *grow_fn)
{
    long lVar1;
    word_t uVar2;
    long *unaff_x20;
    long lVar3;

    lVar3 = *unaff_x20;
    uVar2 = sk_h_003a261c(lVar3);
    *unaff_x20 = lVar3;
    if (((int)uVar2 == 0) || ((long)(*(ulong *)(lVar3 + 0x18) >> 1) < count)) {
        lVar1 = *(long *)(lVar3 + 0x10);
        if (*(long *)(lVar3 + 0x10) <= count) {
            lVar1 = count;
        }
        lVar3 = ((long (*)(word_t, long, uint, long))grow_fn)(uVar2, lVar1, flag & 1, lVar3);
        *unaff_x20 = lVar3;
    }
}

/* FUN_0049a3c0 @ 0x0049a3c0   (est. sk_r31_buffer_ensure_capacity2)
 * Ghidra: void FUN_0049a3c0(void)
 * Like FUN_0049a348 with the target size from FUN_0034d090 and a grow call
 * through a register-global function pointer (in_x5).
 * Confidence: low
 * Notes: unaff_x20/in_x5 register globals. */
void sk_r31_49a3c0(void)
{
    long lVar1, lVar3, lVar4;
    word_t uVar2;
    long *unaff_x20;
    sk_r31_pair_t auVar5;

    sk_h_00084220();
    auVar5 = sk_h_0034d090();
    lVar3 = auVar5.lo;
    lVar4 = *unaff_x20;
    uVar2 = sk_h_003a261c(lVar4);
    *unaff_x20 = lVar4;
    if (((int)uVar2 == 0) || ((long)(*(ulong *)(lVar4 + 0x18) >> 1) < lVar3)) {
        lVar1 = *(long *)(lVar4 + 0x10);
        if (*(long *)(lVar4 + 0x10) <= lVar3) {
            lVar1 = lVar3;
        }
        sk_h_004ab910(uVar2, lVar1, auVar5.hi & 1);
        /* (*in_x5)() register-global grow fn: dropped by decompiler */
        *unaff_x20 = lVar4;
    }
    sk_h_00084234(0);
}

/* The following wrappers (0x0049a440-0x0049a4b8) are the public buffer-
 * resize entry points: they resize the buffer at param_1 to its own current
 * element count (param_1+0x10), passing the element stride type. */

/* FUN_0049a440 @ 0x0049a440   (est. sk_r31_buffer_resize_wrap_a)
 * Ghidra: void FUN_0049a440(long)
 * Resize wrapper via FUN_0001dd14.
 * Confidence: low */
void sk_r31_49a440(long buf)
{
    sk_h_0001dd14(0, *(word_t *)(buf + 0x10), 0, buf);
}

/* FUN_0049a454 @ 0x0049a454   (est. sk_r31_buffer_resize_wrap_b)
 * Ghidra: void FUN_0049a454(long)
 * Resize wrapper via FUN_001a09bc.
 * Confidence: low */
void sk_r31_49a454(long buf)
{
    sk_h_001a09bc(0, *(word_t *)(buf + 0x10), 0, buf);
}

/* FUN_0049a468 @ 0x0049a468   (est. sk_r31_buffer_resize_wrap_c)
 * Ghidra: void FUN_0049a468(long)
 * Resize wrapper via sk_r31_498cc8 (0x48-stride).
 * Confidence: low */
void sk_r31_49a468(long buf)
{
    sk_r31_498cc8(0, *(ulong *)(buf + 0x10), 0, buf);
}

/* FUN_0049a47c @ 0x0049a47c   (est. sk_r31_buffer_resize_wrap_d)
 * Ghidra: void FUN_0049a47c(long)
 * Resize wrapper via thunk_FUN_001a0d1c.
 * Confidence: low */
void sk_r31_49a47c(long buf)
{
    sk_h_001a0d1c(0, *(word_t *)(buf + 0x10), 0, buf);
}

/* FUN_0049a490 @ 0x0049a490   (est. sk_r31_buffer_resize_wrap_e)
 * Ghidra: void FUN_0049a490(long)
 * Resize wrapper via sk_r31_498d8c (0x48-stride variant B).
 * Confidence: low */
void sk_r31_49a490(long buf)
{
    sk_r31_498d8c(0, *(ulong *)(buf + 0x10), 0, buf);
}

/* FUN_0049a4a4 @ 0x0049a4a4   (est. sk_r31_buffer_resize_wrap_f)
 * Ghidra: void FUN_0049a4a4(long)
 * Resize wrapper via sk_r31_498fd0.
 * Confidence: low */
void sk_r31_49a4a4(long buf)
{
    sk_r31_498fd0(0, *(ulong *)(buf + 0x10), 0, buf);
}

/* FUN_0049a4b8 @ 0x0049a4b8   (est. sk_r31_buffer_resize_wrap_g)
 * Ghidra: void FUN_0049a4b8(long)
 * Generic resize wrapper passing the 4-byte-element alloc (sk_r31_4982ac),
 * move (FUN_00071fe4) and done (FUN_00074a28) functions.
 * Confidence: low */
void sk_r31_49a4b8(long buf)
{
    sk_r31_498e50(0, *(long *)(buf + 0x10), 0, buf,
                  (void *)sk_r31_4982ac, (void *)sk_h_00071fe4, (void *)sk_h_00074a28);
}
