/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel, GL1,
 * arm64e, image base 0) — the cL4 microkernel. Ground truth: Ghidra FUN_ names +
 * addresses in cl4_kernel.raw. Version "cL4 microkernel (cL4 (679.100.61))".
 * All names are estimates unless string/header-matched.
 * Slice 0x3f41b8-0x3fabe8 (SKR59): the embedded Swift-runtime Array / generic
 * Collection buffer-management layer that cL4 uses for its message/object
 * queues. It implements the shared mutable array buffer (the 3-word descriptor
 * {capacity, count, elements-base} plus a per-element stride/layout word), the
 * index / offset arithmetic with bounds checking (after/before/advanced-by/
 * distance helpers), range replacement (replaceSubrange), element append /
 * prepend / remove-first / remove-last / remove-at / remove-subrange, and the
 * read/write subscript accessors plus their closures. Bounds violations raise
 * the standard Swift runtime traps ("Index out of bounds", "Index range out of
 * bounds", "Can't insert/remove element(s) at invalid index", "Invalid slice",
 * "Assertion failed", "Precondition failed", "Fatal error").
 *
 * Calling-convention notes: most functions take the array/collection "box" in
 * an early register and operate on a buffer object whose layout is
 * { +0x00 capacity, +0x08 count, +0x10 elements base } (the count/capacity
 * prefix), while +0x18.. are per-element stride / element layout words. The
 * 0/1/else parameter pattern seen throughout (op 0 unwrap/release-arg, op 1
 * copy-clone, else release-self) is the Swift boxed-value (copy/retain/release)
 * dispatcher. Ghidra FUN_ names are kept only in comments.
 */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>

#include "sk_internal.h"

typedef uint64_t word_t;
typedef int64_t  sword_t;
typedef unsigned char byte;

#ifndef ABS
#define ABS(x)  ((x) < 0 ? -(x) : (x))
#endif


/* 16-byte value returned in x0/x1 by many Swift helpers. */
typedef struct { unsigned long lo, hi; } cl4_pair_t;

/* SoftwareBreakpoint(1, addr) fail-closed trap. */
#define CL4_SW_BP(addr)  __asm__ volatile("brk #1" ::: "memory")

/* ---- Out-of-range cL4 helpers referenced by this region (FUN_ in comment).
 * Declared with unspecified-argument prototype (matching slice conventions);
 * their bodies are reconstructed by the range worker that owns them. ---- */
extern unsigned long sk_x_000026e8();   /* FUN_000026e8 (dealloc) */
extern unsigned long sk_x_0006a4c0();   /* FUN_0006a4c0 (context fetch) */
extern unsigned long sk_x_0006b6f4();   /* FUN_0006b6f4 */
extern unsigned long sk_x_00068e14();   /* FUN_00068e14 */
extern unsigned long sk_x_0007c028();   /* FUN_0007c028 */
extern unsigned long sk_x_0007c1a4();   /* FUN_0007c1a4 */
extern unsigned long sk_x_0007c1c4();   /* FUN_0007c1c4 */
extern unsigned long sk_x_000839d8();   /* FUN_000839d8 */
extern unsigned long sk_x_000839f8();   /* FUN_000839f8 */
extern unsigned long sk_x_0008409c();   /* FUN_0008409c */
extern unsigned long sk_x_00084174();   /* FUN_00084174 */
extern unsigned long sk_x_00084180();   /* FUN_00084180 */
extern unsigned long sk_x_00084220();   /* FUN_00084220 (16-byte) */
extern unsigned long sk_x_00084234();   /* FUN_00084234 (release) */
extern unsigned long sk_x_0008e160();   /* FUN_0008e160 (16-byte) */
extern unsigned long sk_x_0008e500();   /* FUN_0008e500 */
extern unsigned long sk_x_0008e518();   /* FUN_0008e518 (16-byte) */
extern unsigned long sk_x_000a68c4();   /* FUN_000a68c4 */
extern unsigned long sk_x_000a6894();   /* FUN_000a6894 */
extern unsigned long sk_x_000a68f4();   /* FUN_000a68f4 */
extern unsigned long sk_x_000a6f88();   /* FUN_000a6f88 */
extern unsigned long sk_x_000aa4ec();   /* FUN_000aa4ec */
extern unsigned long sk_x_000b4390();   /* FUN_000b4390 (16-byte) */
extern unsigned long sk_x_000bd3a4();   /* FUN_000bd3a4 */
extern unsigned long sk_x_000dbd0c();   /* FUN_000dbd0c (16-byte) */
extern unsigned long sk_x_000e46d0();   /* FUN_000e46d0 */
extern unsigned long sk_x_000e15d8();   /* FUN_000e15d8 */
extern unsigned long sk_x_00100c04();   /* FUN_00100c04 */
extern unsigned long sk_x_00100efc();   /* FUN_00100efc */
extern unsigned long sk_x_0014ae44();   /* FUN_0014ae44 */
extern unsigned long sk_x_0019cb68();   /* FUN_0019cb68 */
extern unsigned long sk_x_0019ce60();   /* FUN_0019ce60 */
extern unsigned long sk_x_0019dadc();   /* FUN_0019dadc */
extern unsigned long sk_x_0019f1ec();   /* FUN_0019f1ec */
extern unsigned long sk_x_0019fd10();   /* FUN_0019fd10 */
extern unsigned long sk_x_001a0194();   /* FUN_001a0194 */
extern unsigned long sk_x_001a26e0();   /* FUN_001a26e0 */
extern unsigned long sk_x_001a29a0();   /* FUN_001a29a0 (thunk) */
extern unsigned long sk_x_001a73cc();   /* FUN_001a73cc */
extern unsigned long sk_x_001afa84();   /* FUN_001afa84 (noreturn trap) */
extern unsigned long sk_x_001afe4c();   /* FUN_001afe4c (noreturn trap) */
extern unsigned long sk_x_001b6c4c();   /* FUN_001b6c4c */
extern unsigned long sk_x_001d3fd0();   /* FUN_001d3fd0 */
extern unsigned long sk_x_001d9890();   /* FUN_001d9890 */
extern unsigned long sk_x_001e4cbc();   /* FUN_001e4cbc */
extern unsigned long sk_x_00208418();   /* FUN_00208418 */
extern unsigned long sk_x_00251c40();   /* FUN_00251c40 */
extern unsigned long sk_x_00251638();   /* FUN_00251638 */
extern unsigned long sk_x_00251ecc();   /* FUN_00251ecc */
extern unsigned long sk_x_00252024();   /* FUN_00252024 */
extern unsigned long sk_x_002a4ab4();   /* FUN_002a4ab4 */
extern unsigned long sk_x_002acbb8();   /* FUN_002acbb8 (thunk) */
extern unsigned long sk_x_00310c44();   /* FUN_00310c44 */
extern unsigned long sk_x_00310d34();   /* FUN_00310d34 */
extern unsigned long sk_x_00310d68();   /* FUN_00310d68 */
extern unsigned long sk_x_00319308();   /* FUN_00319308 */
extern unsigned long sk_x_0031a14c();   /* FUN_0031a14c */
extern unsigned long sk_x_0031a17c();   /* FUN_0031a17c */
extern unsigned long sk_x_0031a1ac();   /* FUN_0031a1ac */
extern unsigned long sk_x_0031a26c();   /* FUN_0031a26c */
extern unsigned long sk_x_0031afcc();   /* FUN_0031afcc */
extern unsigned long sk_x_0031b080();   /* FUN_0031b080 */
extern unsigned long sk_x_0031b37c();   /* FUN_0031b37c */
extern unsigned long sk_x_0031d600();   /* FUN_0031d600 */
extern unsigned long sk_x_003191e8();   /* FUN_003191e8 */
extern unsigned long sk_x_00332168();   /* FUN_00332168 */
extern unsigned long sk_x_00347da8();   /* FUN_00347da8 (overflow trap) */
extern unsigned long sk_x_003488bc();   /* FUN_003488bc (fatal/overflow) */
extern unsigned long sk_x_003493d8();   /* FUN_003493d8 */
extern unsigned long sk_x_00349410();   /* FUN_00349410 */
extern unsigned long sk_x_0034a2f8();   /* FUN_0034a2f8 */
extern unsigned long sk_x_0034a210();   /* FUN_0034a210 */
extern unsigned long sk_x_0034a478();   /* FUN_0034a478 (msg trap) */
extern unsigned long sk_x_0034ab10();   /* FUN_0034ab10 */
extern unsigned long sk_x_0034ab20();   /* FUN_0034ab20 */
extern unsigned long sk_x_0034aee4();   /* FUN_0034aee4 */
extern unsigned long sk_x_0034b05c();   /* FUN_0034b05c */
extern unsigned long sk_x_0034b0d4();   /* FUN_0034b0d4 */
extern unsigned long sk_x_0034b460();   /* FUN_0034b460 */
extern unsigned long sk_x_0034ba48();   /* FUN_0034ba48 */
extern unsigned long sk_x_0034c2e8();   /* FUN_0034c2e8 */
extern unsigned long sk_x_0034d004();   /* FUN_0034d004 */
extern unsigned long sk_x_0034d2b4();   /* FUN_0034d2b4 (16-byte) */
extern unsigned long sk_x_0034e4ec();   /* FUN_0034e4ec */
extern unsigned long sk_x_00350298();   /* FUN_00350298 */
extern unsigned long sk_x_00350410();   /* FUN_00350410 (fail) */
extern unsigned long sk_x_00350428();   /* FUN_00350428 */
extern unsigned long sk_x_00350470();   /* FUN_00350470 (16-byte) */
extern unsigned long sk_x_00350488();   /* FUN_00350488 (16-byte) */
extern unsigned long sk_x_003504a0();   /* FUN_003504a0 */
extern unsigned long sk_x_003504ac();   /* FUN_003504ac */
extern unsigned long sk_x_003504b8();   /* FUN_003504b8 */
extern unsigned long sk_x_003504d0();   /* FUN_003504d0 (16-byte) */
extern unsigned long sk_x_003504e8();   /* FUN_003504e8 */
extern unsigned long sk_x_00350500();   /* FUN_00350500 (16-byte) */
extern unsigned long sk_x_0035050c();   /* FUN_0035050c (16-byte) */
extern unsigned long sk_x_00350518();   /* FUN_00350518 (16-byte) */
extern unsigned long sk_x_00350524();   /* FUN_00350524 */
extern unsigned long sk_x_0035053c();   /* FUN_0035053c */
extern unsigned long sk_x_00350548();   /* FUN_00350548 */
extern unsigned long sk_x_00350618();   /* FUN_00350618 (16-byte) */
extern unsigned long sk_x_00350624();   /* FUN_00350624 */
extern unsigned long sk_x_0035063c();   /* FUN_0035063c */
extern unsigned long sk_x_00350720();   /* FUN_00350720 (16-byte) */
extern unsigned long sk_x_00350738();   /* FUN_00350738 (16-byte) */
extern unsigned long sk_x_00350744();   /* FUN_00350744 */
extern unsigned long sk_x_00350798();   /* FUN_00350798 */
extern unsigned long sk_x_003507e0();   /* FUN_003507e0 (16-byte) */
extern unsigned long sk_x_00350878();   /* FUN_00350878 */
extern unsigned long sk_x_00350884();   /* FUN_00350884 */
extern unsigned long sk_x_00350974();   /* FUN_00350974 */
extern unsigned long sk_x_0035098c();   /* FUN_0035098c */
extern unsigned long sk_x_003509c8();   /* FUN_003509c8 */
extern unsigned long sk_x_003509ec();   /* FUN_003509ec */
extern unsigned long sk_x_00350a04();   /* FUN_00350a04 */
extern unsigned long sk_x_00350a64();   /* FUN_00350a64 */
extern unsigned long sk_x_00350ab8();   /* FUN_00350ab8 (16-byte) */
extern unsigned long sk_x_00350b54();   /* FUN_00350b54 */
extern unsigned long sk_x_00350bfc();   /* FUN_00350bfc */
extern unsigned long sk_x_00350c5c();   /* FUN_00350c5c */
extern unsigned long sk_x_00350d04();   /* FUN_00350d04 (fail) */
extern unsigned long sk_x_00351124();   /* FUN_00351124 (16-byte) */
extern unsigned long sk_x_0035128c();   /* FUN_0035128c */
extern unsigned long sk_x_00351330();   /* FUN_00351330 */
extern unsigned long sk_x_00351384();   /* FUN_00351384 (16-byte) */
extern unsigned long sk_x_003513b4();   /* FUN_003513b4 */
extern unsigned long sk_x_00351584();   /* FUN_00351584 */
extern unsigned long sk_x_003515b4();   /* FUN_003515b4 */
extern unsigned long sk_x_00351790();   /* FUN_00351790 */
extern unsigned long sk_x_003517b4();   /* FUN_003517b4 */
extern unsigned long sk_x_003518d0();   /* FUN_003518d0 */
extern unsigned long sk_x_003518dc();   /* FUN_003518dc */
extern unsigned long sk_x_00351a68();   /* FUN_00351a68 */
extern unsigned long sk_x_00351cd0();   /* FUN_00351cd0 */
extern unsigned long sk_x_00351da8();   /* FUN_00351da8 (16-byte) */
extern unsigned long sk_x_00351e3c();   /* FUN_00351e3c */
extern unsigned long sk_x_00351f10();   /* FUN_00351f10 */
extern unsigned long sk_x_003522b8();   /* FUN_003522b8 */
extern unsigned long sk_x_00352700();   /* FUN_00352700 */
extern unsigned long sk_x_00352758();   /* FUN_00352758 */
extern unsigned long sk_x_00352ae4();   /* FUN_00352ae4 */
extern unsigned long sk_x_00352efc();   /* FUN_00352efc */
extern unsigned long sk_x_0035300c();   /* FUN_0035300c (16-byte) */
extern unsigned long sk_x_00353238();   /* FUN_00353238 */
extern unsigned long sk_x_00353ccc();   /* FUN_00353ccc */
extern unsigned long sk_x_00353cfc();   /* FUN_00353cfc */
extern unsigned long sk_x_00353d14();   /* FUN_00353d14 */
extern unsigned long sk_x_00353d70();   /* FUN_00353d70 */
extern unsigned long sk_x_00353efc();   /* FUN_00353efc */
extern unsigned long sk_x_003539e4();   /* FUN_003539e4 */
extern unsigned long sk_x_00353f50();   /* FUN_00353f50 */
extern unsigned long sk_x_003565a8();   /* FUN_003565a8 (16-byte) */
extern unsigned long sk_x_00356590();   /* FUN_00356590 */
extern unsigned long sk_x_00356b80();   /* FUN_00356b80 */
extern unsigned long sk_x_00358298();   /* FUN_00358298 */
extern unsigned long sk_x_00359024();   /* FUN_00359024 */
extern unsigned long sk_x_0035ac70();   /* FUN_0035ac70 */
extern unsigned long sk_x_0036a908();   /* FUN_0036a908 (alloc) */
extern unsigned long sk_x_0036b118();   /* FUN_0036b118 (release) */
extern unsigned long sk_x_0036b270();   /* FUN_0036b270 (retain) */
extern unsigned long sk_x_003722e4();   /* FUN_003722e4 */
extern unsigned long sk_x_00376820();   /* FUN_00376820 (16-byte) */
extern unsigned long sk_x_00377824();   /* FUN_00377824 */
extern unsigned long sk_x_00377bec();   /* FUN_00377bec */
extern unsigned long sk_x_00377dcc();   /* FUN_00377dcc */
extern unsigned long sk_x_003f3b58();   /* FUN_003f3b58 */
extern unsigned long sk_x_003f3b9c();   /* FUN_003f3b9c */
extern unsigned long sk_x_003f3cfc();   /* FUN_003f3cfc (16-byte) */
extern unsigned long sk_x_003f3e64();   /* FUN_003f3e64 */
extern unsigned long sk_x_003f3ecc();   /* FUN_003f3ecc */
extern unsigned long sk_x_003f3f50();   /* FUN_003f3f50 */
extern unsigned long sk_x_003f4040();   /* FUN_003f4040 */
extern unsigned long sk_x_003f4164();   /* FUN_003f4164 */
extern unsigned long sk_x_0039a128();   /* FUN_0039a128 */
extern unsigned long sk_x_00404b8c();   /* FUN_00404b8c */
extern unsigned long sk_x_00404cf4();   /* FUN_00404cf4 */
extern unsigned long sk_x_00404d0c();   /* FUN_00404d0c (16-byte) */
extern unsigned long sk_x_00404d54();   /* FUN_00404d54 */
extern unsigned long sk_x_00404d84();   /* FUN_00404d84 */
extern unsigned long sk_x_00404d24();   /* FUN_00404d24 */
extern unsigned long sk_x_00404c60();   /* FUN_00404c60 */
extern unsigned long sk_x_00404c78();   /* FUN_00404c78 */
extern unsigned long sk_x_00404c08();   /* FUN_00404c08 */
extern unsigned long sk_x_00404cbc();   /* FUN_00404cbc */
extern unsigned long sk_x_00405830();   /* FUN_00405830 */
extern unsigned long sk_x_004058d4();   /* FUN_004058d4 */
extern unsigned long sk_x_00405848();   /* FUN_00405848 */
extern unsigned long sk_x_00405604();   /* FUN_00405604 */
extern unsigned long sk_x_0040567c();   /* FUN_0040567c */
extern unsigned long sk_x_00405904();   /* FUN_00405904 */
extern unsigned long sk_x_00405778();   /* FUN_00405778 */
extern unsigned long sk_x_00405a78();   /* FUN_00405a78 */
extern unsigned long sk_x_00405a44();   /* FUN_00405a44 */
extern unsigned long sk_x_00405a18();   /* FUN_00405a18 */
extern unsigned long sk_x_004059c0();   /* FUN_004059c0 */
extern unsigned long sk_x_004059ec();   /* FUN_004059ec */
extern unsigned long sk_x_00405994();   /* FUN_00405994 */
extern unsigned long sk_x_00405968();   /* FUN_00405968 */
extern unsigned long sk_x_00405b0c();   /* FUN_00405b0c */
extern unsigned long sk_x_00405b40();   /* FUN_00405b40 */
extern unsigned long sk_x_00405b70();   /* FUN_00405b70 */
extern unsigned long sk_x_00405b90();   /* FUN_00405b90 */
extern unsigned long sk_x_00405bc0();   /* FUN_00405bc0 */
extern unsigned long sk_x_00405ca0();   /* FUN_00405ca0 */
extern unsigned long sk_x_00405cd4();   /* FUN_00405cd4 */
extern unsigned long sk_x_00405da8();   /* FUN_00405da8 */
extern unsigned long sk_x_00405dcc();   /* FUN_00405dcc */
extern unsigned long sk_x_00405fb4();   /* FUN_00405fb4 */
extern unsigned long sk_x_0040621c();   /* FUN_0040621c */
extern unsigned long sk_x_00406310();   /* FUN_00406310 (fatal) */
extern unsigned long sk_x_0040633c();   /* FUN_0040633c (fatal) */
extern unsigned long sk_x_004063d0();   /* FUN_004063d0 */
extern unsigned long sk_x_004063f4();   /* FUN_004063f4 (fatal) */
extern unsigned long sk_x_00406478();   /* FUN_00406478 */
extern unsigned long sk_x_00406518();   /* FUN_00406518 */
extern unsigned long sk_x_00406678();   /* FUN_00406678 */
extern unsigned long sk_x_0040668c();   /* FUN_0040668c */
extern unsigned long sk_x_004066a4();   /* FUN_004066a4 */
extern unsigned long sk_x_0040677c();   /* FUN_0040677c */
extern unsigned long sk_x_0040697c();   /* FUN_0040697c */
extern unsigned long sk_x_00406d90();   /* FUN_00406d90 */
extern unsigned long sk_x_004070c0();   /* FUN_004070c0 (fatal) */
extern unsigned long sk_x_004070cc();   /* FUN_004070cc (fatal) */
extern unsigned long sk_x_00407254();   /* FUN_00407254 (fatal) */
extern unsigned long sk_x_004072cc();   /* FUN_004072cc */
extern unsigned long sk_x_00407300();   /* FUN_00407300 */
extern unsigned long sk_x_0040753c();   /* FUN_0040753c */
extern unsigned long sk_x_0040754c();   /* FUN_0040754c */
extern unsigned long sk_x_0040755c();   /* FUN_0040755c */
extern unsigned long sk_x_0040761c();   /* FUN_0040761c */
extern unsigned long sk_x_004076d8();   /* FUN_004076d8 */
extern unsigned long sk_x_00407710();   /* FUN_00407710 */
extern unsigned long sk_x_00407784();   /* FUN_00407784 */
extern unsigned long sk_x_00407790();   /* FUN_00407790 */
extern unsigned long sk_x_00407930();   /* FUN_00407930 */
extern unsigned long sk_x_00407984();   /* FUN_00407984 */
extern unsigned long sk_x_00407ab8();   /* FUN_00407ab8 */
extern unsigned long sk_x_00407b34();   /* FUN_00407b34 */
extern unsigned long sk_x_00407b54();   /* FUN_00407b54 */
extern unsigned long sk_x_00407b80();   /* FUN_00407b80 */
extern unsigned long sk_x_00407c20();   /* FUN_00407c20 */
extern unsigned long sk_x_00407d34();   /* FUN_00407d34 */
extern unsigned long sk_x_00407d44();   /* FUN_00407d44 */
extern unsigned long sk_x_00407d64();   /* FUN_00407d64 */
extern unsigned long sk_x_00407dd0();   /* FUN_00407dd0 */
extern unsigned long sk_x_00407ed0();   /* FUN_00407ed0 */
extern unsigned long sk_x_00407eac();   /* FUN_00407eac */
extern unsigned long sk_x_00407f18();   /* FUN_00407f18 */
extern unsigned long sk_x_00407f24();   /* FUN_00407f24 */
extern unsigned long sk_x_00407f54();   /* FUN_00407f54 */
extern unsigned long sk_x_00407ff0();   /* FUN_00407ff0 */
extern unsigned long sk_x_00408020();   /* FUN_00408020 */
extern unsigned long sk_x_00408118();   /* FUN_00408118 */
extern unsigned long sk_x_004081e4();   /* FUN_004081e4 */
extern unsigned long sk_x_004081f0();   /* FUN_004081f0 */
extern unsigned long sk_x_00408258();   /* FUN_00408258 */
extern unsigned long sk_x_00408294();   /* FUN_00408294 */
extern unsigned long sk_x_0040841c();   /* FUN_0040841c */
extern unsigned long sk_x_00408428();   /* FUN_00408428 */
extern unsigned long sk_x_004084c0();   /* FUN_004084c0 */
extern unsigned long sk_x_0040854c();   /* FUN_0040854c */
extern unsigned long sk_x_004085a8();   /* FUN_004085a8 */
extern unsigned long sk_x_004085f0();   /* FUN_004085f0 */

