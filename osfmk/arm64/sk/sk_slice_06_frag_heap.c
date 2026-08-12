/* sk_slice_06_frag_heap.c — VAS heap / region allocator (0x33780-0x34468).
 *
 * These functions implement the global VAS heap: the fixed node at 0x6af180
 * (tag 0xd) whose fields are laid out in sk_vas_frag_heap_node_t below, the
 * two bootstrap region descriptors (0x6af020 / 0x6af0d0), the free-list and
 * the per-pool element allocators. Cross-function helpers that the shared
 * header declares with an incompatible signature (void where the decompile
 * returns a value, or a different arity) are reached through local extern
 * aliases so the bodies stay faithful to the decompile.
 */
#include "sk_slice_06_shared.h"

/* ---- Local model of the fixed VAS heap node at 0x6af180. ---- */
typedef struct {
    uint8_t  pad00[0x40];        /* +0x00 */
    uint8_t  h2_kind;            /* +0x40 */
    uint8_t  h2_flags;           /* +0x41 */
    uint8_t  pad42[6];           /* +0x42 */
    uint64_t h2_base;            /* +0x48 */
    uint64_t h2_end;             /* +0x50 */
    uint8_t  h2_meta;            /* +0x58 */
    uint8_t  pad59[0xf];         /* +0x59 */
    uint64_t h2_region;          /* +0x68 */
    uint8_t  h2_active;          /* +0x70 */
    uint8_t  pad71[7];
    uint8_t  h0_kind;            /* +0x78 */
    uint8_t  h0_flags;           /* +0x79 */
    uint8_t  pad7a[6];
    uint64_t h0_base;            /* +0x80 */
    uint64_t h0_end;             /* +0x88 */
    uint8_t  h0_meta;            /* +0x90 */
    uint8_t  pad91[7];
    uint64_t h0_next;            /* +0x98 */
    uint64_t h0_region;          /* +0xa0 */
    uint8_t  h0_active;          /* +0xa8 */
    uint8_t  pada9[7];
    uint64_t region;             /* +0xb0 */
    uint8_t  padb8[8];
    uint8_t  active;             /* +0xc0 */
    uint8_t  guard;              /* +0xc1 */
    uint8_t  slot_in;            /* +0xc2 */
    uint8_t  padc3[0xd];
    uint64_t free_head;          /* +0xd0 */
    uint64_t free_tail;          /* +0xd8 */
    uint64_t free_ptr;           /* +0xe0 */
    uint8_t  reserve_pool[0x38]; /* +0xe8 */
    uint8_t  pad120[0xe0];       /* +0x120 */
    uint8_t  pool0[0x38];        /* +0x200 */
    uint8_t  pool1[0x38];        /* +0x238 */
    uint8_t  pad270[0x150];      /* +0x270 */
    uint64_t direct[3];          /* +0x3c0 */
    uint8_t  count;              /* +0x3d8 */
    uint8_t  min;                /* +0x3d9 */
    uint8_t  pad3da[6];
    uint8_t  end;                /* +0x3e0 */
} sk_vas_frag_heap_node_t;

/* ---- Global VAS registry / bootstrap state (Ghidra data addresses). ---- */
static void     *heap_registry_head;    /* DAT_0064c6d0 (registry list head) */
static uint64_t  heap_0064c728;         /* DAT_0064c728 = DAT_004bc3b8 */
static uint64_t  heap_004bc3b8;         /* DAT_004bc3b8 (bootstrap constant) */
static uint64_t  heap_0064c768;         /* DAT_0064c768 (region-0 base const) */
static uint64_t  heap_0064c770;         /* DAT_0064c770 */
static uint64_t  heap_0064c778;         /* DAT_0064c778 */
static uint64_t  heap_0064c780;         /* DAT_0064c780 */
static uint64_t  heap_0064c730;         /* DAT_0064c730 (region-1 base const) */
static uint64_t  heap_0064c738;         /* DAT_0064c738 */
static uint64_t  heap_0064c740[2];      /* DAT_0064c740 (16-byte common) */
static uint64_t  heap_bss_lock;         /* s___bss_0064c6f0 (shared VAS lock) */
static uint64_t  heap_registry_table[4];/* DAT_0064cab0 (registry slot table) */
static uint8_t   heap_registry_count;   /* DAT_0064cac8 (low byte) */
static uint8_t   heap_registry_overflow;/* DAT_0064cac9 */
static uint8_t   heap_region0[0xb0];    /* DAT_006af020 (bootstrap region 0) */
static uint8_t   heap_region1[0xb0];    /* DAT_006af0d0 (bootstrap region 1) */
static uint64_t *heap_region0_ptr;      /* DAT_0064c790 */
static uint64_t *heap_region1_ptr;      /* DAT_0064c758 */
static uint8_t   heap_clean;            /* *(extraout_x1 + 0x38) byte flag */

/* Quad-return of the direct-refill helper FUN_004b233c (Ghidra renders the
 * extra x8/x9/x10 return registers as extraout_*). */
typedef struct {
    uint64_t   node;   /* x0: node to run count/guard ops on */
    uint64_t   value;  /* x8: allocated element */
    uint64_t  *slot;   /* x9 */
    uint64_t  *count;  /* x10 */
} sk_vas_refill_t;

