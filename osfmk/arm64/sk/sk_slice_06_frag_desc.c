/* sk_slice_06_frag_desc.c — VAS descriptor/object helpers (0x30b2c-0x31594).
 * Backing-store (page/span) descriptor lifecycle: descriptor init, add, kind
 * predicates, slot allocation from a store, store link, store release, and
 * store bitmap marking. */

#include "sk_slice_06_shared.h"

/* ---- Cross-function helpers not declared in the shared header (each with its
 * FUN_ address ground truth). ---- */
extern unsigned long sk_vm_bitmap_find(unsigned long map, unsigned long store); /* FUN_004b1d40 */
extern void sk_vas_fault(void);       /* FUN_004b1d08 */
extern void sk_vas_fault2(void);      /* FUN_004b1de4 */
extern void sk_vas_fault3(void);      /* FUN_004b1e90 */
extern void sk_vas_fault4(void);      /* FUN_004b1ec8 */
extern void sk_vas_fault5(void);      /* FUN_004b1f04 */
extern void sk_vas_fault6(void);      /* FUN_004b1f3c */
extern void sk_vas_fault7(void);      /* FUN_004b1e1c */
extern void sk_vas_fault8(void);      /* FUN_004b1e58 */

/* The shared header estimates sk_vas_region_alloc, sk_pool_alloc_2/3 and
 * sk_vspace_alloc as returning void, but their decompiles use the x0 result
 * (the freshly allocated block / descriptor pointer). Recover the value by
 * calling through a function pointer of the correct return type. */
typedef void *(*sk_ptr_alloc_rtn)(void);
typedef void *(*sk_vspace_alloc_rtn)(uint64_t *, uint64_t, uint64_t);

/* FUN_00030b2c @ 0x00030b2c  (est. sk_vas_desc_init)
 * Ghidra: undefined8 * FUN_00030b2c(undefined8 *param_1)
 * Initialises a fresh VAS descriptor block: stamps the 0x2001 free-list tag,
 * the small-layout shift/capacity hints (0x20 / 0x7e), self-links the list
 * heads and points slot 8 at the fixed 0x2007e root-table word. Zeroes a
 * 16-byte region at slot 9. Returns the descriptor.
 * Confidence: high
 * Notes: DAT_0002007e root-table pointer; FUN_001143a0 (sk_mem_zero). */
static uint64_t *sk_vas_desc_init(uint64_t *d)
{
    *(uint16_t *)((uint8_t *)d + 0x58) = 0x2001;   /* free-list type tag */
    *(uint8_t *)((uint8_t *)d + 0x5a) = 0x20;      /* granule shift hint */
    *(uint16_t *)((uint8_t *)d + 0x5c) = 0x7e;     /* small-layout capacity */
    d[0] = 0;
    d[1] = (uint64_t)((uint8_t *)d + 0x58);
    d[2] = 0;
    d[3] = 0;
    d[4] = 0;
    d[5] = (uint64_t)((uint8_t *)d + 0x48);
    d[6] = (uint64_t)((uint8_t *)d + 0x78);
    d[7] = 0;
    d[8] = (uint64_t)(uintptr_t)0x2007e;           /* &DAT_0002007e */
    sk_mem_zero((uint8_t *)d + 0x48, 0, 0x10);
    return d;
}

/* FUN_00030b9c @ 0x00030b9c  (est. sk_vas_desc_init2)
 * Ghidra: undefined8 * FUN_00030b9c(undefined8 *param_1, ulong param_2)
 * Initialises a VAS descriptor backed by an externally supplied store at
 * `base` (which must be 0x4000-aligned). Stamps the large-layout store header
 * (tag 0x2001, shift 0x20, capacity 0x1fe) at base+0x20, zeroes the descriptor
 * field block and wires the descriptor's list heads into the store. Returns
 * the descriptor.
 * Confidence: high
 * Notes: alignment failure aborts via VAS string 005aec3d; the
 *   always-true `d <= d+0x48` guard ends in SK_ASRT_PANIC(0x30c3c). */
