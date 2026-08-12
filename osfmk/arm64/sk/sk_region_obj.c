/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel,
 * arm64e, image base 0) — the cL4 (Apple seL4-derived) microkernel (GL1).
 * Ground truth: Ghidra FUN_ names + addresses in program cl4_kernel.raw.
 * All names are estimates unless string/header-matched.
 *
 * This file covers the object/kernel-object machinery region
 * 0x280000 - 0x300000.
 *
 * SeL4/cL4 vocabulary is used for naming: TCB, cap, CNode, IPC, notification,
 * endpoint, vspace, sched, etc. Confidence is medium unless a string matches.
 */

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

/* Out-of-range kernel helpers referenced by this region (FUN_ addr in
 * comment; reconstructed by sibling SK range workers). Names are estimates. */

/* Core lock/refcount/allocator primitives (region 0x34xxxx-0x37xxxx). */
extern void *sk_alloc(unsigned long size, unsigned long tag);        /* FUN_0036a908 */
extern void *sk_alloc_pages(unsigned long size, unsigned long tag);  /* FUN_0036b270 */
extern void sk_free(void *ptr);                                      /* FUN_0036b118 */
extern unsigned long sk_object_lock(unsigned long a, unsigned long b,
                                    unsigned long c, void *dbg1, void *dbg2); /* FUN_00377824 */
extern unsigned long sk_lock_ref(unsigned long a, ...);               /* FUN_00377bec */
extern void sk_lock_release(unsigned long a, ...);                    /* FUN_00377dcc */
extern void sk_enable_irq(void);                                     /* FUN_00350ca4 */
extern unsigned long sk_spin_irqsave(unsigned long *flags);          /* FUN_00357cb4 */
extern void sk_irqrestore(unsigned long flags);                      /* FUN_00357c74 */

/* TCB/thread context helpers (region 0x0008xxxx). */
extern void *sk_current_tcb(void);                                   /* FUN_000867ec */
extern void *sk_cpu(void);                                           /* FUN_0008e518 */

/* Object method-dispatch table base used by object constructors. */
extern unsigned char sk_obj_methods_0[];  /* DAT_00611b24 */
extern unsigned char sk_obj_methods_1[];  /* DAT_00611b34 / DAT_00611b3c / LAB_00611b2c */

/* Forward declarations (functions reconstructed in this file). */
void *sk_object_create_impl(void **out_obj, void *param_2, void *param_3);
void sk_object_construct(void);
void sk_object_dispatch_sel(unsigned long sel);
void sk_object_kernel_dispatch(void);
void sk_object_sched_yield(void);
unsigned long sk_lock_release_pull(unsigned long a);
int sk_queue_complete(void *a, unsigned long b, ...);
void sk_object_resume(void);
void sk_object_store(void);
void sk_object_store_forward(void);
void sk_object_notify_loop(void);
void sk_object_wake(void);
unsigned int sk_swift_string_index_cmp(long, unsigned long, long, unsigned long);
void sk_object_service_w(void *param_1, void *param_2, void *param_3, void *param_4, void *param_5);
void sk_cap_setup(void *param_1, unsigned long slot, int type_idx, void *table, void *obj);
void *sk_cap_node_create_impl(void **out, unsigned long p2, unsigned long p3,
                              void *p4, void *p5, void *p6);

/* Swift runtime fatal-error (noreturn) and element-transform helpers. */
extern void sk_fatal_error(unsigned long, unsigned long, ...) __attribute__((noreturn)); /* FUN_001afe4c */
extern void sk_swift_release(unsigned long, ...);                    /* FUN_003a25d4 */
extern unsigned long sk_swift_string_index(unsigned long, unsigned long, unsigned long,
                                           unsigned long, unsigned long, ...); /* FUN_002aaf80 */
extern long sk_swift_str_buf(unsigned long, unsigned long, ...);     /* FUN_002a9ba8 */
extern unsigned long sk_swift_string_char_width(unsigned long, unsigned long,
                                                unsigned long, ...);  /* FUN_002c7020 */
extern unsigned long sk_swift_string_cmp(unsigned long, unsigned long, unsigned long,
                                         unsigned long, unsigned long, ...); /* FUN_002a0d50 */
extern void *sk_swift_elem_map(void);                                /* FUN_0029fb80 */
extern unsigned int sk_swift_elem_map_16(void);                      /* FUN_002b0c84 */
extern void sk_swift_string_index_next(void);                        /* FUN_00286b20 */
extern unsigned long sk_swift_next_char2(unsigned long, unsigned long, unsigned long,
                                         void *, void *);            /* FUN_002b439c */
extern unsigned long sk_swift_string_next(unsigned long, unsigned long, unsigned long,
                                          void *, void *);           /* FUN_002ab058 */
extern unsigned long sk_swift_advance2(unsigned long, unsigned long, unsigned long,
                                       void *, void *);              /* FUN_002b3d68 */
extern void *sk_swift_str_buf3(unsigned long, unsigned long, unsigned long); /* FUN_00267510 */
extern unsigned long sk_swift_string_char(unsigned long, unsigned long,
                                          unsigned long, ...);     /* FUN_0029ef1c */
extern unsigned long sk_swift_index_char(unsigned long, unsigned long, unsigned long,
                                         unsigned long, unsigned long, ...); /* FUN_002ab4d4 */
extern unsigned long sk_swift_elem_map16(void);                      /* FUN_0029fb80 */
extern unsigned long sk_swift_next_char(unsigned long, unsigned long, unsigned long,
                                        void *, void *);            /* FUN_002b439c */
extern unsigned long sk_swift_advance(unsigned long, unsigned long, unsigned long,
                                      void *, void *);              /* FUN_002b3b84 */
extern unsigned long sk_swift_elem_transform(unsigned long, void *, ...); /* FUN_00263360 */
extern unsigned long sk_swift_elem_transform2(void);                /* FUN_00264068 */
extern unsigned char sk_swift_unknown_5be7c0[];                     /* DAT_005be7c0 */
extern unsigned long sk_swift_string_hash(void);                    /* FUN_001a8564 */
extern void sk_swift_set_insert(long, unsigned long, unsigned long, void *); /* FUN_000b394c */
extern long sk_set_descriptor(void *);                              /* FUN_0025a060 */
extern void sk_set_insert(unsigned long, long, void *);             /* FUN_0025c2b8 */

static inline int sk_swift_utf8_len(unsigned int c)                  /* LZCOUNT(c<<24 ^ 0xffffffff) */
{
    unsigned int x = (c << 0x18) ^ 0xffffffff;
    int n = (int)__builtin_clzll((unsigned long)x) / 8 + 1;
    return (c < 0x80) ? 1 : n;
}
static inline long sk_swift_utf8_decode(unsigned int *out)
{
    unsigned int c = *out; int n = sk_swift_utf8_len(c);
    *out = c; return n;
}

/*--------------------------------------------------------------------*/
/* FUN_002800cc @ 0x002800cc   (est. sk_object_method_invoke)
 * Ghidra: undefined FUN_002800cc(undefined8 param_1, undefined8 param_2, long param_3)
 * Looks up the per-object method table (param_3+0x18) via FUN_0031ba70 and
 * performs an indirect call through the resolved entry, passing the object's
 * argument (x19+0x10). Wraps the call with FUN_000867ec (current-thread save).
 * Confidence: low (heavy indirect-call/jumptable structure; target resolved at
 *   runtime through a helper).
 * Notes: indirect jump at 0x0028011c not recoverable ("too many branches");
 *   FUN_0031ba70 / FUN_000b4390 unresolved helpers.
 */
void sk_object_method_invoke(void *param_1, void *param_2, void *obj)
{
    (void)param_1; (void)param_2;
    sk_current_tcb();
    /* FUN_0031ba70 resolves the dispatch table from obj->methods (obj+0x18). */
    void *table = (void *)sk_object_lock(*(unsigned long *)((char *)obj + 0x18), 0, 0, 0, 0);
    void (*entry)(void *a, void *b, void *c) = table;
    entry(table, ((void **)table)[1], *(void **)((char *)__builtin_frame_address(0) + 0x10));
    /* indirect jump through entry — jumptable not recoverable */
}

/*--------------------------------------------------------------------*/
/* FUN_00280120 @ 0x00280120   (est. sk_object_construct)
 * Ghidra: void FUN_00280120(void)
 * Constructor for a kernel object: acquires the per-object lock, resolves the
 * method table, and runs a sequence of object-init helpers. Finalizes with
 * FUN_0008e500 (thread epilogue).
 * Confidence: low (inlined init pipeline; many unresolved helpers).
 */
void sk_object_construct(void)
{
    /* FUN_0008e518 current-CPU; FUN_0035a6a8 / FUN_00351bec / FUN_00349748 /
     * FUN_00350ad0 / FUN_00377824 / FUN_00348e00 / FUN_0007c1a4 /
     * FUN_0034b0c4 / FUN_0031e104 / FUN_00350c50 / FUN_000e72b0 /
     * FUN_00352ecc / FUN_00350b48 / FUN_0035351c / FUN_00348b94 /
     * FUN_00349530 / FUN_00351d00 / FUN_003507bc / FUN_0008e500 */
    sk_object_lock(0, 0, 0, 0, 0);
    /* object fields at +0x10 / +0x18 dispatched via table at +0x18,
     * calls through DAT_00658c00 global jump slot. */
    (*(void (**)(void))(0x658c00))();  /* DAT_00658c00 */
}

/*--------------------------------------------------------------------*/
/* FUN_0028028c @ 0x0028028c   (est. sk_object_create)
 * Ghidra: undefined * FUN_0028028c(long *param_1, undefined8 param_2, undefined8 param_3)
 * Allocates a 0x28-byte object (tag 0x8087), stores it into *param_1, runs the
 * constructor FUN_00280300 on it, and records the returned vtable (DAT_003471a4).
 * Confidence: medium (clean allocate + construct + vtable-store shape).
 */
void *sk_object_create(void **slot, void *param_2, void *param_3)
{
    void *obj = sk_alloc(0x28, 0x8087);          /* FUN_0036a908(0x28, 0x8087) */
    *slot = obj;
    void *vtable = sk_object_create_impl(obj, param_2, param_3);  /* FUN_00280300 */
    *(void **)((char *)obj + 0x20) = vtable;
    return (void *)0x3471a4;  /* DAT_003471a4 — vtable */
}

/*--------------------------------------------------------------------*/
/* FUN_00280300 @ 0x00280300   (est. sk_object_create_impl)
 * Ghidra: undefined1 [16] FUN_00280300(long *param_1, undefined8 param_2, long param_3)
 * Allocates an instance descriptor for the object: resolves object type from
 * param_3+0x18, allocates a type-descriptor (tag 0xab22), and calls
 * FUN_00280120 (constructor). Returns a 16-byte {vtable, obj} pair.
 * Confidence: low (allocator plumbing, inlined).
 */
void *sk_object_create_impl(void **out_obj, void *param_2, void *param_3)
{
    unsigned long t = sk_object_lock(*(unsigned long *)((char *)param_3 + 0x18), 0, 0, 0, 0); /* FUN_00027754 */
    unsigned long t2 = sk_object_lock(0, 0, 0, 0, 0);  /* FUN_00027754 */
    void *desc = (void *)sk_object_lock(0, t2, *(unsigned long *)((char *)param_3 + 0x10),
                                        sk_obj_methods_0, sk_obj_methods_1);  /* FUN_00377824 */
    *out_obj = desc;
    void *type_desc = *(void **)((char *)desc - 8);
    out_obj[1] = type_desc;
    void *inst = sk_alloc(*(unsigned long *)((char *)type_desc + 0x40), 0xab22); /* FUN_0036a908 */
    out_obj[2] = inst;
    sk_object_construct();  /* FUN_00280120(inst, param_2, param_3) */
    return inst;
}

/*--------------------------------------------------------------------*/
/* FUN_002803d4 @ 0x002803d4   (est. sk_object_lock_teardown)
 * Ghidra: void FUN_002803d4(undefined8 param_1, long param_2)
 * Reinitializes object fields: sk_object_lock(0xff,...) on obj+0x10/+0x18,
 * then a sequence of teardown helpers. Likely lock + state reset.
 * Confidence: low.
 */
void sk_object_lock_teardown(void *param_1, void *obj)
{
    (void)param_1;
    sk_object_lock(0xff, *(unsigned long *)((char *)obj + 0x10),
                   *(unsigned long *)((char *)obj + 0x18), 0, 0); /* FUN_0031dc40 */
    /* FUN_00352efc / FUN_00310d68 / FUN_0034b690 / FUN_000839d8 */
}

/*--------------------------------------------------------------------*/
/* FUN_00280444 @ 0x00280444   (est. sk_object_destroy)
 * Ghidra: void FUN_00280444(void)
 * Object teardown path: saves CPU state (FUN_00084220), dispatches a
 * destruction callback through in_x3, and runs helper sequence before the
 * thread epilogue (FUN_00084234).
 * Confidence: low (indirect-call teardown).
 */
void sk_object_destroy(void)
{
    /* FUN_00084220 / FUN_003509ec; indirect call (*in_x3)(0, obj+0x10, x21+0x18);
     * then FUN_00348d64 / FUN_0007c1a4 / (*DAT_00658c00)() / FUN_0034b05c /
     * FUN_003547ec / FUN_0034ee48 / FUN_003504f4 / FUN_0034ded4 / FUN_00084234 */
    (*(void (**)(void))(0x658c00))();  /* DAT_00658c00 */
}

/*--------------------------------------------------------------------*/
/* FUN_00280504 @ 0x00280504   (est. sk_object_link_try)
 * Ghidra: bool FUN_00280504(void)
 * Insert-links an object into a singly-linked list head (*unaff_x20): if the
 * head is null, stores the new object; otherwise frees it (FUN_0036b118).
 * Returns true if the object was stored (head was empty).
 * Confidence: medium (clean list-insert/free-if-occupied shape).
 */
bool sk_object_link_try(void)
{
    void *head = *(void **)0;  /* *unaff_x20 */
    if (head == 0) {
        *(void **)0 = (void *)0;  /* unaff_x19 */
    }
    if (head != 0) {
        sk_free((void *)0);  /* FUN_0036b118 */
    }
    return head == 0;
}

