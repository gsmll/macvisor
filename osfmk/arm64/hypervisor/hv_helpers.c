/* Recreated from kernelcache.arm64.kc (xnu-12377.121.10 RELEASE_ARM64_T8142, image base fffffe0007004000). Ground truth: Ghidra FUN_ names + addresses; all names are estimates. */

/*
 * hv_helpers.c — hypervisor-owned helpers and the EL1 guest-exit handlers.
 *
 * Owned by the hv-helpers tree. Previously these were shimmed as shared
 * kernel; decompilation (this file) shows they are hypervisor behavior or
 * the EL1 exception handlers the guest-exit path erets into. Each body is
 * faithful to the Ghidra decompile; kernel callees remain stubbed externs.
 */

#include "hv_helpers.h"
#include "hv_el2.h"   /* hv_el2_guest_exc_check / hv_el2_guest_fiq / hv_el2_guest_irq /
                       * hv_el2_exception_exit / hv_el2_preemption_panic */

/* ---- kernel helpers used by these bodies (declared, NOT recreated) ---- */
extern void kernel_free_pair(long zone, long slot);       /* FUN_fffffe000b7f007c */
extern void kernel_lock_magic_cleanup(uint32_t magic);    /* FUN_fffffe000b840ae4 */
extern uint64_t hv_cpu_count;                             /* DAT_fffffe0007d7ca20 */
extern void kernel_broadcast_finish(long head, long tail, long data, uint16_t size); /* FUN_fffffe000b85d440 */
extern void waitq_lock_register(uint64_t lock, uint64_t **table);   /* FUN_fffffe000b7f78ec */
extern uint64_t *PTR_s_waitq_fffffe0007d7c8f0;
extern void kernel_lock_slow_acquire(uint32_t *lock, uint64_t a, uint64_t b, uint32_t c, uint64_t d); /* FUN_fffffe000b8547cc */
extern void kernel_debug_reg_write(uint64_t slot, unsigned char reg);  /* FUN_fffffe000c0d994c */
extern void debug_exceptions_disable(int restore);        /* FUN_fffffe000b968948 */
extern long kernel_ipc_send(long port, uint64_t msg, uint64_t *out);   /* FUN_fffffe000b7968e8 */
extern long kernel_ipc_complete(long port, uint64_t msg, uint64_t out);/* FUN_fffffe000b7976a4 */
extern void kernel_ipc_panic(uint64_t msg, uint64_t a, uint64_t b) __attribute__((noreturn)); /* FUN_fffffe000c0e0b28 */
extern long kernel_queue_alloc(long cpu, long a, uint64_t flags);      /* FUN_fffffe000b85e2e8 */
extern uint64_t kernel_queue_fallback(long cpu, long buf, uint64_t flags); /* FUN_fffffe000b85e858 */
extern void kernel_tlb_flush(void);                       /* FUN_fffffe000b96c6d4 */
extern void kernel_time_delta(uint64_t ns, uint8_t *out); /* FUN_fffffe000b9717a4 */
extern void kernel_panic_b(void) __attribute__((noreturn));            /* FUN_fffffe000c0f1874 */
extern void kernel_panic_msg_fmt(const char *fmt, ...) __attribute__((noreturn)); /* FUN_fffffe000c0e11ec */
extern void hv_rbtree_unlink(void *root, void *node);   /* FUN_fffffe000b9860bc, decompiled in hv_vmapple.c */
extern void os_release(void *object);                     /* FUN_fffffe000b8afa78 */
extern void kfree_type(void *obj);                        /* FUN_fffffe000b793cf4 */
extern void refcount_dec(void *ref, void *free_fn);       /* FUN_fffffe000b862b6c */
extern long FUN_fffffe000c0e4c28(void);                   /* est. per-cpu struct */
extern void FUN_fffffe000c0d79b8(long frame, uint64_t esr);            /* est. dtrace probe */
extern void FUN_fffffe000b9627e0(long frame, uint64_t esr, uint64_t far, int guest); /* est. exception dispatch */
extern void FUN_fffffe000b9671b4(void);                   /* est. error handler */
extern uint64_t hv_region_refcount;                       /* DAT_fffffe0007d54078 */
extern uint64_t hv_signal_timeout;                        /* hv_signal_timeout */
extern uint64_t hv_signal_use_table;                      /* hv_signal_use_table */
extern uint32_t *cpu_table_base;                          /* cpu_table_base */
extern char *hv_halt_flag;                                /* hv_halt_flag */
extern long cpu_cur_thread_frame;                         /* est. current thread frame */

