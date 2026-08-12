/* Recreated from kernelcache.arm64.kc (xnu-12377.121.10 RELEASE_ARM64_T8142, image base fffffe0007004000). Ground truth: Ghidra FUN_ names + addresses; all names are estimates. */

/*
 * hv_entitlements.c — entitlement-gated hypervisor capability reporting.
 *
 * Owned by the entitlements tree.
 *
 * The hypervisor capability trap (FUN_fffffe000b984fd8, est. hv_trap_op_0 /
 * hv_capabilities; trap-dispatch tree) builds a 0x1b3-byte capabilities
 * block and copies it out to the caller. It does so in three steps:
 *   1. FUN_fffffe000b985ae4 (est. hv_entitlement_access_level, owned by the
 *      vmapple-ipc tree, decompiled in hv_vmapple.c) returns the calling
 *      task's hypervisor entitlement tier (0/1/3/4) from the three strings
 *      com.apple.security.hypervisor / com.apple.private.hypervisor.vmapple /
 *      com.apple.private.hypervisor via the credential ops table
 *      DAT_fffffe0007e93310 slot +0x1c0.
 *   2. FUN_fffffe000b987d9c (this file, est. hv_caps_feature_mask) folds that
 *      tier into a 19-qword feature-mask block.
 *   3. FUN_fffffe000b988038 (this file, est. hv_caps_cpu_report) fills the
 *      CPU/memory feature report (cache geometry + ID registers) into the
 *      same block.
 * hv_vm_create (FUN_fffffe000b985588, trap-dispatch) also calls
 * FUN_fffffe000b987d9c with a tier value.
 */

#include "hv_entitlements.h"
#include "hv_support.h"      /* DAT_fffffe0007e0d7f0 (quota), DAT_fffffe0007e41db0 */
#include "hv_internal.h"     /* per_cpu_base, DAT_fffffe0007e0d818, PTR_PTR_... */

/* ------------------------------------------------------------------ *
 * FUN_fffffe000b985ae4 @ 0xfffffe000b985ae4   (est. hv_entitlement_tier)
 * Ghidra: undefined1 FUN_fffffe000b985ae4(void)
 * Determines the calling thread's hypervisor entitlement tier by probing the
 * three entitlement strings through the shared credential ops table. Returns
 * 0 (no entitlement), 1 (com.apple.security.hypervisor), 3 (the vmapple or
 * private-hypervisor entitlement is present) or 4 (private-hypervisor is
 * present AND the boot-arg enable bit DAT_fffffe0007e255f8 & 0x1010 is set).
 * Called by op-table index 0 (FUN_fffffe000b984fd8) to gate the capabilities
 * report, and is the tier input to FUN_fffffe000b987d9c.
 * Confidence: high
 * Notes: resolves the current task via per_cpu_base(FUN_fffffe000b866ec4) and
 *   validates it via current_task (FUN_fffffe000b8663e8, recreated in
 *   hv_kernel_glue.c); entitlement dispatch is
 *   `(**(code **)(DAT_fffffe0007e93310 + 0x1c0))(cred, string)`. Reads
 *   DAT_fffffe0007e255f8 (boot-arg enable flags). Ground truth FUN_ + addr
 *   verified; tier values are inferred from the three string probes. */
uint8_t hv_entitlement_tier(void)
{
	uint8_t tier;
	int     rc;
	long    proc;
	long    cred;
	bool    has_security;

	proc = (long)per_cpu_base((uint64_t)tpidr_el1); /* FUN_fffffe000b866ec4: thread->proc (kernel dep) */
	if (proc == 0 || (cred = current_task((void *)proc), cred == 0)) {
		has_security = false;
	} else {
		rc = ((int (*)(long, const char *))DAT_fffffe0007e93310[0x38])(cred,
		                                                              "com.apple.security.hypervisor");
		has_security = (rc == 0);
	}
	tier = has_security;

	if (proc != 0 && (cred = current_task((void *)proc), cred != 0)) {
		rc = ((int (*)(long, const char *))DAT_fffffe0007e93310[0x38])(cred,
		                                                              "com.apple.private.hypervisor.vmapple");
		tier = 3;
		if (rc != 0)
			tier = has_security;
	}

	if (proc != 0 && (cred = current_task((void *)proc), cred != 0) &&
	    ((rc = ((int (*)(long, const char *))DAT_fffffe0007e93310[0x38])(cred,
	                                                                    "com.apple.private.hypervisor"),
	      rc == 0)) && ((tier = 3), (DAT_fffffe0007e255f8 & 0x1010) != 0)) {
		tier = 4;
	}
	return tier;
}

