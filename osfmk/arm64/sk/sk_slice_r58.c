/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel,
 * arm64e, image base 0) — the cL4 microkernel (GL1), "cL4 (679.100.61)".
 * Ground truth: Ghidra FUN_ names + addresses in program cl4_kernel.raw.
 * Slice R58: 0x3eefc0-0x3f4164. This is the cL4 notification / tightbeam
 * IPC event-queue region: a collection of continuation-style dispatch
 * helpers (the FUN_00406xxx/00407xxx/00408xxx cluster is the shared event
 * pump / queue primitive library), a coroutine-resume pattern built on the
 * preserved-register object pointer in x20/x22 (the unaff_x20/unaff_x22
 * bases, with per-object continuation slots at offsets 0x10..0x1d8), and a
 * block of Swift-concurrency runtime helpers (task-local, deque storage,
 * bounds/extent arithmetic) that cL4 embeds. Many bodies are small
 * continuations that store a resume function pointer into an object slot and
 * tail into the shared dispatcher; Ghidra flags those as unrecovered
 * indirect-jump tables. All names are estimates (medium confidence) unless
 * string-matched (high).
 *
 * Calling-convention notes:
 *  - unaff_x20/unaff_x21/unaff_x22/unaff_x25 are preserved registers
 *    (callee-saved) that the decompiler kept as opaque bases; they hold the
 *    current event/queue object and its dispatch context. They are rendered
 *    as register locals here.
 *  - "extraout_xN" values are return values that Ghidra tracked flowing from
 *    the immediately preceding helper call into the next call's base register.
 *    They are rendered by capturing the preceding helper's return value.
 *  - The "(*UNRECOVERED_JUMPTABLE)()" tails are tail-calls into the shared
 *    dispatch table (too many branches to recover); rendered as an indirect
 *    call through a code pointer.
 */

#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdbool.h>

typedef uint64_t word_t;
typedef uint32_t seL4_Word;
typedef unsigned char byte;

/* cL4 returns many values as a 16-byte pair (two 64-bit words in x0/x1). */
typedef struct { unsigned long lo, hi; } cL4_w16_t;

/* SoftwareBreakpoint(1, addr) fail-closed trap (Ghidra "Does not return"). */
#define CL4_SW_BP(addr)  __asm__ volatile("brk #1" ::: "memory")

/* ------------------------------------------------------------------ *
 * Out-of-slice helper declarations (extern; bodies reconstructed by the
 * range worker that owns them). Declared with the K&R unspecified-parameter
 * form so call sites may pass any argument list; each returns the 16-byte
 * word pair in x0/x1 (call sites use .lo for single-word uses). The Ghidra
 * FUN_ address is kept in a comment.
 * ------------------------------------------------------------------ */
extern cL4_w16_t cL4_h_00407000();  /* FUN_00407000 */
extern cL4_w16_t cL4_h_0040d07c();  /* FUN_0040d07c */
extern cL4_w16_t cL4_h_0040678c();  /* FUN_0040678c */
extern cL4_w16_t cL4_h_004079cc();  /* FUN_004079cc */
extern cL4_w16_t cL4_h_004070d8();  /* FUN_004070d8 */
extern cL4_w16_t cL4_h_00407f48();  /* FUN_00407f48 */
extern cL4_w16_t cL4_h_0040bd24();  /* FUN_0040bd24 */
extern cL4_w16_t cL4_h_004078f4();  /* FUN_004078f4 */
extern cL4_w16_t cL4_h_00407520();  /* FUN_00407520 */
extern cL4_w16_t cL4_h_00407444();  /* FUN_00407444 */
extern cL4_w16_t cL4_h_00408db8();  /* FUN_00408db8 */
extern cL4_w16_t cL4_h_00406fd4();  /* FUN_00406fd4 */
extern cL4_w16_t cL4_h_00407128();  /* FUN_00407128 */
extern cL4_w16_t cL4_h_00407018();  /* FUN_00407018 */
extern cL4_w16_t cL4_h_0040676c();  /* FUN_0040676c */
extern cL4_w16_t cL4_h_00407248();  /* FUN_00407248 */
extern cL4_w16_t cL4_h_00406734();  /* FUN_00406734 */
extern cL4_w16_t cL4_h_00408130();  /* FUN_00408130 */
extern cL4_w16_t cL4_h_004078e8();  /* FUN_004078e8 */
extern cL4_w16_t cL4_h_00408094();  /* FUN_00408094 */
extern cL4_w16_t cL4_h_00406fe0();  /* FUN_00406fe0 */
extern cL4_w16_t cL4_h_00406c98();  /* FUN_00406c98 */
extern cL4_w16_t cL4_h_004075c4();  /* FUN_004075c4 */
extern cL4_w16_t cL4_h_00407588();  /* FUN_00407588 */
extern cL4_w16_t cL4_h_00408058();  /* FUN_00408058 */
extern cL4_w16_t cL4_h_0040700c();  /* FUN_0040700c */
extern cL4_w16_t cL4_h_00407aa0();  /* FUN_00407aa0 */
extern cL4_w16_t cL4_h_0040711c();  /* FUN_0040711c */
extern cL4_w16_t cL4_h_004081cc();  /* FUN_004081cc */
extern cL4_w16_t cL4_h_00406af4();  /* FUN_00406af4 */
extern cL4_w16_t cL4_h_004081a8();  /* FUN_004081a8 */
extern cL4_w16_t cL4_h_00407ac4();  /* FUN_00407ac4 */
extern cL4_w16_t cL4_h_00407024();  /* FUN_00407024 */
extern cL4_w16_t cL4_h_0040723c();  /* FUN_0040723c */
extern cL4_w16_t cL4_h_00407158();  /* FUN_00407158 */
extern cL4_w16_t cL4_h_00407374();  /* FUN_00407374 */
extern cL4_w16_t cL4_h_0040683c();  /* FUN_0040683c */
extern cL4_w16_t cL4_h_00407594();  /* FUN_00407594 */
extern cL4_w16_t cL4_h_0040686c();  /* FUN_0040686c */
extern cL4_w16_t cL4_h_00407954();  /* FUN_00407954 */
extern cL4_w16_t cL4_h_0040691c();  /* FUN_0040691c */
extern cL4_w16_t cL4_h_0040d99c();  /* FUN_0040d99c */
extern cL4_w16_t cL4_h_00406894();  /* FUN_00406894 */
extern cL4_w16_t cL4_h_0040bb18();  /* FUN_0040bb18 */
extern cL4_w16_t cL4_h_0040f4c8();  /* FUN_0040f4c8 */
extern cL4_w16_t cL4_h_00407610();  /* FUN_00407610 */
extern cL4_w16_t cL4_h_0040752c();  /* FUN_0040752c */
extern cL4_w16_t cL4_h_00406590();  /* FUN_00406590 */
extern cL4_w16_t cL4_h_0040f434();  /* FUN_0040f434 */
extern cL4_w16_t cL4_h_0040833c();  /* FUN_0040833c */
extern cL4_w16_t cL4_h_004084a4();  /* FUN_004084a4 */
extern cL4_w16_t cL4_h_00407924();  /* FUN_00407924 */
extern cL4_w16_t cL4_h_00407ca0();  /* FUN_00407ca0 */
extern cL4_w16_t cL4_h_0040f524();  /* FUN_0040f524 */
extern cL4_w16_t cL4_h_004078d4();  /* FUN_004078d4 */
extern cL4_w16_t cL4_h_004080b0();  /* FUN_004080b0 */
extern cL4_w16_t cL4_h_00406444();  /* FUN_00406444 */
extern cL4_w16_t cL4_h_004064c4();  /* FUN_004064c4 */
extern cL4_w16_t cL4_h_004085a8();  /* FUN_004085a8 */
extern cL4_w16_t cL4_h_00406518();  /* FUN_00406518 */
extern cL4_w16_t cL4_h_00407030();  /* FUN_00407030 */
extern cL4_w16_t cL4_h_004070cc();  /* FUN_004070cc */
extern cL4_w16_t cL4_h_0040677c();  /* FUN_0040677c */
extern cL4_w16_t cL4_h_00408044();  /* FUN_00408044 */
extern cL4_w16_t cL4_h_00406394();  /* FUN_00406394 */
extern cL4_w16_t cL4_h_004083e4();  /* FUN_004083e4 */
extern cL4_w16_t cL4_h_0040d068();  /* FUN_0040d068 */
extern cL4_w16_t cL4_h_00407824();  /* FUN_00407824 */
extern cL4_w16_t cL4_h_00407484();  /* FUN_00407484 */
extern cL4_w16_t cL4_h_004072c0();  /* FUN_004072c0 */
extern cL4_w16_t cL4_h_00408148();  /* FUN_00408148 */
extern cL4_w16_t cL4_h_0040633c();  /* FUN_0040633c */
extern cL4_w16_t cL4_h_00407d74();  /* FUN_00407d74 */
extern cL4_w16_t cL4_h_0040c9d0();  /* FUN_0040c9d0 */
extern cL4_w16_t cL4_h_0040755c();  /* FUN_0040755c */

extern cL4_w16_t cL4_h_000839f8();  /* FUN_000839f8 */
extern cL4_w16_t cL4_h_000839d8();  /* FUN_000839d8 */
extern cL4_w16_t cL4_h_0008e1ec();  /* FUN_0008e1ec */
extern cL4_w16_t cL4_h_0007c1c4();  /* FUN_0007c1c4 */
extern cL4_w16_t cL4_h_0007c028();  /* FUN_0007c028 */
extern cL4_w16_t cL4_h_00084180();  /* FUN_00084180 */
extern cL4_w16_t cL4_h_0008409c();  /* FUN_0008409c */
extern cL4_w16_t cL4_h_000027e8();  /* FUN_000027e8 */
extern cL4_w16_t cL4_h_00002534();  /* FUN_00002534 */

extern cL4_w16_t cL4_h_001afa84() __attribute__((noreturn)); /* FUN_001afa84 (fatal) */
extern cL4_w16_t cL4_h_00100c04();  /* FUN_00100c04 */
extern cL4_w16_t cL4_h_001b1780();  /* FUN_001b1780 */
extern cL4_w16_t cL4_h_001ee018();  /* FUN_001ee018 */
extern cL4_w16_t cL4_h_0019cb68();  /* FUN_0019cb68 */
extern cL4_w16_t cL4_h_0011aa70();  /* FUN_0011aa70 */
extern cL4_w16_t cL4_h_001a8564();  /* FUN_001a8564 */
extern cL4_w16_t cL4_h_001a26e0();  /* FUN_001a26e0 */
extern cL4_w16_t cL4_h_001d88fc();  /* FUN_001d88fc */

extern cL4_w16_t cL4_h_00251758();  /* FUN_00251758 */
extern cL4_w16_t cL4_h_00251820();  /* FUN_00251820 */
extern cL4_w16_t cL4_h_002a4ab4();  /* FUN_002a4ab4 */
extern cL4_w16_t cL4_h_00208418();  /* FUN_00208418 */
extern cL4_w16_t cL4_h_002a4468();  /* FUN_002a4468 */
extern cL4_w16_t cL4_h_00213834();  /* thunk_FUN_00213834 */
extern cL4_w16_t cL4_h_002d49f4();  /* thunk_FUN_002d49f4 */
extern cL4_w16_t cL4_h_0028c754();  /* thunk_FUN_0028c754 */
extern cL4_w16_t cL4_h_0022b584();  /* thunk_FUN_0022b584 */
extern cL4_w16_t cL4_h_002acbb8();  /* thunk_FUN_002acbb8 */
extern cL4_w16_t cL4_h_002298d4();  /* thunk_FUN_002298d4 */
extern cL4_w16_t cL4_h_00027724();  /* FUN_00027724 */

extern cL4_w16_t cL4_h_00350b54();  /* FUN_00350b54 */
extern cL4_w16_t cL4_h_003d4658();  /* FUN_003d4658 */
extern cL4_w16_t cL4_h_00353080();  /* FUN_00353080 */
extern cL4_w16_t cL4_h_00352018();  /* FUN_00352018 */
extern cL4_w16_t cL4_h_00351d24();  /* FUN_00351d24 */
extern cL4_w16_t cL4_h_00350884();  /* FUN_00350884 */
extern cL4_w16_t cL4_h_00351330();  /* FUN_00351330 */
extern cL4_w16_t cL4_h_003510c4();  /* FUN_003510c4 */
extern cL4_w16_t cL4_h_00353c00();  /* FUN_00353c00 */
extern cL4_w16_t cL4_h_003504ac();  /* FUN_003504ac */
extern cL4_w16_t cL4_h_003504a0();  /* FUN_003504a0 */
extern cL4_w16_t cL4_h_003504e8();  /* FUN_003504e8 */
extern cL4_w16_t cL4_h_0031dc0c();  /* FUN_0031dc0c */
extern cL4_w16_t cL4_h_00350744();  /* FUN_00350744 */
extern cL4_w16_t cL4_h_00350750();  /* FUN_00350750 */
extern cL4_w16_t cL4_h_00369340();  /* FUN_00369340 */
extern cL4_w16_t cL4_h_00350798();  /* FUN_00350798 */
extern cL4_w16_t cL4_h_00310d68();  /* FUN_00310d68 */
extern cL4_w16_t cL4_h_00359024();  /* FUN_00359024 */
extern cL4_w16_t cL4_h_003509c8();  /* FUN_003509c8 */
extern cL4_w16_t cL4_h_0035136c();  /* FUN_0035136c */
extern cL4_w16_t cL4_h_003522b8();  /* FUN_003522b8 */
extern cL4_w16_t cL4_h_003539e4();  /* FUN_003539e4 */
extern cL4_w16_t cL4_h_003593c0();  /* FUN_003593c0 */
extern cL4_w16_t cL4_h_0035ac70();  /* FUN_0035ac70 */
extern cL4_w16_t cL4_h_0036a940();  /* FUN_0036a940 */
extern cL4_w16_t cL4_h_0036b118();  /* FUN_0036b118 */
extern cL4_w16_t cL4_h_0036b270();  /* FUN_0036b270 */
extern cL4_w16_t cL4_h_0036b6ac();  /* FUN_0036b6ac */
extern cL4_w16_t cL4_h_0036986c();  /* FUN_0036986c */
extern cL4_w16_t cL4_h_003565a8();  /* FUN_003565a8 */
extern cL4_w16_t cL4_h_003504c4();  /* FUN_003504c4 */
extern cL4_w16_t cL4_h_00351790();  /* FUN_00351790 */
extern cL4_w16_t cL4_h_00350738();  /* FUN_00350738 */
extern cL4_w16_t cL4_h_00356590();  /* FUN_00356590 */
extern cL4_w16_t cL4_h_0035098c();  /* FUN_0035098c */
extern cL4_w16_t cL4_h_00351124();  /* FUN_00351124 */
extern cL4_w16_t cL4_h_0031b37c();  /* FUN_0031b37c */
extern cL4_w16_t cL4_h_00352efc();  /* FUN_00352efc */
extern cL4_w16_t cL4_h_0031de7c();  /* FUN_0031de7c */
extern cL4_w16_t cL4_h_0031b080();  /* FUN_0031b080 */
extern cL4_w16_t cL4_h_0034c2e8();  /* FUN_0034c2e8 */
extern cL4_w16_t cL4_h_0034bcf0();  /* FUN_0034bcf0 */
extern cL4_w16_t cL4_h_00351384();  /* FUN_00351384 */
extern cL4_w16_t cL4_h_003a25d4();  /* FUN_003a25d4 */
extern cL4_w16_t cL4_h_003eeb6c();  /* FUN_003eeb6c */
extern cL4_w16_t cL4_h_0036b6ac2(); /* unused */

/* Additional out-of-slice helpers discovered during transcription. */
extern cL4_w16_t cL4_h_00406c5c();  /* FUN_00406c5c */
extern cL4_w16_t cL4_h_00406a94();  /* FUN_00406a94 */
extern cL4_w16_t cL4_h_004071d0();  /* FUN_004071d0 */
extern cL4_w16_t cL4_h_004075a4();  /* FUN_004075a4 */
extern cL4_w16_t cL4_h_00353498();  /* FUN_00353498 */
extern cL4_w16_t cL4_h_00407954();  /* FUN_00407954 */
extern cL4_w16_t cL4_h_004ba7ec();  /* FUN_004ba7ec */
extern cL4_w16_t cL4_h_00407048();  /* FUN_00407048 */
extern cL4_w16_t cL4_h_0001a1c8();  /* thunk_FUN_0001a1c8 */
extern cL4_w16_t cL4_h_000e15d8();  /* FUN_000e15d8 */
extern cL4_w16_t cL4_h_00376820();  /* FUN_00376820 */
/* out-of-slice callback referenced by FUN_003f32d8 (FUN_003fd3ac) */
extern void sk_r58_003fd3ac(void);
/* remove unused placeholder guard */
/* Forward declarations for in-slice cross-references. */
void sk_r58_003eefc0(void);
void sk_r58_003ef0ac(void);
void sk_r58_003ef178(void);
void sk_r58_003ef3e8(void);
void sk_r58_003ef544(word_t p1, word_t p2, word_t p3);
void sk_r58_003ef6b0(void);
void sk_r58_003ef754(void);
void sk_r58_003ef848(void);
void sk_r58_003ef924(void);
void sk_r58_003ef9b0(void);
void sk_r58_003efb08(void);
void sk_r58_003efbc4(void);
void sk_r58_003efc1c(word_t p1, word_t p2, word_t p3, word_t p4);
void sk_r58_003efcd0(void);
void sk_r58_003efd60(void);
void sk_r58_003efe7c(void);
void sk_r58_003f0054(void);
void sk_r58_003f0110(void);
void sk_r58_003f01c4(void);
void sk_r58_003f0268(void);
void sk_r58_003f0444(void);
void sk_r58_003f0508(void);
void sk_r58_003f05d4(void);
void sk_r58_003f06c0(word_t p1, word_t p2);
void sk_r58_003f075c(void);
void sk_r58_003f08ac(word_t *out);
void sk_r58_003f08dc(void);
void sk_r58_003f099c(void);
void sk_r58_003f0a5c(void);
void sk_r58_003f0b18(void);
void sk_r58_003f0d70(void);
void sk_r58_003f0e4c(void);
void sk_r58_003f0f34(void);
void sk_r58_003f1158(void);
void sk_r58_003f1310(void);
void sk_r58_003f1454(void);
void sk_r58_003f1534(void);
void sk_r58_003f1744(word_t p1, word_t p2, word_t handler);
void sk_r58_003f1990(void);
void sk_r58_003f1a98(void);
void sk_r58_003f1c40(void);
void sk_r58_003f1cb8(void);
void sk_r58_003f1d58(void);
void sk_r58_003f1de8(void);
void sk_r58_003f1ec4(void);
void sk_r58_003f1f5c(void);
void sk_r58_003f1fec(void);
void sk_r58_003f2270(void);
void sk_r58_003f22f4(void);
void sk_r58_003f244c(void);
void sk_r58_003f256c(word_t p1);
void sk_r58_003f2570(word_t p1);
void sk_r58_003f25d4(word_t p1);
void sk_r58_003f274c(void);
void sk_r58_003f27f8(void);
void sk_r58_003f2918(word_t p1, word_t p2, word_t p3, word_t p4, long p5);
void sk_r58_003f29f0(void);
void sk_r58_003f2bb8(void);
void sk_r58_003f2d58(word_t p1, word_t p2, int *tbl);
void sk_r58_003f3058(void);
void sk_r58_003f30b8(word_t *head);
void sk_r58_003f3108(word_t *head, unsigned int flags);
void sk_r58_003f310c(word_t *head, unsigned int flags);
cL4_w16_t sk_r58_003f312c(void);
void sk_r58_003f3218(void);
void sk_r58_003f327c(void);
void sk_r58_003f3280(void);
void sk_r58_003f32b4(void);
void sk_r58_003f32d8(word_t p1, word_t p2, word_t p3);
void sk_r58_003f33f0(void);
void sk_r58_003f345c(void);
void sk_r58_003f34b4(byte flag);
void sk_r58_003f34fc(void);
void sk_r58_003f3524(void);
void sk_r58_003f354c(void);
void sk_r58_003f3574(void);
void sk_r58_003f359c(void);
void sk_r58_003f35a0(void);
void sk_r58_003f35ac(void);
void sk_r58_003f35d4(void);
void sk_r58_003f3610(void);
void sk_r58_003f3650(word_t p1, word_t p2, word_t p3, word_t p4);
void sk_r58_003f36dc(void);
void sk_r58_003f371c(void);
void sk_r58_003f3744(void);
void sk_r58_003f376c(void);
void sk_r58_003f3794(void);
void sk_r58_003f37bc(void);
void sk_r58_003f37e4(void);
void sk_r58_003f380c(void);
void sk_r58_003f3834(void);
void sk_r58_003f3838(void);
void sk_r58_003f3844(void);
void sk_r58_003f386c(void);
void sk_r58_003f38a8(void);
void sk_r58_003f38e8(void);
void sk_r58_003f3910(void);
void sk_r58_003f3938(void);
void sk_r58_003f3960(void);
void sk_r58_003f3a34(void);
void sk_r58_003f3a38(void);
cL4_w16_t sk_r58_003f3a58(void);
void sk_r58_003f3b34(void);
void sk_r58_003f3b58(void);
void sk_r58_003f3b5c(void);
cL4_w16_t sk_r58_003f3b9c(word_t a, word_t b, word_t c);
long sk_r58_003f3cfc(long a, long b);
cL4_w16_t sk_r58_003f3d34(void);
unsigned int sk_r58_003f3db8(void);
unsigned int sk_r58_003f3dbc(void);
unsigned int sk_r58_003f3ddc(void);
unsigned int sk_r58_003f3de0(void);
void sk_r58_003f3dfc(void);
void sk_r58_003f3e34(void);
void sk_r58_003f3e64(word_t *rec, word_t id, long len, word_t data, long off, byte flag);
void sk_r58_003f3ecc(void);
void sk_r58_003f3f50(void);
long sk_r58_003f4040(void);
void sk_r58_003f406c(void);
void sk_r58_003f4164(long src);
void sk_r58_003f3f50_print(void);

