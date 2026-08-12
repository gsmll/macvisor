/* Recreated from kernelcache.arm64.kc (xnu-12377.121.10 RELEASE_ARM64_T8142, image base fffffe0007004000). Ground truth: Ghidra FUN_ names + addresses; all names are estimates. */
#include "hv_compat.h"

/*
 * startup.h — boot path prototypes and shared-kernel externs (est.).
 *
 * Owned by the boot-audit tree. Per the BOOT-AUDIT rule the boot path is
 * decompiled with bodies into osfmk/kern/startup.c (kernel_bootstrap,
 * kernel_bootstrap_thread, arm_cpu_init and their direct boot-step callees)
 * and the kernel entry is annotated in osfmk/arm64/start.s.
 *
 * Kernel machinery these boot steps call (scheduler/VM/IOKit internals, the
 * boot-step logging helpers, panic paths, boot-arg/DT getters, allocation)
 * is declared here as shared dependencies with one-line notes and is NOT
 * recreated — that is the audit boundary. Every other FUN_* referenced
 * inside startup.c is likewise a shared kernel dep (kept in comments).
 */

#ifndef _KERN_STARTUP_H_
#define _KERN_STARTUP_H_

/* ---- Boot path functions recreated in startup.c ---- */
extern void kernel_entry_annotated(void);        /* annotated in start.s, not a real symbol */

/* FUN_fffffe000c110000 — kernel entry; see osfmk/arm64/start.s for the
 * annotated early-boot sequence and the transfer into arm_cpu_init. */

/* FUN_fffffe000b95af80 — est. arm_cpu_init. Per-CPU early boot: sets up
 * EL1/EL2 control registers, then calls kernel_bootstrap on the boot CPU. */
void arm_cpu_init(unsigned short *cpu, long *boot_args);

/* FUN_fffffe000b8243f0 — est. kernel_bootstrap. Boot CPU: stores the boot
 * args, runs kernel_bootstrap_thread, then the boot continuation hooks. */
void kernel_bootstrap(unsigned long boot_args);

/* FUN_fffffe000b8239e0 — est. kernel_bootstrap_thread. The first kernel
 * thread; logs and runs every named boot step in order, including
 * hv_support_init (hv_support_init). */
void kernel_bootstrap_thread(void *cpu_thread);

/* Direct boot-step callees of kernel_bootstrap_thread (recreated here). */
void idle_thread_create(void *idle_sched, void *machine_idle);     /* FUN_fffffe000b8187d0 */
void sched_startup(void);                                          /* FUN_fffffe000b818990 */
void thread_daemon_init(void);                                     /* FUN_fffffe000b83d0ac */
void thread_bind(void);                                            /* FUN_fffffe000b81b388 */
void kdp_init(void);                                               /* FUN_fffffe000b776080 */
void pe_init_iokit(void);                                          /* FUN_fffffe000c09e430 */
void dtrace_early_init(void);                                      /* FUN_fffffe000b9da910 */
void code_signing_monitor_lockdown(void);                          /* FUN_fffffe000bdbb37c */
void provisioning_profile_init(void);                              /* FUN_fffffe000bdbaa20 */
void trust_cache_init(void);                                       /* FUN_fffffe000bdb9144 */
unsigned long oskext_remove_kext_bootstrap(void);            /* FUN_fffffe000bf2413c */
void machine_lockdown(void);                                       /* FUN_fffffe000b969374 */
void pe_lockdown_iokit(void);                                      /* FUN_fffffe000bf748bc */

/* hv_support_init — decompiled by the support-init tree in
 * osfmk/arm64/hypervisor/hv_support.c (static there); referenced here by
 * its Ghidra name so startup.c does not own it. Returns 1 when EL2 is
 * active; kernel_bootstrap_thread stores that to DAT_fffffe0007e41db0. */
extern unsigned long hv_support_init(void);