static uint64_t *sk_vas_desc_init2(uint64_t *d, uint64_t base)
{
    if ((base & 0x3fff) != 0)
        sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5aec3d);

    *(uint16_t *)(base + 0x20) = 0x2001;
    *(uint8_t *)(base + 0x22) = 0x20;
    *(uint16_t *)(base + 0x24) = 0x1fe;            /* large-layout capacity */
    sk_mem_zero((uint8_t *)d + 0x48, 0, 0x40);

    if ((uint64_t)d <= (uint64_t)((uint8_t *)d + 0x48)) {
        d[0] = 0;
        d[1] = base + 0x20;
        d[2] = 0;
        d[3] = base;
        d[4] = base + 0x18;
        d[5] = (uint64_t)((uint8_t *)d + 0x48);
        d[6] = base + 0x40;
        d[7] = 0;
        d[8] = 0x801fe;
        return d;
    }
    SK_ASRT_PANIC(0x30c3c);
}

/* FUN_00030c70 @ 0x00030c70  (est. sk_vas_add)
 * Ghidra: void FUN_00030c70(long param_1,long *param_2)
 * Publishes a VAS descriptor (param_1) into a page/slot descriptor slot
 * (param_2) after confirming the descriptor carries the 0x1fe page layout
 * and that its base (+0x18) does not wrap when extended by 0x4000. Non-page
 * descriptors take the fault path; wrap or mismatch panics.
 * Confidence: high
 * Notes: kind check *(short*)(param_1+0x40)==0x1fe; sk_vas_fault (FUN_004b1d08);
 *   SK_ASRT_PANIC(0x30ca8). */
static void sk_vas_add(uint64_t vas, uint64_t *desc)
{
    if (*(uint16_t *)(vas + 0x40) == 0x1fe) {      /* page layout */
        *desc = vas;
        if (*(uint64_t *)(vas + 0x18) <= *(uint64_t *)(vas + 0x18) + 0x4000)
            return;
    } else {
        sk_vas_fault();                            /* FUN_004b1d08 */
    }
    SK_ASRT_PANIC(0x30ca8);
}

/* FUN_00030ca8 @ 0x00030ca8  (est. sk_vas_is_page)
 * Ghidra: bool FUN_00030ca8(long param_1)
 * Predicate: true iff the object at `o` carries the 0x1fe page layout tag.
 * Confidence: high */
static bool sk_vas_is_page(uint64_t o)
{
    return *(uint16_t *)(o + 0x40) == 0x1fe;
}

/* FUN_00030cb8 @ 0x00030cb8  (est. sk_vas_is_span)
 * Ghidra: bool FUN_00030cb8(long param_1)
 * Predicate: true iff the object at `o` carries the 0x7e span layout tag.
 * Confidence: high */
static bool sk_vas_is_span(uint64_t o)
{
    return *(uint16_t *)(o + 0x40) == 0x7e;
}

/* FUN_00030cc8 @ 0x00030cc8  (est. sk_vas_page_alloc)
 * Ghidra: ulong FUN_00030cc8(long param_1)
 * Allocates the next free slot offset from the VAS backing store at
 * vas+0x138. If no store exists yet it lazily creates one — small layout via
 * sk_vas_region_alloc (FUN_00033da4) or large via sk_vas_region_alloc2
 * (FUN_00033e64), selected by vas+9 bit 0 — and hooks it in with
 * sk_vas_page_add (FUN_00030fb0). It then either bumps the store's free-run
 * counter (fast path) or clears a bit in the allocation bitmap (FUN_004b1d40),
 * and returns the 0x20-byte slot offset within the store. Returns 0 when the
 * vspace is full; malformed state aborts (VAS 005aed68 / SK_ASRT_PANIC).
 * Confidence: high
 * Notes: all lock ops target vas+0x40 (sk_vm_lock_acquire/release);
 *   SoftwareBreakpoint(0x5519) at 0x30f18. */