/* ------------------------------------------------------------------ *
 * FUN_fffffe000b7f09dc @ 0xfffffe000b7f09dc   (est. hv_vm_pool_release)
 * Ghidra: void FUN_fffffe000b7f09dc(undefined4 *param_1,long param_2)
 * Destroys a lock/mutex object and frees it back to its zone. Validates the
 * lock header (no-waiters state and magic): if the object is unowned
 * (param_1[1] == 0) and the header bytes match the free-lock pattern
 * (byte +3 == '"', word +8 masked == 0, shorts +0xe / +6 == 0), it stamps
 * the magic 0xf0fe2007, zeroes the header, and frees the object via
 * FUN_fffffe000b7f007c(param_2, param_2 + 0x10). If the lock still has
 * waiters it panics "Mutex to destroy still has waiters". Finally it binds
 * the current cpu id into the per-cpu struct and takes the per-cpu lock
 * (FUN_fffffe000b7f0afc) if a cross-cpu flag is pending.
 * Confidence: high (panic string + header validation are unambiguous).
 * Notes: the "Mutex to destroy still has waiters" string @ fffffe00070674e8;
 *   per-cpu struct via FUN_fffffe000c0e4c28; lock FUN_fffffe000b7f0afc;
 *   free FUN_fffffe000b7f007c (kernel). Called by hv_vm_create unwind and
 *   hv_vcpu_object_release as the vm-object lock release.
 * ------------------------------------------------------------------ */
void
hv_vm_pool_release(uint32_t *lock, long zone)
{
	uint64_t u;
	long    l;
	int     i;
	long    cpu;

	if (lock[1] == 0) {
		if ((((*(char *)((long)lock + 3) == '"') &&
		      ((lock[2] & 0x7fffffff) == 0)) &&
		     (*(short *)((long)lock + 0xe) == 0)) &&
		    (*(short *)(lock + 3) == 0)) {
			lock[2] = 0xf0fe2007;          /* est. free-lock magic */
			lock[0] = 0;
			kernel_free_pair(zone, zone + 0x10);  /* FUN_fffffe000b7f007c (kernel) */
			return;
		}
	} else if (*(char *)((long)lock + 3) == '"') {
		kernel_lock_magic_cleanup(lock[2] & 0xfffffff);  /* FUN_fffffe000b840ae4 */
		kernel_panic_msg_fmt("Mutex to destroy still has waiters: %p: <0x%06x 0x%02x 0x%08x 0x%08x/%p 0x%04x 0x%04x> @%s:%d");
	}

	l = FUN_fffffe000c0e4c28();              /* per-cpu struct (kernel) */
	i = (int)hv_debug_flag;                  /* DAT_fffffe000c62b3d0 */
	cpu = tpidr_el1;
	u = *(uint64_t *)(l + 8);
	if (u == 0)
		*(uint64_t *)(l + 8) = *(uint32_t *)(cpu + 0x518);
	if (u == 0 && i == 0)
		return;
	lock_acquire((void *)hv_lock, 0);         /* FUN_fffffe000b7f0afc */
}

/* ------------------------------------------------------------------ *
 * FUN_fffffe000b8627ac @ 0xfffffe000b8627ac   (est. hv_cpu_broadcast)
 * Ghidra: void FUN_fffffe000b8627ac(long *param_1,long param_2)
 * Broadcasts a per-CPU message: reads the list head and a 16-bit size
 * (uVar3) from *param_1 + 0x34, then, for each of DAT_fffffe0007d7ca20
 * entries, copies the size bytes from param_2 into consecutive 0x4000-byte
 * per-CPU slots (FUN_fffffe000b758d80 = copy). Finally invokes
 * FUN_fffffe000b85d440(list, param_1[1], param_2, size) — the actual
 * per-CPU notify.
 * Confidence: medium (copy-to-every-cpu-slot pattern; the target fn is
 *   kernel).
 * Notes: DAT_fffffe0007d7ca20 = cpu count; stride 0x4000 = per-CPU block;
 *   'tco' is toggled around the copy (time-compare override).
 * ------------------------------------------------------------------ */
void
hv_cpu_broadcast(long *list, long data)
{
	long    head;
	long    tail;
	uint16_t size;
	long    cur;
	uint64_t i;

	head = list[0];
	tail = list[1];
	size = *(uint16_t *)(head + 0x34);
	if (hv_cpu_count != 0) {                 /* DAT_fffffe0007d7ca20 */
		i = 0;
		cur = data;
		do {
			tco = 1;
			kernel_copy_src(cur, size);     /* FUN_fffffe000b758d80 */
			tco = 0;
			i++;
			cur += 0x4000;
		} while (i < hv_cpu_count);
	}
	kernel_broadcast_finish(head, tail, data, size);  /* FUN_fffffe000b85d440 (kernel) */
}

/* ------------------------------------------------------------------ *
 * FUN_fffffe000b8563f8 @ 0xfffffe000b8563f8   (est. hv_flush_lock_op)
 * Ghidra: void FUN_fffffe000b8563f8(uint *param_1, ...)
 * Acquires the hypervisor flush lock (DAT_fffffe000c756760, the
 * hv_flush_lock global) with waitq registration. Validates the lock header
 * (byte +5 bit 0), panics if kernel-mode debug exceptions are enabled,
 * raises DAIF (0x1c0) when needed, registers the embedded waitq
 * (FUN_fffffe000b7f78ec) and calls the slow-path acquire
 * FUN_fffffe000b8547cc with the caller flags ORed with 0x10/4.
 * Confidence: high (lock-header validation + DAIF handling are the XNU
 *   lck_mtx_lock pattern).
 * Notes: waitq register FUN_fffffe000b7f78ec; slow path FUN_fffffe000b8547cc.
 * ------------------------------------------------------------------ */
