/* Recreated from kernelcache.arm64.kc (xnu-12377.121.10 RELEASE_ARM64_T8142, image base fffffe0007004000). Ground truth: Ghidra FUN_ names + addresses; all names are estimates. */
#include "hv_compat.h"

/*
 * hv_kernel_iface.h — kernel-side consumers of the hypervisor (est.).
 *
 * Owned by the kernel-iface tree. Documents the two ways the rest of the
 * kernel touches the hypervisor:
 *
 *   (1) The panic / coredump "docommand" command table (data @ 0x7e34c40
 *       region, list head 0x7e34f18) through which the kernel requests a live
 *       hypervisor kernel dump ("trigger_kernel_coredump") and describes the
 *       hypervisor guest ("hvg"/"hypervisor guest"). Reconstructed here as
 *       read-only data; the walker is shared kernel panic/coredump code.
 *
 *   (2) Hypervisor-presence checks. The availability flag
 *       DAT_fffffe0007e41db0 is READ only by the mach-trap dispatcher
 *       hv_available (est. hv_available, support-init) and WRITTEN by
 *       kernel_bootstrap_thread (kernel_bootstrap_thread) from
 *       hv_support_init()'s return; the hv_support / hv_disable boot-arg
 *       descriptors (0x7e2bda8 / 0x7e41dd0) use the flag address as their
 *       value-storage target. The IOKit "vmm-present" property path
 *       (hv_vmm_present, est. hv_vmm_present, trap-dispatch) is the
 *       second presence query. No hibernation / power / vm subsystem reads the
 *       availability flag directly.
 */

#ifndef _ARM64_HYPERVISOR_HV_KERNEL_IFACE_H_
#define _ARM64_HYPERVISOR_HV_KERNEL_IFACE_H_

#include <stdint.h>

/* ======================================================================== *
 * (1) Panic / coredump "docommand" table (read-only data, 0x7e34c40 region).
 * ======================================================================== */

/*
 * One docommand entry, 0x50 bytes, chained into a queue whose head is
 * 0x7e34f18 (the second, hv-related list; the VM-stat list is headed at
 * 0x7e34c40). Fields read directly from the kernelcache bytes:
 *   +0x00 name        : ASCII command name (string pointer)
 *   +0x08 value/handler: 0 for "hvg"; a code pointer for commands that act
 *   +0x10 help        : short help string pointer
 *   +0x18 description : human-readable description string pointer
 *   +0x20 flags       : 1
 *   +0x28 chain       : pointer back to the list head 0x7e34f18
 * The +0x08 code pointer for "trigger_kernel_coredump" (0xfffffe000b8f9f08)
 * falls INSIDE FUN_fffffe000b8f91b8 (a large VM contiguous-page function),
 * so it is not a clean docommand entry point; the actual live-dump request
 * is issued by the shared kernel coredump path (stubbed, not recreated).
 */
struct hv_coredump_docmd {
    const char *name;          /* +0x00 command name (string ptr) */
    uint64_t    value_or_func; /* +0x08 0 or a code/data pointer */
    const char *help;          /* +0x10 short help (string ptr) */
    const char *description;   /* +0x18 human-readable description */
    uint64_t    flags;         /* +0x20 1 */
    void       *chain;         /* +0x28 -> list head 0x7e34f18 */
    uint64_t    pad0;          /* +0x30 */
    uint64_t    mask;          /* +0x38 type/mask word */
    uint64_t    pad1;          /* +0x40 */
    uint64_t    pad2;          /* +0x48 */
};

/*
 * The two hypervisor-relevant docommand entries (both in the 0x7e34f18 list):
 *   "hvg"                @ 0x7e34f48  desc "hypervisor guest"   (0x70c5886)
 *   "trigger_kernel_coredump" @ 0x7e34f98
 *                        desc "Request that the hypervisor take a live
 *                             kernel dump"                     (0x70c58af)
 * They are the kernel's coredump/panic interface for requesting a live dump
 * of a hypervisor guest. Reconstructed as data; not decompiled.
 */

/* ======================================================================== *
 * (2) Hypervisor-presence consumers (owned by other trees; declared here).
 * ======================================================================== */

/* est. hv_available (FUN_fffffe000b984ed8, support-init) — mach-trap
 * dispatcher; returns 0xfae9400f when hv_available_flag is clear, else
 * dispatches cmd through the PTR_hv_op_table op table. */
extern void hv_available(long param_1);

/* est. hv_vmm_present (FUN_fffffe000be39fd0, trap-dispatch) — reads the
 * IOKit "vmm-present" boot property and copies the normalized 0/1 out. */
extern void hv_vmm_present(void *trap_record);

/* hv availability flag DAT_fffffe0007e41db0 — written at boot by
 * kernel_bootstrap_thread (hv_support_init return); read by hv_available. */
extern uint64_t hv_available_flag;

/* Shared kernel coredump/panic path (not recreated). */
extern void kernel_panic_msg_fmt(const char *fmt, ...) __attribute__((noreturn));


/* ---- raw kernel/boot helpers referenced as calls (identity uncertain;
 * old-style declarations so the tree compiles; NOT recreated) ---- */
#endif /* _ARM64_HYPERVISOR_HV_KERNEL_IFACE_H_ */