static uint64_t sk_vas_page_alloc(uint64_t vas)
{
    uint64_t store;      /* uVar15 = *(vas+0x138) */
    uint64_t new_store;  /* lVar14 */
    uint64_t base;       /* uVar9 */
    uint16_t *cnt;       /* puVar8 */
    uint16_t size;       /* uVar4 */
    uint64_t slot;       /* uVar16 */
    uint64_t bitmask;    /* uVar12 */
    uint64_t *cell;      /* puVar10 */
    unsigned ncells;     /* uVar11 */
    unsigned idx;
    int r;
    unsigned flag;       /* bVar3 */

    if (vas + 0x40 > vas + 0x50)
        goto fail;
    flag = *(uint8_t *)(vas + 9);
    r = sk_vm_lock_acquire();                    /* FUN_00118164 (lock vas+0x40) */
    if (r != 0)
        sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5aed68);

    store = *(uint64_t *)(vas + 0x138);
    new_store = 0;
    if (store == 0) {
        /* No backing store yet: allocate one and attach it, retrying until a
         * store is present. */
        do {
            if (new_store == 0) {
                r = sk_vm_lock_release();        /* FUN_00118194 */
                if (r != 0)
                    sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5aed68);
                new_store = (flag & 1) == 0
                    ? (uint64_t)((sk_ptr_alloc_rtn)sk_vas_region_alloc)()  /* FUN_00033da4 */
                    : sk_vas_region_alloc2();                            /* FUN_00033e64 */
                r = sk_vm_lock_acquire();
                if (r != 0)
                    sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5aed68);
            } else {
                sk_vas_page_add(vas, (uint64_t *)new_store);  /* FUN_00030fb0 */
                new_store = 0;
            }
            store = *(uint64_t *)(vas + 0x138);
        } while (store == 0);
    }

    base = store + 0x48;                         /* wrap-check sentinel */
    cnt = (uint16_t *)(*(uint64_t *)(store + 8) + 6);
    slot = *cnt;
    size = *(uint16_t *)(store + 0x40);
    if (slot < size) {
        /* Fast path: bump the free-run counter. */
        uint16_t nv = (uint16_t)(slot + 1);
        *cnt = nv;
        if (nv == size) {
            if (base < store) goto fail;         /* store+0x48 < store: wrap */
            sk_vas_page_free(vas, store);        /* FUN_000314b4 */
        }
        base = *(uint64_t *)(store + 0x30);
        slot = base + slot * 0x20;
    } else {
        /* Bitmap path: locate the first clear bit in the allocation map. */
        uint64_t acc = 0;
        ncells = *(uint8_t *)(store + 0x42);
        cell = (uint64_t *)(store + 0x28);
        if (ncells != 0) {
            acc = 0;
            for (;;) {
                bitmask = *cell;
                if (bitmask != 0) break;
                acc -= 0x800;
                cell++;
                if (ncells * 0x800 + acc == 0) break;
            }
        }
        /* FUN_004b1d40 returns the found bitmap word (x10); the cell pointer
         * (x9) and wrap value (x8) are its register outputs. */
        bitmask = sk_vm_bitmap_find(store + 0x42, store);
        idx = 0;
        while (((bitmask >> (idx & 0x3f)) & 1) == 0) idx++;
        if (((1UL << (idx & 0x3f)) & bitmask) == 0)
            sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5aee2b);
        bitmask &= ~(1UL << (idx & 0x3f));
        *cell = bitmask;
        if (bitmask == 0) {
            if (base < store) goto fail;
            sk_vas_page_free(vas, store);        /* FUN_000314b4 */
        }
        base = *(uint64_t *)(store + 0x30);
        slot = (base + idx * 0x20) - acc;
    }

    if (slot == 0 ||
        (base <= slot && slot <= slot + 0x20 &&
         slot + 0x20 <= base + (uint64_t)size * 0x20)) {
        r = sk_vm_lock_release();
        if (r == 0) {
            if (new_store != 0) {
                if ((flag & 1) == 0)
                    ((void (*)(void))sk_vas_region_free)();  /* FUN_00033e00 */
                else
                    sk_vas_heap_free(new_store);             /* FUN_000341f4 */
            }
            return slot;
        }
        sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5aed68);
    }
fail:
    SK_ASRT_PANIC(0x30f18);
}

/* FUN_00030fb0 @ 0x00030fb0  (est. sk_vas_page_add)
 * Ghidra: void FUN_00030fb0(long param_1, undefined8 *param_2)
 * Allocates and links a new vspace object (page) into the VAS descriptor at
 * vas. Two regions are managed: a slot-node list at vas+0x148 and a page-group
 * list whose free-run head is *(vas+0x140). The object is stamped with the
 * current level byte (vas+0xf8), its parent reference (vas+0x20), and chained
 * onto the free-run list. When the level marker at vas+0x1d1 is set it calls
 * sk_vas_rebuild_inner (FUN_00031bf4). Backing blocks come from sk_pool_alloc_3
 * (node, FUN_000333a8) and sk_pool_alloc_2 (group, FUN_0003335c). Overflows
 * abort (VAS 005aed68/005af74e / SK_ASRT_PANIC).
 * Confidence: high
 * Notes: SoftwareBreakpoint(0x5519) at 0x312dc/0x312e4/0x31494; block lock at
 *   lv+0xb0 and vas lock at vas+0x40 via sk_vm_lock_acquire/release. */