/* Global data slots referenced by this slice (Ghidra names in comments). */
extern word_t DAT_00658c80;   /* global Swift dispatch slot */
extern word_t DAT_00611b24;   /* element tag / metadata word */
extern sword_t DAT_006c0b80;  /* lazily-initialised global (=-1 until set) */
extern word_t DAT_006adf70;   /* retained global object */
extern double DAT_004e7cd0;   /* growth bound constant (1.5x growth) */

/* Out-of-range cL4 helpers referenced by later bodies (FUN_ in comment). */
extern unsigned long sk_x_00002534();   /* FUN_00002534 */
extern unsigned long sk_x_00027754();   /* FUN_00027754 */
extern unsigned long sk_x_000277b8();   /* FUN_000277b8 */
extern unsigned long sk_x_0001a1c8();   /* FUN_0001a1c8 */
extern unsigned long sk_x_00077888();   /* FUN_00077888 */
extern unsigned long sk_x_000836a4();   /* FUN_000836a4 */
extern unsigned long sk_x_000a6e14();   /* FUN_000a6e14 */
extern unsigned long sk_x_001f2ec4();   /* thunk_FUN_001f2ec4 */
extern unsigned long sk_x_0021867c();   /* FUN_0021867c */
extern unsigned long sk_x_0022b584();   /* FUN_0022b584 */
extern unsigned long sk_x_0028c754();   /* FUN_0028c754 */
extern unsigned long sk_x_003a25d4();   /* FUN_003a25d4 (release) */
extern unsigned long sk_x_00404654();   /* FUN_00404654 */
extern unsigned long sk_x_00404ba4();   /* FUN_00404ba4 */
extern unsigned long sk_x_00404db0();   /* FUN_00404db0 */
extern unsigned long sk_x_00404dc8();   /* FUN_00404dc8 */
extern unsigned long sk_x_00404ed8();   /* FUN_00404ed8 */
extern unsigned long sk_x_00404fdc();   /* FUN_00404fdc */
extern unsigned long sk_x_00405088();   /* FUN_00405088 */
extern unsigned long sk_x_004050b4();   /* FUN_004050b4 */
extern unsigned long sk_x_00405180();   /* FUN_00405180 */
extern unsigned long sk_x_00405374();   /* FUN_00405374 */
extern unsigned long sk_x_0040542c();   /* FUN_0040542c */

/* Retain/release of the (Swift) object at a given address. */
#define CL4_OBJ_RETAIN(p)  sk_x_0036b270((unsigned long)(p))
#define CL4_OBJ_RELEASE(p) sk_x_0036b118((unsigned long)(p))

/* The shared runtime trap entry points used throughout the array layer. */
#define CL4_TRAP_INDEX_OOB()  do { sk_x_0034a478((unsigned long)s_Index_out_of_bounds_005cdab0); sk_x_004063d0(); sk_x_00407254(); sk_x_001afa84(); } while (0)
#define CL4_TRAP_INDEX_RANGE_OOB() do { sk_x_0034a478((unsigned long)s_Index_range_out_of_bounds_005d35a0); sk_x_004063d0(); sk_x_00407254(); sk_x_001afa84(); } while (0)

/* String constants (addresses kept in comments). */
static const char s_Index_out_of_bounds_005cdab0[]  = "Index out of bounds";
static const char s_Index_range_out_of_bounds_005d35a0[] = "Index range out of bounds";
static const char s_Precondition_failed_005ce2d0[] = "Precondition failed";
static const char s_Assertion_failed_005ce250[]    = "Assertion failed";
static const char s_Fatal_error_005accd0[]         = "Fatal error";
static const char s_Invalid_slice_005cfa58[]       = "Invalid slice";
static const char s_Swift_UnsafeBufferPointer_swift_005cdc10[] = "Swift._UnsafeBufferPointer.swift";
static const char s_Closure_must_not_replace_the_pro_005dc4a0[] = "Closure must not replace the protocol witness";
static const char s_Can_t_insert_element_at_invalid_i_005dc5d0[] = "Can't insert element at invalid index";
static const char s_Can_t_insert_elements_at_an_inva_005dc5a0[] = "Can't insert elements at an invalid index";
static const char s_Cannot_remove_last_element_of_an_005dc570[] = "Cannot remove last element of an empty collection";
static const char s_Cannot_remove_first_element_of_a_005dc540[] = "Cannot remove first element of an empty collection";
static const char s_Can_t_remove_a_negative_number_o_005dc4d0[] = "Can't remove a negative number of elements";

/* ---- In-slice forward declarations (bodies follow in address order).
 * The array layer is register-fragment heavy; params are carried in the
 * Swift convention and bodies are faithful to the decompile. ---- */
static void sk_col_run_003f41b8(word_t a, word_t b);
static void sk_col_loop_003f4210(void);
static void sk_col_iter_003f441c(void);
static void sk_col_ins_003f4828(void);
static void sk_col_precond_003f4d48(void);
static void sk_col_assert_003f4ff4(void);
static void sk_col_setup_003f50fc(void);
static cl4_pair_t sk_col_descr_003f5190(void);
static void sk_col_register_003f5268(void);
static void sk_col_register2_003f52cc(void);
static word_t sk_col_tag_003f5338(void);
static word_t sk_col_tag2_003f539c(void);
static void sk_col_cfg_003f540c(void);
static void sk_col_reserve_003f54b0(word_t param_1);
static void sk_col_grow_003f54dc(word_t param_1);
static word_t sk_col_wrap_003f55a0(word_t *param_1, word_t param_2, word_t param_3);
static sword_t sk_col_grow1_5_003f568c(void);
static void sk_col_ensure_003f5780(void);
static void sk_col_reserve_n_003f5998(void);
static word_t sk_col_insert_hdr_003f5ad4(void);
static void sk_col_copy1_003f5c54(word_t *param_1, word_t param_2);
static void sk_col_copy2_003f5c64(word_t param_1, word_t param_2, sword_t *param_3, word_t param_4, word_t param_5);
static void sk_col_copy3_003f5cc4(void);
static void sk_col_ck_003f5cf0(sword_t *param_1);
static sword_t sk_col_next_003f5d1c(sword_t param_1, sword_t *param_2);
static sword_t sk_col_prev_003f5d80(sword_t param_1, sword_t *param_2);
static void sk_col_range_003f5de0(sword_t param_1, sword_t param_2, sword_t *param_3);
static void sk_col_range2_003f5e68(sword_t param_1);
static sword_t sk_col_off_003f5e78(sword_t param_1, sword_t *param_2);
static void sk_col_slice_003f5ee8(word_t param_1, word_t param_2, word_t param_3);
static void sk_col_copy4_003f5fc4(sword_t param_1, sword_t param_2, sword_t *param_3);
static void sk_col_rep_003f60e4(word_t param_1, word_t param_2, word_t param_3);
static void sk_col_rep2_003f612c(void);
static void sk_col_push_003f6174(word_t param_1, word_t param_2, word_t param_3);
static void sk_col_move_003f6278(sword_t param_1, word_t param_2, sword_t param_3, sword_t *param_4, word_t param_5, word_t param_6, word_t param_7, word_t fn);
static void sk_col_replace_003f637c(sword_t param_1, sword_t param_2, sword_t param_3, sword_t *param_4, word_t param_5, word_t param_6);
static void sk_col_pushback_003f648c(void);
static void sk_col_pushback1_003f6560(word_t param_1, sword_t param_2, word_t param_3, word_t param_4);
static void sk_col_pushback2_003f6668(word_t param_1, word_t param_2, sword_t *param_3);
static void sk_col_pushfront_003f6738(word_t param_1, word_t param_2, word_t param_3, word_t param_4);
static void sk_col_rm_003f684c(sword_t param_1, sword_t param_2, sword_t *param_3, word_t param_4, word_t param_5);
static void sk_col_fill_003f697c(void);
static void sk_col_rep3_003f6a8c(void);
static void sk_col_pop_copy_003f6e08(word_t param_1, sword_t param_2, word_t param_3, word_t param_4);
static void sk_col_pop_003f6ea8(word_t param_1, sword_t param_2, word_t param_3, word_t param_4);
static void sk_col_rm_first_003f6f3c(sword_t param_1, sword_t param_2, word_t param_3);
static void sk_col_rm_last_003f6fec(void);
static void sk_col_clear_003f709c(sword_t param_1);
static void sk_col_rm_range_003f70f8(sword_t param_1, word_t param_2, sword_t param_3);
static void sk_col_foreach_003f7464(word_t param_1, word_t param_2, word_t param_3, word_t param_4);
static cl4_pair_t sk_col_retain_003f761c(word_t param_1, word_t param_2);
static void sk_col_append_003f7648(word_t param_1, sword_t param_2, word_t param_3, word_t param_4);
static void sk_col_foreach2_003f7774(word_t param_1, sword_t param_2, word_t param_3);
static void sk_col_foreach3_003f7778(word_t param_1, sword_t param_2, word_t param_3);
static void sk_col_pump_003f77a0(void);
static void sk_col_pump1_003f79a0(word_t param_1, sword_t param_2);
static void sk_col_pump2_003f79d8(void);
static void sk_col_pump3_003f7a80(word_t *param_1, word_t param_2, sword_t param_3, word_t param_4);
static cl4_pair_t sk_col_box_003f7ab8(void);
static cl4_pair_t sk_col_box2_003f7b44(word_t param_1, word_t param_2, word_t param_3);
static word_t sk_col_box3_003f7bd8(void);
static word_t sk_col_box4_003f7cc4(void);
static void sk_col_copy5_003f7d48(sword_t param_1, sword_t param_2, sword_t param_3, sword_t param_4);
static cl4_pair_t sk_col_box5_003f7de0(word_t param_1, word_t param_2, word_t param_3, word_t param_4);
static void sk_col_slice2_003f7e8c(void);
static void sk_col_emit_003f8024(word_t param_1, word_t param_2, word_t param_3, word_t param_4, word_t param_5, word_t param_6);
static void sk_col_subget_003f80b4(word_t param_1, sword_t param_2, word_t param_3, word_t param_4);
static void sk_col_ret_003f8110(word_t param_1);
static word_t sk_col_subget2_003f8158(word_t param_1, word_t param_2, word_t param_3, sword_t param_4);
static void sk_col_subget3_003f819c(word_t param_1, word_t param_2, word_t param_3, sword_t param_4);
static void sk_col_subget4_003f81a0(word_t param_1, word_t param_2, word_t param_3, sword_t param_4);
static void sk_col_next2_003f81c4(void);
static void sk_col_set_003f8224(sword_t param_1, word_t param_2, sword_t param_3);
static void sk_col_subset_003f8264(word_t param_1, sword_t param_2, word_t param_3, word_t param_4);
static void sk_col_subset2_003f833c(word_t param_1, sword_t param_2, sword_t param_3);
static void sk_col_subset3_003f8458(word_t param_1, word_t param_2, sword_t param_3);
static void sk_col_free_003f861c(void);
static void sk_col_subget5_003f86e4(sword_t param_1, word_t param_2, word_t param_3, word_t param_4);
static void sk_col_subget6_003f87c8(void);
static void sk_col_getrange_003f88a8(word_t param_1, word_t param_2, word_t param_3, word_t param_4, word_t param_5, word_t param_6);
static cl4_pair_t sk_col_buf_003f8b88(word_t param_1, word_t param_2, word_t *param_3);
static void sk_col_len_003f8bb8(void);
static word_t sk_col_it_003f8be8(void);
static cl4_pair_t sk_col_acc_003f8c5c(sword_t *param_1, word_t param_2, word_t param_3, sword_t param_4);
static void sk_col_acc2_003f8d08(word_t param_1, word_t *param_2, sword_t param_3);
static void sk_col_acc3_003f8d48(void);
static void sk_col_acc4_003f8d98(sword_t param_1, word_t param_2, sword_t param_3);
static void sk_col_acc5_003f8ea8(word_t param_1, word_t param_2, sword_t param_3, word_t param_4);
static void sk_col_ckclos_003f8f60(sword_t *param_1, sword_t param_2, sword_t param_3);
static void sk_col_acc6_003f8fc0(word_t param_1, word_t param_2, word_t param_3, word_t param_4);
static word_t sk_col_mkit_003f8fe0(void);
static cl4_pair_t sk_col_mkacc_003f906c(void);
static void sk_col_mkacc2_003f90f0(void);
static void sk_col_wrap1_003f9178(word_t param_1, word_t param_2, word_t param_3);
static void sk_col_disp_003f91ec(word_t param_1, word_t param_2, word_t param_3, word_t param_4);
static void sk_col_disp2_003f91f0(word_t param_1, word_t param_2, word_t param_3, word_t param_4);
static void sk_col_disp3_003f9210(word_t param_1, word_t param_2, word_t param_3, word_t param_4);
static void sk_col_disp4_003f9214(word_t param_1, word_t param_2, word_t param_3, word_t param_4);
static void sk_col_splice_003f9234(word_t param_1, word_t param_2, sword_t param_3, sword_t param_4, sword_t param_5, word_t param_6, word_t param_7, sword_t param_8);
static word_t sk_col_rmat_003f96a4(word_t param_1, sword_t param_2, word_t param_3);
static word_t sk_col_rmat2_003f97bc(void);
static void sk_col_append_loop_003f983c(word_t param_1, word_t param_2, word_t param_3, word_t param_4);
static void sk_col_append_loop2_003f9bdc(void);
static void sk_col_setfirst_003f9cec(word_t param_1, word_t param_2, sword_t param_3, word_t param_4, word_t param_5, word_t param_6, word_t param_7, word_t param_8, word_t param_9, word_t param_10);
static void sk_col_append1_003f9e34(word_t param_1, word_t param_2, word_t *param_3, word_t param_4);
static void sk_col_fill2_003f9f4c(void);
static void sk_col_ins1_003fa038(word_t param_1, sword_t param_2, sword_t param_3);
static void sk_col_ins2_003fa168(word_t param_1, word_t param_2, sword_t param_3, word_t param_4, word_t *param_5, word_t param_6);
static void sk_col_ins3_003fa308(word_t param_1, word_t param_2, sword_t param_3, word_t param_4, word_t param_5);
static void sk_col_rep4_003fa478(void);
static void sk_col_subset4_003fa53c(word_t param_1, sword_t param_2, sword_t param_3);
static void sk_col_set2_003fa64c(sword_t param_1, word_t param_2, sword_t param_3);
static void sk_col_rmlast_003fa72c(sword_t param_1);
static word_t sk_col_rmn_003fa828(sword_t param_1);
static void sk_col_rmfirst_003fa910(sword_t param_1);
static void sk_col_rmn2_003fa9f8(sword_t param_1);
static void sk_col_pop1_003faadc(word_t param_1, sword_t param_2);
static void sk_col_pop2_003fab98(word_t *param_1, sword_t param_2);
static void sk_col_pop3_003fabe8(word_t *param_1, word_t param_2, word_t param_3, sword_t param_4);

