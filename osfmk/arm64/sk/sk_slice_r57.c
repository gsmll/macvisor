/* Recreated from cl4_kernel.raw (cL4 microkernel, arm64e, image base 0).
 * Ground truth: Ghidra FUN_ names + addresses. Names use cL4/seL4 vocabulary; estimates unless matched.
 *
 * Slice R57: 0x003e68f0-0x003eeef4 (120 functions). The cL4 IPC / "tightbeam"
 * messaging-dispatch subsystem. The region is the thread-message send/receive
 * and context-switch dispatch engine that runs over the per-cpu/thread context
 * block addressed by the callee-preserved register x22 (`ctx` below). Bodies
 * are written as dispatched by the decompiler; many are shallow trampolines
 * into the shared 0x40xxxx IPC core (FUN_00407000 et al.) and indirect
 * function-pointer tables (UNRECOVERED_JUMPTABLE = tail dispatch through a
 * saved handler slot). Where the decompiler only recovered register artifacts
 * (in_rN inputs, xr_xN live-out register slots, zero_cc flags) the body keeps
 * that shape with low/medium confidence.
 *
 * Notable pieces:
 *   - The `sk_rt_0040bb18` allocator + `sk_rt_00406fe0` frame-slot push are
 *     the message/stack-frame allocation pair used by most entry wrappers.
 *   - FUN_003ec9c4 maps a task-priority value to a scheduler code
 *     (s_TaskPriority_low/medium/high string refs) - a small switch.
 *   - FUN_003ebf10/003ee818/003eeef4 embed tagged pointer/error constants and
 *     the "Exclaves" / "Task swift" swift error strings.
 *   - The 003ec6c8..003ec874 run is the SoftwareBreakpoint(1,addr) exception
 *     dispatch chain (a fault-injection / breakpoint table).
 *
 * Confidence: medium-low (IPC dispatch glue; names inferred from cL4 vocabulary;
 * no header matches in this slice). */
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "sk_internal.h"

/* 128-bit word-pair used by the 16-byte-return runtime helpers. */
typedef struct sk_u128 { word_t lo; word_t hi; } sk_u128_t;
/* Generic indirect-call slot type (decompiler `code *`); returns a word_t so
 * the decompiler's register-artifact reads of a call result compile. */
typedef word_t (*code_t)();
/* Opaque GENTER/GEXIT boundary (opcode 0x00201420 / 0x00201400) into the
 * guarded execution levels; the selector in x16 chooses the dispatch endpoint. */
#define GENTER() __asm__ __volatile__ (".word 0x00201420\n" :: : "memory")
#define GEXIT()  __asm__ __volatile__ (".word 0x00201400\n" :: : "memory")

/* out-of-slice data globals referenced by this slice (Ghidra name in comment) */
extern uint64_t sk_d_004060bc;            /* DAT_004060bc */
extern uint64_t sk_d_004bbc30;            /* DAT_004bbc30 */
extern uint64_t sk_d_005a00bc;            /* DAT_005a00bc */
extern uint64_t sk_d_005a00cc;            /* DAT_005a00cc */
extern uint64_t sk_d_005a00dc;            /* DAT_005a00dc */
extern uint64_t sk_d_005a00ec;            /* DAT_005a00ec */
extern uint64_t sk_d_005a0138;            /* DAT_005a0138 */
extern uint64_t sk_d_005a0194;            /* DAT_005a0194 */
extern uint64_t sk_d_00614a5c;            /* DAT_00614a5c */
extern uint64_t sk_d_0064c260;            /* DAT_0064c260 */
extern uint64_t sk_d_00658c80;            /* DAT_00658c80 */
extern uint64_t sk_d_006adf30;            /* DAT_006adf30 */
extern uint64_t sk_d_006c0b58;            /* DAT_006c0b58 */
extern uint64_t sk_lab_003e7a08;            /* LAB_003e7a08 */
extern uint64_t sk_lab_003e7c34;            /* LAB_003e7c34 */
extern uint64_t sk_lab_003e8d3c;            /* LAB_003e8d3c */
extern uint64_t sk_lab_003e8fc4;            /* LAB_003e8fc4 */
extern uint64_t sk_lab_003e9224;            /* LAB_003e9224 */
extern uint64_t sk_lab_003ea380;            /* LAB_003ea380 */
extern uint64_t sk_lab_003eaa20;            /* LAB_003eaa20 */
extern uint64_t sk_lab_003eb2dc;            /* LAB_003eb2dc */
extern uint64_t sk_lab_003eb4b4;            /* LAB_003eb4b4 */
extern uint64_t sk_lab_003ebaec;            /* LAB_003ebaec */
extern uint64_t sk_lab_003ec5f8;            /* LAB_003ec5f8 */
extern uint64_t sk_lab_003ed834;            /* LAB_003ed834 */
extern uint64_t sk_lab_003edbfc;            /* LAB_003edbfc */
extern uint64_t sk_u_006775b0;            /* UINT_006775b0 */
extern uint64_t sk_d_006adf30;            /* _DAT_006adf30 */
extern uint64_t sk_d_006c0b58;            /* _DAT_006c0b58 */
extern uint64_t sk_s_taskpriority_high_005dc050;            /* s_TaskPriority_high_005dc050 */
extern uint64_t sk_s_taskpriority_low_005dc090;            /* s_TaskPriority_low_005dc090 */
extern uint64_t sk_s_taskpriority_medium_005dc070;            /* s_TaskPriority_medium_005dc070 */
extern uint64_t sk_s_unavailable_in_exclaves_005dc0d0;            /* s_Unavailable_in_Exclaves_005dc0d0 */
extern uint64_t sk_s__concurrency_task_swift_005dc0b0;            /* s__Concurrency_Task_swift_005dc0b0 */

/* out-of-slice cL4 helpers referenced by this slice (all defined elsewhere; FUN_ address preserved).
 * Declared with word_t return so a helper that the decompiler reads a result from
 * (undefined8) compiles; void-result helpers just discard the return value. */
extern word_t sk_rt_00002534();   /* FUN_00002534 */
extern word_t sk_rt_000026e8();   /* FUN_000026e8 */
extern sk_u128_t sk_rt_00019858();   /* FUN_00019858 */
extern sk_u128_t sk_rt_00027614();   /* FUN_00027614 */
extern word_t sk_rt_00027724();   /* FUN_00027724 */
extern word_t sk_rt_0006a4c0();   /* FUN_0006a4c0 */
extern word_t sk_rt_0007c028();   /* FUN_0007c028 */
extern word_t sk_rt_0007c1a4();   /* FUN_0007c1a4 */
extern word_t sk_rt_000836a4();   /* FUN_000836a4 */
extern sk_u128_t sk_rt_000839d8();   /* FUN_000839d8 */
extern word_t sk_rt_000839f8();   /* FUN_000839f8 */
extern word_t sk_rt_0008409c();   /* FUN_0008409c */
extern word_t sk_rt_00084180();   /* FUN_00084180 */
extern word_t sk_rt_00084220();   /* FUN_00084220 */
extern word_t sk_rt_00084234();   /* FUN_00084234 */
extern word_t sk_rt_0008e1ec();   /* FUN_0008e1ec */
extern word_t sk_rt_0009461c();   /* FUN_0009461c */
extern word_t sk_rt_000a649c();   /* FUN_000a649c */
extern word_t sk_rt_000a6f88();   /* FUN_000a6f88 */
extern word_t sk_rt_000b430c();   /* FUN_000b430c */
extern word_t sk_rt_000e72d4();   /* FUN_000e72d4 */
extern word_t sk_rt_001a84f4();   /* FUN_001a84f4 */
extern word_t sk_rt_001a8564();   /* FUN_001a8564 */
extern word_t sk_rt_001afa84();   /* FUN_001afa84 */
extern word_t sk_rt_001afe4c();   /* FUN_001afe4c */
extern word_t sk_rt_001c9a1c();   /* FUN_001c9a1c */
extern word_t sk_rt_001e9c00();   /* FUN_001e9c00 */
extern word_t sk_rt_0027ed7c();   /* FUN_0027ed7c */
extern word_t sk_rt_002a4ab4();   /* FUN_002a4ab4 */
extern word_t sk_rt_00310d68();   /* FUN_00310d68 */
extern word_t sk_rt_0031986c();   /* FUN_0031986c */
extern word_t sk_rt_00319f3c();   /* FUN_00319f3c */
extern word_t sk_rt_0031dc0c();   /* FUN_0031dc0c */
extern word_t sk_rt_003488bc();   /* FUN_003488bc */
extern word_t sk_rt_00349530();   /* FUN_00349530 */
extern word_t sk_rt_00349a54();   /* FUN_00349a54 */
extern word_t sk_rt_0034a210();   /* FUN_0034a210 */
extern word_t sk_rt_0034b05c();   /* FUN_0034b05c */
extern word_t sk_rt_0034bb84();   /* FUN_0034bb84 */
extern word_t sk_rt_0034bcf0();   /* FUN_0034bcf0 */
extern word_t sk_rt_0034d004();   /* FUN_0034d004 */
extern sk_u128_t sk_rt_0034d2b4();   /* FUN_0034d2b4 */
extern word_t sk_rt_00350404();   /* FUN_00350404 */
extern sk_u128_t sk_rt_00350500();   /* FUN_00350500 */
extern sk_u128_t sk_rt_0035050c();   /* FUN_0035050c */
extern sk_u128_t sk_rt_00350518();   /* FUN_00350518 */
extern word_t sk_rt_00350548();   /* FUN_00350548 */
extern word_t sk_rt_00350624();   /* FUN_00350624 */
extern word_t sk_rt_00350744();   /* FUN_00350744 */
extern word_t sk_rt_00350750();   /* FUN_00350750 */
extern word_t sk_rt_00350798();   /* FUN_00350798 */
extern word_t sk_rt_003507e0();   /* FUN_003507e0 */
extern word_t sk_rt_00350878();   /* FUN_00350878 */
extern word_t sk_rt_00350968();   /* FUN_00350968 */
extern word_t sk_rt_003509c8();   /* FUN_003509c8 */
extern word_t sk_rt_00350b54();   /* FUN_00350b54 */
extern word_t sk_rt_00350c5c();   /* FUN_00350c5c */
extern word_t sk_rt_003510a0();   /* FUN_003510a0 */
extern sk_u128_t sk_rt_00351384();   /* FUN_00351384 */
extern word_t sk_rt_003513b4();   /* FUN_003513b4 */
extern word_t sk_rt_0035187c();   /* FUN_0035187c */
extern word_t sk_rt_00351d24();   /* FUN_00351d24 */
extern word_t sk_rt_00351da8();   /* FUN_00351da8 */
extern word_t sk_rt_00351e3c();   /* FUN_00351e3c */
extern word_t sk_rt_00351f10();   /* FUN_00351f10 */
extern word_t sk_rt_00352018();   /* FUN_00352018 */
extern word_t sk_rt_00352efc();   /* FUN_00352efc */
extern word_t sk_rt_00353080();   /* FUN_00353080 */
extern word_t sk_rt_00353498();   /* FUN_00353498 */
extern word_t sk_rt_00353930();   /* FUN_00353930 */
extern sk_u128_t sk_rt_00356b98();   /* FUN_00356b98 */
extern word_t sk_rt_003591d0();   /* FUN_003591d0 */
extern word_t sk_rt_003593c0();   /* FUN_003593c0 */
extern sk_u128_t sk_rt_0035a7e8();   /* FUN_0035a7e8 */
extern word_t sk_rt_0035ac70();   /* FUN_0035ac70 */
extern word_t sk_rt_00369340();   /* FUN_00369340 */
extern word_t sk_rt_0036986c();   /* FUN_0036986c */
extern word_t sk_rt_0036993c();   /* FUN_0036993c */
extern word_t sk_rt_0036a9d4();   /* FUN_0036a9d4 */
extern word_t sk_rt_0036b118();   /* FUN_0036b118 */
extern word_t sk_rt_0036b270();   /* FUN_0036b270 */
extern word_t sk_rt_00377824();   /* FUN_00377824 */
extern word_t sk_rt_00377bec();   /* FUN_00377bec */
extern word_t sk_rt_00377dcc();   /* FUN_00377dcc */
extern word_t sk_rt_0039a128();   /* FUN_0039a128 */
extern word_t sk_rt_003a25d4();   /* FUN_003a25d4 */
extern word_t sk_rt_003d4658();   /* FUN_003d4658 */
extern word_t sk_rt_003e63a8();   /* FUN_003e63a8 */
extern word_t sk_rt_003eefc0();   /* FUN_003eefc0 */
extern word_t sk_rt_003ef544();   /* FUN_003ef544 */
extern word_t sk_rt_003ef924();   /* FUN_003ef924 */
extern word_t sk_rt_003fcc1c();   /* FUN_003fcc1c */
extern word_t sk_rt_003fcc4c();   /* FUN_003fcc4c */
extern word_t sk_rt_003fd194();   /* FUN_003fd194 */
extern word_t sk_rt_003fd25c();   /* FUN_003fd25c */
extern word_t sk_rt_00406268();   /* FUN_00406268 */
extern word_t sk_rt_00406288();   /* FUN_00406288 */
extern word_t sk_rt_004062a8();   /* FUN_004062a8 */
extern word_t sk_rt_004062c8();   /* FUN_004062c8 */
extern word_t sk_rt_004062e8();   /* FUN_004062e8 */
extern word_t sk_rt_00406374();   /* FUN_00406374 */
extern word_t sk_rt_00406394();   /* FUN_00406394 */
extern word_t sk_rt_004063b4();   /* FUN_004063b4 */
extern word_t sk_rt_00406420();   /* FUN_00406420 */
extern word_t sk_rt_00406490();   /* FUN_00406490 */
extern word_t sk_rt_0040652c();   /* FUN_0040652c */
extern word_t sk_rt_0040654c();   /* FUN_0040654c */
extern word_t sk_rt_00406574();   /* FUN_00406574 */
extern word_t sk_rt_00406590();   /* FUN_00406590 */
extern word_t sk_rt_00406608();   /* FUN_00406608 */
extern word_t sk_rt_004066bc();   /* FUN_004066bc */
extern word_t sk_rt_00406704();   /* FUN_00406704 */
extern word_t sk_rt_0040676c();   /* FUN_0040676c */
extern sk_u128_t sk_rt_0040678c();   /* FUN_0040678c */
extern word_t sk_rt_0040679c();   /* FUN_0040679c */
extern word_t sk_rt_004067b8();   /* FUN_004067b8 */
extern word_t sk_rt_004067f8();   /* FUN_004067f8 */
extern word_t sk_rt_0040683c();   /* FUN_0040683c */
extern word_t sk_rt_0040684c();   /* FUN_0040684c */
extern word_t sk_rt_0040686c();   /* FUN_0040686c */
extern sk_u128_t sk_rt_00406894();   /* FUN_00406894 */
extern word_t sk_rt_004068bc();   /* FUN_004068bc */
extern word_t sk_rt_004068f4();   /* FUN_004068f4 */
extern word_t sk_rt_0040691c();   /* FUN_0040691c */
extern word_t sk_rt_004069b0();   /* FUN_004069b0 */
extern word_t sk_rt_004069c4();   /* FUN_004069c4 */
extern word_t sk_rt_004069ec();   /* FUN_004069ec */
extern word_t sk_rt_00406a24();   /* FUN_00406a24 */
extern word_t sk_rt_00406ab4();   /* FUN_00406ab4 */
extern sk_u128_t sk_rt_00406ac4();   /* FUN_00406ac4 */
extern sk_u128_t sk_rt_00406b54();   /* FUN_00406b54 */
extern word_t sk_rt_00406bb4();   /* FUN_00406bb4 */
extern word_t sk_rt_00406bd4();   /* FUN_00406bd4 */
extern word_t sk_rt_00406be4();   /* FUN_00406be4 */
extern word_t sk_rt_00406c1c();   /* FUN_00406c1c */
extern word_t sk_rt_00406c5c();   /* FUN_00406c5c */
extern word_t sk_rt_00406cf0();   /* FUN_00406cf0 */
extern word_t sk_rt_00406d70();   /* FUN_00406d70 */
extern word_t sk_rt_00406dd0();   /* FUN_00406dd0 */
extern word_t sk_rt_00406e34();   /* FUN_00406e34 */
extern sk_u128_t sk_rt_00406e64();   /* FUN_00406e64 */
extern word_t sk_rt_00406e8c();   /* FUN_00406e8c */
extern word_t sk_rt_00406ee4();   /* FUN_00406ee4 */
extern word_t sk_rt_00406f08();   /* FUN_00406f08 */
extern word_t sk_rt_00406f50();   /* FUN_00406f50 */
extern word_t sk_rt_00406fb0();   /* FUN_00406fb0 */
extern sk_u128_t sk_rt_00406fd4();   /* FUN_00406fd4 */
extern word_t sk_rt_00406fe0();   /* FUN_00406fe0 */
extern sk_u128_t sk_rt_00407000();   /* FUN_00407000 */
extern word_t sk_rt_0040700c();   /* FUN_0040700c */
extern word_t sk_rt_00407018();   /* FUN_00407018 */
extern word_t sk_rt_00407030();   /* FUN_00407030 */
extern word_t sk_rt_004070a0();   /* FUN_004070a0 */
extern word_t sk_rt_004070d8();   /* FUN_004070d8 */
extern word_t sk_rt_004070e4();   /* FUN_004070e4 */
extern word_t sk_rt_00407100();   /* FUN_00407100 */
extern word_t sk_rt_0040711c();   /* FUN_0040711c */
extern sk_u128_t sk_rt_00407128();   /* FUN_00407128 */
extern word_t sk_rt_004071c0();   /* FUN_004071c0 */
extern word_t sk_rt_004071d0();   /* FUN_004071d0 */
extern word_t sk_rt_00407214();   /* FUN_00407214 */
extern word_t sk_rt_00407248();   /* FUN_00407248 */
extern word_t sk_rt_00407280();   /* FUN_00407280 */
extern word_t sk_rt_004072c0();   /* FUN_004072c0 */
extern word_t sk_rt_00407374();   /* FUN_00407374 */
extern word_t sk_rt_00407444();   /* FUN_00407444 */
extern word_t sk_rt_00407450();   /* FUN_00407450 */
extern word_t sk_rt_00407478();   /* FUN_00407478 */
extern sk_u128_t sk_rt_00407484();   /* FUN_00407484 */
extern word_t sk_rt_004074c4();   /* FUN_004074c4 */
extern word_t sk_rt_00407504();   /* FUN_00407504 */
extern word_t sk_rt_00407520();   /* FUN_00407520 */
extern word_t sk_rt_0040752c();   /* FUN_0040752c */
extern word_t sk_rt_00407594();   /* FUN_00407594 */
extern word_t sk_rt_004075a4();   /* FUN_004075a4 */
extern word_t sk_rt_004075d0();   /* FUN_004075d0 */
extern word_t sk_rt_00407604();   /* FUN_00407604 */
extern word_t sk_rt_00407610();   /* FUN_00407610 */
extern word_t sk_rt_0040764c();   /* FUN_0040764c */
extern word_t sk_rt_00407700();   /* FUN_00407700 */
extern word_t sk_rt_00407764();   /* FUN_00407764 */
extern word_t sk_rt_004077cc();   /* FUN_004077cc */
extern word_t sk_rt_00407814();   /* FUN_00407814 */
extern word_t sk_rt_00407830();   /* FUN_00407830 */
extern word_t sk_rt_0040785c();   /* FUN_0040785c */
extern word_t sk_rt_00407878();   /* FUN_00407878 */
extern word_t sk_rt_004078c0();   /* FUN_004078c0 */
extern word_t sk_rt_004078e8();   /* FUN_004078e8 */
extern word_t sk_rt_004078f4();   /* FUN_004078f4 */
extern word_t sk_rt_0040790c();   /* FUN_0040790c */
extern word_t sk_rt_00407960();   /* FUN_00407960 */
extern word_t sk_rt_00407990();   /* FUN_00407990 */
extern word_t sk_rt_004079a8();   /* FUN_004079a8 */
extern word_t sk_rt_004079b4();   /* FUN_004079b4 */
extern word_t sk_rt_004079cc();   /* FUN_004079cc */
extern word_t sk_rt_00407ac4();   /* FUN_00407ac4 */
extern word_t sk_rt_00407adc();   /* FUN_00407adc */
extern word_t sk_rt_00407afc();   /* FUN_00407afc */
extern word_t sk_rt_00407b18();   /* FUN_00407b18 */
extern word_t sk_rt_00407b48();   /* FUN_00407b48 */
extern word_t sk_rt_00407b80();   /* FUN_00407b80 */
extern word_t sk_rt_00407bf8();   /* FUN_00407bf8 */
extern word_t sk_rt_00407c04();   /* FUN_00407c04 */
extern word_t sk_rt_00407c78();   /* FUN_00407c78 */
extern word_t sk_rt_00407c8c();   /* FUN_00407c8c */
extern word_t sk_rt_00407ca0();   /* FUN_00407ca0 */
extern sk_u128_t sk_rt_00407ce4();   /* FUN_00407ce4 */
extern word_t sk_rt_00407d14();   /* FUN_00407d14 */
extern word_t sk_rt_00407db0();   /* FUN_00407db0 */
extern word_t sk_rt_00407e10();   /* FUN_00407e10 */
extern word_t sk_rt_00407e58();   /* FUN_00407e58 */
extern word_t sk_rt_00407ea0();   /* FUN_00407ea0 */
extern sk_u128_t sk_rt_00407f60();   /* FUN_00407f60 */
extern sk_u128_t sk_rt_00407fcc();   /* FUN_00407fcc */
extern word_t sk_rt_00408038();   /* FUN_00408038 */
extern word_t sk_rt_0040807c();   /* FUN_0040807c */
extern word_t sk_rt_00408094();   /* FUN_00408094 */
extern word_t sk_rt_004080b0();   /* FUN_004080b0 */
extern word_t sk_rt_004080cc();   /* FUN_004080cc */
extern word_t sk_rt_00408108();   /* FUN_00408108 */
extern word_t sk_rt_004081b4();   /* FUN_004081b4 */
extern word_t sk_rt_00408280();   /* FUN_00408280 */
extern word_t sk_rt_004082a8();   /* FUN_004082a8 */
extern word_t sk_rt_00408328();   /* FUN_00408328 */
extern sk_u128_t sk_rt_00408354();   /* FUN_00408354 */
extern word_t sk_rt_00408374();   /* FUN_00408374 */
extern word_t sk_rt_0040838c();   /* FUN_0040838c */
extern word_t sk_rt_004083c0();   /* FUN_004083c0 */
extern word_t sk_rt_004083cc();   /* FUN_004083cc */
extern word_t sk_rt_004083d8();   /* FUN_004083d8 */
extern word_t sk_rt_004083f0();   /* FUN_004083f0 */
extern word_t sk_rt_00408404();   /* FUN_00408404 */
extern word_t sk_rt_00408410();   /* FUN_00408410 */
extern word_t sk_rt_00408440();   /* FUN_00408440 */
extern word_t sk_rt_00408460();   /* FUN_00408460 */
extern word_t sk_rt_00408560();   /* FUN_00408560 */
extern word_t sk_rt_004085b4();   /* FUN_004085b4 */
extern word_t sk_rt_0040880c();   /* FUN_0040880c */
extern word_t sk_rt_00408898();   /* FUN_00408898 */
extern word_t sk_rt_004088a0();   /* FUN_004088a0 */
extern word_t sk_rt_00408c4c();   /* FUN_00408c4c */
extern word_t sk_rt_00408db8();   /* FUN_00408db8 */
extern word_t sk_rt_00409354();   /* FUN_00409354 */
extern word_t sk_rt_00409484();   /* FUN_00409484 */
extern word_t sk_rt_00409c10();   /* FUN_00409c10 */
extern word_t sk_rt_00409c1c();   /* FUN_00409c1c */
extern word_t sk_rt_00409c24();   /* FUN_00409c24 */
extern word_t sk_rt_0040a688();   /* FUN_0040a688 */
extern word_t sk_rt_0040a8d8();   /* FUN_0040a8d8 */
extern word_t sk_rt_0040a9b0();   /* FUN_0040a9b0 */
extern word_t sk_rt_0040a9f4();   /* FUN_0040a9f4 */
extern word_t sk_rt_0040aa98();   /* FUN_0040aa98 */
extern word_t sk_rt_0040aac8();   /* FUN_0040aac8 */
extern word_t sk_rt_0040ab60();   /* FUN_0040ab60 */
extern word_t sk_rt_0040ada4();   /* FUN_0040ada4 */
extern word_t sk_rt_0040bb18();   /* FUN_0040bb18 */
extern word_t sk_rt_0040bd24();   /* FUN_0040bd24 */
extern word_t sk_rt_0040d07c();   /* FUN_0040d07c */
extern word_t sk_rt_002298d4();   /* thunk_FUN_002298d4 */
extern word_t sk_rt_00409414();   /* thunk_FUN_00409414 */

