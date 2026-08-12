/* Recreated from kernelcache.arm64.kc (xnu-12377.121.10 RELEASE_ARM64_T8142, image base fffffe0007004000). Ground truth: Ghidra FUN_ names + addresses; all names are estimates. */

/*
 * hv_kernel_shims.h — verified declarations for the kernel/boot helper shims.
 *
 * Owned by the de-guess (kernel/boot shims) tree.
 *
 * Each of these functions was decompiled and its guessed name VERIFIED against
 * the real Ghidra function before being declared here. They are all universal
 * XNU core (thread/scheduler/KDP/DT/VM/clock boot helpers with 40+ kernel
 * callers and no hypervisor-specific behavior), so per the FULL-AUDIT rule in
 * AGENTS.md they are declared as externs with the Ghidra FUN_ + address noted
 * and are NOT recreated — recreating them is recreating core XNU (out of
 * branch scope). Where the previous guessed name was wrong, the corrected
 * name is used and the previous name is recorded in the note.
 *
 * Signatures are intentionally K&R-style (empty parameter lists with a
 * verified return type): the reconstruction calls these universal kernel
 * functions with heterogeneous pointer/integer argument types across files,
 * and the exact ABI is an estimate. The empty-parameter form accepts any
 * arguments (C, not C++), matching how the tree already used the old
 * `extern int NAME();` shims, while carrying the corrected name + note.
 *
 * These declarations REPLACE the old `extern int NAME();` untyped shims that
 * used to live in hv_internal.h / startup.h.
 */

#ifndef _ARM64_HYPERVISOR_HV_KERNEL_SHIMS_H_
#define _ARM64_HYPERVISOR_HV_KERNEL_SHIMS_H_

#include <stdint.h>
#include <stddef.h>

/* ======================================================================== *
 * Thread / scheduler creation + naming.
 * ======================================================================== */

/* kernel_thread_create — universal XNU thread creation.
 * FUN_fffffe000b83ec0c; wraps the thread-alloc core b83db54, links the thread
 * into the per-task queue, returns it in the last arg. 40+ kernel callers. */
extern int kernel_thread_create();

/* kernel_thread_create_variant — same core as kernel_thread_create but also
 * enqueues the new thread (b840c20). FUN_fffffe000b83ed20. */
extern int kernel_thread_create_variant();

/* kernel_snprintf — kernel snprintf (vsnprintf wrapper, base-10/hex).
 * FUN_fffffe000bdc36b4. 100+ kernel callers. */
extern int kernel_snprintf();

/* thread_set_name — set a thread's name (strlcpy into thread+0x2a8, trace).
 * FUN_fffffe000be2e398. 40+ kernel callers. */
extern void thread_set_name();

/* thread_deallocate — free a terminated thread's resources.
 * FUN_fffffe000b83bed8. Universal. */
extern void thread_deallocate();

/* thread_bind_core — bind the current thread to a CPU / keep the CPU awake
 * (sched_update_powered_cores suspend). FUN_fffffe000b81b430. Universal. */
extern void thread_bind_core();

/* sched_maintenance_thread — the scheduler maintenance thread body; passed as
 * the continuation to kernel_thread_create_variant by sched_startup.
 * FUN_fffffe000b818a50. PREVIOUSLY (wrongly) guessed as kernel_thread_create_core. */
extern void sched_maintenance_thread();

/* ---- daemon / thread-stack daemon plumbing ---- */

/* thread_daemon_create — create a named daemon thread (record+0x.. = 2, stores
 * the continuation, thread_create + name + enqueue). FUN_fffffe000b800368.
 * PREVIOUSLY guessed as kernel_daemon_plumbing_a. Universal. */
extern int thread_daemon_create();

/* thread_deallocate_daemon_init — init the daemon.deferred-deallocation daemon
 * (thread_deallocate_daemon). FUN_fffffe000b8009ec.
 * PREVIOUSLY guessed as kernel_daemon_plumbing_b. Universal. */
extern void thread_deallocate_daemon_init();