/* ---- Shared kernel dependencies (declared, NOT recreated) ---- */
extern void   kernel_panic_msg_fmt(const char *fmt, ...); /* kernel panic, noreturn */
extern void   kernel_stack_check_panic(void);                 /* kernel stack-check panic, noreturn */
extern void   kernel_panic_b(void);                 /* kernel panic, noreturn */
extern void   kernel_panic(void);                 /* kernel panic, noreturn */
extern int    kernel_boot_arg_get(long base, const char *name, void *val, int size, long flag); /* kernel boot-arg getter */
extern void   kernel_early_log(unsigned long v);      /* kernel early log/timestamp */
extern void   kernel_daemon_init(const char *fmt, ...); /* kernel printf */
extern void   kernel_boot_misc_o(const char *fmt, ...); /* kernel printf (boot) */
extern void   debug_exceptions_disable(int flag);             /* kernel interrupt/exception state restore */
extern void   kernel_spinlock_acquire(void *lock);         /* FUN_fffffe000b7f8738, kernel lock acquire */
extern void   kernel_spinlock_release(void *lock);         /* FUN_fffffe000b7f8a60, kernel lock release */
extern void   lck_mtx_lock(void *lock, ...);      /* kernel lock acquire (spl) */
extern void   lck_mtx_unlock(void *lock, ...);      /* kernel lock release (spl) */
extern void   kernel_boot_continuation(unsigned long x, int f); /* kernel boot continuation hook */
extern void   kernel_preemption_helper(void *fn, unsigned long a, unsigned long b); /* kernel thread/daemon dispatch */
extern unsigned long kernel_feature_flag(void);          /* kernel current-cpu / generation */
extern void   kernel_percpu_op(void *cpu);            /* kernel per-cpu setup */
extern void   kernel_strncpy_chk(void *dst, const char *src, unsigned long n, unsigned long max); /* boot-step name build (strncpy_chk) */
extern void   kernel_boot_step_log(int tag, void *a, unsigned long b, unsigned long c, unsigned long d); /* boot-step log */
extern void   kernel_thread_state_setup(void *thread);         /* kernel thread state setup */
extern void   kernel_early_cpu_init(void);                 /* kernel early-CPU init */

/* ---- Boot-path + hypervisor globals written/read by the boot steps.
 * Ground truth is the Ghidra DAT_ address (kept in the comment); code uses
 * the English name. Hypervisor globals listed here match hv_internal.h's
 * shared naming table; boot-path-only globals are declared here. ---- */
extern uint64_t hv_available_flag;     /* DAT_fffffe0007e41db0 : hv availability (hv_support_init return) */
extern uint64_t hv_build_gate;         /* DAT_fffffe0007e0da68 : EL2 build-path gate (==0 at runtime) */
extern uint64_t hv_soc_feature_index;  /* DAT_fffffe0007e31628 : SoC feature index */
extern uint64_t hv_trace_flag;         /* DAT_fffffe000c68ac90 : trace-enable flag (bit 0) */
extern uintptr_t cred_ops[];            /* DAT_fffffe0007e93310 : credential/sandbox ops table */
extern uint64_t hv_bootarg_table;      /* DAT_fffffe0007e9d440 : boot-arg descriptor table */
extern uint32_t hv_debug_flag;         /* DAT_fffffe000c62b3d0 : pending-sync / lock-storm flag */
extern uint64_t hv_flush_lock;         /* DAT_fffffe000c756760 : flush/state lock */
extern uint64_t boot_stack_marker;     /* DAT_fffffe000c5f0000 : boot stack marker */
extern uint16_t hv_el2_capable;        /* DAT_fffffe0007e0d81e : EL2 feature bit 0 */
extern uint64_t hv_soc_no_l2;          /* DAT_fffffe0007e0d81c : aidr bit 45 (L2-table-absent) */
extern uint64_t hv_soc_bit_index;      /* DAT_fffffe0007e0c6d8 : SoC bit index (panic if >0x3f) */
extern uint64_t hv_soc_actlr_field;    /* DAT_fffffe0007e0c928 : SoC field ORd into ACTLR (est.) */

