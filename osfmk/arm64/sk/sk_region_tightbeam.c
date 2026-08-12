/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel,
 * arm64e, image base 0) — the cL4 microkernel (GL1), "cL4 (679.100.61)".
 * Ground truth: Ghidra FUN_ names + addresses in program cl4_kernel.raw.
 * This region (0x380000-0x400000) is the IPC / notification / message
 * register subsystem. All names are estimates unless string-matched. */

#include <stdint.h>
#include <stddef.h>
#include <string.h>

/* cL4 returns many values as a 16-byte pair (two 64-bit words in x0/x1).
 * Model it as a struct so callers can carry both halves. */
typedef struct { unsigned long lo, hi; } cL4_w16_t;

/* ------------------------------------------------------------------ *
 * Out-of-range cL4 helper declarations (declared extern with a one-line
 * note; their bodies are reconstructed by the range worker that owns them).
 * ------------------------------------------------------------------ */

/* FUN_0037aaac @ 0x37aaac — classify the message word in *param_1 (an
 * IPC message/notification state word): returns the message kind
 * (0=empty, 1=..., 2=waiting, 3=with-registers, 4=...); carries state via
 * the low 3 bits. Also takes an options byte (param_2&0xff) and a flag
 * (param_2&0x100). */
extern unsigned int cL4_msg_classify(unsigned long *word, unsigned long opts);
/* FUN_0037a48c @ 0x37a48c — acquire a reference / lock on the object
 * whose handle is in x0 (the thread or object pointer _DAT_006c0380). */
extern void cL4_ref_acquire(unsigned long obj);
/* FUN_0037aed8 @ 0x37aed8 — release a reference / lock previously taken by
 * cL4_ref_acquire. */
extern void cL4_ref_release(unsigned long obj);
/* FUN_0037a978 @ 0x37a978 — release (LO release / unlock) an object. */
extern void cL4_release(unsigned long obj);
/* FUN_0037a7f8 @ 0x37a7f8 — allocate a fresh message/notification object;
 * returns its virtual address. */
extern unsigned long cL4_obj_alloc(void);
/* FUN_0037b054 @ 0x37b054 — enqueue / publish a message object onto a
 * linked list whose head is *list; *list is updated. */
extern void cL4_msg_list_push(unsigned long *list);
/* FUN_0037b350 @ 0x37b350 — free / destroy a message object allocated by
 * cL4_obj_alloc. */
extern void cL4_msg_free(void *msg);
/* FUN_0035bd48 @ 0x35bd48 — resolve the message/notification register block
 * (MR) for the thread at *tcb - 8; returns a pointer to the MR word. */
extern unsigned int *cL4_mr_block(long tcb);
/* FUN_0037f7a4 @ 0x37f7a4 — fetch the endpoint/notification object pointer
 * for an IPC object whose MR word is at puVar6 (kind 0x10). */
extern long cL4_obj_kind16(long *mr);
/* FUN_00379480 @ 0x379480 — fetch endpoint for kind 0x10. */
extern long cL4_ipc_obj_kind10(unsigned int *cap);
/* Endpoint dispatch call (indirect through the endpoint object). */
extern cL4_w16_t cL4_ipc_obj_dispatch(long ep, unsigned long tcb, unsigned long *q, long zero);
/* FUN_00376634 @ 0x376634 — advance the per-thread MR state. */
extern void cL4_mr_state2(unsigned long tcb);
/* FUN_0037bcac @ 0x37bcac — fetch the endpoint object pointer for an IPC
 * object of kind 0x11. */
extern long cL4_obj_kind17(long *mr);
/* FUN_0037b3b8 @ 0x37b3b8 — fetch the endpoint object pointer for an IPC
 * object of kind 0x12. */
extern long cL4_obj_kind18(long *mr);
/* FUN_00378374 @ 0x378374 — copy/collect the incoming message registers from
 * the sender into the receiver's message object; returns a 16-byte value
 * {status, something}. */
extern cL4_w16_t cL4_msg_collect(long tcb);
/* FUN_00378a30 @ 0x378a30 — handle a message-register transfer / advance the
 * IPC handshake between two threads (tcb, kind, data0, data1). */
extern void cL4_msg_handshake(long tcb, unsigned int kind, unsigned long d0, unsigned long d1);
/* FUN_00111890 @ 0x111890 — allocate `size` bytes from the cL4 allocator
 * with magic/tag 0x80c4018a671a6; returns pointer. */
extern void *cL4_alloc(unsigned long size, unsigned long tag);
/* thunk_FUN_00012568 @ 0x12568 — cL4 deallocation/free with size tag. */
extern void cL4_free(void *p, unsigned long size);
/* FUN_0037ae38 @ 0x37ae38 — helper consulted by cL4_msg_classify. */
extern unsigned long cL4_msg_state_advance(unsigned long *word, unsigned int opts);

/* Global: the current thread / TCB pointer (_DAT_006c0380). */
extern unsigned long cL4_current_thread;  /* _DAT_006c0380 */

/* In-range function prototypes (bodies below). */
/* In-range function prototypes (bodies below). */
    cL4_w16_t cL4_msg_result(unsigned long *msg_word, int kind);
    cL4_w16_t cL4_msg_send_finalize(unsigned long *msg_word, void *obj, unsigned int opts);
    void cL4_msg_finish(unsigned long *msg_word, void *obj, unsigned long d0, unsigned long d1, unsigned long extra);
    void cL4_msg_wake(unsigned long tcb, void *obj, unsigned long d0, unsigned long d1);
    long cL4_mr_copy_slot8(long dst, long src, long desc);
    long cL4_mr_copy_slot10(long dst, long src, long desc);
    long cL4_mr_copy_slot18(long dst, long src, long desc);
    long cL4_mr_copy_slot20(long dst, long src, long desc);
    long cL4_mr_copy_slot28(long dst, long src, long desc);
    void cL4_mr_copy6(unsigned long reg, unsigned long acc0, unsigned long n, unsigned long opts, unsigned long *src5, unsigned long *src6);
    void cL4_mr_copy8(unsigned long reg, unsigned long acc0, unsigned long n, unsigned long opts, unsigned long *src5, unsigned long *src6, unsigned long a7, unsigned long a8);
/* FUN_003a3944 — IPC object dispatch-table fetch. */
extern unsigned long cL4_ipc_obj_getf(unsigned long a, uint32_t tag, ...);
/* FUN_00363718 @ 0x363718 — publish a raw IPC object descriptor. */
/* FUN_003a3430/003a3460 — object field get/set. */
/* FUN_0036c430 @ 0x36c430 — object hardware-init hook. */
/* FUN_003658e8 @ 0x3658e8 — next cap in a chain. */
extern unsigned int *cL4_cap_next(unsigned int *cap);
/* FUN_0038ef30 @ 0x38ef30 — final cap-chain dispatch. */
extern unsigned long cL4_cap_final(unsigned int *cap);
/* FUN_0036f460 @ 0x36f460 — capability type/operation gate. */
/* FUN_0035ef4c @ 0x35ef4c — capability slot index. */
/* FUN_0036fb10 @ 0x36fb10 — capability owner object. */
/* FUN_0037cb08 @ 0x37cb08 — release a capability context block. */
/* FUN_004b89f8 @ 0x4b89f8 — noreturn allocation-size panic. */
extern void cL4_panic_big(void) __attribute__((noreturn));
/* FUN_0036f460 @ 0x36f460 — capability type/operation gate. */
extern unsigned long cL4_type_gate(void);
/* FUN_0035ef4c @ 0x35ef4c — capability slot index. */
extern int cL4_cap_slot_index(unsigned int *cap);
/* FUN_0036fb10 @ 0x36fb10 — capability owner object. */
extern long cL4_cap_owner(unsigned int *cap);
/* FUN_0037cb08 @ 0x37cb08 — release a capability context block. */
extern void cL4_cap_release_ctx(long *ctx);
/* FUN_00363718 @ 0x363718 — publish a raw IPC object descriptor. */
extern void cL4_ipc_obj_publish(long *d, long a, long b);
/* FUN_0001a1c8 @ 0x1a1c8 — per-CPU init for the table. */
extern void FUN_0001a1c8(void);
/* FUN_0036c430 @ 0x36c430 — object hardware-init hook. */
extern void cL4_obj_hw_init(void);
/* FUN_004ba214 — resolve a raw descriptor. */
/* FUN_0001a1c8 @ 0x1a1c8 — per-CPU init for the table. */

/* FUN_003802a4 @ 0x003802a4   (est. cL4_msg_result)
 * Ghidra: undefined1[16] FUN_003802a4(long param_1, int param_2)
 * Builds the caller-visible result word for an IPC operation: the 16-byte
 * return is { mr_word(hi-word set per kind), kind-dependent mask }.
 * kind 1 -> hi=0xff; 2 -> hi=0x3f; 3 -> hi=1; 4 -> hi=0. Falls through to a
 * SoftwareBreakpoint(1) trap on an out-of-range kind (fail-closed).
 * Confidence: medium
 */
cL4_w16_t cL4_msg_result(unsigned long *msg_word, int kind)
{
    cL4_w16_t r;
    unsigned long w = msg_word[1];           /* auVar2._0_8_ = *(param_1+8) */
    r.lo = w;
    switch (kind) {
    case 1: r.hi = 0xff; break;
    case 2: r.hi = 0x3f; break;
    case 3: r.hi = 1;    break;
    case 4: r.hi = 0;    break;
    default:
        __asm__ volatile("brk #1" ::: "memory");   /* SoftwareBreakpoint(1,0x3802f4) */
        r.hi = 0;
    }
    return r;
}

/* FUN_003802f4 @ 0x003802f4   (est. cL4_msg_send_finalize)
 * Ghidra: void FUN_003802f4(long param_1,long param_2,uint param_3)
 * Finalizes a message send/receive transition. Walks the IPC object chain for
 * the current thread, dispatching on the object's kind (0x10/0x11/0x12) to
 * fetch the endpoint, and either delivers the collected message registers
 * (cL4_msg_collect) or packages them into an allocated message object queued
 * onto the receiver's message queue. Advances the per-object handshake byte
 * (obj+0x11). Any unexpected kind is a fail-closed SoftwareBreakpoint trap.
 * Confidence: medium
 */
cL4_w16_t cL4_msg_send_finalize(unsigned long *msg_word, void *obj, unsigned int opts)
{
    int kind, old_kind, cur_kind, saved_kind;
    cL4_w16_t m;
    unsigned long obj2, queue;
    long endpoint;
    unsigned int *mr;
    void *node;
    void **list;
    unsigned long u0, u1;

    long tcb = (long)(msg_word[1]);                 /* local_88 / param_1+8 */
    long *recv  = *(long **)(obj + 8);              /* param_2+8 */
    list = (void **)(recv + 0x20);                  /* local_88+0x20 */
    if (*list == 0) {
        /* fall back to a local (stack) 4-word staging area */
        queue = 0; (void)queue;
    }

    kind = opts & 0xff;
    do {
        old_kind = *(unsigned char *)(obj + 0x11);
        if (old_kind < 3) {
            mr = cL4_mr_block(tcb);
            saved_kind = *mr & 0x1f;
            if (saved_kind == 0x10) {
                endpoint = cL4_obj_kind16((long*)mr);
            } else if (saved_kind == 0x11) {
                endpoint = cL4_obj_kind17((long*)mr);
            } else if (saved_kind == 0x12) {
                endpoint = cL4_obj_kind18((long*)mr);
            } else {
                __asm__ volatile("brk #1" ::: "memory");   /* 0x3807a8 trap */
                m.lo = m.hi = 0; return m;
            }
            endpoint += ((*mr & 0x30000) == 0x20000) * 4;
            /* indirect call through the endpoint's dispatch table slot */
            int off = *(int *)(endpoint + 8);
            cL4_w16_t (*handler)(long, void **, long) = 0;
            if (off != 0) handler = (void*)((long)off + endpoint + 8);
            m = handler(tcb, list, 0);
            if (m.lo == 0) goto collect;
            cur_kind = 1;
            if ((*(unsigned char *)(*(long *)(tcb - 8) + 0x52) & 0x40) == 0)
                cur_kind = 2;
        } else {
collect:
            m = cL4_msg_collect(tcb);
            if (m.lo == 0) {
                /* no collected registers; enqueue the sender TCB on the endpoint */
                mr = cL4_mr_block(tcb);
                saved_kind = *mr & 0x1f;
                long **slot;
                if (saved_kind == 0x10)      slot = (long**)cL4_obj_kind16((long*)mr);
                else if (saved_kind == 0x11) slot = (long**)cL4_obj_kind17((long*)mr);
                else if (saved_kind == 0x12) slot = (long**)cL4_obj_kind18((long*)mr);
                else { __asm__ volatile("brk #1" ::: "memory"); m.lo=m.hi=0; return m; }
                long **q = slot + ((*mr & 0x30000) == 0x20000);
                if (*q != 0) q = (long**)((long)*q + (long)q);
                *q = (long*)tcb;
                cur_kind = 4;
                *(unsigned char *)(obj + 0x11) = 4;
                goto finish;
            }
            cur_kind = 3;
        }
        u0 = m.lo; u1 = m.hi;
        *(unsigned char *)(obj + 0x11) = cur_kind;
        if (saved_kind < 0x3f) {
            if ((opts & 0xff) != 0) {
                if (saved_kind != 1) { __asm__ volatile("brk #1" ::: "memory"); m.lo=m.hi=0; return m; }
                if (cur_kind == 3) goto package;
            }
        } else {
            if (saved_kind != 0x3f && saved_kind != 0xff) {
                __asm__ volatile("brk #1" ::: "memory"); m.lo=m.hi=0; return m;
            }
package:
            if (*(long *)(recv + 0x20) == 0 && u0 != 0) {
                /* allocate and populate a 4-word message node, queue it */
                void *node2 = cL4_alloc(0x20, 0x80c4018a671a6);
                ((long*)node2)[0] = u0;
                ((long*)node2)[1] = u1;
                long old = *(long *)(recv + 0x20);
                *(void **)(recv + 0x20) = node2;
                if (old != 0) cL4_free((void*)old, 0x20);
            }
finish:
            u0 = *(unsigned long *)(recv + 0x20);
            *(unsigned long *)(recv + 0x20) = 0;
            cL4_msg_finish(msg_word, obj, m.lo, m.hi, u0);
            m = cL4_msg_result(msg_word, cur_kind);
            return m;
        }
        if ((opts >> 8 & 1) != 0) goto package;
        if (old_kind < cur_kind) {
            cL4_msg_wake((long)msg_word, obj, m.lo, u1);
            recv = *(long **)(obj + 8);
        }
        cL4_msg_handshake(*(unsigned long *)(msg_word + 1), opts & 0xff, m.lo, u1);
    } while (1);
}


/* FUN_003800cc @ 0x003800cc   (est. cL4_ipc_recv_wait)
 * Ghidra: undefined1[16] FUN_003800cc(ulong *param_1, undefined8 param_2)
 * The core IPC receive/wait loop for the current thread. Reads the message
 * word *param_1 and classifies it; an empty/ready message (kind<2) returns
 * immediately with the low 3 bits of the word. Otherwise it loops: acquires a
 * reference on the IPC object, advances the handshake, and for a
 * "with-registers" message (kind 3) collects the incoming registers into a
 * freshly allocated message node queued onto the receiver, then finalizes via
 * cL4_msg_send_finalize. The 16-byte return carries the collected/result
 * word. Any unexpected message kind is a fail-closed SoftwareBreakpoint trap.
 * Confidence: medium
 */
cL4_w16_t cL4_ipc_recv_wait(unsigned long *msg_word, unsigned long opts)
{
    cL4_w16_t out;
    unsigned long word, mkind, thread;
    long *node;
    void **pending = 0;
    void *staging;
    unsigned long alloc = 0;

    word = *msg_word;
    mkind = cL4_msg_classify(&word, 0);
    if (mkind < 2) {
        out = cL4_msg_result(msg_word, word & 7);
        return out;
    }

    node = 0;
    staging = &cL4_current_thread;
    alloc = 0;
    for (;;) {
        thread = cL4_current_thread;           /* _DAT_006c0380 */
        cL4_ref_acquire(cL4_current_thread);
        if (node != 0) cL4_ref_release((unsigned long)node);
        word = *msg_word;
        mkind = cL4_msg_classify(&word, opts);
        if (mkind != 2) break;
        node = (long *)(word & 0xfffffffffffffff0ULL);
        node[0] = node[0] + 1;                 /* refcount++ */
        if (((word >> 3) & 1) == 0) goto bail;
        cL4_release(thread);
        cL4_ref_acquire((unsigned long)(node + 2));
        cL4_release((unsigned long)(node + 2));
    }
    if (mkind == 3) {
        alloc = cL4_obj_alloc();
        if (((word >> 3) & 1) == 0) {
            unsigned long *src = (unsigned long *)(word & 0xfffffffffffffff0ULL);
            if (src != 0) {
                unsigned long v0 = src[0], v1 = src[1], v2 = src[2];
                *(unsigned long *)(alloc + 0x30) = v1;
                *(unsigned long *)(alloc + 0x28) = v0;
                src[2] = 0;
                unsigned long old = *(unsigned long *)(alloc + 0x20);
                *(unsigned long *)(alloc + 0x20) = v2;
                if (old != 0) cL4_free((void*)old, 0x20);
                int had = (pending != 0);
                pending = (void**)src;
                if (had) cL4_msg_list_push((unsigned long*)&pending);
            }
        }
        *msg_word = (word & 7) | alloc | 8;
        cL4_release(thread);
        out = cL4_msg_send_finalize(msg_word, staging, opts);
        goto done;
    }
bail:
    cL4_release(thread);
    out = cL4_msg_result(msg_word, word & 7);
done:
    if (pending != 0) cL4_msg_list_push((unsigned long*)&pending);
    cL4_msg_free(staging);
    return out;
}


/* FUN_003807a8 @ 0x003807a8   (est. cL4_msg_finish)
 * Ghidra: void FUN_003807a8(ulong*, undefined8*, long, long, long)
 * Finalizes an IPC handshake for a thread. If either collected data word
 * (param_3) or the extra word (param_5) is nonzero, allocates a 3-word
 * message node {d0,d1,d2} (tag 0x1060c4048d9c6c4). Then acquires a reference
 * on the peer object, stores the node pointer OR the handshake byte into the
 * thread's message word (*param_1), releases the IPC object locks, clears the
 * handshake/queue state, and releases the peer reference.
 * Confidence: medium
 */
void cL4_msg_finish(unsigned long *msg_word, void *obj, unsigned long d0,
                    unsigned long d1, unsigned long extra)
{
    unsigned char hb = *(unsigned char *)((char*)obj + 0x11);
    long *node;
    unsigned long peer;

    if (d0 == 0 && extra == 0) {
        node = 0;
    } else {
        node = cL4_alloc(0x20, 0x1060c4048d9c6c4ULL);
        node[0] = d0;
        node[1] = d1;
        node[2] = extra;
    }
    peer = *(unsigned long *)*(unsigned long **)obj;
    cL4_ref_acquire(peer);
    *msg_word = (unsigned long)node | (unsigned long)hb;
    cL4_release(((unsigned long *)obj)[1] + 0x10);
    cL4_ref_release(((unsigned long *)obj)[1]);
    cL4_release(peer);
    *(unsigned short *)((char*)obj + 0x10) = 0;   /* *(undefined1*)(param_2+2)=0 (byte at +0x10) */
    ((unsigned long *)obj)[1] = 0;
}


/* ------------------------------------------------------------------ *
 * IPC message-register (MR) copy machinery. FUN_0037e780 copies one message
 * word into an accumulator; FUN_0037e868 finalizes a multi-word copy. Each
 * of the small in-range wrappers below copies a fixed register count.
 * ------------------------------------------------------------------ */

/* FUN_0037e780 @ 0x37e780 — copy one message word: returns the updated
 * accumulator and stores the copied word into *out. */
extern unsigned long cL4_mr_copy(long reg, unsigned long *out, unsigned long n,
                                 unsigned long opts, unsigned long src);
/* FUN_0037e868 @ 0x37e868 — finalize a message-register copy (commit). */
extern void cL4_mr_copy_finish(long reg, unsigned long acc, unsigned long n,
                               unsigned long opts);
/* FUN_003810c4 @ 0x3810c4 — copy a message word through a word-table entry. */
extern unsigned long cL4_mr_copy_word(long reg, unsigned long *out, unsigned long n,
                                      unsigned long opts, unsigned long entry);
/* FUN_0037e528 @ 0x37e528 — init a message-register copy context block. */
extern void cL4_mr_ctx_init(void *ctx);
/* FUN_0035b178 @ 0x35b178 — iterate a thread's blocked/message waiters:
 * returns the next waiter index for the given wait-set word, else 0. */
extern int cL4_waiter_next(unsigned long *word, unsigned long start, int mode);
/* FUN_0036becc @ 0x36becc — waiter-scan hash of a key. */
extern unsigned long cL4_waiter_hash(unsigned long key);
unsigned long cL4_mr_copy6_disp(unsigned long *reg, unsigned long acc0, void *c1, void *c2,
                                unsigned char *c, unsigned long *d0);

/* FUN_00117cc4 @ 0x117cc4 — simple bulk memory/register copy op. */
extern long cL4_obj_copy_simple(long dst, long src, unsigned long op);
/* FUN_0036b270 @ 0x36b270 — resolve the per-object copy stride/offset. */
extern void cL4_obj_copy_advance(void);
/* thunk_FUN_00114d10 @ 0x114d10 — capability equality check. */
extern int cL4_cap_equal(unsigned long cap);
/* FUN_003a2b38 @ 0x3a2b38 — resolve a message word from a capability pair. */
extern unsigned long cL4_cap_resolve_word(unsigned long a, unsigned long b);
/* thunk_FUN_00115080 @ 0x115080 — resolve a capability to a word. */
extern unsigned long cL4_cap_resolve(unsigned long cap);
/* thunk_FUN_001145b0 @ 0x1145b0 — cap equality with detail compare. */
unsigned long cL4_mr_copy_cap(unsigned long reg, unsigned long acc0, unsigned long n,
                  unsigned long opts, unsigned long *src);
