/* Recreated from kernelcache.arm64.kc (xnu-12377.121.10 RELEASE_ARM64_T8142, image base fffffe0007004000). Ground truth: Ghidra FUN_ names + addresses; all names are estimates. */
#include "hv_compat.h"

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
 *   current_task   current_task
 *   waitq_validate waitq_validate
 *   hv_object_lookup hv_object_lookup
 *
 * Direct callees of the vmapple-ipc tree functions:
 *   - current_cpu_datap (est. current_cpu_datap) : per-CPU struct getter.
 *       Decompiler shows a noreturn panic stub (body PAC'd / removed by the
 *       decompiler) — NOT recreatable, used by the whole kernel. Extern.
 *   - current_task (est. current_task) : validates + returns the
 *       current task from a per-CPU pointer (checks the task is a live task
 *       zone object; returns 0 unless the is-task bit is set). Shared kernel.
 *   - lck_mtx_lock / b7f1e80 (lck_mtx_lock / lck_mtx_unlock) :
 *       XNU mutex acquire/release on DAT_fffffe000c62c0b8 (the hv lock).
 *       Full futex/waitq mutex implementation — universal kernel core. Extern.
 *   - os_release (os_release) : ARC-style object refcount release.
 *   - zfree_waitq (zfree / object release w/ waitq) : zone free.
 *   - refcount_dec (refcount hash dec) : refcount decrement + free.
 *   - waitq_validate (waitq validation) : wait queue registration check.
 *   - hv_object_lookup (container lookup by handle/type) : hypervisor
 *       object registry lookup (0x2d type); decompiled in hv_vmapple.c notes.
 *   - hv_vcpu_object_release (est. hv_vcpu_object_release) : vcpu-core tree.
 *   - hv_rbtree_unlink (est. hv_rbtree_unlink) : RB-tree rebalance/unlink
 *       used by hv container teardown; hypervisor-internal, shared by
 *       vmapple-ipc / trap-dispatch / vcpu-core (owned via shared-utils).
 */

#include "hv_kernel_glue.h"

/* Universal XNU core primitives — shared kernel, NOT recreated. */
extern void *per_cpu_base(uint64_t cpu); /* FUN_fffffe000b866ec4; per-CPU getter (decompiler panic-stub) */
extern void *current_task(void *);      /* FUN_fffffe000b8663e8; task getter (body recreated below) */
extern void  os_release(void *);        /* FUN_fffffe000b8afa78 */
extern void  zfree(void *);             /* FUN_fffffe000b793cf4; zone free w/ waitq */
extern void  refcount_dec(void *, void *);  /* FUN_fffffe000b862b6c */

/* waitq_validate / hv_object_lookup are now bodies below (see hv_kernel_glue.h). */

/* Direct callees of the entitlements-tree functions (hv_entitlements.c):
 *   - cache_type_lookup (est. cache_type_lookup) : indexes a cache/topology
 *       descriptor table (stride 0xa8) by a cache-type selector; spins on
 *       FUN_fffffe000b812380/812e54/812f5c while the entry is being built.
 *       Used by the CPU-feature report (hv_caps_cpu_report). Universal XNU
 *       cache-topology primitive (7 kernel callers) — extern, NOT recreated.
 *   - osmeta_reserved_slot_panic (FUN_fffffe000c0f8cfc) : NOT an entitlement
 *       probe (earlier de-guess corrected 2026-08-12). It is an OSMetaClass
 *       reserved-virtual-slot panic stub: `pacibsp; stp; mov x29,sp;
 *       adrp/add x0,#0xfffffe000c680fc8; mov w1,#N; bl c0f7394`; the helper
 *       calls the class's authenticated vtable+0x168 hook then panics
 *       "%s::_RESERVED%s%d called. @%s:%d" (OSMetaClass.cpp line 0x57e=1406).
 *       Shared by 100+ IOKit class vtables' reserved slots — extern, NOT
 *       recreated (deep IOKit, 7-instruction stub).
 *   - DAT_fffffe0007e93310 : the credential/sandbox ops TABLE POINTER slot —
 *       hv_entitlement_tier (b985ae4) calls *(*(0x7e93310)+0x1c0)(task, ent).
 *       The static image value at 0x7e93310 is 0 (boot-time-filled auth
 *       pointer), so the actual probe identity is not statically resolvable. */
extern long  cache_type_lookup(int idx);   /* FUN_fffffe000b95fe60; universal cache-topology */
extern void  osmeta_reserved_slot_panic(void); /* FUN_fffffe000c0f8cfc; reserved-slot panic stub, noreturn via c0f7394 */
extern uintptr_t cred_ops[];   /* boot-filled ops-table pointer slot (static 0); *(*(0x7e93310)+0x1c0) = entitlement probe */

/*
 * Current-task getter — validated task pointer from a per-CPU credential.
 *   current_task @ 0xfffffe000b8663e8   (est. current_task)
 * Ghidra: ulong current_task(long param_1)
 * Computes the task object's offset from the task-zone base
 * (DAT_fffffe000c5c5bb0), asserts the pointer is a live task-zone object
 * (magic/size check, panic zone_panic(0x19) otherwise), and returns
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
		panic_dyn(0x19);   /* zone_panic(0x19): not a task-zone object */
	}
	task = 0;
	if ((*(uint32_t *)((uint64_t)param_1 + 0x420) & 0x800000) != 0) {
		task = (void *)off;
	}
	return task;
}

