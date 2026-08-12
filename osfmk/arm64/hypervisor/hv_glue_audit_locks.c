/* Recreated from kernelcache.arm64.kc (xnu-12377.121.10 RELEASE_ARM64_T8142, image base fffffe0007004000). Ground truth: Ghidra FUN_ names + addresses; all names are estimates. */
/* hv_glue_audit_locks.c — kernel lock touch-set recreation (tree hv-deps, FULL-AUDIT). */

#include <stdint.h>
#include <stddef.h>

/*
 * hv_glue_audit_locks.c — the kernel lock/mutex touch-set the hypervisor calls
 * directly (category Locks), recreated per the FULL-AUDIT rule in AGENTS.md:
 * the hypervisor calls these DIRECTLY, so their bodies are reconstructed
 * faithfully from kernelcache.arm64.kc (image base fffffe0007004000).
 *
 * The FUN_ names are the Ghidra ground truth; the English names are estimates.
 * Confirmed identities (the s_lck_mtx_t_ilk string at 0xfffffe0007d790b8 and
 * the hw_lock_t string at 0xfffffe0007d79170 plus the LZCOUNT lock-class table
 * at 0xfffffe000c5b0400 confirm these are XNU lck_mtx / hw_lock):
 *   lck_mtx_lock            @ 0xfffffe000b7f0afc — XNU mutex acquire (4 args:
 *                             lock, thread, old, flags). ~14KB decompile.
 *   lck_mtx_unlock          @ 0xfffffe000b7f1e80 — XNU mutex release (3 args).
 *   lock_release            @ 0xfffffe000b7f1e4c — fast-path release: clears
 *                             the cpu-owner slot *(lock+8) when it equals the
 *                             current cpu id and the debug flag is clear.
 *   kernel_lock_ref         @ 0xfffffe000b7f62e8 — per-cpu lock-ref count inc.
 *   kernel_spinlock_acquire @ 0xfffffe000b7f8738 — hw_lock_t spinlock acquire.
 *   kernel_spinlock_release @ 0xfffffe000b7f8a60 — hw_lock_t spinlock release.
 *   kernel_lock_bit_acquire @ 0xfffffe000b7f8d9c — lock-bit acquire (1=ok).
 *   kernel_lock_bit_release @ 0xfffffe000b7f8e50 — lock-bit release.
 *   kernel_lock_bit_wait4   @ 0xfffffe000b7f8ce0 — lock-bit wait/acquire used
 *                             by hv_el2_guest_pte_check (4-arg; decompile
 *                             drops args 3-4 as unused).
 *   kernel_lock_bit_clear   @ 0xfffffe000b812380 — lock event clear.
 *   kernel_lock_flush_ack   @ 0xfffffe000b812f5c — flush/state event ack.
 *   kernel_owner_mismatch_panic @ 0xfffffe000c0e4d74 — noreturn "Mutex %p is
 *                             unexpectedly not owned by thread %p" panic.
 *
 * Callees 2+ levels into XNU stay externs (FUN_/DAT_ kept in comments).
 * Ghidra pseudo-artifacts (LZCOUNT, ExclusiveMonitorPass/Status,
 * ClearExclusiveLocal, in_wzr, the 0x2bad poison-tag sign-extension branches)
 * are reproduced with local helpers / notes so the bodies compile.
 */

/* ------------------------------------------------------------------ *
 * Ghidra-compat typedefs + pseudo-functions (self-contained file).
 * ------------------------------------------------------------------ */
typedef unsigned long ulong;
typedef unsigned int  uint;
typedef unsigned char byte;
typedef unsigned short ushort;

/* LZCOUNT = ARM64 `clz` leading-zero count (32-bit width here: the lock
 * class / waitq-hash table index 0x16 - LZCOUNT(tag|0x3ff) must stay in
 * [0, 32] for a 32-entry table, so the 32-bit form is what the kernel used). */
#define LZCOUNT(x)   ((int)__builtin_clz((unsigned)(x)))

/* Exclusive-monitor / WFE primitives (Ghidra pseudo-functions). For an audit
 * recreation these are documented stubs: ExclusiveMonitorPass (LDXP load)
 * succeeds, ExclusiveMonitorsStatus (STXP store) succeeds (0), and
 * ClearExclusiveLocal is a real `clrex`. */
#define ClearExclusiveLocal()       __asm__ volatile("clrex")
#define ExclusiveMonitorsStatus()   (0)
#define ExclusiveMonitorPass(a, s)  (1)
#define WaitForEvent()              __asm__ volatile("wfe")
#define SendEventLocally()          __asm__ volatile("sevl")

/* ------------------------------------------------------------------ *
 * Kernel globals (DAT_/PTR_DAT_ kept in comments).
 * ------------------------------------------------------------------ */
extern uint64_t tpidr_el1;           /* per-cpu data base (raw TPIDR_EL1) */
extern uint32_t hv_debug_flag;       /* DAT_fffffe000c62b3d0 "pending sync" / lock-storm flag */
extern uint32_t hv_trace_flag;       /* DAT_fffffe000c68ac90 trace-enable flag, bit 0 */
extern uint64_t hv_flush_lock;       /* DAT_fffffe000c756760 flush/state lock */

/* Lock trace/stat enable flags consulted before each lock_stat_record call. */
extern uint32_t hv_lock_trace_60[];  /* DAT_fffffe000c630c60 array (index 4/5 = non-spin/spin) */
extern uint64_t hv_lock_trace_80;    /* DAT_fffffe000c630c80 */
extern uint64_t hv_lock_trace_64;    /* DAT_fffffe000c630c64 (spinlock acquire) */
extern uint64_t hv_lock_trace_6c;    /* DAT_fffffe000c630c6c (spinlock release) */
extern uint64_t hv_lock_trace_84;    /* DAT_fffffe000c630c84 */
extern uint64_t hv_lock_trace_88;    /* DAT_fffffe000c630c88 */
extern uint64_t hv_lock_trace_8c;    /* DAT_fffffe000c630c8c */

/* Lock-class / waitq-hash lookup tables (indexed by 0x16 - LZCOUNT(tag|0x3ff)). */
extern void *   lck_grp_class_table[]; /* PTR_DAT_fffffe000c5b0400 lock-class table */
extern void *   waitq_hash_table[];    /* PTR_DAT_fffffe000c5b22f8 waitq hash table */
extern void *   waitq_chain_table[];   /* PTR_DAT_fffffe000c5b0970 waitq chain table */
extern uint32_t waitq_hash_secret;     /* DAT_fffffe0007d7c8ac waitq hash secret */
extern uint32_t waitq_chain_secret;    /* DAT_fffffe0007d7c874 waitq chain secret */

/* Waitq-link slot arrays (per-cpu). */
extern ulong    hv_waitq_link_100[];   /* DAT_fffffe000c5f4100 waitq link slots */
extern uint8_t  hv_waitq_link_108[];   /* DAT_fffffe000c5f4108 (back-links, stride 0x40) */
extern uint8_t  hv_waitq_link_110[];   /* DAT_fffffe000c5f4110 (slot flags, stride 0x40) */

/* Per-cpu event arrays used by kernel_lock_bit_clear / kernel_lock_flush_ack. */
extern uint8_t  hv_cpu_event_028[];    /* DAT_fffffe000c5ee028 */
extern uint8_t  hv_cpu_event_02f[];    /* DAT_fffffe000c5ee02f */
extern uint8_t  hv_cpu_event_098[];    /* DAT_fffffe000c5ee098 */

