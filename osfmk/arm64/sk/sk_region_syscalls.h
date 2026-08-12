/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel,
 * arm64e, image base 0) — the cL4 (Apple seL4-derived) microkernel (GL1).
 * Ground truth: Ghidra FUN_ names + addresses in program cl4_kernel.raw.
 * All names are estimates unless string/header-matched.
 *
 * Shared types / helpers for the syscall + exception-entry region
 * 0x300000 - 0x380000. cL4/seL4 vocabulary (TCB, cap, CNode, IPC,
 * notification, endpoint, vspace, sched, syscall, trap, etc.).
 */
#ifndef SK_REGION_SYSCALLS_H
#define SK_REGION_SYSCALLS_H

#include <stdint.h>
#include <stddef.h>

/* Word / cap / tcb types (cL4, arm64). */
typedef uint64_t sk_word_t;
typedef uint64_t sk_cap_t;          /* capability word */
typedef uint32_t sk_cptr_t;         /* capability pointer */
typedef uint64_t sk_obj_ref_t;      /* kernel object reference */
typedef uint64_t sk_error_t;        /* seL4 error type (seL4_Error) */

/* Ghidra's undefined* maps to these fixed-width types. */
typedef uint8_t  und1_t;
typedef uint16_t und2_t;
typedef uint32_t und4_t;
typedef uint64_t und8_t;

/* Kernel trap / syscall entry dispatch tables. */
typedef und8_t (*sk_syscall_handler_t)(und8_t, und8_t, und8_t, und8_t,
    und8_t, und8_t, und8_t, und8_t);

#endif /* SK_REGION_SYSCALLS_H */