void
hv_flush_lock_op(uint32_t *lock, uint64_t a, uint64_t b, uint32_t c, uint64_t d)
{
	uint64_t u;
	uint64_t daif_val;
	uint32_t flags;

	if ((lock == NULL) || ((*(uint8_t *)((long)lock + 5) & 1) == 0))
		kernel_panic_msg_fmt("invalid hv_flush_lock header");   /* FUN_fffffe000c0e90d4 */
	if ((*lock & 7) - 1 < 2) {
		u = daif;
		if (((uint)u >> 9 & 1) == 0)
			kernel_panic_msg_fmt("%s: debug exceptions enabled in kernel mode @%s:%d");
		if ((~(uint)u & 0x1c0) != 0) {
			daif_val = daif;
			daif = daif_val | 0x1c0;
			flags = 0x10;
			goto do_acquire;
		}
	}
	flags = 0;
do_acquire:
	waitq_lock_register((uint64_t)(lock + 1), &PTR_s_waitq_fffffe0007d7c8f0);  /* FUN_fffffe000b7f78ec */
	kernel_lock_slow_acquire(lock, a, b, c | flags | 4, d);         /* FUN_fffffe000b8547cc */
}

/* ------------------------------------------------------------------ *
 * FUN_fffffe000b954160 @ 0xfffffe000b954160   (est. hv_debug_reg_write)
 * Ghidra: void FUN_fffffe000b954160(long param_1,undefined1 param_2)
 * Writes a hardware debug register for a vm/pmap (called by
 * hv_vm_set_trap_debug, op-table idx14). Validates the pmap is stage-2
 * ("invoked on stage 1 pmap" panic), raises DAIF, writes the register via
 * FUN_fffffe000c0d994c(*(param_1 + 8), param_2), then restores DAIF via
 * debug_exceptions_disable (FUN_fffffe000b968948).
 * Confidence: high (the stage-1-pmap panic identifies the pmap debug path).
 * Notes: FUN_fffffe000c0d994c = kernel debug-reg write; restore
 *   FUN_fffffe000b968948.
 * ------------------------------------------------------------------ */
void
hv_debug_reg_apply(long pmap, unsigned char reg, ...)
{
	uint64_t u;
	uint64_t v;

	if ((*(uint8_t *)(*(long *)(pmap + 0x20) + 0x4c) & 1) == 0)
		kernel_panic_msg_fmt("%s: invoked on stage 1 pmap %p @%s:%d");
	u = daif;
	if (((uint)u >> 9 & 1) != 0) {
		if ((u & 0x1c0) != 0x1c0) {
			v = daif;
			daif = v | 0x1c0;
		}
		kernel_debug_reg_write(*(uint64_t *)(pmap + 8), reg);  /* FUN_fffffe000c0d994c */
		debug_exceptions_disable((u & 0x1c0) != 0x1c0);        /* FUN_fffffe000b968948 */
		return;
	}
	kernel_panic_msg_fmt("%s: debug exceptions enabled in kernel mode @%s:%d");
}

/* ------------------------------------------------------------------ *
 * FUN_fffffe000b7a1dd8 @ 0xfffffe000b7a1dd8   (est. hv_ipc_send)
 * Ghidra: undefined8 FUN_fffffe000b7a1dd8(long param_1,undefined8 param_2)
 * Sends an IPC message on a hypervisor port (est. mach_msg_send path used by
 * hv_vm_map_shared's per-cpu notify). Returns 0x10 (MACH_SEND_INVALID_DEST?)
 * when the port is NULL; otherwise sends via FUN_fffffe000b7968e8 and, on
 * success, receives/completes via FUN_fffffe000b7976a4. A send failure
 * panics via FUN_fffffe000c0e0b28.
 * Confidence: low (IPC shape inferred from port/send/receive triple; the
 *   exact message semantics are not visible here).
 * Notes: FUN_fffffe000b7968e8 (send), FUN_fffffe000b7976a4 (recv/completion),
 *   FUN_fffffe000c0e0b28 (panic) — all kernel.
 * ------------------------------------------------------------------ */
uint64_t
hv_percpu_notify(long port, uint64_t msg)
{
	uint64_t r;
	uint64_t out;

	if (port == 0)
		return 0x10;
	if ((uint32_t)msg - 1U < 0xfffffffe) {
		out = 0;
		r = kernel_ipc_send(port, msg, &out);      /* FUN_fffffe000b7968e8 */
		if ((int)r == 0)
			return kernel_ipc_complete(port, msg, out);  /* FUN_fffffe000b7976a4 */
		kernel_ipc_panic(msg, 0, 0x200);           /* FUN_fffffe000c0e0b28 */
	}
	return 0;
}

