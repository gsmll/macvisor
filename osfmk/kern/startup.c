/* Recreated from kernelcache.arm64.kc (xnu-12377.121.10 RELEASE_ARM64_T8142, image base fffffe0007004000). Ground truth: Ghidra FUN_ names + addresses; all names are estimates. */
#include "hv_compat.h"

/*
 * startup.c — boot path reconstruction (est.).
 *
 * Owned by the boot-audit tree. Per the BOOT-AUDIT rule this file carries the
 * boot CPU's early boot chain with bodies: kernel_bootstrap
 * (kernel_bootstrap), kernel_bootstrap_thread (kernel_bootstrap_thread),
 * arm_cpu_init (arm_cpu_init) and the direct boot-step callees of
 * kernel_bootstrap_thread (idle_thread_create, sched_startup,
 * thread_daemon_init, thread_bind, kdp_init, PE_init_iokit,
 * dtrace_early_init, code-signing lockdown, provisioning_profile_init,
 * trust_cache_init, OSKextRemoveKextBootstrap, machine_lockdown,
 * PE_lockdown_iokit). hv_support_init (hv_support_init) is owned by the
 * support-init tree and lives in osfmk/arm64/hypervisor/hv_support.c — it is
 * referenced here, not recreated.
 *
 * The kernel entry that reaches arm_cpu_init is annotated in
 * osfmk/arm64/start.s. Kernel machinery the boot steps call (scheduler/VM/
 * IOKit internals) is stubbed as shared dependencies and never decompiled —
 * that is the audit boundary. Every FUN_* / DAT_* below keeps its exact
 * Ghidra name + address in a comment.
 */

#include "startup.h"

/*
 * Boot-step logging helper pair used by kernel_bootstrap_thread:
 *   kernel_strncpy_chk(buf, name, 0x20, 0x20) — bounded copy of the step
 *     name into a 0x20-byte buffer (a strncpy_chk-style helper; panics
 *     "object size check failed" on overflow).
 *   kernel_boot_step_log(0x7020010, buf, 0, 0, 0) — records the boot step
 *     (kernel-thread-start log record @ DAT_fffffe000c750000, tag 0x7020010).
 */

/* ------------------------------------------------------------------ *
 * idle_thread_create @ 0xfffffe000b8187d0   (est. idle_thread_create)
 * Ghidra: void idle_thread_create(long param_1, undefined8 param_2)
 * Creates the per-CPU idle thread with the given machine-idle-thread
 * continuation (param_2), names it "idle #N", and binds it to the boot
 * thread scheduling slot. Runs under a spinlock while disabling debug
 * exceptions in kernel mode (panics if they were already enabled). Releases
 * the thread object reference it created on the way out.
 * Confidence: high
 * Notes: calls kernel_thread_create (kernel_thread_create, kernel dep),
 *   kernel_snprintf (snprintf "idle #%d"), thread_set_name
 *   (thread naming), kernel_spinlock_acquire/0x7f8a60 (spinlock on lVar9+0xa0),
 *   debug_exceptions_disable (restore debug state), LORelease (refcount drop),
 *   thread_deallocate (thread deallocate). Panics:
 *   kernel_panic_msg_fmt("idle_thread_create failed: %d @%s:%d") and
 *   "%s: debug exceptions enabled in kernel mode". Warning:
 *   "Type propagation algorithm not settling". */
void idle_thread_create(void *idle_sched, void *machine_idle)
{
    long  th_info[10];      /* Ghidra local_88 : [0]=thread, [1..]=name buf */
    long  stack_marker;
    int   rc;
    long  th;
    long  cur, prev, prev2;
    unsigned long t;

    stack_marker = boot_stack_marker;   /* boot stack marker global */
    th_info[0] = 0;
    th_info[6] = 0;
    th_info[5] = 0;
    th_info[8] = 0;
    th_info[7] = 0;
    th_info[2] = 0;
    th_info[1] = 0;
    th_info[4] = 0;
    th_info[3] = 0;

    rc = kernel_thread_create(machine_idle, 0, 0x5f, th_info); /* kernel_thread_create, kernel */
    if (rc != 0) {
        kernel_panic_msg_fmt("idle_thread_create failed: %d @%s:%d");
    }
    kernel_snprintf(th_info + 1, 0x40, "idle #%d"); /* snprintf name, kernel */

    th = th_info[0];
    if (th != 0) {
        thread_set_name(th + 0x610, *(void **)(th + 0x510), th_info + 1); /* thread name set, kernel */
    }

    cur = tpidr_el1;
    {
        unsigned long daif_state = daif;   /* DAIF (debug/interrupt mask) */
        if (((daif_state >> 9) & 1) != 0) { /* debug exceptions were masked */
            if ((daif_state & 0x1c0) != 0x1c0) {
                daif = daif | 0x1c0;        /* raise interrupt mask */
            }
            kernel_spinlock_acquire((void *)(th + 0xa0));  /* spinlock acquire, kernel */
            *(long *)(th + 0x298) = (long)idle_sched;
            *(long *)(th + 0x2a8) = (long)idle_sched;
            *(long *)((char *)idle_sched + 0x10) = th;
            *(unsigned int *)(th + 0x214) = 0;
            *(unsigned int *)(th + 0x1f8) = 0x84;
            *(unsigned short *)(th + 0xc0) |= 0x80;
            /* per-CPU current time; compute sched_start timestamp @ +0x270/0x278 */
            prev = *(long *)(*(long *)(cur + 0x1b8) + 0x58);
            do {
                prev2 = prev;
                t = UnkSytemRegRead(3,4,0xf,10,6); /* CNTPCT_EL0 (est.; op1=4 => EL2 view) */
                prev = *(long *)(*(long *)(cur + 0x1b8) + 0x58);
            } while (prev != prev2);
            *(long *)(th_info[0] + 0x278) = t + prev2;
            *(long *)(th_info[0] + 0x270) = t + prev2;
            kernel_spinlock_release((void *)(th_info[0] + 0xa0)); /* spinlock release, kernel */
            debug_exceptions_disable((daif_state & 0x1c0) != 0x1c0); /* restore debug state, kernel */
            /* drop the create reference */
            if (--*(int *)(th + 0x228) == 0) {
                kernel_panic_b();  /* kernel panic, noreturn */
            }
            LORelease();                 /* kernel object release, kernel dep */
            if (*(int *)(th + 0x228) == 1) {
                thread_deallocate(th); /* thread deallocate, kernel */
            }
            if (boot_stack_marker == stack_marker) {
                return;
            }
            kernel_stack_check_panic();      /* stack-check panic, noreturn */
        }
    }
    kernel_panic_msg_fmt("%s: debug exceptions enabled in kernel mode @%s:%d");
}

/* ------------------------------------------------------------------ *
 * sched_startup @ 0xfffffe000b818990   (est. sched_startup)
 * Ghidra: void sched_startup(void)
 * Initializes the scheduler: sets the scheduling-priority globals, creates
 * the scheduler thread running kernel_thread_create_core, releases its create
 * reference, and calls the preemption/unblock helper kernel_preemption_helper.
 * Confidence: high
 * Notes: writes DAT_fffffe000c6ef5c8=0x11 / DAT_fffffe000c6ef5c0=0;
 *   calls kernel_thread_create_variant (kernel_thread_create, kernel) with
 *   continuation kernel_thread_create_core; LORelease + thread_deallocate on
 *   the release path. Panics kernel_panic_msg_fmt("sched_startup @%s:%d")
 *   and kernel_panic_b. */
void sched_startup(void)
{
    int   rc;
    long  th;
    long  th_out;           /* Ghidra local_18 : thread create out-param */

    th_out = 0;
    sched_prio_hi = 0x11;   /* sched priority global */
    sched_prio_lo = 0;
    rc = kernel_thread_create_variant(kernel_thread_create_core, 0, 0x5f, &th_out); /* kernel_thread_create, kernel */
    if (rc != 0) {
        kernel_panic_msg_fmt("sched_startup @%s:%d");
    }
    if (th_out != 0) {
        th = th_out;
        if (--*(int *)(th + 0x228) == 0) {
            kernel_panic_b();  /* kernel panic, noreturn */
        }
        LORelease();                 /* kernel dep */
        if (*(int *)(th + 0x228) == 1) {
            thread_deallocate();  /* thread deallocate, kernel */
        }
    }
    kernel_preemption_helper(0, 0, 0);   /* preemption/unblock helper, kernel */
}

