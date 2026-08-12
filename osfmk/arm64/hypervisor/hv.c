/* Recreated from kernelcache.arm64.kc (xnu-12377.121.10 RELEASE_ARM64_T8142, image base fffffe0007004000). Ground truth: Ghidra FUN_ names + addresses; all names are estimates. */

/*
 * hv.c — Hypervisor.framework mach-trap handlers.
 *
 * Owned by the trap-dispatch tree.
 *
 * ===========================================================================
 * TRAP DISPATCH RECORD LAYOUT  (learned from FUN_fffffe000bda3ca8 @ 0xfffffe000bda3ca8,
 *   est. trap_arg_munger — shared kernel, decompiled once here, NOT recreated)
 * ===========================================================================
 * The mach-trap argument munger is registered by the hv_support / hv_disable
 * boot-arg descriptors and the VM-name table (see docs/chain-map.md). It
 * consumes a trap dispatch record at param_4 with these verified offsets:
 *
 *   record + 0x10   copyin_flag  : bool; if nonzero the 4-byte user arg is
 *                                  fetched through the copyin/copyout helper.
 *   record + 0x28   copy         : copyin/copyout helper fn; called as
 *                                  copy(record, buf, 4) to move the arg
 *                                  between kernel and user address space.
 *   record + 0x30   copyout_flag : bool; nonzero => the handler produces a
 *                                  result value that must be copied back out.
 *   record + 0x38   arg_size     : 8 or 4; selects the handler call shape
 *                                  below (8 => value held in a 64-bit local,
 *                                  4 => written straight into the caller's
 *                                  32-bit slot).
 *   record + 0x48   handler      : called as handler(record, &value, arg_size).
 *
 * Munger logic (FUN_fffffe000bda3ca8): copy in (if copyin_flag) into a local,
 * then if the caller wants a result AND copyout_flag is set, invoke the
 * handler and return its code; on an 8-byte arg the result is range-checked to
 * fit a 32-bit int (else error 0x22). Shared dispatch machinery — not hv code.
 *
 * Name/registration table @ 0xfffffe0007e35080 — ENUMERATED EXHAUSTIVELY
 * (windows 0x7e35080–0x7e35800, 256 B each). This is a kernel VM-statistics /
 * boot-arg name table, NOT a mach trap table. Record fields confirmed from
 * FUN_fffffe000be39fd0's entry: name pointer at record+0x08, handler pointer at
 * record+0x10 (other records use a larger 0x50-byte form with name at +0x18 and
 * handler at +0x20). Classification of every handler pointer found:
 *   - FUN_fffffe000be39fd0  (name "hv_vmm_present" @ 0x70c592c) — HV. The ONLY
 *     hypervisor entry in the entire region.
 *   - FUN_fffffe000bda3ca8 / FUN_fffffe000bda45c0 — shared arg mungers
 *     (bda45c0 is a sibling munger, body 0x7e0d…); non-hv.
 *   - FUN_fffffe000be3b6f8 / be3b784 / be3b80c / be3b8c8 and FUN_fffffe000bda5734
 *     — VM statistics handlers; names are VM stats boot-args ("global_enable",
 *     "local_enable", "fault_busy_retry_count", "self_region_footprint",
 *     "self_region_page_size", "self_region_info_flags", "mem_entry_wimg_non_writable",
 *     "lock_contention", "Number of VM fault operations … busy page"). NON-hv.
 *   No other hypervisor handler exists in this table.
 *
 * Hypervisor op table PTR_FUN_fffffe0007e0d750 @ 0xfffffe0007e0d750 — VERIFIED
 * INDEX BY INDEX (read 160 B = 19 * 8 B pointers). This is the real hv
 * mach-trap dispatch table, driven by FUN_fffffe000b984ed8 (est. hv_available /
 * hv_vmm_present dispatcher, support-init tree) on cmd = args+8:
 *   idx0  b984fd8  hv_capabilities      idx10 b98e488 hv_trap_op_10 (unidentified)
 *   idx1  b985588  hv_vm_create         idx11 b986e50 (vcpu-core)
 *   idx2  b985bf0  hv_vm_destroy        idx12 b986da4 hv_vm_map_shared
 *   idx3  b986898  hv_vm_map            idx13 NULL
 *   idx4  b986d84  hv_vm_protect (stub) idx14 b986f1c hv_vm_set_trap_debug
 *   idx5  b986d94  hv_vm_unmap          idx15 b98e788 hv_trap_op_15 (unidentified)
 *   idx6  b989040  (vcpu-core)          idx16 b98e964 hv_trap_op_16 (unidentified)
 *   idx7  b9897bc  hv_vcpu_destroy_trap  idx17 b986ff4 hv_vm_map_region
 *   idx8  b9899b0  hv_vcpu_run_trap      idx18 NULL
 *   idx9  b989a44  (vcpu-core hub)
 * Indexes 6/9/11 are owned by the vcpu-core tree (b989040/b989a44/b986e50);
 * 13 and 18 are NULL; 0xd (=13) unavail → 0xfae9400f, default → 0xfae94001.
 *
 * NAME MATCHING (this batch): idx0 hv_capabilities (435-byte feature/CPU-ID
 * report, entitlement-gated); idx4 hv_vm_protect (verified: stub sets
 * op=1,mode=0 -> protect core b8a8078); idx12 hv_vm_map_shared (map guest
 * memory + return handle via hv_vcpu_map_memory b9866d0); idx14
 * hv_vm_set_trap_debug (per-vm debug-reg slot 0..9 via b954160, which panics
 * on "debug exceptions enabled in kernel mode"). idx10/15/16 remain
 * hv_trap_op_N (unidentified): idx10 = per-CPU vcpu-slot flush (bitmask);
 * idx15 = guest SVCR_EL2 streaming-SVE mode select; idx16 = SoC-feature-gated
 * hv_el2_pt_alloc. See each function's header + docs/chain-map.md.
 * The remaining 14 are reconstructed in this file.
 * ===========================================================================
 */

#include "hv.h"
#include "hv_internal.h"

/* -------------------------------------------------------------------------
 * FUN_fffffe000be39fd0 @ 0xfffffe000be39fd0  (est. hv_vmm_present)
 * Ghidra: void FUN_fffffe000be39fd0(void)   [uses in_x3 = trap record]
 * Reads the "vmm-present" boot property into a 4-byte local, normalizes it to
 * 0/1, and copies that result out to the caller through the trap record's
 * copyin/copyout helper at record+0x28. This is the hv_vmm_present mach trap
 * used by callers to query whether a hypervisor VM is configured.
 * Confidence: high
 * Notes: calls FUN_fffffe000bf77834("vmm-present",&local,4) (kernel boot prop
 *   getter, stubbed); copies via (**(code **)(in_x3 + 0x28))(in_x3,&local,4).
 *   Decompiler declared void return; the trap handler realistically returns
 *   the copyout result (kept void to match Ghidra).
 * ------------------------------------------------------------------------- */
void
hv_vmm_present(hv_trap_record_t *rec)   /* in_x3 */
{
	uint32_t present = 0;

	boot_prop_getter("vmm-present", &present, sizeof(present));
	present = (present != 0);
	(void)rec->copy(rec, &present, sizeof(present));
}

