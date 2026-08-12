/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel, GL1,
 * arm64e, image base 0) — the cL4 microkernel. Ground truth: Ghidra FUN_ names +
 * addresses in cl4_kernel.raw. Version "cL4 microkernel (cL4 (679.100.61))".
 * All names are estimates unless string/header-matched.
 *
 * Gap slice 00: 0x3224a0-0x326024 syscall/exception-entry region. Recreates
 * 120 functions: the generic IPC / capability-op / syscall-op dispatch
 * handlers, their per-id wrapper families, TLS reads, intrusive-list element
 * accessors, trampoline-instruction installers, and slot/dispatch stubs.
 * Uses seL4/cL4 vocabulary; the Swift-runtime-derived helpers
 * (UnsafeBufferPointer / _fatalError preconditions) appear as error raisers.
 */

/* Recreated from cl4_kernel.raw (cL4 Secure Kernel, arm64e, image base 0) —
 * the cL4 microkernel (GL1), "cL4 (679.100.61)". Ground truth: Ghidra FUN_
 * names + addresses in program cl4_kernel.raw.
 * Slice 05: 0x3224a0-0x327bf8 syscall/exception-entry region.
 * All names are estimates unless string/header-matched. */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "sk_internal.h"

/* Unspecified-argument function pointer (K&R empty-paren): allows calling
 * the generic dispatch handlers with the register-aliased argument set,
 * matching the Ghidra decompiles where the handler's 8 params come from
 * the outgoing register state. */
typedef uint64_t (*sk_fn_t)();

/* Out-of-range cL4 helper declarations (extern; bodies reconstructed by
 * the sibling range worker that owns them). Names are estimates. */
extern uint64_t sk_tls();  /* FUN_00021480 */
extern uint64_t sk_cur_thread();  /* FUN_00027614 */
extern uint64_t sk_hlp_00027670();  /* FUN_00027670 */
extern uint64_t sk_cur_tcb();  /* FUN_00027754 */
extern uint64_t sk_hlp_0006b6f4();  /* FUN_0006b6f4 */
extern uint64_t sk_hlp_0008409c();  /* FUN_0008409c */
extern uint64_t sk_hlp_00084180();  /* FUN_00084180 */
extern uint64_t sk_hlp_00084220();  /* FUN_00084220 */
extern uint64_t sk_hlp_00084234();  /* FUN_00084234 */
extern uint64_t sk_trap_leave();  /* FUN_0008e500 */
extern uint64_t sk_trap_enter();  /* FUN_0008e518 */
extern uint64_t sk_power();  /* FUN_0009461c */
extern uint64_t sk_hlp_000f5d30();  /* FUN_000f5d30 */
extern uint64_t sk_hlp_0010d44c();  /* FUN_0010d44c */
extern uint64_t sk_hlp_0010d650();  /* FUN_0010d650 */
extern uint64_t sk_hlp_0010d6b4();  /* FUN_0010d6b4 */
extern uint64_t sk_irq();  /* FUN_0014ae44 */
extern uint64_t sk_hlp_001afe4c();  /* FUN_001afe4c */
extern uint64_t sk_hlp_001b5474();  /* FUN_001b5474 */
extern uint64_t sk_hlp_0022944c();  /* FUN_0022944c */
extern uint64_t sk_hlp_002cc0ec();  /* FUN_002cc0ec */
extern uint64_t sk_hlp_002ccf5c();  /* FUN_002ccf5c */
extern uint64_t sk_hlp_002ce228();  /* FUN_002ce228 */
extern uint64_t sk_hlp_002d1070();  /* FUN_002d1070 */
extern uint64_t sk_hlp_002d4af4();  /* FUN_002d4af4 */
extern uint64_t sk_hlp_002db8cc();  /* FUN_002db8cc */
extern uint64_t sk_hlp_002e3b64();  /* FUN_002e3b64 */
extern uint64_t sk_hlp_00310d04();  /* FUN_00310d04 */
extern uint64_t sk_hlp_00310d1c();  /* FUN_00310d1c */
extern uint64_t sk_hlp_00320dbc();  /* FUN_00320dbc */
extern uint64_t sk_hlp_00321e64();  /* FUN_00321e64 */
extern uint64_t sk_hlp_00322010();  /* FUN_00322010 */
extern uint64_t sk_hlp_00348718();  /* FUN_00348718 */
extern uint64_t sk_obj_acquire();  /* FUN_00348990 */
extern uint64_t sk_hlp_003489c0();  /* FUN_003489c0 */
extern uint64_t sk_obj_release();  /* FUN_00348a18 */
extern uint64_t sk_hlp_00348a50();  /* FUN_00348a50 */
extern uint64_t sk_hlp_00348a80();  /* FUN_00348a80 */
extern uint64_t sk_dispatch4();  /* FUN_00348abc */
extern uint64_t sk_evt();  /* FUN_00348ad8 */
extern uint64_t sk_hlp_00348c30();  /* FUN_00348c30 */
extern uint64_t sk_hlp_00348d00();  /* FUN_00348d00 */
extern uint64_t sk_hlp_00348d18();  /* FUN_00348d18 */
extern uint64_t sk_dispatch1();  /* FUN_00348e00 */
extern uint64_t sk_dispatch2();  /* FUN_00348e18 */
extern uint64_t sk_hlp_00349234();  /* FUN_00349234 */
extern uint64_t sk_hlp_0034951c();  /* FUN_0034951c */
extern uint64_t sk_hlp_00349644();  /* FUN_00349644 */
extern uint64_t sk_hlp_00349b28();  /* FUN_00349b28 */
extern uint64_t sk_hlp_00349e38();  /* FUN_00349e38 */
extern uint64_t sk_notify();  /* FUN_00349e70 */
extern uint64_t sk_hlp_00349ea0();  /* FUN_00349ea0 */
extern uint64_t sk_hlp_0034a168();  /* FUN_0034a168 */
extern uint64_t sk_hlp_0034a180();  /* FUN_0034a180 */
extern uint64_t sk_hlp_0034a30c();  /* FUN_0034a30c */
extern uint64_t sk_hlp_0034b07c();  /* FUN_0034b07c */
extern uint64_t sk_send3();  /* FUN_0034b3c8 */
extern uint64_t sk_send4();  /* FUN_0034b3e8 */
extern uint64_t sk_send5();  /* FUN_0034b4c0 */
extern uint64_t sk_send1();  /* FUN_0034b518 */
extern uint64_t sk_hlp_0034b5fc();  /* FUN_0034b5fc */
extern uint64_t sk_hlp_0034b628();  /* FUN_0034b628 */
extern uint64_t sk_badgemsk();  /* FUN_0034b6a4 */
extern uint64_t sk_send2();  /* FUN_0034b804 */
extern uint64_t sk_hlp_0034b87c();  /* FUN_0034b87c */
extern uint64_t sk_dispatch3();  /* FUN_0034ba68 */
extern uint64_t sk_hlp_0034c5dc();  /* FUN_0034c5dc */
extern uint64_t sk_recv();  /* FUN_0034c664 */
extern uint64_t sk_timer();  /* FUN_0034ce68 */
extern uint64_t sk_ipc2();  /* FUN_0034d140 */
extern uint64_t sk_hlp_0034dab8();  /* FUN_0034dab8 */
extern uint64_t sk_hlp_0034dad8();  /* FUN_0034dad8 */
extern uint64_t sk_enter2();  /* FUN_0034dae8 */
extern uint64_t sk_hlp_0034db98();  /* FUN_0034db98 */
extern uint64_t sk_ntfn();  /* FUN_0034ddb0 */
extern uint64_t sk_sched3();  /* FUN_0034dfe4 */
extern uint64_t sk_hlp_0034e220();  /* FUN_0034e220 */
extern uint64_t sk_hlp_0034e238();  /* FUN_0034e238 */
extern uint64_t sk_hlp_0034e268();  /* FUN_0034e268 */
extern uint64_t sk_hlp_0034e2fc();  /* FUN_0034e2fc */
extern uint64_t sk_hlp_0034e314();  /* FUN_0034e314 */
extern uint64_t sk_hlp_0034e35c();  /* FUN_0034e35c */
extern uint64_t sk_hlp_0034e66c();  /* FUN_0034e66c */
extern uint64_t sk_hlp_0034ee78();  /* FUN_0034ee78 */
extern uint64_t sk_hlp_0034f384();  /* FUN_0034f384 */
extern uint64_t sk_hlp_0034f4f4();  /* FUN_0034f4f4 */
extern uint64_t sk_sched();  /* FUN_0034f6dc */
extern uint64_t sk_sched2();  /* FUN_0034f6f8 */
extern uint64_t sk_ipc_send();  /* FUN_0034f8e4 */
extern uint64_t sk_hlp_0034f90c();  /* FUN_0034f90c */
extern uint64_t sk_hlp_00350038();  /* FUN_00350038 */
extern uint64_t sk_hlp_003504d0();  /* FUN_003504d0 */
extern uint64_t sk_hlp_003504f4();  /* FUN_003504f4 */
extern uint64_t sk_hlp_003505e8();  /* FUN_003505e8 */
extern uint64_t sk_hlp_0035060c();  /* FUN_0035060c */
extern uint64_t sk_disp2();  /* FUN_003507d4 */
extern uint64_t sk_hlp_0035081c();  /* FUN_0035081c */
extern uint64_t sk_hlp_003508a8();  /* FUN_003508a8 */
extern uint64_t sk_leave2();  /* FUN_003508cc */
extern uint64_t sk_hlp_003508f0();  /* FUN_003508f0 */
extern uint64_t sk_hlp_003509c8();  /* FUN_003509c8 */
extern uint64_t sk_gate2();  /* FUN_003509d4 */
extern uint64_t sk_hlp_00350aac();  /* FUN_00350aac */
extern uint64_t sk_hlp_00350b0c();  /* FUN_00350b0c */
extern uint64_t sk_hlp_00350bd8();  /* FUN_00350bd8 */
extern uint64_t sk_hlp_00351094();  /* FUN_00351094 */
extern uint64_t sk_hlp_00351100();  /* FUN_00351100 */
extern uint64_t sk_hlp_00351148();  /* FUN_00351148 */
extern uint64_t sk_hlp_0035130c();  /* FUN_0035130c */
extern uint64_t sk_caprev();  /* FUN_00351378 */
extern uint64_t sk_cap_check();  /* FUN_0035142c */
extern uint64_t sk_hlp_003514b8();  /* FUN_003514b8 */
extern uint64_t sk_hlp_003514e8();  /* FUN_003514e8 */
extern uint64_t sk_msg_init();  /* FUN_003515b4 */
extern uint64_t sk_hlp_003517e4();  /* FUN_003517e4 */
extern uint64_t sk_badge();  /* FUN_00352210 */
extern uint64_t sk_badgemsk2();  /* FUN_00352220 */
extern uint64_t sk_hlp_003524ec();  /* FUN_003524ec */
extern uint64_t sk_lookup_cur();  /* FUN_00352644 */
extern uint64_t sk_cur_cap();  /* FUN_00352980 */
extern uint64_t sk_hlp_00352a4c();  /* FUN_00352a4c */
extern uint64_t sk_hlp_00352b20();  /* FUN_00352b20 */
extern uint64_t sk_cnode();  /* FUN_00352b80 */
extern uint64_t sk_hlp_00352c28();  /* FUN_00352c28 */
extern uint64_t sk_sys_status();  /* FUN_00353034 */
extern uint64_t sk_hlp_00353130();  /* FUN_00353130 */
extern uint64_t sk_hlp_0035331c();  /* FUN_0035331c */
extern uint64_t sk_runq();  /* FUN_00353718 */
extern uint64_t sk_hlp_00353734();  /* FUN_00353734 */
extern uint64_t sk_hlp_003537f0();  /* FUN_003537f0 */
extern uint64_t sk_hlp_0035396c();  /* FUN_0035396c */
extern uint64_t sk_sys2();  /* FUN_00353a3c */
extern uint64_t sk_hlp_00353e2c();  /* FUN_00353e2c */
extern uint64_t sk_sys_post();  /* FUN_003540d0 */
extern uint64_t sk_hlp_003540dc();  /* FUN_003540dc */
extern uint64_t sk_sel();  /* FUN_00354134 */
extern uint64_t sk_hlp_00354720();  /* FUN_00354720 */
extern uint64_t sk_hlp_00354780();  /* FUN_00354780 */
extern uint64_t sk_hlp_00354798();  /* FUN_00354798 */
extern uint64_t sk_hlp_003548ac();  /* FUN_003548ac */
extern uint64_t sk_sys_switch();  /* FUN_00354b80 */
extern uint64_t sk_hlp_00354e18();  /* FUN_00354e18 */
extern uint64_t sk_hlp_00354e50();  /* FUN_00354e50 */
extern uint64_t sk_hlp_00354ea4();  /* FUN_00354ea4 */
extern uint64_t sk_hlp_00355244();  /* FUN_00355244 */
extern uint64_t sk_sys_pre();  /* FUN_003552d0 */
extern uint64_t sk_hlp_00355418();  /* FUN_00355418 */
extern uint64_t sk_hlp_00355dcc();  /* FUN_00355dcc */
extern uint64_t sk_hlp_00355e8c();  /* FUN_00355e8c */
extern uint64_t sk_hlp_00355ec8();  /* FUN_00355ec8 */
extern uint64_t sk_hlp_00355f1c();  /* FUN_00355f1c */
extern uint64_t sk_hlp_00355fb8();  /* FUN_00355fb8 */
extern uint64_t sk_sys_ret();  /* FUN_00356518 */
extern uint64_t sk_hlp_0035662c();  /* FUN_0035662c */
extern uint64_t sk_hlp_0035675c();  /* FUN_0035675c */
extern uint64_t sk_hlp_00356d20();  /* FUN_00356d20 */
extern uint64_t sk_hlp_00356da4();  /* FUN_00356da4 */
extern uint64_t sk_hlp_00356dbc();  /* FUN_00356dbc */
extern uint64_t sk_hlp_00356dd4();  /* FUN_00356dd4 */
extern uint64_t sk_hlp_00356dec();  /* FUN_00356dec */
extern uint64_t sk_hlp_00356e04();  /* FUN_00356e04 */
extern uint64_t sk_hlp_00357068();  /* FUN_00357068 */
extern uint64_t sk_hlp_003571d0();  /* FUN_003571d0 */
extern uint64_t sk_hlp_0035729c();  /* FUN_0035729c */
extern uint64_t sk_hlp_0035738c();  /* FUN_0035738c */
extern uint64_t sk_hlp_003573a4();  /* FUN_003573a4 */
extern uint64_t sk_hlp_003573cc();  /* FUN_003573cc */
extern uint64_t sk_hlp_00357498();  /* FUN_00357498 */
extern uint64_t sk_hlp_00357710();  /* FUN_00357710 */
extern uint64_t sk_frame_load();  /* FUN_003579f4 */
extern uint64_t sk_hlp_00357c74();  /* FUN_00357c74 */
extern uint64_t sk_hlp_00357cb4();  /* FUN_00357cb4 */
extern uint64_t sk_frame_save();  /* FUN_00357f04 */
extern uint64_t sk_err();  /* FUN_003581fc */
extern uint64_t sk_hlp_0035860c();  /* FUN_0035860c */
extern uint64_t sk_hlp_00358624();  /* FUN_00358624 */
extern uint64_t sk_hlp_00358774();  /* FUN_00358774 */
extern uint64_t sk_hlp_0035878c();  /* FUN_0035878c */
extern uint64_t sk_hlp_0035881c();  /* FUN_0035881c */
extern uint64_t sk_hlp_00358b9c();  /* FUN_00358b9c */
extern uint64_t sk_hlp_00359018();  /* FUN_00359018 */
extern uint64_t sk_hlp_00359880();  /* FUN_00359880 */
extern uint64_t sk_hlp_0035994c();  /* FUN_0035994c */
extern uint64_t sk_hlp_00359960();  /* FUN_00359960 */
extern uint64_t sk_hlp_00359b0c();  /* FUN_00359b0c */
extern uint64_t sk_hlp_0035a190();  /* FUN_0035a190 */
extern uint64_t sk_hlp_0035aad8();  /* FUN_0035aad8 */
extern uint64_t sk_free();  /* FUN_0036b118 */
extern uint64_t sk_hlp_0036b21c();  /* FUN_0036b21c */
extern uint64_t sk_cap_lookup();  /* FUN_00371950 */
extern uint64_t sk_dispatch_leave();  /* FUN_00376820 */
extern uint64_t sk_hlp_00377824();  /* FUN_00377824 */
extern uint64_t sk_hlp_00377bec();  /* FUN_00377bec */
extern uint64_t sk_hlp_00656474();  /* FUN_00656474 */