/* Lock-type name strings passed to the waitq-link helpers. */
extern void *   hw_lock_t_name;        /* PTR_s_hw_lock_t_fffffe0007d79170 "hw_lock_t" */
extern void *   lck_mtx_t_name;        /* PTR_s_lck_mtx_t__ilk__fffffe0007d790b8 "lck_mtx_t" */

/* Registers / pseudo-reads. */
extern uint64_t daif;                  /* DAIF interrupt mask */
extern uint64_t UnkSytemRegRead(int op0, int op1, int crn, int crm, int op2);

/* ARC-style lock-object / group acquire+release (XNU, not recreated). */
extern void LOAcquire(void);   /* lck_grp object-lock acquire */
extern void LORelease(void);   /* lck_grp object-lock release */

/* ------------------------------------------------------------------ *
 * Stubbed kernel callees (audit boundary — their internals are 2+ levels
 * into XNU). Signatures taken from the call sites in the decompiles.
 * ------------------------------------------------------------------ */
extern void  lock_stat_record(uint64_t flag, void *obj, uint64_t arg,
                              uint64_t a, uint64_t b, uint64_t c); /* FUN_fffffe000b9ba5f8 */
extern void  waitq_drop(void *lock, int flags);                    /* FUN_fffffe000b7f15fc */
extern void  waitq_wakeup(uint64_t waitq, void *state, uint64_t a,
                          uint64_t b, uint64_t c);                 /* FUN_fffffe000b8563f8 */
extern void  waitq_release(void);                                  /* FUN_fffffe000b852ee8 */
extern void  waitq_pending_clear(uint64_t waitq, uint64_t tag);    /* FUN_fffffe000b85304c */
extern void *waitq_lookup(void *lock, uint32_t handle, int flags); /* FUN_fffffe000b8515a0 */
extern void  waitq_block(void *waitq, void *slot, uint64_t flags,
                         uint64_t deadline);                       /* FUN_fffffe000b8561a8 */
extern void  waitq_prepare(void *lock);                            /* FUN_fffffe000b7f1318 */
extern ulong waitq_link_init(ushort *type_p, ulong *link, int n,
                             void *event, void *name);             /* FUN_fffffe000b7f8158 */
extern ulong waitq_link_get(ulong *slot, int n);                   /* FUN_fffffe000b7f84e0 */
extern void  waitq_link_validate(ulong *link, ushort *type_p);     /* FUN_fffffe000b7f85cc */
extern int   waitq_pending(uint state);                            /* FUN_fffffe000b7f1854 */
extern void  waitq_chain_lock(void *waitq);                        /* FUN_fffffe000b840260 */
extern int   waitq_chain_next(void *chain, ulong *out);            /* FUN_fffffe000b75fa98 */
extern void  waitq_chain_unlock(void *waitq);                      /* FUN_fffffe000b8401d0 */
extern void *kernel_waitq_event(void *lock);                       /* FUN_fffffe000c0e4cc4 */
extern void  lock_trace_record(int trace_id, void *lock, uint state,
                               uint64_t ts);                       /* FUN_fffffe000b7f0794 */
extern void  lock_trace_cont(long *flags_p);                       /* FUN_fffffe000b7f191c */
extern int   waitq_check_lock(void *lock, void *waitq);            /* FUN_fffffe000b8527ec */
extern void  kernel_tlb_flush(void);                               /* FUN_fffffe000b96c6d4 */
extern void  kernel_panic(void) __attribute__((noreturn));         /* FUN_fffffe000c0f1874 */
extern void  kernel_panic_msg_fmt(const char *fmt, ...) __attribute__((noreturn)); /* FUN_fffffe000c0e11ec */
extern void  lck_mtx_self_owned_panic(void *lock, void *thread) __attribute__((noreturn)); /* FUN_fffffe000c0e4c94 */
extern void  lck_mtx_bad_state_panic(void *lock) __attribute__((noreturn));  /* FUN_fffffe000c0e4c28 */
extern void  hw_lock_contended(void *lock, void *thread, void *name); /* FUN_fffffe000b7f8798 */
extern void  lock_ref_contended(void *lock, void *thread, int n);   /* FUN_fffffe000b7f6378 */
extern void  lock_ref_trace(void);                                  /* FUN_fffffe000b7f67a0 */
extern int   hw_lock_wait_abort(void);                              /* FUN_fffffe000b7f8ad4 */
extern int   kernel_event_valid(uint64_t ev);                       /* FUN_fffffe000b8124c0 */
extern uint64_t kernel_event_decode(uint64_t ev);                   /* FUN_fffffe000b96af70 */
extern uint64_t kernel_ptr_validate(uint64_t addr);              /* FUN_fffffe000b7605fc */
extern void  kernel_trace(uint32_t event, uint64_t a, uint64_t b,
                          uint64_t c, uint64_t d);                  /* FUN_fffffe000bd30528 */
extern void  kernel_event_clear(void *slot, int n);                 /* FUN_fffffe000b850e94 */
extern uint64_t kernel_event_wait(void *cpu, void *slot, uint32_t *flags); /* FUN_fffffe000b813144 */
extern int   kernel_event_poll(void *cpu, uint64_t ev, uint32_t flags);     /* FUN_fffffe000b813f34 */
extern void  kernel_barrier(int cond);                              /* FUN_fffffe000b968948 */

/* ------------------------------------------------------------------ *
 * Class-table / waitq-hash lookup helpers (the 0x16 - LZCOUNT(tag|0x3ff)
 * index that recurs in the decompiles). The Ghidra 0x2bad000000000000
 * poison-tag sign-extension branches are dead (the *8 offsets fit in 32
 * bits) and are omitted.
 * ------------------------------------------------------------------ */
static inline void *lck_class_ptr(uint16_t tag)
{
    return (void *)((char *)lck_grp_class_table[0x16 - LZCOUNT(tag | 0x3ff)]
                    + (ulong)tag * 8);
}

static inline long lck_class_data(uint16_t tag)
{
    return *(long *)lck_class_ptr(tag);
}

/* Waitq hash: key = secret ^ handle (fall back to secret when == 0xfffff),
 * then read the *8-th byte of the class entry at the hashed table row. */
static inline uint64_t waitq_hash_read(uint32_t handle)
{
    uint32_t key = waitq_hash_secret;
    uint32_t x   = waitq_hash_secret ^ handle;
    if (x != 0xfffff) {
        key = x;
    }
    return *(uint64_t *)((char *)waitq_hash_table[0x16 - LZCOUNT(key | 0x3ff)]
                         + (ulong)key * 8);
}

/* Waitq chain: same hashing against the owner id, returning the chain head. */
static inline long waitq_chain_read(uint32_t owner)
{
    uint32_t key = waitq_chain_secret;
    uint32_t x   = waitq_chain_secret ^ owner;
    if (x != 0xfffff) {
        key = x;
    }
    return *(long *)((char *)waitq_chain_table[0x16 - LZCOUNT(key | 0x3ff)]
                     + (ulong)key * 8);
}

/* The CPU-per-fault critical-section depth at thread+0x1c0 is decremented and
 * a TLB flush issued when it drops to zero on an interrupt-handler path. This
 * helper encapsulates that (appears in nearly every release path). */
static inline int depth_leave(void *thread)
{
    int depth;
    depth = *(int *)((char *)thread + 0x1c0) - 1;
    *(int *)((char *)thread + 0x1c0) = depth;
    if ((depth == 0) &&
        ((*(byte *)(*(long *)((char *)thread + 0x1b8) + 0x4c) >> 2 & 1) != 0)) {
        kernel_tlb_flush();
    }
    return depth;
}