/* FUN_00365238 @ 0x365238 — helper consulted by cL4_msg_validate. */
extern unsigned long cL4_mr_validate_finish(unsigned long *p);
/* SIMD copy helper primitives (0x37e58c/0x37e614/0x37eb4c/0x37e8e8). */
extern void cL4_simd_copy_begin(void *ctx, unsigned long p, unsigned long imm);
extern void cL4_simd_copy_loop(void *ctx, unsigned long p);
extern void cL4_simd_copy_finish(void *ctx, unsigned long n);
extern void cL4_simd_copy_small(unsigned long p, unsigned long n);
/* FUN_0011d7e8 @ 0x11d7e8 — noreturn stack-canary failure handler. */
extern void cL4_stack_fail(void) __attribute__((noreturn));
/* FUN_00380dd0 zero-arg form — working waiter-state word. */
extern unsigned long cL4_mr_collect_state(void);
/* FUN_0037a850 @ 0x37a850 — init a message-node wait queue. */
extern void cL4_node_wait_init(unsigned long *wq, unsigned long v);
/* thunk_FUN_00053aa0 @ 0x53aa0 — destroy a wait queue. */
extern void cL4_waitq_destroy(unsigned long *wq);
/* FUN_00362e54 @ 0x362e54 — get the per-CPU TCB zone descriptor. */
extern long cL4_zone_get(void);
/* FUN_00367d50 @ 0x367d50 — get the per-CPU context descriptor table. */
extern void cL4_percpu_ctx_table(void *out);
/* FUN_00375fc8 @ 0x375fc8 — build a context block from an object. */
extern void cL4_ctx_build(unsigned long *out, unsigned long obj, unsigned long src);
/* FUN_00379f6c @ 0x379f6c — validate a context block against a waiter. */
extern unsigned long cL4_ctx_validate(unsigned long *ctx, long waiter);
/* thunk_FUN_001145b0 @ 0x1145b0 — cap equality with detail compare. */
extern int cL4_cap_equal2(long a, unsigned long b, long r);
/* FUN_00367d50 @ 0x367d50 — get the per-CPU context descriptor table. */
/* FUN_00386160 — table-2 waiter scan (capability hash). */
extern cL4_w16_t cL4_waiter_scan_cap_hash(unsigned long *key, unsigned long start,
                                          unsigned long limit, long base);
/* FUN_00386280 — table-2 entry hash. */
extern unsigned long cL4_tbl2_hash(unsigned long *entry);
/* FUN_00375fc8 @ 0x375fc8 — build a context block from an object. */
/* FUN_00379f6c @ 0x379f6c — validate a context block against a waiter. */
/* FUN_00384e60 — shifted MR copy. */
extern unsigned long cL4_mr_copy_shifted_r(unsigned long reg, unsigned long *acc,
                                           unsigned long n, unsigned long opts,
                                           unsigned char byte);

/* FUN_00365238 @ 0x365238 — helper consulted by cL4_msg_validate. */
/* SIMD copy helper primitives (0x37e58c/0x37e614/0x37eb4c/0x37e8e8). */
extern void cL4_simd_copy_begin(void *ctx, unsigned long p, unsigned long imm);
extern void cL4_simd_copy_loop(void *ctx, unsigned long p);
extern void cL4_simd_copy_finish(void *ctx, unsigned long n);
extern void cL4_simd_copy_small(unsigned long p, unsigned long n);
/* FUN_00380dd0 zero-arg form — working waiter-state word. */
extern unsigned long cL4_mr_collect_state(void);
/* FUN_0037a850 @ 0x37a850 — init a message-node wait queue. */
extern void cL4_node_wait_init(unsigned long *wq, unsigned long v);
/* thunk_FUN_00053aa0 @ 0x53aa0 — destroy a wait queue. */
extern void cL4_waitq_destroy(unsigned long *wq);
/* FUN_00362e54 @ 0x362e54 — get the per-CPU TCB zone descriptor. */
extern long cL4_zone_get(void);
/* FUN_00367d50 @ 0x367d50 — get the per-CPU context descriptor table. */
extern void cL4_percpu_ctx_table(void *out);
/* FUN_00375fc8 @ 0x375fc8 — build a context block from an object. */
extern void cL4_ctx_build(unsigned long *out, unsigned long obj, unsigned long src);
/* FUN_00379f6c @ 0x379f6c — validate a context block against a waiter. */
extern unsigned long cL4_ctx_validate(unsigned long *ctx, long waiter);
/* thunk_FUN_001145b0 @ 0x1145b0 — cap equality with detail compare. */
extern int cL4_cap_equal2(long a, unsigned long b, long r);
/* FUN_00367d50 @ 0x367d50 — get the per-CPU context descriptor table. */
/* FUN_00386160 — table-2 waiter scan (capability hash). */
extern cL4_w16_t cL4_waiter_scan_cap_hash(unsigned long *key, unsigned long start,
                                          unsigned long limit, long base);
/* FUN_00386280 — table-2 entry hash. */
extern unsigned long cL4_tbl2_hash(unsigned long *entry);
/* FUN_00375fc8 @ 0x375fc8 — build a context block from an object. */
/* FUN_00379f6c @ 0x379f6c — validate a context block against a waiter. */
/* FUN_00384e60 — shifted MR copy. */
extern unsigned long cL4_mr_copy_shifted_r(unsigned long reg, unsigned long *acc,
                                           unsigned long n, unsigned long opts,
                                           unsigned char byte);

/* FUN_00380ad4 @ 0x00380ad4   (est. cL4_mr_copy6)
 * Ghidra: void FUN_00380ad4(reg, b, n, opts, src*, out*)
 * Copies a 2-message-word payload: two cL4_mr_copy steps then finalize. The
 * first source word comes from *param_5, the second from *param_6.
 * Confidence: medium
 */

long cL4_mr_copy_slot8(long dst, long src, long desc);
long cL4_mr_copy_slot10(long dst, long src, long desc);
long cL4_mr_copy_slot18(long dst, long src, long desc);
long cL4_mr_copy_slot20(long dst, long src, long desc);
long cL4_mr_copy_slot28(long dst, long src, long desc);

void cL4_mr_copy6(unsigned long reg, unsigned long acc0, unsigned long n,
                  unsigned long opts, unsigned long *src5, unsigned long *src6)
{
    unsigned long acc;
    acc = cL4_mr_copy(reg, &acc0, n, opts, *src5);
    acc0 = acc;
    acc = cL4_mr_copy(reg, &acc0, acc, opts, *src6);
    cL4_mr_copy_finish(reg, acc0, acc, opts);
}

/* FUN_00380f0c @ 0x00380f0c   (est. cL4_mr_copy10)
 * Ghidra: 10-arg variant of the MR copy sequence: two copies then tail into
 * FUN_00380fb4 (which continues with 8 more words). */
void cL4_mr_copy10(unsigned long reg, unsigned long acc0, unsigned long n,
                   unsigned long opts, unsigned long *src5, unsigned long *src6,
                   unsigned long a7, unsigned long a8, unsigned long a9, unsigned long a10)
{
    unsigned long acc;
    acc = cL4_mr_copy(reg, &acc0, n, opts, *src5);
    acc0 = acc;
    acc = cL4_mr_copy(reg, &acc0, acc, opts, *src6);
    cL4_mr_copy8(reg, acc0, acc, opts, &a7, &a8, a9, a10);
}

/* FUN_00380fb4 @ 0x00380fb4   (est. cL4_mr_copy8)
 * Ghidra: 8-arg variant: two copies then tail into cL4_mr_copy6. */
void cL4_mr_copy8(unsigned long reg, unsigned long acc0, unsigned long n,
                  unsigned long opts, unsigned long *src5, unsigned long *src6,
                  unsigned long a7, unsigned long a8)
{
    unsigned long acc;
    acc = cL4_mr_copy(reg, &acc0, n, opts, *src5);
    acc0 = acc;
    acc = cL4_mr_copy(reg, &acc0, acc, opts, *src6);
    cL4_mr_copy6(reg, acc0, acc, opts, &a7, &a8);
}

/* FUN_00381048 @ 0x00381048   (est. cL4_mr_copy6_word)
 * Ghidra: first word copied via cL4_mr_copy_word (word-table), second via
 * cL4_mr_copy, then finalize. */
void cL4_mr_copy6_word(unsigned long reg, unsigned long acc0, unsigned long n,
                       unsigned long opts, unsigned long *src5, unsigned long *src6)
{
    unsigned long acc;
    acc = cL4_mr_copy_word(reg, &acc0, n, opts, *src5);
    acc0 = acc;
    acc = cL4_mr_copy(reg, &acc0, acc, opts, *src6);
    cL4_mr_copy_finish(reg, acc0, acc, opts);
}

/* FUN_003811ac @ 0x003811ac   (est. cL4_mr_copy6_word2)
 * Ghidra: first word via cL4_mr_copy, second via cL4_mr_copy_word, finalize. */
void cL4_mr_copy6_word2(unsigned long reg, unsigned long acc0, unsigned long n,
                        unsigned long opts, unsigned long *src5, unsigned long *src6)
{
    unsigned long acc;
    acc = cL4_mr_copy(reg, &acc0, n, opts, *src5);
    acc0 = acc;
    acc = cL4_mr_copy_word(reg, &acc0, acc, opts, *src6);
    cL4_mr_copy_finish(reg, acc0, acc, opts);
}

/* FUN_00380b50 @ 0x00380b50   (est. cL4_msg_validate)
 * Ghidra: undefined8 FUN_00380b50(long param_1, ulong *param_2)
 * Validates an incoming IPC message descriptor (param_2) against the saved
 * sender message registers in the thread object (param_1): matches the
 * message-length/flag word, the optional word-selector field, the cap field,
 * and (when a cap-list is present) every cap and selector against the saved
 * copy. Returns 1 if every field matches, else 0. The address arithmetic
 * (param_1 + (len&0xffff)*8 + ... + 0x2f & ~7) selects the saved message
 * register array (stride 8 for words, 4 for selectors).
 * Confidence: medium
 */

int cL4_msg_validate(unsigned long *obj, unsigned long *desc)
{
    unsigned long len = *desc;
    if (len != obj[3]) return 0;                     /* *(param_1+0x18) */
    uint32_t f = (uint32_t)len;
    unsigned long sel0, sel1, sel2;
    long mrs;                                        /* saved MR array base */

    mrs = (long)(obj + (len & 0xffff)) & ~7UL;       /* param_1 + (len&0xffff)*8 + 0x2f & ~7 (approx) */

    sel0 = (f >> 0x1b & 1) ? ((unsigned long*)mrs)[0] : 0;
    if (desc[1] != sel0) return 0;
    if (desc[4] != obj[4]) return 0;                 /* *(param_1+0x20) */
    sel1 = (f >> 0x1c & 1) ? ((unsigned long*)mrs)[(f >> 0x1b & 1)] : 0;
    if (desc[5] != sel1) return 0;
    sel2 = ((int)f < 0) ? ((unsigned long*)mrs)[(f >> 0x1b & 1) + (f >> 0x1c & 1)] : 0;
    if ((int)desc[6] != (int)sel2) return 0;
    if (desc[7] != cL4_mr_validate_finish(obj + 2)) return 0;   /* FUN_00365238(param_1+0x10) */

    f = (uint32_t)*desc;
    if ((*desc & 0xffff) != 0) {
        for (unsigned long i = 0; i < (*desc & 0xffff); i++) {
            if (*(unsigned long *)(desc[2] + i*8) != *(unsigned long *)(obj + 0x28/8 + i*8)) return 0;
            int s1 = (f >> 0x19 & 1) ? *(int *)(desc[3] + i*4) : 0;
            int s2;
            if ((*(unsigned long *)(obj + 0x18/8) >> 0x19 & 1) == 0) s2 = 0;
            else s2 = *(int *)(obj + 0x28/8 + (obj[3] & 0xffff) + i*1 - (obj[3] & 0xffff));
            if (s1 != s2) return 0;
        }
    }
    return 1;
}


/* FUN_00380dd0 @ 0x00380dd0   (est. cL4_mr_collect_thread)
 * Ghidra: void FUN_00380dd0(ushort *param_1)
 * Collects the full message-register payload of a sender thread into a fresh
 * copy context: reads the MR header words, then copies the base word pair and
 * the extended words via the MR copy engine (cL4_mr_copy10 / cL4_mr_copy6 /
 * cL4_mr_copy6_word2), then iterates the cap/word lists copying each cap word
 * and selector. Stack-protected (canary -0x2c8502b44bfffed6); a mismatch
 * routes to the noreturn FUN_0011d7e8.
 * Confidence: low (register-move engine, exact layout inferred)
 */
void cL4_mr_collect_thread(unsigned short *mr)
{
    unsigned long hdr0, hdr1;
    unsigned int hdr2;
    unsigned long acc;
    unsigned char reg0[64], reg1[64];      /* auStack_b8 / auStack_78 */
    unsigned long canary = (unsigned long)-0x2c8502b44bfffed6ULL;

    hdr0 = *(unsigned long *)mr;
    hdr1 = *(unsigned long *)(mr + 4);
    hdr2 = *(unsigned int *)(mr + 0x18);
    cL4_mr_ctx_init(reg0);
    cL4_mr_copy10(0, 0, (unsigned long)reg0, (unsigned long)reg1,
                  &hdr0, &hdr1, (unsigned long)(mr + 0x10), (unsigned long)(mr + 0x14), (unsigned long)&hdr2, (unsigned long)(mr + 0x1c));
    if (*(unsigned short *)mr != 0) {
        for (unsigned long i = 0; i < *(unsigned short *)mr; i++) {
            hdr0 = *(unsigned long *)(*(long *)(mr + 8) + i*8);
            cL4_mr_ctx_init(reg0);
            cL4_mr_copy6(0, 0, (unsigned long)reg0, (unsigned long)reg1,
                         &acc, &hdr0);
            if ((*(unsigned char *)((long)mr + 3) >> 1 & 1) == 0) hdr2 = 0;
            else hdr2 = *(unsigned int *)(*(long *)(mr + 0xc) + i*4);
            hdr0 = (hdr0 & 0xffffffff00000000ULL) | hdr2;
            cL4_mr_ctx_init(reg0);
            cL4_mr_copy6_word2(0, 0, (unsigned long)reg0, (unsigned long)reg1,
                               &acc, &hdr0);
        }
    }
    if (canary == (unsigned long)-0x2c8502b44bfffed6ULL) return;
    cL4_stack_fail();   /* FUN_0011d7e8 noreturn */
}

/* FUN_00380cec @ 0x00380cec   (est. cL4_msg_scan_find)
 * Ghidra: undefined1[16] FUN_00380cec(param_1, param_2, param_3, param_4)
 * Scans the blocked/message waiters for one whose saved message registers
 * match the given descriptor (cL4_msg_validate). Starts at waiter index
 * param_2 (masked by the type field from obj+0), walks the wait set via
 * cL4_waiter_next, and returns {matched_wait_index, waiter_ptr} when a match
 * is found; otherwise {count&0xffffffff, 0}. The loop is gated on the object's
 * waiter-state word (FUN_00380dd0 builds the working copy). param_3 bounds the
 * scan; param_4 is the descriptor array base.
 * Confidence: medium
 */

cL4_w16_t cL4_msg_scan_find(unsigned long *desc, unsigned long start, unsigned long limit, long base)
{
    cL4_w16_t out;
    unsigned long idx, mask;
    unsigned long w = start;
    unsigned char type = *(unsigned char *)(start & 0xfffffffffffffffcULL);

    idx = cL4_mr_collect_state();
    mask = 4;
    if ((start & 3) != 0 && (unsigned char *)(start & 0xfffffffffffffffcULL) != 0)
        mask = (unsigned long)*(unsigned char *)(start & 0xfffffffffffffffcULL);
    mask = -1UL << (mask & 0x3f);
    idx = idx & ~mask;
    if (idx < 2) idx = 1;
    int w2 = cL4_waiter_next(&w, idx, 2);
    while (w2 != 0) {
        unsigned long i = (unsigned long)(w2 - 1);
        if (i < limit) {
            if ((cL4_msg_validate((unsigned long *)*(unsigned long *)(base + i*8), desc) & 1) != 0) {
                idx = 0;
                base = base + i*8;
                goto found;
            }
        }
        idx = (idx + 1) & ~mask;
        if (idx < 2) idx = 1;
        w2 = cL4_waiter_next(&w, idx, 2);
    }
    base = 0;
    idx = idx & 0xffffffff;
found:
    out.hi = idx;
    out.lo = base;
    return out;
}

/* ------------------------------------------------------------------ *
 * Message-register / buffer copy family. Each variant checks the object's
 * capability flag byte (at *(obj-8)+0x52, bit 0): when clear it performs a
 * simple bulk copy (FUN_00117cc4) using the object's single-copy op
 * (*(obj-8)+0x40); when set it iterates `count` elements (from param_3+8)
 * calling the object's element-copy op from its dispatch table
 * (*(*(param_3+0x10)-8)+0x8..0x28). The variants differ only in the dispatch
 * slot used (0x8/0x10/0x18/0x20/0x28).
 * ------------------------------------------------------------------ */


/* Dispatch-table call helper: call slot `slot` on object `obj` for (a,b). */
static inline long cL4_obj_copy_call(long obj, long a, long b, long slot)
{
    long *vt = *(long **)(*(long *)(obj) - 8);
    unsigned long (*fn)(long, long) = (void*)(vt[slot/8]);
    return fn(a, b);
}

/* FUN_0038179c @ 0x0038179c   (est. cL4_mr_copy_advance)
 * Ghidra: long* FUN_0038179c(long *param_1, long *param_2, long param_3)
 * Advances a message-register copy: when the object's flag bit1 at
 * *(obj-8)+0x52 is clear, delegates to FUN_003818b4; otherwise stores
 * *param_2 into *param_1, resolves the object's per-element stride
 * (*(obj-8)+0x50 + 0x10) via FUN_0036b270, and returns the advanced pointer.
 * Confidence: medium
 */
long *cL4_mr_copy_advance(long *dst, long *src, long obj)
{
    long *r;
    if ((*(unsigned char *)(*(long *)(obj - 8) + 0x52) >> 1 & 1) == 0) {
        dst = (long*)cL4_mr_copy_slot8((long)dst,(long)src,obj);
    } else {
        *dst = *src;
        cL4_obj_copy_advance();
        dst = (long *)(*dst + ((unsigned long)*(unsigned char *)(*(long *)(obj-8)+0x50) + 0x10 &
                    ((unsigned long)*(unsigned char *)(*(long *)(obj-8)+0x50) ^ ~0UL)));
    }
    return dst;
}

/* FUN_0038181c @ 0x0038181c   (est. cL4_mr_copy_foreach_slot8)
 * Ghidra: void FUN_0038181c(long param_1, long param_2)
 * When the object's flag bit0 at *(obj-8)+0x52 is set, iterates `count`
 * elements calling the object's slot-0x8 copy op (through
 * *(*(param_2+0x10)-8)+8) with stride from *(*(param_2+0x10)-8)+0x48.
 * Confidence: medium
 */
void cL4_mr_copy_foreach_slot8(long dst, long desc)
{
    if ((*(unsigned char *)(*(long *)(desc - 8) + 0x52) & 1) != 0) {
        uint32_t n = (uint32_t)*(unsigned long *)(desc + 8) &
            ((uint32_t)((long)*(unsigned long *)(desc + 8) >> 0x3f) ^ 0xffffffffu);
        if (n != 0) {
            uint32_t stride = *(uint32_t *)(*(long *)(*(long *)(desc + 0x10) - 8) + 0x48);
            do {
                (**(void (**)(long))(*(long *)(*(long *)(desc + 0x10) - 8) + 8))(dst);
                dst = dst + stride;
                n--;
            } while (n != 0);
        }
    }
}

/* FUN_003818b4 / 0038198c / 00381a64 / 00381b3c — the 5 dispatch-slot copy
 * variants (slot 0x8/0x10/0x18/0x20/0x28). */
long cL4_mr_copy_slot8(long dst, long src, long desc)
{
    long r;
    if ((*(unsigned char *)(*(long *)(desc - 8) + 0x52) & 1) == 0) {
        return cL4_obj_copy_simple(dst, src, *(unsigned long *)(*(long *)(desc-8) + 0x40));
    }
    uint32_t n = (uint32_t)*(unsigned long *)(desc + 8) &
        ((uint32_t)((long)*(unsigned long *)(desc + 8) >> 0x3f) ^ 0xffffffffu);
    if (n != 0) {
        unsigned long stride = *(uint32_t *)(*(long *)(*(long *)(desc + 0x10) - 8) + 0x48);
        long d = dst;
        long s = src;
        do {
            cL4_obj_copy_call(*(long *)(desc + 0x10), d, s, 0x8);
            d += stride; s += stride;
            n--;
        } while (n != 0);
    }
    return dst;
}

long cL4_mr_copy_slot10(long dst, long src, long desc)
{
    long r;
    if ((*(unsigned char *)(*(long *)(desc - 8) + 0x52) & 1) == 0) {
        return cL4_obj_copy_simple(dst, src, *(unsigned long *)(*(long *)(desc-8) + 0x40));
    }
    uint32_t n = (uint32_t)*(unsigned long *)(desc + 8) &
        ((uint32_t)((long)*(unsigned long *)(desc + 8) >> 0x3f) ^ 0xffffffffu);
    if (n != 0) {
        unsigned long stride = *(uint32_t *)(*(long *)(*(long *)(desc + 0x10) - 8) + 0x48);
        long d = dst, s = src;
        do { cL4_obj_copy_call(*(long *)(desc + 0x10), d, s, 0x10); d+=stride; s+=stride; n--; }
        while (n != 0);
    }
    return dst;
}

long cL4_mr_copy_slot18(long dst, long src, long desc)
{
    if ((*(unsigned char *)(*(long *)(desc - 8) + 0x52) & 1) == 0)
        return cL4_obj_copy_simple(dst, src, *(unsigned long *)(*(long *)(desc-8) + 0x40));
    uint32_t n = (uint32_t)*(unsigned long *)(desc + 8) &
        ((uint32_t)((long)*(unsigned long *)(desc + 8) >> 0x3f) ^ 0xffffffffu);
    if (n != 0) {
        unsigned long stride = *(uint32_t *)(*(long *)(*(long *)(desc + 0x10) - 8) + 0x48);
        long d = dst, s = src;
        do { cL4_obj_copy_call(*(long *)(desc + 0x10), d, s, 0x18); d+=stride; s+=stride; n--; }
        while (n != 0);
    }
    return dst;
}

long cL4_mr_copy_slot20(long dst, long src, long desc)
{
    if ((*(unsigned char *)(*(long *)(desc - 8) + 0x52) & 1) == 0)
        return cL4_obj_copy_simple(dst, src, *(unsigned long *)(*(long *)(desc-8) + 0x40));
    uint32_t n = (uint32_t)*(unsigned long *)(desc + 8) &
        ((uint32_t)((long)*(unsigned long *)(desc + 8) >> 0x3f) ^ 0xffffffffu);
    if (n != 0) {
        unsigned long stride = *(uint32_t *)(*(long *)(*(long *)(desc + 0x10) - 8) + 0x48);
        long d = dst, s = src;
        do { cL4_obj_copy_call(*(long *)(desc + 0x10), d, s, 0x20); d+=stride; s+=stride; n--; }
        while (n != 0);
    }
    return dst;
}

