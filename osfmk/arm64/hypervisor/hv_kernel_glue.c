/* Recreated from kernelcache.arm64.kc (xnu-12377.121.10 RELEASE_ARM64_T8142, image base fffffe0007004000). Ground truth: Ghidra FUN_ names + addresses; all names are estimates. */

/*
 * hv_kernel_glue.c — direct kernel-dependency interface for the hypervisor.
 *
 * Owned by the hv-deps tree.
 *
 * Per the FULL-AUDIT rule in AGENTS.md (branch scope decision 2026-08-11):
 * kernel functions the hypervisor calls DIRECTLY (its touch set) are recreated
 * with bodies here where they are hypervisor-glue or small/self-contained;
 * universal XNU core primitives (mutex, refcount, zalloc/zfree, waitq,
 * per-CPU/task accessors, copyin/copyout, DT/boot-arg parsers) are shared by
 * the ENTIRE kernel, not just the hypervisor, and recreating them would be
 * recreating core XNU. Those are declared as externs with the Ghidra address
 * noted and left NOT recreated (consistent with the chain-map stubbing rule).
 *
 * Bodies recreated here (direct callees of hv code, small enough to audit):
 *   current_task   FUN_fffffe000b8663e8
 *   waitq_validate FUN_fffffe000b78fb24
 *   hv_object_lookup FUN_fffffe000b7e0d8c
 *
 * Direct callees of the vmapple-ipc tree functions:
 *   - FUN_fffffe000b866ec4 (est. current_cpu_datap) : per-CPU struct getter.
 *       Decompiler shows a noreturn panic stub (body PAC'd / removed by the
 *       decompiler) — NOT recreatable, used by the whole kernel. Extern.
 *   - FUN_fffffe000b8663e8 (est. current_task) : validates + returns the
 *       current task from a per-CPU pointer (checks the task is a live task
 *       zone object; returns 0 unless the is-task bit is set). Shared kernel.
 *   - FUN_fffffe000b7f0afc / b7f1e80 (lck_mtx_lock / lck_mtx_unlock) :
 *       XNU mutex acquire/release on DAT_fffffe000c62c0b8 (the hv lock).
 *       Full futex/waitq mutex implementation — universal kernel core. Extern.
 *   - FUN_fffffe000b8afa78 (os_release) : ARC-style object refcount release.
 *   - FUN_fffffe000b793cf4 (zfree / object release w/ waitq) : zone free.
 *   - FUN_fffffe000b862b6c (refcount hash dec) : refcount decrement + free.
 *   - FUN_fffffe000b78fb24 (waitq validation) : wait queue registration check.
 *   - FUN_fffffe000b7e0d8c (container lookup by handle/type) : hypervisor
 *       object registry lookup (0x2d type); decompiled in hv_vmapple.c notes.
 *   - FUN_fffffe000b98533c (est. hv_vcpu_object_release) : vcpu-core tree.
 *   - FUN_fffffe000b9860bc (est. hv_rbtree_unlink) : RB-tree rebalance/unlink
 *       used by hv container teardown; hypervisor-internal, shared by
 *       vmapple-ipc / trap-dispatch / vcpu-core (owned via shared-utils).
 */

#include "hv_kernel_glue.h"

/* Universal XNU core primitives — shared kernel, NOT recreated. */
extern void *current_cpu_datap(uint64_t cpu); /* FUN_fffffe000b866ec4; per-CPU getter (decompiler panic-stub) */
extern void *current_task(void *);      /* FUN_fffffe000b8663e8; task getter (body recreated below) */
extern void  lck_mtx_lock(void *, void *, uint64_t, int);   /* FUN_fffffe000b7f0afc; hv lock DAT_fffffe000c62c0b8 */
extern void  lck_mtx_unlock(void *, void *, uint32_t);      /* FUN_fffffe000b7f1e80 */
extern void  os_release(void *);        /* FUN_fffffe000b8afa78 */
extern void  zfree(void *);             /* FUN_fffffe000b793cf4; zone free w/ waitq */
extern void  refcount_dec(void *, void *);  /* FUN_fffffe000b862b6c */

/* waitq_validate / hv_object_lookup are now bodies below (see hv_kernel_glue.h). */

