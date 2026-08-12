/* Recreated from kernelcache.arm64.kc (xnu-12377.121.10 RELEASE_ARM64_T8142, image base fffffe0007004000). Ground truth: Ghidra FUN_ names + addresses; all names are estimates. */

/*
 * hv_kernel_glue.c — direct kernel-dependency declarations for the hypervisor.
 *
 * Owned by the hv-deps tree.
 *
 * Per the branch scope decision (2026-08-11): kernel functions the hypervisor
 * calls DIRECTLY are recreated with bodies where they are hypervisor-glue or
 * small/self-contained; universal XNU core primitives (mutex, refcount,
 * zalloc/zfree, waitq, per-CPU/task accessors) are shared by the ENTIRE
 * kernel, not just the hypervisor, and recreating them would be recreating
 * core XNU. Those are declared here as externs with the Ghidra address noted,
 * and left NOT recreated (consistent with the chain-map stubbing rule).
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

/* Universal XNU core primitives — shared kernel, NOT recreated. */
extern void *current_cpu_datap(void);   /* FUN_fffffe000b866ec4; per-CPU getter (decompiler panic-stub) */
extern void *current_task(void *);      /* FUN_fffffe000b8663e8; task getter (body recreated below) */
extern void  lck_mtx_lock(void *, void *, uint64_t, int);   /* FUN_fffffe000b7f0afc; hv lock DAT_fffffe000c62c0b8 */
extern void  lck_mtx_unlock(void *, void *, uint32_t);      /* FUN_fffffe000b7f1e80 */
extern void  os_release(void *);        /* FUN_fffffe000b8afa78 */
extern void  zfree(void *);             /* FUN_fffffe000b793cf4; zone free w/ waitq */
extern void  refcount_dec(void *, void *);  /* FUN_fffffe000b862b6c */
extern void  waitq_validate(void *);    /* FUN_fffffe000b78fb24 */
extern uint64_t hv_object_lookup(void *, uint64_t, uint64_t); /* FUN_fffffe000b7e0d8c */

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
extern uintptr_t DAT_fffffe0007e93310[];   /* credential/sandbox ops table */

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

	off = (uint64_t)param_1 - DAT_fffffe000c5c5bb0;
	if (off != 0 &&
	    ((CARRY8(off | 0xf00000000000000, DAT_fffffe000c6492c8) ||
	      (off | 0xf00000000000000) + DAT_fffffe000c6492c8 != 0) ||
	     (*(uint16_t *)((off >> 10) & 0xffffffff0) & 0x3ff) != 0x19)) {
		panic_dyn(0x19);   /* FUN_fffffe000c0eae24(0x19): not a task-zone object */
	}
	task = 0;
	if ((*(uint32_t *)((uint64_t)param_1 + 0x420) & 0x800000) != 0) {
		task = (void *)off;
	}
	return task;
}
