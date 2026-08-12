/* Recreated from the cL4 Secure Kernel VAS-subsystem slice (region
 * 0x0002ee90-0x00038184). Ground truth: Ghidra FUN_ names + addresses. All
 * names are estimates unless string/header matched. */
#include "sk_slice_06_shared.h"

/* Slot-word encoding used throughout the VAS slot manager:
 *   bits[1:0]  present/occupancy state (0 = empty, 1 = occupied)
 *   bits[5:2]  kind nibble (array class: 1=?, 2=span, 3=cap-slot)
 *   bits[23:6] count (number of entries held in the array / span)
 *   bits[63:28] pointer to the referenced array/span. */

/* FUN_000347c4 — allocate a fresh cap-slot array node from the cap-slot pool
 * and return its base pointer. The shared-header declaration `sk_capslot_alloc`
 * (frag_lock.c) models this as returning void, but the callers in this slice
 * (incl. sk_vas_span_alloc) consume the allocated node pointer, so this
 * fragment uses its own extern with the corrected (pointer) signature. */
extern uint64_t *sk_capslot_alloc_p(void);                 /* FUN_000347c4 */

/* 8-byte bitmask at 0x4bc1e0 used by the span-compaction merge to clear a
 * pair of slot words byte-wise. */
extern uint64_t sk_slot_mask_4bc1e0;                       /* DAT_004bc1e0 */

/* FUN_00036d58 @ 0x00036d58  (est. sk_vas_cap_alloc_slot)
 * Ghidra: void FUN_00036d58(long param_1, undefined8 param_2)
 * Allocates a capability slot for `cap` by delegating to sk_vas_span_alloc on
 * the given slot array, then validates that the returned span (out[3]) is a
 * well-formed 0x40..0x80-byte array. On any bounds/overflow violation the
 * assertion trap fires. The 4-word scratch buffer is passed to the allocator
 * as its result block.
 * Confidence: medium
 * Notes: Bounds assertion renders as SoftwareBreakpoint(0x5519,0x36dec). The
 *   +0x40 / >0x38 arithmetic mirrors the "valid 8-slot array" predicate. */
static void sk_vas_cap_alloc_slot(uint64_t slots, uint64_t cap)
{
    uint64_t end = (slots != 0) ? slots + 0x40 : 0;
    uint64_t out[4];
    uint64_t span;
    uint64_t span_end;
    uint64_t end2;

    if (slots + 8 <= end) {
        out[0] = 0; out[1] = 0; out[2] = 0; out[3] = 0;
        /* The slot array must be null or at least 0x40 bytes (8 slots). */
        if (slots == 0 || 0x38 < end - slots) {
            sk_vas_span_alloc(out, (uint64_t *)slots, (uint32_t)cap, 0);
            span = out[3];
            span_end = span + 0x40;
            if (span <= span_end && (span == 0 || 0x38 < span_end - span)) {
                end2 = (span != 0) ? span_end : 0;
                if (span <= end2 && (span == 0 || 0x38 < end2 - span))
                    return;
            }
        }
    }
    SK_ASRT_PANIC(0x36dec);
}

/* FUN_00036dec @ 0x00036dec  (est. sk_vas_span_alloc)
 * Ghidra: void FUN_00036dec(ulong *param_1,ulong *param_2,uint param_3,ulong param_4)
 * Allocates a span of the requested `kind` inside the slot array `slots`,
 * writing a 4-word descriptor into `out` (out[0..1]=0, out[2]=count,
 * out[3]=the array/span root). Span arrays (kind 4/8) walk to the first slot
 * whose count is zero or exceeds the request, recursing into that sub-span;
 * cap-slot arrays (kind 0xc) delegate to sk_vas_cap_insert. When a fresh node
 * is required the trailing occupied slots are relocated into a new cap-slot
 * array and, unless `flag&1`, a wrapper node is built linking the old array.
 * Confidence: high
 * Notes: Recursion is FUN_00036dec; sk_vas_cap_insert = FUN_00036bd4;
 *   sk_capslot_alloc_p = FUN_000347c4; assertion @ 0x36ffc. */