/* ------------------------------------------------------------------ *
 * Forward declarations for cross-referenced bodies defined below.
 * ------------------------------------------------------------------ */
void kernel_owner_mismatch_panic(void *mutex, void *thread);
void kernel_spinlock_acquire(uint64_t *lock);
void kernel_spinlock_release(uint64_t *lock);

/* ================================================================== *
 * Recreated bodies
 * ================================================================== */

/* FUN_fffffe000c0e4d74 @ 0xfffffe000c0e4d74   (est. kernel_owner_mismatch_panic)
 * Ghidra: void FUN_fffffe000c0e4d74(void)
 * Noreturn assertion panic: "Mutex %p is unexpectedly not owned by thread %p
 * @%s:%d". The decompiler shows only the forward to the variadic panic-printf
 * (c0e11ec) with the format string; the lock/thread/file/line varargs are
 * register leftovers Ghidra drops for noreturn calls. Called from
 * hv_rbtree_unlink as (mutex, thread).
 * Confidence: high
 * Notes: c0e11ec = kernel_panic_msg_fmt; @%s:%d fill is __FILE__/__LINE__
 *   (kernel's own values are not recoverable from the decompile).
 * Kernel code recreated for audit (hv-deps). */
void
kernel_owner_mismatch_panic(void *mutex, void *thread)
{
    kernel_panic_msg_fmt("Mutex %p is unexpectedly not owned by thread %p @%s:%d",
                         mutex, thread, __FILE__, __LINE__);
}

/* FUN_fffffe000b7f1e80 @ 0xfffffe000b7f1e80   (est. lck_mtx_unlock)
 * Ghidra: void FUN_fffffe000b7f1e80(ushort *param_1, long param_2, uint param_3)
 * XNU mutex release. Validates that the thread at param_2 (its cpu-id field
 * +0x518) owns the lock (low 28 bits of the state word == cpu id), else panics
 * c0e4d74. The 0x80000000 state bit is the "no owner" sentinel. If the state's
 * high nibble (0x70000000) is clear it is a plain (non-contended) release and
 * returns after an optional trace. Otherwise it drops the waitq/lock bit
 * (bit 28), clears the owner slot keeping only the sentinel, wakes any
 * waiters (b8563f8) or just decrements the critical-section depth, issuing a
 * TLB flush (b96c6d4) on the interrupt path, and finally panics c0f1874 if the
 * depth underflowed.
 * Confidence: high
 * Notes: lock-class table c5b0400; waitq hash table c5b22f8 (secret 7d7c8ac);
 *   LZCOUNT indexing; DAT_fffffe000c630c80 trace gate; 0x2bad poison-tag
 *   branch omitted (dead). */
void
lck_mtx_unlock(uint32_t *lock, void *thread, uint32_t flags)
{
    uint32_t state;              /* uVar10 */
    uint64_t u11;                /* uVar11 */
    uint64_t u12;                /* uVar12 */
    uint32_t *slot;              /* puVar1 */
    void     *grp;               /* lVar9 */
    uint64_t waitq;              /* uVar13 */
    uint32_t key;                /* uVar4 */
    uint32_t kx;                 /* uVar6 */
    uint64_t u2;                 /* uVar2 */
    int      depth;              /* iVar8 */
    byte     b7;                 /* bVar7 */

    state = flags;
    if ((int)flags < -0x70000000) {           /* high bit (negative) set */
        state = *(uint32_t *)(lock + 4);
        if (state == flags) {
            *(uint32_t *)(lock + 4) = 0x80000000;   /* sentinel: no waitq */
        }
    }
    if (*(uint32_t *)((char *)thread + 0x518) != (state & 0xfffffff)) {
        kernel_owner_mismatch_panic(lock, thread);   /* c0e4d74, noreturn */
    }
    if ((state & 0x70000000) == 0) {          /* non-contended release */
        if (hv_lock_trace_80 == 0) {
            return;
        }
        lock_stat_record(hv_lock_trace_80, lock,
                         (uint64_t)lck_class_ptr((ushort)*lock), 0, 0, 0);
        return;
    }
    if ((state >> 0x1d & 1) == 0) {           /* bit 29 clear: set waiting bit */
        *(int *)((char *)thread + 0x1c0) += 1;
        u11 = *(ulong *)(lock + 4);
        do {
            if ((u11 & 0xffff10000000) != 0) {
                waitq_drop(lock, 1);          /* b7f15fc */
                goto drop_done;
            }
            u12 = u11 | 0x10000000;
            u2  = *(ulong *)(lock + 4);
            u11 = u2;
        } while (u2 != u12 - 0x10000000);     /* retry while unchanged */
        *(ulong *)(lock + 4) = u12;
    }
drop_done:
    slot = (uint32_t *)(lock + 4);
    state = *(uint32_t *)(lock + 4);
    if ((state >> 0x1e & 1) == 0) {           /* bit 30 clear: no waiters */
        *slot = state & 0x80000000;
        grp = (void *)tpidr_el1;
        if (*(int *)((char *)grp + 0x1c0) != 0) {
            depth = depth_leave(grp);
            if (hv_lock_trace_80 == 0) {
                return;
            }
            lock_stat_record(hv_lock_trace_80, lock,
                             (uint64_t)lck_class_ptr((ushort)*lock), 0, 0, 0);
            return;
        }
    }
    else {                                    /* bit 30 set: wake waiters */
        if (*(uint32_t *)(lock + 2) == 0) {
            waitq = 0;
        }
        else {
            waitq = waitq_hash_read(*(uint32_t *)(lock + 2));
        }
        waitq_wakeup(waitq, slot, 0, 1, 1);   /* b8563f8 */
        grp = (void *)tpidr_el1;
        b7  = *(byte *)((char *)grp + 0x58c);
        waitq_release();                      /* b852ee8 */
        if ((b7 >> 5 & 1) != 0) {
            waitq_pending_clear(waitq, 0x88); /* b85304c */
        }
        *slot = state & 0x80000000;
        if (*(int *)((char *)grp + 0x1c0) != 0) {
            depth = depth_leave(grp);
            if (hv_lock_trace_80 != 0) {
                lock_stat_record(hv_lock_trace_80, lock,
                                 (uint64_t)lck_class_ptr((ushort)*lock), 0, 0, 0);
            }
            waitq_release();                  /* b852ee8 */
            return;
        }
    }
    kernel_panic();                           /* c0f1874, noreturn */
}

/* FUN_fffffe000b7f1e4c @ 0xfffffe000b7f1e4c   (est. lock_release)
 * Ghidra: void FUN_fffffe000b7f1e4c(long param_1)
 * Fast-path mutex release. Reads the cpu-owner slot at lock+8; if it equals
 * the current cpu id (thread+0x518) it is cleared to 0. When it matched AND
 * the debug flag DAT_fffffe000c62b3d0 is clear, return immediately; otherwise
 * fall through to the full lck_mtx_unlock (b7f1e80).
 * Confidence: high
 * Notes: in_wzr (zero register) becomes the 0 store; DAT_fffffe000c62b3d0 is
 *   hv_debug_flag. */
