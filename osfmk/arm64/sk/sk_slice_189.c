/* Recreated from cl4_kernel.raw (cL4 Secure Kernel, arm64e, image base 0) —
 * the cL4 microkernel (GL1). Ground truth: Ghidra FUN_ names + addresses.
 * All names are estimates unless string/header matched.
 *
 * SK189 slice (0x0040aa98-0x0040fcb4): the Swift `_Concurrency` runtime
 * embedded in the cL4 kernel — the continuation / task / actor machinery that
 * the kernel's own Swift code uses for async operations.  Functionally this
 * region implements:
 *   - the continuation registry (Checked/UnsafeContinuation) with a hash-set
 *     of outstanding continuations and a mutex/condition-variable wake path
 *     (resume/suspend of a kernel task on a continuation),
 *   - the TaskGroup result store: a lock-free SPSC record queue over a
 *     0x200-slot ring with a bitset allocator (POPCOUNT/LZCOUNT) for child
 *     completion records and "task local" state,
 *   - the task-local storage key/value tree (RB-tree of allocated task-local
 *     values keyed by key, with per-task iteration),
 *   - the actor executor enqueue/dequeue primitives (precondition-gated on
 *     non-NULL job/executor) and the task-suspend / executor-switch glue.
 *
 * Most of the region is Swift concurrency runtime compiled to machine code:
 * heap allocations, vtable dispatch, overflow-checked arithmetic and CAS
 * loops are rendered faithfully, but the high-level Swift semantics cannot be
 * fully recovered.  Confidence is medium for the accessor/state-machine
 * helpers and low for the heavy Swift-ABI functions.
 *
 * Anchoring ground-truth strings (in the binary):
 *   0x005d3f10 "__mtx_init: handle mutex failed (mtx)"
 *   0x005d3ee0 "__mtx_lock: handle mutex failed (mtx)"
 *   0x005dc7f3 "__mtx_init: handle (mtx_recursive) failed"
 *   0x005dc8b6 "__cnd_signal: handle condition failed (cnd)"
 *   0x005dc965 "__cnd_wait: handle condition  (cnd)"
 *   0x005dc85e "Resuming continuation for task: ..."
 *   0x005dc8ec "Initializing continuation for ta..."
 *   0x005dc7cf "not all allocations are deallocated"
 *   0x005dcb68 "TaskGroupStatus: "
 *   0x005dcb89 "error: task local detected illegal..."
 *   0x005dca22 / 0x005dca72 "only errors can be stored by a d..."/"Claimed NULL waitingTask!"
 *   0x005dd036 "Incorrect actor executor assumption"
 */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

typedef uint64_t word_t;

#define SK189_FATAL(addr) __builtin_trap()   /* SoftwareBreakpoint(1,<addr>) path */

/* ---- Shared kernel / Swift-runtime externs (ground truth FUN_ addresses). ----
 * Swift ABI arity is deliberately flexible (variadic): Ghidra renders the
 * unaff-register conventions with varying argument counts; the bodies call
 * these with the counts shown in each decompile. */

extern word_t sk_swift_current_task(void);                 /* FUN_0040880c */
extern word_t sk_swift_alloc(word_t, ...);                 /* FUN_0036a804 */
extern word_t sk_swift_array_buf_alloc(word_t, ...);       /* FUN_0036a940 */
extern word_t sk_swift_closure_box(word_t, ...);           /* FUN_0036bfe4 */
extern void   sk_swift_deinit_small(void);                 /* FUN_0036a244 */
extern void   sk_swift_destroy_small(void);                /* FUN_0036a2ac */
extern word_t sk_swift_release(word_t, ...);               /* FUN_0036b118 */
extern word_t sk_swift_retain(word_t, ...);                /* FUN_0036b270 */
extern void   sk_atomic_enter(word_t);                     /* FUN_0037a48c */
extern void   sk_atomic_exit(word_t);                      /* FUN_0037a978 */
extern void   sk_hashtable_resize(word_t, ...);            /* FUN_0037d700 */
extern int    sk_c11_mtx_init(word_t, word_t);             /* FUN_00118148 */
extern int    sk_c11_mtx_lock(word_t);                     /* FUN_00118164 */
extern int    sk_c11_mtx_unlock(word_t);                   /* FUN_00118194 */
extern int    sk_c11_mtx_trylock(word_t);                  /* FUN_00118114 */
extern int    sk_c11_cnd_init(word_t);                     /* FUN_001180fc */
extern int    sk_c11_cnd_wait(word_t, word_t);             /* FUN_0011812c */
extern void   sk_swift_fatal(word_t, ...) __attribute__((noreturn)); /* FUN_003a2578 */
extern void   sk_precond_fatal(word_t, ...) __attribute__((noreturn)); /* FUN_004ba640 */
extern word_t sk_swift_array_dealloc(word_t, ...);         /* FUN_00117e14 */
extern void   sk_free(word_t, ...);                        /* thunk_FUN_00012568 */
extern word_t sk_swift_hash8(word_t *);                    /* FUN_00112098 */
extern word_t sk_calloc(word_t, ...);                      /* FUN_00111890 */
extern word_t sk_memmove(word_t, ...);                     /* FUN_00117d14 */
extern void   sk_once_gate(word_t, ...);                   /* FUN_003d3dd8 */
extern void   sk_lock_exit(void);                          /* FUN_0035b228 */
extern int    sk_error_str(word_t, word_t, word_t, ...);   /* FUN_00116bb4 */
extern word_t sk_error_fmt(word_t, ...);                   /* FUN_001131f4 */
extern word_t sk_error_fmt2(word_t, ...);                  /* FUN_00113c30 */
extern word_t sk_error_fmt3(word_t, ...);                  /* FUN_0011394c */
extern void   sk_str_append2(word_t, ...);                 /* FUN_00112db4 */
extern void   sk_str_render(word_t, ...);                  /* FUN_00112e8c */
extern word_t sk_heap_alloc(word_t, ...);                  /* FUN_000101a0 */
extern int    sk_runtime_once(word_t, ...);                /* FUN_003697c4 */
extern int    sk_runtime_once2(void);                      /* FUN_00369818 */
extern word_t sk_ctx_save(word_t, ...);                    /* FUN_00408834 */
extern void   sk_ctx_save2(word_t);                        /* FUN_00408864 */
extern void   sk_ctx_restore(void);                        /* FUN_004087cc */
extern void   sk_ctx_restore2(word_t);                     /* FUN_00408784 */
extern void   sk_task_resume(word_t, word_t, word_t);      /* FUN_00408ae4 */
extern word_t sk_executor_enq(word_t, ...);                /* FUN_003a25b8 */
extern void   sk_executor_enq2(word_t, word_t, ...);       /* FUN_003d5338 */
extern word_t sk_executor_enq3(word_t, word_t, ...);       /* FUN_003d5370 */
extern word_t sk_executor_deq(word_t, word_t, ...);        /* FUN_003d5308 */
extern void   sk_ctx_push(void);                           /* FUN_001a8564 */
extern void   sk_ctx_pop(word_t, ...);                     /* FUN_003509ec */
extern void   sk_ctx_pop2(void);                           /* FUN_0035199c */
extern void   sk_ctx_swap(word_t, ...);                    /* FUN_003523fc */
extern void   sk_actor_enter(word_t, ...);                 /* FUN_00350af4 */
extern void   sk_actor_leave(void);                        /* FUN_00350518 */
extern void   sk_sched_enter(word_t, ...);                 /* FUN_00229a3c */
extern void   sk_sched_enter2(void);                       /* FUN_0006b6f4 */
extern void   sk_task_switch1(void);                       /* FUN_0041001c */
extern void   sk_task_switch2(void);                       /* FUN_00410414 */
extern void   sk_task_switch3(void);                       /* FUN_004110ec */
extern void   sk_task_switch4(void);                       /* FUN_00411624 */
extern void   sk_task_switch5(void);                       /* FUN_004080b0 */
extern void   sk_task_switch6(void);                       /* FUN_00458200 */
extern void   sk_task_switch7(void);                       /* FUN_00458780 */
extern void   sk_task_switch8(void);                       /* FUN_00100efc */
extern void   sk_swift_identity(word_t, ...);              /* FUN_0001a1c8 */
extern word_t sk_swift_hotpath(word_t, ...);               /* FUN_00361528 */

/* Register-held self/context pointers (Ghidra sk_reg_x20/x21/x22/w19/w4):
 * the arm64e callee-saved registers carrying the Swift self / accessor-context
 * value. Represented as scalar words; dereferenced with explicit casts. */
extern word_t sk_reg_x20;
extern word_t sk_reg_x21;
extern word_t sk_reg_x22;
extern word_t sk_reg_w19;
extern word_t sk_reg_w4;

/* Global concurrency-runtime state (Ghidra DAT_ addresses). */
#define SK_TASK_REGISTRY         0x6c0c48   /* registry of continuations */
#define SK_REGISTRY_MTX          0x6c0c20   /* registry mutex (mtx) */
#define SK_REGISTRY_CND          0x6c0c78   /* registry condition var */
#define SK_TASK_LOCAL_ROOT       0x6c0c80   /* task-local store root flag */
#define SK_TASK_LOCAL_BASE       0x6c0c88   /* task-local store base */
#define SK_CONTINUATION_TYPE     0x67f4f0   /* continuation type metadata */
#define SK_CONTINUATION_TYPE_B   0x67f470   /* variant continuation metadata */
#define SK_RECORD_BUFFER_TYPE    0x6adfa8   /* task-group record buffer type */
#define SK_EXECUTOR_TYPE         0x67f4b0   /* executor type metadata */
#define SK_EMPTY_VEC             0x657778   /* Swift empty-vector sentinel */

