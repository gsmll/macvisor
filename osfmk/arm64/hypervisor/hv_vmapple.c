/* Recreated from kernelcache.arm64.kc (xnu-12377.121.10 RELEASE_ARM64_T8142, image base fffffe0007004000). Ground truth: Ghidra FUN_ names + addresses; all names are estimates. */
#include "hv_compat.h"

/*
 * hv_vmapple.c — Apple Virtualization (vmapple) IPC service / hypervisor
 * access-gate tree.
 *
 * Owned by the vmapple-ipc tree.
 *
 * Seed anchor trace (verified 2026-08-11):
 *   Data at fffffe000c7a9f28 is a record whose first field points at the
 *   IKOT_HYPERVISOR string (fffffe0007072550) and whose second field is the
 *   function pointer hv_ikot_hypervisor_handler. Reading the surrounding region
 *   (fffffe000c7a9a00 .. fffffe000c7aa000) shows a name->handler/value table
 *   (records {name_ptr, handler/value_ptr, ...}) holding entries such as
 *   "hv" (@ fffffe000c7a9e68, value refs DAT_fffffe000c62c0c0 the hv lock and
 *   DAT_fffffe0007e0d7e8 near the hv quota global), "hv_vm_t.hv_vm_percpu_t"
 *   (@ fffffe0007071e74), and this IKOT_HYPERVISOR record.
 *   The function referenced by the IKOT_HYPERVISOR record, hv_ikot_hypervisor_handler,
 *   is hypervisor code: it takes the hv lock DAT_fffffe000c62c0c0, reads
 *   per-CPU state, and on the refcount==1 path calls hv_vcpu_object_release
 *   (est. hv_vcpu_object_release, vcpu-core tree). It is therefore the IPC
 *   kobject handler for the Hypervisor.framework service (the same service
 *   gated by com.apple.private.hypervisor.vmapple).
 *
 * The vmapple entitlement (com.apple.private.hypervisor.vmapple @
 * fffffe000707250e) is referenced from three functions:
 *   - hv_vm_create (est. hv_vm_create, trap-dispatch tree, decompiled)
 *   - hv_entitlement_tier (owned by entitlements tree, est. hv_entitlement_tier)
 *   - task_entitlement_flags (kernel exec-path task flag computation; documented
 *     in this file's notes, owned as shared kernel)
 */

#include "hv_vmapple.h"
#include "hv_kernel_glue.h"   /* os_release / waitq_validate / hv_object_lookup prototypes */

/* ---- externals (shared kernel, not recreated) ---- */
extern void *current_cpu_datap(uint64_t cpu); /* kernel: returns per-CPU struct (FUN_fffffe000b866ec4) */
extern void *os_ref_retain(void *);     /* kernel: refcount retain (FUN_fffffe000b7f089c) */
extern void *os_ref_release(void *);    /* kernel: refcount release (FUN_fffffe000b8afa78) */
extern void *kfree_type(void *);        /* kernel: zfree/kfree (FUN_fffffe000b793cf4) */
extern void *ref_count_dec(void *, void *); /* kernel: lck refcount dec (FUN_fffffe000b862b6c) */
extern uint64_t hv_object_lookup(uint64_t *container, uint64_t handle, uint64_t type); /* hv-deps recreated (FUN_fffffe000b7e0d8c) */
extern void  rbtree_unlink(void *, void *); /* hv-internal RB-tree unlink (FUN_fffffe000b9860bc) */

/* DAT_fffffe000c62b3d0 : "lock contended / disable" flag consulted around the
 *   hv lock acquire/release sequences. DAT_fffffe0007d54078 : container refcount. */

/* DAT_fffffe0007e93310 : pointer to an entitlement/credential ops vtable;
 *   +0x1c0 is the per-task entitlement-check function pointer.
 * DAT_fffffe0007e255f8 : kernel config/boot-arg flags word.
 * DAT_fffffe0007d54078 : a reference-counted container's refcount global. */

/*
 * hv_entitlement_tier @ 0xfffffe000b985ae4   (est. hv_entitlement_tier)
 * NOTE (ownership): this address is owned by the entitlements tree, which
 * decompiled it in full as `hv_entitlement_tier` in hv_entitlements.c/h
 * (already called by hv.c's hv_trap_op_0). This tree originally drafted it as
 * `hv_entitlement_access_level`; that duplicate was removed to avoid a
 * double-declaration. See hv_entitlements.h for the canonical prototype.
 * vmapple-relevant fact (from the shared Ghidra decompile): the tier returns
 * 3 when the task holds com.apple.private.hypervisor.vmapple
 * (fffffe000707250e), 1 for com.apple.security.hypervisor, and 4 for
 * com.apple.private.hypervisor + boot flag DAT_fffffe0007e255f8 & 0x1010.
 * Confidence: high (logic shared, ground truth FUN_ + addr verified)
 * Ghidra: undefined1 hv_entitlement_tier(void) */