static void sk_vas_page_add(uint64_t vas, uint64_t *page)
{
    uint64_t *slot_head = (uint64_t *)(vas + 0x148);
    uint64_t *node;      /* puVar6 */
    uint64_t *walk;      /* puVar7 */
    uint64_t *g;         /* group block */
    uint64_t *tail, *q;
    uint64_t lv = 0;     /* uVar15 / lVar16 (block owning the group list) */
    uint64_t cur = 0;    /* lVar13 */
    uint64_t prev = 0;   /* lVar16 */
    long off;
    unsigned char filled; /* bVar3 */
    char c;
    int r;
    bool made;           /* bVar10 */

    if (slot_head > (uint64_t *)(vas + 0x1c8))
        goto fail_312dc;
    if (*(uint64_t *)(vas + 0x138) != 0) {
        sk_vas_fault2();                       /* FUN_004b1de4 */
        sk_vas_fault3();                       /* FUN_004b1e90 */
        sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5aed68);
    }

    made = false;
    node = slot_head;
    for (;;) {
        if (node == (uint64_t *)0) {
            if (made) {
                sk_vas_fault5();               /* FUN_004b1f04 */
                sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5af74e);
            }
            r = sk_vm_lock_release();          /* FUN_00118194 (lock vas+0x40) */
            if (r != 0) goto fail_312dc;
            node = ((sk_ptr_alloc_rtn)sk_pool_alloc_3)();   /* FUN_000333a8 */
            if (node == (uint64_t *)0) {
                sk_vas_fault4();               /* FUN_004b1ec8 */
                goto fail_31490;
            }
            for (int k = 0; k < 16; k++) node[k] = 0;
            r = sk_vm_lock_acquire();          /* FUN_00118164 (lock vas+0x40) */
            if (r != 0)
                sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5aed68);
            /* Walk to the tail of the node list and append the fresh node. */
            walk = slot_head;
            if ((uint64_t *)(vas + 0x150) < slot_head) goto fail_312dc;
            while ((walk = (uint64_t *)*walk) != (uint64_t *)0) {
                if (walk + 1 < walk) goto fail_312dc;
            }
            *node = 0;
            *walk = (uint64_t)node;
            made = true;
        }
        /* Walk the 7 slot-groups of this node. */
        off = 0;
        cur = prev;
        for (;;) {
            long *p1 = (long *)((long)node + off + 0x48);
            long *p2 = (long *)((long)node + off + 0x50);
            if ((long)node + 0x10 < (long)p2 || (long)p2 < (long)p1)
                goto fail_312dc;
            prev = (uint64_t)*p1;
            if (prev == 0) {
                if (cur == 0) {
                    if (2 < *(uint8_t *)(vas + 0xf8)) goto fail_31494;
                    c = 0;
                    prev = page[1];
                    *(uint8_t *)(prev + 0x10) = *(uint8_t *)(vas + 0xf8);
                    *(uint64_t *)(prev + 8) = *(uint64_t *)(vas + 0x20);
                } else {
                    if (lv < cur + 0x48) goto fail_312dc;
                    cur = *(uint64_t *)(cur + 8);
                    prev = page[1];
                    *(uint64_t *)(prev + 8) = *(uint64_t *)(cur + 8);
                    *(uint8_t *)(prev + 0x10) = *(uint8_t *)(cur + 0x10);
                    c = *(char *)(cur + 0x11) + 1;
                }
                *(char *)(prev + 0x11) = c;
                *(uint64_t **)((long)node + off + 0x48) = page;
                if ((long)node + 8 < (long)node + off + 8 ||
                    (long)node + off + 0x10 < (long)node + off + 8)
                    goto fail_312dc;
                *(uint64_t *)((long)node + off + 8) = page[6];
                if (*(char *)((long)page + 0x43) == 1) goto fail_312e0;
                page[7] = 0;
                **(uint64_t **)(vas + 0x140) = (uint64_t)page;
                *(uint64_t **)(vas + 0x140) = page + 7;
                *(uint8_t *)((long)page + 0x43) = 1;
                if (*(char *)(vas + 0x1d1) == 1)
                    sk_vas_rebuild_inner(vas); /* FUN_00031bf4 */
                r = sk_vm_lock_release();      /* FUN_00118194 */
                if (r != 0) goto fail_312e4;
                prev = (uint64_t)((sk_vspace_alloc_rtn)sk_vspace_alloc)
                           ((uint64_t *)0x6af010, 4, 10);      /* FUN_0005acac */
                lv = prev + 0xb0;
                if (prev + 0xc0 < lv) goto fail_312dc;
                r = sk_vm_lock_acquire();      /* FUN_00118164 (block lock lv) */
                if (r != 0)
                    sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5aed68);
                made = false;
                node = *(uint64_t **)(prev + 0xa0);
                goto group_walk;
            }
            lv = prev + 0x48;
            off += 8;
            cur = prev;
            if (off == 0x38) break;
        }
        node = (uint64_t *)*node;
    }