/* =====================================================================
 * Continuation registry primitives.
 * ===================================================================== */

/* FUN_0040aa98 @ 0x0040aa98   (est. sk_cont_init_dispatch)
 * Ghidra: void FUN_0040aa98(undefined8 param_1)
 * Initializes a continuation dispatch record: calls the task-record allocator
 * then the continuation record hook. Thin two-call wrapper.
 * Confidence: low */
void sk_cont_init_dispatch(word_t param_1)
{
        sk_task_record_alloc(param_1, 0);
        sk_cont_record_init(param_1);
        return;
}

/* FUN_0040aac8 @ 0x0040aac8   (est. sk_continuation_create)
 * Ghidra: void FUN_0040aac8(int param_1, undefined8 param_2)
 * Allocates a 0x50-byte continuation record, seeds the header
 * (0x3900c02952800029, kind=3), stores the selector/kind byte
 * (param_1<<8|0xc3), zeroes fields at +0x24/+0x2c/+0x34, then stores the
 * completion closure (FUN_00409818), the current-task token and param_2.
 * Confidence: medium */
void sk_continuation_create(word_t kind_hi, word_t param_2)
{
        word_t *rec;

        rec = (word_t *)sk_swift_alloc(0x50, 0xf);
        rec[0] = 0x3900c02952800029;
        rec[1] = 3;
        *(uint *)(rec + 4) = (uint)kind_hi << 8 | 0xc3;
        *(word_t *)((long)rec + 0x2c) = 0;
        *(word_t *)((long)rec + 0x24) = 0;
        *(uint *)((long)rec + 0x34) = 0;
        rec[7] = 0x409818;   /* FUN_00409818 completion closure */
        rec[8] = sk_swift_current_task();
        rec[9] = param_2;
        return;
}

/* FUN_0040ab60 @ 0x0040ab60   (est. sk_task_continuation_init)
 * Ghidra: long FUN_0040ab60(long param_1, ulong param_2)
 * The continuation-registry initializer for a kernel task.  Seeds the
 * continuation record: flags in the low bits of param_2 are unpacked into
 * +0x10 (bit0=1,bit3->1), +0x18 (bit2), zeroing +0x20/+0x30/+0x38/+0x40.
 * If bit2 set, registers a waiting-task node at the task's +0xa0 and links it
 * into the registry's continuation set via sk_cont_set_link.  Sets the task's
 * owner (+0x40) and the wake function (+0x38).  Takes the registry mutex
 * (0x6c0c20) and appends the continuation into the registry set
 * (sk_registry_add at 0x6c0c48); panics "Initializing continuation for ta..."
 * if it cannot be added.  Runs once the mtx-init once-gate.
 * Confidence: low
 * Notes: shared string 0x005dc8ec; registry lock/unlock helpers
 *   FUN_00118148/FUN_00118164/FUN_003d3dd8; DAT_006c0c40 once-gate. */
long sk_task_continuation_init(long task, word_t flags)
{
        int once;
        long owner;
        word_t wake_slot;

        *(ulong *)(task + 0x10) = (flags & 1) | ((flags >> 3 & 1) << 1);
        *(word_t *)(task + 0x20) = 0;
        if (((uint)flags >> 1 & 1) == 0) {
                *(word_t *)(task + 0x30) = 0;
                *(word_t *)(task + 0x38) = 0;
        }
        *(ulong *)(task + 0x18) = flags >> 2 & 1;
        *(word_t *)(task + 0x40) = 0;
        owner = sk_swift_current_task();
        if (((uint)flags >> 2 & 1) != 0) {
                word_t *node = (word_t *)sk_cont_set_alloc(owner, 0x30);
                node[0] = 0;
                node[1] = 0;
                *(uint *)(node + 4) = 2;
                node[5] = owner;
                node[2] = task;
                *(word_t **)(owner + 0xa0) = node;
                word_t *slot = (word_t *)(*(long *)(owner + 0x60) & 0xffffffffffffffff);
                word_t slot_hi = *(word_t *)(owner + 0x68);
                word_t *arr = (word_t *)&node;
                word_t *pair = (word_t *)&slot;
                sk_cont_set_link(owner, node, &slot, 0x40af00, &arr);
                sk_swift_destroy_small(owner + 0x50);
                sk_ctx_restore();
                sk_ctx_save();
        }
        *(long *)(owner + 0x40) = task;
        *(word_t *)(owner + 0x38) = *(word_t *)(task + 8);
        wake_slot = owner;
        if (DAT_006c0c40 == 0) {
                once = sk_runtime_once();
                DAT_006c0c40 = 1;
                if (once == 0) {
                        DAT_006c0c40 = 2;
                }
        }
        if (DAT_006c0c40 == 1) {
                word_t *mtx = (word_t *)0x6c0c20;
                if (-1 < DAT_006c0c30) {
                        if (DAT_006c0c30 == 0) {
                                DAT_006c0c30 = 1;
                                once = sk_c11_mtx_init(0x6c0c20, 0);
                                if (once != 0) {
                                        sk_swift_fatal(0x5d3f10); /* "__mtx_init..." */
                                }
                                DAT_006c0c30 = -1;
                        } else {
                                do { } while (-1 < DAT_006c0c30);
                        }
                }
                once = sk_c11_mtx_lock(0x6c0c20);
                if (once != 0) {
                        sk_swift_fatal(0x5d3ee0); /* "__mtx_lock..." */
                }
                if (-1 < DAT_006c0c78) {
                        sk_once_gate(&DAT_006c0c78, 0x40b408);
                }
                sk_registry_add(0x6c0c48, &wake_slot, &wake_slot);
                if ((extraout_x1 & 1) == 0) {
                        sk_precond_fatal(0, 0x5dc8ec); /* "Initializing continuation for ta..." */
                }
                sk_lock_exit(&mtx);
        }
        return owner;
}

/* FUN_0040ada4 @ 0x0040ada4   (est. sk_continuation_destroy)
 * Ghidra: void FUN_0040ada4(long param_1)
 * Deinitializes a continuation record.  If not yet destroyed (state +0x18 != 2),
 * initializes a condition var (+0x40) and a mutex, sets state to 1, then waits
 * (cnd_wait loop) until state becomes 2, finally destroying both.  Then invokes
 * the task's wake function (via +0x08) or, when bit1 of +0x10 set, calls
 * FUN_00408db8(wake, +0x30, +0x38).  Traps on a corrupt canary.
 * Confidence: low
 * Notes: canary -0x2c8502b44bfffed6; cnd/mtx init strings 0x5dc931/0x5d3f10;
 *   FUN_0040b96c/0040b9a4/0040b9dc are mtx_lock/cnd_wait/mtx_unlock wrappers. */
void sk_continuation_destroy(long task)
{
        int once;
        long state;
        byte wake_bits;

        state = *(long *)(task + 0x18);
        if (state != 2) {
                sk_swift_current_task();
                once = sk_c11_cnd_init(&cnd_cond);
                if (once != 0) {
                        sk_swift_fatal(0x5dc931); /* "__cnd_init..." */
                }
                once = sk_c11_mtx_init(&cnd_mtx, 0);
                if (once != 0) {
                        sk_swift_fatal(0x5d3f10); /* "__mtx_init..." */
                }
                *(byte **)(task + 0x40) = (byte *)&cnd_cond;
                if (*(long *)(task + 0x18) == state) {
                        *(long *)(task + 0x18) = 1;
                        sk_mtx_lock(&cnd_cond);
                        do {
                                sk_cnd_wait(&cnd_cond);
                        } while (*(long *)(task + 0x18) != 2);
                        sk_mtx_unlock(&cnd_cond);
                }
                sk_cnd_destroy(&cnd_cond);
                sk_mtx_destroy(&cnd_mtx);
        }
        if ((*(byte *)(task + 0x10) >> 1 & 1) == 0) {
                if (canary_ok) {
                        (**(code **)(task + 8))();
                        return;
                }
        } else if (canary_ok) {
                sk_cont_dispatch(*(code **)(task + 8), *(word_t *)(task + 0x30),
                                 *(word_t *)(task + 0x38));
                return;
        }
        sk_swift_fatal(0);
}

/* FUN_0040af00 @ 0x0040af00   (est. sk_cont_set_link)
 * Ghidra: undefined8 FUN_0040af00(undefined8 *param_1, ...)
 * Registry-append helper used by the task-continuation init path: clears the
 * record's tag bits (|0x4000) and calls the record-commit FUN_0040c84c with
 * the low byte. Returns 1 (success).
 * Confidence: low */
word_t sk_cont_set_link(word_t *rec, word_t a2, word_t a3, word_t *flags)
{
        word_t f;

        f = *flags;
        *flags = (f & 0xfffff3ff) | 0x4000;
        sk_record_commit(*(word_t *)*rec, *(byte *)rec[1], (uint)f & 0xff);
        return 1;
}

/* FUN_0040af04 @ 0x0040af04   (est. sk_cont_set_link_b)
 * Ghidra: undefined8 FUN_0040af04(undefined8 *param_1, ...)
 * Same shape as 0040af00 (alternate record-link variant).
 * Confidence: low */
word_t sk_cont_set_link_b(word_t *rec, word_t a2, word_t a3, word_t *flags)
{
        word_t f;

        f = *flags;
        *flags = (f & 0xfffff3ff) | 0x4000;
        sk_record_commit(*(word_t *)*rec, *(byte *)rec[1], (uint)f & 0xff);
        return 1;
}

