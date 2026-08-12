/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel, GL1,
 * arm64e, image base 0) — the cL4 microkernel. Ground truth: Ghidra FUN_ names +
 * addresses in cl4_kernel.raw. Version "cL4 microkernel (cL4 (679.100.61))".
 * All names are estimates unless string/header-matched.
 *
 * This file covers the 0x60000-0x70000 region: object method-dispatch tables
 * and the early boot / object-constructor dispatch machinery. SeL4/cL4
 * vocabulary (TCB, cap, CNode, IPC, notification, endpoint, vspace, sched,
 * boot, etc.). Confidence is medium unless a string matches. */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "sk_internal.h"

/* ------------------------------------------------------------------ *
 * Out-of-range cL4 helper declarations (declared extern with a one-line
 * note; their bodies are reconstructed by the range worker that owns them).
 * ------------------------------------------------------------------ */

/* Core allocator / object primitives (region 0x34xxxx-0x37xxxx). */
extern void *sk_alloc(unsigned long size, unsigned long tag);        /* FUN_0036a908 */
extern void sk_free(void *ptr);                                      /* FUN_0036b118 */
extern unsigned long sk_object_lock(unsigned long a, unsigned long b,
                                    unsigned long c, void *d, void *e); /* FUN_00377824 */
extern void *sk_current_tcb(void);                                   /* FUN_000867ec */
extern void *sk_cpu(void);                                           /* FUN_0008e518 */