/* in-slice forward declarations (functions defined below) */
void sk_slice57_003e68f0();
void sk_slice57_003e6be8();
void sk_slice57_003e6cbc();
void sk_slice57_003e6cf0();
void sk_slice57_003e6d08();
void sk_slice57_003e6da8();
void sk_slice57_003e6dd0();
void sk_slice57_003e6ecc();
void sk_slice57_003e6fc8();
void sk_slice57_003e7228();
void sk_slice57_003e74fc();
void sk_slice57_003e788c();
void sk_slice57_003e7b14();
void sk_slice57_003e7d20();
void sk_slice57_003e838c();
void sk_slice57_003e86c8();
void sk_slice57_003e89f0();
void sk_slice57_003e8e28();
void sk_slice57_003e90f4();
void sk_slice57_003e9310();
void sk_slice57_003e9c34();
void sk_slice57_003e9d04();
void sk_slice57_003e9db0();
void sk_slice57_003e9de0();
void sk_slice57_003e9df8();
void sk_slice57_003e9e74();
void sk_slice57_003e9f40();
void sk_slice57_003e9fcc();
void sk_slice57_003ea0a4();
void sk_slice57_003ea260();
void sk_slice57_003ea494();
void sk_slice57_003ea4ec();
void sk_slice57_003ea5a8();
void sk_slice57_003ea6ec();
void sk_slice57_003ea8f4();
void sk_slice57_003eab58();
void sk_slice57_003ead6c();
void sk_slice57_003eae24();
void sk_slice57_003eaef4();
void sk_slice57_003eaf34();
void sk_slice57_003eaf4c();
void sk_slice57_003eafc8();
void sk_slice57_003eb0a4();
void sk_slice57_003eb120();
void sk_slice57_003eb1d8();
void sk_slice57_003eb398();
void sk_slice57_003eb594();
void sk_slice57_003eb68c();
void sk_slice57_003eb7c4();
void sk_slice57_003eb9c8();
void sk_slice57_003ebbd4();
void sk_slice57_003ebd9c();
void sk_slice57_003ebe6c();
sk_u128_t sk_slice57_003ebf10();
void sk_slice57_003ebfe8();
void sk_slice57_003ec094();
void sk_slice57_003ec098();
uint8_t * sk_slice57_003ec0c4();
void sk_slice57_003ec12c();
void sk_slice57_003ec130();
void sk_slice57_003ec144();
void sk_slice57_003ec148();
void sk_slice57_003ec178();
void sk_slice57_003ec20c();
void sk_slice57_003ec438();
void sk_slice57_003ec4dc();
void sk_slice57_003ec598();
void sk_slice57_003ec6c8();
void sk_slice57_003ec708();
void sk_slice57_003ec730();
void sk_slice57_003ec758();
void sk_slice57_003ec780();
void sk_slice57_003ec7bc();
void sk_slice57_003ec7fc();
void sk_slice57_003ec824();
void sk_slice57_003ec84c();
void sk_slice57_003ec874();
void sk_slice57_003ec8a0();
void sk_slice57_003ec8c8();
void sk_slice57_003ec918();
int64_t sk_slice57_003ec9c4();
void sk_slice57_003ecb1c();
void sk_slice57_003ecb20();
void sk_slice57_003ecb48();
void sk_slice57_003ecb4c();
void sk_slice57_003ecb64();
uint64_t sk_slice57_003ecc18();
void sk_slice57_003eccc4();
uint32_t sk_slice57_003ecd44();
void sk_slice57_003ecd98();
void sk_slice57_003ecd9c();
void sk_slice57_003ecddc();
void sk_slice57_003ed0a8();
void sk_slice57_003ed0ec();
void sk_slice57_003ed14c();
void sk_slice57_003ed1a4();
void sk_slice57_003ed2dc();
void sk_slice57_003ed340();
void sk_slice57_003ed4d4();
void sk_slice57_003ed5f8();
void sk_slice57_003ed6d0();
void sk_slice57_003ed930();
void sk_slice57_003edad4();
void sk_slice57_003edf5c();
void sk_slice57_003ee090();
void sk_slice57_003ee234();
void sk_slice57_003ee310();
void sk_slice57_003ee3c8();
void sk_slice57_003ee47c();
void sk_slice57_003ee520();
void sk_slice57_003ee5e8();
void sk_slice57_003ee688();
void sk_slice57_003ee818();
void sk_slice57_003ee8e4();
void sk_slice57_003eead0();
void sk_slice57_003eeb6c();
void sk_slice57_003eebf0();
void sk_slice57_003eec90();
void sk_slice57_003eed30();
void sk_slice57_003eeef4();

/* void FUN_003e68f0(void) */

void sk_slice57_003e68f0()

