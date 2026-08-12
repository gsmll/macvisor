/* Recreated from cl4_kernel.raw (cL4 Secure Kernel, arm64e, image base 0) —
 * the cL4 microkernel (GL1), "cL4 (679.100.61)".
 * Ground truth: Ghidra FUN_ names + addresses in program cl4_kernel.raw.
 * All names are estimates unless string/header matched.
 * Slice 15: 0x34e004-0x34efa8 syscall/exception-entry region. */

#include <stdint.h>
#include <stddef.h>
#include "sk_internal.h"
#include "sk_region_syscalls.h"

/* cL4 returns many values as a 16-byte pair (two 64-bit words in x0/x1).
 * Model it as a struct so callers can carry both halves. */
typedef struct { unsigned long lo, hi; } cL4_w16_t;
