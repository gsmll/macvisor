/* Recreated from the cL4 Secure Kernel VAS-subsystem slice (region
 * 0x0002ee90-0x00038184). Ground truth: Ghidra FUN_ names + addresses. All
 * names are estimates unless string/header matched. */
#include "sk_slice_06_shared.h"

/* Cross-slice fault/panic helpers (0x4b... family), not declared in the
 * shared header — local externs, ground-truth address in comment. */
extern void sk_vas_fault20(void);                 /* FUN_004b2368 */
extern void sk_vas_fault21(void);                 /* FUN_004b23a0 */
extern uint64_t sk_vas_fault22(void);             /* FUN_004b2584 */
extern void sk_vas_fault23(void);                 /* FUN_004b25f4 */
extern void sk_vas_fault24(void);                 /* FUN_004b262c */
extern void sk_vas_fault25(void);                 /* FUN_004b269c */
extern void sk_vas_fault26(void);                 /* FUN_004b25bc */
extern void sk_vas_fault27(void);                 /* FUN_004b2664 */
extern sk_vas_lock_tok_t sk_vas_fault_lock(void); /* FUN_004b26d4 */

/* VAS-check globals (data region). */
extern uint64_t sk_vas_check_head;                /* DAT_0064cb20 (list head) */
extern uint64_t sk_vas_root_obj;                  /* DAT_006ad2c0 (root node) */

/*--------------------------------------------------------------------*/
/* FUN_0003456c @ 0x0003456c  (est. sk_vas_reserve)
 * Ghidra: void FUN_0003456c(ulong param_1, undefined1 *param_2)
 * Reserves a 0x10000 region out of a VAS meta-descriptor (param_2) within
 * the pool node (param_1). Requires the VAS lock to be held by the current
 * CPU. If the region is not yet committed (meta[1] != 1): validates the
 * current cursor (+0x20) against the low bound (+8, abort 005b0c27), or for
 * the indirect layout checks the mapped-region descriptor (+0x28) and maps a
 * fresh 0x10000 heap region (sk_vas_heap_alloc_span) when the cursor equals
 * the mapped base. On success marks the region committed (meta[1]=1) and
 * stores the next cursor as base-0x4000. Aborts (005b090a/005b0ca4) on
 * lock/layout violations. Used by FUN_00034468.
 * Confidence: medium (structural).
 * Notes: Bounds assertions render as SoftwareBreakpoint(0x5519,0x34634).
 *   Decompiler's FUN_00033c60 = sk_vas_heap_alloc_span. */
static void sk_vas_reserve(uint64_t vas, uint8_t *meta)
{
    uint64_t u;
    uint64_t u1;

    if (vas + 0x30 < vas)
        SK_ASRT_PANIC(0x34634);
    if ((sk_vas_locked(vas) & 1) == 0)            /* FUN_00034ba4 */
        sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5b090a);
    if (meta[1] != 1) {
        u = *(uint64_t *)(meta + 0x20);
        if ((meta[0x30] & 1) == 0) {
            if (u <= *(uint64_t *)(meta + 8))
                sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5b0c27);
        } else {
            u1 = *(uint64_t *)(*(uint64_t *)(meta + 0x28) + 8);
            if (*(uint64_t *)(*(uint64_t *)(meta + 0x28) + 0x10) < u - u1)
                goto fail_34660;
            if (u == u1) {
                u = sk_vas_heap_alloc_span(meta[0], 0, 0x10000, meta[0x18]); /* FUN_00033c60 */
                if (u == 0)
                    return;
                *(uint64_t *)(meta + 0x28) = u;
                if (u + 0x20 < u)
                    SK_ASRT_PANIC(0x34634);
                u = *(int64_t *)(u + 0x10) + *(int64_t *)(u + 8);
            }
        }
        meta[1] = 1;
        *(uint64_t *)(meta + 0x20) = u - 0x4000;
        return;
    }
    sk_vas_fault20();                             /* FUN_004b2368 */
fail_34660:
    sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5b0ca4);
}