/* FUN_0040af3c @ 0x0040af3c   (est. sk_cont_block_dealloc)
 * Ghidra: long * FUN_0040af3c(long *param_1)
 * Deallocates a continuation block: if the block is empty, walks the linked
 * free-list (via +0x10 count of each allocation, FUN_00117e14 dealloc per
 * node) and returns; otherwise panics "not all allocations are deallocated".
 * Confidence: low */
word_t *sk_cont_block_dealloc(word_t *block)
{
        word_t *p;

        if (*block == 0) {
                p = block;
                if (((*(byte *)(block + 2) & 1) != 0) &&
                    (sk_swift_array_dealloc(block[1], 8, 0, 8, 8),
                     (*(byte *)(block + 2) & 1) != 0)) {
                        p = (word_t *)block[1];
                }
                sk_cont_free_nodes(block, p + 1);
                return block;
        }
        sk_precond_fatal(0, 0x5dc7cf); /* "not all allocations are deallocated" */
}

/* FUN_0040afb8 @ 0x0040afb8   (est. sk_cont_free_nodes)
 * Ghidra: long FUN_0040afb8(long param_1, long *param_2)
 * Walks a linked list of allocation nodes (each node has next at +8 and a
 * per-node allocation count at +0x10), deallocating each via FUN_00117e14 and
 * decrementing the block's outstanding-allocation counter (+0x10) by 2 each.
 * Returns the total count of deallocated units.
 * Confidence: medium */
long sk_cont_free_nodes(long block, word_t *head)
{
        long node;
        long next;
        long count;

        node = *head;
        *head = 0;
        if (node == 0) {
                count = 0;
        } else {
                count = 0;
                do {
                        next = *(long *)(node + 8);
                        count = count + (ulong)*(uint *)(node + 0x10);
                        sk_swift_array_dealloc(node, 8, 0, 8, 8);
                        sk_free(node);
                        *(int *)(block + 0x10) = *(int *)(block + 0x10) + -2;
                        node = next;
                } while (next != 0);
        }
        return count;
}

/* FUN_0040b03c @ 0x0040b03c   (est. sk_cont_save_b)
 * Ghidra: void FUN_0040b03c(void)
 * Saves the continuation context then runs the block teardown hook.
 * Confidence: low */
void sk_cont_save_b(void)
{
        sk_ctx_save();
        sk_cont_teardown_block();
        return;
}

/* FUN_0040b084 @ 0x0040b084   (est. sk_cont_save_c)
 * Ghidra: void FUN_0040b084(void)
 * Same shape as 0040b03c (alternate save+teardown hook).
 * Confidence: low */
void sk_cont_save_c(void)
{
        sk_ctx_save();
        sk_cont_teardown_block();
        return;
}

/* FUN_0040b0cc @ 0x0040b0cc   (est. sk_cont_save_d)
 * Ghidra: void FUN_0040b0cc(void)
 * Releases the saved self pointer, saves the continuation context, runs the
 * block teardown hook and releases the returned token.
 * Confidence: low */
void sk_cont_save_d(void)
{
        word_t tok;

        sk_swift_release(*(word_t *)(sk_reg_x22 + -0x10));
        tok = sk_ctx_save();
        sk_cont_teardown_block();
        sk_swift_release(tok);
        return;
}

/* FUN_0040b128 @ 0x0040b128   (est. sk_cont_save_e)
 * Ghidra: void FUN_0040b128(void)
 * Saves the continuation context, runs the block teardown hook, releases the
 * returned token.
 * Confidence: low */
void sk_cont_save_e(void)
{
        word_t tok;

        tok = sk_ctx_save();
        sk_cont_teardown_block();
        sk_swift_release(tok);
        return;
}

/* FUN_0040b17c @ 0x0040b17c   (est. sk_cont_teardown_block)
 * Ghidra: void FUN_0040b17c(long param_1, long param_2, undefined8 param_3)
 * Stores the teardown context word at param_2-8 then dispatches the 
 * continuation state machine (sk_cont_state_dispatch at +0x50).  If the task
 * has the resume flag (bit1 of +0x23) set, runs the resume hook
 * (FUN_004098c8).
 * Confidence: low */
void sk_cont_teardown_block(long task, long ctx, word_t param_3)
{
        *(word_t *)(ctx + -8) = param_3;
        sk_cont_state_dispatch(task + 0x50, task);
        if ((*(byte *)(task + 0x23) >> 1 & 1) == 0) {
                return;
        }
        sk_cont_resume_hook(task, ctx);
        return;
}

/* FUN_0040b1d0 @ 0x0040b1d0   (est. sk_cont_state_dispatch)
 * Ghidra: void FUN_0040b1d0(long param_1, long param_2)
 * The continuation state machine dispatcher.  If the task flags (at +0x20)
 * have bit 0x1e set, runs the exception hook (FUN_0040c554); if bit 0x1d set,
 * runs the cancel hook (FUN_0040c434).  Then performs the CAS state transition
 * on the task's +0x60/+0x68 record (setting bit 0x2000) and finally appends
 * the task to the run queue via sk_runq_append (FUN_0040f23c at +0x38).
 * Confidence: low */
void sk_cont_state_dispatch(long queue, long task)
{
        uint flags;
        long a, b;
        long ca, cb;

        flags = *(uint *)(task + 0x20);
        if ((flags >> 0x1e & 1) != 0) {
                sk_cont_exception(task);
                flags = *(uint *)(task + 0x20);
        }
        if ((flags >> 0x1d & 1) != 0) {
                sk_cont_cancel(task);
        }
        a = *(long *)(task + 0x60);
        b = *(long *)(task + 0x68);
        ca = *(long *)(task + 0x60);
        cb = *(long *)(task + 0x68);
        if ((ca == b) && (cb == a)) {
                *(long *)(task + 0x60) = b;
                *(ulong *)(task + 0x68) = (ulong)((uint)a & 0xffffc3ff | 0x2000);
        }
        if (ca != a || cb != b) {
                do {
                        a = *(long *)(task + 0x60);
                        b = *(long *)(task + 0x68);
                        if ((a == cb) && (b == ca)) {
                                *(long *)(task + 0x60) = cb;
                                *(ulong *)(task + 0x68) = (ulong)((uint)ca & 0xffffc3ff | 0x2000);
                        }
                        bool eq_a = (a != ca);
                        bool eq_b = (b != cb);
                        ca = a;
                        cb = b;
                } while (eq_a || eq_b);
        }
        sk_runq_append(queue + 0x38, task);
        return;
}

/* FUN_0040b280 @ 0x0040b280   (est. sk_mtx_recursive_init)
 * Ghidra: undefined8 FUN_0040b280(undefined8 param_1)
 * Initializes a recursive mutex (mtx type 2); panics on failure with
 * "__mtx_init: handle (mtx_recursive) failed".  Returns the mutex.
 * Confidence: high */
word_t sk_mtx_recursive_init(word_t mtx)
{
        int rc;

        rc = sk_c11_mtx_init(mtx, 2);
        if (rc == 0) {
                return mtx;
        }
        sk_swift_fatal(0x5dc7f3); /* "__mtx_init: handle (mtx_recursive) failed" */
}

/* FUN_0040b2c8 @ 0x0040b2c8   (est. sk_cont_resume_for_task)
 * Ghidra: void FUN_0040b2c8(undefined8 param_1)
 * Resumes a continuation for a kernel task: locks the registry mutex
 * (0x6c0c20), then pulls the waiting task out of the registry set
 * (sk_registry_pop at 0x6c0c48) and panics "Resuming continuation for task: ..."
 * if there is none.  Unlocks on success.
 * Confidence: high
 * Notes: strings 0x5d3f10/0x5d3ee0/0x5dc85e; DAT_006c0c40 once-gate; registry
 *   pop helper FUN_0040b424. */
void sk_cont_resume_for_task(word_t task)
{
        int once;
        word_t *mtx;
        word_t rec;
        word_t *slot;

        if (DAT_006c0c40 == 0) {
                once = sk_runtime_once();
                DAT_006c0c40 = 1;
                if (once == 0) {
                        DAT_006c0c40 = 2;
                }
        }
        if (DAT_006c0c40 == 1) {
                slot = (word_t *)0x6c0c20;
                if (-1 < DAT_006c0c30) {
                        if (DAT_006c0c30 == 0) {
                                DAT_006c0c30 = 1;
                                once = sk_c11_mtx_init(0x6c0c20, 0);
                                if (once != 0) {
                                        sk_swift_fatal(0x5d3f10); /* "__mtx_init..." */
                                }
                                DAT_006c0c30 = -1;
                        } else {
                                do { } while (-1 < DAT_006c0c30);
                        }
                }
                once = sk_c11_mtx_lock(0x6c0c20);
                if (once != 0) {
                        sk_swift_fatal(0x5d3ee0); /* "__mtx_lock..." */
                }
                if (-1 < DAT_006c0c78) {
                        sk_once_gate(&DAT_006c0c78, 0x40b408);
                }
                rec = sk_registry_pop(0x6c0c48, &task);
                if (rec == 0) {
                        sk_precond_fatal(0, 0x5dc85e); /* "Resuming continuation for task: ..." */
                }
                sk_lock_exit(slot);
        }
        return;
}

/* FUN_0040b424 @ 0x0040b424   (est. sk_registry_pop)
 * Ghidra: bool FUN_0040b424(undefined8 param_1)
 * Pops a waiting task out of the registry set: looks it up and, if present,
 * removes it (FUN_0040b548).  Returns whether a task was removed.
 * Confidence: high */