void
lock_release(void *lock)
{
    int   cpu_id;      /* iVar2 = *(int *)(tpidr_el1 + 0x518) */
    int   owner;       /* iVar1 = *(int *)(lock + 8) */
    int   dbg;         /* iVar4 = hv_debug_flag */

    dbg     = hv_debug_flag;
    cpu_id  = *(int *)((char *)tpidr_el1 + 0x518);
    owner   = *(int *)((char *)lock + 8);
    if (owner == cpu_id) {
        *(int *)((char *)lock + 8) = 0;       /* in_wzr */
    }
    if (owner == cpu_id && dbg == 0) {
        return;
    }
    lck_mtx_unlock((uint32_t *)lock, (void *)tpidr_el1, 0);
}

/* FUN_fffffe000b7f62e8 @ 0xfffffe000b7f62e8   (est. kernel_lock_ref)
 * Ghidra: void FUN_fffffe000b7f62e8(long param_1)
 * Per-cpu lock-ref acquire. Increments the per-cpu lock-ref counter
 * (thread+0x22c). If the lock word (param_1+8) carries the lock-ref tag
 * ((word & 0xffffffff0001ffff) == 0x10000) and the tail field (param_1+0xc)
 * is 0, the tail is set to 2 (lock owned by the current thread); otherwise the
 * contended path b7f6378 runs. The cpu-id field (param_1+4) is then stamped
 * with the current cpu id (thread+0x518). A debug trace (b7f67a0) fires when
 * DAT_fffffe000c62b3d0 is set.
 * Confidence: high
 * Notes: DAT_fffffe000c62b3d0 = hv_debug_flag; b7f6378/b7f67a0 stubbed. */
void
kernel_lock_ref(void *lock)
{
    void *thread;   /* lVar1 = tpidr_el1 */

    thread = (void *)tpidr_el1;
    *(int *)((char *)thread + 0x22c) += 1;
    if (((*(ulong *)((char *)lock + 8) & 0xffffffff0001ffff) == 0x10000) &&
        (*(int *)((char *)lock + 0xc) == 0)) {
        *(int *)((char *)lock + 0xc) = 2;
    }
    else {
        lock_ref_contended(lock, thread, 0);  /* b7f6378 */
    }
    *(uint32_t *)((char *)lock + 4) = *(uint32_t *)((char *)thread + 0x518);
    if (hv_debug_flag != 0) {
        lock_ref_trace();                     /* b7f67a0 */
    }
}

/* FUN_fffffe000b7f8738 @ 0xfffffe000b7f8738   (est. kernel_spinlock_acquire)
 * Ghidra: void FUN_fffffe000b7f8738(long *param_1)
 * hw_lock_t spinlock acquire. Bumps the critical-section depth (thread+0x1c0).
 * If the lock word is free (== 0) it is set to the current thread pointer
 * (tpidr_el1) and an optional trace fires; otherwise WaitForEvent() spins
 * before the contended path b7f8798 runs with the "hw_lock_t" name string.
 * Confidence: high
 * Notes: DAT_fffffe000c630c64 trace gate; PTR_s_hw_lock_t_fffffe0007d79170
 *   name; b7f8798 stubbed. */
void
kernel_spinlock_acquire(uint64_t *lock)
{
    void *thread;   /* lVar1 = tpidr_el1 */

    thread = (void *)tpidr_el1;
    *(int *)((char *)thread + 0x1c0) += 1;
    if (*lock == 0) {
        if (*lock == 0) {
            *lock = (uint64_t)thread;
            if (hv_lock_trace_64 != 0) {
                lock_stat_record(hv_lock_trace_64, lock, 0, 0, 0, 0);
                return;
            }
            return;
        }
    }
    else {
        WaitForEvent();
    }
    hw_lock_contended(lock, thread, &hw_lock_t_name);   /* b7f8798 */
}

/* FUN_fffffe000b7f8a60 @ 0xfffffe000b7f8a60   (est. kernel_spinlock_release)
 * Ghidra: void FUN_fffffe000b7f8a60(undefined8 *param_1)
 * hw_lock_t spinlock release. Clears the lock word, fires the optional trace
 * (DAT_fffffe000c630c6c), then leaves the critical section (decrementing the
 * depth at thread+0x1c0 with a TLB flush on the interrupt path). Panics
 * c0f1874 if the depth underflowed.
 * Confidence: high
 * Notes: DAT_fffffe000c630c6c trace gate; depth_leave + kernel_panic. */
void
kernel_spinlock_release(uint64_t *lock)
{
    void *thread;   /* lVar2 = tpidr_el1 */

    *lock = 0;
    if (hv_lock_trace_6c != 0) {
        lock_stat_record(hv_lock_trace_6c, lock, 0, 0, 0, 0);
    }
    thread = (void *)tpidr_el1;
    if (*(int *)((char *)thread + 0x1c0) != 0) {
        depth_leave(thread);
        return;
    }
    kernel_panic();                           /* c0f1874, noreturn */
}

/* FUN_fffffe000b7f8d9c @ 0xfffffe000b7f8d9c   (est. kernel_lock_bit_acquire)
 * Ghidra: undefined8 FUN_fffffe000b7f8d9c(uint *param_1,uint param_2)
 * Lock-bit acquire (a hw_lock bit-slot). Bumps the critical-section depth,
 * computes the bit mask (1 << (param_2 & 0x1f)), and CAS-style sets it under
 * LOAcquire; returns 1 when the bit was free (acquired) or 0 when it was
 * already set. On the failed path it leaves the critical section and returns 0
 * (panicking c0f1874 on depth underflow).
 * Confidence: high
 * Notes: returns 1=ok, 0=busy (matches hv_el2.h "0 = busy"); LOAcquire;
 *   DAT_fffffe000c630c64 trace gate. */
int
kernel_lock_bit_acquire(uint32_t *lock, int bit)
{
    int      depth;   /* iVar1 */
    uint     mask;    /* uVar2 */
    uint     old;     /* uVar4 */
    void     *thread; /* lVar3 */

    thread = (void *)tpidr_el1;
    *(int *)((char *)thread + 0x1c0) += 1;
    mask = 1 << (ulong)(bit & 0x1f);
    if ((mask & *lock) == 0) {
        LOAcquire();
        old = *lock;
        *lock = old | mask;
        if ((old & mask) == 0) {
            if (hv_lock_trace_64 != 0) {
                lock_stat_record(hv_lock_trace_64, lock, 0, 0, 0, 0);
            }
            return 1;
        }
        depth = *(int *)((char *)thread + 0x1c0);
    }
    else {
        ClearExclusiveLocal();
        depth = *(int *)((char *)thread + 0x1c0);
    }
    if (depth != 0) {
        depth_leave(thread);
        return 0;
    }
    kernel_panic();                           /* c0f1874, noreturn */
}

/* FUN_fffffe000b7f8e50 @ 0xfffffe000b7f8e50   (est. kernel_lock_bit_release)
 * Ghidra: void FUN_fffffe000b7f8e50(uint *param_1,uint param_2)
 * Lock-bit release. Clears the bit mask (1 << (param_2 & 0x1f)) under
 * LORelease, fires the optional trace (DAT_fffffe000c630c6c), and leaves the
 * critical section (panicking c0f1874 on depth underflow).
 * Confidence: high
 * Notes: LORelease; DAT_fffffe000c630c6c trace gate. */
void
kernel_lock_bit_release(uint32_t *lock, int bit)
{
    void *thread;   /* lVar2 */

    *lock = *lock & ~(1 << (ulong)(bit & 0x1f));
    LORelease();
    if (hv_lock_trace_6c != 0) {
        lock_stat_record(hv_lock_trace_6c, lock, (uint64_t)(uint)bit, 0, 0, 0);
    }
    thread = (void *)tpidr_el1;
    if (*(int *)((char *)thread + 0x1c0) != 0) {
        depth_leave(thread);
        return;
    }
    kernel_panic();                           /* c0f1874, noreturn */
}