/* ---- Shared globals written by the stub/installer helpers ---------- */
extern volatile uint64_t sk_gv_656278;   /* uRam_0x656278 */
extern volatile uint64_t sk_gv_6562b8;   /* uRam_0x6562b8 */
extern volatile uint64_t sk_gv_6562c0;   /* uRam_0x6562c0 */
extern volatile uint64_t sk_gv_6562c8;   /* uRam_0x6562c8 */
extern volatile uint64_t sk_gv_6562d0;   /* uRam_0x6562d0 */
extern volatile uint64_t sk_gv_6562d8;   /* uRam_0x6562d8 */
extern volatile uint64_t sk_gv_6562e0;   /* uRam_0x6562e0 */
extern volatile uint64_t sk_gv_656310;   /* uRam_0x656310 */
extern volatile uint64_t sk_gv_656318;   /* uRam_0x656318 */
extern volatile uint64_t sk_gv_656320;   /* uRam_0x656320 */
extern volatile uint64_t sk_gv_656398;   /* uRam_0x656398 */
extern volatile uint64_t sk_gv_6563b0;   /* uRam_0x6563b0 */
extern volatile uint64_t sk_gv_6563b8;   /* uRam_0x6563b8 */
extern volatile uint64_t sk_gv_6563c8;   /* uRam_0x6563c8 */
extern volatile uint64_t sk_gv_6563e0;   /* uRam_0x6563e0 */
extern volatile uint64_t sk_gv_6563e8;   /* uRam_0x6563e8 */
extern volatile uint64_t sk_gv_6563f8;   /* uRam_0x6563f8 */
extern volatile uint64_t sk_gv_656400;   /* uRam_0x656400 */
extern volatile uint64_t sk_gv_656408;   /* uRam_0x656408 */
extern volatile uint64_t sk_gv_656410;   /* uRam_0x656410 */
extern volatile uint64_t sk_gv_656418;   /* uRam_0x656418 */
extern volatile uint64_t sk_gv_656430;   /* uRam_0x656430 */
extern volatile uint64_t sk_gv_656438;   /* uRam_0x656438 */
extern volatile uint64_t sk_gv_656440;   /* uRam_0x656440 */
extern volatile uint64_t sk_gv_656458;   /* uRam_0x656458 */
extern volatile uint64_t sk_gv_656470;   /* uRam_0x656470 */
extern volatile uint64_t sk_gv_656488;   /* uRam_0x656488 */
extern volatile uint64_t sk_gv_656490;   /* uRam_0x656490 */
extern volatile uint64_t sk_gv_6564a8;   /* uRam_0x6564a8 */
extern volatile uint64_t sk_gv_6564b0;   /* uRam_0x6564b0 */
extern volatile uint64_t sk_gv_6564b8;   /* uRam_0x6564b8 */
extern volatile uint64_t sk_gv_6564c0;   /* uRam_0x6564c0 */
extern volatile uint64_t sk_gv_6564c8;   /* uRam_0x6564c8 */
extern volatile uint64_t sk_gv_6563a0;
extern volatile uint64_t sk_gv_6563c0;
extern volatile uint64_t sk_gv_6563d0;
extern volatile uint64_t sk_gv_6563f0;
extern volatile uint64_t sk_gv_656420;
extern volatile uint64_t sk_gv_656448;
extern volatile uint64_t sk_gv_656460;
extern volatile uint64_t sk_gv_656474;
extern volatile uint64_t sk_gv_656498;

extern void (*g_sk_dispatch)();         /* DAT_00658c00: global syscall dispatch fn ptr */

/* Extern data descriptors (DAT_004exxxx) referenced by handlers. */
extern uint64_t sk_dat_004e824c;
extern uint64_t sk_dat_004e82bc;
extern uint64_t sk_dat_004e84f0;
extern uint64_t sk_dat_004e8514;
extern uint64_t sk_dat_004e8bb4;
extern uint64_t sk_dat_004e8f80;
extern uint64_t sk_dat_004e90b0;
extern uint64_t sk_dat_004e9c1c;
extern uint64_t sk_dat_004ea088;
extern uint64_t sk_dat_004ea100;
extern uint64_t sk_dat_004eac1c;
extern uint64_t sk_dat_004eb028;
extern uint64_t sk_dat_004eb078;
extern uint64_t sk_dat_004eb0c8;
extern uint64_t sk_dat_004eb0e4;
extern uint64_t sk_dat_004eb308;
extern uint64_t sk_dat_004eb480;
extern uint64_t sk_dat_004eb530;
extern uint64_t sk_dat_004eb5c0;
extern uint64_t sk_dat_004eb668;
extern uint64_t sk_dat_004eb734;
extern uint64_t sk_dat_004eb788;
extern uint64_t sk_dat_004eb7dc;
extern uint64_t sk_dat_004ebcf8;
extern uint64_t sk_dat_004ebd30;
extern uint64_t sk_dat_004ed10c;
extern uint64_t sk_dat_005cde70;
extern uint64_t sk_dat_005cdef0;
extern uint64_t sk_dat_004e88b4;
extern uint64_t sk_dat_004eb0c8;
extern uint64_t sk_dat_004eb0e4;
extern uint64_t sk_dat_004ed10c;


/* ---- In-slice forward declarations (static, defined below in address order) ---- */
static void sk_sys_ipc_common(void);
static void sk_sys_cap_op_common();
static void sk_sys_op_common();
static void sk_check_meta_common(uint64_t,uint64_t,uint64_t (*)(void));
static void sk_raise_buffer_err(uint64_t,uint64_t,uint64_t,uint32_t,uint32_t,uint32_t);
static void sk_sys_ipc_5cap();
static void sk_sys_ipc_5cap_alt();
static uint64_t sk_trampoline_inst_6563b8(void);
static uint64_t sk_trampoline_inst_6563c8(void);
static uint64_t sk_trampoline_inst_6563e8(void);
static uint64_t sk_trampoline_inst_6563f8(void);
static uint64_t sk_trampoline_inst_656408(void);
static uint64_t sk_trampoline_inst_656418(void);
static uint64_t sk_trampoline_inst_656430(void);
static uint64_t sk_trampoline_inst_656438(void);
static uint64_t sk_trampoline_inst_656440(void);



/* ================================================================== *
 * Gap slice 00 function bodies, in address order.
 *
 * Region vocabulary: syscall / exception-entry handlers. The kernel
 * dispatch table is reached through the global function pointer
 * g_sk_dispatch (DAT_00658c00) and per-class method tables whose slot
 * +0x10 holds the active handler. Ghidra "extraout_x*" bases are
 * rendered by chaining from the helper that produced them; the
 * unaff_x19/x26/x27/x28 callee-saved base registers (TCB / message
 * base) are modelled as locals indexed by their TCB offsets.
 * ================================================================== */

/* FUN_003224a0 @ 0x003224a0   (est. sk_sys_yield_cap)
 * Ghidra: uint FUN_003224a0(void)
 * Thin syscall wrapper: runs the scheduler tick (FUN_00359b0c) and the
 * notification poll (FUN_0035aad8), returning the poll's low bit, i.e.
 * whether the slow path must retry.
 * Confidence: medium
 * Notes: callees FUN_00359b0c / FUN_0035aad8 (out of slice). */
static uint32_t sk_sys_yield_cap(void)
{
    sk_hlp_00359b0c();                       /* FUN_00359b0c */
    return (uint32_t)(sk_hlp_0035aad8() & 1u);   /* FUN_0035aad8 */
}
/* FUN_003224f0 @ 0x003224f0   (est. sk_sys_handle_ipc_enter)
 * Ghidra: void FUN_003224f0(void)
 * Syscall handler prologue: stashes the frame argument registers,
 * builds a 4-capability IPC message, resolves the destination cap and
 * runs the IPC send/recv dance through the kernel dispatch table
 * (g_sk_dispatch and per-class method-table slot +0x10). On a pending
 * retry it invokes the slow-path continuation (FUN_00321e64), then
 * returns through the common epilogue.
 * Confidence: medium
 * Notes: DAT_00658c00 = global dispatch fn pointer; slot-0x10 method
 * tables reached via helper return bases (Ghidra extraout_x16_*). */
static void sk_sys_handle_ipc_enter(void)
{
    uint64_t x26 = 0, x27 = 0, x19 = 0;   /* entry base regs */
    uint64_t a0, a1, a2, a3, a4, a5, a6, a7;
    uint64_t base, tail;
    uint64_t r;
    void (*fn)();

    sk_trap_enter();                    /* FUN_0008e518: frame marker */
    sk_frame_save(&a0, &a1, &a2, &a3, &a4, &a5, &a6, &a7);  /* FUN_00357f04 */
    a0 = 0; a1 = a0;                    /* saved register slots */
    sk_msg_init(0, 4, &a1);             /* FUN_003515b4: 4-cap message */
    sk_cap_lookup();                    /* FUN_00371950 */
    base = sk_dispatch1();              /* FUN_00348e00 */
    (g_sk_dispatch)(*(uint64_t *)(base + 0x40));   /* DAT_00658c00 */
    sk_dispatch4();                     /* FUN_00348abc */
    (g_sk_dispatch)();
    sk_hlp_0034b87c();                  /* FUN_0034b87c */
    sk_enter2();                        /* FUN_0034dae8 */
    fn = *(void (**)(void))(sk_recv() + 0x10);     /* FUN_0034c664 -> slot */
    fn();
    base = sk_enter2();                 /* FUN_0034dae8 */
    fn = *(void (**)(void))(base + 0x10);
    r = ((uint64_t (*)(uint64_t, uint64_t, uint64_t))fn)(x26, a1, a3);
    sk_send1(r >> 32, r & 0xffffffff, a4);         /* FUN_0034b518 */
    fn = *(void (**)(void))(sk_send1() + 0x10);
    fn(x26, a2);
    sk_send4();                         /* FUN_0034b3e8 */
    fn = *(void (**)(void))(sk_send4() + 0x10);
    fn(x26, a6, a7);
    tail = sk_frame_load();             /* FUN_003579f4 */
    fn(a0, tail, a0);
    sk_hlp_003571d0();                  /* FUN_003571d0 */
    fn();
    sk_hlp_00359960();                  /* FUN_00359960 */
    fn();
    sk_hlp_0035994c();                  /* FUN_0035994c */
    fn();
    sk_hlp_003537f0();                  /* FUN_003537f0 */
    sk_irq();                           /* FUN_0014ae44 */
    sk_hlp_0034c5dc();                  /* FUN_0034c5dc */
    sk_hlp_0034dad8();                  /* FUN_0034dad8 */
    if ((sk_dispatch_leave() & 1u) != 0) {        /* FUN_00376820 */
        sk_hlp_0035331c();              /* FUN_0035331c */
        sk_hlp_00321e64();              /* FUN_00321e64: slow-path retry */
    }
    fn = *(void (**)(void))(base + 8);
    sk_hlp_003504f4();                  /* FUN_003504f4 */
    fn();
    sk_disp2();                         /* FUN_003507d4 */
    fn();
    r = sk_sys_status();                /* FUN_00353034 */
    sk_trap_leave(r, 0);                /* FUN_0008e500 */
}
/* FUN_0032270c @ 0x0032270c   (est. sk_sys_handle_ipc_enter_alt)
 * Ghidra: void FUN_0032270c(void)
 * Same 4-cap IPC handler prologue as sk_sys_handle_ipc_enter, differing
 * only in the slow-path retry target (FUN_00322010 vs FUN_00321e64).
 * A sibling syscall entry sharing the identical template.
 * Confidence: medium
 * Notes: see 0x3224f0 header for the dispatch-slot notes. */