long cL4_mr_copy_slot28(long dst, long src, long desc)
{
    if ((*(unsigned char *)(*(long *)(desc - 8) + 0x52) & 1) == 0)
        return cL4_obj_copy_simple(dst, src, *(unsigned long *)(*(long *)(desc-8) + 0x40));
    uint32_t n = (uint32_t)*(unsigned long *)(desc + 8) &
        ((uint32_t)((long)*(unsigned long *)(desc + 8) >> 0x3f) ^ 0xffffffffu);
    if (n != 0) {
        unsigned long stride = *(uint32_t *)(*(long *)(*(long *)(desc + 0x10) - 8) + 0x48);
        long d = dst, s = src;
        do { cL4_obj_copy_call(*(long *)(desc + 0x10), d, s, 0x28); d+=stride; s+=stride; n--; }
        while (n != 0);
    }
    return dst;
}

/* FUN_00381c5c @ 0x00381c5c   (est. cL4_buffer_validate)
 * Ghidra: bool FUN_00381c5c(long param_1, ulong *param_2)
 * Validates a message/buffer descriptor (param_2) against the thread's saved
 * buffer state (param_1): the length word must match *(param_1+0x78); each of
 * the `len` buffer words at param_2[1] must equal the saved copy at
 * param_1+0x88 (stride 0x10); and the buffer capability word (param_2[2]) must
 * equal *(param_1+0x80) or be capability-equal (thunk_FUN_00114d10 == 0).
 * Returns true only if all match.
 * Confidence: medium
 */
int cL4_buffer_validate(unsigned long *obj, unsigned long *desc)
{
    unsigned long len = *desc;
    if (len != obj[0x78/8]) return 0;
    if (len != 0) {
        for (unsigned long i = 0; i < len; i++) {
            if (*(unsigned long *)(desc[1] + i*8) !=
                *(unsigned long *)((char*)obj + 0x88 + (i & 0xffffffff)*0x10)) return 0;
        }
    }
    unsigned long cap = desc[2];
    if (cap == obj[0x80/8]) return 1;
    if (cap != 0 && obj[0x80/8] != 0) {
        return cL4_cap_equal(cap) == 0;
    }
    return 0;
}

/* FUN_00381e64 @ 0x00381e64   (est. cL4_buffer_copy)
 * Ghidra: void FUN_00381e64(long param_1, long param_2)
 * Copies a buffer [param_1, param_2). For ranges >0x40 bytes it runs a
 * 0x40-byte SIMD copy loop (cL4_mr_ctx_init-style ops) in 0x40 chunks then
 * finalizes; for small ranges it uses the simple copy path.
 * Confidence: medium
 */
void cL4_buffer_copy(unsigned long dst, unsigned long end)
{
    unsigned long n = end - dst;
    unsigned char ctx[56];
    if (0x40 < n) {
        unsigned long rem = n & ~0x3fULL;
        cL4_simd_copy_begin(ctx, dst, 0xf9000a63a9000a61ULL);
        while ((rem -= 0x40) != 0) {
            dst += 0x40;
            cL4_simd_copy_loop(ctx, dst);
        }
        if ((n & 0x3f) != 0) cL4_simd_copy_loop(ctx, end - 0x40);
        cL4_simd_copy_finish(ctx, n);
        return;
    }
    cL4_simd_copy_small(dst, n);
}

/* FUN_00381f3c @ 0x00381f3c   (est. cL4_mr_copy_cap)
 * Ghidra: void FUN_00381f3c(reg, acc0, n, opts, src*)
 * Copies one message word from a capability-derived source: resolves the word
 * via FUN_003a2b38(src[0],src[1]) then one cL4_mr_copy step + finalize.
 * Confidence: medium
 */
unsigned long cL4_mr_copy_cap(unsigned long reg, unsigned long acc0, unsigned long n,
                     unsigned long opts, unsigned long *src)
{
    unsigned long w = cL4_cap_resolve_word(src[0], src[1]);   /* FUN_003a2b38 */
    unsigned long acc;
    acc = cL4_mr_copy(reg, &acc0, n, opts, w);
    cL4_mr_copy_finish(reg, acc0, acc, opts);
    return acc;
}

/* FUN_00381378 @ 0x00381378   (est. cL4_ipc_send_recv_loop)
 * Ghidra: undefined1[16] FUN_00381378(ulong *param_1, undefined8 *param_2, uint param_3)
 * The message-register send/receive loop that drives the IPC state machine.
 * Builds a per-object dispatch table (slots 1..8) pointing at the MR copy
 * family (cL4_mr_copy_advance / foreach / slot8..28), then dispatches on the
 * message kind byte (obj+0x11): a "with-registers" message (kind 3) collects
 * the registers; other kinds copy the incoming MRs into the message object.
 * Advances the handshake, wakes/queues as needed, and finally publishes the
 * message word and returns {ptr, kind-lookup}. Any unexpected kind is a
 * fail-closed SoftwareBreakpoint trap.
 * Confidence: low (large state machine, dispatch-table slot mapping inferred)
 */
cL4_w16_t cL4_ipc_send_recv_loop(unsigned long *msg, unsigned long *obj, unsigned int opts)
{
    cL4_w16_t r;
    unsigned long thread, u12, u8, u2;
    uint32_t u7;
    unsigned char b3;
    unsigned long extra_x1;
    unsigned long l13 = obj[1];
    unsigned long *pu1 = msg + 1;
    unsigned long u2v = opts & 0xff;
    void *node5;

    do {
        b3 = *(unsigned char *)((char*)obj + 0x11);
        if (b3 == 3) {
            r = cL4_msg_collect((long)(msg + 0xe));
            u12 = r.lo;
            u7 = (u12 == 0) ? 4 : 3;
            u8 = u7;
            *(char *)((char*)obj + 0x11) = (char)u7;
            goto after_classify;
        } else {
            u12 = msg[0x10];
            unsigned long kind = 0x13f;
            extra_x1 = cL4_msg_state_advance(&u12, (unsigned int)kind);
            if (0x3f < extra_x1) {
                u8 = 1;
                *(unsigned char *)((char*)obj + 0x11) = 1;
                r.lo = u12; r.hi = 0x3f;
                goto after_classify;
            }
            /* build the MR copy dispatch table in msg[1..8] */
            msg[0xd] = (unsigned long)pu1;
            unsigned long l9 = *(unsigned long *)(u12 - 8);
            unsigned long st = *(unsigned long *)(l9 + 0x48) * msg[0xf];
            msg[9] = st; msg[10] = st;
            uint32_t flags = (*(uint32_t *)(l9 + 0x50) & 0x1000f8) != 0 || 0x18 < st;
            *(uint32_t *)(msg + 0xb) = (flags ? 0x20000 : 0) | *(uint32_t *)(l9 + 0x50) & 0xfffdffff;
            *(uint32_t *)((char*)msg + 0x5c) = *(uint32_t *)(l9 + 0x54);
            msg[1] = (unsigned long)cL4_mr_copy_advance;
            msg[2] = (unsigned long)cL4_mr_copy_foreach_slot8;
            msg[3] = (unsigned long)cL4_mr_copy_slot8;
            msg[4] = (unsigned long)cL4_mr_copy_slot10;
            msg[5] = (unsigned long)cL4_mr_copy_slot18;
            msg[6] = (unsigned long)cL4_mr_copy_slot20;
            msg[7] = (unsigned long)cL4_mr_copy_slot28;
            if (extra_x1 == 1) { r = cL4_msg_collect((long)(msg + 0xe)); u12 = r.lo; u7=(u12==0)?4:3; u8=u7; *(char*)((char*)obj+0x11)=(char)u7; goto after_classify; }
            if (extra_x1 == 0) {
                r.lo = msg[0xe]; r.hi = 0;   /* auVar16 = auVar4 << 0x40 with x21 */
                u8 = 4;
                *(unsigned char *)((char*)obj + 0x11) = 4;
                u12 = 3;
                goto LAB_finish_setup;
            }
            u8 = 3;
            *(unsigned char *)((char*)obj + 0x11) = 3;
            r.lo = u12; r.hi = 1;
        }
after_classify:
        u2 = (unsigned long)u8;
        if (u2v < 0x3f) {
            if ((opts & 0xff) != 0) {
                if (u2v != 1) goto trap;
                if (u8 == 3) goto LAB_publish;
            }
        } else {
            if (u2v != 0x3f) {
                if (u2v != 0xff) { trap: __asm__ volatile("brk #1" ::: "memory"); r.lo=r.hi=0; return r; }
            }
LAB_publish:
            u12 = (unsigned long)((int)u8 - 1) & 0xff;
LAB_finish_setup:
            node5 = 0;
            unsigned long l9 = *(unsigned long *)(l13 + 0x20);
            *(unsigned long *)(l13 + 0x20) = 0;
            if (r.lo != 0 || l9 != 0) {
                node5 = cL4_alloc(0x20, 0x1060c4048d9c6c4ULL);
                *(cL4_w16_t*)node5 = r;
                *(unsigned long *)((char*)node5 + 8) = l9;
            }
            unsigned long peer = *(unsigned long *)*(unsigned long**)obj;
            cL4_ref_acquire(peer);
            *msg = (unsigned long)node5 | u8;
            cL4_release(obj[1] + 0x10);
            cL4_ref_release(obj[1]);
            cL4_release(peer);
            *(unsigned short *)((char*)obj + 0x10) = 0;
            obj[1] = 0;
            r.lo = (unsigned long)(msg + 0xe);
            r.hi = *(unsigned long *)(u12 * 8 + 0x4f27b0);   /* kind->result table */
            return r;
        }
        if ((opts >> 8 & 1) != 0) goto LAB_publish;
        if (b3 < u8) {
            unsigned long peer = *(unsigned long *)*(unsigned long**)obj;
            cL4_ref_acquire(peer);
            long *q = (long*)obj[1];
            long *q2 = q;
            if (*q != 1) {
                q2 = (long*)cL4_obj_alloc();
                unsigned long l9 = q[4];
                q[4] = 0;
                unsigned long old = q2[4];
                q2[4] = l9;
                if (old != 0) cL4_free((void*)old, 0x20);
            }
            *(cL4_w16_t*)(q2 + 5) = r;
            *msg = (unsigned long)*(unsigned char *)((char*)obj + 0x11) | (unsigned long)q2 | 8;
            if (q2 != q) {
                cL4_release(obj[1] + 0x10);
                cL4_ref_release(obj[1]);
                obj[1] = (unsigned long)q2;
            }
            cL4_release(peer);
            l13 = obj[1];
        }
        cL4_msg_handshake((long)(msg + 0xe), opts & 0xff, r.lo, r.hi);
    } while (1);
}

/* ------------------------------------------------------------------ *
 * Second copy-dispatch family: iterate `count` entries in a descriptor table
 * at param_3+0x18 (each entry = {object, offset}) calling the object's
 * element-copy op from its dispatch table (*(obj-8)+slot). Variants differ
 * only in slot (0x8/0x10/0x18/0x20/0x28). cL4_dispatch_foreach (slot 8, void)
 * is the single-arg form.
 * ------------------------------------------------------------------ */

/* FUN_00382df4 / 00383490 — slot-8 foreach (no per-entry source). */
static void cL4_dispatch_foreach_slot8(long dst, long desc)
{
    long n = *(long *)(desc + 8);
    if (n != 0) {
        long *e = (long *)(desc + 0x20);
        do {
            (**(void (**)(long))(*(long *)(e[-1] - 8) + 8))(dst + *e);
            e += 2;
            n--;
        } while (n != 0);
    }
}

/* The (dst, src, desc) 2-operand variants with element table at desc+0x18. */
static long cL4_dispatch_copy_slot10(long dst, long src, long desc)
{
    unsigned long n = *(unsigned long *)(desc + 8);
    if (n != 0) {
        for (unsigned long i = 0; i < n; i++) {
            long *e = (long *)(desc + 0x18 + (i & 0xffffffff)*0x10);
            long off = e[1];
            (**(void (**)(long,long))(*(long *)(e[0] - 8) + 0x10))(dst + off, src + off);
        }
    }
    return dst;
}
static long cL4_dispatch_copy_slot18(long dst, long src, long desc)
{
    unsigned long n = *(unsigned long *)(desc + 8);
    if (n != 0) {
        for (unsigned long i = 0; i < n; i++) {
            long *e = (long *)(desc + 0x18 + (i & 0xffffffff)*0x10);
            long off = e[1];
            (**(void (**)(long,long))(*(long *)(e[0] - 8) + 0x18))(dst + off, src + off);
        }
    }
    return dst;
}
static long cL4_dispatch_copy_slot20(long dst, long src, long desc)
{
    unsigned long n = *(unsigned long *)(desc + 8);
    if (n != 0) {
        for (unsigned long i = 0; i < n; i++) {
            long *e = (long *)(desc + 0x18 + (i & 0xffffffff)*0x10);
            long off = e[1];
            (**(void (**)(long,long))(*(long *)(e[0] - 8) + 0x20))(dst + off, src + off);
        }
    }
    return dst;
}
static long cL4_dispatch_copy_slot28(long dst, long src, long desc)
{
    unsigned long n = *(unsigned long *)(desc + 8);
    if (n != 0) {
        for (unsigned long i = 0; i < n; i++) {
            long *e = (long *)(desc + 0x18 + (i & 0xffffffff)*0x10);
            long off = e[1];
            (**(void (**)(long,long))(*(long *)(e[0] - 8) + 0x28))(dst + off, src + off);
        }
    }
    return dst;
}

/* FUN_00383200 / 00383204 / 00383444 / 00383448 — copy-advance helpers
 * (identical bodies): store *src into *dst, resolve the object's stride via
 * FUN_0036b270, and return the advanced pointer.
 * Confidence: medium
 */
long cL4_mr_advance_a(unsigned long *dst, unsigned long *src)
{
    *dst = *src;
    cL4_obj_copy_advance();
    return (long)src + (*(unsigned char *)(*(long *)((long)src - 8) + 0x50) + 0x10 &
            (*(unsigned char *)(*(long *)((long)src - 8) + 0x50) ^ ~0UL));
}
long cL4_mr_advance_b(unsigned long *dst, unsigned long *src) { return cL4_mr_advance_a(dst, src); }
long cL4_mr_advance_c(unsigned long *dst, unsigned long *src) { return cL4_mr_advance_a(dst, src); }
long cL4_mr_advance_d(unsigned long *dst, unsigned long *src) { return cL4_mr_advance_a(dst, src); }

/* FUN_003838a8 @ 0x003838a8   (est. cL4_msg_node_alloc_fixed)
 * Ghidra: void FUN_003838a8(long param_1)
 * Allocates a 0x10-byte message/notification node (tag 0xa1c40bd48d6d6),
 * initializes it with a fixed dispatch-table pointer (0x67b530) and the
 * caller's saved state word. Returns void (node pointer implicit).
 * Confidence: medium
 */
void cL4_msg_node_alloc_fixed(long obj)
{
    unsigned long *node = cL4_alloc(0x10, 0xa1c40bd48d6d6ULL);
    node[0] = 0x67b530;
    node[1] = *(unsigned long *)(obj + 8);
}

/* FUN_00381cfc @ 0x00381cfc   (est. cL4_msg_scan_find_cap)
 * Ghidra: undefined1[16] FUN_00381cfc(long *param_1, ulong param_2, ulong param_3, long param_4)
 * Like cL4_msg_scan_find but for capability-bearing messages: first copies
 * the message registers (cL4_buffer_copy over param_1[1]..+len*8), resolves
 * the capability (thunk_FUN_00115080) into the MR copy, then scans the
 * blocked waiters for one whose saved buffer matches (cL4_buffer_validate).
 * Returns {matched_wait_index, waiter_ptr}; 0 index on no match.
 * Confidence: medium
 */
cL4_w16_t cL4_msg_scan_find_cap(unsigned long *desc, unsigned long start,
                                unsigned long limit, long base)
{
    cL4_w16_t out;
    unsigned long w = start, u3, u5;
    unsigned char type;
    long cap = desc[2];
    unsigned long capres;
    unsigned long mr0;
    int w2;

    cL4_buffer_copy(desc[1], desc[1] + *desc * 8);
    unsigned long copied = 0;
    if (cap == 0) capres = 0;
    else capres = cL4_cap_resolve(cap);           /* thunk_FUN_00115080 */
    unsigned long c8 = copied;
    cL4_mr_ctx_init(&c8);
    u3 = cL4_mr_copy_cap(0, 0, 0, 0, &capres);   /* FUN_00381f3c */

    u5 = 4;
    if ((start & 3) != 0 && (unsigned char *)(start & 0xfffffffffffffffcULL) != 0)
        u5 = (unsigned long)*(unsigned char *)(start & 0xfffffffffffffffcULL);
    u5 = -1UL << (u5 & 0x3f);
    u3 = u3 & ~u5;
    if (u3 < 2) u3 = 1;
    w2 = cL4_waiter_next(&w, u3, 2);
    while (w2 != 0) {
        unsigned long i = (unsigned long)(w2 - 1);
        if (i < limit && (cL4_buffer_validate((unsigned long *)*(unsigned long *)(base + i*8), desc) & 1) != 0) {
            u3 = 0;
            base = base + i*8;
            goto found;
        }
        u3 = (u3 + 1) & ~u5;
        if (u3 < 2) u3 = 1;
        w2 = cL4_waiter_next(&w, u3, 2);
    }
    base = 0;
    u3 = u3 & 0xffffffff;
found:
    out.lo = base; out.hi = u3;
    return out;
}
/* FUN_00381f3c — copy one MR word from a capability pair (cL4_mr_copy_cap). */

/* FUN_00381fac @ 0x00381fac   (est. cL4_ipc_recv_wait_b)
 * Ghidra: undefined1[16] FUN_00381fac(ulong *param_1, undefined8 param_2)
 * A second IPC receive/wait loop, structurally identical to cL4_ipc_recv_wait
 * (003800cc) but keyed off the thread pointer global _DAT_006c0520 and using
 * cL4_msg_send_finalize_b (00382200) to finalize a with-registers message.
 * Empty/ready messages return the message-word low bits; otherwise it loops
 * acquiring the object reference, collects incoming registers into a fresh
 * message node, publishes it, and finalizes.
 * Confidence: medium
 */
extern unsigned long cL4_current_thread_b;   /* _DAT_006c0520 */
extern cL4_w16_t cL4_msg_send_finalize_b(unsigned long *msg_word, void *obj,
                                         unsigned int opts);   /* FUN_00382200 */

cL4_w16_t cL4_ipc_recv_wait_b(unsigned long *msg_word, unsigned long opts)
{
    cL4_w16_t out;
    unsigned long word, mkind, thread;
    long *node;
    void **pending = 0;
    void *staging;
    unsigned long alloc = 0;

    word = *msg_word;
    mkind = cL4_msg_classify(&word, 0);
    if (mkind < 2) {
        uint32_t lo = (uint32_t)word & 7;
        if (lo < 3) out.hi = (lo == 1) ? 0xff : 0x3f;
        else if (lo == 3) out.hi = 1;
        else out.hi = 0;                        /* lo==4; else fail-closed */
        out.lo = (unsigned long)(msg_word + 0xe);
        return out;
    }

    node = 0;
    staging = &cL4_current_thread_b;
    for (;;) {
        thread = cL4_current_thread_b;
        cL4_ref_acquire(cL4_current_thread_b);
        if (node != 0) cL4_ref_release((unsigned long)node);
        word = *msg_word;
        mkind = cL4_msg_classify(&word, opts);
        if (mkind != 2) break;
        node = (long *)(word & 0xfffffffffffffff0ULL);
        node[0]++;
        if (((word >> 3) & 1) == 0) goto bail;
        cL4_release(thread);
        cL4_ref_acquire((unsigned long)(node + 2));
        cL4_release((unsigned long)(node + 2));
    }
    if (mkind == 3) {
        alloc = cL4_obj_alloc();
        if (((word >> 3) & 1) == 0) {
            unsigned long *src = (unsigned long *)(word & 0xfffffffffffffff0ULL);
            if (src != 0) {
                unsigned long v0 = src[0], v1 = src[1], v2 = src[2];
                *(unsigned long *)(alloc + 0x30) = v1;
                *(unsigned long *)(alloc + 0x28) = v0;
                src[2] = 0;
                unsigned long old = *(unsigned long *)(alloc + 0x20);
                *(unsigned long *)(alloc + 0x20) = v2;
                if (old != 0) cL4_free((void*)old, 0x20);
                int had = (pending != 0);
                pending = (void**)src;
                if (had) cL4_msg_list_push((unsigned long*)&pending);
            }
        }
        *msg_word = (word & 7) | alloc | 8;
        cL4_release(thread);
        out = cL4_msg_send_finalize_b(msg_word, staging, opts);
        goto done;
    }
bail:
    cL4_release(thread);
    {
        uint32_t lo = (uint32_t)word & 7;
        if (lo < 3) out.hi = (lo == 1) ? 0xff : 0x3f;
        else if (lo == 3) out.hi = 1;
        else out.hi = 0;
        out.lo = (unsigned long)(msg_word + 0xe);
    }
done:
    if (pending != 0) cL4_msg_list_push((unsigned long*)&pending);
    cL4_msg_free(staging);
    return out;
}

/* FUN_00382200 @ 0x00382200   (est. cL4_msg_send_recv_engine)
 * Ghidra: undefined1[16] FUN_00382200(ulong *param_1, undefined8 *param_2, uint param_3)
 * The message-register send/receive engine (the -b finalize for
 * cL4_ipc_recv_wait_b). Builds a per-object dispatch table by walking the
 * caller's register groups (param_1+0x11 stride 2): for each group it reads
 * the group's flags word (*(group-8)+0x50), accumulates word counts and the
 * per-group element count, then selects a dispatch table from a fixed set
 * (0x67a550/0x67a5a8/0x67a600/0x67a6b0/0x67a718/0x67b3c0/... based on the
 * message length and element-count match). Publishes the selected table into
 * the message object, collects incoming registers (kind 3) or the object
 * header word, then finalizes the handshake: allocates a 3-word message node,
 * updates the thread's message word, releases the object locks, and returns
 * {msg+0xe, kind-lookup-table}. Any unexpected kind is a fail-closed trap.
 * Confidence: low (dispatch-table selection inferred; large state machine)
 */
