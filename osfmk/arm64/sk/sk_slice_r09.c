/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel, GL1,
 * arm64e, image base 0) — the cL4 microkernel. Ground truth: Ghidra FUN_ names +
 * addresses in the cl4_kernel.raw program. Names use seL4/cL4 vocabulary; all
 * are estimates unless string/header matched.
 *
 * Slice 0x003e68f0-0x003eeef4 (worker SKR09): the cap-invocation / operation-
 * dispatch subsystem — the op-frame builders that allocate a per-invocation
 * frame and seed it with the running context (x22) and a vtable, and the
 * operation runner / state machines that drive a capability operation to
 * completion, allocate reply/message slots, and release the op frame.
 */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "sk_internal.h"

/* ------------------------------------------------------------------ *
 * Hardware / intrinsic helpers (same semantics as the Ghidra pseudo-ops
 * used in the decompiles).
 * ------------------------------------------------------------------ */
static inline unsigned sk_clz64(uint64_t x) { return (unsigned)__builtin_clzll(x); }
#define LZCOUNT(x) sk_clz64((uint64_t)(x))
static inline void sk_callsup(uint64_t kind)
{ __asm__ volatile("svc %0" : : "i"(0)); (void)kind; }
#define CallSupervisor(k) sk_callsup((uint64_t)(k))
static inline void sk_break(uint64_t a, uint64_t b) __attribute__((noreturn))
{ (void)a; (void)b; __asm__ volatile("brk #1"); }
#define SoftwareBreakpoint(a,b) sk_break((uint64_t)(a),(uint64_t)(b))
#define SK_CANARY (-0x2c8502b44bfffed6LL)

static uint8_t sk_tpidr_area[0x100] __attribute__((aligned(16)));