/* ------------------------------------------------------------------ *
 * thread_daemon_init @ 0xfffffe000b83d0ac   (est. thread_daemon_init)
 * Ghidra: void thread_daemon_init(void)
 * Initializes the thread daemons: registers the thread-stack, thread-exception
 * and thread-backtrace daemons (and their per-thread queues) by initializing a
 * set of global daemon records and starting three daemon threads via
 * kernel_daemon_plumbing_a. Panics on any registration failure.
 * Confidence: high
 * Notes: writes DAT_fffffe000c6efb78/0xfb80/... (thread-stack daemon record),
 *   DAT_fffffe000c6efc10/... (thread-exception), DAT_fffffe000c68e3b8/...
 *   (thread-backtrace). Calls kernel_daemon_plumbing_b, kernel_daemon_plumbing_a
 *   (kernel thread_stack_daemon create) with continuations thread_daemon_cont_c,
 *   thread_daemon_cont_b, thread_daemon_cont_a and names
 *   "daemon.thread-stack"/"daemon.thread-exception"/"daemon.thread-backtrace".
 *   Panics "thread_daemon_init: <name> @%s:%d". */
void thread_daemon_init(void)
{
    int rc;

    kernel_daemon_plumbing_b();  /* kernel daemon plumbing init, kernel */
    ts_daemon_0 = 1;
    ts_daemon_1 = (uint64_t)thread_daemon_cont_d;
    ts_daemon_2 = (uint64_t)daemon_record_base;
    ts_daemon_3 = 0;
    ts_daemon_4 = (uint64_t)&ts_daemon_3;
    ts_daemon_5 = 0xffffffffffffffff;
    exc_daemon_3 = 0;
    exc_daemon_0 = 1;
    exc_daemon_1 = 0; /* decompiler label LAB_fffffe000b83d4d8; target not defined in this reconstruction */
    exc_daemon_2 = (uint64_t)daemon_record_base;
    exc_daemon_4 = (uint64_t)&exc_daemon_3;
    exc_daemon_5 = 0xffffffffffffffff;
    bt_daemon_0 = 1;
    bt_daemon_3 = 0;
    bt_daemon_1 = 0; /* decompiler label LAB_fffffe000b78cc0c; target not defined in this reconstruction */
    bt_daemon_2 = (uint64_t)daemon_record_base;
    bt_daemon_4 = (uint64_t)&bt_daemon_3;
    bt_daemon_5 = 0xffffffffffffffff;
    ts_daemon_7 = 0x11;
    ts_daemon_6 = 0;
    ts_daemon_8 = (uint64_t)&ts_daemon_8;
    ts_daemon_9 = (uint64_t)&ts_daemon_8;

    rc = kernel_daemon_plumbing_a(&ts_daemon_10, thread_daemon_cont_c, 0x5d,
                              "daemon.thread-stack", 0); /* kernel thread_stack_daemon, kernel */
    if (rc != 0) {
        kernel_panic_msg_fmt("thread_daemon_init: thread_stack_daemon @%s:%d");
    }
    rc = kernel_daemon_plumbing_a(&daemon_thread_exc, thread_daemon_cont_b, 0x50,
                              "daemon.thread-exception", 0); /* kernel, kernel */
    if (rc == 0) {
        rc = kernel_daemon_plumbing_a(&daemon_thread_bt, thread_daemon_cont_a, 0x50,
                                  "daemon.thread-backtrace", 0); /* kernel, kernel */
        if (rc == 0) {
            return;
        }
        kernel_panic_msg_fmt("thread_daemon_init: thread_backtrace_daemon @%s:%d");
    }
    kernel_panic_msg_fmt("thread_daemon_init: thread_exception_daemon @%s:%d");
}

/* ------------------------------------------------------------------ *
 * thread_bind @ 0xfffffe000b81b388   (est. thread_bind)
 * Ghidra: void thread_bind(void)
 * Binds the boot thread to the current CPU: caches the current CPU number
 * from the per-CPU slot (tpidr_el1+0x518) into DAT_fffffe000c5f4fa8, runs
 * thread_bind_core(0) (the actual bind), and clears the cached CPU when
 * it matches. Guards the cached-CPU update with the DAT_fffffe000c5f4fa0 lock
 * when the thread was previously bound or a cross-cpu flag is set.
 * Confidence: high
 * Notes: reads DAT_fffffe000c5f4fa8 (cached cpu) and DAT_fffffe000c62b3d0
 *   (cross-cpu/thread flag); locks via lck_mtx_lock/0x7f1e80;
 *   calls thread_bind_core (thread_bind core, kernel). */
void thread_bind(void)
{
    long cur;
    unsigned long old_cpu;

    old_cpu = cached_cpu;   /* cached boot cpu */
    cur = tpidr_el1;
    if (cached_cpu == 0) {
        cached_cpu = (unsigned long)*(unsigned int *)(cur + 0x518); /* per-cpu slot */
    }
    if (old_cpu != 0 || hv_debug_flag != 0) {
        lck_mtx_lock(&cached_cpu_lock, cur, old_cpu, 0); /* lock, kernel */
    }
    thread_bind_core(0);  /* thread_bind core, kernel */
    if ((int)cached_cpu == *(int *)(cur + 0x518)) {
        cached_cpu = 0;   /* clear cached cpu */
    }
    if ((int)old_cpu == *(int *)(cur + 0x518) && hv_debug_flag == 0) {
        return;
    }
    lck_mtx_unlock(&cached_cpu_lock, cur);  /* unlock, kernel */
}

/* ------------------------------------------------------------------ *
 * kdp_init @ 0xfffffe000b776080   (est. kdp_init)
 * Ghidra: void kdp_init(void)
 * Initializes the kernel debug protocol (KDP): prints the Darwin kernel
 * version banner into the boot log buffer, sets up panic-log globals, allocates
 * and zeroes the KDP crash-state record, reads the "kdp_crashdump_pkt_size"
 * and "kdp_match_name" boot-args, and if serial KDP is selected registers the
 * serial transport and the panic-handler callback. Panics on the stack-marker
 * mismatch at exit.
 * Confidence: high
 * Notes: version string "Darwin Kernel Version 25.5.0: Tue Jun  9 22:28:17
 *   PDT 2026; root:xnu-12377.121.10~1/RELEASE_ARM64_T8142" @ fffffe0007045595
 *   (via kernel_strlcat_b/0x923d64 strlcat into DAT_fffffe000c5f3c9c);
 *   reads DAT_fffffe000c68ab80/0xace0/0x62be38 (panic base);
 *   DAT_fffffe0007e9d300 (stext flag); alloc hv_zone_alloc
 *   (DAT_fffffe000c68d3e0 KDP record); boot-arg getter kernel_boot_arg_get;
 *   serial KDP path: kernel_kalloc (alloc), kdp_register_transport/
 *   0x774360 (register), kdp_callback_c/0x77658c/0x7763f0/0x7765e8
 *   (KDP callbacks). Strings "Initializing serial KDP\n" etc. via
 *   kernel_boot_misc_o/0x801ce4. Warning: "Removing unreachable block
 *   (ram,0xfffffe000b7761a8)". */