/*--------------------------------------------------------------------*/
/* FUN_000346c0 @ 0x000346c0  (est. sk_vas_unreserve)
 * Ghidra: void FUN_000346c0(ulong param_1, long param_2, long param_3)
 * Commits / releases a reserved region of a VAS meta-descriptor (meta).
 * Requires the VAS lock. If the region at meta is committed (meta[1] bit 0)
 * and the base param_3 equals the region's current cursor (+0x20), validates
 * it against the mapped-region size (+0x28, abort 005b0e13 on overflow) and
 * clears the committed flag (meta[1]=0). Aborts (005b0daa/005b090a) on
 * mismatch, or faults (FUN_004b23a0) if not committed. Used by
 * FUN_00033f1c/34468.
 * Confidence: medium (structural).
 * Notes: Bounds assertion renders as SoftwareBreakpoint(0x5519,0x34740). */
static void sk_vas_unreserve(uint64_t vas, uint64_t meta, uint64_t addr)
{
    int64_t r;

    if (vas + 0x30 < vas)
        SK_ASRT_PANIC(0x34740);
    if ((sk_vas_locked(vas) & 1) != 0) {          /* FUN_00034ba4 */
        if ((*(uint8_t *)(meta + 1) & 1) == 0) {
            sk_vas_fault21();                     /* FUN_004b23a0 */
        } else if (addr == *(uint64_t *)(meta + 0x20)) {
            r = *(int64_t *)(meta + 0x28);
            if (r != 0) {
                if (*(uint64_t *)(r + 0x10) <= (uint64_t)(addr - *(int64_t *)(r + 8)))
                    sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5b0e13);
            }
            *(uint8_t *)(meta + 1) = 0;
            return;
        }
        sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5b0daa);
    }
    sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5b090a);
}

/*--------------------------------------------------------------------*/
/* FUN_000347c4 @ 0x000347c4  (est. sk_capslot_alloc)
 * Ghidra: void FUN_000347c4(void)
 * Allocates a capsot pool node and initialises its free-list at offset 0x120
 * via sk_pool_alloc; the result must fit +0x40. Used by FUN_00035bac/36dec.
 * Confidence: medium (trivial wrapper).
 * Notes: Bounds assertion renders as SoftwareBreakpoint(0x5519,0x3481c). */
static void sk_capslot_alloc(void)
{
    uint64_t node;
    uint64_t out;

    sk_vspace_alloc(&out, 4, 0xd);                /* FUN_0005acac; &out = 0x6af180 */
    node = out;
    if (node <= node + 0x3e0 && node + 0x120 <= node + 0x158 &&
        (node = (uint64_t)sk_pool_alloc(node, (uint16_t *)(node + 0x120), 1),
         node <= node + 0x40))
        return;
    SK_ASRT_PANIC(0x3481c);
}

/*--------------------------------------------------------------------*/
/* FUN_0003481c @ 0x0003481c  (est. sk_capslot_free)
 * Ghidra: void FUN_0003481c(undefined8 param_1)
 * Returns a capsot element (cap) to the free-list at offset 0x120 via
 * sk_pool_free. Used by FUN_00035bac/3611c/36920/373a4/37e9c.
 * Confidence: medium (trivial wrapper).
 * Notes: Bounds assertion renders as SoftwareBreakpoint(0x5519,0x34874). */
static void sk_capslot_free(uint64_t cap)
{
    uint64_t node;
    uint64_t out;

    sk_vspace_alloc(&out, 4, 0xd);                /* FUN_0005acac; &out = 0x6af180 */
    node = out;
    if (node <= node + 0x3e0 && node + 0x120 <= node + 0x158) {
        sk_pool_free(node, (uint16_t *)(node + 0x120), &cap); /* FUN_000331a0 */
        return;
    }
    SK_ASRT_PANIC(0x34874);
}

/*--------------------------------------------------------------------*/
/* FUN_00034874 @ 0x00034874  (est. sk_vas_abort2)
 * Ghidra: void FUN_00034874(undefined8 param_1)
 * Non-returning VAS abort wrapper (string at 005b0352). Referenced by
 * FUN_004b2128/21c4.
 * Confidence: high (trivial abort wrapper). */