cL4_w16_t cL4_msg_send_recv_engine(unsigned long *msg, unsigned long *obj, unsigned int opts)
{
    cL4_w16_t r;
    unsigned long *g1 = msg + 0x11;
    unsigned long *g2 = msg + 2;
    unsigned int u3 = opts & 0xff;
    unsigned long l90 = obj[1];
    unsigned long wordcnt = 0, len = 0, idx = 0, group, group2;
    unsigned long x, v11, g9, g10;
    unsigned int f15;
    unsigned char b4;
    unsigned long u30, u31;
    int b29, b5, b6, b7;
    unsigned long *dt;
    void *node;
    uint32_t c0, c1, c2;
    long l18;
    unsigned long x21, l27, peer, lVar18;
    uint32_t f15c;
    long *q, *q2;
    unsigned long oldq, old2;
    uint32_t fl, v9, w, piter;

    do {
        b4 = *(unsigned char *)((char*)obj + 0x11);
        if (b4 == 3) goto collect;
        u30 = msg[0xf];
        if (u30 == 0) {
            u31 = 0; b29 = 1;
        } else {
            u31 = 0; idx = 0; b29 = 1;
            do {
                group2 = g1[(idx & 0xffffffff)*2];
                x = cL4_msg_state_advance(&group2, 3);
                if (x != 0) {
                    if (0x3f < x) { u30 = 1; r.lo = group2; r.hi = 0x3f; goto publish_setup; }
                    b29 = 0;
                    if (u31 == 0 && x != 1) u31 = group2;
                }
                idx++;
            } while (u30 != idx);
        }
        g2 = msg + 2;
        msg[0xd] = (unsigned long)g2;
        u30 = msg[0xf];
        wordcnt = 0; len = 0; idx = 0; group2 = 0;
        c0 = 0; c1 = 0; c2 = 0;
        b7 = 1; b6 = 1; b5 = 1;
        if (u30 != 0) {
            g9 = 1; g10 = 0;
            do {
                v11 = g9;
                l18 = *(long *)(g1[g10*2] - 8);
                f15 = *(uint32_t *)(l18 + 0x50);
                g9 = (unsigned long)(f15 & 0xff);
                wordcnt = wordcnt + g9 & (g9 ^ ~0UL);
                (g1 + g10*2)[1] = wordcnt;
                wordcnt = wordcnt + *(long *)(l18 + 0x40);
                if (len <= g9) len = g9;
                b7 = b7 && ((f15 & 0x10000) == 0);
                b6 = b6 && ((f15 & 0x100000) == 0);
                b5 = b5 && ((f15 & 0x1100000) == 0);
                g9 = (unsigned long)((int)v11 + 1);
                g10 = v11;
            } while (u30 != v11);
            f15 = 0;
            if (!b7) f15 = 0x10000;
            c0 = 0; if (!b6) c0 = 0x100000;
            c1 = 0; if (!b5) c1 = 0x1000000;
            b6 = b6 && (len < 8 && wordcnt < 0x19);
            group2 = (uint32_t)len;
            c2 = 0; if (!b6) c2 = 0x20000;
            c2 = c0 | c1 | c2;
        }
        len = len + wordcnt & (len ^ ~0UL);
        *(uint32_t *)(msg + 0xc) = c2 | (uint32_t)group2 | f15;
        if (len < 2) len = 1;
        msg[10] = wordcnt;
        msg[0xb] = len;
        if (u30 == 0) {
            *(uint32_t *)((char*)msg + 100) = 0;
            b7 = 1; b5 = 1;
            goto table_done;
        } else {
            x = 0; f15c = 0xffffffff; piter = 0; w = 0;
            do {
                fl = *(uint32_t *)(*(long *)(g1[piter*2] - 8) + 0x54);
                v9 = (uint32_t)x;
                if (fl <= w) { fl = w; v9 = f15c; }
                f15c = v9; x++;
                piter++;
                w = fl;
            } while ((u30 & 0xffffffff) != x);
            *(uint32_t *)((char*)msg + 100) = w;
            if (w == 0) { b7 = 1; b5 = 1; goto table_done; }
            b7 = 0;
            *(uint32_t *)(msg + 1) = f15c;
            b5 = 0;
        }
table_done:
        if (b6) {
            if (f15 == 0) {
                if (wordcnt == 8) { if (!b7) goto dt_default; dt = (unsigned long*)0x67a6b0; }
                else if (wordcnt == 4) { if (!b7) goto dt_default; dt = (unsigned long*)0x67a600; }
                else if (wordcnt == 2) { if (len == 1) dt = (unsigned long*)0x67a5a8; else goto dt_default; }
                else if (wordcnt == 1) { if (!b7) goto dt_default; dt = (unsigned long*)0x67a550; }
                else goto dt_default;
            } else dt = (unsigned long*)0x67b418;
        } else if (f15 == 0) dt = (unsigned long*)0x67b470;
        else dt = (unsigned long*)0x67b4c8;
        u30 = *dt;
        g2[0] = u30;
        msg[3] = dt[1]; msg[4] = dt[2]; msg[5] = dt[3];
        msg[6] = dt[4]; msg[7] = dt[5]; msg[8] = dt[6]; msg[9] = dt[7];
        if (b29) {
            r.lo = 0; r.hi = 0;
            u30 = 4;
        } else {
            if (u31 == 0) goto collect;
            u30 = 3; r.lo = u31; r.hi = 1;
        }
        goto publish_setup;
dt_default:
        dt = (unsigned long*)0x67b3c0;
        u30 = *dt;
        g2[0] = u30;
        msg[3] = dt[1]; msg[4] = dt[2]; msg[5] = dt[3];
        msg[6] = dt[4]; msg[7] = dt[5]; msg[8] = dt[6]; msg[9] = dt[7];
        if (b29) { r.lo = 0; r.hi = 0; u30 = 4; }
        else { if (u31 == 0) goto collect; u30 = 3; r.lo = u31; r.hi = 1; }
        goto publish_setup;
collect:
        r = cL4_msg_collect((long)(msg + 0xe));
        u30 = (r.lo == 0) ? 4 : 3;
publish_setup:
        x21 = r.hi;
        lVar18 = (long)r.lo;
        f15c = (uint32_t)u30;
        *(char *)((char*)obj + 0x11) = (char)u30;
        if ((lVar18 == 0) || (2 < ((f15c - 1) & 0xff))) {
            node = 0;
            l27 = *(unsigned long *)(l90 + 0x20);
            *(unsigned long *)(l90 + 0x20) = 0;
            if (lVar18 != 0 || l27 != 0) {
                node = cL4_alloc(0x20, 0x1060c4048d9c6c4ULL);
                *(cL4_w16_t*)node = r;
                *(unsigned long *)((char*)node + 8) = l27;
            }
            peer = *(unsigned long *)*obj;
            cL4_ref_acquire(peer);
            *msg = (unsigned long)node | u30;
            cL4_release(obj[1] + 0x10);
            cL4_ref_release(obj[1]);
            cL4_release(peer);
            *(unsigned short *)((char*)obj + 0x10) = 0;
            obj[1] = 0;
            r.lo = (unsigned long)(msg + 0xe);
            r.hi = *(unsigned long *)(((unsigned long)(f15c - 1) & 0xff) * 8 + 0x4f27b0);
            return r;
        }
        if (u3 < 0x3f) {
            if (u3 != 0) { if (u3 != 1) goto trap; if (2 < f15c) goto wake; }
        } else {
            if (u3 != 0x3f) { if (u3 != 0xff) { trap: __asm__ volatile("brk #1" ::: "memory"); r.lo=r.hi=0; return r; } goto publish_alt; }
            if (1 < f15c) { wake: l90 = obj[1]; }
publish_alt:
            l27 = *(unsigned long *)(l90 + 0x20);
            *(unsigned long *)(l90 + 0x20) = 0;
            node = cL4_alloc(0x20, 0x1060c4048d9c6c4ULL);
            *(cL4_w16_t*)node = r;
            *(unsigned long *)((char*)node + 8) = l27;
            peer = *(unsigned long *)*obj;
            cL4_ref_acquire(peer);
            *msg = (unsigned long)node | u30;
            cL4_release(obj[1] + 0x10);
            cL4_ref_release(obj[1]);
            cL4_release(peer);
            *(unsigned short *)((char*)obj + 0x10) = 0;
            obj[1] = 0;
            r.lo = (unsigned long)(msg + 0xe);
            r.hi = *(unsigned long *)(((unsigned long)(f15c - 1) & 0xff) * 8 + 0x4f27b0);
            return r;
        }
        if ((opts >> 8 & 1) != 0) goto publish_alt;
        if (b4 < u30) {
            peer = *(unsigned long *)*obj;
            cL4_ref_acquire(peer);
            q = (long*)obj[1];
            q2 = q;
            if (*q != 1) {
                q2 = (long*)cL4_obj_alloc();
                oldq = q[4];
                q[4] = 0;
                old2 = q2[4];
                q2[4] = oldq;
                if (old2 != 0) cL4_free((void*)old2, 0x20);
            }
            *(cL4_w16_t*)(q2 + 5) = r;
            *msg = (unsigned long)*(unsigned char *)((char*)obj + 0x11) | (unsigned long)q2 | 8;
            if (q2 != q) {
                cL4_release(obj[1] + 0x10);
                cL4_ref_release(obj[1]);
                obj[1] = (unsigned long)q2;
            }
            cL4_release(peer);
            l90 = obj[1];
        }
        cL4_msg_handshake((long)(msg + 0xe), opts & 0xff, (long)r.lo, r.hi);
    } while (1);
}

/* ------------------------------------------------------------------ *
 * Register-copy helper family. Each copies a fixed number of words from a
 * source register/object (param_2) into a destination (param_1), optionally
 * resolving the object's copy stride via FUN_0036b270 (forward) / FUN_0036b118
 * (reverse). The variants differ only in the number of words copied and which
 * object-resolution helper runs.
 * ------------------------------------------------------------------ */

/* FUN_0036b118 @ 0x36b118 — reverse copy-stride resolution helper. */
extern void cL4_obj_copy_reverse(void *src);

/* 1-word copy, forward stride (FUN_00384344 / 00385b7c / 00385e5c). */
long cL4_reg_copy1_f(unsigned long *dst, unsigned long *src)
{
    unsigned long v = *src;
    *dst = v;
    cL4_obj_copy_advance();
    return (long)src + (*(unsigned char *)(*(long *)((long)src - 8) + 0x50) + 0x10 &
            (*(unsigned char *)(*(long *)((long)src - 8) + 0x50) ^ ~0UL));
}

/* 2-word copy, forward stride (FUN_003858c8/cc/fc/00). */
unsigned long cL4_reg_copy2_f(unsigned long *dst, unsigned long *src)
{
    unsigned long v = *src;
    dst[1] = src[1];
    *dst = v;
    cL4_obj_copy_advance();
    return 0;
}
/* 2-word copy, reverse stride (FUN_00385938/3c). */
unsigned long cL4_reg_copy2_r(unsigned long *dst, unsigned long *src)
{
    unsigned long v = *src;
    dst[1] = src[1];
    *dst = src[1];
    cL4_obj_copy_reverse(&v);
    return 0;
}
/* 2-word copy, forward+reverse (FUN_003859b4/b8). */
unsigned long cL4_reg_copy2_fr(unsigned long *dst, unsigned long *src)
{
    unsigned long v = *src;
    dst[1] = src[1];
    *dst = src[1];
    cL4_obj_copy_advance();
    cL4_obj_copy_reverse(0);
    return 0;
}

/* 3-word copy, forward stride (FUN_003859fc/5a00/5a38/5a3c). */
unsigned long cL4_reg_copy3_f(unsigned long *dst, unsigned long *src)
{
    unsigned long v0 = *src, v1 = src[1], v2 = *src;
    dst[2] = src[2];
    dst[1] = v1;
    *dst = v2;
    cL4_obj_copy_advance();
    return 0;
}
/* 3-word copy, reverse stride (FUN_00385a84/88). */
unsigned long cL4_reg_copy3_r(unsigned long *dst, unsigned long *src)
{
    unsigned long v0 = *src, v1 = src[1], v2 = *src;
    dst[2] = src[2];
    dst[1] = v1;
    *dst = v2;
    cL4_obj_copy_reverse(&v0);
    return 0;
}
/* 3-word copy, forward+reverse (FUN_00385b08/0c). */
unsigned long cL4_reg_copy3_fr(unsigned long *dst, unsigned long *src)
{
    unsigned long v0 = *src, v1 = src[1], v2 = *src;
    dst[2] = src[2];
    dst[1] = v1;
    *dst = v2;
    cL4_obj_copy_advance();
    cL4_obj_copy_reverse(0);
    return 0;
}

/* FUN_00385bb4 @ 0x00385bb4 — bulk copy via the object's size op then advance. */
unsigned long cL4_reg_copy_sized(unsigned long dst, unsigned long *src, long obj)
{
    unsigned long v = *src;
    cL4_obj_copy_simple(dst, (long)src, *(unsigned long *)(*(long *)(obj - 8) + 0x48));
    cL4_obj_copy_advance();
    return dst;
}
/* FUN_00385c18 — bulk copy with reverse stride. */
unsigned long *cL4_reg_copy_sized_r(unsigned long *dst, unsigned long src, long obj)
{
    unsigned long v = *dst;
    cL4_obj_copy_simple((long)dst, (long)&src, *(unsigned long *)(*(long *)(obj - 8) + 0x48));
    cL4_obj_copy_reverse(&v);
    return dst;
}
/* FUN_00385dcc — bulk copy with forward+reverse stride. */
unsigned long *cL4_reg_copy_sized_fr(unsigned long *dst, unsigned long *src, long obj)
{
    unsigned long v1 = *src, v2 = *dst;
    cL4_obj_copy_simple((long)dst, (long)src, *(unsigned long *)(*(long *)(obj - 8) + 0x48));
    cL4_obj_copy_advance();
    cL4_obj_copy_reverse(&v2);
    return dst;
}
/* FUN_00385efc — 5-word copy dispatching on the object flag bit1 at
 * *(obj-8)+0x52: clear -> slot-0x10 element copy; set -> word copy + advance. */
unsigned long *cL4_reg_copy5_disp(unsigned long *dst, unsigned long *src)
{
    unsigned long v = src[3];
    dst[4] = src[4];
    dst[3] = v;
    if ((*(unsigned char *)(*(long *)(src[3] - 8) + 0x52) >> 1 & 1) == 0) {
        (**(void (**)(unsigned long*))(*(long *)(src[3] - 8) + 0x10))(dst);
    } else {
        *dst = *src;
        cL4_obj_copy_advance();
    }
    return dst;
}

/* FUN_00383968 @ 0x00383968   (est. cL4_msg_node_alloc_fixed2)
 * Ghidra: node = alloc(0x10, 0xa1c40bd48d6d6); node[0]=0x67b578; node[1]=obj[1]
 * Allocates a 0x10-byte message node with dispatch table 0x67b578.
 * Confidence: medium
 */
void cL4_msg_node_alloc_fixed2(long obj)
{
    unsigned long *node = cL4_alloc(0x10, 0xa1c40bd48d6d6ULL);
    node[0] = 0x67b578;
    node[1] = *(unsigned long *)(obj + 8);
}

/* FUN_003842b0 @ 0x003842b0   (est. cL4_hash_mix)
 * Ghidra: long FUN_003842b0(uint param_1)
 * A 3-round integer mix (splitmix-style finalizer) over param_1*8 + const.
 * Confidence: medium
 */
unsigned long cL4_hash_mix(uint32_t v)
{
    unsigned long x = ((unsigned long)v * 8 + (unsigned long)-0x6fff59c56fff59fLL) * (unsigned long)-0x622015f714c7d297LL;
    x = (x ^ x >> 0x2f) * (unsigned long)-0x622015f714c7d297LL;
    return (x ^ x >> 0x2f) * (unsigned long)-0x622015f714c7d297LL;
}

/* ------------------------------------------------------------------ *
 * Object-copy dispatch family (FUN_00384554 / 00384740 / 0038493c /
 * 00385f64). Copy the contents of one message/buffer object (param_2) into
 * another (param_1). When both carry the same object tag (param[3]) and the
 * object's flag bit1 (*(obj-8)+0x52) is clear, they call the object's
 * same-type copy op (*(obj-8)+0x18/0x28). When the tags differ they run the
 * 3-word source/dest copy sequence: source-setup op (*(src-8)+0x20), bulk copy
 * of the payload, then dest-setup op (*(dst-8)+0x8). Variants differ in the
 * destination op slot (0x10/0x20) and whether a fixed-size bulk copy
 * (FUN_00117cc4 with size-0x18) is inserted.
 * ------------------------------------------------------------------ */

/* FUN_00384554 — same/diff-tag 4-word copy (dest slot 0x10). */
unsigned long *cL4_obj_copy4(unsigned long *dst, unsigned long *src)
{
    long srcobj, dstobj;
    unsigned long tmp[3];
    if (src == dst) return dst;
    if (src[3] == dst[3]) {
        if ((*(unsigned char *)(*(long *)(src[3] - 8) + 0x52) >> 1 & 1) == 0) {
            (**(void (**)(unsigned long*,unsigned long*,long))(*(long *)(src[3] - 8) + 0x18))(dst, src, src[3]);
            return dst;
        }
        *dst = *src;
        cL4_obj_copy_advance();
    } else {
        dstobj = *(long *)(dst[3] - 8);
        long s = dstobj; if (s == 0) s = 0;
        srcobj = *(long *)(src[3] - 8);
        long d = srcobj; if (d == 0) d = 0;
        if ((*(unsigned char *)(s + 0x52) >> 1 & 1) == 0) {
            (**(void (**)(unsigned long*,unsigned long*,long))(dstobj + 0x20))(tmp, dst, dst[3]);
            dst[3] = src[3];
            if ((*(unsigned char *)(d + 0x52) >> 1 & 1) == 0)
                (**(void (**)(unsigned long*,unsigned long*,long))(*(long *)(src[3] - 8) + 0x10))(dst, src, src[3]);
            else { *dst = *src; cL4_obj_copy_advance(); }
            (**(void (**)(unsigned long*,long))(*(long *)(dst[3] - 8) + 8))(tmp, dst[3]);
            return dst;
        }
        unsigned long v = *dst;
        dst[3] = src[3];
        if ((*(unsigned char *)(d + 0x52) >> 1 & 1) == 0)
            (**(void (**)(unsigned long*,unsigned long*,long))(*(long *)(src[3] - 8) + 0x10))(dst, src, src[3]);
        else { *dst = *src; cL4_obj_copy_advance(); }
        cL4_obj_copy_reverse(&v);
    }
    return dst;
}

/* FUN_00384740 — 5-word copy (dest slot 0x10, copies dst[4] too). */
unsigned long *cL4_obj_copy5(unsigned long *dst, unsigned long *src)
{
    long srcobj, dstobj;
    unsigned long tmp[3];
    if (src == dst) return dst;
    if (src[3] == dst[3]) {
        if ((*(unsigned char *)(*(long *)(src[3] - 8) + 0x52) >> 1 & 1) == 0) {
            (**(void (**)(unsigned long*,unsigned long*,long))(*(long *)(src[3] - 8) + 0x18))(dst, src, src[3]);
            return dst;
        }
        *dst = *src;
        cL4_obj_copy_advance();
    } else {
        dstobj = *(long *)(dst[3] - 8);
        long s = dstobj; if (s == 0) s = 0;
        srcobj = *(long *)(src[3] - 8);
        long d = srcobj; if (d == 0) d = 0;
        if ((*(unsigned char *)(s + 0x52) >> 1 & 1) == 0) {
            (**(void (**)(unsigned long*,unsigned long*,long))(dstobj + 0x20))(tmp, dst, dst[3]);
            dst[4] = src[4];
            dst[3] = src[3];
            if ((*(unsigned char *)(d + 0x52) >> 1 & 1) == 0)
                (**(void (**)(unsigned long*,unsigned long*,long))(*(long *)(src[3] - 8) + 0x10))(dst, src, src[3]);
            else { *dst = *src; cL4_obj_copy_advance(); }
            (**(void (**)(unsigned long*,long))(*(long *)(dst[3] - 8) + 8))(tmp, dst[3]);
            return dst;
        }
        unsigned long v = *dst;
        dst[4] = src[4];
        dst[3] = src[3];
        if ((*(unsigned char *)(d + 0x52) >> 1 & 1) == 0)
            (**(void (**)(unsigned long*,unsigned long*,long))(*(long *)(src[3] - 8) + 0x10))(dst, src, src[3]);
        else { *dst = *src; cL4_obj_copy_advance(); }
        cL4_obj_copy_reverse(&v);
    }
    return dst;
}

/* FUN_0038493c — copy with fixed-size payload copy (size-0x18). */
unsigned long *cL4_obj_copy_fixed(unsigned long *dst, unsigned long *src, long obj)
{
    long srcobj, dstobj;
    unsigned long tmp[3];
    if (src == dst) return dst;
    if (src[3] == dst[3]) {
        if ((*(unsigned char *)(*(long *)(src[3] - 8) + 0x52) >> 1 & 1) == 0) {
            (**(void (**)(unsigned long*,unsigned long*,long))(*(long *)(src[3] - 8) + 0x18))(dst, src, src[3]);
            return dst;
        }
        *dst = *src;
        cL4_obj_copy_advance();
    } else {
        dstobj = *(long *)(dst[3] - 8);
        long s = dstobj; if (s == 0) s = 0;
        srcobj = *(long *)(src[3] - 8);
        long d = srcobj; if (d == 0) d = 0;
        if ((*(unsigned char *)(s + 0x52) >> 1 & 1) == 0) {
            (**(void (**)(unsigned long*,unsigned long*,long))(dstobj + 0x20))(tmp, dst, dst[3]);
            cL4_obj_copy_simple((long)(dst+3), (long)(src+3), *(long *)(*(long *)(obj - 8) + 0x48) + -0x18);
            if ((*(unsigned char *)(d + 0x52) >> 1 & 1) == 0)
                (**(void (**)(unsigned long*,unsigned long*,long))(*(long *)(src[3] - 8) + 0x10))(dst, src, src[3]);
            else { *dst = *src; cL4_obj_copy_advance(); }
            (**(void (**)(unsigned long*,long))(*(long *)(dst[3] - 8) + 8))(tmp, dst[3]);
            return dst;
        }
        unsigned long v = *dst;
        cL4_obj_copy_simple((long)(dst+3), (long)(src+3), *(long *)(*(long *)(obj - 8) + 0x48) + -0x18);
        if ((*(unsigned char *)(d + 0x52) >> 1 & 1) == 0)
            (**(void (**)(unsigned long*,unsigned long*,long))(*(long *)(src[3] - 8) + 0x10))(dst, src, src[3]);
        else { *dst = *src; cL4_obj_copy_advance(); }
        cL4_obj_copy_reverse(&v);
    }
    return dst;
}