/* ===================================================================== *
 * Function bodies (address order)
 * ===================================================================== */

/* FUN_003f41b8 @ 0x003f41b8   (est. sk_col_run_003f41b8)
 * Ghidra: void FUN_003f41b8(long param_1,long param_2)
 * Runs the given number of collection items: if a non-null context is
 * supplied the per-item helper is invoked (count, context); otherwise the
 * empty-buffer fatal trap path is taken (buffer absent). Returns silently
 * for a zero/negative count.
 * Confidence: medium
 * Notes: FUN_0019cb68 (item runner), FUN_003488bc/00407984/0034a2f8 then
 *   noreturn FUN_001afe4c = empty-container fatal. */
static void sk_col_run_003f41b8(word_t a, word_t b)
{
    if (b < 1) {
        return;
    }
    if (a != 0) {
        sk_x_0019cb68(b, a);
        return;
    }
    sk_x_003488bc(1);
    sk_x_00407984();
    sk_x_0034a2f8();
    sk_x_001afe4c();   /* does not return: empty-buffer fatal */
}

/* FUN_003f4210 @ 0x003f4210   (est. sk_col_loop_003f4210)
 * Ghidra: void FUN_003f4210(undefined8 param_1,...)
 * The core iteration/accumulation loop over a slice of the collection
 * buffer. Walks an element run maintained in an unspilled frame (unaff_x20):
 * when the low/high indices meet, either re-reads the "is empty / count"
 * flags (extend the run) or finishes by calling the 0008e500 epilogue with
 * the total count. Each step fetches a function pointer from the element
 * layout and drives the element copy/retain protocol via the callbacks.
 * Confidence: low (register-fragment heavy; the iteration/selection wiring
 *   is faithfully preserved but element stride details are inferred).
 * Notes: DAT_00658c80 global dispatch slot; SoftwareBreakpoint(1) overflow
 *   traps at 0x3f43f0 / 0x3f4398. */
static void sk_col_loop_003f4210(void)
{
    word_t *run;
    sword_t count;
    sword_t idx, end;
    int first;
    sword_t run_count;

    sk_x_0008e518();
    run = (word_t *)sk_x_00310d68();      /* extraout_x1-derived */
    sk_x_00350500();
    sk_x_00310d68();
    sk_x_000a6f88();
    sk_x_0007c1a4();
    (*(word_t (**)(void))DAT_00658c80)();
    sk_x_0034aee4();
    sk_x_0007c028();
    (*(word_t (**)(word_t))DAT_00658c80)(sk_x_00350ab8);
    sk_x_000aa4ec();

    first = 0;
    count = 0;
    idx = (word_t)run[0];            /* base element index */
    end = run[1];
    for (;;) {
        int again = 0;
        sword_t n = end;
        if (count == end) {
            if (!first) {
                n = run[3];
                first = (run[4] == 1);
                again = !first && n == 1;
                count = end;
                if (first || n < 1) goto finish;
                count = 0;
                idx = run[2];
                first = 1;
                goto advance;
            }
            count = end + n;
            if (__builtin_add_overflow(end, n, &count)) {
                __asm__ volatile("brk #1" ::: "memory");   /* SW BP 0x3f43f0 */
            }
        finish:
            sk_x_0008e500(count, 0);
            return;
        }
    advance:
        (*(void (**)(void))sk_x_000a68f4(0))(0, 0);
        sk_x_003518dc();
        sk_x_00350884();
        if (again) {
            (*(void (**)(void))(sk_x_00350ab8() + 8))();
            end = count;
            if (!first) goto finish;
            count = end + n;
            if (__builtin_add_overflow(end, n, &count)) {
                __asm__ volatile("brk #1" ::: "memory");
            }
        } else {
            word_t *slot = (word_t *)(sk_x_00350ab8() + 0x20);
            void (*emit)(word_t, word_t, word_t) = (void (*)(word_t, word_t, word_t))*slot;
            emit(slot[0], slot[1], run[0]);
            if (idx == 0) {
                sk_x_00350410();
                sk_x_003488bc();
                sk_x_00407984();
                sk_x_0034a2f8();
                sk_x_001afe4c();   /* does not return */
            }
            emit(((word_t)slot & 0xffffffffffffULL) | 0x48d8000000000000ULL,
                 idx + slot[9] * count, 0, 0);
            count++;
            end = n;
            if (__builtin_add_overflow(count, -1, &count)) {
                __asm__ volatile("brk #1" ::: "memory");   /* SW BP 0x3f4398 */
            }
        }
    }
}

/* FUN_003f441c @ 0x003f441c   (est. sk_col_iter_003f441c)
 * Ghidra: void FUN_003f441c(undefined8 param_1,...)
 * Enumerates the collection and, for a non-single-element container,
 * iterates element-by-element applying the per-element formatting helper
 * (UnsafeBufferPointer-style byte emission) using the stride at +0x48;
 * otherwise emits the whole buffer through the "write one" callback.
 * The final index is returned via the 0008e500 epilogue.
 * Confidence: medium
 * Notes: DAT_00658c80 dispatch slot; &DAT_00611b24 tag; SoftwareBreakpoint
 *   (1) at 0x3f47fc on index overflow. */
static void sk_col_iter_003f441c(void)
{
    word_t *buf;
    word_t *base;
    sword_t count, got;
    int is_single;

    sk_x_0008e518();
    sk_x_00310d68(0, 0);
    sk_x_000a6f88();
    sk_x_0007c1a4();
    (*(word_t (**)(void))DAT_00658c80)();
    sk_x_0034b0d4();
    sk_x_0007c028();
    (*(word_t (**)(word_t))DAT_00658c80)(0);
    sk_x_000aa4ec();
    sk_x_00407b80();
    sk_x_0007c028();
    (*(word_t (**)(word_t))DAT_00658c80)(0);
    sk_x_000aa4ec();

    base = (word_t *)buf[2];       /* element base */
    is_single = buf[4] == 1;
    if (!is_single) {
        count = buf[1];
        sk_x_000a6894(0);
        sk_x_003504ac();
        got = (sword_t)sk_x_00310d68();
        if (count < got) {
            sk_x_000a68c4(0);
            sk_x_003504ac();
            sk_x_00310d68();
            sk_x_00407f24();
            sk_x_00350488();
            sk_x_00377824(0, 0, 0, (word_t)&DAT_00611b24);
            sk_x_00407f18();
            sk_x_00350878(0);
            sk_x_00377bec();
            sk_x_000dbd0c();
            sk_x_0008e500(0, 0, 0);
            sk_col_loop_003f4210();
            return;
        }
    }
    sk_x_003504a0(0);
    sk_x_00310d68();
    base = (word_t *)buf[0];
    count = buf[1];
    sk_x_003191e8(0);
    got = (sword_t)sk_x_00310d68(base, count, 0, 0);
    if (got == count) {
        if (is_single) {
            sk_x_00084180(0);
            sk_x_00310d68();
            got = count;
        } else {
            word_t n = 0;
            word_t limit = buf[3] & ((sword_t)buf[3] >> 0x3f ^ -1ULL);
            while (n != limit) {
                sk_x_00407f24(0xff, 0, 0, (word_t)&DAT_00611b24);
                sk_x_00377824();
                sk_x_00350298(0);
                sk_x_00407f18();
                sk_x_00377bec();
                sk_x_00350798();
                sk_x_00377dcc();
                sk_x_00350884();
                (*(void (**)(word_t, word_t))(sk_x_00310d68() + 8))(0, 0);
                (*(void (**)(void))(sk_x_00350ab8() + 8))();
                if (base == 0) {
                    sk_x_00350410();
                    sk_x_003488bc();
                    sk_x_00407984();
                    sk_x_0034a2f8();
                    sk_x_001afe4c();   /* does not return */
                }
                (*(void (**)(word_t))(sk_x_00350ab8() + 0x20))(
                    ((word_t)sk_x_00350ab8() & 0xffffffffffffULL) | 0x48d8000000000000ULL,
                    base + sk_x_00350ab8() + 0x48 * n);
                n++;
            }
            sk_x_00084180(0);
            sk_x_00310d68();
            got = count + limit;
            if (__builtin_add_overflow(count, limit, &got)) {
                __asm__ volatile("brk #1" ::: "memory");   /* SW BP 0x3f47fc */
            }
        }
    } else {
        sk_x_00084180(0);
        sk_x_00310d68();
    }
    sk_x_0008e500(got, 0);
}

/* FUN_003f4828 @ 0x003f4828   (est. sk_col_ins_003f4828)
 * Ghidra: void FUN_003f4828(...)
 * Inserts a run of elements into the shared array buffer: validates the
 * collection state, then either appends via the single-element fast path or
 * splits into front/back halves around the insert point, driving the
 * element copy/retain protocol through the layout callbacks and re-wrapping
 * the boxed value (003f4d48). Falls to the noreturn fatal on failure.
 * Confidence: low (register-fragment heavy; exact element pointer math
 *   inferred from the +0x48 stride convention).
 * Notes: DAT_00658c80 dispatch slot; SoftwareBreakpoint(1) at 0x3f4d04. */
static void sk_col_ins_003f4828(void)
{
    word_t *frame;
    word_t *buf;
    word_t count, got;

    frame = (word_t *)sk_x_0008e518();
    sk_x_00407ed0();
    sk_x_00377824(0, 0);
    sk_x_00377bec(0, 0, 0);
    sk_x_00350720();
    sk_x_00319308(0, 0, 0);
    sk_x_000a6f88();
    sk_x_0007c1a4();
    (*(word_t (**)(void))DAT_00658c80)();
    sk_x_00350428();
    sk_x_00350488();
    sk_x_00377824(0, 0, 0);
    sk_x_000a6f88();
    sk_x_0007c1a4();
    (*(word_t (**)(void))DAT_00658c80)();
    sk_x_00350428();
    sk_x_00350720();
    sk_x_0031d600(0, 0, 0);
    sk_x_000a6f88();
    sk_x_0007c1a4();
    (*(word_t (**)(void))DAT_00658c80)();
    sk_x_00350428();
    sk_x_0007c028();
    (*(word_t (**)(word_t))DAT_00658c80)(0);
    sk_x_0034ab10();
    sk_x_00350ab8();
    sk_x_00310d68();
    (*(word_t (**)(void))DAT_00658c80)();
    sk_x_00310d68();
    sk_x_003f4040();
    sk_x_00353efc(0);
    sk_x_003504ac();
    got = (sword_t)sk_x_00310d68();
    if (sk_x_003f4040() != got) {
        sk_x_00350d04();
        sk_x_0040677c(0xb0);
        sk_x_00406518();
        sk_x_004085a8();
        __asm__ volatile("brk #1" ::: "memory");   /* SW BP 0x3f4d04 */
    }
    if (frame[4] == 1) {
        sk_col_precond_003f4d48(0, frame[0], frame[1], 0, 0, 0);
        (*(void (**)(word_t, word_t))(*(word_t *)(0 + -8) + 8))(0, 0);
        return;
    }
    sk_x_000277b8(0);
    sk_x_003504ac(0);
    sk_x_00310d68();
    buf = (word_t *)frame[2];
    sk_x_0031afcc(0);
    sk_x_00310d68(0, 0, 0, 0, 0);
    sk_x_000dbd0c();
    sk_x_00310d68();
    sk_x_00027754(0);
    sk_x_0014ae44();
    sk_x_00407c20();
    got = (sword_t)sk_x_00310d68();
    if ((got & 1) == 0) {
        sk_x_00350410();
        sk_x_003488bc();
    } else {
        (*(void (**)(word_t, word_t, word_t))(sk_x_00350ab8() + 0x10))(0, 0, 0);
        sk_x_000dbd0c();
        sk_x_00310d68();
        sk_x_0040668c();
        sk_x_00351e3c(0, 0, 0);
        sk_x_001d9890();
        (*(void (**)(word_t, word_t))(sk_x_00350ab8() + 8))(0, 0);
        sk_x_00408294();
        sk_x_00377bec(0, 0, 0);
        sk_col_precond_003f4d48(0, buf[0], buf[1], 0, 0, 0);
        (*(void (**)(word_t, word_t))(sk_x_00350ab8() + 8))(0, 0);
        sk_x_00027754(0);
        sk_x_0014ae44();
        sk_x_00407c20();
        got = (sword_t)sk_x_00310d68();
        if ((got & 1) != 0) {
            sk_x_00310d68(0, 0, 0, 0);
            sk_x_00407300();
            sk_x_00084180(0);
            sk_x_00351e3c();
            sk_x_001d9890();
            sk_x_003509c8(0);
            (*(void (**)(word_t, word_t))(sk_x_00350ab8() + 8))(0, 0);
            (*(void (**)(word_t, word_t))(sk_x_00350ab8() + 8))(0, 0);
            sk_col_precond_003f4d48(0, buf[2], buf[3], 0, 0, 0);
            (*(void (**)(word_t, word_t))(sk_x_00350ab8() + 8))(0, 0);
            sk_x_0008e500(0, 0);
            return;
        }
        sk_x_00350410();
        sk_x_003488bc();
    }
    sk_x_00349410();
    sk_x_003504b8();
    sk_x_001afe4c();   /* does not return */
}

/* FUN_003f4d48 @ 0x003f4d48   (est. sk_col_precond_003f4d48)
 * Ghidra: void FUN_003f4d48(undefined8 param_1,undefined8 param_2,long param_3,
 *                           undefined8 param_4,undefined8 param_5,undefined8 param_6)
 * Swift "Precondition failed" wrapper: verifies an equality/positional
 * invariant on the collection, and on success rewraps the boxed value; on
 * failure formats the assertion message ("Precondition failed") plus the
 * 0x2b/0x2c range-code and raises the noreturn runtime trap.
 * Confidence: low (register-fragment heavy)
 * Notes: s_Precondition_failed_005ce2d0; FUN_0040677c(0x29) range name. */