/* ------------------------------------------------------------------ *
 * FUN_fffffe000b987d9c @ 0xfffffe000b987d9c   (est. hv_caps_feature_mask)
 * Ghidra: void FUN_fffffe000b987d9c(ulong *param_1, uint param_2)
 * Fills a 19-qword (0x98-byte) feature-mask block at param_1 with the
 * hypervisor capability bits that the caller (param_2 = entitlement tier from
 * FUN_fffffe000b985ae4) is entitled to. For tiers < 2 it additionally probes
 * the "com.apple.private.virtualization" entitlement to decide whether to set
 * the extended (0x202) capability; tiers 2..3 select progressively richer
 * default masks. Clears a CPU-feature bit when DAT_fffffe0007e0d820 bit 1 is
 * set. Called by op-table index 0 and hv_vm_create.
 * Confidence: medium
 * Notes: reads DAT_fffffe0007e0d818 (SoC implementer) to clear a feature bit
 *   (uVar9 = 0 when (DAT-3) > 0xfffffffd) and DAT_fffffe0007e0d820 (hv feature
 *   flags). Entitlement dispatch via DAT_fffffe0007e93310 + 0x1c0; current
 *   task via per_cpu_base(FUN_fffffe000b866ec4) + current_task (FUN_fffffe000b8663e8, recreated in hv_kernel_glue.c). */
void hv_caps_feature_mask(ulong *mask, uint tier)
{
	ulong uVar9, uVar4, uVar5, uVar7, uVar6, uVar8;
	long  lVar3;
	int   iVar2;

	mask[2] = 0x30000200000;
	mask[1] = 0xf8202c0077dfd1c0;
	mask[0] = 0x403c8028223b;
	mask[5] = 0x1000000008006c01;
	mask[8] = 0x200;
	mask[4] = 0x100000200000000;
	mask[3] = 0x1e1f000018257c03;
	mask[0xb] = 0x1c00;
	mask[7] = 0x100;
	mask[6] = 0x8000e00;
	mask[10] = 0xffffffffffffc3ff;
	mask[9] = 0x3c00;
	mask[0xe] = 0;
	mask[0xd] = 0x20e12;
	mask[0xc] = 0;
	mask[0x10] = 0x20e12;
	mask[0xf] = 0;
	uVar9 = 0x4000000000000000;
	if (0xfffffffd < DAT_fffffe0007e0d818 - 3U)   /* DAT_7e0d818: SoC implementer */
		uVar9 = 0;
	mask[0x11] = 0;
	mask[0x12] = uVar9;

	if (tier < 2) {
		uVar9 = 2;
		mask[0xd] = 2;
		lVar3 = (long)per_cpu_base((uint64_t)tpidr_el1);
		if (lVar3 != 0) {
			lVar3 = current_task((void *)lVar3);
			if (lVar3 == 0) {
				uVar9 = 2;
			} else {
				iVar2 = ((int (*)(long, const char *))DAT_fffffe0007e93310[0x38])(lVar3,
				                                                                "com.apple.private.virtualization");
				uVar9 = 0x202;
				if (iVar2 != 0)
					uVar9 = 2;
			}
		}
		mask[0x10] = uVar9;
		uVar9 = mask[0];
		uVar4 = mask[1];
		uVar5 = mask[3];
		uVar7 = mask[2] | 0x100000;
		uVar6 = mask[0x12] | 0xdf80000000000000;
		uVar8 = mask[4] & 0xfffffffdffffffff;
	} else {
		uVar9 = 0x403c8028223b;
		uVar7 = uVar9;
		if (3 < tier)
			goto build;
		uVar4 = 0xf8202c0077dfd1c0;
		uVar7 = 0x30000300000;
		uVar5 = 0x1e1f000018257c03;
		uVar6 = 0xdd80000000000000;
		uVar8 = 0x100000000000000;
	}
	mask[0] = uVar9 | 0x100000;
	mask[1] = uVar4 & 0xffffffffffefffff;
	mask[0x12] = uVar6;
	mask[2] = uVar7;
	mask[3] = uVar5 | 0x204008300;
	mask[4] = uVar8;
	mask[5] = 0;
	uVar7 = uVar9 | 0x100000;
	if (1 < tier) {
		mask[0] = uVar9 & 0xffffffffffefffff;
		mask[1] = uVar4 | 0x100000;
		mask[3] = uVar5 | 0x207088310;
		mask[5] = 1;
		mask[0x12] = uVar6 & 0xefffffffffffffff;
		uVar7 = uVar9 & 0xffffffffffefffff;
	}
build:
	if ((DAT_fffffe0007e0d820 >> 1 & 1) != 0)   /* DAT_7e0d820: hv feature flags, bit 1 */
		mask[0] = uVar7 & 0xfffffffffff7ffff;
}

