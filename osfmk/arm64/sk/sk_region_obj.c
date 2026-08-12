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

/* Out-of-range kernel helpers referenced by this region (FUN_ addr in
 * comment; reconstructed by sibling SK range workers). Names are estimates. */

/* Core lock/refcount/allocator primitives (region 0x34xxxx-0x37xxxx). */
extern void *sk_alloc(unsigned long size, unsigned long tag);        /* FUN_0036a908 */
extern void *sk_alloc_pages(unsigned long size, unsigned long tag);  /* FUN_0036b270 */
extern void sk_free(void *ptr);                                      /* FUN_0036b118 */
extern unsigned long sk_object_lock(unsigned long a, unsigned long b,
                                    unsigned long c, void *dbg1, void *dbg2); /* FUN_00377824 */
extern unsigned long sk_lock_ref(unsigned long a);                   /* FUN_00377bec */
extern void sk_lock_release(unsigned long a);                        /* FUN_00377dcc */
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
    do {
        n -= 1;
        if (n == 0) return;
        unsigned long lk = sk_object_lock(0xff, lk2, lk1, sk_obj_methods_0, (void *)0x611b3c); /* FUN_00377824 */
        unsigned long item = sk_lock_ref(lk2, lk1, lk, sk_obj_methods_0, (void *)0x611b2c); /* FUN_00377bec */
        void (*cb)(void *, unsigned long, unsigned long) = (void *)sk_alloc_pages(0, 0); /* FUN_000a68f4 */
        unsigned long item2 = sk_lock_release(0, lk);  /* FUN_00377dcc */
        cb(param_1, item2, item);
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