/* FUN_003eefc0 @ 0x003eefc0   (est. sk_r58_003eefc0 — event-pump entry continuation)
 * Ghidra: void FUN_003eefc0(void)
 * Wakes the event pump, publishes the per-object pending buffer at obj+0x10,
 * then tail-calls into the shared dispatch table. The jumptable at 0x003ef008
 * could not be recovered (too many branches); the tail is opaque.
 * Confidence: medium
 * Notes: unaff_x22 = object base; UNRECOVERED_JUMPTABLE @0x003ef008. */
void sk_r58_003eefc0(void)
{
    long obj = 0;            /* unaff_x22 */
    cL4_h_00407000();                 /* FUN_00407000 */
    cL4_h_0040d07c((word_t)(obj + 0x10)); /* FUN_0040d07c(obj+0x10) */
    cL4_h_0040678c();                 /* FUN_0040678c */
    /* tail: (*UNRECOVERED_JUMPTABLE)() @0x003ef008 */
}

/* FUN_003ef0ac @ 0x003ef0ac   (est. sk_r58_003ef0ac — queue notify with reservation)
 * Ghidra: void FUN_003ef0ac(void)
 * Acquires a queue lock, reserves a slot (FUN_0040bd24 with the object's
 * notify reservation @self+0x168), then re-arms the dispatcher with the
 * resume continuation FUN_003ef178.
 * Confidence: medium
 * Notes: unaff_x20 = self; DAT-style tagged reservation 0xc31a000000000000. */
void sk_r58_003ef0ac(void)
{
    word_t self = 0;         /* unaff_x20 */
    word_t h16;                       /* extraout_x16 */
    cL4_h_00407000();                 /* FUN_00407000 */
    cL4_h_00407520();                 /* FUN_00407520 */
    h16 = cL4_h_0040bd24(((word_t)&self & 0xffffffffffff) | 0xc31a000000000000,
                         *(word_t *)(self + 0x168)).lo; /* FUN_0040bd24 tagged reserve */
    cL4_h_00407444();                 /* FUN_00407444 */
    cL4_h_00408db8((word_t)&sk_r58_003ef178, *(word_t *)(self + 0x138),
                   *(word_t *)(h16 + 0x140)); /* FUN_00408db8(cont, ...) */
}

/* FUN_003ef178 @ 0x003ef178   (est. sk_r58_003ef178 — notify continuation)
 * Ghidra: void FUN_003ef178(void)
 * Continuation: delivers the object's pending notification, publishes
 * obj+0x10, and tail-calls the shared dispatch table.
 * Confidence: medium
 * Notes: unaff_x22 = object base; UNRECOVERED_JUMPTABLE @0x003ef1d4. */
void sk_r58_003ef178(void)
{
    long obj = 0;            /* unaff_x22 */
    cL4_h_00406fd4();                 /* FUN_00406fd4 */
    cL4_h_0040d07c((word_t)(obj + 0x10)); /* FUN_0040d07c(obj+0x10) */
    cL4_h_0036986c();                 /* FUN_0036986c */
    cL4_h_00407128();                 /* FUN_00407128 */
    /* tail: (*UNRECOVERED_JUMPTABLE)() @0x003ef1d4 */
}

/* FUN_003ef3e8 @ 0x003ef3e8   (est. sk_r58_003ef3e8 — pump teardown continuation)
 * Ghidra: void FUN_003ef3e8(void)
 * Releases the pump's notify reservation and pending buffer then tail-calls
 * the dispatch table.
 * Confidence: medium
 * Notes: extraout_x8/x9 register flow; UNRECOVERED_JUMPTABLE @0x003ef480. */
void sk_r58_003ef3e8(void)
{
    word_t r8 = 0;                    /* extraout_x8 */
    word_t r8b = 0;                   /* extraout_x8_00 */
    word_t r9 = 0;                    /* extraout_x9 */
    cL4_h_00407000();                 /* FUN_00407000 */
    cL4_h_00407018();                 /* FUN_00407018 */
    cL4_h_0040676c();                 /* FUN_0040676c */
    *(word_t *)r9 = r8;               /* *extraout_x9 = extraout_x8 */
    cL4_h_0040bd24(*(word_t *)(r8b + 0x138)); /* FUN_0040bd24(obj+0x138) */
    cL4_h_0040d07c((word_t)(r8 + 0x10));      /* FUN_0040d07c(r8+0x10) */
    cL4_h_0040678c();                 /* FUN_0040678c */
    /* tail: (*UNRECOVERED_JUMPTABLE)() @0x003ef480 */
}

/* FUN_003ef544 @ 0x003ef544   (est. sk_r58_003ef544 — dispatch enter / coroutine kick)
 * Ghidra: void FUN_003ef544(undefined8 param_1,undefined8 param_2,undefined8 param_3)
 * Enters the dispatch pump. Stores the current object word and resume
 * continuation, and if a flag (pair.hi) is clear invokes the empty path,
 * otherwise runs the payload routine before continuing. Re-arms the table.
 * Confidence: medium
 * Notes: unaff_x20 self; unaff_x22 object; extraout_x8 = code ptr from FUN_00406734. */
void sk_r58_003ef544(word_t p1, word_t p2, word_t p3)
{
    word_t self = 0;         /* unaff_x20 */
    long obj = 0;            /* unaff_x22 */
    cL4_w16_t pair;                   /* auVar2 */
    word_t u;
    pair = cL4_h_00406fd4();          /* FUN_00406fd4 */
    *(word_t *)(obj + 0x38) = pair.lo;
    *(word_t *)(obj + 0x40) = self;
    if (pair.hi == 0) {
        cL4_h_00407248();             /* FUN_00407248 */
        u = cL4_h_00407248().lo;      /* extraout_x8_01 (return of 00407248) */
    } else {
        cL4_w16_t r;
        cL4_h_00350b54();             /* FUN_00350b54 */
        cL4_h_003d4658(p3);           /* FUN_003d4658(param_3) */
        r = cL4_h_00406734();         /* FUN_00406734 -> code ptr extraout_x8 */
        ((void (*)(void))r.lo)();     /* (*extraout_x8)() */
        cL4_h_0008e1ec();             /* FUN_0008e1ec */
        u = cL4_h_0008e1ec().lo;      /* extraout_x8_00 */
    }
    *(word_t *)(obj + 0x48) = u;
    *(word_t *)(obj + 0x50) = p3;
    cL4_h_00353080();                 /* FUN_00353080 */
    cL4_h_00408db8();                 /* FUN_00408db8 */
}

/* FUN_003ef6b0 @ 0x003ef6b0   (est. sk_r58_003ef6b0 — pump enter, build state record)
 * Ghidra: void FUN_003ef6b0(void)
 * Enters the pump: captures the queue id, current context, and a fresh
 * state record pointer (allocated by FUN_00406fe0) then runs FUN_003ef544.
 * Confidence: medium
 * Notes: unaff_x22 object; extraout_x8/x16/x17 register flow. */
void sk_r58_003ef6b0(void)
{
    long obj = 0;            /* unaff_x22 */
    word_t r8 = 0;                    /* extraout_x8 */
    word_t e16 = 0;                   /* extraout_x16 */
    word_t e17 = 0;                   /* extraout_x17 */
    cL4_w16_t u;
    word_t *slot;
    cL4_h_00407000();                 /* FUN_00407000 */
    u = cL4_h_00408130();             /* FUN_00408130 */
    *(word_t *)(obj + 0x38) = u.lo;
    cL4_h_00352018();                 /* FUN_00352018 */
    *(word_t *)(obj + 0x40) = e16;
    u = cL4_h_004078e8(*(word_t *)(r8 + 0x40)); /* FUN_004078e8(r8+0x40) */
    *(word_t *)(obj + 0x48) = u.lo;
    cL4_h_00408094();                 /* FUN_00408094 */
    slot = (word_t *)cL4_h_00406fe0().lo; /* FUN_00406fe0 alloc */
    *(word_t **)(obj + 0x50) = slot;
    *slot = e17;
    cL4_h_00406c98();                 /* FUN_00406c98 */
    ((void (*)(void))sk_r58_003ef544)();                /* FUN_003ef544 */
}

/* FUN_003ef754 @ 0x003ef754   (est. sk_r58_003ef754 — pump enter with pending check)
 * Ghidra: void FUN_003ef754(void)
 * Enters the pump, checks the pending flag @obj+0x10; if set runs the
 * payload via FUN_003d4658, else the empty path. Re-arms with continuation
 * FUN_003ef848.
 * Confidence: medium
 * Notes: unaff_x22 object; UNRECOVERED indirect call via extraout_x8_01. */
void sk_r58_003ef754(void)
{
    word_t r8 = 0;                    /* extraout_x8 */
    word_t r8b = 0;                   /* extraout_x8_00 */
    word_t r9 = 0;                    /* extraout_x9 */
    word_t f = 0;                     /* extraout_x8_01 code ptr */
    long pend;
    cL4_h_00406fd4();                 /* FUN_00406fd4 */
    cL4_h_00407018();                 /* FUN_00407018 */
    cL4_h_0040676c();                 /* FUN_0040676c */
    *(word_t *)r9 = r8;
    pend = *(long *)(r8b + 0x10);
    cL4_h_0040bd24(*(word_t *)(r8b + 0x50)); /* FUN_0040bd24(obj+0x50) */
    if (pend == 0) {
        cL4_h_004075c4();             /* FUN_004075c4 */
    } else {
        word_t u = *(word_t *)(r8 + 0x18);
        cL4_h_000027e8();             /* FUN_000027e8 */
        cL4_h_003d4658(u);            /* FUN_003d4658(u) */
        cL4_h_0034bcf0();             /* FUN_0034bcf0 */
        ((void (*)(void))f)();        /* (*extraout_x8_01)() */
        cL4_h_00407588();             /* FUN_00407588 */
    }
    cL4_h_00408db8((word_t)&sk_r58_003ef848, 0); /* FUN_00408db8(FUN_003ef848, in_x3) */
}

/* FUN_003ef848 @ 0x003ef848   (est. sk_r58_003ef848 — pump step continuation)
 * Ghidra: void FUN_003ef848(void)
 * Continuation of the pump step: validates the record via FUN_00351d24 /
 * FUN_00350884 and either completes (tail table) or allocates a fresh state
 * record and re-enters FUN_003ef544.
 * Confidence: medium
 * Notes: unaff_x22 object; UNRECOVERED_JUMPTABLE @0x003ef8b8. */
void sk_r58_003ef848(void)
{
    long obj = 0;            /* unaff_x22 */
    word_t zr = 0;                    /* in_ZR flag */
    cL4_w16_t pair;                   /* auVar4 */
    word_t u1, u3;
    word_t *slot;
    pair = cL4_h_00407000();          /* FUN_00407000 */
    u3 = *(word_t *)(obj + 0x48);
    cL4_h_00351d24(pair.lo, pair.hi, *(word_t *)(obj + 0x30)); /* FUN_00351d24 */
    u1 = cL4_h_00350884().lo;         /* FUN_00350884 */
    if (zr) {
        cL4_h_0040711c(*(word_t *)(obj + 0x40), u1, *(word_t *)(obj + 0x38)); /* FUN_0040711c */
        cL4_h_0040bd24(u3);           /* FUN_0040bd24(u3) */
        cL4_h_00407128();             /* FUN_00407128 */
        /* tail: (*UNRECOVERED_JUMPTABLE)() @0x003ef8b8 */
        return;
    }
    cL4_h_0040711c(*(word_t *)(obj + 0x40), u1, *(word_t *)(obj + 0x38)); /* FUN_0040711c */
    cL4_h_00408094();                 /* FUN_00408094 */
    slot = (word_t *)cL4_h_00406fe0().lo; /* FUN_00406fe0 */
    *(word_t **)(obj + 0x50) = slot;
    *slot = 0;                        /* extraout_x17 */
    cL4_h_00406c98();                 /* FUN_00406c98 */
    ((void (*)(void))sk_r58_003ef544)();                /* FUN_003ef544 */
}

/* FUN_003ef924 @ 0x003ef924   (est. sk_r58_003ef924 — pump enter, variant of 003ef6b0)
 * Ghidra: void FUN_003ef924(void)
 * Mirror of FUN_003ef6b0 but uses FUN_004081cc and FUN_00406af4, then
 * re-enters FUN_003efc1c.
 * Confidence: medium
 * Notes: unaff_x22 object; extraout register flow. */
void sk_r58_003ef924(void)
{
    long obj = 0;            /* unaff_x22 */
    word_t r8 = 0;                    /* extraout_x8 */
    word_t e16 = 0;                   /* extraout_x16 */
    word_t e17 = 0;                   /* extraout_x17 */
    cL4_w16_t u;
    word_t *slot;
    cL4_h_00407000();                 /* FUN_00407000 */
    u = cL4_h_00408130();             /* FUN_00408130 */
    *(word_t *)(obj + 0x38) = u.lo;
    cL4_h_00352018();                 /* FUN_00352018 */
    *(word_t *)(obj + 0x40) = e16;
    u = cL4_h_004078e8(*(word_t *)(r8 + 0x40)); /* FUN_004078e8 */
    *(word_t *)(obj + 0x48) = u.lo;
    cL4_h_004081cc();                 /* FUN_004081cc */
    slot = (word_t *)cL4_h_00406fe0().lo; /* FUN_00406fe0 */
    *(word_t **)(obj + 0x50) = slot;
    *slot = e17;
    cL4_h_00406af4();                 /* FUN_00406af4 */
    ((void (*)(void))sk_r58_003efc1c)();                /* FUN_003efc1c */
}

/* FUN_003ef9b0 @ 0x003ef9b0   (est. sk_r58_003ef9b0 — dispatch with two-phase select)
 * Ghidra: void FUN_003ef9b0(void)
 * Two-phase dispatch: depending on unaff_x20 it selects one of the
 * continuations FUN_003efb08 / FUN_003efbc4 and runs the matching payload.
 * Confidence: medium
 * Notes: unaff_x20 selector; unaff_x21 object; extraout code ptrs. */
void sk_r58_003ef9b0(void)
{
    word_t sel = 0;          /* unaff_x20 */
    long obj = 0;            /* unaff_x21 */
    word_t e16 = 0;                   /* extraout_x16 */
    word_t f0 = 0, f1 = 0;            /* extraout_x8_00 / _01 */
    word_t cb;
    long pend;
    cL4_h_00406fd4();                 /* FUN_00406fd4 */
    cL4_h_0040723c();                 /* FUN_0040723c */
    cL4_h_00407024((word_t)&sel);     /* FUN_00407024(&stack...) */
    cL4_h_0040bd24(*(word_t *)(obj + 0x50)); /* FUN_0040bd24 */
    cL4_h_00407158();                 /* FUN_00407158 */
    pend = *(long *)(e16 + 0x10);
    if (sel == 0) {
        if (pend == 0) {
            cL4_h_004075c4();         /* FUN_004075c4 */
        } else {
            cL4_h_00407374(*(word_t *)(obj + 0x18)); /* FUN_00407374 */
            cL4_h_003504ac();         /* FUN_003504ac */
            ((void (*)(void))f1)();   /* (*extraout_x8_01)() */
            cL4_h_00407588();         /* FUN_00407588 */
        }
        cb = (word_t)&sk_r58_003efb08;
    } else {
        cL4_h_0036b118();             /* FUN_0036b118 */
        if (pend == 0) {
            cL4_h_004075c4();         /* FUN_004075c4 */
        } else {
            word_t u = *(word_t *)(obj + 0x18);
            cL4_h_000027e8();         /* FUN_000027e8 */
            cL4_h_00407374(u);        /* FUN_00407374(u) */
            cL4_h_003504ac();         /* FUN_003504ac */
            ((void (*)(void))f0)();   /* (*extraout_x8_00)() */
            cL4_h_00407588();         /* FUN_00407588 */
        }
        cb = (word_t)&sk_r58_003efbc4;
    }
    cL4_h_00408db8(cb, 0);            /* FUN_00408db8(pcVar2, in_x3) */
}

/* FUN_003efb08 @ 0x003efb08   (est. sk_r58_003efb08 — dispatch continuation A)
 * Ghidra: void FUN_003efb08(void)
 * Continuation that validates and either completes (tail table) or re-enters
 * FUN_003efc1c. Mirror of FUN_003ef848 using the 004081cc/00406af4 path.
 * Confidence: medium
 * Notes: unaff_x22 object; UNRECOVERED_JUMPTABLE @0x003efb78. */
void sk_r58_003efb08(void)
{
    long obj = 0;            /* unaff_x22 */
    word_t zr = 0;                    /* in_ZR */
    cL4_w16_t pair;                   /* auVar4 */
    word_t u1, u3;
    word_t *slot;
    pair = cL4_h_00407000();          /* FUN_00407000 */
    u3 = *(word_t *)(obj + 0x48);
    cL4_h_00351d24(pair.lo, pair.hi, *(word_t *)(obj + 0x30)); /* FUN_00351d24 */
    u1 = cL4_h_00350884().lo;         /* FUN_00350884 */
    if (zr) {
        cL4_h_0040711c(*(word_t *)(obj + 0x40), u1, *(word_t *)(obj + 0x38));
        cL4_h_0040bd24(u3);
        cL4_h_00407128();
        /* tail: (*UNRECOVERED_JUMPTABLE)() @0x003efb78 */
        return;
    }
    cL4_h_0040711c(*(word_t *)(obj + 0x40), u1, *(word_t *)(obj + 0x38));
    cL4_h_004081cc();                 /* FUN_004081cc */
    slot = (word_t *)cL4_h_00406fe0().lo; /* FUN_00406fe0 */
    *(word_t **)(obj + 0x50) = slot;
    *slot = 0;                        /* extraout_x17 */
    cL4_h_00406af4();                 /* FUN_00406af4 */
    ((void (*)(void))sk_r58_003efc1c)();                /* FUN_003efc1c */
}

/* FUN_003efbc4 @ 0x003efbc4   (est. sk_r58_003efbc4 — dispatch continuation B)
 * Ghidra: void FUN_003efbc4(void)
 * Short continuation: allocates a fresh state record and re-enters
 * FUN_003efc1c.
 * Confidence: medium
 * Notes: unaff_x22 object. */