/* ------------------------------------------------------------------ *
 * FUN_fffffe000b85e180 @ 0xfffffe000b85e180   (est. hv_percpu_queue_pop)
 * Ghidra: undefined1 [16] FUN_fffffe000b85e180(long,long,ulong)
 * Pops an entry from a per-CPU queue while accounting: increments the
 * per-CPU nesting counter (tpidr_el1+0x1c0), walks the per-CPU block array
 * (param_1+0x40, stride 0x4000) for this cpu (index from tpidr_el1+0x1b0),
 * rotates the queue head (NEON_ext 8-byte rotate), accumulates the entry
 * size into param_2's counter, pops the queue tail, decrements nesting and
 * fires a TLB flush (FUN_fffffe000b96c6d4) when nesting returns to 0.
 * Returns a 16-byte struct {entry, size, 0}.
 * Confidence: low (queue/accounting shape; the 16-byte return and NEON_ext
 *   rotation are Ghidra artifacts of a 128-bit queue slot).
 * Notes: NEON_ext = 64-bit rotate of a 16-byte slot; TLB flush
 *   FUN_fffffe000b96c6d4; fallback FUN_fffffe000b85e858.
 * ------------------------------------------------------------------ */
uint64_t
hv_percpu_queue_pop(long cpu, long buf, uint64_t flags)
{
	uint64_t *slot;
	long    *q;
	uint16_t size;
	uint16_t cnt;
	int      i;
	long     base;
	long     cur;
	uint64_t entry;
	uint64_t out[2];

	base = tpidr_el1;
	*(int *)(base + 0x1c0) += 1;
	cur = *(long *)(cpu + 0x40);
	if ((cur != 0) && (cur != 0)) {
		cur += (uint64_t)*(uint16_t *)(base + 0x1b0) * 0x4000;
		if (*(short *)(cur + 4) == 0) {
			if ((*(short *)(cur + 6) == 0) || (*(long *)(cur + 0x30) != 0)) {
				cur = kernel_queue_alloc(cpu, 0, flags & 0xffffffff);  /* FUN_fffffe000b85e2e8 */
				flags = flags & 0xffffffff;
				if (cur == 0) goto fallback;
			} else {
				*(short *)(cur + 4) = *(short *)(cur + 6);
				*(uint16_t *)(cur + 6) = 0;
				/* rotate the 16-byte queue head (NEON_ext 8,1) */
				uint64_t hi = *(uint64_t *)(cur + 8);
				uint64_t lo = *(uint64_t *)(cur + 0x10);
				*(uint64_t *)(cur + 0x10) = hi;
				*(uint64_t *)(cur + 8) = lo;
			}
		}
		size = *(uint16_t *)(cpu + 0x34);
		q = (long *)((uint64_t)*(uint16_t *)(base + 0x1b0) * 0x4000 + buf);
		*q += size;
		cnt = *(short *)(cur + 4) - 1;
		*(uint16_t *)(cur + 4) = cnt;
		slot = (uint64_t *)(*(long *)(cur + 8) + (uint64_t)cnt * 8);
		entry = *slot;
		*slot = 0;
		if (*(int *)(base + 0x1c0) == 0)
			kernel_panic_b();                 /* FUN_fffffe000c0f1874 */
		i = *(int *)(base + 0x1c0) - 1;
		*(int *)(base + 0x1c0) = i;
		if ((i == 0) && ((*(uint8_t *)(*(long *)(base + 0x1b8) + 0x4c) >> 2 & 1) != 0))
			kernel_tlb_flush();               /* FUN_fffffe000b96c6d4 */
		out[0] = entry;
		out[1] = size;
		return out[0];
	}
fallback:
	return kernel_queue_fallback(cpu, buf, flags);   /* FUN_fffffe000b85e858 */
}

/* ------------------------------------------------------------------ *
 * FUN_fffffe000b9882ac @ 0xfffffe000b9882ac   (est. hv_el2_amx_swap)
 * Ghidra: void FUN_fffffe000b9882ac(long param_1)
 * Swaps the AMX/SVE streaming state at EL2 for a vcpu. When the vcpu's
 * EL2-state dirty flag (el2+0x411f bit 1) and the vcpu pending flag
 * (vcpu+200 bit 0) are both set: clears the pending flag, then either (a)
 * if streaming SVE is NOT active (el2+0x4118 bit 4 clear OR el2+0x4138&3
 * zero): DSB, reads SVCR_EL2 (S3_4_15_1_3) and the AMX control reg
 * (S3_4_15_1_4), locks it (set bit 63), calls __amx_disable()/__amx_enable()
 * based on SVCR, unlocks and ISB; or (b) if streaming SVE IS active, reads
 * SVCR and clears it (S3_4_15_1_3 = 0) with ISB.
 * Confidence: medium (register encodings op1=4 => EL2; S3_4_15_1_3/4 are
 *   Apple AMX/SVCR control; the lock-bit dance is characteristic).
 * Notes: __amx_disable/__amx_enable are AMX intrinsics (est.);
 *   UnkSytemRegRead/Write(3,4,0xf,1,3) = SVCR_EL2,
 *   (3,4,0xf,1,4) = S3_4_15_1_4 (AMX state control).
 * ------------------------------------------------------------------ */