/* PE / IOKit boot globals. */
extern uint64_t pe_state;              /* DAT_fffffe0007e9d338 : PE state struct base */
extern uint64_t pe_byte_swap_flag;     /* DAT_fffffe0007e9d428 : PE byte-swap flag (bit0) */
extern uint64_t pe_finalize_arg;       /* DAT_fffffe0007e9d438 : PE/iokit finalize arg */
extern uint64_t arm_cpu_init_flag;     /* DAT_fffffe0007e9d461 : arm_cpu_init flag (bit0) */
extern uint64_t iokit_object;          /* DAT_fffffe0007e48808 : IOKit object (finalize/lockdown) */
extern uint64_t iokit_service;         /* DAT_fffffe000c733810 : IOKit service object */
extern uint32_t pe_progress_active;    /* DAT_fffffe000c734018 : PE progress active flag */
extern uint64_t pe_failed_boot_ptr;    /* DAT_fffffe000c734020 : Pict-FailedBoot data ptr */
extern uint64_t pe_progress_config;    /* DAT_fffffe000c5d0110 : PE progress-config record */
extern uint64_t pe_boot_clut_value;    /* DAT_fffffe000c5d0128 : PE boot CLUT value (byte-swapped) */
extern uint32_t pe_progress_dy;        /* DAT_fffffe000c5d012c : PE progress-dy value */
extern uint64_t pe_boot_clut_buffer;   /* DAT_fffffe000c5d0140 : PE boot CLUT copy buffer */
extern uint32_t pe_failed_boot_0;      /* DAT_fffffe000c5d0450 : Pict-FailedBoot record word 0 */
extern uint32_t pe_failed_boot_1;      /* DAT_fffffe000c5d0454 : Pict-FailedBoot record word 1 */
extern uint32_t pe_failed_boot_2;      /* DAT_fffffe000c5d0458 : Pict-FailedBoot record word 2 */
extern uint32_t pe_failed_boot_3;      /* DAT_fffffe000c5d045c : Pict-FailedBoot record word 3 */
extern uint64_t pe_progress_data_a;    /* DAT_fffffe0007043cc8 : progress-config data ptr (est.) */
extern uint64_t pe_progress_data_b;    /* DAT_fffffe000703dcc8 : progress-config data ptr (est.) */
extern uint64_t pe_progress_data_c;    /* DAT_fffffe00070304c8 : progress-config data ptr (est.) */
extern uint32_t pe_lockdown_done;      /* DAT_fffffe000c70c1b0 : PE lockdown done flag */
extern uint64_t kernel_stext_symbol;   /* DAT_fffffe00070e2d2e : kernel stext symbol name string */
extern uint64_t kernel_stext_flag;     /* DAT_fffffe0007e9d300 : kernel stext flag */