/* ------------------------------------------------------------------ *
 * FUN_fffffe000b988038 @ 0xfffffe000b988038   (est. hv_caps_cpu_report)
 * Ghidra: void FUN_fffffe000b988038(long param_1, undefined8 *param_2)
 * Fills the hv capabilities CPU/memory report block at param_2 with feature
 * and cache information: the cache block-size shift for 0x1000/0x4000 page
 * sizes, CTR/DCZID/ID_AA64* read-only registers, and the cache-geometry data
 * selected by a population-count decision over DAT_fffffe0007e0c6ac. Reads a
 * couple of raw feature words out of param_1 (the tier block). Ends in a
 * halt_baddata() (decompiler truncation).
 * Confidence: medium
 * Notes: reads ctr_el0, dczid_el0, id_aa64dfr0/1_el1, id_aa64isar0/1_el1,
 *   id_aa64mmfr0/1_el1, id_aa64pfr0/1_el1, UnkSytemRegRead(3,0,0,7,2) and
 *   UnkSytemRegRead(3,0,0,4,5)/(3,0,0,4,4). Cache geometry via
 *   FUN_fffffe000b95fe60 (est. cache_type_lookup, shared kernel dep,
 *   universal cache-topology primitive, extern in hv_kernel_glue.c);
 *   page-size tables PTR_PTR_fffffe000c5b3f58/60/68. DAT_fffffe0007e0c6ac is a
 *   cache/topology flag word; DAT_fffffe0007e0d820 bit 2 feeds byte +0x34.
 *   Decompiler warning: "Control flow encountered bad instruction data". */