void
hv_el2_state_activate(long vcpu)
{
	long    el2;
	uint64_t svcr;
	uint64_t ctl;
	uint64_t v;

	el2 = *(long *)(vcpu + 0xb0);
	if (((*(uint8_t *)(el2 + 0x411f) >> 1 & 1) != 0) &&
	    ((*(uint8_t *)(vcpu + 200) & 1) != 0)) {
		*(uint8_t *)(vcpu + 200) = 0;
		if (((*(uint8_t *)(el2 + 0x4118) >> 4 & 1) == 0) ||
		    ((*(uint8_t *)(el2 + 0x4138) & 3) == 0)) {
			DataSynchronizationBarrier(2, 3, 0);
			svcr = UnkSytemRegRead(3, 4, 0xf, 1, 3);
			ctl = UnkSytemRegRead(3, 4, 0xf, 1, 4);
			if ((int64_t)ctl >= 0) {
				v = UnkSytemRegRead(3, 4, 0xf, 1, 4);
				UnkSytemRegWrite(3, 4, 0xf, 1, 4, v | 0x8000000000000000ULL);
				InstructionSynchronizationBarrier();
			}
			if (svcr == 0)
				__amx_disable();
			else
				__amx_enable();
			if ((int64_t)ctl >= 0) {
				v = UnkSytemRegRead(3, 4, 0xf, 1, 4);
				UnkSytemRegWrite(3, 4, 0xf, 1, 4, v & 0x7fffffffffffffffULL);
				InstructionSynchronizationBarrier();
				return;
			}
		} else {
			svcr = UnkSytemRegRead(3, 4, 0xf, 1, 3);
			if (svcr != 0) {
				UnkSytemRegWrite(3, 4, 0xf, 1, 3, 0);
				InstructionSynchronizationBarrier();
				return;
			}
		}
	}
	return;
}

/* ------------------------------------------------------------------ *
 * FUN_fffffe000b987c44 @ 0xfffffe000b987c44   (est. hv_vm_regions_teardown)
 * Ghidra: void FUN_fffffe000b987c44(long *param_1)
 * Tears down every mapped region of a VM owner: binds the current cpu into
 * the owner (+8), takes the owner lock, walks the region RB-tree rooted at
 * param_1 + 0x427 (fields [5]=left, [6]=right, [7]=parent with the low bit
 * as a color flag), and for each node: unlinks it (hv_rbtree_unlink),
 * releases the node object (os_release), frees the node's backing store
 * (FUN_fffffe000b793cf4 = zfree of node[4]), and decrements the region
 * refcount (FUN_fffffe000b862b6c on DAT_fffffe0007d54078). Releases the
 * owner lock when the walk completes.
 * Confidence: high (full RB-tree unlink loop with the region root at
 *   owner+0x427 matches hv_vm_map_region's tree).
 * Notes: rbtree root owner+0x427 (stride 5 longs/node); lock
 *   FUN_fffffe000b7f0afc / unlock FUN_fffffe000b7f1e80; called from
 *   hv_vm_create unwind and hv_vcpu_object_release.
 * ------------------------------------------------------------------ */
void
hv_vm_owner_teardown(long *owner)
{
	uint64_t *slot;
	uint64_t *node;
	uint64_t *next;
	uint64_t *last;
	uint64_t *child;
	int       i, j;
	uint64_t  v;
	uint64_t *t;
	int       pending;
	long      obj;
	long      cpu;
	bool      is_right;

	pending = (int)hv_debug_flag;
	obj = owner[0];
	cpu = tpidr_el1;
	slot = (uint64_t *)(obj + 8);
	v = *slot;
	if (v == 0)
		*slot = *(uint32_t *)(cpu + 0x518);
	if (v != 0 || pending != 0)
		lock_acquire((void *)obj, cpu, v, 0);

	slot = (uint64_t *)(owner + 0x427);
	next = NULL;
	do {
		last = next;
		next = (uint64_t *)*slot;
		slot = next + 5;
		pending = (int)hv_debug_flag;
	} while (next != NULL);

	do {
		hv_debug_flag = pending;
		if (last == NULL) {
			obj = owner[0];
			i = *(int *)(cpu + 0x518);
			j = *(int *)(obj + 8);
			if (j == i)
				*(int *)(obj + 8) = 0;
			if (j != i || pending != 0) {
				lock_release((void *)obj);
				return;
			}
			return;
		}
		next = (uint64_t *)last[6];
		if (last[6] == NULL) {
			t = (uint64_t *)(last[7] & 0xfffffffffffffffeULL);
			next = last;
			if ((t == NULL) || (last != (uint64_t *)t[5])) {
				do {
					t = (uint64_t *)(next[7] & 0xfffffffffffffffeULL);
					if (t == NULL) break;
					is_right = next == (uint64_t *)t[6];
					next = t;
				} while (is_right);
			}
		} else {
			do {
				t = next;
				next = (uint64_t *)t[5];
			} while (t[5] != NULL);
		}
		hv_rbtree_unlink(owner, last);          /* FUN_fffffe000b9860bc */
		os_release((void *)last[0]);            /* FUN_fffffe000b8afa78 */
		kfree_type((void *)last[4]);            /* FUN_fffffe000b793cf4 */
		refcount_dec(&hv_region_refcount, last);/* FUN_fffffe000b862b6c, DAT_fffffe0007d54078 */
		last = t;
		pending = (int)hv_debug_flag;
	} while (true);
}

