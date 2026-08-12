/* Recreated from cl4_kernel.raw (cL4 Secure Kernel, arm64e, image base 0) —
 * the cL4 microkernel (GL1). Ground truth: Ghidra FUN_ names + addresses.
 * All names are estimates unless string/header matched.
 * Slice 07: 0x32cc70-0x33979c syscall/exception-entry region. */

#include <stdint.h>
#include <stddef.h>
#include "sk_internal.h"

/* Out-of-range callees (bodies reconstructed by their range workers). */
extern void FUN_0034d724(void);
extern void FUN_00348d94(void);
extern void FUN_00377824(void);
extern void FUN_0034b57c(void);
extern cl4_result_t FUN_00357104(void);
extern void FUN_00358750(word_t, word_t, word_t);
extern void FUN_0034e974(word_t);
extern void FUN_0036b270(void);

/* FUN_0032cc70 @ 0x32cc70   (est. sk_exception_entry)
 * Top-level exception/syscall entry dispatcher. Runs the pre-entry
 * setup sequence (timer/cpu setup helpers), then branches on the
 * carry/zero flag state left by the earlier result: on the success
 * path it performs a capability-transfer/write (copies the incoming
 * value through the x19/x20 frame words), invokes the copy helper and
 * calls a completion routine; on the failure path it releases the
 * incoming word and runs a cleanup/return helper.
 * Ghidra: void FUN_0032cc70(void)
 * Confidence: low (flag-driven entry, decompiler lost input flag state)
 * Notes: callees FUN_0034d724/348d94/377824/34b57c (setup),
 *   FUN_00357104 (result), FUN_00358750 (copy),
 *   FUN_0034e974 (release), FUN_0036b270 (cleanup). */
void sk_exception_entry(void)
{
    FUN_0034d724();          /* pre-entry setup */
    FUN_00348d94();
    FUN_00377824();
    FUN_0034b57c();
    cl4_result_t r = FUN_00357104();   /* obtain entry result/selector */

    if (!(/* carry */ false || /* zero */ false) && /* w12 */ 0 == 0 &&
        0xffffffffffffffe6 < (long long)r.lo) {
        /* success path: commit the capability write through the frame */
        *((word_t *)/* x19 */0) = *((word_t *)/* x20 */0);
        FUN_00358750(r.lo, r.hi, r.lo);   /* capability copy helper */
        ((void (*)(void))/* dispatch */0)();  /* completion dispatch */
    } else {
        FUN_0034e974(*((word_t *)/* x20 */0));  /* release incoming word */
        FUN_0036b270();                    /* cleanup/return */
    }
}
