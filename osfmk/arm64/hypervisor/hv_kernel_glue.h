/* Recreated from kernelcache.arm64.kc (xnu-12377.121.10 RELEASE_ARM64_T8142, image base fffffe0007004000). Ground truth: Ghidra FUN_ names + addresses; all names are estimates. */
#include "hv_compat.h"

/*
 * hv_kernel_glue.h — direct kernel-dependency interface for the hypervisor.
 *
 * Owned by the hv-deps tree.
 *
 * Per the FULL-AUDIT rule in AGENTS.md: kernel functions the hypervisor calls
 * DIRECTLY (its touch set) are recreated with bodies into hv_kernel_glue.c
 * when they are small / self-contained enough to audit; their own callees
 * (2+ levels into the kernel) stay stubbed externs. Universal XNU core
 * primitives that the whole kernel shares (mutex, refcount, zalloc/zfree,
 * waitq, per-CPU/task accessors, copyin/copyout, DT/boot-arg parsers) are
 * declared here as externs with the Ghidra FUN_ + address noted and are NOT
 * recreated — recreating them is recreating core XNU (out of branch scope).
 *
 * Functions recreated with bodies (see hv_kernel_glue.c):
 *   - current_task      current_task
 *   - waitq_validate    waitq_validate
 *   - hv_object_lookup  hv_object_lookup
 *
 * Functions kept as externs (universal XNU core / not recreatable):
 *   see the declaration block below.
 */

#ifndef _ARM64_HYPERVISOR_HV_KERNEL_GLUE_H_
#define _ARM64_HYPERVISOR_HV_KERNEL_GLUE_H_

#include <stdint.h>
#include <stddef.h>

/* ======================================================================== *
 * Recreated bodies (hv_kernel_glue.c).
 * ======================================================================== */

/* Validates that a waitq pointer is a live waitq-zone object (magic 0x15)
 * and registers its embedded lock; panics otherwise. waitq_validate. */
void waitq_validate(uint64_t waitq);

/* XNU container/object-registry lookup by handle + type. The hypervisor uses
 * this (via hv_ikot_hypervisor_handler hv_ikot_hypervisor_handler) to resolve its
 * registered IPC kobjects. Returns 1 when a live object of `type` matches
 * `handle`, 0 otherwise. hv_object_lookup. */
uint64_t hv_object_lookup(uint64_t *container, uint64_t handle, uint64_t type);

/* Current-task getter (validated task pointer from a per-CPU credential).
 * current_task. */
void *current_task(void *param_1);

/* ======================================================================== *
 * Universal XNU core — shared kernel, NOT recreated (see header comment).
 * ======================================================================== */

/* User<->kernel buffer move primitives. FUN_fffffe000b95c144 (est. copyin),
 * copyout (est. copyout). 100+ kernel callers each. */
extern int  copyin(const void *src, void *dst, size_t len);
extern int  copyout(const void *src, void *dst, size_t len);

/* Per-CPU struct / task getters. FUN_fffffe000b866ec4 (est. current_cpu_datap)
 * body is PAC'd — the decompiler only sees a panic stub, so it is NOT
 * recreatable and is used by the whole kernel. Extern. */
extern void *per_cpu_base(uint64_t cpu);

/* XNU mutex on the shared vm/owner lock DAT_fffffe000c62c0b8.
 * Canonical declarations live in hv_internal.h (lck_mtx_lock b7f0afc /
 * lck_mtx_unlock b7f1e80 / lock_release b7f1e4c). 100+ kernel callers;
 * full futex/waitq mutex implementation. Extern, NOT recreated. */

/* Kernel panics (all noreturn). FUN_fffffe000c0f86a4 / c0f8674 / c0f1874 /
 * c0e1c3c. Universal noreturn panic paths; not recreated. */
extern void kernel_panic_a(void) __attribute__((noreturn));  /* FUN_fffffe000c0f86a4 */
extern void kernel_panic_b(void) __attribute__((noreturn));  /* FUN_fffffe000c0f8674 */
extern void kernel_panic(void) __attribute__((noreturn));    /* FUN_fffffe000c0f1874 (hv_vmm.h alias) */
extern void kernel_panic_c(void) __attribute__((noreturn));  /* FUN_fffffe000c0e1c3c */

/* Object lifecycle. FUN_fffffe000b8afa78 (os_release, ARC-style release),
 * zfree_waitq (zone free w/ waitq teardown),
 * refcount_dec (refcount hash dec + free). Universal kernel. */
extern void os_release(void *object);
extern void zfree(void *object);
extern void refcount_dec(void *ref, void *free_fn);

/* Universal cache-topology lookup (stride 0xa8 descriptor table).
 * cache_type_lookup; 7 kernel callers; used by hv_caps_cpu_report. */
extern long cache_type_lookup(int idx);

/* OSMetaClass reserved-virtual-slot panic stub (FUN_fffffe000c0f8cfc) — NOT
 * an entitlement probe (earlier cred_has_entitlement de-guess corrected
 * 2026-08-12): pacibsp + tail-call c0f7394 which calls the class's
 * authenticated vtable+0x168 hook then panics "%s::_RESERVED%s%d called.
 * @%s:%d" (OSMetaClass.cpp:1406). Shared by 100+ IOKit class vtables. */
extern void osmeta_reserved_slot_panic(void);

/* Boot-filled ops-table pointer slot (static image value 0).
 * hv_entitlement_tier (b985ae4) dispatches the entitlement probe as
 * *(*(0x7e93310)+0x1c0)(task, entitlement); identity resolved at boot. */
extern uintptr_t cred_ops[];

#endif /* _ARM64_HYPERVISOR_HV_KERNEL_GLUE_H_ */
