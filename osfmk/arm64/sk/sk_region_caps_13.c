/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel,
 * arm64e, image base 0) — the cL4 microkernel (GL1), "cL4 (679.100.61)".
 * Ground truth: Ghidra FUN_ names + addresses in program cl4_kernel.raw.
 * This region (0xbe360-0xcc088) is the caps / capability-machinery
 * subsystem (CNode, cap words, cap validation, capability lookup).
 * All names are estimates unless string/header-matched. */

#include <stdint.h>
#include <stddef.h>
#include "sk_internal.h"

/* ------------------------------------------------------------------ *
 * Out-of-range cL4 helper declarations (declared extern with a one-line
 * note; their bodies are reconstructed by the range worker that owns them).
 * ------------------------------------------------------------------ */


/* FUN_000be360 @ 0x000be360   (est. cL4_cap_null_const)
 * Ghidra: undefined1 [16] FUN_000be360(void)
 * Returns a fixed 16-byte capability constant {0xd000000000000014,
 * 0x80000000004c2350} — an inline, side-effect-free getter for a
 * kernel-internal capability word pair (lo = type/tag bits, hi = pointer
 * metadata). No inputs; no side effects.
 * Confidence: low
 * Notes: Small leaf; returns two immediate constants. */
cl4_result_t cL4_cap_null_const(void)
{
    cl4_result_t r;
    r.lo = 0xd000000000000014ull;
    r.hi = 0x80000000004c2350ull;
    return r;
}
