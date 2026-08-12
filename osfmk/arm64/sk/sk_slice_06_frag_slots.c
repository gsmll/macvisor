/* sk_slice_06_frag_slots.c — VAS cap-slot allocator, RB tree and mark helpers
 * (0x34f70-0x35b98). The span-node layout used throughout (a 0x48-byte node):
 *   +0x00 bitmap[4] (4 x u64 = 256 slots of 0x40 bytes = 0x4000-byte span)
 *   +0x20 u16 slot count | +0x22 u8 AVL height
 *   +0x28 u64 base (RB key) | +0x30 u64 free-list link
 *   +0x38 u64 RB left | +0x40 u64 RB right.
 * The vspace root (fetched via sk_vas_root_get at 0x6af188) holds:
 *   +0x20 RB-tree root | +0x28 free capsnode list | +0x30 partial/spare list
 *   +0x40 u32 created count | +0x44 u32 created limit. */

#include "sk_slice_06_shared.h"

/* FUN_0005acac is the global vspace-root fetcher, but the shared header
 * declares it with an out-parameter signature; here it is called through the
 * ABI-accurate value-returning pointer type. */
static uint64_t sk_vas_root_get(void)
{
    uint64_t (*fetch)(uint64_t, uint64_t, uint64_t) =
        (uint64_t (*)(uint64_t, uint64_t, uint64_t))sk_vspace_alloc;
    return fetch(0x6af188, 4, 8);   /* FUN_0005acac(0x6af188, 4, 8) */
}

/* Full 64-bit bit-reversal (used to locate the lowest free bit of a bitmap
 * word). */
static uint64_t sk_vas_bitrev64(uint64_t x)
{
    x = ((x & 0xaaaaaaaaaaaaaaaaULL) >> 1) | ((x & 0x5555555555555555ULL) << 1);
    x = ((x & 0xccccccccccccccccULL) >> 2) | ((x & 0x3333333333333333ULL) << 2);
    x = ((x & 0xf0f0f0f0f0f0f0f0ULL) >> 4) | ((x & 0x0f0f0f0f0f0f0f0fULL) << 4);
    x = ((x & 0xff00ff00ff00ff00ULL) >> 8) | ((x & 0x00ff00ff00ff00ffULL) << 8);
    x = ((x & 0xffff0000ffff0000ULL) >> 16) | ((x & 0x0000ffff0000ffffULL) << 16);
    return (x >> 32) | (x << 32);
}

/* Cross-slice helpers not declared in the shared header (used only here). */
extern sk_vas_lock_tok_t sk_vas_span_cursor(void);   /* FUN_004b2748: {span node, cursor VA} */
extern sk_vas_lock_tok_t sk_vas_span_cursor2(void);  /* FUN_004b2780: {current ptr, value} */
extern uint64_t sk_vas_reinit_cur(void);             /* FUN_004b27b8: current VAS handle */
extern void sk_vas_alloc_fail(void);                 /* FUN_004b270c: allocation-failure hook */
extern void sk_vas_init_root(uint64_t a, uint64_t b, uint64_t c); /* FUN_0004158c */
extern void sk_vas_registry_heap(void);              /* FUN_0003c09c */
extern void sk_vas_teardown_free(void);              /* FUN_00041d9c */

/* DAT_006af190 — one-time VAS boot-init done flag. */
static uint64_t sk_vas_boot_done;

/* FUN_00034f70 @ 0x00034f70  (est. sk_vas_slot_alloc)
 * Ghidra: long FUN_00034f70(void)
 * Allocates the next free 0x40-byte capability slot. Under the VAS lock it
 * either reuses a partially-filled span node from the spare list or carves a
 * fresh span node (popped from the free capsnode list, its base and slot value
 * set via the backend +8 method), inserts it into the RB tree, then scans the
 * node's bitmap to find and set the first free bit. Returns the slot's VA.
 * Confidence: high
 * Notes: strings 0x5b1748/0x5b17aa/0x5b17f5 (alloc-fail aborts) and 0x5b1837
 *   (no-free-slot abort); bit-reverse + LZCOUNT finds the lowest free bit. */