static void sk_vas_abort2(uint64_t a) __attribute__((noreturn));
static void sk_vas_abort2(uint64_t a)
{
    (void)a;
    sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5b0352);
    __builtin_unreachable();
}

/*--------------------------------------------------------------------*/
/* FUN_00034888 @ 0x00034888  (est. sk_vas_check_init)
 * Ghidra: bool FUN_00034888(void)
 * One-time initialisation of the VAS object-table node. Allocates the boot
 * node (sk_vspace_lookup, tag 8); if none is currently in use (returns 0),
 * initialises the shared list head (DAT_0064cb20) and runs sk_vas_check_grow
 * (FUN_000348d0) to size the table. Returns true iff the node was freshly
 * allocated. Used by FUN_00034970.
 * Confidence: medium (structural; DAT_0064cb20). */
static bool sk_vas_check_init(void)
{
    uint64_t node;

    node = sk_vspace_lookup(4, 8);                /* FUN_0005baac */
    if (node == 0) {
        sk_list_init(&sk_vas_check_head);         /* FUN_0005ba5c */
        sk_vas_check_grow();                      /* FUN_000348d0 */
    }
    return node == 0;
}

/*--------------------------------------------------------------------*/
/* FUN_000348d0 @ 0x000348d0  (est. sk_vas_check_grow)
 * Ghidra: void FUN_000348d0(void)
 * Computes the VAS object-table capacity. Allocates the table node (0x6af188,
 * tag 8), reads the element count at +0x48, and if the count is small enough
 * (bit 17 clear and count*0x8000 < 0xfffe0000) sets the table boundary at
 * +0x44 to count*0x8000+0x20000. Otherwise it records the overflow node
 * pointer in the global DAT_006ad2c0 (aborting if already set, VAS 005b0e73).
 * Used by FUN_00034888/34a5c/34ad0.
 * Confidence: medium (structural; DAT_006ad2c0). */
static void sk_vas_check_grow(void)
{
    uint64_t node;
    uint32_t cnt;
    uint64_t u;
    uint64_t out;

    sk_vspace_alloc(&out, 4, 8);                  /* FUN_0005acac; &out = 0x6af188 */
    node = out;
    cnt = *(uint32_t *)(node + 0x48) * 0x8000;
    if (*(uint32_t *)(node + 0x48) >> 0x11 == 0 && cnt < 0xfffe0000) {
        *(uint32_t *)(node + 0x44) = cnt + 0x20000;
        return;
    }
    u = sk_vas_fault22();                         /* FUN_004b2584 */
    if (sk_vas_root_obj == 0) {
        sk_vas_root_obj = u;
        return;
    }
    sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5b0e73);
}

/*--------------------------------------------------------------------*/
/* FUN_00034920 @ 0x00034920  (est. sk_vas_set_root)
 * Ghidra: void FUN_00034920(undefined8 param_1)
 * Registers the VAS object-table node pointer in the global DAT_006ad2c0;
 * aborts (VAS 005b0e73) if it is already registered. Used by FUN_00031868.
 * Confidence: high (structural; DAT_006ad2c0). */
static void sk_vas_set_root(uint64_t v)
{
    if (sk_vas_root_obj == 0) {
        sk_vas_root_obj = v;
        return;
    }
    sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5b0e73);
}

/*--------------------------------------------------------------------*/
/* FUN_00034970 @ 0x00034970  (est. sk_vas_obj_init)
 * Ghidra: long * FUN_00034970(long param_1, long param_2, long *param_3)
 * Initialises the VAS object table. Runs sk_vas_check_init (FUN_00034888)
 * and allocates the table node (0x6af188, tag 8). If the node was not freshly
 * booted but already marked initialised (bit 0 at node+8) and carries a valid
 * method triple, it returns it. Otherwise, if freshly booted and
 * uninitialised, it stores the method table (a=methods, b=table base,
 * c=object list) into the node and marks it initialised (node+8 bit 0). On
 * any inconsistency it faults (FUN_004b25bc/25f4/262c/2664/269c) and returns
 * the stored object pointer at (node+0x10). Used by FUN_00031868.
 * Confidence: medium (structural init guard). */