void sk_r58_003efbc4(void)
{
    long obj = 0;            /* unaff_x22 */
    word_t *slot;
    cL4_h_00407000();                 /* FUN_00407000 */
    cL4_h_004081cc();                 /* FUN_004081cc */
    slot = (word_t *)cL4_h_00406fe0().lo; /* FUN_00406fe0 */
    *(word_t **)(obj + 0x50) = slot;
    *slot = 0;                        /* extraout_x17 */
    cL4_h_00406af4();                 /* FUN_00406af4 */
    ((void (*)(void))sk_r58_003efc1c)();                /* FUN_003efc1c */
}

/* FUN_003efc1c @ 0x003efc1c   (est. sk_r58_003efc1c — dispatch enter, 4-arg form)
 * Ghidra: void FUN_003efc1c(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)
 * Enters the pump with four args; if the flag is clear runs the empty path,
 * else runs the payload routine FUN_003d4658 before re-arming with the
 * continuation at LAB_003efcb4.
 * Confidence: medium
 * Notes: unaff_x20 self; unaff_x22 object; extraout_x8 code ptr from 00406734. */
void sk_r58_003efc1c(word_t p1, word_t p2, word_t p3, word_t p4)
{
    word_t self = 0;         /* unaff_x20 */
    long obj = 0;            /* unaff_x22 */
    cL4_w16_t pair;                   /* auVar1 */
    cL4_w16_t r;
    pair = cL4_h_00406fd4();          /* FUN_00406fd4 */
    *(word_t *)(obj + 0x38) = pair.lo;
    *(word_t *)(obj + 0x40) = self;
    if (pair.hi == 0) {
        cL4_h_004075c4();             /* FUN_004075c4 */
    } else {
        cL4_h_00350b54();             /* FUN_00350b54 */
        cL4_h_003d4658(p3);           /* FUN_003d4658(param_3) */
        r = cL4_h_00406734();         /* FUN_00406734 -> code ptr */
        ((void (*)(void))r.lo)();     /* (*extraout_x8)() */
        cL4_h_00407588();             /* FUN_00407588 */
    }
    cL4_h_00408db8(0x003efcb4, p4);   /* FUN_00408db8(&LAB_003efcb4,param_4) */
}

/* FUN_003efcd0 @ 0x003efcd0   (est. sk_r58_003efcd0 — record init / type-name fill)
 * Ghidra: void FUN_003efcd0(void)
 * Allocates a two-word record, fills slot[1] with the global type name
 * DAT_00405fec and hands the record+id to FUN_003eeb6c.
 * Confidence: medium
 * Notes: DAT_00405fec global; FUN_003eeb6c is out-of-slice. */
void sk_r58_003efcd0(void)
{
    cL4_w16_t u;
    word_t *slot;
    extern char cL4_D_00405fec;       /* DAT_00405fec */
    u = cL4_h_00407000();             /* FUN_00407000 */
    cL4_h_004081a8();                 /* FUN_004081a8 */
    slot = (word_t *)cL4_h_00407ac4().lo; /* FUN_00407ac4 alloc */
    *slot = 0;                        /* extraout_x17 */
    slot[1] = (word_t)&cL4_D_00405fec;
    cL4_h_003eeb6c((word_t)(slot + 1), u.lo); /* FUN_003eeb6c(slot+1, uVar1) */
}

/* FUN_003efd60 @ 0x003efd60   (est. sk_r58_003efd60 — pump enter, full state record)
 * Ghidra: void FUN_003efd60(void)
 * Enters the pump building a 7-slot state record: object id/context pair,
 * capability-derived context, two task/context handles and their flags, then
 * runs the pump tail.
 * Confidence: medium
 * Notes: unaff_x20 self; unaff_x22 object; extraout register flow. */
void sk_r58_003efd60(void)
{
    word_t self = 0;         /* unaff_x20 */
    long obj = 0;            /* unaff_x22 */
    word_t r8 = 0, r8b = 0;           /* extraout_x8 / _00 */
    word_t e16 = 0, e16b = 0;         /* extraout_x16 / _00 */
    cL4_w16_t pair;                   /* auVar2 */
    cL4_w16_t u;
    pair = cL4_h_00407000();          /* FUN_00407000 */
    *(word_t *)(obj + 0x48) = pair.hi;
    *(word_t *)(obj + 0x50) = self;
    *(word_t *)(obj + 0x40) = pair.lo;
    *(word_t *)(obj + 0x58) = *(word_t *)(pair.hi + 0x10);
    cL4_h_00350798();                 /* FUN_00350798 */
    u = cL4_h_00310d68();             /* FUN_00310d68 */
    *(word_t *)(obj + 0x60) = u.lo;
    cL4_h_00352018();                 /* FUN_00352018 */
    *(word_t *)(obj + 0x68) = e16;
    u = cL4_h_004078e8(*(word_t *)(r8 + 0x40)); /* FUN_004078e8 */
    *(word_t *)(obj + 0x70) = u.lo;
    cL4_h_0040683c();                 /* FUN_0040683c */
    *(word_t *)(obj + 0x78) = e16b;
    u = cL4_h_004078e8(*(word_t *)(r8b + 0x40)); /* FUN_004078e8 */
    *(word_t *)(obj + 0x80) = u.lo;
    cL4_h_00407594();                 /* FUN_00407594 */
    cL4_h_00408db8();                 /* FUN_00408db8 */
}

/* FUN_003efe7c @ 0x003efe7c   (est. sk_r58_003efe7c — event send with capability handoff)
 * Ghidra: void FUN_003efe7c(void)
 * Sends an event: resolves the destination capability via FUN_000839f8; if
 * it yields 1 it posts the event record (FUN_00407f48) and invokes the
 * registered receiver; otherwise it walks the indirect handler table
 * (obj+0x78 -> slot+0x20) and notifies through it. Releases the capability
 * words and tail-calls the table.
 * Confidence: medium
 * Notes: unaff_x22 object; UNRECOVERED_JUMPTABLE @0x003eff8c. */
void sk_r58_003efe7c(void)
{
    long obj = 0;            /* unaff_x22 */
    word_t u2, u3, u4, u5;
    long l1;
    cL4_w16_t r;
    word_t *slot;
    u2 = cL4_h_004079cc().lo;         /* FUN_004079cc */
    cL4_h_004070d8();                 /* FUN_004070d8 */
    u4 = *(word_t *)(obj + 0x58);
    u3 = cL4_h_000839f8(*(word_t *)(obj + 0x70), 1, u4).lo; /* FUN_000839f8 */
    u5 = *(word_t *)(obj + 0x40);
    l1 = *(long *)(obj + 0x48);
    if ((int)u3 == 1) {
        cL4_h_00407f48(*(word_t *)(obj + 0x68), u3, *(word_t *)(obj + 0x60)); /* FUN_00407f48 */
        r = cL4_h_00407f48(*(word_t *)(obj + 0x68), u3, *(word_t *)(obj + 0x60)); /* extraout_x9 pair */
        cL4_h_003504e8(r.lo, r.hi, *(word_t *)(l1 + 0x18), *(word_t *)(l1 + 0x20)); /* FUN_003504e8 */
        cL4_h_0031dc0c();             /* FUN_0031dc0c */
        cL4_h_00350744(u5);           /* FUN_00350744(u5) */
    } else {
        u3 = *(word_t *)(obj + 0x80);
        slot = *(word_t **)(*(long *)(obj + 0x78) + 0x20);
        cL4_h_003504a0(u3);           /* FUN_003504a0(u3) */
        ((void (*)(void))slot)();     /* (*pcVar6)() */
        r = ((cL4_w16_t(*)(word_t, word_t, word_t))slot)(u5, u3, u4); /* (*pcVar6)(u5,u3,u4) */
        cL4_h_003504e8(r.lo, r.hi, *(word_t *)(l1 + 0x18), *(word_t *)(l1 + 0x20));
        cL4_h_0031dc0c();             /* FUN_0031dc0c */
        r = cL4_h_0007c1c4();         /* FUN_0007c1c4 */
        cL4_h_00369340(r.lo, r.hi, 0);/* FUN_00369340 */
        cL4_h_00350750(u5);           /* FUN_00350750(u5) */
    }
    cL4_h_000839d8();                 /* FUN_000839d8 */
    u5 = *(word_t *)(obj + 0x70);
    cL4_h_0040bd24(*(word_t *)(obj + 0x80)); /* FUN_0040bd24(obj+0x80) */
    cL4_h_0040bd24(u5);               /* FUN_0040bd24(u5) */
    r = cL4_h_0040678c();             /* FUN_0040678c */
    cL4_h_004078f4(r.lo, r.hi, u2);   /* FUN_004078f4 */
    /* tail: (*UNRECOVERED_JUMPTABLE)() @0x003eff8c */
}

/* FUN_003f0054 @ 0x003f0054   (est. sk_r58_003f0054 — pump enter, compact state record)
 * Ghidra: void FUN_003f0054(void)
 * Compact variant of FUN_003efd60 building a 7-slot record at lower offsets
 * (0x10..0x48).
 * Confidence: medium
 * Notes: unaff_x20 self; unaff_x22 object. */
void sk_r58_003f0054(void)
{
    word_t self = 0;         /* unaff_x20 */
    long obj = 0;            /* unaff_x22 */
    word_t r8 = 0, r8b = 0;           /* extraout_x8 / _00 */
    word_t e16 = 0, e16b = 0;         /* extraout_x16 / _00 */
    cL4_w16_t pair;                   /* auVar2 */
    cL4_w16_t u;
    pair = cL4_h_00407000();          /* FUN_00407000 */
    *(word_t *)(obj + 0x10) = pair.lo;
    *(word_t *)(obj + 0x18) = self;
    *(word_t *)(obj + 0x20) = *(word_t *)(pair.hi + 0x10);
    cL4_h_00350798();                 /* FUN_00350798 */
    u = cL4_h_00310d68();             /* FUN_00310d68 */
    *(word_t *)(obj + 0x28) = u.lo;
    cL4_h_00352018();                 /* FUN_00352018 */
    *(word_t *)(obj + 0x30) = e16;
    u = cL4_h_004078e8(*(word_t *)(r8 + 0x40)); /* FUN_004078e8 */
    *(word_t *)(obj + 0x38) = u.lo;
    cL4_h_0040683c();                 /* FUN_0040683c */
    *(word_t *)(obj + 0x40) = e16b;
    u = cL4_h_004078e8(*(word_t *)(r8b + 0x40)); /* FUN_004078e8 */
    *(word_t *)(obj + 0x48) = u.lo;
    cL4_h_00407594();                 /* FUN_00407594 */
    cL4_h_00408db8();                 /* FUN_00408db8 */
}

/* FUN_003f0110 @ 0x003f0110   (est. sk_r58_003f0110 — pump step with early-exit flag)
 * Ghidra: void FUN_003f0110(void)
 * If the object's done-flag (byte at obj[0x18]+8, bit0) is set, completes the
 * step and tails the table; otherwise allocates a fresh record and re-enters
 * FUN_003ef544.
 * Confidence: medium
 * Notes: unaff_x22 object; UNRECOVERED_JUMPTABLE @0x003f0174. */
void sk_r58_003f0110(void)
{
    long obj = 0;            /* unaff_x22 */
    word_t u2;
    word_t *slot;
    cL4_h_00407000();                 /* FUN_00407000 */
    if ((*(byte *)(*(long *)(obj + 0x18) + 8) & 1) != 0) {
        u2 = *(word_t *)(obj + 0x38);
        cL4_h_0040686c();             /* FUN_0040686c */
        cL4_h_0040bd24(u2);           /* FUN_0040bd24(u2) */
        cL4_h_00407128();             /* FUN_00407128 */
        /* tail: (*UNRECOVERED_JUMPTABLE)() @0x003f0174 */
        return;
    }
    cL4_h_00408094();                 /* FUN_00408094 */
    slot = (word_t *)cL4_h_00406fe0().lo; /* FUN_00406fe0 */
    *(word_t **)(obj + 0x50) = slot;
    *slot = 0;                        /* extraout_x17 */
    cL4_h_004071d0();                 /* FUN_004071d0 */
    ((void (*)(void))sk_r58_003ef544)();                /* FUN_003ef544 */
}

/* FUN_003f01c4 @ 0x003f01c4   (est. sk_r58_003f01c4 — pump completion tail)
 * Ghidra: void FUN_003f01c4(void)
 * Releases the object's notify reservation and re-arms the dispatcher.
 * Confidence: medium
 * Notes: extraout_x8 base. */
void sk_r58_003f01c4(void)
{
    word_t r8 = 0;                    /* extraout_x8 */
    cL4_h_00407000();                 /* FUN_00407000 */
    cL4_h_00407018();                 /* FUN_00407018 */
    cL4_h_0040bd24(*(word_t *)(r8 + 0x50)); /* FUN_0040bd24(r8+0x50) */
    cL4_h_00407594();                 /* FUN_00407594 */
    cL4_h_00408db8();                 /* FUN_00408db8 */
}

/* FUN_003f0268 @ 0x003f0268   (est. sk_r58_003f0268 — send payload / claim-continuation)
 * Ghidra: void FUN_003f0268(void)
 * Claims a notification: resolves the payload word via FUN_00351330 /
 * FUN_00350884; on success marks the done-flag at obj[0x18]+8, otherwise
 * invokes the failure handler (unaff_x25). Releases the notify reservation
 * and tails the table.
 * Confidence: medium
 * Notes: unaff_x22 object; unaff_x25 handler; UNRECOVERED_JUMPTABLE @0x003f0340. */
void sk_r58_003f0268(void)
{
    long obj = 0;            /* unaff_x22 */
    word_t handler = 0;      /* unaff_x25 */
    word_t zr = 0;                    /* in_ZR */
    word_t u1, u2, u3;
    long l4;
    cL4_w16_t r;
    u1 = cL4_h_00408058().lo;         /* FUN_00408058 */
    cL4_h_0040700c();                 /* FUN_0040700c */
    u3 = *(word_t *)(obj + 0x20);
    r = cL4_h_00351330();             /* FUN_00351330 */
    u2 = cL4_h_00350884(r.lo, r.hi, u3).lo; /* FUN_00350884 */
    if (!zr) {
        cL4_h_00407aa0();             /* FUN_00407aa0 */
        r = cL4_h_0007c1c4();         /* FUN_0007c1c4 */
        ((void (*)(word_t, word_t, word_t))handler)(r.lo, r.hi, u3); /* (*unaff_x25)() */
        cL4_h_003510c4();             /* FUN_003510c4 */
        ((void (*)(void))handler)();  /* (*unaff_x25)() */
    } else {
        l4 = *(long *)(obj + 0x18);
        cL4_h_00353c00(*(word_t *)(obj + 0x30), u2, *(word_t *)(obj + 0x28)); /* FUN_00353c00 */
        *(byte *)(l4 + 8) = 1;
    }
    u2 = *(word_t *)(obj + 0x38);
    cL4_h_004075a4(*(word_t *)(obj + 0x10), zr); /* FUN_004075a4 */
    cL4_h_0040bd24(u2);               /* FUN_0040bd24 */
    r = cL4_h_00407128();             /* FUN_00407128 */
    cL4_h_00408044(r.lo, r.hi, u1);   /* FUN_00408044 */
    /* tail: (*UNRECOVERED_JUMPTABLE)() @0x003f0340 */
}

/* FUN_003f0444 @ 0x003f0444   (est. sk_r58_003f0444 — pump step, high-offset state)
 * Ghidra: void FUN_003f0444(void)
 * Step continuation using state slots 0x28..0x70; if the done-flag
 * (obj[0x28]+8) is set it completes, else re-enters FUN_003ef544 with a
 * stored continuation FUN_003f0508.
 * Confidence: medium
 * Notes: unaff_x22 object; UNRECOVERED_JUMPTABLE @0x003f04a8. */
void sk_r58_003f0444(void)
{
    long obj = 0;            /* unaff_x22 */
    word_t u2;
    word_t *slot;
    cL4_h_00407000();                 /* FUN_00407000 */
    if ((*(byte *)(*(long *)(obj + 0x28) + 8) & 1) != 0) {
        u2 = *(word_t *)(obj + 0x48);
        cL4_h_0040686c();             /* FUN_0040686c */
        cL4_h_0040bd24(u2);           /* FUN_0040bd24 */
        cL4_h_00407128();             /* FUN_00407128 */
        /* tail: (*UNRECOVERED_JUMPTABLE)() @0x003f04a8 */
        return;
    }
    cL4_h_00408094();                 /* FUN_00408094 */
    slot = (word_t *)cL4_h_00406fe0().lo; /* FUN_00406fe0 */
    *(word_t **)(obj + 0x70) = slot;
    *slot = 0;                        /* extraout_x17 */
    slot[1] = (word_t)&sk_r58_003f0508;
    sk_r58_003ef544(*(word_t *)(obj + 0x48), *(word_t *)(obj + 0x18),
                    *(word_t *)(obj + 0x20)); /* FUN_003ef544 */
}

/* FUN_003f0508 @ 0x003f0508   (est. sk_r58_003f0508 — notify re-arm continuation)
 * Ghidra: void FUN_003f0508(void)
 * Re-arms the dispatcher with continuation FUN_003f05d4.
 * Confidence: medium
 * Notes: unaff_x20 self; tagged reservation 0xc31a000000000000. */
void sk_r58_003f0508(void)
{
    word_t self = 0;         /* unaff_x20 */
    word_t e16 = 0;                   /* extraout_x16 */
    cL4_h_00407000();                 /* FUN_00407000 */
    cL4_h_00407520();                 /* FUN_00407520 */
    cL4_h_0040bd24(((word_t)&self & 0xffffffffffff) | 0xc31a000000000000,
                   *(word_t *)(self + 0x70)); /* FUN_0040bd24 tagged */
    cL4_h_00407444();                 /* FUN_00407444 */
    cL4_h_00408db8((word_t)&sk_r58_003f05d4, *(word_t *)(self + 0x60),
                   *(word_t *)(e16 + 0x68)); /* FUN_00408db8 */
}

/* FUN_003f05d4 @ 0x003f05d4   (est. sk_r58_003f05d4 — send payload, high-slot form)
 * Ghidra: void FUN_003f05d4(void)
 * Mirror of FUN_003f0268 using state slots 0x28..0x48.
 * Confidence: medium
 * Notes: unaff_x22 object; unaff_x25 handler; UNRECOVERED_JUMPTABLE @0x003f06ac. */
void sk_r58_003f05d4(void)
{
    long obj = 0;            /* unaff_x22 */
    word_t handler = 0;      /* unaff_x25 */
    word_t zr = 0;                    /* in_ZR */
    word_t u1, u2, u3;
    long l4;
    cL4_w16_t r;
    u1 = cL4_h_00408058().lo;         /* FUN_00408058 */
    cL4_h_0040700c();                 /* FUN_0040700c */
    u3 = *(word_t *)(obj + 0x30);
    r = cL4_h_00351330();             /* FUN_00351330 */
    u2 = cL4_h_00350884(r.lo, r.hi, u3).lo; /* FUN_00350884 */
    if (!zr) {
        cL4_h_00407aa0();             /* FUN_00407aa0 */
        r = cL4_h_0007c1c4();         /* FUN_0007c1c4 */
        ((void (*)(word_t, word_t, word_t))handler)(r.lo, r.hi, u3);
        cL4_h_003510c4();             /* FUN_003510c4 */
        ((void (*)(void))handler)();
    } else {
        l4 = *(long *)(obj + 0x28);
        cL4_h_00353c00(*(word_t *)(obj + 0x40), u2, *(word_t *)(obj + 0x38)); /* FUN_00353c00 */
        *(byte *)(l4 + 8) = 1;
    }
    u2 = *(word_t *)(obj + 0x48);
    cL4_h_004075a4(*(word_t *)(obj + 0x10), zr); /* FUN_004075a4 */
    cL4_h_0040bd24(u2);               /* FUN_0040bd24 */
    r = cL4_h_00407128();             /* FUN_00407128 */
    cL4_h_00408044(r.lo, r.hi, u1);   /* FUN_00408044 */
    /* tail: (*UNRECOVERED_JUMPTABLE)() @0x003f06ac */
}