/* Direct callees of the entitlements-tree functions (hv_entitlements.c):
 *   - FUN_fffffe000b95fe60 (est. cache_type_lookup) : indexes a cache/topology
 *       descriptor table (stride 0xa8) by a cache-type selector; spins on
 *       FUN_fffffe000b812380/812e54/812f5c while the entry is being built.
 *       Used by the CPU-feature report (hv_caps_cpu_report). Universal XNU
 *       cache-topology primitive (7 kernel callers) — extern, NOT recreated.
 *   - FUN_fffffe000c0f8cfc : the credential/sandbox entitlement probe reached
 *       via DAT_fffffe0007e93310 slot +0x1c0; returns 0 when the cred carries
 *       the named entitlement. Universal XNU credential ops primitive (100+
 *       sysctl/ops-table callers) — extern, NOT recreated.
 *   - DAT_fffffe0007e93310 : credential/sandbox ops table (slot +0x1c0 = the
 *       entitlement probe above). Shared kernel data. */
extern long  cache_type_lookup(int idx);   /* FUN_fffffe000b95fe60; universal cache-topology */
extern int   cred_has_entitlement(void *cred, const char *entitlement); /* FUN_fffffe000c0f8cfc */
extern uintptr_t cred_ops[];   /* credential/sandbox ops table */

/*
 * Current-task getter — validated task pointer from a per-CPU credential.
 *   FUN_fffffe000b8663e8 @ 0xfffffe000b8663e8   (est. current_task)
 * Ghidra: ulong FUN_fffffe000b8663e8(long param_1)
 * Computes the task object's offset from the task-zone base
 * (DAT_fffffe000c5c5bb0), asserts the pointer is a live task-zone object
 * (magic/size check, panic FUN_fffffe000c0eae24(0x19) otherwise), and returns
 * the task pointer only when the task's flags at +0x420 have the is-task bit
 * (0x800000) set; otherwise returns 0.
 * Confidence: high
 * Notes: DAT_fffffe000c5c5bb0 = task-zone base; DAT_fffffe000c6492c8 = zone
 *   size bound; object magic at (task>>10) entry is validated against 0x19. */
void *
current_task(void *param_1)
{
	uint64_t off;
	void *task;

	off = (uint64_t)param_1 - hv_task_zone_base;
	if (off != 0 &&
	    ((CARRY8(off | 0xf00000000000000, hv_task_zone_size) ||
	      (off | 0xf00000000000000) + hv_task_zone_size != 0) ||
	     (*(uint16_t *)((off >> 10) & 0xffffffff0) & 0x3ff) != 0x19)) {
		panic_dyn(0x19);   /* FUN_fffffe000c0eae24(0x19): not a task-zone object */
	}
	task = 0;
	if ((*(uint32_t *)((uint64_t)param_1 + 0x420) & 0x800000) != 0) {
		task = (void *)off;
	}
	return task;
}

/*
 * Supplementary direct kernel callees of hv code that have no manifest entry of
 * their own in the hv-deps tree but ARE part of the hypervisor's touch set
 * (declared extern in hv_internal.h). All are universal XNU core with 40-100+
 * kernel callers — recreated nowhere per the glue policy; declared here so the
 * audit reader can see the full direct-dependency surface.
 */
extern int  FUN_fffffe000b95c144(void);  /* est. copyin  — user<->kernel copy; 100+ callers */
extern int  FUN_fffffe000b95d6f4(void);  /* est. copyout — user<->kernel copy; 100+ callers */
extern void FUN_fffffe000c0f86a4(void) __attribute__((noreturn)); /* est. panic */
extern void FUN_fffffe000c0f8674(void) __attribute__((noreturn)); /* est. panic */
extern void FUN_fffffe000c0e1c3c(void) __attribute__((noreturn)); /* est. panic (hv_vcpu_attach) */
extern long FUN_fffffe000c09c084(void);  /* est. kernel_dt_node_lookup — device-tree parse; 45 callers */
extern long FUN_fffffe000c09c31c(void);  /* est. kernel_dt_prop_get — device-tree property; 55 callers */
extern long FUN_fffffe000c09cbf0(void);  /* est. kernel_boot_arg_get — boot-arg parse; 100+ callers */
extern long FUN_fffffe000bf77834(void);  /* est. boot_prop_getter — 'vmm-present' (hv_vmm_present) */