static void sk_col_precond_003f4d48(word_t a, word_t b, word_t c, word_t d, word_t e, word_t f)
{
    word_t *sp;
    sword_t result, expect;
    const char *msg;

    sk_x_0008e518();
    expect = (sword_t)c;
    sk_x_003517b4();
    sk_x_00310d68(0, 0);
    sk_x_000a6f88();
    sk_x_0007c1a4();
    (*(word_t (**)(void))DAT_00658c80)();
    sk_x_0034aee4();
    sk_x_0007c028();
    (*(word_t (**)(word_t))DAT_00658c80)(0);
    sk_x_000aa4ec();
    sk_x_0040841c();
    sk_x_00027754(f);
    sk_x_00407eac();
    sk_x_00407f24();
    sk_x_00350488();
    sk_x_00377824(0, 0, e);
    sk_x_000a6f88();
    sk_x_0007c1a4();
    (*(word_t (**)(void))DAT_00658c80)();
    sk_x_0034aee4();
    sk_x_00353efc(f);
    result = (sword_t)sk_x_00350ab8();
    if (result == expect) {
        (*(void (**)(void))(sk_x_00350ab8() + 0x10))();
        sk_x_003191e8(d);
        result = (sword_t)sk_x_00310d68();
        if (result == expect) {
            sk_x_00407eac();
            sk_x_00407f18();
            sk_x_00377bec(0, e, 0);
            (*(void (**)(void))sk_x_000a68f4())();
            sk_x_00350884(0, 1, 0);
            sk_x_00350a04(*(word_t *)(sk_x_00350ab8() + 8));
            (*(void (**)(void))sk_x_00350ab8())();
            (*(void (**)(word_t, word_t))(sk_x_00350ab8() + 8))(0, 0);
            sk_x_0008e500(0);
            return;
        }
        (*(void (**)(word_t, word_t))(sk_x_00350ab8() + 8))(0, 0);
        *sp = 1;
        result = 0x2c;
    } else {
        sk_x_00350d04();
        result = 0x2b;
    }
    msg = s_Precondition_failed_005ce2d0;
    sk_x_004070c0((word_t)msg, (word_t)result, 2);
    sk_x_001afa84();   /* does not return */
}

/* FUN_003f4ff4 @ 0x003f4ff4   (est. sk_col_assert_003f4ff4)
 * Ghidra: void FUN_003f4ff4(void)
 * Asserts the collection iterator position matches the stored cursor
 * (003f4040); on match, continues the insert helper (003f4164 -> 000bd3a4
 * -> sk_col_ins_003f4828) and returns; on mismatch raises the assertion
 * trap ("Assertion failed", code 0xbd).
 * Confidence: low
 * Notes: SoftwareBreakpoint(1) at 0x3f50fc. */
static void sk_col_assert_003f4ff4(void)
{
    sword_t got;

    sk_x_0008e518();
    sk_x_0034c2e8();
    sk_x_0007c028();
    (*(word_t (**)(word_t))DAT_00658c80)(0);
    sk_x_000aa4ec();
    sk_x_00407784();
    sk_x_00353efc(0);
    sk_x_00100efc();
    got = (sword_t)sk_x_00310d68();
    if (got == sk_x_003f4040()) {
        sk_x_003f4164();
        (*(void (**)(void))(sk_x_00350ab8() + 0x10))();
        sk_x_000bd3a4();
        sk_col_ins_003f4828();
        sk_x_0008e500(0);
        return;
    }
    sk_x_00350d04();
    sk_x_0040677c(0xbd);
    sk_x_00406518();
    sk_x_004085a8();
    __asm__ volatile("brk #1" ::: "memory");   /* SW BP 0x3f50fc */
}

/* FUN_003f50fc @ 0x003f50fc   (est. sk_col_setup_003f50fc)
 * Ghidra: void FUN_003f50fc(void)
 * Small setup shim: obtains the 16-byte context, builds the collection
 * element handle (retain tag 0xff via 00377824), runs the buffer-format /
 * index helpers (00352efc, 00310d34, 00310c44) and finishes with the
 * 000a6e14 run helper.
 * Confidence: low */
static void sk_col_setup_003f50fc(void)
{
    sk_x_0034d2b4();
    sk_x_00407eac();
    sk_x_00377824(0xff);
    sk_x_00352efc();
    sk_x_00310d34();
    sk_x_00310c44();
    sk_x_000a6e14(0);
    sk_x_00310d68();
}

/* FUN_003f5190 @ 0x003f5190   (est. sk_col_descr_003f5190)
 * Ghidra: undefined1[16] FUN_003f5190(void)
 * Returns the 16-byte "current collection" descriptor: runs the context
 * setup (0008409c, 00100c04), reads the two tagged words from the state
 * (002a4ab4(0x14), 003a25d4), emits the "Stored.as.Array" type name via the
 * 002acbb8 encoder with the tag payloads, and resolves the buffer object
 * (00251ecc -> 003f3b9c) before returning the pair.
 * Confidence: medium
 * Notes: string-fragment tag 0x61726f74535f2e3e/0xea00000000006567
 *   ("...STora"/"ge..." little-endian). */
static cl4_pair_t sk_col_descr_003f5190(void)
{
    cl4_pair_t out;
    word_t *p;

    sk_x_0008409c();
    sk_x_00100c04();
    sk_x_002a4ab4(0x14);
    sk_x_003a25d4(0);
    sk_x_00408258();
    sk_x_00208418();
    sk_x_002acbb8();
    sk_x_003a25d4(0);
    sk_x_002acbb8(0x61726f74535f2e3eULL, 0xea00000000006567ULL);
    p = (word_t *)sk_x_00251ecc();
    sk_x_003f3b9c(p[0], p[1], p[2]);
    sk_x_002acbb8();
    sk_x_003a25d4(0);
    out.lo = sk_x_00310d68();
    out.hi = sk_x_00350ab8();
    return out;
}

/* FUN_003f5268 @ 0x003f5268   (est. sk_col_register_003f5268)
 * Ghidra: void FUN_003f5268(void)
 * One-time registration of the collection buffer manager: if the lazily
 * initialised global (DAT_006c0b80) is still unset, installs the
 * 003f3b58 handler via 0039a128; then retains the global element object
 * (DAT_006adf70) and finishes with the buffer-finalise helpers
 * (00407710 -> 00251c40).
 * Confidence: medium */
static void sk_col_register_003f5268(void)
{
    if (DAT_006c0b80 != -1) {
        sk_x_0039a128((word_t)&DAT_006c0b80, (word_t)sk_x_003f3b58);
    }
    CL4_OBJ_RETAIN(DAT_006adf70);
    sk_x_00407710();
    sk_x_00251c40();
}

/* FUN_003f52cc @ 0x003f52cc   (est. sk_col_register2_003f52cc)
 * Ghidra: void FUN_003f52cc(void)
 * Second registration/teardown shim: runs the context helper (003517b4),
 * the element-format setup (00404654), the buffer-finalise (00251638,
 * 00407710, 00251c40). Mirrors sk_col_register_003f5268 without the
 * lazy-global guard.
 * Confidence: low */
static void sk_col_register2_003f52cc(void)
{
    sk_x_003517b4();
    sk_x_00404654();
    sk_x_00251638();
    sk_x_00407710();
    sk_x_00251c40();
}

/* FUN_003f5338 @ 0x003f5338   (est. sk_col_tag_003f5338)
 * Ghidra: undefined8 FUN_003f5338(void)
 * Reads a tagged word from the current collection context using the 000af3f8
 * data pattern: initialises the context (00407930), decodes the tag via
 * 001b6c4c(&out, LAB_000af3f8, 0) and returns the decoded value.
 * Confidence: low
 * Notes: LAB_000af3f8 is a data/string reference in the context block. */
static word_t sk_col_tag_003f5338(void)
{
    word_t out;
    sk_x_00407930();
    sk_x_001b6c4c((word_t)&out, (word_t)0x000af3f8, 0);
    return out;
}

/* FUN_003f539c @ 0x003f539c   (est. sk_col_tag2_003f539c)
 * Ghidra: undefined8 FUN_003f539c(void)
 * Reads the collection's current count/length: initialises the context
 * (00407930) and decodes the count tag via 001b6c4c(&out, LAB_003f5400, 0).
 * This is the central "how many elements" getter used by the whole slice.
 * Confidence: medium
 * Notes: LAB_003f5400 is the count tag/data pattern. */
static word_t sk_col_tag2_003f539c(void)
{
    word_t out;
    sk_x_00407930();
    sk_x_001b6c4c((word_t)&out, (word_t)0x003f5400, 0);
    return out;
}

/* FUN_003f540c @ 0x003f540c   (est. sk_col_cfg_003f540c)
 * Ghidra: void FUN_003f540c(void)
 * Configures the current collection run: sets the element layout words from
 * the in_x3/in_x4 values, runs the element-setup (0034a210, 00002534) and
 * installs the run via 00252024(extra, in_x5, stack-block).
 * Confidence: low */
static void sk_col_cfg_003f540c(void)
{
    word_t v3, v4, v5;
    word_t stack[2];
    (void)v3; (void)v4; (void)v5;
    sk_x_0034d2b4();
    sk_x_0034a210();
    sk_x_00002534();
    sk_x_00252024(0, 0, (word_t)&stack[0]);
}

/* FUN_003f54b0 @ 0x003f54b0   (est. sk_col_reserve_003f54b0)
 * Ghidra: void FUN_003f54b0(long param_1)
 * Reserve-capacity probe: asks 00332168(0, 0x67f000, elements(param_1+0x10))
 * whether the buffer has room for the requested element count; the returned
 * value (a boolean "has capacity" flag in the low bit) propagates through
 * thunk_FUN_001f2ec4.
 * Confidence: medium
 * Notes: 0x67f000 is the array-buffer metadata tag. */
static void sk_col_reserve_003f54b0(word_t param_1)
{
    sk_x_00332168(0, 0x67f000, *(word_t *)(param_1 + 0x10));
    sk_x_001f2ec4();
}

/* FUN_003f54dc @ 0x003f54dc   (est. sk_col_grow_003f54dc)
 * Ghidra: void FUN_003f54dc(long param_1)
 * Ensures capacity for the collection boxed in unaff_x20: if the reserve
 * probe (sk_col_reserve_003f54b0) succeeds nothing is done; otherwise it
 * reconfigures the box (003f540c with the 0040621c formatter and the
 * 00404c60 initialiser), releasing the old boxed object and storing the
 * new configuration back into *unaff_x20.
 * Confidence: low */
static void sk_col_grow_003f54dc(word_t param_1)
{
    word_t *box;
    word_t newcfg;

    if ((sk_x_003f54b0() & 1) != 0) {
        return;
    }
    box = (word_t *)sk_x_00350ab8();
    sk_x_003f540c((word_t)&newcfg, (word_t)sk_x_0040621c, 0, box[0],
                  *(word_t *)(param_1 + 0x10), param_1, (word_t)sk_x_00404c60);
    CL4_OBJ_RELEASE(box[0]);
    *box = newcfg;
}

/* FUN_003f55a0 @ 0x003f55a0   (est. sk_col_wrap_003f55a0)
 * Ghidra: undefined8 FUN_003f55a0(undefined8 *param_1,...)
 * Wraps the boxed collection (param_1/param_2) in a retained run: configures
 * the buffer formatter (00251638 with LAB_00404db0), and when the collection
 * is non-empty, installs a closure thunk storing param_1/param_2/param_3 in
 * the run frame (00359024), re-emits via 0035053c(00404dc8) and reconfigures
 * through sk_col_cfg_003f540c. Returns the run cursor.
 * Confidence: low */
static word_t sk_col_wrap_003f55a0(word_t *param_1, word_t param_2, word_t param_3)
{
    word_t *run;
    word_t result;

    sk_x_00350a64();
    sk_x_00404654();
    run = param_1;
    sk_x_00251638(*param_1, (word_t)0x00404db0, 0);
    sk_x_00407710();
    result = sk_x_00251c40();
    if (0 < (sword_t)param_1[1]) {
        sk_x_004081e4();
        (*(word_t (**)(void))DAT_00658c80)();
        sk_x_003539e4();
        *(word_t *)(sk_x_00350ab8() + -0x20) = param_3;
        *(word_t **)(sk_x_00350ab8() + -0x18) = param_1;
        *(word_t *)(sk_x_00350ab8() + -0x10) = param_2;
        sk_x_00359024();
        sk_x_0035053c((word_t)sk_x_00404dc8);
        sk_col_cfg_003f540c();
    }
    return result;
}

/* FUN_003f568c @ 0x003f568c   (est. sk_col_grow1_5_003f568c)
 * Ghidra: long FUN_003f568c(undefined8 param_1,...)
 * Computes the grown element count = max(current, floor(count * 1.5)) with
 * full floating-point growth overflow handling. If the requested count is
 * already flagged (unaff_x20 & 1) the max is taken directly; otherwise the
 * count is multiplied by 1.5 in double precision and converted back, raising
 * the fatal growth-overflow trap (003488bc/003493d8) on NaN/too-large.
 * Confidence: medium
 * Notes: DAT_004e7cd0 is the growth bound; 9.223372036854776e+18 = 2^63. */
static sword_t sk_col_grow1_5_003f568c(void)
{
    sword_t lVar1;
    double dVar2;

    sk_x_00350c5c();
    lVar1 = (sword_t)sk_col_tag_003f5338(0, 0);
    if ((sk_x_00350ab8() & 1) != 0) {
    grow_ret:
        {
            word_t cur = sk_x_00350ab8();
            if (cur <= (word_t)lVar1) {
                cur = (word_t)lVar1;
            }
            return (sword_t)cur;
        }
    }
    dVar2 = (double)(sword_t)((double)lVar1 * 1.5);
    if (ABS(dVar2) < 0x7ff0000000000000ULL) {
        if (dVar2 <= DAT_004e7cd0) {
            sk_x_003488bc(1);
            sk_x_003493d8();
        } else if (dVar2 < 9.223372036854776e+18) {
            lVar1 = (sword_t)dVar2;
            goto grow_ret;
        } else {
            sk_x_003488bc(1);
            sk_x_003493d8();
        }
    } else {
        sk_x_003488bc(1);
        sk_x_003493d8();
    }
    sk_x_001afe4c();   /* does not return */
}

/* FUN_003f5780 @ 0x003f5780   (est. sk_col_ensure_003f5780)
 * Ghidra: void FUN_003f5780(long param_1,uint param_2,long param_3)
 * Ensures the boxed collection (unaff_x20, elements at param_3+0x10) has
 * room for at least param_1 elements, growing the buffer (sk_col_grow_1_5_)
 * when needed and reconfiguring via sk_col_cfg_003f540c with one of the
 * formatter closures (00404d54 / 00404d24 / 00404d84) depending on whether
 * growth happened and the reserve-flag state. The low bit of param_2 selects
 * growth semantics.
 * Confidence: low */
static void sk_col_ensure_003f5780(void)
{
    word_t *box;
    word_t elem, count;
    word_t v, v2, fmt, init;

    if ((sk_x_003f54b0(0) & 1) != 0 &&
        (sword_t)(count = sk_col_tag2_003f539c(*box, *(word_t *)(0 + 0x10))) >= 0 &&
        (sword_t)count >= (sword_t)sk_x_00350ab8()) {
        return;
    }
    box = (word_t *)sk_x_00350ab8();
    elem = box[0];
    count = *(word_t *)(0 + 0x10);
    sk_x_003504ac();
    sk_col_tag2_003f539c();
    sk_x_003f54b0(0);
    if ((sword_t)count < (sword_t)sk_x_00350ab8()) {
        sk_col_grow1_5_003f568c((word_t)sk_x_00350ab8(), (word_t)(sk_x_00350ab8() & 1), elem, count);
        if ((sk_x_003f54b0(0) & 1) != 0) {
            (*(word_t (**)(void))DAT_00658c80)();
            v = sk_x_0008e160();
            v2 = sk_x_00350ab8();
            *(word_t *)(sk_x_00350ab8() + -0x10) = count;
            *(word_t *)(sk_x_00350ab8() + -8) = sk_x_00350ab8();
            fmt = (word_t)sk_x_00404d54;
            init = (word_t)sk_x_00405fb4;
            goto cfg;
        }
        (*(word_t (**)(void))DAT_00658c80)();
        v = sk_x_0008e160();
        v2 = sk_x_00350ab8();
        *(word_t *)(sk_x_00350ab8() + -0x10) = count;
        *(word_t *)(sk_x_00350ab8() + -8) = sk_x_00350ab8();
        fmt = (word_t)sk_x_00404d24;
    } else {
        if ((sk_x_003f54b0(0) & 1) != 0) {
            sk_x_00350d04();
            sk_x_0040677c(0xa7);
            sk_x_00406518();
            sk_x_001afa84();   /* does not return */
        }
        (*(word_t (**)(void))DAT_00658c80)();
        sk_x_0008e160();
        *(word_t *)(sk_x_00350ab8() + -0x10) = count;
        fmt = (word_t)sk_x_00404d84;
        v2 = sk_x_00350ab8();
    }
    init = (word_t)sk_x_00404c60;
cfg:
    sk_col_cfg_003f540c((word_t)(void *)&count, fmt, v2, elem, count, 0, init);
    CL4_OBJ_RELEASE(elem);
    *box = sk_x_00350ab8();
    sk_x_00084234(0);
}

