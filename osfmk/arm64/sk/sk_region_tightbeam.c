/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel,
 * arm64e, image base 0) — the cL4 microkernel (GL1), "cL4 (679.100.61)".
 * Ground truth: Ghidra FUN_ names + addresses in program cl4_kernel.raw.
 * This region (0x380000-0x400000) is the IPC / notification / message
 * register subsystem. All names are estimates unless string-matched. */

#include <stdint.h>
#include <stddef.h>

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
cL4_w16_t cL4_msg_result(unsigned long *msg_word, int kind);
cL4_w16_t cL4_msg_send_finalize(unsigned long *msg_word, void *obj, unsigned int opts);
void cL4_msg_finish(unsigned long *msg_word, void *obj, unsigned long d0,
                    unsigned long d1, unsigned long extra);
void cL4_msg_wake(unsigned long tcb, void *obj, unsigned long d0, unsigned long d1);

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