/* Stubbed kernel callees of the recreated bodies below (audit boundary:
 * their own internals are 2+ levels into XNU and stay out of scope). */
extern void FUN_fffffe000b7f78ec(uint64_t lock, uint64_t *table); /* waitq lock register */
extern void FUN_fffffe000c0eae24(uint64_t code, ...) __attribute__((noreturn)); /* zone panic */
extern void SoftwareBreakpoint(uint32_t imm, uint64_t addr) __attribute__((noreturn)); /* XNU brk assert */
extern uint16_t *hv_object_type_table;        /* container type table (stride 0x28) */
extern uint64_t *PTR_s_waitq_fffffe0007d7c8f0; /* global waitq registration table */
extern void FUN_fffffe000c0e1cf4(uint64_t *container, uint64_t type); /* container ref */
/* current thread/waitq ctx; Ghidra models the return as a 12-byte struct
 * { qword waitq, dword handle, byte flags } — modeled here as a 16-byte
 * struct for convenience. */
struct hv_waitq_ctx { uint64_t waitq; uint32_t handle; uint32_t flags; };
extern struct hv_waitq_ctx FUN_fffffe000c0e1cbc(void);
extern void FUN_fffffe000b7f7538(uint64_t lock); /* waitq lock release */
extern void FUN_fffffe000b7914c8(void);        /* container notify/free */

/*
 * Waitq-zone object validation — registers a waitq's embedded lock.
 *   FUN_fffffe000b78fb24 @ 0xfffffe000b78fb24   (est. waitq_validate)
 * Ghidra: void FUN_fffffe000b78fb24(ulong param_1)
 * Verifies that `param_1` points at a live waitq-zone object: the zone-header
 * element at (param_1 >> 10) must carry magic 0x15 and the (tagged) address
 * must satisfy the zone-range check; then it registers the waitq's embedded
 * lock at param_1+0x14 against the global waitq registration table
 * (PTR_s_waitq_fffffe0007d7c8f0) via FUN_fffffe000b7f78ec. Any failure falls
 * through to panic FUN_fffffe000c0eae24(0x15, param_1).
 * Direct callee of hv code: FUN_fffffe000b985e38 (hv_ikot_hypervisor_handler)
 * calls it on container teardown; ~130 kernel callers total, but the body is
 * tiny and self-contained, so it is recreated here for audit.
 * Confidence: medium
 * Notes: Ghidra decompiles the zone-range test as the never-true conjunction
 *   `(x < 0xffffffffffffff70) && (x == 0xffffffffffffff70)` — a decompiler
 *   artifact of the tagged-address range check; kept faithfully below. Its
 *   callees FUN_fffffe000b7f78ec (waitq lock register) and FUN_fffffe000c0eae24
 *   (zone panic, noreturn) are kernel and remain stubbed externs. Kernel code
 *   recreated for audit; its own callees remain stubbed. */
void
waitq_validate(uint64_t waitq)
{
	uint64_t tagged;

	tagged = waitq | 0xf00000000000000;
	/* Zone-element magic check on the waitq-zone header slot. */
	if (((tagged < 0xffffffffffffff70) && (tagged == 0xffffffffffffff70)) &&
	    ((*(uint16_t *)((waitq >> 10) & 0xffffffff0) & 0x3ff) == 0x15)) {
		FUN_fffffe000b7f78ec(waitq + 0x14, &PTR_s_waitq_fffffe0007d7c8f0);
		return;
	}
	FUN_fffffe000c0eae24(0x15, waitq);   /* noreturn: not a live waitq-zone object */
}