bool sk_registry_pop(word_t registry, word_t task)
{
        long node;

        node = sk_cont_set_find(task);
        if (node != 0) {
                sk_cont_set_remove(registry, node);
        }
        return node != 0;
}

/* FUN_0040b45c @ 0x0040b45c   (est. sk_cont_set_find)
 * Ghidra: long FUN_0040b45c(long *param_1, long *param_2)
 * Hash-set lookup for a continuation keyed by {hash, key}: computes the bucket
 * via sk_swift_hash8 and scans the collision chain for a matching {hash,key}
 * pair; returns the node or 0.  Traps (SoftwareBreakpoint 0x40b548) on an
 * out-of-range bucket index.
 * Confidence: medium */
long sk_cont_set_find(word_t *set, word_t *key)
{
        word_t hash, keyv;
        word_t mask;
        word_t idx;
        word_t bucket_count;
        word_t chain_count;
        long node;

        bucket_count = set[1];
        if (bucket_count != 0) {
                if (set[4] == 0) {
                        return 0;
                }
                keyv = *key;
                hash = sk_swift_hash8(&keyv);
                mask = bucket_count - 1;
                if ((bucket_count & mask) == 0) {
                        idx = hash & mask;
                } else {
                        idx = hash;
                        if (bucket_count <= hash) {
                                chain_count = 0;
                                if (bucket_count != 0) {
                                        chain_count = hash / bucket_count;
                                }
                                idx = hash - chain_count * bucket_count;
                        }
                }
                if ((word_t)set[2] <= idx) {
                        SK189_FATAL(0x40b548);
                }
                node = *(long **)(*set + idx * 8);
                if (node == 0) {
                        return 0;
                }
                do {
                        while (1) {
                                node = *(long *)node;
                                if (node == 0) {
                                        return 0;
                                }
                                hash = *(long *)(node + 8);
                                if (hash != keyv) {
                                        break;
                                }
                                if (*(long *)(node + 0x10) == keyv) {
                                        return node;
                                }
                        }
                        if ((bucket_count & mask) == 0) {
                                hash = hash & mask;
                        } else if (bucket_count <= hash) {
                                chain_count = 0;
                                if (bucket_count != 0) {
                                        chain_count = hash / bucket_count;
                                }
                                hash = hash - chain_count * bucket_count;
                        }
                } while (hash == idx);
        }
        return 0;
}

/* FUN_0040b548 @ 0x0040b548   (est. sk_cont_set_remove)
 * Ghidra: undefined8 FUN_0040b548(undefined8 param_1, undefined8 *param_2)
 * Removes a node from the continuation set: unlinks it (FUN_0040b598) and
 * returns its stored value.  Traps if the node is null.
 * Confidence: medium */
word_t sk_cont_set_remove(word_t set, word_t *node)
{
        word_t value;
        long free_list[3];

        if (node != 0) {
                value = *node;
                sk_cont_set_unlink(free_list);
                long head = free_list[0];
                free_list[0] = 0;
                if (head != 0) {
                        sk_free(head, 0x18);
                }
                return value;
        }
        SK189_FATAL(0x40b598);
}

/* FUN_0040b598 @ 0x0040b598   (est. sk_cont_set_unlink)
 * Ghidra: void FUN_0040b598(undefined8 *param_1, long *param_2, long *param_3)
 * Unlinks a node from the hash-set bucket chain and re-roots the head of the
 * chain; returns the node into an internal free list (param_1).  Traps on a
 * bucket underflow.
 * Confidence: low
 * Notes: node at +8 holds the hash, +0x10 the key; param_1 receives the
 *   {node, bucket-head, flags} free-list record. */
void sk_cont_set_unlink(word_t *out, word_t *set, word_t *node)
{
        word_t bucket_count;
        word_t hash;
        word_t mask;
        word_t idx;
        word_t bucket_count2;
        word_t chain_count;
        word_t *head;
        long bucket_base;
        word_t *prev;
        word_t *cur;
        word_t next;

        bucket_count = set[1];
        hash = node[1];
        mask = bucket_count - 1;
        if ((bucket_count & mask) == 0) {
                hash = mask & hash;
        } else if (bucket_count <= hash) {
                chain_count = 0;
                if (bucket_count != 0) {
                        chain_count = hash / bucket_count;
                }
                hash = hash - chain_count * bucket_count;
        }
        bucket_count2 = set[2];
        if (bucket_count2 <= hash) {
                SK189_FATAL(0x40b6cc);
        }
        bucket_base = *set;
        head = *(word_t **)(bucket_base + hash * 8);
        do {
                prev = head;
                head = (word_t *)*prev;
        } while ((word_t *)*prev != node);
        if (prev == set + 3) {
                if (*node != 0) {
                        next = *(ulong *)(*node + 8);
                        if ((bucket_count & mask) == 0) {
                                next = next & mask;
                        } else if (bucket_count <= next) {
                                chain_count = 0;
                                if (bucket_count != 0) {
                                        chain_count = next / bucket_count;
                                }
                                next = next - chain_count * bucket_count;
                        }
                        if (next == hash) {
                                goto relink_tail;
                        }
                }
                *(word_t *)(bucket_base + hash * 8) = 0;
        } else {
                next = prev[1];
                if ((bucket_count & mask) == 0) {
                        next = next & mask;
                } else if (bucket_count <= next) {
                        chain_count = 0;
                        if (bucket_count != 0) {
                                chain_count = next / bucket_count;
                        }
                        next = next - chain_count * bucket_count;
                }
                if (next != hash) {
                        goto clear_head;
                }
        }
relink_tail:
        next = *node;
        if (next != 0) {
                word_t nh = *(ulong *)(next + 8);
                if ((bucket_count & mask) == 0) {
                        nh = nh & mask;
                } else if (bucket_count <= nh) {
                        chain_count = 0;
                        if (bucket_count != 0) {
                                chain_count = nh / bucket_count;
                        }
                        nh = nh - chain_count * bucket_count;
                }
                if (nh != hash) {
                        if (bucket_count2 <= nh) {
                                SK189_FATAL(0x40b6cc);
                        }
                        *(word_t **)(bucket_base + nh * 8) = prev;
                        next = *node;
                }
        }
        *prev = next;
        *node = 0;
        set[4] = set[4] - 1;
        out[0] = (word_t)node;
        out[1] = (word_t)(set + 3);
        *(byte *)(out + 2) = 1;
        *(uint *)((long)out + 0x11) = 0;
        *(uint *)((long)out + 0x14) = 0;
        return;
clear_head:
        *(word_t *)(bucket_base + hash * 8) = 0;
        goto relink_tail;
}

/* FUN_0040b6cc @ 0x0040b6cc   (est. sk_cnd_signal)
 * Ghidra: void FUN_0040b6cc(void)
 * Signals a condition variable (cnd_signal); panics "__cnd_signal: handle
 * condition failed (cnd)" on failure.
 * Confidence: high */
void sk_cnd_signal(void)
{
        int rc;

        rc = sk_c11_mtx_trylock(0);
        if (rc == 0) {
                return;
        }
        sk_swift_fatal(0x5dc8b6); /* "__cnd_signal..." */
}

/* FUN_0040b96c @ 0x0040b96c   (est. sk_mtx_lock)
 * Ghidra: void FUN_0040b96c(long param_1)
 * Locks the mutex at param_1+0x10; panics "__mtx_lock: handle mutex failed
 * (mtx)" on failure.
 * Confidence: high */
void sk_mtx_lock(long cnd)
{
        int rc;

        rc = sk_c11_mtx_lock(cnd + 0x10);
        if (rc == 0) {
                return;
        }
        sk_swift_fatal(0x5d3ee0); /* "__mtx_lock..." */
}

/* FUN_0040b9a4 @ 0x0040b9a4   (est. sk_cnd_wait)
 * Ghidra: void FUN_0040b9a4(long param_1)
 * Waits on the condition var at param_1 with its associated mutex at
 * param_1+0x10; panics "__cnd_wait..." on failure.
 * Confidence: high */
void sk_cnd_wait(long cnd)
{
        int rc;

        rc = sk_c11_cnd_wait(cnd, cnd + 0x10);
        if (rc == 0) {
                return;
        }
        sk_swift_fatal(0x5dc965); /* "__cnd_wait..." */
}

/* FUN_0040b9dc @ 0x0040b9dc   (est. sk_mtx_unlock)
 * Ghidra: void FUN_0040b9dc(long param_1)
 * Unlocks the mutex at param_1+0x10; panics "__mtx_unlock..." on failure.
 * Confidence: high */
void sk_mtx_unlock(long cnd)
{
        int rc;

        rc = sk_c11_mtx_unlock(cnd + 0x10);
        if (rc == 0) {
                return;
        }
        sk_swift_fatal(0x5d3f4d); /* "__mtx_unlock..." */
}

/* FUN_0040ba14 @ 0x0040ba14   (est. sk_task_exclusive_init)
 * Ghidra: void FUN_0040ba14(void)
 * Registers the two task-exclusive hooks (FUN_00409a54 for the exclusive
 * trampoline and the region-dispatch entry) with their closure boxes
 * (FUN_00409b14).  Boot-time one-time registration.
 * Confidence: low
 * Notes: closure box via FUN_0036bfe4; labels LAB_00409a48; registry slots
 *   0x6c0bb0/0x6c0be8. */