/* FUN_fffffe000b7f8ce0 @ 0xfffffe000b7f8ce0   (est. kernel_lock_bit_wait4)
 * Ghidra: undefined8 FUN_fffffe000b7f8ce0(uint *param_1,uint param_2)
 * Lock-bit wait/acquire. Bumps the critical-section depth, sets the bit mask
 * under LOAcquire, returning 1 on success (bit was free). If the bit was
 * already set it WaitForEvent()s and probes the contended/abort path
 * (b7f8ad4), returning 1 on a successful take-over or 0 when the bit is still
 * held. Decompiled as 2-arg; the 4-arg form (addr, field, name, state) used by
 * hv_el2_guest_pte_check is the real signature — args 3-4 are unused by the
 * body (Ghidra drops them).
 * Confidence: high
 * Notes: LOAcquire; WaitForEvent; b7f8ad4 abort probe; DAT_fffffe000c630c64
 *   trace gate. */
int
kernel_lock_bit_wait4(uint64_t addr, int field, void **name, uint64_t *state)
{
    uint32_t *lock = (uint32_t *)addr;   /* param_1 (unused args 3-4) */
    uint     mask;                       /* uVar1 */
    uint     old;                        /* uVar3 */
    int      depth;                      /* iVar4 */
    void     *thread;                    /* lVar2 */

    thread = (void *)tpidr_el1;
    *(int *)((char *)thread + 0x1c0) += 1;
    mask = 1 << (ulong)(field & 0x1f);
    if ((mask & *lock) == 0) {
        LOAcquire();
        old = *lock;
        *lock = old | mask;
        if ((old & mask) == 0) {
            if (hv_lock_trace_64 == 0) {
                return 1;
            }
            lock_stat_record(hv_lock_trace_64, lock, 0, 0, 0, 0);
            return 1;
        }
    }
    else {
        WaitForEvent();
    }
    depth = hw_lock_wait_abort();         /* b7f8ad4 */
    if (depth != 0) {
        return 1;
    }
    if (*(int *)((char *)thread + 0x1c0) == 0) {
        kernel_panic();                   /* c0f1874, noreturn */
    }
    depth_leave(thread);
    return 0;
}

/* FUN_fffffe000b812380 @ 0xfffffe000b812380   (est. kernel_lock_bit_clear)
 * Ghidra: void FUN_fffffe000b812380(ulong param_1,undefined8 param_2)
 * Lock event clear. With a non-zero event (param_1), if the trace flag
 * (DAT_fffffe000c68ac90 bit 0) is set it validates/decodes the event address
 * (sign-extending bit 55) and emits a trace record (bd30528), then blocks on
 * the flush lock (b8561a8 with hv_flush_lock DAT_fffffe000c756760). A zero
 * event is a fatal "%s() called with NO_EVENT" panic.
 * Confidence: high
 * Notes: DAT_fffffe000c68ac90 = hv_trace_flag; b8124c0/b96af70/b7605fc
 *   validation; bd30528 trace; b8561a8 waitq_block on hv_flush_lock. */
void
kernel_lock_bit_clear(uint64_t event, uint64_t flags)
{
    int      ev_rc;    /* iVar1 */
    uint64_t ev;       /* uVar2 */

    if (event != 0) {
        if ((hv_trace_flag & 1) != 0) {
            ev_rc = kernel_event_valid(event);       /* b8124c0 */
            ev = -(event >> 0x37 & 1) & 0xffff800000000000 | event & 0x7fffffffffff;
            if (ev_rc == 0) {
                if ((ev + 0x20000000000) >> 0x24 < 0xd) {
                    ev = kernel_ptr_validate(ev);    /* b7605fc */
                }
            }
            else {
                ev = kernel_event_decode(ev);        /* b96af70 */
            }
            kernel_trace(0x1400040, ev, 0, 0, 0);
        }
        waitq_block(&hv_flush_lock, (void *)event, flags, 0);   /* b8561a8 */
        return;
    }
    kernel_panic_msg_fmt("%s() called with NO_EVENT @%s:%d", __func__, __FILE__, __LINE__);  /* c0e11ec */
}

/* FUN_fffffe000b812f5c @ 0xfffffe000b812f5c   (est. kernel_lock_flush_ack)
 * Ghidra: undefined4 FUN_fffffe000b812f5c(ulong param_1,undefined8 param_2,uint param_3)
 * Flush/state event ack. Requires debug exceptions disabled (else panic),
 * forces IRQ/FIQ/async masked (DAIF = 0x1c0) when they were not already.
 * Indexes the per-cpu event arrays by (thread+0x1b0 >> 0x10), clears the
 * event/flag slots and (optionally) emits a trace, records param_1/param_2
 * into the per-cpu scratch (thread+0xd8/0xe0), then spins holding the
 * spinlock (kernel_spinlock_acquire/release) polling the event wait
 * (b813144/b813f34) until it settles, and returns the per-cpu result
 * (thread+0xd0). The DAIF mask is restored by b968948.
 * Confidence: high
 * Notes: spinlock b7f8738/b7f8a60 are this file's kernel_spinlock_acquire/
 *   release; DAIF pseudo-global; DAT_fffffe000c68ac90 = hv_trace_flag;
 *   b813144/b813f34/b850e94/bd30528 stubbed; return is (thread+0xd0). */
uint32_t
kernel_lock_flush_ack(uint64_t param1, uint64_t param2, uint32_t param3)
{
    void     *cpu;      /* lVar3 = tpidr_el1 */
    uint64_t daif_old;  /* uVar2 */
    uint64_t ev;        /* uVar5 */
    uint64_t ev2;       /* uVar6 */
    uint64_t ev3;       /* uVar7 */
    long     idx;       /* lVar1 */
    int      rc;        /* iVar4 */
    uint32_t flags_local; /* local_54 */

    cpu = (void *)tpidr_el1;
    daif_old = daif;
    flags_local = param3;
    if (((uint)daif_old >> 9 & 1) == 0) {
        kernel_panic_msg_fmt("%s: debug exceptions enabled in kernel mode @%s:%d",
                             __func__, __FILE__, __LINE__);   /* c0e11ec, noreturn */
    }
    if ((daif_old & 0x1c0) != 0x1c0) {
        daif = daif_old | 0x1c0;        /* mask IRQ/FIQ/async */
    }
    idx = *(long *)((char *)cpu + 0x1b0) >> 0x10;
    if ((param3 >> 4 & 1) != 0) {
        hv_cpu_event_098[idx] = 0;
    }
    *(uint32_t *)(*(long *)((char *)cpu + 0x1b8) + 0x4c) &= 0xffffffe0;
    if ((hv_cpu_event_02f[idx] & 1) != 0) {
        if ((hv_trace_flag & 0xfffffff7) != 0) {
            kernel_trace(0x140018e, 0, 0, 0, 0);
        }
        hv_cpu_event_02f[idx] = 0;
        kernel_event_clear(&hv_cpu_event_028[idx], 1);   /* b850e94 */
    }
    *(ulong *)((char *)cpu + 0xd8) = param1;
    *(ulong *)((char *)cpu + 0xe0) = param2;
    if (((*(uint32_t *)((char *)cpu + 0x1f8) & 0xffffff7b) == 0) ||
        ((hv_trace_flag & 1) == 0)) {
        goto poll;
    }
    if (param1 == 0) {
        ev2 = kernel_event_valid(0);     /* b8124c0 */
        ev = 0;
        ev3 = 0;
        if ((ev2 & 1) != 0) {
            goto trace_report;
        }
    }
    else {
        rc = kernel_event_valid(param1); /* b8124c0 */
        if (rc == 0) {
            ev = 0;
        }
        else {
            ev3 = param1 & 0x7fffffffffff;
            if ((param1 & 0x80000000000000) != 0) {
                ev3 = param1 | 0xffff800000000000;
            }
trace_report:
            ev = kernel_event_decode(ev3);   /* b96af70 */
        }
    }
    kernel_trace(0x140003c, param3, ev, 0, 0);
poll:
    do {
        kernel_spinlock_acquire((uint64_t *)((char *)cpu + 0xa0));
        ev = kernel_event_wait(cpu, &hv_cpu_event_028[idx], &flags_local);  /* b813144 */
        kernel_spinlock_release((uint64_t *)((char *)cpu + 0xa0));
        rc = kernel_event_poll(cpu, ev, flags_local);   /* b813f34 */
    } while (rc == 0);
    kernel_barrier((daif_old & 0x1c0) != 0x1c0);        /* b968948 */
    return *(uint32_t *)((char *)cpu + 0xd0);
}