/* FUN_003f06c0 @ 0x003f06c0   (est. sk_r58_003f06c0 — record alloc + dispatch enter)
 * Ghidra: void FUN_003f06c0(undefined8 param_1,undefined8 param_2)
 * Allocates a two-word record via FUN_0040bb18, stamps it with the object
 * base and continuation FUN_003f075c, then enters FUN_003f0054.
 * Confidence: medium
 * Notes: unaff_x22 object; DAT_005a01dc global; FUN_003f0054 in-slice. */
void sk_r58_003f06c0(word_t p1, word_t p2)
{
    long obj = 0;            /* unaff_x22 */
    extern word_t cL4_D_005a01dc;     /* DAT_005a01dc */
    word_t *rec;
    rec = (word_t *)cL4_h_0040bb18(cL4_D_005a01dc).lo; /* FUN_0040bb18(DAT_005a01dc) */
    *(word_t **)(obj + 0x10) = rec;
    *rec = (word_t)obj;
    rec[1] = (word_t)&sk_r58_003f075c;
    ((void (*)(word_t, word_t, word_t))sk_r58_003f0054)((word_t)rec, p1, p2); /* FUN_003f0054 */
}

/* FUN_003f075c @ 0x003f075c   (est. sk_r58_003f075c — pump completion continuation)
 * Ghidra: void FUN_003f075c(void)
 * Releases the record reservation and tails the dispatch table.
 * Confidence: medium
 * Notes: extraout_x8 base; UNRECOVERED_JUMPTABLE @0x003f07f4. */
void sk_r58_003f075c(void)
{
    word_t r8 = 0;                    /* extraout_x8 */
    cL4_h_00407000();                 /* FUN_00407000 */
    cL4_h_00407018();                 /* FUN_00407018 */
    cL4_h_0040bd24(*(word_t *)(r8 + 0x10)); /* FUN_0040bd24 */
    cL4_h_0040678c();                 /* FUN_0040678c */
    /* tail: (*UNRECOVERED_JUMPTABLE)() @0x003f07f4 */
}

/* FUN_003f08ac @ 0x003f08ac   (est. sk_r58_003f08ac — context capture)
 * Ghidra: void FUN_003f08ac(undefined8 *param_1)
 * Captures the current context id into *param_1 (via thunk_FUN_000e46d0) and
 * clears the flag byte at param_1[1].
 * Confidence: medium
 * Notes: unaff_x20 context base; thunk_FUN_000e46d0 out-of-slice. */
void sk_r58_003f08ac(word_t *out)
{
    word_t *ctx = 0;         /* unaff_x20 */
    extern cL4_w16_t cL4_h_000e46d0(); /* thunk_FUN_000e46d0 */
    word_t u;
    u = cL4_h_000e46d0(*ctx).lo;
    *out = u;
    *(byte *)(out + 1) = 0;
}

/* FUN_003f08dc @ 0x003f08dc   (est. sk_r58_003f08dc — pump enter, low-offset state)
 * Ghidra: void FUN_003f08dc(void)
 * Compact state-record variant (offsets 0x10..0x50).
 * Confidence: medium
 * Notes: unaff_x20 self; unaff_x22 object. */
void sk_r58_003f08dc(void)
{
    word_t self = 0;         /* unaff_x20 */
    long obj = 0;            /* unaff_x22 */
    word_t r8 = 0, r8b = 0;           /* extraout_x8 / _00 */
    word_t e16 = 0, e16b = 0;         /* extraout_x16 / _00 */
    cL4_w16_t pair;                   /* auVar2 */
    cL4_w16_t u;
    pair = cL4_h_00407000();          /* FUN_00407000 */
    *(word_t *)(obj + 0x18) = pair.hi;
    *(word_t *)(obj + 0x20) = self;
    *(word_t *)(obj + 0x10) = pair.lo;
    *(word_t *)(obj + 0x28) = *(word_t *)(pair.hi + 0x10);
    cL4_h_00350798();                 /* FUN_00350798 */
    u = cL4_h_00310d68();             /* FUN_00310d68 */
    *(word_t *)(obj + 0x30) = u.lo;
    cL4_h_00352018();                 /* FUN_00352018 */
    *(word_t *)(obj + 0x38) = e16;
    u = cL4_h_004078e8(*(word_t *)(r8 + 0x40)); /* FUN_004078e8 */
    *(word_t *)(obj + 0x40) = u.lo;
    cL4_h_0040683c();                 /* FUN_0040683c */
    *(word_t *)(obj + 0x48) = e16b;
    u = cL4_h_004078e8(*(word_t *)(r8b + 0x40)); /* FUN_004078e8 */
    *(word_t *)(obj + 0x50) = u.lo;
    cL4_h_00407594();                 /* FUN_00407594 */
    cL4_h_00408db8();                 /* FUN_00408db8 */
}

/* FUN_003f099c @ 0x003f099c   (est. sk_r58_003f099c — pump step, mid-offset state)
 * Ghidra: void FUN_003f099c(void)
 * Step continuation using slots 0x20..0x58; if done-flag (obj[0x20]+8) set it
 * completes, else allocates a record and re-enters FUN_003efc1c via
 * FUN_00353498.
 * Confidence: medium
 * Notes: unaff_x22 object; UNRECOVERED_JUMPTABLE @0x003f09fc. */
void sk_r58_003f099c(void)
{
    long obj = 0;            /* unaff_x22 */
    word_t *slot;
    cL4_h_00407000();                 /* FUN_00407000 */
    if ((*(byte *)(*(long *)(obj + 0x20) + 8) & 1) != 0) {
        cL4_h_00407954();             /* FUN_00407954 */
        cL4_h_0040686c();             /* FUN_0040686c */
        cL4_h_0040bd24();             /* FUN_0040bd24 */
        cL4_h_0040678c();             /* FUN_0040678c */
        /* tail: (*UNRECOVERED_JUMPTABLE)() @0x003f09fc */
        return;
    }
    cL4_h_004081cc();                 /* FUN_004081cc */
    slot = (word_t *)cL4_h_00406fe0().lo; /* FUN_00406fe0 */
    *(word_t **)(obj + 0x58) = slot;
    *slot = 0;                        /* extraout_x17 */
    slot[1] = (word_t)&sk_r58_003f0a5c;
    cL4_h_00353498(*(word_t *)(obj + 0x40)); /* FUN_00353498 */
    ((void (*)(void))sk_r58_003efc1c)();                /* FUN_003efc1c */
}

/* FUN_003f0a5c @ 0x003f0a5c   (est. sk_r58_003f0a5c — pump resume, branch on status)
 * Ghidra: void FUN_003f0a5c(void)
 * Stores the object base into the record and picks the next continuation
 * (FUN_003f0b18 or LAB_003f0bf4) depending on status, then re-arms.
 * Confidence: medium
 * Notes: unaff_x20 status; extraout register flow. */
void sk_r58_003f0a5c(void)
{
    word_t status = 0;       /* unaff_x20 */
    word_t r8 = 0, r9 = 0, r10 = 0;   /* extraout_x8/x9/x10 */
    word_t u;
    word_t cb;
    cL4_h_00407000();                 /* FUN_00407000 */
    cL4_h_00407018();                 /* FUN_00407018 */
    cL4_h_0040691c();                 /* FUN_0040691c */
    *(word_t *)r10 = r9;              /* *extraout_x10 = extraout_x9 */
    u = *(word_t *)(r8 + 0x58);
    *(word_t *)(r9 + 0x60) = status;
    cL4_h_0040bd24(u);                /* FUN_0040bd24 */
    cb = (status == 0) ? (word_t)&sk_r58_003f0b18 : 0x003f0bf4; /* LAB_003f0bf4 */
    cL4_h_00353498(cb);               /* FUN_00353498(cb) */
    cL4_h_00408db8();                 /* FUN_00408db8 */
}

/* FUN_003f0b18 @ 0x003f0b18   (est. sk_r58_003f0b18 — send payload, low-slot form)
 * Ghidra: void FUN_003f0b18(void)
 * Mirror of FUN_003f0268 using slots 0x20..0x40.
 * Confidence: medium
 * Notes: unaff_x22 object; unaff_x25 handler; UNRECOVERED_JUMPTABLE @0x003f0bf0. */
void sk_r58_003f0b18(void)
{
    long obj = 0;            /* unaff_x22 */
    word_t handler = 0;      /* unaff_x25 */
    word_t zr = 0;                    /* in_ZR */
    word_t u1, u2, u3;
    long l4;
    cL4_w16_t r;
    u1 = cL4_h_00408058().lo;         /* FUN_00408058 */
    cL4_h_0040700c();                 /* FUN_0040700c */
    u3 = *(word_t *)(obj + 0x28);
    r = cL4_h_00351330();             /* FUN_00351330 */
    u2 = cL4_h_00350884(r.lo, r.hi, u3).lo; /* FUN_00350884 */
    if (!zr) {
        cL4_h_00407aa0();             /* FUN_00407aa0 */
        r = cL4_h_0007c1c4();         /* FUN_0007c1c4 */
        ((void (*)(word_t, word_t, word_t))handler)(r.lo, r.hi, u3);
        cL4_h_003510c4();             /* FUN_003510c4 */
        ((void (*)(void))handler)();
    } else {
        l4 = *(long *)(obj + 0x20);
        cL4_h_00353c00(*(word_t *)(obj + 0x38), u2, *(word_t *)(obj + 0x30)); /* FUN_00353c00 */
        *(byte *)(l4 + 8) = 1;
    }
    u2 = *(word_t *)(obj + 0x40);
    cL4_h_004075a4(*(word_t *)(obj + 0x10), zr); /* FUN_004075a4 */
    cL4_h_0040bd24(u2);               /* FUN_0040bd24 */
    r = cL4_h_0040678c();             /* FUN_0040678c */
    cL4_h_00408044(r.lo, r.hi, u1);   /* FUN_00408044 */
    /* tail: (*UNRECOVERED_JUMPTABLE)() @0x003f0bf0 */
}

/* FUN_003f0d70 @ 0x003f0d70   (est. sk_r58_003f0d70 — pump step, high-offset resume)
 * Ghidra: void FUN_003f0d70(void)
 * Step continuation using slots 0x18..0x98; if done-flag (obj[0x38]+8) set
 * completes, else copies the payload words from the record and re-enters
 * FUN_003efc1c.
 * Confidence: medium
 * Notes: unaff_x22 object; UNRECOVERED_JUMPTABLE @0x003f0dd8. */
void sk_r58_003f0d70(void)
{
    long obj = 0;            /* unaff_x22 */
    word_t u2;
    word_t *slot;
    long l3;
    cL4_h_00407000();                 /* FUN_00407000 */
    if ((*(byte *)(*(long *)(obj + 0x38) + 8) & 1) != 0) {
        u2 = *(word_t *)(obj + 0x60);
        cL4_h_00406c5c(*(word_t *)(obj + 0x18)); /* FUN_00406c5c */
        cL4_h_0040bd24(u2);           /* FUN_0040bd24 */
        cL4_h_0040678c();             /* FUN_0040678c */
        /* tail: (*UNRECOVERED_JUMPTABLE)() @0x003f0dd8 */
        return;
    }
    l3 = *(long *)(obj + 0x30);
    cL4_h_004081cc();                 /* FUN_004081cc */
    slot = (word_t *)cL4_h_00406fe0().lo; /* FUN_00406fe0 */
    *(word_t **)(obj + 0x88) = slot;
    *(word_t *)(obj + 0x90) = *(word_t *)(l3 + 0x18);
    *(word_t *)(obj + 0x98) = *(word_t *)(l3 + 0x20);
    *slot = 0;                        /* extraout_x17 */
    slot[1] = (word_t)&sk_r58_003f0e4c;
    ((void (*)(word_t, word_t, word_t))sk_r58_003efc1c)(*(word_t *)(obj + 0x60),
                    *(word_t *)(obj + 0x20),
                    *(word_t *)(obj + 0x28)); /* FUN_003efc1c */
}

/* FUN_003f0e4c @ 0x003f0e4c   (est. sk_r58_003f0e4c — pump resume branch)
 * Ghidra: void FUN_003f0e4c(void)
 * Stores status into the record and selects continuation FUN_003f0f34 or
 * LAB_003f1014, re-arming the dispatcher.
 * Confidence: medium
 * Notes: unaff_x20 status; unaff_x21 object. */
void sk_r58_003f0e4c(void)
{
    word_t status = 0;       /* unaff_x20 */
    long obj = 0;            /* unaff_x21 */
    word_t r8 = 0, r9 = 0;            /* extraout_x8/x9 */
    word_t e16 = 0;                   /* extraout_x16 */
    word_t u;
    word_t cb;
    cL4_h_00406fd4();                 /* FUN_00406fd4 */
    cL4_h_0040723c();                 /* FUN_0040723c */
    cL4_h_0040676c();                 /* FUN_0040676c */
    *(word_t *)r9 = r8;               /* *extraout_x9 = extraout_x8 */
    u = *(word_t *)(obj + 0x88);
    *(word_t *)(r8 + 0xa0) = status;
    cL4_h_0040bd24(u);                /* FUN_0040bd24 */
    cL4_h_00407158();                 /* FUN_00407158 */
    cb = (status == 0) ? (word_t)&sk_r58_003f0f34 : 0x003f1014; /* LAB_003f1014 */
    cL4_h_00408db8(cb, *(word_t *)(obj + 0x78), *(word_t *)(e16 + 0x80)); /* FUN_00408db8 */
}

/* FUN_003f0f34 @ 0x003f0f34   (est. sk_r58_003f0f34 — send payload, vtable dispatch)
 * Ghidra: void FUN_003f0f34(void)
 * Payload sender that routes through an indirect vtable handler
 * (obj[0x68]->slot+0x20) on the failure path, marking the done-flag on
 * success. Uses slots 0x18..0x60.
 * Confidence: medium
 * Notes: unaff_x22 object; UNRECOVERED_JUMPTABLE @0x003f1010. */
void sk_r58_003f0f34(void)
{
    long obj = 0;            /* unaff_x22 */
    word_t zr = 0;                    /* in_ZR */
    word_t u1, u2, u3;
    long l4;
    word_t *vt;
    cL4_w16_t r;
    u1 = cL4_h_00408058().lo;         /* FUN_00408058 */
    cL4_h_0040700c();                 /* FUN_0040700c */
    u3 = *(word_t *)(obj + 0x48);
    r = cL4_h_00351330();             /* FUN_00351330 */
    u2 = cL4_h_00350884(r.lo, r.hi, u3).lo; /* FUN_00350884 */
    if (!zr) {
        u2 = *(word_t *)(obj + 0x18);
        vt = *(word_t **)(*(long *)(obj + 0x68) + 0x20);
        r = cL4_h_0007c1c4();         /* FUN_0007c1c4 */
        ((void (*)(word_t, word_t, word_t))vt)(r.lo, r.hi, u3); /* (*pcVar5)() */
        cL4_h_003510c4(u2);           /* FUN_003510c4(u2) */
        ((void (*)(void))vt)();       /* (*pcVar5)() */
    } else {
        l4 = *(long *)(obj + 0x38);
        cL4_h_00353c00(*(word_t *)(obj + 0x58), u2, *(word_t *)(obj + 0x50)); /* FUN_00353c00 */
        *(byte *)(l4 + 8) = 1;
    }
    u2 = *(word_t *)(obj + 0x60);
    cL4_h_004075a4(*(word_t *)(obj + 0x18), zr); /* FUN_004075a4 */
    cL4_h_0040bd24(u2);               /* FUN_0040bd24 */
    r = cL4_h_0040678c();             /* FUN_0040678c */
    cL4_h_00408044(r.lo, r.hi, u1);   /* FUN_00408044 */
    /* tail: (*UNRECOVERED_JUMPTABLE)() @0x003f1010 */
}

/* FUN_003f1158 @ 0x003f1158   (est. sk_r58_003f1158 — dispatch via vtable slot)
 * Ghidra: void FUN_003f1158(void)
 * Calls the vtable slot at record[0]+8 (record from unaff_x22), after
 * publishing the payload and releasing the reservation.
 * Confidence: medium
 * Notes: unaff_x22 record; UNRECOVERED_JUMPTABLE @0x003f1208. */
void sk_r58_003f1158(void)
{
    word_t *rec = 0;         /* unaff_x22 */
    word_t r8 = 0;                    /* extraout_x8 */
    word_t vt;
    cL4_h_00406fd4();                 /* FUN_00406fd4 */
    cL4_h_00407018();                 /* FUN_00407018 */
    vt = *rec;
    cL4_h_00407158(*(word_t *)(r8 + 0x10)); /* FUN_00407158 */
    cL4_h_0040bd24();                 /* FUN_0040bd24 */
    /* tail: (*UNRECOVERED_JUMPTABLE)() == (**(code **)(vt + 8))() @0x003f1208 */
    ((void (*)(void))(*(word_t *)(vt + 8)))();
}

/* FUN_003f1310 @ 0x003f1310   (est. sk_r58_003f1310 — dispatch with object release)
 * Ghidra: void FUN_003f1310(void)
 * If the status base (unaff_x20) is zero it completes, otherwise runs the
 * object's release path (vtable slot+0x20) and re-arms.
 * Confidence: medium
 * Notes: unaff_x20 status; extraout register flow; UNRECOVERED_JUMPTABLE @0x003f13d8. */
void sk_r58_003f1310(void)
{
    word_t status = 0;       /* unaff_x20 */
    word_t r8 = 0, r8b = 0, r9 = 0;   /* extraout */
    word_t u;
    cL4_h_00407000();                 /* FUN_00407000 */
    cL4_h_00407018();                 /* FUN_00407018 */
    cL4_h_0040676c();                 /* FUN_0040676c */
    *(word_t *)r9 = r8;
    cL4_h_0040bd24(*(word_t *)(r8b + 0x30)); /* FUN_0040bd24 */
    if (status == 0) {
        cL4_h_0040bd24(*(word_t *)(r8 + 0x28)); /* FUN_0040bd24 */
        cL4_h_00407128();             /* FUN_00407128 */
        /* tail: (*UNRECOVERED_JUMPTABLE)() @0x003f13d8 */
    } else {
        u = *(word_t *)(r8 + 0x28);
        ((void (*)(word_t, word_t, word_t))(*(word_t *)(*(long *)(r8 + 0x20) + 0x20)))
            (*(word_t *)(r8 + 0x10), u, *(word_t *)(r8 + 0x18)); /* vtable+0x20 */
        cL4_h_0040bd24(u);            /* FUN_0040bd24 */
        cL4_h_00406a94();             /* FUN_00406a94 */
        /* tail: (*UNRECOVERED_JUMPTABLE)() @0x003f13d8 */
    }
}

/* FUN_003f1454 @ 0x003f1454   (est. sk_r58_003f1454 — bare dispatch tail)
 * Ghidra: void FUN_003f1454(void)
 * Pure tail into the shared dispatch table.
 * Confidence: medium
 * Notes: UNRECOVERED_JUMPTABLE @0x003f1470. */
void sk_r58_003f1454(void)
{
    cL4_h_0040678c();                 /* FUN_0040678c */
    /* tail: (*UNRECOVERED_JUMPTABLE)() @0x003f1470 */
}

/* FUN_003f1534 @ 0x003f1534   (est. sk_r58_003f1534 — notification record submit)
 * Ghidra: void FUN_003f1534(void)
 * Submits a notification record: reads the queue id from record[0x148]+4,
 * publishes the payload buffer and allocates/stamps a submission record, then
 * tails the dispatch table with the queue args.
 * Confidence: medium
 * Notes: unaff_x22 object; UNRECOVERED_JUMPTABLE @0x003f15f0. */