{
  word_t uv1;
  int64_t ln2;
  word_t uv3;
  word_t *wp4;
  word_t xr_x1;
  word_t uv5;
  code_t *jt0;
  code_t *jt;
  word_t xr_x17;
  word_t uv6;
  int64_t ctx;
  sk_u128_t auVar7;
  
  uv3 = sk_rt_00407ca0();
  sk_rt_0040700c();
  if ((*(uint8_t *)(ctx + 0xe5) & 1) == 0) {
    (**(code_t **)(*(int64_t *)(ctx + 0x80) + 8))
              (*(word_t *)(ctx + 0x88),*(word_t *)(ctx + 0x60));
    if ((*(uint8_t *)(ctx + 0xe4) & 1) == 0) {
      ln2 = *(int64_t *)(ctx + 0x40);
      sk_rt_0040652c();
      sk_rt_00406608();
      sk_rt_004083cc();
      uv3 = sk_rt_00406e8c();
      *(word_t *)(ctx + 0xb0) = uv3;
      sk_rt_00406288();
      sk_rt_0040bb18(*(uint32_t *)(ln2 + 4));
      wp4 = (word_t *)sk_rt_00406fe0();
      *(word_t **)(ctx + 0xb8) = wp4;
      *wp4 = xr_x17;
      sk_rt_00407830();
      sk_rt_004067b8();
                    /* WARNING: Could not recover jumptable at 0x003e6a3c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      ((code_t)jt)();
      return;
    }
    uv5 = 1;
  }
  else {
    (**(code_t **)(ctx + 0xc0))
              (*(word_t *)(ctx + 200),*(word_t *)(ctx + 0x10),
               *(word_t *)(ctx + 0x88),*(word_t *)(ctx + 0x60));
    sk_rt_00407bf8();
    uv5 = xr_x1;
  }
  uv6 = *(word_t *)(ctx + 0x78);
  uv1 = *(word_t *)(ctx + 0x58);
  sk_rt_004075a4(*(word_t *)(ctx + 0x10),uv5);
  sk_rt_0040bd24(uv6);
  sk_rt_0040bd24(uv1);
  auVar7 = sk_rt_00406e64();
  sk_rt_00407e58(auVar7.lo,auVar7.hi,uv3);
                    /* WARNING: Could not recover jumptable at 0x003e69a8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  ((code_t)jt0)();
  return;
}



/* void FUN_003e6be8(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4, undefined8 param_5) */

void sk_slice57_003e6be8(word_t  param_1, word_t  param_2, word_t  param_3, word_t  param_4, word_t  param_5)

{
  int64_t *lp1;
  int64_t ctx;
  
  *(word_t *)(ctx + 0x10) = param_4;
  lp1 = (int64_t *)sk_rt_0040bb18(sk_d_005a00bc);
  *(int64_t **)(ctx + 0x18) = lp1;
  *lp1 = ctx;
  lp1[1] = (int64_t)(word_t)&sk_d_004060bc;
  sk_rt_003e63a8(lp1,param_1,param_2,param_3,param_5);
  return;
}



/* void FUN_003e6cbc(void) */

void sk_slice57_003e6cbc()

{
  sk_rt_00406574();
  sk_slice57_003e6cf0();
  sk_rt_0036b270();
  return;
}



/* void FUN_003e6cf0(void) */

void sk_slice57_003e6cf0()

{
  sk_slice57_003e6d08();
  return;
}



/* void FUN_003e6d08(void) */

void sk_slice57_003e6d08()

{
  word_t *stack_addr;
  word_t *wp1;
  int64_t ln2;
  word_t xr_x1;
  word_t in_r3;
  code_t *in_r7;
  int64_t xr_x8;
  int64_t xr_x16;
  word_t in_r24;
  sk_u128_t auVar3;
  
  auVar3 = sk_rt_0034d2b4();
  sk_rt_003509c8(in_r3,auVar3.lo,auVar3.lo);
  (**(code_t **)(xr_x16 + 0x20))(xr_x8,xr_x1,in_r3);
  ln2 = ((code_t)in_r7)(0,stack_addr);
  wp1 = (word_t *)(xr_x8 + *(int32_t *)(ln2 + 0x34));
  *wp1 = auVar3.hi;
  wp1[1] = in_r24;
  return;
}



/* void FUN_003e6da8(long param_1) */

void sk_slice57_003e6da8(int64_t  param_1)

{
  sk_rt_003591d0((int64_t)*(int32_t *)(param_1 + 0x34));
  sk_rt_0009461c();
  return;
}



/* void FUN_003e6dd0(undefined8 param_1,long param_2) */

void sk_slice57_003e6dd0(word_t  param_1, int64_t  param_2)

{
  int32_t iv1;
  word_t uv2;
  int64_t xr_x16;
  int64_t in_r20;
  
  iv1 = *(int32_t *)(param_2 + 0x38);
  sk_rt_00406f08(param_2,*(word_t *)(param_2 + 0x28),*(word_t *)(param_2 + 0x18));
  sk_rt_00377824(0xff);
  sk_rt_00352efc();
  sk_rt_00310d68();
  uv2 = sk_rt_00350404();
                    /* WARNING: Could not recover jumptable at 0x003e6e3c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code_t **)(xr_x16 + 0x10))(param_1,in_r20 + iv1,uv2);
  return;
}



/* void FUN_003e6ecc(long param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4, undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8, code *param_9) */

void sk_slice57_003e6ecc(int64_t  param_1, word_t  param_2, word_t  param_3, word_t  param_4, word_t  param_5, word_t  param_6, word_t  param_7, word_t  param_8, code_t * param_9)

{
  word_t *wp1;
  int32_t iv2;
  int64_t ln3;
  int64_t xr_x16;
  sk_u128_t auVar4;
  word_t stack_slot_128;
  word_t loc_120;
  word_t stack_slot_112;
  word_t loc_104;
  
  stack_slot_128 = param_5;
  loc_120 = param_6;
  stack_slot_112 = param_7;
  loc_104 = param_8;
  ln3 = ((code_t)param_9)(0,&stack_slot_128);
  iv2 = *(int32_t *)(ln3 + 0x38);
  auVar4 = sk_rt_00350500();
  sk_rt_00377824(auVar4.lo,auVar4.hi,param_6,(word_t)&sk_d_00614a5c);
  sk_rt_00350744(param_1 + iv2);
  sk_rt_000839d8();
  *(uint8_t *)(param_1 + *(int32_t *)(ln3 + 0x3c)) = 0;
  auVar4 = sk_rt_0035050c();
  sk_rt_00377824(auVar4.lo,auVar4.hi,param_5,(word_t)&sk_d_00614a5c);
  sk_rt_00349530();
  (**(code_t **)(xr_x16 + 0x20))(param_1,param_2);
  wp1 = (word_t *)(param_1 + *(int32_t *)(ln3 + 0x34));
  *wp1 = param_3;
  wp1[1] = param_4;
  return;
}



/* void FUN_003e6fc8(void) */

void sk_slice57_003e6fc8()

{
  word_t uv1;
  uint64_t uv2;
  int64_t xr_x1;
  int64_t xr_x8;
  int64_t xr_x8_00;
  int64_t xr_x8_01;
  int64_t xr_x8_02;
  int64_t xr_x8_03;
  int64_t xr_x8_04;
  int64_t xr_x8_05;
  word_t xr_x16;
  word_t xr_x16_00;
  word_t xr_x16_01;
  word_t xr_x16_02;
  word_t xr_x16_03;
  word_t xr_x16_04;
  word_t xr_x16_05;
  int64_t ctx;
  uint64_t in_r24;
  
  sk_rt_00407c8c();
  sk_rt_0040700c();
  sk_rt_00407214();
  sk_rt_0007c028();
  *(word_t *)(ctx + 0x30) = xr_x16;
  uv2 = *(int64_t *)(xr_x8 + 0x40) + 0xf;
  uv1 = sk_rt_0040bb18(uv2 & 0xfffffffffffffff0);
  *(word_t *)(ctx + 0x38) = uv1;
  uv1 = sk_rt_0040bb18(uv2 & 0xfffffffffffffff0);
  *(word_t *)(ctx + 0x40) = uv1;
  uv1 = sk_rt_0040bb18(uv2 & 0xfffffffffffffff0);
  *(word_t *)(ctx + 0x48) = uv1;
  *(word_t *)(ctx + 0x50) = *(word_t *)(xr_x1 + 0x20);
  *(word_t *)(ctx + 0x58) = *(word_t *)(xr_x1 + 0x10);
  uv1 = sk_rt_0040807c();
  *(word_t *)(ctx + 0x60) = uv1;
  sk_rt_00350500();
  uv1 = sk_rt_00310d68();
  *(word_t *)(ctx + 0x68) = uv1;
  sk_rt_00352018();
  *(word_t *)(ctx + 0x70) = xr_x16_00;
  uv1 = sk_rt_004078e8(*(word_t *)(xr_x8_00 + 0x40));
  *(word_t *)(ctx + 0x78) = uv1;
  sk_rt_00406f50();
  *(word_t *)(ctx + 0x80) = xr_x16_01;
  uv1 = sk_rt_004078e8(*(word_t *)(xr_x8_01 + 0x40));
  *(word_t *)(ctx + 0x88) = uv1;
  *(word_t *)(ctx + 0x90) = *(word_t *)(xr_x1 + 0x28);
  sk_rt_00350548(0xff);
  uv1 = sk_rt_00377824();
  *(word_t *)(ctx + 0x98) = uv1;
  sk_rt_00350500();
  uv1 = sk_rt_00310d68();
  *(word_t *)(ctx + 0xa0) = uv1;
  sk_rt_00352018();
  *(word_t *)(ctx + 0xa8) = xr_x16_02;
  uv1 = sk_rt_004081b4(*(word_t *)(xr_x8_02 + 0x40));
  *(word_t *)(ctx + 0xb0) = uv1;
  uv1 = sk_rt_0040bb18(in_r24 & 0xfffffffffffffff0);
  *(word_t *)(ctx + 0xb8) = uv1;
  sk_rt_00406f50();
  *(word_t *)(ctx + 0xc0) = xr_x16_03;
  uv2 = *(int64_t *)(xr_x8_03 + 0x40) + 0xf;
  uv1 = sk_rt_0040bb18(uv2 & 0xfffffffffffffff0);
  *(word_t *)(ctx + 200) = uv1;
  uv1 = sk_rt_0040bb18(uv2 & 0xfffffffffffffff0);
  *(word_t *)(ctx + 0xd0) = uv1;
  sk_rt_00350548(0xff);
  uv2 = sk_rt_00377824();
  *(uint64_t *)(ctx + 0xd8) = uv2;
  sk_rt_00350798();
  uv1 = sk_rt_00310d68();
  *(word_t *)(ctx + 0xe0) = uv1;
  sk_rt_00352018();
  *(word_t *)(ctx + 0xe8) = xr_x16_04;
  uv1 = sk_rt_004078e8(*(word_t *)(xr_x8_04 + 0x40));
  *(word_t *)(ctx + 0xf0) = uv1;
  sk_rt_0040683c();
  *(word_t *)(ctx + 0xf8) = xr_x16_05;
  uv1 = sk_rt_00407b48(*(word_t *)(xr_x8_05 + 0x40));
  *(word_t *)(ctx + 0x100) = uv1;
  uv1 = sk_rt_0040bb18(uv2 & 0xfffffffffffffff0);
  *(word_t *)(ctx + 0x108) = uv1;
  sk_rt_00407594();
  sk_rt_00407c78();
  sk_rt_00408db8();
  return;
}



/* void FUN_003e7228(void) */

void sk_slice57_003e7228()

{
  int32_t iv1;
  uint8_t zero_cc;
  word_t uv2;
  word_t *wp3;
  int64_t ln4;
  code_t *jt0;
  word_t xr_x8;
  word_t uv5;
  word_t xr_x9;
  code_t *xr_x9_00;
  code_t *xr_x9_01;
  word_t xr_x10;
  word_t xr_x10_00;
  code_t *xr_x11;
  code_t *xr_x16;
  code_t *xr_x16_00;
  word_t xr_x17;
  word_t xr_x17_00;
  int64_t ctx;
  sk_u128_t auVar6;
  code_t *jt;
  
  uv2 = sk_rt_00407b18();
  auVar6 = sk_rt_00407fcc();
  iv1 = *(int32_t *)(*(int64_t *)(ctx + 0x18) + 0x3c);
  *(int32_t *)(ctx + 0x178) = iv1;
  if ((*(uint8_t *)(*(int64_t *)(ctx + 0x20) + (int64_t)iv1) & 1) != 0) {
    sk_rt_004069ec();
    uv5 = *(word_t *)(ctx + 0x38);
    sk_rt_0040686c();
    sk_rt_0040bd24();
    sk_rt_0040bd24();
    sk_rt_0040bd24();
    sk_rt_0040bd24();
    sk_rt_0040bd24();
    sk_rt_0040bd24();
    sk_rt_0040bd24();
    sk_rt_0040bd24();
    sk_rt_0040bd24(xr_x9);
    sk_rt_0040bd24(xr_x8);
    sk_rt_0040bd24(uv5);
    auVar6 = sk_rt_0040678c();
    sk_rt_00407878(auVar6.lo,auVar6.hi,uv2);
                    /* WARNING: Could not recover jumptable at 0x003e72f0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    ((code_t)jt0)();
    return;
  }
  *(uint32_t *)(ctx + 0x17c) = *(uint32_t *)(*(int64_t *)(ctx + 0x18) + 0x38);
  *(word_t *)(ctx + 0x110) = *(word_t *)(*(int64_t *)(ctx + 0xe8) + 0x10);
  sk_rt_00408460(auVar6.lo,auVar6.hi,*(word_t *)(ctx + 0xe0));
  ((code_t)xr_x11)();
  sk_rt_00406420();
  if ((bool)zero_cc) {
    uv5 = *(word_t *)(ctx + 0x50);
    ln4 = *(int64_t *)(ctx + 0x58);
    sk_rt_00353930(*(word_t *)(ctx + 0xe8),*(word_t *)(ctx + 0xf0),
                 *(word_t *)(ctx + 0xe0));
    *(code_t **)(ctx + 0x138) = xr_x9_00;
    *(word_t *)(ctx + 0x140) = xr_x10;
    ((code_t)xr_x9_00)();
    sk_rt_0040652c();
    sk_rt_00406608();
    sk_rt_004068f4();
    sk_rt_00406268();
    sk_rt_0040bb18(*(uint32_t *)(ln4 + 4));
    wp3 = (word_t *)sk_rt_00406fe0();
    *(word_t **)(ctx + 0x148) = wp3;
    *wp3 = xr_x17;
    auVar6 = sk_rt_00406b54();
    jt = xr_x16;
  }
  else {
    uv5 = *(word_t *)(ctx + 0xd8);
    auVar6 = sk_rt_00406894(*(word_t *)(ctx + 0xf8),*(word_t *)(ctx + 0x108),
                          *(word_t *)(ctx + 0xf0));
    *(code_t **)(ctx + 0x118) = xr_x9_01;
    *(word_t *)(ctx + 0x120) = xr_x10_00;
    ((code_t)xr_x9_01)(auVar6.lo,auVar6.hi,uv5);
    uv5 = sk_rt_004067f8();
    sk_rt_003fcc1c();
    ln4 = sk_rt_004062c8();
    sk_rt_0040bb18(*(uint32_t *)(ln4 + 4));
    wp3 = (word_t *)sk_rt_00406fe0();
    *(word_t **)(ctx + 0x128) = wp3;
    *wp3 = xr_x17_00;
    auVar6 = sk_rt_00406ac4();
    jt = xr_x16_00;
  }
  sk_rt_00407878(auVar6.lo,auVar6.hi,uv5,jt,uv2);
                    /* WARNING: Could not recover jumptable at 0x003e7420. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  ((code_t)jt)();
  return;
}



/* void FUN_003e74fc(void) */

void sk_slice57_003e74fc()

{
  word_t uv1;
  word_t uv2;
  uint8_t zero_cc;
  word_t uv3;
  word_t *wp4;
  int64_t ln5;
  code_t *jt;
  code_t *jt0;
  code_t *xr_x8;
  code_t *xr_x8_00;
  code_t *xr_x8_01;
  word_t xr_x8_02;
  word_t uv6;
  code_t *xr_x9;
  code_t *xr_x9_00;
  word_t xr_x9_01;
  code_t *xr_x9_02;
  word_t xr_x10;
  word_t xr_x10_00;
  word_t xr_x17;
  word_t xr_x17_00;
  word_t uv7;
  int64_t ln8;
  int64_t ctx;
  int64_t ln9;
  word_t *wp10;
  sk_u128_t auVar11;
  
  uv3 = sk_rt_0040785c();
  sk_rt_00407adc();
  uv7 = *(word_t *)(ctx + 0xb8);
  sk_rt_00406be4();
  if ((bool)zero_cc) {
    ln5 = *(int64_t *)(ctx + 0xa8);
    (**(code_t **)(*(int64_t *)(ctx + 0xf8) + 8))
              (*(word_t *)(ctx + 0x108),*(word_t *)(ctx + 0xd8));
    sk_rt_003507e0(*(word_t *)(ln5 + 8));
    ((code_t)xr_x8)();
    sk_rt_00407764();
    ((code_t)xr_x8_00)();
    jt0 = *(code_t **)(ctx + 0xd8);
    sk_rt_00350744(*(int64_t *)(ctx + 0x20) + (int64_t)*(int32_t *)(ctx + 0x17c));
    auVar11 = sk_rt_000839d8();
    sk_rt_00406fb0(*(word_t *)(ctx + 0x110),auVar11.lo,auVar11.hi,
                 *(word_t *)(ctx + 0xe0));
    ((code_t)xr_x8_01)();
    sk_rt_00406420();
    if ((bool)zero_cc) {
      ln5 = *(int64_t *)(ctx + 0x58);
      sk_rt_00353930(*(word_t *)(ctx + 0xe8),*(word_t *)(ctx + 0xf0),
                   *(word_t *)(ctx + 0xe0));
      *(code_t **)(ctx + 0x138) = xr_x9;
      *(word_t *)(ctx + 0x140) = xr_x10;
      ((code_t)xr_x9)();
      sk_rt_0040652c();
      sk_rt_00406608();
      sk_rt_004068f4();
      sk_rt_00406268();
      sk_rt_0040bb18(*(uint32_t *)(ln5 + 4));
      wp4 = (word_t *)sk_rt_00406fe0();
      *(word_t **)(ctx + 0x148) = wp4;
      *wp4 = xr_x17;
      sk_rt_00406b54();
    }
    else {
      uv3 = *(word_t *)(ctx + 0xd8);
      auVar11 = sk_rt_00406894(*(word_t *)(ctx + 0xf8),*(word_t *)(ctx + 0x108),
                             *(word_t *)(ctx + 0xf0));
      *(code_t **)(ctx + 0x118) = xr_x9_02;
      *(word_t *)(ctx + 0x120) = xr_x10_00;
      ((code_t)xr_x9_02)(auVar11.lo,auVar11.hi,uv3);
      sk_rt_004067f8();
      sk_rt_003fcc1c();
      ln5 = sk_rt_004062c8();
      sk_rt_0040bb18(*(uint32_t *)(ln5 + 4));
      wp4 = (word_t *)sk_rt_00406fe0();
      *(word_t **)(ctx + 0x128) = wp4;
      *wp4 = xr_x17_00;
      sk_rt_00406ac4();
    }
    sk_rt_00408404();
    sk_rt_00407504();
                    /* WARNING: Could not recover jumptable at 0x003e77cc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    ((code_t)jt0)();
    return;
  }
  ln9 = (int64_t)*(int32_t *)(ctx + 0x17c);
  uv6 = *(word_t *)(ctx + 0xe0);
  ln5 = *(int64_t *)(ctx + 0xe8);
  uv1 = *(word_t *)(ctx + 0xd0);
  uv2 = *(word_t *)(ctx + 0xd8);
  ln8 = *(int64_t *)(ctx + 0x20);
  wp10 = (word_t *)(*(int64_t *)(ctx + 0xc0) + 0x20);
  jt0 = (code_t *)*wp10;
  sk_rt_00350968(uv1);
  ((code_t)jt0)();
  wp4 = (word_t *)(ln5 + 8);
  (*(code_t *)*wp4)(ln8 + ln9,uv6);
  sk_rt_00408440();
  ((code_t)xr_x9_00)();
  sk_rt_00350750(ln8 + ln9);
  sk_rt_0040764c();
  ((code_t)jt0)();
  sk_rt_004069ec();
  uv6 = *(word_t *)(ctx + 0x38);
  sk_rt_00406cf0();
  sk_rt_0040bd24(uv7);
  sk_rt_0040bd24(ln8);
  sk_rt_0040bd24(jt0);
  sk_rt_0040bd24(uv2);
  sk_rt_0040bd24(uv1);
  sk_rt_0040bd24(ln9);
  sk_rt_0040bd24(wp4);
  sk_rt_0040bd24(wp10);
  sk_rt_0040bd24(xr_x9_01);
  sk_rt_0040bd24(xr_x8_02);
  sk_rt_0040bd24(uv6);
  auVar11 = sk_rt_0040678c();
  sk_rt_00407504(auVar11.lo,auVar11.hi,uv3);
                    /* WARNING: Could not recover jumptable at 0x003e773c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  ((code_t)jt)();
  return;
}



/* void FUN_003e788c(void) */

void sk_slice57_003e788c()

{
  int64_t ln1;
  int64_t ln2;
  uint8_t zero_cc;
  word_t uv3;
  word_t uv4;
  word_t *wp5;
  code_t *jt0;
  code_t *jt;
  word_t xr_x8;
  int64_t xr_x8_00;
  code_t *xr_x9;
  word_t xr_x9_00;
  code_t *xr_x9_01;
  code_t *xr_x16;
  word_t xr_x17;
  word_t uv6;
  int64_t ctx;
  sk_u128_t auVar7;
  
  uv3 = sk_rt_00407b18();
  sk_rt_00407fcc();
  uv6 = *(word_t *)(ctx + 0x60);
  uv4 = sk_rt_00406420();
  if ((bool)zero_cc) {
    sk_rt_0040711c(*(word_t *)(ctx + 0x70),uv4,*(word_t *)(ctx + 0x68));
    ((code_t)xr_x9)();
    sk_rt_004069ec();
    uv4 = *(word_t *)(ctx + 0x38);
    sk_rt_0040686c();
    sk_rt_0040bd24(uv6);
    sk_rt_0040bd24();
    sk_rt_0040bd24();
    sk_rt_0040bd24();
    sk_rt_0040bd24();
    sk_rt_0040bd24();
    sk_rt_0040bd24();
    sk_rt_0040bd24();
    sk_rt_0040bd24(xr_x9_00);
    sk_rt_0040bd24(xr_x8);
    sk_rt_0040bd24(uv4);
    auVar7 = sk_rt_0040678c();
    sk_rt_00407878(auVar7.lo,auVar7.hi,uv3);
                    /* WARNING: Could not recover jumptable at 0x003e7964. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    ((code_t)jt0)();
    return;
  }
  ln1 = *(int64_t *)(ctx + 0x18);
  ln2 = *(int64_t *)(ctx + 0x20);
  sk_rt_00406bd4(*(word_t *)(ctx + 0x80),*(word_t *)(ctx + 0x88));
  ((code_t)xr_x9_01)();
  sk_rt_004062a8(*(word_t *)(ln2 + *(int32_t *)(ln1 + 0x34)));
  sk_rt_0040bb18(*(uint32_t *)(xr_x8_00 + 4));
  wp5 = (word_t *)sk_rt_00406fe0();
  *(word_t **)(ctx + 0x158) = wp5;
  *wp5 = xr_x17;
  wp5[1] = (word_t)&sk_lab_003e7a08;
  jt = xr_x16;
  sk_rt_00407878(*(word_t *)(ctx + 0x40),*(word_t *)(ctx + 0x88),xr_x16,
               uv3);
                    /* WARNING: Could not recover jumptable at 0x003e7a04. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  ((code_t)jt)();
  return;
}



/* void FUN_003e7b14(void) */

void sk_slice57_003e7b14()

{
  word_t uv1;
  int64_t ln2;
  word_t *wp3;
  code_t *jt;
  code_t *xr_x8;
  code_t *xr_x9;
  code_t *xr_x9_00;
  word_t xr_x17;
  word_t uv4;
  word_t uv5;
  int64_t ctx;
  word_t uv6;
  sk_u128_t auVar7;
  
  sk_rt_004079cc();
  uv1 = sk_rt_004070d8();
  uv4 = *(word_t *)(ctx + 0xd8);
  uv5 = *(word_t *)(ctx + 0x90);
  ln2 = *(int64_t *)(ctx + 0x30);
  uv6 = *(word_t *)(ctx + 0x28);
  auVar7 = sk_rt_00407ce4(uv1,*(word_t *)(ctx + 0x40));
  ((code_t)xr_x9)(auVar7.lo,auVar7.hi,uv6);
  auVar7 = sk_rt_00350518(*(word_t *)(ln2 + 0x10));
  ((code_t)xr_x8)(auVar7.lo,auVar7.hi,uv6);
  sk_rt_004070e4(uv5);
  ((code_t)xr_x9_00)(uv6,uv5);
  sk_rt_004068bc();
  sk_rt_00377bec(uv5,uv6,uv4);
  sk_rt_003fcc1c();
  ln2 = sk_rt_004062c8();
  sk_rt_0040bb18(*(uint32_t *)(ln2 + 4));
  wp3 = (word_t *)sk_rt_00406fe0();
  *(word_t **)(ctx + 0x168) = wp3;
  *wp3 = xr_x17;
  wp3[1] = (word_t)&sk_lab_003e7c34;
  sk_rt_00407814(*(word_t *)(ctx + 0xb0),*(word_t *)(ctx + 0xd8));
  sk_rt_004078f4();
                    /* WARNING: Could not recover jumptable at 0x003e7c30. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  ((code_t)jt)();
  return;
}



/* void FUN_003e7d20(void) */

void sk_slice57_003e7d20()

{
  word_t uv1;
  word_t uv2;
  word_t uv3;
  word_t uv4;
  uint8_t zero_cc;
  word_t uv5;
  word_t *wp6;
  int64_t ln7;
  code_t *jt;
  code_t *jt0;
  code_t *xr_x8;
  code_t *xr_x8_00;
  code_t *xr_x8_01;
  word_t xr_x8_02;
  word_t uv8;
  code_t *xr_x9;
  word_t xr_x9_00;
  code_t *xr_x9_01;
  word_t xr_x10;
  word_t xr_x10_00;
  word_t xr_x17;
  word_t xr_x17_00;
  word_t uv9;
  int64_t ctx;
  code_t *fptr10;
  int64_t ln11;
  sk_u128_t auVar12;
  
  uv5 = sk_rt_0040785c();
  sk_rt_00407adc();
  uv9 = *(word_t *)(ctx + 0xb0);
  sk_rt_00406be4();
  if ((bool)zero_cc) {
    jt0 = *(code_t **)(ctx + 0x138);
    ln7 = *(int64_t *)(ctx + 0xa8);
    (**(code_t **)(*(int64_t *)(ctx + 0xf8) + 8))
              (*(word_t *)(ctx + 0x100),*(word_t *)(ctx + 0xd8));
    sk_rt_003507e0(*(word_t *)(ln7 + 8));
    ((code_t)xr_x8)();
    sk_rt_00408410();
    ((code_t)jt0)();
    jt0 = *(code_t **)(ctx + 0xd8);
    sk_rt_00350744(*(int64_t *)(ctx + 0x20) + (int64_t)*(int32_t *)(ctx + 0x17c));
    auVar12 = sk_rt_000839d8();
    sk_rt_00406fb0(*(word_t *)(ctx + 0x110),auVar12.lo,auVar12.hi,
                 *(word_t *)(ctx + 0xe0));
    ((code_t)xr_x8_00)();
    sk_rt_00406420();
    if ((bool)zero_cc) {
      ln7 = *(int64_t *)(ctx + 0x58);
      sk_rt_00353930(*(word_t *)(ctx + 0xe8),*(word_t *)(ctx + 0xf0),
                   *(word_t *)(ctx + 0xe0));
      *(code_t **)(ctx + 0x138) = xr_x9;
      *(word_t *)(ctx + 0x140) = xr_x10;
      ((code_t)xr_x9)();
      sk_rt_0040652c();
      sk_rt_00406608();
      sk_rt_004068f4();
      sk_rt_00406268();
      sk_rt_0040bb18(*(uint32_t *)(ln7 + 4));
      wp6 = (word_t *)sk_rt_00406fe0();
      *(word_t **)(ctx + 0x148) = wp6;
      *wp6 = xr_x17;
      sk_rt_00406b54();
    }
    else {
      uv5 = *(word_t *)(ctx + 0xd8);
      auVar12 = sk_rt_00406894(*(word_t *)(ctx + 0xf8),*(word_t *)(ctx + 0x108),
                             *(word_t *)(ctx + 0xf0));
      *(code_t **)(ctx + 0x118) = xr_x9_01;
      *(word_t *)(ctx + 0x120) = xr_x10_00;
      ((code_t)xr_x9_01)(auVar12.lo,auVar12.hi,uv5);
      sk_rt_004067f8();
      sk_rt_003fcc1c();
      ln7 = sk_rt_004062c8();
      sk_rt_0040bb18(*(uint32_t *)(ln7 + 4));
      wp6 = (word_t *)sk_rt_00406fe0();
      *(word_t **)(ctx + 0x128) = wp6;
      *wp6 = xr_x17_00;
      sk_rt_00406ac4();
    }
    sk_rt_00408404();
    sk_rt_00407504();
                    /* WARNING: Could not recover jumptable at 0x003e7fe0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    ((code_t)jt0)();
    return;
  }
  jt0 = *(code_t **)(ctx + 0x138);
  uv8 = *(word_t *)(ctx + 0x140);
  ln7 = (int64_t)*(int32_t *)(ctx + 0x17c);
  uv1 = *(word_t *)(ctx + 0xf8);
  uv2 = *(word_t *)(ctx + 0xd8);
  uv3 = *(word_t *)(ctx + 0xe0);
  uv4 = *(word_t *)(ctx + 200);
  ln11 = *(int64_t *)(ctx + 0x20);
  wp6 = (word_t *)(*(int64_t *)(ctx + 0xc0) + 0x20);
  fptr10 = (code_t *)*wp6;
  sk_rt_00350968(uv4);
  ((code_t)fptr10)();
  ((code_t)jt0)(uv8,ln11 + ln7,uv3);
  sk_rt_004083f0();
  ((code_t)xr_x8_01)();
  sk_rt_00350750(ln11 + ln7);
  sk_rt_0040764c();
  ((code_t)fptr10)();
  sk_rt_004069ec();
  uv8 = *(word_t *)(ctx + 0x38);
  sk_rt_00406cf0();
  sk_rt_0040bd24(uv9);
  sk_rt_0040bd24(uv1);
  sk_rt_0040bd24(fptr10);
  sk_rt_0040bd24(uv2);
  sk_rt_0040bd24(uv4);
  sk_rt_0040bd24(ln7);
  sk_rt_0040bd24(wp6);
  sk_rt_0040bd24(ln11);
  sk_rt_0040bd24(xr_x9_00);
  sk_rt_0040bd24(xr_x8_02);
  sk_rt_0040bd24(uv8);
  auVar12 = sk_rt_0040678c();
  sk_rt_00407504(auVar12.lo,auVar12.hi,uv5);
                    /* WARNING: Could not recover jumptable at 0x003e7f50. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  ((code_t)jt)();
  return;
}



/* void FUN_003e838c(undefined8 param_1,undefined8 param_2,undefined8 param_3,long param_4) */

void sk_slice57_003e838c(word_t  param_1, word_t  param_2, word_t  param_3, int64_t  param_4, word_t param_5)

{
  word_t uv1;
  uint64_t uv2;
  uint64_t uv3;
  int64_t xr_x1;
  int64_t ln4;
  int64_t xr_x8;
  int64_t xr_x8_00;
  int64_t xr_x8_01;
  int64_t xr_x8_02;
  int64_t xr_x8_03;
  int64_t xr_x8_04;
  int64_t xr_x8_05;
  int64_t xr_x8_06;
  int64_t xr_x8_07;
  code_t *xr_x8_08;
  word_t xr_x8_09;
  word_t xr_x8_10;
  word_t xr_x16;
  word_t xr_x16_00;
  word_t xr_x16_01;
  word_t xr_x16_02;
  word_t xr_x16_03;
  word_t xr_x16_04;
  word_t xr_x16_05;
  word_t xr_x16_06;
  word_t xr_x16_07;
  uint64_t in_r20;
  word_t uv5;
  int64_t ctx;
  
  sk_rt_004079cc();
  sk_rt_004070d8();
  ln4 = param_4;
  sk_rt_0040752c();
  uv5 = *(word_t *)(ln4 + 0x18);
  *(word_t *)(ctx + 0x38) = uv5;
  sk_rt_0007c028();
  *(word_t *)(ctx + 0x40) = xr_x16;
  uv1 = sk_rt_00407b48(*(word_t *)(xr_x8 + 0x40));
  *(word_t *)(ctx + 0x48) = uv1;
  uv1 = sk_rt_0040bb18(in_r20 & 0xfffffffffffffff0);
  *(word_t *)(ctx + 0x50) = uv1;
  uv1 = sk_rt_0040bb18(in_r20 & 0xfffffffffffffff0);
  *(word_t *)(ctx + 0x58) = uv1;
  *(word_t *)(ctx + 0x60) = *(word_t *)(param_4 + 0x20);
  *(word_t *)(ctx + 0x68) = *(word_t *)(param_4 + 0x10);
  sk_rt_004083d8();
  sk_rt_00350798();
  uv1 = sk_rt_004085b4();
  *(word_t *)(ctx + 0x70) = uv1;
  sk_rt_00352018();
  *(word_t *)(ctx + 0x78) = xr_x16_00;
  uv1 = sk_rt_004078e8(*(word_t *)(xr_x8_00 + 0x40));
  *(word_t *)(ctx + 0x80) = uv1;
  sk_rt_004072c0();
  uv1 = sk_rt_004085b4();
  *(word_t *)(ctx + 0x88) = uv1;
  sk_rt_00350798();
  uv1 = sk_rt_00310d68();
  *(word_t *)(ctx + 0x90) = uv1;
  sk_rt_00352018();
  *(word_t *)(ctx + 0x98) = xr_x16_01;
  uv1 = sk_rt_004078e8(*(word_t *)(xr_x8_01 + 0x40));
  *(word_t *)(ctx + 0xa0) = uv1;
  sk_rt_0040683c();
  *(word_t *)(ctx + 0xa8) = xr_x16_02;
  sk_rt_004078e8(*(word_t *)(xr_x8_02 + 0x40));
  sk_rt_00408328();
  sk_rt_003510a0(0xff);
  uv2 = sk_rt_00377824();
  *(uint64_t *)(ctx + 0xc0) = uv2;
  sk_rt_00350798();
  uv1 = sk_rt_00310d68();
  *(word_t *)(ctx + 200) = uv1;
  sk_rt_00352018();
  *(word_t *)(ctx + 0xd0) = xr_x16_03;
  uv3 = *(int64_t *)(xr_x8_03 + 0x40) + 0xf;
  uv1 = sk_rt_0040bb18(uv3 & 0xfffffffffffffff0);
  *(word_t *)(ctx + 0xd8) = uv1;
  uv1 = sk_rt_0040bb18(uv3 & 0xfffffffffffffff0);
  *(word_t *)(ctx + 0xe0) = uv1;
  sk_rt_0040683c();
  *(word_t *)(ctx + 0xe8) = xr_x16_04;
  uv1 = sk_rt_00407b48(*(word_t *)(xr_x8_04 + 0x40));
  *(word_t *)(ctx + 0xf0) = uv1;
  uv1 = sk_rt_0040bb18(uv2 & 0xfffffffffffffff0);
  *(word_t *)(ctx + 0xf8) = uv1;
  sk_rt_0035050c();
  uv1 = sk_rt_00377824();
  *(word_t *)(ctx + 0x100) = uv1;
  sk_rt_00352018();
  *(word_t *)(ctx + 0x108) = xr_x16_05;
  uv1 = sk_rt_00407b48(*(word_t *)(xr_x8_05 + 0x40));
  *(word_t *)(ctx + 0x110) = uv1;
  uv1 = sk_rt_0040bb18(uv2 & 0xfffffffffffffff0);
  *(word_t *)(ctx + 0x118) = uv1;
  uv1 = sk_rt_0040bb18(uv2 & 0xfffffffffffffff0);
  *(word_t *)(ctx + 0x120) = uv1;
  sk_rt_004083c0();
  sk_rt_003510a0();
  uv3 = sk_rt_00377824();
  *(uint64_t *)(ctx + 0x128) = uv3;
  sk_rt_00350798();
  uv1 = sk_rt_00310d68();
  *(word_t *)(ctx + 0x130) = uv1;
  sk_rt_00352018();
  *(word_t *)(ctx + 0x138) = xr_x16_06;
  uv1 = sk_rt_004078e8(*(word_t *)(xr_x8_06 + 0x40));
  *(word_t *)(ctx + 0x140) = uv1;
  sk_rt_0040683c();
  *(word_t *)(ctx + 0x148) = xr_x16_07;
  uv1 = sk_rt_00407b48(*(word_t *)(xr_x8_07 + 0x40));
  *(word_t *)(ctx + 0x150) = uv1;
  uv1 = sk_rt_0040bb18(uv3 & 0xfffffffffffffff0);
  *(word_t *)(ctx + 0x158) = uv1;
  if (xr_x1 == 0) {
    sk_rt_00407248();
    uv1 = xr_x8_10;
  }
  else {
    sk_rt_00407374(param_3);
    sk_rt_00084180();
    ((code_t)xr_x8_08)();
    sk_rt_0008e1ec();
    uv1 = xr_x8_09;
  }
  *(word_t *)(ctx + 0x160) = uv1;
  *(word_t *)(ctx + 0x168) = uv5;
  sk_rt_00353080();
  sk_rt_004078f4();
  sk_rt_00408db8();
  return;
}



/* void FUN_003e86c8(void) */

void sk_slice57_003e86c8()

{
  int32_t iv1;
  uint8_t zero_cc;
  word_t uv2;
  word_t *wp3;
  int64_t ln4;
  code_t *jt0;
  code_t *xr_x9;
  code_t *xr_x9_00;
  word_t xr_x10;
  word_t xr_x10_00;
  code_t *xr_x11;
  code_t *xr_x16;
  code_t *xr_x16_00;
  word_t xr_x17;
  word_t xr_x17_00;
  int64_t ctx;
  sk_u128_t auVar5;
  word_t st_arg_0;
  word_t st_arg_8;
  word_t st_arg_16;
  word_t st_arg_24;
  word_t st_arg_32;
  word_t st_arg_40;
  code_t *jt;
  
  uv2 = sk_rt_00407afc();
  auVar5 = sk_rt_00407f60();
  iv1 = *(int32_t *)(*(int64_t *)(ctx + 0x28) + 0x3c);
  *(int32_t *)(ctx + 0x1e0) = iv1;
  if ((*(uint8_t *)(*(int64_t *)(ctx + 0x30) + (int64_t)iv1) & 1) != 0) {
    sk_rt_004066bc();
    sk_rt_00350744();
    sk_rt_000839d8();
    sk_rt_0040bd24();
    sk_rt_0040bd24();
    sk_rt_0040bd24();
    sk_rt_0040bd24();
    sk_rt_0040bd24();
    sk_rt_0040bd24();
    sk_rt_0040bd24();
    sk_rt_0040bd24();
    sk_rt_0040bd24();
    sk_rt_0040bd24(st_arg_0);
    sk_rt_0040bd24(st_arg_8);
    sk_rt_0040bd24(st_arg_16);
    sk_rt_0040bd24(st_arg_24);
    sk_rt_0040bd24(st_arg_32);
    sk_rt_0040bd24(st_arg_40);
    sk_rt_0040bd24(jt);
    auVar5 = sk_rt_0040678c();
    sk_rt_004075d0(auVar5.lo,auVar5.hi,uv2);
                    /* WARNING: Could not recover jumptable at 0x003e87b0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    ((code_t)jt0)();
    return;
  }
  *(uint32_t *)(ctx + 0x1e4) = *(uint32_t *)(*(int64_t *)(ctx + 0x28) + 0x38);
  *(word_t *)(ctx + 0x170) = *(word_t *)(*(int64_t *)(ctx + 0x138) + 0x10);
  sk_rt_00408460(auVar5.lo,auVar5.hi,*(word_t *)(ctx + 0x130));
  ((code_t)xr_x11)();
  sk_rt_00406420();
  if ((bool)zero_cc) {
    ln4 = *(int64_t *)(ctx + 0x68);
    sk_rt_00353930(*(word_t *)(ctx + 0x138),*(word_t *)(ctx + 0x140),
                 *(word_t *)(ctx + 0x130));
    *(code_t **)(ctx + 0x198) = xr_x9;
    *(word_t *)(ctx + 0x1a0) = xr_x10;
    ((code_t)xr_x9)();
    sk_rt_0040652c();
    uv2 = sk_rt_00406608();
    *(word_t *)(ctx + 0x1a8) = uv2;
    uv2 = sk_rt_00406e8c();
    *(word_t *)(ctx + 0x1b0) = uv2;
    sk_rt_00406288();
    sk_rt_0040bb18(*(uint32_t *)(ln4 + 4));
    wp3 = (word_t *)sk_rt_00406fe0();
    *(word_t **)(ctx + 0x1b8) = wp3;
    *wp3 = xr_x17;
    wp3[1] = (word_t)&sk_lab_003e8d3c;
    sk_rt_004067b8(*(word_t *)(ctx + 0xa0));
    jt = xr_x16;
  }
  else {
    uv2 = *(word_t *)(ctx + 0x128);
    auVar5 = sk_rt_00406894(*(word_t *)(ctx + 0x148),*(word_t *)(ctx + 0x158),
                          *(word_t *)(ctx + 0x140));
    *(code_t **)(ctx + 0x178) = xr_x9_00;
    *(word_t *)(ctx + 0x180) = xr_x10_00;
    ((code_t)xr_x9_00)(auVar5.lo,auVar5.hi,uv2);
    uv2 = sk_rt_004067f8();
    *(word_t *)(ctx + 0x188) = uv2;
    sk_rt_003fcc4c();
    ln4 = sk_rt_00406374();
    sk_rt_0040bb18(*(uint32_t *)(ln4 + 4));
    wp3 = (word_t *)sk_rt_00406fe0();
    *(word_t **)(ctx + 400) = wp3;
    *wp3 = xr_x17_00;
    sk_rt_00406a24();
    jt = xr_x16_00;
  }
  sk_rt_004075d0();
                    /* WARNING: Could not recover jumptable at 0x003e8914. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  ((code_t)jt)();
  return;
}



/* void FUN_003e89f0(void) */

void sk_slice57_003e89f0()

{
  code_t *fptr1;
  word_t uv2;
  word_t uv3;
  uint8_t zero_cc;
  word_t uv4;
  word_t *wp5;
  int64_t ln6;
  code_t *jt;
  code_t *xr_x8;
  code_t *xr_x8_00;
  code_t *xr_x8_01;
  word_t uv7;
  code_t *xr_x9;
  word_t uv8;
  code_t *xr_x9_00;
  word_t xr_x10;
  word_t xr_x10_00;
  code_t *xr_x16;
  code_t *xr_x16_00;
  word_t xr_x17;
  word_t xr_x17_00;
  word_t uv9;
  word_t uv10;
  int64_t ln11;
  int64_t ctx;
  code_t *fptr12;
  word_t uv13;
  word_t uv14;
  int64_t ln15;
  word_t *wp16;
  sk_u128_t auVar17;
  word_t st_arg_0;
  word_t st_arg_8;
  code_t *jt0;
  
  uv4 = sk_rt_00407afc();
  sk_rt_00407f60();
  uv9 = *(word_t *)(ctx + 0xe0);
  uv10 = *(word_t *)(ctx + 0xc0);
  sk_rt_00406be4();
  if ((bool)zero_cc) {
    ln6 = *(int64_t *)(ctx + 0xd0);
    (**(code_t **)(*(int64_t *)(ctx + 0x148) + 8))
              (*(word_t *)(ctx + 0x158),*(word_t *)(ctx + 0x128));
    sk_rt_003507e0(*(word_t *)(ln6 + 8));
    ((code_t)xr_x8)();
    sk_rt_00407764();
    ((code_t)xr_x8_00)();
    sk_rt_00350744(*(int64_t *)(ctx + 0x30) + (int64_t)*(int32_t *)(ctx + 0x1e4));
    auVar17 = sk_rt_000839d8();
    sk_rt_00406fb0(*(word_t *)(ctx + 0x170),auVar17.lo,auVar17.hi,
                 *(word_t *)(ctx + 0x130));
    ((code_t)xr_x8_01)();
    sk_rt_00406420();
    if ((bool)zero_cc) {
      ln6 = *(int64_t *)(ctx + 0x68);
      sk_rt_00353930(*(word_t *)(ctx + 0x138),*(word_t *)(ctx + 0x140),
                   *(word_t *)(ctx + 0x130));
      *(code_t **)(ctx + 0x198) = xr_x9;
      *(word_t *)(ctx + 0x1a0) = xr_x10;
      ((code_t)xr_x9)();
      sk_rt_0040652c();
      uv4 = sk_rt_00406608();
      *(word_t *)(ctx + 0x1a8) = uv4;
      uv4 = sk_rt_00406e8c();
      *(word_t *)(ctx + 0x1b0) = uv4;
      sk_rt_00406288();
      sk_rt_0040bb18(*(uint32_t *)(ln6 + 4));
      wp5 = (word_t *)sk_rt_00406fe0();
      *(word_t **)(ctx + 0x1b8) = wp5;
      *wp5 = xr_x17;
      wp5[1] = (word_t)&sk_lab_003e8d3c;
      sk_rt_004067b8(*(word_t *)(ctx + 0xa0));
      jt0 = xr_x16;
    }
    else {
      uv4 = *(word_t *)(ctx + 0x128);
      auVar17 = sk_rt_00406894(*(word_t *)(ctx + 0x148),*(word_t *)(ctx + 0x158),
                             *(word_t *)(ctx + 0x140));
      *(code_t **)(ctx + 0x178) = xr_x9_00;
      *(word_t *)(ctx + 0x180) = xr_x10_00;
      ((code_t)xr_x9_00)(auVar17.lo,auVar17.hi,uv4);
      uv4 = sk_rt_004067f8();
      *(word_t *)(ctx + 0x188) = uv4;
      sk_rt_003fcc4c();
      ln6 = sk_rt_00406374();
      sk_rt_0040bb18(*(uint32_t *)(ln6 + 4));
      wp5 = (word_t *)sk_rt_00406fe0();
      *(word_t **)(ctx + 400) = wp5;
      *wp5 = xr_x17_00;
      sk_rt_00406a24();
      jt0 = xr_x16_00;
    }
    sk_rt_004075d0();
                    /* WARNING: Could not recover jumptable at 0x003e8d38. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    ((code_t)jt0)();
    return;
  }
  fptr1 = *(code_t **)(ctx + 0x178);
  uv3 = *(word_t *)(ctx + 0x180);
  ln15 = (int64_t)*(int32_t *)(ctx + 0x1e4);
  uv8 = *(word_t *)(ctx + 0x158);
  uv2 = *(word_t *)(ctx + 0x130);
  ln6 = *(int64_t *)(ctx + 0x138);
  uv13 = *(word_t *)(ctx + 0x128);
  uv14 = *(word_t *)(ctx + 0xf8);
  ln11 = *(int64_t *)(ctx + 0x30);
  uv7 = *(word_t *)(ctx + 0x10);
  wp16 = (word_t *)(*(int64_t *)(ctx + 0xe8) + 0x20);
  fptr12 = (code_t *)*wp16;
  sk_rt_00350968(uv14);
  ((code_t)fptr12)();
  wp5 = (word_t *)(ln6 + 8);
  (*(code_t *)*wp5)(ln11 + ln15,uv2);
  ((code_t)fptr1)(uv3,ln11 + ln15,uv8,uv13);
  sk_rt_00350750(ln11 + ln15);
  sk_rt_000839d8();
  ((code_t)fptr12)(uv7,uv14,uv10);
  sk_rt_004066bc();
  sk_rt_00350750();
  sk_rt_000839d8();
  sk_rt_0040bd24(uv13);
  sk_rt_0040bd24(uv14);
  sk_rt_0040bd24(ln15);
  sk_rt_0040bd24(wp5);
  sk_rt_0040bd24(wp16);
  sk_rt_0040bd24(uv10);
  sk_rt_0040bd24(uv9);
  sk_rt_0040bd24(ln11);
  sk_rt_0040bd24(fptr12);
  sk_rt_0040bd24(st_arg_0);
  sk_rt_0040bd24(st_arg_8);
  sk_rt_0040bd24(uv2);
  sk_rt_0040bd24(uv8);
  sk_rt_0040bd24(fptr1);
  sk_rt_0040bd24(uv3);
  sk_rt_0040bd24(uv7);
  auVar17 = sk_rt_0040678c();
  sk_rt_004075d0(auVar17.lo,auVar17.hi,uv4);
                    /* WARNING: Could not recover jumptable at 0x003e8ca0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  ((code_t)jt)();
  return;
}



/* void FUN_003e8e28(void) */

void sk_slice57_003e8e28()

{
  int64_t ln1;
  int64_t ln2;
  uint8_t zero_cc;
  word_t uv3;
  word_t uv4;
  word_t *wp5;
  code_t *jt0;
  code_t *jt;
  int64_t xr_x8;
  code_t *xr_x9;
  code_t *xr_x9_00;
  code_t *xr_x16;
  word_t xr_x17;
  word_t uv6;
  word_t uv7;
  int64_t ctx;
  sk_u128_t auVar8;
  word_t st_arg_0;
  word_t st_arg_8;
  word_t st_arg_16;
  word_t st_arg_24;
  word_t st_arg_32;
  word_t st_arg_40;
  word_t st_arg_48;
  
  uv3 = sk_rt_00407afc();
  sk_rt_00407f60();
  uv7 = *(word_t *)(ctx + 0xa0);
  uv6 = *(word_t *)(ctx + 0x88);
  uv4 = sk_rt_00406420();
  if ((bool)zero_cc) {
    sk_rt_0040711c(*(word_t *)(ctx + 0x98),uv4,*(word_t *)(ctx + 0x90));
    ((code_t)xr_x9)();
    sk_rt_004066bc();
    sk_rt_00350744();
    sk_rt_000839d8();
    sk_rt_0040bd24();
    sk_rt_0040bd24();
    sk_rt_0040bd24();
    sk_rt_0040bd24();
    sk_rt_0040bd24();
    sk_rt_0040bd24(uv7);
    sk_rt_0040bd24(uv6);
    sk_rt_0040bd24();
    sk_rt_0040bd24();
    sk_rt_0040bd24(st_arg_0);
    sk_rt_0040bd24(st_arg_8);
    sk_rt_0040bd24(st_arg_16);
    sk_rt_0040bd24(st_arg_24);
    sk_rt_0040bd24(st_arg_32);
    sk_rt_0040bd24(st_arg_40);
    sk_rt_0040bd24(st_arg_48);
    auVar8 = sk_rt_0040678c();
    sk_rt_004075d0(auVar8.lo,auVar8.hi,uv3);
                    /* WARNING: Could not recover jumptable at 0x003e8f20. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    ((code_t)jt0)();
    return;
  }
  ln1 = *(int64_t *)(ctx + 0x28);
  ln2 = *(int64_t *)(ctx + 0x30);
  sk_rt_00406bd4(*(word_t *)(ctx + 0xa8),*(word_t *)(ctx + 0xb0));
  ((code_t)xr_x9_00)();
  sk_rt_004062a8(*(word_t *)(ln2 + *(int32_t *)(ln1 + 0x34)));
  sk_rt_0040bb18(*(uint32_t *)(xr_x8 + 4));
  wp5 = (word_t *)sk_rt_00406fe0();
  *(word_t **)(ctx + 0x1c0) = wp5;
  *wp5 = xr_x17;
  wp5[1] = (word_t)&sk_lab_003e8fc4;
  jt = xr_x16;
  sk_rt_004075d0(*(word_t *)(ctx + 0x50),*(word_t *)(ctx + 0xb0),xr_x16,
               uv3);
                    /* WARNING: Could not recover jumptable at 0x003e8fc0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  ((code_t)jt)();
  return;
}



/* void FUN_003e90f4(void) */

void sk_slice57_003e90f4()

{
  word_t uv1;
  int64_t ln2;
  word_t *wp3;
  code_t *jt;
  code_t *xr_x8;
  code_t *xr_x9;
  code_t *xr_x9_00;
  word_t xr_x17;
  word_t uv4;
  word_t uv5;
  int64_t ctx;
  word_t uv6;
  sk_u128_t auVar7;
  
  sk_rt_004079cc();
  uv1 = sk_rt_004070d8();
  uv4 = *(word_t *)(ctx + 0x128);
  uv5 = *(word_t *)(ctx + 0xb8);
  ln2 = *(int64_t *)(ctx + 0x40);
  uv6 = *(word_t *)(ctx + 0x38);
  auVar7 = sk_rt_00407ce4(uv1,*(word_t *)(ctx + 0x50));
  ((code_t)xr_x9)(auVar7.lo,auVar7.hi,uv6);
  auVar7 = sk_rt_00350518(*(word_t *)(ln2 + 0x10));
  ((code_t)xr_x8)(auVar7.lo,auVar7.hi,uv6);
  sk_rt_004070e4(uv5);
  ((code_t)xr_x9_00)(uv6,uv5);
  sk_rt_004068bc();
  uv1 = sk_rt_00377bec(uv5,uv6,uv4);
  *(word_t *)(ctx + 0x1d0) = uv1;
  sk_rt_003fcc4c();
  ln2 = sk_rt_00406374();
  sk_rt_0040bb18(*(uint32_t *)(ln2 + 4));
  wp3 = (word_t *)sk_rt_00406fe0();
  *(word_t **)(ctx + 0x1d8) = wp3;
  *wp3 = xr_x17;
  wp3[1] = (word_t)&sk_lab_003e9224;
  sk_rt_00407990(*(word_t *)(ctx + 0xd8),*(word_t *)(ctx + 0x18),
               *(word_t *)(ctx + 0x20),*(word_t *)(ctx + 0x110),
               *(word_t *)(ctx + 0x128));
  sk_rt_004078f4();
                    /* WARNING: Could not recover jumptable at 0x003e9220. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  ((code_t)jt)();
  return;
}



/* void FUN_003e9310(void) */

void sk_slice57_003e9310()

{
  code_t *fptr1;
  word_t uv2;
  word_t uv3;
  word_t uv4;
  word_t uv5;
  word_t uv6;
  uint8_t zero_cc;
  word_t uv7;
  word_t *wp8;
  int64_t ln9;
  code_t *jt;
  code_t *xr_x8;
  code_t *xr_x8_00;
  word_t uv10;
  code_t *xr_x9;
  code_t *xr_x9_00;
  word_t xr_x10;
  word_t xr_x10_00;
  code_t *xr_x16;
  code_t *xr_x16_00;
  word_t xr_x17;
  word_t xr_x17_00;
  word_t uv11;
  word_t uv12;
  int64_t ctx;
  code_t *fptr13;
  int64_t ln14;
  word_t *wp15;
  int64_t ln16;
  sk_u128_t auVar17;
  word_t st_arg_0;
  word_t st_arg_8;
  code_t *jt0;
  
  uv7 = sk_rt_00407afc();
  sk_rt_00407f60();
  uv11 = *(word_t *)(ctx + 0xd8);
  uv12 = *(word_t *)(ctx + 0xc0);
  sk_rt_00406be4();
  if ((bool)zero_cc) {
    fptr1 = *(code_t **)(ctx + 0x198);
    ln9 = *(int64_t *)(ctx + 0xd0);
    (**(code_t **)(*(int64_t *)(ctx + 0x148) + 8))
              (*(word_t *)(ctx + 0x150),*(word_t *)(ctx + 0x128));
    sk_rt_003507e0(*(word_t *)(ln9 + 8));
    ((code_t)xr_x8)();
    sk_rt_00408410();
    ((code_t)fptr1)();
    sk_rt_00350744(*(int64_t *)(ctx + 0x30) + (int64_t)*(int32_t *)(ctx + 0x1e4));
    auVar17 = sk_rt_000839d8();
    sk_rt_00406fb0(*(word_t *)(ctx + 0x170),auVar17.lo,auVar17.hi,
                 *(word_t *)(ctx + 0x130));
    ((code_t)xr_x8_00)();
    sk_rt_00406420();
    if ((bool)zero_cc) {
      ln9 = *(int64_t *)(ctx + 0x68);
      sk_rt_00353930(*(word_t *)(ctx + 0x138),*(word_t *)(ctx + 0x140),
                   *(word_t *)(ctx + 0x130));
      *(code_t **)(ctx + 0x198) = xr_x9;
      *(word_t *)(ctx + 0x1a0) = xr_x10;
      ((code_t)xr_x9)();
      sk_rt_0040652c();
      uv7 = sk_rt_00406608();
      *(word_t *)(ctx + 0x1a8) = uv7;
      uv7 = sk_rt_00406e8c();
      *(word_t *)(ctx + 0x1b0) = uv7;
      sk_rt_00406288();
      sk_rt_0040bb18(*(uint32_t *)(ln9 + 4));
      wp8 = (word_t *)sk_rt_00406fe0();
      *(word_t **)(ctx + 0x1b8) = wp8;
      *wp8 = xr_x17;
      wp8[1] = (word_t)&sk_lab_003e8d3c;
      sk_rt_004067b8(*(word_t *)(ctx + 0xa0));
      jt0 = xr_x16;
    }
    else {
      uv7 = *(word_t *)(ctx + 0x128);
      auVar17 = sk_rt_00406894(*(word_t *)(ctx + 0x148),*(word_t *)(ctx + 0x158),
                             *(word_t *)(ctx + 0x140));
      *(code_t **)(ctx + 0x178) = xr_x9_00;
      *(word_t *)(ctx + 0x180) = xr_x10_00;
      ((code_t)xr_x9_00)(auVar17.lo,auVar17.hi,uv7);
      uv7 = sk_rt_004067f8();
      *(word_t *)(ctx + 0x188) = uv7;
      sk_rt_003fcc4c();
      ln9 = sk_rt_00406374();
      sk_rt_0040bb18(*(uint32_t *)(ln9 + 4));
      wp8 = (word_t *)sk_rt_00406fe0();
      *(word_t **)(ctx + 400) = wp8;
      *wp8 = xr_x17_00;
      sk_rt_00406a24();
      jt0 = xr_x16_00;
    }
    sk_rt_004075d0();
                    /* WARNING: Could not recover jumptable at 0x003e9644. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    ((code_t)jt0)();
    return;
  }
  fptr1 = *(code_t **)(ctx + 0x198);
  uv3 = *(word_t *)(ctx + 0x1a0);
  ln14 = (int64_t)*(int32_t *)(ctx + 0x1e4);
  ln9 = *(int64_t *)(ctx + 0x148);
  uv4 = *(word_t *)(ctx + 0x150);
  uv2 = *(word_t *)(ctx + 0x128);
  uv5 = *(word_t *)(ctx + 0x130);
  uv6 = *(word_t *)(ctx + 0xf0);
  ln16 = *(int64_t *)(ctx + 0x30);
  uv10 = *(word_t *)(ctx + 0x10);
  wp15 = (word_t *)(*(int64_t *)(ctx + 0xe8) + 0x20);
  fptr13 = (code_t *)*wp15;
  sk_rt_00350968(uv6);
  ((code_t)fptr13)();
  ((code_t)fptr1)(uv3,ln16 + ln14,uv5);
  wp8 = (word_t *)(ln9 + 0x20);
  (*(code_t *)*wp8)(ln16 + ln14,uv4,uv2);
  sk_rt_00350750(ln16 + ln14);
  sk_rt_000839d8();
  ((code_t)fptr13)(uv10,uv6,uv12);
  sk_rt_004066bc();
  sk_rt_00350750();
  sk_rt_000839d8();
  sk_rt_0040bd24(uv2);
  sk_rt_0040bd24(uv6);
  sk_rt_0040bd24(ln14);
  sk_rt_0040bd24(wp15);
  sk_rt_0040bd24(ln16);
  sk_rt_0040bd24(uv12);
  sk_rt_0040bd24(uv11);
  sk_rt_0040bd24(wp8);
  sk_rt_0040bd24(fptr13);
  sk_rt_0040bd24(st_arg_0);
  sk_rt_0040bd24(st_arg_8);
  sk_rt_0040bd24(uv5);
  sk_rt_0040bd24(fptr1);
  sk_rt_0040bd24(uv3);
  sk_rt_0040bd24(uv4);
  sk_rt_0040bd24(uv10);
  auVar17 = sk_rt_0040678c();
  sk_rt_004075d0(auVar17.lo,auVar17.hi,uv7);
                    /* WARNING: Could not recover jumptable at 0x003e95ac. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  ((code_t)jt)();
  return;
}



/* void FUN_003e9c34(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4, undefined8 param_5) */

void sk_slice57_003e9c34(word_t  param_1, word_t  param_2, word_t  param_3, word_t  param_4, word_t  param_5)

{
  int64_t *lp1;
  int64_t ctx;
  
  *(word_t *)(ctx + 0x10) = param_4;
  lp1 = (int64_t *)sk_rt_0040bb18(sk_d_005a00cc);
  *(int64_t **)(ctx + 0x18) = lp1;
  *lp1 = ctx;
  lp1[1] = (int64_t)(word_t)&sk_d_004060bc;
  sk_slice57_003e838c((word_t)lp1,(word_t)param_1,(word_t)param_2,(word_t)param_3,(word_t)param_5);
  return;
}



/* void FUN_003e9d04(void) */

void sk_slice57_003e9d04()

{
  code_t *xr_x9;
  code_t *in_r19;
  int64_t in_r21;
  word_t in_r30;
  
  sk_rt_00084220();
  sk_rt_0008409c();
  sk_rt_0040654c();
  sk_rt_003513b4();
  sk_rt_00377824();
  sk_rt_00351f10();
  sk_rt_0007c1a4();
  ((code_t)sk_d_00658c80)();
  sk_rt_0034b05c();
  sk_rt_00407100();
  sk_rt_00350518();
  ((code_t)xr_x9)();
  sk_rt_004082a8((int64_t)*(int32_t *)(in_r21 + 0x34));
  sk_rt_00407700();
  ((code_t)in_r19)();
  sk_rt_00084234(in_r30);
  return;
}



/* void FUN_003e9db0(void) */

void sk_slice57_003e9db0()

{
  sk_rt_00406574();
  sk_slice57_003e9de0();
  sk_rt_0036b270();
  return;
}



/* void FUN_003e9de0(void) */

void sk_slice57_003e9de0()

{
  sk_slice57_003e9df8();
  return;
}



/* void FUN_003e9df8(void) */

void sk_slice57_003e9df8()

{
  word_t *wp1;
  int64_t ln2;
  word_t xr_x1;
  word_t in_r3;
  int64_t xr_x8;
  int64_t xr_x16;
  code_t *in_r19;
  word_t in_r23;
  word_t in_r30;
  sk_u128_t auVar3;
  
  sk_rt_00084220();
  auVar3 = sk_rt_00407484();
  sk_rt_003509c8(in_r3,auVar3.lo,auVar3.lo);
  (**(code_t **)(xr_x16 + 0x20))(xr_x8,xr_x1,in_r3);
  sk_rt_0034d004(0);
  ln2 = ((code_t)in_r19)();
  wp1 = (word_t *)(xr_x8 + *(int32_t *)(ln2 + 0x2c));
  *wp1 = auVar3.hi;
  wp1[1] = in_r23;
  sk_rt_00084234(in_r30);
  return;
}



/* void FUN_003e9e74(undefined8 param_1,long param_2) */

void sk_slice57_003e9e74(word_t  param_1, int64_t  param_2)

{
  int64_t xr_x16;
  
  sk_rt_0040654c(param_2,*(word_t *)(param_2 + 0x20),*(word_t *)(param_2 + 0x10));
  sk_rt_00377824();
  sk_rt_00350404();
                    /* WARNING: Could not recover jumptable at 0x003e9ec8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code_t **)(xr_x16 + 0x10))(param_1);
  return;
}



/* void FUN_003e9f40(void) */

void sk_slice57_003e9f40()

{
  int64_t ln1;
  code_t *in_r6;
  int64_t xr_x16;
  int64_t in_r24;
  word_t in_r30;
  
  sk_rt_00084220();
  sk_rt_0034bb84();
  sk_rt_00407450();
  ln1 = ((code_t)in_r6)();
  *(uint8_t *)(in_r24 + *(int32_t *)(ln1 + 0x30)) = 0;
  sk_rt_0040654c();
  sk_rt_00350968();
  sk_rt_00377824();
  sk_rt_00349530();
  (**(code_t **)(xr_x16 + 0x20))();
  sk_rt_00407ea0((int64_t)*(int32_t *)(ln1 + 0x2c));
  sk_rt_00084234(in_r30);
  return;
}



/* void FUN_003e9fcc(void) */

void sk_slice57_003e9fcc()

{
  word_t uv1;
  int64_t ln2;
  word_t xr_x8;
  int64_t xr_x8_00;
  int64_t xr_x8_01;
  word_t xr_x16;
  word_t xr_x16_00;
  word_t in_r20;
  int64_t ctx;
  sk_u128_t auVar3;
  
  auVar3 = sk_rt_00407000();
  ln2 = auVar3.hi;
  *(int64_t *)(ctx + 0x18) = ln2;
  *(word_t *)(ctx + 0x20) = in_r20;
  *(int64_t *)(ctx + 0x10) = auVar3.lo;
  *(word_t *)(ctx + 0x28) = *(word_t *)(ln2 + 0x20);
  *(word_t *)(ctx + 0x30) = *(word_t *)(ln2 + 0x10);
  uv1 = sk_rt_004069c4();
  sk_rt_00377824(uv1,xr_x8);
  sk_rt_004079a8();
  sk_rt_00350798();
  uv1 = sk_rt_00310d68();
  *(word_t *)(ctx + 0x40) = uv1;
  sk_rt_00352018();
  *(word_t *)(ctx + 0x48) = xr_x16;
  uv1 = sk_rt_004078e8(*(word_t *)(xr_x8_00 + 0x40));
  *(word_t *)(ctx + 0x50) = uv1;
  sk_rt_0040683c();
  *(word_t *)(ctx + 0x58) = xr_x16_00;
  uv1 = sk_rt_004078e8(*(word_t *)(xr_x8_01 + 0x40));
  *(word_t *)(ctx + 0x60) = uv1;
  sk_rt_00407594();
  sk_rt_00408db8();
  return;
}



/* void FUN_003ea0a4(void) */

void sk_slice57_003ea0a4()

{
  int64_t ln1;
  int32_t iv2;
  word_t uv3;
  word_t *wp4;
  code_t *jt0;
  code_t *jt;
  word_t xr_x17;
  int64_t ctx;
  sk_u128_t auVar5;
  
  uv3 = sk_rt_00407ca0();
  sk_rt_0040700c();
  iv2 = *(int32_t *)(*(int64_t *)(ctx + 0x18) + 0x30);
  *(int32_t *)(ctx + 0x88) = iv2;
  if ((*(uint8_t *)(*(int64_t *)(ctx + 0x20) + (int64_t)iv2) & 1) != 0) {
    sk_rt_00407604();
    sk_rt_00406c5c(*(word_t *)(ctx + 0x10));
    sk_rt_0040bd24();
    auVar5 = sk_rt_0040678c();
    sk_rt_00407e58(auVar5.lo,auVar5.hi,uv3);
                    /* WARNING: Could not recover jumptable at 0x003ea118. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    ((code_t)jt0)();
    return;
  }
  ln1 = *(int64_t *)(ctx + 0x30);
  sk_rt_0040652c();
  sk_rt_00406608();
  sk_rt_004068f4();
  sk_rt_00406268();
  sk_rt_0040bb18(*(uint32_t *)(ln1 + 4));
  wp4 = (word_t *)sk_rt_00406fe0();
  *(word_t **)(ctx + 0x68) = wp4;
  *wp4 = xr_x17;
  sk_rt_004074c4();
  sk_rt_00406ab4();
                    /* WARNING: Could not recover jumptable at 0x003ea1a0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  ((code_t)jt)();
  return;
}



/* void FUN_003ea260(void) */

void sk_slice57_003ea260()

{
  int64_t ln1;
  int64_t ln2;
  uint8_t zero_cc;
  word_t uv3;
  word_t uv4;
  word_t *wp5;
  code_t *jt0;
  int64_t xr_x8;
  code_t *xr_x9;
  code_t *xr_x9_00;
  code_t *jt;
  word_t xr_x17;
  word_t uv6;
  int64_t ctx;
  sk_u128_t auVar7;
  
  uv3 = sk_rt_00407ca0();
  sk_rt_0040700c();
  uv6 = *(word_t *)(ctx + 0x38);
  uv4 = sk_rt_00406420();
  if ((bool)zero_cc) {
    sk_rt_0040711c(*(word_t *)(ctx + 0x48),uv4,*(word_t *)(ctx + 0x40));
    ((code_t)xr_x9)();
    sk_rt_00407604();
    sk_rt_00408374();
    sk_rt_00406c5c();
    sk_rt_0040bd24(uv6);
    auVar7 = sk_rt_0040678c();
    sk_rt_00407e58(auVar7.lo,auVar7.hi,uv3);
                    /* WARNING: Could not recover jumptable at 0x003ea2e0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    ((code_t)jt0)();
    return;
  }
  ln1 = *(int64_t *)(ctx + 0x18);
  ln2 = *(int64_t *)(ctx + 0x20);
  sk_rt_00406bd4(*(word_t *)(ctx + 0x58),*(word_t *)(ctx + 0x60));
  ((code_t)xr_x9_00)();
  sk_rt_004062a8(*(word_t *)(ln2 + *(int32_t *)(ln1 + 0x2c)));
  sk_rt_0040bb18(*(uint32_t *)(xr_x8 + 4));
  wp5 = (word_t *)sk_rt_00406fe0();
  *(word_t **)(ctx + 0x78) = wp5;
  *wp5 = xr_x17;
  wp5[1] = (word_t)&sk_lab_003ea380;
  sk_rt_00407610(wp5,*(word_t *)(ctx + 0x60));
                    /* WARNING: Could not recover jumptable at 0x003ea37c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  ((code_t)jt)();
  return;
}



/* void FUN_003ea494(void) */

void sk_slice57_003ea494()

{
  code_t *jt;
  
  sk_rt_00407000();
  sk_rt_00407604();
  sk_rt_00408374();
  sk_rt_00406ee4();
  sk_rt_0040bd24();
  sk_rt_0040678c();
                    /* WARNING: Could not recover jumptable at 0x003ea4e8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  ((code_t)jt)();
  return;
}



/* void FUN_003ea4ec(void) */

void sk_slice57_003ea4ec()

{
  code_t *jt;
  
  sk_rt_00407000();
  sk_rt_00408038();
  sk_rt_0040bd24();
  sk_rt_00407128();
                    /* WARNING: Could not recover jumptable at 0x003ea53c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  ((code_t)jt)();
  return;
}



/* void FUN_003ea5a8(undefined8 param_1,undefined8 param_2,undefined8 param_3,long param_4) */

void sk_slice57_003ea5a8(word_t  param_1, word_t  param_2, word_t  param_3, int64_t  param_4, word_t param_5)

{
  word_t uv1;
  int64_t xr_x8;
  int64_t xr_x8_00;
  int64_t xr_x8_01;
  code_t *xr_x8_02;
  word_t xr_x8_03;
  word_t xr_x8_04;
  word_t xr_x16;
  word_t xr_x16_00;
  word_t xr_x16_01;
  int64_t in_r21;
  int64_t ctx;
  
  sk_rt_00407c8c();
  sk_rt_0040700c();
  sk_rt_00350b54();
  sk_rt_0040752c();
  *(word_t *)(ctx + 0x38) = *(word_t *)(param_4 + 0x20);
  *(word_t *)(ctx + 0x40) = *(word_t *)(param_4 + 0x10);
  uv1 = sk_rt_0040684c();
  *(word_t *)(ctx + 0x48) = uv1;
  sk_rt_00352018();
  *(word_t *)(ctx + 0x50) = xr_x16;
  uv1 = sk_rt_004078e8(*(word_t *)(xr_x8 + 0x40));
  *(word_t *)(ctx + 0x58) = uv1;
  uv1 = sk_rt_00406dd0();
  *(word_t *)(ctx + 0x60) = uv1;
  sk_rt_00350798();
  uv1 = sk_rt_00310d68();
  *(word_t *)(ctx + 0x68) = uv1;
  sk_rt_00352018();
  *(word_t *)(ctx + 0x70) = xr_x16_00;
  uv1 = sk_rt_004078e8(*(word_t *)(xr_x8_00 + 0x40));
  *(word_t *)(ctx + 0x78) = uv1;
  sk_rt_0040683c();
  *(word_t *)(ctx + 0x80) = xr_x16_01;
  uv1 = sk_rt_004078e8(*(word_t *)(xr_x8_01 + 0x40));
  *(word_t *)(ctx + 0x88) = uv1;
  if (in_r21 == 0) {
    sk_rt_00407248();
    uv1 = xr_x8_04;
  }
  else {
    sk_rt_00406590();
    ((code_t)xr_x8_02)();
    sk_rt_0008e1ec();
    uv1 = xr_x8_03;
  }
  *(word_t *)(ctx + 0x90) = uv1;
  *(word_t *)(ctx + 0x98) = param_3;
  sk_rt_00353080();
  sk_rt_00407c78();
  sk_rt_00408db8();
  return;
}



/* void FUN_003ea6ec(void) */

void sk_slice57_003ea6ec()

{
  int64_t ln1;
  int32_t iv2;
  word_t uv3;
  word_t *wp4;
  code_t *jt0;
  code_t *jt;
  word_t xr_x17;
  word_t uv5;
  int64_t ctx;
  sk_u128_t auVar6;
  
  uv3 = sk_rt_00407ca0();
  sk_rt_0040700c();
  iv2 = *(int32_t *)(*(int64_t *)(ctx + 0x28) + 0x30);
  *(int32_t *)(ctx + 200) = iv2;
  if ((*(uint8_t *)(*(int64_t *)(ctx + 0x30) + (int64_t)iv2) & 1) != 0) {
    sk_rt_00407960();
    uv5 = *(word_t *)(ctx + 0x58);
    sk_rt_00406c5c(*(word_t *)(ctx + 0x10));
    sk_rt_0040bd24();
    sk_rt_0040bd24(uv5);
    auVar6 = sk_rt_0040678c();
    sk_rt_00407e58(auVar6.lo,auVar6.hi,uv3);
                    /* WARNING: Could not recover jumptable at 0x003ea76c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    ((code_t)jt0)();
    return;
  }
  ln1 = *(int64_t *)(ctx + 0x40);
  sk_rt_0040652c();
  uv3 = sk_rt_00406608();
  *(word_t *)(ctx + 0xa0) = uv3;
  uv3 = sk_rt_00406e8c();
  *(word_t *)(ctx + 0xa8) = uv3;
  sk_rt_00406288();
  sk_rt_0040bb18(*(uint32_t *)(ln1 + 4));
  wp4 = (word_t *)sk_rt_00406fe0();
  *(word_t **)(ctx + 0xb0) = wp4;
  *wp4 = xr_x17;
  sk_rt_00407830();
  sk_rt_004067b8();
                    /* WARNING: Could not recover jumptable at 0x003ea804. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  ((code_t)jt)();
  return;
}



/* void FUN_003ea8f4(void) */

void sk_slice57_003ea8f4()

{
  int64_t ln1;
  int64_t ln2;
  uint8_t zero_cc;
  word_t uv3;
  word_t uv4;
  word_t *wp5;
  code_t *jt0;
  int64_t xr_x8;
  code_t *xr_x9;
  code_t *xr_x9_00;
  code_t *jt;
  word_t xr_x17;
  word_t uv6;
  int64_t ctx;
  sk_u128_t auVar7;
  
  uv3 = sk_rt_00407ca0();
  sk_rt_0040700c();
  uv6 = *(word_t *)(ctx + 0x60);
  uv4 = sk_rt_00406420();
  if ((bool)zero_cc) {
    sk_rt_0040711c(*(word_t *)(ctx + 0x70),uv4,*(word_t *)(ctx + 0x68));
    ((code_t)xr_x9)();
    sk_rt_00407960();
    uv4 = *(word_t *)(ctx + 0x58);
    sk_rt_004077cc();
    sk_rt_00406c5c();
    sk_rt_0040bd24(uv6);
    sk_rt_0040bd24(uv4);
    auVar7 = sk_rt_0040678c();
    sk_rt_00407e58(auVar7.lo,auVar7.hi,uv3);
                    /* WARNING: Could not recover jumptable at 0x003ea980. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    ((code_t)jt0)();
    return;
  }
  ln1 = *(int64_t *)(ctx + 0x28);
  ln2 = *(int64_t *)(ctx + 0x30);
  sk_rt_00406bd4(*(word_t *)(ctx + 0x80),*(word_t *)(ctx + 0x88));
  ((code_t)xr_x9_00)();
  sk_rt_004062a8(*(word_t *)(ln2 + *(int32_t *)(ln1 + 0x2c)));
  sk_rt_0040bb18(*(uint32_t *)(xr_x8 + 4));
  wp5 = (word_t *)sk_rt_00406fe0();
  *(word_t **)(ctx + 0xb8) = wp5;
  *wp5 = xr_x17;
  wp5[1] = (word_t)&sk_lab_003eaa20;
  sk_rt_00407610(wp5,*(word_t *)(ctx + 0x88));
                    /* WARNING: Could not recover jumptable at 0x003eaa1c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  ((code_t)jt)();
  return;
}



/* void FUN_003eab58(void) */

void sk_slice57_003eab58()

{
  code_t *jt;
  word_t uv1;
  int64_t ctx;
  
  sk_rt_00406fd4();
  sk_rt_00407960();
  uv1 = *(word_t *)(ctx + 0x58);
  sk_rt_004077cc();
  sk_rt_00406ee4();
  sk_rt_0040bd24();
  sk_rt_0040bd24(uv1);
  sk_rt_0040678c();
                    /* WARNING: Could not recover jumptable at 0x003eabc0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  ((code_t)jt)();
  return;
}



/* void FUN_003ead6c(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4, undefined8 param_5) */

void sk_slice57_003ead6c(word_t  param_1, word_t  param_2, word_t  param_3, word_t  param_4, word_t  param_5)

{
  int64_t *lp1;
  int64_t ctx;
  
  *(word_t *)(ctx + 0x10) = param_4;
  lp1 = (int64_t *)sk_rt_0040bb18(sk_d_005a00dc);
  *(int64_t **)(ctx + 0x18) = lp1;
  *lp1 = ctx;
  lp1[1] = (int64_t)sk_slice57_003eae24;
  sk_slice57_003ea5a8((word_t)lp1,(word_t)param_1,(word_t)param_2,(word_t)param_3,(word_t)param_5);
  return;
}



/* void FUN_003eae24(void) */

void sk_slice57_003eae24()

{
  code_t *xr_x1;
  code_t *xr_x1_00;
  code_t *jt;
  int64_t xr_x8;
  int64_t xr_x8_00;
  int64_t *xr_x9;
  int64_t in_r20;
  
  sk_rt_00406fd4();
  sk_rt_00407018();
  sk_rt_0040676c();
  *xr_x9 = xr_x8;
  sk_rt_0040bd24(*(word_t *)(xr_x8_00 + 0x18));
  if (in_r20 == 0) {
    sk_rt_00407e10();
    jt = xr_x1_00;
  }
  else {
    **(int64_t **)(xr_x8 + 0x10) = in_r20;
    sk_rt_00407e10();
    jt = xr_x1;
  }
                    /* WARNING: Could not recover jumptable at 0x003eaed4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  ((code_t)jt)();
  return;
}



/* void FUN_003eaef4(void) */

void sk_slice57_003eaef4()

{
  word_t xr_x1;
  sk_u128_t auVar1;
  
  sk_rt_00407478();
  auVar1 = sk_rt_0035a7e8();
  sk_slice57_003eaf34((word_t)auVar1.lo,(word_t)auVar1.hi,(word_t)xr_x1);
  sk_rt_0036b270(xr_x1);
  return;
}



/* void FUN_003eaf34(void) */

void sk_slice57_003eaf34(word_t param_1, word_t param_2, word_t param_3)

{
  sk_slice57_003eaf4c();
  return;
}



/* void FUN_003eaf4c(void) */

void sk_slice57_003eaf4c()

{
  word_t *wp1;
  word_t uv2;
  int64_t ln3;
  word_t xr_x1;
  word_t in_r3;
  code_t *in_r5;
  int64_t xr_x8;
  int64_t xr_x16;
  word_t ctx;
  word_t in_r23;
  
  uv2 = sk_rt_00406e34();
  sk_rt_003509c8(in_r3,uv2,uv2);
  (**(code_t **)(xr_x16 + 0x20))(xr_x8,xr_x1,in_r3);
  sk_rt_00350548(0);
  ln3 = ((code_t)in_r5)();
  wp1 = (word_t *)(xr_x8 + *(int32_t *)(ln3 + 0x24));
  *wp1 = in_r23;
  wp1[1] = ctx;
  return;
}



/* void FUN_003eafc8(undefined8 param_1,long param_2) */

void sk_slice57_003eafc8(word_t  param_1, int64_t  param_2)

{
  int32_t iv1;
  word_t uv2;
  int64_t xr_x16;
  int64_t in_r20;
  
  iv1 = *(int32_t *)(param_2 + 0x24);
  sk_rt_0040654c(param_2,*(word_t *)(param_2 + 0x18),*(word_t *)(param_2 + 0x10));
  sk_rt_00377824();
  uv2 = sk_rt_00350404();
                    /* WARNING: Could not recover jumptable at 0x003eb024. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code_t **)(xr_x16 + 0x10))(param_1,in_r20 + iv1,uv2);
  return;
}



/* void FUN_003eb0a4(void) */

void sk_slice57_003eb0a4()

{
  int32_t iv1;
  int64_t ln2;
  code_t *in_r5;
  uint8_t *xr_x8;
  int64_t xr_x16;
  int64_t in_r24;
  word_t in_r30;
  
  sk_rt_00084220();
  sk_rt_0040679c();
  *xr_x8 = 0;
  sk_rt_00407450();
  ln2 = ((code_t)in_r5)();
  iv1 = *(int32_t *)(ln2 + 0x24);
  sk_rt_0040654c();
  sk_rt_00350968();
  sk_rt_00377824();
  sk_rt_00349530();
  (**(code_t **)(xr_x16 + 0x20))(in_r24 + iv1);
  sk_rt_00407ea0((int64_t)*(int32_t *)(ln2 + 0x28));
  sk_rt_00084234(in_r30);
  return;
}



/* void FUN_003eb120(void) */

void sk_slice57_003eb120()

{
  word_t uv1;
  int64_t xr_x8;
  int64_t xr_x8_00;
  word_t xr_x16;
  word_t xr_x16_00;
  int64_t ctx;
  
  sk_rt_00407000();
  sk_rt_00406704();
  sk_rt_004079a8();
  sk_rt_00350798();
  uv1 = sk_rt_00310d68();
  *(word_t *)(ctx + 0x40) = uv1;
  sk_rt_00352018();
  *(word_t *)(ctx + 0x48) = xr_x16;
  uv1 = sk_rt_004078e8(*(word_t *)(xr_x8 + 0x40));
  *(word_t *)(ctx + 0x50) = uv1;
  sk_rt_0040683c();
  *(word_t *)(ctx + 0x58) = xr_x16_00;
  uv1 = sk_rt_004078e8(*(word_t *)(xr_x8_00 + 0x40));
  *(word_t *)(ctx + 0x60) = uv1;
  sk_rt_00407594();
  sk_rt_00408db8();
  return;
}



/* void FUN_003eb1d8(void) */

void sk_slice57_003eb1d8()

{
  int64_t ln1;
  word_t uv2;
  word_t *wp3;
  code_t *jt0;
  code_t *jt;
  code_t *xr_x16;
  word_t xr_x17;
  int64_t ctx;
  sk_u128_t auVar4;
  
  uv2 = sk_rt_0040790c();
  sk_rt_004070d8();
  if ((**(uint8_t **)(ctx + 0x20) & 1) != 0) {
    sk_rt_00407604();
    sk_rt_0040686c();
    sk_rt_0040bd24();
    auVar4 = sk_rt_0040678c();
    sk_rt_004079b4(auVar4.lo,auVar4.hi,uv2);
                    /* WARNING: Could not recover jumptable at 0x003eb240. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    ((code_t)jt0)();
    return;
  }
  ln1 = *(int64_t *)(ctx + 0x30);
  sk_rt_0040652c();
  sk_rt_00406608();
  sk_rt_004068f4();
  sk_rt_00406268();
  sk_rt_0040bb18(*(uint32_t *)(ln1 + 4));
  wp3 = (word_t *)sk_rt_00406fe0();
  *(word_t **)(ctx + 0x68) = wp3;
  *wp3 = xr_x17;
  wp3[1] = (word_t)&sk_lab_003eb2dc;
  sk_rt_00406ab4(*(word_t *)(ctx + 0x50));
  jt = xr_x16;
  sk_rt_004080cc();
                    /* WARNING: Could not recover jumptable at 0x003eb2d8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  ((code_t)jt)();
  return;
}



/* void FUN_003eb398(void) */

void sk_slice57_003eb398()

{
  int64_t ln1;
  uint8_t zero_cc;
  word_t uv2;
  word_t uv3;
  int64_t *lp4;
  code_t *jt0;
  code_t *jt;
  int64_t xr_x8;
  code_t *xr_x9;
  word_t xr_x9_00;
  code_t *xr_x9_01;
  word_t xr_x10;
  word_t uv5;
  int64_t ctx;
  sk_u128_t auVar6;
  
  uv2 = sk_rt_00407ca0();
  sk_rt_0040700c();
  uv5 = *(word_t *)(ctx + 0x38);
  uv3 = sk_rt_00406420();
  if ((bool)zero_cc) {
    sk_rt_0040711c(*(word_t *)(ctx + 0x48),uv3,*(word_t *)(ctx + 0x40));
    ((code_t)xr_x9)();
    sk_rt_00407604();
    sk_rt_0040686c();
    sk_rt_0040bd24(uv5);
    auVar6 = sk_rt_0040678c();
    sk_rt_00407e58(auVar6.lo,auVar6.hi,uv2);
                    /* WARNING: Could not recover jumptable at 0x003eb418. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    ((code_t)jt0)();
    return;
  }
  ln1 = *(int64_t *)(ctx + 0x18);
  sk_rt_00406894(*(word_t *)(ctx + 0x58),*(word_t *)(ctx + 0x60));
  *(word_t *)(ctx + 0x78) = xr_x9_00;
  *(word_t *)(ctx + 0x80) = xr_x10;
  sk_rt_00350624();
  ((code_t)xr_x9_01)();
  sk_rt_004062e8((int64_t)*(int32_t *)(ln1 + 0x28));
  lp4 = (int64_t *)sk_rt_0040bb18(*(uint32_t *)(xr_x8 + 4));
  *(int64_t **)(ctx + 0x88) = lp4;
  *lp4 = ctx;
  lp4[1] = (int64_t)(word_t)&sk_lab_003eb4b4;
  sk_rt_00406bb4(*(word_t *)(ctx + 0x60));
                    /* WARNING: Could not recover jumptable at 0x003eb4b0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  ((code_t)jt)();
  return;
}



/* void FUN_003eb594(void) */

void sk_slice57_003eb594()

{
  uint64_t uv1;
  code_t *jt;
  code_t *xr_x9;
  code_t *xr_x9_00;
  int64_t ctx;
  sk_u128_t auVar2;
  
  sk_rt_00407000();
  if (*(char *)(ctx + 0x98) == '\x01') {
    sk_rt_00407d14(*(word_t *)(ctx + 0x80));
    uv1 = ((code_t)xr_x9)();
    auVar2.hi = 0;
    auVar2.lo = uv1;
  }
  else {
    sk_rt_00408280();
    ((code_t)xr_x9_00)();
    auVar2 = sk_rt_00408354();
  }
  sk_rt_004069b0(auVar2.lo,auVar2.hi);
  sk_rt_004070a0();
  sk_rt_0040bd24();
  sk_rt_0040678c();
                    /* WARNING: Could not recover jumptable at 0x003eb618. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  ((code_t)jt)();
  return;
}



/* void FUN_003eb68c(undefined8 param_1,undefined8 param_2,undefined8 param_3,long param_4) */

void sk_slice57_003eb68c(word_t  param_1, word_t  param_2, word_t  param_3, int64_t  param_4, word_t param_5)

{
  word_t uv1;
  int64_t xr_x8;
  int64_t xr_x8_00;
  int64_t xr_x8_01;
  code_t *xr_x8_02;
  word_t xr_x8_03;
  word_t xr_x8_04;
  word_t xr_x16;
  word_t xr_x16_00;
  word_t xr_x16_01;
  int64_t in_r21;
  int64_t ctx;
  
  sk_rt_00407c8c();
  sk_rt_0040700c();
  sk_rt_00406c1c();
  *(word_t *)(ctx + 0x40) = *(word_t *)(param_4 + 0x10);
  uv1 = sk_rt_0040684c();
  *(word_t *)(ctx + 0x48) = uv1;
  sk_rt_00352018();
  *(word_t *)(ctx + 0x50) = xr_x16;
  uv1 = sk_rt_004078e8(*(word_t *)(xr_x8 + 0x40));
  *(word_t *)(ctx + 0x58) = uv1;
  uv1 = sk_rt_00406dd0();
  *(word_t *)(ctx + 0x60) = uv1;
  sk_rt_00350798();
  uv1 = sk_rt_00310d68();
  *(word_t *)(ctx + 0x68) = uv1;
  sk_rt_00352018();
  *(word_t *)(ctx + 0x70) = xr_x16_00;
  uv1 = sk_rt_004078e8(*(word_t *)(xr_x8_00 + 0x40));
  *(word_t *)(ctx + 0x78) = uv1;
  sk_rt_0040683c();
  *(word_t *)(ctx + 0x80) = xr_x16_01;
  uv1 = sk_rt_004078e8(*(word_t *)(xr_x8_01 + 0x40));
  *(word_t *)(ctx + 0x88) = uv1;
  if (in_r21 == 0) {
    sk_rt_00407248();
    uv1 = xr_x8_04;
  }
  else {
    sk_rt_00406590();
    ((code_t)xr_x8_02)();
    sk_rt_0008e1ec();
    uv1 = xr_x8_03;
  }
  *(word_t *)(ctx + 0x90) = uv1;
  *(word_t *)(ctx + 0x98) = param_3;
  sk_rt_00353080();
  sk_rt_00407c78();
  sk_rt_00408db8();
  return;
}



/* void FUN_003eb7c4(void) */

void sk_slice57_003eb7c4()

{
  word_t uv1;
  int64_t ln2;
  word_t uv3;
  word_t *wp4;
  code_t *jt0;
  code_t *jt;
  code_t *xr_x16;
  word_t xr_x17;
  int64_t ctx;
  sk_u128_t auVar5;
  
  uv3 = sk_rt_0040790c();
  sk_rt_004070d8();
  if ((**(uint8_t **)(ctx + 0x30) & 1) != 0) {
    sk_rt_00407960();
    uv1 = *(word_t *)(ctx + 0x58);
    sk_rt_0040686c();
    sk_rt_0040bd24();
    sk_rt_0040bd24(uv1);
    auVar5 = sk_rt_0040678c();
    sk_rt_004079b4(auVar5.lo,auVar5.hi,uv3);
                    /* WARNING: Could not recover jumptable at 0x003eb834. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    ((code_t)jt0)();
    return;
  }
  ln2 = *(int64_t *)(ctx + 0x40);
  sk_rt_0040652c();
  uv3 = sk_rt_00406608();
  *(word_t *)(ctx + 0xa0) = uv3;
  uv3 = sk_rt_00406e8c();
  *(word_t *)(ctx + 0xa8) = uv3;
  sk_rt_00406288();
  sk_rt_0040bb18(*(uint32_t *)(ln2 + 4));
  wp4 = (word_t *)sk_rt_00406fe0();
  *(word_t **)(ctx + 0xb0) = wp4;
  *wp4 = xr_x17;
  uv3 = sk_rt_00407830();
  sk_rt_00406d70(uv3,*(word_t *)(ctx + 0x18),*(word_t *)(ctx + 0x20));
  jt = xr_x16;
  sk_rt_004080cc();
                    /* WARNING: Could not recover jumptable at 0x003eb8d8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  ((code_t)jt)();
  return;
}



/* void FUN_003eb9c8(void) */

void sk_slice57_003eb9c8()

{
  int64_t ln1;
  uint8_t zero_cc;
  word_t uv2;
  word_t uv3;
  int64_t *lp4;
  code_t *jt0;
  code_t *jt;
  int64_t xr_x8;
  code_t *xr_x9;
  word_t xr_x9_00;
  code_t *xr_x9_01;
  word_t xr_x10;
  word_t uv5;
  int64_t ctx;
  sk_u128_t auVar6;
  
  uv2 = sk_rt_00407ca0();
  sk_rt_0040700c();
  uv5 = *(word_t *)(ctx + 0x60);
  uv3 = sk_rt_00406420();
  if ((bool)zero_cc) {
    sk_rt_0040711c(*(word_t *)(ctx + 0x70),uv3,*(word_t *)(ctx + 0x68));
    ((code_t)xr_x9)();
    sk_rt_00407960();
    uv3 = *(word_t *)(ctx + 0x58);
    sk_rt_0040686c();
    sk_rt_0040bd24(uv5);
    sk_rt_0040bd24(uv3);
    auVar6 = sk_rt_0040678c();
    sk_rt_00407e58(auVar6.lo,auVar6.hi,uv2);
                    /* WARNING: Could not recover jumptable at 0x003eba50. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    ((code_t)jt0)();
    return;
  }
  ln1 = *(int64_t *)(ctx + 0x28);
  sk_rt_00406894(*(word_t *)(ctx + 0x80),*(word_t *)(ctx + 0x88));
  *(word_t *)(ctx + 0xb8) = xr_x9_00;
  *(word_t *)(ctx + 0xc0) = xr_x10;
  sk_rt_00350624();
  ((code_t)xr_x9_01)();
  sk_rt_004062e8((int64_t)*(int32_t *)(ln1 + 0x28));
  lp4 = (int64_t *)sk_rt_0040bb18(*(uint32_t *)(xr_x8 + 4));
  *(int64_t **)(ctx + 200) = lp4;
  *lp4 = ctx;
  lp4[1] = (int64_t)(word_t)&sk_lab_003ebaec;
  sk_rt_00406bb4(*(word_t *)(ctx + 0x88));
                    /* WARNING: Could not recover jumptable at 0x003ebae8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  ((code_t)jt)();
  return;
}



/* void FUN_003ebbd4(void) */

void sk_slice57_003ebbd4()

{
  word_t uv1;
  uint64_t uv2;
  code_t *jt;
  int64_t ctx;
  sk_u128_t auVar3;
  
  sk_rt_00406fd4();
  if (*(char *)(ctx + 0xd8) == '\x01') {
    uv2 = (**(code_t **)(ctx + 0xb8))
                      (*(word_t *)(ctx + 0xc0),*(word_t *)(ctx + 0x10),
                       *(word_t *)(ctx + 0x88),*(word_t *)(ctx + 0x60));
    auVar3.hi = 0;
    auVar3.lo = uv2;
  }
  else {
    (**(code_t **)(*(int64_t *)(ctx + 0x80) + 8))
              (*(word_t *)(ctx + 0x88),*(word_t *)(ctx + 0x60));
    auVar3 = sk_rt_00408354();
  }
  sk_rt_00407960(auVar3.lo,auVar3.hi);
  uv1 = *(word_t *)(ctx + 0x58);
  sk_rt_004070a0(*(word_t *)(ctx + 0x10));
  sk_rt_0040bd24();
  sk_rt_0040bd24(uv1);
  sk_rt_0040678c();
                    /* WARNING: Could not recover jumptable at 0x003ebc84. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  ((code_t)jt)();
  return;
}



/* void FUN_003ebd9c(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4, undefined8 param_5) */

void sk_slice57_003ebd9c(word_t  param_1, word_t  param_2, word_t  param_3, word_t  param_4, word_t  param_5)

{
  int64_t *lp1;
  int64_t ctx;
  
  *(word_t *)(ctx + 0x10) = param_4;
  lp1 = (int64_t *)sk_rt_0040bb18(sk_d_005a00ec);
  *(int64_t **)(ctx + 0x18) = lp1;
  *lp1 = ctx;
  lp1[1] = (int64_t)(word_t)&sk_d_004060bc;
  sk_slice57_003eb68c((word_t)lp1,(word_t)param_1,(word_t)param_2,(word_t)param_3,(word_t)param_5);
  return;
}



/* void FUN_003ebe6c(void) */

void sk_slice57_003ebe6c()

{
  code_t *xr_x9;
  code_t *in_r19;
  int64_t in_r21;
  word_t in_r30;
  
  sk_rt_00084220();
  sk_rt_0008409c();
  sk_rt_0040654c();
  sk_rt_003513b4();
  sk_rt_00377824();
  sk_rt_00351f10();
  sk_rt_0007c1a4();
  ((code_t)sk_d_00658c80)();
  sk_rt_0034b05c();
  sk_rt_00407100();
  sk_rt_00350518();
  ((code_t)xr_x9)();
  sk_rt_004082a8((int64_t)*(int32_t *)(in_r21 + 0x24));
  sk_rt_00407700();
  ((code_t)in_r19)();
  sk_rt_00084234(in_r30);
  return;
}



/* undefined1 [16] FUN_003ebf10(void) */

sk_u128_t sk_slice57_003ebf10()

{
  int64_t ln1;
  code_t *fptr2;
  word_t uv3;
  word_t uv4;
  sk_u128_t auVar5;
  
  ln1 = sk_rt_00409484();
  if (ln1 == 0) {
    uv4 = 0x80000000005dbf70;
    uv3 = 0xd000000000000013;
  }
  else {
    fptr2 = (code_t *)sk_rt_00027724(0x671848);
    ((code_t)fptr2)(0x677790,0x671848);
    sk_rt_000e72d4();
    sk_rt_003a25d4(0x671848);
    sk_rt_00408108();
    uv3 = 0x4a64656e776f6e55;
    uv4 = 0xef203a646928626f;
  }
  auVar5.hi = uv4;
  auVar5.lo = uv3;
  return auVar5;
}



/* void FUN_003ebfe8(void) */

void sk_slice57_003ebfe8()

{
  word_t uv1;
  word_t uv2;
  code_t *fptr3;
  word_t uv4;
  word_t xr_x1;
  code_t *xr_x8;
  
  sk_rt_0008409c();
  sk_rt_0031986c(xr_x1);
  sk_rt_0034bcf0();
  uv1 = ((code_t)xr_x8)();
  sk_rt_00350878(0xff);
  sk_rt_00377824();
  sk_rt_003507e0();
  sk_rt_00351e3c();
  uv2 = sk_rt_00377bec();
  fptr3 = (code_t *)sk_rt_003d4658();
  sk_rt_00350500();
  uv4 = sk_rt_00377dcc();
  ((code_t)fptr3)(uv4,uv2);
  sk_rt_0036b118(uv1);
  sk_rt_003507e0();
  return;
}



/* void FUN_003ec094(void) */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sk_slice57_003ec094()

{
  sk_d_006adf30 = sk_rt_0036a9d4(0x6578a0,0x6c0b68);
  return;
}



/* void FUN_003ec098(void) */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sk_slice57_003ec098()

{
  sk_d_006adf30 = sk_rt_0036a9d4(0x6578a0,0x6c0b68);
  return;
}



/* undefined1 * FUN_003ec0c4(void) */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint8_t * sk_slice57_003ec0c4(void)

{
  if (sk_d_006c0b58 != -1) {
    sk_rt_0039a128((word_t)&sk_d_006c0b58,sk_slice57_003ec094);
  }
  return (word_t)&sk_d_006adf30;
}



/* void FUN_003ec12c(void) */

void sk_slice57_003ec12c()

{
  sk_rt_00409414();
  return;
}



/* void FUN_003ec130(void) */

void sk_slice57_003ec130()

{
  sk_rt_00409414();
  return;
}



/* void FUN_003ec144(void) */

void sk_slice57_003ec144()

{
  word_t *wp1;
  
  wp1 = (word_t *)sk_slice57_003ec0c4();
  sk_rt_0036b270(*wp1);
  return;
}



/* void FUN_003ec148(void) */

void sk_slice57_003ec148()

{
  word_t *wp1;
  
  wp1 = (word_t *)sk_slice57_003ec0c4();
  sk_rt_0036b270(*wp1);
  return;
}



/* void FUN_003ec178(void) */

void sk_slice57_003ec178()

{
  uint8_t uv1;
  word_t uv2;
  int64_t ctx;
  
  sk_rt_00407000();
  *(int64_t *)(ctx + 0x10) = ctx;
  *(code_t **)(ctx + 0x18) = sk_slice57_003ec20c;
  uv2 = sk_rt_0040ab60(ctx + 0x18,ctx + 0x10,0);
  uv1 = sk_slice57_003ecc18();
  sk_rt_0040aac8(uv1,uv2);
  sk_rt_00409354();
  sk_rt_0040ada4(ctx + 0x10);
  return;
}



/* void FUN_003ec20c(void) */

void sk_slice57_003ec20c()

{
  int64_t *ctx;
  
  sk_rt_00407000();
                    /* WARNING: Could not recover jumptable at 0x003ec2a0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code_t **)(*ctx + 8))(*ctx);
  return;
}



/* void FUN_003ec438(void) */

void sk_slice57_003ec438()

{
  sk_u128_t auVar1;
  
  auVar1 = sk_rt_00407128();
                    /* WARNING: Could not recover jumptable at 0x003ec450. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  ((code_t)auVar1.hi)(auVar1.lo & 0xffffffffffff | 0xd707000000000000);
  return;
}



/* void FUN_003ec4dc(void) */

void sk_slice57_003ec4dc()

{
  word_t uv1;
  int64_t xr_x8;
  int64_t xr_x9;
  int64_t *xr_x10;
  code_t *fptr2;
  int64_t in_r20;
  
  sk_rt_00407000();
  sk_rt_00407018();
  sk_rt_0040691c();
  *xr_x10 = xr_x9;
  uv1 = *(word_t *)(xr_x8 + 0x38);
  *(int64_t *)(xr_x9 + 0x40) = in_r20;
  sk_rt_0040bd24(uv1);
  if (in_r20 == 0) {
    fptr2 = sk_slice57_003ec598;
  }
  else {
    fptr2 = (code_t *)(word_t)&sk_lab_003ec5f8;
  }
  sk_rt_00353498(fptr2);
  sk_rt_00408db8();
  return;
}



/* void FUN_003ec598(void) */

void sk_slice57_003ec598()

{
  code_t *jt;
  int64_t ctx;
  sk_u128_t auVar1;
  
  sk_rt_00407000();
  sk_rt_0031dc0c(0,*(word_t *)(ctx + 0x20),*(word_t *)(ctx + 0x28),
               *(word_t *)(ctx + 0x30));
  auVar1 = sk_rt_0035a7e8();
  sk_rt_00369340(auVar1.lo,auVar1.hi,0);
  sk_rt_00407128();
                    /* WARNING: Could not recover jumptable at 0x003ec5f4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  ((code_t)jt)();
  return;
}



/* void FUN_003ec6c8(void) */

void sk_slice57_003ec6c8()

{
  sk_rt_00406fd4();
  sk_rt_00407030();
  sk_rt_00406490();
  return;
}



/* void FUN_003ec708(void) */

void sk_slice57_003ec708()

{
  code_t *fptr1;
  
  sk_rt_00407030();
  sk_rt_00406490();
                    /* WARNING: Does not return */
  fptr1 = (code_t *)SoftwareBreakpoint(1,0x3ec730);
  ((code_t)fptr1)();
}



/* void FUN_003ec730(void) */

void sk_slice57_003ec730()

{
  code_t *fptr1;
  
  sk_rt_00407030();
  sk_rt_00406490();
                    /* WARNING: Does not return */
  fptr1 = (code_t *)SoftwareBreakpoint(1,0x3ec758);
  ((code_t)fptr1)();
}



/* void FUN_003ec758(void) */

void sk_slice57_003ec758()

{
  code_t *fptr1;
  
  sk_rt_00407030();
  sk_rt_00406490();
                    /* WARNING: Does not return */
  fptr1 = (code_t *)SoftwareBreakpoint(1,0x3ec780);
  ((code_t)fptr1)();
}



/* void FUN_003ec780(void) */

void sk_slice57_003ec780()

{
  code_t *fptr1;
  
  sk_rt_00407030();
  sk_rt_00406490();
                    /* WARNING: Does not return */
  fptr1 = (code_t *)SoftwareBreakpoint(1,0x3ec7a8);
  ((code_t)fptr1)();
}



/* void FUN_003ec7bc(void) */

void sk_slice57_003ec7bc()

{
  sk_rt_00406fd4();
  sk_rt_00407030();
  sk_rt_00406490();
  return;
}



/* void FUN_003ec7fc(void) */

void sk_slice57_003ec7fc()

{
  code_t *fptr1;
  
  sk_rt_00407030();
  sk_rt_00406490();
                    /* WARNING: Does not return */
  fptr1 = (code_t *)SoftwareBreakpoint(1,0x3ec824);
  ((code_t)fptr1)();
}



/* void FUN_003ec824(void) */

void sk_slice57_003ec824()

{
  code_t *fptr1;
  
  sk_rt_00407030();
  sk_rt_00406490();
                    /* WARNING: Does not return */
  fptr1 = (code_t *)SoftwareBreakpoint(1,0x3ec84c);
  ((code_t)fptr1)();
}



/* void FUN_003ec84c(void) */

void sk_slice57_003ec84c()

{
  code_t *fptr1;
  
  sk_rt_00407030();
  sk_rt_00406490();
                    /* WARNING: Does not return */
  fptr1 = (code_t *)SoftwareBreakpoint(1,0x3ec874);
  ((code_t)fptr1)();
}



/* void FUN_003ec874(void) */

void sk_slice57_003ec874()

{
  code_t *fptr1;
  
  sk_rt_00407030();
  sk_rt_00406490();
                    /* WARNING: Does not return */
  fptr1 = (code_t *)SoftwareBreakpoint(1,0x3ec89c);
  ((code_t)fptr1)();
}



/* void FUN_003ec8a0(undefined8 param_1,undefined8 param_2) */

void sk_slice57_003ec8a0(word_t  param_1, word_t  param_2)

{
  sk_rt_002298d4(param_2);
  return;
}



/* void FUN_003ec8c8(undefined8 param_1) */

void sk_slice57_003ec8c8(word_t  param_1)

{
  sk_rt_004080b0();
  sk_rt_002298d4(param_1);
  sk_rt_001a8564();
  return;
}



/* void FUN_003ec918(void) */

void sk_slice57_003ec918()

{
  word_t *in_r20;
  uint8_t stack_slot_104 [72];
  
  sk_rt_001a84f4(stack_slot_104);
  sk_slice57_003ec8a0((word_t)stack_slot_104,(word_t)*in_r20);
  sk_rt_001a8564();
  return;
}



/* long FUN_003ec9c4(int param_1) */

int64_t sk_slice57_003ec9c4(int32_t  param_1)

{
  uint32_t uv1;
  uint32_t uv2;
  int64_t ln3;
  code_t *fptr4;
  int64_t xr_x8;
  int64_t xr_x8_00;
  int64_t xr_x8_01;
  word_t loc_40;
  
  uv2 = param_1 - 9U >> 2 & 0x3f;
  uv1 = (param_1 - 9U) * 0x40;
  if ((uv2 | uv1 & 0xff) < 5) {
    switch(uv2 | uv1 & 0xff) {
    default:
      ln3 = -0x2fffffffffffffe9;
      break;
    case 1:
      goto switchD_003eca14_caseD_1;
    case 2:
      sk_rt_004078c0(sk_s_taskpriority_low_005dc090);
      ln3 = xr_x8_00 + -7;
      break;
    case 3:
      sk_rt_004078c0(sk_s_taskpriority_medium_005dc070);
      ln3 = xr_x8 + -4;
      break;
    case 4:
      sk_rt_004078c0(sk_s_taskpriority_high_005dc050);
      ln3 = xr_x8_01 + -6;
    }
  }
  else {
switchD_003eca14_caseD_1:
    sk_rt_000b430c();
    sk_rt_002a4ab4(0x10);
    sk_rt_003a25d4(loc_40);
    fptr4 = (code_t *)sk_rt_00027724(0x670738);
    ((code_t)fptr4)((word_t)&sk_u_006775b0,0x670738);
    sk_rt_000e72d4();
    sk_rt_003a25d4(0x670738);
    sk_rt_00408108();
    ln3 = -0x2fffffffffffffe9;
  }
  return ln3;
}



/* void FUN_003ecb1c(void) */

void sk_slice57_003ecb1c()

{
  sk_rt_001c9a1c();
  return;
}



/* void FUN_003ecb20(void) */

void sk_slice57_003ecb20()

{
  sk_rt_001c9a1c();
  return;
}



/* void FUN_003ecb48(undefined8 param_1) */

void sk_slice57_003ecb48(word_t  param_1)

{
  uint8_t *in_r20;
  
  sk_slice57_003ecb64((word_t)param_1,(word_t)*in_r20);
  return;
}



/* void FUN_003ecb4c(undefined8 param_1) */

void sk_slice57_003ecb4c(word_t  param_1)

{
  uint8_t *in_r20;
  
  sk_slice57_003ecb64((word_t)param_1,(word_t)*in_r20);
  return;
}



/* void FUN_003ecb64(long param_1,undefined8 param_2) */

void sk_slice57_003ecb64(int64_t  param_1, word_t  param_2)

{
  word_t uv1;
  word_t uv2;
  code_t *fptr3;
  uint8_t stack_slot_104 [24];
  word_t loc_80;
  word_t stack_slot_72;
  
  uv1 = *(word_t *)(param_1 + 0x18);
  uv2 = *(word_t *)(param_1 + 0x20);
  sk_rt_0006a4c0(param_1,uv1);
  fptr3 = (code_t *)sk_rt_000a649c(uv2);
  ((code_t)fptr3)(stack_slot_104,uv1,uv2);
  sk_rt_000836a4(stack_slot_104,loc_80);
  fptr3 = (code_t *)sk_rt_00319f3c(stack_slot_72);
  ((code_t)fptr3)(param_2,loc_80,stack_slot_72);
  sk_rt_000026e8(stack_slot_104);
  return;
}



/* ulong FUN_003ecc18(void) */

uint64_t sk_slice57_003ecc18()

{
  int64_t ln1;
  uint64_t uv2;
  
  ln1 = sk_rt_0040880c();
  if (ln1 != 0) {
    sk_rt_0036b270();
    uv2 = sk_rt_00409c10();
    sk_rt_0036b118(ln1);
    return uv2;
  }
  uv2 = sk_rt_00408898();
  if ((int64_t)uv2 < 0) {
    sk_rt_003488bc(1);
    sk_rt_00349a54();
  }
  else {
    if (uv2 < 0x100) {
      return uv2;
    }
    sk_rt_003488bc(1);
    sk_rt_00349a54();
  }
                    /* WARNING: Subroutine does not return */
  sk_rt_001afe4c();
}



/* void FUN_003eccc4(void) */

void sk_slice57_003eccc4()

{
  int64_t ln1;
  word_t xr_x8;
  code_t *in_r19;
  
  sk_rt_00350c5c();
  ln1 = sk_rt_0040880c();
  if (ln1 == 0) {
    ((code_t)in_r19)(xr_x8);
  }
  else {
    sk_rt_0036b270();
    ((code_t)in_r19)(xr_x8);
    sk_rt_0036b118(ln1);
  }
  return;
}



/* uint FUN_003ecd44(void) */

uint32_t sk_slice57_003ecd44()

{
  uint32_t uv1;
  int64_t ln2;
  
  ln2 = sk_rt_0040880c();
  if (ln2 == 0) {
    uv1 = 0;
  }
  else {
    sk_rt_0036b270();
    uv1 = sk_rt_00409c1c();
    sk_rt_0036b118(ln2);
  }
  return uv1 & 0xff | (uint32_t)(ln2 == 0) << 8;
}



/* void FUN_003ecd98(void) */

void sk_slice57_003ecd98()

{
  int64_t ln1;
  
  ln1 = sk_rt_004088a0();
  if (ln1 != 0) {
    sk_rt_001e9c00();
  }
  return;
}



/* void FUN_003ecd9c(void) */

void sk_slice57_003ecd9c()

{
  int64_t ln1;
  
  ln1 = sk_rt_004088a0();
  if (ln1 != 0) {
    sk_rt_001e9c00();
  }
  return;
}



/* void FUN_003ecddc(void) */

void sk_slice57_003ecddc()

{
  int32_t iv1;
  int64_t ln2;
  word_t *wp3;
  word_t uv4;
  word_t xr_x17;
  word_t xr_x17_00;
  int32_t *ip5;
  int64_t ctx;
  code_t *loc_48;
  
  sk_rt_00406fd4();
  ln2 = sk_rt_0040880c();
  *(int64_t *)(ctx + 0x28) = ln2;
  ip5 = *(int32_t **)(ctx + 0x18);
  if (ln2 == 0) {
    iv1 = *ip5;
    sk_rt_0040bb18(ip5[1]);
    wp3 = (word_t *)sk_rt_00406fe0();
    *(word_t **)(ctx + 0x38) = wp3;
    *wp3 = xr_x17_00;
    uv4 = sk_rt_004071c0();
    ln2 = 0;
  }
  else {
    sk_rt_0036b270();
    iv1 = *ip5;
    sk_rt_0040bb18(ip5[1]);
    wp3 = (word_t *)sk_rt_00406fe0();
    *(word_t **)(ctx + 0x30) = wp3;
    *wp3 = xr_x17;
    uv4 = sk_rt_004071c0();
  }
  loc_48 = (code_t *)((int64_t)ip5 + (int64_t)iv1);
                    /* WARNING: Could not recover jumptable at 0x003ecf1c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  ((code_t)loc_48)(uv4,ln2);
  return;
}



/* void FUN_003ed0a8(void) */

void sk_slice57_003ed0a8()

{
  word_t uv1;
  word_t *in_r20;
  uint8_t stack_slot_104 [72];
  
  uv1 = *in_r20;
  sk_rt_001a84f4(stack_slot_104);
  sk_slice57_003ec8a0((word_t)stack_slot_104,(word_t)uv1);
  sk_rt_001a8564();
  return;
}



/* void FUN_003ed0ec(void) */

void sk_slice57_003ed0ec()

{
  word_t uv1;
  uint64_t xr_x8;
  
  uv1 = sk_rt_0035ac70(sk_s_unavailable_in_exclaves_005dc0d0);
  uv1 = sk_rt_003593c0(uv1,uv1);
                    /* WARNING: Subroutine does not return */
  sk_rt_001afa84(uv1,0xb,2,0xd000000000000017,xr_x8 | 0x8000000000000000,
               sk_s__concurrency_task_swift_005dc0b0,0x17,2);
}



/* void FUN_003ed14c(void) */

void sk_slice57_003ed14c()

{
  word_t xr_x1;
  code_t *xr_x8;
  sk_u128_t auVar1;
  
  sk_rt_0008409c();
  sk_rt_003fd194(xr_x1);
  sk_rt_0034bcf0();
  auVar1 = ((code_t)xr_x8)();
  sk_rt_00408c4c(auVar1.lo,auVar1.hi,0);
  return;
}



/* void FUN_003ed1a4(undefined8 param_1,undefined8 param_2,undefined8 param_3,code *param_4, undefined8 param_5,undefined8 param_6,undefined8 param_7) */

void sk_slice57_003ed1a4(word_t  param_1, word_t  param_2, word_t  param_3, code_t * param_4, word_t  param_5, word_t  param_6, word_t  param_7)

{
  word_t *stack_addr;
  word_t uv1;
  int64_t ln2;
  int64_t ln3;
  int64_t xr_x8;
  uint8_t *wp4;
  
  uv1 = sk_rt_00027614((word_t)&sk_d_0064c260,(word_t)&sk_d_004bbc30);
  ln2 = sk_rt_0031dc0c(0,param_7,uv1,0x66c1c8);
  ln3 = *(int64_t *)(ln2 + -8);
  ((code_t)sk_d_00658c80)(*(int64_t *)(ln3 + 0x40) + 0xfU & 0xfffffffffffffff0);
  wp4 = stack_addr + -xr_x8;
  sk_rt_00409c24(wp4,param_2,param_3,ln2);
  ((code_t)param_4)(param_1,wp4);
  (**(code_t **)(ln3 + 8))(wp4,ln2);
  return;
}



/* void FUN_003ed2dc(undefined8 param_1,undefined8 param_2,undefined8 param_3) */

void sk_slice57_003ed2dc(word_t  param_1, word_t  param_2, word_t  param_3)

{
  uint8_t stack_slot_96 [16];
  word_t loc_80;
  uint8_t stack_slot_64 [16];
  word_t loc_48;
  word_t stack_slot_40;
  word_t loc_32;
  
  loc_80 = param_3;
  loc_48 = param_3;
  stack_slot_40 = param_1;
  loc_32 = param_2;
  sk_slice57_003ed1a4((word_t)(word_t)&sk_d_005a0138,(word_t)stack_slot_64,(word_t)sk_rt_003fd25c,(word_t)stack_slot_96,(word_t)param_3,(word_t)param_3);
  return;
}



/* void FUN_003ed340(void) */

void sk_slice57_003ed340()

{
  word_t uv1;
  word_t *wp2;
  code_t *jt;
  int64_t in_r3;
  int64_t ln3;
  word_t xr_x17;
  int64_t ctx;
  sk_u128_t auVar4;
  
  auVar4 = sk_rt_00406fd4();
  *(int64_t *)(ctx + 0x10) = auVar4.lo;
  *(int64_t *)(ctx + 0x18) = in_r3;
  ln3 = *(int64_t *)(in_r3 + -8);
  *(int64_t *)(ctx + 0x20) = ln3;
  uv1 = sk_rt_004078e8(*(word_t *)(ln3 + 0x40));
  *(word_t *)(ctx + 0x28) = uv1;
  sk_rt_00407280();
  sk_rt_0040bb18(*(uint32_t *)(auVar4.hi + 4));
  wp2 = (word_t *)sk_rt_00406fe0();
  *(word_t **)(ctx + 0x30) = wp2;
  *wp2 = xr_x17;
  sk_rt_0040838c();
                    /* WARNING: Could not recover jumptable at 0x003ed414. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  ((code_t)jt)();
  return;
}



/* void FUN_003ed4d4(void) */

void sk_slice57_003ed4d4()

{
  word_t uv1;
  word_t uv2;
  code_t *jt;
  word_t uv3;
  int64_t ctx;
  sk_u128_t auVar4;
  
  sk_rt_00406fd4();
  (**(code_t **)(*(int64_t *)(ctx + 0x20) + 0x20))
            (*(word_t *)(ctx + 0x10),*(word_t *)(ctx + 0x28),
             *(word_t *)(ctx + 0x18));
  uv3 = *(word_t *)(ctx + 0x28);
  uv1 = *(word_t *)(ctx + 0x18);
  sk_rt_0034a210();
  auVar4 = sk_rt_00027614();
  uv2 = sk_rt_004063b4(auVar4.lo,auVar4.hi,auVar4.lo);
  sk_rt_0031dc0c(uv2,uv1);
  auVar4 = sk_rt_00356b98();
  sk_rt_00369340(auVar4.lo,auVar4.hi,0);
  sk_rt_0040bd24(uv3);
  sk_rt_00407128();
                    /* WARNING: Could not recover jumptable at 0x003ed568. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  ((code_t)jt)();
  return;
}



/* void FUN_003ed5f8(undefined8 param_1,undefined8 param_2,undefined8 param_3) */

void sk_slice57_003ed5f8(word_t  param_1, word_t  param_2, word_t  param_3)

{
  word_t uv1;
  code_t *xr_x8;
  int64_t xr_x12;
  sk_u128_t auVar2;
  uint8_t loc_56 [8];
  
  sk_rt_0034a210();
  auVar2 = sk_rt_00027614();
  uv1 = sk_rt_004063b4(auVar2.lo,auVar2.hi,auVar2.lo);
  uv1 = sk_rt_0031dc0c(uv1,param_3);
  sk_rt_000a6f88();
  sk_rt_0007c1a4();
  ((code_t)sk_d_00658c80)();
  sk_rt_00407b80();
  auVar2 = sk_rt_00351384(*(word_t *)(xr_x12 + 0x10));
  ((code_t)xr_x8)(auVar2.lo,auVar2.hi,uv1);
  sk_rt_0027ed7c(param_1,uv1,loc_56);
  return;
}



/* void FUN_003ed6d0(undefined8 param_1,undefined8 param_2,undefined8 param_3,int *param_4, undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8, long param_9,undefined8 param_10,undefined8 param_11) */

void sk_slice57_003ed6d0(word_t  param_1, word_t  param_2, word_t  param_3, int32_t * param_4, word_t  param_5, word_t  param_6, word_t  param_7, word_t  param_8, int64_t  param_9, word_t  param_10, word_t  param_11)

{
  int32_t iv1;
  word_t uv2;
  word_t uv3;
  int64_t *lp4;
  int64_t ln5;
  int64_t ctx;
  
  *(int64_t *)(ctx + 0x20) = param_9;
  *(word_t *)(ctx + 0x28) = param_11;
  *(word_t *)(ctx + 0x10) = param_2;
  *(word_t *)(ctx + 0x18) = param_3;
  ln5 = *(int64_t *)(param_9 + -8);
  *(int64_t *)(ctx + 0x30) = ln5;
  uv2 = sk_rt_0040bb18(*(int64_t *)(ln5 + 0x40) + 0xfU & 0xfffffffffffffff0);
  *(word_t *)(ctx + 0x38) = uv2;
  uv3 = sk_rt_0040a9f4(param_6,param_7);
  *(word_t *)(ctx + 0x40) = uv3;
  iv1 = *param_4;
  lp4 = (int64_t *)sk_rt_0040bb18(param_4[1]);
  *(int64_t **)(ctx + 0x48) = lp4;
  *lp4 = ctx;
  lp4[1] = (int64_t)(word_t)&sk_lab_003ed834;
                    /* WARNING: Could not recover jumptable at 0x003ed830. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code_t *)((int64_t)param_4 + (int64_t)iv1))(lp4,param_1,param_2,param_3,uv2);
  return;
}



/* void FUN_003ed930(void) */

void sk_slice57_003ed930()

{
  word_t uv1;
  code_t *jt;
  int64_t ctx;
  
  sk_rt_00407000();
  uv1 = *(word_t *)(ctx + 0x38);
  sk_rt_0040aa98(*(word_t *)(ctx + 0x40));
  sk_rt_0040bd24(uv1);
  sk_rt_0040678c();
                    /* WARNING: Could not recover jumptable at 0x003ed980. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  ((code_t)jt)();
  return;
}



/* void FUN_003edad4(void) */

void sk_slice57_003edad4()

{
  int64_t ln1;
  int64_t ln2;
  word_t *wp3;
  code_t *jt;
  word_t xr_x17;
  word_t uv4;
  int64_t ctx;
  word_t uv5;
  word_t uv6;
  word_t uv7;
  word_t uv8;
  word_t uv9;
  word_t uv10;
  
  sk_rt_004070d8();
  uv4 = *(word_t *)(ctx + 0x58);
  ln1 = sk_rt_0040bb18(0x40);
  *(int64_t *)(ctx + 0x78) = ln1;
  uv10 = *(word_t *)(ctx + 0x50);
  uv9 = *(word_t *)(ctx + 0x48);
  uv7 = *(word_t *)(ctx + 0x20);
  uv5 = *(word_t *)(ctx + 0x18);
  ln2 = sk_rt_0040bb18(0x20);
  uv8 = *(word_t *)(ctx + 0x30);
  uv6 = *(word_t *)(ctx + 0x28);
  *(word_t *)(ln1 + 0x18) = uv10;
  *(word_t *)(ln1 + 0x10) = uv9;
  *(word_t *)(ln1 + 0x20) = uv4;
  *(word_t *)(ln1 + 0x30) = uv7;
  *(word_t *)(ln1 + 0x28) = uv5;
  *(int64_t *)(ctx + 0x80) = ln2;
  *(word_t *)(ln2 + 0x18) = uv8;
  *(word_t *)(ln2 + 0x10) = uv6;
  sk_rt_00407db0(0x5a0158);
  sk_rt_0040bb18();
  wp3 = (word_t *)sk_rt_00406fe0();
  *(word_t **)(ctx + 0x88) = wp3;
  *wp3 = xr_x17;
  wp3[1] = (word_t)&sk_lab_003edbfc;
                    /* WARNING: Could not recover jumptable at 0x003edbf8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*jt)
            (*(word_t *)(ctx + 0x10),*(word_t *)(ctx + 0x38),
             *(word_t *)(ctx + 0x40),0x5a0150,ln1,0x3fd354,ln2,
             *(word_t *)(ctx + 0x48),*(word_t *)(ctx + 0x50),
             *(word_t *)(ctx + 0x58),*(word_t *)(ctx + 0x70));
  return;
}



/* void FUN_003edf5c(void) */

void sk_slice57_003edf5c()

{
  code_t *jt;
  int64_t ctx;
  
  sk_rt_00407000();
  sk_rt_0040bd24(*(word_t *)(ctx + 0x38));
  sk_rt_0040678c();
                    /* WARNING: Could not recover jumptable at 0x003edfa4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  ((code_t)jt)();
  return;
}



/* void FUN_003ee090(void) */

void sk_slice57_003ee090()

{
  int32_t iv1;
  word_t uv2;
  word_t *wp3;
  word_t xr_x17;
  int32_t *ip4;
  int64_t ctx;
  
  sk_rt_00407000();
  ip4 = *(int32_t **)(ctx + 0x18);
  uv2 = sk_rt_0040a8d8(*(word_t *)(ctx + 0x28),*(word_t *)(ctx + 0x30));
  *(word_t *)(ctx + 0x48) = uv2;
  iv1 = *ip4;
  sk_rt_0040bb18(ip4[1]);
  wp3 = (word_t *)sk_rt_00406fe0();
  *(word_t **)(ctx + 0x50) = wp3;
  *wp3 = xr_x17;
  sk_rt_004071c0();
                    /* WARNING: Could not recover jumptable at 0x003ee148. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code_t *)((int64_t)ip4 + (int64_t)iv1))();
  return;
}



/* void FUN_003ee234(void) */

void sk_slice57_003ee234()

{
  code_t *jt;
  int64_t ctx;
  
  sk_rt_00407000();
  sk_rt_0040a9b0(*(word_t *)(ctx + 0x48));
  sk_rt_0040678c();
                    /* WARNING: Could not recover jumptable at 0x003ee27c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  ((code_t)jt)();
  return;
}



/* void FUN_003ee310(void) */

void sk_slice57_003ee310()

{
  int64_t ln1;
  uint64_t uv2;
  
  ln1 = sk_rt_0040880c();
  if (ln1 != 0) {
    sk_rt_0036b270();
    uv2 = sk_rt_0040a688();
    sk_rt_0036b118(ln1);
    if ((uv2 & 1) != 0) {
      sk_rt_0035187c(0x67e930,0x67db20);
      sk_rt_0036993c();
      sk_rt_0036986c();
    }
  }
  return;
}



/* void FUN_003ee3c8(void) */

void sk_slice57_003ee3c8()

{
  int64_t ln1;
  word_t uv2;
  word_t *wp3;
  int64_t xr_x8;
  word_t xr_x16;
  word_t xr_x17;
  word_t in_r20;
  int64_t ctx;
  
  ln1 = sk_rt_00407000().lo;
  *(int64_t *)(ctx + 0x10) = ln1;
  *(word_t *)(ctx + 0x18) = in_r20;
  *(word_t *)(ctx + 0x20) = *(word_t *)(ln1 + 0x10);
  uv2 = sk_rt_00310d68(0);
  *(word_t *)(ctx + 0x28) = uv2;
  sk_rt_00352018();
  *(word_t *)(ctx + 0x30) = xr_x16;
  uv2 = sk_rt_004078e8(*(word_t *)(xr_x8 + 0x40));
  *(word_t *)(ctx + 0x38) = uv2;
  sk_rt_00408094();
  wp3 = (word_t *)sk_rt_00406fe0();
  *(word_t **)(ctx + 0x40) = wp3;
  *wp3 = xr_x17;
  sk_rt_004071d0();
  sk_rt_003ef544();
  return;
}



/* void FUN_003ee47c(void) */

void sk_slice57_003ee47c()

{
  int64_t xr_x8;
  
  sk_rt_00407000();
  sk_rt_00407018();
  sk_rt_0040bd24(*(word_t *)(xr_x8 + 0x40));
  sk_rt_00407594();
  sk_rt_00408db8();
  return;
}



/* void FUN_003ee520(void) */

void sk_slice57_003ee520()

{
  word_t uv1;
  word_t *wp2;
  code_t *jt;
  code_t *xr_x9;
  word_t xr_x17;
  word_t uv3;
  int64_t ctx;
  sk_u128_t auVar4;
  
  auVar4 = sk_rt_00407000();
  uv3 = *(word_t *)(ctx + 0x38);
  sk_rt_00351d24(auVar4.lo,auVar4.hi,*(word_t *)(ctx + 0x20));
  uv1 = sk_rt_000839f8();
  sk_rt_0040711c(*(word_t *)(ctx + 0x30),uv1,*(word_t *)(ctx + 0x28));
  ((code_t)xr_x9)();
  if ((int32_t)uv1 == 1) {
    sk_rt_0040bd24(uv3);
    sk_rt_00407128();
                    /* WARNING: Could not recover jumptable at 0x003ee598. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    ((code_t)jt)();
    return;
  }
  sk_rt_00408094();
  wp2 = (word_t *)sk_rt_00406fe0();
  *(word_t **)(ctx + 0x40) = wp2;
  *wp2 = xr_x17;
  sk_rt_004071d0();
  sk_rt_003ef544();
  return;
}



/* void FUN_003ee5e8(undefined8 param_1,undefined8 param_2,undefined8 param_3,long param_4, undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8) */

void sk_slice57_003ee5e8(word_t  param_1, word_t  param_2, word_t  param_3, int64_t  param_4, word_t  param_5, word_t  param_6, word_t  param_7, word_t  param_8)

{
  word_t uv1;
  code_t *xr_x8;
  word_t xr_x8_00;
  word_t xr_x8_01;
  int64_t ctx;
  
  uv1 = sk_rt_00406fd4().lo;
  *(word_t *)(ctx + 0x128) = param_7;
  *(word_t *)(ctx + 0x130) = param_8;
  *(word_t *)(ctx + 0x118) = uv1;
  *(word_t *)(ctx + 0x120) = param_6;
  if (param_4 == 0) {
    sk_rt_00407248();
    uv1 = xr_x8_01;
  }
  else {
    sk_rt_00351da8();
    sk_rt_003d4658(param_5);
    sk_rt_0034bcf0();
    ((code_t)xr_x8)();
    sk_rt_0008e1ec();
    uv1 = xr_x8_00;
  }
  *(word_t *)(ctx + 0x138) = uv1;
  *(word_t *)(ctx + 0x140) = param_3;
  sk_rt_00353080();
  sk_rt_00408db8();
  return;
}



/* void FUN_003ee688(undefined8 param_1,undefined8 param_2,code *UNRECOVERED_JUMPTABLE) */

void sk_slice57_003ee688(word_t  param_1, word_t  param_2, code_t * UNRECOVERED_JUMPTABLE)

{
  word_t *wp1;
  word_t xr_x17;
  int64_t in_r19;
  word_t in_r20;
  int64_t ctx;
  
  sk_rt_00406fd4();
  sk_rt_00408560();
  *(word_t *)(ctx + 0x110) = in_r20;
  sk_rt_00406394();
  sk_rt_0040bb18(*(uint32_t *)(in_r19 + 4));
  wp1 = (word_t *)sk_rt_00406fe0();
  *(word_t **)(ctx + 0x148) = wp1;
  *wp1 = xr_x17;
  sk_rt_00407c04();
                    /* WARNING: Could not recover jumptable at 0x003ee71c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  ((code_t)jt)();
  return;
}



/* void FUN_003ee818(void) */

void sk_slice57_003ee818()

{
  word_t *stack_addr;
  int64_t xr_x16;
  int64_t in_r20;
  
  sk_rt_00407000();
  sk_rt_00407520();
  sk_rt_0040bd24((uint64_t)stack_addr & 0xffffffffffff | 0xc31a000000000000,
               *(word_t *)(in_r20 + 0x150));
  sk_rt_00407444();
  sk_rt_00408db8(sk_slice57_003ee8e4,*(word_t *)(in_r20 + 0x138),*(word_t *)(xr_x16 + 0x140)
              );
  return;
}



/* void FUN_003ee8e4(void) */

void sk_slice57_003ee8e4()

{
  code_t *jt;
  int64_t ctx;
  
  sk_rt_00407000();
  sk_rt_0040d07c(ctx + 0x10);
  sk_rt_00407128();
                    /* WARNING: Could not recover jumptable at 0x003ee92c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  ((code_t)jt)();
  return;
}



/* void FUN_003eead0(void) */

void sk_slice57_003eead0()

{
  code_t *jt;
  int64_t xr_x8;
  int64_t xr_x8_00;
  int64_t *xr_x9;
  
  sk_rt_00407000();
  sk_rt_00407018();
  sk_rt_0040676c();
  *xr_x9 = xr_x8;
  sk_rt_0040bd24(*(word_t *)(xr_x8_00 + 0x128));
  sk_rt_0040d07c(xr_x8 + 0x10);
  sk_rt_00407128();
                    /* WARNING: Could not recover jumptable at 0x003eeb68. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  ((code_t)jt)();
  return;
}



/* void FUN_003eeb6c(void) */

void sk_slice57_003eeb6c()

{
  word_t uv1;
  word_t *wp2;
  word_t xr_x17;
  sk_u128_t auVar3;
  
  uv1 = sk_rt_00407000().lo;
  sk_rt_0040bb18(sk_d_005a0194);
  wp2 = (word_t *)sk_rt_00407ac4();
  *wp2 = xr_x17;
  wp2[1] = sk_slice57_003eebf0;
  auVar3 = sk_rt_00019858(wp2 + 1);
  sk_rt_003ef924(auVar3.lo,auVar3.hi,uv1);
  return;
}



/* void FUN_003eebf0(void) */

void sk_slice57_003eebf0()

{
  code_t *jt;
  int64_t xr_x8;
  
  sk_rt_00407000();
  sk_rt_00407018();
  sk_rt_0040bd24(*(word_t *)(xr_x8 + 0x10));
  sk_rt_00407128();
                    /* WARNING: Could not recover jumptable at 0x003eec88. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  ((code_t)jt)();
  return;
}



/* void FUN_003eec90(undefined8 param_1,undefined8 param_2,undefined8 param_3,long param_4, undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8) */

void sk_slice57_003eec90(word_t  param_1, word_t  param_2, word_t  param_3, int64_t  param_4, word_t  param_5, word_t  param_6, word_t  param_7, word_t  param_8)

{
  word_t uv1;
  code_t *xr_x8;
  word_t xr_x8_00;
  word_t xr_x8_01;
  int64_t ctx;
  
  uv1 = sk_rt_00406fd4().lo;
  *(word_t *)(ctx + 0x128) = param_7;
  *(word_t *)(ctx + 0x130) = param_8;
  *(word_t *)(ctx + 0x118) = uv1;
  *(word_t *)(ctx + 0x120) = param_6;
  if (param_4 == 0) {
    sk_rt_00407248();
    uv1 = xr_x8_01;
  }
  else {
    sk_rt_00351da8();
    sk_rt_003d4658(param_5);
    sk_rt_0034bcf0();
    ((code_t)xr_x8)();
    sk_rt_0008e1ec();
    uv1 = xr_x8_00;
  }
  *(word_t *)(ctx + 0x138) = uv1;
  *(word_t *)(ctx + 0x140) = param_3;
  sk_rt_00353080();
  sk_rt_00408db8();
  return;
}



/* void FUN_003eed30(undefined8 param_1,undefined8 param_2,code *UNRECOVERED_JUMPTABLE) */

void sk_slice57_003eed30(word_t  param_1, word_t  param_2, code_t * UNRECOVERED_JUMPTABLE)

{
  word_t uv1;
  word_t *wp2;
  word_t xr_x17;
  int64_t in_r19;
  word_t in_r20;
  int64_t ctx;
  
  sk_rt_00406fd4();
  sk_rt_00408560();
  sk_rt_0034a210();
  uv1 = sk_rt_00002534();
  *(word_t *)(ctx + 0x148) = uv1;
  *(word_t *)(ctx + 0x110) = in_r20;
  sk_rt_00406394();
  sk_rt_0040bb18(*(uint32_t *)(in_r19 + 4));
  wp2 = (word_t *)sk_rt_00406fe0();
  *(word_t **)(ctx + 0x150) = wp2;
  *wp2 = xr_x17;
  sk_rt_00407c04();
                    /* WARNING: Could not recover jumptable at 0x003eedd0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  ((code_t)jt)();
  return;
}



/* void FUN_003eeef4(void) */

void sk_slice57_003eeef4()

{
  word_t *stack_addr;
  int64_t xr_x16;
  int64_t in_r20;
  
  sk_rt_00407000();
  sk_rt_00407520();
  sk_rt_0040bd24((uint64_t)stack_addr & 0xffffffffffff | 0xc31a000000000000,
               *(word_t *)(in_r20 + 0x160));
  sk_rt_00407444();
  sk_rt_00408db8(sk_rt_003eefc0,*(word_t *)(in_r20 + 0x138),*(word_t *)(xr_x16 + 0x140)
              );
  return;
}