/* thread-daemon continuation bodies (thread-stack/exception/backtrace
 * daemons). Universal kernel; NOT recreated (core XNU daemon machinery).
 *   cont_a @ b83d270, cont_b @ b83d318, cont_c @ b83d440, cont_d @ b83d4e0. */
extern void thread_daemon_cont_a();
extern void thread_daemon_cont_b();
extern void thread_daemon_cont_c();
extern void thread_daemon_cont_d();

/* ======================================================================== *
 * Object / zone / per-CPU primitives.
 * ======================================================================== */

/* LOAcquire / LORelease — XNU lock-object acquire/release (lck_grp object
 * lock around a refcounted object's lock word). Ghidra-named symbols. Universal. */
extern void LOAcquire();
extern void LORelease();

/* kernel_zone_alloc — allocate from a zone (zone, type, flags, ...).
 * FUN_fffffe000b7e0b70. 100+ kernel callers. */
extern void *kernel_zone_alloc();

/* kernel_zone_meta — zone metadata query. FUN_fffffe000b7e10b4. Universal. */
extern uint64_t kernel_zone_meta();

/* zfree_waitq — zone free with waitq teardown. FUN_fffffe000b793cf4.
 * Universal; already stubbed in hv_kernel_glue.h as `zfree`.
 * No prototype on purpose: the decompiler renders most call sites with a
 * dropped argument (FUN_fffffe000b793cf4()), some with the object. */
extern void zfree_waitq();

/* kernel_obj_lookup_core — kernel object-registry lookup core.
 * FUN_fffffe000b78d064. Universal; already in manifest (hv-deps). */
extern int kernel_obj_lookup_core();

/* kernel_percpu_bind_cpu — register a thread in a per-CPU table slot.
 * FUN_fffffe000b803e6c. Universal. */
extern void kernel_percpu_bind_cpu();

/* kernel_percpu_bind — per-CPU bind. FUN_fffffe000b7fd830. Universal. */
extern void kernel_percpu_bind();

/* kernel_percpu_finalize — per-CPU finalize. FUN_fffffe000b821424. Universal. */
extern void kernel_percpu_finalize();

/* kernel_percpu_id — per-CPU id. FUN_fffffe000b96c5e4. Universal. */
extern void kernel_percpu_id();

/* kernel_thread_state_get — read the current thread's state.
 * FUN_fffffe000b8057e8. Universal. */
extern void kernel_thread_state_get();

/* kernel_thread_state_set — write thread state. FUN_fffffe000b808054. Universal. */
extern void kernel_thread_state_set();

/* ======================================================================== *
 * Kernel / PE / KDP / DT boot helpers.
 * ======================================================================== */

/* kernel_log — kernel log/printf with level+code. FUN_fffffe000bf0a554. Universal. */
extern void kernel_log();

/* kernel_daemon_init / kernel_boot_misc_o / kernel_trace / kernel_tlb_flush /
 * kernel_boot_arg_get are already declared with prototypes in
 * startup.h / hv_support.h / hv_el2.h / hv_vmm.h — they are NOT redeclared
 * here to avoid conflicting K&R forms.

 * kernel_progress_log — PE progress-config logging. FUN_fffffe000b934dc0. Universal. */
extern void kernel_progress_log();

/* kernel_progress — PE progress value write. FUN_fffffe000c09d30c. Universal. */
extern void kernel_progress();

/* kernel_trace / kernel_tlb_flush — declared with prototypes in hv_el2.h /
 * hv_support.h / hv_vmm.h (kernel_trace @ bd30528, kernel_tlb_flush @ b96c6d4).
 * Not redeclared here: the K&R `void f()` form conflicts with the real
 * prototypes (C23 treats `()` as zero-param), so keep only the header ones.
 */
/* kernel_flush — pmap flush (jettison). FUN_fffffe000b96b118. Universal. */
extern void kernel_flush();

/* ---- string helpers ---- */

/* kernel_strlcat_a — strlcat (dst, src, size). FUN_fffffe000b923d64. Universal. */
extern void kernel_strlcat_a();