/* -------------------------------------------------------------------------
 * FUN_fffffe000b984fd8 @ 0xfffffe000b984fd8  (est. hv_capabilities; op table idx0)
 * Ghidra: undefined4 FUN_fffffe000b984fd8(undefined8 param_1)
 * Builds a hypervisor capabilities/feature report for the caller and copies it
 * out. Reads the calling task's entitlement tier via hv_entitlement_tier
 * (FUN_fffffe000b985ae4), folds it into a 19-qword feature mask via
 * hv_caps_feature_mask (FUN_fffffe000b987d9c) and a per-cpu CPU/memory report
 * (cache geometry + ID_AA64* regs) via hv_caps_cpu_report
 * (FUN_fffffe000b988038), then copies the 0x1b3 (435) byte report out to the
 * caller (FUN_fffffe000b95d6f4). Returns error 0xfae94001 on copyout failure.
 * Matches the Hypervisor.framework capability query: no user copyin, only a
 * kernel-built report copyout.
 * Confidence: medium (identity from the 435-byte feature/ID report + the
 *   entitlement tier input; the entitlements tree also names this
 *   "hv_capabilities").
 * Notes: b985ae4 / b987d9c / b988038 are OWNED and decompiled by the
 *   entitlements tree (hv_entitlements.c) — called here by estimated name;
 *   b95d6f4 is the shared kernel copyout (stubbed). auStack_270 is a 157-byte
 *   caps buffer, auStack_1d3 a 435-byte report buffer. The report includes
 *   feature-mask words, cache block-size shifts and id_aa64* feature regs
 *   (see hv_entitlements.c). No bounds/copyin on the caller side.
 * ------------------------------------------------------------------------- */
kern_return_t
hv_capabilities(hv_trap_record_t *rec __unused)
{
	uint8_t  caps[157];    /* auStack_270 */
	uint8_t  report[435];  /* auStack_1d3 */
	uint8_t  tier;
	int      r;

	tier = hv_entitlement_tier();                       /* b985ae4: current task's tier */
	hv_caps_feature_mask((uint64_t *)caps, tier);       /* b987d9c */
	hv_caps_cpu_report((int64_t *)caps, (uint64_t *)report); /* b988038 */
	r = copyout(report, rec, 0x1b3);       /* est. copyout 435 bytes */
	return (r != 0) ? 0xfae94001 : 0;
}

/* -------------------------------------------------------------------------
 * FUN_fffffe000b985588 @ 0xfffffe000b985588  (est. hv_vm_create; op table idx1)
 * Ghidra: undefined8 FUN_fffffe000b985588(undefined8 param_1)
 * Creates a hypervisor VM object. Copies the 0x1c-byte user arg block
 * (FUN_fffffe000b95c144), then enforces entitlement checks via the sandbox
 * (**(code **)(DAT_fffffe0007e93310 + 0x1c0)) against the three entitlement
 * strings "com.apple.security.hypervisor", "com.apple.private.hypervisor.vmapple"
 * and "com.apple.private.hypervisor"; a numeric "tier" (local_48) must be <= the
 * granted entitlement tier or the call fails. Allocates the vm object + a
 * 0x430-slot array of per-cpu owner blocks, decrements the global quota
 * counters at DAT_fffffe000c5b83b0, and records the new vm at owner+0x628.
 * Confidence: medium (strong entitlement/quota/alloc evidence for vm_create;
 *   exact field offsets are estimates).
 * Notes: heavy use of shared kernel helpers (b7eb624 alloc, b7f0ac8/b7f1e4c
 *   locks at DAT_fffffe000c62c0b8, b862b6c refcount, b85e180, b7f09dc/b7f089c);
 *   entitlement fns via DAT_fffffe0007e93310+0x1c0; err 0xfae94002/3/5/7/0xfae94fff;
 *   error paths unwind via b98533c (vcpu-core's release) and b987c44/b862b6c.
 * ------------------------------------------------------------------------- */
kern_return_t
hv_vm_create(void *args)
{
	uint64_t in  = 0, out = 0, size = 0;
	uint32_t tier = 0;
	uint64_t q0, q1;
	long    *owner;
	uint32_t granted;
	void    *vm;
	int      r, i, j;
	uint32_t u;

	in = out = size = tier = 0;
	r = copyin(args, &in, 0x1c);      /* est. copyin 0x1c bytes */
	if (r != 0)
		return 0xfae94003;
	if (tier != 0 && hv_caps_gate == 0) {   /* DAT_fffffe000c649750 */
		/* Entitlement tier check (condensed). hv_entitlement_tier (b985ae4,
		 * entitlements tree) reads the current task's granted tier itself. */
		granted = hv_entitlement_tier();             /* b985ae4: current task's tier */
		if (tier > granted) {
			owner = (long *)FUN_fffffe000b7eb624(&hv_vm_zone, 4); /* est. alloc vm */ /* DAT_fffffe0007d53eb8 */
			if (owner == NULL)
				return 0xfae94005;
			vm = FUN_fffffe000b7f089c(&hv_vm_pool, 0); /* DAT_fffffe000c5d7068 */
			*owner = (long)vm;
			if (vm != NULL) {
				owner[2] = *(long *)(tier ? 0 : 0);
				owner[0x427] = 0;
				r = (int)FUN_fffffe000b9866d0(owner, in, out, size & 0xffffffff, 0);
				if (r != 0) {
					FUN_fffffe000b7f09dc(vm, &hv_vm_pool); /* DAT_fffffe000c5d7068 */
					FUN_fffffe000b862b6c(&hv_vm_list, vm); /* DAT_fffffe0007d52478 */
					FUN_fffffe000b862b6c(&hv_owner_list, owner); /* DAT_fffffe0007d53f38 */
					return r;
				}
				/* Allocate 0x430 per-cpu owner slots; each failure decrements the
				 * quota array DAT_fffffe000c5b83b0 and unwinds. (condensed) */
				for (j = 0; j < 7; j++) {
					owner[0x429 + j] = (long)FUN_fffffe000b7eb624(&hv_slot_zone, 4); /* DAT_fffffe0007d53f78 */
					if (owner[0x429 + j] == 0)
						goto unwind;
				}
				owner[0x410] = FUN_fffffe000b85e180(u, u, 0xa004); /* est. addr width */
				hv_caps_feature_mask((uint64_t *)(owner + 0x411), tier); /* b987d9c */
				lock_acquire(&hv_lock);
				if ((*(long *)(vm + 0x628) != 0)) {
					lock_release(&hv_lock);
					hv_vcpu_object_release(owner);   /* vcpu-core release */
					return 0xfae94002;
				}
				if (tier > 1) {
					q0 = (tier != 2) ? 2 : 1;
					q1 = (tier != 3) ? q0 : 0;
					if (hv_quota_derived[q1] < 1) {
						lock_release(&hv_lock);
						hv_vcpu_object_release(owner);
						return 0xfae94fff;
					}
					hv_quota_derived[q1]--;
				}
				owner[0x425] = tier;
				owner[0x426] = hv_quota_cap;   /* DAT_fffffe000c5b83a8 */
				owner[0x432] = (tier - 3) < 2;
				owner[0x2191] = 0;
				owner[1] = 1;
				*(long **)(vm + 0x628) = owner;
				lock_release(&hv_lock);
				return 0;
			}
		unwind:
			/* Release any partially allocated owner slots. */
			for (i = 0; i < 8; i++) {
				if (owner[0x429 + i] != 0) {
					FUN_fffffe000b862b6c(&hv_slot_rel_zone, owner[0x429 + i]); /* DAT_fffffe0007d53fb8 */
					owner[0x429 + i] = 0;
				}
			}
			FUN_fffffe000b987c44(owner);
			FUN_fffffe000b7f09dc(vm, &hv_vm_pool); /* DAT_fffffe000c5d7068 */
			FUN_fffffe000b862b6c(&hv_vm_list, vm); /* DAT_fffffe0007d52478 */
		}
		FUN_fffffe000b862b6c(&hv_vm_rel_zone, owner); /* DAT_fffffe0007d53ff8 */
		return 0xfae94005;
	}
	return 0xfae94007;
}