/* Forward declarations of the in-slice functions (definition order). */
static void sk_capop_003e68f0(void);
static void sk_capop_003e6be8(uint64_t arg1, uint64_t arg2, uint64_t arg3, uint64_t arg4, uint64_t arg5);
static void sk_capop_003e6cbc(void);
static void sk_capop_003e6cf0(void);
static void sk_capop_003e6d08(void);
static void sk_capop_003e6da8(uint64_t arg1);
static void sk_capop_003e6dd0(uint64_t arg1, int64_t arg2);
static void sk_capop_003e6ecc(long param_1, uint64_t param_2, uint64_t param_3, uint64_t param_4, uint64_t param_5, uint64_t param_6, uint64_t param_7, uint64_t param_8, uint64_t (*param_9);
static void sk_capop_003e6fc8(void);
static void sk_capop_003e7228(void);
static void sk_capop_003e74fc(void);
static void sk_capop_003e788c(void);
static void sk_capop_003e7b14(void);
static void sk_capop_003e7d20(void);
static void sk_capop_003e838c(uint64_t param_1, uint64_t param_2, uint64_t param_3, int64_t param_4);
static void sk_capop_003e86c8(void);
static void sk_capop_003e89f0(void);
static void sk_capop_003e8e28(void);
static void sk_capop_003e90f4(void);
static void sk_capop_003e9310(void);
static void sk_capop_003e9c34(uint64_t arg1, uint64_t arg2, uint64_t arg3, uint64_t arg4, uint64_t arg5);
static void sk_capop_003e9d04(void);
static void sk_capop_003e9db0(void);
static void sk_capop_003e9de0(void);
static void sk_capop_003e9df8(void);
static void sk_capop_003e9e74(uint64_t arg1, uint64_t arg2);
static void sk_capop_003e9f40(void);
static void sk_capop_003e9fcc(void);
static void sk_capop_003ea0a4(void);
static void sk_capop_003ea260(void);
static void sk_capop_003ea494(void);
static void sk_capop_003ea4ec(void);
static void sk_capop_003ea5a8(uint64_t param_1, uint64_t param_2, uint64_t param_3, uint64_t param_4);
static void sk_capop_003ea6ec(void);
static void sk_capop_003ea8f4(void);
static void sk_capop_003eab58(void);
static void sk_capop_003ead6c(uint64_t arg1, uint64_t arg2, uint64_t arg3, uint64_t arg4, uint64_t arg5);
static void sk_capop_003eae24(void);
static void sk_capop_003eaef4(void);
static void sk_capop_003eaf34(void);
static void sk_capop_003eaf4c(void);
static void sk_capop_003eafc8(uint64_t arg1, int64_t arg2);
static void sk_capop_003eb0a4(void);
static void sk_capop_003eb120(void);
static void sk_capop_003eb1d8(void);
static void sk_capop_003eb398(void);
static void sk_capop_003eb594(void);
static void sk_capop_003eb68c(uint64_t param_1, uint64_t param_2, uint64_t param_3, uint64_t param_4);
static void sk_capop_003eb7c4(void);
static void sk_capop_003eb9c8(void);
static void sk_capop_003ebbd4(void);
static void sk_capop_003ebd9c(uint64_t arg1, uint64_t arg2, uint64_t arg3, uint64_t arg4, uint64_t arg5);
static void sk_capop_003ebe6c(void);
static cl4_result_t sk_capop_003ebf10(void);
static void sk_capop_003ebfe8(void);
static void sk_capop_003ec094(void);
static void sk_capop_003ec098(void);
static uint8_t *sk_capop_003ec0c4(void);
static void sk_capop_003ec12c(void);
static void sk_capop_003ec130(void);
static void sk_capop_003ec144(void);
static void sk_capop_003ec148(void);
static void sk_capop_003ec178(void);
static void sk_capop_003ec20c(void);
static void sk_capop_003ec438(void);
static void sk_capop_003ec4dc(void);
static void sk_capop_003ec598(void);
static void sk_capop_003ec6c8(void);
static void sk_capop_003ec708(void);
static void sk_capop_003ec730(void);
static void sk_capop_003ec758(void);
static void sk_capop_003ec780(void);
static void sk_capop_003ec7bc(void);
static void sk_capop_003ec7fc(void);
static void sk_capop_003ec824(void);
static void sk_capop_003ec84c(void);
static void sk_capop_003ec874(void);
static void sk_capop_003ec8a0(uint64_t param_1, uint64_t param_2);
static void sk_capop_003ec8c8(uint64_t param_1);
static void sk_capop_003ec918(void);
static int64_t sk_capop_003ec9c4(int arg1);
static void sk_capop_003ecb1c(void);
static void sk_capop_003ecb20(void);
static void sk_capop_003ecb48(uint64_t param_1);
static void sk_capop_003ecb4c(uint64_t param_1);
static void sk_capop_003ecb64(uint64_t arg1, uint64_t arg2);
static uint64_t sk_capop_003ecc18(void);
static void sk_capop_003eccc4(void);
static uint32_t sk_capop_003ecd44(void);
static void sk_capop_003ecd98(void);
static void sk_capop_003ecd9c(void);
static void sk_capop_003ecddc(void);
static void sk_capop_003ed0a8(void);
static void sk_capop_003ed0ec(void);
static void sk_capop_003ed14c(void);
static void sk_capop_003ed1a4(uint64_t arg1, uint64_t arg2, uint64_t arg3, uint64_t arg4, uint64_t arg5, uint64_t arg6, uint64_t arg7);
static void sk_capop_003ed2dc(uint64_t arg1, uint64_t arg2, uint64_t arg3);
static void sk_capop_003ed340(void);
static void sk_capop_003ed4d4(void);
static void sk_capop_003ed5f8(uint64_t param_1, uint64_t param_2, uint64_t param_3);
static void sk_capop_003ed6d0(uint64_t arg1, uint64_t arg2, uint64_t arg3, int *arg4, uint64_t arg5, uint64_t arg6, uint64_t arg7, uint64_t arg8, int64_t arg9, uint64_t arg10, uint64_t arg11);
static void sk_capop_003ed930(void);
static void sk_capop_003edad4(void);
static void sk_capop_003edf5c(void);
static void sk_capop_003ee090(void);
static void sk_capop_003ee234(void);
static void sk_capop_003ee310(void);
static void sk_capop_003ee3c8(void);
static void sk_capop_003ee47c(void);
static void sk_capop_003ee520(void);
static void sk_capop_003ee5e8(uint64_t arg1, uint64_t arg2, uint64_t arg3, int64_t arg4, uint64_t arg5, uint64_t arg6, uint64_t arg7, uint64_t arg8);
static void sk_capop_003ee688(uint64_t arg1, uint64_t arg2, uint64_t (*tail);
static void sk_capop_003ee818(void);
static void sk_capop_003ee8e4(void);
static void sk_capop_003eead0(void);
static void sk_capop_003eeb6c(void);
static void sk_capop_003eebf0(void);
static void sk_capop_003eec90(uint64_t param_1, uint64_t param_2, uint64_t param_3, uint64_t param_4, uint64_t param_5, uint64_t param_6, uint64_t param_7, uint64_t param_8);
static void sk_capop_003eed30(uint64_t param_1, uint64_t param_2, void (*UNRECOVERED_JUMPTABLE);
static void sk_capop_003eeef4(void);

#define tpidr_el0    ((uint8_t *)sk_tpidr_area)
#define tpidrro_el0  ((uint8_t *)sk_tpidr_area)

/* ------------------------------------------------------------------ *
 * Shared globals referenced by this slice (image-base addresses are the
 * Ghidra ground truth).
 * ------------------------------------------------------------------ */
extern uint64_t sk_g_004060bc;          /* DAT_004060bc */
extern uint64_t sk_g_004bbc30;          /* DAT_004bbc30 */
extern uint64_t sk_g_005a00bc;          /* DAT_005a00bc */
extern uint64_t sk_g_005a00cc;          /* DAT_005a00cc */
extern uint64_t sk_g_005a00dc;          /* DAT_005a00dc */
extern uint64_t sk_g_005a00ec;          /* DAT_005a00ec */
extern uint64_t sk_g_005a0138;          /* DAT_005a0138 */
extern uint64_t sk_g_005a0194;          /* DAT_005a0194 */
extern uint64_t sk_g_00614a5c;          /* DAT_00614a5c */
extern uint64_t sk_g_0064c260;          /* DAT_0064c260 */
extern uint64_t sk_g_00658c80;          /* DAT_00658c80 */
extern uint64_t sk_g_006adf30;          /* DAT_006adf30 */
extern uint64_t sk_g_006c0b58;          /* DAT_006c0b58 */
extern uint32_t sk_g_006775b0;          /* UINT_006775b0 */
extern uint8_t  sk_g_005dc050;          /* string s_TaskPriority_high_005dc050 */
extern uint8_t  sk_g_005dc070;          /* string s_TaskPriority_medium_005dc070 */
extern uint8_t  sk_g_005dc090;          /* string s_TaskPriority_low_005dc090 */
extern uint8_t  sk_g_005dc0b0;          /* string s_Concurrency_Task_swift_005dc0b0 */
extern uint8_t  sk_g_005dc0d0;          /* string s_Unavailable_in_Exclaves_005dc0d0 */

/* ------------------------------------------------------------------ *
 * Out-of-slice callees (reconstructed by other slice workers). The
 * sk_x_XXXXXXXX names encode the Ghidra FUN_ address.
 * ------------------------------------------------------------------ */
extern unsigned long sk_x_00002534();   /* FUN_00002534 */
extern unsigned long sk_x_000026e8();   /* FUN_000026e8 */
extern unsigned long sk_x_00019858();   /* FUN_00019858 */
extern cl4_result_t sk_x_00027614();   /* FUN_00027614 */
extern unsigned long sk_x_00027724();   /* FUN_00027724 */
extern unsigned long sk_x_0006a4c0();   /* FUN_0006a4c0 */
extern unsigned long sk_x_0007c028();   /* FUN_0007c028 */
extern unsigned long sk_x_0007c1a4();   /* FUN_0007c1a4 */
extern unsigned long sk_x_000836a4();   /* FUN_000836a4 */
extern cl4_result_t sk_x_000839d8();   /* FUN_000839d8 */
extern unsigned long sk_x_000839f8();   /* FUN_000839f8 */
extern unsigned long sk_x_0008409c();   /* FUN_0008409c */
extern unsigned long sk_x_00084180();   /* FUN_00084180 */
extern unsigned long sk_x_00084220();   /* FUN_00084220 */
extern unsigned long sk_x_00084234();   /* FUN_00084234 */
extern unsigned long sk_x_0008e1ec();   /* FUN_0008e1ec */
extern unsigned long sk_x_0009461c();   /* FUN_0009461c */
extern unsigned long sk_x_000a649c();   /* FUN_000a649c */
extern unsigned long sk_x_000a6f88();   /* FUN_000a6f88 */
extern unsigned long sk_x_000b430c();   /* FUN_000b430c */
extern unsigned long sk_x_000e72d4();   /* FUN_000e72d4 */
extern unsigned long sk_x_001a84f4();   /* FUN_001a84f4 */
extern unsigned long sk_x_001a8564();   /* FUN_001a8564 */
extern unsigned long sk_x_001afa84();   /* FUN_001afa84 */
extern unsigned long sk_x_001afe4c();   /* FUN_001afe4c */
extern unsigned long sk_x_001c9a1c();   /* FUN_001c9a1c */
extern unsigned long sk_x_001e9c00();   /* FUN_001e9c00 */
extern unsigned long sk_x_002298d4();   /* FUN_002298d4 */
extern unsigned long sk_x_0027ed7c();   /* FUN_0027ed7c */
extern unsigned long sk_x_002a4ab4();   /* FUN_002a4ab4 */
extern unsigned long sk_x_00310d68();   /* FUN_00310d68 */
extern unsigned long sk_x_0031986c();   /* FUN_0031986c */
extern unsigned long sk_x_00319f3c();   /* FUN_00319f3c */
extern unsigned long sk_x_0031dc0c();   /* FUN_0031dc0c */
extern unsigned long sk_x_003488bc();   /* FUN_003488bc */
extern unsigned long sk_x_00349530();   /* FUN_00349530 */
extern unsigned long sk_x_00349a54();   /* FUN_00349a54 */
extern unsigned long sk_x_0034a210();   /* FUN_0034a210 */
extern unsigned long sk_x_0034b05c();   /* FUN_0034b05c */
extern unsigned long sk_x_0034bb84();   /* FUN_0034bb84 */
extern unsigned long sk_x_0034bcf0();   /* FUN_0034bcf0 */
extern unsigned long sk_x_0034d004();   /* FUN_0034d004 */
extern unsigned long sk_x_0034d2b4();   /* FUN_0034d2b4 */
extern unsigned long sk_x_00350404();   /* FUN_00350404 */
extern unsigned long sk_x_00350500();   /* FUN_00350500 */
extern unsigned long sk_x_0035050c();   /* FUN_0035050c */
extern cl4_result_t sk_x_00350518();   /* FUN_00350518 */
extern unsigned long sk_x_00350548();   /* FUN_00350548 */
extern unsigned long sk_x_00350624();   /* FUN_00350624 */
extern unsigned long sk_x_00350744();   /* FUN_00350744 */
extern unsigned long sk_x_00350750();   /* FUN_00350750 */
extern unsigned long sk_x_00350798();   /* FUN_00350798 */
extern unsigned long sk_x_003507e0();   /* FUN_003507e0 */
extern unsigned long sk_x_00350878();   /* FUN_00350878 */
extern unsigned long sk_x_00350968();   /* FUN_00350968 */
extern unsigned long sk_x_003509c8();   /* FUN_003509c8 */
extern unsigned long sk_x_00350b54();   /* FUN_00350b54 */
extern unsigned long sk_x_00350c5c();   /* FUN_00350c5c */
extern unsigned long sk_x_003510a0();   /* FUN_003510a0 */
extern unsigned long sk_x_00351384();   /* FUN_00351384 */
extern unsigned long sk_x_003513b4();   /* FUN_003513b4 */
extern unsigned long sk_x_0035187c();   /* FUN_0035187c */
extern unsigned long sk_x_00351d24();   /* FUN_00351d24 */
extern unsigned long sk_x_00351da8();   /* FUN_00351da8 */
extern unsigned long sk_x_00351e3c();   /* FUN_00351e3c */
extern unsigned long sk_x_00351f10();   /* FUN_00351f10 */
extern unsigned long sk_x_00352018();   /* FUN_00352018 */
extern unsigned long sk_x_00352efc();   /* FUN_00352efc */
extern unsigned long sk_x_00353080();   /* FUN_00353080 */
extern unsigned long sk_x_00353498();   /* FUN_00353498 */
extern unsigned long sk_x_00353930();   /* FUN_00353930 */
extern cl4_result_t sk_x_00356b98();   /* FUN_00356b98 */
extern unsigned long sk_x_003591d0();   /* FUN_003591d0 */
extern unsigned long sk_x_003593c0();   /* FUN_003593c0 */
extern cl4_result_t sk_x_0035a7e8();   /* FUN_0035a7e8 */
extern unsigned long sk_x_0035ac70();   /* FUN_0035ac70 */
extern unsigned long sk_x_00369340();   /* FUN_00369340 */
extern unsigned long sk_x_0036986c();   /* FUN_0036986c */
extern unsigned long sk_x_0036993c();   /* FUN_0036993c */
extern unsigned long sk_x_0036a9d4();   /* FUN_0036a9d4 */
extern unsigned long sk_x_0036b118();   /* FUN_0036b118 */
extern unsigned long sk_x_0036b270();   /* FUN_0036b270 */
extern unsigned long sk_x_00377824();   /* FUN_00377824 */
extern unsigned long sk_x_00377bec();   /* FUN_00377bec */
extern unsigned long sk_x_00377dcc();   /* FUN_00377dcc */
extern unsigned long sk_x_0039a128();   /* FUN_0039a128 */
extern unsigned long sk_x_003a25d4();   /* FUN_003a25d4 */
extern unsigned long sk_x_003d4658();   /* FUN_003d4658 */
extern unsigned long sk_x_003e63a8();   /* FUN_003e63a8 */
extern unsigned long sk_x_003eefc0();   /* FUN_003eefc0 */
extern unsigned long sk_x_003ef544();   /* FUN_003ef544 */
extern unsigned long sk_x_003ef924();   /* FUN_003ef924 */
extern unsigned long sk_x_003fcc1c();   /* FUN_003fcc1c */
extern unsigned long sk_x_003fcc4c();   /* FUN_003fcc4c */
extern unsigned long sk_x_003fd194();   /* FUN_003fd194 */
extern unsigned long sk_x_003fd25c();   /* FUN_003fd25c */
extern unsigned long sk_x_00406268();   /* FUN_00406268 */
extern unsigned long sk_x_00406288();   /* FUN_00406288 */
extern unsigned long sk_x_004062a8();   /* FUN_004062a8 */
extern unsigned long sk_x_004062c8();   /* FUN_004062c8 */
extern unsigned long sk_x_004062e8();   /* FUN_004062e8 */
extern unsigned long sk_x_00406374();   /* FUN_00406374 */
extern unsigned long sk_x_00406394();   /* FUN_00406394 */
extern unsigned long sk_x_004063b4();   /* FUN_004063b4 */
extern unsigned long sk_x_00406420();   /* FUN_00406420 */
extern unsigned long sk_x_00406490();   /* FUN_00406490 */
extern unsigned long sk_x_0040652c();   /* FUN_0040652c */
extern unsigned long sk_x_0040654c();   /* FUN_0040654c */
extern unsigned long sk_x_00406574();   /* FUN_00406574 */
extern unsigned long sk_x_00406590();   /* FUN_00406590 */
extern unsigned long sk_x_00406608();   /* FUN_00406608 */
extern unsigned long sk_x_004066bc();   /* FUN_004066bc */
extern unsigned long sk_x_00406704();   /* FUN_00406704 */
extern unsigned long sk_x_0040676c();   /* FUN_0040676c */
extern cl4_result_t sk_x_0040678c();   /* FUN_0040678c */
extern unsigned long sk_x_0040679c();   /* FUN_0040679c */
extern unsigned long sk_x_004067b8();   /* FUN_004067b8 */
extern unsigned long sk_x_004067f8();   /* FUN_004067f8 */
extern unsigned long sk_x_0040683c();   /* FUN_0040683c */
extern unsigned long sk_x_0040684c();   /* FUN_0040684c */
extern unsigned long sk_x_0040686c();   /* FUN_0040686c */
extern cl4_result_t sk_x_00406894();   /* FUN_00406894 */
extern unsigned long sk_x_004068bc();   /* FUN_004068bc */
extern unsigned long sk_x_004068f4();   /* FUN_004068f4 */
extern unsigned long sk_x_0040691c();   /* FUN_0040691c */
extern unsigned long sk_x_004069b0();   /* FUN_004069b0 */
extern unsigned long sk_x_004069c4();   /* FUN_004069c4 */
extern unsigned long sk_x_004069ec();   /* FUN_004069ec */
extern unsigned long sk_x_00406a24();   /* FUN_00406a24 */
extern unsigned long sk_x_00406ab4();   /* FUN_00406ab4 */
extern unsigned long sk_x_00406ac4();   /* FUN_00406ac4 */
extern unsigned long sk_x_00406b54();   /* FUN_00406b54 */
extern unsigned long sk_x_00406bb4();   /* FUN_00406bb4 */
extern unsigned long sk_x_00406bd4();   /* FUN_00406bd4 */
extern unsigned long sk_x_00406be4();   /* FUN_00406be4 */
extern unsigned long sk_x_00406c1c();   /* FUN_00406c1c */
extern unsigned long sk_x_00406c5c();   /* FUN_00406c5c */
extern unsigned long sk_x_00406cf0();   /* FUN_00406cf0 */
extern unsigned long sk_x_00406d70();   /* FUN_00406d70 */
extern unsigned long sk_x_00406dd0();   /* FUN_00406dd0 */
extern unsigned long sk_x_00406e34();   /* FUN_00406e34 */
extern cl4_result_t sk_x_00406e64();   /* FUN_00406e64 */
extern unsigned long sk_x_00406e8c();   /* FUN_00406e8c */
extern unsigned long sk_x_00406ee4();   /* FUN_00406ee4 */
extern unsigned long sk_x_00406f08();   /* FUN_00406f08 */
extern unsigned long sk_x_00406f50();   /* FUN_00406f50 */
extern unsigned long sk_x_00406fb0();   /* FUN_00406fb0 */
extern unsigned long sk_x_00406fd4();   /* FUN_00406fd4 */
extern unsigned long sk_x_00406fe0();   /* FUN_00406fe0 */
extern unsigned long sk_x_00407000();   /* FUN_00407000 */
extern unsigned long sk_x_0040700c();   /* FUN_0040700c */
extern unsigned long sk_x_00407018();   /* FUN_00407018 */
extern unsigned long sk_x_00407030();   /* FUN_00407030 */
extern unsigned long sk_x_004070a0();   /* FUN_004070a0 */
extern unsigned long sk_x_004070d8();   /* FUN_004070d8 */
extern unsigned long sk_x_004070e4();   /* FUN_004070e4 */
extern unsigned long sk_x_00407100();   /* FUN_00407100 */
extern unsigned long sk_x_0040711c();   /* FUN_0040711c */
extern unsigned long sk_x_00407128();   /* FUN_00407128 */
extern unsigned long sk_x_004071c0();   /* FUN_004071c0 */
extern unsigned long sk_x_004071d0();   /* FUN_004071d0 */
extern unsigned long sk_x_00407214();   /* FUN_00407214 */
extern unsigned long sk_x_00407248();   /* FUN_00407248 */
extern unsigned long sk_x_00407280();   /* FUN_00407280 */
extern unsigned long sk_x_004072c0();   /* FUN_004072c0 */
extern unsigned long sk_x_00407374();   /* FUN_00407374 */
extern unsigned long sk_x_00407444();   /* FUN_00407444 */
extern unsigned long sk_x_00407450();   /* FUN_00407450 */
extern unsigned long sk_x_00407478();   /* FUN_00407478 */
extern unsigned long sk_x_00407484();   /* FUN_00407484 */
extern unsigned long sk_x_004074c4();   /* FUN_004074c4 */
extern unsigned long sk_x_00407504();   /* FUN_00407504 */
extern unsigned long sk_x_00407520();   /* FUN_00407520 */
extern unsigned long sk_x_0040752c();   /* FUN_0040752c */
extern unsigned long sk_x_00407594();   /* FUN_00407594 */
extern unsigned long sk_x_004075a4();   /* FUN_004075a4 */
extern unsigned long sk_x_004075d0();   /* FUN_004075d0 */
extern unsigned long sk_x_00407604();   /* FUN_00407604 */
extern unsigned long sk_x_00407610();   /* FUN_00407610 */
extern unsigned long sk_x_0040764c();   /* FUN_0040764c */
extern unsigned long sk_x_00407700();   /* FUN_00407700 */
extern unsigned long sk_x_00407764();   /* FUN_00407764 */
extern unsigned long sk_x_004077cc();   /* FUN_004077cc */
extern unsigned long sk_x_00407814();   /* FUN_00407814 */
extern unsigned long sk_x_00407830();   /* FUN_00407830 */
extern unsigned long sk_x_0040785c();   /* FUN_0040785c */
extern unsigned long sk_x_00407878();   /* FUN_00407878 */
extern unsigned long sk_x_004078c0();   /* FUN_004078c0 */
extern unsigned long sk_x_004078e8();   /* FUN_004078e8 */
extern unsigned long sk_x_004078f4();   /* FUN_004078f4 */
extern unsigned long sk_x_0040790c();   /* FUN_0040790c */
extern unsigned long sk_x_00407960();   /* FUN_00407960 */
extern unsigned long sk_x_00407990();   /* FUN_00407990 */
extern unsigned long sk_x_004079a8();   /* FUN_004079a8 */
extern unsigned long sk_x_004079b4();   /* FUN_004079b4 */
extern unsigned long sk_x_004079cc();   /* FUN_004079cc */
extern unsigned long sk_x_00407ac4();   /* FUN_00407ac4 */
extern unsigned long sk_x_00407adc();   /* FUN_00407adc */
extern unsigned long sk_x_00407afc();   /* FUN_00407afc */
extern unsigned long sk_x_00407b18();   /* FUN_00407b18 */
extern unsigned long sk_x_00407b48();   /* FUN_00407b48 */
extern unsigned long sk_x_00407b80();   /* FUN_00407b80 */
extern unsigned long sk_x_00407bf8();   /* FUN_00407bf8 */
extern unsigned long sk_x_00407c04();   /* FUN_00407c04 */
extern unsigned long sk_x_00407c78();   /* FUN_00407c78 */
extern unsigned long sk_x_00407c8c();   /* FUN_00407c8c */
extern unsigned long sk_x_00407ca0();   /* FUN_00407ca0 */
extern cl4_result_t sk_x_00407ce4();   /* FUN_00407ce4 */
extern unsigned long sk_x_00407d14();   /* FUN_00407d14 */
extern unsigned long sk_x_00407db0();   /* FUN_00407db0 */
extern unsigned long sk_x_00407e10();   /* FUN_00407e10 */
extern unsigned long sk_x_00407e58();   /* FUN_00407e58 */
extern unsigned long sk_x_00407ea0();   /* FUN_00407ea0 */
extern unsigned long sk_x_00407f60();   /* FUN_00407f60 */
extern unsigned long sk_x_00407fcc();   /* FUN_00407fcc */
extern unsigned long sk_x_00408038();   /* FUN_00408038 */
extern unsigned long sk_x_0040807c();   /* FUN_0040807c */
extern unsigned long sk_x_00408094();   /* FUN_00408094 */
extern unsigned long sk_x_004080b0();   /* FUN_004080b0 */
extern unsigned long sk_x_004080cc();   /* FUN_004080cc */
extern unsigned long sk_x_00408108();   /* FUN_00408108 */
extern unsigned long sk_x_004081b4();   /* FUN_004081b4 */
extern unsigned long sk_x_00408280();   /* FUN_00408280 */
extern unsigned long sk_x_004082a8();   /* FUN_004082a8 */
extern unsigned long sk_x_00408328();   /* FUN_00408328 */
extern cl4_result_t sk_x_00408354();   /* FUN_00408354 */
extern unsigned long sk_x_00408374();   /* FUN_00408374 */
extern unsigned long sk_x_0040838c();   /* FUN_0040838c */
extern unsigned long sk_x_004083c0();   /* FUN_004083c0 */
extern unsigned long sk_x_004083cc();   /* FUN_004083cc */
extern unsigned long sk_x_004083d8();   /* FUN_004083d8 */
extern unsigned long sk_x_004083f0();   /* FUN_004083f0 */
extern unsigned long sk_x_00408404();   /* FUN_00408404 */
extern unsigned long sk_x_00408410();   /* FUN_00408410 */
extern unsigned long sk_x_00408440();   /* FUN_00408440 */
extern unsigned long sk_x_00408460();   /* FUN_00408460 */
extern unsigned long sk_x_00408560();   /* FUN_00408560 */
extern unsigned long sk_x_004085b4();   /* FUN_004085b4 */
extern unsigned long sk_x_0040880c();   /* FUN_0040880c */
extern unsigned long sk_x_00408898();   /* FUN_00408898 */
extern unsigned long sk_x_004088a0();   /* FUN_004088a0 */
extern unsigned long sk_x_00408c4c();   /* FUN_00408c4c */
extern unsigned long sk_x_00408db8();   /* FUN_00408db8 */
extern unsigned long sk_x_00409354();   /* FUN_00409354 */
extern unsigned long sk_x_00409414();   /* FUN_00409414 */
extern unsigned long sk_x_00409484();   /* FUN_00409484 */
extern unsigned long sk_x_00409c10();   /* FUN_00409c10 */
extern unsigned long sk_x_00409c1c();   /* FUN_00409c1c */
extern unsigned long sk_x_00409c24();   /* FUN_00409c24 */
extern unsigned long sk_x_0040a688();   /* FUN_0040a688 */
extern unsigned long sk_x_0040a8d8();   /* FUN_0040a8d8 */
extern unsigned long sk_x_0040a9b0();   /* FUN_0040a9b0 */
extern unsigned long sk_x_0040a9f4();   /* FUN_0040a9f4 */
extern unsigned long sk_x_0040aa98();   /* FUN_0040aa98 */
extern unsigned long sk_x_0040aac8();   /* FUN_0040aac8 */
extern unsigned long sk_x_0040ab60();   /* FUN_0040ab60 */
extern unsigned long sk_x_0040ada4();   /* FUN_0040ada4 */
extern unsigned long sk_x_0040bb18();   /* FUN_0040bb18 */
extern unsigned long sk_x_0040bd24();   /* FUN_0040bd24 */
extern unsigned long sk_x_0040d07c();   /* FUN_0040d07c */


/* FUN_003e68f0 @ 0x003e68f0   (est. sk_capop_003e68f0)
 * Ghidra: void FUN_003e68f0(void)
 * This is the capability-operation dispatcher entry. It opens the op context
 * (x22), and branches on a one-bit flag at context offset 0xe5. The clear path
 * calls the reply dispatch through the context vtable (offset 0x80 -> +8), and
 * if the secondary flag at offset 0xe4 is also clear, walks the frame/length
 * fields, allocates a per-op frame for the pending message slot, links it into
 * the context, and tail-dispatches through an unrecovered jumptable. The set
 * path invokes the alternate reply handler through context offset 0xc0, then
 * both paths release the per-op frames (FUN_0040bd24) and recompose the
 * reply/message pair before a final tail dispatch.
 * Confidence: low
 * Notes: two UNRECOVERED_JUMPTABLE sites (0x003e6a3c, 0x003e69a8) — Ghidra
 *   "Too many branches"; extraout_x17 feeds the frame backlink; FUN_0040bb18
 *   is the op-frame allocator, FUN_0040bd24 the op-frame release. */
static void sk_capop_003e68f0(void)
{
    uint64_t r3;
    int64_t v2;
    uint64_t *slot;
    uint64_t extraout_x1 = /* extraout_x1 */ 0;
    uint64_t r5;
    uint64_t (*tail_00)(void);
    uint64_t (*tail)(void);
    uint64_t extraout_x17 = /* extraout_x17 */ 0;
    uint64_t r6;
    uint8_t *ctx = /* unaff_x22: current op context */ 0;
    cl4_result_t auVar7;

    r3 = sk_x_00407ca0();
    sk_x_0040700c();
    if ((*(uint8_t *)(ctx + 0xe5) & 1) == 0) {
        ((void (*)(uint64_t, uint64_t))(*(uint64_t *)(*(uint64_t *)(ctx + 0x80) + 8)))(
            *(uint64_t *)(ctx + 0x88), *(uint64_t *)(ctx + 0x60));
        if ((*(uint8_t *)(ctx + 0xe4) & 1) == 0) {
            v2 = *(int64_t *)(ctx + 0x40);
            sk_x_0040652c();
            sk_x_00406608();
            sk_x_004083cc();
            r3 = sk_x_00406e8c();
            *(uint64_t *)(ctx + 0xb0) = r3;
            sk_x_00406288();
            sk_x_0040bb18(*(uint32_t *)(v2 + 4));
            slot = (uint64_t *)sk_x_00406fe0();
            *(uint64_t **)(ctx + 0xb8) = slot;
            *slot = extraout_x17;
            sk_x_00407830();
            sk_x_004067b8();
            /* tail dispatch: indirect jump, jumptable at 0x003e6a3c not recovered by Ghidra */
            (*tail)();
            return;
        }
        r5 = 1;
    }
    else {
        ((void (*)(uint64_t, uint64_t, uint64_t, uint64_t))(*(uint64_t *)(ctx + 0xc0)))(
            *(uint64_t *)(ctx + 0xc8), *(uint64_t *)(ctx + 0x10),
            *(uint64_t *)(ctx + 0x88), *(uint64_t *)(ctx + 0x60));
        sk_x_00407bf8();
        r5 = extraout_x1;
    }
    r6 = *(uint64_t *)(ctx + 0x78);
    (void)0; /* uVar1 */
    sk_x_004075a4(*(uint64_t *)(ctx + 0x10), r5);
    sk_x_0040bd24(r6);
    sk_x_0040bd24(*(uint64_t *)(ctx + 0x58));
    auVar7 = sk_x_00406e64();
    sk_x_00407e58(auVar7.lo, auVar7.hi, r3);
    /* tail dispatch: indirect jump, jumptable at 0x003e69a8 not recovered by Ghidra */
    (*tail_00)();
    return;
}

/* FUN_003e74fc @ 0x003e74fc   (est. sk_capop_003e74fc)
 * Ghidra: void FUN_003e74fc(void)
 * This capability-operation runner is the main dispatch state machine for the
 * message-path. It fetches a pair of helper results, then on the zero-flag path
 * walks the frame/length fields, invokes the reply/message-slot helpers,
 * installs a fresh op frame (reply slot) linked into the context, and
 * tail-dispatches through an unrecovered jumptable. The alternative path
 * resolves the operation index, calls through the frame-table function pointer,
 * and releases the per-op frames before recomposing the reply/message pair.
 * Confidence: low
 * Notes: three UNRECOVERED_JUMPTABLE sites (0x003e77cc, 0x003e773c); LAB refs
 *   none; several extraout_xN locals are uninitialized call results; FUN_0040bd24
 *   is the per-op frame release. */
static void sk_capop_003e74fc(void)
{
    uint64_t r1;
    uint64_t r2;
    uint8_t in_ZR;
    uint64_t r3;
    uint64_t *slot;
    int64_t v5;
    uint64_t (*tail)(void);
    uint64_t (*tail_00)(void);
    uint64_t (*extraout_x8)(void) = /* extraout_x8 */ 0;
    uint64_t (*extraout_x8_00)(void) = /* extraout_x8_00 */ 0;
    uint64_t (*extraout_x8_01)(void) = /* extraout_x8_01 */ 0;
    uint64_t extraout_x8_02 = /* extraout_x8_02 */ 0;
    uint64_t r6;
    uint64_t (*extraout_x9)(void) = /* extraout_x9 */ 0;
    uint64_t (*extraout_x9_00)(void) = /* extraout_x9_00 */ 0;
    uint64_t extraout_x9_01 = /* extraout_x9_01 */ 0;
    uint64_t (*extraout_x9_02)(void) = /* extraout_x9_02 */ 0;
    uint64_t extraout_x10 = /* extraout_x10 */ 0;
    uint64_t extraout_x10_00 = /* extraout_x10_00 */ 0;
    uint64_t extraout_x17 = /* extraout_x17 */ 0;
    uint64_t extraout_x17_00 = /* extraout_x17_00 */ 0;
    uint64_t r7;
    int64_t v8;
    uint8_t *ctx = /* unaff_x22: current op context */ 0;
    int64_t v9;
    uint64_t *sl_10;
    cl4_result_t auVar11;

    r3 = sk_x_0040785c();
    sk_x_00407adc();
    r7 = *(uint64_t *)(ctx + 0xb8);
    sk_x_00406be4();
    if (0 /* in_ZR */) {
        v5 = *(int64_t *)(ctx + 0xa8);
        ((void (*)(uint64_t, uint64_t))(*(uint64_t *)(*(uint64_t *)(ctx + 0xf8) + 8)))(
            *(uint64_t *)(ctx + 0x108), *(uint64_t *)(ctx + 0xd8));
        sk_x_003507e0(*(uint64_t *)(v5 + 8));
        (*extraout_x8)();
        sk_x_00407764();
        (*extraout_x8_00)();
        tail_00 = *(uint64_t (**)(void))(ctx + 0xd8);
        sk_x_00350744(*(int64_t *)(ctx + 0x20) + (int64_t)*(int *)(ctx + 0x17c));
        auVar11 = sk_x_000839d8();
        sk_x_00406fb0(*(uint64_t *)(ctx + 0x110), auVar11.lo, auVar11.hi,
                      *(uint64_t *)(ctx + 0xe0));
        (*extraout_x8_01)();
        sk_x_00406420();
        if (0 /* in_ZR */) {
            v5 = *(int64_t *)(ctx + 0x58);
            sk_x_00353930(*(uint64_t *)(ctx + 0xe8), *(uint64_t *)(ctx + 0xf0),
                          *(uint64_t *)(ctx + 0xe0));
            *(uint64_t (**)(void))(ctx + 0x138) = extraout_x9;
            *(uint64_t *)(ctx + 0x140) = extraout_x10;
            (*extraout_x9)();
            sk_x_0040652c();
            sk_x_00406608();
            sk_x_004068f4();
            sk_x_00406268();
            sk_x_0040bb18(*(uint32_t *)(v5 + 4));
            slot = (uint64_t *)sk_x_00406fe0();
            *(uint64_t **)(ctx + 0x148) = slot;
            *slot = extraout_x17;
            sk_x_00406b54();
        }
        else {
            r3 = *(uint64_t *)(ctx + 0xd8);
            auVar11 = sk_x_00406894(*(uint64_t *)(ctx + 0xf8), *(uint64_t *)(ctx + 0x108),
                                    *(uint64_t *)(ctx + 0xf0));
            *(uint64_t (**)(void))(ctx + 0x118) = extraout_x9_02;
            *(uint64_t *)(ctx + 0x120) = extraout_x10_00;
            ((void (*)(uint64_t, uint64_t, uint64_t))extraout_x9_02)(auVar11.lo, auVar11.hi, r3);
            sk_x_004067f8();
            sk_x_003fcc1c();
            v5 = sk_x_004062c8();
            sk_x_0040bb18(*(uint32_t *)(v5 + 4));
            slot = (uint64_t *)sk_x_00406fe0();
            *(uint64_t **)(ctx + 0x128) = slot;
            *slot = extraout_x17_00;
            sk_x_00406ac4();
        }
        sk_x_00408404();
        sk_x_00407504();
        /* tail dispatch: indirect jump, jumptable at 0x003e77cc not recovered by Ghidra */
        (*tail_00)();
        return;
    }
    v9 = (int64_t)*(int *)(ctx + 0x17c);
    r6 = *(uint64_t *)(ctx + 0xe0);
    v5 = *(int64_t *)(ctx + 0xe8);
    r1 = *(uint64_t *)(ctx + 0xd0);
    r2 = *(uint64_t *)(ctx + 0xd8);
    v8 = *(int64_t *)(ctx + 0x20);
    sl_10 = (uint64_t *)(*(uint64_t *)(ctx + 0xc0) + 0x20);
    tail_00 = (uint64_t (*)(void))*sl_10;
    sk_x_00350968(r1);
    (*tail_00)();
    slot = (uint64_t *)(v5 + 8);
    (*(uint64_t (*)(uint64_t, uint64_t))*slot)(v8 + v9, r6);
    sk_x_00408440();
    (*extraout_x9_00)();
    sk_x_00350750(v8 + v9);
    sk_x_0040764c();
    (*tail_00)();
    sk_x_004069ec();
    r6 = *(uint64_t *)(ctx + 0x38);
    sk_x_00406cf0();
    sk_x_0040bd24(r7);
    sk_x_0040bd24(v8);
    sk_x_0040bd24((uint64_t)tail_00);
    sk_x_0040bd24(r2);
    sk_x_0040bd24(r1);
    sk_x_0040bd24(v9);
    sk_x_0040bd24((uint64_t)slot);
    sk_x_0040bd24((uint64_t)sl_10);
    sk_x_0040bd24(extraout_x9_01);
    sk_x_0040bd24(extraout_x8_02);
    sk_x_0040bd24(r6);
    auVar11 = sk_x_0040678c();
    sk_x_00407504(auVar11.lo, auVar11.hi, r3);
    /* tail dispatch: indirect jump, jumptable at 0x003e773c not recovered by Ghidra */
    (*tail)();
    return;
}

/* FUN_003e9c34 @ 0x003e9c34   (est. sk_capop_003e9c34)
 * Ghidra: void FUN_003e9c34(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,undefined8 param_5)
 * This is a capability-operation entry that seeds a per-invocation op frame on
 * the current op context: it stores the fourth argument at context offset 0x10,
 * allocates a fresh op frame of the given size (DAT_005a00cc), links it back to
 * the running context, installs the shared reply/message vtable (DAT_004060bc),
 * then dispatches the operation into the in-slice frame driver 0x003e838c.
 * Confidence: low
 * Notes: DAT_005a00cc is the op-frame size, DAT_004060bc the frame vtable
 *   address; the inner worker is in-slice (sk_capop_003e838c). */
static void sk_capop_003e9c34(uint64_t arg1, uint64_t arg2, uint64_t arg3,
                              uint64_t arg4, uint64_t arg5)
{
    uint8_t *ctx = /* unaff_x22: current op context */ 0;
    int64_t *frame;

    *(uint64_t *)(ctx + 0x10) = arg4;
    frame = (int64_t *)sk_x_0040bb18(sk_g_005a00cc);
    *(int64_t **)(ctx + 0x18) = frame;
    *frame = (int64_t)ctx;
    frame[1] = (int64_t)&sk_g_004060bc;
    sk_capop_003e838c(frame, arg1, arg2, arg3, arg5);
    return;
}

/* FUN_003ea494 @ 0x003ea494   (est. sk_capop_003ea494)
 * Ghidra: void FUN_003ea494(void)
 * Short capability-operation wrapper: runs five out-of-slice prep/release
 * helpers, then tail-dispatches through an unrecovered jumptable.
 * Confidence: low
 * Notes: UNRECOVERED_JUMPTABLE at 0x003ea4e8 — Ghidra "Too many branches". */
static void sk_capop_003ea494(void)
{
    uint64_t (*tail)(void);

    sk_x_00407000();
    sk_x_00407604();
    sk_x_00408374();
    sk_x_00406ee4();
    sk_x_0040bd24();
    sk_x_0040678c();
    /* tail dispatch: indirect jump, jumptable at 0x003ea4e8 not recovered by Ghidra */
    (*tail)();
    return;
}

/* FUN_003eaf4c @ 0x003eaf4c   (est. sk_capop_003eaf4c)
 * Ghidra: void FUN_003eaf4c(void)
 * Capability-operation helper: resolves the operation value, calls the 
 * two-slot helper pair (through a vtable at the previous call result), then
 * writes the {unaff_x23, unaff_x22} pair into the frame slot indexed by the
 * prior call result's length field. Returns void.
 * Confidence: low
 * Notes: indirect call through *(extraout_x16 + 0x20); unaff_x22/x23 are
 *   incoming register values stored into the frame; FUN_00350548 reseeds a
 *   table index. */
static void sk_capop_003eaf4c(void)
{
    uint64_t *slot;
    uint64_t v2;
    int64_t v3;
    uint64_t extraout_x1 = /* extraout_x1 */ 0;
    uint64_t in_x3 = /* in_x3 */ 0;
    uint64_t (*in_x5)(void) = /* in_x5 */ 0;
    int64_t extraout_x8 = /* extraout_x8 */ 0;
    int64_t extraout_x16 = /* extraout_x16 */ 0;
    uint64_t unaff_x22 = /* unaff_x22 */ 0;
    uint64_t unaff_x23 = /* unaff_x23 */ 0;

    v2 = sk_x_00406e34();
    sk_x_003509c8(in_x3, v2, v2);
    ((void (*)(uint64_t, uint64_t, uint64_t))(*(uint64_t *)(extraout_x16 + 0x20)))(
        extraout_x8, extraout_x1, in_x3);
    sk_x_00350548(0);
    v3 = (*in_x5)();
    slot = (uint64_t *)(extraout_x8 + *(int *)(v3 + 0x24));
    *slot = unaff_x23;
    slot[1] = unaff_x22;
    return;
}

/* FUN_003ebbd4 @ 0x003ebbd4   (est. sk_capop_003ebbd4)
 * Ghidra: void FUN_003ebbd4(void)
 * Capability-operation runner with a two-way dispatch: when the one-byte flag
 * at context offset 0xd8 equals 0x01 it calls the alternate reply handler
 * through context offset 0xb8 and builds a {result, 0} pair; otherwise it calls
 * the primary reply dispatch through the vtable at context offset 0x80 (+8) and
 * recomposes a pair from the helper. It then hands the pair to the commit
 * helper, releases the per-op frames, and tail-dispatches through an unrecovered
 * jumptable.
 * Confidence: low
 * Notes: UNRECOVERED_JUMPTABLE at 0x003ebc84 — "Too many branches"; the
 *   auVar3 pair is assembled from the helper results. */
static void sk_capop_003ebbd4(void)
{
    uint64_t r1;
    uint64_t r2;
    uint64_t (*tail)(void);
    uint8_t *ctx = /* unaff_x22: current op context */ 0;
    cl4_result_t auVar3;

    sk_x_00406fd4();
    if (*(char *)(ctx + 0xd8) == '\x01') {
        r2 = ((uint64_t (*)(uint64_t, uint64_t, uint64_t, uint64_t))(*(uint64_t *)(ctx + 0xb8)))(
            *(uint64_t *)(ctx + 0xc0), *(uint64_t *)(ctx + 0x10),
            *(uint64_t *)(ctx + 0x88), *(uint64_t *)(ctx + 0x60));
        auVar3.hi = 0;
        auVar3.lo = r2;
    }
    else {
        ((void (*)(uint64_t, uint64_t))(*(uint64_t *)(*(uint64_t *)(ctx + 0x80) + 8)))(
            *(uint64_t *)(ctx + 0x88), *(uint64_t *)(ctx + 0x60));
        auVar3 = sk_x_00408354();
    }
    sk_x_00407960(auVar3.lo, auVar3.hi);
    r1 = *(uint64_t *)(ctx + 0x58);
    sk_x_004070a0(*(uint64_t *)(ctx + 0x10));
    sk_x_0040bd24();
    sk_x_0040bd24(r1);
    sk_x_0040678c();
    /* tail dispatch: indirect jump, jumptable at 0x003ebc84 not recovered by Ghidra */
    (*tail)();
    return;
}

/* FUN_003ec144 @ 0x003ec144   (est. sk_capop_003ec144)
 * Ghidra: void FUN_003ec144(void)
 * Capability-operation wrapper: allocates a fresh op frame from the in-slice
 * allocator (sk_capop_003ec0c4), then feeds the first slot of that frame to an
 * out-of-slice consumer to drive the operation to completion.
 * Confidence: low
 * Notes: the allocator is in-slice (sk_capop_003ec0c4); the consumer is
 *   out-of-slice (sk_x_0036b270). */
static void sk_capop_003ec144(void)
{
    uint64_t *slot;

    slot = (uint64_t *)sk_capop_003ec0c4();
    sk_x_0036b270(*slot);
    return;
}

/* FUN_003ec758 @ 0x003ec758   (est. sk_capop_003ec758)
 * Ghidra: void FUN_003ec758(void)
 * Capability-operation wrapper: runs two out-of-slice prep helpers, then reaches
 * a non-returning software-breakpoint trap (Does not return).
 * Confidence: low
 * Notes: SoftwareBreakpoint(1, 0x3ec780) is the trap site; Ghidra flags the
 *   path "Does not return". */
static void sk_capop_003ec758(void)
{
    sk_x_00407030();
    sk_x_00406490();
    /* WARNING: Does not return */
    SoftwareBreakpoint(1, 0x3ec780);
}

/* FUN_003ec9c4 @ 0x003ec9c4   (est. sk_capop_003ec9c4)
 * Ghidra: long FUN_003ec9c4(int param_1)
 * This is the task-priority classifier. It folds the raw priority index through
 * (index-9)>>2 & 0x3f and (index-9)*0x40, and when that combined value is < 5
 * switches to a table of task-priority strings: index 2 -> "TaskPriority.low"
 * (0x5dc090), 3 -> "TaskPriority.medium" (0x5dc070), 4 -> "TaskPriority.high"
 * (0x5dc050), each returning an adjusted error (the per-string helper result
 * minus a small constant), default -0x2fffffffffffffe9. Otherwise (the "d" path)
 * it runs a Swift Concurrency task initializer sequence and returns the same
 * sentinel. This is a Swift runtime / cL4 priority validation path.
 * Confidence: low
 * Notes: string refs s_TaskPriority_low_005dc090 / _medium_005dc070 /
 *   _high_005dc050; UINT_006775b0 + FUN_00027724 build a trap/message; several
 *   extraout_x8 result locals. The sentinel -0x2fffffffffffffe9 recurs. */
static int64_t sk_capop_003ec9c4(int arg1)
{
    uint32_t v1;
    uint32_t v2;
    int64_t r3;
    int64_t extraout_x8 = /* extraout_x8 */ 0;
    int64_t extraout_x8_00 = /* extraout_x8_00 */ 0;
    int64_t extraout_x8_01 = /* extraout_x8_01 */ 0;
    uint64_t local_28;

    v2 = (uint32_t)(arg1 - 9) >> 2 & 0x3f;
    v1 = (uint32_t)(arg1 - 9) * 0x40;
    if ((v2 | v1 & 0xff) < 5) {
        switch (v2 | v1 & 0xff) {
        default:
            r3 = -0x2fffffffffffffe9;
            break;
        case 1:
            goto caseD_1;
        case 2:
            sk_x_004078c0(&sk_g_005dc090);
            r3 = extraout_x8_00 - 7;
            break;
        case 3:
            sk_x_004078c0(&sk_g_005dc070);
            r3 = extraout_x8 - 4;
            break;
        case 4:
            sk_x_004078c0(&sk_g_005dc050);
            r3 = extraout_x8_01 - 6;
        }
    }
    else {
    caseD_1:
        sk_x_000b430c();
        sk_x_002a4ab4(0x10);
        sk_x_003a25d4(local_28);
        {
            void (*trap)(uint64_t, uint64_t) = (void (*)(uint64_t, uint64_t))sk_x_00027724(0x670738);
            (*trap)((uint64_t)&sk_g_006775b0, 0x670738);
        }
        sk_x_000e72d4();
        sk_x_003a25d4(0x670738);
        sk_x_00408108();
        r3 = -0x2fffffffffffffe9;
    }
    return r3;
}

/* FUN_003ecd9c @ 0x003ecd9c   (est. sk_capop_003ecd9c)
 * Ghidra: void FUN_003ecd9c(void)
 * Simple capability-operation wrapper: queries the per-op state and, when the
 * result is non-null, runs a teardown helper.
 * Confidence: low
 * Notes: sk_x_004088a0 is the state getter; sk_x_001e9c00 the teardown. */
static void sk_capop_003ecd9c(void)
{
    int64_t v1;

    v1 = sk_x_004088a0();
    if (v1 != 0) {
        sk_x_001e9c00();
    }
    return;
}

/* FUN_003ed6d0 @ 0x003ed6d0   (est. sk_capop_003ed6d0)
 * Ghidra: void FUN_003ed6d0(undefined8 param_1,undefined8 param_2,undefined8 param_3,int *param_4,undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,long param_9,undefined8 param_10,undefined8 param_11)
 * This is the general capability-operation entry that seeds a per-invocation
 * op frame from an 11-argument invocation. It records the request fields (arg9,
 * arg11, arg2, arg3) into the context, allocates a message buffer whose size is
 * taken from the frame descriptor, allocates a reply-slot frame, links it to the
 * context with a saved return label, then dispatches the operation by calling
 * through a code pointer derived from param_4 (base + offset*8... actually the
 * decompiler folds the offset into the function pointer).
 * Confidence: low
 * Notes: FUN_0040bb18 is the allocator, FUN_0040a9f4 the message-pair builder;
 *   LAB_003ed834 is the saved return label; UNRECOVERED_JUMPTABLE at 0x003ed830
 *   is the tail dispatch (rendered as the direct call through param_4+offset). */
static void sk_capop_003ed6d0(uint64_t arg1, uint64_t arg2, uint64_t arg3, int *arg4,
                              uint64_t arg5, uint64_t arg6, uint64_t arg7, uint64_t arg8,
                              int64_t arg9, uint64_t arg10, uint64_t arg11)
{
    int v1;
    uint64_t v2;
    uint64_t v3;
    int64_t *frame;
    int64_t v5;
    uint8_t *ctx = /* unaff_x22: current op context */ 0;

    *(int64_t *)(ctx + 0x20) = arg9;
    *(uint64_t *)(ctx + 0x28) = arg11;
    *(uint64_t *)(ctx + 0x10) = arg2;
    *(uint64_t *)(ctx + 0x18) = arg3;
    v5 = *(int64_t *)(arg9 - 8);
    *(int64_t *)(ctx + 0x30) = v5;
    v2 = sk_x_0040bb18((uint64_t)(*(int64_t *)(v5 + 0x40) + 0xf) & 0xfffffffffffffff0);
    *(uint64_t *)(ctx + 0x38) = v2;
    v3 = sk_x_0040a9f4(arg6, arg7);
    *(uint64_t *)(ctx + 0x40) = v3;
    v1 = *arg4;
    frame = (int64_t *)sk_x_0040bb18(arg4[1]);
    *(int64_t **)(ctx + 0x48) = frame;
    *frame = (int64_t)ctx;
    frame[1] = (int64_t)0x003ed834 /* LAB_003ed834 */;
    /* tail dispatch: indirect jump, jumptable at 0x003ed830 not recovered by Ghidra */
    (*(void (*)(int64_t *, uint64_t, uint64_t, uint64_t, uint64_t))((char *)arg4 + v1))(
        frame, arg1, arg2, arg3, v2);
    return;
}

/* FUN_003ee5e8 @ 0x003ee5e8   (est. sk_capop_003ee5e8)
 * Ghidra: void FUN_003ee5e8(undefined8 param_1,undefined8 param_2,undefined8 param_3,long param_4,undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8)
 * Capability-operation entry that records a message/result frame: it resolves
 * the current operation result, stores the payload fields into the context
 * (0x128, 0x130, 0x118, 0x120), then branches on arg4. When arg4 is null it
 * records the null-branch result; otherwise it runs the recovery/commit helper
 * sequence and records that result. Finally it stores the frame index and the
 * caller value (arg3) into the context and runs the epilogue.
 * Confidence: low
 * Notes: extraout_x8 locals carry the branch results; the epilogue is
 *   sk_x_00353080 + sk_x_00408db8. */
static void sk_capop_003ee5e8(uint64_t arg1, uint64_t arg2, uint64_t arg3, int64_t arg4,
                              uint64_t arg5, uint64_t arg6, uint64_t arg7, uint64_t arg8)
{
    uint64_t v1;
    uint64_t (*extraout_x8)(void) = /* extraout_x8 */ 0;
    uint64_t extraout_x8_00 = /* extraout_x8_00 */ 0;
    uint64_t extraout_x8_01 = /* extraout_x8_01 */ 0;
    uint8_t *ctx = /* unaff_x22: current op context */ 0;

    v1 = sk_x_00406fd4();
    *(uint64_t *)(ctx + 0x128) = arg7;
    *(uint64_t *)(ctx + 0x130) = arg8;
    *(uint64_t *)(ctx + 0x118) = v1;
    *(uint64_t *)(ctx + 0x120) = arg6;
    if (arg4 == 0) {
        sk_x_00407248();
        v1 = extraout_x8_01;
    }
    else {
        sk_x_00351da8();
        sk_x_003d4658(arg5);
        sk_x_0034bcf0();
        (*extraout_x8)();
        sk_x_0008e1ec();
        v1 = extraout_x8_00;
    }
    *(uint64_t *)(ctx + 0x138) = v1;
    *(uint64_t *)(ctx + 0x140) = arg3;
    sk_x_00353080();
    sk_x_00408db8();
    return;
}

/* FUN_003e6be8 @ 0x003e6be8   (est. sk_capop_003e6be8)
 * Ghidra: void FUN_003e6be8(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,undefined8 param_5)
 * This is a capability-operation entry that seeds the per-invocation op frame on the
 * current op context (unaff_x22). It stores the fourth argument into the context at
 * offset 0x10, then allocates a fresh op frame of the given size, links the frame to
 * the running context, and installs the shared reply/message vtable before dispatching
 * the actual operation into the frame-slot driver.
 * Confidence: low
 * Notes: DAT_005a00bc is an op-frame size, DAT_004060bc is the frame vtable address
 *   (taken by address); the inner worker is out-of-slice (sk_x_003e63a8). */
static void sk_capop_003e6be8(uint64_t arg1, uint64_t arg2, uint64_t arg3, uint64_t arg4, uint64_t arg5)
{
    uint8_t *ctx = /* unaff_x22: current op context */ 0;
    int64_t *frame;
    
    *(uint64_t *)(ctx + 0x10) = arg4;
    frame = (int64_t *)sk_x_0040bb18(sk_g_005a00bc);
    *(int64_t **)(ctx + 0x18) = frame;
    *frame = (int64_t)ctx;
    frame[1] = (int64_t)&sk_g_004060bc;
    sk_x_003e63a8(frame, arg1, arg2, arg3, arg5);
    return;
}

/* FUN_003e788c @ 0x003e788c   (est. sk_capop_003e788c)
 * Ghidra: void FUN_003e788c(void)
 * This is the capability-operation dispatcher hub. It performs a two-stage protocol:
 * first it consults the out-of-slice helper results and, when the zero-flag from the
 * preceding call is set, it tears down the op context by releasing every per-op frame
 * (a run of FUN_0040bd24 frame releases) then recomposes the reply/message pair and
 * tail-dispatches through an unrecovered jumptable. The alternative branch walks the
 * current frame/length fields, invokes the message-slot helpers, installs a fresh op
 * frame linked to a saved return label, and tail-dispatches through another
 * unrecovered jumptable.
 * Confidence: low
 * Notes: two UNRECOVERED_JUMPTABLE sites (0x003e7964 and 0x003e7a04) — Ghidra
 *   "Too many branches" / "Treating indirect jump as call"; LAB_003e7a08 is the
 *   saved return label; several extraout_xN locals are uninitialized call results. */
static void sk_capop_003e788c(void)
{
    int64_t v1;
    int64_t v2;
    uint8_t in_ZR;
    uint64_t r3;
    uint64_t r4;
    uint64_t *slot;
    uint64_t (*tail_00)(void);
    uint64_t (*tail)(void);
    uint64_t extraout_x8 = /* extraout_x8 */ 0;
    int64_t extraout_x8_00 = /* extraout_x8_00 */ 0;
    uint64_t (*extraout_x9)(void) = /* extraout_x9 */ 0;
    uint64_t extraout_x9_00 = /* extraout_x9_00 */ 0;
    uint64_t (*extraout_x9_01)(void) = /* extraout_x9_01 */ 0;
    uint64_t (*extraout_x16)(void) = /* extraout_x16 */ 0;
    uint64_t extraout_x17 = /* extraout_x17 */ 0;
    uint64_t r6;
    uint8_t *ctx = /* unaff_x22: current op context */ 0;
    cl4_result_t auVar7;

    r3 = sk_x_00407b18();
    sk_x_00407fcc();
    r6 = *(uint64_t *)(ctx + 0x60);
    r4 = sk_x_00406420();
    if (0 /* in_ZR */) {
        sk_x_0040711c(*(uint64_t *)(ctx + 0x70), r4, *(uint64_t *)(ctx + 0x68));
        (*extraout_x9)();
        sk_x_004069ec();
        r4 = *(uint64_t *)(ctx + 0x38);
        sk_x_0040686c();
        sk_x_0040bd24(r6);
        sk_x_0040bd24();
        sk_x_0040bd24();
        sk_x_0040bd24();
        sk_x_0040bd24();
        sk_x_0040bd24();
        sk_x_0040bd24();
        sk_x_0040bd24();
        sk_x_0040bd24(extraout_x9_00);
        sk_x_0040bd24(extraout_x8);
        sk_x_0040bd24(r4);
        auVar7 = sk_x_0040678c();
        sk_x_00407878(auVar7.lo, auVar7.hi, r3);
        /* tail dispatch: indirect jump, jumptable at 0x003e7964 not recovered by Ghidra */
        (*tail_00)();
        return;
    }
    v1 = *(int64_t *)(ctx + 0x18);
    v2 = *(int64_t *)(ctx + 0x20);
    sk_x_00406bd4(*(uint64_t *)(ctx + 0x80), *(uint64_t *)(ctx + 0x88));
    (*extraout_x9_01)();
    sk_x_004062a8(*(uint64_t *)(v2 + *(int *)(v1 + 0x34)));
    sk_x_0040bb18(*(uint32_t *)(extraout_x8_00 + 4));
    slot = (uint64_t *)sk_x_00406fe0();
    *(uint64_t **)(ctx + 0x158) = slot;
    *slot = extraout_x17;
    slot[1] = 0x003e7a08 /* LAB_003e7a08 */;
    tail = extraout_x16;
    sk_x_00407878(*(uint64_t *)(ctx + 0x40), *(uint64_t *)(ctx + 0x88), extraout_x16, r3);
    /* tail dispatch: indirect jump, jumptable at 0x003e7a04 not recovered by Ghidra */
    (*tail)();
    return;
}

/* FUN_003e9d04 @ 0x003e9d04   (est. sk_capop_003e9d04)
 * Ghidra: void FUN_003e9d04(void)
 * This capability operation runs a linear sequence of out-of-slice kernel helper
 * calls that prepare the invocation: it resets/finalizes several shared subsystems,
 * dereferences the global reply dispatch pointer, walks the frame length field to
 * index a slot, then tail-dispatches through an op-frame function pointer. The
 * unaff_x19 and unaff_x30 locals carry prior call results through the sequence.
 * Confidence: low
 * Notes: DAT_00658c80 is dereferenced as a code pointer (indirect call through the
 *   global); extraout_x9 and unaff_x19 are uninitialized call results used as
 *   function pointers. */
static void sk_capop_003e9d04(void)
{
    uint64_t (*extraout_x9)(void) = /* extraout_x9 */ 0;
    uint64_t (*unaff_x19)(void) = /* unaff_x19 */ 0;
    int64_t unaff_x21 = /* unaff_x21 */ 0;
    uint64_t unaff_x30 = /* unaff_x30 */ 0;

    sk_x_00084220();
    sk_x_0008409c();
    sk_x_0040654c();
    sk_x_003513b4();
    sk_x_00377824();
    sk_x_00351f10();
    sk_x_0007c1a4();
    ((void (*)(void))sk_g_00658c80)();
    sk_x_0034b05c();
    sk_x_00407100();
    sk_x_00350518();
    (*extraout_x9)();
    sk_x_004082a8((int64_t)*(int *)(unaff_x21 + 0x34));
    sk_x_00407700();
    (*unaff_x19)();
    sk_x_00084234(unaff_x30);
    return;
}

/* FUN_003ea4ec @ 0x003ea4ec   (est. sk_capop_003ea4ec)
 * Ghidra: void FUN_003ea4ec(void)
 * This capability operation invokes three out-of-slice prep helpers, releases a
 * per-op frame, then tail-dispatches through an unrecovered jumptable. It is a
 * short wrapper in the op dispatch chain.
 * Confidence: low
 * Notes: UNRECOVERED_JUMPTABLE at 0x003ea53c — Ghidra "Too many branches" /
 *   "Treating indirect jump as call". */
static void sk_capop_003ea4ec(void)
{
    uint64_t (*tail)(void);

    sk_x_00407000();
    sk_x_00408038();
    sk_x_0040bd24();
    sk_x_00407128();
    /* tail dispatch: indirect jump, jumptable at 0x003ea53c not recovered by Ghidra */
    (*tail)();
    return;
}

/* FUN_003eafc8 @ 0x003eafc8   (est. sk_capop_003eafc8)
 * Ghidra: void FUN_003eafc8(undefined8 param_1,long param_2)
 * This capability operation reads the frame's length field (offset 0x24), re-seeds
 * the frame from the current message payload fields, then tail-dispatches through a
 * vtable entry at the previous call result, passing the slot index computed from the
 * running context plus the frame length and the resolved value.
 * Confidence: low
 * Notes: UNRECOVERED_JUMPTABLE at 0x003eb024 — "Treating indirect jump as call";
 *   the indirect call is through *(extraout_x16 + 0x10) with three arguments. */
static void sk_capop_003eafc8(uint64_t arg1, int64_t arg2)
{
    int v1;
    uint64_t v2;
    int64_t extraout_x16 = /* extraout_x16 */ 0;
    int64_t unaff_x20 = /* unaff_x20 */ 0;

    v1 = *(int *)(arg2 + 0x24);
    sk_x_0040654c(arg2, *(uint64_t *)(arg2 + 0x18), *(uint64_t *)(arg2 + 0x10));
    sk_x_00377824();
    v2 = sk_x_00350404();
    /* tail dispatch: indirect jump, jumptable at 0x003eb024 not recovered by Ghidra */
    ((void (*)(uint64_t, uint64_t, uint64_t))(*(uint64_t *)(extraout_x16 + 0x10)))(arg1, unaff_x20 + v1, v2);
    return;
}

/* FUN_003ebd9c @ 0x003ebd9c   (est. sk_capop_003ebd9c)
 * Ghidra: void FUN_003ebd9c(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,undefined8 param_5)
 * This is a capability-operation entry that seeds a per-invocation op frame on the
 * current op context: it stores the fourth argument at context offset 0x10, allocates
 * a fresh op frame of the given size, links it back to the running context, and
 * installs the shared reply/message vtable before dispatching the operation into the
 * in-slice frame driver.
 * Confidence: low
 * Notes: DAT_005a00ec is an op-frame size, DAT_004060bc is the frame vtable address
 *   (taken by address); the inner worker is in-slice (sk_capop_003eb68c). */
static void sk_capop_003ebd9c(uint64_t arg1, uint64_t arg2, uint64_t arg3, uint64_t arg4, uint64_t arg5)
{
    uint8_t *ctx = /* unaff_x22: current op context */ 0;
    int64_t *frame;
    
    *(uint64_t *)(ctx + 0x10) = arg4;
    frame = (int64_t *)sk_x_0040bb18(sk_g_005a00ec);
    *(int64_t **)(ctx + 0x18) = frame;
    *frame = (int64_t)ctx;
    frame[1] = (int64_t)&sk_g_004060bc;
    sk_capop_003eb68c(frame, arg1, arg2, arg3, arg5);
    return;
}

/* FUN_003ec148 @ 0x003ec148   (est. sk_capop_003ec148)
 * Ghidra: void FUN_003ec148(void)
 * This capability operation allocates a fresh op frame from the in-slice allocator,
 * then feeds the first slot of that frame to an out-of-slice consumer to drive the
 * operation to completion.
 * Confidence: low
 * Notes: the allocator is in-slice (sk_capop_003ec0c4); the consumer is out-of-slice
 *   (sk_x_0036b270). */
static void sk_capop_003ec148(void)
{
    uint64_t *frame;

    frame = (uint64_t *)sk_capop_003ec0c4();
    sk_x_0036b270(*frame);
    return;
}

/* FUN_003ec780 @ 0x003ec780   (est. sk_capop_003ec780)
 * Ghidra: void FUN_003ec780(void)
 * This capability operation runs two out-of-slice prep helpers, then reaches a
 * non-returning software-breakpoint path: it takes the address of the breakpoint
 * trap and calls through it. The compiler flags the path as never returning.
 * Confidence: low
 * Notes: SoftwareBreakpoint(1, 0x3ec7a8) is the trap site; Ghidra emits "Does not
 *   return" for this path. */
static void sk_capop_003ec780(void)
{
    uint64_t (*brk)(void);

    sk_x_00407030();
    sk_x_00406490();
    /* WARNING: Does not return */
    /* WARNING: Does not return */
    SoftwareBreakpoint(1, 0x3ec7a8);
}

/* FUN_003ecb1c @ 0x003ecb1c   (est. sk_capop_003ecb1c)
 * Ghidra: void FUN_003ecb1c(void)
 * This capability operation is a single out-of-slice call wrapper that delegates the
 * whole operation to the kernel helper and returns.
 * Confidence: low
 * Notes: the sole callee is out-of-slice (sk_x_001c9a1c). */
static void sk_capop_003ecb1c(void)
{
    sk_x_001c9a1c();
    return;
}

/* FUN_003ecddc @ 0x003ecddc   (est. sk_capop_003ecddc)
 * Ghidra: void FUN_003ecddc(void)
 * This capability operation runs a two-branch dispatch: it fetches the current
 * operation result, stores it into the context (offset 0x28), and branches on
 * whether that result is null. Each branch allocates a fresh op frame (of the size
 * given by the frame table), links it into the context at a different slot, resolves
 * the message slot, then tail-dispatches through a function pointer derived from the
 * frame table's indexed entry.
 * Confidence: low
 * Notes: UNRECOVERED_JUMPTABLE at 0x003ecf1c — "Too many branches" / "Treating
 *   indirect jump as call"; local_30 is a code pointer computed from the frame table;
 *   two extraout_x17 call-result locals feed the frame backlinks. */
static void sk_capop_003ecddc(void)
{
    int v1;
    int64_t v2;
    uint64_t *slot;
    uint64_t r4;
    uint64_t extraout_x17 = /* extraout_x17 */ 0;
    uint64_t extraout_x17_00 = /* extraout_x17_00 */ 0;
    int *table;
    uint8_t *ctx = /* unaff_x22: current op context */ 0;
    uint64_t (*frame)(uint64_t, int64_t);

    sk_x_00406fd4();
    v2 = sk_x_0040880c();
    *(int64_t *)(ctx + 0x28) = v2;
    table = *(int **)(ctx + 0x18);
    if (v2 == 0) {
        v1 = *table;
        sk_x_0040bb18(table[1]);
        slot = (uint64_t *)sk_x_00406fe0();
        *(uint64_t **)(ctx + 0x38) = slot;
        *slot = extraout_x17_00;
        r4 = sk_x_004071c0();
        v2 = 0;
    }
    else {
        sk_x_0036b270();
        v1 = *table;
        sk_x_0040bb18(table[1]);
        slot = (uint64_t *)sk_x_00406fe0();
        *(uint64_t **)(ctx + 0x30) = slot;
        *slot = extraout_x17;
        r4 = sk_x_004071c0();
    }
    frame = (uint64_t (*)(uint64_t, int64_t))((int64_t)table + (int64_t)v1);
    /* tail dispatch: indirect jump, jumptable at 0x003ecf1c not recovered by Ghidra */
    (*frame)(r4, v2);
    return;
}

/* FUN_003ed930 @ 0x003ed930   (est. sk_capop_003ed930)
 * Ghidra: void FUN_003ed930(void)
 * This capability operation invokes a prep helper, resolves the current message slot
 * from the context (offset 0x38) and its payload (offset 0x40), releases the op
 * frame, recomposes the message pair, then tail-dispatches through an unrecovered
 * jumptable.
 * Confidence: low
 * Notes: UNRECOVERED_JUMPTABLE at 0x003ed980 — "Too many branches" / "Treating
 *   indirect jump as call". */
static void sk_capop_003ed930(void)
{
    uint64_t r1;
    uint64_t (*tail)(void);
    uint8_t *ctx = /* unaff_x22: current op context */ 0;

    sk_x_00407000();
    r1 = *(uint64_t *)(ctx + 0x38);
    sk_x_0040aa98(*(uint64_t *)(ctx + 0x40));
    sk_x_0040bd24(r1);
    sk_x_0040678c();
    /* tail dispatch: indirect jump, jumptable at 0x003ed980 not recovered by Ghidra */
    (*tail)();
    return;
}

/* FUN_003ee688 @ 0x003ee688   (est. sk_capop_003ee688)
 * Ghidra: void FUN_003ee688(undefined8 param_1,undefined8 param_2,code *UNRECOVERED_JUMPTABLE)
 * This capability operation runs the setup helpers, stores the running context value
 * into the context (offset 0x110), allocates a fresh op frame of the size given by
 * the frame table, links it into the context (offset 0x148), then tail-dispatches
 * through the passed-in unrecovered jump target.
 * Confidence: low
 * Notes: UNRECOVERED_JUMPTABLE is passed in as a parameter and tail-called at
 *   0x003ee71c — "Too many branches" / "Treating indirect jump as call";
 *   extraout_x17 feeds the frame backlink. */
static void sk_capop_003ee688(uint64_t arg1, uint64_t arg2, uint64_t (*tail)(void))
{
    uint64_t *slot;
    uint64_t extraout_x17 = /* extraout_x17 */ 0;
    int64_t unaff_x19 = /* unaff_x19 */ 0;
    uint64_t unaff_x20 = /* unaff_x20 */ 0;
    uint8_t *ctx = /* unaff_x22: current op context */ 0;

    sk_x_00406fd4();
    sk_x_00408560();
    *(uint64_t *)(ctx + 0x110) = unaff_x20;
    sk_x_00406394();
    sk_x_0040bb18(*(uint32_t *)(unaff_x19 + 4));
    slot = (uint64_t *)sk_x_00406fe0();
    *(uint64_t **)(ctx + 0x148) = slot;
    *slot = extraout_x17;
    sk_x_00407c04();
    /* tail dispatch: indirect jump, jumptable at 0x003ee71c not recovered by Ghidra */
    (*tail)();
    return;
}

/* FUN_003e6cbc @ 0x003e6cbc   (est. sk_capop_003e6cbc)
 * Ghidra: void FUN_003e6cbc(void)
 * Capability-invocation entry that seeds the per-op frame by running the
 * op-frame allocator/service bootstrap (sk_x_00406574), then drives the
 * in-slice op handler sk_capop_003e6cf0 to completion before tearing the
 * frame back down (sk_x_0036b270). No arguments and no return; side effects
 * are confined to the current op context.
 * Confidence: low
 * Notes: thin 3-call stub; all three callees are external shims/subsystems. */
static void sk_capop_003e6cbc(void)
{
    sk_x_00406574();
    sk_capop_003e6cf0();
    sk_x_0036b270();
    return;
}

/* FUN_003e7b14 @ 0x003e7b14   (est. sk_capop_003e7b14)
 * Ghidra: void FUN_003e7b14(void)
 * Capability-invocation driver that builds an op frame seeded from the
 * running context: it reads reply/message slots off ctx, calls the out-of-slice
 * capability argument munger sk_x_00407ce4 and the in-slice capability
 * preparer, dispatches through recovered function pointers, then allocates a
 * per-op frame and hooks its vtable return slot before tail-jumping into the
 * unrecovered dispatch table. Every store to ctx+0xNN is preserved in order.
 * Confidence: low
 * Notes: UNRECOVERED_JUMPTABLE at 0x003e7c30 (too many branches) rendered as
 *   comment; LAB_003e7c34 is a vtable return label stored in the op frame;
 *   several callees (00407ce4, 00350518) return 16-byte pairs split into .lo/.hi. */
static void sk_capop_003e7b14(void)
{
    uint64_t value;
    uint64_t base;
    uint64_t *puVar3;
    uint64_t extraout_x17 = 0; /* extraout_x17 */
    uint64_t ctx_d8;
    uint64_t ctx_90;
    uint64_t ctx_28;
    uint8_t *ctx = /* unaff_x22: current op context */ 0;
    cl4_result_t auVar7;
    void (*extraout_x9)(uint64_t, uint64_t, uint64_t) = 0; /* extraout_x9 */
    void (*extraout_x8)(uint64_t, uint64_t, uint64_t) = 0; /* extraout_x8 */
    void (*extraout_x9_00)(uint64_t, uint64_t) = 0; /* extraout_x9_00 */

    sk_x_004079cc();
    value = sk_x_004070d8();
    ctx_d8 = *(uint64_t *)(ctx + 0xd8);
    ctx_90 = *(uint64_t *)(ctx + 0x90);
    base = *(uint64_t *)(ctx + 0x30);
    ctx_28 = *(uint64_t *)(ctx + 0x28);
    auVar7 = sk_x_00407ce4(value, *(uint64_t *)(ctx + 0x40));
    extraout_x9(auVar7.lo, auVar7.hi, ctx_28);
    auVar7 = sk_x_00350518(*(uint64_t *)(base + 0x10));
    extraout_x8(auVar7.lo, auVar7.hi, ctx_28);
    sk_x_004070e4(ctx_90);
    extraout_x9_00(ctx_28, ctx_90);
    sk_x_004068bc();
    sk_x_00377bec(ctx_90, ctx_28, ctx_d8);
    sk_x_003fcc1c();
    base = sk_x_004062c8();
    sk_x_0040bb18(*(uint32_t *)(base + 4));
    puVar3 = (uint64_t *)sk_x_00406fe0();
    *(uint64_t **)(ctx + 0x168) = puVar3;
    *puVar3 = extraout_x17;
    puVar3[1] = (uint64_t)0x003e7c34; /* LAB_003e7c34 */
    sk_x_00407814(*(uint64_t *)(ctx + 0xb0), *(uint64_t *)(ctx + 0xd8));
    sk_x_004078f4();
    /* tail dispatch: indirect jump, jumptable at 0x003e7c30 not recovered by Ghidra */
    return;
}

/* FUN_003e9db0 @ 0x003e9db0   (est. sk_capop_003e9db0)
 * Ghidra: void FUN_003e9db0(void)
 * Capability-invocation entry that seeds the per-op frame via the op-frame
 * allocator/service bootstrap (sk_x_00406574), drives the in-slice op handler
 * sk_capop_003e9de0, then tears the frame down (sk_x_0036b270). Pure
 * sequencing of the current op context; no arguments, no return.
 * Confidence: low
 * Notes: thin 3-call stub; sibling structure to sk_capop_003e6cbc. */
static void sk_capop_003e9db0(void)
{
    sk_x_00406574();
    sk_capop_003e9de0();
    sk_x_0036b270();
    return;
}

/* FUN_003ea5a8 @ 0x003ea5a8   (est. sk_capop_003ea5a8)
 * Ghidra: void FUN_003ea5a8(undefined8 param_1,undefined8 param_2,undefined8 param_3,long param_4)
 * Capability-invocation body that populates a per-op frame on the running
 * context from the invocation arguments: it copies the capability identifier
 * and reply slot out of the argument frame (param_4+0x10/0x20), resolves each
 * capability field (sk_x_004078e8 on the fetched base registers), and selects
 * an access path (grants vs. trap) based on the unaff_x21 register before
 * storing the resolved capability and passing param_3 through to the reply
 * slot at ctx+0x98. Every ctx+0xNN store is preserved in order.
 * Confidence: low
 * Notes: unaff_x21/unaff_x22 are register artifacts; extraout_x8* are address
 *   bases used with +0x40 derefs; extraout_x8_02 is a tail-called function
 *   pointer in the else branch. */
static void sk_capop_003ea5a8(uint64_t param_1, uint64_t param_2, uint64_t param_3, uint64_t param_4)
{
    uint64_t value;
    uint64_t extraout_x8 = 0; /* extraout_x8 */
    uint64_t extraout_x8_00 = 0; /* extraout_x8_00 */
    uint64_t extraout_x8_01 = 0; /* extraout_x8_01 */
    void (*extraout_x8_02)(void) = 0; /* extraout_x8_02 */
    uint64_t extraout_x8_03 = 0; /* extraout_x8_03 */
    uint64_t extraout_x8_04 = 0; /* extraout_x8_04 */
    uint64_t extraout_x16 = 0; /* extraout_x16 */
    uint64_t extraout_x16_00 = 0; /* extraout_x16_00 */
    uint64_t extraout_x16_01 = 0; /* extraout_x16_01 */
    uint64_t unaff_x21 = 0; /* unaff_x21 */
    uint8_t *ctx = /* unaff_x22: current op context */ 0;

    sk_x_00407c8c();
    sk_x_0040700c();
    sk_x_00350b54();
    sk_x_0040752c();
    *(uint64_t *)(ctx + 0x38) = *(uint64_t *)(param_4 + 0x20);
    *(uint64_t *)(ctx + 0x40) = *(uint64_t *)(param_4 + 0x10);
    value = sk_x_0040684c();
    *(uint64_t *)(ctx + 0x48) = value;
    sk_x_00352018();
    *(uint64_t *)(ctx + 0x50) = extraout_x16;
    value = sk_x_004078e8(*(uint64_t *)(extraout_x8 + 0x40));
    *(uint64_t *)(ctx + 0x58) = value;
    value = sk_x_00406dd0();
    *(uint64_t *)(ctx + 0x60) = value;
    sk_x_00350798();
    value = sk_x_00310d68();
    *(uint64_t *)(ctx + 0x68) = value;
    sk_x_00352018();
    *(uint64_t *)(ctx + 0x70) = extraout_x16_00;
    value = sk_x_004078e8(*(uint64_t *)(extraout_x8_00 + 0x40));
    *(uint64_t *)(ctx + 0x78) = value;
    sk_x_0040683c();
    *(uint64_t *)(ctx + 0x80) = extraout_x16_01;
    value = sk_x_004078e8(*(uint64_t *)(extraout_x8_01 + 0x40));
    *(uint64_t *)(ctx + 0x88) = value;
    if (unaff_x21 == 0) {
        sk_x_00407248();
        value = extraout_x8_04;
    } else {
        sk_x_00406590();
        extraout_x8_02();
        sk_x_0008e1ec();
        value = extraout_x8_03;
    }
    *(uint64_t *)(ctx + 0x90) = value;
    *(uint64_t *)(ctx + 0x98) = param_3;
    sk_x_00353080();
    sk_x_00407c78();
    sk_x_00408db8();
    return;
}

/* FUN_003eb0a4 @ 0x003eb0a4   (est. sk_capop_003eb0a4)
 * Ghidra: void FUN_003eb0a4(void)
 * Capability-invocation entry that runs a sequence of capability/scheduling
 * helpers, invokes a recovered per-op function pointer to obtain a status
 * record (reading fields +0x24 and +0x28 off it), then dispatches through the
 * op-frame vtable (extraout_x16+0x20) passing the tag offset and finally
 * releases the op frame. Preserves every branch and call in order.
 * Confidence: low
 * Notes: in_x5 is the recovered code pointer; extraout_x16 is the vtable base;
 *   DAT_ none; no unrecovered jumptable in this body. */
static void sk_capop_003eb0a4(void)
{
    int off24;
    uint64_t rec;
    uint64_t (*in_x5)(void) = 0; /* in_x5 */
    uint8_t *extraout_x8 = 0; /* extraout_x8 */
    uint64_t extraout_x16 = 0; /* extraout_x16 */
    uint64_t unaff_x24 = 0; /* unaff_x24 */
    uint64_t unaff_x30 = 0; /* unaff_x30 */

    sk_x_00084220();
    sk_x_0040679c();
    *extraout_x8 = 0;
    sk_x_00407450();
    rec = in_x5();
    off24 = *(int *)(rec + 0x24);
    sk_x_0040654c();
    sk_x_00350968();
    sk_x_00377824();
    sk_x_00349530();
    ((void (*)(uint64_t))(*(uint64_t *)(extraout_x16 + 0x20)))((uint64_t)(unaff_x24 + off24));
    sk_x_00407ea0((int64_t)*(int *)(rec + 0x28));
    sk_x_00084234(unaff_x30);
    return;
}

/* FUN_003ebe6c @ 0x003ebe6c   (est. sk_capop_003ebe6c)
 * Ghidra: void FUN_003ebe6c(void)
 * Capability-invocation entry that chains a set of scheduling/capability
 * helpers, calls through the global op-dispatch function pointer
 * sk_g_00658c80, then invokes two further recovered function pointers and
 * releases the op frame. A vtable tail call at unaff_x21+0x24 feeds a
 * tag-check before teardown.
 * Confidence: low
 * Notes: DAT_00658c80 is a global code pointer called as (*DAT)(); extraout_x9
 *   and unaff_x19 are recovered function pointers; LAB none. */
static void sk_capop_003ebe6c(void)
{
    void (*extraout_x9)(void) = 0; /* extraout_x9 */
    void (*unaff_x19)(void) = 0; /* unaff_x19 */
    uint64_t unaff_x21 = 0; /* unaff_x21 */
    uint64_t unaff_x30 = 0; /* unaff_x30 */

    sk_x_00084220();
    sk_x_0008409c();
    sk_x_0040654c();
    sk_x_003513b4();
    sk_x_00377824();
    sk_x_00351f10();
    sk_x_0007c1a4();
    ((void (*)(void))sk_g_00658c80)();
    sk_x_0034b05c();
    sk_x_00407100();
    sk_x_00350518();
    extraout_x9();
    sk_x_004082a8((int64_t)*(int *)(unaff_x21 + 0x24));
    sk_x_00407700();
    unaff_x19();
    sk_x_00084234(unaff_x30);
    return;
}

/* FUN_003ec178 @ 0x003ec178   (est. sk_capop_003ec178)
 * Ghidra: void FUN_003ec178(void)
 * Capability-invocation entry that seeds the per-op frame on the running
 * context: stores the context pointer at ctx+0x10 and registers the in-slice
 * op handler sk_capop_003ec20c as a callback at ctx+0x18, wires the handler
 * and a register-update result into the dispatch machinery, then releases the
 * frame's callback slot. Preserves every ctx store in order.
 * Confidence: low
 * Notes: FUN_003ec20c/FUN_003ecc18 are in-slice; FUN_0040ab60/0040aac8/00409354/
 *   0040ada4 are out-of-slice. uVar1/uVar2 hold the handler register results. */
static void sk_capop_003ec178(void)
{
    uint8_t reg_lo;
    uint64_t reg_hi;
    uint8_t *ctx = /* unaff_x22: current op context */ 0;

    sk_x_00407000();
    *(uint64_t *)(ctx + 0x10) = (uint64_t)ctx;
    *(uint64_t *)(ctx + 0x18) = (uint64_t)sk_capop_003ec20c;
    reg_hi = sk_x_0040ab60(ctx + 0x18, ctx + 0x10, 0);
    reg_lo = sk_capop_003ecc18();
    sk_x_0040aac8((uint64_t)reg_lo, reg_hi);
    sk_x_00409354();
    sk_x_0040ada4(ctx + 0x10);
    return;
}

/* FUN_003ec7bc @ 0x003ec7bc   (est. sk_capop_003ec7bc)
 * Ghidra: void FUN_003ec7bc(void)
 * Capability-invocation entry that drives three out-of-slice helpers in
 * sequence (message-slot setup, capability resolution, and frame completion).
 * No arguments, no return; purely sequential side effects on the current op
 * context.
 * Confidence: low
 * Notes: thin 3-call stub; all callees external. */
static void sk_capop_003ec7bc(void)
{
    sk_x_00406fd4();
    sk_x_00407030();
    sk_x_00406490();
    return;
}

/* FUN_003ecb20 @ 0x003ecb20   (est. sk_capop_003ecb20)
 * Ghidra: void FUN_003ecb20(void)
 * Capability-invocation entry that delegates entirely to the out-of-slice
 * helper sk_x_001c9a1c. Single-call passthrough; no local state, no return.
 * Confidence: low
 * Notes: minimal one-call body. */
static void sk_capop_003ecb20(void)
{
    sk_x_001c9a1c();
    return;
}

/* FUN_003ed0a8 @ 0x003ed0a8   (est. sk_capop_003ed0a8)
 * Ghidra: void FUN_003ed0a8(void)
 * Capability-invocation entry that captures the first word of the unaff_x20
 * capability frame, allocates a 72-byte stack scratch area, passes it with the
 * captured word into the in-slice op handler sk_capop_003ec8a0, then runs the
 * out-of-slice completion helper. Preserves the stack-buffer handoff in order.
 * Confidence: low
 * Notes: unaff_x20 is a register artifact holding the frame base; the 72-byte
 *   auStack_68 buffer is the scratch area passed by pointer. */
static void sk_capop_003ed0a8(void)
{
    uint64_t word0;
    uint64_t *unaff_x20 = 0; /* unaff_x20 */
    uint8_t auStack_68[72];

    word0 = *unaff_x20;
    sk_x_001a84f4(auStack_68);
    sk_capop_003ec8a0(auStack_68, word0);
    sk_x_001a8564();
    return;
}

/* FUN_003edad4 @ 0x003edad4   (est. sk_capop_003edad4)
 * Ghidra: void FUN_003edad4(void)
 * Capability-invocation driver that builds two op frames from the running
 * context: it allocates a 0x40-byte frame (ctx+0x78) and a 0x20-byte frame
 * (ctx+0x80) via the op-frame allocator sk_x_0040bb18, seeds each frame's
 * fields from ctx slots, runs the framing registration helper, allocates the
 * reply frame and hooks its vtable return slot, then tail-jumps into the
 * unrecovered dispatch table with the collected frame pointers and message
 * slots. Every allocation, store, and load is preserved in order.
 * Confidence: low
 * Notes: UNRECOVERED_JUMPTABLE at 0x003edbf8 (too many branches) rendered as
 *   comment with its 11 dispatch arguments; LAB_003edbfc is the vtable return
 *   label; extraout_x17 is the stored reply tag. */
static void sk_capop_003edad4(void)
{
    uint64_t frame_a;
    uint64_t frame_b;
    uint64_t *puVar3;
    uint64_t extraout_x17 = 0; /* extraout_x17 */
    uint64_t ctx_58;
    uint64_t ctx_18;
    uint64_t ctx_28;
    uint64_t ctx_20;
    uint64_t ctx_30;
    uint64_t ctx_48;
    uint64_t ctx_50;
    uint8_t *ctx = /* unaff_x22: current op context */ 0;

    sk_x_004070d8();
    ctx_58 = *(uint64_t *)(ctx + 0x58);
    frame_a = sk_x_0040bb18(0x40);
    *(uint64_t *)(ctx + 0x78) = frame_a;
    ctx_50 = *(uint64_t *)(ctx + 0x50);
    ctx_48 = *(uint64_t *)(ctx + 0x48);
    ctx_20 = *(uint64_t *)(ctx + 0x20);
    ctx_18 = *(uint64_t *)(ctx + 0x18);
    frame_b = sk_x_0040bb18(0x20);
    ctx_30 = *(uint64_t *)(ctx + 0x30);
    ctx_28 = *(uint64_t *)(ctx + 0x28);
    *(uint64_t *)(frame_a + 0x18) = ctx_50;
    *(uint64_t *)(frame_a + 0x10) = ctx_48;
    *(uint64_t *)(frame_a + 0x20) = ctx_58;
    *(uint64_t *)(frame_a + 0x30) = ctx_20;
    *(uint64_t *)(frame_a + 0x28) = ctx_18;
    *(uint64_t *)(ctx + 0x80) = frame_b;
    *(uint64_t *)(frame_b + 0x18) = ctx_30;
    *(uint64_t *)(frame_b + 0x10) = ctx_28;
    sk_x_00407db0(0x5a0158);
    sk_x_0040bb18();
    puVar3 = (uint64_t *)sk_x_00406fe0();
    *(uint64_t **)(ctx + 0x88) = puVar3;
    *puVar3 = extraout_x17;
    puVar3[1] = (uint64_t)0x003edbfc; /* LAB_003edbfc */
    /* tail dispatch: indirect jump, jumptable at 0x003edbf8 not recovered by Ghidra;
       dispatch args would be (ctx+0x10, ctx+0x38, ctx+0x40, 0x5a0150, frame_a,
       0x3fd354, frame_b, ctx+0x48, ctx+0x50, ctx+0x58, ctx+0x70) */
    return;
}

/* FUN_003ee818 @ 0x003ee818   (est. sk_capop_003ee818)
 * Ghidra: void FUN_003ee818(void)
 * Capability-invocation entry that seeds the frame (sk_x_00407000), runs a
 * pre-release helper, releases a per-op frame passing a tagged stack-slot
 * address and a capability id off unaff_x20+0x150, then registers the in-slice
 * handler sk_capop_003ee8e4 as a callback with two capability fields. The
 * tagged pointer combines a 48-bit stack-slot address with tag 0xc31a.
 * Confidence: low
 * Notes: first argument to sk_x_0040bd24 is `&stack0xffffffffffffffe8` masked
 *   to 48 bits then ORed with tag 0xc31a000000000000; extraout_x16 is an
 *   address base for the +0x140 deref. */
static void sk_capop_003ee818(void)
{
    uint64_t extraout_x16 = 0; /* extraout_x16 */
    uint64_t unaff_x20 = 0; /* unaff_x20 */
    uint64_t stack_slot = 0; /* &stack0xffffffffffffffe8: caller stack slot address */

    sk_x_00407000();
    sk_x_00407520();
    sk_x_0040bd24((stack_slot & 0xffffffffffffULL) | 0xc31a000000000000ULL,
                  *(uint64_t *)(unaff_x20 + 0x150));
    sk_x_00407444();
    sk_x_00408db8((uint64_t)sk_capop_003ee8e4, *(uint64_t *)(unaff_x20 + 0x138),
                  *(uint64_t *)(extraout_x16 + 0x140));
    return;
}

/* FUN_003e6cf0 @ 0x003e6cf0   (est. sk_capop_003e6cf0)
 * Ghidra: void FUN_003e6cf0(void)
 * Thin capability-op entry that immediately forwards to the shared op-frame
 * driver at 003e6d08, passing no arguments. This is a leaf wrapper in the
 * per-invocation op-dispatch chain: it seeds nothing itself and relies on the
 * callee to build and run the op frame seeded with the current op context.
 * No stores, no branches, no local state beyond the call.
 * Confidence: low
 * Notes: single tail-call body; no DAT_ refs, no labels, no jumptable. */
static void sk_capop_003e6cf0(void)
{
    sk_capop_003e6d08();
    return;
}

/* FUN_003e7d20 @ 0x003e7d20   (est. sk_capop_003e7d20)
 * Ghidra: void FUN_003e7d20(void)
 * Large capability-op frame driver. Reads the running op context (unaff_x22),
 * picks up the result/link slot pointers from offsets 0xb0/0xa8/0xf8/0x100/0xd8,
 * and branches on the zero flag of a prior probe call. The taken path builds a
 * fresh op frame via the op-frame allocator (0x40bb18), stores an object
 * pointer into ctx+0x148, fills the first vtable slot, and releases the frame;
 * the alternate path invokes a vtable method (ctx+0xc0 + 0x20) and then
 * releases every captured op-frame/reply reference before a final message
 * reply. Both paths end in an unrecovered tail dispatch.
 * Confidence: low
 * Notes: UNRECOVERED_JUMPTABLE at 0x003e7fe0 and 0x003e7f50; in_ZR branches;
 *   extraout_x8/x9/x10/x17; 16-byte auVar12 pair from 0x839d8/0x406894/0x40678c. */
static void sk_capop_003e7d20(void)
{
    uint64_t msg = 0;
    uint64_t slot_a = 0;
    uint64_t slot_b = 0;
    uint64_t slot_c = 0;
    uint64_t idx = 0;
    uint64_t arg = 0;
    uint64_t frame = 0;
    uint64_t *obj;
    int64_t len;
    int64_t base;
    uint64_t vtbl_fn;
    uint64_t dispatch = 0;   /* tail dispatch: indirect jump, jumptable at 0x003e7fe0 not recovered by Ghidra */
    uint64_t extraout_x8 = 0;   /* extraout_x8 */
    uint64_t extraout_x8_00 = 0;   /* extraout_x8_00 */
    uint64_t extraout_x8_01 = 0;   /* extraout_x8_01 */
    uint64_t extraout_x8_02 = 0;   /* extraout_x8_02 */
    uint64_t extraout_x9 = 0;   /* extraout_x9 */
    uint64_t extraout_x9_00 = 0;   /* extraout_x9_00 */
    uint64_t extraout_x9_01 = 0;   /* extraout_x9_01 */
    uint64_t extraout_x10 = 0;   /* extraout_x10 */
    uint64_t extraout_x10_00 = 0;   /* extraout_x10_00 */
    uint64_t extraout_x17 = 0;   /* extraout_x17 */
    uint64_t extraout_x17_00 = 0;   /* extraout_x17_00 */
    uint64_t ctx = 0;   /* unaff_x22: current op context */
    cl4_result_t pair;

    msg = sk_x_0040785c();
    sk_x_00407adc();
    frame = *(uint64_t *)(ctx + 0xb0);
    sk_x_00406be4();
    if (0 /* in_ZR */) {
        dispatch = *(uint64_t *)(ctx + 0x138);   /* tail dispatch: indirect jump, jumptable at 0x003e7fe0 not recovered by Ghidra */
        len = *(int64_t *)(ctx + 0xa8);
        ((void (*)(uint64_t, uint64_t))(*(uint64_t *)(*(uint64_t *)(ctx + 0xf8) + 8)))(
            *(uint64_t *)(ctx + 0x100), *(uint64_t *)(ctx + 0xd8));
        sk_x_003507e0(*(uint64_t *)(len + 8));
        ((void (*)(void))extraout_x8)();
        sk_x_00408410();
        /* tail dispatch: indirect jump, jumptable at 0x003e7fe0 not recovered by Ghidra */
        dispatch = *(uint64_t *)(ctx + 0xd8);   /* tail dispatch: indirect jump, jumptable at 0x003e7fe0 not recovered by Ghidra */
        sk_x_00350744(*(int64_t *)(ctx + 0x20) + (int64_t)*(int *)(ctx + 0x17c));
        pair = sk_x_000839d8();
        sk_x_00406fb0(*(uint64_t *)(ctx + 0x110), pair.lo, pair.hi,
                      *(uint64_t *)(ctx + 0xe0));
        ((void (*)(void))extraout_x8_00)();
        sk_x_00406420();
        if (0 /* in_ZR */) {
            len = *(int64_t *)(ctx + 0x58);
            sk_x_00353930(*(uint64_t *)(ctx + 0xe8), *(uint64_t *)(ctx + 0xf0),
                          *(uint64_t *)(ctx + 0xe0));
            *(uint64_t *)(ctx + 0x138) = extraout_x9;
            *(uint64_t *)(ctx + 0x140) = extraout_x10;
            ((void (*)(void))extraout_x9)();
            sk_x_0040652c();
            sk_x_00406608();
            sk_x_004068f4();
            sk_x_00406268();
            sk_x_0040bb18((uint32_t)*(int *)(len + 4));
            obj = (uint64_t *)sk_x_00406fe0();
            *(uint64_t *)(ctx + 0x148) = (uint64_t)obj;
            *obj = extraout_x17;
            sk_x_00406b54();
        } else {
            msg = *(uint64_t *)(ctx + 0xd8);
            pair = sk_x_00406894(*(uint64_t *)(ctx + 0xf8), *(uint64_t *)(ctx + 0x108),
                                 *(uint64_t *)(ctx + 0xf0));
            *(uint64_t *)(ctx + 0x118) = extraout_x9_01;
            *(uint64_t *)(ctx + 0x120) = extraout_x10_00;
            ((void (*)(uint64_t, uint64_t, uint64_t))extraout_x9_01)(pair.lo, pair.hi, msg);
            sk_x_004067f8();
            sk_x_003fcc1c();
            len = sk_x_004062c8();
            sk_x_0040bb18((uint32_t)*(int *)(len + 4));
            obj = (uint64_t *)sk_x_00406fe0();
            *(uint64_t *)(ctx + 0x128) = (uint64_t)obj;
            *obj = extraout_x17_00;
            sk_x_00406ac4();
        }
        sk_x_00408404();
        sk_x_00407504();
        /* tail dispatch: indirect jump, jumptable at 0x003e7fe0 not recovered by Ghidra */
        return;
    }
    dispatch = *(uint64_t *)(ctx + 0x138);   /* tail dispatch: indirect jump, jumptable at 0x003e7fe0 not recovered by Ghidra */
    arg = *(uint64_t *)(ctx + 0x140);
    len = (int64_t)*(int *)(ctx + 0x17c);
    slot_a = *(uint64_t *)(ctx + 0xf8);
    slot_b = *(uint64_t *)(ctx + 0xd8);
    slot_c = *(uint64_t *)(ctx + 0xe0);
    idx = *(uint64_t *)(ctx + 200);
    base = *(int64_t *)(ctx + 0x20);
    obj = (uint64_t *)(*(int64_t *)(ctx + 0xc0) + 0x20);
    vtbl_fn = *obj;
    sk_x_00350968(idx);
    ((void (*)(void))vtbl_fn)();
    /* tail dispatch: indirect jump, jumptable at 0x003e7f50 not recovered by Ghidra (would call with arg, base + len, slot_c) */
    sk_x_004083f0();
    ((void (*)(void))extraout_x8_01)();
    sk_x_00350750(base + len);
    sk_x_0040764c();
    ((void (*)(void))vtbl_fn)();
    sk_x_004069ec();
    arg = *(uint64_t *)(ctx + 0x38);
    sk_x_00406cf0();
    sk_x_0040bd24(frame);
    sk_x_0040bd24(slot_a);
    sk_x_0040bd24(vtbl_fn);
    sk_x_0040bd24(slot_b);
    sk_x_0040bd24(idx);
    sk_x_0040bd24(len);
    sk_x_0040bd24(obj);
    sk_x_0040bd24(base);
    sk_x_0040bd24(extraout_x9_00);
    sk_x_0040bd24(extraout_x8_02);
    sk_x_0040bd24(arg);
    pair = sk_x_0040678c();
    sk_x_00407504(pair.lo, pair.hi, msg);
    /* tail dispatch: indirect jump, jumptable at 0x003e7f50 not recovered by Ghidra */
    return;
}

/* FUN_003e9de0 @ 0x003e9de0   (est. sk_capop_003e9de0)
 * Ghidra: void FUN_003e9de0(void)
 * Thin capability-op entry that forwards unconditionally to the shared op-frame
 * driver at 003e9df8, passing no arguments. No stores, no branches; the callee
 * builds and runs the per-invocation op frame seeded with the current op
 * context.
 * Confidence: low
 * Notes: single tail-call body; no DAT_ refs, no labels, no jumptable. */
static void sk_capop_003e9de0(void)
{
    sk_capop_003e9df8();
    return;
}

/* FUN_003ea6ec @ 0x003ea6ec   (est. sk_capop_003ea6ec)
 * Ghidra: void FUN_003ea6ec(void)
 * Capability-op driver. Reads a capability vector index (offset 0x28 + 0x30)
 * and stores it into ctx+200, then tests bit 0 of the indexed byte in the
 * vector at ctx+0x30. If set, it replies after releasing an op frame and
 * captured refs; otherwise it seeds the frame builder chain: allocates an op
 * frame from 0x40bb18, records the object pointer at ctx+0xb0, fills its first
 * vtable slot, and stores two derived values at ctx+0xa0/0xa8 before dispatching.
 * Confidence: low
 * Notes: UNRECOVERED_JUMPTABLE at 0x003ea76c and 0x003ea804; extraout_x17;
 *   16-byte auVar6 pair from 0x40678c; ctx+200 decimal. */
static void sk_capop_003ea6ec(void)
{
    int64_t rec;
    int32_t idx;
    uint64_t msg = 0;
    uint64_t ref = 0;
    uint64_t *obj;
    uint64_t extraout_x17 = 0;   /* extraout_x17 */
    uint64_t ctx = 0;   /* unaff_x22: current op context */
    cl4_result_t pair;

    msg = sk_x_00407ca0();
    sk_x_0040700c();
    idx = *(int *)(*(int64_t *)(ctx + 0x28) + 0x30);
    *(int *)(ctx + 200) = idx;
    if ((*(uint8_t *)(*(int64_t *)(ctx + 0x30) + (int64_t)idx) & 1) != 0) {
        sk_x_00407960();
        ref = *(uint64_t *)(ctx + 0x58);
        sk_x_00406c5c(*(uint64_t *)(ctx + 0x10));
        sk_x_0040bd24();
        sk_x_0040bd24(ref);
        pair = sk_x_0040678c();
        sk_x_00407e58(pair.lo, pair.hi, msg);
        /* tail dispatch: indirect jump, jumptable at 0x003ea76c not recovered by Ghidra */
        return;
    }
    rec = *(int64_t *)(ctx + 0x40);
    sk_x_0040652c();
    msg = sk_x_00406608();
    *(uint64_t *)(ctx + 0xa0) = msg;
    msg = sk_x_00406e8c();
    *(uint64_t *)(ctx + 0xa8) = msg;
    sk_x_00406288();
    sk_x_0040bb18((uint32_t)*(int *)(rec + 4));
    obj = (uint64_t *)sk_x_00406fe0();
    *(uint64_t *)(ctx + 0xb0) = (uint64_t)obj;
    *obj = extraout_x17;
    sk_x_00407830();
    sk_x_004067b8();
    /* tail dispatch: indirect jump, jumptable at 0x003ea804 not recovered by Ghidra */
    return;
}

/* FUN_003eb120 @ 0x003eb120   (est. sk_capop_003eb120)
 * Ghidra: void FUN_003eb120(void)
 * Capability-op frame builder. Runs a fixed sequence of initializer helpers,
 * then records results into the current op context: the output of 0x310d68 at
 * ctx+0x40, a frame value at ctx+0x48, a slot pointer derived from
 * extraout_x8+0x40 (via 0x4078e8) at ctx+0x50, another frame value at ctx+0x58,
 * and a second slot pointer derived from extraout_x8_00+0x40 at ctx+0x60.
 * No branches; ends with two finalizer helpers.
 * Confidence: low
 * Notes: extraout_x8/x8_00/x16/x16_00 carry chained frame/slot pointers; the
 *   +0x40 offsets are read through the returned object pointers. */
static void sk_capop_003eb120(void)
{
    uint64_t val = 0;
    uint64_t extraout_x8 = 0;   /* extraout_x8 */
    uint64_t extraout_x8_00 = 0;   /* extraout_x8_00 */
    uint64_t extraout_x16 = 0;   /* extraout_x16 */
    uint64_t extraout_x16_00 = 0;   /* extraout_x16_00 */
    uint64_t ctx = 0;   /* unaff_x22: current op context */

    sk_x_00407000();
    sk_x_00406704();
    sk_x_004079a8();
    sk_x_00350798();
    val = sk_x_00310d68();
    *(uint64_t *)(ctx + 0x40) = val;
    sk_x_00352018();
    *(uint64_t *)(ctx + 0x48) = extraout_x16;
    val = sk_x_004078e8(*(uint64_t *)(extraout_x8 + 0x40));
    *(uint64_t *)(ctx + 0x50) = val;
    sk_x_0040683c();
    *(uint64_t *)(ctx + 0x58) = extraout_x16_00;
    val = sk_x_004078e8(*(uint64_t *)(extraout_x8_00 + 0x40));
    *(uint64_t *)(ctx + 0x60) = val;
    sk_x_00407594();
    sk_x_00408db8();
    return;
}

/* FUN_003ebf10 @ 0x003ebf10   (est. sk_capop_003ebf10)
 * Ghidra: undefined1 [16] FUN_003ebf10(void)
 * Returns a 16-byte status/result pair. Probes a condition via 0x409484; when
 * it succeeds it returns the "ok" pair {0xd000000000000013, 0x80000000005dbf70},
 * otherwise it logs an error through a message/assert chain (0x27724 +
 * 0xe72d4 + 0x3a25d4 + 0x408108) and returns a pair whose lo is the ASCII
 * string "UnoneJdenw" (0x4a64656e776f6e55) and hi "obi:di :o..." marker
 * (0xef203a646928626f).
 * Confidence: low
 * Notes: returns 16-byte auVar5; hi/lo assembled from distinct constant paths. */
static cl4_result_t sk_capop_003ebf10(void)
{
    int64_t ok;
    uint64_t lo = 0;
    uint64_t hi = 0;
    cl4_result_t result;

    ok = sk_x_00409484();
    if (ok == 0) {
        hi = 0x80000000005dbf70;
        lo = 0xd000000000000013;
    } else {
        uint64_t fn = (uint64_t)sk_x_00027724(0x671848);
        ((void (*)(uint64_t, uint64_t))fn)(0x677790, 0x671848);
        sk_x_000e72d4();
        sk_x_003a25d4(0x671848);
        sk_x_00408108();
        lo = 0x4a64656e776f6e55;
        hi = 0xef203a646928626f;
    }
    result.hi = hi;
    result.lo = lo;
    return result;
}

/* FUN_003ec20c @ 0x003ec20c   (est. sk_capop_003ec20c)
 * Ghidra: void FUN_003ec20c(void)
 * Capability-op entry that runs a single finalizer helper, then dispatches to
 * the vtable method stored at (vtable+8) where vtable is the object pointer at
 * ctx+0, passing that same object pointer as the sole argument. The call target
 * is the second vtable slot of the current op context's root object.
 * Confidence: low
 * Notes: unaff_x22 typed as long*; unrecovered jumptable at 0x003ec2a0. */
static void sk_capop_003ec20c(void)
{
    uint64_t ctx = 0;   /* unaff_x22: current op context */

    sk_x_00407000();
    ((void (*)(uint64_t))(*(uint64_t *)(*(uint64_t *)(ctx + 0) + 8)))(*(uint64_t *)(ctx + 0));
    /* tail dispatch: indirect jump, jumptable at 0x003ec2a0 not recovered by Ghidra */
    return;
}

/* FUN_003ec7fc @ 0x003ec7fc   (est. sk_capop_003ec7fc)
 * Ghidra: void FUN_003ec7fc(void)
 * Capability-op entry that runs two finalizer helpers, then triggers a
 * software breakpoint trap (1, 0x3ec824) and calls through the returned
 * breakpoint address. The breakpoint path does not return.
 * Confidence: low
 * Notes: SoftwareBreakpoint(1, 0x3ec824) intrinsic; "Does not return" warning. */
static void sk_capop_003ec7fc(void)
{
    uint64_t pcVar1;

    sk_x_00407030();
    sk_x_00406490();
    pcVar1 = (uint64_t)SoftwareBreakpoint(1, 0x3ec824);
    ((void (*)(void))pcVar1)();
}

/* FUN_003ecb48 @ 0x003ecb48   (est. sk_capop_003ecb48)
 * Ghidra: void FUN_003ecb48(undefined8 param_1)
 * Forwards the single argument plus a byte read from the running context
 * (unaff_x20) to the shared op-frame driver at 003ecb64. The context pointer is
 * not otherwise dereferenced here; it supplies the second argument to the
 * callee.
 * Confidence: low
 * Notes: unaff_x20 typed as undefined1* (byte pointer); single tail-call body. */
static void sk_capop_003ecb48(uint64_t param_1)
{
    uint8_t *unaff_x20 = 0;   /* unaff_x20 */

    sk_capop_003ecb64(param_1, (uint64_t)*unaff_x20);
    return;
}

/* FUN_003ed0ec @ 0x003ed0ec   (est. sk_capop_003ed0ec)
 * Ghidra: void FUN_003ed0ec(void)
 * Fatal capability-op error path. Resolves a message string via 0x35ac70,
 * passes it through 0x3593c0, then raises a non-returning panic/report through
 * 0x1afa84 with a formatted tag string, a flags word built from an extraout
 * register with the high bit set, and the provided codes (0xb, 2, 0x17, 2).
 * Control never resumes.
 * Confidence: low
 * Notes: "Subroutine does not return"; extraout_x8 folded with
 *   0x8000000000000000; two string references (s_Unavailable_in_Exclaves and
 *   s__Concurrency_Task_swift). */
static void sk_capop_003ed0ec(void)
{
    uint64_t tag = 0;
    uint64_t extraout_x8 = 0;   /* extraout_x8 */

    tag = sk_x_0035ac70((uint64_t)"Unavailable in Exclaves" /* s_Unavailable_in_Exclaves_005dc0d0 */);
    tag = sk_x_003593c0(tag, tag);
    sk_x_001afa84(tag, 0xb, 2, 0xd000000000000017, extraout_x8 | 0x8000000000000000,
                  (uint64_t)"Concurrency Task swift" /* s__Concurrency_Task_swift_005dc0b0 */, 0x17, 2);
}

/* FUN_003edf5c @ 0x003edf5c   (est. sk_capop_003edf5c)
 * Ghidra: void FUN_003edf5c(void)
 * Capability-op entry that runs a finalizer helper, releases the op-frame
 * reference stored at ctx+0x38, calls the message-build helper 0x40678c, then
 * tail-dispatches through the unrecovered jump table.
 * Confidence: low
 * Notes: UNRECOVERED_JUMPTABLE at 0x003edfa4; ctx+0x38 release via 0x40bd24. */
static void sk_capop_003edf5c(void)
{
    uint64_t ctx = 0;   /* unaff_x22: current op context */

    sk_x_00407000();
    sk_x_0040bd24(*(uint64_t *)(ctx + 0x38));
    sk_x_0040678c();
    /* tail dispatch: indirect jump, jumptable at 0x003edfa4 not recovered by Ghidra */
    return;
}

/* FUN_003ee8e4 @ 0x003ee8e4   (est. sk_capop_003ee8e4)
 * Ghidra: void FUN_003ee8e4(void)
 * Capability-op entry that runs a finalizer helper, hands the op-frame region
 * at ctx+0x10 to the frame-release helper 0x40d07c, runs another helper
 * (0x407128), then tail-dispatches through the unrecovered jump table.
 * Confidence: low
 * Notes: UNRECOVERED_JUMPTABLE at 0x003ee92c; ctx+0x10 passed to 0x40d07c. */
static void sk_capop_003ee8e4(void)
{
    uint64_t ctx = 0;   /* unaff_x22: current op context */

    sk_x_00407000();
    sk_x_0040d07c(ctx + 0x10);
    sk_x_00407128();
    /* tail dispatch: indirect jump, jumptable at 0x003ee92c not recovered by Ghidra */
    return;
}

/* FUN_003e6d08 @ 0x003e6d08   (est. sk_capop_003e6d08)
 * Ghidra: void FUN_003e6d08(void)
 * Seeds a per-invocation capability reply: it reads a 16-byte result pair,
 * formats it through a capability-operation helper, then performs a vtable
 * dispatch into the running operation context to hand the result to the
 * caller's continuation. Finally it writes the result pair's hi word plus the
 * running op register into the reply slot at an offset derived from the
 * dispatch frame. It drives the current op context toward completion.
 * Confidence: low
 * Notes: Ghidra artifacts: unaff_x24/in_x3/in_x7 plus extraout x1/x8/x16 regs;
 *   in_x7 is an indirect code pointer; the second dispatch arg is the
 *   synthetic &stack0xffffffffffffff90 slot (unrecoverable address). */
static void
sk_capop_003e6d08(void)
{
    uint64_t *slots;
    int64_t base;
    cl4_result_t r;

    r = sk_x_0034d2b4();
    sk_x_003509c8(0 /*in_x3*/, r.lo, r.lo);
    ((void (*)(uint64_t, uint64_t, uint64_t))(*(uint64_t *)(0 /*extraout_x16*/ + 0x20)))(0 /*extraout_x8*/, 0 /*extraout_x1*/, 0 /*in_x3*/);
    base = ((int64_t (*)(uint64_t, void *))0 /*in_x7*/)(0, (void *)0); /* arg2: &stack0xffffffffffffff90 */
    slots = (uint64_t *)(0 /*extraout_x8*/ + *(int *)(base + 0x34));
    *slots = r.hi;
    slots[1] = 0 /*unaff_x24*/;
    return;
}

/* FUN_003e838c @ 0x003e838c   (est. sk_capop_003e838c)
 * Ghidra: void FUN_003e838c(undefined8 param_1,undefined8 param_2,undefined8 param_3,long param_4)
 * Builds a per-invocation op frame seeded from the running context (ctx): it
 * allocates a large number of capability/message slots via the op-frame
 * allocator, fills them from the message parameters and intermediate
 * capability lookups, and stores every intermediate into ctx+OFF. Depending on
 * a condition register it either releases the frame or performs an extra
 * capability lookup before recording the final slot values, then runs the
 * frame to completion. Faithful to the decompile: every call and store kept in
 * order, no merging.
 * Confidence: low
 * Notes: Ghidra artifacts: heavy extraout_x8/x8_00.._07/x16/x16_00.._07 usage;
 *   unaff_x22/ctx is the current op context; FUN_0040bb18 is the op-frame
 *   allocator, FUN_0040bd24 a per-op-frame release; one indirect call through
 *   code* extraout_x8_08. */
static void
sk_capop_003e838c(uint64_t param_1, uint64_t param_2, uint64_t param_3, int64_t param_4)
{
    uint64_t v;
    uint64_t s;
    uint64_t n;
    int64_t msg;
    uint64_t saved;
    uint8_t *ctx = 0;              /* unaff_x22: current op context */

    sk_x_004079cc();
    sk_x_004070d8();
    msg = param_4;
    sk_x_0040752c();
    saved = *(uint64_t *)(msg + 0x18);
    *(uint64_t *)(ctx + 0x38) = saved;
    sk_x_0007c028();
    *(uint64_t *)(ctx + 0x40) = 0 /*extraout_x16*/;
    v = sk_x_00407b48(*(uint64_t *)(0 /*extraout_x8*/ + 0x40));
    *(uint64_t *)(ctx + 0x48) = v;
    v = sk_x_0040bb18(0 /*unaff_x20*/ & 0xfffffffffffffff0);
    *(uint64_t *)(ctx + 0x50) = v;
    v = sk_x_0040bb18(0 /*unaff_x20*/ & 0xfffffffffffffff0);
    *(uint64_t *)(ctx + 0x58) = v;
    *(uint64_t *)(ctx + 0x60) = *(uint64_t *)(param_4 + 0x20);
    *(uint64_t *)(ctx + 0x68) = *(uint64_t *)(param_4 + 0x10);
    sk_x_004083d8();
    sk_x_00350798();
    v = sk_x_004085b4();
    *(uint64_t *)(ctx + 0x70) = v;
    sk_x_00352018();
    *(uint64_t *)(ctx + 0x78) = 0 /*extraout_x16_00*/;
    v = sk_x_004078e8(*(uint64_t *)(0 /*extraout_x8_00*/ + 0x40));
    *(uint64_t *)(ctx + 0x80) = v;
    sk_x_004072c0();
    v = sk_x_004085b4();
    *(uint64_t *)(ctx + 0x88) = v;
    sk_x_00350798();
    v = sk_x_00310d68();
    *(uint64_t *)(ctx + 0x90) = v;
    sk_x_00352018();
    *(uint64_t *)(ctx + 0x98) = 0 /*extraout_x16_01*/;
    v = sk_x_004078e8(*(uint64_t *)(0 /*extraout_x8_01*/ + 0x40));
    *(uint64_t *)(ctx + 0xa0) = v;
    sk_x_0040683c();
    *(uint64_t *)(ctx + 0xa8) = 0 /*extraout_x16_02*/;
    sk_x_004078e8(*(uint64_t *)(0 /*extraout_x8_02*/ + 0x40));
    sk_x_00408328();
    sk_x_003510a0(0xff);
    s = sk_x_00377824();
    *(uint64_t *)(ctx + 0xc0) = s;
    sk_x_00350798();
    v = sk_x_00310d68();
    *(uint64_t *)(ctx + 200) = v;   /* 200 == 0xc8 */
    sk_x_00352018();
    *(uint64_t *)(ctx + 0xd0) = 0 /*extraout_x16_03*/;
    n = *(int64_t *)(0 /*extraout_x8_03*/ + 0x40) + 0xf;
    v = sk_x_0040bb18(n & 0xfffffffffffffff0);
    *(uint64_t *)(ctx + 0xd8) = v;
    v = sk_x_0040bb18(n & 0xfffffffffffffff0);
    *(uint64_t *)(ctx + 0xe0) = v;
    sk_x_0040683c();
    *(uint64_t *)(ctx + 0xe8) = 0 /*extraout_x16_04*/;
    v = sk_x_00407b48(*(uint64_t *)(0 /*extraout_x8_04*/ + 0x40));
    *(uint64_t *)(ctx + 0xf0) = v;
    v = sk_x_0040bb18(s & 0xfffffffffffffff0);
    *(uint64_t *)(ctx + 0xf8) = v;
    sk_x_0035050c();
    v = sk_x_00377824();
    *(uint64_t *)(ctx + 0x100) = v;
    sk_x_00352018();
    *(uint64_t *)(ctx + 0x108) = 0 /*extraout_x16_05*/;
    v = sk_x_00407b48(*(uint64_t *)(0 /*extraout_x8_05*/ + 0x40));
    *(uint64_t *)(ctx + 0x110) = v;
    v = sk_x_0040bb18(s & 0xfffffffffffffff0);
    *(uint64_t *)(ctx + 0x118) = v;
    v = sk_x_0040bb18(s & 0xfffffffffffffff0);
    *(uint64_t *)(ctx + 0x120) = v;
    sk_x_004083c0();
    sk_x_003510a0();
    n = sk_x_00377824();
    *(uint64_t *)(ctx + 0x128) = n;
    sk_x_00350798();
    v = sk_x_00310d68();
    *(uint64_t *)(ctx + 0x130) = v;
    sk_x_00352018();
    *(uint64_t *)(ctx + 0x138) = 0 /*extraout_x16_06*/;
    v = sk_x_004078e8(*(uint64_t *)(0 /*extraout_x8_06*/ + 0x40));
    *(uint64_t *)(ctx + 0x140) = v;
    sk_x_0040683c();
    *(uint64_t *)(ctx + 0x148) = 0 /*extraout_x16_07*/;
    v = sk_x_00407b48(*(uint64_t *)(0 /*extraout_x8_07*/ + 0x40));
    *(uint64_t *)(ctx + 0x150) = v;
    v = sk_x_0040bb18(n & 0xfffffffffffffff0);
    *(uint64_t *)(ctx + 0x158) = v;
    if (0 /*extraout_x1*/ == 0) {
        sk_x_00407248();
        v = 0 /*extraout_x8_10*/;
    }
    else {
        sk_x_00407374(param_3);
        sk_x_00084180();
        ((void (*)(void))0 /*extraout_x8_08*/)();
        sk_x_0008e1ec();
        v = 0 /*extraout_x8_09*/;
    }
    *(uint64_t *)(ctx + 0x160) = v;
    *(uint64_t *)(ctx + 0x168) = saved;
    sk_x_00353080();
    sk_x_004078f4();
    sk_x_00408db8();
    return;
}

/* FUN_003e9df8 @ 0x003e9df8   (est. sk_capop_003e9df8)
 * Ghidra: void FUN_003e9df8(void)
 * Seals a capability reply for the running operation: it fetches a 16-byte
 * result pair, normalises it through a capability-operation helper, dispatches
 * into the current op context via a vtable slot, and stores the pair's hi word
 * plus the running op register into the reply slot at an offset from the
 * dispatch frame. It finishes by releasing the operation with a final cleanup
 * call. Every call and store is preserved verbatim.
 * Confidence: low
 * Notes: Ghidra artifacts: unaff_x19 (code pointer)/x23/x30, in_x3, extraout
 *   x1/x8/x16 regs; FUN_0040bb18-style op-frame usage; auVar3 pair. */
static void
sk_capop_003e9df8(void)
{
    uint64_t *slots;
    int64_t base;
    cl4_result_t r;

    sk_x_00084220();
    r = sk_x_00407484();
    sk_x_003509c8(0 /*in_x3*/, r.lo, r.lo);
    ((void (*)(uint64_t, uint64_t, uint64_t))(*(uint64_t *)(0 /*extraout_x16*/ + 0x20)))(0 /*extraout_x8*/, 0 /*extraout_x1*/, 0 /*in_x3*/);
    sk_x_0034d004(0);
    base = ((int64_t (*)(void))0 /*unaff_x19*/)();
    slots = (uint64_t *)(0 /*extraout_x8*/ + *(int *)(base + 0x2c));
    *slots = r.hi;
    slots[1] = 0 /*unaff_x23*/;
    sk_x_00084234(0 /*unaff_x30*/);
    return;
}

/* FUN_003ea8f4 @ 0x003ea8f4   (est. sk_capop_003ea8f4)
 * Ghidra: void FUN_003ea8f4(void)
 * Dispatches a capability operation from the current op context (ctx). On the
 * in_ZR (zero-flag) path it releases two op frames, rebuilds a fresh result
 * pair and hands it to the context, then tail-dispatches. Otherwise it reads
 * two frame pointers from ctx, runs a capability check, allocates a new
 * op-frame slot from a size field, records a continuation label into the new
 * slot and passes it to the context before tail-dispatching. Both branches end
 * in unrecovered indirect jumps.
 * Confidence: low
 * Notes: Ghidra artifacts: two unrecovered jumptables at 0x003ea980 and
 *   0x003eaa1c (indirect jumps, treated as calls); LAB_003eaa20 continuation;
 *   extraout_x9/x9_00 code pointers; FUN_0040bb18/0040bd24 op-frame
 *   alloc/release. */
static void
sk_capop_003ea8f4(void)
{
    int64_t off;
    int64_t base;
    uint64_t arg;
    uint64_t val;
    uint64_t *slot;
    uint64_t f;
    uint8_t *ctx = 0;              /* unaff_x22: current op context */
    cl4_result_t r;

    arg = sk_x_00407ca0();
    sk_x_0040700c();
    f = *(uint64_t *)(ctx + 0x60);
    val = sk_x_00406420();
    if (0 /* in_ZR */) {
        sk_x_0040711c(*(uint64_t *)(ctx + 0x70), val, *(uint64_t *)(ctx + 0x68));
        ((void (*)(void))0 /*extraout_x9*/)();
        sk_x_00407960();
        val = *(uint64_t *)(ctx + 0x58);
        sk_x_004077cc();
        sk_x_00406c5c();
        sk_x_0040bd24(f);
        sk_x_0040bd24(val);
        r = sk_x_0040678c();
        sk_x_00407e58(r.lo, r.hi, arg);
        /* WARNING: Could not recover jumptable at 0x003ea980. Too many branches */
        /* WARNING: Treating indirect jump as call */
        /* tail dispatch: indirect jump, jumptable at 0x003ea980 not recovered by Ghidra */
        return;
    }
    off = *(int64_t *)(ctx + 0x28);
    base = *(int64_t *)(ctx + 0x30);
    sk_x_00406bd4(*(uint64_t *)(ctx + 0x80), *(uint64_t *)(ctx + 0x88));
    ((void (*)(void))0 /*extraout_x9_00*/)();
    sk_x_004062a8(*(uint64_t *)(base + *(int *)(off + 0x2c)));
    sk_x_0040bb18(*(uint32_t *)(0 /*extraout_x8*/ + 4));
    slot = (uint64_t *)sk_x_00406fe0();
    *(uint64_t **)(ctx + 0xb8) = slot;
    *slot = 0 /*extraout_x17*/;
    slot[1] = 0x003eaa20;          /* LAB_003eaa20 */
    sk_x_00407610(slot, *(uint64_t *)(ctx + 0x88));
    /* WARNING: Could not recover jumptable at 0x003eaa1c. Too many branches */
    /* WARNING: Treating indirect jump as call */
    /* tail dispatch: indirect jump, jumptable at 0x003eaa1c not recovered by Ghidra */
    return;
}

/* FUN_003eb1d8 @ 0x003eb1d8   (est. sk_capop_003eb1d8)
 * Ghidra: void FUN_003eb1d8(void)
 * Dispatches a capability operation from the current op context (ctx). If a
 * flag bit in the op frame is set it releases an op frame, builds a fresh
 * result pair and hands it to the context before tail-dispatching. Otherwise
 * it allocates a new op-frame slot from a size field, records a continuation
 * label into it, links it into the context, and tail-dispatches. Both paths
 * end in unrecovered indirect jumps.
 * Confidence: low
 * Notes: Ghidra artifacts: unrecovered jumptables at 0x003eb240 and 0x003eb2d8
 *   (indirect jumps, treated as calls); LAB_003eb2dc continuation; extraout
 *   x16/x17; FUN_0040bb18/0040bd24 op-frame alloc/release. */
static void
sk_capop_003eb1d8(void)
{
    int64_t off;
    uint64_t arg;
    uint64_t *slot;
    uint8_t *ctx = 0;              /* unaff_x22: current op context */
    cl4_result_t r;

    arg = sk_x_0040790c();
    sk_x_004070d8();
    if ((**(uint8_t **)(ctx + 0x20) & 1) != 0) {
        sk_x_00407604();
        sk_x_0040686c();
        sk_x_0040bd24();
        r = sk_x_0040678c();
        sk_x_004079b4(r.lo, r.hi, arg);
        /* WARNING: Could not recover jumptable at 0x003eb240. Too many branches */
        /* WARNING: Treating indirect jump as call */
        /* tail dispatch: indirect jump, jumptable at 0x003eb240 not recovered by Ghidra */
        return;
    }
    off = *(int64_t *)(ctx + 0x30);
    sk_x_0040652c();
    sk_x_00406608();
    sk_x_004068f4();
    sk_x_00406268();
    sk_x_0040bb18(*(uint32_t *)(off + 4));
    slot = (uint64_t *)sk_x_00406fe0();
    *(uint64_t **)(ctx + 0x68) = slot;
    *slot = 0 /*extraout_x17*/;
    slot[1] = 0x003eb2dc;          /* LAB_003eb2dc */
    sk_x_00406ab4(*(uint64_t *)(ctx + 0x50));
    /* UNRECOVERED_JUMPTABLE = extraout_x16;  (dead store into tail-dispatch target) */
    sk_x_004080cc();
    /* WARNING: Could not recover jumptable at 0x003eb2d8. Too many branches */
    /* WARNING: Treating indirect jump as call */
    /* tail dispatch: indirect jump, jumptable at 0x003eb2d8 not recovered by Ghidra */
    return;
}

/* FUN_003ebfe8 @ 0x003ebfe8   (est. sk_capop_003ebfe8)
 * Ghidra: void FUN_003ebfe8(void)
 * Drives a capability invocation: it performs several setup calls, obtains a
 * capability object, then a code pointer from an out-of-slice lookup, and
 * finally calls through that pointer with two capability values, feeding the
 * earlier result through a final cleanup call. Preserves every call in order.
 * Confidence: low
 * Notes: Ghidra artifacts: extraout_x1, code* extraout_x8 (indirect call), and
 *   code* pcVar3 obtained from FUN_003d4658 and invoked directly. */
static void
sk_capop_003ebfe8(void)
{
    uint64_t a;
    uint64_t b;
    uint8_t *fn;                   /* code pointer from lookup */
    uint64_t c;

    sk_x_0008409c();
    sk_x_0031986c(0 /*extraout_x1*/);
    sk_x_0034bcf0();
    a = ((uint64_t (*)(void))0 /*extraout_x8*/)();
    sk_x_00350878(0xff);
    sk_x_00377824();
    sk_x_003507e0();
    sk_x_00351e3c();
    b = sk_x_00377bec();
    fn = (uint8_t *)sk_x_003d4658();
    sk_x_00350500();
    c = sk_x_00377dcc();
    ((void (*)(uint64_t, uint64_t))fn)(c, b);
    sk_x_0036b118(a);
    sk_x_003507e0();
    return;
}

/* FUN_003ec438 @ 0x003ec438   (est. sk_capop_003ec438)
 * Ghidra: void FUN_003ec438(void)
 * Runs a capability operation: it obtains a 16-byte pair whose hi half is a
 * function pointer, then tail-calls that pointer with a single argument formed
 * by masking the pair's lo half down to 48 bits and OR-ing in a fixed
 * 0xd707... tag (a message-slot/object tag). The jumptable leading to the
 * call is not recovered by Ghidra.
 * Confidence: low
 * Notes: Ghidra artifacts: unrecovered jumptable at 0x003ec450 (indirect jump,
 *   treated as call); auVar1 pair used as {function pointer, argument}. */
static void
sk_capop_003ec438(void)
{
    cl4_result_t r;

    r = sk_x_00407128();
    /* WARNING: Could not recover jumptable at 0x003ec450. Too many branches */
    /* WARNING: Treating indirect jump as call */
    ((void (*)(uint64_t))r.hi)(r.lo & 0xffffffffffff | 0xd707000000000000);
    return;
}

/* FUN_003ec824 @ 0x003ec824   (est. sk_capop_003ec824)
 * Ghidra: void FUN_003ec824(void)
 * Fault/diagnostic entry: runs two setup calls then traps into a breakpoint
 * (SoftwareBreakpoint with the address 0x3ec84c) and jumps to the code it
 * returns. The decompile notes this path does not return.
 * Confidence: low
 * Notes: Ghidra artifacts: SoftwareBreakpoint intrinsic; "WARNING: Does not
 *   return" noted by the decompiler. */
static void
sk_capop_003ec824(void)
{
    uint8_t *fn;                   /* code pointer from breakpoint */

    sk_x_00407030();
    sk_x_00406490();
    /* WARNING: Does not return */
    fn = (uint8_t *)SoftwareBreakpoint(1, 0x3ec84c);
    ((void (*)(void))fn)();
}

/* FUN_003ecb4c @ 0x003ecb4c   (est. sk_capop_003ecb4c)
 * Ghidra: void FUN_003ecb4c(undefined8 param_1)
 * Thin forwarding wrapper: passes param_1 together with the byte pointed to by
 * the unaff_x20 register into the in-slice handler sk_capop_003ecb64.
 * Confidence: low
 * Notes: Ghidra artifacts: unaff_x20 is a pointer register dereferenced for a
 *   single byte argument. */
static void
sk_capop_003ecb4c(uint64_t param_1)
{
    sk_capop_003ecb64(param_1, *(uint8_t *)0 /*unaff_x20*/);
    return;
}

/* FUN_003ed14c @ 0x003ed14c   (est. sk_capop_003ed14c)
 * Ghidra: void FUN_003ed14c(void)
 * Runs a capability operation: performs setup calls, obtains a 16-byte result
 * pair through an indirect code pointer, then hands both halves (plus a zero)
 * to an out-of-slice completion call. Preserves every call in order.
 * Confidence: low
 * Notes: Ghidra artifacts: extraout_x1, code* extraout_x8 (indirect call
 *   producing the pair); auVar1 pair. */
static void
sk_capop_003ed14c(void)
{
    cl4_result_t r;

    sk_x_0008409c();
    sk_x_003fd194(0 /*extraout_x1*/);
    sk_x_0034bcf0();
    r = ((cl4_result_t (*)(void))0 /*extraout_x8*/)();
    sk_x_00408c4c(r.lo, r.hi, 0);
    return;
}

/* FUN_003ee090 @ 0x003ee090   (est. sk_capop_003ee090)
 * Ghidra: void FUN_003ee090(void)
 * Dispatch for a capability operation: reads an integer dispatch table pointer
 * from the current op context (ctx), computes a result through a lookup and
 * stores it into ctx, allocates a new op-frame slot, then tail-dispatches by
 * jumping to a table entry at table + *table (recovered by Ghidra as an
 * indirect call). Every call and store preserved.
 * Confidence: low
 * Notes: Ghidra artifacts: unrecovered jumptable at 0x003ee148; extraout_x17;
 *   piVar4 is an int dispatch table whose first word is the offset and second
 *   word the allocation size; FUN_0040bb18 is the op-frame allocator. */
static void
sk_capop_003ee090(void)
{
    int off;
    uint64_t v;
    uint64_t *slot;
    int *table;
    uint8_t *ctx = 0;              /* unaff_x22: current op context */

    sk_x_00407000();
    table = *(int **)(ctx + 0x18);
    v = sk_x_0040a8d8(*(uint64_t *)(ctx + 0x28), *(uint64_t *)(ctx + 0x30));
    *(uint64_t *)(ctx + 0x48) = v;
    off = *table;
    sk_x_0040bb18(table[1]);
    slot = (uint64_t *)sk_x_00406fe0();
    *(uint64_t **)(ctx + 0x50) = slot;
    *slot = 0 /*extraout_x17*/;
    sk_x_004071c0();
    /* WARNING: Could not recover jumptable at 0x003ee148. Too many branches */
    /* WARNING: Treating indirect jump as call */
    ((void (*)(void))((int64_t)table + (int64_t)off))();
    return;
}

/* FUN_003eead0 @ 0x003eead0   (est. sk_capop_003eead0)
 * Ghidra: void FUN_003eead0(void)
 * Capability operation teardown/completion: runs several setup calls, stores a
 * value through an extraout pointer register, releases an op frame via
 * FUN_0040bd24 on a slot from the running frame, passes a frame+0x10 address
 * to an out-of-slice helper, then tail-dispatches (unrecovered jumptable).
 * Confidence: low
 * Notes: Ghidra artifacts: unrecovered jumptable at 0x003eeb68 (indirect jump,
 *   treated as call); extraout_x8/x8_00 (frame bases), long* extraout_x9
 *   (store target); FUN_0040bd24 is a per-op-frame release. */
static void
sk_capop_003eead0(void)
{
    sk_x_00407000();
    sk_x_00407018();
    sk_x_0040676c();
    /* *extraout_x9 = extraout_x8;  (store through extraout_x9 pointer reg) */
    sk_x_0040bd24(*(uint64_t *)(0 /*extraout_x8_00*/ + 0x128));
    sk_x_0040d07c(0 /*extraout_x8*/ + 0x10);
    sk_x_00407128();
    /* WARNING: Could not recover jumptable at 0x003eeb68. Too many branches */
    /* WARNING: Treating indirect jump as call */
    /* tail dispatch: indirect jump, jumptable at 0x003eeb68 not recovered by Ghidra */
    return;
}

/* FUN_003e6da8 @ 0x003e6da8   (est. sk_capop_003e6da8)
 * Ghidra: void FUN_003e6da8(long param_1)
 * Capability-op cleanup handler for the current op context. Reads the op code
 * word at offset 0x34 of the argument frame and feeds it to the shared
 * op-code decoder, then calls the kernel-side completion primitive. Returns
 * void; the invoked routines drive the invocation to completion.
 * Confidence: low
 * Notes: the two callees (003591d0, 0009461c) are out-of-slice; the frame
 *   offset 0x34 holds the op code read as a signed 32-bit value widened to
 *   uint64_t. */
static void sk_capop_003e6da8(uint64_t arg1)
{
    sk_x_003591d0((uint64_t)*(int *)(arg1 + 0x34));
    sk_x_0009461c();
    return;
}

/* FUN_003e86c8 @ 0x003e86c8   (est. sk_capop_003e86c8)
 * Ghidra: void FUN_003e86c8(void)
 * Main capability-invocation dispatch for the current op context (unaff_x22).
 * Reads the per-op code at (ctx+0x28)->0x3c, stores it at ctx+0x1e0, and
 * tests bit 0 of a byte indexed by that code; the taken branch releases a
 * batch of op frames, refreshes the result pair, and tails into the
 * reply-message dispatch jumptable. The fall-through path copies the op word
 * and message-slot fields, builds a nested op frame via the frame allocator,
 * and dispatches through per-operation handler vectors, recording handler
 * pointers and results back into the context at 0x178/0x180/0x188/0x198/
 * 0x1a0/0x1a8/0x1b0/0x1b8.
 * Confidence: low
 * Notes: two unrecovered jumptables (0x003e87b0, 0x003e8914) rendered as tail
 *   dispatch comments; LAB_003e8d3c is a continuation label; in_ZR branch is
 *   unknowable (kept both sides); the 0x10-byte result pairs (pair) from
 *   00407f60/00406894/0040678c are carried as lo/hi; the per-op-frame release
 *   (0040bd24) is invoked with the stacked arguments. */
static void sk_capop_003e86c8(void)
{
    int code;
    uint64_t result;
    uint64_t *slot;
    uint64_t base;
    cl4_result_t pair;
    uint64_t extraout_x9 = /* extraout_x9 */ 0;
    uint64_t extraout_x9_00 = /* extraout_x9_00 */ 0;
    uint64_t extraout_x10 = /* extraout_x10 */ 0;
    uint64_t extraout_x10_00 = /* extraout_x10_00 */ 0;
    uint64_t extraout_x11 = /* extraout_x11 */ 0;
    uint64_t extraout_x16 = /* extraout_x16 */ 0;
    uint64_t extraout_x16_00 = /* extraout_x16_00 */ 0;
    uint64_t extraout_x17 = /* extraout_x17 */ 0;
    uint64_t extraout_x17_00 = /* extraout_x17_00 */ 0;
    uint8_t *ctx = /* unaff_x22: current op context */ 0;
    uint64_t sp0; /* in_stack_00000000 */
    uint64_t sp1; /* in_stack_00000008 */
    uint64_t sp2; /* in_stack_00000010 */
    uint64_t sp3; /* in_stack_00000018 */
    uint64_t sp4; /* in_stack_00000020 */
    uint64_t sp5; /* in_stack_00000028 */
    uint64_t tail = /* UNRECOVERED_JUMPTABLE */ 0;

    result = sk_x_00407afc();
    pair = sk_x_00407f60();
    code = *(int *)(*(uint64_t *)(ctx + 0x28) + 0x3c);
    *(int *)(ctx + 0x1e0) = code;
    if ((*(uint8_t *)(*(uint64_t *)(ctx + 0x30) + (uint64_t)code) & 1) != 0) {
        sk_x_004066bc();
        sk_x_00350744();
        sk_x_000839d8();
        sk_x_0040bd24();
        sk_x_0040bd24();
        sk_x_0040bd24();
        sk_x_0040bd24();
        sk_x_0040bd24();
        sk_x_0040bd24();
        sk_x_0040bd24();
        sk_x_0040bd24();
        sk_x_0040bd24();
        sk_x_0040bd24(sp0);
        sk_x_0040bd24(sp1);
        sk_x_0040bd24(sp2);
        sk_x_0040bd24(sp3);
        sk_x_0040bd24(sp4);
        sk_x_0040bd24(sp5);
        sk_x_0040bd24(tail);
        pair = sk_x_0040678c();
        sk_x_004075d0(pair.lo, pair.hi, result);
        /* tail dispatch: indirect jump, jumptable at 0x003e87b0 not recovered by Ghidra */
        return;
    }
    *(int *)(ctx + 0x1e4) = *(int *)(*(uint64_t *)(ctx + 0x28) + 0x38);
    *(uint64_t *)(ctx + 0x170) = *(uint64_t *)(*(uint64_t *)(ctx + 0x138) + 0x10);
    sk_x_00408460(pair.lo, pair.hi, *(uint64_t *)(ctx + 0x130));
    ((void (*)(void))extraout_x11)();
    sk_x_00406420();
    if (0 /* in_ZR */) {
        base = *(uint64_t *)(ctx + 0x68);
        sk_x_00353930(*(uint64_t *)(ctx + 0x138), *(uint64_t *)(ctx + 0x140),
                      *(uint64_t *)(ctx + 0x130));
        *(uint64_t *)(ctx + 0x198) = extraout_x9;
        *(uint64_t *)(ctx + 0x1a0) = extraout_x10;
        ((void (*)(void))extraout_x9)();
        sk_x_0040652c();
        result = sk_x_00406608();
        *(uint64_t *)(ctx + 0x1a8) = result;
        result = sk_x_00406e8c();
        *(uint64_t *)(ctx + 0x1b0) = result;
        sk_x_00406288();
        sk_x_0040bb18(*(uint32_t *)(base + 4));
        slot = (uint64_t *)sk_x_00406fe0();
        *(uint64_t *)(ctx + 0x1b8) = (uint64_t)slot;
        *slot = extraout_x17;
        slot[1] = 0x3e8d3c; /* LAB_003e8d3c */
        sk_x_004067b8(*(uint64_t *)(ctx + 0xa0));
        tail = extraout_x16;
    }
    else {
        result = *(uint64_t *)(ctx + 0x128);
        pair = sk_x_00406894(*(uint64_t *)(ctx + 0x148),
                                                           *(uint64_t *)(ctx + 0x158),
                                                           *(uint64_t *)(ctx + 0x140));
        *(uint64_t *)(ctx + 0x178) = extraout_x9_00;
        *(uint64_t *)(ctx + 0x180) = extraout_x10_00;
        ((void (*)(uint64_t, uint64_t, uint64_t))extraout_x9_00)(pair.lo, pair.hi, result);
        result = sk_x_004067f8();
        *(uint64_t *)(ctx + 0x188) = result;
        sk_x_003fcc4c();
        base = sk_x_00406374();
        sk_x_0040bb18(*(uint32_t *)(base + 4));
        slot = (uint64_t *)sk_x_00406fe0();
        *(uint64_t *)(ctx + 400) = (uint64_t)slot;
        *slot = extraout_x17_00;
        sk_x_00406a24();
        tail = extraout_x16_00;
    }
    sk_x_004075d0();
    /* tail dispatch: indirect jump, jumptable at 0x003e8914 not recovered by Ghidra */
    return;
}

/* FUN_003e9e74 @ 0x003e9e74   (est. sk_capop_003e9e74)
 * Ghidra: void FUN_003e9e74(undefined8 param_1,long param_2)
 * Capability-op completion helper. Seeds the reply slot of the current
 * invocation from param_2 (message word, buffer, and buffer length at
 * offsets 0x20/0x10), runs the shared completion and unwind primitives, and
 * tails through the per-op handler vector located at offset 0x10 of the
 * extraout_x16 dispatch base, passing param_1 (the invoking capability).
 * Confidence: low
 * Notes: final call is an indirect dispatch through (extraout_x16+0x10) with
 *   one argument; the jumptable at 0x003e9ec8 is not recovered (tail comment). */
static void sk_capop_003e9e74(uint64_t arg1, uint64_t arg2)
{
    uint64_t extraout_x16 = /* extraout_x16 */ 0;

    sk_x_0040654c(arg2, *(uint64_t *)(arg2 + 0x20), *(uint64_t *)(arg2 + 0x10));
    sk_x_00377824();
    sk_x_00350404();
    /* tail dispatch: indirect jump, jumptable at 0x003e9ec8 not recovered by Ghidra */
    ((void (*)(uint64_t))(*(uint64_t *)(extraout_x16 + 0x10)))(arg1);
    return;
}

/* FUN_003eab58 @ 0x003eab58   (est. sk_capop_003eab58)
 * Ghidra: void FUN_003eab58(void)
 * Capability-op release/teardown for the current op context (unaff_x22).
 * Runs the pre-release bookkeeping (register save, message refill, lock
 * release), releases the current op frame and the one holding the saved
 * message slot (read from ctx+0x58), then refreshes the result pair and
 * tails into the reply-dispatch jumptable. Returns void.
 * Confidence: low
 * Notes: unrecovered jumptable at 0x003eabc0 rendered as a tail-dispatch
 *   comment; the single per-op-frame release (0040bd24) receives no explicit
 *   frame and is emitted with no argument. */
static void sk_capop_003eab58(void)
{
    uint64_t slot;
    uint8_t *ctx = /* unaff_x22: current op context */ 0;

    sk_x_00406fd4();
    sk_x_00407960();
    slot = *(uint64_t *)(ctx + 0x58);
    sk_x_004077cc();
    sk_x_00406ee4();
    sk_x_0040bd24();
    sk_x_0040bd24(slot);
    sk_x_0040678c();
    /* tail dispatch: indirect jump, jumptable at 0x003eabc0 not recovered by Ghidra */
    return;
}

/* FUN_003eb398 @ 0x003eb398   (est. sk_capop_003eb398)
 * Ghidra: void FUN_003eb398(void)
 * Capability-op dispatch for the current op context (unaff_x22). Pulls the
 * frame word at ctx+0x38, tests the zero-flag result of the shared op-entry
 * probe; the taken branch builds a fresh result pair and tails into the
 * reply-message jumptable after releasing the frame. The fall-through path
 * performs a nested op-frame allocation (seeded with the op word from
 * ctx+0x18->0x28 and the continuation LAB_003eb4b4), records the frame at
 * ctx+0x88 and the handler/result pair at ctx+0x78/0x80, then tails into the
 * handler dispatch jumptable.
 * Confidence: low
 * Notes: unrecovered jumptables at 0x003eb418 and 0x003eb4b0 rendered as tail
 *   dispatch comments; LAB_003eb4b4 is a continuation label; the in_ZR branch
 *   is unknowable (both sides kept); the 16-byte result pair (pair) from
 *   0040678c is carried as lo/hi. */
static void sk_capop_003eb398(void)
{
    uint64_t base;
    uint64_t result;
    uint64_t check;
    uint64_t *slot;
    uint64_t extraout_x8 = /* extraout_x8 */ 0;
    uint64_t extraout_x9 = /* extraout_x9 */ 0;
    uint64_t extraout_x9_00 = /* extraout_x9_00 */ 0;
    uint64_t extraout_x9_01 = /* extraout_x9_01 */ 0;
    uint64_t extraout_x10 = /* extraout_x10 */ 0;
    uint64_t saved;
    uint8_t *ctx = /* unaff_x22: current op context */ 0;
    cl4_result_t pair;

    result = sk_x_00407ca0();
    sk_x_0040700c();
    saved = *(uint64_t *)(ctx + 0x38);
    check = sk_x_00406420();
    if (0 /* in_ZR */) {
        sk_x_0040711c(*(uint64_t *)(ctx + 0x48), check, *(uint64_t *)(ctx + 0x40));
        ((void (*)(void))extraout_x9)();
        sk_x_00407604();
        sk_x_0040686c();
        sk_x_0040bd24(saved);
        pair = sk_x_0040678c();
        sk_x_00407e58(pair.lo, pair.hi, result);
        /* tail dispatch: indirect jump, jumptable at 0x003eb418 not recovered by Ghidra */
        return;
    }
    base = *(uint64_t *)(ctx + 0x18);
    sk_x_00406894(*(uint64_t *)(ctx + 0x58), *(uint64_t *)(ctx + 0x60));
    *(uint64_t *)(ctx + 0x78) = extraout_x9_00;
    *(uint64_t *)(ctx + 0x80) = extraout_x10;
    sk_x_00350624();
    ((void (*)(void))extraout_x9_01)();
    sk_x_004062e8((uint64_t)*(int *)(base + 0x28));
    slot = (uint64_t *)sk_x_0040bb18(*(uint32_t *)(extraout_x8 + 4));
    *(uint64_t *)(ctx + 0x88) = (uint64_t)slot;
    *slot = (uint64_t)ctx;
    slot[1] = 0x3eb4b4; /* LAB_003eb4b4 */
    sk_x_00406bb4(*(uint64_t *)(ctx + 0x60));
    /* tail dispatch: indirect jump, jumptable at 0x003eb4b0 not recovered by Ghidra */
    return;
}

/* FUN_003ec094 @ 0x003ec094   (est. sk_capop_003ec094)
 * Ghidra: void FUN_003ec094(void)
 * Single-assignment capability-op that initializes the module-global op
 * table slot (sk_g_006adf30) from the symbol-resolution helper, passing the
 * two symbol table anchors 0x6578a0 and 0x6c0b68. Returns void.
 * Confidence: low
 * Notes: the Ghidra warning notes globals starting with '_' overlap smaller
 *   symbols at the same address; the assigned global is used as a value. */
static void sk_capop_003ec094(void)
{
    sk_g_006adf30 = sk_x_0036a9d4(0x6578a0, 0x6c0b68);
    return;
}

/* FUN_003ec4dc @ 0x003ec4dc   (est. sk_capop_003ec4dc)
 * Ghidra: void FUN_003ec4dc(void)
 * Capability-op cleanup/teardown using the caller-saved register frame
 * (extraout_x8 = context base, extraout_x9 = frame base, unaff_x20 =
 * distinguishing value). Stores the frame base into the slot pointed by
 * extraout_x10, links the context pointer into the frame at +0x40, releases
 * the frame holding the word at extraout_x8+0x38, then selects the cleanup
 * continuation: the in-slice handler FUN_003ec598 when unaff_x20 is zero,
 * otherwise the LAB_003ec5f8 continuation, installing it via 00353498.
 * Returns void.
 * Confidence: low
 * Notes: FUN_003ec598 is in-slice (sk_capop_003ec598); LAB_003ec5f8 is a
 *   continuation label; extraout_x8/x9/x10 and unaff_x20 carry register
 *   values through the preceding prologue. */
static void sk_capop_003ec4dc(void)
{
    uint64_t saved;
    uint64_t extraout_x8 = /* extraout_x8 */ 0;
    uint64_t extraout_x9 = /* extraout_x9 */ 0;
    uint64_t *extraout_x10 = /* extraout_x10 */ 0;
    uint64_t cont;
    uint64_t x20 = /* unaff_x20 */ 0;

    sk_x_00407000();
    sk_x_00407018();
    sk_x_0040691c();
    *extraout_x10 = extraout_x9;
    saved = *(uint64_t *)(extraout_x8 + 0x38);
    *(uint64_t *)(extraout_x9 + 0x40) = x20;
    sk_x_0040bd24(saved);
    if (x20 == 0) {
        cont = 0x3ec598; /* FUN_003ec598 -> sk_capop_003ec598 */
    }
    else {
        cont = 0x3ec5f8; /* LAB_003ec5f8 */
    }
    sk_x_00353498(cont);
    sk_x_00408db8();
    return;
}

/* FUN_003ec84c @ 0x003ec84c   (est. sk_capop_003ec84c)
 * Ghidra: void FUN_003ec84c(void)
 * Capability-op breakpoint trap: after the pre-breakpoint bookkeeping, this
 * fires a SoftwareBreakpoint at 0x3ec874 and dispatches to the breakpoint
 * handler vector. The decompiler marks it as not returning, so the handler
 * never falls through.
 * Confidence: low
 * Notes: the decompiler emits SoftwareBreakpoint(1,0x3ec874) as the trap
 *   intrinsic; the function is flagged 'Does not return'. */
static void sk_capop_003ec84c(void)
{
    uint64_t trap;

    sk_x_00407030();
    sk_x_00406490();
    /* WARNING: Does not return */
    trap = (uint64_t)SoftwareBreakpoint(1, 0x3ec874);
    ((void (*)(void))trap)();
}

/* FUN_003ecb64 @ 0x003ecb64   (est. sk_capop_003ecb64)
 * Ghidra: void FUN_003ecb64(long param_1,undefined8 param_2)
 * Message-path bridge: reads the buffer (param_1+0x18) and length/limit
 * (param_1+0x20), runs the message-copy primitive on the frame, invokes a
 * per-message handler obtained from 000a649c on a small stack scratch area,
 * folds the result through the 000836a4 aggregator, invokes a second handler
 * obtained from 00319f3c with param_2 and the accumulated message state, and
 * tears down the scratch frame. Returns void.
 * Confidence: low
 * Notes: the two handlers are obtained via code-pointer-returning callees and
 *   invoked through indirect calls; auStack_68 is a 24-byte stack scratch
 *   buffer; local_50/uStack_48 are 8-byte stack locals passed by value. */
static void sk_capop_003ecb64(uint64_t arg1, uint64_t arg2)
{
    uint64_t buf;
    uint64_t len;
    uint64_t handler;
    uint8_t scratch[24]; /* auStack_68 */
    uint64_t out_lo;     /* local_50 */
    uint64_t out_hi;     /* uStack_48 */

    buf = *(uint64_t *)(arg1 + 0x18);
    len = *(uint64_t *)(arg1 + 0x20);
    sk_x_0006a4c0(arg1, buf);
    handler = (uint64_t)sk_x_000a649c(len);
    ((void (*)(uint8_t *, uint64_t, uint64_t))handler)(scratch, buf, len);
    sk_x_000836a4(scratch, out_lo);
    handler = (uint64_t)sk_x_00319f3c(out_hi);
    ((void (*)(uint64_t, uint64_t, uint64_t))handler)(arg2, out_lo, out_hi);
    sk_x_000026e8(scratch);
    return;
}

/* FUN_003ed1a4 @ 0x003ed1a4   (est. sk_capop_003ed1a4)
 * Ghidra: void FUN_003ed1a4(undefined8 param_1,undefined8 param_2,undefined8 param_3,code *param_4,undefined8 param_5,undefined8 param_6,undefined8 param_7)
 * Capability-op invocation bridge. Resolves a pair of symbol anchors
 * (sk_g_0064c260 / sk_g_004bbc30), allocates a new op frame via 0031dc0c with
 * the given type (0x66c1c8) and argument, reads the frame's dispatch table
 * base from frame-8, aligns the message length through the global size fn
 * (sk_g_00658c80), sets up a stack scratch area, seeds it via 00409c24, then
 * calls the caller-supplied handler (param_4) with param_1 and the scratch,
 * and finally invokes the frame's continuation at dtab+8. Returns void.
 * Confidence: low
 * Notes: param_4 is an incoming code pointer invoked indirectly; sk_g_00658c80
 *   is a function-pointer global dereferenced directly; the stack scratch is
 *   an emulated frame slot (extraout_x8 is a 0-valued local); param_5/6 are
 *   declared but unused in the decompiled body. */
static void sk_capop_003ed1a4(uint64_t arg1, uint64_t arg2, uint64_t arg3, uint64_t arg4,
                              uint64_t arg5, uint64_t arg6, uint64_t arg7)
{
    uint64_t anchor;
    uint64_t frame;
    uint64_t dtab;
    uint64_t extraout_x8 = /* extraout_x8 */ 0;
    uint8_t *scratch;
    uint8_t stackbuf[0x40]; /* emulated stack slot at 0xffffffffffffffa0 */

    anchor = sk_x_00027614(&sk_g_0064c260, &sk_g_004bbc30);
    frame = sk_x_0031dc0c(0, arg7, anchor, 0x66c1c8);
    dtab = *(uint64_t *)(frame + -8);
    ((void (*)(uint64_t))sk_g_00658c80)((*(uint64_t *)(dtab + 0x40) + 0xfU) & 0xfffffffffffffff0);
    scratch = (uint8_t *)((uint64_t)stackbuf - extraout_x8);
    sk_x_00409c24(scratch, arg2, arg3, frame);
    ((void (*)(uint64_t, uint8_t *))arg4)(arg1, scratch);
    ((void (*)(uint8_t *, uint64_t))(*(uint64_t *)(dtab + 8)))(scratch, frame);
    return;
}

/* FUN_003ee234 @ 0x003ee234   (est. sk_capop_003ee234)
 * Ghidra: void FUN_003ee234(void)
 * Capability-op dispatch for the current op context (unaff_x22). Runs the
 * pre-dispatch bookkeeping, feeds the capability word at ctx+0x48 into the
 * message handler, refreshes the result pair, and tails into the
 * reply-dispatch jumptable. Returns void.
 * Confidence: low
 * Notes: unrecovered jumptable at 0x003ee27c rendered as a tail-dispatch
 *   comment; ctx+0x48 supplies the capability being dispatched. */
static void sk_capop_003ee234(void)
{
    uint8_t *ctx = /* unaff_x22: current op context */ 0;

    sk_x_00407000();
    sk_x_0040a9b0(*(uint64_t *)(ctx + 0x48));
    sk_x_0040678c();
    /* tail dispatch: indirect jump, jumptable at 0x003ee27c not recovered by Ghidra */
    return;
}

/* FUN_003eeb6c @ 0x003eeb6c   (est. sk_capop_003eeb6c)
 * Ghidra: void FUN_003eeb6c(void)
 * Capability-op frame builder. Runs the pre-build bookkeeping, allocates an
 * op frame sized by the global sk_g_005a0194, pulls a frame base from
 * 00407ac4, seeds its first word with the pending result and links its
 * continuation to the in-slice handler FUN_003eebf0, then folds the frame
 * handle through 00019858 and passes the resulting lo/hi pair with the op
 * result to 003ef924. Returns void.
 * Confidence: low
 * Notes: FUN_003eebf0 is in-slice (sk_capop_003eebf0), referenced as a value
 *   (its address stored in the frame); the 16-byte pair from 00019858 is
 *   carried as lo/hi; the per-op-frame allocator 0040bb18 receives the global
 *   size value. */
static void sk_capop_003eeb6c(void)
{
    uint64_t result;
    uint64_t *slot;
    uint64_t extraout_x17 = /* extraout_x17 */ 0;
    cl4_result_t pair;

    result = sk_x_00407000();
    sk_x_0040bb18(sk_g_005a0194);
    slot = (uint64_t *)sk_x_00407ac4();
    *slot = extraout_x17;
    slot[1] = (uint64_t)sk_capop_003eebf0; /* FUN_003eebf0 */
    pair = sk_x_00019858((uint64_t)(slot + 1));
    sk_x_003ef924(pair.lo, pair.hi, result);
    return;
}

/* FUN_003e6dd0 @ 0x003e6dd0   (est. sk_capop_003e6dd0)
 * Ghidra: void FUN_003e6dd0(undefined8 param_1,long param_2)
 * Drives a capability invocation to completion from the op frame (param_2).
 * Reads an index field at +0x38, invokes the metadata/transfer glue with the
 * slot words at +0x28/+0x18, then performs several kernel setup steps and
 * dispatches through a vtable pointer at +0x10 of the extraout base. The
 * indirect jump is a tail dispatch into the next handler.
 * Confidence: low
 * Notes: unrecovered jumptable at 0x003e6e3c (too many branches); uses
 *   extraout_x16 as a vtable base; unaff_x20 supplies the op-frame base. */
static void
sk_capop_003e6dd0(uint64_t arg1, int64_t arg2)
{
	int32_t index;
	uint64_t slot_val;
	uint64_t vtable_base = 0; /* extraout_x16: vtable base */
	uint64_t op_base = 0;     /* unaff_x20 */

	index = *(int32_t *)(arg2 + 0x38);
	sk_x_00406f08(arg2, *(uint64_t *)(arg2 + 0x28), *(uint64_t *)(arg2 + 0x18));
	sk_x_00377824(0xff);
	sk_x_00352efc();
	sk_x_00310d68();
	slot_val = sk_x_00350404();
	/* tail dispatch: indirect jump, jumptable at 0x003e6e3c not recovered by Ghidra */
	((void (*)(uint64_t, uint64_t, uint64_t))(*(uint64_t *)(vtable_base + 0x10)))(
		arg1, op_base + index, slot_val);
	return;
}

/* FUN_003e89f0 @ 0x003e89f0   (est. sk_capop_003e89f0)
 * Ghidra: void FUN_003e89f0(void)
 * The main op-frame driver for a capability invocation, seeded with the
 * current op context (unaff_x22 -> ctx). It branches on a condition-flag from
 * a preceding call: the true path builds a message-slot/result reply frame,
 * while the false path teardown path frees the whole op frame through the
 * per-op-frame release helper. Both paths end in an unrecovered indirect tail
 * jump that returns control to the dispatch loop.
 * Confidence: low
 * Notes: two unrecovered jumptables at 0x003e8d38 and 0x003e8ca0 (too many
 *   branches); uses in_ZR twice; LAB_003e8d3c referenced as a code address;
 *   stores vtable pointers into ctx at +0x178/+0x180/+0x198/+0x1a0;
 *   op-frame allocator 0040bb18 and release 0040bd24. */
static void
sk_capop_003e89f0(void)
{
	cl4_result_t result_pair; /* auVar17 */
	void (*msg_fn)(uint64_t, uint64_t, uint64_t, uint64_t); /* pcVar1 */
	void (*slot_fn)(); /* pcVar12: vtable function pointer */
	uint64_t u2, u3, u4, u7, u8, u9, u10, u13, u14;
	uint64_t *pu5, *pu16;
	int64_t l6, l11, l15;
	uint64_t in_stack_0 = 0; /* in_stack_00000000 */
	uint64_t in_stack_8 = 0; /* in_stack_00000008 */
	void (*e8)(void) = 0;            /* extraout_x8 */
	void (*e8_00)(void) = 0;         /* extraout_x8_00 */
	void (*e8_01)(void) = 0;         /* extraout_x8_01 */
	void (*e9)(void) = 0;            /* extraout_x9 */
	void (*e9_00)(uint64_t, uint64_t, uint64_t) = 0; /* extraout_x9_00 */
	uint64_t e10 = 0;                /* extraout_x10 */
	uint64_t e10_00 = 0;             /* extraout_x10_00 */
	void (*e16)(void) = 0;           /* extraout_x16 */
	void (*e16_00)(void) = 0;        /* extraout_x16_00 */
	uint64_t e17 = 0;                /* extraout_x17 */
	uint64_t e17_00 = 0;             /* extraout_x17_00 */
	void (*tail_00)(void) = 0; /* UNRECOVERED_JUMPTABLE_00 */
	uint8_t *ctx = /* unaff_x22: current op context */ 0;

	u4 = sk_x_00407afc();
	sk_x_00407f60();
	u9 = *(uint64_t *)(ctx + 0xe0);
	u10 = *(uint64_t *)(ctx + 0xc0);
	sk_x_00406be4();
	if (0 /* in_ZR */) {
		l6 = *(int64_t *)(ctx + 0xd0);
		((void (*)(uint64_t, uint64_t))(*(uint64_t *)(*(uint64_t *)(ctx + 0x148) + 8)))(
			*(uint64_t *)(ctx + 0x158), *(uint64_t *)(ctx + 0x128));
		sk_x_003507e0(*(uint64_t *)(l6 + 8));
		e8();
		sk_x_00407764();
		e8_00();
		sk_x_00350744(*(int64_t *)(ctx + 0x30) + (int64_t)*(int32_t *)(ctx + 0x1e4));
		result_pair = sk_x_000839d8();
		sk_x_00406fb0(*(uint64_t *)(ctx + 0x170), result_pair.lo, result_pair.hi,
		              *(uint64_t *)(ctx + 0x130));
		e8_01();
		sk_x_00406420();
		if (0 /* in_ZR */) {
			l6 = *(int64_t *)(ctx + 0x68);
			sk_x_00353930(*(uint64_t *)(ctx + 0x138), *(uint64_t *)(ctx + 0x140),
			              *(uint64_t *)(ctx + 0x130));
			*(uint64_t *)(ctx + 0x198) = (uint64_t)e9;
			*(uint64_t *)(ctx + 0x1a0) = e10;
			e9();
			sk_x_0040652c();
			u4 = sk_x_00406608();
			*(uint64_t *)(ctx + 0x1a8) = u4;
			u4 = sk_x_00406e8c();
			*(uint64_t *)(ctx + 0x1b0) = u4;
			sk_x_00406288();
			sk_x_0040bb18(*(int32_t *)(l6 + 4));
			pu5 = (uint64_t *)sk_x_00406fe0();
			*(uint64_t **)(ctx + 0x1b8) = pu5;
			pu5[0] = e17;
			pu5[1] = (uint64_t)0x003e8d3c; /* LAB_003e8d3c */
			sk_x_004067b8(*(uint64_t *)(ctx + 0xa0));
			tail_00 = e16;
		} else {
			u4 = *(uint64_t *)(ctx + 0x128);
			result_pair = sk_x_00406894(*(uint64_t *)(ctx + 0x148),
			                            *(uint64_t *)(ctx + 0x158),
			                            *(uint64_t *)(ctx + 0x140));
			*(uint64_t *)(ctx + 0x178) = (uint64_t)e9_00;
			*(uint64_t *)(ctx + 0x180) = e10_00;
			e9_00(result_pair.lo, result_pair.hi, u4);
			u4 = sk_x_004067f8();
			*(uint64_t *)(ctx + 0x188) = u4;
			sk_x_003fcc4c();
			l6 = sk_x_00406374();
			sk_x_0040bb18(*(int32_t *)(l6 + 4));
			pu5 = (uint64_t *)sk_x_00406fe0();
			*(uint64_t **)(ctx + 0x190) = pu5;
			pu5[0] = e17_00;
			sk_x_00406a24();
			tail_00 = e16_00;
		}
		sk_x_004075d0();
		/* tail dispatch: indirect jump, jumptable at 0x003e8d38 not recovered by Ghidra */
		return;
	}
	msg_fn = (void (*)(uint64_t, uint64_t, uint64_t, uint64_t))(
		*(uint64_t *)(ctx + 0x178));
	u3 = *(uint64_t *)(ctx + 0x180);
	l15 = (int64_t)*(int32_t *)(ctx + 0x1e4);
	u8 = *(uint64_t *)(ctx + 0x158);
	u2 = *(uint64_t *)(ctx + 0x130);
	l6 = *(int64_t *)(ctx + 0x138);
	u13 = *(uint64_t *)(ctx + 0x128);
	u14 = *(uint64_t *)(ctx + 0xf8);
	l11 = *(int64_t *)(ctx + 0x30);
	u7 = *(uint64_t *)(ctx + 0x10);
	pu16 = (uint64_t *)(*(uint64_t *)(ctx + 0xe8) + 0x20);
	slot_fn = (void (*)())*pu16;
	sk_x_00350968(u14);
	slot_fn();
	pu5 = (uint64_t *)(l6 + 8);
	((void (*)(uint64_t, uint64_t))(*(uint64_t *)*pu5))(l11 + l15, u2);
	msg_fn(u3, l11 + l15, u8, u13);
	sk_x_00350750(l11 + l15);
	sk_x_000839d8();
	slot_fn(u7, u14, u10);
	sk_x_004066bc();
	sk_x_00350750();
	sk_x_000839d8();
	sk_x_0040bd24(u13);
	sk_x_0040bd24(u14);
	sk_x_0040bd24(l15);
	sk_x_0040bd24((uint64_t)pu5);
	sk_x_0040bd24((uint64_t)pu16);
	sk_x_0040bd24(u10);
	sk_x_0040bd24(u9);
	sk_x_0040bd24(l11);
	sk_x_0040bd24((uint64_t)slot_fn);
	sk_x_0040bd24(in_stack_0);
	sk_x_0040bd24(in_stack_8);
	sk_x_0040bd24(u2);
	sk_x_0040bd24(u8);
	sk_x_0040bd24((uint64_t)msg_fn);
	sk_x_0040bd24(u3);
	sk_x_0040bd24(u7);
	result_pair = sk_x_0040678c();
	sk_x_004075d0(result_pair.lo, result_pair.hi, u4);
	/* tail dispatch: indirect jump, jumptable at 0x003e8ca0 not recovered by Ghidra */
	return;
}

/* FUN_003e9f40 @ 0x003e9f40   (est. sk_capop_003e9f40)
 * Ghidra: void FUN_003e9f40(void)
 * Performs a capability op on the current context: runs a chain of kernel
 * glue calls, invokes an indirect callback (in_x6) whose result object is
 * used to clear a per-request slot byte at +0x30, then builds and releases
 * the op frame. Ends by releasing the op frame and a message-slot value.
 * Confidence: low
 * Notes: uses unaff_x24 as the op-frame base and unaff_x30 as an incoming
 *   slot value; indirect call via in_x6; extraout_x16 vtable dispatch at
 *   +0x20. */
static void
sk_capop_003e9f40(void)
{
	int64_t obj;
	int64_t (*cb)() = 0; /* in_x6: indirect callback */
	uint64_t vbase = 0;  /* extraout_x16 */
	uint8_t *frame = 0;  /* unaff_x24 */
	uint64_t slot_in = 0; /* unaff_x30 */

	sk_x_00084220();
	sk_x_0034bb84();
	sk_x_00407450();
	obj = (int64_t)cb();
	*(uint8_t *)(frame + *(int32_t *)(obj + 0x30)) = 0;
	sk_x_0040654c();
	sk_x_00350968();
	sk_x_00377824();
	sk_x_00349530();
	((void (*)(void))(*(uint64_t *)(vbase + 0x20)))();
	sk_x_00407ea0((int64_t)*(int32_t *)(obj + 0x2c));
	sk_x_00084234(slot_in);
	return;
}

/* FUN_003ead6c @ 0x003ead6c   (est. sk_capop_003ead6c)
 * Ghidra: void FUN_003ead6c(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,undefined8 param_5)
 * Builds a new op frame for a capability invocation: allocates an op frame
 * via the frame allocator using a size from global sk_g_005a00dc, seeds it
 * with the running op context and a vtable/continuation at slot [1], then
 * hands it to the in-slice dispatcher sk_capop_003ea5a8 along with the five
 * invocation arguments. The op context is the running context (unaff_x22).
 * Confidence: low
 * Notes: DAT_005a00dc supplies the op-frame size; continuation is the
 *   in-slice function sk_capop_003eae24. */
static void
sk_capop_003ead6c(uint64_t arg1, uint64_t arg2, uint64_t arg3, uint64_t arg4,
                  uint64_t arg5)
{
	int64_t *frame;
	uint8_t *ctx = /* unaff_x22: current op context */ 0;

	*(uint64_t *)(ctx + 0x10) = arg4;
	frame = (int64_t *)sk_x_0040bb18(sk_g_005a00dc);
	*(int64_t **)(ctx + 0x18) = frame;
	frame[0] = (int64_t)ctx;
	frame[1] = (int64_t)sk_capop_003eae24;
	sk_capop_003ea5a8(frame, arg1, arg2, arg3, arg5);
	return;
}

/* FUN_003eb594 @ 0x003eb594   (est. sk_capop_003eb594)
 * Ghidra: void FUN_003eb594(void)
 * Runs a capability operation keyed off the op-frame flag at +0x98: if set,
 * the request is pushed through the metadata path at +0x80, otherwise a
 * different request builder is used. The resulting 16-byte pair is handed to
 * a resolver, then the op frame is released and dispatched onward.
 * Confidence: low
 * Notes: unrecovered jumptable at 0x003eb618 (too many branches);
 *   extraout_x9 provides an indirect callback; uses op-frame release
 *   0040bd24 and 0040678c. */
static void
sk_capop_003eb594(void)
{
	cl4_result_t result; /* auVar2 */
	uint64_t (*req_fn)(void) = 0; /* extraout_x9 */
	void (*req_fn_00)(void) = 0; /* extraout_x9_00 */
	uint8_t *ctx = /* unaff_x22: current op context */ 0;

	sk_x_00407000();
	if (*(char *)(ctx + 0x98) == '\x01') {
		sk_x_00407d14(*(uint64_t *)(ctx + 0x80));
		result.lo = (uint64_t)req_fn();
		result.hi = 0;
	} else {
		sk_x_00408280();
		req_fn_00();
		result = sk_x_00408354();
	}
	sk_x_004069b0(result.lo, result.hi);
	sk_x_004070a0();
	sk_x_0040bd24();
	sk_x_0040678c();
	/* tail dispatch: indirect jump, jumptable at 0x003eb618 not recovered by Ghidra */
	return;
}

/* FUN_003ec098 @ 0x003ec098   (est. sk_capop_003ec098)
 * Ghidra: void FUN_003ec098(void)
 * Initializes a global capability/object registry entry by asking the
 * out-of-slice constructor sk_x_0036a9d4 to build an object from the two
 * constant metadata addresses and storing the result into the global at
 * sk_g_006adf30.
 * Confidence: low
 * Notes: the decompiler warns that globals starting with '_' overlap smaller
 *   symbols at the same address; _DAT_006adf30 -> sk_g_006adf30. */
static void
sk_capop_003ec098(void)
{
	sk_g_006adf30 = sk_x_0036a9d4(0x6578a0, 0x6c0b68);
	return;
}

/* FUN_003ec598 @ 0x003ec598   (est. sk_capop_003ec598)
 * Ghidra: void FUN_003ec598(void)
 * Executes a capability operation on the current op context: runs the common
 * prologue, invokes a three-slot setup with the op-frame words at +0x20/+0x28
 * and +0x30, then resolves a 16-byte pair and finishes through the release
 * epilogue before an unrecovered indirect tail dispatch.
 * Confidence: low
 * Notes: unrecovered jumptable at 0x003ec5f4 (too many branches);
 *   auVar1 is the 16-byte pair result. */
static void
sk_capop_003ec598(void)
{
	cl4_result_t result; /* auVar1 */
	uint8_t *ctx = /* unaff_x22: current op context */ 0;

	sk_x_00407000();
	sk_x_0031dc0c(0, *(uint64_t *)(ctx + 0x20), *(uint64_t *)(ctx + 0x28),
	              *(uint64_t *)(ctx + 0x30));
	result = sk_x_0035a7e8();
	sk_x_00369340(result.lo, result.hi, 0);
	sk_x_00407128();
	/* tail dispatch: indirect jump, jumptable at 0x003ec5f4 not recovered by Ghidra */
	return;
}

/* FUN_003ec874 @ 0x003ec874   (est. sk_capop_003ec874)
 * Ghidra: void FUN_003ec874(void)
 * Runs a terminal error/abort path for a capability op: invokes the two
 * kernel abort helpers and then traps into a breakpoint. The decompiler
 * reports that this path does not return; the breakpoint handler receives the
 * fault location and the resulting code pointer is called (unreachable).
 * Confidence: low
 * Notes: SoftwareBreakpoint(1, 0x3ec89c) is the trap intrinsic; the function
 *   is marked noreturn. */
static void
sk_capop_003ec874(void)
{
	void (*bp_fn)(); /* pcVar1 */

	sk_x_00407030();
	sk_x_00406490();
	/* does not return */
	bp_fn = (void (*)())SoftwareBreakpoint(1, 0x3ec89c);
	bp_fn();
}

/* FUN_003ecc18 @ 0x003ecc18   (est. sk_capop_003ecc18)
 * Ghidra: ulong FUN_003ecc18(void)
 * Resolves a capability/object value. If a cached object handle is found it
 * is re-registered and its refcount revalidated through the out-of-slice
 * helpers. Otherwise a fresh lookup returns a value that is range-checked:
 * values in [0, 0x100) are accepted, and anything else triggers a failure
 * path that reports and faults. A negative result also faults.
 * Confidence: low
 * Notes: the failure branch ends in sk_x_001afe4c which the decompiler marks
 *   as not returning. */
static uint64_t
sk_capop_003ecc18(void)
{
	int64_t handle;
	uint64_t value;

	handle = sk_x_0040880c();
	if (handle != 0) {
		sk_x_0036b270();
		value = sk_x_00409c10();
		sk_x_0036b118(handle);
		return value;
	}
	value = sk_x_00408898();
	if ((int64_t)value < 0) {
		sk_x_003488bc(1);
		sk_x_00349a54();
	} else {
		if (value < 0x100) {
			return value;
		}
		sk_x_003488bc(1);
		sk_x_00349a54();
	}
	/* subroutine does not return */
	sk_x_001afe4c();
	return 0; /* not reached */
}

/* FUN_003ed2dc @ 0x003ed2dc   (est. sk_capop_003ed2dc)
 * Ghidra: void FUN_003ed2dc(undefined8 param_1,undefined8 param_2,undefined8 param_3)
 * Records the three invocation arguments into stack spill slots and then
 * delegates to the in-slice dispatcher sk_capop_003ed1a4 with a registry key
 * (address of global sk_g_005a0138), two 16-byte scratch buffers, a callback
 * (out-of-slice sk_x_003fd25c) and the third argument duplicated as the final
 * two parameters.
 * Confidence: low
 * Notes: the assigned locals local_50/local_30/uStack_28/local_20 are
 *   decompiler stack-spill artifacts; auStack_40 and auStack_60 are passed
 *   by address; &DAT_005a0138 -> &sk_g_005a0138. */
static void
sk_capop_003ed2dc(uint64_t arg1, uint64_t arg2, uint64_t arg3)
{
	uint8_t stack60[16]; /* auStack_60 */
	uint64_t local50;    /* local_50 */
	uint8_t stack40[16]; /* auStack_40 */
	uint64_t local30;    /* local_30 */
	uint64_t stack28;    /* uStack_28 */
	uint64_t local20;    /* local_20 */

	local50 = arg3;
	local30 = arg3;
	stack28 = arg1;
	local20 = arg2;
	sk_capop_003ed1a4(&sk_g_005a0138, stack40, sk_x_003fd25c, stack60, arg3, arg3);
	return;
}

/* FUN_003ee310 @ 0x003ee310   (est. sk_capop_003ee310)
 * Ghidra: void FUN_003ee310(void)
 * Looks up a cached object handle; if present it re-registers and inspects a
 * status bit. When bit 0 of the returned value is set, it runs the two
 * out-of-slice reconstruction helpers against the constant metadata
 * addresses to rebuild the associated object state.
 * Confidence: low
 * Notes: uses the registry helpers 0040880c/0036b270/0036b118 and the
 *   rebuild trio 0035187c/0036993c/0036986c. */
static void
sk_capop_003ee310(void)
{
	int64_t handle;
	uint64_t value;

	handle = sk_x_0040880c();
	if (handle != 0) {
		sk_x_0036b270();
		value = sk_x_0040a688();
		sk_x_0036b118(handle);
		if ((value & 1) != 0) {
			sk_x_0035187c(0x67e930, 0x67db20);
			sk_x_0036993c();
			sk_x_0036986c();
		}
	}
	return;
}

/* FUN_003eebf0 @ 0x003eebf0   (est. sk_capop_003eebf0)
 * Ghidra: void FUN_003eebf0(void)
 * Runs the tail of a capability operation: executes the common prologue and
 * epilogue glue, releases the object referenced at +0x10 of the extraout
 * base, and finishes with an unrecovered indirect tail dispatch back into the
 * op loop.
 * Confidence: low
 * Notes: unrecovered jumptable at 0x003eec88 (too many branches); uses
 *   extraout_x8 as a frame base for the release call. */
static void
sk_capop_003eebf0(void)
{
	uint64_t frame = 0; /* extraout_x8 */

	sk_x_00407000();
	sk_x_00407018();
	sk_x_0040bd24(*(uint64_t *)(frame + 0x10));
	sk_x_00407128();
	/* tail dispatch: indirect jump, jumptable at 0x003eec88 not recovered by Ghidra */
	return;
}

/* FUN_003e6ecc @ 0x003e6ecc   (est. sk_capop_003e6ecc)
 * Ghidra: void FUN_003e6ecc(long param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                 code *param_9)
 * Builds a per-invocation op frame: it first invokes the op-frame callback
 * (param_9) with the message slot vector (param_5..param_8) to obtain the frame
 * base, then uses the frame's offset fields to publish capability words and zero
 * a field. Two type descriptors are pushed (via the descriptor-register helpers)
 * and the final capability pair is stored into the frame's argument slot before
 * the op completes.
 * Confidence: low
 * Notes: extraout_x16 is an implicit register (x16) continuation used as the
 *   base of an indirect vtable dispatch at +0x20. DAT_00614a5c is a tag/string
 *   constant passed by address to both descriptor pushes. */
static void sk_capop_003e6ecc(long param_1, uint64_t param_2, uint64_t param_3, uint64_t param_4,
                 uint64_t param_5, uint64_t param_6, uint64_t param_7, uint64_t param_8,
                 uint64_t (*param_9)(uint64_t, uint64_t *))
{
    uint64_t *slot;             /* puVar1 */
    int off38;                  /* iVar2 */
    long frame;                 /* lVar3 */
    uint64_t tail_x16 = 0;      /* extraout_x16 */
    cl4_result_t pair;          /* auVar4 */
    uint64_t msg_a;             /* uStack_80 */
    uint64_t msg_b;             /* local_78 */
    uint64_t msg_c;             /* uStack_70 */
    uint64_t msg_d;             /* local_68 */

    msg_a = param_5;
    msg_b = param_6;
    msg_c = param_7;
    msg_d = param_8;
    frame = (*param_9)(0, &msg_a);
    off38 = *(int *)(frame + 0x38);
    pair = sk_x_00350500();
    sk_x_00377824(pair.lo, pair.hi, param_6, &sk_g_00614a5c);
    sk_x_00350744(param_1 + off38);
    sk_x_000839d8();
    *(uint8_t *)(param_1 + *(int *)(frame + 0x3c)) = 0;
    pair = sk_x_0035050c();
    sk_x_00377824(pair.lo, pair.hi, param_5, &sk_g_00614a5c);
    sk_x_00349530();
    ((void (*)(uint64_t, uint64_t))(*(uint64_t *)(tail_x16 + 0x20)))(param_1, param_2);
    slot = (uint64_t *)(param_1 + *(int *)(frame + 0x34));
    *slot = param_3;
    slot[1] = param_4;
    return;
}

/* FUN_003e8e28 @ 0x003e8e28   (est. sk_capop_003e8e28)
 * Ghidra: void FUN_003e8e28(void)
 * Drives the current op context to completion. On the success path it engages a
 * per-op reply handler, releases the run of op-frame buffers captured on the
 * stack, and re-arms the reply/message slot before tail-dispatching. On the
 * non-success path it re-invokes a wait/rearm sequence through the context's
 * saved slots and funnels through the op-frame allocator, seeding a new frame
 * that tails through the unrecovered dispatch table.
 * Confidence: low
 * Notes: unaff_x22 is the running op context. The in_ZR condition (zero-flag of
 *   the preceding call) is unknowable; both branches are preserved. Jumptables
 *   at 0x003e8f20 and 0x003e8fc0 were not recovered by Ghidra; extraout_x9 /
 *   extraout_x9_00 / extraout_x16 are implicit register continuations, and
 *   LAB_003e8fc4 is an inline code label stored as a word. */
static void sk_capop_003e8e28(void)
{
    uint64_t saved;             /* uVar3 */
    uint64_t poll;              /* uVar4 */
    uint64_t stored_a;          /* uVar7 */
    uint64_t stored_b;          /* uVar6 */
    uint64_t base_a;            /* lVar1 */
    uint64_t base_b;            /* lVar2 */
    uint64_t *newframe;         /* puVar5 */
    uint64_t tail_x8 = 0;       /* extraout_x8 */
    uint64_t tail_x9 = 0;       /* extraout_x9 */
    uint64_t tail_x9b = 0;      /* extraout_x9_00 */
    uint64_t tail_x16 = 0;      /* extraout_x16 */
    uint64_t seed = 0;          /* extraout_x17 */
    uint64_t stack_0;           /* in_stack_00000000 */
    uint64_t stack_1;           /* in_stack_00000008 */
    uint64_t stack_2;           /* in_stack_00000010 */
    uint64_t stack_3;           /* in_stack_00000018 */
    uint64_t stack_4;           /* in_stack_00000020 */
    uint64_t stack_5;           /* in_stack_00000028 */
    uint64_t stack_6;           /* in_stack_00000030 */
    uint8_t *ctx = 0;           /* unaff_x22: current op context */
    cl4_result_t pair;          /* auVar8 */

    saved = sk_x_00407afc();
    sk_x_00407f60();
    stored_a = *(uint64_t *)(ctx + 0xa0);
    stored_b = *(uint64_t *)(ctx + 0x88);
    poll = sk_x_00406420();
    if (0 /* in_ZR */) {
        sk_x_0040711c(*(uint64_t *)(ctx + 0x98), poll, *(uint64_t *)(ctx + 0x90));
        ((void (*)(void))tail_x9)();        /* tail_x9: implicit register tail call */
        sk_x_004066bc();
        sk_x_00350744();
        sk_x_000839d8();
        sk_x_0040bd24();
        sk_x_0040bd24();
        sk_x_0040bd24();
        sk_x_0040bd24();
        sk_x_0040bd24();
        sk_x_0040bd24(stored_a);
        sk_x_0040bd24(stored_b);
        sk_x_0040bd24();
        sk_x_0040bd24();
        sk_x_0040bd24(stack_0);
        sk_x_0040bd24(stack_1);
        sk_x_0040bd24(stack_2);
        sk_x_0040bd24(stack_3);
        sk_x_0040bd24(stack_4);
        sk_x_0040bd24(stack_5);
        sk_x_0040bd24(stack_6);
        pair = sk_x_0040678c();
        sk_x_004075d0(pair.lo, pair.hi, saved);
        /* tail dispatch: indirect jump, jumptable at 0x003e8f20 not recovered by Ghidra */
        ((void (*)(void))tail_x9b)();       /* UNRECOVERED_JUMPTABLE_00: register-held target */
        return;
    }
    base_a = *(uint64_t *)(ctx + 0x28);
    base_b = *(uint64_t *)(ctx + 0x30);
    sk_x_00406bd4(*(uint64_t *)(ctx + 0xa8), *(uint64_t *)(ctx + 0xb0));
    ((void (*)(void))tail_x9b)();           /* tail_x9b: implicit register tail call */
    sk_x_004062a8(*(uint64_t *)(base_b + *(int *)(base_a + 0x34)));
    sk_x_0040bb18(*(uint32_t *)(tail_x8 + 4));
    newframe = (uint64_t *)sk_x_00406fe0();
    *(uint64_t **)(ctx + 0x1c0) = newframe;
    *newframe = seed;
    newframe[1] = 0x003e8fc4;               /* &LAB_003e8fc4 */
    sk_x_004075d0(*(uint64_t *)(ctx + 0x50), *(uint64_t *)(ctx + 0xb0), tail_x16, saved);
    /* tail dispatch: indirect jump, jumptable at 0x003e8fc0 not recovered by Ghidra */
    return;
}

/* FUN_003e9fcc @ 0x003e9fcc   (est. sk_capop_003e9fcc)
 * Ghidra: void FUN_003e9fcc(void)
 * Seeds the running op context from a freshly built op frame: it records the
 * frame base pair and message words, caches the frame's method/type words at
 * +0x20/+0x30, then resolves and stores the capability/region tokens at
 * +0x40..+0x60. It finishes by re-arming the descriptor table and running the
 * completion helpers.
 * Confidence: low
 * Notes: unaff_x22 is the op context, unaff_x20 an incoming capability word.
 *   extraout_x8 / extraout_x8_00 / extraout_x8_01 are register-passed bases and
 *   extraout_x16 / extraout_x16_00 carry function results used as stored
 *   tokens. */
static void sk_capop_003e9fcc(void)
{
    uint64_t res;               /* uVar1 */
    uint64_t frame_hi;          /* lVar2 */
    uint64_t tail_x8 = 0;       /* extraout_x8 */
    uint64_t base_a = 0;        /* extraout_x8_00 */
    uint64_t base_b = 0;        /* extraout_x8_01 */
    uint64_t out16 = 0;         /* extraout_x16 */
    uint64_t out16b = 0;        /* extraout_x16_00 */
    uint64_t in_arg = 0;        /* unaff_x20 */
    uint8_t *ctx = 0;           /* unaff_x22: current op context */
    cl4_result_t pair;          /* auVar3 */

    pair = sk_x_00407000();
    frame_hi = pair.hi;
    *(uint64_t *)(ctx + 0x18) = frame_hi;
    *(uint64_t *)(ctx + 0x20) = in_arg;
    *(uint64_t *)(ctx + 0x10) = pair.lo;
    *(uint64_t *)(ctx + 0x28) = *(uint64_t *)(frame_hi + 0x20);
    *(uint64_t *)(ctx + 0x30) = *(uint64_t *)(frame_hi + 0x10);
    res = sk_x_004069c4();
    sk_x_00377824(res, tail_x8);
    sk_x_004079a8();
    sk_x_00350798();
    res = sk_x_00310d68();
    *(uint64_t *)(ctx + 0x40) = res;
    sk_x_00352018();
    *(uint64_t *)(ctx + 0x48) = out16;
    res = sk_x_004078e8(*(uint64_t *)(base_a + 0x40));
    *(uint64_t *)(ctx + 0x50) = res;
    sk_x_0040683c();
    *(uint64_t *)(ctx + 0x58) = out16b;
    res = sk_x_004078e8(*(uint64_t *)(base_b + 0x40));
    *(uint64_t *)(ctx + 0x60) = res;
    sk_x_00407594();
    sk_x_00408db8();
    return;
}

/* FUN_003eae24 @ 0x003eae24   (est. sk_capop_003eae24)
 * Ghidra: void FUN_003eae24(void)
 * Advances a capability op: it runs the three op-frame setup steps, stores a
 * register-passed value into a slot located through the op context, and
 * releases one buffered op frame. Depending on an incoming capability word it
 * either publishes it into a second frame slot or skips that publish, then
 * dispatches through the op completion table.
 * Confidence: low
 * Notes: unaff_x20 selects the publish branch. extraout_x8 / extraout_x8_00 are
 *   register-passed bases, extraout_x9 a pointer through which a value is
 *   stored, and extraout_x1 / extraout_x1_00 hold the tail-dispatch targets.
 *   Jumptable at 0x003eaed4 was not recovered by Ghidra. */
static void sk_capop_003eae24(void)
{
    uint64_t tail_a = 0;        /* extraout_x1 */
    uint64_t tail_b = 0;        /* extraout_x1_00 */
    uint64_t tail_target;       /* UNRECOVERED_JUMPTABLE */
    uint64_t base_a = 0;        /* extraout_x8 */
    uint64_t base_b = 0;        /* extraout_x8_00 */
    uint64_t *slotp = 0;        /* extraout_x9 (long *) */
    uint64_t in_arg = 0;        /* unaff_x20 */

    sk_x_00406fd4();
    sk_x_00407018();
    sk_x_0040676c();
    *slotp = base_a;
    sk_x_0040bd24(*(uint64_t *)(base_b + 0x18));
    if (in_arg == 0) {
        sk_x_00407e10();
        tail_target = tail_b;
    } else {
        **(uint64_t **)(base_a + 0x10) = in_arg;
        sk_x_00407e10();
        tail_target = tail_a;
    }
    /* tail dispatch: indirect jump, jumptable at 0x003eaed4 not recovered by Ghidra */
    return;
}

/* FUN_003eb68c @ 0x003eb68c   (est. sk_capop_003eb68c)
 * Ghidra: void FUN_003eb68c(undefined8 param_1,undefined8 param_2,undefined8 param_3,long param_4)
 * Fills the running op context from the given op frame (param_4): it caches the
 * frame's method word, then resolves and stores six capability/region tokens at
 * +0x40..+0x88. Based on an incoming context word it either takes the direct
 * completion path or drives a chained sub-op before publishing the final token
 * and message word at +0x90/+0x98, then runs the completion helpers.
 * Confidence: low
 * Notes: unaff_x22 is the op context, unaff_x21 selects the branch. The many
 *   extraout_x8_* / extraout_x16_* are implicit register results/bases, and
 *   extraout_x8_02 is an implicit register tail call on the chained path. */
static void sk_capop_003eb68c(uint64_t param_1, uint64_t param_2, uint64_t param_3, uint64_t param_4)
{
    uint64_t res;               /* uVar1 */
    uint64_t base_a = 0;        /* extraout_x8 */
    uint64_t base_b = 0;        /* extraout_x8_00 */
    uint64_t base_c = 0;        /* extraout_x8_01 */
    uint64_t tail_x8 = 0;       /* extraout_x8_02 */
    uint64_t res_a = 0;         /* extraout_x8_03 */
    uint64_t res_b = 0;         /* extraout_x8_04 */
    uint64_t out16 = 0;         /* extraout_x16 */
    uint64_t out16b = 0;        /* extraout_x16_00 */
    uint64_t out16c = 0;        /* extraout_x16_01 */
    uint64_t in_flag = 0;       /* unaff_x21 */
    uint8_t *ctx = 0;           /* unaff_x22: current op context */
    (void)param_1;
    (void)param_2;

    sk_x_00407c8c();
    sk_x_0040700c();
    sk_x_00406c1c();
    *(uint64_t *)(ctx + 0x40) = *(uint64_t *)(param_4 + 0x10);
    res = sk_x_0040684c();
    *(uint64_t *)(ctx + 0x48) = res;
    sk_x_00352018();
    *(uint64_t *)(ctx + 0x50) = out16;
    res = sk_x_004078e8(*(uint64_t *)(base_a + 0x40));
    *(uint64_t *)(ctx + 0x58) = res;
    res = sk_x_00406dd0();
    *(uint64_t *)(ctx + 0x60) = res;
    sk_x_00350798();
    res = sk_x_00310d68();
    *(uint64_t *)(ctx + 0x68) = res;
    sk_x_00352018();
    *(uint64_t *)(ctx + 0x70) = out16b;
    res = sk_x_004078e8(*(uint64_t *)(base_b + 0x40));
    *(uint64_t *)(ctx + 0x78) = res;
    sk_x_0040683c();
    *(uint64_t *)(ctx + 0x80) = out16c;
    res = sk_x_004078e8(*(uint64_t *)(base_c + 0x40));
    *(uint64_t *)(ctx + 0x88) = res;
    if (in_flag == 0) {
        sk_x_00407248();
        res = res_b;
    } else {
        sk_x_00406590();
        ((void (*)(void))tail_x8)();        /* tail_x8: implicit register tail call */
        sk_x_0008e1ec();
        res = res_a;
    }
    *(uint64_t *)(ctx + 0x90) = res;
    *(uint64_t *)(ctx + 0x98) = param_3;
    sk_x_00353080();
    sk_x_00407c78();
    sk_x_00408db8();
    return;
}

/* FUN_003ec0c4 @ 0x003ec0c4   (est. sk_capop_003ec0c4)
 * Ghidra: undefined1 * FUN_003ec0c4(void)
 * One-time lazy registration of a capability descriptor table: if the global
 * init sentinel is not yet armed it passes the sentinel and the in-slice
 * initializer callback to the registration helper, then returns a pointer to
 * the descriptor table.
 * Confidence: low
 * Notes: DAT_006c0b58 is a once-sentinel global (compared and passed by
 *   address); DAT_006adf30 is the returned descriptor table; FUN_003ec094 is an
 *   in-slice initializer used as a callback. */
static uint8_t *sk_capop_003ec0c4(void)
{
    if (sk_g_006c0b58 != -1) {
        sk_x_0039a128(&sk_g_006c0b58, sk_capop_003ec094);
    }
    return &sk_g_006adf30;
}

/* FUN_003ec6c8 @ 0x003ec6c8   (est. sk_capop_003ec6c8)
 * Ghidra: void FUN_003ec6c8(void)
 * A three-step op-frame teardown/finalize: it runs the op-frame release, a
 * per-context state re-arm, and the completion helper in order, then returns.
 * Confidence: low
 * Notes: No data is read from or written to a live context in this body; all
 *   three callees are out-of-slice helpers. */
static void sk_capop_003ec6c8(void)
{
    sk_x_00406fd4();
    sk_x_00407030();
    sk_x_00406490();
    return;
}

/* FUN_003ec8a0 @ 0x003ec8a0   (est. sk_capop_003ec8a0)
 * Ghidra: void FUN_003ec8a0(undefined8 param_1,undefined8 param_2)
 * Forwards a single argument to the out-of-slice capability/operation helper
 * and returns. The first parameter is unused by the body.
 * Confidence: low
 * Notes: thunk_FUN_002298d4 is an out-of-slice thunk. */
static void sk_capop_003ec8a0(uint64_t param_1, uint64_t param_2)
{
    (void)param_1;
    sk_x_002298d4(param_2);
    return;
}

/* FUN_003eccc4 @ 0x003eccc4   (est. sk_capop_003eccc4)
 * Ghidra: void FUN_003eccc4(void)
 * Polls for a pending object via the lookup helper: if none is returned it
 * immediately runs the completion callback; otherwise it acquires the object,
 * runs the completion callback with the poll result, and releases it through
 * the object release helper. All branches end through the register-held
 * continuation.
 * Confidence: low
 * Notes: unaff_x19 is an implicit register-held callback/continuation called
 *   with the extraout_x8 result; the object-acquire and object-release steps
 *   are out-of-slice helpers. */
static void sk_capop_003eccc4(void)
{
    uint64_t obj;               /* lVar1 */
    uint64_t res = 0;           /* extraout_x8 */
    uint64_t cont = 0;          /* unaff_x19 (code *) */

    sk_x_00350c5c();
    obj = sk_x_0040880c();
    if (obj == 0) {
        ((void (*)(uint64_t))cont)(res);    /* cont: implicit register call */
    } else {
        sk_x_0036b270();
        ((void (*)(uint64_t))cont)(res);    /* cont: implicit register call */
        sk_x_0036b118(obj);
    }
    return;
}

/* FUN_003ed340 @ 0x003ed340   (est. sk_capop_003ed340)
 * Ghidra: void FUN_003ed340(void)
 * Rebuilds an op frame around the running context: it records the frame base
 * and the register-passed argument (in_x3), reads the parent capability word
 * behind it, and resolves and stores the capability token at +0x28. It then
 * allocates a fresh op frame, links it into the context at +0x30, and tails
 * through the dispatch table.
 * Confidence: low
 * Notes: unaff_x22 is the op context; in_x3 is a register-passed argument used
 *   as a pointer base. extraout_x17 is an implicit register result seeded into
 *   the new frame. Jumptable at 0x003ed414 was not recovered by Ghidra. */
static void sk_capop_003ed340(void)
{
    uint64_t res;               /* uVar1 */
    uint64_t *newframe;         /* puVar2 */
    uint64_t in_arg3 = 0;       /* in_x3 */
    uint64_t capword;           /* lVar3 */
    uint64_t seed = 0;          /* extraout_x17 */
    uint8_t *ctx = 0;           /* unaff_x22: current op context */
    cl4_result_t pair;          /* auVar4 */

    pair = sk_x_00406fd4();
    *(uint64_t *)(ctx + 0x10) = pair.lo;
    *(uint64_t *)(ctx + 0x18) = in_arg3;
    capword = *(uint64_t *)(in_arg3 + -8);
    *(uint64_t *)(ctx + 0x20) = capword;
    res = sk_x_004078e8(*(uint64_t *)(capword + 0x40));
    *(uint64_t *)(ctx + 0x28) = res;
    sk_x_00407280();
    sk_x_0040bb18(*(uint32_t *)(pair.hi + 4));
    newframe = (uint64_t *)sk_x_00406fe0();
    *(uint64_t **)(ctx + 0x30) = newframe;
    *newframe = seed;
    sk_x_0040838c();
    /* tail dispatch: indirect jump, jumptable at 0x003ed414 not recovered by Ghidra */
    return;
}

/* FUN_003ee3c8 @ 0x003ee3c8   (est. sk_capop_003ee3c8)
 * Ghidra: void FUN_003ee3c8(void)
 * Seeds the running op context from a fresh op frame: it records the frame base
 * pair, caches the frame's method word at +0x20, resolves and stores three
 * capability/region tokens at +0x28..+0x38, links a freshly allocated frame at
 * +0x40, and finishes through the per-context and completion helpers.
 * Confidence: low
 * Notes: unaff_x22 is the op context, unaff_x20 an incoming capability word
 *   stored at +0x18. extraout_x8 is a register-passed base, and extraout_x16 /
 *   extraout_x17 are implicit register results (one stored as a token, one
 *   seeded into the new frame). */
static void sk_capop_003ee3c8(void)
{
    uint64_t frame;             /* lVar1 */
    uint64_t res;               /* uVar2 */
    uint64_t *newframe;         /* puVar3 */
    uint64_t base = 0;          /* extraout_x8 */
    uint64_t out16 = 0;         /* extraout_x16 */
    uint64_t seed = 0;          /* extraout_x17 */
    uint64_t in_arg = 0;        /* unaff_x20 */
    uint8_t *ctx = 0;           /* unaff_x22: current op context */

    frame = sk_x_00407000();
    *(uint64_t *)(ctx + 0x10) = frame;
    *(uint64_t *)(ctx + 0x18) = in_arg;
    *(uint64_t *)(ctx + 0x20) = *(uint64_t *)(frame + 0x10);
    res = sk_x_00310d68(0);
    *(uint64_t *)(ctx + 0x28) = res;
    sk_x_00352018();
    *(uint64_t *)(ctx + 0x30) = out16;
    res = sk_x_004078e8(*(uint64_t *)(base + 0x40));
    *(uint64_t *)(ctx + 0x38) = res;
    sk_x_00408094();
    newframe = (uint64_t *)sk_x_00406fe0();
    *(uint64_t **)(ctx + 0x40) = newframe;
    *newframe = seed;
    sk_x_004071d0();
    sk_x_003ef544();
    return;
}

/* FUN_003eec90 @ 0x003eec90   (est. sk_capop_003eec90)
 * Ghidra: void FUN_003eec90(undefined8 param_1,undefined8 param_2,undefined8 param_3,long param_4,
                 undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8)
 * Publishes a capability-op invocation into the running op context: it records
 * the frame base and the message words at +0x118..+0x130. Depending on param_4
 * it either takes the direct path or drives a chained sub-op (with param_5)
 * before publishing the final token and message word at +0x138/+0x140, then
 * runs the completion helpers.
 * Confidence: low
 * Notes: unaff_x22 is the op context. extraout_x8_01 / extraout_x8_00 are
 *   implicit register results selected by the branch, and extraout_x8 is an
 *   implicit register tail call on the chained path. */
static void sk_capop_003eec90(uint64_t param_1, uint64_t param_2, uint64_t param_3, uint64_t param_4,
                 uint64_t param_5, uint64_t param_6, uint64_t param_7, uint64_t param_8)
{
    uint64_t res;               /* uVar1 */
    uint64_t tail_x8 = 0;       /* extraout_x8 */
    uint64_t res_a = 0;         /* extraout_x8_00 */
    uint64_t res_b = 0;         /* extraout_x8_01 */
    uint8_t *ctx = 0;           /* unaff_x22: current op context */
    (void)param_1;
    (void)param_2;

    res = sk_x_00406fd4();
    *(uint64_t *)(ctx + 0x128) = param_7;
    *(uint64_t *)(ctx + 0x130) = param_8;
    *(uint64_t *)(ctx + 0x118) = res;
    *(uint64_t *)(ctx + 0x120) = param_6;
    if (param_4 == 0) {
        sk_x_00407248();
        res = res_b;
    } else {
        sk_x_00351da8();
        sk_x_003d4658(param_5);
        sk_x_0034bcf0();
        ((void (*)(void))tail_x8)();        /* tail_x8: implicit register tail call */
        sk_x_0008e1ec();
        res = res_a;
    }
    *(uint64_t *)(ctx + 0x138) = res;
    *(uint64_t *)(ctx + 0x140) = param_3;
    sk_x_00353080();
    sk_x_00408db8();
    return;
}

/* FUN_003e6fc8 @ 0x003e6fc8   (est. sk_capop_003e6fc8)
 * Ghidra: void FUN_003e6fc8(void)
 * Capability-invocation entry that seeds a fresh per-invocation op frame from
 * the running operation context (unaff_x22): it releases/allocates several
 * aligned op-frame buffers and stores a sequence of capability/object handles
 * (op descriptor, reply slot, message fields) at fixed offsets of the frame.
 * Each call either pushes a resolved object pointer into the frame or drives a
 * sub-invocation helper; the frame is then left ready for the tail dispatch
 * that completes the operation. Side effects are confined to the op frame and
 * the referenced kernel objects.
 * Confidence: low
 * Notes: heavy extraout_x1/x8/x16 register-artifact usage (each kept as a
 *   local); all callees are out-of-slice and mapped to sk_x_. */
static void sk_capop_003e6fc8(void)
{
    uint64_t uVar1;
    uint64_t uVar2;
    uint64_t extraout_x1 = 0;   /* Ghidra extraout_x1 */
    uint64_t extraout_x8 = 0;   /* Ghidra extraout_x8 */
    uint64_t extraout_x8_00 = 0;/* Ghidra extraout_x8_00 */
    uint64_t extraout_x8_01 = 0;/* Ghidra extraout_x8_01 */
    uint64_t extraout_x8_02 = 0;/* Ghidra extraout_x8_02 */
    uint64_t extraout_x8_03 = 0;/* Ghidra extraout_x8_03 */
    uint64_t extraout_x8_04 = 0;/* Ghidra extraout_x8_04 */
    uint64_t extraout_x8_05 = 0;/* Ghidra extraout_x8_05 */
    uint64_t extraout_x16 = 0;  /* Ghidra extraout_x16 */
    uint64_t extraout_x16_00 = 0;/* Ghidra extraout_x16_00 */
    uint64_t extraout_x16_01 = 0;/* Ghidra extraout_x16_01 */
    uint64_t extraout_x16_02 = 0;/* Ghidra extraout_x16_02 */
    uint64_t extraout_x16_03 = 0;/* Ghidra extraout_x16_03 */
    uint64_t extraout_x16_04 = 0;/* Ghidra extraout_x16_04 */
    uint64_t extraout_x16_05 = 0;/* Ghidra extraout_x16_05 */
    uint64_t unaff_x24 = 0;     /* Ghidra unaff_x24 */
    uint8_t *ctx = 0;           /* unaff_x22: current op context */

    sk_x_00407c8c();
    sk_x_0040700c();
    sk_x_00407214();
    sk_x_0007c028();
    *(uint64_t *)(ctx + 0x30) = extraout_x16;
    uVar2 = *(uint64_t *)(extraout_x8 + 0x40) + 0xf;
    uVar1 = sk_x_0040bb18(uVar2 & 0xfffffffffffffff0);
    *(uint64_t *)(ctx + 0x38) = uVar1;
    uVar1 = sk_x_0040bb18(uVar2 & 0xfffffffffffffff0);
    *(uint64_t *)(ctx + 0x40) = uVar1;
    uVar1 = sk_x_0040bb18(uVar2 & 0xfffffffffffffff0);
    *(uint64_t *)(ctx + 0x48) = uVar1;
    *(uint64_t *)(ctx + 0x50) = *(uint64_t *)(extraout_x1 + 0x20);
    *(uint64_t *)(ctx + 0x58) = *(uint64_t *)(extraout_x1 + 0x10);
    uVar1 = sk_x_0040807c();
    *(uint64_t *)(ctx + 0x60) = uVar1;
    sk_x_00350500();
    uVar1 = sk_x_00310d68();
    *(uint64_t *)(ctx + 0x68) = uVar1;
    sk_x_00352018();
    *(uint64_t *)(ctx + 0x70) = extraout_x16_00;
    uVar1 = sk_x_004078e8(*(uint64_t *)(extraout_x8_00 + 0x40));
    *(uint64_t *)(ctx + 0x78) = uVar1;
    sk_x_00406f50();
    *(uint64_t *)(ctx + 0x80) = extraout_x16_01;
    uVar1 = sk_x_004078e8(*(uint64_t *)(extraout_x8_01 + 0x40));
    *(uint64_t *)(ctx + 0x88) = uVar1;
    *(uint64_t *)(ctx + 0x90) = *(uint64_t *)(extraout_x1 + 0x28);
    sk_x_00350548(0xff);
    uVar1 = sk_x_00377824();
    *(uint64_t *)(ctx + 0x98) = uVar1;
    sk_x_00350500();
    uVar1 = sk_x_00310d68();
    *(uint64_t *)(ctx + 0xa0) = uVar1;
    sk_x_00352018();
    *(uint64_t *)(ctx + 0xa8) = extraout_x16_02;
    uVar1 = sk_x_004081b4(*(uint64_t *)(extraout_x8_02 + 0x40));
    *(uint64_t *)(ctx + 0xb0) = uVar1;
    uVar1 = sk_x_0040bb18(unaff_x24 & 0xfffffffffffffff0);
    *(uint64_t *)(ctx + 0xb8) = uVar1;
    sk_x_00406f50();
    *(uint64_t *)(ctx + 0xc0) = extraout_x16_03;
    uVar2 = *(uint64_t *)(extraout_x8_03 + 0x40) + 0xf;
    uVar1 = sk_x_0040bb18(uVar2 & 0xfffffffffffffff0);
    *(uint64_t *)(ctx + 200) = uVar1;
    uVar1 = sk_x_0040bb18(uVar2 & 0xfffffffffffffff0);
    *(uint64_t *)(ctx + 0xd0) = uVar1;
    sk_x_00350548(0xff);
    uVar2 = sk_x_00377824();
    *(uint64_t *)(ctx + 0xd8) = uVar2;
    sk_x_00350798();
    uVar1 = sk_x_00310d68();
    *(uint64_t *)(ctx + 0xe0) = uVar1;
    sk_x_00352018();
    *(uint64_t *)(ctx + 0xe8) = extraout_x16_04;
    uVar1 = sk_x_004078e8(*(uint64_t *)(extraout_x8_04 + 0x40));
    *(uint64_t *)(ctx + 0xf0) = uVar1;
    sk_x_0040683c();
    *(uint64_t *)(ctx + 0xf8) = extraout_x16_05;
    uVar1 = sk_x_00407b48(*(uint64_t *)(extraout_x8_05 + 0x40));
    *(uint64_t *)(ctx + 0x100) = uVar1;
    uVar1 = sk_x_0040bb18(uVar2 & 0xfffffffffffffff0);
    *(uint64_t *)(ctx + 0x108) = uVar1;
    sk_x_00407594();
    sk_x_00407c78();
    sk_x_00408db8();
    return;
}

/* FUN_003e90f4 @ 0x003e90f4   (est. sk_capop_003e90f4)
 * Ghidra: void FUN_003e90f4(void)
 * Capability-invocation op-frame builder. It pulls capability, reply-slot and
 * message-slot handles out of the running op context (unaff_x22), packs the
 * lo/hi halves of several helpers' 16-byte results into the reply/message
 * slots, allocates a fresh op-frame buffer and a vtable-pair object, then
 * performs a tail dispatch to the recovered indirect jump. The final branch
 * cannot be resolved by Ghidra (too many jumptable branches).
 * Confidence: low
 * Notes: unrecovered jumptable at 0x003e9220; LAB_003e9224 referenced as a
 *   vtable/return address; extraout_x8/x9/x9_00 are function pointers. */
static void sk_capop_003e90f4(void)
{
    uint64_t uVar1;
    uint64_t lVar2;
    uint64_t *puVar3;
    void (*extraout_x8)(uint64_t, uint64_t, uint64_t) = 0;   /* Ghidra extraout_x8 */
    void (*extraout_x9)(uint64_t, uint64_t, uint64_t) = 0;   /* Ghidra extraout_x9 */
    void (*extraout_x9_00)(uint64_t, uint64_t) = 0;          /* Ghidra extraout_x9_00 */
    uint64_t extraout_x17 = 0;  /* Ghidra extraout_x17 */
    uint64_t uVar4;
    uint64_t uVar5;
    uint64_t uVar6;
    uint8_t *ctx = 0;           /* unaff_x22: current op context */
    cl4_result_t auVar7;

    sk_x_004079cc();
    uVar1 = sk_x_004070d8();
    uVar4 = *(uint64_t *)(ctx + 0x128);
    uVar5 = *(uint64_t *)(ctx + 0xb8);
    lVar2 = *(uint64_t *)(ctx + 0x40);
    uVar6 = *(uint64_t *)(ctx + 0x38);
    auVar7 = sk_x_00407ce4(uVar1, *(uint64_t *)(ctx + 0x50));
    (*extraout_x9)(auVar7.lo, auVar7.hi, uVar6);
    auVar7 = sk_x_00350518(*(uint64_t *)(lVar2 + 0x10));
    (*extraout_x8)(auVar7.lo, auVar7.hi, uVar6);
    sk_x_004070e4(uVar5);
    (*extraout_x9_00)(uVar6, uVar5);
    sk_x_004068bc();
    uVar1 = sk_x_00377bec(uVar5, uVar6, uVar4);
    *(uint64_t *)(ctx + 0x1d0) = uVar1;
    sk_x_003fcc4c();
    lVar2 = sk_x_00406374();
    sk_x_0040bb18(*(uint32_t *)(lVar2 + 4));
    puVar3 = (uint64_t *)sk_x_00406fe0();
    *(uint64_t **)(ctx + 0x1d8) = puVar3;
    *puVar3 = extraout_x17;
    puVar3[1] = 0x003e9224;     /* LAB_003e9224 */
    sk_x_00407990(*(uint64_t *)(ctx + 0xd8), *(uint64_t *)(ctx + 0x18),
                  *(uint64_t *)(ctx + 0x20), *(uint64_t *)(ctx + 0x110),
                  *(uint64_t *)(ctx + 0x128));
    sk_x_004078f4();
    /* tail dispatch: indirect jump, jumptable at 0x003e9220 not recovered by Ghidra */
    return;
}

/* FUN_003ea0a4 @ 0x003ea0a4   (est. sk_capop_003ea0a4)
 * Ghidra: void FUN_003ea0a4(void)
 * Capability-invocation handler that branches on a capability-index bit: when
 * the indexed capability is flagged, it releases the op frame and routes to
 * the tail-dispatch jumptable; otherwise it builds a fresh op-frame buffer and
 * vtable-pair object and again tail-dispatches. Both indirect branches are
 * unrecovered by Ghidra.
 * Confidence: low
 * Notes: unrecovered jumptables at 0x003ea118 and 0x003ea1a0; extraout_x17
 *   kept as a local; all callees out-of-slice. */
static void sk_capop_003ea0a4(void)
{
    uint64_t lVar1;
    int iVar2;
    uint64_t uVar3;
    uint64_t *puVar4;
    uint64_t extraout_x17 = 0;  /* Ghidra extraout_x17 */
    uint8_t *ctx = 0;           /* unaff_x22: current op context */
    cl4_result_t auVar5;

    uVar3 = sk_x_00407ca0();
    sk_x_0040700c();
    iVar2 = *(int *)(*(uint64_t *)(ctx + 0x18) + 0x30);
    *(int *)(ctx + 0x88) = iVar2;
    if ((*(uint8_t *)(*(uint64_t *)(ctx + 0x20) + (int64_t)iVar2) & 1) != 0) {
        sk_x_00407604();
        sk_x_00406c5c(*(uint64_t *)(ctx + 0x10));
        sk_x_0040bd24();
        auVar5 = sk_x_0040678c();
        sk_x_00407e58(auVar5.lo, auVar5.hi, uVar3);
        /* tail dispatch: indirect jump, jumptable at 0x003ea118 not recovered by Ghidra */
        return;
    }
    lVar1 = *(uint64_t *)(ctx + 0x30);
    sk_x_0040652c();
    sk_x_00406608();
    sk_x_004068f4();
    sk_x_00406268();
    sk_x_0040bb18(*(uint32_t *)(lVar1 + 4));
    puVar4 = (uint64_t *)sk_x_00406fe0();
    *(uint64_t **)(ctx + 0x68) = puVar4;
    *puVar4 = extraout_x17;
    sk_x_004074c4();
    sk_x_00406ab4();
    /* tail dispatch: indirect jump, jumptable at 0x003ea1a0 not recovered by Ghidra */
    return;
}

/* FUN_003eaef4 @ 0x003eaef4   (est. sk_capop_003eaef4)
 * Ghidra: void FUN_003eaef4(void)
 * Small capability-invocation shim: it runs a sub-invocation helper, forwards
 * the lo/hi halves of the returned 16-byte result into the in-slice handler
 * sk_capop_003eaf34 along with the running context pointer (extraout_x1), and
 * then completes the operation through sk_x_0036b270.
 * Confidence: low
 * Notes: extraout_x1 is the running context register artifact; callee
 *   sk_capop_003eaf34 is in-slice, the rest out-of-slice. */
static void sk_capop_003eaef4(void)
{
    uint64_t extraout_x1 = 0;   /* Ghidra extraout_x1 */
    cl4_result_t auVar1;

    sk_x_00407478();
    auVar1 = sk_x_0035a7e8();
    sk_capop_003eaf34(auVar1.lo, auVar1.hi, extraout_x1);
    sk_x_0036b270(extraout_x1);
    return;
}

/* FUN_003eb7c4 @ 0x003eb7c4   (est. sk_capop_003eb7c4)
 * Ghidra: void FUN_003eb7c4(void)
 * Capability-invocation handler branching on the low bit of the capability
 * descriptor pointed to by the op frame: if set, it releases the op frame and
 * tail-dispatches; otherwise it loads capability handles, allocates an op-frame
 * buffer and a vtable-pair object, and tail-dispatches through the recovered
 * jump. Both indirect branches are unrecovered by Ghidra.
 * Confidence: low
 * Notes: unrecovered jumptables at 0x003eb834 and 0x003eb8d8; extraout_x16 is
 *   a function pointer feeding the jumptable variable; extraout_x17 local. */
static void sk_capop_003eb7c4(void)
{
    uint64_t uVar1;
    uint64_t lVar2;
    uint64_t uVar3;
    uint64_t *puVar4;
    void (*extraout_x16)(void) = 0; /* Ghidra extraout_x16 */
    void (*UNRECOVERED_JUMPTABLE)(void) = 0;
    uint64_t extraout_x17 = 0;  /* Ghidra extraout_x17 */
    uint8_t *ctx = 0;           /* unaff_x22: current op context */
    cl4_result_t auVar5;

    uVar3 = sk_x_0040790c();
    sk_x_004070d8();
    if ((**(uint8_t **)(ctx + 0x30) & 1) != 0) {
        sk_x_00407960();
        uVar1 = *(uint64_t *)(ctx + 0x58);
        sk_x_0040686c();
        sk_x_0040bd24();
        sk_x_0040bd24(uVar1);
        auVar5 = sk_x_0040678c();
        sk_x_004079b4(auVar5.lo, auVar5.hi, uVar3);
        /* tail dispatch: indirect jump, jumptable at 0x003eb834 not recovered by Ghidra */
        return;
    }
    lVar2 = *(uint64_t *)(ctx + 0x40);
    sk_x_0040652c();
    uVar3 = sk_x_00406608();
    *(uint64_t *)(ctx + 0xa0) = uVar3;
    uVar3 = sk_x_00406e8c();
    *(uint64_t *)(ctx + 0xa8) = uVar3;
    sk_x_00406288();
    sk_x_0040bb18(*(uint32_t *)(lVar2 + 4));
    puVar4 = (uint64_t *)sk_x_00406fe0();
    *(uint64_t **)(ctx + 0xb0) = puVar4;
    *puVar4 = extraout_x17;
    uVar3 = sk_x_00407830();
    sk_x_00406d70(uVar3, *(uint64_t *)(ctx + 0x18), *(uint64_t *)(ctx + 0x20));
    UNRECOVERED_JUMPTABLE = extraout_x16;
    sk_x_004080cc();
    /* tail dispatch: indirect jump, jumptable at 0x003eb8d8 not recovered by Ghidra */
    return;
}

/* FUN_003ec12c @ 0x003ec12c   (est. sk_capop_003ec12c)
 * Ghidra: void FUN_003ec12c(void)
 * Trivial single-thunk dispatcher: forwards directly to the out-of-slice
 * target sk_x_00409414 (a thunk). No local state or op-frame access.
 * Confidence: low
 * Notes: body is only a thunk call to an out-of-slice function. */
static void sk_capop_003ec12c(void)
{
    sk_x_00409414();
    return;
}

/* FUN_003ec708 @ 0x003ec708   (est. sk_capop_003ec708)
 * Ghidra: void FUN_003ec708(void)
 * Noreturn fault/abort path: it runs two out-of-slice setup helpers and then
 * trips a SoftwareBreakpoint (exception 1, code 0x3ec730), treating the
 * returned pointer as a code target to jump to. Execution does not return.
 * Confidence: low
 * Notes: SoftwareBreakpoint result cast to a code pointer; callees out-of-slice. */
static void sk_capop_003ec708(void)
{
    void (*pcVar1)(void);

    sk_x_00407030();
    sk_x_00406490();
    pcVar1 = (void (*)(void))SoftwareBreakpoint(1, 0x3ec730);
    (*pcVar1)();
}

/* FUN_003ec8c8 @ 0x003ec8c8   (est. sk_capop_003ec8c8)
 * Ghidra: void FUN_003ec8c8(undefined8 param_1)
 * Capability-invocation shim that chains three out-of-slice helpers, passing
 * the single argument through the middle (thunked) call, then returns.
 * Confidence: low
 * Notes: arg passed as param_1; middle call is a thunk. */
static void sk_capop_003ec8c8(uint64_t param_1)
{
    sk_x_004080b0();
    sk_x_002298d4(param_1);
    sk_x_001a8564();
    return;
}

/* FUN_003ecd44 @ 0x003ecd44   (est. sk_capop_003ecd44)
 * Ghidra: uint FUN_003ecd44(void)
 * Capability-invocation result helper: it queries an out-of-slice capability
 * lookup; on success it runs a completion helper, reads a return code, and
 * releases the queried object. It packs the result as a byte return value plus
 * a success/failure flag in bit 8 of the returned word.
 * Confidence: low
 * Notes: returns (result & 0xff) | (success << 8); callees out-of-slice. */
static uint32_t sk_capop_003ecd44(void)
{
    uint32_t uVar1;
    uint64_t lVar2;

    lVar2 = sk_x_0040880c();
    if (lVar2 == 0) {
        uVar1 = 0;
    } else {
        sk_x_0036b270();
        uVar1 = sk_x_00409c1c();
        sk_x_0036b118(lVar2);
    }
    return uVar1 & 0xff | (uint32_t)(lVar2 == 0) << 8;
}

/* FUN_003ed4d4 @ 0x003ed4d4   (est. sk_capop_003ed4d4)
 * Ghidra: void FUN_003ed4d4(void)
 * Capability-invocation handler that makes an indirect vtable call through the
 * op frame (vtable at ctx+0x20, slot +0x20), passes lo/hi halves of several
 * 16-byte helper results into out-of-slice services, releases a message slot,
 * and tail-dispatches through the recovered indirect jump.
 * Confidence: low
 * Notes: unrecovered jumptable at 0x003ed568; indirect vtable call at
 *   (*(ctx+0x20) + 0x20); cl4_result_t used for the auVar4 pairs. */
static void sk_capop_003ed4d4(void)
{
    uint64_t uVar1;
    uint64_t uVar2;
    uint64_t uVar3;
    uint8_t *ctx = 0;           /* unaff_x22: current op context */
    cl4_result_t auVar4;

    sk_x_00406fd4();
    ((void (*)(uint64_t, uint64_t, uint64_t))(*(uint64_t *)(*(uint64_t *)(ctx + 0x20) + 0x20)))
        (*(uint64_t *)(ctx + 0x10), *(uint64_t *)(ctx + 0x28), *(uint64_t *)(ctx + 0x18));
    uVar3 = *(uint64_t *)(ctx + 0x28);
    uVar1 = *(uint64_t *)(ctx + 0x18);
    sk_x_0034a210();
    auVar4 = sk_x_00027614();
    uVar2 = sk_x_004063b4(auVar4.lo, auVar4.hi, auVar4.lo);
    sk_x_0031dc0c(uVar2, uVar1);
    auVar4 = sk_x_00356b98();
    sk_x_00369340(auVar4.lo, auVar4.hi, 0);
    sk_x_0040bd24(uVar3);
    sk_x_00407128();
    /* tail dispatch: indirect jump, jumptable at 0x003ed568 not recovered by Ghidra */
    return;
}

/* FUN_003ee47c @ 0x003ee47c   (est. sk_capop_003ee47c)
 * Ghidra: void FUN_003ee47c(void)
 * Short op-frame teardown helper: runs two out-of-slice setup/release helpers,
 * releases the op-frame buffer whose pointer is read from the running context
 * register artifact (extraout_x8 + 0x40), and runs two more out-of-slice
 * completion helpers before returning.
 * Confidence: low
 * Notes: extraout_x8 is the running context register artifact used as a base
 *   for the buffer pointer deref; callees out-of-slice. */
static void sk_capop_003ee47c(void)
{
    uint64_t extraout_x8 = 0;   /* Ghidra extraout_x8 */

    sk_x_00407000();
    sk_x_00407018();
    sk_x_0040bd24(*(uint64_t *)(extraout_x8 + 0x40));
    sk_x_00407594();
    sk_x_00408db8();
    return;
}

/* FUN_003eed30 @ 0x003eed30   (est. sk_capop_003eed30)
 * Ghidra: void FUN_003eed30(undefined8 param_1,undefined8 param_2,code *UNRECOVERED_JUMPTABLE)
 * Capability-invocation handler that seeds a fresh op frame: it stores a
 * capability token at ctx+0x148, carries the running capability (unaff_x20)
 * into the reply slot at ctx+0x110, allocates an op-frame buffer and vtable-pair
 * object, then tail-dispatches through the incoming (parameter) jump target.
 * Confidence: low
 * Notes: UNRECOVERED_JUMPTABLE arrives as a code-pointer parameter (jumptable
 *   at 0x003eedd0 not recovered); unaff_x19/unaff_x20 register artifacts kept
 *   as locals. */
static void sk_capop_003eed30(uint64_t param_1, uint64_t param_2, void (*UNRECOVERED_JUMPTABLE)(void))
{
    uint64_t uVar1;
    uint64_t *puVar2;
    uint64_t extraout_x17 = 0;  /* Ghidra extraout_x17 */
    uint64_t unaff_x19 = 0;     /* Ghidra unaff_x19 */
    uint64_t unaff_x20 = 0;     /* Ghidra unaff_x20 */
    uint8_t *ctx = 0;           /* unaff_x22: current op context */

    sk_x_00406fd4();
    sk_x_00408560();
    sk_x_0034a210();
    uVar1 = sk_x_00002534();
    *(uint64_t *)(ctx + 0x148) = uVar1;
    *(uint64_t *)(ctx + 0x110) = unaff_x20;
    sk_x_00406394();
    sk_x_0040bb18(*(uint32_t *)(unaff_x19 + 4));
    puVar2 = (uint64_t *)sk_x_00406fe0();
    *(uint64_t **)(ctx + 0x150) = puVar2;
    *puVar2 = extraout_x17;
    sk_x_00407c04();
    /* tail dispatch: indirect jump, jumptable at 0x003eedd0 not recovered by Ghidra */
    return;
}

/* FUN_003e7228 @ 0x003e7228   (est. sk_capop_003e7228)
 * Ghidra: void FUN_003e7228(void)
 * Dispatch hub for one capability operation: it inspects the running op
 * context, seeds the per-invocation op frame, and selects between a
 * completion path and a run path. On the completion path it releases a
 * chain of op frames and performs a tail dispatch; on the run path it
 * builds a fresh op frame from the op-frame allocator and drives it.
 * Faithful to the Ghidra control flow, including the unknowable zero-flag
 * branch and the unrecovered indirect jump tables.
 * Confidence: low
 * Notes: UNRECOVERED_JUMPTABLE at 0x003e72f0 and 0x003e7420 (too many
 *   branches); unaff_x22 op context; in_ZR zero-flag result of FUN_00406420;
 *   extraout_* locals carry AArch64 call-clobbered register results. */
static void sk_capop_003e7228(void)
{
    int op_index;
    uint64_t v2;
    uint64_t *frame_ptr;
    long len_val;
    uint64_t jt_hi;
    uint64_t v5;
    uint64_t ret_x8 = 0;         /* extraout_x8 */
    uint64_t ret_x9 = 0;         /* extraout_x9 */
    uint64_t ret_x9_00 = 0;      /* extraout_x9_00 */
    uint64_t ret_x9_01 = 0;      /* extraout_x9_01 */
    uint64_t ret_x10 = 0;        /* extraout_x10 */
    uint64_t ret_x10_00 = 0;     /* extraout_x10_00 */
    uint64_t ret_x11 = 0;        /* extraout_x11 */
    uint64_t ret_x16 = 0;        /* extraout_x16 */
    uint64_t ret_x16_00 = 0;     /* extraout_x16_00 */
    uint64_t ret_x17 = 0;        /* extraout_x17 */
    uint64_t ret_x17_00 = 0;     /* extraout_x17_00 */
    uint8_t *ctx = 0;            /* unaff_x22: current op context */
    cl4_result_t result_pair;  /* auVar6 16-byte pair */
    uint64_t jt;                 /* UNRECOVERED_JUMPTABLE */

    v2 = sk_x_00407b18();
    result_pair = sk_x_00407fcc();
    op_index = *(int *)(*(long *)(ctx + 0x18) + 0x3c);
    *(int *)(ctx + 0x178) = op_index;
    if ((*(uint8_t *)(*(long *)(ctx + 0x20) + (long)op_index) & 1) != 0) {
        sk_x_004069ec();
        v5 = *(uint64_t *)(ctx + 0x38);
        sk_x_0040686c();
        sk_x_0040bd24();
        sk_x_0040bd24();
        sk_x_0040bd24();
        sk_x_0040bd24();
        sk_x_0040bd24();
        sk_x_0040bd24();
        sk_x_0040bd24();
        sk_x_0040bd24();
        sk_x_0040bd24(ret_x9);
        sk_x_0040bd24(ret_x8);
        sk_x_0040bd24(v5);
        result_pair = sk_x_0040678c();
        sk_x_00407878(result_pair.lo, result_pair.hi, v2);
        /* tail dispatch: indirect jump, jumptable at 0x003e72f0 not recovered by Ghidra */
        return;
    }
    *(int *)(ctx + 0x17c) = *(int *)(*(long *)(ctx + 0x18) + 0x38);
    *(uint64_t *)(ctx + 0x110) = *(uint64_t *)(*(long *)(ctx + 0xe8) + 0x10);
    sk_x_00408460(result_pair.lo, result_pair.hi, *(uint64_t *)(ctx + 0xe0));
    ((void (*)(void))ret_x11)();
    sk_x_00406420();
    if (0 /* in_ZR */) {
        v5 = *(uint64_t *)(ctx + 0x50);
        len_val = *(long *)(ctx + 0x58);
        sk_x_00353930(*(uint64_t *)(ctx + 0xe8), *(uint64_t *)(ctx + 0xf0),
                      *(uint64_t *)(ctx + 0xe0));
        *(uint64_t *)(ctx + 0x138) = ret_x9_00;
        *(uint64_t *)(ctx + 0x140) = ret_x10;
        ((void (*)(void))ret_x9_00)();
        sk_x_0040652c();
        sk_x_00406608();
        sk_x_004068f4();
        sk_x_00406268();
        sk_x_0040bb18(*(int *)(len_val + 4));
        frame_ptr = (uint64_t *)sk_x_00406fe0();
        *(uint64_t **)(ctx + 0x148) = frame_ptr;
        *frame_ptr = ret_x17;
        result_pair = sk_x_00406b54();
        jt = ret_x16;
    }
    else {
        v5 = *(uint64_t *)(ctx + 0xd8);
        result_pair = sk_x_00406894(*(uint64_t *)(ctx + 0xf8), *(uint64_t *)(ctx + 0x108),
                                    *(uint64_t *)(ctx + 0xf0));
        *(uint64_t *)(ctx + 0x118) = ret_x9_01;
        *(uint64_t *)(ctx + 0x120) = ret_x10_00;
        ((void (*)(uint64_t, uint64_t, uint64_t))ret_x9_01)(result_pair.lo, result_pair.hi, v5);
        v5 = sk_x_004067f8();
        sk_x_003fcc1c();
        len_val = sk_x_004062c8();
        sk_x_0040bb18(*(int *)(len_val + 4));
        frame_ptr = (uint64_t *)sk_x_00406fe0();
        *(uint64_t **)(ctx + 0x128) = frame_ptr;
        *frame_ptr = ret_x17_00;
        result_pair = sk_x_00406ac4();
        jt = ret_x16_00;
    }
    sk_x_00407878(result_pair.lo, result_pair.hi, v5, jt, v2);
    /* tail dispatch: indirect jump, jumptable at 0x003e7420 not recovered by Ghidra */
    return;
}

/* FUN_003e9310 @ 0x003e9310   (est. sk_capop_003e9310)
 * Ghidra: void FUN_003e9310(void)
 * Capability operation dispatch hub over the running op context. It reads
 * reply/message-slot pointers out of the context, probes the dispatch
 * condition, and on the success side drives the run path (seeding a new op
 * frame, recording reply-slot metadata, dispatching the tail handler),
 * while on the fallback side it walks the context, invokes vtable and
 * indirect handler entries, and releases the full chain of op frames.
 * Faithfully preserves every store, call and branch including the
 * unrecovered jump tables.
 * Confidence: low
 * Notes: UNRECOVERED_JUMPTABLE at 0x003e95ac and 0x003e9644 (too many
 *   branches); LAB_003e8d3c reply-slot marker; in_ZR zero-flag results;
 *   in_stack_00000000/00000008 spilled stack args released as op frames;
 *   unaff_x22 op context; extraout_* register-result locals. */
static void sk_capop_003e9310(void)
{
    uint64_t slot_fn;
    uint64_t v2;
    uint64_t v3;
    uint64_t v4;
    uint64_t v5;
    uint64_t v6;
    uint64_t v7;
    uint64_t *frame_ptr;
    long long_arg;
    uint64_t jt;
    uint64_t ret_x8 = 0;         /* extraout_x8 */
    uint64_t ret_x8_00 = 0;      /* extraout_x8_00 */
    uint64_t v10;
    uint64_t ret_x9 = 0;         /* extraout_x9 */
    uint64_t ret_x9_00 = 0;      /* extraout_x9_00 */
    uint64_t ret_x10 = 0;        /* extraout_x10 */
    uint64_t ret_x10_00 = 0;     /* extraout_x10_00 */
    uint64_t ret_x16 = 0;        /* extraout_x16 */
    uint64_t ret_x16_00 = 0;     /* extraout_x16_00 */
    uint64_t ret_x17 = 0;        /* extraout_x17 */
    uint64_t ret_x17_00 = 0;     /* extraout_x17_00 */
    uint64_t v11;
    uint64_t v12;
    uint8_t *ctx = 0;            /* unaff_x22: current op context */
    uint64_t vtable_fn;
    long idx;
    uint64_t *vtable_slot;
    long base_off;
    cl4_result_t result_pair;  /* auVar17 16-byte pair */
    uint64_t spill0 = 0;         /* in_stack_00000000 */
    uint64_t spill8 = 0;         /* in_stack_00000008 */
    uint64_t jt_hi;              /* UNRECOVERED_JUMPTABLE_00 */

    v7 = sk_x_00407afc();
    sk_x_00407f60();
    v11 = *(uint64_t *)(ctx + 0xd8);
    v12 = *(uint64_t *)(ctx + 0xc0);
    sk_x_00406be4();
    if (0 /* in_ZR */) {
        slot_fn = *(uint64_t *)(ctx + 0x198);
        long_arg = *(long *)(ctx + 0xd0);
        ((void (*)(uint64_t, uint64_t))(*(uint64_t *)(*(uint64_t *)(ctx + 0x148) + 8)))
                  (*(uint64_t *)(ctx + 0x150), *(uint64_t *)(ctx + 0x128));
        sk_x_003507e0(*(uint64_t *)(long_arg + 8));
        ((void (*)(void))ret_x8)();
        sk_x_00408410();
        ((void (*)(void))slot_fn)();
        sk_x_00350744(*(long *)(ctx + 0x30) + (long)*(int *)(ctx + 0x1e4));
        result_pair = sk_x_000839d8();
        sk_x_00406fb0(*(uint64_t *)(ctx + 0x170), result_pair.lo, result_pair.hi,
                      *(uint64_t *)(ctx + 0x130));
        ((void (*)(void))ret_x8_00)();
        sk_x_00406420();
        if (0 /* in_ZR */) {
            long_arg = *(long *)(ctx + 0x68);
            sk_x_00353930(*(uint64_t *)(ctx + 0x138), *(uint64_t *)(ctx + 0x140),
                          *(uint64_t *)(ctx + 0x130));
            *(uint64_t *)(ctx + 0x198) = ret_x9;
            *(uint64_t *)(ctx + 0x1a0) = ret_x10;
            ((void (*)(void))ret_x9)();
            sk_x_0040652c();
            v7 = sk_x_00406608();
            *(uint64_t *)(ctx + 0x1a8) = v7;
            v7 = sk_x_00406e8c();
            *(uint64_t *)(ctx + 0x1b0) = v7;
            sk_x_00406288();
            sk_x_0040bb18(*(int *)(long_arg + 4));
            frame_ptr = (uint64_t *)sk_x_00406fe0();
            *(uint64_t **)(ctx + 0x1b8) = frame_ptr;
            *frame_ptr = ret_x17;
            frame_ptr[1] = 0x003e8d3c; /* LAB_003e8d3c */
            sk_x_004067b8(*(uint64_t *)(ctx + 0xa0));
            jt_hi = ret_x16;
        }
        else {
            v7 = *(uint64_t *)(ctx + 0x128);
            result_pair = sk_x_00406894(*(uint64_t *)(ctx + 0x148), *(uint64_t *)(ctx + 0x158),
                                        *(uint64_t *)(ctx + 0x140));
            *(uint64_t *)(ctx + 0x178) = ret_x9_00;
            *(uint64_t *)(ctx + 0x180) = ret_x10_00;
            ((void (*)(uint64_t, uint64_t, uint64_t))ret_x9_00)(result_pair.lo, result_pair.hi, v7);
            v7 = sk_x_004067f8();
            *(uint64_t *)(ctx + 0x188) = v7;
            sk_x_003fcc4c();
            long_arg = sk_x_00406374();
            sk_x_0040bb18(*(int *)(long_arg + 4));
            frame_ptr = (uint64_t *)sk_x_00406fe0();
            *(uint64_t **)(ctx + 400) = frame_ptr;
            *frame_ptr = ret_x17_00;
            sk_x_00406a24();
            jt_hi = ret_x16_00;
        }
        sk_x_004075d0();
        /* tail dispatch: indirect jump, jumptable at 0x003e9644 not recovered by Ghidra */
        return;
    }
    slot_fn = *(uint64_t *)(ctx + 0x198);
    v3 = *(uint64_t *)(ctx + 0x1a0);
    idx = (long)*(int *)(ctx + 0x1e4);
    long_arg = *(long *)(ctx + 0x148);
    v4 = *(uint64_t *)(ctx + 0x150);
    v2 = *(uint64_t *)(ctx + 0x128);
    v5 = *(uint64_t *)(ctx + 0x130);
    v6 = *(uint64_t *)(ctx + 0xf0);
    base_off = *(long *)(ctx + 0x30);
    v10 = *(uint64_t *)(ctx + 0x10);
    vtable_slot = (uint64_t *)(*(long *)(ctx + 0xe8) + 0x20);
    vtable_fn = *vtable_slot;
    sk_x_00350968(v6);
    ((void (*)(void))vtable_fn)();
    ((void (*)(uint64_t, uint64_t, uint64_t))slot_fn)(v3, base_off + idx, v5);
    frame_ptr = (uint64_t *)(long_arg + 0x20);
    ((void (*)(uint64_t, uint64_t, uint64_t))*frame_ptr)(base_off + idx, v4, v2);
    sk_x_00350750(base_off + idx);
    sk_x_000839d8();
    ((void (*)(uint64_t, uint64_t, uint64_t))vtable_fn)(v10, v6, v12);
    sk_x_004066bc();
    sk_x_00350750();
    sk_x_000839d8();
    sk_x_0040bd24(v2);
    sk_x_0040bd24(v6);
    sk_x_0040bd24(idx);
    sk_x_0040bd24(vtable_slot);
    sk_x_0040bd24(base_off);
    sk_x_0040bd24(v12);
    sk_x_0040bd24(v11);
    sk_x_0040bd24(frame_ptr);
    sk_x_0040bd24(vtable_fn);
    sk_x_0040bd24(spill0);
    sk_x_0040bd24(spill8);
    sk_x_0040bd24(v5);
    sk_x_0040bd24(slot_fn);
    sk_x_0040bd24(v3);
    sk_x_0040bd24(v4);
    sk_x_0040bd24(v10);
    result_pair = sk_x_0040678c();
    sk_x_004075d0(result_pair.lo, result_pair.hi, v7);
    /* tail dispatch: indirect jump, jumptable at 0x003e95ac not recovered by Ghidra */
    return;
}

/* FUN_003ea260 @ 0x003ea260   (est. sk_capop_003ea260)
 * Ghidra: void FUN_003ea260(void)
 * Capability operation dispatch over the running op context. On the success
 * branch it forwards operation arguments, releases the op frame, and tail
 * dispatches; otherwise it seeds a new per-invocation op frame from the
 * frame allocator, records the reply-slot marker, and drives the frame to
 * completion via an unrecovered indirect jump.
 * Confidence: low
 * Notes: UNRECOVERED_JUMPTABLE at 0x003ea2e0 and 0x003ea37c (too many
 *   branches); LAB_003ea380 reply-slot marker; in_ZR zero-flag result of
 *   FUN_00406420; extraout_x8/x9/x17 register-result locals; unaff_x22 op
 *   context. */
static void sk_capop_003ea260(void)
{
    long frame_base;
    long idx_base;
    uint64_t v3;
    uint64_t v4;
    uint64_t *frame_ptr;
    uint64_t jt;                 /* UNRECOVERED_JUMPTABLE_00 */
    long ret_x8 = 0;             /* extraout_x8 */
    uint64_t ret_x9 = 0;         /* extraout_x9 */
    uint64_t ret_x9_00 = 0;      /* extraout_x9_00 */
    uint64_t ret_x17 = 0;        /* extraout_x17 */
    uint64_t v6;
    uint8_t *ctx = 0;            /* unaff_x22: current op context */
    cl4_result_t result_pair;  /* auVar7 16-byte pair */
    uint64_t jt_lo;              /* UNRECOVERED_JUMPTABLE */

    v3 = sk_x_00407ca0();
    sk_x_0040700c();
    v6 = *(uint64_t *)(ctx + 0x38);
    v4 = sk_x_00406420();
    if (0 /* in_ZR */) {
        sk_x_0040711c(*(uint64_t *)(ctx + 0x48), v4, *(uint64_t *)(ctx + 0x40));
        ((void (*)(void))ret_x9)();
        sk_x_00407604();
        sk_x_00408374();
        sk_x_00406c5c();
        sk_x_0040bd24(v6);
        result_pair = sk_x_0040678c();
        sk_x_00407e58(result_pair.lo, result_pair.hi, v3);
        /* tail dispatch: indirect jump, jumptable at 0x003ea2e0 not recovered by Ghidra */
        return;
    }
    frame_base = *(long *)(ctx + 0x18);
    idx_base = *(long *)(ctx + 0x20);
    sk_x_00406bd4(*(uint64_t *)(ctx + 0x58), *(uint64_t *)(ctx + 0x60));
    ((void (*)(void))ret_x9_00)();
    sk_x_004062a8(*(uint64_t *)(idx_base + *(int *)(frame_base + 0x2c)));
    sk_x_0040bb18(*(int *)(ret_x8 + 4));
    frame_ptr = (uint64_t *)sk_x_00406fe0();
    *(uint64_t **)(ctx + 0x78) = frame_ptr;
    *frame_ptr = ret_x17;
    frame_ptr[1] = 0x003ea380; /* LAB_003ea380 */
    sk_x_00407610(frame_ptr, *(uint64_t *)(ctx + 0x60));
    /* tail dispatch: indirect jump, jumptable at 0x003ea37c not recovered by Ghidra */
    return;
}

/* FUN_003eaf34 @ 0x003eaf34   (est. sk_capop_003eaf34)
 * Ghidra: void FUN_003eaf34(void)
 * Thin wrapper that forwards directly to the in-slice handler sk_capop_
 * 003eaf4c. The whole body is a single tail call followed by a return.
 * Confidence: low
 * Notes: none — no Ghidra artifacts beyond the single in-slice callee. */
static void sk_capop_003eaf34(void)
{
    sk_capop_003eaf4c();
    return;
}

/* FUN_003eb9c8 @ 0x003eb9c8   (est. sk_capop_003eb9c8)
 * Ghidra: void FUN_003eb9c8(void)
 * Capability operation dispatch over the running op context. On the success
 * branch it forwards operation arguments, releases the op frames, and tail
 * dispatches; otherwise it runs the operation by seeding a new op frame
 * from the frame allocator, stashing the context and a reply-slot marker in
 * it, and driving it to completion.
 * Confidence: low
 * Notes: UNRECOVERED_JUMPTABLE at 0x003eba50 and 0x003ebae8 (too many
 *   branches); LAB_003ebaec reply-slot marker; in_ZR zero-flag result of
 *   FUN_00406420; extraout_x8/x9/x10 register-result locals; unaff_x22 op
 *   context. */
static void sk_capop_003eb9c8(void)
{
    long idx_base;
    uint64_t v2;
    uint64_t v3;
    long *frame_ptr;
    uint64_t jt;                 /* UNRECOVERED_JUMPTABLE_00 */
    long ret_x8 = 0;             /* extraout_x8 */
    uint64_t ret_x9 = 0;         /* extraout_x9 */
    uint64_t ret_x9_00 = 0;      /* extraout_x9_00 */
    uint64_t ret_x9_01 = 0;      /* extraout_x9_01 */
    uint64_t ret_x10 = 0;        /* extraout_x10 */
    uint64_t v5;
    uint8_t *ctx = 0;            /* unaff_x22: current op context */
    cl4_result_t result_pair;  /* auVar6 16-byte pair */
    uint64_t jt_lo;              /* UNRECOVERED_JUMPTABLE */

    v2 = sk_x_00407ca0();
    sk_x_0040700c();
    v5 = *(uint64_t *)(ctx + 0x60);
    v3 = sk_x_00406420();
    if (0 /* in_ZR */) {
        sk_x_0040711c(*(uint64_t *)(ctx + 0x70), v3, *(uint64_t *)(ctx + 0x68));
        ((void (*)(void))ret_x9)();
        sk_x_00407960();
        v3 = *(uint64_t *)(ctx + 0x58);
        sk_x_0040686c();
        sk_x_0040bd24(v5);
        sk_x_0040bd24(v3);
        result_pair = sk_x_0040678c();
        sk_x_00407e58(result_pair.lo, result_pair.hi, v2);
        /* tail dispatch: indirect jump, jumptable at 0x003eba50 not recovered by Ghidra */
        return;
    }
    idx_base = *(long *)(ctx + 0x28);
    sk_x_00406894(*(uint64_t *)(ctx + 0x80), *(uint64_t *)(ctx + 0x88));
    *(uint64_t *)(ctx + 0xb8) = ret_x9_00;
    *(uint64_t *)(ctx + 0xc0) = ret_x10;
    sk_x_00350624();
    ((void (*)(void))ret_x9_01)();
    sk_x_004062e8((long)*(int *)(idx_base + 0x28));
    frame_ptr = (long *)sk_x_0040bb18(*(int *)(ret_x8 + 4));
    *(long **)(ctx + 200) = frame_ptr;
    *frame_ptr = (long)ctx;
    frame_ptr[1] = (long)0x003ebaec; /* LAB_003ebaec */
    sk_x_00406bb4(*(uint64_t *)(ctx + 0x88));
    /* tail dispatch: indirect jump, jumptable at 0x003ebae8 not recovered by Ghidra */
    return;
}

/* FUN_003ec130 @ 0x003ec130   (est. sk_capop_003ec130)
 * Ghidra: void FUN_003ec130(void)
 * Thin wrapper that forwards directly to the out-of-slice helper sk_x_
 * 00409414 and returns. No op-context work of its own.
 * Confidence: low
 * Notes: none — single out-of-slice tail call. */
static void sk_capop_003ec130(void)
{
    sk_x_00409414();
    return;
}

/* FUN_003ec730 @ 0x003ec730   (est. sk_capop_003ec730)
 * Ghidra: void FUN_003ec730(void)
 * Invokes two out-of-slice helpers and then traps via a software
 * breakpoint (the decompiler marks this path as non-returning). The
 * breakpoint result is treated as a code pointer and called.
 * Confidence: low
 * Notes: SoftwareBreakpoint(1, 0x3ec758) — decompiler "Does not return"
 *   warning on the breakpoint path. */
static void sk_capop_003ec730(void)
{
    uint64_t trap_fn;

    sk_x_00407030();
    sk_x_00406490();
    /* WARNING: Does not return */
    trap_fn = (uint64_t)SoftwareBreakpoint(1, 0x3ec758);
    ((void (*)(void))trap_fn)();
}

/* FUN_003ec918 @ 0x003ec918   (est. sk_capop_003ec918)
 * Ghidra: void FUN_003ec918(void)
 * Builds a local stack buffer, seeds it through an out-of-slice initializer,
 * forwards it together with the value pointed to by the unaff_x20 base into
 * the in-slice handler sk_capop_003ec8a0, and tears the buffer down through
 * an out-of-slice finalizer.
 * Confidence: low
 * Notes: unaff_x20 is the running op-context base (uint64_t*); local 72-byte
 *   stack scratch auStack_68. */
static void sk_capop_003ec918(void)
{
    uint64_t *ctx_base = 0;      /* unaff_x20: running op-context base */
    uint8_t stack_scratch[72];   /* auStack_68 local stack scratch */

    sk_x_001a84f4(stack_scratch);
    sk_capop_003ec8a0(stack_scratch, *ctx_base);
    sk_x_001a8564();
    return;
}

/* FUN_003ecd98 @ 0x003ecd98   (est. sk_capop_003ecd98)
 * Ghidra: void FUN_003ecd98(void)
 * Queries an out-of-slice condition; when the returned value is non-zero it
 * invokes an out-of-slice handler, then returns. Minimal probe-and-act body.
 * Confidence: low
 * Notes: none beyond the two out-of-slice callees. */
static void sk_capop_003ecd98(void)
{
    long check_val;

    check_val = sk_x_004088a0();
    if (check_val != 0) {
        sk_x_001e9c00();
    }
    return;
}

/* FUN_003ed5f8 @ 0x003ed5f8   (est. sk_capop_003ed5f8)
 * Ghidra: void FUN_003ed5f8(undefined8 param_1,undefined8 param_2,undefined8 param_3)
 * Capability operation with three arguments. It runs a sequence of out-of-
 * slice setup steps, folds the third argument into a message value, calls a
 * global function pointer, then invokes a reply handler passing the message
 * value and a small local slot, and finally delivers the reply with the
 * original first argument.
 * Confidence: low
 * Notes: (*DAT_00658c80)() is a global code pointer (sk_g_00658c80);
 *   extraout_x8/x12 register-result locals; auVar2 16-byte pseudo-pair;
 *   local_38 reply-slot buffer. */
static void sk_capop_003ed5f8(uint64_t param_1, uint64_t param_2, uint64_t param_3)
{
    uint64_t msg_val;
    uint64_t ret_x8 = 0;         /* extraout_x8 */
    long ret_x12 = 0;            /* extraout_x12 */
    uint8_t reply_slot[8];       /* local_38 reply-slot buffer */
    cl4_result_t result_pair;  /* auVar2 16-byte pair */

    sk_x_0034a210();
    result_pair = sk_x_00027614();
    msg_val = sk_x_004063b4(result_pair.lo, result_pair.hi, result_pair.lo);
    msg_val = sk_x_0031dc0c(msg_val, param_3);
    sk_x_000a6f88();
    sk_x_0007c1a4();
    ((void (*)(void))sk_g_00658c80)(); /* (*DAT_00658c80)() */
    sk_x_00407b80();
    result_pair = sk_x_00351384(*(uint64_t *)(ret_x12 + 0x10));
    ((void (*)(uint64_t, uint64_t, uint64_t))ret_x8)(result_pair.lo, result_pair.hi, msg_val);
    sk_x_0027ed7c(param_1, msg_val, reply_slot);
    return;
}

/* FUN_003ee520 @ 0x003ee520   (est. sk_capop_003ee520)
 * Ghidra: void FUN_003ee520(void)
 * Capability operation dispatch over the running op context. It forwards an
 * argument pair, probes a result value, and when that result is exactly one
 * it releases the op frame and tail dispatches; otherwise it seeds a new
 * op frame, records the frame pointer into the context, and runs two
 * out-of-slice continuations before returning.
 * Confidence: low
 * Notes: UNRECOVERED_JUMPTABLE at 0x003ee598 (too many branches);
 *   extraout_x9/x17 register-result locals; unaff_x22 op context. */
static void sk_capop_003ee520(void)
{
    uint64_t probe;
    uint64_t *frame_ptr;
    uint64_t jt;                 /* UNRECOVERED_JUMPTABLE */
    uint64_t ret_x9 = 0;         /* extraout_x9 */
    uint64_t ret_x17 = 0;        /* extraout_x17 */
    uint64_t v3;
    uint8_t *ctx = 0;            /* unaff_x22: current op context */
    cl4_result_t result_pair;  /* auVar4 16-byte pair */

    result_pair = sk_x_00407000();
    v3 = *(uint64_t *)(ctx + 0x38);
    sk_x_00351d24(result_pair.lo, result_pair.hi, *(uint64_t *)(ctx + 0x20));
    probe = sk_x_000839f8();
    sk_x_0040711c(*(uint64_t *)(ctx + 0x30), probe, *(uint64_t *)(ctx + 0x28));
    ((void (*)(void))ret_x9)();
    if ((int)probe == 1) {
        sk_x_0040bd24(v3);
        sk_x_00407128();
        /* tail dispatch: indirect jump, jumptable at 0x003ee598 not recovered by Ghidra */
        return;
    }
    sk_x_00408094();
    frame_ptr = (uint64_t *)sk_x_00406fe0();
    *(uint64_t **)(ctx + 0x40) = frame_ptr;
    *frame_ptr = ret_x17;
    sk_x_004071d0();
    sk_x_003ef544();
    return;
}

/* FUN_003eeef4 @ 0x003eeef4   (est. sk_capop_003eeef4)
 * Ghidra: void FUN_003eeef4(void)
 * Capability operation dispatch over the running op-context base. It runs
 * two out-of-slice setup helpers, releases an op frame whose tag is derived
 * from the local stack address, then registers an out-of-slice handler
 * (sk_x_003eefc0) as a callback together with two context pointers into
 * an out-of-slice installer.
 * Confidence: low
 * Notes: unaff_x20 op-context base; the 0xc31a000000000000 constant is a
 *   tagged-pointer marker OR-ed with the stack-address tag; extraout_x16
 *   register-result local used as a base for the callback arg. */
static void sk_capop_003eeef4(void)
{
    long ret_x16 = 0;            /* extraout_x16 */
    uint8_t *ctx_base = 0;       /* unaff_x20: running op-context base */
    uint8_t stack_cell;          /* local stack cell */

    sk_x_00407000();
    sk_x_00407520();
    sk_x_0040bd24((uint64_t)&stack_cell & 0xffffffffffff | 0xc31a000000000000,
                  *(uint64_t *)(ctx_base + 0x160));
    sk_x_00407444();
    sk_x_00408db8((uint64_t)sk_x_003eefc0, *(uint64_t *)(ctx_base + 0x138),
                  *(uint64_t *)(ret_x16 + 0x140));
    return;
}