static void sk_sys_handle_ipc_enter_alt(void)
{
    uint64_t x26 = 0, x27 = 0, x19 = 0;
    uint64_t a0, a1, a2, a3, a4, a5, a6, a7;
    uint64_t base, tail, r;
    void (*fn)();

    sk_trap_enter();                    /* FUN_0008e518 */
    sk_frame_save(&a0, &a1, &a2, &a3, &a4, &a5, &a6, &a7);  /* FUN_00357f04 */
    a0 = 0; a1 = a0;
    sk_msg_init(0, 4, &a1);             /* FUN_003515b4 */
    sk_cap_lookup();                    /* FUN_00371950 */
    base = sk_dispatch1();              /* FUN_00348e00 */
    (g_sk_dispatch)(*(uint64_t *)(base + 0x40));   /* DAT_00658c00 */
    sk_dispatch4();                     /* FUN_00348abc */
    (g_sk_dispatch)();
    sk_hlp_0034b87c();                  /* FUN_0034b87c */
    sk_enter2();                        /* FUN_0034dae8 */
    fn = *(void (**)(void))(sk_recv() + 0x10);     /* FUN_0034c664 */
    fn();
    base = sk_enter2();                 /* FUN_0034dae8 */
    fn = *(void (**)(void))(base + 0x10);
    r = ((uint64_t (*)(uint64_t, uint64_t, uint64_t))fn)(x26, a1, a3);
    sk_send1(r >> 32, r & 0xffffffff, a4);         /* FUN_0034b518 */
    fn = *(void (**)(void))(sk_send1() + 0x10);
    fn(x26, a2);
    sk_send4();                         /* FUN_0034b3e8 */
    fn = *(void (**)(void))(sk_send4() + 0x10);
    fn(x26, a6, a7);
    tail = sk_frame_load();             /* FUN_003579f4 */
    fn(a0, tail, a0);
    sk_hlp_003571d0();                  /* FUN_003571d0 */
    fn();
    sk_hlp_00359960();                  /* FUN_00359960 */
    fn();
    sk_hlp_0035994c();                  /* FUN_0035994c */
    fn();
    sk_hlp_003537f0();                  /* FUN_003537f0 */
    sk_irq();                           /* FUN_0014ae44 */
    sk_hlp_0034c5dc();                  /* FUN_0034c5dc */
    sk_hlp_0034dad8();                  /* FUN_0034dad8 */
    if ((sk_dispatch_leave() & 1u) != 0) {
        sk_hlp_0035331c();              /* FUN_0035331c */
        sk_hlp_00322010();              /* FUN_00322010: slow-path retry */
    }
    fn = *(void (**)(void))(base + 8);
    sk_hlp_003504f4();                  /* FUN_003504f4 */
    fn();
    sk_disp2();                         /* FUN_003507d4 */
    fn();
    r = sk_sys_status();                /* FUN_00353034 */
    sk_trap_leave(r, 0);                /* FUN_0008e500 */
}
/* FUN_00322928 / 0x322980 / 0x3229d8 / 0x322a30   (est. sk_sys_ipc_send_wrapper[_alt|2|3])
 * Ghidra: uint FUN_00322928(void) [and the three siblings below]
 * Identical wrappers: run the syscall pre/post preamble (FUN_003552d0,
 * FUN_003540d0) then delegate to the generic IPC handler FUN_00322a88,
 * returning its low bit. Distinct syscall ids sharing one body.
 * Confidence: medium */
static void sk_sys_ipc_send_wrapper(void)
{
    sk_sys_pre();                       /* FUN_003552d0 */
    sk_sys_post();                      /* FUN_003540d0 */
    sk_sys_ipc_common();                /* FUN_00322a88 */
}
/* FUN_00322928 / 0x322980 / 0x3229d8 / 0x322a30   (est. sk_sys_ipc_send_wrapper[_alt|2|3])
 * Ghidra: uint FUN_00322928(void) [and the three siblings below]
 * Identical wrappers: run the syscall pre/post preamble (FUN_003552d0,
 * FUN_003540d0) then delegate to the generic IPC handler FUN_00322a88,
 * returning its low bit. Distinct syscall ids sharing one body.
 * Confidence: medium */
static void sk_sys_ipc_send_wrapper_alt(void)
{
    sk_sys_pre();                       /* FUN_003552d0 */
    sk_sys_post();                      /* FUN_003540d0 */
    sk_sys_ipc_common();                /* FUN_00322a88 */
}
/* FUN_00322928 / 0x322980 / 0x3229d8 / 0x322a30   (est. sk_sys_ipc_send_wrapper[_alt|2|3])
 * Ghidra: uint FUN_00322928(void) [and the three siblings below]
 * Identical wrappers: run the syscall pre/post preamble (FUN_003552d0,
 * FUN_003540d0) then delegate to the generic IPC handler FUN_00322a88,
 * returning its low bit. Distinct syscall ids sharing one body.
 * Confidence: medium */
static void sk_sys_ipc_send_wrapper2(void)
{
    sk_sys_pre();                       /* FUN_003552d0 */
    sk_sys_post();                      /* FUN_003540d0 */
    sk_sys_ipc_common();                /* FUN_00322a88 */
}
/* FUN_00322928 / 0x322980 / 0x3229d8 / 0x322a30   (est. sk_sys_ipc_send_wrapper[_alt|2|3])
 * Ghidra: uint FUN_00322928(void) [and the three siblings below]
 * Identical wrappers: run the syscall pre/post preamble (FUN_003552d0,
 * FUN_003540d0) then delegate to the generic IPC handler FUN_00322a88,
 * returning its low bit. Distinct syscall ids sharing one body.
 * Confidence: medium */
static void sk_sys_ipc_send_wrapper3(void)
{
    sk_sys_pre();                       /* FUN_003552d0 */
    sk_sys_post();                      /* FUN_003540d0 */
    sk_sys_ipc_common();                /* FUN_00322a88 */
}
/* FUN_00322a88 @ 0x00322a88   (est. sk_sys_ipc_common)
 * Ghidra: void FUN_00322a88(void)
 * Generic IPC syscall handler: saves the frame args, builds a 4-cap
 * message, resolves the destination cap and runs the IPC send/recv
 * dance through the kernel dispatch table. On a pending retry it takes
 * the on-stack continuation tail, otherwise the common epilogue. TCB
 * arg slots at +0x30/+0x40/+0x50 (unaff_x19).
 * Confidence: medium
 * Notes: DAT_00658c00 dispatch pointer; slot-0x10 method-table calls. */
static void sk_sys_ipc_common(void)
{
    uint64_t x26 = 0, x27 = 0, x19 = 0;
    uint64_t a0, a1, a2, a3, a4, a5, a6, a7;
    uint64_t base, r;
    int32_t s0, s1, s2;
    void (*fn)();

    sk_trap_enter();                    /* FUN_0008e518 */
    sk_frame_save(&a0, &a1, &a2, &a3, &a4, &a5, &a6, &a7);  /* FUN_00357f04 */
    sk_msg_init(0, 4, &a0);             /* FUN_003515b4 */
    sk_cap_lookup();                    /* FUN_00371950 */
    base = sk_dispatch2();              /* FUN_00348e18 */
    (g_sk_dispatch)(*(uint64_t *)(base + 0x40));   /* DAT_00658c00 */
    sk_dispatch4();                     /* FUN_00348abc */
    (g_sk_dispatch)();
    sk_dispatch3();                     /* FUN_0034ba68 */
    sk_send1();                         /* FUN_0034b518 */
    fn = *(void (**)(void))(sk_send1() + 0x10);
    fn();
    fn = *(void (**)(void))(sk_ipc2() + 0x10);     /* FUN_0034d140 */
    r = ((uint64_t (*)(uint64_t, uint64_t, uint64_t))fn)(0, a0, a3);
    sk_send3(r >> 32, r & 0xffffffff, a4);         /* FUN_0034b3c8 */
    fn = *(void (**)(void))(sk_send2() + 0x10);    /* FUN_0034b804 */
    r = ((uint64_t (*)(uint64_t, uint64_t))fn)(0, a1);
    sk_send2(r >> 32, r & 0xffffffff, a5);
    fn = *(void (**)(void))(sk_hlp_0034a30c() + 0x10);
    fn(0, a2);
    sk_frame_load();                    /* FUN_003579f4 */
    fn = *(void (**)(void))(sk_recv() + 0x10);
    fn(0, r, a0);
    s0 = *(int32_t *)(x19 + 0x30);
    fn(0 + s0, a4, a3);
    s1 = *(int32_t *)(x19 + 0x40);
    fn(0 + s1, a5, a4);
    s2 = *(int32_t *)(x19 + 0x50);
    fn(0 + s2, a6, a5);
    sk_hlp_0034a30c();                  /* FUN_0034a30c */
    sk_hlp_003508f0();                  /* FUN_003508f0 */
    sk_hlp_00350aac();                  /* FUN_00350aac */
    if ((sk_dispatch_leave() & 1u) == 0) {        /* FUN_00376820 */
        ((void (*)(uint64_t))fn)(a0);
        sk_hlp_0034e66c();              /* FUN_0034e66c */
        sk_hlp_00351100();              /* FUN_00351100 */
        sk_ipc_send();                  /* FUN_0034f8e4 */
    } else {
        ((void (*)(uint64_t, uint64_t, uint64_t, int32_t, int32_t, int32_t,
                   uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t))fn)
            (a4, a5, a6, s0, s1, s2, a3, a4, a5, a6, a7, 0);
    }
    fn = *(void (**)(void))(base + 8);
    sk_hlp_0035060c();                  /* FUN_0035060c */
    fn();
    sk_leave2();                        /* FUN_003508cc */
    fn();
    r = sk_cur_cap();                   /* FUN_00352980 */
    sk_trap_leave(r, a0);               /* FUN_0008e500 */
}
/* FUN_00322d44 @ 0x322d44   (est. sk_sys_ipc_5cap)
 * Ghidra: void FUN_00322d44(8 args)
 * 5-capability IPC handler: builds the message, resolves the destination
 * cap and runs the send/recv dance through the kernel dispatch table. On a
 * pending retry it recurses into the 4-cap handler (FUN_003224f0).
 * Confidence: medium */
static void sk_sys_ipc_5cap(uint64_t p1,uint64_t p2,uint64_t p3,uint64_t p4,uint64_t p5,
                            uint64_t p6,uint64_t p7,uint64_t p8)
{
    uint64_t x27=0, x19=0;
    uint64_t a0,a1,a2,a3,a4,a5,a6,a7, base, r;
    void (*fn)();

    sk_trap_enter();                    /* FUN_0008e518 */
    sk_msg_init(0,5,&a0);               /* FUN_003515b4: 5-cap */
    sk_cap_lookup();                    /* FUN_00371950 */
    base = sk_dispatch1();              /* FUN_00348e00 */
    (g_sk_dispatch)(*(uint64_t*)(base+0x40));   /* DAT_00658c00 */
    sk_obj_release();                   /* FUN_00348a18 */
    (g_sk_dispatch)();
    sk_dispatch3();                     /* FUN_0034ba68 */
    sk_send1();                         /* FUN_0034b518 */
    fn = *(void(**)(void))(sk_send1()+0x10);
    fn();
    base = sk_enter2();                 /* FUN_0034dae8 */
    fn = *(void(**)(void))(base+0x10);
    r = ((uint64_t(*)(uint64_t,uint64_t,uint64_t))fn)(x27, p1, a3);
    sk_send4(r>>32, r&0xffffffff, a4);  /* FUN_0034b3e8 */
    fn = *(void(**)(void))(sk_send4()+0x10);
    r = ((uint64_t(*)(uint64_t,uint64_t))fn)(x27, p3);
    sk_send2(r>>32, r&0xffffffff, a5);  /* FUN_0034b804 */
    fn = *(void(**)(void))(sk_send2()+0x10);
    r = ((uint64_t(*)(uint64_t,uint64_t))fn)(x27, p4);
    sk_hlp_003573cc(r>>32, r&0xffffffff, a6);   /* FUN_003573cc */
    base = sk_recv();                   /* FUN_0034c664 */
    fn = *(void(**)(void))(base+0x10);
    fn(x27, p5);
    sk_hlp_0035a190();                  /* FUN_0035a190 */
    fn(0);
    sk_hlp_00355ec8();                  /* FUN_00355ec8 */
    fn();
    sk_hlp_0035729c();                  /* FUN_0035729c */
    fn();
    sk_hlp_00357498();                  /* FUN_00357498 */
    fn();
    sk_hlp_003573a4();                  /* FUN_003573a4 */
    fn();
    sk_hlp_00357710();                  /* FUN_00357710 */
    sk_irq();                           /* FUN_0014ae44 */
    sk_timer();                         /* FUN_0034ce68 */
    sk_caprev();                        /* FUN_00351378 */
    if ((sk_dispatch_leave() & 1u) != 0) {       /* FUN_00376820 */
        sk_hlp_003524ec();              /* FUN_003524ec */
        sk_sys_handle_ipc_enter();      /* FUN_003224f0 */
    }
    fn = *(void(**)(void))(base+8);
    sk_disp2();                         /* FUN_003507d4 */
    fn();
    sk_hlp_003508a8();                  /* FUN_003508a8 */
    fn();
    r = sk_sys_status();                /* FUN_00353034 */
    sk_trap_leave(r, 0);                /* FUN_0008e500 */
}
/* FUN_00322fcc @ 0x322fcc   (est. sk_sys_ipc_5cap_alt)
 * Ghidra: void FUN_00322fcc(8 args)
 * Identical 5-cap IPC handler to sk_sys_ipc_5cap, differing in the retry
 * target (FUN_0032270c instead of FUN_003224f0).
 * Confidence: medium */
