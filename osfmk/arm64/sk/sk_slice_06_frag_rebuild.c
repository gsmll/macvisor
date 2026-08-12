/* sk_slice_06_frag_rebuild.c — VAS rebuild path (0x31868-0x31bf4).
 * Global VAS bring-up + the "rebuild" pass that re-materialises span
 * backings after a cold/hot reboot of the address space. */

#include "sk_slice_06_shared.h"

/* ---- Local externs (FUN_/DAT_ addresses = ground truth; bodies live in
 * sibling slices / other fragments). These are declared here because the
 * shared header only forward-declares the 120 slice functions, not the
 * VAS globals or the cross-slice fault/supervisor helpers used below. ---- */

/* Early-vspace data region (0x64cxxx / 0x6axxxx). */
extern void *sk_vspace_root_obj;            /* DAT_0064c3f0 */
extern unsigned long sk_vspace_free_head;   /* DAT_0064c528 */
extern void *sk_vspace_free_tail;           /* DAT_0064c530 */
extern unsigned long sk_vspace_lock;        /* DAT_0064c5e0 */
extern unsigned long sk_vspace_lock2;       /* DAT_0064c430 */
extern unsigned long sk_vspace_c5f0;        /* DAT_0064c5f0 */
extern unsigned long sk_vspace_c690;        /* DAT_0064c690 */
extern unsigned long sk_vspace_c6b0;        /* DAT_0064c6b0 */
extern unsigned long sk_vspace_sentinel_tag;    /* _DAT_006aef68 */
extern void *sk_vspace_sentinel_next;       /* _DAT_006aef58 */
extern unsigned long sk_vspace_sentinel_eff0;   /* _DAT_006aeff0 */

/* Fixed L4 error-word block (data 0x4bc028-40) used to seed supervisor msgs. */
extern unsigned long sk_l4_err_word0;       /* _DAT_004bc028 */
extern unsigned long sk_l4_err_word1;       /* 0x4bc030 */
extern unsigned long sk_l4_err_word2;       /* _DAT_004bc038 */
extern unsigned long sk_l4_err_word3;       /* 0x4bc040 */

/* Lock helpers — take the lock address (the shared header's zero-arg
 * sk_vm_lock_acquire/sk_vm_lock_release do not fit the call sites here). */
extern int sk_lock_acquire(uint64_t lock);  /* FUN_00118164 */
extern int sk_lock_release(uint64_t lock);  /* FUN_00118194 */

/* VAS fault / supervisor helpers. */
extern void sk_vas_fault9(void);            /* FUN_004b1f74 */
extern void sk_vas_fault11(void);           /* FUN_004b2034 */
extern void sk_vas_fault12(void);           /* FUN_004b2084 */
extern void sk_vas_fault13(void);           /* FUN_004b1fd4 */
extern uint64_t sk_vas_rebuild_peer(void);  /* FUN_004b1fac — returns the peer/global vspace */
extern void sk_vas_fault15(void);           /* FUN_004b200c */
extern void sk_vas_fault16(void);           /* FUN_004b205c */
extern void sk_vas_fault17(uint64_t marker);/* FUN_004b1c84 */

/* Span-capability / spanmap helpers. */
extern void sk_vas_cap_desc_build(uint64_t *out, uint64_t span, uint64_t count); /* FUN_000287e4 */
extern uint64_t sk_spanmap_lookup(uint64_t vas, long level, long va);            /* FUN_00042abc */
extern uint64_t sk_spanmap_release(uint64_t vas, uint64_t va);                   /* FUN_00042c20 */
extern cl4_result_t sk_vas_span_map_op2(uint64_t vas, uint64_t a, uint64_t b,
                                        uint64_t c, uint64_t d, uint64_t e);      /* FUN_00043be8 */
extern uint64_t sk_vas_populate_level_nonself(uint64_t vas, uint64_t va);        /* FUN_000436fc */
extern void sk_l4_error_word(void **out, unsigned char code);                    /* FUN_00032d08 */

/* GENTER supervisor entries (opcode 0x00201420 — enters GL1; the selector in
 * x16 picks the dispatch endpoint). Ghidra renders the two endpoints as the
 * indirect calls SUB_90000010f9002830 / SUB_f9002c30dac10230. */
