/* Recreated from kernelcache.arm64.kc (xnu-12377.121.10 RELEASE_ARM64_T8142, image base fffffe0007004000). Ground truth: Ghidra FUN_ names + addresses; all names are estimates. */
#include "hv_compat.h"

/*
 * hv_kernel_iface.c — kernel-side consumers of the hypervisor (est.).
 *
 * Owned by the kernel-iface tree. This file does NOT recreate hypervisor code
 * (that lives in osfmk/arm64/hypervisor/); it documents the two directions
 * in which the rest of the kernel reaches the hypervisor:
 *
 *   1. The panic / coredump "docommand" command table (data @ 0x7e34c40
 *      region) — the dump-request path. The strings "hypervisor guest"
 *      (0x70c5886) and "Request that the hypervisor take a live kernel dump"
 *      (0x70c58af) are the DESCRIPTION (+0x18) of the "hvg" and
 *      "trigger_kernel_coredump" commands. The table itself is reconstructed
 *      below as read-only data; the walker/dispatcher is shared kernel
 *      panic/coredump code (stubbed, not recreated).
 *
 *   2. Hypervisor-presence consumers. The availability flag
 *      DAT_fffffe0007e41db0 is read by the mach-trap dispatcher hv_available
 *      (hv_available) and written by kernel_bootstrap_thread
 *      (kernel_bootstrap_thread); the hv_support / hv_disable boot-arg
 *      descriptors (0x7e2bda8 / 0x7e41dd0) point at the flag as their value
 *      storage. Presence is also reported via the IOKit "vmm-present"
 *      property by hv_vmm_present (hv_vmm_present). Both hv_available
 *      and hv_vmm_present are decompiled in their owning trees (support-init
 *      hv_support.c / trap-dispatch hv.c) and only referenced here.
 *
 * Ground truth: get_xrefs_to on 0x70c5886 and 0x70c58af return only the two
 * data slots 0x7e34f60 / 0x7e34fb0; get_xrefs_to on DAT_fffffe0007e41db0
 * returns exactly {0x7e2bda8, 0x7e41dd0 (DATA), hv_available READ, bootstrap
 * WRITE}. No other kernel function consumes the availability flag.
 */

#include "hv_kernel_iface.h"

/* ======================================================================== *
 * (1) Panic / coredump "docommand" command table (reconstructed data).
 * ======================================================================== */

/*
 * The two hypervisor-relevant entries in the coredump docommand list
 * (list head 0x7e34f18). Field offsets follow the 0x50-byte entry layout in
 * hv_kernel_iface.h. Only the description string is reproduced; the +0x08
 * code pointer for trigger_kernel_coredump (0xfffffe000b8f9f08) lies inside
 * FUN_fffffe000b8f91b8 and is not a clean docommand entry point, so the
 * entries are documented as data, not executed.
 */
const struct hv_coredump_docmd
hv_coredump_docmd_hvg[] = {
    {
        .name          = "hvg",                       /* @ 0x70c5882 */
        .value_or_func = 0,                           /* +0x08 0 */
        .help          = (const char *)0xfffffe00070f13bd, /* +0x10 (string) */
        .description   = "hypervisor guest",          /* +0x18 @ 0x70c5886 */
        .flags         = 1,                           /* +0x20 */
        .chain         = (void *)0xfffffe0007e34f18,  /* +0x28 list head */
        .mask          = 0xffffffffc2600003ULL,       /* +0x38 */
    },
};

const struct hv_coredump_docmd
hv_coredump_docmd_trigger_kernel_coredump[] = {
    {
        .name          = "trigger_kernel_coredump",        /* @ 0x70c5897 */
        .value_or_func = 0xfffffe000b8f9f08ULL,            /* +0x08 (mid-func) */
        .help          = (const char *)0xfffffe00070ec35e, /* +0x10 (string) */
        .description   = "Request that the hypervisor take a live kernel dump",
                                                          /* +0x18 @ 0x70c58af */
        .flags         = 1,                               /* +0x20 */
        .chain         = (void *)0xfffffe0007e34f18,      /* +0x28 list head */
        .mask          = 0xffffffff82e00004ULL,           /* +0x38 */
    },
};

/*
 * The list head 0x7e34f18 (this second docommand list) is chained to by both
 * entries above and by the "mp" entry (0x7e34fe8). The first list, headed at
 * 0x7e34c40, holds the VM-statistics / boot-arg docommands enumerated by the
 * trap-dispatch tree. The walker for both lists is shared kernel
 * panic/coredump code — not hypervisor code — and is not recreated.
 */

/* ======================================================================== *
 * (2) Hypervisor-presence gating (documented; consumers owned elsewhere).
 * ======================================================================== */

/*
 * Kernel-side hypervisor-presence summary (reconstructed from xref evidence).
 *
 * The availability flag DAT_fffffe0007e41db0 is the single presence gate the
 * kernel exposes to the hv mach-trap path:
 *
 *   - WRITTEN once at boot by kernel_bootstrap_thread (kernel_bootstrap_thread)
 *     from the return value of hv_support_init() (hv_support_init).
 *   - READ by hv_available (hv_available): if clear, every hv
 *     mach-trap returns error 0xfae9400f; else it dispatches through the
 *     19-entry op table PTR_hv_op_table.
 *   - The hv_support (0x7e2bda8) and hv_disable (0x7e41dd0) boot-arg
 *     descriptors use the flag address as their value-storage target, i.e. a
 *     "hv_support"/"hv_disable" boot-arg lands directly in the flag.
 *
 * The IOKit "vmm-present" property path (hv_vmm_present, hv_vmm_present)
 * is a second, read-only presence query used by the coredump docommand path;
 * it does not touch the flag.
 *
 * No hibernation / power-management / vm subsystem reads the availability
 * flag — get_xrefs_to(DAT_fffffe0007e41db0) returns only the four refs above.
 */
void hv_kernel_iface_presence_summary(void)
{
    /* Presence gating is entirely inside hv_available (support-init) and
     * hv_vmm_present (trap-dispatch); see those files for bodies. */
    (void)hv_available;
    (void)hv_vmm_present;
    (void)hv_available_flag;
}
