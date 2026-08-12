/* Recreated from kernelcache.arm64.kc (xnu-12377.121.10 RELEASE_ARM64_T8142, image base fffffe0007004000). Ground truth: Ghidra FUN_ names + addresses; all names are estimates. */
#include "hv_compat.h"

/*
 * hv_entitlements.c — entitlement-gated hypervisor capability reporting.
 *
 * Owned by the entitlements tree.
 *
 * The hypervisor capability trap (hv_capabilities, est. hv_trap_op_0 /
 * hv_capabilities; trap-dispatch tree) builds a 0x1b3-byte capabilities
 * block and copies it out to the caller. It does so in three steps:
 *   1. hv_entitlement_tier (est. hv_entitlement_access_level, owned by the
 *      vmapple-ipc tree, decompiled in hv_vmapple.c) returns the calling
 *      task's hypervisor entitlement tier (0/1/3/4) from the three strings
 *      com.apple.security.hypervisor / com.apple.private.hypervisor.vmapple /
 *      com.apple.private.hypervisor via the credential ops table
 *      DAT_fffffe0007e93310 slot +0x1c0.
 *   2. hv_caps_feature_mask (this file, est. hv_caps_feature_mask) folds that
 *      tier into a 19-qword feature-mask block.
 *   3. hv_caps_cpu_report (this file, est. hv_caps_cpu_report) fills the
 *      CPU/memory feature report (cache geometry + ID registers) into the
 *      same block.
 * hv_vm_create (hv_vm_create, trap-dispatch) also calls
 * hv_caps_feature_mask with a tier value.
 */

#include "hv_entitlements.h"
#include "hv_support.h"      /* DAT_fffffe0007e0d7f0 (quota), DAT_fffffe0007e41db0 */
#include "hv_internal.h"     /* per_cpu_base, DAT_fffffe0007e0d818, PTR_PTR_... */

/* ------------------------------------------------------------------ *
 * hv_entitlement_tier @ 0xfffffe000b985ae4   (est. hv_entitlement_tier)
 * Ghidra: undefined1 hv_entitlement_tier(void)
 * Determines the calling thread's hypervisor entitlement tier by probing the
 * three entitlement strings through the shared credential ops table. Returns
 * 0 (no entitlement), 1 (com.apple.security.hypervisor), 3 (the vmapple or
 * private-hypervisor entitlement is present) or 4 (private-hypervisor is
 * present AND the boot-arg enable bit DAT_fffffe0007e255f8 & 0x1010 is set).
 * Called by op-table index 0 (hv_capabilities) to gate the capabilities
 * report, and is the tier input to hv_caps_feature_mask.
 * Confidence: high
 * Notes: resolves the current task via per_cpu_base(current_cpu_datap) and
 *   validates it via current_task (current_task, recreated in
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
	if (proc == 0 || (cred = (long)current_task((void *)proc), cred == 0)) {
		has_security = false;
	} else {
		rc = ((int (*)(long, const char *))cred_ops[0x38])(cred,
		                                                  "com.apple.security.hypervisor");   /* DAT_fffffe0007e93310 */
		has_security = (rc == 0);
	}
	tier = has_security;

		if (proc != 0 && (cred = (long)current_task((void *)proc), cred != 0)) {
			rc = ((int (*)(long, const char *))cred_ops[0x38])(cred,
			                                                  "com.apple.private.hypervisor.vmapple");
		tier = 3;
		if (rc != 0)
			tier = has_security;
	}

	if (proc != 0 && (cred = (long)current_task((void *)proc), cred != 0) &&
	    ((rc = ((int (*)(long, const char *))cred_ops[0x38])(cred,
	                                                        "com.apple.private.hypervisor"),
	      rc == 0)) && ((tier = 3), (hv_bootarg_flags & 0x1010) != 0)) {   /* DAT_fffffe0007e255f8 */
		tier = 4;
	}
	return tier;
}