/*--------------------------------------------------------------------*/
/* FUN_00033780 @ 0x00033780  (est. sk_vas_registry_init)
 * Ghidra: void FUN_00033780(void)
 * One-time initialisation of the global VAS registry and its bootstrap region
 * descriptors. Returns immediately if a type-4/flags-0xd VAS object already
 * exists. Otherwise it stamps the two bootstrap regions (0x6af020/0x6af0d0)
 * with the fixed kernel/heap bounds, initialises the shared VAS lock, then
 * walks the 4-entry registry slot table filling each empty slot from the
 * per-CPU VAS stack (FUN_00043eac). When that stack is exhausted it switches
 * to the current node (FUN_004b2128) and, holding the VAS lock, fills its
 * 3-slot direct ring (+0x3c0) and its 13 per-region pools (each 0x38 bytes
 * from +0xe8) with freshly allocated slots.
 * Confidence: low (heavy global stamping + SoftwareBreakpoint 0x5519 at
 *   0x33978/0x33ae4; several opaque fault helpers).
 * Notes: DAT_0064c728=0x4bc3b8, DAT_0064c6d0 list head, DAT_0064cab0 slot
 *   table, DAT_0064cac8/69 counters, DAT_006af020/0xd0 region descriptors,
 *   DAT_0064c758/790 region pointers, s___bss_0064c6f0 lock. */