/* FUN_00385f64 — same/diff-tag copy (dest slot 0x20, copies dst[4]). */
unsigned long *cL4_obj_copy5_slot20(unsigned long *dst, unsigned long *src)
{
    long srcobj, dstobj;
    unsigned long tmp[3];
    if (src == dst) return dst;
    if (src[3] == dst[3]) {
        if ((*(unsigned char *)(*(long *)(src[3] - 8) + 0x52) >> 1 & 1) == 0) {
            (**(void (**)(unsigned long*,unsigned long*,long))(*(long *)(src[3] - 8) + 0x28))(dst, src, src[3]);
            return dst;
        }
        unsigned long v = *dst;
        *dst = *src;
    } else {
        dstobj = *(long *)(dst[3] - 8);
        long s = dstobj; if (s == 0) s = 0;
        srcobj = *(long *)(src[3] - 8);
        long d = srcobj; if (d == 0) d = 0;
        if ((*(unsigned char *)(s + 0x52) >> 1 & 1) == 0) {
            (**(void (**)(unsigned long*,unsigned long*,long))(dstobj + 0x20))(tmp, dst, dst[3]);
            dst[4] = src[4];
            dst[3] = src[3];
            if ((*(unsigned char *)(d + 0x52) >> 1 & 1) == 0)
                (**(void (**)(unsigned long*,unsigned long*,long))(*(long *)(src[3] - 8) + 0x20))(dst, src, src[3]);
            else { *dst = *src; }
            (**(void (**)(unsigned long*,long))(*(long *)(dst[3] - 8) + 8))(tmp, dst[3]);
            return dst;
        }
        unsigned long v = *dst;
        dst[4] = src[4];
        dst[3] = src[3];
        if ((*(unsigned char *)(d + 0x52) >> 1 & 1) == 0)
            (**(void (**)(unsigned long*,unsigned long*,long))(*(long *)(src[3] - 8) + 0x20))(dst, src, src[3]);
        else { *dst = *src; }
        cL4_obj_copy_reverse(&v);
    }
    return dst;
}

/* ------------------------------------------------------------------ *
 * Waiter-scan variants. Each scans the blocked waiters (via cL4_waiter_next
 * over the wait-set word) for one matching a key, returning {index, ptr}.
 * ------------------------------------------------------------------ */

/* FUN_00383a1c — match waiter whose object's +0x18 field == key (*param_1). */
cL4_w16_t cL4_waiter_scan_field18(unsigned long key, unsigned long start,
                                  unsigned long limit, long base)
{
    cL4_w16_t out;
    unsigned long w = start, u2, u3, i;
    unsigned char type;
    int w2;
    u2 = cL4_waiter_hash(key);                    /* FUN_0036becc(*param_1) */
    u3 = 4;
    if ((start & 3) != 0 && (unsigned char *)(start & 0xfffffffffffffffcULL) != 0)
        u3 = (unsigned long)*(unsigned char *)(start & 0xfffffffffffffffcULL);
    u3 = -1UL << (u3 & 0x3f);
    u2 = u2 & ~u3;
    if (u2 < 2) u2 = 1;
    w2 = cL4_waiter_next(&w, u2, 2);
    while (w2 != 0) {
        i = (unsigned long)(w2 - 1);
        if (i < limit && key == *(unsigned long *)(*(unsigned long *)(base + i*8) + 0x18)) {
            u2 = 0; base = base + i*8; goto found;
        }
        u2 = (u2 + 1) & ~u3;
        if (u2 < 2) u2 = 1;
        w2 = cL4_waiter_next(&w, u2, 2);
    }
    base = 0; u2 &= 0xffffffff;
found:
    out.lo = base; out.hi = u2; return out;
}
/* FUN_0036becc @ 0x36becc — waiter-scan hash of a key. */
extern unsigned long cL4_waiter_hash(unsigned long key);

/* FUN_003841b8 — match waiter whose object's +0x40 field (as a count index)
 * matches key. */
cL4_w16_t cL4_waiter_scan_field40(int key, unsigned long start,
                                  unsigned long limit, long base)
{
    cL4_w16_t out;
    unsigned long w = start, u2, u3, i;
    int w2;
    u2 = cL4_hash_mix((uint32_t)key);             /* FUN_003842b0(*param_1) */
    u3 = 4;
    if ((start & 3) != 0 && (unsigned char *)(start & 0xfffffffffffffffcULL) != 0)
        u3 = (unsigned long)*(unsigned char *)(start & 0xfffffffffffffffcULL);
    u3 = -1UL << (u3 & 0x3f);
    u2 = u2 & ~u3;
    if (u2 < 2) u2 = 1;
    w2 = cL4_waiter_next(&w, u2, 2);
    while (w2 != 0) {
        i = (unsigned long)(w2 - 1);
        if (i < limit &&
            key == (int)((*(unsigned long *)(*(unsigned long *)(base + i*8) + 0x40) + 0x7fffffff8ULL) >> 3)) {
            u2 = 0; base = base + i*8; goto found;
        }
        u2 = (u2 + 1) & ~u3;
        if (u2 < 2) u2 = 1;
        w2 = cL4_waiter_next(&w, u2, 2);
    }
    base = 0; u2 &= 0xffffffff;
found:
    out.lo = base; out.hi = u2; return out;
}

/* FUN_00384b74 @ 0x00384b74   (est. cL4_waiter_match_cap)
 * Ghidra: bool FUN_00384b74(long param_1, long *param_2)
 * Matches a waiter against a capability descriptor: compares the sign/flag
 * word, the optional capability selector (*(obj+0x18) when flag bit30), the
 * length field, and (when present) each capability word. Returns true only if
 * every field matches.
 * Confidence: medium
 */
int cL4_waiter_match_cap(unsigned long *obj, unsigned long *desc)
{
    uint32_t u1 = *(uint32_t *)(desc + 1);
    uint32_t u2 = *(uint32_t *)(obj + 0x10);
    if ((((int32_t)u2 < 0) ^ u1) & 1) return 0;
    unsigned long sel;
    if ((u2 >> 0x1e & 1) == 0) sel = 0; else sel = *(unsigned long *)(obj + 0x18);
    if (*desc != sel) return 0;
    if (u1 >> 1 != *(uint32_t *)(obj + 0x14)) return 0;
    if (u1 < 2) return 1;
    unsigned long *p4 = (unsigned long *)(obj + ((u2 >> 0x1e) & 1)*1 + 0x18);
    unsigned long *p5 = (unsigned long *)desc[2];
    unsigned long n = (unsigned long)(u1 >> 1);
    do {
        n--;
        if (*p5 != *p4) return 0;
        p4++; p5++;
    } while (n != 0);
    return 1;
}

/* FUN_00384c08 — waiter scan using cL4_waiter_match_cap. */
cL4_w16_t cL4_waiter_scan_cap(unsigned long *desc, unsigned long start,
                              unsigned long limit, long base)
{
    cL4_w16_t out;
    unsigned long w = start, u2, u3, i;
    int w2;
    u2 = cL4_mr_collect_state();                  /* FUN_00384cec() */
    u3 = 4;
    if ((start & 3) != 0 && (unsigned char *)(start & 0xfffffffffffffffcULL) != 0)
        u3 = (unsigned long)*(unsigned char *)(start & 0xfffffffffffffffcULL);
    u3 = -1UL << (u3 & 0x3f);
    u2 = u2 & ~u3;
    if (u2 < 2) u2 = 1;
    w2 = cL4_waiter_next(&w, u2, 2);
    while (w2 != 0) {
        i = (unsigned long)(w2 - 1);
        if (i < limit && (cL4_waiter_match_cap((unsigned long *)*(unsigned long *)(base + i*8), desc) & 1)) {
            u2 = 0; base = base + i*8; goto found;
        }
        u2 = (u2 + 1) & ~u3;
        if (u2 < 2) u2 = 1;
        w2 = cL4_waiter_next(&w, u2, 2);
    }
    base = 0; u2 &= 0xffffffff;
found:
    out.lo = base; out.hi = u2; return out;
}

/* FUN_00384cec — collect the capability-descriptor message (canary-protected
 * copy of the waiter's cap word + list into a fresh MR copy context). */
void cL4_waiter_collect_cap(unsigned long *desc)
{
    unsigned char c1 = (unsigned char)(*(uint32_t *)(desc + 1) & 1);
    unsigned long d0 = ((unsigned long)(*(uint32_t *)(desc + 1) >> 1) << 32);
    unsigned char ctx1[56], ctx2[64];
    unsigned long local_b8, acc;
    unsigned long canary = (unsigned long)-0x2c8502b44bfffed6ULL;
    cL4_mr_ctx_init(ctx1);
    local_b8 = *desc;
    acc = cL4_mr_copy6_disp(&local_b8, 0, ctx1, ctx2, &c1, &d0);
    if (1 < *(uint32_t *)(desc + 1)) {
        for (unsigned long i = 0; i < *(uint32_t *)(desc + 1) >> 1; i++) {
            d0 = *(unsigned long *)(desc[2] + i*8);
            cL4_mr_ctx_init(ctx1);
            cL4_mr_copy6(local_b8, 0, (unsigned long)ctx1, (unsigned long)ctx2, &acc, &d0);
        }
    }
    if (canary == (unsigned long)-0x2c8502b44bfffed6ULL) return;
    cL4_stack_fail();
}
/* FUN_00384de4 — 2-word MR copy with word-table second step. */
unsigned long cL4_mr_copy6_disp(unsigned long *reg, unsigned long acc0, void *c1, void *c2,
                                unsigned char *c, unsigned long *d0);

/* FUN_00384e60 @ 0x00384e60   (est. cL4_mr_copy_shifted)
 * Ghidra: undefined1* FUN_00384e60(param_1, long *param_2, param_3, param_4, param_5)
 * A shifted message-register copy: when the destination range is shorter than
 * one word it copies the partial byte(s) and loads the object's register
 * buffer (FUN_0037e58c) into param_1+0x40..0x70, then stores the running
 * count at *param_2; otherwise it appends the word to the copy context.
 * Confidence: low
 */
unsigned char *cL4_mr_copy_shifted(unsigned char *dst, unsigned long *acc, unsigned char *src,
                                   unsigned char *end, unsigned char byte)
{
    unsigned char *r;
    if (end < src + 1) {
        long n = (long)end - (long)src;
        unsigned char local_31 = byte;
        cL4_obj_copy_simple((long)src, (long)&local_31, n);
        if (*acc == 0) {
            unsigned char reg[7];
            cL4_simd_copy_begin(&reg[0], (unsigned long)dst, *(unsigned long *)(dst + 0x78));
            *(unsigned long *)(dst + 0x48) = reg[1];
            *(unsigned long *)(dst + 0x40) = reg[0];
            *(unsigned long *)(dst + 0x58) = reg[3];
            *(unsigned long *)(dst + 0x50) = reg[2];
            *(unsigned long *)(dst + 0x68) = reg[5];
            *(unsigned long *)(dst + 0x60) = reg[4];
            *(unsigned long *)(dst + 0x70) = reg[6];
            *acc = 0x40;
        } else {
            cL4_simd_copy_loop(dst + 0x40, (unsigned long)dst);
            *acc = *acc + 0x40;
        }
        r = dst;
        if (dst + (1 - n) <= end) {
            cL4_obj_copy_simple((long)dst, (long)(&local_31 + n), 1);
            r = dst + (1 - n);
        }
    } else {
        *src = byte;
        r = src + 1;
    }
    return r;
}

/* ------------------------------------------------------------------ *
 * Object-table lookup-with-resize. FUN_00384f48 implements two duplicated
 * lookups: an object pointer by ID (table base _DAT_006c0830/0x838/0x840,
 * hash FUN_003841b8) and a capability by ID (table base _DAT_006c0880/0x888/
 * 0x890, hash FUN_00386160). Both share the same structure: fast-path hit
 * check against the cached last-lookup (_DAT_006c0878/0x8c8), then under
 * LOAcquire a linear probe; on miss and load-factor >3/4 it grows the hash
 * table (FUN_00010244, rehash via FUN_0035b178/FUN_0035b588), allocates the
 * entry table (FUN_000101a0), installs the per-entry object copy-dispatch
 * block, and finally registers the new ID. Deferred frees are drained when
 * the acquire counter hits 0.
 * ------------------------------------------------------------------ */

/* FUN_00361718 @ 0x361718 — push a deferred-free descriptor onto a list. */
extern void cL4_deferred_free_push(unsigned long n, void *ctx, unsigned long tag);
/* FUN_0035b228 @ 0x35b228 — release the deferred-free batch / handoff ctx. */
extern void cL4_handoff_release(void *ctx);
/* FUN_00010244 @ 0x10244 — allocate a hash bucket array (type flags). */
extern void *cL4_bucket_alloc(unsigned long n, unsigned int kind, unsigned long tag);
/* FUN_000101a0 @ 0x101a0 — allocate a table/slot block. */
extern void *cL4_slot_alloc(unsigned long size, unsigned long tag);
/* FUN_0001279c @ 0x1279c — round size up for the table. */
extern unsigned long cL4_table_round(unsigned long size);
/* FUN_0001062c @ 0x1062c — allocate the per-entry object-dispatch block. */
extern int cL4_entry_dispatch_alloc(unsigned long *out, int a, int b, unsigned long tag);
/* FUN_0035b588 @ 0x35b588 — insert a bucket-entry pair. */
extern void cL4_bucket_insert(unsigned long *tbl, unsigned long *head, unsigned long slot,
                              unsigned long hash, int mode);
/* FUN_00117cc8 @ 0x117cc8 — bulk copy of the bucket table. */
extern void cL4_bucket_copy(void *dst, void *src, unsigned long n, unsigned long pad);

#define LOAcquire()   /* opaque cL4 lock acquire */
#define LORelease()   /* opaque cL4 lock release */
#define DataMemoryBarrier(a,b) __asm__ volatile("dmb ish" ::: "memory")

/* Table-1 globals (object pointers by id). */
extern unsigned long cL4_tbl1_count;     /* _DAT_006c0830 */
extern unsigned long cL4_tbl1_load;      /* _DAT_006c0834 */
extern unsigned int *cL4_tbl1_entries;   /* _DAT_006c0838 */
extern unsigned long *cL4_tbl1_head;     /* _DAT_006c0840 */
extern unsigned long *cL4_tbl1_cache;    /* _DAT_006c0878 */
extern unsigned long *cL4_tbl1_freelist; /* _DAT_006c0870 */
/* Table-2 globals (capabilities by id). */
extern unsigned long cL4_tbl2_count;     /* _DAT_006c0880 */
extern unsigned long cL4_tbl2_load;      /* _DAT_006c0884 */
extern unsigned int *cL4_tbl2_entries;   /* _DAT_006c0888 */
extern unsigned long *cL4_tbl2_head;     /* _DAT_006c0890 */
extern unsigned long *cL4_tbl2_cache;    /* _DAT_006c08c8 */
extern unsigned long *cL4_tbl2_freelist; /* _DAT_006c08c0 */

/* Table-2 entry-initializer (FUN_00386328). */
extern void cL4_tbl2_entry_init(unsigned long *entry, unsigned long id);

/* One half of FUN_00384f48: object-pointer lookup/insert into table 1. */
static unsigned long *cL4_tbl1_lookup_insert(unsigned long id, uint32_t mode)
{
    unsigned long *found, *h = cL4_tbl1_head, *cache = cL4_tbl1_cache;
    unsigned int n, load, u;
    unsigned long old_head, hash, mask, idx;
    unsigned int *ent;
    uint32_t e0, e1, f, u2, k, c0, c1, c2;
    void *tmp, *entry, *bucket;
    unsigned long local_70, local_68;
    int r;

    if (cL4_tbl1_cache != 0 && id == (uint32_t)((cL4_tbl1_cache[8] + 0x7fffffff8ULL) >> 3))
        return cL4_tbl1_cache;
    LOAcquire();
    cL4_tbl1_count++;
    unsigned long key = id;
    cL4_w16_t scan0 = cL4_waiter_scan_field40((int)key, (unsigned long)cL4_tbl1_head,
                              cL4_tbl1_load, (long)(cL4_tbl1_entries + 2));
    if (cL4_tbl1_entries == 0 || cL4_tbl1_head == 0 || cL4_tbl1_load == 0 || scan0.lo == 0) {
        unsigned long n0 = cL4_tbl1_count;
        cL4_tbl1_count--;
        LORelease();
        cL4_deferred_free_push(n0, 0, 0x6c0850);
        found = cL4_tbl1_head;
        ent = cL4_tbl1_entries;
        u = (uint32_t)cL4_tbl1_load;
        old_head = (unsigned long)cL4_tbl1_head;
        hash = ((unsigned long)cL4_tbl1_head & 3) != 0 ? *(unsigned char *)((unsigned long)cL4_tbl1_head & ~3UL) : 4;
        mask = (unsigned long)cL4_tbl1_load;
        unsigned int *pe = cL4_tbl1_entries + 2;
        unsigned int *pe2 = (cL4_tbl1_entries != 0) ? pe : 0;
        unsigned long lk = id;
        cL4_w16_t res = cL4_waiter_scan_field40((int)lk, (unsigned long)cL4_tbl1_head, mask, (long)pe2);
        unsigned long resi = res.hi;
        if (res.lo == 0) {
            unsigned long cap = 1UL << (hash & 0x3f);
            unsigned long load1 = (unsigned long)(u + 1);
            unsigned long rem = cap - load1;
            unsigned long loadf = (rem != 0) ? cap / rem : 0;
            if (3 < loadf) {
                /* grow the bucket table */
                old_head = (unsigned long)found;
                unsigned long nb = (unsigned long)((uint32_t)hash + 1);
                unsigned long nbk = nb & 0xff;
                uint32_t bk = (0x10 < nbk) ? 4 : ((nbk < 9) ? 1 : 2);
                bucket = cL4_bucket_alloc(2UL << (hash & 0x3f), bk, 0x48dda4ae);
                if (bucket == 0) goto fail;
                found = (unsigned long *)((unsigned long)((bk==1)?1:(bk==4)?3:2) | (unsigned long)bucket);
                *(unsigned char *)bucket = (unsigned char)((uint32_t)hash + 1);
                if ((int)hash != 0) {
                    for (unsigned long i2 = 1; (i2 >> (hash & 0x3f)) == 0; i2++) {
                        unsigned long v = cL4_waiter_next(&old_head, i2, 0);
                        if (v != 0) {
                            unsigned long h2 = cL4_hash_mix((uint32_t)((*(unsigned long *)(pe + (v-1)*2) + 0x7fffffff8ULL) >> 3));
                            while ((h2 = h2 & ~(-2UL << (hash & 0x3f))), h2 == 0 ||
                                   (r = cL4_waiter_next(&found, h2, 0), r != 0)) h2++;
                            cL4_bucket_insert(&found, 0, v, h2, 0);
                        }
                    }
                }
                cL4_tbl1_head = found;
                if (pe != 0) {
                    unsigned long *ln = cL4_slot_alloc(0x10, 0xa0040aff93c70);
                    *ln = (unsigned long)cL4_tbl1_freelist;
                    ln[1] = (unsigned long)pe;
                    cL4_tbl1_freelist = ln;
                }
                old_head = (unsigned long)found;
                cL4_waiter_scan_field40((int)lk, (unsigned long)found, mask, (long)pe2);
            }
            /* grow / ensure the entry table */
            if (ent == 0 || ent[0] <= u) {
                unsigned long sz = (unsigned long)(u >> 2);
                if (sz < 2) sz = 1;
                sz = cL4_table_round((sz + mask) * 8 + 8);
                ent = cL4_slot_alloc(sz, 0x1020040d5a9d86f);
                if (ent == 0) goto fail;
                ent[0] = (uint32_t)((sz + 0x7fffffff8ULL) >> 3);
                if (pe != 0) {
                    cL4_bucket_copy(ent + 2, pe, mask << 3, (7 < sz) ? sz - 8 : 0);
                    unsigned long *ln = cL4_slot_alloc(0x10, 0xa0040aff93c70);
                    *ln = (unsigned long)cL4_tbl1_freelist;
                    ln[1] = (unsigned long)pe;
                    cL4_tbl1_freelist = ln;
                }
            }
            cL4_tbl1_entries = ent;
            entry = 0;
            r = cL4_entry_dispatch_alloc(&entry, 8, 0x58, 0x59dd9b33);
            if (r != 0 || entry == 0) goto fail;
            /* install the object copy-dispatch block (FUN_00385bb4 family) */
            ((unsigned long*)entry)[0] = (unsigned long)&cL4_dispatch_foreach_slot8;
            ((unsigned long*)entry)[2] = (unsigned long)cL4_reg_copy_sized;
            ((unsigned long*)entry)[4] = (unsigned long)cL4_reg_copy_sized_r;
            ((unsigned long*)entry)[6] = (unsigned long)cL4_reg_copy_sized_fr;
            unsigned long stride = (unsigned long)id * 8 + 8;
            ((unsigned long*)entry)[7] = (unsigned long)&cL4_dispatch_copy_slot10;
            ((unsigned long*)entry)[8] = stride;
            ((unsigned long*)entry)[10] = 0x4f2758; /* DAT_004f2758 */
            ((unsigned long*)entry)[9] = stride;
            ent[u*2+2] = (unsigned int)(unsigned long)entry;
            cL4_tbl1_load = (uint32_t)(u + 1);
            cL4_bucket_insert(&old_head, &cL4_tbl1_head, (unsigned long)(u+1), resi & 0xffffffff, 3);
        } else {
            found = (unsigned long *)*(unsigned long*)res.lo;
        }
    }
    DataMemoryBarrier(2,3);
    if (cL4_tbl1_count == 0) {
        while (cL4_tbl1_freelist != 0) {
            unsigned long *nxt = (unsigned long*)*cL4_tbl1_freelist;
            cL4_free((void*)cL4_tbl1_freelist[1], 0);
            cL4_free(cL4_tbl1_freelist, 0);
            cL4_tbl1_freelist = nxt;
        }
        cL4_tbl1_freelist = 0;
    }
    cL4_handoff_release(0);
    cL4_tbl1_cache = found;
    return found;
fail:
    __asm__ volatile("brk #1" ::: "memory");   /* SoftwareBreakpoint(1,0x3858c8) */
    return 0;
}

