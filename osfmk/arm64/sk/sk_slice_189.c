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
#include <stdarg.h>

typedef uint64_t word_t;
typedef unsigned int uint;
typedef unsigned long ulong;
typedef unsigned char byte;
typedef void (*code)(void);
typedef word_t (*vcode)(word_t, ...);

#define SK189_FATAL(addr) __builtin_trap()   /* SoftwareBreakpoint(1,<addr>) path */

/* LOAcquire / LORelease / GENTER / GEXIT opaque primitives. */
#define LOAcquire()      do { } while (0)
#define LORelease()      do { } while (0)
#define GENTER()         do { } while (0)   /* GENTER opcode 0x00201420 */
#define GEXIT()          do { } while (0)   /* GEXIT opcode 0x00201400 */
#define LZCOUNT(x)       __builtin_clzll(x)
#define POPCOUNT(x)      __builtin_popcountll(x)
static inline word_t bit_reverse64(word_t x)
{
        x = ((x & 0xaaaaaaaaaaaaaaaa) >> 1) | ((x & 0x5555555555555555) << 1);
        x = ((x & 0xcccccccccccccccc) >> 2) | ((x & 0x3333333333333333) << 2);
        x = ((x & 0xf0f0f0f0f0f0f0f0) >> 4) | ((x & 0x0f0f0f0f0f0f0f0f) << 4);
        x = ((x & 0xff00ff00ff00ff00) >> 8) | ((x & 0x00ff00ff00ff00ff) << 8);
        x = ((x & 0xffff0000ffff0000) >> 16) | ((x & 0x0000ffff0000ffff) << 16);
        return (x >> 32) | (x << 32);
}
#define CONCAT44(h, l) (((word_t)(h) << 32) | ((word_t)(l) & 0xffffffff))
static inline int byte_popcount8(unsigned char b)
{
        static const char t[16] = {0,1,1,2,1,2,2,3,1,2,2,3,2,3,3,4};
        return t[b & 0xf] + t[b >> 4];
}

/* ---- Shared kernel / Swift-runtime externs (ground truth FUN_ addresses). ----
 * Swift ABI arity is deliberately flexible (variadic): Ghidra renders the
 * unaff-register conventions with varying argument counts; the bodies call
 * these with the counts shown in each decompile. */

extern word_t sk_swift_current_task();                 /* FUN_0040880c */
extern word_t sk_swift_alloc();                 /* FUN_0036a804 */
extern word_t sk_swift_array_buf_alloc();       /* FUN_0036a940 */
extern word_t sk_swift_closure_box();           /* FUN_0036bfe4 */
extern void   sk_swift_deinit_small();                 /* FUN_0036a244 */
extern void   sk_swift_destroy_small();                /* FUN_0036a2ac */
extern word_t sk_swift_release();               /* FUN_0036b118 */
extern word_t sk_swift_retain();                /* FUN_0036b270 */
extern void   sk_atomic_enter();                     /* FUN_0037a48c */
extern void   sk_atomic_exit();                      /* FUN_0037a978 */
extern void   sk_hashtable_resize();            /* FUN_0037d700 */
extern int    sk_c11_mtx_init();             /* FUN_00118148 */
extern int    sk_c11_mtx_lock();                     /* FUN_00118164 */
extern int    sk_c11_mtx_unlock();                   /* FUN_00118194 */
extern int    sk_c11_mtx_trylock();                  /* FUN_00118114 */
extern int    sk_c11_cnd_init();                     /* FUN_001180fc */
extern int    sk_c11_cnd_wait();             /* FUN_0011812c */
extern void   sk_swift_fatal(); /* FUN_003a2578 */
extern void   sk_precond_fatal(); /* FUN_004ba640 */
extern word_t sk_swift_array_dealloc();         /* FUN_00117e14 */
extern void   sk_free();                        /* thunk_FUN_00012568 */
extern word_t sk_swift_hash8(word_t *);                    /* FUN_00112098 */
extern word_t sk_calloc();                      /* FUN_00111890 */
extern word_t sk_memmove();                     /* FUN_00117d14 */
extern void   sk_once_gate();                   /* FUN_003d3dd8 */
extern void   sk_lock_exit();                          /* FUN_0035b228 */
extern int    sk_error_str();   /* FUN_00116bb4 */
extern word_t sk_error_fmt();                   /* FUN_001131f4 */
extern word_t sk_error_fmt2();                  /* FUN_00113c30 */
extern word_t sk_error_fmt3();                  /* FUN_0011394c */
extern void   sk_str_append2();                 /* FUN_00112db4 */
extern void   sk_str_render();                  /* FUN_00112e8c */
extern word_t sk_heap_alloc();                  /* FUN_000101a0 */
extern int    sk_runtime_once();                /* FUN_003697c4 */
extern int    sk_runtime_once2();                      /* FUN_00369818 */
extern word_t sk_ctx_save();                    /* FUN_00408834 */
extern void   sk_ctx_save2();                        /* FUN_00408864 */
extern void   sk_ctx_restore();                        /* FUN_004087cc */
extern void   sk_ctx_restore2();                     /* FUN_00408784 */
extern void   sk_task_resume();      /* FUN_00408ae4 */
extern word_t sk_executor_enq();                /* FUN_003a25b8 */
extern void   sk_executor_enq2();       /* FUN_003d5338 */
extern word_t sk_executor_enq3();       /* FUN_003d5370 */
extern word_t sk_executor_deq();        /* FUN_003d5308 */
extern void   sk_ctx_push();                           /* FUN_001a8564 */
extern void   sk_ctx_pop();                     /* FUN_003509ec */
extern void   sk_ctx_pop2();                           /* FUN_0035199c */
extern void   sk_ctx_swap();                    /* FUN_003523fc */
extern void   sk_actor_enter();                 /* FUN_00350af4 */
extern void   sk_actor_leave();                        /* FUN_00350518 */
extern void   sk_sched_enter();                 /* FUN_00229a3c */
extern void   sk_sched_enter2();                       /* FUN_0006b6f4 */
extern word_t sk_task_switch1();                       /* FUN_0041001c */
extern void   sk_task_switch2();                       /* FUN_00410414 */
extern word_t sk_task_switch3();                       /* FUN_004110ec */
extern word_t sk_task_switch4();                       /* FUN_00411624 */
extern void   sk_task_switch5();                       /* FUN_004080b0 */
extern void   sk_task_switch6();                       /* FUN_00458200 */
extern void   sk_task_switch7();                       /* FUN_00458780 */
extern void   sk_task_switch8();                       /* FUN_00100efc */
extern void   sk_swift_identity();              /* FUN_0001a1c8 */
extern word_t sk_swift_hotpath();               /* FUN_00361528 */

/* Register-held self/context pointers (Ghidra sk_reg_x20/x21/x22/w19/w4):
 * the arm64e callee-saved registers carrying the Swift self / accessor-context
 * value. Represented as scalar words; dereferenced with explicit casts. */
extern word_t sk_reg_x20;
extern word_t sk_reg_x21;
extern word_t sk_reg_x22;
extern word_t sk_reg_w19;
extern word_t sk_reg_w4;
extern word_t sk_reg_x9;
extern word_t sk_reg_x10;
extern word_t sk_reg_x11;

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

/* ---- Swift pseudo-registers / Ghidra unaff + DAT_ globals referenced by the
 * region (decompiler artifacts, kept as scalar words; ground-truth addresses
 * in comments). ---- */
extern word_t extraout_x1;
extern word_t extraout_x8;
extern word_t extraout_x9;
extern word_t extraout_x10;
extern word_t extraout_x11;
extern word_t extraout_w9;
extern word_t low_flag;
extern word_t low_flag2;
extern word_t cb_arg2;
extern word_t canary_ok;
extern word_t DAT_006c0c30;
extern word_t DAT_006c0c40;
extern word_t DAT_006c0c78;
extern word_t DAT_006adfb0;
extern word_t DAT_005a17f0;
extern word_t lRam00000000005a17f8;
extern word_t (*DAT_0068a6d8)();
extern word_t DAT_006c0c80;
extern word_t FUN_004ba704(word_t *);
extern word_t FUN_004ba780(word_t *);
extern void sk_task_local_init(void);
extern void thunk_FUN_00369b04(word_t, ...);
extern long thunk_FUN_00115080(word_t, ...);
extern long thunk_FUN_0011537c(word_t, ...);
extern void sk_assert_hook();
extern void sk_assert_abort();
extern void sk_cont_deliver();
extern void sk_cont_dispatch();
extern void sk_cont_register_excl();
extern void sk_cont_resume_hook();
extern void sk_cnd_destroy();
extern void sk_mtx_destroy();

/* cnd/mtx backing storage referenced by sk_continuation_destroy. */
static word_t cnd_cond[8];
static word_t cnd_mtx[8];
static word_t stk;

/* ---- Internal forward declarations (region-internal helpers). ---- */
void sk_actor_box_write(word_t value, byte tag);
word_t sk_actor_executor_dequeue(word_t job, word_t executor);
void sk_actor_executor_enqueue(word_t job, word_t executor);
word_t sk_actor_executor_enqueue_check(word_t job, word_t executor);
void sk_actor_noop(void);
word_t sk_actor_value_retain(word_t value);
void sk_actor_value_retain_param3(word_t a, word_t b, word_t value);
void sk_actor_value_set(word_t value);
void sk_claim_null_waiting_fatal(void);
void sk_cnd_signal(void);
void sk_cnd_wait(long cnd);
long sk_cont_block(word_t param_1);
long sk_cont_block_alloc(word_t *block, long size);
void sk_cont_buf_append(word_t *buf, word_t *value);
void sk_cont_cancel(word_t task);
void sk_cont_dequeue(long task, word_t cb, word_t cb_arg, word_t arg4, word_t arg5);
void sk_cont_enqueue_record(long task, word_t a2, word_t a3, int enable);
void sk_cont_enqueue_str(long task, word_t str);
void sk_cont_exception(long task);
word_t sk_cont_exception_check(long task);
long sk_cont_free_nodes(long block, word_t head);
void sk_cont_init_dispatch(word_t param_1);
void sk_cont_record_alloc(word_t *block, word_t *rec);
uint sk_cont_record_commit(word_t rec, word_t cb, word_t cb_arg, ...);
void sk_cont_record_free(word_t block, word_t rec);
void sk_cont_record_init(word_t param_1);
bool sk_cont_record_pop(long queue, word_t out);
void sk_cont_result_dispatch(long consumer, word_t rec);
void sk_cont_resume_async(long task, word_t state, word_t *rec, word_t cb, word_t cb_arg);
void sk_cont_resume_for_task(word_t task);
void sk_cont_resume_record(word_t rec, word_t cb, word_t cb_arg, ...);
void sk_cont_save_b(void);
void sk_cont_save_c(void);
void sk_cont_save_d(void);
void sk_cont_save_e(void);
word_t sk_cont_set_alloc(word_t block, word_t size);
long sk_cont_set_find(word_t *set, word_t *key);
word_t sk_cont_set_link(word_t *rec, word_t a2, word_t a3, word_t *flags);
word_t sk_cont_set_link_b(word_t *rec, word_t a2, word_t a3, word_t *flags);
word_t sk_cont_set_remove(word_t set, word_t *node);
void sk_cont_set_status(long task, uint status, word_t param_3, long param_4, ...);
ulong sk_cont_set_status2(long task, ulong want);
void sk_cont_set_unlink(word_t *out, word_t *set, word_t *node);
void sk_cont_state_cb(word_t *rec, word_t a2, word_t a3, word_t *state);
void sk_cont_state_dispatch(long queue, long task);
void sk_cont_suspend(long task, word_t s_lo, word_t s_hi, word_t cb, word_t cb_arg, word_t wait_cb, ...);
word_t sk_cont_suspend_and_check(long task);
word_t sk_cont_suspend_simple(word_t task);
void sk_cont_teardown_block(long task, long ctx, word_t param_3);
void sk_cont_wake_cb(word_t *rec, word_t status, word_t param_3);
uint sk_cont_wake_loop(long task, word_t state, word_t rec, word_t cb, word_t cb_arg, ...);
void sk_cont_wake_task(word_t arg, long task);
void sk_cont_wake_task2(word_t arg, long task);
void sk_continuation_create(word_t kind_hi, word_t param_2);
void sk_continuation_destroy(long task);
void sk_mtx_lock(long cnd);
word_t sk_mtx_recursive_init(word_t mtx);
void sk_mtx_unlock(long cnd);
long sk_popcount_range(word_t *bits, uint start, word_t span);
void sk_record_commit(long rec, word_t a2, word_t param_3);
bool sk_registry_pop(word_t registry, word_t task);
void sk_runq_append(word_t *queue, word_t task);
ulong sk_status_high_set(long p);
long sk_task_continuation_init(long task, word_t flags);
void sk_task_exclusive_init(void);
void sk_task_executor_switch(void);
void sk_task_group_add_child(long child, long *group, long body, long *result);
void sk_task_group_child_end(long *group, long child, long body);
void sk_task_group_dump(word_t *out, word_t *ids, byte on, byte off);
uint sk_task_group_end(long *group, word_t accepting);
void sk_task_group_error(word_t *out);
void sk_task_group_init(word_t *group, word_t parent);
void sk_task_group_init_full(word_t parent, uint flags, word_t *group);
void sk_task_group_init_variant(word_t a, word_t b, word_t c);
void sk_task_group_store(word_t *queue, word_t record);
void sk_task_group_store2(word_t group, word_t result);
void sk_task_group_store3(word_t group, word_t result);
void sk_task_group_store4(word_t group, word_t result);
void sk_task_group_wait(long child, long *group, word_t want_result, long body, long *result);
byte sk_task_has_waiters(void);
void sk_task_local_check_wake(word_t arg, long task);
void sk_task_local_cleanup(long store);
void sk_task_local_clear(void);
void sk_task_local_collect(word_t *out, word_t task, long store);
void sk_task_local_deinit_a(void);
void sk_task_local_deinit_b(void);
void sk_task_local_deinit_c(void);
void sk_task_local_deinit_d(void);
void sk_task_local_destructure(long node, long task);
void sk_task_local_error(word_t *out);
void sk_task_local_free_node(long task);
long sk_task_local_get_value(word_t key);
void sk_task_local_invoke(word_t *obj);
void sk_task_local_invoke2(word_t *obj);
void sk_task_local_iterate(word_t task);
void sk_task_local_pop(long task, long node);
void sk_task_local_push(long task, word_t value);
void sk_task_local_release_all(word_t *store, word_t task);
void sk_task_local_release_all2(word_t task);
word_t sk_task_local_set_alloc(word_t block, word_t flags, int kind);
void sk_task_local_set_value(word_t key, word_t value, long meta);
bool sk_task_local_value_release(uint *value, long block, ...);
word_t sk_task_record_alloc(word_t size, ...);
void sk_task_resume_trampoline(void);
uint sk_task_suspend_switch(word_t a, long b, word_t c, uint d, word_t e, long f, word_t g, uint h);
void sk_task_switch_enter(void);
void sk_tl_buf_destroy(word_t buf, word_t *node);
word_t sk_tl_buf_insert(word_t tree, word_t *key, word_t *node);
void sk_tl_buf_link(word_t *tree, word_t parent, word_t *where, word_t *node);
void sk_tl_rb_rebalance(word_t *tree, word_t *node);
word_t sk_tl_value_alloc(word_t task, word_t key, word_t meta, int flag);
void sk_vtable_dispatch_10(word_t *obj);
void sk_vtable_dispatch_20(word_t *obj);