static void sk_vas_registry_init(void)
{
    extern uint64_t sk_vas_stack_pop(void);              /* FUN_00043eac */
    extern sk_vas_frag_heap_node_t *sk_vas_current(void);/* FUN_004b2128 */
    extern void *sk_vas_registry_peek(void);             /* FUN_004b21ec */
    extern void sk_vas_abort_chain_1(void);              /* FUN_004b21c4 */
    extern void sk_vas_abort_chain_2(void);              /* FUN_004b2224 */
    extern void sk_vas_abort_chain_3(void);              /* FUN_004b2150 */
    extern void sk_vas_abort_chain_4(void);              /* FUN_004b2188 */

    if (sk_vspace_lookup(4, 0xd) != 0)                   /* FUN_0005baac */
        return;

    sk_list_init(&heap_registry_head);                   /* FUN_0005ba5c */
    *(uint64_t *)(heap_region0 + 0x50) = (uint64_t)sk_vas_registry(); /* FUN_00032514 */
    heap_0064c728 = heap_004bc3b8;                       /* DAT_0064c728 = DAT_004bc3b8 */

    /* Stamp bootstrap region descriptor 0 (DAT_006af020). */
    *(uint64_t *)(heap_region0 + 0x00) = heap_0064c768;  /* base */
    heap_region0[0x01] = 0;
    heap_region0[0x05] = 0;
    *(uint64_t *)(heap_region0 + 0x08) = heap_0064c770;
    *(uint64_t *)(heap_region0 + 0x18) = heap_0064c780;
    heap_region0[0x19] = 0;
    *(uint64_t *)(heap_region0 + 0x1d) = 0x1000149000000;/* 6-byte uRam store */
    *(uint64_t *)(heap_region0 + 0x2c) = 0;
    *(uint64_t *)(heap_region0 + 0x24) = 0;
    *(uint64_t *)(heap_region0 + 0x3c) = 0;
    *(uint64_t *)(heap_region0 + 0x34) = 0;
    *(uint64_t *)(heap_region0 + 0x48) = 0;
    *(uint64_t *)(heap_region0 + 0x40) = 0;
    *(uint64_t *)(heap_region0 + 0x44) = 0;
    *(uint64_t *)(heap_region0 + 0xa8) = 0;
    *(uint64_t *)(heap_region0 + 0xa0) = 0;
    *(uint64_t *)(heap_region0 + 0x98) = 0;
    *(uint64_t *)(heap_region0 + 0x90) = 0;
    *(uint64_t *)(heap_region0 + 0x88) = 0;
    *(uint64_t *)(heap_region0 + 0x80) = 0;
    *(uint64_t *)(heap_region0 + 0x78) = 0;
    *(uint64_t *)(heap_region0 + 0x70) = 0;
    *(uint64_t *)(heap_region0 + 0x68) = 0;
    *(uint64_t *)(heap_region0 + 0x60) = 0;
    *(uint64_t *)(heap_region0 + 0x58) = 0;
    heap_region0_ptr = (uint64_t *)heap_region0;         /* DAT_0064c790 */

    /* Stamp bootstrap region descriptor 1 (DAT_006af0d0). */
    *(uint64_t *)(heap_region1 + 0x00) = heap_0064c730;
    heap_region1[0x01] = 0;
    heap_region1[0x05] = 0;
    *(uint64_t *)(heap_region1 + 0x08) = heap_0064c738;
    *(uint64_t *)(heap_region1 + 0x18) = heap_0064c740[1];/* s___common_0064c740[8] */
    heap_region1[0x19] = 0;
    *(uint64_t *)(heap_region1 + 0x1d) = 0x1000149000000;
    *(uint64_t *)(heap_region1 + 0x2c) = 0;
    *(uint64_t *)(heap_region1 + 0x24) = 0;
    *(uint64_t *)(heap_region1 + 0x3c) = 0;
    *(uint64_t *)(heap_region1 + 0x34) = 0;
    *(uint64_t *)(heap_region1 + 0x48) = 0;
    *(uint64_t *)(heap_region1 + 0x40) = 0;
    *(uint64_t *)(heap_region1 + 0x44) = 0;
    *(uint64_t *)(heap_region1 + 0xa8) = 0;
    *(uint64_t *)(heap_region1 + 0xa0) = 0;
    *(uint64_t *)(heap_region1 + 0x98) = 0;
    *(uint64_t *)(heap_region1 + 0x90) = 0;
    *(uint64_t *)(heap_region1 + 0x88) = 0;
    *(uint64_t *)(heap_region1 + 0x80) = 0;
    *(uint64_t *)(heap_region1 + 0x78) = 0;
    *(uint64_t *)(heap_region1 + 0x70) = 0;
    *(uint64_t *)(heap_region1 + 0x68) = 0;
    *(uint64_t *)(heap_region1 + 0x60) = 0;
    *(uint64_t *)(heap_region1 + 0x58) = 0;
    heap_region1_ptr = (uint64_t *)heap_region1;         /* DAT_0064c758 */
    *(uint64_t *)(heap_region1 + 0x50) = *(uint64_t *)(heap_region0 + 0x50);

    sk_vas_lock_init((uint64_t)&heap_bss_lock, 0x3397c,
                     (uint64_t)&heap_bss_lock);           /* FUN_00034b10 */

    {
        uint64_t *slot = heap_registry_table;
        int left = 3;
        sk_vas_lock_tok_t tok = sk_vas_lock_acquire((uint64_t)&heap_bss_lock);
        sk_vas_frag_heap_node_t *vas = NULL;
        uint8_t *cnt = NULL;
        for (;;) {
            if (slot + 1 > heap_registry_table + 4 || slot < heap_registry_table)
                SK_ASRT_PANIC(0x33978);
            if (*slot == 0) {
                uint64_t popped = sk_vas_stack_pop();    /* FUN_00043eac */
                if (popped == 0) {
                    vas = sk_vas_current();              /* FUN_004b2128 */
                    if ((uint8_t *)vas + 0x30 < (uint8_t *)vas)
                        SK_ASRT_PANIC(0x33ae4);
                    if (!sk_vas_locked((uint64_t)&heap_bss_lock)) /* FUN_00034ba4 */
                        goto abort_b24;
                    if ((vas->h2_flags & 1) != 0 || vas->h0_flags == 1)
                        goto abort_b18;
                    if (vas->active == 1) {
                        void *obj = sk_vas_registry_peek(); /* FUN_004b21ec */
                        sk_vas_lock_tok_t t2 =
                            sk_vas_lock_acquire((uint64_t)&heap_bss_lock);
                        (*(void (**)(void *))(obj + 0x10))(obj);
                        sk_vas_lock_release((uint64_t)&heap_bss_lock, t2.flags, t2.counter);
                        return;
                    }
                    left = 0;
                    vas->active = 1;
                    cnt = &vas->count;
                    break;
                }
                *slot = popped;
                heap_registry_count++;                   /* DAT_0064cac8 */
            }
            slot++;
            left--;
            if (left == 0) {
                heap_registry_overflow = 3;              /* DAT_0064cac9 */
                sk_vas_lock_release((uint64_t)&heap_bss_lock, tok.flags, tok.counter);
                return;
            }
        }

        /* Slot-manager refill for the current node: scan the 3-slot direct
         * ring, then the 13 per-region pools. */
        for (;;) {
            uint8_t *p = (uint8_t *)vas + 0x3c0 + left * 8;
            if ((uint8_t *)vas + 0x3c0 < p + 8 || p + 8 < p)
                SK_ASRT_PANIC(0x33ae4);
            if (*(uint64_t *)p == 0) {
                vas->slot_in = 1;
                uint64_t sa = sk_vas_slot_alloc();       /* FUN_00034f70 */
                vas->slot_in = 0;
                if (sa == 0) {
                    sk_vas_abort_chain_1();              /* FUN_004b21c4 */
abort_b18:
                    sk_vas_abort_chain_2();              /* FUN_004b2224 */
abort_b1c:
                    sk_vas_abort_chain_3();              /* FUN_004b2150 */
abort_b20:
                    sk_vas_abort_chain_4();              /* FUN_004b2188 */
abort_b24:
                    sk_vas_abort("VAS abort in function %s at line %d",
                                 __func__, 0x5b090a);
                }
                *(uint64_t *)p = sa;
                if (2 < *cnt)
                    sk_vas_abort("VAS abort in function %s at line %d",
                                 __func__, 0x5b0a96);
                left = 0;
                (*cnt)++;
            } else {
                left++;
                if (left == 3) {
                    left = 0;
                    for (;;) {
                        uint8_t *r = (uint8_t *)vas + left;
                        if ((uint8_t *)vas + 0x3c0 < r + 0x120U)
                            SK_ASRT_PANIC(0x33ae4);
                        if (*(uint64_t *)(r + 0xf0) < *(uint8_t *)(r + 0xea))
                            break;
                        left += 0x38;
                        if (left == 0x2d8) {
                            vas->active = 0;
                            if ((vas->h2_flags & 1) == 0 && vas->h0_flags != 1)
                                return;
                            goto abort_b1c;
                        }
                    }
                    uint8_t *pool = (uint8_t *)vas + left + 0xe8;
                    if ((uint8_t *)vas + left + 0x120 < pool)
                        SK_ASRT_PANIC(0x33ae4);
                    uint64_t *got = sk_pool_alloc((uint64_t)vas,
                                                  (uint16_t *)pool, 0); /* FUN_00032e90 */
                    if (got == 0)
                        goto abort_b20;
                    sk_pool_free((uint64_t)vas, (uint16_t *)pool, got); /* FUN_000331a0 */
                    left = 0;
                }
            }
        }
    }
}

/*--------------------------------------------------------------------*/
/* FUN_00033b50 @ 0x00033b50  (est. sk_vas_registry_call)
 * Ghidra: void FUN_00033b50(long param_1)
 * Dispatches a method call on a registry-callable object: takes the VAS lock,
 * invokes the object's handler at *(param_1 + 0x10), then releases the lock.
 * Confidence: high (trivial lock/dispatch wrapper). */