/* Table-2 half: capability lookup/insert (hash FUN_00386160). */
static unsigned long *cL4_tbl2_lookup_insert(unsigned long id, uint32_t mode)
{
    unsigned long *found, *h = cL4_tbl2_head;
    unsigned int n, load, u;
    unsigned long old_head, hash, mask, idx;
    unsigned int *ent;
    uint32_t u2, k, c0, c1, c2;
    void *tmp, *entry, *bucket;
    unsigned long local_70, local_68;
    int r;

    if (cL4_tbl2_cache != 0 &&
        ((((uint32_t)((cL4_tbl2_cache[8] + 0x3ffffffe0ULL) >> 3) & 0x7fffffff |
           (*(uint32_t*)(cL4_tbl2_cache + 10) >> 0x17) << 0x1f) ^ (uint32_t)id) == 0x80000000))
        return cL4_tbl2_cache;
    LOAcquire();
    cL4_tbl2_count++;
    unsigned long key = id;
    cL4_w16_t hit = cL4_waiter_scan_cap_hash(&key, (unsigned long)cL4_tbl2_head, cL4_tbl2_load,
                                             (long)(cL4_tbl2_entries + 2));
    if (hit.lo != 0) {
        found = (unsigned long *)*(unsigned long*)hit.lo;
        goto hit2;
    }
    unsigned long n0 = cL4_tbl2_count;
    cL4_tbl2_count--;
    LORelease();
    cL4_deferred_free_push(n0, 0, 0x6c08a0);
    found = cL4_tbl2_head;
    ent = cL4_tbl2_entries;
    u = (uint32_t)cL4_tbl2_load;
    old_head = (unsigned long)cL4_tbl2_head;
    hash = ((unsigned long)cL4_tbl2_head & 3) != 0 ? *(unsigned char *)((unsigned long)cL4_tbl2_head & ~3UL) : 4;
    mask = (unsigned long)cL4_tbl2_load;
    unsigned int *pe = cL4_tbl2_entries + 2;
    unsigned int *pe2 = (cL4_tbl2_entries != 0) ? pe : 0;
    unsigned long lk = id;
    cL4_w16_t res = cL4_waiter_scan_cap_hash(&lk, (unsigned long)cL4_tbl2_head, mask, (long)pe2);
    unsigned long resi = res.hi;
    if (res.lo == 0) {
        unsigned long cap = 1UL << (hash & 0x3f);
        unsigned long load1 = (unsigned long)(u + 1);
        unsigned long rem = cap - load1;
        unsigned long loadf = (rem != 0) ? cap / rem : 0;
        if (3 < loadf) {
            old_head = (unsigned long)found;
            unsigned long nb = (unsigned long)((uint32_t)hash + 1);
            unsigned long nbk = nb & 0xff;
            uint32_t bk = (0x10 < nbk) ? 4 : ((nbk < 9) ? 1 : 2);
            bucket = cL4_bucket_alloc(2UL << (hash & 0x3f), bk, 0x48dda4ae);
            if (bucket == 0) goto fail;
            found = (unsigned long *)((unsigned long)((bk==1)?1:(bk==4)?3:2) | (unsigned long)bucket);
            *(unsigned char *)bucket = (unsigned char)((uint32_t)hash + 1);
            if ((int)hash != 0) {
                for (unsigned long i2 = 1; (i2 >> (hash & 0x3f)) == 0; i2++) {
                    unsigned long v = cL4_waiter_next(&old_head, i2, 0);
                    if (v != 0) {
                        unsigned long h2 = cL4_tbl2_hash((unsigned long*)*(unsigned long*)(pe + (v-1)*2));
                        while ((h2 = h2 & ~(-2UL << (hash & 0x3f))), h2 == 0 ||
                               (r = cL4_waiter_next(&found, h2, 0), r != 0)) h2++;
                        cL4_bucket_insert(&found, 0, v, h2, 0);
                    }
                }
            }
            cL4_tbl2_head = found;
            if (pe != 0) {
                unsigned long *ln = cL4_slot_alloc(0x10, 0xa0040aff93c70);
                *ln = (unsigned long)cL4_tbl2_freelist;
                ln[1] = (unsigned long)pe;
                cL4_tbl2_freelist = ln;
            }
            old_head = (unsigned long)found;
            cL4_waiter_scan_cap_hash(&lk, (unsigned long)found, mask, (long)pe2);
        }
        if (ent == 0 || ent[0] <= u) {
            unsigned long sz = (unsigned long)(u >> 2);
            if (sz < 2) sz = 1;
            sz = cL4_table_round((sz + mask) * 8 + 8);
            ent = cL4_slot_alloc(sz, 0x1020040d5a9d86f);
            if (ent == 0) goto fail;
            ent[0] = (uint32_t)((sz + 0x7fffffff8ULL) >> 3);
            if (pe != 0) {
                cL4_bucket_copy(ent + 2, pe, mask << 3, (7 < sz) ? sz - 8 : 0);
                unsigned long *ln = cL4_slot_alloc(0x10, 0xa0040aff93c70);
                *ln = (unsigned long)cL4_tbl2_freelist;
                ln[1] = (unsigned long)pe;
                cL4_tbl2_freelist = ln;
            }
        }
        cL4_tbl2_entries = ent;
        entry = 0;
        r = cL4_entry_dispatch_alloc(&entry, 8, 0x58, 0x59dd9b33);
        if (r != 0 || entry == 0) goto fail;
        cL4_tbl2_entry_init(entry, id);           /* FUN_00386328 */
        ent[u*2+2] = (unsigned int)(unsigned long)entry;
        cL4_tbl2_load = (uint32_t)(u + 1);
        cL4_bucket_insert(&old_head, &cL4_tbl2_head, (unsigned long)(u+1), resi & 0xffffffff, 3);
    } else {
        found = (unsigned long *)*(unsigned long*)res.lo;
    }
hit2:
    DataMemoryBarrier(2,3);
    if (cL4_tbl2_count == 0) {
        while (cL4_tbl2_freelist != 0) {
            unsigned long *nxt = (unsigned long*)*cL4_tbl2_freelist;
            cL4_free((void*)cL4_tbl2_freelist[1], 0);
            cL4_free(cL4_tbl2_freelist, 0);
            cL4_tbl2_freelist = nxt;
        }
        cL4_tbl2_freelist = 0;
    }
    cL4_handoff_release(0);
    cL4_tbl2_cache = found;
    return found;
fail:
    __asm__ volatile("brk #1" ::: "memory");
    return 0;
}

/* FUN_00384f48 @ 0x00384f48   (est. cL4_obj_table_lookup_insert)
 * Ghidra: undefined8* FUN_00384f48(ulong id, uint mode, int a, int b)
 * Public entry: mode 1 returns the fixed "invalid" pointer (0x67aa20); an
 * even id routes to the table-1 object lookup; an odd id (with mode) routes
 * to the table-2 capability lookup (encoding cap presence in the top bit).
 * Returns the resolved object/capability pointer.
 * Confidence: high (verified against decompile; dispatcher keys corrected to mode)
 */
unsigned long *cL4_obj_table_lookup_insert(unsigned long id, uint32_t mode, int a, int b)
{
    if (a == 1) return (unsigned long*)0x67aa20;
    if ((id & 1) == 0) {
        if (mode < 3) return (unsigned long *)((unsigned long)mode * 8 + 0x67b780);
        /* table-1 half keys on param_2 (mode): stride = mode*8+8, lookup key = mode */
        return cL4_tbl1_lookup_insert(mode, mode);
    }
    /* odd path: key = (b ? 0x80000000 : 0) | (mode & 0x7fffffff); param_1 (id) unused */
    if (b == 0) return cL4_tbl2_lookup_insert(mode & 0x7fffffff, mode);
    if (mode == 0) return (unsigned long*)0x67b188;
    if (mode == 1) return (unsigned long*)0x67b710;
    return cL4_tbl2_lookup_insert(mode | 0x80000000, mode);
}

/* Table-3 globals (fixed small-id object table, base _DAT_006c07e0). */
extern unsigned long cL4_tbl3_count;     /* _DAT_006c07e0 */
extern unsigned long cL4_tbl3_load;      /* _DAT_006c07e4 */
extern unsigned int *cL4_tbl3_entries;   /* _DAT_006c07e8 */
extern unsigned long *cL4_tbl3_head;     /* _DAT_006c07f0 */
extern unsigned long *cL4_tbl3_cache;    /* _DAT_006c0828 */
extern unsigned long *cL4_tbl3_freelist; /* _DAT_006c0820 */
/* DAT_004f2750 — shared entry field for table-3 objects. */

/* FUN_00383b08 @ 0x00383b08   (est. cL4_obj_table_lookup_insert_fixed)
 * Ghidra: undefined8* FUN_00383b08(uint param_1)
 * Third object-table lookup/insert for small object ids: ids < 3 resolve from
 * a fixed dispatch table (0x67b768 + id*8); otherwise a hash-table probe with
 * growth (identical to the table-1/2 halves in FUN_00384f48, base 0x6c07e0),
 * with a cached last-hit (_DAT_006c0828). On miss it grows the bucket table,
 * (re)allocates the entry table, installs the per-entry copy-dispatch block
 * (referencing 0x384320 family), and registers the new id. Any failure is a
 * fail-closed SoftwareBreakpoint trap.
 * Confidence: low (third duplicate of the table-lookup core)
 */
unsigned long *cL4_obj_table_lookup_insert_fixed(uint32_t id)
{
    unsigned long *found, *h = cL4_tbl3_head;
    unsigned int n, load, u;
    unsigned long old_head, hash, mask, idx;
    unsigned int *ent;
    uint32_t u2, k, c0, c1, c2;
    void *tmp, *entry, *bucket;
    unsigned long local_70, local_68;
    int r;

    if (id < 3) return (unsigned long *)*(unsigned long *)(0x67b768 + (unsigned long)id * 8);
    if (cL4_tbl3_cache != 0 && id == (uint32_t)((cL4_tbl3_cache[8] + 0x7fffffff8ULL) >> 3))
        return cL4_tbl3_cache;
    LOAcquire();
    cL4_tbl3_count++;
    unsigned long key = id;
    cL4_w16_t hit = cL4_waiter_scan_field40((int)key, (unsigned long)cL4_tbl3_head,
                                            cL4_tbl3_load, (long)(cL4_tbl3_entries + 2));
    if (hit.lo != 0) {
        LORelease();
        cL4_tbl3_count--;
        cL4_tbl3_cache = (unsigned long *)*(unsigned long*)hit.lo;
        return (unsigned long *)*(unsigned long*)hit.lo;
    }
    unsigned long n0 = cL4_tbl3_count;
    cL4_tbl3_count--;
    LORelease();
    cL4_deferred_free_push(n0, 0, 0x6c0800);
    found = cL4_tbl3_head;
    ent = cL4_tbl3_entries;
    u = (uint32_t)cL4_tbl3_load;
    old_head = (unsigned long)cL4_tbl3_head;
    hash = ((unsigned long)cL4_tbl3_head & 3) != 0 ? *(unsigned char *)((unsigned long)cL4_tbl3_head & ~3UL) : 4;
    mask = (unsigned long)cL4_tbl3_load;
    unsigned int *pe = cL4_tbl3_entries + 2;
    unsigned int *pe2 = (cL4_tbl3_entries != 0) ? pe : 0;
    unsigned long lk = id;
    cL4_w16_t res = cL4_waiter_scan_field40((int)lk, (unsigned long)cL4_tbl3_head, mask, (long)pe2);
    unsigned long resi = res.hi;
    if (res.lo == 0) {
        unsigned long cap = 1UL << (hash & 0x3f);
        unsigned long load1 = (unsigned long)(u + 1);
        unsigned long rem = cap - load1;
        unsigned long loadf = (rem != 0) ? cap / rem : 0;
        if (3 < loadf) {
            old_head = (unsigned long)found;
            unsigned long nb = (unsigned long)((uint32_t)hash + 1);
            unsigned long nbk = nb & 0xff;
            uint32_t bk = (0x10 < nbk) ? 4 : ((nbk < 9) ? 1 : 2);
            bucket = cL4_bucket_alloc(2UL << (hash & 0x3f), bk, 0x48dda4ae);
            if (bucket == 0) goto fail;
            found = (unsigned long *)((unsigned long)((bk==1)?1:(bk==4)?3:2) | (unsigned long)bucket);
            *(unsigned char *)bucket = (unsigned char)((uint32_t)hash + 1);
            if ((int)hash != 0) {
                for (unsigned long i2 = 1; (i2 >> (hash & 0x3f)) == 0; i2++) {
                    unsigned long v = cL4_waiter_next(&old_head, i2, 0);
                    if (v != 0) {
                        unsigned long h2 = cL4_hash_mix((uint32_t)((*(unsigned long *)(pe + (v-1)*2) + 0x7fffffff8ULL) >> 3));
                        while ((h2 = h2 & ~(-2UL << (hash & 0x3f))), h2 == 0 ||
                               (r = cL4_waiter_next((unsigned long*)found, h2, 0), r != 0)) h2++;
                        cL4_bucket_insert((unsigned long*)found, 0, v, h2, 0);
                    }
                }
            }
            cL4_tbl3_head = found;
            if (pe != 0) {
                unsigned long *ln = cL4_slot_alloc(0x10, 0xa0040aff93c70);
                *ln = (unsigned long)cL4_tbl3_freelist;
                ln[1] = (unsigned long)pe;
                cL4_tbl3_freelist = ln;
            }
            old_head = (unsigned long)found;
            cL4_waiter_scan_field40((int)lk, (unsigned long)found, mask, (long)pe2);
        }
        if (ent == 0 || ent[0] <= u) {
            unsigned long sz = (unsigned long)(u >> 2);
            if (sz < 2) sz = 1;
            sz = cL4_table_round((sz + mask) * 8 + 8);
            ent = cL4_slot_alloc(sz, 0x1020040d5a9d86f);
            if (ent == 0) goto fail;
            ent[0] = (uint32_t)((sz + 0x7fffffff8ULL) >> 3);
            if (pe != 0) {
                cL4_bucket_copy(ent + 2, pe, mask << 3, (7 < sz) ? sz - 8 : 0);
                unsigned long *ln = cL4_slot_alloc(0x10, 0xa0040aff93c70);
                *ln = (unsigned long)cL4_tbl3_freelist;
                ln[1] = (unsigned long)pe;
                cL4_tbl3_freelist = ln;
            }
        }
        cL4_tbl3_entries = ent;
        entry = 0;
        r = cL4_entry_dispatch_alloc(&entry, 8, 0x58, 0x59dd9b33);
        if (r != 0 || entry == 0) goto fail;
        ((unsigned long*)entry)[0] = 0x384320;
        unsigned long stride = (unsigned long)id * 8 + 8;
        ((unsigned long*)entry)[8] = stride;
        ((unsigned long*)entry)[9] = stride;
        ((unsigned long*)entry)[10] = 0x4f2750;
        ent[u*2+2] = (unsigned int)(unsigned long)entry;
        cL4_tbl3_load = (uint32_t)(u + 1);
        cL4_bucket_insert(&old_head, &cL4_tbl3_head, (unsigned long)(u+1), resi & 0xffffffff, 3);
    } else {
        found = (unsigned long *)*(unsigned long*)res.lo;
    }
    DataMemoryBarrier(2,3);
    if (cL4_tbl3_count == 0) {
        while (cL4_tbl3_freelist != 0) {
            unsigned long *nxt = (unsigned long*)*cL4_tbl3_freelist;
            cL4_free((void*)cL4_tbl3_freelist[1], 0);
            cL4_free(cL4_tbl3_freelist, 0);
            cL4_tbl3_freelist = nxt;
        }
        cL4_tbl3_freelist = 0;
    }
    cL4_handoff_release(0);
    cL4_tbl3_cache = found;
    return found;
fail:
    __asm__ volatile("brk #1" ::: "memory");
    return 0;
}

/* ------------------------------------------------------------------ *
 * Table-2 capability hash machinery (00386160/00386280/00386328) plus the
 * table-2 entry copy helpers.
 * ------------------------------------------------------------------ */

/* FUN_00386160 @ 0x00386160   (est. cL4_waiter_scan_cap_hash)
 * Ghidra: undefined1[16] FUN_00386160(uint *param_1, ...)
 * The table-2 waiter scan: builds the capability descriptor block via
 * cL4_tbl2_entry_init (00386328), hashes it (00386280), then scans the
 * waiters for one whose object's cap word ((*(obj+0x40)+...)&0x7fffffff with
 * bit-31 from *(obj+0x50)) matches the requested capability. Returns
 * {index, waiter_ptr}.
 * Confidence: medium
 */
cL4_w16_t cL4_waiter_scan_cap_hash(unsigned long *cap, unsigned long start,
                                   unsigned long limit, long base)
{
    cL4_w16_t out;
    unsigned long w = start, u2, u3, i;
    unsigned char dblock[88];
    int w2;
    cL4_tbl2_entry_init((unsigned long*)dblock, *cap);
    u2 = cL4_tbl2_hash((unsigned long *)dblock);
    u3 = 4;
    if ((start & 3) != 0 && (unsigned char *)(start & 0xfffffffffffffffcULL) != 0)
        u3 = (unsigned long)*(unsigned char *)(start & 0xfffffffffffffffcULL);
    u3 = -1UL << (u3 & 0x3f);
    u2 = u2 & ~u3;
    if (u2 < 2) u2 = 1;
    w2 = cL4_waiter_next(&w, u2, 2);
    while (w2 != 0) {
        i = (unsigned long)(w2 - 1);
        if (i < limit) {
            unsigned long l5 = *(unsigned long *)(base + i*8);
            uint32_t v = (((uint32_t)((*(long *)(l5 + 0x40) + 0x3ffffffe0ULL) >> 3) & 0x7fffffff |
                           (*(uint32_t *)(l5 + 0x50) >> 0x17) << 0x1f) ^ (uint32_t)*cap);
            if (v == 0x80000000) {
                u2 = 0; base = base + i*8; goto found;
            }
        }
        u2 = (u2 + 1) & ~u3;
        if (u2 < 2) u2 = 1;
        w2 = cL4_waiter_next(&w, u2, 2);
    }
    base = 0; u2 &= 0xffffffff;
found:
    out.lo = base; out.hi = u2; return out;
}

/* FUN_00386280 @ 0x00386280   (est. cL4_tbl2_hash)
 * Ghidra: void FUN_00386280(long param_1)
 * Computes the table-2 hash over the descriptor block: extracts the cap index
 * (*(obj+0x40)>>3) and the cap-presence bit (*(obj+0x50) & 0x800000), then
 * runs the two-word MR copy through the table-2 word op to produce the hash.
 * Canary-protected.
 * Confidence: medium
 */
unsigned long cL4_mr_copy_hash(uint32_t *b0, unsigned long acc, unsigned long c1,
                               unsigned long c2, unsigned char *ac);

unsigned long cL4_tbl2_hash(unsigned long *obj)
{
    unsigned char ac = (*(uint32_t *)(obj + 0x50) & 0x800000) == 0;
    uint32_t b0 = (uint32_t)((*(long *)(obj + 0x40) + 0x7ffffffe0ULL) >> 3);
    unsigned char c1[64], c2[64];
    unsigned long canary = (unsigned long)-0x2c8502b44bfffed6ULL;
    cL4_mr_ctx_init(c1);
    cL4_mr_copy_hash(&b0, 0, (unsigned long)c1, (unsigned long)c2, &ac);
    if (canary == (unsigned long)-0x2c8502b44bfffed6ULL) return 0;
    cL4_stack_fail();
    return 0;
}
/* FUN_00386328 @ 0x00386328   (est. cL4_tbl2_entry_init)
 * Ghidra: void FUN_00386328(undefined8 *param_1, ulong param_2)
 * Initializes a table-2 descriptor block: fills the copy-dispatch slots
 * (0x3864b4 family), computes the per-id stride (id&0x7fffffff)*8+0x20, sets
 * the type/flags word (0x1830007, or 0x30007 when the top bit is set) and the
 * per-entry size (0x1000).
 * Confidence: medium
 */
void cL4_tbl2_entry_init(unsigned long *e, unsigned long id)
{
    e[0] = 0x3864b4;
    e[1] = 0x386508;
    e[2] = 0x38650c;
    e[3] = 0x37541c;
    e[4] = 0x386510;
    e[5] = 0x386528;
    e[6] = 0x38652c;
    unsigned long stride = (id & 0x7fffffff) * 8 + 0x20;
    e[7] = 0x38664c;
    e[8] = stride;
    uint32_t flags = 0x1830007;
    if ((id >> 0x1f) != 0) flags = 0x30007;
    *(uint32_t *)(e + 10) = flags;
    *(uint32_t *)((char*)e + 0x54) = 0x1000;
    e[9] = stride;
}

/* FUN_00386438 — table-2 word+shift MR copy (cL4_mr_copy_hash). */
unsigned long cL4_mr_copy_hash(uint32_t *b0, unsigned long acc, unsigned long c1,
                               unsigned long c2, unsigned char *ac)
{
    unsigned long a2 = acc, a1;
    a1 = cL4_mr_copy_word(0, &a2, c1, c2, *b0);
    a2 = a1;
    return cL4_mr_copy_shifted_r(0, &a2, a1, c2, *ac);
}
/* FUN_003864d8 @ 0x003864d8 — 1-word copy with forward stride (dup of
 * cL4_reg_copy1_f). */
long cL4_reg_copy1_f2(unsigned long *dst, unsigned long *src)
{
    unsigned long v = *src;
    *dst = v;
    cL4_obj_copy_advance();
    return (long)src + (*(unsigned char *)(*(long *)((long)src - 8) + 0x50) + 0x10 &
            (*(unsigned char *)(*(long *)((long)src - 8) + 0x50) ^ ~0UL));
}

/* FUN_00386698 @ 0x00386698   (est. cL4_obj_copy4_fixed)
 * Ghidra: undefined8* FUN_00386698(param_1, param_2, param_3)
 * Copies the fixed-size payload (size-0x18) of obj[3..], then the object
 * header via slot-0x10 dispatch (or word copy + advance when flag bit1 set).
 * Confidence: medium
 */
unsigned long *cL4_obj_copy4_fixed(unsigned long *dst, unsigned long *src, long obj)
{
    cL4_obj_copy_simple((long)(dst+3), (long)(src+3), *(long *)(*(long *)(obj - 8) + 0x48) + -0x18);
    if ((*(unsigned char *)(*(long *)(src[3] - 8) + 0x52) >> 1 & 1) == 0) {
        (**(void (**)(unsigned long*,unsigned long*))(*(long *)(src[3] - 8) + 0x10))(dst, src);
    } else {
        *dst = *src;
        cL4_obj_copy_advance();
    }
    return dst;
}

/* FUN_00386724 @ 0x00386724   (est. cL4_obj_copy5_slot20_fixed)
 * Ghidra: undefined8* FUN_00386724(param_1, param_2, param_3)
 * Copy variant: same-tag uses slot-0x28 dispatch; diff-tag runs the source
 * setup (slot-0x20), a fixed-size payload copy (size-0x18), and the dest
 * setup (slot-0x20). Reverse-stride cleanup on the fall-through path.
 * Confidence: medium
 */
unsigned long *cL4_obj_copy5_slot20_fixed(unsigned long *dst, unsigned long *src, long obj)
{
    long srcobj, dstobj;
    unsigned long tmp[3];
    if (src == dst) return dst;
    if (src[3] == dst[3]) {
        if ((*(unsigned char *)(*(long *)(src[3] - 8) + 0x52) >> 1 & 1) == 0) {
            (**(void (**)(unsigned long*,unsigned long*,long))(*(long *)(src[3] - 8) + 0x28))(dst, src, src[3]);
            return dst;
        }
        unsigned long v = *dst;
        *dst = *src;
        cL4_obj_copy_reverse(&v);
    } else {
        dstobj = *(long *)(dst[3] - 8);
        long s = dstobj; if (s == 0) s = 0;
        srcobj = *(long *)(src[3] - 8);
        long d = srcobj; if (d == 0) d = 0;
        if ((*(unsigned char *)(s + 0x52) >> 1 & 1) == 0) {
            (**(void (**)(unsigned long*,unsigned long*,long))(dstobj + 0x20))(tmp, dst, dst[3]);
            cL4_obj_copy_simple((long)(dst+3), (long)(src+3), *(long *)(*(long *)(obj - 8) + 0x48) + -0x18);
            if ((*(unsigned char *)(d + 0x52) >> 1 & 1) == 0)
                (**(void (**)(unsigned long*,unsigned long*,long))(*(long *)(src[3] - 8) + 0x20))(dst, src, src[3]);
            else { *dst = *src; }
            (**(void (**)(unsigned long*,long))(*(long *)(dst[3] - 8) + 8))(tmp, dst[3]);
            return dst;
        }
        unsigned long v = *dst;
        cL4_obj_copy_simple((long)(dst+3), (long)(src+3), *(long *)(*(long *)(obj - 8) + 0x48) + -0x18);
        if ((*(unsigned char *)(d + 0x52) >> 1 & 1) == 0)
            (**(void (**)(unsigned long*,unsigned long*,long))(*(long *)(src[3] - 8) + 0x20))(dst, src, src[3]);
        else { *dst = *src; }
        cL4_obj_copy_reverse(&v);
    }
    return dst;
}