/* ------------------------------------------------------------------ *
 * FUN_fffffe000b95ecd8 @ 0xfffffe000b95ecd8   (est. cpu_signal)
 * Ghidra: undefined8 FUN_fffffe000b95ecd8(long,uint,undefined8,undefined8,int)
 * Sends a cross-call / IPI to another CPU (XNU cpu_signal pattern): raises
 * DAIF, and for the cross-call signals (4 = cross-call, 0x200 = rtclock)
 * stores the caller payload into the target's signal slots
 * (param_1+0x180/0x188 for 4, +0x190/0x198 for 0x200) and spins on the
 * per-CPU pending-flags (param_1+0x48) with a CNTPCT_EL0 deadline
 * (hv_signal_timeout + start), delivering via the registered callbacks;
 * panics "CPU%u has failed to respond to cross-call after %llu nanoseconds"
 * on timeout. Other signals are ORed into param_1+0x48. Finally writes the
 * Apple IPI register (UnkSytemRegWrite(3,5,0xf,0,0/1) = S3_5_15_0_x) with
 * the target's affinity (from the cpu table cpu_table_base + cpu*0x20
 * or param_1+0x1d0) matched against MPIDR_EL1, then ISB and restores DAIF.
 * Confidence: high (the cross-call timeout panic string + IPI register
 *   writes are unambiguous).
 * Notes: Apple IPI reg S3_5_15_0_0/1 (op1=5); cpu table stride 0x20;
 *   callback slots +0x180/0x188 and +0x190/0x198; timeout global
 *   hv_signal_timeout; restore debug_exceptions_disable FUN_fffffe000b968948.
 * ------------------------------------------------------------------ */