/* ------------------------------------------------------------------ *
 * hv_caps_feature_mask @ 0xfffffe000b987d9c   (est. hv_caps_feature_mask)
 * Ghidra: void hv_caps_feature_mask(ulong *param_1, uint param_2)
 * Fills a 19-qword (0x98-byte) feature-mask block at param_1 with the
 * hypervisor capability bits that the caller (param_2 = entitlement tier from
 * hv_entitlement_tier) is entitled to. For tiers < 2 it additionally probes
 * the "com.apple.private.virtualization" entitlement to decide whether to set
 * the extended (0x202) capability; tiers 2..3 select progressively richer
 * default masks. Clears a CPU-feature bit when DAT_fffffe0007e0d820 bit 1 is
 * set. Called by op-table index 0 and hv_vm_create.
 * Confidence: medium
 * Notes: reads DAT_fffffe0007e0d818 (SoC implementer) to clear a feature bit
 *   (uVar9 = 0 when (DAT-3) > 0xfffffffd) and DAT_fffffe0007e0d820 (hv feature
 *   flags). Entitlement dispatch via DAT_fffffe0007e93310 + 0x1c0; current
 *   task via per_cpu_base(current_cpu_datap) + current_task (current_task, recreated in hv_kernel_glue.c). */
/* Fixed capability feature-mask literals for hv_caps_feature_mask().
 * HV_CAP_MASK_<n> is the default mask stored at mask[n]. Index 0x12 (18) is
 * computed at runtime (SoC-dependent) and stays a literal. */
#define HV_CAP_MASK_0   0x403c8028223b
#define HV_CAP_MASK_1   0xf8202c0077dfd1c0
#define HV_CAP_MASK_2   0x30000200000
#define HV_CAP_MASK_3   0x1e1f000018257c03
#define HV_CAP_MASK_4   0x100000200000000
#define HV_CAP_MASK_5   0x1000000008006c01
#define HV_CAP_MASK_6   0x8000e00
#define HV_CAP_MASK_7   0x100
#define HV_CAP_MASK_8   0x200
#define HV_CAP_MASK_9   0x3c00
#define HV_CAP_MASK_10  0xffffffffffffc3ff
#define HV_CAP_MASK_11  0x1c00
#define HV_CAP_MASK_12  0
#define HV_CAP_MASK_13  0x20e12
#define HV_CAP_MASK_14  0
#define HV_CAP_MASK_15  0
#define HV_CAP_MASK_16  0x20e12
#define HV_CAP_MASK_17  0