void sk_r58_003f1534(void)
{
    long obj = 0;            /* unaff_x22 */
    word_t u;
    word_t *slot;
    long l3;
    cL4_h_00406fd4();                 /* FUN_00406fd4 */
    l3 = *(long *)(obj + 0x148);
    cL4_h_00359024();                 /* FUN_00359024 */
    u = cL4_h_004083e4().lo;          /* FUN_004083e4 */
    cL4_h_0040d068(u, (word_t)(obj + 0x10)); /* FUN_0040d068(u, &buf) */
    *(word_t *)(obj + 0x138) = (word_t)(obj + 0x10);
    cL4_h_00406394();                 /* FUN_00406394 */
    cL4_h_0040bb18(*(word_t *)(l3 + 4)); /* FUN_0040bb18(record+4) */
    slot = (word_t *)cL4_h_00406fe0().lo; /* FUN_00406fe0 */
    *(word_t **)(obj + 0x168) = slot;
    *slot = 0;                        /* extraout_x17 */
    slot[1] = 0x003f15f4;             /* LAB_003f15f4 */
    /* tail: (*UNRECOVERED_JUMPTABLE)(obj+0x140, obj+0x138) @0x003f15f0 */
}

/* FUN_003f1744 @ 0x003f1744   (est. sk_r58_003f1744 — notification record submit w/ handler)
 * Ghidra: void FUN_003f1744(undefined8 param_1,undefined8 param_2,code *param_3)
 * Variant of FUN_003f1534 that stores the caller-provided handler code as the
 * table entry and publishes through FUN_00407824.
 * Confidence: medium
 * Notes: unaff_x22 object; UNRECOVERED_JUMPTABLE @0x003f1804. */
void sk_r58_003f1744(word_t p1, word_t p2, word_t handler)
{
    long obj = 0;            /* unaff_x22 */
    word_t u1, u2;
    word_t *slot;
    word_t cb = handler;
    cL4_h_00407ca0();                 /* FUN_00407ca0 */
    u1 = cL4_h_0040700c().lo;         /* FUN_0040700c */
    cL4_h_00359024();                 /* FUN_00359024 */
    u2 = cL4_h_004083e4().lo;         /* FUN_004083e4 */
    cL4_h_0040d068(u2, (word_t)(obj + 0x10)); /* FUN_0040d068 */
    *(word_t *)(obj + 0x138) = (word_t)(obj + 0x10);
    cL4_h_00406394();                 /* FUN_00406394 */
    cL4_h_0040bb18(*(word_t *)(handler + 4)); /* FUN_0040bb18(param_3+4) */
    slot = (word_t *)cL4_h_00406fe0().lo; /* FUN_00406fe0 */
    *(word_t **)(obj + 0x140) = slot;
    *slot = 0;                        /* extraout_x17 */
    slot[1] = 0x003f1808;             /* LAB_003f1808 */
    cL4_h_00407824(u1, (word_t)(obj + 0x138)); /* FUN_00407824 */
    /* tail: (*UNRECOVERED_JUMPTABLE)() @0x003f1804 (handler = param_3) */
    ((void (*)(void))cb)();
}

/* FUN_003f1990 @ 0x003f1990   (est. sk_r58_003f1990 — bare dispatch tail 2)
 * Ghidra: void FUN_003f1990(void)
 * Pure tail into the shared dispatch table.
 * Confidence: medium
 * Notes: UNRECOVERED_JUMPTABLE @0x003f19b0. */
void sk_r58_003f1990(void)
{
    cL4_h_00407128();                 /* FUN_00407128 */
    /* tail: (*UNRECOVERED_JUMPTABLE)() @0x003f19b0 */
}

/* FUN_003f1a98 @ 0x003f1a98   (est. sk_r58_003f1a98 — notification record submit, deep slots)
 * Ghidra: void FUN_003f1a98(void)
 * Deep-slot variant of FUN_003f1534 (record at 0x170, submission slot 0x1b0).
 * Confidence: medium
 * Notes: unaff_x22 object; UNRECOVERED_JUMPTABLE @0x003f1b54. */
void sk_r58_003f1a98(void)
{
    long obj = 0;            /* unaff_x22 */
    word_t u;
    word_t *slot;
    long l3;
    cL4_h_00406fd4();                 /* FUN_00406fd4 */
    l3 = *(long *)(obj + 0x170);
    cL4_h_00359024();                 /* FUN_00359024 */
    u = cL4_h_004083e4().lo;          /* FUN_004083e4 */
    cL4_h_0040d068(u, (word_t)(obj + 0x10)); /* FUN_0040d068 */
    *(word_t *)(obj + 0x138) = (word_t)(obj + 0x10);
    cL4_h_00406394();                 /* FUN_00406394 */
    cL4_h_0040bb18(*(word_t *)(l3 + 4)); /* FUN_0040bb18(record+4) */
    slot = (word_t *)cL4_h_00406fe0().lo; /* FUN_00406fe0 */
    *(word_t **)(obj + 0x1b0) = slot;
    *slot = 0;                        /* extraout_x17 */
    slot[1] = 0x003f1b58;             /* LAB_003f1b58 */
    /* tail: (*UNRECOVERED_JUMPTABLE)(obj+400, obj+0x138) @0x003f1b54 */
}

/* FUN_003f1c40 @ 0x003f1c40   (est. sk_r58_003f1c40 — continue with queued context)
 * Ghidra: void FUN_003f1c40(void)
 * Publishes four queued context words to FUN_00406894, installs the resume
 * code pointer returned in extraout_x9 and arms the continuation FUN_003f1cb8
 * via FUN_0040d99c.
 * Confidence: medium
 * Notes: unaff_x22 object; FUN_003f1cb8 in-slice. */
void sk_r58_003f1c40(void)
{
    long obj = 0;            /* unaff_x22 */
    word_t r9 = 0, r10 = 0;           /* extraout_x9/x10 */
    cL4_h_00407000();                 /* FUN_00407000 */
    cL4_h_00406894(*(word_t *)(obj + 0x188), *(word_t *)(obj + 0x198),
                   *(word_t *)(obj + 400), *(word_t *)(obj + 0x180)); /* FUN_00406894 */
    *(word_t **)(obj + 0x1c0) = (word_t *)r9;
    *(word_t *)(obj + 0x1c8) = r10;
    ((void (*)(void))r9)();           /* (*extraout_x9)() */
    cL4_h_0040d99c((word_t)(obj + 0x1e1), *(word_t *)(obj + 0x138), 0,
                   (word_t)&sk_r58_003f1cb8, (word_t)(obj + 0x140)); /* FUN_0040d99c */
}

/* FUN_003f1cb8 @ 0x003f1cb8   (est. sk_r58_003f1cb8 — resume branch on status)
 * Ghidra: void FUN_003f1cb8(void)
 * On nonzero status runs the object's handler (obj[0x188]->slot+8) with the
 * queued args, else takes the empty path, then re-arms via FUN_00353498.
 * Confidence: medium
 * Notes: unaff_x20 status; unaff_x22 object. */
void sk_r58_003f1cb8(void)
{
    word_t status = 0;       /* unaff_x20 */
    long obj = 0;            /* unaff_x22 */
    word_t cb;
    cL4_h_00407000();                 /* FUN_00407000 */
    *(word_t *)(obj + 0x1d0) = status;
    if (status == 0) {
        cb = 0x003f1d3c;              /* LAB_003f1d3c */
    } else {
        ((void (*)(word_t, word_t))(*(word_t *)(*(long *)(obj + 0x188) + 8)))
            (*(word_t *)(obj + 0x198), *(word_t *)(obj + 0x180)); /* vtable+8 */
        cb = 0x003f1dcc;              /* LAB_003f1dcc */
    }
    cL4_h_00353498(cb);               /* FUN_00353498(cb) */
    cL4_h_00408db8();                 /* FUN_00408db8 */
}

/* FUN_003f1d58 @ 0x003f1d58   (est. sk_r58_003f1d58 — dispatch with 4-arg handler)
 * Ghidra: void FUN_003f1d58(void)
 * Invokes the resume handler (obj[0x1c0]) with four queued args, releases the
 * payload words and tails the table.
 * Confidence: medium
 * Notes: unaff_x22 object; UNRECOVERED_JUMPTABLE @0x003f1dc8. */
void sk_r58_003f1d58(void)
{
    long obj = 0;            /* unaff_x22 */
    word_t u1, u2;
    cL4_h_00407000();                 /* FUN_00407000 */
    u1 = *(word_t *)(obj + 400);
    u2 = *(word_t *)(obj + 0x198);
    ((void (*)(word_t, word_t, word_t, word_t))*(word_t *)(obj + 0x1c0))
        (*(word_t *)(obj + 0x1c8), *(word_t *)(obj + 0x168), u2, *(word_t *)(obj + 0x180));
    cL4_h_0040d07c((word_t)(obj + 0x10)); /* FUN_0040d07c */
    cL4_h_0040bd24(u2);               /* FUN_0040bd24 */
    cL4_h_0040bd24(u1);               /* FUN_0040bd24 */
    cL4_h_0040678c();                 /* FUN_0040678c */
    /* tail: (*UNRECOVERED_JUMPTABLE)() @0x003f1dc8 */
}

/* FUN_003f1de8 @ 0x003f1de8   (est. sk_r58_003f1de8 — dispatch completion, no handler)
 * Ghidra: void FUN_003f1de8(void)
 * Releases the payload words and tails the table (completion path).
 * Confidence: medium
 * Notes: unaff_x22 object; UNRECOVERED_JUMPTABLE @0x003f1e50. */
void sk_r58_003f1de8(void)
{
    long obj = 0;            /* unaff_x22 */
    word_t u1, u2;
    cL4_h_00406fd4();                 /* FUN_00406fd4 */
    u1 = *(word_t *)(obj + 400);
    u2 = *(word_t *)(obj + 0x198);
    cL4_h_0040d07c((word_t)(obj + 0x10)); /* FUN_0040d07c */
    cL4_h_0040bd24(u2);               /* FUN_0040bd24 */
    cL4_h_0040bd24(u1);               /* FUN_0040bd24 */
    cL4_h_00407128();                 /* FUN_00407128 */
    /* tail: (*UNRECOVERED_JUMPTABLE)() @0x003f1e50 */
}

/* FUN_003f1ec4 @ 0x003f1ec4   (est. sk_r58_003f1ec4 — resume branch, double notify)
 * Ghidra: void FUN_003f1ec4(void)
 * Stores status and, on the nonzero path, notifies twice via FUN_0036b118,
 * then re-arms.
 * Confidence: medium
 * Notes: unaff_x20 status; unaff_x22 object. */
void sk_r58_003f1ec4(void)
{
    word_t status = 0;       /* unaff_x20 */
    long obj = 0;            /* unaff_x22 */
    word_t cb;
    cL4_h_00407000();                 /* FUN_00407000 */
    *(word_t *)(obj + 0x1d8) = status;
    cL4_h_0036b118(*(word_t *)(obj + 0x1b8)); /* FUN_0036b118 */
    if (status == 0) {
        cb = 0x003f1f40;              /* LAB_003f1f40 */
    } else {
        cL4_h_0036b118(*(word_t *)(obj + 0x1b8)); /* FUN_0036b118 */
        cb = 0x003f1fd0;              /* LAB_003f1fd0 */
    }
    cL4_h_00353498(cb);               /* FUN_00353498(cb) */
    cL4_h_00408db8();                 /* FUN_00408db8 */
}

/* FUN_003f1f5c @ 0x003f1f5c   (est. sk_r58_003f1f5c — dispatch completion w/ notify)
 * Ghidra: void FUN_003f1f5c(void)
 * Notifies then releases payload words and tails the table.
 * Confidence: medium
 * Notes: unaff_x22 object; UNRECOVERED_JUMPTABLE @0x003f1fcc. */
void sk_r58_003f1f5c(void)
{
    long obj = 0;            /* unaff_x22 */
    word_t u1, u2;
    cL4_h_00406fd4();                 /* FUN_00406fd4 */
    cL4_h_0036986c();                 /* FUN_0036986c */
    u1 = *(word_t *)(obj + 400);
    u2 = *(word_t *)(obj + 0x198);
    cL4_h_0040d07c((word_t)(obj + 0x10)); /* FUN_0040d07c */
    cL4_h_0040bd24(u2);               /* FUN_0040bd24 */
    cL4_h_0040bd24(u1);               /* FUN_0040bd24 */
    cL4_h_00407128();                 /* FUN_00407128 */
    /* tail: (*UNRECOVERED_JUMPTABLE)() @0x003f1fcc */
}

/* FUN_003f1fec @ 0x003f1fec   (est. sk_r58_003f1fec — dispatch completion, variant)
 * Ghidra: void FUN_003f1fec(void)
 * Releases payload words and tails the table.
 * Confidence: medium
 * Notes: unaff_x22 object; UNRECOVERED_JUMPTABLE @0x003f2054. */
void sk_r58_003f1fec(void)
{
    long obj = 0;            /* unaff_x22 */
    word_t u1, u2;
    cL4_h_00406fd4();                 /* FUN_00406fd4 */
    u1 = *(word_t *)(obj + 400);
    u2 = *(word_t *)(obj + 0x198);
    cL4_h_0040d07c((word_t)(obj + 0x10)); /* FUN_0040d07c */
    cL4_h_0040bd24(u2);               /* FUN_0040bd24 */
    cL4_h_0040bd24(u1);               /* FUN_0040bd24 */
    cL4_h_00407128();                 /* FUN_00407128 */
    /* tail: (*UNRECOVERED_JUMPTABLE)() @0x003f2054 */
}

/* FUN_003f2270 @ 0x003f2270   (est. sk_r58_003f2270 — resume branch, vtable handler)
 * Ghidra: void FUN_003f2270(void)
 * On nonzero status runs the object's handler (obj[0x178]->slot+8), else the
 * empty path, then re-arms.
 * Confidence: medium
 * Notes: unaff_x20 status; unaff_x22 object. */
void sk_r58_003f2270(void)
{
    word_t status = 0;       /* unaff_x20 */
    long obj = 0;            /* unaff_x22 */
    word_t cb;
    cL4_h_00407000();                 /* FUN_00407000 */
    *(word_t *)(obj + 0x1b0) = status;
    if (status == 0) {
        cb = (word_t)&sk_r58_003f22f4;
    } else {
        ((void (*)(word_t, word_t))(*(word_t *)(*(long *)(obj + 0x178) + 8)))
            (*(word_t *)(obj + 0x188), *(word_t *)(obj + 0x170)); /* vtable+8 */
        cb = 0x003f2364;              /* LAB_003f2364 */
    }
    cL4_h_00353498(cb);               /* FUN_00353498(cb) */
    cL4_h_00408db8();                 /* FUN_00408db8 */
}

/* FUN_003f22f4 @ 0x003f22f4   (est. sk_r58_003f22f4 — dispatch with 4-arg handler 2)
 * Ghidra: void FUN_003f22f4(void)
 * Invokes the resume handler (obj[0x1a0]) with four queued args, releases the
 * payload words and tails the table.
 * Confidence: medium
 * Notes: unaff_x22 object; UNRECOVERED_JUMPTABLE @0x003f2360. */
void sk_r58_003f22f4(void)
{
    long obj = 0;            /* unaff_x22 */
    word_t u1, u2;
    cL4_h_00407000();                 /* FUN_00407000 */
    u1 = *(word_t *)(obj + 0x180);
    u2 = *(word_t *)(obj + 0x188);
    ((void (*)(word_t, word_t, word_t, word_t))*(word_t *)(obj + 0x1a0))
        (*(word_t *)(obj + 0x1a8), *(word_t *)(obj + 0x168), u2, *(word_t *)(obj + 0x170));
    cL4_h_0040d07c((word_t)(obj + 0x10)); /* FUN_0040d07c */
    cL4_h_0040bd24(u2);               /* FUN_0040bd24 */
    cL4_h_0040bd24(u1);               /* FUN_0040bd24 */
    cL4_h_0040678c();                 /* FUN_0040678c */
    /* tail: (*UNRECOVERED_JUMPTABLE)() @0x003f2360 */
}

/* FUN_003f244c @ 0x003f244c   (est. sk_r58_003f244c — dispatch completion w/ notify 2)
 * Ghidra: void FUN_003f244c(void)
 * Notifies, releases payload words and tails the table.
 * Confidence: medium
 * Notes: unaff_x22 object; UNRECOVERED_JUMPTABLE @0x003f24bc. */
void sk_r58_003f244c(void)
{
    long obj = 0;            /* unaff_x22 */
    word_t u1, u2;
    cL4_h_00406fd4();                 /* FUN_00406fd4 */
    cL4_h_0036986c();                 /* FUN_0036986c */
    u1 = *(word_t *)(obj + 0x180);
    u2 = *(word_t *)(obj + 0x188);
    cL4_h_0040d07c((word_t)(obj + 0x10)); /* FUN_0040d07c */
    cL4_h_0040bd24(u2);               /* FUN_0040bd24 */
    cL4_h_0040bd24(u1);               /* FUN_0040bd24 */
    cL4_h_00407128();                 /* FUN_00407128 */
    /* tail: (*UNRECOVERED_JUMPTABLE)() @0x003f24bc */
}

/* FUN_003f256c @ 0x003f256c   (est. sk_r58_003f256c — notification release)
 * Ghidra: void FUN_003f256c(undefined8 param_1)
 * Calls the notification release helper (self[0]->+0x38) with the object and
 * then runs the vtable slot at +0x20.
 * Confidence: medium
 * Notes: unaff_x20 self; extraout_x9/x16 register flow. */
void sk_r58_003f256c(word_t p1)
{
    word_t *self = 0;        /* unaff_x20 */
    word_t r9 = 0, e16 = 0;           /* extraout */
    cL4_h_003509c8(*(word_t *)(*self + 0x38), p1, p1); /* FUN_003509c8 */
    ((void (*)(word_t))*(word_t *)(e16 + 0x20))((word_t)self + r9); /* vtable+0x20 */
}

/* FUN_003f2570 @ 0x003f2570   (est. sk_r58_003f2570 — notification release, mirror)
 * Ghidra: void FUN_003f2570(undefined8 param_1)
 * Identical to FUN_003f256c.
 * Confidence: medium
 * Notes: unaff_x20 self. */
void sk_r58_003f2570(word_t p1)
{
    word_t *self = 0;        /* unaff_x20 */
    word_t r9 = 0, e16 = 0;           /* extraout */
    cL4_h_003509c8(*(word_t *)(*self + 0x38), p1, p1); /* FUN_003509c8 */
    ((void (*)(word_t))*(word_t *)(e16 + 0x20))((word_t)self + r9); /* vtable+0x20 */
}

/* FUN_003f25d4 @ 0x003f25d4   (est. sk_r58_003f25d4 — context lock release / trampoline)
 * Ghidra: void FUN_003f25d4(undefined8 param_1)
 * Resolves the current context base (self + self[0]->+0x40 when
 * FUN_0040f4c8 returns 0) and tail-calls the context vtable slot at
 * *(ctx-8)->+0x10.
 * Confidence: medium
 * Notes: unaff_x20 self; UNRECOVERED_JUMPTABLE @0x003f2660. */
void sk_r58_003f25d4(word_t p1)
{
    word_t *self = 0;        /* unaff_x20 */
    word_t e16 = 0;                   /* extraout_x16 */
    word_t base;
    cL4_h_000027e8();                 /* FUN_000027e8 */
    base = cL4_h_0040f4c8().lo;       /* FUN_0040f4c8 */
    if (base == 0) {
        base = (word_t)self + *(word_t *)(*self + 0x40);
    }
    /* tail: (**(code **)(*(long *)(*(long *)(e16 + 0x38) + -8) + 0x10))(p1, base) @0x003f2660 */
    ((void (*)(word_t, word_t))*(word_t *)(*(long *)(*(long *)(e16 + 0x38) + -8) + 0x10))(p1, base);
}

/* FUN_003f274c @ 0x003f274c   (est. sk_r58_003f274c — notify deliver with handler)
 * Ghidra: void FUN_003f274c(void)
 * Runs the object's deliver handler (obj[0x70]->slot+0x10), allocates a
 * notification record stamped with continuation FUN_003f27f8, publishes six
 * payload words via FUN_00407610, then re-enters FUN_003f2918.
 * Confidence: medium
 * Notes: unaff_x22 object; DAT_005a0234 global. */