extern uint64_t sk_supervisor_alloc_span(uint64_t vas, uint64_t op, void *msg_in,
                                         uint64_t *msg_out, uint64_t a5, void *msg_in2); /* SUB_90000010f9002830 */
extern uint64_t sk_supervisor_map_span(uint64_t root, uint64_t frame, uint64_t a3,
                                       uint64_t cap);                            /* SUB_f9002c30dac10230 */

/* Stack canary value (the -0x2c8502b44bfffed6 constant from the decompiles). */
#define SK_VAS_CANARY 0xd37afd4bb400012aull

/* Error-code bounds check. Decompiled as the three-clause pointer comparison
 * (&DAT_0064cb40 + c < 0x64cb81, with the two lower clauses always true);
 * 0x64cb81 - 0x64cb48 == 0x39. */
static bool sk_err_in_range(uint64_t c) { return c < 0x39; }

/*--------------------------------------------------------------------*/
/* FUN_00031868 @ 0x00031868   (est. sk_vas_global_init)
 * Ghidra: void FUN_00031868(void)
 * Early VAS subsystem bring-up. Initialises the early vspace descriptor at
 * 0x6ac270 (FUN_00030b2c) and the object method table (FUN_00034970), resets
 * the free-run list head (DAT_0064c528/.530), initialises the vspace lock
 * (DAT_0064c5e0) and a secondary list head (DAT_0064c690), then — when no
 * vspace of type 4/flags 10 exists yet — builds a 0x1001-tagged free-run
 * sentinel (0x6aef58 → 0x6aef70, root at 0x6aef50) and links the initial
 * vspace object into the root table (FUN_00030fb0). Aborts (VAS 005aed68) on
 * any failure.
 * Confidence: medium (structural; global refs DAT_0064c3f0/6aef58 etc.).
 */
static void sk_vas_global_init(void)
{
    int r;
    uint64_t v;

    sk_vas_desc_init((uint64_t *)0x6ac270);                          /* FUN_00030b2c */
    sk_vas_obj_init((uint64_t)(uintptr_t)&sk_vspace_root_obj, 0x65b5c8,
                    (uint64_t *)0x65b580);                           /* FUN_00034970 */
    sk_vspace_free_head = 0;
    sk_vspace_free_tail = &sk_vspace_free_head;
    r = sk_mutex_init(&sk_vspace_lock, 0);                           /* FUN_00118148 */
    if (r != 0)
        sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5aed68);
    sk_vspace_c5f0 = 0;
    sk_list_init(&sk_vspace_c690);                                   /* FUN_0005ba5c */
    r = sk_mutex_init((void *)0x6ad2b0, 0);                          /* FUN_00118148 */
    if (r != 0)
        sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5aed68);
    v = sk_vspace_lookup(4, 10);                                     /* FUN_0005baac */
    if (v == 0) {
        r = sk_mutex_init((void *)0x6af000, 0);                      /* FUN_00118148 */
        if (r == 0) {
            sk_vspace_sentinel_tag = 0x1001;                         /* _DAT_006aef68 */
            sk_vspace_sentinel_next = (void *)0x6aef70;              /* _DAT_006aef58 */
            sk_list_init(&sk_vspace_c6b0);                           /* FUN_0005ba5c */
            sk_vas_set_root((uint64_t)(uintptr_t)&sk_vspace_sentinel_next); /* FUN_00034920 */
            sk_vspace_sentinel_eff0 = 0x6aef50;                      /* _DAT_006aeff0 */
            r = sk_lock_acquire((uint64_t)&sk_vspace_lock2);         /* FUN_00118164 */
            if (r != 0)
                sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5aed68);
            sk_vas_page_add((uint64_t)(uintptr_t)&sk_vspace_root_obj,
                            (uint64_t *)0x6ac270);                   /* FUN_00030fb0 */
            r = sk_lock_release((uint64_t)&sk_vspace_lock2);         /* FUN_00118194 */
            if (r == 0) return;
            sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5aed68);
        }
    } else {
        sk_vas_fault9();                                             /* FUN_004b1f74 */
    }
    sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5aed68);
}