void kdp_init(void)
{
    long  marker = boot_stack_marker;   /* boot stack marker */
    long *rec;
    int   rc;
    uint  tmp;
    char  name[0x50];
    char  ver[0x100];
    long  newrec;
    long  plist[4];

    (void)ver;
    kernel_strlcat_b(&kernel_version_buf,
        "Darwin Kernel Version 25.5.0: Tue Jun  9 22:28:17 PDT 2026; root:xnu-12377.121.10~1/RELEASE_ARM64_T8142",
        0x100);   /* kernel version banner strlcat, kernel */
    if (kernel_uuid != '\0') {   /* kernel UUID global */
        kernel_strlcat_a(&kernel_version_buf, "; UUID=", 0x100);
        kernel_strlcat_a(&kernel_version_buf, &kernel_uuid, 0x100);
    }
    if (panic_base == 0) {      /* panic base */
        kernel_daemon_init("debug_log_init: Error!! gPanicBase is still not initialized\n");
    } else {
        panic_log_start = panic_base + 0xe1;
        panic_log_buf = panic_log_end - 0xe1;
        panic_log_copy = panic_log_start;
    }
    if (kernel_stext_flag != 0) {      /* stext flag: append "; stext=" + symbol */
        kernel_strlcat_a(&kernel_version_buf, "; stext=", 0x100);
        kernel_snprintf(name, 0x13, &kernel_stext_symbol);
        kernel_strlcat_a(&kernel_version_buf, name, 0x100);
    }
    rec = hv_zone_alloc(&kdp_record_zone, 0);  /* kalloc, kernel */
    kdp_crash_state = (uint64_t)rec;
    rec[1] = 0;
    rec[0] = 0;
    rec[3] = 0;
    rec[2] = 0;
    rec[5] = 0;
    rec[4] = 0;
    rec[7] = 0;
    rec[6] = 0;
    rec[9] = 0;
    rec[10] = 0;
    rec[0xb] = (uint64_t)kdp_callback_d;  /* KDP callback, kernel */
    rec[0xc] = 0;
    rec[0xe] = 0;
    rec[0xf] = 0;
    rec[0xd] = 0;
    rec[8] = 0x102010001;
    /* byte-swap DAT_fffffe000c5b002c */
    tmp = (kdp_version_word & 0xff00ff00) >> 8 | (kdp_version_word & 0xff00ff) << 8;
    kdp_version_word = tmp >> 0x10 | tmp << 0x10;
    kdp_crashdump_pkt_size = 0x57e;   /* default kdp_crashdump_pkt_size */
    rc = kernel_boot_arg_get(hv_bootarg_table + 0x6c, "kdp_crashdump_pkt_size",
                              &kdp_crashdump_pkt_size, 4, 0);  /* boot-arg getter, kernel */
    if ((rc != 0) && (0x57e < kdp_crashdump_pkt_size)) {
        kdp_crashdump_pkt_size = 0x57e;
        kernel_daemon_init("kdp_crashdump_pkt_size is too large. Reverting to %u\n");
    }
    kdp_init_part1();  /* kernel KDP init part 1, kernel */

    /* kdp_match_name boot-arg: serial transport selection */
    name[0] = 0;
    rc = kernel_boot_arg_get(hv_bootarg_table + 0x6c, "kdp_match_name", name, 0x50, 0);
    if ((rc == 0) || (rc = kernel_mp_setup(name, "serial", 0x50), rc == 0)) {
        kernel_daemon_init(
            "Serial requested, consistent debug disabled or debug boot arg not present, configuring debugging over serial\n");
        kernel_boot_misc_o("Initializing serial KDP\n");
        newrec = (long)kernel_kalloc(&kdp_serial_zone, 0x20, 7);  /* kalloc, kernel */
        plist[0] = kdp_serial_list;   /* append to serial transport list */
        plist[1] = (long)kdp_callback_c;  /* KDP serial callback, kernel */
        plist[3] = 0;
        *(int *)&plist[2] = 0;
        /* insert newrec at head of DAT_fffffe000c68f1a8 list */
        kdp_serial_list = newrec;
        kdp_serial_flag = 0;
        kdp_serial_cb = (uint64_t)kdp_callback_b;  /* kernel */
        kdp_register_transport(&kdp_serial_transport, kdp_callback_a); /* register transport, kernel */
        /* magic handshake record */
        kdp_magic_init(&kdp_serial_magic, "serial");  /* est. magic @ 0xc5d0100, kernel */
    }
    if (boot_stack_marker == marker) {
        return;
    }
    kernel_stack_check_panic();  /* stack-check panic, noreturn */
}

/* ------------------------------------------------------------------ *
 * pe_init_iokit @ 0xfffffe000c09e430   (est. PE_init_iokit)
 * Ghidra: void pe_init_iokit(void)
 * Early platform-expert (PE) / IOKit init: prints the iBoot version banners,
 * reads the "/chosen/memory-map" device-tree node for the BootCLUT and
 * Pict-FailedBoot properties, handles the "-restore"/"-noprogress" boot args
 * to configure the progress display, and — when debug is enabled and the
 * "/chosen/iBoot" node is present — reads the iBoot timing properties and
 * emits boot-phase trace events. Finalizes the PE and IOKit bootstrap.
 * Confidence: medium
 * Notes: DT lookup kernel_dt_node_lookup, DT property get kernel_dt_prop_get
 *   (BootCLUT/Pict-FailedBoot/start-time/debug-wait-start/load-kernel-start/
 *   populate-registry-time), boot-arg getter kernel_boot_arg_get
 *   ("-restore"/"-noprogress"/"-noprogressonce"); trace kernel_trace
 *   (0x5350000/0x5350004); NEON_rev64(DAT_fffffe000c5d0128) when
 *   DAT_fffffe0007e9d428 bit0; progress kernel_progress, b934dc0;
 *   debug-gate DAT_fffffe000c68ac90; kernel_boot_arg_present (boot-arg present);
 *   pe_iokit_finalize(DAT_fffffe0007e9d438) and iokit_finalize
 *   (DAT_fffffe0007e48808) finalize. iBoot version strings via
 *   kernel_daemon_init("iBoot version: %s\n"). */
void pe_init_iokit(void)
{
    void *mem_map = 0;
    void *val;
    int   size = 0;
    int   rc;
    uint  u;
    uint  a0 = 0, a1 = 0, a2 = 0, a3 = 0;

    pe_early_init();  /* kernel early PE init, kernel */
    kernel_daemon_init("iBoot version: %s\n");
    kernel_daemon_init("iBoot Stage 2 version: %s\n");

    rc = kernel_dt_node_lookup(0, "/chosen/memory-map", &mem_map);  /* DT node, kernel */
    if (rc == 1) {
        val = 0;
        if (kernel_dt_prop_get(mem_map, "BootCLUT", &val, &size) == 1) {
            kernel_early_init(&pe_boot_clut_buffer, *((void **)val), 0x300);  /* memcpy, kernel */
        }
        if (kernel_dt_prop_get(mem_map, "Pict-FailedBoot", &val, &size) == 1) {
            uint *pv = *((uint **)val);
            pe_failed_boot_0 = pv[0];
            pe_failed_boot_1 = pv[1];
            pe_failed_boot_2 = 0;
            pe_failed_boot_3 = pv[2];
            pe_failed_boot_ptr = (uint64_t)(pv + 8);
        }
    }

    if ((pe_byte_swap_flag & 1) != 0) {
        pe_boot_clut_value = NEON_rev64(pe_boot_clut_value, 4);  /* byte-swap */
    }

    u = 0;
    rc = kernel_boot_arg_get(hv_bootarg_table + 0x6c, "-restore", &u, 4, 0);
    rc = kernel_boot_arg_get(hv_bootarg_table + 0x6c, "-noprogress", &u, 4, 0);
    rc = kernel_boot_arg_get(hv_bootarg_table + 0x6c, "-noprogressonce", &u, 4, 0);
    /* (all three absent ⇒ configure the progress display) */
    if ((rc == 0) && (rc == 0) && (rc == 0)) {
        /* progress-dy via FUN_fffffe000c09d30c("progress-dy", &DAT_fffffe000c5d012c, 4) */
        kernel_progress("progress-dy", 0xfffffe000c5d012c, 4);  /* kernel */
        kernel_progress_log(&pe_progress_config, &pe_progress_data_a,
                             &pe_progress_data_b, &pe_progress_data_c,
                             &pe_boot_clut_buffer);  /* kernel progress config */
        pe_progress_active = 1;
    }

    if ((hv_trace_flag != 0) && (rc = kernel_boot_arg_present(0x5350000), rc != 0)) {
        rc = kernel_dt_node_lookup(0, "/chosen/iBoot", &mem_map);  /* DT node, kernel */
        a0 = a1 = a2 = a3 = 0;
        if (rc == 1) {
            val = 0;
            if (kernel_dt_prop_get(mem_map, "start-time", &val, &size) == 1 && size == 4)
                a0 = *((uint *)val);
            if (kernel_dt_prop_get(mem_map, "debug-wait-start", &val, &size) == 1 && size == 4)
                a1 = *((uint *)val);
            if (kernel_dt_prop_get(mem_map, "load-kernel-start", &val, &size) == 1 && size == 4)
                a2 = *((uint *)val);
            if (kernel_dt_prop_get(mem_map, "populate-registry-time", &val, &size) == 1 && size == 4)
                a3 = *((uint *)val);
        }
        if ((hv_trace_flag & 0xfffffff7) != 0) {
            kernel_trace(0x5350000, a0, a1, a2, a3);  /* boot trace, kernel */
            if ((hv_trace_flag & 0xfffffff7) != 0) {
                kernel_trace(0x5350004,
                    *(void **)(pe_state + 0x300),
                    *(void **)(pe_state + 0x308),
                    *(void **)(pe_state + 0x310), 0);
            }
        }
    }
    pe_iokit_finalize(pe_finalize_arg);  /* PE/iokit finalize, kernel */
    iokit_finalize(iokit_object);  /* iokit finalize, kernel */
}