/* FUN_fffffe000b7f0afc @ 0xfffffe000b7f0afc   (est. lck_mtx_lock)
 * Ghidra: void FUN_fffffe000b7f0afc(uint *param_1,long param_2,ulong param_3,ulong param_4)
 * XNU mutex acquire — the full futex/waitq mutex core. param_1 = lock,
 * param_2 = thread, param_3 = old state token, param_4 = flags.
 * Fast path: a free lock (old==0, non-0x80000000 sentinel handling) takes the
 * lock, stamps the owner slot (lock+2) with cpu_id (thread+0x518), records
 * stats and returns. Slow path: spins on the owner slot, CAS-setting bit 28
 * (waiting) and, when ownership can't be taken, walks the waitq chain
 * (c5b0970 hash, secret 7d7c874), enqueues this thread and blocks via
 * waitq_block (b8561a8), re-looping after wake. The 0x80000000 sentinel means
 * "no owner"; a self-owned lock panics c0e4c94, a corrupt state panics c0e4c28.
 * Confidence: high
 * Notes: ~14KB decompile; s_lck_mtx_t_ilk string 7d790b8; LZCOUNT class table
 *   c5b0400; cpu bind via *(thread+0x518); waitq-link slots c5f4100/108/110;
 *   0x2bad poison-tag branches + redundant outer `if` dropped (dead); the
 *   waitq epilogue (LAB_1310) continuation is waitq_prepare (b7f1318). */