/* -------------------------------------------------------------------------
 * FUN_fffffe000b985bf0 @ 0xfffffe000b985bf0  (est. hv_vm_destroy; op table idx2)
 * Ghidra: undefined8 FUN_fffffe000b985bf0(void)
 * Destroys the calling thread's hypervisor VM: takes the vm owner block from
 * per-cpu owner+0x628, releases the shared vm lock (DAT_fffffe000c62c0b8),
 * drops a per-cpu "active cpu" reference (clear cpu id at owner+8, sync via
 * FUN_fffffe000b7f1e80), decrements the vm refcount and LORelease(); when the
 * refcount hits 1 the object release path FUN_fffffe000b98533c runs and the
 * last releaser panics (FUN_fffffe000c0f8674, no-return).
 * Confidence: medium (per-cpu vm teardown + refcount release pattern).
 * Notes: reads per-cpu id at tpidr_el1+0x518; DAT_fffffe000c62b3d0 is a global
 *   "pending sync" flag; err 0xfae94002/6; FUN_fffffe000b866ec4 is the per-cpu
 *   state base; lock/refcount helpers are shared kernel.
 * ------------------------------------------------------------------------- */
kern_return_t
hv_vm_destroy(void *args __unused)
{
	uint64_t u;
	uint64_t cpu_slot = 0;
	long    *owner;
	long    *vm_owner;
	long    *o;
	int      cpu, i, pending;
	uint32_t prev;

	u = hv_cached_cpu_id;   /* DAT_fffffe000c62c0c0 */
	cpu_slot = tpidr_el1;
	if (hv_cached_cpu_id == 0)
		hv_cached_cpu_id = *(uint32_t *)(cpu_slot + 0x518);
	if (u != 0 || hv_debug_flag != 0)
		lock_acquire(&hv_lock, cpu_slot, u, 0);  /* est. lock */

	owner = (long *)per_cpu_base(cpu_slot);
	pending = hv_debug_flag;
	vm_owner = *(long **)(owner + 0x628);
	if (vm_owner == NULL) {
		lock_release(&hv_lock);   /* est. unlock */
		return 0xfae94006;
	}
	o = (long *)*vm_owner;
	cpu = (int)*(uint32_t *)(o + 1);         /* stored per-cpu id */
	if (cpu == 0) {
		*(uint32_t *)(o + 1) = *(uint32_t *)(cpu_slot + 0x518);
	}
	if (cpu != 0 || pending == 0) {
		lock_acquire(o, cpu_slot, (uint64_t)cpu, 0);
	}
	o = (long *)vm_owner[3];
	pending = hv_debug_flag;
	hv_debug_flag = pending;
	if (o == NULL) {
		*(uint64_t *)(owner + 0x628) = 0;
		pending = hv_debug_flag;
		o = (long *)*vm_owner;
		prev = *(uint32_t *)(o + 1);
		i = *(uint32_t *)(cpu_slot + 0x518);
		if (prev == (uint32_t)i)
			*(uint32_t *)(o + 1) = 0;
		if (prev != (uint32_t)i || pending != 0)
			lock_sync(o, cpu_slot);          /* est. per-cpu sync */
		i = (int)hv_cached_cpu_id;
		if ((int)hv_cached_cpu_id == *(uint32_t *)(cpu_slot + 0x518))
			hv_cached_cpu_id = (hv_cached_cpu_id & 0xffffffff00000000);
		if (i != *(uint32_t *)(cpu_slot + 0x518) || hv_debug_flag != 0)
			lock_sync(&hv_lock, cpu_slot);
		i = (int)vm_owner[1];
		vm_owner[1] = i - 1;
		LORelease();
		if (i == 0)
			kernel_panic_b();                      /* est. panic, no-return */
		if (i == 1)
			hv_vcpu_object_release(vm_owner);              /* vcpu-core release */
		return 0;
	}
	prev = *(uint32_t *)(o + 1);
	i = *(uint32_t *)(cpu_slot + 0x518);
	if (prev == (uint32_t)i)
		*(uint32_t *)(o + 1) = 0;
	if (prev != (uint32_t)i || pending != 0)
		lock_sync(o, cpu_slot);
	return 0xfae94002;
}

/* -------------------------------------------------------------------------
 * FUN_fffffe000b986898 @ 0xfffffe000b986898  (est. hv_vm_map; op table idx3)
 * Ghidra: void FUN_fffffe000b986898(undefined8 param_1)
 * Thin wrapper: dispatches the map operation with (op=0, mode=0).
 * Confidence: low (identity from shape; map/unmap pairing with idx5).
 * ------------------------------------------------------------------------- */
kern_return_t
hv_vm_map(void *args)
{
	return hv_vm_map_core(args, 0, 0);
}

/* -------------------------------------------------------------------------
 * FUN_fffffe000b986d94 @ 0xfffffe000b986d94  (est. hv_vm_unmap; op table idx5)
 * Ghidra: void FUN_fffffe000b986d94(undefined8 param_1)
 * Thin wrapper: dispatches the unmap/protect operation with (op=0, mode=1).
 * Confidence: low.
 * ------------------------------------------------------------------------- */
kern_return_t
hv_vm_unmap(void *args)
{
	return hv_vm_map_core(args, 0, 1);
}

/* -------------------------------------------------------------------------
 * FUN_fffffe000b9868a8 @ 0xfffffe000b9868a8  (est. hv_vm_map_core; shared by
 *   idx3/idx5)
 * Ghidra: undefined8 FUN_fffffe000b9868a8(undefined8 param_1,int param_2,int param_3)
 * Common vm-map/unmap core. Copies the 0x28-byte user arg block
 * (FUN_fffffe000b95c144), looks up the vm owner via FUN_fffffe000b986b34, then
 * validates the requested range (start/size) against the vm's allowed region
 * bounds (vm+0x28 start, vm+0x30 size) and the address-cap mask derived from
 * the vm cap field at vm+0x44 (1<<(cap&0x3f))-1. For mode==0 && op==0 it maps
 * memory (FUN_fffffe000b8b51c8) with perms 0x80001100001, else unmaps
 * (FUN_fffffe000b8b49e8) or protects (FUN_fffffe000b8a8078) the range. On
 * validation failure the caller's per-cpu vcpu slot (tpidr_el1+0x4d8) is torn
 * down via FUN_fffffe000b8afa78 and error 0xfae94003 returned.
 * Confidence: medium (clear vm-map range validation + map/unmap helpers).
 * Notes: caps: (1L<<(*(ushort*)(vm+0x44)&0x3f))-1; bounds vm+0x28 / vm+0x30;
 *   addr limit 0x7ffffe000000; err 0xfae94001/3; helper fns b8b51c8/b8b49e8/
 *   b8a8078/b986b34/b8afa78/b793cf4/b8a8078 are shared kernel, not recreated.
 * ------------------------------------------------------------------------- */