void sk_task_exclusive_init(void)
{
        word_t box[2];
        word_t box2;
        byte *code;
        word_t flags;
        word_t *fn;
        byte mtx[24];

        fn = (word_t *)0x409a44;
        flags = 0;
        box2 = 0;
        sk_swift_closure_box(mtx, &flags, &fn, &box2);
        box[0] = 0x503;
        box2 = 1;
        code = (byte *)0x409a48;
        sk_cont_register_excl(box, 0x6c0bb0, mtx, box);
        fn = (word_t *)0x409b14;
        flags = 0;
        box2 = 0;
        sk_swift_closure_box(mtx, &flags, &fn, &box2);
        box[0] = 0x502;
        box2 = 1;
        code = (byte *)0x409a48;
        sk_cont_register_excl(0x6c0be8, mtx, box);
        return;
}

/* FUN_0040bb18 @ 0x0040bb18   (est. sk_task_record_alloc)
 * Ghidra: void FUN_0040bb18(undefined8 param_1)
 * Allocates a task record of the given size from the continuation block
 * allocator: resolves the block (FUN_0040bb48) and appends the record.
 * Confidence: low */
void sk_task_record_alloc(word_t size)
{
        word_t block;

        sk_swift_current_task();
        block = sk_cont_block();
        sk_cont_block_alloc(block, size);
        return;
}

/* FUN_0040bb48 @ 0x0040bb48   (est. sk_cont_block)
 * Ghidra: long FUN_0040bb48(long param_1)
 * Resolves the continuation block allocator: if param_1 is non-null returns
 * param_1+0x70, else the process-wide task-local root (0x6c0c88) once its
 * flag (0x6c0c80) is set, else the freshly-initialized block.
 * Confidence: low */
long sk_cont_block(long param_1)
{
        word_t block;

        if (param_1 != 0) {
                return param_1 + 0x70;
        }
        if ((DAT_006c0c80 & 1) != 0) {
                return 0x6c0c88;
        }
        FUN_004ba704(&block);
        return block;
}

/* FUN_0040bcf8 @ 0x0040bcf8   (est. sk_cont_set_alloc)
 * Ghidra: void FUN_0040bcf8(undefined8 param_1, undefined8 param_2)
 * Allocates a record of size param_2 from the continuation block and appends
 * it (via FUN_0040bb98).
 * Confidence: low */
void sk_cont_set_alloc(word_t block, word_t size)
{
        word_t b;

        b = sk_cont_block();
        sk_cont_block_alloc(b, size);
        return;
}

/* FUN_0040bd24 @ 0x0040bd24   (est. sk_cont_record_init)
 * Ghidra: void FUN_0040bd24(undefined8 param_1)
 * Resolves the continuation block and initializes a record of the given size
 * (sk_cont_record_alloc).
 * Confidence: low */
void sk_cont_record_init(word_t param_1)
{
        word_t block;

        sk_swift_current_task();
        block = sk_cont_block();
        sk_cont_record_alloc(block, param_1);
        return;
}

/* FUN_0040bd54 @ 0x0040bd54   (est. sk_cont_record_alloc)
 * Ghidra: void FUN_0040bd54(undefined8 *param_1, undefined8 *param_2)
 * Appends an allocation record to a continuation block: if the current head
 * already owns this allocation it updates the running size and advances the
 * head; otherwise it reports an invalid free via FUN_004ba780.
 * Confidence: low */
void sk_cont_record_alloc(word_t *block, word_t *rec)
{
        word_t next;

        next = *block;
        if (next != 0 && (word_t *)(next + 0x10) == rec) {
                word_t hdr = *next;
                *(int *)(hdr + 0x14) = ((int)next - (int)hdr) - 0x20;
                *block = hdr;
                return;
        }
        FUN_004ba780(rec);
        return;
}

/* FUN_0040bda0 @ 0x0040bda0   (est. sk_cont_record_free)
 * Ghidra: void FUN_0040bda0(undefined8 param_1, undefined8 param_2)
 * Frees a record from the continuation block (block-relative free).
 * Confidence: low */
void sk_cont_record_free(word_t block, word_t rec)
{
        word_t b;

        b = sk_cont_block();
        sk_cont_record_alloc(b, rec);
        return;
}

/* FUN_0040bdd0 @ 0x0040bdd0   (est. sk_cont_wake_loop)
 * Ghidra: uint FUN_0040bdd0(long param_1, ulong param_2, ulong *param_3,
 *                           code *param_4, undefined8 param_5)
 * The continuation wake/suspend CAS loop: while the task state bit 9 is clear,
 * repeatedly invoke the state-machine callback (param_4) and, on success,
 * commit the transition to the task's +0x60/+0x68 record; once the flag is
 * set, fall through to the suspend path (FUN_0040bed0 with the callbacks
 * FUN_0040cc24/FUN_0040cc28). Returns bit0 of the outcome.
 * Confidence: low */
uint sk_cont_wake_loop(long task, word_t state, word_t *rec, word_t cb,
                       word_t cb_arg)
{
        word_t s, s2;
        word_t w;
        uint result;
        word_t *slot;
        byte flag;
        word_t *cb_slot;
        word_t newstate;

        s = (ulong)(uint)*rec;
        newstate = state;
        cb_slot = (word_t *)cb;
        cb_arg2 = cb_arg;
        if (((uint)*rec >> 9 & 1) == 0) {
                s2 = rec[1];
                do {
                        *(ulong *)(newstate + 8) = s2;
                        slot = (word_t *)(s & 0xffffffff);
                        byte *recp = (byte *)newstate;
                        result = (*cb_slot)(cb_arg2, *rec, rec[1], &slot);
                        if (result == 0) {
                                goto wake_done;
                        }
                        w = *rec;
                        s2 = rec[1];
                        s = *(ulong *)(task + 0x60);
                        s2 = *(ulong *)(task + 0x68);
                        if ((s == s2) && (s2 == w)) {
                                *(ulong *)(task + 0x60) = (ulong)recp;
                                *(word_t **)(task + 0x68) = slot;
                        }
                        if (s == w && s2 == s2) {
                                goto wake_done;
                        }
                        *rec = s;
                        rec[1] = s2;
                } while (((uint)s >> 9 & 1) == 0);
        } else {
                s = *rec;
                s2 = rec[1];
        }
        flag = 0;
        slot = &newstate;
        recp = &flag;
        cb_slot = &cb;
        sk_cont_suspend(task, s, s2, 0x40cc24, &stk, 0x40cc28, &slot);
        result = (uint)flag;
wake_done:
        return result & 1;
}

/* FUN_0040bed0 @ 0x0040bed0   (est. sk_cont_suspend)
 * Ghidra: void FUN_0040bed0(long param_1, ulong param_2, ulong param_3,
 *                           code *param_4, undefined8 param_5, code *param_6,
 *                           undefined8 param_7)
 * The core continuation suspend machinery: enters the atomic section on the
 * task's +0xb0 lock, then performs a CAS loop that sets bit 9 (and 0x200) on
 * the task record, committing the new state to +0x60/+0x68.  Once committed,
 * invokes the state callback (param_4) with the new state, then runs the
 * wait callback (param_6) in a loop until the record reverts to the original
 * state.  Exits the atomic section on completion.
 * Confidence: low
 * Notes: atomic enter/exit FUN_0037a48c/FUN_0037a978; CONCAT44 packed state. */
void sk_cont_suspend(long task, word_t s_lo, word_t s_hi, word_t cb, word_t cb_arg,
                     word_t wait_cb, word_t wait_arg)
{
        word_t x1, x2, x3, x4, x5, x6;
        bool flag;

        sk_atomic_enter(task + 0xb0);
        if (((uint)s_lo >> 9 & 1) == 0) {
                x5 = s_lo >> 0x20;
        } else {
                s_lo = *(ulong *)(task + 0x60);
                s_hi = *(ulong *)(task + 0x68);
                x5 = s_lo >> 0x20;
                if (((uint)s_lo >> 9 & 1) != 0) {
                        x4 = s_lo & 0xffffffff;
                        flag = true;
                        goto commit;
                }
        }
        x4 = (ulong)((uint)s_lo | 0x200);
        x3 = s_lo & 0xffffffff | x5 << 0x20;
        x5 = *(ulong *)(task + 0x60);
        x1 = *(ulong *)(task + 0x68);
        if ((x5 == s_hi) && (x1 == x3)) {
                *(ulong *)(task + 0x60) = s_hi;
                *(ulong *)(task + 0x68) = x4;
        }
        if (x5 == x3 && x1 == s_hi) {
                flag = false;
                x5 = 0;
                s_lo = x4;
        } else {
                do {
                        s_hi = x1;
                        x4 = (ulong)((uint)x5 | 0x200);
                        x3 = *(ulong *)(task + 0x60);
                        x1 = *(ulong *)(task + 0x68);
                        if ((x3 == s_hi) && (x1 == x5)) {
                                *(ulong *)(task + 0x60) = s_hi;
                                *(ulong *)(task + 0x68) = x4;
                        }
                        flag = x3 != x5;
                        x5 = x3;
                } while (flag || x1 != s_hi);
                flag = false;
                x5 = 0;
                s_lo = x4;
        }
commit:
        (*cb)(cb_arg, x4 | x5 << 0x20, s_hi);
        if (!flag) {
                goto exit_atomic;
        }
        wait_loop:
        if (wait_cb == 0) {
                goto exit_atomic;
        }
        {
                word_t wstate = CONCAT44((int)x5, (int)s_lo);
                do {
                        x4 = x5 << 0x20 | s_lo & 0xffffffff;
                        word_t prev_hi = s_hi;
                        (*wait_cb)(wait_arg, x4, s_hi, &wstate);
                        x5 = s_hi;
                        while (1) {
                                s_lo = *(ulong *)(task + 0x60);
                                s_hi = *(ulong *)(task + 0x68);
                                if ((s_lo == x5) && (s_hi == x4)) {
                                        *(ulong *)(task + 0x60) = prev_hi;
                                        *(ulong *)(task + 0x68) = wstate;
                                }
                                if (s_lo == x4 && s_hi == x5) {
                                        goto exit_atomic;
                                }
                                x5 = s_lo >> 0x20;
                                if (flag) {
                                        goto wait_loop;
                                }
                                s_lo = (ulong)((uint)s_lo & 0xfffffdff);
                                if (wait_cb != 0) {
                                        break;
                                }
                                x4 = s_lo & 0xffffffff | x5 << 0x20;
                                x5 = s_hi;
                                prev_hi = s_hi;
                        }
                } while (1);
        }
exit_atomic:
        sk_atomic_exit(task + 0xb0);
        return;
}