void hv_caps_cpu_report(long tier_block, ulong *report)
{
	ulong uVar6;
	ulong uVar3;
	int   iVar1, iVar8, iVar7;
	byte  uVar4;
	long *puVar5;
	long *puVar9;
	long  lVar10;

	report[5] = 0; report[4] = 0; report[7] = 0; report[6] = 0;
	report[1] = 0; report[0] = 0; report[3] = 0; report[2] = 0;
	report[8]  = *(ulong *)(tier_block + 0x10) | *(ulong *)(tier_block + 8);
	report[9]  = *(ulong *)(tier_block + 0x28) | *(ulong *)(tier_block + 0x20);
	report[0xb] = 0x300;
	report[0xa] = 0x80300000;
	report[0xd] = 1;
	report[0xc] = 0xffffffffffffdfff;
	report[0xf] = 0xffffffffffffffff;
	report[0xe] = 1;
	report[0x11] = 0xffffffffffffffff;
	report[0x10] = 0xffffffffffffffff;
	report[0x13] = 0xffffffffffffffff;
	report[0x12] = 0xffffffffffffffff;
	report[0x14] = 0x1ec00;
	report[0x15] = *(ulong *)(tier_block + 0x80);
	*(byte *)(report + 0x34) = DAT_fffffe0007e0d820 >> 2 & 1;   /* DAT_7e0d820 bit 2 */

	puVar5 = PTR_PTR_fffffe000c5b3f68;
	puVar9 = PTR_PTR_fffffe000c5b3f68;
	if ((*(long *)(PTR_PTR_fffffe000c5b3f68 + 0x58) == 0x1000) ||
	    (puVar9 = PTR_PTR_fffffe000c5b3f60, *(long *)(PTR_PTR_fffffe000c5b3f60 + 0x58) == 0x1000) ||
	    (puVar9 = PTR_PTR_fffffe000c5b3f58, *(long *)(PTR_PTR_fffffe000c5b3f58 + 0x58) == 0x1000)) {
		lVar10 = 0x40 - (*(ulong *)(puVar9 + 0x50) & 0x3f);
	} else {
		lVar10 = 0;
	}
	*(long *)((long)report + 0x1a1) = lVar10;   /* 4 KB cache block shift */

	if ((*(long *)(puVar5 + 0x58) == 0x4000) ||
	    (puVar5 = PTR_PTR_fffffe000c5b3f60, *(long *)(PTR_PTR_fffffe000c5b3f60 + 0x58) == 0x4000) ||
	    (puVar5 = PTR_PTR_fffffe000c5b3f58, *(long *)(PTR_PTR_fffffe000c5b3f58 + 0x58) == 0x4000)) {
		lVar10 = 0x40 - (*(ulong *)(puVar5 + 0x50) & 0x3f);
	} else {
		lVar10 = 0;
	}
	*(long *)((long)report + 0x1a9) = lVar10;   /* 16 KB cache block shift */

	uVar6 = ctr_el0;
	uVar3 = dczid_el0;
	report[0x16] = uVar6;
	report[0x17] = uVar3 & 0xffffffffffffffef;
	iVar1 = POPCOUNT(DAT_fffffe0007e0c6ac) + -1;
	if ((DAT_fffffe0007e0c6ac & 1) == 0) {
		iVar8 = 0;
		iVar7 = 0;
joined:
		if ((DAT_fffffe0007e0c6ac >> 2 & 1) != 0) {
			if (iVar7 == iVar1) {
				uVar4 = 2;
				goto select;
			}
			iVar8 = iVar7 + 1;
		}
		if (((DAT_fffffe0007e0c6ac >> 1 & 1) != 0) &&
		    ((uVar4 = iVar8 == iVar1, (bool)uVar4 || ((DAT_fffffe0007e0c6ac & 1) == 0))))
			goto select;
	} else if (POPCOUNT(DAT_fffffe0007e0c6ac) != 1) {
		iVar8 = 1;
		iVar7 = 1;
		goto joined;
	}
	uVar4 = 0;
select:
	lVar10 = (long)FUN_fffffe000b95fe60(uVar4);   /* est. cache_type_lookup (kernel dep) */
	report[0x18] = (ulong)*(uint *)(lVar10 + 0x30);
	report[0x19] = *(ulong *)(lVar10 + 0x38);
	report[0x21] = *(ulong *)(lVar10 + 0x70);
	report[0x1a] = *(ulong *)(lVar10 + 0x40);
	report[0x22] = *(ulong *)(lVar10 + 0x78);
	report[0x1b] = *(ulong *)(lVar10 + 0x48);
	report[0x23] = *(ulong *)(lVar10 + 0x80);
	report[0x1c] = *(ulong *)(lVar10 + 0x50);
	report[0x24] = *(ulong *)(lVar10 + 0x88);
	report[0x1d] = *(ulong *)(lVar10 + 0x58);
	report[0x25] = *(ulong *)(lVar10 + 0x90);
	report[0x1e] = *(ulong *)(lVar10 + 0x60);
	report[0x26] = *(ulong *)(lVar10 + 0x98);
	report[0x1f] = *(ulong *)(lVar10 + 0x68);
	uVar6 = *(ulong *)(lVar10 + 0xa0);
	report[0x20] = 0;
	report[0x27] = uVar6;
	report[0x28] = 0;

	report[0x29] = id_aa64dfr0_el1;
	report[0x2a] = id_aa64dfr1_el1;
	report[0x2b] = id_aa64isar0_el1;
	report[0x2c] = id_aa64isar1_el1;
	report[0x2d] = id_aa64mmfr0_el1;
	report[0x2e] = id_aa64mmfr1_el1;
	report[0x2f] = UnkSytemRegRead(3,0,0,7,2);   /* op1=0, CRn=7, CRm=2; register identity unverified */
	report[0x30] = id_aa64pfr0_el1;
	report[0x31] = id_aa64pfr1_el1;
	report[0x32] = UnkSytemRegRead(3,0,0,4,5);   /* op1=0, CRn=4, CRm=5; identity unverified */
	report[0x33] = UnkSytemRegRead(3,0,0,4,4);   /* op1=0, CRn=4, CRm=4; identity unverified */

	/* WARNING: Bad instruction - Truncating control flow here */
	halt_baddata();   /* est. hard halt; Ghidra truncated control flow */
}