kern_return_t
hv_vm_map_core(void *args, int op, int mode)
{
	uint64_t start, size, capmask, addr_limit, perms;
	uint64_t a, b, c, d;
	uint64_t offset = 0, prot = 0;
	uint64_t a0 = 0, b0 = 0, c0 = 0, d0 = 0;
	void    *vm;
	char    *ret;
	uint64_t v;
	int      r;
	uint64_t arg0, arg1;

	(void)op;
	r = copyin(args, &start, 0x28);   /* est. copyin 0x28 bytes */
	if (r != 0)
		return 0xfae94003;
	vm = FUN_fffffe000b986b34(a0, &ret);            /* est. vm owner lookup */
	if (vm == NULL)
		return 0xfae94003;
	arg0 = start;
	if (*(void **)(vm + 0x58) != NULL) {
		/* For the special owner block DAT_fffffe000c62b698, force the high
		 * "unrestricted" bit so the mask check below passes. */
		v = start & 0xf0ffffffffffffff;
		if (*(void **)(vm + 0x58) == &hv_special_owner_block)
			v = start | 0xf00000000000000;
		arg0 = (start != 0) ? v : 0;
	}
	capmask = (1ULL << (*(uint16_t *)(vm + 0x44) & 0x3f)) - 1;
	start = arg0;
	if (((start & capmask) != 0 || (b0 & capmask) != 0 || (c0 & capmask) != 0 ||
	     d0 > 7 ||
	     (start + c0) > 0x7ffffe000000ULL ||
	     b0 < *(uint64_t *)(vm + 0x28) ||
	     *(uint64_t *)(vm + 0x30) < (c0 + b0))) {
		/* Range rejected: tear down caller's per-cpu vcpu if present. */
		if (ret != (char *)0xffffffffffffffff) {
			if (ret == NULL) {
				if (*(long *)(tpidr_el1 + 0x4d8) != 0)
					return 0xfae94003;
				FUN_fffffe000b8afa78();
				return 0xfae94003;
			}
			if (*ret != '-')
				kernel_panic_c(ret, 0, 0x2d);  /* est. panic on bad ref */
		}
		FUN_fffffe000b793cf4(ret);
		return 0xfae94003;
	}
	if (mode == 0 && op == 0) {
		offset = 0; addr_limit = 0;
		addr_limit = tpidr_el1;
		v = per_cpu_base(addr_limit);
		v = (v != 0) ? *(long *)(v + 0x28) : 0;
		r = FUN_fffffe000b8b51c8(vm, &offset, c0, 0, 0x80001100001ULL,
		                          v, start, 0, (void *)((long)&addr_limit + 4),
		                          &addr_limit, 2);          /* est. vm_map */
		if (r == 0) {
			if (c0 != 0) {
				r = FUN_fffffe000b8b49e8(vm, b0, c0 + b0, 1, 7);  /* est. adjust */
				prot = c0;
				if (r != 0) {
					FUN_fffffe000b8a8078(vm, b0, c0);   /* est. unmap on failure */
					goto fail;
				}
			}
			goto ok;
		}
	fail:
		FUN_fffffe000b986d34(ret, vm);
		return 0xfae94001;
	}
ok:
	if (op == 0) {
		if (c0 != 0) {
			r = FUN_fffffe000b8b49e8(vm, b0, c0 + b0, 0, (uint32_t)d0 & 7);
			goto join;
		}
	} else {
		r = FUN_fffffe000b8a8078(vm, b0, c0);
join:
		if (r != 0)
			goto fail;
	}
	FUN_fffffe000b986d34(ret, vm);
	return 0;
}

/* -------------------------------------------------------------------------
 * FUN_fffffe000b986d84 @ 0xfffffe000b986d84  (est. hv_vm_protect; op table idx4)
 * Ghidra: <no function defined at this address>
 * Op-table index 4 points here, but Ghidra has no function at the address.
 * Raw bytes (verified, read_memory b986d84): `dsb; mov w1,#1; mov w2,#0;
 * b 0xfffffe000b9868a8` — a thin barrier + dispatch stub that jumps into the
 * shared map/unmap/protect core (hv_vm_map_core @ b9868a8) with op=1, mode=0.
 * The core dispatches on (op, mode): (0,0)->map (b8b51c8), op==0->unmap
 * (b8b49e8), op!=0->protect (b8a8078). So idx4 selects the PROTECT path.
 * This matches hv_vm_protect, the third member of the map/unmap/protect
 * family (idx3 map, idx4 protect, idx5 unmap). Treated as an alias/secondary
 * entry, not a standalone decompilable function.
 * Confidence: high (op=1/mode=0 -> protect core b8a8078 confirmed from the
 *   branch stub + core dispatch at b986a10..b986a20).
 * Notes: the earlier comment claimed the stub branched to b98689c; the branch
 *   imm (0x17fffec6, imm26=0x3fffec6, offset -0x4e8) resolves to b9868a8, the
 *   core entry. The stub's w1/w2 are hv_vm_map_core's (op, mode).
 * ------------------------------------------------------------------------- */
kern_return_t
hv_vm_protect(void *args __unused)
{
	/* dsb; w1=1(op); w2=0(mode); b core@b9868a8 -> protect path (see header) */
	return 0;
}

/* -------------------------------------------------------------------------
 * FUN_fffffe000b9897bc @ 0xfffffe000b9897bc  (est. hv_vcpu_destroy_trap; op table idx7)
 * Ghidra: undefined8 FUN_fffffe000b9897bc(void)
 * Destroys the calling CPU's bound vcpu. Reads the per-cpu vcpu slot
 * (tpidr_el1+0x4d8); takes the vm lock and bumps the per-cpu "in critical
 * section" counter (tpidr_el1+0x1c0). If the vcpu has the AMX feature
 * (vcpu+0x411e bit6 set and vcpu[0x18]+0x1400 nonzero) it disables AMX by
 * clearing bit63 of UnkSytemRegRead(3,4,0xf,1,4) around __amx_disable() with
 * isb barriers. If EL2 is enabled (DAT_fffffe0007e0da68) and the vcpu uses
 * streaming SVE (vcpu+0x4118 bit4, vcpu+0x4138&3) it clears bits 0/1 of the
 * svcr register and calls sveStreamingModeStop(). Then it clears the per-cpu
 * vcpu slot, calls FUN_fffffe000b988e70 (est. hv_vcpu_destroy in vcpu-core)
 * to release the vcpu, releases the lock, and returns 0.
 * Confidence: medium (per-cpu vcpu teardown + EL2 AMX/SVE disable is decisive).
 * Notes: EL2 sysreg read/write (3,4,0xf,1,4) = op1=4 ⇒ EL2; register identity
 *   (likely amcr_el2/amair) unverified; __amx_disable / sveStreamingModeStop are
 *   kernel builtins; svcr is the SVE control reg global; err 0xfae94006;
 *   FUN_fffffe000b988e70 owned by vcpu-core tree.
 * ------------------------------------------------------------------------- */