static uint64_t *sk_vas_obj_init(uint64_t a, uint64_t b, uint64_t *c)
{
    uint64_t fresh;
    uint64_t *node;
    uint64_t *obj;
    uint64_t out;

    fresh = sk_vas_check_init();                  /* FUN_00034888 */
    sk_vspace_alloc(&out, 4, 8);                  /* FUN_0005acac; &out = 0x6af188 */
    node = (uint64_t *)out;
    if ((fresh & 1) == 0) {
        /* Table already initialised: if the node is marked and carries a
         * valid method triple, hand back the existing node. */
        if ((*((uint8_t *)node + 8) & 1) != 0) {
            obj = (uint64_t *)*node;
            if (obj != NULL && obj[0] != 0 && obj[1] != 0 && obj[2] != 0)
                return node;
            sk_vas_fault23();                     /* FUN_004b25f4 */
            goto fault;
        }
    } else {
        /* Fresh table: populate the node from the caller's triple. */
        if (*((uint8_t *)node + 8) == 0) {
            if (a == 0)
                goto fault2;
            if (c != NULL && c[0] != 0 && c[1] != 0) {
                node[2] = a;
                node[3] = b;
                *node = (uint64_t)c;
                *((uint8_t *)node + 8) = 1;
                return node;
            }
fault:
            sk_vas_fault24();                     /* FUN_004b262c */
        }
        sk_vas_fault25();                         /* FUN_004b269c */
    }
    sk_vas_fault26();                             /* FUN_004b25bc */
fault2:
    sk_vas_fault27();                             /* FUN_004b2664 */
    {
        uint64_t out2;
        sk_vspace_alloc(&out2, 4, 8);             /* FUN_0005acac; &out = 0x6af188 */
        return (uint64_t *)*(uint64_t *)(out2 + 0x10);
    }
}

/*--------------------------------------------------------------------*/
/* FUN_00034a2c @ 0x00034a2c  (est. sk_vas_obj_root)
 * Ghidra: undefined1 [16] FUN_00034a2c(void)
 * Returns the 16-byte lock-token stored at offset +0x10 of the VAS
 * object-table node (0x6af188, tag 8). Used to hand back the table's root
 * lock/counter pair.
 * Confidence: high (trivial accessor). */
static sk_vas_lock_tok_t sk_vas_obj_root(void)
{
    uint64_t out;

    sk_vspace_alloc(&out, 4, 8);                  /* FUN_0005acac; &out = 0x6af188 */
    return *(sk_vas_lock_tok_t *)(out + 0x10);
}

/*--------------------------------------------------------------------*/
/* FUN_00034a5c @ 0x00034a5c  (est. sk_vas_check_inc)
 * Ghidra: void FUN_00034a5c(void)
 * Increments the VAS object-table element count at +0x48 (capping at 0xffff)
 * and re-sizes the table boundary (sk_vas_check_grow). Aborts (VAS 005b11ec)
 * if the count would exceed 0xffff.
 * Confidence: high (trivial counter bump). */
static void sk_vas_check_inc(void)
{
    uint64_t node;
    uint64_t out;

    sk_vspace_alloc(&out, 4, 8);                  /* FUN_0005acac; &out = 0x6af188 */
    node = out;
    if (*(uint32_t *)(node + 0x48) < 0xffff) {
        *(uint32_t *)(node + 0x48) += 1;
        sk_vas_check_grow();                      /* FUN_000348d0 */
        return;
    }
    sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5b11ec);
}

/*--------------------------------------------------------------------*/
/* FUN_00034ad0 @ 0x00034ad0  (est. sk_vas_check_dec)
 * Ghidra: void FUN_00034ad0(void)
 * Decrements the VAS object-table element count at +0x48. When the count is
 * non-zero it simply decrements and re-sizes (sk_vas_check_grow). When it
 * reaches zero it obtains a fresh lock token (FUN_004b26d4), initialises a
 * mutex at the token address (sk_mutex_init) and stamps the lock fields
 * (+0x10=0, +0x18=0x100, +0x20=token hi, +0x28=8). Aborts (VAS 005aed68) on
 * mutex-init failure; bounds assertion renders as SoftwareBreakpoint
 * (0x5519,0x34b70).
 * Confidence: medium (structural; counter underflow path). */