/* Supplementary direct kernel callees of hv code that have no manifest entry of
 * their own in the hv-deps tree but ARE part of the hypervisor's touch set
 * (declared extern in hv_internal.h). All are universal XNU core with 40-100+
 * kernel callers — recreated nowhere per the glue policy; declared here so the
 * audit reader can see the full direct-dependency surface.
 * (Typed prototypes for copyin/copyout/panics/DT/boot-arg getters live in
 * hv_kernel_glue.h / hv_support.h / hv.h.) */

/* Stubbed kernel callees of the recreated bodies below (audit boundary:
 * their own internals are 2+ levels into XNU and stay out of scope). */
extern void waitq_lock_register(uint64_t lock, uint64_t **table); /* waitq lock register */
extern void zone_panic(uint64_t code, ...) __attribute__((noreturn)); /* zone panic */
extern void SoftwareBreakpoint(uint32_t imm, uint64_t addr) __attribute__((noreturn)); /* XNU brk assert */
extern uint16_t *hv_object_type_table;        /* container type table (stride 0x28) */
extern uint64_t *PTR_s_waitq_fffffe0007d7c8f0; /* global waitq registration table */
extern void container_ref(uint64_t *container, uint64_t type); /* container ref */
/* current thread/waitq ctx; Ghidra models the return as a 12-byte struct
 * { qword waitq, dword handle, byte flags } — modeled here as a 16-byte
 * struct for convenience. */
struct hv_waitq_ctx { uint64_t waitq; uint32_t handle; uint32_t flags; };
extern struct hv_waitq_ctx kernel_waitq_ctx_get(void);
extern void waitq_lock_release(uint64_t lock); /* waitq lock release */
extern void container_notify_free(void);        /* container notify/free */

/*
 * Waitq-zone object validation — registers a waitq's embedded lock.
 *   waitq_validate @ 0xfffffe000b78fb24   (waitq_validate)
 * Ghidra: void waitq_validate(ulong param_1)
 * Verifies that `param_1` points at a live waitq-zone object: the zone-header
 * element at (param_1 >> 10) must carry magic 0x15 and the (tagged) address
 * must satisfy the zone-range check; then it registers the waitq's embedded
 * lock at param_1+0x14 against the global waitq registration table
 * (PTR_s_waitq_fffffe0007d7c8f0) via waitq_lock_register. Any failure falls
 * through to panic zone_panic(0x15, param_1).
 * Direct callee of hv code: hv_ikot_hypervisor_handler (hv_ikot_hypervisor_handler)
 * calls it on container teardown; ~130 kernel callers total, but the body is
 * tiny and self-contained, so it is recreated here for audit.
 * Confidence: high (verified against fresh decompile; faithful).
 * Notes: Ghidra decompiles the zone-range test as the never-true conjunction
 *   `(x < 0xffffffffffffff70) && (x == 0xffffffffffffff70)` — a decompiler
 *   artifact of the tagged-address range check; kept faithfully below. Its
 *   callees waitq_lock_register (waitq lock register) and zone_panic
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
		waitq_lock_register(waitq + 0x14, &PTR_s_waitq_fffffe0007d7c8f0);
		return;
	}
	zone_panic(0x15, waitq);   /* noreturn: not a live waitq-zone object */
}

/*
 * XNU container/object-registry lookup by handle + type.
 *   hv_object_lookup @ 0xfffffe000b7e0d8c   (hv_object_lookup)
 * Ghidra: ulong hv_object_lookup(ulong *param_1,ulong param_2,ulong param_3)
 * Resolves an object inside a container registry: `param_1` = container state
 * (a per-container context), `param_2` = handle, `param_3` = object type.
 * Guards: type must be <= 0x30 and the container's state word must not have the
 * 0x10000 (dead) bit set nor be missing the 0x700 (present) bits — each guard
 * trips a SoftwareBreakpoint(0xbffc) assert. Marks the container busy
 * (*(param_1+2)=1). If handle == -1, or handle matches the container's own id
 * (+0x84) and the slot table (+0x88) is empty, it dequeues the head entry and
 * returns it. Otherwise it takes a reference (container_ref), resolves
 * the current thread/waitq context (kernel_waitq_ctx_get), validates the waitq
 * (waitq_validate, above) and returns 1 when the thread's slot id (+0x84)
 * equals the request handle, else 0. Releases the waitq lock
 * (waitq_lock_release) on return.
 * This is XNU kernel container/object infrastructure (the registry backing the
 * IPC kobject table DAT_fffffe0007d78658, stride 0x28) — NOT hypervisor-owned.
 * The hypervisor calls it directly (hv_ikot_hypervisor_handler uses type 0x2d) to
 * resolve its registered kobjects, so per the FULL-AUDIT rule it is recreated
 * here. Its own callees (b7914c8, c0e1cf4, c0e1cbc, b7f7538) remain stubbed.
 * Confidence: high (verified against fresh decompile; faithful).
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
	container_ref(container, type);                /* take reference */
not_found:
	{
		/* FUN_fffffe000c0e1cbc returns { waitq (qword), handle (dword),
		 * flags (byte) }; waitq = the current thread's waitq, handle = the
		 * request handle the lookup matches against. */
		struct hv_waitq_ctx ctx = kernel_waitq_ctx_get();
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
		waitq_lock_release(ctx.waitq + 0x14);           /* release waitq lock */
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
		container_notify_free();                           /* container notify/free */
		return out;
	}
}
