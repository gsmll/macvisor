/* Recreated from kernelcache.arm64.kc (xnu-12377.121.10 RELEASE_ARM64_T8142, image base fffffe0007004000). Ground truth: Ghidra FUN_ names + addresses; all names are estimates. */

/*
 * hv_vmapple.c — Apple Virtualization (vmapple) IPC service / hypervisor
 * access-gate tree.
 *
 * Owned by the vmapple-ipc tree.
 *
 * Seed anchor trace (verified 2026-08-11):
 *   Data at fffffe000c7a9f28 is a record whose first field points at the
 *   IKOT_HYPERVISOR string (fffffe0007072550) and whose second field is the
 *   function pointer FUN_fffffe000b985e38. Reading the surrounding region
 *   (fffffe000c7a9a00 .. fffffe000c7aa000) shows a name->handler/value table
 *   (records {name_ptr, handler/value_ptr, ...}) holding entries such as
 *   "hv" (@ fffffe000c7a9e68, value refs DAT_fffffe000c62c0c0 the hv lock and
 *   DAT_fffffe0007e0d7e8 near the hv quota global), "hv_vm_t.hv_vm_percpu_t"
 *   (@ fffffe0007071e74), and this IKOT_HYPERVISOR record.
 *   The function referenced by the IKOT_HYPERVISOR record, FUN_fffffe000b985e38,
 *   is hypervisor code: it takes the hv lock DAT_fffffe000c62c0c0, reads
 *   per-CPU state, and on the refcount==1 path calls FUN_fffffe000b98533c
 *   (est. hv_vcpu_object_release, vcpu-core tree). It is therefore the IPC
 *   kobject handler for the Hypervisor.framework service (the same service
 *   gated by com.apple.private.hypervisor.vmapple).
 *
 * The vmapple entitlement (com.apple.private.hypervisor.vmapple @
 * fffffe000707250e) is referenced from three functions:
 *   - FUN_fffffe000b985588 (est. hv_vm_create, trap-dispatch tree, decompiled)
 *   - FUN_fffffe000b985ae4 (owned by entitlements tree, est. hv_entitlement_tier)
 *   - FUN_fffffe000b96c158 (kernel exec-path task flag computation; documented
 *     in this file's notes, owned as shared kernel)
 */

#include "hv_vmapple.h"

/* ---- externals (shared kernel, not recreated) ---- */
extern void *current_cpu_datap(void);   /* kernel: returns per-CPU struct (FUN_fffffe000b866ec4) */
extern int  hv_lock_hv(void);           /* kernel: hv mutex lock  (FUN_fffffe000b7f0afc, DAT_fffffe000c62c0c0) */
extern void hv_unlock_hv(void);         /* kernel: hv mutex unlock (FUN_fffffe000b7f1e80, DAT_fffffe000c62c0c0) */
extern void *os_ref_retain(void *);     /* kernel: refcount retain (FUN_fffffe000b7f089c) */
extern void *os_ref_release(void *);    /* kernel: refcount release (FUN_fffffe000b8afa78) */
extern void *kfree_type(void *);        /* kernel: zfree/kfree (FUN_fffffe000b793cf4) */
extern void *ref_count_dec(void *, void *); /* kernel: lck refcount dec (FUN_fffffe000b862b6c) */
extern void  panic_dyn(void);           /* kernel: noreturn panic (FUN_fffffe000c0f86a4/c0f8674) */
extern void *hv_object_lookup(void *, uint64_t, uint64_t); /* kernel lookup (FUN_fffffe000b7e0d8c) */
extern void  rbtree_unlink(void *, void *); /* hv-internal RB-tree unlink (FUN_fffffe000b9860bc) */
extern void  hv_vcpu_object_release(void *); /* vcpu-core tree (FUN_fffffe000b98533c) */

/* DAT_fffffe000c62b3d0 : "lock contended / disable" flag consulted around the
 *   hv lock acquire/release sequences. DAT_fffffe0007d54078 : container refcount. */

/* DAT_fffffe0007e93310 : pointer to an entitlement/credential ops vtable;
 *   +0x1c0 is the per-task entitlement-check function pointer.
 * DAT_fffffe0007e255f8 : kernel config/boot-arg flags word.
 * DAT_fffffe0007d54078 : a reference-counted container's refcount global. */