static void sk_vas_registry_call(uint64_t o)
{
    sk_vas_lock_tok_t tok = sk_vas_lock_acquire((uint64_t)&heap_bss_lock);
    (*(void (**)(uint64_t))(o + 0x10))(o);
    sk_vas_lock_release((uint64_t)&heap_bss_lock, tok.flags, tok.counter);
}

/*--------------------------------------------------------------------*/
/* FUN_00033bb0 @ 0x00033bb0  (est. sk_vas_heap_init)
 * Ghidra: void FUN_00033bb0(void)
 * Boot-time VAS region setup. Allocates the fixed heap node (0x6af180, tag
 * 0xd) and builds three guarded region mappings via sk_vas_heap_alloc_span:
 * the node's stored range (+0x78..+0x88, attr +0x90) recorded at +0xa0 with
 * active flag +0xa8; the fixed kernel/heap range (4, 0x200000, 0x10020000,
 * 0xfe) recorded at +0xb0; and the node's second stored range (+0x40..+0x50,
 * attr +0x58) recorded at +0x68 with active flag +0x70.
 * Confidence: medium (structural region setup). */
static void sk_vas_heap_init(void)
{
    sk_vas_frag_heap_node_t *node = NULL;
    sk_vspace_alloc((uint64_t *)&node, 4, 0xd);   /* FUN_0005acac */
    if ((uint8_t *)node + 0x78 <= (uint8_t *)node + 0xb0) {
        node->h0_region = sk_vas_heap_alloc_span(node->h0_kind, node->h0_base,
                                                 node->h0_end - node->h0_base,
                                                 node->h0_meta);   /* FUN_00033c60 */
        node->h0_active = 1;
        node->region = sk_vas_heap_alloc_span(4, 0x200000, 0x10020000, 0xfe);
        if ((uint8_t *)node <= (uint8_t *)node + 0x3e0) {
            node->h2_region = sk_vas_heap_alloc_span(node->h2_kind, node->h2_base,
                                                     node->h2_end - node->h2_base,
                                                     node->h2_meta);
            node->h2_active = 1;
            return;
        }
    }
    SK_ASRT_PANIC(0x33c60);
}

/*--------------------------------------------------------------------*/
/* FUN_00033c60 @ 0x00033c60  (est. sk_vas_heap_alloc_span)
 * Ghidra: undefined8 FUN_00033c60(undefined1 param_1,long param_2,
 *           undefined8 param_3,undefined1 param_4)
 * Allocates a VAS/private region via the trap FUN_0003c510. Builds a region
 * descriptor {type k, base, size n, attr m} and calls FUN_0003c510 with the
 * memory-attribute selector 0x1000148 (base 0) or 0x1000149 (non-zero base).
 * On success returns the mapped base; on failure of a zero-base (private)
 * region it prints a warning and returns 0, otherwise it aborts.
 * Confidence: medium (structural; string "Could not allocate for VAS private"
 *   at 005b060a, abort at 005b0655). */
static uint64_t sk_vas_heap_alloc_span(uint8_t k, uint64_t base, uint64_t n, uint8_t m)
{
    uint64_t sel = 0x1000148;
    if (base != 0) sel = 0x1000149;
    uint64_t in[4] = { k, base, n, m };
    uint64_t out = 0;
    uint8_t rc = (uint8_t)(sk_trap_alloc_region(sel, in, &out, 0, 0) & 0xff); /* FUN_0003c510 */
    if (rc == 0) return out;
    if (base == 0) {
        sk_printf("Could not allocate for VAS private region (rc=%u)\n", rc); /* FUN_00118b28 */
        return 0;
    }
    sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5b0655);
}

/*--------------------------------------------------------------------*/
/* FUN_00033da4 @ 0x00033da4  (est. sk_vas_region_alloc)
 * Ghidra: void FUN_00033da4(void)
 * Allocates the fixed heap node and initialises its small free-list at
 * offset +0x200 via sk_pool_alloc; on success it stamps the early descriptor
 * via sk_vas_desc_init (FUN_00030b2c). Aborts on layout failure.
 * Confidence: medium (structural; SoftwareBreakpoint 0x5519 at 0x33e00). */
static void sk_vas_region_alloc(void)
{
    sk_vas_frag_heap_node_t *node = NULL;
    sk_vspace_alloc((uint64_t *)&node, 4, 0xd);   /* FUN_0005acac */
    if ((uint8_t *)node + 0x3e0 < (uint8_t *)node ||
        (uint8_t *)node + 0x238 < (uint8_t *)node + 0x200)
        SK_ASRT_PANIC(0x33e00);
    uint64_t *r = sk_pool_alloc((uint64_t)node,
                                (uint16_t *)((uint8_t *)node + 0x200), 1); /* FUN_00032e90 */
    if (r != 0)
        sk_vas_desc_init(r);   /* FUN_00030b2c */
}

/*--------------------------------------------------------------------*/
/* FUN_00033e00 @ 0x00033e00  (est. sk_vas_region_free)
 * Ghidra: undefined8 FUN_00033e00(undefined8 param_1)
 * Releases a vspace element. If the root descriptor's small-layout flag
 * (FUN_00030cb8) is set, the element is returned to the free-list at node
 * +0x200 (sk_pool_free, which yields the element back). Otherwise, on the
 * large-layout path, it allocates a fresh node, initialises the +0x238 pool,
 * allocates a 4 KiB chunk (sk_vas_heap_alloc), and re-initialises the store
 * via sk_vas_desc_init2 (FUN_00030b9c). Returns 0 on the slow path, else the
 * re-initialised store pointer. Aborts (0x5519 @0x33e60/0x33f1c) on layout
 * failure.
 * Confidence: medium (structural). */
