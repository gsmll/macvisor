/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel,
 * arm64e, image base 0) — the cL4 microkernel (GL1). Ground truth: Ghidra FUN_
 * names + addresses in program cl4_kernel.raw. Version "cL4 microkernel
 * (cL4 (679.100.61))". All names are estimates unless string/header-matched.
 *
 * This file covers the syscall/exception/IPC/CNode dispatch + error-code and
 * boot-region machinery at 0x50000 - 0x60000.
 *
 * SeL4/cL4 vocabulary is used for naming: TCB, cap, CNode, IPC, notification,
 * vspace, sched, etc. Confidence is medium unless a string matches.
 */

#ifndef _SK_REGION_BOOT_50000_H_
#define _SK_REGION_BOOT_50000_H_

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

/* 128-bit message/result word used by the SVC frame ABI. */
typedef struct { uint64_t lo; uint64_t hi; } sk_u128_t;
/* Function pointer rendered from Ghidra's "code *" type. */
typedef void (*sk_code_t)(void);

/* Supervisor-call + debug intrinsics (render of CallSupervisor /
 * SoftwareBreakpoint / LORelease / DataMemoryBarrier / NEON_ext and the
 * tpidr/tpidrro register reads). */
extern uint64_t sk_break(uintptr_t a, ...);
extern uint64_t sk_svc(uintptr_t n, ...);
extern void sk_lo_release(void);
extern void sk_dmb(unsigned long a, unsigned long b);
extern unsigned long sk_tpidrro;
extern unsigned long sk_tpidr;

/* Out-of-region kernel helpers (FUN_ addr in the declaration notes). */

/* Ghidra  */ void sk_abort_msg(uint64_t a1);
/* Ghidra  */ sk_u128_t sk_boot_heap(void);
/* Ghidra  */ uint64_t sk_boot_next(void);
/* Ghidra  */ void sk_cap_load(uint64_t a1, uint64_t a2);
/* Ghidra  */ void sk_cap_store(void);
/* Ghidra  */ long sk_cnode_alloc(unsigned long a1, unsigned long a2);
/* Ghidra  */ void sk_console(void);
/* Ghidra  */ uint64_t sk_ctx_abort(void);
/* Ghidra  */ void sk_ctx_abort2(unsigned long a1);
/* Ghidra  */ void sk_ctx_alloc(long a1, uint64_t a2);
/* Ghidra  */ unsigned long sk_ctx_cpsr(uint64_t a1, uint64_t a2, uint64_t a3);
/* Ghidra  */ bool sk_ctx_dbg(void);
/* Ghidra  */ void sk_ctx_el(void);
/* Ghidra  */ void sk_ctx_exc(long a1);
/* Ghidra  */ void sk_ctx_fault(void);
/* Ghidra  */ sk_u128_t sk_ctx_finish(void);
/* Ghidra  */ uint64_t sk_ctx_flag(long a1);
/* Ghidra  */ unsigned long sk_ctx_fp(long a1);
/* Ghidra  */ uint64_t sk_ctx_id(long a1);
/* Ghidra  */ long sk_ctx_ip(long a1);
/* Ghidra  */ void sk_ctx_irq(uint64_t a1, uint64_t a2);
/* Ghidra  */ void sk_ctx_meta(uint64_t *a1, long a2);
/* Ghidra  */ uint64_t sk_ctx_owner(long a1);
/* Ghidra  */ void sk_ctx_panic(uint64_t a1, uint64_t a2, uint64_t a3, long a4, int a5, int a6, unsigned long a7, unsigned long a8);
/* Ghidra  */ long sk_ctx_pop(long a1, long a2);
/* Ghidra  */ void sk_ctx_printf(uint64_t a1, uint64_t a2);
/* Ghidra  */ void sk_ctx_push(long a1, uint64_t a2);
/* Ghidra  */ uint64_t sk_ctx_regs(long a1);
/* Ghidra  */ void sk_ctx_save(long a1, long *a2, long *a3);
/* Ghidra  */ long sk_ctx_sp(long a1);
/* Ghidra  */ void sk_ctx_stack(long a1);
/* Ghidra  */ unsigned long sk_ctx_state(long a1, long a2);
/* Ghidra  */ void sk_ctx_trace(void);
/* Ghidra  */ void sk_ctx_type(uint64_t *a1, long a2);
/* Ghidra  */ uint64_t sk_ctx_vm(unsigned long a1);
/* Ghidra  */ uint32_t sk_ctx_vm2(unsigned long a1);
/* Ghidra  */ uint64_t sk_current_thread(void);
/* Ghidra  */ void sk_debug(uint64_t a1);
/* Ghidra  */ uint8_t * sk_disable_preempt(uint8_t *a1);
/* Ghidra  */ bool sk_domain_state(void);
/* Ghidra  */ void sk_enable_preempt(uint8_t *a1);
/* Ghidra  */ uint64_t sk_hexdump(char a1, uint64_t a2);
/* Ghidra  */ void sk_klog(uint64_t a1, uint8_t a2);
/* Ghidra  */ void sk_klog2(void);
/* Ghidra  */ void sk_klog3(void);
/* Ghidra  */ void sk_klog4(void);
/* Ghidra  */ uint32_t sk_log_char(unsigned long a1);
/* Ghidra  */ unsigned long sk_log_fmt(uint64_t a1, unsigned long a2, unsigned long a3, uint64_t a4);
/* Ghidra  */ void sk_log_str(uint64_t a1);
/* Ghidra  */ void sk_log_v(uint64_t a1, uint64_t a2, uint64_t a3);
/* Ghidra  */ unsigned int sk_macho_dysymtab(long a1, long a2, long a3, long a4);
/* Ghidra  */ void sk_macho_hdr(uint64_t a1);
/* Ghidra  */ void sk_macho_loadcmds(uint64_t a1, uint64_t a2);
/* Ghidra  */ sk_u128_t sk_macho_segcmd(long a1, long a2, long a3, long a4);
/* Ghidra  */ sk_u128_t sk_macho_symtab(long a1, long a2, long a3, long a4);
/* Ghidra  */ uint32_t sk_macho_uuid2(long a1);
/* Ghidra  */ long sk_memcmp(unsigned long a1);
/* Ghidra  */ void sk_memcpy(long *a1, unsigned long a2, unsigned long a3);
/* Ghidra  */ void sk_memcpy2(uint64_t *a1, uint64_t *a2, unsigned long a3);
/* Ghidra  */ void sk_memmove(uint64_t a1, uint64_t a2, unsigned long a3, unsigned long a4);
/* Ghidra  */ void sk_memset(uint64_t *a1, unsigned long a2);
/* Ghidra  */ void sk_msg_cap_read(void);
/* Ghidra  */ void sk_msg_capacity(void);
/* Ghidra  */ unsigned long sk_msg_count(unsigned short *a1);
/* Ghidra  */ long sk_msg_get(unsigned short *a1, unsigned long a2);
/* Ghidra  */ unsigned short * sk_msg_iter(long *a1);
/* Ghidra  */ unsigned int sk_msg_next(unsigned short *a1);
/* Ghidra  */ void sk_msg_push_cap(void);
/* Ghidra  */ void sk_msg_record(uint64_t a1, unsigned short *a2, uint64_t a3, uint64_t a4, long a5, uint64_t a6);
/* Ghidra  */ void sk_msg_zero(void);
/* Ghidra  */ sk_u128_t sk_noreturn_error(uint64_t a1, uint64_t a2, unsigned long a3, unsigned long a4);
/* Ghidra  */ unsigned long * sk_obj_alloc(unsigned long *a1, uint64_t a2, long a3, long a4, long a5);
/* Ghidra  */ void sk_obj_ref(void);
/* Ghidra  */ void sk_panic_log(uint64_t a1, uint64_t a2);
/* Ghidra  */ unsigned long sk_phys_to_obj(unsigned long a1);
/* Ghidra  */ void sk_pmap_op(long a1, long a2, long a3);
/* Ghidra  */ uint8_t sk_preempt_check(void);
/* Ghidra  */ void sk_printf(long a1, long a2);
/* Ghidra  */ void sk_rt_assert(void);
/* Ghidra  */ void sk_rt_barrier(void);
/* Ghidra  */ void sk_rt_check(uint16_t *a1, long a2, unsigned long *a3);
/* Ghidra  */ void sk_rt_dbg(void);
/* Ghidra  */ void sk_rt_done(void);
/* Ghidra  */ void sk_rt_error(void);
/* Ghidra  */ void sk_rt_flags(void);
/* Ghidra  */ void sk_rt_list(void);
/* Ghidra  */ void sk_rt_list2(void);
/* Ghidra  */ void sk_rt_lock(void);
/* Ghidra  */ void sk_rt_log(long a1, long a2);
/* Ghidra  */ void sk_rt_meta(long a1);
/* Ghidra  */ uint64_t sk_rt_park(uint64_t a1, uint64_t a2, long a3);
/* Ghidra  */ void sk_rt_phase(void);
/* Ghidra  */ void sk_rt_proc(void);
/* Ghidra  */ void sk_rt_proc10(void);
/* Ghidra  */ void sk_rt_proc11(void);
/* Ghidra  */ void sk_rt_proc12(void);
/* Ghidra  */ void sk_rt_proc2(void);
/* Ghidra  */ void sk_rt_proc3(void);
/* Ghidra  */ void sk_rt_proc4(long a1);
/* Ghidra  */ void sk_rt_proc5(void);
/* Ghidra  */ void sk_rt_proc6(void);
/* Ghidra  */ void sk_rt_proc7(void);
/* Ghidra  */ void sk_rt_proc8(void);
/* Ghidra  */ void sk_rt_proc9(void);
/* Ghidra  */ void sk_rt_run(long a1);
/* Ghidra  */ void sk_rt_state(void);
/* Ghidra  */ void sk_rt_sync(void);
/* Ghidra  */ void sk_rt_sync2(void);
/* Ghidra  */ void sk_rt_unlock(void);
/* Ghidra  */ uint64_t sk_rt_unpark(long a1, uint64_t a2, long a3);
/* Ghidra  */ void sk_rt_wait(void);
/* Ghidra  */ void sk_snprintf(uint64_t a1, uint64_t a2, uint64_t a3, uint64_t a4);
/* Ghidra  */ long sk_strchr(unsigned long a1, char a2, long a3);
/* Ghidra  */ long sk_strcmp(uint8_t *a1, uint8_t *a2, unsigned long a3);
/* Ghidra  */ long sk_strlen(unsigned long a1, long a2);
/* Ghidra  */ void sk_syscall_exc(int a1, unsigned int a2);
/* Ghidra  */ void sk_syscall_get_state(void);
/* Ghidra  */ uint64_t sk_thread_create(uint64_t a1, uint64_t a2, uint64_t a3);
/* Ghidra  */ uint8_t sk_thread_lock(void);
/* Ghidra  */ long sk_thread_resume(void);
/* Ghidra  */ void sk_thread_state(void);
/* Ghidra  */ void sk_thread_switch(void *a1, uint64_t a1);
/* Ghidra  */ uint8_t sk_thread_unlock(void);
/* Ghidra  */ uint64_t sk_thread_yield(void);
/* Ghidra  */ void sk_timer(uint64_t a1, uint64_t a2);
/* Ghidra  */ void sk_tlb_flush(void);
/* Ghidra  */ uint32_t sk_trace(unsigned long a1, uint64_t a2);
/* Ghidra  */ bool sk_trap(long a1);
/* Ghidra  */ uint64_t sk_trap2(long a1, uint64_t a2);
/* Ghidra  */ uint64_t sk_trap3(long a1, uint64_t a2);
/* Ghidra  */ void sk_trap4(long a1, uint64_t a2);
/* Ghidra  */ void sk_vsnprintf(uint64_t a1, unsigned long a2, uint64_t a3, unsigned long a4, uint64_t a5, uint64_t a6);
/* Ghidra  */ sk_u128_t sk_vspace_get_ops(void);
/* Ghidra  */ long sk_vspace_op2(void);
/* Ghidra  */ void sk_xrt_abort(uint64_t a1);
/* Ghidra  */ void sk_xrt_init(long a1);

/* Out-of-region globals (DAT_ refs). */

extern uint64_t sk_global_000;  /* Ghidra DAT_/global */
extern uint64_t sk_global_001;  /* Ghidra DAT_/global */
extern uint64_t sk_global_002;  /* Ghidra DAT_/global */
extern uint64_t sk_global_003;  /* Ghidra DAT_/global */
extern uint64_t sk_global_004;  /* Ghidra DAT_/global */
extern uint64_t sk_global_005;  /* Ghidra DAT_/global */
extern uint64_t sk_global_006;  /* Ghidra DAT_/global */
extern uint64_t sk_global_007;  /* Ghidra DAT_/global */
extern uint64_t sk_global_008;  /* Ghidra DAT_/global */
extern uint64_t sk_global_009;  /* Ghidra DAT_/global */
extern uint64_t sk_global_010;  /* Ghidra DAT_/global */
extern uint64_t sk_global_011;  /* Ghidra DAT_/global */
extern uint64_t sk_global_012;  /* Ghidra DAT_/global */
extern uint64_t sk_global_013;  /* Ghidra DAT_/global */
extern uint64_t sk_global_014;  /* Ghidra DAT_/global */
extern uint64_t sk_global_015;  /* Ghidra DAT_/global */
extern uint64_t sk_global_016;  /* Ghidra DAT_/global */
extern uint64_t sk_global_017;  /* Ghidra DAT_/global */
extern uint64_t sk_global_018;  /* Ghidra DAT_/global */
extern uint64_t sk_global_019;  /* Ghidra DAT_/global */
extern uint64_t sk_global_020;  /* Ghidra DAT_/global */
extern uint64_t sk_global_021;  /* Ghidra DAT_/global */
extern uint64_t sk_global_022;  /* Ghidra DAT_/global */
extern uint64_t sk_global_023;  /* Ghidra DAT_/global */
extern uint64_t sk_global_024;  /* Ghidra DAT_/global */
extern uint64_t sk_global_025;  /* Ghidra DAT_/global */
extern uint64_t sk_global_026;  /* Ghidra DAT_/global */
extern uint64_t sk_global_027;  /* Ghidra DAT_/global */
extern uint64_t sk_global_028;  /* Ghidra DAT_/global */
extern uint64_t sk_global_029;  /* Ghidra DAT_/global */
extern uint64_t sk_global_030;  /* Ghidra DAT_/global */
extern uint64_t sk_global_031;  /* Ghidra DAT_/global */
extern uint64_t sk_global_032;  /* Ghidra DAT_/global */
extern uint64_t sk_global_033;  /* Ghidra DAT_/global */
extern uint64_t sk_global_034;  /* Ghidra DAT_/global */
extern uint64_t sk_global_035;  /* Ghidra DAT_/global */
extern uint64_t sk_global_036;  /* Ghidra DAT_/global */
extern uint64_t sk_global_037;  /* Ghidra DAT_/global */
extern uint64_t sk_global_038;  /* Ghidra DAT_/global */
extern uint64_t sk_global_039;  /* Ghidra DAT_/global */
extern uint64_t sk_global_040;  /* Ghidra DAT_/global */
extern uint64_t sk_global_041;  /* Ghidra DAT_/global */
extern uint64_t sk_global_042;  /* Ghidra DAT_/global */
extern uint64_t sk_global_043;  /* Ghidra DAT_/global */
extern uint64_t sk_global_044;  /* Ghidra DAT_/global */
extern uint64_t sk_global_045;  /* Ghidra DAT_/global */
extern uint64_t sk_global_046;  /* Ghidra DAT_/global */
extern uint64_t sk_global_047;  /* Ghidra DAT_/global */
extern uint64_t sk_global_048;  /* Ghidra DAT_/global */
extern uint64_t sk_global_049;  /* Ghidra DAT_/global */
extern uint64_t sk_global_050;  /* Ghidra DAT_/global */
extern uint64_t sk_global_051;  /* Ghidra DAT_/global */
extern uint64_t sk_global_052;  /* Ghidra DAT_/global */
extern uint64_t sk_global_053;  /* Ghidra DAT_/global */
extern uint64_t sk_global_054;  /* Ghidra DAT_/global */
extern uint64_t sk_global_055;  /* Ghidra DAT_/global */
extern uint64_t sk_global_056;  /* Ghidra DAT_/global */
extern uint64_t sk_global_057;  /* Ghidra DAT_/global */
extern uint64_t sk_global_058;  /* Ghidra DAT_/global */
extern uint64_t sk_global_059;  /* Ghidra DAT_/global */
extern uint64_t sk_global_060;  /* Ghidra DAT_/global */
extern uint64_t sk_global_061;  /* Ghidra DAT_/global */
extern uint64_t sk_global_062;  /* Ghidra DAT_/global */
extern uint64_t sk_global_063;  /* Ghidra DAT_/global */
extern uint64_t sk_global_064;  /* Ghidra DAT_/global */
extern uint64_t sk_global_065;  /* Ghidra DAT_/global */
extern uint64_t sk_global_066;  /* Ghidra DAT_/global */
extern uint64_t sk_global_067;  /* Ghidra DAT_/global */
extern uint64_t sk_global_068;  /* Ghidra DAT_/global */
extern uint64_t sk_global_069;  /* Ghidra DAT_/global */
extern uint64_t sk_global_070;  /* Ghidra DAT_/global */
extern uint64_t sk_global_071;  /* Ghidra DAT_/global */
extern uint64_t sk_global_072;  /* Ghidra DAT_/global */
extern uint64_t sk_global_073;  /* Ghidra DAT_/global */
extern uint64_t sk_global_074;  /* Ghidra DAT_/global */
extern uint64_t sk_global_075;  /* Ghidra DAT_/global */
extern uint64_t sk_global_076;  /* Ghidra DAT_/global */
extern uint64_t sk_global_077;  /* Ghidra DAT_/global */
extern uint64_t sk_global_078;  /* Ghidra DAT_/global */
extern uint64_t sk_global_079;  /* Ghidra DAT_/global */
extern uint64_t sk_global_080;  /* Ghidra DAT_/global */
extern uint64_t sk_global_081;  /* Ghidra DAT_/global */
extern uint64_t sk_global_082;  /* Ghidra DAT_/global */
extern uint64_t sk_global_083;  /* Ghidra DAT_/global */
extern uint64_t sk_global_084;  /* Ghidra DAT_/global */
extern uint64_t sk_global_085;  /* Ghidra DAT_/global */
extern uint64_t sk_global_086;  /* Ghidra DAT_/global */
extern uint64_t sk_global_087;  /* Ghidra DAT_/global */
extern uint64_t sk_global_088;  /* Ghidra DAT_/global */
extern uint64_t sk_global_089;  /* Ghidra DAT_/global */
extern uint64_t sk_global_090;  /* Ghidra DAT_/global */
extern uint64_t sk_global_091;  /* Ghidra DAT_/global */
extern uint64_t sk_global_092;  /* Ghidra DAT_/global */
extern uint64_t sk_global_093;  /* Ghidra DAT_/global */
extern uint64_t sk_global_094;  /* Ghidra DAT_/global */
extern uint64_t sk_global_095;  /* Ghidra DAT_/global */
extern uint64_t sk_global_096;  /* Ghidra DAT_/global */
extern uint64_t sk_global_097;  /* Ghidra DAT_/global */
extern uint64_t sk_global_098;  /* Ghidra DAT_/global */
extern uint64_t sk_global_099;  /* Ghidra DAT_/global */
extern uint64_t sk_global_100;  /* Ghidra DAT_/global */
extern uint64_t sk_global_101;  /* Ghidra DAT_/global */
extern uint64_t sk_global_102;  /* Ghidra DAT_/global */
extern uint64_t sk_global_103;  /* Ghidra DAT_/global */
extern uint64_t sk_global_104;  /* Ghidra DAT_/global */
extern uint64_t sk_global_105;  /* Ghidra DAT_/global */
extern uint64_t sk_global_106;  /* Ghidra DAT_/global */
extern uint64_t sk_global_107;  /* Ghidra DAT_/global */
extern uint64_t sk_global_108;  /* Ghidra DAT_/global */
extern uint64_t sk_global_109;  /* Ghidra DAT_/global */
extern uint64_t sk_global_110;  /* Ghidra DAT_/global */
extern uint64_t sk_global_111;  /* Ghidra DAT_/global */
extern uint64_t sk_global_112;  /* Ghidra DAT_/global */
extern uint64_t sk_global_113;  /* Ghidra DAT_/global */
extern uint64_t sk_global_114;  /* Ghidra DAT_/global */
extern uint64_t sk_global_115;  /* Ghidra DAT_/global */
extern uint64_t sk_global_116;  /* Ghidra DAT_/global */
extern uint64_t sk_global_117;  /* Ghidra DAT_/global */
extern uint64_t sk_global_118;  /* Ghidra DAT_/global */

/* String literals referenced by this region (s_ labels). */

extern const char sk_str_00[];  /* Ghidra string label */
extern const char sk_str_01[];  /* Ghidra string label */
extern const char sk_str_02[];  /* Ghidra string label */
extern const char sk_str_03[];  /* Ghidra string label */
extern const char sk_str_04[];  /* Ghidra string label */
extern const char sk_str_05[];  /* Ghidra string label */
extern const char sk_str_06[];  /* Ghidra string label */
extern const char sk_str_07[];  /* Ghidra string label */
extern const char sk_str_08[];  /* Ghidra string label */
extern const char sk_str_09[];  /* Ghidra string label */
extern const char sk_str_10[];  /* Ghidra string label */
extern const char sk_str_100[];  /* Ghidra string label */
extern const char sk_str_101[];  /* Ghidra string label */
extern const char sk_str_102[];  /* Ghidra string label */
extern const char sk_str_103[];  /* Ghidra string label */
extern const char sk_str_104[];  /* Ghidra string label */
extern const char sk_str_105[];  /* Ghidra string label */
extern const char sk_str_106[];  /* Ghidra string label */
extern const char sk_str_107[];  /* Ghidra string label */
extern const char sk_str_108[];  /* Ghidra string label */
extern const char sk_str_109[];  /* Ghidra string label */
extern const char sk_str_11[];  /* Ghidra string label */
extern const char sk_str_110[];  /* Ghidra string label */
extern const char sk_str_111[];  /* Ghidra string label */
extern const char sk_str_112[];  /* Ghidra string label */
extern const char sk_str_113[];  /* Ghidra string label */
extern const char sk_str_114[];  /* Ghidra string label */
extern const char sk_str_115[];  /* Ghidra string label */
extern const char sk_str_12[];  /* Ghidra string label */
extern const char sk_str_13[];  /* Ghidra string label */
extern const char sk_str_14[];  /* Ghidra string label */
extern const char sk_str_15[];  /* Ghidra string label */
extern const char sk_str_16[];  /* Ghidra string label */
extern const char sk_str_17[];  /* Ghidra string label */
extern const char sk_str_18[];  /* Ghidra string label */
extern const char sk_str_19[];  /* Ghidra string label */
extern const char sk_str_20[];  /* Ghidra string label */
extern const char sk_str_21[];  /* Ghidra string label */
extern const char sk_str_22[];  /* Ghidra string label */
extern const char sk_str_23[];  /* Ghidra string label */
extern const char sk_str_24[];  /* Ghidra string label */
extern const char sk_str_25[];  /* Ghidra string label */
extern const char sk_str_26[];  /* Ghidra string label */
extern const char sk_str_27[];  /* Ghidra string label */
extern const char sk_str_28[];  /* Ghidra string label */
extern const char sk_str_29[];  /* Ghidra string label */
extern const char sk_str_30[];  /* Ghidra string label */
extern const char sk_str_31[];  /* Ghidra string label */
extern const char sk_str_32[];  /* Ghidra string label */
extern const char sk_str_33[];  /* Ghidra string label */
extern const char sk_str_34[];  /* Ghidra string label */
extern const char sk_str_35[];  /* Ghidra string label */
extern const char sk_str_36[];  /* Ghidra string label */
extern const char sk_str_37[];  /* Ghidra string label */
extern const char sk_str_38[];  /* Ghidra string label */
extern const char sk_str_39[];  /* Ghidra string label */
extern const char sk_str_40[];  /* Ghidra string label */
extern const char sk_str_41[];  /* Ghidra string label */
extern const char sk_str_42[];  /* Ghidra string label */
extern const char sk_str_43[];  /* Ghidra string label */
extern const char sk_str_44[];  /* Ghidra string label */
extern const char sk_str_45[];  /* Ghidra string label */
extern const char sk_str_46[];  /* Ghidra string label */
extern const char sk_str_47[];  /* Ghidra string label */
extern const char sk_str_48[];  /* Ghidra string label */
extern const char sk_str_49[];  /* Ghidra string label */
extern const char sk_str_50[];  /* Ghidra string label */
extern const char sk_str_51[];  /* Ghidra string label */
extern const char sk_str_52[];  /* Ghidra string label */
extern const char sk_str_53[];  /* Ghidra string label */
extern const char sk_str_54[];  /* Ghidra string label */
extern const char sk_str_55[];  /* Ghidra string label */
extern const char sk_str_56[];  /* Ghidra string label */
extern const char sk_str_57[];  /* Ghidra string label */
extern const char sk_str_58[];  /* Ghidra string label */
extern const char sk_str_59[];  /* Ghidra string label */
extern const char sk_str_60[];  /* Ghidra string label */
extern const char sk_str_61[];  /* Ghidra string label */
extern const char sk_str_62[];  /* Ghidra string label */
extern const char sk_str_63[];  /* Ghidra string label */
extern const char sk_str_64[];  /* Ghidra string label */
extern const char sk_str_65[];  /* Ghidra string label */
extern const char sk_str_66[];  /* Ghidra string label */
extern const char sk_str_67[];  /* Ghidra string label */
extern const char sk_str_68[];  /* Ghidra string label */
extern const char sk_str_69[];  /* Ghidra string label */
extern const char sk_str_70[];  /* Ghidra string label */
extern const char sk_str_71[];  /* Ghidra string label */
extern const char sk_str_72[];  /* Ghidra string label */
extern const char sk_str_73[];  /* Ghidra string label */
extern const char sk_str_74[];  /* Ghidra string label */
extern const char sk_str_75[];  /* Ghidra string label */
extern const char sk_str_76[];  /* Ghidra string label */
extern const char sk_str_77[];  /* Ghidra string label */
extern const char sk_str_78[];  /* Ghidra string label */
extern const char sk_str_79[];  /* Ghidra string label */
extern const char sk_str_80[];  /* Ghidra string label */
extern const char sk_str_81[];  /* Ghidra string label */
extern const char sk_str_82[];  /* Ghidra string label */
extern const char sk_str_83[];  /* Ghidra string label */
extern const char sk_str_84[];  /* Ghidra string label */
extern const char sk_str_85[];  /* Ghidra string label */
extern const char sk_str_86[];  /* Ghidra string label */
extern const char sk_str_87[];  /* Ghidra string label */
extern const char sk_str_88[];  /* Ghidra string label */
extern const char sk_str_89[];  /* Ghidra string label */
extern const char sk_str_90[];  /* Ghidra string label */
extern const char sk_str_91[];  /* Ghidra string label */
extern const char sk_str_92[];  /* Ghidra string label */
extern const char sk_str_93[];  /* Ghidra string label */
extern const char sk_str_94[];  /* Ghidra string label */
extern const char sk_str_95[];  /* Ghidra string label */
extern const char sk_str_96[];  /* Ghidra string label */
extern const char sk_str_97[];  /* Ghidra string label */
extern const char sk_str_98[];  /* Ghidra string label */
extern const char sk_str_99[];  /* Ghidra string label */

/* Forward declarations of functions defined in this region. */

void sk_sec_mem_scan(int arg1,int arg2);
void sk_sec_mem_scan2(uint64_t arg1);
long sk_ipc_send2(uint64_t arg1,unsigned long arg2);
uint64_t sk_ipc_fault(long *arg1,uint64_t *arg2,unsigned long *arg3);
void sk_ipc_scan(long *arg1);
char * sk_strnlen(char *arg1,long arg2);
uint64_t sk_ipc_msg_write(long *arg1,long arg2,unsigned short *arg3);
void sk_ipc_buf_write(long arg1,uint64_t arg2,long arg3,unsigned long arg4);
void sk_ipc_msg_read(uint64_t arg1,uint8_t arg2);
void sk_ipc_src_cap(long *arg1,long arg2,uint8_t *arg3);
uint64_t sk_ipc_src_map(long arg1,unsigned long arg2,long arg3);
uint8_t sk_ipc_cap_check(long arg1,unsigned long arg2);
unsigned long sk_sec_region_find(long arg1,unsigned long arg2);
void sk_sec_regions(unsigned int *arg1,unsigned long arg2);
unsigned long sk_macho_vmrange(long arg1);
unsigned long sk_macho_vmrange2(long arg1);
int * sk_macho_seg(long arg1,int *arg2);
unsigned long sk_macho_seg_by(uint64_t arg1,uint64_t arg2);
unsigned long sk_macho_seg_off(long arg1,uint64_t arg2);
int * sk_macho_uuid(long arg1);
void sk_macho_layout(long arg1,unsigned long *arg2,unsigned long *arg3,long *arg4);
long sk_macho_bind(unsigned long arg1,long *arg2,long arg3,long arg4,long arg5);
void sk_dump_rebasechains(void);
unsigned long sk_rebasechain_walk(long arg1,unsigned long arg2);
uint64_t sk_rebasechain_map(long arg1,unsigned long arg2,long arg3);
void sk_boot_finish(uint64_t arg1);
void sk_domain_notify(int arg1,uint64_t arg2);
void sk_init_stage(void);
void sk_init_stage2(void);
void sk_init_stage3(void);
void sk_init_stage4(void);
void sk_init_check(void);
void sk_init_result(uint64_t *arg1,uint64_t arg2);
uint64_t sk_init_result_word(uint64_t arg1);
void sk_init_cpu_region(unsigned long arg1);
uint64_t sk_exc_abort(uint64_t *arg1);
void sk_init_cnodes(void);
uint64_t sk_cpu_irq(void);
uint64_t sk_cpu_irq2(void);
uint64_t sk_cpu_irq3(void);
void sk_cpu_irq4(void);
uint64_t sk_cpu_irq5(long arg1);
uint64_t sk_cpu_irq6(void);
uint64_t sk_cpu_irq_slot(long arg1,uint64_t *arg2,uint8_t *arg3);
uint64_t sk_boot_done(void);
unsigned long sk_boot_arg(long arg1);
void sk_boot_triple(unsigned long *arg1,long *arg2,unsigned long *arg3);
void sk_boot_state(void);
unsigned long * sk_boot_list(void);
void sk_boot_putc(long arg1);
int sk_boot_puts(uint64_t arg1,unsigned long arg2,unsigned long arg3,uint64_t arg4);
uint64_t thunk_FUN_00060524(void);
bool sk_obj_cmp(long arg1,long arg2);
uint64_t sk_obj_get(unsigned long arg1);
void sk_obj_put(unsigned long arg1);
uint64_t sk_exc_entry(uint64_t *arg1);
uint64_t sk_cpu_boot_get(unsigned long arg1);
uint32_t sk_cpu_cmp(unsigned long arg1,unsigned long arg2);
void sk_cpu_start(void);
uint64_t sk_cpu_startup(uint64_t *arg1,unsigned int arg2);
void sk_cpu_init(unsigned long arg1);
uint32_t sk_cpu_ready(unsigned long arg1);
uint64_t sk_cpu_wait(unsigned long arg1);
uint64_t sk_cnode_create(unsigned long *arg1,unsigned long arg2,unsigned int arg3,int arg4,long *arg5,unsigned long arg6, unsigned int arg7);
bool sk_cnode_check(int arg1);
uint64_t sk_cnode_resolve(long arg1,long arg2,uint8_t (*arg3) [16]);
uint64_t sk_cnode_op(unsigned long arg1,unsigned long arg2,uint8_t (*arg3) [16],unsigned int arg4);
uint64_t thunk_FUN_0005fd2c(unsigned long arg1);
void sk_tcb_abort(void);
void sk_tcb_x(uint64_t arg1);
void sk_tcb_y(uint64_t arg1,uint64_t arg2);
void thunk_FUN_0006037c(void);
void sk_tcb_z(long arg1,unsigned long arg2);
unsigned long sk_tcb_w(unsigned long arg1);
void sk_tcb_v(long arg1);
unsigned long sk_cnode_find(long arg1);
void sk_cnode_cur(long arg1);
void sk_cnode_notify(int arg1);
void sk_tcb_cur(void);
uint8_t * sk_setup_cpu_regs(long arg1);
void sk_tcb_set(uint64_t arg1);
void sk_global_ensure(void);
void sk_cnode_walk(unsigned long arg1,long arg2);
void sk_cnode_map(long arg1,uint64_t arg2,long arg3,uint64_t arg4,uint64_t arg5 ,uint64_t arg6);
void sk_cnode_record(uint64_t *arg1,uint64_t arg2,uint64_t arg3,uint64_t arg4, uint64_t arg5,uint64_t arg6,uint64_t arg7,uint64_t arg8, uint64_t arg9);
uint64_t sk_cnode_get(void);
uint64_t sk_cnode_get2(void);
void sk_cnode_validate(void);
void sk_cnode_copy(unsigned long arg1);
void sk_cnode_revoke(uint64_t arg1,uint64_t arg2);
unsigned long sk_cnode_scan(void);
uint64_t sk_cnode_scan2(void);
void sk_cnode_scan3(void);
long sk_cnode_tokenize(long arg1,char *arg2,long arg3);
void sk_tcb_clear(uint64_t arg1);
uint64_t sk_tcb_get(void);
uint64_t sk_tcb_peek(void);
uint8_t sk_tcb_a(void);
void sk_tcb_b(uint64_t arg1,uint64_t arg2,uint64_t arg3);
uint8_t sk_tcb_c(void);
uint8_t sk_tcb_d(void);
uint8_t sk_tcb_e(void);
uint8_t sk_tcb_f(void);
void sk_tcb_g(uint64_t arg1);
void sk_tcb_h(uint64_t arg1);
void sk_tcb_i(uint64_t arg1,uint64_t arg2);
void sk_tcb_j(uint64_t arg1);
void sk_tcb_k(uint64_t arg1);
void sk_tcb_l(uint64_t arg1);
void sk_tcb_m(uint64_t arg1);
void sk_tcb_n(uint64_t arg1);
void sk_tcb_o(uint64_t arg1);
void sk_tcb_p(uint64_t arg1,uint64_t arg2,uint64_t arg3,uint64_t arg4);
void sk_tcb_q(uint64_t arg1,uint64_t arg2,uint64_t arg3);
void sk_tcb_r(uint64_t arg1);
void sk_tcb_s(uint64_t arg1);
void sk_tcb_t(uint64_t arg1);
void sk_tcb_u(uint64_t arg1);
uint64_t sk_tcb_v2(void);
void sk_tcb_w2(uint64_t arg1);
void sk_tcb_x2(uint64_t arg1);
void sk_tcb_y2(uint64_t arg1);
uint8_t sk_tcb_z2(void);
void sk_tcb_ab(uint64_t arg1,uint64_t arg2,uint64_t arg3);
void sk_tcb_ac(uint64_t arg1,uint64_t arg2);
void sk_tcb_ad(uint64_t arg1);
uint8_t sk_tcb_ae(void);
void sk_tcb_af(uint64_t arg1,uint64_t arg2,uint64_t arg3);
void sk_tcb_ag(uint64_t arg1,uint64_t arg2,uint64_t arg3);
void sk_tcb_ah(uint64_t arg1,uint64_t arg2);
void sk_tcb_ai(uint64_t arg1);
void sk_tcb_aj(uint64_t arg1,uint64_t arg2);
uint64_t sk_tcb_ak(unsigned int arg1);
uint64_t sk_tcb_al(unsigned int arg1);
uint64_t sk_tcb_am(unsigned int arg1);
void sk_tcb_an(void);
void sk_tcb_ao(void);
uint64_t sk_tcb_ap(void);
uint8_t sk_tcb_aq(void);
bool sk_tcb_ar(long arg1,long arg2);
void sk_tcb_as(uint64_t arg1,uint64_t arg2,uint64_t arg3,uint64_t arg4);
void sk_tcb_at(long arg1);
void sk_tcb_au(long arg1);
void sk_tcb_av(long arg1,uint64_t arg2);
bool sk_tcb_aw(long arg1,long arg2);
void sk_cap_op_a(uint64_t arg1,uint64_t arg2,uint64_t arg3,uint64_t arg4);
void sk_cap_op_b(long arg1);
void sk_cap_op_c(long arg1);
void sk_cap_op_d(long arg1);
void sk_cap_op_e(long arg1);
void sk_cap_op_f(long arg1);
void sk_cap_op_g(long arg1,uint64_t arg2);
bool sk_cap_cmp(long arg1,long arg2);
void sk_cap_op_h(uint64_t arg1,uint64_t arg2,uint64_t arg3,uint64_t arg4);
void sk_cap_op_i(long arg1);
void sk_cap_op_j(long arg1);
void sk_cap_op_k(long arg1);
void sk_cap_op_l(long arg1);
void sk_cap_op_m(long arg1);
void sk_cap_op_n(long arg1,uint64_t arg2);
bool sk_cap_cmp2(long arg1,long arg2);
void sk_cap_op_o(uint64_t arg1,uint64_t arg2,uint64_t arg3,uint64_t arg4);
void sk_cap_op_p(long arg1);
void sk_cap_op_q(long arg1);
void sk_cap_op_r(long arg1);
void sk_cap_op_s(long arg1);
void sk_cap_op_t(long arg1);
void sk_cap_op_u(long arg1,uint64_t arg2);
bool sk_cap_cmp3(long arg1,long arg2);
void sk_cap_op_v(uint64_t arg1,uint64_t arg2,uint64_t arg3,uint64_t arg4);
void sk_cap_op_w(long arg1);
void sk_cap_op_x(long arg1);
void sk_cap_op_y(long arg1);
void sk_cap_op_z(long arg1);
void sk_cap_op_aa(long arg1);
void sk_cap_op_ab(long arg1,uint64_t arg2);
bool sk_cap_cmp4(long arg1,long arg2);
void sk_cap_op_ac(uint64_t arg1,uint64_t arg2,uint64_t arg3,uint64_t arg4);
void sk_cap_op_ad(long arg1);
void sk_cap_op_ae(long arg1);
void sk_cap_op_af(long arg1);
void sk_cap_op_ag(long arg1);
void sk_cap_op_ah(long arg1);
void sk_cap_op_ai(long arg1,uint64_t arg2);
bool sk_cap_cmp5(long arg1,long arg2);
void sk_cap_op_aj(uint64_t arg1,uint64_t arg2,uint64_t arg3,uint64_t arg4);
void sk_cap_op_ak(long arg1);
void sk_cap_op_al(long arg1);
void sk_cap_op_am(long arg1);
void sk_cap_op_an(long arg1);
void sk_cap_op_ao(long arg1);
void sk_cap_op_ap(long arg1,uint64_t arg2);
bool sk_cap_cmp6(long arg1,long arg2);
void sk_cap_op_aq(uint64_t arg1,uint64_t arg2,uint64_t arg3,uint64_t arg4);
void sk_cap_op_ar(long arg1);
void sk_cap_op_as(long arg1);
void sk_cap_op_at(long arg1);
void sk_cap_op_au(long arg1);
void sk_cap_op_av(long arg1);
void sk_cap_op_aw(long arg1,uint64_t arg2);
bool sk_cap_cmp7(long arg1,long arg2);
void sk_cap_op_ax(uint64_t arg1,uint64_t arg2,uint64_t arg3,uint64_t arg4);
void sk_cap_op_ay(long arg1);
void sk_cap_op_az(long arg1);
void sk_cap_op_ba(long arg1);
void sk_cap_op_bb(long arg1);
void sk_cap_op_bc(long arg1);
void sk_cap_op_bd(long arg1,uint64_t arg2);
bool sk_cap_cmp8(long arg1,long arg2);
void svc_dispatch_3arg(uint64_t arg1,uint64_t arg2,uint64_t arg3,uint64_t arg4);
void svc_repeat_on_suspend_1(long arg1);
void svc_repeat_on_suspend_2(long arg1);
void svc_repeat_on_suspend_3(long arg1);
void svc_repeat_on_suspend_4(long arg1);
void svc_repeat_on_suspend_5(long arg1);
void svc_set_arg_repeat_on_suspend(long arg1,uint64_t arg2);
bool fill_cap_dispatch_table(long arg1,long arg2);
void svc_dispatch_3arg_b(uint64_t arg1,uint64_t arg2,uint64_t arg3,uint64_t arg4);
void svc_repeat_on_suspend_6(long arg1);
void svc_repeat_on_suspend_7(long arg1);
void svc_repeat_on_suspend_8(long arg1);
void svc_repeat_on_suspend_9(long arg1);
void svc_repeat_on_suspend_10(long arg1);
void svc_set_arg_repeat_on_suspend_b(long arg1,uint64_t arg2);
void sk_syscall_boot(void);
void thunk_FUN_000558c0(uint64_t arg1,uint64_t arg2,uint64_t arg3);
uint32_t sk_error_register(unsigned long arg1,unsigned int arg2);
unsigned long sk_error_get(void);
void sk_global_get(long *arg1,uint64_t arg2,uint64_t arg3);
void sk_error_clear(void);
uint64_t sk_error_status(void);
void sk_error_reset(void);
void sk_error_set(long arg1);
void sk_error_emit(uint64_t arg1,long arg2,uint64_t arg3,int arg4);
void sk_error_fmt(long arg1,uint64_t arg2,uint64_t arg3);
void sk_error_release(long arg1,uint64_t arg2);
void sk_error_broadcast(long arg1);
void sk_error_cpu(uint64_t arg1);
void sk_error_cpu2(uint64_t arg1);
void sk_error_sync(void);
uint64_t sk_error_flag(void);
void sk_panic_msg(uint64_t arg1,uint64_t arg2);
void sk_panic(unsigned long arg1,uint64_t arg2,uint64_t arg3);
void sk_format_vsnprintf(uint64_t arg1,uint64_t arg2,uint64_t arg3,uint64_t arg4);
uint64_t sk_kernel_state_get(uint64_t *arg1);
uint64_t sk_kernel_field_40(void);
void sk_format_uuid(void);
uint64_t sk_kernel_head(void);
void sk_register_global_3(uint64_t arg1);
void sk_register_global(long *arg1);
long sk_lookup_thread_obj(int arg1,int arg2);
void sk_list_push(unsigned long *arg1);
void sk_kernel_get(void);
unsigned long * sk_list_head(void);
unsigned long sk_strtok(long arg1,long *arg2);
void sk_range_lookup(unsigned long *arg1,int arg2);
void sk_register_cb(long arg1);
void sk_list_push_28(unsigned long *arg1);
void sk_iter_list_cb(sk_code_t arg1,uint64_t arg2);
void sk_kernel_set_70(uint64_t arg1,uint64_t arg2);
void sk_waitq_enqueue(unsigned long *arg1,int arg2);
void sk_waitq_dequeue(unsigned long *arg1);
void sk_waitq_dequeue_all(void);
void sk_register_global_2(void);
unsigned long sk_log_append(uint64_t arg1,unsigned long arg2);
unsigned long sk_log_consume(unsigned long arg1,unsigned long arg2);
void sk_dispatch_reset2(void);
void sk_dispatch_reset3(void);
void sk_dispatch_reset4(void);
void sk_dispatch_reset5(void);
void sk_dispatch_reset6(void);
void sk_dispatch_reset7(void);
void sk_dispatch_reset8(void);
void sk_dispatch_reset9(void);
void sk_dispatch_reset10(void);
void sk_dispatch_reset11(void);
void sk_dispatch_reset12(void);
void sk_dispatch_reset13(void);
void sk_dispatch_error_print(void);
void sk_dispatch_default(void);
long sk_cap_word_lookup(uint64_t arg1);
void sk_method_handle(uint64_t arg1);
void sk_error_from_code(uint64_t *out, unsigned long code);
void sk_dispatch_reset(void);
void sk_dispatch_record(unsigned long arg1,long arg2);
long sk_error_classify(uint64_t arg1,uint8_t (*arg2) [16],uint8_t (*arg3) [16], unsigned long arg4);
long sk_error_to_word(uint64_t arg1);
uint64_t sk_errno_name(unsigned int arg1);
void sk_set_cap_class(uint8_t arg1);
void sk_cap_record(uint64_t arg1,unsigned long arg2,uint8_t (*arg3) [16],unsigned long arg4);
uint64_t sk_lock_prepare(unsigned long *arg1);
uint64_t sk_lock_acquire_recursive(unsigned long *arg1,uint64_t arg2);
uint64_t sk_lock_try(unsigned long *arg1);
void sk_unlock(uint64_t *arg1);
void sk_lock_set_mode(uint64_t *arg1,uint16_t arg2);
void sk_lock_init(void);
void sk_lock_record(long arg1,uint64_t arg2,uint64_t arg3);
void sk_notify_domain(long arg1,uint64_t arg2);
void sk_notify_domain_slot(long *arg1,unsigned long arg2);
uint64_t sk_cap_lookup_slot(long arg1);
uint64_t sk_cap_resolve_name(long arg1,long *arg2);
unsigned short sk_lock_acquire(unsigned long *arg1,uint64_t arg2);
void sk_lock_release(unsigned long *arg1,int arg2);
void sk_register_cb2(unsigned int *arg1,sk_code_t arg2,uint64_t arg3);
void sk_msg_init(void);
void sk_msg_send2(uint64_t arg1,unsigned int arg2,uint64_t arg3,uint64_t arg4);
void sk_msg_send(long arg1,uint16_t arg2,uint64_t *arg3,unsigned long arg4);
uint64_t sk_ipc_retrieve(void);
void sk_msg_push(long *arg1);
void sk_msg_pop(void);
void sk_msg_print(long arg1,int arg2);
uint64_t sk_ipc_call_guard(sk_code_t arg1,unsigned long arg2,uint8_t *arg3,uint64_t arg4);
void sk_msg_release(long arg1);
uint64_t thunk_FUN_00061638(long arg1);
uint64_t sk_cpu_array(unsigned long arg1);
void sk_lock_dispatch_10(void);
void sk_lock_release_recursive(unsigned int arg1,uint64_t arg2,uint64_t arg3,long arg4,unsigned int arg5);
void sk_lock_dispatch_18(void);
void sk_lock_release_recursive2(unsigned int arg1,uint64_t arg2,unsigned int arg3,unsigned long arg4);
void sk_ipc_begin(void);
void sk_ipc_end(uint64_t arg1);
void sk_ipc_set(unsigned int arg1);
sk_u128_t sk_ipc_msg_frame(unsigned long arg1, unsigned short *msg);
void sk_syscall_entry(void);
void sk_syscall_handler(unsigned long arg1,uint8_t *arg2);
void sk_syscall_exit(uint8_t arg1);
void sk_syscall_restore(void);
void sk_syscall_print(long arg1,uint64_t arg2,uint64_t arg3,unsigned long arg4);
void sk_buf_advance(unsigned long *arg1,unsigned long arg2,uint64_t arg3);
uint64_t sk_syscall_name(uint32_t arg1);
long sk_syscall_table_lookup(uint64_t arg1,unsigned long arg2,unsigned long arg3,unsigned int arg4);
long sk_syscall_table_lookup2(unsigned long arg1,unsigned long arg2,unsigned long arg3);
void sk_syscall_set_table(unsigned int arg1,uint64_t arg2);
unsigned long sk_syscall_get_table(unsigned int arg1);
void sk_syscall_set_handlers(unsigned int arg1,uint64_t arg2);
void sk_syscall_set_handlers2(unsigned int arg1,uint64_t arg2);
unsigned long sk_shift_0(unsigned long arg1);
unsigned long sk_shift_1(unsigned long arg1);
unsigned long sk_shift_2(unsigned long arg1);
unsigned long sk_shift_multi(unsigned long arg1,unsigned long arg2,unsigned int arg3,int arg4);
void sk_shift_dispatch(void);
void sk_syscall_cap_dispatch(unsigned long *arg1,uint64_t arg2,unsigned long arg3,long arg4,int arg5);
void sk_restore_ctx(long arg1);
void sk_restore_ctx1(uint64_t arg1);
void sk_restore_ctx2(long arg1);
void sk_save_ctx(uint64_t arg1,uint64_t arg2,long arg3);
void sk_save_ctx2(uint64_t arg1,uint64_t *arg2,uint64_t arg3);
void sk_restore_ctx3(long arg1);
void sk_restore_ctx4(long arg1);
uint64_t sk_current_cpu(unsigned long arg1);
long sk_cpu_state_check(long arg1,uint64_t arg2);
void sk_state_enter(void);
void sk_state_exit(void);
void sk_alloc_frame(uint64_t *arg1,unsigned long arg2,unsigned int arg3);


/* FUN_000501cc @ 0x501cc   (est. sk_sec_mem_scan)
 * Ghidra: void FUN_000501cc(int arg1,int arg2)
 * sk_sec_mem_scan: cL4 sk sec mem scan operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_sec_mem_scan(int arg1,int arg2)
{
  unsigned long t3;
  sk_code_t t0;
  long *t1;
  unsigned long t4;
  unsigned short *t2;
  unsigned int t5;
  unsigned long t6;
  unsigned long t7;
  unsigned long stk1 [2];
  uint8_t stk0 [16];
  
  t1 = (long *)sk_kernel_head();
  t4 = sk_msg_capacity();
  if ((t4 != 0) && (t4 + 8 < t4)) {
LAB_00050440:
                    
    t0 = (sk_code_t )sk_break(0x5519,0x50444);
    (*t0)();
  }
  stk0 = sk_msg_zero();
  do {
    if (t1 == (long *)0x0) {
      return;
    }
    if (*(char *)(t1 + 1) < '\0') {
      t6 = t1[7];
      stk1[1] = 0;
      stk1[0] = t4;
      t2 = (unsigned short *)sk_msg_iter(stk1);
      if (t2 != (unsigned short *)0x0) {
        t3 = t6 + 0x20;
        do {
          if (t2 + 6 < t2) goto LAB_00050440;
          t7 = (unsigned long)(uint8_t)t2[3] << 0x10 | (unsigned long)*(uint8_t *)((long)t2 + 7) << 0x18 |
                  (unsigned long)t2[2] |
                  (unsigned long)((unsigned int)(uint8_t)t2[5] << 0x10 |
                          (unsigned int)*(uint8_t *)((long)t2 + 0xb) << 0x18 | (unsigned int)t2[4]) << 0x20;
          t5 = (unsigned int)(uint8_t)t2[1] << 0x10 | (unsigned int)*(uint8_t *)((long)t2 + 3) << 0x18 |
                  (unsigned int)*t2;
          if ((arg2 != 0) && (t5 == 0)) {
            if (t3 < t6) goto LAB_00050440;
            sk_msg_record(t4,t2,stk0,t6,t1[4],sk_str_60);
            if (t7 < ((unsigned long)(uint8_t)t2[3] << 0x10 | (unsigned long)*(uint8_t *)((long)t2 + 7) << 0x18
                         | (unsigned long)t2[2] |
                        (unsigned long)((unsigned int)(uint8_t)t2[5] << 0x10 |
                                (unsigned int)*(uint8_t *)((long)t2 + 0xb) << 0x18 | (unsigned int)t2[4]) <<
                        0x20)) goto LAB_00050440;
            t5 = (unsigned int)(uint8_t)t2[1] << 0x10 | (unsigned int)*(uint8_t *)((long)t2 + 3) << 0x18 |
                    (unsigned int)*t2;
          }
          if (t5 != 0) {
            if (arg1 != 0) {
              if (t3 < t6) goto LAB_00050440;
              sk_msg_record(t4,t2,stk0,t6,t1[4],sk_str_64);
            }
            if ((t7 < ((unsigned long)(uint8_t)t2[3] << 0x10 |
                          (unsigned long)*(uint8_t *)((long)t2 + 7) << 0x18 | (unsigned long)t2[2] |
                         (unsigned long)((unsigned int)(uint8_t)t2[5] << 0x10 |
                                 (unsigned int)*(uint8_t *)((long)t2 + 0xb) << 0x18 | (unsigned int)t2[4]) <<
                         0x20)) || (t3 < t6)) goto LAB_00050440;
            sk_msg_record(t4,t2,stk0,t6,t1[4],sk_str_60);
          }
          t2 = (unsigned short *)sk_msg_iter(stk1);
        } while (t2 != (unsigned short *)0x0);
      }
    }
    t1 = (long *)*t1;
  } while( true );
}




/* FUN_00050444 @ 0x50444   (est. sk_sec_mem_scan2)
 * Ghidra: void FUN_00050444(undefined8 arg1)
 * sk_sec_mem_scan2: cL4 sk sec mem scan2 operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_sec_mem_scan2(uint64_t arg1)
{
  uint8_t t0;
  uint8_t t2;
  unsigned short t8;
  unsigned short t9;
  unsigned short t10;
  unsigned short t11;
  sk_code_t t5;
  unsigned long t12;
  unsigned short *t7;
  long t3;
  unsigned short *t6;
  bool t1;
  long t4;
  unsigned long stk0 [2];
  
  t12 = sk_msg_capacity();
  if ((t12 != 0) && (t12 + 8 < t12)) {
LAB_00050650:
                    
    t5 = (sk_code_t )sk_break(0x5519,0x50654);
    (*t5)();
  }
  stk0[1] = 0;
  stk0[0] = t12;
  t7 = (unsigned short *)sk_msg_iter(stk0);
  if (t7 != (unsigned short *)0x0) {
    t1 = false;
    do {
      if (t7 + 6 < t7) goto LAB_00050650;
      if (((unsigned int)(uint8_t)t7[1] << 0x10 | (unsigned int)*(uint8_t *)((long)t7 + 3) << 0x18 | (unsigned int)*t7
          ) == 0xb) {
        t8 = t7[2];
        t0 = *(uint8_t *)((long)t7 + 7);
        t10 = t7[3];
        t9 = t7[4];
        t2 = *(uint8_t *)((long)t7 + 0xb);
        t11 = t7[5];
        t3 = sk_msg_count(t7);
        if (t3 != 0) {
          t4 = 0;
          do {
            if (((unsigned long)(uint8_t)t10 << 0x10 | (unsigned long)t0 << 0x18 | (unsigned long)t8 |
                (unsigned long)((unsigned int)(uint8_t)t11 << 0x10 | (unsigned int)t2 << 0x18 | (unsigned int)t9) << 0x20) <
                ((unsigned long)(uint8_t)t7[3] << 0x10 | (unsigned long)*(uint8_t *)((long)t7 + 7) << 0x18 |
                 (unsigned long)t7[2] |
                (unsigned long)((unsigned int)(uint8_t)t7[5] << 0x10 | (unsigned int)*(uint8_t *)((long)t7 + 0xb) << 0x18
                       | (unsigned int)t7[4]) << 0x20)) goto LAB_00050650;
            t6 = (unsigned short *)sk_msg_get(t7,t4);
            sk_notify_domain((unsigned long)(uint8_t)t6[1] << 0x10 |
                         (unsigned long)*(uint8_t *)((long)t6 + 3) << 0x18 | (unsigned long)*t6 |
                         (unsigned long)((unsigned int)(uint8_t)t6[3] << 0x10 |
                                 (unsigned int)*(uint8_t *)((long)t6 + 7) << 0x18 | (unsigned int)t6[2]) <<
                         0x20,arg1);
            t4 = t4 + 1;
          } while (t3 != t4);
        }
        t1 = true;
      }
      t7 = (unsigned short *)sk_msg_iter(stk0);
    } while (t7 != (unsigned short *)0x0);
    if (t1) {
      return;
    }
  }
  sk_notify_domain(0x706c6174,arg1);
  return;
}




/* FUN_00050654 @ 0x50654   (est. sk_ipc_send2)
 * Ghidra: long FUN_00050654(undefined8 arg1,ulong arg2)
 * sk_ipc_send2: cL4 sk ipc send2 operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

long sk_ipc_send2(uint64_t arg1,unsigned long arg2)
{
  sk_code_t t0;
  short *psVar2;
  unsigned short *t1;
  unsigned long t2;
  unsigned long t3;
  uint8_t stk0 [16];
  uint64_t stk1;
  uint64_t stk2;
  
  stk0 = sk_msg_zero();
  stk2 = 0;
  stk1 = arg1;
  psVar2 = (short *)sk_msg_iter(&stk1);
  do {
    if (psVar2 == (short *)0x0) {
      return 0;
    }
    if (psVar2 + 6 < psVar2) {
                    
      t0 = (sk_code_t )sk_break(0x5519,0x5082c);
      (*t0)();
    }
    if ((((char)psVar2[1] == '\0' && *(char *)((long)psVar2 + 3) == '\0') && *psVar2 == 0) &&
       (t2 = (unsigned long)*(uint8_t *)(psVar2 + 3) << 0x10 | (unsigned long)*(uint8_t *)((long)psVar2 + 7) << 0x18 |
                (unsigned long)(unsigned short)psVar2[2] |
                (unsigned long)((unsigned int)*(uint8_t *)(psVar2 + 5) << 0x10 |
                        (unsigned int)*(uint8_t *)((long)psVar2 + 0xb) << 0x18 | (unsigned int)(unsigned short)psVar2[4]) <<
                0x20, 0x10f < t2)) {
      t3 = 0;
      do {
        t1 = (unsigned short *)sk_msg_get(psVar2,t3);
        if (((unsigned long)(uint8_t)t1[1] << 0x10 | (unsigned long)*(uint8_t *)((long)t1 + 3) << 0x18 |
             (unsigned long)*t1 |
            (unsigned long)((unsigned int)(uint8_t)t1[3] << 0x10 | (unsigned int)*(uint8_t *)((long)t1 + 7) << 0x18 |
                   (unsigned int)t1[2]) << 0x20) == arg2) {
          if (*(uint8_t *)((long)t1 + 0x10f) >> 2 != 0) {
                    
            sk_abort_msg(sk_str_92);
          }
          t2 = (unsigned long)(uint8_t)t1[0x85] << 0x10 | (unsigned long)*(uint8_t *)((long)t1 + 0x10b) << 0x18
                  | (unsigned long)t1[0x84] |
                  (unsigned long)((unsigned int)(uint8_t)t1[0x87] << 0x10 |
                          (unsigned int)*(uint8_t *)((long)t1 + 0x10f) << 0x18 | (unsigned int)t1[0x86]) <<
                  0x20;
          if (t2 << 6 < stk0._8_8_) {
            return stk0._0_8_ + t2 * 0x40;
          }
          return 0;
        }
        t3 = t3 + 1;
      } while (t3 < t2 / 0x110);
    }
    psVar2 = (short *)sk_msg_iter(&stk1);
  } while( true );
}




/* FUN_00050838 @ 0x50838   (est. sk_ipc_fault)
 * Ghidra: undefined8 FUN_00050838(long *arg1,undefined8 *arg2,ulong *arg3)
 * sk_ipc_fault: cL4 sk ipc fault operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

uint64_t sk_ipc_fault(long *arg1,uint64_t *arg2,unsigned long *arg3)
{
  sk_code_t t0;
  uint64_t t1;
  uint8_t *stk0;
  
  stk0 = &sk_global_042;
  sk_register_cb2(0x6af880,sk_ipc_scan,&stk0);
  t1 = sk_global_059;
  if ((sk_global_058 == 0) || (sk_global_060 == 0)) {
    t1 = 0;
  }
  else {
    *arg1 = sk_global_058;
    *arg2 = t1;
    if ((sk_global_060 != 0 && sk_global_060 + 8 <= sk_global_060) &&
        (sk_global_060 == 0 || sk_global_060 != sk_global_060 + 8)) {
                    
      t0 = (sk_code_t )sk_break(0x5519,0x508e8);
      (*t0)();
    }
    *arg3 = sk_global_060;
    t1 = 1;
  }
  return t1;
}




/* FUN_000508e8 @ 0x508e8   (est. sk_ipc_scan)
 * Ghidra: void FUN_000508e8(long *arg1)
 * sk_ipc_scan: cL4 sk ipc scan operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_ipc_scan(long *arg1)
{
  long t2;
  uint8_t t0;
  uint8_t t8;
  uint8_t t1;
  unsigned short t9;
  unsigned short t10;
  unsigned short t11;
  unsigned short t12;
  sk_code_t t3;
  unsigned long t6;
  unsigned short *t4;
  unsigned long *t5;
  unsigned long t7;
  uint8_t stk0 [16];
  uint8_t stk1 [16];
  uint64_t stk7;
  long stk6;
  uint8_t stk5 [8];
  unsigned long stk4;
  unsigned long stk3;
  uint64_t stk8;
  unsigned long stk2 [2];
  
  if (arg1 == (long *)0x0) {
    return;
  }
  stk0 = sk_msg_zero();
  t6 = sk_msg_capacity();
  if ((t6 == 0) || (t6 <= t6 + 8)) {
    stk2[1] = 0;
    stk2[0] = t6;
    do {
      t4 = (unsigned short *)sk_msg_iter(stk2);
      if (t4 == (unsigned short *)0x0) {
        return;
      }
      if (t4 + 6 < t4) goto LAB_00050c80;
    } while (((unsigned int)(uint8_t)t4[1] << 0x10 | (unsigned int)*(uint8_t *)((long)t4 + 3) << 0x18 |
             (unsigned int)*t4) != 10);
    if (0x17 < ((unsigned long)(uint8_t)t4[3] << 0x10 | (unsigned long)*(uint8_t *)((long)t4 + 7) << 0x18 |
                (unsigned long)t4[2] |
               (unsigned long)((unsigned int)(uint8_t)t4[5] << 0x10 | (unsigned int)*(uint8_t *)((long)t4 + 0xb) << 0x18
                      | (unsigned int)t4[4]) << 0x20) - 0x18) {
      sk_log_str(sk_str_68);
    }
    t4 = (unsigned short *)sk_msg_get(t4,0);
    t10 = t4[8];
    t9 = t4[10];
    t0 = *(uint8_t *)((long)t4 + 0x17);
    t11 = t4[0xb];
    if (t0 >> 2 != 0) {
                    
      sk_abort_msg(sk_str_92);
    }
    t8 = *(uint8_t *)((long)t4 + 0x11);
    t1 = *(uint8_t *)((long)t4 + 0x13);
    t12 = t4[9];
    t7 = ((unsigned long)(uint8_t)t4[1] << 0x10 | (unsigned long)*(uint8_t *)((long)t4 + 3) << 0x18 |
              (unsigned long)*t4 |
             (unsigned long)((unsigned int)(uint8_t)t4[3] << 0x10 | (unsigned int)*(uint8_t *)((long)t4 + 7) << 0x18 |
                    (unsigned int)t4[2]) << 0x20) + 0x3fff +
             ((unsigned long)(uint8_t)t4[5] << 0x10 | (unsigned long)*(uint8_t *)((long)t4 + 0xb) << 0x18 |
              (unsigned long)t4[4] |
             (unsigned long)((unsigned int)(uint8_t)t4[7] << 0x10 | (unsigned int)*(uint8_t *)((long)t4 + 0xf) << 0x18 |
                    (unsigned int)t4[6]) << 0x20) & 0xffffffffffffc000;
    stk5[0] = 0x11;
    sk_memset((unsigned long)stk5 | 1,0xf);
    stk8 = 0xf;
    stk7 = 0;
    stk6 = 0;
    stk3 = t7;
    stk1 = sk_vspace_get_ops();
    t6 = (**(sk_code_t *)(stk1._8_8_ + 0x30))(stk1._0_8_,0x1800,stk5,&stk7,0,0);
    t6 = t6 & 0xff;
    if (t6 == 0) {
      t6 = (unsigned long)(uint8_t)t12 << 0x10 | (unsigned long)t1 << 0x18 |
               (unsigned long)CONCAT11(t8,(char)t10) |
               (unsigned long)((unsigned int)(uint8_t)t11 << 0x10 | (unsigned int)t0 << 0x18 | (unsigned int)t9) << 0x20;
      t2 = stk0._0_8_ + t6 * 0x40;
      if (stk0._8_8_ <= t6 << 6) {
        t2 = 0;
      }
      sk_ipc_buf_write(t2,stk7,stk6,t7);
      if (stk6 == 0) {
                    
        sk_tcb_abort();
      }
      (**(sk_code_t *)(stk6 + 8))(stk7,stk5);
      t6 = (unsigned long)(uint8_t)t4[1] << 0x10 | (unsigned long)*(uint8_t *)((long)t4 + 3) << 0x18 |
               (unsigned long)*t4 |
               (unsigned long)((unsigned int)(uint8_t)t4[3] << 0x10 | (unsigned int)*(uint8_t *)((long)t4 + 7) << 0x18 |
                      (unsigned int)t4[2]) << 0x20;
      if (stk4 <= stk4 + t6) {
        t5 = (unsigned long *)*arg1;
        *t5 = stk4;
        t5[1] = t6;
        stk4 = stk4 + t6;
        if ((stk4 == 0) || (stk4 <= stk4 + 8)) {
          t5[2] = stk4;
          return;
        }
      }
    }
    else if ((((uint64_t *)0x64cb3f < &sk_global_034 + t6) &&
             (&sk_global_035 + t6 < (uint64_t *)0x64cb81)) &&
            (&sk_global_034 + t6 <= &sk_global_035 + t6)) {
                    
      sk_panic_msg(0,sk_str_06);
    }
  }
LAB_00050c80:
                    
  t3 = (sk_code_t )sk_break(0x5519,0x50c84);
  (*t3)();
}




/* FUN_00050c88 @ 0x50c88   (est. sk_strnlen)
 * Ghidra: char * FUN_00050c88(char *arg1,long arg2)
 * sk_strnlen: cL4 sk strnlen operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

char * sk_strnlen(char *arg1,long arg2)
{
  char t0;
  char *t2;
  sk_code_t t3;
  long t1;
  
  t1 = sk_strlen();
  if (t1 == arg2) {
    arg1 = (char *)0x0;
  }
  else {
    if (arg2 == 0) {
LAB_00050ce4:
                    
      t3 = (sk_code_t )sk_break(0x5519,0x50ce8);
      (*t3)();
    }
    t2 = arg1;
    do {
      if (arg1 + arg2 < t2 + 1) goto LAB_00050ce4;
      t0 = *t2;
      t2 = t2 + 1;
    } while (t0 != '\0');
  }
  return arg1;
}




/* FUN_00050ce8 @ 0x50ce8   (est. sk_ipc_msg_write)
 * Ghidra: undefined8 FUN_00050ce8(long *arg1,long arg2,ushort *arg3)
 * sk_ipc_msg_write: cL4 sk ipc msg write operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

uint64_t sk_ipc_msg_write(long *arg1,long arg2,unsigned short *arg3)
{
  unsigned short *t10;
  uint8_t t20;
  uint8_t t2;
  uint8_t t3;
  uint8_t t4;
  uint8_t t5;
  uint8_t t26;
  uint8_t t27;
  uint8_t t28;
  uint8_t t12;
  uint8_t t13;
  uint8_t t14;
  uint8_t t15;
  uint8_t t0;
  uint8_t t16;
  uint8_t t1;
  unsigned short t17;
  unsigned short t18;
  unsigned short t19;
  unsigned short t21;
  unsigned short t22;
  unsigned short t23;
  sk_code_t t9;
  char t6;
  int t7;
  unsigned short *t11;
  unsigned long t24;
  unsigned long t25;
  long t8;
  uint8_t stk0 [16];
  uint8_t stk5 [8];
  long stk4;
  unsigned long stk3;
  uint64_t stk6;
  uint64_t stk2;
  long stk1;
  
  if (*(uint8_t *)(arg2 + 0x117) >> 2 != 0) {
                    
    sk_abort_msg(sk_str_92);
  }
  t10 = arg3 + 0xc0;
  t21 = arg3[0xc2];
  t20 = *(uint8_t *)(arg2 + 0x104);
  t17 = *(unsigned short *)(arg2 + 0x108);
  t2 = *(uint8_t *)(arg2 + 0x10b);
  t3 = *(uint8_t *)(arg2 + 0x10a);
  t19 = *(unsigned short *)(arg2 + 0x10c);
  t4 = *(uint8_t *)(arg2 + 0x10f);
  t5 = *(uint8_t *)(arg2 + 0x10e);
  t25 = (unsigned long)t3 << 0x10 | (unsigned long)t2 << 0x18 | (unsigned long)t17 |
           (unsigned long)((unsigned int)t5 << 0x10 | (unsigned int)t4 << 0x18 | (unsigned int)t19) << 0x20;
  t24 = ((unsigned long)*(uint8_t *)(arg2 + 0x112) << 0x10 | (unsigned long)*(uint8_t *)(arg2 + 0x113) << 0x18 |
            (unsigned long)*(unsigned short *)(arg2 + 0x110) |
           (unsigned long)((unsigned int)*(uint8_t *)(arg2 + 0x116) << 0x10 |
                   (unsigned int)*(uint8_t *)(arg2 + 0x117) << 0x18 | (unsigned int)*(unsigned short *)(arg2 + 0x114)) <<
           0x20) * 0x40;
  if (t24 < (unsigned long)arg1[1]) {
    t8 = t24 + *arg1;
  }
  else {
    t8 = 0;
  }
  t26 = *(uint8_t *)(arg2 + 0x102);
  t27 = *(uint8_t *)(arg2 + 0x106);
  t22 = arg3[0xc1];
  t23 = arg3[0xc3];
  t28 = *(uint8_t *)(arg2 + 0x101);
  t12 = *(uint8_t *)(arg2 + 0x100);
  t13 = *(uint8_t *)(arg2 + 0x103);
  t14 = *(uint8_t *)(arg2 + 0x105);
  t15 = *(uint8_t *)(arg2 + 0x107);
  t18 = arg3[0xc0];
  t0 = *(uint8_t *)((long)arg3 + 0x183);
  t16 = *(uint8_t *)((long)arg3 + 0x185);
  t1 = *(uint8_t *)((long)arg3 + 0x187);
  t7 = sk_strcmp(arg2,sk_str_58,0x100);
  if (t7 != 0) {
    stk2 = 0;
    stk1 = 0;
    stk5[0] = 0x11;
    sk_memset((unsigned long)stk5 | 1,0xf);
    stk6 = 9;
    stk3 = t25;
    stk0 = sk_vspace_get_ops();
    t6 = (**(sk_code_t *)(stk0._8_8_ + 0x30))(stk0._0_8_,0x1a08,stk5,&stk2,0,0);
    if (t6 != '\0') {
      return 0;
    }
    sk_ipc_buf_write(t8,stk2,stk1,t25);
    if (stk1 == 0) {
                    
      sk_tcb_abort();
    }
    (**(sk_code_t *)(stk1 + 8))(stk2,stk5);
    t8 = stk4;
  }
  t11 = arg3 + ((unsigned long)(uint8_t)t22 << 0x10 | (unsigned long)t0 << 0x18 | (unsigned long)t18 |
                      (unsigned long)((unsigned int)(uint8_t)t23 << 0x10 | (unsigned int)t1 << 0x18 |
                             (unsigned int)CONCAT11(t16,(char)t21)) << 0x20) * 0xc;
  if (((arg3 <= t11) && (t11 + 0xc <= t10)) && (t11 <= t11 + 0xc)) {
    *(char *)((long)t11 + 0x15) = (char)((unsigned long)t8 >> 0x28);
    *(char *)(t11 + 8) = (char)t8;
    *(char *)((long)t11 + 0x13) = (char)((unsigned long)t8 >> 0x18);
    *(char *)(t11 + 9) = (char)((unsigned long)t8 >> 0x10);
    *(char *)((long)t11 + 0x11) = (char)((unsigned long)t8 >> 8);
    *(char *)(t11 + 10) = (char)((unsigned long)t8 >> 0x20);
    *(char *)((long)t11 + 0x17) = (char)((unsigned long)t8 >> 0x38);
    *(char *)(t11 + 0xb) = (char)((unsigned long)t8 >> 0x30);
    *(char *)((long)t11 + 0xd) = (char)(t19 >> 8);
    *(char *)(t11 + 4) = (char)t17;
    *(uint8_t *)((long)t11 + 0xb) = t2;
    *(uint8_t *)(t11 + 5) = t3;
    *(char *)((long)t11 + 9) = (char)(t17 >> 8);
    *(char *)(t11 + 6) = (char)t19;
    *(uint8_t *)((long)t11 + 0xf) = t4;
    *(uint8_t *)(t11 + 7) = t5;
    *(uint8_t *)t11 = t12;
    *(uint8_t *)((long)t11 + 5) = t14;
    *(uint8_t *)((long)t11 + 3) = t13;
    *(uint8_t *)(t11 + 1) = t26;
    *(uint8_t *)((long)t11 + 1) = t28;
    *(uint8_t *)(t11 + 2) = t20;
    *(uint8_t *)((long)t11 + 7) = t15;
    *(uint8_t *)(t11 + 3) = t27;
    t8 = ((unsigned long)(uint8_t)arg3[0xc1] << 0x10 | (unsigned long)*(uint8_t *)((long)arg3 + 0x183) << 0x18 |
              (unsigned long)*t10 |
             (unsigned long)((unsigned int)(uint8_t)arg3[0xc3] << 0x10 |
                     (unsigned int)*(uint8_t *)((long)arg3 + 0x187) << 0x18 | (unsigned int)arg3[0xc2]) << 0x20)
             + 1;
    *(char *)t10 = (char)t8;
    *(uint8_t *)(arg3 + 0xc3) = (uint8_t)((unsigned long)t8 >> 0x30);
    *(char *)((long)arg3 + 0x187) = (char)((unsigned long)t8 >> 0x38);
    *(char *)(arg3 + 0xc2) = (char)((unsigned long)t8 >> 0x20);
    *(char *)((long)arg3 + 0x185) = (char)((unsigned long)t8 >> 0x28);
    *(uint8_t *)(arg3 + 0xc1) = (uint8_t)((unsigned long)t8 >> 0x10);
    *(char *)((long)arg3 + 0x183) = (char)((unsigned long)t8 >> 0x18);
    *(char *)((long)arg3 + 0x181) = (char)((unsigned long)t8 >> 8);
    return 1;
  }
                    
  t9 = (sk_code_t )sk_break(0x5519,0x510d4);
  (*t9)();
}




/* FUN_000510e4 @ 0x510e4   (est. sk_ipc_buf_write)
 * Ghidra: void FUN_000510e4(long arg1,undefined8 arg2,long arg3,ulong arg4)
 * sk_ipc_buf_write: cL4 sk ipc buf write operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_ipc_buf_write(long arg1,uint64_t arg2,long arg3,unsigned long arg4)
{
  uint8_t *t3;
  unsigned int t4;
  sk_code_t t1;
  long t0;
  unsigned long t5;
  char *t2;
  unsigned long t6;
  uint8_t stk0 [32];
  long stk1;
  
  stk1 = -0x2c8502b44bfffed6;
  t0 = sk_vspace_op2();
  if (0x3fff < arg4) {
    t6 = 0;
    t3 = (uint8_t *)sk_tpidrro;
    do {
      t3[4] = 0;
      t3[1] = 0;
      t3[5] = 0;
      t3[2] = 0;
      t3[3] = 0;
      *t3 = 0x11;
      t3[6] = 0;
      t3[7] = 0;
      t3[0xd] = (char)(t6 >> 0x1a);
      t3[8] = 0;
      t3[9] = (char)(t6 << 6);
      t3[0xb] = (char)(t6 >> 10);
      t3[10] = (char)(t6 >> 2);
      t3[0xc] = (char)(t6 >> 0x12);
      t4 = (unsigned int)(t6 >> 0x20);
      t3[0xf] = (char)(t4 >> 10);
      t3[0xe] = (char)(t4 >> 2);
      t3[0x15] = (char)((unsigned long)t0 >> 0x28);
      t3[0x10] = (char)t0;
      t3[0x13] = (char)((unsigned long)t0 >> 0x18);
      t3[0x12] = (char)((unsigned long)t0 >> 0x10);
      t3[0x11] = (char)((unsigned long)t0 >> 8);
      t3[0x14] = (char)((unsigned long)t0 >> 0x20);
      t3[0x17] = (char)((unsigned long)t0 >> 0x38);
      t3[0x16] = (char)((unsigned long)t0 >> 0x30);
      sk_svc(0);
      t3[7] = 0;
      t3[6] = 0;
      t3[5] = 0;
      t3[4] = 0;
      t3[3] = 0;
      t3[2] = 0;
      *t3 = 0x11;
      t3[1] = 0;
      if (arg1 != 0) {
        sk_ipc_msg_read(stk0,arg1,0);
        t2 = sk_str_05;
LAB_00051340:
                    
        sk_panic_msg(0,t2);
      }
      t5 = (**(sk_code_t *)(arg3 + 0x28))(arg2,t6 << 0xe,t0);
      t5 = t5 & 0xff;
      if (t5 != 0) {
        if (((&sk_global_034 + t5 < &sk_global_034) || (&sk_global_036 < &sk_global_035 + t5)) ||
           (&sk_global_035 + t5 < &sk_global_034 + t5)) {
                    
          t1 = (sk_code_t )sk_break(0x5519,0x51350);
          (*t1)();
        }
        t2 = sk_str_07;
        goto LAB_00051340;
      }
      do {
        sk_svc(4);
      } while (t0 == 1);
      t6 = t6 + 1;
    } while (t6 != arg4 >> 0xe);
  }
  if (stk1 == -0x2c8502b44bfffed6) {
    sk_xrt_init(t0);
    return;
  }
                    
  sk_noreturn_error();
}




/* FUN_00051350 @ 0x51350   (est. sk_ipc_msg_read)
 * Ghidra: void FUN_00051350(undefined8 arg1,uint8_t arg2)
 * sk_ipc_msg_read: cL4 sk ipc msg read operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_ipc_msg_read(uint64_t arg1,uint8_t arg2)
{
  char *t0;
  
  if (9 < arg2) {
    sk_memcpy2(arg1,&sk_global_002,0x20);
    sk_timer(arg1,0x20);
    return;
  }
  switch(arg2) {
  default:
    t0 = sk_str_33;
    break;
  case 1:
    t0 = sk_str_27;
    break;
  case 2:
    t0 = sk_str_11;
    break;
  case 3:
    t0 = sk_str_36;
    break;
  case 4:
    t0 = sk_str_14;
    break;
  case 5:
    t0 = sk_str_30;
    break;
  case 6:
    t0 = sk_str_17;
    break;
  case 7:
    t0 = sk_str_08;
    break;
  case 8:
    t0 = sk_str_21;
    break;
  case 9:
    t0 = sk_str_24;
  }
  sk_memcpy2(arg1,t0,0x20);
  return;
}




/* FUN_00051488 @ 0x51488   (est. sk_ipc_src_cap)
 * Ghidra: void FUN_00051488(long *arg1,long arg2,uint8_t *arg3)
 * sk_ipc_src_cap: cL4 sk ipc src cap operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_ipc_src_cap(long *arg1,long arg2,uint8_t *arg3)
{
  uint8_t t2;
  uint8_t t7;
  uint8_t t8;
  uint8_t t9;
  uint8_t t10;
  uint8_t t11;
  uint8_t t12;
  uint8_t t13;
  uint16_t t14;
  uint16_t t3;
  uint16_t t4;
  uint16_t t5;
  unsigned long t6;
  long t0;
  long t1;
  
  if (*(uint8_t *)(arg2 + 0x107) >> 2 != 0) {
                    
    sk_abort_msg(sk_str_92);
  }
  t6 = ((unsigned long)*(uint8_t *)(arg2 + 0x102) << 0x10 | (unsigned long)*(uint8_t *)(arg2 + 0x103) << 0x18 |
            (unsigned long)*(unsigned short *)(arg2 + 0x100) |
           (unsigned long)((unsigned int)*(uint8_t *)(arg2 + 0x106) << 0x10 |
                   (unsigned int)*(uint8_t *)(arg2 + 0x107) << 0x18 | (unsigned int)*(unsigned short *)(arg2 + 0x104)) <<
           0x20) * 0x40;
  if (t6 < (unsigned long)arg1[1]) {
    t0 = t6 + *arg1;
  }
  else {
    t0 = 0;
  }
  t6 = (unsigned long)*(uint8_t *)(arg2 + 0x10a) << 0x10 | (unsigned long)*(uint8_t *)(arg2 + 0x10b) << 0x18 |
           (unsigned long)*(unsigned short *)(arg2 + 0x108) |
           (unsigned long)((unsigned int)*(uint8_t *)(arg2 + 0x10e) << 0x10 |
                   (unsigned int)*(uint8_t *)(arg2 + 0x10f) << 0x18 | (unsigned int)*(unsigned short *)(arg2 + 0x10c)) <<
           0x20;
  if (t6 != 0) {
    if (*(uint8_t *)(arg2 + 0x10f) >> 2 != 0) {
                    
      sk_abort_msg(sk_str_92);
    }
    t6 = t6 * 0x40;
    if (t6 < (unsigned long)arg1[1]) {
      t1 = t6 + *arg1;
      goto LAB_00051578;
    }
  }
  t1 = 0;
LAB_00051578:
  *arg3 = (char)t0;
  arg3[5] = (char)((unsigned long)t0 >> 0x28);
  arg3[3] = (char)((unsigned long)t0 >> 0x18);
  arg3[2] = (char)((unsigned long)t0 >> 0x10);
  arg3[1] = (char)((unsigned long)t0 >> 8);
  arg3[4] = (char)((unsigned long)t0 >> 0x20);
  arg3[7] = (char)((unsigned long)t0 >> 0x38);
  arg3[6] = (char)((unsigned long)t0 >> 0x30);
  arg3[0xed] = (char)((unsigned long)t1 >> 0x28);
  arg3[0xe8] = (char)t1;
  arg3[0xeb] = (char)((unsigned long)t1 >> 0x18);
  arg3[0xea] = (char)((unsigned long)t1 >> 0x10);
  arg3[0xe9] = (char)((unsigned long)t1 >> 8);
  arg3[0xec] = (char)((unsigned long)t1 >> 0x20);
  arg3[0xef] = (char)((unsigned long)t1 >> 0x38);
  arg3[0xee] = (char)((unsigned long)t1 >> 0x30);
  t14 = *(uint16_t *)(arg2 + 0x110);
  t2 = *(uint8_t *)(arg2 + 0x113);
  t7 = *(uint8_t *)(arg2 + 0x112);
  t3 = *(uint16_t *)(arg2 + 0x114);
  t8 = *(uint8_t *)(arg2 + 0x117);
  t9 = *(uint8_t *)(arg2 + 0x116);
  t4 = *(uint16_t *)(arg2 + 0x118);
  t10 = *(uint8_t *)(arg2 + 0x11b);
  t11 = *(uint8_t *)(arg2 + 0x11a);
  t5 = *(uint16_t *)(arg2 + 0x11c);
  t12 = *(uint8_t *)(arg2 + 0x11f);
  t13 = *(uint8_t *)(arg2 + 0x11e);
  arg3[0xf0] = (char)t14;
  arg3[0xfd] = (char)((unsigned short)t5 >> 8);
  arg3[0xf9] = (char)((unsigned short)t4 >> 8);
  arg3[0xf5] = (char)((unsigned short)t3 >> 8);
  arg3[0xf3] = t2;
  arg3[0xf2] = t7;
  arg3[0xf1] = (char)((unsigned short)t14 >> 8);
  arg3[0xf8] = (char)t4;
  arg3[0xfb] = t10;
  arg3[0xf4] = (char)t3;
  arg3[0xfa] = t11;
  arg3[0xf7] = t8;
  arg3[0xf6] = t9;
  arg3[0xfc] = (char)t5;
  arg3[0xff] = t12;
  arg3[0xfe] = t13;
  return;
}




/* FUN_00051740 @ 0x51740   (est. sk_ipc_src_map)
 * Ghidra: undefined8 FUN_00051740(long arg1,ulong arg2,long arg3)
 * sk_ipc_src_map: cL4 sk ipc src map operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

uint64_t sk_ipc_src_map(long arg1,unsigned long arg2,long arg3)
{
  unsigned long t11;
  long t3;
  unsigned short *t8;
  unsigned long *t9;
  long t4;
  unsigned short t16;
  short t10;
  sk_code_t t5;
  unsigned long t17;
  long t0;
  long t1;
  unsigned long t12;
  uint64_t t13;
  unsigned long t14;
  unsigned long t15;
  unsigned long *t6;
  unsigned long *t7;
  long t2;
  
  if (arg1 != 0) {
    if ((arg2 & 0x3fff) != 0) {
LAB_0005191c:
                    
      t5 = (sk_code_t )sk_break(1,0x51920);
      (*t5)();
    }
    if (arg2 < 0xffffffffffffc000) {
      t13 = 0;
      t11 = arg2 + 0x4000;
      t1 = *(long *)(arg1 + 8);
      t12 = (unsigned long)*(unsigned short *)(arg1 + 4);
      t16 = *(unsigned short *)(arg1 + 0x14);
      t3 = arg2 + t12;
      t0 = 0;
      do {
        t17 = 0;
        if (t12 != 0) {
          t17 = (arg2 - t1) / t12;
        }
        if (t16 <= t17) {
          return t13;
        }
        t8 = (unsigned short *)(arg1 + 0x16 + t17 * 2);
        if (t8 + 1 < t8 || (unsigned short *)(arg1 + 0x16 + (unsigned long)t16 * 2) < t8 + 1) {
LAB_00051918:
                    
          t5 = (sk_code_t )sk_break(0x5519,0x5191c);
          (*t5)();
        }
        t17 = (unsigned long)*t8;
        if (t17 != 0xffff) {
          t10 = *(short *)(arg1 + 6);
          if ((t10 != 0xc) && (t10 != 7)) goto LAB_0005191c;
          t9 = (unsigned long *)(t0 + arg3);
          t6 = (unsigned long *)((long)t9 + t17);
          if (t6 != (unsigned long *)0x0) {
            t4 = 2;
            if (t10 != 7) {
              t4 = 3;
            }
            do {
              t14 = *t6;
              t15 = t14 >> 0x33 & 0x7ff;
              t2 = t15 << t4;
              if (t15 == 0) {
                t7 = (unsigned long *)0x0;
                if (-1 < (long)t14) goto LAB_00051848;
LAB_0005187c:
                t14 = t14 & 0xffffffff;
              }
              else {
                t7 = (unsigned long *)((long)t9 + (t17 & 0xffff) + t2);
                if ((t7 != (unsigned long *)0x0) &&
                   ((t7 < t9 || (unsigned long *)((long)t9 + t12) < t7 + 1) ||
                    t7 + 1 < t7)) goto LAB_00051918;
                if ((long)t14 < 0) goto LAB_0005187c;
LAB_00051848:
                t14 = t14 & 0x7ffffffffff | (t14 >> 0x2b) << 0x38;
              }
              t17 = (unsigned long)(unsigned int)((int)t17 + (int)t2);
              *t6 = t14;
              t6 = t7;
            } while (t7 != (unsigned long *)0x0);
          }
          t13 = 1;
        }
        arg2 = t0 + t3;
        t0 = t0 + t12;
        if (t11 <= arg2) {
          return t13;
        }
      } while( true );
    }
  }
  return 0;
}




/* FUN_00051920 @ 0x51920   (est. sk_ipc_cap_check)
 * Ghidra: uint8_t FUN_00051920(long arg1,ulong arg2)
 * sk_ipc_cap_check: cL4 sk ipc cap check operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

uint8_t sk_ipc_cap_check(long arg1,unsigned long arg2)
{
  unsigned long t2;
  short *psVar2;
  unsigned long t3;
  sk_code_t t1;
  uint8_t t0;
  unsigned long t4;
  
  if (arg1 != 0) {
    if ((arg2 & 0x3fff) != 0) {
                    
      t1 = (sk_code_t )sk_break(1,0x519c8);
      (*t1)();
    }
    if (arg2 < 0xffffffffffffc000) {
      t0 = 0;
      t2 = arg2 + 0x4000;
      t4 = (unsigned long)*(unsigned short *)(arg1 + 4);
      do {
        t3 = 0;
        if (t4 != 0) {
          t3 = (arg2 - *(long *)(arg1 + 8)) / t4;
        }
        if (*(unsigned short *)(arg1 + 0x14) <= t3) {
          return t0;
        }
        psVar2 = (short *)(arg1 + 0x16 + t3 * 2);
        if (psVar2 + 1 < psVar2 ||
            (short *)(arg1 + 0x16 + (unsigned long)*(unsigned short *)(arg1 + 0x14) * 2) < psVar2 + 1) {
                    
          t1 = (sk_code_t )sk_break(0x5519,0x519c4);
          (*t1)();
        }
        t0 = *psVar2 != -1 | t0;
        arg2 = arg2 + t4;
      } while (arg2 < t2);
      return t0;
    }
  }
  return 0;
}




/* FUN_000519c8 @ 0x519c8   (est. sk_sec_region_find)
 * Ghidra: ulong FUN_000519c8(long arg1,ulong arg2)
 * sk_sec_region_find: cL4 sk sec region find operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

unsigned long sk_sec_region_find(long arg1,unsigned long arg2)
{
  unsigned long t3;
  unsigned int *t1;
  unsigned long t4;
  unsigned long t5;
  unsigned int t6;
  sk_code_t t0;
  unsigned long t7;
  unsigned int *t2;
  
  if ((sk_global_061 != 0) && (t7 = (unsigned long)*sk_global_062, *sk_global_062 != 0)) {
    t2 = sk_global_062 + 1;
    t1 = t2 + t7;
    t4 = sk_global_063 + sk_global_064;
    do {
      if (t1 < t2 + 1 || t2 + 1 < t2) {
LAB_00051ab4:
                    
        t0 = (sk_code_t )sk_break(0x5519,0x51ab8);
        (*t0)();
      }
      t6 = *t2;
      if (t6 != 0) {
        t5 = sk_global_063 + *(unsigned int *)(sk_global_061 + 4) + (unsigned long)t6;
        if ((t5 != 0) &&
           ((t3 = t5 + 0x18,
            (((t3 < t5 || t5 < sk_global_063) || t4 < t3) || t4 <= t5 + 0x16)
            && (((t3 < t5 || t5 < sk_global_063) || t4 < t3) || t5 + 0x16 != t4
               ) || ((unsigned long)((long)((sk_global_064 -
                                    ((unsigned long)t6 + (unsigned long)*(unsigned int *)(sk_global_061 + 4))) + -0x16)
                            >> 1) < (unsigned long)*(unsigned short *)(t5 + 0x14))))) goto LAB_00051ab4;
        if (*(long *)(t5 + 8) == arg1) {
          if ((unsigned long)*(unsigned short *)(t5 + 0x14) * (unsigned long)*(unsigned short *)(t5 + 4) <= arg2) {
            return t5;
          }
                    
          t0 = (sk_code_t )sk_break(1,0x51ab4);
          (*t0)();
        }
      }
      t2 = t2 + 1;
      t7 = t7 - 1;
    } while (t7 != 0);
  }
  return 0;
}




/* FUN_00051ab8 @ 0x51ab8   (est. sk_sec_regions)
 * Ghidra: void FUN_00051ab8(unsigned int *arg1,ulong arg2)
 * sk_sec_regions: cL4 sk sec regions operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_sec_regions(unsigned int *arg1,unsigned long arg2)
{
  unsigned int *t5;
  unsigned int *t7;
  unsigned int *t8;
  unsigned int *t9;
  unsigned int *t10;
  unsigned int t14;
  long t2;
  sk_code_t t4;
  long t3;
  long t0;
  long t1;
  unsigned long *t6;
  unsigned long t11;
  unsigned long t12;
  unsigned long t13;
  
  t2 = sk_global_055;
  if (arg2 < 0x1c) {
                    
    t4 = (sk_code_t )sk_break(1,0x51d3c);
    (*t4)();
  }
  t8 = (unsigned int *)((long)arg1 + arg2);
  t9 = (unsigned int *)((long)arg1 + (unsigned long)arg1[1]);
  if (t9 == (unsigned int *)0x0) {
    t12 = 0;
  }
  else if (((t9 + 1 < t9 || t9 < arg1) || t8 < t9 + 1) ||
          (t12 = (unsigned long)*t9, (unsigned long)((long)((arg2 - arg1[1]) + -4) >> 2) < t12)) {
LAB_00051b24:
                    
    t4 = (sk_code_t )sk_break(0x5519,0x51b28);
    (*t4)();
  }
  sk_global_043 = 1;
  sk_global_061 = arg1;
  sk_global_062 = t9;
  sk_global_063 = arg1;
  sk_global_064 = arg2;
  t3 = sk_macho_seg_by(0,sk_str_60);
  t0 = sk_macho_seg_by(0,sk_str_61);
  if ((int)t12 != 0) {
    t13 = 0;
    t5 = t9 + 1;
    do {
      t10 = t5 + t13;
      if ((t10 < t5 || t10 + 1 < t10) || t5 + *t9 < t10 + 1)
      goto LAB_00051b24;
      t14 = *t10;
      if (t14 != 0) {
        t10 = (unsigned int *)((long)arg1 + (unsigned long)t14 + (unsigned long)arg1[1]);
        if ((t10 != (unsigned int *)0x0) &&
           ((t7 = t10 + 6,
            (((t7 < t10 || t10 < arg1) || t8 < t7) ||
            t8 <= (unsigned int *)((long)t10 + 0x16U)) &&
            (((t7 < t10 || t10 < arg1) || t8 < t7) ||
            (unsigned int *)((long)t10 + 0x16U) != t8) ||
            ((unsigned long)((long)((arg2 - 0x16) - ((unsigned long)t14 + (unsigned long)arg1[1])) >> 1) <
             (unsigned long)(unsigned short)t10[5])))) goto LAB_00051b24;
        t1 = *(long *)(t10 + 2);
        if (sk_global_039 == '\x01') {
          if ((t3 == 0) ||
             (*(unsigned long *)(t3 + 0x20) <= (unsigned long)(t1 - (t2 + *(long *)(t3 + 0x18))))) {
            if ((t0 == 0) ||
               (*(unsigned long *)(t0 + 0x20) <= (unsigned long)(t1 - (t2 + *(long *)(t0 + 0x18)))))
            goto LAB_00051cdc;
            if ((t10 != (unsigned int *)0x0) &&
               ((t10 + 6 < t10 ||
                ((unsigned int *)((long)t10 + (unsigned long)(unsigned short)t10[5] * 2 + 0x16) < t10 + 6))))
            goto LAB_00051b24;
            t6 = (unsigned long *)&sk_global_045;
          }
          else {
            if ((t10 != (unsigned int *)0x0) &&
               ((t10 + 6 < t10 ||
                ((unsigned int *)((long)t10 + (unsigned long)(unsigned short)t10[5] * 2 + 0x16) < t10 + 6))))
            goto LAB_00051b24;
            t6 = (unsigned long *)&sk_global_044;
          }
          *t6 = (unsigned long)t10;
        }
        else {
LAB_00051cdc:
          if ((short)t10[5] != 0) {
            t11 = 0;
            do {
              sk_ipc_src_map(t10,t1,t1);
              t11 = t11 + 1;
              t1 = t1 + 0x4000;
            } while (t11 < (unsigned short)t10[5]);
          }
        }
      }
      t13 = t13 + 1;
    } while (t13 != t12);
  }
  return;
}




/* FUN_00051d3c @ 0x51d3c   (est. sk_macho_vmrange)
 * Ghidra: ulong FUN_00051d3c(long arg1)
 * sk_macho_vmrange: cL4 sk macho vmrange operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

unsigned long sk_macho_vmrange(long arg1)
{
  int t0;
  unsigned long t2;
  unsigned long t3;
  unsigned long t4;
  int *t1;
  
  t4 = (unsigned long)*(unsigned int *)(arg1 + 0x10);
  if (*(unsigned int *)(arg1 + 0x10) == 0) {
    t3 = 0xffffffffffffffff;
  }
  else {
    t1 = (int *)(arg1 + 0x20);
    t2 = 0xffffffffffffffff;
    do {
      t3 = t2;
      if (((*t1 == 0x19) &&
          (t0 = sk_strcmp(t1 + 2,sk_str_63,0x10), t0 != 0)) &&
         (t3 = *(unsigned long *)(t1 + 6), t2 <= *(unsigned long *)(t1 + 6))) {
        t3 = t2;
      }
      t1 = (int *)((long)t1 + (unsigned long)(unsigned int)t1[1]);
      t4 = t4 - 1;
      t2 = t3;
    } while (t4 != 0);
  }
  return t3;
}




/* FUN_00051dc0 @ 0x51dc0   (est. sk_macho_vmrange2)
 * Ghidra: ulong FUN_00051dc0(long arg1)
 * sk_macho_vmrange2: cL4 sk macho vmrange2 operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

unsigned long sk_macho_vmrange2(long arg1)
{
  unsigned long t1;
  unsigned long t2;
  int *t0;
  unsigned long t3;
  
  t3 = (unsigned long)*(unsigned int *)(arg1 + 0x10);
  if (*(unsigned int *)(arg1 + 0x10) == 0) {
    return 0;
  }
  t0 = (int *)(arg1 + 0x20);
  t1 = 0;
  do {
    t2 = t1;
    if ((*t0 == 0x19) &&
       (t2 = *(long *)(t0 + 8) + *(long *)(t0 + 6),
       (unsigned long)(*(long *)(t0 + 8) + *(long *)(t0 + 6)) <= t1)) {
      t2 = t1;
    }
    t0 = (int *)((long)t0 + (unsigned long)(unsigned int)t0[1]);
    t3 = t3 - 1;
    t1 = t2;
  } while (t3 != 0);
  return t2;
}




/* FUN_00051e0c @ 0x51e0c   (est. sk_macho_seg)
 * Ghidra: int * FUN_00051e0c(long arg1,int *arg2)
 * sk_macho_seg: cL4 sk macho seg operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

int * sk_macho_seg(long arg1,int *arg2)
{
  sk_code_t t0;
  int *t1;
  int *t2;
  unsigned long t3;
  
  t3 = (unsigned long)*(unsigned int *)(arg1 + 0x10);
  if (*(unsigned int *)(arg1 + 0x10) != 0) {
    t1 = (int *)(arg1 + 0x20);
    do {
      t2 = arg2;
      if (*t1 == 0x19) {
        if (arg2 == (int *)0x0) {
          if (t1 + 0x12 < t1) {
                    
            t0 = (sk_code_t )sk_break(0x5519,0x51e5c);
            (*t0)();
          }
          return t1;
        }
        t2 = (int *)0x0;
        if (arg2 != t1) {
          t2 = arg2;
        }
      }
      t1 = (int *)((long)t1 + (unsigned long)(unsigned int)t1[1]);
      t3 = t3 - 1;
      arg2 = t2;
    } while (t3 != 0);
  }
  return (int *)0x0;
}




/* FUN_00051e5c @ 0x51e5c   (est. sk_macho_seg_by)
 * Ghidra: ulong FUN_00051e5c(undefined8 arg1,undefined8 arg2)
 * sk_macho_seg_by: cL4 sk macho seg by operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

unsigned long sk_macho_seg_by(uint64_t arg1,uint64_t arg2)
{
  sk_code_t t1;
  int t0;
  unsigned long t2;
  unsigned long t3;
  
  t3 = 0;
  t2 = 0;
  do {
    if ((t2 != 0) && ((t3 < t2 + 0x48 || (t2 + 0x48 < t2)))) goto LAB_00051ee0;
    t2 = sk_macho_seg(arg1,t2);
    if (t2 == 0) {
      return 0;
    }
    t3 = t2 + 0x48;
    t0 = sk_strcmp(arg2,t2 + 8,0x10);
  } while (t0 != 0);
  if (t2 <= t3) {
    return t2;
  }
LAB_00051ee0:
                    
  t1 = (sk_code_t )sk_break(0x5519,0x51ee4);
  (*t1)();
}




/* FUN_00051ee4 @ 0x51ee4   (est. sk_macho_seg_off)
 * Ghidra: ulong FUN_00051ee4(long arg1,undefined8 arg2)
 * sk_macho_seg_off: cL4 sk macho seg off operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

unsigned long sk_macho_seg_off(long arg1,uint64_t arg2)
{
  unsigned long t2;
  sk_code_t t1;
  int t0;
  unsigned long t3;
  unsigned long t4;
  
  t4 = 0;
  t3 = 0;
  t2 = arg1 + 0x48;
  do {
    if (t3 == 0) {
      if (*(int *)(arg1 + 0x40) == 0) {
        return 0;
      }
      t3 = t2;
      if (arg1 + 0x98U < t2) goto LAB_00051f9c;
    }
    else {
      if ((t4 < t3 + 0x50) || (t3 + 0x50 < t3)) goto LAB_00051f9c;
      if (*(unsigned int *)(arg1 + 0x40) == 0) {
        return 0;
      }
      if (t3 < t2) {
        return 0;
      }
      if (arg1 + -8 + (unsigned long)*(unsigned int *)(arg1 + 0x40) * 0x50 <= t3) {
        return 0;
      }
      t3 = t3 + 0x50;
    }
    if (t3 == 0) {
      return 0;
    }
    t4 = t3 + 0x50;
    t0 = sk_strcmp(arg2,t3,0x10);
  } while (t0 != 0);
  if (t3 <= t4) {
    return t3;
  }
LAB_00051f9c:
                    
  t1 = (sk_code_t )sk_break(0x5519,0x51fa0);
  (*t1)();
}




/* FUN_00051fbc @ 0x51fbc   (est. sk_macho_uuid)
 * Ghidra: int * FUN_00051fbc(long arg1)
 * sk_macho_uuid: cL4 sk macho uuid operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

int * sk_macho_uuid(long arg1)
{
  unsigned long t1;
  int *t0;
  
  t1 = (unsigned long)*(unsigned int *)(arg1 + 0x10);
  if (*(unsigned int *)(arg1 + 0x10) != 0) {
    t0 = (int *)(arg1 + 0x20);
    do {
      if (*t0 == 0x1b) {
        return t0 + 2;
      }
      t0 = (int *)((long)t0 + (unsigned long)(unsigned int)t0[1]);
      t1 = t1 - 1;
    } while (t1 != 0);
  }
  return (int *)0x0;
}




/* FUN_00051ff4 @ 0x51ff4   (est. sk_macho_layout)
 * Ghidra: void FUN_00051ff4(long arg1,ulong *arg2,ulong *arg3,long *arg4)
 * sk_macho_layout: cL4 sk macho layout operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_macho_layout(long arg1,unsigned long *arg2,unsigned long *arg3,long *arg4)
{
  unsigned long t5;
  unsigned long t6;
  unsigned int t7;
  sk_code_t t3;
  long t0;
  long t1;
  unsigned long t8;
  long t2;
  int *t4;
  
  t0 = sk_macho_seg_by(arg1,sk_str_65);
  t8 = (unsigned long)*(unsigned int *)(arg1 + 0x10);
  if (*(unsigned int *)(arg1 + 0x10) != 0) {
    t0 = *(long *)(t0 + 0x18);
    t4 = (int *)(arg1 + 0x20);
    do {
      if (*t4 == 2) {
        t1 = sk_macho_seg_by(arg1,sk_str_62);
        if ((t1 == 0) || (t8 = (unsigned long)(unsigned int)t4[3], t4[3] == 0)) goto LAB_00052068;
        t2 = *(long *)(t1 + 0x28);
        t0 = *(long *)(t1 + 0x18) + (arg1 - t0);
        t5 = (t0 - t2) + (unsigned long)(unsigned int)t4[2];
        t6 = t5 + t8 * 0x10;
        if ((t6 < t5) || ((unsigned long)((long)(t6 - t5) >> 4) < t8)) {
                    
          t3 = (sk_code_t )sk_break(0x5519,0x520f0);
          (*t3)();
        }
        t7 = t4[4];
        *arg2 = t8;
        *arg3 = t5;
        t0 = ((unsigned long)t7 - t2) + t0;
        goto LAB_00052074;
      }
      t4 = (int *)((long)t4 + (unsigned long)(unsigned int)t4[1]);
      t8 = t8 - 1;
    } while (t8 != 0);
  }
  sk_macho_seg_by(arg1,sk_str_62);
LAB_00052068:
  t0 = 0;
  *arg2 = 0;
  *arg3 = 0;
LAB_00052074:
  *arg4 = t0;
  return;
}




/* FUN_000520f0 @ 0x520f0   (est. sk_macho_bind)
 * Ghidra: long FUN_000520f0(ulong arg1,long *arg2,long arg3,long arg4,long arg5)
 * sk_macho_bind: cL4 sk macho bind operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

long sk_macho_bind(unsigned long arg1,long *arg2,long arg3,long arg4,long arg5)
{
  long t0;
  long *t3;
  long t1;
  long t2;
  
  if (arg3 == 0) {
    t0 = 0;
    t1 = 0;
  }
  else {
    t1 = 0;
    t0 = 0;
    t3 = (long *)(arg4 + 8);
    do {
      if ((((*(uint8_t *)((long)t3 + -4) & 0xee) == 0xe) && (t2 = *t3, t2 - 1U < arg1)
          ) && (arg1 - t2 < arg1 - t1)) {
        t0 = (unsigned long)*(unsigned int *)(t3 + -1) + arg5;
        t1 = t2;
      }
      t3 = t3 + 2;
      arg3 = arg3 + -1;
    } while (arg3 != 0);
  }
  *arg2 = t1;
  return t0;
}




/* FUN_00052248 @ 0x52248   (est. sk_dump_rebasechains)
 * Ghidra: void FUN_00052248(void)
 * sk_dump_rebasechains: cL4 sk dump rebasechains operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_dump_rebasechains(void)
{
  uint64_t stk0;
  
  if (sk_global_041 == '\x01') {
    sk_sec_region_find();
    return;
  }
  stk0 = 0;
  sk_ctx_printf(sk_str_100,&stk0);
  return;
}




/* FUN_0005228c @ 0x5228c   (est. sk_rebasechain_walk)
 * Ghidra: ulong FUN_0005228c(long arg1,ulong arg2)
 * sk_rebasechain_walk: cL4 sk rebasechain walk operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

unsigned long sk_rebasechain_walk(long arg1,unsigned long arg2)
{
  short *psVar1;
  short *psVar2;
  short *psVar3;
  sk_code_t t0;
  unsigned long t1;
  
  if (sk_global_041 == '\x01') {
    t1 = sk_ipc_cap_check();
    return t1;
  }
  psVar1 = (short *)(arg1 + 0x18);
  psVar2 = (short *)(arg1 + ((unsigned long)*(uint8_t *)(arg1 + 0x16) << 2 |
                               (unsigned long)*(uint8_t *)(arg1 + 0x17) << 10) +
                     (unsigned long)*(unsigned short *)(arg1 + 0x14) * 2 + 0x18);
  if (psVar1 <= psVar2) {
    t1 = ((unsigned long)*(uint8_t *)(arg1 + 0xe) << 0x10 | (unsigned long)*(uint8_t *)(arg1 + 0xf) << 0x18 |
             (unsigned long)*(unsigned short *)(arg1 + 0xc) |
            (unsigned long)((unsigned int)*(uint8_t *)(arg1 + 0x12) << 0x10 |
                    (unsigned int)*(uint8_t *)(arg1 + 0x13) << 0x18 | (unsigned int)*(unsigned short *)(arg1 + 0x10)) <<
            0x20) + sk_global_055;
    if (arg2 < t1 || t1 + (unsigned long)*(unsigned short *)(arg1 + 0x14) * 0x4000 <= arg2) {
      return 0;
    }
    psVar3 = psVar1 + (arg2 - t1 >> 0xe);
    if ((psVar1 <= psVar3 && psVar3 + 1 <= psVar2) && psVar3 <= psVar3 + 1) {
      return (unsigned long)(*psVar3 != -1);
    }
  }
                    
  t0 = (sk_code_t )sk_break(0x5519,0x5236c);
  (*t0)();
}




/* FUN_0005236c @ 0x5236c   (est. sk_rebasechain_map)
 * Ghidra: undefined8 FUN_0005236c(long arg1,ulong arg2,long arg3)
 * sk_rebasechain_map: cL4 sk rebasechain map operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

uint64_t sk_rebasechain_map(long arg1,unsigned long arg2,long arg3)
{
  unsigned short *t6;
  unsigned short *t8;
  unsigned short *t9;
  unsigned short *t10;
  unsigned short *t11;
  long t3;
  uint64_t *t12;
  unsigned short t20;
  uint64_t *t13;
  uint8_t t14;
  uint8_t t15;
  sk_code_t t5;
  bool t0;
  int t1;
  unsigned long t16;
  uint64_t t17;
  uint8_t *t4;
  uint64_t *t7;
  unsigned long t18;
  unsigned long t19;
  long t2;
  uint8_t stk0 [16];
  uint64_t stk6;
  uint64_t stk5;
  uint64_t stk4;
  unsigned short *stk3;
  long lStack_88;
  unsigned long stk2;
  long lStack_78;
  uint8_t *stk1;
  uint64_t stk7;
  
  if (sk_global_041 == '\x01') {
    t16 = sk_ipc_src_map(arg1,arg2,arg3);
    if ((t16 & 1) != 0) {
      return 1;
    }
    sk_rt_flags();
  }
  t6 = (unsigned short *)(arg1 + 0x18);
  t16 = (unsigned long)(unsigned int)*(unsigned short *)(arg1 + 0x16);
  t8 = (unsigned short *)(arg1 + t16 * 4 + (unsigned long)*(unsigned short *)(arg1 + 0x14) * 2 + 0x18);
  if (t6 <= t8) {
    t18 = (unsigned long)*(uint8_t *)(arg1 + 0xe) << 0x10 | (unsigned long)*(uint8_t *)(arg1 + 0xf) << 0x18 |
             (unsigned long)*(unsigned short *)(arg1 + 0xc) |
             (unsigned long)((unsigned int)*(uint8_t *)(arg1 + 0x12) << 0x10 |
                     (unsigned int)*(uint8_t *)(arg1 + 0x13) << 0x18 | (unsigned int)*(unsigned short *)(arg1 + 0x10)) <<
             0x20;
    t19 = t18 + sk_global_055;
    if (arg2 < t19 ||
        sk_global_055 + (unsigned long)*(unsigned short *)(arg1 + 0x14) * 0x4000 + t18 <= arg2) {
LAB_00052570:
      t17 = sk_rt_flags();
      stk7 = 0x52574;
      if ((sk_global_046 & 1) == 0) {
        stk3 = t6;
        lStack_88 = arg1;
        stk2 = arg2;
        lStack_78 = arg3;
        stk1 = NULL;
        t4 = (uint8_t *)sk_tcb_cur();
        if ((*t4 & 1) == 0) {
          stk4 = 0;
          t17 = sk_ctx_irq(sk_str_59,&stk4);
          if (*(long *)(t4 + 0xc0) == 0) {
            sk_cap_load(stk4,t17);
          }
        }
        t15 = sk_global_040;
        t14 = sk_global_039;
        sk_global_056 = sk_ctx_cpsr(sk_init_stage3,0x52988,0);
        t17 = sk_boot_list();
        t13 = (uint64_t *)sk_tpidr;
        t12 = t13 + sk_global_056;
        t7 = t12 + -1;
        if ((t7 < t13 || t13 + 0x1f < t12) || t12 < t7) {
                    
          t5 = (sk_code_t )sk_break(0x5519,0x52718);
          (*t5)();
        }
        *t7 = t17;
        t1 = sk_domain_state();
        if (t1 != 0) {
          sk_syscall_exc(t15,t14);
        }
        stk5 = 0;
        stk4 = 0;
        stk6 = 0;
        sk_boot_triple(&stk4,&stk5,&stk6);
        sk_pmap_op(stk4,stk5,stk6);
        sk_boot_state();
        sk_obj_ref();
        sk_cap_store();
        if (sk_global_065 != (sk_code_t )0x0) {
          (*sk_global_065)();
        }
        sk_shift_dispatch();
        t1 = sk_domain_state();
        if (t1 != 0) {
          sk_sec_mem_scan(t15,t14);
        }
        sk_current_thread();
        t17 = sk_ctx_flag();
        stk0 = sk_boot_heap();
        (**(sk_code_t *)(stk0._8_8_ + 0x20))(t17,stk0._0_8_);
        sk_debug(0);
        sk_console();
        t17 = sk_set_cap_class(0);
        sk_global_046 = 1;
      }
      return t17;
    }
    t19 = arg2 - t19 >> 0xe;
    t9 = t6 + t19;
    if ((t6 <= t9 && t9 + 1 <= t8) && t9 <= t9 + 1) {
      t20 = *t9;
      if (t20 == 0xfffe) {
        if (*(unsigned short *)(arg1 + 0x16) != 0) {
          t18 = 0;
          t2 = arg1;
          do {
            t3 = t2 + (unsigned long)*(unsigned short *)(arg1 + 0x14) * 2;
            t9 = (unsigned short *)(t3 + 0x18);
            t10 = (unsigned short *)(t3 + 0x1a);
            t0 = t9 < t6;
            t11 = (unsigned short *)(t3 + 0x1c);
            if (((((t0 || t8 < t10) || t10 < t9) || t8 <= t11) &&
                 (((t0 || t8 < t10) || t10 < t9) || t11 != t8) ||
                t11 <= t10) &&
                ((((t0 || t8 < t10) || t10 < t9) || t8 <= t11) &&
                 (((t0 || t8 < t10) || t10 < t9) || t11 != t8) ||
                t10 != t11)) goto LAB_0005256c;
            if (t19 == *t9) {
              sk_obj_alloc(arg3 + (unsigned long)*t10,arg2 & 0xffffffffffffc000,
                           *(uint16_t *)(arg1 + 2),-sk_global_055);
              t16 = (unsigned long)*(unsigned short *)(arg1 + 0x16);
            }
            t18 = t18 + 1;
            t2 = t2 + 4;
          } while (t18 < t16);
        }
      }
      else {
        if (t20 == 0xffff) goto LAB_00052570;
        sk_obj_alloc(arg3 + (unsigned long)t20,arg2 & 0xffffffffffffc000,
                     *(uint16_t *)(arg1 + 2),-sk_global_055);
      }
      return 1;
    }
  }
LAB_0005256c:
                    
  t5 = (sk_code_t )sk_break(0x5519,0x52570);
  (*t5)();
}




/* FUN_00052718 @ 0x52718   (est. sk_boot_finish)
 * Ghidra: void FUN_00052718(undefined8 arg1)
 * sk_boot_finish: cL4 sk boot finish operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_boot_finish(uint64_t arg1)
{
  uint8_t *t3;
  int t0;
  long t1;
  long t2;
  
  if (sk_global_065 == 0) {
    sk_global_065 = arg1;
    return;
  }
  t1 = sk_rt_phase();
  t2 = sk_tcb_cur();
  sk_cnode_notify(*(uint8_t *)(t2 + 0xd8) & 1);
  sk_domain_notify(t1 != 0,1);
  sk_domain_notify(t1 != 0,0);
  if ((t1 == 0) && (t0 = sk_preempt_check(), t0 != 0)) {
    t0 = sk_thread_create(0x40000,&sk_global_000,t2);
  }
  else {
    sk_init_stage2(t2);
    t0 = sk_boot_next();
  }
  if (t0 == 0) {
    sk_current_thread();
    sk_error_broadcast();
    if (t1 != 0) {
      return;
    }
    sk_kernel_field_40();
    sk_log_str(sk_str_56);
    t0 = sk_error_register(1,2);
    if (t0 == 1) {
      sk_ctx_finish();
    }
    t3 = (uint8_t *)sk_tpidrro;
    t3[1] = 0;
    *t3 = 0;
    t3[4] = 0;
    t3[2] = 0;
    t3[5] = 0;
    t3[3] = 0;
    t3[6] = 0;
    t3[7] = 0;
    sk_svc(0);
    *t3 = 0;
    t3[7] = 0;
    t3[6] = 0;
    t3[5] = 0;
    t3[4] = 0;
    t3[3] = 0;
    t3[2] = 0;
    t3[1] = 0;
                    
    sk_abort_msg(sk_str_86,1);
  }
                    
  sk_xrt_abort(sk_str_114);
}




/* FUN_000528c4 @ 0x528c4   (est. sk_domain_notify)
 * Ghidra: void FUN_000528c4(int arg1,undefined8 arg2)
 * sk_domain_notify: cL4 sk domain notify operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_domain_notify(int arg1,uint64_t arg2)
{
  int t0;
  
  sk_notify_domain(0x706c6174);
  t0 = sk_domain_state();
  if (t0 != 0) {
    sk_sec_mem_scan2(arg2);
    return;
  }
  if (arg1 != 0) {
    sk_notify_domain(0x726f6f74,arg2);
    return;
  }
  return;
}




/* FUN_00052940 @ 0x52940   (est. sk_init_stage)
 * Ghidra: void FUN_00052940(void)
 * sk_init_stage: cL4 sk init stage operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_init_stage(void)
{
  sk_init_stage2();
  sk_boot_next();
  return;
}




/* FUN_0005295c @ 0x5295c   (est. sk_init_stage2)
 * Ghidra: void FUN_0005295c(void)
 * sk_init_stage2: cL4 sk init stage2 operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_init_stage2(void)
{
  sk_log_char(sk_str_79);
  return;
}




/* FUN_00052968 @ 0x52968   (est. sk_init_stage3)
 * Ghidra: void FUN_00052968(void)
 * sk_init_stage3: cL4 sk init stage3 operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_init_stage3(void)
{
  int t1;
  long t2;
  uint64_t t3;
  uint64_t *t0;
  
  t2 = sk_vspace_op2();
  if (t2 != 0) {
    return;
  }
  t2 = sk_rt_state();
  if (t2 != 0) {
    sk_xrt_init();
    return;
  }
  t3 = sk_syscall_get_state();
  t1 = (int)t3;
  if (t1 != 1) {
    if (t1 != 6) {
      if (t1 == 4) {
        sk_error_from_code(2);
        return;
      }
      t0[1] = 0;
      t0[2] = 0;
      *t0 = 0;
      return;
    }
    t3 = 3;
  }
  sk_error_from_code(t3);
  return;
}




/* FUN_0005296c @ 0x5296c   (est. sk_init_stage4)
 * Ghidra: void FUN_0005296c(void)
 * sk_init_stage4: cL4 sk init stage4 operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_init_stage4(void)
{
  int t1;
  long t2;
  uint64_t t3;
  uint64_t *t0;
  
  t2 = sk_vspace_op2();
  if (t2 != 0) {
    return;
  }
  t2 = sk_rt_state();
  if (t2 != 0) {
    sk_xrt_init();
    return;
  }
  t3 = sk_syscall_get_state();
  t1 = (int)t3;
  if (t1 != 1) {
    if (t1 != 6) {
      if (t1 == 4) {
        sk_error_from_code(2);
        return;
      }
      t0[1] = 0;
      t0[2] = 0;
      *t0 = 0;
      return;
    }
    t3 = 3;
  }
  sk_error_from_code(t3);
  return;
}




/* FUN_00052994 @ 0x52994   (est. sk_init_check)
 * Ghidra: void FUN_00052994(void)
 * sk_init_check: cL4 sk init check operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_init_check(void)
{
  int t1;
  uint64_t t2;
  uint64_t *t0;
  
  t2 = sk_syscall_get_state();
  t1 = (int)t2;
  if (t1 != 1) {
    if (t1 != 6) {
      if (t1 == 4) {
        sk_error_from_code(2);
        return;
      }
      t0[1] = 0;
      t0[2] = 0;
      *t0 = 0;
      return;
    }
    t2 = 3;
  }
  sk_error_from_code(t2);
  return;
}




/* FUN_000529a0 @ 0x529a0   (est. sk_init_result)
 * Ghidra: void FUN_000529a0(undefined8 *arg1,undefined8 arg2)
 * sk_init_result: cL4 sk init result operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_init_result(uint64_t *arg1,uint64_t arg2)
{
  int t0;
  
  t0 = (int)arg2;
  if (t0 != 1) {
    if (t0 != 6) {
      if (t0 == 4) {
        sk_error_from_code(2);
        return;
      }
      arg1[1] = 0;
      arg1[2] = 0;
      *arg1 = 0;
      return;
    }
    arg2 = 3;
  }
  sk_error_from_code(arg2);
  return;
}




/* FUN_000529d4 @ 0x529d4   (est. sk_init_result_word)
 * Ghidra: undefined8 FUN_000529d4(undefined8 arg1)
 * sk_init_result_word: cL4 sk init result word operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

uint64_t sk_init_result_word(uint64_t arg1)
{
  int t0;
  uint64_t t1;
  
  t0 = (int)arg1;
  if (t0 != 1) {
    if (t0 != 6) {
      if (t0 == 4) {
        t1 = sk_error_to_word(2);
        return t1;
      }
      return 0xffffffffffffffff;
    }
    arg1 = 3;
  }
  t1 = sk_error_to_word(arg1);
  return t1;
}




/* FUN_00052a04 @ 0x52a04   (est. sk_init_cpu_region)
 * Ghidra: void FUN_00052a04(ulong arg1)
 * sk_init_cpu_region: cL4 sk init cpu region operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_init_cpu_region(unsigned long arg1)
{
  uint8_t t0;
  unsigned short t5;
  uint64_t t6;
  unsigned short t7;
  sk_code_t t2;
  long t1;
  unsigned short *t3;
  unsigned long t8;
  unsigned short *t4;
  
  if (arg1 <= arg1 + 0x4000) {
    t1 = sk_lookup_thread_obj(4,4);
    if (t1 == 0) {
      uRam000000000064cc60 = arg1;
                    
      sk_register_global();
                    
      uRam000000000064cc80 = 0x6af8e0;
      sk_register_global();
      for (t3 = (unsigned short *)sk_global_get(0x6aff18,2,4); t3 != (unsigned short *)0xffffffffffffffff;
          t3 = (unsigned short *)
                   ((unsigned long)(uint8_t)t3[5] << 0x10 | (unsigned long)*(uint8_t *)((long)t3 + 0xb) << 0x18 |
                    (unsigned long)t3[4] |
                   (unsigned long)((unsigned int)(uint8_t)t3[7] << 0x10 |
                           (unsigned int)*(uint8_t *)((long)t3 + 0xf) << 0x18 | (unsigned int)t3[6]) << 0x20))
      {
        if (t3 + 0x2000 < t3) goto LAB_00052c48;
        if ((((char)t3[1] != '\0' || *(char *)((long)t3 + 3) != '\0') || *t3 != 0) ||
            (((char)t3[3] != '\0' || *(char *)((long)t3 + 7) != '\0') || t3[2] != 0)) {
          t8 = 0;
          t4 = t3 + 0x10;
          do {
            if ((t4 != (unsigned short *)0x0) &&
               (((t4 < t3 + 0x10 || (t3 + 0x2000 < t4 + 0x10)) ||
                (t4 + 0x10 < t4)))) goto LAB_00052c48;
            t6 = *(uint64_t *)(t4 + 2);
            if (*(char *)((long)t4 + 7) == '\v') {
              if (t4 + 0x10 < t4) goto LAB_00052c48;
              t5 = *t4;
              t0 = *(uint8_t *)((long)t4 + 3);
              t7 = t4[1];
              t1 = sk_global_get(0x6af8d8,2,5);
              *(unsigned long *)(t1 + 0x2a0) =
                   (unsigned long)(uint8_t)t7 << 0x10 | (unsigned long)t0 << 0x18 | (unsigned long)t5 |
                   (unsigned long)t6 << 0x20;
            }
            t8 = t8 + 1;
            t4 = t4 + 0x10;
          } while (t8 < ((unsigned long)(uint8_t)t3[1] << 0x10 |
                            (unsigned long)*(uint8_t *)((long)t3 + 3) << 0x18 | (unsigned long)*t3 |
                           (unsigned long)((unsigned int)(uint8_t)t3[3] << 0x10 |
                                   (unsigned int)*(uint8_t *)((long)t3 + 7) << 0x18 | (unsigned int)t3[2]) <<
                           0x20));
        }
      }
    }
    return;
  }
LAB_00052c48:
                    
  t2 = (sk_code_t )sk_break(0x5519,0x52c4c);
  (*t2)();
}




/* FUN_00052c4c @ 0x52c4c   (est. sk_exc_abort)
 * Ghidra: undefined8 FUN_00052c4c(undefined8 *arg1)
 * sk_exc_abort: cL4 sk exc abort operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

uint64_t sk_exc_abort(uint64_t *arg1)
{
  return *arg1;
}




/* FUN_00052c54 @ 0x52c54   (est. sk_init_cnodes)
 * Ghidra: void FUN_00052c54(void)
 * sk_init_cnodes: cL4 sk init cnodes operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_init_cnodes(void)
{
  unsigned short *t5;
  unsigned short *t8;
  uint8_t t0;
  uint64_t t16;
  unsigned short t17;
  unsigned short t18;
  unsigned short t19;
  sk_code_t t4;
  unsigned int t20;
  unsigned int t10;
  unsigned int t11;
  unsigned short *t6;
  long t1;
  long t2;
  unsigned long *t7;
  unsigned long t12;
  long t3;
  unsigned int t13;
  unsigned long t14;
  unsigned short *t9;
  unsigned long t15;
  
  t20 = sk_tcb_a();
  t10 = sk_tcb_z2();
  t11 = sk_tcb_ae();
  t6 = (unsigned short *)sk_global_get(0x6aff18,2,4);
  t1 = sk_global_get(0x6af8d8,2,5);
  if ((*(uint8_t *)(t1 + 0x630) & 1) != 0) {
    return;
  }
  while( true ) {
    if (t6 == (unsigned short *)0xffffffffffffffff) {
      if (*(char *)(t1 + 0x278) != '\0') {
        *(uint8_t *)(t1 + 0x279) = 0;
                    
        sk_xrt_abort(sk_str_83);
      }
      if (*(char *)(t1 + 0x27a) == '\x01') {
                    
        sk_xrt_abort(sk_str_98);
      }
      t15 = *(unsigned long *)(t1 + 0x240);
      if (*(unsigned long *)(t1 + 0x238) == t15) {
        sk_rt_done();
      }
      else {
        t14 = *(unsigned long *)(t1 + 0x250);
        if (*(unsigned long *)(t1 + 0x238) == *(unsigned long *)(t1 + 0x248)) {
          if (t15 < t14) {
                    
            sk_xrt_abort(sk_str_85);
          }
          if (0x3ff < t15 - t14) {
            *(unsigned long *)(t1 + 600) = t14;
            t2 = (t15 - t14 & 0xffffffffffffffc0) + t14;
            t3 = t2 + -0x400;
            *(long *)(t1 + 0x260) = t3;
            *(long *)(t1 + 0x268) = t3;
            *(long *)(t1 + 0x270) = t2;
            *(uint8_t *)(t1 + 0x278) = 1;
            *(uint8_t *)(t1 + 0x630) = 1;
            return;
          }
                    
          sk_xrt_abort(sk_str_87);
        }
      }
                    
      sk_xrt_abort(sk_str_84);
    }
    if (t6 + 0x2000 < t6) break;
    if ((((uint8_t)t6[1] != 0 || *(uint8_t *)((long)t6 + 3) != 0) || *t6 != 0) ||
        (((uint8_t)t6[3] != 0 || *(uint8_t *)((long)t6 + 7) != 0) || t6[2] != 0)) {
      t15 = 0;
      t9 = t6 + 0x10;
      do {
        if ((t9 != (unsigned short *)0x0) &&
           (((t9 < t6 + 0x10 || (t6 + 0x2000 < t9 + 0x10)) ||
            (t9 + 0x10 < t9)))) goto LAB_000532f0;
        t13 = (unsigned int)*(uint8_t *)((long)t9 + 7);
        t14 = (unsigned long)(uint8_t)t9[1] << 0x10 | (unsigned long)*(uint8_t *)((long)t9 + 3) << 0x18 |
                 (unsigned long)*t9 | (unsigned long)*(uint64_t *)(t9 + 2) << 0x20;
        if ((*(unsigned long *)(t1 + 0x248) == 0) && (*(long *)(t1 + 0x250) == 0)) {
          *(unsigned long *)(t1 + 0x248) = t14;
LAB_00052de4:
          *(unsigned long *)(t1 + 0x250) = t14 + 0x40;
        }
        else {
          if (t14 < *(unsigned long *)(t1 + 0x248)) {
            *(unsigned long *)(t1 + 0x248) = t14;
          }
          if (*(unsigned long *)(t1 + 0x250) < t14 + 0x40) goto LAB_00052de4;
        }
        t5 = t9 + 0x10;
        if (t13 < 0x12) {
          switch(t13) {
          case 1:
          case 2:
          case 3:
          case 5:
          case 8:
          case 9:
          case 0xf:
          case 0x10:
            goto switchD_00052e18_caseD_1;
          case 4:
            if (t9 <= t5) {
              t19 = t9[8];
              t0 = *(uint8_t *)((long)t9 + 0x13);
              t17 = t9[9];
              t18 = t9[10];
              t2 = sk_global_get(0x6af8d8,2,5);
              if (t2 + 0x238U <= t2 + 0x288U) {
                if (*(char *)(t2 + 0x278) != '\0') {
                  *(uint8_t *)(t2 + 0x279) = 0;
                    
                  sk_xrt_abort(sk_str_83);
                }
                t14 = ((unsigned long)(uint8_t)t17 << 0x10 | (unsigned long)t0 << 0x18 | (unsigned long)t19) << 0xc |
                         (unsigned long)(uint8_t)t18 << 0x2c;
                if (*(long *)(t2 + 0x238) == 0 && *(unsigned long *)(t2 + 0x240) == 0) {
                  *(unsigned long *)(t2 + 0x238) = t14;
                  *(unsigned long *)(t2 + 0x240) = t14 + 0x4000;
                }
                else if (*(unsigned long *)(t2 + 0x240) == t14) {
                  *(unsigned long *)(t2 + 0x240) = t14 + 0x4000;
                }
                else if ((*(uint8_t *)(t2 + 0x27a) & 1) == 0) {
                  *(uint8_t *)(t2 + 0x27a) = 1;
                  *(unsigned long *)(t2 + 0x280) = t14;
                }
                goto LAB_00052ff4;
              }
            }
            goto LAB_000532f0;
          case 6:
            if (t5 < t9) goto LAB_000532f0;
            t2 = sk_global_get(0x6af8d8,2,5);
            *(unsigned long *)(t2 + 0x288) = t14;
            break;
          case 7:
            if (t5 < t9) goto LAB_000532f0;
            t2 = sk_global_get(0x6af8d8,2,5);
            *(unsigned long *)(t2 + 0x290) = t14;
            break;
          case 10:
            if (t5 < t9) goto LAB_000532f0;
            t2 = sk_global_get(0x6af8d8,2,5);
            t7 = (unsigned long *)(t2 + 0x38U) + sk_global_066 * 2;
            if (((t7 < (unsigned long *)(t2 + 0x38U)) || ((unsigned long *)(t2 + 0x238U) < t7 + 2)
                ) || (t7 + 2 < t7)) goto LAB_000532f0;
            t19 = t9[8];
            *t7 = t14;
            *(unsigned short *)(t7 + 1) = CONCAT11(*(uint8_t *)((long)t9 + 0x11),(uint8_t)t19);
            sk_global_066 = sk_global_066 + 1;
            break;
          case 0xb:
            if (t5 < t9) goto LAB_000532f0;
            t2 = sk_global_get(0x6af8d8,2,5);
            *(unsigned long *)(t2 + 0x2a0) = t14;
            break;
          case 0xc:
            *(unsigned long *)(t1 + 0x28) = t14;
            *(uint64_t *)(t1 + 0x30) = 0;
            break;
          case 0xd:
            t12 = ((unsigned long)(uint8_t)t9[9] << 0x10 |
                      (unsigned long)*(uint8_t *)((long)t9 + 0x13) << 0x18 | (unsigned long)t9[8]) << 0xc |
                     (unsigned long)(uint8_t)t9[10] << 0x2c;
            if (*(unsigned long *)(t1 + 0x20) <= t12) {
              *(unsigned long *)(t1 + 0x18) = t14;
              *(unsigned long *)(t1 + 0x20) = t12;
            }
            break;
          case 0xe:
            t12 = ((unsigned long)(uint8_t)t9[9] << 0x10 |
                      (unsigned long)*(uint8_t *)((long)t9 + 0x13) << 0x18 | (unsigned long)t9[8]) << 0xc |
                     (unsigned long)(uint8_t)t9[10] << 0x2c;
            if (*(unsigned long *)(t1 + 0x10) <= t12) {
              *(unsigned long *)(t1 + 8) = t14;
              *(unsigned long *)(t1 + 0x10) = t12;
            }
            break;
          case 0x11:
            if (t5 < t9) goto LAB_000532f0;
LAB_00052ff4:
            sk_boot_putc(t9);
          }
        }
        else {
switchD_00052e18_caseD_1:
          if (t20 == t13) {
            if (t5 < t9) goto LAB_000532f0;
            t2 = sk_global_get(0x6af8d8,2,5);
            *(unsigned long *)(t2 + 0x2a8) = t14;
          }
          else if (t10 == t13) {
            if (t5 < t9) goto LAB_000532f0;
            t2 = sk_global_get(0x6af8d8,2,5);
            *(unsigned long *)(t2 + 0x298) = t14;
          }
          else if (t11 == t13) {
            if (t5 < t9) goto LAB_000532f0;
            sk_tcb_ai(t9);
            t7 = (unsigned long *)sk_boot_arg();
            if (t7 + 1 < t7) goto LAB_000532f0;
            *t7 = (unsigned long)(uint8_t)t9[1] << 0x10 | (unsigned long)*(uint8_t *)((long)t9 + 3) << 0x18
                       | (unsigned long)*t9 | (unsigned long)*(uint64_t *)(t9 + 2) << 0x20;
          }
          else {
            if (t13 != 5) goto switchD_00052e18_caseD_0;
            if (t5 < t9) goto LAB_000532f0;
            t2 = sk_global_get(0x6af8d8,2,5);
            t3 = *(long *)(t2 + 0x628);
            t7 = (unsigned long *)(t2 + 0x2c8U) + t3 * 3;
            if (t7 < (unsigned long *)(t2 + 0x2c8U)) goto LAB_000532f0;
            if (((unsigned long *)(t2 + 0x628U) < t7 + 3) || (t7 + 3 < t7))
            goto LAB_000532f0;
            t16 = *(uint64_t *)(t9 + 8);
            *t7 = t14;
            t7[1] = (unsigned long)t16;
            t8 = t9 + 0xc;
            if ((t5 < t8) || (t8 < t9)) goto LAB_000532f0;
            *(uint8_t *)(t7 + 2) = (uint8_t)*t8 & 1;
            *(unsigned long *)(t2 + 0x628U) = t3 + 1;
          }
        }
switchD_00052e18_caseD_0:
        t15 = t15 + 1;
        t9 = t9 + 0x10;
      } while (t15 < ((unsigned long)(uint8_t)t6[1] << 0x10 |
                         (unsigned long)*(uint8_t *)((long)t6 + 3) << 0x18 | (unsigned long)*t6 |
                        (unsigned long)((unsigned int)(uint8_t)t6[3] << 0x10 |
                                (unsigned int)*(uint8_t *)((long)t6 + 7) << 0x18 | (unsigned int)t6[2]) <<
                        0x20));
    }
    t6 = (unsigned short *)
              ((unsigned long)(uint8_t)t6[5] << 0x10 | (unsigned long)*(uint8_t *)((long)t6 + 0xb) << 0x18 |
               (unsigned long)t6[4] |
              (unsigned long)((unsigned int)(uint8_t)t6[7] << 0x10 | (unsigned int)*(uint8_t *)((long)t6 + 0xf) << 0x18
                     | (unsigned int)t6[6]) << 0x20);
  }
LAB_000532f0:
                    
  t4 = (sk_code_t )sk_break(0x5519,0x532f4);
  (*t4)();
}




/* FUN_000533ec @ 0x533ec   (est. sk_cpu_irq)
 * Ghidra: undefined8 FUN_000533ec(void)
 * sk_cpu_irq: cL4 sk cpu irq operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

uint64_t sk_cpu_irq(void)
{
  long t0;
  
  t0 = sk_global_get(0x6af8d8,2,5);
  return *(uint64_t *)(t0 + 0x2a0);
}




/* FUN_00053418 @ 0x53418   (est. sk_cpu_irq2)
 * Ghidra: undefined8 FUN_00053418(void)
 * sk_cpu_irq2: cL4 sk cpu irq2 operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

uint64_t sk_cpu_irq2(void)
{
  long t0;
  
  t0 = sk_global_get(0x6af8d8,2,5);
  return *(uint64_t *)(t0 + 0x288);
}




/* FUN_00053444 @ 0x53444   (est. sk_cpu_irq3)
 * Ghidra: undefined8 FUN_00053444(void)
 * sk_cpu_irq3: cL4 sk cpu irq3 operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

uint64_t sk_cpu_irq3(void)
{
  long t0;
  
  t0 = sk_global_get(0x6af8d8,2,5);
  return *(uint64_t *)(t0 + 0x2a8);
}




/* FUN_00053470 @ 0x53470   (est. sk_cpu_irq4)
 * Ghidra: void FUN_00053470(void)
 * sk_cpu_irq4: cL4 sk cpu irq4 operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_cpu_irq4(void)
{
  sk_global_get(0x6aff18,2,4);
  return;
}




/* FUN_00053484 @ 0x53484   (est. sk_cpu_irq5)
 * Ghidra: undefined8 FUN_00053484(long arg1)
 * sk_cpu_irq5: cL4 sk cpu irq5 operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

uint64_t sk_cpu_irq5(long arg1)
{
  long t0;
  
  if (arg1 != 0) {
    return 0;
  }
  t0 = sk_global_get(0x6af8d8,2,5);
  return *(uint64_t *)(t0 + 0x298);
}




/* FUN_000534c0 @ 0x534c0   (est. sk_cpu_irq6)
 * Ghidra: undefined8 FUN_000534c0(void)
 * sk_cpu_irq6: cL4 sk cpu irq6 operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

uint64_t sk_cpu_irq6(void)
{
  long t0;
  
  t0 = sk_global_get(0x6af8d8,2,5);
  return *(uint64_t *)(t0 + 0x628);
}




/* FUN_000534ec @ 0x534ec   (est. sk_cpu_irq_slot)
 * Ghidra: undefined8 FUN_000534ec(long arg1,undefined8 *arg2,uint8_t *arg3)
 * sk_cpu_irq_slot: cL4 sk cpu irq slot operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

uint64_t sk_cpu_irq_slot(long arg1,uint64_t *arg2,uint8_t *arg3)
{
  uint64_t t3;
  sk_code_t t1;
  long t0;
  uint64_t *t2;
  
  t0 = sk_global_get(0x6af8d8,2,5);
  t2 = (uint64_t *)(t0 + 0x2c8U) + arg1 * 3;
  if (((uint64_t *)(t0 + 0x2c8U) <= t2 && t2 + 3 <= (uint64_t *)(t0 + 0x628U)) &&
      t2 <= t2 + 3) {
    t3 = t2[1];
    *arg2 = *t2;
    *arg3 = *(uint8_t *)(t2 + 2);
    return t3;
  }
                    
  t1 = (sk_code_t )sk_break(0x5519,0x53568);
  (*t1)();
}




/* FUN_00053568 @ 0x53568   (est. sk_boot_done)
 * Ghidra: undefined8 FUN_00053568(void)
 * sk_boot_done: cL4 sk boot done operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

uint64_t sk_boot_done(void)
{
  sk_code_t t0;
  uint64_t *t1;
  uint64_t t2;
  
  t1 = (uint64_t *)sk_boot_arg();
  t2 = 0;
  if (t1 != (uint64_t *)0x0) {
    if (t1 + 1 < t1) {
                    
      t0 = (sk_code_t )sk_break(0x5519,0x53598);
      (*t0)();
    }
    t2 = *t1;
  }
  return t2;
}




/* FUN_00053598 @ 0x53598   (est. sk_boot_arg)
 * Ghidra: ulong FUN_00053598(long arg1)
 * sk_boot_arg: cL4 sk boot arg operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

unsigned long sk_boot_arg(long arg1)
{
  unsigned long t3;
  sk_code_t t2;
  long t0;
  long t1;
  
  if (arg1 == 1) {
    t1 = 0x2b8;
  }
  else {
    if (arg1 == 2) {
      t1 = sk_global_get(0x6af8d8,2,5);
      t3 = t1 + 0x2c0;
      if (t3 == 0) {
        return 0;
      }
      if ((t3 <= t1 + 0x2c8U) && (t1 + 0x2b0U <= t3)) {
        return t3;
      }
                    
      t2 = (sk_code_t )sk_break(0x5519,0x53604);
      (*t2)();
    }
    if (arg1 != 3) {
      return 0;
    }
    t1 = 0x2b0;
  }
  t0 = sk_global_get(0x6af8d8,2,5);
  return t0 + t1;
}




/* FUN_00053634 @ 0x53634   (est. sk_boot_triple)
 * Ghidra: void FUN_00053634(ulong *arg1,long *arg2,ulong *arg3)
 * sk_boot_triple: cL4 sk boot triple operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_boot_triple(unsigned long *arg1,long *arg2,unsigned long *arg3)
{
  sk_code_t t2;
  long t0;
  unsigned long t3;
  unsigned long t4;
  long t1;
  
  t0 = sk_global_get(0x6af8d8,2,5);
  if (t0 + 0x238U <= t0 + 0x288U) {
    if (*(char *)(t0 + 0x278) != '\x01') {
      *(uint8_t *)(t0 + 0x279) = 1;
                    
      sk_xrt_abort(sk_str_83);
    }
    *(uint8_t *)(t0 + 0x278) = 2;
    t3 = *(unsigned long *)(t0 + 0x238);
    t4 = *(unsigned long *)(t0 + 0x240);
    if ((((((unsigned int)t3 | (unsigned int)t4) & 0x3fff) == 0) && (t4 == *(unsigned long *)(t0 + 0x270))) &&
       (t3 <= *(unsigned long *)(t0 + 0x268) && *(unsigned long *)(t0 + 0x268) <= t4)) {
      *arg1 = t3;
      t1 = *(long *)(t0 + 0x268);
      *arg2 = t1;
      *arg3 = (unsigned long)(*(long *)(t0 + 0x270) - t1) >> 6;
      return;
    }
    sk_rt_wait();
  }
                    
  t2 = (sk_code_t )sk_break(0x5519,0x536f8);
  (*t2)();
}




/* FUN_0005371c @ 0x5371c   (est. sk_boot_state)
 * Ghidra: void FUN_0005371c(void)
 * sk_boot_state: cL4 sk boot state operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_boot_state(void)
{
  sk_code_t t1;
  long t0;
  unsigned long t2;
  
  t0 = sk_global_get(0x6af8d8,2,5);
  if (t0 + 0x288U < t0 + 0x238U) {
                    
    t1 = (sk_code_t )sk_break(0x5519,0x537a0);
    (*t1)();
  }
  if (*(char *)(t0 + 0x278) == '\x02') {
    *(uint8_t *)(t0 + 0x278) = 3;
    for (t2 = *(unsigned long *)(t0 + 600); t2 < *(unsigned long *)(t0 + 0x260); t2 = t2 + 0x40) {
      sk_xrt_init(t2);
    }
    return;
  }
  *(uint8_t *)(t0 + 0x279) = 2;
                    
  sk_xrt_abort(sk_str_83);
}




/* FUN_000537c4 @ 0x537c4   (est. sk_boot_list)
 * Ghidra: ulong * FUN_000537c4(void)
 * sk_boot_list: cL4 sk boot list operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

unsigned long * sk_boot_list(void)
{
  unsigned long t3;
  sk_code_t t1;
  long t0;
  unsigned long *t2;
  
  t0 = sk_global_get(0x6af8d8,2,5);
  if (t0 + 0x288U < t0 + 0x238U) {
                    
    t1 = (sk_code_t )sk_break(0x5519,0x53830);
    (*t1)();
  }
  if (*(char *)(t0 + 0x278) == '\x01') {
    t2 = *(unsigned long **)(t0 + 0x268);
    if (t2 < *(unsigned long **)(t0 + 0x270)) {
      *(unsigned long **)(t0 + 0x268) = t2 + 8;
      return t2;
    }
    t0 = sk_rt_barrier();
    t3 = (((unsigned long)*(uint8_t *)(t0 + 0x12) << 0x10 | (unsigned long)*(uint8_t *)(t0 + 0x13) << 0x18 |
             (unsigned long)*(unsigned short *)(t0 + 0x10)) << 0xc | (unsigned long)*(uint8_t *)(t0 + 0x14) << 0x2c) +
            0x4000;
    t2 = (unsigned long *)sk_global_get(0x6af8d8,2,5);
    if (*t2 < t3) {
      *t2 = t3;
    }
    return t2;
  }
  *(uint8_t *)(t0 + 0x279) = 1;
                    
  sk_xrt_abort(sk_str_83);
}




/* FUN_00053858 @ 0x53858   (est. sk_boot_putc)
 * Ghidra: void FUN_00053858(long arg1)
 * sk_boot_putc: cL4 sk boot putc operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_boot_putc(long arg1)
{
  unsigned long t1;
  unsigned long *t0;
  
  t1 = (((unsigned long)*(uint8_t *)(arg1 + 0x12) << 0x10 | (unsigned long)*(uint8_t *)(arg1 + 0x13) << 0x18 |
           (unsigned long)*(unsigned short *)(arg1 + 0x10)) << 0xc | (unsigned long)*(uint8_t *)(arg1 + 0x14) << 0x2c) +
          0x4000;
  t0 = (unsigned long *)sk_global_get(0x6af8d8,2,5);
  if (*t0 < t1) {
    *t0 = t1;
  }
  return;
}




/* FUN_000538c8 @ 0x538c8   (est. sk_boot_puts)
 * Ghidra: int FUN_000538c8(undefined8 arg1,ulong arg2,ulong arg3,undefined8 arg4)
 * sk_boot_puts: cL4 sk boot puts operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

int sk_boot_puts(uint64_t arg1,unsigned long arg2,unsigned long arg3,uint64_t arg4)
{
  bool t0;
  unsigned long t5;
  sk_code_t t4;
  int t1;
  long t3;
  unsigned long t6;
  unsigned long t7;
  int t2;
  
  t3 = sk_strchr(arg2,0);
  t7 = arg3;
  if ((t3 == 0) || (t7 = t3 - arg2, t7 <= arg3)) {
    t2 = 0;
    while( true ) {
      if (t7 == 0) {
        return t2;
      }
      sk_trace(arg1,arg4);
      t3 = sk_strchr(arg2,10,t7);
      t5 = t7;
      if (t3 != 0) {
        t5 = t3 - arg2;
      }
      if (t7 < t5) break;
      t6 = sk_log_fmt(arg2,t5,1,arg4);
      t2 = t2 + (int)t6;
      if (t6 < t5) {
        return t2;
      }
      t1 = sk_hexdump(10,arg4);
      if (t1 == -1) {
        return t2;
      }
      t6 = arg2 + t5 + 1;
      if ((arg2 + t7 < t6) ||
         (t7 = t7 - (t5 + 1), t0 = t6 < arg2, arg2 = t6, t0)) break;
    }
  }
                    
  t4 = (sk_code_t )sk_break(0x5519,0x539a4);
  (*t4)();
}




/* FUN_000539bc @ 0x539bc   (est. thunk_current)
 * Ghidra: undefined8 thunk_FUN_00060524(void)
 * thunk_current: cL4 thunk current operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

uint64_t thunk_FUN_00060524(void)
{
  long t0;
  
  t0 = sk_tpidr;
  return *(uint64_t *)(t0 + 8);
}




/* FUN_000539c0 @ 0x539c0   (est. sk_obj_cmp)
 * Ghidra: bool FUN_000539c0(long arg1,long arg2)
 * sk_obj_cmp: cL4 sk obj cmp operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

bool sk_obj_cmp(long arg1,long arg2)
{
  return arg1 == arg2;
}




/* FUN_000539cc @ 0x539cc   (est. sk_obj_get)
 * Ghidra: undefined8 FUN_000539cc(ulong arg1)
 * sk_obj_get: cL4 sk obj get operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

uint64_t sk_obj_get(unsigned long arg1)
{
  sk_code_t t0;
  
  if (arg1 <= arg1 + 0x10) {
    sk_lock_release(arg1,1);
    return 0;
  }
                    
  t0 = (sk_code_t )sk_break(0x5519,0x539fc);
  (*t0)();
}




/* FUN_000539fc @ 0x539fc   (est. sk_obj_put)
 * Ghidra: void FUN_000539fc(ulong arg1)
 * sk_obj_put: cL4 sk obj put operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_obj_put(unsigned long arg1)
{
  sk_code_t t0;
  
  if (arg1 <= arg1 + 0x10) {
    sk_lock_release(arg1,1);
    return;
  }
                    
  t0 = (sk_code_t )sk_break(0x5519,0x53a14);
  (*t0)();
}




/* FUN_00053a14 @ 0x53a14   (est. sk_exc_entry)
 * Ghidra: undefined8 FUN_00053a14(undefined8 *arg1)
 * sk_exc_entry: cL4 sk exc entry operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

uint64_t sk_exc_entry(uint64_t *arg1)
{
  sk_code_t t0;
  
  if (arg1 <= arg1 + 2) {
    *arg1 = 0;
    arg1[1] = 0;
    return 0;
  }
                    
  t0 = (sk_code_t )sk_break(0x5519,0x53a30);
  (*t0)();
}




/* FUN_00053a30 @ 0x53a30   (est. sk_cpu_boot_get)
 * Ghidra: undefined8 FUN_00053a30(ulong arg1)
 * sk_cpu_boot_get: cL4 sk cpu boot get operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

uint64_t sk_cpu_boot_get(unsigned long arg1)
{
  sk_code_t t0;
  
  if (arg1 <= arg1 + 0x10) {
    sk_lock_release(arg1,0);
    return 0;
  }
                    
  t0 = (sk_code_t )sk_break(0x5519,0x53a60);
  (*t0)();
}




/* FUN_00053a60 @ 0x53a60   (est. sk_cpu_cmp)
 * Ghidra: uint32_t FUN_00053a60(ulong arg1,ulong arg2)
 * sk_cpu_cmp: cL4 sk cpu cmp operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

uint32_t sk_cpu_cmp(unsigned long arg1,unsigned long arg2)
{
  sk_code_t t1;
  int t0;
  uint32_t t2;
  
  if ((arg1 <= arg1 + 0x10) && (arg2 <= arg2 + 0x10)) {
    t0 = sk_lock_acquire();
    t2 = 0;
    if (t0 == 0) {
      t2 = 4;
    }
    return t2;
  }
                    
  t1 = (sk_code_t )sk_break(0x5519,0x53aa0);
  (*t1)();
}




/* FUN_00053aa0 @ 0x53aa0   (est. sk_cpu_start)
 * Ghidra: void FUN_00053aa0(void)
 * sk_cpu_start: cL4 sk cpu start operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_cpu_start(void)
{
  return;
}




/* FUN_00053aa4 @ 0x53aa4   (est. sk_cpu_startup)
 * Ghidra: undefined8 FUN_00053aa4(undefined8 *arg1,unsigned int arg2)
 * sk_cpu_startup: cL4 sk cpu startup operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

uint64_t sk_cpu_startup(uint64_t *arg1,unsigned int arg2)
{
  sk_code_t t0;
  
  if (arg1 <= arg1 + 2) {
    *arg1 = 0;
    arg1[1] = 0;
    if ((arg2 >> 1 & 1) != 0) {
      sk_lock_set_mode(arg1,0x100);
    }
    return 0;
  }
                    
  t0 = (sk_code_t )sk_break(0x5519,0x53ae0);
  (*t0)();
}




/* FUN_00053ae0 @ 0x53ae0   (est. sk_cpu_init)
 * Ghidra: void FUN_00053ae0(ulong arg1)
 * sk_cpu_init: cL4 sk cpu init operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_cpu_init(unsigned long arg1)
{
  sk_code_t t0;
  
  if (arg1 <= arg1 + 0x10) {
    sk_lock_prepare();
    return;
  }
                    
  t0 = (sk_code_t )sk_break(0x5519,0x53af4);
  (*t0)();
}




/* FUN_00053af4 @ 0x53af4   (est. sk_cpu_ready)
 * Ghidra: uint32_t FUN_00053af4(ulong arg1)
 * sk_cpu_ready: cL4 sk cpu ready operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

uint32_t sk_cpu_ready(unsigned long arg1)
{
  sk_code_t t1;
  int t0;
  uint32_t t2;
  
  if (arg1 <= arg1 + 0x10) {
    t0 = sk_lock_try();
    t2 = 0;
    if (t0 == 0) {
      t2 = 3;
    }
    return t2;
  }
                    
  t1 = (sk_code_t )sk_break(0x5519,0x53b28);
  (*t1)();
}




/* FUN_00053b28 @ 0x53b28   (est. sk_cpu_wait)
 * Ghidra: undefined8 FUN_00053b28(ulong arg1)
 * sk_cpu_wait: cL4 sk cpu wait operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

uint64_t sk_cpu_wait(unsigned long arg1)
{
  sk_code_t t0;
  
  if (arg1 <= arg1 + 0x10) {
    sk_unlock();
    return 0;
  }
                    
  t0 = (sk_code_t )sk_break(0x5519,0x53b54);
  (*t0)();
}




/* FUN_00053db8 @ 0x53db8   (est. sk_cnode_create)
 * Ghidra: undefined8 FUN_00053db8(ulong *arg1,ulong arg2,unsigned int arg3,int arg4,long *arg5,ulong arg6, unsigned int arg7)
 * sk_cnode_create: cL4 sk cnode create operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

uint64_t sk_cnode_create(unsigned long *arg1,unsigned long arg2,unsigned int arg3,int arg4,long *arg5,unsigned long arg6, unsigned int arg7)
{
  uint64_t t4;
  undefined3 t9;
  uint16_t t10;
  sk_code_t t2;
  char t0;
  unsigned long t11;
  uint8_t *t1;
  unsigned long t12;
  uint32_t *t3;
  uint64_t t5;
  uint8_t t6;
  unsigned int t7;
  unsigned int t8;
  uint8_t stk0 [16];
  uint64_t stk6;
  unsigned long stk8;
  unsigned long stk5;
  uint64_t stk4;
  uint64_t stk3;
  unsigned long stk2;
  uint64_t stk1;
  uint64_t stk7;
  
  stk8 = 0;
  stk6 = 0;
  stk4 = 0;
  stk5 = 0;
  if ((((arg5 == (long *)0x0) || (0x3e < arg3)) || (arg1 == (unsigned long *)0x0)) ||
     ((arg6 & 1) == 0)) goto LAB_00053f50;
  if (arg5 + 2 < arg5) {
LAB_0005402c:
                    
    t2 = (sk_code_t )sk_break(0x5519,0x54030);
    (*t2)();
  }
  if (*arg5 != 0) goto LAB_00053f50;
  stk6 = 0x11;
  if (arg4 - 1U < 6) {
    t6 = (uint8_t)*(uint32_t *)(&sk_global_003 + (unsigned long)(arg4 - 1U) * 4);
  }
  else {
    t6 = 2;
  }
  stk4._0_2_ = (uint16_t)CONCAT41(0x20000000,t6);
  t10 = (uint16_t)stk4;
  stk4._0_3_ = CONCAT12((char)arg3,(uint16_t)stk4);
  t4 = CONCAT23(0x2000,(undefined3)stk4);
  stk4 = (unsigned long)t4;
  stk5 = arg2;
  if ((arg7 >> 3 & 1) == 0) {
    t8 = 0;
    t9 = (undefined3)(t4 >> 0x10);
    stk4._0_2_ = CONCAT11((arg7 & 0x10) == 0,t6);
    stk4 = (unsigned long)CONCAT32(t9,(uint16_t)stk4);
    if ((arg2 >> 0x1e == 0) && ((arg7 & 0x10) == 0)) {
      stk4 = (unsigned long)CONCAT32(t9,t10);
      if (sk_global_067 == 0) {
        stk1 = 0x4000;
        stk7 = 0x2000000102;
        stk3 = 0x11;
        stk2 = 0;
        stk0 = sk_vspace_get_ops();
        t11 = (**(sk_code_t *)(stk0._8_8_ + 0x30))(stk0._0_8_,8,&stk3,0x6b0330,0,&stk3);
        t11 = t11 & 0xff;
        if (t11 != 0) {
          if ((((uint64_t *)0x64cb3f < &sk_global_034 + t11) &&
              (&sk_global_035 + t11 < (uint64_t *)0x64cb81)) &&
             (&sk_global_034 + t11 <= &sk_global_035 + t11)) {
            sk_rt_sync();
          }
          goto LAB_0005402c;
        }
        sk_global_067 = stk2;
      }
      t8 = 0x20000;
      stk8 = sk_global_067;
    }
  }
  else {
    stk8 = *arg1;
    t8 = 1;
  }
  t11 = stk8;
  if ((arg7 & 1) == 0) goto LAB_00053f50;
  t8 = ((unsigned int)arg6 & 2 | (unsigned int)(arg6 >> 2) & 1) << 3 | t8;
  if ((arg7 >> 1 & 1) == 0) {
    t8 = t8 | 0x20;
  }
  else {
    if ((arg7 >> 5 & 1) == 0) {
      t7 = 0x2010000;
    }
    else {
      t1 = (uint8_t *)sk_tcb_cur();
      if (((*t1 & 1) == 0) && (t12 = sk_ctx_dbg(), (t12 & 1) != 0)) {
        t8 = t8 | 0x10000;
        goto LAB_00053f48;
      }
      t7 = 0x10020;
    }
    t8 = t8 | t7;
  }
LAB_00053f48:
  if (!CARRY8(t11,arg2)) {
    stk0 = sk_vspace_get_ops();
    t0 = (**(sk_code_t *)(stk0._8_8_ + 0x30))
                      (stk0._0_8_,t8 | (arg7 & 4) << 0x14,&stk6,arg5,0,0);
    if (t0 != '\0') {
      t5 = sk_cnode_check();
      return t5;
    }
    if (arg5[1] != 0) {
      (**(sk_code_t *)(arg5[1] + 8))(*arg5,&stk6);
      *arg1 = stk8;
      t3 = (uint32_t *)sk_thread_state();
      *t3 = 0;
      return 1;
    }
                    
    sk_tcb_abort(0);
  }
LAB_00053f50:
  t3 = (uint32_t *)sk_thread_state();
  *t3 = 0x16;
  return 0;
}




/* FUN_00054034 @ 0x54034   (est. sk_cnode_check)
 * Ghidra: bool FUN_00054034(int arg1)
 * sk_cnode_check: cL4 sk cnode check operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

bool sk_cnode_check(int arg1)
{
  uint32_t t2;
  bool t0;
  uint32_t *t1;
  uint32_t t3;
  
  t3 = 0x2d;
  if (arg1 != 5) {
    t3 = 0x16;
  }
  t2 = 0;
  if (arg1 != 0) {
    t2 = t3;
  }
  t0 = 1 < arg1 - 2U;
  t3 = 0xc;
  if (t0) {
    t3 = t2;
  }
  t1 = (uint32_t *)sk_thread_state();
  *t1 = t3;
  return t0 && arg1 == 0;
}




/* FUN_00054094 @ 0x54094   (est. sk_cnode_resolve)
 * Ghidra: undefined8 FUN_00054094(long arg1,long arg2,uint8_t (*arg3) [16])
 * sk_cnode_resolve: cL4 sk cnode resolve operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

uint64_t sk_cnode_resolve(long arg1,long arg2,uint8_t (*arg3) [16])
{
  char t0;
  uint64_t t4;
  uint32_t *t2;
  long t1;
  uint64_t *t3;
  uint8_t stk0 [16];
  uint64_t stk2;
  long lStack_48;
  long stk1;
  uint64_t stk3;
  
  if (arg3 == (uint8_t (*) [16])0x0) {
    stk0 = sk_vspace_get_ops();
    stk0 = (**(sk_code_t *)(stk0._8_8_ + 0x38))(stk0._0_8_,arg1,0,0);
  }
  else {
    stk0 = *arg3;
  }
  t3 = stk0._8_8_;
  t1 = stk0._0_8_;
  lStack_48 = 0;
  stk2 = 0;
  stk3 = 0;
  stk1 = 0;
  if (t1 != 0) {
    if (t3 == (uint64_t *)0x0) {
                    
      sk_tcb_abort();
    }
    (*(sk_code_t )t3[1])(t1,&stk2);
    if ((lStack_48 == arg1) && (stk1 == arg2)) {
      t0 = (*(sk_code_t )*t3)(t1);
      if (t0 != '\0') {
        t4 = sk_cnode_check();
        return t4;
      }
      t2 = (uint32_t *)sk_thread_state(0);
      *t2 = 0;
      return 1;
    }
  }
  t2 = (uint32_t *)sk_thread_state();
  *t2 = 0x16;
  return 0;
}




/* FUN_0005417c @ 0x5417c   (est. sk_cnode_op)
 * Ghidra: undefined8 FUN_0005417c(ulong arg1,ulong arg2,uint8_t (*arg3) [16],unsigned int arg4)
 * sk_cnode_op: cL4 sk cnode op operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

uint64_t sk_cnode_op(unsigned long arg1,unsigned long arg2,uint8_t (*arg3) [16],unsigned int arg4)
{
  long t2;
  char t0;
  unsigned int t9;
  int t1;
  uint32_t *t7;
  uint8_t *t6;
  uint64_t t10;
  uint32_t t11;
  long t5;
  long t3;
  unsigned long t8;
  long t4;
  uint8_t stk0 [16];
  long stk2;
  unsigned long stk1 [5];
  
  if (arg3 == (uint8_t (*) [16])0x0) {
    stk0 = sk_vspace_get_ops();
    stk0 = (**(sk_code_t *)(stk0._8_8_ + 0x38))(stk0._0_8_,arg1,0,0);
  }
  else {
    stk0 = *arg3;
  }
  t3 = stk0._8_8_;
  t5 = stk0._0_8_;
  stk1[2] = 0;
  stk1[1] = 0;
  stk1[4] = 0;
  stk1[3] = 0;
  if (t5 == 0) {
LAB_00054210:
    t7 = (uint32_t *)sk_thread_state();
    t11 = 0x16;
LAB_00054220:
    t10 = 0;
    *t7 = t11;
  }
  else {
    if (t3 == 0) goto LAB_0005434c;
    t9 = (**(sk_code_t *)(t3 + 8))(t5,stk1 + 1);
    if ((((arg1 < stk1[2]) || (stk1[3] < arg2)) ||
        (stk1[3] + stk1[2] <= arg1)) || (stk1[3] + stk1[2] < arg2 + arg1))
    goto LAB_00054210;
    t8 = arg1 - stk1[2] & 0xffffffffffffc000;
    t4 = (arg2 + 0x3fff + (arg1 - stk1[2]) & 0xffffffffffffc000) - t8;
    if ((arg4 & 0xc) == 0) {
LAB_000542e8:
      if ((arg4 & 3) == 0) {
        t0 = '\0';
      }
      else {
        t2 = 0x20;
        if ((arg4 & 1) != 0) {
          t2 = 0x30;
        }
        stk2 = t4;
        stk1[0] = t8;
        t0 = (**(sk_code_t *)(t3 + t2))(t5,stk1,&stk2);
        if ((stk1[0] != t8) || (stk2 != t4)) {
          sk_rt_sync2();
LAB_0005434c:
                    
          sk_tcb_abort();
        }
      }
    }
    else {
      if ((t9 >> 0x10 & 1) == 0) {
        t7 = (uint32_t *)sk_thread_state();
        t11 = 0x2d;
        goto LAB_00054220;
      }
      t0 = (**(sk_code_t *)(t3 + 0x50))(t5,arg4 >> 1 & 4,t8,t4);
      t6 = (uint8_t *)sk_tcb_cur();
      if ((*t6 & 1) == 0) {
        t1 = sk_ctx_dbg();
      }
      else {
        t1 = 0;
      }
      if (t0 == '\0') {
        if ((arg4 & 4) == 0) {
          t1 = 1;
        }
        if (t1 == 0) {
          arg4 = 2;
        }
        goto LAB_000542e8;
      }
    }
    t10 = sk_cnode_check(t0);
  }
  return t10;
}




/* FUN_00054350 @ 0x54350   (est. thunk_cpu)
 * Ghidra: undefined8 thunk_FUN_0005fd2c(ulong arg1)
 * thunk_cpu: cL4 thunk cpu operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

uint64_t thunk_FUN_0005fd2c(unsigned long arg1)
{
  sk_code_t t1;
  long t0;
  
  t0 = sk_current_thread();
  if ((*(uint8_t **)(t0 + 0x168) <= NULL) &&
     (NULL < *(uint8_t **)(t0 + 0x170))) {
    if (arg1 <= (unsigned long)((long)NULL - (long)*(uint8_t **)(t0 + 0x168)))
    {
      return 1;
    }
                    
    sk_xrt_abort(sk_str_101);
  }
                    
  t1 = (sk_code_t )sk_break(1,0x5fd90);
  (*t1)();
}




/* FUN_00054354 @ 0x54354   (est. sk_tcb_abort)
 * Ghidra: void FUN_00054354(void)
 * sk_tcb_abort: cL4 sk tcb abort operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_tcb_abort(void)
{
  int t0;
  uint64_t t1;
  
  t0 = sk_cnode_find(0xeb1a02bf914012ba);
  t1 = sk_current_thread();
  sk_ctx_panic(sk_str_80,0x3d,0xeb1a02bf914012ba,t1,1,0,0,0);
  if (t0 == 0) {
    sk_cnode_cur(0xeb1a02bf914012ba);
  }
                    
  sk_panic_msg(t1,sk_str_80);
}




/* FUN_000543c4 @ 0x543c4   (est. sk_tcb_x)
 * Ghidra: void FUN_000543c4(undefined8 arg1)
 * sk_tcb_x: cL4 sk tcb x operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_tcb_x(uint64_t arg1)
{
  sk_log_v(0xeb1a02bf914012ba,arg1,NULL);
                    
  sk_tcb_abort();
}




/* FUN_000543f4 @ 0x543f4   (est. sk_tcb_y)
 * Ghidra: void FUN_000543f4(undefined8 arg1,undefined8 arg2)
 * sk_tcb_y: cL4 sk tcb y operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_tcb_y(uint64_t arg1,uint64_t arg2)
{
                    
  sk_panic(0,arg1,arg2);
}




/* FUN_00054410 @ 0x54410   (est. thunk_cpu2)
 * Ghidra: void thunk_FUN_0006037c(void)
 * thunk_cpu2: cL4 thunk cpu2 operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void thunk_FUN_0006037c(void)
{
  sk_code_t t1;
  long t0;
  
  t0 = sk_current_thread();
  if (t0 + 0x104U <= t0 + 0x108U) {
    return;
  }
                    
  t1 = (sk_code_t )sk_break(0x5519,0x603ac);
  (*t1)();
}




/* FUN_00054414 @ 0x54414   (est. sk_tcb_z)
 * Ghidra: void FUN_00054414(long arg1,ulong arg2)
 * sk_tcb_z: cL4 sk tcb z operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_tcb_z(long arg1,unsigned long arg2)
{
  unsigned long t1;
  unsigned long t2;
  unsigned long t3;
  sk_code_t t0;
  unsigned long t4;
  long lStack_60;
  long lStack_58;
  
  t4 = 0;
  lStack_58 = -0x2c8502b44bfffed6;
  while( true ) {
    t2 = arg2 - t4;
    if (arg2 < t4 || t2 == 0) {
      if (lStack_58 == -0x2c8502b44bfffed6) {
        return;
      }
                    
      sk_noreturn_error();
    }
    t3 = sk_global_117 * 5;
    t1 = sk_global_117 * 0x280;
    sk_global_118 = sk_global_118 ^ sk_global_117;
    sk_global_117 =
         (sk_global_117 >> 0x28 | sk_global_117 << 0x18) ^ sk_global_118 << 0x10 ^ sk_global_118;
    sk_global_118 = sk_global_118 >> 0x1b | sk_global_118 << 0x25;
    lStack_60 = (t3 >> 0x39 | t1) * 9;
    if (7 < t2) {
      t2 = 8;
    }
    t1 = arg1 + t4;
    sk_memcpy2(t1,&lStack_60,t2);
    if (t1 + t2 < t1) break;
    t4 = t2 + t4;
  }
                    
  t0 = (sk_code_t )sk_break(0x5519,0x116d5c);
  (*t0)();
}




/* FUN_00054418 @ 0x54418   (est. sk_tcb_w)
 * Ghidra: ulong FUN_00054418(ulong arg1)
 * sk_tcb_w: cL4 sk tcb w operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

unsigned long sk_tcb_w(unsigned long arg1)
{
  long t0;
  unsigned long t1;
  unsigned long stk0;
  
  stk0 = arg1;
  t0 = sk_range_lookup(&stk0,0);
  if (t0 == 0) {
    t1 = 0xffff000000000000;
  }
  else {
    t1 = (unsigned long)*(unsigned short *)(t0 + 0x40) << 0x30;
  }
  return stk0 & 0xffffffffffff | t1;
}




/* FUN_00054464 @ 0x54464   (est. sk_tcb_v)
 * Ghidra: void FUN_00054464(long arg1)
 * sk_tcb_v: cL4 sk tcb v operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_tcb_v(long arg1)
{
  int t0;
  uint64_t t1;
  
  t1 = sk_current_thread();
  if ((arg1 == -0x14e5fd406ebfed46 || arg1 == -0x55e9fc042d7fffe4) &&
     (t0 = sk_trap(), t0 != 0)) {
    sk_trap2(t1,*(uint64_t *)(arg1 + 0x58));
    return;
  }
  sk_klog2(*(uint64_t *)(arg1 + 0x58));
  return;
}




/* FUN_000544d0 @ 0x544d0   (est. sk_cnode_find)
 * Ghidra: ulong FUN_000544d0(long arg1)
 * sk_cnode_find: cL4 sk cnode find operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

unsigned long sk_cnode_find(long arg1)
{
  int t0;
  uint64_t t1;
  unsigned long t2;
  
  t1 = sk_current_thread();
  if ((arg1 == -0x14e5fd406ebfed46 || arg1 == -0x55e9fc042d7fffe4) &&
     (t0 = sk_trap(), t0 != 0)) {
    t2 = sk_trap3(t1,*(uint64_t *)(arg1 + 0x58));
  }
  else {
    t0 = sk_klog3(*(uint64_t *)(arg1 + 0x58));
    t2 = (unsigned long)(t0 != 0);
  }
  return t2;
}




/* FUN_0005453c @ 0x5453c   (est. sk_cnode_cur)
 * Ghidra: void FUN_0005453c(long arg1)
 * sk_cnode_cur: cL4 sk cnode cur operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_cnode_cur(long arg1)
{
  int t0;
  uint64_t t1;
  
  t1 = sk_current_thread();
  if ((arg1 == -0x14e5fd406ebfed46 || arg1 == -0x55e9fc042d7fffe4) &&
     (t0 = sk_trap(), t0 != 0)) {
    sk_trap4(t1,*(uint64_t *)(arg1 + 0x58));
    return;
  }
  sk_klog4(*(uint64_t *)(arg1 + 0x58));
  return;
}




/* FUN_000545a8 @ 0x545a8   (est. sk_cnode_notify)
 * Ghidra: void FUN_000545a8(int arg1)
 * sk_cnode_notify: cL4 sk cnode notify operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_cnode_notify(int arg1)
{
  if (arg1 != 0) {
                    
    uRam000000000064cd88 = 0;
                    
    uRam000000000064cee8 = 0;
  }
  sk_klog(0x6ad700,2);
  sk_klog(0x6ad710,2);
  sk_klog(0x6ad720,2);
  sk_klog(0x6ad730,2);
  return;
}




/* FUN_00054610 @ 0x54610   (est. sk_tcb_cur)
 * Ghidra: void FUN_00054610(void)
 * sk_tcb_cur: cL4 sk tcb cur operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_tcb_cur(void)
{
  sk_global_get(0x6b04a8,2,2);
  return;
}




/* FUN_00054624 @ 0x54624   (est. sk_setup_cpu_regs)
 * Ghidra: uint8_t * FUN_00054624(long arg1)
 * sk_setup_cpu_regs: cL4 sk setup cpu regs operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

uint8_t * sk_setup_cpu_regs(long arg1)
{
  sk_code_t t2;
  unsigned long t3;
  long t0;
  unsigned long t4;
  long t1;
  
  t0 = 0;
  t3 = 0;
  sk_global_087 = 0;
  sk_global_093 = 0x400;
  do {
    t1 = *(long *)(arg1 + t0);
    if (t1 - 1U < 0x2b) {
      t4 = ((long *)(arg1 + t0))[1];
      switch(t1) {
      default:
        sk_global_068 = t4;
        break;
      case 2:
        sk_global_069 = t4;
        break;
      case 3:
        sk_global_070 = t4;
        break;
      case 4:
      case 5:
      case 6:
      case 10:
      case 0xb:
      case 0xd:
      case 0x19:
        break;
      case 7:
        sk_global_073 = t4;
        break;
      case 8:
        sk_global_074 = t4;
        break;
      case 9:
        sk_global_075 = t4;
        break;
      case 0xc:
        sk_global_076 = t4;
        break;
      case 0xe:
        sk_global_080 = t4;
        break;
      case 0xf:
        sk_global_081 = t4;
        break;
      case 0x10:
        sk_global_082 = t4;
        break;
      case 0x11:
        sk_global_083 = t4;
        break;
      case 0x12:
        sk_global_084 = t4;
        break;
      case 0x13:
        sk_global_077 = t4;
        break;
      case 0x14:
        sk_global_078 = t4;
        break;
      case 0x15:
        sk_global_047 = t4 == 0;
        sk_global_085 = t4;
        break;
      case 0x16:
        t3 = t4;
        break;
      case 0x17:
        sk_global_087 = t4;
        break;
      case 0x18:
        sk_global_048 = (uint8_t)t4;
        break;
      case 0x1a:
        sk_global_089 = t4;
        break;
      case 0x1b:
        sk_global_090 = t4;
        break;
      case 0x1c:
        sk_global_091 = t4;
        break;
      case 0x1d:
        sk_global_094 = t4;
      case 0x1e:
        sk_global_095 = t4;
        break;
      case 0x1f:
        sk_global_096 = t4;
        break;
      case 0x20:
        sk_global_079 = t4;
        break;
      case 0x21:
        sk_global_097 = t4;
        break;
      case 0x22:
        sk_global_098 = t4;
        break;
      case 0x23:
        sk_global_099 = t4;
        break;
      case 0x24:
        sk_global_100 = t4;
        break;
      case 0x25:
        sk_global_101 = t4;
        break;
      case 0x26:
        sk_global_102 = t4;
        break;
      case 0x27:
        sk_global_088 = t4;
        break;
      case 0x28:
        sk_global_071 = t4;
        break;
      case 0x29:
        sk_global_072 = t4;
        break;
      case 0x2a:
        sk_global_103 = t4;
        break;
      case 0x2b:
        sk_global_104 = t4;
      }
    }
    t0 = t0 + 0x10;
  } while (t0 != 0x400);
  sk_global_092 = arg1;
  if ((t3 != 0) && (t3 + sk_global_087 * 0x78 < t3 + 0x78 || t3 + 0x78 < t3)) {
                    
    t2 = (sk_code_t )sk_break(0x5519,0x548b4);
    (*t2)();
  }
  lRam000000000064ccd0 = arg1;
  sk_global_086 = t3;
                    
                    
  sk_register_global(0x64ccb8);
                    
                    
  puRam000000000064ccf0 = &sk_global_047;
  sk_register_global();
  return &sk_global_047;
}




/* FUN_00054960 @ 0x54960   (est. sk_tcb_set)
 * Ghidra: void FUN_00054960(undefined8 arg1)
 * sk_tcb_set: cL4 sk tcb set operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_tcb_set(uint64_t arg1)
{
  long t0;
  
  t0 = sk_lookup_thread_obj(2,6);
  if (t0 != 0) {
    return;
  }
  uRam000000000064cd10 = arg1;
                    
  sk_register_global();
  return;
}




/* FUN_000549ac @ 0x549ac   (est. sk_global_ensure)
 * Ghidra: void FUN_000549ac(void)
 * sk_global_ensure: cL4 sk global ensure operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_global_ensure(void)
{
  sk_global_get(0x6b04b0,2,6);
  return;
}




/* FUN_000549c0 @ 0x549c0   (est. sk_cnode_walk)
 * Ghidra: void FUN_000549c0(ulong arg1,long arg2)
 * sk_cnode_walk: cL4 sk cnode walk operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_cnode_walk(unsigned long arg1,long arg2)
{
  long t0;
  sk_code_t t1;
  unsigned long t2;
  
  if (arg2 != 0) {
    t0 = arg2 * 0x78;
    t2 = arg1;
    do {
      if (((t2 < arg1) || (arg1 + t0 < t2 + 0x78)) || (t2 + 0x78 < t2)) {
                    
        t1 = (sk_code_t )sk_break(0x5519,0x54a4c);
        (*t1)();
      }
      if (((unsigned int)*(uint64_t *)(t2 + 8) >> 7 & 1) != 0) {
        sk_cnode_map(t2,*(uint64_t *)(t2 + 0x38),*(uint64_t *)(t2 + 0x20),
                     *(uint64_t *)(t2 + 0x50),*(uint64_t *)(t2 + 0x48));
      }
      sk_list_push(t2);
      t2 = t2 + 0x78;
      arg2 = arg2 + -1;
    } while (arg2 != 0);
  }
  return;
}




/* FUN_00054a4c @ 0x54a4c   (est. sk_cnode_map)
 * Ghidra: void FUN_00054a4c(long arg1,undefined8 arg2,long arg3,undefined8 arg4,undefined8 arg5 ,undefined8 arg6)
 * sk_cnode_map: cL4 sk cnode map operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_cnode_map(long arg1,uint64_t arg2,long arg3,uint64_t arg4,uint64_t arg5 ,uint64_t arg6)
{
  sk_code_t t2;
  long t0;
  long t1;
  unsigned long t3;
  uint64_t stk1;
  uint64_t stk0;
  long lStack_58;
  
  t0 = sk_macho_vmrange(arg2);
  t1 = sk_macho_vmrange2(arg2);
  stk0 = 0;
  lStack_58 = 0;
  stk1 = 0;
  sk_macho_layout(arg2,&lStack_58,&stk0,&stk1);
  *(uint64_t *)(arg1 + 0x48) = arg5;
  *(uint64_t *)(arg1 + 0x50) = arg4;
  *(long *)(arg1 + 0x20) = arg3;
  *(long *)(arg1 + 0x28) = t0 + arg3;
  *(long *)(arg1 + 0x30) = t1 - t0;
  *(uint64_t *)(arg1 + 0x38) = arg2;
  *(long *)(arg1 + 0x58) = lStack_58;
  *(long *)(arg1 + 0x60) = lStack_58 << 4;
  *(uint64_t *)(arg1 + 0x68) = stk0;
  *(uint64_t *)(arg1 + 0x70) = stk1;
  *(uint64_t *)(arg1 + 8) = arg6;
  t3 = sk_macho_uuid(arg2);
  if (t3 == 0) {
    sk_memset(arg1 + 0x10,0x10);
  }
  else if ((t3 + 0x10 < t3) ||
          (sk_memcpy2(arg1 + 0x10U,t3,0x10), arg1 + 0x20U < arg1 + 0x10U)) {
                    
    t2 = (sk_code_t )sk_break(0x5519,0x54b1c);
    (*t2)();
  }
  return;
}




/* FUN_00054b44 @ 0x54b44   (est. sk_cnode_record)
 * Ghidra: void FUN_00054b44(undefined8 *arg1,undefined8 arg2,undefined8 arg3,undefined8 arg4, undefined8 arg5,undefined8 arg6,undefined8 arg7,undefined8 arg8, undefined8 arg9)
 * sk_cnode_record: cL4 sk cnode record operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_cnode_record(uint64_t *arg1,uint64_t arg2,uint64_t arg3,uint64_t arg4, uint64_t arg5,uint64_t arg6,uint64_t arg7,uint64_t arg8, uint64_t arg9)
{
  sk_code_t t0;
  uint64_t *t1;
  
  *arg1 = 0;
  arg1[1] = arg9;
  arg1[3] = 0;
  arg1[5] = arg4;
  arg1[6] = arg5;
  arg1[7] = arg3;
  arg1[8] = 0;
  arg1[9] = arg8;
  arg1[10] = arg7;
  arg1[0xb] = 0;
  arg1[0xc] = 0;
  arg1[0xd] = 0;
  arg1[0xe] = 0;
  t1 = arg1 + 2;
  *t1 = 0;
  arg1[4] = arg6;
  sk_memcpy2(t1,arg2,0x10);
  if (t1 <= arg1 + 4) {
    return;
  }
                    
  t0 = (sk_code_t )sk_break(0x5519,0x54ba8);
  (*t0)();
}




/* FUN_00054ba8 @ 0x54ba8   (est. sk_cnode_get)
 * Ghidra: undefined8 FUN_00054ba8(void)
 * sk_cnode_get: cL4 sk cnode get operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

uint64_t sk_cnode_get(void)
{
  long t0;
  uint64_t t1;
  
  t0 = sk_list_head();
  t1 = 0;
  if (t0 != 0) {
    t1 = *(uint64_t *)(t0 + 0x38);
  }
  return t1;
}




/* FUN_00054bc8 @ 0x54bc8   (est. sk_cnode_get2)
 * Ghidra: undefined8 FUN_00054bc8(void)
 * sk_cnode_get2: cL4 sk cnode get2 operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

uint64_t sk_cnode_get2(void)
{
  long t0;
  uint64_t t1;
  
  t0 = sk_list_head();
  t1 = 0;
  if (t0 != 0) {
    t1 = *(uint64_t *)(t0 + 0x20);
  }
  return t1;
}




/* FUN_00054be8 @ 0x54be8   (est. sk_cnode_validate)
 * Ghidra: void FUN_00054be8(void)
 * sk_cnode_validate: cL4 sk cnode validate operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_cnode_validate(void)
{
  sk_code_t t0;
  unsigned long t1;
  unsigned long stk0;
  
  stk0 = 0;
  t1 = sk_kernel_state_get(&stk0);
  if (((t1 != 0) || (t1 = sk_cap_resolve_name(0,&stk0), t1 != 0)) &&
     (t1 + stk0 < t1 || (t1 + stk0) - t1 < stk0)) {
                    
    t0 = (sk_code_t )sk_break(0x5519,0x54c2c);
    (*t0)();
  }
  return;
}




/* FUN_00054c3c @ 0x54c3c   (est. sk_cnode_copy)
 * Ghidra: void FUN_00054c3c(ulong arg1)
 * sk_cnode_copy: cL4 sk cnode copy operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_cnode_copy(unsigned long arg1)
{
  sk_code_t t1;
  long t0;
  
  t0 = sk_list_head();
  if (t0 == 0) {
    sk_memset(arg1,0x10);
    return;
  }
  sk_memcpy2(arg1,t0 + 0x10,0x10);
  if (arg1 <= arg1 + 0x10) {
    return;
  }
                    
  t1 = (sk_code_t )sk_break(0x5519,0x54c9c);
  (*t1)();
}




/* FUN_00054c9c @ 0x54c9c   (est. sk_cnode_revoke)
 * Ghidra: void FUN_00054c9c(undefined8 arg1,undefined8 arg2)
 * sk_cnode_revoke: cL4 sk cnode revoke operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_cnode_revoke(uint64_t arg1,uint64_t arg2)
{
  sk_code_t t1;
  long t0;
  uint64_t stk0;
  
  stk0 = arg1;
  t0 = sk_range_lookup(&stk0,1);
  if (t0 != 0) {
    if (*(unsigned long *)(t0 + 0x60) >> 4 < *(unsigned long *)(t0 + 0x58)) {
                    
      t1 = (sk_code_t )sk_break(0x5519,0x54cfc);
      (*t1)();
    }
    sk_macho_bind(stk0,arg2,*(unsigned long *)(t0 + 0x58),*(uint64_t *)(t0 + 0x68),
                 *(uint64_t *)(t0 + 0x70));
  }
  return;
}




/* FUN_00054cfc @ 0x54cfc   (est. sk_cnode_scan)
 * Ghidra: ulong FUN_00054cfc(void)
 * sk_cnode_scan: cL4 sk cnode scan operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

unsigned long sk_cnode_scan(void)
{
  sk_code_t t1;
  int t0;
  unsigned long t3;
  unsigned short *t2;
  uint8_t stk0 [16];
  
  t0 = sk_domain_state();
  if (t0 != 0) {
    t3 = sk_msg_capacity();
    if ((t3 != 0) && (t3 + 8 < t3)) {
LAB_00054de0:
                    
      t1 = (sk_code_t )sk_break(0x5519,0x54de4);
      (*t1)();
    }
    stk0 = sk_msg_push_cap();
    t3 = sk_msg_iter(stk0);
    while (t3 != 0) {
      if (t3 + 0xc < t3) goto LAB_00054de0;
      t0 = sk_msg_next(t3);
      if (t0 == 0x19) {
        t2 = (unsigned short *)sk_msg_get(t3,0);
        if (t2 != (unsigned short *)0x0) {
          return (unsigned long)(uint8_t)t2[1] << 0x10 | (unsigned long)*(uint8_t *)((long)t2 + 3) << 0x18 |
                 (unsigned long)*t2 |
                 (unsigned long)((unsigned int)(uint8_t)t2[3] << 0x10 | (unsigned int)*(uint8_t *)((long)t2 + 7) << 0x18 |
                        (unsigned int)t2[2]) << 0x20;
        }
      }
      t3 = sk_msg_iter(stk0);
    }
  }
  return 0;
}




/* FUN_00054de4 @ 0x54de4   (est. sk_cnode_scan2)
 * Ghidra: undefined8 FUN_00054de4(void)
 * sk_cnode_scan2: cL4 sk cnode scan2 operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

uint64_t sk_cnode_scan2(void)
{
  return 0;
}




/* FUN_00054dec @ 0x54dec   (est. sk_cnode_scan3)
 * Ghidra: void FUN_00054dec(void)
 * sk_cnode_scan3: cL4 sk cnode scan3 operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_cnode_scan3(void)
{
  long t0;
  uint64_t stk1;
  uint64_t stk2;
  long stk0;
  
  stk0 = -0x2c8502b44bfffed6;
  t0 = sk_log_consume(&stk1,0x10);
  if (t0 == 0x10) {
    sk_printf(stk1,stk2);
    if (stk0 == -0x2c8502b44bfffed6) {
      return;
    }
  }
  else {
    sk_rt_park();
  }
                    
  sk_noreturn_error();
}




/* FUN_00054e54 @ 0x54e54   (est. sk_cnode_tokenize)
 * Ghidra: long FUN_00054e54(long arg1,char *arg2,long arg3)
 * sk_cnode_tokenize: cL4 sk cnode tokenize operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

long sk_cnode_tokenize(long arg1,char *arg2,long arg3)
{
  char *t5;
  uint8_t t16;
  uint8_t t18;
  uint8_t t19;
  uint8_t t20;
  uint8_t t21;
  uint8_t t22;
  char t0;
  char t1;
  uint8_t t8;
  uint8_t t9;
  uint8_t t10;
  uint8_t t11;
  uint8_t t12;
  uint8_t t13;
  uint8_t *t7;
  uint8_t t14;
  uint16_t t15;
  sk_code_t t6;
  long t2;
  long t3;
  uint64_t t17;
  long t4;
  uint8_t stk0 [16];
  
  if ((arg1 != 0x64cd78) || (t2 = sk_cnode_alloc(arg2,arg3), t2 != 0)) {
    stk0 = sk_cpu_irq();
    t17 = stk0._8_8_;
    t2 = stk0._0_8_;
    t7 = (uint8_t *)sk_tpidrro;
    t18 = t7[9];
    t16 = t7[8];
    t19 = t7[0xb];
    t20 = t7[10];
    t15 = *(uint16_t *)(t7 + 0xc);
    t21 = t7[0xf];
    t22 = t7[0xe];
    if (arg3 != 0) {
      t4 = 0;
      do {
        if ((arg1 == 0x64d038) && (t3 = sk_tcb_ap(t2,t17), t3 != 0)) {
          t17 = sk_tcb_ap();
          t5 = arg2 + t4;
          if ((arg2 + arg3 <= t5) || (t5 < arg2)) {
LAB_00055160:
                    
            t6 = (sk_code_t )sk_break(0x5519,0x55164);
            (*t6)();
          }
          t0 = *t5;
          *t7 = (char)t17;
          t8 = (uint8_t)((unsigned long)t17 >> 0x28);
          t7[5] = t8;
          t9 = (uint8_t)((unsigned long)t17 >> 0x18);
          t7[3] = t9;
          t10 = (uint8_t)((unsigned long)t17 >> 0x10);
          t7[2] = t10;
          t11 = (uint8_t)((unsigned long)t17 >> 8);
          t7[1] = t11;
          t13 = (uint8_t)((unsigned long)t17 >> 0x20);
          t7[4] = t13;
          t14 = (uint8_t)((unsigned long)t17 >> 0x38);
          t7[7] = t14;
          t12 = (uint8_t)((unsigned long)t17 >> 0x30);
          t7[6] = t12;
          t1 = (char)t0 >> 7;
          t7[0xd] = t1;
          t7[8] = t0;
          t7[0xb] = t1;
          t7[10] = t1;
          t7[9] = t1;
          t7[0xc] = t1;
          t7[0xf] = t0 >> 7;
          t7[0xe] = t1;
          do {
            sk_svc(0);
            *t7 = (char)t17;
            t7[5] = t8;
            t7[3] = t9;
            t7[2] = t10;
            t7[1] = t11;
            t7[4] = t13;
            t7[7] = t14;
            t7[6] = t12;
          } while (t2 == 1);
        }
        else {
          t5 = arg2 + t4;
          if ((arg2 + arg3 <= t5) || (t5 < arg2)) goto LAB_00055160;
          t0 = *t5;
          t7[5] = 0;
          t7[3] = 0;
          t7[2] = 0;
          t7[1] = 0;
          t7[4] = 0;
          *t7 = 0;
          t7[7] = 0;
          t7[6] = 0;
          t1 = (char)t0 >> 7;
          t7[0xd] = t1;
          t7[8] = t0;
          t7[0xb] = t1;
          t7[10] = t1;
          t7[9] = t1;
          t7[0xc] = t1;
          t7[0xf] = t0 >> 7;
          t7[0xe] = t1;
          do {
            sk_svc(0);
            *t7 = 0;
            t7[5] = 0;
            t7[3] = 0;
            t7[2] = 0;
            t7[1] = 0;
            t7[4] = 0;
            t7[7] = 0;
            t7[6] = 0;
          } while (t2 == 1);
        }
        t17 = 0;
        t4 = t4 + 1;
      } while (t4 != arg3);
    }
    t7[8] = t16;
    t7[0xd] = (char)((unsigned short)t15 >> 8);
    t7[0xb] = t19;
    t7[10] = t20;
    t7[9] = t18;
    t7[0xc] = (char)t15;
    t7[0xf] = t21;
    t7[0xe] = t22;
  }
  return arg3;
}




/* FUN_00055164 @ 0x55164   (est. sk_tcb_clear)
 * Ghidra: void FUN_00055164(undefined8 arg1)
 * sk_tcb_clear: cL4 sk tcb clear operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_tcb_clear(uint64_t arg1)
{
  sk_code_t t0;
  unsigned long t1;
  
  t1 = sk_tcb_ar(arg1,0x6ad740);
  if (((((((t1 & 1) == 0) && (t1 = sk_tcb_aw(arg1,0x6ad740), (t1 & 1) == 0)) &&
        (t1 = sk_cap_cmp(arg1,0x6ad740), (t1 & 1) == 0)) &&
       ((t1 = sk_cap_cmp2(arg1,0x6ad740), (t1 & 1) == 0 &&
        (t1 = sk_cap_cmp3(arg1,0x6ad740), (t1 & 1) == 0)))) &&
      ((t1 = sk_cap_cmp4(arg1,0x6ad740), (t1 & 1) == 0 &&
       ((t1 = sk_cap_cmp5(arg1,0x6ad740), (t1 & 1) == 0 &&
        (t1 = sk_cap_cmp6(arg1,0x6ad740), (t1 & 1) == 0)))))) &&
     ((t1 = sk_cap_cmp7(arg1,0x6ad740), (t1 & 1) == 0 &&
      ((t1 = sk_cap_cmp8(arg1,0x6ad740), (t1 & 1) == 0 &&
       (t1 = fill_cap_dispatch_table(arg1,0x6ad740), (t1 & 1) == 0)))))) {
                    
    t0 = (sk_code_t )sk_break(1,0x5526c);
    (*t0)();
  }
  sk_tcb_set(0x6ad740);
  return;
}




/* FUN_0005526c @ 0x5526c   (est. sk_tcb_get)
 * Ghidra: undefined8 FUN_0005526c(void)
 * sk_tcb_get: cL4 sk tcb get operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

uint64_t sk_tcb_get(void)
{
  long t0;
  
  t0 = sk_global_ensure();
  return *(uint64_t *)(t0 + 8);
}




/* FUN_00055288 @ 0x55288   (est. sk_tcb_peek)
 * Ghidra: undefined8 FUN_00055288(void)
 * sk_tcb_peek: cL4 sk tcb peek operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

uint64_t sk_tcb_peek(void)
{
  long t0;
  
  t0 = sk_global_ensure();
  return *(uint64_t *)(t0 + 0x10);
}




/* FUN_000552a4 @ 0x552a4   (est. sk_tcb_a)
 * Ghidra: uint8_t FUN_000552a4(void)
 * sk_tcb_a: cL4 sk tcb a operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

uint8_t sk_tcb_a(void)
{
  long t0;
  
  t0 = sk_global_ensure();
  return *(uint8_t *)(t0 + 0x20);
}




/* FUN_000552c0 @ 0x552c0   (est. sk_tcb_b)
 * Ghidra: void FUN_000552c0(undefined8 arg1,undefined8 arg2,undefined8 arg3)
 * sk_tcb_b: cL4 sk tcb b operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_tcb_b(uint64_t arg1,uint64_t arg2,uint64_t arg3)
{
  long t0;
  
  t0 = sk_global_ensure();
                    
                    
  (**(sk_code_t *)(t0 + 0x28))(arg1,arg2,arg3);
  return;
}




/* FUN_0005530c @ 0x5530c   (est. sk_tcb_c)
 * Ghidra: uint8_t FUN_0005530c(void)
 * sk_tcb_c: cL4 sk tcb c operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

uint8_t sk_tcb_c(void)
{
  long t0;
  
  t0 = sk_global_ensure();
  return *(uint8_t *)(t0 + 0x30);
}




/* FUN_00055328 @ 0x55328   (est. sk_tcb_d)
 * Ghidra: uint8_t FUN_00055328(void)
 * sk_tcb_d: cL4 sk tcb d operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

uint8_t sk_tcb_d(void)
{
  long t0;
  
  t0 = sk_global_ensure();
  return *(uint8_t *)(t0 + 0x38);
}




/* FUN_00055344 @ 0x55344   (est. sk_tcb_e)
 * Ghidra: uint8_t FUN_00055344(void)
 * sk_tcb_e: cL4 sk tcb e operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

uint8_t sk_tcb_e(void)
{
  long t0;
  
  t0 = sk_global_ensure();
  return *(uint8_t *)(t0 + 0x39);
}




/* FUN_00055360 @ 0x55360   (est. sk_tcb_f)
 * Ghidra: uint8_t FUN_00055360(void)
 * sk_tcb_f: cL4 sk tcb f operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

uint8_t sk_tcb_f(void)
{
  long t0;
  
  t0 = sk_global_ensure();
  return *(uint8_t *)(t0 + 0x3a);
}




/* FUN_0005537c @ 0x5537c   (est. sk_tcb_g)
 * Ghidra: void FUN_0005537c(undefined8 arg1)
 * sk_tcb_g: cL4 sk tcb g operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_tcb_g(uint64_t arg1)
{
  long t0;
  
  t0 = sk_global_ensure();
                    
                    
  (**(sk_code_t *)(t0 + 0x40))(arg1);
  return;
}




/* FUN_000553b0 @ 0x553b0   (est. sk_tcb_h)
 * Ghidra: void FUN_000553b0(undefined8 arg1)
 * sk_tcb_h: cL4 sk tcb h operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_tcb_h(uint64_t arg1)
{
  long t0;
  
  t0 = sk_global_ensure();
                    
                    
  (**(sk_code_t *)(t0 + 0x48))(arg1);
  return;
}




/* FUN_000553e4 @ 0x553e4   (est. sk_tcb_i)
 * Ghidra: void FUN_000553e4(undefined8 arg1,undefined8 arg2)
 * sk_tcb_i: cL4 sk tcb i operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_tcb_i(uint64_t arg1,uint64_t arg2)
{
  long t0;
  
  t0 = sk_global_ensure();
                    
                    
  (**(sk_code_t *)(t0 + 0x50))(arg1,arg2);
  return;
}




/* FUN_00055420 @ 0x55420   (est. sk_tcb_j)
 * Ghidra: void FUN_00055420(undefined8 arg1)
 * sk_tcb_j: cL4 sk tcb j operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_tcb_j(uint64_t arg1)
{
  long t0;
  
  t0 = sk_global_ensure();
                    
                    
  (**(sk_code_t *)(t0 + 0x58))(arg1);
  return;
}




/* FUN_00055454 @ 0x55454   (est. sk_tcb_k)
 * Ghidra: void FUN_00055454(undefined8 arg1)
 * sk_tcb_k: cL4 sk tcb k operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_tcb_k(uint64_t arg1)
{
  long t0;
  
  t0 = sk_global_ensure();
                    
                    
  (**(sk_code_t *)(t0 + 0x60))(arg1);
  return;
}




/* FUN_00055488 @ 0x55488   (est. sk_tcb_l)
 * Ghidra: void FUN_00055488(undefined8 arg1)
 * sk_tcb_l: cL4 sk tcb l operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_tcb_l(uint64_t arg1)
{
  long t0;
  
  t0 = sk_global_ensure();
                    
                    
  (**(sk_code_t *)(t0 + 0x68))(arg1);
  return;
}




/* FUN_000554bc @ 0x554bc   (est. sk_tcb_m)
 * Ghidra: void FUN_000554bc(undefined8 arg1)
 * sk_tcb_m: cL4 sk tcb m operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_tcb_m(uint64_t arg1)
{
  long t0;
  
  t0 = sk_global_ensure();
                    
                    
  (**(sk_code_t *)(t0 + 0x70))(arg1);
  return;
}




/* FUN_000554f0 @ 0x554f0   (est. sk_tcb_n)
 * Ghidra: void FUN_000554f0(undefined8 arg1)
 * sk_tcb_n: cL4 sk tcb n operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_tcb_n(uint64_t arg1)
{
  long t0;
  
  t0 = sk_global_ensure();
                    
                    
  (**(sk_code_t *)(t0 + 0x78))(arg1);
  return;
}




/* FUN_00055524 @ 0x55524   (est. sk_tcb_o)
 * Ghidra: void FUN_00055524(undefined8 arg1)
 * sk_tcb_o: cL4 sk tcb o operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_tcb_o(uint64_t arg1)
{
  long t0;
  
  t0 = sk_global_ensure();
                    
                    
  (**(sk_code_t *)(t0 + 0x80))(arg1);
  return;
}




/* FUN_00055558 @ 0x55558   (est. sk_tcb_p)
 * Ghidra: void FUN_00055558(undefined8 arg1,undefined8 arg2,undefined8 arg3,undefined8 arg4)
 * sk_tcb_p: cL4 sk tcb p operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_tcb_p(uint64_t arg1,uint64_t arg2,uint64_t arg3,uint64_t arg4)
{
  long t0;
  
  t0 = sk_global_ensure();
                    
                    
  (**(sk_code_t *)(t0 + 0x88))(arg1,arg2,arg3,arg4);
  return;
}




/* FUN_000555ac @ 0x555ac   (est. sk_tcb_q)
 * Ghidra: void FUN_000555ac(undefined8 arg1,undefined8 arg2,undefined8 arg3)
 * sk_tcb_q: cL4 sk tcb q operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_tcb_q(uint64_t arg1,uint64_t arg2,uint64_t arg3)
{
  long t0;
  
  t0 = sk_global_ensure();
                    
                    
  (**(sk_code_t *)(t0 + 0x90))(arg1,arg2,arg3);
  return;
}




/* FUN_000555f8 @ 0x555f8   (est. sk_tcb_r)
 * Ghidra: void FUN_000555f8(undefined8 arg1)
 * sk_tcb_r: cL4 sk tcb r operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_tcb_r(uint64_t arg1)
{
  long t0;
  
  t0 = sk_global_ensure();
                    
                    
  (**(sk_code_t *)(t0 + 0x98))(arg1);
  return;
}




/* FUN_0005562c @ 0x5562c   (est. sk_tcb_s)
 * Ghidra: void FUN_0005562c(undefined8 arg1)
 * sk_tcb_s: cL4 sk tcb s operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_tcb_s(uint64_t arg1)
{
  long t0;
  
  t0 = sk_global_ensure();
                    
                    
  (**(sk_code_t *)(t0 + 0xb0))(arg1);
  return;
}




/* FUN_00055660 @ 0x55660   (est. sk_tcb_t)
 * Ghidra: void FUN_00055660(undefined8 arg1)
 * sk_tcb_t: cL4 sk tcb t operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_tcb_t(uint64_t arg1)
{
  long t0;
  
  t0 = sk_global_ensure();
                    
                    
  (**(sk_code_t *)(t0 + 0xb8))(arg1);
  return;
}




/* FUN_00055694 @ 0x55694   (est. sk_tcb_u)
 * Ghidra: void FUN_00055694(undefined8 arg1)
 * sk_tcb_u: cL4 sk tcb u operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_tcb_u(uint64_t arg1)
{
  long t0;
  
  t0 = sk_global_ensure();
                    
                    
  (**(sk_code_t *)(t0 + 0xc0))(arg1);
  return;
}




/* FUN_000556c8 @ 0x556c8   (est. sk_tcb_v2)
 * Ghidra: undefined8 FUN_000556c8(void)
 * sk_tcb_v2: cL4 sk tcb v2 operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

uint64_t sk_tcb_v2(void)
{
  long t0;
  
  t0 = sk_global_ensure();
  return *(uint64_t *)(t0 + 0xd0);
}




/* FUN_000556e4 @ 0x556e4   (est. sk_tcb_w2)
 * Ghidra: void FUN_000556e4(undefined8 arg1)
 * sk_tcb_w2: cL4 sk tcb w2 operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_tcb_w2(uint64_t arg1)
{
  long t0;
  
  t0 = sk_global_ensure();
                    
                    
  (**(sk_code_t *)(t0 + 0xd8))(arg1);
  return;
}




/* FUN_00055718 @ 0x55718   (est. sk_tcb_x2)
 * Ghidra: void FUN_00055718(undefined8 arg1)
 * sk_tcb_x2: cL4 sk tcb x2 operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_tcb_x2(uint64_t arg1)
{
  long t0;
  
  t0 = sk_global_ensure();
                    
                    
  (**(sk_code_t *)(t0 + 0xe0))(arg1);
  return;
}




/* FUN_0005574c @ 0x5574c   (est. sk_tcb_y2)
 * Ghidra: void FUN_0005574c(undefined8 arg1)
 * sk_tcb_y2: cL4 sk tcb y2 operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_tcb_y2(uint64_t arg1)
{
  long t0;
  
  t0 = sk_global_ensure();
                    
                    
  (**(sk_code_t *)(t0 + 0xe8))(arg1);
  return;
}




/* FUN_00055780 @ 0x55780   (est. sk_tcb_z2)
 * Ghidra: uint8_t FUN_00055780(void)
 * sk_tcb_z2: cL4 sk tcb z2 operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

uint8_t sk_tcb_z2(void)
{
  long t0;
  
  t0 = sk_global_ensure();
  return *(uint8_t *)(t0 + 0xf1);
}




/* FUN_0005579c @ 0x5579c   (est. sk_tcb_ab)
 * Ghidra: void FUN_0005579c(undefined8 arg1,undefined8 arg2,undefined8 arg3)
 * sk_tcb_ab: cL4 sk tcb ab operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_tcb_ab(uint64_t arg1,uint64_t arg2,uint64_t arg3)
{
  long t0;
  
  t0 = sk_global_ensure();
                    
                    
  (**(sk_code_t *)(t0 + 0xf8))(arg1,arg2,arg3);
  return;
}




/* FUN_000557e8 @ 0x557e8   (est. sk_tcb_ac)
 * Ghidra: void FUN_000557e8(undefined8 arg1,undefined8 arg2)
 * sk_tcb_ac: cL4 sk tcb ac operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_tcb_ac(uint64_t arg1,uint64_t arg2)
{
  long t0;
  
  t0 = sk_global_ensure();
                    
                    
  (**(sk_code_t *)(t0 + 0x100))(arg1,arg2);
  return;
}




/* FUN_00055824 @ 0x55824   (est. sk_tcb_ad)
 * Ghidra: void FUN_00055824(undefined8 arg1)
 * sk_tcb_ad: cL4 sk tcb ad operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_tcb_ad(uint64_t arg1)
{
  long t0;
  
  t0 = sk_global_ensure();
                    
                    
  (**(sk_code_t *)(t0 + 0x108))(arg1);
  return;
}




/* FUN_00055858 @ 0x55858   (est. sk_tcb_ae)
 * Ghidra: uint8_t FUN_00055858(void)
 * sk_tcb_ae: cL4 sk tcb ae operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

uint8_t sk_tcb_ae(void)
{
  long t0;
  
  t0 = sk_global_ensure();
  return *(uint8_t *)(t0 + 0x14a);
}




/* FUN_00055874 @ 0x55874   (est. sk_tcb_af)
 * Ghidra: void FUN_00055874(undefined8 arg1,undefined8 arg2,undefined8 arg3)
 * sk_tcb_af: cL4 sk tcb af operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_tcb_af(uint64_t arg1,uint64_t arg2,uint64_t arg3)
{
  long t0;
  
  t0 = sk_global_ensure();
                    
                    
  (**(sk_code_t *)(t0 + 0x150))(arg1,arg2,arg3);
  return;
}




/* FUN_000558c0 @ 0x558c0   (est. sk_tcb_ag)
 * Ghidra: void FUN_000558c0(undefined8 arg1,undefined8 arg2,undefined8 arg3)
 * sk_tcb_ag: cL4 sk tcb ag operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_tcb_ag(uint64_t arg1,uint64_t arg2,uint64_t arg3)
{
  long t0;
  
  t0 = sk_global_ensure();
                    
                    
  (**(sk_code_t *)(t0 + 0x158))(arg1,arg2,arg3);
  return;
}




/* FUN_0005590c @ 0x5590c   (est. sk_tcb_ah)
 * Ghidra: void FUN_0005590c(undefined8 arg1,undefined8 arg2)
 * sk_tcb_ah: cL4 sk tcb ah operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_tcb_ah(uint64_t arg1,uint64_t arg2)
{
  long t0;
  
  t0 = sk_global_ensure();
                    
                    
  (**(sk_code_t *)(t0 + 0x160))(arg1,arg2);
  return;
}




/* FUN_00055948 @ 0x55948   (est. sk_tcb_ai)
 * Ghidra: void FUN_00055948(undefined8 arg1)
 * sk_tcb_ai: cL4 sk tcb ai operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_tcb_ai(uint64_t arg1)
{
  long t0;
  
  t0 = sk_global_ensure();
                    
                    
  (**(sk_code_t *)(t0 + 0x168))(arg1);
  return;
}




/* FUN_0005597c @ 0x5597c   (est. sk_tcb_aj)
 * Ghidra: void FUN_0005597c(undefined8 arg1,undefined8 arg2)
 * sk_tcb_aj: cL4 sk tcb aj operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_tcb_aj(uint64_t arg1,uint64_t arg2)
{
  long t0;
  
  t0 = sk_global_ensure();
                    
                    
  (**(sk_code_t *)(t0 + 0x170))(arg1,arg2);
  return;
}




/* FUN_000559b8 @ 0x559b8   (est. sk_tcb_ak)
 * Ghidra: undefined8 FUN_000559b8(unsigned int arg1)
 * sk_tcb_ak: cL4 sk tcb ak operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

uint64_t sk_tcb_ak(unsigned int arg1)
{
  uint64_t *t2;
  sk_code_t t1;
  long t0;
  uint64_t t4;
  uint64_t *t3;
  
  if (((int)arg1 < 0) || (t0 = sk_global_ensure(), *(uint8_t *)(t0 + 0x178) <= arg1)) {
    t4 = 0;
  }
  else {
    t0 = sk_global_ensure();
    t3 = *(uint64_t **)(t0 + 0x180);
    t2 = t3 + arg1;
    if ((t2 < t3 || t3 + *(uint8_t *)(t0 + 0x178) < t2 + 1) || t2 + 1 < t2)
    {
                    
      t1 = (sk_code_t )sk_break(0x5519,0x55a24);
      (*t1)();
    }
    t4 = *t2;
  }
  return t4;
}




/* FUN_00055a24 @ 0x55a24   (est. sk_tcb_al)
 * Ghidra: undefined8 FUN_00055a24(unsigned int arg1)
 * sk_tcb_al: cL4 sk tcb al operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

uint64_t sk_tcb_al(unsigned int arg1)
{
  uint64_t *t2;
  sk_code_t t1;
  long t0;
  uint64_t t4;
  uint64_t *t3;
  
  if (((int)arg1 < 0) || (t0 = sk_global_ensure(), *(uint8_t *)(t0 + 0x178) <= arg1)) {
    t4 = 0;
  }
  else {
    t0 = sk_global_ensure();
    t3 = *(uint64_t **)(t0 + 0x188);
    t2 = t3 + arg1;
    if ((t2 < t3 || t3 + *(uint8_t *)(t0 + 0x178) < t2 + 1) || t2 + 1 < t2)
    {
                    
      t1 = (sk_code_t )sk_break(0x5519,0x55a90);
      (*t1)();
    }
    t4 = *t2;
  }
  return t4;
}




/* FUN_00055a90 @ 0x55a90   (est. sk_tcb_am)
 * Ghidra: undefined8 FUN_00055a90(unsigned int arg1)
 * sk_tcb_am: cL4 sk tcb am operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

uint64_t sk_tcb_am(unsigned int arg1)
{
  uint64_t *t2;
  sk_code_t t1;
  long t0;
  uint64_t t4;
  uint64_t *t3;
  
  if (((int)arg1 < 0) || (t0 = sk_global_ensure(), *(uint8_t *)(t0 + 0x178) <= arg1)) {
    t4 = 0;
  }
  else {
    t0 = sk_global_ensure();
    t3 = *(uint64_t **)(t0 + 400);
    t2 = t3 + arg1;
    if ((t2 < t3 || t3 + *(uint8_t *)(t0 + 0x178) < t2 + 1) || t2 + 1 < t2)
    {
                    
      t1 = (sk_code_t )sk_break(0x5519,0x55afc);
      (*t1)();
    }
    t4 = *t2;
  }
  return t4;
}




/* FUN_00055afc @ 0x55afc   (est. sk_tcb_an)
 * Ghidra: void FUN_00055afc(void)
 * sk_tcb_an: cL4 sk tcb an operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_tcb_an(void)
{
  long t0;
  
  t0 = sk_global_ensure();
                    
                    
  (**(sk_code_t *)(t0 + 0x198))();
  return;
}




/* FUN_00055b20 @ 0x55b20   (est. sk_tcb_ao)
 * Ghidra: void FUN_00055b20(void)
 * sk_tcb_ao: cL4 sk tcb ao operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_tcb_ao(void)
{
  long t0;
  
  t0 = sk_global_ensure();
                    
                    
  (**(sk_code_t *)(t0 + 0x1a0))();
  return;
}




/* FUN_00055b44 @ 0x55b44   (est. sk_tcb_ap)
 * Ghidra: undefined8 FUN_00055b44(void)
 * sk_tcb_ap: cL4 sk tcb ap operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

uint64_t sk_tcb_ap(void)
{
  long t0;
  
  t0 = sk_global_ensure();
  return *(uint64_t *)(t0 + 0x1b0);
}




/* FUN_00055b60 @ 0x55b60   (est. sk_tcb_aq)
 * Ghidra: uint8_t FUN_00055b60(void)
 * sk_tcb_aq: cL4 sk tcb aq operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

uint8_t sk_tcb_aq(void)
{
  long t0;
  
  t0 = sk_global_ensure();
  return *(uint8_t *)(t0 + 0x1b8);
}




/* FUN_00055b7c @ 0x55b7c   (est. sk_tcb_ar)
 * Ghidra: bool FUN_00055b7c(long arg1,long arg2)
 * sk_tcb_ar: cL4 sk tcb ar operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

bool sk_tcb_ar(long arg1,long arg2)
{
  if (arg1 == 2) {
    *(uint64_t *)(arg2 + 8) = 2;
    *(char **)(arg2 + 0x10) = sk_str_43;
    *(uint8_t *)(arg2 + 0x18) = 1;
    *(uint32_t *)(arg2 + 0x1c) = 2;
    *(uint8_t *)(arg2 + 0x20) = 0x18;
    *(uint8_t **)(arg2 + 0x28) = &LAB_00055e24;
    *(uint8_t *)(arg2 + 0x30) = 0;
    *(uint64_t *)(arg2 + 0x34) = 0xffffffff;
    *(uint64_t *)(arg2 + 0x48) = 0;
    *(uint64_t *)(arg2 + 0x40) = 0;
    *(uint64_t *)(arg2 + 0x58) = 0;
    *(uint64_t *)(arg2 + 0x50) = 0;
    *(uint64_t *)(arg2 + 0x68) = 0;
    *(uint64_t *)(arg2 + 0x60) = 0;
    *(uint64_t *)(arg2 + 0x78) = 0;
    *(uint64_t *)(arg2 + 0x70) = 0;
    *(uint64_t *)(arg2 + 0x88) = 0;
    *(uint64_t *)(arg2 + 0x80) = 0;
    *(uint64_t *)(arg2 + 0x98) = 0;
    *(uint64_t *)(arg2 + 0x90) = 0;
    *(uint8_t *)(arg2 + 0xa0) = 1;
    *(uint32_t *)(arg2 + 0xa4) = 3;
    *(uint8_t **)(arg2 + 0xa8) = &LAB_00055e44;
    *(uint8_t **)(arg2 + 0xb0) = &LAB_00055e4c;
    *(uint8_t **)(arg2 + 0xb8) = &LAB_00055e54;
    *(uint8_t **)(arg2 + 0xc0) = &LAB_00055e5c;
    *(uint64_t *)(arg2 + 0xd0) = 0xc;
    *(uint8_t **)(arg2 + 0xd8) = &LAB_00055e64;
    *(uint8_t **)(arg2 + 0xe0) = &LAB_00055e6c;
    *(uint8_t **)(arg2 + 0xe8) = &LAB_00055e74;
    *(uint16_t *)(arg2 + 0xf0) = 0x1601;
    *(uint32_t *)(arg2 + 0xf4) = 3;
    *(uint8_t **)(arg2 + 0xf8) = &LAB_00055e7c;
    *(uint8_t **)(arg2 + 0x100) = &LAB_00055e9c;
    *(uint8_t **)(arg2 + 0x108) = &LAB_00055eb8;
    *(uint8_t **)(arg2 + 0x110) = &LAB_00055ed0;
    *(uint8_t **)(arg2 + 0x118) = &LAB_00055ed8;
    *(sk_code_t *)(arg2 + 0x120) = sk_tcb_as;
    *(sk_code_t *)(arg2 + 0x128) = sk_tcb_at;
    *(uint8_t **)(arg2 + 0x130) = &LAB_00055f0c;
    *(sk_code_t *)(arg2 + 0x138) = sk_tcb_au;
    *(uint16_t *)(arg2 + 0x149) = 0x1701;
    *(uint32_t *)(arg2 + 0x14c) = 1;
    *(uint8_t **)(arg2 + 0x150) = &LAB_00055f28;
    *(uint8_t **)(arg2 + 0x158) = &LAB_00055f48;
    *(sk_code_t *)(arg2 + 0x160) = sk_tcb_av;
    *(uint8_t **)(arg2 + 0x168) = &LAB_00055f68;
    *(uint8_t **)(arg2 + 0x170) = &LAB_00055fb0;
    *(uint8_t *)(arg2 + 0x140) = 1;
    *(uint32_t *)(arg2 + 0x144) = 5;
    *(uint8_t *)(arg2 + 0x148) = 1;
    *(uint8_t *)(arg2 + 0x178) = 0x19;
    *(uint8_t **)(arg2 + 0x180) = &sk_global_007;
    *(uint8_t **)(arg2 + 0x188) = &sk_global_008;
    *(uint64_t *)(arg2 + 400) = 0x64d198;
    *(uint8_t **)(arg2 + 0x198) = &LAB_00055ff0;
    *(uint8_t **)(arg2 + 0x1a0) = &LAB_00055ff8;
    *(uint8_t *)(arg2 + 0x1a8) = 1;
    *(uint64_t *)(arg2 + 0x1b0) = 0;
    *(int *)(arg2 + 0x1b8) = (int)sk_global_004;
  }
  return arg1 == 2;
}




/* FUN_00055ee0 @ 0x55ee0   (est. sk_tcb_as)
 * Ghidra: void FUN_00055ee0(undefined8 arg1,undefined8 arg2,undefined8 arg3,undefined8 arg4)
 * sk_tcb_as: cL4 sk tcb as operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_tcb_as(uint64_t arg1,uint64_t arg2,uint64_t arg3,uint64_t arg4)
{
  uint64_t *t0;
  
  t0 = (uint64_t *)sk_tpidrro;
  *t0 = arg2;
  t0[1] = arg3;
  t0[2] = arg4;
  sk_svc(0);
  *t0 = arg2;
  return;
}




/* FUN_00056004 @ 0x56004   (est. sk_tcb_at)
 * Ghidra: void FUN_00056004(long arg1)
 * sk_tcb_at: cL4 sk tcb at operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_tcb_at(long arg1)
{
  uint64_t *t0;
  uint64_t t1;
  
  t0 = (uint64_t *)sk_tpidrro;
  t1 = *t0;
  do {
    sk_svc(0);
    *t0 = t1;
  } while (arg1 == 1);
  return;
}




/* FUN_00056034 @ 0x56034   (est. sk_tcb_au)
 * Ghidra: void FUN_00056034(long arg1)
 * sk_tcb_au: cL4 sk tcb au operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_tcb_au(long arg1)
{
  uint64_t *t0;
  uint64_t t1;
  
  t0 = (uint64_t *)sk_tpidrro;
  t1 = *t0;
  do {
    sk_svc(0);
    *t0 = t1;
  } while (arg1 == 1);
  return;
}




/* FUN_00056064 @ 0x56064   (est. sk_tcb_av)
 * Ghidra: void FUN_00056064(long arg1,undefined8 arg2)
 * sk_tcb_av: cL4 sk tcb av operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_tcb_av(long arg1,uint64_t arg2)
{
  uint64_t *t0;
  
  t0 = (uint64_t *)sk_tpidrro;
  *t0 = arg2;
  do {
    sk_svc(0);
    *t0 = arg2;
  } while (arg1 == 1);
  return;
}




/* FUN_00056098 @ 0x56098   (est. sk_tcb_aw)
 * Ghidra: bool FUN_00056098(long arg1,long arg2)
 * sk_tcb_aw: cL4 sk tcb aw operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

bool sk_tcb_aw(long arg1,long arg2)
{
  if (arg1 == 1) {
    *(uint64_t *)(arg2 + 8) = 1;
    *(char **)(arg2 + 0x10) = sk_str_43;
    *(uint8_t *)(arg2 + 0x18) = 0;
    *(uint32_t *)(arg2 + 0x1c) = 0xffffffff;
    *(uint8_t *)(arg2 + 0x20) = 0;
    *(uint64_t *)(arg2 + 0x28) = 0;
    *(uint8_t *)(arg2 + 0x30) = 1;
    *(uint32_t *)(arg2 + 0x34) = 3;
    *(int *)(arg2 + 0x38) = (int)sk_global_005;
    *(uint8_t **)(arg2 + 0x40) = &LAB_00056410;
    *(uint8_t **)(arg2 + 0x48) = &LAB_00056428;
    *(uint8_t **)(arg2 + 0x50) = &LAB_00056440;
    *(sk_code_t *)(arg2 + 0x58) = sk_cap_op_b;
    *(uint8_t **)(arg2 + 0x60) = &LAB_0005645c;
    *(sk_code_t *)(arg2 + 0x68) = sk_cap_op_c;
    *(uint8_t **)(arg2 + 0x70) = &LAB_00056474;
    *(uint8_t **)(arg2 + 0x78) = &LAB_000564ac;
    *(uint8_t **)(arg2 + 0x80) = &LAB_000564c4;
    *(uint8_t **)(arg2 + 0x88) = &LAB_000564dc;
    *(uint8_t **)(arg2 + 0x90) = &LAB_00056504;
    *(sk_code_t *)(arg2 + 0x98) = sk_cap_op_d;
    *(uint8_t *)(arg2 + 0xa0) = 1;
    *(uint32_t *)(arg2 + 0xa4) = 4;
    *(uint8_t **)(arg2 + 0xa8) = &LAB_00056528;
    *(uint8_t **)(arg2 + 0xb0) = &LAB_00056530;
    *(uint8_t **)(arg2 + 0xb8) = &LAB_00056538;
    *(uint8_t **)(arg2 + 0xc0) = &LAB_00056540;
    *(uint64_t *)(arg2 + 0xd0) = 0xc;
    *(uint8_t **)(arg2 + 0xd8) = &LAB_00056548;
    *(uint8_t **)(arg2 + 0xe0) = &LAB_00056550;
    *(uint8_t **)(arg2 + 0xe8) = &LAB_00056558;
    *(uint16_t *)(arg2 + 0xf0) = 0x1601;
    *(uint32_t *)(arg2 + 0xf4) = 3;
    *(uint8_t **)(arg2 + 0xf8) = &LAB_00056560;
    *(uint8_t **)(arg2 + 0x100) = &LAB_00056580;
    *(uint8_t **)(arg2 + 0x108) = &LAB_0005659c;
    *(uint8_t **)(arg2 + 0x110) = &LAB_000565b4;
    *(uint8_t **)(arg2 + 0x118) = &LAB_000565bc;
    *(sk_code_t *)(arg2 + 0x120) = sk_cap_op_a;
    *(sk_code_t *)(arg2 + 0x128) = sk_cap_op_e;
    *(uint8_t **)(arg2 + 0x130) = &LAB_000565f0;
    *(sk_code_t *)(arg2 + 0x138) = sk_cap_op_f;
    *(uint16_t *)(arg2 + 0x149) = 0x1701;
    *(uint32_t *)(arg2 + 0x14c) = 1;
    *(uint8_t **)(arg2 + 0x150) = &LAB_0005660c;
    *(uint8_t **)(arg2 + 0x158) = &LAB_0005662c;
    *(sk_code_t *)(arg2 + 0x160) = sk_cap_op_g;
    *(uint8_t **)(arg2 + 0x168) = &LAB_0005664c;
    *(uint8_t **)(arg2 + 0x170) = &LAB_00056694;
    *(uint8_t *)(arg2 + 0x140) = 1;
    *(uint32_t *)(arg2 + 0x144) = 5;
    *(uint8_t *)(arg2 + 0x148) = 0;
    *(uint8_t *)(arg2 + 0x178) = 0x1a;
    *(uint8_t **)(arg2 + 0x180) = &sk_global_009;
    *(uint8_t **)(arg2 + 0x188) = &sk_global_010;
    *(uint64_t *)(arg2 + 400) = 0x64d260;
    *(uint8_t **)(arg2 + 0x198) = &LAB_000566d4;
    *(uint8_t **)(arg2 + 0x1a0) = &LAB_000566dc;
    *(uint8_t *)(arg2 + 0x1a8) = 1;
    *(uint64_t *)(arg2 + 0x1b0) = 1;
    *(uint32_t *)(arg2 + 0x1b8) = 0;
  }
  return arg1 == 1;
}




/* FUN_000565c4 @ 0x565c4   (est. sk_cap_op_a)
 * Ghidra: void FUN_000565c4(undefined8 arg1,undefined8 arg2,undefined8 arg3,undefined8 arg4)
 * sk_cap_op_a: cL4 sk cap op a operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_cap_op_a(uint64_t arg1,uint64_t arg2,uint64_t arg3,uint64_t arg4)
{
  uint64_t *t0;
  
  t0 = (uint64_t *)sk_tpidrro;
  *t0 = arg2;
  t0[1] = arg3;
  t0[2] = arg4;
  sk_svc(0);
  *t0 = arg2;
  return;
}




/* FUN_000566e8 @ 0x566e8   (est. sk_cap_op_b)
 * Ghidra: void FUN_000566e8(long arg1)
 * sk_cap_op_b: cL4 sk cap op b operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_cap_op_b(long arg1)
{
  uint64_t *t0;
  uint64_t t1;
  
  t0 = (uint64_t *)sk_tpidrro;
  t1 = *t0;
  do {
    sk_svc(0);
    *t0 = t1;
  } while (arg1 == 1);
  return;
}




/* FUN_00056718 @ 0x56718   (est. sk_cap_op_c)
 * Ghidra: void FUN_00056718(long arg1)
 * sk_cap_op_c: cL4 sk cap op c operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_cap_op_c(long arg1)
{
  uint64_t *t0;
  uint64_t t1;
  
  t0 = (uint64_t *)sk_tpidrro;
  t1 = *t0;
  do {
    sk_svc(0);
    *t0 = t1;
  } while (arg1 == 1);
  return;
}




/* FUN_00056748 @ 0x56748   (est. sk_cap_op_d)
 * Ghidra: void FUN_00056748(long arg1)
 * sk_cap_op_d: cL4 sk cap op d operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_cap_op_d(long arg1)
{
  uint64_t *t0;
  uint64_t t1;
  
  t0 = (uint64_t *)sk_tpidrro;
  t1 = *t0;
  do {
    sk_svc(0);
    *t0 = t1;
  } while (arg1 == 1);
  return;
}




/* FUN_00056778 @ 0x56778   (est. sk_cap_op_e)
 * Ghidra: void FUN_00056778(long arg1)
 * sk_cap_op_e: cL4 sk cap op e operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_cap_op_e(long arg1)
{
  uint64_t *t0;
  uint64_t t1;
  
  t0 = (uint64_t *)sk_tpidrro;
  t1 = *t0;
  do {
    sk_svc(0);
    *t0 = t1;
  } while (arg1 == 1);
  return;
}




/* FUN_000567a8 @ 0x567a8   (est. sk_cap_op_f)
 * Ghidra: void FUN_000567a8(long arg1)
 * sk_cap_op_f: cL4 sk cap op f operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_cap_op_f(long arg1)
{
  uint64_t *t0;
  uint64_t t1;
  
  t0 = (uint64_t *)sk_tpidrro;
  t1 = *t0;
  do {
    sk_svc(0);
    *t0 = t1;
  } while (arg1 == 1);
  return;
}




/* FUN_000567d8 @ 0x567d8   (est. sk_cap_op_g)
 * Ghidra: void FUN_000567d8(long arg1,undefined8 arg2)
 * sk_cap_op_g: cL4 sk cap op g operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_cap_op_g(long arg1,uint64_t arg2)
{
  uint64_t *t0;
  
  t0 = (uint64_t *)sk_tpidrro;
  *t0 = arg2;
  do {
    sk_svc(0);
    *t0 = arg2;
  } while (arg1 == 1);
  return;
}




/* FUN_0005680c @ 0x5680c   (est. sk_cap_cmp)
 * Ghidra: bool FUN_0005680c(long arg1,long arg2)
 * sk_cap_cmp: cL4 sk cap cmp operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

bool sk_cap_cmp(long arg1,long arg2)
{
  if (arg1 == 0x100000001) {
    *(uint64_t *)(arg2 + 8) = 0x100000001;
    *(char **)(arg2 + 0x10) = sk_str_43;
    *(uint8_t *)(arg2 + 0x18) = 0;
    *(uint32_t *)(arg2 + 0x1c) = 0xffffffff;
    *(uint8_t *)(arg2 + 0x20) = 0;
    *(uint64_t *)(arg2 + 0x28) = 0;
    *(uint8_t *)(arg2 + 0x30) = 1;
    *(uint32_t *)(arg2 + 0x34) = 3;
    *(int *)(arg2 + 0x38) = (int)sk_global_005;
    *(uint8_t **)(arg2 + 0x40) = &LAB_00056b88;
    *(uint8_t **)(arg2 + 0x48) = &LAB_00056ba0;
    *(uint8_t **)(arg2 + 0x50) = &LAB_00056bb8;
    *(sk_code_t *)(arg2 + 0x58) = sk_cap_op_i;
    *(uint8_t **)(arg2 + 0x60) = &LAB_00056bd4;
    *(sk_code_t *)(arg2 + 0x68) = sk_cap_op_j;
    *(uint8_t **)(arg2 + 0x70) = &LAB_00056bec;
    *(uint8_t **)(arg2 + 0x78) = &LAB_00056c24;
    *(uint8_t **)(arg2 + 0x80) = &LAB_00056c3c;
    *(uint8_t **)(arg2 + 0x88) = &LAB_00056c54;
    *(uint8_t **)(arg2 + 0x90) = &LAB_00056c7c;
    *(sk_code_t *)(arg2 + 0x98) = sk_cap_op_k;
    *(uint8_t *)(arg2 + 0xa0) = 1;
    *(uint32_t *)(arg2 + 0xa4) = 4;
    *(uint8_t **)(arg2 + 0xa8) = &LAB_00056ca0;
    *(uint8_t **)(arg2 + 0xb0) = &LAB_00056ca8;
    *(uint8_t **)(arg2 + 0xb8) = &LAB_00056cb0;
    *(uint8_t **)(arg2 + 0xc0) = &LAB_00056cb8;
    *(uint64_t *)(arg2 + 0xd0) = 0xc;
    *(uint8_t **)(arg2 + 0xd8) = &LAB_00056cc0;
    *(uint8_t **)(arg2 + 0xe0) = &LAB_00056cc8;
    *(uint8_t **)(arg2 + 0xe8) = &LAB_00056cd0;
    *(uint16_t *)(arg2 + 0xf0) = 0x1601;
    *(uint32_t *)(arg2 + 0xf4) = 3;
    *(uint8_t **)(arg2 + 0xf8) = &LAB_00056cd8;
    *(uint8_t **)(arg2 + 0x100) = &LAB_00056cf8;
    *(uint8_t **)(arg2 + 0x108) = &LAB_00056d14;
    *(uint8_t **)(arg2 + 0x110) = &LAB_00056d2c;
    *(uint8_t **)(arg2 + 0x118) = &LAB_00056d34;
    *(sk_code_t *)(arg2 + 0x120) = sk_cap_op_h;
    *(sk_code_t *)(arg2 + 0x128) = sk_cap_op_l;
    *(uint8_t **)(arg2 + 0x130) = &LAB_00056d68;
    *(sk_code_t *)(arg2 + 0x138) = sk_cap_op_m;
    *(uint16_t *)(arg2 + 0x149) = 0x1701;
    *(uint32_t *)(arg2 + 0x14c) = 1;
    *(uint8_t **)(arg2 + 0x150) = &LAB_00056d84;
    *(uint8_t **)(arg2 + 0x158) = &LAB_00056da4;
    *(sk_code_t *)(arg2 + 0x160) = sk_cap_op_n;
    *(uint8_t **)(arg2 + 0x168) = &LAB_00056dc4;
    *(uint8_t **)(arg2 + 0x170) = &LAB_00056e0c;
    *(uint8_t *)(arg2 + 0x140) = 1;
    *(uint32_t *)(arg2 + 0x144) = 5;
    *(uint8_t *)(arg2 + 0x148) = 0;
    *(uint8_t *)(arg2 + 0x178) = 0x1a;
    *(uint8_t **)(arg2 + 0x180) = &sk_global_011;
    *(uint8_t **)(arg2 + 0x188) = &sk_global_012;
    *(uint64_t *)(arg2 + 400) = 0x64d330;
    *(uint8_t **)(arg2 + 0x198) = &LAB_00056e4c;
    *(uint8_t **)(arg2 + 0x1a0) = &LAB_00056e54;
    *(uint8_t *)(arg2 + 0x1a8) = 1;
    *(uint64_t *)(arg2 + 0x1b0) = 1;
    *(uint32_t *)(arg2 + 0x1b8) = 0;
  }
  return arg1 == 0x100000001;
}




/* FUN_00056d3c @ 0x56d3c   (est. sk_cap_op_h)
 * Ghidra: void FUN_00056d3c(undefined8 arg1,undefined8 arg2,undefined8 arg3,undefined8 arg4)
 * sk_cap_op_h: cL4 sk cap op h operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_cap_op_h(uint64_t arg1,uint64_t arg2,uint64_t arg3,uint64_t arg4)
{
  uint64_t *t0;
  
  t0 = (uint64_t *)sk_tpidrro;
  *t0 = arg2;
  t0[1] = arg3;
  t0[2] = arg4;
  sk_svc(0);
  *t0 = arg2;
  return;
}




/* FUN_00056e60 @ 0x56e60   (est. sk_cap_op_i)
 * Ghidra: void FUN_00056e60(long arg1)
 * sk_cap_op_i: cL4 sk cap op i operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_cap_op_i(long arg1)
{
  uint64_t *t0;
  uint64_t t1;
  
  t0 = (uint64_t *)sk_tpidrro;
  t1 = *t0;
  do {
    sk_svc(0);
    *t0 = t1;
  } while (arg1 == 1);
  return;
}




/* FUN_00056e90 @ 0x56e90   (est. sk_cap_op_j)
 * Ghidra: void FUN_00056e90(long arg1)
 * sk_cap_op_j: cL4 sk cap op j operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_cap_op_j(long arg1)
{
  uint64_t *t0;
  uint64_t t1;
  
  t0 = (uint64_t *)sk_tpidrro;
  t1 = *t0;
  do {
    sk_svc(0);
    *t0 = t1;
  } while (arg1 == 1);
  return;
}




/* FUN_00056ec0 @ 0x56ec0   (est. sk_cap_op_k)
 * Ghidra: void FUN_00056ec0(long arg1)
 * sk_cap_op_k: cL4 sk cap op k operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_cap_op_k(long arg1)
{
  uint64_t *t0;
  uint64_t t1;
  
  t0 = (uint64_t *)sk_tpidrro;
  t1 = *t0;
  do {
    sk_svc(0);
    *t0 = t1;
  } while (arg1 == 1);
  return;
}




/* FUN_00056ef0 @ 0x56ef0   (est. sk_cap_op_l)
 * Ghidra: void FUN_00056ef0(long arg1)
 * sk_cap_op_l: cL4 sk cap op l operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_cap_op_l(long arg1)
{
  uint64_t *t0;
  uint64_t t1;
  
  t0 = (uint64_t *)sk_tpidrro;
  t1 = *t0;
  do {
    sk_svc(0);
    *t0 = t1;
  } while (arg1 == 1);
  return;
}




/* FUN_00056f20 @ 0x56f20   (est. sk_cap_op_m)
 * Ghidra: void FUN_00056f20(long arg1)
 * sk_cap_op_m: cL4 sk cap op m operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_cap_op_m(long arg1)
{
  uint64_t *t0;
  uint64_t t1;
  
  t0 = (uint64_t *)sk_tpidrro;
  t1 = *t0;
  do {
    sk_svc(0);
    *t0 = t1;
  } while (arg1 == 1);
  return;
}




/* FUN_00056f50 @ 0x56f50   (est. sk_cap_op_n)
 * Ghidra: void FUN_00056f50(long arg1,undefined8 arg2)
 * sk_cap_op_n: cL4 sk cap op n operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_cap_op_n(long arg1,uint64_t arg2)
{
  uint64_t *t0;
  
  t0 = (uint64_t *)sk_tpidrro;
  *t0 = arg2;
  do {
    sk_svc(0);
    *t0 = arg2;
  } while (arg1 == 1);
  return;
}




/* FUN_00056f84 @ 0x56f84   (est. sk_cap_cmp2)
 * Ghidra: bool FUN_00056f84(long arg1,long arg2)
 * sk_cap_cmp2: cL4 sk cap cmp2 operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

bool sk_cap_cmp2(long arg1,long arg2)
{
  if (arg1 == 0x200000001) {
    *(uint64_t *)(arg2 + 8) = 0x200000001;
    *(char **)(arg2 + 0x10) = sk_str_43;
    *(uint8_t *)(arg2 + 0x18) = 0;
    *(uint32_t *)(arg2 + 0x1c) = 0xffffffff;
    *(uint8_t *)(arg2 + 0x20) = 0;
    *(uint64_t *)(arg2 + 0x28) = 0;
    *(uint8_t *)(arg2 + 0x30) = 1;
    *(uint32_t *)(arg2 + 0x34) = 3;
    *(int *)(arg2 + 0x38) = (int)sk_global_005;
    *(uint8_t **)(arg2 + 0x40) = &LAB_0005730c;
    *(uint8_t **)(arg2 + 0x48) = &LAB_00057324;
    *(uint8_t **)(arg2 + 0x50) = &LAB_0005733c;
    *(sk_code_t *)(arg2 + 0x58) = sk_cap_op_p;
    *(uint8_t **)(arg2 + 0x60) = &LAB_00057358;
    *(sk_code_t *)(arg2 + 0x68) = sk_cap_op_q;
    *(uint8_t **)(arg2 + 0x70) = &LAB_00057370;
    *(uint8_t **)(arg2 + 0x78) = &LAB_000573a8;
    *(uint8_t **)(arg2 + 0x80) = &LAB_000573c0;
    *(uint8_t **)(arg2 + 0x88) = &LAB_000573d8;
    *(uint8_t **)(arg2 + 0x90) = &LAB_00057400;
    *(sk_code_t *)(arg2 + 0x98) = sk_cap_op_r;
    *(uint8_t *)(arg2 + 0xa0) = 1;
    *(uint32_t *)(arg2 + 0xa4) = 4;
    *(uint8_t **)(arg2 + 0xa8) = &LAB_00057424;
    *(uint8_t **)(arg2 + 0xb0) = &LAB_0005742c;
    *(uint8_t **)(arg2 + 0xb8) = &LAB_00057434;
    *(uint8_t **)(arg2 + 0xc0) = &LAB_0005743c;
    *(uint64_t *)(arg2 + 0xd0) = 0xc;
    *(uint8_t **)(arg2 + 0xd8) = &LAB_00057444;
    *(uint8_t **)(arg2 + 0xe0) = &LAB_0005744c;
    *(uint8_t **)(arg2 + 0xe8) = &LAB_00057454;
    *(uint16_t *)(arg2 + 0xf0) = 0x1601;
    *(uint32_t *)(arg2 + 0xf4) = 3;
    *(uint8_t **)(arg2 + 0xf8) = &LAB_0005745c;
    *(uint8_t **)(arg2 + 0x100) = &LAB_0005747c;
    *(uint8_t **)(arg2 + 0x108) = &LAB_00057498;
    *(uint8_t **)(arg2 + 0x110) = &LAB_000574b0;
    *(uint8_t **)(arg2 + 0x118) = &LAB_000574b8;
    *(sk_code_t *)(arg2 + 0x120) = sk_cap_op_o;
    *(sk_code_t *)(arg2 + 0x128) = sk_cap_op_s;
    *(uint8_t **)(arg2 + 0x130) = &LAB_000574ec;
    *(sk_code_t *)(arg2 + 0x138) = sk_cap_op_t;
    *(uint16_t *)(arg2 + 0x149) = 0x1701;
    *(uint32_t *)(arg2 + 0x14c) = 1;
    *(uint8_t **)(arg2 + 0x150) = &LAB_00057508;
    *(uint8_t **)(arg2 + 0x158) = &LAB_00057528;
    *(sk_code_t *)(arg2 + 0x160) = sk_cap_op_u;
    *(uint8_t **)(arg2 + 0x168) = &LAB_00057548;
    *(uint8_t **)(arg2 + 0x170) = &LAB_00057590;
    *(uint8_t *)(arg2 + 0x140) = 1;
    *(uint32_t *)(arg2 + 0x144) = 5;
    *(uint8_t *)(arg2 + 0x148) = 0;
    *(uint8_t *)(arg2 + 0x178) = 0x1a;
    *(uint8_t **)(arg2 + 0x180) = &sk_global_013;
    *(uint8_t **)(arg2 + 0x188) = &sk_global_014;
    *(uint64_t *)(arg2 + 400) = 0x64d400;
    *(uint8_t **)(arg2 + 0x198) = &LAB_000575d0;
    *(uint8_t **)(arg2 + 0x1a0) = &LAB_000575d8;
    *(uint8_t *)(arg2 + 0x1a8) = 1;
    *(uint64_t *)(arg2 + 0x1b0) = 1;
    *(int *)(arg2 + 0x1b8) = (int)sk_global_006;
  }
  return arg1 == 0x200000001;
}




/* FUN_000574c0 @ 0x574c0   (est. sk_cap_op_o)
 * Ghidra: void FUN_000574c0(undefined8 arg1,undefined8 arg2,undefined8 arg3,undefined8 arg4)
 * sk_cap_op_o: cL4 sk cap op o operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_cap_op_o(uint64_t arg1,uint64_t arg2,uint64_t arg3,uint64_t arg4)
{
  uint64_t *t0;
  
  t0 = (uint64_t *)sk_tpidrro;
  *t0 = arg2;
  t0[1] = arg3;
  t0[2] = arg4;
  sk_svc(0);
  *t0 = arg2;
  return;
}




/* FUN_000575e4 @ 0x575e4   (est. sk_cap_op_p)
 * Ghidra: void FUN_000575e4(long arg1)
 * sk_cap_op_p: cL4 sk cap op p operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_cap_op_p(long arg1)
{
  uint64_t *t0;
  uint64_t t1;
  
  t0 = (uint64_t *)sk_tpidrro;
  t1 = *t0;
  do {
    sk_svc(0);
    *t0 = t1;
  } while (arg1 == 1);
  return;
}




/* FUN_00057614 @ 0x57614   (est. sk_cap_op_q)
 * Ghidra: void FUN_00057614(long arg1)
 * sk_cap_op_q: cL4 sk cap op q operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_cap_op_q(long arg1)
{
  uint64_t *t0;
  uint64_t t1;
  
  t0 = (uint64_t *)sk_tpidrro;
  t1 = *t0;
  do {
    sk_svc(0);
    *t0 = t1;
  } while (arg1 == 1);
  return;
}




/* FUN_00057644 @ 0x57644   (est. sk_cap_op_r)
 * Ghidra: void FUN_00057644(long arg1)
 * sk_cap_op_r: cL4 sk cap op r operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_cap_op_r(long arg1)
{
  uint64_t *t0;
  uint64_t t1;
  
  t0 = (uint64_t *)sk_tpidrro;
  t1 = *t0;
  do {
    sk_svc(0);
    *t0 = t1;
  } while (arg1 == 1);
  return;
}




/* FUN_00057674 @ 0x57674   (est. sk_cap_op_s)
 * Ghidra: void FUN_00057674(long arg1)
 * sk_cap_op_s: cL4 sk cap op s operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_cap_op_s(long arg1)
{
  uint64_t *t0;
  uint64_t t1;
  
  t0 = (uint64_t *)sk_tpidrro;
  t1 = *t0;
  do {
    sk_svc(0);
    *t0 = t1;
  } while (arg1 == 1);
  return;
}




/* FUN_000576a4 @ 0x576a4   (est. sk_cap_op_t)
 * Ghidra: void FUN_000576a4(long arg1)
 * sk_cap_op_t: cL4 sk cap op t operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_cap_op_t(long arg1)
{
  uint64_t *t0;
  uint64_t t1;
  
  t0 = (uint64_t *)sk_tpidrro;
  t1 = *t0;
  do {
    sk_svc(0);
    *t0 = t1;
  } while (arg1 == 1);
  return;
}




/* FUN_000576d4 @ 0x576d4   (est. sk_cap_op_u)
 * Ghidra: void FUN_000576d4(long arg1,undefined8 arg2)
 * sk_cap_op_u: cL4 sk cap op u operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_cap_op_u(long arg1,uint64_t arg2)
{
  uint64_t *t0;
  
  t0 = (uint64_t *)sk_tpidrro;
  *t0 = arg2;
  do {
    sk_svc(0);
    *t0 = arg2;
  } while (arg1 == 1);
  return;
}




/* FUN_00057708 @ 0x57708   (est. sk_cap_cmp3)
 * Ghidra: bool FUN_00057708(long arg1,long arg2)
 * sk_cap_cmp3: cL4 sk cap cmp3 operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

bool sk_cap_cmp3(long arg1,long arg2)
{
  if (arg1 == 0x300000001) {
    *(uint64_t *)(arg2 + 8) = 0x300000001;
    *(char **)(arg2 + 0x10) = sk_str_43;
    *(uint8_t *)(arg2 + 0x18) = 0;
    *(uint32_t *)(arg2 + 0x1c) = 0xffffffff;
    *(uint8_t *)(arg2 + 0x20) = 0;
    *(uint64_t *)(arg2 + 0x28) = 0;
    *(uint8_t *)(arg2 + 0x30) = 1;
    *(uint32_t *)(arg2 + 0x34) = 3;
    *(int *)(arg2 + 0x38) = (int)sk_global_005;
    *(uint8_t **)(arg2 + 0x40) = &LAB_00057a90;
    *(uint8_t **)(arg2 + 0x48) = &LAB_00057aa8;
    *(uint8_t **)(arg2 + 0x50) = &LAB_00057ac0;
    *(sk_code_t *)(arg2 + 0x58) = sk_cap_op_w;
    *(uint8_t **)(arg2 + 0x60) = &LAB_00057adc;
    *(sk_code_t *)(arg2 + 0x68) = sk_cap_op_x;
    *(uint8_t **)(arg2 + 0x70) = &LAB_00057af4;
    *(uint8_t **)(arg2 + 0x78) = &LAB_00057b2c;
    *(uint8_t **)(arg2 + 0x80) = &LAB_00057b44;
    *(uint8_t **)(arg2 + 0x88) = &LAB_00057b5c;
    *(uint8_t **)(arg2 + 0x90) = &LAB_00057b84;
    *(sk_code_t *)(arg2 + 0x98) = sk_cap_op_y;
    *(uint8_t *)(arg2 + 0xa0) = 1;
    *(uint32_t *)(arg2 + 0xa4) = 4;
    *(uint8_t **)(arg2 + 0xa8) = &LAB_00057ba8;
    *(uint8_t **)(arg2 + 0xb0) = &LAB_00057bb0;
    *(uint8_t **)(arg2 + 0xb8) = &LAB_00057bb8;
    *(uint8_t **)(arg2 + 0xc0) = &LAB_00057bc0;
    *(uint64_t *)(arg2 + 0xd0) = 0xc;
    *(uint8_t **)(arg2 + 0xd8) = &LAB_00057bc8;
    *(uint8_t **)(arg2 + 0xe0) = &LAB_00057bd0;
    *(uint8_t **)(arg2 + 0xe8) = &LAB_00057bd8;
    *(uint16_t *)(arg2 + 0xf0) = 0x1601;
    *(uint32_t *)(arg2 + 0xf4) = 3;
    *(uint8_t **)(arg2 + 0xf8) = &LAB_00057be0;
    *(uint8_t **)(arg2 + 0x100) = &LAB_00057c00;
    *(uint8_t **)(arg2 + 0x108) = &LAB_00057c1c;
    *(uint8_t **)(arg2 + 0x110) = &LAB_00057c34;
    *(uint8_t **)(arg2 + 0x118) = &LAB_00057c3c;
    *(sk_code_t *)(arg2 + 0x120) = sk_cap_op_v;
    *(sk_code_t *)(arg2 + 0x128) = sk_cap_op_z;
    *(uint8_t **)(arg2 + 0x130) = &LAB_00057c70;
    *(sk_code_t *)(arg2 + 0x138) = sk_cap_op_aa;
    *(uint16_t *)(arg2 + 0x149) = 0x1701;
    *(uint32_t *)(arg2 + 0x14c) = 1;
    *(uint8_t **)(arg2 + 0x150) = &LAB_00057c8c;
    *(uint8_t **)(arg2 + 0x158) = &LAB_00057cac;
    *(sk_code_t *)(arg2 + 0x160) = sk_cap_op_ab;
    *(uint8_t **)(arg2 + 0x168) = &LAB_00057ccc;
    *(uint8_t **)(arg2 + 0x170) = &LAB_00057d14;
    *(uint8_t *)(arg2 + 0x140) = 1;
    *(uint32_t *)(arg2 + 0x144) = 5;
    *(uint8_t *)(arg2 + 0x148) = 0;
    *(uint8_t *)(arg2 + 0x178) = 0x1a;
    *(uint8_t **)(arg2 + 0x180) = &sk_global_015;
    *(uint8_t **)(arg2 + 0x188) = &sk_global_016;
    *(uint64_t *)(arg2 + 400) = 0x64d4d0;
    *(uint8_t **)(arg2 + 0x198) = &LAB_00057d54;
    *(uint8_t **)(arg2 + 0x1a0) = &LAB_00057d5c;
    *(uint8_t *)(arg2 + 0x1a8) = 1;
    *(uint64_t *)(arg2 + 0x1b0) = 1;
    *(int *)(arg2 + 0x1b8) = (int)sk_global_006;
  }
  return arg1 == 0x300000001;
}




/* FUN_00057c44 @ 0x57c44   (est. sk_cap_op_v)
 * Ghidra: void FUN_00057c44(undefined8 arg1,undefined8 arg2,undefined8 arg3,undefined8 arg4)
 * sk_cap_op_v: cL4 sk cap op v operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_cap_op_v(uint64_t arg1,uint64_t arg2,uint64_t arg3,uint64_t arg4)
{
  uint64_t *t0;
  
  t0 = (uint64_t *)sk_tpidrro;
  *t0 = arg2;
  t0[1] = arg3;
  t0[2] = arg4;
  sk_svc(0);
  *t0 = arg2;
  return;
}




/* FUN_00057d68 @ 0x57d68   (est. sk_cap_op_w)
 * Ghidra: void FUN_00057d68(long arg1)
 * sk_cap_op_w: cL4 sk cap op w operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_cap_op_w(long arg1)
{
  uint64_t *t0;
  uint64_t t1;
  
  t0 = (uint64_t *)sk_tpidrro;
  t1 = *t0;
  do {
    sk_svc(0);
    *t0 = t1;
  } while (arg1 == 1);
  return;
}




/* FUN_00057d98 @ 0x57d98   (est. sk_cap_op_x)
 * Ghidra: void FUN_00057d98(long arg1)
 * sk_cap_op_x: cL4 sk cap op x operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_cap_op_x(long arg1)
{
  uint64_t *t0;
  uint64_t t1;
  
  t0 = (uint64_t *)sk_tpidrro;
  t1 = *t0;
  do {
    sk_svc(0);
    *t0 = t1;
  } while (arg1 == 1);
  return;
}




/* FUN_00057dc8 @ 0x57dc8   (est. sk_cap_op_y)
 * Ghidra: void FUN_00057dc8(long arg1)
 * sk_cap_op_y: cL4 sk cap op y operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_cap_op_y(long arg1)
{
  uint64_t *t0;
  uint64_t t1;
  
  t0 = (uint64_t *)sk_tpidrro;
  t1 = *t0;
  do {
    sk_svc(0);
    *t0 = t1;
  } while (arg1 == 1);
  return;
}




/* FUN_00057df8 @ 0x57df8   (est. sk_cap_op_z)
 * Ghidra: void FUN_00057df8(long arg1)
 * sk_cap_op_z: cL4 sk cap op z operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_cap_op_z(long arg1)
{
  uint64_t *t0;
  uint64_t t1;
  
  t0 = (uint64_t *)sk_tpidrro;
  t1 = *t0;
  do {
    sk_svc(0);
    *t0 = t1;
  } while (arg1 == 1);
  return;
}




/* FUN_00057e28 @ 0x57e28   (est. sk_cap_op_aa)
 * Ghidra: void FUN_00057e28(long arg1)
 * sk_cap_op_aa: cL4 sk cap op aa operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_cap_op_aa(long arg1)
{
  uint64_t *t0;
  uint64_t t1;
  
  t0 = (uint64_t *)sk_tpidrro;
  t1 = *t0;
  do {
    sk_svc(0);
    *t0 = t1;
  } while (arg1 == 1);
  return;
}




/* FUN_00057e58 @ 0x57e58   (est. sk_cap_op_ab)
 * Ghidra: void FUN_00057e58(long arg1,undefined8 arg2)
 * sk_cap_op_ab: cL4 sk cap op ab operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_cap_op_ab(long arg1,uint64_t arg2)
{
  uint64_t *t0;
  
  t0 = (uint64_t *)sk_tpidrro;
  *t0 = arg2;
  do {
    sk_svc(0);
    *t0 = arg2;
  } while (arg1 == 1);
  return;
}




/* FUN_00057e8c @ 0x57e8c   (est. sk_cap_cmp4)
 * Ghidra: bool FUN_00057e8c(long arg1,long arg2)
 * sk_cap_cmp4: cL4 sk cap cmp4 operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

bool sk_cap_cmp4(long arg1,long arg2)
{
  if (arg1 == 0x400000001) {
    *(uint64_t *)(arg2 + 8) = 0x400000001;
    *(char **)(arg2 + 0x10) = sk_str_43;
    *(uint8_t *)(arg2 + 0x18) = 0;
    *(uint32_t *)(arg2 + 0x1c) = 0xffffffff;
    *(uint8_t *)(arg2 + 0x20) = 0;
    *(uint64_t *)(arg2 + 0x28) = 0;
    *(uint8_t *)(arg2 + 0x30) = 1;
    *(uint32_t *)(arg2 + 0x34) = 3;
    *(int *)(arg2 + 0x38) = (int)sk_global_005;
    *(uint8_t **)(arg2 + 0x40) = &LAB_00058210;
    *(uint8_t **)(arg2 + 0x48) = &LAB_00058228;
    *(uint8_t **)(arg2 + 0x50) = &LAB_00058240;
    *(sk_code_t *)(arg2 + 0x58) = sk_cap_op_ad;
    *(uint8_t **)(arg2 + 0x60) = &LAB_0005825c;
    *(sk_code_t *)(arg2 + 0x68) = sk_cap_op_ae;
    *(uint8_t **)(arg2 + 0x70) = &LAB_00058274;
    *(uint8_t **)(arg2 + 0x78) = &LAB_000582ac;
    *(uint8_t **)(arg2 + 0x80) = &LAB_000582c4;
    *(uint8_t **)(arg2 + 0x88) = &LAB_000582dc;
    *(uint8_t **)(arg2 + 0x90) = &LAB_00058304;
    *(sk_code_t *)(arg2 + 0x98) = sk_cap_op_af;
    *(uint8_t *)(arg2 + 0xa0) = 1;
    *(uint32_t *)(arg2 + 0xa4) = 4;
    *(uint8_t **)(arg2 + 0xa8) = &LAB_00058328;
    *(uint8_t **)(arg2 + 0xb0) = &LAB_00058330;
    *(uint8_t **)(arg2 + 0xb8) = &LAB_00058338;
    *(uint8_t **)(arg2 + 0xc0) = &LAB_00058340;
    *(uint64_t *)(arg2 + 0xd0) = 0xc;
    *(uint8_t **)(arg2 + 0xd8) = &LAB_00058348;
    *(uint8_t **)(arg2 + 0xe0) = &LAB_00058350;
    *(uint8_t **)(arg2 + 0xe8) = &LAB_00058358;
    *(uint16_t *)(arg2 + 0xf0) = 0x1601;
    *(uint32_t *)(arg2 + 0xf4) = 3;
    *(uint8_t **)(arg2 + 0xf8) = &LAB_00058360;
    *(uint8_t **)(arg2 + 0x100) = &LAB_00058380;
    *(uint8_t **)(arg2 + 0x108) = &LAB_0005839c;
    *(uint8_t **)(arg2 + 0x110) = &LAB_000583b4;
    *(uint8_t **)(arg2 + 0x118) = &LAB_000583bc;
    *(sk_code_t *)(arg2 + 0x120) = sk_cap_op_ac;
    *(sk_code_t *)(arg2 + 0x128) = sk_cap_op_ag;
    *(uint8_t **)(arg2 + 0x130) = &LAB_000583f0;
    *(sk_code_t *)(arg2 + 0x138) = sk_cap_op_ah;
    *(uint16_t *)(arg2 + 0x149) = 0x1701;
    *(uint32_t *)(arg2 + 0x14c) = 1;
    *(uint8_t **)(arg2 + 0x150) = &LAB_0005840c;
    *(uint8_t **)(arg2 + 0x158) = &LAB_0005842c;
    *(sk_code_t *)(arg2 + 0x160) = sk_cap_op_ai;
    *(uint8_t **)(arg2 + 0x168) = &LAB_0005844c;
    *(uint8_t **)(arg2 + 0x170) = &LAB_00058494;
    *(uint8_t *)(arg2 + 0x140) = 1;
    *(uint32_t *)(arg2 + 0x144) = 5;
    *(uint8_t *)(arg2 + 0x148) = 0;
    *(uint8_t *)(arg2 + 0x178) = 0x1a;
    *(uint8_t **)(arg2 + 0x180) = &sk_global_017;
    *(uint8_t **)(arg2 + 0x188) = &sk_global_018;
    *(uint64_t *)(arg2 + 400) = 0x64d5a0;
    *(uint8_t **)(arg2 + 0x198) = &LAB_000584d4;
    *(uint8_t **)(arg2 + 0x1a0) = &LAB_000584dc;
    *(uint8_t *)(arg2 + 0x1a8) = 1;
    *(uint64_t *)(arg2 + 0x1b0) = 1;
    *(uint32_t *)(arg2 + 0x1b8) = 1;
  }
  return arg1 == 0x400000001;
}




/* FUN_000583c4 @ 0x583c4   (est. sk_cap_op_ac)
 * Ghidra: void FUN_000583c4(undefined8 arg1,undefined8 arg2,undefined8 arg3,undefined8 arg4)
 * sk_cap_op_ac: cL4 sk cap op ac operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_cap_op_ac(uint64_t arg1,uint64_t arg2,uint64_t arg3,uint64_t arg4)
{
  uint64_t *t0;
  
  t0 = (uint64_t *)sk_tpidrro;
  *t0 = arg2;
  t0[1] = arg3;
  t0[2] = arg4;
  sk_svc(0);
  *t0 = arg2;
  return;
}




/* FUN_000584e8 @ 0x584e8   (est. sk_cap_op_ad)
 * Ghidra: void FUN_000584e8(long arg1)
 * sk_cap_op_ad: cL4 sk cap op ad operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_cap_op_ad(long arg1)
{
  uint64_t *t0;
  uint64_t t1;
  
  t0 = (uint64_t *)sk_tpidrro;
  t1 = *t0;
  do {
    sk_svc(0);
    *t0 = t1;
  } while (arg1 == 1);
  return;
}




/* FUN_00058518 @ 0x58518   (est. sk_cap_op_ae)
 * Ghidra: void FUN_00058518(long arg1)
 * sk_cap_op_ae: cL4 sk cap op ae operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_cap_op_ae(long arg1)
{
  uint64_t *t0;
  uint64_t t1;
  
  t0 = (uint64_t *)sk_tpidrro;
  t1 = *t0;
  do {
    sk_svc(0);
    *t0 = t1;
  } while (arg1 == 1);
  return;
}




/* FUN_00058548 @ 0x58548   (est. sk_cap_op_af)
 * Ghidra: void FUN_00058548(long arg1)
 * sk_cap_op_af: cL4 sk cap op af operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_cap_op_af(long arg1)
{
  uint64_t *t0;
  uint64_t t1;
  
  t0 = (uint64_t *)sk_tpidrro;
  t1 = *t0;
  do {
    sk_svc(0);
    *t0 = t1;
  } while (arg1 == 1);
  return;
}




/* FUN_00058578 @ 0x58578   (est. sk_cap_op_ag)
 * Ghidra: void FUN_00058578(long arg1)
 * sk_cap_op_ag: cL4 sk cap op ag operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_cap_op_ag(long arg1)
{
  uint64_t *t0;
  uint64_t t1;
  
  t0 = (uint64_t *)sk_tpidrro;
  t1 = *t0;
  do {
    sk_svc(0);
    *t0 = t1;
  } while (arg1 == 1);
  return;
}




/* FUN_000585a8 @ 0x585a8   (est. sk_cap_op_ah)
 * Ghidra: void FUN_000585a8(long arg1)
 * sk_cap_op_ah: cL4 sk cap op ah operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_cap_op_ah(long arg1)
{
  uint64_t *t0;
  uint64_t t1;
  
  t0 = (uint64_t *)sk_tpidrro;
  t1 = *t0;
  do {
    sk_svc(0);
    *t0 = t1;
  } while (arg1 == 1);
  return;
}




/* FUN_000585d8 @ 0x585d8   (est. sk_cap_op_ai)
 * Ghidra: void FUN_000585d8(long arg1,undefined8 arg2)
 * sk_cap_op_ai: cL4 sk cap op ai operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_cap_op_ai(long arg1,uint64_t arg2)
{
  uint64_t *t0;
  
  t0 = (uint64_t *)sk_tpidrro;
  *t0 = arg2;
  do {
    sk_svc(0);
    *t0 = arg2;
  } while (arg1 == 1);
  return;
}




/* FUN_0005860c @ 0x5860c   (est. sk_cap_cmp5)
 * Ghidra: bool FUN_0005860c(long arg1,long arg2)
 * sk_cap_cmp5: cL4 sk cap cmp5 operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

bool sk_cap_cmp5(long arg1,long arg2)
{
  if (arg1 == 0x500000001) {
    *(uint64_t *)(arg2 + 8) = 0x500000001;
    *(char **)(arg2 + 0x10) = sk_str_43;
    *(uint8_t *)(arg2 + 0x18) = 0;
    *(uint32_t *)(arg2 + 0x1c) = 0xffffffff;
    *(uint8_t *)(arg2 + 0x20) = 0;
    *(uint64_t *)(arg2 + 0x28) = 0;
    *(uint8_t *)(arg2 + 0x30) = 1;
    *(uint32_t *)(arg2 + 0x34) = 3;
    *(int *)(arg2 + 0x38) = (int)sk_global_005;
    *(uint8_t **)(arg2 + 0x40) = &LAB_00058990;
    *(uint8_t **)(arg2 + 0x48) = &LAB_000589a8;
    *(uint8_t **)(arg2 + 0x50) = &LAB_000589c0;
    *(sk_code_t *)(arg2 + 0x58) = sk_cap_op_ak;
    *(uint8_t **)(arg2 + 0x60) = &LAB_000589dc;
    *(sk_code_t *)(arg2 + 0x68) = sk_cap_op_al;
    *(uint8_t **)(arg2 + 0x70) = &LAB_000589f4;
    *(uint8_t **)(arg2 + 0x78) = &LAB_00058a2c;
    *(uint8_t **)(arg2 + 0x80) = &LAB_00058a44;
    *(uint8_t **)(arg2 + 0x88) = &LAB_00058a5c;
    *(uint8_t **)(arg2 + 0x90) = &LAB_00058a84;
    *(sk_code_t *)(arg2 + 0x98) = sk_cap_op_am;
    *(uint8_t *)(arg2 + 0xa0) = 1;
    *(uint32_t *)(arg2 + 0xa4) = 4;
    *(uint8_t **)(arg2 + 0xa8) = &LAB_00058aa8;
    *(uint8_t **)(arg2 + 0xb0) = &LAB_00058ab0;
    *(uint8_t **)(arg2 + 0xb8) = &LAB_00058ab8;
    *(uint8_t **)(arg2 + 0xc0) = &LAB_00058ac0;
    *(uint64_t *)(arg2 + 0xd0) = 0xc;
    *(uint8_t **)(arg2 + 0xd8) = &LAB_00058ac8;
    *(uint8_t **)(arg2 + 0xe0) = &LAB_00058ad0;
    *(uint8_t **)(arg2 + 0xe8) = &LAB_00058ad8;
    *(uint16_t *)(arg2 + 0xf0) = 0x1601;
    *(uint32_t *)(arg2 + 0xf4) = 3;
    *(uint8_t **)(arg2 + 0xf8) = &LAB_00058ae0;
    *(uint8_t **)(arg2 + 0x100) = &LAB_00058b00;
    *(uint8_t **)(arg2 + 0x108) = &LAB_00058b1c;
    *(uint8_t **)(arg2 + 0x110) = &LAB_00058b34;
    *(uint8_t **)(arg2 + 0x118) = &LAB_00058b3c;
    *(sk_code_t *)(arg2 + 0x120) = sk_cap_op_aj;
    *(sk_code_t *)(arg2 + 0x128) = sk_cap_op_an;
    *(uint8_t **)(arg2 + 0x130) = &LAB_00058b70;
    *(sk_code_t *)(arg2 + 0x138) = sk_cap_op_ao;
    *(uint16_t *)(arg2 + 0x149) = 0x1701;
    *(uint32_t *)(arg2 + 0x14c) = 1;
    *(uint8_t **)(arg2 + 0x150) = &LAB_00058b8c;
    *(uint8_t **)(arg2 + 0x158) = &LAB_00058bac;
    *(sk_code_t *)(arg2 + 0x160) = sk_cap_op_ap;
    *(uint8_t **)(arg2 + 0x168) = &LAB_00058bcc;
    *(uint8_t **)(arg2 + 0x170) = &LAB_00058c14;
    *(uint8_t *)(arg2 + 0x140) = 1;
    *(uint32_t *)(arg2 + 0x144) = 5;
    *(uint8_t *)(arg2 + 0x148) = 0;
    *(uint8_t *)(arg2 + 0x178) = 0x1a;
    *(uint8_t **)(arg2 + 0x180) = &sk_global_019;
    *(uint8_t **)(arg2 + 0x188) = &sk_global_020;
    *(uint64_t *)(arg2 + 400) = 0x64d670;
    *(uint8_t **)(arg2 + 0x198) = &LAB_00058c54;
    *(uint8_t **)(arg2 + 0x1a0) = &LAB_00058c5c;
    *(uint8_t *)(arg2 + 0x1a8) = 1;
    *(uint64_t *)(arg2 + 0x1b0) = 1;
    *(uint32_t *)(arg2 + 0x1b8) = 1;
  }
  return arg1 == 0x500000001;
}




/* FUN_00058b44 @ 0x58b44   (est. sk_cap_op_aj)
 * Ghidra: void FUN_00058b44(undefined8 arg1,undefined8 arg2,undefined8 arg3,undefined8 arg4)
 * sk_cap_op_aj: cL4 sk cap op aj operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_cap_op_aj(uint64_t arg1,uint64_t arg2,uint64_t arg3,uint64_t arg4)
{
  uint64_t *t0;
  
  t0 = (uint64_t *)sk_tpidrro;
  *t0 = arg2;
  t0[1] = arg3;
  t0[2] = arg4;
  sk_svc(0);
  *t0 = arg2;
  return;
}




/* FUN_00058c68 @ 0x58c68   (est. sk_cap_op_ak)
 * Ghidra: void FUN_00058c68(long arg1)
 * sk_cap_op_ak: cL4 sk cap op ak operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_cap_op_ak(long arg1)
{
  uint64_t *t0;
  uint64_t t1;
  
  t0 = (uint64_t *)sk_tpidrro;
  t1 = *t0;
  do {
    sk_svc(0);
    *t0 = t1;
  } while (arg1 == 1);
  return;
}




/* FUN_00058c98 @ 0x58c98   (est. sk_cap_op_al)
 * Ghidra: void FUN_00058c98(long arg1)
 * sk_cap_op_al: cL4 sk cap op al operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_cap_op_al(long arg1)
{
  uint64_t *t0;
  uint64_t t1;
  
  t0 = (uint64_t *)sk_tpidrro;
  t1 = *t0;
  do {
    sk_svc(0);
    *t0 = t1;
  } while (arg1 == 1);
  return;
}




/* FUN_00058cc8 @ 0x58cc8   (est. sk_cap_op_am)
 * Ghidra: void FUN_00058cc8(long arg1)
 * sk_cap_op_am: cL4 sk cap op am operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_cap_op_am(long arg1)
{
  uint64_t *t0;
  uint64_t t1;
  
  t0 = (uint64_t *)sk_tpidrro;
  t1 = *t0;
  do {
    sk_svc(0);
    *t0 = t1;
  } while (arg1 == 1);
  return;
}




/* FUN_00058cf8 @ 0x58cf8   (est. sk_cap_op_an)
 * Ghidra: void FUN_00058cf8(long arg1)
 * sk_cap_op_an: cL4 sk cap op an operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_cap_op_an(long arg1)
{
  uint64_t *t0;
  uint64_t t1;
  
  t0 = (uint64_t *)sk_tpidrro;
  t1 = *t0;
  do {
    sk_svc(0);
    *t0 = t1;
  } while (arg1 == 1);
  return;
}




/* FUN_00058d28 @ 0x58d28   (est. sk_cap_op_ao)
 * Ghidra: void FUN_00058d28(long arg1)
 * sk_cap_op_ao: cL4 sk cap op ao operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_cap_op_ao(long arg1)
{
  uint64_t *t0;
  uint64_t t1;
  
  t0 = (uint64_t *)sk_tpidrro;
  t1 = *t0;
  do {
    sk_svc(0);
    *t0 = t1;
  } while (arg1 == 1);
  return;
}




/* FUN_00058d58 @ 0x58d58   (est. sk_cap_op_ap)
 * Ghidra: void FUN_00058d58(long arg1,undefined8 arg2)
 * sk_cap_op_ap: cL4 sk cap op ap operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_cap_op_ap(long arg1,uint64_t arg2)
{
  uint64_t *t0;
  
  t0 = (uint64_t *)sk_tpidrro;
  *t0 = arg2;
  do {
    sk_svc(0);
    *t0 = arg2;
  } while (arg1 == 1);
  return;
}




/* FUN_00058d8c @ 0x58d8c   (est. sk_cap_cmp6)
 * Ghidra: bool FUN_00058d8c(long arg1,long arg2)
 * sk_cap_cmp6: cL4 sk cap cmp6 operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

bool sk_cap_cmp6(long arg1,long arg2)
{
  if (arg1 == 0x600000001) {
    *(uint64_t *)(arg2 + 8) = 0x600000001;
    *(char **)(arg2 + 0x10) = sk_str_43;
    *(uint8_t *)(arg2 + 0x18) = 0;
    *(uint32_t *)(arg2 + 0x1c) = 0xffffffff;
    *(uint8_t *)(arg2 + 0x20) = 0;
    *(uint64_t *)(arg2 + 0x28) = 0;
    *(uint8_t *)(arg2 + 0x30) = 1;
    *(uint32_t *)(arg2 + 0x34) = 3;
    *(int *)(arg2 + 0x38) = (int)sk_global_005;
    *(uint8_t **)(arg2 + 0x40) = &LAB_00059110;
    *(uint8_t **)(arg2 + 0x48) = &LAB_00059128;
    *(uint8_t **)(arg2 + 0x50) = &LAB_00059140;
    *(sk_code_t *)(arg2 + 0x58) = sk_cap_op_ar;
    *(uint8_t **)(arg2 + 0x60) = &LAB_0005915c;
    *(sk_code_t *)(arg2 + 0x68) = sk_cap_op_as;
    *(uint8_t **)(arg2 + 0x70) = &LAB_00059174;
    *(uint8_t **)(arg2 + 0x78) = &LAB_000591ac;
    *(uint8_t **)(arg2 + 0x80) = &LAB_000591c4;
    *(uint8_t **)(arg2 + 0x88) = &LAB_000591dc;
    *(uint8_t **)(arg2 + 0x90) = &LAB_00059204;
    *(sk_code_t *)(arg2 + 0x98) = sk_cap_op_at;
    *(uint8_t *)(arg2 + 0xa0) = 1;
    *(uint32_t *)(arg2 + 0xa4) = 4;
    *(uint8_t **)(arg2 + 0xa8) = &LAB_00059228;
    *(uint8_t **)(arg2 + 0xb0) = &LAB_00059230;
    *(uint8_t **)(arg2 + 0xb8) = &LAB_00059238;
    *(uint8_t **)(arg2 + 0xc0) = &LAB_00059240;
    *(uint64_t *)(arg2 + 0xd0) = 0xc;
    *(uint8_t **)(arg2 + 0xd8) = &LAB_00059248;
    *(uint8_t **)(arg2 + 0xe0) = &LAB_00059250;
    *(uint8_t **)(arg2 + 0xe8) = &LAB_00059258;
    *(uint16_t *)(arg2 + 0xf0) = 0x1601;
    *(uint32_t *)(arg2 + 0xf4) = 3;
    *(uint8_t **)(arg2 + 0xf8) = &LAB_00059260;
    *(uint8_t **)(arg2 + 0x100) = &LAB_00059280;
    *(uint8_t **)(arg2 + 0x108) = &LAB_0005929c;
    *(uint8_t **)(arg2 + 0x110) = &LAB_000592b4;
    *(uint8_t **)(arg2 + 0x118) = &LAB_000592bc;
    *(sk_code_t *)(arg2 + 0x120) = sk_cap_op_aq;
    *(sk_code_t *)(arg2 + 0x128) = sk_cap_op_au;
    *(uint8_t **)(arg2 + 0x130) = &LAB_000592f0;
    *(sk_code_t *)(arg2 + 0x138) = sk_cap_op_av;
    *(uint16_t *)(arg2 + 0x149) = 0x1701;
    *(uint32_t *)(arg2 + 0x14c) = 1;
    *(uint8_t **)(arg2 + 0x150) = &LAB_0005930c;
    *(uint8_t **)(arg2 + 0x158) = &LAB_0005932c;
    *(sk_code_t *)(arg2 + 0x160) = sk_cap_op_aw;
    *(uint8_t **)(arg2 + 0x168) = &LAB_0005934c;
    *(uint8_t **)(arg2 + 0x170) = &LAB_00059394;
    *(uint8_t *)(arg2 + 0x140) = 1;
    *(uint32_t *)(arg2 + 0x144) = 5;
    *(uint8_t *)(arg2 + 0x148) = 0;
    *(uint8_t *)(arg2 + 0x178) = 0x1a;
    *(uint8_t **)(arg2 + 0x180) = &sk_global_021;
    *(uint8_t **)(arg2 + 0x188) = &sk_global_022;
    *(uint64_t *)(arg2 + 400) = 0x64d740;
    *(uint8_t **)(arg2 + 0x198) = &LAB_000593d4;
    *(uint8_t **)(arg2 + 0x1a0) = &LAB_000593dc;
    *(uint8_t *)(arg2 + 0x1a8) = 1;
    *(uint64_t *)(arg2 + 0x1b0) = 1;
    *(uint32_t *)(arg2 + 0x1b8) = 1;
  }
  return arg1 == 0x600000001;
}




/* FUN_000592c4 @ 0x592c4   (est. sk_cap_op_aq)
 * Ghidra: void FUN_000592c4(undefined8 arg1,undefined8 arg2,undefined8 arg3,undefined8 arg4)
 * sk_cap_op_aq: cL4 sk cap op aq operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_cap_op_aq(uint64_t arg1,uint64_t arg2,uint64_t arg3,uint64_t arg4)
{
  uint64_t *t0;
  
  t0 = (uint64_t *)sk_tpidrro;
  *t0 = arg2;
  t0[1] = arg3;
  t0[2] = arg4;
  sk_svc(0);
  *t0 = arg2;
  return;
}




/* FUN_000593e8 @ 0x593e8   (est. sk_cap_op_ar)
 * Ghidra: void FUN_000593e8(long arg1)
 * sk_cap_op_ar: cL4 sk cap op ar operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_cap_op_ar(long arg1)
{
  uint64_t *t0;
  uint64_t t1;
  
  t0 = (uint64_t *)sk_tpidrro;
  t1 = *t0;
  do {
    sk_svc(0);
    *t0 = t1;
  } while (arg1 == 1);
  return;
}




/* FUN_00059418 @ 0x59418   (est. sk_cap_op_as)
 * Ghidra: void FUN_00059418(long arg1)
 * sk_cap_op_as: cL4 sk cap op as operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_cap_op_as(long arg1)
{
  uint64_t *t0;
  uint64_t t1;
  
  t0 = (uint64_t *)sk_tpidrro;
  t1 = *t0;
  do {
    sk_svc(0);
    *t0 = t1;
  } while (arg1 == 1);
  return;
}




/* FUN_00059448 @ 0x59448   (est. sk_cap_op_at)
 * Ghidra: void FUN_00059448(long arg1)
 * sk_cap_op_at: cL4 sk cap op at operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_cap_op_at(long arg1)
{
  uint64_t *t0;
  uint64_t t1;
  
  t0 = (uint64_t *)sk_tpidrro;
  t1 = *t0;
  do {
    sk_svc(0);
    *t0 = t1;
  } while (arg1 == 1);
  return;
}




/* FUN_00059478 @ 0x59478   (est. sk_cap_op_au)
 * Ghidra: void FUN_00059478(long arg1)
 * sk_cap_op_au: cL4 sk cap op au operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_cap_op_au(long arg1)
{
  uint64_t *t0;
  uint64_t t1;
  
  t0 = (uint64_t *)sk_tpidrro;
  t1 = *t0;
  do {
    sk_svc(0);
    *t0 = t1;
  } while (arg1 == 1);
  return;
}




/* FUN_000594a8 @ 0x594a8   (est. sk_cap_op_av)
 * Ghidra: void FUN_000594a8(long arg1)
 * sk_cap_op_av: cL4 sk cap op av operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_cap_op_av(long arg1)
{
  uint64_t *t0;
  uint64_t t1;
  
  t0 = (uint64_t *)sk_tpidrro;
  t1 = *t0;
  do {
    sk_svc(0);
    *t0 = t1;
  } while (arg1 == 1);
  return;
}




/* FUN_000594d8 @ 0x594d8   (est. sk_cap_op_aw)
 * Ghidra: void FUN_000594d8(long arg1,undefined8 arg2)
 * sk_cap_op_aw: cL4 sk cap op aw operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_cap_op_aw(long arg1,uint64_t arg2)
{
  uint64_t *t0;
  
  t0 = (uint64_t *)sk_tpidrro;
  *t0 = arg2;
  do {
    sk_svc(0);
    *t0 = arg2;
  } while (arg1 == 1);
  return;
}




/* FUN_0005950c @ 0x5950c   (est. sk_cap_cmp7)
 * Ghidra: bool FUN_0005950c(long arg1,long arg2)
 * sk_cap_cmp7: cL4 sk cap cmp7 operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

bool sk_cap_cmp7(long arg1,long arg2)
{
  if (arg1 == 0x700000001) {
    *(uint64_t *)(arg2 + 8) = 0x700000001;
    *(char **)(arg2 + 0x10) = sk_str_43;
    *(uint8_t *)(arg2 + 0x18) = 0;
    *(uint32_t *)(arg2 + 0x1c) = 0xffffffff;
    *(uint8_t *)(arg2 + 0x20) = 0;
    *(uint64_t *)(arg2 + 0x28) = 0;
    *(uint8_t *)(arg2 + 0x30) = 1;
    *(uint32_t *)(arg2 + 0x34) = 3;
    *(int *)(arg2 + 0x38) = (int)sk_global_005;
    *(uint8_t **)(arg2 + 0x40) = &LAB_00059890;
    *(uint8_t **)(arg2 + 0x48) = &LAB_000598a8;
    *(uint8_t **)(arg2 + 0x50) = &LAB_000598c0;
    *(sk_code_t *)(arg2 + 0x58) = sk_cap_op_ay;
    *(uint8_t **)(arg2 + 0x60) = &LAB_000598dc;
    *(sk_code_t *)(arg2 + 0x68) = sk_cap_op_az;
    *(uint8_t **)(arg2 + 0x70) = &LAB_000598f4;
    *(uint8_t **)(arg2 + 0x78) = &LAB_0005992c;
    *(uint8_t **)(arg2 + 0x80) = &LAB_00059944;
    *(uint8_t **)(arg2 + 0x88) = &LAB_0005995c;
    *(uint8_t **)(arg2 + 0x90) = &LAB_00059984;
    *(sk_code_t *)(arg2 + 0x98) = sk_cap_op_ba;
    *(uint8_t *)(arg2 + 0xa0) = 1;
    *(uint32_t *)(arg2 + 0xa4) = 4;
    *(uint8_t **)(arg2 + 0xa8) = &LAB_000599a8;
    *(uint8_t **)(arg2 + 0xb0) = &LAB_000599b0;
    *(uint8_t **)(arg2 + 0xb8) = &LAB_000599b8;
    *(uint8_t **)(arg2 + 0xc0) = &LAB_000599c0;
    *(uint64_t *)(arg2 + 0xd0) = 0xc;
    *(uint8_t **)(arg2 + 0xd8) = &LAB_000599c8;
    *(uint8_t **)(arg2 + 0xe0) = &LAB_000599d0;
    *(uint8_t **)(arg2 + 0xe8) = &LAB_000599d8;
    *(uint16_t *)(arg2 + 0xf0) = 0x1601;
    *(uint32_t *)(arg2 + 0xf4) = 3;
    *(uint8_t **)(arg2 + 0xf8) = &LAB_000599e0;
    *(uint8_t **)(arg2 + 0x100) = &LAB_00059a00;
    *(uint8_t **)(arg2 + 0x108) = &LAB_00059a1c;
    *(uint8_t **)(arg2 + 0x110) = &LAB_00059a34;
    *(uint8_t **)(arg2 + 0x118) = &LAB_00059a3c;
    *(sk_code_t *)(arg2 + 0x120) = sk_cap_op_ax;
    *(sk_code_t *)(arg2 + 0x128) = sk_cap_op_bb;
    *(uint8_t **)(arg2 + 0x130) = &LAB_00059a70;
    *(sk_code_t *)(arg2 + 0x138) = sk_cap_op_bc;
    *(uint16_t *)(arg2 + 0x149) = 0x1701;
    *(uint32_t *)(arg2 + 0x14c) = 1;
    *(uint8_t **)(arg2 + 0x150) = &LAB_00059a8c;
    *(uint8_t **)(arg2 + 0x158) = &LAB_00059aac;
    *(sk_code_t *)(arg2 + 0x160) = sk_cap_op_bd;
    *(uint8_t **)(arg2 + 0x168) = &LAB_00059acc;
    *(uint8_t **)(arg2 + 0x170) = &LAB_00059b14;
    *(uint8_t *)(arg2 + 0x140) = 1;
    *(uint32_t *)(arg2 + 0x144) = 5;
    *(uint8_t *)(arg2 + 0x148) = 0;
    *(uint8_t *)(arg2 + 0x178) = 0x1a;
    *(uint8_t **)(arg2 + 0x180) = &sk_global_023;
    *(uint8_t **)(arg2 + 0x188) = &sk_global_024;
    *(uint64_t *)(arg2 + 400) = 0x64d810;
    *(uint8_t **)(arg2 + 0x198) = &LAB_00059b54;
    *(uint8_t **)(arg2 + 0x1a0) = &LAB_00059b5c;
    *(uint8_t *)(arg2 + 0x1a8) = 1;
    *(uint64_t *)(arg2 + 0x1b0) = 1;
    *(uint32_t *)(arg2 + 0x1b8) = 1;
  }
  return arg1 == 0x700000001;
}




/* FUN_00059a44 @ 0x59a44   (est. sk_cap_op_ax)
 * Ghidra: void FUN_00059a44(undefined8 arg1,undefined8 arg2,undefined8 arg3,undefined8 arg4)
 * sk_cap_op_ax: cL4 sk cap op ax operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_cap_op_ax(uint64_t arg1,uint64_t arg2,uint64_t arg3,uint64_t arg4)
{
  uint64_t *t0;
  
  t0 = (uint64_t *)sk_tpidrro;
  *t0 = arg2;
  t0[1] = arg3;
  t0[2] = arg4;
  sk_svc(0);
  *t0 = arg2;
  return;
}




/* FUN_00059b68 @ 0x59b68   (est. sk_cap_op_ay)
 * Ghidra: void FUN_00059b68(long arg1)
 * sk_cap_op_ay: cL4 sk cap op ay operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_cap_op_ay(long arg1)
{
  uint64_t *t0;
  uint64_t t1;
  
  t0 = (uint64_t *)sk_tpidrro;
  t1 = *t0;
  do {
    sk_svc(0);
    *t0 = t1;
  } while (arg1 == 1);
  return;
}




/* FUN_00059b98 @ 0x59b98   (est. sk_cap_op_az)
 * Ghidra: void FUN_00059b98(long arg1)
 * sk_cap_op_az: cL4 sk cap op az operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_cap_op_az(long arg1)
{
  uint64_t *t0;
  uint64_t t1;
  
  t0 = (uint64_t *)sk_tpidrro;
  t1 = *t0;
  do {
    sk_svc(0);
    *t0 = t1;
  } while (arg1 == 1);
  return;
}




/* FUN_00059bc8 @ 0x59bc8   (est. sk_cap_op_ba)
 * Ghidra: void FUN_00059bc8(long arg1)
 * sk_cap_op_ba: cL4 sk cap op ba operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_cap_op_ba(long arg1)
{
  uint64_t *t0;
  uint64_t t1;
  
  t0 = (uint64_t *)sk_tpidrro;
  t1 = *t0;
  do {
    sk_svc(0);
    *t0 = t1;
  } while (arg1 == 1);
  return;
}




/* FUN_00059bf8 @ 0x59bf8   (est. sk_cap_op_bb)
 * Ghidra: void FUN_00059bf8(long arg1)
 * sk_cap_op_bb: cL4 sk cap op bb operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_cap_op_bb(long arg1)
{
  uint64_t *t0;
  uint64_t t1;
  
  t0 = (uint64_t *)sk_tpidrro;
  t1 = *t0;
  do {
    sk_svc(0);
    *t0 = t1;
  } while (arg1 == 1);
  return;
}




/* FUN_00059c28 @ 0x59c28   (est. sk_cap_op_bc)
 * Ghidra: void FUN_00059c28(long arg1)
 * sk_cap_op_bc: cL4 sk cap op bc operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_cap_op_bc(long arg1)
{
  uint64_t *t0;
  uint64_t t1;
  
  t0 = (uint64_t *)sk_tpidrro;
  t1 = *t0;
  do {
    sk_svc(0);
    *t0 = t1;
  } while (arg1 == 1);
  return;
}




/* FUN_00059c58 @ 0x59c58   (est. sk_cap_op_bd)
 * Ghidra: void FUN_00059c58(long arg1,undefined8 arg2)
 * sk_cap_op_bd: cL4 sk cap op bd operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_cap_op_bd(long arg1,uint64_t arg2)
{
  uint64_t *t0;
  
  t0 = (uint64_t *)sk_tpidrro;
  *t0 = arg2;
  do {
    sk_svc(0);
    *t0 = arg2;
  } while (arg1 == 1);
  return;
}




/* FUN_00059c8c @ 0x59c8c   (est. sk_cap_cmp8)
 * Ghidra: bool FUN_00059c8c(long arg1,long arg2)
 * sk_cap_cmp8: cL4 sk cap cmp8 operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

bool sk_cap_cmp8(long arg1,long arg2)
{
  if (arg1 == 0x800000001) {
    *(uint64_t *)(arg2 + 8) = 0x800000001;
    *(char **)(arg2 + 0x10) = sk_str_43;
    *(uint8_t *)(arg2 + 0x18) = 0;
    *(uint32_t *)(arg2 + 0x1c) = 0xffffffff;
    *(uint8_t *)(arg2 + 0x20) = 0;
    *(uint64_t *)(arg2 + 0x28) = 0;
    *(uint8_t *)(arg2 + 0x30) = 1;
    *(uint32_t *)(arg2 + 0x34) = 3;
    *(int *)(arg2 + 0x38) = (int)sk_global_005;
    *(uint8_t **)(arg2 + 0x40) = &LAB_0005a010;
    *(uint8_t **)(arg2 + 0x48) = &LAB_0005a028;
    *(uint8_t **)(arg2 + 0x50) = &LAB_0005a040;
    *(sk_code_t *)(arg2 + 0x58) = svc_repeat_on_suspend_1;
    *(uint8_t **)(arg2 + 0x60) = &LAB_0005a05c;
    *(sk_code_t *)(arg2 + 0x68) = svc_repeat_on_suspend_2;
    *(uint8_t **)(arg2 + 0x70) = &LAB_0005a074;
    *(uint8_t **)(arg2 + 0x78) = &LAB_0005a0ac;
    *(uint8_t **)(arg2 + 0x80) = &LAB_0005a0c4;
    *(uint8_t **)(arg2 + 0x88) = &LAB_0005a0dc;
    *(uint8_t **)(arg2 + 0x90) = &LAB_0005a104;
    *(sk_code_t *)(arg2 + 0x98) = svc_repeat_on_suspend_3;
    *(uint8_t *)(arg2 + 0xa0) = 1;
    *(uint32_t *)(arg2 + 0xa4) = 4;
    *(uint8_t **)(arg2 + 0xa8) = &LAB_0005a128;
    *(uint8_t **)(arg2 + 0xb0) = &LAB_0005a130;
    *(uint8_t **)(arg2 + 0xb8) = &LAB_0005a138;
    *(uint8_t **)(arg2 + 0xc0) = &LAB_0005a140;
    *(uint64_t *)(arg2 + 0xd0) = 0xc;
    *(uint8_t **)(arg2 + 0xd8) = &LAB_0005a148;
    *(uint8_t **)(arg2 + 0xe0) = &LAB_0005a150;
    *(uint8_t **)(arg2 + 0xe8) = &LAB_0005a158;
    *(uint16_t *)(arg2 + 0xf0) = 0x1601;
    *(uint32_t *)(arg2 + 0xf4) = 3;
    *(uint8_t **)(arg2 + 0xf8) = &LAB_0005a160;
    *(uint8_t **)(arg2 + 0x100) = &LAB_0005a180;
    *(uint8_t **)(arg2 + 0x108) = &LAB_0005a19c;
    *(uint8_t **)(arg2 + 0x110) = &LAB_0005a1b4;
    *(uint8_t **)(arg2 + 0x118) = &LAB_0005a1bc;
    *(sk_code_t *)(arg2 + 0x120) = svc_dispatch_3arg;
    *(sk_code_t *)(arg2 + 0x128) = svc_repeat_on_suspend_4;
    *(uint8_t **)(arg2 + 0x130) = &LAB_0005a1f0;
    *(sk_code_t *)(arg2 + 0x138) = svc_repeat_on_suspend_5;
    *(uint16_t *)(arg2 + 0x149) = 0x1701;
    *(uint32_t *)(arg2 + 0x14c) = 1;
    *(uint8_t **)(arg2 + 0x150) = &LAB_0005a20c;
    *(uint8_t **)(arg2 + 0x158) = &LAB_0005a22c;
    *(sk_code_t *)(arg2 + 0x160) = svc_set_arg_repeat_on_suspend;
    *(uint8_t **)(arg2 + 0x168) = &LAB_0005a24c;
    *(uint8_t **)(arg2 + 0x170) = &LAB_0005a294;
    *(uint8_t *)(arg2 + 0x140) = 1;
    *(uint32_t *)(arg2 + 0x144) = 5;
    *(uint8_t *)(arg2 + 0x148) = 0;
    *(uint8_t *)(arg2 + 0x178) = 0x1a;
    *(uint8_t **)(arg2 + 0x180) = &sk_global_025;
    *(uint8_t **)(arg2 + 0x188) = &sk_global_026;
    *(uint64_t *)(arg2 + 400) = 0x64d8e0;
    *(uint8_t **)(arg2 + 0x198) = &LAB_0005a2d4;
    *(uint8_t **)(arg2 + 0x1a0) = &LAB_0005a2dc;
    *(uint8_t *)(arg2 + 0x1a8) = 1;
    *(uint64_t *)(arg2 + 0x1b0) = 1;
    *(uint32_t *)(arg2 + 0x1b8) = 1;
  }
  return arg1 == 0x800000001;
}




/* FUN_0005a1c4 @ 0x5a1c4   (est. svc_dispatch_3arg)
 * Ghidra: void FUN_0005a1c4(undefined8 arg1,undefined8 arg2,undefined8 arg3,undefined8 arg4)
 * svc_dispatch_3arg: cL4 svc dispatch 3arg operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void svc_dispatch_3arg(uint64_t arg1,uint64_t arg2,uint64_t arg3,uint64_t arg4)
{
  uint64_t *t0;
  
  t0 = (uint64_t *)sk_tpidrro;
  *t0 = arg2;
  t0[1] = arg3;
  t0[2] = arg4;
  sk_svc(0);
  *t0 = arg2;
  return;
}




/* FUN_0005a2e8 @ 0x5a2e8   (est. svc_repeat_on_suspend_1)
 * Ghidra: void FUN_0005a2e8(long arg1)
 * svc_repeat_on_suspend_1: cL4 svc repeat on suspend 1 operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void svc_repeat_on_suspend_1(long arg1)
{
  uint64_t *t0;
  uint64_t t1;
  
  t0 = (uint64_t *)sk_tpidrro;
  t1 = *t0;
  do {
    sk_svc(0);
    *t0 = t1;
  } while (arg1 == 1);
  return;
}




/* FUN_0005a318 @ 0x5a318   (est. svc_repeat_on_suspend_2)
 * Ghidra: void FUN_0005a318(long arg1)
 * svc_repeat_on_suspend_2: cL4 svc repeat on suspend 2 operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void svc_repeat_on_suspend_2(long arg1)
{
  uint64_t *t0;
  uint64_t t1;
  
  t0 = (uint64_t *)sk_tpidrro;
  t1 = *t0;
  do {
    sk_svc(0);
    *t0 = t1;
  } while (arg1 == 1);
  return;
}




/* FUN_0005a348 @ 0x5a348   (est. svc_repeat_on_suspend_3)
 * Ghidra: void FUN_0005a348(long arg1)
 * svc_repeat_on_suspend_3: cL4 svc repeat on suspend 3 operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void svc_repeat_on_suspend_3(long arg1)
{
  uint64_t *t0;
  uint64_t t1;
  
  t0 = (uint64_t *)sk_tpidrro;
  t1 = *t0;
  do {
    sk_svc(0);
    *t0 = t1;
  } while (arg1 == 1);
  return;
}




/* FUN_0005a378 @ 0x5a378   (est. svc_repeat_on_suspend_4)
 * Ghidra: void FUN_0005a378(long arg1)
 * svc_repeat_on_suspend_4: cL4 svc repeat on suspend 4 operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void svc_repeat_on_suspend_4(long arg1)
{
  uint64_t *t0;
  uint64_t t1;
  
  t0 = (uint64_t *)sk_tpidrro;
  t1 = *t0;
  do {
    sk_svc(0);
    *t0 = t1;
  } while (arg1 == 1);
  return;
}




/* FUN_0005a3a8 @ 0x5a3a8   (est. svc_repeat_on_suspend_5)
 * Ghidra: void FUN_0005a3a8(long arg1)
 * svc_repeat_on_suspend_5: cL4 svc repeat on suspend 5 operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void svc_repeat_on_suspend_5(long arg1)
{
  uint64_t *t0;
  uint64_t t1;
  
  t0 = (uint64_t *)sk_tpidrro;
  t1 = *t0;
  do {
    sk_svc(0);
    *t0 = t1;
  } while (arg1 == 1);
  return;
}




/* FUN_0005a3d8 @ 0x5a3d8   (est. svc_set_arg_repeat_on_suspend)
 * Ghidra: void FUN_0005a3d8(long arg1,undefined8 arg2)
 * svc_set_arg_repeat_on_suspend: cL4 svc set arg repeat on suspend operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void svc_set_arg_repeat_on_suspend(long arg1,uint64_t arg2)
{
  uint64_t *t0;
  
  t0 = (uint64_t *)sk_tpidrro;
  *t0 = arg2;
  do {
    sk_svc(0);
    *t0 = arg2;
  } while (arg1 == 1);
  return;
}




/* FUN_0005a40c @ 0x5a40c   (est. fill_cap_dispatch_table)
 * Ghidra: bool FUN_0005a40c(long arg1,long arg2)
 * fill_cap_dispatch_table: cL4 fill cap dispatch table operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

bool fill_cap_dispatch_table(long arg1,long arg2)
{
  if (arg1 == 0x900000001) {
    *(uint64_t *)(arg2 + 8) = 0x900000001;
    *(char **)(arg2 + 0x10) = sk_str_43;
    *(uint8_t *)(arg2 + 0x18) = 0;
    *(uint32_t *)(arg2 + 0x1c) = 0xffffffff;
    *(uint8_t *)(arg2 + 0x20) = 0;
    *(uint64_t *)(arg2 + 0x28) = 0;
    *(uint8_t *)(arg2 + 0x30) = 1;
    *(uint32_t *)(arg2 + 0x34) = 3;
    *(int *)(arg2 + 0x38) = (int)sk_global_005;
    *(uint8_t **)(arg2 + 0x40) = &LAB_0005a78c;
    *(uint8_t **)(arg2 + 0x48) = &LAB_0005a7a4;
    *(uint8_t **)(arg2 + 0x50) = &LAB_0005a7bc;
    *(sk_code_t *)(arg2 + 0x58) = svc_repeat_on_suspend_6;
    *(uint8_t **)(arg2 + 0x60) = &LAB_0005a7d8;
    *(sk_code_t *)(arg2 + 0x68) = svc_repeat_on_suspend_7;
    *(uint8_t **)(arg2 + 0x70) = &LAB_0005a7f0;
    *(uint8_t **)(arg2 + 0x78) = &LAB_0005a828;
    *(uint8_t **)(arg2 + 0x80) = &LAB_0005a840;
    *(uint8_t **)(arg2 + 0x88) = &LAB_0005a858;
    *(uint8_t **)(arg2 + 0x90) = &LAB_0005a880;
    *(sk_code_t *)(arg2 + 0x98) = svc_repeat_on_suspend_8;
    *(uint8_t *)(arg2 + 0xa0) = 1;
    *(uint32_t *)(arg2 + 0xa4) = 4;
    *(uint8_t **)(arg2 + 0xa8) = &LAB_0005a8a4;
    *(uint8_t **)(arg2 + 0xb0) = &LAB_0005a8ac;
    *(uint8_t **)(arg2 + 0xb8) = &LAB_0005a8b4;
    *(uint8_t **)(arg2 + 0xc0) = &LAB_0005a8bc;
    *(uint64_t *)(arg2 + 0xd0) = 0xc;
    *(uint8_t **)(arg2 + 0xd8) = &LAB_0005a8c4;
    *(uint8_t **)(arg2 + 0xe0) = &LAB_0005a8cc;
    *(uint8_t **)(arg2 + 0xe8) = &LAB_0005a8d4;
    *(uint16_t *)(arg2 + 0xf0) = 0x1601;
    *(uint32_t *)(arg2 + 0xf4) = 3;
    *(uint8_t **)(arg2 + 0xf8) = &LAB_0005a8dc;
    *(uint8_t **)(arg2 + 0x100) = &LAB_0005a8fc;
    *(uint8_t **)(arg2 + 0x108) = &LAB_0005a918;
    *(uint8_t **)(arg2 + 0x110) = &LAB_0005a930;
    *(uint8_t **)(arg2 + 0x118) = &LAB_0005a938;
    *(sk_code_t *)(arg2 + 0x120) = svc_dispatch_3arg_b;
    *(sk_code_t *)(arg2 + 0x128) = svc_repeat_on_suspend_9;
    *(uint8_t **)(arg2 + 0x130) = &LAB_0005a96c;
    *(sk_code_t *)(arg2 + 0x138) = svc_repeat_on_suspend_10;
    *(uint16_t *)(arg2 + 0x149) = 0x1701;
    *(uint32_t *)(arg2 + 0x14c) = 1;
    *(uint8_t **)(arg2 + 0x150) = &LAB_0005a988;
    *(uint8_t **)(arg2 + 0x158) = &LAB_0005a9a8;
    *(sk_code_t *)(arg2 + 0x160) = svc_set_arg_repeat_on_suspend_b;
    *(uint8_t **)(arg2 + 0x168) = &LAB_0005a9c8;
    *(uint8_t **)(arg2 + 0x170) = &LAB_0005aa10;
    *(uint8_t *)(arg2 + 0x140) = 1;
    *(uint32_t *)(arg2 + 0x144) = 5;
    *(uint8_t *)(arg2 + 0x148) = 0;
    *(uint8_t *)(arg2 + 0x178) = 0x1a;
    *(uint8_t **)(arg2 + 0x180) = &sk_global_027;
    *(uint8_t **)(arg2 + 0x188) = &sk_global_028;
    *(uint64_t *)(arg2 + 400) = 0x64d9b0;
    *(uint8_t **)(arg2 + 0x198) = &LAB_0005aa50;
    *(uint8_t **)(arg2 + 0x1a0) = &LAB_0005aa58;
    *(uint8_t *)(arg2 + 0x1a8) = 1;
    *(uint64_t *)(arg2 + 0x1b0) = 1;
    *(uint32_t *)(arg2 + 0x1b8) = 0;
  }
  return arg1 == 0x900000001;
}




/* FUN_0005a940 @ 0x5a940   (est. svc_dispatch_3arg_b)
 * Ghidra: void FUN_0005a940(undefined8 arg1,undefined8 arg2,undefined8 arg3,undefined8 arg4)
 * svc_dispatch_3arg_b: cL4 svc dispatch 3arg b operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void svc_dispatch_3arg_b(uint64_t arg1,uint64_t arg2,uint64_t arg3,uint64_t arg4)
{
  uint64_t *t0;
  
  t0 = (uint64_t *)sk_tpidrro;
  *t0 = arg2;
  t0[1] = arg3;
  t0[2] = arg4;
  sk_svc(0);
  *t0 = arg2;
  return;
}




/* FUN_0005aa64 @ 0x5aa64   (est. svc_repeat_on_suspend_6)
 * Ghidra: void FUN_0005aa64(long arg1)
 * svc_repeat_on_suspend_6: cL4 svc repeat on suspend 6 operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void svc_repeat_on_suspend_6(long arg1)
{
  uint64_t *t0;
  uint64_t t1;
  
  t0 = (uint64_t *)sk_tpidrro;
  t1 = *t0;
  do {
    sk_svc(0);
    *t0 = t1;
  } while (arg1 == 1);
  return;
}




/* FUN_0005aa94 @ 0x5aa94   (est. svc_repeat_on_suspend_7)
 * Ghidra: void FUN_0005aa94(long arg1)
 * svc_repeat_on_suspend_7: cL4 svc repeat on suspend 7 operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void svc_repeat_on_suspend_7(long arg1)
{
  uint64_t *t0;
  uint64_t t1;
  
  t0 = (uint64_t *)sk_tpidrro;
  t1 = *t0;
  do {
    sk_svc(0);
    *t0 = t1;
  } while (arg1 == 1);
  return;
}




/* FUN_0005aac4 @ 0x5aac4   (est. svc_repeat_on_suspend_8)
 * Ghidra: void FUN_0005aac4(long arg1)
 * svc_repeat_on_suspend_8: cL4 svc repeat on suspend 8 operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void svc_repeat_on_suspend_8(long arg1)
{
  uint64_t *t0;
  uint64_t t1;
  
  t0 = (uint64_t *)sk_tpidrro;
  t1 = *t0;
  do {
    sk_svc(0);
    *t0 = t1;
  } while (arg1 == 1);
  return;
}




/* FUN_0005aaf4 @ 0x5aaf4   (est. svc_repeat_on_suspend_9)
 * Ghidra: void FUN_0005aaf4(long arg1)
 * svc_repeat_on_suspend_9: cL4 svc repeat on suspend 9 operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void svc_repeat_on_suspend_9(long arg1)
{
  uint64_t *t0;
  uint64_t t1;
  
  t0 = (uint64_t *)sk_tpidrro;
  t1 = *t0;
  do {
    sk_svc(0);
    *t0 = t1;
  } while (arg1 == 1);
  return;
}




/* FUN_0005ab24 @ 0x5ab24   (est. svc_repeat_on_suspend_10)
 * Ghidra: void FUN_0005ab24(long arg1)
 * svc_repeat_on_suspend_10: cL4 svc repeat on suspend 10 operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void svc_repeat_on_suspend_10(long arg1)
{
  uint64_t *t0;
  uint64_t t1;
  
  t0 = (uint64_t *)sk_tpidrro;
  t1 = *t0;
  do {
    sk_svc(0);
    *t0 = t1;
  } while (arg1 == 1);
  return;
}




/* FUN_0005ab54 @ 0x5ab54   (est. svc_set_arg_repeat_on_suspend_b)
 * Ghidra: void FUN_0005ab54(long arg1,undefined8 arg2)
 * svc_set_arg_repeat_on_suspend_b: cL4 svc set arg repeat on suspend b operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void svc_set_arg_repeat_on_suspend_b(long arg1,uint64_t arg2)
{
  uint64_t *t0;
  
  t0 = (uint64_t *)sk_tpidrro;
  *t0 = arg2;
  do {
    sk_svc(0);
    *t0 = arg2;
  } while (arg1 == 1);
  return;
}




/* FUN_0005ab88 @ 0x5ab88   (est. sk_syscall_boot)
 * Ghidra: void FUN_0005ab88(void)
 * sk_syscall_boot: cL4 sk syscall boot operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_syscall_boot(void)
{
  sk_boot_done(1);
  return;
}




/* FUN_0005ab90 @ 0x5ab90   (est. thunk_cap_dispatch)
 * Ghidra: void thunk_FUN_000558c0(undefined8 arg1,undefined8 arg2,undefined8 arg3)
 * thunk_cap_dispatch: cL4 thunk cap dispatch operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void thunk_FUN_000558c0(uint64_t arg1,uint64_t arg2,uint64_t arg3)
{
  long t0;
  
  t0 = sk_global_ensure();
                    
                    
  (**(sk_code_t *)(t0 + 0x158))(arg1,arg2,arg3);
  return;
}




/* FUN_0005ab94 @ 0x5ab94   (est. sk_error_register)
 * Ghidra: uint32_t FUN_0005ab94(ulong arg1,unsigned int arg2)
 * sk_error_register: cL4 sk error register operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

uint32_t sk_error_register(unsigned long arg1,unsigned int arg2)
{
  char *t1;
  sk_code_t t2;
  long t0;
  uint64_t t3;
  uint32_t t4;
  unsigned long stk0;
  
  stk0 = 0;
  t0 = sk_ctx_irq(sk_str_112,&stk0);
  if (t0 == 0) {
    t4 = 0;
  }
  else {
    if (stk0 < (arg1 & 0xffffffff)) {
      t3 = sk_current_thread();
                    
      sk_panic_msg(t3,sk_str_115);
    }
    t1 = (char *)(t0 + (arg1 & 0xffffffff));
    if ((char *)(t0 + stk0) <= t1) {
                    
      t2 = (sk_code_t )sk_break(0x5519,0x5ac1c);
      (*t2)();
    }
    t4 = 1;
    if (((unsigned int)(int)*t1 >> (unsigned long)(arg2 & 0x1f) & 1) == 0) {
      t4 = 2;
    }
  }
  return t4;
}




/* FUN_0005ac2c @ 0x5ac2c   (est. sk_error_get)
 * Ghidra: ulong FUN_0005ac2c(void)
 * sk_error_get: cL4 sk error get operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

unsigned long sk_error_get(void)
{
  int t0;
  unsigned long t3;
  uint8_t *t2;
  long t1;
  uint64_t stk0;
  
  t3 = sk_tcb_aq();
  if ((int)t3 != 0) {
    t2 = (uint8_t *)sk_tcb_cur();
    if ((*t2 & 1) == 0) {
      stk0 = 0;
      t1 = sk_ctx_irq(sk_str_102,&stk0);
      if ((t1 == 0) || (t0 = sk_strcmp(t1,&sk_global_033,stk0), t0 == 0)) {
        t0 = sk_error_register(2,1);
        t3 = (unsigned long)(t0 == 1);
      }
      else {
        t3 = 1;
      }
    }
    else {
      t3 = 0;
    }
  }
  return t3;
}




/* FUN_0005acac @ 0x5acac   (est. sk_global_get)
 * Ghidra: void FUN_0005acac(long *arg1,undefined8 arg2,undefined8 arg3)
 * sk_global_get: cL4 sk global get operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_global_get(long *arg1,uint64_t arg2,uint64_t arg3)
{
  long t0;
  
  if (*arg1 == 0) {
    t0 = sk_lookup_thread_obj(arg2,arg3);
    *arg1 = t0;
  }
  return;
}




/* FUN_0005ace4 @ 0x5ace4   (est. sk_error_clear)
 * Ghidra: void FUN_0005ace4(void)
 * sk_error_clear: cL4 sk error clear operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_error_clear(void)
{
  sk_code_t t1;
  long t0;
  unsigned long t2;
  uint64_t t3;
  
  t0 = sk_tcb_cur();
  t2 = *(unsigned long *)(t0 + 0x108);
  if (t2 == 0) {
    t3 = sk_current_thread();
                    
    sk_panic_msg(t3,sk_str_40);
  }
  if (t2 <= t2 + 0x30) {
    return;
  }
                    
  t1 = (sk_code_t )sk_break(0x5519,0x5ad14);
  (*t1)();
}




/* FUN_0005ad24 @ 0x5ad24   (est. sk_error_status)
 * Ghidra: undefined8 FUN_0005ad24(void)
 * sk_error_status: cL4 sk error status operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

uint64_t sk_error_status(void)
{
  long t0;
  
  t0 = sk_tcb_cur();
  return *(uint64_t *)(t0 + 0x108);
}




/* FUN_0005ad40 @ 0x5ad40   (est. sk_error_reset)
 * Ghidra: void FUN_0005ad40(void)
 * sk_error_reset: cL4 sk error reset operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_error_reset(void)
{
                    
  uRam000000000064db08 = 0x64da80;
  sk_register_global();
  return;
}




/* FUN_0005ad58 @ 0x5ad58   (est. sk_error_set)
 * Ghidra: void FUN_0005ad58(long arg1)
 * sk_error_set: cL4 sk error set operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_error_set(long arg1)
{
  sk_code_t t0;
  uint64_t t1;
  unsigned long t2;
  unsigned long t3;
  long in_xzr;
  unsigned long stk0;
  
  if (*(unsigned long *)(arg1 + 0x48) < *(unsigned long *)(arg1 + 0x28)) {
    t2 = *(unsigned long *)(arg1 + 0x50);
    t3 = *(unsigned long *)(arg1 + 0x48);
    if ((t3 < t2 || t3 - t2 == 0) || ((t3 - t2) + *(long *)(arg1 + 0x60) < 5))
    {
      if (t3 <= t2) {
        t3 = t2;
      }
      stk0 = t3 + 5;
      if (*(unsigned long *)(arg1 + 0x28) <= t3 + 5) {
        stk0 = *(unsigned long *)(arg1 + 0x28);
      }
      stk0 = stk0 << 6;
      t3 = (**(sk_code_t *)(*(long *)(arg1 + 0x38) + 0x18))
                        (*(uint64_t *)(arg1 + 0x30),&stk0);
      t3 = t3 & 0xff;
      if (t3 != 0) {
        t1 = sk_current_thread();
        if ((&sk_global_034 <= &sk_global_034 + t3 && &sk_global_035 + t3 <= &sk_global_036) &&
            &sk_global_034 + t3 <= &sk_global_035 + t3) {
                    
          sk_panic_msg(t1,sk_str_04);
        }
                    
        t0 = (sk_code_t )sk_break(0x5519,0x5ae4c);
        (*t0)();
      }
      *(unsigned long *)(arg1 + 0x48) = stk0 >> 6;
      *(long *)(arg1 + 0x50) = *(long *)(arg1 + 0x50) + in_xzr;
      sk_lo_release();
    }
  }
  return;
}




/* FUN_0005ae4c @ 0x5ae4c   (est. sk_error_emit)
 * Ghidra: void FUN_0005ae4c(undefined8 arg1,long arg2,undefined8 arg3,int arg4)
 * sk_error_emit: cL4 sk error emit operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_error_emit(uint64_t arg1,long arg2,uint64_t arg3,int arg4)
{
  sk_code_t t1;
  long t0;
  unsigned long t3;
  long *t2;
  uint64_t stk3;
  long stk2;
  uint8_t stk0 [20];
  long stk1;
  
  stk1 = -0x2c8502b44bfffed6;
  sk_ctx_alloc(arg1,stk0);
  sk_log_str(sk_str_76);
  if ((arg4 != 0) && (*(long *)(arg2 + 0x38) != 0)) {
    t3 = 0;
    t2 = (long *)(arg2 + 0x10);
    do {
      if (((t2 < (long *)(arg2 + 0x10)) || ((long *)(arg2 + 0x38) < t2 + 1)) ||
         (t2 + 1 < t2)) {
                    
        t1 = (sk_code_t )sk_break(0x5519,0x5afe4);
        (*t1)();
      }
      stk2 = *t2;
      t0 = sk_range_lookup(&stk2,1);
      if (t0 == 0) break;
      stk3 = 0;
      sk_cnode_revoke(*t2,&stk3);
      sk_log_str(sk_str_78);
      t3 = t3 + 1;
      t2 = t2 + 1;
    } while (t3 < *(unsigned long *)(arg2 + 0x38));
  }
  if (stk1 == -0x2c8502b44bfffed6) {
    return;
  }
                    
  sk_noreturn_error();
}




/* FUN_0005afe8 @ 0x5afe8   (est. sk_error_fmt)
 * Ghidra: void FUN_0005afe8(long arg1,undefined8 arg2,undefined8 arg3)
 * sk_error_fmt: cL4 sk error fmt operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_error_fmt(long arg1,uint64_t arg2,uint64_t arg3)
{
  char *t0;
  unsigned long t1;
  
  t0 = (char *)sk_global_get(0x6b04b8,1,3);
  if ((*t0 != '\x02') || (t1 = sk_rt_unpark(arg1,arg3,arg2), (t1 & 1) != 0)) {
    *(long *)(arg1 + 0x58) = *(long *)(arg1 + 0x58) + 1;
  }
  return;
}




/* FUN_0005b05c @ 0x5b05c   (est. sk_error_release)
 * Ghidra: void FUN_0005b05c(long arg1,undefined8 arg2)
 * sk_error_release: cL4 sk error release operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_error_release(long arg1,uint64_t arg2)
{
  char *t0;
  
  t0 = (char *)sk_global_get(0x6b04b8,1,3);
  if (*t0 == '\x02') {
    sk_rt_log(arg1,arg2);
  }
  *(long *)(arg1 + 0x58) = *(long *)(arg1 + 0x58) + -1;
  return;
}




/* FUN_0005b0bc @ 0x5b0bc   (est. sk_error_broadcast)
 * Ghidra: void FUN_0005b0bc(long arg1)
 * sk_error_broadcast: cL4 sk error broadcast operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_error_broadcast(long arg1)
{
  char *t0;
  
  t0 = (char *)sk_global_get(0x6b04b8,1,3);
  if (*t0 == '\x02') {
    sk_rt_run(arg1);
  }
  if (*(long *)(arg1 + 0x58) == 0) {
    return;
  }
                    
  sk_panic_msg(0,sk_str_109);
}




/* FUN_0005b120 @ 0x5b120   (est. sk_error_cpu)
 * Ghidra: void FUN_0005b120(undefined8 arg1)
 * sk_error_cpu: cL4 sk error cpu operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_error_cpu(uint64_t arg1)
{
  sk_global_get(arg1,1,3);
  return;
}




/* FUN_0005b12c @ 0x5b12c   (est. sk_error_cpu2)
 * Ghidra: void FUN_0005b12c(undefined8 arg1)
 * sk_error_cpu2: cL4 sk error cpu2 operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_error_cpu2(uint64_t arg1)
{
  uint64_t uStack0000000000000010;
  
  uStack0000000000000010 = arg1;
                    
  sk_abort_msg(sk_str_44);
}




/* FUN_0005b140 @ 0x5b140   (est. sk_error_sync)
 * Ghidra: void FUN_0005b140(void)
 * sk_error_sync: cL4 sk error sync operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_error_sync(void)
{
  if (sk_global_105 != 0) {
    return;
  }
  sk_global_105 = 0x65c4d8;
  return;
}




/* FUN_0005b160 @ 0x5b160   (est. sk_error_flag)
 * Ghidra: undefined8 FUN_0005b160(void)
 * sk_error_flag: cL4 sk error flag operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

uint64_t sk_error_flag(void)
{
  return 0;
}




/* FUN_0005b190 @ 0x5b190   (est. sk_panic_msg)
 * Ghidra: void FUN_0005b190(undefined8 arg1,undefined8 arg2)
 * sk_panic_msg: cL4 sk panic msg operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_panic_msg(uint64_t arg1,uint64_t arg2)
{
                    
  sk_panic(arg1,arg2,NULL);
}




/* FUN_0005b1b0 @ 0x5b1b0   (est. sk_panic)
 * Ghidra: void FUN_0005b1b0(ulong arg1,undefined8 arg2,undefined8 arg3)
 * sk_panic: cL4 sk panic operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_panic(unsigned long arg1,uint64_t arg2,uint64_t arg3)
{
  long t0;
  uint16_t *t6;
  uint16_t t16;
  uint16_t t17;
  uint64_t t18;
  uint64_t t19;
  sk_code_t t3;
  unsigned long t20;
  long t1;
  uint64_t t7;
  uint64_t t8;
  uint64_t t9;
  uint64_t t10;
  uint64_t t11;
  long *t4;
  char *t2;
  unsigned long t12;
  unsigned long t13;
  unsigned long *t5;
  unsigned long t14;
  unsigned long t15;
  unsigned long unaff_x30;
  unsigned long stk17;
  uint64_t stk27;
  uint64_t stk16;
  uint64_t stk26;
  uint64_t stk15;
  uint8_t stk1 [128];
  uint64_t stk14;
  uint8_t stk0 [64];
  uint64_t stk13;
  uint64_t stk12;
  uint32_t stk11;
  uint32_t stk10;
  uint32_t stk9;
  uint32_t stk8;
  unsigned long stk7;
  uint64_t stk25;
  uint64_t stk6;
  uint64_t stk24;
  unsigned long stk5;
  uint64_t stk23;
  uint64_t stk4;
  uint64_t stk22;
  uint64_t stk3;
  uint64_t stk30;
  unsigned long stk21;
  unsigned long stk29;
  uint64_t stk20;
  uint64_t stk28;
  uint64_t stk19;
  unsigned long stk2 [11];
  unsigned long stk18 [2];
  
  t20 = sk_current_thread();
  if (((arg1 != 0) || (arg1 = t20, t20 <= t20 + 0x178)) &&
     (*(unsigned long *)(arg1 + 0x48) = *(unsigned long *)(arg1 + 0x48) | 0x20, t20 <= t20 + 0x178)) {
    *(unsigned long *)(t20 + 0x48) = *(unsigned long *)(t20 + 0x48) | 0x40;
    t15 = t20 >> 0xe & 0xffffff;
    t12 = arg1 >> 0xe & 0xffffff;
    sk_panic_log(0xeb1a02bf914012ba,sk_str_73);
    sk_log_fmt(sk_str_70,0x20,1,0xeb1a02bf914012ba);
    sk_log_v(0xeb1a02bf914012ba,arg2,arg3);
    sk_log_fmt(&sk_global_031,2,1,0xeb1a02bf914012ba);
    if (arg1 == t20) {
      sk_ctx_panic(sk_str_42,0x3d,0xeb1a02bf914012ba,arg1,1,0,0,0,t15,t12)
      ;
    }
    sk_memset(stk1,0x1b8);
    sk_snprintf(stk1,0x80,arg2,arg3);
    t12 = *(unsigned long *)(arg1 + 8);
    stk15 = 0;
    if (t12 <= t12 + 0x28) {
      t1 = sk_cap_resolve_name(t12,&stk15);
      if (t1 == 0) {
        t1 = sk_global_get(0x6b2568,1,1);
        if (*(long *)(t1 + 0x78) == 0) {
          t2 = sk_str_55;
        }
        else {
          t2 = &sk_global_032;
        }
      }
      else {
        t2 = &sk_global_032;
      }
      sk_format_vsnprintf(stk0,0x130,0x40,t2);
      t1 = sk_global_get(0x6b2568,1,1);
      stk14 = *(uint64_t *)(t1 + 0x40);
      stk13 = sk_macho_uuid(t12);
      stk12 = *(uint64_t *)(arg1 + 0x10);
      stk11 = sk_format_uuid();
      stk10 = sk_macho_uuid2(t12);
      stk9 = sk_ctx_vm2(*(uint64_t *)(arg1 + 0xa8));
      stk8 = *(uint32_t *)(arg1 + 0x118);
      stk16 = 0;
      stk26 = 0;
      sk_ctx_save(arg1,&stk26,&stk16);
      stk27 = 0;
      stk17 = 0;
      sk_ctx_meta(&stk17,arg1);
      stk18[0] = 0;
      if (arg1 == t20) {
        stk17 = 0x5b40c;
        stk18[0] = unaff_x30;
      }
      t7 = sk_ctx_sp(arg1);
      t8 = sk_ctx_ip(arg1);
      t9 = sk_ctx_id(arg1);
      t10 = sk_ctx_owner(arg1);
      t19 = stk26;
      t18 = stk16;
      t11 = sk_ctx_regs(arg1);
      t1 = sk_range_lookup(stk18,0);
      if (t1 == 0) {
        t12 = 0xffff000000000000;
      }
      else {
        t12 = (unsigned long)*(unsigned short *)(t1 + 0x40) << 0x30;
      }
      t12 = stk18[0] & 0xffffffffffff | t12;
      stk18[0] = stk17;
      t1 = sk_range_lookup(stk18,0);
      if (t1 == 0) {
        stk29 = 0xffff000000000000;
      }
      else {
        stk29 = (unsigned long)*(unsigned short *)(t1 + 0x40) << 0x30;
      }
      stk29 = stk18[0] & 0xffffffffffff | stk29;
      stk4 = 0;
      stk22 = t19;
      stk3 = t18;
      stk20 = stk27;
      stk28 = 0;
      stk7 = arg1;
      stk25 = t7;
      stk6 = t8;
      stk24 = t9;
      stk5 = arg1;
      stk23 = t10;
      stk30 = t11;
      stk21 = t12;
      if (*(long *)(arg1 + 0xa8) != 0) {
        stk4 = sk_ctx_vm();
      }
      t15 = sk_msg_cap_read(arg1,0,&stk19,0xc,0);
      t12 = 0;
      if (t15 != 0) {
        t12 = 0;
        t5 = &stk19;
        t13 = t15;
        do {
          if (((t5 < &stk19) || (stk18 < t5 + 1)) || (t5 + 1 < t5))
          goto LAB_0005b820;
          t14 = (unsigned long)*(unsigned short *)((long)t5 + 6);
          if (t12 <= t14 && t14 != 0xffff) {
            t12 = t14 + 1;
          }
          t5 = t5 + 1;
          t13 = t13 - 1;
        } while (t13 != 0);
      }
      t1 = 0;
      if (t12 < 7) {
        t1 = 6 - t12;
      }
      if (t15 < (unsigned long)(t1 << 1)) {
        if ((stk18 < stk2 + t15) || (stk2 + t15 < &stk19 + t15))
        goto LAB_0005b820;
        *(uint16_t *)((long)stk2 + t15 * 8 + -2) = 6;
      }
      else {
        t15 = t1 << 1;
      }
      if (t12 < 7) {
        t1 = 6 - t12;
        t4 = (long *)sk_global_get(0x6b2568,1,1);
        for (t4 = (long *)*t4; t4 != (long *)0x0; t4 = (long *)*t4) {
          if ((*(char *)(t4 + 1) < '\0') &&
             (t13 = (unsigned long)*(unsigned short *)(t4 + 8), t13 < t12)) {
            t5 = &stk19 + t1 * 2 + t13 * 2;
            if ((t5 < &stk19 || stk18 < t5 + 2) || t5 + 2 < t5)
            goto LAB_0005b820;
            t13 = (t1 + t13) * 0x10 + 0x158;
            t0 = 0;
            if (t13 < 0x1b9) {
              t0 = 0x1b8 - t13;
            }
            t13 = sk_memmove(t5,t4 + 2,0x10,t0);
            if (t13 + 0x10 < t13) goto LAB_0005b820;
          }
        }
      }
      else {
        t1 = 0;
      }
      if (t15 != 0) {
        t5 = &stk19;
        do {
          if (((t5 < &stk19) || (stk18 < t5 + 1)) || (t5 + 1 < t5))
          goto LAB_0005b820;
          *t5 = *t5 + (t1 << 0x30);
          t15 = t15 - 1;
          t5 = t5 + 1;
        } while (t15 != 0);
      }
      if (*(sk_code_t *)(t20 + 0xa0) == (sk_code_t )0x0) {
        t2 = sk_str_71;
      }
      else {
        (**(sk_code_t *)(t20 + 0xa0))(stk1);
        t2 = sk_str_72;
      }
      sk_panic_log(0xeb1a02bf914012ba,t2);
      sk_syscall_print(stk1,0x6b04d0,0x2000,0);
      sk_boot_puts(sk_str_57,0x6b04d0,0x2000,0xeb1a02bf914012ba);
      t1 = 0;
      while (t1 != 0x2000) {
        t2 = (char *)(t1 + 0x6b04d0);
        t1 = t1 + 1;
        if (*t2 == '\0') {
          sk_trace(0x6b04d0,0xaa1603fbd280001c);
          t1 = sk_cpu_irq3();
          if (t1 != 0) {
            sk_tcb_b(t1,6,0x6b04d0);
          }
          t1 = sk_cpu_irq();
          if (t1 != 0) {
            t6 = (uint16_t *)sk_tpidrro;
            t16 = *t6;
            t17 = t6[2];
            sk_svc(0);
            *(char *)t6 = (char)t16;
            *(uint8_t *)((long)t6 + 7) = *(uint8_t *)((long)t6 + 7);
            *(uint8_t *)(t6 + 3) = *(uint8_t *)(t6 + 3);
            *(char *)((long)t6 + 5) = (char)((unsigned short)t17 >> 8);
            *(char *)(t6 + 2) = (char)t17;
            *(uint8_t *)((long)t6 + 3) = *(uint8_t *)((long)t6 + 3);
            *(uint8_t *)(t6 + 1) = *(uint8_t *)(t6 + 1);
            *(char *)((long)t6 + 1) = (char)((unsigned short)t16 >> 8);
          }
          sk_panic_log(0xeb1a02bf914012ba,sk_str_74);
                    
          t3 = (sk_code_t )sk_break(1,0x5b820);
          (*t3)();
        }
      }
    }
  }
LAB_0005b820:
                    
  t3 = (sk_code_t )sk_break(0x5519,0x5b824);
  (*t3)();
}




/* FUN_0005b824 @ 0x5b824   (est. sk_format_vsnprintf)
 * Ghidra: void FUN_0005b824(undefined8 arg1,undefined8 arg2,undefined8 arg3,undefined8 arg4)
 * sk_format_vsnprintf: cL4 sk format vsnprintf operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_format_vsnprintf(uint64_t arg1,uint64_t arg2,uint64_t arg3,uint64_t arg4)
{
  sk_vsnprintf(arg1,arg3,0,arg2,arg4,NULL);
  return;
}




/* FUN_0005b860 @ 0x5b860   (est. sk_kernel_state_get)
 * Ghidra: undefined8 FUN_0005b860(undefined8 *arg1)
 * sk_kernel_state_get: cL4 sk kernel state get operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

uint64_t sk_kernel_state_get(uint64_t *arg1)
{
  uint64_t t1;
  long t0;
  
  t0 = sk_global_get(0x6b2568,1,1);
  t1 = *(uint64_t *)(t0 + 0x78);
  *arg1 = *(uint64_t *)(t0 + 0x70);
  return t1;
}




/* FUN_0005b89c @ 0x5b89c   (est. sk_kernel_field_40)
 * Ghidra: undefined8 FUN_0005b89c(void)
 * sk_kernel_field_40: cL4 sk kernel field 40 operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

uint64_t sk_kernel_field_40(void)
{
  long t0;
  
  t0 = sk_global_get(0x6b2568,1,1);
  return *(uint64_t *)(t0 + 0x40);
}




/* FUN_0005b8c8 @ 0x5b8c8   (est. sk_format_uuid)
 * Ghidra: void FUN_0005b8c8(void)
 * sk_format_uuid: cL4 sk format uuid operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_format_uuid(void)
{
  uint8_t *t2;
  sk_code_t t3;
  unsigned int t4;
  long t0;
  unsigned long t5;
  long t1;
  unsigned long stk3;
  unsigned long stk4;
  uint8_t stk2;
  uint8_t stk0 [7];
  long stk1;
  
  stk1 = -0x2c8502b44bfffed6;
  t0 = sk_global_get(0x6b2568,1,1);
  t1 = 0;
  t4 = 0;
  t5 = (unsigned long)*(unsigned short *)(t0 + 0x40);
  stk2 = 0;
  stk3 = (unsigned long)(uint8_t)sk_str_00[2] << 0x10 |
             (unsigned long)(uint8_t)sk_str_00[3] << 0x18 |
             (unsigned long)(unsigned short)sk_str_00._0_2_ |
             (unsigned long)((unsigned int)(uint8_t)sk_str_00[6] << 0x10 |
                     (unsigned int)(uint8_t)sk_str_00[7] << 0x18 |
                    (unsigned int)(unsigned short)sk_str_00._4_2_) << 0x20;
  stk4 = (unsigned long)(uint8_t)sk_str_00[10] << 0x10 |
              (unsigned long)(uint8_t)sk_str_00[0xb] << 0x18 |
              (unsigned long)(unsigned short)sk_str_00._8_2_ |
              (unsigned long)((unsigned int)(uint8_t)sk_str_00[0xe] << 0x10 |
                      (unsigned int)(uint8_t)sk_str_00[0xf] << 0x18 |
                     (unsigned int)(unsigned short)sk_str_00._12_2_) << 0x20;
  while( true ) {
    t2 = (uint8_t *)((long)&stk3 + (t5 & 0xf));
    if ((stk0 <= t2) || (t2 < &stk3)) break;
    t4 = (unsigned int)*t2 << (unsigned long)((unsigned int)t1 & 0x1f) | t4;
    t5 = t5 >> 4;
    t1 = t1 + 8;
    if (t1 == 0x20) {
      if (stk1 == -0x2c8502b44bfffed6) {
        return;
      }
                    
      sk_noreturn_error(t4);
    }
  }
                    
  t3 = (sk_code_t )sk_break(0x5519,0x5ba10);
  (*t3)();
}




/* FUN_0005ba14 @ 0x5ba14   (est. sk_kernel_head)
 * Ghidra: undefined8 FUN_0005ba14(void)
 * sk_kernel_head: cL4 sk kernel head operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

uint64_t sk_kernel_head(void)
{
  uint64_t *t0;
  
  t0 = (uint64_t *)sk_global_get(0x6b2568,1,1);
  return *t0;
}




/* FUN_0005ba40 @ 0x5ba40   (est. sk_register_global_3)
 * Ghidra: void FUN_0005ba40(undefined8 arg1)
 * sk_register_global_3: cL4 sk register global 3 operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_register_global_3(uint64_t arg1)
{
                    
  uRam000000000064db30 = 0x6b24d0;
  sk_global_106 = arg1;
  sk_register_global();
  return;
}




/* FUN_0005ba5c @ 0x5ba5c   (est. sk_register_global)
 * Ghidra: void FUN_0005ba5c(long *arg1)
 * sk_register_global: cL4 sk register global operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_register_global(long *arg1)
{
  sk_code_t t1;
  long *t2;
  long t0;
  
  t0 = sk_tpidr;
  t2 = *(long **)(t0 + 0x10);
  while (*arg1 == 0) {
    if (t2 + 1 < t2) goto LAB_0005baa8;
    t0 = *t2;
    *arg1 = t0;
    if (*t2 == t0) {
      *t2 = (long)arg1;
      return;
    }
  }
  sk_rt_lock();
LAB_0005baa8:
                    
  t1 = (sk_code_t )sk_break(0x5519,0x5baac);
  (*t1)();
}




/* FUN_0005baac @ 0x5baac   (est. sk_lookup_thread_obj)
 * Ghidra: long FUN_0005baac(int arg1,int arg2)
 * sk_lookup_thread_obj: cL4 sk lookup thread obj operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

long sk_lookup_thread_obj(int arg1,int arg2)
{
  long t0;
  long t1;
  long *t2;
  
  t1 = sk_tpidr;
  t2 = (long *)**(long **)(t1 + 0x10);
  if (t2 == (long *)0x0) {
    t1 = 0;
  }
  else {
    t0 = 0;
    do {
      t1 = t2[3];
      if ((int)t2[2] != arg2 || (int)t2[1] != arg1) {
        t1 = t0;
      }
      t2 = (long *)*t2;
      t0 = t1;
    } while (t2 != (long *)0x0);
  }
  return t1;
}




/* FUN_0005baf0 @ 0x5baf0   (est. sk_list_push)
 * Ghidra: void FUN_0005baf0(ulong *arg1)
 * sk_list_push: cL4 sk list push operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_list_push(unsigned long *arg1)
{
  short t2;
  sk_code_t t0;
  unsigned long *t1;
  unsigned long t3;
  
  t1 = (unsigned long *)sk_global_get(0x6b2568,1,1);
  t2 = (short)t1[1];
  *(short *)(t1 + 1) = t2 + 1;
  *(short *)(arg1 + 8) = t2;
  while ((t3 = *t1, t3 <= t3 + 0x78 && (*arg1 = t3, t1 <= t1 + 0x12))) {
    if (*t1 == t3) {
      *t1 = (unsigned long)arg1;
      return;
    }
  }
                    
  t0 = (sk_code_t )sk_break(0x5519,0x5bb68);
  (*t0)();
}




/* FUN_0005bb68 @ 0x5bb68   (est. sk_kernel_get)
 * Ghidra: void FUN_0005bb68(void)
 * sk_kernel_get: cL4 sk kernel get operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_kernel_get(void)
{
  sk_global_get(0x6b2568,1,1);
  return;
}




/* FUN_0005bb7c @ 0x5bb7c   (est. sk_list_head)
 * Ghidra: ulong * FUN_0005bb7c(void)
 * sk_list_head: cL4 sk list head operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

unsigned long * sk_list_head(void)
{
  unsigned long *t1;
  sk_code_t t0;
  unsigned long *t2;
  
  t2 = (unsigned long *)sk_global_get(0x6b2568,1,1);
  t1 = (unsigned long *)*t2;
  if (*t2 == 0) {
    t2 = (unsigned long *)0x65c4e8;
  }
  else {
    do {
      t2 = t1;
      if (*t2 == 0) break;
      t1 = (unsigned long *)*t2;
    } while ((*(uint8_t *)(t2 + 1) & 1) == 0);
    if (t2 + 0xf < t2) {
                    
      t0 = (sk_code_t )sk_break(0x5519,0x5bbc8);
      (*t0)();
    }
  }
  return t2;
}




/* FUN_0005bbd8 @ 0x5bbd8   (est. sk_strtok)
 * Ghidra: ulong FUN_0005bbd8(long arg1,long *arg2)
 * sk_strtok: cL4 sk strtok operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

unsigned long sk_strtok(long arg1,long *arg2)
{
  unsigned long t4;
  unsigned long t5;
  bool t0;
  sk_code_t t3;
  long t1;
  long t2;
  unsigned long t6;
  
  t2 = *(long *)(arg1 + 0x48);
  t6 = *(unsigned long *)(arg1 + 0x50);
  do {
    t1 = sk_strchr(t6,0x2f,t2);
    if (t1 == 0) {
      *arg2 = t2;
      return t6;
    }
    t4 = t1 + 1;
    t5 = t6 + t2;
    t2 = ~(t1 - t6) + t2;
    t0 = t6 <= t4;
    t6 = t4;
  } while (t4 <= t5 && t0);
                    
  t3 = (sk_code_t )sk_break(0x5519,0x5bc30);
  (*t3)();
}




/* FUN_0005bc48 @ 0x5bc48   (est. sk_range_lookup)
 * Ghidra: void FUN_0005bc48(ulong *arg1,int arg2)
 * sk_range_lookup: cL4 sk range lookup operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_range_lookup(unsigned long *arg1,int arg2)
{
  long *t0;
  unsigned long t1;
  
  t0 = (long *)sk_global_get(0x6b2568,1,1);
  t0 = (long *)*t0;
  do {
    if (t0 == (long *)0x0) {
      return;
    }
    if (arg2 == 0) {
      t1 = *arg1;
      if (((unsigned long)t0[5] <= t1) && (t1 - t0[5] < (unsigned long)t0[6])) {
        t1 = t1 - t0[4];
        goto LAB_0005bcd0;
      }
    }
    else if (*(short *)(t0 + 8) == (short)(*arg1 >> 0x30)) {
      t1 = *arg1 & 0xffffffffffff;
LAB_0005bcd0:
      *arg1 = t1;
      return;
    }
    t0 = (long *)*t0;
  } while( true );
}




/* FUN_0005bce0 @ 0x5bce0   (est. sk_register_cb)
 * Ghidra: void FUN_0005bce0(long arg1)
 * sk_register_cb: cL4 sk register cb operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_register_cb(long arg1)
{
  sk_code_t t0;
  
  if (arg1 + 8U <= arg1 + 0xcU) {
    sk_register_cb2(arg1 + 8U,sk_list_push_28);
    return;
  }
                    
  t0 = (sk_code_t )sk_break(0x5519,0x5bd10);
  (*t0)();
}




/* FUN_0005bd10 @ 0x5bd10   (est. sk_list_push_28)
 * Ghidra: void FUN_0005bd10(ulong *arg1)
 * sk_list_push_28: cL4 sk list push 28 operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_list_push_28(unsigned long *arg1)
{
  sk_code_t t0;
  unsigned long t1;
  unsigned long t2;
  
  t1 = sk_global_get(0x6b2568,1,1);
  while ((t2 = *(unsigned long *)(t1 + 0x28), t2 <= t2 + 0x28 &&
         (*arg1 = t2, t1 <= t1 + 0x90))) {
    if (*(unsigned long *)(t1 + 0x28) == t2) {
      *(unsigned long *)(t1 + 0x28) = (unsigned long)arg1;
      return;
    }
  }
                    
  t0 = (sk_code_t )sk_break(0x5519,0x5bd7c);
  (*t0)();
}




/* FUN_0005bd7c @ 0x5bd7c   (est. sk_iter_list_cb)
 * Ghidra: void FUN_0005bd7c(sk_code_t arg1,undefined8 arg2)
 * sk_iter_list_cb: cL4 sk iter list cb operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_iter_list_cb(sk_code_t arg1,uint64_t arg2)
{
  sk_code_t t2;
  unsigned long t4;
  int t0;
  long t1;
  unsigned long *t3;
  uint8_t stk0;
  
  stk0 = 0;
  do {
    t0 = sk_disable_preempt(&stk0);
  } while (t0 == 0);
  t1 = sk_global_get(0x6b2568,1,1);
  t3 = *(unsigned long **)(t1 + 0x10);
  if (t3 == (unsigned long *)0x0) {
    t4 = 0;
    goto LAB_0005bdf4;
  }
  do {
    t4 = *t3;
    if ((t4 >> 0x25 & 1) != 0) break;
    t3 = (unsigned long *)(t4 & 0xfffffffff);
  } while (t3 != (unsigned long *)0x0);
  do {
    while( true ) {
      if (t3 + 0x2f < t3) {
                    
        t2 = (sk_code_t )sk_break(0x5519,0x5be48);
        (*t2)();
      }
LAB_0005bdf4:
      if (t3 == (unsigned long *)0x0) {
        sk_enable_preempt(&stk0);
        return;
      }
      (*arg1)(arg2);
      t3 = (unsigned long *)(t4 & 0xfffffffff);
      if (t3 != (unsigned long *)0x0) break;
      t4 = 0;
    }
    do {
      t4 = *t3;
      if ((t4 >> 0x25 & 1) != 0) break;
      t3 = (unsigned long *)(t4 & 0xfffffffff);
    } while (t3 != (unsigned long *)0x0);
  } while( true );
}




/* FUN_0005be48 @ 0x5be48   (est. sk_kernel_set_70)
 * Ghidra: void FUN_0005be48(undefined8 arg1,undefined8 arg2)
 * sk_kernel_set_70: cL4 sk kernel set 70 operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_kernel_set_70(uint64_t arg1,uint64_t arg2)
{
  long t0;
  
  t0 = sk_global_get(0x6b2568,1,1);
  *(uint64_t *)(t0 + 0x70) = arg2;
  *(uint64_t *)(t0 + 0x78) = arg1;
  return;
}




/* FUN_0005be84 @ 0x5be84   (est. sk_waitq_enqueue)
 * Ghidra: void FUN_0005be84(ulong *arg1,int arg2)
 * sk_waitq_enqueue: cL4 sk waitq enqueue operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_waitq_enqueue(unsigned long *arg1,int arg2)
{
  long t0;
  unsigned long *t1;
  unsigned long t2;
  
  t0 = sk_global_get(0x6b2568,1,1);
  if (arg2 == 0) {
    t1 = (unsigned long *)(t0 + 0x10);
    *(long *)(t0 + 0x18) = *(long *)(t0 + 0x18) + 1;
  }
  else {
    t1 = (unsigned long *)(t0 + 0x20);
  }
  do {
    t2 = *t1;
    *arg1 = t2 & 0xfffffffff | 0x2000000000;
  } while (*t1 != t2);
  *t1 = (unsigned long)arg1;
  if (sk_global_107 == (sk_code_t )0x0) {
    return;
  }
                    
                    
  (*sk_global_107)(arg1,1);
  return;
}




/* FUN_0005bf20 @ 0x5bf20   (est. sk_waitq_dequeue)
 * Ghidra: void FUN_0005bf20(ulong *arg1)
 * sk_waitq_dequeue: cL4 sk waitq dequeue operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_waitq_dequeue(unsigned long *arg1)
{
  sk_code_t t1;
  long t0;
  unsigned long t5;
  unsigned long *t2;
  unsigned long *t3;
  unsigned long *t4;
  unsigned long t6;
  unsigned long t7;
  uint8_t stk0;
  
  t0 = sk_global_get(0x6b2568,1,1);
  *arg1 = *arg1 & 0xfffffffff;
  stk0 = 0;
  do {
    t5 = sk_disable_preempt(&stk0);
  } while ((t5 & 1) == 0);
  do {
    while( true ) {
      t4 = *(unsigned long **)(t0 + 0x10);
      if (t4 == (unsigned long *)0x0) goto LAB_0005c06c;
      if (arg1 != t4) break;
      if ((t4 + 0x2f < arg1) || (t5 = *arg1 & 0xfffffffff, t5 + 0x178 < t5)) {
LAB_0005c0a8:
                    
        t1 = (sk_code_t )sk_break(0x5519,0x5c0ac);
        (*t1)();
      }
      if (*(unsigned long **)(t0 + 0x10) == t4) {
        *(unsigned long *)(t0 + 0x10) = t5;
        goto LAB_0005c06c;
      }
    }
    if (t4 + 0x2f < t4) goto LAB_0005c0a8;
    do {
      t5 = *t4;
      if ((t5 >> 0x25 & 1) != 0) break;
      t4 = (unsigned long *)(t5 & 0xfffffffff);
    } while (t4 != (unsigned long *)0x0 && arg1 != t4);
    if (t4 + 0x2f < t4) goto LAB_0005c0a8;
    t3 = t4;
    t7 = t5;
    if (t4 == (unsigned long *)0x0) goto LAB_0005c06c;
    do {
      t6 = t7;
      t2 = t3;
      t3 = t2;
      if (t2 == arg1) break;
      t7 = 0;
      t3 = (unsigned long *)(t6 & 0xfffffffff);
      if ((t3 != (unsigned long *)0x0) && (arg1 != t3)) {
        do {
          t7 = *t3;
          if ((t7 >> 0x25 & 1) != 0) break;
          t3 = (unsigned long *)(t7 & 0xfffffffff);
        } while (t3 != (unsigned long *)0x0 && arg1 != t3);
      }
      if (t3 + 0x2f < t3) goto LAB_0005c0a8;
      t4 = t2;
      t5 = t6;
    } while (t3 != (unsigned long *)0x0);
    if (t3 == (unsigned long *)0x0) goto LAB_0005c06c;
  } while ((t4 == (unsigned long *)0x0) || (*t4 != t5));
  *t4 = *arg1 & 0xfff0000000000000 |
            *arg1 & 0xfffffffff | (t5 >> 0x24 & 0xffff) << 0x24;
LAB_0005c06c:
  sk_enable_preempt(&stk0);
  sk_tlb_flush();
  *arg1 = 0;
  if (sk_global_107 != (sk_code_t )0x0) {
    (*sk_global_107)(arg1,0);
  }
  return;
}




/* FUN_0005c0ac @ 0x5c0ac   (est. sk_waitq_dequeue_all)
 * Ghidra: void FUN_0005c0ac(void)
 * sk_waitq_dequeue_all: cL4 sk waitq dequeue all operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_waitq_dequeue_all(void)
{
  sk_code_t t1;
  long t0;
  unsigned long *t2;
  unsigned long t3;
  
  t0 = sk_global_get(0x6b2568,1,1);
  while( true ) {
    t2 = *(unsigned long **)(t0 + 0x20);
    if (t2 == (unsigned long *)0x0) {
      return;
    }
    if ((t2 + 0x2f < t2) || (t3 = *t2 & 0xfffffffff, t3 + 0x178 < t3)) break;
    if (*(unsigned long **)(t0 + 0x20) == t2) {
      *(unsigned long *)(t0 + 0x20) = t3;
      *t2 = 0;
      return;
    }
  }
                    
  t1 = (sk_code_t )sk_break(0x5519,0x5c11c);
  (*t1)();
}




/* FUN_0005c16c @ 0x5c16c   (est. sk_register_global_2)
 * Ghidra: void FUN_0005c16c(void)
 * sk_register_global_2: cL4 sk register global 2 operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_register_global_2(void)
{
                    
  uRam000000000064db50 = 0x6b2570;
  sk_register_global();
  return;
}




/* FUN_0005c184 @ 0x5c184   (est. sk_log_append)
 * Ghidra: ulong FUN_0005c184(undefined8 arg1,ulong arg2)
 * sk_log_append: cL4 sk log append operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

unsigned long sk_log_append(uint64_t arg1,unsigned long arg2)
{
  unsigned long t5;
  long t0;
  sk_code_t t1;
  long *t2;
  unsigned long *t3;
  unsigned long *t4;
  
  t0 = sk_tpidr;
  t2 = (long *)**(long **)(t0 + 0x10);
  if (t2 == (long *)0x0) {
    t4 = (unsigned long *)0x0;
  }
  else {
    t3 = (unsigned long *)0x0;
    do {
      t4 = (unsigned long *)t2[3];
      if ((int)t2[2] != 5 || (int)t2[1] != 1) {
        t4 = t3;
      }
      t2 = (long *)*t2;
      t3 = t4;
    } while (t2 != (long *)0x0);
  }
  t3 = t4 + 0x10;
  if (t3 <= t4 + 0x12) {
    sk_lock_prepare(t3);
    if ((arg2 < 0x79) && (*t4 <= 0x78 - arg2)) {
      t5 = (long)t4 + *t4 + 8;
      sk_memcpy2(t5,arg1,arg2);
      if (t5 + arg2 < t5) goto LAB_0005c274;
      *t4 = *t4 + arg2;
    }
    else {
      arg2 = 0;
    }
    if (t4 <= t4 + 0x12) {
      sk_unlock(t3);
      return arg2;
    }
  }
LAB_0005c274:
                    
  t1 = (sk_code_t )sk_break(0x5519,0x5c278);
  (*t1)();
}




/* FUN_0005c278 @ 0x5c278   (est. sk_log_consume)
 * Ghidra: ulong FUN_0005c278(ulong arg1,ulong arg2)
 * sk_log_consume: cL4 sk log consume operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

unsigned long sk_log_consume(unsigned long arg1,unsigned long arg2)
{
  unsigned long *t3;
  long t0;
  sk_code_t t1;
  long *t2;
  unsigned long *t4;
  unsigned long *t5;
  
  t0 = sk_tpidr;
  t2 = (long *)**(long **)(t0 + 0x10);
  if (t2 == (long *)0x0) {
    t5 = (unsigned long *)0x0;
  }
  else {
    t4 = (unsigned long *)0x0;
    do {
      t5 = (unsigned long *)t2[3];
      if ((int)t2[2] != 5 || (int)t2[1] != 1) {
        t5 = t4;
      }
      t2 = (long *)*t2;
      t4 = t5;
    } while (t2 != (long *)0x0);
  }
  t4 = t5 + 0x10;
  if (t4 <= t5 + 0x12) {
    sk_lock_prepare(t4);
    t0 = *t5 - arg2;
    if (*t5 < arg2) {
      arg2 = 0;
    }
    else {
      t3 = (unsigned long *)((long)(t5 + 1) + t0);
      if (((0x78U - t0 < arg2 || t4 < t3) || t3 < t5 + 1) ||
         (sk_memcpy2(arg1,t3,arg2), arg1 + arg2 < arg1)) goto LAB_0005c320;
      sk_memset(t3,arg2);
      *t5 = *t5 - arg2;
    }
    if (t5 <= t5 + 0x12) {
      sk_unlock(t4);
      return arg2;
    }
  }
LAB_0005c320:
                    
  t1 = (sk_code_t )sk_break(0x5519,0x5c324);
  (*t1)();
}




/* FUN_0005c380 @ 0x5c380   (est. sk_dispatch_reset2)
 * Ghidra: void FUN_0005c380(void)
 * sk_dispatch_reset2: cL4 sk dispatch reset2 operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_dispatch_reset2(void)
{
  return;
}




/* FUN_0005c414 @ 0x5c414   (est. sk_dispatch_reset3)
 * Ghidra: void FUN_0005c414(void)
 * sk_dispatch_reset3: cL4 sk dispatch reset3 operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_dispatch_reset3(void)
{
  return;
}




/* FUN_0005c440 @ 0x5c440   (est. sk_dispatch_reset4)
 * Ghidra: void FUN_0005c440(void)
 * sk_dispatch_reset4: cL4 sk dispatch reset4 operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_dispatch_reset4(void)
{
  return;
}




/* FUN_0005c468 @ 0x5c468   (est. sk_dispatch_reset5)
 * Ghidra: void FUN_0005c468(void)
 * sk_dispatch_reset5: cL4 sk dispatch reset5 operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_dispatch_reset5(void)
{
  return;
}




/* FUN_0005c490 @ 0x5c490   (est. sk_dispatch_reset6)
 * Ghidra: void FUN_0005c490(void)
 * sk_dispatch_reset6: cL4 sk dispatch reset6 operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_dispatch_reset6(void)
{
  return;
}




/* FUN_0005c4a8 @ 0x5c4a8   (est. sk_dispatch_reset7)
 * Ghidra: void FUN_0005c4a8(void)
 * sk_dispatch_reset7: cL4 sk dispatch reset7 operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_dispatch_reset7(void)
{
  return;
}




/* FUN_0005c4c0 @ 0x5c4c0   (est. sk_dispatch_reset8)
 * Ghidra: void FUN_0005c4c0(void)
 * sk_dispatch_reset8: cL4 sk dispatch reset8 operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_dispatch_reset8(void)
{
  return;
}




/* FUN_0005c510 @ 0x5c510   (est. sk_dispatch_reset9)
 * Ghidra: void FUN_0005c510(void)
 * sk_dispatch_reset9: cL4 sk dispatch reset9 operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_dispatch_reset9(void)
{
  return;
}




/* FUN_0005c520 @ 0x5c520   (est. sk_dispatch_reset10)
 * Ghidra: void FUN_0005c520(void)
 * sk_dispatch_reset10: cL4 sk dispatch reset10 operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_dispatch_reset10(void)
{
  return;
}




/* FUN_0005c53c @ 0x5c53c   (est. sk_dispatch_reset11)
 * Ghidra: void FUN_0005c53c(void)
 * sk_dispatch_reset11: cL4 sk dispatch reset11 operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_dispatch_reset11(void)
{
  return;
}




/* FUN_0005c558 @ 0x5c558   (est. sk_dispatch_reset12)
 * Ghidra: void FUN_0005c558(void)
 * sk_dispatch_reset12: cL4 sk dispatch reset12 operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_dispatch_reset12(void)
{
  return;
}




/* FUN_0005c570 @ 0x5c570   (est. sk_dispatch_reset13)
 * Ghidra: void FUN_0005c570(void)
 * sk_dispatch_reset13: cL4 sk dispatch reset13 operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_dispatch_reset13(void)
{
  return;
}




/* FUN_0005c588 @ 0x5c588   (est. sk_dispatch_error_print)
 * Ghidra: void FUN_0005c588(void)
 * sk_dispatch_error_print: cL4 sk dispatch error print operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_dispatch_error_print(void)
{
  sk_format_vsnprintf(NULL,0x20,0x1f,sk_str_39);
  return;
}




/* FUN_0005c5a0 @ 0x5c5a0   (est. sk_dispatch_default)
 * Ghidra: void FUN_0005c5a0(void)
 * sk_dispatch_default: cL4 sk dispatch default operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_dispatch_default(void)
{
  return;
}




/* FUN_0005c5b4 @ 0x5c5b4   (est. sk_cap_word_lookup)
 * Ghidra: long FUN_0005c5b4(undefined8 arg1)
 * sk_cap_word_lookup: cL4 sk cap word lookup operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

long sk_cap_word_lookup(uint64_t arg1)
{
  long t0;
  long t1;
  uint8_t stk0 [16];
  
  t0 = sk_vspace_op2();
  if (t0 != 0) {
    stk0 = sk_boot_heap();
    t1 = (*(sk_code_t )*stk0._8_8_)(stk0._0_8_,arg1,t0,t0,0);
    if (t1 != 0) {
      sk_xrt_init(t0);
      t0 = 0;
    }
  }
  return t0;
}




/* FUN_0005c614 @ 0x5c614   (est. sk_method_handle)
 * Ghidra: void FUN_0005c614(undefined8 arg1)
 * sk_method_handle: cL4 sk method handle operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_method_handle(uint64_t arg1)
{
  uint8_t stk0 [16];
  
  stk0 = sk_boot_heap();
  (**(sk_code_t *)(stk0._8_8_ + 0x10))(stk0._0_8_,arg1);
  sk_xrt_init(arg1);
  return;
}




/* FUN_0005c650 @ 0x5c650   (est. sk_error_from_code)
 * Ghidra: void FUN_0005c650(undefined8 *out, ulong code)
 * sk_error_from_code: cL4 sk error from code operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_error_from_code(uint64_t *out, unsigned long code)
{
    long t0;
    unsigned long t1;
    uint64_t hi, lo;

    /* Build the per-error-code dispatch records (4 fixed records at 0x64db60). */
    t1 = 0;
    t0 = 0x64db60;
    do {
        if ((((unsigned int)t1 - 1) & 0xff) < 3) {
            sk_dispatch_record((unsigned int)t1 & 0xff, t0);
        }
        t1 = t1 + 1;
        t0 = t0 + 0x50;
    } while (t1 != 4);

    lo = 0;
    hi = 0;
    sk_dispatch_record(code, &lo);
    sk_error_classify(code, &lo, 0, 1);

    /* 128-bit payload: the record's two 64-bit words are swapped so that the
     * classified error code lands in the message's result word. */
    out[0] = hi;
    out[1] = lo;
    out[2] = code & 0xffffffff;
    return;
}


/* FUN_0005c710 @ 0x5c710   (est. sk_dispatch_reset)
 * Ghidra: void FUN_0005c710(void)
 * sk_dispatch_reset: cL4 sk dispatch reset operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_dispatch_reset(void)
{
  long t0;
  long t1;
  
  t1 = 0;
  t0 = 0x64db60;
  do {
    if (((unsigned int)t1 - 1 & 0xff) < 3) {
      sk_dispatch_record((unsigned int)t1 & 0xff,t0);
    }
    t1 = t1 + 1;
    t0 = t0 + 0x50;
  } while (t1 != 4);
  return;
}




/* FUN_0005c764 @ 0x5c764   (est. sk_dispatch_record)
 * Ghidra: void FUN_0005c764(ulong arg1,long arg2)
 * sk_dispatch_record: cL4 sk dispatch record operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_dispatch_record(unsigned long arg1,long arg2)
{
  long t0;
  sk_code_t t1;
  unsigned long t2;
  unsigned long t3;
  unsigned long t4;
  unsigned long t5;
  
  t0 = (arg1 & 0xffffffff) * 0x50;
  t3 = t0 + 0x64db60;
  t4 = t0 + 0x64dbb0;
  if ((t3 < 0x64db60 || 0x64dca0 < t4) || t4 < t3) {
                    
    t1 = (sk_code_t )sk_break(0x5519,0x5c858);
    (*t1)();
  }
  sk_memcpy2(arg2,t3,0x50);
  if ((*(char *)(arg2 + 0x20) == '\x01') && (*(long *)(arg2 + 0x28) != 0)) {
    return;
  }
  if ((int)arg1 - 1U < 3) {
    t2 = sk_tcb_ao();
    *(unsigned long *)(arg2 + 0x28) = t2;
    t4 = t2;
    t3 = 1000000000;
    do {
      t5 = t3;
      t3 = 0;
      if (t5 != 0) {
        t3 = t4 / t5;
      }
      t3 = t4 - t3 * t5;
      t4 = t5;
    } while (t3 != 0);
    t4 = 0;
    if (t5 != 0) {
      t4 = t2 / t5;
    }
    t3 = 0;
    if (t5 != 0) {
      t3 = 1000000000 / t5;
    }
    *(unsigned long *)(arg2 + 0x30) = t4;
    *(unsigned long *)(arg2 + 0x38) = t3;
    sk_cap_record(arg1,0xffffffffffffffff,arg2 + 0x10,0);
    return;
  }
                    
  sk_panic_msg(0,sk_str_95);
}




/* FUN_0005c86c @ 0x5c86c   (est. sk_error_classify)
 * Ghidra: long FUN_0005c86c(undefined8 arg1,uint8_t (*arg2) [16],uint8_t (*arg3) [16], ulong arg4)
 * sk_error_classify: cL4 sk error classify operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

long sk_error_classify(uint64_t arg1,uint8_t (*arg2) [16],uint8_t (*arg3) [16], unsigned long arg4)
{
  unsigned long t2;
  uint64_t t3;
  uint64_t t4;
  int t0;
  long t1;
  uint8_t stk0 [16];
  uint64_t stk4;
  uint64_t stk10;
  uint64_t stk3;
  uint64_t stk9;
  uint64_t stk8;
  long stk2;
  long stk1;
  unsigned long stk7;
  uint64_t stk6;
  uint64_t stk5;
  
  stk7 = 0;
  stk1 = 0;
  stk5 = 0;
  stk6 = 0;
  stk9 = 0;
  stk3 = 0;
  stk2 = 0;
  stk8 = 0;
  stk10 = 0;
  stk4 = 0;
  sk_dispatch_record(arg1,&stk4);
  t4 = stk9;
  t3 = stk3;
  t0 = sk_macho_dysymtab(*(uint64_t *)*arg2,*(uint64_t *)(*arg2 + 8),stk3,stk9);
  if (t0 < 1) {
    stk0 = *arg2;
    if ((arg4 & 1) == 0) {
      stk0 = sk_macho_symtab(*(uint64_t *)*arg2,*(uint64_t *)(*arg2 + 8),stk4,stk10
                           );
    }
    t2 = 0;
    if (stk7 != 0) {
      t2 = (unsigned long)(stk1 * stk0._8_8_) / stk7;
    }
    t1 = t2 + stk2 * stk0._0_8_;
  }
  else {
    if (arg3 != (uint8_t (*) [16])0x0) {
      stk0 = sk_macho_symtab(*(uint64_t *)*arg2,*(uint64_t *)(*arg2 + 8),t3,t4);
      *arg3 = stk0;
    }
    t1 = -1;
  }
  return t1;
}




/* FUN_0005c924 @ 0x5c924   (est. sk_error_to_word)
 * Ghidra: long FUN_0005c924(undefined8 arg1)
 * sk_error_to_word: cL4 sk error to word operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

long sk_error_to_word(uint64_t arg1)
{
  long t0;
  long t1;
  long t2;
  
  if ((int)arg1 == 3) {
    t0 = sk_tcb_an();
    return t0;
  }
  t0 = sk_errno_name(arg1);
  if (((int)arg1 - 1U & 0xff) < 2) {
    do {
      t1 = t0;
      t2 = sk_tcb_an();
      t0 = sk_errno_name(arg1);
    } while (t0 != t1);
    return t1 + t2;
  }
                    
  sk_panic_msg(0,sk_str_95);
}




/* FUN_0005ca20 @ 0x5ca20   (est. sk_errno_name)
 * Ghidra: undefined8 FUN_0005ca20(unsigned int arg1)
 * sk_errno_name: cL4 sk errno name operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

uint64_t sk_errno_name(unsigned int arg1)
{
  int t0;
  sk_code_t t3;
  long t1;
  long t2;
  int *t4;
  uint64_t *t5;
  uint64_t *t6;
  uint64_t t7;
  
  t2 = (unsigned long)arg1 * 0x50;
  if ((t2 + 0x64db60U < 0x64db60 || 0x64dca0 < t2 + 0x64dbb0U) ||
      t2 + 0x64dbb0U < t2 + 0x64db60U) goto LAB_0005cb14;
  t5 = *(uint64_t **)(t2 + 0x64dba0);
  if (t5 == (uint64_t *)0x0) {
    t1 = sk_error_status();
    if (t1 == 0) {
LAB_0005caa8:
      t5 = *(uint64_t **)(t2 + 0x64dba0);
      if (t5 == (uint64_t *)0x0) {
        return 0;
      }
    }
    else {
      if (arg1 == 2) {
        if ((*(uint8_t *)(t1 + 8) >> 1 & 1) == 0) goto LAB_0005caa8;
        t1 = sk_error_clear();
        t5 = (uint64_t *)(t1 + 0x20);
        t6 = (uint64_t *)(t1 + 0x28);
      }
      else {
        if ((arg1 != 1) || ((*(uint8_t *)(t1 + 8) & 1) == 0)) goto LAB_0005caa8;
        t1 = sk_error_clear();
        t5 = (uint64_t *)(t1 + 0x18);
        t6 = (uint64_t *)(t1 + 0x20);
      }
      if (t6 < t5) goto LAB_0005cb14;
      *(uint64_t **)(t2 + 0x64dba0) = t5;
      *(uint8_t *)(t2 + 0x64dba8) = 1;
    }
  }
  t7 = *t5;
  if (*(char *)(t2 + 0x64dba8) == '\x01') {
    t2 = sk_error_clear();
    t0 = *(int *)(t2 + 4);
    t4 = (int *)sk_error_clear();
    if (t0 != *t4) {
      sk_rt_unlock();
LAB_0005cb14:
                    
      t3 = (sk_code_t )sk_break(0x5519,0x5cb18);
      (*t3)();
    }
  }
  return t7;
}




/* FUN_0005cb18 @ 0x5cb18   (est. sk_set_cap_class)
 * Ghidra: void FUN_0005cb18(uint8_t arg1)
 * sk_set_cap_class: cL4 sk set cap class operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_set_cap_class(uint8_t arg1)
{
                    
  uRam000000000064db58 = arg1;
  return;
}




/* FUN_0005cb24 @ 0x5cb24   (est. sk_cap_record)
 * Ghidra: void FUN_0005cb24(undefined8 arg1,ulong arg2,uint8_t (*arg3) [16],ulong arg4)
 * sk_cap_record: cL4 sk cap record operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_cap_record(uint64_t arg1,unsigned long arg2,uint8_t (*arg3) [16],unsigned long arg4)
{
  unsigned long t0;
  unsigned long t1;
  uint8_t stk0 [16];
  uint64_t stk4;
  uint64_t stk9;
  uint64_t stk3;
  uint64_t stk8;
  uint64_t stk7;
  unsigned long stk2;
  unsigned long stk1;
  long lStack_48;
  uint64_t stk6;
  uint64_t stk5;
  
  lStack_48 = 0;
  stk1 = 0;
  stk5 = 0;
  stk6 = 0;
  stk8 = 0;
  stk3 = 0;
  stk2 = 0;
  stk7 = 0;
  stk9 = 0;
  stk4 = 0;
  sk_dispatch_record(arg1,&stk4);
  t0 = 0;
  if (stk2 != 0) {
    t0 = arg2 / stk2;
  }
  t1 = 0;
  if (stk1 != 0) {
    t1 = (lStack_48 * (arg2 - t0 * stk2)) / stk1;
  }
  stk0._8_8_ = t1;
  stk0._0_8_ = t0;
  if ((arg4 & 1) == 0) {
    stk0 = sk_macho_segcmd(t0,t1,stk4,stk9);
  }
  *arg3 = stk0;
  return;
}




/* FUN_0005cb9c @ 0x5cb9c   (est. sk_lock_prepare)
 * Ghidra: undefined8 FUN_0005cb9c(ulong *arg1)
 * sk_lock_prepare: cL4 sk lock prepare operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

uint64_t sk_lock_prepare(unsigned long *arg1)
{
  sk_code_t t0;
  unsigned long t1;
  unsigned long t2;
  
  t2 = *arg1;
  t1 = sk_current_thread();
  if (t1 + 0x178 < t1) {
                    
    t0 = (sk_code_t )sk_break(0x5519,0x5cc3c);
    (*t0)();
  }
  if ((((unsigned int)(t1 >> 0xe) ^ (unsigned int)t2) & 0xffffff) == 0) {
    if (*(short *)((long)arg1 + 0xe) != 0) {
      *(short *)((long)arg1 + 0xe) = *(short *)((long)arg1 + 0xe) + -1;
      *(short *)((long)arg1 + 0xc) = *(short *)((long)arg1 + 0xc) + 1;
      goto LAB_0005cc0c;
    }
  }
  else {
    do {
      if (t2 != 0) goto LAB_0005cc1c;
      t2 = *arg1;
    } while (t2 != 0);
    *arg1 = t1 >> 0xe & 0xffffff;
    if (*(short *)((long)arg1 + 0xc) == 0) {
LAB_0005cc0c:
      sk_error_fmt(t1,arg1,NULL);
      return 0;
    }
  }
LAB_0005cc1c:
  sk_lock_acquire_recursive(arg1,0);
  return 0;
}




/* FUN_0005cc3c @ 0x5cc3c   (est. sk_lock_acquire_recursive)
 * Ghidra: undefined8 FUN_0005cc3c(ulong *arg1,undefined8 arg2)
 * sk_lock_acquire_recursive: cL4 sk lock acquire recursive operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

uint64_t sk_lock_acquire_recursive(unsigned long *arg1,uint64_t arg2)
{
  unsigned long t3;
  unsigned int t4;
  sk_code_t t2;
  int t0;
  unsigned long t5;
  uint64_t t6;
  long t1;
  unsigned long t7;
  unsigned long t8;
  
  t4 = (unsigned int)arg1 >> 4 & 0xf;
  if ((uint8_t)arg1[1] != 0) {
    t4 = (uint8_t)arg1[1] - 1;
  }
  t5 = sk_current_thread();
  t6 = sk_cpu_array(t4 & 0xff);
  t7 = sk_global_057 >> 10;
  t1 = sk_current_thread();
  *(unsigned long *)(t1 + 0x78) = t7;
  t8 = t5 >> 0xe & 0xffffff;
  t7 = *arg1;
  if (t7 == 0) {
    *arg1 = t8;
  }
  if ((t7 != 0) && ((((unsigned int)t7 ^ (unsigned int)(t5 >> 0xe)) & 0xffffff) == 0)) {
    t6 = sk_current_thread();
                    
    sk_panic_msg(t6,sk_str_97);
  }
  if (t7 != 0) {
    t5 = 0;
    do {
      while (((unsigned int)t7 >> 0x18 & 1) == 0) {
        t3 = *arg1;
        if (t3 == t7) {
          *arg1 = t7 | 0x1000000;
          break;
        }
        t7 = t3;
        if ((t3 == 0) && (t7 = *arg1, t7 == 0)) {
          *arg1 = t5 | t8;
          goto LAB_0005ccc8;
        }
      }
      t7 = sk_phys_to_obj((unsigned int)t7 & 0xffffff);
      if (t7 + 0x178 < t7) {
                    
        t2 = (sk_code_t )sk_break(0x5519,0x5cdac);
        (*t2)();
      }
      t0 = sk_lock_dispatch_10(t4 & 0xff,arg1,t6,t7,arg2);
      if (t0 == 1) {
        t5 = 0;
      }
      else if (t0 == 2) {
        t5 = 0x1000000;
      }
      else if (t0 == 3) {
        return 0;
      }
      t6 = sk_cpu_array(t4 & 0xff);
      t7 = *arg1;
    } while (t7 != 0);
    *arg1 = t5 | t8;
  }
LAB_0005ccc8:
  t6 = sk_current_thread();
  sk_error_fmt(t6,arg1,NULL);
  return 1;
}




/* FUN_0005cdbc @ 0x5cdbc   (est. sk_lock_try)
 * Ghidra: undefined8 FUN_0005cdbc(ulong *arg1)
 * sk_lock_try: cL4 sk lock try operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

uint64_t sk_lock_try(unsigned long *arg1)
{
  sk_code_t t0;
  unsigned long t1;
  unsigned long t2;
  
  t2 = *arg1;
  t1 = sk_current_thread();
  if (t1 + 0x178 < t1) {
                    
    t0 = (sk_code_t )sk_break(0x5519,0x5ce54);
    (*t0)();
  }
  if ((((unsigned int)(t1 >> 0xe) ^ (unsigned int)t2) & 0xffffff) == 0) {
    if (*(short *)((long)arg1 + 0xe) != 0) {
      *(short *)((long)arg1 + 0xe) = *(short *)((long)arg1 + 0xe) + -1;
      *(short *)((long)arg1 + 0xc) = *(short *)((long)arg1 + 0xc) + 1;
      goto LAB_0005ce2c;
    }
  }
  else {
    do {
      if (t2 != 0) {
        return 0;
      }
      t2 = *arg1;
    } while (t2 != 0);
    *arg1 = t1 >> 0xe & 0xffffff;
    if (*(short *)((long)arg1 + 0xc) == 0) {
LAB_0005ce2c:
      sk_error_fmt(t1,arg1,NULL);
      return 1;
    }
  }
  return 0;
}




/* FUN_0005ce54 @ 0x5ce54   (est. sk_unlock)
 * Ghidra: void FUN_0005ce54(undefined8 *arg1)
 * sk_unlock: cL4 sk unlock operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_unlock(uint64_t *arg1)
{
  unsigned int t0;
  unsigned long t1;
  uint64_t t2;
  uint64_t in_xzr;
  
  t2 = *arg1;
  t1 = sk_current_thread();
  if ((((unsigned int)(t1 >> 0xe) ^ (unsigned int)t2) & 0xffffff) != 0) {
                    
    sk_panic_msg(0,sk_str_110);
  }
  t2 = sk_current_thread();
  sk_error_release(t2,arg1,NULL);
  if (*(short *)((long)arg1 + 0xc) == 0) {
    t2 = *arg1;
    *arg1 = in_xzr;
    sk_lo_release();
    if (((unsigned int)t2 >> 0x18 & 1) != 0) {
      t0 = (unsigned int)arg1 >> 4 & 0xf;
      if (*(uint8_t *)(arg1 + 1) != 0) {
        t0 = *(uint8_t *)(arg1 + 1) - 1;
      }
      sk_lock_dispatch_18(t0 & 0xff,arg1,3,0);
      return;
    }
  }
  else {
    *(short *)((long)arg1 + 0xc) = *(short *)((long)arg1 + 0xc) + -1;
    *(short *)((long)arg1 + 0xe) = *(short *)((long)arg1 + 0xe) + 1;
  }
  return;
}




/* FUN_0005cf08 @ 0x5cf08   (est. sk_lock_set_mode)
 * Ghidra: void FUN_0005cf08(undefined8 *arg1,uint16_t arg2)
 * sk_lock_set_mode: cL4 sk lock set mode operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_lock_set_mode(uint64_t *arg1,uint16_t arg2)
{
  *(uint16_t *)((long)arg1 + 0xe) = arg2;
  *arg1 = 0;
  return;
}




/* FUN_0005cf14 @ 0x5cf14   (est. sk_lock_init)
 * Ghidra: void FUN_0005cf14(void)
 * sk_lock_init: cL4 sk lock init operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_lock_init(void)
{
  return;
}




/* FUN_0005cf18 @ 0x5cf18   (est. sk_lock_record)
 * Ghidra: void FUN_0005cf18(long arg1,undefined8 arg2,undefined8 arg3)
 * sk_lock_record: cL4 sk lock record operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_lock_record(long arg1,uint64_t arg2,uint64_t arg3)
{
  uint64_t unaff_x29;
  uint64_t unaff_x30;
  
  *(uint64_t *)(arg1 + -0x10) = unaff_x29;
  *(uint64_t *)(arg1 + -8) = unaff_x30;
  *(BADSPACEBASE **)(arg1 + -0x20) = register0x00000008;
  sk_thread_switch(arg2,arg3);
  return;
}




/* FUN_0005cf4c @ 0x5cf4c   (est. sk_notify_domain)
 * Ghidra: void FUN_0005cf4c(long arg1,undefined8 arg2)
 * sk_notify_domain: cL4 sk notify domain operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_notify_domain(long arg1,uint64_t arg2)
{
  long *t1;
  long t0;
  
  if (((int)arg2 == 0) || ((sk_global_039 & 1) == 0)) {
    t0 = 2;
    t1 = &__shared_cache;
    do {
      if (*t1 == arg1) {
        sk_notify_domain_slot(t1,arg2);
      }
      t1 = t1 + 7;
      t0 = t0 + -1;
    } while (t0 != 0);
  }
  return;
}




/* FUN_0005d03c @ 0x5d03c   (est. sk_notify_domain_slot)
 * Ghidra: void FUN_0005d03c(long *arg1,ulong arg2)
 * sk_notify_domain_slot: cL4 sk notify domain slot operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_notify_domain_slot(long *arg1,unsigned long arg2)
{
  sk_code_t t0;
  unsigned long t1;
  unsigned long t2;
  unsigned long t3;
  
  t2 = arg1[3];
  if (t2 != 0) {
    t3 = 0;
    do {
      t1 = *(unsigned long *)(arg1[2] + t3 * 8);
      if (t1 != 0) {
        if (t1 + 0x38 < t1) {
                    
          t0 = (sk_code_t )sk_break(0x5519,0x5d130);
          (*t0)();
        }
        sk_notify_domain_slot(t1,arg2);
        t2 = arg1[3];
      }
      t3 = t3 + 1;
    } while (t3 < t2);
  }
  if ((arg2 & 1) == 0) {
    if ((arg1[4] != 1) && ((sk_code_t )arg1[1] != (sk_code_t )0x0)) {
      if (*arg1 == 0x706c6174) {
        (*(sk_code_t )arg1[1])();
      }
      else {
        sk_thread_create(0x40000,&sk_global_001,arg1);
      }
      arg1[4] = 1;
    }
  }
  else if ((arg1[5] != 1) && ((sk_code_t )arg1[6] != (sk_code_t )0x0)) {
    (*(sk_code_t )arg1[6])();
    arg1[5] = 1;
  }
  return;
}




/* FUN_0005d134 @ 0x5d134   (est. sk_cap_lookup_slot)
 * Ghidra: undefined8 FUN_0005d134(long arg1)
 * sk_cap_lookup_slot: cL4 sk cap lookup slot operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

uint64_t sk_cap_lookup_slot(long arg1)
{
  (**(sk_code_t *)(arg1 + 8))();
  return 0;
}




/* FUN_0005d154 @ 0x5d154   (est. sk_cap_resolve_name)
 * Ghidra: undefined8 FUN_0005d154(long arg1,long *arg2)
 * sk_cap_resolve_name: cL4 sk cap resolve name operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

uint64_t sk_cap_resolve_name(long arg1,long *arg2)
{
  sk_code_t t0;
  uint64_t t1;
  long stk0;
  
  if (arg1 == 0) {
    stk0 = 0;
    t1 = sk_ctx_irq(sk_str_59,&stk0);
  }
  else {
    t1 = *(uint64_t *)(arg1 + 0x20);
    stk0 = sk_memcmp(t1);
    if (stk0 < 0) {
                    
      t0 = (sk_code_t )sk_break(0x5519,0x5d184);
      (*t0)();
    }
  }
  *arg2 = stk0;
  return t1;
}




/* FUN_0005d38c @ 0x5d38c   (est. sk_lock_acquire)
 * Ghidra: ushort FUN_0005d38c(ulong *arg1,undefined8 arg2)
 * sk_lock_acquire: cL4 sk lock acquire operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

unsigned short sk_lock_acquire(unsigned long *arg1,uint64_t arg2)
{
  unsigned short t4;
  unsigned int t9;
  unsigned short t10;
  sk_code_t t3;
  bool t0;
  int t1;
  uint64_t t11;
  unsigned short t12;
  int t2;
  unsigned long t5;
  unsigned long t6;
  unsigned long t7;
  unsigned int t8;
  
  t9 = (unsigned int)arg1 >> 4 & 0xf;
  if ((uint8_t)arg1[1] != 0) {
    t9 = (uint8_t)arg1[1] - 1;
  }
  t11 = sk_cpu_array(t9 & 0xff);
  if (arg1 + 2 < arg1) {
                    
    t3 = (sk_code_t )sk_break(0x5519,0x5d38c);
    (*t3)();
  }
  t5 = *arg1;
  t8 = (int)(t5 >> 0x20) + 1;
  t2 = (int)t5;
  t7 = *arg1;
  if (*arg1 == t5) {
    *arg1 = t5 & 0xffff000000000000 | t5 & 0xffffffff | (unsigned long)(t8 & 0xffff) << 0x20;
    sk_unlock(arg2);
    t7 = t5;
  }
  else {
    do {
      t6 = t7;
      t8 = (int)(t6 >> 0x20) + 1;
      t7 = *arg1;
    } while (*arg1 != t6);
    *arg1 = t6 & 0xffff000000000000 | t6 & 0xffffffff | (unsigned long)(t8 & 0xffff) << 0x20;
    sk_unlock(arg2);
    t7 = t6;
    if ((int)t6 != t2) {
      t12 = 1;
      goto LAB_0005d2f0;
    }
  }
  t1 = sk_lock_dispatch_10(t9 & 0xff,arg1,t11,0,1);
  if (t1 == 3) {
    t12 = 0;
    t6 = t5;
  }
  else {
    do {
      t11 = sk_cpu_array(t9 & 0xff);
      t7 = *arg1;
      t0 = (int)t7 != t2;
      t12 = (unsigned short)t0;
      t6 = t7;
      if (t0) break;
      t1 = sk_lock_dispatch_10(t9 & 0xff,arg1,t11,0,1);
      t6 = t5;
    } while (t1 != 3);
    t8 = (unsigned int)(t7 >> 0x20);
  }
LAB_0005d2f0:
  t10 = (unsigned short)(t7 >> 0x30);
  t4 = 0;
  if (t12 <= t10) {
    t4 = t10 - t12;
  }
  t5 = *arg1;
  if (t5 == (t7 & 0xffff000000000000 | (unsigned long)(t8 & 0xffff) << 0x20 |
                t6 & 0xffffffff)) {
    *arg1 = (unsigned long)(t8 - 1 & 0xffff) << 0x20 | (unsigned long)t4 << 0x30 | t6 & 0xffffffff;
  }
  else {
    do {
      t10 = (unsigned short)(t5 >> 0x30);
      t4 = 0;
      if (t12 <= t10) {
        t4 = t10 - t12;
      }
      t7 = t5 + 0xffff00000000;
      t6 = t5 & 0xffffffff;
      t0 = *arg1 != t5;
      t5 = *arg1;
    } while (t0);
    *arg1 = t7 & 0xffff00000000 | (unsigned long)t4 << 0x30 | t6;
  }
  sk_lock_prepare(arg2);
  return t12;
}




/* FUN_0005d394 @ 0x5d394   (est. sk_lock_release)
 * Ghidra: void FUN_0005d394(ulong *arg1,int arg2)
 * sk_lock_release: cL4 sk lock release operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_lock_release(unsigned long *arg1,int arg2)
{
  bool t0;
  unsigned int t5;
  unsigned int t6;
  unsigned short t7;
  sk_code_t t2;
  unsigned int t8;
  uint32_t t9;
  int t1;
  unsigned long t10;
  unsigned long t3;
  unsigned long t4;
  
  t5 = (unsigned int)arg1 >> 4 & 0xf;
  if ((uint8_t)arg1[1] != 0) {
    t5 = (uint8_t)arg1[1] - 1;
  }
  if (arg1 + 2 < arg1) {
                    
    t2 = (sk_code_t )sk_break(0x5519,0x5d470);
    (*t2)();
  }
  t10 = *arg1;
  t8 = (unsigned int)(t10 >> 0x20);
  t7 = (unsigned short)(t10 >> 0x30);
  t6 = t8 & 0xffff;
  if (t7 + 1 < (t8 & 0xffff)) {
    t6 = t7 + 1;
  }
  t4 = t10 >> 0x20;
  if (arg2 == 0) {
    t4 = (unsigned long)t6;
  }
  t3 = *arg1;
  if (t3 == t10) {
    *arg1 = (unsigned long)((int)t10 + 1) | t4 << 0x30 | t10 & 0xffff00000000;
  }
  else {
    do {
      t8 = (unsigned int)(t3 >> 0x20);
      t7 = (unsigned short)(t3 >> 0x30);
      t1 = (int)t3;
      t6 = t8 & 0xffff;
      if (t7 + 1 < (t8 & 0xffff)) {
        t6 = t7 + 1;
      }
      t10 = t3 >> 0x20;
      if (arg2 == 0) {
        t10 = (unsigned long)t6;
      }
      t4 = t3 & 0xffff00000000;
      t0 = *arg1 != t3;
      t3 = *arg1;
    } while (t0);
    *arg1 = (unsigned long)(t1 + 1) | t10 << 0x30 | t4;
  }
  if ((unsigned int)t7 < (t8 & 0xffff)) {
    t9 = 6;
    if (arg2 == 0) {
      t9 = 4;
    }
    sk_lock_dispatch_18(t5 & 0xff,arg1,t9,0);
    return;
  }
  return;
}




/* FUN_0005d470 @ 0x5d470   (est. sk_register_cb2)
 * Ghidra: void FUN_0005d470(unsigned int *arg1,sk_code_t arg2,undefined8 arg3)
 * sk_register_cb2: cL4 sk register cb2 operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_register_cb2(unsigned int *arg1,sk_code_t arg2,uint64_t arg3)
{
  unsigned int t2;
  unsigned int t3;
  unsigned int t4;
  sk_code_t t1;
  unsigned int t5;
  unsigned long t6;
  long t0;
  uint64_t t7;
  unsigned long t8;
  
  if (*arg1 != 0xffffffff) {
    t3 = (unsigned int)arg1 >> 4 & 0xf;
    t6 = sk_current_thread();
    t8 = sk_global_057 >> 10;
    t0 = sk_current_thread();
    *(unsigned long *)(t0 + 0x78) = t8;
    t7 = sk_cpu_array(t3);
    t2 = (unsigned int)(t6 >> 0xc) & 0x3fffffc;
    t5 = *arg1;
    if (t5 == 0) {
      *arg1 = t2 | 1;
      (*arg2)(arg3);
      t5 = *arg1;
      *arg1 = 0xffffffff;
      sk_lo_release();
      if (t5 == (t2 | 3)) {
        sk_lock_dispatch_18(t3,arg1,6,0);
        return;
      }
    }
    else {
      t4 = t5 >> 2 & 0xffffff;
      t2 = t5;
      if (((t5 >> 2 & 0xffffff) << 2 | 1) == t5) {
        t7 = sk_cpu_array(t3);
        t2 = *arg1;
        if (t2 == t5) {
          *arg1 = t4 << 2 | 3;
          goto LAB_0005d584;
        }
      }
      while (t2 != 0xffffffff) {
LAB_0005d584:
        t6 = sk_phys_to_obj(t4);
        if (t6 + 0x178 < t6) {
                    
          t1 = (sk_code_t )sk_break(0x5519,0x5d5dc);
          (*t1)();
        }
        sk_lock_dispatch_10(t3,arg1,t7,t6,0);
        t2 = *arg1;
      }
    }
  }
  return;
}




/* FUN_0005d5dc @ 0x5d5dc   (est. sk_msg_init)
 * Ghidra: void FUN_0005d5dc(void)
 * sk_msg_init: cL4 sk msg init operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_msg_init(void)
{
  sk_register_global(0x64dca0);
  return;
}




/* FUN_0005d5e8 @ 0x5d5e8   (est. sk_msg_send2)
 * Ghidra: void FUN_0005d5e8(undefined8 arg1,unsigned int arg2,undefined8 arg3,undefined8 arg4)
 * sk_msg_send2: cL4 sk msg send2 operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_msg_send2(uint64_t arg1,unsigned int arg2,uint64_t arg3,uint64_t arg4)
{
  uint64_t stk1;
  uint64_t stk2;
  long stk0;
  
  stk0 = -0x2c8502b44bfffed6;
  stk1 = arg3;
  stk2 = arg4;
  sk_msg_send(arg1,(arg2 & 0xf) << 0xc | 8,&stk1,0);
  if (stk0 == -0x2c8502b44bfffed6) {
    return;
  }
                    
  sk_noreturn_error();
}




/* FUN_0005d64c @ 0x5d64c   (est. sk_msg_send)
 * Ghidra: void FUN_0005d64c(long arg1,uint16_t arg2,undefined8 *arg3,ulong arg4)
 * sk_msg_send: cL4 sk msg send operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_msg_send(long arg1,uint16_t arg2,uint64_t *arg3,unsigned long arg4)
{
  bool t0;
  long t1;
  unsigned long t3;
  uint64_t t4;
  char *t2;
  char stk9;
  uint16_t stk8;
  uint16_t stk7;
  uint16_t stk6;
  uint16_t stk5;
  uint64_t stk4;
  uint64_t stk10;
  uint64_t stk3;
  unsigned long stk2;
  uint8_t stk0 [32];
  long stk1;
  
  stk1 = -0x2c8502b44bfffed6;
  stk7 = 0;
  stk6 = 0;
  stk5 = 0;
  stk10 = arg3[1];
  stk4 = *arg3;
  stk3 = 0;
  stk2 = 0;
  stk8 = arg2;
  if ((arg4 & 1) == 0) {
    t0 = false;
    t2 = (char *)0x0;
  }
  else {
    t1 = sk_current_thread();
    t2 = &stk9;
    t0 = arg1 != t1;
    if (!t0) {
      t2 = (char *)0x0;
    }
  }
  stk2 = (unsigned long)t0;
  stk9 = '\0';
  t3 = sk_ipc_call_guard(sk_ipc_msg_frame,arg1,t2,&stk8);
  if ((t3 & 0xff) == 0) {
    t4 = 5;
    if (stk9 == '\0') {
      t4 = stk3;
    }
    if (stk1 == -0x2c8502b44bfffed6) {
      return;
    }
  }
  else {
    t4 = sk_rt_error(t3,stk0);
  }
                    
  sk_noreturn_error(t4);
}




/* FUN_0005d77c @ 0x5d77c   (est. sk_ipc_retrieve)
 * Ghidra: undefined8 FUN_0005d77c(void)
 * sk_ipc_retrieve: cL4 sk ipc retrieve operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

uint64_t sk_ipc_retrieve(void)
{
  sk_register_cb2(0x6b2680,sk_msg_push,&sk_global_049);
  return sk_global_108;
}




/* FUN_0005d7c8 @ 0x5d7c8   (est. sk_msg_push)
 * Ghidra: void FUN_0005d7c8(long *arg1)
 * sk_msg_push: cL4 sk msg push operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_msg_push(long *arg1)
{
  sk_code_t t2;
  char t0;
  long t1;
  uint8_t stk0 [16];
  
  t1 = sk_vspace_op2();
  if (arg1 + 1 < arg1) {
                    
    t2 = (sk_code_t )sk_break(0x5519,0x5d82c);
    (*t2)();
  }
  *arg1 = t1;
  if (t1 != 0) {
    stk0 = sk_vspace_get_ops();
    t0 = (**(sk_code_t *)(stk0._8_8_ + 0x48))(stk0._0_8_,*arg1);
    if (t0 == '\0') {
      return;
    }
                    
    sk_panic_msg(0,sk_str_113);
  }
                    
  sk_panic_msg(0,sk_str_69);
}




/* FUN_0005d84c @ 0x5d84c   (est. sk_msg_pop)
 * Ghidra: void FUN_0005d84c(void)
 * sk_msg_pop: cL4 sk msg pop operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_msg_pop(void)
{
  if (sk_global_109 == (uint64_t *)0x0) {
    sk_global_109 = (uint64_t *)0x65c560;
  }
                    
                    
  (*(sk_code_t )*sk_global_109)();
  return;
}




/* FUN_0005d870 @ 0x5d870   (est. sk_msg_print)
 * Ghidra: void FUN_0005d870(long arg1,int arg2)
 * sk_msg_print: cL4 sk msg print operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_msg_print(long arg1,int arg2)
{
  uint8_t *t4;
  uint8_t t0;
  long t2;
  unsigned long t5;
  char *t3;
  uint64_t t1;
  uint8_t stk0 [32];
  long stk1;
  
  stk1 = -0x2c8502b44bfffed6;
  if ((arg2 == 0) || ((*(uint8_t *)(arg1 + 0x48) >> 3 & 1) != 0)) {
    return;
  }
  t2 = sk_vspace_op2();
  if (t2 != 0) {
    t5 = sk_ctx_flag(arg1);
    t4 = (uint8_t *)sk_tpidrro;
    t4[5] = 0;
    t4[3] = 0;
    t4[2] = 0;
    t4[1] = 2;
    *t4 = 0;
    t4[4] = 0;
    t4[7] = 0;
    t4[6] = 0;
    sk_svc(3);
    if ((t5 & 0xff) != 0) {
      t0 = sk_rt_assert(t5,stk0,0x200);
      if (t0 < 10) {
        switch(t0) {
        default:
          t3 = sk_str_34;
          break;
        case 1:
          t3 = sk_str_28;
          break;
        case 2:
          t3 = sk_str_12;
          break;
        case 3:
          t3 = sk_str_37;
          break;
        case 4:
          t3 = sk_str_15;
          break;
        case 5:
          t3 = sk_str_31;
          break;
        case 6:
          t3 = sk_str_18;
          break;
        case 7:
          t3 = sk_str_09;
          break;
        case 8:
          t3 = sk_str_22;
          break;
        case 9:
          t3 = sk_str_25;
        }
        sk_memcpy2(t1,t3,0x20);
        return;
      }
      sk_memcpy2(t1,&sk_global_029,0x20);
      sk_timer(t1,0x20);
      return;
    }
    sk_rt_check(t4,t2,(uint8_t *)(arg1 + 0x48));
  }
  if (stk1 == -0x2c8502b44bfffed6) {
    sk_xrt_init(t2);
    return;
  }
                    
  sk_noreturn_error();
}




/* FUN_0005dab8 @ 0x5dab8   (est. sk_ipc_call_guard)
 * Ghidra: undefined8 FUN_0005dab8(sk_code_t arg1,ulong arg2,uint8_t *arg3,undefined8 arg4)
 * sk_ipc_call_guard: cL4 sk ipc call guard operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

uint64_t sk_ipc_call_guard(sk_code_t arg1,unsigned long arg2,uint8_t *arg3,uint64_t arg4)
{
  sk_code_t t1;
  unsigned long t2;
  uint64_t t3;
  unsigned long t4;
  long t0;
  
  t2 = sk_current_thread();
  if (arg2 == t2) {
    t4 = t2;
    if (t2 + 0x178 < arg2) {
                    
      t1 = (sk_code_t )sk_break(0x5519,0x5db7c);
      (*t1)();
    }
  }
  else {
    t4 = arg2;
    if (arg3 != (uint8_t *)0x0) {
      t0 = *(long *)(t2 + 0x70);
      t2 = sk_cpu_state_check(arg2,t0);
      if ((t2 & 1) == 0) {
        *arg3 = 1;
        return 0;
      }
      goto LAB_0005db2c;
    }
  }
  t0 = *(long *)(t4 + 0x28);
LAB_0005db2c:
  t3 = (*arg1)(t0,arg4);
  t2 = sk_current_thread();
  if ((arg3 != (uint8_t *)0x0) && (arg2 != t2)) {
    do {
      sk_svc(4);
    } while (t0 == 1);
  }
  return t3;
}




/* FUN_0005db7c @ 0x5db7c   (est. sk_msg_release)
 * Ghidra: void FUN_0005db7c(long arg1)
 * sk_msg_release: cL4 sk msg release operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_msg_release(long arg1)
{
  int t0;
  long t1;
  uint8_t stk2;
  uint64_t stk1;
  uint64_t stk3;
  long stk0;
  
  stk0 = -0x2c8502b44bfffed6;
  if ((*(uint8_t *)(arg1 + 0x48) >> 3 & 1) != 0) {
    t1 = sk_current_thread();
    stk2 = 0;
    if (arg1 == t1) {
      stk1 = 0;
      stk3 = 0;
      sk_msg_send(arg1,0xd,&stk1,1);
      *(unsigned long *)(arg1 + 0x48) = *(unsigned long *)(arg1 + 0x48) & 0xfffffffffffffff7;
    }
    else {
      do {
        t0 = sk_disable_preempt(&stk2);
      } while (t0 == 0);
      stk1 = 0;
      stk3 = 0;
      sk_msg_send(arg1,0xc,&stk1,1);
      *(unsigned long *)(arg1 + 0x48) = *(unsigned long *)(arg1 + 0x48) & 0xfffffffffffffff7;
      sk_enable_preempt(&stk2);
    }
  }
  if (stk0 == -0x2c8502b44bfffed6) {
    return;
  }
                    
  sk_noreturn_error();
}




/* FUN_0005dc48 @ 0x5dc48   (est. thunk_cap_word)
 * Ghidra: undefined8 thunk_FUN_00061638(long arg1)
 * thunk_cap_word: cL4 thunk cap word operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

uint64_t thunk_FUN_00061638(long arg1)
{
  uint8_t stk0 [8];
  uint64_t stk1;
  
  sk_ctx_type(stk0,*(uint64_t *)(arg1 + 0x28));
  return stk1;
}




/* FUN_0005dc4c @ 0x5dc4c   (est. sk_cpu_array)
 * Ghidra: undefined8 FUN_0005dc4c(ulong arg1)
 * sk_cpu_array: cL4 sk cpu array operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

uint64_t sk_cpu_array(unsigned long arg1)
{
  long t0;
  
  t0 = sk_global_get(0x6b2698,1,4);
  sk_dmb(2,3);
  return *(uint64_t *)(t0 + (arg1 & 0xffffffff) * 8);
}




/* FUN_0005dc8c @ 0x5dc8c   (est. sk_lock_dispatch_10)
 * Ghidra: void FUN_0005dc8c(void)
 * sk_lock_dispatch_10: cL4 sk lock dispatch 10 operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_lock_dispatch_10(void)
{
  if (sk_global_109 == 0) {
    sk_global_109 = 0x65c560;
  }
                    
                    
  (**(sk_code_t *)(sk_global_109 + 0x10))();
  return;
}




/* FUN_0005dcb0 @ 0x5dcb0   (est. sk_lock_release_recursive)
 * Ghidra: void FUN_0005dcb0(unsigned int arg1,undefined8 arg2,undefined8 arg3,long arg4,unsigned int arg5)
 * sk_lock_release_recursive: cL4 sk lock release recursive operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_lock_release_recursive(unsigned int arg1,uint64_t arg2,uint64_t arg3,long arg4,unsigned int arg5)
{
  unsigned long t1;
  unsigned long t2;
  char *t0;
  unsigned int t3;
  uint64_t stk1;
  uint64_t stk2;
  long stk0;
  
  stk0 = -0x2c8502b44bfffed6;
  t3 = 1;
  if (arg5 != 0) {
    t3 = 2;
  }
  stk1 = arg2;
  stk2 = arg3;
  if (arg4 == 0) {
    arg4 = sk_current_thread();
  }
  t2 = sk_msg_send(arg4,t3 | (arg1 & 0xf) << 0xc,&stk1,1);
  t1 = 0;
  if (t2 != 5) {
    t1 = t2;
  }
  if (t1 < 4) {
    if (((arg5 & 1) != 0) || (t1 != 3)) {
      if (stk0 == -0x2c8502b44bfffed6) {
        return;
      }
                    
      sk_noreturn_error();
    }
    t0 = sk_str_54;
  }
  else {
    t0 = sk_str_111;
  }
                    
  sk_panic_msg(0,t0);
}




/* FUN_0005dd70 @ 0x5dd70   (est. sk_lock_dispatch_18)
 * Ghidra: void FUN_0005dd70(void)
 * sk_lock_dispatch_18: cL4 sk lock dispatch 18 operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_lock_dispatch_18(void)
{
  if (sk_global_109 == 0) {
    sk_global_109 = 0x65c560;
  }
                    
                    
  (**(sk_code_t *)(sk_global_109 + 0x18))();
  return;
}




/* FUN_0005dd94 @ 0x5dd94   (est. sk_lock_release_recursive2)
 * Ghidra: void FUN_0005dd94(unsigned int arg1,undefined8 arg2,unsigned int arg3,ulong arg4)
 * sk_lock_release_recursive2: cL4 sk lock release recursive2 operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_lock_release_recursive2(unsigned int arg1,uint64_t arg2,unsigned int arg3,unsigned long arg4)
{
  long *t2;
  sk_code_t t1;
  unsigned long t3;
  long t0;
  uint64_t stk1;
  uint64_t stk2;
  long stk0;
  
  stk0 = -0x2c8502b44bfffed6;
  t3 = sk_current_thread();
  if ((int)arg3 < 5) {
    if (arg3 == 3) goto LAB_0005de28;
    if (arg3 != 4) {
LAB_0005de10:
                    
      sk_panic_msg(0,sk_str_94);
    }
    if (arg4 != 0) {
      arg3 = 4;
      t3 = arg4;
      goto LAB_0005de28;
    }
  }
  else if (arg3 != 5) {
    if (arg3 != 6) goto LAB_0005de10;
    goto LAB_0005de28;
  }
  arg3 = 5;
LAB_0005de28:
  t0 = sk_global_get(0x6b2698,1,4);
  t2 = (long *)(t0 + (unsigned long)arg1 * 8);
  *t2 = *t2 + 1;
  sk_lo_release();
  stk2 = *(uint64_t *)(t0 + (unsigned long)arg1 * 8);
  stk1 = arg2;
  if (t3 + 0x178 < t3) {
                    
    t1 = (sk_code_t )sk_break(0x5519,0x5deb0);
    (*t1)();
  }
  t0 = sk_msg_send(t3,(arg3 | arg1 << 0xc) & 0xffff,&stk1,0);
  if (stk0 == -0x2c8502b44bfffed6) {
    return;
  }
                    
  sk_noreturn_error(t0 != 5);
}




/* FUN_0005deb4 @ 0x5deb4   (est. sk_ipc_begin)
 * Ghidra: void FUN_0005deb4(void)
 * sk_ipc_begin: cL4 sk ipc begin operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_ipc_begin(void)
{
  if (sk_global_109 == 0) {
    sk_global_109 = 0x65c560;
  }
                    
                    
  (**(sk_code_t *)(sk_global_109 + 0x20))();
  return;
}




/* FUN_0005ded8 @ 0x5ded8   (est. sk_ipc_end)
 * Ghidra: void FUN_0005ded8(undefined8 arg1)
 * sk_ipc_end: cL4 sk ipc end operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_ipc_end(uint64_t arg1)
{
  uint64_t stk1;
  uint64_t stk2;
  long stk0;
  
  stk0 = -0x2c8502b44bfffed6;
  stk1 = 0;
  stk2 = 0;
  sk_msg_send(arg1,7,&stk1,1);
  if (stk0 == -0x2c8502b44bfffed6) {
    return;
  }
                    
  sk_noreturn_error();
}




/* FUN_0005df34 @ 0x5df34   (est. sk_ipc_set)
 * Ghidra: void FUN_0005df34(unsigned int arg1)
 * sk_ipc_set: cL4 sk ipc set operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_ipc_set(unsigned int arg1)
{
  uint64_t t0;
  uint64_t stk1;
  uint64_t stk2;
  long stk0;
  
  stk0 = -0x2c8502b44bfffed6;
  stk1 = 0;
  stk2 = 0;
  t0 = sk_current_thread();
  sk_msg_send(t0,(arg1 & 0xf) << 0xc | 0x11,&stk1,0);
  if (stk0 == -0x2c8502b44bfffed6) {
    return;
  }
                    
  sk_noreturn_error();
}




/* FUN_0005dfa8 @ 0x5dfa8   (est. sk_ipc_msg_frame)
 * Ghidra: sk_u128_t FUN_0005dfa8(ulong arg1, ushort *msg)
 * sk_ipc_msg_frame: cL4 sk ipc msg frame operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

sk_u128_t sk_ipc_msg_frame(unsigned long arg1, unsigned short *msg)
{
    unsigned short tag;
    uint64_t word2, word3;
    uint8_t *frame;

    tag = *msg;
    word2 = *(uint64_t *)(msg + 4);
    word3 = *(uint64_t *)(msg + 8);

    /* The SVC message frame (tpidrro) is the ABI for issuing a supervisor call:
     * write tag + two message words into the frame, then trap. */
    frame = (uint8_t *)sk_tpidrro;
    frame[4] = 0; frame[2] = 0; frame[5] = 0; frame[3] = 0;
    frame[6] = 0; frame[7] = 0;
    *frame = (char)tag;
    frame[1] = (uint8_t)(tag >> 8);
    frame[0xd] = (char)(word2 >> 0x28);
    frame[8]  = (char)word2;
    frame[0xb] = (char)(word2 >> 0x18);
    frame[10] = (char)(word2 >> 0x10);
    frame[9]  = (char)(word2 >> 8);
    frame[0xc] = (char)(word2 >> 0x20);
    frame[0xf] = (char)(word2 >> 0x38);
    frame[0xe] = (char)(word2 >> 0x30);
    frame[0x15] = (char)(word3 >> 0x28);
    frame[0x10] = (char)word3;
    frame[0x13] = (char)(word3 >> 0x18);
    frame[0x12] = (char)(word3 >> 0x10);
    frame[0x11] = (char)(word3 >> 8);
    frame[0x14] = (char)(word3 >> 0x20);
    frame[0x17] = (char)(word3 >> 0x38);
    frame[0x16] = (char)(word3 >> 0x30);

    sk_svc(0);

    /* Restore the caller's frame contents. */
    *frame = (char)tag;
    frame[7] = 0; frame[6] = 0; frame[5] = 0; frame[4] = 0;
    frame[3] = 0; frame[2] = 0; frame[1] = (uint8_t)(tag >> 8);

    /* Result: if the request tag matched a 8-byte message slot, return the
     * message payload word and the capability selector; else zero. */
    bool ok = ((msg[0x10] & arg1) == 8);
    unsigned long lo = ok ? (unsigned long)tag : 0;
    unsigned long hi = ok ? arg1 : 0;
    *(unsigned long *)(msg + 0xc) = lo;
    sk_u128_t r;
    r.lo = hi;
    r.hi = 0;
    return r;
}


/* FUN_0005e0dc @ 0x5e0dc   (est. sk_syscall_entry)
 * Ghidra: void FUN_0005e0dc(void)
 * sk_syscall_entry: cL4 sk syscall entry operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_syscall_entry(void)
{
  if (sk_global_109 == 0) {
    sk_global_109 = 0x65c560;
  }
                    
                    
  (**(sk_code_t *)(sk_global_109 + 8))();
  return;
}




/* FUN_0005e100 @ 0x5e100   (est. sk_syscall_handler)
 * Ghidra: void FUN_0005e100(ulong arg1,uint8_t *arg2)
 * sk_syscall_handler: cL4 sk syscall handler operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_syscall_handler(unsigned long arg1,uint8_t *arg2)
{
  unsigned int t3;
  uint64_t t7;
  uint64_t t8;
  unsigned short t9;
  uint8_t t0;
  uint64_t t10;
  char *t2;
  unsigned int t11;
  unsigned long t12;
  unsigned long t4;
  unsigned int t5;
  unsigned long t6;
  int t1;
  uint64_t stk3;
  uint64_t stk5;
  uint64_t stk2;
  uint64_t stk4;
  uint8_t stk0 [32];
  long stk1;
  
  stk1 = -0x2c8502b44bfffed6;
  t10 = sk_vspace_op2();
  t8 = uRam00000000004be038;
  t7 = sk_global_052;
  t1 = (int)arg2;
  if (t1 < 9) {
    if (t1 != 6) {
      if (t1 != 8) goto LAB_0005e490;
      arg2 = (uint8_t *)sk_tpidrro;
      stk5 = uRam00000000004be038;
      stk3 = sk_global_052;
      *arg2 = (char)sk_global_052;
      arg2[0xd] = (char)((unsigned long)t8 >> 0x28);
      arg2[8] = (char)t8;
      arg2[0xb] = (char)((unsigned long)t8 >> 0x18);
      arg2[10] = (char)((unsigned long)t8 >> 0x10);
      arg2[9] = (char)((unsigned long)t8 >> 8);
      arg2[5] = (char)((unsigned long)t7 >> 0x28);
      arg2[3] = (char)((unsigned long)t7 >> 0x18);
      arg2[2] = (char)((unsigned long)t7 >> 0x10);
      arg2[0xc] = (char)((unsigned long)t8 >> 0x20);
      arg2[1] = (char)((unsigned long)t7 >> 8);
      arg2[0xf] = (char)((unsigned long)t8 >> 0x38);
      arg2[0xe] = (char)((unsigned long)t8 >> 0x30);
      arg2[4] = (char)((unsigned long)t7 >> 0x20);
      arg2[7] = (char)((unsigned long)t7 >> 0x38);
      arg2[6] = (char)((unsigned long)t7 >> 0x30);
      arg2[0x15] = 0;
      arg2[0x11] = 0;
      arg2[0x10] = 0;
      arg2[0x13] = 0;
      arg2[0x12] = 0;
      arg2[0x14] = 0;
      arg2[0x17] = 0;
      arg2[0x16] = 0;
      sk_svc(3);
      if ((arg1 & 0xff) != 0) {
        sk_rt_list2(arg1,stk0,1);
        goto LAB_0005e22c;
      }
      goto LAB_0005e33c;
    }
  }
  else {
LAB_0005e22c:
    t8 = uRam00000000004bb1a8;
    t7 = sk_global_051;
    if ((int)arg2 == 9) {
      arg2 = (uint8_t *)sk_tpidrro;
      stk4 = uRam00000000004bb1a8;
      stk2 = sk_global_051;
      *arg2 = (char)sk_global_051;
      arg2[0xd] = (char)((unsigned long)t8 >> 0x28);
      arg2[8] = (char)t8;
      arg2[0xb] = (char)((unsigned long)t8 >> 0x18);
      arg2[10] = (char)((unsigned long)t8 >> 0x10);
      arg2[9] = (char)((unsigned long)t8 >> 8);
      arg2[5] = (char)((unsigned long)t7 >> 0x28);
      arg2[3] = (char)((unsigned long)t7 >> 0x18);
      arg2[2] = (char)((unsigned long)t7 >> 0x10);
      arg2[0xc] = (char)((unsigned long)t8 >> 0x20);
      arg2[1] = (char)((unsigned long)t7 >> 8);
      arg2[0xf] = (char)((unsigned long)t8 >> 0x38);
      arg2[0xe] = (char)((unsigned long)t8 >> 0x30);
      arg2[4] = (char)((unsigned long)t7 >> 0x20);
      arg2[7] = (char)((unsigned long)t7 >> 0x38);
      arg2[6] = (char)((unsigned long)t7 >> 0x30);
      arg2[0x15] = 0;
      arg2[0x11] = 0;
      arg2[0x10] = 0;
      arg2[0x13] = 0;
      arg2[0x12] = 0;
      arg2[0x14] = 0;
      arg2[0x17] = 0;
      arg2[0x16] = 0;
      sk_svc(3);
      if ((arg1 & 0xff) != 0) {
        t0 = sk_rt_list(arg1,stk0,1);
        if (9 < t0) {
          sk_memcpy2(&stk3,&sk_global_029,0x20);
          sk_timer(&stk3,0x20);
          return;
        }
        switch(t0) {
        default:
          t2 = sk_str_34;
          break;
        case 1:
          t2 = sk_str_28;
          break;
        case 2:
          t2 = sk_str_12;
          break;
        case 3:
          t2 = sk_str_37;
          break;
        case 4:
          t2 = sk_str_15;
          break;
        case 5:
          t2 = sk_str_31;
          break;
        case 6:
          t2 = sk_str_18;
          break;
        case 7:
          t2 = sk_str_09;
          break;
        case 8:
          t2 = sk_str_22;
          break;
        case 9:
          t2 = sk_str_25;
        }
        sk_memcpy2(&stk3,t2,0x20);
        return;
      }
LAB_0005e33c:
      arg2[0x1c0] = (char)t10;
      arg2[0x1c5] = (char)((unsigned long)t10 >> 0x28);
      arg2[0x1c3] = (char)((unsigned long)t10 >> 0x18);
      arg2[0x1c2] = (char)((unsigned long)t10 >> 0x10);
      arg2[0x1c1] = (char)((unsigned long)t10 >> 8);
      arg2[0x1c4] = (char)((unsigned long)t10 >> 0x20);
      arg2[0x1c7] = (char)((unsigned long)t10 >> 0x38);
      arg2[0x1c6] = (char)((unsigned long)t10 >> 0x30);
      t9 = sk_global_054;
      t12 = (unsigned long)sk_global_054;
      t4 = (unsigned long)sk_global_038;
      t6 = (unsigned long)sk_global_037;
      t3 = (unsigned int)(unsigned short)sk_str_20._0_2_;
      t11 = (unsigned int)(uint8_t)sk_str_20[2];
      t5 = (unsigned int)(uint8_t)sk_str_20[3];
      *arg2 = 0x40;
      arg2[1] = 0;
      arg2[4] = 0;
      arg2[5] = 0;
      arg2[2] = 3;
      arg2[3] = 0;
      arg2[6] = 0;
      arg2[7] = 0;
      sk_svc(0);
      *arg2 = 0x40;
      arg2[7] = 0;
      arg2[6] = 0;
      arg2[5] = 0;
      arg2[4] = 0;
      arg2[3] = 0;
      arg2[2] = 3;
      arg2[1] = 0;
      if ((t9 & 0xff) != 0) {
        sk_rt_dbg(t6 << 0x10 | t4 << 0x18 | t12 |
                     (unsigned long)(t11 << 0x10 | t5 << 0x18 | t3) << 0x20,stk0);
LAB_0005e490:
                    
        sk_panic_msg(0,sk_str_93);
      }
      if (stk1 == -0x2c8502b44bfffed6) {
        sk_xrt_init(t10,0);
        return;
      }
      goto LAB_0005e484;
    }
    if ((int)arg2 != 0xd) goto LAB_0005e490;
  }
  if (stk1 == -0x2c8502b44bfffed6) {
    return;
  }
LAB_0005e484:
                    
  sk_noreturn_error();
}




/* FUN_0005e4ac @ 0x5e4ac   (est. sk_syscall_exit)
 * Ghidra: void FUN_0005e4ac(uint8_t arg1)
 * sk_syscall_exit: cL4 sk syscall exit operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_syscall_exit(uint8_t arg1)
{
  char *t0;
  
  if (9 < arg1) {
    sk_memcpy2(NULL,&sk_global_029,0x20);
    sk_timer(NULL,0x20);
    return;
  }
  switch(arg1) {
  default:
    t0 = sk_str_34;
    break;
  case 1:
    t0 = sk_str_28;
    break;
  case 2:
    t0 = sk_str_12;
    break;
  case 3:
    t0 = sk_str_37;
    break;
  case 4:
    t0 = sk_str_15;
    break;
  case 5:
    t0 = sk_str_31;
    break;
  case 6:
    t0 = sk_str_18;
    break;
  case 7:
    t0 = sk_str_09;
    break;
  case 8:
    t0 = sk_str_22;
    break;
  case 9:
    t0 = sk_str_25;
  }
  sk_memcpy2(NULL,t0,0x20);
  return;
}




/* FUN_0005e4cc @ 0x5e4cc   (est. sk_syscall_restore)
 * Ghidra: void FUN_0005e4cc(void)
 * sk_syscall_restore: cL4 sk syscall restore operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_syscall_restore(void)
{
  uint8_t unaff_w20;
  
  if (9 < unaff_w20) {
    sk_memcpy2();
    sk_timer();
    return;
  }
  switch(unaff_w20) {
  default:
    break;
  case 1:
    break;
  case 2:
    break;
  case 3:
    break;
  case 4:
    break;
  case 5:
    break;
  case 6:
    break;
  case 7:
    break;
  case 8:
    break;
  case 9:
  }
  sk_memcpy2();
  return;
}




/* FUN_0005e4d8 @ 0x5e4d8   (est. sk_syscall_print)
 * Ghidra: void FUN_0005e4d8(long arg1,undefined8 arg2,undefined8 arg3,ulong arg4)
 * sk_syscall_print: cL4 sk syscall print operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_syscall_print(long arg1,uint64_t arg2,uint64_t arg3,unsigned long arg4)
{
  unsigned long t3;
  sk_code_t t2;
  bool t0;
  unsigned long t4;
  long t1;
  uint64_t stk0;
  uint64_t stk1;
  
  stk0 = arg2;
  stk1 = arg3;
  sk_buf_advance(&stk0,0,sk_str_67);
  if ((arg4 & 1) == 0) {
    sk_buf_advance(&stk0,1,sk_str_01);
    sk_buf_advance(&stk0,1,sk_str_02);
    sk_buf_advance(&stk0,1,sk_str_03);
    sk_syscall_name(*(uint32_t *)(arg1 + 0xd8));
    sk_syscall_name(*(uint32_t *)(arg1 + 0xe0));
    sk_syscall_name(*(uint32_t *)(arg1 + 0xdc));
    sk_syscall_name(*(uint32_t *)(arg1 + 0xe4));
    sk_buf_advance(&stk0,1,sk_str_107);
    sk_buf_advance(&stk0,1,sk_str_53);
    sk_buf_advance(&stk0,1,sk_str_51);
    sk_buf_advance(&stk0,1,sk_str_50);
    sk_buf_advance(&stk0,1,sk_str_49);
    sk_buf_advance(&stk0,1,sk_str_47);
    sk_buf_advance(&stk0,1,sk_str_48);
    sk_buf_advance(&stk0,1,sk_str_45);
    sk_buf_advance(&stk0,1,sk_str_52);
    sk_buf_advance(&stk0,1,sk_str_46);
    sk_buf_advance(&stk0,1,sk_str_41);
    t4 = arg1 + 0x160;
    t1 = -0xc;
    do {
      if (arg1 + 0x1b8U < t4) {
LAB_0005e8a0:
                    
        t2 = (sk_code_t )sk_break(0x5519,0x5e8a4);
        (*t2)();
      }
      t3 = arg1 + 0x158U + (*(unsigned long *)(t4 - 8) >> 0x30) * 0x10;
      if (2 < *(unsigned long *)(t4 - 8) >> 0x31 || t3 == 0) {
        return;
      }
      if ((((((t3 < arg1 + 0x158U || arg1 + 0x1b8U < t3 + 0x10) || t3 + 0x10 < t3)
            || (t3 + 1 < t3)) || (t3 + 2 < t3)) ||
          (((t3 + 3 < t3 || (t3 + 4 < t3)) ||
           ((t3 + 5 < t3 || ((t3 + 6 < t3 || (t3 + 7 < t3)))))))) ||
         ((t3 + 8 < t3 ||
          (((((t3 + 9 < t3 || (t3 + 10 < t3)) || (t3 + 0xb < t3)) ||
            ((t3 + 0xc < t3 || (t3 + 0xd < t3)))) ||
           ((t3 + 0xe < t3 || (t3 + 0xf < t3)))))))) goto LAB_0005e8a0;
      sk_buf_advance(&stk0,1,sk_str_66);
      t4 = t4 + 8;
      t0 = t1 != -1;
      t1 = t1 + 1;
    } while (t0);
  }
  return;
}




/* FUN_0005e8a4 @ 0x5e8a4   (est. sk_buf_advance)
 * Ghidra: void FUN_0005e8a4(ulong *arg1,ulong arg2,undefined8 arg3)
 * sk_buf_advance: cL4 sk buf advance operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_buf_advance(unsigned long *arg1,unsigned long arg2,uint64_t arg3)
{
  unsigned long t1;
  unsigned long t2;
  unsigned long t3;
  sk_code_t t0;
  unsigned int t4;
  unsigned long t5;
  uint8_t stk0;
  
  if (1 < arg1[1]) {
    if ((arg2 & 1) == 0) {
      t5 = arg1[1];
    }
    else {
      t4 = sk_snprintf(&stk0,1,arg3,NULL);
      if ((int)t4 < 0) {
        return;
      }
      t5 = arg1[1];
      if (t5 <= t4) {
        return;
      }
    }
    t4 = sk_snprintf(*arg1,t5,arg3,NULL);
    t5 = (unsigned long)(t4 & ((int)t4 >> 0x1f ^ 0xffffffffU));
    t2 = *arg1;
    t3 = arg1[1];
    if (t3 <= t5) {
      t5 = t3 - 1;
    }
    t1 = t2 + t5;
    if (t2 + t3 < t1 || t1 < t2) {
                    
      t0 = (sk_code_t )sk_break(0x5519,0x5e940);
      (*t0)();
    }
    *arg1 = t1;
    arg1[1] = t3 - t5;
  }
  return;
}




/* FUN_0005e958 @ 0x5e958   (est. sk_syscall_name)
 * Ghidra: undefined8 FUN_0005e958(uint32_t arg1)
 * sk_syscall_name: cL4 sk syscall name operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

uint64_t sk_syscall_name(uint32_t arg1)
{
  uint8_t *t3;
  uint8_t t0;
  sk_code_t t5;
  long t1;
  long t2;
  unsigned int t7;
  uint32_t *t6;
  uint8_t *t4;
  uint8_t bStack_11;
  uint32_t stk0;
  uint32_t stk2;
  uint64_t stk1;
  
  stk0 = arg1;
  stk2 = 0;
  t1 = 0;
  do {
    t0 = *(uint8_t *)((long)&stk0 + t1);
    if (t0 == 0) {
      if (t1 == 0) {
        t1 = 4;
        t2 = 4;
        t6 = &stk0;
        goto LAB_0005e9e8;
      }
      break;
    }
    t7 = (unsigned int)t0;
    if (((9 < t7 - 0x30 && 0x19 < (t0 & 0xffffffdf) - 0x41) &&
        (0x3c < t7 - 0x23 || (1L << ((unsigned long)(t7 - 0x23) & 0x3f) & 0x1000000000000587U) == 0))
       && (t7 != 0x7e)) {
      *(uint8_t *)((long)&stk0 + t1) = 0x3f;
    }
    t1 = t1 + 1;
  } while (t1 != 4);
  goto LAB_0005ea08;
  while( true ) {
    *(uint8_t *)t6 = 0x3f;
    t2 = t2 + -1;
    t6 = (uint32_t *)((long)t6 + 1);
    if (t2 == 0) break;
LAB_0005e9e8:
    if (((uint8_t *)((long)&stk2 + 1) <= t6) || (t6 < &stk0)) goto LAB_0005ea90;
  }
LAB_0005ea08:
  t4 = (uint8_t *)((long)&stk0 + t1);
  if ((t4 < (uint8_t *)((long)&stk2 + 1)) && (&stk0 <= t4)) {
    *t4 = 0;
    stk1 = 0;
    t4 = (uint8_t *)&stk1;
    while( true ) {
      t3 = &bStack_11 + t1;
      if ((((uint8_t *)((long)&stk2 + 1) <= t3) || (t3 < &stk0)) ||
         (((uint8_t *)((unsigned long)&stk1 | 5) <= t4 || (t4 < &stk1)))) break;
      *t4 = *t3;
      t1 = t1 + -1;
      t4 = t4 + 1;
      if (t1 == 0) {
        return stk1;
      }
    }
  }
LAB_0005ea90:
                    
  t5 = (sk_code_t )sk_break(0x5519,0x5ea94);
  (*t5)();
}




/* FUN_0005ea94 @ 0x5ea94   (est. sk_syscall_table_lookup)
 * Ghidra: long FUN_0005ea94(undefined8 arg1,ulong arg2,ulong arg3,unsigned int arg4)
 * sk_syscall_table_lookup: cL4 sk syscall table lookup operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

long sk_syscall_table_lookup(uint64_t arg1,unsigned long arg2,unsigned long arg3,unsigned int arg4)
{
  uint8_t *t2;
  uint8_t *t3;
  sk_code_t t0;
  char *t1;
  unsigned long t4;
  
  if (arg3 < 0x37) {
    t4 = arg3 * -8 + 0x1b8;
    if (arg2 + arg4 <= t4) {
      t3 = (uint8_t *)sk_tpidrro;
      if (arg2 <= t4) {
        t2 = t3 + arg3 * 8 + 8;
        sk_memcpy2(t2,arg1,arg2);
        if (t2 <= t2 + arg2) {
          if (arg4 != 0) {
            t2 = t2 + arg2;
            if ((t3 + 0x1c0 <= t2) || (t2 < t3)) goto LAB_0005eae4;
            *t2 = 0;
          }
          return arg3 + (arg2 + arg4 + 7 >> 3);
        }
      }
LAB_0005eae4:
                    
      t0 = (sk_code_t )sk_break(0x5519,0x5eae8);
      (*t0)();
    }
    t1 = sk_str_106;
  }
  else {
    t1 = sk_str_99;
  }
                    
  sk_panic_msg(0,t1);
}




/* FUN_0005eb78 @ 0x5eb78   (est. sk_syscall_table_lookup2)
 * Ghidra: long FUN_0005eb78(ulong arg1,ulong arg2,ulong arg3)
 * sk_syscall_table_lookup2: cL4 sk syscall table lookup2 operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

long sk_syscall_table_lookup2(unsigned long arg1,unsigned long arg2,unsigned long arg3)
{
  long t0;
  sk_code_t t1;
  char *t2;
  
  if (arg3 < 0x37) {
    if (arg2 <= arg3 * -8 + 0x1b8) {
      t0 = sk_tpidrro;
      sk_memcpy2(arg1,t0 + arg3 * 8 + 8,arg2);
      if (arg1 <= arg1 + arg2) {
        return arg3 + (arg2 + 7 >> 3);
      }
                    
      t1 = (sk_code_t )sk_break(0x5519,0x5ec20);
      (*t1)();
    }
    t2 = sk_str_106;
  }
  else {
    t2 = sk_str_99;
  }
                    
  sk_panic_msg(0,t2);
}




/* FUN_0005ec20 @ 0x5ec20   (est. sk_syscall_set_table)
 * Ghidra: void FUN_0005ec20(unsigned int arg1,undefined8 arg2)
 * sk_syscall_set_table: cL4 sk syscall set table operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_syscall_set_table(unsigned int arg1,uint64_t arg2)
{
  long t0;
  
  if (arg1 < 0x37) {
    t0 = sk_tpidrro;
    t0 = t0 + (unsigned long)arg1 * 8;
    *(char *)(t0 + 8) = (char)arg2;
    *(char *)(t0 + 0xd) = (char)((unsigned long)arg2 >> 0x28);
    *(char *)(t0 + 0xb) = (char)((unsigned long)arg2 >> 0x18);
    *(char *)(t0 + 10) = (char)((unsigned long)arg2 >> 0x10);
    *(char *)(t0 + 9) = (char)((unsigned long)arg2 >> 8);
    *(char *)(t0 + 0xc) = (char)((unsigned long)arg2 >> 0x20);
    *(char *)(t0 + 0xf) = (char)((unsigned long)arg2 >> 0x38);
    *(char *)(t0 + 0xe) = (char)((unsigned long)arg2 >> 0x30);
    return;
  }
                    
  sk_panic_msg(0,sk_str_104);
}




/* FUN_0005ec98 @ 0x5ec98   (est. sk_syscall_get_table)
 * Ghidra: ulong FUN_0005ec98(unsigned int arg1)
 * sk_syscall_get_table: cL4 sk syscall get table operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

unsigned long sk_syscall_get_table(unsigned int arg1)
{
  long t0;
  
  if (arg1 < 0x37) {
    t0 = sk_tpidrro;
    t0 = t0 + (unsigned long)arg1 * 8;
    return (unsigned long)*(uint8_t *)(t0 + 10) << 0x10 | (unsigned long)*(uint8_t *)(t0 + 0xb) << 0x18 |
           (unsigned long)*(unsigned short *)(t0 + 8) |
           (unsigned long)((unsigned int)*(uint8_t *)(t0 + 0xe) << 0x10 | (unsigned int)*(uint8_t *)(t0 + 0xf) << 0x18 |
                  (unsigned int)*(unsigned short *)(t0 + 0xc)) << 0x20;
  }
                    
  sk_panic_msg(0,sk_str_91);
}




/* FUN_0005ed18 @ 0x5ed18   (est. sk_syscall_set_handlers)
 * Ghidra: void FUN_0005ed18(unsigned int arg1,undefined8 arg2)
 * sk_syscall_set_handlers: cL4 sk syscall set handlers operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_syscall_set_handlers(unsigned int arg1,uint64_t arg2)
{
  long t0;
  long t1;
  sk_code_t t2;
  
  if (3 < arg1) {
                    
    sk_panic_msg(0,sk_str_105);
  }
  t1 = sk_tpidrro;
  t0 = t1 + (unsigned long)arg1 * 8;
  if ((uint8_t *)(t0 + 0x1c8U) <= (uint8_t *)(t1 + 0x1e0U) &&
      (uint8_t *)(t0 + 0x1c0U) <= (uint8_t *)(t0 + 0x1c8U)) {
    *(uint8_t *)(t0 + 0x1c0U) = (char)arg2;
    *(char *)(t0 + 0x1c5) = (char)((unsigned long)arg2 >> 0x28);
    *(char *)(t0 + 0x1c3) = (char)((unsigned long)arg2 >> 0x18);
    *(char *)(t0 + 0x1c2) = (char)((unsigned long)arg2 >> 0x10);
    *(char *)(t0 + 0x1c1) = (char)((unsigned long)arg2 >> 8);
    *(char *)(t0 + 0x1c4) = (char)((unsigned long)arg2 >> 0x20);
    *(char *)(t0 + 0x1c7) = (char)((unsigned long)arg2 >> 0x38);
    *(char *)(t0 + 0x1c6) = (char)((unsigned long)arg2 >> 0x30);
    return;
  }
                    
  t2 = (sk_code_t )sk_break(0x5519,0x5ed84);
  (*t2)();
}




/* FUN_0005edac @ 0x5edac   (est. sk_syscall_set_handlers2)
 * Ghidra: void FUN_0005edac(unsigned int arg1,undefined8 arg2)
 * sk_syscall_set_handlers2: cL4 sk syscall set handlers2 operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_syscall_set_handlers2(unsigned int arg1,uint64_t arg2)
{
  long t0;
  long t1;
  sk_code_t t2;
  
  if (3 < arg1) {
                    
    sk_panic_msg(0,sk_str_103);
  }
  t1 = sk_tpidrro;
  t0 = t1 + (unsigned long)arg1 * 8;
  if ((uint8_t *)(t0 + 0x1e8U) <= (uint8_t *)(t1 + 0x200U) &&
      (uint8_t *)(t0 + 0x1e0U) <= (uint8_t *)(t0 + 0x1e8U)) {
    *(uint8_t *)(t0 + 0x1e0U) = (char)arg2;
    *(char *)(t0 + 0x1e5) = (char)((unsigned long)arg2 >> 0x28);
    *(char *)(t0 + 0x1e3) = (char)((unsigned long)arg2 >> 0x18);
    *(char *)(t0 + 0x1e2) = (char)((unsigned long)arg2 >> 0x10);
    *(char *)(t0 + 0x1e1) = (char)((unsigned long)arg2 >> 8);
    *(char *)(t0 + 0x1e4) = (char)((unsigned long)arg2 >> 0x20);
    *(char *)(t0 + 0x1e7) = (char)((unsigned long)arg2 >> 0x38);
    *(char *)(t0 + 0x1e6) = (char)((unsigned long)arg2 >> 0x30);
    return;
  }
                    
  t2 = (sk_code_t )sk_break(0x5519,0x5ee18);
  (*t2)();
}




/* FUN_0005ee40 @ 0x5ee40   (est. sk_shift_0)
 * Ghidra: ulong FUN_0005ee40(ulong arg1)
 * sk_shift_0: cL4 sk shift 0 operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

unsigned long sk_shift_0(unsigned long arg1)
{
  return arg1 >> 6 & 7;
}




/* FUN_0005ee48 @ 0x5ee48   (est. sk_shift_1)
 * Ghidra: ulong FUN_0005ee48(ulong arg1)
 * sk_shift_1: cL4 sk shift 1 operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

unsigned long sk_shift_1(unsigned long arg1)
{
  return arg1 >> 0x10 & 0xffff;
}




/* FUN_0005ee50 @ 0x5ee50   (est. sk_shift_2)
 * Ghidra: ulong FUN_0005ee50(ulong arg1)
 * sk_shift_2: cL4 sk shift 2 operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

unsigned long sk_shift_2(unsigned long arg1)
{
  return arg1 & 0x3f;
}




/* FUN_0005ee58 @ 0x5ee58   (est. sk_shift_multi)
 * Ghidra: ulong FUN_0005ee58(ulong arg1,ulong arg2,unsigned int arg3,int arg4)
 * sk_shift_multi: cL4 sk shift multi operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

unsigned long sk_shift_multi(unsigned long arg1,unsigned long arg2,unsigned int arg3,int arg4)
{
  unsigned long t0;
  
  t0 = 0x1000;
  if (arg4 == 0) {
    t0 = 0;
  }
  return arg1 & 0x3f | (arg2 & 7) << 6 | (unsigned long)arg3 << 0x10 | t0;
}




/* FUN_0005ee7c @ 0x5ee7c   (est. sk_shift_dispatch)
 * Ghidra: void FUN_0005ee7c(void)
 * sk_shift_dispatch: cL4 sk shift dispatch operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_shift_dispatch(void)
{
  long t0;
  unsigned int t1;
  
  if ((sk_global_050 & 1) == 0) {
    t1 = sk_thread_unlock();
    if ((t1 & 1) == 0) {
      sk_ctx_trace();
    }
    t0 = sk_kernel_get();
    *(short *)(t0 + 0x38) = *(short *)(t0 + 0x38) + 1;
    sk_global_050 = 1;
  }
  return;
}




/* FUN_0005eec4 @ 0x5eec4   (est. sk_syscall_cap_dispatch)
 * Ghidra: void FUN_0005eec4(ulong *arg1,undefined8 arg2,ulong arg3,long arg4,int arg5)
 * sk_syscall_cap_dispatch: cL4 sk syscall cap dispatch operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_syscall_cap_dispatch(unsigned long *arg1,uint64_t arg2,unsigned long arg3,long arg4,int arg5)
{
  bool t0;
  uint32_t t19;
  unsigned short t24;
  unsigned int t27;
  uint8_t t28;
  uint8_t t29;
  uint8_t t30;
  uint8_t t31;
  uint8_t t32;
  uint8_t t14;
  uint8_t t15;
  unsigned int t16;
  uint8_t *t12;
  uint8_t t17;
  uint64_t t18;
  sk_code_t t9;
  char t2;
  char t3;
  uint8_t t1;
  int t5;
  long t6;
  unsigned long t20;
  uint64_t t21;
  unsigned long t22;
  long t7;
  long *t11;
  long t8;
  char *t10;
  unsigned int t23;
  uint64_t t4;
  unsigned int t25;
  unsigned int t26;
  unsigned short *t13;
  uint8_t in_wzr;
  uint8_t stk1 [16];
  unsigned long stk8;
  uint64_t stk7;
  uint64_t *stk6;
  uint8_t stk0 [32];
  uint64_t stk5;
  long stk4;
  long stk3;
  uint64_t stk9;
  long stk2;
  
  stk2 = -0x2c8502b44bfffed6;
  t6 = sk_kernel_get();
  t13 = (unsigned short *)(t6 + 0x38);
  t24 = *t13;
  *t13 = t24 + 1;
  if (t24 < 0x400) {
    t20 = sk_waitq_dequeue_all();
    if (t20 != 0) {
      sk_msg_release();
      goto LAB_0005ef44;
    }
    stk3 = 0x24000;
    stk9 = 0x200000000c;
    stk5 = 0x11;
    stk4 = 0;
    stk7 = 0;
    stk6 = (uint64_t *)0x0;
    t5 = sk_cnode_scan2();
    t19 = 0x40c8;
    if (t5 == 0) {
      t19 = 0x41140c8;
    }
    stk1 = sk_vspace_get_ops();
    t2 = (**(sk_code_t *)(stk1._8_8_ + 0x30))(stk1._0_8_,t19,&stk5,&stk7,0,0);
    t20 = sk_cnode_scan2();
    if (((t20 & 1) == 0) &&
       (t3 = (*(sk_code_t )stk6[10])(stk7,0,0x4000,0x20000), t3 != '\0')) {
LAB_0005f95c:
      t10 = sk_str_75;
LAB_0005f974:
                    
      sk_panic_msg(0,t10);
    }
    if (t2 != '\0') {
      sk_global_110 = sk_global_110 + 1;
      goto LAB_0005ef24;
    }
    if (stk6 == (uint64_t *)0x0) {
                    
      sk_tcb_abort();
    }
    (*(sk_code_t )stk6[1])(stk7,&stk5);
    t20 = sk_ctx_pop(stk4,stk3);
    if (t20 + 0x178 < t20) goto LAB_0005f584;
    t6 = sk_ctx_state(t20,0);
    t22 = (stk4 - t6) + stk3;
    if (0x1ffff < t22) {
      t10 = sk_str_77;
      goto LAB_0005f974;
    }
    stk8 = t22;
    t5 = sk_cnode_scan2();
    if (t5 != 0) {
      stk8 = 0x20000;
    }
    t2 = (*(sk_code_t )stk6[3])(stk7,&stk8);
    if (t2 == '\0') {
      sk_memcpy(t20,0,0x178);
      *(uint64_t *)(t20 + 0x30) = stk7;
      *(uint64_t **)(t20 + 0x38) = stk6;
      *(long *)(t20 + 0x138) = stk3;
      *(long *)(t20 + 0x130) = stk4;
      *(long *)(t20 + 0x140) = t6;
      *(long *)(t20 + 0x168) = stk4 + 0x4000;
      *(long *)(t20 + 0x170) = t6;
      t21 = sk_ctx_ip(t20);
      t6 = sk_vspace_op2();
      if (t6 == 0) {
        sk_global_112 = sk_global_112 + 1;
      }
      else {
        stk1 = sk_vspace_get_ops();
        t2 = (**(sk_code_t *)(stk1._8_8_ + 0x40))(stk1._0_8_,t21,1,t6);
        if (t2 == '\0') {
          t7 = sk_vspace_op2();
          *(long *)(t20 + 0x70) = t7;
          if (t7 == 0) {
            sk_global_114 = sk_global_114 + 1;
          }
          else {
            t22 = sk_macho_hdr(6);
            *(unsigned long *)(t20 + 0x28) = t22;
            if (t22 == 0) {
              sk_global_115 = sk_global_115 + 1;
            }
            else {
              t12 = (uint8_t *)sk_tpidrro;
              *t12 = (char)t6;
              t28 = (uint8_t)((unsigned long)t6 >> 8);
              t12[1] = t28;
              t31 = (uint8_t)((unsigned long)t6 >> 0x20);
              t12[4] = t31;
              t29 = (uint8_t)((unsigned long)t6 >> 0x28);
              t12[5] = t29;
              t32 = (uint8_t)((unsigned long)t6 >> 0x10);
              t12[2] = t32;
              t30 = (uint8_t)((unsigned long)t6 >> 0x18);
              t12[3] = t30;
              t14 = (uint8_t)((unsigned long)t6 >> 0x30);
              t12[6] = t14;
              t15 = (uint8_t)((unsigned long)t6 >> 0x38);
              t12[7] = t15;
              t12[0xd] = (char)((unsigned long)t21 >> 0x28);
              t12[8] = (char)t21;
              t12[0xb] = (char)((unsigned long)t21 >> 0x18);
              t12[10] = (char)((unsigned long)t21 >> 0x10);
              t12[9] = (char)((unsigned long)t21 >> 8);
              t12[0xc] = (char)((unsigned long)t21 >> 0x20);
              t12[0xf] = (char)((unsigned long)t21 >> 0x38);
              t12[0xe] = (char)((unsigned long)t21 >> 0x30);
              sk_svc(0);
              *t12 = (char)t6;
              t12[7] = t15;
              t12[6] = t14;
              t12[5] = t29;
              t12[4] = t31;
              t12[3] = t30;
              t12[2] = t32;
              t12[1] = t28;
              if ((t22 & 0xff) != 0) {
                t1 = sk_rt_proc(t22,stk0);
                if (t1 < 10) {
                  switch(t1) {
                  default:
                    t10 = sk_str_35;
                    break;
                  case 1:
                    t10 = sk_str_29;
                    break;
                  case 2:
                    t10 = sk_str_13;
                    break;
                  case 3:
                    t10 = sk_str_38;
                    break;
                  case 4:
                    t10 = sk_str_16;
                    break;
                  case 5:
                    t10 = sk_str_32;
                    break;
                  case 6:
                    t10 = sk_str_19;
                    break;
                  case 7:
                    t10 = sk_str_10;
                    break;
                  case 8:
                    t10 = sk_str_23;
                    break;
                  case 9:
                    t10 = sk_str_26;
                  }
                  sk_memcpy2(t4,t10,0x20);
                  return;
                }
                sk_memcpy2(t4,&sk_global_030,0x20);
                sk_timer(t4,0x20);
                return;
              }
              if (t22 == 0) {
                t7 = *(long *)(t20 + 0x28);
                t21 = sk_ipc_retrieve(0,0xb);
                *t12 = (char)t21;
                t28 = (uint8_t)((unsigned long)t21 >> 8);
                t12[1] = t28;
                t31 = (uint8_t)((unsigned long)t21 >> 0x20);
                t12[4] = t31;
                t29 = (uint8_t)((unsigned long)t21 >> 0x28);
                t12[5] = t29;
                t32 = (uint8_t)((unsigned long)t21 >> 0x10);
                t12[2] = t32;
                t30 = (uint8_t)((unsigned long)t21 >> 0x18);
                t12[3] = t30;
                t14 = (uint8_t)((unsigned long)t21 >> 0x30);
                t12[6] = t14;
                t15 = (uint8_t)((unsigned long)t21 >> 0x38);
                t12[7] = t15;
                sk_svc(0);
                *t12 = (char)t21;
                t12[7] = t15;
                t12[6] = t14;
                t12[5] = t29;
                t12[4] = t31;
                t12[3] = t30;
                t12[2] = t32;
                t12[1] = t28;
                if (t7 == 0) {
                  t22 = sk_ctx_stack(t20,9);
                  if ((t22 & 1) == 0) {
LAB_0005f938:
                    sk_rt_proc3();
                  }
                  else {
                    t7 = sk_thread_yield();
                    if (t7 == 0) {
LAB_0005ef44:
                      t21 = sk_thread_resume();
                      *(uint64_t *)(t20 + 0x120) = t21;
                      t25 = (unsigned int)t21 + (((unsigned int)t21 >> 3 & 0x1fff) / 0x7d) * -1000;
                      t23 = 0x54;
                      t26 = 1000;
                      do {
                        t27 = t26 / 10;
                        t16 = 0;
                        if (t27 != 0) {
                          t16 = (t25 & 0xffff) / t27;
                        }
                        t23 = t16 + 0x30 & 0xffff | t23 << 8;
                        t25 = t25 - t16 * t27;
                        t0 = 0x13 < t26;
                        t26 = t27;
                      } while (t0);
                      *(unsigned int *)(t20 + 0x118) = t23;
                      *(unsigned long *)(t20 + 0x128) = t20;
                      t22 = *(unsigned long *)(t20 + 0x28);
                      t12 = (uint8_t *)sk_tpidrro;
                      t28 = (uint8_t)t20;
                      *t12 = t28;
                      t32 = (uint8_t)(t20 >> 0x20);
                      t12[4] = t32;
                      t29 = (uint8_t)(t20 >> 8);
                      t12[1] = t29;
                      t14 = (uint8_t)(t20 >> 0x10);
                      t12[2] = t14;
                      t30 = (uint8_t)(t20 >> 0x28);
                      t12[5] = t30;
                      t15 = (uint8_t)(t20 >> 0x30);
                      t12[6] = t15;
                      t31 = (uint8_t)(t20 >> 0x18);
                      t12[3] = t31;
                      t17 = (uint8_t)(t20 >> 0x38);
                      t12[7] = t17;
                      sk_svc(0);
                      *t12 = t28;
                      t12[7] = t17;
                      t12[6] = t15;
                      t12[5] = t30;
                      t12[4] = t32;
                      t12[3] = t31;
                      t12[2] = t14;
                      t12[1] = t29;
                      if ((t22 & 0xff) != 0) {
                        sk_rt_proc5(t22,&stk5);
                        goto LAB_0005f95c;
                      }
                      *(uint64_t *)(t20 + 0x18) = arg2;
                      *(unsigned long *)(t20 + 0x20) = arg3;
                      *(uint64_t *)(t20 + 0x90) = 0;
                      *(uint64_t *)(t20 + 0x40) = 0;
                      *(uint64_t *)(t20 + 0x48) = 0;
                      *(uint64_t *)(t20 + 0x50) = 0;
                      *(uint64_t *)(t20 + 0x58) = 0;
                      *(uint8_t *)(t20 + 0x80) = in_wzr;
                      *(uint32_t *)(t20 + 0x84) = 0;
                      *(uint64_t *)(t20 + 0xa8) = 0;
                      *(uint64_t *)(t20 + 8) = 0;
                      *(uint64_t *)(t20 + 0x10) = 0;
                      if (t20 + 0x178 < t20) {
LAB_0005f584:
                    
                        t9 = (sk_code_t )sk_break(0x5519,0x5f588);
                        (*t9)();
                      }
                      t6 = sk_ctx_fp(t20,8);
                      t7 = sk_ctx_abort();
                      if (t7 == 0) {
                        t6 = 0;
                      }
                      else {
                        sk_ctx_abort2(t6);
                      }
                      t11 = (long *)sk_ctx_sp(t20);
                      sk_memcpy(t11,0,0x100);
                      t11[0x1f] = 0;
                      *t11 = t6;
                      t11[1] = t20;
                      t8 = sk_ctx_el();
                      t7 = sk_tpidr;
                      if (*(long *)(t8 + 0x208) == -1) {
                        sk_rt_proc7();
                      }
                      else if (*(long *)(t7 + 0xf8) == 0) {
                        t11[2] = *(long *)(t7 + 0x10);
                        if (t11 + 0x20 < t11) goto LAB_0005f584;
                        sk_ctx_exc(t11);
                        stk1 = sk_ctx_state(t20,arg4);
                        t21 = stk1._8_8_;
                        t22 = stk1._0_8_;
                        if ((*(long *)(t20 + 0x130) - t22) + *(long *)(t20 + 0x138) <
                            0x20000) {
                          if (arg4 != 0) {
                            if ((((arg3 + arg4 < arg3) || (t22 + arg4 < t22)) ||
                                (sk_memcpy2(t22,arg3,arg4), t22 + arg4 < t22))
                               || ((t22 != 0 && (t22 + arg4 <= t22))))
                            goto LAB_0005f584;
                            *(unsigned long *)(t20 + 0x20) = t22;
                          }
                          sk_ctx_push(t20,sk_rt_runflags);
                          t12[0x15] = t30;
                          t12[0x10] = t28;
                          t12[0x13] = t31;
                          t12[0x12] = t14;
                          t12[0x14] = t32;
                          t12[0x11] = t29;
                          t12[0x17] = t17;
                          t12[0x16] = t15;
                          sk_memset(t12 + 0x18,0x10);
                          t12[0x2d] = 0;
                          t12[0x28] = 0xbc;
                          t12[0x29] = 0xfa;
                          t12[0x2b] = 0;
                          t12[0x2a] = 5;
                          t12[0x2c] = 0;
                          t12[0x2f] = 0;
                          t12[0x2e] = 0;
                          t12[0x35] = stk1[5];
                          t12[0x30] = stk1[0];
                          t12[0x31] = stk1[1];
                          t12[0x33] = stk1[3];
                          t12[0x32] = stk1[2];
                          t12[0x34] = stk1[4];
                          t12[0x37] = stk1[7];
                          t12[0x36] = stk1[6];
                          t12[0x3d] = (char)((unsigned long)t11 >> 0x28);
                          t12[0x38] = (char)t11;
                          t12[0x39] = (char)((unsigned long)t11 >> 8);
                          t12[0x3b] = (char)((unsigned long)t11 >> 0x18);
                          t12[0x3a] = (char)((unsigned long)t11 >> 0x10);
                          t12[0x3c] = (char)((unsigned long)t11 >> 0x20);
                          t12[0x3f] = (char)((unsigned long)t11 >> 0x38);
                          t12[0x3e] = (char)((unsigned long)t11 >> 0x30);
                          t21 = sk_ctx_ip(t20);
                          t12[0x45] = (char)((unsigned long)t21 >> 0x28);
                          t12[0x40] = (char)t21;
                          t12[0x43] = (char)((unsigned long)t21 >> 0x18);
                          t12[0x42] = (char)((unsigned long)t21 >> 0x10);
                          t12[0x41] = (char)((unsigned long)t21 >> 8);
                          t12[0x44] = (char)((unsigned long)t21 >> 0x20);
                          t12[0x47] = (char)((unsigned long)t21 >> 0x38);
                          t12[0x46] = (char)((unsigned long)t21 >> 0x30);
                          t18 = uRam00000000004be1a8;
                          t21 = sk_global_053;
                          t6 = *(long *)(t20 + 0x28);
                          *t12 = (char)sk_global_053;
                          t12[8] = (char)t18;
                          t12[10] = (char)((unsigned long)t18 >> 0x10);
                          t12[0xb] = (char)((unsigned long)t18 >> 0x18);
                          t12[9] = (char)((unsigned long)t18 >> 8);
                          t12[0xd] = (char)((unsigned long)t18 >> 0x28);
                          t12[1] = (char)((unsigned long)t21 >> 8);
                          t12[0xc] = (char)((unsigned long)t18 >> 0x20);
                          t12[0xe] = (char)((unsigned long)t18 >> 0x30);
                          t12[0xf] = (char)((unsigned long)t18 >> 0x38);
                          t12[2] = (char)((unsigned long)t21 >> 0x10);
                          t12[3] = (char)((unsigned long)t21 >> 0x18);
                          t12[4] = (char)((unsigned long)t21 >> 0x20);
                          t12[5] = (char)((unsigned long)t21 >> 0x28);
                          t12[6] = (char)((unsigned long)t21 >> 0x30);
                          t12[7] = (char)((unsigned long)t21 >> 0x38);
                          t21 = 4;
                          sk_svc(0);
                          *t12 = 0;
                          t12[7] = 0;
                          t12[6] = 0;
                          t12[5] = 0;
                          t12[4] = 0;
                          t12[3] = 0;
                          t12[2] = 0;
                          t12[1] = 0;
                          if (t6 == 0) {
                            t5 = sk_thread_lock();
                            if ((arg5 != 0) && (t5 == 0)) {
                              sk_msg_pop(t20,1);
                            }
                            sk_waitq_enqueue(t20,0);
                            *arg1 = t20;
                            goto LAB_0005f4b4;
                          }
                        }
                        sk_rt_meta(t20,t21);
                        goto LAB_0005ef24;
                      }
                      sk_rt_proc6();
                      t13 = (unsigned short *)(t20 >> 0x38);
                      goto LAB_0005f938;
                    }
                    t8 = *(long *)(t20 + 0x28);
                    t12[1] = 0;
                    t12[4] = 0;
                    t12[5] = 0;
                    t12[2] = 0;
                    t12[3] = 0;
                    *t12 = 1;
                    t12[6] = 0;
                    t12[7] = 0;
                    t12[0xd] = (char)((unsigned long)t7 >> 0x28);
                    t12[8] = (char)t7;
                    t12[0xb] = (char)((unsigned long)t7 >> 0x18);
                    t12[10] = (char)((unsigned long)t7 >> 0x10);
                    t12[9] = (char)((unsigned long)t7 >> 8);
                    t12[0xc] = (char)((unsigned long)t7 >> 0x20);
                    t12[0xf] = (char)((unsigned long)t7 >> 0x38);
                    t12[0xe] = (char)((unsigned long)t7 >> 0x30);
                    sk_svc(0);
                    *t12 = 1;
                    t12[7] = 0;
                    t12[6] = 0;
                    t12[5] = 0;
                    t12[4] = 0;
                    t12[3] = 0;
                    t12[2] = 0;
                    t12[1] = 0;
                    if (t8 == 0) goto LAB_0005ef44;
                    sk_rt_proc2(t8,0x13);
                  }
                  sk_rt_proc4(t20);
                }
                else {
                  sk_global_116 = sk_global_116 + 1;
                }
              }
              sk_macho_loadcmds(*(uint64_t *)(t20 + 0x28),6);
            }
            sk_xrt_init(*(uint64_t *)(t20 + 0x70));
          }
        }
        else {
          sk_global_113 = sk_global_113 + 1;
        }
        sk_xrt_init(t6);
      }
    }
    else {
      sk_global_111 = sk_global_111 + 1;
    }
    (*(sk_code_t )*stk6)(stk7);
  }
LAB_0005ef24:
  *t13 = *t13 - 1;
LAB_0005f4b4:
  if (stk2 == -0x2c8502b44bfffed6) {
    return;
  }
                    
  sk_noreturn_error();
}




/* FUN_0005fac0 @ 0x5fac0   (est. sk_restore_ctx)
 * Ghidra: void FUN_0005fac0(long arg1)
 * sk_restore_ctx: cL4 sk restore ctx operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_restore_ctx(long arg1)
{
  int *t3;
  unsigned short *t4;
  unsigned short t5;
  int t0;
  unsigned int t6;
  sk_code_t t2;
  uint64_t t7;
  unsigned long t8;
  long t1;
  
  (**(sk_code_t *)(arg1 + 0x18))(*(uint64_t *)(arg1 + 0x20));
  t7 = sk_restore_ctx1();
  t8 = sk_current_thread();
  if (t8 <= t8 + 0x178) {
    sk_error_broadcast();
    sk_ctx_fault();
    *(uint64_t *)(t8 + 0x40) = t7;
    *(uint8_t *)(t8 + 0x80) = 1;
    t3 = (int *)(t8 + 0x84);
    t6 = (unsigned int)t3 >> 4 & 0xf;
    t7 = sk_cpu_array(t6);
    t0 = *(int *)(t8 + 0x84);
    while (t0 == 0) {
      sk_lock_dispatch_10(t6,t3,t7,0,0);
      t7 = sk_cpu_array(t6);
      t0 = *t3;
    }
    sk_lock_dispatch_18((unsigned int)(t8 + 0x80) >> 4 & 0xf,t8 + 0x80,5,0);
    if (t0 == 2) {
      sk_waitq_dequeue(t8);
      t1 = sk_kernel_get();
      t4 = (unsigned short *)(t1 + 0x38);
      t5 = *t4;
      *t4 = t5 - 1;
      sk_waitq_enqueue(CONCAT44((int)((unsigned long)t4 >> 0x20),(unsigned int)t5),t8,1);
    }
    sk_current_thread();
    sk_msg_release();
                    
    sk_panic_msg(0,sk_str_108);
  }
                    
  t2 = (sk_code_t )sk_break(0x5519,0x5fbc0);
  (*t2)();
}




/* FUN_0005fad8 @ 0x5fad8   (est. sk_restore_ctx1)
 * Ghidra: void FUN_0005fad8(undefined8 arg1)
 * sk_restore_ctx1: cL4 sk restore ctx1 operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_restore_ctx1(uint64_t arg1)
{
  int *t3;
  unsigned short *t4;
  unsigned short t5;
  int t0;
  unsigned int t6;
  sk_code_t t2;
  unsigned long t7;
  uint64_t t8;
  long t1;
  
  t7 = sk_current_thread();
  if (t7 <= t7 + 0x178) {
    sk_error_broadcast();
    sk_ctx_fault();
    *(uint64_t *)(t7 + 0x40) = arg1;
    *(uint8_t *)(t7 + 0x80) = 1;
    t3 = (int *)(t7 + 0x84);
    t6 = (unsigned int)t3 >> 4 & 0xf;
    t8 = sk_cpu_array(t6);
    t0 = *(int *)(t7 + 0x84);
    while (t0 == 0) {
      sk_lock_dispatch_10(t6,t3,t8,0,0);
      t8 = sk_cpu_array(t6);
      t0 = *t3;
    }
    sk_lock_dispatch_18((unsigned int)(t7 + 0x80) >> 4 & 0xf,t7 + 0x80,5,0);
    if (t0 == 2) {
      sk_waitq_dequeue(t7);
      t1 = sk_kernel_get();
      t4 = (unsigned short *)(t1 + 0x38);
      t5 = *t4;
      *t4 = t5 - 1;
      sk_waitq_enqueue(CONCAT44((int)((unsigned long)t4 >> 0x20),(unsigned int)t5),t7,1);
    }
    sk_current_thread();
    sk_msg_release();
                    
    sk_panic_msg(0,sk_str_108);
  }
                    
  t2 = (sk_code_t )sk_break(0x5519,0x5fbc0);
  (*t2)();
}




/* FUN_0005fbc0 @ 0x5fbc0   (est. sk_restore_ctx2)
 * Ghidra: void FUN_0005fbc0(long arg1)
 * sk_restore_ctx2: cL4 sk restore ctx2 operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_restore_ctx2(long arg1)
{
  *(uint32_t *)(arg1 + 0x84) = 2;
  sk_lock_dispatch_18((unsigned int)(arg1 + 0x84) >> 4 & 0xf,arg1 + 0x84,5,0);
  return;
}




/* FUN_0005fbdc @ 0x5fbdc   (est. sk_save_ctx)
 * Ghidra: void FUN_0005fbdc(undefined8 arg1,undefined8 arg2,long arg3)
 * sk_save_ctx: cL4 sk save ctx operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_save_ctx(uint64_t arg1,uint64_t arg2,long arg3)
{
  uint64_t t0;
  uint64_t t1;
  
  if (arg3 == 0) {
    t0 = 0;
  }
  else {
    t0 = sk_error_classify(2,arg3,0,1);
  }
  t1 = sk_error_classify(2,arg2,0,0);
  sk_msg_send2(arg1,2,t1,t0);
  return;
}




/* FUN_0005fc54 @ 0x5fc54   (est. sk_save_ctx2)
 * Ghidra: void FUN_0005fc54(undefined8 arg1,undefined8 *arg2,undefined8 arg3)
 * sk_save_ctx2: cL4 sk save ctx2 operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_save_ctx2(uint64_t arg1,uint64_t *arg2,uint64_t arg3)
{
  uint64_t t0;
  uint8_t stk0 [16];
  
  stk0._0_8_ = 0;
  stk0._8_8_ = 0;
  t0 = sk_error_to_word(2);
  sk_cap_record(2,t0,stk0,0);
  stk0 = sk_macho_segcmd(stk0._0_8_,stk0._8_8_,*arg2,arg2[1]);
  sk_save_ctx(arg1,stk0,arg3);
  return;
}




/* FUN_0005fccc @ 0x5fccc   (est. sk_restore_ctx3)
 * Ghidra: void FUN_0005fccc(long arg1)
 * sk_restore_ctx3: cL4 sk restore ctx3 operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_restore_ctx3(long arg1)
{
  char t0;
  uint64_t stk0;
  
  stk0 = 0x20000;
  t0 = (**(sk_code_t *)(*(long *)(arg1 + 0x38) + 0x18))(*(uint64_t *)(arg1 + 0x30),&stk0)
  ;
  if (t0 == '\0') {
    return;
  }
                    
  sk_panic_msg(0,sk_str_90);
}




/* FUN_0005fd24 @ 0x5fd24   (est. sk_restore_ctx4)
 * Ghidra: void FUN_0005fd24(long arg1)
 * sk_restore_ctx4: cL4 sk restore ctx4 operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_restore_ctx4(long arg1)
{
  char t0;
  uint64_t stk0;
  
  stk0 = 0xc000;
  t0 = (**(sk_code_t *)(*(long *)(arg1 + 0x38) + 0x18))
                    (*(uint64_t *)(arg1 + 0x30),&stk0);
  if (t0 == '\0') {
    return;
  }
                    
  sk_panic_msg(0,sk_str_90);
}




/* FUN_0005fd2c @ 0x5fd2c   (est. sk_current_cpu)
 * Ghidra: undefined8 FUN_0005fd2c(ulong arg1)
 * sk_current_cpu: cL4 sk current cpu operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

uint64_t sk_current_cpu(unsigned long arg1)
{
  sk_code_t t1;
  long t0;
  
  t0 = sk_current_thread();
  if ((*(uint8_t **)(t0 + 0x168) <= NULL) &&
     (NULL < *(uint8_t **)(t0 + 0x170))) {
    if (arg1 <= (unsigned long)((long)NULL - (long)*(uint8_t **)(t0 + 0x168)))
    {
      return 1;
    }
                    
    sk_xrt_abort(sk_str_101);
  }
                    
  t1 = (sk_code_t )sk_break(1,0x5fd90);
  (*t1)();
}




/* FUN_0005fdac @ 0x5fdac   (est. sk_cpu_state_check)
 * Ghidra: long FUN_0005fdac(long arg1,undefined8 arg2)
 * sk_cpu_state_check: cL4 sk cpu state check operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

long sk_cpu_state_check(long arg1,uint64_t arg2)
{
  long t3;
  char t0;
  unsigned long t1;
  unsigned long t2;
  unsigned long t4;
  uint8_t stk2;
  uint8_t stk0 [32];
  long stk1;
  
  stk1 = -0x2c8502b44bfffed6;
  stk2 = 0;
  t3 = sk_disable_preempt(&stk2);
  if ((int)t3 == 0) {
LAB_0005fe0c:
    if (stk1 == -0x2c8502b44bfffed6) {
      return t3;
    }
                    
    sk_noreturn_error();
  }
  sk_svc(2);
  if ((*(unsigned long *)(arg1 + 0x28) & 0xff) == 0) {
    sk_enable_preempt(&stk2,arg2);
    goto LAB_0005fe0c;
  }
  sk_rt_proc8(*(unsigned long *)(arg1 + 0x28),stk0);
  t3 = sk_current_thread();
  t0 = *(char *)(t3 + 0x69);
  t4 = t1;
  if (t0 != '\0') {
    if (t0 != -1) goto LAB_0005fe84;
    t3 = sk_rt_proc9();
    t4 = t2;
  }
  if ((t4 & 1) != 0) {
                    
    sk_xrt_abort(sk_str_82);
  }
  t0 = *(char *)(t3 + 0x69);
LAB_0005fe84:
  *(char *)(t3 + 0x69) = t0 + '\x01';
  return t3;
}




/* FUN_0005fe48 @ 0x5fe48   (est. sk_state_enter)
 * Ghidra: void FUN_0005fe48(void)
 * sk_state_enter: cL4 sk state enter operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_state_enter(void)
{
  long t3;
  char t0;
  unsigned long t1;
  unsigned long t2;
  unsigned long t4;
  
  t3 = sk_current_thread();
  t0 = *(char *)(t3 + 0x69);
  t4 = t1;
  if (t0 != '\0') {
    if (t0 != -1) goto LAB_0005fe84;
    t3 = sk_rt_proc9();
    t4 = t2;
  }
  if ((t4 & 1) != 0) {
                    
    sk_xrt_abort(sk_str_82);
  }
  t0 = *(char *)(t3 + 0x69);
LAB_0005fe84:
  *(char *)(t3 + 0x69) = t0 + '\x01';
  return;
}




/* FUN_0005fea8 @ 0x5fea8   (est. sk_state_exit)
 * Ghidra: void FUN_0005fea8(void)
 * sk_state_exit: cL4 sk state exit operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_state_exit(void)
{
  char t0;
  long t2;
  unsigned long t1;
  
  t2 = sk_current_thread();
  t0 = *(char *)(t2 + 0x69);
  if (t0 == '\0') {
    sk_rt_proc10();
  }
  else {
    *(char *)(t2 + 0x69) = t0 + -1;
    if ((t0 != '\x01') || ((t1 & 1) != 0)) {
      return;
    }
  }
                    
  sk_xrt_abort(sk_str_81);
}




/* FUN_0005ff04 @ 0x5ff04   (est. sk_alloc_frame)
 * Ghidra: void FUN_0005ff04(undefined8 *arg1,ulong arg2,unsigned int arg3)
 * sk_alloc_frame: cL4 sk alloc frame operation.
 * Confidence: medium
 * Notes: name estimated from call-graph role and string usage;
 *   Ghidra identifiers renamed to English in body.
 */

void sk_alloc_frame(uint64_t *arg1,unsigned long arg2,unsigned int arg3)
{
  long t1;
  sk_code_t t3;
  int t0;
  unsigned long t4;
  long t2;
  unsigned int t5;
  uint8_t stk0 [16];
  unsigned long stk7;
  uint64_t stk6;
  long lStack_68;
  uint8_t stk5 [8];
  long stk4;
  long stk3;
  uint32_t stk2;
  uint32_t stk1;
  
  t1 = arg2 + 0x4000;
  if (arg2 < 0xffffffffffffc000) {
    stk5[0] = 0x11;
    sk_memset((unsigned long)stk5 | 1,0xf);
    stk2 = 0xc;
    stk1 = 0x20;
    t5 = arg3 & 0xf;
    if ((arg3 & 0xe) == 0) {
      t5 = 1;
    }
    stk3 = t1;
    if ((t5 & t5 - 1) == 0) {
      t5 = 0x40c8;
      if ((arg3 & 2) != 0) {
        t5 = 0x44c8;
      }
      stk6 = 0;
      lStack_68 = 0;
      stk0 = sk_vspace_get_ops();
      t4 = (**(sk_code_t *)(stk0._8_8_ + 0x30))
                        (stk0._0_8_,(arg3 & 4) << 0xb | (arg3 >> 3 & 1) << 9 | t5,
                         stk5,&stk6,0,stk5);
      t4 = t4 & 0xff;
      if (t4 == 0) {
        stk7 = arg2;
        t4 = (**(sk_code_t *)(lStack_68 + 0x18))(stk6,&stk7);
        t4 = t4 & 0xff;
        if (t4 == 0) {
          t2 = sk_kernel_get();
          t0 = *(int *)(t2 + 0x88);
          *(int *)(t2 + 0x88) = t0 + 1;
          if (t0 != -1) {
            *arg1 = stk6;
            arg1[1] = lStack_68;
            *(unsigned int *)(arg1 + 2) = arg3 & 0xffffffdf | (unsigned int)((arg3 & 0xf) == 0);
            *(uint32_t *)((long)arg1 + 0x14) = 0;
            arg1[3] = stk4;
            arg1[4] = stk4 + t1;
            arg1[5] = t1;
            *(int *)(arg1 + 6) = t0 + 1;
            *(uint32_t *)((long)arg1 + 0x34) = 0;
            return;
          }
          sk_rt_proc11();
        }
        else if (((uint64_t *)0x64cb3f < &sk_global_034 + t4 &&
                 &sk_global_035 + t4 < (uint64_t *)0x64cb81) &&
                 &sk_global_034 + t4 <= &sk_global_035 + t4) {
                    
          sk_xrt_abort(sk_str_89);
        }
      }
      else if ((((uint64_t *)0x64cb3f < &sk_global_034 + t4) &&
               (&sk_global_035 + t4 < (uint64_t *)0x64cb81)) &&
              (&sk_global_034 + t4 <= &sk_global_035 + t4)) {
                    
        sk_xrt_abort(sk_str_88);
      }
                    
      t3 = (sk_code_t )sk_break(0x5519,0x600f0);
      (*t3)();
    }
  }
  else {
    sk_rt_proc12();
  }
                    
  sk_xrt_abort(sk_str_96);
}