kern_return_t
hv_vcpu_destroy_trap(void *args __unused)
{
	uint64_t u;
	uint64_t cpu_slot;
	long    *vcpu;
	long    *v;
	int      pending, i;
	uint32_t prev;

	pending = hv_debug_flag;
	cpu_slot = tpidr_el1;
	vcpu = *(long **)(cpu_slot + 0x4d8);
	if (vcpu == NULL)
		return 0xfae94006;
	v = (long *)*vcpu;
	u = *(uint64_t *)(v + 1);
	if (u == 0)
		*(uint64_t *)(v + 1) = *(uint32_t *)(cpu_slot + 0x518);
	if (u != 0 || pending != 0)
		lock_acquire(v, cpu_slot, u, 0);   /* est. lock */
	*(int *)(cpu_slot + 0x1c0) += 1;               /* critical-section depth */
	FUN_fffffe000b9882ac(vcpu);                    /* est. EL2 state activate */
	if (*(int *)(cpu_slot + 0x1c0) == 0)
		kernel_panic();                    /* est. panic, no-return */
	i = *(int *)(cpu_slot + 0x1c0) - 1;
	*(int *)(cpu_slot + 0x1c0) = i;
	if (i == 0 && ((*(uint8_t *)(*(long *)(cpu_slot + 0x1b8) + 0x4c) >> 2) & 1) != 0)
		FUN_fffffe000b96c6d4();                    /* est. post-EL2 hook */
	*(uint64_t *)(cpu_slot + 0x4d8) = 0;           /* clear per-cpu vcpu slot */

	/* AMX disable if enabled on this vcpu. */
	if (((*(uint8_t *)(vcpu[0x16] + 0x411e) >> 6) & 1) != 0 &&
	    *(long *)(vcpu[0x18] + 0x1400) != 0) {
		*(int *)(cpu_slot + 0x1c0) += 1;
		u = UnkSytemRegRead(3,4,0xf,1,4);
		UnkSytemRegWrite(3,4,0xf,1,4, u | 0x8000000000000000);
		InstructionSynchronizationBarrier();
		__amx_disable();
		u = UnkSytemRegRead(3,4,0xf,1,4);
		UnkSytemRegWrite(3,4,0xf,1,4, u & 0x7fffffffffffffff);
		InstructionSynchronizationBarrier();
		if (*(int *)(cpu_slot + 0x1c0) == 0)
			kernel_panic();
		i = *(int *)(cpu_slot + 0x1c0) - 1;
		*(int *)(cpu_slot + 0x1c0) = i;
		if (i == 0 && ((*(uint8_t *)(*(long *)(cpu_slot + 0x1b8) + 0x4c) >> 2) & 1) != 0)
			FUN_fffffe000b96c6d4();
	}
	/* Streaming SVE stop if EL2 enabled and vcpu is in streaming mode. */
	if (hv_build_gate != 0 &&
	    ((*(uint8_t *)(vcpu[0x16] + 0x4118) >> 4) & 1) != 0 &&
	    (*(uint8_t *)(vcpu[0x16] + 0x4138) & 3) != 0) {
		u = svcr;
		svcr = u & 0xfffffffffffffffe;
		u = svcr;
		svcr = u & 0xfffffffffffffffd;
		sveStreamingModeStop();
	}
	FUN_fffffe000b793cf4(vcpu[0x1c]);
	vcpu[0x1c] = 0;
	FUN_fffffe000b988e70(vcpu);                    /* vcpu-core: hv_vcpu_destroy */
	i = hv_debug_flag;
	v = (long *)*v;
	prev = *(uint32_t *)(v + 1);
	if (prev == *(uint32_t *)(cpu_slot + 0x518))
		*(uint32_t *)(v + 1) = 0;
	if (prev != *(uint32_t *)(cpu_slot + 0x518) || i != 0)
		lock_sync(v, cpu_slot);         /* est. per-cpu sync */
	return 0;
}

/* -------------------------------------------------------------------------
 * FUN_fffffe000b9899b0 @ 0xfffffe000b9899b0  (est. hv_vcpu_run_trap; op table idx8)
 * Ghidra: undefined8 FUN_fffffe000b9899b0(void)
 * Runs / resumes the calling CPU's bound vcpu. Reads the per-cpu vcpu slot
 * (tpidr_el1+0x4d8); if none, returns 0xfae94006. Otherwise enters the
 * critical section (tpidr_el1+0x1c0++) and calls FUN_fffffe000b988358 (vcpu-core
 * launch helper) with the vcpu and an EL2 control mask chosen by the EL2-L2
 * feature flag DAT_fffffe0007e0d81d: 0x7fc000000000001f (L2-capable) else
 * 0x7bc000000000001f. Exits the critical section and returns 0.
 * Confidence: medium (vcpu launch with EL2 feature-gated control mask).
 * Notes: reads EL2-L2 flag DAT_fffffe0007e0d81d (set by hv_el2_feature_detect);
 *   FUN_fffffe000b988358 owned by vcpu-core tree; err 0xfae94006.
 * ------------------------------------------------------------------------- */
kern_return_t
hv_vcpu_run_trap(void *args __unused)
{
	uint64_t mask;
	uint64_t cpu_slot = tpidr_el1;
	int      i;

	if (*(long *)(cpu_slot + 0x4d8) == 0)
		return 0xfae94006;
	*(int *)(cpu_slot + 0x1c0) += 1;
	mask = (hv_el2_l2 & 1) ? 0x7fc000000000001fULL : 0x7bc000000000001fULL;
	FUN_fffffe000b988358(*(long *)(cpu_slot + 0x4d8), mask); /* vcpu-core: launch */
	if (*(int *)(cpu_slot + 0x1c0) == 0)
		kernel_panic();
	i = *(int *)(cpu_slot + 0x1c0) - 1;
	*(int *)(cpu_slot + 0x1c0) = i;
	if (i == 0 && ((*(uint8_t *)(*(long *)(cpu_slot + 0x1b8) + 0x4c) >> 2) & 1) != 0)
		FUN_fffffe000b96c6d4();
	return 0;
}

/* -------------------------------------------------------------------------
 * FUN_fffffe000b98e488 @ 0xfffffe000b98e488  (est. hv_trap_op_10; op table idx10)
 * Ghidra: undefined8 FUN_fffffe000b98e488(ulong param_1)   [WARNING: Removing
 *   unreachable block (ram,0xfffffe000b98e648); Type propagation not settling]
 * Marks a set of per-cpu vcpu slots dirty/taken according to a bitmask in
 * param_1 (param_1==0 => just a DMB barrier). For each set bit it computes the
 * bit index via a 64-bit reverse-bits + LZCOUNT, tags the per-cpu slot table
 * entry (plVar11 + idx*0x10 + 0x12 = 1), then (if the vm owner at plVar11+0x10
 * block exists) takes that owner's lock, flags it busy (|=4), and flushes its
 * state (FUN_fffffe000b8563f8 / FUN_fffffe000b95ecd8). Ends with a DMB and, for
 * a fresh (no vcpu) caller, calls FUN_fffffe000b98e74c to finalize.
 * Confidence: low (bitmask-driven per-CPU vcpu-state flush op; NOT matched to a
 *   public API — attempted: hv_vcpu_exec, hv_vm_map/unmap propagation to all
 *   CPUs, shared-memory sync; none fit the per-CPU-slot flush + owner-refcount
 *   dance, so kept descriptive hv_trap_op_10).
 * Notes: bit index = LZCOUNT(bitrev64(mask)); DMB barrier DataMemoryBarrier(2,3);
 *   helpers b8563f8/b95ecd8/b98e74c shared/el2; err 0xfae94006; LOAcquire/LORelease
 *   around the owner busy flag. Takes the trap arg as a 64-bit CPU-bitmask value
 *   (no copyin); owner refcount inc/dec with panic on overflow (c0f86a4).
 * ------------------------------------------------------------------------- */