void sk_r58_003f274c(void)
{
    long obj = 0;            /* unaff_x22 */
    extern word_t cL4_D_005a0234;     /* DAT_005a0234 */
    word_t *slot;
    cL4_h_00407000();                 /* FUN_00407000 */
    ((void (*)(word_t, word_t, word_t))*(word_t *)(*(long *)(obj + 0x70) + 0x10))
        (*(word_t *)(obj + 0x78), *(word_t *)(obj + 0x18), *(word_t *)(obj + 0x68));
    cL4_h_0040bb18(cL4_D_005a0234);   /* FUN_0040bb18(DAT_005a0234) */
    slot = (word_t *)cL4_h_00406fe0().lo; /* FUN_00406fe0 */
    *(word_t **)(obj + 0x90) = slot;
    *slot = 0;                        /* extraout_x17 */
    slot[1] = (word_t)&sk_r58_003f27f8;
    cL4_h_00407610((word_t)slot, *(word_t *)(obj + 0x78), *(word_t *)(obj + 0x20),
                   *(word_t *)(obj + 0x28), *(word_t *)(obj + 0x30),
                   *(word_t *)(obj + 0x38)); /* FUN_00407610 */
    ((void (*)(void))sk_r58_003f2918)();                /* FUN_003f2918 */
}

/* FUN_003f27f8 @ 0x003f27f8   (est. sk_r58_003f27f8 — resume branch on delivery)
 * Ghidra: void FUN_003f27f8(void)
 * Stores the delivery status and, if nonzero, re-arms with the success
 * continuation (LAB_003f28c8), otherwise releases the record and tails the
 * table.
 * Confidence: medium
 * Notes: unaff_x20 status; UNRECOVERED_JUMPTABLE @0x003f28c4. */
void sk_r58_003f27f8(void)
{
    word_t status = 0;       /* unaff_x20 */
    word_t r8 = 0, r8b = 0, r9 = 0;   /* extraout */
    word_t u;
    cL4_h_00407000();                 /* FUN_00407000 */
    cL4_h_00407018();                 /* FUN_00407018 */
    cL4_h_0040676c();                 /* FUN_0040676c */
    *(word_t *)r9 = r8;
    u = *(word_t *)(r8b + 0x90);
    *(word_t *)(r8 + 0x98) = status;
    cL4_h_0040bd24(u);                /* FUN_0040bd24 */
    if (status != 0) {
        cL4_h_00408db8(0x003f28c8, *(word_t *)(r8 + 0x80), *(word_t *)(r8 + 0x88)); /* LAB_003f28c8 */
        return;
    }
    cL4_h_0040bd24(*(word_t *)(r8 + 0x78)); /* FUN_0040bd24 */
    cL4_h_00407128();                 /* FUN_00407128 */
    /* tail: (*UNRECOVERED_JUMPTABLE)() @0x003f28c4 */
}

/* FUN_003f2918 @ 0x003f2918   (est. sk_r58_003f2918 — dispatch enter, 5-arg form)
 * Ghidra: void FUN_003f2918(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,long param_5)
 * Enters the pump with a 5-arg record: captures the object word, context, a
 * task handle, and on nonzero param_5 runs the payload routine else the empty
 * path. Re-arms the table.
 * Confidence: medium
 * Notes: unaff_x22 object; extraout register flow. */
void sk_r58_003f2918(word_t p1, word_t p2, word_t p3, word_t p4, long p5)
{
    long obj = 0;            /* unaff_x22 */
    word_t r8 = 0;                    /* extraout_x8 */
    word_t f = 0;                     /* extraout_x8_00 */
    word_t f2 = 0;                    /* extraout_x8_01 */
    word_t f3 = 0;                    /* extraout_x8_02 */
    word_t e16 = 0, e16b = 0;         /* extraout_x16/_00 */
    word_t u;
    cL4_h_00406fd4();                 /* FUN_00406fd4 */
    cL4_h_0040752c();                 /* FUN_0040752c */
    cL4_h_000027e8();                 /* FUN_000027e8 */
    *(word_t *)(obj + 0x38) = *(word_t *)(e16 + 0x38);
    cL4_h_0007c028();                 /* FUN_0007c028 */
    *(word_t *)(obj + 0x40) = e16b;
    u = cL4_h_004078e8(*(word_t *)(r8 + 0x40)).lo; /* FUN_004078e8 */
    *(word_t *)(obj + 0x48) = u;
    if (p5 == 0) {
        cL4_h_00407248();             /* FUN_00407248 */
        u = f3;                       /* extraout_x8_02 */
    } else {
        cL4_h_00406590();             /* FUN_00406590 */
        ((void (*)(void))f)();        /* (*extraout_x8_00)() */
        cL4_h_0008e1ec();             /* FUN_0008e1ec */
        u = f2;                       /* extraout_x8_01 */
    }
    *(word_t *)(obj + 0x50) = u;
    *(word_t *)(obj + 0x58) = p3;
    cL4_h_00353080();                 /* FUN_00353080 */
    cL4_h_00408db8();                 /* FUN_00408db8 */
}

/* FUN_003f29f0 @ 0x003f29f0   (est. sk_r58_003f29f0 — table-dispatched operation)
 * Ghidra: void FUN_003f29f0(void)
 * Resolves an operation through FUN_0040833c, runs the handler, then jumps
 * into an entry table: reads the selector int at the operation table and
 * tail-calls (table + selector).
 * Confidence: medium
 * Notes: unaff_x22 object; UNRECOVERED_JUMPTABLE @0x003f2acc. */
void sk_r58_003f29f0(void)
{
    long obj = 0;            /* unaff_x22 */
    word_t u1, u4;
    int *tbl;
    int sel;
    word_t *slot;
    cL4_w16_t r;
    cL4_h_00407ca0();                 /* FUN_00407ca0 */
    u4 = cL4_h_0040700c().lo;         /* FUN_0040700c */
    u1 = *(word_t *)(obj + 0x38);
    tbl = *(int **)(obj + 0x20);
    r = cL4_h_0040833c(*(word_t *)(obj + 0x40), u4, *(word_t *)(obj + 0x18)); /* FUN_0040833c */
    ((void (*)(word_t, word_t, word_t))r.lo)(r.lo, r.hi, u1); /* (*extraout_x9)(auVar6_0,auVar6_8,uVar1) */
    cL4_h_0011aa70();                 /* FUN_0011aa70 */
    cL4_h_0040f434();                 /* FUN_0040f434 */
    sel = *tbl;
    cL4_h_0040bb18(tbl[1]);           /* FUN_0040bb18 */
    slot = (word_t *)cL4_h_00406fe0().lo; /* FUN_00406fe0 */
    *(word_t **)(obj + 0x60) = slot;
    *slot = 0;                        /* extraout_x17 */
    slot[1] = 0x003f2ad0;
    cL4_h_00407610();                 /* FUN_00407610 */
    /* tail: (*(code *)((long)tbl + (long)sel))() @0x003f2acc */
    ((void (*)(void))*(word_t *)((word_t)tbl + (word_t)sel))();
}

/* FUN_003f2bb8 @ 0x003f2bb8   (est. sk_r58_003f2bb8 — dispatch completion tail)
 * Ghidra: void FUN_003f2bb8(void)
 * Releases the payload word and tails the dispatch table.
 * Confidence: medium
 * Notes: unaff_x22 object; UNRECOVERED_JUMPTABLE @0x003f2c08. */
void sk_r58_003f2bb8(void)
{
    long obj = 0;            /* unaff_x22 */
    word_t u;
    cL4_h_00407000();                 /* FUN_00407000 */
    u = *(word_t *)(obj + 0x48);
    cL4_h_0040f524();                 /* FUN_0040f524 */
    cL4_h_0040bd24(u);                /* FUN_0040bd24 */
    cL4_h_0040678c();                 /* FUN_0040678c */
    /* tail: (*UNRECOVERED_JUMPTABLE)() @0x003f2c08 */
}

/* FUN_003f2d58 @ 0x003f2d58   (est. sk_r58_003f2d58 — table-dispatched op, 3-arg)
 * Ghidra: void FUN_003f2d58(undefined8 param_1,undefined8 param_2,int *param_3)
 * Resolves the operation table, runs the handler, then tail-calls into the
 * entry table at (param_3 + *param_3).
 * Confidence: medium
 * Notes: unaff_x22 object; UNRECOVERED_JUMPTABLE @0x003f2e9c. */
void sk_r58_003f2d58(word_t p1, word_t p2, int *tbl)
{
    long obj = 0;            /* unaff_x22 */
    word_t r8 = 0;                    /* extraout_x8 */
    word_t f = 0;                     /* extraout_x8_00 */
    word_t e16 = 0;                   /* extraout_x16 */
    word_t u2, u3;
    int sel;
    word_t *rec;
    cL4_h_004084a4();                 /* FUN_004084a4 */
    u2 = cL4_h_00407924().lo;         /* FUN_00407924 */
    cL4_h_0007c028();                 /* FUN_0007c028 */
    u3 = cL4_h_004078e8(*(word_t *)(r8 + 0x40)).lo; /* FUN_004078e8 */
    *(word_t *)(obj + 0x10) = u3;
    cL4_h_0035136c(*(word_t *)(e16 + 0x20)); /* FUN_0035136c */
    ((void (*)(void))f)();            /* (*extraout_x8_00)() */
    cL4_h_0040f434();                 /* FUN_0040f434 */
    sel = *tbl;
    rec = (word_t *)cL4_h_0040bb18(tbl[1]).lo; /* FUN_0040bb18 */
    *(word_t **)(obj + 0x18) = rec;
    *rec = (word_t)obj;
    rec[1] = 0x003f2ea0;
    /* tail: (*(code *)((long)tbl + (long)sel))(rec, u2) @0x003f2e9c */
    ((void (*)(word_t, word_t))*(word_t *)((word_t)tbl + (word_t)sel))((word_t)rec, u2);
}

/* FUN_003f3058 @ 0x003f3058   (est. sk_r58_tasklocal_illegal_trap — Swift TaskLocal fault)
 * Ghidra: void FUN_003f3058(void)
 * Fatal trap for an illegal TaskLocal operation. Builds the message from the
 * string "Illegal attempt to set a TaskLocal..." (0x5dc160), then tail-calls
 * the noreturn fatal printer FUN_001afa84 with the Swift concurrency source
 * location ("__Concurrency/TaskLocal.swift", 0x5dc140, line 0x1c, col 2).
 * Confidence: high (string-matched)
 * Notes: s__Concurrency_TaskLocal_swift_005dc140; s_Illegal..._005dc160;
 *   FUN_001afa84 is noreturn. */
void sk_r58_003f3058(void)
{
    extern cL4_w16_t cL4_h_0035ac70();
    extern cL4_w16_t cL4_h_003593c0();
    word_t msg;
    msg = cL4_h_0035ac70((word_t)0x005dc160).lo; /* FUN_0035ac70(&"Illegal attempt to set a TaskLocal...") */
    msg = cL4_h_003593c0(msg, msg).lo;           /* FUN_003593c0 */
    cL4_h_001afa84(msg, 0xb, 2, 0xd00000000000004f,
                   0x8000000000000000, 0x005dc140, 0x1c, 2); /* FUN_001afa84 noreturn */
}

/* FUN_003f30b8 @ 0x003f30b8   (est. sk_r58_003f30b8 — list init)
 * Ghidra: void FUN_003f30b8(undefined8 *param_1)
 * Initializes a doubly-linked list head: both links point to itself, then
 * runs FUN_0036b270 and FUN_00084180.
 * Confidence: medium
 * Notes: unaff_x20 self; list head at param_1[0]/[1]. */
void sk_r58_003f30b8(word_t *head)
{
    word_t self = 0;         /* unaff_x20 */
    *head = self;
    head[1] = self;
    cL4_h_0036b270();                 /* FUN_0036b270 */
    cL4_h_00084180();                 /* FUN_00084180 */
}

/* FUN_003f3108 @ 0x003f3108   (est. sk_r58_003f3108 — list destroy)
 * Ghidra: void FUN_003f3108(undefined8 *param_1,uint param_2)
 * On the odd flag, unlinks the head (FUN_0036b270) then traps via
 * FUN_003f3058, otherwise just traps and runs FUN_003f25d4.
 * Confidence: medium
 * Notes: FUN_003f3058 noreturn path. */
void sk_r58_003f3108(word_t *head, unsigned int flags)
{
    if ((flags & 1) != 0) {
        cL4_h_0036b270(*head);        /* FUN_0036b270 */
        sk_r58_003f3058();            /* FUN_003f3058 (noreturn) */
    }
    sk_r58_003f3058();                /* FUN_003f3058 */
    ((void (*)(void))sk_r58_003f25d4)();                /* FUN_003f25d4 */
}

/* FUN_003f310c @ 0x003f310c   (est. sk_r58_003f310c — list destroy, mirror)
 * Ghidra: void FUN_003f310c(undefined8 *param_1,uint param_2)
 * Identical to FUN_003f3108.
 * Confidence: medium
 * Notes: FUN_003f3058 noreturn path. */
void sk_r58_003f310c(word_t *head, unsigned int flags)
{
    if ((flags & 1) != 0) {
        cL4_h_0036b270(*head);        /* FUN_0036b270 */
        sk_r58_003f3058();            /* FUN_003f3058 */
    }
    sk_r58_003f3058();                /* FUN_003f3058 */
    ((void (*)(void))sk_r58_003f25d4)();                /* FUN_003f25d4 */
}

/* FUN_003f312c @ 0x003f312c   (est. sk_r58_003f312c — "Value of failed..." trap builder)
 * Ghidra: undefined1 [16] FUN_003f312c(void)
 * Builds and returns a Swift-trapping diagnostic: prints the failed-value
 * address ("Value of failed:" tag via thunk_FUN_002acbb8 with the 0x746c756166656428
 * = "deflaut"/"Value of failed:" fragments), the object context, then returns
 * a "failed:" string pair. The `FUN_003a25d4` calls push diagnostic frames.
 * Confidence: medium
 * Notes: unaff_x20 self; string fragments 0x746c756166656428 / 0xef203a65756c6156
 *   ("deflaut"+" :Value\xef") and 0x29 / 0xe1. */
cL4_w16_t sk_r58_003f312c(void)
{
    word_t *self = 0;        /* unaff_x20 */
    word_t l2;
    cL4_w16_t out;
    l2 = *self;
    cL4_h_00100c04();                 /* FUN_00100c04 */
    cL4_h_002a4ab4(0x14);             /* FUN_002a4ab4(0x14) */
    cL4_h_00208418(l2, 0);            /* FUN_00208418(l2,0) */
    cL4_h_002acbb8();                 /* thunk_FUN_002acbb8 */
    cL4_h_003a25d4(0);                /* FUN_003a25d4(extraout_x1) */
    cL4_h_002acbb8(0x746c756166656428, 0xef203a65756c6156); /* thunk: "Value of failed:" frags */
    cL4_h_001b1780((word_t)self + *(word_t *)(*self + 0x40), *(word_t *)(l2 + 0x38)); /* FUN_001b1780 */
    cL4_h_002acbb8(0x29, 0xe100000000000000); /* thunk */
    out.lo = 0;
    out.hi = 0;
    return out;                       /* auVar1 (local_40 / uStack_38) */
}

/* FUN_003f3218 @ 0x003f3218   (est. sk_r58_003f3218 — vtable-slot dispatch helper)
 * Ghidra: void FUN_003f3218(void)
 * Calls the notification helper (self[0]->+0x38) then runs vtable slot +8.
 * Confidence: medium
 * Notes: unaff_x20 self; extraout_x9/x16 register flow. */
void sk_r58_003f3218(void)
{
    word_t *self = 0;        /* unaff_x20 */
    word_t r9 = 0, e16 = 0;           /* extraout */
    cL4_h_003509c8(*(word_t *)(*self + 0x38)); /* FUN_003509c8 */
    ((void (*)(word_t))*(word_t *)(e16 + 8))((word_t)self + r9); /* vtable+8 */
}

/* FUN_003f327c @ 0x003f327c   (est. sk_r58_003f327c — vtable dispatch + notify)
 * Ghidra: void FUN_003f327c(void)
 * Runs FUN_003f3218 then notifies via FUN_0036b6ac.
 * Confidence: medium */
void sk_r58_003f327c(void)
{
    sk_r58_003f3218();                /* FUN_003f3218 */
    cL4_h_0036b6ac();                 /* FUN_0036b6ac */
}

/* FUN_003f3280 @ 0x003f3280   (est. sk_r58_003f3280 — vtable dispatch + notify, mirror)
 * Ghidra: void FUN_003f3280(void)
 * Identical to FUN_003f327c.
 * Confidence: medium */
void sk_r58_003f3280(void)
{
    sk_r58_003f3218();                /* FUN_003f3218 */
    cL4_h_0036b6ac();                 /* FUN_0036b6ac */
}

/* FUN_003f32b4 @ 0x003f32b4   (est. sk_r58_003f32b4 — forward to trap builder)
 * Ghidra: void FUN_003f32b4(void)
 * Forwards to FUN_003f312c.
 * Confidence: medium */
void sk_r58_003f32b4(void)
{
    sk_r58_003f312c();                /* FUN_003f312c */
}

/* FUN_003f32d8 @ 0x003f32d8   (est. sk_r58_003f32d8 — Swift value-box tagging / description)
 * Ghidra: void FUN_003f32d8(undefined8 param_1,undefined8 param_2,undefined8 param_3)
 * Classifies a Swift value-box header (unaff_x19/unaff_x21 tag words): if the
 * global DAT_00658c80 handler is armed, it decodes box tags to decide whether
 * to describe an inline box, an indirect box (tag bit 0x3c), or a buffer, and
 * otherwise falls back to the generic description path.
 * Confidence: medium
 * Notes: DAT_00658c80 function pointer global; bit tests >>0x3c/>>0x3d. */
void sk_r58_003f32d8(word_t p1, word_t p2, word_t p3)
{
    extern void (*cL4_D_00658c80)(void); /* DAT_00658c80 */
    word_t tag_hi = 0;       /* unaff_x19 */
    word_t tag_lo = 0;       /* unaff_x21 */
    word_t r8 = 0;                    /* extraout_x8 */
    word_t u, u2;
    cL4_h_0008409c();                 /* FUN_0008409c */
    u = cL4_h_0040c9d0().lo;          /* FUN_0040c9d0 */
    if ((u & 1) != 0) {
        cL4_D_00658c80();             /* (*DAT_00658c80)() */
        cL4_h_003539e4();             /* FUN_003539e4 */
        *(word_t *)(r8 - 0x20) = tag_lo;
        *(word_t *)(r8 - 0x18) = tag_hi;
        *(word_t *)(r8 - 0x10) = p3;
        if ((tag_hi >> 0x3c & 1) == 0) {
            if ((tag_hi >> 0x3d & 1) != 0) {
                cL4_h_00084180();     /* FUN_00084180 */
                u2 = cL4_h_001ee018().lo; /* FUN_001ee018 */
                cL4_h_004ba7ec((word_t)&p3, u2, 1, p3); /* FUN_004ba7ec(&stack, u2, 1, p3) */
                return;
            }
            if ((tag_lo >> 0x3c & 1) != 0) {
                cL4_h_00084180();     /* FUN_00084180 */
                u2 = cL4_h_001ee018().lo; /* FUN_001ee018 */
                cL4_h_004ba7ec((tag_hi & 0xfffffffffffffff) + 0x20, u2, 1, p3); /* FUN_004ba7ec */
                return;
            }
        }
        cL4_h_00359024();             /* FUN_00359024 */
        cL4_h_0040755c((word_t)&sk_r58_003fd3ac); /* FUN_0040755c(FUN_003fd3ac) */
        cL4_h_002a4468();             /* FUN_002a4468 */
    }
}

/* FUN_003f33f0 @ 0x003f33f0   (est. sk_r58_003f33f0 — fatal guard 1)
 * Ghidra: void FUN_003f33f0(void)
 * Runs the guard preamble then tail-calls the noreturn fatal FUN_001afa84.
 * Confidence: medium
 * Notes: FUN_001afa84 noreturn. */
void sk_r58_003f33f0(void)
{
    cL4_h_00406fd4();                 /* FUN_00406fd4 */
    cL4_h_00407030();                 /* FUN_00407030 */
    cL4_h_003593c0();                 /* FUN_003593c0 */
    cL4_h_00407048();                 /* FUN_00407048 */
    cL4_h_001afa84();                 /* FUN_001afa84 noreturn */
}