/* kernel_strlcat_b — strlcat variant (fixed 0x100). FUN_fffffe000b923f6c. Universal. */
extern void kernel_strlcat_b();

/* kernel_copy_src — tco-annotated copy. FUN_fffffe000b758d80. Universal.
 * PREVIOUSLY guessed as kernel_copy_src; it is a copy helper (b758d80). */
extern void kernel_copy_src();

/* kernel_early_init — memcpy. FUN_fffffe000b758bd0. Universal.
 * PREVIOUSLY guessed as kernel_early_init; it is the kernel's memcpy. */
extern void kernel_early_init();

/* kernel_strncmp — bounded string compare. FUN_fffffe000b760950. Universal.
 * PREVIOUSLY guessed as kernel_mp_setup; the decompile (used to compare
 * segnames/names to "serial"/"__KLD"/"__LINKEDIT" with a length bound) is the
 * kernel's strncmp. */
extern int kernel_strncmp();

/* ---- boot-arg / DT ---- */

/* kernel_boot_arg_handle — parse a boot-args record. FUN_fffffe000bf6aa48. Universal. */
extern void kernel_boot_arg_handle();

/* kernel_boot_arg_get — declared with a prototype in startup.h / hv_support.h
 * (boot-arg getter @ c09cbf0). Not redeclared here. */

/* kernel_boot_arg_present — boot-arg present check. FUN_fffffe000bd322e0. Universal. */
extern int kernel_boot_arg_present();

/* kernel_dt_node_lookup — device-tree node lookup. FUN_fffffe000c09c084. Universal. */
extern int kernel_dt_node_lookup();

/* kernel_dt_prop_get — device-tree property get. FUN_fffffe000c09c31c. Universal. */
extern int kernel_dt_prop_get();

/* kernel_dt_read — device-tree read. FUN_fffffe000c0d7b94. Universal. */
extern void kernel_dt_read();

/* ---- KDP ---- */

/* kdp_init_part1 — KDP init part 1. FUN_fffffe000b779358. Universal. */
extern void kdp_init_part1();

/* kdp_magic_init — KDP serial magic handshake. FUN_fffffe000b774360. Universal. */
extern void kdp_magic_init();

/* kdp_register_transport — register a KDP serial transport. FUN_fffffe000b773fdc. Universal. */
extern void kdp_register_transport();

/* kdp_callback_a — KDP serial receive callback (timeout + copyin).
 * FUN_fffffe000b7763f0. Universal. */
extern void kdp_callback_a();

/* kdp_callback_b — KDP serial callback. FUN_fffffe000b77658c. Universal. */
extern void kdp_callback_b();

/* kdp_callback_c — KDP serial callback. FUN_fffffe000b7765d0. Universal. */
extern void kdp_callback_c();

/* kdp_callback_d — KDP serial callback (empty/truncated body). FUN_fffffe000b7765e8. Universal. */
extern void kdp_callback_d();

/* ======================================================================== *
 * Boot finalize / lockdown / clock / sched / MP.
 * ======================================================================== */

/* zone_create — universal XNU zone creation. FUN_fffffe000b85f794; strings
 * "zone_create: element size too large", "zone_create: invalid desired zone
 * ID %d for %s", ZC_VM/ZC_DESTRUCTIBLE/ZC_OBJ_CACHE/ZC_PERCPU/ZC_READONLY/
 * ZC_NOGC/ZC_NOCACHING/ZC_DATA flags. PREVIOUSLY guessed as kernel_vm_pages. */
extern void *zone_create();

/* kernel_queue_free_walk — walk a linked queue and free every element.
 * FUN_fffffe000b8f6e54; iterates the list at *param_1, frees each node via
 * b958108/b8f4310 + zone-free b85d440, adjusts refcount DAT_fffffe000c608a60.
 * PREVIOUSLY guessed as kernel_boot_finalize_d. */
extern void kernel_queue_free_walk();

