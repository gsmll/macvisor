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

/* FUN_000be37c @ 0x000be37c   (est. cL4_cap_ret_and_free_entry)
 * Ghidra: undefined FUN_000be37c(void)
 * PAC-entry stub (pacibsp) that immediately falls through into the
 * body at 0xbe380; the real work (release/return a capability via the
 * free helper FUN_000be218) lives in the adjacent function.
 * Confidence: low
 * Notes: Single pacibsp instruction; Ghidra split the PAC entry from body. */
void cL4_cap_ret_and_free_entry(void)
{
    /* pacibsp (PAC-sign stack pointer) then fall into FUN_000be380 */
}

/* FUN_000be380 @ 0x000be380   (est. cL4_cap_free_and_return)
 * Ghidra: undefined FUN_000be380(void)
 * Releases a capability object and returns: calls the object-free helper
 * FUN_000be218 (declared extern below), sign/verify frame, return.
 * Confidence: low
 * Notes: Thin wrapper: stp frame, bl FUN_000be218, retab. */
void cL4_cap_free_and_return(void)
{
    /* stp x29,x30; mov x29,sp; bl cL4_obj_free_218; ldp; retab */
}

/* FUN_000be394 @ 0x000be394   (est. cL4_cap_state_entry)
 * Ghidra: undefined FUN_000be394(void)
 * PAC-entry stub falling into 0xbe398 (which calls FUN_000be234).
 * Confidence: low */
void cL4_cap_state_entry(void)
{
}

/* FUN_000be398 @ 0x000be398   (est. cL4_cap_state_advance)
 * Ghidra: undefined FUN_000be398(void)
 * Thin wrapper around FUN_000be234 (extern): advances/processes cap state.
 * Confidence: low */
void cL4_cap_state_advance(void)
{
    /* bl cL4_cap_state_234 */
}

/* FUN_000be3ac @ 0x000be3ac   (est. cL4_cap_null_ret_entry)
 * Ghidra: undefined FUN_000be3ac(void)
 * PAC-entry stub: calls FUN_000be360 then forces lo=0x14, hi=0xd000...<<48.
 * Confidence: low */
void cL4_cap_null_ret_entry(void)
{
    /* bl cL4_cap_null_const; mov x0,#0x14; movk x0,#0xd000,lsl #48 */
}
