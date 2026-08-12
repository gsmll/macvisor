/* Recreated from cl4_kernel.raw (cL4 microkernel, arm64e, image base 0).
 * Ground truth: Ghidra FUN_ names + addresses. Names use cL4/seL4 vocabulary; estimates unless matched.
 *
 * Slice R49: 0x0065d804-0x00663ac8 (120 functions). The cL4 clock / timer /
 * scheduling-dispatch subsystem. Key pieces:
 *   - The per-cpu timer-table clock source (FUN_0065d804/0065d90c/0065da08/
 *     0065db0c: nanosecond conversion against the 0x6b5250 timer-table stride-0x50
 *     entries; global flag DAT_006b5248 selects a fast read path).
 *   - The thread-notification wait/signal machinery (FUN_0065e370/0065e378/
 *     0065e454) driving the indirect dispatch table behind _DAT_006fe760
 *     (FUN_0065ec08/0065ecec/0065ee30/0065e7cc/0065f058).
 *   - The message-register / IPC get/put helpers over the tpidrro_el0 context
 *     (FUN_0065fa24/0065fb08/0065fbb0/0065fc28/0065fca8) and the 128-byte
 *     CallSupervisor(0)-based message send/receive frames (FUN_0065ef24,
 *     006623d0, 00662754).
 *   - The TCB / message-slot allocator built on the _DAT_006fe7e0 free block
 *     (FUN_00661488/0066204c/00662158/006621f4/00662264/006622d8) and the
 *     big thread-spawn path FUN_0065fdb8.
 *   - The boot log/panic-format helpers (FUN_0065f468/0065f834/0065f8e8 and the
 *     error-code string mappers 0065f428/006612c0/00662a40).
 *
 * Many helpers were disassembled with only register artifacts (unaff_w20, the
 * x8 return slot, in_wzr) because they are the read-before-Supervisor call
 * frame builders; signatures are reconstructed best-effort and marked
 * low/medium. The trap/panic helpers (FUN_0065c2f0, FUN_0067f660, FUN_006833d4)
 * are noreturn. CallSupervisor(n)/SoftwareBreakpoint(code,addr) are opaque.
 *
 * Confidence: medium-low (clock/timer/notification glue; names inferred from
 * cL4 vocabulary and string constants; no header matches in this slice). */
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include "sk_internal.h"

/* 128-bit word-pair used by the 16-byte-return runtime helpers. */
typedef struct sk_u128 { word_t lo; word_t hi; } sk_u128_t;

/* ---- shared runtime helpers referenced by this slice (all defined elsewhere
 * in the cL4 tree; FUN_ address preserved in the trailing comment) ---- */
extern void   sk_memmove(void *dst, const void *src, unsigned long n);   /* FUN_0067aa00 */
extern void   sk_memzero(void *dst, unsigned long n);                    /* FUN_0067a780 */
extern __attribute__((noreturn)) void sk_panic_2(unsigned long a, unsigned long b); /* FUN_0065c2f0 */
extern __attribute__((noreturn)) void sk_fatal(unsigned long code, ...); /* FUN_0067f660 */
extern __attribute__((noreturn)) void sk_fatal_code(unsigned long msg);  /* FUN_006833d4 */
extern void   sk_fatal_6a612a(unsigned long msg);                        /* FUN_0067b280 noreturn */
extern void   sk_ret_ctx_restore(unsigned long a, unsigned long b);      /* FUN_0065c310 noreturn */
extern unsigned long sk_percpu_ptr(unsigned long a);                     /* FUN_00655848: per-cpu base */
extern unsigned long sk_percpu_108(void);                                       /* FUN_0065be80: read +0x108 */
extern unsigned long sk_percpu_40(void);                                        /* FUN_0065be40 */
extern unsigned long sk_bucket_lookup(unsigned long *inout, int which);  /* FUN_0065cda8 */
extern unsigned long sk_bucket_base(void);                               /* FUN_0065ccc8: timer/clock base */
extern unsigned long sk_clock_reg_read(unsigned long idx);               /* FUN_0065ebc8 */
extern int    sk_clock_reg_inc(unsigned long idx, unsigned long *w,
                               unsigned long a, unsigned long b,
                               unsigned long c);                         /* FUN_0065ec08 indirect */
extern void   sk_clock_dispatch_18(unsigned long a, void *b,
                                   unsigned long c, unsigned long d);    /* FUN_0065ecec */
extern void   sk_clock_dispatch_20(void);                                /* FUN_0065ee30 */
extern void   sk_clock_dispatch_00(void);                                /* FUN_0065e7cc */
extern void   sk_clock_dispatch_08(void);                                /* FUN_0065f058 */

/* out-of-slice cL4 helpers referenced by this slice */
extern unsigned long sk_rt_00656c28(void);      /* raw clock tick read */
extern unsigned long sk_rt_00656c04(void);      /* per-cpu counter read */
extern unsigned long sk_rt_0065be40(void);      /* per-cpu field read */
extern unsigned long sk_rt_0065be08(unsigned long a, unsigned long b,
                                    unsigned long c);   /* global/table base */
extern void   sk_rt_0065c144(unsigned long t, unsigned long *w, void *s); /* timer enqueue */
extern void   sk_rt_0065c1b8(unsigned long t, unsigned long *w, void *s); /* timer dequeue */
extern void   sk_rt_0065c984(unsigned long a, unsigned long b,
                             unsigned long c, unsigned long m);          /* panic/err log */
extern void   sk_rt_0065cbbc(unsigned long base);                         /* timer-slot reset */
extern void   sk_rt_0065cfe4(unsigned long t, unsigned long v);          /* tcb state set */
extern void   sk_rt_0065d080(unsigned long t);                           /* tcb teardown */
extern void   sk_rt_00663d3c(unsigned long t, unsigned long v);          /* tcb release */
extern unsigned long sk_rt_006661e0(unsigned long a, long *b);           /* clock handle */
extern sk_u128_t sk_rt_0066a8c4(void);                                   /* allocator table */
extern unsigned long sk_rt_0066ad54(void);                               /* allocator node */
extern long    sk_rt_0067b220(unsigned long x);                          /* string validate */
extern void   sk_rt_00683338(unsigned long a, unsigned long b,
                             unsigned long c, unsigned long d,
                             unsigned char *out);                        /* round-up helper */
extern void   sk_rt_00684860(void);                                      /* timer mis-validate */
extern unsigned char sk_rt_00684940(unsigned long e, unsigned char *b,
                                    unsigned long n);                    /* err decode */
extern void   sk_rt_0068498c(unsigned char *f, unsigned long a,
                             unsigned char *b);                          /* frame finish */
extern void   sk_rt_006860f4(unsigned long obj, ...);                    /* object free */
extern void   sk_rt_0064effc(void *dst, unsigned long n);                /* err-string copy */

/* globals used by this slice */
extern unsigned long _DAT_006b5ed0;    /* stack canary / frame marker */
extern unsigned long _DAT_006fe760;    /* clock dispatch table ptr */
extern unsigned long _DAT_006ff0a8;    /* global preemption/clock counter */
extern unsigned long _DAT_006fe7e0;    /* slot/free-block base */
extern unsigned long _DAT_006fe7a0;    /* thread-stack pool base */
extern unsigned long _DAT_006b5248;    /* clock fast-path flag */
extern unsigned long _DAT_006fe770;    /* clock init flag */
extern unsigned long _DAT_006fe798;    /* flag byte */
extern unsigned long _DAT_006fe799;    /* flag byte */
extern unsigned long _DAT_006b53b0;    /* flag byte */
extern unsigned long _DAT_006fe750;    /* notif slot */
extern unsigned long _DAT_006fe758;    /* notif result */
extern unsigned long _DAT_006b6518;    /* dispatch table backing */
extern unsigned long _DAT_006b71e8;    /* notif-walk table */
extern unsigned long _DAT_006fec90;    /* walk-enable flag */
extern unsigned long _DAT_00689af0;    /* boot tag word lo */
extern unsigned long _DAT_00689ae0;    /* boot tag word lo */
extern unsigned long uRam0000000000689af8;  /* boot tag word hi */
extern unsigned long uRam0000000000689ae8;  /* boot tag word hi */
extern unsigned long _DAT_00689dd0;    /* msg tag lo */
extern unsigned long uRam0000000000689dd8;  /* msg tag hi */
extern unsigned long _DAT_006b6fd4;    /* clock global lo */
extern unsigned long DAT_006b6fd6;     /* clock global */
extern unsigned long DAT_006b6fd7;     /* clock global */
extern unsigned long _DAT_006b6fd8;    /* clock global */
extern unsigned long DAT_006b6fda;     /* clock global */
extern unsigned long DAT_006b6fdb;     /* clock global */




extern unsigned long sk_rt_00650af8(); /* FUN_00650af8 */
extern unsigned long sk_rt_00650b3c(); /* FUN_00650b3c */
extern unsigned long sk_rt_00650c10(); /* FUN_00650c10 */
extern sk_u128_t sk_rt_00650ec8(); /* FUN_00650ec8 */
extern unsigned long sk_rt_00650ed0(); /* FUN_00650ed0 */
extern unsigned long sk_rt_00651074(); /* FUN_00651074 */
extern unsigned long sk_rt_006510cc(); /* FUN_006510cc */
extern sk_u128_t sk_rt_00651108(); /* FUN_00651108 */
extern unsigned long sk_rt_00652204(); /* FUN_00652204 */
extern unsigned long sk_rt_006542e0(); /* FUN_006542e0 */
extern unsigned long sk_rt_00654528(); /* FUN_00654528 */
extern unsigned long sk_rt_00654cf4(); /* FUN_00654cf4 */
extern unsigned long sk_rt_0065558c(); /* FUN_0065558c */
extern unsigned long sk_rt_0065585c(); /* FUN_0065585c */
extern unsigned long sk_rt_00655d7c(); /* FUN_00655d7c */
extern unsigned long sk_rt_00655d9c(); /* FUN_00655d9c */
extern unsigned long sk_rt_00655dbc(); /* FUN_00655dbc */
extern unsigned long sk_rt_00655e1c(); /* FUN_00655e1c */
extern unsigned long sk_rt_00655e7c(); /* FUN_00655e7c */
extern unsigned long sk_rt_00655e84(); /* FUN_00655e84 */
extern unsigned long sk_rt_00656744(); /* FUN_00656744 */
extern unsigned long sk_rt_0065be9c(); /* FUN_0065be9c */
extern unsigned long sk_rt_0065c218(); /* FUN_0065c218 */
extern unsigned long sk_rt_0065c9c0(); /* FUN_0065c9c0 */
extern unsigned long sk_rt_0065ca28(); /* FUN_0065ca28 */
extern unsigned long sk_rt_0065cba0(); /* FUN_0065cba0 */
extern unsigned long sk_rt_0065ce40(); /* FUN_0065ce40 */
extern unsigned long sk_rt_0065d20c(); /* FUN_0065d20c */
extern unsigned long sk_rt_0065d2cc(); /* FUN_0065d2cc */
extern unsigned long sk_rt_0065d2e4(); /* FUN_0065d2e4 */
extern unsigned long sk_rt_00664330(); /* FUN_00664330 */
extern unsigned long sk_rt_006643b8(); /* FUN_006643b8 */
extern unsigned long sk_rt_00664588(); /* FUN_00664588 */
extern unsigned long sk_rt_006645bc(); /* FUN_006645bc */
extern unsigned long sk_rt_0066469c(); /* FUN_0066469c */
extern unsigned long sk_rt_006646e0(); /* FUN_006646e0 */
extern unsigned long sk_rt_006649b4(); /* FUN_006649b4 */
extern unsigned long sk_rt_00664a84(); /* FUN_00664a84 */
extern unsigned long sk_rt_00664bd4(); /* FUN_00664bd4 */
extern unsigned long sk_rt_00664cbc(); /* FUN_00664cbc */
extern unsigned long sk_rt_006657d8(); /* FUN_006657d8 */
extern unsigned long sk_rt_0067a7f0(); /* FUN_0067a7f0 */
extern unsigned long sk_rt_0067ad00(); /* FUN_0067ad00 */
extern unsigned long sk_rt_0067b478(); /* FUN_0067b478 */
extern unsigned long sk_rt_0067b580(); /* FUN_0067b580 */
extern unsigned long sk_rt_0067b664(); /* FUN_0067b664 */
extern unsigned long sk_rt_0067ca6c(); /* FUN_0067ca6c */
extern unsigned long sk_rt_0067d014(); /* FUN_0067d014 */
extern unsigned long sk_rt_0067d02c(); /* FUN_0067d02c */
extern unsigned long sk_rt_0067d1f0(); /* FUN_0067d1f0 */
extern unsigned long sk_rt_0067d3f8(); /* FUN_0067d3f8 */
extern unsigned long sk_rt_0067d440(); /* FUN_0067d440 */
extern unsigned long sk_rt_0067d6c0(); /* FUN_0067d6c0 */
extern unsigned long sk_rt_0067f608(); /* FUN_0067f608 */
extern unsigned long sk_rt_006832c8(); /* FUN_006832c8 */
extern unsigned long sk_rt_006833bc(); /* FUN_006833bc */
extern unsigned long sk_rt_006848f4(); /* FUN_006848f4 */
extern unsigned long sk_rt_00684bc0(); /* FUN_00684bc0 */
extern unsigned long sk_rt_00684c0c(); /* FUN_00684c0c */
extern unsigned long sk_rt_00684c58(); /* FUN_00684c58 */
extern unsigned long sk_rt_00684de0(); /* FUN_00684de0 */
extern unsigned long sk_rt_00684e44(); /* FUN_00684e44 */
extern unsigned long sk_rt_00684f2c(); /* FUN_00684f2c */
extern unsigned long sk_rt_00684f7c(); /* FUN_00684f7c */
extern unsigned long sk_rt_00684f94(); /* FUN_00684f94 */
extern unsigned long sk_rt_00684fac(); /* FUN_00684fac */
extern unsigned long sk_rt_00684fc4(); /* FUN_00684fc4 */
extern unsigned long sk_rt_00685054(); /* FUN_00685054 */
extern unsigned long sk_rt_00685084(); /* FUN_00685084 */
extern unsigned long sk_rt_006850dc(); /* FUN_006850dc */
extern unsigned long sk_rt_006850f4(); /* FUN_006850f4 */
extern sk_u128_t sk_rt_00685164(); /* FUN_00685164 */
extern unsigned long sk_rt_0068538c(); /* FUN_0068538c */

extern unsigned char *sk_lock_acq_65_61348(unsigned char *flag); /* FUN_00661348 */


extern unsigned long _DAT_006fe774;   /* thread-create failure counter */
extern unsigned long _DAT_006fe77c;   /* thread-create counter */
extern unsigned long _DAT_006fe780;   /* thread-create counter */
extern unsigned long _DAT_006fe784;   /* thread-create counter */
extern unsigned long _DAT_006fe788;   /* thread-create counter */
extern unsigned long _DAT_006fe78c;   /* thread-create counter */

/* plain (non-underscore) globals referenced directly in this slice */
extern unsigned long DAT_006b5248;
extern unsigned long DAT_006b53b0;
extern unsigned long DAT_006b6518;
extern unsigned long DAT_006b6fd4;
extern unsigned long DAT_006b6fd6;
extern unsigned long DAT_006b6fd7;
extern unsigned long DAT_006b6fda;
extern unsigned long DAT_006b6fdb;
extern unsigned long DAT_006b71e8;
extern unsigned long DAT_006fe750;
extern unsigned long DAT_006fe770;
extern unsigned long DAT_006fe798;
extern unsigned long DAT_006fe799;
extern unsigned long DAT_006fec90;
extern unsigned long DAT_006ff0a8;
extern const char DAT_0065e114[1];    /* string ref 0065e114 */
extern const char DAT_00689c40[0x20]; /* error-string fallback */
extern const char DAT_00689db0[0x20]; /* error-string fallback */
extern const char DAT_00689f20[0x20]; /* error-string fallback */

extern void CallSupervisor(unsigned long call);
extern void SoftwareBreakpoint(unsigned long code, unsigned long addr);
extern void DataMemoryBarrier(unsigned long a, unsigned long b);
extern void LOAcquire(void);
extern void LORelease(void);
extern unsigned long tpidr_el0;     /* current thread control block pointer */
extern unsigned long tpidrro_el0;   /* per-cpu / user context base */

/* ---- forward declarations of in-batch functions ---- */
void sk_clock_cfg_65d804(unsigned long param_1, void *param_2);
long sk_clock_now_65d90c(unsigned long param_1);
unsigned long sk_timer_tbl_read_65da08(unsigned int param_1);
void sk_clock_fast_enable_65db00(unsigned char param_1);
void sk_time_div_65db0c(unsigned long param_1, unsigned long param_2,                         unsigned char (*param_3)[16], unsigned long param_4);
unsigned long sk_timer_dec_65db84(unsigned long *param_1);
unsigned long sk_timer_acquire_65dc24(unsigned long *param_1, unsigned long param_2);
unsigned long sk_timer_dec_alt_65dda4(unsigned long *param_1);
void sk_timer_release_65de3c(unsigned long *param_1);
void sk_wait_init_65def0(unsigned long *param_1, unsigned short param_2);
unsigned long sk_msg_dispatch_65defc(unsigned long param_1, unsigned long param_2, unsigned long param_3);
void sk_notify_walk_65df30(unsigned long param_1, unsigned long param_2);
void sk_tree_walk_65e020(long *param_1, unsigned long param_2);
unsigned long sk_call_ind_65e118(unsigned long param_1);
unsigned long sk_clock_name_65e138(unsigned long param_1, long *param_2);
unsigned short sk_notif_wait_65e370(unsigned long *param_1, unsigned long param_2);
void sk_notif_signal_65e378(unsigned long *param_1, int param_2);
void sk_notif_slot_65e454(unsigned int *param_1, void (*param_2)(unsigned long),                           unsigned long param_3);
void sk_timer_slot_clear_65e5c0(void);
unsigned long sk_notif_oneshot_65e6fc(void);
void sk_timer_alloc_65e748(long *param_1);
void sk_dispatch_slot0_65e7cc(void);
void sk_sched_msg_send_65e7f0(unsigned long param_1, int param_2);
unsigned long sk_exec_in_ctx_65ea38(sk_u128_t (*param_1)(unsigned long, unsigned long),
                                     unsigned long param_2, unsigned char *param_3,
                                     unsigned long param_4);
void sk_thread_unblock_65eafc(unsigned long param_1);
void sk_dispatch_slot10_65ec08(void);
void sk_dispatch_slot18_65ecec(void);
void sk_log_panic_65ec2c(unsigned int param_1, unsigned long param_2, unsigned long param_3,                          unsigned long param_4, unsigned int param_5);
void sk_clock_event_65ed10(unsigned int param_1, unsigned long param_2, unsigned int param_3,                            unsigned long param_4);
void sk_dispatch_slot20_65ee30(void);
void sk_err_frame_7_65ee54(unsigned long param_1);
sk_u128_t sk_msg_send_65ef24(unsigned long param_1, unsigned short *param_2);
void sk_dispatch_slot8_65f058(void);
void sk_ctx_set_65f07c(unsigned long param_1, unsigned char *param_2);
void sk_err_str_65f428(unsigned char param_1);
void sk_err_str_w20_65f448(void);
void sk_noop_65f454(void);
void sk_boot_log_65f468(unsigned long param_1, unsigned long param_2, unsigned long param_3,                         unsigned long param_4);
long sk_msg_reg_build_65fa24(unsigned long param_1, unsigned long param_2, unsigned long param_3,                              unsigned int param_4);
long sk_msg_reg_copy_65fb08(unsigned long param_1, unsigned long param_2, unsigned long param_3);
void sk_msg_slot_put_65fbb0(unsigned int param_1, unsigned long param_2);
unsigned long sk_msg_slot_get_65fc28(unsigned int param_1);
void sk_msg2_slot_put_65fca8(unsigned int param_1, unsigned long param_2);
unsigned long sk_bits_level_65fd3c(unsigned long param_1);
unsigned long sk_bits_low6_65fd44(unsigned long param_1);
unsigned long sk_desc_pack_65fd4c(unsigned long param_1, unsigned long param_2,                                   unsigned int param_3, int param_4);
void sk_clock_init_65fd70(void);
void sk_strbuf_append_65f834(unsigned long *param_1, unsigned long param_2, unsigned long param_3);
unsigned long sk_tag_sanitize_65f8e8(unsigned int param_1);
void sk_thread_create_65fdb8(unsigned long *param_1, unsigned long param_2, unsigned long param_3,                              unsigned long param_4, int param_5);
void sk_sched_wake_65_609b4(unsigned long param_1);
void sk_wake_alloc_65_609cc(unsigned long param_1);
void sk_wake_settle_65_60ab4(unsigned long param_1);
void sk_tcb_stack_reclaim_65_60b20(unsigned long param_1);
unsigned long sk_stack_check_65_60b28(unsigned long param_1);
long sk_preempt_acq_65_60ba8(unsigned long param_1, unsigned long param_2);
void sk_nested_inc_65_60c44(void);
void sk_nested_dec_65_60ca4(void);
void sk_buf_alloc_65_60d00(unsigned long *param_1, unsigned long param_2, unsigned int param_3);
unsigned long sk_buf_copy_65_60eec(unsigned long param_1, unsigned long param_2, unsigned long param_3);
unsigned long sk_buf_exec_65_60f60(unsigned long param_1, unsigned long param_2, unsigned long param_3);
void sk_stack_tail_check_65_61178(void);
void sk_ind_call_65_611a8(unsigned long (*fn)(unsigned long), unsigned long param_2);
unsigned long sk_boot_param_65_611b8(void);
void sk_err_str_b_65_612c0(unsigned char param_1);
void sk_err_str_w20b_65_612e0(void);
void sk_noop_65_612ec(void);
long sk_next_seq_65_612f0(void);
unsigned long sk_cur_tcb_65_61318(void);
unsigned char sk_flag_798_65_61324(void);
unsigned char sk_flag_799_65_61330(void);
unsigned char sk_flag_b53b0_65_6133c(void);
void sk_lock_rel_65_613d0(unsigned char *param_1);
void sk_lock_drain_65_61428(void);
unsigned long sk_slot_addr_65_61488(unsigned long param_1);
void sk_thread_boot_65_61500(unsigned long param_1, unsigned long param_2,                              unsigned long *param_3, unsigned long *param_4, unsigned long param_5);
unsigned long sk_msg_word_65_61d38(unsigned long param_1, unsigned long *param_2,                                    unsigned long param_3, unsigned long param_4,                                    unsigned long param_5, unsigned long param_6);
void sk_msg_word_fwd_65_61e1c(void);
unsigned long sk_msg_extract_65_61e24(unsigned long param_1, long *param_2, unsigned long *param_3,                                       unsigned long param_4, unsigned long param_5,                                       unsigned char param_6, long *param_7, unsigned char *param_8);
void sk_tcb_cb_set_65_62044(unsigned long param_1, unsigned long param_2);
long sk_stack_alloc_65_6204c(long param_1, long param_2);
unsigned long sk_tcb_read_140_65_62098(unsigned long param_1);
unsigned long sk_stack_alloc_mode_65_620a0(unsigned long param_1, unsigned char param_2);
unsigned long sk_block_alloc_65_62158(long param_1, long param_2);
long sk_tcb_to_block_65_621f4(long param_1);
long sk_slot_base_65_62264(long param_1);
unsigned long sk_block_alloc_v_65_622d8(long param_1);
void sk_tcb_msg_range_65_62368(unsigned long param_1, long *param_2, long *param_3);
void sk_tcb_window_set_65_62380(unsigned long param_1, unsigned long param_2, unsigned long param_3,                                 long param_4, long param_5);
unsigned long sk_tcb_cap_65_6239c(unsigned long param_1);
unsigned long sk_tcb_tag_65_623a4(unsigned long param_1);
void sk_msg_recv_65_623d0(unsigned long *param_1, long param_2);
void sk_tcb_name_set_65_62628(unsigned long param_1, unsigned int param_2);
void sk_boot_print_65_62630(unsigned long param_1, unsigned long param_2);
unsigned long sk_tcb_read_120_65_626f0(unsigned long param_1);
void sk_tcb_obj_set_65_626f8(unsigned long param_1, unsigned long param_2);
void sk_msg_clear_65_6272c(unsigned long *param_1, unsigned long param_2);
void sk_msg_send2_65_62754(unsigned long *param_1, unsigned long param_2);
void sk_err_str_c_65_62a40(unsigned long param_1, unsigned char param_2);
unsigned long sk_msg_word_tcb_65_62b84(unsigned long param_1);
void sk_caps_dump_65_62bf0(unsigned long param_1, unsigned long param_2);
bool sk_intvec_read_65_62f0c(unsigned long param_1, unsigned long param_2);
void sk_intvec_print_65_630f8(unsigned long param_1, unsigned long param_2);
void sk_boot_dump_65_631d8(unsigned long param_1, unsigned long param_2, unsigned long param_3,                            unsigned long param_4, int param_5, int param_6,                            unsigned long param_7, unsigned long param_8);
void sk_pad_print_65_634c0(unsigned long param_1, unsigned long param_2, unsigned long param_3);
bool sk_tcb_bound_65_635ac(unsigned long param_1);
unsigned long sk_user_ref_65_635c0(unsigned long param_1, unsigned long param_2);
unsigned long sk_user_ref_b_65_6363c(unsigned long param_1, unsigned long param_2);
void sk_user_unref_65_63644(unsigned long param_1, unsigned long param_2);
unsigned long sk_addr_to_cap_65_636f8(unsigned long param_1);
unsigned long sk_boot_name_65_63744(int param_1, unsigned int param_2);
void sk_err_str_fwd_65_638d8(void);
void sk_panic_7886_65_638f8(void);
void sk_panic_785c_65_63910(void);
void sk_timer_publish_65_63928(unsigned long *param_1, unsigned long param_2, long *param_3);
void sk_timer_cb_65_63ac8(unsigned long param_1, unsigned long param_2);
unsigned long sk_clock_reg_read_65_ebc8(unsigned long param_1);
unsigned long sk_err_frame_11_65_eeb0(unsigned int param_1);
unsigned long sk_err_frame_65_e5cc(unsigned long param_1, unsigned short param_2, unsigned long *param_3,
                           unsigned long param_4);
/*--------------------------------------------------------------------*/
/* FUN_0065d804 @ 0x0065d804
 * Ghidra: void FUN_0065d804(ulong param_1, long param_2)
 * Configures one timer-table entry (stride 0x50 at 0x6b5250): copies the 0x50
 * calibration record, then, when the entry is a 1..3 style clock, computes and
 * stores the frequency and period from the raw tick read (FUN_00656c28) and
 * calls FUN_0065db0c to publish the derived ns-per-tick into the caller buffer.
 * Confidence: medium
 * Notes: panic strings 0x6a66ba ("bad clock index"); bounds-checked table. */