/*--------------------------------------------------------------------*/
/* FUN_00280554 @ 0x00280554   (est. sk_object_alloc_pages)
 * Ghidra: void FUN_00280554(void)
 * Thin wrapper over the page allocator FUN_0036b270.
 * Confidence: medium (trivial wrapper).
 */
void sk_object_alloc_pages(void)
{
    sk_alloc_pages(0, 0);  /* FUN_0036b270 */
}

/*--------------------------------------------------------------------*/
/* FUN_00280570 @ 0x00280570   (est. sk_trap_dispatch_small)
 * Ghidra: void FUN_00280570(undefined8 param_1, undefined8 param_2, ulong param_3)
 * Decodes a capability/trap word param_3: for non-kernel (bit 60 clear) and
 * user-mode (bit 61 set) targets it extracts a 4-bit selector (bits 56-59)
 * and dispatches via FUN_002af74c(sel<<16 | 7); kernel target goes through
 * FUN_00106e3c / FUN_0029b9a8.
 * Confidence: low (trap-word decode, semantics inferred).
 */
void sk_trap_dispatch_small(void *param_1, void *param_2, unsigned long trap_word)
{
    (void)param_1; (void)param_2;
    sk_spin_irqsave(0);  /* FUN_00358fa8 */
    if ((trap_word >> 0x3c & 1) == 0) {
        unsigned long sel = 0;
        if ((trap_word & 0x2000000000000000) != 0) {
            sel = trap_word >> 0x38 & 0xf;
        }
        sk_object_dispatch_sel(sel << 0x10 | 7);  /* FUN_002af74c */
    } else {
        /* kernel/trusted path */
        sk_object_kernel_dispatch();  /* FUN_00106e3c */
        sk_object_sched_yield();      /* FUN_0029b9a8 */
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002805b8 @ 0x002805b8   (est. sk_object_complete)
 * Ghidra: void FUN_002805b8(void)
 * Trivial forwarder to FUN_00280b00.
 * Confidence: medium.
 */
void sk_object_complete(void)
{
    sk_object_resume();  /* FUN_00280b00 */
}

/*--------------------------------------------------------------------*/
/* FUN_002805e0 @ 0x002805e0   (est. sk_object_run_loop)
 * Ghidra: void FUN_002805e0(void)
 * Main object-service loop: resolves current CPU (FUN_0008e518), reads an
 * operation count from the per-CPU queue (x20 + cpu[0x24]), then repeatedly
 * pulls work items via FUN_00359530 / FUN_00377bec / FUN_000a68f4 dispatch
 * until the completion check FUN_000839f8 returns 1. Epilogue FUN_0008e500.
 * Confidence: low (service-loop structure, unresolved helpers).
 */
void sk_object_run_loop(void)
{
    /* FUN_0008e518 current CPU; loop over cpu->work_count (offset 0x24) */
    unsigned long count = 0;
    int done;
    do {
        count -= 1;
        if (count == 0) break;
        /* pull + dispatch a queued work item */
        unsigned long msg = sk_lock_ref(0);   /* FUN_00377bec */
        void (*dispatch)(unsigned long, unsigned long) = (void *)sk_alloc_pages(0, 0); /* FUN_000a68f4 */
        dispatch(sk_lock_release_pull(0), msg); /* FUN_00377dcc + FUN_00358d4c */
        done = sk_queue_complete(0, 0);        /* FUN_000839f8 */
    } while (done != 1);
    /* FUN_0034ece8 / FUN_0008e500 epilogue */
}

/*--------------------------------------------------------------------*/
/* FUN_00280798 @ 0x00280798   (est. sk_object_count_bump)
 * Ghidra: void FUN_00280798(void)
 * Reads a per-CPU counter (x20 + cpu[0x24]) and adds the CPU value (auVar4._0_8_)
 * to it with overflow check; on carry it takes a breakpoint (0x280870). On
 * success calls FUN_002805b8 (completion). Overflow is a hard trap.
 * Confidence: low (counter math + overflow trap).
 */
void sk_object_count_bump(void)
{
    /* FUN_00084220 current CPU; count at x20 + cpu[0x24] */
    long base = 0;
    unsigned long delta = 0;
    if (!__builtin_add_overflow(base, delta, &base)) {
        sk_object_complete();  /* FUN_002805b8 */
        return;
    }
    /* WARNING: overflow -> SoftwareBreakpoint(1, 0x280870) noreturn */
    __builtin_trap();
}

/*--------------------------------------------------------------------*/
/* FUN_00280870 @ 0x00280870   (est. sk_object_dispatch_loop)
 * Ghidra: void FUN_00280870(undefined8 param_1, long param_2)
 * Object service dispatch: takes lock on obj fields (+0x10/+0x18), dispatches
 * a work callback through the method table (param_2-8 + 0x10), then loops over
 * the per-CPU work count (param_2+0x24), invoking sk_object_lock/sk_lock_ref
 * and the completion callback FUN_000839f8 for each queued item.
 * Confidence: low (dispatch loop, unresolved helper identity).
 */
void sk_object_dispatch_loop(void *param_1, void *obj)
{
    (void)param_1;
    unsigned long lk1 = *(unsigned long *)((char *)obj + 0x10);
    unsigned long lk2 = *(unsigned long *)((char *)obj + 0x18);
    unsigned long ctx = sk_object_lock(0xff, lk2, lk1, sk_obj_methods_0, sk_obj_methods_1); /* FUN_00377824 */
    void *type = *(void **)(ctx - 8);
    /* FUN_00310d68; call (*(obj-8 + 0x10))(...) */
    void (*entry)(void *, unsigned long, unsigned long) = *(void **)((char *)ctx - 8 + 0x10);
    entry(param_1, lk1, lk2);
    /* per-CPU work-count loop at obj+0x24 */
    unsigned long count = *(unsigned long *)((char *)obj + 0x24);
    unsigned long n = (count & ((long)count >> 0x3f ^ -1UL)) + 1;
    int done = 0;
    do {
        n -= 1;
        if (n == 0) return;
        unsigned long lk = sk_object_lock(0xff, lk2, lk1, sk_obj_methods_0, (void *)0x611b3c); /* FUN_00377824 */
        unsigned long item = sk_lock_ref(lk2, lk1, lk, sk_obj_methods_0, (void *)0x611b2c); /* FUN_00377bec */
        void (*cb)(void *, unsigned long, unsigned long) = (void *)sk_alloc_pages(0, 0); /* FUN_000a68f4 */
        sk_lock_release(0, lk);  /* FUN_00377dcc */
        cb(param_1, item, item);
        int done = sk_queue_complete(param_1, 1, ctx);  /* FUN_000839f8 */
        /* (*(type + 8))(param_1, ctx) */
    } while (done != 1);
}

/*--------------------------------------------------------------------*/
/* FUN_00280ad8 @ 0x00280ad8   (est. sk_object_resume_forward)
 * Ghidra: void FUN_00280ad8(void)
 * Forwarder to FUN_00280b00 (resume).
 * Confidence: medium.
 */
void sk_object_resume_forward(void)
{
    sk_object_resume();
}

/*--------------------------------------------------------------------*/
/* FUN_00280b00 @ 0x00280b00   (est. sk_object_resume)
 * Ghidra: void FUN_00280b00(void)
 * Resumes a blocked/preempted object service: on success (helper >= 0) runs the
 * scheduler-install helpers (FUN_00353274/FUN_00356ba4/...) and writes the
 * result into the per-CPU slot (x21 + ctx[0x24]); on failure runs the
 * teardown path and jumps to the noreturn panic FUN_001afe4c.
 * Confidence: low (resume/scheduler path with noreturn failure branch).
 */
void sk_object_resume(void)
{
    long ret = sk_spin_irqsave(0);  /* FUN_00357ca0 */
    if (ret >= 0) {
        /* FUN_00353274 / FUN_00356ba4 / FUN_0034b07c / FUN_0034d3f4;
         * store ret into x21[ctx[0x24]] via FUN_00357c44 */
    } else {
        /* failure: FUN_0035047c / FUN_0034951c / FUN_0006f768 /
         * FUN_00356358 / FUN_003523f0 -> noreturn FUN_001afe4c */
        __builtin_trap();
    }
}

/*--------------------------------------------------------------------*/
/* FUN_00280ba0 @ 0x00280ba0   (est. sk_object_store_forward)
 * Ghidra: void FUN_00280ba0(void)
 * Forwarder to FUN_00280bc4.
 * Confidence: medium.
 */
void sk_object_store_forward(void)
{
    sk_object_store();  /* FUN_00280bc4 */
}

/*--------------------------------------------------------------------*/
/* FUN_00280bc4 @ 0x00280bc4   (est. sk_object_store)
 * Ghidra: void FUN_00280bc4(void)
 * Acquires object lock and stores the caller-provided value (x22) into the
 * per-CPU slot (x24 + ctx[0x24]) after an indirect dispatch helper.
 * Confidence: low.
 */
void sk_object_store(void)
{
    /* FUN_0034a354 / FUN_003516cc / FUN_00356358 / FUN_00377824 /
     * FUN_00349530; (*ctx + 0x20)(); FUN_00350530;
     * ctx = (*in_x6)(...); x24[ctx[0x24]] = x22 */
    sk_object_lock(0, 0, 0, 0, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_00280c40 @ 0x00280c40   (est. sk_object_ref_release)
 * Ghidra: void FUN_00280c40(void)
 * Releases an object reference: if the per-CPU refcount (x20 + ctx[0x24]) is
 * nonzero, decrements it and runs the release helper chain; if zero, runs the
 * final teardown (FUN_003497a0) on the object fields. Jumptable call at the
 * end is not recoverable.
 * Confidence: low (refcount release with teardown branch).
 */
void sk_object_ref_release(void)
{
    /* FUN_00357cb4 spin_irqsave */
    long refs = *(long *)((char *)0 + 0x24);
    if (refs != 0) {
        /* x20[ctx[0x24]] = refs - 1 */
        /* FUN_00350ca4 / FUN_0034c444 / FUN_00377824 / FUN_000b4390 /
         * FUN_00352ae4 / FUN_00377bec / FUN_000a68f4 / FUN_0035050c /
         * FUN_00377dcc / FUN_00357c74; then indirect jump */
    } else {
        /* FUN_003497a0(ctx, ctx+0x18, ctx+0x10); FUN_00377824;
         * FUN_0034b690; FUN_00357c74; FUN_000839d8 */
        sk_object_lock(0, 0, 0, 0, 0);
    }
}

/*--------------------------------------------------------------------*/
/* FUN_00280d00 @ 0x00280d00   (est. sk_object_teardown_svc)
 * Ghidra: void FUN_00280d00(void)
 * Object teardown service: saves CPU state, dispatches through the method
 * table (obj+0x18), runs helper chain, then calls FUN_00280ba0 (store) and
 * the thread epilogue FUN_00084234.
 * Confidence: low.
 */
void sk_object_teardown_svc(void)
{
    /* FUN_00084220 / FUN_003494e8 / (*DAT_00658c00)(ctx+0x40) /
     * FUN_00348f50 / FUN_00349830 / FUN_003508d8 / FUN_00377824 /
     * FUN_00351f10 / FUN_0007c1a4 / FUN_0034aee4 / FUN_0034db68 /
     * FUN_000a68c4 / FUN_00350b24 / FUN_0035072c / FUN_0034b804 /
     * FUN_00353f20 / FUN_00350624 / FUN_00280ba0 / FUN_00084234 */
    (*(void (**)(void))(0x658c00))();
    sk_object_store_forward();
}

/*--------------------------------------------------------------------*/
/* FUN_00280e48 @ 0x00280e48   (est. sk_object_notify_loop)
 * Ghidra: void FUN_00280e48(void)
 * Notification dispatch loop: repeatedly pulls notifications (FUN_00377bec /
 * FUN_000a68f4), dispatches to the object's notify handler (obj-8 + 0x10),
 * and loops until the completion predicate (FUN_000839f8) returns. Wakes the
 * waiter (FUN_0029b9a8-style) and finalizes with FUN_00353d14.
 * Confidence: low (notify service loop, heavy indirect dispatch).
 */
void sk_object_notify_loop(void)
{
    /* FUN_00353cfc / FUN_003520f8 / FUN_00350500 / FUN_00377824 /
     * FUN_00348d7c / FUN_0007c1a4 / (*DAT_00658c00)() / FUN_0034b71c /
     * FUN_00350720 / FUN_00310d68 / FUN_000a6f88 / FUN_00348a34 /
     * FUN_0034b87c / FUN_00350798 / FUN_0031b990 / FUN_00350744 /
     * FUN_000839d8 / FUN_00350500 / FUN_0035053c / FUN_00377824 /
     * FUN_0034ab20 / FUN_0034b278 / FUN_0034c818 / FUN_00377bec /
     * FUN_000a68f4 / FUN_00350b24 / FUN_00084174 / FUN_00351b38 */
    void (*notify)(unsigned long, void *, void *, void *) =
        (void *)(0xe3ba000000000000UL | 0x10);
    /* loop: notify(...); completion check FUN_000839f8; on done goto epilogue */
    for (;;) {
        /* pull a notification, dispatch, check FUN_00352560/FUN_00350884 */
        unsigned long state = 0;
        if (sk_queue_complete(0, 0)) break;   /* FUN_003567d4 path */
        /* FUN_00352b14 / FUN_00353f5c / FUN_00351f4c */
    }
    /* FUN_003567d4 / FUN_00353d14 epilogue */
}

/*--------------------------------------------------------------------*/
/* FUN_00281128 @ 0x00281128   (est. sk_object_destroy_svc)
 * Ghidra: void FUN_00281128(undefined8 param_1, undefined8 param_2, undefined8 param_3)
 * Object-destroy service: takes the object lock, resolves the object type
 * (FUN_0031b990), invokes the per-type destructor (FUN_00280e48), and if the
 * waiter is null releases the type's method table slot. Epilogue FUN_00353d14.
 * Confidence: low.
 */
void sk_object_destroy_svc(void *param_1, void *param_2, void *param_3)
{
    (void)param_1; (void)param_2;
    /* FUN_00353cfc / FUN_00356c84 / FUN_00353aa0 / FUN_0034d5fc /
     * FUN_00377824 / FUN_00351f10 / FUN_0007c1a4 / (*DAT_00658c00)() /
     * FUN_0034b05c / FUN_0034f614 / FUN_0031b990 / FUN_00348cd0 /
     * FUN_0034b460 */
    int type_idx = *(int *)((char *)0 + 0x24);
    /* FUN_0034d3e4 / FUN_00377824 / FUN_00350744 / FUN_000839d8 /
     * FUN_000a68c4 / FUN_0034f654 / FUN_003530a4 / FUN_00354318 /
     * FUN_00280e48 / FUN_003508e4 / FUN_00310d68 / FUN_000841a0 */
    sk_object_notify_loop();  /* FUN_00280e48 */
    if (0 == 0) {             /* unaff_x21 == 0 */
        /* FUN_003504ac / (*extraout_x8)() */
    }
    /* FUN_00352df4 / FUN_00353d14 epilogue */
}

/*--------------------------------------------------------------------*/
/* (next function) */


/*--------------------------------------------------------------------*/
/* FUN_00281288 @ 0x00281288   (est. sk_object_finalize)
 * Ghidra: void FUN_00281288(undefined8 param_1,long param_2)
 * Finalizes an object: reads its type index (param_2+0x24), runs the lock
 * teardown (FUN_00349b14) over the object fields, then dispatches through the
 * per-type finalizer table (extraout_x16+0x10) on obj+idx. Indirect jump not
 * recoverable.
 * Confidence: low.
 */
void sk_object_finalize(void *param_1, void *obj)
{
    (void)param_1;
    int idx = *(int *)((char *)obj + 0x24);
    /* FUN_00349b14(obj, obj+0x18, obj+0x10); FUN_00377824; FUN_00352efc;
     * FUN_00310d68; FUN_00350404 */
    sk_object_lock(0, 0, 0, 0, 0);
    void (*finalizer)(void *, void *, void *) = *(void **)((char *)obj - 8 + 0x10);
    finalizer(param_1, (char *)0 + idx, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_00281358 @ 0x00281358   (est. sk_object_destroy_dispatch)
 * Ghidra: void FUN_00281358(void)
 * Object destroy dispatch: saves CPU state, resolves object type
 * (FUN_0031dc70), reads type index (+0x24), then calls the per-type destroy
 * handler (extraout_x16_00+0x28) and per-CPU slot helpers.
 * Confidence: low (indirect destroy dispatch).
 */
void sk_object_destroy_dispatch(void)
{
    /* FUN_00084220 / FUN_0035199c / FUN_00356334 / FUN_0034d024 /
     * FUN_0031dc70 / FUN_0034d1b0 / FUN_00377824 / FUN_00350744 /
     * FUN_000839d8 / FUN_0034d1b0 / FUN_00377824 / FUN_00349530 /
     * FUN_00350720 / FUN_00310d68 / FUN_0034ad10 */
    sk_object_lock(0, 0, 0, 0, 0);
    int idx = *(int *)((char *)0 + 0x24);
    void (*destroy)(void *) = *(void **)((char *)0 - 8 + 0x28);
    destroy((char *)0 + idx);
}

/*--------------------------------------------------------------------*/
/* FUN_0028160c @ 0x0028160c   (est. sk_object_service_entry)
 * Ghidra: void FUN_0028160c(void)
 * Object service entry: saves thread state (FUN_0008e518), acquires object
 * lock (FUN_00350968(0xff)), runs service helpers, then forwards to
 * FUN_00281358 (destroy dispatch). Epilogue FUN_0008e500.
 * Confidence: low.
 */
void sk_object_service_entry(void)
{
    /* FUN_0008e518 / FUN_00358f78 / FUN_00352078 / FUN_00350968(0xff) /
     * FUN_00377824 / FUN_00352efc / FUN_00310d68 / FUN_00348d4c /
     * FUN_0007c1a4 / (*DAT_00658c00)() / FUN_0034b0d4 / FUN_003504e8 /
     * FUN_00352c28 / FUN_00377824 / FUN_000a6f88 / FUN_0034aee4 /
     * FUN_0035084c / FUN_00350a04 / FUN_0035053c */
    sk_object_lock(0xff, 0, 0, 0, 0);
    (*(void (**)(void))(0x658c00))();
    sk_object_destroy_dispatch();  /* FUN_00281358 */
}

/*--------------------------------------------------------------------*/
/* FUN_00281734 @ 0x00281734   (est. sk_object_service_notify)
 * Ghidra: void FUN_00281734(undefined8 param_1,undefined8 param_2,long param_3)
 * Object service with notification: acquires lock, runs a notify/wake path
 * (FUN_00280e48) or a release path depending on the wake flag; ends with
 * epilogue FUN_00353d14. Contains the same indirect-dispatch pattern as the
 * other service loops.
 * Confidence: low.
 */
void sk_object_service_notify(void *param_1, void *param_2, void *obj)
{
    (void)param_1; (void)param_2;
    /* FUN_00353cfc / FUN_00350798 / FUN_00351280 / FUN_00377824 /
     * FUN_000a6f88 / FUN_0007c1a4 / (*DAT_00658c00)() / FUN_0034b6f4 /
     * FUN_00350ed0(0xff) / FUN_00377824 / FUN_0034e67c / FUN_00310d68 /
     * FUN_000a6f88 / FUN_0034bdfc / FUN_0034a5c8 / FUN_0034b0c4 /
     * FUN_00353aec(uVar3, x20 + obj[0x24]) */
    unsigned long w = 0;
    if (w) {
        /* FUN_0009461c(*(x16_00+8)) */
    } else {
        /* FUN_0035792c / FUN_00350b9c; w = (*pcVar1)();
         * if x21 != 0: release path (FUN_0034b804, ...);
         * else if (w & 1): FUN_003510ac(...) then FUN_0034ef98 + FUN_00280e48 */
        sk_object_notify_loop();
    }
    /* FUN_00352df4 / FUN_00353d14 epilogue */
}

/*--------------------------------------------------------------------*/
/* FUN_002819c8 @ 0x002819c8   (est. sk_object_service_tail)
 * Ghidra: void FUN_002819c8(long param_1)
 * Calls FUN_0028160c then dispatches through the object's method table
 * (param_1-8 + 8) via an unrecoverable indirect jump.
 * Confidence: low.
 */
void sk_object_service_tail(void *obj)
{
    sk_object_service_entry();  /* FUN_0028160c */
    void (*tail)(void) = *(void **)((char *)obj - 8 + 8);
    tail();
}

/*--------------------------------------------------------------------*/
/* FUN_00281a18 @ 0x00281a18   (est. sk_object_wake_forward)
 * Ghidra: void FUN_00281a18(void)
 * Forwarder to FUN_00281a54.
 * Confidence: medium.
 */
void sk_object_wake_forward(void)
{
    sk_object_wake();  /* FUN_00281a54 */
}

/*--------------------------------------------------------------------*/
/* FUN_00281a54 @ 0x00281a54   (est. sk_object_wake)
 * Ghidra: void FUN_00281a54(void)
 * Object wake: runs a sequence of scheduler/lock helpers
 * (FUN_00357198/FUN_0034a210/FUN_00002534/FUN_003498c4/FUN_0035a0b8/
 * FUN_00352ea8) then an indirect wake call (*in_x6).
 * Confidence: low.
 */
void sk_object_wake(void)
{
    /* FUN_00357198 / FUN_0034a210 / FUN_00002534 / FUN_003498c4 /
     * FUN_0035a0b8 / FUN_00352ea8(in_x5) ; (*in_x6)() */
}

/*--------------------------------------------------------------------*/
/* FUN_00281b08 @ 0x00281b08   (est. sk_object_service2)
 * Ghidra: void FUN_00281b08(void)
 * Second object-service flavor: thread-save (FUN_0008e518), dispatch via
 * FUN_0007c1c4, epilogue FUN_0008e500.
 * Confidence: low.
 */
void sk_object_service2(void)
{
    /* FUN_0008e518 / FUN_00356c84 / FUN_003537fc / FUN_00349a68 /
     * (*DAT_00658c00)(x8+0x40) / FUN_003491ec / FUN_00351c4c /
     * FUN_0007c1c4 / FUN_0035767c / FUN_0035072c / FUN_003548b8 /
     * FUN_0008e500 */
    (*(void (**)(void))(0x658c00))();
}

/*--------------------------------------------------------------------*/
/* FUN_00281bf0 @ 0x00281bf0   (est. sk_object_resume2)
 * Ghidra: void FUN_00281bf0(void)
 * Object resume with failure path: on success (FUN_0035acfc >= 0) runs the
 * scheduler-install chain and FUN_0019e578/FUN_001d614c; on failure runs
 * FUN_003488bc(1) and jumps to noreturn panic FUN_001afe4c.
 * Confidence: low.
 */
void sk_object_resume2(void)
{
    long ret = sk_spin_irqsave(0);  /* FUN_0035acfc */
    if (ret >= 0) {
        /* FUN_00353274 / FUN_003497a0 / FUN_00377824 / FUN_00353ef0 /
         * FUN_0019e578 / FUN_0035113c / FUN_00310d34 / FUN_00348718 /
         * FUN_00376820 / FUN_00356a14 / FUN_00351c70 / FUN_001d614c /
         * FUN_0035841c */
    } else {
        /* FUN_003488bc(1); FUN_0034987c; noreturn FUN_001afe4c */
        __builtin_trap();
    }
}

/*--------------------------------------------------------------------*/
/* FUN_00281cc0 @ 0x00281cc0   (est. sk_swift_array_init_repeat)
 * Ghidra: long FUN_00281cc0(undefined8 *param_1,long param_2,long param_3,
 *        undefined8 param_4, undefined8 param_5)
 * Swift Array(repeating:count:) initializer: writes `count` copies of the
 * element {param_4,param_5} into the destination buffer param_2, enforcing a
 * capacity bound of 2 (only the first two elements fit; further fills hit the
 * noreturn Range fatal error FUN_001afe4c). Returns the count written.
 * Confidence: high (Swift Array init_repeat shape, string-matched fatal err).
 */
long sk_swift_array_init_repeat(void *out, long dest, long count,
                                 unsigned long elem_a, unsigned long elem_b)
{
    if (dest == 0) {
        count = 0;
    } else {
        if (count < 0) {
            /* "Range requires lowerBound <= upperBound" -> noreturn */
            sk_fatal_error(0xb, 2, "Range requires lowerBound <= upperBound",
                           0x27, 2, "Swift.Range", 0x11, 2, 0xb5, 1);  /* FUN_001afe4c */
        }
        if (count != 0) {
            long i = 0;
            do {
                if (count == i) {
                    /* "Index out of range" -> noreturn */
                    sk_fatal_error(0xb, 2, "Index out of range", 0x12, 2,
                                   "Swift.Range", 0x11, 2, 0x136, 1);
                }
                if (i == 2) { count = 2; break; }
                unsigned long e = (i != 0) ? elem_b : elem_a;
                *(unsigned long *)(dest + i * 8) = e;
                i += 1;
            } while (count != i);
        }
    }
    ((unsigned long *)out)[0] = elem_a;
    ((unsigned long *)out)[1] = elem_b;
    ((unsigned long *)out)[2] = count;
    return count;
}

/*--------------------------------------------------------------------*/
/* FUN_00281d4c @ 0x00281d4c   (est. sk_swift_string_utf16_append)
 * Ghidra: ulong FUN_00281d4c(uint *param_1,long param_2,ulong param_3,uint param_4)
 * Swift String UTF-16 append helper: UTF-16-encodes the Unicode scalar
 * param_4 into the destination buffer param_2 (surrogate-pair logic), bound
 * checking against param_3; the count is capped at 2 code units. Returns the
 * number of UTF-16 units written. Fatal-error paths (noreturn FUN_001afe4c)
 * on negative count / index-out-of-range.
 * Confidence: high (Swift String.UTF16View append, string-matched).
 */
unsigned long sk_swift_string_utf16_append(unsigned int *out, long dest,
                                           unsigned long count, unsigned int scalar)
{
    unsigned long n;
    if (dest == 0) {
        n = 0;
    } else {
        if ((long)count < 0) {
            /* "Range requires lowerBound <= upperBound" -> noreturn */
            sk_fatal_error(0xb, 2, "Range requires lowerBound <= upperBound", 0x27,
                           2, "Swift.Range", 0x11, 2, 0xb5, 1);
        }
        n = count;
        if (count != 0) {
            unsigned long i = 0;
            unsigned int surrogate = (scalar + 0x3ff0000 >> 10 & 0xffff) + 0xd800;
            do {
                if (count == i) {
                    /* "Index out of range" -> noreturn */
                    sk_fatal_error(0xb, 2, "Index out of range", 0x12, 2,
                                   "Swift.Range", 0x11, 2, 0x136, 1);
                }
                unsigned long units; unsigned int unit; 
                if (scalar < 0x10000) {
                    units = 1; n = 1; unit = scalar;
                    if (i == 1) break;
                } else if (i == 1) {
                    units = 2; unit = scalar & 0x3ff | 0xffffdc00;
                } else {
                    if (i == 2) { n = 2; break; }
                    if (surrogate >> 0x10 != 0) {
                        /* SoftwareBreakpoint(1, 0x281ef4) noreturn */
                        __builtin_trap();
                    }
                    units = 2; unit = surrogate;
                }
                if (units <= i) {
                    /* "Index out of bounds" -> noreturn */
                    sk_fatal_error(0xb, 2, "Index out of bounds", 0x13, 2,
                                   "Swift.Collection", 0x16, 2, 0x2ca, 1);
                }
                *(short *)(dest + i * 2) = (short)unit;
                i += 1;
                n = count;
            } while (count != i);
        }
    }
    out[0] = scalar;
    *(unsigned long *)(out + 2) = n;
    return n;
}

/*--------------------------------------------------------------------*/
/* FUN_00281ef4 @ 0x00281ef4   (est. sk_swift_string_utf8_append)
 * Ghidra: ulong FUN_00281ef4(uint *param_1,long param_2,ulong param_3,uint param_4)
 * Swift String UTF-8 append helper: UTF-8-encodes the Unicode scalar param_4
 * (1-4 bytes) into dest param_2, bound-checking against param_3. Returns the
 * number of UTF-8 bytes written. Uses LZCOUNT to compute the encoded length.
 * Confidence: high (Swift UTF8View append, string-matched fatal errors).
 */
unsigned long sk_swift_string_utf8_append(unsigned int *out, long dest,
                                          unsigned long count, unsigned int scalar)
{
    unsigned long n;
    if (dest == 0) {
        n = 0;
    } else {
        if ((long)count < 0) {
            /* "Range requires lowerBound <= upperBound" -> noreturn */
            sk_fatal_error(0xb, 2, "Range requires lowerBound <= upperBound", 0x27,
                           2, "Swift.Range", 0x11, 2, 0xb5, 1);
        }
        n = count;
        if (count != 0) {
            unsigned long i = 0;
            unsigned int c = scalar >> 6 & 0x3f | (scalar & 0x3f) << 8;
            do {
                if (count == i) {
                    /* "Index out of range" -> noreturn */
                    sk_fatal_error(0xb, 2, "Index out of range", 0x12, 2,
                                   "Swift.Range", 0x11, 2, 0x136, 1);
                }
                n = i;
                unsigned int enc;
                if (scalar < 0x80) {
                    if (i == 1) break;
                    enc = scalar + 1;
                    if (i != 0) {
                        /* "Unicode.Scalar.UTF8View index is invalid" -> noreturn */
                        sk_fatal_error(0xb, 2, "Unicode.Scalar.UTF8View index is invalid",
                                       0x2e, 2, "Swift.UnicodeScalar", 0x19, 2, 0x1e2, 1);
                    }
                } else if (scalar < 0x800) {
                    if (i == 2) break;
                    enc = (scalar & 0x3f) * 0x100 + (scalar >> 6) + 0x81c1;
                    if (1 < i) goto invalid_index;
                } else if (scalar >> 0x10 == 0) {
                    if (i == 3) break;
                    enc = (scalar >> 0xc) + c * 0x100 + 0x8181e1;
                    if (2 < i) goto invalid_index;
                } else {
                    enc = ((c << 8 | scalar >> 0xc & 0x3f) << 8 | scalar >> 0x12) + 0x818181f1;
                    if (i == 4) break;
                }
                {
                    unsigned long len = (unsigned long)(4 - ((int)__builtin_clzll(enc) >> 3));
                    unsigned long mask = -1UL << ((len & 7) << 3);
                    unsigned long packed = enc + 0xfefefefefefeff & ~mask;
                    if (len <= i) {
                        /* "Index out of bounds" on UnsafeBufferPointer -> noreturn */
                        sk_fatal_error(0xb, 2, "Index out of bounds", 0x13, 2,
                                       "Swift.UnsafeBufferPointer", 0x1f, 2, 0x75e, 1);
                    }
                    *(unsigned char *)(dest + i) = *(unsigned char *)((char *)&packed + i);
                }
                i += 1;
                n = count;
            } while (count != i);
        }
    }
    out[0] = scalar;
    *(unsigned long *)(out + 2) = n;
    return n;
invalid_index:
    /* "Unicode.Scalar.UTF8View index is invalid" -> noreturn */
    sk_fatal_error(0xb, 2, "Unicode.Scalar.UTF8View index is invalid", 0x2e, 2,
                   "Swift.UnicodeScalar", 0x19, 2, 0x1e2, 1);
}

/*--------------------------------------------------------------------*/
/* FUN_002821c4 @ 0x002821c4   (est. sk_swift_array_init_repeat_2elem)
 * Ghidra: long FUN_002821c4(undefined8 *param_1,long param_2,long param_3,
 *        undefined8 param_4, undefined8 param_5)
 * Swift Array init(repeating:) for a 2-word element type: writes up to 2
 * copies, with Range/Index fatal-error paths (noreturn FUN_001afe4c).
 * Confidence: high (Swift Array init_repeat, string-matched).
 */
long sk_swift_array_init_repeat_2elem(void *out, long dest, long count,
                                      unsigned long elem_a, unsigned long elem_b)
{
    if (dest == 0) {
        count = 0;
    } else {
        if (count < 0) {
            sk_fatal_error(0xb, 2, "Range requires lowerBound <= upperBound", 0x27,
                           2, "Swift.Range", 0x11, 2, 0xb5, 1);
        }
        if (count != 0) {
            long i = 0;
            do {
                if (count == i) {
                    sk_fatal_error(0xb, 2, "Index out of range", 0x12, 2,
                                   "Swift.Range", 0x11, 2, 0x136, 1);
                }
                if (i == 2) { count = 2; break; }
                unsigned long elems[2] = { elem_a, elem_b };
                *(unsigned long *)(dest + i * 8) = elems[i];
                i += 1;
            } while (count != i);
        }
    }
    ((unsigned long *)out)[0] = elem_a;
    ((unsigned long *)out)[1] = elem_b;
    ((unsigned long *)out)[2] = count;
    return count;
}

/*--------------------------------------------------------------------*/
/* FUN_00282300 .. FUN_002825f8   (est. sk_swift_range_fatal)
 * Ghidra: void FUN_00282300(void) ... (six identical bodies)
 * Each is a noreturn stub raising the Swift Range precondition
 * "Range requires lowerBound <= upperBound" (fatal error 0xb, code 0xb5,
 * "Swift.Range" 0x11). These are the failure targets of the collection
 * initializers above.
 * Confidence: high (string-matched).
 */
void sk_swift_range_fatal(void)  /* FUN_00282300 */
{
    sk_fatal_error(0xb, 2, "Range requires lowerBound <= upperBound", 0x27,
                   2, "Swift.Range", 0x11, 2, 0xb5, 1);
}
void sk_swift_range_fatal_398(void)  /* FUN_00282398 */
{
    sk_fatal_error(0xb, 2, "Range requires lowerBound <= upperBound", 0x27,
                   2, "Swift.Range", 0x11, 2, 0xb5, 1);
}
void sk_swift_range_fatal_430(void)  /* FUN_00282430 */
{
    sk_fatal_error(0xb, 2, "Range requires lowerBound <= upperBound", 0x27,
                   2, "Swift.Range", 0x11, 2, 0xb5, 1);
}
void sk_swift_range_fatal_4c8(void)  /* FUN_002824c8 */
{
    sk_fatal_error(0xb, 2, "Range requires lowerBound <= upperBound", 0x27,
                   2, "Swift.Range", 0x11, 2, 0xb5, 1);
}
void sk_swift_range_fatal_560(void)  /* FUN_00282560 */
{
    sk_fatal_error(0xb, 2, "Range requires lowerBound <= upperBound", 0x27,
                   2, "Swift.Range", 0x11, 2, 0xb5, 1);
}
void sk_swift_range_fatal_5f8(void)  /* FUN_002825f8 */
{
    sk_fatal_error(0xb, 2, "Range requires lowerBound <= upperBound", 0x27,
                   2, "Swift.Range", 0x11, 2, 0xb5, 1);
}

/*--------------------------------------------------------------------*/
/* FUN_00282650 @ 0x00282650   (est. sk_swift_array_map)
 * Ghidra: long FUN_00282650(undefined8 param_1,undefined4 *param_2,long param_3,
 *        undefined8 param_4, ... )
 * Swift Array map/reduce helper: iterates the source range [0,param_3),
 * applying FUN_00263360 (element transform) / FUN_00264068 to each element and
 * storing the int result into the output array param_2. Stops early when a
 * transform returns the sentinel tag 0x1000000000000. Finalizes with
 * FUN_00117cc4.
 * Confidence: medium (Swift collection transform, sentinel semantics inferred).
 */
long sk_swift_array_map(void *param_1, unsigned int *out, long count,
                        unsigned long p4, unsigned long p5, unsigned long p6,
                        unsigned long p7)
{
    (void)p4; (void)p5; (void)p6; (void)p7;
    long n = 0;
    if (out != 0) {
        /* FUN_0026bd30(0, count) returns iteration range {lo, hi} */
        long lo = 0, hi = count, i;
        for (i = lo; i < hi; i++) {
            if (hi <= i) {
                sk_fatal_error(0xb, 2, "Index out of range", 0x12, 2,
                               "Swift.Range", 0x11, 2, 0x136, 1);
            }
            unsigned long v = sk_swift_elem_transform(1, &p4);   /* FUN_00263360 */
            if ((v & 0xff000000000000) == 0x1000000000000 &&
                (v = sk_swift_elem_transform2(), (v & 0xff000000000000) == 0x1000000000000))
                break;
            *out++ = (unsigned int)v;
            n = i;
        }
    }
    /* FUN_00117cc4 — collection finalize/epilogue helper */
    sk_swift_elem_transform2();
    return n;
}

/*--------------------------------------------------------------------*/
/* FUN_002835c4 @ 0x002835c4   (est. sk_swift_string_unicode_scan)
 * Ghidra: long FUN_002835c4(ulong *param_1, long param_2, long param_3,
 *        ulong param_4..param_7)
 * Swift String scanning: iterates a string, decoding one UTF-8/UTF-16 scalar
 * per step into the output uint buffer. Uses the embedded-Unicode fast path
 * (LZCOUNT-based UTF-8 decode with surrogate/continuation handling) and
 * FUN_002a9ba8 (opaque buffer deref). Fatal errors: Range lowerBound
 * (0xb5), Index out of range (0x136), String index out of bounds (0x1f/0x79),
 * UnicodeHelpers trap (0xfd).
 * Confidence: high (Swift String index/character iteration, string-matched).
 */
long sk_swift_string_unicode_scan(unsigned long *out, long dest, long count,
                                  unsigned long s, unsigned long s2,
                                  unsigned long p6, unsigned long p7)
{
    unsigned long u = s;
    long n;
    if (dest == 0) { n = 0; }
    else {
        if (count < 0) { sk_fatal_error(0xb,2,"Range requires lowerBound <= upperBound",0x27,2,"Swift.Range",0x11,2,0xb5,1); }
        n = count;
        if (count != 0) {
            long i = 0;
            unsigned long base = (p7 & 0xfffffffffffffff) + 0x20;
            unsigned long bound = p6 & 0xffffffffffff;
            if ((p7 & 0x2000000000000000) != 0) bound = p7 >> 0x38 & 0xf;
            do {
                if (count == i) { sk_fatal_error(0xb,2,"Index out of range",0x12,2,"Swift.Range",0x11,2,0x136,1); }
                n = i;
                if ((u ^ s2) < 0x4000) break;               /* end of string */
                unsigned long off = sk_swift_index_char(u, s, s2, p6, p7); /* FUN_002ab4d4 */
                if ((p7 >> 0x3c & 1) != 0) { sk_fatal_error(0xb,2,0xd000000000000034,0x80000000005ce6d0,"Swift.UnicodeHelpers",0x1a,2,0xfd,1); }
                /* decode scalar at offset off (UTF-8 or embedded UTF-16) */
                unsigned int scalar;
                long adv;
                if ((p7 >> 0x3d & 1) != 0) {
                    /* embedded UTF-16 via local_70 stack copy */
                    scalar = *(unsigned char *)((char *)&p6 + (off >> 0x10));
                    adv = 1;
                } else {
                    long p = base;
                    if ((p6 >> 0x3c & 1) == 0) p = sk_swift_str_buf(p6, p7); /* FUN_002a9ba8 */
                    scalar = *(unsigned char *)(p + (off >> 0x10));
                    /* UTF-8 continuation decode via LZCOUNT */
                    adv = sk_swift_utf8_len(scalar);        /* 1..4 */
                }
                /* store scalar, advance index */
                *(unsigned int *)(dest + i*4) = scalar;
                i += 1;
                /* u = (off + adv)<<16 | 5 */
                n = count;
            } while (count != i);
        }
    }
    out[0] = s; out[1] = s2; out[2] = p6; out[3] = p7; out[4] = u;
    return n;
}

/*--------------------------------------------------------------------*/
/* FUN_00283a08 @ 0x00283a08   (est. sk_swift_array_init_single)
 * Ghidra: undefined8 FUN_00283a08(undefined8 *param_1, undefined8 *param_2,
 *        long param_3, undefined8 param_4)
 * Swift Array init with a single element: writes param_4 into the buffer if
 * count>0; returns {elem, count}. Negative count raises Range fatal.
 * Confidence: high.
 */
void *sk_swift_array_init_single(void *out, void *dest, long count, unsigned long elem)
{
    unsigned long n, c;
    if (dest == 0) { n = 0; c = 0; }
    else {
        if (count < 0) { sk_fatal_error(0xb,2,0,0,0,0,0); __builtin_trap(); }
        if (count == 0) { n = 0; c = 0; }
        else { *(unsigned long *)dest = elem; n = 1; c = 1; }
    }
    ((unsigned long *)out)[0] = elem;
    ((unsigned long *)out)[1] = n;
    return (void *)c;
}

/*--------------------------------------------------------------------*/
/* FUN_00283a60 @ 0x00283a60   (est. sk_swift_unsafe_raw_copy)
 * Ghidra: long FUN_00283a60(undefined8 *param_1, long param_2, long param_3,
 *        undefined1 *param_4, undefined1 *param_5)
 * Swift UnsafeRawBufferPointer copy: copies bytes from [param_4,param_5) into
 * dest param_2, validating bounds (fatal 0x4f9/0x4fc) and count range.
 * Returns count copied.
 * Confidence: high (UnsafeRawBufferPointer, string-matched).
 */
long sk_swift_unsafe_raw_copy(void *out, long dest, long count,
                              unsigned char *src, unsigned char *src_end)
{
    long n;
    if (dest == 0) { n = 0; }
    else {
        if (count < 0) { sk_fatal_error(0xb,2,"Range requires lowerBound <= upperBound",0x27,2,"Swift.Range",0x11,2,0xb5,1); }
        n = count;
        if (count != 0) {
            long i = 0;
            unsigned char *p = src;
            do {
                if (count == i) { sk_fatal_error(0xb,2,"Index out of range",0x12,2,"Swift.Range",0x11,2,0x136,1); }
                src = p; n = i;
                if (p == 0) break;
                if (src_end == 0) { sk_fatal_error(0xb,2,sk_swift_unknown_5be7c0,0,2,"Swift.UnsafeRawBufferPointer",0x22,2,0x4f9,1); }
                src = src_end;
                if (p == src_end) break;
                if (src_end <= p) { sk_fatal_error(0xb,2,sk_swift_unknown_5be7c0,0,2,"Swift.UnsafeRawBufferPointer",0x22,2,0x4fc,1); }
                src = p + 1;
                *(unsigned char *)(dest + i) = *p;
                i += 1;
                p = src;
                n = count;
            } while (count != i);
        }
    }
    ((unsigned long *)out)[0] = (unsigned long)src;
    ((unsigned long *)out)[1] = (unsigned long)src_end;
    return n;
}

/*--------------------------------------------------------------------*/
/* FUN_00283be4 @ 0x00283be4   (est. sk_swift_array_map_16)
 * Ghidra: long FUN_00283be4(ulong *param_1, undefined1 (*param_2)[16],
 *        long param_3, ulong param_4, ulong param_5)
 * Swift Array map over 16-byte elements: iterates [0,count), applies
 * FUN_0029fb80 to produce a 16-byte result; stops when the high half is 0.
 * Confidence: high (Array map, string-matched Index out of range).
 */
long sk_swift_array_map_16(unsigned long *out, void *dest, long count,
                           unsigned long p4, unsigned long p5)
{
    unsigned long bound = p4 & 0xffffffffffff;
    if ((p5 & 0x2000000000000000) != 0) bound = p5 >> 0x38 & 0xf;
    long n;
    if (dest == 0) { n = 0; }
    else {
        /* FUN_0026bd30(0,count) -> range */
        long i;
        for (i = 0; i < count; i++) {
            if (count <= i) { sk_fatal_error(0xb,2,"Index out of range",0x12,2,"Swift.Range",0x11,2,0x136,1); }
            void *r = (void *)sk_swift_elem_map();   /* FUN_0029fb80 -> {lo,hi} */
            n = i;
            if (((unsigned long *)r)[1] == 0) break;
            *(void **)dest = r;
            dest = (char *)dest + 16;
        }
    }
    out[0] = p4; out[1] = p5; out[3] = bound; out[2] = 0;
    return n;
}

/*--------------------------------------------------------------------*/
/* FUN_00283d14 @ 0x00283d14   (est. sk_swift_array_map_16bit)
 * Ghidra: long FUN_00283d14(ulong *param_1, undefined2 *param_2, long param_3,
 *        ulong param_4, ulong param_5)
 * Swift Array map over 16-bit elements; applies FUN_002b0c84, stops when the
 * element carries the sentinel 0x10000 tag.
 * Confidence: high (Array map, string-matched).
 */
long sk_swift_array_map_16bit(unsigned long *out, void *dest, long count,
                              unsigned long p4, unsigned long p5)
{
    unsigned long bound = p4 & 0xffffffffffff;
    if ((p5 & 0x2000000000000000) != 0) bound = p5 >> 0x38 & 0xf;
    long n;
    if (dest == 0) { n = 0; }
    else {
        /* FUN_0026bd30(0,count) */
        long i;
        for (i = 0; i < count; i++) {
            if (count <= i) { sk_fatal_error(0xb,2,"Index out of range",0x12,2,"Swift.Range",0x11,2,0x136,1); }
            unsigned int v = sk_swift_elem_map_16();  /* FUN_002b0c84 */
            n = i;
            if ((v & 0xff0000) == 0x10000) break;
            *(unsigned short *)dest = (unsigned short)v;
            dest = (char *)dest + 2;
        }
    }
    out[0] = p4; out[1] = p5; out[3] = bound; out[2] = 0;
    ((unsigned short *)(out + 4))[0] = 0;
    *(unsigned char *)((char *)out + 0x22) = 1;
    return n;
}

/*--------------------------------------------------------------------*/
/* FUN_00283e7c @ 0x00283e7c   (est. sk_swift_string_unicode_map)
 * Ghidra: long FUN_00283e7c(ulong *param_1, long param_2, long param_3,
 *        ulong param_4, ulong param_5)
 * Swift String unicode scalar map: iterates the string, decoding each scalar
 * (UTF-8 or embedded UTF-16) into the output uint buffer, with index bounds
 * (uVar1) enforced. Fatal errors: Range 0xb5, Index out of range 0x136,
 * UnicodeHelpers 0xfd.
 * Confidence: high (Swift String unicodeScalars map, string-matched).
 */
long sk_swift_string_unicode_map(unsigned long *out, long dest, long count,
                                 unsigned long p4, unsigned long p5)
{
    unsigned long bound = p4 & 0xffffffffffff;
    if ((p5 & 0x2000000000000000) != 0) bound = p5 >> 0x38 & 0xf;
    unsigned long pos = 0;
    long n;
    if (dest == 0) { pos = 0; n = 0; }
    else {
        if (count < 0) { sk_fatal_error(0xb,2,"Range requires lowerBound <= upperBound",0x27,2,"Swift.Range",0x11,2,0xb5,1); }
        if (count == 0) { pos = 0; n = count; }
        else {
            long i = 0; pos = 0;
            do {
                if (count == i) { sk_fatal_error(0xb,2,"Index out of range",0x12,2,"Swift.Range",0x11,2,0x136,1); }
                n = i;
                if ((long)bound <= (long)pos) break;
                if ((p5 >> 0x3c & 1) != 0) { sk_fatal_error(0xb,2,0xd000000000000034,0x80000000005ce6d0,"Swift.UnicodeHelpers",0x1a,2,0xfd,1); }
                unsigned int scalar; long adv;
                if ((p5 >> 0x3d & 1) == 0) {
                    /* UTF-8 decode from buffer */
                    long p = (p5 & 0xfffffffffffffff) + 0x20;
                    if ((p4 >> 0x3c & 1) == 0) p = sk_swift_str_buf(p4, p5);
                    scalar = *(unsigned char *)(p + pos);
                    adv = sk_swift_utf8_decode(&scalar);   /* via LZCOUNT */
                } else {
                    /* embedded UTF-16 */
                    scalar = *(unsigned char *)((char *)&p4 + pos);
                    adv = 1;
                }
                *(unsigned int *)(dest + i*4) = scalar;
                i += 1;
                pos += adv;
                n = count;
            } while (count != i);
        }
    }
    out[0] = p4; out[1] = p5; out[2] = pos; out[3] = bound;
    return n;
}

/*--------------------------------------------------------------------*/
/* FUN_00284148 @ 0x00284148   (est. sk_swift_uint_setbit_map)
 * Ghidra: long FUN_00284148(long *param_1, undefined8 *param_2, long param_3,
 *        long param_4)
 * Swift Set/bitmap map: iterates a packed bitmap (base param_4+0x30, first
 * word mask from param_4+0x20), extracting set-bit indices via the bit
 * reversal LZCOUNT pattern; writes each {index<<... , high} pair into the
 * output array. Overflow of index counter hits breakpoint 0x2842e4.
 * Confidence: high (Swift Set iterator / bitmap pop, string-matched).
 */
long sk_swift_uint_setbit_map(long *out, void **dest, long count, long set)
{
    unsigned long *words = (unsigned long *)(set + 0x38);
    unsigned long mask = -1L << (*(unsigned char *)(set + 0x20) & 0x3f);
    unsigned long word = 0xffffffffffffffff;
    if (-mask < 0x40) word = ~(-1L << (-mask & 0x3f));
    word = word & *words;
    long i, wi = 0, n = 0;
    if (dest == 0) { n = 0; }
    else {
        /* FUN_0026bd30(0,count) -> {lo,hi} */
        long lo = 0, hi = count;
        while (lo != hi) {
            if (hi <= lo) { sk_fatal_error(0xb,2,"Index out of range",0x12,2,"Swift.Range",0x11,2,0x136,1); }
            while (word == 0) {
                long next = wi + 1;
                if (__builtin_add_overflow(wi, 1, &wi)) { __builtin_trap(); } /* breakpoint 0x2842e4 */
                if ((long)(0x3f - mask >> 6) <= next) { word = 0; goto done; }
                wi = next;
                word = words[wi];
            }
            lo += 1;
            unsigned long rev = __builtin_bitreverse64(word);
            void **entry = (void **)(*(long *)(set + 0x30) + (long)__builtin_clzll(rev | (rev<<0) ) * 0x10 + wi * 0x400);
            void *hi2 = entry[1];
            word &= word - 1;
            dest[0] = entry[0];
            dest[1] = hi2;
            if (lo == hi) break;
            sk_alloc_pages(0, 0);  /* thunk_FUN_0036b270 */
            dest += 2;
        }
        sk_alloc_pages(0, 0);
        n = count;
    }
done:
    out[0] = set; out[1] = (long)words; out[2] = ~mask; out[3] = wi; out[4] = word;
    return n;
}

/*--------------------------------------------------------------------*/
/* FUN_002842e4 @ 0x002842e4   (est. sk_swift_array_element_prefix)
 * Ghidra: ulong FUN_002842e4(long *param_1, undefined8 *param_2, ulong param_3,
 *        long param_4)
 * Swift Array prefix/map: copies 2-word elements from buffer param_4+0x28,
 * bounded by param_4+0x10 (count) and param_3. Fatal: Range 0xb5, Index out
 * of range (ContiguousArrayBuffer 0x2b4).
 * Confidence: high (ContiguousArrayBuffer, string-matched).
 */
unsigned long sk_swift_array_element_prefix(long *out, void **dest, unsigned long count, long arr)
{
    unsigned long n;
    if (dest == 0) { n = 0; }
    else {
        if ((long)count < 0) { sk_fatal_error(0xb,2,"Range requires lowerBound <= upperBound",0x27,2,"Swift.Range",0x11,2,0xb5,1); }
        n = count;
        if (count != 0) {
            unsigned long *src = (unsigned long *)(arr + 0x28);
            unsigned long i;
            for (i = 0; i != *(unsigned long *)(arr + 0x10); i++) {
                if (*(unsigned long *)(arr + 0x10) <= i) {
                    sk_fatal_error(0xb,2,"Index out of range",0x12,2,"Swift.ContiguousArrayBuffer",0x21,2,0x2b4,1);
                }
                dest[0] = (void *)src[-1];
                dest[1] = (void *)*src;
                if (count - 1 == i) { sk_alloc_pages(0,0); n = count; break; }
                sk_alloc_pages(0,0);
                src += 2; dest += 2;
            }
        }
    }
    out[0] = arr; out[1] = n;
    return n;
}

/*--------------------------------------------------------------------*/
/* FUN_00284424 @ 0x00284424   (est. sk_swift_collection_map_typed)
 * Ghidra: long FUN_00284424(undefined8 param_1, long param_2, long param_3, ...)
 * Swift typed-collection map: acquires three object contexts (locks),
 * resolves method tables (local_70+0x20 iterate, local_88+8 finalize,
 * local_68+0x20 epilogue), iterates source range [0,param_3), applying the
 * map function and advancing dest by the element stride (local_70+0x48).
 * Confidence: low (typed-collection map with method-table dispatch).
 */
long sk_swift_collection_map_typed(void *param_1, void *dest, long count,
                                   unsigned long p4, unsigned long p5)
{
    unsigned long ctx1 = sk_object_lock(0xff, p5, p4, sk_obj_methods_0, sk_obj_methods_1); /* FUN_00377824 */
    void *type1 = *(void **)(ctx1 - 8);
    unsigned long ctx2 = sk_object_lock(0, p5, p4, sk_obj_methods_0, (void *)0x611b3c);
    void *type2 = *(void **)(ctx2 - 8);
    unsigned long ctx3 = sk_object_lock(0, p5, p4, sk_obj_methods_0, (void *)0x611b2c); /* FUN_00377bec */
    void *type3 = *(void **)(ctx3 - 8);
    long n;
    if (dest == 0) { n = 0; count = 0; }
    else {
        long lo = 0, hi = count, i = lo;
        do {
            if (hi <= i) { sk_fatal_error(0xb,2,"Index out of range",0x12,2,"Swift.Range",0x11,2,0x136,1); }
            /* FUN_00377bec + FUN_000a68f4 dispatch; FUN_000839f8 completion */
            int done = sk_queue_complete(0, 1, (void *)ctx1);
            if (done == 1) { (*(void(**)(void*,void*))(type1+8))(0, (void *)ctx1); n = i; break; }
            i += 1;
            void (*iter)(void*,void*,void*) = *(void(**)(void*,void*,void*))(type2 + 0x20);
            iter(dest, 0, (void *)ctx1);
            dest = (char*)dest + *(long *)((char*)type2 + 0x48);
        } while (hi != i);
    }
    (*(void(**)(void*,void*,void*))(type3 + 0x20))(param_1, 0, (void *)ctx3);
    return n;
}

/*--------------------------------------------------------------------*/
/* FUN_002847c4 @ 0x002847c4   (est. sk_object_dispatch_global)
 * Ghidra: void FUN_002847c4(undefined8 param_1, undefined8 param_2,
 *        code *UNRECOVERED_JUMPTABLE)
 * Resolves a global dispatch target (FUN_00351cc4), runs helper, then jumps
 * through an unrecoverable indirect jumptable.
 * Confidence: low.
 */
void sk_object_dispatch_global(void *param_1, void *param_2, void *target)
{
    (void)param_1; (void)param_2;
    long ctx = sk_spin_irqsave(0);   /* FUN_00351cc4 */
    sk_alloc_pages(*(unsigned long *)((char *)ctx + 0x18), 0);  /* FUN_000a68f4 */
    /* FUN_0035a2dc; (*target)() unrecoverable jumptable */
}

/*--------------------------------------------------------------------*/
/* FUN_00284808 / FUN_00284b9c   (est. sk_object_service_loop_a/b)
 * Ghidra: void FUN_00284808(void) / FUN_00284b9c(void)
 * Two near-identical object-service loops: acquire object lock, run a long
 * chain of dispatch helpers (FUN_00359634 lock-capture, FUN_0034e81c,
 * FUN_00377824, ...), then loop pulling notifications (FUN_00377bec +
 * FUN_000a68f4) and dispatching through the per-object notify handler until
 * the completion predicate FUN_000839d8/0x839f8 fires. Epilogue FUN_00353d14.
 * Confidence: low (object notification service loop).
 */
void sk_object_service_loop_a(void)
{
    /* FUN_00353cfc; FUN_00359634; FUN_0034e81c; FUN_00377824; FUN_00352efc;
     * FUN_00310d68; FUN_000a6f88; (*DAT_00658c00)(x8+0x40); FUN_00348a34;
     * (*DAT_00658c00)(); FUN_0034c2b4; FUN_00349b00; FUN_00348a18;
     * FUN_00350464; FUN_00349c70; FUN_003491ec; FUN_00350318; FUN_00377824;
     * FUN_00348ce8; FUN_0007c1a4; (*DAT_00658c00)(); FUN_0034b0c4;
     * FUN_00356024; FUN_000a68c4; FUN_00350c50; FUN_00351274; FUN_0034b278;
     * FUN_0034edd8; FUN_00377bec; FUN_000a68f4; FUN_0034efa8; FUN_0035a670;
     * FUN_00350c14; FUN_00353c84; FUN_00350884; then loop:
     *   FUN_0035a40c; FUN_00352560; FUN_00350884; FUN_003579a4; FUN_00359614;
     *   if x19: FUN_00350ea4; (*pcVar4)(); ... goto epilogue
     *   else if (v&1): FUN_00350bf0; FUN_00353050; (*pcVar5)()
     * end: FUN_00350af4; FUN_00356924; FUN_00352c68; FUN_000839d8;
     * epilogue FUN_00351348 + FUN_00353d14 */
    (*(void (**)(void))(0x658c00))();
    sk_alloc_pages(0, 0);
    sk_queue_complete(0, 0, 1, 0);  /* FUN_000839d8 */
}
void sk_object_service_loop_b(void)  /* FUN_00284b9c — identical */
{
    sk_object_service_loop_a();
}

/*--------------------------------------------------------------------*/
/* FUN_00284f5c @ 0x00284f5c   (est. sk_object_service_loop_c)
 * Ghidra: void FUN_00284f5c(void)
 * Wrapper: runs helpers then calls FUN_00284b9c (service loop b), then
 * FUN_00358344 epilogue.
 * Confidence: low.
 */
void sk_object_service_loop_c(void)
{
    /* FUN_00358374 / FUN_0034b668 / FUN_003497a0 / FUN_00377824 /
     * FUN_00351f58 / FUN_00352ae4 */
    sk_object_service_loop_b();  /* FUN_00284b9c */
    /* FUN_00358344 */
}

/*--------------------------------------------------------------------*/
/* FUN_00284ff4 @ 0x00284ff4   (est. sk_swift_string_character_equal)
 * Ghidra: bool FUN_00284ff4(ulong param_1..param_4)
 * Swift String equality comparison: walks two string indices (packed
 * {offset<<16 | flags}), comparing the scalar at each, handling surrogate
 * pairs / UTF-16 edges (FUN_002c7020, 0xa0d line separator). Fatal errors:
 * String index out of bounds (0x62), unsafelyUnwrapped nil optional (0x179).
 * Returns true if equal. FUN_003a25d4 releases temporary strings.
 * Confidence: high (Swift String ==, string-matched).
 */
bool sk_swift_string_character_equal(unsigned long s1, unsigned long i1,
                                     unsigned long s2, unsigned long i2)
{
    /* index packing: bit57=1 => user, bit60 set if untagged; offset bits */
    unsigned long bound1 = i1 >> 0x38 & 0xf;
    unsigned int sc1 = (unsigned int)(s1 >> 0x3b) & 1;
    if ((i1 & 0x1000000000000000) == 0) sc1 = 1;
    unsigned long f1 = (sc1 == 0) ? 0xb : 7;
    unsigned long idx1 = f1 | bound1 << 0x10;
    unsigned long bound2 = i2 >> 0x38 & 0xf;
    unsigned int sc2 = (unsigned int)(s2 >> 0x3b) & 1;
    if ((i2 & 0x1000000000000000) == 0) sc2 = 1;
    unsigned long f2 = (sc2 == 0) ? 0xb : 7;
    unsigned long idx2 = f2 | bound2 << 0x10;
    for (;;) {
        unsigned long b2 = idx2 >> 0xe;
        if (b2 == 0) {
            if (idx1 < 0x4000) return true;
            idx2 = sk_swift_string_index(s1, i1, 0x188, 0x141, 0);  /* FUN_002aaf80 */
            if (idx2 < 0x4000) { sk_fatal_error(0xb,2,"String index is out of bounds",0x1d,2,"Swift.StringCharacterView",0x1f,2,0x62,1); }
            /* FUN_0029ef1c + FUN_00267510 -> end of string */
            return b2 != 0;
        }
        idx2 = sk_swift_string_index(b2, s2, i2, 0x188, 0x141); /* FUN_002aaf80 */
        if (idx2 < 0x4000) { sk_fatal_error(0xb,2,"String index is out of bounds",0x1d,2,"Swift.StringCharacterView",0x1f,2,0x62,1); }
        unsigned long off2 = idx2 >> 0x10;
        if (idx2 >> 0x11 != 0) {
            unsigned short u;
            if ((i2 >> 0x3c & 1) == 0) {
                if ((i2 >> 0x3d & 1) == 0) {
                    long p = (i2 & 0xfffffffffffffff) + 0x20;
                    if ((s2 >> 0x3c & 1) == 0) { p = sk_swift_str_buf(s2, i2); }
                    if (p == 0) { sk_fatal_error(0xb,2,"unsafelyUnwrapped of nil optional",0x21,2,"Swift.Optional",0x14,2,0x179,1); }
                    u = *(unsigned short *)(p + off2 - 2);
                } else {
                    /* embedded UTF-16 */
                    u = *(unsigned short *)((char *)&idx2 + off2 + 6);
                }
                if (u != 0xa0d && (u & 0x8080) == 0) { off2 = 1; goto adv2; }
            }
            off2 = sk_swift_string_char_width(off2, s2, i2);  /* FUN_002c7020 */
        }
adv2:
        idx2 = (idx2 + off2 * -0x10000) & 0xffffffffffff0000 | (off2 << 8) | f2;
        /* FUN_00267510 decode */
        /* similar advance of idx1 (string 1) */
        unsigned long b1 = idx1 >> 0xe;
        if (b1 == 0) { /* end */ }
        idx1 = sk_swift_string_index(idx1, s1, i1, 0x188, 0x141);
        if (idx1 >> 0xe == 0) { sk_fatal_error(0xb,2,"String index is out of bounds",0x1d,2,"Swift.StringCharacterView",0x1f,2,0x62,1); }
        unsigned long off1 = idx1 >> 0x10;
        if (idx1 >> 0x11 != 0) {
            unsigned short u;
            if ((i1 >> 0x3c & 1) == 0) {
                if ((i1 >> 0x3d & 1) == 0) {
                    long p = (i1 & 0xfffffffffffffff) + 0x20;
                    if ((s1 >> 0x3c & 1) == 0) { p = sk_swift_str_buf(s1, i1); }
                    if (p == 0) { sk_fatal_error(0xb,2,"unsafelyUnwrapped of nil optional",0x21,2,"Swift.Optional",0x14,2,0x179,1); }
                    u = *(unsigned short *)(p + off1 - 2);
                } else { u = *(unsigned short *)((char *)&idx1 + off1 + 6); }
                if (u != 0xa0d && (u & 0x8080) == 0) { off1 = 1; goto adv1; }
            }
            off1 = sk_swift_string_char_width(off1, s1, i1);
        }
adv1:
        idx1 = (idx1 + off1 * -0x10000) & 0xffffffffffff0000 | (off1 << 8) | f1;
        int eq = sk_swift_string_index_cmp(0, 0, 0, 0);   /* FUN_00285e50 */
        sk_swift_release(0);   /* FUN_003a25d4 */
        if (0 != 0) { return b2 != 0; }
        sk_swift_release(0);
        if ((eq & 1) == 0) return false;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_00285984 @ 0x00285984   (est. sk_swift_string_has_prefix)
 * Ghidra: undefined8 FUN_00285984(undefined8 param_1, ulong param_2..param_4, ...)
 * Swift String hasPrefix: walks both strings, comparing character-by-character
 * via FUN_002b439c (next scalar) and FUN_002a0d50 (compare), short-circuiting
 * when the prefix is exhausted. FUN_003a25d4 releases temp strings.
 * Confidence: high (Swift hasPrefix, string-matched bounds).
 */
int sk_swift_string_has_prefix(void *param_1, unsigned long p2, unsigned long p3,
                               unsigned long p4, void *p5, void *p6)
{
    (void)param_1;
    sk_alloc_pages(p2, 0);  /* thunk_FUN_0036b270 */
    unsigned long i = p3;
    unsigned long c = 0, hi = 0;
    for (;;) {
        for (;;) {
            if ((i ^ p4) < 0x4000) {   /* end of string 2 */
                sk_swift_elem_map();
                sk_swift_release(p2);
                if (0 == 0) return 1;
                return 0;
            }
            /* FUN_002b439c next char; FUN_002ab6a0; FUN_002b3b84 */
            c = sk_swift_next_char(i, p3, p4, p5, p6);
            i = sk_swift_advance(c, p3, p4, p5, p6);
            void *r = (void *)sk_swift_elem_map();  /* FUN_0029fb80 */
            hi = ((unsigned long *)r)[1];
            if (hi == 0) { sk_swift_release(p2); return 1; }
            if (/* chars equal */ 0) break;
            /* mismatch: FUN_003a25d4 releases, return 0 */
            sk_swift_release(p2);
            return 0;
        }
        /* character mismatch check */
        if (((c ^ hi ^ -1UL) & 0x6000000000000000) == 0) break;
        int same = sk_swift_string_cmp(0, c, 0, hi, 0);  /* FUN_002a0d50 */
        sk_swift_release(c);
        sk_swift_release(hi);
        if ((same & 1) == 0) return 0;
    }
    sk_swift_release(c);
    sk_swift_release(hi);
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_00285b30 @ 0x00285b30   (est. sk_swift_string_contains_sub)
 * Ghidra: undefined8 FUN_00285b30(ulong param_1..param_4, ...)
 * Swift String contains(substring): searches for substring by advancing the
 * haystack index until it can no longer fit the needle, comparing character
 * runs. Fatal: String index out of bounds (0x62), Substring index out of
 * bounds (0x10b).
 * Confidence: high (String contains, string-matched).
 */
int sk_swift_string_contains_sub(unsigned long s1, unsigned long i1,
                                 unsigned long s2, unsigned long i2,
                                 void *p5, void *p6)
{
    unsigned long b1 = s1;
    if ((i1 & 0x2000000000000000) != 0) b1 = i1 >> 0x38 & 0xf;
    unsigned int sc = (unsigned int)(s1 >> 0x3b) & 1;
    if ((i1 & 0x1000000000000000) == 0) sc = 1;
    unsigned long f1 = (sc == 0) ? 0xb : 7;
    unsigned long idx1 = f1 | b1 << 0x10;
    unsigned long i = i2;
    for (;;) {
        if (s2 >> 0xe == i >> 0xe) {   /* needle exhausted */
            if (idx1 < 0x4000) return 1;
            i = sk_swift_string_index(idx1, s1, i1, 0x188, 0x141);
            if (i >> 0xe == 0) { sk_fatal_error(0xb,2,"String index is out of bounds",0x1d,2,"Swift.StringCharacterView",0x1f,2,0x62,1); }
            /* end of haystack */
            sk_swift_release(0);
            return 0;
        }
        i = sk_swift_string_next(i, s2, i2, p5, p6);   /* FUN_002ab058 */
        if (i >> 0xe <= s2 >> 0xe) { sk_fatal_error(0xb,2,"Substring index is out of bounds",0x20,2,"Swift.Substring",0x15,2,0x10b,1); }
        i = sk_swift_advance2(i, s2, i2, p5, p6);       /* FUN_002b3d68 */
        void *c = (void *)sk_swift_next_char2(i, s2, i2, p5, p6); /* FUN_002b439c */
        unsigned long c2 = ((unsigned long *)c)[1];
        if (idx1 < 0x4000) { sk_swift_release(c2); return 1; }
        idx1 = sk_swift_string_index(idx1, s1, i1, 0x188, 0x141);
        if (idx1 >> 0xe == 0) { sk_fatal_error(0xb,2,"String index is out of bounds",0x1d,2,"Swift.StringCharacterView",0x1f,2,0x62,1); }
        idx1 = sk_swift_string_char(idx1, s1, i1);     /* FUN_0029ef1c */
        void *d = (void *)sk_swift_str_buf(idx1, s1, i1); /* FUN_00267510 */
        unsigned long d2 = ((unsigned long *)d)[1];
        if ((unsigned long)c == (unsigned long)d) {
            sk_swift_release(c2);
            sk_swift_release(d2);
        } else {
            if (((c2 ^ -1UL) & 0x6000000000000000) == 0 &&
                (d2 & 0x6000000000000000) == 0x6000000000000000) {
                sk_swift_release(c2, d2, ((unsigned long *)d)[0]);
                sk_swift_release(d2);
                return 0;
            }
            int same = sk_swift_string_cmp(0, c2, 0, d2, 0);
            sk_swift_release(c2);
            sk_swift_release(d2);
            if ((same & 1) == 0) return 0;
        }
    }
}

/*--------------------------------------------------------------------*/
/* FUN_00285e24 @ 0x00285e24   (est. sk_swift_string_index_forward)
 * Ghidra: void FUN_00285e24(void)
 * Forwarder to FUN_00286b20.
 * Confidence: medium.
 */
void sk_swift_string_index_forward(void)
{
    sk_swift_string_index_next();  /* FUN_00286b20 */
}

/*--------------------------------------------------------------------*/
/* FUN_00285e50 @ 0x00285e50   (est. sk_swift_string_index_cmp)
 * Ghidra: uint FUN_00285e50(long param_1, ulong param_2, long param_3, ulong param_4)
 * Swift string-index comparison: equal if both strings identical; else uses
 * the fast path if param_2 is non-embedded and param_4 embedded; otherwise
 * FUN_002a0d50 (character compare). Returns boolean.
 * Confidence: high (Swift String index ==).
 */
unsigned int sk_swift_string_index_cmp(long a, unsigned long b, long c, unsigned long d)
{
    if (a == c && b == d) return 1;
    if (((b ^ -1UL) & 0x6000000000000000) == 0 &&
        (d & 0x6000000000000000) == 0x6000000000000000) return 0;
    return sk_swift_string_cmp(0, b, 0, d, 0) & 1;   /* FUN_002a0d50 */
}

/*--------------------------------------------------------------------*/
/* FUN_00285eb4 @ 0x00285eb4   (est. sk_object_service_x)
 * Ghidra: void FUN_00285eb4(void)
 * Object service with multiple lock/dispatch phases and a long helper chain;
 * ends with a double lock release (FUN_00353034) and FUN_00353d14 epilogue.
 * Confidence: low (indirect service dispatcher).
 */
void sk_object_service_x(void)
{
    /* FUN_00353cfc / FUN_0034f860 / FUN_00377824 / FUN_00348e18 /
     * FUN_0007c1a4 / (*DAT_00658c00)() / FUN_003501d0 / FUN_00350220 /
     * FUN_00377824 / FUN_000a6f88 / FUN_0034d89c / FUN_00310d68(0xff) /
     * FUN_00310d68(0xff) / FUN_0034c60c / FUN_003515b4 / FUN_003722e4 /
     * FUN_0034ab20 / FUN_0034b2f8 / FUN_0034e3ac / FUN_0034f3d4 /
     * FUN_00358208 / FUN_0034cd54 / FUN_0034a5c8 / FUN_003493ac /
     * FUN_00350720 / FUN_00377824 / FUN_000a6f88 / FUN_0034af20 /
     * FUN_003499c8 / FUN_00349068 / FUN_00350624 / FUN_00377824 /
     * FUN_00348d7c / FUN_0034b460 / FUN_00358e00 / FUN_00352680 /
     * FUN_0035072c / FUN_00352680 / FUN_00358d4c / FUN_0035084c /
     * FUN_0034b278 / FUN_003514e8 / FUN_00377bec / FUN_000a68f4 /
     * FUN_00350b78 / FUN_00377bec / FUN_000a68f4 / FUN_00353718
     * loop: (*pcVar6)(...); FUN_00356970; (*pcVar8)(...); lVar11 = *(lVar3+0x30);
     *   FUN_00350470; FUN_0035172c; FUN_00350884; FUN_00355eec; FUN_00351414;
     *   FUN_0034d688; FUN_00351414; FUN_00354b14; FUN_00350b00
     *   ... until (uVar9 & 1) == 0
     * epilogue: FUN_00353034; FUN_00353d14 */
    (*(void (**)(void))(0x658c00))();
    sk_object_lock(0, 0, 0, 0, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_002864f8 @ 0x002864f8   (est. sk_object_service_y)
 * Ghidra: void FUN_002864f8(undefined8 param_1, undefined8 param_2, uint param_3, ...)
 * Object service with a notification loop: pull notifications (FUN_00377bec +
 * FUN_000a68f4), dispatch through the object's notify handler, and on
 * completion set the result flag (param_3) before the FUN_00353d14 epilogue.
 * Confidence: low.
 */
void sk_object_service_y(void *param_1, void *param_2, unsigned int result,
                         void *p4, void *p5, void *p6, void *p7)
{
    (void)param_1; (void)param_2; (void)p4; (void)p5;
    /* FUN_00353cfc; FUN_0034e81c; FUN_00377824; FUN_0034da88; FUN_00310d68;
     * FUN_000a6f88; (*DAT_00658c00)(x8+0x40); FUN_0034926c; (*DAT_00658c00)();
     * FUN_00350434; FUN_003503f8; FUN_00350464; FUN_0034911c; FUN_003493c4;
     * FUN_0034d234; FUN_00354028; FUN_00349b00; FUN_003497b4; FUN_003508e4;
     * FUN_00351100; FUN_00377824; FUN_000a6f88; FUN_0034af20; FUN_0034a688;
     * FUN_003491ec; FUN_00350720; FUN_00352998; FUN_00377824; FUN_00348e60;
     * FUN_0034b460; (**(x16_02+0x10))(p5, x20, p4); FUN_00352680(p6);
     * FUN_003508f0; FUN_00357a5c; FUN_00352680; FUN_00350518; FUN_0034b278;
     * FUN_00350b6c; FUN_00377bec; FUN_000a68f4
     * loop: (*pcVar5)(...); FUN_00351390; FUN_00350884;
     *   if ZR: completion branch -> result flag; goto done
     *   else: (*x16_00+0x20); FUN_00351554; FUN_0034b278; FUN_00377bec;
     *     FUN_000a68f4; FUN_0035102c; FUN_00351324; FUN_003518dc; FUN_00350884
     *     ... until (uVar6 & 1) == 0
     * done: result = ...; FUN_00359b64(result & 1); FUN_00353d14 */
    (*(void (**)(void))(0x658c00))();
    sk_object_lock(0, 0, 0, 0, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_00286b20 @ 0x00286b20   (est. sk_swift_string_index_next)
 * Ghidra: void FUN_00286b20(void)
 * String-index advance helper: runs lock/state helpers then dispatches the
 * index-advance callback through unaff_x19, passing the low bit result to
 * FUN_000b45b0.
 * Confidence: low (indirect index advance).
 */
void sk_swift_string_index_next(void)
{
    /* FUN_000b4594 / FUN_00357f84 / FUN_00352068 / FUN_003537fc /
     * FUN_003497a0 / FUN_00351dfc / FUN_00377824 / FUN_003508a8 /
     * FUN_0035a4bc; uVar1 = (*unaff_x19)(); FUN_000b45b0(uVar1&1,...) */
    sk_object_lock(0, 0, 0, 0, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_00286b94 @ 0x00286b94   (est. sk_object_service_forward)
 * Ghidra: void FUN_00286b94(void)
 * Object service forwarder: callback via stack (in_stack_00000050), lock
 * helpers, epilogue FUN_0035a7d4.
 * Confidence: low.
 */
void sk_object_service_forward(void)
{
    /* FUN_0035a7c0 / FUN_0034d6d8; pcVar1 = (*in_stack_00000050)(in_x7);
     * FUN_00349ea0; FUN_00350ed0; FUN_00377824; FUN_000a6e14; (*pcVar1)();
     * FUN_0035396c; FUN_0035a7d4 */
    sk_object_lock(0, 0, 0, 0, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_00286c10 @ 0x00286c10   (est. sk_object_service_pump)
 * Ghidra: void FUN_00286c10(void)
 * Object service pump: acquires lock, runs the dispatch chain, then loops
 * pulling work (FUN_00377bec + FUN_000a68f4) and dispatching until the
 * completion predicate FUN_000839f8 returns 1 or a wake flag trips.
 * Epilogue FUN_00353d14.
 * Confidence: low (service loop with lock + completion predicate).
 */
void sk_object_service_pump(void)
{
    /* FUN_00353cfc / FUN_00355e68 / FUN_0034f860 / FUN_00377824 /
     * FUN_00348d4c / FUN_0007c1a4 / (*DAT_00658c00)() / FUN_0034b05c /
     * FUN_0035050c / FUN_0034d464 / FUN_0034aee4 / FUN_003499f0 /
     * FUN_003490ec / FUN_0034d8d4 / FUN_00377824 / FUN_00348fd8 /
     * FUN_0034d3c4 / FUN_00358aa4 / FUN_00352680 / FUN_00359bec /
     * FUN_00350c80 / FUN_0034b278 / FUN_003508b4 / FUN_00377bec /
     * FUN_000a68f4
     * loop: (*pcVar4)(x28, msg); FUN_00351738;
     *   iVar1 = FUN_000839f8(); if (iVar1==1) break;
     *   FUN_00350738; FUN_00357050; FUN_00358ea0; FUN_00350618;
     *   if (x19 || (x16_00&1)) break;
     * end: FUN_0034ed28; FUN_00351348; FUN_00353d14 */
    (*(void (**)(void))(0x658c00))();
    sk_object_lock(0, 0, 0, 0, 0);
    sk_queue_complete(0, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_00286e40 @ 0x00286e40   (est. sk_object_service_pump_wrap)
 * Ghidra: void FUN_00286e40(void)
 * Wrapper: FUN_00354d44, then FUN_00286c10 (pump), then FUN_00356d20.
 * Confidence: medium.
 */
void sk_object_service_pump_wrap(void)
{
    /* FUN_00354d44 */
    sk_object_service_pump();  /* FUN_00286c10 */
    /* FUN_00356d20 */
}

/*--------------------------------------------------------------------*/
/* FUN_00286e80 @ 0x00286e80   (est. sk_object_lock_quick)
 * Ghidra: void FUN_00286e80(void)
 * Quick lock helper: FUN_003585f4 / FUN_0035694c / FUN_00349ea0 /
 * FUN_00377824 / FUN_0014ae44 / FUN_003505d0 / FUN_0034e5fc / FUN_0035396c.
 * Confidence: low.
 */
void sk_object_lock_quick(void)
{
    /* FUN_003585f4 / FUN_0035694c / FUN_00349ea0 / FUN_00377824 /
     * FUN_0014ae44 / FUN_003505d0 / FUN_0034e5fc / FUN_0035396c */
    sk_object_lock(0, 0, 0, 0, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_00286ee8 @ 0x00286ee8   (est. sk_object_service_z)
 * Ghidra: void FUN_00286ee8(undefined8 param_1..param_6)
 * Object service with a notify loop: acquires the object lock, pulls
 * notifications (FUN_00377bec + FUN_000a68f4), dispatches through the
 * per-object handler, and on completion frees the waiter (FUN_0036b118)
 * before the FUN_00353d14 epilogue.
 * Confidence: low.
 */
void sk_object_service_z(void *param_1, void *param_2, void *param_3, void *param_4,
                         void *param_5, void *param_6)
{
    (void)param_1; (void)param_2;
    /* FUN_00353cfc / FUN_00359634 / FUN_003509c8(param_4) /
     * (*DAT_00658c00)(x16+0x40) / FUN_003497b4 / FUN_00352078 /
     * FUN_00350488 / FUN_00377824 / FUN_00348cd0 / FUN_0007c1a4 /
     * (*DAT_00658c00)() / FUN_0034af20 / FUN_00350920 / FUN_0034d464 /
     * FUN_0034b0c4 / FUN_0034998c / FUN_00348f50 / FUN_00350488 /
     * FUN_00377824 / FUN_00348ce8 / FUN_0034d3c4 / FUN_003497a0 /
     * FUN_00377824 / FUN_00352efc / FUN_001a0414 / FUN_00358cd4 /
     * FUN_00352680 / FUN_003511a8 / FUN_0034b278 / FUN_000e72b0 /
     * FUN_00377bec / FUN_000a68f4
     * loop: (*pcVar3)(param_5, msg); FUN_00352290; FUN_00350884;
     *   if ZR: FUN_00354324; goto epilogue
     *   else: FUN_00350c38; FUN_00354834; FUN_003509b0;
     *     if x19: FUN_00354324; FUN_0036b118(uVar2); goto epilogue
     *     FUN_00310d34; FUN_00355c1c; FUN_001a2128
     * epilogue: FUN_00351348; FUN_00353d14 */
    (*(void (**)(void))(0x658c00))();
    sk_object_lock(0, 0, 0, 0, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_002871b4 @ 0x002871b4   (est. sk_object_service_w_forward)
 * Ghidra: void FUN_002871b4(void)
 * Forwarder to FUN_002871cc.
 * Confidence: medium.
 */
void sk_object_service_w_forward(void)
{
    sk_object_service_w(0, 0, 0, 0, 0);  /* FUN_002871cc */
}

/*--------------------------------------------------------------------*/
/* FUN_002871cc @ 0x002871cc   (est. sk_object_service_w)
 * Ghidra: void FUN_002871cc(undefined8 param_1..param_5)
 * Object service loop: acquire lock, dispatch through the object's handlers
 * (FUN_00354d14 / FUN_00377bec), loop until completion; frees waiter
 * (FUN_0036b118) on the x21 exit. Epilogue FUN_00353d14.
 * Confidence: low.
 */
void sk_object_service_w(void *param_1, void *param_2, void *param_3, void *param_4,
                         void *param_5)
{
    (void)param_1; (void)param_2;
    /* FUN_00353cfc / FUN_003516cc / FUN_00310d68 / FUN_000a6f88 /
     * FUN_0007c1a4 / (*DAT_00658c00)() / FUN_0034aee4 / FUN_00349b00 /
     * FUN_003497b4 / FUN_003497a0 / FUN_00377824 / FUN_00348fd8 /
     * FUN_0034b05c / FUN_0035113c / FUN_0034d464 / FUN_0034b2f8 /
     * FUN_003499f0 / FUN_00348f38 / FUN_00349830 / FUN_000dbf08 /
     * FUN_00377824 / FUN_000a6f88 / FUN_0034b0d4 / FUN_001a0414 /
     * FUN_00354d14 / FUN_000a68c4 / FUN_0035102c / FUN_0034b278 /
     * FUN_00377bec / FUN_000a68f4
     * loop: FUN_00351384; (*pcVar3)(); FUN_0035172c; FUN_00350884;
     *   if ZR: FUN_00353be8; FUN_00350a34; goto epilogue
     *   else: FUN_003578b4; FUN_00351274; FUN_003531a8; (*auVar4._0_8_)();
     *     FUN_00357170; FUN_003510dc;
     *     if x21: FUN_00353be8; FUN_00350a34; FUN_0036b118(uVar2); goto epilogue
     *     FUN_00351738; FUN_0035a274; FUN_00350884; FUN_00354bbc / FUN_00353bf4
     * epilogue: FUN_00351348; FUN_00353d14 */
    (*(void (**)(void))(0x658c00))();
    sk_object_lock(0, 0, 0, 0, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_00287580 @ 0x00287580   (est. sk_swift_string_set_build)
 * Ghidra: undefined8 * FUN_00287580(long param_1)
 * Swift Set builder: converts an array of string keys (param_1+0x20, stride
 * 0x10, count at +0x10) into a hash set (DAT_00657728 set descriptor), using
 * the string hash FUN_001a8564 and an open-addressing probe table
 * (puVar8[6] entries, bitmask puVar8+7). De-duplicates keys via
 * FUN_002a0d50 compare. Releases key strings (FUN_003a25d4) and the array
 * (FUN_0036b118). Returns the set.
 * Confidence: high (Swift Set-from-array, de-dup + hash-probe shape).
 */
void *sk_swift_string_set_build(void *arr)
{
    if (*(long *)((char *)arr + 0x10) == 0) return (void *)0x6577e0;  /* DAT_006577e0 */
    /* FUN_001fab14 + FUN_0025e4a0 allocate set with descriptor 0x657728 */
    void *set = (void *)0x657728;
    long count = *(long *)((char *)arr + 0x10);
    long i = 0;
    do {
        long key = *(long *)((char *)arr + 0x20 + i * 0x10);
        unsigned long keyhi = *(unsigned long *)((char *)arr + 0x28 + i * 0x10);
        /* local_88 = xor 0x65777365 'setedbyted' ; local_98 = xor 0x646f72616e646f6d */
        unsigned long hash = sk_swift_string_hash();   /* FUN_001a8564 */
        unsigned char nbits = *(unsigned char *)((char *)set + 4);
        unsigned long h = hash & ~(-1L << (nbits & 0x3f));
        while ((*(unsigned long *)((char *)set + 56 + (h >> 6) * 8) >> (h & 0x3f) & 1) != 0) {
            void *slot = (void *)(*(unsigned long *)((char *)set + 48) + h * 0x10);
            long skey = *(long *)slot;
            unsigned long skeyhi = *(unsigned long *)((char *)slot + 8);
            if ((skey == key && skeyhi == keyhi) ||
                ((skeyhi ^ -1UL) & 0x6000000000000000) == 0 ||
                ((keyhi & 0x6000000000000000) == 0x6000000000000000 &&
                 (skeyhi = sk_swift_string_cmp(skey, skeyhi, key, keyhi, 0), (skeyhi & 1) != 0))) {
                sk_swift_release(keyhi);
                goto next;
            }
            h += 1;
        }
        sk_swift_set_insert(key, keyhi, h, set);   /* FUN_000b394c */
next:
        i += 1;
    } while (i != count);
    sk_free(arr);   /* FUN_0036b118 */
    return set;
}

/*--------------------------------------------------------------------*/
/* FUN_00287794 @ 0x00287794   (est. sk_swift_set_apply)
 * Ghidra: long FUN_00287794(long param_1, long param_2, undefined8 param_3)
 * Swift Set apply/map: iterates the source collection (param_1, count at
 * +0x10), applying the object's iterate handler (lVar8+0x10) to each element
 * and the per-set hash-probe insert (local_70 bitmask + FUN_0025c2b8),
 * short-circuiting when the apply predicate returns nonzero.
 * Confidence: low (Set apply with object method-table dispatch).
 */
long sk_swift_set_apply(void *src, void *obj, void *param_3)
{
    long type = *(long *)((char *)obj - 8);
    /* (*DAT_00658c00)(type+0x40) stack setup */
    long l3 = sk_set_descriptor(*(void **)((char *)obj - 8 + 0x40));  /* FUN_0025a060 */
    if (*(long *)((char *)src + 0x10) != 0) {
        /* local_98 = FUN_0031948c(param_3); local_70 = l3+0x38; local_a0 = type+0x20;
         * local_78 = type+0x10; local_a8 = type+8 ... */
        long count = *(long *)((char *)src + 0x10);
        long i = 0;
        do {
            /* FUN_0019ea20; (*(type+0x20))(stack, ...); uVar4 = (*local_98)(l3+0x28,...) */
            unsigned long h = 0;
            unsigned char nbits = *(unsigned char *)((char *)l3 + 0x20);
            h &= ~(-1L << (nbits & 0x3f));
            while ((*(unsigned long *)((char *)l3 + 0x38 + (h >> 6) * 8) >> (h & 0x3f) & 1) != 0) {
                (*(void (**)(void*, void*, void*))(type + 0x10))(
                    (void *)(*(long *)((char *)l3 + 0x30) + *(long *)((char *)type + 0x48) * h),
                    (void *)0, obj);
                unsigned long v = sk_swift_elem_transform(0, param_3);   /* FUN_00027754/FUN_0014ae44 */
                void (*cb)(void*,void*,void*) = *(void (**)(void*,void*,void*))(type + 8);
                cb(0, 0, obj);
                if ((v & 1) != 0) { cb(0, 0, obj); goto done; }
                h += 1;
            }
            sk_set_insert(h, l3, obj);   /* FUN_0025c2b8 */
done:
            i += 1;
        } while (i != count);
    }
    sk_free(src);   /* FUN_0036b118 */
    return l3;
}

/*--------------------------------------------------------------------*/
/* FUN_00287d08 @ 0x00287d08   (est. sk_cap_badge_store)
 * Ghidra: void FUN_00287d08(void)
 * Stores a badge/capability value: resolves the object (FUN_00352194) and
 * writes the per-object uint field (+8) via FUN_0025bae0.
 * Confidence: medium (small setter, clean shape).
 */
void sk_cap_badge_store(void)
{
    unsigned long obj = sk_swift_elem_transform2();  /* FUN_00352194 */
    /* FUN_0025bae0(obj, *(uint *)(x19+8)); FUN_00357670 */
}

/*--------------------------------------------------------------------*/
/* FUN_00287d34 @ 0x00287d34   (est. sk_cap_tree_walk)
 * Ghidra: void FUN_00287d34(void)
 * Walks a capability tree / object table: saves thread state (FUN_0008e518),
 * reads the object descriptor (+0x10 non-null gate), and iterates entries via
 * FUN_00359fa0 while the per-object bitmask (x26) is set, invoking the
 * per-entry handler (extraout_x16+0x10). Returns the final index via
 * FUN_00359920. Epilogue FUN_0008e500.
 * Confidence: low (capability-tree walk with bitmask iteration).
 */
void sk_cap_tree_walk(void)
{
    /* FUN_0008e518 / FUN_00352c34 / FUN_00349720 / (*DAT_00658c00)(x8+0x40) /
     * FUN_00348f50; if (obj+0x10 != 0):
     *   lVar1 = FUN_00354948(obj[0x20]);
     *   while (uVar2 = FUN_00359fa0(lVar1), (extraout_x8_01 >> (x26&0x3f) & 1) != 0):
     *     FUN_00356260(x16+0x10, uVar2, obj[0x30] + (x16+0x48)*x26);
     *     FUN_00351ef8; FUN_0034d49c; FUN_00351b20; FUN_00357b04; FUN_00350630;
     *     uVar2 = (*extraout_x8_04)();
     *     if (auVar5._0_8_ & 1) { uVar4 = obj[0x24]; goto done; }
     *   done: uVar4 = 0x100000000;
     * FUN_00359920; FUN_0008e500 */
    (*(void (**)(void))(0x658c00))();
    sk_queue_complete(0, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_00287d38 / FUN_00287d3c   (est. sk_cap_tree_walk_variants)
 * Ghidra: void FUN_00287d38(void) / FUN_00287d3c(void)
 * Identical forwarders to FUN_00287d34.
 * Confidence: medium.
 */
void sk_cap_tree_walk_a(void)  /* FUN_00287d38 */
{
    sk_cap_tree_walk();
}
void sk_cap_tree_walk_b(void)  /* FUN_00287d3c */
{
    sk_cap_tree_walk();
}

/*--------------------------------------------------------------------*/
/* FUN_00287d54 @ 0x00287d54   (est. sk_obj_desc_read_a)
 * Ghidra: void FUN_00287d54(undefined1 (*param_1)[12])
 * Reads a 12-byte object descriptor from the object (via thunk_FUN_0025baa4).
 * Confidence: medium (trivial 12-byte copy).
 */
void sk_obj_desc_read_a(void *out)
{
    /* auVar1 = thunk_FUN_0025baa4(*x20); *out = auVar1 (12 bytes) */
    sk_swift_elem_transform2();
}

/*--------------------------------------------------------------------*/
/* FUN_00287d84 @ 0x00287d84   (est. sk_obj_desc_read_b)
 * Ghidra: void FUN_00287d84(undefined1 (*param_1)[12])
 * Same as above but via thunk_FUN_00355354.
 * Confidence: medium.
 */
void sk_obj_desc_read_b(void *out)
{
    /* auVar1 = thunk_FUN_00355354(*x20); *out = auVar1 */
    sk_swift_elem_transform2();
}

/*--------------------------------------------------------------------*/
/* FUN_00287db4 @ 0x00287db4   (est. sk_cap_node_create)
 * Ghidra: undefined * FUN_00287db4(long *param_1, undefined8 *param_2, long param_3)
 * Allocates a 0x28-byte capability-node object (tag 0x96c4), runs the
 * constructor FUN_00287e30 with the caller's cap fields, stores the vtable
 * (DAT_003471a4).
 * Confidence: medium (allocate + construct + vtable).
 */
void *sk_cap_node_create(void **slot, unsigned long *cap, void *obj)
{
    void *node = sk_alloc(0x28, 0x96c4);  /* FUN_0036a908(0x28, 0x96c4) */
    *slot = node;
    void *v = sk_cap_node_create_impl(node, cap[0], *(unsigned int *)(cap + 1),
                                      *(void **)0, *(void **)((char *)obj + 0x10),
                                      *(void **)((char *)obj + 0x18));  /* FUN_00287e30 */
    *(void **)((char *)node + 0x20) = v;
    return (void *)0x3471a4;  /* DAT_003471a4 */
}

/*--------------------------------------------------------------------*/
/* FUN_00287e30 @ 0x00287e30   (est. sk_cap_node_create_impl)
 * Ghidra: undefined1 [16] FUN_00287e30(long *param_1, undefined8 param_2, ...)
 * Allocates the per-type cap-node instance (tag 0x5732) sized by the type
 * descriptor (+0x40), and calls the cap-setup FUN_00287c68. Returns a
 * {vtable, node} 16-byte pair.
 * Confidence: low (allocator plumbing).
 */
void *sk_cap_node_create_impl(void **out, unsigned long p2, unsigned long p3,
                              void *p4, void *p5, void *p6)
{
    (void)p4; (void)p5; (void)p6;
    long type = *(long *)((char *)p5 - 8);
    out[0] = p5;
    out[1] = (void *)type;
    void *node = sk_alloc(*(unsigned long *)((char *)type + 0x40), 0x5732);  /* FUN_0036a908 */
    out[2] = node;
    sk_cap_setup(node, p2, p3, p4, p5);  /* FUN_00287c68 */
    return node;
}

/*--------------------------------------------------------------------*/
/* FUN_00287ee8 @ 0x00287ee8   (est. sk_obj_state_reset)
 * Ghidra: void FUN_00287ee8(long param_1)
 * Resets object state: runs FUN_00359350 + FUN_00287d34 (tree walk) +
 * FUN_00357670, then stores a status byte at param_1+0xc and zero at +0xd.
 * Confidence: medium (state reset with status flags).
 */
void sk_obj_state_reset(void *obj)
{
    /* FUN_00359350 */
    sk_cap_tree_walk();  /* FUN_00287d34 */
    /* FUN_00357670 */
    *(unsigned char *)((char *)obj + 0xc) = 0;
    *(unsigned char *)((char *)obj + 0xd) = 0;
}

/*--------------------------------------------------------------------*/
/* FUN_00287f20 @ 0x00287f20   (est. sk_obj_desc_write)
 * Ghidra: void FUN_00287f20(undefined1 (*param_1)[12], undefined8 *param_2)
 * Writes a 12-byte object descriptor from cap fields via thunk_FUN_0025bae0.
 * Confidence: medium.
 */
void sk_obj_desc_write(void *out, unsigned long *cap)
{
    /* auVar1 = thunk_FUN_0025bae0(cap[0], *(uint*)(cap+1), *x20); *out = auVar1 */
    sk_swift_elem_transform2();
}

/*--------------------------------------------------------------------*/
/* FUN_00287c68 @ 0x00287c68   (est. sk_cap_setup)
 * Ghidra: void FUN_00287c68(undefined8 param_1, ulong param_2, int param_3,
 *        long param_4, long param_5)
 * Installs a capability into the object's cap table: validates that the slot
 * index param_2 is in-bounds (>=0, < the bit width in param_4+0x20, and the
 * slot bit is set in the bitmap at param_4+0x38) and matches the type index
 * (param_4+0x24); on success dispatches the per-type cap install handler
 * (param_5-8 + 0x10) with the element pointer. Any validation failure raises
 * the noreturn panic FUN_001afe4c.
 * Confidence: medium (cap-slot install with explicit bounds/bitmap checks).
 */
void sk_cap_setup(void *param_1, unsigned long slot, int type_idx, void *table,
                  void *obj)
{
    unsigned long nbits = *(unsigned char *)((char *)table + 0x20) & 0x3f;
    if (((long)slot >= 0) && ((slot >> nbits) == 0) &&
        ((*(unsigned long *)((char *)table + (slot >> 6) * 8 + 0x38) >> (slot & 0x3f) & 1) != 0) &&
        (type_idx == *(int *)((char *)table + 0x24))) {
        /* indirect jump through obj-8 + 0x10 (cap install handler) */
        void (*install)(void *, void *, void *) = *(void (**)(void *, void *, void *))((char *)obj - 8 + 0x10);
        install(param_1, (void *)(*(long *)((char *)table + 0x30) +
                                  *(long *)((char *)obj - 8 + 0x48) * slot), obj);
        return;
    }
    /* FUN_003488bc(1); FUN_0034a3ec; noreturn FUN_001afe4c */
    sk_fatal_error(0xb, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0);
}