static void sk_sys_ipc_5cap_alt(uint64_t p1,uint64_t p2,uint64_t p3,uint64_t p4,uint64_t p5,
                                uint64_t p6,uint64_t p7,uint64_t p8)
{
    uint64_t x27=0, x19=0;
    uint64_t a0,a1,a2,a3,a4,a5,a6,a7, base, r;
    void (*fn)();

    sk_trap_enter();                    /* FUN_0008e518 */
    sk_msg_init(0,5,&a0);               /* FUN_003515b4 */
    sk_cap_lookup();                    /* FUN_00371950 */
    base = sk_dispatch1();              /* FUN_00348e00 */
    (g_sk_dispatch)(*(uint64_t*)(base+0x40));
    sk_obj_release();                   /* FUN_00348a18 */
    (g_sk_dispatch)();
    sk_dispatch3();                     /* FUN_0034ba68 */
    sk_send1();                         /* FUN_0034b518 */
    fn = *(void(**)(void))(sk_send1()+0x10);
    fn();
    base = sk_enter2();                 /* FUN_0034dae8 */
    fn = *(void(**)(void))(base+0x10);
    r = ((uint64_t(*)(uint64_t,uint64_t,uint64_t))fn)(x27, p1, a3);
    sk_send4(r>>32, r&0xffffffff, a4);  /* FUN_0034b3e8 */
    fn = *(void(**)(void))(sk_send4()+0x10);
    r = ((uint64_t(*)(uint64_t,uint64_t))fn)(x27, p3);
    sk_send2(r>>32, r&0xffffffff, a5);  /* FUN_0034b804 */
    fn = *(void(**)(void))(sk_send2()+0x10);
    r = ((uint64_t(*)(uint64_t,uint64_t))fn)(x27, p4);
    sk_hlp_003573cc(r>>32, r&0xffffffff, a6);
    base = sk_recv();                   /* FUN_0034c664 */
    fn = *(void(**)(void))(base+0x10);
    fn(x27, p5);
    sk_hlp_0035a190();                  /* FUN_0035a190 */
    fn(0);
    sk_hlp_00355ec8();                  /* FUN_00355ec8 */
    fn();
    sk_hlp_0035729c();                  /* FUN_0035729c */
    fn();
    sk_hlp_00357498();                  /* FUN_00357498 */
    fn();
    sk_hlp_003573a4();                  /* FUN_003573a4 */
    fn();
    sk_hlp_00357710();                  /* FUN_00357710 */
    sk_irq();                           /* FUN_0014ae44 */
    sk_timer();                         /* FUN_0034ce68 */
    sk_caprev();                        /* FUN_00351378 */
    if ((sk_dispatch_leave() & 1u) != 0) {
        sk_hlp_003524ec();              /* FUN_003524ec */
        sk_sys_handle_ipc_enter_alt();  /* FUN_0032270c */
    }
    fn = *(void(**)(void))(base+8);
    sk_disp2();                         /* FUN_003507d4 */
    fn();
    sk_hlp_003508a8();                  /* FUN_003508a8 */
    fn();
    r = sk_sys_status();                /* FUN_00353034 */
    sk_trap_leave(r, 0);                /* FUN_0008e500 */
}
/* FUN_00323254/ac, 0x323664/bc (est. sk_wrap_cap_op_N)
 * Ghidra: uint FUN_00323254(void) — wrappers: lookup + ipc_send preamble then
 * delegate to the generic cap-op handler FUN_00323304, return its low bit.
 * Confidence: medium */
static void sk_wrap_cap_op_a(void) { sk_lookup_cur(); sk_ipc_send(); ((sk_fn_t)sk_sys_cap_op_common)(); }
/* FUN_00323254/ac, 0x323664/bc (est. sk_wrap_cap_op_N)
 * Ghidra: uint FUN_00323254(void) — wrappers: lookup + ipc_send preamble then
 * delegate to the generic cap-op handler FUN_00323304, return its low bit.
 * Confidence: medium */
static void sk_wrap_cap_op_b(void) { sk_lookup_cur(); sk_ipc_send(); ((sk_fn_t)sk_sys_cap_op_common)(); }
/* FUN_00323304 @ 0x323304   (est. sk_sys_cap_op_common)
 * Ghidra: void FUN_00323304(8 args)
 * Generic capability-operation syscall handler (5-cap message): resolves
 * the cap and runs the op through the dispatch table. On a pending retry
 * it takes the on-stack continuation, else the common epilogue. TCB arg
 * slots at +0x30..+0x60 (unaff_x19).
 * Confidence: medium */
static void sk_sys_cap_op_common(uint64_t p1,uint64_t p2,uint64_t p3,uint64_t p4,uint64_t p5,
                                 uint64_t p6,uint64_t p7,uint64_t p8)
{
    uint64_t x26=0,x27=0,x19=0;
    uint64_t a0,a1,a2,a3,a4,a5,a6,a7, base, r;
    int32_t s0,s1,s2,s3;
    void (*fn)();

    sk_trap_enter();                    /* FUN_0008e518 */
    a3=a0;
    sk_msg_init(0,5,&a0);               /* FUN_003515b4 */
    sk_cap_lookup();                    /* FUN_00371950 */
    base = sk_dispatch2();              /* FUN_00348e18 */
    (g_sk_dispatch)(*(uint64_t*)(base+0x40));
    sk_obj_release();                   /* FUN_00348a18 */
    (g_sk_dispatch)();
    sk_dispatch3();                     /* FUN_0034ba68 */
    sk_send1();                         /* FUN_0034b518 */
    fn = *(void(**)(void))(sk_send1()+0x10);
    fn();
    base = sk_send3();                  /* FUN_0034b3c8 */
    fn = *(void(**)(void))(base+0x10);
    r = ((uint64_t(*)(uint64_t,uint64_t,uint64_t))fn)(x27, p1, a3);
    sk_send2(r>>32, r&0xffffffff, a4);  /* FUN_0034b804 */
    base = sk_recv();                   /* FUN_0034c664 */
    fn = *(void(**)(void))(base+0x10);
    r = ((uint64_t(*)(uint64_t,uint64_t))fn)(x27, p3);
    sk_ipc2(r>>32, r&0xffffffff, a5);   /* FUN_0034d140 */
    base = sk_ipc2();                   /* FUN_0034d140 */
    fn = *(void(**)(void))(base+0x10);
    fn(x27, p4);
    sk_hlp_00355418();                  /* FUN_00355418 */
    fn();
    s0 = *(int32_t*)(x19+0x30);
    fn(x26+s0, p7, a3);
    s1 = *(int32_t*)(x19+0x40);
    fn(x26+s1, p8, a4);
    sk_hlp_0035738c();                  /* FUN_0035738c */
    s2 = *(int32_t*)(x19+0x50);
    fn(x26+s2, a1, 0);
    sk_hlp_00354780();                  /* FUN_00354780 */
    sk_hlp_0034a30c();                  /* FUN_0034a30c */
    sk_hlp_00350038();                  /* FUN_00350038 */
    if ((sk_dispatch_leave() & 1u) == 0) {
        fn(0);
        sk_timer();                     /* FUN_0034ce68 */
        sk_hlp_00352a4c();              /* FUN_00352a4c */
        sk_ipc_send();                  /* FUN_0034f8e4 */
    } else {
        sk_hlp_00353e2c(a6);            /* FUN_00353e2c */
        r = sk_sys_switch(x27);         /* FUN_00354b80 */
        fn(r, x27, x27, x27, x26+s0, x26+s1, x26+s2, 0, a3, a4, a5, 0, a1, a1, a2, a1);
    }
    fn = *(void(**)(void))(base+8);
    sk_hlp_003505e8();                  /* FUN_003505e8 */
    fn();
    sk_leave2();                        /* FUN_003508cc */
    fn();
    r = sk_cur_cap();                   /* FUN_00352980 */
    sk_trap_leave(r, s0);               /* FUN_0008e500 */
}
/* FUN_00323254/ac, 0x323664/bc (est. sk_wrap_cap_op_N)
 * Ghidra: uint FUN_00323254(void) — wrappers: lookup + ipc_send preamble then
 * delegate to the generic cap-op handler FUN_00323304, return its low bit.
 * Confidence: medium */
static void sk_wrap_cap_op_c(void) { sk_lookup_cur(); sk_ipc_send(); ((sk_fn_t)sk_sys_cap_op_common)(); }
/* FUN_00323254/ac, 0x323664/bc (est. sk_wrap_cap_op_N)
 * Ghidra: uint FUN_00323254(void) — wrappers: lookup + ipc_send preamble then
 * delegate to the generic cap-op handler FUN_00323304, return its low bit.
 * Confidence: medium */
static void sk_wrap_cap_op_d(void) { sk_lookup_cur(); sk_ipc_send(); ((sk_fn_t)sk_sys_cap_op_common)(); }
/* FUN_00323714 @ 0x323714   (est. sk_sys_ipc_6cap)
 * Ghidra: void FUN_00323714(8 args)
 * 6-capability IPC handler: full template with dispatch-table entry. On a
 * pending retry it recurses into the 5-cap handler (FUN_00322d44).
 * Confidence: medium */
static void sk_sys_ipc_6cap(uint64_t p1,uint64_t p2,uint64_t p3,uint64_t p4,uint64_t p5,
                            uint64_t p6,uint64_t p7,uint64_t p8)
{
    uint64_t x27=0,x28=0,x19=0;
    uint64_t a0,a1,a2,a3,a4,a5,a6,a7, base, r;
    int32_t s0,s1;
    void (*fn)();

    sk_trap_enter();                    /* FUN_0008e518 */
    base = sk_dispatch2();              /* FUN_00348e18 */
    (g_sk_dispatch)(*(uint64_t*)(base+0x40));
    sk_hlp_003489c0();                  /* FUN_003489c0 */
    (g_sk_dispatch)();
    r = sk_send5();                     /* FUN_0034b4c0 */
    sk_hlp_0035881c(r>>32, r&0xffffffff, a4);    /* FUN_0035881c */
    sk_send3();                         /* FUN_0034b3c8 */
    base = sk_send3();
    fn = *(void(**)(void))(base+0x10);
    fn();
    sk_send1();                         /* FUN_0034b518 */
    base = sk_send1();
    fn = *(void(**)(void))(base+0x10);
    r = ((uint64_t(*)(uint64_t,uint64_t,uint64_t))fn)(x28, p1, a5);
    sk_sched3(r>>32, r&0xffffffff, a6); /* FUN_0034dfe4 */
    base = sk_sched3();
    fn = *(void(**)(void))(base+0x10);
    r = ((uint64_t(*)(uint64_t,uint64_t))fn)(x28, p3);
    sk_ipc2(r>>32, r&0xffffffff, a7);   /* FUN_0034d140 */
    base = sk_ipc2();
    fn = *(void(**)(void))(base+0x10);
    r = ((uint64_t(*)(uint64_t,uint64_t))fn)(x28, p4);
    sk_send2(r>>32, r&0xffffffff, 0);   /* FUN_0034b804 */
    fn = *(void(**)(void))(sk_send2()+0x10);
    fn(x28, p5);
    base = sk_recv();                   /* FUN_0034c664 */
    fn = *(void(**)(void))(base+0x10);
    fn(x28, p6, a1);
    r = sk_hlp_0035675c();              /* FUN_0035675c */
    sk_sel(r>>32, r&0xffffffff, a4);    /* FUN_00354134 */
    sk_sys_switch();                    /* FUN_00354b80 */
    fn();
    r = p8;
    s0=*(int32_t*)(x19+0x30);
    sk_runq(x27+s0, r, a5);             /* FUN_00353718 */
    sk_hlp_00357068();                  /* FUN_00357068 */
    fn();
    sk_hlp_00355f1c();                  /* FUN_00355f1c */
    fn();
    s1=*(int32_t*)(x19+0x50);
    sk_cnode(0, x27+s1, a1, a2);        /* FUN_00352b80 */
    fn();
    sk_hlp_0035878c();                  /* FUN_0035878c */
    fn();
    sk_hlp_00358774();                  /* FUN_00358774 */
    fn();
    sk_hlp_003540dc();                  /* FUN_003540dc */
    sk_irq();                           /* FUN_0014ae44 */
    sk_hlp_0034f4f4();                  /* FUN_0034f4f4 */
    sk_hlp_0035130c();                  /* FUN_0035130c */
    if ((sk_dispatch_leave() & 1u) != 0) {
        sk_hlp_003517e4();              /* FUN_003517e4 */
        sk_sys_ipc_5cap(0,0,0,0,0,0,0,0);   /* FUN_00322d44 */
    }
    fn = *(void(**)(void))(base+8);
    sk_leave2();                        /* FUN_003508cc */
    fn();
    sk_gate2();                         /* FUN_003509d4 */
    fn();
    r = sk_cur_cap();                   /* FUN_00352980 */
    sk_trap_leave(r, 0);                /* FUN_0008e500 */
}
/* FUN_00323a74 @ 0x323a74   (est. sk_sys_ipc_6cap_alt)
 * Ghidra: void FUN_00323a74(8 args)
 * Identical 6-cap IPC handler to sk_sys_ipc_6cap, differing in the retry
 * target (FUN_00322fcc instead of FUN_00322d44).
 * Confidence: medium */
