/* Recreated from ringminus1/sk/cl4_kernel.raw (cL4 Secure Kernel, arm64e,
 * image base 0) — the cL4 microkernel (GL1), "cL4 (679.100.61)".
 * Ground truth: Ghidra FUN_ names + addresses in program cl4_kernel.raw.
 * Slice 12: 0x34af04-0x34c034 syscall/exception-entry region.
 * All names are estimates unless string/header-matched. Uses seL4/cL4
 * vocabulary (TCB, cap, CNode, IPC, notification, endpoint, vspace, sched,
 * syscall, trap, GENTER/GEXIT). */

#include <stdint.h>
#include <stddef.h>
#include "sk_internal.h"

/* ------------------------------------------------------------------ *
 * Out-of-range cL4 helper declarations (their bodies are reconstructed by
 * the range worker that owns them; declared here for linkage).
 * ------------------------------------------------------------------ */
extern void FUN_00310ad4(void);   /* out of slice */
extern void FUN_00027754(void);   /* out of slice */