group_walk:
    for (;;) {
        filled = *(uint8_t *)((long)node + 0x1a);
        if (filled < *(uint8_t *)((long)node + 0x19))
            goto add_to_group;
        node = (uint64_t *)*node;
        if (node == (uint64_t *)0) {
            if (made) goto group_walk_done;
            r = sk_vm_lock_release();          /* FUN_00118194 (block lock lv) */
            if (r != 0)
                sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5aed68);
            g = ((sk_ptr_alloc_rtn)sk_pool_alloc_2)();       /* FUN_0003335c */
            if (g != (uint64_t *)0) {
                g[1] = (uint64_t)(g + 4);
                *(uint16_t *)((long)g + 3 * 8) = 0x1001;
                g[2] = 0;
                r = sk_vm_lock_acquire();      /* FUN_00118164 (block lock lv) */
                if (r != 0)
                    sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5aed68);
                tail = *(uint64_t **)(prev + 0xa0);
                q = tail;
                while (*q != 0) q = (uint64_t *)*q;   /* walk to last non-null */
                *g = 0;
                if ((long)g + 0x14 < (long)g) goto fail_312dc;
                *q = (uint64_t)g;
                g[2] = q[2];
                if ((long)g + 4 * 8 < (long)(g + 1)) goto fail_312dc;
                q[2] = (uint64_t)(g + 1);
                made = true;
                continue;
            }
            sk_vas_fault7();                   /* FUN_004b1e1c */
        }
        sk_vas_fault8();                       /* FUN_004b1e58 */
        sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5aed68);
    }

add_to_group:
    {
        uint64_t *p = (uint64_t *)((long)node + 4 + filled);
        if ((long)node + 4 <= (long)p && (long)p + 1 <= (long)node + 0x14 &&
            (long)p <= (long)p + 1) {
            *p = page[1];
            *(uint8_t *)((long)node + 0x1a) = filled + 1;
            *page = (uint64_t)node;
            *(uint64_t **)(prev + 0xa0) = node;
            r = sk_vm_lock_release();          /* FUN_00118194 (block lock lv) */
            if (r != 0)
                sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5aed68);
            r = sk_vm_lock_acquire();          /* FUN_00118164 (lock vas+0x40) */
            if (r != 0)
                sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5aed68);
            return;
        }
        goto fail_312dc;
    }

group_walk_done:
    return;

fail_312dc: SK_ASRT_PANIC(0x312dc);
fail_312e0: SK_ASRT_PANIC(0x312e4);
fail_312e4: sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5aed68);
fail_31490: SK_ASRT_PANIC(0x31494);
fail_31494: sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5af74e);
}

/* FUN_000314b4 @ 0x000314b4  (est. sk_vas_page_free)
 * Ghidra: void FUN_000314b4(long param_1,long param_2)
 * Releases a VAS backing store once its free-run counter has reached capacity.
 * Verifies the store is the current one (vas+0x138 == store) and that it is
 * fully allocated; if so it walks the store's bitmap (store+0x42 cells at
 * store+0x28) confirming no free bit remains, checks the store is not the
 * sentinel head (*(vas+0x140)-0x38) while still referenced, then pops the
 * store from the free-run list (via +0x38) and clears its in-list flag
 * (store+0x43).
 * Confidence: high
 * Notes: VAS strings 005af8d2/005af950. */
static void sk_vas_page_free(uint64_t vas, uint64_t page)
{
    uint64_t n;
    long *cell;

    if (*(uint64_t *)(vas + 0x138) != page)
        sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5af8d2);
    if (*(uint16_t *)(page + 0x40) <=
        *(uint16_t *)(*(uint64_t *)(page + 8) + 6)) {
        n = (uint64_t)*(uint8_t *)(page + 0x42);
        if (n != 0) {
            cell = *(long **)(page + 0x28);
            do {
                if (*cell != 0) return;        /* a bit is still in use */
                n -= 1;
                cell += 1;
            } while (n != 0);
        }
        if (*(uint64_t *)(vas + 0x140) - 0x38 == page &&
            *(uint64_t *)(page + 0x38) != 0)
            sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5af950);
        {
            uint64_t next = *(uint64_t *)(*(uint64_t *)(vas + 0x138) + 0x38);
            *(uint64_t *)(vas + 0x138) = next;
            if (next == 0)
                *(uint64_t *)(vas + 0x140) = vas + 0x138;
        }
        *(uint8_t *)(page + 0x43) = 0;
    }
}

