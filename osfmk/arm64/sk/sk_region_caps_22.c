/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel,
 * arm64e, image base 0) — the cL4 (Apple seL4-derived) microkernel (GL1).
 * Ground truth: Ghidra FUN_ names + addresses in program cl4_kernel.raw.
 * All names are estimates unless string/header-matched.
 *
 * Slice 22: 0x000f66a4 - 0x000f9b28 caps region.
 *
 * SeL4/cL4 vocabulary is used for naming: TCB, cap, CNode, IPC, notification,
 * endpoint, vspace, sched, etc. Confidence is medium unless a string matches.
 */
#include "sk_internal.h"

/* Shared kernel helpers used across this slice (out of slice).
 * FUN_002a4ab4 — enter monitored/trap context, recording an exception code.
 * FUN_003a25d4 — monitor lock/save primitive (takes a status word).
 * FUN_00027724 — resolve a PC-relative branch/jump slot to its target code pointer.
 * thunk_FUN_002acbb8 — completion/IPC primitive used after exception logging.
 * FUN_000fc85c — formatted kernel panic/log with (fmt, ...) varargs. */
