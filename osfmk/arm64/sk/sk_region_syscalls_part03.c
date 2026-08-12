/* Recreated from cl4_kernel.raw (cL4 Secure Kernel, arm64e, image base 0) —
 * the cL4 microkernel (GL1). Ground truth: Ghidra FUN_ names + addresses.
 * All names are estimates unless string/header matched.
 * Slice 03: 0x31a99c-0x31d4e8 syscall/exception-entry region. */

#include <stdint.h>
#include <stddef.h>
#include "sk_internal.h"
#include "sk_region_syscalls.h"

/* ------------------------------------------------------------------ *
 * Out-of-range cL4 helper declarations (declared extern with a one-line
 * note; their bodies are reconstructed by the range worker that owns them).
 * ------------------------------------------------------------------ */