void hv_caps_feature_mask(uint64_t *mask, uint32_t tier)
{
	ulong feat, cap4, cap5, cap7, cap6, cap8;
	long  task;
	int   ent_rc;

	mask[2] = HV_CAP_MASK_2;
	mask[1] = HV_CAP_MASK_1;
	mask[0] = HV_CAP_MASK_0;
	mask[5] = HV_CAP_MASK_5;
	mask[8] = HV_CAP_MASK_8;
	mask[4] = HV_CAP_MASK_4;
	mask[3] = HV_CAP_MASK_3;
	mask[0xb] = HV_CAP_MASK_11;
	mask[7] = HV_CAP_MASK_7;
	mask[6] = HV_CAP_MASK_6;
	mask[10] = HV_CAP_MASK_10;
	mask[9] = HV_CAP_MASK_9;
	mask[0xe] = HV_CAP_MASK_14;
	mask[0xd] = HV_CAP_MASK_13;
	mask[0xc] = HV_CAP_MASK_12;
	mask[0x10] = HV_CAP_MASK_16;
	mask[0xf] = HV_CAP_MASK_15;
	feat = 0x4000000000000000;
	if (0xfffffffd < hv_soc_implementer - 3U)   /* DAT_7e0d818: SoC implementer */
		feat = 0;
	mask[0x11] = HV_CAP_MASK_17;
	mask[0x12] = feat;

	if (tier < 2) {
		feat = 2;
		mask[0xd] = 2;
		task = (long)per_cpu_base((uint64_t)tpidr_el1);
		if (task != 0) {
                        task = (long)current_task((void *)task);
			if (task == 0) {
				feat = 2;
			} else {
				ent_rc = ((int (*)(long, const char *))cred_ops[0x38])(task,
				                                                       "com.apple.private.virtualization");   /* DAT_fffffe0007e93310 */
				feat = 0x202;
				if (ent_rc != 0)
					feat = 2;
			}
		}
		mask[0x10] = feat;
		feat = mask[0];
		cap4 = mask[1];
		cap5 = mask[3];
		cap7 = mask[2] | 0x100000;
		cap6 = mask[0x12] | 0xdf80000000000000;
		cap8 = mask[4] & 0xfffffffdffffffff;
	} else {
		feat = 0x403c8028223b;
		cap7 = feat;
		if (3 < tier)
			goto build;
		cap4 = 0xf8202c0077dfd1c0;
		cap7 = 0x30000300000;
		cap5 = 0x1e1f000018257c03;
		cap6 = 0xdd80000000000000;
		cap8 = 0x100000000000000;
	}
	mask[0] = feat | 0x100000;
	mask[1] = cap4 & 0xffffffffffefffff;
	mask[0x12] = cap6;
	mask[2] = cap7;
	mask[3] = cap5 | 0x204008300;
	mask[4] = cap8;
	mask[5] = 0;
	cap7 = feat | 0x100000;
	if (1 < tier) {
		mask[0] = feat & 0xffffffffffefffff;
		mask[1] = cap4 | 0x100000;
		mask[3] = cap5 | 0x207088310;
		mask[5] = 1;
		mask[0x12] = cap6 & 0xefffffffffffffff;
		cap7 = feat & 0xffffffffffefffff;
	}
build:
	if ((hv_features >> 1 & 1) != 0)   /* DAT_7e0d820: hv feature flags, bit 1 */
		mask[0] = cap7 & 0xfffffffffff7ffff;
}

/* ------------------------------------------------------------------ *
 * hv_caps_cpu_report @ 0xfffffe000b988038   (est. hv_caps_cpu_report)
 * Ghidra: void hv_caps_cpu_report(long param_1, undefined8 *param_2)
 * Fills the hv capabilities CPU/memory report block at param_2 with feature
 * and cache information: the cache block-size shift for 0x1000/0x4000 page
 * sizes, CTR/DCZID/ID_AA64* read-only registers, and the cache-geometry data
 * selected by a population-count decision over DAT_fffffe0007e0c6ac. Reads a
 * couple of raw feature words out of param_1 (the tier block). Ends with
 * the ID_AA64* register word dump; the epilogue is a clean return
 * (disassembly b988038-b9882a8; the decompiler's "Control flow encountered
 * bad instruction data" was a false alarm on the sysreg read at +0x268).
 * Confidence: high (full disassembly verified)
 * Notes: reads ctr_el0, dczid_el0, id_aa64dfr0/1_el1, id_aa64isar0/1_el1,
 *   id_aa64mmfr0/1_el1, id_aa64pfr0/1_el1, UnkSytemRegRead(3,0,0,7,2) and
 *   UnkSytemRegRead(3,0,0,4,5)/(3,0,0,4,4). Cache geometry via
 *   cache_type_lookup (est. cache_type_lookup, shared kernel dep,
 *   universal cache-topology primitive, extern in hv_kernel_glue.c);
 *   page-size tables PTR_PTR_fffffe000c5b3f58/60/68. DAT_fffffe0007e0c6ac is a
 *   cache/topology flag word; DAT_fffffe0007e0d820 bit 2 feeds byte +0x34.
 *   Decompiler warning: "Control flow encountered bad instruction data". */