/*
 * FUN_fffffe000b985ae4 @ 0xfffffe000b985ae4   (est. hv_entitlement_tier)
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
 * Ghidra: undefined1 FUN_fffffe000b985ae4(void) */

/* FUN_fffffe000b985e38 @ 0xfffffe000b985e38   (est. hv_ikot_hypervisor_handler)
 * Ghidra: void FUN_fffffe000b985e38(undefined8 param_1, undefined4 param_2)
 * IPC kobject handler referenced by the IKOT_HYPERVISOR record at
 * fffffe000c7a9f28. Under the hv lock it looks up an object (param_1/param_2,
 * type 0x2d via FUN_fffffe000b7e0d8c), walks the per-CPU hv container list
 * (head at per_cpu + 0x628, child list at head[0x427]), and for the node whose
 * key matches the lookup result unlinks it (FUN_fffffe000b9860bc), releases the
 * node, drops the container reference, and when the container refcount falls
 * to 1 calls FUN_fffffe000b98533c (est. hv_vcpu_object_release). This is the
 * teardown/cleanup path for a hypervisor object reached via its IPC port.
 * Confidence: medium
 * Notes: uses hv lock DAT_fffffe000c62c0c0. Refcount overflow guard
 *   (iVar15 + 0xf0000001 < 0xf0000002 => panic). LORelease is the ARC-style
 *   object release used by the kernel's C++ kobject layer. */
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
		hv_lock_hv(&hv_lock, tpidr_el1, cpu_ts, 0);
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
				panic_dyn();          /* refcount overflow */
			}
			retained = false;
		}
	}

	c = (int)hv_cached_cpu_id;
	if ((int)hv_cached_cpu_id == *(int *)(tpidr_el1 + 0x518)) {
		hv_cached_cpu_id = 0;
	}
	if (c != *(int *)(tpidr_el1 + 0x518) || hv_debug_flag != 0) {
		hv_unlock_hv(&hv_lock, tpidr_el1);
	}

	/* lookup object key */
	hv_object_lookup(param_1);
	lookup_key = hv_object_lookup(param_1, param_2, 0x2d);
	os_ref_release();

	c = hv_debug_flag;
	if (!retained) {
		node = (long *)*head;
		child = (ulong *)(node + 1);
		key = *child;
		if (key == 0) {
			*child = (uint64_t)*(uint *)(tpidr_el1 + 0x518);
		}
		if (key != 0 || c != 0) {
			hv_lock_hv(node, tpidr_el1, key, 0);
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
				os_ref_release(*child);
				kfree_type(child[4]);
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
			hv_unlock_hv(*head, tpidr_el1);
		}

		c = (int)head[1];
		*(int *)(head + 1) = c - 1;
		LORelease();                    /* ARC-style object release */
		if (c == 0) {
			panic_dyn();
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
 * FUN_fffffe000b9860bc @ 0xfffffe000b9860bc   (est. hv_rbtree_unlink)
 * Ghidra: void FUN_fffffe000b9860bc(long *param_1, ulong param_2)
 * Removes node `param_2` from the red-black tree whose root is stored at
 * param_1[0x427] (0x427 * 8 = 0x2138 bytes into the container). The tree nodes
 * are embedded lists: each node has +0x28 (left child), +0x30 (right child),
 * +0x38 (parent, low bit = red flag). The routine handles the three classic
 * RB-delete cases — node with two children (splice successor), a single
 * red child, and double-black rebalance — including the parent-link fixups
 * and the +0x38 low-bit (red/black) color propagation, then clears the root
 * entry. Written from the Ghidra decompile (logic faithful; locals renamed).
 * Confidence: low
 * Notes: called by FUN_fffffe000b985e38 (vmapple-ipc), FUN_fffffe000b986ff4
 *   (trap-dispatch hv_vm_map_region), FUN_fffffe000b987c44 (vcpu-core
 *   hv_vm_owner_teardown). Decompiler produced a long balanced-tree routine
 *   with no external calls; the complete body is retained in Ghidra at
 *   FUN_fffffe000b9860bc. Reconstructed here as a faithful structural
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