static uint64_t sk_vas_slot_alloc(void)
{
    uint64_t root = sk_vas_root_get();
    uint64_t obj = *(uint64_t *)root;
    uint64_t lock = *(uint64_t *)(obj + 0x10);
    sk_vas_lock_tok_t tok = sk_vas_lock_acquire(lock);
    uint64_t flags = tok.flags;
    uint64_t counter = tok.counter;
    uint64_t result = 0;
    uint64_t *node = (uint64_t *)(*(uint64_t *)(root + 0x30));   /* spare list head */

    if (node == NULL) {
        if (*(uint32_t *)(root + 0x44) <= *(uint32_t *)(root + 0x40)) {
            sk_vas_lock_release(lock, (uint8_t)flags, counter);
            sk_vas_abort("vas slot_alloc: no created slots left");   /* 0x5b1748 */
        }
        /* if the VAS is already built, consult the +0x18 backend check first */
        if (((flags & 1) != 0) &&
            (result = ((uint64_t (*)(void))(*(uint64_t *)(obj + 0x18)))(), result != 0))
            goto release_and_return;
        node = (uint64_t *)sk_capslot_take();
        if (node == NULL) {
            sk_vas_lock_release(lock, (uint8_t)flags, counter);
            sk_vas_abort("vas slot_alloc: capsnode pool empty");   /* 0x5b17aa */
        }
        result = ((uint64_t (*)(void))(*(uint64_t *)(obj + 8)))();
        if (result == 0) {
            sk_capslot_push(node);
            sk_vas_lock_release(lock, (uint8_t)flags, counter);
            sk_vas_abort("vas slot_alloc: backend refused a new slot");   /* 0x5b17f5 */
        }
        node[1] = 0; node[0] = 0; node[3] = 0; node[2] = 0; node[4] = 0;
        node[5] = result;          /* base = slot value */
        node[7] = 0; node[8] = 0; node[6] = 0;
        sk_rb_insert((uint64_t *)(root + 0x20), (uint64_t)node);
        *(uint32_t *)(root + 0x40) = *(uint32_t *)(root + 0x40) + 0x100;
    } else {
        *(uint64_t *)(root + 0x30) = node[6];   /* pop spare node */
        node[6] = 0;
    }

    /* scan the span's bitmap for the lowest free 0x40 slot */
    {
        uint64_t acc = 0;
        int off;
        for (off = 0; off != 0x20; off += 8) {
            uint64_t word = *(uint64_t *)((char *)node + off);
            if (word != UINT64_MAX) {
                uint64_t idx = LZCOUNT(sk_vas_bitrev64(~word));
                *(uint64_t *)((char *)node + off) = (1ULL << (idx & 0x3f)) | word;
                uint64_t va = (node[5] + idx * 0x40) - acc;
                if (va != 0) {
                    uint16_t cnt = *(uint16_t *)(node + 4);   /* node+0x20 */
                    *(uint16_t *)(node + 4) = cnt + 1;
                    if ((uint16_t)(cnt + 1) < 0x100) {
                        node[6] = *(uint64_t *)(root + 0x30);
                        *(uint64_t *)(root + 0x30) = (uint64_t)node;
                    }
                    result = va;
                    goto release_and_return;
                }
                break;
            }
            acc -= 0x1000;
        }
    }
    sk_vas_abort("VAS abort in function slot_alloc (span bitmap full)");   /* 0x5b1837 */

release_and_return:
    sk_vas_lock_release(lock, (uint8_t)flags, counter);
    return result;
}

/* FUN_000351a0 @ 0x000351a0  (est. sk_capslot_take)
 * Ghidra: void FUN_000351a0(void)
 * Pops a free span node off the vspace root's capsnode free list (+0x28) and
 * returns it. If the list is empty, calls the root's pool-refill trampoline
 * (+0) which never returns; returns 0 in that unreachable fallthrough.
 * Confidence: high
 * Notes: free-list link is at node+0x30; bounds check else
 *   SoftwareBreakpoint(0x5519,0x35204). */