/* Scheduler / thread-boot globals. */
extern uint32_t sched_prio_hi;         /* DAT_fffffe000c6ef5c8 : sched priority global (hi) */
extern uint32_t sched_prio_lo;         /* DAT_fffffe000c6ef5c0 : sched priority global (lo) */
extern uint64_t daemon_record_base;    /* DAT_fffffe000c6ef368 : daemon record base */
extern uint64_t ts_daemon_0;           /* DAT_fffffe000c6efb78 : thread-stack daemon record 0 */
extern uint64_t ts_daemon_1;           /* DAT_fffffe000c6efb80 : thread-stack daemon record 1 */
extern uint64_t ts_daemon_2;           /* DAT_fffffe000c6efb88 : thread-stack daemon record 2 */
extern uint64_t ts_daemon_3;           /* DAT_fffffe000c6efb90 : thread-stack daemon record 3 */
extern uint64_t ts_daemon_4;           /* DAT_fffffe000c6efb98 : thread-stack daemon record 4 */
extern uint64_t ts_daemon_5;           /* DAT_fffffe000c6efba0 : thread-stack daemon record 5 */
extern uint64_t ts_daemon_6;           /* DAT_fffffe000c6efba8 : thread-stack daemon record 6 */
extern uint64_t ts_daemon_7;           /* DAT_fffffe000c6efbb0 : thread-stack daemon record 7 */
extern uint64_t ts_daemon_8;           /* DAT_fffffe000c6efbb8 : thread-stack daemon record 8 */
extern uint64_t ts_daemon_9;           /* DAT_fffffe000c6efbc0 : thread-stack daemon record 9 */
extern uint64_t ts_daemon_10;          /* DAT_fffffe000c6efbc8 : thread-stack daemon thread record */
extern uint64_t exc_daemon_0;          /* DAT_fffffe000c6efbf8 : thread-exception daemon record 0 */
extern uint64_t exc_daemon_1;          /* DAT_fffffe000c6efc00 : thread-exception daemon record 1 */
extern uint64_t exc_daemon_2;          /* DAT_fffffe000c6efc08 : thread-exception daemon record 2 */
extern uint64_t exc_daemon_3;          /* DAT_fffffe000c6efc10 : thread-exception daemon record 3 */
extern uint64_t exc_daemon_4;          /* DAT_fffffe000c6efc18 : thread-exception daemon record 4 */
extern uint64_t exc_daemon_5;          /* DAT_fffffe000c6efc20 : thread-exception daemon record 5 */
extern uint64_t daemon_thread_exc;     /* DAT_fffffe000c6efb18 : thread-exception daemon record */
extern uint64_t daemon_thread_bt;      /* DAT_fffffe000c6efb48 : thread-backtrace daemon record */
extern uint64_t bt_daemon_0;           /* DAT_fffffe000c68e3b8 : thread-backtrace daemon record 0 */
extern uint64_t bt_daemon_1;           /* DAT_fffffe000c68e3c0 : thread-backtrace daemon record 1 */
extern uint64_t bt_daemon_2;           /* DAT_fffffe000c68e3c8 : thread-backtrace daemon record 2 */
extern uint64_t bt_daemon_3;           /* DAT_fffffe000c68e3d0 : thread-backtrace daemon record 3 */
extern uint64_t bt_daemon_4;           /* DAT_fffffe000c68e3d8 : thread-backtrace daemon record 4 */
extern uint64_t bt_daemon_5;           /* DAT_fffffe000c68e3e0 : thread-backtrace daemon record 5 */
extern uint8_t  cpu_thread_table;      /* DAT_fffffe000c5ee028 : per-CPU thread table base */
extern uint8_t  cpu_thread_thread;     /* DAT_fffffe000c5ee030 : per-CPU thread table slot */
extern uint8_t  cpu_boot_thread_rec;   /* DAT_fffffe000c5ee038 : per-CPU bootstrap thread record */
extern uint8_t  cpu_thread_id;         /* DAT_fffffe000c5ee070 : per-CPU thread table id slot */
extern uint8_t  cpu_thread_step;       /* DAT_fffffe000c5ee080 : per-CPU thread table step slot */
extern uint8_t  cpu_thread_end;        /* DAT_fffffe000c5ee090 : per-CPU thread table end slot */
extern uint8_t  boot_cpu;              /* DAT_fffffe000c5ee6f0 : boot CPU struct */
extern uint8_t  boot_cpu_thread;       /* DAT_fffffe000c5ee720 : boot CPU thread */
extern uint64_t cpu_start_marker;      /* DAT_fffffe000c5ee800 : CPU start marker (all ones) */
extern uint64_t cached_cpu_lock;       /* DAT_fffffe000c5f4fa0 : cached-CPU lock */
extern uint64_t cached_cpu;            /* DAT_fffffe000c5f4fa8 : cached boot CPU id */
extern uint64_t cpu_generation_0;      /* DAT_fffffe0007d79f98 : per-CPU generation counter 0 */
extern uint64_t cpu_generation_1;      /* DAT_fffffe0007d79fa0 : per-CPU generation counter 1 */
extern uint64_t cpu_generation_2;      /* DAT_fffffe0007d79fa8 : per-CPU generation counter 2 */
extern uint64_t cpu_generation_3;      /* DAT_fffffe0007d7fa48 : per-CPU generation counter 3 */
extern uint64_t cpu_generation_4;      /* DAT_fffffe0007e34a40 : per-CPU generation counter 4 */