/* ---- Tiny region helpers used before their definitions. ---- */
word_t sk_task_local_store(word_t store);
word_t sk_cont_buf_destroy(word_t buf, ...);

long sk_ptr_offset_8(long p);
ulong sk_status_high(long p);
long sk_task_local_root(word_t task);
word_t *sk_registry_add(word_t *set, word_t *key, word_t *arg3);
long sk_cont_free_nodes(long block, word_t head);
word_t *sk_cont_block_dealloc(word_t *block);

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
                sk_cont_wake_loop(owner, (word_t)node, (word_t)&slot, 0x40af00, (word_t)&arr);
                sk_swift_destroy_small(owner + 0x50);
                sk_ctx_restore(0);
                sk_ctx_save(0);
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
                sk_registry_add((word_t *)0x6c0c48, &wake_slot, &wake_slot);
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
                once = sk_c11_cnd_init((word_t)cnd_cond);
                if (once != 0) {
                        sk_swift_fatal(0x5dc931); /* "__cnd_init..." */
                }
                once = sk_c11_mtx_init((word_t)cnd_mtx, 0);
                if (once != 0) {
                        sk_swift_fatal(0x5d3f10); /* "__mtx_init..." */
                }
                *(byte **)(task + 0x40) = (byte *)cnd_cond;
                if (*(long *)(task + 0x18) == state) {
                        *(long *)(task + 0x18) = 1;
                        sk_mtx_lock((word_t)cnd_cond);
                        do {
                                sk_cnd_wait((word_t)cnd_cond);
                        } while (*(long *)(task + 0x18) != 2);
                        sk_mtx_unlock((word_t)cnd_cond);
                }
                sk_cnd_destroy((word_t)cnd_cond);
                sk_mtx_destroy((word_t)cnd_mtx);
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
                sk_cont_free_nodes((long)block, (word_t)(p + 1));
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
long sk_cont_free_nodes(long block, word_t head)
{
        long node;
        long next;
        long count;
        word_t *hp = (word_t *)head;

        node = *hp;
        *hp = 0;
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
        sk_ctx_save(0);
        sk_cont_teardown_block(0, 0, 0);
        return;
}

/* FUN_0040b084 @ 0x0040b084   (est. sk_cont_save_c)
 * Ghidra: void FUN_0040b084(void)
 * Same shape as 0040b03c (alternate save+teardown hook).
 * Confidence: low */
void sk_cont_save_c(void)
{
        sk_ctx_save(0);
        sk_cont_teardown_block(0, 0, 0);
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
        tok = sk_ctx_save(0);
        sk_cont_teardown_block(0, 0, 0);
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

        tok = sk_ctx_save(0);
        sk_cont_teardown_block(0, 0, 0);
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
                        bool eq_a;
                        bool eq_b;
                        a = *(long *)(task + 0x60);
                        b = *(long *)(task + 0x68);
                        if ((a == cb) && (b == ca)) {
                                *(long *)(task + 0x60) = cb;
                                *(ulong *)(task + 0x68) = (ulong)((uint)ca & 0xffffc3ff | 0x2000);
                        }
                        eq_a = a != ca;
                        eq_b = b != cb;
                        ca = a;
                        cb = b;
                        if (!eq_a && !eq_b) {
                                break;
                        }
                } while (1);
        }
        sk_runq_append((word_t *)(queue + 0x38), task);
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
                rec = sk_registry_pop(0x6c0c48, (word_t)&task);
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

        node = sk_cont_set_find((word_t *)task, (word_t *)task);
        if (node != 0) {
                sk_cont_set_remove(registry, (word_t *)node);
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
                node = (long)*(long **)(*set + idx * 8);
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
                sk_cont_set_unlink((word_t *)free_list, (word_t *)0, (word_t *)0);
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
word_t sk_task_record_alloc(word_t size, ...)
{
        word_t block;

        sk_swift_current_task();
        block = sk_cont_block(0);
        return (word_t)sk_cont_block_alloc((word_t *)block, size);
}

/* FUN_0040bb48 @ 0x0040bb48   (est. sk_cont_block)
 * Ghidra: long FUN_0040bb48(long param_1)
 * Resolves the continuation block allocator: if param_1 is non-null returns
 * param_1+0x70, else the process-wide task-local root (0x6c0c88) once its
 * flag (0x6c0c80) is set, else the freshly-initialized block.
 * Confidence: low */
long sk_cont_block(word_t param_1)
{
        word_t block;

        if (param_1 != 0) {
                return param_1 + 0x70;
        }
        if ((DAT_006c0c80 & 1) != 0) {
                return 0x6c0c88;
        }
        FUN_004ba704((word_t *)&block);
        return block;
}

/* FUN_0040bcf8 @ 0x0040bcf8   (est. sk_cont_set_alloc)
 * Ghidra: void FUN_0040bcf8(undefined8 param_1, undefined8 param_2)
 * Allocates a record of size param_2 from the continuation block and appends
 * it (via FUN_0040bb98).
 * Confidence: low */
word_t sk_cont_set_alloc(word_t block, word_t size)
{
        word_t b;

        b = sk_cont_block(0);
        return (word_t)sk_cont_block_alloc((word_t *)b, size);
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
        block = sk_cont_block(0);
        sk_cont_record_alloc((word_t *)block, (word_t *)param_1);
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
                word_t hdr = next;
                *(int *)(hdr + 0x14) = ((int)next - (int)hdr) - 0x20;
                *block = hdr;
                return;
        }
        FUN_004ba780((word_t *)rec);
        return;
}

/* FUN_0040bda0 @ 0x0040bda0   (est. sk_cont_record_free)
 * Ghidra: void FUN_0040bda0(undefined8 param_1, undefined8 param_2)
 * Frees a record from the continuation block (block-relative free).
 * Confidence: low */