static uint64_t sk_vas_region_free(uint64_t page)
{
    extern void sk_vas_fault15(void);   /* FUN_004b225c */

    if (sk_vas_is_span(page) & 1) {   /* FUN_00030cb8 */
        sk_vas_frag_heap_node_t *node = NULL;
        sk_vspace_alloc((uint64_t *)&node, 4, 0xd);
        if ((uint8_t *)node <= (uint8_t *)node + 0x3e0 &&
            (uint8_t *)node + 0x200 <= (uint8_t *)node + 0x238) {
            sk_pool_free((uint64_t)node,
                         (uint16_t *)((uint8_t *)node + 0x200),
                         (uint64_t *)page);   /* FUN_000331a0 (returns page) */
            return page;
        }
        SK_ASRT_PANIC(0x33e60);
    }
    sk_vas_fault15();   /* FUN_004b225c */
    {
        sk_vas_frag_heap_node_t *node = NULL;
        sk_vspace_alloc((uint64_t *)&node, 4, 0xd);
        if ((uint8_t *)node <= (uint8_t *)node + 0x3e0 &&
            (uint8_t *)node + 0x238 <= (uint8_t *)node + 0x270) {
            uint64_t *r = sk_pool_alloc((uint64_t)node,
                                        (uint16_t *)((uint8_t *)node + 0x238), 1);
            if (r != 0) {
                uint64_t *chunk = sk_vas_heap_alloc();   /* FUN_00033f1c */
                if (chunk != 0)
                    return (uint64_t)sk_vas_desc_init2(r, (uint64_t)chunk); /* FUN_00030b9c */
                sk_vspace_alloc((uint64_t *)&node, 4, 0xd);
                if ((uint8_t *)node + 0x3e0 < (uint8_t *)node ||
                    (uint8_t *)node + 0x270 < (uint8_t *)node + 0x238)
                    goto fail_33f1c;
                sk_pool_free((uint64_t)node,
                             (uint16_t *)((uint8_t *)node + 0x238), r);
            }
            return 0;
        }
fail_33f1c:
        SK_ASRT_PANIC(0x33f1c);
    }
}

/*--------------------------------------------------------------------*/
/* FUN_00033e64 @ 0x00033e64  (est. sk_vas_region_alloc2)
 * Ghidra: undefined8 FUN_00033e64(void)
 * Allocates a large-layout store: initialises the node's +0x238 free-list,
 * allocates a 4 KiB chunk (sk_vas_heap_alloc) and re-initialises the store
 * backed by it via sk_vas_desc_init2; on chunk failure the store node is
 * returned to the +0x238 pool. Returns the new store or 0.
 * Confidence: medium (structural). */
static uint64_t sk_vas_region_alloc2(void)
{
    sk_vas_frag_heap_node_t *node = NULL;
    sk_vspace_alloc((uint64_t *)&node, 4, 0xd);
    if ((uint8_t *)node <= (uint8_t *)node + 0x3e0 &&
        (uint8_t *)node + 0x238 <= (uint8_t *)node + 0x270) {
        uint64_t *r = sk_pool_alloc((uint64_t)node,
                                    (uint16_t *)((uint8_t *)node + 0x238), 1);
        if (r != 0) {
            uint64_t *chunk = sk_vas_heap_alloc();   /* FUN_00033f1c */
            if (chunk != 0)
                return (uint64_t)sk_vas_desc_init2(r, (uint64_t)chunk); /* FUN_00030b9c */
            sk_vspace_alloc((uint64_t *)&node, 4, 0xd);
            if ((uint8_t *)node + 0x3e0 < (uint8_t *)node ||
                (uint8_t *)node + 0x270 < (uint8_t *)node + 0x238)
                goto fail_33f1c;
            sk_pool_free((uint64_t)node,
                         (uint16_t *)((uint8_t *)node + 0x238), r);
        }
        return 0;
    }
fail_33f1c:
    SK_ASRT_PANIC(0x33f1c);
}

/*--------------------------------------------------------------------*/
/* FUN_00033f1c @ 0x00033f1c  (est. sk_vas_heap_alloc)
 * Ghidra: undefined8 * FUN_00033f1c(void)
 * Allocates a 4 KiB-aligned chunk from the VAS heap node (0x6af180). If the
 * node's free list (+0xd0/0xd8/0xe0) is non-empty it pops the head chunk and
 * returns it. Otherwise it allocates a fresh node, maps a new 4 KiB region
 * via FUN_0003456c, populates it through the VAS trap (SUB_dac10230d2860f51)
 * and hooks it onto the free list with 0x4000-word entries. On first init it
 * zeroes the fresh chunk when the page is not already clean. The result must
 * be 0x4000-aligned. Aborts (0x5519 @0x34130/0x34308; strings 005b0829,
 * 005b06ea, 005b0490) on failure/corruption. Note the decompiler emits the
 * Type-propagation-warning and returns with locks held on the fast path.
 * Confidence: low (structural; heavy decompiler artifacts). */