static void sk_vas_span_alloc(uint64_t *out, uint64_t *slots, uint32_t kind, uint64_t flag)
{
    uint64_t *end;          /* slots + 8 */
    uint64_t *end2;         /* NULL or slots + 8 */
    uint64_t *slot;         /* current slot */
    uint64_t *slot2;        /* secondary slot */
    uint64_t *node;         /* fresh cap-slot array */
    uint64_t *node_end;     /* node + 8 */
    uint64_t *wrap;         /* two-level wrapper node */
    uint64_t *wrap_end;     /* wrap + 8 */
    uint64_t *dst;          /* relocation source/dest */
    uint64_t *src;
    uint64_t child_span;    /* slots[slot_idx] ptr field */
    uint64_t child_end;     /* child_span + 0x40 */
    uint64_t carry;         /* trailing ptr propagated while clearing kinds */
    uint64_t local_out[4];  /* recursive result block */
    uint64_t word;          /* slot word */
    uint32_t slot_idx;      /* 0..7 */
    uint32_t new_kind;      /* kind nibble to install */
    uint32_t count;         /* count field extracted from a slot word */
    uint64_t i;             /* relocation loop byte offset */
    sk_vas_lock_tok_t tok;  /* cap-insert result */

    end = slots + 8;
    end2 = (slots != NULL) ? end : NULL;
    if (end2 < slots + 1) goto panic;

    word = *slots & 0x3c;
    if (word == 4 || word == 8) {
        /* ---- span slot array ---- */
        slot_idx = 0;
        slot = slots;
        do {
            if (slot < slots || end2 < slot + 1 || slot + 1 < slot) goto panic;
        } while ((*slot & 0xfffffc0) != 0 &&
                 ((uint32_t)(*slot >> 6) & 0x3fffff) <= (kind >> 6 & 0x3fffff) &&
                 (slot_idx++, slot++, slot_idx != 7));

        slot = slots + (slot_idx & 0xff);
        if (slot < slots || end2 < slot + 1 || slot + 1 < slot) goto panic;

        /* The chosen slot's ptr is the child span to recurse into. */
        child_span = *slot >> 0x1c;
        child_end = child_span + 0x40;
        if (child_end < (*slot >> 0x1c) ||
            (child_span != 0 && child_end - child_span < 0x39)) goto panic;
        carry = (child_span != 0) ? child_end : 0;

        local_out[0] = 0; local_out[1] = 0; local_out[2] = 0; local_out[3] = 0;
        if (carry < child_span || (child_span != 0 && carry - child_span < 0x39))
            goto panic;

        /* Recurse into the sub-span; on success the sub-span is the new root. */
        sk_vas_span_alloc(local_out, (uint64_t *)child_span, kind, 1);
        if ((int)local_out[2] == 0) {
            *slot = *slot & 0xfffffff | local_out[3] << 0x1c;
            goto success_slots;
        }

        {
            uint64_t *tail = slots + 7;      /* slots[7] */
            uint64_t tail_word;
            uint64_t orig_slot_word;         /* uVar18 */
            uint64_t slot_word;              /* uVar17 */

            if (end2 < tail || tail < slots) goto panic;
            tail_word = *tail;
            orig_slot_word = *slot;
            slot_word = orig_slot_word;
            if ((slot_idx & 0xff) < 7) {
                /* Clear the kind nibble of the trailing slots (7 down to
                 * slot_idx+1), propagating the last present slot's ptr. */
                uint64_t *p = slots + 6;
                uint32_t k = 7;
                carry = 0;
                do {
                    uint64_t *q = p + 1;
                    uint64_t w = *q;
                    uint64_t v = w >> 0x1c;
                    if ((w & 0xfffffc0) != 0 || carry != 0) v = carry;
                    if ((w & 3) == 1) carry = v;
                    if (p < slots || end2 < q || q < p) goto panic;
                    p[1] = *p & 0xffffffffffffffc3;
                    k--;
                    p--;
                } while ((slot_idx & 0xff) < (k & 0xff));
                slot_word = *slot;
            } else {
                carry = 0;
                slot_word = orig_slot_word;
            }

            /* Stash the sub-allocation's count into the chosen slot. */
            *slot = slot_word & 0xfffffffff0000000 | slot_word & 0x3f |
                    (local_out[2] & 0x3fffff) << 6;
            if ((tail_word & 3) == 0 || (orig_slot_word & 0xfffffc0) != 0) {
                /* If slots[7] is empty, or the chosen slot carried a count,
                 * record the sub-span as a fresh entry one past the slot. */
                if (slot < slots || end2 < slot + 2 || slot + 2 < slot) goto panic;
                slot[1] = slot[1] & 0xffffffc | local_out[3] << 0x1c | 1;
                if ((tail_word & 3) == 0) goto success_slots;
                word = carry;               /* uVar17 = uVar23 */
            } else {
                word = local_out[3];        /* uVar17 = local_58 (sub-span) */
            }
        }
        /* Fall through to relocate the trailing slots into a fresh node. */
    } else if (word == 0xc) {
        /* ---- cap-slot array: delegate to the ordered insert ---- */
        {
            uint64_t *cap6 = slots + 6;
            uint64_t *cap7 = slots + 7;
            if (cap6 < slots || end < cap7 || cap7 < cap6) goto panic;
            if ((*cap6 & 3) == 0) {
                tok = sk_vas_cap_insert(slots, kind, 7, 0);  /* FUN_00036bd4 */
                if ((tok.flags & 0xff) == 0) goto success_slots;
                goto store_cap_err;
            }
            if (cap7 < slots) goto panic;
            word = slots[7];
            tok = sk_vas_cap_insert(slots, kind, 8, 1);      /* FUN_00036bd4 */
            if ((tok.flags & 0xff) != 0) goto store_cap_err;
            word = word >> 0x1c;                             /* slots[7] ptr */
        }
    } else {
        word = 0;
    }

    /* ---- relocate the trailing occupied slots into a fresh cap-slot node ---- */
    node = sk_capslot_alloc_p();                             /* FUN_000347c4 */
    node_end = node + 8;
    end2 = (node != NULL) ? node_end : NULL;
    new_kind = (uint8_t)(*slots >> 2) & 0xf;
    new_kind = (new_kind == 1) ? 2 : new_kind;

    if (new_kind == 3) {
        /* Cap-slot layout: move slots[4..7] (4 words) into the node. */
        for (i = 0; i != 0x20; i += 8) {
            dst = (uint64_t *)((char *)node + i);
            src = (uint64_t *)((char *)slots + i + 0x20);
            if (dst < node || end2 < dst + 1 || dst + 1 < dst ||
                src < slots || end < src + 1 || src + 1 < src) goto panic;
            *dst = *src & 0xfffffffffffffffc | 1;
            *src = 0;
        }
        slot = slots + 7;
        if (end < slot || slot < slots) goto panic;
        *slot = *slot & 0xfffffff | (uint64_t)node << 0x1c;  /* slots[7] ptr = node */
        if (node + 7 < node || node_end < node + 7) goto panic;
        node[7] = node[7] & 0xfffffff | word << 0x1c;        /* node[7] ptr = word */
        if (node_end < node + 1) goto panic;
        word = *node;
    } else {
        /* Span layout: move slots[5..7] (3 words) into the node. */
        for (i = 0; i != 0x18; i += 8) {
            dst = (uint64_t *)((char *)node + i);
            src = (uint64_t *)((char *)slots + i + 0x28);
            if (dst < node || end2 < dst + 1 || dst + 1 < dst ||
                src < slots || end < src + 1 || src + 1 < src) goto panic;
            *dst = *src & 0xffffffffffffffc0 | 1;
            *src = 0;
        }
        if (node + 4 < node + 3 || node_end < node + 4 || node + 3 < node) goto panic;
        node[3] = word << 0x1c | 1;                          /* node[3] ptr = word */
        src = slots + 4;
        if (src < slots || end < src + 1 || src + 1 < src) goto panic;
        word = *src;
        *src = word & 0xfffffffff000003f;                    /* clear count of slots[4] */
    }

    *slots = *slots & 0xffffffffffffffc3 | (uint64_t)new_kind << 2;
    if (node + 1 <= node_end) {
        count = (uint32_t)(word >> 6) & 0x3fffff;
        *node = *node & 0xffffffffffffffc3 | (uint64_t)new_kind << 2;
        if ((flag & 1) != 0) {
            /* Single-level result: the fresh node is the root. */
            out[0] = 0; out[1] = 0; out[2] = count; out[3] = (uint64_t)node;
            return;
        }
        /* Two-level result: build a wrapper node linking the old array. */
        wrap = sk_capslot_alloc_p();                         /* FUN_000347c4 */
        wrap_end = (wrap != NULL) ? wrap + 8 : NULL;
        if (wrap <= wrap + 1 && wrap + 1 <= wrap_end) {
            *wrap = (uint64_t)(count << 6 | 5) | (uint64_t)slots << 0x1c;
            if (wrap + 1 <= wrap + 2 && wrap + 2 <= wrap_end) {
                wrap[1] = (uint64_t)node << 0x1c | 1;
                out[0] = 0; out[1] = 0; out[2] = 0; out[3] = (uint64_t)wrap;
                return;
            }
        }
    }
    goto panic;

store_cap_err:
    out[0] = tok.flags;
    out[1] = tok.counter;
    out[2] = 0;
    out[3] = 0;
    return;

success_slots:
    out[0] = 0; out[1] = 0; out[2] = 0; out[3] = (uint64_t)slots;
    return;

panic:
    SK_ASRT_PANIC(0x36ffc);
}