void sk_cont_record_free(word_t block, word_t rec)
{
        word_t b;

        b = sk_cont_block(0);
        sk_cont_record_alloc((word_t *)b, (word_t *)rec);
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
uint sk_cont_wake_loop(long task, word_t state, word_t rec, word_t cb,
                       word_t cb_arg, ...)
{
        word_t s_lo, s_hi;
        word_t s_old;
        word_t w;
        uint result;
        word_t *slot;
        byte flag;
        word_t *cb_slot;
        word_t newstate;

        word_t *recp2 = (word_t *)rec;
        s_lo = (ulong)(uint)*recp2;
        newstate = state;
        cb_slot = (word_t *)cb;
        cb_arg2 = cb_arg;
        if (((uint)*recp2 >> 9 & 1) == 0) {
                s_hi = recp2[1];
                do {
                        *(ulong *)(newstate + 8) = s_hi;
                        slot = (word_t *)(s_lo & 0xffffffff);
                        result = ((vcode)cb_slot)(cb_arg2, *recp2, recp2[1], (word_t)&slot);
                        if (result == 0) {
                                goto wake_done;
                        }
                        s_old = *recp2;
                        w = recp2[1];
                        s_lo = *(ulong *)(task + 0x60);
                        s_hi = *(ulong *)(task + 0x68);
                        if ((s_lo == w) && (s_hi == s_old)) {
                                *(ulong *)(task + 0x60) = (ulong)(byte *)newstate;
                                *(word_t **)(task + 0x68) = slot;
                        }
                        if (s_lo == s_old && s_hi == w) {
                                goto wake_done;
                        }
                        *recp2 = s_lo;
                        recp2[1] = s_hi;
                } while (((uint)s_lo >> 9 & 1) == 0);
        } else {
                s_lo = *recp2;
                s_hi = recp2[1];
        }
        flag = 0;
        slot = &newstate;
        cb_slot = &cb;
        {
                word_t *cbp = &cb;
                word_t *slp = &slot;
                byte f = 0;
                word_t stk2;
                word_t *wslot = &newstate;
                sk_cont_suspend(task, s_lo, s_hi, 0x40cc24, (word_t)&stk2, 0x40cc28, (word_t)&wslot);
        }
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
                     word_t wait_cb, ...)
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
        ((vcode)cb)(cb_arg, x4 | x5 << 0x20, s_hi);
        if (!flag) {
                goto exit_atomic;
        }
        wait_loop:
        if (wait_cb == 0) {
                goto exit_atomic;
        }
        {
                word_t wait_arg_v = 0;
                word_t wstate = CONCAT44((int)x5, (int)s_lo);
                do {
                        x4 = x5 << 0x20 | s_lo & 0xffffffff;
                        word_t prev_hi = s_hi;
                        ((vcode)wait_cb)(wait_arg_v, x4, s_hi, (word_t)&wstate);
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
uint sk_cont_record_commit(word_t rec, word_t cb, word_t cb_arg, ...)
{
        word_t task;
        word_t state_lo;
        word_t state_hi;
        uint result;

        task = sk_swift_current_task();
        state_lo = *(word_t *)(task + 0x60);
        state_hi = *(word_t *)(task + 0x68);
        result = sk_cont_wake_loop(task, rec, (word_t)&state_lo, cb, cb_arg);
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
                                ((vcode)fn)(cb_arg, s3, s4, (word_t)&slot);
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
        sk_cont_suspend(task, *rec, rec[1], 0x40cc9c, (word_t)&wslot, 0x40cccc, (word_t)&slot);
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
        sk_cont_suspend(task, *(word_t *)(task + 0x60), *(word_t *)(task + 0x68), 0x40cd08, (word_t)&pair, 0x40cdac, (word_t)&flag);
        return;
}

/* FUN_0040c280 @ 0x0040c280   (est. sk_cont_resume_record)
 * Ghidra: void FUN_0040c280(undefined8 param_1, undefined8 param_2,
 *                           undefined8 param_3)
 * Resumes a continuation record: loads the current task's +0x60/+0x68 state
 * and runs the async resume path (FUN_0040c0f8).
 * Confidence: low */
void sk_cont_resume_record(word_t rec, word_t cb, word_t cb_arg, ...)
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
        sk_cont_suspend(task, *(word_t *)(task + 0x60), *(word_t *)(task + 0x68), 0x40cde8, (word_t)&local, 0);
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
        sk_cont_dequeue(task, 0x40ce18, (word_t)&slot, 0, 0);
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
        sk_cont_wake_loop(task, (word_t)rec, (word_t)&state_lo, 0x40ce4c, (word_t)&flag);
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
        sk_cont_dequeue(task, 0x40ce60, (word_t)&slot, 0, 0);
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
        sk_cont_wake_loop(task, (word_t)rec, (word_t)&state_lo, 0x40ce94, (word_t)&flag);
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
                sk_cont_dequeue(task, 0x40ce9c, (word_t)&slot, 0, 0);
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
        sk_cont_suspend(task, *(word_t *)(task + 0x60), *(word_t *)(task + 0x68), 0x40ced0, (word_t)&recp, 0);
        return value;
}

/* FUN_0040c640 @ 0x0040c640   (est. sk_cont_set_status)
 * Ghidra: void FUN_0040c640(long param_1, uint param_2, undefined8 param_3,
 *                           long param_4)
 * Sets the continuation status: updates the task's +0x60 status field with
 * param_2's low byte (default 0x19), setting bit 8 if the failure flag (bit 8
 * of param_2) or param_4's high bit (via FUN_0040cfb0) is set.
 * Confidence: low */
void sk_cont_set_status(long task, uint status, word_t param_3, long param_4, ...)
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
        sk_cont_suspend(rq, *(word_t *)(rq + 0x60), *(word_t *)(rq + 0x68), 0x40cf00, (word_t)&recp2, 0);
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
        long store;
        long node;

        sk_status_high_set(task + 0x28);   /* FUN_0040cfbc: mark store torn down */
        store = sk_ptr_offset_8(task);     /* FUN_0040cf24 */
        for (node = *(long *)(store + 0x10); node != 0; node = *(long *)(node + 200)) {
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
        sk_cont_suspend(task, s5, s4, 0x40cab4, (word_t)&flag, 0);
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
        root = sk_task_local_root(0);
        if (*(long *)(root + 0x10) != 0) {
                slot = &value;
                recp = &slot;
                sk_cont_suspend(task, *(word_t *)(task + 0x60), *(word_t *)(task + 0x68), 0x40cf14, (word_t)&recp, 0);
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
                sk_cont_set_status(*(word_t *)(rec + 0x10), param_3, 0, 0);
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
                                        sk_cont_suspend(task, s4, s5, 0x40cb40, (word_t)&slot, 0);
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
        sk_cont_suspend(rq, *(word_t *)(rq + 0x60), *(word_t *)(rq + 0x68), 0x40ca3c, (word_t)&recp2, 0);
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
                sk_cont_suspend(task, *(word_t *)(task + 0x60), *(word_t *)(task + 0x68), 0x40ca84, (word_t)&recp, 0);
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
        rc = (*(vcode *)rec[2])(((word_t *)rec[2])[1], *state, state[1], &st);
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
        long prev;

        cur = *(long *)(task + 0x18);
        prev = 0;
        if (node == *(long *)(task + 0x18)) {
                next = *(long *)(node + 200);
                *(long *)(task + 0x18) = next;
                if (next == 0) {
                        *(word_t *)(task + 0x20) = 0;
                        return;
                }
        } else {
                while (cur != 0 && cur != node) {
                        prev = cur;
                        cur = *(long *)(cur + 200);
                }
                if (cur == node) {
                        *(word_t *)(prev + 200) = *(word_t *)(node + 200);
                        if (node == *(long *)(task + 0x20)) {
                                *(long *)(task + 0x20) = prev;
                                return;
                        }
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
        sk_cont_record_commit((word_t)(group + 1), 0x40ea3c, (word_t)&slot);
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
        sk_task_group_init_full(c, a, (word_t *)b);
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

/* FUN_0040d098 @ 0x0040d098   (est. sk_task_group_add_child)
 * Ghidra: void FUN_0040d098(long param_1, long *param_2, long param_3,
 *                           long *param_4)
 * Adds a child task to a TaskGroup.  The current task becomes the "waiting
 * task": its run-queue hook is set (FUN_0040ea5c), the child task pointer and
 * its body are stored into the caller's result slot (param_4), and the group's
 * live-child counter (+5) is CAS-incremented under LOAcquire/LORelease.  While
 * the group still has live children, the current task registers itself as the
 * group's waiter (allocation via FUN_0040bcf8, registration via FUN_0040bdd0),
 * is linked into the group's waiting list (+6), yields to the scheduler
 * (FUN_00408ae4), and re-checks the counter.  Once no children remain, the
 * group's result is drained via FUN_0040e258/FUN_0040eac8 and the result
 * record is released.
 * Confidence: low
 * Notes: LOAcquire/LORelease atomics; strings 0x5dca8c "accumulating task
 *   group should n..."; group waiting-list +6; continuation 0xa0 slot. */
void sk_task_group_add_child(long child, long *group, long body, long *result)
{
        word_t *cnt;
        word_t st;
        bool first;
        bool second;
        word_t mask;
        int live;
        word_t task;
        word_t token;
        word_t *cb;
        word_t rec_lo, rec_hi;
        word_t rec2;
        word_t waiting_task;
        word_t recv;
        word_t *slot;
        word_t *pair;
        word_t *node;
        long prev_tail;

        task = sk_swift_current_task();
        *(word_t **)(task + 0x38) = (word_t *)0x40ea5c;
        slot = (word_t *)result;
        if (result == 0) {
                slot = 0;
        }
        *(word_t **)(task + 0x40) = slot;
        if (body == 0) {
                body = 0;
        }
        result[1] = body;
        if (sk_reg_x22 == 0) {
                sk_reg_x22 = 0;
        }
        *result = sk_reg_x22;
        result[2] = 0;
        result[3] = child;
        cnt = (word_t *)(group + 5);
        LOAcquire();
        st = *cnt;
        *cnt = st | 0x4000000000000000;
        live = (*(vcode *)(*group + 0x18))((word_t)group);
        mask = 0x3fffffffffffffff;
        if (live == 0) {
                mask = 0x7fffffff;
        }
        if ((mask & st) != 0) {
                first = false;
                do {
                        prev_tail = group[6];
                        if ((st & 0x3fffffff80000000) != 0) {
                                mask = st | 0x4000000000000000;
                                do {
                                        live = (*(vcode *)(*group + 0x18))((word_t)group);
                                        long delta = -0x4000000000000001;
                                        if (live == 0) {
                                                delta = -0x4000000080000001;
                                        }
                                        st = group[5];
                                        if (st == mask) {
                                                group[5] = delta + mask;
                                                if (first) {
                                                        rec_lo = *(ulong *)(task + 0x60);
                                                        rec_hi = *(ulong *)(task + 0x68);
                                                        if (((uint)rec_lo >> 0xe & 1) == 0) {
                                                                mask = *(ulong *)(task + 0x60);
                                                                st = *(ulong *)(task + 0x68);
                                                                if ((mask == rec_hi) && (st == rec_lo)) {
                                                                        *(ulong *)(task + 0x60) = rec_hi;
                                                                        *(ulong *)(task + 0x68) =
                                                                                (ulong)((uint)rec_lo & 0xffffa3ff | 0x800);
                                                                }
                                                                if (mask != rec_lo || st != rec_hi) {
                                                                        do {
                                                                                recv = *(ulong *)(task + 0x60);
                                                                                st = *(ulong *)(task + 0x68);
                                                                                if ((recv == st) && (st == mask)) {
                                                                                        *(ulong *)(task + 0x60) = st;
                                                                                        *(ulong *)(task + 0x68) =
                                                                                                (ulong)((uint)mask & 0xffffe3ff | 0x800);
                                                                                }
                                                                                first = recv != mask;
                                                                                second = st != st;
                                                                                mask = recv;
                                                                                st = st;
                                                                        } while (first || second);
                                                                }
                                                        } else {
                                                                token = *(word_t *)(task + 0xa0);
                                                                sk_cont_resume_async(task, token, &rec_lo, 0x4090d8, (word_t)&slot);
                                                                sk_cont_record_free(task, token);
                                                                *(word_t *)(task + 0xa0) = 0;
                                                        }
                                                        sk_ctx_restore2(task);
                                                        sk_swift_deinit_small(task + 0x50);
                                                }
                                                sk_cont_record_pop((long)(group + 7), (word_t)&rec_lo);
                                                recv = rec_lo & 3;
                                                if (recv == 1) {
                                                        sk_precond_fatal(0, 0x5dca8c);
                                                }
                                                st = rec_lo & 0xfffffffffffffffc;
                                                prev_tail = 0xc0;
                                                if ((*(uint *)(st + 0x20) & 0x1000000) != 0) {
                                                        prev_tail = 0xd0;
                                                }
                                                if (recv == 0) {
                                                        rec_hi = 0;
                                                        st = 0;
                                                        waiting_task = group[0xd];
                                                } else {
                                                        prev_tail = st + prev_tail +
                                                                ((ulong)(*(uint *)(st + 0x20) >> 0x17) & 8);
                                                        if (recv == 3) {
                                                                waiting_task = 0;
                                                                rec_hi = *(ulong *)(prev_tail + 0x10);
                                                        } else {
                                                                waiting_task = *(long *)(prev_tail + 8);
                                                                recv = (ulong)*(byte *)(*(long *)(waiting_task + -8) + 0x50);
                                                                rec_hi = recv + prev_tail + 0x18 &
                                                                        (recv ^ 0xffffffffffffffff);
                                                        }
                                                }
                                                goto drain;
                                        }
                                        mask = st;
                                } while ((st & 0x3fffffff80000000) != 0);
                        }
                        if (!first) {
                                node = (word_t *)sk_cont_set_alloc(task, 0x30);
                                *node = 0;
                                node[1] = 0;
                                *(uint *)(node + 4) = 3;
                                node[5] = task;
                                node[2] = (word_t)group;
                                *(word_t **)(task + 0xa0) = node;
                                rec_lo = *(ulong *)(task + 0x60);
                                rec_hi = *(ulong *)(task + 0x68);
                                slot = &node;
                                pair = &rec_lo;
                                sk_cont_wake_loop(task, (word_t)node, (word_t)&rec_lo, 0x40af00, (word_t)&slot);
                                sk_swift_destroy_small(task + 0x50);
                                sk_ctx_restore(0);
                        }
                        recv = group[6];
                        if (recv == prev_tail) {
                                group[6] = task;
                        } else {
                                do {
                                        prev_tail = group[6];
                                        first = prev_tail != recv;
                                        recv = prev_tail;
                                } while (first);
                                group[6] = task;
                        }
                        token = sk_ctx_save(0);
                        sk_task_resume(group[3], 0, 0);
                        sk_ctx_save2(token);
                        LOAcquire();
                        st = group[5];
                        group[5] = st | 0x4000000000000000;
                        live = (*(vcode *)(*group + 0x18))((word_t)group);
                        mask = 0x3fffffffffffffff;
                        if (live == 0) {
                                mask = 0x7fffffff;
                        }
                        first = true;
                } while ((mask & st) != 0);
        }
        st = 0;
        rec_hi = 0;
        mask = 0;
        *cnt = *cnt & 0xbfffffffffffffff;
        LORelease();
        waiting_task = group[0xd];
drain:
        rec_lo = mask;
        rec2 = st;
        sk_cont_result_dispatch((long)result, (word_t)&rec_lo);
        if (st != 0) {
                sk_cont_wake_task((word_t)group, (long)st);
                sk_swift_release(st);
        }
        cb = *(word_t **)(task + 0x38);
        ((vcode)cb)((word_t)cb, task + 0x38 & 0xffffffffffff | 0x2c42000000000000);
        return;
}

/* FUN_0040d5b8 @ 0x0040d5b8   (est. sk_task_local_cleanup)
 * Ghidra: void FUN_0040d5b8(long param_1)
 * Marks the task-local store as torn down (sets bit 63 of +0x28) and, if this
 * is the first teardown, runs the task-local check-wake hook
 * (FUN_0040c7dc) against the current task.
 * Confidence: low */
void sk_task_local_cleanup(long store)
{
        word_t v;
        word_t task;

        task = sk_swift_current_task();
        v = *(ulong *)(store + 0x28);
        *(ulong *)(store + 0x28) = v | 0x8000000000000000;
        if (-1 < (long)v) {
                sk_task_local_check_wake(store, task);
                return;
        }
        return;
}

/* FUN_0040d604 @ 0x0040d604   (est. sk_task_group_end)
 * Ghidra: uint FUN_0040d604(long *param_1, ulong param_2)
 * Ends a TaskGroup: increments the group's task counter (+5), checks it
 * against the group's capacity (via the +0x18 vtable predicate) and, when the
 * count equals the capacity, builds a "TaskGroupStatus: ..." diagnostic string
 * (with the count and status bits rendered via the error-string helpers),
 * formats the group's record buffer (FUN_0040ec54), builds the final error
 * via FUN_0040ebac and aborts (FUN_00116d60).  Otherwise returns whether the
 * group is still accepting tasks.
 * Confidence: low
 * Notes: strings 0x5dcb68 "TaskGroupStatus: "; error fns FUN_00112db4/
 *   FUN_00112e8c/FUN_0011394c/FUN_00113c30/FUN_001131f4; records 0x5d6fcd/
 *   0x5d6ff3; assert hook FUN_00118b94; noreturn FUN_00116d60. */
uint sk_task_group_end(long *group, word_t accepting)
{
        word_t v;
        word_t count;
        int i;
        word_t mask;
        long *node;
        word_t fmt[3];
        word_t bits;
        word_t fmt2;
        word_t fmt2hi;
        word_t fmt2sz;
        word_t *q;

        count = group[5];
        group[5] = count + 1;
        bits = count + 1;
        i = ((vcode)(*(word_t *)(*group + 0x18)))(0);
        mask = 0x3fffffffffffffff;
        if (i == 0) {
                mask = 0x7fffffff;
        }
        i = (*(vcode *)(*group + 0x18))((word_t)group);
        v = 0x3fffffffffffffff;
        if (i == 0) {
                v = 0x7fffffff;
        }
        if ((mask & bits) == v) {
                (*(vcode *)(*group + 0x18))((word_t)group);
                fmt[0] = 0;
                fmt[1] = 0;
                fmt[2] = 0;
                sk_str_append2(&fmt, 0x5dcb68);   /* "TaskGroupStatus: " */
                sk_str_append2(&fmt, 0x5dcb7a);
                word_t *p = (word_t *)0x5d6ff3;
                if (-1 < (long)bits) {
                        p = (word_t *)0x5d6fcd;
                }
                sk_str_append2(&fmt, p);
                sk_str_append2(&fmt, 0x5dcb7d);
                p = (word_t *)0x5d6fcd;
                if ((bits & 0x4000000000000000) != 0) {
                        p = (word_t *)0x5d6ff3;
                }
                sk_str_append2(&fmt, p);
                mask = (*(vcode *)(*group + 0x18))((word_t)group);
                if ((mask & 1) == 0) {
                        sk_str_append2(&fmt, 0x5dcb81);
                        sk_error_fmt3(&fmt2, bits >> 0x1f & 0x7fffffff);
                        mask = fmt2hi;
                        word_t *q = (word_t *)fmt2;
                        if (-1 < (long)fmt2sz) {
                                mask = fmt2sz >> 0x38;
                                q = &fmt2;
                        }
                        sk_str_render(&fmt, q, mask);
                        if ((long)fmt2sz < 0) {
                                sk_free(fmt2, fmt2sz & 0x7fffffffffffffff);
                        }
                }
                sk_str_append2(&fmt, 0x5dcb85);
                i = (*(vcode *)(*group + 0x18))((word_t)group);
                mask = 0x3fffffffffffffff;
                if (i == 0) {
                        mask = 0x7fffffff;
                }
                sk_error_fmt2(&fmt2, mask & bits);
                q = (word_t *)fmt2;
                if (-1 < (long)fmt2sz) {
                        fmt2hi = fmt2sz >> 0x38;
                        q = &fmt2;
                }
                sk_str_render(&fmt, q, fmt2hi);
                if ((long)fmt2sz < 0) {
                        sk_free(fmt2, fmt2sz & 0x7fffffffffffffff);
                }
                bits = bits;
                sk_task_group_dump(fmt, &bits, 0x30, 0x31);
                node = (long *)sk_error_fmt(fmt, 0, 0x5d021c);
                fmt2sz = node[2];
                fmt2hi = node[1];
                fmt2 = *node;
                node[1] = 0;
                node[2] = 0;
                *node = 0;
                bits = fmt2hi;
                q = (word_t *)fmt2;
                if (-1 < (long)fmt2sz) {
                        bits = fmt2sz >> 0x38;
                        q = &fmt2;
                }
                sk_str_render(&fmt, q, bits);
                if ((long)fmt2sz < 0) {
                        sk_free(fmt2, fmt2sz & 0x7fffffffffffffff);
                }
                sk_str_append2(&fmt, 0x5d8a3a);
                sk_task_group_error(fmt);
                i = sk_runtime_once2();
                if (i != 0) {
                        /* register the assert hook (raw machine-code thunk) */
                        word_t thunk[10];
                        thunk[0] = 0x910153e2d65f03c0;
                        thunk[1] = 0xf94013ead65f03c0;
                        thunk[2] = 0x8b08014391032149;
                        thunk[3] = 0x9112a14ab000012a;
                        thunk[4] = 0xd65f03c0eb09007f;
                        thunk[5] = 0xaa1303e2aa1403e1;
                        thunk[6] = 0xaa1503e0d65f03c0;
                        thunk[7] = 0x409000;   /* FUN_0067f528 */
                        thunk[8] = 0x409010;
                        thunk[9] = 0x409020;
                        thunk_FUN_00369b04(1, fmt[0], &thunk);
                }
                sk_assert_hook(fmt[0]);
                sk_free(fmt[0]);
                sk_assert_abort();
        }
        if (((accepting & 1) == 0) && ((long)bits < 0)) {
                count = group[5];
                group[5] = count - 1;
                bits = count - 1;
        }
        return (uint)(bits >> 0x3f) ^ 1;
}

/* FUN_0040d99c @ 0x0040d99c   (est. sk_task_group_wait)
 * Ghidra: void FUN_0040d99c(long param_1, long *param_2, ulong param_3,
 *                           long param_4, long *param_5)
 * Waits for a TaskGroup to finish.  Sets up the current task as the group's
 * waiter (run-queue hook FUN_0040ea5c), records the child body into the result
 * slot (param_5), then while the group still has live children registers the
 * current task as waiter, links it into the waiting list, yields to the
 * scheduler and re-checks.  Once done, drains the group's first result via
 * FUN_0040e258 and dispatches it (FUN_0040eac8).  The group's child result is
 * retained when param_3 is set.
 * Confidence: low */
void sk_task_group_wait(long child, long *group, word_t want_result, long body,
                        long *result)
{
        word_t mask;
        int live;
        word_t task;
        word_t token;
        long tail;
        long node;
        word_t pending;
        word_t rec;
        bool first;
        long tmp;
        long group_tail;
        word_t rec_lo, rec_hi;
        word_t recv;
        word_t *slot;
        word_t *pair;
        word_t *nodeptr;

        task = sk_swift_current_task();
        *(word_t **)(task + 0x38) = (word_t *)0x40ea5c;
        slot = (word_t *)result;
        if (result == 0) {
                slot = 0;
        }
        *(word_t **)(task + 0x40) = slot;
        if (body == 0) {
                body = 0;
        }
        result[1] = body;
        if (sk_reg_x22 == 0) {
                sk_reg_x22 = 0;
        }
        *result = sk_reg_x22;
        result[2] = 0;
        result[3] = child;
        group_tail = group[0xd];
        pending = group[5];
        live = (*(vcode *)(*group + 0x18))((word_t)group);
        mask = 0x3fffffffffffffff;
        if (live == 0) {
                mask = 0x7fffffff;
        }
        if ((mask & pending) != 0) {
                first = false;
                do {
                        if ((want_result != 0) &&
                            (live = (*(vcode *)(*group + 0x18))((word_t)group), live != 0) &&
                            (group[0xc] == 0)) {
                                sk_task_group_store(group + 7, want_result | 1);
                        }
                        tail = group[6];
                        if (!first) {
                                nodeptr = (word_t *)sk_cont_set_alloc(task, 0x30);
                                *nodeptr = 0;
                                nodeptr[1] = 0;
                                *(uint *)(nodeptr + 4) = 3;
                                nodeptr[5] = task;
                                nodeptr[2] = (word_t)group;
                                *(word_t **)(task + 0xa0) = nodeptr;
                                rec_lo = *(ulong *)(task + 0x60);
                                rec_hi = *(ulong *)(task + 0x68);
                                slot = &nodeptr;
                                pair = &rec_lo;
                                sk_cont_wake_loop(task, (word_t)nodeptr, (word_t)&rec_lo, 0x40af00, (word_t)&slot);
                                sk_swift_destroy_small(task + 0x50);
                                sk_ctx_restore(0);
                        }
                        node = group[6];
                        if (node == tail) {
                                group[6] = task;
                        } else {
                                do {
                                        tail = group[6];
                                        first = tail != node;
                                        node = tail;
                                } while (first);
                                group[6] = task;
                        }
                        mask = group[5];
                        group[5] = mask | 0x4000000000000000;
                        LORelease();
                        token = sk_ctx_save(mask);
                        sk_task_resume(group[3], 0, 0);
                        sk_ctx_save2(token);
                        pending = group[5];
                        live = (*(vcode *)(*group + 0x18))((word_t)group);
                        mask = 0x3fffffffffffffff;
                        if (live == 0) {
                                mask = 0x7fffffff;
                        }
                        first = true;
                } while ((mask & pending) != 0);
        }
        live = (*(vcode *)(*group + 0x18))((word_t)group);
        if (live == 0) {
                mask = 0;
                pending = 0;
        } else {
                live = sk_cont_record_pop((long)(group + 7), (word_t)&rec_lo);
                if (live == 0) {
                        mask = 0;
                        pending = 0;
                } else if ((rec_lo & 3) == 1) {
                        mask = rec_lo & 0xfffffffffffffffc;
                        pending = 3;
                } else {
                        if ((rec_lo & 3) == 3) {
                                recv = rec_lo & 0xfffffffffffffffc;
                                long off = 0xc0;
                                if ((*(uint *)(recv + 0x20) & 0x1000000) != 0) {
                                        off = 0xd0;
                                }
                                node = recv + off + ((ulong)(*(uint *)(recv + 0x20) >> 0x17) & 8);
                                rec = *(long *)(node + 8);
                                mask = *(ulong *)(node + 0x10);
                                pending = 3;
                                goto done_pop;
                        }
                        mask = 0;
                        pending = 0;
                }
        }
        recv = 0;
done_pop:
        if (want_result == 0) {
                rec_lo = pending;
                rec_hi = mask;
                tmp = group_tail;
                rec = recv;
                sk_cont_result_dispatch((long)result, (word_t)&rec_lo);
        } else {
                result[2] = want_result;
                sk_swift_retain(want_result);
        }
        if (recv != 0) {
                sk_cont_wake_task((word_t)group, (long)recv);
                sk_swift_release(recv);
        }
        (**(void (**)(word_t))(task + 0x38))(task + 0x38 & 0xffffffffffff | 0x2c42000000000000);
        return;
}

/* FUN_0040dd90 @ 0x0040dd90   (est. sk_task_group_init_full)
 * Ghidra: void FUN_0040dd90(undefined8 param_1, uint param_2, undefined8 *param_3)
 * Full task-group initializer: zeroes all fields, selects the group's type
 * metadata (0x67f470 if the "throwing" flag bit 8 of param_2 is set, else
 * 0x67f4f0), sets kind=2, records the parent group (param_1) at +0xd, and
 * registers the group via FUN_0040c09c (callback FUN_0040ea3c).
 * Confidence: low */
void sk_task_group_init_full(word_t parent, uint flags, word_t *group)
{
        word_t meta;
        word_t *slot;
        word_t *rec;

        group[0xc] = 0;
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
        if ((flags >> 8 & 1) == 0) {
                meta = 0x67f4f0;
        } else {
                meta = 0x67f470;
        }
        group[1] = 2;
        group[0xd] = parent;
        *group = meta;
        slot = &rec;
        rec = group;
        sk_cont_record_commit((word_t)(group + 1), 0x40ea3c, (word_t)&slot);
        return;
}

/* FUN_0040de24 @ 0x0040de24   (est. sk_task_local_deinit_a)
 * Ghidra: void FUN_0040de24(void)
 * Resolves the task-local store and frees it (0x70 bytes, tag 7).
 * Confidence: low */
void sk_task_local_deinit_a(void)
{
        word_t store;

        store = sk_task_local_store(0);
        sk_free(store, 0x70, 7);
        return;
}

/* FUN_0040de28 @ 0x0040de28   (est. sk_task_local_deinit_b)
 * Ghidra: void FUN_0040de28(void)
 * Same shape as 0040de24 (alternate task-local store deinit).
 * Confidence: low */
void sk_task_local_deinit_b(void)
{
        word_t store;

        store = sk_task_local_store(0);
        sk_free(store, 0x70, 7);
        return;
}

/* FUN_0040de48 @ 0x0040de48   (est. sk_task_local_invoke)
 * Ghidra: void FUN_0040de48(undefined8 *param_1)
 * Resumes the task-local continuation record (FUN_0040c280) then invokes the
 * object's closure through its vtable (param_1[0]).
 * Confidence: low */
void sk_task_local_invoke(word_t *obj)
{
        sk_cont_resume_record((word_t)(obj + 1), 0, 0);
        (*(vcode *)*obj)((word_t)obj);
        return;
}

/* FUN_0040de9c @ 0x0040de9c   (est. sk_task_group_child_end)
 * Ghidra: void FUN_0040de9c(long *param_1, long param_2, long param_3)
 * Ends a child task of a TaskGroup.  Decrements the group's live-child
 * counter (+5) under LOAcquire/LORelease; when the count reaches the point at
 * which the last child is finishing (checked via the +0x18 vtable predicate),
 * locks the group, claims the group's waiting task (+6) and delivers the child
 * result: either stores it into the result record (FUN_0040e2f0) or invokes
 * the group's completion vtable (+0x28).  Panics "Claimed NULL waitingTask!"
 * (0x5dca72) or "only errors can be stored by a d..." (0x5dca22/0x5dc9d2) on
 * invalid states.
 * Confidence: low */
void sk_task_group_child_end(long *group, long child, long body)
{
        word_t *cnt;
        word_t st;
        word_t mask;
        int live;
        word_t token;
        char *fatal;
        word_t tail;
        word_t waiting;
        word_t rec;
        long prev;

        cnt = (word_t *)(group + 5);
        tail = group[5];
        prev = *(long *)(body + -8);
        st = *cnt;
        *cnt = st - 1;
        LORelease();
        st = st - 1;
        if (prev == 0) {
                if ((st >> 0x3e & 1) == 0) {
                        goto no_wait;
                }
                live = (*(vcode *)(*group + 0x18))((word_t)group);
                mask = 0x3fffffffffffffff;
                if (live == 0) {
                        mask = 0x7fffffff;
                }
                if ((mask & st) != 0) {
                        goto no_wait;
                }
                LOAcquire();
                waiting = group[6];
                group[6] = tail;
                if (waiting != 0) {
                        live = sk_cont_record_pop((long)(group + 7), (word_t)&rec);
                        if (live != 0) {
                                sk_cont_wake_task((word_t)group, (long)child);
                                if ((rec & 3) != 3) {
                                        if ((rec & 3) != 1) {
                                                fatal = (char *)0x5dca22;
                                                goto fatal_deliver;
                                        }
                                        goto store_err;
                                }
                                goto deliver_rec;
                        }
                        deliver_empty:
                        sk_cont_deliver(group, child, 0);
                        return;
                }
                fatal = (char *)0x5dca72;   /* "Claimed NULL waitingTask!" */
                goto fatal_deliver;
        }
        token = *(word_t *)(child + 0xc0);
        st = *cnt;
        *cnt = st | 0x8000000000000000;
        if (-1 < (long)st) {
                sk_task_local_check_wake(child, token);
        }
        if ((st >> 0x3e & 1) != 0) {
                live = (*(vcode *)(*group + 0x18))((word_t)group);
                mask = 0x3fffffffffffffff;
                if (live == 0) {
                        mask = 0x7fffffff;
                }
                if ((mask & st) == 0) {
                        LOAcquire();
                        waiting = group[6];
                        group[6] = tail;
                        if (waiting != 0) {
                                live = sk_cont_record_pop((long)(group + 7), (word_t)&rec);
                                sk_cont_wake_task((word_t)group, (long)child);
                                if (live == 0) {
                                        sk_cont_deliver(group, child, 1);
                                        return;
                                }
                                if ((rec & 3) == 3) {
                                        goto deliver_rec;
                                }
                                if ((rec & 3) == 1) {
                                        goto store_err;
                                }
                                fatal = (char *)0x5dc9d2;
                                goto fatal_deliver;
                        }
                        goto fatal_wait_null;
                }
        }
        if (group[0xc] == 0) {
                sk_cont_deliver(group, child, 1);
                return;
        }
no_wait:
        sk_cont_wake_task((word_t)group, (long)child);
        return;
deliver_rec:
        sk_cont_deliver(group, rec & 0xfffffffffffffffc, 1);
        return;
store_err:
        sk_task_group_store(group + 7, rec & 0xfffffffffffffffc | 1);
        return;
fatal_wait_null:
        fatal = (char *)0x5dca72;
fatal_deliver:
        sk_precond_fatal(0, fatal);
}

/* FUN_0040e128 @ 0x0040e128   (est. sk_task_group_store2)
 * Ghidra: void FUN_0040e128(undefined8 param_1, undefined8 param_2)
 * Retains the child result and stores it into the group's result record.
 * Confidence: low */
void sk_task_group_store2(word_t group, word_t result)
{
        sk_swift_retain(result);
        sk_task_group_store((word_t *)(sk_reg_x10 + 0x38), sk_reg_x9 | 3);
        return;
}

/* FUN_0040e158 @ 0x0040e158   (est. sk_task_local_store)
 * Ghidra: undefined8 * FUN_0040e158(undefined8 *param_1)
 * Tears down a task-local store: frees the value buffers (each 0x1000-byte
 * page via sk_free tag 7), advances the value pointer, and frees the key
 * buffer.  Returns the store.
 * Confidence: high (verified 1:1 vs decompile+disasm; clean logic, no opaque
 * register-forwarding) */
word_t sk_task_local_store(word_t store)
{
        word_t *p;
        word_t *end;
        word_t *q;
        word_t v;
        long diff;

        *(word_t *)store = 0x67f4b0;
        word_t *stp=(word_t *)store; end = (word_t *)stp[8];
        p = (word_t *)stp[9];
        stp[0xc] = 0;
        diff = (long)p - (long)end;
        while ((diff >> 3) > 2) {
                sk_free(*end, 0x1000, 7);
                p = (word_t *)stp[9];
                end = (word_t *)((word_t *)stp[8] + 8);
                stp[8] = (word_t)end;
                diff = (long)p - (long)end;
        }
        v = (diff >> 3);
        if (v == 1) {
                v = 0x100;
        } else {
                if (v != 2) {
                        goto skip_tag;
                }
                v = 0x200;
        }
        stp[0xb] = v;
skip_tag:
        if (end != p) {
                do {
                        q = end + 1;
                        sk_free(*end, 0x1000, 7);
                        end = q;
                } while (q != p);
                diff = stp[8] - stp[9];
                if (diff != 0) {
                        stp[9] = stp[9] + (diff + 7 & 0xfffffffffffffff8);
                }
        }
        diff = stp[7];
        if (diff != 0) {
                sk_free(diff, stp[10] - diff, 7);
        }
        return (word_t)stp;
}

/* FUN_0040e258 @ 0x0040e258   (est. sk_cont_record_pop)
 * Ghidra: bool FUN_0040e258(long param_1, undefined8 *param_2)
 * Pops a record from the task-group result queue: if the queue has a pending
 * entry (count at +0x28), reads the entry indexed by the head (+0x20) from the
 * ring buffer, advances the head, and when a page boundary is crossed frees
 * the old page.  Returns whether a record was available.
 * Confidence: low */
bool sk_cont_record_pop(long queue, word_t out)
{
        word_t count;
        word_t *buf;
        word_t idx;
        long head;

        count = *(long *)(queue + 0x28);
        if (count != 0) {
                buf = *(word_t **)(queue + 8);
                idx = *(ulong *)(queue + 0x20);
                *(word_t *)out = *(word_t *)(buf[idx >> 9] + (idx & 0x1ff) * 8);
                if (*(long *)(queue + 0x28) == 0) {
                        SK189_FATAL(0x40e2f0);
                }
                head = *(long *)(queue + 0x20) + 1;
                *(ulong *)(queue + 0x20) = head;
                *(long *)(queue + 0x28) = *(long *)(queue + 0x28) - 1;
                if (0x3ff < head) {
                        sk_free(*buf, 0x1000, 7);
                        *(long *)(queue + 8) = *(long *)(queue + 8) + 8;
                        *(long *)(queue + 0x20) = *(long *)(queue + 0x20) - 0x200;
                }
        }
        return count != 0;
}

/* FUN_0040e2f0 @ 0x0040e2f0   (est. sk_task_group_store)
 * Ghidra: void FUN_0040e2f0(ulong *param_1, undefined8 param_2)
 * Stores a child result into the task-group result ring buffer: if the buffer
 * is full, grows it (allocating a new 0x1000-byte page and copying the used
 * entries), then writes the record into the tail slot and bumps the tail
 * count (+5).
 * Confidence: high */
void sk_task_group_store(word_t *queue, word_t record)
{
        word_t *begin, *end;
        word_t *p, *q, *newbuf;
        word_t *head;
        word_t len;
        long off;
        long count;
        word_t cap;
        word_t *slot;
        word_t *old;
        word_t *src, *dst;
        long i;

        begin = (word_t *)queue[1];
        end = (word_t *)queue[2];
        len = (long)end - (long)begin;
        count = 0;
        if (len != 0) {
                count = ((long)end - (long)begin) * 0x40 - 1;
        }
        cap = queue[4];
        if (count != queue[5] + cap) {
                goto write_slot;
        }
        if (cap < 0x200) {
                slot = queue + 3;
                head = (word_t *)*slot;
                cap = (long)head - (long)*queue;
                if (cap <= len) {
                        long nc = 8;
                        if (head != (word_t *)*queue) {
                                nc = cap * 2;
                        }
                        word_t *grow_slot = slot;
                        p = (word_t *)sk_swift_alloc(nc, 7);
                        q = (word_t *)((long)p + len);
                        newbuf = (word_t *)((long)p + nc);
                        old = p;
                        src = q;
                        dst = newbuf;
                        cap = sk_swift_alloc(0x1000, 7);
                        end = p;
                        head = newbuf;
                        if (len == nc) {
                                if (end == begin) {
                                        q = (word_t *)sk_swift_alloc(8, 7);
                                        head = q + 1;
                                        old = q;
                                        src = q;
                                        dst = head;
                                        end = p;
                                        q = p;
                                        count = (word_t)begin;
                                        q = (word_t *)q;
                                        dst = (word_t *)len;
                                        sk_cont_buf_destroy((word_t)&old);
                                        src = q;
                                } else {
                                        count = ((long)len >> 3) + 1;
                                        src = q + -((ulong)(count - (count >> 0x3f)) >> 1);
                                        q = src;
                                }
                        }
                        dst = q + 1;
                        *q = cap;
                        begin = (word_t *)queue[1];
                        end = (word_t *)queue[2];
                        newbuf = dst;
                        if (end != begin) {
                                do {
                                        begin = q;
                                        if (q == end) {
                                                if (dst < head) {
                                                        count = ((long)head - (long)dst >> 3) + 1;
                                                        long mv = (long)dst - (long)q;
                                                        p = dst + ((ulong)(count - (count >> 0x3f)) >> 1);
                                                        begin = (word_t *)((long)p - mv);
                                                        dst = p;
                                                        if (mv != 0) {
                                                                sk_memmove(begin, q, mv);
                                                        }
                                                } else {
                                                        count = (long)head - (long)q >> 2;
                                                        if ((long)head - (long)q == 0) {
                                                                count = 1;
                                                        }
                                                        q = (word_t *)sk_swift_alloc(count << 3, 7);
                                                        begin = (word_t *)((long)q + (count * 2 + 6 & 0xfffffffffffffff8));
                                                        long mv = (long)dst - (long)q;
                                                        src = begin;
                                                        if (mv != 0) {
                                                                src = (word_t *)((long)begin + mv);
                                                                p = begin;
                                                                word_t *s = q;
                                                                do {
                                                                        *p = *s;
                                                                        mv = mv - 8;
                                                                        p = p + 1;
                                                                        s = s + 1;
                                                                } while (mv != 0);
                                                        }
                                                        old = end;
                                                        dst = q;
                                                        head = q + count;
                                                        dst = src;
                                                        end = q;
                                                        q = begin;
                                                }
                                        }
                                        end = end - 1;
                                        q = begin - 1;
                                        *q = *end;
                                        begin = (word_t *)queue[1];
                                } while (end != begin);
                                end = (word_t *)queue[2];
                        }
                        old = (word_t *)*queue;
                        *queue = (word_t)end;
                        queue[1] = (word_t)q;
                        dst = (word_t *)queue[3];
                        queue[2] = (word_t)src;
                        queue[3] = (word_t)head;
                        newbuf = begin;
                        dst = end;
                        sk_cont_buf_destroy((word_t)&old);
                        goto write_slot;
                }
                begin = (word_t *)sk_swift_alloc(0x1000, 7);
                if (head != end) {
                        end = (word_t *)queue[2];
                        if (end == (word_t *)queue[3]) {
                                len = *queue;
                                cap = queue[1];
                                if (cap < len || cap - len == 0) {
                                        cap = (long)((long)end - len) >> 2;
                                        if ((long)end - len == 0) {
                                                cap = 1;
                                        }
                                        len = sk_swift_alloc(cap << 3, 7);
                                        end = (word_t *)(len + (cap >> 2) * 8);
                                        dst = (word_t *)queue[2];
                                        count = queue[2] - (long)queue[1];
                                        head = end;
                                        if (count != 0) {
                                                head = (word_t *)((long)end + count);
                                                p = (word_t *)queue[1];
                                                q = end;
                                                do {
                                                        *q = *p;
                                                        count = count - 8;
                                                        p = p + 1;
                                                        q = q + 1;
                                                } while (count != 0);
                                        }
                                        old = (word_t *)*queue;
                                        *queue = len;
                                        queue[1] = (word_t)end;
                                        dst = (word_t *)queue[3];
                                        queue[2] = (word_t)head;
                                        queue[3] = len + cap * 8;
                                        sk_cont_buf_destroy((word_t)&old);
                                        end = (word_t *)queue[2];
                                } else {
                                        count = (((long)(cap - len) >> 3) + 1) / 2;
                                        long tail = cap + count * -8;
                                        long mv = (long)end - cap;
                                        if (mv != 0) {
                                                sk_memmove(tail, cap, mv);
                                                cap = queue[1];
                                        }
                                        end = (word_t *)(tail + mv);
                                        queue[1] = cap + count * -8;
                                }
                        }
                        *end = (word_t)begin;
                        queue[2] = (word_t)(end + 1);
                        goto write_slot;
                }
                len = queue[1];
                if (len == *queue) {
                        cap = queue[2];
                        off = queue[3];
                        if (cap < off) {
                                count = (((long)(off - cap) >> 3) + 1) / 2;
                                off = count * 8 + len;
                                if (cap - len != 0) {
                                        sk_memmove(off, len, cap - len);
                                        cap = queue[2];
                                }
                                queue[2] = cap + count * 8;
                                len = off;
                        } else {
                                count = (long)(off - len) >> 2;
                                if (off - len == 0) {
                                        count = 1;
                                }
                                q = (word_t *)sk_swift_alloc(count << 3, 7);
                                end = (word_t *)(q + (count * 2 + 6 & 0xfffffffffffffff8));
                                dst = (word_t *)queue[2];
                                count = queue[2] - (long)queue[1];
                                head = end;
                                if (count != 0) {
                                        head = (word_t *)((long)end + count);
                                        p = (word_t *)queue[1];
                                        src = end;
                                        do {
                                                *src = *p;
                                                count = count - 8;
                                                p = p + 1;
                                                src = src + 1;
                                        } while (count != 0);
                                }
                                old = (word_t *)*queue;
                                *queue = (word_t)q;
                                queue[1] = (word_t)end;
                                dst = (word_t *)queue[3];
                                queue[2] = (word_t)head;
                                queue[3] = (word_t)(q + count * 8);
                                sk_cont_buf_destroy((word_t)&old);
                                len = queue[1];
                        }
                }
                *(word_t **)(len - 8) = (word_t *)begin;
                queue[1] = len;
                old = begin;
        } else {
                queue[4] = cap - 0x200;
                old = (word_t *)*begin;
                queue[1] = (word_t)(begin + 1);
        }
        sk_cont_buf_append(queue, &old);   /* FUN_0040e79c */
write_slot:
        *(word_t *)(*(long *)(queue[1] + (queue[5] + queue[4] >> 9) * 8) +
                    (queue[5] + queue[4] & 0x1ff) * 8) = record;
        queue[5] = queue[5] + 1;
        return;
}

/* FUN_0040e79c @ 0x0040e79c   (est. sk_cont_buf_append)
 * Ghidra: void FUN_0040e79c(ulong *param_1, undefined8 *param_2)
 * Appends a value to a growable word buffer (param_1: {base,start,end,cap}):
 * grows the backing store when the buffer is full (copy into a new allocation
 * or shift into reserved space) then stores the value and bumps the end.
 * Confidence: low */
void sk_cont_buf_append(word_t *buf, word_t *value)
{
        word_t *end;
        word_t base, start;
        word_t *dst, *src;
        word_t *p, *q;
        long off;
        long mv;
        word_t cap;
        word_t *old;

        end = (word_t *)buf[2];
        if (end == (word_t *)*buf + 3) {
                base = *buf;
                start = buf[1];
                if (start < base || start - base == 0) {
                        cap = (long)((long)end - base) >> 2;
                        if ((long)end - base == 0) {
                                cap = 1;
                        }
                        base = sk_swift_alloc(cap << 3, 7);
                        end = (word_t *)(base + (cap >> 2) * 8);
                        dst = (word_t *)buf[2];
                        src = (word_t *)buf[1];
                        mv = buf[2] - (long)src;
                        q = end;
                        if (mv != 0) {
                                q = (word_t *)((long)end + mv);
                                p = src;
                                dst = end;
                                do {
                                        *dst = *p;
                                        mv = mv - 8;
                                        p = p + 1;
                                        dst = dst + 1;
                                } while (mv != 0);
                        }
                        old = (word_t *)*buf;
                        *buf = base;
                        buf[1] = (word_t)end;
                        cap = buf[3];
                        buf[2] = (word_t)q;
                        buf[3] = base + cap * 8;
                        sk_cont_buf_destroy((word_t)&old);
                        end = (word_t *)buf[2];
                } else {
                        off = (((long)(start - base) >> 3) + 1) / 2;
                        long tail = start + off * -8;
                        mv = (long)end - start;
                        if (mv != 0) {
                                sk_memmove(tail, start, mv);
                                start = buf[1];
                        }
                        end = (word_t *)(tail + mv);
                        buf[1] = start + off * -8;
                }
        }
        *end = *value;
        buf[2] = (word_t)(end + 1);
        return;
}

/* FUN_0040e8c4 @ 0x0040e8c4   (est. sk_cont_buf_destroy)
 * Ghidra: long * FUN_0040e8c4(long *param_1)
 * Destroys a growable word buffer: advances the start pointer past any used
 * bytes, then frees the backing allocation.
 * Confidence: low */
word_t sk_cont_buf_destroy(word_t buf, ...)
{
        long used; word_t *bp=(word_t *)buf;

        used = bp[1] - bp[2];
        if (used != 0) {
                bp[2] = bp[2] + (used + 7 & 0xfffffffffffffff8);
        }
        used = *bp;
        if (used != 0) {
                sk_free(used, bp[3] - used, 7);
        }
        return (word_t)bp;
}

/* FUN_0040e920 @ 0x0040e920   (est. sk_task_local_deinit_c)
 * Ghidra: void FUN_0040e920(void)
 * Resolves and frees the task-local store (0x70 bytes, tag 7).
 * Confidence: low */
void sk_task_local_deinit_c(void)
{
        word_t store;

        store = sk_task_local_store(0);
        sk_free(store, 0x70, 7);
        return;
}

/* FUN_0040e924 @ 0x0040e924   (est. sk_task_local_deinit_d)
 * Ghidra: void FUN_0040e924(void)
 * Same shape as 0040e920 (alternate task-local store deinit).
 * Confidence: low */
void sk_task_local_deinit_d(void)
{
        word_t store;

        store = sk_task_local_store(0);
        sk_free(store, 0x70, 7);
        return;
}

/* FUN_0040e944 @ 0x0040e944   (est. sk_task_local_invoke2)
 * Ghidra: void FUN_0040e944(undefined8 *param_1)
 * Resumes the task-local continuation record then invokes the object closure.
 * Confidence: low */
void sk_task_local_invoke2(word_t *obj)
{
        sk_cont_resume_record((word_t)(obj + 1), 0, 0);
        (*(vcode *)*obj)((word_t)obj);
        return;
}

/* FUN_0040e9e4 @ 0x0040e9e4   (est. sk_claim_null_waiting_fatal)
 * Ghidra: void FUN_0040e9e4(void)
 * Fatal: "Claimed NULL waitingTask!" (0x5dca72).  Always aborts.
 * Confidence: high */
void sk_claim_null_waiting_fatal(void)
{
        sk_precond_fatal(0, 0x5dca72);   /* "Claimed NULL waitingTask!" */
}

/* FUN_0040e9fc @ 0x0040e9fc   (est. sk_task_group_store3)
 * Ghidra: void FUN_0040e9fc(undefined8 param_1, undefined8 param_2)
 * Retains a child result and stores it into the group record (result kind
 * 2/3 depending on the low flag).
 * Confidence: low */
void sk_task_group_store3(word_t group, word_t result)
{
        word_t kind;
        int low;

        sk_swift_retain(result);
        kind = 2;
        if (low_flag != 0) {
                kind = 3;
        }
        sk_task_group_store((word_t *)(sk_reg_x11 + 0x38), kind | sk_reg_x10);
        return;
}

/* FUN_0040ea00 @ 0x0040ea00   (est. sk_task_group_store4)
 * Ghidra: void FUN_0040ea00(undefined8 param_1, undefined8 param_2)
 * Same shape as 0040e9fc (alternate result-kind store).
 * Confidence: low */
void sk_task_group_store4(word_t group, word_t result)
{
        word_t kind;
        int low;

        sk_swift_retain(result);
        kind = 2;
        if (low_flag2 != 0) {
                kind = 3;
        }
        sk_task_group_store((word_t *)(sk_reg_x11 + 0x38), kind | sk_reg_x10);
        return;
}

/* FUN_0040ea5c @ 0x0040ea5c   (est. sk_task_resume_trampoline)
 * Ghidra: void FUN_0040ea5c(void)
 * Resume trampoline: loads the run-queue hook at self+8 and invokes it
 * indirectly.  The deferred body jumps through the hook pointer.
 * Confidence: low */
void sk_task_resume_trampoline(void)
{
        word_t hook;

        hook = *(word_t *)(sk_reg_x22 + 8);
        if ((hook == 0) || (hook == 0)) {
                hook = 0;
        }
        (**(void (**)(void))hook)();
        return;
}

/* FUN_0040eac8 @ 0x0040eac8   (est. sk_cont_result_dispatch)
 * Ghidra: void FUN_0040eac8(long param_1, long *param_2)
 * Dispatches a continuation result record (param_2) to its consumer
 * (param_1): for a success/empty record (kind 0) invokes the vtable's +0x38
 * resume hook with a single flag; for kind 2 invokes the +0x10 value hook then
 * the +0x38 hook; for kind 3 retains the value and stores it at param_1+0x10.
 * Confidence: low */
void sk_cont_result_dispatch(long consumer, word_t rec)
{
        word_t *rp = (word_t *)rec;
        word_t kind;
        word_t value;
        word_t hook;
        uint flag;

        kind = *rp;
        if (kind == 0) {
                value = *(word_t *)(consumer + 0x18);
                hook = *(word_t *)(*(long *)(rp[2] + -8) + 0x38);
                flag = 1;
        } else {
                if (kind != 2) {
                        if (kind == 3) {
                                value = rp[1];
                                *(long *)(consumer + 0x10) = value;
                                sk_swift_retain(value);
                                return;
                        }
                        return;
                }
                value = *(word_t *)(consumer + 0x18);
                (**(void (**)(word_t, word_t))(*(long *)(rp[2] + -8) + 0x10))(value, rp[1]);
                hook = *(word_t *)(*(long *)(rp[2] + -8) + 0x38);
                flag = 0;
        }
        (**(void (**)(word_t, uint, int))hook)(value, flag, 1);
        return;
}

/* FUN_0040ebac @ 0x0040ebac   (est. sk_task_group_error)
 * Ghidra: void FUN_0040ebac(long *param_1)
 * Builds a Swift error string "error: ...TaskGroup... detected penalty..." via
 * the error-string helper (FUN_00116bb4), storing the result (or NULL on
 * allocation failure) into param_1.
 * Confidence: low */
void sk_task_group_error(word_t *out)
{
        int rc;
        long buf;

        rc = sk_error_str(0, 0, 0x5dcac1, (word_t)0);
        *out = 0;
        if (-1 < rc) {
                buf = sk_heap_alloc(rc + 1, 0x100004077774924);
                if (buf != 0) {
                        rc = sk_error_str(buf, rc + 1, 0x5dcac1, (word_t)0);
                        if (rc < 0) {
                                sk_free(buf);
                        } else {
                                *out = buf;
                        }
                }
        }
        return;
}

/* FUN_0040ec54 @ 0x0040ec54   (est. sk_task_group_dump)
 * Ghidra: void FUN_0040ec54(long *param_1, ulong *param_2, undefined1 param_3,
 *                           undefined1 param_4)
 * Renders a bitset of task-group child IDs into an ASCII bitmap (each child's
 * 1-bit maps to a byte 0x30/0x31 = '0'/'1'): allocates a 0x48-byte bitmap
 * buffer, fills it with the child-id byte, then walks the set bits (bit-reverse
 * + LZCOUNT) writing param_3/param_4 into the corresponding positions.  Traps
 * (SoftwareBreakpoint 0x40ed8c/0x40ee50) on a set bit beyond capacity.
 * Confidence: low
 * Notes: LZCOUNT/POPCOUNT bit tricks; bitmap filled from constant
 *   lRam00000000005a17f8. */
void sk_task_group_dump(word_t *out, word_t *ids, byte on, byte off)
{
        word_t *bitmap;
        word_t bits;
        word_t rev;
        word_t idx;
        word_t *slot;
        byte flag;

        bits = sk_popcount_range(ids, 0, 0x40);
        if (bits < 0x20) {
                bitmap = (word_t *)sk_calloc(0x48, 0x1000c0077774924);
                *out = (word_t)bitmap;
                long v1 = DAT_005a17f0;
                out[2] = lRam00000000005a17f8;
                out[1] = v1;
                bitmap[1] = 0x3030303030303030 + (on << 0);   /* fill byte = param_3 */
                *bitmap = 0x3030303030303030 + (on << 0);
                bitmap[3] = bitmap[1];
                bitmap[2] = *bitmap;
                bitmap[5] = bitmap[1];
                bitmap[4] = *bitmap;
                bitmap[7] = bitmap[1];
                bitmap[6] = *bitmap;
                *(byte *)(bitmap + 8) = 0;
                bits = *ids;
                while (bits != 0) {
                        rev = bit_reverse64(bits);
                        idx = LZCOUNT(rev >> 0x20 | rev << 0x20) ^ 0x3f;
                        flag = *(byte *)((long)out + 0x17);
                        word_t cap = out[1];
                        if (-1 < (char)flag) {
                                cap = (ulong)flag;
                        }
                        if (cap < idx) {
                                break;   /* trap 0x40ed8c */
                        }
                        slot = (word_t *)*out;
                        if (-1 < (char)flag) {
                                slot = out;
                        }
                        *(byte *)((long)slot + idx) = off;
                        bits = bits - 1 & bits;
                }
                SK189_FATAL(0x40ed8c);
        }
        bitmap = (word_t *)sk_calloc(0x48, 0x1000c0077774924);
        *out = (word_t)bitmap;
        long v2 = DAT_005a17f0;
        out[2] = lRam00000000005a17f8;
        out[1] = v2;
        bitmap[1] = 0x3030303030303030 + (off << 0);
        *bitmap = 0x3030303030303030 + (off << 0);
        bitmap[3] = bitmap[1];
        bitmap[2] = *bitmap;
        bitmap[5] = bitmap[1];
        bitmap[4] = *bitmap;
        bitmap[7] = bitmap[1];
        bitmap[6] = *bitmap;
        *(byte *)(bitmap + 8) = 0;
        if (*ids != 0xffffffffffffffff) {
                bits = ~*ids;
                do {
                        rev = bit_reverse64(bits);
                        idx = LZCOUNT(rev >> 0x20 | rev << 0x20) ^ 0x3f;
                        flag = *(byte *)((long)out + 0x17);
                        word_t cap = out[1];
                        if (-1 < (char)flag) {
                                cap = (ulong)flag;
                        }
                        if (cap < idx) {
                                SK189_FATAL(0x40ee50);
                        }
                        slot = (word_t *)*out;
                        if (-1 < (char)flag) {
                                slot = out;
                        }
                        *(byte *)((long)slot + idx) = on;
                        bits = bits - 1 & bits;
                } while (bits != 0);
        }
        return;
}

/* FUN_0040ee50 @ 0x0040ee50   (est. sk_popcount_range)
 * Ghidra: long FUN_0040ee50(ulong *param_1, uint param_2, ulong param_3)
 * Counts the set bits in a bitset (param_1) over the range starting at bit
 * param_2 with param_3 bits of span, using POPCOUNT per byte with a partial
 * first/last word.  Returns the popcount.
 * Confidence: medium
 * Notes: pure POPCOUNT arithmetic; clamps the trailing span to a word. */
long sk_popcount_range(word_t *bits, uint start, word_t span)
{
        word_t total;
        word_t *p;
        uint tail;
        word_t rem;
        word_t v;
        int c;

        total = 0;
        p = bits;
        if ((word_t)start != 0) {
                tail = 0x40 - start;
                rem = span;
                if (tail <= span) {
                        rem = (ulong)tail;
                }
                p = bits + 1;
                v = 0xffffffffffffffff >> ((ulong)(tail - (int)rem) & 0x3f) &
                    -1 << ((ulong)start & 0x3f) & *bits;
                c = byte_popcount8((char)(v >> 8)) + byte_popcount8((char)v);
                total = byte_popcount8((char)(v >> 0x10)) + byte_popcount8((char)(v >> 0x18)) +
                        byte_popcount8((char)(v >> 0x20)) + byte_popcount8((char)(v >> 0x28)) +
                        byte_popcount8((char)(v >> 0x30)) + byte_popcount8((char)(v >> 0x38)) + c;
                span = span - rem;
        }
        for (; 0x3f < span; span = span - 0x40) {
                v = *p;
                c = byte_popcount8((char)(v >> 8)) + byte_popcount8((char)v);
                total = total + byte_popcount8((char)(v >> 0x10)) + byte_popcount8((char)(v >> 0x18)) +
                        byte_popcount8((char)(v >> 0x20)) + byte_popcount8((char)(v >> 0x28)) +
                        byte_popcount8((char)(v >> 0x30)) + byte_popcount8((char)(v >> 0x38)) + c;
                p = p + 1;
        }
        if (span != 0) {
                v = *p & 0xffffffffffffffff >> (-span & 0x3f);
                c = byte_popcount8((char)(v >> 8)) + byte_popcount8((char)v);
                total = total + byte_popcount8((char)(v >> 0x10)) + byte_popcount8((char)(v >> 0x18)) +
                        byte_popcount8((char)(v >> 0x20)) + byte_popcount8((char)(v >> 0x28)) +
                        byte_popcount8((char)(v >> 0x30)) + byte_popcount8((char)(v >> 0x38)) + c;
        }
        return total;
}

/* FUN_0040eef8 @ 0x0040eef8   (est. sk_task_local_collect)
 * Ghidra: void FUN_0040eef8(undefined8 *param_1, undefined8 param_2, long param_3)
 * Collects the pending task-local values from a task's store (param_3+0x88):
 * allocates an output set (FUN_0040f078), walks the doubly-linked value list
 * from the store's head, copying each live value into the output (via the
 * growable-buffer append FUN_0040f718) and, when a value is a self-contained
 * task-local, destructures it (FUN_0040efe0).  Returns the output set in
 * param_1.
 * Confidence: low */
void sk_task_local_collect(word_t *out, word_t task, long store)
{
        word_t *node;
        word_t v;
        uint kind;
        word_t *slot;
        word_t value;
        word_t hi;

        node = *(word_t **)(store + 0x88);
        if (node != 0) {
                *out = sk_task_local_set_alloc(task, 0, 2);
                slot = &value;
                value = 0;
                hi = 0;
                do {
                        v = *node;
                        kind = (uint)v >> 1 & 3;
                        if (kind != 1) {
                                if (kind == 2) {
                                        node = (word_t *)(v & 0xfffffffffffffff8);
                                        if (node == 0) {
                                                break;
                                        }
                                        v = *node;
                                }
                                node = 0;
                                if ((~(uint)v & 6) != 0) {
                                        node = node;
                                }
                                goto finalize;
                        }
                        sk_tl_buf_insert((word_t)&slot, (word_t *)(node + 1), (word_t *)(node + 1));
                        if ((extraout_x1 & 1) != 0) {
                                sk_task_local_destructure((long)node, task);
                        }
                        node = (word_t *)(*node & 0xfffffffffffffff8);
                } while (node != 0);
                node = 0;
finalize:
                *out = *out & 7 | (word_t)node;
                sk_tl_buf_destroy((word_t)&slot, (word_t *)value);
        }
        return;
}

/* FUN_0040efe0 @ 0x0040efe0   (est. sk_task_local_destructure)
 * Ghidra: void FUN_0040efe0(long param_1, long param_2)
 * Destructures a task-local value node: allocates a fresh task-local value via
 * FUN_0040f0cc, copies the node's payload via the value's copy hook (+0x10 of
 * the element type metadata), and stores the new value into the task's store
 * (+0x88).
 * Confidence: low */
void sk_task_local_destructure(long node, long task)
{
        word_t value;
        word_t node_pad;
        word_t node_pad2;
        long ty;

        value = sk_tl_value_alloc(task, *(word_t *)(node + 8), *(word_t *)(node + 0x10), 0);
        node_pad = (ulong)*(byte *)(*(long *)(*(long *)(value + 0x10) + -8) + 0x50);
        ty = *(long *)(*(long *)(node + 0x10) + -8);
        node_pad2 = (ulong)*(byte *)(ty + 0x50);
        (**(void (**)(word_t, word_t))(ty + 0x10))
                (value + (node_pad + 0x18 & (node_pad ^ 0xffffffffffffffff)),
                 node + (node_pad2 + 0x18 & (node_pad2 ^ 0xffffffffffffffff)));
        *(long *)(task + 0x88) = value;
        return;
}

/* FUN_0040f078 @ 0x0040f078   (est. sk_task_local_set_alloc)
 * Ghidra: void FUN_0040f078(long param_1, ulong param_2, int param_3)
 * Allocates a task-local set header: either a global 8-byte cell (FUN_000101a0)
 * or a record from the continuation block, then stores the {kind<<1 | flags}
 * header word.
 * Confidence: low */
word_t sk_task_local_set_alloc(word_t block, word_t flags, int kind)
{
        word_t *cell;

        if (block == 0) {
                cell = (word_t *)sk_heap_alloc(8, 0xd94f91c1);
        } else {
                cell = (word_t *)sk_cont_set_alloc(block, 8);
        }
        *cell = flags & 0xfffffffffffffff9 | (long)kind << 1;
        return (word_t)cell;
}

/* FUN_0040f0cc @ 0x0040f0cc   (est. sk_tl_value_alloc)
 * Ghidra: void FUN_0040f0cc(undefined8 param_1, ulong param_2, ulong param_3,
 *                           int param_4)
 * Allocates a task-local value object: resolves the value's header/kind from
 * the element metadata (via the *DAT_0068a6d8 dispatch), allocates a record of
 * size (element-storage-pad + value-size) either from the heap or the
 * continuation block, stores the {kind<<1 | flag} header plus the key
 * (param_2) and element metadata (param_3).
 * Confidence: low */
word_t sk_tl_value_alloc(word_t task, word_t key, word_t meta, int flag)
{
        word_t *cell;
        word_t *value;
        word_t size;
        word_t pad;
        long vty;
        word_t v;

        v = meta;
        cell = (word_t *)(*DAT_0068a6d8)(task);
        value = (word_t *)*cell;
        if (extraout_x8 != 0) {
                value = (word_t *)extraout_x9;
        }
        v = *value;
        pad = (ulong)*(byte *)(*(long *)(meta - 8) + 0x50);
        pad = pad + 0x18 & (pad ^ 0xffffffffffffffff);
        vty = *(long *)(*(long *)(meta - 8) + 0x40);
        if (extraout_x8 == 0) {
                value = (word_t *)sk_heap_alloc(pad + vty, 0x2fc667fa);
        } else {
                value = (word_t *)sk_cont_set_alloc(extraout_x8, pad + vty);
        }
        word_t kind = 2;
        if (flag == 0) {
                kind = 0;
        }
        *value = v & 0xfffffffffffffff9 | kind;
        value[1] = key;
        value[2] = meta;
        return (word_t)value;
}

/* FUN_0040f19c @ 0x0040f19c   (est. sk_task_local_value_release)
 * Ghidra: bool FUN_0040f19c(uint *param_1, long param_2)
 * Releases a task-local value: invokes the value's destructor hook (+8 of the
 * element metadata) for value kinds 0/1, then frees the value (from the
 * continuation block if param_2 is non-null, else via sk_free).  Returns
 * whether the value kind was 2 (self-contained task-local).
 * Confidence: low */
bool sk_task_local_value_release(uint *value, long block, ...)
{
        uint kind;
        word_t pad;

        kind = *value >> 1 & 3;
        if (kind < 2) {
                pad = (ulong)*(byte *)(*(long *)(*(long *)(value + 4) + -8) + 0x50);
                (**(void (**)(word_t))(*(long *)(*(long *)(value + 4) + -8) + 8))
                        ((long)value + (pad + 0x18 & (pad ^ 0xffffffffffffffff)));
        }
        if (block == 0) {
                sk_free(value);
        } else {
                sk_cont_record_free(block, (word_t)value);
        }
        return kind == 2;
}

/* FUN_0040f23c @ 0x0040f23c   (est. sk_runq_append)
 * Ghidra: void FUN_0040f23c(long *param_1, undefined8 param_2)
 * Appends a task to a run-queue (param_1 = queue head list): walks the linked
 * list freeing each task-local value (sk_task_local_value_release) until a
 * self-contained task-local is found, or the list is empty.
 * Confidence: low */
void sk_runq_append(word_t *queue, word_t task)
{
        word_t *node;
        word_t next;
        bool done;

        node = (word_t *)*queue;
        *queue = 0;
        do {
                if (node == 0) {
                        return;
                }
                next = *node;
                done = sk_task_local_value_release((uint *)node, task);
                node = (word_t *)(next & 0xfffffffffffffff8);
        } while (done == 0);
        return;
}

/* FUN_0040f39c @ 0x0040f39c   (est. sk_task_local_release_all)
 * Ghidra: void FUN_0040f39c(ulong *param_1, undefined8 param_2)
 * Releases every task-local value in a store: walks the value list, copying
 * live values into a work buffer (FUN_0040f718) and destructuring
 * self-contained task-locals (FUN_0040efe0); stops at the first terminal
 * node.  Then destroys the work buffer.
 * Confidence: low */
void sk_task_local_release_all(word_t *store, word_t task)
{
        word_t *node;
        word_t v;
        word_t *slot;
        word_t value;
        word_t hi;

        slot = &value;
        value = 0;
        hi = 0;
        for (node = (word_t *)*store; node != 0; node = (word_t *)(*node & 0xfffffffffffffff8)) {
                if (((uint)*node >> 2 & 1) == 0) {
                        sk_tl_buf_insert((word_t)&slot, (word_t *)(node + 1), (word_t *)(node + 1));
                        if ((extraout_x1 & 1) != 0) {
                                sk_task_local_destructure((long)node, task);
                        }
                } else if ((~(uint)*node & 6) == 0) {
                        break;
                }
        }
        sk_tl_buf_destroy((word_t)&slot, (word_t *)value);
        return;
}

/* FUN_0040f434 @ 0x0040f434   (est. sk_task_local_set_value)
 * Ghidra: void FUN_0040f434(undefined8 param_1, undefined8 param_2, long param_3)
 * Sets a task-local value: allocates the task-local object via FUN_0040f0cc,
 * invokes the element's initialize-with-key hook (+0x20 of the value's
 * metadata) with (param_2, param_3), and stores the value into the current
 * task's task-local store (+0x88), lazily initializing the store root when
 * the current task is absent.
 * Confidence: low */
void sk_task_local_set_value(word_t key, word_t value, long meta)
{
        word_t task;
        word_t *store;
        word_t *store_root;
        word_t obj;
        word_t pad;
        word_t has_wait;

        task = sk_swift_current_task();
        if (task == 0) {
                store = (word_t *)(*DAT_0068a6d8)();
                store_root = (word_t *)*store;
                if (store_root == 0) {
                        store_root = (word_t *)sk_heap_alloc(8, 0x2004093837f09);
                        *store_root = 0;
                        *store = (word_t)store_root;
                }
                task = 0;
        } else {
                store = (word_t *)(task + 0x88);
        }
        has_wait = sk_task_has_waiters();
        obj = sk_tl_value_alloc(task, key, meta, has_wait & 1);
        pad = (ulong)*(byte *)(*(long *)(*(long *)(obj + 0x10) + -8) + 0x50);
        (**(void (**)(word_t, word_t, word_t))(*(long *)(meta + -8) + 0x20))
                (obj + (pad + 0x18 & (pad ^ 0xffffffffffffffff)), value, meta);
        *store = obj;
        return;
}

/* FUN_0040f4c8 @ 0x0040f4c8   (est. sk_task_local_get_value)
 * Ghidra: long FUN_0040f4c8(ulong param_1)
 * Looks up a task-local value by key: resolves the current task's store
 * (+0x88, or the global root), walks the value list looking for a non-live
 * value whose key (at +8) equals param_1, and returns a pointer to its
 * element payload.  Returns 0 when not found.
 * Confidence: low */
long sk_task_local_get_value(word_t key)
{
        word_t task;
        word_t *store;
        word_t *node;
        word_t v;

        task = sk_swift_current_task();
        if (task == 0) {
                store = (word_t *)(*DAT_0068a6d8)();
                node = (word_t *)*store;
                if (node == 0) {
                        return 0;
                }
        } else {
                store = (word_t *)(task + 0x88);
        }
        node = (word_t *)*store;
        if (node != 0) {
                do {
                        while (1) {
                                v = *node;
                                if (((uint)v >> 2 & 1) != 0) {
                                        break;
                                }
                                if (node[1] == key) {
                                        v = (ulong)*(byte *)(*(long *)(node[2] - 8) + 0x50);
                                        return (long)node + (v + 0x18 & (v ^ 0xffffffffffffffff));
                                }
                                node = (word_t *)(v & 0xfffffffffffffff8);
                                if (node == 0) {
                                        return 0;
                                }
                        }
                        node = (word_t *)(v & 0xfffffffffffffff8);
                } while ((~(uint)v & 6) != 0 && node != 0);
        }
        return 0;
}

/* FUN_0040f524 @ 0x0040f524   (est. sk_task_local_clear)
 * Ghidra: void FUN_0040f524(void)
 * Clears the current task's task-local store: unlinks and releases the head
 * value, and if the store becomes empty, frees the store root.
 * Confidence: low */
void sk_task_local_clear(void)
{
        word_t task;
        word_t *store;
        word_t *node;
        word_t *root;

        task = sk_swift_current_task();
        if (task != 0) {
                *(ulong *)(task + 0x88) = **(ulong **)(task + 0x88) & 0xfffffffffffffff8;
                sk_task_local_value_release((uint *)0, 0);
                return;
        }
        store = (word_t *)(*DAT_0068a6d8)();
        root = (word_t *)*store;
        if (root != 0) {
                node = (word_t *)*root;
                *root = *node & 0xfffffffffffffff8;
                sk_task_local_value_release((uint *)node, 0);
                if (*root == 0) {
                        *store = 0;
                        sk_free(root);
                        return;
                }
        }
        return;
}

/* FUN_0040f5c0 @ 0x0040f5c0   (est. sk_task_local_release_all2)
 * Ghidra: void FUN_0040f5c0(undefined8 param_1)
 * Releases all task-local values of the current task (via FUN_0040f39c on its
 * store).
 * Confidence: low */
void sk_task_local_release_all2(word_t task)
{
        word_t tok;
        word_t *store;
        word_t v;

        tok = sk_swift_current_task();
        store = (word_t *)(*DAT_0068a6d8)(tok);
        v = *store;
        if (extraout_x8 != 0) {
                v = extraout_x9;
        }
        if (v != 0) {
                sk_task_local_release_all((word_t *)v, task);
                return;
        }
        return;
}

/* FUN_0040f620 @ 0x0040f620   (est. sk_task_local_error)
 * Ghidra: void FUN_0040f620(long *param_1)
 * Builds a Swift error string "error: task local detected illegal..." via the
 * error-string helper, storing the result (or NULL) into param_1.
 * Confidence: low */
void sk_task_local_error(word_t *out)
{
        int rc;
        long buf;

        rc = sk_error_str(0, 0, 0x5dcb89, (word_t)0);
        *out = 0;
        if (-1 < rc) {
                buf = sk_heap_alloc(rc + 1, 0x100004077774924);
                if (buf != 0) {
                        rc = sk_error_str(buf, rc + 1, 0x5dcb89, (word_t)0);
                        if (rc < 0) {
                                sk_free(buf);
                        } else {
                                *out = buf;
                        }
                }
        }
        return;
}

/* FUN_0040f6c8 @ 0x0040f6c8   (est. sk_tl_buf_destroy)
 * Ghidra: void FUN_0040f6c8(undefined8 param_1, undefined8 *param_2)
 * Destroys a task-local work tree recursively: frees both children then the
 * node itself (0x28 bytes, tag 7).
 * Confidence: low */
void sk_tl_buf_destroy(word_t buf, word_t *node)
{
        if (node != 0) {
                sk_tl_buf_destroy(buf, (word_t *)*node);
                sk_tl_buf_destroy(buf, (word_t *)node[1]);
                sk_free(node, 0x28, 7);
                return;
        }
        return;
}

/* FUN_0040f718 @ 0x0040f718   (est. sk_tl_buf_insert)
 * Ghidra: undefined1 [16] FUN_0040f718(long param_1, ulong *param_2, long *param_3)
 * Inserts a value into a task-local RB-tree keyed by the value's tag: walks
 * the tree to find the insertion point (comparing +0x20 keys), allocates a
 * 0x28-byte node, links it via FUN_0040f7d8 and rebalances (FUN_0040f82c).
 * Returns {node, inserted} as a 16-byte pair.
 * Confidence: low */
word_t sk_tl_buf_insert(word_t tree, word_t *key, word_t *node)
{
        word_t *root;
        word_t *p;
        word_t *q;
        word_t inserted;
        word_t *new;

        root = (word_t *)(tree + 8);
        q = root;
        if ((word_t *)*root != 0) {
                p = (word_t *)*root;
                do {
                        while ((word_t)p[4] <= *key) {
                                if (*key <= (word_t)p[4]) {
                                        inserted = 0;
                                        goto found;
                                }
                                p = (word_t *)p[1];
                                if ((word_t *)p[1] == 0) {
                                        q = p + 1;
                                        goto link;
                                }
                        }
                        p = (word_t *)*p;
                        q = p;
                } while ((word_t *)*p != 0);
        }
link:
        p = (word_t *)sk_swift_alloc(0x28, 7);
        p[4] = *node;
        sk_tl_buf_link((word_t *)tree, (word_t)q, (word_t *)p, (word_t *)p);
        inserted = 1;
        p = p;
found:
        return inserted << 8 | (word_t)p;
}

/* FUN_0040f7d8 @ 0x0040f7d8   (est. sk_tl_buf_link)
 * Ghidra: void FUN_0040f7d8(long *param_1, undefined8 param_2, undefined8 *param_3,
 *                           undefined8 *param_4)
 * Links a new node into the task-local RB-tree: zeroes the node's children,
 * sets its parent, links it under the parent (or as root), then rebalances
 * (FUN_0040f82c) and bumps the node count.
 * Confidence: low */
void sk_tl_buf_link(word_t *tree, word_t parent, word_t *where, word_t *node)
{
        *node = 0;
        node[1] = 0;
        node[2] = parent;
        *where = (word_t)node;
        if (*(long *)*tree != 0) {
                *tree = *(long *)*tree;
        }
        sk_tl_rb_rebalance((word_t *)tree[1], (word_t *)node);
        tree[2] = tree[2] + 1;
        return;
}

/* FUN_0040f82c @ 0x0040f82c   (est. sk_tl_rb_rebalance)
 * Ghidra: void FUN_0040f82c(long *param_1, long *param_2)
 * RB-tree insert-fixup (rebalance) for the task-local tree.  Standard
 * rotations/recoloring restoring red-black invariants after insertion.
 * Confidence: high
 * Notes: verified 2026-08-12; all three rotations (left/right/double) and
 *   recoloring steps match the decompile; goto labels recolor/link_right
 *   correspond to decompile LAB_0040f950/LAB_0040f93c. */
void sk_tl_rb_rebalance(word_t *tree, word_t *node)
{
        word_t *parent;
        word_t *grand;
        word_t *uncle;
        word_t *sib;
        word_t *child;
        long tmp;

        *(bool *)(node + 3) = node == tree;
        if (node != tree) {
                do {
                        parent = (word_t *)node[2];
                        if ((*(byte *)(parent + 3) & 1) != 0) {
                                return;
                        }
                        grand = (word_t *)parent[2];
                        uncle = (word_t *)*grand;
                        if (parent == uncle) {
                                tmp = grand[1];
                                if ((tmp == 0) || ((*(byte *)(tmp + 0x18) & 1) != 0)) {
                                        if (node == (word_t *)*parent) {
                                                goto recolor;
                                        }
                                        sib = (word_t *)parent[1];
                                        tmp = *sib;
                                        parent[1] = tmp;
                                        if (tmp == 0) {
                                                sib[2] = (word_t)grand;
                                                goto link_right;
                                        }
                                        *(word_t **)(tmp + 0x10) = parent;
                                        grand = (word_t *)parent[2];
                                        uncle = (word_t *)*grand;
                                        sib[2] = (word_t)grand;
                                        if (parent == uncle) {
                                                goto link_right;
                                        }
                                        grand[1] = (word_t)sib;
                                }
                                *(byte *)(parent + 3) = 1;
                                *(bool *)(grand + 3) = grand == tree;
                                *(byte *)(tmp + 0x18) = 1;
                        } else {
                                if ((uncle == 0) || ((*(byte *)(uncle + 3) & 1) != 0)) {
                                        uncle = (word_t *)*parent;
                                        if (node == uncle) {
                                                tmp = uncle[1];
                                                *parent = tmp;
                                                if (tmp != 0) {
                                                        *(word_t **)(tmp + 0x10) = parent;
                                                        grand = (word_t *)parent[2];
                                                }
                                                uncle[2] = (word_t)grand;
                                                if (parent == (word_t *)*grand) {
                                                        *grand = (word_t)uncle;
                                                } else {
                                                        grand[1] = (word_t)uncle;
                                                }
                                                uncle[1] = (word_t)parent;
                                                parent[2] = (word_t)uncle;
                                                grand = (word_t *)uncle[2];
                                                parent = uncle;
                                        }
                                        *(byte *)(parent + 3) = 1;
                                        *(byte *)(grand + 3) = 0;
                                        parent = (word_t *)grand[1];
                                        tmp = *parent;
                                        grand[1] = tmp;
                                        if (tmp != 0) {
                                                *(word_t **)(tmp + 0x10) = grand;
                                        }
                                        sib = (word_t *)grand[2];
                                        parent[2] = (word_t)sib;
                                        if (grand == (word_t *)*sib) {
                                                *sib = (word_t)parent;
                                        } else {
                                                sib[1] = (word_t)parent;
                                        }
                                        *parent = (word_t)grand;
                                        grand[2] = (word_t)parent;
                                        return;
                                }
                                *(byte *)(parent + 3) = 1;
                                *(bool *)(grand + 3) = grand == tree;
                                *(byte *)(uncle + 3) = 1;
                        }
                        node = grand;
                } while (grand != tree);
        }
        return;
recolor:
        *(byte *)(node + 3) = 1;
        *(byte *)(grand + 3) = 0;
        tmp = uncle[1];
        *grand = tmp;
        if (tmp != 0) {
                *(word_t **)(tmp + 0x10) = grand;
        }
        sib = (word_t *)grand[2];
        uncle[2] = (word_t)sib;
        if (grand == (word_t *)*sib) {
                *sib = (word_t)uncle;
        } else {
                sib[1] = (word_t)uncle;
        }
        uncle[1] = (word_t)grand;
        grand[2] = (word_t)uncle;
        return;
link_right:
        *grand = (word_t)sib;
        goto recolor_common;
recolor_common:
        *sib = (word_t)parent;
        parent[2] = (word_t)sib;
        grand = (word_t *)sib[2];
        uncle = (word_t *)*grand;
        parent = sib;
        goto recolor;
}

/* FUN_0040f9f4 @ 0x0040f9f4   (est. sk_actor_executor_enqueue)
 * Ghidra: void FUN_0040f9f4(long param_1, ulong param_2)
 * Enqueues a job onto an actor executor: requires both a job (param_1) and an
 * executor (param_2); resolves the executor token (FUN_003a25b8) and enqueues
 * via FUN_003d5338.  Panics "Incorrect actor executor assumption" (0x5dd036)
 * if either is null.
 * Confidence: high */
void sk_actor_executor_enqueue(word_t job, word_t executor)
{
        word_t token;

        token = sk_executor_enq();
        if ((job != 0) && (executor != 0)) {
                sk_executor_enq2(job, token, executor & 0xfffffffffffffff8);
                return;
        }
        sk_swift_hotpath(token, 1);
        sk_precond_fatal(0, 0x5dd036);   /* "Incorrect actor executor assumption" */
}

/* FUN_0040fa5c @ 0x0040fa5c   (est. sk_actor_executor_enqueue_check)
 * Ghidra: undefined8 FUN_0040fa5c(long param_1, ulong param_2)
 * Enqueues a job onto an actor executor, returning 0xff if either the job or
 * executor is null (precondition check), else forwarding to FUN_003d5370.
 * Confidence: high */
word_t sk_actor_executor_enqueue_check(word_t job, word_t executor)
{
        word_t token;

        if ((job != 0) && (executor != 0)) {
                token = sk_executor_enq();
                token = sk_executor_enq3(job, token, executor & 0xfffffffffffffff8);
                return token;
        }
        return 0xff;
}

/* FUN_0040faac @ 0x0040faac   (est. sk_actor_executor_dequeue)
 * Ghidra: undefined8 FUN_0040faac(long param_1, ulong param_2)
 * Dequeues a job from an actor executor, returning 0 if either the job or
 * executor is null, else forwarding to FUN_003d5308.
 * Confidence: high */
word_t sk_actor_executor_dequeue(word_t job, word_t executor)
{
        word_t token;

        if ((job != 0) && (executor != 0)) {
                token = sk_executor_enq();
                token = sk_executor_deq(job, token, executor & 0xfffffffffffffff8);
                return token;
        }
        return 0;
}

/* FUN_0040fafc @ 0x0040fafc   (est. sk_actor_value_retain)
 * Ghidra: ulong FUN_0040fafc(ulong param_1)
 * Retains an actor-stored value (masked to 52 bits) and returns it.
 * Confidence: high */
word_t sk_actor_value_retain(word_t value)
{
        sk_swift_retain(value & 0xfffffffffffffff);
        return value;
}

/* FUN_0040fb28 @ 0x0040fb28   (est. sk_actor_value_set)
 * Ghidra: void FUN_0040fb28(ulong param_1)
 * Releases the previous actor-stored value and stores the new one (self via
 * sk_reg_x20).
 * Confidence: high */
void sk_actor_value_set(word_t value)
{
        sk_swift_release(*(word_t *)sk_reg_x20 & 0xfffffffffffffff);
        *(word_t *)sk_reg_x20 = value;
        return;
}

/* FUN_0040fb58 @ 0x0040fb58   (est. sk_actor_value_retain_param3)
 * Ghidra: void FUN_0040fb58(undefined8 param_1, undefined8 param_2,
 *                           undefined8 param_3)
 * Retains param_3 (an actor-stored value).
 * Confidence: high */
void sk_actor_value_retain_param3(word_t a, word_t b, word_t value)
{
        sk_swift_retain(value);
        return;
}

/* FUN_0040fb84 @ 0x0040fb84   (est. sk_actor_box_write)
 * Ghidra: void FUN_0040fb84(undefined8 param_1, undefined1 param_2)
 * Writes an actor boxed value: releases the previous value at self+0x10,
 * stores the new value and its tag at self+0x18 (self via sk_reg_x20).
 * Confidence: high */
void sk_actor_box_write(word_t value, byte tag)
{
        sk_swift_release(*(word_t *)(sk_reg_x20 + 0x10));
        *(word_t *)(sk_reg_x20 + 0x10) = value;
        *(byte *)(sk_reg_x20 + 0x18) = tag;
        return;
}

/* FUN_0040fbc0 @ 0x0040fbc0   (est. sk_actor_noop)
 * Ghidra: void FUN_0040fbc0(void)
 * No-op witness (empty).
 * Confidence: medium */
void sk_actor_noop(void)
{
        return;
}

/* FUN_0040fbc8 @ 0x0040fbc8   (est. sk_task_suspend_switch)
 * Ghidra: uint FUN_0040fbc8(undefined8 param_1, long param_2, undefined8 param_3,
 *                           uint param_4, undefined8 param_5, long param_6,
 *                           undefined8 param_7, uint param_8)
 * Task-suspend/switch decision: checks the task-switch predicate
 * (FUN_0041001c); when both the current and pending contexts are present,
 * runs the full switch (FUN_00350518 + FUN_004110ec).  Otherwise performs the
 * context swap (FUN_00100efc + FUN_00411624).  Returns whether the switch
 * completed.
 * Confidence: low */
uint sk_task_suspend_switch(word_t a, long b, word_t c, uint d, word_t e,
                            long f, word_t g, uint h)
{
        word_t sw;
        uint result;

        sw = sk_task_switch1(a, e);
        if ((sw & 1) != 0) {
                if (b == 0) {
                        if (f == 0) {
                                goto do_swap;
                        }
                } else if (f != 0) {
                        sk_actor_leave();
                        sw = sk_task_switch3();
                        if ((sw & 1) != 0) {
                                goto do_swap;
                        }
                }
        }
        result = 0;
        return result & 1;
do_swap:
        sk_task_switch8();
        sw = sk_task_switch4();
        sw = sw & (d ^ h ^ 1);
        return sw & 1;
}

/* FUN_0040fc50 @ 0x0040fc50   (est. sk_task_executor_switch)
 * Ghidra: void FUN_0040fc50(void)
 * Switches the current task onto its executor: saves the context, runs the
 * executor-enter and scheduler hooks (with or without the "isMain" flag from
 * sk_reg_x22), then restores and re-arms.
 * Confidence: low */
void sk_task_executor_switch(void)
{
        uint w4;

        sk_ctx_pop();
        sk_task_switch2();
        if (sk_reg_x22 == 0) {
                sk_sched_enter(0);
        } else {
                sk_sched_enter(1);
                sk_actor_enter();
                sk_task_switch6();
        }
        sk_sched_enter2();
        sk_task_switch7();
        sk_sched_enter(sk_reg_w4 & 1);
        return;
}

/* FUN_0040fcb4 @ 0x0040fcb4   (est. sk_task_switch_enter)
 * Ghidra: void FUN_0040fcb4(void)
 * Task-switch entry: pops the context frame, runs the switch prologue, swaps
 * the context (72-byte frame), switches the executor and re-arms.
 * Confidence: low */
void sk_task_switch_enter(void)
{
        byte frame[72];

        sk_ctx_pop();
        sk_task_switch5();
        sk_ctx_swap(frame);
        sk_task_executor_switch();
        sk_ctx_push();
        return;
}

/* =====================================================================
 * Hash-set registry (continuation set) + block allocator (completing the
 * region's core data structures).
 * ===================================================================== */

/* FUN_0040b724 @ 0x0040b724   (est. sk_registry_add)
 * Ghidra: long * FUN_0040b724(long *param_1, long *param_2, long *param_3)
 * Inserts a key into a Swift-style hash set (the continuation registry).
 * Computes the bucket via sk_swift_hash8, scans the collision chain for a
 * duplicate {hash,key}; if none, allocates a 0x18-byte node, and when the
 * load factor is exceeded grows the table via FUN_0037d700 and re-inserts.
 * Returns the existing node on duplicate, else the new node.  Traps
 * (SoftwareBreakpoint 0x40b96c) on a full table.
 * Confidence: low
 * Notes: table layout {bucket_base,+8 count,+0x10 capacity,+0x18 free_head,
 *   +0x20 size,+0x28 load-factor(float)}; node {next,+8 hash,+0x10 key};
 *   FUN_00112098 hash; FUN_0037d700 resize; FUN_00111890 node alloc. */
word_t *sk_registry_add(word_t *set, word_t *key, word_t *arg3)
{
        word_t hash;
        word_t nbuckets;
        word_t mask;
        word_t idx;
        word_t size;
        word_t rem;
        word_t *chain;
        word_t *node;
        word_t keyv;
        word_t newcap;
        long bucket;

        keyv = *key;
        hash = sk_swift_hash8(&keyv);
        nbuckets = set[1];
        if (nbuckets != 0) {
                mask = nbuckets - 1;
                if ((nbuckets & mask) == 0) {
                        idx = mask & hash;
                } else {
                        idx = hash;
                        if (nbuckets <= hash) {
                                rem = 0;
                                if (nbuckets != 0) {
                                        rem = hash / nbuckets;
                                }
                                idx = hash - rem * nbuckets;
                        }
                }
                if ((word_t)set[2] <= idx) {
                        SK189_FATAL(0x40b96c);
                }
                chain = *(word_t **)(*set + idx * 8);
                if (chain != 0) {
                        for (chain = (word_t *)*chain; chain != 0; chain = (word_t *)*chain) {
                                rem = chain[1];
                                if (rem == hash) {
                                        if (chain[2] == keyv) {
                                                return chain;
                                        }
                                } else {
                                        if ((nbuckets & mask) == 0) {
                                                rem = rem & mask;
                                        } else if (nbuckets <= rem) {
                                                size = 0;
                                                if (nbuckets != 0) {
                                                        size = rem / nbuckets;
                                                }
                                                rem = rem - size * nbuckets;
                                        }
                                        if (rem != idx) {
                                                break;
                                        }
                                }
                        }
                }
        }
        node = (word_t *)sk_calloc(0x18, 0x1020c0014030ade);
        *node = 0;
        node[1] = hash;
        node[2] = *arg3;
        if ((nbuckets == 0) ||
            (*(float *)(set + 5) * (float)nbuckets < (float)(set[4] + 1))) {
                newcap = 1;
                if (2 < nbuckets) {
                        newcap = (ulong)((nbuckets & nbuckets - 1) != 0);
                }
                newcap = newcap | nbuckets << 1;
                size = (ulong)((float)(set[4] + 1) / *(float *)(set + 5));
                if (newcap <= size) {
                        newcap = size;
                }
                sk_hashtable_resize(set, newcap);
                nbuckets = set[1];
                if ((nbuckets & nbuckets - 1) == 0) {
                        idx = nbuckets - 1 & hash;
                } else {
                        idx = hash;
                        if (nbuckets <= hash) {
                                newcap = 0;
                                if (nbuckets != 0) {
                                        newcap = hash / nbuckets;
                                }
                                idx = hash - newcap * nbuckets;
                        }
                }
        }
        size = set[2];
        if (idx < size) {
                bucket = *set;
                chain = *(word_t **)(bucket + idx * 8);
                if (chain == 0) {
                        chain = set + 3;
                        *node = *chain;
                        *chain = (word_t)node;
                        *(word_t **)(bucket + idx * 8) = chain;
                        if (*node != 0) {
                                rem = *(ulong *)(*node + 8);
                                if ((nbuckets & nbuckets - 1) == 0) {
                                        rem = rem & nbuckets - 1;
                                } else if (nbuckets <= rem) {
                                        size = 0;
                                        if (nbuckets != 0) {
                                                size = rem / nbuckets;
                                        }
                                        rem = rem - size * nbuckets;
                                }
                                if (size <= rem) {
                                        SK189_FATAL(0x40b96c);
                                }
                                *(word_t **)(bucket + rem * 8) = node;
                        }
                } else {
                        *node = *chain;
                        *chain = (word_t)node;
                }
                set[4] = set[4] + 1;
                return node;
        }
        SK189_FATAL(0x40b96c);
}

/* FUN_0040bb98 @ 0x0040bb98   (est. sk_cont_block_alloc)
 * Ghidra: long FUN_0040bb98(undefined8 *param_1, long param_2)
 * Allocates a block of size param_2 (16-aligned) from a continuation block
 * allocator: uses the current head's free space if it fits, else recycles
 * freed allocations (FUN_0040afb8) and, when exhausted, allocates a fresh
 * 0x1000-byte page via FUN_000101a0 (minimum capacity 0x3d8) and links it.
 * Returns a pointer to the new allocation (16 bytes past the record header).
 * Confidence: low
 * Notes: block header {+0x10 size,+0x14 used,+0x20 free-space; page header
 *   {next,+8 self,size at +2,used at +0x14}}. */
long sk_cont_block_alloc(word_t *block, long size)
{
        word_t need;
        word_t *page;
        word_t *head;
        word_t free_space;
        word_t *p;
        word_t used;
        int once;
        long newpage;

        need = size + 0xf & 0xfffffffffffffff0;
        page = (word_t *)*block;
        head = block;
        if (page != 0) {
                head = page;
        }
        head = (word_t *)head[1];
        used = need;
        if (head != 0) {
                free_space = (ulong)*(uint *)((long)head + 0x14);
                p = head;
                if (need + 0x10 + free_space <= (ulong)*(uint *)(head + 2)) {
                        goto alloc_from_page;
                }
                p = (word_t *)head[1];
                if (p != 0) {
                        free_space = (ulong)*(uint *)((long)p + 0x14);
                        if (need + 0x10 + free_space <= (ulong)*(uint *)(p + 2)) {
                                goto alloc_from_page;
                        }
                        free_space = sk_cont_free_nodes((long)block, 0);
                        if (need <= free_space) {
                                used = free_space;
                        }
                }
        }
        if (DAT_006adfb0 == 0) {
                once = sk_runtime_once2();
                DAT_006adfb0 = 1;
                if (once == 0) {
                        DAT_006adfb0 = 2;
                }
        }
        if (DAT_006adfb0 != 1) {
                newpage = sk_heap_alloc(size, 0xc07e9746);
                return newpage;
        }
        used = used + 0x10;
        if (used < 0x3d9) {
                used = 0x3d8;
        }
        p = (word_t *)sk_heap_alloc(used + 0x20, 0xcc82f7e);
        *p = 0x6adfa8;
        p[1] = 0;
        *(int *)(p + 2) = (int)used;
        *(uint *)((long)p + 0x14) = 0;
        page = block;
        if (head != 0) {
                page = head;
        }
        page[1] = (word_t)p;
        *(int *)(block + 2) = *(int *)(block + 2) + 2;
        page = (word_t *)*block;
        free_space = (ulong)*(uint *)((long)p + 0x14);
alloc_from_page:
        head = (word_t *)((long)p + free_space + 0x20);
        *head = (word_t)page;
        *(word_t **)((long)p + free_space + 0x28) = p;
        *(int *)((long)p + 0x14) = (int)need + (int)free_space + 0x10;
        *block = (word_t)head;
        return (long)p + free_space + 0x30;
}

/* ---- Task-local root / init helpers used by the region. ---- */

/* FUN_0040cfbc-init equivalent: task-local store root flag test-and-set. */
word_t sk_task_local_root_flag(void) { return sk_status_high_set(0x6c0c80); }

/* Task-local store root accessor (root at +0x10 list head). */
long sk_task_local_root(word_t task) { return sk_ptr_offset_8(task); }

/* Task-local store initializer hook. */
void sk_task_local_init(void) { return; }