/* ------------------------------------------------------------------ *
 * dtrace_early_init @ 0xfffffe000b9da910   (est. dtrace_early_init)
 * Ghidra: void dtrace_early_init(void)
 * Early DTrace initialization. In this build the body is empty (it returns
 * immediately); the actual DTrace symbol-mode configuration is done inline in
 * kernel_bootstrap_thread via the "dtrace_kernel_symbol_mode" boot-arg read.
 * Confidence: high
 * Notes: empty body; decompiler removed all unreachable blocks
 *   (0xfffffe000b9da940 etc.). The boot-arg handling that precedes this call
 *   lives in kernel_bootstrap_thread. */
void dtrace_early_init(void)
{
    return;
}

/* ------------------------------------------------------------------ *
 * code_signing_monitor_lockdown @ 0xfffffe000bdbb37c   (est. code_signing_monitor_lockdown)
 * Ghidra: void code_signing_monitor_lockdown(void)
 * Locks down code-signing monitoring. If the code-signing feature is
 * initialized, it walks the feature-permission bitmap and clears the enable
 * bits for the monitored features, dropping each via a memory barrier. If a
 * feature was never initialized, it panics instead of silently disabling it.
 * Confidence: high
 * Notes: gate cs_features_enabled (code-signing features enabled?); per-bit
 *   checks at lVar2+0x4f/0x4b/0x4a/0x49 with clear masks 0xfbffffff/0xefffffff/
 *   0xdfffffff/0xbfffffff on DAT_fffffe0007e31c58; init-flag DAT_fffffe0007e31c50;
 *   DataMemoryBarrier(2,3) after each clear; panic "attempted to disable code
 *   signing feature without init: %u @%s:%d" via kernel_panic_msg_fmt. */
void code_signing_monitor_lockdown(void)
{
    int   rc;
    long  cs;
    void *buf[10];

    rc = cs_features_enabled();  /* code-signing features enabled?, kernel */
    if (rc != 0) {
        buf[0] = (void *)0x1000000000005;  /* cs feature query record */
        cs_feature_query(buf); /* code-signing feature query, kernel */
        cs = (long)*cs_feature_query;
        if ((*(unsigned char *)(cs + 0x4f) & 1) == 0) {
            if ((cs_feature_init_flag & 1) == 0) goto _panic;
            cs_feature_bitmap &= 0xfbffffff;  /* clear feature bit */
            DataMemoryBarrier(2,3);
            cs = (long)*cs_feature_query;
        }
        if ((*(unsigned char *)(cs + 0x4b) & 1) == 0) {
            if ((cs_feature_init_flag & 1) == 0) goto _panic;
            cs_feature_bitmap &= 0xefffffff;
            DataMemoryBarrier(2,3);
            cs = (long)*cs_feature_query;
        }
        if ((*(unsigned char *)(cs + 0x4a) & 1) == 0) {
            if ((cs_feature_init_flag & 1) == 0) goto _panic;
            cs_feature_bitmap &= 0xdfffffff;
            DataMemoryBarrier(2,3);
            cs = (long)*cs_feature_query;
        }
        if ((*(unsigned char *)(cs + 0x49) & 1) == 0) {
            if ((cs_feature_init_flag & 1) == 0) goto _panic;
            cs_feature_bitmap &= 0xbfffffff;
            DataMemoryBarrier(2,3);
        }
    }
    return;
_panic:
    kernel_panic_msg_fmt("attempted to disable code signing feature without init: %u @%s:%d");
}

/* ------------------------------------------------------------------ *
 * provisioning_profile_init @ 0xfffffe000bdbaa20   (est. provisioning_profile_init)
 * Ghidra: void provisioning_profile_init(void)
 * Initializes XNU provisioning-profile data: verifies the coretrust interface
 * is present, derives the profile-handling mode/version globals from the
 * DAT_fffffe0007d790f8 feature flags, bumps the profile generation counter,
 * and prints the init banner. Panics if the coretrust interface is absent.
 * Confidence: high
 * Notes: interface check DAT_fffffe0007e46a60; feature flags _DAT_fffffe0007d790f8
 *   bits 0x10000/0x20000 select uVar4 (2 or 0) and uVar3 (0x40 or 0); writes
 *   DAT_fffffe000c64e452/0x448/0x450/0x454 (profile globals) and bumps
 *   DAT_fffffe000c5e1ae4 (generation); refcount DAT_fffffe000c5e1ad0/0x1ad4
 *   with panic kernel_panic_a on overflow; banner via
 *   kernel_daemon_init("initialized XNU provisioning profile data\n").
 *   Warning: "Globals starting with '_' overlap smaller symbols at the same
 *   address". */
void provisioning_profile_init(void)
{
    uint u;
    int  i;
    ushort mode = 2;
    ushort version = 0x40;

    if (coretrust_interface == 0) {   /* coretrust interface */
        kernel_panic_msg_fmt("coretrust interface not available @%s:%d");
    }
    if ((profile_feature_flags & 0x10000) != 0) {
        mode = 0;
    }
    if ((profile_feature_flags & 0x20000) != 0) {
        version = 0;
    }
    profile_mode_2 = mode | version;
    profile_mode_0 = 0x33000000;
    profile_mode_1 = 0;
    profile_mode_3 = 0;
    profile_generation += 1;          /* generation counter */
    if (profile_refcount_hi < 0) {
        i = profile_refcount_lo + 1;
        u = profile_refcount_lo + 0xf0000001;
        profile_refcount_lo = i;
        if (u < 0xf0000002) {
            kernel_panic_a();  /* refcount-overflow panic, noreturn (arg dropped; est.) */
        }
    }
    kernel_daemon_init("initialized XNU provisioning profile data\n");
}

/* ------------------------------------------------------------------ *
 * trust_cache_init @ 0xfffffe000bdb9144   (est. trust_cache_init)
 * Ghidra: void trust_cache_init(void)
 * Initializes the trust cache / AMFI (Apple Mobile File Integrity) interface.
 * Verifies the image4 and AMFI interfaces are present and not stale, queries
 * the trust-cache configuration record and copies the resulting flags/version
 * into the AMFI globals. Panics on a missing or stale interface.
 * Confidence: high
 * Notes: interface checks DAT_fffffe0007e46a78 (image4) and DAT_fffffe0007e93310
 *   (AMFI record, version field at +0x118); query cs_feature_query with
 *   record 0x1000000000003 / size 4; writes DAT_fffffe0007e31788/0x790/0x798.
 *   Panics "image4 interface not available", "amfi interface is stale: %u",
 *   "amfi interface not available" via kernel_panic_msg_fmt. */
void trust_cache_init(void)
{
    void *buf[10];

    if (image4_interface == 0) {   /* image4 interface */
        kernel_panic_msg_fmt("image4 interface not available @%s:%d");
    }
    if (cred_ops != 0) {   /* AMFI record */
        if (1 < *(uint *)(cred_ops + 0x118)) {   /* version */
            buf[0] = (void *)0x1000000000003;
            buf[1] = (void *)4;
            cs_feature_query(buf);  /* code-signing feature query, kernel */
            amfi_flags_0 = (uint64_t)buf[4];
            amfi_flags_1 = (uint64_t)buf[5];
            amfi_flags_2 = (uint64_t)buf[6];
            return;
        }
        kernel_panic_msg_fmt("amfi interface is stale: %u @%s:%d");
    }
    kernel_panic_msg_fmt("amfi interface not available @%s:%d");
}

/* ------------------------------------------------------------------ *
 * oskext_remove_kext_bootstrap @ 0xfffffe000bf2413c   (est. oskext_remove_kext_bootstrap)
 * Ghidra: undefined8 oskext_remove_kext_bootstrap(void)
 * Jettisons the kext bootstrap segments from the kernel mapping after boot:
 * frees/rounds the __HEADER, __SYMTAB, __KLDDATA and (unless symbols are kept)
 * __LINKEDIT segments and runs their terminator functions, so the kext
 * prelink/linkedit memory is reclaimed before the kext subsystem starts.
 * Returns 0.
 * Confidence: high
 * Notes: logs "Jettisoning kext bootstrap segments." via kernel_log;
 *   walks the Mach-O load commands (segment_command_fffffe000700c020 table,
 *   __KLD/__KLDDATA/__LINKEDIT via kernel_mp_setup strcmp); segment
 *   bounds via kernel_segment_bounds (name→addr/size) and kernel_unmap
 *   (unmap); terminator kernel_termfuncs("__mod_term_func"); symtab
 *   kernel_boot_misc_l(&MACH_HEADER,"__PRELINK","__symtab"); fileset-linkedit
 *   handling under boot-arg "keepsyms"; overflow panic kernel_panic_msg_fmt
 *   ("overflow detected @%s:%d"), missing-linkedit panic "FileSet booted with
 *   no Linkedit segment". Warning: "Removing unreachable block
 *   (ram,0xfffffe000bf241b4)". */