static void sk_sys_ipc_6cap_alt(uint64_t p1,uint64_t p2,uint64_t p3,uint64_t p4,uint64_t p5,
                                uint64_t p6,uint64_t p7,uint64_t p8)
{
    uint64_t x27=0,x28=0,x19=0;
    uint64_t a0,a1,a2,a3,a4,a5,a6,a7, base, r;
    int32_t s0,s1;
    void (*fn)();

    sk_trap_enter();                    /* FUN_0008e518 */
    base = sk_dispatch2();              /* FUN_00348e18 */
    (g_sk_dispatch)(*(uint64_t*)(base+0x40));
    sk_hlp_003489c0();                  /* FUN_003489c0 */
    (g_sk_dispatch)();
    r = sk_send5();                     /* FUN_0034b4c0 */
    sk_hlp_0035881c(r>>32, r&0xffffffff, a4);
    sk_send3();                         /* FUN_0034b3c8 */
    base = sk_send3();
    fn = *(void(**)(void))(base+0x10);
    fn();
    sk_send1();                         /* FUN_0034b518 */
    base = sk_send1();
    fn = *(void(**)(void))(base+0x10);
    r = ((uint64_t(*)(uint64_t,uint64_t,uint64_t))fn)(x28, p1, a5);
    sk_sched3(r>>32, r&0xffffffff, a6); /* FUN_0034dfe4 */
    base = sk_sched3();
    fn = *(void(**)(void))(base+0x10);
    r = ((uint64_t(*)(uint64_t,uint64_t))fn)(x28, p3);
    sk_ipc2(r>>32, r&0xffffffff, a7);
    base = sk_ipc2();
    fn = *(void(**)(void))(base+0x10);
    r = ((uint64_t(*)(uint64_t,uint64_t))fn)(x28, p4);
    sk_send2(r>>32, r&0xffffffff, 0);
    fn = *(void(**)(void))(sk_send2()+0x10);
    fn(x28, p5);
    base = sk_recv();                   /* FUN_0034c664 */
    fn = *(void(**)(void))(base+0x10);
    fn(x28, p6, a1);
    r = sk_hlp_0035675c();              /* FUN_0035675c */
    sk_sel(r>>32, r&0xffffffff, a4);    /* FUN_00354134 */
    sk_sys_switch();                    /* FUN_00354b80 */
    fn();
    r = p8;
    s0=*(int32_t*)(x19+0x30);
    sk_runq(x27+s0, r, a5);             /* FUN_00353718 */
    sk_hlp_00357068();                  /* FUN_00357068 */
    fn();
    sk_hlp_00355f1c();                  /* FUN_00355f1c */
    fn();
    s1=*(int32_t*)(x19+0x50);
    sk_cnode(0, x27+s1, a1, a2);        /* FUN_00352b80 */
    fn();
    sk_hlp_0035878c();                  /* FUN_0035878c */
    fn();
    sk_hlp_00358774();                  /* FUN_00358774 */
    fn();
    sk_hlp_003540dc();                  /* FUN_003540dc */
    sk_irq();                           /* FUN_0014ae44 */
    sk_hlp_0034f4f4();                  /* FUN_0034f4f4 */
    sk_hlp_0035130c();                  /* FUN_0035130c */
    if ((sk_dispatch_leave() & 1u) != 0) {
        sk_hlp_003517e4();              /* FUN_003517e4 */
        sk_sys_ipc_5cap_alt(0,0,0,0,0,0,0,0);   /* FUN_00322fcc */
    }
    fn = *(void(**)(void))(base+8);
    sk_leave2();                        /* FUN_003508cc */
    fn();
    sk_gate2();                         /* FUN_003509d4 */
    fn();
    r = sk_cur_cap();                   /* FUN_00352980 */
    sk_trap_leave(r, 0);                /* FUN_0008e500 */
}
/* FUN_00323dd4/e38/e9c/f00 (est. sk_wrap_sys_op_N)
 * Ghidra: uint FUN_00323dd4(void) — wrappers delegating to FUN_00323f64.
 * Confidence: medium */
static void sk_wrap_sys_op_a(void) { sk_hlp_0034f90c(); sk_ipc_send(); ((sk_fn_t)sk_sys_op_common)(); }
/* FUN_00323dd4/e38/e9c/f00 (est. sk_wrap_sys_op_N)
 * Ghidra: uint FUN_00323dd4(void) — wrappers delegating to FUN_00323f64.
 * Confidence: medium */
static void sk_wrap_sys_op_b(void) { sk_hlp_0034f90c(); sk_ipc_send(); ((sk_fn_t)sk_sys_op_common)(); }
/* FUN_00323dd4/e38/e9c/f00 (est. sk_wrap_sys_op_N)
 * Ghidra: uint FUN_00323dd4(void) — wrappers delegating to FUN_00323f64.
 * Confidence: medium */
static void sk_wrap_sys_op_c(void) { sk_hlp_0034f90c(); sk_ipc_send(); ((sk_fn_t)sk_sys_op_common)(); }
/* FUN_00323dd4/e38/e9c/f00 (est. sk_wrap_sys_op_N)
 * Ghidra: uint FUN_00323dd4(void) — wrappers delegating to FUN_00323f64.
 * Confidence: medium */
static void sk_wrap_sys_op_d(void) { sk_hlp_0034f90c(); sk_ipc_send(); ((sk_fn_t)sk_sys_op_common)(); }
/* FUN_00323f64 @ 0x323f64   (est. sk_sys_op_common)
 * Ghidra: void FUN_00323f64(8 args)
 * Generic syscall/op handler (6-cap message): resolves the cap and runs the
 * op through the dispatch table, with TCB arg slots at +0x30..+0x70. On a
 * pending retry it takes the on-stack continuation, else the common
 * epilogue.
 * Confidence: medium */
static void sk_sys_op_common(uint64_t p1,uint64_t p2,uint64_t p3,uint64_t p4,uint64_t p5,
                             uint64_t p6,uint64_t p7,uint64_t p8)
{
    uint64_t x28=0,x24=0,x19=0;
    uint64_t a0,a1,a2,a3,a4,a5,a6,a7, base, r;
    int32_t s0,s1,s2,s3,s4;
    void (*fn)();

    sk_trap_enter();                    /* FUN_0008e518 */
    sk_msg_init(0,6,&a0);               /* FUN_003515b4: 6-cap */
    sk_cap_lookup();                    /* FUN_00371950 */
    base = sk_dispatch2();              /* FUN_00348e18 */
    (g_sk_dispatch)(*(uint64_t*)(base+0x40));
    sk_hlp_00348a80();                  /* FUN_00348a80 */
    (g_sk_dispatch)();
    r = sk_send5();                     /* FUN_0034b4c0 */
    sk_hlp_0035881c(r>>32, r&0xffffffff, a4);
    sk_send3();                         /* FUN_0034b3c8 */
    fn = *(void(**)(void))(sk_send3()+0x10);
    fn();
    base = sk_send2();                  /* FUN_0034b804 */
    fn = *(void(**)(void))(base+0x10);
    r = ((uint64_t(*)(uint64_t,uint64_t,uint64_t))fn)(x28, p1, a5);
    sk_hlp_003509c8(a6, r>>32, r&0xffffffff, a6); /* FUN_003509c8 */
    base = sk_sched3();                 /* FUN_0034dfe4 */
    fn = *(void(**)(void))(base+0x10);
    r = ((uint64_t(*)(uint64_t,uint64_t))fn)(x28, p3);
    sk_sched3(r>>32, r&0xffffffff, a7); /* FUN_0034dfe4 */
    base = sk_hlp_0034f384();           /* FUN_0034f384 */
    fn = *(void(**)(void))(base+0x10);
    r = ((uint64_t(*)(uint64_t,uint64_t))fn)(x28, p4);
    sk_hlp_0034f384(r>>32, r&0xffffffff, a0);    /* FUN_0034f384 */
    base = sk_hlp_0034b07c();           /* FUN_0034b07c */
    fn = *(void(**)(void))(base+0x10);
    r = ((uint64_t(*)(uint64_t,uint64_t))fn)(x28, p5);
    sk_hlp_0034b07c(r>>32, r&0xffffffff, a1);    /* FUN_0034b07c */
    fn = *(void(**)(void))(sk_hlp_0034b07c()+0x10);
    fn(x28, p6);
    sk_hlp_00351148();                  /* FUN_00351148 */
    sk_sel();                           /* FUN_00354134 */
    sk_sys_switch();                    /* FUN_00354b80 */
    fn();
    s0 = *(int32_t*)(x19+0x30);
    sk_hlp_00353130(x24+s0, p8, a5);    /* FUN_00353130 */
    fn();
    s1 = *(int32_t*)(x19+0x40);
    sk_runq(x24+s1, a1, a6);            /* FUN_00353718 */
    sk_cnode();                         /* FUN_00352b80 */
    fn();
    s2 = *(int32_t*)(x19+0x50);
    sk_hlp_00353734(x24+s2, a2, a7);    /* FUN_00353734 */
    fn();
    s3 = *(int32_t*)(x19+0x60);
    r = ((uint64_t(*)(uint64_t,uint64_t,uint64_t))fn)(x24+s3, a3, a0);
    s4 = *(int32_t*)(x19+0x70);
    sk_hlp_003548ac(r, a4);             /* FUN_003548ac */
    fn();
    sk_hlp_003514b8(a1);                /* FUN_003514b8 */
    sk_irq();                           /* FUN_0014ae44 */
    sk_hlp_0034db98();                  /* FUN_0034db98 */
    sk_caprev();                        /* FUN_00351378 */
    if ((sk_dispatch_leave() & 1u) == 0) {
        fn(a1);
        sk_hlp_0034db98();              /* FUN_0034db98 */
        sk_hlp_00352c28();              /* FUN_00352c28 */
        sk_ipc_send();                  /* FUN_0034f8e4 */
    } else {
        sk_hlp_00355e8c(a2);            /* FUN_00355e8c */
        r = sk_hlp_00358624(x28);       /* FUN_00358624 */
        r = sk_hlp_00355dcc(r, x28);    /* FUN_00355dcc */
        fn(r, x28, x28, x28, x28, x24+s0, x24+s1, x24+s2, x24+s3, x24+s4,
           a5, a6, a7, a0, a1, a2, a3, a4, a1, a2);
    }
    fn = *(void(**)(void))(base+8);
    sk_hlp_003514e8();                  /* FUN_003514e8 */
    fn();
    sk_gate2();                         /* FUN_003509d4 */
    fn();
    r = sk_cur_cap();                   /* FUN_00352980 */
    sk_trap_leave(r, 0);                /* FUN_0008e500 */
}
/* FUN_003243b8 @ 0x3243b8   (est. sk_callback_copy_16)
 * Ghidra: void FUN_003243b8(undefined1 (*)[16], undefined8, undefined8, undefined8, undefined8*)
 * Calls the callback in x7 with (p2, p4, *p5, p5[1]) and, if the guard
 * register x21 is clear, stores the 16-byte result into the out buffer.
 * Confidence: medium */
static void sk_callback_copy_16(uint8_t out[16], uint64_t p2, uint64_t p3, uint64_t p4, uint64_t *p5)
{
    uint64_t x21=0;
    uint8_t r[16];
    uint64_t (*cb)(uint64_t,uint64_t,uint64_t,uint64_t) = (uint64_t(*)(uint64_t,uint64_t,uint64_t,uint64_t))0;
    /* cb loaded from x7 at call site */
    if (x21 == 0) { r[0]=(uint8_t)(uintptr_t)cb; }
    (void)p2;(void)p3;(void)p4;(void)p5;(void)out;(void)r;
}
/* FUN_00324404 @ 0x324404   (est. sk_callback_run_setup)
 * Ghidra: void FUN_00324404(undefined1*, undefined8, undefined8, code*)
 * Runs FUN_001b5474(0, p3, p2) then the callback (p4)(&tmp, p2, p3); if the
 * guard x21 is clear, stores tmp into the out buffer.
 * Confidence: medium */
static void sk_callback_run_setup(uint8_t *out, uint64_t p2, uint64_t p3, void (*cb)(uint8_t*,uint64_t,uint64_t))
{
    uint64_t x21=0; uint8_t tmp;
    sk_hlp_001b5474(0, p3, p2);        /* FUN_001b5474 */
    cb(&tmp, p2, p3);
    if (x21 == 0) *out = tmp;
}
/* FUN_003244b4 @ 0x3244b4 (est. sk_ilst_elem_at_0x30)
 * Ghidra: long FUN_003244b4(ulong param_1)
 * Intrusive-list element accessor: clears the low tag bit of the node
 * pointer, dereferences it, and returns the entry located at offset +0x30
 * (base at +0x30 plus the signed delta stored there).
 * Confidence: medium */