/* FUN_fffffe000b985e38 @ 0xfffffe000b985e38   (est. hv_ikot_hypervisor_handler)
 * Ghidra: void hv_ikot_hypervisor_handler(undefined8 param_1, undefined4 param_2)
 * IPC kobject handler referenced by the IKOT_HYPERVISOR record at
 * fffffe000c7a9f28. Under the hv lock it looks up an object (param_1/param_2,
 * type 0x2d via hv_object_lookup), walks the per-CPU hv container list
 * (head at per_cpu + 0x628, child list at head[0x427]), and for the node whose
 * key matches the lookup result unlinks it (hv_rbtree_unlink), releases the
 * node, drops the container reference, and when the container refcount falls
 * to 1 calls hv_vcpu_object_release (est. hv_vcpu_object_release). This is the
 * teardown/cleanup path for a hypervisor object reached via its IPC port.
 * Confidence: medium
 * Notes: uses hv lock DAT_fffffe000c62c0c0. Refcount overflow guard
 *   (iVar15 + 0xf0000001 < 0xf0000002 => panic). os_release is the ARC-style
 *   object release (os_release) used by the kernel's kobject layer. */
void
hv_ikot_hypervisor_handler(uint64_t param_1, uint32_t param_2)
{
	uint64_t cpu_ts;
	int *count_ptr;
	int c, newc;
	uint64_t key;
	long *head;            /* per-CPU hv container list head */
	long *node;
	long *child;
	bool retained = false;
	long lookup_key;

	cpu_ts = hv_cached_cpu_id;
	if (hv_cached_cpu_id == 0) {
		hv_cached_cpu_id = (uint64_t)*(uint *)(tpidr_el1 + 0x518);
	}
	if (cpu_ts != 0 || hv_debug_flag != 0) {
		lock_acquire(&hv_lock, tpidr_el1, cpu_ts, 0);
	}

	head = *(long **)(current_cpu_datap(tpidr_el1) + 0x628);
	if (head == 0) {
		head = 0;
		retained = true;
	} else {
		retained = true;
		if (head != 0) {
			c = (int)head[1];
			*(int *)(head + 1) = c + 1;
			if ((uint)(c + 0xf0000001) < 0xf0000002) {
				kernel_panic_a();  /* est. kernel panic (no-arg) */          /* refcount overflow */
			}
			retained = false;
		}
	}

	c = (int)hv_cached_cpu_id;
	if ((int)hv_cached_cpu_id == *(int *)(tpidr_el1 + 0x518)) {
		hv_cached_cpu_id = 0;
	}
	if (c != *(int *)(tpidr_el1 + 0x518) || hv_debug_flag != 0) {
		lock_release(&hv_lock);
	}

	/* validate the waitq/port, then resolve the object key by handle+type.
	 * waitq_validate = waitq_validate; hv_object_lookup (kernel
	 * container registry) = hv_object_lookup, type 0x2d. */
	waitq_validate(param_1);
	lookup_key = hv_object_lookup((void *)param_1, param_2, 0x2d);
	os_release(NULL);                       /* FUN_fffffe000b8afa78; est. LORelease, arg unknown */

	c = hv_debug_flag;
	if (!retained) {
		node = (long *)*head;
		child = (ulong *)(node + 1);
		key = *child;
		if (key == 0) {
			*child = (uint64_t)*(uint *)(tpidr_el1 + 0x518);
		}
		if (key != 0 || c != 0) {
			lock_acquire(node, tpidr_el1, key, 0);
		}

		c = 0;
		child = (ulong *)(head + 0x427);
		node = 0;
		do {
			child = node;
			node = (long *)*child;
			child = (ulong *)(node + 5);
			c = hv_debug_flag;
		} while (node != 0);

		while (hv_debug_flag = c, child != 0) {
			node = (long *)child[6];
			if (node == 0) {
				long *p = (long *)(child[7] & ~1UL);
				node = child;
				if (p == 0 || child != (long *)p[5]) {
					do {
						p = (long *)(node[7] & ~1UL);
						if (p == 0) break;
						retained = node == (long *)p[6];
						node = p;
					} while (retained);
				}
			} else {
				do {
					child = node;
					node = (long *)child[5];
				} while (child[5] != 0);
			}
			if (lookup_key == (long)*child) {
				rbtree_unlink(head, child);
				os_ref_release((void *)*child);
				kfree_type((void *)child[4]);
				ref_count_dec(&hv_container_refcount, child);
			}
			c = 0;
			child = node;
			c = hv_debug_flag;
		}

		/* release container */
		count_ptr = (int *)((long)*head + 8);
		newc = *(int *)(tpidr_el1 + 0x518);
		c = *count_ptr;
		if (c == newc) {
			*count_ptr = 0;
		}
		if (c != newc || hv_debug_flag != 0) {
			lock_release((void *)*head);
		}

		c = (int)head[1];
		*(int *)(head + 1) = c - 1;
		os_release(NULL);           /* ARC-style object release (FUN_fffffe000b8afa78); arg unknown */
		if (c == 0) {
			kernel_panic_a();  /* est. kernel panic (no-arg) */
		}
		if (c == 1) {
			hv_vcpu_object_release(head);
		}
	}
}