/* FUN_003f5998 @ 0x003f5998   (est. sk_col_reserve_n_003f5998)
 * Ghidra: void FUN_003f5998(undefined8 param_1,...)
 * Reserves space for an additional element in the shared buffer: if the
 * current count is still within capacity it re-runs the buffer formatter
 * (00251c40) storing the run metadata and resets the count; otherwise raises
 * the capacity overflow trap (code 0x122).
 * Confidence: low */
static void sk_col_reserve_n_003f5998(void)
{
    sword_t cap;

    cap = (sword_t)sk_x_00084220() & 0;
    cap = (sword_t)sk_x_00350ab8() + 0;
    if (cap <= (sword_t)sk_x_00350ab8()) {
        sk_x_003517b4();
        sk_x_00404654(0, 0);
        (*(word_t (**)(void))DAT_00658c80)();
        sk_x_0040854c();
        sk_x_00251c40(0, 0x67f000, 0);
        if (0 < cap) {
            sk_x_004081e4();
            (*(word_t (**)(void))DAT_00658c80)();
            sk_x_003539e4();
            *(word_t *)(sk_x_00350ab8() + -0x20) = 0;
            *(word_t *)(sk_x_00350ab8() + -0x18) = sk_x_00350ab8();
            *(word_t *)(sk_x_00350ab8() + -0x10) = 0;
            sk_x_00359024();
            sk_col_cfg_003f540c((word_t)sk_x_00404ed8, 0, 0, 0, 0, (word_t)sk_x_00405fb4);
            *(word_t *)(sk_x_00350ab8() + 8) = 0;
        }
        sk_x_00084234(0, 0);
        return;
    }
    sk_x_00350d04();
    sk_x_00406310(0x122);
    sk_x_001afa84();   /* does not return */
}

/* FUN_003f5ad4 @ 0x003f5ad4   (est. sk_col_insert_hdr_003f5ad4)
 * Ghidra: undefined8 FUN_003f5ad4(long param_1,long param_2,...)
 * Insert-header fast path: if the collection count (param_2+8) is within the
 * requested index, runs the buffer formatter and stores the insertion
 * metadata (param_3/param_4) via sk_col_cfg_003f540c with the 00404fdc
 * closure; otherwise raises the index-overflow trap (0x101).
 * Confidence: low */
static word_t sk_col_insert_hdr_003f5ad4(void)
{
    word_t result;

    if (*(sword_t *)(0 + 8) <= (sword_t)sk_x_00350ab8()) {
        sk_x_0035128c();
        sk_x_003517b4();
        sk_x_00404654(0, 0);
        (*(word_t (**)(void))DAT_00658c80)();
        sk_x_0040854c();
        sk_x_00407710();
        result = sk_x_00251c40();
        if (0 < *(sword_t *)(sk_x_00350ab8() + 8)) {
            sk_x_004081e4();
            (*(word_t (**)(void))DAT_00658c80)();
            sk_x_003539e4();
            *(word_t *)(sk_x_00350ab8() + -0x20) = 0;
            *(word_t *)(sk_x_00350ab8() + -0x18) = sk_x_00350ab8();
            *(word_t *)(sk_x_00350ab8() + -0x10) = sk_x_00350ab8();
            sk_x_00359024();
            sk_x_0035053c((word_t)sk_x_00404fdc);
            sk_col_cfg_003f540c();
        }
        return result;
    }
    sk_x_00350d04();
    sk_x_00406310(0x101);
    sk_x_001afa84();   /* does not return */
}

/* FUN_003f5c54 @ 0x003f5c54   (est. sk_col_copy1_003f5c54)
 * Ghidra: void FUN_003f5c54(undefined8 *param_1,undefined8 param_2)
 * Single-element copy shim: runs 001a26e0(param_2, *param_1) to copy one
 * element out of the buffer.
 * Confidence: low */
static void sk_col_copy1_003f5c54(word_t *param_1, word_t param_2)
{
    sk_x_001a26e0(param_2, *param_1);
}

/* FUN_003f5c64 @ 0x003f5c64   (est. sk_col_copy2_003f5c64)
 * Ghidra: void FUN_003f5c64(long param_1,long param_2,long *param_3,...)
 * Range copy: copies param_2-param_1 elements from the element base at
 * param_4+stride*param_1 (stride from the layout word at param_5-8, offset
 * +0x48) into the destination; validates the count against capacity
 * (param_3) and raises the overflow/assertion trap (0x52) on underflow.
 * Confidence: medium */
static void sk_col_copy2_003f5c64(word_t param_1, word_t param_2, sword_t *param_3,
                                  word_t param_4, word_t param_5)
{
    if (*param_3 < (sword_t)param_2) {
        sk_x_004070cc();
        sk_x_00406310(0x52);
        sk_x_001afa84();   /* does not return */
    }
    if (!__builtin_sub_overflow((sword_t)param_2, (sword_t)param_1, (long *)&param_2)) {
        sk_x_001e4cbc(param_4 + *(sword_t *)(*(sword_t *)(param_5 + -8) + 0x48) * param_1,
                      param_2 - param_1, param_5);
        return;
    }
    __asm__ volatile("brk #1" ::: "memory");   /* SW BP 0x3f5c9c */
}

/* FUN_003f5cc4 @ 0x003f5cc4   (est. sk_col_copy3_003f5cc4)
 * Ghidra: void FUN_003f5cc4(void)
 * Wrapper for sk_col_copy2_003f5c64 that forwards the (16-byte) range and
 * an extra argument through thunk_FUN_0001a1c8.
 * Confidence: low */
static void sk_col_copy3_003f5cc4(void)
{
    sk_col_copy2_003f5c64(0, 0, 0, 0, 0);
    sk_x_0001a1c8(0, 0, 0);
}

/* FUN_003f5cf0 @ 0x003f5cf0   (est. sk_col_ck_003f5cf0)
 * Ghidra: void FUN_003f5cf0(long *param_1)
 * Negativity check on a count: returns silently if *param_1 >= 0, else
 * raises the negative-count trap (0040633c -> noreturn 001afa84).
 * Confidence: high */
static void sk_col_ck_003f5cf0(sword_t *param_1)
{
    if (-1 < *param_1) {
        return;
    }
    sk_x_0040633c();
    sk_x_001afa84();   /* does not return */
}

/* FUN_003f5d1c @ 0x003f5d1c   (est. sk_col_next_003f5d1c)
 * Ghidra: long FUN_003f5d1c(long param_1,long *param_2)
 * Returns the index after param_1 in a collection of size *param_2,
 * wrapping to 0 when param_1+1 reaches the end (and validating param_1 is
 * within bounds, else raising the index-overflow trap 0x65).
 * Confidence: high */
static sword_t sk_col_next_003f5d1c(sword_t param_1, sword_t *param_2)
{
    sword_t n;

    if (*param_2 <= param_1) {
        sk_x_004070cc();
        sk_x_00406310(0x65);
        sk_x_001afa84();   /* does not return */
    }
    n = param_1 + 1;
    if (n < *param_2) {
        if (param_1 < -1) {
            sk_x_0040633c();
            sk_x_001afa84();   /* does not return */
        }
    } else {
        n = 0;
    }
    return n;
}

/* FUN_003f5d80 @ 0x003f5d80   (est. sk_col_prev_003f5d80)
 * Ghidra: long FUN_003f5d80(long param_1,long *param_2)
 * Returns the index before param_1, wrapping to the last element (*param_2-1)
 * when param_1 == 0; validates bounds (else trap 0x6e).
 * Confidence: high */
static sword_t sk_col_prev_003f5d80(sword_t param_1, sword_t *param_2)
{
    sword_t n;

    if (*param_2 <= param_1) {
        sk_x_004070cc();
        sk_x_00406310(0x6e);
        sk_x_001afa84();   /* does not return */
    }
    if (param_1 == 0) {
        n = *param_2 + -1;
    } else {
        n = param_1 + -1;
        if (__builtin_sub_overflow(param_1, 1, &n)) {
            __asm__ volatile("brk #1" ::: "memory");   /* SW BP 0x3f5dc8 */
        }
        if (n < 0) {
            sk_x_0040633c();
            sk_x_001afa84();   /* does not return */
        }
    }
    return n;
}

/* FUN_003f5de0 @ 0x003f5de0   (est. sk_col_range_003f5de0)
 * Ghidra: void FUN_003f5de0(long param_1,long param_2,long *param_3)
 * Range-window check: validates that [param_1, param_1+param_2) lies within
 * the collection count *param_3, raising the appropriate overflow/assertion
 * trap (0x74, or 0040633c negative) when out of range. Central bounds guard
 * for the buffer arithmetic.
 * Confidence: high */
static void sk_col_range_003f5de0(sword_t param_1, sword_t param_2, sword_t *param_3)
{
    sword_t n, w;

    w = *param_3;
    if (w < param_1) {
        sk_x_004070cc();
        sk_x_00406310(0x74);
    } else {
        n = param_1 + param_2;
        if (__builtin_add_overflow(param_1, param_2, &n)) {
            __asm__ volatile("brk #1" ::: "memory");   /* SW BP 0x3f5e40 */
        }
        if (param_2 < 0) {
            if (-1 < n) {
                return;
            }
            n = n + w;
            if (__builtin_add_overflow(n, w, &n)) {
                __asm__ volatile("brk #1" ::: "memory");   /* SW BP 0x3f5e48 */
            }
        } else {
            n = n;
            if ((w <= n) && (n = n - w, __builtin_sub_overflow(n, w, &n))) {
                __asm__ volatile("brk #1" ::: "memory");   /* SW BP 0x3f5e44 */
            }
        }
        if (-1 < n) {
            return;
        }
        sk_x_0040633c(n);
    }
    sk_x_001afa84();   /* does not return */
}

/* FUN_003f5e68 @ 0x003f5e68   (est. sk_col_range2_003f5e68)
 * Ghidra: void FUN_003f5e68(long param_1)
 * Bounds-guard shim over the collection descriptor at param_1: applies
 * sk_col_range_003f5de0 to the count (+0x08) and element base (+0x10).
 * Confidence: medium */
static void sk_col_range2_003f5e68(sword_t param_1)
{
    sk_col_range_003f5de0(*(sword_t *)(param_1 + 0x10), *(sword_t *)(param_1 + 8), 0);
}

/* FUN_003f5e78 @ 0x003f5e78   (est. sk_col_off_003f5e78)
 * Ghidra: long FUN_003f5e78(long param_1,long *param_2)
 * Converts an index into a byte offset within the element buffer: validates
 * param_1 is in [0, *param_2], then returns (base + index) - count, i.e. the
 * signed distance from the buffer end; raises the index traps (0x85/0x86).
 * Confidence: high */
static sword_t sk_col_off_003f5e78(sword_t param_1, sword_t *param_2)
{
    sword_t n, end;

    if (param_1 < 0) {
        sk_x_004070cc();
        sk_x_00406310(0x85);
    } else {
        end = *param_2;
        if (param_1 <= end) {
            param_1 = param_2[2] + param_1;
            n = param_1 - end;
            if ((end <= param_1) || (n = param_1, -1 < param_1)) {
                return n;
            }
            sk_x_0040633c();
            goto done;
        }
        sk_x_004070cc();
        sk_x_00406310(0x86);
    }
    sk_x_00406310(sk_x_00350ab8());
done:
    sk_x_001afa84();   /* does not return */
}

/* FUN_003f5ee8 @ 0x003f5ee8   (est. sk_col_slice_003f5ee8)
 * Ghidra: void FUN_003f5ee8(undefined8 param_1,...)
 * Produces a slice view of the buffer: computes the used range (capacity -
 * base from the 003565a8 context), and either copies the used prefix via
 * sk_col_copy2_003f5c64 (when capacity >= count) or builds an in-place
 * slice via the 003f3ecc helper, then repacks the result with
 * 00407790 / 00356590.
 * Confidence: low */
static void sk_col_slice_003f5ee8(word_t param_1, word_t param_2, word_t param_3)
{
    word_t *buf;
    sword_t used, count;

    buf = (word_t *)sk_x_003565a8();
    used = (sword_t)buf[0] - (sword_t)buf[2];
    count = (sword_t)buf[1];
    sk_x_003513b4();
    sk_x_003f5c00();
    if (used < count) {
        sk_x_00350500();
        sk_x_003f5c00(0, 0, 0, param_3);
        sk_x_004072cc();
        sk_x_00100efc();
        sk_x_003f3ecc();
    } else {
        sk_x_001e4cbc(0, buf[1], param_3);
        sk_x_00408428();
    }
    sk_x_00407790(0, 0, 0);
    sk_x_00356590(0);
}

/* FUN_003f5fc4 @ 0x003f5fc4   (est. sk_col_copy4_003f5fc4)
 * Ghidra: void FUN_003f5fc4(long param_1,long param_2,long *param_3)
 * Copies the range [param_1, param_2) of the buffer (param_3), validating
 * bounds; when the range is empty it runs the initialiser closure
 * (001e4cbc -> 00408428); otherwise it reserves the overlap (003f3ecc) and
 * repacks via 00407790. Raises the range trap (0x9f) out of bounds.
 * Confidence: low */
static void sk_col_copy4_003f5fc4(sword_t param_1, sword_t param_2, sword_t *param_3)
{
    sword_t lo, hi;

    if ((-1 < param_1) && (param_2 <= param_3[1])) {
        lo = (sword_t)sk_x_00353d70();
        sk_col_off_003f5e78(lo, param_3);
        sk_x_00351384();
        hi = (sword_t)sk_col_off_003f5e78(0, param_3);
        sk_x_0034d004(lo);
        sk_col_index_check_003f5c00();
        if ((param_2 - lo == 0) || (lo < hi)) {
            sk_x_001e4cbc(0, param_2 - lo);
            sk_x_00408428();
        } else {
            sk_x_0034d004(0);
            sk_x_003f5c00();
            sk_x_004072cc();
            sk_x_000dbd0c(0);
            sk_x_003f3ecc();
            sk_x_00407dd0();
        }
        sk_x_00407790();
        return;
    }
    sk_x_004070cc();
    sk_x_00406310(0x9f);
    sk_x_001afa84();   /* does not return */
}

/* FUN_003f60e4 @ 0x003f60e4   (est. sk_col_rep_003f60e4)
 * Ghidra: void FUN_003f60e4(undefined8 param_1,...)
 * Two-stage repack helper: builds an intermediate via sk_col_slice_003f5ee8
 * then recombines through 003f3f50 and repacks with 00407ff0.
 * Confidence: low */
static void sk_col_rep_003f60e4(word_t param_1, word_t param_2, word_t param_3)
{
    word_t st[5];
    sk_col_slice_003f5ee8((word_t)&st[0], 0, param_3);
    sk_x_003f3f50((word_t)&st[5], (word_t)&st[0], param_3);
    sk_x_00407ff0();
}

/* FUN_003f612c @ 0x003f612c   (est. sk_col_rep2_003f612c)
 * Ghidra: void FUN_003f612c(void)
 * Repack shim: runs sk_col_copy4_003f5fc4 into a temp, recombines via
 * 003f3f50 and repacks with 00407ff0.
 * Confidence: low */
static void sk_col_rep2_003f612c(void)
{
    word_t st[5];
    sk_col_copy4_003f5fc4((sword_t)&st[0], 0, 0);
    sk_x_003f3f50((word_t)&st[5], (word_t)&st[0], 0);
    sk_x_00407ff0();
}

/* FUN_003f6174 @ 0x003f6174   (est. sk_col_push_003f6174)
 * Ghidra: void FUN_003f6174(undefined8 param_1,...)
 * Appends elements to the shared buffer: validates the range (003f5e68 /
 * sk_col_ck_003f5cf0), copies the trailing run (sk_col_copy3_003f5cc4), then
 * pushes the remaining elements with the single-element copy path
 * (001a26e0). Repacks via 00408428 / 00407790. Raises the overflow trap on
 * count underflow.
 * Confidence: low */
static void sk_col_push_003f6174(word_t param_1, word_t param_2, word_t param_3)
{
    sword_t *buf;
    word_t idx;

    sk_x_003509ec();
    idx = (word_t)sk_col_range2_003f5e68(0);
    buf = (sword_t *)sk_x_00350ab8();
    if (buf[1] < buf[0]) {
        if (buf[2] <= (sword_t)idx) {
            if ((word_t)sk_col_ck_003f5cf0(0) < idx) {
            overflow:
                sk_x_00347da8();
                sk_x_003504b8();
                sk_x_001afe4c();   /* does not return */
            }
            sk_x_0040761c(idx, 0);
            sk_col_copy3_003f5cc4();
            if (buf[2] < 0) goto overflow;
            sk_x_0040761c(0);
            sk_col_copy3_003f5cc4();
            sk_x_00351790();
            sk_x_00350470(0);
            sk_x_003f3e64();
            sk_x_00407dd0();
            goto done;
        }
        sk_x_0040761c(idx);
        sk_col_copy3_003f5cc4();
    } else {
        sk_x_0034d004(idx);
        sk_col_index_check_003f5c00();
        sk_x_001a26e0(0, 0, param_3);
    }
    sk_x_00408428();
done:
    sk_x_00407790();
}

