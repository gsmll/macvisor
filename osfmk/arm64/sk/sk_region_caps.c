/* Recreated from cl4_kernel.raw (cL4 Secure Kernel, arm64e, image base 0) —
 * the cL4 microkernel (GL1). Ground truth: Ghidra FUN_ names + addresses.
 * All names are estimates unless string/header matched.
 *
 * This is the cL4 caps region (0x80000-0x100000): capability / CNode / object
 * primitives, the exclave launcher, endpoint and notification services, the
 * VAS (virtual address space) layer, and the PMM-instance vtable thunks that
 * sit at the caps/object boundary.
 *
 * The bodies live in the per-slice compilation units sk_region_caps_00..24.c
 * (each individually compiles clean and is named in docs/sptm/manifest.json).
 * This file is the region umbrella for cross-referencing.
 */