/* Machine / timer / lockdown globals. */
extern uint64_t machine_timer_flag;    /* DAT_fffffe000c7169b0 : machine external-timer flag */
extern uint8_t  machine_locked;        /* DAT_fffffe000c7169e1 : machine locked byte */
extern uint64_t machine_lockdown_state;/* DAT_fffffe000c7169e8 : machine lockdown state */
extern uint32_t machine_lockdown_done; /* DAT_fffffe000c62bc78 : machine lockdown done flag */
extern uint64_t boot_time_offset;      /* DAT_fffffe000c62bc70 : boot time offset */
extern uint64_t boot_time_offset_ext;  /* DAT_fffffe000c67ff40 : external-timer boot time offset */
extern uint64_t boot_cpu_preempt_sel;  /* DAT_fffffe000c681990 : boot CPU preempt select flag */
extern uint64_t cpu_boot_time_delta;   /* DAT_fffffe000c5ac010 : per-CPU boot time delta */
extern uint64_t cpu_struct_field_0;    /* DAT_fffffe000c5ac020 : per-CPU struct fill field 0 */
extern uint64_t cpu_struct_field_1;    /* DAT_fffffe000c5ac040 : per-CPU struct fill field 1 */
extern uint64_t cpu_struct_field_2;    /* DAT_fffffe000c5ac028 : per-CPU struct fill field 2 */
extern uint64_t cpu_struct_field_3;    /* DAT_fffffe000c5ac030 : per-CPU struct fill field 3 */
extern uint64_t cpu_struct_field_4;    /* DAT_fffffe000c5ac038 : per-CPU struct fill field 4 */
extern uint8_t  cpu_started;           /* DAT_fffffe000c738008 : per-CPU started array */
extern uint64_t cpu_start_lock;        /* DAT_fffffe000c62ba78 : CPU-start lock */
extern uint64_t boot_timer_block;      /* DAT_fffffe000c738000 : boot timer block (0x670 bytes) */
extern uint32_t boot_timer_on;         /* DAT_fffffe000c738010 : boot timer enabled flag */
extern uint32_t boot_timer_mode;       /* DAT_fffffe000c7387ac : boot timer mode (2=external) */
extern uint64_t cpu_timer_a;           /* DAT_fffffe000c68f208 : cpu timer value a */
extern uint64_t cpu_timer_b;           /* DAT_fffffe000c68f218 : cpu timer value b */
extern uint64_t kernel_clock;          /* DAT_fffffe000c5f4c38 : kernel clock record */
extern uint32_t cpu_slot_count;        /* DAT_fffffe000c5b00c0 : number of per-CPU slots */
extern uint32_t boot_cpu_started;      /* DAT_fffffe000c5b3f90 : boot CPU started flag */
extern uint8_t  keepsyms_flag;         /* DAT_fffffe000c732541 : keepsyms boot-arg flag (bit0) */