/* FUN_0038695c @ 0x0038695c   (est. cL4_cap_desc_match)
 * Ghidra: bool FUN_0038695c(long *param_1, long *param_2)
 * Compares a capability descriptor pair: if the caps differ, resolves the
 * first (thunk_FUN_00115080) and requires the second to match it (and be
 * equal via thunk_FUN_001145b0). Returns true on match.
 * Confidence: medium
 */
int cL4_cap_desc_match(unsigned long *a, unsigned long *b)
{
    if (*a != *b) {
        int *p = (int *)(*a + 8);
        long l1 = (long)*p + (long)p;
        if (l1 == 0) return b[2] == 0;
        long r = cL4_cap_resolve(l1);
        if (r != b[2]) return 0;
        if (r != 0) return cL4_cap_equal2(l1, b[1], r) == 0;
    }
    return 1;
}
/* FUN_003869f4 @ 0x003869f4   (est. cL4_waiter_scan_cap_desc)
 * Ghidra: undefined1[16] FUN_003869f4(long param_1, ...)
 * Waiter scan matching a capability descriptor (param_1) via FUN_003a2b38
 * hash and cL4_cap_desc_match. Returns {index, waiter_ptr}.
 * Confidence: medium
 */
cL4_w16_t cL4_waiter_scan_cap_desc(unsigned long *desc, unsigned long start,
                                   unsigned long limit, long base)
{
    cL4_w16_t out;
    unsigned long w = start, u2, u3, i;
    int w2;
    u2 = cL4_cap_resolve_word(*(unsigned long *)(desc + 8), *(unsigned long *)(desc + 0x10));
    u3 = 4;
    if ((start & 3) != 0 && (unsigned char *)(start & 0xfffffffffffffffcULL) != 0)
        u3 = (unsigned long)*(unsigned char *)(start & 0xfffffffffffffffcULL);
    u3 = -1UL << (u3 & 0x3f);
    u2 = u2 & ~u3;
    if (u2 < 2) u2 = 1;
    w2 = cL4_waiter_next(&w, u2, 2);
    while (w2 != 0) {
        i = (unsigned long)(w2 - 1);
        if (i < limit && (cL4_cap_desc_match((unsigned long *)*(unsigned long *)(base + i*8), desc) & 1)) {
            u2 = 0; base = base + i*8; goto found;
        }
        u2 = (u2 + 1) & ~u3;
        if (u2 < 2) u2 = 1;
        w2 = cL4_waiter_next(&w, u2, 2);
    }
    base = 0; u2 &= 0xffffffff;
found:
    out.lo = base; out.hi = u2; return out;
}

/* FUN_00386ae0 @ 0x00386ae0   (est. cL4_waiter_match_context)
 * Ghidra: undefined8 FUN_00386ae0(long param_1, long param_2)
 * Matches a waiter's saved context: compares the object pointer at
 * *(param_1+0x18) against the waiter's context word (*(param_2+0x20)), then
 * builds a context block (FUN_00375fc8) and validates via FUN_00379f6c.
 * Returns nonzero on match.
 * Confidence: low
 */
unsigned long cL4_waiter_match_context(long a, long b)
{
    unsigned long ctx[4];
    unsigned long l2 = *(long *)(a + 0x18);
    if (l2 == 0) {
        if (*(long *)(b + 0x20) != 0) return 0;
        l2 = 0;
    } else if (*(long *)(b + 0x20) != l2) {
        return 0;
    }
    cL4_ctx_build(ctx, l2, a + 0x20);            /* FUN_00375fc8 */
    if (ctx[0] != *(long *)(b + 0x20)) return 0;
    return cL4_ctx_validate(ctx, b);             /* FUN_00379f6c */
}
/* FUN_00375fc8 @ 0x375fc8 — build a context block from an object. */
/* FUN_00379f6c @ 0x379f6c — validate a context block against a waiter. */

/* FUN_00386b78 @ 0x00386b78   (est. cL4_waiter_scan_context)
 * Ghidra: void FUN_00386b78(param_1, ulong, ulong, long)
 * Waiter scan matching a context descriptor (param_1): copies the 5-word
 * descriptor block, runs the two-word MR copy (003811ac), then scans for a
 * waiter whose saved context matches (cL4_waiter_match_context). Canary-
 * protected; 16-byte return {index, ptr}.
 * Confidence: medium
 */
cL4_w16_t cL4_waiter_scan_context(unsigned long *desc, unsigned long start,
                                  unsigned long limit, long base)
{
    cL4_w16_t out;
    unsigned long w = start, u2, u3, i;
    unsigned char c1[72];
    uint32_t d4 = *(uint32_t *)(desc + 3);
    unsigned long d0, x;
    int w2;
    cL4_mr_ctx_init(&d0);
    cL4_mr_copy6_word2(0, 0, (unsigned long)&d0, (unsigned long)c1, desc + 4, &d4);
    u2 = 0;
    u3 = 4;
    if ((start & 3) != 0 && (unsigned char *)(start & 0xfffffffffffffffcULL) != 0)
        u3 = (unsigned long)*(unsigned char *)(start & 0xfffffffffffffffcULL);
    u3 = -1UL << (u3 & 0x3f);
    u2 = u2 & ~u3;
    if (u2 < 2) u2 = 1;
    w2 = cL4_waiter_next(&w, u2, 2);
    while (w2 != 0) {
        i = (unsigned long)(w2 - 1);
        if (i < limit) {
            unsigned long d0b[5];
            d0b[0] = desc[0]; d0b[1] = desc[1]; d0b[2] = desc[2]; d0b[3] = desc[3]; d0b[4] = desc[4];
            if ((cL4_waiter_match_context(*(unsigned long *)(base + i*8), (long)d0b) & 1) != 0) {
                u2 = 0; base = base + i*8; goto found;
            }
        }
        u2 = (u2 + 1) & ~u3;
        if (u2 < 2) u2 = 1;
        w2 = cL4_waiter_next(&w, u2, 2);
    }
    base = 0; u2 &= 0xffffffff;
found:
    out.lo = base; out.hi = u2; return out;
}

/* FUN_00386cc4 @ 0x00386cc4   (est. cL4_tcb_pinned_check)
 * Ghidra: undefined8 FUN_00386cc4(void)
 * Checks the per-CPU context list: walks the descriptor array (stride 0xc,
 * count from FUN_00367d50) and returns 0 if any entry is a pinned/active
 * kernel context (type 5 with flag bit0 set); otherwise returns 1.
 * Confidence: medium
 */
unsigned long cL4_tcb_pinned_check(void)
{
    unsigned char hdr[2];
    unsigned short n;
    unsigned int *e;
    cL4_percpu_ctx_table(hdr);
    n = *(unsigned short *)&hdr[0];
    if (n != 0) {
        long cnt = (long)n * 0xc;
        do {
            if (((*e & 0x1f) == 5) && ((*(unsigned short *)((long)e + 10) & 1) != 0))
                return 0;
            e += 3;
            cnt -= 0xc;
        } while (cnt != 0);
    }
    return 1;
}

/* FUN_00386d2c @ 0x00386d2c   (est. cL4_cap_resolve_word)
 * Ghidra: undefined8* FUN_00386d2c(uint *param_1)
 * Resolves a capability word to its object pointer: when flag bit10 is clear
 * returns NULL; otherwise decodes the pointer/selector fields (bits 8/9) to
 * select the slot, and either returns the inline pointer or dereferences the
 * indirect slot (bit0 set). This is the cap-word -> object resolution used by
 * the MR copy engine.
 * Confidence: medium
 */
unsigned long *cL4_cap_resolve_word_fn(unsigned int *cap)
{
    uint32_t v = *cap;
    if ((v >> 10 & 1) == 0) return 0;
    int *slot = (int *)(((long)cap + ((v >> 8) & 1)*8 + 0x13 & 0xfffffffffffffffcULL) + ((v >> 9) & 1)*4);
    unsigned long w = (unsigned long)*slot;
    unsigned long *ptr = (unsigned long *)((w & 0xfffffffffffffffeULL) + (long)slot);
    if ((w & 1) == 0) return ptr;
    return (unsigned long *)*ptr;
}

/* FUN_00386d70 @ 0x00386d70   (est. cL4_ipc_obj_endpoint)
 * Ghidra: long FUN_00386d70(uint *param_1)
 * Resolves the endpoint/notification object pointer for an IPC object whose
 * kind (word&0x1f) is 0x10/0x11/0x12, dispatching to the kind-specific fetch
 * (FUN_00379480/FUN_0037bcac/FUN_0037b3b8). Kind 0x10 adds 4 when the
 * large-object flag (bit 0x1d) is set. Any other kind is a fail-closed trap.
 * Confidence: medium
 */
long cL4_ipc_obj_endpoint(unsigned int *cap)
{
    uint32_t k = *cap & 0x1f;
    long e;
    if (k == 0x12) {
        e = (cap == 0) ? cL4_obj_kind18(0) : cL4_obj_kind18(cap);
        return e;
    }
    if (k == 0x11) {
        e = (cap == 0) ? cL4_obj_kind17(0) : cL4_obj_kind17(cap);
        return e;
    }
    if (k != 0x10) { __asm__ volatile("brk #1" ::: "memory"); return 0; }
    if (cap == 0) cap = 0;
    e = cL4_ipc_obj_kind10(cap);                  /* FUN_00379480 */
    return e + (((*cap >> 0x1d) & 1)) * 4;
}
/* FUN_00379480 @ 0x379480 — fetch endpoint for kind 0x10. */
extern long cL4_ipc_obj_kind10(unsigned int *cap);
/* FUN_00386ee0 @ 0x00386ee0   (est. cL4_ipc_recv_wait_c)
 * Ghidra: undefined1[16] FUN_00386ee0(ulong *param_1, undefined8 param_2)
 * Third IPC receive/wait loop, identical structure to cL4_ipc_recv_wait
 * (003800cc) but keyed off _DAT_006c0720 and finalizing via
 * cL4_msg_send_finalize_c (003870b8).
 * Confidence: medium
 */
extern unsigned long cL4_current_thread_c;   /* _DAT_006c0720 */
extern cL4_w16_t cL4_msg_send_finalize_c(unsigned long *msg_word, void *obj,
                                         unsigned int opts);   /* FUN_003870b8 */

cL4_w16_t cL4_ipc_recv_wait_c(unsigned long *msg_word, unsigned long opts)
{
    cL4_w16_t out;
    unsigned long word, mkind, thread;
    long *node;
    void **pending = 0;
    void *staging;
    unsigned long alloc = 0;

    word = *msg_word;
    mkind = cL4_msg_classify(&word, 0);
    if (mkind < 2) {
        out = cL4_msg_result(msg_word, word & 7);
        return out;
    }
    node = 0;
    staging = &cL4_current_thread_c;
    for (;;) {
        thread = cL4_current_thread_c;
        cL4_ref_acquire(cL4_current_thread_c);
        if (node != 0) cL4_ref_release((unsigned long)node);
        word = *msg_word;
        mkind = cL4_msg_classify(&word, opts);
        if (mkind != 2) break;
        node = (long *)(word & 0xfffffffffffffff0ULL);
        node[0]++;
        if (((word >> 3) & 1) == 0) goto bail;
        cL4_release(thread);
        cL4_ref_acquire((unsigned long)(node + 2));
        cL4_release((unsigned long)(node + 2));
    }
    if (mkind == 3) {
        alloc = cL4_obj_alloc();
        if (((word >> 3) & 1) == 0) {
            unsigned long *src = (unsigned long *)(word & 0xfffffffffffffff0ULL);
            if (src != 0) {
                unsigned long v0 = src[0], v1 = src[1], v2 = src[2];
                *(unsigned long *)(alloc + 0x30) = v1;
                *(unsigned long *)(alloc + 0x28) = v0;
                src[2] = 0;
                unsigned long old = *(unsigned long *)(alloc + 0x20);
                *(unsigned long *)(alloc + 0x20) = v2;
                if (old != 0) cL4_free((void*)old, 0x20);
                int had = (pending != 0);
                pending = (void**)src;
                if (had) cL4_msg_list_push((unsigned long*)&pending);
            }
        }
        *msg_word = (word & 7) | alloc | 8;
        cL4_release(thread);
        out = cL4_msg_send_finalize_c(msg_word, staging, opts);
        goto done;
    }
bail:
    cL4_release(thread);
    out = cL4_msg_result(msg_word, word & 7);
done:
    if (pending != 0) cL4_msg_list_push((unsigned long*)&pending);
    cL4_msg_free(staging);
    return out;
}

/* FUN_003870b8 @ 0x003870b8   (est. cL4_msg_send_finalize_c)
 * Ghidra: void FUN_003870b8(ulong *param_1, undefined8 *param_2, uint param_3)
 * Message-register send finalize (third variant). Resolves the IPC object's
 * endpoint via cL4_ipc_obj_endpoint (00386d70) after the per-thread state
 * advance (FUN_00376634), then either delivers the collected message
 * registers (cL4_msg_collect) or packages them into an allocated message node
 * queued onto the receiver's queue. Advances the per-object handshake byte
 * (obj+0x11). Any unexpected kind is a fail-closed trap.
 * Confidence: medium
 */
cL4_w16_t cL4_msg_send_finalize_c(unsigned long *msg_word, void *obj, unsigned int opts)
{
    cL4_w16_t m, out;
    unsigned long u10 = msg_word[1], l12 = ((unsigned long*)obj)[1];
    unsigned long *local_88 = *(unsigned long **)(l12 + 0x20);
    unsigned long staged[4];
    if (local_88 == 0) { staged[0]=staged[1]=staged[2]=staged[3]=0; local_88 = staged; }
    unsigned int u1 = opts & 0xff;
    unsigned long u7 = u10;
    unsigned char b2;
    unsigned long x21;
    int b14;

    do {
        b2 = *(unsigned char *)((char*)obj + 0x11);
        cL4_mr_state2(u7);                          /* FUN_00376634 */
        unsigned int *cap = (unsigned int *)cL4_ipc_obj_endpoint((unsigned int*)0);
        long ep = (long)*cap + (long)cap;
        if ((*cap == 0 || ep == 0) || ((m = cL4_ipc_obj_dispatch(ep, u10, local_88, 0)).lo == 0)) {
            m = cL4_msg_collect(u10);
            if (m.lo == 0) {
                b14 = 4;
                *(unsigned char *)((char*)obj + 0x11) = 4;
                goto finish;
            }
            b14 = 3;
        } else {
            b14 = 1;
            if ((*(unsigned char *)(*(long *)(u10 - 8) + 0x52) & 0x40) == 0) b14 = 2;
        }
        x21 = m.hi;
        *(unsigned char *)((char*)obj + 0x11) = b14;
        if (u1 < 0x3f) {
            if ((opts & 0xff) != 0) {
                if (u1 != 1) { trap: __asm__ volatile("brk #1" ::: "memory"); m.lo=m.hi=0; return m; }
                if (b14 == 3) goto package;
            }
        } else {
            if (u1 != 0x3f) { if (u1 != 0xff) goto trap; }
package:
            if (*(long *)(l12 + 0x20) == 0 && (staged[0]||staged[1]||staged[2]||staged[3])) {
                long *node = cL4_alloc(0x20, 0x80c4018a671a6);
                node[0] = staged[0]; node[1] = staged[1]; node[2] = staged[2]; node[3] = staged[3];
                long old = *(long *)(l12 + 0x20);
                *(long **)(l12 + 0x20) = node;
                if (old != 0) cL4_free((void*)old, 0x20);
            }
finish:
            void *node2 = 0;
            long l8 = *(long *)(l12 + 0x20);
            *(long *)(l12 + 0x20) = 0;
            b2 = *(unsigned char *)((char*)obj + 0x11);
            if (m.lo != 0 || l8 != 0) {
                node2 = cL4_alloc(0x20, 0x1060c4048d9c6c4ULL);
                *(cL4_w16_t*)node2 = m;
                *(long *)((char*)node2 + 8) = l8;
            }
            unsigned long peer = *(unsigned long *)*(unsigned long**)obj;
            cL4_ref_acquire(peer);
            *msg_word = (unsigned long)node2 | (unsigned long)b2;
            cL4_release(((unsigned long*)obj)[1] + 0x10);
            cL4_ref_release(((unsigned long*)obj)[1]);
            cL4_release(peer);
            *(unsigned short *)((char*)obj + 0x10) = 0;
            ((unsigned long*)obj)[1] = 0;
            return cL4_msg_result(msg_word, b14);
        }
        if ((opts >> 8 & 1) != 0) goto package;
        if (b2 < b14) {
            unsigned long peer = *(unsigned long *)*(unsigned long**)obj;
            cL4_ref_acquire(peer);
            long *q = (long*)((unsigned long*)obj)[1];
            long *q2 = q;
            if (*q != 1) {
                q2 = (long*)cL4_obj_alloc();
                unsigned long old = q[4]; q[4] = 0;
                unsigned long old2 = q2[4]; q2[4] = old;
                if (old2 != 0) cL4_free((void*)old2, 0x20);
            }
            *(cL4_w16_t*)(q2 + 5) = m;
            *msg_word = (unsigned long)*(unsigned char *)((char*)obj + 0x11) | (unsigned long)q2 | 8;
            if (q2 != q) {
                cL4_release(((unsigned long*)obj)[1] + 0x10);
                cL4_ref_release(((unsigned long*)obj)[1]);
                ((unsigned long*)obj)[1] = (unsigned long)q2;
            }
            cL4_release(peer);
            l12 = ((unsigned long*)obj)[1];
        }
        cL4_msg_handshake((long)msg_word[1], opts & 0xff, m.lo, x21);
        u7 = msg_word[1];
    } while (1);
}
/* FUN_00376634 @ 0x376634 — advance the per-thread MR state. */
extern void cL4_mr_state2(unsigned long tcb);
/* Endpoint dispatch call (indirect through the endpoint object). */
extern cL4_w16_t cL4_ipc_obj_dispatch(long ep, unsigned long tcb, unsigned long *q, long zero);
/* FUN_00376634 @ 0x376634 — advance the per-thread MR state. */
extern void cL4_mr_state2(unsigned long tcb);

/* FUN_003873c0 @ 0x003873c0   (est. cL4_cap_slot_get)
 * Ghidra: long FUN_003873c0(int *param_1, int param_2)
 * Fetches a capability-slot pointer: mode 1 returns the indirect slot value,
 * mode 0 returns the inline slot pointer (when nonzero).
 * Confidence: medium
 */
long cL4_cap_slot_get(int *cap, int mode)
{
    if (mode == 1) {
        if (*(long *)((long)*cap + (long)cap) != 0) return *(long *)((long)*cap + (long)cap);
    } else if (mode == 0 && *cap != 0) {
        long l = (long)*cap + (long)cap;
        if (l != 0) return l;
    }
    return 0;
}

/* FUN_00387424 @ 0x00387424   (est. cL4_msg_node_alloc_ref)
 * Ghidra: undefined8* FUN_00387424(void)
 * Allocates a 0x20-byte message node (tag 0xf), zeroes it, sets refcount=1,
 * registers a wait/notify (FUN_0037a850) and acquires a reference.
 * Confidence: medium
 */
unsigned long *cL4_msg_node_alloc_ref(void)
{
    unsigned long *node = cL4_alloc(0x20, 0xf);
    node[0] = node[1] = node[2] = node[3] = 0;
    node[0] = 1;
    cL4_node_wait_init(node + 2, 0);              /* FUN_0037a850 */
    cL4_ref_acquire(0);
    return node;
}
/* FUN_0037a850 @ 0x37a850 — init a message-node wait queue. */
/* FUN_00387474 @ 0x00387474   (est. cL4_msg_node_release)
 * Ghidra: void FUN_00387474(long *param_1)
 * Releases a message node reference: decrements the refcount; at 0 it tears
 * down the wait queue (thunk_FUN_00053aa0) and frees the node.
 * Confidence: medium
 */
void cL4_msg_node_release(unsigned long *node)
{
    if (node[0] - 1 == 0) {
        cL4_waitq_destroy(node + 2);              /* thunk_FUN_00053aa0 */
        cL4_free(node, 0x20);
        return;
    }
    node[0]--;
}
/* thunk_FUN_00053aa0 @ 0x53aa0 — destroy a wait queue. */

/* FUN_003874c8 @ 0x003874c8   (est. cL4_msg_node_free_linked)
 * Ghidra: long FUN_003874c8(long param_1)
 * Releases and frees a linked message-node chain: releases the node at
 * *(obj+8)+0x10 and frees it, then returns the parent object.
 * Confidence: medium
 */
long cL4_msg_node_free_linked(long obj)
{
    if (*(long *)(obj + 8) != 0) {
        cL4_release(*(long *)(obj + 8) + 0x10);
        long l = *(long *)(obj + 8);
        if (l != 0) {
            cL4_waitq_destroy((unsigned long *)(l + 0x10));
            cL4_free((void*)l, 0x20);
        }
    }
    return obj;
}

/* FUN_0038751c @ 0x0038751c   (est. cL4_waiter_scan_field8)
 * Ghidra: undefined1[16] FUN_0038751c(long *param_1, ...)
 * Waiter scan matching the object field at +8 against the key (*param_1),
 * hashed via FUN_0036becc. Returns {index, waiter_ptr}.
 * Confidence: medium
 */
cL4_w16_t cL4_waiter_scan_field8(unsigned long key, unsigned long start,
                                 unsigned long limit, long base)
{
    cL4_w16_t out;
    unsigned long w = start, u2, u3, i;
    int w2;
    u2 = cL4_waiter_hash(key);
    u3 = 4;
    if ((start & 3) != 0 && (unsigned char *)(start & 0xfffffffffffffffcULL) != 0)
        u3 = (unsigned long)*(unsigned char *)(start & 0xfffffffffffffffcULL);
    u3 = -1UL << (u3 & 0x3f);
    u2 = u2 & ~u3;
    if (u2 < 2) u2 = 1;
    w2 = cL4_waiter_next(&w, u2, 2);
    while (w2 != 0) {
        i = (unsigned long)(w2 - 1);
        if (i < limit && *(unsigned long *)(*(unsigned long *)(base + i*8) + 8) == key) {
            u2 = 0; base = base + i*8; goto found;
        }
        u2 = (u2 + 1) & ~u3;
        if (u2 < 2) u2 = 1;
        w2 = cL4_waiter_next(&w, u2, 2);
    }
    base = 0; u2 &= 0xffffffff;
found:
    out.lo = base; out.hi = u2; return out;
}