/* FUN_0003730c @ 0x0003730c  (est. sk_vas_slot_remove)
 * Ghidra: uint FUN_0003730c(ulong *param_1,uint param_2,uint param_3)
 * Removes the slot at index `idx` from an 8-slot array and compacts the array
 * leftward: each following occupied slot is copied one position down, and the
 * top slot (index n-1) is cleared. Returns the index of the last entry that
 * was shifted (mod 256). Bounds violations raise the assertion trap.
 * Confidence: medium
 * Notes: Bounds assertion renders as SoftwareBreakpoint(0x5519,0x373a4). */
static uint32_t sk_vas_slot_remove(uint64_t *slots, uint32_t idx, uint32_t n)
{
    uint64_t *end = (slots != NULL) ? slots + 8 : NULL;
    uint64_t *slot = slots + idx;
    uint32_t cur = idx;
    uint32_t src_idx;

    if ((slots <= slot && slot + 1 <= end) && slot <= slot + 1) {
        *slot = 0;                       /* clear the removed slot */
        do {
            src_idx = cur;
            cur = src_idx + 1;
            if (n <= (cur & 0xff)) break;
            slot = slots + (cur & 0xff);
            {
                uint64_t *prev = slot - 1;
                uint64_t *next = slot + 1;
                if (prev < slots || end < slot || slot < prev ||
                    end < next || next != end || next <= slot) goto panic;
            }
            slot[-1] = *slot;            /* slots[cur-1] = slots[cur] */
        } while ((*slot & 3) != 0);      /* keep shifting while a present slot moves */

        slot = slots + (n - 1);
        if ((slots <= slot && slot + 1 <= end) && slot <= slot + 1) {
            *slot = 0;                   /* clear the vacated top slot */
            return src_idx & 0xff;
        }
    }
panic:
    SK_ASRT_PANIC(0x373a4);
}