/* FUN_003f345c @ 0x003f345c   (est. sk_r58_003f345c — fatal guard 2)
 * Ghidra: void FUN_003f345c(void)
 * Identical guard/fatal path to FUN_003f33f0.
 * Confidence: medium
 * Notes: FUN_001afa84 noreturn. */
void sk_r58_003f345c(void)
{
    cL4_h_00406fd4();                 /* FUN_00406fd4 */
    cL4_h_00407030();                 /* FUN_00407030 */
    cL4_h_003593c0();                 /* FUN_003593c0 */
    cL4_h_00407048();                 /* FUN_00407048 */
    cL4_h_001afa84();                 /* FUN_001afa84 noreturn */
}

/* FUN_003f34b4 @ 0x003f34b4   (est. sk_r58_003f34b4 — flag-write helper)
 * Ghidra: void FUN_003f34b4(undefined1 param_1)
 * Writes a flag byte via thunk_FUN_002298d4 and runs FUN_001a8564.
 * Confidence: medium
 * Notes: FUN_004080b0 out-of-slice. */
void sk_r58_003f34b4(byte flag)
{
    cL4_h_004080b0();                 /* FUN_004080b0 */
    cL4_h_002298d4(flag);             /* thunk_FUN_002298d4(param_1) */
    cL4_h_001a8564();                 /* FUN_001a8564 */
}

/* FUN_003f34fc @ 0x003f34fc   (est. sk_r58_003f34fc — dead-end trap A)
 * Ghidra: void FUN_003f34fc(void)
 * Runs FUN_00407030/FUN_00406444 then traps via SoftwareBreakpoint @0x3f3524.
 * Confidence: medium */
void sk_r58_003f34fc(void)
{
    cL4_h_00407030();                 /* FUN_00407030 */
    cL4_h_00406444();                 /* FUN_00406444 */
    CL4_SW_BP(0x3f3524);              /* SoftwareBreakpoint(1,0x3f3524) */
}

/* FUN_003f3524 @ 0x003f3524   (est. sk_r58_003f3524 — dead-end trap B)
 * Ghidra: void FUN_003f3524(void)
 * Trap continuation @0x3f354c.
 * Confidence: medium */
void sk_r58_003f3524(void)
{
    cL4_h_00407030();                 /* FUN_00407030 */
    cL4_h_00406444();                 /* FUN_00406444 */
    CL4_SW_BP(0x3f354c);              /* SoftwareBreakpoint(1,0x3f354c) */
}

/* FUN_003f354c @ 0x003f354c   (est. sk_r58_003f354c — dead-end trap C)
 * Ghidra: void FUN_003f354c(void)
 * Trap continuation @0x3f3574.
 * Confidence: medium */
void sk_r58_003f354c(void)
{
    cL4_h_00407030();                 /* FUN_00407030 */
    cL4_h_00406444();                 /* FUN_00406444 */
    CL4_SW_BP(0x3f3574);              /* SoftwareBreakpoint(1,0x3f3574) */
}

/* FUN_003f3574 @ 0x003f3574   (est. sk_r58_003f3574 — dead-end trap D)
 * Ghidra: void FUN_003f3574(void)
 * Trap continuation @0x3f359c.
 * Confidence: medium */
void sk_r58_003f3574(void)
{
    cL4_h_00407030();                 /* FUN_00407030 */
    cL4_h_00406444();                 /* FUN_00406444 */
    CL4_SW_BP(0x3f359c);              /* SoftwareBreakpoint(1,0x3f359c) */
}

/* FUN_003f359c @ 0x003f359c   (est. sk_r58_003f359c — nested trap, variant)
 * Ghidra: void FUN_003f359c(void)
 * Runs the C-trap first, then the guard and trap @0x3f35d4.
 * Confidence: medium */
void sk_r58_003f359c(void)
{
    sk_r58_003f354c();                /* FUN_003f354c */
    cL4_h_00407030((word_t)&sk_r58_003f35ac); /* FUN_00407030(FUN_003f35ac) */
    cL4_h_00406444();                 /* FUN_00406444 */
    CL4_SW_BP(0x3f35d4);              /* SoftwareBreakpoint(1,0x3f35d4) */
}

/* FUN_003f35a0 @ 0x003f35a0   (est. sk_r58_003f35a0 — nested trap, mirror)
 * Ghidra: void FUN_003f35a0(void)
 * Identical to FUN_003f359c.
 * Confidence: medium */
void sk_r58_003f35a0(void)
{
    sk_r58_003f354c();                /* FUN_003f354c */
    cL4_h_00407030((word_t)&sk_r58_003f35ac); /* FUN_00407030 */
    cL4_h_00406444();                 /* FUN_00406444 */
    CL4_SW_BP(0x3f35d4);              /* SoftwareBreakpoint(1,0x3f35d4) */
}

/* FUN_003f35ac @ 0x003f35ac   (est. sk_r58_003f35ac — dead-end trap E)
 * Ghidra: void FUN_003f35ac(void)
 * Trap continuation @0x3f35d4.
 * Confidence: medium */
void sk_r58_003f35ac(void)
{
    cL4_h_00407030();                 /* FUN_00407030 */
    cL4_h_00406444();                 /* FUN_00406444 */
    CL4_SW_BP(0x3f35d4);              /* SoftwareBreakpoint(1,0x3f35d4) */
}

/* FUN_003f35d4 @ 0x003f35d4   (est. sk_r58_003f35d4 — dead-end trap F)
 * Ghidra: void FUN_003f35d4(void)
 * Trap continuation @0x3f35fc.
 * Confidence: medium */
void sk_r58_003f35d4(void)
{
    cL4_h_00407030();                 /* FUN_00407030 */
    cL4_h_00406444();                 /* FUN_00406444 */
    CL4_SW_BP(0x3f35fc);              /* SoftwareBreakpoint(1,0x3f35fc) */
}

/* FUN_003f3610 @ 0x003f3610   (est. sk_r58_003f3610 — trap preamble only)
 * Ghidra: void FUN_003f3610(void)
 * Runs the guard preamble and returns (no trap in this body).
 * Confidence: medium */
void sk_r58_003f3610(void)
{
    cL4_h_00406fd4();                 /* FUN_00406fd4 */
    cL4_h_00407030();                 /* FUN_00407030 */
    cL4_h_00406444();                 /* FUN_00406444 */
}

/* FUN_003f3650 @ 0x003f3650   (est. sk_r58_003f3650 — dispatch enter w/ flag select)
 * Ghidra: void FUN_003f3650(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)
 * Enters the pump; based on the guard flag either runs the empty path or the
 * payload routine FUN_003d4658, then re-arms with continuation FUN_003f36dc.
 * Confidence: medium
 * Notes: extraout_x1 guard; FUN_003f36dc in-slice. */
void sk_r58_003f3650(word_t p1, word_t p2, word_t p3, word_t p4)
{
    word_t guard = 0;                 /* extraout_x1 */
    word_t f = 0;                     /* extraout_x8 */
    if (guard == 0) {
        cL4_h_004075c4();             /* FUN_004075c4 */
    } else {
        cL4_h_004078d4();             /* FUN_004078d4 */
        cL4_h_003d4658(p3);           /* FUN_003d4658(param_3) */
        cL4_h_0034bcf0();             /* FUN_0034bcf0 */
        ((void (*)(void))f)();        /* (*extraout_x8)() */
        cL4_h_00407588();             /* FUN_00407588 */
    }
    cL4_h_00408db8((word_t)&sk_r58_003f36dc, p4); /* FUN_00408db8(FUN_003f36dc,param_4) */
}

/* FUN_003f36dc @ 0x003f36dc   (est. sk_r58_003f36dc — pump continuation tail)
 * Ghidra: void FUN_003f36dc(void)
 * Runs the guard preamble and returns.
 * Confidence: medium */
void sk_r58_003f36dc(void)
{
    cL4_h_00406fd4();                 /* FUN_00406fd4 */
    cL4_h_00407030();                 /* FUN_00407030 */
    cL4_h_00406444();                 /* FUN_00406444 */
}

/* FUN_003f371c @ 0x003f371c   (est. sk_r58_003f371c — dead-end trap G)
 * Ghidra: void FUN_003f371c(void)
 * Trap @0x3f3744.
 * Confidence: medium */
void sk_r58_003f371c(void)
{
    cL4_h_00407030();                 /* FUN_00407030 */
    cL4_h_00406444();                 /* FUN_00406444 */
    CL4_SW_BP(0x3f3744);
}

/* FUN_003f3744 @ 0x003f3744   (est. sk_r58_003f3744 — dead-end trap H)
 * Ghidra: void FUN_003f3744(void)
 * Trap @0x3f376c.
 * Confidence: medium */
void sk_r58_003f3744(void)
{
    cL4_h_00407030();                 /* FUN_00407030 */
    cL4_h_00406444();                 /* FUN_00406444 */
    CL4_SW_BP(0x3f376c);
}

/* FUN_003f376c @ 0x003f376c   (est. sk_r58_003f376c — dead-end trap I)
 * Ghidra: void FUN_003f376c(void)
 * Trap @0x3f3794.
 * Confidence: medium */
void sk_r58_003f376c(void)
{
    cL4_h_00407030();                 /* FUN_00407030 */
    cL4_h_00406444();                 /* FUN_00406444 */
    CL4_SW_BP(0x3f3794);
}

/* FUN_003f3794 @ 0x003f3794   (est. sk_r58_003f3794 — dead-end trap J, 004064c4)
 * Ghidra: void FUN_003f3794(void)
 * Trap @0x3f37bc using the 004064c4 guard.
 * Confidence: medium */
void sk_r58_003f3794(void)
{
    cL4_h_00407030();                 /* FUN_00407030 */
    cL4_h_004064c4();                 /* FUN_004064c4 */
    CL4_SW_BP(0x3f37bc);
}

/* FUN_003f37bc @ 0x003f37bc   (est. sk_r58_003f37bc — dead-end trap K)
 * Ghidra: void FUN_003f37bc(void)
 * Trap @0x3f37e4.
 * Confidence: medium */
void sk_r58_003f37bc(void)
{
    cL4_h_00407030();                 /* FUN_00407030 */
    cL4_h_004064c4();                 /* FUN_004064c4 */
    CL4_SW_BP(0x3f37e4);
}

/* FUN_003f37e4 @ 0x003f37e4   (est. sk_r58_003f37e4 — dead-end trap L)
 * Ghidra: void FUN_003f37e4(void)
 * Trap @0x3f380c.
 * Confidence: medium */
void sk_r58_003f37e4(void)
{
    cL4_h_00407030();                 /* FUN_00407030 */
    cL4_h_004064c4();                 /* FUN_004064c4 */
    CL4_SW_BP(0x3f380c);
}

/* FUN_003f380c @ 0x003f380c   (est. sk_r58_003f380c — dead-end trap M)
 * Ghidra: void FUN_003f380c(void)
 * Trap @0x3f3834.
 * Confidence: medium */
void sk_r58_003f380c(void)
{
    cL4_h_00407030();                 /* FUN_00407030 */
    cL4_h_004064c4();                 /* FUN_004064c4 */
    CL4_SW_BP(0x3f3834);
}

/* FUN_003f3834 @ 0x003f3834   (est. sk_r58_003f3834 — nested trap, 004064c4 variant)
 * Ghidra: void FUN_003f3834(void)
 * Runs the L-trap then the guard and trap @0x3f386c.
 * Confidence: medium */
void sk_r58_003f3834(void)
{
    sk_r58_003f37e4();                /* FUN_003f37e4 */
    cL4_h_00407030((word_t)&sk_r58_003f3844); /* FUN_00407030 */
    cL4_h_004064c4();                 /* FUN_004064c4 */
    CL4_SW_BP(0x3f386c);
}

/* FUN_003f3838 @ 0x003f3838   (est. sk_r58_003f3838 — nested trap, mirror)
 * Ghidra: void FUN_003f3838(void)
 * Identical to FUN_003f3834.
 * Confidence: medium */
void sk_r58_003f3838(void)
{
    sk_r58_003f37e4();                /* FUN_003f37e4 */
    cL4_h_00407030((word_t)&sk_r58_003f3844); /* FUN_00407030 */
    cL4_h_004064c4();                 /* FUN_004064c4 */
    CL4_SW_BP(0x3f386c);
}

/* FUN_003f3844 @ 0x003f3844   (est. sk_r58_003f3844 — dead-end trap N)
 * Ghidra: void FUN_003f3844(void)
 * Trap @0x3f386c.
 * Confidence: medium */
void sk_r58_003f3844(void)
{
    cL4_h_00407030();                 /* FUN_00407030 */
    cL4_h_004064c4();                 /* FUN_004064c4 */
    CL4_SW_BP(0x3f386c);
}

/* FUN_003f386c @ 0x003f386c   (est. sk_r58_003f386c — dead-end trap O)
 * Ghidra: void FUN_003f386c(void)
 * Trap @0x3f3894.
 * Confidence: medium */
void sk_r58_003f386c(void)
{
    cL4_h_00407030();                 /* FUN_00407030 */
    cL4_h_004064c4();                 /* FUN_004064c4 */
    CL4_SW_BP(0x3f3894);
}

/* FUN_003f38a8 @ 0x003f38a8   (est. sk_r58_003f38a8 — trap preamble only, 004064c4)
 * Ghidra: void FUN_003f38a8(void)
 * Runs the guard preamble and returns.
 * Confidence: medium */
void sk_r58_003f38a8(void)
{
    cL4_h_00406fd4();                 /* FUN_00406fd4 */
    cL4_h_00407030();                 /* FUN_00407030 */
    cL4_h_004064c4();                 /* FUN_004064c4 */
}

/* FUN_003f38e8 @ 0x003f38e8   (est. sk_r58_003f38e8 — dead-end trap P)
 * Ghidra: void FUN_003f38e8(void)
 * Trap @0x3f3910.
 * Confidence: medium */
void sk_r58_003f38e8(void)
{
    cL4_h_00407030();                 /* FUN_00407030 */
    cL4_h_004064c4();                 /* FUN_004064c4 */
    CL4_SW_BP(0x3f3910);
}

/* FUN_003f3910 @ 0x003f3910   (est. sk_r58_003f3910 — dead-end trap Q)
 * Ghidra: void FUN_003f3910(void)
 * Trap @0x3f3938.
 * Confidence: medium */
void sk_r58_003f3910(void)
{
    cL4_h_00407030();                 /* FUN_00407030 */
    cL4_h_004064c4();                 /* FUN_004064c4 */
    CL4_SW_BP(0x3f3938);
}

/* FUN_003f3938 @ 0x003f3938   (est. sk_r58_003f3938 — dead-end trap R)
 * Ghidra: void FUN_003f3938(void)
 * Trap @0x3f3960.
 * Confidence: medium */
void sk_r58_003f3938(void)
{
    cL4_h_00407030();                 /* FUN_00407030 */
    cL4_h_004064c4();                 /* FUN_004064c4 */
    CL4_SW_BP(0x3f3960);
}

/* FUN_003f3960 @ 0x003f3960   (est. sk_r58_003f3960 — buffer advance / span move)
 * Ghidra: void FUN_003f3960(void)
 * Advances a span: reads the object's current word @self[0]+0x58, computes a
 * slice via FUN_00251758/FUN_00251820 (base/len stride), and moves the tail
 * through FUN_0019cb68 with overflow traps (SCARRY/SBORROW -> brk @0x3f3a2c..).
 * Confidence: medium
 * Notes: unaff_x20 self; SCARRY8/SBORROW8 overflow checks. */
void sk_r58_003f3960(void)
{
    word_t *self = 0;        /* unaff_x20 */
    word_t l8, l1, l2, l6, l7;
    word_t *p;
    word_t u9;
    bool borrow;
    word_t e16 = 0, e16b = 0;         /* extraout_x16/_00 */
    word_t r8 = 0, r8b = 0;           /* extraout_x8/_00 */
    l8 = *self;
    p = (word_t *)cL4_h_00251758().lo;/* FUN_00251758 */
    l6 = cL4_h_00251820().lo;         /* FUN_00251820 */
    u9 = *(word_t *)(l8 + 0x58);
    l8 = p[1];
    l1 = p[2];
    if ((l1 + l8) < l8) {             /* SCARRY8(l1,l8) */
        CL4_SW_BP(0x3f3a2c);
    }
    l7 = p[0];
    if (l7 < l1 + l8) {
        l2 = l7 - l1;
        if (l7 < l1) {                /* SBORROW8(l7,l1) */
            CL4_SW_BP(0x3f3a30);
        }
        cL4_h_003522b8();             /* FUN_003522b8 */
        cL4_h_0019cb68(l2, l6 + *(word_t *)(e16 + 0x48) * r8, u9); /* FUN_0019cb68 */
        borrow = (l8 < l2);           /* SBORROW8(l8,l2) */
        l8 = l8 - l2;
        if (borrow) {
            CL4_SW_BP(0x3f3a34);
        }
    } else {
        cL4_h_003522b8();             /* FUN_003522b8 */
        l6 = l6 + *(word_t *)(e16b + 0x48) * r8b;
    }
    cL4_h_0019cb68(l8, l6, u9);       /* FUN_0019cb68 */
    cL4_h_00213834();                 /* thunk_FUN_00213834 */
}

/* FUN_003f3a34 @ 0x003f3a34   (est. sk_r58_003f3a34 — span move + notify)
 * Ghidra: void FUN_003f3a34(void)
 * Runs FUN_003f3960 then notifies via FUN_0036b6ac (tag 7, size 0x28).
 * Confidence: medium */
void sk_r58_003f3a34(void)
{
    word_t u;
    u = cL4_h_0036b6ac(0, 0x28, 7).lo; /* FUN_0036b6ac(uVar1,0x28,7) */
}

/* FUN_003f3a38 @ 0x003f3a38   (est. sk_r58_003f3a38 — span move + notify, mirror)
 * Ghidra: void FUN_003f3a38(void)
 * Identical to FUN_003f3a34.
 * Confidence: medium */
void sk_r58_003f3a38(void)
{
    word_t u;
    u = cL4_h_0036b6ac(0, 0x28, 7).lo; /* FUN_0036b6ac */
}

/* FUN_003f3a58 @ 0x003f3a58   (est. sk_r58_003f3a58 — "_DequeuStorage<...>" type-name builder)
 * Ghidra: undefined1 [16] FUN_003f3a58(void)
 * Builds and returns the Swift type-name string "_DequeuStorage<..." for the
 * deque storage object: reads the storage base/len (self[0]->+0x58), prints
 * the header via FUN_003a25d4 / thunk_FUN_002acbb8 fragments and the element
 * via FUN_003f3b9c, then returns the name pair.
 * Confidence: high (string-matched: returned 0x745365757165445f/0xee003c656761726f
 *   little-endian == "_DequeuStorage<")
 * Notes: unaff_x20 self; string fragments 0x3e / 0xe1. */
cL4_w16_t sk_r58_003f3a58(void)
{
    word_t *self = 0;        /* unaff_x20 */
    word_t *p;
    word_t l3;
    word_t u4;
    cL4_w16_t out;
    l3 = *self;
    p = (word_t *)cL4_h_00251758().lo;/* FUN_00251758 */
    cL4_h_00251820();                 /* FUN_00251820 */
    u4 = *(word_t *)(l3 + 0x58);
    cL4_h_00100c04();                 /* FUN_00100c04 */
    cL4_h_002a4ab4(0x13);             /* FUN_002a4ab4(0x13) */
    cL4_h_003a25d4(0);                /* FUN_003a25d4(local_38) */
    cL4_h_00208418(u4, 0);            /* FUN_00208418(u4,0) */
    cL4_h_002acbb8();                 /* thunk_FUN_002acbb8 */
    cL4_h_003a25d4(0);                /* FUN_003a25d4(extraout_x1) */
    cL4_h_002acbb8(0x3e, 0xe100000000000000); /* thunk: ">" tag */
    sk_r58_003f3b9c(*p, p[1], p[2]);  /* FUN_003f3b9c */
    cL4_h_002acbb8();                 /* thunk_FUN_002acbb8 */
    cL4_h_003a25d4(0);                /* FUN_003a25d4(extraout_x1_00) */
    out.lo = 0x745365757165445f;      /* auVar1._0_8_ : "_DequeuStorage<" */
    out.hi = 0xee003c656761726f;      /* auVar1._8_8_ */
    return out;
}