kern_return_t
hv_trap_op_10(uint64_t mask)
{
	uint64_t u, idx, m;
	long    *vcpu, *owner, *slot;
	uint64_t cpu_slot = tpidr_el1;
	int      pending, i;
	uint32_t prev;
	uint64_t a;

	u = hv_cached_cpu_id;
	vcpu = *(long **)(cpu_slot + 0x4d8);
	if (vcpu == NULL) {
		if (hv_cached_cpu_id == 0)
			hv_cached_cpu_id = *(uint32_t *)(cpu_slot + 0x518);
		if (u != 0 || hv_debug_flag != 0)
			lock_acquire(&hv_lock, cpu_slot, u, 0);  /* DAT_fffffe000c62c0b8 */
		owner = (long *)per_cpu_base(cpu_slot);
		owner = *(long **)(owner + 0x628);
		if (owner == NULL) {
			lock_release(&hv_lock);
			return 0xfae94006;
		}
		pending = (int)owner[1];
		owner[1] = pending + 1;
		if ((uint32_t)(pending + 0xf0000001) < 0xf0000002)
			kernel_panic_a();               /* est. panic on refcount overflow */
		pending = (int)hv_cached_cpu_id;
		if ((int)hv_cached_cpu_id == *(uint32_t *)(cpu_slot + 0x518))
			hv_cached_cpu_id = (hv_cached_cpu_id & 0xffffffff00000000);
		if (pending != *(uint32_t *)(cpu_slot + 0x518) || hv_debug_flag != 0)
			lock_sync(&hv_lock, cpu_slot);
	} else {
		owner = (long *)*vcpu;
	}
	m = mask;
	if (mask == 0) {
		DataMemoryBarrier(2, 3);
	} else {
		do {
			u = bitrev64(m);
			u = (u >> 0x20) | (u << 0x20);
			idx = __builtin_clzll(u);
			*(uint8_t *)(owner + idx * 0x10 + 0x12) = 1;   /* tag slot dirty */
			m &= ~(1ULL << (idx & 0x3f));
		} while (m != 0);
		DataMemoryBarrier(2, 3);
		do {
			u = bitrev64(mask);
			u = (u >> 0x20) | (u << 0x20);
			idx = __builtin_clzll(u);
			slot = (long *)(owner + idx * 0x10 + 0x10);
			if (*slot != 0 && vcpu != (long *)*slot) {
				prev = *(uint32_t *)(owner + idx * 0x80 + 0x94);
				LOAcquire();
				*(uint32_t *)(owner + idx * 0x80 + 0x94) = prev | 4;
				pending = hv_debug_flag;
				LORelease();
				if ((prev & 1) == 0) {
					a = slot[1];
				} else {
					a = *owner;
					u = *(uint64_t *)(a + 1);
					if (u == 0)
						*(uint64_t *)(a + 1) = *(uint32_t *)(cpu_slot + 0x518);
					if (u != 0 || pending != 0)
						lock_acquire(a, cpu_slot, u, 0);
					FUN_fffffe000b8563f8(&hv_flush_lock, (void *)*slot, 0, 0, 1);  /* DAT_fffffe000c756760 */
					pending = hv_debug_flag;
					a = *owner;
					if (*(uint32_t *)(a + 1) == *(uint32_t *)(cpu_slot + 0x518)) {
						*(uint32_t *)(a + 1) = 0;
						if (pending == 0)
							goto l_flush;
					}
					lock_sync(a, cpu_slot);
					a = slot[1];
				}
			l_flush:
				if (a != 0)
					FUN_fffffe000b95ecd8(a, 0, 0, 0, 0);   /* est. flush */
			}
			mask &= ~(1ULL << (idx & 0x3f));
		} while (mask != 0);
	}
	if (vcpu == NULL)
		FUN_fffffe000b98e74c(owner);               /* el2-state: finalize */
	return 0;
}

/* -------------------------------------------------------------------------
 * FUN_fffffe000b986da4 @ 0xfffffe000b986da4  (est. hv_vm_map_shared; op table idx12)
 * Ghidra: undefined8 FUN_fffffe000b986da4(long param_1)
 * Maps a range of guest physical memory and returns a shared-region handle.
 * Copies the 0x20-byte user arg block (FUN_fffffe000b95c144: [gpa(8),
 * size(8), page_size/flags(4)...]), calls the vcpu-core helper
 * hv_vcpu_map_memory (FUN_fffffe000b9866d0, vcpu=0 => current vm) which maps
 * gpa..gpa+size and produces an 8-byte handle; on success copies the handle
 * back out at args+0x18 (FUN_fffffe000b95d6f4) and returns 0. If the copyout
 * fails it still notifies the per-cpu state block (tpidr_el1+0x318, via
 * FUN_fffffe000b7a1dd8) with the handle's low 32 bits, then returns
 * 0xfae94003.
 * Confidence: medium (map-guest-memory + return-handle is the
 *   hv_vm_map_shared contract; the handle is copied out, not written into a
 *   guest register).
 * Notes: helper b9866d0 (hv_vcpu_map_memory) is owned by the vcpu-core tree;
 *   b95c144/b95d6f4 are the shared copyin/copyout helpers; b866ec4 (per-cpu
 *   base) / b7a1dd8 (per-cpu notify) are kernel deps. Copyin size 0x20, copyout
 *   8 bytes at offset 0x18.
 * ------------------------------------------------------------------------- */
kern_return_t
hv_vm_map_shared(void *args)
{
	uint64_t a0 = 0, a1 = 0, a2 = 0, a3 = 0;
	uint64_t result = 0;
	uint64_t cpu_slot;
	long    *o;
	int      r;

	r = copyin(args, &a0, 0x20);
	if (r != 0)
		return 0xfae94003;
	r = (int)FUN_fffffe000b9866d0(0, a0, a1, a2 & 0xffffffff, &result); /* vcpu-core: map mem */
	if (r != 0)
		return r;
	r = copyout(&result, (void *)((long)args + 0x18), 8);  /* copyout handle */
	if (r == 0)
		return r;
	cpu_slot = tpidr_el1;
	o = (long *)per_cpu_base(cpu_slot);
	o = (o != 0) ? *(long **)(o + 0x318) : 0;
	FUN_fffffe000b7a1dd8(o, result & 0xffffffff);           /* per-cpu notify */
	return 0xfae94003;
}