static uint64_t sk_capslot_take(void)
{
    uint64_t root = sk_vas_root_get();
    uint64_t head = *(uint64_t *)(root + 0x28);
    if (head == 0) {
        /* root+0 is a pool-refill trampoline (noreturn jump table) */
        ((void (*)(void))(*(uint64_t *)root))();
        return 0;
    }
    *(uint64_t *)(root + 0x28) = *(uint64_t *)(head + 0x30);
    if (head <= head + 0x48)
        return head;
    SK_ASRT_PANIC(0x35204);
}

/* FUN_00035204 @ 0x00035204  (est. sk_capslot_push)
 * Ghidra: void FUN_00035204(undefined8 *param_1)
 * Clears a span node's fields and pushes it onto the vspace root's capsnode
 * free list (+0x28), linking the old head via the node's +0x30 field.
 * Confidence: high */
static void sk_capslot_push(uint64_t *cap)
{
    uint64_t root = sk_vas_root_get();
    uint64_t head = *(uint64_t *)(root + 0x28);
    cap[1] = 0; cap[0] = 0; cap[3] = 0; cap[2] = 0; cap[5] = 0; cap[4] = 0;
    cap[6] = head;
    cap[7] = 0; cap[8] = 0;
    *(uint64_t *)(root + 0x28) = (uint64_t)cap;
}

/* FUN_00035254 @ 0x00035254  (est. sk_rb_insert)
 * Ghidra: void FUN_00035254(ulong *param_1,ulong param_2)
 * Inserts a span node into the AVL tree rooted at *root, keyed on the node's
 * base (+0x28); duplicate keys abort. After the recursive descent it recomputes
 * child heights and performs a single left or right rotation when the balance
 * factor exceeds +/-1, then refreshes the stored heights of the affected nodes.
 * Confidence: medium
 * Notes: recursive FUN_00035254 arg-passing is dropped by the decompiler;
 *   balance = height(left) - height(right); bounds checks else
 *   SoftwareBreakpoint(0x5519,0x353e4). */
static void sk_rb_insert(uint64_t *root, uint64_t node)
{
    uint64_t cur = *root;
    if (cur == 0) { *root = node; return; }
    if (*(uint64_t *)(cur + 0x28) == *(uint64_t *)(node + 0x28))
        sk_vas_abort("VAS abort in function rb_insert (duplicate key)");   /* 0x5b1e88 */
    if (*(uint64_t *)(node + 0x28) < *(uint64_t *)(cur + 0x28))
        sk_rb_insert((uint64_t *)(cur + 0x38), node);   /* descend left */
    else
        sk_rb_insert((uint64_t *)(cur + 0x40), node);   /* descend right */

    /* rebalance along the unwind path */
    int left_h = (*(uint64_t *)(cur + 0x38) == 0) ? 0
                 : (int)(uint8_t)(*(uint8_t *)(*(uint64_t *)(cur + 0x38) + 0x22)) + 1;
    int right_h = (*(uint64_t *)(cur + 0x40) == 0) ? 0
                  : (int)(~(uint32_t)(uint8_t)(*(uint8_t *)(*(uint64_t *)(cur + 0x40) + 0x22)));
    int bal = left_h + right_h;

    uint64_t newroot = cur;
    if (bal < -1) {                          /* right-heavy: rotate left */
        uint64_t r = *(uint64_t *)(cur + 0x40);
        if (r != 0) {
            *(uint64_t *)(cur + 0x40) = *(uint64_t *)(r + 0x38);
            *(uint64_t *)(r + 0x38) = cur;
            *root = r;
            newroot = r;
        }
    } else if (bal > 1) {                    /* left-heavy: rotate right */
        uint64_t r = *(uint64_t *)(cur + 0x38);
        if (r != 0) {
            *(uint64_t *)(cur + 0x38) = *(uint64_t *)(r + 0x40);
            *(uint64_t *)(r + 0x40) = cur;
            *root = r;
            newroot = r;
        }
    }

    /* refresh stored heights of the (possibly rotated) nodes */
    {
        int h1 = (*(uint64_t *)(cur + 0x38) == 0) ? 0
                 : (int)(uint8_t)(*(uint8_t *)(*(uint64_t *)(cur + 0x38) + 0x22)) + 1;
        int h2 = (*(uint64_t *)(cur + 0x40) == 0) ? 0
                 : (int)(uint8_t)(*(uint8_t *)(*(uint64_t *)(cur + 0x40) + 0x22)) + 1;
        *(uint8_t *)(cur + 0x22) = (uint8_t)(h1 > h2 ? h1 : h2);
        h1 = (*(uint64_t *)(newroot + 0x38) == 0) ? 0
             : (int)(uint8_t)(*(uint8_t *)(*(uint64_t *)(newroot + 0x38) + 0x22)) + 1;
        h2 = (*(uint64_t *)(newroot + 0x40) == 0) ? 0
             : (int)(uint8_t)(*(uint8_t *)(*(uint64_t *)(newroot + 0x40) + 0x22)) + 1;
        *(uint8_t *)(newroot + 0x22) = (uint8_t)(h1 > h2 ? h1 : h2);
    }
}