unsigned long oskext_remove_kext_bootstrap(void)
{
    segment_command *seg;
    unsigned long    nseg;
    int              rc;
    int              i;
    long             laddr, lsize;
    long             sym;

    kernel_log(0, 0x14, "Jettisoning kext bootstrap segments.");  /* kernel log */
    if ((kernel_mach_header == 0) || (*(int *)(kernel_mach_header + 0xc) != 0xc)) {
        i = 4;   /* not a fileset kernel */
    } else {
        i = 3;   /* fileset kernel */
    }

    rc = kernel_segment_bounds("Kernel-__HEADER", &laddr, &lsize);  /* segment bounds, kernel */
    if ((rc == 0) && (laddr != 0)) {
        if (0xffffc000 < (unsigned long)lsize) goto _overflow;
        kernel_unmap("Kernel-__HEADER", laddr, lsize + 0x3fff & 0xffffc000);  /* unmap, kernel */
    }
    rc = kernel_segment_bounds("Kernel-__SYMTAB", &laddr, &lsize);
    if ((rc == 0) && (laddr != 0)) {
        if (0xffffc000 < (unsigned long)lsize) goto _overflow;
        kernel_unmap("Kernel-__SYMTAB", laddr, lsize + 0x3fff & 0xffffc000);
    }

    /* run __mod_term_func in __KLDDATA, then drop the segment */
    nseg = 0;
    seg = &segment_command_fffffe000700c020;
    do {
        if ((seg->cmd == 0x19) &&
            (rc = kernel_mp_setup(seg->segname, "__KLD", 0x10), rc == 0)) break;
        seg = (segment_command *)(seg->segname + ((unsigned long)seg->cmdsize - 8));
        nseg++;
    } while (nseg < 0x1d);

    nseg = 0;
    seg = &segment_command_fffffe000700c020;
    do {
        if ((seg->cmd == 0x19) &&
            (rc = kernel_mp_setup(seg->segname, "__KLDDATA", 0x10), rc == 0)) {
            kernel_termfuncs(0, &kernel_mod_term_funcs, 0, seg, "__mod_term_func", 0, 0);  /* termfuncs, kernel */
            rc = kernel_segment_bounds("Kernel-__KLDDATA", &laddr, &lsize);
            if (rc == 0) {
                kernel_unmap("Kernel-__KLDDATA", laddr, lsize);
            } else if ((seg->vmaddr != 0) && (seg->vmsize != 0)) {
                kernel_flush();  /* kernel flush, kernel */
            }
            break;
        }
        seg = (segment_command *)(seg->segname + ((unsigned long)seg->cmdsize - 8));
        nseg++;
    } while (nseg < 0x1d);

    /* if a __PRELINK __symtab exists, flush it too */
    if (((i != 3) &&
         (sym = kernel_boot_misc_l(&MACH_HEADER, "__PRELINK", "__symtab"), sym != 0)) &&
        (*(long *)(sym + 0x20) != 0) && (*(long *)(sym + 0x28) != 0)) {
        kernel_flush();  /* kernel flush, kernel */
    }

    /* __LINKEDIT: kept only if "keepsyms" is set, otherwise jettisoned */
    nseg = 0;
    seg = &segment_command_fffffe000700c020;
    do {
        if ((seg->cmd == 0x19) &&
            (rc = kernel_mp_setup(seg->segname, "__LINKEDIT", 0x10), rc == 0)) break;
        seg = (segment_command *)(seg->segname + ((unsigned long)seg->cmdsize - 8));
        nseg++;
    } while (nseg < 0x1d);

    if ((i == 3) || ((keepsyms_flag & 1) != 0)) {
        /* keep symbols (fileset or keepsyms boot arg) */
        kernel_log(0, 0x13, "keepsyms boot arg specified; keeping linkedit segment for symbols.");
    } else {
        rc = kernel_segment_bounds("Kernel-__LINKEDIT", &laddr, &lsize);
        if (rc == 0) {
            kernel_unmap("Kernel-__LINKEDIT", laddr, lsize);
        }
    }
    return 0;

_overflow:
    kernel_panic_msg_fmt("overflow detected @%s:%d");
}

/* ------------------------------------------------------------------ *
 * machine_lockdown @ 0xfffffe000b969374   (est. machine_lockdown)
 * Ghidra: void machine_lockdown(void)
 * Locks down the machine: applies the early-lockdown hook when the SoC
 * debug-disable flag is set, runs the cache/translation and pmap lockdown,
 * marks the machine locked, and flushes the TLB once the preemption count
 * drops to zero. Panics on a negative preemption count.
 * Confidence: high
 * Notes: gated by (**(byte **)(DAT_fffffe0007e9d338+0x318) & 1) → early_machine_lockdown
 *   (early lockdown); calls kernel_boot_misc_c, kernel_boot_finalize_d
 *   (DAT_fffffe000c7169e8,0), kernel_boot_misc, kernel_spl
 *   (spl), kernel_tlb_flush (TLB flush); sets DAT_fffffe000c7169e1=1,
 *   DAT_fffffe000c62bc78=1; preemption count at tpidr_el1+0x1c0; panic
 *   kernel_panic. */
void machine_lockdown(void)
{
    int  i;
    long cur;

    if ((**(unsigned char **)(pe_state + 0x318) & 1) != 0) {
        early_machine_lockdown();  /* early machine lockdown, kernel */
    }
    kernel_boot_misc_c();                              /* kernel */
    kernel_boot_finalize_d(machine_lockdown_state, 0);        /* kernel */
    machine_locked = 1;                            /* machine locked */
    kernel_boot_misc();                              /* kernel */
    cur = tpidr_el1;
    *(int *)(cur + 0x1c0) += 1;                          /* preemption count */
    kernel_spl();                              /* spl, kernel */
    if (*(int *)(cur + 0x1c0) != 0) {
        i = *(int *)(cur + 0x1c0) - 1;
        *(int *)(cur + 0x1c0) = i;
        if ((i == 0) && ((*(unsigned char *)(*(long *)(cur + 0x1b8) + 0x4c) >> 2 & 1) != 0)) {
            kernel_tlb_flush();  /* TLB flush, kernel */
        }
        machine_lockdown_done = 1;
        return;
    }
    kernel_panic();  /* kernel panic, noreturn */
}

/* ------------------------------------------------------------------ *
 * pe_lockdown_iokit @ 0xfffffe000bf748bc   (est. pe_lockdown_iokit)
 * Ghidra: void pe_lockdown_iokit(void)
 * Locks down IOKit after PE lockdown: emits the platform-expert lockdown
 * trace event, reads the IOKit state and, when nonzero, drives the
 * IOService-matching finalization through the IOKit vtable. Panics if the
 * IOService match cannot be started.
 * Confidence: medium
 * Notes: trace pe_trace(0x61f0004,0,0,0,0); reads DAT_fffffe0007e48808
 *   (IOKit object) and calls *(*(plVar1)+0x5e0)(plVar1,0) and
 *   (*(DAT_fffffe000c733810 + 0x660))(DAT_fffffe000c733810,1,...) via
 *   kernel_boot_misc_m; panic "Failed to start IOService matching @%s:%d"
 *   via kernel_panic_msg_fmt. Warning: "Could not recover jumptable at
 *   0xfffffe000bf74968. Too many branches" / "Treating indirect jump as call". */
void pe_lockdown_iokit(void)
{
    long *io;
    long  v;

    pe_trace(0x61f0004, 0, 0, 0, 0);  /* PE trace, kernel */
    io = (long *)iokit_object;
    v = (long)kernel_boot_misc_m();  /* kernel */
    io[0x11] = v;
    if (v != 0) {
        (*(void (**)(void *, int))(*(void **)io + 0x5e0))(io, 0);           /* IOKit vtable call, kernel */
        (*(void (**)(void *, int, void *))(*(void **)(uint64_t)iokit_service + 0x660))
            ((void *)iokit_service, 1, *(void **)(uint64_t)iokit_service + 0x660); /* IOService match, kernel */
        return;
    }
    kernel_panic_msg_fmt("Failed to start IOService matching @%s:%d");
}