static void sk_vas_check_dec(void)
{
    sk_vas_lock_tok_t tok;
    uint64_t lock;
    uint64_t out;
    int r;

    sk_vspace_alloc(&out, 4, 0);                  /* FUN_0005acac; &out = 0x6af188 (flags omitted) */
    lock = out;
    if (*(int32_t *)(lock + 0x48) != 0) {
        *(int32_t *)(lock + 0x48) -= 1;
        sk_vas_check_grow();                      /* FUN_000348d0 */
        return;
    }
    tok = sk_vas_fault_lock();                    /* FUN_004b26d4 */
    lock = tok.flags;
    if (lock <= lock + 0x10) {
        r = sk_mutex_init((void *)lock, 0);       /* FUN_00118148 */
        if (r == 0) {
            *(uint64_t *)(lock + 0x10) = 0;
            *(uint64_t *)(lock + 0x18) = 0x100;
            *(uint64_t *)(lock + 0x20) = tok.counter;
            *(uint64_t *)(lock + 0x28) = 8;
            return;
        }
        sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5aed68);
    }
    SK_ASRT_PANIC(0x34b70);
}

/*--------------------------------------------------------------------*/
/* FUN_00034b10 @ 0x00034b10  (est. sk_vas_lock_init)
 * Ghidra: void FUN_00034b10(ulong param_1, undefined8 param_2, undefined8 param_3)
 * Initialises a VAS lock at the given address: runs sk_mutex_init(lock,0)
 * and stamps the lock fields (+0x10=0, +0x18=0x100, +0x20=a2, +0x28=a3).
 * Aborts (VAS 005aed68) on mutex-init failure; bounds assertion renders as
 * SoftwareBreakpoint (0x5519,0x34b70).
 * Confidence: high (trivial lock setup). */
static void sk_vas_lock_init(uint64_t lock, uint64_t a2, uint64_t a3)
{
    int r;

    if (lock + 0x10 < lock)
        SK_ASRT_PANIC(0x34b70);
    r = sk_mutex_init((void *)lock, 0);           /* FUN_00118148 */
    if (r == 0) {
        *(uint64_t *)(lock + 0x10) = 0;
        *(uint64_t *)(lock + 0x18) = 0x100;
        *(uint64_t *)(lock + 0x20) = a2;
        *(uint64_t *)(lock + 0x28) = a3;
        return;
    }
    sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5aed68);
}

/*--------------------------------------------------------------------*/
/* FUN_00034ba4 @ 0x00034ba4  (est. sk_vas_locked)
 * Ghidra: bool FUN_00034ba4(long param_1)
 * Reports whether the VAS lock at param_1 is currently owned by the running
 * CPU: true iff sk_percpu_base() equals the recorded owner (+0x10).
 * Confidence: high (trivial ownership probe). */
static bool sk_vas_locked(uint64_t lock)
{
    uint64_t pcpu;

    pcpu = sk_percpu_base();                      /* thunk_FUN_00060524 */
    return sk_obj_cmp(pcpu, *(uint64_t *)(lock + 0x10)) != 0; /* thunk_FUN_000539c0 */
}

/*--------------------------------------------------------------------*/
/* FUN_00034bd8 @ 0x00034bd8  (est. sk_vas_lock_acquire)
 * Ghidra: undefined1 [16] FUN_00034bd8(long param_1)
 * Acquires the VAS lock at param_1. If not already owned by the current CPU,
 * takes the global VM lock (FUN_00118164) to serialise acquisition, verifies
 * the owner slot is clear and the depth byte is 0, then records ownership
 * (+0x10=percpu) and bumps the counter by 0x101; returns {flags=0,
 * counter=old+0x100}. If already owned (recursive re-entry), verifies the
 * depth byte is neither 0 nor 0xff, bumps the counter by 1, and returns
 * {flags=1, counter=old}. Aborts (005aed68/005b144d/005b14d8/005b13b9/
 * 005b133b) on any inconsistency.
 * Confidence: high (lock acquisition protocol). */