/* FUN_00035418 @ 0x00035418  (est. sk_rb_find)
 * Ghidra: void FUN_00035418(ulong param_1)
 * Walks the RB tree rooted at vspace-root+0x20 looking for the span node whose
 * base (+0x28) equals the caller's address masked to 0x4000 alignment. Returns
 * the matching node, or 0 if none. Traverses left when target <= key, else right.
 * Confidence: high */
static uint64_t sk_rb_find(uint64_t addr)
{
    uint64_t root = sk_vas_root_get();
    uint64_t node = *(uint64_t *)(root + 0x20);
    uint64_t target = addr & 0xffffffffffffc000ULL;
    while (node != 0) {
        if (*(uint64_t *)(node + 0x28) == target)
            return node;
        node = *(uint64_t *)(node + (target <= *(uint64_t *)(node + 0x28) ? 0x38 : 0x40));
    }
    return 0;
}

/* FUN_0003548c @ 0x0003548c  (est. sk_vas_slot_alloc_range)
 * Ghidra: ulong FUN_0003548c(long param_1,ulong param_2,ulong param_3)
 * Allocates a run of 0x40-byte cap slots. va and total must be 0x4000-aligned
 * and total >= n. When the VAS is already built (lock bit 0), marks a single
 * slot at the current span cursor and returns whether it was newly free;
 * otherwise it carves one or more span nodes (up to 256 slots each) from the
 * capsnode pool, marks each slot's bitmap bit, inserts them into the RB tree
 * and links non-full nodes into the spare list, advancing va by 0x4000 per
 * span until total is exhausted.
 * Confidence: medium
 * Notes: strings 0x5b1a12/0x5b1a80/0x5b1f02/0x5b1b9e; FUN_004b270c on pool
 *   exhaustion; returns the lock-release result in the slow path. */