/* FUN_000373a4 @ 0x000373a4  (est. sk_vas_slot_compact)
 * Ghidra: undefined1 [16] FUN_000373a4(ulong *param_1,uint param_2,code *param_3)
 * Compacts a slot array, returning a 16-byte {flags, root} pair. Cap-slot
 * arrays (kind 0xc) locate the slot whose count equals `kind`, invoke the
 * optional callback on its ptr, and remove it. Span arrays recurse into the
 * child span at the first under-full slot, then merge the compacted child with
 * a neighbouring array (left or right) so the array stays dense: surplus
 * entries are shifted into the survivor with sk_memmove, the absorbed array is
 * freed, the emptied slot is removed, and the survivor becomes the new root.
 * Confidence: medium
 * Notes: Recursion is FUN_000373a4; sk_vas_slot_remove = FUN_0003730c;
 *   sk_capslot_free = FUN_0003481c; sk_memmove = FUN_00117d14; the merge clears
 *   two slot words byte-wise with the mask DAT_004bc1e0; assertion @ 0x379ac.
 *   The decompiler reuses registers (extraout_x1 / puVar16/puVar21) between the
 *   left/right merge paths; the roles (survivor = `target`, absorbed = `source`)
 *   are reconstructed accordingly. */
static sk_vas_lock_tok_t sk_vas_slot_compact(uint64_t *slots, uint32_t kind, void (*cb)(uint64_t))
{
    uint64_t *end;          /* slots + 8 */
    uint64_t *end2;         /* NULL or child_end */
    uint64_t *slot;
    uint64_t *slot2;
    uint64_t *target;       /* surviving array after a merge */
    uint64_t *target_end;
    uint64_t *source;       /* array absorbed into the survivor */
    uint64_t *source_end;
    uint64_t *child;        /* recursively compacted child span */
    uint64_t *child_end;
    uint64_t *span;         /* neighbour span array */
    uint64_t *span_end;
    uint64_t *span_cap;     /* NULL or span_end */
    uint64_t slot_word;
    uint64_t child_span;
    uint64_t child_span_end;
    uint64_t child_end_cap;
    uint64_t dist;          /* span_end - span */
    uint64_t byte_len;      /* occupied byte length */
    uint64_t last_word;     /* slot word being rotated across arrays */
    uint64_t mask;
    uint32_t count_slots;   /* number of leading occupied slots */
    uint32_t slot_idx;
    uint32_t lo_slot;       /* slot index to the left of the child */
    uint32_t hi_slot;       /* slot index to the right of the child */
    uint32_t status;
    uint32_t removed;
    uint32_t kind_save;
    uint32_t child_kind;
    uint8_t  occ_byte;
    long occ;               /* negative occupancy while scanning */
    long tail;              /* first-empty offset */
    uint64_t cur;           /* current neighbour index (lo, then hi) */
    uint64_t i;
    bool keep;
    bool next;
    sk_vas_lock_tok_t sub;

    end = (slots != NULL) ? slots + 8 : NULL;
    if (end < slots + 1) goto panic;

    slot_word = *slots;
    if ((slot_word & 0x3c) == 0xc) {
        /* ---- cap-slot array: remove the slot whose count equals `kind` ---- */
        uint32_t i2 = 0;
        status = 1;
        kind_save = 0xc;
        do {
            if (((uint32_t)(slots[i2] >> 6) & 0x3fffff) == kind) {
                if (cb == NULL) {
                    kind_save = 0xc;
                } else {
                    cb(slots[i2] >> 0x1c);
                    slot_word = *slots;
                    kind_save = slot_word & 0x3c;
                }
                *slots = slot_word & 0xffffffffffffffc3;
                removed = sk_vas_slot_remove(slots, i2 & 0xff, 7);
                *slots = (*slots & 0xffffffffffffffc3) | kind_save;
                status = 2;
                if (2 < removed) status = 3;
                break;
            }
            i2++;
        } while (i2 != 7);
        return (sk_vas_lock_tok_t){ status, (uint64_t)slots };
    }

    /* ---- span array: locate the child span at the first under-full slot ---- */
    count_slots = 0;
    slot = slots;
    do {
        if (slot < slots || end < slot + 1 || slot + 1 < slot) goto panic;
    } while ((*slot & 0xfffffc0) != 0 &&
             ((uint32_t)(*slot >> 6) & 0x3fffff) <= kind &&
             (count_slots++, slot++, count_slots != 8));
    slot_idx = count_slots & 0xff;

    slot = slots + slot_idx;
    if (slot < slots || end < slot + 1 || slot + 1 < slot) goto panic;
    child_span = *slot >> 0x1c;
    child_span_end = child_span + 0x40;
    if (child_span_end < (*slot >> 0x1c) ||
        (child_span != 0 && child_span_end - child_span < 0x39)) goto panic;
    child_end_cap = (child_span != 0) ? child_span_end : 0;
    if (child_end_cap < child_span ||
        (child_span != 0 && child_end_cap - child_span < 0x39)) goto panic;

    /* Recurse into the child span; the returned counter is its new root. */
    sub = sk_vas_slot_compact((uint64_t *)child_span, 0, NULL);
    *slot = (*slot & 0xfffffff) | sub.counter << 0x1c;
    child = (uint64_t *)sub.counter;
    child_end = child + 8;
    end2 = (child != NULL) ? child_end : NULL;
    if (sub.flags == 3) { status = 3; goto ret; }
    if (sub.flags == 1) { status = 1; goto ret; }

    lo_slot = slot_idx - 1;
    hi_slot = slot_idx + 1;
    tail = 7;
    cur = lo_slot;
    keep = true;
    do {
        next = keep;
        if ((uint32_t)cur < 8) {
            slot = slots + cur;
            if (slot < slots || end < slot + 1 || slot + 1 < slot) goto panic;
            slot_word = *slot;
            if ((slot_word & 3) == 1) {
                /* A present neighbour span: measure its occupancy. */
                span = (uint64_t *)(slot_word >> 0x1c);
                span_end = span + 8;
                if (span_end < span || (span != NULL && span_end - span < 0x39))
                    goto panic;
                span_cap = (span != NULL) ? span_end : NULL;
                dist = (uint64_t)span_cap - (uint64_t)span;
                if (span_cap < span || (span != NULL && dist < 0x39)) goto panic;
                occ = 0;
                slot2 = span;
                while (true) {
                    if (slot2 < span || span_cap < slot2 + 1 || slot2 + 1 < slot2)
                        goto panic;
                    if ((*slot2 & 0xfffffc0) == 0) break;   /* first empty slot */
                    occ--;
                    slot2++;
                    if (occ == -7) goto merge_big;          /* span full */
                }
                if (3 < (uint64_t)-occ) { tail = -occ; goto merge_big; }
            }
        }
        cur = hi_slot;
        keep = false;
    } while (next);

    /* ---- merge the child with a neighbour array ---- */
    target = NULL; target_end = NULL;
    source = NULL; source_end = NULL;
    if ((count_slots & 0xff) == 0) {
        /* No leading slots: examine the right neighbour. */
        slot = slots + hi_slot;
        if (slot < slots || end < slot + 1 || slot + 1 < slot) goto panic;
        slot_word = *slot;
        if ((slot_word & 3) == 1) {
            /* Absorb slots[hi].ptr into the child. */
            source = (uint64_t *)(slot_word >> 0x1c);
            source_end = source + 8;
            if (source_end < source || (source != NULL && source_end - source < 0x39))
                goto panic;
            target = child;
            target_end = child_end;
            lo_slot = count_slots & 0xff;
            goto do_merge;
        }
        goto no_merge;
    } else {
        /* Examine the left neighbour. */
        slot = slots + lo_slot;
        if (slot < slots || end < slot + 1 || slot + 1 < slot) goto panic;
        slot_word = *slot;
        if ((slot_word & 3) != 1) {
            if ((count_slots & 0xff) < 7) {
                slot = slots + hi_slot;
                if (slot < slots || end < slot + 1 || slot + 1 < slot) goto panic;
                slot_word = *slot;
                if ((slot_word & 3) == 1) {
                    source = (uint64_t *)(slot_word >> 0x1c);
                    source_end = source + 8;
                    if (source_end < source ||
                        (source != NULL && source_end - source < 0x39)) goto panic;
                    target = child;
                    target_end = child_end;
                    lo_slot = count_slots & 0xff;
                    goto do_merge;
                }
            }
            goto no_merge;
        }
        /* Absorb the child into slots[lo].ptr. */
        source = child;
        source_end = child_end;
        target = (uint64_t *)(slot_word >> 0x1c);
        target_end = target + 8;
        if (target_end < target || (target != NULL && target_end - target < 0x39))
            goto panic;
        hi_slot = count_slots & 0xff;
        goto do_merge;
    }

no_merge:
    target = NULL;
    target_end = NULL;

do_merge:
    if (target != NULL && source != NULL) {
        if (source_end < source + 1) goto panic;
        source[0] = source[0] & 0xffffffffffffffc3;         /* clear absorbed kind */
        if (target_end < target + 1) goto panic;
        if ((target[0] & 0x3c) == 0xc) {
            /* ---- target is a cap-slot array: append source into its gap ---- */
            if (target_end < target || (uint64_t)(target_end - target) < 0x39)
                goto panic;
            occ = 0; tail = 7; slot2 = target;
            do {
                if (slot2 < target || target + 8 < slot2 + 1 || slot2 + 1 < slot2)
                    goto panic;
                if ((*slot2 & 0xfffffc0) == 0) { tail = -occ; break; }
                occ--;
                slot2++;
            } while (occ != -7);
            if (source_end < source || (uint64_t)(source_end - source) < 0x39)
                goto panic;
            byte_len = 0;
            slot2 = source;
            do {
                if (slot2 < source || source + 8 < slot2 + 1 || slot2 + 1 < slot2)
                    goto panic;
            } while ((*slot2 & 0xfffffc0) != 0 && (byte_len += 8, byte_len != 0x38));
            slot2 = target + tail;
            if (slot2 < target ||
                ((uint64_t)(source_end - source) < byte_len || target_end < slot2) ||
                ((uint64_t)(target_end - slot2) < byte_len)) goto panic;
            sk_memmove(slot2, source, byte_len);            /* FUN_00117d14 */
            if ((uint64_t *)((char *)slot2 + byte_len) < slot2 ||
                source_end < source + 8 || target_end < target + 8) goto panic;
            target[7] = (source[7] & 0xfffffffff0000000) |
                        (target[7] & 0xfffffff);            /* target[7] ptr = source[7] ptr */
        } else {
            /* ---- target is a span array: splice source after its gap ---- */
            if (target_end < target || (uint64_t)(target_end - target) < 0x39)
                goto panic;
            tail = 0; slot2 = target;
            do {
                if (slot2 < target || target + 8 < slot2 + 1 || slot2 + 1 < slot2)
                    goto panic;
                if ((*slot2 & 0xfffffc0) == 0) { occ_byte = (uint8_t)(-tail); goto contB; }
                tail--;
                slot2++;
            } while (tail != -7);
            occ_byte = 7;
contB:
            if (source_end < source || (uint64_t)(source_end - source) < 0x39)
                goto panic;
            byte_len = 0x40;
            tail = 0; slot2 = source;
            do {
                if (slot2 < source || source + 8 < slot2 + 1 || slot2 + 1 < slot2)
                    goto panic;
                if ((*slot2 & 0xfffffc0) == 0) { byte_len = tail + 8; break; }
                tail += 8;
            } while (tail != 0x38);
            /* target[occ_byte] takes the count of the left slot, then source is
             * moved in one position past it. */
            slot = slots + (lo_slot & 0xff);
            if (slot < slots || end < slot + 1 || slot + 1 < slot) goto panic;
            target[occ_byte] = (target[occ_byte] & 0xfffffffff0000000) |
                               (target[occ_byte] & 0x3f) |
                               ((*slot >> 6 & 0x3fffff) << 6);
            if ((uint64_t)(source_end - source) < byte_len) goto panic;
            slot2 = target + (uint8_t)(occ_byte + 1);
            if (slot2 < target || target_end < slot2) goto panic;
            if ((uint64_t)(target_end - slot2) < byte_len) goto panic;
            sk_memmove(slot2, source, byte_len);            /* FUN_00117d14 */
            if ((uint64_t *)((char *)slot2 + byte_len) < slot2) goto panic;
        }

        /* ---- common post-merge: absorb, drop the vacated slot, free source ---- */
        slot = slots + (hi_slot & 0xff);
        if (slot < slots || end < slot + 1 || slot + 1 < slot) goto panic;
        slot2 = slots + (lo_slot & 0xff);
        if (slot2 < slots || end < slot2 + 1 || slot2 + 1 < slot2) goto panic;
        *slot2 = (*slot2 & 0xfffffffff0000000) | (*slot2 & 0x3f) |
                 ((*slot >> 6 & 0x3fffff) << 6);            /* lo.count = hi.count */
        slot_word = *slots;
        *slots = slot_word & 0xffffffffffffffc3;
        removed = sk_vas_slot_remove(slots, hi_slot & 0xff, 8);
        if (slots + 8 < slots + 1) goto panic;
        *slots = (*slots & 0xffffffffffffffc0) | (*slots & 3) |
                 ((slot_word >> 2 & 0xf) << 2);             /* restore slots[0] kind */
        if (source + 1 < source) goto panic;
        sk_capslot_free((uint64_t)source);                  /* FUN_0003481c */
        if (removed != 1) {
            status = 2;
            if (2 < (uint8_t)(removed - 1)) status = 3;
            goto ret;
        }
    }

    /* Replace the whole array with the survivor (target). */
    sk_capslot_free((uint64_t)slots);                       /* FUN_0003481c */
    if (target + 1 <= target_end) {
        if ((target[0] & 0x3c) == 8) target[0] = target[0] & 0xffffffffffffffc3 | 4;
        if ((target <= target_end) && (0x38 < (uint64_t)target_end - (uint64_t)target)) {
            status = 3;
            slots = target;
            goto ret;
        }
    }
    goto panic;

merge_big:
    /* ---- a neighbour span is >3 entries (or full): rotate one entry into
     *      the child so the two arrays can coalesce ---- */
    mask = sk_slot_mask_4bc1e0;                             /* DAT_004bc1e0 */
    if ((int)(uint32_t)cur < (int)count_slots) {
        /* Left neighbour: pop the last occupied span slot into the child. */
        if (end2 < child + 1) goto panic;
        child_kind = (uint32_t)(*child >> 2) & 0xf;
        if (child_kind == 3) {
            /* child is cap-slot: rotate the span's tail into its front. */
            slot2 = span + (tail - 1);
            if (slot2 < span || span_end < slot2 + 1 || slot2 + 1 < slot2) goto panic;
            last_word = *slot2;
            *slot2 = 0;
            *child = *child & 0xffffffffffffffc3;
            if (child == NULL || (uint64_t)(child_end - child) < 0x18) goto panic;
            child[3] = child[2];
            child[2] = child[1];
            child[1] = *child;
            if (child + 4 < child + 1) goto panic;
            *child = (last_word & 0xffffffffffffffc3) | 0xc;
            *slot = (*slot & 0xfffffffff0000000) | (*slot & 0x3f) |
                    ((last_word >> 6 & 0x3fffff) << 6);     /* slots[cur].count = tail count */
        } else {
            /* child is span slots: rotate tail + carry its kind/ptr. */
            *child = *child & 0xffffffffffffffc3;
            if (child == NULL || (uint64_t)(child_end - child) < 0x18) goto panic;
            child[3] = child[2];
            child[2] = child[1];
            child[1] = *child;
            if (child + 4 < child + 1) goto panic;
            last_word = *child;
            i = (*slot >> 6 & 0x3fffff) << 6;               /* slots[cur] count << 6 */
            *child = (last_word & 0xfffffffff0000000) | (last_word & 0x3f) | i;
            slot2 = span + tail;
            if (slot2 < span || span_end < slot2 + 1 || slot2 + 1 < slot2) goto panic;
            {
                uint64_t *prev = slot2 - 1;
                *child = (last_word & 3) | i | (uint64_t)(child_kind << 2) |
                         (*slot2 & 0xfffffffff0000000);
                if (prev < span || slot2 < prev) goto panic;
                *slot = (*slot & 0xfffffffff0000000) | (*slot & 0x3f) |
                        ((*prev >> 6 & 0x3fffff) << 6);     /* slots[cur].count = prev count */
                *slot2 &= mask;
                *prev &= mask;
            }
        }
    } else {
        /* Right neighbour: rotate the span's front into the child. */
        if (end2 < child + 1) goto panic;
        slot2 = span + 1;
        if ((*child & 0x3c) != 0xc) {
            /* child not cap-slot: full 8-word left-rotate of the span. */
            if (span_end < slot2 || slot2 < span || dist < 0x39) goto panic;
            occ = 0;
            last_word = *span;
            tail = 7;
            goto walk2;
        }
        /* child is cap-slot: 8-word shuffle of the span into the child. */
        if (span_end < slot2 || slot2 < span ||
            (uint64_t)(span_cap - slot2) < 0x30 || dist < 0x30) goto panic;
        {
            uint64_t w1 = span[1];
            uint64_t w2 = span[2];
            uint64_t w3 = span[3];
            uint64_t w5 = span[5];
            last_word = *span;
            span[3] = span[4];
            span[2] = w3;
            span[5] = span[6];
            span[4] = w5;
            span[1] = w2;
            *span = w1;
            if (span + 6 < span) goto panic;
            slot2 = span + 6;
            *span = (*span & 0xffffffffffffffc3) | (last_word & 0x3c);
            if (slot2 < span || span_end < span + 7 || span + 7 < slot2) goto panic;
            *slot2 = 0;
            slot2 = child + 2;
            if (slot2 < child || child + 3 < slot2 || end2 < child + 3) goto panic;
            *slot2 = last_word & 0xffffffffffffffc3;
            *slot = (*slot & 0xfffffffff0000000) | (*slot & 0x3f) |
                    ((*span >> 6 & 0x3fffff) << 6);         /* slots[cur].count = span[0] count */
        }
    }
    status = 3;
    goto ret;

walk2:
    /* Scan the span (from word 1) for the first empty slot; `tail` becomes its
     * index (or stays 7 when the span is full) and `last_word` holds the old
     * span[0] that will be rotated out into the child. */
    slot2 = span + 1;
    if (span_end < slot2 || slot2 < span || (uint64_t)(span_cap - slot2) < 0x38)
        goto panic;
    slot2 = span;
    while (occ != -7) {
        occ--;
        slot2++;
        if (slot2 < span || span_end < slot2 + 1 || slot2 + 1 < slot2) goto panic;
        if ((*slot2 & 0xfffffc0) == 0) { tail = -occ; break; }
    }
    {
        /* Rotate the span left by one (old span[1] -> span[0], ...,
         * old span[7] -> span[6]); span[0]'s kind is restored from last_word. */
        uint64_t w1 = span[1];
        uint64_t w2 = span[2];
        uint64_t w3 = span[3];
        uint64_t w5 = span[5];
        uint64_t w6 = span[6];
        span[6] = span[7];
        span[3] = span[4];
        span[2] = w3;
        span[5] = w6;
        span[4] = w5;
        span[1] = w2;
        *span = w1;
        if (span + 7 < span) goto panic;
        *span = (*span & 0xffffffffffffffc3) | (last_word & 0x3c);
        slot2 = span + tail;
        if (slot2 < span || span_end < slot2 + 1 || slot2 + 1 < slot2) goto panic;
        *slot2 = 0;
        if (child + 2 < child) goto panic;
        slot2 = child + 3;
        if (slot2 < child + 2 || end2 < slot2 || child + 4 < slot2) goto panic;
        child[2] = (child[2] & 0xfffffffff0000000) | (child[2] & 0x3f) |
                   ((*slot >> 6 & 0x3fffff) << 6);
        *slot2 = (last_word & 0xfffffffff0000000) | 1;
        *slot = (*slot & 0xfffffffff0000000) | (*slot & 0x3f) |
                ((last_word >> 6 & 0x3fffff) << 6);
    }
    status = 3;
    goto ret;

ret:
    return (sk_vas_lock_tok_t){ status, (uint64_t)slots };

panic:
    SK_ASRT_PANIC(0x379ac);
}