/* KDP / panic-log globals. */
extern uint64_t kdp_record_zone;       /* DAT_fffffe0007d52a38 : kalloc zone for KDP crash-state record */
extern uint64_t kdp_serial_zone;       /* DAT_fffffe000c608c40 : KDP serial alloc zone */
extern uint32_t kdp_version_word;      /* DAT_fffffe000c5b002c : KDP version word (byte-swapped) */
extern uint32_t kdp_crashdump_pkt_size;/* DAT_fffffe000c5b0034 : kdp_crashdump_pkt_size value */
extern uint64_t kdp_serial_transport;  /* DAT_fffffe000b77452c : KDP serial transport record */
extern uint64_t kdp_serial_magic;      /* DAT_fffffe000c5d0100 : KDP serial magic handshake */
extern uint32_t kdp_serial_flag;       /* DAT_fffffe000c68ccc0 : KDP serial flag */
extern uint64_t kdp_serial_cb;         /* DAT_fffffe000c68ccc8 : KDP serial callback */
extern uint64_t kdp_serial_list;       /* DAT_fffffe000c68f1a8 : KDP serial transport list head */
extern uint64_t kdp_crash_state;       /* DAT_fffffe000c68d3e0 : KDP crash-state record */
extern uint64_t kernel_version_buf;    /* DAT_fffffe000c5f3c9c : kernel version banner buffer */
extern uint64_t kernel_uuid;           /* DAT_fffffe000c649338 : kernel UUID string */
extern uint64_t panic_base;            /* DAT_fffffe000c68ab80 : panic base */
extern uint64_t panic_log_start;       /* DAT_fffffe000c68ace0 : panic log start */
extern uint64_t panic_log_copy;        /* DAT_fffffe000c68ace8 : panic log copy */
extern uint64_t panic_log_end;         /* DAT_fffffe000c68acf0 : panic log end */
extern uint64_t panic_log_buf;         /* DAT_fffffe000c62be38 : panic log buffer bound */

/* Code-signing / provisioning / trust-cache / MAC globals. */
extern uint64_t cs_feature_init_flag;  /* DAT_fffffe0007e31c50 : code-signing feature init flag */
extern uint64_t cs_feature_bitmap;     /* DAT_fffffe0007e31c58 : code-signing feature bitmap */
extern int (*cs_feature_query)(void *buf);      /* DAT_fffffe0007e31d78 : code-signing feature query fn ptr (est.) */
extern uint64_t coretrust_interface;   /* DAT_fffffe0007e46a60 : coretrust interface present flag */
extern uint64_t image4_interface;      /* DAT_fffffe0007e46a78 : image4 interface present flag */
extern uint64_t amfi_flags_0;          /* DAT_fffffe0007e31788 : AMFI/trust-cache flags word 0 */
extern uint64_t amfi_flags_1;          /* DAT_fffffe0007e31790 : AMFI/trust-cache flags word 1 */
extern uint64_t amfi_flags_2;          /* DAT_fffffe0007e31798 : AMFI/trust-cache flags word 2 */
extern uint64_t profile_feature_flags; /* _DAT_fffffe0007d790f8 : profile feature flags */
extern uint32_t profile_mode_0;        /* DAT_fffffe000c64e448 : profile mode global 0 */
extern uint32_t profile_mode_1;        /* DAT_fffffe000c64e450 : profile mode global 1 */
extern uint32_t profile_mode_2;        /* DAT_fffffe000c64e452 : profile mode global 2 */
extern uint32_t profile_mode_3;        /* DAT_fffffe000c64e454 : profile mode global 3 */
extern uint32_t profile_refcount_lo;   /* DAT_fffffe000c5e1ad0 : profile refcount low word */
extern int32_t  profile_refcount_hi;   /* DAT_fffffe000c5e1ad4 : profile refcount high word */
extern uint32_t profile_generation;    /* DAT_fffffe000c5e1ae4 : profile generation counter */
extern uint32_t mac_policy_initmach_done; /* DAT_fffffe000c68aef0 : mac policy initmach done flag */
extern uint64_t mac_policy_initmach_fn;   /* DAT_fffffe000c68af08 : mac_policy_initmach function ptr */
extern uint32_t dtrace_kernel_symbol_mode;/* DAT_fffffe000c630d90 : dtrace_kernel_symbol_mode value */

/* Kernel alloc / mach-header / vm array globals. */
extern uint64_t kernel_alloc_zone;     /* DAT_fffffe0007d82440 : kernel alloc zone descriptor */
extern uint64_t kernel_alloc_result;   /* DAT_fffffe0007e62dd0 : kernel alloc result handle */
extern uint64_t kernel_mach_header;    /* DAT_fffffe0007e9d280 : MACH_HEADER (fileset kernel) */
extern uint64_t kernel_mod_term_funcs; /* DAT_fffffe000c5ce770 : kernel mod term funcs record */
extern uint64_t kernel_boot_state;     /* DAT_fffffe000c62be78 : kernel boot state handle */
extern uintptr_t per_cpu_kmem_slots;   /* PTR_DAT_fffffe0007d6c6d0 : per-CPU kmem slot table */
extern uintptr_t vm_pages_array;       /* PTR_DAT_fffffe0007d7ffe0 : vm pages array table */