static uint64_t sk_vas_slot_alloc_range(uint64_t va, uint64_t n, uint64_t total)
{
    uint64_t root = sk_vas_root_get();
    if ((((uint32_t)total | (uint32_t)va) & 0x3fff) != 0)
        sk_vas_abort("VAS abort in function slot_alloc_range (misaligned)");   /* 0x5b1a12 */
    if (total < n)
        sk_vas_abort("VAS abort in function slot_alloc_range (range over total)");   /* 0x5b1a80 */
    uint64_t obj = *(uint64_t *)root;
    uint64_t lock = *(uint64_t *)(obj + 0x10);
    sk_vas_lock_tok_t tok = sk_vas_lock_acquire(lock);

    if ((tok.flags & 1) != 0) {
        /* VAS already built: allocate a single slot from the current span cursor */
        sk_vas_lock_tok_t cur = sk_vas_span_cursor();   /* FUN_004b2748 */
        return (uint64_t)sk_capslot_mark((uint64_t *)cur.flags, cur.counter);
    }

    if (total != 0) {
        do {
            uint64_t node = sk_capslot_take();
            if (node == 0) {
                sk_vas_alloc_fail();                    /* FUN_004b270c */
                sk_vas_abort("VAS abort in function slot_alloc_range (no node)");
            }
            sk_mem_zero((void *)node, 0, 0x48);
            *(uint64_t *)(node + 0x28) = va;            /* base */
            uint64_t slots = (n < 0x100) ? n : 0x100;
            if (n != 0) {
                uint64_t i = slots;
                uint64_t a = va;
                do {
                    if (!sk_capslot_mark((uint64_t *)node, a))
                        sk_vas_abort("VAS abort in function slot_alloc_range (mark)");   /* 0x5b1b9e */
                    a += 0x40;
                    i -= 1;
                } while (i != 0);
            }
            sk_rb_insert((uint64_t *)(root + 0x20), node);
            if (*(uint16_t *)(node + 0x20) < 0x100) {   /* not full: link into spare list */
                *(uint64_t *)(node + 0x30) = *(uint64_t *)(root + 0x30);
                *(uint64_t *)(root + 0x30) = node;
            }
            va += 0x4000;
            n -= slots;
            total -= 0x4000;
        } while (total != 0);
    }
    sk_vas_lock_release(lock, (uint8_t)tok.flags, tok.counter);
    return 0;   /* release returns void here; the caller ignores the value */
}

/* FUN_00035684 @ 0x00035684  (est. sk_capslot_mark)
 * Ghidra: bool FUN_00035684(ulong *param_1,long param_2)
 * Marks the bitmap bit for the 0x40-byte slot at va within a span node. Returns
 * true if the bit was previously clear (newly allocated), false if already set.
 * Aborts if va falls outside the node's 0x4000-byte span.
 * Confidence: high
 * Notes: offset = va - node->base; bit word at node+(offset>>12),
 *   bit = 1<<((offset>>6)&0x3f); count at node+0x20; else
 *   SoftwareBreakpoint(0x5519,0x356f0). */
static bool sk_capslot_mark(uint64_t *cap, uint64_t va)
{
    uint64_t offset = va - cap[5];
    if (offset >> 0xe != 0)
        sk_vas_abort("VAS abort in function capslot_mark (offset out of span)");   /* 0x5b1f02 */
    uint64_t *count = cap + 4;                  /* node+0x20 */
    uint64_t *word = cap + (offset >> 0xc);
    uint64_t bit = 1ULL << ((offset >> 6) & 0x3f);
    uint64_t w = *word;
    uint64_t was = w & bit;
    if (was == 0) {
        *(uint16_t *)count = (uint16_t)(*(uint16_t *)count + 1);
        *word = w | bit;
    }
    return was == 0;
}

/* FUN_0003573c @ 0x0003573c  (est. sk_vas_mark_cap_slots)
 * Ghidra: void FUN_0003573c(ulong param_1,long param_2,undefined8 param_3,undefined8 param_4)
 * Marks every 0x40-byte cap slot in [va, va+n) as allocated, using the RB-tree
 * span nodes. When the VAS lock is already held it routes through a callback
 * descriptor (sk_vas_mark_cb) or a VAS reinit; otherwise it walks the range,
 * re-finding the containing span node as va advances past each node's 0x4000
 * end, marking each slot, and unlinking any node that becomes full (count==0x100)
 * from the spare list.
 * Confidence: medium
 * Notes: strings 0x5b1c12/0x5b1caf; SoftwareBreakpoint(0x5519,0x358e0) bounds
 *   checks elided (dead pointer-overflow guards). */