void hv_caps_cpu_report(int64_t *tier_block, uint64_t *report)
{
	ulong ctr;
	ulong dczid;
	int   popcnt, sel_a, sel_b;
	byte  sel;
	uint64_t *psz_tbl;
	uint64_t *psz_tbl_b;
	long  cache_desc;

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
	*(byte *)(report + 0x34) = hv_features >> 2 & 1;   /* DAT_7e0d820 bit 2 */

	psz_tbl = hv_page_size_table_3;   /* PTR_PTR_fffffe000c5b3f68 */
	psz_tbl_b = hv_page_size_table_3;
	if ((*(long *)(hv_page_size_table_3 + 0x58) == 0x1000) ||
	    (psz_tbl_b = hv_page_size_table_2, *(long *)(hv_page_size_table_2 + 0x58) == 0x1000) ||
	    (psz_tbl_b = hv_page_size_table_1, *(long *)(hv_page_size_table_1 + 0x58) == 0x1000)) {
		cache_desc = 0x40 - (*(ulong *)(psz_tbl_b + 0x50) & 0x3f);
	} else {
		cache_desc = 0;
	}
	*(long *)((long)report + 0x1a1) = cache_desc;   /* 4 KB cache block shift */

	if ((*(long *)(psz_tbl + 0x58) == 0x4000) ||
	    (psz_tbl = hv_page_size_table_2, *(long *)(hv_page_size_table_2 + 0x58) == 0x4000) ||
	    (psz_tbl = hv_page_size_table_1, *(long *)(hv_page_size_table_1 + 0x58) == 0x4000)) {
		cache_desc = 0x40 - (*(ulong *)(psz_tbl + 0x50) & 0x3f);
	} else {
		cache_desc = 0;
	}
	*(long *)((long)report + 0x1a9) = cache_desc;   /* 16 KB cache block shift */

	ctr = ctr_el0;
	dczid = dczid_el0;
	report[0x16] = ctr;
	report[0x17] = dczid & 0xffffffffffffffef;
	popcnt = POPCOUNT(hv_cache_flags) + -1;   /* DAT_fffffe0007e0c6ac */
	if ((hv_cache_flags & 1) == 0) {
		sel_a = 0;
		sel_b = 0;
joined:
		if ((hv_cache_flags >> 2 & 1) != 0) {
			if (sel_b == popcnt) {
				sel = 2;
				goto select;
			}
			sel_a = sel_b + 1;
		}
		if (((hv_cache_flags >> 1 & 1) != 0) &&
		    ((sel = sel_a == popcnt, (bool)sel || ((hv_cache_flags & 1) == 0))))
			goto select;
	} else if (POPCOUNT(hv_cache_flags) != 1) {
		sel_a = 1;
		sel_b = 1;
		goto joined;
	}
	sel = 0;
select:
	cache_desc = (long)cache_type_lookup(sel);   /* est. cache_type_lookup (kernel dep) */
	report[0x18] = (ulong)*(uint *)(cache_desc + 0x30);
	report[0x19] = *(ulong *)(cache_desc + 0x38);
	report[0x21] = *(ulong *)(cache_desc + 0x70);
	report[0x1a] = *(ulong *)(cache_desc + 0x40);
	report[0x22] = *(ulong *)(cache_desc + 0x78);
	report[0x1b] = *(ulong *)(cache_desc + 0x48);
	report[0x23] = *(ulong *)(cache_desc + 0x80);
	report[0x1c] = *(ulong *)(cache_desc + 0x50);
	report[0x24] = *(ulong *)(cache_desc + 0x88);
	report[0x1d] = *(ulong *)(cache_desc + 0x58);
	report[0x25] = *(ulong *)(cache_desc + 0x90);
	report[0x1e] = *(ulong *)(cache_desc + 0x60);
	report[0x26] = *(ulong *)(cache_desc + 0x98);
	report[0x1f] = *(ulong *)(cache_desc + 0x68);
	ctr = *(ulong *)(cache_desc + 0xa0);
	report[0x20] = 0;
	report[0x27] = ctr;
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

	/* Function ends here. The decompiler's "Bad instruction - Truncating
	 * control flow" was a false alarm on the sysreg read at +0x268
	 * (sreg(3,0,c0x0,c0x7,0x2)); the full disassembly (b988038-b9882a8)
	 * shows a normal epilogue after these stores. No halt. */
}