/* FUN_00031594 @ 0x00031594  (est. sk_vas_page_map)
 * Ghidra: void FUN_00031594(long param_1, ulong param_2)
 * Marks the VAS slot at byte offset `p` as allocated by setting its bit in the
 * backing store's allocation bitmap. Selects the capacity (0x7e small / 0x1fe
 * large) from vas+9 bit 0. Walks the store chain from vas+0x148; for each
 * store whose base (store+0x30) encloses `p`, computes the slot index
 * ((p-base)>>5) and sets bit (index&0x3f) in cell (index>>6) of the bitmap
 * (store+0x28). On first alloc for a store it links the store onto the free-run
 * list and sets its in-list flag (store+0x43). Aborts on out-of-range
 * (VAS 005aef1a/005af0a5/005aeff5/005af107) or SK_ASRT_PANIC.
 * Confidence: high
 * Notes: SoftwareBreakpoint(0x5519) at 0x31770; sk_vas_fault6 (FUN_004b1f3c). */
static void sk_vas_page_map(uint64_t vas, uint64_t p)
{
    uint64_t cap = 0x7e;
    uint64_t base, store, bit;
    uint64_t *walk;     /* puVar4 */
    long *pl;           /* plVar5 */
    long off;
    long idx;
    uint64_t *bm, *cell;
    int r;

    if ((*(uint8_t *)(vas + 9) & 1) != 0) cap = 0x1fe;
    *(uint8_t *)(p + 0x18) = 0;                 /* in_wzr: zero scratch slot */
    if (vas + 0x40 > vas + 0x50)
        goto fail;
    r = sk_vm_lock_acquire();                   /* FUN_00118164 (lock vas+0x40) */
    if (r != 0)
        sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5aed68);

    pl = (long *)(vas + 0x148);
    walk = (uint64_t *)(vas + 0x1c8);
    while ((long)pl + 0x10 <= (long)walk) {
        off = 0;
        do {
            walk = (uint64_t *)((long)pl + off + 8);
            if ((long)pl + 8 < (long)walk + 0x10 ||
                (long)(walk + 0x10) < (long)walk)
                goto fail;
            base = *walk;
            if (base == 0) break;
            idx = (long)(p - base) >> 5;
            if (idx < (long)cap) {
                store = *(uint64_t *)((long)pl + off + 0x48);
                if (*(uint64_t *)(store + 0x30) != base)
                    sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5aef1a);
                if (p < base ||
                    *(uint64_t *)(store + 0x30) +
                        (uint64_t)*(uint16_t *)(store + 0x40) * 0x20 <= p) {
                    sk_vas_fault6();            /* FUN_004b1f3c */
                } else if (idx < *(uint16_t *)(*(uint64_t *)(store + 8) + 6)) {
                    bm = *(uint64_t **)(store + 0x28);
                    cell = bm + (idx >> 6);
                    if ((long)bm <= (long)cell && (long)bm +
                        *(uint8_t *)(store + 0x42) < (long)cell + 1 &&
                        (long)(cell + 1) >= (long)cell) {
                        bit = 1UL << (((p - base) >> 5) & 0x3f);
                        if ((*cell & bit) != 0)
                            sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5af0a5);
                        *cell |= bit;
                        if ((*(uint8_t *)(store + 0x43) & 1) == 0) {
                            *(uint64_t *)(store + 0x38) = 0;
                            **(uint64_t **)(vas + 0x140) = store;
                            *(uint64_t **)(vas + 0x140) = (uint64_t *)(store + 0x38);
                            *(uint8_t *)(store + 0x43) = 1;
                        }
                        r = sk_vm_lock_release();   /* FUN_00118194 (lock vas+0x40) */
                        if (r == 0) return;
                        sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5aed68);
                    }
                    goto fail;
                }
                sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5aeff5);
            }
        } while ((off += 8) != 0x38);
        pl = (long *)*pl;
        walk = (uint64_t *)(pl + 0x10);
        if (pl == (long *)0)
            sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5af107);
    }
fail:
    SK_ASRT_PANIC(0x31770);
}