/* FUN_003f6278 @ 0x003f6278   (est. sk_col_move_003f6278)
 * Ghidra: void FUN_003f6278(long param_1,...)
 * Moves param_3 elements starting at param_1 within the buffer (param_4),
 * calling the per-element move function param_8 for each; validates the
 * range against capacity (else "Assertion failed" / fatal). param_2==0 is a
 * fatal "Fatal error" condition on the element copy.
 * Confidence: medium
 * Notes: s_Assertion_failed_005ce250, s_Fatal_error_005accd0. */
static void sk_col_move_003f6278(sword_t param_1, word_t param_2, sword_t param_3,
                                 sword_t *param_4, word_t param_5, word_t param_6,
                                 word_t param_7, word_t fn)
{
    sword_t n;
    word_t base;

    n = param_1 + param_3;
    if (__builtin_add_overflow(param_1, param_3, &n)) {
        __asm__ volatile("brk #1" ::: "memory");   /* SW BP 0x3f630c */
    }
    if (*param_4 < n) {
        sk_x_004070cc();
        sk_x_00406518((word_t)s_Assertion_failed_005ce250);
        sk_x_001afa84();   /* does not return */
    }
    if (0 < param_3) {
        base = sk_x_003f5c00(param_1, (word_t)param_4, param_5, param_6);
        if (param_2 == 0) {
            sk_x_00407984((word_t)s_Fatal_error_005accd0);
            sk_x_0034a2f8();
            sk_x_001afe4c();   /* does not return */
        }
        sk_x_00100efc(base, base, base);
        (*(void (**)(void))fn)();
        if (n < 0) {
            sk_x_0040633c(n);
            sk_x_001afa84();   /* does not return */
        }
    }
}

/* FUN_003f637c @ 0x003f637c   (est. sk_col_replace_003f637c)
 * Ghidra: void FUN_003f637c(long param_1,...)
 * replaceSubrange: replaces [param_1, param_1+param_3) of the buffer with
 * param_2 elements from the source, validating all three ranges against the
 * capacity (param_4) and copying elements via 0019ce60 with the stride at
 * the +0x48 layout word. Repacks with 0007c1c4. Raises the range traps
 * (0xe0/0xe1/0xe2).
 * Confidence: medium */
static void sk_col_replace_003f637c(sword_t param_1, sword_t param_2, sword_t param_3,
                                    sword_t *param_4, word_t param_5, word_t param_6)
{
    word_t dst, src;

    if (param_3 < 0) {
        sk_x_004070cc();
        sk_x_00406310(0xe0);
    } else {
        if (__builtin_add_overflow(param_1, param_3, &dst)) {
            __asm__ volatile("brk #1" ::: "memory");   /* SW BP 0x3f6458 */
        }
        if (*param_4 < (sword_t)dst) {
            sk_x_004070cc();
            sk_x_00406310(0xe1);
        } else {
            if (__builtin_add_overflow(param_2, param_3, &src)) {
                __asm__ volatile("brk #1" ::: "memory");   /* SW BP 0x3f645c */
            }
            if (param_2 + param_3 <= *param_4) {
                if (param_3 != 0) {
                    sk_x_003507e0();
                    dst = sk_x_003f5c00(0, 0, param_5, param_6);
                    sk_x_0006b6f4();
                    sk_x_00352ae4();
                    src = sk_x_003f5c00();
                    sk_x_0019ce60(src, param_3, dst, param_6);
                    sk_col_range_003f5de0(param_1, param_3, param_4);
                    sk_x_003504ac();
                    sk_col_range_003f5de0(0, 0, param_4);
                }
                sk_x_0007c1c4();
                return;
            }
            sk_x_004070cc();
            sk_x_00406310(0xe2);
        }
    }
    sk_x_00406310(sk_x_00350ab8());
    sk_x_001afa84();   /* does not return */
}

/* FUN_003f648c @ 0x003f648c   (est. sk_col_pushback_003f648c)
 * Ghidra: void FUN_003f648c(undefined8 param_1,...)
 * Appends one element to the buffer (param_4): validates the count against
 * capacity, and when room exists copies the element at the current cursor
 * (via sk_col_pushback1_003f6560 / 003f4ff4 / 003f612c) and bumps the
 * count; else raises the capacity trap (0x15f).
 * Confidence: low */
static void sk_col_pushback_003f648c(void)
{
    sword_t cap, count;
    word_t lo, hi;

    lo = sk_x_0035300c();
    hi = sk_x_00350ab8();
    if (*(sword_t *)(0 + 8) < (sword_t)hi) {
        sk_x_004070cc();
        sk_x_00406310(0x15f);
    } else {
        sk_x_00353efc(0);
        sk_x_00084180();
        count = (sword_t)sk_x_00350ab8();
        if (__builtin_sub_overflow(hi, lo, (long *)&cap)) {
            __asm__ volatile("brk #1" ::: "memory");   /* SW BP 0x3f653c */
        }
        if (count == cap) {
            if (lo != hi) {
                sk_x_00407b54();
                sk_col_rep2_003f612c();
                sk_x_00350500();
                sk_col_pushback1_003f6560(0, 0, 0, 0);
                sk_x_0035063c(0, 0);
                sk_col_assert_003f4ff4();
            }
            sk_x_00353238(0);
            return;
        }
        sk_x_004070cc();
        sk_x_00406310(0x160);
    }
    sk_x_00406310(sk_x_00350ab8());
    sk_x_001afa84();   /* does not return */
}

/* FUN_003f6560 @ 0x003f6560   (est. sk_col_pushback1_003f6560)
 * Ghidra: void FUN_003f6560(undefined8 param_1,long param_2,...)
 * Appends the element at param_2 to the buffer, incrementing its count
 * (+0x08). Validates the buffer is non-full (else trap 0x171), then copies
 * the element through the two element-copy closures (00351384 / 00350470)
 * and bumps the count. Raises overflow trap on count wrap.
 * Confidence: low */
static void sk_col_pushback1_003f6560(word_t param_1, sword_t param_2, word_t param_3, word_t param_4)
{
    word_t *buf;

    sk_x_0007c028();
    (*(word_t (**)(word_t))DAT_00658c80)(0);
    sk_x_000aa4ec();
    sk_x_00407b80();
    buf = (word_t *)sk_x_00350ab8();
    if (*buf <= buf[1]) {
        sk_x_00350d04();
        sk_x_00406310(0x171);
        sk_x_001afa84();   /* does not return */
    }
    sk_x_003f5e68(param_2);
    sk_col_index_check_003f5c00();
    sk_x_00407d44();
    sk_x_00351384();
    sk_x_00310d68(0, 0, param_4);
    sk_x_00350470(0);
    sk_x_00310d68(0, 0, param_4);
    if (!__builtin_add_overflow(buf[1], 1, &buf[1])) {
        buf[1] = buf[1] + 1;
        return;
    }
    __asm__ volatile("brk #1" ::: "memory");   /* SW BP 0x3f664c */
}

/* FUN_003f6668 @ 0x003f6668   (est. sk_col_pushback2_003f6668)
 * Ghidra: void FUN_003f6668(undefined8 param_1,undefined8 param_2,long *param_3)
 * Appends extraout_x1 elements to the buffer (param_3): validates the new
 * count fits, bumps the count, and when the total is positive repacks the
 * new elements (sk_col_rep2_003f612c) then re-emits via 00376820/003504a0
 * and sk_col_ins_003f4828. Raises the capacity trap (0x17d).
 * Confidence: low */
static void sk_col_pushback2_003f6668(word_t param_1, word_t param_2, sword_t *param_3)
{
    sword_t n, m;

    sk_x_0035098c();
    m = param_3[1];
    n = m + (sword_t)sk_x_00350ab8();
    if (__builtin_add_overflow(m, (sword_t)sk_x_00350ab8(), &n)) {
        __asm__ volatile("brk #1" ::: "memory");   /* SW BP 0x3f6710 */
    }
    if (n <= param_3[0]) {
        if (0 < (sword_t)sk_x_00350ab8()) {
            param_3[1] = n;
            if (n < m) {
                sk_x_00347da8();
                sk_x_003504b8();
                sk_x_001afe4c();   /* does not return */
            }
            sk_col_rep2_003f612c();
            sk_x_003504e8();
            sk_x_00405830();
            sk_x_003504e8();
            sk_x_0031b37c();
            sk_x_004066a4();
            sk_x_00376820(0, 0);
            sk_x_003504a0();
            sk_col_ins_003f4828();
        }
        return;
    }
    sk_x_004070cc();
    sk_x_00406310(0x17d);
    sk_x_001afa84();   /* does not return */
}

/* FUN_003f6738 @ 0x003f6738   (est. sk_col_pushfront_003f6738)
 * Ghidra: void FUN_003f6738(undefined8 param_1,...)
 * Prepends an element to the buffer: validates non-full, computes the
 * element before the current head (sk_col_prev_003f5d80), copies it through
 * the two copy closures, stores it as the new head (+0x10) and bumps the
 * count. Raises trap 0x18b on full.
 * Confidence: low */
static void sk_col_pushfront_003f6738(word_t param_1, word_t param_2, word_t param_3, word_t param_4)
{
    word_t *buf;
    word_t head;

    sk_x_00084220();
    sk_x_0007c028();
    (*(word_t (**)(word_t))DAT_00658c80)(0);
    sk_x_000aa4ec();
    sk_x_00407b80();
    buf = (word_t *)sk_x_00350ab8();
    if (*buf <= buf[1]) {
        sk_x_00350d04();
        sk_x_00406310(0x18b);
        sk_x_001afa84();   /* does not return */
    }
    head = (word_t)sk_col_prev_003f5d80(*(sword_t *)(buf + 2), (sword_t *)buf);
    sk_col_index_check_003f5c00();
    sk_x_00407d44();
    sk_x_00351384();
    sk_x_00310d68(0, 0, param_4);
    sk_x_00350470(0);
    sk_x_00310d68(0, 0, param_4);
    buf[2] = head;
    if (!__builtin_add_overflow(buf[1], 1, &buf[1])) {
        buf[1] = buf[1] + 1;
        sk_x_00084234(0);
        return;
    }
    __asm__ volatile("brk #1" ::: "memory");   /* SW BP 0x3f6830 */
}

/* FUN_003f684c @ 0x003f684c   (est. sk_col_rm_003f684c)
 * Ghidra: void FUN_003f684c(long param_1,...)
 * Removes the range [param_1, param_2) from the buffer (param_3): when
 * param_1 < param_2 copies the tail via 001a26e0 and repacks; when equal,
 * copies the head (003f3ecc) and repacks; else raises the range trap
 * (0x1c4/0x1c5).
 * Confidence: low */
static void sk_col_rm_003f684c(sword_t param_1, sword_t param_2, sword_t *param_3,
                               word_t param_4, word_t param_5)
{
    sword_t n;

    if (*param_3 < param_1) {
        sk_x_004070cc();
        sk_x_00406310(0x1c4);
    } else {
        if (param_2 <= *param_3) {
            sk_col_index_check_003f5c00();
            if (param_1 < param_2) {
                sk_x_001a26e0(0, param_2 - param_1, param_5);
                sk_x_00408428();
            } else {
                n = *param_3;
                sk_x_0035050c();
                sk_x_003f5c00(0, 0, param_4, param_5);
                sk_x_0040761c(0, 0, n - param_1, 0);
                sk_x_003f3ecc();
                sk_x_00407dd0();
            }
            sk_x_00407790();
            return;
        }
        sk_x_004070cc();
        sk_x_00406310(0x1c5);
    }
    sk_x_00406310(sk_x_00350ab8());
    sk_x_001afa84();   /* does not return */
}

/* FUN_003f697c @ 0x003f697c   (est. sk_col_fill_003f697c)
 * Ghidra: void FUN_003f697c(undefined8 param_1,...)
 * Fills the buffer (param_4) with param_3 new elements: validates capacity,
 * runs the element initialiser (003f6a8c) for each and repacks; when the
 * run is already complete it dispatches to the element protocol directly
 * (indirect call through param_7-8 layout +8). Raises trap 0x1b9/0x1ba.
 * Confidence: low */
static void sk_col_fill_003f697c(void)
{
    sword_t lo, hi;

    lo = sk_x_0035300c();
    hi = sk_x_00350ab8();
    if (*(sword_t *)(0 + 8) < (sword_t)sk_x_00350ab8()) {
        sk_x_004070cc();
        sk_x_00406310(0x1b9);
    } else {
        sk_x_00353efc(0);
        sk_x_003507e0();
        if (sk_x_00350ab8() == hi) {
            if (0 < hi) {
                sk_x_00407b54();
                sk_col_rep3_003f6a8c();
                sk_x_00350500();
                sk_x_00405830();
                sk_x_00350974(lo, 0);
                sk_col_ins_003f4828();
                sk_x_00353238(0);
                return;
            }
            (*(void (**)(word_t, word_t))(*(sword_t *)(0 + -8) + 8))(lo, 0);
            return;
        }
        sk_x_004070cc();
        sk_x_00406310(0x1ba);
    }
    sk_x_00406310(sk_x_00350ab8());
    sk_x_001afa84();   /* does not return */
}

/* FUN_003f6a8c @ 0x003f6a8c   (est. sk_col_rep3_003f6a8c)
 * Ghidra: void FUN_003f6a8c(undefined8 param_1,...)
 * The range-replacement core: inserts a run of elements into the middle of
 * the buffer. Validates the insertion window [uVar13, uVar13+uVar4) against
 * capacity, shifts the tail, and re-copies through the 0040753c move helper
 * in up to three segments (head / middle / tail) using the sk_col_* index
 * helpers to compute each boundary. Raises the range traps (0x1dd/0x1de/
 * 0x1ff/0x1fd).
 * Confidence: low (register-fragment heavy; segment math faithful to the
 *   decompile, element pointers inferred from the +0x48 stride).
 * Notes: SoftwareBreakpoint(1) overflow traps at 0x3f6d98-0x3f6db8. */
static void sk_col_rep3_003f6a8c(void)
{
    sword_t *buf;
    sword_t insert, span, lo, hi, n;
    sword_t a, b;

    insert = (sword_t)sk_x_0035300c() & 0;
    span = (sword_t)sk_x_00350ab8();
    if (span < 0) {
    bad1:
        sk_x_004070cc();
        sk_x_00406310(0x1dd);
        sk_x_001afa84();   /* does not return */
    }
    buf = (sword_t *)0;   /* register-fragment: carried in x20 */
    lo = buf[1];
    n = lo - span;
    if (lo < span) goto bad1;
    if (__builtin_add_overflow(lo, insert, &hi)) {
        __asm__ volatile("brk #1" ::: "memory");   /* SW BP 0x3f6d98 */
    }
    if (buf[0] < hi) {
        sk_x_004070cc();
        sk_x_00406310(0x1de);
        sk_x_001afa84();   /* does not return */
    }
    if (0 < span) {
        sk_x_00353d70();
        sk_x_003f5de0(0, 0, 0);
        if (n <= span) {
            sk_col_range_003f5de0(0, 0, 0);
            sk_col_range_003f5de0(0, lo + span, buf);
            a = (sword_t)sk_col_off_003f5e78(span, buf);
            sk_x_000bd3a4();
            sk_x_003f5de0();
            lo = (sword_t)sk_x_003f3cfc(buf[0], 0);
            b = (sword_t)sk_x_003f3cfc(buf[0], 0);
            if (lo < a) {
                if (b < (sword_t)sk_x_00350ab8()) {
                    sk_x_00350500();
                    sk_x_0040753c(0, 0, 0);
                    sk_x_003f5cf0(0);
                    span = (sword_t)sk_x_00350ab8();
                    insert = (sword_t)sk_x_00350ab8() - span;
                    if (insert < 0) goto bad2;
                    sk_x_0040753c(insert, 0, span);
                    n = (n - span) - 0;
                    if (__builtin_sub_overflow(n, 0, &n)) {
                        __asm__ volatile("brk #1" ::: "memory");   /* SW BP 0x3f6c38 */
                    }
                }
                /* fall through to tail move */
            } else if (b < (sword_t)sk_x_00350ab8()) {
                lo = (sword_t)sk_x_003f5cf0(0);
                insert = (sword_t)sk_x_00350ab8() - span;
                if (insert < 0) goto bad2;
                sk_x_0040753c(insert, 0, n);
                n = n - 0;
                if (__builtin_sub_overflow(n, 0, &n)) {
                    __asm__ volatile("brk #1" ::: "memory");   /* SW BP 0x3f6c94 */
                }
            }
            sk_x_00350738();
            sk_x_0040753c(0, 0, n);
            if (__builtin_add_overflow(buf[1], span, &buf[1])) {
                __asm__ volatile("brk #1" ::: "memory");   /* SW BP 0x3f6da4 */
            }
            buf[1] = buf[1] + span;
            goto done;
        }
        sk_col_range_003f5de0(0, -span, buf);
        a = (sword_t)sk_col_off_003f5e78(span, buf);
        b = (sword_t)sk_col_range_003f5de0(a, -span, buf);
        lo = (sword_t)sk_x_003f3cfc(buf[0], a);
        sk_x_003f3cfc(buf[0], b);
        if (0 <= (sword_t)sk_x_00350ab8()) {
            /* tail/shrink path */
            if (lo <= buf[2]) {
                sk_x_00350798();
                sk_x_0040753c(0, 0, 0);
                lo = (sword_t)sk_x_003f5cf0(0);
                b = lo - span;
                insert = span;
                if (-1 < b) goto mov1;
            } else if (-1 < b - a) {
                sk_x_0040753c(0, b - a, a);
                buf[2] = b;
                goto mov2;
            }
        bad2:
            sk_x_0040633c(b);
            sk_x_001afa84();   /* does not return */
        mov1:
            sk_x_0040753c(b, 0, insert);
            buf[2] = b;
            insert = b;
        mov2:
            n = n - insert;
        }
        sk_x_0040753c(buf[2], (sword_t)sk_x_00350ab8(), n);
    }
    buf[2] = (sword_t)sk_x_00350ab8();
done:
    buf[1] = buf[1] - span;
    if (__builtin_sub_overflow(buf[1], span, &buf[1])) {
        __asm__ volatile("brk #1" ::: "memory");   /* SW BP 0x3f73c4 */
    }
}