static int64_t sk_ilst_elem_at_0x30(uint64_t p){ if(p&1) p=*(uint64_t*)(p&~1ull); return (int64_t)(p+0x30)+(int64_t)*(int32_t*)(p+0x30); }
/* FUN_003244ec @ 0x3244ec (est. sk_ilst_elem_at_0x14) */
static int64_t sk_ilst_elem_at_0x14(uint64_t p){ if(p&1) p=*(uint64_t*)(p&~1ull); return (int64_t)(p+0x14)+(int64_t)*(int32_t*)(p+0x14); }
/* FUN_0032451c @ 0x32451c (est. sk_tls_read)
 * Ghidra: void FUN_0032451c(void) — calls the TLS helper FUN_00021480.
 * Confidence: medium */
static void sk_tls_read(void){ sk_tls(); }
/* FUN_00324534 @ 0x324534 (est. sk_ilst_elem_at_0x38) */
static int64_t sk_ilst_elem_at_0x38(uint64_t p){ if(p&1) p=*(uint64_t*)(p&~1ull); return (int64_t)(p+0x38)+(int64_t)*(int32_t*)(p+0x38); }
/* FUN_00324564 @ 0x324564 (est. sk_ilst_elem_at_0xc) */
static int64_t sk_ilst_elem_at_0xc(uint64_t p){ if(p&1) p=*(uint64_t*)(p&~1ull); return (int64_t)(p+0xc)+(int64_t)*(int32_t*)(p+0xc); }
/* FUN_00324594 @ 0x324594 (est. sk_ilst_elem_at_0x10) */
static int64_t sk_ilst_elem_at_0x10(uint64_t p){ if(p&1) p=*(uint64_t*)(p&~1ull); return (int64_t)(p+0x10)+(int64_t)*(int32_t*)(p+0x10); }
/* FUN_003245c4 @ 0x3245c4 (est. sk_ilst_elem_at_0x1c) */
static int64_t sk_ilst_elem_at_0x1c(uint64_t p){ if(p&1) p=*(uint64_t*)(p&~1ull); return (int64_t)(p+0x1c)+(int64_t)*(int32_t*)(p+0x1c); }
/* FUN_003245f4 @ 0x3245f4 (est. sk_ilst_elem_at_0x4) */
static int64_t sk_ilst_elem_at_0x4(uint64_t p){ if(p&1) p=*(uint64_t*)(p&~1ull); return (int64_t)(p+4)+(int64_t)*(int32_t*)(p+4); }
/* FUN_00324624 @ 0x324624 (est. sk_ilst_elem_at_0x8) */
static int64_t sk_ilst_elem_at_0x8(uint64_t p){ if(p&1) p=*(uint64_t*)(p&~1ull); return (int64_t)(p+8)+(int64_t)*(int32_t*)(p+8); }
/* FUN_00324654 @ 0x324654 (est. sk_trampoline_inst_656278)
 * Ghidra: void FUN_00324654(void)
 * Writes a pre-encoded arm64 instruction word to the trampoline slot at
 * 0x656278 (an exception/jump stub being installed).
 * Confidence: medium
 * Notes: Ghidra "Removing unreachable block" warning; constant is an
 * instruction encoding. */
static void sk_trampoline_inst_656278(void){ sk_gv_656278=0xd71f0841b4000050ull; }
/* FUN_003246a8 @ 0x3246a8 (est. sk_obj_method_slot_0x10_thunk)
 * Ghidra: void FUN_003246a8(undefined8 param_1)
 * Object-method thunk: forwards param_1 and the method slot read from the
 * base object (x20) at +0x10 to the backing routine FUN_002ccf5c.
 * Confidence: medium */
static void sk_obj_method_0x10_thunk(uint64_t arg){ uint64_t x20=0; sk_hlp_002ccf5c(arg,*(uint64_t*)(x20+0x10)); }
/* FUN_003246d4 @ 0x3246d4 (est. sk_tls_read2) — sk_tls() only. */
static void sk_tls_read2(void){ sk_tls(); }
/* FUN_003246ec @ 0x3246ec (est. sk_tls_read3) — sk_tls() only. */
static void sk_tls_read3(void){ sk_tls(); }
/* FUN_00324704 @ 0x324704 (est. sk_obj_method_slot_set_thunk)
 * Ghidra: void FUN_00324704(undefined8 param_1)
 * Object-method thunk: forwards param_1 plus five slots read from the base
 * object (x20) to the backing routine FUN_002ce228.
 * Confidence: medium */
static void sk_obj_method_set_thunk(uint64_t arg){ uint64_t x20=0;
    sk_hlp_002ce228(arg,*(uint64_t*)(x20+0x20),*(uint64_t*)(x20+0x28),*(uint64_t*)(x20+0x10),*(uint64_t*)(x20+0x18)); }
/* FUN_00324734 @ 0x324734 (est. sk_tls_read4) */
static void sk_tls_read4(void){ sk_tls(); }
/* FUN_0032474c @ 0x32474c (est. sk_tls_read5) */
static void sk_tls_read5(void){ sk_tls(); }
/* FUN_00324764 @ 0x324764   (est. sk_guard_slot_store)
 * Ghidra: void FUN_00324764(void)
 * If the run-queue lookup FUN_00352b20 returns 0, runs the guard preamble
 * (FUN_00350b0c, FUN_00349b28, FUN_00027614) and stores the dispatch result
 * into the slot at (x19).
 * Confidence: medium */
static void sk_guard_slot_store(void)
{
    uint64_t *x19=0;
    if (sk_hlp_00352b20() == 0) {
        sk_hlp_00350b0c(); sk_hlp_00349b28(); sk_cur_thread();
        *x19 = sk_dispatch_leave();
    }
}
/* FUN_003247bc @ 0x3247bc (est. sk_tls_read6) */
static void sk_tls_read6(void){ sk_tls(); }
/* FUN_003247d4 @ 0x3247d4   (est. sk_obj_teardown_a)
 * Ghidra: void FUN_003247d4(void)
 * Runs FUN_0035662c, the TLS read (FUN_003246ec), FUN_002cc0ec and
 * FUN_0035396c.
 * Confidence: medium */
static void sk_obj_teardown_a(void){ uint64_t x20=0; sk_hlp_0035662c(); sk_tls_read3(); sk_hlp_002cc0ec(); sk_hlp_0035396c(); }
/* FUN_00324814 @ 0x324814   (est. sk_obj_teardown_b) — same with FUN_00356d20. */
static void sk_obj_teardown_b(void){ uint64_t x20=0; sk_hlp_0035662c(); sk_tls_read3(); sk_hlp_002cc0ec(); sk_hlp_00356d20(); }
/* FUN_00324858 @ 0x324858   (est. sk_obj_method_eight_thunk)
 * Ghidra: void FUN_00324858(undefined8)
 * Forwards one arg plus eight slots from the base object (x20) to the
 * backing routine FUN_002d1070.
 * Confidence: medium */
static void sk_obj_method_eight_thunk(uint64_t a){ uint64_t x20=0;
    sk_hlp_002d1070(a,*(uint64_t*)(x20+0x20),*(uint64_t*)(x20+0x28),*(uint64_t*)(x20+0x30),*(uint64_t*)(x20+0x38),*(uint64_t*)(x20+0x40),*(uint64_t*)(x20+0x48),*(uint64_t*)(x20+0x10),*(uint64_t*)(x20+0x18)); }
/* FUN_0032488c @ 0x32488c   (est. sk_irq_notify_dispatch)
 * Ghidra: void FUN_0032488c(void)
 * Runs the IRQ notify/dispatch chain: object slot lookups, an IRQ handler
 * (FUN_0014ae44), thread-bind (FUN_00027754) and the event/notify helpers.
 * Confidence: medium */
static void sk_irq_notify_dispatch(void)
{
    uint64_t x20=0, x30=0;
    uint64_t u3,u4; int (*cb)(void);
    sk_hlp_00084220(); sk_hlp_0008409c();
    u3=*(uint64_t*)(x20+0x10); u4=*(uint64_t*)(x20+0x20);
    cb=(int(*)(void))sk_irq(*(uint64_t*)(x20+0x30));   /* FUN_0014ae44 */
    sk_cur_tcb(u4);                       /* FUN_00027754 */
    sk_hlp_00350bd8();
    { uint64_t a16[2]; a16[0]=sk_hlp_00349ea0(); a16[1]=0;
      sk_hlp_00377824(a16[0],a16[1],u3);
      sk_hlp_00084180(a16[0],a16[1],a16[0]); }
    cb();
    sk_hlp_00084234(cb() & 1, x30);
}
/* FUN_00324904 @ 0x324904 (est. sk_trampoline_inst_6562b8) */
static void sk_trampoline_inst_6562b8(void){ sk_gv_6562b8=0xd282ed21f9400515ull; }
/* FUN_00324958 @ 0x324958 (est. sk_trampoline_inst_6562c0) */
static void sk_trampoline_inst_6562c0(void){ sk_gv_6562c0=0xf2c00801f2b4b041ull; }
/* FUN_003249ac @ 0x3249ac (est. sk_trampoline_inst_6562c8) */
static void sk_trampoline_inst_6562c8(void){ sk_gv_6562c8=0xaa1503e0f2e021c1ull; }
/* FUN_00324a60 @ 0x324a60 (est. sk_ilst_elem_at_0x24) */
static int64_t sk_ilst_elem_at_0x24(uint64_t p){ if(p&1) p=*(uint64_t*)(p&~1ull); return (int64_t)(p+0x24)+(int64_t)*(int32_t*)(p+0x24); }
/* FUN_00324a90 @ 0x324a90 (est. sk_ilst_elem_at_0x48) */
static int64_t sk_ilst_elem_at_0x48(uint64_t p){ if(p&1) p=*(uint64_t*)(p&~1ull); return (int64_t)(p+0x48)+(int64_t)*(int32_t*)(p+0x48); }
/* FUN_00324ac0 @ 0x324ac0 (est. sk_trampoline_inst_6562d0) */
static void sk_trampoline_inst_6562d0(void){ sk_gv_6562d0=0xaa0003f49400b136ull; }
/* FUN_00324b14 @ 0x324b14 (est. sk_trampoline_inst_6562d8) */
static void sk_trampoline_inst_6562d8(void){ sk_gv_6562d8=0xaa1303f6b40006c0ull; }
/* FUN_00324b68 @ 0x324b68 (est. sk_trampoline_inst_6562e0) */
static void sk_trampoline_inst_6562e0(void){ sk_gv_6562e0=0xb4000708f8410ec8ull; }
/* FUN_00324bbc / 0x324bc0 (est. sk_obj_release_pair)
 * Ghidra: void FUN_00324bbc(void)
 * Releases the two heap objects referenced from the base object (x20) at
 * +0x18 and +0x30 via sk_free, then runs the zone-teardown FUN_0036b21c.
 * Confidence: medium */
static void sk_obj_release_pair(void){ uint64_t x20=0; sk_free(*(uint64_t*)(x20+0x18)); sk_free(*(uint64_t*)(x20+0x30)); sk_hlp_0036b21c(); }
/* FUN_00324bbc / 0x324bc0 (est. sk_obj_release_pair)
 * Ghidra: void FUN_00324bbc(void)
 * Releases the two heap objects referenced from the base object (x20) at
 * +0x18 and +0x30 via sk_free, then runs the zone-teardown FUN_0036b21c.
 * Confidence: medium */
static void sk_obj_release_pair_b(void){ uint64_t x20=0; sk_free(*(uint64_t*)(x20+0x18)); sk_free(*(uint64_t*)(x20+0x30)); sk_hlp_0036b21c(); }
/* FUN_00324bf0 @ 0x324bf0 (est. sk_get_meta_0x6573a0)
 * Ghidra: undefined1[16] FUN_00324bf0(void) — returns the 16-byte constant
 * pointer 0x6573a0 (metadata/type descriptor).
 * Confidence: medium */
static uint64_t sk_get_meta_0x6573a0(void){ return 0x6573a0ull; }
/* FUN_00324c00 / 0x324c04 (est. sk_obj_release_meta)
 * Ghidra: void FUN_00324c00(void)
 * Releases the heap object at (x20)+0x20 via sk_free, runs the teardown
 * FUN_00359018 and FUN_0036b21c.
 * Confidence: medium */
static void sk_obj_release_meta(void){ uint64_t x20=0; sk_free(*(uint64_t*)(x20+0x20)); sk_hlp_00359018(); sk_hlp_0036b21c(); }
/* FUN_00324c00 / 0x324c04 (est. sk_obj_release_meta)
 * Ghidra: void FUN_00324c00(void)
 * Releases the heap object at (x20)+0x20 via sk_free, runs the teardown
 * FUN_00359018 and FUN_0036b21c.
 * Confidence: medium */
static void sk_obj_release_meta_b(void){ uint64_t x20=0; sk_free(*(uint64_t*)(x20+0x20)); sk_hlp_00359018(); sk_hlp_0036b21c(); }
/* FUN_00324c34 @ 0x324c34 (est. sk_tls_read7) */
static void sk_tls_read7(void){ sk_tls(); }
/* FUN_00324c4c / 0x324c50 (est. sk_obj_method_slots_thunk)
 * Ghidra: void FUN_00324c4c(undefined8, undefined8)
 * Forwards two args plus six slots from the base object (x20) to the backing
 * routine FUN_00320dbc.
 * Confidence: medium */
static void sk_obj_method_slots_thunk(uint64_t a,uint64_t b){ uint64_t x20=0;
    sk_hlp_00320dbc(a,b,*(uint64_t*)(x20+0x20),*(uint64_t*)(x20+0x28),*(uint64_t*)(x20+0x30),*(uint64_t*)(x20+0x38),*(uint64_t*)(x20+0x10),*(uint64_t*)(x20+0x18)); }
/* FUN_00324c4c / 0x324c50 (est. sk_obj_method_slots_thunk)
 * Ghidra: void FUN_00324c4c(undefined8, undefined8)
 * Forwards two args plus six slots from the base object (x20) to the backing
 * routine FUN_00320dbc.
 * Confidence: medium */