/*--------------------------------------------------------------------*/
/* FUN_00031bf4 @ 0x00031bf4   (est. sk_vas_rebuild_inner)
 * Ghidra: void FUN_00031bf4(long param_1)
 * Inner VAS rebuild: walks the red-black interval tree rooted at vas+0x148
 * and, for every span entry whose +0x10 word is still zero (not yet
 * re-materialised), re-allocates the level backing descriptor (via a GENTER
 * supervisor call), builds a capability with FUN_000287e4, maps the frame
 * into the root vspace, and runs the span-map op (FUN_00043be8, retrying
 * through FUN_000436fc on a preempted result) before linking the span into
 * the last-mapped chain (vas+0x1c8). Clears the in-progress bit in the
 * 16-bit flag at vas+0x1d0 when done. Aborts / SoftwareBreakpoint(0x5519)
 * on any inconsistency.
 * Confidence: high (structure matches rebuild's second half 1:1).
 */
static void sk_vas_rebuild_inner(uint64_t vas)
{
    uint64_t canary = SK_VAS_CANARY;
    uint64_t cur, eptr, next, slot, backing, frame, base_va, last;
    uint64_t off, idx, target_va, span, rel, desc, err, sp_start, sp_end, size;
    uint64_t new_end;
    uint64_t msg[5], out[2];
    bool changed, made_progress;
    int r;
    cl4_result_t cres;

    if ((*(uint8_t *)(vas + 9) & 1) == 0) {
        sk_vas_fault12();                        /* FUN_004b2084 */
    ab_5aed68:
        sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5aed68);
    }
    if ((*(uint8_t *)(vas + 0x1d0) & 1) == 0) {  /* not already rebuilding */
        changed = false;
        *(uint8_t *)(vas + 0x1d0) = 1;           /* mark rebuild in progress */
        cur = vas + 0x148;                       /* red-black tree head */
        do {
            if (*(uint64_t *)(cur + 8) == 0) {   /* level backing not allocated yet */
                msg[0] = sk_l4_err_word0;        /* _DAT_004bc028 */
                msg[1] = sk_l4_err_word1;        /* 0x4bc030 */
                msg[2] = sk_l4_err_word2;        /* _DAT_004bc038 */
                msg[3] = sk_l4_err_word3;        /* 0x4bc040 */
                msg[4] = 0;
                out[0] = 0; out[1] = 0;
                if (sk_lock_release(vas + 0x40) != 0)  /* FUN_00118194 */
                    goto ab_5aed68;
                /* GENTER: supervisor span-backing allocation (op 0x1800).
                 * msg doubles as the in/out message block; out[1] carries the
                 * returned type tag, out[0] the allocated backing. */
                err = sk_supervisor_alloc_span(vas, 0x1800, msg, out, 0, msg);
                err &= 0xff;
                if (err != 0) {
                    if (sk_err_in_range(err))
                        sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5afade);
                    goto trap_32460;
                }
                if (out[1] != 0x65b648)          /* returned type tag mismatch */
                    sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5afb3f);
                if (sk_lock_acquire(vas + 0x40) != 0)  /* FUN_00118164 */
                    goto ab_5aed68;
                if (*(uint64_t *)(cur + 8) != 0)
                    sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5afba3);
                *(uint64_t *)(cur + 8) = out[0]; /* store the allocated backing */
                changed = true;
            }
            off = 0;
            idx = 0;
            eptr = cur + 9;                      /* start of the 7 span-slot entries */
            made_progress = changed;
            do {
                /* pointer-overflow guard (decompiled bounds check) */
                if ((uintptr_t)cur + 0x80 < (uintptr_t)eptr + 8 ||
                    (uintptr_t)eptr + 8 < (uintptr_t)eptr)
                    goto trap_32460;
                slot = *(uint64_t *)eptr;
                if (slot == 0) break;            /* empty slot: stop this node */
                if (*(uint64_t *)(slot + 0x10) == 0) {   /* span not yet mapped */
                    if ((*(uint8_t *)(vas + 9) & 1) == 0) {
                        sk_vas_fault16();        /* FUN_004b205c */
                    ab_5afcfb:
                        sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5afcfb);
                    }
                    backing = *(uint64_t *)(cur + 8);
                    if (backing == 0)
                        sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5afc10);
                    last = *(uint64_t *)(vas + 0x1c8);
                    if (last != 0) {
                        if (*(uint64_t *)(last + 0x10) == 0)
                            sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5afc68);
                        if (*(uint64_t *)(*(uint64_t *)(last + 0x18) + 8) != 0)
                            goto ab_5afcfb;
                    }
                    frame = *(uint64_t *)(slot + 0x18);
                    if (frame == 0 || (frame & 0x3fff) != 0)   /* must be 16K aligned */
                        sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5afdb8);
                    base_va = *(uint64_t *)(backing + 8);
                    if (sk_lock_release(vas + 0x40) != 0)      /* FUN_00118194 */
                        goto ab_5aed68;
                    /* sub-object lock lives at backing + 0x80 */
                    if ((uintptr_t)backing + 0x90 < (uintptr_t)(backing + 0x80))
                        goto trap_32460;
                    if (sk_lock_acquire(backing + 0x80) != 0)  /* FUN_00118164 */
                        goto ab_5aed68;
                    msg[0] = 0; msg[1] = 0; msg[2] = 0; msg[3] = 0; msg[4] = 0;
                    /* build the span capability descriptor; count = (va>>14)+1 */
                    sk_vas_cap_desc_build(msg,
                                          *(uint64_t *)(backing + 0x78),
                                          ((off + (base_va - *(uint64_t *)(vas + 0x88))) >> 0xe) + 1);
                    desc = msg[0];
                    *(uint64_t *)(backing + 0x78) = msg[4];
                    r = sk_lock_release(backing + 0x80);       /* FUN_00118194 */
                    if (desc == 0) {
                        if (r != 0) goto ab_5aed68;
                        if (sk_err_in_range(msg[2] & 0xff))
                            sk_vas_abort("spanmap could not alloc a cap");
                        goto trap_32460;
                    }
                    if (r != 0) goto ab_5aed68;
                    target_va = off + base_va;
                    span = sk_spanmap_lookup(vas + 0x60, 1, target_va);  /* FUN_00042abc */
                    rel = sk_spanmap_release(vas + 0x60, span);          /* FUN_00042c20 */
                    if ((rel & 1) == 0)
                        sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5afecd);
                    /* GENTER: map the frame into the root vspace. */
                    err = sk_supervisor_map_span((uint64_t)(uintptr_t)&sk_vspace_root_obj,
                                                 frame, 0, desc);
                    err &= 0xff;
                    if (err != 0) {
                        if (sk_err_in_range(err))
                            sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5aff2f);
                        goto trap_32460;
                    }
                    cres = sk_vas_span_map_op2(vas + 0x60, span, desc, target_va, 0, 0); /* FUN_00043be8 */
                    err = cres.lo;
                    if ((err & 0xff) == 4) {     /* preempted: populate level, then retry */
                        err = sk_vas_populate_level_nonself(vas + 0x60, target_va);  /* FUN_000436fc */
                        if ((err & 1) == 0)
                            sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5affa4);
                        cres = sk_vas_span_map_op2(vas + 0x60, span, desc, target_va, 0, 0);
                        err = cres.lo;
                    }
                    if ((err & 0xff) != 0) {
                        sk_l4_error_word((void **)out, 0);   /* first call; code elided in decompile */
                        sk_vas_fault17(0xeb1a02bf914012ba);  /* FUN_004b1c84 */
                        sk_l4_error_word((void **)out, (uint8_t)(err & 0xff));
                        sk_vas_abort("Unexpected L4 Error: %s (%zu, err)");
                    }
                    if (sk_lock_acquire(vas + 0x40) != 0)    /* FUN_00118164 */
                        goto ab_5aed68;
                    if (*(uint64_t *)(slot + 0x10) != 0)
                        sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5b0136);
                    sp_start = *(uint64_t *)(slot + 0x18);   /* span start */
                    sp_end = *(uint64_t *)(slot + 0x20);     /* span end */
                    if (0x3fff < (uint64_t)(sp_end - sp_start))
                        sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5b0195);
                    size = *(uint64_t *)(slot + 8);
                    if (0x4000 < (uint64_t)((size - sp_start) + 0x3fe0))
                        sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5b01eb);
                    new_end = sp_end + off + (base_va - sp_start);
                    *(uint8_t *)(sp_start + 2) = 1;          /* mark mapped */
                    /* overflow guard; the decompiled second clause
                     * (sp_start + l18 + ((sp_end-sp_start)+idx*0x4000-sp_end) < 1)
                     * reduces algebraically to 1 < 1, i.e. always false. */
                    if (new_end + 1 < new_end)
                        goto trap_32460;
                    *(uint64_t *)sp_start = new_end;
                    *(uint16_t *)(sp_start + 0x11) = 0x101;  /* span tag */
                    *(uint64_t *)sp_end = off + ((base_va + size) - sp_start);
                    if (last != 0)
                        *(uint64_t *)(*(uint64_t *)(last + 0x18) + 8) = target_va;
                    *(uint64_t *)(vas + 0x1c8) = slot;        /* remember last mapped */
                    *(uint64_t *)(slot + 0x10) = target_va;   /* mark mapped */
                    made_progress = true;
                }
                idx++; off += 0x4000; eptr++;
            } while (off != 0x1c000);            /* 7 slot entries (0x1c000/0x4000) */
            next = *(uint64_t *)cur;             /* red-black child */
            cur = (next != 0) ? next : (vas + 0x148);
            changed = (next != 0) && made_progress;
        } while (next != 0 || made_progress);
        if ((*(uint8_t *)(vas + 0x1d0) & 1) == 0)
            sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5afa56);
        *(uint16_t *)(vas + 0x1d0) = 0x100;      /* clear in-progress, set bit 8 */
    }
    if (canary == SK_VAS_CANARY) return;
    sk_stack_chk_fail();                         /* FUN_0011d7e8 */