/* FUN_003f6e08 @ 0x003f6e08   (est. sk_col_pop_copy_003f6e08)
 * Ghidra: void FUN_003f6e08(undefined8 param_1,long param_2,...)
 * Pops and copies the first element of the buffer (param_2): validates
 * non-empty (trap 0x25b), copies the element at +0x10 via 001a29a0,
 * advances the head (sk_col_next_003f5d1c) and decrements the count.
 * Confidence: low */
static void sk_col_pop_copy_003f6e08(word_t param_1, sword_t param_2, word_t param_3, word_t param_4)
{
    if (*(sword_t *)(param_2 + 8) < 1) {
        sk_x_004070cc();
        sk_x_00406310(0x25b);
        sk_x_001afa84();   /* does not return */
    }
    sk_col_index_check_003f5c00(*(word_t *)(param_2 + 0x10), param_2, param_3, param_4);
    sk_x_001a29a0(param_1, 0, param_4);
    *(sword_t *)(param_2 + 0x10) =
        sk_col_next_003f5d1c(*(sword_t *)(param_2 + 0x10), (sword_t *)param_2);
    if (!__builtin_sub_overflow(*(sword_t *)(param_2 + 8), 1, (long *)&param_2)) {
        *(sword_t *)(param_2 + 8) = *(sword_t *)(param_2 + 8) + -1;
        return;
    }
    __asm__ volatile("brk #1" ::: "memory");   /* SW BP 0x3f6e90 */
}

/* FUN_003f6ea8 @ 0x003f6ea8   (est. sk_col_pop_003f6ea8)
 * Ghidra: void FUN_003f6ea8(undefined8 param_1,long param_2,...)
 * Pops the last element of the buffer: validates non-empty (trap 0x264),
 * computes the last index (sk_col_off_003f5e78(-1)), copies the element via
 * 001a29a0 and decrements the count.
 * Confidence: low */
static void sk_col_pop_003f6ea8(word_t param_1, sword_t param_2, word_t param_3, word_t param_4)
{
    if (*(sword_t *)(param_2 + 8) < 1) {
        sk_x_004070cc();
        sk_x_00406310(0x264);
        sk_x_001afa84();   /* does not return */
    }
    sk_x_00352758();
    sk_col_off_003f5e78(sk_x_00350ab8() + -1, 0);
    sk_x_003518d0();
    sk_col_index_check_003f5c00();
    sk_x_001a29a0(param_1, 0, param_4);
    if (!__builtin_sub_overflow(*(sword_t *)(0 + 8), 1, (long *)&param_2)) {
        *(sword_t *)(0 + 8) = *(sword_t *)(0 + 8) + -1;
        return;
    }
    __asm__ volatile("brk #1" ::: "memory");   /* SW BP 0x3f6f24 */
}

/* FUN_003f6f3c @ 0x003f6f3c   (est. sk_col_rm_first_003f6f3c)
 * Ghidra: void FUN_003f6f3c(long param_1,long param_2,undefined8 param_3)
 * Removes the first param_1 elements of the buffer (param_2): validates
 * count (trap 0x26d), repacks the remainder (sk_col_rep2_003f612c after
 * 003f4164) and advances the head by param_1, decrementing the count.
 * Confidence: low */
static void sk_col_rm_first_003f6f3c(sword_t param_1, sword_t param_2, word_t param_3)
{
    word_t *buf = (word_t *)param_2;
    if (*(sword_t *)(param_2 + 8) < param_1) {
        sk_x_004070cc();
        sk_x_00406310(0x26d);
        sk_x_001afa84();   /* does not return */
    }
    if (0 < param_1) {
        sk_x_003504a0(0, 0, param_2, param_3, param_3);
        sk_col_rep2_003f612c();
        sk_x_00350798();
        sk_x_00405830();
        sk_x_003f4164();
        sk_x_003504a0(buf[2]);
        buf[2] = (word_t)sk_col_range_003f5de0(0, 0, 0);
        if (__builtin_sub_overflow(*(sword_t *)(param_2 + 8), param_1, (long *)&param_2)) {
            __asm__ volatile("brk #1" ::: "memory");   /* SW BP 0x3f6fd4 */
        }
        *(sword_t *)(param_2 + 8) = *(sword_t *)(param_2 + 8) - param_1;
    }
}

/* FUN_003f6fec @ 0x003f6fec   (est. sk_col_rm_last_003f6fec)
 * Ghidra: void FUN_003f6fec(void)
 * Removes the last unaff_x21 elements of the buffer: validates count (trap
 * 0x277), repacks the remainder and decrements the count by unaff_x21.
 * Confidence: low */
static void sk_col_rm_last_003f6fec(void)
{
    sword_t count;
    word_t *buf;

    buf = (word_t *)sk_x_0008409c();
    count = (sword_t)buf[1];
    if (count < (sword_t)buf[0]) {
        sk_x_004070cc();
        sk_x_00406310(0x277);
        sk_x_001afa84();   /* does not return */
    }
    if (0 < (sword_t)sk_x_00350ab8()) {
        if (count < count - (sword_t)buf[0]) {
            sk_x_00347da8();
            sk_x_003504b8();
            sk_x_001afe4c();   /* does not return */
        }
        sk_col_rep2_003f612c();
        sk_x_00350798();
        sk_x_00405830();
        sk_x_003f4164();
        if (__builtin_sub_overflow(*(sword_t *)(0 + 8), (sword_t)sk_x_00350ab8(), (long *)&buf)) {
            __asm__ volatile("brk #1" ::: "memory");   /* SW BP 0x3f7074 */
        }
        *(sword_t *)(0 + 8) = *(sword_t *)(0 + 8) - (sword_t)sk_x_00350ab8();
    }
}

/* FUN_003f709c @ 0x003f709c   (est. sk_col_clear_003f709c)
 * Ghidra: void FUN_003f709c(long param_1)
 * Clears the buffer: when non-empty, repacks (sk_col_rep_003f60e4) then
 * resets the count (+0x08) and element base (+0x10) to empty.
 * Confidence: medium */
static void sk_col_clear_003f709c(sword_t param_1)
{
    if (0 < *(sword_t *)(param_1 + 8)) {
        sk_col_rep_003f60e4(0, 0, 0);
        sk_x_003504e8();
        sk_x_00405830();
        sk_x_003f4164();
        *(sword_t *)(param_1 + 8) = 0;
        *(word_t *)(param_1 + 0x10) = 0;
    }
}

/* FUN_003f70f8 @ 0x003f70f8   (est. sk_col_rm_range_003f70f8)
 * Ghidra: void FUN_003f70f8(long param_1,undefined8 param_2,long param_3)
 * Removes the range [lVar9, lVar7) of length uVar1 from the collection
 * buffer (unaff_x22) and shifts the tail into place, using the
 * sk_col_off / sk_col_index_check / 0040754c move helpers to relocate the
 * elements after the removed window, updating the count (+0x08) and the
 * element base (+0x10). Handles the three geometric cases (removal at the
 * end, head-overlap, tail-overlap / disjoint) and the head/tail element
 * buffers stored at +0x10/+0x18 of the collection descriptor. Validates the
 * window against capacity (traps 0x292/0x2a0/0x2c0).
 * Confidence: low (segment-move matrix faithfully preserved; element
 *   pointers follow the +0x48 stride convention).
 * Notes: SoftwareBreakpoint(1) overflow traps at 0x3f741c-0x3f7438. */
static void sk_col_rm_range_003f70f8(sword_t param_1, word_t param_2, sword_t param_3)
{
    sword_t *buf = (sword_t *)param_3;
    cl4_pair_t rng;
    sword_t lo, hi, span, tail;
    sword_t offA, offB, rem, mv;

    if ((param_1 < 0) || (sk_x_0035128c(), buf[1] < (sword_t)sk_x_00350ab8())) {
        sk_x_004070cc();
        sk_x_00406310(0x292);
        sk_x_001afa84();   /* does not return */
    }
    sk_x_00352700();
    sk_x_000bd3a4(0);
    sk_col_rep2_003f612c();
    sk_x_003504e8();
    sk_x_00405830();
    sk_x_003f4164();
    rng = sk_x_00350518();
    hi = (sword_t)rng.hi;
    lo = (sword_t)rng.lo;
    if ((lo < 0) || (buf[1] < hi)) {
        sk_x_004070cc();
        sk_x_00406310(0x2a0);
        sk_x_001afa84();   /* does not return */
    }
    span = hi - lo;
    if (__builtin_sub_overflow(hi, lo, &span)) {
        __asm__ volatile("brk #1" ::: "memory");   /* SW BP 0x3f741c */
    }
    if (span < 1) {
        return;
    }
    offA = (sword_t)sk_col_off_003f5e78(lo, buf);
    offB = (sword_t)sk_col_off_003f5e78(hi, buf);
    tail = buf[1] - hi;
    if (__builtin_sub_overflow(buf[1], hi, &tail)) {
        __asm__ volatile("brk #1" ::: "memory");   /* SW BP 0x3f7420 */
    }
    if (tail <= lo) {
        /* removal at the very end: just shrink the window */
        lo = (sword_t)sk_col_range2_003f5e68(0);
        if (__builtin_sub_overflow(buf[1], span, &hi)) {
            __asm__ volatile("brk #1" ::: "memory");   /* SW BP 0x3f7424 */
        }
        hi = (sword_t)sk_col_off_003f5e78(buf[1] - span, buf);
        offA = (sword_t)sk_x_003f3cfc(buf[0], lo);
        sk_x_003f3cfc(buf[0], hi);
        mv = (sword_t)sk_x_00350ab8();
        if (tail != 0) {
            if (offB < offA) {
                if (mv < offA) {
                    lo = buf[0] - offA;
                    if (__builtin_sub_overflow(buf[0], offA, &lo)) {
                        __asm__ volatile("brk #1" ::: "memory");   /* SW BP 0x3f742c */
                    }
                    if (tail <= lo) {
                        sk_x_004070cc();
                        sk_x_00406310(0x2c0);
                        sk_x_001afa84();   /* does not return */
                    }
                    sk_x_00350470();
                    offA = (sword_t)sk_x_0040754c(0, 0, lo);
                    if (__builtin_sub_overflow(tail, lo, &rem)) {
                        __asm__ volatile("brk #1" ::: "memory");   /* SW BP 0x3f7438 */
                    }
                    mv = rem;
                    lo = tail - lo;
                } else {
                    sk_x_00350470();
                    lo = tail;
                }
            } else {
                tail = buf[0];
                if (mv < offA) {
                    if (__builtin_sub_overflow(tail, offB, &hi)) {
                        __asm__ volatile("brk #1" ::: "memory");   /* SW BP 0x3f7430 */
                    }
                    sk_x_00350470(mv, 0, tail - offB);
                    sk_x_0040754c();
                    sk_x_0035053c(0);
                    offA = (sword_t)sk_col_replace_003f637c(0, 0, 0, 0, 0, 0);
                    mv = 0;
                    lo = hi;
                } else {
                    if (__builtin_sub_overflow(tail, offB, &hi)) {
                        __asm__ volatile("brk #1" ::: "memory");   /* SW BP 0x3f7434 */
                    }
                    sk_x_00350470(mv, 0, tail - offB);
                    sk_x_0040754c();
                    mv = 0;
                }
            }
            sk_x_0040754c(mv, 0, lo);
        }
        lo = buf[1] - span;
        if (__builtin_sub_overflow(buf[1], span, &lo)) {
            __asm__ volatile("brk #1" ::: "memory");   /* SW BP 0x3f7428 */
        }
        goto finish;
    }
    /* disjoint / head-overlap removal: relocate the surviving elements */
    tail = buf[2];
    sk_x_00350624(tail);
    mv = (sword_t)sk_col_range_003f5de0(0, 0, 0);
    offA = (sword_t)sk_x_003f3cfc(buf[0], offA);
    offB = (sword_t)sk_x_003f3cfc(buf[0], offB);
    if (lo != 0) {
        if (offA <= tail) {
            if (offB < mv) {
                sk_x_00350798();
                sk_x_0040754c(0, 0, offA);
                offA = (sword_t)sk_col_ck_003f5cf0(0);
                offB = offA - span;
                mv = span;
                if (-1 < offB) goto mov1;
            } else if (-1 < offB - offA) {
                sk_x_0040754c(0, offB - offA, offA);
                tail = buf[2];
                goto mov2;
            }
            sk_x_0040633c(offB);
            sk_x_001afa84();   /* does not return */
        }
        if (offB < mv) {
            offA = (sword_t)sk_col_ck_003f5cf0(0);
            offB = offA - span;
            mv = offB;
            if (offB < 0) {
                sk_x_0040633c(offB);
                sk_x_001afa84();   /* does not return */
            }
        mov1:
            sk_x_0040754c(offB, 0, mv);
            tail = buf[2];
            mv = offB;
        mov2:
            lo = lo - mv;
        }
        sk_x_0040754c(tail, mv, lo);
    }
    buf[2] = mv;
    lo = buf[1] - span;
    if (__builtin_sub_overflow(buf[1], span, &lo)) {
        __asm__ volatile("brk #1" ::: "memory");   /* SW BP 0x3f73c4 */
    }
finish:
    buf[1] = lo;
}

/* FUN_003f7464 @ 0x003f7464   (est. sk_col_foreach_003f7464)
 * Ghidra: void FUN_003f7464(undefined8 param_1,...)
 * Runs a foreach over the collection buffer: reads the element layout
 * (count/base from the 00353cfc context), installs the run via 003f761c,
 * and iterates applying the per-element callback (through the 00350518 /
 * 000dbd0c / 0031a14c element protocol) until the 000839f8 end-marker
 * fires or the 003f7648 append helper indicates exhaustion. Releases the
 * buffer and ends the run.
 * Confidence: low */
static void sk_col_foreach_003f7464(word_t param_1, word_t param_2, word_t param_3, word_t param_4)
{
    word_t *ctx;
    word_t v6, v7, u6;

    ctx = (word_t *)sk_x_00353cfc();
    sk_x_0007c028();
    (*(word_t (**)(word_t))DAT_00658c80)(0);
    sk_x_000aa4ec();
    sk_x_00407b80();
    sk_x_00350a64();
    sk_x_00310d68();
    sk_x_00351f10();
    sk_x_0007c1a4();
    (*(word_t (**)(void))DAT_00658c80)();
    sk_x_0034b05c();
    v6 = ctx[3];      /* +0x18 */
    v7 = ctx[4];      /* +0x20 */
    sk_x_0006a4c0(0, v6);
    sk_x_00353ccc();
    sk_x_000a68c4();
    sk_x_00310d68(0, v6, v7);
    sk_x_000e15d8();
    u6 = (word_t)sk_col_retain_003f761c(0, 0);
    sk_x_00350500();
    sk_x_00404b8c();
    do {
        sk_col_append_003f7648(v7, 0, 0, 0);
        sk_x_003518dc();
        if (sk_x_000839f8() == 1) break;
        sk_x_000dbd0c(0);
        sk_x_00310d68(0, 0, param_3);
        sk_x_000836a4(0, 0);
        sk_x_0031a14c(0);
        sk_x_00350518(0);
        sk_x_00310d68(0, 0, param_4, 0, 0);
        sk_x_00350518(0);
        sk_x_00310d68();
    } while (sk_x_00350ab8() == 0);
    CL4_OBJ_RELEASE(u6);
    sk_x_000026e8(0);
    sk_x_00353d14(0);
}