void sk_clock_cfg_65d804(unsigned long param_1, void *param_2)
{
    long lVar1 = (long)(param_1 & 0xffffffff) * 0x50;
    unsigned long uVar4 = (unsigned long)lVar1 + 0x6b5250;
    unsigned long uVar5 = (unsigned long)lVar1 + 0x6b52a0;
    if ((uVar4 < 0x6b5250 || 0x6b5390 < uVar5) || uVar5 < uVar4) {
        SoftwareBreakpoint(0x5519, 0x65d8f8); /* does not return */
    }
    sk_memmove(param_2, (void *)uVar4, 0x50);
    if ((*(char *)((char *)param_2 + 0x20) == '\x01') &&
        (*(long *)((char *)param_2 + 0x28) != 0)) {
        return;
    }
    if ((unsigned int)((int)param_1 - 1) < 3) {
        unsigned long uVar3 = sk_rt_00656c28(); /* raw tick read */
        *(unsigned long *)((char *)param_2 + 0x28) = uVar3;
        unsigned long uVar5 = uVar3;
        unsigned long uVar4 = 1000000000;
        unsigned long uVar6;
        do {
            uVar6 = uVar4;
            uVar4 = 0;
            if (uVar6 != 0) {
                uVar4 = uVar5 / uVar6;
            }
            uVar4 = uVar5 - uVar4 * uVar6;
            uVar5 = uVar6;
        } while (uVar4 != 0);
        uVar5 = 0;
        if (uVar6 != 0) {
            uVar5 = uVar3 / uVar6;
        }
        uVar4 = 0;
        if (uVar6 != 0) {
            uVar4 = 1000000000 / uVar6;
        }
        *(unsigned long *)((char *)param_2 + 0x30) = uVar5;
        *(unsigned long *)((char *)param_2 + 0x38) = uVar4;
        sk_time_div_65db0c(param_1, 0xffffffffffffffffUL, param_2 + 0x10, 0);
        return;
    }
    sk_panic_2(0, 0x6a66ba); /* does not return */
}

/*--------------------------------------------------------------------*/
/* FUN_0065d90c @ 0x0065d90c
 * Ghidra: long FUN_0065d90c(ulong param_1)
 * Reads the current clock value for clock id param_1. Id 3 returns the raw
 * per-cpu counter (FUN_00656c04). If the fast-path flag (DAT_006b5248) is set,
 * it spins until two consecutive reads of FUN_0065da08 agree and sums them with
 * the current offset; otherwise it consults the per-cpu scheduler state
 * (FUN_0065be80) and its wait flags before falling back to FUN_0065eeb0.
 * Confidence: medium
 * Notes: panics on bad id (0x6a66ba). */
long sk_clock_now_65d90c(unsigned long param_1)
{
    int iVar1 = (int)param_1;
    if (iVar1 == 3) {
        return sk_rt_00656c04();
    }
    if ((DAT_006b5248 & 1) != 0) {
        long lVar2 = sk_timer_tbl_read_65da08((unsigned int)param_1);
        if (1 < ((unsigned int)(iVar1 - 1) & 0xff)) {
            sk_panic_2(0, 0x6a66ba); /* does not return */
        }
        for (;;) {
            long lVar3 = lVar2;
            long lVar4 = sk_rt_00656c04();
            lVar2 = sk_timer_tbl_read_65da08((unsigned int)param_1);
            if (lVar2 == lVar3) {
                return lVar3 + lVar4;
            }
        }
    }
    long lVar2 = sk_percpu_108();
    unsigned long uVar5 = 0;
    if (lVar2 != 0) {
        if (iVar1 == 1) {
            uVar5 = param_1 & 0xffffffff;
        } else if (iVar1 == 2) {
            uVar5 = 2;
        } else {
            goto check_done;
        }
        if ((*(unsigned long *)(lVar2 + 8) & uVar5) != 0) {
            lVar2 = sk_timer_tbl_read_65da08((unsigned int)param_1);
            for (;;) {
                long lVar3 = lVar2;
                long lVar4 = sk_rt_00656c04();
                lVar2 = sk_timer_tbl_read_65da08((unsigned int)param_1);
                if (lVar2 == lVar3) {
                    return lVar3 + lVar4;
                }
            }
        }
    }
check_done:
    return sk_err_frame_11_65_eeb0(param_1);
}

/*--------------------------------------------------------------------*/
/* FUN_0065da08 @ 0x0065da08
 * Ghidra: undefined8 FUN_0065da08(uint param_1)
 * Reads the timer-table read head for clock id param_1. Each table entry
 * (stride 0x50 at 0x6b5250) has a cached read pointer at +0x90 and a "first"
 * byte at +0x98. When empty it lazily fills from the per-cpu schedule source
 * (FUN_0065be80 / FUN_0065be40) and validates the per-cpu timer id.
 * Confidence: medium
 * Notes: SoftwareBreakpoint(0x5519,0x65db00) on mis-validate; FUN_00684860. */
unsigned long sk_timer_tbl_read_65da08(unsigned int param_1)
{
    long lVar4 = (long)param_1 * 0x50;
    if ((lVar4 + 0x6b5250 < 0x6b5250 || 0x6b5390 < lVar4 + 0x6b52a0) ||
        lVar4 + 0x6b52a0 < lVar4 + 0x6b5250) {
        goto bad;
    }
    unsigned long *puVar6 = *(unsigned long **)(lVar4 + 0x6b5290);
    if (puVar6 == 0) {
        long lVar3 = sk_percpu_108();
        if (lVar3 == 0) {
retry:
            puVar6 = *(unsigned long **)(lVar4 + 0x6b5290);
            if (puVar6 == 0) {
                return 0;
            }
        } else {
            unsigned long *puVar7;
            if (param_1 == 2) {
                if (((*(unsigned char *)(lVar3 + 8) >> 1) & 1) == 0) goto retry;
                lVar3 = sk_rt_0065be40();
                puVar6 = (unsigned long *)(lVar3 + 0x20);
                puVar7 = (unsigned long *)(lVar3 + 0x28);
            } else {
                if ((param_1 != 1) || ((*(unsigned char *)(lVar3 + 8) & 1) == 0)) goto retry;
                lVar3 = sk_rt_0065be40();
                puVar6 = (unsigned long *)(lVar3 + 0x18);
                puVar7 = (unsigned long *)(lVar3 + 0x20);
            }
            if (puVar7 < puVar6) goto bad;
            *(unsigned long **)(lVar4 + 0x6b5290) = puVar6;
            *(unsigned char *)(lVar4 + 0x6b5298) = 1;
        }
    }
    unsigned long uVar8 = *puVar6;
    if (*(char *)(lVar4 + 0x6b5298) == '\x01') {
        long lVar4 = sk_rt_0065be40();
        int iVar1 = *(int *)(lVar4 + 4);
        int *piVar5 = (int *)sk_rt_0065be40();
        if (iVar1 != *piVar5) {
            sk_rt_00684860();
bad:
            SoftwareBreakpoint(0x5519, 0x65db00); /* does not return */
        }
    }
    return uVar8;
}

/*--------------------------------------------------------------------*/
/* FUN_0065db00 @ 0x0065db00
 * Ghidra: void FUN_0065db00(undefined1 param_1)
 * Writes the clock fast-path enable byte to DAT_006b5248.
 * Confidence: high (trivial setter) */
void sk_clock_fast_enable_65db00(unsigned char param_1)
{
    DAT_006b5248 = param_1;
}

/*--------------------------------------------------------------------*/
/* FUN_0065db0c @ 0x0065db0c
 * Ghidra: void FUN_0065db0c(undefined8 param_1, ulong param_2,
 *                          undefined1 (*param_3)[16], ulong param_4)
 * Computes a 128-bit ns time from param_2 (a count) using the two calibration
 * words written by FUN_0065d804, optionally rounding up (param_4 bit 0 selects
 * FUN_00683338), and stores the 16-byte result into *param_3.
 * Confidence: medium
 * Notes: div-by-zero guarded; FUN_0065d804 fills the calibration frame. */
void sk_time_div_65db0c(unsigned long param_1, unsigned long param_2,
                        unsigned char (*param_3)[16], unsigned long param_4)
{
    unsigned long local_58 = 0, local_50 = 0;
    unsigned long local_80 = 0, uStack_78 = 0;
    unsigned char auVar3[16] = {0};
    sk_clock_cfg_65d804(param_1, &local_80);
    unsigned long uVar1 = 0;
    if (local_58 != 0) {
        uVar1 = param_2 / local_58;
    }
    unsigned long uVar2 = 0;
    if (local_50 != 0) {
        uVar2 = (local_80 * (param_2 - uVar1 * local_58)) / local_50;
    }
    auVar3[0] = (unsigned char)uVar1;
    auVar3[8] = (unsigned char)uVar2;
    if ((param_4 & 1) == 0) {
        unsigned char r[16];
        sk_rt_00683338(uVar1, uVar2, local_80, uStack_78, r); /* round-up helper */
        __builtin_memcpy(auVar3, r, 16);
    }
    __builtin_memcpy(*param_3, auVar3, 16);
}

/*--------------------------------------------------------------------*/
/* FUN_0065db84 @ 0x0065db84
 * Ghidra: undefined8 FUN_0065db84(ulong *param_1)
 * Decrements a timer/notification wait structure: if the generation word
 * (param_1[0]) matches the current clock generation, bumps the wait count and
 * enqueues; otherwise resets the word and dispatches FUN_0065dc24.
 * Confidence: medium */
