/* Recreated from kernelcache.arm64.kc (xnu-12377.121.10 RELEASE_ARM64_T8142, image base fffffe0007004000). Ground truth: Ghidra FUN_ names + addresses; all names are estimates. */

/*
 * hv_vmapple.h — Apple Virtualization (vmapple) service prototypes (est.).
 *
 * Owned by the vmapple-ipc tree.
 *
 * Covers the Hypervisor.framework access-gate and the IPC kobject handler
 * referenced by the IKOT_HYPERVISOR record (data @ fffffe000c7a9f28 -> string
 * fffffe0007072550, handler FUN_fffffe000b985e38). Ground truth is the Ghidra
 * FUN_* names + addresses; the estimated names below are guesses.
 */

#ifndef _HV_VMAPPLE_H_
#define _HV_VMAPPLE_H_

#include <stdint.h>
#include <stdbool.h>

/*
 * Hypervisor access-level gate. NOTE: owned by the entitlements tree — the
 * canonical prototype is `hv_entitlement_tier` in hv_entitlements.h. Not
 * declared here to avoid a double-declaration; see that header.
 *   FUN_fffffe000b985ae4 @ 0xfffffe000b985ae4
 */

/*
 * IPC kobject handler for the Hypervisor.framework service. Referenced by the
 * IKOT_HYPERVISOR record (data @ fffffe000c7a9f28). Under the hv lock it looks
 * up a hypervisor object by handle and tears it down when the container
 * refcount drops. param_1 = container/registry, param_2 = object handle.
 *   FUN_fffffe000b985e38 @ 0xfffffe000b985e38
 */
void hv_ikot_hypervisor_handler(uint64_t param_1, uint32_t param_2);

#endif /* _HV_VMAPPLE_H_ */