static sk_vas_lock_tok_t sk_vas_lock_acquire(uint64_t lock)
{
    sk_vas_lock_tok_t tok;
    uint64_t counter;
    uint64_t pcpu;
    int r;

    pcpu = sk_percpu_base();                      /* thunk_FUN_00060524 */
    if (sk_obj_cmp(pcpu, *(uint64_t *)(lock + 0x10)) == 0) {
        /* Not owned by this CPU: take the global VM lock, then claim it. */
        r = sk_vm_lock_acquire();                 /* FUN_00118164 */
        if (r != 0)
            sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5aed68);
        if (*(uint64_t *)(lock + 0x10) != 0)
            sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5b144d);
        counter = *(uint64_t *)(lock + 0x18);
        if ((counter & 0xff) != 0)
            sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5b14d8);
        pcpu = sk_percpu_base();
        tok.flags = 0;                            /* fresh ownership */
        *(uint64_t *)(lock + 0x10) = pcpu;
        *(uint64_t *)(lock + 0x18) = counter + 0x101; /* stored = old + 0x101 */
        counter += 0x100;                         /* returned = old + 0x100 */
    } else {
        /* Recursive re-entry on the same CPU: bump only the depth. */
        counter = *(uint64_t *)(lock + 0x18);
        if ((counter & 0xff) == 0xff)
            sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5b13b9);
        if ((counter & 0xff) == 0)
            sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5b133b);
        *(uint64_t *)(lock + 0x18) = counter + 1;
        tok.flags = 1;                            /* recursive */
    }
    tok.counter = counter;
    return tok;
}

/*--------------------------------------------------------------------*/
/* FUN_00034d5c @ 0x00034d5c  (est. sk_vas_lock_release)
 * Ghidra: void FUN_00034d5c(long param_1, byte param_2, ulong param_3)
 * Releases the VAS lock at lock. Verifies the lock is owned by the current
 * CPU, that counter+1 equals the stored counter (+0x18), and that the depth
 * byte's non-zero state matches flags bit 0. For a final release (flags&1==0)
 * it invokes the unlock callback (+0x20 with arg +0x28), re-verifies, clears
 * ownership (+0x10=0), restores the counter to the passed value, and releases
 * the global VM lock (FUN_00118194). For a recursive release (flags&1!=0) it
 * simply stores the passed counter. Aborts (005b1554/005b15c4/005b165f/
 * 005aed68) on any inconsistency.
 * Confidence: high (lock release protocol). */
static void sk_vas_lock_release(uint64_t lock, uint8_t flags, uint64_t counter)
{
    void (*fn)(uint64_t);
    uint64_t pcpu;
    int r;

    pcpu = sk_percpu_base();                      /* thunk_FUN_00060524 */
    if (sk_obj_cmp(pcpu, *(uint64_t *)(lock + 0x10)) == 0)
        sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5b1554);
    if (counter + 1 != *(uint64_t *)(lock + 0x18))
        sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5b15c4);
    if (((counter & 0xff) != 0) != ((flags & 1) != 0))
        sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5b165f);
    if ((flags & 1) == 0) {
        /* Final release: run the unlock callback before dropping the lock. */
        fn = *(void (**)(uint64_t))(lock + 0x20);
        fn(*(uint64_t *)(lock + 0x28));
        pcpu = sk_percpu_base();
        if (sk_obj_cmp(pcpu, *(uint64_t *)(lock + 0x10)) == 0)
            sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5b1554);
        if (counter + 1 != *(uint64_t *)(lock + 0x18))
            sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5b15c4);
        if ((counter & 0xff) != 0)
            sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5b165f);
        *(uint64_t *)(lock + 0x10) = 0;
        *(uint64_t *)(lock + 0x18) = counter;
        r = sk_vm_lock_release();                 /* FUN_00118194 */
        if (r != 0)
            sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5aed68);
    } else {
        *(uint64_t *)(lock + 0x18) = counter;
    }
}
