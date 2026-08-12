/* Recreated from kernelcache.arm64.kc (xnu-12377.121.10 RELEASE_ARM64_T8142, image base fffffe0007004000). Ground truth: Ghidra FUN_ names + addresses; all names are estimates. */

#ifndef _HV_HELPERS_H_
#define _HV_HELPERS_H_

/*
 * hv_helpers.h — hypervisor-owned helpers and the EL1 guest-exit handlers.
 *
 * Owned by the hv-helpers tree. These functions were previously shimmed as
 * "shared kernel"; decompilation showed they are hypervisor behavior (mutex
 * teardown, per-CPU broadcast, flush lock, debug-register write, AMX/SVE EL2
 * swap, region-tree teardown) or the EL1 exception handlers the guest-exit
 * path returns into. Bodies live in hv_helpers.c.
 */

#include "hv_compat.h"

/* FUN_fffffe000b7f09dc @ 0xfffffe000b7f09dc — mutex destroy + zone free. */
void hv_vm_pool_release(uint32_t *lock, long zone);

/* FUN_fffffe000b8627ac @ 0xfffffe000b8627ac — per-CPU broadcast/copy. */
void hv_cpu_broadcast(long *list, long data);

/* FUN_fffffe000b8563f8 @ 0xfffffe000b8563f8 — flush-lock acquire (waitq). */
void hv_flush_lock_op(uint32_t *lock, uint64_t a, uint64_t b, uint32_t c, uint64_t d);

/* FUN_fffffe000b954160 @ 0xfffffe000b954160 — hardware debug-register write. */
void hv_debug_reg_apply(long pmap, unsigned char reg, ...);

/* FUN_fffffe000b7a1dd8 @ 0xfffffe000b7a1dd8 — IPC message send (est.). */
uint64_t hv_percpu_notify(long port, uint64_t msg);

/* FUN_fffffe000b85e180 @ 0xfffffe000b85e180 — per-CPU queue pop (16-byte ret). */
uint64_t hv_percpu_queue_pop(long cpu, long buf, uint64_t flags);

/* FUN_fffffe000b9882ac @ 0xfffffe000b9882ac — AMX/SVE EL2 state swap. */
void hv_el2_state_activate(long vcpu);

/* FUN_fffffe000b987c44 @ 0xfffffe000b987c44 — VM region-tree teardown. */
void hv_vm_owner_teardown(long *owner);

/* FUN_fffffe000b9888a4 @ 0xfffffe000b9888a4 — EL1 hardware debug-state save.
 * Saves DBGBVR/BCR + DBGWVR/WCR into the EL2 save block at `es`. */
void hv_vcpu_debug_save(uint64_t es);

/* FUN_fffffe000b95ecd8 @ 0xfffffe000b95ecd8 — cross-call / IPI signal (cpu_signal). */
uint64_t cpu_signal(long cpu, uint32_t signal, uint64_t a, uint64_t b, int arg5);

/* EL1 exception handlers (guest-exit continuation; VBAR_EL1 = b75c000). */
void el1_sync_handler(long frame, uint64_t esr, uint64_t far);   /* FUN_fffffe000b75deac */
void el1_fiq_handler(void);                                       /* FUN_fffffe000b75df7c */
void el1_irq_handler(void);                                       /* FUN_fffffe000b75e000 */
void el1_error_handler(void);                                     /* FUN_fffffe000b75e058 */

#endif /* _HV_HELPERS_H_ */