static uint64_t *sk_vas_heap_alloc(void)
{
    extern uint64_t sk_vas_reserve_base(uint64_t, uint8_t *);   /* FUN_0003456c */
    extern uint64_t sk_vas_populate(uint64_t, uint64_t *, uint64_t *); /* SUB_dac10230d2860f51 */
    extern uint64_t sk_vas_fault16(void);                       /* FUN_004b2294 */
    extern uint64_t sk_vas_fault17(void);                       /* FUN_004b22cc */
    extern uint64_t sk_vas_mark_cap_slots2(uint64_t, uint64_t); /* FUN_0003573c */
    extern void sk_vas_page_ready(void);                        /* FUN_0004ba18 */

    sk_vas_frag_heap_node_t *node = NULL;
    sk_vspace_alloc((uint64_t *)&node, 4, 0xd);
    if ((uint8_t *)node + 0x30 < (uint8_t *)node) goto fail_3412c;
    sk_vas_lock_tok_t tok = sk_vas_lock_acquire((uint64_t)node);
    uint64_t *head = (uint64_t *)node->free_head;   /* +0xd0 */
    uint64_t *blk, *lo, *hi, *chunk;
    if (head == NULL) {
        sk_vas_frag_heap_node_t *node2 = NULL;
        sk_vspace_alloc((uint64_t *)&node2, 4, 0xd);
        if ((uint8_t *)node2 + 0x30 < (uint8_t *)node2) goto fail_3412c;
        sk_vas_lock_tok_t tok2 = sk_vas_lock_acquire((uint64_t)node2);
        if ((uint8_t *)node2 + 0x3e0 < (uint8_t *)node2 ||
            (uint8_t *)node2 + 0x78 < (uint8_t *)node2 + 0x40)
            goto fail_3412c;
        blk = (uint64_t *)sk_vas_reserve_base((uint64_t)node2,
                                              (uint8_t *)node2 + 0x40); /* FUN_0003456c */
        if (blk == NULL) {
            if (node2->active == 1) {   /* +0xc0 */
                uint64_t pg = sk_vas_fault16();   /* FUN_004b2294 */
                if (!(sk_vas_is_page(pg) & 1)) {   /* FUN_00030ca8 */
                    uint64_t v2 = sk_vas_fault17();   /* FUN_004b22cc */
                    return (uint64_t *)sk_vas_mark_cap_slots2(v2, 0x40); /* FUN_0003573c */
                }
                uint64_t stored = 0;
                sk_vas_add(pg, &stored);   /* FUN_00030c70: desc written to stored */
                blk = (uint64_t *)stored;
                if (blk != NULL) {
                    uint64_t off = ((uint64_t)blk & 0x3fff) ? 0x4000 : 0;
                    if ((uint64_t *)(off + ((uint64_t)blk & ~0x3fff)) == blk) {
                        sk_vspace_alloc((uint64_t *)&node, 4, 0xd);
                        if ((uint8_t *)node + 0x3e0 >= (uint8_t *)node &&
                            (uint8_t *)node + 0x238 <= (uint8_t *)node + 0x270) {
                            sk_pool_free((uint64_t)node,
                                         (uint16_t *)((uint8_t *)node + 0x238),
                                         (uint64_t *)stored);
                            sk_vspace_alloc((uint64_t *)&node, 4, 0xd);
                            if ((uint8_t *)node + 0x30 >= (uint8_t *)node) {
                                sk_vas_lock_tok_t tok3 = sk_vas_lock_acquire((uint64_t)node);
                                uint64_t hiw = node->free_ptr;   /* +0xe0 */
                                uint64_t low = node->free_head;  /* +0xd0 */
                                blk[1] = node->free_tail;        /* +0xd8 */
                                blk[0] = low;
                                blk[2] = hiw;
                                node->free_head = (uint64_t)blk;
                                node->free_tail = (uint64_t)(blk + 0x800);
                                node->free_ptr = (uint64_t)blk;
                                if ((uint8_t *)node + 0x3e0 >= (uint8_t *)node) {
                                    sk_vas_lock_release((uint64_t)node, tok3.flags, tok3.counter);
                                    return blk;
                                }
                            }
                        }
                        goto fail_34308;
                    }
                }
                sk_vas_abort("VAS abort in function %s at line %d",
                             __func__, 0x5b0490);
            }
            sk_vas_lock_release((uint64_t)node2, tok2.flags, tok2.counter);
            if ((uint8_t *)node + 0x3e0 >= (uint8_t *)node) {
                sk_vas_lock_release((uint64_t)node, tok.flags, tok.counter);
                return NULL;
            }
            goto fail_3412c;
        }
        /* Fresh mapping: populate into node2's second region then hook it. */
        {
            uint64_t range[2] = { (uint64_t)blk - *(uint64_t *)(node2->h2_region + 8), 0x4000 };
            uint64_t rc = sk_vas_populate(node2->h2_region, range, range + 1);
            if ((rc & 0xff) != 0)
                sk_vas_abort("Failed to populate VAS heap VA %lx", rc & 0xff); /* 005b0829 */
        }
        sk_vas_unreserve((uint64_t)node2,
                         (uint64_t)((uint8_t *)node2 + 0x40),
                         (uint64_t)blk);   /* FUN_000346c0 */
        sk_vas_lock_release((uint64_t)node2, tok2.flags, tok2.counter);
        lo = (uint64_t *)((uint8_t *)blk + 0x4000);
        sk_vas_page_ready();   /* FUN_0004ba18 */
        chunk = blk;
        hi = blk;
        if ((heap_clean & 1) == 0) {   /* *(extraout_x1 + 0x38) & 1 */
            if (lo < blk || (uint64_t)((uint8_t *)lo - (uint8_t *)blk) < 0x4000)
                goto fail_3412c;
            sk_mem_zero(blk, 0, 0x4000);   /* FUN_001143a0 */
        }
    } else {
        lo = (uint64_t *)node->free_tail;   /* +0xd8 */
        hi = (uint64_t *)node->free_ptr;    /* +0xe0 */
        if (lo < head + 3 || head < hi) goto fail_3412c;
        node->free_ptr = head[2];
        node->free_tail = head[1];
        node->free_head = head[0];
        head[0] = 0; head[1] = 0; head[2] = 0;
        chunk = head;
    }
    if ((uint8_t *)node + 0x3e0 >= (uint8_t *)node) {
        sk_vas_lock_release((uint64_t)node, tok.flags, tok.counter);
        uint64_t off = ((uint64_t)chunk & 0x3fff) ? 0x4000 : 0;
        if ((uint64_t *)(off + ((uint64_t)chunk & ~0x3fff)) != chunk)
            sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5b06ea);
        bool ok;
        if (head == NULL) {
            ok = (((uint64_t)((uint8_t *)lo - (uint8_t *)chunk)) & ~0x3fff) != 0;
        } else {
            if (lo < chunk || chunk < hi ||
                (uint64_t)((uint8_t *)lo - (uint8_t *)chunk) < 0x4000)
                goto fail_3412c;
            sk_mem_zero(chunk, 0, 0x4000);
            ok = true;
        }
        if (chunk <= lo && hi <= chunk && ok)
            return chunk;
    }
