/* Recreated from cl4_kernel.raw (cL4 Secure Kernel, arm64e, image base 0) —
 * the cL4 microkernel (GL1). Ground truth: Ghidra FUN_ names + addresses.
 * All names are estimates unless string/header matched.
 * Slice 01: 0x80000-0x100000 caps region. */

#include <stdint.h>
#include <stddef.h>
#include "sk_internal.h"

/* Out-of-range cL4 helper declarations (declared extern with a one-line
 * note; bodies reconstructed by the range worker that owns them). */

/* FUN_00081ce8 @ 0x81ce8 — thunked helper (see 0x83f00). */
extern void *cL4_081ce8(void *a, void *b);
/* FUN_0006afb4 @ 0x6afb4 — out-of-slice helper (thunk at 0x83f04). */
extern void *cL4_06afb4(void *a);
/* FUN_0001612c @ 0x1612c — out-of-slice helper (thunk at 0x83f08). */
extern void *cL4_01612c(void *a);
/* FUN_0008192c @ 0x8192c — out-of-slice helper (thunk at 0x83f1c). */
extern void *cL4_08192c(void *a);
/* FUN_0006649c @ 0x6649c — out-of-slice helper (thunk at 0x8426c). */
extern void *cL4_06649c(void *a);
/* FUN_00034a2c @ 0x34a2c — out-of-slice helper (thunk at 0x851d0). */
extern void *cL4_034a2c(void *a);

/* Global: the current thread / TCB pointer. */
extern unsigned long cL4_current_thread;  /* _DAT_006c0380 */