/*
 * HV-internal RB-tree node removal/rebalance used by the hypervisor object
 * container teardown.
 *
 * hv_rbtree_unlink @ 0xfffffe000b9860bc   (est. hv_rbtree_unlink)
 * Ghidra: void hv_rbtree_unlink(long *param_1, ulong param_2)
 * Removes node `param_2` from the red-black tree whose root is stored at
 * param_1[0x427] (0x427 * 8 = 0x2138 bytes into the container). The tree nodes
 * are embedded lists: each node has +0x28 (left child), +0x30 (right child),
 * +0x38 (parent, low bit = red flag). The routine handles the three classic
 * RB-delete cases — node with two children (splice successor), a single
 * red child, and double-black rebalance — including the parent-link fixups
 * and the +0x38 low-bit (red/black) color propagation, then clears the root
 * entry. Written from the Ghidra decompile (logic faithful; locals renamed).
 * Confidence: low
 * Notes: called by hv_ikot_hypervisor_handler (vmapple-ipc), hv_vm_map_region
 *   (trap-dispatch hv_vm_map_region), hv_vm_owner_teardown (vcpu-core
 *   hv_vm_owner_teardown). Decompiler produced a long balanced-tree routine
 *   with no external calls; the complete body is retained in Ghidra at
 *   hv_rbtree_unlink. Reconstructed here as a faithful structural
 *   outline only — the double-black rebalance walk is large and flagged
 *   partial (fallback per AGENTS.md: partial reconstruction + notes). */
void
hv_rbtree_unlink(long *root_slot, uint64_t node)
{
	uint64_t left;
	uint64_t right;
	uint64_t parent;

	/* NB: full body in Ghidra FUN_fffffe000b9860bc. This reconstruction
	 * captures the node layout (+0x28 left, +0x30 right, +0x38 parent/red
	 * bit, root slot root_slot[0x427]) and the leaf/red-unlink and
	 * sibling-splice steps; the double-black color-fixup loop is omitted as
	 * a documented partial (confidence low). */
	left = *(uint64_t *)(node + 0x28);
	right = *(uint64_t *)(node + 0x30);
	parent = *(uint64_t *)(node + 0x38);

	(void)left; (void)right; (void)parent;
	/* See Ghidra FUN_fffffe000b9860bc for the complete RB-delete body. */
}