unsigned long sk_timer_dec_65db84(unsigned long *param_1)
{
    unsigned long uVar3 = *param_1;
    unsigned long uVar2 = sk_cur_tcb_65_61318();
    if (uVar2 + 0x178 < uVar2) {
        SoftwareBreakpoint(0x5519, 0x65dc24); /* does not return */
    }
    if ((((unsigned int)(uVar2 >> 0xe) ^ (unsigned int)uVar3) & 0xffffff) == 0) {
        if (*(short *)((char *)param_1 + 0xe) != 0) {
            *(short *)((char *)param_1 + 0xe) -= 1;
            *(short *)((char *)param_1 + 0xc) += 1;
            goto enqueue;
        }
    } else {
        do {
            if (uVar3 != 0) goto busy;
            uVar3 = *param_1;
        } while (uVar3 != 0);
        *param_1 = uVar2 >> 0xe & 0xffffff;
        if (*(short *)((char *)param_1 + 0xc) == 0) {
enqueue:
            sk_rt_0065c144(uVar2, param_1, (void *)0xfffffffffffffff0);
            return 0;
        }
    }
busy:
    sk_timer_acquire_65dc24(param_1, 0);
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_0065dc24 @ 0x0065dc24
 * Ghidra: undefined8 FUN_0065dc24(ulong *param_1, undefined8 param_2)
 * Acquires the timer slot for param_1 (a per-clock wait word): resolves the
 * clock id from the low byte of param_1[1], reads the clock table, marks the
 * word busy (bit 0x1000000), and iterates the per-cpu dispatch to settle the
 * wait. Panics if the generation mismatches (0x6a671f).
 * Confidence: high (verified 1:1 against fresh decompile 2026-08-12: clock-id
 * resolve, generation check, busy-bit walk, panic 0x6a671f, slot-register
 * dispatch, and the done: tail all match). */
unsigned long sk_timer_acquire_65dc24(unsigned long *param_1, unsigned long param_2)
{
    unsigned int uVar2 = ((unsigned int)param_1 >> 4) & 0xf;
    if ((unsigned char)param_1[1] != 0) {
        uVar2 = (unsigned char)param_1[1] - 1;
    }
    unsigned long uVar5 = sk_cur_tcb_65_61318();
    unsigned long uVar6 = sk_clock_reg_read(uVar2 & 0xff);
    unsigned long uVar8 = _DAT_006ff0a8 >> 10;
    long lVar7 = sk_cur_tcb_65_61318();
    *(unsigned long *)(lVar7 + 0x78) = uVar8;
    unsigned long uVar9 = uVar5 >> 0xe & 0xffffff;
    uVar8 = *param_1;
    if (uVar8 == 0) {
        *param_1 = uVar9;
    }
    if ((uVar8 != 0) && ((((unsigned int)uVar8 ^ (unsigned int)(uVar5 >> 0xe)) & 0xffffff) == 0)) {
        sk_panic_2(sk_cur_tcb_65_61318(), 0x6a671f); /* does not return */
    }
    if (uVar8 != 0) {
        unsigned long uVar5 = 0;
        do {
            while ((((unsigned int)uVar8 >> 0x18) & 1) == 0) {
                unsigned long uVar1 = *param_1;
                if (uVar1 == uVar8) {
                    *param_1 = uVar8 | 0x1000000;
                    break;
                }
                uVar8 = uVar1;
                if ((uVar1 == 0) && (uVar8 = *param_1, uVar8 == 0)) {
                    *param_1 = uVar5 | uVar9;
                    goto done;
                }
            }
            uVar8 = sk_slot_addr_65_61488((unsigned int)uVar8 & 0xffffff);
            if (uVar8 + 0x178 < uVar8) {
                SoftwareBreakpoint(0x5519, 0x65dd94); /* does not return */
            }
            int iVar4 = sk_clock_reg_inc(uVar2 & 0xff, param_1, uVar6, uVar8, param_2);
            if (iVar4 == 1) {
                uVar5 = 0;
            } else if (iVar4 == 2) {
                uVar5 = 0x1000000;
            } else if (iVar4 == 3) {
                return 0;
            }
            uVar6 = sk_clock_reg_read(uVar2 & 0xff);
            uVar8 = *param_1;
        } while (uVar8 != 0);
        *param_1 = uVar5 | uVar9;
    }
done:
    sk_rt_0065c144(sk_cur_tcb_65_61318(), param_1, (void *)0xfffffffffffffff0);
    return 1;
}

/*--------------------------------------------------------------------*/
/* FUN_0065dda4 @ 0x0065dda4
 * Ghidra: undefined8 FUN_0065dda4(ulong *param_1)
 * Alternate timer decrement: like FUN_0065db84 but returns 0 on a busy slot
 * instead of falling through to acquire; returns 1 only when it successfully
 * enqueued the wait (generation reset / count bump).
 * Confidence: medium */
unsigned long sk_timer_dec_alt_65dda4(unsigned long *param_1)
{
    unsigned long uVar3 = *param_1;
    unsigned long uVar2 = sk_cur_tcb_65_61318();
    if (uVar2 + 0x178 < uVar2) {
        SoftwareBreakpoint(0x5519, 0x65de3c); /* does not return */
    }
    if ((((unsigned int)(uVar2 >> 0xe) ^ (unsigned int)uVar3) & 0xffffff) == 0) {
        if (*(short *)((char *)param_1 + 0xe) != 0) {
            *(short *)((char *)param_1 + 0xe) -= 1;
            *(short *)((char *)param_1 + 0xc) += 1;
            goto enqueue;
        }
    } else {
        do {
            if (uVar3 != 0) {
                return 0;
            }
            uVar3 = *param_1;
        } while (uVar3 != 0);
        *param_1 = uVar2 >> 0xe & 0xffffff;
        if (*(short *)((char *)param_1 + 0xc) == 0) {
enqueue:
            sk_rt_0065c144(uVar2, param_1, (void *)0xfffffffffffffff0);
            return 1;
        }
    }
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_0065de3c @ 0x0065de3c
 * Ghidra: void FUN_0065de3c(undefined8 *param_1)
 * Releases a timer/notification wait: validates the generation word against the
 * clock, dequeues (FUN_0065c1b8), and either frees the slot (when the nested
 * count hit zero and the word was busy → FUN_0065ecec) or just unwinds the
 * nested count. Panics on generation mismatch (0x6a66fc).
 * Confidence: medium */
void sk_timer_release_65de3c(unsigned long *param_1)
{
    unsigned long uVar3 = *param_1;
    unsigned long uVar2 = sk_cur_tcb_65_61318();
    if ((((unsigned int)(uVar2 >> 0xe) ^ (unsigned int)uVar3) & 0xffffff) != 0) {
        sk_panic_2(0, 0x6a66fc); /* does not return */
    }
    sk_rt_0065c1b8(sk_cur_tcb_65_61318(), param_1, (void *)0xfffffffffffffff0);
    if (*(short *)((char *)param_1 + 0xc) == 0) {
        uVar3 = *param_1;
        *param_1 = 0;
        LORelease();
        if (((unsigned int)uVar3 >> 0x18 & 1) != 0) {
            unsigned int uVar1 = ((unsigned int)param_1 >> 4) & 0xf;
            if (*(unsigned char *)(param_1 + 1) != 0) {
                uVar1 = *(unsigned char *)(param_1 + 1) - 1;
            }
            sk_clock_dispatch_18(uVar1 & 0xff, param_1, 3, 0);
            return;
        }
    } else {
        *(short *)((char *)param_1 + 0xc) -= 1;
        *(short *)((char *)param_1 + 0xe) += 1;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_0065def0 @ 0x0065def0
 * Ghidra: void FUN_0065def0(undefined8 *param_1, undefined2 param_2)
 * Initializes a wait slot: stores the waiter count at +0xe and clears the
 * generation word.
 * Confidence: high (simple init) */
void sk_wait_init_65def0(unsigned long *param_1, unsigned short param_2)
{
    *(unsigned short *)((char *)param_1 + 0xe) = param_2;
    *param_1 = 0;
}

/*--------------------------------------------------------------------*/
/* FUN_0065defc @ 0x0065defc
 * Ghidra: void FUN_0065defc(long param_1, undefined8 param_2, undefined8 param_3)
 * Saves the caller frame link registers and dispatches through the indirect
 * jump table at param_1 (message-copy trampoline). The saved x29/x30/sp are
 * written to the target frame at param_1-0x20..-8.
 * Confidence: high (verified vs decompile 2026-08-12; trivial 4-line body) */
unsigned long sk_msg_dispatch_65defc(unsigned long param_1, unsigned long param_2, unsigned long param_3)
{
    *(unsigned long *)(param_1 - 0x10) = (unsigned long)__builtin_frame_address(0);
    *(unsigned long *)(param_1 - 8) = (unsigned long)__builtin_return_address(0);
    *(unsigned long *)(param_1 - 0x20) = 0x8; /* register0x00000008 */
    sk_ind_call_65_611a8((unsigned long (*)(unsigned long))param_2, param_3);
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_0065df30 @ 0x0065df30
 * Ghidra: void FUN_0065df30(long param_1, undefined8 param_2)
 * Walks a small fixed table at DAT_006b71e8 (stride 7 words, 1 entry) and for
 * each node matching param_1 invokes FUN_0065e020(node, param_2) unless the
 * global flag DAT_006fec90 bit0 is clear.
 * Confidence: low (register-artifact, tiny fixed loop). */
void sk_notify_walk_65df30(unsigned long param_1, unsigned long param_2)
{
    if (((int)param_2 == 0) || ((DAT_006fec90 & 1) == 0)) {
        long lVar2 = 1;
        long *plVar1 = (long *)&DAT_006b71e8;
        do {
            if (*plVar1 == (long)param_1) {
                sk_tree_walk_65e020((void *)plVar1, param_2);
            }
            plVar1 += 7;
            lVar2 -= 1;
        } while (lVar2 != 0);
    }
}

/*--------------------------------------------------------------------*/
/* FUN_0065e020 @ 0x0065e020
 * Ghidra: void FUN_0065e020(long *param_1, ulong param_2)
 * Recursive notification-tree walk: for each child pointer in the array at
 * param_1[2] (count param_1[3]) recurses, then invokes the mounted callback
 * (param_1[1] with tag param_1[0]=0x706c6174, or param_1[6] with param_1[5]
 * flag) at most once per direction. param_2 bit0 selects the alternate branch.
 * Confidence: medium */
void sk_tree_walk_65e020(long *param_1, unsigned long param_2)
{
    unsigned long uVar3 = param_1[3];
    if (uVar3 != 0) {
        unsigned long uVar4 = 0;
        do {
            unsigned long uVar2 = *(unsigned long *)(param_1[2] + uVar4 * 8);
            if (uVar2 != 0) {
                if (uVar2 + 0x38 < uVar2) {
                    SoftwareBreakpoint(0x5519, 0x65e114); /* does not return */
                }
                sk_tree_walk_65e020((void *)uVar2, param_2);
                uVar3 = param_1[3];
            }
            uVar4 += 1;
        } while (uVar4 < uVar3);
    }
    if ((param_2 & 1) == 0) {
        if ((param_1[4] != 1) && (param_1[1] != 0)) {
            if (param_1[0] == 0x706c6174) {
                (*(void (**)(void))param_1[1])();
            } else {
                sk_buf_copy_65_60eec(0x40000, (unsigned long)DAT_0065e114, (unsigned long)param_1);
            }
            param_1[4] = 1;
        }
    } else if ((param_1[5] != 1) && (param_1[6] != 0)) {
        (*(void (**)(void))param_1[6])();
        param_1[5] = 1;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_0065e118 @ 0x0065e118
 * Ghidra: undefined8 FUN_0065e118(long param_1)
 * Calls the function pointer stored at param_1+8 and returns 0.
 * Confidence: high (thin indirect call) */
unsigned long sk_call_ind_65e118(unsigned long param_1)
{
    (*(void (**)(void))(param_1 + 8))();
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_0065e138 @ 0x0065e138
 * Ghidra: undefined8 FUN_0065e138(long param_1, long *param_2)
 * Resolves a monotonic clock name: when param_1==0 returns the default clock
 * handle (FUN_006661e0); otherwise reads the object name at param_1+0x20 and
 * validates it with FUN_0067b220, storing the result in *param_2.
 * Confidence: medium
 * Notes: SoftwareBreakpoint(0x5519,0x65e168) on negative validation. */
unsigned long sk_clock_name_65e138(unsigned long param_1, long *param_2)
{
    unsigned long uVar2;
    long local_28;
    if (param_1 == 0) {
        local_28 = 0;
        uVar2 = sk_rt_006661e0(0x6a5b34, &local_28);
    } else {
        uVar2 = *(unsigned long *)(param_1 + 0x20);
        local_28 = sk_rt_0067b220(uVar2);
        if (local_28 < 0) {
            SoftwareBreakpoint(0x5519, 0x65e168); /* does not return */
        }
    }
    *param_2 = local_28;
    return uVar2;
}

/*--------------------------------------------------------------------*/
/* FUN_0065e370 @ 0x0065e370
 * Ghidra: ushort FUN_0065e370(ulong *param_1, undefined8 param_2)
 * Blocks on a notification word (param_1): spins the wait-generation, releases
 * the timer via FUN_0065de3c, drives the per-cpu dispatch (FUN_0065ec08) until
 * it settles (return 3), and returns the last seen high-word priority delta.
 * Confidence: low (heavy spin/lock register artifacts) */
unsigned short sk_notif_wait_65e370(unsigned long *param_1, unsigned long param_2)
{
    unsigned int uVar2 = ((unsigned int)param_1 >> 4) & 0xf;
    if ((unsigned char)param_1[1] != 0) {
        uVar2 = (unsigned char)param_1[1] - 1;
    }
    unsigned long uVar7 = sk_clock_reg_read(uVar2 & 0xff);
    if ((char *)param_1 + 16 < (char *)param_1) {
        SoftwareBreakpoint(0x5519, 0x65e370); /* does not return */
    }
    unsigned long uVar10 = *param_1;
    unsigned int uVar13 = (unsigned int)(uVar10 >> 0x20) + 1;
    int iVar9 = (int)uVar10;
    unsigned long uVar12 = *param_1;
    unsigned short uVar8;
    if (*param_1 == uVar10) {
        *param_1 = (uVar10 & 0xffff000000000000UL) | (uVar10 & 0xffffffff) |
                   (unsigned long)(uVar13 & 0xffff) << 0x20;
        sk_timer_release_65de3c((unsigned long *)param_2);
        uVar12 = uVar10;
    } else {
        unsigned long uVar11;
        do {
            uVar11 = uVar12;
            uVar13 = (unsigned int)(uVar11 >> 0x20) + 1;
            uVar12 = *param_1;
        } while (*param_1 != uVar11);
        *param_1 = (uVar11 & 0xffff000000000000UL) | (uVar11 & 0xffffffff) |
                   (unsigned long)(uVar13 & 0xffff) << 0x20;
        sk_timer_release_65de3c((unsigned long *)param_2);
        uVar12 = uVar11;
        if ((int)uVar11 != iVar9) {
            uVar8 = 1;
            goto settle;
        }
    }
    int iVar6 = sk_clock_reg_inc(uVar2 & 0xff, param_1, uVar7, 0, 1);
    unsigned long uVar11 = uVar10;
    if (iVar6 == 3) {
        uVar8 = 0;
        uVar11 = uVar10;
    } else {
        do {
            uVar7 = sk_clock_reg_read(uVar2 & 0xff);
            uVar12 = *param_1;
            bool bVar5 = (int)uVar12 != iVar9;
            uVar8 = (unsigned short)bVar5;
            uVar11 = uVar12;
            if (bVar5) break;
            iVar6 = sk_clock_reg_inc(uVar2 & 0xff, param_1, uVar7, 0, 1);
            uVar11 = uVar10;
        } while (iVar6 != 3);
        uVar13 = (unsigned int)(uVar12 >> 0x20);
    }
settle:
    unsigned short uVar3 = (unsigned short)(uVar12 >> 0x30);
    unsigned short uVar1 = 0;
    if (uVar8 <= uVar3) {
        uVar1 = uVar3 - uVar8;
    }
    uVar10 = *param_1;
    if (uVar10 == ((uVar12 & 0xffff000000000000UL) | (unsigned long)(uVar13 & 0xffff) << 0x20 |
                   (uVar11 & 0xffffffff))) {
        *param_1 = (unsigned long)(uVar13 - 1 & 0xffff) << 0x20 |
                   (unsigned long)uVar1 << 0x30 | (uVar11 & 0xffffffff);
    } else {
        unsigned short uVar3b;
        do {
            uVar3b = (unsigned short)(uVar10 >> 0x30);
            uVar1 = 0;
            if (uVar8 <= uVar3b) {
                uVar1 = uVar3b - uVar8;
            }
            unsigned long uVar12b = uVar10 + 0xffff00000000;
            unsigned long uVar11b = uVar10 & 0xffffffff;
            bool bVar5 = *param_1 != uVar10;
            uVar10 = *param_1;
            if (!bVar5) {
                *param_1 = uVar12b & 0xffff00000000 | (unsigned long)uVar1 << 0x30 | uVar11b;
                break;
            }
        } while (1);
    }
    sk_timer_dec_65db84((unsigned long *)param_2);
    return uVar8;
}

/*--------------------------------------------------------------------*/
/* FUN_0065e378 @ 0x0065e378
 * Ghidra: void FUN_0065e378(ulong *param_1, int param_2)
 * Signals a notification word (param_1): bumps the generation and priority
 * fields, and when the high word crosses the low wait count dispatches
 * FUN_0065ecec(code=6 or 4 depending on param_2).
 * Confidence: low */
void sk_notif_signal_65e378(unsigned long *param_1, int param_2)
{
    unsigned int uVar2 = ((unsigned int)param_1 >> 4) & 0xf;
    if ((unsigned char)param_1[1] != 0) {
        uVar2 = (unsigned char)param_1[1] - 1;
    }
    if ((char *)param_1 + 16 < (char *)param_1) {
        SoftwareBreakpoint(0x5519, 0x65e454); /* does not return */
    }
    unsigned long uVar9 = *param_1;
    unsigned int uVar6 = (unsigned int)(uVar9 >> 0x20);
    unsigned short uVar4 = (unsigned short)(uVar9 >> 0x30);
    unsigned int uVar3 = uVar6 & 0xffff;
    if (uVar4 + 1 < (uVar6 & 0xffff)) {
        uVar3 = uVar4 + 1;
    }
    unsigned long uVar11 = uVar9 >> 0x20;
    if (param_2 == 0) {
        uVar11 = (unsigned long)uVar3;
    }
    unsigned long uVar10 = *param_1;
    if (uVar10 == uVar9) {
        *param_1 = (unsigned long)((int)uVar9 + 1) | uVar11 << 0x30 | (uVar9 & 0xffff00000000UL);
    } else {
        int iVar8;
        unsigned int uVar6b;
        unsigned short uVar4b;
        unsigned long uVar11b;
        do {
            uVar6b = (unsigned int)(uVar10 >> 0x20);
            uVar4b = (unsigned short)(uVar10 >> 0x30);
            iVar8 = (int)uVar10;
            uVar3 = uVar6b & 0xffff;
            if (uVar4b + 1 < (uVar6b & 0xffff)) {
                uVar3 = uVar4b + 1;
            }
            uVar9 = uVar10 >> 0x20;
            if (param_2 == 0) {
                uVar9 = (unsigned long)uVar3;
            }
            uVar11b = uVar10 & 0xffff00000000UL;
            bool bVar1 = *param_1 != uVar10;
            uVar10 = *param_1;
            if (!bVar1) {
                *param_1 = (unsigned long)(iVar8 + 1) | uVar9 << 0x30 | uVar11b;
                break;
            }
        } while (1);
    }
    if ((unsigned int)uVar4 < (uVar6 & 0xffff)) {
        unsigned int uVar7 = 6;
        if (param_2 == 0) {
            uVar7 = 4;
        }
        sk_clock_dispatch_18(uVar2 & 0xff, param_1, uVar7, 0);
        return;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_0065e454 @ 0x0065e454
 * Ghidra: void FUN_0065e454(uint *param_1, code *param_2, undefined8 param_3)
 * One-shot notification slot: when *param_1 != 0xffffffff, stamps the slot with
 * the clock generation, runs the callback param_2(param_3), marks done
 * (0xffffffff), and when the observed value was the armed+triggered pattern
 * dispatches FUN_0065ecec(code=6). Otherwise chains onto the per-cpu dispatch.
 * Confidence: low */
void sk_notif_slot_65e454(unsigned int *param_1, void (*param_2)(unsigned long),
                          unsigned long param_3)
{
    if (*param_1 != 0xffffffff) {
        unsigned int uVar2 = ((unsigned int)param_1 >> 4) & 0xf;
        unsigned long uVar6 = sk_cur_tcb_65_61318();
        unsigned long uVar9 = _DAT_006ff0a8 >> 10;
        long lVar7 = sk_cur_tcb_65_61318();
        *(unsigned long *)(lVar7 + 0x78) = uVar9;
        unsigned long uVar8 = sk_clock_reg_read(uVar2);
        unsigned int uVar1 = (unsigned int)(uVar6 >> 0xc) & 0x3fffffc;
        unsigned int uVar5 = *param_1;
        if (uVar5 == 0) {
            *param_1 = uVar1 | 1;
            (*param_2)(param_3);
            uVar5 = *param_1;
            *param_1 = 0xffffffff;
            LORelease();
            if (uVar5 == (uVar1 | 3)) {
                sk_clock_dispatch_18(uVar2, param_1, 6, 0);
                return;
            }
        } else {
            unsigned int uVar3 = uVar5 >> 2 & 0xffffff;
            if (((uVar5 >> 2 & 0xffffff) << 2 | 1) == uVar5) {
                uVar8 = sk_clock_reg_read(uVar2);
                unsigned int uVar1b = *param_1;
                if (uVar1b == uVar5) {
                    *param_1 = uVar3 << 2 | 3;
                    goto chain;
                }
            }
            while (1) {
chain:
                uVar6 = sk_slot_addr_65_61488(uVar3);
                if (uVar6 + 0x178 < uVar6) {
                    SoftwareBreakpoint(0x5519, 0x65e5c0); /* does not return */
                }
                sk_clock_reg_inc(uVar2, param_1, uVar8, uVar6, 0);
                uVar5 = *param_1;
                if (uVar5 == 0xffffffff) break;
            }
        }
    }
}

/*--------------------------------------------------------------------*/
/* FUN_0065e5c0 @ 0x0065e5c0
 * Ghidra: void FUN_0065e5c0(void)
 * Clears the timer-slot table at 0x6b5390.
 * Confidence: high (thin forward) */
void sk_timer_slot_clear_65e5c0(void)
{
    sk_rt_0065cbbc(0x6b5390);
}

/*--------------------------------------------------------------------*/
/* FUN_0065e6fc @ 0x0065e6fc
 * Ghidra: undefined8 FUN_0065e6fc(void)
 * Drives the one-shot notif slot at 0x6fe750 with the handler FUN_0065e748 and
 * returns the value written into _DAT_006fe758.
 * Confidence: high (thin forward) */
unsigned long sk_notif_oneshot_65e6fc(void)
{
    sk_notif_slot_65e454((unsigned int *)&DAT_006fe750,
                             (void (*)(unsigned long))sk_timer_alloc_65e748,
                             (unsigned long)&_DAT_006fe758);
    return _DAT_006fe758;
}

/*--------------------------------------------------------------------*/
/* FUN_0065e748 @ 0x0065e748
 * Ghidra: void FUN_0065e748(long *param_1)
 * Allocates a timer/clock node (FUN_0066ad54), installs it into the dispatch
 * table via FUN_0066a8c4 slot +0x48, and panics on failure (0x6a6b13/0x6a6b3e).
 * Confidence: medium */
void sk_timer_alloc_65e748(long *param_1)
{
    long lVar3 = sk_rt_0066ad54();
    if ((char *)param_1 + 8 < (char *)param_1) {
        SoftwareBreakpoint(0x5519, 0x65e7ac); /* does not return */
    }
    *param_1 = lVar3;
    if (lVar3 != 0) {
        sk_u128_t auVar4 = sk_rt_0066a8c4();
        char cVar2 = (*(char (**)(unsigned long, unsigned long))(auVar4.hi + 0x48))(
            auVar4.lo, (unsigned long)*param_1);
        if (cVar2 == '\0') {
            return;
        }
        sk_panic_2(0, 0x6a6b3e); /* does not return */
    }
    sk_panic_2(0, 0x6a6b13); /* does not return */
}

/*--------------------------------------------------------------------*/
/* FUN_0065e7cc @ 0x0065e7cc
 * Ghidra: void FUN_0065e7cc(void)
 * Ensures the dispatch table (_DAT_006fe760) is initialized to 0x6b6518 and
 * dispatches through slot +0.
 * Confidence: medium (indirect jumptable, treated as call) */
void sk_dispatch_slot0_65e7cc(void)
{
    if (_DAT_006fe760 == 0) {
        _DAT_006fe760 = (unsigned long)&DAT_006b6518;
    }
    (*(void (**)(void))(*(unsigned long *)_DAT_006fe760))();
}

/*--------------------------------------------------------------------*/
/* FUN_0065e7f0 @ 0x0065e7f0
 * Ghidra: void FUN_0065e7f0(long param_1, int param_2)
 * Sends a schedule/notify message for thread param_1 via CallSupervisor(3):
 * when the thread's 0x48 byte bit3 is clear and param_2 nonzero. Maps the
 * error code to an L4 error string (thunk_FUN_0067aa00 into the x8 slot).
 * Confidence: low (CallSupervisor(3) frame build). */
void sk_sched_msg_send_65e7f0(unsigned long param_1, int param_2)
{
    unsigned long local_38 = _DAT_006b5ed0;
    if ((param_2 == 0) || (((*(unsigned char *)(param_1 + 0x48) >> 3) & 1) != 0)) {
        return;
    }
    long lVar3 = sk_rt_0066ad54();
    if (lVar3 != 0) {
        unsigned long uVar4 = sk_tcb_cap_65_6239c(param_1);
        unsigned char *puVar1 = (unsigned char *)tpidrro_el0;
        puVar1[5] = 0; puVar1[3] = 0; puVar1[2] = 0; puVar1[1] = 2; puVar1[0] = 0;
        puVar1[4] = 0; puVar1[7] = 0; puVar1[6] = 0;
        CallSupervisor(3);
        if ((uVar4 & 0xff) != 0) {
            unsigned char bVar2 = sk_rt_00684940(uVar4, (unsigned char *)0, 0x200);
            const char *pcVar5;
            if (bVar2 < 10) {
                switch (bVar2) {
                default: pcVar5 = "Success"; break;
                case 1: pcVar5 = "Preempted"; break;
                case 2: pcVar5 = "Canceled"; break;
                case 3: pcVar5 = "Truncated"; break;
                case 4: pcVar5 = "CapInvalid"; break;
                case 5: pcVar5 = "SlotInvalid"; break;
                case 6: pcVar5 = "MethodInvalid"; break;
                case 7: pcVar5 = "ArgumentInvalid"; break;
                case 8: pcVar5 = "OperationInvalid"; break;
                case 9: pcVar5 = "PermissionInvalid"; break;
                }
                sk_memmove((void *)0, pcVar5, 0x20);
                return;
            }
            sk_memmove((void *)0, (const void *)&DAT_00689c40, 0x20);
            sk_rt_0064effc((void *)0, 0x20);
            return;
        }
        sk_rt_0068498c((unsigned char *)0, lVar3, (unsigned char *)(param_1 + 0x48));
    }
    if (_DAT_006b5ed0 == local_38) {
        sk_rt_006860f4(lVar3);
        return;
    }
    sk_fatal(0); /* does not return */
}

/*--------------------------------------------------------------------*/
/* FUN_0065ea38 @ 0x0065ea38
 * Ghidra: undefined8 FUN_0065ea38(code *param_1, ulong param_2,
 *                                undefined1 *param_3, undefined8 param_4)
 * Runs the callback param_1 in the context of thread param_2: when param_2 is
 * the current thread it calls param_1 directly with the thread's cap word
 * (param_2+0x28); otherwise it first verifies the target is in the same
 * protection domain (FUN_00660ba8) and, when the flag byte param_3 is given,
 * marks it busy and spins on CallSupervisor(4) while the callee re-schedules.
 * Confidence: medium */
unsigned long sk_exec_in_ctx_65ea38(sk_u128_t (*param_1)(unsigned long, unsigned long),
                                    unsigned long param_2, unsigned char *param_3,
                                    unsigned long param_4)
{
    unsigned long uVar2 = sk_cur_tcb_65_61318();
    unsigned long uVar4, lVar5;
    if (param_2 == uVar2) {
        uVar4 = uVar2;
        if (uVar2 + 0x178 < param_2) {
            SoftwareBreakpoint(0x5519, 0x65eafc); /* does not return */
        }
    } else {
        uVar4 = param_2;
        if (param_3 != 0) {
            lVar5 = *(long *)(uVar2 + 0x70);
            uVar2 = sk_preempt_acq_65_60ba8(param_2, lVar5);
            if ((uVar2 & 1) == 0) {
                *param_3 = 1;
                return 0;
            }
            goto invoke;
        }
    }
    lVar5 = *(long *)(uVar4 + 0x28);
invoke:
    sk_u128_t r3 = (*param_1)(lVar5, param_4);
    unsigned long uVar3 = r3.lo;
    uVar2 = sk_cur_tcb_65_61318();
    if ((param_3 != 0) && (param_2 != uVar2)) {
        do {
            CallSupervisor(4);
        } while (lVar5 == 1);
    }
    return uVar3;
}

/*--------------------------------------------------------------------*/
/* FUN_0065eafc @ 0x0065eafc
 * Ghidra: void FUN_0065eafc(long param_1)
 * Clears the "blocked" bit (0x48 bit3) of thread param_1, logging the event
 * (FUN_0065e5cc code 0xd for the current thread, 0xc otherwise) under the
 * preemption lock.
 * Confidence: medium */
void sk_thread_unblock_65eafc(unsigned long param_1)
{
    unsigned long local_28 = _DAT_006b5ed0;
    if (((*(unsigned char *)(param_1 + 0x48) >> 3) & 1) != 0) {
        unsigned long lVar2 = sk_cur_tcb_65_61318();
        unsigned char local_39 = 0;
        if (param_1 == lVar2) {
            sk_err_frame_65_e5cc(param_1, 0xd, (unsigned long *)&local_39, 1);
            *(unsigned long *)(param_1 + 0x48) &= 0xfffffffffffffff7;
        } else {
            int iVar1;
            do {
                iVar1 = (int)sk_lock_acq_65_61348(&local_39);
            } while (iVar1 == 0);
            sk_err_frame_65_e5cc(param_1, 0xc, (unsigned long *)&local_39, 1);
            *(unsigned long *)(param_1 + 0x48) &= 0xfffffffffffffff7;
            sk_lock_rel_65_613d0(&local_39);
        }
    }
    if (_DAT_006b5ed0 == local_28) {
        return;
    }
    sk_fatal(0); /* does not return */
}

/*--------------------------------------------------------------------*/
/* FUN_0065ec08 @ 0x0065ec08
 * Ghidra: void FUN_0065ec08(void)
 * Dispatches through the clock/timer dispatch table slot +0x10
 * (_DAT_006fe760, lazily initialized to 0x6b6518).
 * Confidence: medium (indirect jumptable, treated as call) */
void sk_dispatch_slot10_65ec08(void)
{
    if (_DAT_006fe760 == 0) {
        _DAT_006fe760 = (unsigned long)&DAT_006b6518;
    }
    (*(void (**)(void))(*(unsigned long *)(_DAT_006fe760 + 0x10)))();
}

/*--------------------------------------------------------------------*/
/* FUN_0065ecec @ 0x0065ecec
 * Ghidra: void FUN_0065ecec(void)
 * Dispatches through the clock/timer dispatch table slot +0x18.
 * Confidence: medium (indirect jumptable) */
void sk_dispatch_slot18_65ecec(void)
{
    if (_DAT_006fe760 == 0) {
        _DAT_006fe760 = (unsigned long)&DAT_006b6518;
    }
    (*(void (**)(void))(*(unsigned long *)(_DAT_006fe760 + 0x18)))();
}

/*--------------------------------------------------------------------*/
/* FUN_0065ec2c @ 0x0065ec2c
 * Ghidra: void FUN_0065ec2c(uint param_1, undefined8 param_2, undefined8 param_3,
 *                          long param_4, uint param_5)
 * Emits an error/log frame (FUN_0065e5cc) with a combined code = (param_1&0xf)<<12
 * | (param_5?2:1), then panics unless the returned status is the expected one.
 * Confidence: medium
 * Notes: panic strings 0x6a68ad / 0x6a68d4. */
void sk_log_panic_65ec2c(unsigned int param_1, unsigned long param_2, unsigned long param_3,
                         unsigned long param_4, unsigned int param_5)
{
    unsigned long local_28 = _DAT_006b5ed0;
    unsigned int uVar4 = 1;
    if (param_5 != 0) {
        uVar4 = 2;
    }
    unsigned long local_38 = param_2, uStack_30 = param_3;
    if (param_4 == 0) {
        param_4 = sk_cur_tcb_65_61318();
    }
    unsigned long uVar2 = sk_err_frame_65_e5cc(param_4, (unsigned short)(uVar4 | (param_1 & 0xf) << 0xc),
                                         &local_38, 1);
    unsigned long uVar1 = 0;
    if (uVar2 != 5) {
        uVar1 = uVar2;
    }
    if (uVar1 < 4) {
        if (((param_5 & 1) != 0) || (uVar1 != 3)) {
            if (_DAT_006b5ed0 == local_28) {
                return;
            }
            sk_fatal(0); /* does not return */
        }
        sk_panic_2(0, 0x6a68d4); /* does not return */
    } else {
        sk_panic_2(0, 0x6a68ad); /* does not return */
    }
}

/*--------------------------------------------------------------------*/
/* FUN_0065ed10 @ 0x0065ed10
 * Ghidra: void FUN_0065ed10(uint param_1, undefined8 param_2, uint param_3, ulong param_4)
 * Counts a clock event: bumps the per-clock counter at 0x6fe768 + param_1*8
 * under LORelease, then emits an error frame (code (param_3 | param_1<<12) & 0xffff).
 * Confidence: medium
 * Notes: panic strings 0x6a68f1 on bad kind; only kinds 3..6 accepted. */
void sk_clock_event_65ed10(unsigned int param_1, unsigned long param_2, unsigned int param_3,
                           unsigned long param_4)
{
    unsigned long local_48 = _DAT_006b5ed0;
    unsigned long uVar3 = sk_cur_tcb_65_61318();
    if ((int)param_3 < 5) {
        if (param_3 == 3) goto count;
        if (param_3 != 4) {
            sk_panic_2(0, 0x6a68f1); /* does not return */
        }
        if (param_4 != 0) {
            param_3 = 4;
            uVar3 = param_4;
            goto count;
        }
    } else if (param_3 != 5) {
        if (param_3 != 6) {
            sk_panic_2(0, 0x6a68f1); /* does not return */
        }
        goto count;
    }
    param_3 = 5;
count:
    long lVar4 = sk_rt_0065be08(0x6fe768, 1, 4);
    long *plVar1 = (long *)(lVar4 + (unsigned long)param_1 * 8);
    *plVar1 += 1;
    LORelease();
    unsigned long uStack_50 = *(unsigned long *)(lVar4 + (unsigned long)param_1 * 8);
    unsigned long local_58 = param_2;
    if (uVar3 + 0x178 < uVar3) {
        SoftwareBreakpoint(0x5519, 0x65ee2c); /* does not return */
    }
    long lVar4b = sk_err_frame_65_e5cc(uVar3, (unsigned short)((param_3 | param_1 << 0xc) & 0xffff),
                                 &local_58, 0);
    if (_DAT_006b5ed0 == local_48) {
        return;
    }
    sk_fatal(lVar4b != 5); /* does not return */
}

/*--------------------------------------------------------------------*/
/* FUN_0065ee30 @ 0x0065ee30
 * Ghidra: void FUN_0065ee30(void)
 * Dispatches through the clock/timer dispatch table slot +0x20.
 * Confidence: medium (indirect jumptable) */
void sk_dispatch_slot20_65ee30(void)
{
    if (_DAT_006fe760 == 0) {
        _DAT_006fe760 = (unsigned long)&DAT_006b6518;
    }
    (*(void (**)(void))(*(unsigned long *)(_DAT_006fe760 + 0x20)))();
}

/*--------------------------------------------------------------------*/
/* FUN_0065ee54 @ 0x0065ee54
 * Ghidra: void FUN_0065ee54(undefined8 param_1)
 * Emits a minimal error frame (code 7) for thread param_1 via FUN_0065e5cc.
 * Confidence: high (thin forward) */
void sk_err_frame_7_65ee54(unsigned long param_1)
{
    unsigned long local_18 = _DAT_006b5ed0;
    unsigned long local_28 = 0, uStack_20 = 0;
    sk_err_frame_65_e5cc(param_1, 7, &local_28, 1);
    if (_DAT_006b5ed0 == local_18) {
        return;
    }
    sk_fatal(0); /* does not return */
}

/*--------------------------------------------------------------------*/
/* FUN_0065ef24 @ 0x0065ef24
 * Ghidra: undefined1 [16] FUN_0065ef24(ulong param_1, ushort *param_2)
 * Builds and sends a message via CallSupervisor(0): the first word of param_2
 * (the tag) plus two 64-bit payload words at param_2+8/+0x10 are copied into
 * the tpidrro_el0 message frame; the result carries the tag back and stores
 * the tag into param_2[0xc] when ((byte)param_2[0x10] & (param_1==8))==0.
 * Confidence: low (message-frame builder). */
sk_u128_t sk_msg_send_65ef24(unsigned long param_1, unsigned short *param_2)
{
    unsigned short uVar5 = *param_2;
    unsigned long uVar3 = *(unsigned long *)(param_2 + 4);
    unsigned long uVar4 = *(unsigned long *)(param_2 + 8);
    unsigned char *puVar7 = (unsigned char *)tpidrro_el0;
    puVar7[4] = 0; puVar7[2] = 0; puVar7[5] = 0; puVar7[3] = 0; puVar7[6] = 0; puVar7[7] = 0;
    puVar7[0] = (unsigned char)uVar5;
    unsigned char uVar6 = (unsigned char)(uVar5 >> 8);
    puVar7[1] = uVar6;
    puVar7[0xd] = (unsigned char)(uVar3 >> 0x28);
    puVar7[8] = (unsigned char)uVar3;
    puVar7[0xb] = (unsigned char)(uVar3 >> 0x18);
    puVar7[10] = (unsigned char)(uVar3 >> 0x10);
    puVar7[9] = (unsigned char)(uVar3 >> 8);
    puVar7[0xc] = (unsigned char)(uVar3 >> 0x20);
    puVar7[0xf] = (unsigned char)(uVar3 >> 0x38);
    puVar7[0xe] = (unsigned char)(uVar3 >> 0x30);
    puVar7[0x15] = (unsigned char)(uVar4 >> 0x28);
    puVar7[0x10] = (unsigned char)uVar4;
    puVar7[0x13] = (unsigned char)(uVar4 >> 0x18);
    puVar7[0x12] = (unsigned char)(uVar4 >> 0x10);
    puVar7[0x11] = (unsigned char)(uVar4 >> 8);
    puVar7[0x14] = (unsigned char)(uVar4 >> 0x20);
    puVar7[0x17] = (unsigned char)(uVar4 >> 0x38);
    puVar7[0x16] = (unsigned char)(uVar4 >> 0x30);
    CallSupervisor(0);
    puVar7[0] = (unsigned char)uVar5;
    puVar7[7] = 0; puVar7[6] = 0; puVar7[5] = 0; puVar7[4] = 0; puVar7[3] = 0; puVar7[2] = 0;
    puVar7[1] = uVar6;
    /* ((byte)param_2[0x10] & param_1 == 8) == 0  (Ghidra C-precedence: &(param_1==8)) */
    bool bVar8 = (((unsigned char)param_2[0x10] & (param_1 == 8)) == 0);
    unsigned long uVar1 = 0, uVar2 = 0;
    if (bVar8) {
        uVar1 = (unsigned long)uVar5;
        uVar2 = param_1;
    }
    *(unsigned long *)(param_2 + 0xc) = uVar1;
    sk_u128_t auVar9 = { uVar2, 0 };
    return auVar9;
}

/*--------------------------------------------------------------------*/
/* FUN_0065f058 @ 0x0065f058
 * Ghidra: void FUN_0065f058(void)
 * Dispatches through the clock/timer dispatch table slot +8.
 * Confidence: medium (indirect jumptable) */
void sk_dispatch_slot8_65f058(void)
{
    if (_DAT_006fe760 == 0) {
        _DAT_006fe760 = (unsigned long)&DAT_006b6518;
    }
    (*(void (**)(void))(*(unsigned long *)(_DAT_006fe760 + 8)))();
}

/*--------------------------------------------------------------------*/
/* FUN_0065f07c @ 0x0065f07c
 * Ghidra: void FUN_0065f07c(ulong param_1, undefined1 *param_2)
 * Complex thread-context setter: switches on param_2 (0x6/0x8/0x9/0xd) and for
 * each kind builds a CallSupervisor(3) message frame (thread id + capability
 * words from the 0x6a89af0/0x6a89ae0 constant pairs), then copies the resolved
 * allocator handle (FUN_0066ad54) and the clock global (DAT_006b6fd4..) into the
 * frame and sends CallSupervisor(0). Errors map to L4 error strings.
 * Confidence: low (heavy frame builder; panics 0x6a6aa4). */
void sk_ctx_set_65f07c(unsigned long param_1, unsigned char *param_2)
{
    unsigned long local_38 = _DAT_006b5ed0;
    unsigned long uVar6 = sk_rt_0066ad54();
    unsigned long uVar3 = uRam0000000000689af8;
    unsigned long uVar2 = _DAT_00689af0;
    int iVar13 = (int)param_2;
    unsigned char *frame;
    if (iVar13 < 9) {
        if (iVar13 != 6) {
            if (iVar13 != 8) goto bad_kind;
            frame = (unsigned char *)tpidrro_el0;
            /* frame[0..0xf] = little-endian copy of (uVar2, uVar3) */
            frame[0] = (unsigned char)uVar2;
            frame[1] = (unsigned char)(uVar2 >> 8);
            frame[2] = (unsigned char)(uVar2 >> 0x10);
            frame[3] = (unsigned char)(uVar2 >> 0x18);
            frame[4] = (unsigned char)(uVar2 >> 0x20);
            frame[5] = (unsigned char)(uVar2 >> 0x28);
            frame[6] = (unsigned char)(uVar2 >> 0x30);
            frame[7] = (unsigned char)(uVar2 >> 0x38);
            frame[8] = (unsigned char)uVar3;
            frame[9] = (unsigned char)(uVar3 >> 8);
            frame[10] = (unsigned char)(uVar3 >> 0x10);
            frame[0xb] = (unsigned char)(uVar3 >> 0x18);
            frame[0xc] = (unsigned char)(uVar3 >> 0x20);
            frame[0xd] = (unsigned char)(uVar3 >> 0x28);
            frame[0xe] = (unsigned char)(uVar3 >> 0x30);
            frame[0xf] = (unsigned char)(uVar3 >> 0x38);
            frame[0x10] = 0; frame[0x11] = 0; frame[0x12] = 0; frame[0x13] = 0;
            frame[0x14] = 0; frame[0x15] = 0; frame[0x16] = 0; frame[0x17] = 0;
            CallSupervisor(3);
            if ((param_1 & 0xff) != 0) {
                sk_rt_00684c0c(param_1, frame, 1);
                goto kind9;
            }
            goto common;
        }
    } else {
kind9:
        uVar3 = uRam0000000000689ae8;
        uVar2 = _DAT_00689ae0;
        if ((int)param_2 == 9) {
            frame = (unsigned char *)tpidrro_el0;
            frame[0] = (unsigned char)uVar2;
            frame[1] = (unsigned char)(uVar2 >> 8);
            frame[2] = (unsigned char)(uVar2 >> 0x10);
            frame[3] = (unsigned char)(uVar2 >> 0x18);
            frame[4] = (unsigned char)(uVar2 >> 0x20);
            frame[5] = (unsigned char)(uVar2 >> 0x28);
            frame[6] = (unsigned char)(uVar2 >> 0x30);
            frame[7] = (unsigned char)(uVar2 >> 0x38);
            frame[8] = (unsigned char)uVar3;
            frame[9] = (unsigned char)(uVar3 >> 8);
            frame[10] = (unsigned char)(uVar3 >> 0x10);
            frame[0xb] = (unsigned char)(uVar3 >> 0x18);
            frame[0xc] = (unsigned char)(uVar3 >> 0x20);
            frame[0xd] = (unsigned char)(uVar3 >> 0x28);
            frame[0xe] = (unsigned char)(uVar3 >> 0x30);
            frame[0xf] = (unsigned char)(uVar3 >> 0x38);
            frame[0x10] = 0; frame[0x11] = 0; frame[0x12] = 0; frame[0x13] = 0;
            frame[0x14] = 0; frame[0x15] = 0; frame[0x16] = 0; frame[0x17] = 0;
            CallSupervisor(3);
            if ((param_1 & 0xff) != 0) {
                unsigned char bVar5 = sk_rt_00684bc0(param_1, frame, 1);
                const char *pcVar7;
                if (9 < bVar5) {
                    sk_memmove(&_DAT_00689af0, (const void *)&DAT_00689c40, 0x20);
                    sk_rt_0064effc((void *)&_DAT_00689af0, 0x20);
                    return;
                }
                switch (bVar5) {
                default: pcVar7 = "Success"; break;
                case 1: pcVar7 = "Preempted"; break;
                case 2: pcVar7 = "Canceled"; break;
                case 3: pcVar7 = "Truncated"; break;
                case 4: pcVar7 = "CapInvalid"; break;
                case 5: pcVar7 = "SlotInvalid"; break;
                case 6: pcVar7 = "MethodInvalid"; break;
                case 7: pcVar7 = "ArgumentInvalid"; break;
                case 8: pcVar7 = "OperationInvalid"; break;
                case 9: pcVar7 = "PermissionInvalid"; break;
                }
                sk_memmove(&_DAT_00689af0, pcVar7, 0x20);
                return;
            }
common:
            /* store the allocator handle at frame+0x1c0.. */
            frame[0x1c0] = (unsigned char)uVar6;
            frame[0x1c1] = (unsigned char)(uVar6 >> 8);
            frame[0x1c2] = (unsigned char)(uVar6 >> 0x10);
            frame[0x1c3] = (unsigned char)(uVar6 >> 0x18);
            frame[0x1c4] = (unsigned char)(uVar6 >> 0x20);
            frame[0x1c5] = (unsigned char)(uVar6 >> 0x28);
            frame[0x1c6] = (unsigned char)(uVar6 >> 0x30);
            frame[0x1c7] = (unsigned char)(uVar6 >> 0x38);
            /* clock global words */
            unsigned short uVar4 = _DAT_006b6fd4;
            unsigned long uVar9 = (unsigned long)_DAT_006b6fd4;
            unsigned long uVar10 = (unsigned long)DAT_006b6fd7;
            unsigned long uVar12 = (unsigned long)DAT_006b6fd6;
            unsigned int uVar1 = (unsigned int)_DAT_006b6fd8;
            unsigned int uVar8 = (unsigned int)DAT_006b6fda;
            unsigned int uVar11 = (unsigned int)DAT_006b6fdb;
            frame[0] = 0x40;
            frame[1] = 0; frame[2] = 3; frame[3] = 0; frame[4] = 0; frame[5] = 0;
            frame[6] = 0; frame[7] = 0;
            CallSupervisor(0);
            frame[0] = 0x40;
            frame[7] = 0; frame[6] = 0; frame[5] = 0; frame[4] = 0; frame[3] = 0;
            frame[2] = 3; frame[1] = 0;
            if ((uVar4 & 0xff) != 0) {
                unsigned long combined = (uVar12 << 0x10 | uVar10 << 0x18 | uVar9) |
                    ((unsigned long)(uVar8 << 0x10 | uVar11 << 0x18 | uVar1) << 0x20);
                sk_rt_00684c58(combined, frame);
bad_kind:
                sk_panic_2(0, 0x6a6aa4); /* does not return */
            }
            if (_DAT_006b5ed0 == local_38) {
                sk_rt_006860f4(uVar6, 0);
                return;
            }
            sk_fatal(0); /* does not return */
        }
        if ((int)param_2 != 0xd) goto bad_kind;
    }
    if (_DAT_006b5ed0 == local_38) {
        return;
    }
    sk_fatal(0); /* does not return */
}

/*--------------------------------------------------------------------*/
/* FUN_0065f428 @ 0x0065f428
 * Ghidra: void FUN_0065f428(byte param_1)
 * Maps an L4 error code byte to its string and copies it (0x20 bytes) into the
 * caller's stack slot (thunk_FUN_0067aa00 / FUN_0064effc).
 * Confidence: high (error-string mapper) */
void sk_err_str_65f428(unsigned char param_1)
{
    const char *pcVar1;
    if (9 < param_1) {
        sk_memmove((void *)0x10, (const void *)&DAT_00689c40, 0x20);
        sk_rt_0064effc((void *)0x10, 0x20);
        return;
    }
    switch (param_1) {
    default: pcVar1 = "Success"; break;
    case 1: pcVar1 = "Preempted"; break;
    case 2: pcVar1 = "Canceled"; break;
    case 3: pcVar1 = "Truncated"; break;
    case 4: pcVar1 = "CapInvalid"; break;
    case 5: pcVar1 = "SlotInvalid"; break;
    case 6: pcVar1 = "MethodInvalid"; break;
    case 7: pcVar1 = "ArgumentInvalid"; break;
    case 8: pcVar1 = "OperationInvalid"; break;
    case 9: pcVar1 = "PermissionInvalid"; break;
    }
    sk_memmove((void *)0x10, pcVar1, 0x20);
}

/*--------------------------------------------------------------------*/
/* FUN_0065f448 @ 0x0065f448
 * Ghidra: void FUN_0065f448(void)
 * Error-string mapper driven by the unaff_w20 register (the x8 return slot);
 * equivalent to FUN_0065f428 but reads the code from a register artifact.
 * Confidence: low (register-artifact twin of FUN_0065f428). */
void sk_err_str_w20_65f448(void)
{
    unsigned char code = (unsigned char)0; /* unaff_w20: code from register artifact */
    if (9 < code) {
        sk_memmove((void *)0, (const void *)&DAT_00689c40, 0x20);
        sk_rt_0064effc((void *)0, 0x20);
        return;
    }
    const char *pcVar1;
    switch (code) {
    default: pcVar1 = "Success"; break;
    case 1: pcVar1 = "Preempted"; break;
    case 2: pcVar1 = "Canceled"; break;
    case 3: pcVar1 = "Truncated"; break;
    case 4: pcVar1 = "CapInvalid"; break;
    case 5: pcVar1 = "SlotInvalid"; break;
    case 6: pcVar1 = "MethodInvalid"; break;
    case 7: pcVar1 = "ArgumentInvalid"; break;
    case 8: pcVar1 = "OperationInvalid"; break;
    case 9: pcVar1 = "PermissionInvalid"; break;
    }
    sk_memmove((void *)0, pcVar1, 0x20);
}

/*--------------------------------------------------------------------*/
/* FUN_0065f454 @ 0x0065f454
 * Ghidra: void FUN_0065f454(void)
 * No-op.
 * Confidence: high (trivial) */
void sk_noop_65f454(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_0065f468 @ 0x0065f468
 * Ghidra: void FUN_0065f468(long param_1, undefined8 param_2, undefined8 param_3,
 *                          ulong param_4)
 * Boot-log formatter: appends a series of label strings (FUN_0065f834) and the
 * sanitized 4-char fields at param_1+0xd8..+0xe4 (FUN_0065f8e8), then walks the
 * region table at param_1+0x158 (stride 0x10, count from the tag word) appending
 * a label per region. Only runs when param_4 bit0 is clear.
 * Confidence: medium */
void sk_boot_log_65f468(unsigned long param_1, unsigned long param_2, unsigned long param_3,
                        unsigned long param_4)
{
    unsigned long local_50 = param_2, uStack_48 = param_3;
    sk_strbuf_append_65f834(&local_50, 0, 0x6a6b74);
    if ((param_4 & 1) == 0) {
        sk_strbuf_append_65f834(&local_50, 1, 0x6a6b9c);
        sk_strbuf_append_65f834(&local_50, 1, 0x6a6bb9);
        sk_strbuf_append_65f834(&local_50, 1, 0x6a6bd2);
        sk_tag_sanitize_65f8e8(*(unsigned int *)(param_1 + 0xd8));
        sk_tag_sanitize_65f8e8(*(unsigned int *)(param_1 + 0xe0));
        sk_tag_sanitize_65f8e8(*(unsigned int *)(param_1 + 0xdc));
        sk_tag_sanitize_65f8e8(*(unsigned int *)(param_1 + 0xe4));
        sk_strbuf_append_65f834(&local_50, 1, 0x6a6bf1);
        sk_strbuf_append_65f834(&local_50, 1, 0x6a6c20);
        sk_strbuf_append_65f834(&local_50, 1, 0x6a6c48);
        sk_strbuf_append_65f834(&local_50, 1, 0x6a6c6f);
        sk_strbuf_append_65f834(&local_50, 1, 0x6a6c89);
        sk_strbuf_append_65f834(&local_50, 1, 0x6a6ca4);
        sk_strbuf_append_65f834(&local_50, 1, 0x6a6cc1);
        sk_strbuf_append_65f834(&local_50, 1, 0x6a6cd9);
        sk_strbuf_append_65f834(&local_50, 1, 0x6a6cf1);
        sk_strbuf_append_65f834(&local_50, 1, 0x6a6d0f);
        sk_strbuf_append_65f834(&local_50, 1, 0x6a6d27);
        unsigned long uVar4 = param_1 + 0x160;
        long lVar5 = -0xc;
        do {
            if (param_1 + 0x1b8 < uVar4) {
                SoftwareBreakpoint(0x5519, 0x65f834); /* does not return */
            }
            unsigned long uVar1 = param_1 + 0x158 +
                (*(unsigned long *)(uVar4 - 8) >> 0x30) * 0x10;
            if ((2 < *(unsigned long *)(uVar4 - 8) >> 0x31) || (uVar1 == 0)) {
                return;
            }
            if ((uVar1 < param_1 + 0x158) || (param_1 + 0x1b8 < uVar1 + 0x10) ||
                (uVar1 + 0xf < uVar1)) {
                SoftwareBreakpoint(0x5519, 0x65f834); /* does not return */
            }
            sk_strbuf_append_65f834(&local_50, 1, 0x6a6d39);
            uVar4 += 8;
            lVar5 += 1;
        } while (lVar5 != -1);
    }
}

/*--------------------------------------------------------------------*/
/* FUN_0065fa24 @ 0x0065fa24
 * Ghidra: long FUN_0065fa24(undefined8 param_1, ulong param_2, ulong param_3, uint param_4)
 * Message-register builder: copies param_2 bytes from param_1 into the
 * tpidrro_el0 message slot selected by param_3 (bounded to 0x36 slots, total
 * 0x1b8 bytes), optionally appends a NUL when param_4!=0, and returns the new
 * slot count. Panics on overflow (0x6a6e6f / 0x6a6e43).
 * Confidence: low (tpidrro message-region arithmetic). */
long sk_msg_reg_build_65fa24(unsigned long param_1, unsigned long param_2, unsigned long param_3,
                             unsigned int param_4)
{
    if (param_3 < 0x37) {
        unsigned long uVar5 = param_3 * -8 + 0x1b8;
        if (param_2 + param_4 <= uVar5) {
            unsigned char *puVar2 = (unsigned char *)tpidrro_el0;
            if (param_2 <= uVar5) {
                unsigned char *puVar1 = puVar2 + param_3 * 8 + 8;
                sk_memmove(puVar1, (const void *)param_1, param_2);
                if (puVar1 <= puVar1 + param_2) {
                    if (param_4 != 0) {
                        puVar1 = puVar1 + param_2;
                        if ((puVar2 + 0x1c0 <= puVar1) || (puVar1 < puVar2)) {
                            SoftwareBreakpoint(0x5519, 0x65fa78); /* does not return */
                        }
                        *puVar1 = 0;
                    }
                    return param_3 + (param_2 + param_4 + 7 >> 3);
                }
            }
            SoftwareBreakpoint(0x5519, 0x65fa78); /* does not return */
        }
        sk_panic_2(0, 0x6a6e6f); /* does not return */
    } else {
        sk_panic_2(0, 0x6a6e43); /* does not return */
    }
}

/*--------------------------------------------------------------------*/
/* FUN_0065fb08 @ 0x0065fb08
 * Ghidra: long FUN_0065fb08(ulong param_1, ulong param_2, ulong param_3)
 * Copies param_2 bytes from the tpidrro_el0 message slot param_3 into param_1
 * and returns the advanced slot count. Panics on overflow (0x6a6e6f/0x6a6e43).
 * Confidence: low */
long sk_msg_reg_copy_65fb08(unsigned long param_1, unsigned long param_2, unsigned long param_3)
{
    if (param_3 < 0x37) {
        if (param_2 <= param_3 * -8 + 0x1b8) {
            long lVar1 = tpidrro_el0;
            sk_memmove((void *)param_1, (const void *)(lVar1 + param_3 * 8 + 8), param_2);
            if (param_1 <= param_1 + param_2) {
                return param_3 + (param_2 + 7 >> 3);
            }
            SoftwareBreakpoint(0x5519, 0x65fbb0); /* does not return */
        }
        sk_panic_2(0, 0x6a6e6f); /* does not return */
    } else {
        sk_panic_2(0, 0x6a6e43); /* does not return */
    }
}

/*--------------------------------------------------------------------*/
/* FUN_0065fbb0 @ 0x0065fbb0
 * Ghidra: void FUN_0065fbb0(uint param_1, undefined8 param_2)
 * Stores an 8-byte value param_2 into the tpidrro_el0 message slot param_1
 * (little-endian). Panics when param_1 >= 0x37 (0x6a6db3).
 * Confidence: medium */
void sk_msg_slot_put_65fbb0(unsigned int param_1, unsigned long param_2)
{
    if (param_1 < 0x37) {
        long lVar1 = tpidrro_el0;
        lVar1 += (unsigned long)param_1 * 8;
        *(char *)(lVar1 + 8) = (char)param_2;
        *(char *)(lVar1 + 0xd) = (char)(param_2 >> 0x28);
        *(char *)(lVar1 + 0xb) = (char)(param_2 >> 0x18);
        *(char *)(lVar1 + 10) = (char)(param_2 >> 0x10);
        *(char *)(lVar1 + 9) = (char)(param_2 >> 8);
        *(char *)(lVar1 + 0xc) = (char)(param_2 >> 0x20);
        *(char *)(lVar1 + 0xf) = (char)(param_2 >> 0x38);
        *(char *)(lVar1 + 0xe) = (char)(param_2 >> 0x30);
        return;
    }
    sk_panic_2(0, 0x6a6db3); /* does not return */
}

/*--------------------------------------------------------------------*/
/* FUN_0065fc28 @ 0x0065fc28
 * Ghidra: ulong FUN_0065fc28(uint param_1)
 * Reads an 8-byte value from the tpidrro_el0 message slot param_1
 * (little-endian). Panics when param_1 >= 0x37 (0x6a6de3).
 * Confidence: medium */
unsigned long sk_msg_slot_get_65fc28(unsigned int param_1)
{
    if (param_1 < 0x37) {
        long lVar1 = tpidrro_el0;
        lVar1 += (unsigned long)param_1 * 8;
        return (unsigned long)*(unsigned char *)(lVar1 + 10) << 0x10 |
               (unsigned long)*(unsigned char *)(lVar1 + 0xb) << 0x18 |
               (unsigned long)*(unsigned short *)(lVar1 + 8) |
               (unsigned long)((unsigned int)*(unsigned char *)(lVar1 + 0xe) << 0x10 |
                               (unsigned int)*(unsigned char *)(lVar1 + 0xf) << 0x18 |
                               (unsigned int)*(unsigned short *)(lVar1 + 0xc)) << 0x20;
    }
    sk_panic_2(0, 0x6a6de3); /* does not return */
}

/*--------------------------------------------------------------------*/
/* FUN_0065fca8 @ 0x0065fca8
 * Ghidra: void FUN_0065fca8(uint param_1, undefined8 param_2)
 * Stores an 8-byte value param_2 into the second message region at
 * tpidrro_el0 + param_1*8 + 0x1c0 (little-endian), bounds-checked against
 * 0x1e0. Panics when param_1 > 3 (0x6a6e13).
 * Confidence: medium */
void sk_msg2_slot_put_65fca8(unsigned int param_1, unsigned long param_2)
{
    if (3 < param_1) {
        sk_panic_2(0, 0x6a6e13); /* does not return */
    }
    long lVar2 = tpidrro_el0;
    long lVar1 = lVar2 + (unsigned long)param_1 * 8;
    if ((unsigned char *)(lVar1 + 0x1c8) <= (unsigned char *)(lVar2 + 0x1e0) &&
        (unsigned char *)(lVar1 + 0x1c0) <= (unsigned char *)(lVar1 + 0x1c8)) {
        *(unsigned char *)(lVar1 + 0x1c0) = (char)param_2;
        *(char *)(lVar1 + 0x1c5) = (char)(param_2 >> 0x28);
        *(char *)(lVar1 + 0x1c3) = (char)(param_2 >> 0x18);
        *(char *)(lVar1 + 0x1c2) = (char)(param_2 >> 0x10);
        *(char *)(lVar1 + 0x1c1) = (char)(param_2 >> 8);
        *(char *)(lVar1 + 0x1c4) = (char)(param_2 >> 0x20);
        *(char *)(lVar1 + 0x1c7) = (char)(param_2 >> 0x38);
        *(char *)(lVar1 + 0x1c6) = (char)(param_2 >> 0x30);
        return;
    }
    SoftwareBreakpoint(0x5519, 0x65fd14); /* does not return */
}

/*--------------------------------------------------------------------*/
/* FUN_0065fd3c @ 0x0065fd3c
 * Ghidra: ulong FUN_0065fd3c(ulong param_1)
 * Extracts the 3-bit level field (bits 6..8).
 * Confidence: high (bit extract) */
unsigned long sk_bits_level_65fd3c(unsigned long param_1)
{
    return param_1 >> 6 & 7;
}

/*--------------------------------------------------------------------*/
/* FUN_0065fd44 @ 0x0065fd44
 * Ghidra: ulong FUN_0065fd44(ulong param_1)
 * Extracts the low 6-bit field.
 * Confidence: high (bit extract) */
unsigned long sk_bits_low6_65fd44(unsigned long param_1)
{
    return param_1 & 0x3f;
}

/*--------------------------------------------------------------------*/
/* FUN_0065fd4c @ 0x0065fd4c
 * Ghidra: ulong FUN_0065fd4c(ulong param_1, ulong param_2, uint param_3, int param_4)
 * Packs a descriptor word: low6 | level<<6 | kind<<16 | (param_4?0x1000:0).
 * Confidence: high (word pack) */
unsigned long sk_desc_pack_65fd4c(unsigned long param_1, unsigned long param_2,
                                  unsigned int param_3, int param_4)
{
    unsigned long uVar1 = 0x1000;
    if (param_4 == 0) {
        uVar1 = 0;
    }
    return param_1 & 0x3f | (param_2 & 7) << 6 | (unsigned long)param_3 << 0x10 | uVar1;
}

/*--------------------------------------------------------------------*/
/* FUN_0065fd70 @ 0x0065fd70
 * Ghidra: void FUN_0065fd70(void)
 * One-time clock/timer subsystem init: if the global init flag DAT_006fe770 is
 * clear, drains pending preemption (FUN_00661330 / FUN_00664cbc), bumps the
 * clock base counter (+0x38) and sets the flag.
 * Confidence: medium */
void sk_clock_init_65fd70(void)
{
    if ((DAT_006fe770 & 1) == 0) {
        unsigned int uVar2 = sk_flag_799_65_61330();
        if ((uVar2 & 1) == 0) {
            sk_rt_00664cbc(0);
        }
        long lVar1 = sk_bucket_base();
        *(short *)(lVar1 + 0x38) = *(short *)(lVar1 + 0x38) + 1;
        DAT_006fe770 = 1;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_0065f834 @ 0x0065f834
 * Ghidra: void FUN_0065f834(ulong *param_1, ulong param_2, undefined8 param_3)
 * String-buffer append into a (ptr,len) buffer: when the buffer has room
 * (len>1), optionally drains the pending character (FUN_0067ca6c) when param_2
 * bit0 is set, computes the appended length (clamped to len-1), validates the
 * pointer arithmetic, and advances the buffer. Panics on overflow.
 * Confidence: low (buffer advance with char drain; SoftwareBreakpoint 0x65f8d0) */
void sk_strbuf_append_65f834(unsigned long *param_1, unsigned long param_2, unsigned long param_3)
{
    unsigned long uVar6;
    if (1 < param_1[1]) {
        if ((param_2 & 1) == 0) {
            uVar6 = param_1[1];
        } else {
            unsigned int uVar5 = sk_rt_0067ca6c((unsigned long)0, 1, param_3, (unsigned long)0);
            if ((int)uVar5 < 0) {
                return;
            }
            uVar6 = param_1[1];
            if (uVar6 <= uVar5) {
                return;
            }
        }
        unsigned int uVar5 = sk_rt_0067ca6c(param_1[0], uVar6, param_3, (void *)0);
        uVar6 = (unsigned long)(uVar5 & ((unsigned int)uVar5 >> 0x1f ^ 0xffffffffU));
        unsigned long uVar2 = param_1[0];
        unsigned long uVar3 = param_1[1];
        if (uVar3 <= uVar6) {
            uVar6 = uVar3 - 1;
        }
        unsigned long uVar1 = uVar2 + uVar6;
        if ((uVar2 + uVar3 < uVar1) || (uVar1 < uVar2)) {
            SoftwareBreakpoint(0x5519, 0x65f8d0); /* does not return */
        }
        param_1[0] = uVar1;
        param_1[1] = uVar3 - uVar6;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_0065f8e8 @ 0x0065f8e8
 * Ghidra: undefined8 FUN_0065f8e8(undefined4 param_1)
 * Sanitizes a 4-character tag: any byte that is not alnum/underscore/dash/~ is
 * replaced with '?', then the 4 bytes are byte-reversed into the return value.
 * Confidence: medium (tag sanitize; SoftwareBreakpoint 0x65fa24). */
unsigned long sk_tag_sanitize_65f8e8(unsigned int param_1)
{
    unsigned int local_10 = param_1;
    unsigned int uStack_c = 0;
    long lVar4 = 0;
    /* Sanitize the 4 tag bytes in place: any byte that is not alphanumeric /
     * '_' / '-' / '~' becomes '?'. A NUL byte terminates (only when it is the
     * first byte is the whole field zero-filled). */
    do {
        unsigned char bVar2 = *(unsigned char *)((char *)&local_10 + lVar4);
        if (bVar2 == 0) {
            if (lVar4 != 0) {
                break;
            }
            /* leading NUL: fill all 4 bytes with '?' */
            for (long i = 0; i < 4; i++) {
                *(unsigned char *)((char *)&local_10 + i) = 0x3f;
            }
            lVar4 = 4;
            break;
        }
        unsigned int uVar6 = (unsigned int)bVar2;
        if (((9 < uVar6 - 0x30 && 0x19 < ((bVar2 & 0xffffffdf) - 0x41)) &&
            (0x3c < uVar6 - 0x23 ||
             ((1UL << ((uVar6 - 0x23) & 0x3f)) & 0x1000000000000587UL) == 0)) &&
            (uVar6 != 0x7e)) {
            *(unsigned char *)((char *)&local_10 + lVar4) = 0x3f;
        }
        lVar4 += 1;
    } while (lVar4 != 4);
    /* NUL-terminate at the current position. */
    *(unsigned char *)((char *)&local_10 + lVar4) = 0;
    /* Byte-reverse the (up to 4) tag bytes into the return value. */
    unsigned long local_8 = 0;
    unsigned char *dst = (unsigned char *)&local_8;
    unsigned char *src = (unsigned char *)&local_10 + lVar4;
    while (lVar4 != 0) {
        *dst = *src;
        lVar4 -= 1;
        src -= 1;
        dst += 1;
    }
    return local_8;
}

/*--------------------------------------------------------------------*/
/* FUN_0065fdb8 @ 0x0065fdb8
 * Ghidra: void FUN_0065fdb8(ulong *param_1, undefined8 param_2, ulong param_3,
 *                          long param_4, int param_5)
 * The cL4 thread-create path. Allocates a TCB stack block (via the allocator
 * table behind FUN_0066a8c4 and the _DAT_006fe7e0 pool), maps it through the
 * per-cpu allocator, installs the message/thread fields (0x130/0x138/0x140/
 * 0x168/0x170 window), sends the boot Capability and entry frames through
 * CallSupervisor(0) with the tpidrro_el0 message region, and returns the new
 * TCB in *param_1. On failure panics via FUN_0065c2f0 with 0x6a7135.
 * Confidence: low (very large frame builder; SoftwareBreakpoint 0x66047c). */
void sk_thread_create_65fdb8(unsigned long *param_1, unsigned long param_2, unsigned long param_3,
                             unsigned long param_4, int param_5)
{
    unsigned long local_70 = _DAT_006b5ed0;
    long lVar21 = sk_bucket_base();
    unsigned short *puVar32 = (unsigned short *)(lVar21 + 0x38);
    unsigned short uVar3 = *puVar32;
    *puVar32 = uVar3 + 1;
    if (uVar3 < 0x400) {
        unsigned long uVar22 = sk_rt_0065d20c(0);
        if (uVar22 != 0) {
            sk_thread_unblock_65eafc(uVar22);
            goto done;
        }
        long local_80 = 0x24000;
        unsigned long uStack_78 = 0x200000000c;
        unsigned long local_90 = 0x11;
        long local_88 = 0;
        unsigned long local_c0 = 0;
        unsigned long *local_b8 = 0;
        int iVar20 = (int)sk_rt_00655e7c(0);
        unsigned int uVar2 = 0x40c8;
        if (iVar20 == 0) {
            uVar2 = 0x41140c8;
        }
        sk_u128_t auVar33 = sk_rt_0066a8c4();
        char cVar17 = (*(char (**)(unsigned long, unsigned int, void *, void *, int, void *))(
            auVar33.hi + 0x30))(auVar33.lo, uVar2, &local_90, &local_c0, 0, 0);
        uVar22 = sk_rt_00655e7c(0);
        if ((uVar22 & 1) == 0) {
            char cVar18 = (*(char (**)(unsigned long, int, int, int))(local_b8[10]))(
                local_c0, 0, 0x4000, 0x20000);
            if (cVar18 != '\0') {
                sk_panic_2(0, 0x6a7135); /* does not return */
            }
        }
        if (cVar17 != '\0') {
            _DAT_006fe774 += 1;
            goto dec;
        }
        if (local_b8 == 0) {
            sk_rt_0065558c(0); /* does not return */
        }
        (*(void (**)(unsigned long, void *))local_b8[1])(local_c0, &local_90);
        uVar22 = sk_stack_alloc_65_6204c(local_88, local_80);
        if (uVar22 + 0x178 < uVar22) goto breakpoint;
        long lVar21b = sk_block_alloc_65_62158(uVar22, 0);
        unsigned long uVar24 = (local_88 - lVar21b) + local_80;
        if (0x1ffff < uVar24) {
            sk_panic_2(0, 0x6a7162); /* does not return */
        }
        unsigned long local_c8 = uVar24;
        iVar20 = (int)sk_rt_00655e7c(0);
        if (iVar20 != 0) {
            local_c8 = 0x20000;
        }
        cVar17 = (*(char (**)(unsigned long, unsigned long *))local_b8[3])(local_c0, &local_c8);
        if (cVar17 == '\0') {
            sk_rt_0067a7f0(uVar22, 0, 0x178);
            *(unsigned long *)(uVar22 + 0x30) = local_c0;
            *(unsigned long **)(uVar22 + 0x38) = local_b8;
            *(long *)(uVar22 + 0x138) = local_80;
            *(long *)(uVar22 + 0x130) = local_88;
            *(long *)(uVar22 + 0x140) = lVar21b;
            *(long *)(uVar22 + 0x168) = local_88 + 0x4000;
            *(long *)(uVar22 + 0x170) = lVar21b;
            unsigned long uVar23 = sk_tcb_to_block_65_621f4(uVar22);
            long lVar21 = sk_rt_0066ad54();
            if (lVar21 == 0) {
                _DAT_006fe77c += 1;
            } else {
                auVar33 = sk_rt_0066a8c4();
                cVar17 = (*(char (**)(unsigned long, unsigned long, int, long))(
                    auVar33.hi + 0x40))(auVar33.lo, uVar23, 1, lVar21);
                if (cVar17 == '\0') {
                    long lVar25 = sk_rt_0066ad54();
                    *(long *)(uVar22 + 0x70) = lVar25;
                    if (lVar25 == 0) {
                        _DAT_006fe784 += 1;
                    } else {
                        unsigned long uVar24 = sk_rt_006832c8(0, 6);
                        *(unsigned long *)(uVar22 + 0x28) = uVar24;
                        if (uVar24 == 0) {
                            _DAT_006fe788 += 1;
                        } else {
                            /* boot frame: CallSupervisor(0) with the cap word */
                            unsigned char *puVar13 = (unsigned char *)tpidrro_el0;
                            *(unsigned long *)puVar13 = lVar21;
                            CallSupervisor(0);
                            if ((uVar24 & 0xff) != 0) {
                                unsigned char bVar19 = sk_rt_00684de0(uVar24, (unsigned char *)0);
                                const char *pcVar28;
                                if (bVar19 < 10) {
                                    switch (bVar19) {
                                    default: pcVar28 = "Success"; break;
                                    case 1: pcVar28 = "Preempted"; break;
                                    case 2: pcVar28 = "Canceled"; break;
                                    case 3: pcVar28 = "Truncated"; break;
                                    case 4: pcVar28 = "CapInvalid"; break;
                                    case 5: pcVar28 = "SlotInvalid"; break;
                                    case 6: pcVar28 = "MethodInvalid"; break;
                                    case 7: pcVar28 = "ArgumentInvalid"; break;
                                    case 8: pcVar28 = "OperationInvalid"; break;
                                    case 9: pcVar28 = "PermissionInvalid"; break;
                                    }
                                    sk_memmove((void *)0, pcVar28, 0x20);
                                    return;
                                }
                                sk_memmove((void *)0, (const void *)&DAT_00689db0, 0x20);
                                sk_rt_0064effc((void *)0, 0x20);
                                return;
                            }
                            if (uVar24 == 0) {
                                unsigned long lVar25 = *(long *)(uVar22 + 0x28);
                                unsigned long uVar23 = sk_notif_oneshot_65e6fc();
                                CallSupervisor(0);
                                if (lVar25 == 0) {
                                    unsigned long uVar24 = sk_rt_006657d8(uVar22, 9);
                                    if ((uVar24 & 1) == 0) {
                                        sk_rt_00684e44(0);
                                    } else {
                                        long lVar25 = sk_boot_param_65_611b8();
                                        if (lVar25 == 0) {
                                            goto seq;
                                        }
                                        goto setseq;
                                    }
                                }
                                sk_thread_unblock_65eafc(uVar22);
                            }
                        }
                    }
                }
            }
        }
        breakpoint:
        SoftwareBreakpoint(0x5519, 0x66047c); /* does not return */
        seq:
        sk_thread_unblock_65eafc(uVar22);
        setseq:
        ; /* (scheduler-entry tail; label sink) */
    }
dec:
    *puVar32 -= 1;
done:
    if (_DAT_006b5ed0 == local_70) {
        return;
    }
    sk_fatal(0); /* does not return */
}

/*--------------------------------------------------------------------*/
/* FUN_006609b4 @ 0x006609b4
 * Ghidra: void FUN_006609b4(long param_1)
 * Scheduler wake entry: invokes the callback at param_1+0x18 (with arg at
 * +0x20), allocates a wake context on the current TCB (0x40=1, flag 0x80=1),
 * spins the per-cpu notif dispatch until it returns 2, then tears the TCB
 * down (FUN_0065d080, FUN_0065cfe4) and panics (0x6a6fe0).
 * Confidence: low */
void sk_sched_wake_65_609b4(unsigned long param_1)
{
    (*(void (**)(unsigned long))(param_1 + 0x18))(*(unsigned long *)(param_1 + 0x20));
    sk_wake_alloc_65_609cc(param_1);
    unsigned long uVar7 = 0;
    unsigned long uVar8 = sk_cur_tcb_65_61318();
    if (uVar8 <= uVar8 + 0x178) {
        sk_rt_0065c218();
        sk_rt_006649b4();
        *(unsigned long *)(uVar8 + 0x40) = uVar7;
        *(unsigned char *)(uVar8 + 0x80) = 1;
        int *piVar1 = (int *)(uVar8 + 0x84);
        unsigned int uVar5 = ((unsigned int)piVar1 >> 4) & 0xf;
        unsigned long uVar7b = sk_clock_reg_read(uVar5);
        int iVar4 = *(int *)(uVar8 + 0x84);
        while (iVar4 == 0) {
            sk_clock_reg_inc(uVar5, piVar1, uVar7b, 0, 0);
            uVar7b = sk_clock_reg_read(uVar5);
            iVar4 = *piVar1;
        }
        sk_clock_dispatch_18(((unsigned int)(uVar8 + 0x80) >> 4) & 0xf, (void *)(uVar8 + 0x80), 5, 0);
        if (iVar4 == 2) {
            sk_rt_0065d080(uVar8);
            long lVar9 = sk_bucket_base();
            unsigned short *puVar2 = (unsigned short *)(lVar9 + 0x38);
            unsigned short uVar3 = *puVar2;
            *puVar2 = uVar3 - 1;
            sk_rt_0065cfe4(uVar8, 1);
        }
        sk_cur_tcb_65_61318();
        sk_thread_unblock_65eafc(uVar8);
        sk_panic_2(0, 0x6a6fe0); /* does not return */
    }
    SoftwareBreakpoint(0x5519, 0x660ab4); /* does not return */
}

/*--------------------------------------------------------------------*/
/* FUN_006609cc @ 0x006609cc
 * Ghidra: void FUN_006609cc(undefined8 param_1)
 * Notify-alloc path (current-thread variant of FUN_006609b4): allocates a wake
 * context, spins the per-cpu dispatch, and on completion returns.
 * Confidence: low */
void sk_wake_alloc_65_609cc(unsigned long param_1)
{
    unsigned long uVar7 = sk_cur_tcb_65_61318();
    if (uVar7 <= uVar7 + 0x178) {
        sk_rt_0065c218();
        sk_rt_006649b4();
        *(unsigned long *)(uVar7 + 0x40) = param_1;
        *(unsigned char *)(uVar7 + 0x80) = 1;
        int *piVar1 = (int *)(uVar7 + 0x84);
        unsigned int uVar5 = ((unsigned int)piVar1 >> 4) & 0xf;
        unsigned long uVar8 = sk_clock_reg_read(uVar5);
        int iVar4 = *(int *)(uVar7 + 0x84);
        while (iVar4 == 0) {
            sk_clock_reg_inc(uVar5, piVar1, uVar8, 0, 0);
            uVar8 = sk_clock_reg_read(uVar5);
            iVar4 = *piVar1;
        }
        sk_clock_dispatch_18(((unsigned int)(uVar7 + 0x80) >> 4) & 0xf, (void *)(uVar7 + 0x80), 5, 0);
        if (iVar4 == 2) {
            sk_rt_0065d080(uVar7);
            long lVar9 = sk_bucket_base();
            unsigned short *puVar2 = (unsigned short *)(lVar9 + 0x38);
            unsigned short uVar3 = *puVar2;
            *puVar2 = uVar3 - 1;
            sk_rt_0065cfe4(uVar7, 1);
        }
        sk_cur_tcb_65_61318();
        sk_thread_unblock_65eafc(uVar7);
        sk_panic_2(0, 0x6a6fe0); /* does not return */
    }
    SoftwareBreakpoint(0x5519, 0x660ab4); /* does not return */
}

/*--------------------------------------------------------------------*/
/* FUN_00660ab4 @ 0x00660ab4
 * Ghidra: void FUN_00660ab4(long param_1)
 * Marks the wake word at param_1+0x84 as 2 (settled) and dispatches slot+0x18.
 * Confidence: high (thin) */
void sk_wake_settle_65_60ab4(unsigned long param_1)
{
    *(unsigned int *)(param_1 + 0x84) = 2;
    sk_clock_dispatch_18(((unsigned int)(param_1 + 0x84) >> 4) & 0xf, (void *)(param_1 + 0x84), 5, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_00660b20 @ 0x00660b20
 * Ghidra: void FUN_00660b20(long param_1)
 * Reclaims the TCB stack: calls the allocator slot +0x18 (from param_1+0x38
 * table) with size 0xc000, panicking on failure (0x6a711c).
 * Confidence: medium */
void sk_tcb_stack_reclaim_65_60b20(unsigned long param_1)
{
    unsigned long local_18 = 0xc000;
    char cVar1 = (*(char (**)(unsigned long, unsigned long *))(*(long *)(param_1 + 0x38) + 0x18))(
        *(unsigned long *)(param_1 + 0x30), &local_18);
    if (cVar1 == '\0') {
        return;
    }
    sk_panic_2(0, 0x6a711c); /* does not return */
}

/*--------------------------------------------------------------------*/
/* FUN_00660b28 @ 0x00660b28
 * Ghidra: undefined8 FUN_00660b28(ulong param_1)
 * Stack-bounds check: returns 1 if param_1 bytes fit between the TCB stack
 * limits (0x168..0x170), panics otherwise (0x6a6ffa / breakpoint 1,0x660b8c).
 * Confidence: medium */
unsigned long sk_stack_check_65_60b28(unsigned long param_1)
{
    unsigned long lVar2 = sk_cur_tcb_65_61318();
    if (*(unsigned char **)(lVar2 + 0x168) <= (unsigned char *)0xfffffffffffffff0 &&
        (unsigned char *)0xfffffffffffffff0 < *(unsigned char **)(lVar2 + 0x170)) {
        if (param_1 <= (unsigned long)((char *)0xfffffffffffffff0 - (char *)*(unsigned long *)(lVar2 + 0x168))) {
            return 1;
        }
        sk_fatal_code(0x6a6ffa); /* does not return */
    }
    SoftwareBreakpoint(1, 0x660b8c); /* does not return */
}

/*--------------------------------------------------------------------*/
/* FUN_00660ba8 @ 0x00660ba8
 * Ghidra: long FUN_00660ba8(long param_1, undefined8 param_2)
 * Acquires the preemption lock (FUN_00661348), issues CallSupervisor(2), and
 * returns the current TCB while its 0x28 word is clear; otherwise maps the
 * error (FUN_00684f2c) and faults (0x6a71c8).
 * Confidence: low */
long sk_preempt_acq_65_60ba8(unsigned long param_1, unsigned long param_2)
{
    unsigned long local_38 = _DAT_006b5ed0;
    unsigned char local_59 = 0;
    long lVar1 = (long)(uintptr_t)sk_lock_acq_65_61348(&local_59);
    if ((int)lVar1 == 0) {
        goto done;
    }
    CallSupervisor(2);
    if ((*(unsigned long *)(param_1 + 0x28) & 0xff) == 0) {
        sk_lock_rel_65_613d0(&local_59);
        goto done;
    }
    sk_rt_00684f2c(*(unsigned long *)(param_1 + 0x28), (unsigned char *)0);
    long lVar1b = sk_cur_tcb_65_61318();
    char cVar2 = *(char *)(lVar1b + 0x69);
    if (cVar2 != '\0') {
        if (cVar2 != -1) goto bump;
        lVar1b = sk_rt_00684f7c();
    }
    sk_fatal_code(0x6a71c8); /* does not return */
bump:
    *(char *)(lVar1b + 0x69) += 1;
    return lVar1b;
done:
    if (_DAT_006b5ed0 == local_38) {
        return lVar1;
    }
    sk_fatal(0); /* does not return */
}

/*--------------------------------------------------------------------*/
/* FUN_00660c44 @ 0x00660c44
 * Ghidra: void FUN_00660c44(void)
 * Increments the current TCB's nested count at +0x69, faulting (0x6a71c8)
 * when the count is saturated.
 * Confidence: medium */
void sk_nested_inc_65_60c44(void)
{
    long lVar1 = sk_cur_tcb_65_61318();
    char cVar2 = *(char *)(lVar1 + 0x69);
    if (cVar2 != '\0') {
        if (cVar2 != -1) goto bump;
        lVar1 = sk_rt_00684f7c();
    }
    sk_fatal_code(0x6a71c8); /* does not return */
bump:
    *(char *)(lVar1 + 0x69) += 1;
}

/*--------------------------------------------------------------------*/
/* FUN_00660ca4 @ 0x00660ca4
 * Ghidra: void FUN_00660ca4(void)
 * Decrements the current TCB's nested count at +0x69, faulting (0x6a71dd)
 * on underflow.
 * Confidence: medium */
void sk_nested_dec_65_60ca4(void)
{
    long lVar2 = sk_cur_tcb_65_61318();
    char cVar1 = *(char *)(lVar2 + 0x69);
    if (cVar1 == '\0') {
        sk_rt_00684f94();
    } else {
        *(char *)(lVar2 + 0x69) = cVar1 - 1;
        if ((cVar1 != '\x01')) {
            return;
        }
    }
    sk_fatal_code(0x6a71dd); /* does not return */
}

/*--------------------------------------------------------------------*/
/* FUN_00660d00 @ 0x00660d00
 * Ghidra: void FUN_00660d00(undefined8 *param_1, ulong param_2, uint param_3)
 * Allocates a message/IO buffer of param_2+0x4000 bytes with the given flag
 * bits (via the allocator slot +0x30), fills a 5-word descriptor into param_1
 * (base, ops, flags, limits) and bumps the bucket count (+0x88). Panics on
 * failure (0x6a71f3 / breakpoint 0x660eec).
 * Confidence: low (allocator descriptor build) */
void sk_buf_alloc_65_60d00(unsigned long *param_1, unsigned long param_2, unsigned int param_3)
{
    long lVar1 = param_2 + 0x4000;
    if (param_2 < 0xffffffffffffc000) {
        unsigned char local_60[8] = { 0x11 };
        sk_memzero((void *)((unsigned long)local_60 | 1), 0xf);
        unsigned int local_48 = 0xc;
        unsigned int local_44 = 0x20;
        unsigned int uVar7 = param_3 & 0xf;
        if ((param_3 & 0xe) == 0) {
            uVar7 = 1;
        }
        long local_50 = lVar1;
        if ((uVar7 & (uVar7 - 1)) == 0) {
            unsigned int uVar7b = 0x40c8;
            if ((param_3 & 2) != 0) {
                uVar7b = 0x44c8;
            }
            unsigned long local_70 = 0, lStack_68 = 0;
            unsigned char auVar8[16];
            sk_u128_t auVar8t = sk_rt_0066a8c4();
            unsigned long uVar5 = (*(unsigned long (**)(unsigned long, unsigned int, void *, void *, int, void *))(
                auVar8t.hi + 0x30))(auVar8t.lo,
                    (param_3 & 4) << 0xb | (param_3 >> 3 & 1) << 9 | uVar7b,
                    local_60, &local_70, 0, local_60);
            if ((uVar5 & 0xff) == 0) {
                unsigned long local_78 = param_2;
                uVar5 = (*(unsigned long (**)(unsigned long, unsigned long *))(lStack_68 + 0x18))(
                    local_70, &local_78);
                if ((uVar5 & 0xff) == 0) {
                    long lVar6 = sk_bucket_base();
                    int iVar4 = *(int *)(lVar6 + 0x88);
                    *(int *)(lVar6 + 0x88) = iVar4 + 1;
                    if (iVar4 != -1) {
                        unsigned long local_58 = param_2;
                        param_1[0] = local_70;
                        param_1[1] = lStack_68;
                        *(unsigned int *)(param_1 + 2) =
                            param_3 & 0xffffffdf | (unsigned int)((param_3 & 0xf) == 0);
                        *(unsigned int *)((char *)param_1 + 0x14) = 0;
                        param_1[3] = local_58;
                        param_1[4] = local_58 + lVar1;
                        param_1[5] = lVar1;
                        *(int *)(param_1 + 6) = iVar4 + 1;
                        *(unsigned int *)((char *)param_1 + 0x34) = 0;
                        return;
                    }
                    sk_rt_00684fac();
                } else {
                    sk_fatal_code(0x6a7255); /* does not return */
                }
            } else {
                sk_fatal_code(0x6a721d); /* does not return */
            }
            SoftwareBreakpoint(0x5519, 0x660eec); /* does not return */
        }
    } else {
        sk_rt_00684fc4();
    }
    sk_fatal_code(0x6a71f3); /* does not return */
}

/*--------------------------------------------------------------------*/
/* FUN_00660eec @ 0x00660eec
 * Ghidra: undefined8 FUN_00660eec(undefined8 param_1, undefined8 param_2, undefined8 param_3)
 * Allocates a buffer (FUN_00660d00, 0x20 flag), runs the copy op FUN_00660f60,
 * tears down the ops (FUN_00660f60's indirect release), and returns the copy result.
 * Confidence: medium */
unsigned long sk_buf_copy_65_60eec(unsigned long param_1, unsigned long param_2, unsigned long param_3)
{
    unsigned long local_60 = 0, local_50 = 0, uStack_48 = 0, uStack_40 = 0, uStack_38 = 0, local_30 = 0;
    unsigned long *puStack_58 = 0;
    sk_buf_alloc_65_60d00(&local_60, param_1, 0x20);
    unsigned long uVar1 = sk_buf_exec_65_60f60(local_60, param_2, param_3);
    (*(void (**)(unsigned long))(*puStack_58))(local_60);
    return uVar1;
}

/*--------------------------------------------------------------------*/
/* FUN_00660f60 @ 0x00660f60
 * Ghidra: undefined8 FUN_00660f60(long param_1, undefined8 param_2, undefined8 param_3)
 * Executes a message copy through the buffer descriptor param_1: checks the
 * active-user count, saves the frame around FUN_0065defc, and when the
 * descriptor's "map/return" bits require, flushes the written pages
 * (CallSupervisor(4) spin) and zeroes the block. Returns the copy status.
 * Confidence: low (frame-save + page flush; panics 0x6a70e3/0x6a7104). */
unsigned long sk_buf_exec_65_60f60(unsigned long param_1, unsigned long param_2, unsigned long param_3)
{
    unsigned long *puVar12 = *(unsigned long **)(param_1 + 0x20);
    unsigned long lVar6 = sk_cur_tcb_65_61318();
    if (*(int *)(lVar6 + 0x148) != 0) {
        sk_fatal_code(0x6a70e3); /* does not return */
    }
    int iVar8 = *(int *)(param_1 + 0x30);
    if (iVar8 == 0) {
        sk_fatal_code(0x6a7104); /* does not return */
    }
    if ((*(unsigned char *)(param_1 + 0x10) >> 3 & 1) != 0) {
        sk_nested_inc_65_60c44();
        iVar8 = *(int *)(param_1 + 0x30);
    }
    unsigned long uVar1 = *(unsigned long *)(lVar6 + 0x168);
    unsigned long uVar2 = *(unsigned long *)(lVar6 + 0x170);
    unsigned long uVar7 = *(unsigned long *)(param_1 + 0x20);
    *(long *)(lVar6 + 0x168) = *(long *)(param_1 + 0x18) + 0x4000;
    *(unsigned long *)(lVar6 + 0x170) = uVar7;
    unsigned long result = sk_msg_dispatch_65defc((unsigned long)puVar12, param_2, param_3);
    *(unsigned long *)(lVar6 + 0x168) = uVar1;
    *(unsigned long *)(lVar6 + 0x170) = uVar2;
    *(unsigned int *)(lVar6 + 0x148) = 0;
    *(unsigned int *)(lVar6 + 0x160) = 0;
    *(unsigned int *)(lVar6 + 0x164) = 0;
    *(unsigned int *)(lVar6 + 0x158) = 0;
    *(unsigned int *)(lVar6 + 0x15c) = 0;
    *(unsigned int *)(lVar6 + 0x150) = 0;
    *(unsigned int *)(lVar6 + 0x154) = 0;
    *(unsigned int *)(lVar6 + 0x14c) = 0;
    unsigned int uVar9 = *(unsigned int *)(param_1 + 0x10);
    unsigned long *puVar13 = 0;
    unsigned long uVar10 = 0;
    if ((uVar9 >> 4 & 1) != 0) {
        long lVar6b = sk_rt_0066ad54();
        unsigned long *puVar11 = (unsigned long *)(*(long *)(param_1 + 0x18) + 0x4000);
        unsigned long uVar3 = 0;
        unsigned long *puVar14 = puVar12;
        char cVar5;
        do {
            puVar13 = puVar14;
            uVar10 = uVar3;
            if ((puVar13 <= puVar11) || (puVar14 = puVar13 - 0x800, puVar14 < puVar11)) break;
            sk_u128_t auVar15t = sk_rt_0066a8c4();
            cVar5 = (*(char (**)(unsigned long, unsigned long *, int, long))(
                auVar15t.hi + 0x40))(auVar15t.lo, puVar14, 0, lVar6b);
            do {
                CallSupervisor(4);
            } while (lVar6b == 1);
            uVar3 = uVar10 + 0x4000;
        } while (cVar5 == '\0');
        sk_rt_006860f4(lVar6b);
        uVar9 = *(unsigned int *)(param_1 + 0x10);
        unsigned long uVar3b = (unsigned long)puVar12 - (unsigned long)puVar13;
        if (uVar3b != 0) {
            puVar12 = (unsigned long *)((unsigned long)puVar13 + uVar3b);
            if ((uVar9 >> 3 & 1) == 0) {
                if ((puVar12 < puVar13) || ((unsigned long)((unsigned long)puVar12 - (unsigned long)puVar13) < uVar3b)) {
                    SoftwareBreakpoint(0x5519, 0x661154); /* does not return */
                }
                sk_memzero((void *)puVar13, uVar3b);
                uVar9 = *(unsigned int *)(param_1 + 0x10);
            } else if (7 < uVar3b) {
                unsigned long uVar10b = uVar10 >> 3;
                unsigned long *puVar11b = puVar13;
                if (uVar10b < 2) {
                    uVar10b = 1;
                }
                do {
                    if ((puVar11b < puVar13) || (puVar12 < puVar11b + 1)) {
                        SoftwareBreakpoint(0x5519, 0x661154); /* does not return */
                    }
                    *puVar11b = 0;
                    uVar10b -= 1;
                    puVar11b += 1;
                } while (uVar10b != 0);
            }
        }
    }
    if ((uVar9 >> 3 & 1) != 0) {
        sk_nested_dec_65_60ca4();
    }
    return result;
}

/*--------------------------------------------------------------------*/
/* FUN_00661178 @ 0x00661178
 * Ghidra: void FUN_00661178(void)
 * Validates the TCB stack tail region (0x104 <= 0x108), faulting on overflow.
 * Confidence: medium */
void sk_stack_tail_check_65_61178(void)
{
    unsigned long lVar2 = sk_cur_tcb_65_61318();
    if (lVar2 + 0x104 <= lVar2 + 0x108) {
        return;
    }
    SoftwareBreakpoint(0x5519, 0x6611a8); /* does not return */
}

/*--------------------------------------------------------------------*/
/* FUN_006611a8 @ 0x006611a8
 * Ghidra: void FUN_006611a8(code *UNRECOVERED_JUMPTABLE, undefined8 param_2)
 * Indirect jump-table dispatch: calls the function pointer param_1 with param_2.
 * Confidence: medium (indirect jumptable, treated as call) */
void sk_ind_call_65_611a8(unsigned long (*fn)(unsigned long), unsigned long param_2)
{
    (*fn)(param_2);
}

/*--------------------------------------------------------------------*/
/* FUN_006611b8 @ 0x006611b8
 * Ghidra: undefined8 FUN_006611b8(void)
 * Boot-parameter lookup: iterates the boot info block (FUN_00650ec8 /
 * FUN_00651074 / FUN_00650ed0 / FUN_00650c10) looking for a "0x1c"-kind node,
 * reads its 4-byte name (FUN_00650b3c) and returns the composed capability.
 * Returns 0 when the boot block is absent or malformed.
 * Confidence: low (boot-info parse; SoftwareBreakpoint 0x6612c0). */
unsigned long sk_boot_param_65_611b8(void)
{
    unsigned char local_30[16] = {0};
    int iVar3 = sk_rt_00652204();
    if (iVar3 != 0) {
        unsigned long uVar4 = sk_rt_006510cc();
        if (uVar4 != 0) {
            if (uVar4 + 8 < uVar4) {
                SoftwareBreakpoint(0x5519, 0x6612c0); /* does not return */
            }
        }
        sk_u128_t lt = sk_rt_00650ec8();
        local_30[0] = (unsigned char)lt.lo;
        local_30[8] = (unsigned char)lt.hi;
        uVar4 = sk_rt_00651074((unsigned long)local_30);
        if ((uVar4 & 1) == 0) {
            unsigned short *puVar6 = 0;
            do {
                uVar4 = sk_rt_00650ed0((unsigned long)local_30);
                if ((uVar4 != 0) && (uVar4 + 0xc < uVar4)) {
                    SoftwareBreakpoint(0x5519, 0x6612c0); /* does not return */
                }
                iVar3 = sk_rt_00650c10(uVar4);
                if (iVar3 == 0x1c) {
                    puVar6 = (unsigned short *)sk_rt_00650b3c(uVar4, 0);
                }
                iVar3 = sk_rt_00651074((unsigned long)local_30);
            } while (iVar3 == 0);
            if (puVar6 != 0) {
                unsigned char local_40[16];
                sk_u128_t lt2 = sk_rt_00651108();
                local_40[0] = (unsigned char)lt2.lo;
                local_40[8] = (unsigned char)lt2.hi;
                unsigned long name = (unsigned long)(unsigned char)puVar6[1] << 0x10 |
                    (unsigned long)*(unsigned char *)((char *)puVar6 + 3) << 0x18 |
                    (unsigned long)*puVar6 |
                    (unsigned long)((unsigned int)(unsigned char)puVar6[3] << 0x10 |
                                    (unsigned int)*(unsigned char *)((char *)puVar6 + 7) << 0x18 |
                                    (unsigned int)puVar6[2]) << 0x20;
                return sk_rt_00650af8((unsigned long)local_40, name);
            }
        }
    }
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_006612c0 @ 0x006612c0
 * Ghidra: void FUN_006612c0(byte param_1)
 * Maps an L4 error code byte to its string and copies 0x20 bytes into the
 * caller stack slot (alt strings set).
 * Confidence: high (error-string mapper) */
void sk_err_str_b_65_612c0(unsigned char param_1)
{
    const char *pcVar1;
    if (9 < param_1) {
        sk_memmove((void *)0x10, (const void *)&DAT_00689db0, 0x20);
        sk_rt_0064effc((void *)0x10, 0x20);
        return;
    }
    switch (param_1) {
    default: pcVar1 = "Success"; break;
    case 1: pcVar1 = "Preempted"; break;
    case 2: pcVar1 = "Canceled"; break;
    case 3: pcVar1 = "Truncated"; break;
    case 4: pcVar1 = "CapInvalid"; break;
    case 5: pcVar1 = "SlotInvalid"; break;
    case 6: pcVar1 = "MethodInvalid"; break;
    case 7: pcVar1 = "ArgumentInvalid"; break;
    case 8: pcVar1 = "OperationInvalid"; break;
    case 9: pcVar1 = "PermissionInvalid"; break;
    }
    sk_memmove((void *)0x10, pcVar1, 0x20);
}

/*--------------------------------------------------------------------*/
/* FUN_006612e0 @ 0x006612e0
 * Ghidra: void FUN_006612e0(void)
 * Error-string mapper reading the code from the unaff_w20 register artifact.
 * Confidence: low (register-artifact twin) */
void sk_err_str_w20b_65_612e0(void)
{
    unsigned char code = (unsigned char)0;
    if (9 < code) {
        sk_memmove((void *)0, (const void *)&DAT_00689db0, 0x20);
        sk_rt_0064effc((void *)0, 0x20);
        return;
    }
    const char *pcVar1;
    switch (code) {
    default: pcVar1 = "Success"; break;
    case 1: pcVar1 = "Preempted"; break;
    case 2: pcVar1 = "Canceled"; break;
    case 3: pcVar1 = "Truncated"; break;
    case 4: pcVar1 = "CapInvalid"; break;
    case 5: pcVar1 = "SlotInvalid"; break;
    case 6: pcVar1 = "MethodInvalid"; break;
    case 7: pcVar1 = "ArgumentInvalid"; break;
    case 8: pcVar1 = "OperationInvalid"; break;
    case 9: pcVar1 = "PermissionInvalid"; break;
    }
    sk_memmove((void *)0, pcVar1, 0x20);
}

/*--------------------------------------------------------------------*/
/* FUN_006612ec @ 0x006612ec
 * Ghidra: void FUN_006612ec(void)
 * No-op.
 * Confidence: high (trivial) */
void sk_noop_65_612ec(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_006612f0 @ 0x006612f0
 * Ghidra: long FUN_006612f0(void)
 * Returns the next sequence number from the clock base (+0x30), incrementing it.
 * Confidence: high (atomic sequence bump) */
long sk_next_seq_65_612f0(void)
{
    long lVar2 = sk_bucket_base();
    long lVar1 = *(long *)(lVar2 + 0x30);
    *(long *)(lVar2 + 0x30) = lVar1 + 1;
    return lVar1 + 1;
}

/*--------------------------------------------------------------------*/
/* FUN_00661318 @ 0x00661318
 * Ghidra: undefined8 FUN_00661318(void)
 * Returns the current TCB pointer (tpidr_el0 + 8).
 * Confidence: high (trivial read) */
unsigned long sk_cur_tcb_65_61318(void)
{
    return *(unsigned long *)(tpidr_el0 + 8);
}

/*--------------------------------------------------------------------*/
/* FUN_00661324 @ 0x00661324
 * Ghidra: undefined1 FUN_00661324(void)
 * Returns flag byte DAT_006fe798.
 * Confidence: high (trivial read) */
unsigned char sk_flag_798_65_61324(void)
{
    return (unsigned char)DAT_006fe798;
}

/*--------------------------------------------------------------------*/
/* FUN_00661330 @ 0x00661330
 * Ghidra: undefined1 FUN_00661330(void)
 * Returns flag byte DAT_006fe799.
 * Confidence: high (trivial read) */
unsigned char sk_flag_799_65_61330(void)
{
    return (unsigned char)DAT_006fe799;
}

/*--------------------------------------------------------------------*/
/* FUN_0066133c @ 0x0066133c
 * Ghidra: undefined1 FUN_0066133c(void)
 * Returns flag byte DAT_006b53b0.
 * Confidence: high (trivial read) */
unsigned char sk_flag_b53b0_65_6133c(void)
{
    return (unsigned char)DAT_006b53b0;
}

/*--------------------------------------------------------------------*/
/* FUN_00661348 @ 0x00661348
 * Ghidra: byte * FUN_00661348(byte *param_1)
 * Acquires the global preemption/clock lock (DAT_006ff0a8 counter): if the
 * current TCB's 0x68 byte is clear, atomically bumps the counter (LOAcquire),
 * marks the TCB busy, and returns 1. When param_1 is non-null it is set to the
 * previous state. Drains queued work when the generation advances.
 * Confidence: medium */
unsigned char *sk_lock_acq_65_61348(unsigned char *param_1)
{
    unsigned long lVar5 = tpidr_el0;
    lVar5 = *(unsigned long *)(lVar5 + 8);
    unsigned char bVar1 = *(unsigned char *)(lVar5 + 0x68);
    if (param_1 == 0) {
        if (bVar1 != 0) {
            unsigned char *pbVar3 = (unsigned char *)sk_rt_00685054();
            lVar5 = tpidr_el0;
            lVar5 = *(unsigned long *)(lVar5 + 8);
            if ((*(unsigned char *)(lVar5 + 0x68) & 1) == 0) {
                pbVar3 = (unsigned char *)sk_rt_00685084();
                while ((_DAT_006ff0a8 & 0x3ff) != 0) {
                    lVar5 = tpidr_el0;
                    sk_dispatch_slot20_65ee30();
                    pbVar3 = (unsigned char *)0;
                }
                _DAT_006ff0a8 += 0x400;
                return pbVar3;
            }
            if (pbVar3 == 0) {
                *(unsigned char *)(lVar5 + 0x68) = 0;
            } else {
                bVar1 = *pbVar3;
                *(unsigned char *)(lVar5 + 0x68) = bVar1;
                if ((bVar1 & 1) != 0) {
                    return pbVar3;
                }
            }
            *(long *)(lVar5 + 0x58) -= 1;
            _DAT_006ff0a8 -= 1;
            return pbVar3;
        }
    } else {
        *param_1 = bVar1;
        if ((bVar1 & 1) != 0) {
            return (unsigned char *)1;
        }
    }
    unsigned long uVar2 = _DAT_006ff0a8;
    LOAcquire();
    _DAT_006ff0a8 += 1;
    *(unsigned char *)(lVar5 + 0x68) = 1;
    *(long *)(lVar5 + 0x58) += 1;
    unsigned int uVar4 = 1;
    if (uVar2 >> 10 != *(unsigned long *)(lVar5 + 0x78)) {
        sk_lock_rel_65_613d0(0);
        *(unsigned long *)(lVar5 + 0x78) = uVar2 >> 10;
        uVar4 = (unsigned int)*(unsigned char *)(lVar5 + 0x68);
    }
    return (unsigned char *)(unsigned long)(uVar4 & 1);
}

/*--------------------------------------------------------------------*/
/* FUN_006613d0 @ 0x006613d0
 * Ghidra: void FUN_006613d0(byte *param_1)
 * Releases the global preemption lock: clears the current TCB's 0x68 busy byte
 * (or restores it from param_1), decrements the counter, and drains the
 * preemption queue when the low bits clear.
 * Confidence: medium */
void sk_lock_rel_65_613d0(unsigned char *param_1)
{
    unsigned long lVar2 = tpidr_el0;
    lVar2 = *(unsigned long *)(lVar2 + 8);
    if ((*(unsigned char *)(lVar2 + 0x68) & 1) == 0) {
        sk_rt_00685084();
        while ((_DAT_006ff0a8 & 0x3ff) != 0) {
            lVar2 = tpidr_el0;
            sk_dispatch_slot20_65ee30();
        }
        _DAT_006ff0a8 += 0x400;
        return;
    }
    if (param_1 == 0) {
        *(unsigned char *)(lVar2 + 0x68) = 0;
    } else {
        unsigned char bVar1 = *param_1;
        *(unsigned char *)(lVar2 + 0x68) = bVar1;
        if ((bVar1 & 1) != 0) {
            return;
        }
    }
    *(long *)(lVar2 + 0x58) -= 1;
    _DAT_006ff0a8 -= 1;
}

/*--------------------------------------------------------------------*/
/* FUN_00661428 @ 0x00661428
 * Ghidra: void FUN_00661428(void)
 * Drains all queued preemption work and advances the global counter.
 * Confidence: medium */
void sk_lock_drain_65_61428(void)
{
    while ((_DAT_006ff0a8 & 0x3ff) != 0) {
        long lVar1 = tpidr_el0;
        sk_dispatch_slot20_65ee30();
    }
    _DAT_006ff0a8 += 0x400;
}

/*--------------------------------------------------------------------*/
/* FUN_00661488 @ 0x00661488
 * Ghidra: ulong FUN_00661488(ulong param_1)
 * Slot->block-address translation: if the pool base (_DAT_006fe7e0) is not yet
 * established, computes it from the fixed block base (FUN_00664bd4) and size
 * 0x1fd00, then returns base + param_1<<14 with the low 14 bits set from the
 * pool offset. Panics on overflow.
 * Confidence: medium */
unsigned long sk_slot_addr_65_61488(unsigned long param_1)
{
    if (_DAT_006fe7e0 == 0) {
        long lVar2 = sk_rt_00664bd4();
        unsigned long uVar3 = (0x1fd00 - (unsigned long)lVar2) & 0xfffffffffffffff0;
        if (uVar3 + (unsigned long)lVar2 < uVar3) {
            SoftwareBreakpoint(0x5519, 0x6614d4); /* does not return */
        }
        _DAT_006fe7e0 = 0x20178 - uVar3;
    }
    return (unsigned long)(unsigned int)(-(int)_DAT_006fe7e0) & 0x3fff |
           (param_1 & 0xffffffff) << 0xe;
}

/*--------------------------------------------------------------------*/
/* FUN_00661500 @ 0x00661500
 * Ghidra: void FUN_00661500(undefined8 param_1, ulong param_2,
 *                          undefined8 *param_3, undefined8 *param_4, undefined8 param_5)
 * Boot/secondary-thread setup: establishes the thread stack region (allocating
 * the _DAT_006fe7a0 pool, mounting the "entr" magic frame and the boot-info
 * blocks), wires the per-cpu kernel stack (lVar12+0x10), loads the boot image
 * regions, then switches to the dispatcher for the requested mode. Complex
 * entry/exit path.
 * Confidence: low (very large; many indirect allocator calls). */
void sk_thread_boot_65_61500(unsigned long param_1, unsigned long param_2,
                             unsigned long *param_3, unsigned long *param_4, unsigned long param_5)
{
    long lVar12 = tpidr_el0;
    unsigned long uVar23 = param_2;
    unsigned long local_1a8 = 0, uStack_1a0 = 0, local_198 = 0, local_190 = 0x656e7472;
    unsigned char auStack_188[32];
    if (lVar12 == 0) {
        unsigned long *puVar20 = (unsigned long *)((unsigned long)param_3 + 0x3fff & 0xffffffffffffc000);
        if (puVar20 < param_4) goto overflow;
        sk_rt_0067ad00((unsigned long)param_4, (unsigned long *)0);
        unsigned long *puVar22 = puVar20 - 0x60;
        lVar12 = sk_rt_00664bd4();
        uVar23 = ((unsigned long)puVar22 - (unsigned long)lVar12) & 0xfffffffffffffff0;
        if (uVar23 + (unsigned long)lVar12 < uVar23) goto overflow;
        unsigned long uVar13 = (unsigned long)param_4 & 0xffffffffffffc000;
        sk_memzero((void *)auStack_188, 0x118);
        sk_memmove((void *)(uVar23 - 0x178), auStack_188, 0x118);
        *(unsigned int *)(uVar23 - 0x60) = local_190;
        sk_memmove((void *)(uVar23 - 0x5c), &local_1a8, 0x14);
        *(unsigned long *)(uVar23 - 0x48) = uVar13;
        *(unsigned long *)(uVar23 - 0x40) = (unsigned long)puVar20 - uVar13;
        *(unsigned long **)(uVar23 - 0x38) = param_4;
        *(unsigned long *)(uVar23 - 0x18) = 0;
        *(unsigned long *)(uVar23 - 0x20) = 0;
        *(unsigned long *)(uVar23 - 0x28) = 0;
        *(unsigned long *)(uVar23 - 0x30) = 0;
        *(unsigned long *)(uVar23 - 0x10) = uVar13;
        *(unsigned long **)(uVar23 - 8) = param_4;
        sk_rt_00664a84((unsigned long)puVar22);
        *puVar22 = uVar23;
        puVar20[-0x5f] = uVar23 - 0x178;
    }
    if (((param_2 & 0xfd) == 1) && (_DAT_006fe7a0 == 0)) {
        lVar12 = sk_rt_00664bd4();
        uVar23 = ((((unsigned long)param_3 + 0x3fff & 0xffffffffffffc000) - (unsigned long)lVar12) - 0x300) &
                 0xfffffffffffffff0;
        if (uVar23 + (unsigned long)lVar12 < uVar23) goto overflow;
        unsigned long *puVar25 = (unsigned long *)(uVar23 - 0x200);
        _DAT_006fe7a0 = (unsigned long)puVar25;
        unsigned long uVar13 = sk_rt_006646e0();
        long lVar14 = sk_rt_0066469c();
        lVar12 = tpidr_el0;
        long lVar11;
        if (*(long *)(lVar12 + 0x10) != uVar23 - 400) {
            if ((*(long *)(lVar12 + 0x10) != 0) ||
                (lVar11 = *(long *)(lVar14 + 0x208), *(long *)(lVar14 + 0x208) = lVar11 + 1, lVar11 != -1)) {
                *(unsigned long *)(lVar12 + 0x10) = uVar23 - 400;
                goto mapped;
            }
            goto overflow;
        }
mapped:
        if (uVar13 + 0x2f0 < uVar13) goto overflow;
        sk_rt_0065cba0(uVar13);
        sk_timer_slot_clear_65e5c0();
        sk_rt_0065be9c();
        lVar12 = sk_rt_0065585c(param_5);
        if (*(long *)(lVar12 + 8) == 0) {
            sk_rt_00654528(*(unsigned long *)(lVar12 + 0x18));
        }
        sk_rt_00656744();
        unsigned char *pbVar15 = (unsigned char *)sk_percpu_ptr(0);
        sk_rt_0065d2cc();
        if ((*pbVar15 & 1) != 0) {
            /* ... boot-image load tail ... */
            goto done;
        }
        unsigned long uVar16 = *(unsigned long *)(pbVar15 + 0x40);
        if ((uVar16 != 0) && (uVar13 = *(unsigned long *)(pbVar15 + 0x30), uVar13 != 0)) {
            unsigned long uVar24 = sk_rt_0065d2e4(uVar13);
            if (uVar24 != *(unsigned long *)(pbVar15 + 0x40)) {
                sk_rt_006850dc();
            }
            sk_memzero((void *)uVar13, uVar24);
            goto proceed;
        }
        sk_rt_006850f4();
        goto done2;
proceed:
        sk_rt_00655e84();
        sk_rt_0067f608();
        sk_rt_006542e0(*(unsigned long *)(lVar12 + 0x10));
        /* ... (region wiring tail elided structurally) ... */
        goto done;
    }
done:
    /* mode switch via the dispatcher table */
    unsigned long *puVar25 = (unsigned long *)sk_rt_0065be08(0x6fe7a8, 1, 2);
    unsigned long *puVar20 = puVar25 + (uVar23 & 0xff) * 2;
    if (*puVar20 == 0) {
        sk_panic_2(0, 0x6a79dd); /* does not return */
    }
    ((void (*)(unsigned long, unsigned long, unsigned long))*puVar20)(puVar20[1], param_1, param_2);
    sk_panic_2(0, 0x6a79ff); /* does not return */
overflow:
    SoftwareBreakpoint(0x5519, 0x6616b4); /* does not return */
done2:
    sk_fatal(0); /* does not return */
}

/*--------------------------------------------------------------------*/
/* FUN_00661d38 @ 0x00661d38
 * Ghidra: undefined8 FUN_00661d38(long param_1, undefined8 *param_2,
 *                              undefined8 param_3, undefined8 param_4,
 *                              undefined8 param_5, undefined8 param_6)
 * Message-word read: when param_5==0 returns the message word *param_2 (or
 * reads it from the TCB via FUN_00662b84); when param_5!=0 requires param_2 to
 * be null and param_1 to be the current TCB. Delegates to FUN_00661e24.
 * Confidence: medium */
unsigned long sk_msg_word_65_61d38(unsigned long param_1, unsigned long *param_2,
                                   unsigned long param_3, unsigned long param_4,
                                   unsigned long param_5, unsigned long param_6)
{
    unsigned char local_59 = 0;
    unsigned long local_58;
    unsigned char bVar4;
    if ((int)param_5 == 0) {
        if (param_2 != 0) {
            local_58 = *param_2;
            bVar4 = 1;
            goto go;
        }
    } else {
        long lVar1 = tpidr_el0;
        if (param_2 != 0) {
            return 0;
        }
        if (param_1 != *(long *)(lVar1 + 8)) {
            return 0;
        }
    }
    local_58 = sk_msg_word_tcb_65_62b84(param_1);
    bVar4 = 0;
go:
    if (param_1 + 0x118 <= param_1 + 0x168) {
        unsigned long uVar3 = sk_msg_extract_65_61e24(param_1 + 0x118, &local_58, (unsigned long *)param_3, param_4,
                                             param_5, param_6, 0, &local_59);
        if ((bVar4 & local_59) == 1) {
            *param_2 = local_58;
        }
        return uVar3;
    }
    SoftwareBreakpoint(0x5519, 0x661e1c); /* does not return */
}

/*--------------------------------------------------------------------*/
/* FUN_00661e1c @ 0x00661e1c
 * Ghidra: void FUN_00661e1c(void)
 * Thin forwarder to FUN_00661d38 (current-thread message read).
 * Confidence: high (thin) */
void sk_msg_word_fwd_65_61e1c(void)
{
    sk_msg_word_65_61d38(0, 0, 0, 0, 0, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_00661e24 @ 0x00661e24
 * Ghidra: ulong FUN_00661e24(long param_1, long *param_2, ulong *param_3,
 *                          ulong param_4, undefined8 param_5, undefined1 param_6,
 *                          long *param_7, undefined1 *param_8)
 * Message extraction core: computes the message bounds (base/limit from
 * param_1+0x18/+0x28/+0x20), copies the words via FUN_0067b478 (or the
 * scatter variants FUN_0067b664/FUN_0067b580) into param_3, resolves the
 * capability from the region map (FUN_0065cda8), and reports completion via
 * param_8. Returns the number of words read.
 * Confidence: low (scatter-gather; SoftwareBreakpoint 0x662044). */
unsigned long sk_msg_extract_65_61e24(unsigned long param_1, long *param_2, unsigned long *param_3,
                                      unsigned long param_4, unsigned long param_5,
                                      unsigned char param_6, long *param_7, unsigned char *param_8)
{
    long lVar5 = *param_2;
    long lVar3 = (param_7 == 0) ? 0 : *param_7;
    unsigned long uVar4 = (unsigned long)lVar5 - *(long *)(param_1 + 0x18);
    unsigned long uStack_a8 = *(long *)(param_1 + 0x28) - *(long *)(param_1 + 0x18);
    if (*(unsigned long *)(param_1 + 0x20) <= uStack_a8) {
        uStack_a8 = *(unsigned long *)(param_1 + 0x20);
    }
    long local_b0 = lVar3 + *(long *)(param_1 + 0x18);
    unsigned long local_98 = 0, local_90 = 0;
    unsigned long local_80 = 0, local_78 = 0, uVar7 = 0;
    if ((param_7 == 0) && (*(unsigned long *)(param_1 + 0x20) <= uVar4) &&
        (*(int *)(param_1 + 0x30) != 0) && (lVar3 == 0)) {
        local_80 = *(unsigned long *)(param_1 + 0x38);
        local_78 = (unsigned long)*(unsigned int *)(param_1 + 0x34);
    } else if ((*(unsigned long *)(param_1 + 0x20) <= uVar4) && (*(int *)(param_1 + 0x30) != 0)) {
        lVar5 = *(long *)(param_1 + 0x40);
        uVar7 = *(unsigned long *)(param_1 + 0x48);
    }
    unsigned long local_a0 = param_4;
    long local_70 = lVar3;
    uVar4 = sk_rt_0067b478(lVar5, param_5, 0, lVar3, &local_b0, (void *)0x663670);
    if (uVar4 <= param_4) {
        param_4 = uVar4;
    }
    if (param_3 != 0) {
        unsigned long *puVar6 = param_3;
        if (uVar7 != 0) {
            if (lVar3 == 0) {
                unsigned long local_68 = uVar7;
                long lVar2 = sk_bucket_lookup(&local_68, 0);
                if (lVar2 == 0) {
                    uVar7 = 0xffff000000000000;
                } else {
                    uVar7 = (unsigned long)*(unsigned short *)(lVar2 + 0x40) << 0x30;
                }
                uVar7 = local_68 & 0xffffffffffff | uVar7;
            }
            puVar6 = param_3 + 1;
            if ((puVar6 < param_3) || (param_3 + param_4 < puVar6)) {
                SoftwareBreakpoint(0x5519, 0x662044); /* does not return */
            }
            unsigned long lVar2 = param_4 * 8;
            *param_3 = uVar7;
            param_4 -= 1;
            if (((lVar2 + -8) >> 3) < param_4) {
                SoftwareBreakpoint(0x5519, 0x662044); /* does not return */
            }
        }
        if ((int)param_5 == 0) {
            sk_rt_0067b664(lVar5, puVar6, param_4, lVar3, (void *)0x6636e8, &local_70);
        } else {
            sk_rt_0067b580(lVar5, puVar6, param_4, 0);
        }
    }
    if ((char)local_98 == '\x01') {
        *param_2 = local_90;
        *param_8 = 1;
    }
    return uVar4;
}

/*--------------------------------------------------------------------*/
/* FUN_00662044 @ 0x00662044
 * Ghidra: void FUN_00662044(long param_1, undefined8 param_2)
 * Stores the notify/cleanup callback at TCB+0xa0.
 * Confidence: high (trivial setter) */
void sk_tcb_cb_set_65_62044(unsigned long param_1, unsigned long param_2)
{
    *(unsigned long *)(param_1 + 0xa0) = param_2;
}

/*--------------------------------------------------------------------*/
/* FUN_0066204c @ 0x0066204c
 * Ghidra: long FUN_0066204c(long param_1, long param_2)
 * Stack-block allocation: computes (param_1+param_2 aligned) - base - 0x300
 * (rounded) - 0x178 from the block base (FUN_00664bd4). Panics on overflow.
 * Confidence: medium */
long sk_stack_alloc_65_6204c(long param_1, long param_2)
{
    long lVar2 = sk_rt_00664bd4();
    unsigned long uVar3 = ((param_2 + param_1 & 0xfffffffffffffff8) - (unsigned long)lVar2 - 0x300) &
                          0xfffffffffffffff0;
    if (uVar3 + (unsigned long)lVar2 < uVar3) {
        SoftwareBreakpoint(0x5519, 0x662088); /* does not return */
    }
    return uVar3 - 0x178;
}

/*--------------------------------------------------------------------*/
/* FUN_00662098 @ 0x00662098
 * Ghidra: undefined8 FUN_00662098(long param_1)
 * Returns the TCB+0x140 word.
 * Confidence: high (trivial read) */
unsigned long sk_tcb_read_140_65_62098(unsigned long param_1)
{
    return *(unsigned long *)(param_1 + 0x140);
}

/*--------------------------------------------------------------------*/
/* FUN_006620a0 @ 0x006620a0
 * Ghidra: ulong FUN_006620a0(ulong param_1, byte param_2)
 * Allocates a stack/message block for mode param_2: for mode 3 returns
 * (param_1+0x3fff & ~0x3fff) - base - 0x300 - 0x200; for other kernel modes
 * returns (param_1 & ~7) - base - 0x300 - 0x178; for user modes returns
 * param_1 unchanged. Panics on overflow.
 * Confidence: low (mode-dependent address math). */
unsigned long sk_stack_alloc_mode_65_620a0(unsigned long param_1, unsigned char param_2)
{
    if (param_2 == 0) {
        SoftwareBreakpoint(1, 0x662158); /* does not return */
    }
    long lVar2 = tpidr_el0;
    if (lVar2 == 0) {
        if (param_2 == 3) {
            lVar2 = sk_rt_00664bd4();
            unsigned long uVar3 = ((param_1 + 0x3fff & 0xffffffffffffc000) - (unsigned long)lVar2 - 0x300) &
                                  0xfffffffffffffff0;
            if (uVar3 + (unsigned long)lVar2 < uVar3) {
                SoftwareBreakpoint(0x5519, 0x662140); /* does not return */
            }
            uVar3 -= 0x200;
            return uVar3 & 0xfffffffffffffff0;
        }
    } else if ((1 < param_2 - 0x50) && (param_2 != 2)) {
        return param_1;
    }
    lVar2 = sk_rt_00664bd4();
    unsigned long uVar3 = ((param_1 & 0xfffffffffffffff8) - (unsigned long)lVar2 - 0x300) &
                          0xfffffffffffffff0;
    if (uVar3 + (unsigned long)lVar2 < uVar3) {
        SoftwareBreakpoint(0x5519, 0x662140); /* does not return */
    }
    uVar3 -= 0x178;
    return uVar3 & 0xfffffffffffffff0;
}

/*--------------------------------------------------------------------*/
/* FUN_00662158 @ 0x00662158
 * Ghidra: ulong FUN_00662158(long param_1, long param_2)
 * Block allocation using the _DAT_006fe7e0 pool: base + param_1 aligned, minus
 * the block base (FUN_00664bd4), minus 0x300, minus param_2, minus 0x478.
 * Panics on overflow.
 * Confidence: medium */
unsigned long sk_block_alloc_65_62158(long param_1, long param_2)
{
    long lVar5 = _DAT_006fe7e0;
    long lVar2 = sk_rt_00664bd4();
    if (lVar5 == 0) {
        unsigned long uVar3 = (0x1fd00 - (unsigned long)lVar2) & 0xfffffffffffffff0;
        if (uVar3 + (unsigned long)lVar2 < uVar3) goto overflow;
        lVar5 = 0x20178 - uVar3;
        _DAT_006fe7e0 = lVar5;
    }
    unsigned long uVar3 = ((lVar5 + param_1 & 0xfffffffffffffff8) - (unsigned long)lVar2) &
                          0xfffffffffffffff0;
    unsigned long uVar4 = uVar3 - 0x300;
    if (uVar4 <= uVar4 + (unsigned long)lVar2) {
        return (uVar3 - param_2) - 0x478 & 0xfffffffffffffff0;
    }
overflow:
    SoftwareBreakpoint(0x5519, 0x6621d8); /* does not return */
}

/*--------------------------------------------------------------------*/
/* FUN_006621f4 @ 0x006621f4
 * Ghidra: long FUN_006621f4(long param_1)
 * Resolves a TCB pointer to its block base: param_1 + _DAT_006fe7e0 - 0x200
 * (after establishing the pool).
 * Confidence: medium */
long sk_tcb_to_block_65_621f4(long param_1)
{
    if (_DAT_006fe7e0 == 0) {
        long lVar2 = sk_rt_00664bd4();
        unsigned long uVar3 = (0x1fd00 - (unsigned long)lVar2) & 0xfffffffffffffff0;
        if (uVar3 + (unsigned long)lVar2 < uVar3) {
            SoftwareBreakpoint(0x5519, 0x662240); /* does not return */
        }
        _DAT_006fe7e0 = 0x20178 - uVar3;
    }
    return param_1 + _DAT_006fe7e0 - 0x200;
}

/*--------------------------------------------------------------------*/
/* FUN_00662264 @ 0x00662264
 * Ghidra: long FUN_00662264(long param_1)
 * Slot-base resolution: (_DAT_006fe7e0 + param_1 & ~7) - 0x300.
 * Confidence: medium */
long sk_slot_base_65_62264(long param_1)
{
    if (_DAT_006fe7e0 == 0) {
        long lVar2 = sk_rt_00664bd4();
        unsigned long uVar3 = (0x1fd00 - (unsigned long)lVar2) & 0xfffffffffffffff0;
        if (uVar3 + (unsigned long)lVar2 < uVar3) {
            SoftwareBreakpoint(0x5519, 0x6622b0); /* does not return */
        }
        _DAT_006fe7e0 = 0x20178 - uVar3;
    }
    return (_DAT_006fe7e0 + param_1 & 0xfffffffffffffff8) - 0x300;
}

/*--------------------------------------------------------------------*/
/* FUN_006622d8 @ 0x006622d8
 * Ghidra: ulong FUN_006622d8(long param_1)
 * Block allocation variant: (pool + param_1 aligned - base) & ~0xf - 0x300.
 * Panics on overflow.
 * Confidence: medium */
unsigned long sk_block_alloc_v_65_622d8(long param_1)
{
    long lVar4 = _DAT_006fe7e0;
    long lVar2 = sk_rt_00664bd4();
    if (lVar4 == 0) {
        unsigned long uVar3 = (0x1fd00 - (unsigned long)lVar2) & 0xfffffffffffffff0;
        if (uVar3 + (unsigned long)lVar2 < uVar3) goto overflow;
        lVar4 = 0x20178 - uVar3;
        _DAT_006fe7e0 = lVar4;
    }
    unsigned long uVar3 = ((lVar4 + param_1 & 0xfffffffffffffff8) - (unsigned long)lVar2 &
                           0xfffffffffffffff0) - 0x300;
    if (uVar3 <= uVar3 + (unsigned long)lVar2) {
        return uVar3;
    }
overflow:
    SoftwareBreakpoint(0x5519, 0x662354); /* does not return */
}

/*--------------------------------------------------------------------*/
/* FUN_00662368 @ 0x00662368
 * Ghidra: void FUN_00662368(long param_1, long *param_2, long *param_3)
 * Returns the TCB message range: *param_2 = base (0x130), *param_3 = limit-base.
 * Confidence: high (trivial read pair) */
void sk_tcb_msg_range_65_62368(unsigned long param_1, long *param_2, long *param_3)
{
    long lVar1 = *(long *)(param_1 + 0x130);
    *param_2 = lVar1;
    *param_3 = *(long *)(param_1 + 0x140) - lVar1;
}

/*--------------------------------------------------------------------*/
/* FUN_00662380 @ 0x00662380
 * Ghidra: void FUN_00662380(long param_1, undefined8 param_2, undefined8 param_3,
 *                          long param_4, long param_5)
 * Configures the TCB buffer window (0x30/0x38 ops, 0x138/0x140/0x130 limits,
 * 0x168/0x170 stack bounds).
 * Confidence: high (multi-field setter) */
void sk_tcb_window_set_65_62380(unsigned long param_1, unsigned long param_2, unsigned long param_3,
                                long param_4, long param_5)
{
    *(unsigned long *)(param_1 + 0x30) = param_2;
    *(unsigned long *)(param_1 + 0x38) = param_3;
    *(long *)(param_1 + 0x138) = param_5;
    *(long *)(param_1 + 0x140) = param_5 + param_4;
    *(long *)(param_1 + 0x130) = param_4;
    *(long *)(param_1 + 0x168) = param_4 + 0x4000;
    *(long *)(param_1 + 0x170) = param_5 + param_4;
}

/*--------------------------------------------------------------------*/
/* FUN_0066239c @ 0x0066239c
 * Ghidra: undefined8 FUN_0066239c(long param_1)
 * Returns the TCB cap word at +0x28.
 * Confidence: high (trivial read) */
unsigned long sk_tcb_cap_65_6239c(unsigned long param_1)
{
    return *(unsigned long *)(param_1 + 0x28);
}

/*--------------------------------------------------------------------*/
/* FUN_006623a4 @ 0x006623a4
 * Ghidra: undefined8 FUN_006623a4(long param_1)
 * Reads the message tag for TCB param_1 via FUN_006623d0 and returns the
 * composed tag word.
 * Confidence: medium */
unsigned long sk_tcb_tag_65_623a4(unsigned long param_1)
{
    unsigned char auStack_48[8];
    unsigned long local_40;
    sk_msg_recv_65_623d0((unsigned long *)&local_40, *(unsigned long *)(param_1 + 0x28));
    return local_40;
}

/*--------------------------------------------------------------------*/
/* FUN_006623d0 @ 0x006623d0
 * Ghidra: void FUN_006623d0(undefined8 *param_1, long param_2)
 * Message receive: builds a CallSupervisor(0) frame with the tag word
 * (0x1d/other) and fills param_1[0..6] from the returned message words,
 * decoding the tag type (0..4) into the result fields. When param_2!=0 the
 * message was empty (returns all zeros).
 * Confidence: low (CallSupervisor(0) frame decode). */
void sk_msg_recv_65_623d0(unsigned long *param_1, long param_2)
{
    param_1[5] = 0; param_1[6] = 0; param_1[3] = 0; param_1[4] = 0;
    param_1[1] = 0; param_1[2] = 0; *param_1 = 0;
    unsigned short *puVar6 = (unsigned short *)tpidrro_el0;
    unsigned short uVar7 = *puVar6;
    unsigned char bVar1 = (unsigned char)puVar6[1];
    unsigned short uVar8 = puVar6[2];
    unsigned char bVar2 = (unsigned char)puVar6[3];
    unsigned long uVar15 = (unsigned long)bVar1 << 0x10 |
        (unsigned long)*(unsigned char *)((char *)puVar6 + 3) << 0x18 | (unsigned long)uVar7 |
        (unsigned long)((unsigned int)bVar2 << 0x10 |
                        (unsigned int)*(unsigned char *)((char *)puVar6 + 7) << 0x18 |
                        (unsigned int)uVar8) << 0x20;
    CallSupervisor(0);
    if (param_2 != 0) {
        *param_1 = 0;
        return;
    }
    unsigned short uVar10 = puVar6[0x10];
    unsigned short uVar7b = puVar6[4];
    unsigned short uVar11 = puVar6[5];
    unsigned char bVar1b = *(unsigned char *)((char *)puVar6 + 0xb);
    unsigned short uVar8b = puVar6[6];
    unsigned short uVar12 = puVar6[7];
    unsigned char bVar2b = *(unsigned char *)((char *)puVar6 + 0xf);
    param_1[1] = (unsigned long)(unsigned char)puVar6[9] << 0x10 |
        (unsigned long)*(unsigned char *)((char *)puVar6 + 0x13) << 0x18 | (unsigned long)puVar6[8] |
        (unsigned long)((unsigned int)(unsigned char)puVar6[0xb] << 0x10 |
                        (unsigned int)*(unsigned char *)((char *)puVar6 + 0x17) << 0x18 |
                        (unsigned int)puVar6[10]) << 0x20;
    param_1[6] = (unsigned long)(unsigned char)puVar6[0xd] << 0x10 |
        (unsigned long)*(unsigned char *)((char *)puVar6 + 0x1b) << 0x18 | (unsigned long)puVar6[0xc] |
        (unsigned long)((unsigned int)(unsigned char)puVar6[0xf] << 0x10 |
                        (unsigned int)*(unsigned char *)((char *)puVar6 + 0x1f) << 0x18 |
                        (unsigned int)puVar6[0xe]) << 0x20;
    unsigned char uVar3 = *(unsigned char *)((char *)puVar6 + 0x21);
    unsigned char bVar4 = *(unsigned char *)((char *)puVar6 + 0x23);
    unsigned short uVar13 = puVar6[0x11];
    unsigned short uVar9 = puVar6[0x12];
    unsigned char bVar5 = *(unsigned char *)((char *)puVar6 + 0x27);
    unsigned short uVar14 = puVar6[0x13];
    param_1[3] = (unsigned long)(unsigned char)uVar11 << 0x10 | (unsigned long)bVar1b << 0x18 |
        (unsigned long)uVar7b |
        (unsigned long)((unsigned int)(unsigned char)uVar12 << 0x10 |
                        (unsigned int)bVar2b << 0x18 | (unsigned int)uVar8b) << 0x20;
    param_1[4] = (unsigned long)(unsigned char)uVar13 << 0x10 | (unsigned long)bVar4 << 0x18 |
        (unsigned long)((unsigned char)uVar3 | (unsigned short)((unsigned char)uVar10) << 8) |
        (unsigned long)((unsigned int)(unsigned char)uVar14 << 0x10 |
                        (unsigned int)bVar5 << 0x18 | (unsigned int)uVar9) << 0x20;
    if ((long)uVar15 < 2) {
        if (uVar15 != 0) {
            if (uVar15 != 1) {
                return;
            }
            *param_1 = 1;
            return;
        }
        *param_1 = 0;
        return;
    }
    unsigned long uVar16;
    if (uVar15 == 2) {
        uVar16 = 2;
    } else {
        if (uVar15 != 3) {
            if (uVar15 != 4) {
                return;
            }
            *param_1 = 3;
            *(unsigned char *)(param_1 + 2) = 1;
            goto mark;
        }
        uVar16 = 4;
    }
    *param_1 = uVar16;
mark:
    *(unsigned char *)(param_1 + 5) = 1;
}

/*--------------------------------------------------------------------*/
/* FUN_00662628 @ 0x00662628
 * Ghidra: void FUN_00662628(long param_1, undefined4 param_2)
 * Stores the thread name tag at TCB+0x118.
 * Confidence: high (trivial setter) */
void sk_tcb_name_set_65_62628(unsigned long param_1, unsigned int param_2)
{
    *(unsigned int *)(param_1 + 0x118) = param_2;
}

/*--------------------------------------------------------------------*/
/* FUN_00662630 @ 0x00662630
 * Ghidra: void FUN_00662630(long param_1, undefined8 param_2)
 * Boot-log printer: sanitizes and prints the cpu id, capability, allocator and
 * name-tag fields, then panics via FUN_0065c984.
 * Confidence: medium */
void sk_boot_print_65_62630(unsigned long param_1, unsigned long param_2)
{
    unsigned int uVar2 = sk_rt_0065ca28();
    unsigned long uVar3 = sk_rt_006645bc(*(unsigned long *)(param_1 + 0xa8));
    unsigned long uVar4 = sk_rt_006833bc(*(unsigned long *)(param_1 + 8));
    unsigned int uVar1 = *(unsigned int *)(param_1 + 0x118);
    sk_tag_sanitize_65f8e8(uVar2);
    sk_tag_sanitize_65f8e8(uVar3);
    sk_tag_sanitize_65f8e8(uVar4);
    sk_tag_sanitize_65f8e8(uVar1);
    sk_rt_0065c984(param_2, 0xffffffffffffffff, 0x14, 0x6a73ee);
}

/*--------------------------------------------------------------------*/
/* FUN_006626f0 @ 0x006626f0
 * Ghidra: undefined8 FUN_006626f0(long param_1)
 * Returns the TCB+0x120 word.
 * Confidence: high (trivial read) */
unsigned long sk_tcb_read_120_65_626f0(unsigned long param_1)
{
    return *(unsigned long *)(param_1 + 0x120);
}

/*--------------------------------------------------------------------*/
/* FUN_006626f8 @ 0x006626f8
 * Ghidra: void FUN_006626f8(long param_1, long param_2)
 * Installs the TCB message/IO object (param_2) at +8, releasing the prior one
 * (FUN_0065ce40) and clearing +0x10.
 * Confidence: medium */
void sk_tcb_obj_set_65_626f8(unsigned long param_1, unsigned long param_2)
{
    if (param_2 != 0) {
        sk_rt_0065ce40(param_2);
    }
    *(long *)(param_1 + 8) = param_2;
    *(unsigned long *)(param_1 + 0x10) = 0;
}

/*--------------------------------------------------------------------*/
/* FUN_0066272c @ 0x0066272c
 * Ghidra: void FUN_0066272c(undefined8 *param_1, long param_2)
 * Clears a message word set for thread param_2, or reads the current thread's
 * tag via FUN_00662754 when param_2 is another thread.
 * Confidence: medium */
void sk_msg_clear_65_6272c(unsigned long *param_1, unsigned long param_2)
{
    param_1[3] = 0; param_1[4] = 0; param_1[1] = 0; param_1[2] = 0; *param_1 = 0;
    unsigned long lVar1 = tpidr_el0;
    if (param_2 != *(long *)(lVar1 + 8)) {
        sk_msg_send2_65_62754((unsigned long *)0, *(unsigned long *)(param_2 + 0x28));
        return;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_00662754 @ 0x00662754
 * Ghidra: void FUN_00662754(ulong *param_1, ulong param_2)
 * Message send: builds a CallSupervisor(0) frame with the 0x1d tag and the
 * constant capability words (0x6a89dd0), sends, and when the status word is
 * zero fills param_1[0..4] from the returned message registers; otherwise maps
 * the error (FUN_00685164) and faults via FUN_0067f660.
 * Confidence: low (CallSupervisor(0) frame decode). */
void sk_msg_send2_65_62754(unsigned long *param_1, unsigned long param_2)
{
    unsigned long lVar9 = _DAT_006b5ed0;
    unsigned long uVar8 = uRam0000000000689dd8;
    unsigned long uVar10 = _DAT_00689dd0;
    unsigned char *puVar5 = (unsigned char *)tpidrro_el0;
    /* frame[0..0xf] = little-endian (uVar10, uVar8) */
    puVar5[0] = (unsigned char)uVar10;
    puVar5[1] = (unsigned char)(uVar10 >> 8);
    puVar5[2] = (unsigned char)(uVar10 >> 0x10);
    puVar5[3] = (unsigned char)(uVar10 >> 0x18);
    puVar5[4] = (unsigned char)(uVar10 >> 0x20);
    puVar5[5] = (unsigned char)(uVar10 >> 0x28);
    puVar5[6] = (unsigned char)(uVar10 >> 0x30);
    puVar5[7] = (unsigned char)(uVar10 >> 0x38);
    puVar5[8] = (unsigned char)uVar8;
    puVar5[9] = (unsigned char)(uVar8 >> 8);
    puVar5[10] = (unsigned char)(uVar8 >> 0x10);
    puVar5[0xb] = (unsigned char)(uVar8 >> 0x18);
    puVar5[0xc] = (unsigned char)(uVar8 >> 0x20);
    puVar5[0xd] = (unsigned char)(uVar8 >> 0x28);
    puVar5[0xe] = (unsigned char)(uVar8 >> 0x30);
    puVar5[0xf] = (unsigned char)(uVar8 >> 0x38);
    CallSupervisor(0);
    puVar5[0] = 0x1d;
    puVar5[7] = 0; puVar5[6] = 0; puVar5[5] = 0; puVar5[4] = 0;
    puVar5[3] = 0; puVar5[2] = 0; puVar5[1] = 0;
    if ((param_2 & 0xff) == 0) {
        unsigned short uVar6 = *(unsigned short *)(puVar5 + 0x20);
        unsigned char bVar1 = puVar5[0x23];
        unsigned char bVar2 = puVar5[0x22];
        unsigned short uVar7 = *(unsigned short *)(puVar5 + 0x24);
        unsigned char bVar3 = puVar5[0x27];
        unsigned char bVar4 = puVar5[0x26];
        param_1[1] = (unsigned long)(unsigned char)puVar5[0x2a] << 0x10 |
            (unsigned long)(unsigned char)puVar5[0x2b] << 0x18 |
            (unsigned long)*(unsigned short *)(puVar5 + 0x28) |
            (unsigned long)((unsigned int)(unsigned char)puVar5[0x2e] << 0x10 |
                            (unsigned int)(unsigned char)puVar5[0x2f] << 0x18 |
                            (unsigned int)*(unsigned short *)(puVar5 + 0x2c)) << 0x20;
        param_1[0] = (unsigned long)bVar2 << 0x10 | (unsigned long)bVar1 << 0x18 |
            (unsigned long)uVar6 |
            (unsigned long)((unsigned int)bVar4 << 0x10 | (unsigned int)bVar3 << 0x18 |
                            (unsigned int)uVar7) << 0x20;
        unsigned short uVar6b = *(unsigned short *)(puVar5 + 0x10);
        unsigned char bVar1b = puVar5[0x13];
        unsigned char bVar2b = puVar5[0x12];
        unsigned short uVar7b = *(unsigned short *)(puVar5 + 0x14);
        unsigned char bVar3b = puVar5[0x17];
        unsigned char bVar4b = puVar5[0x16];
        param_1[2] = (unsigned long)(unsigned char)puVar5[0x1a] << 0x10 |
            (unsigned long)(unsigned char)puVar5[0x1b] << 0x18 |
            (unsigned long)*(unsigned short *)(puVar5 + 0x18) |
            (unsigned long)((unsigned int)(unsigned char)puVar5[0x1e] << 0x10 |
                            (unsigned int)(unsigned char)puVar5[0x1f] << 0x18 |
                            (unsigned int)*(unsigned short *)(puVar5 + 0x1c)) << 0x20;
        param_1[3] = (unsigned long)bVar2b << 0x10 | (unsigned long)bVar1b << 0x18 |
            (unsigned long)uVar6b |
            (unsigned long)((unsigned int)bVar4b << 0x10 | (unsigned int)bVar3b << 0x18 |
                            (unsigned int)uVar7b) << 0x20;
        param_1[4] = (unsigned long)(unsigned char)puVar5[0x32] << 0x10 |
            (unsigned long)(unsigned char)puVar5[0x33] << 0x18 |
            (unsigned long)*(unsigned short *)(puVar5 + 0x30) |
            (unsigned long)((unsigned int)(unsigned char)puVar5[0x36] << 0x10 |
                            (unsigned int)(unsigned char)puVar5[0x37] << 0x18 |
                            (unsigned int)*(unsigned short *)(puVar5 + 0x34)) << 0x20;
        if (_DAT_006b5ed0 == lVar9) {
            return;
        }
    } else {
        unsigned long auVar11[2];
        sk_u128_t r = sk_rt_00685164(param_2, (unsigned char *)0);
        param_2 = r.lo;
        uVar10 = r.hi;
    }
    sk_fatal(param_2, uVar10); /* does not return */
}

/*--------------------------------------------------------------------*/
/* FUN_00662a40 @ 0x00662a40
 * Ghidra: void FUN_00662a40(undefined8 param_1, byte param_2)
 * Copies an L4 error string (0x20 bytes) into param_1; for codes >9 uses the
 * fallback buffer (0x6a89f20) and faults via FUN_0065c984.
 * Confidence: high (error-string copy) */
void sk_err_str_c_65_62a40(unsigned long param_1, unsigned char param_2)
{
    const char *pcVar1;
    if (9 < param_2) {
        sk_memmove((void *)param_1, (const void *)&DAT_00689f20, 0x20);
        sk_rt_0065c984(param_1, 0x20, 0x1f, 0x6a5139);
        return;
    }
    switch (param_2) {
    default: pcVar1 = "Success"; break;
    case 1: pcVar1 = "Preempted"; break;
    case 2: pcVar1 = "Canceled"; break;
    case 3: pcVar1 = "Truncated"; break;
    case 4: pcVar1 = "CapInvalid"; break;
    case 5: pcVar1 = "SlotInvalid"; break;
    case 6: pcVar1 = "MethodInvalid"; break;
    case 7: pcVar1 = "ArgumentInvalid"; break;
    case 8: pcVar1 = "OperationInvalid"; break;
    case 9: pcVar1 = "PermissionInvalid"; break;
    }
    sk_memmove((void *)param_1, pcVar1, 0x20);
}

/*--------------------------------------------------------------------*/
/* FUN_00662b84 @ 0x00662b84
 * Ghidra: undefined8 FUN_00662b84(long param_1)
 * Reads the message word for thread param_1: returns the current thread's word
 * directly, or resolves another thread's via FUN_00662754.
 * Confidence: medium */
unsigned long sk_msg_word_tcb_65_62b84(unsigned long param_1)
{
    unsigned long lVar1 = tpidr_el0;
    unsigned long local_28 = (unsigned long)__builtin_frame_address(0);
    if (param_1 != *(long *)(lVar1 + 8)) {
        unsigned long local_40 = 0, uStack_38 = 0, uStack_30 = 0;
        local_28 = 0;
        lVar1 = tpidr_el0;
        if (param_1 == *(long *)(lVar1 + 8)) {
            local_28 = 0;
        } else {
            sk_msg_send2_65_62754(&local_40, *(unsigned long *)(param_1 + 0x28));
        }
    }
    return local_28;
}

/*--------------------------------------------------------------------*/
/* FUN_00662bf0 @ 0x00662bf0
 * Ghidra: void FUN_00662bf0(undefined8 param_1, long param_2)
 * Dumps the message/capability words of thread param_2 through the logger
 * param_1: collects the up-to-16 cap words (FUN_00662754 + FUN_0065cda8 for the
 * region tags), prints each via FUN_0067d1f0, and resolves overflow/underflow
 * panics.
 * Confidence: low (log walk with cap resolution). */
void sk_caps_dump_65_62bf0(unsigned long param_1, unsigned long param_2)
{
    unsigned long local_78 = _DAT_006b5ed0;
    unsigned long local_100[17];
    unsigned long local_130[6];
    for (int i = 0; i < 17; i++) local_100[i] = 0;
    for (int i = 0; i < 6; i++) local_130[i] = 0;
    unsigned long lVar11 = tpidr_el0;
    lVar11 = *(long *)(lVar11 + 8);
    unsigned long lVar4;
    if (param_2 == lVar11) {
        lVar4 = 0;
    } else {
        lVar4 = tpidr_el0;
        if (param_2 != *(long *)(lVar4 + 8)) {
            sk_msg_send2_65_62754(local_130, *(unsigned long *)(param_2 + 0x28));
        }
        local_130[5] = local_130[0];
        long lVar4b = sk_bucket_lookup(local_130 + 5, 0);
        if (lVar4b == 0) {
            local_100[0] = 0xffff000000000000;
        } else {
            local_100[0] = (unsigned long)*(unsigned short *)(lVar4b + 0x40) << 0x30;
        }
        local_100[0] = local_130[5] & 0xffffffffffff | local_100[0];
        local_130[5] = local_130[2];
        lVar4b = sk_bucket_lookup(local_130 + 5, 0);
        if (lVar4b == 0) {
            local_100[1] = 0xffff000000000000;
        } else {
            local_100[1] = (unsigned long)*(unsigned short *)(lVar4b + 0x40) << 0x30;
        }
        local_100[1] = local_130[5] & 0xffffffffffff | local_100[1];
        lVar4 = 2;
    }
    local_130[0] = sk_msg_word_tcb_65_62b84(param_2);
    unsigned long *puVar10 = local_100 + lVar4;
    if ((local_100 + 0x10 < puVar10) || (puVar10 < local_100)) {
        SoftwareBreakpoint(0x5519, 0x662f08); /* does not return */
    }
    unsigned long lVar5 = sk_msg_word_65_61d38(param_2, local_130, (unsigned long)puVar10, 0x10 - lVar4, 0, 0);
    unsigned long uVar7 = lVar5 + lVar4;
    if (uVar7 != 0) {
        unsigned long lVar4b = 0;
        do {
            unsigned long uVar1 = uVar7;
            if (0xf < uVar7) {
                uVar1 = 0x10;
            }
            unsigned long uVar9 = uVar1;
            unsigned long *puVar10b = local_100;
            unsigned long lVar5b = lVar4b;
            do {
                unsigned long uVar12 = *puVar10b;
                local_130[5] = uVar12;
                long lVar6 = sk_bucket_lookup(local_130 + 5, 1);
                unsigned long uVar2 = uVar12 - 4;
                if (lVar5b == 0 && param_2 != lVar11) {
                    uVar2 = uVar12;
                }
                unsigned long uVar8;
                if (lVar6 == 0) {
                    uVar8 = 0x6a7679;
                } else {
                    unsigned long local_138 = 0;
                    sk_rt_00655e1c(uVar2, &local_138);
                    uVar8 = 0x6a75e3;
                }
                sk_rt_0067d1f0(param_1, uVar8);
                lVar5b += 1;
                uVar9 -= 1;
                puVar10b += 1;
            } while (uVar9 != 0);
            if (uVar7 < 0x11) break;
            lVar4b = uVar1 + lVar4b;
            uVar7 = sk_msg_word_65_61d38(param_2, local_130, (unsigned long)local_100, 0x10, 0, 0);
        } while (uVar7 != 0);
    }
    if (_DAT_006b5ed0 != local_78) {
        sk_fatal(0); /* does not return */
    }
}

/*--------------------------------------------------------------------*/
/* FUN_00662f0c @ 0x00662f0c
 * Ghidra: bool FUN_00662f0c(long param_1, long param_2)
 * Reads the per-cpu interrupt vector table for thread param_1 into param_2
 * (0x69 words of 8 bytes each) via a CallSupervisor(0) probe, returning whether
 * the vector was populated (lVar4 != 0).
 * Confidence: high (verified against fresh decompile 2026-08-12; restored the
 * dropped pre-/post-CallSupervisor tag-byte zeroing stores at offsets 2-7 so
 * the message construction now matches ground truth). */
bool sk_intvec_read_65_62f0c(unsigned long param_1, unsigned long param_2)
{
    unsigned long uVar9 = 0;
    unsigned long lVar4;
    unsigned int uVar8 = 0;
    unsigned short *puVar2 = (unsigned short *)tpidrro_el0;
    do {
        uVar8 = (unsigned int)uVar9;
        lVar4 = *(long *)(param_1 + 0x28);
        *(unsigned char *)(puVar2 + 2) = 0;          /* byte offset 4 */
        *(unsigned char *)((char *)puVar2 + 5) = 0;  /* byte offset 5 */
        *(unsigned char *)(puVar2 + 1) = 0;          /* byte offset 2 */
        unsigned long uVar1 = 0x36;
        if (0x32 < (uVar8 & 0xffff)) {
            uVar1 = 0x69 - uVar8;
        }
        *(unsigned char *)((char *)puVar2 + 3) = 0;  /* byte offset 3 */
        *(unsigned char *)(puVar2 + 3) = 0;          /* byte offset 6 */
        unsigned long uVar5 = ~(0xffffffffffffffffUL << (uVar1 & 0x3f));
        *(char *)puVar2 = (char)uVar9;               /* byte offset 0 */
        *(unsigned char *)((char *)puVar2 + 7) = 0;  /* byte offset 7 */
        *(unsigned char *)((char *)puVar2 + 1) = (char)(uVar9 >> 8); /* byte offset 1 */
        *(unsigned char *)((char *)puVar2 + 0xd) = (char)(uVar5 >> 0x28);
        *(unsigned char *)(puVar2 + 4) = (char)uVar5;
        *(unsigned char *)((char *)puVar2 + 0xb) = (char)(uVar5 >> 0x18);
        *(unsigned char *)(puVar2 + 5) = (char)(uVar5 >> 0x10);
        *(unsigned char *)((char *)puVar2 + 9) = (char)(uVar5 >> 8);
        *(unsigned char *)(puVar2 + 6) = (char)(uVar5 >> 0x20);
        *(unsigned char *)((char *)puVar2 + 0xf) = (char)(uVar5 >> 0x38);
        *(unsigned char *)(puVar2 + 7) = (char)(uVar5 >> 0x30);
        CallSupervisor(0);
        *(char *)puVar2 = (char)(uVar9 & 0xffff);    /* byte offset 0 */
        *(unsigned char *)((char *)puVar2 + 7) = 0;  /* byte offset 7 */
        *(unsigned char *)(puVar2 + 3) = 0;          /* byte offset 6 */
        *(unsigned char *)((char *)puVar2 + 5) = 0;  /* byte offset 5 */
        *(unsigned char *)(puVar2 + 2) = 0;          /* byte offset 4 */
        *(unsigned char *)((char *)puVar2 + 3) = 0;  /* byte offset 3 */
        *(unsigned char *)(puVar2 + 1) = 0;          /* byte offset 2 */
        *(unsigned char *)((char *)puVar2 + 1) = (char)((uVar9 & 0xffff) >> 8); /* byte offset 1 */
        if (lVar4 != 0) break;
        unsigned long uVar5b = (unsigned long)uVar1 & 0xffff;
        if (((uVar9 & 0x1fff) * -8 + 0x348) >> 3 < uVar5b) {
            SoftwareBreakpoint(0x5519, 0x6630f8); /* does not return */
        }
        unsigned long *puVar6 = (unsigned long *)(param_2 + (uVar9 & 0x1fff) * 8);
        unsigned short *puVar7 = puVar2 + 8;
        unsigned long uVar9b = uVar5b;
        do {
            if ((puVar7 < puVar2) || (puVar2 + 0xe0 < puVar7 + 4)) {
                SoftwareBreakpoint(0x5519, 0x6630f8); /* does not return */
            }
            *puVar6 = (unsigned long)(unsigned char)puVar7[1] << 0x10 |
                (unsigned long)*(unsigned char *)((char *)puVar7 + 3) << 0x18 |
                (unsigned long)*puVar7 |
                (unsigned long)((unsigned int)(unsigned char)puVar7[3] << 0x10 |
                                (unsigned int)*(unsigned char *)((char *)puVar7 + 7) << 0x18 |
                                (unsigned int)puVar7[2]) << 0x20;
            puVar7 += 4;
            uVar9b -= 1;
            puVar6 += 1;
        } while (uVar9b != 0);
        uVar8 = (int)uVar5b + uVar8;
        uVar9 = (unsigned long)uVar8;
    } while ((uVar8 & 0xffff) < 0x69);
    return lVar4 == 0;
}

/*--------------------------------------------------------------------*/
/* FUN_006630f8 @ 0x006630f8
 * Ghidra: void FUN_006630f8(undefined8 param_1, undefined8 param_2)
 * Prints the interrupt vector table for thread param_2 via the logger param_1,
 * alternating two label strings per word (0x6a76c0 / 0x6a76cf + newline).
 * Confidence: medium */
void sk_intvec_print_65_630f8(unsigned long param_1, unsigned long param_2)
{
    unsigned char local_398[840];
    sk_memzero((void *)local_398, 0x200);
    int iVar1 = sk_intvec_read_65_62f0c(param_2, (unsigned long)local_398);
    if (iVar1 == 0) {
        sk_rt_0067d1f0(param_1, 0x6a7694);
    } else {
        unsigned long uVar2 = 0;
        do {
            sk_rt_0067d1f0(param_1, 0x6a76c0);
            if ((uVar2 & 1) == 0) {
                sk_rt_0067d440(0x6a76cf, param_1);
            } else {
                sk_rt_0067d3f8(10, param_1);
            }
            uVar2 += 1;
        } while (uVar2 != 0x69);
    }
}

/*--------------------------------------------------------------------*/
/* FUN_006631d8 @ 0x006631d8
 * Ghidra: void FUN_006631d8(undefined8 param_1, undefined8 param_2,
 *                          undefined8 param_3, long param_4, int param_5,
 *                          int param_6, ulong param_7, ulong param_8)
 * Comprehensive boot-log dump for thread param_4: prints the version, sched
 * gate, clock name, TCB range, capability vector (param_6), int-vector
 * (param_5), and optional region info (param_7/param_8), using the format
 * helpers FUN_0067d1f0 / FUN_0067d6c0 / FUN_0067d3f8.
 * Confidence: low (log-format sequence) */
void sk_boot_dump_65_631d8(unsigned long param_1, unsigned long param_2, unsigned long param_3,
                           unsigned long param_4, int param_5, int param_6,
                           unsigned long param_7, unsigned long param_8)
{
    unsigned long local_68 = _DAT_006b5ed0;
    sk_pad_print_65_634c0(param_3, param_2, param_1);
    unsigned long local_98 = 0;
    long lVar1 = sk_rt_0065c9c0(&local_98);
    if (lVar1 == 0) {
        local_98 = 1;
    }
    sk_rt_0067d1f0(param_3, 0x6a76d3);
    unsigned long local_a0 = 0;
    lVar1 = sk_clock_name_65e138(0, (long *)&local_a0);
    if (lVar1 == 0) {
        local_a0 = 1;
    }
    sk_rt_0067d1f0(param_3, 0x6a76e8);
    sk_rt_00655d7c();
    sk_rt_0067d1f0(param_3, 0x6a76f9);
    sk_rt_00655d9c();
    sk_rt_0067d1f0(param_3, 0x6a7712);
    unsigned long local_78 = 0, local_70 = 0;
    sk_rt_00655dbc(&local_78);
    sk_rt_0067d1f0(param_3, 0x6a772a);
    sk_pad_print_65_634c0(param_3, param_2, 0);
    unsigned char auStack_8c[20];
    sk_boot_print_65_62630(param_4, (unsigned long)auStack_8c);
    long lVar1b = *(long *)(param_4 + 0x130);
    sk_rt_0067d1f0(param_3, 0x6a7796);
    sk_rt_0067d1f0(param_3, 0x6a77af);
    if (param_7 != 0) {
        sk_rt_0067d1f0(param_3, 0x6a77d1);
        if ((*(unsigned long *)(param_4 + 0x130) <= param_8) &&
            (param_8 < (unsigned long)lVar1b + 0x4000)) {
            sk_rt_0067d1f0(param_3, 0x6a77ed);
        }
        if ((param_7 & 0x3f) == 0x11) {
            sk_rt_0067d6c0(0x6a7817, 0x1c, 1, param_3);
        }
    }
    if (param_6 != 0) {
        sk_rt_0067d6c0(0x6a7834, 0xc, 1, param_3);
        sk_intvec_print_65_630f8(param_3, param_4);
    }
    if (param_5 != 0) {
        sk_rt_0067d6c0(0x6a7841, 0xc, 1, param_3);
        sk_caps_dump_65_62bf0(param_3, param_4);
    }
    sk_pad_print_65_634c0(param_3, param_2, 0);
    if (_DAT_006b5ed0 != local_68) {
        sk_fatal(0); /* does not return */
    }
}

/*--------------------------------------------------------------------*/
/* FUN_006634c0 @ 0x006634c0
 * Ghidra: void FUN_006634c0(undefined8 param_1, undefined8 param_2, long param_3)
 * Padding/frame printer: emits a fixed pad of 0x48 separator glyphs when
 * param_3==0; otherwise pads around the label string at 0x6a7a1f.
 * Confidence: medium */
void sk_pad_print_65_634c0(unsigned long param_1, unsigned long param_2, unsigned long param_3)
{
    if (param_3 == 0) {
        long lVar2 = 0x48;
        do {
            sk_rt_0067d3f8(param_2, param_1);
            lVar2 -= 1;
        } while (lVar2 != 0);
    } else {
        long lVar2 = sk_rt_0067b220(param_3);
        unsigned long uVar3 = (0x46 - (unsigned long)lVar2) >> 1;
        unsigned long uVar4 = uVar3;
        if (1 < 0x46 - (unsigned long)lVar2) {
            do {
                sk_rt_0067d3f8(param_2, param_1);
                uVar4 -= 1;
            } while (uVar4 != 0);
        }
        sk_rt_0067d1f0(param_1, 0x6a7a1f);
        if (lVar2 + 2 + (long)uVar3 != 0x48) {
            long lVar2b = lVar2 + (long)uVar3 - 0x46;
            do {
                sk_rt_0067d3f8(param_2, param_1);
                lVar2b += 1;
            } while (lVar2b != -1);
        }
    }
    sk_rt_0067d3f8(10, param_1);
}

/*--------------------------------------------------------------------*/
/* FUN_006635ac @ 0x006635ac
 * Ghidra: bool FUN_006635ac(long param_1)
 * Tests whether TCB param_1 is bound/active: (0x48 & 0x41) != 0.
 * Confidence: high (trivial test) */
bool sk_tcb_bound_65_635ac(unsigned long param_1)
{
    return (*(unsigned char *)(param_1 + 0x48) & 0x41) != 0;
}

/*--------------------------------------------------------------------*/
/* FUN_006635c0 @ 0x006635c0
 * Ghidra: undefined8 FUN_006635c0(long param_1, undefined8 param_2)
 * Ref-counts an active user on TCB param_1: when the 0x48 bit1 is clear and
 * the current count (+0x90) is nonzero, verifies the peer (FUN_0067d014),
 * setting bit1; then increments the count and returns 1.
 * Confidence: medium */
unsigned long sk_user_ref_65_635c0(unsigned long param_1, unsigned long param_2)
{
    if (((*(unsigned char *)(param_1 + 0x48) >> 1 & 1) == 0) && (*(long *)(param_1 + 0x90) != 0)) {
        int iVar1 = sk_rt_0067d014(param_2);
        if (iVar1 == 0) {
            *(unsigned long *)(param_1 + 0x48) &= 0xfffffffffffffffd;
        } else {
            *(unsigned long *)(param_1 + 0x48) |= 2;
        }
    }
    *(long *)(param_1 + 0x90) += 1;
    return 1;
}

/*--------------------------------------------------------------------*/
/* FUN_0066363c @ 0x0066363c
 * Ghidra: undefined8 FUN_0066363c(long param_1, undefined8 param_2)
 * Ref-counts a user on TCB param_1 like FUN_006635c0 but returns 0 when the
 * peer verify failed.
 * Confidence: medium */
unsigned long sk_user_ref_b_65_6363c(unsigned long param_1, unsigned long param_2)
{
    if (((*(unsigned char *)(param_1 + 0x48) >> 1 & 1) == 0) && (*(long *)(param_1 + 0x90) != 0)) {
        int iVar1 = sk_rt_0067d014(param_2);
        if (iVar1 == 0) {
            *(unsigned long *)(param_1 + 0x48) &= 0xfffffffffffffffd;
            return 0;
        }
        *(unsigned long *)(param_1 + 0x48) |= 2;
    }
    *(long *)(param_1 + 0x90) += 1;
    return 1;
}

/*--------------------------------------------------------------------*/
/* FUN_00663644 @ 0x00663644
 * Ghidra: void FUN_00663644(long param_1, undefined8 param_2)
 * Releases a user ref on TCB param_1: decrements +0x90 and, when it reaches
 * zero, clears bit1 and notifies the peer (FUN_0067d02c) if it was pending.
 * Confidence: medium */
void sk_user_unref_65_63644(unsigned long param_1, unsigned long param_2)
{
    long lVar1 = *(long *)(param_1 + 0x90) - 1;
    *(long *)(param_1 + 0x90) = lVar1;
    if (lVar1 == 0) {
        unsigned long uVar2 = *(unsigned long *)(param_1 + 0x48);
        *(unsigned long *)(param_1 + 0x48) = uVar2 & 0xfffffffffffffffd;
        if (((unsigned int)uVar2 >> 1 & 1) != 0) {
            sk_rt_0067d02c(param_2);
            return;
        }
    }
}

/*--------------------------------------------------------------------*/
/* FUN_006636f8 @ 0x006636f8
 * Ghidra: ulong FUN_006636f8(ulong param_1)
 * Resolves an address to a capability word: looks up the region (FUN_0065cda8)
 * and, on success, ORs in the region tag (ushort at +0x40) in the high word.
 * Confidence: medium */
unsigned long sk_addr_to_cap_65_636f8(unsigned long param_1)
{
    unsigned long local_18 = param_1;
    long lVar1 = sk_bucket_lookup(&local_18, 0);
    unsigned long uVar2;
    if (lVar1 == 0) {
        uVar2 = 0xffff000000000000;
    } else {
        uVar2 = (unsigned long)*(unsigned short *)(lVar1 + 0x40) << 0x30;
    }
    return local_18 & 0xffffffffffff | uVar2;
}

/*--------------------------------------------------------------------*/
/* FUN_00663744 @ 0x00663744
 * Ghidra: void FUN_00663744(int param_1, undefined4 param_2)
 * Boot-name lookup by kind: scans the boot-info block for a node matching the
 * selector param_1 (0x11 for kinds <0x50, else 0x13) and returns the composed
 * 4-byte name. Panics (0x6a78fc) when not found or when boot info is absent.
 * Confidence: low (boot-info parse) */
unsigned long sk_boot_name_65_63744(int param_1, unsigned int param_2)
{
    unsigned long uVar12 = sk_rt_00652204();
    if ((uVar12 & 1) == 0) {
        sk_rt_00654cf4();
        return 0;
    }
    int iVar15;
    unsigned int uVar13;
    if (param_1 < 0x50) {
        iVar15 = 0x11;
        uVar13 = 0;
        if ((param_1 == 1) || (param_1 != 2)) goto scan;
    }
    iVar15 = 0x13;
    uVar13 = param_2;
scan:
    uVar12 = sk_rt_006510cc();
    if (uVar12 != 0) {
        if (uVar12 + 8 < uVar12) {
            SoftwareBreakpoint(0x5519, 0x6638c4); /* does not return */
        }
    }
    unsigned char local_50[16];
    sk_u128_t lt = sk_rt_00650ec8();
    local_50[0] = (unsigned char)lt.lo;
    local_50[8] = (unsigned char)lt.hi;
    uVar12 = sk_rt_00651074((unsigned long)local_50);
    if ((uVar12 & 1) == 0) {
        unsigned short *puVar14 = 0;
        int iVar11;
        do {
            uVar12 = sk_rt_00650ed0((unsigned long)local_50);
            if ((uVar12 != 0) && (uVar12 + 0xc < uVar12)) {
                SoftwareBreakpoint(0x5519, 0x6638c4); /* does not return */
            }
            iVar11 = (int)sk_rt_00650c10(uVar12);
            if (iVar11 == iVar15) {
                puVar14 = (unsigned short *)sk_rt_00650b3c(uVar12, uVar13);
            }
            iVar11 = (int)sk_rt_00651074((unsigned long)local_50);
        } while (iVar11 == 0);
        if (puVar14 != 0) {
            unsigned short *puVar1 = puVar14 + 0xc;
            if (param_1 != 2) {
                puVar1 = puVar14;
            }
            unsigned short *puVar2 = puVar14;
            if (param_1 != 1) {
                puVar2 = puVar1;
            }
            unsigned short *puVar14b = puVar14 + 4;
            if (param_1 < 0x50) {
                puVar14b = puVar2;
            }
            unsigned short uVar5 = *puVar14b;
            unsigned char bVar3 = *(unsigned char *)((char *)puVar14b + 3);
            unsigned short uVar8 = puVar14b[1];
            unsigned short uVar6 = puVar14b[2];
            unsigned char bVar4 = *(unsigned char *)((char *)puVar14b + 7);
            unsigned short uVar9 = puVar14b[3];
            unsigned char local_60[16];
            sk_u128_t lt2 = sk_rt_00651108();
            local_60[0] = (unsigned char)lt2.lo;
            local_60[8] = (unsigned char)lt2.hi;
            unsigned long name = (unsigned long)(unsigned char)uVar8 << 0x10 |
                (unsigned long)bVar3 << 0x18 | (unsigned long)uVar5 |
                (unsigned long)((unsigned int)(unsigned char)uVar9 << 0x10 |
                                (unsigned int)bVar4 << 0x18 | (unsigned int)uVar6) << 0x20;
            return sk_rt_00650af8((unsigned long)local_60, name);
        }
    }
    sk_panic_2(0, 0x6a78fc); /* does not return */
}

/*--------------------------------------------------------------------*/
/* FUN_006638d8 @ 0x006638d8
 * Ghidra: void FUN_006638d8(void)
 * Thin forwarder to the error-string mapper FUN_00662a40 (stack slot 0x10).
 * Confidence: high (thin) */
void sk_err_str_fwd_65_638d8(void)
{
    sk_err_str_c_65_62a40(0x10, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_006638f8 @ 0x006638f8
 * Ghidra: void FUN_006638f8(void)
 * Panics with the 0x6a7886 message.
 * Confidence: high (unconditional panic) */
void sk_panic_7886_65_638f8(void)
{
    sk_panic_2(0, 0x6a7886); /* does not return */
}

/*--------------------------------------------------------------------*/
/* FUN_00663910 @ 0x00663910
 * Ghidra: void FUN_00663910(void)
 * Panics with the 0x6a785c message.
 * Confidence: high (unconditional panic) */
void sk_panic_785c_65_63910(void)
{
    sk_panic_2(0, 0x6a785c); /* does not return */
}

/*--------------------------------------------------------------------*/
/* FUN_00663928 @ 0x00663928
 * Ghidra: void FUN_00663928(ulong *param_1, ulong param_2, long *param_3)
 * Publishes a timer request for thread param_2: clears a 0x50-byte slot,
 * registers the wait (FUN_0065dda4), stores the requested time (param_2) and
 * copies the 0x28-byte capability frame (param_3), then sets the wake callback
 * (per-cpu slot or FUN_00663ac8) and dispatches CallSupervisor(0). On error
 * faults via FUN_0067f660; panics (0x6a7c2d) when the slot is busy.
 * Confidence: low (timer publish; CallSupervisor(0) frame). */
void sk_timer_publish_65_63928(unsigned long *param_1, unsigned long param_2, long *param_3)
{
    unsigned long local_48 = _DAT_006b5ed0;
    sk_memzero((void *)param_1, 0x50);
    if (param_1 + 2 < param_1) {
        SoftwareBreakpoint(0x5519, 0x663aac); /* does not return */
    }
    unsigned long uVar9 = sk_timer_dec_alt_65dda4(param_1);
    if ((uVar9 & 1) != 0) {
        param_1[2] = param_2;
        sk_memmove(param_1 + 4, param_3, 0x28);
        param_1[3] = 0;
        void (*pcVar11)(unsigned long, unsigned long);
        if (*param_3 == 0) {
            unsigned long lVar10 = sk_percpu_ptr(0);
            pcVar11 = (void (*)(unsigned long, unsigned long))*(unsigned long *)(lVar10 + 0xe0);
            param_2 = param_1[2];
        } else {
            pcVar11 = sk_timer_cb_65_63ac8;
        }
        unsigned char *puVar7 = (unsigned char *)tpidrro_el0;
        *(unsigned long *)puVar7 = (unsigned long)pcVar11;
        CallSupervisor(0);
        if ((param_2 & 0xfd) == 0) {
            unsigned long uVar9b = param_1[6];
            param_1[6] = 0;
            sk_rt_00663d3c((unsigned long)param_1, uVar9b);
            if (_DAT_006b5ed0 == local_48) {
                sk_timer_release_65de3c(param_1);
                return;
            }
        } else {
            sk_rt_0068538c(param_2 & 0xfffffffffffffffd, (unsigned char *)0);
        }
        sk_fatal(0); /* does not return */
    }
    sk_panic_2(0, 0x6a7c2d); /* does not return */
}

/*--------------------------------------------------------------------*/
/* FUN_00663ac8 @ 0x00663ac8
 * Ghidra: void FUN_00663ac8(undefined8 param_1, undefined8 param_2)
 * Timer-callback entry: through the current TCB's timer node (+0xa8) invokes
 * the mounted handler (slot +0x20), sends the result via CallSupervisor(0),
 * tears down the node (FUN_00664588) and runs any release callback, then
 * panics (0x6a7ea9).
 * Confidence: low (callback frame; SoftwareBreakpoint 0x663c04). */
void sk_timer_cb_65_63ac8(unsigned long param_1, unsigned long param_2)
{
    unsigned long lVar10 = sk_cur_tcb_65_61318();
    unsigned long uVar12 = *(unsigned long *)(lVar10 + 0xa8);
    if (uVar12 <= uVar12 + 0x50) {
        sk_rt_00664330(param_1);
        unsigned long uVar11 = (*(unsigned long (**)(unsigned long, unsigned long, unsigned long))(
            uVar12 + 0x20))(*(unsigned long *)(uVar12 + 0x28), param_1, param_2);
        sk_rt_006643b8();
        unsigned char *puVar7 = (unsigned char *)tpidrro_el0;
        *(unsigned long *)puVar7 = uVar11;
        CallSupervisor(0);
        long lVar10b = sk_rt_00664588(uVar12, 1);
        if ((lVar10b != 0) && (*(unsigned long *)(lVar10b + 0x50) != 0)) {
            if (uVar12 + 0x50 <= uVar12) goto overflow;
            (*(void (**)(unsigned long))(lVar10b + 0x50))(uVar12);
        }
        sk_panic_2(0, 0x6a7ea9); /* does not return */
    }
overflow:
    SoftwareBreakpoint(0x5519, 0x663c04); /* does not return */
}

/*--------------------------------------------------------------------*/
/* FUN_0065ebc8 @ 0x0065ebc8
 * Ghidra: undefined8 FUN_0065ebc8(ulong param_1)
 * Reads the per-clock counter table entry param_1: resolves the table base via
 * FUN_0065be08(0x6fe768,1,4), issues a data-memory-barrier, and returns the
 * 8-byte word at base + param_1*8.
 * Confidence: high (thin MMIO/global read) */
unsigned long sk_clock_reg_read_65_ebc8(unsigned long param_1)
{
    long lVar1 = sk_rt_0065be08(0x6fe768, 1, 4);
    DataMemoryBarrier(2, 3);
    return *(unsigned long *)(lVar1 + (param_1 & 0xffffffff) * 8);
}

/*--------------------------------------------------------------------*/
/* FUN_0065eeb0 @ 0x0065eeb0
 * Ghidra: void FUN_0065eeb0(uint param_1)
 * Emits an error frame (code (param_1&0xf)<<12 | 0x11) for the current thread
 * via FUN_0065e5cc.
 * Confidence: high (thin error-frame emit) */
unsigned long sk_err_frame_11_65_eeb0(unsigned int param_1)
{
    unsigned long local_28 = _DAT_006b5ed0;
    unsigned long local_38 = 0, uStack_30 = 0;
    sk_err_frame_65_e5cc(sk_cur_tcb_65_61318(), (unsigned short)((param_1 & 0xf) << 0xc | 0x11),
                   &local_38, 0);
    if (_DAT_006b5ed0 == local_28) {
        return 0;
    }
    sk_fatal(0); /* does not return */
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_0065e5cc @ 0x0065e5cc
 * Ghidra: void FUN_0065e5cc(long param_1, undefined2 param_2, undefined8 *param_3,
 *                          ulong param_4)
 * Error-frame emit: builds a log record from the message words (*param_3 and
 * param_3[1]) plus the code param_2 and thread param_1, calls the format
 * callback FUN_0065ef24 through FUN_0065ea38, and faults via FUN_0067f660 when
 * the result differs from the expected (local_58 or 5).
 * Confidence: low (frame builder; _DAT_006b5ed0 canary check). */
unsigned long sk_err_frame_65_e5cc(unsigned long param_1, unsigned short param_2, unsigned long *param_3,
                          unsigned long param_4)
{
    unsigned long local_28 = _DAT_006b5ed0;
    unsigned short local_6e = 0, local_6c = 0, local_6a = 0;
    unsigned long local_68 = *param_3;
    unsigned long uStack_60 = param_3[1];
    unsigned long local_58 = 0, local_50 = 0;
    unsigned short local_70 = param_2;
    bool bVar1 = false;
    char *pcVar5 = 0;
    unsigned char local_71 = 0;
    if ((param_4 & 1) != 0) {
        unsigned long lVar2 = sk_cur_tcb_65_61318();
        pcVar5 = (char *)&local_71;
        bVar1 = param_1 != lVar2;
        if (!bVar1) {
            pcVar5 = 0;
        }
        local_50 = (unsigned long)bVar1;
        local_71 = '\0';
    }
    unsigned long uVar3 = sk_exec_in_ctx_65ea38((sk_u128_t (*)(unsigned long, unsigned long))sk_msg_send_65ef24, param_1, (unsigned char *)pcVar5,
                                         (unsigned long)&local_70);
    unsigned long uVar4;
    if ((uVar3 & 0xff) == 0) {
        uVar4 = 5;
        if (local_71 == '\0') {
            uVar4 = local_58;
        }
        if (_DAT_006b5ed0 == local_28) {
            return 0;
        }
    } else {
        uVar4 = sk_rt_006848f4(uVar3, (unsigned char *)0);
    }
    sk_fatal(uVar4); /* does not return */
}

/* __END_R49__ */