/* ------------------------------------------------------------------ *
 * kernel_bootstrap_thread @ 0xfffffe000b8239e0   (est. kernel_bootstrap_thread)
 * Ghidra: void kernel_bootstrap_thread(long param_1)
 * The first kernel thread (est. kernel_bootstrap_thread). Called with the
 * boot thread object; it asserts the thread's load-context state, registers
 * the thread in the per-CPU thread table, then runs every named boot step in
 * order, logging each via the kernel-thread-start pattern
 * (kernel_strncpy_chk name-build + kernel_boot_step_log log). The hv-relevant
 * step is "hv_support_init": it calls hv_support_init (est.
 * hv_support_init) and stores the return to DAT_fffffe0007e41db0 (the hv
 * availability flag consumed by the mach-trap dispatcher). Each step's init
 * function is a direct boot-step callee recreated in this file where it is a
 * boot init function; the rest are shared kernel deps.
 * Confidence: high
 * Notes: reads tpidr_el1 and the per-CPU base at *(lVar6+0x1b0); asserts via
 *   kernel_load_context_check + panic kernel_panic_msg_fmt("load_context @%s:%d");
 *   per-CPU thread table at DAT_fffffe000c5ee028 + (per_cpu>>0x10) with
 *   DAT_fffffe000c5ee030/0x70/0x80/0x90; boot-step logging through
 *   kernel_boot_step_log(0x7020010,...) into DAT_fffffe000c750000; boot step
 *   order/addresses: idle_thread_create=b8187d0, sched_startup=b818990,
 *   thread_daemon_init=b83d0ac, thread_bind=b81b388, kdp_init=b776080,
 *   hv_support_init=b984d4c, PE_init_iokit=c09e430, mac_policy_initmach
 *   (indirect via DAT_fffffe000c68af08), dtrace_early_init=b9da910,
 *   code-signing lockdown=bdbb37c, provisioning_profile_init=bdbaa20,
 *   trust_cache_init=bdb9144, OSKextRemoveKextBootstrap=bf2413c,
 *   machine_lockdown=b969374, PE_lockdown_iokit=bf748bc. Warn: many
 *   "Removing unreachable block" (loop/panic paths). */
void kernel_bootstrap_thread(void *param_1)
{
    unsigned long per_cpu;
    unsigned char *tbl;
    unsigned long gen;
    long  marker;
    char  step[0x20];
    int   i, cnt;
    void **ppu;

    per_cpu = tpidr_el1;
    per_cpu = *(long *)(per_cpu + 0x1b0);   /* per-cpu base */
    kernel_early_cpu_init();                 /* kernel early-CPU init */

    /* load-context assertion */
    if ((*(long *)(param_1 + 0xe8) == 0) &&
        (i = kernel_load_context_check(param_1), i == 0)) {   /* kernel load-context check */
        kernel_panic_msg_fmt("load_context @%s:%d");
    }
    if (-1 < *(char *)(param_1 + 0x1f8)) {
        kernel_cpu_data_setup(param_1);      /* kernel */
    }

    /* register this thread in the per-CPU thread table */
    tbl = &cpu_thread_table + (per_cpu >> 0x10);
    kernel_percpu_bind_cpu(tbl, param_1, 0, param_1 != *(void **)(&cpu_thread_thread + (per_cpu >> 0x10)));
    *(void **)(&cpu_thread_thread + (per_cpu >> 0x10)) = param_1;
    *(int *)(&cpu_thread_id + (per_cpu >> 0x10)) = (int)*(short *)(param_1 + 0x214);
    *(void **)(&cpu_thread_end + (per_cpu >> 0x10)) = (void *)0xffffffffffffffff;
    *(void **)(param_1 + 0x2a0) = (void *)tbl;
    kernel_percpu_bind(tbl);              /* kernel */
    kernel_thread_state_get(step);
    *(void **)(&cpu_thread_step + (per_cpu >> 0x10)) = step;
    kernel_thread_state_set(tbl, step);        /* kernel */
    kernel_percpu_finalize(tbl);              /* kernel */
    kernel_thread_state_setup(param_1);          /* kernel thread state setup */

    marker = boot_stack_marker;          /* boot stack marker */

    /* ---- boot steps (each logged via kernel-thread-start pattern) ---- */

    /* idle_thread_create */
    kernel_strncpy_chk(step, "idle_thread_create", 0x20, 0x20);
    kernel_boot_step_log(0x7020010, step, 0, 0, 0);
    idle_thread_create(&cpu_thread_table + (per_cpu >> 0x10), machine_idle_continue); /* idle_thread_create */

    /* sched_startup */
    kernel_strncpy_chk(step, "sched_startup", 0x20, 0x20);
    kernel_boot_step_log(0x7020010, step, 0, 0, 0);
    sched_startup();                 /* sched_startup */

    /* thread_daemon_init */
    kernel_strncpy_chk(step, "thread_daemon_init", 0x20, 0x20);
    kernel_boot_step_log(0x7020010, step, 0, 0, 0);
    thread_daemon_init();                 /* thread_daemon_init */
    kernel_early_log(0xf);              /* kernel early log */

    /* thread_bind */
    kernel_strncpy_chk(step, "thread_bind", 0x20, 0x20);
    kernel_boot_step_log(0x7020010, step, 0, 0, 0);
    thread_bind();                 /* thread_bind */
    kernel_percpu_op(&cpu_thread_table + (per_cpu >> 0x10)); /* kernel per-cpu */

    /* mapping_adjust — logged step; the map adjustment is inlined in this
     * binary's path (no distinct direct call between its log and the next). */
    kernel_strncpy_chk(step, "mapping_adjust", 0x20, 0x20);
    kernel_boot_step_log(0x7020010, step, 0, 0, 0);

    /* clock_service_create — logged step; clock service init work is done by
     * the per-cpu kmem + clock globals block below (no distinct direct call). */
    kernel_strncpy_chk(step, "clock_service_create", 0x20, 0x20);
    kernel_boot_step_log(0x7020010, step, 0, 0, 0);
    if (0 < cpu_slot_count) {          /* number of per-cpu slots */
        cnt = cpu_slot_count;
        ppu = &per_cpu_kmem_slots;
        i = 0;
        do {
            if (*ppu != 0) {
                ppu[1] = (void *)kernel_zone_alloc(ppu, 0x11a, 0, 0);   /* per-cpu kmem, kernel */
                cnt = cpu_slot_count;
            }
            i++;
            ppu += 2;
        } while (i < cnt);
    }
    kernel_alloc_result = kernel_zone_alloc(&kernel_alloc_zone, 0x125, 0, 0);  /* kernel alloc */
    gen = kernel_zone_meta(kernel_alloc_result, &kernel_alloc_zone, 0x25);     /* kernel */
    kernel_clock_init(&kernel_clock, 3, gen);            /* kernel clock */
    kernel_sched_init();                 /* kernel */

    /* kdp_init */
    kernel_strncpy_chk(step, "kdp_init", 0x20, 0x20);
    kernel_boot_step_log(0x7020010, step, 0, 0, 0);
    kdp_init();                 /* kdp_init */

    /* hv_support_init */
    kernel_strncpy_chk(step, "hv_support_init", 0x20, 0x20);
    kernel_boot_step_log(0x7020010, step, 0, 0, 0);
    hv_available_flag = hv_support_init();  /* est. hv_support_init → hv availability flag */
    kernel_early_log(0x10);             /* kernel early log */

    /* per-CPU generation counters (current-cpu from FUN_fffffe000b93c6c8) */
    gen = kernel_feature_flag();
    cpu_generation_0 = gen | 1;
    gen = kernel_feature_flag();
    cpu_generation_1 = gen | 1;
    gen = kernel_feature_flag();
    cpu_generation_2 = gen | 1;
    cpu_generation_4 = kernel_feature_flag();
    cpu_generation_3 = kernel_feature_flag();

    /* PE_init_iokit */
    kernel_strncpy_chk(step, "PE_init_iokit", 0x20, 0x20);
    kernel_boot_step_log(0x7020010, step, 0, 0, 0);
    pe_init_iokit();                 /* PE_init_iokit */
    kernel_early_log(0x12);
    debug_exceptions_disable(1);                /* kernel interrupt restore */
    kernel_boot_mp_start(0, 4);             /* kernel */
    kernel_mp_op_b();                 /* kernel */
    kernel_mp_op_a();                 /* kernel */

    /* mac_policy_initmach */
    kernel_strncpy_chk(step, "mac_policy_initmach", 0x20, 0x20);
    kernel_boot_step_log(0x7020010, step, 0, 0, 0);
    if (mac_policy_initmach_fn != (void *)0) {   /* function pointer, kernel MAC policy */
        (*(void (**)(void))mac_policy_initmach_fn)();  /* indirect: est. mac_policy_initmach */
    }
    mac_policy_initmach_done = 1;               /* mac policy initmach done */

    /* dtrace_early_init */
    kernel_strncpy_chk(step, "dtrace_early_init", 0x20, 0x20);
    kernel_boot_step_log(0x7020010, step, 0, 0, 0);
    i = kernel_boot_arg_get(hv_bootarg_table + 0x6c, "dtrace_kernel_symbol_mode",
                             &dtrace_kernel_symbol_mode, 4, 0);   /* boot-arg getter, kernel */
    if (i == 0) {
        dtrace_kernel_symbol_mode = 2;           /* default dtrace_kernel_symbol_mode */
    }
    dtrace_early_init();                 /* dtrace_early_init */
    kernel_callback_register(kernel_lockdown_cb, 0);  /* kernel */

    /* code-signing-monitor lockdown mode */
    kernel_strncpy_chk(step, "code-signing-monitor lockdown mode", 0x20, 0x20);
    kernel_boot_step_log(0x7020010, step, 0, 0, 0);
    code_signing_monitor_lockdown();                 /* code_signing_monitor_lockdown */

    /* provisioning_profile_init */
    kernel_strncpy_chk(step, "provisioning_profile_init", 0x20, 0x20);
    kernel_boot_step_log(0x7020010, step, 0, 0, 0);
    provisioning_profile_init();                 /* provisioning_profile_init */

    /* trust_cache_init */
    kernel_strncpy_chk(step, "trust_cache_init", 0x20, 0x20);
    kernel_boot_step_log(0x7020010, step, 0, 0, 0);
    trust_cache_init();                 /* trust_cache_init */
    kernel_boot_misc_j();                 /* kernel */
    kernel_early_log(0xffffffff);       /* kernel early log */

    /* OSKextRemoveKextBootstrap */
    kernel_strncpy_chk(step, "OSKextRemoveKextBootstrap", 0x20, 0x20);
    kernel_boot_step_log(0x7020010, step, 0, 0, 0);
    oskext_remove_kext_bootstrap();                 /* oskext_remove_kext_bootstrap */
    kernel_boot_misc_k();                 /* kernel */

    /* machine_lockdown */
    kernel_strncpy_chk(step, "machine_lockdown", 0x20, 0x20);
    kernel_boot_step_log(0x7020010, step, 0, 0, 0);
    machine_lockdown();                 /* machine_lockdown */

    /* PE_lockdown_iokit */
    kernel_strncpy_chk(step, "PE_lockdown_iokit", 0x20, 0x20);
    kernel_boot_step_log(0x7020010, step, 0, 0, 0);
    pe_lockdown_done = 1;               /* PE lockdown done */
    pe_lockdown_iokit();                 /* pe_lockdown_iokit */

    /* ---- remaining boot continuation ---- */
    kernel_boot_finalize_a(kernel_boot_state);  /* kernel */
    kernel_boot_sync();                 /* kernel */
    kernel_boot_misc_h();                 /* kernel */
    kernel_boot_alloc_init();                 /* kernel */
    kernel_boot_finalize_c(kernel_boot_state);  /* kernel */
    kernel_percpu_op(0);                /* kernel */
    kernel_mapping_init();                 /* kernel */
    kernel_vm_pages("vm pages array", 0x30, 0xc000000000000000, 0x14, &vm_pages_array); /* kernel VM */

    if (boot_stack_marker != marker) {
        kernel_stack_check_panic();             /* stack-check panic, noreturn */
    }
    kernel_boot_finalize_b();                 /* kernel */
}