static void sk_vas_mark_cap_slots(uint64_t va, uint64_t n, uint64_t a3, uint64_t a4)
{
    uint64_t root = sk_vas_root_get();
    if ((va & 0x3f) != 0)
        sk_vas_abort("vas mark_cap_slots: misaligned start");   /* 0x5b1c12 */
    uint64_t end = n + va;
    if (end > (UINT64_MAX - 0x40) || end < va)
        sk_vas_abort("vas mark_cap_slots: end > SIZE_MAX (L4 CapSize)");   /* 0x5b1caf */
    uint64_t obj = *(uint64_t *)root;
    uint64_t lock = *(uint64_t *)(obj + 0x10);
    sk_vas_lock_tok_t tok = sk_vas_lock_acquire(lock);

    if ((tok.flags & 1) != 0) {
        /* already-locked fast path */
        sk_vas_lock_tok_t cur = sk_vas_span_cursor2();   /* FUN_004b2780 */
        if (cur.flags != 0) {
            uint8_t desc[0x30];
            *(uint16_t *)(desc + 0x0) = 0x100;
            *(uint32_t *)(desc + 0x2) = 0;
            *(uint16_t *)(desc + 0x6) = 0;
            *(uint64_t *)(desc + 0x8) = cur.flags;
            *(uint64_t *)(desc + 0x10) = 0;
            *(uint64_t *)(desc + 0x18) = a4;
            *(uint64_t *)(desc + 0x20) = (uint64_t)sk_vas_mark_cb;
            *(uint64_t *)(desc + 0x28) = (uint64_t)desc;   /* callback stack */
            sk_vas_new((char *)desc, 0, cur.counter, 8);
            return;
        }
        uint64_t v = sk_vas_reinit_cur();   /* FUN_004b27b8 */
        sk_vas_reinit(v, 8, a4);
        return;
    }

    /* mark each 0x40 slot into its containing span node */
    uint64_t node = sk_rb_find(va);
    while (va < end) {
        uint64_t next = va + 0x40;
        if (node == 0 || (*(uint64_t *)(node + 0x28) + 0x4000ULL <= va)) {
            node = sk_rb_find(va);
            if (node == 0) {
                uint64_t adj = (next & 0x3fff) ? 0x4000 : 0;
                va = (next & 0xffffffffffffc000ULL) + adj;
                continue;
            }
        }
        bool ok = sk_capslot_mark((uint64_t *)node, va);
        va = next;
        if (ok && (uint16_t)(*(uint16_t *)(node + 0x20)) == 0x100) {
            /* node became full: unlink it from the spare/partial list */
            uint64_t walk = root;
            uint64_t *link_slot = NULL;
            uint64_t nxt;
            do {
                link_slot = (uint64_t *)(walk + 0x30);
                nxt = *link_slot;
                walk = nxt;
            } while (walk != 0 && walk != node);
            if (walk == node)
                *link_slot = *(uint64_t *)(node + 0x30);
        }
    }
    sk_vas_lock_release(lock, (uint8_t)tok.flags, tok.counter);
}

/* FUN_00035944 @ 0x00035944  (est. sk_vas_mark_cb)
 * Ghidra: void FUN_00035944(long param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)
 * Mark helper callback. When a base is supplied, it builds a VAS descriptor
 * (tag 0x100, base at +0x10, extra at +0x18) and hands it to sk_vas_new;
 * otherwise it reinitialises the current VAS with (param_3, param_4).
 * Confidence: medium
 * Notes: descriptor fields byte-packed per the Ghidra stack frame. */
static void sk_vas_mark_cb(uint64_t a, uint64_t b, uint64_t c, uint64_t d)
{
    if (a != 0) {
        uint8_t desc[0x20];
        *(uint16_t *)(desc + 0x0) = 0x100;
        *(uint32_t *)(desc + 0x2) = 0;
        *(uint16_t *)(desc + 0x6) = 0;
        *(uint64_t *)(desc + 0x8) = 0;
        *(uint64_t *)(desc + 0x10) = a;   /* base */
        *(uint64_t *)(desc + 0x18) = d;
        sk_vas_new((char *)desc, 0, b, c);
        return;
    }
    uint64_t v = sk_vas_reinit_cur();   /* FUN_004b27b8 */
    sk_vas_reinit(v, c, d);
}

/* FUN_000359a0 @ 0x000359a0  (est. sk_vas_reinit_thunk)
 * Ghidra: void FUN_000359a0(undefined8,undefined8,undefined8,undefined8)
 * Thin thunk that forwards (a, c, d) to sk_vas_reinit.
 * Confidence: high (trivial wrapper) */