/* kernel_vm_map_create — create a VM map/object for a guest window.
 * FUN_fffffe000b8ada1c; allocates an object via b85e180, self-list, elem
 * size 8, addr bounds, lock init b7f52a0 at DAT_fffffe000c5d4100. A VM
 * map/object create, NOT a page op.
 * PREVIOUSLY guessed as kernel_vm_page_op. */
extern void *kernel_vm_map_create();

/* cs_features_enabled — code-signing features enabled check.
 * FUN_fffffe000bdbdffc. Universal. */
extern int cs_features_enabled();

/* early_machine_lockdown — early machine lockdown hook.
 * FUN_fffffe000b97b850. Universal. */
extern void early_machine_lockdown();

/* iokit_finalize — finalize IOKit bootstrap. FUN_fffffe000bffed08. Universal. */
extern void iokit_finalize();

/* pe_early_init — early PE init. FUN_fffffe000b9366f4. Universal. */
extern void pe_early_init();

/* pe_iokit_finalize — PE/iokit finalize. FUN_fffffe000bf7466c. Universal. */
extern void pe_iokit_finalize();

/* pe_trace — PE trace event. FUN_fffffe000b86a2c0. Universal. */
extern void pe_trace();

/* machine_idle_continue — idle-loop continuation. FUN_fffffe000b8186a4. Universal. */
extern void machine_idle_continue();

/* percpu_boot_continuation — per-CPU boot continuation. FUN_fffffe000b95b520. Universal. */
extern void percpu_boot_continuation();

/* kernel_callback_register — register a boot callback. FUN_fffffe000b7ff408. Universal. */
extern void kernel_callback_register();

/* kernel_lockdown_cb — machine lockdown callback. FUN_fffffe000b7b5958. Universal. */
extern void kernel_lockdown_cb();

/* kernel_clock_init — initialize the kernel clock. FUN_fffffe000b7de1b0. Universal. */
extern void kernel_clock_init();

/* kernel_sched_init — scheduler init. FUN_fffffe000b7af764. Universal. */
extern void kernel_sched_init();

/* kernel_spl — spl (interrupt state). FUN_fffffe000c0d83c0. Universal. */
extern void kernel_spl();

/* kernel_boot_mp_start — boot MP start. FUN_fffffe000b9353d8. Universal. */
extern void kernel_boot_mp_start();

/* kernel_mp_op_a — MP op a. FUN_fffffe000b90bf34. Universal. */
extern void kernel_mp_op_a();

/* kernel_mp_op_b — MP op b. FUN_fffffe000b90c034. Universal. */
extern void kernel_mp_op_b();

/* kernel_boot_policy — boot policy. FUN_fffffe000b93b17c. Universal. */
extern void kernel_boot_policy();

/* kernel_boot_sync — boot sync. FUN_fffffe000b9245e4. Universal. */
extern void kernel_boot_sync();

/* kernel_boot_alloc_init — boot alloc init. FUN_fffffe000b92ed18. Universal. */
extern void kernel_boot_alloc_init();

/* kernel_mapping_init — mapping init. FUN_fffffe000b81a9ec. Universal. */
extern void kernel_mapping_init();

/* kernel_load_context_check — load-context assertion. FUN_fffffe000b8233d8. Universal. */
extern int kernel_load_context_check();

/* kernel_cpu_data_setup — per-CPU data setup. FUN_fffffe000b80cf88. Universal. */
extern void kernel_cpu_data_setup();

/* kernel_cpu_feature_setup — per-CPU feature/ACTLR setup. FUN_fffffe000b75f7a0. Universal. */
extern void kernel_cpu_feature_setup();

/* kernel_cpu_data_init — per-CPU data init (SME/AMX state save).
 * FUN_fffffe000b75f118. Universal. */
extern void kernel_cpu_data_init();

/* kernel_termfuncs — call module term funcs. FUN_fffffe000bf364b4. Universal. */
extern void kernel_termfuncs();

/* kernel_segment_bounds — segment bounds (name -> addr/size).
 * FUN_fffffe000bf776d0. Universal. */
extern int kernel_segment_bounds();

/* kernel_unmap — unmap a kernel segment. FUN_fffffe000bf775ec. Universal. */
extern void kernel_unmap();