/* FUN_003f761c @ 0x003f761c   (est. sk_col_retain_003f761c)
 * Ghidra: void FUN_003f761c(undefined8 param_1,undefined8 param_2)
 * Retains the boxed collection and produces a fresh 16-byte descriptor via
 * sk_col_box_003f7ab8. Used to capture the buffer before iteration.
 * Confidence: low */
static cl4_pair_t sk_col_retain_003f761c(word_t param_1, word_t param_2)
{
    CL4_OBJ_RETAIN(0);
    return sk_col_box_003f7ab8(0, param_2);
}

/* FUN_003f7648 @ 0x003f7648   (est. sk_col_append_003f7648)
 * Ghidra: void FUN_003f7648(undefined8 param_1,long param_2,...)
 * Appends one element to the buffer (unaff_x20 layout at +8/+0x10): when the
 * buffer is full it re-boxes (sk_col_box3_003f7bd8) and takes the grow path
 * (00350744); otherwise it stores the element at the current cursor via
 * sk_col_cfg_003f540c with the 00404ba4 closure and bumps the count. Raises
 * the overflow trap (0x4f) on count overflow.
 * Confidence: low */
static void sk_col_append_003f7648(word_t param_1, sword_t param_2, word_t param_3, word_t param_4)
{
    sword_t n1, n2;
    word_t *buf;
    cl4_pair_t box;

    n1 = *(sword_t *)(0 + 8);
    n2 = *(sword_t *)(0 + 0x10);
    if (n1 == n2) {
        box = sk_col_box3_003f7bd8(param_2);
        if ((box.lo & 1) == 0) {
            sk_x_00350744(param_1, box.hi, param_4, *(word_t *)(param_2 + 0x10));
            sk_x_000839d8();
            return;
        }
        n1 = *(sword_t *)(0 + 8);
        n2 = *(sword_t *)(0 + 0x10);
    }
    if (n1 < n2) {
        if (-2 < n1) {
            *(sword_t *)(0 + 8) = n1 + 1;
            sk_x_00407f54();
            (*(word_t (**)(void))DAT_00658c80)();
            sk_x_00350ab8();
            sk_col_cfg_003f540c(param_1, (word_t)sk_x_00404ba4, 0, param_4, 0, 0, (word_t)sk_x_00404c60);
            sk_x_0034ba48();
            sk_x_000839d8();
            return;
        }
        sk_x_0040633c();
    } else {
        sk_x_00350d04();
        sk_x_004063f4(0x4f);
    }
    sk_x_001afa84();   /* does not return */
}

/* FUN_003f7774 @ 0x003f7774   (est. sk_col_foreach2_003f7774)
 * Ghidra: void FUN_003f7774(undefined8 param_1,long param_2,ulong param_3)
 * Foreach wrapper: forwards to sk_col_foreach_003f7464 with the boxed
 * collection, the element base (+0x10) and the tagged layout word
 * ((param_3 & ~1) - 8).
 * Confidence: low */
static void sk_col_foreach2_003f7774(word_t param_1, sword_t param_2, word_t param_3)
{
    sk_col_foreach_003f7464(param_1, *(word_t *)0, *(word_t *)(param_2 + 0x10),
                            *(word_t *)((param_3 & 0xfffffffffffffffeULL) - 8));
}

/* FUN_003f7778 @ 0x003f7778   (est. sk_col_foreach3_003f7778)
 * Ghidra: void FUN_003f7778(undefined8 param_1,long param_2,ulong param_3)
 * Identical foreach wrapper (register-pair twin of 003f7774).
 * Confidence: low */
static void sk_col_foreach3_003f7778(word_t param_1, sword_t param_2, word_t param_3)
{
    sk_col_foreach_003f7464(param_1, *(word_t *)0, *(word_t *)(param_2 + 0x10),
                            *(word_t *)((param_3 & 0xfffffffffffffffeULL) - 8));
}

/* FUN_003f77a0 @ 0x003f77a0   (est. sk_col_pump_003f77a0)
 * Ghidra: void FUN_003f77a0(void)
 * Pumps the collection buffer: fetches the run descriptor (0035128c / the
 * 0006a4c0 context), registers the manager (sk_col_register_003f5268), and
 * either runs the empty-buffer teardown or iterates the element run with
 * the 0031a17c / 0031a1ac advance loop, dispatching each element through
 * sk_col_pump1_003f79a0 / sk_col_pump2_003f79d8. Ends with sk_col_register2_
 * style teardown.
 * Confidence: low */
static void sk_col_pump_003f77a0(void)
{
    word_t *run;
    word_t u2, u4;

    sk_x_00353cfc();
    sk_x_0035128c();
    sk_x_0007c028();
    (*(word_t (**)(word_t))DAT_00658c80)(0);
    sk_x_000aa4ec();
    sk_x_00350ab8();
    sk_x_00350ab8();
    u2 = (word_t)sk_col_register_003f5268();
    run = (word_t *)sk_x_00350ab8();
    u4 = sk_x_0006a4c0(0, run[3]);
    sk_x_000a68c4(run[4]);
    sk_x_00350ab8(0);
    sk_x_00350ab8();
    if (sk_x_00350ab8() == 0) {
        sk_x_00407d64();
        sk_x_0006a4c0();
        sk_x_00353ccc();
        u4 = (word_t)sk_x_0031a26c();
        sk_x_00350a04(u4);
        sk_x_00350ab8();
        if ((sk_x_00350ab8() & 0xff) != 1) {
            sk_x_00350500();
            u4 = (word_t)sk_x_00404cf4();
            sk_col_pump1_003f79a0(0, u4);
        }
        for (;;) {
            sk_x_00407d64();
            sk_x_0006a4c0();
            sk_x_00353ccc();
            u4 = (word_t)sk_x_0031a17c();
            sk_x_00350a04(u4);
            if ((sk_x_00350ab8() & 1) != 0) break;
            sk_x_00407d64();
            sk_x_000836a4();
            sk_x_00353ccc();
            sk_x_0031a1ac();
            sk_x_000bd3a4(0);
            sk_x_00350ab8();
            sk_x_00350500();
            u4 = (word_t)sk_x_00404cf4();
            sk_col_pump2_003f79d8();
            (*(void (**)(word_t))(sk_x_00350ab8() + 8))(0);
        }
        sk_x_000026e8(0);
        sk_x_000026e8(run);
    } else {
        CL4_OBJ_RELEASE(u2);
        sk_x_000026e8(run);
        u2 = u4;
    }
    sk_x_00353d14(u2, 0);
}

/* FUN_003f79a0 @ 0x003f79a0   (est. sk_col_pump1_003f79a0)
 * Ghidra: void FUN_003f79a0(undefined8 param_1,long param_2)
 * Pump helper: builds a descriptor from the element base (param_2+0x10),
 * re-emits it (00351330) and ensures capacity via sk_col_ensure_003f5780.
 * Confidence: low */
static void sk_col_pump1_003f79a0(word_t param_1, sword_t param_2)
{
    word_t d;
    d = sk_x_00404d0c(0, *(word_t *)(param_2 + 0x10));
    sk_x_00351330(d, d, d);
    sk_col_ensure_003f5780();
}

/* FUN_003f79d8 @ 0x003f79d8   (est. sk_col_pump2_003f79d8)
 * Ghidra: void FUN_003f79d8(void)
 * Pump advance: computes the next index (00407b34 + 1), ensures capacity
 * and installs the closure thunk (00359024 / 0040755c / 00405088), then
 * reconfigures via sk_col_cfg_003f540c. Raises overflow trap on index wrap.
 * Confidence: low */
static void sk_col_pump2_003f79d8(void)
{
    sword_t n;

    n = (sword_t)sk_x_00407b34();
    if (!__builtin_add_overflow(n, 1, &n)) {
        sk_x_003504e8();
        sk_x_00404d0c();
        sk_col_ensure_003f5780(n + 1, 0, sk_x_00350ab8());
        sk_x_00407f54();
        (*(word_t (**)(void))DAT_00658c80)();
        sk_x_0008e160();
        *(word_t *)(sk_x_00350ab8() + -0x10) = sk_x_00350ab8();
        *(word_t *)(sk_x_00350ab8() + -8) = sk_x_00350ab8();
        sk_x_00359024();
        sk_x_0040755c((word_t)sk_x_00405088);
        sk_col_cfg_003f540c();
        return;
    }
    __asm__ volatile("brk #1" ::: "memory");   /* SW BP 0x3f7a80 */
}

/* FUN_003f7a80 @ 0x003f7a80   (est. sk_col_pump3_003f7a80)
 * Ghidra: void FUN_003f7a80(undefined8 *param_1,...)
 * Pump wrapper: runs sk_col_pump_003f77a0 and, on the empty-buffer branch,
 * stores the result into *param_1.
 * Confidence: low */
static void sk_col_pump3_003f7a80(word_t *param_1, word_t param_2, sword_t param_3, word_t param_4)
{
    word_t u;

    u = (word_t)sk_col_pump_003f77a0(param_2, *(word_t *)(param_3 + 0x10),
                                     *(word_t *)((param_4 & 0xfffffffffffffffeULL) - 8));
    if (sk_x_00350ab8() == 0) {
        *param_1 = u;
    }
}

/* FUN_003f7ab8 @ 0x003f7ab8   (est. sk_col_box_003f7ab8)
 * Ghidra: undefined1[16] FUN_003f7ab8(void)
 * Produces a 16-byte boxed collection descriptor: fetches the current
 * descriptor (003504d0), reconfigures the run (00404b8c -> 0035053c with
 * the 00404c78 closure) and returns the pair.
 * Confidence: low */
static cl4_pair_t sk_col_box_003f7ab8(void)
{
    cl4_pair_t p, out;
    p = sk_x_003504d0();
    sk_x_00404b8c(0);
    sk_x_0035053c((word_t)&out, (word_t)sk_x_00404c78, 0);
    sk_col_cfg_003f540c();
    sk_x_0036b118();
    return out;
}

/* FUN_003f7b44 @ 0x003f7b44   (est. sk_col_box2_003f7b44)
 * Ghidra: undefined1[16] FUN_003f7b44(undefined8 param_1,...)
 * Boxed descriptor variant that keeps the three incoming words, configures
 * the 00405374 closure run and releases param_1.
 * Confidence: low */
static cl4_pair_t sk_col_box2_003f7b44(word_t param_1, word_t param_2, word_t param_3)
{
    cl4_pair_t out;
    sk_x_00350a64();
    sk_x_00404b8c();
    sk_x_0035053c((word_t)&out, (word_t)sk_x_00405374, 0);
    sk_col_cfg_003f540c();
    sk_x_0036b118(param_1);
    return out;
}

/* FUN_003f7bd8 @ 0x003f7bd8   (est. sk_col_box3_003f7bd8)
 * Ghidra: undefined1 FUN_003f7bd8(void)
 * Single-element box: if the buffer holds one element it retains it and
 * builds a boxed descriptor via sk_col_cfg_003f540c (00404c08 closure);
 * otherwise raises the element-count trap (0x3b).
 * Confidence: low */
static word_t sk_col_box3_003f7bd8(void)
{
    word_t *box;
    word_t u;
    word_t out;

    box = (word_t *)sk_x_00350ab8();
    if (box[1] == box[2]) {
        u = box[0];
        (*(word_t (**)(void))DAT_00658c80)();
        CL4_OBJ_RETAIN(u);
        sk_x_003504a0((word_t)&out, (word_t)sk_x_00404c08);
        sk_col_cfg_003f540c();
        CL4_OBJ_RELEASE(u);
        return out;
    }
    sk_x_00350d04();
    sk_x_004063f4(0x3b);
    sk_x_001afa84();   /* does not return */
}

/* FUN_003f7cc4 @ 0x003f7cc4   (est. sk_col_box4_003f7cc4)
 * Ghidra: undefined8 FUN_003f7cc4(void)
 * Boxed-array constructor: reads the count (sk_col_tag2_003f539c), builds
 * the run via 0040755c with the 0040542c closure and the two metadata tags
 * (0x674330 / 0x66d208), then returns the run id.
 * Confidence: low */
static word_t sk_col_box4_003f7cc4(void)
{
    word_t u, count;

    sk_x_003504d0();
    u = (word_t)sk_col_tag2_003f539c();
    sk_x_0040755c(u, (word_t)sk_x_0040542c, 0, 0, 0x674330, 0x66d208);
    u = (word_t)sk_x_001a73cc();
    sk_x_0036b118();
    return u;
}

/* FUN_003f7d48 @ 0x003f7d48   (est. sk_col_copy5_003f7d48)
 * Ghidra: void FUN_003f7d48(long param_1,...)
 * Validated memory copy of param_2 elements: requires source (param_3) and
 * destination (param_1) counts to match and both pointers non-null, then
 * copies via 0019dadc; on any mismatch raises the fatal copy trap
 * (003488bc/00407984/0034a2f8).
 * Confidence: medium */
static void sk_col_copy5_003f7d48(sword_t param_1, sword_t param_2, sword_t param_3, sword_t param_4)
{
    if (param_2 != param_4) {
        sk_x_004070cc();
        sk_x_0040677c(0x21);
        sk_x_00406518();
        sk_x_001afa84();   /* does not return */
    }
    if (0 < param_2) {
        if ((param_3 != 0) && (param_1 != 0)) {
            sk_x_0019dadc();
            return;
        }
        sk_x_003488bc(1);
        sk_x_00407984();
        sk_x_0034a2f8();
        sk_x_001afe4c();   /* does not return */
    }
}

/* FUN_003f7de0 @ 0x003f7de0   (est. sk_col_box5_003f7de0)
 * Ghidra: undefined1[16] FUN_003f7de0(...)
 * Boxed descriptor constructor with the 00405180 closure: captures the
 * element layout via 00077888, builds the run with 003515b4 / 003722e4 and
 * reconfigures via sk_col_cfg_003f540c.
 * Confidence: low */
static cl4_pair_t sk_col_box5_003f7de0(word_t param_1, word_t param_2, word_t param_3, word_t param_4)
{
    cl4_pair_t out;
    word_t u;
    sk_x_00077888();
    u = (word_t)sk_x_00404b8c(0xff, param_4);
    sk_x_003515b4(0, u, 0x677880);
    sk_x_003722e4();
    sk_x_0035053c((word_t)&out, (word_t)sk_x_00405180, 0);
    sk_col_cfg_003f540c();
    sk_x_0036b118();
    return out;
}

/* FUN_003f7e8c @ 0x003f7e8c   (est. sk_col_slice2_003f7e8c)
 * Ghidra: void FUN_003f7e8c(void)
 * Slice of a Swift._UnsafeBufferPointer: validates the buffer bounds
 * against the requested slice range and copies the sub-range via
 * 001e4cbc. On an invalid slice it raises the runtime fatal naming
 * "Invalid slice" / "Swift._UnsafeBufferPointer.swift".
 * Confidence: medium
 * Notes: s_Invalid_slice_005cfa58, s_Swift_UnsafeBufferPointer_swift_005cdc10;
 *   SoftwareBreakpoint(1) at 0x3f80... (via the fatal path). */
static void sk_col_slice2_003f7e8c(void)
{
    sword_t base, len, off;
    word_t u2, u3;

    sk_x_0034c2e8();
    sk_x_0031b37c(0xff, 0);
    u3 = (word_t)sk_x_004066a4();
    sk_x_00376820(u3, 0);
    sk_x_00350720(0, 0, 0);
    sk_x_0031b080();
    sk_x_0021867c((word_t)&base);
    if (-1 < base) {
        sk_x_0022b584((word_t)&len, 0);
        sk_x_0028c754((word_t)&off, 0);
        if (len <= off) {
            u3 = (word_t)sk_x_004066a4();
            sk_x_00376820(u3, 0);
            sk_x_00350720(0, 0, 0);
            u2 = (word_t)sk_x_0031b080();
            sk_x_0028c754((word_t)&off);
            len = off;
            if (off != 0) {
                sk_x_00408118();
                sk_x_003522b8(base);
                len = len + *(sword_t *)(0 + 0x48) * (sword_t)sk_x_00350ab8();
            }
            sk_x_0022b584((word_t)&off, u2);
            sk_x_00408118();
            sk_x_001e4cbc(len, off - base, 0);
            return;
        }
    }
    sk_x_003488bc(1);
    sk_x_001afe4c(0, 0xb, 2, (word_t)s_Invalid_slice_005cfa58, 0xd, 2,
                  (word_t)s_Swift_UnsafeBufferPointer_swift_005cdc10, 0x1f);
}

/* FUN_003f8024 @ 0x003f8024   (est. sk_col_emit_003f8024)
 * Ghidra: void FUN_003f8024(undefined8 param_1,...)
 * Emits the current element through the 004050b4 closure: sets up the
 * element layout (00310d68), configures the run via sk_col_cfg_003f540c.
 * Confidence: low */
static void sk_col_emit_003f8024(word_t param_1, word_t param_2, word_t param_3,
                                 word_t param_4, word_t param_5, word_t param_6)
{
    sk_x_00310d68(0, param_6);
    sk_x_003518d0(param_1, (word_t)sk_x_004050b4, 0);
    sk_col_cfg_003f540c();
}