/* FUN_0040c09c @ 0x0040c09c   (est. sk_cont_record_commit)
 * Ghidra: uint FUN_0040c09c(undefined8 param_1, undefined8 param_2,
 *                           undefined8 param_3)
 * Commits a continuation record: loads the task's +0x60/+0x68 state and runs
 * the wake loop (FUN_0040bdd0), returning bit0.
 * Confidence: low */
uint sk_cont_record_commit(word_t rec, word_t cb, word_t cb_arg)
{
        word_t task;
        word_t state_lo;
        word_t state_hi;
        uint result;

        task = sk_swift_current_task();
        state_lo = *(word_t *)(task + 0x60);
        state_hi = *(word_t *)(task + 0x68);
        result = sk_cont_wake_loop(task, rec, &state_lo, cb, cb_arg);
        return result & 1;
}

/* FUN_0040c0f8 @ 0x0040c0f8   (est. sk_cont_resume_async)
 * Ghidra: void FUN_0040c0f8(long param_1, ulong param_2, ulong *param_3,
 *                           code *param_4, undefined8 param_5)
 * Resume path for an async continuation: repeatedly commit the record via the
 * CAS loop, invoking the callback (param_4) if non-null; when the state's bit 9
 * clears, run the suspend wait callbacks (FUN_0040cc9c/FUN_0040cccc).
 * Confidence: low */
void sk_cont_resume_async(long task, word_t state, word_t *rec, word_t cb,
                          word_t cb_arg)
{
        word_t s;
        word_t s2, s3, s4;
        word_t *slot;
        word_t **cbs;
        word_t *wslot;
        word_t newstate;
        word_t *fn;

        s = (ulong)(uint)*rec;
        newstate = state;
        fn = (word_t *)cb;
        cb_arg2 = cb_arg;
        if (((uint)*rec >> 9 & 1) == 0) {
                s2 = rec[1];
                do {
                        if (s2 != state) {
                                break;
                        }
                        cbs = (word_t **)(state + 8);
                        slot = (word_t *)(s & 0xffffffff);
                        s3 = *rec;
                        s4 = rec[1];
                        if (cb != 0) {
                                (*fn)(cb_arg, s3, s4, &slot);
                                s3 = *rec;
                                s4 = rec[1];
                        }
                        s = *(ulong *)(task + 0x60);
                        s2 = *(ulong *)(task + 0x68);
                        if ((s == s4) && (s2 == s3)) {
                                *(ulong *)(task + 0x60) = (ulong)cbs;
                                *(word_t **)(task + 0x68) = slot;
                        }
                        if (s == s3 && s2 == s4) {
                                return;
                        }
                        *rec = s;
                        rec[1] = s2;
                } while (((uint)s >> 9 & 1) == 0);
        }
        slot = &newstate;
        cbs = &fn;
        wslot = slot;
        sk_cont_suspend(task, *rec, rec[1], 0x40cc9c, &wslot, 0x40cccc, &slot);
        return;
}

/* FUN_0040c204 @ 0x0040c204   (est. sk_cont_dequeue)
 * Ghidra: void FUN_0040c204(long param_1, undefined8 param_2, undefined8 param_3,
 *                           undefined8 param_4, undefined8 param_5)
 * Dequeues a waiting continuation: sets up the {state, cb} pair and runs the
 * suspend path (FUN_0040bed0 with callbacks FUN_0040cd08/FUN_0040cdac).
 * Confidence: low */
void sk_cont_dequeue(long task, word_t cb, word_t cb_arg, word_t arg4, word_t arg5)
{
        byte *flag;
        word_t *slot;
        word_t *pair;
        byte *slot2;
        byte flag2;
        word_t st;
        word_t st2;
        word_t s;
        word_t s2;

        pair = &s;
        flag2 = 0;
        flag = &flag2;
        slot = &st;
        slot2 = flag;
        st = arg4;
        st2 = arg5;
        s = cb;
        s2 = cb_arg;
        sk_cont_suspend(task, *(word_t *)(task + 0x60), *(word_t *)(task + 0x68),
                        0x40cd08, &pair, 0x40cdac, &flag);
        return;
}

/* FUN_0040c280 @ 0x0040c280   (est. sk_cont_resume_record)
 * Ghidra: void FUN_0040c280(undefined8 param_1, undefined8 param_2,
 *                           undefined8 param_3)
 * Resumes a continuation record: loads the current task's +0x60/+0x68 state
 * and runs the async resume path (FUN_0040c0f8).
 * Confidence: low */
void sk_cont_resume_record(word_t rec, word_t cb, word_t cb_arg)
{
        word_t task;
        word_t state_lo;
        word_t state_hi;

        task = sk_swift_current_task();
        state_lo = *(word_t *)(task + 0x60);
        state_hi = *(word_t *)(task + 0x68);
        sk_cont_resume_async(task, rec, &state_lo, cb, cb_arg);
        return;
}

/* FUN_0040c2d8 @ 0x0040c2d8   (est. sk_cont_suspend_and_check)
 * Ghidra: undefined1 [16] FUN_0040c2d8(long param_1)
 * Suspends a continuation and returns whether a resume is pending: unless the
 * task has the bit5-of-+0x23 flag or bit 0xf of +0x60 set, returns zero; else
 * runs the suspend path (callback FUN_0040cde8) and returns the 16-byte
 * {value,status} pair.
 * Confidence: low */
word_t sk_cont_suspend_and_check(long task)
{
        word_t *slot;
        word_t value;
        word_t status;
        byte *local;

        if (((*(byte *)(task + 0x23) >> 5 & 1) == 0) &&
            (((uint)*(word_t *)(task + 0x60) >> 0xf & 1) == 0)) {
                return 0;
        }
        local = (byte *)&slot;
        value = 0;
        status = 0;
        slot = &value;
        sk_cont_suspend(task, *(word_t *)(task + 0x60), *(word_t *)(task + 0x68),
                        0x40cde8, &local, 0);
        return (status << 8) | value;   /* 16-byte {lo,hi} register pair */
}

/* FUN_0040c350 @ 0x0040c350   (est. sk_cont_suspend_simple)
 * Ghidra: undefined8 FUN_0040c350(undefined8 param_1)
 * Suspends a continuation with a simple zero callback and returns the stored
 * resume value.
 * Confidence: low */
word_t sk_cont_suspend_simple(word_t task)
{
        byte *slot;
        word_t *value;
        byte flag;
        word_t out;

        out = 0;
        flag = 0;
        slot = &flag;
        value = &out;
        sk_cont_dequeue(task, 0x40ce18, &slot, 0);
        return out;
}

/* FUN_0040c3a4 @ 0x0040c3a4   (est. sk_cont_enqueue_record)
 * Ghidra: void FUN_0040c3a4(long param_1, undefined8 param_2, undefined8 param_3,
 *                           int param_4)
 * Enqueues a continuation record (kind 5) carrying {a2, a3} and an enabled
 * flag; then commits it via the wake loop (FUN_0040bdd0 with callback
 * FUN_0040ce4c).
 * Confidence: low */
void sk_cont_enqueue_record(long task, word_t a2, word_t a3, int enable)
{
        word_t *rec;
        byte flag;
        word_t state_lo;
        word_t state_hi;

        rec = (word_t *)sk_cont_set_alloc(task, 0x28);
        *rec = 5;
        rec[1] = 0;
        *(byte *)(rec + 2) = 0;
        rec[3] = a2;
        rec[4] = a3;
        if (enable != 0) {
                *(byte *)(rec + 2) = 1;
        }
        state_lo = *(word_t *)(task + 0x60);
        state_hi = *(word_t *)(task + 0x68);
        sk_cont_wake_loop(task, rec, &state_lo, 0x40ce4c, &flag);
        return;
}

/* FUN_0040c434 @ 0x0040c434   (est. sk_cont_cancel)
 * Ghidra: void FUN_0040c434(undefined8 param_1)
 * Cancels a continuation: dequeues the waiting record, releases its stored
 * value, then frees it.
 * Confidence: low */
void sk_cont_cancel(word_t task)
{
        word_t *slot;
        word_t *recp;
        byte flag;
        word_t rec;

        rec = 0;
        flag = 0;
        slot = &flag;
        recp = &rec;
        sk_cont_dequeue(task, 0x40ce60, &slot, 0);
        long recv = rec;
        if ((*(byte *)(rec + 0x10) & 1) != 0) {
                sk_swift_release(*(word_t *)(rec + 0x18));
        }
        sk_cont_record_free(task, recv);
        return;
}

/* FUN_0040c4b0 @ 0x0040c4b0   (est. sk_cont_enqueue_str)
 * Ghidra: void FUN_0040c4b0(long param_1, undefined8 param_2)
 * Enqueues a string continuation record (kind 6): allocates a string copy of
 * param_2 (size via thunk_FUN_00115080, copy via thunk_FUN_0011537c), wraps it
 * in a record and commits it via the wake loop (callback FUN_0040ce94).
 * Confidence: low */