/* ------------------------------------------------------------------ *
 * kernel_bootstrap @ 0xfffffe000b8243f0   (est. kernel_bootstrap)
 * Ghidra: void kernel_bootstrap(undefined8 param_1)
 * Boot-CPU kernel bootstrap. Stores the boot arguments into the per-CPU
 * bootstrap thread record, runs kernel_bootstrap_thread
 * (kernel_bootstrap_thread) on it, then runs the boot continuation hooks
 * kernel_boot_continuation(thread,1) and kernel_preemption_helper(idle_main,0,0).
 * Called from arm_cpu_init with 0 on the boot CPU.
 * Confidence: high
 * Notes: reads tpidr_el1 and the per-CPU thread record at
 *   DAT_fffffe000c5ee038 + (*(lVar2+0x1b0)>>0x10); writes boot args to
 *   record+0xe0; kernel_boot_continuation and kernel_preemption_helper are kernel
 *   boot-continuation hooks (shared deps). */
void kernel_bootstrap(unsigned long param_1)
{
    long  cur, rec;
    unsigned long ret;

    cur = tpidr_el1;
    rec = *(long *)(&cpu_boot_thread_rec + (*(long *)(cur + 0x1b0) >> 0x10));
    *(void **)(rec + 0xe0) = (void *)param_1;   /* store boot args */
    kernel_bootstrap_thread((void *)rec);            /* kernel_bootstrap_thread */
    kernel_boot_continuation(ret, 1);               /* kernel boot continuation hook */
    kernel_preemption_helper(machine_idle_continue, 0, 0);  /* kernel (idle main dispatch) */
}

/* ------------------------------------------------------------------ *
 * arm_cpu_init @ 0xfffffe000b95af80   (est. arm_cpu_init)
 * Ghidra: void arm_cpu_init(undefined2 *param_1, long *param_2)
 * Per-CPU early boot. Selects the EL2/EL1 control state (panics if an
 * unexpected preemption count is seen on the boot CPU), programs CPACR_EL1 /
 * CNTKCTL_EL1 and the counter-timer, invalidates the EL1 TLB, installs the
 * per-CPU boot continuation (cpu->+0xb8 = percpu_boot_continuation), sets up the
 * cpu struct and, on the boot CPU (param_1 == &DAT_fffffe000c5ee6f0), configures
 * the boot CPU's time/timer and prints "arm_cpu_init(): cpu %d online\n"
 * before calling kernel_bootstrap (kernel_bootstrap, with 0). On
 * secondary CPUs it returns to the caller without calling kernel_bootstrap.
 * Confidence: high
 * Notes: EL2 sysreg writes UnkSytemRegWrite(3,1,0xf,1,5,0) [SPSR_EL1],
 *   (3,4,0xf,0xe,6,3) [CNTHCTL_EL2?], (3,4,0xf,1,4,0x100), (3,4,1,2,5,0),
 *   (3,4,0xf,10,4,0), (3,0,1,2,6,0x4000000f), (3,0,1,2,4,0), (3,3,0xd,0,5,0)
 *   [DAIF masking], reads actlr_el1, cpacr_el1, cntkctl_el1, mpidr_el1,
 *   UnkSytemRegRead(3,0,1,0,6)/(3,4,0xf,9,6)/(3,4,0xf,10,6)/(3,5,0xf,1,6);
 *   boot-time DT property via kernel_dt_read + kernel_early_init;
 *   DAT_fffffe0007e31628 (SoC feature index, <5 gates the mpidr path),
 *   DAT_fffffe0007e0c928, DAT_fffffe0007e0da68 (el2 feature gate),
 *   DAT_fffffe0007e0c6d8 (bit index, panics if >0x3f), DAT_fffffe000c5b00c0.
 *   Panics: kernel_panic_msg_fmt("unexpected preemption count %u on boot cpu
 *   thread (should be %u) @%s:%d") and "%s: invalid bit index (%u) @%s:%d".
 *   Warning: "Globals starting with '_' overlap smaller symbols". */