fail_3412c:
    SK_ASRT_PANIC(0x34130);
fail_34308:
    SK_ASRT_PANIC(0x34308);
}

/*--------------------------------------------------------------------*/
/* FUN_000341f4 @ 0x000341f4  (est. sk_vas_heap_free)
 * Ghidra: void FUN_000341f4(undefined8 param_1)
 * Destroys / returns a large-layout backing store element. If the large-layout
 * flag (FUN_00030ca8) is clear it frees an aligned frame via FUN_0003573c and
 * returns. Otherwise it looks up the store descriptor (FUN_00030c70); if it is
 * 0x4000-aligned it returns the descriptor to the node +0x238 pool, allocates
 * a fresh node and splices the descriptor back onto the free list
 * (+0xd0/0xd8/0xe0) as a 0x800-word region. Aborts (0x5519 @0x34308, string
 * 005b0490) on layout failure.
 * Confidence: medium (structural). */
static void sk_vas_heap_free(uint64_t page)
{
    extern uint64_t sk_vas_fault17(void);                       /* FUN_004b22cc */
    extern uint64_t sk_vas_mark_cap_slots2(uint64_t, uint64_t); /* FUN_0003573c */

    if (!(sk_vas_is_page(page) & 1)) {   /* FUN_00030ca8 */
        uint64_t v = sk_vas_fault17();   /* FUN_004b22cc */
        sk_vas_mark_cap_slots2(v, 0x40); /* FUN_0003573c */
        return;
    }
    {
        uint64_t stored = 0;
        sk_vas_add(page, &stored);   /* FUN_00030c70: desc written to stored */
        uint64_t *desc = (uint64_t *)stored;
        if (desc != NULL) {
            uint64_t off = ((uint64_t)desc & 0x3fff) ? 0x4000 : 0;
            if ((uint64_t *)(off + ((uint64_t)desc & ~0x3fff)) == desc) {
                sk_vas_frag_heap_node_t *node = NULL;
                sk_vspace_alloc((uint64_t *)&node, 4, 0xd);
                if ((uint8_t *)node + 0x3e0 >= (uint8_t *)node) {
                    if ((uint8_t *)node + 0x238 <= (uint8_t *)node + 0x270) {
                        sk_pool_free((uint64_t)node,
                                     (uint16_t *)((uint8_t *)node + 0x238),
                                     (uint64_t *)stored);
                        sk_vspace_alloc((uint64_t *)&node, 4, 0xd);
                        if ((uint8_t *)node + 0x30 >= (uint8_t *)node) {
                            sk_vas_lock_tok_t tok = sk_vas_lock_acquire((uint64_t)node);
                            uint64_t hiw = node->free_ptr;   /* +0xe0 */
                            uint64_t low = node->free_head;  /* +0xd0 */
                            desc[1] = node->free_tail;       /* +0xd8 */
                            desc[0] = low;
                            desc[2] = hiw;
                            node->free_head = (uint64_t)desc;
                            node->free_tail = (uint64_t)(desc + 0x800);
                            node->free_ptr = (uint64_t)desc;
                            if ((uint8_t *)node + 0x3e0 >= (uint8_t *)node) {
                                sk_vas_lock_release((uint64_t)node, tok.flags, tok.counter);
                                return;
                            }
                        }
                    }
                }
                SK_ASRT_PANIC(0x34308);
            }
        }
    }
    sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5b0490);
}

/*--------------------------------------------------------------------*/
/* FUN_00034334 @ 0x00034334  (est. sk_vas_mark_slots)
 * Ghidra: void FUN_00034334(undefined8 param_1)
 * Thin wrapper: marks the 0x40 cap slots of the given page via FUN_0003573c
 * and returns. Used by FUN_00041d9c.
 * Confidence: high (trivial wrapper). */
static void sk_vas_mark_slots(uint64_t a)
{
    extern uint64_t sk_vas_mark_cap_slots2(uint64_t, uint64_t); /* FUN_0003573c */
    sk_vas_mark_cap_slots2(a, 0x40);
}