void sk_cont_enqueue_str(long task, word_t str)
{
        word_t *rec;
        long len;
        word_t buf;
        long copy;
        byte flag;
        word_t state_lo;
        word_t state_hi;

        rec = (word_t *)sk_cont_set_alloc(task, 0x18);
        len = thunk_FUN_00115080(str);
        buf = sk_cont_set_alloc(task, len + 1);
        copy = thunk_FUN_0011537c(buf, str, len);
        *(byte *)(copy + len) = 0;
        *rec = 6;
        rec[1] = 0;
        rec[2] = copy;
        state_lo = *(word_t *)(task + 0x60);
        state_hi = *(word_t *)(task + 0x68);
        sk_cont_wake_loop(task, rec, &state_lo, 0x40ce94, &flag);
        return;
}

/* FUN_0040c554 @ 0x0040c554   (est. sk_cont_exception)
 * Ghidra: void FUN_0040c554(long param_1)
 * Handles a continuation exception: if the bit6-of-+0x23 flag is set, dequeues
 * the waiting record and frees its two stored values.
 * Confidence: low */
void sk_cont_exception(long task)
{
        word_t *slot;
        word_t *recp;
        byte flag;
        word_t rec;

        if ((*(byte *)(task + 0x23) >> 6 & 1) != 0) {
                rec = 0;
                flag = 0;
                slot = &flag;
                recp = &rec;
                sk_cont_dequeue(task, 0x40ce9c, &slot, 0);
                long recv = rec;
                sk_cont_record_free(task, *(word_t *)(rec + 0x10));
                sk_cont_record_free(task, recv);
        }
        return;
}

/* FUN_0040c5d8 @ 0x0040c5d8   (est. sk_cont_exception_check)
 * Ghidra: undefined8 FUN_0040c5d8(long param_1)
 * If the bit6-of-+0x23 flag is set, runs the suspend path (callback
 * FUN_0040ced0) and returns the stored value; else returns 0.
 * Confidence: low */
word_t sk_cont_exception_check(long task)
{
        word_t *slot;
        word_t value;
        word_t **recp;

        if ((*(byte *)(task + 0x23) >> 6 & 1) == 0) {
                return 0;
        }
        slot = &value;
        value = 0;
        recp = &slot;
        sk_cont_suspend(task, *(word_t *)(task + 0x60), *(word_t *)(task + 0x68),
                        0x40ced0, &recp, 0);
        return value;
}

/* FUN_0040c640 @ 0x0040c640   (est. sk_cont_set_status)
 * Ghidra: void FUN_0040c640(long param_1, uint param_2, undefined8 param_3,
 *                           long param_4)
 * Sets the continuation status: updates the task's +0x60 status field with
 * param_2's low byte (default 0x19), setting bit 8 if the failure flag (bit 8
 * of param_2) or param_4's high bit (via FUN_0040cfb0) is set.
 * Confidence: low */
void sk_cont_set_status(long task, uint status, word_t param_3, long param_4)
{
        uint s;
        word_t hi;

        s = (uint)*(word_t *)(task + 0x60);
        hi = *(word_t *)(task + 0x68);
        if (((status >> 8 & 1) != 0) || (param_4 != 0 && (sk_status_high(param_4) != 0))) {
                s = s | 0x100;
        }
        uint newstatus = 0x19;
        if ((status & 0xff) != 0x21) {
                newstatus = status & 0xff;
        }
        *(ulong *)(task + 0x60) = (ulong)(s & 0xffffff00 | newstatus);
        *(word_t *)(task + 0x68) = hi;
        return;
}

/* FUN_0040c6a4 @ 0x0040c6a4   (est. sk_cont_wake_task)
 * Ghidra: void FUN_0040c6a4(undefined8 param_1, long param_2)
 * Wakes a task's continuation: resolves the task's run-queue (at +0xc0) and
 * runs the suspend path on it with the task as the callback context.
 * Confidence: low */
void sk_cont_wake_task(word_t arg, long task)
{
        word_t *slot;
        word_t *recp;
        word_t rec;
        word_t argv;
        word_t **recp2;

        long rq = *(long *)(task + 0xc0);
        slot = &arg;
        recp = &rec;
        recp2 = &slot;
        rec = task;
        arg = argv;
        sk_cont_suspend(rq, *(word_t *)(rq + 0x60), *(word_t *)(rq + 0x68),
                        0x40cf00, &recp2, 0);
        return;
}

/* FUN_0040c704 @ 0x0040c704   (est. sk_task_local_iterate)
 * Ghidra: void FUN_0040c704(undefined8 param_1)
 * Iterates a task's task-local store: initializes the task-local root, walks
 * the value tree from the root's +0x10 field (nodes at stride 200) and frees
 * each via sk_task_local_free_node (FUN_0040c748).
 * Confidence: low */
void sk_task_local_iterate(word_t task)
{
        long root;
        long node;

        sk_task_local_init();
        root = sk_task_local_root(task);
        for (node = *(long *)(root + 0x10); node != 0; node = *(long *)(node + 200)) {
                sk_task_local_free_node(node);
        }
        return;
}

/* FUN_0040c748 @ 0x0040c748   (est. sk_task_local_free_node)
 * Ghidra: void FUN_0040c748(long param_1)
 * Frees a single task-local value node: clears the "in-use" bit (bit 8) on
 * the task's +0x60 record via a CAS loop, then, if there is a backing value,
 * runs the destructor suspend path (callback FUN_0040cab4).
 * Confidence: low */
void sk_task_local_free_node(long task)
{
        uint s;
        word_t s3, s4;
        word_t s5, s6;
        byte flag;

        s = (uint)*(ulong *)(task + 0x60);
        s3 = *(ulong *)(task + 0x60);
        s4 = *(ulong *)(task + 0x68);
        while (1) {
                if ((s >> 8 & 1) != 0) {
                        return;
                }
                s5 = s3 & 0xffffffff | 0x100;
                s6 = *(ulong *)(task + 0x60);
                word_t h = *(ulong *)(task + 0x68);
                if ((s6 == s4) && (h == s3)) {
                        *(ulong *)(task + 0x60) = s4;
                        *(ulong *)(task + 0x68) = s5;
                }
                if (s6 == s3 && h == s4) {
                        break;
                }
                s = (uint)s6;
                s3 = s6;
                s4 = h;
        }
        if (s4 == 0) {
                return;
        }
        sk_cont_suspend(task, s5, s4, 0x40cab4, &flag, 0);
        return;
}

/* FUN_0040c7dc @ 0x0040c7dc   (est. sk_task_local_check_wake)
 * Ghidra: void FUN_0040c7dc(undefined8 param_1, long param_2)
 * If the task-local store has pending values (root's +0x10 non-null), runs the
 * suspend path on param_2's continuation (callback FUN_0040cf14).
 * Confidence: low */
void sk_task_local_check_wake(word_t arg, long task)
{
        word_t *slot;
        word_t value;
        word_t **recp;
        word_t root;

        value = arg;
        root = sk_task_local_root();
        if (*(long *)(root + 0x10) != 0) {
                slot = &value;
                recp = &slot;
                sk_cont_suspend(task, *(word_t *)(task + 0x60), *(word_t *)(task + 0x68),
                                0x40cf14, &recp, 0);
        }
        return;
}

/* FUN_0040c84c @ 0x0040c84c   (est. sk_record_commit)
 * Ghidra: void FUN_0040c84c(long param_1, undefined8 param_2, undefined8 param_3)
 * Commits a continuation record by kind: kind 4 forwards to the identity
 * helper (FUN_0001a1c8) with the record's +0x10/+0x18/+0x28 fields; kind 1
 * forwards to the status setter (FUN_0040c884) with param_3.  Other kinds are
 * no-ops.
 * Confidence: medium */
void sk_record_commit(long rec, word_t a2, word_t param_3)
{
        if (*(int *)(rec + 0x20) == 4) {
                sk_swift_identity(*(word_t *)(rec + 0x10), *(word_t *)(rec + 0x18),
                                  *(word_t *)(rec + 0x28));
                return;
        }
        if (*(int *)(rec + 0x20) == 1) {
                sk_cont_set_status(*(word_t *)(rec + 0x10), param_3);
                return;
        }
        return;
}

/* FUN_0040c884 @ 0x0040c884   (est. sk_cont_set_status)
 * Ghidra: ulong FUN_0040c884(long param_1, ulong param_2)
 * Continuation status update with a CAS loop: reads the current low status
 * byte (+0x60) and, while it is below param_2, computes the new packed status
 * (clearing/keeping bits per the 0x1800 mask), commits via CAS, and if a
 * backing value is present runs the suspend path (callback FUN_0040cb40).
 * Returns the committed status byte.
 * Confidence: low */
ulong sk_cont_set_status2(long task, ulong want)
{
        word_t s, s5, s4, s6, h;
        uint mask, val;
        uint status;
        word_t *slot;
        word_t *wslot;
        word_t st;

        status = (uint)*(ulong *)(task + 0x60) & 0xff;
        if (status < want) {
                s = *(ulong *)(task + 0x60);
                s5 = *(ulong *)(task + 0x68);
                do {
                        if ((s & 0x1800) == 0) {
                                if (((uint)s >> 0xd & 1) != 0) {
                                        return status;
                                }
                                mask = 0xffffc700;
                                val = (uint)want;
                        } else {
                                mask = 0xfffffb00;
                                val = (uint)want | 0x400;
                        }
                        s4 = (ulong)(mask & (uint)s | val);
                        s6 = *(ulong *)(task + 0x60);
                        h = *(ulong *)(task + 0x68);
                        if ((s6 == s5) && (h == s)) {
                                *(ulong *)(task + 0x60) = s5;
                                *(ulong *)(task + 0x68) = s4;
                        }
                        if (s6 == s && h == s5) {
                                if (s5 != 0) {
                                        slot = &st;
                                        wslot = &s4;
                                        st = want;
                                        sk_cont_suspend(task, s4, s5, 0x40cb40, &slot, 0);
                                }
                                return (ulong)(val & 0xff);
                        }
                        status = (uint)s6 & 0xff;
                        s = s6;
                        s5 = h;
                } while (status < want);
        }
        return status;
}