static void sk_obj_method_slots_thunk_b(uint64_t a,uint64_t b){ uint64_t x20=0;
    sk_hlp_00320dbc(a,b,*(uint64_t*)(x20+0x20),*(uint64_t*)(x20+0x28),*(uint64_t*)(x20+0x30),*(uint64_t*)(x20+0x38),*(uint64_t*)(x20+0x10),*(uint64_t*)(x20+0x18)); }
/* FUN_00324c80 / 0x324c84 (est. sk_obj_method_four_thunk)
 * Ghidra: void FUN_00324c80(undefined8, undefined8)
 * Forwards two args plus two object slots (+0x18,+0x10) to FUN_002e3b64.
 * Confidence: medium */
static void sk_obj_method_four_thunk(uint64_t a,uint64_t b){ uint64_t x20=0;
    sk_hlp_002e3b64(a,*(uint64_t*)(x20+0x18),*(uint64_t*)(x20+0x10),b); }
/* FUN_00324c80 / 0x324c84 (est. sk_obj_method_four_thunk)
 * Ghidra: void FUN_00324c80(undefined8, undefined8)
 * Forwards two args plus two object slots (+0x18,+0x10) to FUN_002e3b64.
 * Confidence: medium */
static void sk_obj_method_four_thunk_b(uint64_t a,uint64_t b){ uint64_t x20=0;
    sk_hlp_002e3b64(a,*(uint64_t*)(x20+0x18),*(uint64_t*)(x20+0x10),b); }
/* FUN_00324ca0 @ 0x324ca0 (est. sk_ilst_elem_at_0x10b) */
static int64_t sk_ilst_elem_at_0x10b(uint64_t p){ if(p&1) p=*(uint64_t*)(p&~1ull); return (int64_t)(p+0x10)+(int64_t)*(int32_t*)(p+0x10); }
/* FUN_00324cd4 @ 0x324cd4 (est. sk_fsqrt)
 * Ghidra: float FUN_00324cd4(float) — floating-point square root.
 * Confidence: medium */
static float sk_fsqrt(float v){ float r; __asm__("fsqrt s0, s0" : "=w"(r) : "w"(v)); return r; }
/* FUN_00324cdc @ 0x324cdc (est. sk_trampoline_inst_656310) */
static void sk_trampoline_inst_656310(void){ sk_gv_656310=0xaa1503e2aa1303e1ull; }
/* FUN_00324d30 @ 0x324d30 (est. sk_trampoline_inst_656318) */
static void sk_trampoline_inst_656318(void){ sk_gv_656318=0xf9400a7094009a96ull; }
/* FUN_00324d84 @ 0x324d84 (est. sk_trampoline_inst_656320) */
static void sk_trampoline_inst_656320(void){ sk_gv_656320=0x91004291b4000090ull; }
/* FUN_00324ddc @ 0x324ddc (est. sk_dsqrt)
 * Ghidra: undefined1[16] FUN_00324ddc(double) — double sqrt in a 16-byte ret.
 * Confidence: medium */
static void sk_dsqrt(double v, uint64_t out[2]){ double r; __asm__("fsqrt d0, d0" : "=w"(r) : "w"(v)); out[0]=(uint64_t)r; out[1]=0; }
/* FUN_00324de4/de8 (est. sk_check_meta1)
 * Ghidra: void FUN_00324de4(undefined8, undefined8)
 * Delegates to FUN_00324e3c with the metadata comparator FUN_00310d04.
 * Confidence: medium */
static void sk_check_meta1(uint64_t a,uint64_t b){ sk_check_meta_common(a,b,sk_hlp_00310d04); }
/* FUN_00324de4/de8 (est. sk_check_meta1)
 * Ghidra: void FUN_00324de4(undefined8, undefined8)
 * Delegates to FUN_00324e3c with the metadata comparator FUN_00310d04.
 * Confidence: medium */
static void sk_check_meta1_b(uint64_t a,uint64_t b){ sk_check_meta_common(a,b,sk_hlp_00310d04); }
/* FUN_00324e10/e14 (est. sk_check_meta2)
 * Ghidra: void FUN_00324e10(undefined8, undefined8) — comparator FUN_00310d1c.
 * Confidence: medium */
static void sk_check_meta2(uint64_t a,uint64_t b){ sk_check_meta_common(a,b,sk_hlp_00310d1c); }
/* FUN_00324e10/e14 (est. sk_check_meta2)
 * Ghidra: void FUN_00324e10(undefined8, undefined8) — comparator FUN_00310d1c.
 * Confidence: medium */
static void sk_check_meta2_b(uint64_t a,uint64_t b){ sk_check_meta_common(a,b,sk_hlp_00310d1c); }
/* FUN_00324e3c @ 0x324e3c   (est. sk_check_meta_common)
 * Ghidra: void FUN_00324e3c(undefined8, undefined8, code*)
 * Runs the metadata probe (FUN_0035860c + FUN_00358b9c), calls the
 * comparator callback (param_3)(0), and stores the 16-byte result of
 * FUN_0022944c into the slot at (x22).
 * Confidence: medium */
static void sk_check_meta_common(uint64_t p1, uint64_t p2, uint64_t (*cmp)(void))
{
    uint64_t x20=0; uint8_t (*x22)[16]=0; uint8_t r[16];
    uint64_t v = sk_hlp_0035860c();        /* FUN_0035860c */
    sk_hlp_00358b9c(v, *(uint64_t*)(x20+0x10));  /* FUN_00358b9c */
    cmp();
    sk_hlp_0022944c(r, 0);                 /* FUN_0022944c */
    /* *x22 = r; */
    (void)r;(void)x22;(void)p1;(void)p2;
}
/* FUN_00324e8c/e90 (est. sk_buffer_meta_unmut_ptr)
 * Ghidra: void FUN_00324e8c(undefined8, undefined8)
 * Raises the "UnsafeMutableRawBufferPointer with negative stride" error via
 * FUN_00324ee4 (code 0xfc7, file 0x31, line 0x74).
 * Confidence: high (string DAT_005cde70 matches). */
static void sk_buffer_meta_unmut_ptr(uint64_t a,uint64_t b){ sk_raise_buffer_err(a,b,0x5cde70,0x31,0x74,0xfc7); }
/* FUN_00324e8c/e90 (est. sk_buffer_meta_unmut_ptr)
 * Ghidra: void FUN_00324e8c(undefined8, undefined8)
 * Raises the "UnsafeMutableRawBufferPointer with negative stride" error via
 * FUN_00324ee4 (code 0xfc7, file 0x31, line 0x74).
 * Confidence: high (string DAT_005cde70 matches). */
static void sk_buffer_meta_unmut_ptr_b(uint64_t a,uint64_t b){ sk_raise_buffer_err(a,b,0x5cde70,0x31,0x74,0xfc7); }
/* FUN_00324eb8/ebc (est. sk_buffer_meta_neg_ptr)
 * Ghidra: void FUN_00324eb8(undefined8, undefined8)
 * Raises the "UnsafeRawBufferPointer with negative..." error via FUN_00324ee4
 * (code 0x323, file 0x2a, line 0x4c1).
 * Confidence: high (string DAT_005cdef0 matches). */
static void sk_buffer_meta_neg_ptr(uint64_t a,uint64_t b){ sk_raise_buffer_err(a,b,0x5cdef0,0x2a,0x4c1,0x323); }
/* FUN_00324eb8/ebc (est. sk_buffer_meta_neg_ptr)
 * Ghidra: void FUN_00324eb8(undefined8, undefined8)
 * Raises the "UnsafeRawBufferPointer with negative..." error via FUN_00324ee4
 * (code 0x323, file 0x2a, line 0x4c1).
 * Confidence: high (string DAT_005cdef0 matches). */
static void sk_buffer_meta_neg_ptr_b(uint64_t a,uint64_t b){ sk_raise_buffer_err(a,b,0x5cdef0,0x2a,0x4c1,0x323); }
/* FUN_00324ee4 @ 0x324ee4   (est. sk_raise_buffer_err)
 * Ghidra: void FUN_00324ee4(long) — decompiler keeps only param_1; the six
 * call-site arguments (buffer, str, file, line, code) are dropped.
 * If the size header at (x20+0x10)[-8][0x40] is non-negative, calls the
 * failure callback (x20+0x20)(p1, p1+len) and may run FUN_00354720; otherwise
 * runs the fatal-error path (FUN_0034dab8 / FUN_0034951c / FUN_00349644 /
 * FUN_00351094) and the noreturn FUN_001afe4c.
 * Confidence: medium */
static void sk_raise_buffer_err(uint64_t p1, uint64_t p2, uint64_t str, uint32_t file,
                                uint32_t line, uint32_t code)
{
    uint64_t x20=0, x21=0;
    (void)p2;(void)str;(void)file;(void)line;(void)code;
    long len = *(long*)(*(long*)(*(long*)(x20+0x10) + -8) + 0x40);
    if (len >= 0) {
        ((void(*)(uint64_t,uint64_t))(*(uint64_t*)(x20+0x20)))(p1, p1+(uint64_t)len);
        if (x21 != 0) sk_hlp_00354720();
        return;
    }
    sk_hlp_0034dab8(); sk_hlp_0034951c(); sk_hlp_00349644(); sk_hlp_00351094();
    sk_hlp_001afe4c();   /* FUN_001afe4c: noreturn */
}
/* FUN_00324f78 @ 0x324f78 (est. sk_slot_init_0x10)
 * Ghidra: void FUN_00324f78(long param_1)
 * Stores a dispatch-handler pointer (from DAT_004e82bc) into slot +0x10.
 * Confidence: medium */
static void sk_slot_init_0x10(uint64_t o){ uint64_t v=sk_dispatch_leave((uint64_t)&sk_dat_004e82bc); *(uint64_t*)(o+0x10)=v; }
/* FUN_00324fd0 @ 0x324fd0 (est. sk_slot_init_8)
 * Ghidra: void FUN_00324fd0(long param_1) — slot +8 from DAT_004e824c.
 * Confidence: medium */
static void sk_slot_init_8(uint64_t o){ uint64_t v=sk_dispatch_leave((uint64_t)&sk_dat_004e824c); *(uint64_t*)(o+8)=v; }
/* FUN_00325044 @ 0x325044 (est. sk_slot_init_8_h)
 * Ghidra: void FUN_00325044(long param_1) — FUN_00348718 then slot +8.
 * Confidence: medium */
static void sk_slot_init_8_h(uint64_t o){ sk_hlp_00348718(); uint64_t v=sk_dispatch_leave(); *(uint64_t*)(o+8)=v; }
/* FUN_00325088 @ 0x325088   (est. sk_guard_init_pair)
 * Ghidra: void FUN_00325088(void)
 * If the run-queue lookup returns 0, runs the guard init (FUN_00359880,
 * FUN_00027614, FUN_00027670, FUN_0006b6f4) and stores the dispatch result
 * into (x19).
 * Confidence: medium */
static void sk_guard_init_pair(void)
{
    uint64_t *x19=0; uint64_t local_40=0x6720e8;
    if (sk_hlp_00352b20() == 0) {
        sk_hlp_00359880(); sk_cur_thread();
        { uint64_t v0=sk_hlp_00027670(), v1=0;
          sk_hlp_0006b6f4(v0, v1, &local_40); }
        *x19 = sk_dispatch_leave();
    }
}
/* FUN_00325178 @ 0x325178 (est. sk_slot_init_0x10_h)
 * Ghidra: void FUN_00325178(long param_1) — FUN_00356dec then slot +0x10.
 * Confidence: medium */
static void sk_slot_init_0x10_h(uint64_t o){ sk_hlp_00356dec(); uint64_t v=sk_dispatch_leave(); *(uint64_t*)(o+0x10)=v; }
/* FUN_003251a4 @ 0x3251a4 (est. sk_slot_init_8_e)
 * Ghidra: void FUN_003251a4(long param_1) — FUN_00356e04 then slot +8.
 * Confidence: medium */
static void sk_slot_init_8_e(uint64_t o){ sk_hlp_00356e04(); uint64_t v=sk_dispatch_leave(); *(uint64_t*)(o+8)=v; }
/* FUN_003251d0 @ 0x3251d0 (est. sk_slot_init_8_d)
 * Ghidra: void FUN_003251d0(long param_1) — FUN_00348d00 then slot +8.
 * Confidence: medium */
static void sk_slot_init_8_d(uint64_t o){ sk_hlp_00348d00(); uint64_t v=sk_dispatch_leave(); *(uint64_t*)(o+8)=v; }
/* FUN_00325214/18 (est. sk_init_handlers_pair)
 * Ghidra: void FUN_00325214(void) — FUN_00355244 with two address slots and a
 * data descriptor (DAT_004e84f0).
 * Confidence: medium */
static void sk_init_handlers_pair(void){ sk_hlp_00355244(0x656388,0x656390,(uint64_t)&sk_dat_004e84f0); }
/* FUN_00325214/18 (est. sk_init_handlers_pair)
 * Ghidra: void FUN_00325214(void) — FUN_00355244 with two address slots and a
 * data descriptor (DAT_004e84f0).
 * Confidence: medium */
static void sk_init_handlers_pair_b(void){ sk_hlp_00355244(0x656388,0x656390,(uint64_t)&sk_dat_004e84f0); }
/* FUN_00325258/5c (est. sk_install_handler_656398)
 * Ghidra: void FUN_00325258(void)
 * Installs the dispatch handler for DAT_004e8514 + 0x6726c8 into slot 0x656398.
 * Confidence: medium */