static void sk_vas_reinit_thunk(uint64_t a, uint64_t b, uint64_t c, uint64_t d)
{
    (void)b;
    sk_vas_reinit(a, c, d);
}

/* FUN_000359ac @ 0x000359ac  (est. sk_vas_set)
 * Ghidra: void FUN_000359ac(undefined8 param_1)
 * Stores a VAS handle into the registry object at +0x20.
 * Confidence: high */
static void sk_vas_set(uint64_t v)
{
    uint64_t *reg = sk_vas_registry();   /* FUN_00032514 */
    reg[4] = v;
}

/* FUN_000359d4 @ 0x000359d4  (est. sk_vas_destroy_check)
 * Ghidra: void FUN_000359d4(long param_1,long param_2)
 * Guards VAS destruction: the kind tag must equal 0x65b5c8, and the target VAS
 * must not be the root object (sk_vas_obj_root). Non-root VASes are torn down
 * via sk_vas_destroy; destroying the root aborts.
 * Confidence: high
 * Notes: magic 0x65b5c8; strings 0x5b1fef/0x5b2057. */
static void sk_vas_destroy_check(uint64_t vas, uint64_t kind)
{
    if (kind != 0x65b5c8)
        sk_vas_abort("VAS abort in function destroy_check (bad kind)");   /* 0x5b1fef */
    sk_vas_lock_tok_t t = sk_vas_obj_root();   /* FUN_00034a2c */
    if (t.flags != vas) {
        sk_vas_destroy((uint64_t *)vas);       /* FUN_00032774 */
        return;
    }
    sk_vas_abort("VAS abort in function destroy_check (destroying root)");   /* 0x5b2057 */
}

/* FUN_00035a78 @ 0x00035a78  (est. sk_vas_boot_init)
 * Ghidra: void FUN_00035a78(long param_1,long param_2,long param_3)
 * One-time boot-time initialisation of the VAS subsystem, guarded by a global
 * done flag (DAT_006af190). Runs global init, root-VAS init, registry init and
 * heap init, exercises the slot allocator over [a, b) plus c*0x40 slots, tears
 * the allocation back down, and allocates a bootstrap region via the trap
 * allocator (kind 0x1000001).
 * Confidence: medium
 * Notes: strings 0x5b20a7; helper calls FUN_0004158c/FUN_0003c09c/
 *   FUN_00041d9c are declared extern here. */
static void sk_vas_boot_init(uint64_t a, uint64_t b, uint64_t c)
{
    if ((sk_vas_boot_done & 1) == 0) {
        sk_vas_global_init();                       /* FUN_00031868 */
        sk_vas_init_root(a, b, c);                  /* FUN_0004158c */
        sk_vas_registry_init();                     /* FUN_00033780 */
        sk_vas_registry_heap();                     /* FUN_0003c09c */
        uint64_t total = (b - a) + c * 0x40;
        sk_vas_slot_alloc_range(a, b - a, total);   /* FUN_0003548c */
        sk_vas_teardown_free();                     /* FUN_00041d9c */

        uint8_t in[0x18];
        *(uint8_t *)(in + 0x0) = 4;
        *(uint32_t *)(in + 0x1) = 0;
        *(uint8_t *)(in + 0x5) = 0;
        *(uint64_t *)(in + 0x8) = a;
        *(uint64_t *)(in + 0x10) = total;
        uint8_t out[0x10] = { 0 };
        uint8_t err = sk_trap_alloc_region(0x1000001, in, out, 0, 0);   /* FUN_0003c510 */
        if (err != 0)
            sk_vas_abort("VAS abort in function boot_init (trap alloc failed)");   /* 0x5b20a7 */
        sk_vas_heap_init();                         /* FUN_00033bb0 */
        sk_vas_boot_done = 1;
    }
}

/* FUN_00035b98 @ 0x00035b98  (est. sk_capslot_alloc_zero)
 * Ghidra: undefined8 FUN_00035b98(void)
 * Returns 0 (the null capability slot) unconditionally.
 * Confidence: high (trivial constant return) */
static uint64_t sk_capslot_alloc_zero(void)
{
    return 0;
}
