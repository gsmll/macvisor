/* Recreated from kernelcache.arm64.kc (xnu-12377.121.10 RELEASE_ARM64_T8142, image base fffffe0007004000). Ground truth: Ghidra FUN_ names + addresses; all names are estimates. */

/*
 * hv_kernel_shims.c — kernel/boot helper shims: verification notes.
 *
 * Owned by the de-guess (kernel/boot shims) tree.
 *
 * This tree de-guessed ~90 kernel/boot helper shims that used to be untyped
 * `extern int NAME();` declarations in hv_internal.h / startup.h. Each was
 * decompiled and its guessed name VERIFIED against the real Ghidra function.
 * Every one turned out to be universal XNU core (thread/scheduler/KDP/DT/VM/
 * clock boot helpers with 40+ kernel callers and no hypervisor-specific
 * behavior), so per the FULL-AUDIT rule in AGENTS.md they are declared as
 * verified externs in hv_kernel_shims.h and are NOT recreated here —
 * recreating them is recreating core XNU (out of branch scope).
 *
 * The declarations replaced the old untyped shims. The verification
 * decompiles, the corrected names, and the FUN_ addresses live in
 * docs/manifest.json (tree "de-guess") and docs/findings.md.
 */

#include "hv_kernel_shims.h"