/* -------------------------------------------------------------------------
 * FUN_fffffe000b986f1c @ 0xfffffe000b986f1c  (est. hv_vm_set_trap_debug; op table idx14)
 * Ghidra: undefined8 FUN_fffffe000b986f1c(undefined8 param_1)
 * Sets a hardware trap-debug register slot on the caller's VM. Copies the
 * 0x18-byte user arg block (FUN_fffffe000b95c144: [id(8), value(8),
 * reg-sel(8)]), validates a 0..9 debug-register selector (local_30), looks up
 * the vm owner by id (FUN_fffffe000b986b34), then calls
 * FUN_fffffe000b954160(vm_resource, selector, value) to apply the debug
 * register. b954160 panics on "invoked on stage 1 pmap" / "debug exceptions
 * enabled in kernel mode" and manipulates daif (must run with IRQs masked)
 * around the write — it is hardware debug-register configuration. On a fresh
 * (unbound) vm ref it binds/tears down the caller's per-cpu vcpu instead.
 * Confidence: medium (per-vm debug-reg slot + the b954160 daif/debug-exception
 *   panics are decisive for a set-trap-debug op; vm-level lookup => vm, not
 *   vcpu).
 * Notes: err 0xfae94003; panic paths c0e1c3c (bad '-' ref) / c0e11ec (b954160);
 *   helpers b986b34 (owner lookup) / b8afa78 / b793cf4 / b866ec4 kernel.
 *   Copyin 0x18, selector bound 0..9.
 * ------------------------------------------------------------------------- */
kern_return_t
hv_vm_set_trap_debug(void *args)
{
	uint64_t a0 = 0, a1 = 0, a2 = 0;
	void    *vm;
	char    *ret;
	uint64_t idx;
	uint64_t cpu_slot;
	int      r;

	r = copyin(args, &a0, 0x18);
	if (r != 0)
		return 0xfae94003;
	idx = a2;
	if (idx > 9)
		return 0xfae94003;
	vm = FUN_fffffe000b986b34(a0, &ret);            /* est. vm owner lookup */
	if (vm == NULL)
		return 0xfae94003;
	if (*(void **)(vm + 0x58) != NULL)
		FUN_fffffe000b954160(*(void **)(vm + 0x58), idx, a1); /* set trap-debug slot */
	if (ret != (char *)0xffffffffffffffff) {
		if (ret == NULL) {
			cpu_slot = tpidr_el1;
			if (*(long *)(cpu_slot + 0x4d8) != 0)
				return 0;
			FUN_fffffe000b8afa78(vm);               /* est. teardown */
			return 0;
		}
		if (*ret != '-')
			kernel_panic_c(ret, 0, 0x2d);     /* est. panic on bad ref */
	}
	FUN_fffffe000b793cf4();
	return 0;
}

/* -------------------------------------------------------------------------
 * FUN_fffffe000b98e788 @ 0xfffffe000b98e788  (est. hv_trap_op_15; op table idx15)
 * Ghidra: undefined8 FUN_fffffe000b98e788(ulong param_1)
 * Binds the calling CPU's vcpu to an EL2 execution mode (param_1 in 0..3).
 * Requires a per-cpu vcpu (tpidr_el1+0x4d8) and EL2 enabled (DAT_fffffe0007e0da68).
 * Rejects modes when AMX is active (vcpu[0x16]+0x411e bit6 and vcpu[0x18]+0x1400).
 * If the 0x4000-byte EL2 scratch area (vcpu[0x1a]) is not yet allocated, it maps
 * a 0x4000 region (FUN_fffffe000b8a6c14 + FUN_fffffe000b8b51c8 with flags
 * 0x1c100008), records the VA at vcpu[0x16]+0x4148 and sets the "active"
 * feature bit (vcpu[0x16]+0x4118 |= 0x10). Finally it stores param_1 in the
 * vcpu's execution-mode field (vcpu[0x16]+0x4138) and, when a scratch area
 * exists, forces the mode bits 0x3000000 into the EL2 state word at
 * vcpu[0x16]+0x4040.
 * Confidence: low (guest streaming-SVE / SVCR_EL2 mode select; NOT matched to a
 *   public API — attempted: hv_vcpu_set_vtimer_offset, hv_vcpu_set_exec_mode,
 *   hv_vcpu_set_trap_debug; none fit the SVCR/SVE-mode + EL2-scratch alloc, so
 *   kept descriptive hv_trap_op_15).
 * Notes: the field at vcpu[0x16]+0x4138 is SVCR_EL2-style (bit0=ZA, bit1=SM;
 *   cf. hv_vcpu_save_el2_state's `+0x4138 >> 1 & 1` streaming-SVE check), and
 *   HCR_EL2 (+0x4040) bits 0x3000000 are forced to trap SVE/SME access; the
 *   0x4000 EL2 scratch (vcpu[0x1a]) holds the SVE save state. err 0xfae94005/3/6;
 *   helpers b8a6c14/b8b51c8/b7f62e8/b8b6860/b866ec4; b96c6d4 post-EL2 hook;
 *   DAT_fffffe0007e0da68 = EL2-enabled flag. Takes mode (0..3) as a value arg.
 * ------------------------------------------------------------------------- */
kern_return_t
hv_trap_op_15(uint64_t mode)
{
	uint64_t cpu_slot = tpidr_el1;
	long    *vcpu;
	long    *v, *scratch;
	uint64_t va = 0, u;
	uint32_t f0 = 3, f1 = 3;
	int      r;

	vcpu = *(long **)(cpu_slot + 0x4d8);
	if (vcpu == NULL)
		return 0xfae94006;
	if (hv_build_gate == 0)
		return 0xfae94005;
	if (mode > 3)
		return 0xfae94003;
	if (mode != 0) {
		v = vcpu[0x16];
		if (((*(uint8_t *)(v + 0x411e) >> 6) & 1) != 0 &&
		    *(long *)(vcpu[0x18] + 0x1400) != 0)
			return 0xfae94005;
		if (vcpu[0x1a] == 0) {
			va = 0;
			r = FUN_fffffe000b8a6c14(0, 0x4000, 0, 0x10080, 0x1c, 0); /* est. alloc */
			if (r != 0)
				return 0xfae94005;
			r = FUN_fffffe000b8b51c8(*(void **)(*vcpu + 0x10), &va, 0x4000, 0,
			                          0x1c100008ULL, 0, 0, 0, &f1, &f0, 2); /* est. map */
			if (r != 0) {
				FUN_fffffe000b7f62e8(0);
				FUN_fffffe000b8b6860(0, 0, 0 + 0x4000, 1, 0);
				return 0xfae94005;
			}
			*(int *)(cpu_slot + 0x1c0) += 1;
			vcpu[0x1a] = (long)scratch;
			*(uint64_t *)(v + 0x4148) = va;
			*(uint64_t *)(v + 0x4118) |= 0x10;
			if (*(int *)(cpu_slot + 0x1c0) == 0)
				kernel_panic();
			r = *(int *)(cpu_slot + 0x1c0) - 1;
			*(int *)(cpu_slot + 0x1c0) = r;
			if (r == 0 && ((*(uint8_t *)(*(long *)(cpu_slot + 0x1b8) + 0x4c) >> 2) & 1) != 0)
				FUN_fffffe000b96c6d4();
			goto store;
		}
	}
	scratch = vcpu[0x1a];
store:
	if (scratch != 0) {
		u = *(uint64_t *)(vcpu[0x16] + 0x4040);
		if ((u & 0x3000000) == 0)
			*(uint64_t *)(vcpu[0x16] + 0x4040) = (u & 0xffffffff) | 0x3000000;
	}
	*(uint64_t *)(vcpu[0x16] + 0x4138) = mode;
	return 0;
}