/* FUN_003f3b34 @ 0x003f3b34   (est. sk_r58_003f3b34 — forward to type-name builder)
 * Ghidra: void FUN_003f3b34(void)
 * Forwards to FUN_003f3a58.
 * Confidence: medium */
void sk_r58_003f3b34(void)
{
    sk_r58_003f3a58();                /* FUN_003f3a58 */
}

/* FUN_003f3b58 @ 0x003f3b58   (est. sk_r58_003f3b58 — lazy object init 1)
 * Ghidra: void FUN_003f3b58(void)
 * Initializes the global object DAT_006adf70 via FUN_00002534 (name lookup
 * at 0x657990 with DAT_005a16f8) and FUN_0036a940, then zeroes its method
 * slots at +0x10/+0x18/+0x20.
 * Confidence: medium
 * Notes: DAT_006adf70 global; DAT_005a16f8 global. */
void sk_r58_003f3b58(void)
{
    extern word_t cL4_D_006adf70;     /* _DAT_006adf70 */
    extern char cL4_D_005a16f8;       /* DAT_005a16f8 */
    word_t u, obj;
    u = cL4_h_00002534(0x657990, (word_t)&cL4_D_005a16f8).lo; /* FUN_00002534 */
    obj = cL4_h_0036a940(u, 0x28, 7).lo; /* FUN_0036a940 */
    cL4_D_006adf70 = obj;
    *(word_t *)(obj + 0x18) = 0;
    *(word_t *)(obj + 0x20) = 0;
    *(word_t *)(obj + 0x10) = 0;
}

/* FUN_003f3b5c @ 0x003f3b5c   (est. sk_r58_003f3b5c — lazy object init 2)
 * Ghidra: void FUN_003f3b5c(void)
 * Identical to FUN_003f3b58.
 * Confidence: medium
 * Notes: DAT_006adf70 global. */
void sk_r58_003f3b5c(void)
{
    extern word_t cL4_D_006adf70;     /* _DAT_006adf70 */
    extern char cL4_D_005a16f8;       /* DAT_005a16f8 */
    word_t u, obj;
    u = cL4_h_00002534(0x657990, (word_t)&cL4_D_005a16f8).lo; /* FUN_00002534 */
    obj = cL4_h_0036a940(u, 0x28, 7).lo; /* FUN_0036a940 */
    cL4_D_006adf70 = obj;
    *(word_t *)(obj + 0x18) = 0;
    *(word_t *)(obj + 0x20) = 0;
    *(word_t *)(obj + 0x10) = 0;
}

/* FUN_003f3b9c @ 0x003f3b9c   (est. sk_r58_003f3b9c — "(capacity: N, count: ...)" printer)
 * Ghidra: undefined1 [16] FUN_003f3b9c(void)
 * Prints a Swift collection header via two vtable-slot calls (FUN_00027724 at
 * 0x6720e0 / FUN_00351384), emitting "capacity: " and " count: " fragments
 * (thunk_FUN_002acbb8 with 0x3a746e756f63202c = ", count:" reversed), then
 * returns the "(capacity" + "y: " name pair.
 * Confidence: medium
 * Notes: string fragments 0x3a746e756f63202c/0xe900000000000020 and
 *   0x537472617473202c/0xed0000203a746f6c; 0x7469636170616328/0xeb00000000203a79. */
cL4_w16_t sk_r58_003f3b9c(word_t a, word_t b, word_t c)
{
    word_t fn;
    cL4_w16_t out;
    extern cL4_w16_t cL4_h_000b430c(); /* FUN_000b430c */
    extern cL4_w16_t cL4_h_000e72d4(); /* FUN_000e72d4 */
    extern cL4_w16_t cL4_h_00408108(); /* FUN_00408108 */
    cL4_h_00350b54();                 /* FUN_00350b54 */
    cL4_h_000b430c();                 /* FUN_000b430c */
    cL4_h_002a4ab4(0x28);             /* FUN_002a4ab4(0x28) */
    cL4_h_003a25d4(0);                /* FUN_003a25d4(local_58) */
    fn = cL4_h_00027724(0x6720e0).lo; /* FUN_00027724(0x6720e0) */
    cL4_h_00351384();                 /* FUN_00351384 */
    ((void (*)(void))fn)();           /* (*pcVar2)() */
    cL4_h_002acbb8();                 /* thunk */
    cL4_h_003a25d4(0);                /* FUN_003a25d4 */
    cL4_h_002acbb8(0x3a746e756f63202c, 0xe900000000000020); /* ", count:" frags */
    cL4_h_00351384();                 /* FUN_00351384 */
    ((void (*)(void))fn)();           /* (*pcVar2)() */
    cL4_h_002acbb8();                 /* thunk */
    cL4_h_003a25d4(0);                /* FUN_003a25d4 */
    cL4_h_002acbb8(0x537472617473202c, 0xed0000203a746f6c); /* ", stats" frags */
    sk_r58_003f3d34();                 /* FUN_003f3d34 */
    cL4_h_000e72d4();                 /* FUN_000e72d4 */
    cL4_h_003a25d4();                 /* FUN_003a25d4 */
    cL4_h_00408108();                 /* FUN_00408108 */
    out.lo = 0x7469636170616328;      /* "(capacity" */
    out.hi = 0xeb00000000203a79;      /* "y: " */
    return out;
}

/* FUN_003f3cfc @ 0x003f3cfc   (est. sk_r58_003f3cfc — clamp-bounds helper)
 * Ghidra: long FUN_003f3cfc(long param_1,long param_2)
 * If param_2 < 1 and (param_1 < 0), re-derived bounds are negative -> fatal.
 * Otherwise returns the clamped value.
 * Confidence: medium
 * Notes: FUN_001afa84 noreturn on the invalid path. */
long sk_r58_003f3cfc(long a, long b)
{
    if ((b < 1) && (b = a, a < 0)) {
        cL4_h_0040633c();             /* FUN_0040633c */
        cL4_h_001afa84();             /* FUN_001afa84 noreturn */
    }
    return b;
}

/* FUN_003f3d34 @ 0x003f3d34   (est. sk_r58_003f3d34 — small-memory "0x40" printer)
 * Ghidra: undefined1 [16] FUN_003f3d34(void)
 * Calls the memory printer (FUN_00027724 at 0x6720e0) with the fixed extent
 * (0x677880, 0x6720e0), flushes, and returns the "0x40" string pair.
 * Confidence: medium
 * Notes: string pair 0x40 / 0xe100000000000000. */
cL4_w16_t sk_r58_003f3d34(void)
{
    word_t fn;
    cL4_w16_t out;
    extern cL4_w16_t cL4_h_000e72d4(); /* FUN_000e72d4 */
    fn = cL4_h_00027724(0x6720e0).lo; /* FUN_00027724(0x6720e0) */
    ((void (*)(word_t, word_t))fn)(0x677880, 0x6720e0);
    cL4_h_000e72d4();                 /* FUN_000e72d4 */
    cL4_h_003a25d4(0x6720e0);         /* FUN_003a25d4(0x6720e0) */
    out.lo = 0x40;
    out.hi = 0xe100000000000000;
    return out;
}

/* FUN_003f3db8 @ 0x003f3db8   (est. sk_r58_003f3db8 — armed-state check 1)
 * Ghidra: uint FUN_003f3db8(void)
 * Returns the negated bit0 of thunk_FUN_002d49f4 (armed flag).
 * Confidence: medium */
unsigned int sk_r58_003f3db8(void)
{
    word_t u;
    cL4_h_00407d74();                 /* FUN_00407d74 */
    u = cL4_h_002d49f4().lo;          /* thunk_FUN_002d49f4 */
    return (unsigned int)((u ^ 0xffffffff) & 1);
}

/* FUN_003f3dbc @ 0x003f3dbc   (est. sk_r58_003f3dbc — armed-state check 2)
 * Ghidra: uint FUN_003f3dbc(void)
 * Identical to FUN_003f3db8.
 * Confidence: medium */
unsigned int sk_r58_003f3dbc(void)
{
    word_t u;
    cL4_h_00407d74();                 /* FUN_00407d74 */
    u = cL4_h_002d49f4().lo;          /* thunk_FUN_002d49f4 */
    return (unsigned int)((u ^ 0xffffffff) & 1);
}

/* FUN_003f3ddc @ 0x003f3ddc   (est. sk_r58_003f3ddc — armed-state check 3)
 * Ghidra: uint FUN_003f3ddc(void)
 * Returns negated bit0 of thunk_FUN_002d49f4 (no preamble).
 * Confidence: medium */
unsigned int sk_r58_003f3ddc(void)
{
    word_t u;
    u = cL4_h_002d49f4().lo;          /* thunk_FUN_002d49f4 */
    return (unsigned int)((u ^ 0xffffffff) & 1);
}

/* FUN_003f3de0 @ 0x003f3de0   (est. sk_r58_003f3de0 — armed-state check 4)
 * Ghidra: uint FUN_003f3de0(void)
 * Identical to FUN_003f3ddc.
 * Confidence: medium */
unsigned int sk_r58_003f3de0(void)
{
    word_t u;
    u = cL4_h_002d49f4().lo;          /* thunk_FUN_002d49f4 */
    return (unsigned int)((u ^ 0xffffffff) & 1);
}

/* FUN_003f3dfc @ 0x003f3dfc   (est. sk_r58_003f3dfc — armed-state probe)
 * Ghidra: void FUN_003f3dfc(void)
 * Runs FUN_00407d74 and thunk_FUN_002d49f4, discarding results.
 * Confidence: medium */
void sk_r58_003f3dfc(void)
{
    cL4_h_00407d74();                 /* FUN_00407d74 */
    cL4_h_002d49f4();                 /* thunk_FUN_002d49f4 */
}

/* FUN_003f3e34 @ 0x003f3e34   (est. sk_r58_003f3e34 — queue state trap)
 * Ghidra: void FUN_003f3e34(void)
 * Prints queue-state diagnostics (FUN_0040677c(0x1d), FUN_00406518,
 * FUN_004085a8) then traps @0x3f3e64.
 * Confidence: medium */
void sk_r58_003f3e34(void)
{
    cL4_h_004070cc();                 /* FUN_004070cc */
    cL4_h_0040677c(0x1d);             /* FUN_0040677c(0x1d) */
    cL4_h_00406518();                 /* FUN_00406518 */
    cL4_h_004085a8();                 /* FUN_004085a8 */
    CL4_SW_BP(0x3f3e64);              /* SoftwareBreakpoint(1,0x3f3e64) */
}

/* FUN_003f3e64 @ 0x003f3e64   (est. sk_r58_003f3e64 — queue record write)
 * Ghidra: void FUN_003f3e64(undefined8 *param_1,undefined8 param_2,long param_3,undefined8 param_4,long param_5,char param_6)
 * Writes a 5-field queue record into *param_1 (id, length, data, offset,
 * flag). If length<1 and the flag is not 1, it traps (queue-state error).
 * Confidence: medium
 * Notes: param_6 is a boolean ("\x01"==true). */
void sk_r58_003f3e64(word_t *rec, word_t id, long len, word_t data, long off, byte flag)
{
    char c;
    word_t d;
    if (len < 1 && flag != '\x01') {
        cL4_h_004070cc();             /* FUN_004070cc */
        cL4_h_0040677c(0x40);         /* FUN_0040677c(0x40) */
        cL4_h_00406518();             /* FUN_00406518 */
        cL4_h_004085a8();             /* FUN_004085a8 */
        CL4_SW_BP(0x3f3ecc);
    }
    d = 0;
    if (off != 0) {
        d = data;
    }
    c = flag;
    if (off == 0 || flag == '\x01') {
        c = '\x01';
    }
    rec[0] = id;
    rec[1] = (word_t)len;
    if (flag != '\x01') {
        data = d;
    }
    rec[2] = data;
    rec[3] = (word_t)off;
    *(char *)(rec + 4) = c;
}

/* FUN_003f3ecc @ 0x003f3ecc   (est. sk_r58_003f3ecc — record passthrough dispatcher)
 * Ghidra: void FUN_003f3ecc(void)
 * Relays an in-register 5-field record: resolves via FUN_00407484, runs the
 * registered handler (unaff_x20) and notify path (unaff_x19), then copies the
 * record words into the caller-provided buffer (extraout_x8[]).
 * Confidence: medium
 * Notes: in_x4/in_x5/unaff_x19/unaff_x20/unaff_x30 register args. */
void sk_r58_003f3ecc(void)
{
    word_t h1 = 0;           /* unaff_x19 */
    word_t h2 = 0;           /* unaff_x20 */
    word_t in4 = 0, in5 = 0, u30 = 0; /* in_x4/in_x5/unaff_x30 */
    word_t *out = 0;                  /* extraout_x8 */
    cL4_w16_t r;
    cL4_h_003565a8();                 /* FUN_003565a8 */
    r = cL4_h_00407484();             /* FUN_00407484 */
    ((void (*)(word_t, word_t, word_t))in5)(r.lo, r.hi, in4); /* (*in_x5)() */
    cL4_h_003504c4();                 /* FUN_003504c4 */
    ((void (*)(void))h2)();           /* (*unaff_x20)() */
    cL4_h_00351790();                 /* FUN_00351790 */
    cL4_h_00350738(0x8);              /* FUN_00350738(&stack+8) */
    ((void (*)(void))h1)();           /* (*unaff_x19)() */
    out[1] = 0x10;                    /* in_stack_00000010 */
    out[0] = 0x8;                     /* in_stack_00000008 */
    out[3] = 0x20;                    /* in_stack_00000020 */
    out[2] = 0x18;                    /* in_stack_00000018 */
    *(char *)(out + 4) = 0x28;        /* in_stack_00000028 */
    cL4_h_00356590(u30);              /* FUN_00356590 */
}

/* FUN_003f3f50 @ 0x003f3f50   (est. sk_r58_003f3f50 — collection print record build)
 * Ghidra: void FUN_003f3f50(void)
 * Builds a print record for a collection: resolves the count/type via
 * FUN_00351124, prints the header through FUN_001d88fc (with type ids 0x674330
 * and 0x66d208), then writes the 5-field record via FUN_003f3e64.
 * Confidence: medium
 * Notes: unaff_x19 out; unaff_x21 collection; string ids 0x674330/0x66d208. */
void sk_r58_003f3f50(void)
{
    word_t *out = 0;         /* unaff_x19 */
    long coll = 0;           /* unaff_x21 */
    word_t u1, u2;
    cL4_w16_t r;
    word_t hdr;
    cL4_h_0035098c();                 /* FUN_0035098c */
    u1 = cL4_h_00351124().lo;         /* FUN_00351124 */
    cL4_h_0001a1c8(u1, *(word_t *)(coll + 8)); /* thunk_FUN_0001a1c8 */
    r = cL4_h_004072c0();             /* FUN_004072c0 */
    cL4_h_0031b37c();                 /* FUN_0031b37c */
    cL4_h_00352efc();                 /* FUN_00352efc */
    u1 = cL4_h_00310d68().lo;         /* FUN_00310d68 */
    cL4_h_00350798();                 /* FUN_00350798 */
    u2 = cL4_h_0031de7c().lo;         /* FUN_0031de7c */
    r = cL4_h_001d88fc((word_t)&hdr, (word_t)&sk_r58_003f3f50_print, (word_t)&r,
                       u1, 0x674330, u2, 0x66d208); /* FUN_001d88fc */
    cL4_h_000e15d8((word_t)&hdr, r.lo, r.hi, 0, 0, 0); /* FUN_000e15d8 */
    ((void (*)(void))sk_r58_003f3e64)();                /* FUN_003f3e64 */
    out[1] = 0;                       /* uStack_68 */
    out[0] = 0;                       /* local_70 */
    out[3] = 0;                       /* uStack_58 */
    out[2] = 0;                       /* CONCAT71(uStack_5f,local_60) */
    *(char *)(out + 4) = 0;           /* local_50 */
}

/* internal print callback referenced by FUN_003f3f50 (FUN_00404f60, out-of-slice) */
void sk_r58_003f3f50_print(void) { }

/* FUN_003f4040 @ 0x003f4040   (est. sk_r58_003f4040 — extent end (base+len, overflow trap))
 * Ghidra: long FUN_003f4040(void)
 * Returns the end of an extent: if the flag byte at self+0x20 is 1 the length
 * is 0, else the length at self+0x18; base at self+8. Traps on overflow.
 * Confidence: medium
 * Notes: unaff_x20 self; SCARRY8 check @0x3f406c. */
long sk_r58_003f4040(void)
{
    word_t self = 0;         /* unaff_x20 */
    long len;
    if (*(char *)(self + 0x20) == '\x01') {
        len = 0;
    } else {
        len = *(long *)(self + 0x18);
    }
    if (!((*(long *)(self + 8) + len) < *(long *)(self + 8))) { /* !SCARRY8 */
        return *(long *)(self + 8) + len;
    }
    CL4_SW_BP(0x3f406c);
}

/* FUN_003f406c @ 0x003f406c   (est. sk_r58_003f406c — memory span describe)
 * Ghidra: void FUN_003f406c(void)
 * Describes a memory span: resolves the context via FUN_0034c2e8 /
 * FUN_0031de7c, builds a buffer through FUN_00376820 (DAT_004edcd0), advances
 * via FUN_0031b080 / thunk_FUN_0028c754 and FUN_0022b584, then finalizes the
 * span with FUN_001a26e0.
 * Confidence: medium
 * Notes: in_x4 register arg; DAT_004edcd0 global. */
void sk_r58_003f406c(void)
{
    extern char cL4_D_004edcd0;       /* DAT_004edcd0 */
    word_t in4 = 0;                   /* in_x4 */
    word_t u1, u2;
    word_t span[2];                   /* local_90 */
    word_t b8 = 0;                    /* local_b8 */
    cL4_w16_t r;
    u1 = cL4_h_0034c2e8().lo;         /* FUN_0034c2e8 */
    u2 = cL4_h_0031de7c(0xff, in4).lo;/* FUN_0031de7c(0xff,in_x4) */
    r = cL4_h_00376820((word_t)&cL4_D_004edcd0, u2); /* FUN_00376820 */
    cL4_h_00350798(r.lo, r.hi, r.lo); /* FUN_00350798 */
    u2 = cL4_h_0031b080().lo;         /* FUN_0031b080 */
    cL4_h_0028c754((word_t)span);     /* thunk_FUN_0028c754(local_90) */
    if (span[0] != 0) {
        cL4_h_00408148();             /* FUN_00408148 */
        cL4_h_003522b8(b8);           /* FUN_003522b8(local_b8) */
        span[0] = span[0] + 0;        /* lVar3 + extraout_x16[0x48]*extraout_x8 */
    }
    cL4_h_0022b584((word_t)span, u2); /* thunk_FUN_0022b584 */
    cL4_h_00408148();                 /* FUN_00408148 */
    cL4_h_001a26e0(span[0], span[0] - b8, in4); /* FUN_001a26e0 */
}

/* FUN_003f4164 @ 0x003f4164   (est. sk_r58_003f4164 — record field dispatch)
 * Ghidra: void FUN_003f4164(long param_1)
 * Dispatches on the record's flag: publishes the primary (unaff_x20[0]/[1])
 * then, unless the flag at unaff_x20[4] is set, the secondary pair ([2]/[3]).
 * Confidence: medium
 * Notes: unaff_x20 record; FUN_003f41b8 out-of-slice. */
void sk_r58_003f4164(long src)
{
    word_t *rec = 0;         /* unaff_x20 */
    extern cL4_w16_t cL4_h_003f41b8(); /* FUN_003f41b8 */
    word_t u;
    u = *(word_t *)(src + 0x10);
    cL4_h_003f41b8(*rec, rec[1], u);  /* FUN_003f41b8(rec[0],rec[1],uVar1) */
    if (*(char *)(rec + 4) == '\x01') {
        return;
    }
    cL4_h_003f41b8(rec[2], rec[3], u);/* FUN_003f41b8(rec[2],rec[3],uVar1) */
}