trap_32460:
    /* SoftwareBreakpoint(0x5519, 0x32460) — does not return */
    SK_ASRT_PANIC(0x32460);
}

/*--------------------------------------------------------------------*/
/* FUN_00031a8c @ 0x00031a8c   (est. sk_vas_rebuild)
 * Ghidra: long FUN_00031a8c(long param_1, long param_2)
 * VAS rebuild entry point. Validates the kind tag (must be 0x65b5c8) and the
 * presence of a rebuild target at vas+400, then either runs the inner rebuild
 * (FUN_00031bf4) or, if the single-byte flag at vas+0x1d0 is already 1, the
 * fault path. Afterwards it fetches the peer vspace (FUN_004b1fac) and repeats
 * the same re-materialisation walk on it, returning that peer; if the rebuild
 * was flagged done (bit 0 of vas+0x1d1), it returns the rebuild target's +0x10
 * word instead. Aborts (VAS 005af2ad/005af3a2/005aed68) on any inconsistency.
 * Confidence: high (structure mirrors rebuild_inner exactly).
 */
static uint64_t sk_vas_rebuild(uint64_t vas, uint64_t kind)
{
    uint64_t canary = SK_VAS_CANARY;
    uint64_t peer, cur, eptr, next, slot, backing, frame, base_va, last;
    uint64_t off, idx, target_va, span, rel, desc, err, sp_start, sp_end, size;
    uint64_t new_end;
    uint64_t msg[5], out[2];
    bool changed, made_progress;
    int r;
    cl4_result_t cres;

    if (kind != 0x65b5c8)
        sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5af2ad);
    if ((*(uint8_t *)(vas + 9) & 1) == 0) {
        sk_vas_fault11();                        /* FUN_004b2034 */
    } else if (*(uint64_t *)(vas + 400) != 0) {  /* rebuild target present */
        if (sk_lock_acquire(vas + 0x40) != 0)    /* FUN_00118164 */
            goto ab_5aed68;
        if ((*(uint8_t *)(vas + 0x1d1) & 1) == 0) {   /* not flagged done */
            if (*(uint8_t *)(vas + 0x1d0) == 1) {
                sk_vas_fault13();                /* FUN_004b1fd4 */
            } else {
                sk_vas_rebuild_inner(vas);       /* FUN_00031bf4 */
                if ((*(uint8_t *)(vas + 0x1d1) & 1) != 0) goto done_31af4;
            }
            peer = sk_vas_rebuild_peer();        /* FUN_004b1fac — returns peer vspace */
            if ((*(uint8_t *)(peer + 9) & 1) == 0) {
                sk_vas_fault12();                /* FUN_004b2084 */
            ab_5aed68:
                sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5aed68);
            }
            if ((*(uint8_t *)(peer + 0x1d0) & 1) == 0) {  /* peer not rebuilding */
                changed = false;
                *(uint8_t *)(peer + 0x1d0) = 1;
                cur = peer + 0x148;              /* red-black tree head */
                do {
                    if (*(uint64_t *)(cur + 8) == 0) {
                        msg[0] = sk_l4_err_word0;
                        msg[1] = sk_l4_err_word1;
                        msg[2] = sk_l4_err_word2;
                        msg[3] = sk_l4_err_word3;
                        msg[4] = 0;
                        out[0] = 0; out[1] = 0;
                        if (sk_lock_release(peer + 0x40) != 0)
                            goto ab_5aed68;
                        /* GENTER: supervisor span-backing allocation. */
                        err = sk_supervisor_alloc_span(peer, 0x1800, msg, out, 0, msg);
                        err &= 0xff;
                        if (err != 0) {
                            if (sk_err_in_range(err))
                                sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5afade);
                            goto trap_32460;
                        }
                        if (out[1] != 0x65b648)
                            sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5afb3f);
                        if (sk_lock_acquire(peer + 0x40) != 0)
                            goto ab_5aed68;
                        if (*(uint64_t *)(cur + 8) != 0)
                            sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5afba3);
                        *(uint64_t *)(cur + 8) = out[0];
                        changed = true;
                    }
                    off = 0;
                    idx = 0;
                    eptr = cur + 9;
                    made_progress = changed;
                    do {
                        if ((uintptr_t)cur + 0x80 < (uintptr_t)eptr + 8 ||
                            (uintptr_t)eptr + 8 < (uintptr_t)eptr)
                            goto trap_32460;
                        slot = *(uint64_t *)eptr;
                        if (slot == 0) break;
                        if (*(uint64_t *)(slot + 0x10) == 0) {   /* span not yet mapped */
                            if ((*(uint8_t *)(peer + 9) & 1) == 0) {
                                sk_vas_fault16();
                            ab_5afcfb:
                                sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5afcfb);
                            }
                            backing = *(uint64_t *)(cur + 8);
                            if (backing == 0)
                                sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5afc10);
                            last = *(uint64_t *)(peer + 0x1c8);
                            if (last != 0) {
                                if (*(uint64_t *)(last + 0x10) == 0)
                                    sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5afc68);
                                if (*(uint64_t *)(*(uint64_t *)(last + 0x18) + 8) != 0)
                                    goto ab_5afcfb;
                            }
                            frame = *(uint64_t *)(slot + 0x18);
                            if (frame == 0 || (frame & 0x3fff) != 0)
                                sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5afdb8);
                            base_va = *(uint64_t *)(backing + 8);
                            if (sk_lock_release(peer + 0x40) != 0)
                                goto ab_5aed68;
                            if ((uintptr_t)backing + 0x90 < (uintptr_t)(backing + 0x80))
                                goto trap_32460;
                            if (sk_lock_acquire(backing + 0x80) != 0)
                                goto ab_5aed68;
                            msg[0] = 0; msg[1] = 0; msg[2] = 0; msg[3] = 0; msg[4] = 0;
                            sk_vas_cap_desc_build(msg,
                                                  *(uint64_t *)(backing + 0x78),
                                                  ((off + (base_va - *(uint64_t *)(peer + 0x88))) >> 0xe) + 1);
                            desc = msg[0];
                            *(uint64_t *)(backing + 0x78) = msg[4];
                            r = sk_lock_release(backing + 0x80);
                            if (desc == 0) {
                                if (r != 0) goto ab_5aed68;
                                if (sk_err_in_range(msg[2] & 0xff))
                                    sk_vas_abort("spanmap could not alloc a cap");
                                goto trap_32460;
                            }
                            if (r != 0) goto ab_5aed68;
                            target_va = off + base_va;
                            span = sk_spanmap_lookup(peer + 0x60, 1, target_va);
                            rel = sk_spanmap_release(peer + 0x60, span);
                            if ((rel & 1) == 0)
                                sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5afecd);
                            /* GENTER: map the frame into the root vspace. */
                            err = sk_supervisor_map_span((uint64_t)(uintptr_t)&sk_vspace_root_obj,
                                                         frame, 0, desc);
                            err &= 0xff;
                            if (err != 0) {
                                if (sk_err_in_range(err))
                                    sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5aff2f);
                                goto trap_32460;
                            }
                            cres = sk_vas_span_map_op2(peer + 0x60, span, desc, target_va, 0, 0);
                            err = cres.lo;
                            if ((err & 0xff) == 4) {
                                err = sk_vas_populate_level_nonself(peer + 0x60, target_va);
                                if ((err & 1) == 0)
                                    sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5affa4);
                                cres = sk_vas_span_map_op2(peer + 0x60, span, desc, target_va, 0, 0);
                                err = cres.lo;
                            }
                            if ((err & 0xff) != 0) {
                                sk_l4_error_word((void **)out, 0);
                                sk_vas_fault17(0xeb1a02bf914012ba);
                                sk_l4_error_word((void **)out, (uint8_t)(err & 0xff));
                                sk_vas_abort("Unexpected L4 Error: %s (%zu, err)");
                            }
                            if (sk_lock_acquire(peer + 0x40) != 0)
                                goto ab_5aed68;
                            if (*(uint64_t *)(slot + 0x10) != 0)
                                sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5b0136);
                            sp_start = *(uint64_t *)(slot + 0x18);
                            sp_end = *(uint64_t *)(slot + 0x20);
                            if (0x3fff < (uint64_t)(sp_end - sp_start))
                                sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5b0195);
                            size = *(uint64_t *)(slot + 8);
                            if (0x4000 < (uint64_t)((size - sp_start) + 0x3fe0))
                                sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5b01eb);
                            new_end = sp_end + off + (base_va - sp_start);
                            *(uint8_t *)(sp_start + 2) = 1;
                            if (new_end + 1 < new_end)
                                goto trap_32460;
                            *(uint64_t *)sp_start = new_end;
                            *(uint16_t *)(sp_start + 0x11) = 0x101;
                            *(uint64_t *)sp_end = off + ((base_va + size) - sp_start);
                            if (last != 0)
                                *(uint64_t *)(*(uint64_t *)(last + 0x18) + 8) = target_va;
                            *(uint64_t *)(peer + 0x1c8) = slot;
                            *(uint64_t *)(slot + 0x10) = target_va;
                            made_progress = true;
                        }
                        idx++; off += 0x4000; eptr++;
                    } while (off != 0x1c000);
                    next = *(uint64_t *)cur;
                    cur = (next != 0) ? next : (peer + 0x148);
                    changed = (next != 0) && made_progress;
                } while (next != 0 || made_progress);
                if ((*(uint8_t *)(peer + 0x1d0) & 1) == 0)
                    sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5afa56);
                *(uint16_t *)(peer + 0x1d0) = 0x100;
            }
            if (canary == SK_VAS_CANARY) return peer;
            sk_stack_chk_fail();                 /* FUN_0011d7e8 */
        }
done_31af4:
        if (*(uint64_t *)(*(uint64_t *)(vas + 400) + 0x10) == 0) {
            sk_vas_fault15();                    /* FUN_004b200c */
        } else {
            if (sk_lock_release(vas + 0x40) == 0)   /* FUN_00118194 */
                return *(uint64_t *)(*(uint64_t *)(vas + 400) + 0x10);
        }
        goto ab_5aed68;
    }
    sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5af3a2);

trap_32460:
    /* SoftwareBreakpoint(0x5519, 0x32460) — does not return */
    SK_ASRT_PANIC(0x32460);
}
