/* Recreated from cl4_kernel.raw (cL4 Secure Kernel, arm64e, image base 0) —
 * the cL4 microkernel (GL1). Ground truth: Ghidra FUN_ names + addresses.
 * All names are estimates unless string/header matched.
 * Slice 16: 0x34efb8-0x350038 syscall/exception-entry region. */

#include <stdint.h>
#include <stddef.h>
#include "sk_internal.h"
#include "sk_region_syscalls.h"

/* Out-of-range cL4 helpers referenced by this region (FUN_ addr in comment;
 * reconstructed by sibling SK range workers). Names are estimates. */

/*--------------------------------------------------------------------*/
/* FUN_0034efb8 @ 0x0034efb8   (est. sk_sys_null)
 * Ghidra: void FUN_0034efb8(void)
 * Empty no-op syscall entry: does nothing and returns. Likely a placeholder
 * or disabled syscall slot in the dispatch table.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_null(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_0034efc8 @ 0x0034efc8   (est. sk_sys_null2)
 * Ghidra: void FUN_0034efc8(void)
 * Empty no-op syscall entry; does nothing and returns.
 * Confidence: high (bare `return`).
 */
void sk_sys_null2(void)
{
    return;
}