/* FUN_00387608 @ 0x00387608   (est. cL4_tcb_zone_free_count)
 * Ghidra: long FUN_00387608(void)
 * Counts the free slots in the per-CPU TCB zone: iterates the zone descriptor
 * (FUN_00362e54) and counts entries whose type-nibble is 0.
 * Confidence: medium
 */
long cL4_tcb_zone_free_count(void)
{
    long l1 = cL4_zone_get();                     /* FUN_00362e54 */
    long l4 = l1 + 0x18;
    if (l4 == 0) l4 = 0;
    if (*(uint32_t *)(l1 + 0x10) == 0) return 0;
    long n = 0;
    long cnt = (unsigned long)*(uint32_t *)(l1 + 0x10) << 3;
    unsigned char *p = (unsigned char *)(l4 + (unsigned long)*(uint32_t *)(l1 + 0xc) * 0xc);
    do {
        if ((*p & 0xf) == 0) n++;
        cnt -= 8;
        p += 8;
    } while (cnt != 0);
    return n;
}
/* FUN_00362e54 @ 0x362e54 — get the per-CPU TCB zone descriptor. */
/* FUN_0037a850 @ 0x37a850 — init a message-node wait queue. */
/* thunk_FUN_00053aa0 @ 0x53aa0 — destroy a wait queue. */

/* FUN_003876c4 @ 0x003876c4   (est. cL4_cap_type_validate)
 * Ghidra: bool FUN_003876c4(long *param_1)
 * Validates a capability descriptor's type/kind for a specific operation
 * domain (FUN_0036f460 gate). Walks the descriptor's tag word (*param_1) and
 * the referenced cap word (param_1[1] or [5]) to decide whether the cap type
 * is permitted; delegates deep validation to cL4_ipc_obj_endpoint for kind 2
 * and to the MR-object path otherwise. Any unexpected kind is a fail-closed
 * trap.
 * Confidence: low (kind semantics inferred)
 */


int cL4_cap_type_validate(long *desc)
{
    unsigned long u4 = cL4_type_gate();           /* FUN_0036f460 */
    long l5 = *desc;
    unsigned int *cap;
    if (l5 - 1U < 0x7ff) {
        if ((int)l5 - 0x203U < 0xfffffffd) {
            if (l5 != 0x203) {
                if (l5 != 0x301) return 0;
                return desc[1] != 0;
            }
            cap = (unsigned int *)desc[1];
            if (cap == 0) cap = 0;
        } else {
            cap = (unsigned int *)desc[1];
            if (cap == 0) { cap = 0; }
        }
    } else {
        cap = (unsigned int *)desc[5];
        if (cap == 0) { cap = 0; }
    }
    if ((*cap >> 7 & 1) != 0) {
        int i3 = cL4_cap_slot_index(cap);         /* FUN_0035ef4c */
        long l5b = cL4_cap_owner(cap);            /* FUN_0036fb10 */
        unsigned long s30 = *(unsigned long *)(l5b + 0x58);
        unsigned long l38 = *(unsigned long *)(l5b + 0x50);
        long local_40 = (long)(desc + i3);
        cL4_cap_release_ctx(&local_40);           /* FUN_0037cb08 */
        return 1;
    }
    uint32_t u1 = *cap >> 0x10 & 3;
    if (u1 < 2) return u1 != 0;
    if (u1 != 2) { __asm__ volatile("brk #1" ::: "memory"); return 0; }
    cL4_ipc_obj_endpoint(cap);
    return 0;
}

/* FUN_00387a34 @ 0x00387a34   (est. cL4_cap_resolve2)
 * Ghidra: long* FUN_00387a34(int param_1, int param_2, int param_3, long param_4)
 * Resolves an IPC cap-word pointer: base at param_4+param_3 (or NULL when
 * param_3==0); mode param_1==1 selects the base; mode param_2==1 dereferences
 * the slot (requires param_1==0, else fail-closed trap). Returns the resolved
 * pointer (or NULL).
 * Confidence: medium
 */
long *cL4_cap_resolve2(int m1, int m2, int off, long base)
{
    long *p0 = 0;
    if (off != 0) p0 = (long *)(base + off);
    long *p = (long *)(base + off);
    if (m1 == 1) p = p0;
    if (m2 == 1) {
        if (m1 != 0) { __asm__ volatile("brk #1" ::: "memory"); return 0; }
        p = (long *)*p;
        if (p != 0) return p;
        p = 0;
    }
    return p;
}

/* FUN_00387aa8 @ 0x00387aa8   (est. cL4_ipc_obj_register)
 * Ghidra: void FUN_00387aa8(param_1, param_2..5)
 * Registers an IPC object into the per-owner dispatch slot: resolves the cap
 * (cL4_cap_resolve2) and, depending on the object kind (param_2), either
 * publishes the raw descriptor (FUN_00363718) or fetches the dispatch-table
 * entry via FUN_003a3944 with the kind-specific tag. Any other kind traps.
 * Confidence: medium
 */
void cL4_ipc_obj_register(unsigned long *owner, unsigned long kind, unsigned long m2,
                          unsigned long off, unsigned long base)
{
    long *l3 = cL4_cap_resolve2(kind, m2, off, base);
    unsigned long u4 = *owner;
    int i2 = (int)kind;
    if (i2 < 2) {
        if (i2 == 0) {
            if (l3 == 0) l3 = 0;
            cL4_ipc_obj_publish(l3, 0, 0);        /* FUN_00363718 */
            return;
        }
        if (i2 == 1) { cL4_ipc_obj_getf(u4, 0x13a, l3); return; }
    } else {
        if (i2 == 2) { cL4_ipc_obj_getf(u4, 0x15f, l3); return; }
        if (i2 == 3) { cL4_ipc_obj_getf(u4, 0x160, l3); return; }
        if (i2 == 4) { cL4_ipc_obj_getf(u4, 0x16b, l3); return; }
    }
    __asm__ volatile("brk #1" ::: "memory");
}

/* FUN_00387bb8 @ 0x00387bb8   (est. cL4_obj_table_grow)
 * Ghidra: void FUN_00387bb8(param_1, ulong param_2, long param_3)
 * Grows the per-owner object table (base _DAT_006c0940/0x930): when the table
 * is full (count >= capacity), reallocates a doubled entry array (each entry
 * 2 words + header, tag 0x1000040504ffac1), copies the existing entries, and
 * queues the old array for deferred free. Then appends the new {start,end}
 * range (param_2, param_2+param_3) at slot count. Deferred frees drained when
 * the acquire counter hits 0.
 * Confidence: medium
 */
extern unsigned long cL4_tbl4_count;      /* _DAT_006c0938 */
extern unsigned long cL4_tbl4_cap;        /* _DAT_006c0930 */
extern unsigned long *cL4_tbl4_entries;   /* _DAT_006c0940 */
extern unsigned long *cL4_tbl4_freelist;  /* _DAT_006c0960 */


void cL4_obj_table_grow(unsigned long param_1, unsigned long start, long size)
{
    FUN_0001a1c8();                            /* per-cpu init */
    cL4_ref_acquire(0x6c0950);
    unsigned long *old = cL4_tbl4_entries;
    unsigned long cnt = (cL4_tbl4_entries == 0) ? 0 : *cL4_tbl4_entries;
    unsigned long cap = cL4_tbl4_cap;
    unsigned long *ne = cL4_tbl4_entries;
    if (cL4_tbl4_cap <= cnt) {
        cap = cnt * 2;
        if (cap < 0x11) cap = 0x10;
        ne = cL4_slot_alloc(((cap >> 1) << 5 | 8), 0x1000040504ffac1);
        if (ne == 0) { __asm__ volatile("brk #1" ::: "memory"); return; }
        *ne = 0;
        if (old != 0 && cnt != 0) {
            unsigned long *d = ne + 1, *s = old + 1;
            unsigned long n = cnt;
            do {
                unsigned long v = *s;
                d[1] = s[1];
                *d = v;
                n--; d += 2; s += 2;
            } while (n != 0);
            *ne = cnt;
            unsigned long *ln = cL4_slot_alloc(0x10, 0xa0040aff93c70);
            *ln = (unsigned long)cL4_tbl4_freelist;
            ln[1] = (unsigned long)old;
            cL4_tbl4_freelist = ln;
        }
    }
    cL4_tbl4_entries = ne;
    cL4_tbl4_cap = cap;
    unsigned long *e = cL4_tbl4_entries;
    e[cnt*2+1] = start;
    e[cnt*2+2] = start + size;
    *e = cnt + 1;
    DataMemoryBarrier(2,3);
    unsigned long *fl = cL4_tbl4_freelist;
    if (cL4_tbl4_count == 0) {
        while (fl != 0) {
            unsigned long *nxt = (unsigned long*)*fl;
            unsigned long n = 0xffffffffffffffffULL;
            do { n++; } while (n < *(unsigned long*)fl[1]);
            cL4_free((void*)fl[1], 0);
            cL4_free(fl, 0);
            fl = nxt;
        }
        cL4_tbl4_freelist = 0;
    }
    cL4_release(0x6c0950);
}

/* FUN_00387d50 @ 0x00387d50   (est. cL4_obj_init_zero)
 * Ghidra: void FUN_00387d50(undefined8 *param_1)
 * Zero-initializes a 0x68-word object, registers a wait queue at +0xe*8, and
 * runs FUN_0036c430.
 * Confidence: medium
 */
void cL4_obj_init_zero(unsigned long *obj)
{
    obj[0]=obj[1]=obj[2]=obj[5]=obj[4]=obj[7]=obj[6]=obj[8]=obj[11]=obj[12]=obj[10]=0;
    cL4_node_wait_init(obj + 0xe, 0);
    obj[0x10] = 0;
    cL4_obj_hw_init();                        /* FUN_0036c430 */
}
/* FUN_0036c430 @ 0x36c430 — object hardware-init hook. */

/* FUN_00387da0 @ 0x00387da0   (est. cL4_cap_kind_walk)
 * Ghidra: undefined8 FUN_00387da0(uint *param_1, long param_2)
 * Validates a capability chain: requires kind in {0x11..0x12}, enforces the
 * tag's exclusion rules (*(param_2+0x50)==1 forbids non-'t' names when the
 * tag count==1), then walks to the last cap (kind 0) via FUN_003658e8 and
 * dispatches FUN_0038ef30. Returns the final result.
 * Confidence: low
 */
unsigned long cL4_cap_kind_walk(unsigned int *cap, long tag)
{
    if (1 < (*cap & 0x1f) - 0x11) return 0;
    if (*(char *)(tag + 0x50) == '\x01') {
        if (*(long *)(tag + 0x38) == 1) {
            if (**(char **)(tag + 0x30) == 't' || *(long *)(tag + 0x48) != 0) return 0;
        } else if (*(long *)(tag + 0x48) != 0) {
            return 0;
        }
    }
    do {
        do { cap = (unsigned int *)cL4_cap_next(cap + 1); } while (cap == 0);
    } while (((*cap & 0x1f) != 0) || (cap == 0));
    return cL4_cap_final(cap);                /* FUN_0038ef30 */
}
/* FUN_003658e8 @ 0x3658e8 — next cap in a chain. */
extern unsigned int *cL4_cap_next(unsigned int *cap);
/* FUN_0038ef30 @ 0x38ef30 — final cap-chain dispatch. */
extern unsigned long cL4_cap_final(unsigned int *cap);

/* FUN_00387e60 @ 0x00387e60   (est. cL4_cap_desc_parse)
 * Ghidra: void FUN_00387e60(long *param_1, long param_2)
 * Parses a capability descriptor chain (param_2) into an expanded
 * descriptor (param_1): reads the inline cap (base+8, resolved via
 * thunk_FUN_00115080), and when the "has sub-caps" flag (bit2 of *(param_2+2))
 * is clear, copies the inline {cap,ref} pair; otherwise iterates the sub-cap
 * records, parsing 'S'/'R'/'N' records into the type/length/offset fields
 * (offsets +8/+0x18/+0x28/+0x38) with per-record length = resolved-1, and
 * records the sub-cap base (param_1[2]) and length (param_1[3]).
 * Confidence: low
 */
void cL4_cap_desc_parse(unsigned long *out, long desc)
{
    out[2] = 0;
    *(unsigned char *)(out + 10) = 0;
    out[3] = 0;
    *(unsigned char *)(out + 4) = 0;
    long base = desc + 8 + (long)*(int *)(desc + 8);
    long ref = (base == 0) ? 0 : cL4_cap_resolve(base);
    *out = base;
    out[1] = ref;
    if ((*(unsigned char *)(desc + 2) >> 2 & 1) == 0) {
        out[3] = out[1];
        out[2] = *out;
    } else {
        out[9]=out[8]=out[7]=out[6]=out[5]=0;
        *(unsigned char *)(out + 10) = 1;
        long p = base + ref;
        long p2 = p + 1;
        long r = cL4_cap_resolve(p2);
        long offN = 0, offS = 0, offR = 0;
        if (r != 0) {
            long cur = p;
            do {
                char c = *(char *)(cur + 1);
                if (c == 'S') {
                    offS = cur + 2;
                    *(long *)((long)out + 0x18 + 0x20) = r + -1;  /* +0x38 */
                    goto done_rec;
                } else if (c == 'R') {
                    offR = cur + 2;
                    *(long *)((long)out + 0x28 + 0x20) = r + -1;  /* +0x48 */
                    goto done_rec;
                } else if (c == 'N') {
                    long l5 = cur + 2;
                    *(long *)((long)out + 8 + 0x20) = r + -1;     /* +0x28 */
                    offN = l5;
                    goto done_rec;
                }
done_rec:
                cur = p + r;
                p2 = cur + 1;
                r = cL4_cap_resolve(p2);
            } while (r != 0);
            out[8] = offR;
            out[6] = offS;
        }
        out[2] = base;
        out[3] = p - base;
        out[4] = offN;
    }
}

/* FUN_00387fbc @ 0x00387fbc   (est. cL4_cap_authorize)
 * Ghidra: void FUN_00387fbc(uint *param_1, long *param_2)
 * The capability-authorization core: validates a capability descriptor chain
 * (param_2, linked through [0]) against the requesting cap word (param_1),
 * following the per-descriptor kind rules. It walks the linked cap records,
 * checking the descriptor tag word (param_2[2]) and length byte
 * (*(param_2+0x12)) against the cap kind (param_1&0x1f), building a 0x2b0-byte
 * expanded descriptor via cL4_cap_desc_parse / cL4_cap_kind_walk, and
 * verifying equality (thunk_FUN_001145b0) and the tag's exclusion rules. Each
 * successful match advances param_1 to the next cap (FUN_003658e8). Returns
 * 1 (via the implicit x1 path / canary) on full authorization, 0 on any
 * mismatch — a fail-closed authorization decision with no partial grants.
 * Confidence: low (large authorization state machine)
 */
extern unsigned long cL4_cap_match_obj(unsigned int *cap, unsigned long obj);
extern unsigned long cL4_cap_subcmp(unsigned long a, unsigned long b, unsigned long base);
extern unsigned long cL4_cap_build(unsigned long cap, unsigned long *out);
extern unsigned long cL4_cap_resolve_desc(unsigned int *cap, unsigned long *buf, unsigned long x);

unsigned long cL4_cap_authorize(unsigned int *cap, unsigned long *desc)
{
    unsigned long out = 0;
    unsigned long canary = (unsigned long)-0x2c8502b44bfffed6ULL;
    unsigned long buf[0x2b0/8];

    do {
        if (cap == 0) {
            out = (unsigned long)(desc == 0);
            goto done;
        }
        short tag = (short)desc[2];
        if (tag == 0xf4) {
            if (*(unsigned char *)((long)desc + 0x12) - 1 < 2) {
                desc = (unsigned long *)*desc;
                if (desc != 0) { tag = (short)desc[2]; goto tag_dispatch; }
            } else {
                if (*(unsigned char *)((long)desc + 0x12) == 5 && (int)desc[1] != 0) {
                    desc = (unsigned long *)*desc;
                }
                else {
                    desc = 0;
                }
            }
        } else {
tag_dispatch:
            if (tag == 0xf5 || tag == 0xc0) {
                unsigned long base = *cap;
                if (base == 0) base = 0;
                if ((cL4_cap_match_obj(cap, base) & 1) != 0) {
                    out = 1;
                    goto done;
                }
            }
        }
        uint32_t u2 = *cap;
        uint32_t u1 = u2 & 0x1f;
        if (u1 == 3) {
            if ((short)desc[2] != 0xbf) goto fail;
            unsigned char b3 = *(unsigned char *)((long)desc + 0x12);
            unsigned long *p11 = desc;
            unsigned long *p15;
            if (b3 == 2) p15 = (unsigned long*)p11[1];
            else if (b3 == 5 && 1 < *(uint32_t*)(desc + 1)) { p11 = (unsigned long*)*desc; p15 = (unsigned long*)p11[1]; }
            else p15 = 0;
            if (*(short*)(p15 + 2) != 0x67) goto fail;
            if ((int)cL4_cap_subcmp(*p15, p15[1], (long)(int)cap[2] + (long)(cap + 2)) == 0) goto done;
            if (b3 - 1 < 2) desc = (unsigned long*)*desc;
            else if (b3 == 5) { if ((int)desc[1] != 0) { desc = (unsigned long*)*desc; } else desc = 0; }
            else desc = 0;
        } else if (u1 != 1) {
            if (u1 == 0) {
                if ((short)desc[2] != 0xa3) goto fail;
                if ((cL4_cap_subcmp(*desc, desc[1], (long)(int)cap[2] + (long)(cap + 2)) & 1) == 0) goto fail;
                desc = 0;
            } else if ((u2 >> 4 & 1) != 0 && cap != 0) {
                /* the large expanded-descriptor branch: build buf via
                 * cL4_cap_desc_parse, dispatch on the record tag, verify the
                 * payload cap equality and the 't' name exclusion rules. */
                unsigned long p15b[3];
                unsigned short v5 = *(unsigned short*)(desc + 2);
                int b14;
                if (v5 > 0xb0) {
                    if (v5 == 0xb1) { b14 = 0; }
                    else if (v5 == 0xf6) {
                        cL4_cap_desc_parse(buf, (long)cap);
                        if (buf[10] == 1 && buf[0x278/8] == 1 && *(char*)((char*)buf + 1) == 't') b14 = 1;
                        else goto fail;
                    } else if (v5 == 0xe7) {
                        if ((u2 & 0x1f) == 0x11) b14 = 0;
                        else {
                            cL4_cap_desc_parse(buf, (long)cap);
                            b14 = 1;
                            if ((cL4_cap_kind_walk(cap, (long)buf) & 1) == 0) goto fail;
                        }
                    } else goto fail;
                } else if (v5 == 0x19) {
                    if ((u2 & 0x1f) == 0x10) b14 = 0; else goto fail;
                } else if (v5 != 0x3f || (u2 & 0x1f) != 0x12) goto fail;
                else b14 = 0;
                unsigned long *pl = desc;
                unsigned long *pv;
                if (*(char*)((long)desc + 0x12) == '\x02') pv = (unsigned long*)pl[1];
                else if (*(char*)((long)desc + 0x12) == '\x05' && 1 < *(uint32_t*)(desc + 1)) { pl = (unsigned long*)*desc; pv = (unsigned long*)pl[1]; }
                else pv = 0;
                if (*(short*)(pv + 2) == 0xd9) {
                    if (!b14) { cL4_cap_desc_parse(buf, (long)cap); }
                    unsigned char b3 = *(unsigned char*)((long)pv + 0x12);
                    unsigned long *p12 = pv;
                    if (1 < b3 - 1) p12 = (unsigned long*)*pv;
                    if (buf[0x260/8] == 1) {
                        unsigned long l13 = ((unsigned long*)*p12)[1];
                        if ((buf[0x268/8] == l13) && (l13 == 0 || cL4_cap_equal2(buf[0x270/8], *(unsigned long*)*p12, 0) == 0)) {
                            if (b3 == 2) pv = (unsigned long*)pv[1];
                            else if (b3 == 5 && 1 < *(uint32_t*)(pv + 1)) { pv = (unsigned long*)*pv; }
                            else pv = 0;
                        } else goto fail;
                    } else goto fail;
                } else if (!b14) {
                    cL4_cap_desc_parse(buf, (long)cap);
                }
                if (*(short*)(pv + 2) != 0x67) goto fail;
                unsigned long l13 = 0;
                if (buf[5] != 0) l13 = 0x20;
                if (buf[0x260/8] == 0) l13 = 0;
                if (pv[1] != *(unsigned long*)((long)buf + l13 + 8) ||
                    (pv[1] != 0 && cL4_cap_equal2(*pv, *(unsigned long*)((long)buf + l13), 0) != 0)) goto fail;
                if (1 < *(unsigned char*)((long)desc + 0x12) - 1) {
                    if (*(unsigned char*)((long)desc + 0x12) != 5) { desc = 0; }
                    else if ((int)desc[1] != 0) desc = (unsigned long*)*desc;
                    else desc = 0;
                } else desc = (unsigned long*)*desc;
            }
            goto fail;
        } else {
            if ((short)desc[2] != 0x49) goto fail;
            unsigned long *pl = desc;
            if (*(char*)((long)desc + 0x12) != '\x02') {
                if (*(char*)((long)desc + 0x12) != '\x05' || *(uint32_t*)(desc + 1) < 2) goto fail;
                pl = (unsigned long*)*desc;
            }
            memset(buf, 0, sizeof(buf));
            buf[0] = 0x67b7a8;
            unsigned long l13 = cL4_cap_build(pl[1], buf);       /* FUN_00388630 */
            unsigned long l9 = cL4_cap_resolve_desc(cap, buf, 0); /* FUN_00388c60 */
            int ok = 1;
            if ((l13 != 0 && l9 != 0) && cL4_cap_match_obj((unsigned int*)l13, l9) != 0) {
                if (1 < *(unsigned char*)((long)desc + 0x12) - 1) {
                    if (*(unsigned char*)((long)desc + 0x12) != 5 || (int)desc[1] == 0) { ok = 0; desc = 0; goto auth_done; }
                    desc = (unsigned long*)*desc;
                }
                ok = 0;
                desc = (unsigned long*)*desc;
            }
auth_done:
            if (ok) goto fail;
        }
        cap = (unsigned int*)cL4_cap_next(cap + 1);
    } while (1);
fail:
    out = 0;
done:
    if (canary != (unsigned long)-0x2c8502b44bfffed6ULL) cL4_stack_fail();
    return out;
}
