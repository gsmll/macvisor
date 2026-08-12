/* Recreated from cl4_kernel.raw (cL4 Secure Kernel, arm64e, image base 0) —
 * the cL4 microkernel (GL1). Ground truth: Ghidra FUN_ names + addresses.
 * All names are estimates unless string/header matched.
 * Slice 11: 0x80000-0x100000 caps region. */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "sk_internal.h"

/* ======================================================================
 * Out-of-range cL4 helper declarations (bodies owned by other range
 * workers; declared extern with a one-line note).
 * ====================================================================== */

/* FUN_002a0cf8 — general cL4 helper (invoked by many caps-region stubs). */
extern void cL4_helper_002a0cf8(void);

/* ======================================================================
 * Caps-region functions (ascending address order).
 * ====================================================================== */

/* FUN_000b44cc @ 0x000b44cc   (est. cL4_noop_helper)
 * Ghidra: undefined FUN_000b44cc(void)
 * Thin pass-through wrapper that invokes the shared cL4 helper and
 * returns; used as a uniform entry point from the caps-region dispatch.
 * Confidence: high
 * Notes: body is a single call to FUN_002a0cf8 (out of slice). */
void cL4_noop_helper(void)
{
    cL4_helper_002a0cf8();
}