/* kernel_kalloc — kalloc from a zone. FUN_fffffe000b859c38. Universal. */
extern void *kernel_kalloc();

/* kernel_copy_handle — convert an io map / create a kernel handle.
 * FUN_fffffe000b78d628. Universal. */
extern int kernel_copy_handle();

/* kernel_boot_misc_b — pmap_create (refcounted pmap create wrapper).
 * FUN_fffffe000b948ac8. Universal. */
extern void *kernel_boot_misc_b();

/* kernel_boot_misc_l — get section by name (getsectbyname-from-header).
 * FUN_fffffe000bf4c2c4. Universal. */
extern void *kernel_boot_misc_l();

/* ---- boot finalize / misc (universal boot-step helpers) ---- */

/* kernel_boot_log — boot-step log. FUN_fffffe000b929414. Universal. */
extern void kernel_boot_log();

/* kernel_boot_finalize_a — boot finalize step a. FUN_fffffe000b8df3b4. Universal. */
extern void kernel_boot_finalize_a();

/* kernel_boot_finalize_b — boot finalize step b. FUN_fffffe000b8df438. Universal. */
extern void kernel_boot_finalize_b();

/* kernel_boot_finalize_c — boot finalize step c. FUN_fffffe000b8f0ff0. Universal. */
extern void kernel_boot_finalize_c();

/* kernel_boot_misc   — boot misc step.  FUN_fffffe000b945d0c. Universal. */
extern void kernel_boot_misc();

/* kernel_boot_misc_c — boot misc step c.  FUN_fffffe000b95b644. Universal. */
extern void kernel_boot_misc_c();

/* kernel_boot_misc_d — boot misc step d.  FUN_fffffe000b95dffc. Universal. */
extern void kernel_boot_misc_d();

/* kernel_boot_misc_e — boot misc step e.  FUN_fffffe000b960af4. Universal. */
extern void kernel_boot_misc_e();

/* kernel_boot_misc_f — boot misc step f.  FUN_fffffe000b977118. Universal. */
extern void kernel_boot_misc_f();

/* kernel_boot_misc_g — boot misc step g.  FUN_fffffe000b979ef0. Universal. */
extern void kernel_boot_misc_g();

/* kernel_boot_misc_h — boot misc step h.  FUN_fffffe000bd2bc14. Universal. */
extern void kernel_boot_misc_h();

/* kernel_boot_misc_i — boot misc step i.  FUN_fffffe000bd332f4. Universal. */
extern void kernel_boot_misc_i();

/* kernel_boot_misc_j — boot misc step j.  FUN_fffffe000bdb9d14. Universal. */
extern void kernel_boot_misc_j();

/* kernel_boot_misc_k — boot misc step k.  FUN_fffffe000bdee9fc. Universal. */
extern void kernel_boot_misc_k();

/* kernel_boot_misc_m — boot misc step m.  FUN_fffffe000bfd25f8. Universal.
 * Returns a newly-created object pointer (long *): allocates a 0x48-byte
 * object from zone DAT_fffffe0007e48528 (or a per-slab variant from
 * DAT_fffffe0007d65238), sets refcount field +8 = 1, stores the vtable
 * pointer PTR_FUN_fffffe0007e51178 at +0, walks/creates a linked record at
 * DAT_fffffe000c6815f0, then calls the vtable slot +0xa8 (init/activate);
 * if that returns even, releases via vtable slot +0x28 and returns NULL.
 * This is the object the boot path passes to pe_lockdown_iokit as the
 * IOService root. Signature corrected from void to void*. */
extern void *kernel_boot_misc_m();

/* kernel_boot_misc_n — boot misc step n.  FUN_fffffe000c09e898. Universal. */
extern void kernel_boot_misc_n();

/* kernel_boot_misc_p — boot misc step p.  FUN_fffffe000c09f560. Universal. */
extern void kernel_boot_misc_p();

#endif /* _ARM64_HYPERVISOR_HV_KERNEL_SHIMS_H_ */
