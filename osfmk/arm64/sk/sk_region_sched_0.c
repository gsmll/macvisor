/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel, GL1, arm64e, image
 * base 0) — the cL4 microkernel (cL4 (679.100.61)), seL4-derived. Ground truth: Ghidra FUN_ names
 * + addresses. All names are estimates unless string-matched.
 * Region 0: 0x180000-0x190000 — XNU upcall / syscall dispatch layer (Swift upcall handlers,
 * message-register marshalling, per-CPU upcall state, XnuUpcalls / XnuUpcallsV2 classes). */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "sk_internal.h"

/* Per-CPU context base (unaff_x20) and per-CPU error flag (unaff_x21) threaded
 * through the upcall/syscall layer; owned by the per-CPU region. */
extern uint8_t *per_cpu;
extern uint64_t per_cpu_err;

/* In-stack argument frame (Ghidra stack0x... tokens). */
extern uint64_t stack_arg;
extern uint64_t dat_004e6548;
extern uint64_t dat_004e64c8;
extern uint64_t dat_004e6468;
extern uint64_t dat_004e65c8;

/* Method-table function pointer (Ghidra "code_fn_t"). */
typedef uint64_t (*code_fn_t)();  /* unspecified params: any arity */

/* 16-uint8_t aggregate returned by message writers (Ghidra "undefined1 [16]").
 * lo = bytes 0..7 (Ghidra _0_8_), hi = bytes 8..15 (_8_8_). */
typedef struct cl4_16 { uint64_t lo; uint64_t hi; } cl4_16_t;
#define _0_8_ lo
#define _8_8_ hi
#define _0_4_ lo
#define _4_4_ lo
#define _8_4_ hi
#define _12_4_ hi
#define CONCAT44(hi4, lo4)  (((uint64_t)(hi4) << 32) | (uint64_t)(lo4))
#define CONCAT31(hi3, lo1)  (((uint64_t)(hi3) << 8)  | (uint64_t)(lo1))
#define CONCAT71(hi7, lo1)  (((uint64_t)(hi7) << 8)  | (uint64_t)(lo1) & 0xffull)
#define EXTRACT17(x)  (((uint64_t)(x) >> 8) & 0x00ffffffffffffffull)
#define EXTRACT13(x)  (((uint32_t)(x) >> 8) & 0x00ffffffu)
#define SCARRY8(v, bits)    ((int64_t)(v) < 0)

/* Wrap a void-returning call so its (undefined) result can be assigned to a
 * typed local; the transcription's leftover-register value is modeled as 0. */
#define CL4_VOID_U64(fn_call)  ((fn_call), 0ull)
#define CL4_VOID_16(fn_call)   ((cl4_16_t)((fn_call), 0ull))

/* Hand-written simple helper externs (bodies in-file under cl4_* names). */

/* Breakpoint: SoftwareBreakpoint(1, addr). */
#define cl4_break(addr) __asm__ volatile("brk #1" : : : "memory")

/* ------------------------------------------------------------------ *
 * Out-of-range cL4 helper declarations (extern; bodies reconstructed by the
 * sibling range workers that own them). FUN_ addresses are ground truth.
 * Declared with unspecified parameter lists so any call arity is legal.
 * ------------------------------------------------------------------ */
extern uint64_t FUN_00002534();  /* 0x00002534 */
extern uint64_t FUN_00019aac();  /* 0x00019aac */
extern uint64_t FUN_0002142c();  /* 0x0002142c */
extern uint64_t FUN_000214b0();  /* 0x000214b0 */
extern uint64_t FUN_00021738();  /* 0x00021738 */
extern uint64_t FUN_000217e4();  /* 0x000217e4 */
extern uint64_t FUN_000218a4();  /* 0x000218a4 */
extern uint64_t FUN_00021904();  /* 0x00021904 */
extern uint64_t FUN_00022028();  /* 0x00022028 */
extern uint64_t FUN_00022c48();  /* 0x00022c48 */
extern uint64_t FUN_000230f8();  /* 0x000230f8 */
extern uint64_t FUN_000231f0();  /* 0x000231f0 */
extern uint64_t FUN_00023208();  /* 0x00023208 */
extern uint64_t FUN_00023318();  /* 0x00023318 */
extern uint64_t FUN_00023c78();  /* 0x00023c78 */
extern uint64_t FUN_00023d00();  /* 0x00023d00 */
extern uint64_t FUN_00023f74();  /* 0x00023f74 */
extern uint64_t FUN_00025704();  /* 0x00025704 */
extern uint64_t FUN_00025ebc();  /* 0x00025ebc */
extern uint64_t FUN_00025f44();  /* 0x00025f44 */
extern uint64_t FUN_000260e0();  /* 0x000260e0 */
extern uint64_t FUN_000262ec();  /* 0x000262ec */
extern uint64_t FUN_00026754();  /* 0x00026754 */
extern uint64_t FUN_000267d4();  /* 0x000267d4 */
extern uint64_t FUN_000268d0();  /* 0x000268d0 */
extern uint64_t FUN_00027724();  /* 0x00027724 */
extern uint64_t FUN_00072c98();  /* 0x00072c98 */
extern uint64_t FUN_00082484();  /* 0x00082484 */
extern uint64_t FUN_000bd0e4();  /* 0x000bd0e4 */
extern uint64_t FUN_001477c4();  /* 0x001477c4 */
extern uint64_t FUN_0017770c();  /* 0x0017770c */
extern uint64_t FUN_0017d710();  /* 0x0017d710 */
extern uint64_t FUN_0017d734();  /* 0x0017d734 */
extern uint64_t FUN_0017d74c();  /* 0x0017d74c */
extern uint64_t FUN_0017d768();  /* 0x0017d768 */
extern uint64_t FUN_0017db0c();  /* 0x0017db0c */
extern uint64_t FUN_0017db28();  /* 0x0017db28 */
extern uint64_t FUN_0017db54();  /* 0x0017db54 */
extern uint64_t FUN_0017db70();  /* 0x0017db70 */
extern uint64_t FUN_0017db8c();  /* 0x0017db8c */
extern uint64_t FUN_0017dbac();  /* 0x0017dbac */
extern uint64_t FUN_0017dbc8();  /* 0x0017dbc8 */
extern uint64_t FUN_0017dbe4();  /* 0x0017dbe4 */
extern uint64_t FUN_0017dc10();  /* 0x0017dc10 */
extern uint64_t FUN_0017e5dc();  /* 0x0017e5dc */
extern uint64_t FUN_0017f188();  /* 0x0017f188 */
extern uint64_t FUN_0017f408();  /* 0x0017f408 */
extern uint64_t FUN_0017f98c();  /* 0x0017f98c */
extern uint64_t FUN_0017fcc4();  /* 0x0017fcc4 */
extern uint64_t FUN_0017fcf4();  /* 0x0017fcf4 */
extern uint64_t FUN_001900d4();  /* 0x001900d4 */
extern uint64_t FUN_001904d8();  /* 0x001904d8 */
extern uint64_t FUN_001908f0();  /* 0x001908f0 */
extern uint64_t FUN_00190bbc();  /* 0x00190bbc */
extern uint64_t FUN_0019179c();  /* 0x0019179c */
extern uint64_t FUN_00191ba8();  /* 0x00191ba8 */
extern uint64_t FUN_00191f84();  /* 0x00191f84 */
extern uint64_t FUN_0019225c();  /* 0x0019225c */
extern uint64_t FUN_00192528();  /* 0x00192528 */
extern uint64_t FUN_00192920();  /* 0x00192920 */
extern uint64_t FUN_00192bec();  /* 0x00192bec */
extern uint64_t FUN_00192eb8();  /* 0x00192eb8 */
extern uint64_t FUN_00193184();  /* 0x00193184 */
extern uint64_t FUN_00193450();  /* 0x00193450 */
extern uint64_t FUN_00193718();  /* 0x00193718 */
extern uint64_t FUN_001939e4();  /* 0x001939e4 */
extern uint64_t FUN_00193cb0();  /* 0x00193cb0 */
extern uint64_t FUN_00193f7c();  /* 0x00193f7c */
extern uint64_t FUN_00194370();  /* 0x00194370 */
extern uint64_t FUN_0019463c();  /* 0x0019463c */
extern uint64_t FUN_001948f8();  /* 0x001948f8 */
extern uint64_t FUN_00194bb4();  /* 0x00194bb4 */
extern uint64_t FUN_00194e80();  /* 0x00194e80 */
extern uint64_t FUN_0019514c();  /* 0x0019514c */
extern uint64_t FUN_00195418();  /* 0x00195418 */
extern uint64_t FUN_001956f4();  /* 0x001956f4 */
extern uint64_t FUN_001959e8();  /* 0x001959e8 */
extern uint64_t FUN_00195cc4();  /* 0x00195cc4 */
extern uint64_t FUN_00195f6c();  /* 0x00195f6c */
extern uint64_t FUN_00196204();  /* 0x00196204 */
extern uint64_t FUN_001964f4();  /* 0x001964f4 */
extern uint64_t FUN_0019661c();  /* 0x0019661c */
extern uint64_t FUN_00196644();  /* 0x00196644 */
extern uint64_t FUN_00196964();  /* 0x00196964 */
extern uint64_t FUN_00196c20();  /* 0x00196c20 */
extern uint64_t FUN_00196fec();  /* 0x00196fec */
extern uint64_t FUN_001972a4();  /* 0x001972a4 */
extern uint64_t FUN_00197594();  /* 0x00197594 */
extern uint64_t FUN_00197850();  /* 0x00197850 */
extern uint64_t FUN_00197be4();  /* 0x00197be4 */
extern uint64_t FUN_001a84f4();  /* 0x001a84f4 */
extern uint64_t FUN_001a8564();  /* 0x001a8564 */
extern uint64_t FUN_001afa84();  /* 0x001afa84 */
extern uint64_t FUN_00205844();  /* 0x00205844 */
extern uint64_t FUN_00208478();  /* 0x00208478 */
extern uint64_t FUN_0022995c();  /* 0x0022995c */
extern uint64_t FUN_002a4ab4();  /* 0x002a4ab4 */
extern uint64_t FUN_00365b6c();  /* 0x00365b6c */
extern uint64_t FUN_0036986c();  /* 0x0036986c */
extern uint64_t FUN_003698b0();  /* 0x003698b0 */
extern cl4_16_t FUN_0036993c();  /* 0x0036993c */
extern uint64_t FUN_0036a940();  /* 0x0036a940 */
extern uint64_t FUN_0036b118();  /* 0x0036b118 */
extern uint64_t FUN_0036b270();  /* 0x0036b270 */
extern uint64_t FUN_003a25d4();  /* 0x003a25d4 */
extern uint64_t FUN_0065a550();  /* 0x0065a550 */
extern uint64_t FUN_00669298();  /* 0x00669298 */
extern uint64_t FUN_0066a720();  /* 0x0066a720 */
extern uint64_t thunk_FUN_00024068();  /* 0x00024068 */
extern uint64_t thunk_FUN_002298d4();  /* 0x002298d4 */
extern uint64_t thunk_FUN_002acbb8();  /* 0x002acbb8 */


/* String/data references. */
extern char s_Fatal_error_005accd0[];
extern char s_StackshotConclaveSupport_Stacksh_005cbc40[];
extern char s_XnuProxyStackshotSupport_Stacksh_005cbf60[];
extern char s_XnuUpcallsV2_XnuUpcallsV2_Swift__005ccbc0[];
extern char s_XnuUpcalls_XnuUpcalls_Swift_swif_005cbff0[];
extern char s_XnuUpcalls_XnuUpcalls_swift_005cbfa0[];



void FUN_001807a4(uint64_t p1, uint64_t p2);
void FUN_001807a8(uint64_t p1, uint64_t p2);
void FUN_001807c0(uint64_t p1, uint64_t p2);
void FUN_001807c4(uint64_t p1, uint64_t p2);
void FUN_001807dc(uint64_t *p1, uint64_t *p2, uint64_t *p3, uint64_t p4);
void FUN_00180ef8(void);
void FUN_00180efc(void);
void FUN_00180f10(void);
void FUN_00180f14(void);
void FUN_00180f28(void);
void FUN_00180f2c(void);
void FUN_00180f44(void);
void FUN_00180f48(void);
void FUN_00180f5c(void);
void FUN_00180f60(void);
void FUN_00180f74(void);
void FUN_00180f78(void);
void FUN_00180f8c(void);
void FUN_00180f90(void);
void FUN_00180fa4(void);
void FUN_00180fa8(void);
void FUN_00180fbc(void);
void FUN_00180fc0(void);
void FUN_00180fd4(void);
void FUN_00180fd8(void);
void FUN_00180ff8(void);
void FUN_00180ffc(void);
void FUN_00181010(void);
void FUN_00181014(void);
void FUN_00181028(void);
void FUN_0018102c(void);
void FUN_00181040(void);
void FUN_00181044(void);
void FUN_00181058(void);
void FUN_0018105c(void);
void FUN_00181070(void);
void FUN_00181074(void);
void FUN_00181088(void);
void FUN_0018108c(void);
long FUN_001810a4(uint64_t p1, uint64_t p2);
void FUN_00181118(void);
long FUN_00181154(uint64_t p1, uint64_t p2, code_fn_t p3);
void FUN_00181204(uint64_t p1, uint64_t p2, code_fn_t p3);
void FUN_00181284(uint64_t p1);
void FUN_00181288(uint64_t p1);
void FUN_001812b0(uint64_t p1);
void FUN_001812b4(uint64_t p1);
cl4_16_t FUN_001812dc(uint64_t p1, code_fn_t p2);
void FUN_00181310(void);
cl4_16_t FUN_00181374(void);
void FUN_00181554(uint64_t p1);
void FUN_00181558(uint64_t p1);
void FUN_0018157c(uint64_t p1);
void FUN_00181580(uint64_t p1);
cl4_16_t FUN_001815a4(uint64_t p1, uint64_t p2);
uint32_t FUN_001817bc(void);
void FUN_001819a0(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4, uint64_t p5);
cl4_16_t FUN_00181a2c(uint64_t p1, uint64_t p2, uint64_t p3);
void FUN_00181ab4(uint64_t *p1);
uint32_t FUN_00181af0(uint64_t p1, uint64_t p2, uint64_t p3);
uint32_t FUN_00181af4(uint64_t p1, uint64_t p2, uint64_t p3);
void FUN_00181b3c(uint64_t p1, uint64_t p2, char p3, uint64_t p4, uint64_t p5);
cl4_16_t FUN_00181bf0(uint64_t p1, uint64_t p2, uint64_t p3);
cl4_16_t FUN_00181c44(uint64_t p1, uint64_t p2);
void FUN_00181db8(uint64_t *p1);
uint32_t FUN_00181e10(uint64_t p1, uint64_t p2, uint64_t p3);
uint32_t FUN_00181e14(uint64_t p1, uint64_t p2, uint64_t p3);
void FUN_00181eb8(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4);
uint64_t FUN_00181f20(uint64_t p1, uint64_t p2);
void FUN_00181fd0(uint64_t a, uint64_t b);
void FUN_00181fd4(uint64_t a, uint64_t b);
uint8_t FUN_0018200c(void);
void FUN_00182018(uint64_t v);
void FUN_00182080(uint64_t *p1, uint32_t p2);
void FUN_001823e0(void);
void FUN_00182430(uint64_t v);
void FUN_00182468(void);
void FUN_001824d4(uint64_t a, uint64_t b);
void FUN_00182528(uint64_t a, uint64_t b);
void FUN_0018257c(void);
void FUN_001825c4(void);
void FUN_00182630(void);
void FUN_00182674(void);
void FUN_0018269c(void);
void FUN_001826f0(uint64_t a, uint64_t b);
void FUN_0018276c(uint64_t a, uint64_t b);
long FUN_001827d0(uint64_t p1, uint64_t p2);
void FUN_00182860(uint64_t p1, uint64_t p2);
void FUN_001828dc(void);
void FUN_00182900(void);
void FUN_00182aac(char *p1);
void FUN_00182c64(char *p1);
void FUN_00182e1c(char *p1);
void FUN_00182fd4(char *p1, uint64_t p2);
void FUN_001831a0(char *p1, uint64_t p2);
void FUN_0018336c(char *p1);
void FUN_00183524(char *p1, char *p2);
uint64_t FUN_001836e8(char *p1, uint64_t p2, uint64_t p3, uint64_t p4);
void FUN_00183b2c(char *p1);
uint32_t FUN_00183ce4(char *p1);
void FUN_00183ea0(uint64_t p1, uint64_t p2);
void FUN_00183ea4(uint64_t p1, uint64_t p2);
void FUN_00183ecc(uint64_t p1, uint64_t p2);
void FUN_00183ed0(uint64_t p1, uint64_t p2);
void FUN_00183ef8(uint64_t p1, uint64_t p2);
void FUN_00183efc(uint64_t p1, uint64_t p2);
void FUN_00183f24(uint64_t p1, uint64_t p2);
void FUN_00183f28(uint64_t p1, uint64_t p2);
void FUN_00183f50(void);
void FUN_001840e0(uint64_t p1, uint64_t p2);
void FUN_001840e4(uint64_t p1, uint64_t p2);
void FUN_0018410c(uint64_t p1, uint64_t p2);
void FUN_00184110(uint64_t p1, uint64_t p2);
void FUN_00184138(uint64_t p1, uint64_t p2);
void FUN_0018413c(uint64_t p1, uint64_t p2);
uint32_t FUN_00184164(uint64_t p1, uint64_t p2, uint64_t *p3);
void FUN_0018430c(uint64_t p1, uint64_t p2);
void FUN_00184310(uint64_t p1, uint64_t p2);
void FUN_00184338(uint64_t p1);
void FUN_0018433c(uint64_t p1);
void FUN_00184364(uint64_t p1);
void FUN_00184368(uint64_t p1);
void FUN_00184390(uint64_t p1, code_fn_t p2);
void FUN_00184524(uint64_t p1, uint64_t p2);
void FUN_00184528(uint64_t p1, uint64_t p2);
void FUN_00184550(uint64_t p1, uint64_t p2);
void FUN_00184554(uint64_t p1, uint64_t p2);
void FUN_0018457c(uint64_t p1, uint64_t p2);
void FUN_00184580(uint64_t p1, uint64_t p2);
void FUN_001845a8(uint64_t p1, uint64_t p2, code_fn_t p3);
uint32_t FUN_0018473c(void);
uint32_t FUN_001848d0(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4);
uint32_t FUN_00184cd4(void);
uint32_t FUN_00184e68(void);
void FUN_00184ffc(void);
void FUN_00185174(void);
void FUN_00185198(void);
void FUN_001851bc(void);
void FUN_001851e0(void);
void FUN_00185370(void);
void FUN_00185500(void);
void FUN_0018569c(void);
void FUN_001857a8(void);
uint64_t * FUN_00185b58(uint64_t *p1, uint64_t *p2);
uint64_t * FUN_00185b94(uint64_t *p1, uint64_t *p2);
cl4_16_t FUN_00185c60(void);
void FUN_00185cbc(uint64_t p1);
uint64_t FUN_00185ce4(long p1);
uint64_t FUN_00186094(uint8_t p1, uint64_t p2, long p3);
void FUN_00186460(uint8_t p1, uint64_t p2);
uint64_t FUN_001866dc(uint8_t p1, uint64_t p2, long p3);
void FUN_00186aa8(uint8_t p1, uint64_t p2, uint64_t *p3);
void FUN_00186e3c(uint8_t p1, uint64_t p2, uint64_t *p3);
void FUN_001871d0(uint8_t p1, uint64_t p2, long p3);
void FUN_0018758c(uint8_t p1, uint8_t p2, uint64_t p3);
uint64_t FUN_00187820(uint8_t p1, uint64_t p2);
uint8_t FUN_00187aac(uint8_t p1);
void FUN_00187d28(uint64_t p1, uint64_t p2);
void FUN_00187fa4(uint64_t p1, uint64_t p2);
void FUN_00188220(uint64_t p1, uint64_t p2);
void FUN_0018849c(uint64_t p1, uint64_t p2);
uint64_t FUN_00188718(uint64_t p1);
void FUN_00188994(uint64_t p1, uint64_t p2);
void FUN_00188c10(uint64_t p1, uint64_t p2);
void FUN_00188e8c(uint64_t p1, uint64_t p2);
uint32_t FUN_00189108(uint64_t p1, uint64_t p2, uint64_t *p3);
void FUN_001894b4(uint64_t p1, uint64_t p2);
void FUN_00189730(uint64_t p1);
void FUN_0018999c(uint64_t p1);
void FUN_00189c08(uint64_t p1, uint64_t p2);
void FUN_00189e84(uint64_t p1, uint64_t p2);
void FUN_0018a100(uint64_t p1, uint64_t p2);
uint32_t FUN_0018a37c(uint64_t p1, uint64_t p2);
uint32_t FUN_0018a608(uint64_t p1, uint64_t p2, uint64_t p3);
uint32_t FUN_0018a8ac(uint64_t p1, uint64_t p2);
void FUN_0018ab38(uint64_t p1, uint64_t p2);
uint64_t FUN_0018ada8(long p1);
uint64_t FUN_0018b094(uint64_t p1, uint64_t p2);
void FUN_0018b1bc(uint64_t p1);
uint64_t FUN_0018b1e4(uint64_t p1, uint64_t p2);
void FUN_0018b2f4(uint64_t *p1, uint64_t p2);
void FUN_0018b5c4(uint64_t p1);
void FUN_0018b830(uint64_t *p1, uint64_t p2);
void FUN_0018bbac(uint64_t p1, uint64_t p2, uint64_t p3);
void FUN_0018bc58(uint64_t *p1, uint64_t p2, uint64_t p3, uint64_t p4, uint64_t *p5);
void FUN_0018bd0c(void);
uint32_t FUN_0018bd44(void);
uint32_t FUN_0018bd48(void);
void FUN_0018bd6c(void);
void FUN_0018bdbc(uint64_t v);
void FUN_0018bdf4(void);
void FUN_0018be40(uint8_t *out, uint32_t *arg);
void FUN_0018be84(uint64_t a, uint64_t b);
void FUN_0018bed8(uint64_t a, uint64_t b);
uint32_t FUN_0018bf2c(uint64_t p1, uint64_t p2, uint64_t p3);
void FUN_0018bf78(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4);
void FUN_0018c020(uint64_t *p1, uint64_t p2, uint64_t p3, uint64_t p4, uint64_t *p5);
uint64_t FUN_0018c078(uint64_t p1, uint64_t p2);
void FUN_0018c108(void);
uint32_t FUN_0018c140(void);
uint32_t FUN_0018c144(void);
void FUN_0018c168(uint64_t a, uint64_t b);
void FUN_0018c1bc(uint64_t a, uint64_t b);
uint32_t FUN_0018c214(uint64_t p1, uint64_t p2, uint64_t p3);
void FUN_0018c288(long p1);
void FUN_0018c3cc(long p1, uint64_t p2, uint64_t p3);
void FUN_0018c540(uint64_t *p1, uint64_t p2, uint64_t p3, uint64_t p4, uint64_t *p5);
void FUN_0018c754(void);
uint32_t FUN_0018c78c(void);
uint32_t FUN_0018c790(void);
uint32_t FUN_0018c7b8(uint64_t p1, uint64_t p2, uint64_t p3);
void FUN_0018c82c(long p1);
void FUN_0018c968(long p1, uint64_t p2, uint64_t p3);
void FUN_0018cad4(uint64_t *p1, uint64_t p2, uint64_t p3, uint64_t p4, uint64_t *p5);
void FUN_0018cd78(void);
uint32_t FUN_0018cdb0(void);
uint32_t FUN_0018cdb4(void);
void FUN_0018cea4(long p1);
void FUN_0018cfe8(void);
void FUN_0018d0e4(uint64_t p1, uint64_t p2);
void FUN_0018d208(void);
uint64_t FUN_0018d304(void);
void FUN_0018d414(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4);
void FUN_0018d494(uint64_t *p1);
uint64_t FUN_0018d50c(uint64_t p1, uint64_t p2);
void FUN_0018d5c4(uint64_t *p1, uint64_t p2, uint64_t p3, uint64_t *p4, uint64_t p5);
void FUN_0018d690(uint64_t p1, uint64_t p2, uint64_t p3);
void FUN_0018d710(uint64_t *p1, uint64_t p2, uint64_t *p3);
uint64_t FUN_0018d7e8(uint64_t p1, uint64_t p2);
void FUN_0018d8a0(uint64_t *p1, uint64_t p2, uint64_t p3, uint64_t *p4, uint64_t p5);
void FUN_0018d96c(uint64_t p1, uint64_t p2);
void FUN_0018d970(uint64_t p1, uint64_t p2);
void FUN_0018d9d8(void);
void FUN_0018d9dc(void);
void FUN_0018da04(void);
void FUN_0018da08(void);
void FUN_0018da30(uint64_t p1, uint64_t p2);
void FUN_0018da34(uint64_t p1, uint64_t p2);
void FUN_0018da9c(void);
void FUN_0018daa0(void);
void FUN_0018dac8(void);
void FUN_0018dacc(void);
void FUN_0018daf4(uint64_t p1, uint64_t p2, uint64_t *p3, code_fn_t p4);
void FUN_0018dbc0(uint64_t p1, uint64_t p2);
void FUN_0018dbc4(uint64_t p1, uint64_t p2);
void FUN_0018dbec(uint64_t *p1, uint64_t p2, uint64_t *p3, code_fn_t p4);
void FUN_0018dcd8(void);
void FUN_0018dcdc(void);
uint64_t FUN_0018dd04(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4, uint64_t p5);
void FUN_0018ddac(void);
void FUN_0018ddb0(void);
void FUN_0018ddd8(uint64_t *p1, uint64_t p2, uint64_t p3, uint64_t *p4, uint64_t p5, uint64_t p6, uint64_t p7);
void FUN_0018de98(void);
uint64_t FUN_0018deb8(uint32_t p1);
void * FUN_0018c660(uint64_t p1, uint64_t p2);
void * FUN_0018cc2c(uint64_t p1, uint64_t p2);
cl4_16_t FUN_0018e1c0(void);
void FUN_0018e290(uint64_t a, uint64_t b);
void FUN_0018e294(uint64_t a, uint64_t b);
void FUN_0018e2b4(uint64_t p1, uint64_t p2);
void FUN_0018e2b8(uint64_t p1, uint64_t p2);
void FUN_0018e2dc(void);
void FUN_0018e2e0(void);
void FUN_0018e310(void);
void FUN_0018e314(void);
void FUN_0018e344(void);
void FUN_0018e348(void);
void FUN_0018e38c(uint8_t *out, uint8_t v);
void FUN_0018e6f4(void);
void FUN_0018e744(uint64_t v);
void FUN_0018e77c(void);
void FUN_0018e7e8(uint64_t a, uint64_t b);
void FUN_0018e84c(uint64_t a, uint64_t b);
void FUN_0018e8a0(uint64_t a, uint64_t b);
void FUN_0018e90c(void);
void FUN_0018e950(void);
void FUN_0018e978(void);
void FUN_0018ea08(void);
void FUN_0018ea5c(void);
void FUN_0018ea80(void);
void FUN_0018eaa4(void);
void FUN_0018eac8(void);
void FUN_0018eaec(void);
void FUN_0018eb10(void);
void FUN_0018eb14(void);
void FUN_0018eb3c(void);
void FUN_0018eb40(void);
void FUN_0018eb68(uint64_t p1, uint64_t p2, uint64_t *p3, code_fn_t p4);
void FUN_0018ebac(void);
void FUN_0018ebd0(uint64_t a, uint8_t *b);
uint64_t FUN_0018ec00(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4);
void FUN_0018ef04(void);
uint32_t FUN_0018ef28(void);
uint32_t FUN_0018ef50(void);
void FUN_0018efa8(void);
void FUN_0018efcc(void);
void FUN_0018eff0(void);
void FUN_0018f014(void);
void FUN_0018f038(void);
void FUN_0018f05c(void);
void FUN_0018f080(void);
void FUN_0018f0a4(void);
uint32_t FUN_0018f0c8(uint64_t p1, uint64_t p2, uint64_t *p3);
void FUN_0018f10c(void);
void FUN_0018f130(void);
void FUN_0018f154(void);
void FUN_0018f178(void);
void FUN_0018f19c(void);
void FUN_0018f1c0(void);
uint32_t FUN_0018f214(void);
uint32_t FUN_0018f23c(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4);
uint32_t FUN_0018f544(void);
uint32_t FUN_0018f56c(void);
void FUN_0018f5c4(void);
void FUN_0018f5e8(void);
void FUN_0018f63c(void);
void FUN_0018f660(void);
void FUN_0018f684(void);
void FUN_0018f6d8(void);
void FUN_0018f6fc(void);
void FUN_0018f720(uint64_t *p);
void FUN_0018f780(void);
void FUN_0018f7a4(void);
void FUN_0018f7c8(void);
void FUN_0018f7ec(void);
long FUN_0018f828(uint64_t p1, uint64_t p2, code_fn_t p3);
void FUN_0018f8d8(uint64_t p1, uint64_t p2, code_fn_t p3);
void FUN_0018f958(uint64_t *p);
cl4_16_t FUN_0018fbe8(void);
void FUN_0018fcb0(uint64_t p1);
uint64_t FUN_0018fcd8(long p1);

/* per-CPU accessors used by the upcall layer (unaff_x20/x21). */
#define cpu per_cpu
#define err per_cpu_err

/* DAT_ globals referenced (owned elsewhere). */
extern uint64_t dat_004bbc30;
extern uint64_t dat_004e6154;
extern uint64_t dat_004e6528;
extern uint64_t dat_004e65a8;
extern uint64_t dat_004e6878;
extern uint64_t dat_004e6898;
extern uint64_t dat_004e68c4;
extern uint64_t dat_004e7004;
extern uint64_t dat_0064c260;
extern uint64_t dat_00657778;
extern uint64_t dat_00657788;
extern uint64_t dat_00657790;
extern uint64_t dat_00657798;
extern uint64_t dat_006695c0;
extern uint64_t dat_006695e0;
extern uint64_t dat_006695f8;


/* ================================================================== *
 * Functions in ADDRESS ORDER (0x180000-0x190000)
 * ================================================================== */

/* FUN_001807a4 @ 0x001807a4   (est. thunk -> ?)
 * Ghidra: void FUN_001807a4(undefined8 p1,undefined8 p2)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_001807a4(uint64_t p1, uint64_t p2)
{
    ;
}



/* FUN_001807a8 @ 0x001807a8   (est. thunk -> ?)
 * Ghidra: void FUN_001807a8(undefined8 p1,undefined8 p2)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_001807a8(uint64_t p1, uint64_t p2)
{
    ;
}



/* FUN_001807c0 @ 0x001807c0   (est. thunk -> ?)
 * Ghidra: void FUN_001807c0(undefined8 p1,undefined8 p2)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_001807c0(uint64_t p1, uint64_t p2)
{
    ;
}



/* FUN_001807c4 @ 0x001807c4   (est. thunk -> ?)
 * Ghidra: void FUN_001807c4(undefined8 p1,undefined8 p2)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_001807c4(uint64_t p1, uint64_t p2)
{
    ;
}



/* FUN_001807dc @ 0x001807dc   (est. FUN_001807dc)
 * Ghidra: void FUN_001807dc(ulong *p1,undefined8 *p2,undefined4 *p3,undefined8 p4)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class X/None */
void FUN_001807dc(uint64_t *p1, uint64_t *p2, uint64_t *p3, uint64_t p4)
{
  uint64_t o;
  uint64_t p;
  uint32_t q;
  uint64_t s;
  uint64_t t;
  code_fn_t m;
  uint64_t u;
  long cpu;
  void *err;
  uint8_t *l;
  uint64_t v;
  void *k;
  uint8_t st2;
  void *st;
  uint64_t fn3;
  uint64_t fn2;
  uint64_t w1;
  uint64_t w0;
  uint64_t val4;
  uint64_t fn;
  uint8_t slot3;
  uint64_t slot2;
  uint64_t val3;
  uint64_t val2;
  uint64_t val;
  uint64_t slot;
  uint64_t idx2;
  uint8_t key2;
  uint8_t key [8];
  uint64_t h4;
  uint64_t idx;
  uint64_t h3;
  uint64_t cnt2;
  uint64_t h2;
  uint8_t h;
  uint8_t msgbuf [64];
  uint64_t ptr4;
  uint64_t cnt;
  uint64_t ptr3;
  uint64_t len2;
  uint64_t ptr2;
  uint8_t ptr;
  uint8_t tmp4 [56];
  uint8_t tmp3;
  uint64_t tmp2;
  uint64_t len;
  uint64_t tmp;
  uint64_t kind2;
  uint64_t tag2;
  uint8_t tag;
  uint64_t w7;
  uint64_t kind;
  uint64_t errword2;
  uint64_t errword;
  uint64_t w6;
  uint64_t msgbuf6;
  uint8_t w5;
  uint64_t w4;
  uint64_t msgbuf5;
  uint64_t msgbuf4;
  uint64_t msgbuf3;
  uint64_t w3;
  uint64_t msgbuf2;
  uint8_t w2;
  uint64_t j;
  uint64_t b;
  uint64_t c3;
  uint64_t c2;
  uint64_t i;
  uint64_t c;
  uint8_t n2;
  uint64_t n;
  uint64_t r4;
  uint64_t r3;
  uint64_t r2;
  uint64_t b3;
  uint64_t r;
  uint8_t b2;
  
  u = *(uint64_t *)(cpu + 0x10);
  p = *(uint64_t *)(cpu + 0x18);
  val3 = p2[1];
  slot2 = *p2;
  val = p2[3];
  val2 = p2[2];
  idx2 = p2[5];
  slot = p2[4];
  key2 = *(uint8_t *)(p2 + 6);
  s = FUN_0017770c();
  if ((s & 1) == 0) {
    m = (code_fn_t)FUN_0017fcf4(p);
    q = (*m)(u,p);
    kind = val3;
    w7 = slot2;
    errword = val;
    errword2 = val2;
    msgbuf6 = idx2;
    w6 = slot;
    w5 = key2;
    FUN_00022028(key,4,0,&st);
    if (err != (void *)0x0) {
      *p3 = *(uint32_t *)(uintptr_t)st;
      return;
    }
    fn3 = (uint64_t)key[0];
    w1 = idx;
    fn2 = h4;
    val4 = cnt2;
    w0 = h3;
    fn = h2;
    slot3 = h;
  }
  else {
    s = FUN_00021904();
    if ((long)s < 0) {
                    /* WARNING: Does not return */
      cl4_break(0x180c00);
    }
    k = &dat_00657778;
    if (s != 0) {
      st = &dat_00657778;
      FUN_00082484(0,s,0);
      v = s;
      do {
        k = st;
        t = FUN_00021904();
        o = *(uint64_t *)(k + 0x10);
        st = k;
        if (*(uint64_t *)(k + 0x18) >> 1 <= o) {
          FUN_00082484(1 < *(uint64_t *)(k + 0x18),o + 1,1);
        }
        *(uint64_t *)(st + 0x10) = o + 1;
        *(uint64_t *)(st + o * 8 + 0x20) = t;
        v = v - 1;
      } while (v != 0);
      v = s;
      if (s - 1 <= s) {
        v = s - 1;
      }
      k = st;
      if (v + 1 != s) {
                    /* WARNING: Does not return */
        cl4_break(0x180c04);
      }
    }
    q = FUN_00021738();
    m = (code_fn_t)FUN_0017fcc4(p);
    s = (*m)(k,q & 1,u,p);
    if (err == (void *)0x0) {
      FUN_0036b118(k);
      msgbuf5 = val3;
      w4 = slot2;
      msgbuf3 = val;
      msgbuf4 = val2;
      msgbuf2 = idx2;
      w3 = slot;
      w2 = key2;
      l = msgbuf;
      FUN_00022028(msgbuf,9,0,&st);
    }
    else {
      FUN_0036b118(k);
      st = err;
      u = FUN_00002534(&dat_0064c260,&dat_004bbc30);
      s = FUN_00365b6c(&st2,&st,u,0x6685a8,0);
      if ((s & 1) == 0) {
        r4 = val3;
        n = slot2;
        r2 = val;
        r3 = val2;
        r = idx2;
        b3 = slot;
        b2 = key2;
        FUN_00025704();
        FUN_0036b118(st);
                    /* WARNING: Subroutine does not return */
        FUN_001afa84(s_Fatal_error_005accd0,0xb,2,0xd000000000000033,0x80000000005cbe30,
                     s_StackshotConclaveSupport_Stacksh_005cbc40,0x36,2,p4,0);
      }
      s = (uint64_t)st2;
      FUN_0036b118(st);
      b = val3;
      j = slot2;
      c2 = val;
      c3 = val2;
      c = idx2;
      i = slot;
      n2 = key2;
      FUN_00022028(tmp4,5,0,&st);
      l = tmp4;
    }
    w1 = *(uint64_t *)(l + 0x10);
    fn2 = *(uint64_t *)(l + 8);
    val4 = *(uint64_t *)(l + 0x20);
    w0 = *(uint64_t *)(l + 0x18);
    fn = *(uint64_t *)(l + 0x28);
    slot3 = l[0x30];
    fn3 = (uint64_t)*l;
    if (err == (void *)0x0) {
      FUN_000230f8(0);
      FUN_00023208(s);
      goto LAB_00180b5c;
    }
    FUN_000230f8(1);
    q = (uint32_t)s;
  }
  FUN_000231f0((q & 0xff) + 1);
LAB_00180b5c:
  if ((uint8_t)fn3 == 2) {
    ptr2 = 0;
    ptr = 0;
    ptr4 = 0;
    cnt = 0;
    s = 2;
    ptr3 = 0;
    len2 = 0;
  }
  else {
    tmp3 = (uint8_t)fn3 & 1;
    len = w1;
    tmp2 = fn2;
    kind2 = val4;
    tmp = w0;
    tag2 = fn;
    tag = slot3;
    FUN_00022c48(msgbuf + 0x38);
    s = (uint64_t)msgbuf[0x38];
  }
  *p1 = s;
  p1[2] = cnt;
  p1[1] = ptr4;
  p1[4] = len2;
  p1[3] = ptr3;
  p1[5] = ptr2;
  *(uint8_t *)(p1 + 6) = ptr;
  return;
}



/* FUN_00180ef8 @ 0x00180ef8   (est. thunk -> ?)
 * Ghidra: void FUN_00180ef8(void)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_00180ef8(void)
{
    ;
}



/* FUN_00180efc @ 0x00180efc   (est. thunk -> ?)
 * Ghidra: void FUN_00180efc(void)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_00180efc(void)
{
    ;
}



/* FUN_00180f10 @ 0x00180f10   (est. thunk -> ?)
 * Ghidra: void FUN_00180f10(void)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_00180f10(void)
{
    ;
}



/* FUN_00180f14 @ 0x00180f14   (est. thunk -> ?)
 * Ghidra: void FUN_00180f14(void)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_00180f14(void)
{
    ;
}



/* FUN_00180f28 @ 0x00180f28   (est. thunk -> ?)
 * Ghidra: void FUN_00180f28(void)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_00180f28(void)
{
    ;
}



/* FUN_00180f2c @ 0x00180f2c   (est. thunk -> ?)
 * Ghidra: void FUN_00180f2c(void)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_00180f2c(void)
{
    ;
}



/* FUN_00180f44 @ 0x00180f44   (est. thunk -> ?)
 * Ghidra: void FUN_00180f44(void)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_00180f44(void)
{
    ;
}



/* FUN_00180f48 @ 0x00180f48   (est. thunk -> ?)
 * Ghidra: void FUN_00180f48(void)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_00180f48(void)
{
    ;
}



/* FUN_00180f5c @ 0x00180f5c   (est. thunk -> ?)
 * Ghidra: void FUN_00180f5c(void)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_00180f5c(void)
{
    ;
}



/* FUN_00180f60 @ 0x00180f60   (est. thunk -> ?)
 * Ghidra: void FUN_00180f60(void)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_00180f60(void)
{
    ;
}



/* FUN_00180f74 @ 0x00180f74   (est. thunk -> ?)
 * Ghidra: void FUN_00180f74(void)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_00180f74(void)
{
    ;
}



/* FUN_00180f78 @ 0x00180f78   (est. thunk -> ?)
 * Ghidra: void FUN_00180f78(void)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_00180f78(void)
{
    ;
}



/* FUN_00180f8c @ 0x00180f8c   (est. thunk -> ?)
 * Ghidra: void FUN_00180f8c(void)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_00180f8c(void)
{
    ;
}



/* FUN_00180f90 @ 0x00180f90   (est. thunk -> ?)
 * Ghidra: void FUN_00180f90(void)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_00180f90(void)
{
    ;
}



/* FUN_00180fa4 @ 0x00180fa4   (est. thunk -> ?)
 * Ghidra: void FUN_00180fa4(void)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_00180fa4(void)
{
    ;
}



/* FUN_00180fa8 @ 0x00180fa8   (est. thunk -> ?)
 * Ghidra: void FUN_00180fa8(void)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_00180fa8(void)
{
    ;
}



/* FUN_00180fbc @ 0x00180fbc   (est. thunk -> ?)
 * Ghidra: void FUN_00180fbc(void)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_00180fbc(void)
{
    ;
}



/* FUN_00180fc0 @ 0x00180fc0   (est. thunk -> ?)
 * Ghidra: void FUN_00180fc0(void)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_00180fc0(void)
{
    ;
}



/* FUN_00180fd4 @ 0x00180fd4   (est. thunk -> ?)
 * Ghidra: void FUN_00180fd4(void)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_00180fd4(void)
{
    ;
}



/* FUN_00180fd8 @ 0x00180fd8   (est. thunk -> ?)
 * Ghidra: void FUN_00180fd8(void)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_00180fd8(void)
{
    ;
}



/* FUN_00180ff8 @ 0x00180ff8   (est. thunk -> ?)
 * Ghidra: void FUN_00180ff8(void)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_00180ff8(void)
{
    ;
}



/* FUN_00180ffc @ 0x00180ffc   (est. thunk -> ?)
 * Ghidra: void FUN_00180ffc(void)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_00180ffc(void)
{
    ;
}



/* FUN_00181010 @ 0x00181010   (est. thunk -> ?)
 * Ghidra: void FUN_00181010(void)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_00181010(void)
{
    ;
}



/* FUN_00181014 @ 0x00181014   (est. thunk -> ?)
 * Ghidra: void FUN_00181014(void)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_00181014(void)
{
    ;
}



/* FUN_00181028 @ 0x00181028   (est. thunk -> ?)
 * Ghidra: void FUN_00181028(void)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_00181028(void)
{
    ;
}



/* FUN_0018102c @ 0x0018102c   (est. thunk -> ?)
 * Ghidra: void FUN_0018102c(void)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_0018102c(void)
{
    ;
}



/* FUN_00181040 @ 0x00181040   (est. thunk -> ?)
 * Ghidra: void FUN_00181040(void)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_00181040(void)
{
    ;
}



/* FUN_00181044 @ 0x00181044   (est. thunk -> ?)
 * Ghidra: void FUN_00181044(void)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_00181044(void)
{
    ;
}



/* FUN_00181058 @ 0x00181058   (est. thunk -> ?)
 * Ghidra: void FUN_00181058(void)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_00181058(void)
{
    ;
}



/* FUN_0018105c @ 0x0018105c   (est. thunk -> ?)
 * Ghidra: void FUN_0018105c(void)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_0018105c(void)
{
    ;
}



/* FUN_00181070 @ 0x00181070   (est. thunk -> ?)
 * Ghidra: void FUN_00181070(void)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_00181070(void)
{
    ;
}



/* FUN_00181074 @ 0x00181074   (est. thunk -> ?)
 * Ghidra: void FUN_00181074(void)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_00181074(void)
{
    ;
}



/* FUN_00181088 @ 0x00181088   (est. thunk -> ?)
 * Ghidra: void FUN_00181088(void)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_00181088(void)
{
    ;
}



/* FUN_0018108c @ 0x0018108c   (est. thunk -> ?)
 * Ghidra: void FUN_0018108c(void)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_0018108c(void)
{
    ;
}



/* FUN_001810a4 @ 0x001810a4   (est. FUN_001810a4)
 * Ghidra: 
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class X/None */
long FUN_001810a4(uint64_t p1, uint64_t p2)
{
  long msgbuf;
  uint64_t msgbuf2;

  msgbuf = FUN_0036a940();
  msgbuf2 = FUN_000262ec(0);
  FUN_0036a940(msgbuf2,0x18,7);
  msgbuf2 = FUN_000260e0(p1,p2);
  *(uint64_t *)(msgbuf + 0x10) = msgbuf2;
  return msgbuf;
}



/* FUN_00181118 @ 0x00181118   (est. thunk -> ?)
 * Ghidra: void FUN_00181118(void)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_00181118(void)
{
    ;
}



/* FUN_00181154 @ 0x00181154   (est. FUN_00181154)
 * Ghidra: long FUN_00181154(undefined8 p1,undefined8 p2,code_fn_t p3)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class X/None */
long FUN_00181154(uint64_t p1, uint64_t p2, code_fn_t p3)
{
  long msgbuf;
  uint64_t msgbuf3;
  long msgbuf2;
  
  msgbuf = FUN_0036a940();
  msgbuf3 = (*p3)(0);
  msgbuf2 = FUN_0036a940(msgbuf3,0x18,7);
  msgbuf3 = FUN_000262ec(0);
  FUN_0036a940(msgbuf3,0x18,7);
  msgbuf3 = FUN_000260e0(p1,p2);
  *(uint64_t *)(msgbuf2 + 0x10) = msgbuf3;
  *(long *)(msgbuf + 0x10) = msgbuf2;
  return msgbuf;
}



/* FUN_00181204 @ 0x00181204   (est. FUN_00181204)
 * Ghidra: void FUN_00181204(undefined8 p1,undefined8 p2,code_fn_t p3)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class X/None */
void FUN_00181204(uint64_t p1, uint64_t p2, code_fn_t p3)
{
  uint64_t msgbuf2;
  long msgbuf;
  long cpu;
  
  msgbuf2 = (*p3)(0);
  msgbuf = FUN_0036a940(msgbuf2,0x18,7);
  msgbuf2 = FUN_000262ec(0);
  msgbuf2 = FUN_0036a940(msgbuf2,0x18,7);
  msgbuf2 = FUN_000260e0(p1,p2,msgbuf2);
  *(uint64_t *)(msgbuf + 0x10) = msgbuf2;
  *(long *)(cpu + 0x10) = msgbuf;
  return;
}



/* FUN_00181284 @ 0x00181284   (est. thunk -> ?)
 * Ghidra: void FUN_00181284(undefined8 p1)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_00181284(uint64_t p1)
{
    ;
}



/* FUN_00181288 @ 0x00181288   (est. thunk -> ?)
 * Ghidra: void FUN_00181288(undefined8 p1)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_00181288(uint64_t p1)
{
    ;
}



/* FUN_001812b0 @ 0x001812b0   (est. thunk -> ?)
 * Ghidra: void FUN_001812b0(undefined8 p1)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_001812b0(uint64_t p1)
{
    ;
}



/* FUN_001812b4 @ 0x001812b4   (est. thunk -> ?)
 * Ghidra: void FUN_001812b4(undefined8 p1)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_001812b4(uint64_t p1)
{
    ;
}



/* FUN_001812dc @ 0x001812dc   (est. FUN_001812dc)
 * Ghidra: undefined1  [16] FUN_001812dc(undefined8 p1,code_fn_t p2)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class X/None */
cl4_16_t FUN_001812dc(uint64_t p1, code_fn_t p2)
{
  cl4_16_t msgbuf2;
  uint64_t msgbuf;
  long err;
  cl4_16_t msgbuf3;
  
  msgbuf3.lo = (*p2)();
  msgbuf2._8_8_ = msgbuf;
  msgbuf2._0_8_ = msgbuf;
  if (err != 0) {
    msgbuf3 = msgbuf2;
  }
  return msgbuf3;
}



/* FUN_00181310 @ 0x00181310   (est. thunk -> ?)
 * Ghidra: void FUN_00181310(void)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_00181310(void)
{
    ;
}



/* FUN_00181374 @ 0x00181374   (est. FUN_00181374)
 * Ghidra: undefined1  [16] FUN_00181374(void)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class X/None */
cl4_16_t FUN_00181374(void)
{
  uint64_t w3;
  uint32_t *msgbuf4;
  long err;
  uint64_t ret;
  cl4_16_t w2;
  uint64_t idx;
  uint8_t cnt2;
  uint64_t cnt;
  uint64_t errword2;
  uint64_t len2;
  uint64_t errword;
  uint64_t len;
  uint64_t msgbuf6;
  uint8_t kind2;
  uint8_t msgbuf3 [52];
  uint32_t kind;
  uint8_t msgbuf2 [56];
  uint8_t msgbuf [56];
  uint8_t msgbuf5 [56];
  uint64_t w1;
  uint64_t val3;
  uint64_t val2;
  uint64_t val;
  uint64_t w0;
  uint64_t idx2;
  uint8_t val4;
  
  FUN_00025ebc(msgbuf2,8,0,&kind);
  if (err == 0) {
    thunk_FUN_00024068(msgbuf3);
    FUN_00023208(0x9c2c8afe22ee2f4e);
    FUN_00022c48(msgbuf);
    FUN_00025f44(msgbuf5,msgbuf,&kind);
    FUN_000214b0(&cnt,msgbuf5);
    FUN_000268d0(&idx,0x668ce8,0x65a688,0x668ce8,0x65a5e8,0x668d10,&kind);
    ret = (uint64_t)cnt2;
    val3 = errword2;
    w1 = cnt;
    val = errword;
    val2 = len2;
    idx2 = msgbuf6;
    w0 = len;
    val4 = kind2;
    FUN_00025704();
  }
  else {
    w3 = FUN_00019aac(0);
    FUN_0036993c(w3,FUN_0065a550,0,0);
    *msgbuf4 = kind;
    idx = (uint64_t)kind;
  }
  w2._8_8_ = ret;
  w2._0_8_ = idx;
  return w2;
}



/* FUN_00181554 @ 0x00181554   (est. thunk -> ?)
 * Ghidra: void FUN_00181554(undefined8 p1)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_00181554(uint64_t p1)
{
    ;
}



/* FUN_00181558 @ 0x00181558   (est. thunk -> ?)
 * Ghidra: void FUN_00181558(undefined8 p1)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_00181558(uint64_t p1)
{
    ;
}



/* FUN_0018157c @ 0x0018157c   (est. thunk -> ?)
 * Ghidra: void FUN_0018157c(undefined8 p1)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_0018157c(uint64_t p1)
{
    ;
}



/* FUN_00181580 @ 0x00181580   (est. thunk -> ?)
 * Ghidra: void FUN_00181580(undefined8 p1)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_00181580(uint64_t p1)
{
    ;
}



/* FUN_001815a4 @ 0x001815a4   (est. FUN_001815a4)
 * Ghidra: undefined1  [16] FUN_001815a4(undefined8 p1,undefined8 p2)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class A/V1 */
cl4_16_t FUN_001815a4(uint64_t p1, uint64_t p2)
{
  char w3;
  uint64_t w4;
  uint32_t *msgbuf5;
  long err;
  cl4_16_t w2;
  uint64_t idx;
  uint64_t kind;
  uint64_t cnt2;
  uint64_t errword2;
  uint64_t cnt;
  uint64_t errword;
  uint64_t len2;
  uint64_t msgbuf6;
  uint8_t len;
  uint8_t msgbuf4 [52];
  uint32_t kind2;
  uint8_t msgbuf3 [56];
  uint8_t msgbuf2 [56];
  uint8_t msgbuf [56];
  uint64_t w1;
  uint64_t val3;
  uint64_t val2;
  uint64_t val;
  uint64_t w0;
  uint64_t idx2;
  uint8_t val4;
  
  FUN_00025ebc(msgbuf3,0x10,0,&kind2);
  if (err == 0) {
    thunk_FUN_00024068(msgbuf4);
    FUN_00023208(p2);
    FUN_00023208(p1);
    FUN_00022c48(msgbuf2);
    FUN_00025f44(msgbuf,msgbuf2,&kind2);
    FUN_000214b0(&cnt2,msgbuf);
    w3 = FUN_000217e4();
    if (w3 == '\x01') {
      FUN_000268d0(&idx,0x668c50,0x65a688,0x668c50,0x65a5e8,0x668cf8,&kind2);
      p1 = idx;
      p2 = kind;
    }
    else {
      p1 = 0;
      p2 = 0;
    }
    val3 = errword2;
    w1 = cnt2;
    val = errword;
    val2 = cnt;
    idx2 = msgbuf6;
    w0 = len2;
    val4 = len;
    FUN_00025704();
  }
  else {
    w4 = FUN_00019aac(0);
    FUN_0036993c(w4,FUN_0065a550,0,0);
    *msgbuf5 = kind2;
  }
  w2._8_8_ = p2;
  w2._0_8_ = p1;
  return w2;
}



/* FUN_001817bc @ 0x001817bc   (est. FUN_001817bc)
 * Ghidra: undefined4 FUN_001817bc(void)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class X/None */
uint32_t FUN_001817bc(void)
{
  uint64_t w1;
  uint64_t w2;
  uint64_t w3;
  void *w0;
  uint64_t w4;
  uint64_t w5;
  uint32_t *msgbuf4;
  uint32_t w6;
  long err;
  uint64_t w7;
  uint64_t len2;
  uint64_t errword2;
  uint64_t len;
  uint64_t errword;
  uint64_t kind2;
  uint64_t msgbuf6;
  uint8_t kind;
  uint8_t msgbuf3 [56];
  uint8_t msgbuf2 [56];
  uint8_t msgbuf [56];
  uint8_t msgbuf5 [56];
  uint64_t val4;
  uint64_t idx2;
  uint64_t idx;
  uint64_t cnt2;
  uint64_t val3;
  uint64_t cnt;
  uint8_t val2;
  uint32_t val;
  
  FUN_00025ebc(msgbuf2,8,0,&val);
  if (err == 0) {
    thunk_FUN_00024068(msgbuf3);
    FUN_00023208(0xd6197e8071d5d7a7);
    FUN_00022c48(msgbuf);
    FUN_00025f44(msgbuf5,msgbuf,&val);
    FUN_000214b0(&len2,msgbuf5);
    w5 = FUN_00021904();
    if ((long)w5 < 0) {
                    /* WARNING: Does not return */
      cl4_break(0x18199c);
    }
    if (w5 != 0) {
      FUN_00082484(0,w5,0);
      w2 = w5;
      if (w5 - 1 <= w5) {
        w2 = w5 - 1;
      }
      w7 = w5;
      do {
        w4 = FUN_00021904();
        w3 = dat_00657788;
        w1 = dat_00657788 + 1;
        if (dat_00657790 >> 1 <= dat_00657788) {
          FUN_00082484(1 < dat_00657790,w1,1);
        }
        dat_00657788 = w1;
        (&dat_00657798)[w3] = w4;
        w7 = w7 - 1;
      } while (w7 != 0);
      if (w2 + 1 != w5) {
                    /* WARNING: Does not return */
        cl4_break(0x1819a0);
      }
    }
    w6 = 0x657778;
    idx2 = errword2;
    val4 = len2;
    cnt2 = errword;
    idx = len;
    cnt = msgbuf6;
    val3 = kind2;
    val2 = kind;
    FUN_00025704();
  }
  else {
    w4 = FUN_00019aac(0);
    FUN_0036993c(w4,FUN_0065a550,0,0);
    *msgbuf4 = val;
    w6 = val;
  }
  return w6;
}



/* FUN_001819a0 @ 0x001819a0   (est. FUN_001819a0)
 * Ghidra: 
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class D/None */
void FUN_001819a0(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4, uint64_t p5)
{
  code_fn_t msgbuf;

  msgbuf = (code_fn_t)FUN_00023c78(p5);
  (*msgbuf)(p2,p4,p5);
  (*msgbuf)(p3,p4,p5);
  return;
}



/* FUN_00181a2c @ 0x00181a2c   (est. FUN_00181a2c)
 * Ghidra: undefined1  [16] FUN_00181a2c(undefined8 p1,undefined8 p2,undefined8 p3)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class D/None */
cl4_16_t FUN_00181a2c(uint64_t p1, uint64_t p2, uint64_t p3)
{
  uint64_t msgbuf3;
  uint64_t msgbuf4;
  code_fn_t msgbuf2;
  uint64_t msgbuf5;
  uint64_t msgbuf6;
  long err;
  cl4_16_t msgbuf;

  msgbuf2 = (code_fn_t)FUN_00023d00(p3);
  msgbuf5 = (*msgbuf2)(p2,p3);
  msgbuf6 = (*msgbuf2)(p2,p3);
  msgbuf3 = msgbuf5 & 0xffffffff;
  msgbuf4 = msgbuf5 & 0xffffffff;
  if (err == 0) {
    msgbuf3 = msgbuf6;
    msgbuf4 = msgbuf5;
  }
  msgbuf._8_8_ = msgbuf3;
  msgbuf._0_8_ = msgbuf4;
  return msgbuf;
}



/* FUN_00181ab4 @ 0x00181ab4   (est. FUN_00181ab4)
 * Ghidra: void FUN_00181ab4(undefined8 *p1)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class X/None */
void FUN_00181ab4(uint64_t *p1)
{
  uint64_t msgbuf2;
  uint64_t msgbuf;
  uint32_t *in_x3;
  long err;
  
  msgbuf2 = FUN_00181a2c(0,0,0).lo;
  if (err == 0) {
    *p1 = msgbuf2;
    p1[1] = msgbuf;
  }
  else {
    *in_x3 = (int)msgbuf2;
  }
  return;
}



/* FUN_00181af0 @ 0x00181af0   (est. FUN_00181af0)
 * Ghidra: undefined4 FUN_00181af0(undefined8 p1,undefined8 p2,undefined8 p3)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class X/None */
uint32_t FUN_00181af0(uint64_t p1, uint64_t p2, uint64_t p3)
{
  uint32_t msgbuf;
  uint64_t *cpu;
  long err;
  
  FUN_001819a0(p1,*cpu,cpu[1],p2,p3);
  if (err == 0) {
    msgbuf = 1;
  }
  return msgbuf;
}



/* FUN_00181af4 @ 0x00181af4   (est. FUN_00181af4)
 * Ghidra: undefined4 FUN_00181af4(undefined8 p1,undefined8 p2,undefined8 p3)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class X/None */
uint32_t FUN_00181af4(uint64_t p1, uint64_t p2, uint64_t p3)
{
  uint32_t msgbuf;
  uint64_t *cpu;
  long err;
  
  FUN_001819a0(p1,*cpu,cpu[1],p2,p3);
  if (err == 0) {
    msgbuf = 1;
  }
  return msgbuf;
}



/* FUN_00181b3c @ 0x00181b3c   (est. FUN_00181b3c)
 * Ghidra: 
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class D/None */
void FUN_00181b3c(uint64_t p1, uint64_t p2, char p3, uint64_t p4, uint64_t p5)
{
  code_fn_t msgbuf;

  msgbuf = (code_fn_t)FUN_00023c78(p5);
  if (p3 == '\x01') {
    p2 = 0x53fc08af3ee9551b;
  }
  else {
    (*msgbuf)(0xda5350727cc174b2,p4,p5);
  }
  (*msgbuf)(p2,p4,p5);
  return;
}



/* FUN_00181bf0 @ 0x00181bf0   (est. FUN_00181bf0)
 * Ghidra: undefined1  [16] FUN_00181bf0(undefined8 p1,undefined8 p2,undefined8 p3)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class X/None */
cl4_16_t FUN_00181bf0(uint64_t p1, uint64_t p2, uint64_t p3)
{
  uint64_t msgbuf4;
  uint64_t msgbuf5;
  bool msgbuf3;
  uint32_t msgbuf6;
  long err;
  cl4_16_t msgbuf;
  cl4_16_t msgbuf2;

  msgbuf2 = FUN_00181c44(p2,p3);
  msgbuf3 = (msgbuf2._8_4_ & 0xff) == 1;
  msgbuf4 = 0;
  if (!msgbuf3) {
    msgbuf4 = msgbuf2._0_8_;
  }
  msgbuf5 = msgbuf2._0_8_ & 0xffffffff;
  if (err == 0) {
    msgbuf5 = msgbuf4;
  }
  msgbuf6 = 1;
  if (err == 0) {
    msgbuf6 = (uint32_t)msgbuf3;
  }
  msgbuf._8_4_ = msgbuf6;
  msgbuf._0_8_ = msgbuf5;
  msgbuf._12_4_ = 0;
  return msgbuf;
}



/* FUN_00181c44 @ 0x00181c44   (est. FUN_00181c44)
 * Ghidra: undefined1  [16] FUN_00181c44(undefined8 p1,undefined8 p2)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class D/None */
cl4_16_t FUN_00181c44(uint64_t p1, uint64_t p2)
{
  code_fn_t msgbuf3;
  long msgbuf4;
  uint64_t msgbuf5;
  uint64_t msgbuf6;
  uint64_t msgbuf;
  cl4_16_t msgbuf2;

  msgbuf3 = (code_fn_t)FUN_00023d00(p2);
  msgbuf4 = (*msgbuf3)(p1,p2);
  if (msgbuf4 == 0x53fc08af3ee9551b) {
    msgbuf5 = 0;
    msgbuf6 = 1;
  }
  else {
    if (msgbuf4 != -0x25acaf8d833e8b4e) {
      FUN_002a4ab4(0x1c);
      FUN_003a25d4(0xe000000000000000);
      msgbuf3 = (code_fn_t)FUN_00027724(0x671848);
      (*msgbuf3)(0x677790,0x671848);
      thunk_FUN_002acbb8();
      FUN_003a25d4(msgbuf);
                    /* WARNING: Subroutine does not return */
      FUN_001afa84(s_Fatal_error_005accd0,0xb,2,0xd00000000000001a,0x80000000005c9590,
                   s_XnuProxyStackshotSupport_Stacksh_005cbf60,0x35,2,0x129,0);
    }
    msgbuf5 = (*msgbuf3)(p1,p2);
    msgbuf6 = 0;
  }
  msgbuf2._8_8_ = msgbuf6;
  msgbuf2._0_8_ = msgbuf5;
  return msgbuf2;
}



/* FUN_00181db8 @ 0x00181db8   (est. FUN_00181db8)
 * Ghidra: void FUN_00181db8(undefined8 *p1)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class X/None */
void FUN_00181db8(uint64_t *p1)
{
  uint64_t msgbuf2;
  uint8_t msgbuf;
  uint32_t *in_x3;
  long err;
  
  msgbuf2 = FUN_00181bf0(0,0,0).lo;
  if (err == 0) {
    *p1 = msgbuf2;
    *(uint8_t *)(p1 + 1) = msgbuf;
  }
  else {
    *in_x3 = (int)msgbuf2;
  }
  return;
}



/* FUN_00181e10 @ 0x00181e10   (est. FUN_00181e10)
 * Ghidra: undefined4 FUN_00181e10(undefined8 p1,undefined8 p2,undefined8 p3)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class X/None */
uint32_t FUN_00181e10(uint64_t p1, uint64_t p2, uint64_t p3)
{
  uint32_t msgbuf;
  uint64_t *cpu;
  long err;
  
  FUN_00181b3c(p1,*cpu,*(uint8_t *)(cpu + 1),p2,p3);
  if (err == 0) {
    msgbuf = 1;
  }
  return msgbuf;
}



/* FUN_00181e14 @ 0x00181e14   (est. FUN_00181e14)
 * Ghidra: undefined4 FUN_00181e14(undefined8 p1,undefined8 p2,undefined8 p3)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class X/None */
uint32_t FUN_00181e14(uint64_t p1, uint64_t p2, uint64_t p3)
{
  uint32_t msgbuf;
  uint64_t *cpu;
  long err;
  
  FUN_00181b3c(p1,*cpu,*(uint8_t *)(cpu + 1),p2,p3);
  if (err == 0) {
    msgbuf = 1;
  }
  return msgbuf;
}



/* FUN_00181eb8 @ 0x00181eb8   (est. FUN_00181eb8)
 * Ghidra: void FUN_00181eb8(undefined8 p1,undefined8 p2,undefined8 p3)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class X/None */
void FUN_00181eb8(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4)
{
  uint8_t msgbuf [56];
  
  thunk_FUN_00024068(msgbuf);
  FUN_00023208(p2);
  FUN_00023208(p3);
  FUN_00025704();
  return;
}



/* FUN_00181f20 @ 0x00181f20   (est. FUN_00181f20)
 * Ghidra: ulong FUN_00181f20(undefined8 p1,undefined8 p2)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class X/None */
uint64_t FUN_00181f20(uint64_t p1, uint64_t p2)
{
  uint64_t msgbuf5;
  uint64_t msgbuf6;
  uint64_t *cpu;
  long err;
  uint8_t msgbuf [16];
  uint64_t msgbuf4;
  uint64_t msgbuf2;
  uint32_t msgbuf3;
  
  msgbuf2 = cpu[1];
  msgbuf4 = *cpu;
  msgbuf5 = FUN_00019aac(0);
  msgbuf6 = FUN_00023f74(0,p1,p2,FUN_00181fd0,msgbuf,0x67b148,msgbuf5,FUN_0065a550,
                       &msgbuf3);
  if (err != 0) {
    msgbuf6 = (uint64_t)msgbuf3;
  }
  return msgbuf6;
}



/* FUN_00181fd0 @ 0x00181fd0   (est. FUN_00181fd0)
 * Ghidra: void FUN_00181fd0(undefined8 p1,undefined8 p2)
 * Small upcall / message-register marshalling helper. Confidence: medium
 * Notes: part of the XNU upcall layer. */
void FUN_00181fd0(uint64_t a, uint64_t b)
{
    /* Sends a two-word upcall reply: writes the two per-CPU words at x20+0x10
     * and x20+0x18 via the message writer then delivers (FUN_00181eb8). */
    FUN_00181eb8(a, *(uint64_t *)(per_cpu + 0x10), *(uint64_t *)(per_cpu + 0x18), b);
}


/* FUN_00181fd4 @ 0x00181fd4   (est. FUN_00181fd4)
 * Ghidra: void FUN_00181fd4(undefined8 p1,undefined8 p2)
 * Small upcall / message-register marshalling helper. Confidence: medium
 * Notes: part of the XNU upcall layer. */
void FUN_00181fd4(uint64_t a, uint64_t b)
{
    /* Twin of 00181fd0; same two-word upcall reply from the per-CPU words. */
    FUN_00181eb8(a, *(uint64_t *)(per_cpu + 0x10), *(uint64_t *)(per_cpu + 0x18), b);
}


/* FUN_0018200c @ 0x0018200c   (est. FUN_0018200c)
 * Ghidra: undefined1 FUN_0018200c(void)
 * Small upcall / message-register marshalling helper. Confidence: medium
 * Notes: part of the XNU upcall layer. */
uint8_t FUN_0018200c(void)
{
    /* Returns the per-CPU upcall kind uint8_t (unaff_x20[0]). */
    return *per_cpu;
}


/* FUN_00182018 @ 0x00182018   (est. FUN_00182018)
 * Ghidra: void FUN_00182018(undefined8 p1)
 * Small upcall / message-register marshalling helper. Confidence: medium
 * Notes: part of the XNU upcall layer. */
void FUN_00182018(uint64_t v)
{
    /* Sets the upcall result: FUN_0022995c(v, per-CPU kind uint8_t). */
    FUN_0022995c(v, *per_cpu);
}


/* FUN_00182080 @ 0x00182080   (est. FUN_00182080)
 * Ghidra: void FUN_00182080(undefined1 *p1,uint p2)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class X/None */
void FUN_00182080(uint64_t *p1, uint32_t p2)
{
  uint8_t msgbuf;
  
  if (p2 < 0x82) {
    msgbuf = 4;
    switch(p2) {
    default:
      msgbuf = 0;
    case 0xc:
      *p1 = msgbuf;
      return;
    case 1:
      *p1 = 1;
      return;
    case 2:
      *p1 = 2;
      return;
    case 3:
    case 4:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 0xb:
    case 0xe:
    case 0xf:
    case 0x10:
    case 0x12:
    case 0x13:
    case 0x17:
    case 0x18:
    case 0x19:
    case 0x1a:
    case 0x1b:
    case 0x1d:
    case 0x1f:
    case 0x20:
    case 0x21:
    case 0x24:
    case 0x25:
    case 0x26:
    case 0x27:
    case 0x28:
    case 0x29:
    case 0x2a:
    case 0x2b:
    case 0x2c:
    case 0x2e:
    case 0x2f:
    case 0x30:
    case 0x31:
    case 0x32:
    case 0x33:
    case 0x34:
    case 0x35:
    case 0x36:
    case 0x38:
    case 0x39:
    case 0x3a:
    case 0x3b:
    case 0x3c:
    case 0x3d:
    case 0x3e:
    case 0x40:
    case 0x41:
    case 0x42:
    case 0x43:
    case 0x44:
    case 0x45:
    case 0x47:
    case 0x48:
    case 0x49:
    case 0x4a:
    case 0x4b:
    case 0x4c:
    case 0x4d:
    case 0x4e:
    case 0x4f:
    case 0x51:
    case 0x52:
    case 0x53:
    case 0x54:
    case 0x55:
    case 0x56:
    case 0x57:
    case 0x58:
    case 0x59:
    case 0x5a:
    case 0x5b:
    case 0x5c:
    case 0x5d:
    case 0x5e:
    case 0x5f:
    case 0x60:
    case 0x61:
    case 0x62:
    case 99:
    case 100:
    case 0x65:
    case 0x66:
    case 0x67:
    case 0x68:
    case 0x69:
    case 0x6a:
    case 0x6b:
    case 0x6c:
    case 0x6d:
    case 0x6e:
    case 0x6f:
    case 0x70:
    case 0x71:
    case 0x72:
    case 0x73:
    case 0x74:
    case 0x75:
    case 0x76:
    case 0x77:
    case 0x78:
    case 0x79:
    case 0x7a:
    case 0x7b:
    case 0x7c:
    case 0x7d:
    case 0x7e:
    case 0x7f:
      goto switchD_001820ac_caseD_3;
    case 5:
      *p1 = 3;
      return;
    case 0xd:
      *p1 = 5;
      return;
    case 0x11:
      *p1 = 6;
      return;
    case 0x14:
      *p1 = 7;
      return;
    case 0x15:
      *p1 = 8;
      return;
    case 0x16:
      *p1 = 9;
      return;
    case 0x1c:
      *p1 = 10;
      return;
    case 0x1e:
      *p1 = 0xb;
      return;
    case 0x22:
      *p1 = 0xc;
      return;
    case 0x23:
      *p1 = 0xd;
      return;
    case 0x2d:
      *p1 = 0xe;
      return;
    case 0x37:
      *p1 = 0xf;
      return;
    case 0x3f:
      *p1 = 0x10;
      return;
    case 0x46:
      *p1 = 0x11;
      return;
    case 0x50:
      *p1 = 0x12;
      return;
    case 0x80:
      *p1 = 0x13;
      return;
    case 0x81:
      *p1 = 0x14;
      return;
    }
  }
  if (p2 == 9999) {
    *p1 = 0x15;
    return;
  }
switchD_001820ac_caseD_3:
  *p1 = 0x16;
  return;
}



/* FUN_001823e0 @ 0x001823e0   (est. FUN_001823e0)
 * Ghidra: void FUN_001823e0(void)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class X/None */
void FUN_001823e0(void)
{
  uint8_t msgbuf2;
  uint8_t *cpu;
  uint8_t msgbuf [72];
  
  msgbuf2 = *cpu;
  FUN_001a84f4(msgbuf,0);
  FUN_0022995c(*(uint32_t *)(&dat_004e6154 + (uint64_t)msgbuf2 * 4));
  FUN_001a8564();
  return;
}



/* FUN_00182430 @ 0x00182430   (est. FUN_00182430)
 * Ghidra: void FUN_00182430(undefined8 p1)
 * Small upcall / message-register marshalling helper. Confidence: medium
 * Notes: part of the XNU upcall layer. */
void FUN_00182430(uint64_t v)
{
    /* Sets the upcall result from a per-CPU-indexed table entry:
     * FUN_0022995c(v, dat_004e6154[per-CPU-kind * 4]). */
    FUN_0022995c(v, *(uint32_t *)(dat_004e6154 + (uint64_t)*per_cpu * 4));
}


/* FUN_00182468 @ 0x00182468   (est. FUN_00182468)
 * Ghidra: void FUN_00182468(void)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class X/None */
void FUN_00182468(void)
{
  uint8_t msgbuf2;
  uint8_t *cpu;
  uint8_t msgbuf [72];
  
  msgbuf2 = *cpu;
  FUN_001a84f4(msgbuf);
  FUN_0022995c(*(uint32_t *)(&dat_004e6154 + (uint64_t)msgbuf2 * 4));
  FUN_001a8564();
  return;
}



/* FUN_001824d4 @ 0x001824d4   (est. FUN_001824d4)
 * Ghidra: void FUN_001824d4(undefined8 p1,undefined8 p2)
 * Small upcall / message-register marshalling helper. Confidence: medium
 * Notes: part of the XNU upcall layer. */
void FUN_001824d4(uint64_t a, uint64_t b)
{
    /* Replies through the cL4 writer FUN_00208478 with the fixed class key
     * 0x668e58 and the current trap state (FUN_0002142c). */
    uint64_t st = FUN_0002142c();
    FUN_00208478(a, b, 0x668e58, st);
}


/* FUN_00182528 @ 0x00182528   (est. FUN_00182528)
 * Ghidra: void FUN_00182528(undefined8 p1,undefined8 p2)
 * Small upcall / message-register marshalling helper. Confidence: medium
 * Notes: part of the XNU upcall layer. */
void FUN_00182528(uint64_t a, uint64_t b)
{
    uint64_t st = FUN_0002142c();
    FUN_00208478(a, b, 0x668ea8, st);
}


/* FUN_0018257c @ 0x0018257c   (est. FUN_0018257c)
 * Ghidra: void FUN_0018257c(void)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class X/None */
void FUN_0018257c(void)
{
  uint8_t msgbuf2;
  uint8_t *cpu;
  uint8_t msgbuf [72];
  
  msgbuf2 = *cpu;
  FUN_001a84f4(msgbuf,0);
  FUN_0022995c(msgbuf2);
  FUN_001a8564();
  return;
}



/* FUN_001825c4 @ 0x001825c4   (est. FUN_001825c4)
 * Ghidra: void FUN_001825c4(void)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class X/None */
void FUN_001825c4(void)
{
  uint8_t msgbuf2;
  uint8_t *cpu;
  uint8_t msgbuf [72];
  
  msgbuf2 = *cpu;
  FUN_001a84f4(msgbuf);
  FUN_0022995c(msgbuf2);
  FUN_001a8564();
  return;
}



/* FUN_00182630 @ 0x00182630   (est. FUN_00182630)
 * Ghidra: void FUN_00182630(void)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class X/None */
void FUN_00182630(void)
{
  uint8_t msgbuf [72];
  
  FUN_001a84f4(msgbuf,0);
  FUN_0022995c(1);
  FUN_001a8564();
  return;
}



/* FUN_00182674 @ 0x00182674   (est. thunk -> ?)
 * Ghidra: void FUN_00182674(void)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_00182674(void)
{
    ;
}



/* FUN_0018269c @ 0x0018269c   (est. FUN_0018269c)
 * Ghidra: void FUN_0018269c(void)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class X/None */
void FUN_0018269c(void)
{
  uint8_t msgbuf [72];
  
  FUN_001a84f4(msgbuf);
  FUN_0022995c(1);
  FUN_001a8564();
  return;
}



/* FUN_001826f0 @ 0x001826f0   (est. FUN_001826f0)
 * Ghidra: void FUN_001826f0(undefined8 p1,undefined8 p2)
 * Small upcall / message-register marshalling helper. Confidence: medium
 * Notes: part of the XNU upcall layer. */
void FUN_001826f0(uint64_t a, uint64_t b)
{
    uint64_t st = FUN_0002142c();
    FUN_00208478(a, b, 0x668f48, st);
}


/* FUN_0018276c @ 0x0018276c   (est. FUN_0018276c)
 * Ghidra: void FUN_0018276c(undefined8 p1,undefined8 p2)
 * Small upcall / message-register marshalling helper. Confidence: medium
 * Notes: part of the XNU upcall layer. */
void FUN_0018276c(uint64_t a, uint64_t b)
{
    uint64_t st = FUN_0002142c();
    FUN_00208478(a, b, 0x668f98, st);
}


/* FUN_001827d0 @ 0x001827d0   (est. FUN_001827d0)
 * Ghidra: long FUN_001827d0(undefined8 p1,undefined8 p2)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class X/None */
long FUN_001827d0(uint64_t p1, uint64_t p2)
{
  long msgbuf;
  uint64_t msgbuf3;
  long msgbuf2;
  
  msgbuf = FUN_0036a940();
    msgbuf2 = FUN_0036a940(msgbuf3,0x18,7);
  msgbuf3 = FUN_000262ec(0);
  FUN_0036a940(msgbuf3,0x18,7);
  msgbuf3 = FUN_000260e0(p1,p2);
  *(uint64_t *)(msgbuf2 + 0x10) = msgbuf3;
  *(long *)(msgbuf + 0x10) = msgbuf2;
  return msgbuf;
}



/* FUN_00182860 @ 0x00182860   (est. FUN_00182860)
 * Ghidra: void FUN_00182860(undefined8 p1,undefined8 p2)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class X/None */
void FUN_00182860(uint64_t p1, uint64_t p2)
{
  uint64_t msgbuf2;
  long msgbuf;
  long cpu;
  
  msgbuf2 = FUN_0018e1c0().lo;
  msgbuf = FUN_0036a940(msgbuf2,0x18,7);
  msgbuf2 = FUN_000262ec(0);
  msgbuf2 = FUN_0036a940(msgbuf2,0x18,7);
  msgbuf2 = FUN_000260e0(p1,p2,msgbuf2);
  *(uint64_t *)(msgbuf + 0x10) = msgbuf2;
  *(long *)(cpu + 0x10) = msgbuf;
  return;
}



/* FUN_001828dc @ 0x001828dc   (est. thunk -> ?)
 * Ghidra: void FUN_001828dc(void)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_001828dc(void)
{
    ;
}



/* FUN_00182900 @ 0x00182900   (est. FUN_00182900)
 * Ghidra: void FUN_00182900(void)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class B/None */
void FUN_00182900(void)
{
  void *msgbuf4;
  int msgbuf5;
  uint64_t msgbuf6;
  char *msgbuf2;
  long err;
  char msgbuf3;
  uint8_t msgbuf;
  
  FUN_00185ce4(0);
  if (err != 0) {
    FUN_0036b270();
    msgbuf6 = FUN_00002534(&dat_0064c260,&dat_004bbc30);
    msgbuf5 = FUN_00365b6c(&stack_arg,&stack_arg,msgbuf6,0x669b78,0);
    if (msgbuf5 == 0) {
      FUN_0036b118(err);
      FUN_0036b270();
      FUN_002a4ab4(0x2f);
      thunk_FUN_002acbb8(0xd00000000000002d,0x80000000005cbfa0);
      FUN_00205844(&stack_arg,&stack_arg,msgbuf6,0x6756a8,0x66e1b8);
                    /* WARNING: Subroutine does not return */
      FUN_001afa84(s_Fatal_error_005accd0,0xb,2,0,0xe000000000000000,
                   s_XnuUpcalls_XnuUpcalls_swift_005cbfa0,0x1b,2,0x10a,0);
    }
    FUN_0036b118();
    FUN_0036993c(0x669208,0x668e68,0,0);
    FUN_00182080(&msgbuf3,*(uint32_t *)(&dat_004e6154 + (uint64_t)msgbuf * 4));
    if (msgbuf3 == '\x16') {
                    /* WARNING: Does not return */
      cl4_break(0x1829f8);
    }
    *msgbuf2 = msgbuf3;
    FUN_0036986c();
    FUN_0036b118(err);
  }
  return;
}



/* FUN_00182aac @ 0x00182aac   (est. FUN_00182aac)
 * Ghidra: void FUN_00182aac(char *p1)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class B/None */
void FUN_00182aac(char *p1)
{
  void *msgbuf4;
  int msgbuf5;
  uint64_t msgbuf6;
  char *msgbuf2;
  long err;
  char msgbuf3;
  uint8_t msgbuf;
  
  FUN_00186094(*p1 == '\x01',0,0);
  if (err != 0) {
    FUN_0036b270();
    msgbuf6 = FUN_00002534(&dat_0064c260,&dat_004bbc30);
    msgbuf5 = FUN_00365b6c(&stack_arg,&stack_arg,msgbuf6,0x669b78,0);
    if (msgbuf5 == 0) {
      FUN_0036b118(err);
      FUN_0036b270();
      FUN_002a4ab4(0x2f);
      thunk_FUN_002acbb8(0xd00000000000002d,0x80000000005cbfa0);
      FUN_00205844(&stack_arg,&stack_arg,msgbuf6,0x6756a8,0x66e1b8);
                    /* WARNING: Subroutine does not return */
      FUN_001afa84(s_Fatal_error_005accd0,0xb,2,0,0xe000000000000000,
                   s_XnuUpcalls_XnuUpcalls_swift_005cbfa0,0x1b,2,0x10a,0);
    }
    FUN_0036b118();
    FUN_0036993c(0x669208,0x668e68,0,0);
    FUN_00182080(&msgbuf3,*(uint32_t *)(&dat_004e6154 + (uint64_t)msgbuf * 4));
    if (msgbuf3 == '\x16') {
                    /* WARNING: Does not return */
      cl4_break(0x182bb0);
    }
    *msgbuf2 = msgbuf3;
    FUN_0036986c();
    FUN_0036b118(err);
  }
  return;
}



/* FUN_00182c64 @ 0x00182c64   (est. FUN_00182c64)
 * Ghidra: void FUN_00182c64(char *p1)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class B/None */
void FUN_00182c64(char *p1)
{
  void *msgbuf4;
  int msgbuf5;
  uint64_t msgbuf6;
  char *msgbuf2;
  long err;
  char msgbuf3;
  uint8_t msgbuf;
  
  FUN_00186460(*p1 == '\x01',0);
  if (err != 0) {
    FUN_0036b270();
    msgbuf6 = FUN_00002534(&dat_0064c260,&dat_004bbc30);
    msgbuf5 = FUN_00365b6c(&stack_arg,&stack_arg,msgbuf6,0x669b78,0);
    if (msgbuf5 == 0) {
      FUN_0036b118(err);
      FUN_0036b270();
      FUN_002a4ab4(0x2f);
      thunk_FUN_002acbb8(0xd00000000000002d,0x80000000005cbfa0);
      FUN_00205844(&stack_arg,&stack_arg,msgbuf6,0x6756a8,0x66e1b8);
                    /* WARNING: Subroutine does not return */
      FUN_001afa84(s_Fatal_error_005accd0,0xb,2,0,0xe000000000000000,
                   s_XnuUpcalls_XnuUpcalls_swift_005cbfa0,0x1b,2,0x10a,0);
    }
    FUN_0036b118();
    FUN_0036993c(0x669208,0x668e68,0,0);
    FUN_00182080(&msgbuf3,*(uint32_t *)(&dat_004e6154 + (uint64_t)msgbuf * 4));
    if (msgbuf3 == '\x16') {
                    /* WARNING: Does not return */
      cl4_break(0x182d68);
    }
    *msgbuf2 = msgbuf3;
    FUN_0036986c();
    FUN_0036b118(err);
  }
  return;
}



/* FUN_00182e1c @ 0x00182e1c   (est. FUN_00182e1c)
 * Ghidra: void FUN_00182e1c(char *p1)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class B/None */
void FUN_00182e1c(char *p1)
{
  void *msgbuf4;
  int msgbuf5;
  uint64_t msgbuf6;
  char *msgbuf2;
  long err;
  char msgbuf3;
  uint8_t msgbuf;
  
  FUN_001866dc(*p1 == '\x01',0,0);
  if (err != 0) {
    FUN_0036b270();
    msgbuf6 = FUN_00002534(&dat_0064c260,&dat_004bbc30);
    msgbuf5 = FUN_00365b6c(&stack_arg,&stack_arg,msgbuf6,0x669b78,0);
    if (msgbuf5 == 0) {
      FUN_0036b118(err);
      FUN_0036b270();
      FUN_002a4ab4(0x2f);
      thunk_FUN_002acbb8(0xd00000000000002d,0x80000000005cbfa0);
      FUN_00205844(&stack_arg,&stack_arg,msgbuf6,0x6756a8,0x66e1b8);
                    /* WARNING: Subroutine does not return */
      FUN_001afa84(s_Fatal_error_005accd0,0xb,2,0,0xe000000000000000,
                   s_XnuUpcalls_XnuUpcalls_swift_005cbfa0,0x1b,2,0x10a,0);
    }
    FUN_0036b118();
    FUN_0036993c(0x669208,0x668e68,0,0);
    FUN_00182080(&msgbuf3,*(uint32_t *)(&dat_004e6154 + (uint64_t)msgbuf * 4));
    if (msgbuf3 == '\x16') {
                    /* WARNING: Does not return */
      cl4_break(0x182f20);
    }
    *msgbuf2 = msgbuf3;
    FUN_0036986c();
    FUN_0036b118(err);
  }
  return;
}



/* FUN_00182fd4 @ 0x00182fd4   (est. FUN_00182fd4)
 * Ghidra: void FUN_00182fd4(char *p1,undefined8 p2)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class B/None */
void FUN_00182fd4(char *p1, uint64_t p2)
{
  void *msgbuf4;
  int msgbuf5;
  uint64_t msgbuf6;
  char *msgbuf2;
  long err;
  char msgbuf3;
  uint8_t msgbuf;
  
  FUN_00186aa8(*p1 == '\x01',p2,&stack_arg);
  if (err != 0) {
    FUN_0036b270();
    msgbuf6 = FUN_00002534(&dat_0064c260,&dat_004bbc30);
    msgbuf5 = FUN_00365b6c(&stack_arg,&stack_arg,msgbuf6,0x669b78,0);
    if (msgbuf5 == 0) {
      FUN_0036b118(err);
      FUN_0036b270();
      FUN_002a4ab4(0x2f);
      thunk_FUN_002acbb8(0xd00000000000002d,0x80000000005cbfa0);
      FUN_00205844(&stack_arg,&stack_arg,msgbuf6,0x6756a8,0x66e1b8);
                    /* WARNING: Subroutine does not return */
      FUN_001afa84(s_Fatal_error_005accd0,0xb,2,0,0xe000000000000000,
                   s_XnuUpcalls_XnuUpcalls_swift_005cbfa0,0x1b,2,0x10a,0);
    }
    FUN_0036b118();
    FUN_0036993c(0x669208,0x668e68,0,0);
    FUN_00182080(&msgbuf3,*(uint32_t *)(&dat_004e6154 + (uint64_t)msgbuf * 4));
    if (msgbuf3 == '\x16') {
                    /* WARNING: Does not return */
      cl4_break(0x1830ec);
    }
    *msgbuf2 = msgbuf3;
    FUN_0036986c();
    FUN_0036b118(err);
  }
  return;
}



/* FUN_001831a0 @ 0x001831a0   (est. FUN_001831a0)
 * Ghidra: void FUN_001831a0(char *p1,undefined8 p2)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class B/None */
void FUN_001831a0(char *p1, uint64_t p2)
{
  void *msgbuf4;
  int msgbuf5;
  uint64_t msgbuf6;
  char *msgbuf2;
  long err;
  char msgbuf3;
  uint8_t msgbuf;
  
  FUN_00186e3c(*p1 == '\x01',p2,&stack_arg);
  if (err != 0) {
    FUN_0036b270();
    msgbuf6 = FUN_00002534(&dat_0064c260,&dat_004bbc30);
    msgbuf5 = FUN_00365b6c(&stack_arg,&stack_arg,msgbuf6,0x669b78,0);
    if (msgbuf5 == 0) {
      FUN_0036b118(err);
      FUN_0036b270();
      FUN_002a4ab4(0x2f);
      thunk_FUN_002acbb8(0xd00000000000002d,0x80000000005cbfa0);
      FUN_00205844(&stack_arg,&stack_arg,msgbuf6,0x6756a8,0x66e1b8);
                    /* WARNING: Subroutine does not return */
      FUN_001afa84(s_Fatal_error_005accd0,0xb,2,0,0xe000000000000000,
                   s_XnuUpcalls_XnuUpcalls_swift_005cbfa0,0x1b,2,0x10a,0);
    }
    FUN_0036b118();
    FUN_0036993c(0x669208,0x668e68,0,0);
    FUN_00182080(&msgbuf3,*(uint32_t *)(&dat_004e6154 + (uint64_t)msgbuf * 4));
    if (msgbuf3 == '\x16') {
                    /* WARNING: Does not return */
      cl4_break(0x1832b8);
    }
    *msgbuf2 = msgbuf3;
    FUN_0036986c();
    FUN_0036b118(err);
  }
  return;
}



/* FUN_0018336c @ 0x0018336c   (est. FUN_0018336c)
 * Ghidra: void FUN_0018336c(char *p1)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class B/None */
void FUN_0018336c(char *p1)
{
  void *msgbuf4;
  int msgbuf5;
  uint64_t msgbuf6;
  char *msgbuf2;
  long err;
  char msgbuf3;
  uint8_t msgbuf;
  
  FUN_001871d0(*p1 == '\x01',0,0);
  if (err != 0) {
    FUN_0036b270();
    msgbuf6 = FUN_00002534(&dat_0064c260,&dat_004bbc30);
    msgbuf5 = FUN_00365b6c(&stack_arg,&stack_arg,msgbuf6,0x669b78,0);
    if (msgbuf5 == 0) {
      FUN_0036b118(err);
      FUN_0036b270();
      FUN_002a4ab4(0x2f);
      thunk_FUN_002acbb8(0xd00000000000002d,0x80000000005cbfa0);
      FUN_00205844(&stack_arg,&stack_arg,msgbuf6,0x6756a8,0x66e1b8);
                    /* WARNING: Subroutine does not return */
      FUN_001afa84(s_Fatal_error_005accd0,0xb,2,0,0xe000000000000000,
                   s_XnuUpcalls_XnuUpcalls_swift_005cbfa0,0x1b,2,0x10a,0);
    }
    FUN_0036b118();
    FUN_0036993c(0x669208,0x668e68,0,0);
    FUN_00182080(&msgbuf3,*(uint32_t *)(&dat_004e6154 + (uint64_t)msgbuf * 4));
    if (msgbuf3 == '\x16') {
                    /* WARNING: Does not return */
      cl4_break(0x183470);
    }
    *msgbuf2 = msgbuf3;
    FUN_0036986c();
    FUN_0036b118(err);
  }
  return;
}



/* FUN_00183524 @ 0x00183524   (est. FUN_00183524)
 * Ghidra: void FUN_00183524(char *p1,char *p2)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class B/None */
void FUN_00183524(char *p1, char *p2)
{
  void *msgbuf4;
  int msgbuf5;
  uint64_t msgbuf6;
  char *msgbuf2;
  long err;
  char msgbuf3;
  uint8_t msgbuf;
  
  FUN_0018758c(*p1 == '\x01',*p2 == '\x01',0);
  if (err != 0) {
    FUN_0036b270();
    msgbuf6 = FUN_00002534(&dat_0064c260,&dat_004bbc30);
    msgbuf5 = FUN_00365b6c(&stack_arg,&stack_arg,msgbuf6,0x669b78,0);
    if (msgbuf5 == 0) {
      FUN_0036b118(err);
      FUN_0036b270();
      FUN_002a4ab4(0x2f);
      thunk_FUN_002acbb8(0xd00000000000002d,0x80000000005cbfa0);
      FUN_00205844(&stack_arg,&stack_arg,msgbuf6,0x6756a8,0x66e1b8);
                    /* WARNING: Subroutine does not return */
      FUN_001afa84(s_Fatal_error_005accd0,0xb,2,0,0xe000000000000000,
                   s_XnuUpcalls_XnuUpcalls_swift_005cbfa0,0x1b,2,0x10a,0);
    }
    FUN_0036b118();
    FUN_0036993c(0x669208,0x668e68,0,0);
    FUN_00182080(&msgbuf3,*(uint32_t *)(&dat_004e6154 + (uint64_t)msgbuf * 4));
    if (msgbuf3 == '\x16') {
                    /* WARNING: Does not return */
      cl4_break(0x183634);
    }
    *msgbuf2 = msgbuf3;
    FUN_0036986c();
    FUN_0036b118(err);
  }
  return;
}



/* FUN_001836e8 @ 0x001836e8   (est. FUN_001836e8)
 * Ghidra: ulong FUN_001836e8(char *p1,undefined8 p2,undefined8 p3,undefined8 p4)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class A/V1 */
uint64_t FUN_001836e8(char *p1, uint64_t p2, uint64_t p3, uint64_t p4)
{
  void *key;
  char slot;
  int slot2;
  uint64_t slot3;
  uint64_t fn;
  char *msgbuf4;
  char *key2;
  uint64_t fn2;
  long err;
  cl4_16_t h4;
  uint64_t fn3;
  uint64_t tmp2;
  uint64_t val2;
  uint64_t tmp;
  uint64_t val;
  uint64_t tag2;
  uint64_t idx2;
  uint8_t tag;
  uint64_t w7;
  uint64_t idx;
  uint64_t cnt2;
  uint64_t cnt;
  uint64_t w6;
  uint64_t len2;
  uint8_t w5;
  char w4;
  uint32_t w3;
  uint8_t msgbuf3 [56];
  uint8_t msgbuf2 [56];
  uint8_t msgbuf [56];
  uint64_t w2;
  uint64_t len;
  uint64_t kind2;
  uint64_t kind;
  uint64_t w1;
  uint64_t errword2;
  uint8_t w0;
  uint64_t val4;
  uint64_t errword;
  uint64_t msgbuf6;
  uint64_t msgbuf5;
  uint64_t val3;
  uint64_t ptr3;
  uint8_t h3;
  uint64_t h2;
  uint64_t ptr2;
  uint64_t ptr;
  uint64_t tmp4;
  uint64_t h;
  uint64_t tmp3;
  uint8_t ptr4;
  
  slot = *p1;
  FUN_00025ebc(msgbuf3,0x20,0,&w3);
  if (err == 0) {
    thunk_FUN_00024068(&w7);
    FUN_00023208(0xe9ae05552f08ff2);
    FUN_000231f0(slot == '\x01');
    FUN_00023208(p2);
    FUN_00023208(p3);
    FUN_000231f0(p4);
    ptr2 = idx;
    h2 = w7;
    tmp4 = cnt;
    ptr = cnt2;
    tmp3 = len2;
    h = w6;
    ptr4 = w5;
    FUN_00022c48(msgbuf2);
    FUN_00025f44(msgbuf,msgbuf2,&w3);
    FUN_000214b0(&tmp2,msgbuf);
    slot = FUN_000217e4();
    if (slot == '\0') {
      fn = FUN_000218a4();
      len = val2;
      w2 = tmp2;
      kind = val;
      kind2 = tmp;
      errword2 = idx2;
      w1 = tag2;
      w0 = tag;
      FUN_00025704();
      return fn;
    }
    if (slot != '\x01') {
      fn3 = 0xb0d;
      key2 = s_XnuUpcalls_XnuUpcalls_Swift_swif_005cbff0;
      fn = 0xd000000000000038;
      slot3 = 0x80000000005cc000;
      fn2 = 0x21;
      goto LAB_00183ad8;
    }
    slot = CL4_VOID_U64(FUN_0018569c());
    w4 = slot;
    FUN_003698b0(&w4,0x669b78,&dat_004e6898);
    h4 = FUN_0036993c(0x669b78,&dat_004e6898,0,0);
    fn = h4._0_8_;
    h4.hi = (uint64_t)(slot);
    errword = val2;
    val4 = tmp2;
    msgbuf5 = val;
    msgbuf6 = tmp;
    ptr3 = idx2;
    val3 = tag2;
    h3 = tag;
    FUN_00025704();
  }
  else {
    slot3 = FUN_00019aac(0);
    h4 = FUN_0036993c(slot3,FUN_0065a550,0,0);
    fn = h4._0_8_;
    h4.hi = (uint64_t)(w3);
  }
  w7 = fn;
  FUN_0036b270(fn);
  slot3 = FUN_00002534(&dat_0064c260,&dat_004bbc30);
  slot2 = FUN_00365b6c(&tmp2,&w7,slot3,0x669b78,0);
  if (slot2 != 0) {
    FUN_0036b118(fn);
    FUN_0036993c(0x669208,0x668e68,0,0);
    FUN_00182080(&w4,*(uint32_t *)(&dat_004e6154 + (tmp2 & 0xff) * 4));
    if (w4 != '\x16') {
      *msgbuf4 = w4;
      FUN_0036986c();
      FUN_0036b118(w7);
      return tmp2 & 0xff;
    }
                    /* WARNING: Does not return */
    cl4_break(0x183a30);
  }
  FUN_0036b118(w7);
  w7 = 0;
  idx = 0xe000000000000000;
  FUN_0036b270(fn);
  FUN_002a4ab4(0x2f);
  thunk_FUN_002acbb8(0xd00000000000002d,0x80000000005cbfa0);
  tmp2 = fn;
  FUN_00205844(&tmp2,&w7,slot3,0x6756a8,0x66e1b8);
  fn3 = 0x10a;
  key2 = s_XnuUpcalls_XnuUpcalls_swift_005cbfa0;
  fn2 = 0x1b;
  fn = w7;
  slot3 = idx;
LAB_00183ad8:
                    /* WARNING: Subroutine does not return */
  FUN_001afa84(s_Fatal_error_005accd0,0xb,2,fn,slot3,key2,fn2,2,fn3,0);
}



/* FUN_00183b2c @ 0x00183b2c   (est. FUN_00183b2c)
 * Ghidra: void FUN_00183b2c(char *p1)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class B/None */
void FUN_00183b2c(char *p1)
{
  void *msgbuf4;
  int msgbuf5;
  uint64_t msgbuf6;
  char *msgbuf2;
  long err;
  char msgbuf3;
  uint8_t msgbuf;
  
  FUN_00187820(*p1 == '\x01',0);
  if (err != 0) {
    FUN_0036b270();
    msgbuf6 = FUN_00002534(&dat_0064c260,&dat_004bbc30);
    msgbuf5 = FUN_00365b6c(&stack_arg,&stack_arg,msgbuf6,0x669b78,0);
    if (msgbuf5 == 0) {
      FUN_0036b118(err);
      FUN_0036b270();
      FUN_002a4ab4(0x2f);
      thunk_FUN_002acbb8(0xd00000000000002d,0x80000000005cbfa0);
      FUN_00205844(&stack_arg,&stack_arg,msgbuf6,0x6756a8,0x66e1b8);
                    /* WARNING: Subroutine does not return */
      FUN_001afa84(s_Fatal_error_005accd0,0xb,2,0,0xe000000000000000,
                   s_XnuUpcalls_XnuUpcalls_swift_005cbfa0,0x1b,2,0x10a,0);
    }
    FUN_0036b118();
    FUN_0036993c(0x669208,0x668e68,0,0);
    FUN_00182080(&msgbuf3,*(uint32_t *)(&dat_004e6154 + (uint64_t)msgbuf * 4));
    if (msgbuf3 == '\x16') {
                    /* WARNING: Does not return */
      cl4_break(0x183c30);
    }
    *msgbuf2 = msgbuf3;
    FUN_0036986c();
    FUN_0036b118(err);
  }
  return;
}



/* FUN_00183ce4 @ 0x00183ce4   (est. FUN_00183ce4)
 * Ghidra: uint FUN_00183ce4(char *p1)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class B/None */
uint32_t FUN_00183ce4(char *p1)
{
  void *msgbuf4;
  uint32_t msgbuf6;
  int msgbuf5;
  uint64_t errword;
  char *msgbuf2;
  long err;
  char msgbuf3;
  uint8_t msgbuf;
  
  msgbuf6 = FUN_00187aac(*p1 == '\x01');
  if (err != 0) {
    FUN_0036b270();
    errword = FUN_00002534(&dat_0064c260,&dat_004bbc30);
    msgbuf5 = FUN_00365b6c(&stack_arg,&stack_arg,errword,0x669b78,0);
    if (msgbuf5 == 0) {
      FUN_0036b118(err);
      FUN_0036b270();
      FUN_002a4ab4(0x2f);
      thunk_FUN_002acbb8(0xd00000000000002d,0x80000000005cbfa0);
      FUN_00205844(&stack_arg,&stack_arg,errword,0x6756a8,0x66e1b8);
                    /* WARNING: Subroutine does not return */
      FUN_001afa84(s_Fatal_error_005accd0,0xb,2,0,0xe000000000000000,
                   s_XnuUpcalls_XnuUpcalls_swift_005cbfa0,0x1b,2,0x10a,0);
    }
    FUN_0036b118();
    FUN_0036993c(0x669208,0x668e68,0,0);
    FUN_00182080(&msgbuf3,*(uint32_t *)(&dat_004e6154 + (uint64_t)msgbuf * 4));
    if (msgbuf3 == '\x16') {
                    /* WARNING: Does not return */
      cl4_break(0x183dec);
    }
    *msgbuf2 = msgbuf3;
    FUN_0036986c();
    msgbuf6 = FUN_0036b118(err);
  }
  return msgbuf6 & 1;
}



/* FUN_00183ea0 @ 0x00183ea0   (est. thunk -> ?)
 * Ghidra: void FUN_00183ea0(undefined8 p1,undefined8 p2)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_00183ea0(uint64_t p1, uint64_t p2)
{
    ;
}



/* FUN_00183ea4 @ 0x00183ea4   (est. thunk -> ?)
 * Ghidra: void FUN_00183ea4(undefined8 p1,undefined8 p2)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_00183ea4(uint64_t p1, uint64_t p2)
{
    ;
}



/* FUN_00183ecc @ 0x00183ecc   (est. thunk -> ?)
 * Ghidra: void FUN_00183ecc(undefined8 p1,undefined8 p2)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_00183ecc(uint64_t p1, uint64_t p2)
{
    ;
}



/* FUN_00183ed0 @ 0x00183ed0   (est. thunk -> ?)
 * Ghidra: void FUN_00183ed0(undefined8 p1,undefined8 p2)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_00183ed0(uint64_t p1, uint64_t p2)
{
    ;
}



/* FUN_00183ef8 @ 0x00183ef8   (est. thunk -> ?)
 * Ghidra: void FUN_00183ef8(undefined8 p1,undefined8 p2)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_00183ef8(uint64_t p1, uint64_t p2)
{
    ;
}



/* FUN_00183efc @ 0x00183efc   (est. thunk -> ?)
 * Ghidra: void FUN_00183efc(undefined8 p1,undefined8 p2)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_00183efc(uint64_t p1, uint64_t p2)
{
    ;
}



/* FUN_00183f24 @ 0x00183f24   (est. thunk -> ?)
 * Ghidra: void FUN_00183f24(undefined8 p1,undefined8 p2)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_00183f24(uint64_t p1, uint64_t p2)
{
    ;
}



/* FUN_00183f28 @ 0x00183f28   (est. thunk -> ?)
 * Ghidra: void FUN_00183f28(undefined8 p1,undefined8 p2)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_00183f28(uint64_t p1, uint64_t p2)
{
    ;
}



/* FUN_00183f50 @ 0x00183f50   (est. FUN_00183f50)
 * Ghidra: void FUN_00183f50(void)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class B/None */
void FUN_00183f50(void)
{
  void *msgbuf3;
  int msgbuf4;
  uint64_t msgbuf5;
  uint8_t *msgbuf2;
  long err;
  uint8_t msgbuf;
  
  FUN_00188718(0);
  if (err != 0) {
    FUN_0036b270();
    msgbuf5 = FUN_00002534(&dat_0064c260,&dat_004bbc30);
    msgbuf4 = FUN_00365b6c(&stack_arg,&stack_arg,msgbuf5,0x669ae8,0);
    if (msgbuf4 == 0) {
      FUN_0036b118(err);
      FUN_0036b270();
      FUN_002a4ab4(0x2f);
      thunk_FUN_002acbb8(0xd00000000000002d,0x80000000005cbfa0);
      FUN_00205844(&stack_arg,&stack_arg,msgbuf5,0x6756a8,0x66e1b8);
                    /* WARNING: Subroutine does not return */
      FUN_001afa84(s_Fatal_error_005accd0,0xb,2,0,0xe000000000000000,
                   s_XnuUpcalls_XnuUpcalls_swift_005cbfa0,0x1b,2,0x10a,0);
    }
    FUN_0036b118();
    FUN_0036993c(FUN_00669298,0x668eb8,0,0);
    if (1 < msgbuf) {
                    /* WARNING: Does not return */
      cl4_break(0x18402c);
    }
    *msgbuf2 = msgbuf;
    FUN_0036986c();
    FUN_0036b118(err);
  }
  return;
}



/* FUN_001840e0 @ 0x001840e0   (est. thunk -> ?)
 * Ghidra: void FUN_001840e0(undefined8 p1,undefined8 p2)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_001840e0(uint64_t p1, uint64_t p2)
{
    ;
}



/* FUN_001840e4 @ 0x001840e4   (est. thunk -> ?)
 * Ghidra: void FUN_001840e4(undefined8 p1,undefined8 p2)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_001840e4(uint64_t p1, uint64_t p2)
{
    ;
}



/* FUN_0018410c @ 0x0018410c   (est. thunk -> ?)
 * Ghidra: void FUN_0018410c(undefined8 p1,undefined8 p2)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_0018410c(uint64_t p1, uint64_t p2)
{
    ;
}



/* FUN_00184110 @ 0x00184110   (est. thunk -> ?)
 * Ghidra: void FUN_00184110(undefined8 p1,undefined8 p2)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_00184110(uint64_t p1, uint64_t p2)
{
    ;
}



/* FUN_00184138 @ 0x00184138   (est. thunk -> ?)
 * Ghidra: void FUN_00184138(undefined8 p1,undefined8 p2)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_00184138(uint64_t p1, uint64_t p2)
{
    ;
}



/* FUN_0018413c @ 0x0018413c   (est. thunk -> ?)
 * Ghidra: void FUN_0018413c(undefined8 p1,undefined8 p2)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_0018413c(uint64_t p1, uint64_t p2)
{
    ;
}



/* FUN_00184164 @ 0x00184164   (est. FUN_00184164)
 * Ghidra: uint FUN_00184164(undefined8 p1,undefined8 p2,undefined1 *p3)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class B/None */
uint32_t FUN_00184164(uint64_t p1, uint64_t p2, uint64_t *p3)
{
  void *errword;
  uint32_t kind;
  int errword2;
  uint64_t kind2;
  uint8_t *msgbuf2;
  long err;
  uint32_t msgbuf6;
  uint32_t msgbuf5;
  uint32_t msgbuf4;
  uint32_t msgbuf3;
  uint8_t msgbuf;
  
  msgbuf6 = CONCAT31(EXTRACT13(msgbuf6),*p3);
  msgbuf5 = (uint32_t)*(uint64_t *)(p3 + 4);
  msgbuf4 = (uint32_t)((uint64_t)*(uint64_t *)(p3 + 4) >> 0x20);
  kind = FUN_00189108(p1,p2,&msgbuf6);
  if (err != 0) {
    msgbuf6 = (uint32_t)err;
    msgbuf5 = (uint32_t)((uint64_t)err >> 0x20);
    FUN_0036b270();
    kind2 = FUN_00002534(&dat_0064c260,&dat_004bbc30);
    errword2 = FUN_00365b6c(&stack_arg,&msgbuf6,kind2,0x669ae8,0);
    if (errword2 == 0) {
      FUN_0036b118(CONCAT44(msgbuf5,msgbuf6));
      msgbuf6 = 0;
      msgbuf5 = 0;
      msgbuf4 = 0;
      msgbuf3 = 0xe0000000;
      FUN_0036b270();
      FUN_002a4ab4(0x2f);
      thunk_FUN_002acbb8(0xd00000000000002d,0x80000000005cbfa0);
      FUN_00205844(&stack_arg,&msgbuf6,kind2,0x6756a8,0x66e1b8);
                    /* WARNING: Subroutine does not return */
      FUN_001afa84(s_Fatal_error_005accd0,0xb,2,CONCAT44(msgbuf5,msgbuf6),
                   CONCAT44(msgbuf3,msgbuf4),s_XnuUpcalls_XnuUpcalls_swift_005cbfa0,0x1b,2,0x10a
                   ,0);
    }
    FUN_0036b118();
    FUN_0036993c(FUN_00669298,0x668eb8,0,0);
    if (1 < msgbuf) {
                    /* WARNING: Does not return */
      cl4_break(0x184258);
    }
    *msgbuf2 = msgbuf;
    FUN_0036986c();
    kind = FUN_0036b118(CONCAT44(msgbuf5,msgbuf6));
  }
  return kind & 1;
}



/* FUN_0018430c @ 0x0018430c   (est. thunk -> ?)
 * Ghidra: void FUN_0018430c(undefined8 p1,undefined8 p2)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_0018430c(uint64_t p1, uint64_t p2)
{
    ;
}



/* FUN_00184310 @ 0x00184310   (est. thunk -> ?)
 * Ghidra: void FUN_00184310(undefined8 p1,undefined8 p2)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_00184310(uint64_t p1, uint64_t p2)
{
    ;
}



/* FUN_00184338 @ 0x00184338   (est. thunk -> ?)
 * Ghidra: void FUN_00184338(undefined8 p1)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_00184338(uint64_t p1)
{
    ;
}



/* FUN_0018433c @ 0x0018433c   (est. thunk -> ?)
 * Ghidra: void FUN_0018433c(undefined8 p1)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_0018433c(uint64_t p1)
{
    ;
}



/* FUN_00184364 @ 0x00184364   (est. thunk -> ?)
 * Ghidra: void FUN_00184364(undefined8 p1)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_00184364(uint64_t p1)
{
    ;
}



/* FUN_00184368 @ 0x00184368   (est. thunk -> ?)
 * Ghidra: void FUN_00184368(undefined8 p1)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_00184368(uint64_t p1)
{
    ;
}



/* FUN_00184390 @ 0x00184390   (est. FUN_00184390)
 * Ghidra: void FUN_00184390(undefined8 p1,code_fn_t p2)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class B/None */
void FUN_00184390(uint64_t p1, code_fn_t p2)
{
  void *msgbuf3;
  int msgbuf4;
  uint64_t msgbuf5;
  uint8_t *msgbuf2;
  long err;
  uint8_t msgbuf;
  
  (*p2)();
  if (err != 0) {
    FUN_0036b270();
    msgbuf5 = FUN_00002534(&dat_0064c260,&dat_004bbc30);
    msgbuf4 = FUN_00365b6c(&stack_arg,&stack_arg,msgbuf5,0x669ae8,0);
    if (msgbuf4 == 0) {
      FUN_0036b118(err);
      FUN_0036b270();
      FUN_002a4ab4(0x2f);
      thunk_FUN_002acbb8(0xd00000000000002d,0x80000000005cbfa0);
      FUN_00205844(&stack_arg,&stack_arg,msgbuf5,0x6756a8,0x66e1b8);
                    /* WARNING: Subroutine does not return */
      FUN_001afa84(s_Fatal_error_005accd0,0xb,2,0,0xe000000000000000,
                   s_XnuUpcalls_XnuUpcalls_swift_005cbfa0,0x1b,2,0x10a,0);
    }
    FUN_0036b118();
    FUN_0036993c(FUN_00669298,0x668eb8,0,0);
    if (1 < msgbuf) {
                    /* WARNING: Does not return */
      cl4_break(0x184470);
    }
    *msgbuf2 = msgbuf;
    FUN_0036986c();
    FUN_0036b118(err);
  }
  return;
}



/* FUN_00184524 @ 0x00184524   (est. thunk -> ?)
 * Ghidra: void FUN_00184524(undefined8 p1,undefined8 p2)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_00184524(uint64_t p1, uint64_t p2)
{
    ;
}



/* FUN_00184528 @ 0x00184528   (est. thunk -> ?)
 * Ghidra: void FUN_00184528(undefined8 p1,undefined8 p2)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_00184528(uint64_t p1, uint64_t p2)
{
    ;
}



/* FUN_00184550 @ 0x00184550   (est. thunk -> ?)
 * Ghidra: void FUN_00184550(undefined8 p1,undefined8 p2)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_00184550(uint64_t p1, uint64_t p2)
{
    ;
}



/* FUN_00184554 @ 0x00184554   (est. thunk -> ?)
 * Ghidra: void FUN_00184554(undefined8 p1,undefined8 p2)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_00184554(uint64_t p1, uint64_t p2)
{
    ;
}



/* FUN_0018457c @ 0x0018457c   (est. thunk -> ?)
 * Ghidra: void FUN_0018457c(undefined8 p1,undefined8 p2)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_0018457c(uint64_t p1, uint64_t p2)
{
    ;
}



/* FUN_00184580 @ 0x00184580   (est. thunk -> ?)
 * Ghidra: void FUN_00184580(undefined8 p1,undefined8 p2)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_00184580(uint64_t p1, uint64_t p2)
{
    ;
}



/* FUN_001845a8 @ 0x001845a8   (est. FUN_001845a8)
 * Ghidra: void FUN_001845a8(undefined8 p1,undefined8 p2,code_fn_t p3)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class B/None */
void FUN_001845a8(uint64_t p1, uint64_t p2, code_fn_t p3)
{
  void *msgbuf3;
  int msgbuf4;
  uint64_t msgbuf5;
  uint8_t *msgbuf2;
  long err;
  uint8_t msgbuf;
  
  (*p3)();
  if (err != 0) {
    FUN_0036b270();
    msgbuf5 = FUN_00002534(&dat_0064c260,&dat_004bbc30);
    msgbuf4 = FUN_00365b6c(&stack_arg,&stack_arg,msgbuf5,0x669ae8,0);
    if (msgbuf4 == 0) {
      FUN_0036b118(err);
      FUN_0036b270();
      FUN_002a4ab4(0x2f);
      thunk_FUN_002acbb8(0xd00000000000002d,0x80000000005cbfa0);
      FUN_00205844(&stack_arg,&stack_arg,msgbuf5,0x6756a8,0x66e1b8);
                    /* WARNING: Subroutine does not return */
      FUN_001afa84(s_Fatal_error_005accd0,0xb,2,0,0xe000000000000000,
                   s_XnuUpcalls_XnuUpcalls_swift_005cbfa0,0x1b,2,0x10a,0);
    }
    FUN_0036b118();
    FUN_0036993c(FUN_00669298,0x668eb8,0,0);
    if (1 < msgbuf) {
                    /* WARNING: Does not return */
      cl4_break(0x184688);
    }
    *msgbuf2 = msgbuf;
    FUN_0036986c();
    FUN_0036b118(err);
  }
  return;
}



/* FUN_0018473c @ 0x0018473c   (est. FUN_0018473c)
 * Ghidra: uint FUN_0018473c(void)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class B/None */
uint32_t FUN_0018473c(void)
{
  void *msgbuf3;
  uint32_t msgbuf5;
  int msgbuf4;
  uint64_t msgbuf6;
  uint8_t *msgbuf2;
  long err;
  uint8_t msgbuf;
  
  msgbuf5 = FUN_0018a37c(0,0);
  if (err != 0) {
    FUN_0036b270();
    msgbuf6 = FUN_00002534(&dat_0064c260,&dat_004bbc30);
    msgbuf4 = FUN_00365b6c(&stack_arg,&stack_arg,msgbuf6,0x669ae8,0);
    if (msgbuf4 == 0) {
      FUN_0036b118(err);
      FUN_0036b270();
      FUN_002a4ab4(0x2f);
      thunk_FUN_002acbb8(0xd00000000000002d,0x80000000005cbfa0);
      FUN_00205844(&stack_arg,&stack_arg,msgbuf6,0x6756a8,0x66e1b8);
                    /* WARNING: Subroutine does not return */
      FUN_001afa84(s_Fatal_error_005accd0,0xb,2,0,0xe000000000000000,
                   s_XnuUpcalls_XnuUpcalls_swift_005cbfa0,0x1b,2,0x10a,0);
    }
    FUN_0036b118();
    FUN_0036993c(FUN_00669298,0x668eb8,0,0);
    if (1 < msgbuf) {
                    /* WARNING: Does not return */
      cl4_break(0x18481c);
    }
    *msgbuf2 = msgbuf;
    FUN_0036986c();
    msgbuf5 = FUN_0036b118(err);
  }
  return msgbuf5 & 1;
}



/* FUN_001848d0 @ 0x001848d0   (est. FUN_001848d0)
 * Ghidra: uint FUN_001848d0(undefined8 p1,undefined8 p2,undefined8 p3,undefined8 p4)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class A/V1 */
uint32_t FUN_001848d0(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4)
{
  uint8_t tmp3;
  void *tag2;
  char tmp4;
  uint8_t ptr2;
  int ptr;
  uint64_t ptr3;
  uint64_t ptr4;
  uint8_t *msgbuf5;
  char *tmp;
  uint64_t h;
  long err;
  cl4_16_t tag;
  uint64_t tmp2;
  uint64_t val;
  uint64_t kind2;
  uint64_t idx2;
  uint64_t kind;
  uint64_t idx;
  uint64_t errword2;
  uint8_t cnt2;
  uint8_t msgbuf4 [56];
  uint64_t cnt;
  uint32_t len2;
  uint8_t msgbuf3 [56];
  uint8_t msgbuf2 [56];
  uint8_t msgbuf [56];
  uint64_t len;
  uint64_t errword;
  uint64_t msgbuf6;
  uint64_t w2;
  uint64_t w7;
  uint64_t w1;
  uint8_t w6;
  uint64_t w5;
  uint64_t w0;
  uint64_t val4;
  uint64_t val3;
  uint64_t w4;
  uint64_t val2;
  uint8_t w3;
  
  FUN_00025ebc(msgbuf3,0x24,0,&len2);
  if (err == 0) {
    thunk_FUN_00024068(msgbuf4);
    FUN_00023208(0xcda3c50dc7684b8c);
    FUN_00023208(p1);
    FUN_00023208(p2);
    FUN_000231f0(p3);
    FUN_00023208(p4);
    FUN_00022c48(msgbuf2);
    FUN_00025f44(msgbuf,msgbuf2,&len2);
    FUN_000214b0(&val,msgbuf);
    tmp4 = FUN_000217e4();
    if (tmp4 == '\0') {
      ptr4 = FUN_00021738();
      errword = kind2;
      len = val;
      w2 = kind;
      msgbuf6 = idx2;
      w1 = errword2;
      w7 = idx;
      w6 = cnt2;
      FUN_00025704();
      goto LAB_00184a70;
    }
    if (tmp4 != '\x01') {
      tmp2 = 0xbde;
      tmp = s_XnuUpcalls_XnuUpcalls_Swift_swif_005cbff0;
      ptr3 = 0xd00000000000003f;
      ptr4 = 0x80000000005cc040;
      h = 0x21;
      goto LAB_00184c7c;
    }
    ptr2 = CL4_VOID_U64(FUN_001857a8());
    cnt = CONCAT71(EXTRACT17(cnt),ptr2);
    FUN_003698b0(&cnt,0x669ae8,&dat_004e6878);
    tag = FUN_0036993c(0x669ae8,&dat_004e6878,0,0);
    ptr3 = tag._0_8_;
    tag.hi = (uint64_t)(ptr2);
    w0 = kind2;
    w5 = val;
    val3 = kind;
    val4 = idx2;
    val2 = errword2;
    w4 = idx;
    w3 = cnt2;
    FUN_00025704();
  }
  else {
    ptr3 = FUN_00019aac(0);
    tag = FUN_0036993c(ptr3,FUN_0065a550,0,0);
    ptr3 = tag._0_8_;
    tag.hi = (uint64_t)(len2);
  }
  val = ptr3;
  FUN_0036b270(ptr3);
  ptr4 = FUN_00002534(&dat_0064c260,&dat_004bbc30);
  ptr = FUN_00365b6c(&cnt,&val,ptr4,0x669ae8,0);
  if (ptr == 0) {
    FUN_0036b118(val);
    val = 0;
    kind2 = 0xe000000000000000;
    FUN_0036b270(ptr3);
    FUN_002a4ab4(0x2f);
    thunk_FUN_002acbb8(0xd00000000000002d,0x80000000005cbfa0);
    cnt = ptr3;
    FUN_00205844(&cnt,&val,ptr4,0x6756a8,0x66e1b8);
    tmp2 = 0x10a;
    tmp = s_XnuUpcalls_XnuUpcalls_swift_005cbfa0;
    h = 0x1b;
    ptr3 = val;
    ptr4 = kind2;
LAB_00184c7c:
                    /* WARNING: Subroutine does not return */
    FUN_001afa84(s_Fatal_error_005accd0,0xb,2,ptr3,ptr4,tmp,h,2,tmp2,0);
  }
  FUN_0036b118(ptr3);
  tmp3 = (uint8_t)cnt;
  FUN_0036993c(FUN_00669298,0x668eb8,0,0);
  if (1 < tmp3) {
                    /* WARNING: Does not return */
    cl4_break(0x184bd4);
  }
  *msgbuf5 = tmp3;
  FUN_0036986c();
  FUN_0036b118(val);
LAB_00184a70:
  return (uint32_t)ptr4 & 1;
}



/* FUN_00184cd4 @ 0x00184cd4   (est. FUN_00184cd4)
 * Ghidra: uint FUN_00184cd4(void)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class B/None */
uint32_t FUN_00184cd4(void)
{
  void *msgbuf3;
  uint32_t msgbuf5;
  int msgbuf4;
  uint64_t msgbuf6;
  uint8_t *msgbuf2;
  long err;
  uint8_t msgbuf;
  
  msgbuf5 = FUN_0018a608(0,0,0);
  if (err != 0) {
    FUN_0036b270();
    msgbuf6 = FUN_00002534(&dat_0064c260,&dat_004bbc30);
    msgbuf4 = FUN_00365b6c(&stack_arg,&stack_arg,msgbuf6,0x669ae8,0);
    if (msgbuf4 == 0) {
      FUN_0036b118(err);
      FUN_0036b270();
      FUN_002a4ab4(0x2f);
      thunk_FUN_002acbb8(0xd00000000000002d,0x80000000005cbfa0);
      FUN_00205844(&stack_arg,&stack_arg,msgbuf6,0x6756a8,0x66e1b8);
                    /* WARNING: Subroutine does not return */
      FUN_001afa84(s_Fatal_error_005accd0,0xb,2,0,0xe000000000000000,
                   s_XnuUpcalls_XnuUpcalls_swift_005cbfa0,0x1b,2,0x10a,0);
    }
    FUN_0036b118();
    FUN_0036993c(FUN_00669298,0x668eb8,0,0);
    if (1 < msgbuf) {
                    /* WARNING: Does not return */
      cl4_break(0x184db4);
    }
    *msgbuf2 = msgbuf;
    FUN_0036986c();
    msgbuf5 = FUN_0036b118(err);
  }
  return msgbuf5 & 1;
}



/* FUN_00184e68 @ 0x00184e68   (est. FUN_00184e68)
 * Ghidra: uint FUN_00184e68(void)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class B/None */
uint32_t FUN_00184e68(void)
{
  void *msgbuf3;
  uint32_t msgbuf5;
  int msgbuf4;
  uint64_t msgbuf6;
  uint8_t *msgbuf2;
  long err;
  uint8_t msgbuf;
  
  msgbuf5 = FUN_0018a8ac(0,0);
  if (err != 0) {
    FUN_0036b270();
    msgbuf6 = FUN_00002534(&dat_0064c260,&dat_004bbc30);
    msgbuf4 = FUN_00365b6c(&stack_arg,&stack_arg,msgbuf6,0x669ae8,0);
    if (msgbuf4 == 0) {
      FUN_0036b118(err);
      FUN_0036b270();
      FUN_002a4ab4(0x2f);
      thunk_FUN_002acbb8(0xd00000000000002d,0x80000000005cbfa0);
      FUN_00205844(&stack_arg,&stack_arg,msgbuf6,0x6756a8,0x66e1b8);
                    /* WARNING: Subroutine does not return */
      FUN_001afa84(s_Fatal_error_005accd0,0xb,2,0,0xe000000000000000,
                   s_XnuUpcalls_XnuUpcalls_swift_005cbfa0,0x1b,2,0x10a,0);
    }
    FUN_0036b118();
    FUN_0036993c(FUN_00669298,0x668eb8,0,0);
    if (1 < msgbuf) {
                    /* WARNING: Does not return */
      cl4_break(0x184f48);
    }
    *msgbuf2 = msgbuf;
    FUN_0036986c();
    msgbuf5 = FUN_0036b118(err);
  }
  return msgbuf5 & 1;
}



/* FUN_00184ffc @ 0x00184ffc   (est. FUN_00184ffc)
 * Ghidra: void FUN_00184ffc(void)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class B/None */
void FUN_00184ffc(void)
{
  int msgbuf;
  uint64_t msgbuf2;
  long err;
  
  FUN_0018ab38(0,0);
  if (err != 0) {
    FUN_0036b270();
    msgbuf2 = FUN_00002534(&dat_0064c260,&dat_004bbc30);
    msgbuf = FUN_00365b6c(msgbuf2,&stack_arg,msgbuf2,0x669a58,0);
    if (msgbuf == 0) {
      FUN_0036b118(err);
      FUN_0036b270();
      FUN_002a4ab4(0x2f);
      thunk_FUN_002acbb8(0xd00000000000002d,0x80000000005cbfa0);
      FUN_00205844(&stack_arg,&stack_arg,msgbuf2,0x6756a8,0x66e1b8);
                    /* WARNING: Subroutine does not return */
      FUN_001afa84(s_Fatal_error_005accd0,0xb,2,0,0xe000000000000000,
                   s_XnuUpcalls_XnuUpcalls_swift_005cbfa0,0x1b,2,0x10a,0);
    }
    FUN_0036b118();
    FUN_0036993c(0x669438,0x668f58,0,0);
    FUN_0036986c();
    FUN_0036b118(err);
  }
  return;
}



/* FUN_00185174 @ 0x00185174   (est. thunk -> ?)
 * Ghidra: void FUN_00185174(void)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_00185174(void)
{
    ;
}



/* FUN_00185198 @ 0x00185198   (est. thunk -> ?)
 * Ghidra: void FUN_00185198(void)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_00185198(void)
{
    ;
}



/* FUN_001851bc @ 0x001851bc   (est. thunk -> ?)
 * Ghidra: void FUN_001851bc(void)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_001851bc(void)
{
    ;
}



/* FUN_001851e0 @ 0x001851e0   (est. FUN_001851e0)
 * Ghidra: void FUN_001851e0(void)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class B/None */
void FUN_001851e0(void)
{
  void *msgbuf3;
  int msgbuf4;
  uint64_t msgbuf5;
  uint8_t *msgbuf2;
  long err;
  uint8_t msgbuf;
  
  FUN_0018b2f4(0,0);
  if (err != 0) {
    FUN_0036b270();
    msgbuf5 = FUN_00002534(&dat_0064c260,&dat_004bbc30);
    msgbuf4 = FUN_00365b6c(&stack_arg,&stack_arg,msgbuf5,0x6699c8,0);
    if (msgbuf4 == 0) {
      FUN_0036b118(err);
      FUN_0036b270();
      FUN_002a4ab4(0x2f);
      thunk_FUN_002acbb8(0xd00000000000002d,0x80000000005cbfa0);
      FUN_00205844(&stack_arg,&stack_arg,msgbuf5,0x6756a8,0x66e1b8);
                    /* WARNING: Subroutine does not return */
      FUN_001afa84(s_Fatal_error_005accd0,0xb,2,0,0xe000000000000000,
                   s_XnuUpcalls_XnuUpcalls_swift_005cbfa0,0x1b,2,0x10a,0);
    }
    FUN_0036b118();
    FUN_0036993c(0x6694c8,0x668fa8,0,0);
    if (1 < msgbuf) {
                    /* WARNING: Does not return */
      cl4_break(0x1852bc);
    }
    *msgbuf2 = msgbuf;
    FUN_0036986c();
    FUN_0036b118(err);
  }
  return;
}



/* FUN_00185370 @ 0x00185370   (est. FUN_00185370)
 * Ghidra: void FUN_00185370(void)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class B/None */
void FUN_00185370(void)
{
  void *msgbuf3;
  int msgbuf4;
  uint64_t msgbuf5;
  uint8_t *msgbuf2;
  long err;
  uint8_t msgbuf;
  
  FUN_0018b5c4(0);
  if (err != 0) {
    FUN_0036b270();
    msgbuf5 = FUN_00002534(&dat_0064c260,&dat_004bbc30);
    msgbuf4 = FUN_00365b6c(&stack_arg,&stack_arg,msgbuf5,0x6699c8,0);
    if (msgbuf4 == 0) {
      FUN_0036b118(err);
      FUN_0036b270();
      FUN_002a4ab4(0x2f);
      thunk_FUN_002acbb8(0xd00000000000002d,0x80000000005cbfa0);
      FUN_00205844(&stack_arg,&stack_arg,msgbuf5,0x6756a8,0x66e1b8);
                    /* WARNING: Subroutine does not return */
      FUN_001afa84(s_Fatal_error_005accd0,0xb,2,0,0xe000000000000000,
                   s_XnuUpcalls_XnuUpcalls_swift_005cbfa0,0x1b,2,0x10a,0);
    }
    FUN_0036b118();
    FUN_0036993c(0x6694c8,0x668fa8,0,0);
    if (1 < msgbuf) {
                    /* WARNING: Does not return */
      cl4_break(0x18544c);
    }
    *msgbuf2 = msgbuf;
    FUN_0036986c();
    FUN_0036b118(err);
  }
  return;
}



/* FUN_00185500 @ 0x00185500   (est. FUN_00185500)
 * Ghidra: void FUN_00185500(void)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class B/None */
void FUN_00185500(void)
{
  void *msgbuf3;
  int msgbuf4;
  uint64_t msgbuf5;
  uint8_t *msgbuf2;
  long err;
  uint8_t msgbuf;
  
  FUN_0018b830(&stack_arg,0);
  if (err != 0) {
    FUN_0036b270();
    msgbuf5 = FUN_00002534(&dat_0064c260,&dat_004bbc30);
    msgbuf4 = FUN_00365b6c(&stack_arg,&stack_arg,msgbuf5,0x6699c8,0);
    if (msgbuf4 == 0) {
      FUN_0036b118(err);
      FUN_0036b270();
      FUN_002a4ab4(0x2f);
      thunk_FUN_002acbb8(0xd00000000000002d,0x80000000005cbfa0);
      FUN_00205844(&stack_arg,&stack_arg,msgbuf5,0x6756a8,0x66e1b8);
                    /* WARNING: Subroutine does not return */
      FUN_001afa84(s_Fatal_error_005accd0,0xb,2,0,0xe000000000000000,
                   s_XnuUpcalls_XnuUpcalls_swift_005cbfa0,0x1b,2,0x10a,0);
    }
    FUN_0036b118();
    FUN_0036993c(0x6694c8,0x668fa8,0,0);
    if (1 < msgbuf) {
                    /* WARNING: Does not return */
      cl4_break(0x1855e8);
    }
    *msgbuf2 = msgbuf;
    FUN_0036986c();
    FUN_0036b118(err);
  }
  return;
}



/* FUN_0018569c @ 0x0018569c   (est. FUN_0018569c)
 * Ghidra: void FUN_0018569c(void)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class X/None */
void FUN_0018569c(void)
{
  char msgbuf3;
  code_fn_t msgbuf2;
  uint64_t msgbuf;
  
  FUN_000218a4();
  msgbuf3 = FUN_0018deb8(0);
  if (msgbuf3 != '\x16') {
    return;
  }
  FUN_002a4ab4(0x2c);
  FUN_003a25d4(0xe000000000000000);
  msgbuf2 = (code_fn_t)FUN_00027724(0x671298);
  (*msgbuf2)(0x6776f0,0x671298);
  thunk_FUN_002acbb8();
  FUN_003a25d4(msgbuf);
                    /* WARNING: Subroutine does not return */
  FUN_001afa84(s_Fatal_error_005accd0,0xb,2,0xd00000000000002a,0x80000000005cc0b0,
               s_XnuUpcalls_XnuUpcalls_Swift_swif_005cbff0,0x21,2,0xa5e,0);
}



/* FUN_001857a8 @ 0x001857a8   (est. FUN_001857a8)
 * Ghidra: void FUN_001857a8(void)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class X/None */
void FUN_001857a8(void)
{
  uint32_t msgbuf3;
  code_fn_t msgbuf2;
  uint64_t msgbuf;
  
  msgbuf3 = FUN_000218a4();
  if (msgbuf3 < 2) {
    return;
  }
  FUN_002a4ab4(0x2a);
  FUN_003a25d4(0xe000000000000000);
  msgbuf2 = (code_fn_t)FUN_00027724(0x671298);
  (*msgbuf2)(0x6776f0,0x671298);
  thunk_FUN_002acbb8();
  FUN_003a25d4(msgbuf);
                    /* WARNING: Subroutine does not return */
  FUN_001afa84(s_Fatal_error_005accd0,0xb,2,0xd000000000000028,0x80000000005cc080,
               s_XnuUpcalls_XnuUpcalls_Swift_swif_005cbff0,0x21,2,0xa66,0);
}



/* FUN_00185b20 @ 0x00185b20   (est. FUN_00185b20)
 * Ghidra: undefined8 * FUN_00185b20(undefined8 *p1,undefined8 *p2)
 * Small upcall / message-register marshalling helper. Confidence: medium
 * Notes: part of the XNU upcall layer. */
uint64_t *cl4_copy_word(uint64_t *dst, uint64_t *src)
{
    /* Copies the first word of src into dst, allocates (FUN_0036b270), returns dst. */
    *dst = *src;
    FUN_0036b270();
    return dst;
}


/* FUN_00185b58 @ 0x00185b58   (est. FUN_00185b58)
 * Ghidra: undefined8 * FUN_00185b58(undefined8 *p1,undefined8 *p2)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class X/None */
uint64_t * FUN_00185b58(uint64_t *p1, uint64_t *p2)
{
  uint64_t msgbuf;
  
  msgbuf = *p1;
  *p1 = *p2;
  FUN_0036b270();
  FUN_0036b118(msgbuf);
  return p1;
}



/* FUN_00185b94 @ 0x00185b94   (est. FUN_00185b94)
 * Ghidra: undefined8 * FUN_00185b94(undefined8 *p1,undefined8 *p2)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class X/None */
uint64_t * FUN_00185b94(uint64_t *p1, uint64_t *p2)
{
  uint64_t msgbuf;
  
  msgbuf = *p1;
  *p1 = *p2;
  FUN_0036b118(msgbuf);
  return p1;
}



/* FUN_00185c60 @ 0x00185c60   (est. FUN_00185c60)
 * Ghidra: undefined1  [16] FUN_00185c60(void)
 * Small upcall / message-register marshalling helper. Confidence: medium
 * Notes: part of the XNU upcall layer. */
cl4_16_t FUN_00185c60(void)
{
    /* Returns the 16-uint8_t tag at 0x655078 (a class/selector constant). */
    return *(cl4_16_t *)0x655078;
}


/* FUN_00185cbc @ 0x00185cbc   (est. thunk -> ?)
 * Ghidra: void FUN_00185cbc(undefined8 p1)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_00185cbc(uint64_t p1)
{
    ;
}



/* FUN_00185ce4 @ 0x00185ce4   (est. FUN_00185ce4)
 * Ghidra: undefined8 FUN_00185ce4(long p1)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class A/V1LONG */
uint64_t FUN_00185ce4(long p1)
{
  long fn;
  code_fn_t key2;
  bool slot2;
  char slot3;
  uint8_t fn3;
  uint64_t st;
  uint32_t *msgbuf5;
  uint64_t msgbuf;
  uint64_t st2;
  long fn2;
  uint64_t r;
  long err;
  uint64_t ret;
  cl4_16_t key;
  uint64_t slot;
  uint64_t tag;
  uint64_t val;
  uint64_t idx2;
  uint64_t idx;
  uint64_t w7;
  uint64_t cnt2;
  uint8_t w6;
  long w5;
  uint64_t w4;
  uint64_t cnt;
  uint64_t len2;
  uint64_t len;
  uint64_t w3;
  uint64_t kind2;
  uint8_t w2;
  uint32_t w1;
  uint8_t msgbuf4 [56];
  uint8_t msgbuf3 [56];
  uint8_t msgbuf2 [56];
  uint64_t w0;
  uint64_t kind;
  uint64_t errword2;
  uint64_t errword;
  uint64_t val4;
  uint64_t msgbuf6;
  uint8_t val3;
  uint64_t val2;
  uint64_t ptr3;
  uint64_t ptr2;
  uint64_t ptr;
  uint64_t h4;
  uint64_t tmp4;
  uint8_t h3;
  uint64_t h2;
  uint64_t tmp3;
  uint64_t tmp2;
  uint64_t tmp;
  uint64_t h;
  uint64_t tag2;
  uint8_t ptr4;
  
  r = 0;
  while ((r != 0x20 &&
         (slot2 = *(uint64_t *)(p1 + 0x10) <= r, r != *(uint64_t *)(p1 + 0x10)))) {
    r = r + 1;
    if (slot2) {
                    /* WARNING: Does not return */
      cl4_break(0x185d28);
    }
  }
  FUN_00025ebc(msgbuf4,r + 8,0,&w1);
  if (err == 0) {
    thunk_FUN_00024068(&w4);
    FUN_00023208(0x80c13727a815903c);
    fn2 = *(long *)(p1 + 0x10);
    if (fn2 != 0x20) {
      tag = 0;
      val = 0xe000000000000000;
      FUN_002a4ab4(0x3b);
      thunk_FUN_002acbb8(0xd000000000000010,0x80000000005ccb40);
      thunk_FUN_002acbb8(0xd000000000000037,0x80000000005cc150);
      w5 = fn2;
      key2 = (code_fn_t)FUN_00027724(0x6720e0);
      (*key2)(0x677880,0x6720e0);
      thunk_FUN_002acbb8();
      FUN_003a25d4(msgbuf);
      slot = 0x3e4;
      st = tag;
      st2 = val;
LAB_0018603c:
                    /* WARNING: Subroutine does not return */
      FUN_001afa84(s_Fatal_error_005accd0,0xb,2,st,st2,
                   s_XnuUpcalls_XnuUpcalls_Swift_swif_005cbff0,0x21,2,slot,0);
    }
    fn2 = 0;
    do {
      fn = fn2 + 1;
      FUN_000230f8(*(uint8_t *)(p1 + 0x20 + fn2));
      fn2 = fn;
    } while (fn != 0x20);
    tmp3 = cnt;
    h2 = w4;
    tmp = len;
    tmp2 = len2;
    tag2 = kind2;
    h = w3;
    ptr4 = w2;
    FUN_00022c48(msgbuf3);
    FUN_00025f44(msgbuf2,msgbuf3,&w1);
    FUN_000214b0(&tag,msgbuf2);
    slot3 = FUN_000217e4();
    if (slot3 == '\0') {
      ret = FUN_00021904();
      kind = val;
      w0 = tag;
      errword = idx;
      errword2 = idx2;
      msgbuf6 = cnt2;
      val4 = w7;
      val3 = w6;
      FUN_00025704();
    }
    else {
      if (slot3 != '\x01') {
        slot = 0xab5;
        st = 0xd000000000000035;
        st2 = 0x80000000005ccb60;
        goto LAB_0018603c;
      }
      fn3 = CL4_VOID_U64(FUN_0018569c());
      w5 = CONCAT71(EXTRACT17(w5),fn3);
      FUN_003698b0(&w5,0x669b78,&dat_004e6898);
      key = FUN_0036993c(0x669b78,&dat_004e6898,0,0);
      ret = key._0_8_;
      key.hi = (uint64_t)(fn3);
      ptr3 = val;
      val2 = tag;
      ptr = idx;
      ptr2 = idx2;
      tmp4 = cnt2;
      h4 = w7;
      h3 = w6;
      FUN_00025704();
    }
  }
  else {
    st = FUN_00019aac(0);
    FUN_0036993c(st,FUN_0065a550,0,0);
    *msgbuf5 = w1;
  }
  return ret;
}



/* FUN_00186094 @ 0x00186094   (est. FUN_00186094)
 * Ghidra: undefined8 FUN_00186094(undefined1 p1,undefined8 p2,long p3)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class A/V1LONG */
uint64_t FUN_00186094(uint8_t p1, uint64_t p2, long p3)
{
  long fn;
  code_fn_t key2;
  bool slot2;
  char slot3;
  uint8_t fn3;
  uint64_t st;
  uint32_t *msgbuf5;
  uint64_t msgbuf;
  uint64_t st2;
  uint64_t r;
  long err;
  uint64_t ret;
  long fn2;
  cl4_16_t key;
  uint64_t slot;
  uint64_t tag2;
  uint64_t val3;
  uint64_t val2;
  uint64_t val;
  uint64_t tag;
  uint64_t idx2;
  uint8_t w7;
  long w6;
  uint64_t w5;
  uint64_t idx;
  uint64_t cnt2;
  uint64_t cnt;
  uint64_t w4;
  uint64_t len2;
  uint8_t w3;
  uint8_t msgbuf4 [56];
  uint8_t msgbuf3 [56];
  uint8_t msgbuf2 [56];
  uint64_t w2;
  uint64_t len;
  uint64_t kind2;
  uint64_t kind;
  uint64_t w1;
  uint64_t errword2;
  uint8_t w0;
  uint64_t val4;
  uint64_t errword;
  uint64_t msgbuf6;
  uint64_t ptr2;
  uint64_t h4;
  uint64_t ptr;
  uint8_t h3;
  uint64_t h2;
  uint64_t tmp4;
  uint64_t tmp3;
  uint64_t tmp2;
  uint64_t h;
  uint64_t tmp;
  uint8_t ptr4;
  uint32_t ptr3;
  
  r = 0;
  while ((r != 0x100 &&
         (slot2 = *(uint64_t *)(p3 + 0x10) <= r, r != *(uint64_t *)(p3 + 0x10)))) {
    r = r + 1;
    if (slot2) {
                    /* WARNING: Does not return */
      cl4_break(0x1860e4);
    }
  }
  FUN_00025ebc(msgbuf4,r + 0x14,0,&ptr3);
  if (err == 0) {
    thunk_FUN_00024068(&w5);
    FUN_00023208(0x737378f3f75b6fe9);
    FUN_000231f0(p1);
    FUN_00023208(p2);
    fn2 = *(long *)(p3 + 0x10);
    if (fn2 != 0x100) {
      tag2 = 0;
      val3 = 0xe000000000000000;
      FUN_002a4ab4(0x3c);
      thunk_FUN_002acbb8(0xd000000000000018,0x80000000005ccae0);
      thunk_FUN_002acbb8(0xd000000000000038,0x80000000005cc940);
      w6 = fn2;
      key2 = (code_fn_t)FUN_00027724(0x6720e0);
      (*key2)(0x677880,0x6720e0);
      thunk_FUN_002acbb8();
      FUN_003a25d4(msgbuf);
      slot = 0x3fa;
      st = tag2;
      st2 = val3;
LAB_0018640c:
                    /* WARNING: Subroutine does not return */
      FUN_001afa84(s_Fatal_error_005accd0,0xb,2,st,st2,
                   s_XnuUpcalls_XnuUpcalls_Swift_swif_005cbff0,0x21,2,slot,0);
    }
    fn2 = 0;
    do {
      fn = fn2 + 1;
      FUN_000230f8(*(uint8_t *)(p3 + 0x20 + fn2));
      fn2 = fn;
    } while (fn != 0x100);
    tmp4 = idx;
    h2 = w5;
    tmp2 = cnt;
    tmp3 = cnt2;
    tmp = len2;
    h = w4;
    ptr4 = w3;
    FUN_00022c48(msgbuf3);
    FUN_00025f44(msgbuf2,msgbuf3,&ptr3);
    FUN_000214b0(&tag2,msgbuf2);
    slot3 = FUN_000217e4();
    if (slot3 == '\0') {
      ret = FUN_00021904();
      len = val3;
      w2 = tag2;
      kind = val;
      kind2 = val2;
      errword2 = idx2;
      w1 = tag;
      w0 = w7;
      FUN_00025704();
    }
    else {
      if (slot3 != '\x01') {
        slot = 0xac0;
        st = 0xd000000000000035;
        st2 = 0x80000000005ccb00;
        goto LAB_0018640c;
      }
      fn3 = CL4_VOID_U64(FUN_0018569c());
      w6 = CONCAT71(EXTRACT17(w6),fn3);
      FUN_003698b0(&w6,0x669b78,&dat_004e6898);
      key = FUN_0036993c(0x669b78,&dat_004e6898,0,0);
      ret = key._0_8_;
      key.hi = (uint64_t)(fn3);
      errword = val3;
      val4 = tag2;
      ptr2 = val;
      msgbuf6 = val2;
      ptr = idx2;
      h4 = tag;
      h3 = w7;
      FUN_00025704();
    }
  }
  else {
    st = FUN_00019aac(0);
    FUN_0036993c(st,FUN_0065a550,0,0);
    *msgbuf5 = ptr3;
  }
  return ret;
}



/* FUN_00186460 @ 0x00186460   (est. FUN_00186460)
 * Ghidra: void FUN_00186460(undefined1 p1,undefined8 p2)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class A/V1 */
void FUN_00186460(uint8_t p1, uint64_t p2)
{
  char tag2;
  uint8_t tmp;
  uint64_t tmp2;
  uint32_t *msgbuf6;
  uint8_t *msgbuf;
  long err;
  uint8_t idx2;
  uint64_t idx;
  uint64_t kind;
  uint64_t cnt2;
  uint64_t errword2;
  uint64_t cnt;
  uint64_t errword;
  uint8_t len2;
  uint8_t msgbuf5 [52];
  uint32_t len;
  uint8_t msgbuf4 [56];
  uint8_t msgbuf3 [56];
  uint8_t msgbuf2 [56];
  uint64_t kind2;
  uint64_t w3;
  uint64_t w2;
  uint64_t w1;
  uint64_t tag;
  uint64_t w0;
  uint8_t w7;
  uint64_t w6;
  uint64_t val4;
  uint64_t val3;
  uint64_t val2;
  uint64_t w5;
  uint64_t val;
  uint8_t w4;
  
  FUN_00025ebc(msgbuf4,0x14,0,&len);
  if (err == 0) {
    thunk_FUN_00024068(msgbuf5);
    FUN_00023208(0xe3314a4fdcaf503d);
    FUN_000231f0(p1);
    FUN_00023208(p2);
    FUN_00022c48(msgbuf3);
    FUN_00025f44(msgbuf2,msgbuf3,&len);
    FUN_000214b0(&idx,msgbuf2);
    tag2 = FUN_000217e4();
    if (tag2 == '\0') {
      w3 = kind;
      kind2 = idx;
      w1 = errword2;
      w2 = cnt2;
      w0 = errword;
      tag = cnt;
      w7 = len2;
      FUN_00025704();
    }
    else {
      if (tag2 != '\x01') {
                    /* WARNING: Subroutine does not return */
        FUN_001afa84(s_Fatal_error_005accd0,0xb,2,0xd000000000000036,0x80000000005ccaa0,
                     s_XnuUpcalls_XnuUpcalls_Swift_swif_005cbff0,0x21,2,0xacb,0);
      }
      tmp = CL4_VOID_U64(FUN_0018569c());
      idx2 = tmp;
      FUN_003698b0(&idx2,0x669b78,&dat_004e6898);
      FUN_0036993c(0x669b78,&dat_004e6898,0,0);
      *msgbuf = tmp;
      val4 = kind;
      w6 = idx;
      val2 = errword2;
      val3 = cnt2;
      val = errword;
      w5 = cnt;
      w4 = len2;
      FUN_00025704();
    }
  }
  else {
    tmp2 = FUN_00019aac(0);
    FUN_0036993c(tmp2,FUN_0065a550,0,0);
    *msgbuf6 = len;
  }
  return;
}



/* FUN_001866dc @ 0x001866dc   (est. FUN_001866dc)
 * Ghidra: undefined8 FUN_001866dc(undefined1 p1,undefined8 p2,long p3)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class A/V1LONG */
uint64_t FUN_001866dc(uint8_t p1, uint64_t p2, long p3)
{
  long fn;
  code_fn_t key2;
  bool slot2;
  char slot3;
  uint8_t fn3;
  uint64_t st;
  uint32_t *msgbuf5;
  uint64_t msgbuf;
  uint64_t st2;
  uint64_t r;
  long err;
  uint64_t ret;
  long fn2;
  cl4_16_t key;
  uint64_t slot;
  uint64_t tag2;
  uint64_t val3;
  uint64_t val2;
  uint64_t val;
  uint64_t tag;
  uint64_t idx2;
  uint8_t w7;
  long w6;
  uint64_t w5;
  uint64_t idx;
  uint64_t cnt2;
  uint64_t cnt;
  uint64_t w4;
  uint64_t len2;
  uint8_t w3;
  uint8_t msgbuf4 [56];
  uint8_t msgbuf3 [56];
  uint8_t msgbuf2 [56];
  uint64_t w2;
  uint64_t len;
  uint64_t kind2;
  uint64_t kind;
  uint64_t w1;
  uint64_t errword2;
  uint8_t w0;
  uint64_t val4;
  uint64_t errword;
  uint64_t msgbuf6;
  uint64_t ptr2;
  uint64_t h4;
  uint64_t ptr;
  uint8_t h3;
  uint64_t h2;
  uint64_t tmp4;
  uint64_t tmp3;
  uint64_t tmp2;
  uint64_t h;
  uint64_t tmp;
  uint8_t ptr4;
  uint32_t ptr3;
  
  r = 0;
  while ((r != 0x100 &&
         (slot2 = *(uint64_t *)(p3 + 0x10) <= r, r != *(uint64_t *)(p3 + 0x10)))) {
    r = r + 1;
    if (slot2) {
                    /* WARNING: Does not return */
      cl4_break(0x18672c);
    }
  }
  FUN_00025ebc(msgbuf4,r + 0x14,0,&ptr3);
  if (err == 0) {
    thunk_FUN_00024068(&w5);
    FUN_00023208(0xdb68f05ae3a6a84c);
    FUN_000231f0(p1);
    FUN_00023208(p2);
    fn2 = *(long *)(p3 + 0x10);
    if (fn2 != 0x100) {
      tag2 = 0;
      val3 = 0xe000000000000000;
      FUN_002a4ab4(0x3c);
      thunk_FUN_002acbb8(0xd00000000000001a,0x80000000005cca40);
      thunk_FUN_002acbb8(0xd000000000000038,0x80000000005cc940);
      w6 = fn2;
      key2 = (code_fn_t)FUN_00027724(0x6720e0);
      (*key2)(0x677880,0x6720e0);
      thunk_FUN_002acbb8();
      FUN_003a25d4(msgbuf);
      slot = 0x41c;
      st = tag2;
      st2 = val3;
LAB_00186a54:
                    /* WARNING: Subroutine does not return */
      FUN_001afa84(s_Fatal_error_005accd0,0xb,2,st,st2,
                   s_XnuUpcalls_XnuUpcalls_Swift_swif_005cbff0,0x21,2,slot,0);
    }
    fn2 = 0;
    do {
      fn = fn2 + 1;
      FUN_000230f8(*(uint8_t *)(p3 + 0x20 + fn2));
      fn2 = fn;
    } while (fn != 0x100);
    tmp4 = idx;
    h2 = w5;
    tmp2 = cnt;
    tmp3 = cnt2;
    tmp = len2;
    h = w4;
    ptr4 = w3;
    FUN_00022c48(msgbuf3);
    FUN_00025f44(msgbuf2,msgbuf3,&ptr3);
    FUN_000214b0(&tag2,msgbuf2);
    slot3 = FUN_000217e4();
    if (slot3 == '\0') {
      ret = FUN_00021904();
      len = val3;
      w2 = tag2;
      kind = val;
      kind2 = val2;
      errword2 = idx2;
      w1 = tag;
      w0 = w7;
      FUN_00025704();
    }
    else {
      if (slot3 != '\x01') {
        slot = 0xad6;
        st = 0xd000000000000037;
        st2 = 0x80000000005cca60;
        goto LAB_00186a54;
      }
      fn3 = CL4_VOID_U64(FUN_0018569c());
      w6 = CONCAT71(EXTRACT17(w6),fn3);
      FUN_003698b0(&w6,0x669b78,&dat_004e6898);
      key = FUN_0036993c(0x669b78,&dat_004e6898,0,0);
      ret = key._0_8_;
      key.hi = (uint64_t)(fn3);
      errword = val3;
      val4 = tag2;
      ptr2 = val;
      msgbuf6 = val2;
      ptr = idx2;
      h4 = tag;
      h3 = w7;
      FUN_00025704();
    }
  }
  else {
    st = FUN_00019aac(0);
    FUN_0036993c(st,FUN_0065a550,0,0);
    *msgbuf5 = ptr3;
  }
  return ret;
}



/* FUN_00186aa8 @ 0x00186aa8   (est. FUN_00186aa8)
 * Ghidra: void FUN_00186aa8(undefined1 p1,undefined8 p2,undefined8 *p3)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class A/V1 */
void FUN_00186aa8(uint8_t p1, uint64_t p2, uint64_t *p3)
{
  uint64_t h4;
  void *h;
  char h2;
  uint8_t key;
  long h3;
  uint64_t key2;
  uint32_t *msgbuf5;
  uint8_t *msgbuf;
  long err;
  uint64_t slot;
  uint8_t tmp;
  uint64_t tag2;
  uint64_t val;
  uint64_t tag;
  uint64_t idx2;
  uint64_t w7;
  uint64_t idx;
  uint8_t w6;
  uint64_t w5;
  uint64_t cnt2;
  uint64_t w4;
  uint64_t cnt;
  uint64_t w3;
  uint64_t len2;
  uint8_t w2;
  uint32_t w1;
  uint8_t msgbuf4 [56];
  uint8_t msgbuf3 [56];
  uint8_t msgbuf2 [56];
  uint64_t w0;
  uint64_t len;
  uint64_t kind2;
  uint64_t val4;
  uint64_t kind;
  uint64_t errword2;
  uint64_t errword;
  uint64_t val3;
  uint64_t msgbuf6;
  uint8_t val2;
  uint64_t ptr4;
  uint64_t ptr;
  uint64_t tmp4;
  uint64_t tmp3;
  uint64_t ptr3;
  uint64_t tmp2;
  uint8_t ptr2;
  
  key2 = *p3;
  h4 = p3[1];
  slot = p3[2];
  w5 = key2;
  cnt2 = h4;
  w4 = slot;
  h3 = FUN_00026754(&w5,0x6690e0,&dat_006695e0);
  if (SCARRY8(h3,0x14)) {
                    /* WARNING: Does not return */
    cl4_break(0x186df0);
  }
  FUN_00025ebc(msgbuf4,h3 + 0x14,0,&w1);
  if (err == 0) {
    thunk_FUN_00024068(&w5);
    FUN_00023208(0x6cb873bde012be5d);
    FUN_000231f0(p1);
    FUN_00023208(p2);
    tag2 = key2;
    val = h4;
    tag = slot;
    FUN_000267d4(&tag2,0x65a870,0x6690e0,0x65a798,&dat_006695e0);
    ptr = cnt2;
    ptr4 = w5;
    tmp3 = cnt;
    tmp4 = w4;
    tmp2 = len2;
    ptr3 = w3;
    ptr2 = w2;
    FUN_00022c48(msgbuf3);
    FUN_00025f44(msgbuf2,msgbuf3,&w1);
    FUN_000214b0(&tag2,msgbuf2);
    h2 = FUN_000217e4();
    if (h2 == '\0') {
      len = val;
      w0 = tag2;
      kind2 = tag;
      FUN_00025704();
    }
    else {
      if (h2 != '\x01') {
                    /* WARNING: Subroutine does not return */
        FUN_001afa84(s_Fatal_error_005accd0,0xb,2,0xd000000000000035,0x80000000005cca00,
                     s_XnuUpcalls_XnuUpcalls_Swift_swif_005cbff0,0x21,2,0xae1,0);
      }
      key = CL4_VOID_U64(FUN_0018569c());
      tmp = key;
      FUN_003698b0(&tmp,0x669b78,&dat_004e6898);
      FUN_0036993c(0x669b78,&dat_004e6898,0,0);
      *msgbuf = key;
      kind = val;
      val4 = tag2;
      errword = idx2;
      errword2 = tag;
      msgbuf6 = idx;
      val3 = w7;
      val2 = w6;
      FUN_00025704();
    }
  }
  else {
    key2 = FUN_00019aac(0);
    FUN_0036993c(key2,FUN_0065a550,0,0);
    *msgbuf5 = w1;
  }
  return;
}



/* FUN_00186e3c @ 0x00186e3c   (est. FUN_00186e3c)
 * Ghidra: void FUN_00186e3c(undefined1 p1,undefined8 p2,undefined8 *p3)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class A/V1 */
void FUN_00186e3c(uint8_t p1, uint64_t p2, uint64_t *p3)
{
  uint64_t h4;
  void *h;
  char h2;
  uint8_t key;
  long h3;
  uint64_t key2;
  uint32_t *msgbuf5;
  uint8_t *msgbuf;
  long err;
  uint64_t slot;
  uint8_t tmp;
  uint64_t tag2;
  uint64_t val;
  uint64_t tag;
  uint64_t idx2;
  uint64_t w7;
  uint64_t idx;
  uint8_t w6;
  uint64_t w5;
  uint64_t cnt2;
  uint64_t w4;
  uint64_t cnt;
  uint64_t w3;
  uint64_t len2;
  uint8_t w2;
  uint32_t w1;
  uint8_t msgbuf4 [56];
  uint8_t msgbuf3 [56];
  uint8_t msgbuf2 [56];
  uint64_t w0;
  uint64_t len;
  uint64_t kind2;
  uint64_t val4;
  uint64_t kind;
  uint64_t errword2;
  uint64_t errword;
  uint64_t val3;
  uint64_t msgbuf6;
  uint8_t val2;
  uint64_t ptr4;
  uint64_t ptr;
  uint64_t tmp4;
  uint64_t tmp3;
  uint64_t ptr3;
  uint64_t tmp2;
  uint8_t ptr2;
  
  key2 = *p3;
  h4 = p3[1];
  slot = p3[2];
  w5 = key2;
  cnt2 = h4;
  w4 = slot;
  h3 = FUN_00026754(&w5,0x6690e0,&dat_006695e0);
  if (SCARRY8(h3,0x14)) {
                    /* WARNING: Does not return */
    cl4_break(0x187184);
  }
  FUN_00025ebc(msgbuf4,h3 + 0x14,0,&w1);
  if (err == 0) {
    thunk_FUN_00024068(&w5);
    FUN_00023208(0xf1554e73609733dd);
    FUN_000231f0(p1);
    FUN_00023208(p2);
    tag2 = key2;
    val = h4;
    tag = slot;
    FUN_000267d4(&tag2,0x65a870,0x6690e0,0x65a798,&dat_006695e0);
    ptr = cnt2;
    ptr4 = w5;
    tmp3 = cnt;
    tmp4 = w4;
    tmp2 = len2;
    ptr3 = w3;
    ptr2 = w2;
    FUN_00022c48(msgbuf3);
    FUN_00025f44(msgbuf2,msgbuf3,&w1);
    FUN_000214b0(&tag2,msgbuf2);
    h2 = FUN_000217e4();
    if (h2 == '\0') {
      len = val;
      w0 = tag2;
      kind2 = tag;
      FUN_00025704();
    }
    else {
      if (h2 != '\x01') {
                    /* WARNING: Subroutine does not return */
        FUN_001afa84(s_Fatal_error_005accd0,0xb,2,0xd000000000000036,0x80000000005cc9c0,
                     s_XnuUpcalls_XnuUpcalls_Swift_swif_005cbff0,0x21,2,0xaec,0);
      }
      key = CL4_VOID_U64(FUN_0018569c());
      tmp = key;
      FUN_003698b0(&tmp,0x669b78,&dat_004e6898);
      FUN_0036993c(0x669b78,&dat_004e6898,0,0);
      *msgbuf = key;
      kind = val;
      val4 = tag2;
      errword = idx2;
      errword2 = tag;
      msgbuf6 = idx;
      val3 = w7;
      val2 = w6;
      FUN_00025704();
    }
  }
  else {
    key2 = FUN_00019aac(0);
    FUN_0036993c(key2,FUN_0065a550,0,0);
    *msgbuf5 = w1;
  }
  return;
}



/* FUN_001871d0 @ 0x001871d0   (est. FUN_001871d0)
 * Ghidra: void FUN_001871d0(undefined1 p1,undefined8 p2,long p3)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class A/V1LONG */
void FUN_001871d0(uint8_t p1, uint64_t p2, long p3)
{
  long fn;
  code_fn_t key2;
  bool slot2;
  char slot3;
  uint8_t fn3;
  uint64_t st;
  uint32_t *msgbuf6;
  uint8_t *msgbuf;
  uint64_t msgbuf2;
  uint64_t st2;
  uint64_t r;
  long err;
  long fn2;
  uint64_t slot;
  uint64_t tmp;
  uint64_t val4;
  uint64_t val3;
  uint64_t val2;
  uint64_t tag2;
  uint64_t val;
  uint8_t tag;
  long w7;
  uint64_t w6;
  uint64_t idx2;
  uint64_t idx;
  uint64_t cnt2;
  uint64_t w5;
  uint64_t cnt;
  uint8_t w4;
  uint8_t msgbuf5 [56];
  uint8_t msgbuf4 [56];
  uint8_t msgbuf3 [56];
  uint64_t w3;
  uint64_t len2;
  uint64_t len;
  uint64_t kind2;
  uint64_t w2;
  uint64_t kind;
  uint8_t w1;
  uint64_t w0;
  uint64_t errword2;
  uint64_t errword;
  uint64_t ptr3;
  uint64_t key;
  uint64_t ptr2;
  uint8_t h4;
  uint64_t h3;
  uint64_t ptr;
  uint64_t tmp4;
  uint64_t tmp3;
  uint64_t h2;
  uint64_t tmp2;
  uint8_t h;
  uint32_t ptr4;
  
  r = 0;
  while ((r != 0x100 &&
         (slot2 = *(uint64_t *)(p3 + 0x10) <= r, r != *(uint64_t *)(p3 + 0x10)))) {
    r = r + 1;
    if (slot2) {
                    /* WARNING: Does not return */
      cl4_break(0x187220);
    }
  }
  FUN_00025ebc(msgbuf5,r + 0x14,0,&ptr4);
  if (err == 0) {
    thunk_FUN_00024068(&w6);
    FUN_00023208(0x3756a9db426694c);
    FUN_000231f0(p1);
    FUN_00023208(p2);
    fn2 = *(long *)(p3 + 0x10);
    if (fn2 != 0x100) {
      tmp = 0;
      val4 = 0xe000000000000000;
      FUN_002a4ab4(0x3c);
      thunk_FUN_002acbb8(0xd00000000000001a,0x80000000005cc920);
      thunk_FUN_002acbb8(0xd000000000000038,0x80000000005cc940);
      w7 = fn2;
      key2 = (code_fn_t)FUN_00027724(0x6720e0);
      (*key2)(0x677880,0x6720e0);
      thunk_FUN_002acbb8();
      FUN_003a25d4(msgbuf2);
      slot = 0x450;
      st = tmp;
      st2 = val4;
LAB_00187538:
                    /* WARNING: Subroutine does not return */
      FUN_001afa84(s_Fatal_error_005accd0,0xb,2,st,st2,
                   s_XnuUpcalls_XnuUpcalls_Swift_swif_005cbff0,0x21,2,slot,0);
    }
    fn2 = 0;
    do {
      fn = fn2 + 1;
      FUN_000230f8(*(uint8_t *)(p3 + 0x20 + fn2));
      fn2 = fn;
    } while (fn != 0x100);
    ptr = idx2;
    h3 = w6;
    tmp3 = cnt2;
    tmp4 = idx;
    tmp2 = cnt;
    h2 = w5;
    h = w4;
    FUN_00022c48(msgbuf4);
    FUN_00025f44(msgbuf3,msgbuf4,&ptr4);
    FUN_000214b0(&tmp,msgbuf3);
    slot3 = FUN_000217e4();
    if (slot3 == '\0') {
      len2 = val4;
      w3 = tmp;
      kind2 = val2;
      len = val3;
      kind = val;
      w2 = tag2;
      w1 = tag;
      FUN_00025704();
    }
    else {
      if (slot3 != '\x01') {
        slot = 0xaf7;
        st = 0xd000000000000037;
        st2 = 0x80000000005cc980;
        goto LAB_00187538;
      }
      fn3 = CL4_VOID_U64(FUN_0018569c());
      w7 = CONCAT71(EXTRACT17(w7),fn3);
      FUN_003698b0(&w7,0x669b78,&dat_004e6898);
      FUN_0036993c(0x669b78,&dat_004e6898,0,0);
      *msgbuf = fn3;
      errword2 = val4;
      w0 = tmp;
      ptr3 = val2;
      errword = val3;
      ptr2 = val;
      key = tag2;
      h4 = tag;
      FUN_00025704();
    }
  }
  else {
    st = FUN_00019aac(0);
    FUN_0036993c(st,FUN_0065a550,0,0);
    *msgbuf6 = ptr4;
  }
  return;
}



/* FUN_0018758c @ 0x0018758c   (est. FUN_0018758c)
 * Ghidra: void FUN_0018758c(undefined1 p1,undefined1 p2,undefined8 p3)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class A/V1 */
void FUN_0018758c(uint8_t p1, uint8_t p2, uint64_t p3)
{
  char tag2;
  uint8_t tmp;
  uint64_t tmp2;
  uint32_t *msgbuf6;
  uint8_t *msgbuf;
  long err;
  uint8_t val2;
  uint64_t val;
  uint64_t len;
  uint64_t idx2;
  uint64_t kind2;
  uint64_t idx;
  uint64_t kind;
  uint8_t cnt2;
  uint8_t msgbuf5 [52];
  uint32_t cnt;
  uint8_t msgbuf4 [56];
  uint8_t msgbuf3 [56];
  uint8_t msgbuf2 [56];
  uint64_t len2;
  uint64_t errword2;
  uint64_t errword;
  uint64_t w3;
  uint64_t tag;
  uint64_t w2;
  uint8_t w7;
  uint64_t w6;
  uint64_t w1;
  uint64_t w0;
  uint64_t val4;
  uint64_t w5;
  uint64_t val3;
  uint8_t w4;
  
  FUN_00025ebc(msgbuf4,0x18,0,&cnt);
  if (err == 0) {
    thunk_FUN_00024068(msgbuf5);
    FUN_00023208(0x11f6aed8a43e4834);
    FUN_000231f0(p1);
    FUN_000231f0(p2);
    FUN_00023208(p3);
    FUN_00022c48(msgbuf3);
    FUN_00025f44(msgbuf2,msgbuf3,&cnt);
    FUN_000214b0(&val,msgbuf2);
    tag2 = FUN_000217e4();
    if (tag2 == '\0') {
      errword2 = len;
      len2 = val;
      w3 = kind2;
      errword = idx2;
      w2 = kind;
      tag = idx;
      w7 = cnt2;
      FUN_00025704();
    }
    else {
      if (tag2 != '\x01') {
                    /* WARNING: Subroutine does not return */
        FUN_001afa84(s_Fatal_error_005accd0,0xb,2,0xd000000000000035,0x80000000005cc8e0,
                     s_XnuUpcalls_XnuUpcalls_Swift_swif_005cbff0,0x21,2,0xb02,0);
      }
      tmp = CL4_VOID_U64(FUN_0018569c());
      val2 = tmp;
      FUN_003698b0(&val2,0x669b78,&dat_004e6898);
      FUN_0036993c(0x669b78,&dat_004e6898,0,0);
      *msgbuf = tmp;
      w1 = len;
      w6 = val;
      val4 = kind2;
      w0 = idx2;
      val3 = kind;
      w5 = idx;
      w4 = cnt2;
      FUN_00025704();
    }
  }
  else {
    tmp2 = FUN_00019aac(0);
    FUN_0036993c(tmp2,FUN_0065a550,0,0);
    *msgbuf6 = cnt;
  }
  return;
}



/* FUN_00187820 @ 0x00187820   (est. FUN_00187820)
 * Ghidra: undefined8 FUN_00187820(undefined1 p1,undefined8 p2)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class A/V1 */
uint64_t FUN_00187820(uint8_t p1, uint64_t p2)
{
  char tag2;
  uint8_t tmp;
  uint64_t tmp2;
  uint32_t *msgbuf5;
  long err;
  cl4_16_t tag;
  uint8_t idx;
  uint64_t cnt2;
  uint64_t errword2;
  uint64_t cnt;
  uint64_t errword;
  uint64_t len2;
  uint64_t msgbuf6;
  uint8_t len;
  uint8_t msgbuf4 [52];
  uint32_t kind2;
  uint8_t msgbuf3 [56];
  uint8_t msgbuf2 [56];
  uint8_t msgbuf [56];
  uint64_t kind;
  uint64_t w2;
  uint64_t w1;
  uint64_t w0;
  uint64_t w7;
  uint64_t val4;
  uint8_t w6;
  uint64_t w5;
  uint64_t val3;
  uint64_t val2;
  uint64_t val;
  uint64_t w4;
  uint64_t idx2;
  uint8_t w3;
  
  FUN_00025ebc(msgbuf3,0x14,0,&kind2);
  if (err == 0) {
    thunk_FUN_00024068(msgbuf4);
    FUN_00023208(0xa8de85603e2c7005);
    FUN_000231f0(p1);
    FUN_00023208(p2);
    FUN_00022c48(msgbuf2);
    FUN_00025f44(msgbuf,msgbuf2,&kind2);
    FUN_000214b0(&cnt2,msgbuf);
    tag2 = FUN_000217e4();
    if (tag2 == '\0') {
      p2 = FUN_00021904();
      w2 = errword2;
      kind = cnt2;
      w0 = errword;
      w1 = cnt;
      val4 = msgbuf6;
      w7 = len2;
      w6 = len;
      FUN_00025704();
    }
    else {
      if (tag2 != '\x01') {
                    /* WARNING: Subroutine does not return */
        FUN_001afa84(s_Fatal_error_005accd0,0xb,2,0xd000000000000038,0x80000000005cc8a0,
                     s_XnuUpcalls_XnuUpcalls_Swift_swif_005cbff0,0x21,2,0xb18,0);
      }
      tmp = CL4_VOID_U64(FUN_0018569c());
      idx = tmp;
      FUN_003698b0(&idx,0x669b78,&dat_004e6898);
      tag = FUN_0036993c(0x669b78,&dat_004e6898,0,0);
      p2 = tag._0_8_;
      tag.hi = (uint64_t)(tmp);
      val3 = errword2;
      w5 = cnt2;
      val = errword;
      val2 = cnt;
      idx2 = msgbuf6;
      w4 = len2;
      w3 = len;
      FUN_00025704();
    }
  }
  else {
    tmp2 = FUN_00019aac(0);
    FUN_0036993c(tmp2,FUN_0065a550,0,0);
    *msgbuf5 = kind2;
  }
  return p2;
}



/* FUN_00187aac @ 0x00187aac   (est. FUN_00187aac)
 * Ghidra: uint8_t FUN_00187aac(uint8_t p1)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class A/V1 */
uint8_t FUN_00187aac(uint8_t p1)
{
  char tag2;
  uint8_t tmp;
  uint64_t tmp2;
  uint32_t *msgbuf6;
  uint8_t *msgbuf;
  long err;
  uint8_t idx2;
  uint64_t idx;
  uint64_t kind;
  uint64_t cnt2;
  uint64_t errword2;
  uint64_t cnt;
  uint64_t errword;
  uint8_t len2;
  uint8_t msgbuf5 [52];
  uint32_t len;
  uint8_t msgbuf4 [56];
  uint8_t msgbuf3 [56];
  uint8_t msgbuf2 [56];
  uint64_t kind2;
  uint64_t w3;
  uint64_t w2;
  uint64_t w1;
  uint64_t tag;
  uint64_t w0;
  uint8_t w7;
  uint64_t w6;
  uint64_t val4;
  uint64_t val3;
  uint64_t val2;
  uint64_t w5;
  uint64_t val;
  uint8_t w4;
  
  FUN_00025ebc(msgbuf4,0xc,0,&len);
  if (err == 0) {
    thunk_FUN_00024068(msgbuf5);
    FUN_00023208(0xb94881222267713b);
    FUN_000231f0(p1);
    FUN_00022c48(msgbuf3);
    FUN_00025f44(msgbuf2,msgbuf3,&len);
    FUN_000214b0(&idx,msgbuf2);
    tag2 = FUN_000217e4();
    if (tag2 == '\0') {
      p1 = FUN_00021738();
      w3 = kind;
      kind2 = idx;
      w1 = errword2;
      w2 = cnt2;
      w0 = errword;
      tag = cnt;
      w7 = len2;
      FUN_00025704();
    }
    else {
      if (tag2 != '\x01') {
                    /* WARNING: Subroutine does not return */
        FUN_001afa84(s_Fatal_error_005accd0,0xb,2,0xd00000000000003a,0x80000000005cc860,
                     s_XnuUpcalls_XnuUpcalls_Swift_swif_005cbff0,0x21,2,0xb23,0);
      }
      tmp = CL4_VOID_U64(FUN_0018569c());
      idx2 = tmp;
      FUN_003698b0(&idx2,0x669b78,&dat_004e6898);
      p1 = (uint8_t)FUN_0036993c(0x669b78,&dat_004e6898,0,0).lo;
      *msgbuf = tmp;
      val4 = kind;
      w6 = idx;
      val2 = errword2;
      val3 = cnt2;
      val = errword;
      w5 = cnt;
      w4 = len2;
      FUN_00025704();
    }
  }
  else {
    tmp2 = FUN_00019aac(0);
    FUN_0036993c(tmp2,FUN_0065a550,0,0);
    *msgbuf6 = len;
  }
  return p1 & 1;
}



/* FUN_00187d28 @ 0x00187d28   (est. FUN_00187d28)
 * Ghidra: void FUN_00187d28(undefined8 p1,undefined8 p2)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class A/V1 */
void FUN_00187d28(uint64_t p1, uint64_t p2)
{
  char tag2;
  uint8_t tmp;
  uint64_t tmp2;
  uint32_t *msgbuf6;
  uint8_t *msgbuf;
  long err;
  uint8_t idx2;
  uint64_t idx;
  uint64_t kind;
  uint64_t cnt2;
  uint64_t errword2;
  uint64_t cnt;
  uint64_t errword;
  uint8_t len2;
  uint8_t msgbuf5 [52];
  uint32_t len;
  uint8_t msgbuf4 [56];
  uint8_t msgbuf3 [56];
  uint8_t msgbuf2 [56];
  uint64_t kind2;
  uint64_t w3;
  uint64_t w2;
  uint64_t w1;
  uint64_t tag;
  uint64_t w0;
  uint8_t w7;
  uint64_t w6;
  uint64_t val4;
  uint64_t val3;
  uint64_t val2;
  uint64_t w5;
  uint64_t val;
  uint8_t w4;
  
  FUN_00025ebc(msgbuf4,0x14,0,&len);
  if (err == 0) {
    thunk_FUN_00024068(msgbuf5);
    FUN_00023208(0x55f93c834fb37099);
    FUN_00023208(p1);
    FUN_00023318(p2);
    FUN_00022c48(msgbuf3);
    FUN_00025f44(msgbuf2,msgbuf3,&len);
    FUN_000214b0(&idx,msgbuf2);
    tag2 = FUN_000217e4();
    if (tag2 == '\0') {
      w3 = kind;
      kind2 = idx;
      w1 = errword2;
      w2 = cnt2;
      w0 = errword;
      tag = cnt;
      w7 = len2;
      FUN_00025704();
    }
    else {
      if (tag2 != '\x01') {
                    /* WARNING: Subroutine does not return */
        FUN_001afa84(s_Fatal_error_005accd0,0xb,2,0xd00000000000003d,0x80000000005cc820,
                     s_XnuUpcalls_XnuUpcalls_Swift_swif_005cbff0,0x21,2,0xb2e,0);
      }
      tmp = CL4_VOID_U64(FUN_001857a8());
      idx2 = tmp;
      FUN_003698b0(&idx2,0x669ae8,&dat_004e6878);
      FUN_0036993c(0x669ae8,&dat_004e6878,0,0);
      *msgbuf = tmp;
      val4 = kind;
      w6 = idx;
      val2 = errword2;
      val3 = cnt2;
      val = errword;
      w5 = cnt;
      w4 = len2;
      FUN_00025704();
    }
  }
  else {
    tmp2 = FUN_00019aac(0);
    FUN_0036993c(tmp2,FUN_0065a550,0,0);
    *msgbuf6 = len;
  }
  return;
}



/* FUN_00187fa4 @ 0x00187fa4   (est. FUN_00187fa4)
 * Ghidra: void FUN_00187fa4(undefined8 p1,undefined8 p2)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class A/V1 */
void FUN_00187fa4(uint64_t p1, uint64_t p2)
{
  char tag2;
  uint8_t tmp;
  uint64_t tmp2;
  uint32_t *msgbuf6;
  uint8_t *msgbuf;
  long err;
  uint8_t idx2;
  uint64_t idx;
  uint64_t kind;
  uint64_t cnt2;
  uint64_t errword2;
  uint64_t cnt;
  uint64_t errword;
  uint8_t len2;
  uint8_t msgbuf5 [52];
  uint32_t len;
  uint8_t msgbuf4 [56];
  uint8_t msgbuf3 [56];
  uint8_t msgbuf2 [56];
  uint64_t kind2;
  uint64_t w3;
  uint64_t w2;
  uint64_t w1;
  uint64_t tag;
  uint64_t w0;
  uint8_t w7;
  uint64_t w6;
  uint64_t val4;
  uint64_t val3;
  uint64_t val2;
  uint64_t w5;
  uint64_t val;
  uint8_t w4;
  
  FUN_00025ebc(msgbuf4,0x14,0,&len);
  if (err == 0) {
    thunk_FUN_00024068(msgbuf5);
    FUN_00023208(0xb52c623eb5351c7f);
    FUN_00023208(p1);
    FUN_00023318(p2);
    FUN_00022c48(msgbuf3);
    FUN_00025f44(msgbuf2,msgbuf3,&len);
    FUN_000214b0(&idx,msgbuf2);
    tag2 = FUN_000217e4();
    if (tag2 == '\0') {
      w3 = kind;
      kind2 = idx;
      w1 = errword2;
      w2 = cnt2;
      w0 = errword;
      tag = cnt;
      w7 = len2;
      FUN_00025704();
    }
    else {
      if (tag2 != '\x01') {
                    /* WARNING: Subroutine does not return */
        FUN_001afa84(s_Fatal_error_005accd0,0xb,2,0xd00000000000003b,0x80000000005cc7e0,
                     s_XnuUpcalls_XnuUpcalls_Swift_swif_005cbff0,0x21,2,0xb39,0);
      }
      tmp = CL4_VOID_U64(FUN_001857a8());
      idx2 = tmp;
      FUN_003698b0(&idx2,0x669ae8,&dat_004e6878);
      FUN_0036993c(0x669ae8,&dat_004e6878,0,0);
      *msgbuf = tmp;
      val4 = kind;
      w6 = idx;
      val2 = errword2;
      val3 = cnt2;
      val = errword;
      w5 = cnt;
      w4 = len2;
      FUN_00025704();
    }
  }
  else {
    tmp2 = FUN_00019aac(0);
    FUN_0036993c(tmp2,FUN_0065a550,0,0);
    *msgbuf6 = len;
  }
  return;
}



/* FUN_00188220 @ 0x00188220   (est. FUN_00188220)
 * Ghidra: void FUN_00188220(undefined8 p1,undefined8 p2)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class A/V1 */
void FUN_00188220(uint64_t p1, uint64_t p2)
{
  char tag2;
  uint8_t tmp;
  uint64_t tmp2;
  uint32_t *msgbuf6;
  uint8_t *msgbuf;
  long err;
  uint8_t idx2;
  uint64_t idx;
  uint64_t kind;
  uint64_t cnt2;
  uint64_t errword2;
  uint64_t cnt;
  uint64_t errword;
  uint8_t len2;
  uint8_t msgbuf5 [52];
  uint32_t len;
  uint8_t msgbuf4 [56];
  uint8_t msgbuf3 [56];
  uint8_t msgbuf2 [56];
  uint64_t kind2;
  uint64_t w3;
  uint64_t w2;
  uint64_t w1;
  uint64_t tag;
  uint64_t w0;
  uint8_t w7;
  uint64_t w6;
  uint64_t val4;
  uint64_t val3;
  uint64_t val2;
  uint64_t w5;
  uint64_t val;
  uint8_t w4;
  
  FUN_00025ebc(msgbuf4,0x14,0,&len);
  if (err == 0) {
    thunk_FUN_00024068(msgbuf5);
    FUN_00023208(0xfb0e58e78628c76);
    FUN_00023208(p1);
    FUN_00023318(p2);
    FUN_00022c48(msgbuf3);
    FUN_00025f44(msgbuf2,msgbuf3,&len);
    FUN_000214b0(&idx,msgbuf2);
    tag2 = FUN_000217e4();
    if (tag2 == '\0') {
      w3 = kind;
      kind2 = idx;
      w1 = errword2;
      w2 = cnt2;
      w0 = errword;
      tag = cnt;
      w7 = len2;
      FUN_00025704();
    }
    else {
      if (tag2 != '\x01') {
                    /* WARNING: Subroutine does not return */
        FUN_001afa84(s_Fatal_error_005accd0,0xb,2,0xd00000000000003b,0x80000000005cc7a0,
                     s_XnuUpcalls_XnuUpcalls_Swift_swif_005cbff0,0x21,2,0xb44,0);
      }
      tmp = CL4_VOID_U64(FUN_001857a8());
      idx2 = tmp;
      FUN_003698b0(&idx2,0x669ae8,&dat_004e6878);
      FUN_0036993c(0x669ae8,&dat_004e6878,0,0);
      *msgbuf = tmp;
      val4 = kind;
      w6 = idx;
      val2 = errword2;
      val3 = cnt2;
      val = errword;
      w5 = cnt;
      w4 = len2;
      FUN_00025704();
    }
  }
  else {
    tmp2 = FUN_00019aac(0);
    FUN_0036993c(tmp2,FUN_0065a550,0,0);
    *msgbuf6 = len;
  }
  return;
}



/* FUN_0018849c @ 0x0018849c   (est. FUN_0018849c)
 * Ghidra: void FUN_0018849c(undefined8 p1,undefined8 p2)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class A/V1 */
void FUN_0018849c(uint64_t p1, uint64_t p2)
{
  char tag2;
  uint8_t tmp;
  uint64_t tmp2;
  uint32_t *msgbuf6;
  uint8_t *msgbuf;
  long err;
  uint8_t idx2;
  uint64_t idx;
  uint64_t kind;
  uint64_t cnt2;
  uint64_t errword2;
  uint64_t cnt;
  uint64_t errword;
  uint8_t len2;
  uint8_t msgbuf5 [52];
  uint32_t len;
  uint8_t msgbuf4 [56];
  uint8_t msgbuf3 [56];
  uint8_t msgbuf2 [56];
  uint64_t kind2;
  uint64_t w3;
  uint64_t w2;
  uint64_t w1;
  uint64_t tag;
  uint64_t w0;
  uint8_t w7;
  uint64_t w6;
  uint64_t val4;
  uint64_t val3;
  uint64_t val2;
  uint64_t w5;
  uint64_t val;
  uint8_t w4;
  
  FUN_00025ebc(msgbuf4,0x14,0,&len);
  if (err == 0) {
    thunk_FUN_00024068(msgbuf5);
    FUN_00023208(0x1ede3fa1a71f0bfb);
    FUN_00023208(p1);
    FUN_00023318(p2);
    FUN_00022c48(msgbuf3);
    FUN_00025f44(msgbuf2,msgbuf3,&len);
    FUN_000214b0(&idx,msgbuf2);
    tag2 = FUN_000217e4();
    if (tag2 == '\0') {
      w3 = kind;
      kind2 = idx;
      w1 = errword2;
      w2 = cnt2;
      w0 = errword;
      tag = cnt;
      w7 = len2;
      FUN_00025704();
    }
    else {
      if (tag2 != '\x01') {
                    /* WARNING: Subroutine does not return */
        FUN_001afa84(s_Fatal_error_005accd0,0xb,2,0xd00000000000003c,0x80000000005cc760,
                     s_XnuUpcalls_XnuUpcalls_Swift_swif_005cbff0,0x21,2,0xb4f,0);
      }
      tmp = CL4_VOID_U64(FUN_001857a8());
      idx2 = tmp;
      FUN_003698b0(&idx2,0x669ae8,&dat_004e6878);
      FUN_0036993c(0x669ae8,&dat_004e6878,0,0);
      *msgbuf = tmp;
      val4 = kind;
      w6 = idx;
      val2 = errword2;
      val3 = cnt2;
      val = errword;
      w5 = cnt;
      w4 = len2;
      FUN_00025704();
    }
  }
  else {
    tmp2 = FUN_00019aac(0);
    FUN_0036993c(tmp2,FUN_0065a550,0,0);
    *msgbuf6 = len;
  }
  return;
}



/* FUN_00188718 @ 0x00188718   (est. FUN_00188718)
 * Ghidra: undefined8 FUN_00188718(undefined8 p1)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class A/V1 */
uint64_t FUN_00188718(uint64_t p1)
{
  char tag2;
  uint8_t tmp;
  uint64_t tmp2;
  uint32_t *msgbuf5;
  long err;
  cl4_16_t tag;
  uint8_t idx;
  uint64_t cnt2;
  uint64_t errword2;
  uint64_t cnt;
  uint64_t errword;
  uint64_t len2;
  uint64_t msgbuf6;
  uint8_t len;
  uint8_t msgbuf4 [52];
  uint32_t kind2;
  uint8_t msgbuf3 [56];
  uint8_t msgbuf2 [56];
  uint8_t msgbuf [56];
  uint64_t kind;
  uint64_t w2;
  uint64_t w1;
  uint64_t w0;
  uint64_t w7;
  uint64_t val4;
  uint8_t w6;
  uint64_t w5;
  uint64_t val3;
  uint64_t val2;
  uint64_t val;
  uint64_t w4;
  uint64_t idx2;
  uint8_t w3;
  
  FUN_00025ebc(msgbuf3,0x10,0,&kind2);
  if (err == 0) {
    thunk_FUN_00024068(msgbuf4);
    FUN_00023208(0xe1a2dbfa8bfc6dc0);
    FUN_00023208(p1);
    FUN_00022c48(msgbuf2);
    FUN_00025f44(msgbuf,msgbuf2,&kind2);
    FUN_000214b0(&cnt2,msgbuf);
    tag2 = FUN_000217e4();
    if (tag2 == '\0') {
      p1 = FUN_000218a4();
      w2 = errword2;
      kind = cnt2;
      w0 = errword;
      w1 = cnt;
      val4 = msgbuf6;
      w7 = len2;
      w6 = len;
      FUN_00025704();
    }
    else {
      if (tag2 != '\x01') {
                    /* WARNING: Subroutine does not return */
        FUN_001afa84(s_Fatal_error_005accd0,0xb,2,0xd00000000000003f,0x80000000005cc720,
                     s_XnuUpcalls_XnuUpcalls_Swift_swif_005cbff0,0x21,2,0xb5a,0);
      }
      tmp = CL4_VOID_U64(FUN_001857a8());
      idx = tmp;
      FUN_003698b0(&idx,0x669ae8,&dat_004e6878);
      tag = FUN_0036993c(0x669ae8,&dat_004e6878,0,0);
      p1 = tag._0_8_;
      tag.hi = (uint64_t)(tmp);
      val3 = errword2;
      w5 = cnt2;
      val = errword;
      val2 = cnt;
      idx2 = msgbuf6;
      w4 = len2;
      w3 = len;
      FUN_00025704();
    }
  }
  else {
    tmp2 = FUN_00019aac(0);
    FUN_0036993c(tmp2,FUN_0065a550,0,0);
    *msgbuf5 = kind2;
  }
  return p1;
}



/* FUN_00188994 @ 0x00188994   (est. FUN_00188994)
 * Ghidra: void FUN_00188994(undefined8 p1,undefined8 p2)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class A/V1 */
void FUN_00188994(uint64_t p1, uint64_t p2)
{
  char tag2;
  uint8_t tmp;
  uint64_t tmp2;
  uint32_t *msgbuf6;
  uint8_t *msgbuf;
  long err;
  uint8_t idx2;
  uint64_t idx;
  uint64_t kind;
  uint64_t cnt2;
  uint64_t errword2;
  uint64_t cnt;
  uint64_t errword;
  uint8_t len2;
  uint8_t msgbuf5 [52];
  uint32_t len;
  uint8_t msgbuf4 [56];
  uint8_t msgbuf3 [56];
  uint8_t msgbuf2 [56];
  uint64_t kind2;
  uint64_t w3;
  uint64_t w2;
  uint64_t w1;
  uint64_t tag;
  uint64_t w0;
  uint8_t w7;
  uint64_t w6;
  uint64_t val4;
  uint64_t val3;
  uint64_t val2;
  uint64_t w5;
  uint64_t val;
  uint8_t w4;
  
  FUN_00025ebc(msgbuf4,0x14,0,&len);
  if (err == 0) {
    thunk_FUN_00024068(msgbuf5);
    FUN_00023208(0x18c32d4348018121);
    FUN_00023208(p1);
    FUN_000231f0(p2);
    FUN_00022c48(msgbuf3);
    FUN_00025f44(msgbuf2,msgbuf3,&len);
    FUN_000214b0(&idx,msgbuf2);
    tag2 = FUN_000217e4();
    if (tag2 == '\0') {
      w3 = kind;
      kind2 = idx;
      w1 = errword2;
      w2 = cnt2;
      w0 = errword;
      tag = cnt;
      w7 = len2;
      FUN_00025704();
    }
    else {
      if (tag2 != '\x01') {
                    /* WARNING: Subroutine does not return */
        FUN_001afa84(s_Fatal_error_005accd0,0xb,2,0xd00000000000003d,0x80000000005cc6e0,
                     s_XnuUpcalls_XnuUpcalls_Swift_swif_005cbff0,0x21,2,0xb65,0);
      }
      tmp = CL4_VOID_U64(FUN_001857a8());
      idx2 = tmp;
      FUN_003698b0(&idx2,0x669ae8,&dat_004e6878);
      FUN_0036993c(0x669ae8,&dat_004e6878,0,0);
      *msgbuf = tmp;
      val4 = kind;
      w6 = idx;
      val2 = errword2;
      val3 = cnt2;
      val = errword;
      w5 = cnt;
      w4 = len2;
      FUN_00025704();
    }
  }
  else {
    tmp2 = FUN_00019aac(0);
    FUN_0036993c(tmp2,FUN_0065a550,0,0);
    *msgbuf6 = len;
  }
  return;
}



/* FUN_00188c10 @ 0x00188c10   (est. FUN_00188c10)
 * Ghidra: void FUN_00188c10(undefined8 p1,undefined8 p2)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class A/V1 */
void FUN_00188c10(uint64_t p1, uint64_t p2)
{
  char tag2;
  uint8_t tmp;
  uint64_t tmp2;
  uint32_t *msgbuf6;
  uint8_t *msgbuf;
  long err;
  uint8_t idx2;
  uint64_t idx;
  uint64_t kind;
  uint64_t cnt2;
  uint64_t errword2;
  uint64_t cnt;
  uint64_t errword;
  uint8_t len2;
  uint8_t msgbuf5 [52];
  uint32_t len;
  uint8_t msgbuf4 [56];
  uint8_t msgbuf3 [56];
  uint8_t msgbuf2 [56];
  uint64_t kind2;
  uint64_t w3;
  uint64_t w2;
  uint64_t w1;
  uint64_t tag;
  uint64_t w0;
  uint8_t w7;
  uint64_t w6;
  uint64_t val4;
  uint64_t val3;
  uint64_t val2;
  uint64_t w5;
  uint64_t val;
  uint8_t w4;
  
  FUN_00025ebc(msgbuf4,0x14,0,&len);
  if (err == 0) {
    thunk_FUN_00024068(msgbuf5);
    FUN_00023208(0xb3be921747bdf609);
    FUN_00023208(p1);
    FUN_000231f0(p2);
    FUN_00022c48(msgbuf3);
    FUN_00025f44(msgbuf2,msgbuf3,&len);
    FUN_000214b0(&idx,msgbuf2);
    tag2 = FUN_000217e4();
    if (tag2 == '\0') {
      w3 = kind;
      kind2 = idx;
      w1 = errword2;
      w2 = cnt2;
      w0 = errword;
      tag = cnt;
      w7 = len2;
      FUN_00025704();
    }
    else {
      if (tag2 != '\x01') {
                    /* WARNING: Subroutine does not return */
        FUN_001afa84(s_Fatal_error_005accd0,0xb,2,0xd00000000000003d,0x80000000005cc6a0,
                     s_XnuUpcalls_XnuUpcalls_Swift_swif_005cbff0,0x21,2,0xb70,0);
      }
      tmp = CL4_VOID_U64(FUN_001857a8());
      idx2 = tmp;
      FUN_003698b0(&idx2,0x669ae8,&dat_004e6878);
      FUN_0036993c(0x669ae8,&dat_004e6878,0,0);
      *msgbuf = tmp;
      val4 = kind;
      w6 = idx;
      val2 = errword2;
      val3 = cnt2;
      val = errword;
      w5 = cnt;
      w4 = len2;
      FUN_00025704();
    }
  }
  else {
    tmp2 = FUN_00019aac(0);
    FUN_0036993c(tmp2,FUN_0065a550,0,0);
    *msgbuf6 = len;
  }
  return;
}



/* FUN_00188e8c @ 0x00188e8c   (est. FUN_00188e8c)
 * Ghidra: void FUN_00188e8c(undefined8 p1,undefined8 p2)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class A/V1 */
void FUN_00188e8c(uint64_t p1, uint64_t p2)
{
  char tag2;
  uint8_t tmp;
  uint64_t tmp2;
  uint32_t *msgbuf6;
  uint8_t *msgbuf;
  long err;
  uint8_t idx2;
  uint64_t idx;
  uint64_t kind;
  uint64_t cnt2;
  uint64_t errword2;
  uint64_t cnt;
  uint64_t errword;
  uint8_t len2;
  uint8_t msgbuf5 [52];
  uint32_t len;
  uint8_t msgbuf4 [56];
  uint8_t msgbuf3 [56];
  uint8_t msgbuf2 [56];
  uint64_t kind2;
  uint64_t w3;
  uint64_t w2;
  uint64_t w1;
  uint64_t tag;
  uint64_t w0;
  uint8_t w7;
  uint64_t w6;
  uint64_t val4;
  uint64_t val3;
  uint64_t val2;
  uint64_t w5;
  uint64_t val;
  uint8_t w4;
  
  FUN_00025ebc(msgbuf4,0x14,0,&len);
  if (err == 0) {
    thunk_FUN_00024068(msgbuf5);
    FUN_00023208(0x8d715509f1407b5c);
    FUN_00023208(p1);
    FUN_000231f0(p2);
    FUN_00022c48(msgbuf3);
    FUN_00025f44(msgbuf2,msgbuf3,&len);
    FUN_000214b0(&idx,msgbuf2);
    tag2 = FUN_000217e4();
    if (tag2 == '\0') {
      w3 = kind;
      kind2 = idx;
      w1 = errword2;
      w2 = cnt2;
      w0 = errword;
      tag = cnt;
      w7 = len2;
      FUN_00025704();
    }
    else {
      if (tag2 != '\x01') {
                    /* WARNING: Subroutine does not return */
        FUN_001afa84(s_Fatal_error_005accd0,0xb,2,0xd00000000000003e,0x80000000005cc660,
                     s_XnuUpcalls_XnuUpcalls_Swift_swif_005cbff0,0x21,2,0xb7b,0);
      }
      tmp = CL4_VOID_U64(FUN_001857a8());
      idx2 = tmp;
      FUN_003698b0(&idx2,0x669ae8,&dat_004e6878);
      FUN_0036993c(0x669ae8,&dat_004e6878,0,0);
      *msgbuf = tmp;
      val4 = kind;
      w6 = idx;
      val2 = errword2;
      val3 = cnt2;
      val = errword;
      w5 = cnt;
      w4 = len2;
      FUN_00025704();
    }
  }
  else {
    tmp2 = FUN_00019aac(0);
    FUN_0036993c(tmp2,FUN_0065a550,0,0);
    *msgbuf6 = len;
  }
  return;
}



/* FUN_00189108 @ 0x00189108   (est. FUN_00189108)
 * Ghidra: uint FUN_00189108(undefined8 p1,undefined8 p2,undefined1 *p3)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class A/V1 */
uint32_t FUN_00189108(uint64_t p1, uint64_t p2, uint64_t *p3)
{
  uint32_t fn3;
  uint32_t st;
  void *slot3;
  char fn;
  uint8_t st2;
  uint32_t r;
  long fn2;
  uint64_t r2;
  uint32_t *msgbuf5;
  uint8_t *msgbuf;
  long err;
  uint8_t h;
  uint32_t ptr4;
  uint32_t w3;
  uint32_t w2;
  uint32_t w1;
  uint64_t ptr3;
  uint64_t w0;
  uint64_t ptr2;
  uint64_t val4;
  uint8_t ptr;
  uint32_t tmp4;
  uint32_t val3;
  uint32_t val2;
  uint32_t val;
  uint64_t idx2;
  uint64_t idx;
  uint64_t tmp3;
  uint64_t cnt2;
  uint8_t tmp2;
  uint32_t tmp;
  uint8_t msgbuf4 [56];
  uint8_t msgbuf3 [56];
  uint8_t msgbuf2 [56];
  uint64_t tag2;
  uint64_t cnt;
  uint64_t len2;
  uint64_t len;
  uint64_t tag;
  uint64_t kind2;
  uint8_t w7;
  uint64_t w6;
  uint64_t kind;
  uint64_t errword2;
  uint64_t errword;
  uint64_t w5;
  uint64_t msgbuf6;
  uint8_t w4;
  uint64_t slot2;
  uint64_t key;
  uint64_t h4;
  uint64_t h3;
  uint64_t slot;
  uint64_t h2;
  uint8_t key2;
  
  st2 = *p3;
  fn3 = *(uint32_t *)(p3 + 4);
  st = *(uint32_t *)(p3 + 8);
  tmp4 = CONCAT31(EXTRACT13(tmp4),st2);
  val3 = fn3;
  val2 = st;
  fn2 = FUN_00026754(&tmp4,0x6693a0,&dat_006695f8);
  if (SCARRY8(fn2,0x14)) {
                    /* WARNING: Does not return */
    cl4_break(0x189468);
  }
  FUN_00025ebc(msgbuf4,fn2 + 0x14,0,&tmp);
  if (err == 0) {
    thunk_FUN_00024068(&tmp4);
    FUN_00023208(0xa255c9fe760496a6);
    FUN_00023208(p1);
    FUN_000231f0(p2);
    ptr4 = CONCAT31(EXTRACT13(ptr4),st2);
    w3 = fn3;
    w2 = st;
    FUN_000267d4(&ptr4,0x65a870,0x6693a0,0x65a798,&dat_006695f8);
    key = CONCAT44(val,val2);
    slot2 = CONCAT44(val3,tmp4);
    h3 = idx;
    h4 = idx2;
    h2 = cnt2;
    slot = tmp3;
    key2 = tmp2;
    FUN_00022c48(msgbuf3);
    FUN_00025f44(msgbuf2,msgbuf3,&tmp);
    FUN_000214b0(&ptr4,msgbuf2);
    fn = FUN_000217e4();
    if (fn == '\0') {
      r = FUN_00021738();
      cnt = CONCAT44(w1,w2);
      tag2 = CONCAT44(w3,ptr4);
      len = w0;
      len2 = ptr3;
      kind2 = val4;
      tag = ptr2;
      w7 = ptr;
      FUN_00025704();
    }
    else {
      if (fn != '\x01') {
                    /* WARNING: Subroutine does not return */
        FUN_001afa84(s_Fatal_error_005accd0,0xb,2,0xd000000000000042,0x80000000005cc610,
                     s_XnuUpcalls_XnuUpcalls_Swift_swif_005cbff0,0x21,2,0xb86,0);
      }
      st2 = CL4_VOID_U64(FUN_001857a8());
      h = st2;
      FUN_003698b0(&h,0x669ae8,&dat_004e6878);
      r = (uint32_t)FUN_0036993c(0x669ae8,&dat_004e6878,0,0).lo;
      *msgbuf = st2;
      kind = CONCAT44(w1,w2);
      w6 = CONCAT44(w3,ptr4);
      errword = w0;
      errword2 = ptr3;
      msgbuf6 = val4;
      w5 = ptr2;
      w4 = ptr;
      FUN_00025704();
    }
  }
  else {
    r = (uint32_t)p2;
    r2 = FUN_00019aac(0);
    FUN_0036993c(r2,FUN_0065a550,0,0);
    *msgbuf5 = tmp;
  }
  return r & 1;
}



/* FUN_001894b4 @ 0x001894b4   (est. FUN_001894b4)
 * Ghidra: void FUN_001894b4(undefined8 p1,undefined8 p2)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class A/V1 */
void FUN_001894b4(uint64_t p1, uint64_t p2)
{
  char tag2;
  uint8_t tmp;
  uint64_t tmp2;
  uint32_t *msgbuf6;
  uint8_t *msgbuf;
  long err;
  uint8_t idx2;
  uint64_t idx;
  uint64_t kind;
  uint64_t cnt2;
  uint64_t errword2;
  uint64_t cnt;
  uint64_t errword;
  uint8_t len2;
  uint8_t msgbuf5 [52];
  uint32_t len;
  uint8_t msgbuf4 [56];
  uint8_t msgbuf3 [56];
  uint8_t msgbuf2 [56];
  uint64_t kind2;
  uint64_t w3;
  uint64_t w2;
  uint64_t w1;
  uint64_t tag;
  uint64_t w0;
  uint8_t w7;
  uint64_t w6;
  uint64_t val4;
  uint64_t val3;
  uint64_t val2;
  uint64_t w5;
  uint64_t val;
  uint8_t w4;
  
  FUN_00025ebc(msgbuf4,0x14,0,&len);
  if (err == 0) {
    thunk_FUN_00024068(msgbuf5);
    FUN_00023208(0x106c1fd99d3a02fb);
    FUN_00023208(p1);
    FUN_000231f0(p2);
    FUN_00022c48(msgbuf3);
    FUN_00025f44(msgbuf2,msgbuf3,&len);
    FUN_000214b0(&idx,msgbuf2);
    tag2 = FUN_000217e4();
    if (tag2 == '\0') {
      w3 = kind;
      kind2 = idx;
      w1 = errword2;
      w2 = cnt2;
      w0 = errword;
      tag = cnt;
      w7 = len2;
      FUN_00025704();
    }
    else {
      if (tag2 != '\x01') {
                    /* WARNING: Subroutine does not return */
        FUN_001afa84(s_Fatal_error_005accd0,0xb,2,0xd000000000000045,0x80000000005cc5c0,
                     s_XnuUpcalls_XnuUpcalls_Swift_swif_005cbff0,0x21,2,0xb91,0);
      }
      tmp = CL4_VOID_U64(FUN_001857a8());
      idx2 = tmp;
      FUN_003698b0(&idx2,0x669ae8,&dat_004e6878);
      FUN_0036993c(0x669ae8,&dat_004e6878,0,0);
      *msgbuf = tmp;
      val4 = kind;
      w6 = idx;
      val2 = errword2;
      val3 = cnt2;
      val = errword;
      w5 = cnt;
      w4 = len2;
      FUN_00025704();
    }
  }
  else {
    tmp2 = FUN_00019aac(0);
    FUN_0036993c(tmp2,FUN_0065a550,0,0);
    *msgbuf6 = len;
  }
  return;
}



/* FUN_00189730 @ 0x00189730   (est. FUN_00189730)
 * Ghidra: void FUN_00189730(undefined8 p1)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class A/V1 */
void FUN_00189730(uint64_t p1)
{
  char tag2;
  uint8_t tmp;
  uint64_t tmp2;
  uint32_t *msgbuf6;
  uint8_t *msgbuf;
  long err;
  uint8_t idx2;
  uint64_t idx;
  uint64_t kind;
  uint64_t cnt2;
  uint64_t errword2;
  uint64_t cnt;
  uint64_t errword;
  uint8_t len2;
  uint8_t msgbuf5 [52];
  uint32_t len;
  uint8_t msgbuf4 [56];
  uint8_t msgbuf3 [56];
  uint8_t msgbuf2 [56];
  uint64_t kind2;
  uint64_t w3;
  uint64_t w2;
  uint64_t w1;
  uint64_t tag;
  uint64_t w0;
  uint8_t w7;
  uint64_t w6;
  uint64_t val4;
  uint64_t val3;
  uint64_t val2;
  uint64_t w5;
  uint64_t val;
  uint8_t w4;
  
  FUN_00025ebc(msgbuf4,0x10,0,&len);
  if (err == 0) {
    thunk_FUN_00024068(msgbuf5);
    FUN_00023208(0xfcd980ae5259752f);
    FUN_00023208(p1);
    FUN_00022c48(msgbuf3);
    FUN_00025f44(msgbuf2,msgbuf3,&len);
    FUN_000214b0(&idx,msgbuf2);
    tag2 = FUN_000217e4();
    if (tag2 == '\0') {
      w3 = kind;
      kind2 = idx;
      w1 = errword2;
      w2 = cnt2;
      w0 = errword;
      tag = cnt;
      w7 = len2;
      FUN_00025704();
    }
    else {
      if (tag2 != '\x01') {
                    /* WARNING: Subroutine does not return */
        FUN_001afa84(s_Fatal_error_005accd0,0xb,2,0xd000000000000038,0x80000000005cc580,
                     s_XnuUpcalls_XnuUpcalls_Swift_swif_005cbff0,0x21,2,0xb9c,0);
      }
      tmp = CL4_VOID_U64(FUN_001857a8());
      idx2 = tmp;
      FUN_003698b0(&idx2,0x669ae8,&dat_004e6878);
      FUN_0036993c(0x669ae8,&dat_004e6878,0,0);
      *msgbuf = tmp;
      val4 = kind;
      w6 = idx;
      val2 = errword2;
      val3 = cnt2;
      val = errword;
      w5 = cnt;
      w4 = len2;
      FUN_00025704();
    }
  }
  else {
    tmp2 = FUN_00019aac(0);
    FUN_0036993c(tmp2,FUN_0065a550,0,0);
    *msgbuf6 = len;
  }
  return;
}



/* FUN_0018999c @ 0x0018999c   (est. FUN_0018999c)
 * Ghidra: void FUN_0018999c(undefined8 p1)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class A/V1 */
void FUN_0018999c(uint64_t p1)
{
  char tag2;
  uint8_t tmp;
  uint64_t tmp2;
  uint32_t *msgbuf6;
  uint8_t *msgbuf;
  long err;
  uint8_t idx2;
  uint64_t idx;
  uint64_t kind;
  uint64_t cnt2;
  uint64_t errword2;
  uint64_t cnt;
  uint64_t errword;
  uint8_t len2;
  uint8_t msgbuf5 [52];
  uint32_t len;
  uint8_t msgbuf4 [56];
  uint8_t msgbuf3 [56];
  uint8_t msgbuf2 [56];
  uint64_t kind2;
  uint64_t w3;
  uint64_t w2;
  uint64_t w1;
  uint64_t tag;
  uint64_t w0;
  uint8_t w7;
  uint64_t w6;
  uint64_t val4;
  uint64_t val3;
  uint64_t val2;
  uint64_t w5;
  uint64_t val;
  uint8_t w4;
  
  FUN_00025ebc(msgbuf4,0x10,0,&len);
  if (err == 0) {
    thunk_FUN_00024068(msgbuf5);
    FUN_00023208(0xe14a2f0de6cf474a);
    FUN_00023208(p1);
    FUN_00022c48(msgbuf3);
    FUN_00025f44(msgbuf2,msgbuf3,&len);
    FUN_000214b0(&idx,msgbuf2);
    tag2 = FUN_000217e4();
    if (tag2 == '\0') {
      w3 = kind;
      kind2 = idx;
      w1 = errword2;
      w2 = cnt2;
      w0 = errword;
      tag = cnt;
      w7 = len2;
      FUN_00025704();
    }
    else {
      if (tag2 != '\x01') {
                    /* WARNING: Subroutine does not return */
        FUN_001afa84(s_Fatal_error_005accd0,0xb,2,0xd00000000000003a,0x80000000005cc540,
                     s_XnuUpcalls_XnuUpcalls_Swift_swif_005cbff0,0x21,2,0xba7,0);
      }
      tmp = CL4_VOID_U64(FUN_001857a8());
      idx2 = tmp;
      FUN_003698b0(&idx2,0x669ae8,&dat_004e6878);
      FUN_0036993c(0x669ae8,&dat_004e6878,0,0);
      *msgbuf = tmp;
      val4 = kind;
      w6 = idx;
      val2 = errword2;
      val3 = cnt2;
      val = errword;
      w5 = cnt;
      w4 = len2;
      FUN_00025704();
    }
  }
  else {
    tmp2 = FUN_00019aac(0);
    FUN_0036993c(tmp2,FUN_0065a550,0,0);
    *msgbuf6 = len;
  }
  return;
}



/* FUN_00189c08 @ 0x00189c08   (est. FUN_00189c08)
 * Ghidra: void FUN_00189c08(undefined8 p1,undefined8 p2)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class A/V1 */
void FUN_00189c08(uint64_t p1, uint64_t p2)
{
  char tag2;
  uint8_t tmp;
  uint64_t tmp2;
  uint32_t *msgbuf6;
  uint8_t *msgbuf;
  long err;
  uint8_t idx2;
  uint64_t idx;
  uint64_t kind;
  uint64_t cnt2;
  uint64_t errword2;
  uint64_t cnt;
  uint64_t errword;
  uint8_t len2;
  uint8_t msgbuf5 [52];
  uint32_t len;
  uint8_t msgbuf4 [56];
  uint8_t msgbuf3 [56];
  uint8_t msgbuf2 [56];
  uint64_t kind2;
  uint64_t w3;
  uint64_t w2;
  uint64_t w1;
  uint64_t tag;
  uint64_t w0;
  uint8_t w7;
  uint64_t w6;
  uint64_t val4;
  uint64_t val3;
  uint64_t val2;
  uint64_t w5;
  uint64_t val;
  uint8_t w4;
  
  FUN_00025ebc(msgbuf4,0x14,0,&len);
  if (err == 0) {
    thunk_FUN_00024068(msgbuf5);
    FUN_00023208(0x9a13163d905ef778);
    FUN_00023208(p1);
    FUN_000231f0(p2);
    FUN_00022c48(msgbuf3);
    FUN_00025f44(msgbuf2,msgbuf3,&len);
    FUN_000214b0(&idx,msgbuf2);
    tag2 = FUN_000217e4();
    if (tag2 == '\0') {
      w3 = kind;
      kind2 = idx;
      w1 = errword2;
      w2 = cnt2;
      w0 = errword;
      tag = cnt;
      w7 = len2;
      FUN_00025704();
    }
    else {
      if (tag2 != '\x01') {
                    /* WARNING: Subroutine does not return */
        FUN_001afa84(s_Fatal_error_005accd0,0xb,2,0xd00000000000004a,0x80000000005cc4f0,
                     s_XnuUpcalls_XnuUpcalls_Swift_swif_005cbff0,0x21,2,0xbb2,0);
      }
      tmp = CL4_VOID_U64(FUN_001857a8());
      idx2 = tmp;
      FUN_003698b0(&idx2,0x669ae8,&dat_004e6878);
      FUN_0036993c(0x669ae8,&dat_004e6878,0,0);
      *msgbuf = tmp;
      val4 = kind;
      w6 = idx;
      val2 = errword2;
      val3 = cnt2;
      val = errword;
      w5 = cnt;
      w4 = len2;
      FUN_00025704();
    }
  }
  else {
    tmp2 = FUN_00019aac(0);
    FUN_0036993c(tmp2,FUN_0065a550,0,0);
    *msgbuf6 = len;
  }
  return;
}



/* FUN_00189e84 @ 0x00189e84   (est. FUN_00189e84)
 * Ghidra: void FUN_00189e84(undefined8 p1,undefined8 p2)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class A/V1 */
void FUN_00189e84(uint64_t p1, uint64_t p2)
{
  char tag2;
  uint8_t tmp;
  uint64_t tmp2;
  uint32_t *msgbuf6;
  uint8_t *msgbuf;
  long err;
  uint8_t idx2;
  uint64_t idx;
  uint64_t kind;
  uint64_t cnt2;
  uint64_t errword2;
  uint64_t cnt;
  uint64_t errword;
  uint8_t len2;
  uint8_t msgbuf5 [52];
  uint32_t len;
  uint8_t msgbuf4 [56];
  uint8_t msgbuf3 [56];
  uint8_t msgbuf2 [56];
  uint64_t kind2;
  uint64_t w3;
  uint64_t w2;
  uint64_t w1;
  uint64_t tag;
  uint64_t w0;
  uint8_t w7;
  uint64_t w6;
  uint64_t val4;
  uint64_t val3;
  uint64_t val2;
  uint64_t w5;
  uint64_t val;
  uint8_t w4;
  
  FUN_00025ebc(msgbuf4,0x14,0,&len);
  if (err == 0) {
    thunk_FUN_00024068(msgbuf5);
    FUN_00023208(0x7b2ff03490360049);
    FUN_00023208(p1);
    FUN_000231f0(p2);
    FUN_00022c48(msgbuf3);
    FUN_00025f44(msgbuf2,msgbuf3,&len);
    FUN_000214b0(&idx,msgbuf2);
    tag2 = FUN_000217e4();
    if (tag2 == '\0') {
      w3 = kind;
      kind2 = idx;
      w1 = errword2;
      w2 = cnt2;
      w0 = errword;
      tag = cnt;
      w7 = len2;
      FUN_00025704();
    }
    else {
      if (tag2 != '\x01') {
                    /* WARNING: Subroutine does not return */
        FUN_001afa84(s_Fatal_error_005accd0,0xb,2,0xd000000000000040,0x80000000005cc4a0,
                     s_XnuUpcalls_XnuUpcalls_Swift_swif_005cbff0,0x21,2,0xbbd,0);
      }
      tmp = CL4_VOID_U64(FUN_001857a8());
      idx2 = tmp;
      FUN_003698b0(&idx2,0x669ae8,&dat_004e6878);
      FUN_0036993c(0x669ae8,&dat_004e6878,0,0);
      *msgbuf = tmp;
      val4 = kind;
      w6 = idx;
      val2 = errword2;
      val3 = cnt2;
      val = errword;
      w5 = cnt;
      w4 = len2;
      FUN_00025704();
    }
  }
  else {
    tmp2 = FUN_00019aac(0);
    FUN_0036993c(tmp2,FUN_0065a550,0,0);
    *msgbuf6 = len;
  }
  return;
}



/* FUN_0018a100 @ 0x0018a100   (est. FUN_0018a100)
 * Ghidra: void FUN_0018a100(undefined8 p1,undefined8 p2)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class A/V1 */
void FUN_0018a100(uint64_t p1, uint64_t p2)
{
  char tag2;
  uint8_t tmp;
  uint64_t tmp2;
  uint32_t *msgbuf6;
  uint8_t *msgbuf;
  long err;
  uint8_t idx2;
  uint64_t idx;
  uint64_t kind;
  uint64_t cnt2;
  uint64_t errword2;
  uint64_t cnt;
  uint64_t errword;
  uint8_t len2;
  uint8_t msgbuf5 [52];
  uint32_t len;
  uint8_t msgbuf4 [56];
  uint8_t msgbuf3 [56];
  uint8_t msgbuf2 [56];
  uint64_t kind2;
  uint64_t w3;
  uint64_t w2;
  uint64_t w1;
  uint64_t tag;
  uint64_t w0;
  uint8_t w7;
  uint64_t w6;
  uint64_t val4;
  uint64_t val3;
  uint64_t val2;
  uint64_t w5;
  uint64_t val;
  uint8_t w4;
  
  FUN_00025ebc(msgbuf4,0x14,0,&len);
  if (err == 0) {
    thunk_FUN_00024068(msgbuf5);
    FUN_00023208(0x88e2cdb355013567);
    FUN_00023208(p1);
    FUN_000231f0(p2);
    FUN_00022c48(msgbuf3);
    FUN_00025f44(msgbuf2,msgbuf3,&len);
    FUN_000214b0(&idx,msgbuf2);
    tag2 = FUN_000217e4();
    if (tag2 == '\0') {
      w3 = kind;
      kind2 = idx;
      w1 = errword2;
      w2 = cnt2;
      w0 = errword;
      tag = cnt;
      w7 = len2;
      FUN_00025704();
    }
    else {
      if (tag2 != '\x01') {
                    /* WARNING: Subroutine does not return */
        FUN_001afa84(s_Fatal_error_005accd0,0xb,2,0xd000000000000042,0x80000000005cc450,
                     s_XnuUpcalls_XnuUpcalls_Swift_swif_005cbff0,0x21,2,0xbc8,0);
      }
      tmp = CL4_VOID_U64(FUN_001857a8());
      idx2 = tmp;
      FUN_003698b0(&idx2,0x669ae8,&dat_004e6878);
      FUN_0036993c(0x669ae8,&dat_004e6878,0,0);
      *msgbuf = tmp;
      val4 = kind;
      w6 = idx;
      val2 = errword2;
      val3 = cnt2;
      val = errword;
      w5 = cnt;
      w4 = len2;
      FUN_00025704();
    }
  }
  else {
    tmp2 = FUN_00019aac(0);
    FUN_0036993c(tmp2,FUN_0065a550,0,0);
    *msgbuf6 = len;
  }
  return;
}



/* FUN_0018a37c @ 0x0018a37c   (est. FUN_0018a37c)
 * Ghidra: uint FUN_0018a37c(undefined8 p1,undefined8 p2)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class A/V1 */
uint32_t FUN_0018a37c(uint64_t p1, uint64_t p2)
{
  char tag2;
  uint8_t tmp;
  uint64_t tmp2;
  uint32_t *msgbuf5;
  long err;
  cl4_16_t tag;
  uint8_t idx;
  uint64_t cnt2;
  uint64_t errword2;
  uint64_t cnt;
  uint64_t errword;
  uint64_t len2;
  uint64_t msgbuf6;
  uint8_t len;
  uint8_t msgbuf4 [52];
  uint32_t kind2;
  uint8_t msgbuf3 [56];
  uint8_t msgbuf2 [56];
  uint8_t msgbuf [56];
  uint64_t kind;
  uint64_t w2;
  uint64_t w1;
  uint64_t w0;
  uint64_t w7;
  uint64_t val4;
  uint8_t w6;
  uint64_t w5;
  uint64_t val3;
  uint64_t val2;
  uint64_t val;
  uint64_t w4;
  uint64_t idx2;
  uint8_t w3;
  
  FUN_00025ebc(msgbuf3,0x14,0,&kind2);
  if (err == 0) {
    thunk_FUN_00024068(msgbuf4);
    FUN_00023208(0xdf5bef7025abd0d8);
    FUN_00023208(p1);
    FUN_000231f0(p2);
    FUN_00022c48(msgbuf2);
    FUN_00025f44(msgbuf,msgbuf2,&kind2);
    FUN_000214b0(&cnt2,msgbuf);
    tag2 = FUN_000217e4();
    if (tag2 == '\0') {
      p2 = FUN_00021738();
      w2 = errword2;
      kind = cnt2;
      w0 = errword;
      w1 = cnt;
      val4 = msgbuf6;
      w7 = len2;
      w6 = len;
      FUN_00025704();
    }
    else {
      if (tag2 != '\x01') {
                    /* WARNING: Subroutine does not return */
        FUN_001afa84(s_Fatal_error_005accd0,0xb,2,0xd000000000000042,0x80000000005cc400,
                     s_XnuUpcalls_XnuUpcalls_Swift_swif_005cbff0,0x21,2,0xbd3,0);
      }
      tmp = CL4_VOID_U64(FUN_001857a8());
      idx = tmp;
      FUN_003698b0(&idx,0x669ae8,&dat_004e6878);
      tag = FUN_0036993c(0x669ae8,&dat_004e6878,0,0);
      p2 = tag._0_8_;
      tag.hi = (uint64_t)(tmp);
      val3 = errword2;
      w5 = cnt2;
      val = errword;
      val2 = cnt;
      idx2 = msgbuf6;
      w4 = len2;
      w3 = len;
      FUN_00025704();
    }
  }
  else {
    tmp2 = FUN_00019aac(0);
    FUN_0036993c(tmp2,FUN_0065a550,0,0);
    *msgbuf5 = kind2;
  }
  return (uint32_t)p2 & 1;
}



/* FUN_0018a608 @ 0x0018a608   (est. FUN_0018a608)
 * Ghidra: uint FUN_0018a608(undefined8 p1,undefined8 p2,undefined8 p3)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class A/V1 */
uint32_t FUN_0018a608(uint64_t p1, uint64_t p2, uint64_t p3)
{
  char tag2;
  uint8_t tmp;
  uint64_t tmp2;
  uint32_t *msgbuf5;
  long err;
  cl4_16_t tag;
  uint8_t val;
  uint64_t idx2;
  uint64_t kind2;
  uint64_t idx;
  uint64_t kind;
  uint64_t cnt2;
  uint64_t errword2;
  uint8_t cnt;
  uint8_t msgbuf4 [52];
  uint32_t len2;
  uint8_t msgbuf3 [56];
  uint8_t msgbuf2 [56];
  uint8_t msgbuf [56];
  uint64_t len;
  uint64_t errword;
  uint64_t msgbuf6;
  uint64_t w2;
  uint64_t w7;
  uint64_t w1;
  uint8_t w6;
  uint64_t w5;
  uint64_t w0;
  uint64_t val4;
  uint64_t val3;
  uint64_t w4;
  uint64_t val2;
  uint8_t w3;
  
  FUN_00025ebc(msgbuf3,0x20,0,&len2);
  if (err == 0) {
    thunk_FUN_00024068(msgbuf4);
    FUN_00023208(0xba0459bda81beb7e);
    FUN_00023208(p1);
    FUN_00023208(p2);
    FUN_00023208(p3);
    FUN_00022c48(msgbuf2);
    FUN_00025f44(msgbuf,msgbuf2,&len2);
    FUN_000214b0(&idx2,msgbuf);
    tag2 = FUN_000217e4();
    if (tag2 == '\0') {
      p3 = FUN_00021738();
      errword = kind2;
      len = idx2;
      w2 = kind;
      msgbuf6 = idx;
      w1 = errword2;
      w7 = cnt2;
      w6 = cnt;
      FUN_00025704();
    }
    else {
      if (tag2 != '\x01') {
                    /* WARNING: Subroutine does not return */
        FUN_001afa84(s_Fatal_error_005accd0,0xb,2,0xd00000000000003e,0x80000000005cc3c0,
                     s_XnuUpcalls_XnuUpcalls_Swift_swif_005cbff0,0x21,2,0xbe9,0);
      }
      tmp = CL4_VOID_U64(FUN_001857a8());
      val = tmp;
      FUN_003698b0(&val,0x669ae8,&dat_004e6878);
      tag = FUN_0036993c(0x669ae8,&dat_004e6878,0,0);
      p3 = tag._0_8_;
      tag.hi = (uint64_t)(tmp);
      w0 = kind2;
      w5 = idx2;
      val3 = kind;
      val4 = idx;
      val2 = errword2;
      w4 = cnt2;
      w3 = cnt;
      FUN_00025704();
    }
  }
  else {
    tmp2 = FUN_00019aac(0);
    FUN_0036993c(tmp2,FUN_0065a550,0,0);
    *msgbuf5 = len2;
  }
  return (uint32_t)p3 & 1;
}



/* FUN_0018a8ac @ 0x0018a8ac   (est. FUN_0018a8ac)
 * Ghidra: uint FUN_0018a8ac(undefined8 p1,undefined8 p2)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class A/V1 */
uint32_t FUN_0018a8ac(uint64_t p1, uint64_t p2)
{
  char tag2;
  uint8_t tmp;
  uint64_t tmp2;
  uint32_t *msgbuf5;
  long err;
  cl4_16_t tag;
  uint8_t idx;
  uint64_t cnt2;
  uint64_t errword2;
  uint64_t cnt;
  uint64_t errword;
  uint64_t len2;
  uint64_t msgbuf6;
  uint8_t len;
  uint8_t msgbuf4 [52];
  uint32_t kind2;
  uint8_t msgbuf3 [56];
  uint8_t msgbuf2 [56];
  uint8_t msgbuf [56];
  uint64_t kind;
  uint64_t w2;
  uint64_t w1;
  uint64_t w0;
  uint64_t w7;
  uint64_t val4;
  uint8_t w6;
  uint64_t w5;
  uint64_t val3;
  uint64_t val2;
  uint64_t val;
  uint64_t w4;
  uint64_t idx2;
  uint8_t w3;
  
  FUN_00025ebc(msgbuf3,0x18,0,&kind2);
  if (err == 0) {
    thunk_FUN_00024068(msgbuf4);
    FUN_00023208(0xb7aae748e04de385);
    FUN_00023208(p1);
    FUN_00023208(p2);
    FUN_00022c48(msgbuf2);
    FUN_00025f44(msgbuf,msgbuf2,&kind2);
    FUN_000214b0(&cnt2,msgbuf);
    tag2 = FUN_000217e4();
    if (tag2 == '\0') {
      p2 = FUN_00021738();
      w2 = errword2;
      kind = cnt2;
      w0 = errword;
      w1 = cnt;
      val4 = msgbuf6;
      w7 = len2;
      w6 = len;
      FUN_00025704();
    }
    else {
      if (tag2 != '\x01') {
                    /* WARNING: Subroutine does not return */
        FUN_001afa84(s_Fatal_error_005accd0,0xb,2,0xd00000000000003c,0x80000000005cc380,
                     s_XnuUpcalls_XnuUpcalls_Swift_swif_005cbff0,0x21,2,0xbf4,0);
      }
      tmp = CL4_VOID_U64(FUN_001857a8());
      idx = tmp;
      FUN_003698b0(&idx,0x669ae8,&dat_004e6878);
      tag = FUN_0036993c(0x669ae8,&dat_004e6878,0,0);
      p2 = tag._0_8_;
      tag.hi = (uint64_t)(tmp);
      val3 = errword2;
      w5 = cnt2;
      val = errword;
      val2 = cnt;
      idx2 = msgbuf6;
      w4 = len2;
      w3 = len;
      FUN_00025704();
    }
  }
  else {
    tmp2 = FUN_00019aac(0);
    FUN_0036993c(tmp2,FUN_0065a550,0,0);
    *msgbuf5 = kind2;
  }
  return (uint32_t)p2 & 1;
}



/* FUN_0018ab38 @ 0x0018ab38   (est. FUN_0018ab38)
 * Ghidra: void FUN_0018ab38(undefined8 p1,undefined8 p2)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class A/V1 */
void FUN_0018ab38(uint64_t p1, uint64_t p2)
{
  char w7;
  uint64_t tag;
  uint32_t *msgbuf5;
  long err;
  uint64_t cnt2;
  uint64_t errword2;
  uint64_t cnt;
  uint64_t errword;
  uint64_t len2;
  uint64_t msgbuf6;
  uint8_t len;
  uint8_t msgbuf4 [52];
  uint32_t kind2;
  uint8_t msgbuf3 [56];
  uint8_t msgbuf2 [56];
  uint8_t msgbuf [56];
  uint64_t kind;
  uint64_t w1;
  uint64_t w0;
  uint64_t val4;
  uint64_t w6;
  uint64_t val3;
  uint8_t w5;
  uint64_t w4;
  uint64_t val2;
  uint64_t val;
  uint64_t idx2;
  uint64_t w3;
  uint64_t idx;
  uint8_t w2;
  
  FUN_00025ebc(msgbuf3,0x14,0,&kind2);
  if (err == 0) {
    thunk_FUN_00024068(msgbuf4);
    FUN_00023208(0x19b276f97c3d433e);
    FUN_00023208(p1);
    FUN_000231f0(p2);
    FUN_00022c48(msgbuf2);
    FUN_00025f44(msgbuf,msgbuf2,&kind2);
    FUN_000214b0(&cnt2,msgbuf);
    w7 = FUN_000217e4();
    if (w7 == '\0') {
      w1 = errword2;
      kind = cnt2;
      val4 = errword;
      w0 = cnt;
      val3 = msgbuf6;
      w6 = len2;
      w5 = len;
    }
    else {
      if (w7 != '\x01') {
                    /* WARNING: Subroutine does not return */
        FUN_001afa84(s_Fatal_error_005accd0,0xb,2,0xd000000000000044,0x80000000005cc300,
                     s_XnuUpcalls_XnuUpcalls_Swift_swif_005cbff0,0x21,2,0xbff,0);
      }
      tag = CL4_VOID_U64(FUN_0018d208());
      FUN_003698b0(tag,0x669a58,&dat_004e6528);
      FUN_0036993c(0x669a58,&dat_004e6528,0,0);
      val2 = errword2;
      w4 = cnt2;
      idx2 = errword;
      val = cnt;
      idx = msgbuf6;
      w3 = len2;
      w2 = len;
    }
    FUN_00025704();
  }
  else {
    tag = FUN_00019aac(0);
    FUN_0036993c(tag,FUN_0065a550,0,0);
    *msgbuf5 = kind2;
  }
  return;
}



/* FUN_0018ada8 @ 0x0018ada8   (est. FUN_0018ada8)
 * Ghidra: ulong FUN_0018ada8(long p1)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class X/None */
uint64_t FUN_0018ada8(long p1)
{
  uint64_t w5;
  code_fn_t w4;
  uint32_t *msgbuf4;
  uint64_t msgbuf;
  uint64_t w6;
  long err;
  uint8_t msgbuf3 [56];
  long idx2;
  uint64_t idx;
  uint64_t len;
  uint64_t cnt2;
  uint64_t kind2;
  uint64_t kind;
  uint64_t errword2;
  uint64_t cnt;
  uint64_t errword;
  uint8_t len2;
  uint8_t msgbuf2 [56];
  uint8_t msgbuf6 [56];
  uint8_t msgbuf5 [56];
  uint64_t w3;
  uint64_t val4;
  uint64_t val3;
  uint64_t val2;
  uint64_t w2;
  uint64_t val;
  uint8_t w1;
  uint32_t w0;
  
  w6 = *(uint64_t *)(p1 + 0x10);
  if (0xf < w6) {
    w6 = 0x10;
  }
  FUN_00025ebc(msgbuf2,w6 + 8,0,&w0);
  if (err == 0) {
    thunk_FUN_00024068(&cnt2);
    FUN_00023208(0x60592e0ace6877ae);
    idx2 = *(long *)(p1 + 0x10);
    if (idx2 != 0x10) {
      idx = 0;
      len = 0xe000000000000000;
      FUN_002a4ab4(0x3b);
      thunk_FUN_002acbb8(0xd000000000000017,0x80000000005cc2e0);
      thunk_FUN_002acbb8(0xd000000000000037,0x80000000005c9400);
      w4 = (code_fn_t)FUN_00027724(0x6720e0);
      (*w4)(0x677880,0x6720e0);
      thunk_FUN_002acbb8();
      FUN_003a25d4(msgbuf);
                    /* WARNING: Subroutine does not return */
      FUN_001afa84(s_Fatal_error_005accd0,0xb,2,idx,len,
                   s_XnuUpcalls_XnuUpcalls_Swift_swif_005cbff0,0x21,2,0x58b,0);
    }
    FUN_000230f8(*(uint8_t *)(p1 + 0x20));
    FUN_000230f8(*(uint8_t *)(p1 + 0x21));
    FUN_000230f8(*(uint8_t *)(p1 + 0x22));
    FUN_000230f8(*(uint8_t *)(p1 + 0x23));
    FUN_000230f8(*(uint8_t *)(p1 + 0x24));
    FUN_000230f8(*(uint8_t *)(p1 + 0x25));
    FUN_000230f8(*(uint8_t *)(p1 + 0x26));
    FUN_000230f8(*(uint8_t *)(p1 + 0x27));
    FUN_000230f8(*(uint8_t *)(p1 + 0x28));
    FUN_000230f8(*(uint8_t *)(p1 + 0x29));
    FUN_000230f8(*(uint8_t *)(p1 + 0x2a));
    FUN_000230f8(*(uint8_t *)(p1 + 0x2b));
    FUN_000230f8(*(uint8_t *)(p1 + 0x2c));
    FUN_000230f8(*(uint8_t *)(p1 + 0x2d));
    FUN_000230f8(*(uint8_t *)(p1 + 0x2e));
    FUN_000230f8(*(uint8_t *)(p1 + 0x2f));
    val4 = kind2;
    w3 = cnt2;
    val2 = errword2;
    val3 = kind;
    val = errword;
    w2 = cnt;
    w1 = len2;
    FUN_00022c48(msgbuf6);
    FUN_00025f44(msgbuf5,msgbuf6,&w0);
    FUN_000214b0(msgbuf3,msgbuf5);
    w6 = FUN_00021904();
    FUN_00025704();
  }
  else {
    w6 = (uint64_t)w0;
    w5 = FUN_00019aac(0);
    FUN_0036993c(w5,FUN_0065a550,0,0);
    *msgbuf4 = w0;
  }
  return w6;
}



/* FUN_0018b094 @ 0x0018b094   (est. FUN_0018b094)
 * Ghidra: ulong FUN_0018b094(undefined8 p1,undefined8 p2)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class X/None */
uint64_t FUN_0018b094(uint64_t p1, uint64_t p2)
{
  uint64_t errword2;
  uint32_t *msgbuf3;
  uint64_t kind;
  long err;
  uint8_t msgbuf2 [56];
  uint8_t msgbuf [52];
  uint32_t errword;
  uint8_t msgbuf6 [56];
  uint8_t msgbuf5 [56];
  uint8_t msgbuf4 [56];
  
  FUN_00025ebc(msgbuf6,0x14,0,&errword);
  if (err == 0) {
    thunk_FUN_00024068(msgbuf);
    FUN_00023208(0x3775303ceb7f21d1);
    FUN_00023208(p1);
    FUN_000231f0(p2);
    FUN_00022c48(msgbuf5);
    FUN_00025f44(msgbuf4,msgbuf5,&errword);
    FUN_000214b0(msgbuf2,msgbuf4);
    kind = FUN_00021904();
    FUN_00025704();
  }
  else {
    kind = (uint64_t)errword;
    errword2 = FUN_00019aac(0);
    FUN_0036993c(errword2,FUN_0065a550,0,0);
    *msgbuf3 = errword;
  }
  return kind;
}



/* FUN_0018b1bc @ 0x0018b1bc   (est. thunk -> ?)
 * Ghidra: void FUN_0018b1bc(undefined8 p1)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_0018b1bc(uint64_t p1)
{
    ;
}



/* FUN_0018b1e4 @ 0x0018b1e4   (est. FUN_0018b1e4)
 * Ghidra: ulong FUN_0018b1e4(undefined8 p1,undefined8 p2)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class X/None */
uint64_t FUN_0018b1e4(uint64_t p1, uint64_t p2)
{
  uint64_t errword2;
  uint32_t *msgbuf3;
  uint64_t kind;
  long err;
  uint8_t msgbuf2 [56];
  uint8_t msgbuf [52];
  uint32_t errword;
  uint8_t msgbuf6 [56];
  uint8_t msgbuf5 [56];
  uint8_t msgbuf4 [56];
  
  FUN_00025ebc(msgbuf6,0x10,0,&errword);
  if (err == 0) {
    thunk_FUN_00024068(msgbuf);
    FUN_00023208(p2);
    FUN_00023208(p1);
    FUN_00022c48(msgbuf5);
    FUN_00025f44(msgbuf4,msgbuf5,&errword);
    FUN_000214b0(msgbuf2,msgbuf4);
    kind = FUN_00021904();
    FUN_00025704();
  }
  else {
    kind = (uint64_t)errword;
    errword2 = FUN_00019aac(0);
    FUN_0036993c(errword2,FUN_0065a550,0,0);
    *msgbuf3 = errword;
  }
  return kind;
}



/* FUN_0018b2f4 @ 0x0018b2f4   (est. FUN_0018b2f4)
 * Ghidra: void FUN_0018b2f4(undefined8 *p1,undefined8 p2)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class A/V1 */
void FUN_0018b2f4(uint64_t *p1, uint64_t p2)
{
  char tmp2;
  uint8_t tmp3;
  uint64_t tmp4;
  uint32_t *msgbuf6;
  uint8_t *msgbuf;
  long err;
  uint8_t val2;
  uint64_t len;
  uint64_t kind2;
  uint64_t val;
  uint64_t kind;
  uint64_t idx2;
  uint64_t errword2;
  uint64_t idx;
  uint64_t errword;
  uint8_t cnt2;
  uint8_t msgbuf5 [52];
  uint32_t cnt;
  uint8_t msgbuf4 [56];
  uint8_t msgbuf3 [56];
  uint8_t msgbuf2 [56];
  uint64_t len2;
  uint64_t w5;
  uint64_t w4;
  uint64_t w3;
  uint64_t tmp;
  uint64_t w2;
  uint8_t tag2;
  uint64_t tag;
  uint64_t w1;
  uint64_t w0;
  uint64_t val4;
  uint64_t w7;
  uint64_t val3;
  uint8_t w6;
  
  FUN_00025ebc(msgbuf4,0xc,0,&cnt);
  if (err == 0) {
    thunk_FUN_00024068(msgbuf5);
    FUN_00023208(0x68468bdf5f358397);
    FUN_000231f0(p2);
    FUN_00022c48(msgbuf3);
    FUN_00025f44(msgbuf2,msgbuf3,&cnt);
    FUN_000214b0(&val,msgbuf2);
    tmp2 = FUN_000217e4();
    if (tmp2 == '\x01') {
      tmp3 = FUN_0018d304();
      val2 = tmp3;
      FUN_003698b0(&val2,0x6699c8,&dat_004e65a8);
      FUN_0036993c(0x6699c8,&dat_004e65a8,0,0);
      *msgbuf = tmp3;
      w1 = kind;
      tag = val;
      val4 = errword2;
      w0 = idx2;
      val3 = errword;
      w7 = idx;
      w6 = cnt2;
      FUN_00025704();
    }
    else {
      if (tmp2 != '\0') {
                    /* WARNING: Subroutine does not return */
        FUN_001afa84(s_Fatal_error_005accd0,0xb,2,0xd000000000000041,0x80000000005cc290,
                     s_XnuUpcalls_XnuUpcalls_Swift_swif_005cbff0,0x21,2,0xc0a,0);
      }
      FUN_000268d0(&val2,0x669540,0x65a688,0x669540,0x65a5e8,(uint64_t)0x669608,&cnt);
      p1[1] = kind2;
      *p1 = CONCAT71(len,val2);
      w5 = kind;
      len2 = val;
      w3 = errword2;
      w4 = idx2;
      w2 = errword;
      tmp = idx;
      tag2 = cnt2;
      FUN_00025704();
    }
  }
  else {
    tmp4 = FUN_00019aac(0);
    FUN_0036993c(tmp4,FUN_0065a550,0,0);
    *msgbuf6 = cnt;
  }
  return;
}



/* FUN_0018b5c4 @ 0x0018b5c4   (est. FUN_0018b5c4)
 * Ghidra: void FUN_0018b5c4(undefined8 p1)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class A/V1 */
void FUN_0018b5c4(uint64_t p1)
{
  char tag2;
  uint8_t tmp;
  uint64_t tmp2;
  uint32_t *msgbuf6;
  uint8_t *msgbuf;
  long err;
  uint8_t idx2;
  uint64_t idx;
  uint64_t kind;
  uint64_t cnt2;
  uint64_t errword2;
  uint64_t cnt;
  uint64_t errword;
  uint8_t len2;
  uint8_t msgbuf5 [52];
  uint32_t len;
  uint8_t msgbuf4 [56];
  uint8_t msgbuf3 [56];
  uint8_t msgbuf2 [56];
  uint64_t kind2;
  uint64_t w3;
  uint64_t w2;
  uint64_t w1;
  uint64_t tag;
  uint64_t w0;
  uint8_t w7;
  uint64_t w6;
  uint64_t val4;
  uint64_t val3;
  uint64_t val2;
  uint64_t w5;
  uint64_t val;
  uint8_t w4;
  
  FUN_00025ebc(msgbuf4,0xc,0,&len);
  if (err == 0) {
    thunk_FUN_00024068(msgbuf5);
    FUN_00023208(0x662abd4b0b018fe0);
    FUN_000231f0(p1);
    FUN_00022c48(msgbuf3);
    FUN_00025f44(msgbuf2,msgbuf3,&len);
    FUN_000214b0(&idx,msgbuf2);
    tag2 = FUN_000217e4();
    if (tag2 == '\0') {
      w3 = kind;
      kind2 = idx;
      w1 = errword2;
      w2 = cnt2;
      w0 = errword;
      tag = cnt;
      w7 = len2;
      FUN_00025704();
    }
    else {
      if (tag2 != '\x01') {
                    /* WARNING: Subroutine does not return */
        FUN_001afa84(s_Fatal_error_005accd0,0xb,2,0xd00000000000003e,0x80000000005cc250,
                     s_XnuUpcalls_XnuUpcalls_Swift_swif_005cbff0,0x21,2,0xc15,0);
      }
      tmp = FUN_0018d304();
      idx2 = tmp;
      FUN_003698b0(&idx2,0x6699c8,&dat_004e65a8);
      FUN_0036993c(0x6699c8,&dat_004e65a8,0,0);
      *msgbuf = tmp;
      val4 = kind;
      w6 = idx;
      val2 = errword2;
      val3 = cnt2;
      val = errword;
      w5 = cnt;
      w4 = len2;
      FUN_00025704();
    }
  }
  else {
    tmp2 = FUN_00019aac(0);
    FUN_0036993c(tmp2,FUN_0065a550,0,0);
    *msgbuf6 = len;
  }
  return;
}



/* FUN_0018b830 @ 0x0018b830   (est. FUN_0018b830)
 * Ghidra: void FUN_0018b830(undefined8 *p1,undefined8 p2)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class A/V1 */
void FUN_0018b830(uint64_t *p1, uint64_t p2)
{
  void *ptr3;
  char ptr4;
  uint8_t h2;
  long h;
  uint32_t *msgbuf5;
  uint8_t *msgbuf;
  long err;
  uint64_t h3;
  uint8_t tag;
  uint64_t w7;
  uint64_t idx2;
  uint64_t w6;
  uint64_t idx;
  uint64_t w5;
  uint64_t cnt2;
  uint8_t w4;
  uint64_t w3;
  uint64_t cnt;
  uint64_t len2;
  uint64_t len;
  uint64_t w2;
  uint64_t kind2;
  uint8_t w1;
  uint32_t w0;
  uint8_t msgbuf4 [56];
  uint8_t msgbuf3 [56];
  uint8_t msgbuf2 [56];
  uint64_t val4;
  uint64_t val3;
  uint64_t kind;
  uint64_t errword2;
  uint64_t errword;
  uint64_t val2;
  uint64_t msgbuf6;
  uint8_t val;
  uint64_t ptr2;
  uint64_t tmp3;
  uint64_t tmp2;
  uint64_t tmp;
  uint64_t ptr;
  uint64_t tag2;
  uint8_t tmp4;
  
  h3 = *p1;
  w3 = h3;
  h = FUN_00026754(&w3,&dat_006695c0,0x669628);
  if (SCARRY8(h,8)) {
                    /* WARNING: Does not return */
    cl4_break(0x18bb5c);
  }
  if (!SCARRY8(h + 8,4)) {
    FUN_00025ebc(msgbuf4,h + 0xc,0,&w0);
    if (err == 0) {
      thunk_FUN_00024068(&w3);
      FUN_00023208(0xffd7e6f3a80bf0d8);
      w7 = h3;
      FUN_000267d4(&w7,0x65a870,&dat_006695c0,0x65a798,0x669628);
      FUN_000231f0(p2);
      tmp3 = cnt;
      ptr2 = w3;
      tmp = len;
      tmp2 = len2;
      tag2 = kind2;
      ptr = w2;
      tmp4 = w1;
      FUN_00022c48(msgbuf3);
      FUN_00025f44(msgbuf2,msgbuf3,&w0);
      FUN_000214b0(&w7,msgbuf2);
      ptr4 = FUN_000217e4();
      if (ptr4 == '\0') {
        val4 = w7;
        FUN_00025704();
      }
      else {
        if (ptr4 != '\x01') {
                    /* WARNING: Subroutine does not return */
          FUN_001afa84(s_Fatal_error_005accd0,0xb,2,0xd000000000000044,0x80000000005cc1d0,
                       s_XnuUpcalls_XnuUpcalls_Swift_swif_005cbff0,0x21,2,0xc20,0);
        }
        h2 = FUN_0018d304();
        tag = h2;
        FUN_003698b0(&tag,0x6699c8,&dat_004e65a8);
        FUN_0036993c(0x6699c8,&dat_004e65a8,0,0);
        *msgbuf = h2;
        kind = idx2;
        val3 = w7;
        errword = idx;
        errword2 = w6;
        msgbuf6 = cnt2;
        val2 = w5;
        val = w4;
        FUN_00025704();
      }
    }
    else {
      h3 = FUN_00019aac(0);
      FUN_0036993c(h3,FUN_0065a550,0,0);
      *msgbuf5 = w0;
    }
    return;
  }
                    /* WARNING: Does not return */
  cl4_break(0x18bb60);
}



/* FUN_0018bbac @ 0x0018bbac   (est. FUN_0018bbac)
 * Ghidra: void FUN_0018bbac(undefined8 p1,undefined8 p2,undefined8 p3)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class D/None */
void FUN_0018bbac(uint64_t p1, uint64_t p2, uint64_t p3)
{
  uint64_t msgbuf2;
  uint64_t msgbuf3;
  code_fn_t msgbuf;
  uint64_t *cpu;
  uint64_t msgbuf4;
  
  msgbuf2 = *cpu;
  msgbuf3 = cpu[1];
  msgbuf4 = cpu[2];
  msgbuf = (code_fn_t)FUN_00023c78(p3);
  (*msgbuf)(msgbuf2,p2,p3);
  (*msgbuf)(msgbuf3,p2,p3);
  (*msgbuf)(msgbuf4,p2,p3);
  return;
}



/* FUN_0018bc58 @ 0x0018bc58   (est. FUN_0018bc58)
 * Ghidra: 
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class D/None */
void FUN_0018bc58(uint64_t *p1, uint64_t p2, uint64_t p3, uint64_t p4, uint64_t *p5)
{
  code_fn_t msgbuf;
  uint64_t msgbuf2;
  uint64_t msgbuf3;
  uint64_t msgbuf4;
  long err;
  
  msgbuf = (code_fn_t)FUN_00023d00(p4);
  msgbuf2 = (*msgbuf)(p3,p4);
  msgbuf3 = (*msgbuf)(p3,p4);
  msgbuf4 = (*msgbuf)(p3,p4);
  if (err == 0) {
    *p1 = msgbuf2;
    p1[1] = msgbuf3;
    p1[2] = msgbuf4;
  }
  else {
    *p5 = (int)msgbuf2;
  }
  return;
}



/* FUN_0018bd0c @ 0x0018bd0c   (est. FUN_0018bd0c)
 * Ghidra: void FUN_0018bd0c(void)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class X/None */
void FUN_0018bd0c(void)
{
  uint32_t *in_x3;
  long err;
  uint32_t msgbuf;
  
  FUN_0018bc58(0,0,0,0,0);
  if (err != 0) {
    *in_x3 = msgbuf;
  }
  return;
}



/* FUN_0018bd44 @ 0x0018bd44   (est. FUN_0018bd44)
 * Ghidra: undefined4 FUN_0018bd44(void)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class X/None */
uint32_t FUN_0018bd44(void)
{
  uint32_t msgbuf;
  long err;
  
  msgbuf = CL4_VOID_U64(FUN_0018bbac(0,0,0));
  if (err == 0) {
    msgbuf = 1;
  }
  return msgbuf;
}



/* FUN_0018bd48 @ 0x0018bd48   (est. FUN_0018bd48)
 * Ghidra: undefined4 FUN_0018bd48(void)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class X/None */
uint32_t FUN_0018bd48(void)
{
  uint32_t msgbuf;
  long err;
  
  msgbuf = CL4_VOID_U64(FUN_0018bbac(0,0,0));
  if (err == 0) {
    msgbuf = 1;
  }
  return msgbuf;
}



/* FUN_0018bd6c @ 0x0018bd6c   (est. FUN_0018bd6c)
 * Ghidra: void FUN_0018bd6c(void)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class X/None */
void FUN_0018bd6c(void)
{
  uint8_t msgbuf2;
  uint8_t *cpu;
  uint8_t msgbuf [72];
  
  msgbuf2 = *cpu;
  FUN_001a84f4(msgbuf,0);
  FUN_0022995c(*(uint32_t *)(&dat_004e68c4 + (uint64_t)msgbuf2 * 4));
  FUN_001a8564();
  return;
}



/* FUN_0018bdbc @ 0x0018bdbc   (est. FUN_0018bdbc)
 * Ghidra: void FUN_0018bdbc(undefined8 p1)
 * Small upcall / message-register marshalling helper. Confidence: medium
 * Notes: part of the XNU upcall layer. */
void FUN_0018bdbc(uint64_t v)
{
    FUN_0022995c(v, *(uint32_t *)(dat_004e68c4 + (uint64_t)*per_cpu * 4));
}


/* FUN_0018bdf4 @ 0x0018bdf4   (est. FUN_0018bdf4)
 * Ghidra: void FUN_0018bdf4(void)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class X/None */
void FUN_0018bdf4(void)
{
  uint8_t msgbuf2;
  uint8_t *cpu;
  uint8_t msgbuf [72];
  
  msgbuf2 = *cpu;
  FUN_001a84f4(msgbuf);
  FUN_0022995c(*(uint32_t *)(&dat_004e68c4 + (uint64_t)msgbuf2 * 4));
  FUN_001a8564();
  return;
}



/* FUN_0018be40 @ 0x0018be40   (est. FUN_0018be40)
 * Ghidra: void FUN_0018be40(undefined1 *p1,undefined4 *p2)
 * Small upcall / message-register marshalling helper. Confidence: medium
 * Notes: part of the XNU upcall layer. */
void FUN_0018be40(uint8_t *out, uint32_t *arg)
{
    /* Classifies the upcall kind: FUN_0018deb8(*arg), stored to *out. */
    *out = FUN_0018deb8(*arg);
}


/* FUN_0018be84 @ 0x0018be84   (est. FUN_0018be84)
 * Ghidra: void FUN_0018be84(undefined8 p1,undefined8 p2)
 * Small upcall / message-register marshalling helper. Confidence: medium
 * Notes: part of the XNU upcall layer. */
void FUN_0018be84(uint64_t a, uint64_t b)
{
    uint64_t st = FUN_0002142c();
    FUN_00208478(a, b, (uint64_t)&dat_004e6468, st);
}


/* FUN_0018bed8 @ 0x0018bed8   (est. FUN_0018bed8)
 * Ghidra: void FUN_0018bed8(undefined8 p1,undefined8 p2)
 * Small upcall / message-register marshalling helper. Confidence: medium
 * Notes: part of the XNU upcall layer. */
void FUN_0018bed8(uint64_t a, uint64_t b)
{
    uint64_t st = FUN_0002142c();
    FUN_00208478(a, b, (uint64_t)&dat_004e64c8, st);
}


/* FUN_0018bf2c @ 0x0018bf2c   (est. FUN_0018bf2c)
 * Ghidra: undefined4 FUN_0018bf2c(undefined8 p1,undefined8 p2,undefined8 p3)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class X/None */
uint32_t FUN_0018bf2c(uint64_t p1, uint64_t p2, uint64_t p3)
{
  uint32_t msgbuf;
  uint8_t *cpu;
  long err;
  
  msgbuf = CL4_VOID_U64(FUN_0018bf78(p1,(uint64_t)*cpu | (uint64_t)*(uint32_t *)(cpu + 4) << 0x20,
                       *(uint32_t *)(cpu + 8),p2));
  if (err == 0) {
    msgbuf = 1;
  }
  return msgbuf;
}



/* FUN_0018bf78 @ 0x0018bf78   (est. FUN_0018bf78)
 * Ghidra: void FUN_0018bf78(ulong p1,undefined8 p2,undefined8 p3,undefined8 p4)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class X/None */
void FUN_0018bf78(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4)
{
  code_fn_t msgbuf;
  long err;
  
  msgbuf = (code_fn_t)FUN_000bd0e4(p4);
  (*msgbuf)((uint32_t)p1 & 0xff,p3,p4);
  if (err == 0) {
    msgbuf = (code_fn_t)FUN_000bd0e4(p4);
    (*msgbuf)(p1 >> 0x20,p3,p4);
    (*msgbuf)(p2,p3,p4);
  }
  return;
}



/* FUN_0018c020 @ 0x0018c020   (est. FUN_0018c020)
 * Ghidra: 
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class X/None */
void FUN_0018c020(uint64_t *p1, uint64_t p2, uint64_t p3, uint64_t p4, uint64_t *p5)
{
  long err;
  cl4_16_t msgbuf;
  
  msgbuf = (cl4_16_t){ .lo = FUN_0018c078(p3,p4), .hi = 0 };
  if (err == 0) {
    *p1 = msgbuf.lo;
    *(int *)(p1 + 4) = msgbuf._4_4_;
    *(int *)(p1 + 8) = msgbuf._8_4_;
  }
  else {
    *p5 = msgbuf._0_4_;
  }
  return;
}



/* FUN_0018c078 @ 0x0018c078   (est. FUN_0018c078)
 * Ghidra: ulong FUN_0018c078(undefined8 p1,undefined8 p2)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class X/None */
uint64_t FUN_0018c078(uint64_t p1, uint64_t p2)
{
  uint32_t msgbuf3;
  uint64_t msgbuf4;
  code_fn_t msgbuf;
  long msgbuf2;
  long err;
  
  msgbuf3 = CL4_VOID_U64(FUN_0018d0e4(0,0));
  if (err == 0) {
    msgbuf = (code_fn_t)FUN_001477c4(p2);
    msgbuf2 = (*msgbuf)(p1,p2);
    (*msgbuf)(p1,p2);
    msgbuf4 = (uint64_t)(msgbuf3 & 0xff) | msgbuf2 << 0x20;
  }
  else {
    msgbuf4 = (uint64_t)msgbuf3;
  }
  return msgbuf4;
}



/* FUN_0018c108 @ 0x0018c108   (est. FUN_0018c108)
 * Ghidra: void FUN_0018c108(void)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class X/None */
void FUN_0018c108(void)
{
  uint32_t *in_x3;
  long err;
  uint32_t msgbuf;
  
  FUN_0018c020(0,0,0,0,0);
  if (err != 0) {
    *in_x3 = msgbuf;
  }
  return;
}



/* FUN_0018c140 @ 0x0018c140   (est. FUN_0018c140)
 * Ghidra: undefined4 FUN_0018c140(void)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class X/None */
uint32_t FUN_0018c140(void)
{
  uint32_t msgbuf;
  long err;
  
  msgbuf = FUN_0018bf2c(0,0,0);
  if (err == 0) {
    msgbuf = 1;
  }
  return msgbuf;
}



/* FUN_0018c144 @ 0x0018c144   (est. FUN_0018c144)
 * Ghidra: undefined4 FUN_0018c144(void)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class X/None */
uint32_t FUN_0018c144(void)
{
  uint32_t msgbuf;
  long err;
  
  msgbuf = FUN_0018bf2c(0,0,0);
  if (err == 0) {
    msgbuf = 1;
  }
  return msgbuf;
}



/* FUN_0018c168 @ 0x0018c168   (est. FUN_0018c168)
 * Ghidra: void FUN_0018c168(undefined8 p1,undefined8 p2)
 * Small upcall / message-register marshalling helper. Confidence: medium
 * Notes: part of the XNU upcall layer. */
void FUN_0018c168(uint64_t a, uint64_t b)
{
    uint64_t st = FUN_0002142c();
    FUN_00208478(a, b, (uint64_t)&dat_004e6548, st);
}


/* FUN_0018c1bc @ 0x0018c1bc   (est. FUN_0018c1bc)
 * Ghidra: void FUN_0018c1bc(undefined8 p1,undefined8 p2)
 * Small upcall / message-register marshalling helper. Confidence: medium
 * Notes: part of the XNU upcall layer. */
void FUN_0018c1bc(uint64_t a, uint64_t b)
{
    uint64_t st = FUN_0002142c();
    FUN_00208478(a, b, (uint64_t)&dat_004e65c8, st);
}


/* FUN_0018c214 @ 0x0018c214   (est. FUN_0018c214)
 * Ghidra: undefined4 FUN_0018c214(undefined8 p1,undefined8 p2,undefined8 p3)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class X/None */
uint32_t FUN_0018c214(uint64_t p1, uint64_t p2, uint64_t p3)
{
  uint32_t msgbuf;
  uint64_t msgbuf2;
  uint64_t *cpu;
  long err;
  uint64_t msgbuf3;
  
  msgbuf3 = *cpu;
  msgbuf2 = FUN_0036b270(msgbuf3);
  msgbuf = CL4_VOID_U64(FUN_0018c3cc(msgbuf2,p2,p3));
  FUN_0036b118(msgbuf3);
  if (err == 0) {
    msgbuf = 1;
  }
  return msgbuf;
}



/* FUN_0018c288 @ 0x0018c288   (est. FUN_0018c288)
 * Ghidra: void FUN_0018c288(long p1)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class X/None */
void FUN_0018c288(long p1)
{
  code_fn_t msgbuf2;
  uint64_t msgbuf;
  long msgbuf3;
  
  if (*(long *)(p1 + 0x10) == 0x20) {
    msgbuf3 = 0;
    do {
      FUN_00023208(*(uint64_t *)(p1 + 0x20 + msgbuf3));
      msgbuf3 = msgbuf3 + 8;
    } while (msgbuf3 != 0x100);
    return;
  }
  FUN_002a4ab4(0x3b);
  thunk_FUN_002acbb8(0x5f2865646f636e65,0xea0000000000293a);
  thunk_FUN_002acbb8(0xd000000000000037,0x80000000005cc150);
  msgbuf2 = (code_fn_t)FUN_00027724(0x6720e0);
  (*msgbuf2)(0x677880,0x6720e0);
  thunk_FUN_002acbb8();
  FUN_003a25d4(msgbuf);
                    /* WARNING: Subroutine does not return */
  FUN_001afa84(s_Fatal_error_005accd0,0xb,2,0,0xe000000000000000,
               s_XnuUpcalls_XnuUpcalls_Swift_swif_005cbff0,0x21,2,0xc69,0);
}



/* FUN_0018c3cc @ 0x0018c3cc   (est. FUN_0018c3cc)
 * Ghidra: void FUN_0018c3cc(long p1,undefined8 p2,undefined8 p3)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class D/None */
void FUN_0018c3cc(long p1, uint64_t p2, uint64_t p3)
{
  code_fn_t msgbuf2;
  uint64_t msgbuf;
  long msgbuf3;
  
  if (*(long *)(p1 + 0x10) == 0x20) {
    msgbuf2 = (code_fn_t)FUN_00023c78(p3);
    msgbuf3 = 0;
    do {
      (*msgbuf2)(*(uint64_t *)(p1 + 0x20 + msgbuf3),p2,p3);
      msgbuf3 = msgbuf3 + 8;
    } while (msgbuf3 != 0x100);
    return;
  }
  FUN_002a4ab4(0x3b);
  thunk_FUN_002acbb8(0x5f2865646f636e65,0xea0000000000293a);
  thunk_FUN_002acbb8(0xd000000000000037,0x80000000005cc150);
  msgbuf2 = (code_fn_t)FUN_00027724(0x6720e0);
  (*msgbuf2)(0x677880,0x6720e0);
  thunk_FUN_002acbb8();
  FUN_003a25d4(msgbuf);
                    /* WARNING: Subroutine does not return */
  FUN_001afa84(s_Fatal_error_005accd0,0xb,2,0,0xe000000000000000,
               s_XnuUpcalls_XnuUpcalls_Swift_swif_005cbff0,0x21,2,0xc69,0);
}



/* FUN_0018c540 @ 0x0018c540   (est. FUN_0018c540)
 * Ghidra: 
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class X/None */
void FUN_0018c540(uint64_t *p1, uint64_t p2, uint64_t p3, uint64_t p4, uint64_t *p5)
{
  uint64_t msgbuf;
  long err;
  
  msgbuf = (uint64_t)FUN_0018c660(p3,p4);
  if (err == 0) {
    *p1 = msgbuf;
    p1[1] = msgbuf;
    FUN_0036b270();
  }
  else {
    *p5 = (int)msgbuf;
  }
  return;
}



/* FUN_0018c594 @ 0x0018c594   (est. FUN_0018c594)
 * Ghidra: undefined * FUN_0018c594(void)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class X/None */
void * FUN_0018c594(void)
{
  uint64_t msgbuf2;
  uint64_t msgbuf3;
  uint64_t msgbuf4;
  long msgbuf;
  
  msgbuf = 0x20;
  FUN_00082484(0,0x20,0);
  do {
    msgbuf4 = FUN_00021904();
    msgbuf3 = dat_00657788;
    msgbuf2 = dat_00657788 + 1;
    if (dat_00657790 >> 1 <= dat_00657788) {
      FUN_00082484(1 < dat_00657790,msgbuf2,1);
    }
    dat_00657788 = msgbuf2;
    (&dat_00657798)[msgbuf3] = msgbuf4;
    msgbuf = msgbuf + -1;
  } while (msgbuf != 0);
  return &dat_00657778;
}



/* FUN_0018c660 @ 0x0018c660   (est. FUN_0018c660)
 * Ghidra: undefined * FUN_0018c660(undefined8 p1,undefined8 p2)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class D/None */
void * FUN_0018c660(uint64_t p1, uint64_t p2)
{
  uint64_t msgbuf3;
  uint64_t msgbuf4;
  code_fn_t msgbuf;
  uint64_t msgbuf5;
  long msgbuf2;
  
  msgbuf2 = 0x20;
  FUN_00082484(0,0x20,0);
  do {
    msgbuf = (code_fn_t)FUN_00023d00(p2);
    msgbuf5 = (*msgbuf)(p1,p2);
    msgbuf4 = dat_00657788;
    msgbuf3 = dat_00657788 + 1;
    if (dat_00657790 >> 1 <= dat_00657788) {
      FUN_00082484(1 < dat_00657790,msgbuf3,1);
    }
    dat_00657788 = msgbuf3;
    (&dat_00657798)[msgbuf4] = msgbuf5;
    msgbuf2 = msgbuf2 + -1;
  } while (msgbuf2 != 0);
  return &dat_00657778;
}



/* FUN_0018c754 @ 0x0018c754   (est. FUN_0018c754)
 * Ghidra: void FUN_0018c754(void)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class X/None */
void FUN_0018c754(void)
{
  uint32_t *in_x3;
  long err;
  uint32_t msgbuf;
  
  FUN_0018c540(0,0,0,0,0);
  if (err != 0) {
    *in_x3 = msgbuf;
  }
  return;
}



/* FUN_0018c78c @ 0x0018c78c   (est. FUN_0018c78c)
 * Ghidra: undefined4 FUN_0018c78c(void)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class X/None */
uint32_t FUN_0018c78c(void)
{
  uint32_t msgbuf;
  long err;
  
  msgbuf = FUN_0018c214(0,0,0);
  if (err == 0) {
    msgbuf = 1;
  }
  return msgbuf;
}



/* FUN_0018c790 @ 0x0018c790   (est. FUN_0018c790)
 * Ghidra: undefined4 FUN_0018c790(void)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class X/None */
uint32_t FUN_0018c790(void)
{
  uint32_t msgbuf;
  long err;
  
  msgbuf = FUN_0018c214(0,0,0);
  if (err == 0) {
    msgbuf = 1;
  }
  return msgbuf;
}



/* FUN_0018c7b8 @ 0x0018c7b8   (est. FUN_0018c7b8)
 * Ghidra: undefined4 FUN_0018c7b8(undefined8 p1,undefined8 p2,undefined8 p3)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class X/None */
uint32_t FUN_0018c7b8(uint64_t p1, uint64_t p2, uint64_t p3)
{
  uint32_t msgbuf;
  uint64_t msgbuf2;
  uint64_t *cpu;
  long err;
  uint64_t msgbuf3;
  
  msgbuf3 = *cpu;
  msgbuf2 = FUN_0036b270(msgbuf3);
  msgbuf = CL4_VOID_U64(FUN_0018c968(msgbuf2,p2,p3));
  FUN_0036b118(msgbuf3);
  if (err == 0) {
    msgbuf = 1;
  }
  return msgbuf;
}



/* FUN_0018c82c @ 0x0018c82c   (est. FUN_0018c82c)
 * Ghidra: void FUN_0018c82c(long p1)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class X/None */
void FUN_0018c82c(long p1)
{
  code_fn_t msgbuf2;
  uint64_t msgbuf;
  
  if (*(long *)(p1 + 0x10) == 2) {
    FUN_00023208(*(uint64_t *)(p1 + 0x20));
    FUN_00023208(*(uint64_t *)(p1 + 0x28));
    return;
  }
  FUN_002a4ab4(0x3a);
  thunk_FUN_002acbb8(0x5f2865646f636e65,0xea0000000000293a);
  thunk_FUN_002acbb8(0xd000000000000036,0x80000000005cc190);
  msgbuf2 = (code_fn_t)FUN_00027724(0x6720e0);
  (*msgbuf2)(0x677880,0x6720e0);
  thunk_FUN_002acbb8();
  FUN_003a25d4(msgbuf);
                    /* WARNING: Subroutine does not return */
  FUN_001afa84(s_Fatal_error_005accd0,0xb,2,0,0xe000000000000000,
               s_XnuUpcalls_XnuUpcalls_Swift_swif_005cbff0,0x21,2,0xc71,0);
}



/* FUN_0018c968 @ 0x0018c968   (est. FUN_0018c968)
 * Ghidra: void FUN_0018c968(long p1,undefined8 p2,undefined8 p3)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class D/None */
void FUN_0018c968(long p1, uint64_t p2, uint64_t p3)
{
  code_fn_t msgbuf2;
  uint64_t msgbuf;
  
  if (*(long *)(p1 + 0x10) == 2) {
    msgbuf2 = (code_fn_t)FUN_00023c78(p3);
    (*msgbuf2)(*(uint64_t *)(p1 + 0x20),p2,p3);
    (*msgbuf2)(*(uint64_t *)(p1 + 0x28),p2,p3);
    return;
  }
  FUN_002a4ab4(0x3a);
  thunk_FUN_002acbb8(0x5f2865646f636e65,0xea0000000000293a);
  thunk_FUN_002acbb8(0xd000000000000036,0x80000000005cc190);
  msgbuf2 = (code_fn_t)FUN_00027724(0x6720e0);
  (*msgbuf2)(0x677880,0x6720e0);
  thunk_FUN_002acbb8();
  FUN_003a25d4(msgbuf);
                    /* WARNING: Subroutine does not return */
  FUN_001afa84(s_Fatal_error_005accd0,0xb,2,0,0xe000000000000000,
               s_XnuUpcalls_XnuUpcalls_Swift_swif_005cbff0,0x21,2,0xc71,0);
}



/* FUN_0018cad4 @ 0x0018cad4   (est. FUN_0018cad4)
 * Ghidra: 
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class X/None */
void FUN_0018cad4(uint64_t *p1, uint64_t p2, uint64_t p3, uint64_t p4, uint64_t *p5)
{
  uint64_t msgbuf;
  long err;
  
  msgbuf = (uint64_t)FUN_0018cc2c(p3,p4);
  if (err == 0) {
    *p1 = msgbuf;
  }
  else {
    *p5 = (int)msgbuf;
  }
  return;
}



/* FUN_0018cb24 @ 0x0018cb24   (est. FUN_0018cb24)
 * Ghidra: undefined * FUN_0018cb24(void)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class X/None */
void * FUN_0018cb24(void)
{
  uint64_t msgbuf2;
  long msgbuf;
  uint64_t msgbuf3;
  uint64_t msgbuf4;
  
  FUN_00082484(0,2,0);
  msgbuf4 = FUN_00021904();
  msgbuf3 = dat_00657788;
  msgbuf2 = dat_00657788 + 1;
  if (dat_00657790 >> 1 <= dat_00657788) {
    FUN_00082484(1 < dat_00657790,msgbuf2,1);
  }
  dat_00657788 = msgbuf2;
  (&dat_00657798)[msgbuf3] = msgbuf4;
  msgbuf4 = FUN_00021904();
  msgbuf2 = dat_00657788;
  msgbuf = dat_00657788 + 1;
  if (dat_00657790 >> 1 <= dat_00657788) {
    FUN_00082484(1 < dat_00657790,msgbuf,1);
  }
  dat_00657788 = msgbuf;
  (&dat_00657798)[msgbuf2] = msgbuf4;
  return &dat_00657778;
}



/* FUN_0018cc2c @ 0x0018cc2c   (est. FUN_0018cc2c)
 * Ghidra: undefined * FUN_0018cc2c(undefined8 p1,undefined8 p2)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class D/None */
void * FUN_0018cc2c(uint64_t p1, uint64_t p2)
{
  uint64_t msgbuf3;
  long msgbuf2;
  uint64_t msgbuf4;
  code_fn_t msgbuf;
  uint64_t msgbuf5;
  
  FUN_00082484(0,2,0);
  msgbuf = (code_fn_t)FUN_00023d00(p2);
  msgbuf5 = (*msgbuf)(p1,p2);
  msgbuf4 = dat_00657788;
  msgbuf3 = dat_00657788 + 1;
  if (dat_00657790 >> 1 <= dat_00657788) {
    FUN_00082484(1 < dat_00657790,msgbuf3,1);
  }
  dat_00657788 = msgbuf3;
  (&dat_00657798)[msgbuf4] = msgbuf5;
  msgbuf = (code_fn_t)FUN_00023d00(p2);
  msgbuf5 = (*msgbuf)(p1,p2);
  msgbuf3 = dat_00657788;
  msgbuf2 = dat_00657788 + 1;
  if (dat_00657790 >> 1 <= dat_00657788) {
    FUN_00082484(1 < dat_00657790,msgbuf2,1);
  }
  dat_00657788 = msgbuf2;
  (&dat_00657798)[msgbuf3] = msgbuf5;
  return &dat_00657778;
}



/* FUN_0018cd78 @ 0x0018cd78   (est. FUN_0018cd78)
 * Ghidra: void FUN_0018cd78(void)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class X/None */
void FUN_0018cd78(void)
{
  uint32_t *in_x3;
  long err;
  uint32_t msgbuf;
  
  FUN_0018cad4(0,0,0,0,0);
  if (err != 0) {
    *in_x3 = msgbuf;
  }
  return;
}



/* FUN_0018cdb0 @ 0x0018cdb0   (est. FUN_0018cdb0)
 * Ghidra: undefined4 FUN_0018cdb0(void)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class X/None */
uint32_t FUN_0018cdb0(void)
{
  uint32_t msgbuf;
  long err;
  
  msgbuf = FUN_0018c7b8(0,0,0);
  if (err == 0) {
    msgbuf = 1;
  }
  return msgbuf;
}



/* FUN_0018cdb4 @ 0x0018cdb4   (est. FUN_0018cdb4)
 * Ghidra: undefined4 FUN_0018cdb4(void)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class X/None */
uint32_t FUN_0018cdb4(void)
{
  uint32_t msgbuf;
  long err;
  
  msgbuf = FUN_0018c7b8(0,0,0);
  if (err == 0) {
    msgbuf = 1;
  }
  return msgbuf;
}



/* FUN_0018cdd8 @ 0x0018cdd8   (est. FUN_0018cdd8)
 * Ghidra: undefined * FUN_0018cdd8(void)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class X/None */
void * FUN_0018cdd8(void)
{
  uint64_t msgbuf2;
  uint64_t msgbuf3;
  uint32_t msgbuf4;
  long msgbuf;
  
  msgbuf = 0x40;
  FUN_0018de98();
  do {
    msgbuf4 = FUN_000218a4();
    msgbuf3 = dat_00657788;
    msgbuf2 = dat_00657788 + 1;
    if (dat_00657790 >> 1 <= dat_00657788) {
      FUN_0018de98();
    }
    dat_00657788 = msgbuf2;
    *(uint32_t *)((long)&dat_00657798 + msgbuf3 * 4) = msgbuf4;
    msgbuf = msgbuf + -1;
  } while (msgbuf != 0);
  return &dat_00657778;
}



/* FUN_0018cea4 @ 0x0018cea4   (est. FUN_0018cea4)
 * Ghidra: void FUN_0018cea4(long p1)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class X/None */
void FUN_0018cea4(long p1)
{
  code_fn_t msgbuf2;
  uint64_t msgbuf;
  long msgbuf3;
  
  if (*(long *)(p1 + 0x10) == 0x40) {
    msgbuf3 = 0;
    do {
      FUN_000231f0(*(uint32_t *)(p1 + 0x20 + msgbuf3));
      msgbuf3 = msgbuf3 + 4;
    } while (msgbuf3 != 0x100);
    return;
  }
  FUN_002a4ab4(0x3b);
  thunk_FUN_002acbb8(0x5f2865646f636e65,0xea0000000000293a);
  thunk_FUN_002acbb8(0xd000000000000037,0x80000000005cc110);
  msgbuf2 = (code_fn_t)FUN_00027724(0x6720e0);
  (*msgbuf2)(0x677880,0x6720e0);
  thunk_FUN_002acbb8();
  FUN_003a25d4(msgbuf);
                    /* WARNING: Subroutine does not return */
  FUN_001afa84(s_Fatal_error_005accd0,0xb,2,0,0xe000000000000000,
               s_XnuUpcalls_XnuUpcalls_Swift_swif_005cbff0,0x21,2,0xc48,0);
}



/* FUN_0018cfe8 @ 0x0018cfe8   (est. FUN_0018cfe8)
 * Ghidra: void FUN_0018cfe8(void)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class X/None */
void FUN_0018cfe8(void)
{
  uint32_t msgbuf3;
  code_fn_t msgbuf2;
  uint64_t msgbuf;
  
  msgbuf3 = FUN_000218a4();
  if (msgbuf3 < 2) {
    return;
  }
  FUN_002a4ab4(0x28);
  FUN_003a25d4(0xe000000000000000);
  msgbuf2 = (code_fn_t)FUN_00027724(0x671298);
  (*msgbuf2)(0x6776f0,0x671298);
  thunk_FUN_002acbb8();
  FUN_003a25d4(msgbuf);
                    /* WARNING: Subroutine does not return */
  FUN_001afa84(s_Fatal_error_005accd0,0xb,2,0xd000000000000026,0x80000000005cc0e0,
               s_XnuUpcalls_XnuUpcalls_Swift_swif_005cbff0,0x21,2,0xa6e,0);
}



/* FUN_0018d0e4 @ 0x0018d0e4   (est. FUN_0018d0e4)
 * Ghidra: void FUN_0018d0e4(undefined8 p1,undefined8 p2)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class X/None */
void FUN_0018d0e4(uint64_t p1, uint64_t p2)
{
  uint32_t msgbuf3;
  code_fn_t msgbuf2;
  uint64_t msgbuf;
  
  msgbuf2 = (code_fn_t)FUN_001477c4(p2);
  msgbuf3 = (*msgbuf2)(p1,p2);
  if (msgbuf3 < 2) {
    return;
  }
  FUN_002a4ab4(0x28);
  FUN_003a25d4(0xe000000000000000);
  msgbuf2 = (code_fn_t)FUN_00027724(0x671298);
  (*msgbuf2)(0x6776f0,0x671298);
  thunk_FUN_002acbb8();
  FUN_003a25d4(msgbuf);
                    /* WARNING: Subroutine does not return */
  FUN_001afa84(s_Fatal_error_005accd0,0xb,2,0xd000000000000026,0x80000000005cc0e0,
               s_XnuUpcalls_XnuUpcalls_Swift_swif_005cbff0,0x21,2,0xa6e,0);
}



/* FUN_0018d208 @ 0x0018d208   (est. FUN_0018d208)
 * Ghidra: void FUN_0018d208(void)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class X/None */
void FUN_0018d208(void)
{
  int msgbuf3;
  code_fn_t msgbuf2;
  uint64_t msgbuf;
  
  msgbuf3 = FUN_000218a4();
  if (msgbuf3 == 1) {
    return;
  }
  FUN_002a4ab4(0x2a);
  FUN_003a25d4(0xe000000000000000);
  msgbuf2 = (code_fn_t)FUN_00027724(0x671298);
  (*msgbuf2)(0x6776f0,0x671298);
  thunk_FUN_002acbb8();
  FUN_003a25d4(msgbuf);
                    /* WARNING: Subroutine does not return */
  FUN_001afa84(s_Fatal_error_005accd0,0xb,2,0xd000000000000028,0x80000000005cc350,
               s_XnuUpcalls_XnuUpcalls_Swift_swif_005cbff0,0x21,2,0xa9a,0);
}



/* FUN_0018d304 @ 0x0018d304   (est. FUN_0018d304)
 * Ghidra: undefined8 FUN_0018d304(void)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class X/None */
uint64_t FUN_0018d304(void)
{
  int msgbuf3;
  uint64_t msgbuf4;
  code_fn_t msgbuf2;
  uint64_t msgbuf;
  
  msgbuf3 = FUN_000218a4();
  if (msgbuf3 == 2) {
    msgbuf4 = 1;
  }
  else {
    if (msgbuf3 != 1) {
      FUN_002a4ab4(0x27);
      FUN_003a25d4(0xe000000000000000);
      msgbuf2 = (code_fn_t)FUN_00027724(0x671298);
      (*msgbuf2)(0x6776f0,0x671298);
      thunk_FUN_002acbb8();
      FUN_003a25d4(msgbuf);
                    /* WARNING: Subroutine does not return */
      FUN_001afa84(s_Fatal_error_005accd0,0xb,2,0xd000000000000025,0x80000000005cc220,
                   s_XnuUpcalls_XnuUpcalls_Swift_swif_005cbff0,0x21,2,0xaa2,0);
    }
    msgbuf4 = 0;
  }
  return msgbuf4;
}



/* FUN_0018d414 @ 0x0018d414   (est. FUN_0018d414)
 * Ghidra: void FUN_0018d414(undefined8 p1,undefined8 p2,undefined8 p3,undefined8 p4)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class X/None */
void FUN_0018d414(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4)
{
  uint8_t msgbuf [56];
  
  thunk_FUN_00024068(msgbuf);
  FUN_00023208(p2);
  FUN_00023208(p3);
  FUN_00023208(p4);
  FUN_00025704();
  return;
}



/* FUN_0018d494 @ 0x0018d494   (est. FUN_0018d494)
 * Ghidra: void FUN_0018d494(undefined8 *p1)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class X/None */
void FUN_0018d494(uint64_t *p1)
{
  uint64_t msgbuf2;
  uint64_t msgbuf3;
  uint64_t msgbuf4;
  uint8_t msgbuf [56];
  
  FUN_000214b0(msgbuf);
  msgbuf2 = FUN_00021904();
  msgbuf3 = FUN_00021904();
  msgbuf4 = FUN_00021904();
  *p1 = msgbuf2;
  p1[1] = msgbuf3;
  p1[2] = msgbuf4;
  FUN_00025704();
  return;
}



/* FUN_0018d50c @ 0x0018d50c   (est. FUN_0018d50c)
 * Ghidra: ulong FUN_0018d50c(undefined8 p1,undefined8 p2)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class X/None */
uint64_t FUN_0018d50c(uint64_t p1, uint64_t p2)
{
  uint64_t msgbuf6;
  uint64_t errword;
  uint64_t *cpu;
  long err;
  uint8_t msgbuf [16];
  uint64_t msgbuf5;
  uint64_t msgbuf2;
  uint64_t msgbuf4;
  uint32_t msgbuf3;
  
  msgbuf4 = cpu[2];
  msgbuf2 = cpu[1];
  msgbuf5 = *cpu;
  msgbuf6 = FUN_00019aac(0);
  errword = FUN_00023f74(0,p1,p2,FUN_0018e290,msgbuf,0x67b148,msgbuf6,FUN_0065a550,
                       &msgbuf3);
  if (err != 0) {
    errword = (uint64_t)msgbuf3;
  }
  return errword;
}



/* FUN_0018d5c4 @ 0x0018d5c4   (est. FUN_0018d5c4)
 * Ghidra: 
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class X/None */
void FUN_0018d5c4(uint64_t *p1, uint64_t p2, uint64_t p3, uint64_t *p4, uint64_t p5)
{
  uint64_t msgbuf5;
  long err;
  uint32_t msgbuf4;
  uint64_t msgbuf3;
  uint64_t msgbuf;
  uint64_t msgbuf2;
  
  msgbuf5 = FUN_00019aac(0);
  FUN_00023f74(&msgbuf3,1,p2,p3,FUN_0018d494,0,p5,msgbuf5,FUN_0065a550,&msgbuf4);
  if (err == 0) {
    p1[1] = msgbuf;
    *p1 = msgbuf3;
    p1[2] = msgbuf2;
  }
  else {
    *p4 = msgbuf4;
  }
  return;
}



/* FUN_0018d690 @ 0x0018d690   (est. FUN_0018d690)
 * Ghidra: void FUN_0018d690(undefined8 p1,ulong p2,undefined8 p3)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class X/None */
void FUN_0018d690(uint64_t p1, uint64_t p2, uint64_t p3)
{
  uint8_t msgbuf [56];
  
  thunk_FUN_00024068(msgbuf);
  FUN_000231f0((uint32_t)p2 & 0xff);
  FUN_000231f0(p2 >> 0x20);
  FUN_000231f0(p3);
  FUN_00025704();
  return;
}



/* FUN_0018d710 @ 0x0018d710   (est. FUN_0018d710)
 * Ghidra: void FUN_0018d710(undefined1 *p1,undefined8 p2,undefined4 *p3)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class X/None */
void FUN_0018d710(uint64_t *p1, uint64_t p2, uint64_t *p3)
{
  uint32_t w1;
  uint32_t w2;
  uint32_t w3;
  long err;
  uint64_t w0;
  uint64_t len;
  uint64_t val4;
  uint64_t kind2;
  uint64_t val3;
  uint64_t kind;
  uint8_t val2;
  uint64_t val;
  uint64_t errword2;
  uint64_t errword;
  uint64_t msgbuf6;
  uint64_t idx2;
  uint64_t msgbuf5;
  uint8_t idx;
  uint64_t cnt2;
  uint64_t msgbuf4;
  uint64_t cnt;
  uint64_t msgbuf3;
  uint64_t msgbuf2;
  uint64_t msgbuf;
  uint8_t len2;
  
  FUN_000214b0(&w0);
  w1 = CL4_VOID_U64(FUN_0018cfe8());
  if (err == 0) {
    w2 = FUN_000218a4();
    w3 = FUN_000218a4();
    *p1 = (char)w1;
    *(uint32_t *)(p1 + 4) = w2;
    *(uint32_t *)(p1 + 8) = w3;
    errword2 = len;
    val = w0;
    msgbuf6 = kind2;
    errword = val4;
    msgbuf5 = kind;
    idx2 = val3;
    idx = val2;
    FUN_00025704();
  }
  else {
    msgbuf4 = len;
    cnt2 = w0;
    msgbuf3 = kind2;
    cnt = val4;
    msgbuf = kind;
    msgbuf2 = val3;
    len2 = val2;
    FUN_00025704();
    *p3 = w1;
  }
  return;
}



/* FUN_0018d7e8 @ 0x0018d7e8   (est. FUN_0018d7e8)
 * Ghidra: ulong FUN_0018d7e8(undefined8 p1,undefined8 p2)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class X/None */
uint64_t FUN_0018d7e8(uint64_t p1, uint64_t p2)
{
  uint64_t msgbuf5;
  uint64_t msgbuf6;
  uint8_t *cpu;
  long err;
  uint8_t msgbuf [16];
  uint8_t msgbuf4;
  uint64_t msgbuf3;
  uint32_t msgbuf2;
  
  msgbuf4 = *cpu;
  msgbuf3 = *(uint64_t *)(cpu + 4);
  msgbuf5 = FUN_00019aac(0);
  msgbuf6 = FUN_00023f74(0,p1,p2,FUN_0018e2b4,msgbuf,0x67b148,msgbuf5,FUN_0065a550,
                       &msgbuf2);
  if (err != 0) {
    msgbuf6 = (uint64_t)msgbuf2;
  }
  return msgbuf6;
}



/* FUN_0018d8a0 @ 0x0018d8a0   (est. FUN_0018d8a0)
 * Ghidra: 
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class X/None */
void FUN_0018d8a0(uint64_t *p1, uint64_t p2, uint64_t p3, uint64_t *p4, uint64_t p5)
{
  uint64_t msgbuf4;
  long err;
  uint32_t msgbuf3;
  uint8_t msgbuf2 [4];
  uint64_t msgbuf;
  
  msgbuf4 = FUN_00019aac(0);
  FUN_00023f74(msgbuf2,1,p2,p3,FUN_0018d710,0,p5,msgbuf4,FUN_0065a550,&msgbuf3);
  if (err == 0) {
    *p1 = msgbuf2[0];
    *(uint64_t *)(p1 + 4) = msgbuf;
  }
  else {
    *p4 = msgbuf3;
  }
  return;
}



/* FUN_0018d96c @ 0x0018d96c   (est. thunk -> ?)
 * Ghidra: void FUN_0018d96c(undefined8 p1,undefined8 p2)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_0018d96c(uint64_t p1, uint64_t p2)
{
    ;
}



/* FUN_0018d970 @ 0x0018d970   (est. thunk -> ?)
 * Ghidra: void FUN_0018d970(undefined8 p1,undefined8 p2)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_0018d970(uint64_t p1, uint64_t p2)
{
    ;
}



/* FUN_0018d9d8 @ 0x0018d9d8   (est. thunk -> ?)
 * Ghidra: void FUN_0018d9d8(void)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_0018d9d8(void)
{
    ;
}



/* FUN_0018d9dc @ 0x0018d9dc   (est. thunk -> ?)
 * Ghidra: void FUN_0018d9dc(void)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_0018d9dc(void)
{
    ;
}



/* FUN_0018da04 @ 0x0018da04   (est. thunk -> ?)
 * Ghidra: void FUN_0018da04(void)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_0018da04(void)
{
    ;
}



/* FUN_0018da08 @ 0x0018da08   (est. thunk -> ?)
 * Ghidra: void FUN_0018da08(void)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_0018da08(void)
{
    ;
}



/* FUN_0018da30 @ 0x0018da30   (est. thunk -> ?)
 * Ghidra: void FUN_0018da30(undefined8 p1,undefined8 p2)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_0018da30(uint64_t p1, uint64_t p2)
{
    ;
}



/* FUN_0018da34 @ 0x0018da34   (est. thunk -> ?)
 * Ghidra: void FUN_0018da34(undefined8 p1,undefined8 p2)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_0018da34(uint64_t p1, uint64_t p2)
{
    ;
}



/* FUN_0018da9c @ 0x0018da9c   (est. thunk -> ?)
 * Ghidra: void FUN_0018da9c(void)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_0018da9c(void)
{
    ;
}



/* FUN_0018daa0 @ 0x0018daa0   (est. thunk -> ?)
 * Ghidra: void FUN_0018daa0(void)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_0018daa0(void)
{
    ;
}



/* FUN_0018dac8 @ 0x0018dac8   (est. thunk -> ?)
 * Ghidra: void FUN_0018dac8(void)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_0018dac8(void)
{
    ;
}



/* FUN_0018dacc @ 0x0018dacc   (est. thunk -> ?)
 * Ghidra: void FUN_0018dacc(void)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_0018dacc(void)
{
    ;
}



/* FUN_0018daf4 @ 0x0018daf4   (est. FUN_0018daf4)
 * Ghidra: void FUN_0018daf4(undefined8 p1,undefined8 p2,undefined4 *p3,code_fn_t p4)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class X/None */
void FUN_0018daf4(uint64_t p1, uint64_t p2, uint64_t *p3, code_fn_t p4)
{
  uint32_t w1;
  long err;
  uint64_t w0;
  uint64_t len;
  uint64_t val4;
  uint64_t kind2;
  uint64_t val3;
  uint64_t kind;
  uint8_t val2;
  uint64_t val;
  uint64_t errword2;
  uint64_t errword;
  uint64_t msgbuf6;
  uint64_t idx2;
  uint64_t msgbuf5;
  uint8_t idx;
  uint64_t cnt2;
  uint64_t msgbuf4;
  uint64_t cnt;
  uint64_t msgbuf3;
  uint64_t msgbuf2;
  uint64_t msgbuf;
  uint8_t len2;
  
  thunk_FUN_00024068(&w0);
  w1 = (*p4)(p2);
  if (err == 0) {
    errword2 = len;
    val = w0;
    msgbuf6 = kind2;
    errword = val4;
    msgbuf5 = kind;
    idx2 = val3;
    idx = val2;
    FUN_00025704();
  }
  else {
    msgbuf4 = len;
    cnt2 = w0;
    msgbuf3 = kind2;
    cnt = val4;
    msgbuf = kind;
    msgbuf2 = val3;
    len2 = val2;
    FUN_00025704();
    *p3 = w1;
  }
  return;
}



/* FUN_0018dbc0 @ 0x0018dbc0   (est. thunk -> ?)
 * Ghidra: void FUN_0018dbc0(undefined8 p1,undefined8 p2)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_0018dbc0(uint64_t p1, uint64_t p2)
{
    ;
}



/* FUN_0018dbc4 @ 0x0018dbc4   (est. thunk -> ?)
 * Ghidra: void FUN_0018dbc4(undefined8 p1,undefined8 p2)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_0018dbc4(uint64_t p1, uint64_t p2)
{
    ;
}



/* FUN_0018dbec @ 0x0018dbec   (est. FUN_0018dbec)
 * Ghidra: void FUN_0018dbec(undefined8 *p1,undefined8 p2,undefined4 *p3,code_fn_t p4)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class X/None */
void FUN_0018dbec(uint64_t *p1, uint64_t p2, uint64_t *p3, code_fn_t p4)
{
  uint64_t w1;
  long err;
  uint64_t w0;
  uint64_t len;
  uint64_t val4;
  uint64_t kind2;
  uint64_t val3;
  uint64_t kind;
  uint8_t val2;
  uint64_t val;
  uint64_t errword2;
  uint64_t errword;
  uint64_t msgbuf6;
  uint64_t idx2;
  uint64_t msgbuf5;
  uint8_t idx;
  uint64_t cnt2;
  uint64_t msgbuf4;
  uint64_t cnt;
  uint64_t msgbuf3;
  uint64_t msgbuf2;
  uint64_t msgbuf;
  uint8_t len2;
  
  FUN_000214b0(&w0);
  w1 = (*p4)();
  if (err == 0) {
    *p1 = w1;
    errword2 = len;
    val = w0;
    msgbuf6 = kind2;
    errword = val4;
    msgbuf5 = kind;
    idx2 = val3;
    idx = val2;
    FUN_00025704();
  }
  else {
    msgbuf4 = len;
    cnt2 = w0;
    msgbuf3 = kind2;
    cnt = val4;
    msgbuf = kind;
    msgbuf2 = val3;
    len2 = val2;
    FUN_00025704();
    *p3 = (int)w1;
  }
  return;
}



/* FUN_0018dcd8 @ 0x0018dcd8   (est. thunk -> ?)
 * Ghidra: void FUN_0018dcd8(void)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_0018dcd8(void)
{
    ;
}



/* FUN_0018dcdc @ 0x0018dcdc   (est. thunk -> ?)
 * Ghidra: void FUN_0018dcdc(void)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_0018dcdc(void)
{
    ;
}



/* FUN_0018dd04 @ 0x0018dd04   (est. FUN_0018dd04)
 * Ghidra: 
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class X/None */
uint64_t FUN_0018dd04(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4, uint64_t p5)
{
  uint64_t msgbuf2;
  uint64_t msgbuf3;
  uint64_t *cpu;
  uint64_t msgbuf4;
  long err;
  uint32_t msgbuf;
  
  msgbuf4 = *cpu;
  msgbuf2 = FUN_00019aac(0);
  msgbuf3 = FUN_00023f74(0,p1,p2,p5,msgbuf4,0x67b148,msgbuf2,FUN_0065a550,&msgbuf);
  if (err != 0) {
    msgbuf3 = (uint64_t)msgbuf;
  }
  return msgbuf3;
}



/* FUN_0018ddac @ 0x0018ddac   (est. thunk -> ?)
 * Ghidra: void FUN_0018ddac(void)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_0018ddac(void)
{
    ;
}



/* FUN_0018ddb0 @ 0x0018ddb0   (est. thunk -> ?)
 * Ghidra: void FUN_0018ddb0(void)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_0018ddb0(void)
{
    ;
}



/* FUN_0018ddd8 @ 0x0018ddd8   (est. FUN_0018ddd8)
 * Ghidra: 
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class X/None */
void FUN_0018ddd8(uint64_t *p1, uint64_t p2, uint64_t p3, uint64_t *p4, uint64_t p5, uint64_t p6, uint64_t p7)
{
  uint64_t msgbuf3;
  long err;
  uint32_t msgbuf2;
  uint64_t msgbuf;
  
  msgbuf3 = FUN_00019aac(0);
  FUN_00023f74(&msgbuf,1,p2,p3,p7,0,p5,msgbuf3,FUN_0065a550,&msgbuf2);
  if (err == 0) {
    *p1 = msgbuf;
  }
  else {
    *p4 = msgbuf2;
  }
  return;
}



/* FUN_0018de98 @ 0x0018de98   (est. FUN_0018de98)
 * Ghidra: void FUN_0018de98(void)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class X/None */
void FUN_0018de98(void)
{
  uint64_t msgbuf;
  uint64_t *cpu;
  
  msgbuf = FUN_00072c98();
  *cpu = msgbuf;
  return;
}



/* FUN_0018deb8 @ 0x0018deb8   (est. FUN_0018deb8)
 * Ghidra: undefined8 FUN_0018deb8(uint p1)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class X/None */
uint64_t FUN_0018deb8(uint32_t p1)
{
  uint64_t msgbuf;
  
  if (p1 < 0x82) {
    msgbuf = 1;
    switch(p1) {
    default:
      msgbuf = 0;
    case 1:
      return msgbuf;
    case 2:
      return 2;
    case 3:
    case 4:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 0xb:
    case 0xe:
    case 0xf:
    case 0x10:
    case 0x12:
    case 0x13:
    case 0x17:
    case 0x18:
    case 0x19:
    case 0x1a:
    case 0x1b:
    case 0x1d:
    case 0x1f:
    case 0x20:
    case 0x21:
    case 0x24:
    case 0x25:
    case 0x26:
    case 0x27:
    case 0x28:
    case 0x29:
    case 0x2a:
    case 0x2b:
    case 0x2c:
    case 0x2e:
    case 0x2f:
    case 0x30:
    case 0x31:
    case 0x32:
    case 0x33:
    case 0x34:
    case 0x35:
    case 0x36:
    case 0x38:
    case 0x39:
    case 0x3a:
    case 0x3b:
    case 0x3c:
    case 0x3d:
    case 0x3e:
    case 0x40:
    case 0x41:
    case 0x42:
    case 0x43:
    case 0x44:
    case 0x45:
    case 0x47:
    case 0x48:
    case 0x49:
    case 0x4a:
    case 0x4b:
    case 0x4c:
    case 0x4d:
    case 0x4e:
    case 0x4f:
    case 0x51:
    case 0x52:
    case 0x53:
    case 0x54:
    case 0x55:
    case 0x56:
    case 0x57:
    case 0x58:
    case 0x59:
    case 0x5a:
    case 0x5b:
    case 0x5c:
    case 0x5d:
    case 0x5e:
    case 0x5f:
    case 0x60:
    case 0x61:
    case 0x62:
    case 99:
    case 100:
    case 0x65:
    case 0x66:
    case 0x67:
    case 0x68:
    case 0x69:
    case 0x6a:
    case 0x6b:
    case 0x6c:
    case 0x6d:
    case 0x6e:
    case 0x6f:
    case 0x70:
    case 0x71:
    case 0x72:
    case 0x73:
    case 0x74:
    case 0x75:
    case 0x76:
    case 0x77:
    case 0x78:
    case 0x79:
    case 0x7a:
    case 0x7b:
    case 0x7c:
    case 0x7d:
    case 0x7e:
    case 0x7f:
      goto switchD_0018dee8_caseD_3;
    case 5:
      return 3;
    case 0xc:
      return 4;
    case 0xd:
      return 5;
    case 0x11:
      return 6;
    case 0x14:
      return 7;
    case 0x15:
      return 8;
    case 0x16:
      return 9;
    case 0x1c:
      return 10;
    case 0x1e:
      return 0xb;
    case 0x22:
      return 0xc;
    case 0x23:
      return 0xd;
    case 0x2d:
      return 0xe;
    case 0x37:
      return 0xf;
    case 0x3f:
      return 0x10;
    case 0x46:
      return 0x11;
    case 0x50:
      return 0x12;
    case 0x80:
      return 0x13;
    case 0x81:
      return 0x14;
    }
  }
  if (p1 == 9999) {
    return 0x15;
  }
switchD_0018dee8_caseD_3:
  return 0x16;
}



/* FUN_0018e1c0 @ 0x0018e1c0   (est. FUN_0018e1c0)
 * Ghidra: undefined1  [16] FUN_0018e1c0(void)
 * Small upcall / message-register marshalling helper. Confidence: medium
 * Notes: part of the XNU upcall layer. */
cl4_16_t FUN_0018e1c0(void)
{
    return *(cl4_16_t *)0x655130;
}


/* FUN_0018e290 @ 0x0018e290   (est. FUN_0018e290)
 * Ghidra: void FUN_0018e290(undefined8 p1,undefined8 p2)
 * Small upcall / message-register marshalling helper. Confidence: medium
 * Notes: part of the XNU upcall layer. */
void FUN_0018e290(uint64_t a, uint64_t b)
{
    /* Sends a three-word upcall reply from the per-CPU words at +0x10/+0x18/+0x20. */
    FUN_0018d414(a, *(uint64_t *)(per_cpu + 0x10), *(uint64_t *)(per_cpu + 0x18),
                 *(uint64_t *)(per_cpu + 0x20));
}


/* FUN_0018e294 @ 0x0018e294   (est. FUN_0018e294)
 * Ghidra: void FUN_0018e294(undefined8 p1,undefined8 p2)
 * Small upcall / message-register marshalling helper. Confidence: medium
 * Notes: part of the XNU upcall layer. */
void FUN_0018e294(uint64_t a, uint64_t b)
{
    FUN_0018d414(a, *(uint64_t *)(per_cpu + 0x10), *(uint64_t *)(per_cpu + 0x18),
                 *(uint64_t *)(per_cpu + 0x20));
}


/* FUN_0018e2b4 @ 0x0018e2b4   (est. FUN_0018e2b4)
 * Ghidra: void FUN_0018e2b4(undefined8 p1,undefined8 p2)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class X/None */
void FUN_0018e2b4(uint64_t p1, uint64_t p2)
{
  long cpu;
  
  FUN_0018d690(p1,(uint64_t)*(uint8_t *)(cpu + 0x10) |
                      (uint64_t)*(uint32_t *)(cpu + 0x14) << 0x20,*(uint32_t *)(cpu + 0x18));
  return;
}



/* FUN_0018e2b8 @ 0x0018e2b8   (est. FUN_0018e2b8)
 * Ghidra: void FUN_0018e2b8(undefined8 p1,undefined8 p2)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class X/None */
void FUN_0018e2b8(uint64_t p1, uint64_t p2)
{
  long cpu;
  
  FUN_0018d690(p1,(uint64_t)*(uint8_t *)(cpu + 0x10) |
                      (uint64_t)*(uint32_t *)(cpu + 0x14) << 0x20,*(uint32_t *)(cpu + 0x18));
  return;
}



/* FUN_0018e2dc @ 0x0018e2dc   (est. thunk -> ?)
 * Ghidra: void FUN_0018e2dc(void)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_0018e2dc(void)
{
    ;
}



/* FUN_0018e2e0 @ 0x0018e2e0   (est. thunk -> ?)
 * Ghidra: void FUN_0018e2e0(void)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_0018e2e0(void)
{
    ;
}



/* FUN_0018e310 @ 0x0018e310   (est. thunk -> ?)
 * Ghidra: void FUN_0018e310(void)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_0018e310(void)
{
    ;
}



/* FUN_0018e314 @ 0x0018e314   (est. thunk -> ?)
 * Ghidra: void FUN_0018e314(void)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_0018e314(void)
{
    ;
}



/* FUN_0018e344 @ 0x0018e344   (est. thunk -> ?)
 * Ghidra: void FUN_0018e344(void)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_0018e344(void)
{
    ;
}



/* FUN_0018e348 @ 0x0018e348   (est. thunk -> ?)
 * Ghidra: void FUN_0018e348(void)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_0018e348(void)
{
    ;
}



/* FUN_0018e38c @ 0x0018e38c   (est. FUN_0018e38c)
 * Ghidra: void FUN_0018e38c(undefined1 *p1,undefined1 p2)
 * Small upcall / message-register marshalling helper. Confidence: medium
 * Notes: part of the XNU upcall layer. */
void FUN_0018e38c(uint8_t *out, uint8_t v)
{
    *out = v;
}


/* FUN_0018e6f4 @ 0x0018e6f4   (est. FUN_0018e6f4)
 * Ghidra: void FUN_0018e6f4(void)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class X/None */
void FUN_0018e6f4(void)
{
  uint8_t msgbuf2;
  uint8_t *cpu;
  uint8_t msgbuf [72];
  
  msgbuf2 = *cpu;
  FUN_001a84f4(msgbuf,0);
  FUN_0022995c(*(uint32_t *)(&dat_004e7004 + (uint64_t)msgbuf2 * 4));
  FUN_001a8564();
  return;
}



/* FUN_0018e744 @ 0x0018e744   (est. FUN_0018e744)
 * Ghidra: void FUN_0018e744(undefined8 p1)
 * Small upcall / message-register marshalling helper. Confidence: medium
 * Notes: part of the XNU upcall layer. */
void FUN_0018e744(uint64_t v)
{
    FUN_0022995c(v, *(uint32_t *)(dat_004e7004 + (uint64_t)*per_cpu * 4));
}


/* FUN_0018e77c @ 0x0018e77c   (est. FUN_0018e77c)
 * Ghidra: void FUN_0018e77c(void)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class X/None */
void FUN_0018e77c(void)
{
  uint8_t msgbuf2;
  uint8_t *cpu;
  uint8_t msgbuf [72];
  
  msgbuf2 = *cpu;
  FUN_001a84f4(msgbuf);
  FUN_0022995c(*(uint32_t *)(&dat_004e7004 + (uint64_t)msgbuf2 * 4));
  FUN_001a8564();
  return;
}



/* FUN_0018e7e8 @ 0x0018e7e8   (est. FUN_0018e7e8)
 * Ghidra: void FUN_0018e7e8(undefined8 p1,undefined8 p2)
 * Small upcall / message-register marshalling helper. Confidence: medium
 * Notes: part of the XNU upcall layer. */
void FUN_0018e7e8(uint64_t a, uint64_t b)
{
    uint64_t st = FUN_0002142c();
    FUN_00208478(a, b, 0x669c40, st);
}


/* FUN_0018e84c @ 0x0018e84c   (est. FUN_0018e84c)
 * Ghidra: void FUN_0018e84c(undefined8 p1,undefined8 p2)
 * Small upcall / message-register marshalling helper. Confidence: medium
 * Notes: part of the XNU upcall layer. */
void FUN_0018e84c(uint64_t a, uint64_t b)
{
    uint64_t st = FUN_0002142c();
    FUN_00208478(a, b, 0x669d60, st);
}


/* FUN_0018e8a0 @ 0x0018e8a0   (est. FUN_0018e8a0)
 * Ghidra: void FUN_0018e8a0(undefined8 p1,undefined8 p2)
 * Small upcall / message-register marshalling helper. Confidence: medium
 * Notes: part of the XNU upcall layer. */
void FUN_0018e8a0(uint64_t a, uint64_t b)
{
    uint64_t st = FUN_0002142c();
    FUN_00208478(a, b, 0x669db0, st);
}


/* FUN_0018e90c @ 0x0018e90c   (est. FUN_0018e90c)
 * Ghidra: void FUN_0018e90c(void)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class X/None */
void FUN_0018e90c(void)
{
  uint8_t msgbuf [72];
  
  FUN_001a84f4(msgbuf,0);
  thunk_FUN_002298d4(0xffffffffffffffff);
  FUN_001a8564();
  return;
}



/* FUN_0018e950 @ 0x0018e950   (est. thunk -> ?)
 * Ghidra: void FUN_0018e950(void)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_0018e950(void)
{
    ;
}



/* FUN_0018e978 @ 0x0018e978   (est. FUN_0018e978)
 * Ghidra: void FUN_0018e978(void)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class X/None */
void FUN_0018e978(void)
{
  uint8_t msgbuf [72];
  
  FUN_001a84f4(msgbuf);
  thunk_FUN_002298d4(0xffffffffffffffff);
  FUN_001a8564();
  return;
}



/* FUN_0018ea08 @ 0x0018ea08   (est. thunk -> ?)
 * Ghidra: void FUN_0018ea08(void)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_0018ea08(void)
{
    ;
}



/* FUN_0018ea5c @ 0x0018ea5c   (est. thunk -> ?)
 * Ghidra: void FUN_0018ea5c(void)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_0018ea5c(void)
{
    ;
}



/* FUN_0018ea80 @ 0x0018ea80   (est. thunk -> ?)
 * Ghidra: void FUN_0018ea80(void)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_0018ea80(void)
{
    ;
}



/* FUN_0018eaa4 @ 0x0018eaa4   (est. thunk -> ?)
 * Ghidra: void FUN_0018eaa4(void)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_0018eaa4(void)
{
    ;
}



/* FUN_0018eac8 @ 0x0018eac8   (est. thunk -> ?)
 * Ghidra: void FUN_0018eac8(void)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_0018eac8(void)
{
    ;
}



/* FUN_0018eaec @ 0x0018eaec   (est. thunk -> ?)
 * Ghidra: void FUN_0018eaec(void)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_0018eaec(void)
{
    ;
}



/* FUN_0018eb10 @ 0x0018eb10   (est. thunk -> ?)
 * Ghidra: void FUN_0018eb10(void)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_0018eb10(void)
{
    ;
}



/* FUN_0018eb14 @ 0x0018eb14   (est. thunk -> ?)
 * Ghidra: void FUN_0018eb14(void)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_0018eb14(void)
{
    ;
}



/* FUN_0018eb3c @ 0x0018eb3c   (est. thunk -> ?)
 * Ghidra: void FUN_0018eb3c(void)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_0018eb3c(void)
{
    ;
}



/* FUN_0018eb40 @ 0x0018eb40   (est. thunk -> ?)
 * Ghidra: void FUN_0018eb40(void)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_0018eb40(void)
{
    ;
}



/* FUN_0018eb68 @ 0x0018eb68   (est. FUN_0018eb68)
 * Ghidra: void FUN_0018eb68(undefined8 p1,undefined8 p2,undefined8 *p3,code_fn_t p4)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class X/None */
void FUN_0018eb68(uint64_t p1, uint64_t p2, uint64_t *p3, code_fn_t p4)
{
  uint64_t msgbuf3;
  uint64_t msgbuf;
  uint64_t msgbuf2;
  
  msgbuf2 = p3[2];
  msgbuf = p3[1];
  msgbuf3 = *p3;
  (*p4)(p1,p2,&msgbuf3);
  return;
}



/* FUN_0018ebac @ 0x0018ebac   (est. thunk -> ?)
 * Ghidra: void FUN_0018ebac(void)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_0018ebac(void)
{
    ;
}



/* FUN_0018ebd0 @ 0x0018ebd0   (est. FUN_0018ebd0)
 * Ghidra: void FUN_0018ebd0(undefined8 p1,undefined1 *p2)
 * Small upcall / message-register marshalling helper. Confidence: medium
 * Notes: part of the XNU upcall layer. */
void FUN_0018ebd0(uint64_t a, uint8_t *b)
{
    /* Delivers an upcall with the uint8_t *b: FUN_00191ba8(a, &b). */
    uint8_t v = *b;
    FUN_00191ba8(a, &v);
}


/* FUN_0018ec00 @ 0x0018ec00   (est. FUN_0018ec00)
 * Ghidra: ulong FUN_0018ec00(undefined8 p1,undefined8 p2,ulong p3,undefined8 p4)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class A/V2 */
uint64_t FUN_0018ec00(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4)
{
  char tag2;
  uint64_t tmp;
  uint32_t *msgbuf6;
  uint8_t *msgbuf;
  long err;
  uint8_t val2;
  uint64_t val;
  uint64_t len;
  uint64_t idx2;
  uint64_t kind2;
  uint64_t idx;
  uint64_t kind;
  uint8_t cnt2;
  uint8_t msgbuf5 [52];
  uint32_t cnt;
  uint8_t msgbuf4 [56];
  uint8_t msgbuf3 [56];
  uint8_t msgbuf2 [56];
  uint64_t len2;
  uint64_t errword2;
  uint64_t errword;
  uint64_t w3;
  uint64_t tag;
  uint64_t w2;
  uint8_t w7;
  uint64_t w6;
  uint64_t w1;
  uint64_t w0;
  uint64_t val4;
  uint64_t w5;
  uint64_t val3;
  uint8_t w4;
  
  FUN_00025ebc(msgbuf4,0x20,0,&cnt);
  if (err == 0) {
    thunk_FUN_00024068(msgbuf5);
    FUN_00023208(0xe75fc0d988051154);
    FUN_000231f0(p1);
    FUN_00023208(p2);
    FUN_00023208(p3);
    FUN_000231f0(p4);
    FUN_00022c48(msgbuf3);
    FUN_00025f44(msgbuf2,msgbuf3,&cnt);
    FUN_000214b0(&val,msgbuf2);
    tag2 = FUN_000217e4();
    if (tag2 == '\0') {
      p3 = FUN_000218a4();
      errword2 = len;
      len2 = val;
      w3 = kind2;
      errword = idx2;
      w2 = kind;
      tag = idx;
      w7 = cnt2;
      FUN_00025704();
    }
    else {
      if (tag2 != '\x01') {
                    /* WARNING: Subroutine does not return */
        FUN_001afa84(s_Fatal_error_005accd0,0xb,2,0xd000000000000038,0x80000000005ccbd0,
                     s_XnuUpcallsV2_XnuUpcallsV2_Swift__005ccbc0,0x25,2,0xfb5,0);
      }
      FUN_000268d0(&val2,0x66a0b0,0x65a688,0x66a0b0,0x65a5e8,0x66a708,&cnt);
      FUN_003698b0(&val2,0x66a0b0,0x669c50);
      p3 = (uint64_t)val2;
      FUN_0036993c(0x66a0b0,0x669c50,0,0);
      *msgbuf = val2;
      w1 = len;
      w6 = val;
      val4 = kind2;
      w0 = idx2;
      val3 = kind;
      w5 = idx;
      w4 = cnt2;
      FUN_00025704();
    }
  }
  else {
    tmp = FUN_00019aac(0);
    FUN_0036993c(tmp,FUN_0065a550,0,0);
    *msgbuf6 = cnt;
  }
  return p3;
}



/* FUN_0018ef04 @ 0x0018ef04   (est. thunk -> ?)
 * Ghidra: void FUN_0018ef04(void)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_0018ef04(void)
{
    ;
}



/* FUN_0018ef28 @ 0x0018ef28   (est. FUN_0018ef28)
 * Ghidra: uint FUN_0018ef28(void)
 * Small upcall / message-register marshalling helper. Confidence: medium
 * Notes: part of the XNU upcall layer. */
uint32_t FUN_0018ef28(void)
{
    return FUN_0019225c() & 1;
}


/* FUN_0018ef50 @ 0x0018ef50   (est. FUN_0018ef50)
 * Ghidra: uint FUN_0018ef50(void)
 * Small upcall / message-register marshalling helper. Confidence: medium
 * Notes: part of the XNU upcall layer. */
uint32_t FUN_0018ef50(void)
{
    return FUN_00192528() & 1;
}


/* FUN_0018efa8 @ 0x0018efa8   (est. thunk -> ?)
 * Ghidra: void FUN_0018efa8(void)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_0018efa8(void)
{
    ;
}



/* FUN_0018efcc @ 0x0018efcc   (est. thunk -> ?)
 * Ghidra: void FUN_0018efcc(void)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_0018efcc(void)
{
    ;
}



/* FUN_0018eff0 @ 0x0018eff0   (est. thunk -> ?)
 * Ghidra: void FUN_0018eff0(void)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_0018eff0(void)
{
    ;
}



/* FUN_0018f014 @ 0x0018f014   (est. thunk -> ?)
 * Ghidra: void FUN_0018f014(void)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_0018f014(void)
{
    ;
}



/* FUN_0018f038 @ 0x0018f038   (est. thunk -> ?)
 * Ghidra: void FUN_0018f038(void)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_0018f038(void)
{
    ;
}



/* FUN_0018f05c @ 0x0018f05c   (est. thunk -> ?)
 * Ghidra: void FUN_0018f05c(void)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_0018f05c(void)
{
    ;
}



/* FUN_0018f080 @ 0x0018f080   (est. thunk -> ?)
 * Ghidra: void FUN_0018f080(void)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_0018f080(void)
{
    ;
}



/* FUN_0018f0a4 @ 0x0018f0a4   (est. thunk -> ?)
 * Ghidra: void FUN_0018f0a4(void)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_0018f0a4(void)
{
    ;
}



/* FUN_0018f0c8 @ 0x0018f0c8   (est. FUN_0018f0c8)
 * Ghidra: uint FUN_0018f0c8(undefined8 p1,undefined8 p2,undefined1 *p3)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class X/None */
uint32_t FUN_0018f0c8(uint64_t p1, uint64_t p2, uint64_t *p3)
{
  uint32_t msgbuf3;
  uint8_t msgbuf2 [4];
  uint64_t msgbuf;
  
  msgbuf2[0] = *p3;
  msgbuf = *(uint64_t *)(p3 + 4);
  msgbuf3 = FUN_00193f7c(p1,p2,msgbuf2);
  return msgbuf3 & 1;
}



/* FUN_0018f10c @ 0x0018f10c   (est. thunk -> ?)
 * Ghidra: void FUN_0018f10c(void)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_0018f10c(void)
{
    ;
}



/* FUN_0018f130 @ 0x0018f130   (est. thunk -> ?)
 * Ghidra: void FUN_0018f130(void)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_0018f130(void)
{
    ;
}



/* FUN_0018f154 @ 0x0018f154   (est. thunk -> ?)
 * Ghidra: void FUN_0018f154(void)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_0018f154(void)
{
    ;
}



/* FUN_0018f178 @ 0x0018f178   (est. thunk -> ?)
 * Ghidra: void FUN_0018f178(void)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_0018f178(void)
{
    ;
}



/* FUN_0018f19c @ 0x0018f19c   (est. thunk -> ?)
 * Ghidra: void FUN_0018f19c(void)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_0018f19c(void)
{
    ;
}



/* FUN_0018f1c0 @ 0x0018f1c0   (est. thunk -> ?)
 * Ghidra: void FUN_0018f1c0(void)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_0018f1c0(void)
{
    ;
}



/* FUN_0018f214 @ 0x0018f214   (est. FUN_0018f214)
 * Ghidra: uint FUN_0018f214(void)
 * Small upcall / message-register marshalling helper. Confidence: medium
 * Notes: part of the XNU upcall layer. */
uint32_t FUN_0018f214(void)
{
    return FUN_00195418() & 1;
}


/* FUN_0018f23c @ 0x0018f23c   (est. FUN_0018f23c)
 * Ghidra: uint FUN_0018f23c(undefined8 p1,undefined8 p2,ulong p3,undefined8 p4)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class A/V2 */
uint32_t FUN_0018f23c(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4)
{
  uint8_t tag2;
  char tmp;
  uint64_t tmp2;
  uint32_t *msgbuf6;
  uint8_t *msgbuf;
  long err;
  uint8_t val2;
  uint64_t val;
  uint64_t len;
  uint64_t idx2;
  uint64_t kind2;
  uint64_t idx;
  uint64_t kind;
  uint8_t cnt2;
  uint8_t msgbuf5 [52];
  uint32_t cnt;
  uint8_t msgbuf4 [56];
  uint8_t msgbuf3 [56];
  uint8_t msgbuf2 [56];
  uint64_t len2;
  uint64_t errword2;
  uint64_t errword;
  uint64_t w3;
  uint64_t tag;
  uint64_t w2;
  uint8_t w7;
  uint64_t w6;
  uint64_t w1;
  uint64_t w0;
  uint64_t val4;
  uint64_t w5;
  uint64_t val3;
  uint8_t w4;
  
  FUN_00025ebc(msgbuf4,0x24,0,&cnt);
  if (err == 0) {
    thunk_FUN_00024068(msgbuf5);
    FUN_00023208(0x755813609d337e7f);
    FUN_00023208(p1);
    FUN_00023208(p2);
    FUN_000231f0(p3);
    FUN_00023208(p4);
    FUN_00022c48(msgbuf3);
    FUN_00025f44(msgbuf2,msgbuf3,&cnt);
    FUN_000214b0(&val,msgbuf2);
    tmp = FUN_000217e4();
    if (tmp == '\x01') {
      FUN_000268d0(&val2,0x66a140,0x65a688,0x66a140,0x65a5e8,FUN_0066a720,&cnt);
      val2 = val2 & 0x7f;
      FUN_003698b0(&val2,0x66a140,0x669c90);
      tag2 = val2;
      p3 = (uint64_t)val2;
      FUN_0036993c(0x66a140,0x669c90,0,0);
      *msgbuf = tag2;
      w1 = len;
      w6 = val;
      val4 = kind2;
      w0 = idx2;
      val3 = kind;
      w5 = idx;
      w4 = cnt2;
      FUN_00025704();
    }
    else {
      if (tmp != '\0') {
                    /* WARNING: Subroutine does not return */
        FUN_001afa84(s_Fatal_error_005accd0,0xb,2,0xd00000000000003e,0x80000000005ccc10,
                     s_XnuUpcallsV2_XnuUpcallsV2_Swift__005ccbc0,0x25,2,0x109f,0);
      }
      p3 = FUN_00021738();
      errword2 = len;
      len2 = val;
      w3 = kind2;
      errword = idx2;
      w2 = kind;
      tag = idx;
      w7 = cnt2;
      FUN_00025704();
    }
  }
  else {
    tmp2 = FUN_00019aac(0);
    FUN_0036993c(tmp2,FUN_0065a550,0,0);
    *msgbuf6 = cnt;
  }
  return (uint32_t)p3 & 1;
}



/* FUN_0018f544 @ 0x0018f544   (est. FUN_0018f544)
 * Ghidra: uint FUN_0018f544(void)
 * Small upcall / message-register marshalling helper. Confidence: medium
 * Notes: part of the XNU upcall layer. */
uint32_t FUN_0018f544(void)
{
    return FUN_001956f4() & 1;
}


/* FUN_0018f56c @ 0x0018f56c   (est. FUN_0018f56c)
 * Ghidra: uint FUN_0018f56c(void)
 * Small upcall / message-register marshalling helper. Confidence: medium
 * Notes: part of the XNU upcall layer. */
uint32_t FUN_0018f56c(void)
{
    return FUN_001959e8() & 1;
}


/* FUN_0018f5c4 @ 0x0018f5c4   (est. thunk -> ?)
 * Ghidra: void FUN_0018f5c4(void)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_0018f5c4(void)
{
    ;
}



/* FUN_0018f5e8 @ 0x0018f5e8   (est. thunk -> ?)
 * Ghidra: void FUN_0018f5e8(void)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_0018f5e8(void)
{
    ;
}



/* FUN_0018f63c @ 0x0018f63c   (est. thunk -> ?)
 * Ghidra: void FUN_0018f63c(void)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_0018f63c(void)
{
    ;
}



/* FUN_0018f660 @ 0x0018f660   (est. thunk -> ?)
 * Ghidra: void FUN_0018f660(void)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_0018f660(void)
{
    ;
}



/* FUN_0018f684 @ 0x0018f684   (est. thunk -> ?)
 * Ghidra: void FUN_0018f684(void)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_0018f684(void)
{
    ;
}



/* FUN_0018f6d8 @ 0x0018f6d8   (est. thunk -> ?)
 * Ghidra: void FUN_0018f6d8(void)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_0018f6d8(void)
{
    ;
}



/* FUN_0018f6fc @ 0x0018f6fc   (est. thunk -> ?)
 * Ghidra: void FUN_0018f6fc(void)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_0018f6fc(void)
{
    ;
}



/* FUN_0018f720 @ 0x0018f720   (est. FUN_0018f720)
 * Ghidra: void FUN_0018f720(undefined8 *p1)
 * Small upcall / message-register marshalling helper. Confidence: medium
 * Notes: part of the XNU upcall layer. */
void FUN_0018f720(uint64_t *p)
{
    /* Runs FUN_00196c20 on the first word of *p. */
    uint64_t v = *p;
    FUN_00196c20(&v);
}


/* FUN_0018f780 @ 0x0018f780   (est. thunk -> ?)
 * Ghidra: void FUN_0018f780(void)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_0018f780(void)
{
    ;
}



/* FUN_0018f7a4 @ 0x0018f7a4   (est. thunk -> ?)
 * Ghidra: void FUN_0018f7a4(void)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_0018f7a4(void)
{
    ;
}



/* FUN_0018f7c8 @ 0x0018f7c8   (est. thunk -> ?)
 * Ghidra: void FUN_0018f7c8(void)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_0018f7c8(void)
{
    ;
}



/* FUN_0018f7ec @ 0x0018f7ec   (est. thunk -> ?)
 * Ghidra: void FUN_0018f7ec(void)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_0018f7ec(void)
{
    ;
}



/* FUN_0018f828 @ 0x0018f828   (est. FUN_0018f828)
 * Ghidra: long FUN_0018f828(undefined8 p1,undefined8 p2,code_fn_t p3)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class X/None */
long FUN_0018f828(uint64_t p1, uint64_t p2, code_fn_t p3)
{
  long msgbuf;
  uint64_t msgbuf3;
  long msgbuf2;
  
  msgbuf = FUN_0036a940();
  msgbuf3 = (*p3)(0);
  msgbuf2 = FUN_0036a940(msgbuf3,0x18,7);
  msgbuf3 = FUN_000262ec(0);
  FUN_0036a940(msgbuf3,0x18,7);
  msgbuf3 = FUN_000260e0(p1,p2);
  *(uint64_t *)(msgbuf2 + 0x10) = msgbuf3;
  *(long *)(msgbuf + 0x10) = msgbuf2;
  return msgbuf;
}



/* FUN_0018f8d8 @ 0x0018f8d8   (est. FUN_0018f8d8)
 * Ghidra: void FUN_0018f8d8(undefined8 p1,undefined8 p2,code_fn_t p3)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class X/None */
void FUN_0018f8d8(uint64_t p1, uint64_t p2, code_fn_t p3)
{
  uint64_t msgbuf2;
  long msgbuf;
  long cpu;
  
  msgbuf2 = (*p3)(0);
  msgbuf = FUN_0036a940(msgbuf2,0x18,7);
  msgbuf2 = FUN_000262ec(0);
  msgbuf2 = FUN_0036a940(msgbuf2,0x18,7);
  msgbuf2 = FUN_000260e0(p1,p2,msgbuf2);
  *(uint64_t *)(msgbuf + 0x10) = msgbuf2;
  *(long *)(cpu + 0x10) = msgbuf;
  return;
}



/* FUN_0018f958 @ 0x0018f958   (est. FUN_0018f958)
 * Ghidra: void FUN_0018f958(undefined8 *p1)
 * Small upcall / message-register marshalling helper. Confidence: medium
 * Notes: part of the XNU upcall layer. */
void FUN_0018f958(uint64_t *p)
{
    uint64_t v = *p;
    FUN_00197be4(&v);
}


/* FUN_0018fbe8 @ 0x0018fbe8   (est. FUN_0018fbe8)
 * Ghidra: undefined1  [16] FUN_0018fbe8(void)
 * Small upcall / message-register marshalling helper. Confidence: medium
 * Notes: part of the XNU upcall layer. */
cl4_16_t FUN_0018fbe8(void)
{
    return *(cl4_16_t *)0x655440;
}


/* FUN_0018fcb0 @ 0x0018fcb0   (est. thunk -> ?)
 * Ghidra: void FUN_0018fcb0(undefined8 p1)
 * Forwarding thunk: forwards its arguments to ? and returns its result.
 * Confidence: medium
 * Notes: XNU upcall dispatch alias. */
void FUN_0018fcb0(uint64_t p1)
{
    ;
}



/* FUN_0018fcd8 @ 0x0018fcd8   (est. FUN_0018fcd8)
 * Ghidra: ulong FUN_0018fcd8(long p1)
 * XNU upcall / syscall handler: reads the message registers, dispatches the
 * operation, marshals the reply and, on a per-CPU error, reports a fault via
 * the XnuUpcalls tracing/fatal path. Confidence: medium
 * Notes: class A/V2LONG */
uint64_t FUN_0018fcd8(long p1)
{
  long slot3;
  code_fn_t key2;
  bool slot;
  char slot2;
  uint64_t fn2;
  uint32_t *msgbuf6;
  uint8_t *msgbuf;
  uint64_t msgbuf2;
  uint64_t fn3;
  long fn;
  uint64_t st;
  long err;
  uint64_t ret;
  uint64_t st2;
  uint64_t tag2;
  uint64_t val2;
  uint64_t val;
  uint64_t idx2;
  uint64_t tag;
  uint64_t idx;
  uint8_t w7;
  uint64_t w6;
  uint64_t w5;
  uint64_t cnt2;
  uint64_t cnt;
  uint64_t len2;
  uint64_t w4;
  uint64_t len;
  uint8_t w3;
  uint32_t w2;
  uint8_t msgbuf5 [56];
  uint8_t msgbuf4 [56];
  uint8_t msgbuf3 [56];
  uint64_t w1;
  uint64_t kind2;
  uint64_t kind;
  uint64_t errword2;
  uint64_t w0;
  uint64_t errword;
  uint8_t val4;
  uint64_t val3;
  uint64_t ptr4;
  uint64_t ptr3;
  uint64_t ptr2;
  uint64_t key;
  uint64_t ptr;
  uint8_t h4;
  uint64_t h3;
  uint64_t tmp4;
  uint64_t tmp3;
  uint64_t tmp2;
  uint64_t h2;
  uint64_t tmp;
  uint8_t h;
  
  st = 0;
  while ((st != 0x20 &&
         (slot = *(uint64_t *)(p1 + 0x10) <= st, st != *(uint64_t *)(p1 + 0x10)))) {
    st = st + 1;
    if (slot) {
                    /* WARNING: Does not return */
      cl4_break(0x18fd1c);
    }
  }
  FUN_00025ebc(msgbuf5,st + 8,0,&w2);
  if (err == 0) {
    thunk_FUN_00024068(&w5);
    FUN_00023208(0x6582f8a8f1e86016);
    st = *(uint64_t *)(p1 + 0x10);
    if (st != 0x20) {
      tag2 = 0;
      val2 = 0xe000000000000000;
      FUN_002a4ab4(0x3b);
      thunk_FUN_002acbb8(0xd000000000000010,0x80000000005cd610);
      thunk_FUN_002acbb8(0xd000000000000037,0x80000000005cc150);
      w6 = st;
      key2 = (code_fn_t)FUN_00027724(0x6720e0);
      (*key2)(0x677880,0x6720e0);
      thunk_FUN_002acbb8();
      FUN_003a25d4(msgbuf2);
      st2 = 0x3e2;
      fn2 = tag2;
      fn3 = val2;
LAB_0019007c:
                    /* WARNING: Subroutine does not return */
      FUN_001afa84(s_Fatal_error_005accd0,0xb,2,fn2,fn3,
                   s_XnuUpcallsV2_XnuUpcallsV2_Swift__005ccbc0,0x25,2,st2,0);
    }
    fn = 0;
    do {
      slot3 = fn + 1;
      FUN_000230f8(*(uint8_t *)(p1 + 0x20 + fn));
      fn = slot3;
    } while (slot3 != 0x20);
    tmp4 = cnt2;
    h3 = w5;
    tmp2 = len2;
    tmp3 = cnt;
    tmp = len;
    h2 = w4;
    h = w3;
    FUN_00022c48(msgbuf4);
    FUN_00025f44(msgbuf3,msgbuf4,&w2);
    FUN_000214b0(&tag2,msgbuf3);
    slot2 = FUN_000217e4();
    if (slot2 == '\0') {
      ret = FUN_00021904();
      kind2 = val2;
      w1 = tag2;
      errword2 = idx2;
      kind = val;
      errword = idx;
      w0 = tag;
      val4 = w7;
      FUN_00025704();
    }
    else {
      if (slot2 != '\x01') {
        st2 = 0xf52;
        fn2 = 0xd000000000000035;
        fn3 = 0x80000000005ccb60;
        goto LAB_0019007c;
      }
      FUN_000268d0(&w6,0x66a0b0,0x65a688,0x66a0b0,0x65a5e8,0x66a708,&w2);
      FUN_003698b0(&w6,0x66a0b0,0x669c50);
      ret = w6 & 0xff;
      FUN_0036993c(0x66a0b0,0x669c50,0,0);
      *msgbuf = (uint8_t)w6;
      ptr4 = val2;
      val3 = tag2;
      ptr2 = idx2;
      ptr3 = val;
      ptr = idx;
      key = tag;
      h4 = w7;
      FUN_00025704();
    }
  }
  else {
    fn2 = FUN_00019aac(0);
    FUN_0036993c(fn2,FUN_0065a550,0,0);
    *msgbuf6 = w2;
  }
  return ret;
}


