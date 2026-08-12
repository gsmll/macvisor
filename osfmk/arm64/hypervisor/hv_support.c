/* Recreated from kernelcache.arm64.kc (xnu-12377.121.10 RELEASE_ARM64_T8142, image base fffffe0007004000). Ground truth: Ghidra FUN_ names + addresses; all names are estimates. */

/*
 * hv_support.c — hypervisor support/init: boot entry, EL2 feature
 * detection, availability (mach-trap dispatcher).
 *
 * Owned by the support-init tree.
 * Seed roots: FUN_fffffe000b984d4c (est. hv_support_init),
 *   FUN_fffffe000b987fa8 (est. hv_el2_feature_detect),
 *   FUN_fffffe000b984ed8 (est. hv_available / mach-trap dispatcher).
 *
 * The hv mach-trap operation table this tree dispatches through lives at
 * PTR_FUN_fffffe0007e0d750; its handlers are owned by the vcpu-core and
 * trap-dispatch trees (see docs/manifest.json).
 */

#include "hv_support.h"

/* ------------------------------------------------------------------ *
 * FUN_fffffe000b984d4c @ 0xfffffe000b984d4c   (est. hv_support_init)
 * Ghidra: undefined8 FUN_fffffe000b984d4c(void)
 * Boot-time hypervisor support initialization. Runs only when the CPU is
 * executing at EL2 (currentel bits [3:2] == 8) and the SoC/chip identifier
 * (DAT_fffffe0007e0c03c, high byte 0x61 = 'a') marks an Apple implementer.
 * Selects feature flag bits 3 and 4 of DAT_fffffe0007e0d820 from the chip
 * id, then (for non-AVF products) reads the ISA VM quota from the
 * "apple-isa-vm-quota" device-tree property, clamps it to INT_MAX, writes it
 * to the quota globals, and lets a "hv_apple_isa_vm_quota" boot-arg override
 * it when the enable bit in DAT_fffffe0007e255f8 is set. Finally runs EL2
 * feature detection (FUN_fffffe000b987fa8) and returns 1 on success, 0 if
 * EL2 is not active or the chip is unsupported.
 * Confidence: high
 * Notes: writes DAT_fffffe0007e0d7f0/0x7f4/0x7f8 (quota) and
 *   DAT_fffffe000c5b83b0/0x3b4/0x3b8 (derived quota copies). Reads
 *   DAT_fffffe0007e0c03c (chip id) and DAT_fffffe0007e255f8 (boot-arg enable
 *   bit 4). Kernel deps: FUN_fffffe000c09c084 (DT "/product" lookup),
 *   FUN_fffffe000c09c31c (DT property get), FUN_fffffe000c09cbf0 (boot-arg
 *   getter). Warning: "Globals starting with '_' overlap smaller symbols." */
static int hv_support_init(void)
{
    uint  quota;
    ulong cur_el;
    int   rc;
    int   boot_quota;
    int   prop_size;
    uint *prop_val;
    void *dt_node;

    cur_el = currentel;
    if (((cur_el & 0xc) == 8) && (hv_chip_id >> 0x18 == 0x61)) {
        /* DAT_fffffe0007e0c03c: SoC/chip identifier global; high byte 0x61='a'. */
        if ((hv_chip_id & 0xffe0) == 0x200) {
            /* AVF/Fusion-class product: set feature bits 0x3. */
            hv_features |= 3;   /* DAT_fffffe0007e0d820: hv feature flags */
        }
        quota = hv_chip_id >> 4 & 0xfff;
        if (quota < 0x32 && (1ULL << (quota & 0x3f) & 0x3033f00000000ULL) != 0) {
            /* chip implementer/variant in a supported set: set feature bit 0x4 */
            hv_features |= 4;
        }
        if ((hv_chip_id & 0xffe0) != 0x200) {
            /* Read ISA VM quota from device tree. */
            dt_node = 0;
            prop_val = 0;
            prop_size = 0;
            rc = FUN_fffffe000c09c084(0, "/product", &dt_node); /* DT "/product" node lookup, kernel */
            if ((rc == 1) &&
                (rc = FUN_fffffe000c09c31c(dt_node, "apple-isa-vm-quota",
                                           &prop_val, &prop_size), /* DT property get, kernel */
                 rc == 1) && (prop_size == 4)) {
                quota = *prop_val;
                /* clamp to signed INT_MAX (0x7fffffff) */
                quota = (quota < 0x80000000u) ? quota : 0x7fffffff;
                hv_quota[0] = quota;   /* hv quota */
                hv_quota[1] = quota;
                hv_quota[2] = quota;
                hv_quota_derived[0] = quota;
                hv_quota_derived[1] = quota;
                hv_quota_derived[2] = quota;
            }
            if ((hv_bootarg_flags >> 4 & 1) != 0) {
                /* boot-arg override enabled: read hv_apple_isa_vm_quota */
                boot_quota = 0;
                rc = FUN_fffffe000c09cbf0(hv_bootarg_table + 0x6c,
                                          "hv_apple_isa_vm_quota",
                                          &boot_quota, 4, 0); /* boot-arg getter, kernel */
                if (rc != 0) {
                    hv_quota_derived[0] = boot_quota;
                    hv_quota_derived[1] = boot_quota;
                    hv_quota_derived[2] = boot_quota;
                    hv_quota[0] = boot_quota;
                    hv_quota[1] = boot_quota;
                    hv_quota[2] = boot_quota;
                }
            }
            FUN_fffffe000b987fa8();   /* est. hv_el2_feature_detect */
            return 1;
        }
    }
    return 0;
}