void
lck_mtx_lock(uint32_t *lock, void *thread, uint64_t old, uint64_t flags)
{
    int      flags_i;        /* iVar12 */
    uint     cpu_id;         /* uVar17 */
    uint     st32;           /* uVar18 */
    uint     owner32;        /* uVar27 */
    uint64_t state;          /* uVar28 */
    uint64_t state_hi;       /* uVar20 (bit31 of owner word) */
    uint32_t lock_state;     /* uVar5 */
    uint16_t tag;            /* uVar4 */
    uint     cnt;            /* uVar19 */
    uint64_t cnt2;           /* uVar20 */
    uint     flags_u;        /* uVar25 */
    uint64_t u9;             /* uVar9 */
    uint64_t u11;            /* uVar11 */
    uint64_t u12;            /* uVar12 */
    uint64_t u2;             /* uVar2 */
    byte     b6;             /* bVar6 */
    char     mon_status;     /* cVar7 */
    int      depth;          /* iVar8 */
    int      class_idx;      /* lVar15 (4 or 5) */
    long     grp;            /* lVar16 */
    long     base;           /* lVar15 */
    long     ev;             /* lVar16/lVar22/lVar23/lVar24 */
    long     chain;          /* plVar2 */
    long     *chain_ptr;     /* plVar2 (try_acquire waitq-hash slot) */
    uint64_t ts;             /* lVar29 */
    void     *waitq;         /* puVar26 */
    ulong    *owner_slot;    /* puVar13 = lock+2 */
    ulong    *wait_slot;     /* puVar14 */
    void     *wait_tab;      /* puVar21 */
    ushort   *type_p;        /* puVar1 */
    char     *spin_p;        /* pcVar3 */
    void     *cur_thread;    /* local_70 */
    int      dropped;        /* local_74 */
    int      trace_id;       /* local_78 */
    ulong    ev_found;       /* local_68 */
    long     cpu_flags_p;    /* lStack_e8 */
    char     *spin_stack;    /* pcStack_e0 */
    uint64_t wait_ctrl;      /* uStack_c8 */
    uint64_t ts_val;         /* uStack_d8 */
    void     *cont_fn;       /* pcStack_88 */
    uint64_t ev_sign;        /* uVar19 (epilogue) */
    ulong    *link;          /* puVar13 (epilogue) */
    uint     link_key;       /* uVar27 (epilogue) */
    uint     spin_hash;      /* uVar17 (epilogue) */
    int      cond1;          /* bVar10 */
    int      cond2;          /* bVar11 */

    flags_i = (int)flags;
    if (old == 0x80000000) {
        cpu_id = 0x80000000;
        if (flags_i != 0) {
            cpu_id = 0xb0000000;
        }
        old = *(ulong *)(lock + 2);
        if (old == 0x80000000) {
            *(ulong *)(lock + 2) = (ulong)(*(uint32_t *)((char *)thread + 0x518) | cpu_id);
        }
    }
    if ((old & 0xffffffff7fffffff) == 0) {        /* fast path: lock free */
        class_idx = 4;
        if (flags_i != 0) {
            class_idx = 5;
        }
        tag = (ushort)*lock;
        if (old != 0) {
            grp = lck_class_data(tag);
            cnt2 = *(ulong *)(grp + 0xe8);
            *(ulong *)(grp + 0xe8) = cnt2 + 1;
            cnt = *(ulong *)(grp + 0xf8);
            if (cnt != 0) {
                u9 = (cnt != 0) ? cnt2 / cnt : 0;
                if (cnt2 == u9 * cnt) {
                    lock_stat_record(*(uint32_t *)(grp + 0xf4), (void *)grp, cnt2, 0, 0, 0);
                }
            }
        }
        if (hv_lock_trace_60[class_idx] == 0) {
            return;
        }
        lock_stat_record(hv_lock_trace_60[class_idx], lock,
                         (uint64_t)lck_class_ptr(tag), 0, 0, 0);
        return;
    }
    cpu_id = *(uint32_t *)((char *)thread + 0x518);
    if (flags_i == 0) {
        *(int *)((char *)thread + 0x1c0) += 1;
        trace_id = 10;
    }
    else {
        trace_id = 0xb;
    }
    dropped = 0;
    waitq   = 0;
    owner_slot = (ulong *)(lock + 2);
    cur_thread = thread;

    for (;;) {
        state = *owner_slot;
        st32 = (uint)state;
        owner32 = st32 & 0xfffffff;
        if (owner32 == cpu_id) {
            lck_mtx_self_owned_panic(lock, cur_thread);   /* c0e4c94, noreturn */
        }
        lock_state = *lock;
        if (st32 == 0xf0fe2007 || (lock_state & 0xff000000) != 0x22000000) {
            break;      /* -> bad-state panic c0e4c28 */
        }
        if ((state & 0xffffffff7fffffff) == 0) {          /* still free: try CAS */
            if (*owner_slot == state) {
                *owner_slot = state | 0x10000000;
                goto try_acquire;
            }
        }
        else {
            flags_u = (uint)flags;
            if ((int)st32 < 0) {                          /* contended: stats */
                grp = lck_class_data((uint16_t)lock_state);
                cnt2 = *(ulong *)(grp + 0x118);
                *(ulong *)(grp + 0x118) = cnt2 + 1;
                cnt = *(ulong *)(grp + 0x128);
                if (cnt == 0) {
                    goto wait_trace0;
                }
                u9 = (cnt != 0) ? cnt2 / cnt : 0;
                if (cnt2 != u9 * cnt) {
                    goto wait_trace0;
                }
                lock_stat_record(*(uint32_t *)(grp + 0x124), (void *)grp, cnt2, 0, 0, 0);
                if (flags_u == 0) {
                    goto wait_trace1;
                }
wait_trace2:
                if (hv_lock_trace_8c == 0) {
                    ts = 0;
                }
                else {
                    base = *(long *)(*(long *)((char *)thread + 0x1b8) + 0x58);
                    do {
                        ev = base;
                        ts = UnkSytemRegRead(3, 4, 0xf, 10, 6);
                        base = *(long *)(*(long *)((char *)thread + 0x1b8) + 0x58);
                    } while (base != ev);
                    ts = ts + ev;
                }
                if (flags_u != 2) {
                    goto wait_joined;
                }
                cond1 = 1;
                goto waitq_cas;
            }
            else {
wait_trace0:
                if (flags_u != 0) {
                    goto wait_trace2;
                }
wait_trace1:
                if (hv_lock_trace_88 == 0) {
                    ts = 0;
                }
                else {
                    base = *(long *)(*(long *)((char *)thread + 0x1b8) + 0x58);
                    do {
                        ev = base;
                        ts = UnkSytemRegRead(3, 4, 0xf, 10, 6);
                        base = *(long *)(*(long *)((char *)thread + 0x1b8) + 0x58);
                    } while (base != ev);
                    ts = ts + ev;
                }
wait_joined:
                if ((((state & 0xfffffff) != 0) && (state >> 0x30 == 0)) &&
                    ((st32 >> 0x1c & 1) == 0)) {
                    if (owner32 - 1 < 0xffffe) {
                        lock_state = waitq_chain_secret;
                        if ((waitq_chain_secret ^ owner32) != 0xfffff) {
                            lock_state = waitq_chain_secret ^ owner32;
                        }
                        wait_tab = waitq_chain_table[0x16 - LZCOUNT(lock_state | 0x3ff)];
                        if (wait_tab != 0) {
                            chain = *(long *)((char *)wait_tab + (ulong)lock_state * 8);
                            cond1 = 0;
                            if (chain == 0) {
                                goto waitq_cas;
                            }
                            ev_found = 0;
                            waitq_chain_lock((void *)chain);                 /* b840260 */
                            flags_i = waitq_chain_next((void *)(chain + 0x1b8), &ev_found);  /* b75fa98 */
                            if ((flags_i == 0) && (ev_found != 0)) {
                                goto wait_prep;
                            }
                        }
                    }
                    cond1 = 0;
waitq_cas:
                    cnt2 = *owner_slot;
                    do {
                        if ((cnt2 & 0xffff10000000) != 0) {
                            waitq_drop(lock, 0);           /* b7f15fc */
                            goto waitq_drop_done;
                        }
                        u12 = cnt2 | 0x10000000;
                        cond2 = (*owner_slot != cnt2);
                        cnt2 = *owner_slot;
                    } while (cond2);
                    *owner_slot = u12;
waitq_drop_done:
                    dropped = 1;
                    goto block_cont;
                }
wait_prep:
                waitq_prepare(lock);                       /* b7f1318 */
                cond1 = 0;
            }
        }
block_cont:
        state_hi = state & 0x80000000;   /* uVar20 */
        state = (ulong)(st32 & 0x80000000);
        lock_trace_record(trace_id, lock, *lock & 0xffffff, ts);   /* b7f0794 */
        flags = *(ulong *)(lock + 2);
        if ((flags & 0xfffffff) == 0) {
            flags = (ulong)flags_u;                   /* local_7c */
            goto try_acquire;
        }
        if (cond1) {
            goto waitq_block_epilogue;
        }
        if (state_hi != 0) {
            grp = lck_class_data((ushort)*lock);
            class_idx = 0x100;
            if ((dropped & 1) == 0) {
                class_idx = 0x130;
            }
            wait_slot = (ulong *)(grp + class_idx);
            cnt2 = *wait_slot;
            *wait_slot = cnt2 + 1;
            cnt = wait_slot[2];
            if (cnt != 0) {
                u9 = (cnt != 0) ? cnt2 / cnt : 0;
                if (cnt2 == u9 * cnt) {
                    lock_stat_record(*(uint32_t *)((char *)wait_slot + 0xc),
                                     (void *)grp, cnt2, 0, 0, 0);
                }
            }
        }
        base = (long)cur_thread;
        *(uint *)owner_slot = (uint)flags | 0x50000000;
        chain = waitq_chain_read((uint)flags & 0xfffffff);
        if (hv_lock_trace_84 == 0) {
            ts = 0;
        }
        else {
            ev = *(long *)(*(long *)((char *)tpidr_el1 + 0x1b8) + 0x58);
            do {
                grp = ev;
                ts = UnkSytemRegRead(3, 4, 0xf, 10, 6);
                ev = *(long *)(*(long *)((char *)tpidr_el1 + 0x1b8) + 0x58);
            } while (ev != grp);
            ts = ts + grp;
        }
        if ((waitq == 0) && (waitq = (void *)waitq_lookup(lock, lock[1], 1), lock[1] == 0)) {
            lock[1] = *(uint32_t *)waitq >> 0xc;
        }
        *(byte *)(base + 0x58d) = 1;
        grp = tpidr_el1;
        *(long *)(grp + 0x38) = chain;
        *(byte *)(grp + 0x58c) = 0;
        if (chain != 0) {
            *(byte *)(grp + 0x58c) = 4;
            waitq_chain_unlock((void *)chain);             /* b8401d0 */
        }
        waitq_block(waitq, owner_slot, 0x40000000, 0);     /* b8561a8 */
        *(uint *)owner_slot = (uint)*owner_slot & 0xefffffff;
        if (*(int *)((char *)grp + 0x1c0) == 0) {
            goto depth_underflow;
        }
        depth = depth_leave((void *)grp);
        b6 = *(byte *)((char *)grp + 0x58c);
        waitq_release();                                   /* b852ee8 */
        if ((b6 >> 5 & 1) != 0) {
            waitq_pending_clear((uint64_t)waitq, 0x88);    /* b85304c */
        }
        kernel_lock_flush_ack(0, 0, 0);                    /* b812f5c */
        lock_trace_record(9, lock, *lock & 0xffffff, ts);   /* b7f0794 */
        *(int *)((char *)cur_thread + 0x1c0) += 1;
        flags = (ulong)flags_u;                            /* local_7c */
        /* loop back to try acquisition */
    }

    /* unreachable when state was corrupt: bad-state panic (noreturn) */
    lck_mtx_bad_state_panic(lock);                         /* c0e4c28 */

try_acquire:        /* LAB_fffffe000b7f1124 */
    owner32 = (uint)state;
    if ((waitq == 0) ||
        (flags_i = waitq_check_lock(lock, waitq), flags_i == 0)) {   /* b8527ec */
        cpu_id = owner32 | cpu_id;
        st32 = cpu_id;
        if (lock[1] != 0) {
            lock_state = waitq_hash_secret ^ lock[1];
            st32 = waitq_hash_secret;
            if (lock_state != 0xfffff) {
                st32 = lock_state;
            }
            class_idx = (ulong)st32 * 8;
            chain_ptr = (long *)((char *)waitq_hash_table[0x16 - LZCOUNT(st32 | 0x3ff)]
                                 + (int)class_idx);
            st32 = cpu_id | 0x40000000;
            if (*(long *)(*chain_ptr + 0x10) != (long)cur_thread) {
                st32 = cpu_id;
            }
        }
    }
    else {
        lock[1] = 0;
        st32 = owner32 | cpu_id;
    }
    flags_i = (int)flags;
    if (flags_i != 0) {
        st32 = st32 | 0x30000000;
    }
    *(uint *)owner_slot = st32;
    if (flags_i == 0) {
        base = tpidr_el1;
        if (*(int *)((char *)base + 0x1c0) == 0) {
depth_underflow:    /* LAB_fffffe000b7f1280 */
            kernel_panic();                       /* c0f1874, noreturn */
        }
        depth = depth_leave((void *)base);
    }
    if (waitq != 0) {
        waitq_release();                          /* b852ee8 */
    }
    class_idx = 4;
    if (flags_i != 0) {
        class_idx = 5;
    }
    tag = (ushort)*lock;
    if (owner32 != 0) {
        grp = lck_class_data(tag);
        cnt2 = *(ulong *)(grp + 0xe8);
        *(ulong *)(grp + 0xe8) = cnt2 + 1;
        cnt = *(ulong *)(grp + 0xf8);
        if (cnt != 0) {
            u9 = (cnt != 0) ? cnt2 / cnt : 0;
            if (cnt2 == u9 * cnt) {
                lock_stat_record(*(uint32_t *)(grp + 0xf4), (void *)grp, cnt2, 0, 0, 0);
            }
        }
    }
    if (hv_lock_trace_60[class_idx] == 0) {
        return;
    }
    lock_stat_record(hv_lock_trace_60[class_idx], lock,
                     (uint64_t)lck_class_ptr(tag), 0, 0, 0);
    return;

waitq_block_epilogue:   /* LAB_fffffe000b7f1310 — thread-block/waitq enqueue */
    ev = (long)kernel_waitq_event(lock);          /* c0e4cc4 */
    wait_ctrl = 0x22000000;
    cont_fn = (void *)waitq_prepare;              /* pcStack_88 = b7f1318 */
    ev_sign = -(uint64_t)(ev >> 0x37 & 1) & 0xffff800000000000 | (uint64_t)ev & 0x7fffffffffff;
    /* (the puStack_* slots here are the block frame the continuation reads) */
    if ((ev_sign + 0x20000000000) >> 0x24 < 0xd) {
        kernel_ptr_validate(ev_sign);             /* b7605fc */
    }
    type_p = (ushort *)(ev + 0xe);
    spin_stack = 0;
    wait_ctrl = 0;
    ts_val = 0;
    base = tpidr_el1;
    cpu_flags_p = *(long *)((char *)base + 0x1b8) + 0x4c;
    ts_val = UnkSytemRegRead(3, 4, 0xf, 0xb, 7);
    class_idx = ((ulong)*(ushort *)((char *)base + 0x1b0) & 0x3fff) << 2 | 1;
    link = &hv_waitq_link_100[class_idx];
    *link = (ulong)type_p;
    *(uint16_t *)(&hv_waitq_link_110[class_idx * 0x40]) = 2;
    tag = *type_p;
    *type_p = (ushort)class_idx;
    LORelease();
    if (tag != 0) {
        *(ulong **)(&hv_waitq_link_108[(ulong)(uint)tag * 0x40]) = link;
        link = (ulong *)waitq_link_init(type_p, link, 2, (void *)ev, lck_mtx_t_name);  /* b7f8158 */
        if (link == 0) {
            goto waitq_clear_done;                /* LAB_155c */
        }
    }
    wait_slot = (ulong *)(ev + 8);
    link_key = ((int)(uintptr_t)link + 0xf3a0bf00U) >> 6 & 0xffff;
    spin_hash = (int)((ulong)type_p >> 4) * 0x5052acdb;
    spin_hash = spin_hash >> 0x18 ^ spin_hash;
cas_retry:      /* LAB_fffffe000b7f1438 */
    state = *wait_slot;
    cond1 = (state & 0xffff00000000) == 0;
    cond2 = (state & 0x10000000) == 0;
    if ((state & 0xfffffff) == 0 && (cond2 && cond1)) {
        owner32 = (uint)(ushort)(state >> 0x30);
        cnt = 0;
        if (link_key != owner32) {
            cnt = state & 0xffff000000000000;
        }
        mon_status = '\x01';
        cond1 = (int)ExclusiveMonitorPass(wait_slot, 0x10);
        if (cond1) {
            *wait_slot = state & 0xffffffff | cnt | 0x10000000;
            mon_status = ExclusiveMonitorsStatus();
        }
        if (mon_status == '\0') {
            if (link_key != owner32) {
                state = link[1];
                if (state == 0) {
                    state = waitq_link_get(link + 1, 0);   /* b7f84e0 */
                }
                *(uint16_t *)(state + 0x12) = 1;
            }
            *link = 0;
            link[1] = 0;
            link[2] = 0;
            return;
        }
        if ((wait_ctrl & 0x1000000000000) != 0) {
            goto waitq_link_free;               /* LAB_1598 */
        }
spin_wait:      /* LAB_fffffe000b7f14bc */
        lock_trace_cont(&cpu_flags_p);          /* b7f191c */
        spin_p = (char *)((ulong)(spin_hash >> 3 & 0x1c) * 0x40
                          + (ulong)(spin_hash & 0x1f) + -0x1fff3a0bee0);
        if (spin_stack != 0) {
            spin_p = spin_stack;
        }
        spin_stack = spin_p;
        if (*spin_p != '\0') {
            waitq_link_validate(link, type_p);  /* b7f85cc */
        }
        goto cas_retry;
    }
    if ((wait_ctrl & 0x1000000000000) == 0) {
        WaitForEvent();
        if ((((state & 0xfffffff) != 0) && (cond2 && cond1)) &&
            (((wait_ctrl & 0x1000000000000) == 0 &&
              (flags_i = waitq_pending((uint)state & 0xfffffff), flags_i == 0)))) {
            goto waitq_link_free;               /* LAB_1598 */
        }
        goto spin_wait;
    }
    ClearExclusiveLocal();
waitq_link_free:    /* LAB_fffffe000b7f1598 */
    wait_slot = link + 1;
    if (*wait_slot == 0) {
        link_key = ((int)(uintptr_t)link + 0xf3a0bf00U) >> 6;
        tag = *type_p;
        if (tag == (ushort)link_key) {
            *type_p = 0;                        /* in_wzr */
        }
        if ((uint)tag != (link_key & 0xffff)) {
            goto link_unlink;                   /* LAB_15c4 */
        }
    }
    else {
link_unlink:
        state = *wait_slot;
        if (state == 0) {
            state = waitq_link_get(wait_slot, 0);   /* b7f84e0 */
        }
        *(uint16_t *)(state + 0x12) = 1;
    }
    *link = 0;
    link[1] = 0;
    link[2] = 0;
waitq_clear_done:   /* LAB_fffffe000b7f155c */
    waitq_drop((void *)ev, 0);                  /* b7f15fc */
    return;
}