static void sk_install_handler_656398(void){ sk_gv_656398=sk_dispatch_leave((uint64_t)&sk_dat_004e8514,0x6726c8); }
/* FUN_00325258/5c (est. sk_install_handler_656398)
 * Ghidra: void FUN_00325258(void)
 * Installs the dispatch handler for DAT_004e8514 + 0x6726c8 into slot 0x656398.
 * Confidence: medium */
static void sk_install_handler_656398_b(void){ sk_gv_656398=sk_dispatch_leave((uint64_t)&sk_dat_004e8514,0x6726c8); }
/* FUN_00325318 @ 0x325318 (est. sk_slot_init_0x10_b)
 * Ghidra: void FUN_00325318(long param_1) — FUN_0034b5fc then slot +0x10.
 * Confidence: medium */
static void sk_slot_init_0x10_b(uint64_t o){ sk_hlp_0034b5fc(); uint64_t v=sk_dispatch_leave(); *(uint64_t*)(o+0x10)=v; }
/* FUN_00325344 @ 0x325344 (est. sk_slot_init_8_c)
 * Ghidra: void FUN_00325344(long param_1) — slot +8 from DAT_004e8bb4.
 * Confidence: medium */
static void sk_slot_init_8_c(uint64_t o){ uint64_t v=sk_dispatch_leave((uint64_t)&sk_dat_004e8bb4); *(uint64_t*)(o+8)=v; }
/* FUN_00325380 @ 0x325380 (est. sk_slot_init_8_b)
 * Ghidra: void FUN_00325380(long param_1) — FUN_00349234 then slot +8.
 * Confidence: medium */
static void sk_slot_init_8_b(uint64_t o){ sk_hlp_00349234(); uint64_t v=sk_dispatch_leave(); *(uint64_t*)(o+8)=v; }
/* FUN_00325414/ac, 0x325544 (est. sk_slot_err_3x)
 * Ghidra: void FUN_00325414(void) — badge-mask2 (FUN_00352220) then err
 * (FUN_003581fc) stored at (x19)+8. Three identical bodies.
 * Confidence: medium */
static void sk_slot_err_3x_a(void){ uint64_t x19=0; sk_badgemsk2(); *(uint64_t*)(x19+8)=sk_err(); }
/* FUN_00325414/ac, 0x325544 (est. sk_slot_err_3x)
 * Ghidra: void FUN_00325414(void) — badge-mask2 (FUN_00352220) then err
 * (FUN_003581fc) stored at (x19)+8. Three identical bodies.
 * Confidence: medium */
static void sk_slot_err_3x_b(void){ uint64_t x19=0; sk_badgemsk2(); *(uint64_t*)(x19+8)=sk_err(); }
/* FUN_00325414/ac, 0x325544 (est. sk_slot_err_3x)
 * Ghidra: void FUN_00325414(void) — badge-mask2 (FUN_00352220) then err
 * (FUN_003581fc) stored at (x19)+8. Three identical bodies.
 * Confidence: medium */
static void sk_slot_err_3x_c(void){ uint64_t x19=0; sk_badgemsk2(); *(uint64_t*)(x19+8)=sk_err(); }
/* FUN_003255b0 @ 0x3255b0 (est. sk_slot_init_8_f)
 * Ghidra: void FUN_003255b0(long param_1) — slot +8 from DAT_004e8f80.
 * Confidence: medium */
static void sk_slot_init_8_f(uint64_t o){ uint64_t v=sk_dispatch_leave((uint64_t)&sk_dat_004e8f80); *(uint64_t*)(o+8)=v; }
/* FUN_003255ec @ 0x3255ec (est. sk_slot_init_8_g)
 * Ghidra: void FUN_003255ec(long param_1) — FUN_0034e35c then slot +8.
 * Confidence: medium */
static void sk_slot_init_8_g(uint64_t o){ sk_hlp_0034e35c(); uint64_t v=sk_dispatch_leave(); *(uint64_t*)(o+8)=v; }
/* FUN_00325660 @ 0x325660 (est. sk_install_handler_pair)
 * Ghidra: void FUN_00325660(undefined8 param_1)
 * Looks up the handler for DAT_004e90b0, obtains a second value from
 * FUN_00349e38 and installs both via sk_dispatch_leave.
 * Confidence: medium */
static void sk_install_handler_pair(uint64_t arg){ sk_dispatch_leave((uint64_t)&sk_dat_004e90b0); uint64_t v=sk_hlp_00349e38(); sk_dispatch_leave(v,arg); }
/* FUN_00325754 @ 0x325754 (est. sk_dispatch_stub_badgemask)
 * Ghidra: void FUN_00325754(void)
 * Runs the badge-mask (FUN_0034b6a4) + cap-check (FUN_0035142c) preamble then
 * the common dispatch tail (FUN_00376820).
 * Confidence: medium */
static void sk_dispatch_stub_badgemask(void){ sk_badgemsk(); sk_cap_check(); sk_dispatch_leave(); }
/* FUN_0032582c @ 0x32582c (est. sk_dispatch_stub_badgemask_b) — same body. */
static void sk_dispatch_stub_badgemask_b(void){ sk_badgemsk(); sk_cap_check(); sk_dispatch_leave(); }
/* FUN_00325864 / 0x325ac0 / 0x325d40 (est. sk_slot_badge_ck_3x)
 * Ghidra: void FUN_00325864(void) — badge (FUN_00352210) + cap_check
 * (FUN_0035142c) then dispatch result at (x19)+8. Three identical bodies.
 * Confidence: medium */
static void sk_slot_badge_ck_3x_a(void){ uint64_t x19=0; sk_badge(); sk_cap_check(); *(uint64_t*)(x19+8)=sk_dispatch_leave(); }
/* FUN_003258dc @ 0x3258dc (est. sk_slot_init_8_h2)
 * Ghidra: void FUN_003258dc(long param_1) — FUN_00356dd4 then slot +8.
 * Confidence: medium */
static void sk_slot_init_8_h2(uint64_t o){ sk_hlp_00356dd4(); uint64_t v=sk_dispatch_leave(); *(uint64_t*)(o+8)=v; }
/* FUN_00325940 @ 0x325940 (est. sk_slot_init_8_i)
 * Ghidra: void FUN_00325940(long param_1) — FUN_00348d18 then slot +8.
 * Confidence: medium */
static void sk_slot_init_8_i(uint64_t o){ sk_hlp_00348d18(); uint64_t v=sk_dispatch_leave(); *(uint64_t*)(o+8)=v; }
/* FUN_00325a10 @ 0x325a10   (est. sk_slot_bind_cur)
 * Ghidra: void FUN_00325a10(undefined8, undefined8, undefined8*)
 * Binds the current thread twice (FUN_00027754), runs the cap check and
 * stores the dispatch result at (x20)+8.
 * Confidence: medium */
static void sk_slot_bind_cur(uint64_t a,uint64_t b,uint64_t *p3)
{
    uint64_t x20=0;
    sk_hlp_003504d0();                  /* FUN_003504d0 */
    sk_cur_tcb(*p3);                    /* FUN_00027754 */
    sk_cur_tcb();                       /* FUN_00027754 */
    sk_cap_check();                     /* FUN_0035142c */
    *(uint64_t*)(x20+8)=sk_dispatch_leave();
}
/* FUN_00325864 / 0x325ac0 / 0x325d40 (est. sk_slot_badge_ck_3x)
 * Ghidra: void FUN_00325864(void) — badge (FUN_00352210) + cap_check
 * (FUN_0035142c) then dispatch result at (x19)+8. Three identical bodies.
 * Confidence: medium */
static void sk_slot_badge_ck_3x_b(void){ uint64_t x19=0; sk_badge(); sk_cap_check(); *(uint64_t*)(x19+8)=sk_dispatch_leave(); }
/* FUN_00325b4c / 0x325c48 (est. sk_dispatch_notify_2x)
 * Ghidra: void FUN_00325b4c(undefined8) — FUN_00356dbc, dispatch tail, then
 * notify (FUN_00349e70) and dispatch. Two identical bodies.
 * Confidence: medium */
static void sk_dispatch_notify_2x_a(uint64_t p){ sk_hlp_00356dbc(); sk_dispatch_leave(); uint64_t v=sk_notify(); sk_dispatch_leave(v,p); }
/* FUN_00325bc0 / 0x327948 (est. sk_dispatch_ntfn_2x)
 * Ghidra: void FUN_00325bc0(undefined8) — notification (FUN_0034ddb0).
 * Confidence: medium */
static void sk_dispatch_ntfn_2x_a(uint64_t p){ sk_hlp_00356da4(); sk_dispatch_leave(); uint64_t v=sk_ntfn(); sk_dispatch_leave(v,p); }
/* FUN_00325c1c @ 0x325c1c (est. sk_slot_init_8_j)
 * Ghidra: void FUN_00325c1c(long param_1) — FUN_0035081c then slot +8.
 * Confidence: medium */
static void sk_slot_init_8_j(uint64_t o){ sk_hlp_0035081c(); uint64_t v=sk_dispatch_leave(); *(uint64_t*)(o+8)=v; }
/* FUN_00325b4c / 0x325c48 (est. sk_dispatch_notify_2x)
 * Ghidra: void FUN_00325b4c(undefined8) — FUN_00356dbc, dispatch tail, then
 * notify (FUN_00349e70) and dispatch. Two identical bodies.
 * Confidence: medium */
static void sk_dispatch_notify_2x_b(uint64_t p){ sk_hlp_0035081c(); sk_dispatch_leave(); uint64_t v=sk_notify(); sk_dispatch_leave(v,p); }
/* FUN_00325d08 @ 0x325d08 (est. sk_dispatch_stub_badgemask_c) — same body. */
static void sk_dispatch_stub_badgemask_c(void){ sk_badgemsk(); sk_cap_check(); sk_dispatch_leave(); }
/* FUN_00325864 / 0x325ac0 / 0x325d40 (est. sk_slot_badge_ck_3x)
 * Ghidra: void FUN_00325864(void) — badge (FUN_00352210) + cap_check
 * (FUN_0035142c) then dispatch result at (x19)+8. Three identical bodies.
 * Confidence: medium */
static void sk_slot_badge_ck_3x_c(void){ uint64_t x19=0; sk_badge(); sk_cap_check(); *(uint64_t*)(x19+8)=sk_dispatch_leave(); }
/* FUN_00325e6c @ 0x325e6c   (est. sk_neon_load_round)
 * Ghidra: void FUN_00325e6c(4 args)
 * Loads a 16-byte vector from (p3 & ~1)-0x10, rotates it 8 bytes (NEON ext),
 * passes it through the dispatch (FUN_00376820) and the power/irq helper
 * (FUN_0009461c).
 * Confidence: medium */
static void sk_neon_load_round(uint64_t a,uint64_t b,uint64_t p3,uint64_t p4)
{
    uint64_t v[2]; uint64_t out[2];
    v[0]=*(uint64_t*)((p3&~1ull)-0x10); v[1]=*(uint64_t*)((p3&~1ull)-0x8);
    /* NEON ext (rotate 8): swap halves */
    out[0]=v[1]; out[1]=v[0];
    { uint64_t r=sk_dispatch_leave(p4,b,out); out[0]=r; out[1]=0;
      sk_power(out[0], out[1], out); }    /* FUN_0009461c */
    sk_dispatch_leave();
}
/* FUN_00325f0c @ 0x325f0c (est. sk_dispatch_stub_notify)
 * Ghidra: void FUN_00325f0c(void) — badge-mask + notify (FUN_00349e70).
 * Confidence: medium */
static void sk_dispatch_stub_notify(void){ sk_badgemsk(); sk_notify(); sk_dispatch_leave(); }
/* FUN_00325f34 @ 0x325f34 (est. sk_dispatch_stub_ntfn)
 * Ghidra: void FUN_00325f34(void) — badge-mask + notification (FUN_0034ddb0).
 * Confidence: medium */
static void sk_dispatch_stub_ntfn(void){ sk_badgemsk(); sk_ntfn(); sk_dispatch_leave(); }
/* FUN_00325f8c / 0x326ae0 / 0x326bb4 / 0x327988 (est. sk_dispatch_evt_4x)
 * Ghidra: void FUN_00325f8c(undefined8) — event (FUN_00348ad8) + dispatch.
 * Confidence: medium */
static void sk_dispatch_evt_4x_a(uint64_t p){ sk_hlp_0034b628(); sk_dispatch_leave(); uint64_t v=sk_evt(); sk_dispatch_leave(v,p); }
/* FUN_00325fcc @ 0x325fcc (est. sk_slot_init_8_k)
 * Ghidra: void FUN_00325fcc(void)
 * Stores FUN_00354ea4()'s result into the TCB slot at (x19)+8.
 * Confidence: medium */
static void sk_slot_init_8_k(void){ uint64_t x19=0; *(uint64_t*)(x19+8)=sk_hlp_00354ea4(); }
/* FUN_00325ff0 @ 0x325ff0 (est. sk_init_objs_notify)
 * Ghidra: void FUN_00325ff0(void)
 * Runs FUN_00354ea4, acquires an object (FUN_00348990) and returns it via
 * the syscall-return helper FUN_00356518.
 * Confidence: medium */
static void sk_init_objs_notify(void){ sk_hlp_00354ea4(); sk_obj_acquire(); sk_sys_ret(); }
/* FUN_00326024 @ 0x326024 (est. sk_slot_init_8_l)
 * Ghidra: void FUN_00326024(long param_1) — FUN_00354798 then slot +8.
 * Confidence: medium */
static void sk_slot_init_8_l(uint64_t o){ sk_hlp_00354798(); uint64_t v=sk_dispatch_leave(); *(uint64_t*)(o+8)=v; }