/*
 * XNU container/object-registry lookup by handle + type.
 *   FUN_fffffe000b7e0d8c @ 0xfffffe000b7e0d8c   (est. hv_object_lookup)
 * Ghidra: ulong FUN_fffffe000b7e0d8c(ulong *param_1,ulong param_2,ulong param_3)
 * Resolves an object inside a container registry: `param_1` = container state
 * (a per-container context), `param_2` = handle, `param_3` = object type.
 * Guards: type must be <= 0x30 and the container's state word must not have the
 * 0x10000 (dead) bit set nor be missing the 0x700 (present) bits — each guard
 * trips a SoftwareBreakpoint(0xbffc) assert. Marks the container busy
 * (*(param_1+2)=1). If handle == -1, or handle matches the container's own id
 * (+0x84) and the slot table (+0x88) is empty, it dequeues the head entry and
 * returns it. Otherwise it takes a reference (FUN_fffffe000c0e1cf4), resolves
 * the current thread/waitq context (FUN_fffffe000c0e1cbc), validates the waitq
 * (waitq_validate, above) and returns 1 when the thread's slot id (+0x84)
 * equals the request handle, else 0. Releases the waitq lock
 * (FUN_fffffe000b7f7538) on return.
 * This is XNU kernel container/object infrastructure (the registry backing the
 * IPC kobject table DAT_fffffe0007d78658, stride 0x28) — NOT hypervisor-owned.
 * The hypervisor calls it directly (FUN_fffffe000b985e38 uses type 0x2d) to
 * resolve its registered kobjects, so per the FULL-AUDIT rule it is recreated
 * here. Its own callees (b7914c8, c0e1cf4, c0e1cbc, b7f7538) remain stubbed.
 * Confidence: medium
 * Notes: DAT_fffffe0007d78658 = container type table (stride 0x28). The
 *   SoftwareBreakpoint(0xbffc) calls are XNU assert/panic brk points with the
 *   assert address encoded in the operand. Kernel code recreated for audit;
 *   its own callees remain stubbed. */
uint64_t
hv_object_lookup(uint64_t *container, uint64_t handle, uint64_t type)
{
	uint64_t obj;
	uint8_t busy;

	if (0x30 < (uint32_t)type) {
		SoftwareBreakpoint(0xbffc, 0xfffffe000b7e0e8c);   /* assert: type > 0x30 */
	}
	if ((*container & 0x10000) != 0) {
		SoftwareBreakpoint(0xbffc, 0xfffffe000b7e0e98);   /* assert: container dead */
	}
	*(uint8_t *)((long)container + 2) = 1;                 /* mark busy */
	if ((*container & 0x700) == 0) {
		SoftwareBreakpoint(0xbffc, 0xfffffe000b7e0ea4);   /* assert: no present bits */
	}
	if (handle == 0xffffffffffffffff) {
		/* Dequeue head when the container's slot table is empty. */
		if ((int)container[0x11] == 0 ||
		    (*(uint16_t *)(&hv_object_type_table + (type & 0xffffffff) * 0x28) & 1) == 0) {
			goto dequeue;
		}
	} else if (handle != *(uint32_t *)((long)container + 0x84)) {
		goto not_found;
	} else if ((int)container[0x11] == 0) {
		goto dequeue;
	}
	FUN_fffffe000c0e1cf4(container, type);                /* take reference */
not_found:
	{
		/* FUN_fffffe000c0e1cbc returns { waitq (qword), handle (dword),
		 * flags (byte) }; waitq = the current thread's waitq, handle = the
		 * request handle the lookup matches against. */
		struct hv_waitq_ctx ctx = FUN_fffffe000c0e1cbc();
		waitq_validate(ctx.waitq);                        /* decompiler drops the arg; validated ptr = ctx.waitq */
		if (((*(uint8_t *)(ctx.waitq + 1) & 7) == 0) || (*(int *)(ctx.waitq + 0x88) != 0)) {
			obj = 0;
		} else {
			obj = (uint64_t)(*(int *)(ctx.waitq + 0x84) == (int)ctx.handle);
		}
		busy = *(uint8_t *)(ctx.waitq + 2);
		if ((busy & 1) != 0) {
			SoftwareBreakpoint(0xbffc, 0xfffffe000b7e0f30); /* assert: double-busy */
		}
		FUN_fffffe000b7f7538(ctx.waitq + 0x14);           /* release waitq lock */
		return obj;
	}
dequeue:
	{
		uint64_t out = container[10];
		container[10] = 0;
		if (container[1] != 0) {
			*(uint64_t *)(container[1] + 8) = 0;
			if ((*container & 0x10000) == 0) {
				SoftwareBreakpoint(0xbffc, 0xfffffe000b7e0eb0); /* assert */
			}
		}
		*(uint8_t *)((long)container + 2) = 0;             /* clear busy */
		FUN_fffffe000b7914c8();                           /* container notify/free */
		return out;
	}
}