void arm_cpu_init(unsigned short *param_1, long *param_2)
{
    unsigned short *cpu;
    long  cur, boot_arg, tval, t;
    int   i;

    if (((param_2 != 0) && (*param_2 != 0)) && ((int)param_2[1] != 0)) {
        kernel_boot_arg_handle((long)param_2 + 0xc);   /* kernel boot-arg handling */
    }
    /* early boot state */
    pan = 1;                                     /* est. global 'pan' (permission access-neutral) */
    UnkSytemRegWrite(3,1,0xf,1,5,0);             /* SPSR_EL1 = 0 (est.; op1=1 => EL1) */
    UnkSytemRegWrite(3,4,0xf,0xe,6,3);           /* op1=4 => EL2 view */
    InstructionSynchronizationBarrier();
    if (hv_soc_feature_index < 5) {              /* SoC feature index */
        t = mpidr_el1;
        kernel_percpu_id(t & 0xff);          /* kernel per-cpu id */
    }
    UnkSytemRegWrite(3,4,0xf,1,4,0x100);         /* op1=4 => EL2 */
    InstructionSynchronizationBarrier();
    t = actlr_el1;
    kernel_cpu_feature_setup(t & 0xfffffffffffff1ff | (unsigned long)hv_soc_actlr_field << 0xd); /* kernel */
    if (hv_build_gate != 0) {             /* el2 feature gate */
        t = cpacr_el1;
        cpacr_el1 = t & 0xfffffffffcffffff | 0x1000000;   /* enable CPACR bit */
        InstructionSynchronizationBarrier();
        UnkSytemRegWrite(3,0,1,2,6,0x4000000f);  /* CNTKCTL_EL1 (est.) */
        UnkSytemRegWrite(3,0,1,2,4,0);
        UnkSytemRegWrite(3,4,1,2,5,0);           /* op1=4 => EL2 */
        UnkSytemRegWrite(3,3,0xd,0,5,0);         /* DAIF mask */
    }
    cpu = param_1 + 1;
    *cpu &= 0xf7ff;                              /* clear a cpu flag bit */
    UnkSytemRegWrite(3,4,0xf,10,4,0);            /* op1=4 => EL2 */
    kernel_early_cpu_init();                      /* kernel early-CPU init */

    t = UnkSytemRegRead(3,0,1,0,6);              /* CNTFRQ_EL0 (est.) */
    UnkSytemRegWrite(3,0,1,0,6, t | 0x10000);    /* set timer freq bit */
    cur = tpidr_el1;
    UnkSytemRegWrite(3,0,1,0,5, (uint64_t)*(void **)(*(long *)(cur + 0x1b8) + 0xa40)); /* CNTP_TVAL? est. */

    if ((param_2 != 0) && (*param_2 != 0)) {
        boot_timer_mode = 2;
        boot_timer_on = 1;
        tco = 1;                                 /* est. global 'tco' (time compare override) */
        boot_arg = 0;
        kernel_dt_read(*param_2, &boot_arg);   /* kernel DT read */
        kernel_early_init(&boot_timer_block, boot_arg, 0x670);  /* kernel memcpy */
        tco = 0;
    }

    if ((param_1 == &boot_cpu) && (boot_timer_mode == 2) &&
        (DataMemoryBarrier(2,1), machine_timer_flag != 0)) {
        /* boot CPU with external timer: remember the boot time offset */
        boot_time_offset_ext = *(long *)(&boot_timer_block + 0xd0);
        boot_time_offset = *(long *)(&boot_timer_block + 0xd8);
        i = 1;
        if (boot_cpu_preempt_sel != 0) {
            i = 2;
        }
        if (*(int *)(&boot_cpu_thread + 0x1c0) != i) {
            kernel_panic_msg_fmt("unexpected preemption count %u on boot cpu thread (should be %u) @%s:%d");
        }
        *(int *)(&boot_cpu_thread + 0x1c0) = i - 1;
    }

    if (0x3f < hv_soc_bit_index) {
        kernel_panic_msg_fmt("%s: invalid bit index (%u) @%s:%d");
    }
    t = UnkSytemRegRead(3,4,0xf,9,6);            /* op1=4 => EL2 */
    UnkSytemRegWrite(3,4,0xf,9,6, t | (unsigned long)hv_soc_bit_index << 4 | 0xf);
    t = cntkctl_el1;
    cntkctl_el1 = t | 3;                         /* enable CNTKCTL bits */
    TLBI_VMALLE1IS();                            /* invalidate EL1 TLB */
    DataSynchronizationBarrier(2,3,0);
    InstructionSynchronizationBarrier();

    *(void **)(*(long *)(cur + 0x1b8) + 0xb8) = percpu_boot_continuation;  /* per-CPU boot continuation */
    DataSynchronizationBarrier(3,3,0);
    kernel_boot_misc_d();                      /* kernel */

    /* fill the per-CPU cpu struct */
    if (*(long *)(*(void **)(cur + 0x1b8) + 0x44) == 0) {
        *(void **)(*(void **)(cur + 0x1b8) + 0x44) = (void *)cpu_struct_field_0;
        *(void **)(*(void **)(cur + 0x1b8) + 0x40) = (void *)cpu_struct_field_3;
        *(void **)(*(void **)(cur + 0x1b8) + 0x3c) = (void *)cpu_struct_field_2;
        *(void **)(*(void **)(cur + 0x1b8) + 0x4c) = *(void **)&cpu_struct_field_1;
        *(void **)(*(void **)(cur + 0x1b8) + 0x48) = (void *)cpu_struct_field_4;
    }
    if ((*(void **)(cur + 0x1b8) == &boot_cpu) &&
        (DataMemoryBarrier(2,1), machine_timer_flag != 0)) {
        t = UnkSytemRegRead(3,4,0xf,10,6);       /* op1=4 => EL2 */
        cpu_boot_time_delta = boot_time_offset_ext - t;
    }
    *(unsigned int *)(*(void **)(cur + 0x1b8) + 0x38) = 0x7fffffff;
    *(long *)(*(void **)(cur + 0x1b8) + 0x2c) = cpu_boot_time_delta;
    *(void **)(*(void **)(cur + 0x1b8) + 0x30) = 0;
    kernel_boot_log();                      /* kernel */

    if (param_1 == &boot_cpu) {
        /* ---- boot CPU ---- */
        DataMemoryBarrier(2,1);
        if (machine_timer_flag != 0) {
            boot_cpu_started = 1;
            kernel_boot_misc_p();              /* kernel */
            kernel_boot_misc_n(1, 0);          /* kernel */
            kernel_boot_misc_f();              /* kernel */
            if (cpu_timer_a != cpu_boot_time_delta) {
                cpu_timer_a = cpu_boot_time_delta;
            }
            if ((boot_timer_mode == 2) && (cpu_timer_b != boot_time_offset)) {
                cpu_timer_b = boot_time_offset;
            }
        }
        if ((arm_cpu_init_flag & 1) != 0) {
            t = UnkSytemRegRead(3,5,0xf,1,6);
            UnkSytemRegWrite(3,5,0xf,1,6, t | 0x1c000000);
        }
        UnkSytemRegWrite(3,1,0xf,0,5,1);         /* SCTLR_EL1? est. */
        cntp_ctl_el0 = 2;
        UnkSytemRegWrite(3,1,0xf,0xd,4,2);       /* CNTP_CTL? est. */
        cpu_start_marker = 0xffffffffffffffff;
        kernel_boot_misc_e();                  /* kernel */
        kernel_boot_misc_o("arm_cpu_init(): cpu %d online\n");
        DataMemoryBarrier(2,1);
        if (machine_timer_flag != 0) {
            if (hv_trace_flag == 0) {
                kernel_boot_misc_i();          /* kernel */
            }
            kernel_boot_policy();              /* kernel */
        }
    } else {
        /* ---- secondary CPU ---- */
        if ((arm_cpu_init_flag & 1) != 0) {
            t = UnkSytemRegRead(3,5,0xf,1,6);
            UnkSytemRegWrite(3,5,0xf,1,6, t | 0x1c000000);
        }
        UnkSytemRegWrite(3,1,0xf,0,5,1);
        cntp_ctl_el0 = 2;
        UnkSytemRegWrite(3,1,0xf,0xd,4,2);
        *(void **)(param_1 + 0x88) = (void *)0xffffffffffffffff;
        kernel_boot_misc_e();                  /* kernel */
        kernel_boot_misc_o("arm_cpu_init(): cpu %d online\n");
    }

    kernel_boot_misc_g();                      /* kernel */

    /* mark this cpu started in DAT_fffffe000c738008 */
    i = *(unsigned int *)(param_1 + 0xf8) * 4;
    if (*(int *)(&cpu_started + i) != 2) {
        kernel_spinlock_acquire(&cpu_start_lock);  /* lock, kernel */
        *(unsigned int *)(&cpu_started + (unsigned int)(*(unsigned int *)(param_1 + 0xf8)) * 4) = 2;
        hv_flush_lock_op(&hv_flush_lock, (uint64_t)(&cpu_started +
                             (unsigned long)*(unsigned int *)(param_1 + 0xf8) * 4), 0, 0, 0xffffffff); /* kernel */
        kernel_spinlock_release(&cpu_start_lock);  /* unlock, kernel */
    }

    kernel_bootstrap(0);                     /* kernel_bootstrap (boot CPU) */
    /* (secondary CPUs return to the entry / cpu->boot_func caller) */
}

/* ------------------------------------------------------------------ *
 * Kernel entry (kernel_entry) — annotated in osfmk/arm64/start.s.
 * On the boot CPU this path eventually calls arm_cpu_init (above), which
 * calls kernel_bootstrap (above), which runs kernel_bootstrap_thread. */