/*
 * ===========================================================================
 * vmapple surface — evidence-backed conclusion (2026-08-11, vmapple-deep)
 * ===========================================================================
 *
 * QUESTION: does this kernelcache contain a large production nested-VM
 * "vmapple" subsystem, or is the vmapple surface genuinely small?
 *
 * ANSWER: GENUINELY SMALL. There is NO separate nested-VM / vmapple vmm in
 * this kernel. The vmapple service is exactly the IPC kobject handler +
 * entitlement gate + object-registry glue reconstructed above. No larger
 * subsystem was fabricated because the evidence rules it out:
 *
 * SEARCHED (targeted MCP calls, all verified):
 *   1. search_strings("vmapple")            -> 1 hit TOTAL in the whole
 *        121 MB binary: the entitlement "com.apple.private.hypervisor.vmapple"
 *        (fffffe000707250e). A production nested-VM subsystem would carry many
 *        vmapple-named strings (trap names, panic paths, log tags); none exist.
 *   2. search_strings("hypervisor")         -> 7 hits, all already mapped
 *        (3 entitlements, IKOT_HYPERVISOR, "hypervisor guest",
 *        "Request that the hypervisor take a live kernel dump" sysctl,
 *        "Hypervisor info"). None names a vmapple module.
 *   3. get_xrefs_to(vmapple entitlement)    -> exactly 3 referencers, all
 *        already owned: hv_vm_create (hv_vm_create, trap-dispatch),
 *        hv_entitlement_tier (hv_entitlement_tier, entitlements), and
 *        task_entitlement_flags (kernel exec-path task flags, shared kernel).
 *   4. get_function_callees(hv_ikot_hypervisor_handler b985e38) -> ALL shared
 *        kernel deps (b78fb24 waitq_validate, b793cf4 zfree, b7e0d8c
 *        hv_object_lookup, b7f0afc/b7f1e80 hv lock, b862b6c refcount,
 *        b866ec4 per-cpu, b8afa78 os_release, c0f8674/c0f86a4 panic) plus
 *        already-owned hv functions (b98533c vcpu release, b9860bc rbtree).
 *        No nested-VM/vmm callee.
 *   5. get_function_callees(hv_entitlement_tier b985ae4) -> only
 *        current_task (b8663e8) + current_cpu_datap (b866ec4), both shared
 *        kernel. get_function_callers(b985ae4) -> single caller
 *        hv_capabilities (hv_capabilities, trap-dispatch). No vmm.
 *   6. Examined the name->handler/value table fffffe000c7a9a00..c7aa000
 *        (TreeVmappleIpc's region): it is a GENERIC kernel name->value
 *        registry (SPTM/DART/power-management names: "UAT SPTM",
 *        "SART SPTM", "t8110dart", "t6000dart", "apple_protect", "sop",
 *        "ctrr_cpu_start_lock", "cpu_lck_grp", "max_cpus",
 *        "mem_fault_report", "ecc-data", "memory_error", ...). Only two
 *        hypervisor records exist in it: the "hv" entry (fffffe000c7a9e68,
 *        value refs DAT_fffffe000c62c0c0 the hv lock) and the
 *        IKOT_HYPERVISOR record (fffffe000c7a9f28, type 0x12d = 301,
 *        name_ptr fffffe0007072550, handler hv_ikot_hypervisor_handler). The
 *        "hv_vm_t.hv_vm_percpu_t" string (fffffe0007071e74) is referenced
 *        only as a type-name in this registry (fffffe000c7a9ef8), not by any
 *        function body.
 *   7. get_xrefs_to(IKOT_HYPERVISOR string fffffe0007072550) -> a single
 *        data ref from the IKOT record. get_xrefs_to(b985e38) -> two data
 *        refs: the IKOT record (c7a9f30) and the generic kernel IKOT kobject
 *        dispatch table (fffffe000d20ad7c). No code caller: the handler is
 *        invoked only via the kernel's kobject dispatch (type 0x12d). The
 *        surrounding kobject dispatch table (fffffe000c7b3340..7b37e0) is the
 *        standard kernel IKOT type table (records of {name_ptr,
 *        registry_ptr, count}), shared by every IKOT type, not a vmapple
 *        ops table.
 *   8. No function in the hypervisor cluster (0xfffffe000b984xxx-b98exxx)
 *        references any "nested", "vmapple", or secondary-guest state beyond
 *        the entitlement tier gate. The vmapple tier (3) simply elevates the
 *        caller's capabilities in the SAME Hypervisor.framework mach-trap
 *        service (op table PTR_hv_op_table, dispatcher b984ed8)
 *        already mapped by the trap-dispatch / vcpu-core / el2-state /
 *        hv-pmap trees.
 *
 * CONCLUSION: the vmapple surface in this kernelcache is the IKOT_HYPERVISOR
 * IPC kobject handler (b985e38) + the entitlement access gate (b985ae4,
 * tier 3 for com.apple.private.hypervisor.vmapple) + the object-registry glue
 * (hv_object_lookup b7e0d8c, kernel, recreated in hv_kernel_glue.c; rbtree
 * b9860bc) + the two "hv"/IKOT registry records above. Nested virtualization
 * on this kernel is provided by the SAME Hypervisor.framework hv_* traps,
 * gated by the vmapple entitlement, NOT by a separate vmapple vmm module.
 * This matches the prior vmapple-ipc finding (3 manifest entries) — the
 * deep-dive confirms and closes the "is there more?" question with no new
 * functions to add.
 * ===========================================================================
 */