/* -------------------------------------------------------------------------
 * FUN_fffffe000b98e964 @ 0xfffffe000b98e964  (est. hv_trap_op_16; op table idx16)
 * Ghidra: undefined8 FUN_fffffe000b98e964(void)
 * Requires a per-cpu vcpu (tpidr_el1+0x4d8). If the vcpu's opcode count at
 * vcpu+0x2128 exceeds 2 and the EL2 debug flag DAT_fffffe0007e31628 is set, it
 * invokes the el2-state helper FUN_fffffe000b98e344 (owned by el2-state tree)
 * and returns 0; otherwise returns 0xfae94005/7.
 * Confidence: low (SoC-feature-gated EL2 page-table alloc hook; NOT matched to a
 *   public API — attempted: hv_vcpu_get_exec_time, hv_vcpu_set_vtimer_offset,
 *   a debug/info report; none fit the "opcode count > 2 AND SoC feature index
 *   nonzero -> hv_el2_pt_alloc" gate, so kept descriptive hv_trap_op_16).
 * Notes: err 0xfae94005/6/7; DAT_fffffe0007e31628 is the SoC feature index
 *   (also read by hv_el2_state_build, >4 clears a TCR bit), not a pure debug
 *   flag; b98e344 is owned by the el2-state tree (hv_el2_pt_alloc); the vcpu
 *   opcode counter at vcpu+0x2128 gates it.
 * ------------------------------------------------------------------------- */
kern_return_t
hv_trap_op_16(void *args __unused)
{
	uint64_t cpu_slot = tpidr_el1;
	long    *vcpu;

	vcpu = *(long **)(cpu_slot + 0x4d8);
	if (vcpu == NULL)
		return 0xfae94006;
	if (*(uint32_t *)(*vcpu + 0x2128) > 2) {
		if (hv_soc_feature_index != 0) {
			FUN_fffffe000b98e344(vcpu);           /* el2-state helper */
			return 0;
		}
		return 0xfae94005;
	}
	return 0xfae94007;
}

/* -------------------------------------------------------------------------
 * FUN_fffffe000b986ff4 @ 0xfffffe000b986ff4  (est. hv_vm_map_region; op table idx17)
 * Ghidra: undefined8 FUN_fffffe000b986ff4(undefined8 param_1)
 *   [WARNING: Type propagation algorithm not settling]
 * Full vm-region-map handler (the large one). Copies the 0x34-byte user arg
 * block, optionally binds a per-cpu resource, then inserts a (start,size)
 * region into the vm's interval rbtree (root at vm_owner+0x427) after checking
 * the range against the vm caps (vm+0x44) and bounds (vm+0x28/0x30). Handles
 * exact-overlap (returns 0xfae94008) vs. split insertion, tracks the active cpu
 * id in the vm owner (+8), takes/releases the shared lock DAT_fffffe000c62c0b8,
 * and bumps/drops the vm refcount with LORelease (overflow => panic
 * FUN_fffffe000c0f86a4). On failure it unwinds the partially inserted node and
 * the per-cpu resource (FUN_fffffe000b8afa78).
 * Confidence: medium (region-tree insert with quota/cap enforcement is the
 *   vm_map signature; exact field semantics condensed).
 * Notes: because the body is a ~1000-line rbtree insert, only a faithful
 *   structural reconstruction is given here (all DAT_/FUN_ artifacts retained);
 *   see Ghidra for the full node-rotation logic. err codes 0xfae94001/3/5/8/0xf;
 *   helpers b986b34/b9860bc/b8afa78/b793cf4/b7eb624/b7f0afc/b7f1e80/b862b6c;
 *   shared lock DAT_fffffe000c62c0b8.
 * ------------------------------------------------------------------------- */
kern_return_t
hv_vm_map_region(void *args)
{
	uint64_t a0 = 0, a1 = 0, a2 = 0, a3 = 0, a4 = 0, a5 = 0;
	void    *vm;
	char    *ret;
	uint64_t start, size;
	uint64_t cpu_slot;
	long    *owner;
	uint64_t capmask;
	int      r, refcnt;
	uint32_t prev;
	void    *node;

	r = copyin(args, &a0, 0x34);
	if (r != 0)
		return 0xfae94003;
	if (a0 == 0) {                              /* optionally bind per-cpu resource */
		cpu_slot = tpidr_el1;
		vm = (void *)per_cpu_base(cpu_slot);
		vm = (vm != 0) ? *(void **)((char *)vm + 0x318) : 0;
		r = FUN_fffffe000b78d064(vm, a1, 0x13, 1, 7, 0, &ret); /* est. bind resource */
		if (r != 0)
			return 0xfae94001;
	}
	start = a3; size = a4;                     /* (est. start/size fields) */

	/* Take vm lock + bump refcount (condensed). */
	lock_acquire(&hv_lock, tpidr_el1, hv_cached_cpu_id, 0);
	owner = (long *)per_cpu_base(tpidr_el1);
	owner = *(long **)(owner + 0x628);
	if (owner == NULL) {
		lock_release(&hv_lock);
		FUN_fffffe000b793cf4(ret);
		return 0xfae94001;
	}
	refcnt = (int)owner[1];
	owner[1] = refcnt + 1;
	if ((uint32_t)(refcnt + 0xf0000001) < 0xf0000002)
		kernel_panic_a();                /* panic on refcount overflow */

	vm = (void *)FUN_fffffe000b986b34(a2, &ret);   /* est. vm owner lookup */
	if (vm != NULL) {
		capmask = (1ULL << (*(uint16_t *)((char *)vm + 0x44) & 0x3f)) - 1;
		/* Range check + rbtree insert at owner+0x427 (condensed: exact-overlap
		 * returns 0xfae94008; otherwise split-insert the node, tracking the
		 * active cpu id and calling b9860bc on the old owner node). */
		node = FUN_fffffe000b7eb624(&hv_region_node_zone, 2); /* est. alloc node */ /* DAT_fffffe0007d54038 */
		if (node != NULL) {
			/* node[0]=vm, node[2]=start, node[1]=? , node[3]=start+size,
			 * node[4]=ret, node[5..7]=rbtree links. */
			*(void **)node = vm;
			((uint64_t *)node)[2] = start;
			((uint64_t *)node)[3] = start + size;
			((uint64_t *)node)[4] = (uint64_t)ret;
			((uint64_t *)node)[5] = ((uint64_t *)node)[6] = ((uint64_t *)node)[7] = 0;
			if (owner[0x427] == 0) {
				owner[0x427] = (long)node;     /* first node: becomes root */
			} else {
			r = hv_rbtree_insert(owner, node); /* est. rbtree insert —
			                                    * structural placeholder for the
			                                    * ~1000-line node-rotation body
			                                    * (see Ghidra FUN_fffffe000b986ff4) */
			if (r != 0)
				return hv_vm_unwind(owner, node, ret, 0xfae94008); /* structural placeholder */
			}
			prev = (uint32_t)*(uint64_t *)((char *)owner + 0x40); /* est. cpu id */
			/* ... (see Ghidra for rotation/dirtying) */
		} else {
			return hv_vm_unwind(owner, NULL, ret, 0xfae94005);
		}
	} else {
		return hv_vm_unwind(owner, NULL, ret, 0xfae9400f);
	}
	/* Release vm lock + drop refcount; last releaser frees (b98533c). */
	lock_release(&hv_lock);
	refcnt = (int)owner[1];
	owner[1] = refcnt - 1;
	LORelease();
	if (refcnt == 1)
		hv_vcpu_object_release(owner);
	FUN_fffffe000b793cf4(ret);
	return 0;
}