uint64_t
cpu_signal(long cpu, uint32_t signal, uint64_t a, uint64_t b, int arg5)
{
	uint64_t daif_save;
	uint32_t old, new;
	uint32_t flags;
	long     base;
	long     t0, t1;
	uint64_t start, now;
	uint64_t deadline;
	long     slot_fn, slot_arg;
	void    (*fn)(void);
	int      i;
	uint64_t r;
	uint64_t t;
	uint32_t *ipitab;
	uint32_t ipi;
	uint64_t mpidr;
	uint8_t  cluster, core;

	base = tpidr_el1;
	daif_save = daif;
	if (((uint)daif_save >> 9 & 1) == 0)
		kernel_panic_msg_fmt("%s: debug exceptions enabled in kernel mode @%s:%d");
	if ((daif_save & 0x1c0) != 0x1c0) {
		t = daif;
		daif = t | 0x1c0;
	}
	base = *(long *)(base + 0x1b8);

	if ((signal == 4) || (signal == 0x200)) {
		t0 = *(long *)(base + 0x58);
		do {
			t1 = t0;
			now = UnkSytemRegRead(3, 4, 0xf, 10, 6);   /* CNTPCT_EL0 (est.) */
			t0 = *(long *)(*(long *)(base + 0x1b8) + 0x58);
		} while (t0 != t1);
		start = now + t1;
		deadline = hv_signal_timeout + start;
		now = start;
		do {
			flags = *(uint32_t *)(cpu + 0x48);
			if ((int)flags < 0) goto err_busy;
			new = flags & ~signal;
			old = *(uint32_t *)(cpu + 0x48);
			if (old == new)
				*(uint32_t *)(cpu + 0x48) = flags | signal;
			if ((signal == 0x200) && (old != new) &&
			    ((*(uint32_t *)(cpu + 0x48) >> 9 & 1) != 0)) {
				r = 0x1e;
				goto out;
			}
			if (old == new) break;
			if ((*(uint32_t *)(base + 0x48) & signal) != 0) {
				DataMemoryBarrier(2, 1);
				fn = (void (*)(void))*(uint64_t *)(base + 0x180);
				if ((fn != NULL) && (*(long *)(base + 0x188) != 0)) {
					*(uint64_t *)(base + 0x180) = 0;
					*(uint64_t *)(base + 0x188) = 0;
					DataMemoryBarrier(2, 3);
					*(uint32_t *)(base + 0x48) &= 0xfffffffb;
					(*fn)();
				}
				fn = (void (*)(void))*(uint64_t *)(base + 400);
				if ((fn != NULL) && (*(long *)(base + 0x198) != 0)) {
					*(uint64_t *)(base + 400) = 0;
					*(uint64_t *)(base + 0x198) = 0;
					DataMemoryBarrier(2, 3);
					*(uint32_t *)(base + 0x48) &= 0xfffffdff;
					(*fn)();
				}
			}
			t0 = *(long *)(*(long *)(base + 0x1b8) + 0x58);
			do {
				t1 = t0;
				now = UnkSytemRegRead(3, 4, 0xf, 10, 6);
				t0 = *(long *)(*(long *)(base + 0x1b8) + 0x58);
			} while (t0 != t1);
			now = now + t1;
		} while (now < deadline);
		if (deadline <= now) {
			kernel_time_delta(now - start, (uint8_t *)&b);
			kernel_time_delta(hv_signal_timeout, (uint8_t *)&a);
			kernel_panic_msg_fmt("CPU%u has failed to respond to cross-call after %llu nanoseconds (timeout = %llu ns) @%s:%d");
		}
		slot_fn = 0x180;
		slot_arg = 0x188;
		if (signal == 0x200) {
			slot_fn = 400;
			slot_arg = 0x198;
		}
		*(uint64_t *)(cpu + slot_fn) = a;
		*(uint64_t *)(cpu + slot_arg) = b;
	} else {
		do {
			flags = *(uint32_t *)(cpu + 0x48);
			if ((int)flags < 0) {
				if (base == cpu)
					kernel_panic_msg_fmt("cpu_signal of self while signals are disabled @%s:%d");
err_busy:
				r = 5;
				goto out;
			}
		} while (*(uint32_t *)(cpu + 0x48) != flags);
		*(uint32_t *)(cpu + 0x48) = flags | signal;
	}

	DataSynchronizationBarrier(2, 2, 0);
	if ((int)*(uint32_t *)(cpu + 0x48) >= 0) {
		if (arg5 == 0) {
			if (hv_signal_use_table == 0) {
				ipitab = &cpu_table_base + (uint64_t)*(uint32_t *)(cpu + 0x40) * 0x20;
				if ((((uint64_t)ipitab ^ (uint64_t)&cpu_table_base) & 0xffc0000000000000ULL) != 0)
					ipitab = (uint32_t *)(((uint64_t)ipitab & 0xffffffffffffULL) | 0xc8a2000000000000ULL);
				ipi = ipitab[1];
				mpidr = mpidr_el1;
				cluster = (uint8_t)(ipi >> 8);
				if (cluster == (uint8_t)(mpidr >> 8)) {
					UnkSytemRegWrite(3, 5, 0xf, 0, 0, (uint64_t)ipi & 0xff);
				} else {
					UnkSytemRegWrite(3, 5, 0xf, 0, 1, (uint64_t)(ipi & 0xff | (int)cluster << 0x10));
				}
			} else {
				ipi = *(uint32_t *)(cpu + 0x1d0);
				mpidr = mpidr_el1;
				cluster = (uint8_t)(ipi >> 8);
				if (cluster == (uint8_t)(mpidr >> 8)) {
					UnkSytemRegWrite(3, 5, 0xf, 0, 0, (uint64_t)ipi & 0xff);
				} else {
					UnkSytemRegWrite(3, 5, 0xf, 0, 1, (uint64_t)(ipi & 0xff | (int)cluster << 0x10));
				}
			}
		} else if (hv_signal_use_table == 0) {
			ipitab = &cpu_table_base + (uint64_t)*(uint32_t *)(cpu + 0x40) * 0x20;
			if ((((uint64_t)ipitab ^ (uint64_t)&cpu_table_base) & 0xffc0000000000000ULL) != 0)
				ipitab = (uint32_t *)(((uint64_t)ipitab & 0xffffffffffffULL) | 0xc8a2000000000000ULL);
			ipi = ipitab[1];
			mpidr = mpidr_el1;
			cluster = (uint8_t)(ipi >> 8);
			if (cluster == (uint8_t)(mpidr >> 8)) {
				UnkSytemRegWrite(3, 5, 0xf, 0, 0, ((uint64_t)ipi & 0xff) | 0x20000000);
			} else {
				UnkSytemRegWrite(3, 5, 0xf, 0, 1, (uint64_t)(ipi & 0xff | (int)cluster << 0x10) | 0x20000000);
			}
		} else {
			ipi = *(uint32_t *)(cpu + 0x1d0);
			mpidr = mpidr_el1;
			cluster = (uint8_t)(ipi >> 8);
			if (cluster == (uint8_t)(mpidr >> 8)) {
				UnkSytemRegWrite(3, 5, 0xf, 0, 0, ((uint64_t)ipi & 0xff) | 0x20000000);
			} else {
				UnkSytemRegWrite(3, 5, 0xf, 0, 1, (uint64_t)(ipi & 0xff | (int)cluster << 0x10) | 0x20000000);
			}
		}
		InstructionSynchronizationBarrier();
	}
	r = 0;
out:
	debug_exceptions_disable((daif_save & 0x1c0) != 0x1c0);  /* FUN_fffffe000b968948 */
	return r;
}