/*--------------------------------------------------------------------*/
/* FUN_0003433c @ 0x0003433c  (est. sk_vas_alloc_direct)
 * Ghidra: ulong FUN_0003433c(void)
 * Allocates a direct heap element. Allocates the node (0x6af180) and, if the
 * node's slot-in flag (+0xc2 bit 0) is clear or the guard flag (+0xc1) is set,
 * scans the 3-slot direct ring (+0x3c0) for a free entry, else refills via
 * FUN_004b233c (which returns the new node, element, slot and count pointers).
 * It clears the found slot and, if the count at +0x3d8 is zero, allocates a
 * fresh pool block at +0xe8 under the guard flag and returns it; otherwise it
 * decrements the count (updating the min at +0x3d9) and returns the element.
 * FUN_00034340 is a duplicate of this routine.
 * Confidence: medium (structural; SoftwareBreakpoint 0x5519 @0x343e0/0x34468). */
static uint64_t sk_vas_alloc_direct(void)
{
    extern sk_vas_refill_t sk_vas_refill(void);   /* FUN_004b233c */
    extern void sk_vas_fault19(void);             /* FUN_004b2304 */

    sk_vas_frag_heap_node_t *node = NULL;
    sk_vspace_alloc((uint64_t *)&node, 4, 0xd);
    if (((node->slot_in & 1) == 0) || (node->guard == 1)) {
        uint64_t *slot = node->direct;                 /* +0x3c0 */
        uint64_t *cnt = (uint64_t *)&node->count;      /* +0x3d8 */
        int left = 3;
        uint64_t val;
        do {
            if (cnt < slot + 1 || slot + 1 < slot)
                SK_ASRT_PANIC(0x343e0);
            val = *slot;
            if (val != 0) goto found;
            slot++;
            left--;
        } while (left != 0);
        {
            sk_vas_refill_t rf = sk_vas_refill();   /* FUN_004b233c */
            node = (sk_vas_frag_heap_node_t *)rf.node;
            val = rf.value;
            slot = rf.slot;
            cnt = rf.count;
        }
found:
        *slot = 0;
        char c = (char)*cnt;
        if (c == 0) {
            sk_vas_fault19();   /* FUN_004b2304 */
            sk_vspace_alloc((uint64_t *)&node, 4, 0xd);
            node->guard = 1;
            uint64_t pool = 0;
            sk_vspace_alloc(&pool, 4, 0xd);
            if (pool <= pool + 0x3e0 && pool + 0xe8 <= pool + 0x120) {
                uint64_t r = (uint64_t)sk_pool_alloc(pool,
                                                     (uint16_t *)(pool + 0xe8), 1);
                node->guard = 0;
                if (r <= r + 0x48) return r;
            }
            SK_ASRT_PANIC(0x34468);
        }
        node->count = (uint8_t)(c - 1);
        if ((uint8_t)(c - 1) < node->min)
            node->min = (uint8_t)(c - 1);
        return val;
    }
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_00034340 @ 0x00034340  (est. sk_vas_alloc_indirect)
 * Ghidra: ulong FUN_00034340(void)
 * Duplicate of FUN_0003433c (same body, separate code entry). Allocates a
 * direct heap element with the identical scan/alloc logic.
 * Confidence: medium. */
static uint64_t sk_vas_alloc_indirect(void)
{
    return sk_vas_alloc_direct();
}

/*--------------------------------------------------------------------*/
/* FUN_00034468 @ 0x00034468  (est. sk_vas_alloc_slow)
 * Ghidra: long FUN_00034468(void)
 * Slow heap allocation: maps a fresh 4 KiB region into the node. Sets the
 * guard flag (+0xc1), maps a region at +0x78 via FUN_0003456c and, if it is a
 * fresh page, populates it through the VAS trap (SUB_dac10230d2860f51) and
 * hooks it (FUN_000346c0), bumping the node's size counter (+0x98) by 0x4000
 * on failure. Clears the guard and releases the node lock. Returns the mapped
 * base or 0. Aborts (0x5519 @0x3456c) on layout failure.
 * Confidence: medium (structural; Type-propagation warning in Ghidra). */
static uint64_t sk_vas_alloc_slow(void)
{
    extern uint64_t sk_vas_reserve_base(uint64_t, uint8_t *);   /* FUN_0003456c */
    extern uint64_t sk_vas_populate(uint64_t, uint64_t *, uint64_t *); /* SUB_dac10230d2860f51 */

    sk_vas_frag_heap_node_t *node = NULL;
    sk_vspace_alloc((uint64_t *)&node, 4, 0xd);
    if ((uint8_t *)node + 0x30 < (uint8_t *)node)
        SK_ASRT_PANIC(0x3456c);
    sk_vas_lock_tok_t tok = sk_vas_lock_acquire((uint64_t)node);
    node->guard = 1;
    if ((uint8_t *)node + 0x3e0 >= (uint8_t *)node) {
        uint64_t base = sk_vas_reserve_base((uint64_t)node,
                                            (uint8_t *)node + 0x78); /* FUN_0003456c */
        if (base != 0) {
            uint64_t range[2] = { base - *(uint64_t *)(node->h0_region + 8), 0x4000 };
            char rc = (char)sk_vas_populate(node->h0_region, range, range + 1);
            sk_vas_unreserve((uint64_t)node,
                             (uint64_t)((uint8_t *)node + 0x78),
                             base);   /* FUN_000346c0 */
            if (rc != 0) {
                base = 0;
                node->h0_next += 0x4000;   /* +0x98 */
            }
        }
        node->guard = 0;
        sk_vas_lock_release((uint64_t)node, tok.flags, tok.counter);
        return base;
    }
    SK_ASRT_PANIC(0x3456c);
}
