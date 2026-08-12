/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel,
 * arm64e, image base 0) — the cL4 microkernel (GL1), "cL4 (679.100.61)".
 * Ground truth: Ghidra FUN_ names + addresses in program cl4_kernel.raw.
 * Slice 10: 0x348074-0x349abc syscall/exception-entry region.
 * All names are estimates unless string/header-matched.
 * Uses seL4/cL4 vocabulary (TCB, cap, CNode, IPC, notification, endpoint,
 * vspace, sched, syscall, trap). */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "sk_internal.h"

/* ------------------------------------------------------------------ *
 * Out-of-range cL4 helper declarations (declared extern with a one-line
 * note; their bodies are reconstructed by the range worker that owns them).
 * ------------------------------------------------------------------ */
extern uint64_t FUN_0036a908(unsigned long size, unsigned long tag); /* sk_alloc */
extern void FUN_0036b118(void *ptr);                                  /* sk_free */
extern uint64_t sk_lock_ref(uint64_t a);                              /* FUN_00377bec */
extern void sk_lock_release(uint64_t a);                              /* FUN_00377dcc */
extern void sk_enable_irq(void);                                      /* FUN_00350ca4 */
extern uint64_t sk_spin_irqsave(uint64_t *flags);                     /* FUN_00357cb4 */
extern void sk_irqrestore(uint64_t flags);                            /* FUN_00357c74 */
extern void *sk_current_tcb(void);                                    /* FUN_000867ec */
extern void *sk_cpu(void);                                            /* FUN_0008e518 */

/* String: "Fatal error" @ 0x005accd0 */
extern const char sk_fatal_error_str[];

/*--------------------------------------------------------------------*/
/* FUN_00348074 @ 0x348074   (est. sk_fatal_error_result)
 * Ghidra: undefined1[16] FUN_00348074(void)
 * Constructs the cL4 "Fatal error" result: a 16-byte pair whose low word is
 * a pointer to the literal "Fatal error" and whose high word is the code 0xb.
 * This is the classic seL4 error-pack: {message, code}. Used to signal an
 * unrecoverable trap/syscall error to a caller.
 * Confidence: medium.
 * Notes: refs string s_Fatal_error_005accd0.
 */
cl4_result_t sk_fatal_error_result(void)
{
    cl4_result_t r;
    r.lo = (uint64_t)&sk_fatal_error_str;  /* s_Fatal_error_005accd0 */
    r.hi = 0xb;
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_003480ac @ 0x3480ac   (est. sk_fatal_error_result_b)
 * Ghidra: undefined1[16] FUN_003480ac(void)
 * Identical to FUN_00348074: returns {msg="Fatal error", code=0xb}.
 * Confidence: medium (identical body).
 */
cl4_result_t sk_fatal_error_result_b(void)
{
    cl4_result_t r;
    r.lo = (uint64_t)&sk_fatal_error_str;
    r.hi = 0xb;
    return r;
}
