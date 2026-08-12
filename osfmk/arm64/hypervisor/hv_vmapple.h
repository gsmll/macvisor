/* Recreated from kernelcache.arm64.kc (xnu-12377.121.10 RELEASE_ARM64_T8142, image base fffffe0007004000). Ground truth: Ghidra FUN_ names + addresses; all names are estimates. */
#include "hv_compat.h"

/*
 * hv_vmapple.h — Apple Virtualization (vmapple) service prototypes (est.).
 *
 * Owned by the vmapple-ipc tree.
 *
 * Covers the Hypervisor.framework access-gate and the IPC kobject handler
 * referenced by the IKOT_HYPERVISOR record (data @ fffffe000c7a9f28 -> string
 * fffffe0007072550, handler hv_ikot_hypervisor_handler). Ground truth is the Ghidra
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
 *   hv_entitlement_tier @ 0xfffffe000b985ae4
 */

/*
 * IPC kobject handler for the Hypervisor.framework service. Referenced by the
 * IKOT_HYPERVISOR record (data @ fffffe000c7a9f28). Under the hv lock it looks
 * up a hypervisor object by handle and tears it down when the container
 * refcount drops. param_1 = container/registry, param_2 = object handle.
 *   hv_ikot_hypervisor_handler @ 0xfffffe000b985e38
 */
void hv_ikot_hypervisor_handler(uint64_t param_1, uint32_t param_2);

/*
 * vmapple surface conclusion (vmapple-deep, 2026-08-11):
 * The vmapple service in this kernelcache is genuinely SMALL. 'vmapple'
 * appears exactly once in the 121 MB binary (the entitlement string
 * com.apple.private.hypervisor.vmapple @ fffffe000707250e, 3 xrefs all
 * already owned). There is NO separate nested-VM/vmapple vmm: the vmapple
 * entitlement only elevates the entitlement tier (b985ae4 -> 3) for the SAME
 * Hypervisor.framework mach-trap service (op table PTR_hv_op_table).
 * The vmapple surface = this IKOT handler + the entitlement gate + the
 * object-registry glue (hv_object_lookup b7e0d8c, rbtree b9860bc). Full
 * evidence (strings searched, tables examined, callees BFS'd) is documented
 * in the conclusion block of hv_vmapple.c and docs/chain-map.md.
 */

#endif /* _HV_VMAPPLE_H_ */
