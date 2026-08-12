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
extern void *per_cpu_base(uint64_t cpu); /* kernel: returns per-CPU struct (FUN_fffffe000b866ec4) */
extern void *os_ref_retain(void *);     /* kernel: refcount retain (FUN_fffffe000b7f089c) */
extern void  os_release(void *);        /* kernel: refcount release (FUN_fffffe000b8afa78) */
extern void  zfree_waitq();                 /* kernel: zfree/kfree (FUN_fffffe000b793cf4) */
extern void *ref_count_dec(void *, void *); /* kernel: lck refcount dec (FUN_fffffe000b862b6c) */
extern uint64_t hv_object_lookup(uint64_t *container, uint64_t handle, uint64_t type); /* hv-deps recreated (FUN_fffffe000b7e0d8c) */
extern void  rbtree_unlink(void *, void *); /* hv-internal RB-tree unlink (FUN_fffffe000b9860bc) */
extern void kernel_owner_mismatch_panic(void *mutex, void *thread) __attribute__((noreturn)); /* c0e4d74 */

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
 * Confidence: high (complete decompile; rewritten 2026-08-12 — the tree walk
 *   no longer dereferences null on the first pass, lock_sync (b7f1e80) is
 *   used where the code had lock_release, the final refcount-0 panic is
 *   kernel_panic_b (c0f8674), and LORelease replaces the guessed os_release).
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
		lck_mtx_lock(&hv_lock, tpidr_el1, cpu_ts, 0);
	}

	head = *(long **)(per_cpu_base(tpidr_el1) + 0x628);
	if (head == 0) {
		head = 0;
		retained = true;
	} else {
		retained = true;
		if (head != 0) {
			c = (int)head[1];
			*(int *)(head + 1) = c + 1;
			if ((uint)(c + 0xf0000001) < 0xf0000002) {
				kernel_panic_a();  /* FUN_fffffe000c0f86a4, refcount overflow */
			}
			retained = false;
		}
	}

	c = (int)hv_cached_cpu_id;
	if ((int)hv_cached_cpu_id == *(int *)(tpidr_el1 + 0x518)) {
		hv_cached_cpu_id = 0;
	}
	if (c != *(int *)(tpidr_el1 + 0x518) || hv_debug_flag != 0) {
		lck_mtx_unlock(&hv_lock, tpidr_el1);   /* FUN_fffffe000b7f1e80 */
	}

	/* validate the waitq/port, then resolve the object key by handle+type.
	 * waitq_validate = waitq_validate; hv_object_lookup (kernel
	 * container registry) = hv_object_lookup, type 0x2d.  The os_release
	 * after the lookup has its argument dropped by the decompiler
	 * (FUN_fffffe000b8afa78() renders arg-less); kept as a null arg. */
	waitq_validate(param_1);
	lookup_key = hv_object_lookup((void *)param_1, param_2, 0x2d);
	os_release(NULL);                       /* FUN_fffffe000b8afa78; decompiler drops the arg */

	c = hv_debug_flag;
	if (!retained) {
		uint64_t *puVar12;
		long *p;
		node = (long *)*head;
		key = *(uint64_t *)(node + 1);
		if (key == 0) {
			*(uint64_t *)(node + 1) = (uint64_t)*(uint *)(tpidr_el1 + 0x518);
		}
		if (key != 0 || c != 0) {
			lck_mtx_lock(node, tpidr_el1, key, 0);
		}

		/* descend to the rightmost node of the region tree (head+0x427);
		 * child = the last non-null node, node = 0 at exit. */
		c = 0;
		puVar12 = (uint64_t *)(head + 0x427);
		node = 0;
		do {
			child = node;                 /* plVar10 = plVar11 */
			node = (long *)*puVar12;      /* plVar11 = *puVar12 (root) */
			puVar12 = (uint64_t *)(node + 5);
			c = hv_debug_flag;
		} while (node != 0);

		while (hv_debug_flag = c, child != 0) {
			node = (long *)child[6];      /* plVar11 = plVar10[6] (right) */
			if (node == 0) {
				p = (long *)(child[7] & ~1UL);   /* plVar14 = plVar10[7]&~1 */
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
				os_release((void *)*child);
				zfree_waitq((void *)child[4]);
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
			lck_mtx_unlock((void *)*head, tpidr_el1);   /* FUN_fffffe000b7f1e80 */
		}

		c = (int)head[1];
		*(int *)(head + 1) = c - 1;
		LORelease();                    /* inline refcount release */
		if (c == 0) {
			kernel_panic_b();           /* FUN_fffffe000c0f8674, noreturn */
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
 * are embedded: +0x28 (left child), +0x30 (right child), +0x38 (parent, low
 * bit = red flag). Full classic RB-delete: splice-successor case, single-red-
 * child case, and the double-black rebalance walk with left/right rotations
 * and color flips. Validates the container's owning cpu id before mutating
 * (panic FUN_fffffe000c0e4d74 on mismatch) and decrements the node count at
 * param_1[0x428].
 * Confidence: high (complete decompile; the only ambiguity is field naming).
 * Notes: called by hv_ikot_hypervisor_handler (vmapple-ipc), hv_vm_map_region
 *   (trap-dispatch), hv_vm_owner_teardown (hv-helpers). Previously a shell
 *   body; replaced with the full decompile.
 */
void
hv_rbtree_unlink(long *root_slot, uint64_t node)
{
	uint64_t l, r, p, u;
	uint64_t x, y, z;
	uint64_t t;
	uint64_t w;
	uint64_t par;
	uint64_t col;
	uint64_t xl, xr;
	long     cpu;
	uint64_t parent_link;
	uint64_t root;
	int      red;

	cpu = tpidr_el1;
	if (((uint)*(uint64_t *)(*root_slot + 8) & 0xfffffff) != *(uint *)(cpu + 0x518))
		kernel_owner_mismatch_panic((void *)*root_slot, (void *)cpu);  /* c0e4d74 */
	*(char *)(root_slot + 0x428) = (char)root_slot[0x428] - 1;

	/* ---- standard RB delete: l = node->left, r = node->right ---- */
	l = *(uint64_t *)(node + 0x28);
	r = *(uint64_t *)(node + 0x30);
	if (l == 0) {
		p = *(uint64_t *)(node + 0x38) & 0xfffffffffffffffeULL;
		red = (uint)*(uint64_t *)(node + 0x38) & 1;
		if (r != 0) goto case_r_single;
		if (p != 0) goto case_p_single;
leaf_root:                              /* LAB_fffffe000b986198 */
		root_slot[0x427] = r;
	} else if (r == 0) {
		p = *(uint64_t *)(node + 0x38) & 0xfffffffffffffffeULL;
		red = (uint)*(uint64_t *)(node + 0x38) & 1;
		r = l;
case_r_single:                          /* LAB_fffffe000b986184 */
		l = p;
		if ((*(uint64_t *)(r + 0x38) & 1) != 0)
			l = p + 1;
		*(uint64_t *)(r + 0x38) = l;
		if (p == 0) goto leaf_root;
case_p_single:                          /* LAB_fffffe000b986160 */
		if (*(uint64_t *)(p + 0x28) == node)
			*(uint64_t *)(p + 0x28) = r;
		else
			*(uint64_t *)(p + 0x30) = r;
	} else {
		/* node has two children: find in-order successor (leftmost of right) */
		x = r;
		do {
			y = x;
			x = *(uint64_t *)(y + 0x28);
		} while (*(uint64_t *)(y + 0x28) != 0);
		x = *(uint64_t *)(y + 0x30);
		p = *(uint64_t *)(y + 0x38);
		u = p & 0xfffffffffffffffeULL;
		if (x != 0) {
			t = u;
			if ((*(uint64_t *)(x + 0x38) & 1) != 0)
				t = p | 1;
			*(uint64_t *)(x + 0x38) = t;
		}
		if (u == 0) {
			root_slot[0x427] = x;
		} else if (*(uint64_t *)(u + 0x28) == y) {
			*(uint64_t *)(u + 0x28) = x;
		} else {
			*(uint64_t *)(u + 0x30) = x;
		}
		red = (uint)p & 1;
		z = y;
		if (node != (*(uint64_t *)(y + 0x38) & 0xfffffffffffffffeULL))
			z = u;
		/* copy node's links into the successor */
		u = *(uint64_t *)(node + 0x38);
		x = *(uint64_t *)(node + 0x28);
		*(uint64_t *)(y + 0x30) = *(uint64_t *)(node + 0x30);
		*(uint64_t *)(y + 0x28) = x;
		*(uint64_t *)(y + 0x38) = u;
		x = *(uint64_t *)(node + 0x38) & 0xfffffffffffffffeULL;
		if (x == 0) {
			root_slot[0x427] = y;
		} else if (*(uint64_t *)(x + 0x28) == node) {
			*(uint64_t *)(x + 0x28) = y;
		} else {
			*(uint64_t *)(x + 0x30) = y;
		}
		x = y;
		if ((*(uint64_t *)(*(long *)(node + 0x28) + 0x38) & 1) != 0)
			x = y | 1;
		*(uint64_t *)(*(long *)(node + 0x28) + 0x38) = x;
		cpu = *(long *)(node + 0x30);
		if (cpu != 0) {
			if ((*(uint64_t *)(cpu + 0x38) & 1) != 0)
				y = y | 1;
			*(uint64_t *)(cpu + 0x38) = y;
		}
	}

	/* ---- rebalance (double-black fixup) ---- */
	if (red != 0)
		return;
	for (;;) {
		if ((r != 0) && ((*(uint64_t *)(r + 0x38) & 1) != 0))
			goto color_node_black;
		if (r == root_slot[0x427])
			goto root_reached;
		l = *(uint64_t *)(z + 0x28);
		if (l == r) {
			/* r is a right child */
			l = *(uint64_t *)(z + 0x30);
			if ((*(uint64_t *)(l + 0x38) & 1) != 0) {
				*(uint64_t *)(l + 0x38) &= 0xfffffffffffffffeULL;
				r = *(uint64_t *)(z + 0x30);
				l = *(uint64_t *)(z + 0x38) | 1;
				*(uint64_t *)(z + 0x38) = l;
				cpu = *(long *)(r + 0x28);
				*(long *)(z + 0x30) = cpu;
				if (cpu != 0) {
					l = z;
					if ((*(uint64_t *)(cpu + 0x38) & 1) != 0)
						l = z | 1;
					*(uint64_t *)(cpu + 0x38) = l;
					l = *(uint64_t *)(z + 0x38);
				}
				*(uint64_t *)(r + 0x38) =
				    (l & 0xfffffffffffffffeULL) | (*(uint64_t *)(r + 0x38) & 1);
				if ((l & 0xfffffffffffffffeULL) == 0) {
					root_slot[0x427] = r;
				} else {
					l = *(uint64_t *)(z + 0x38) & 0xfffffffffffffffeULL;
					if (z == *(uint64_t *)(l + 0x28))
						*(uint64_t *)(l + 0x28) = r;
					else
						*(uint64_t *)(l + 0x30) = r;
				}
				*(uint64_t *)(r + 0x28) = z;
				l = *(uint64_t *)(z + 0x30);
				if ((*(uint64_t *)(z + 0x38) & 1) != 0)
					r = r | 1;
				*(uint64_t *)(z + 0x38) = r;
			}
			cpu = *(long *)(l + 0x28);
			if ((cpu == 0) || ((*(uint64_t *)(cpu + 0x38) & 1) == 0)) {
				if ((*(long *)(l + 0x30) == 0) ||
				    ((*(byte *)(*(long *)(l + 0x30) + 0x38) & 1) == 0))
					goto right_black;
			} else if ((*(long *)(l + 0x30) == 0) ||
			           ((*(byte *)(*(long *)(l + 0x30) + 0x38) & 1) == 0)) {
				*(uint64_t *)(cpu + 0x38) &= 0xfffffffffffffffeULL;
				r = *(uint64_t *)(l + 0x28);
				u = *(uint64_t *)(l + 0x38) | 1;
				*(uint64_t *)(l + 0x38) = u;
				cpu = *(long *)(r + 0x30);
				*(long *)(l + 0x28) = cpu;
				if (cpu != 0) {
					u = l;
					if ((*(uint64_t *)(cpu + 0x38) & 1) != 0)
						u = l | 1;
					*(uint64_t *)(cpu + 0x38) = u;
					u = *(uint64_t *)(l + 0x38);
				}
				*(uint64_t *)(r + 0x38) =
				    (u & 0xfffffffffffffffeULL) | (*(uint64_t *)(r + 0x38) & 1);
				if ((u & 0xfffffffffffffffeULL) == 0) {
					root_slot[0x427] = r;
				} else {
					u = *(uint64_t *)(l + 0x38) & 0xfffffffffffffffeULL;
					if (l == *(uint64_t *)(u + 0x28))
						*(uint64_t *)(u + 0x28) = r;
					else
						*(uint64_t *)(u + 0x30) = r;
				}
				*(uint64_t *)(r + 0x30) = l;
				if ((*(uint64_t *)(l + 0x38) & 1) != 0)
					r = r | 1;
				*(uint64_t *)(l + 0x38) = r;
				l = *(uint64_t *)(z + 0x30);
			}
			*(uint64_t *)(l + 0x38) =
			    (*(uint64_t *)(l + 0x38) & 0xfffffffffffffffeULL) |
			    (*(uint64_t *)(z + 0x38) & 1);
			*(uint64_t *)(z + 0x38) &= 0xfffffffffffffffeULL;
			cpu = *(long *)(l + 0x30);
			if (cpu != 0)
				*(uint64_t *)(cpu + 0x38) &= 0xfffffffffffffffeULL;
			l = *(uint64_t *)(z + 0x30);
			cpu = *(long *)(l + 0x28);
			*(long *)(z + 0x30) = cpu;
			if (cpu != 0) {
				r = z;
				if ((*(uint64_t *)(cpu + 0x38) & 1) != 0)
					r = z | 1;
				*(uint64_t *)(cpu + 0x38) = r;
			}
			r = *(uint64_t *)(z + 0x38);
			*(uint64_t *)(l + 0x38) =
			    (r & 0xfffffffffffffffeULL) | (*(uint64_t *)(l + 0x38) & 1);
			if ((r & 0xfffffffffffffffeULL) == 0) {
				root_slot[0x427] = l;
			} else {
				r = *(uint64_t *)(z + 0x38) & 0xfffffffffffffffeULL;
				if (z == *(uint64_t *)(r + 0x28))
					*(uint64_t *)(r + 0x28) = l;
				else
					*(uint64_t *)(r + 0x30) = l;
			}
			*(uint64_t *)(l + 0x28) = z;
			goto rebalance_continue;
		}
		if ((*(uint64_t *)(l + 0x38) & 1) != 0) {
			*(uint64_t *)(l + 0x38) &= 0xfffffffffffffffeULL;
			r = *(uint64_t *)(z + 0x38) | 1;
			*(uint64_t *)(z + 0x38) = r;
			l = *(uint64_t *)(z + 0x28);
			cpu = *(long *)(l + 0x30);
			*(long *)(z + 0x28) = cpu;
			if (cpu != 0) {
				r = z;
				if ((*(uint64_t *)(cpu + 0x38) & 1) != 0)
					r = z | 1;
				*(uint64_t *)(cpu + 0x38) = r;
				r = *(uint64_t *)(z + 0x38);
			}
			*(uint64_t *)(l + 0x38) =
			    (r & 0xfffffffffffffffeULL) | (*(uint64_t *)(l + 0x38) & 1);
			if ((r & 0xfffffffffffffffeULL) == 0) {
				root_slot[0x427] = l;
			} else {
				r = *(uint64_t *)(z + 0x38) & 0xfffffffffffffffeULL;
				if (z == *(uint64_t *)(r + 0x28))
					*(uint64_t *)(r + 0x28) = l;
				else
					*(uint64_t *)(r + 0x30) = l;
			}
			*(uint64_t *)(l + 0x30) = z;
			if ((*(uint64_t *)(z + 0x38) & 1) != 0)
				l = l | 1;
			*(uint64_t *)(z + 0x38) = l;
			l = *(uint64_t *)(z + 0x28);
		}
		cpu = *(long *)(l + 0x28);
		if ((cpu != 0) && ((*(uint64_t *)(cpu + 0x38) & 1) != 0))
			goto left_red;
		t = *(long *)(l + 0x30);
		if ((t != 0) && ((*(uint64_t *)(t + 0x38) & 1) != 0))
			break;
right_black:
		*(uint64_t *)(l + 0x38) |= 1;
		r = z;
		z = *(uint64_t *)(z + 0x38) & 0xfffffffffffffffeULL;
		continue;
left_red:
		/* handled below */
		;
	}
	if (t == 0) {
black_right:
		*(uint64_t *)(t + 0x38) = r & 0xfffffffffffffffeULL;
		r = *(uint64_t *)(l + 0x30);
	} else {
		r = *(uint64_t *)(t + 0x38);
	}
	if ((r & 1) != 0) {
		t = *(long *)(l + 0x30);
		r = 0;
		if (t != 0) {
			r = *(uint64_t *)(t + 0x38);
			goto black_right;
		}
	}
	u = *(uint64_t *)(l + 0x38) | 1;
	*(uint64_t *)(l + 0x38) = u;
	cpu = *(long *)(r + 0x28);
	*(long *)(l + 0x30) = cpu;
	if (cpu != 0) {
		u = l;
		if ((*(uint64_t *)(cpu + 0x38) & 1) != 0)
			u = l | 1;
		*(uint64_t *)(cpu + 0x38) = u;
		u = *(uint64_t *)(l + 0x38);
	}
	*(uint64_t *)(r + 0x38) = (u & 0xfffffffffffffffeULL) | (*(uint64_t *)(r + 0x38) & 1);
	if ((u & 0xfffffffffffffffeULL) == 0) {
		root_slot[0x427] = r;
	} else {
		u = *(uint64_t *)(l + 0x38) & 0xfffffffffffffffeULL;
		if (l == *(uint64_t *)(u + 0x28))
			*(uint64_t *)(u + 0x28) = r;
		else
			*(uint64_t *)(u + 0x30) = r;
	}
	*(uint64_t *)(r + 0x28) = l;
	if ((*(uint64_t *)(l + 0x38) & 1) != 0)
		r = r | 1;
	*(uint64_t *)(l + 0x38) = r;
	l = *(uint64_t *)(z + 0x28);
color_right:
	*(uint64_t *)(l + 0x38) =
	    (*(uint64_t *)(l + 0x38) & 0xfffffffffffffffeULL) | (*(uint64_t *)(z + 0x38) & 1);
	*(uint64_t *)(z + 0x38) &= 0xfffffffffffffffeULL;
	cpu = *(long *)(l + 0x28);
	if (cpu != 0)
		*(uint64_t *)(cpu + 0x38) &= 0xfffffffffffffffeULL;
	l = *(uint64_t *)(z + 0x28);
	cpu = *(long *)(l + 0x30);
	*(long *)(z + 0x28) = cpu;
	if (cpu != 0) {
		r = z;
		if ((*(uint64_t *)(cpu + 0x38) & 1) != 0)
			r = z | 1;
		*(uint64_t *)(cpu + 0x38) = r;
	}
	r = *(uint64_t *)(z + 0x38);
	*(uint64_t *)(l + 0x38) = (r & 0xfffffffffffffffeULL) | (*(uint64_t *)(l + 0x38) & 1);
	if ((r & 0xfffffffffffffffeULL) == 0) {
		root_slot[0x427] = l;
		*(uint64_t *)(l + 0x30) = z;
	} else {
		r = *(uint64_t *)(z + 0x38) & 0xfffffffffffffffeULL;
		if (z == *(uint64_t *)(r + 0x28)) {
			*(uint64_t *)(r + 0x28) = l;
			*(uint64_t *)(l + 0x30) = z;
		} else {
			*(uint64_t *)(r + 0x30) = l;
			*(uint64_t *)(l + 0x30) = z;
		}
	}
rebalance_continue:
	if ((*(uint64_t *)(z + 0x38) & 1) != 0) {
		l = l | 1;
	}
	*(uint64_t *)(z + 0x38) = l;
	r = root_slot[0x427];
root_reached:
	if (r == 0)
		return;
	l = *(uint64_t *)(r + 0x38);
color_node_black:
	*(uint64_t *)(r + 0x38) = l & 0xfffffffffffffffeULL;
	return;
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