/* FUN_0040c970 @ 0x0040c970   (est. sk_cont_wake_task2)
 * Ghidra: void FUN_0040c970(undefined8 param_1, long param_2)
 * Wakes a task's continuation on its run-queue (callback FUN_0040ca3c).
 * Confidence: low */
void sk_cont_wake_task2(word_t arg, long task)
{
        word_t *slot;
        word_t *recp;
        word_t rec;
        word_t argv;
        word_t **recp2;

        long rq = *(long *)(task + 0xc0);
        slot = &arg;
        recp = &rec;
        recp2 = &slot;
        rec = task;
        arg = argv;
        sk_cont_suspend(rq, *(word_t *)(rq + 0x60), *(word_t *)(rq + 0x68),
                        0x40ca3c, &recp2, 0);
        return;
}

/* FUN_0040c9d0 @ 0x0040c9d0   (est. sk_task_has_waiters)
 * Ghidra: byte FUN_0040c9d0(void)
 * Returns whether the current task has pending task-local values: runs the
 * suspend path (callback FUN_0040ca84) and returns bit0 of the outcome.
 * Confidence: low */
byte sk_task_has_waiters(void)
{
        word_t task;
        byte *slot;
        byte flag;
        word_t **recp;

        task = sk_swift_current_task();
        if (task == 0) {
                flag = 0;
        } else {
                flag = 0;
                slot = &flag;
                recp = &slot;
                sk_cont_suspend(task, *(word_t *)(task + 0x60), *(word_t *)(task + 0x68),
                                0x40ca84, &recp, 0);
        }
        return flag & 1;
}

/* FUN_0040ca3c @ 0x0040ca3c   (est. sk_cont_wake_cb)
 * Ghidra: void FUN_0040ca3c(undefined8 *param_1, undefined8 param_2,
 *                           undefined8 param_3)
 * Wake callback: resolves the waiting task record, runs the wake function
 * (FUN_0040cf34) on it and sets its continuation status.
 * Confidence: low */
void sk_cont_wake_cb(word_t *rec, word_t status, word_t param_3)
{
        rec = (word_t *)*rec;
        sk_task_local_push(*(word_t *)*rec, *(word_t *)rec[1]);
        sk_cont_set_status(*(word_t *)rec[1], status, param_3, *(word_t *)*rec);
        return;
}

/* FUN_0040cc28 @ 0x0040cc28   (est. sk_cont_state_cb)
 * Ghidra: void FUN_0040cc28(undefined8 *param_1, undefined8 param_2,
 *                           undefined8 param_3, ulong *param_4)
 * Continuation state callback: records the new state word into the record,
 * invokes the state-machine closure at param_1[2] with the packed state, and
 * commits the result back into param_4 on success.
 * Confidence: low */
void sk_cont_state_cb(word_t *rec, word_t a2, word_t a3, word_t *state)
{
        word_t st;
        word_t st_hi;
        word_t *target;
        int rc;

        target = (word_t *)*rec;
        *(ulong *)(*target + 8) = state[1];
        st = (ulong)(uint)*state;
        st_hi = *target;
        rc = (**(int (**)(void))rec[2])(((word_t *)rec[2])[1], *state, state[1], &st);
        *(char *)rec[1] = (char)rc;
        if (rc != 0) {
                state[1] = st_hi;
                *state = st;
        }
        return;
}

/* FUN_0040cf24 @ 0x0040cf24   (est. sk_ptr_offset_8)
 * Ghidra: long FUN_0040cf24(long param_1)
 * Returns param_1 + 8 (pointer-advance helper).
 * Confidence: medium */
long sk_ptr_offset_8(long p) { return p + 8; }

/* FUN_0040cf2c @ 0x0040cf2c   (est. sk_ptr_offset_m8)
 * Ghidra: long FUN_0040cf2c(long param_1)
 * Returns param_1 - 8 (pointer-rewind helper).
 * Confidence: medium */
long sk_ptr_offset_m8(long p) { return p + -8; }

/* FUN_0040cf34 @ 0x0040cf34   (est. sk_task_local_push)
 * Ghidra: void FUN_0040cf34(long param_1, undefined8 param_2)
 * Pushes a task-local value into a task's tree: stores the new value at
 * +0x20 and links it after the current tail (+0x18) or as the new head.
 * Confidence: medium */
void sk_task_local_push(long task, word_t value)
{
        long tail;

        tail = *(long *)(task + 0x20);
        *(word_t *)(task + 0x20) = value;
        if (*(long *)(task + 0x18) != 0) {
                *(word_t *)(tail + 200) = value;
                return;
        }
        *(word_t *)(task + 0x18) = value;
        return;
}

/* FUN_0040cf54 @ 0x0040cf54   (est. sk_task_local_pop)
 * Ghidra: void FUN_0040cf54(long param_1, long param_2)
 * Removes a task-local value node from a task's doubly-linked list (head at
 * +0x18, tail at +0x20, prev/next via +200).
 * Confidence: medium */
void sk_task_local_pop(long task, long node)
{
        long cur;
        long next;

        cur = *(long *)(task + 0x18);
        if (node == *(long *)(task + 0x18)) {
                next = *(long *)(node + 200);
                *(long *)(task + 0x18) = next;
                if (next == 0) {
                        *(word_t *)(task + 0x20) = 0;
                        return;
                }
        } else {
                do {
                        long prev = cur;
                        if (prev == 0) {
                                return;
                        }
                        cur = *(long *)(prev + 200);
                } while (*(long *)(prev + 200) != node);
                *(word_t *)(prev + 200) = *(word_t *)(node + 200);
                if (node == *(long *)(task + 0x20)) {
                        *(long *)(task + 0x20) = prev;
                        return;
                }
        }
        return;
}

/* FUN_0040cfb0 @ 0x0040cfb0   (est. sk_status_high)
 * Ghidra: ulong FUN_0040cfb0(long param_1)
 * Returns the high bit (bit 63) of the value at param_1+0x28.
 * Confidence: medium */
ulong sk_status_high(long p) { return *(ulong *)(p + 0x28) >> 0x3f; }

/* FUN_0040cfbc @ 0x0040cfbc   (est. sk_status_high_set)
 * Ghidra: ulong FUN_0040cfbc(long param_1)
 * Sets the high bit of the value at param_1+0x28 and returns its previous
 * high bit (test-and-set).
 * Confidence: medium */
ulong sk_status_high_set(long p)
{
        ulong v;

        v = *(ulong *)(p + 0x28);
        *(ulong *)(p + 0x28) = v | 0x8000000000000000;
        return v >> 0x3f;
}

/* FUN_0040cfd0 @ 0x0040cfd0   (est. sk_vtable_dispatch_20)
 * Ghidra: void FUN_0040cfd0(long *param_1)
 * Indirect vtable dispatch through slot +0x20 of the object's class metadata.
 * Confidence: low */
void sk_vtable_dispatch_20(word_t *obj)
{
        (**(void (**)(void))(*obj + 0x20))();
        return;
}

/* FUN_0040cfec @ 0x0040cfec   (est. sk_task_group_init)
 * Ghidra: void FUN_0040cfec(undefined8 *param_1, undefined8 param_2)
 * Initializes a task-group record: zeroes all 14 words, sets the metadata
 * (0x67f4f0) and kind=2, records the parent group (param_2) at +0xd, then
 * registers the group in the continuation set via FUN_0040c09c (callback
 * FUN_0040ea3c).
 * Confidence: low */
void sk_task_group_init(word_t *group, word_t parent)
{
        word_t *slot;
        word_t *rec;

        group[0xc] = 0;
        group[0xd] = parent;
        group[9] = 0;
        group[8] = 0;
        group[0xb] = 0;
        group[10] = 0;
        group[5] = 0;
        group[4] = 0;
        group[7] = 0;
        group[6] = 0;
        group[3] = 0;
        group[2] = 0;
        *group = 0x67f4f0;
        group[1] = 2;
        slot = &rec;
        rec = group;
        sk_cont_record_commit(group + 1, 0x40ea3c, &slot);
        return;
}

/* FUN_0040d068 @ 0x0040d068   (est. sk_task_group_init_variant)
 * Ghidra: void FUN_0040d068(undefined8 param_1, undefined8 param_2,
 *                           undefined8 param_3)
 * Initializes a task-group variant record via sk_task_group_init_full
 * (FUN_0040dd90) with reordered arguments.
 * Confidence: low */
void sk_task_group_init_variant(word_t a, word_t b, word_t c)
{
        sk_task_group_init_full(c, a, b);
        return;
}

/* FUN_0040d07c @ 0x0040d07c   (est. sk_vtable_dispatch_10)
 * Ghidra: void FUN_0040d07c(long *param_1)
 * Indirect vtable dispatch through slot +0x10 of the object's class metadata.
 * Confidence: low */
void sk_vtable_dispatch_10(word_t *obj)
{
        (**(void (**)(void))(*obj + 0x10))();
        return;
}