/* ---- raw kernel/boot helpers referenced as calls (identity uncertain;
 * old-style declarations so the tree compiles; NOT recreated) ---- */
#endif /* _KERN_STARTUP_H_ */

/* ---- boot-path kernel helpers referenced as calls (identity uncertain;
 * old-style declarations so the tree compiles; NOT recreated) ---- */
extern int cs_features_enabled();
extern int early_machine_lockdown();
extern int hv_flush_lock_op();
extern int iokit_finalize();
extern int kdp_init_part1();
extern int kdp_magic_init();
extern int kdp_register_transport();
extern int kernel_boot_alloc_init();
extern int kernel_boot_arg_handle();
extern int kernel_boot_finalize_a();
extern int kernel_boot_finalize_b();
extern int kernel_boot_finalize_c();
extern int kernel_boot_finalize_d();
extern int kernel_boot_log();
extern int kernel_boot_misc();
extern int kernel_boot_misc_c();
extern int kernel_boot_misc_d();
extern int kernel_boot_misc_e();
extern int kernel_boot_misc_f();
extern int kernel_boot_misc_g();
extern int kernel_boot_misc_h();
extern int kernel_boot_misc_i();
extern int kernel_boot_misc_j();
extern int kernel_boot_misc_k();
extern int kernel_boot_misc_m();
extern int kernel_boot_misc_n();
extern int kernel_boot_misc_p();
extern int kernel_boot_mp_start();
extern int kernel_boot_policy();
extern int kernel_boot_sync();
extern int kernel_callback_register();
extern int kernel_clock_init();
extern int kernel_cpu_data_setup();
extern int kernel_cpu_feature_setup();
extern int kernel_dt_node_lookup();
extern int kernel_dt_prop_get();
extern int kernel_dt_read();
extern int kernel_flush();
extern int kernel_kalloc();
extern int kernel_load_context_check();
extern int kernel_lockdown_cb();
extern int kernel_mapping_init();
extern int kernel_mp_op_a();
extern int kernel_mp_op_b();
extern int kernel_percpu_bind();
extern int kernel_percpu_finalize();
extern int kernel_percpu_id();
extern int kernel_progress();
extern int kernel_sched_init();
extern int kernel_spl();
extern int kernel_termfuncs();
extern int kernel_thread_state_set();
extern int kernel_tlb_flush();
extern int kernel_trace();
extern int kernel_vm_pages();
extern int machine_idle_continue();
extern int pe_early_init();
extern int pe_iokit_finalize();
extern int pe_trace();
extern int percpu_boot_continuation();
extern int kdp_callback_a();
extern int kdp_callback_b();
extern int kdp_callback_c();
extern int kdp_callback_d();

/* ---- Mach-O artifacts from the kernel image (est., from Ghidra) ---- */
struct segment_command {
    uint32_t cmd;          /* LC_SEGMENT_64 = 0x19 */
    uint32_t cmdsize;
    char     segname[16];
    uint64_t vmaddr;
    uint64_t vmsize;
    uint64_t fileoff;
    uint64_t filesize;
    uint32_t maxprot;
    uint32_t initprot;
    uint32_t nsects;
    uint32_t flags;
};
extern struct segment_command segment_command_fffffe000700c020; /* segment-command table base */
typedef struct segment_command segment_command;   /* allow bare 'segment_command *' in the reconstruction */
extern uint64_t MACH_HEADER;      /* DAT_fffffe0007e9d280 kernel Mach-O header */
extern uint64_t kernel_mach_header; /* est. kernel Mach-O header pointer */