/* ------------------------------------------------------------------ *
 * FUN_fffffe000b75deac @ 0xfffffe000b75deac   (est. el1_sync_handler)
 * Ghidra: void FUN_fffffe000b75deac(long param_1,undefined8,undefined8)
 * EL1 synchronous exception handler (VBAR_EL1 = b75c000, vector +0x600).
 * This is where the guest-exit path erets: on an exception from EL0 it
 * spins in WFE if a flag (hv_halt_flag) is set; from EL1 it asks
 * hv_el2_guest_exc_check (decompiled, hv_el2.c) whether the exception is
 * guest-visible, runs the dtrace probe (FUN_fffffe000c0d79b8) when so,
 * stores ELR/FAR into the frame (+0x108/+0x118), dispatches via
 * FUN_fffffe000b9627e0, and returns through hv_el2_exception_exit.
 * Confidence: medium (frame offsets + dispatch are structural).
 * ------------------------------------------------------------------ */
void
el1_sync_handler(long frame, uint64_t esr, uint64_t far)
{
	uint64_t elr;
	uint64_t spsr;
	long     is_guest;

	elr = elr_el1;
	spsr = spsr_el1;
	if ((spsr & 0xc) == 0) {
		if (*hv_halt_flag != '\0') {
			daif = daif & 0xfffffffffffffe3f;
			for (;;)
				WaitForEvent();
		}
	} else {
		is_guest = hv_el2_guest_exc_check(esr, elr, far, spsr_el1);
		if (is_guest != 0) {
			FUN_fffffe000c0d79b8(frame, esr);   /* dtrace probe (kernel) */
		}
	}
	*(uint64_t *)(frame + 0x108) = elr;
	*(uint64_t *)(frame + 0x118) = far;
	FUN_fffffe000b9627e0(frame, esr, far, is_guest != 0);   /* exception dispatch (kernel) */
	hv_el2_exception_exit();
}

/* ------------------------------------------------------------------ *
 * FUN_fffffe000b75df7c @ 0xfffffe000b75df7c   (est. el1_fiq_handler)
 * Ghidra: void FUN_fffffe000b75df7c(void)
 * EL1 FIQ handler (vector +0x200): runs the guest FIQ path
 * (hv_el2_guest_fiq, decompiled in hv_el2.c), clears frame +0xd0,
 * decrements the per-cpu nesting counter (tpidr_el1+0x1c0; panics on
 * underflow via hv_el2_preemption_panic), sends a local event and exits
 * back through hv_el2_exception_exit.
 * ------------------------------------------------------------------ */
void
el1_fiq_handler(void)
{
	long cpu = tpidr_el1;
	long frame = cpu_cur_thread_frame;   /* est. (unaff_x23) */

	hv_el2_guest_fiq();
	*(uint64_t *)(frame + 0xd0) = 0;
	if (*(int *)(cpu + 0x1c0) == 0) {
		hv_el2_preemption_panic();
		return;
	}
	*(int *)(cpu + 0x1c0) -= 1;
	SendEventLocally();
	hv_el2_exception_exit();
}

/* ------------------------------------------------------------------ *
 * FUN_fffffe000b75e000 @ 0xfffffe000b75e000   (est. el1_irq_handler)
 * Ghidra: void FUN_fffffe000b75e000(void)
 * EL1 IRQ handler (vector +0x400): mirror of el1_fiq_handler with the guest
 * IRQ path (hv_el2_guest_irq).
 * ------------------------------------------------------------------ */
void
el1_irq_handler(void)
{
	long cpu = tpidr_el1;
	long frame = cpu_cur_thread_frame;   /* est. (unaff_x23) */

	hv_el2_guest_irq();
	*(uint64_t *)(frame + 0xd0) = 0;
	if (*(int *)(cpu + 0x1c0) == 0) {
		hv_el2_preemption_panic();
		return;
	}
	*(int *)(cpu + 0x1c0) -= 1;
	SendEventLocally();
	hv_el2_exception_exit();
}

/* ------------------------------------------------------------------ *
 * FUN_fffffe000b75e058 @ 0xfffffe000b75e058   (est. el1_error_handler)
 * Ghidra: void FUN_fffffe000b75e058(void)
 * EL1 error (serror) handler (vector +0x800): runs the error path
 * (FUN_fffffe000b9671b4) then exits through hv_el2_exception_exit.
 * ------------------------------------------------------------------ */
void
el1_error_handler(void)
{
	FUN_fffffe000b9671b4();   /* est. kernel error handler */
	hv_el2_exception_exit();
}