/* ------------------------------------------------------------------ *
 * FUN_fffffe000b987fa8 @ 0xfffffe000b987fa8   (est. hv_el2_feature_detect)
 * Ghidra: void FUN_fffffe000b987fa8(void)
 * EL2 feature / SoC detection. Reads the EL2 feature register (masking out
 * bits 0x0..0x2000 into DAT_fffffe0007e0d800), the main ID registers aidr_el1
 * and id_aa64pfr0/1_el1, and derives three SoC feature flags: the part
 * implementer (aidr bits [16:15]), a "no Level-2 table" indicator from aidr
 * bit 45, and a VMID/EL2-capable bit from id_aa64pfr1[35:32] or
 * id_aa64pfr0[55:52]. The first EL2 read result is discarded.
 * Confidence: high
 * Notes: reads UnkSytemRegRead(3,4,0xc,0xb,1) (discarded) and
 *   UnkSytemRegRead(3,4,0xf,0xc,6) (EL2 feature reg; op1=4 ⇒ EL2, register
 *   identity unverified); aidr_el1, id_aa64pfr0_el1, id_aa64pfr1_el1.
 *   Writes DAT_fffffe0007e0d800 (EL2 features), DAT_fffffe0007e0d818
 *   (implementer), 0x7e0d81c (L2 table flag), 0x7e0d81e (EL2-capable).
 *   Decompiler warning: "Removing unreachable block (ram,0xfffffe000b988028)." */
static void hv_el2_feature_detect(void)
{
    ulong el2_feat;
    ulong id;
    ulong pfr0;
    ulong pfr1;

    UnkSytemRegRead(3, 4, 0xc, 0xb, 1);          /* op1=4 ⇒ EL2; register identity unverified */
    el2_feat = UnkSytemRegRead(3, 4, 0xf, 0xc, 6); /* EL2 feature register; identity unverified */
    hv_el2_features = el2_feat & 0xfffffffffffe13ff; /* EL2 features global */

    id = aidr_el1;
    hv_soc_implementer = (uint)id >> 0xe & 3;  /* SoC implementer field */

    id = aidr_el1;
    hv_soc_no_l2 = (id & 0x2000000000000ULL) == 0; /* L2-table-absent flag */

    pfr1 = id_aa64pfr1_el1;
    pfr0 = id_aa64pfr0_el1;
    if ((pfr1 & 0xf00000000ULL) == 0x200000000ULL ||
        (pfr0 & 0xf00000000000000ULL) == 0x200000000000000ULL) {
        hv_el2_capable = 1;  /* EL2/VMID capable */
    }
}

/* ------------------------------------------------------------------ *
 * FUN_fffffe000b984ed8 @ 0xfffffe000b984ed8   (est. hv_available)
 * Ghidra: void FUN_fffffe000b984ed8(long param_1)
 * Mach-trap entry that dispatches hypervisor operations by command number.
 * Reads the command (param_1+8) and its argument (param_1+0x10); if the
 * hypervisor availability global DAT_fffffe0007e41db0 is clear it returns
 * error 0xfae9400f; otherwise it calls the command's handler through the
 * PTR_FUN_fffffe0007e0d750 table (commands 0xd and 0x12 are reserved NULL
 * entries) and writes the result back to param_1+8. Traces entry (0x10c0015)
 * and exit (0x10c0016) through FUN_fffffe000bd30528 when the trace flag
 * (DAT_fffffe000c68ac90 bit 0) is set.
 * Confidence: medium
 * Notes: dispatches through PTR_FUN_fffffe0007e0d750 (19-entry hv mach-trap
 *   op table; handlers owned by vcpu-core/trap-dispatch trees). Reads
 *   DAT_fffffe0007e41db0 (hv availability). Kernel dep: FUN_fffffe000bd30528
 *   (trace). Error codes -0x516bff1=0xfae9400f (hv unavailable),
 *   -0x516bfff=0xfae94001 (default). Decompiler quirk: the table-index
 *   arithmetic (0x2bad000000000000 OR) is pointer sign-extension noise. */
static void hv_available(long param_1)
{
    long   result;
    ulong  cmd;
    ulong  arg;

    cmd = *(ulong *)(param_1 + 8);
    arg = *(ulong *)(param_1 + 0x10);

    if (((byte)hv_trace_flag & 1) != 0) {
        FUN_fffffe000bd30528(0x10c0015, cmd, arg, 0, 0); /* kernel trace */
    }

    result = -0x516bfff;   /* 0xfae94001 default error */
    if (hv_available_flag == 0) {   /* hv availability global */
        result = -0x516bff1;           /* 0xfae9400f: hypervisor unavailable */
    } else if ((cmd < 0x13 && cmd != 0xd) && cmd != 0x12) {
        /* dispatch through the 19-entry hv operation table at
         * PTR_FUN_fffffe0007e0d750; 0xd/0x12 are the two NULL entries. */
        result = (long)((hv_op_func_t *)(PTR_FUN_fffffe0007e0d750))[cmd](arg);
    }

    *(long *)(param_1 + 8) = result;

    if (((byte)hv_trace_flag & 1) == 0) {
        return;
    }
    FUN_fffffe000bd30528(0x10c0016, result, 0, 0, 0); /* kernel trace */
}
