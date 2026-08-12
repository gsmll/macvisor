/* sk_slice_06_frag_cap.c — capability encode/decode helpers (0x35ba0-0x36bd4).
 *
 * These are the cL4 capability-word encoders/decoders: the core encoder
 * sk_vas_cap_build (FUN_00035bac), the descriptor/iterator walkers
 * (describe/next), the lookup/merge/clone/free/insert operations and the
 * cap-kind/get helpers.
 *
 * Capability word layout (low two bits select the representation):
 *   low2 == 0  NULL/empty slot
 *   low2 == 1  direct cap: kind = (cap>>6)&0x3fffff, badge/offset = cap>>28, +1
 *   low2 == 2  indirect: cap>>28 points at an 8-entry span table; small kind
 *              (cap>>2)&0xf in the badge area
 *   low2 == 3  multi-span: cap>>28 points at a chained span; kind = (cap>>6)&0x3fffff
 *
 * DAT_004bc1xx are the error strings copied into the 2-word out[2..3] fields. */
#include "sk_slice_06_shared.h"

/* The shared header declares sk_capslot_alloc (FUN_000347c4) and
 * sk_vas_cap_alloc_slot (FUN_00036d58) as `void` because Ghidra dropped their
 * return in the void decompiles — but every decompiled caller reads the
 * freshly-allocated slot from x0. These local externs recover that value so the
 * encoder stays faithful; the real functions are defined by the slots fragment. */
extern uint64_t sk_vas_capslot_alloc(void);                          /* FUN_000347c4 sk_capslot_alloc */
extern uint64_t sk_vas_cap_slot_alloc(uint64_t slots, uint64_t cap); /* FUN_00036d58 sk_vas_cap_alloc_slot */

/* Error strings (DAT_004bc1xx), copied as 2-word pairs into the out[2..3] fields. */
extern uint64_t sk_dbg_err_badkind_lo;    /* DAT_004bc1b0 */
extern uint64_t sk_dbg_err_badkind_hi;    /* DAT_004bc1b8 */
extern uint64_t sk_dbg_err_compact_lo;    /* DAT_004bc1c0 */
extern uint64_t sk_dbg_err_compact_hi;    /* DAT_004bc1c8 */
extern uint64_t sk_dbg_err_notfound_lo;   /* DAT_004bc1d0 */
extern uint64_t sk_dbg_err_notfound_hi;   /* DAT_004bc1d8 */

/* A capability-descriptor iterator (built by sk_vas_cap_describe, walked by
 * sk_vas_cap_next). tag: 0 = done, 1 = direct, 2 = indirect span, 3 = multi span. */
typedef struct {
    uint8_t  tag;
    uint8_t  flag;   /* direct: emit-once latch (set when orig is returned);
                        indirect/multi: iteration cursor (entry index) */
    uint8_t  pad[6];
    uint64_t ptr;    /* span table / chained-span pointer (indirect/multi) */
    uint64_t orig;   /* direct: the original cap word */
} sk_cap_desc_t;

/* Reconstructs FUN_0003652c (sk_vas_cap_desc_walk): walk the linked span chain
 * headed at `head`, locating the first entry whose kind is >= `kind` (a
 * lower-bound search across the kind-sorted spans). Returns the resolved span
 * pointer (the value the decompile leaves in x0) and stores the entry index
 * into *entry (the x1 byte; high bits set when no exact entry was located).
 * Used directly by the describe and build callers, which the header's void
 * desc_walk cannot serve. */
static uint64_t sk_cap_desc_resolve(uint64_t *head, uint32_t kind, uint64_t *entry)
{
    uint64_t *span = head;
    for (;;) {
        if (span == NULL || span + 8 < span)
            break;
        if ((*span & 0x3c) == 0xc) {
            /* Chained span: entry 7 holds the link to the next span (ptr = e>>28). */
            unsigned i;
            for (i = 0; i < 7; i++) {
                uint64_t e;
                if (span + i + 1 < span + i)
                    break;
                e = span[i];
                if ((e & 3) == 1 && kind <= ((uint32_t)(e >> 6) & 0x3fffff)) {
                    *entry = i;
                    return (uint64_t)span;
                }
            }
            *entry = i;
            return (uint64_t)span;
        } else {
            /* Plain span: lower bound over the up-to-8 entries. */
            unsigned i;
            for (i = 0; i < 8; i++) {
                uint64_t e = span[i];
                if ((e & 0xfffffc0ull) == 0 || ((uint32_t)(e >> 6) & 0x3fffff) > kind)
                    break;
            }
            *entry = i;
            return (uint64_t)span;
        }
    }
    SK_ASRT_PANIC(0x3667c);
}

/* FUN_00035ba0 @ 0x00035ba0  (est. sk_vas_map_lookup)
 * Ghidra: void FUN_00035ba0(undefined8 param_1, undefined8 param_2)
 * Forwards a VAS map lookup to the core capability encoder with an empty kind
 * and zero badge (no build flag). The phys argument is not forwarded.
 * Confidence: high
 * Notes: DAT_004bc1xx error strings; forwards to FUN_00035bac. */
static void sk_vas_map_lookup(uint64_t *d, uint64_t span, uint64_t phys)
{
    sk_vas_cap_build(d, span, 0, 0, 0);
}

/* FUN_00035bac @ 0x00035bac  (est. sk_vas_cap_build)
 * Ghidra: void FUN_00035bac(ulong *param_1, ulong param_2, undefined8 param_3,
 *                           ulong param_4, uint param_5)
 * The core capability encoder. Given a source cap (kind), a target kind (a3), a
 * badge/offset (a4) and a build flag, it produces a capability word for the
 * target in out[4] together with the badge in out[0]. For null sources it
 * synthesizes a direct cap; for direct sources it passthroughs when the kind
 * already matches, otherwise it builds an indirect span (or, when the span's
 * small kind is >= 8, grows a chained multi-span); indirect/multi sources are
 * scanned for an existing entry of the target kind and otherwise extended.
 * Confidence: high
 * Notes: DAT_004bc1b0/8 bad-kind error; slots from FUN_000347c4/FUN_00036d58. */
static void sk_vas_cap_build(uint64_t *out, uint64_t kind, uint64_t a3, uint64_t a4, uint32_t flag)
{
    uint32_t tkind = (uint32_t)a3;        /* target kind */
    uint32_t s_low = (uint32_t)kind;      /* source cap low word */
    sk_vas_lock_tok_t err = {0, 0};
    uint64_t built;

    if (tkind > 0x3fffff) {
        /* target kind does not fit the 22-bit kind field */
        out[0] = 0; out[1] = 0;
        out[2] = sk_dbg_err_badkind_lo; out[3] = sk_dbg_err_badkind_hi;
        out[4] = kind;
        return;
    }

    if ((kind & 3) == 1 || (kind & 3) == 0) {
        /* ---------- direct or null source ---------- */
        if ((kind & 3) == 0) {
            /* null source: synthesize a fresh direct cap */
            uint64_t badge = a4 << 28;
            out[1] = 0; out[2] = 0;
            if (flag == 0)
                a4 = 0;
            out[0] = a4;
            *((uint8_t *)out + 1) = (uint8_t)flag;
            built = ((uint64_t)tkind << 6 | 1) | badge;
            if (flag == 0)
                built = kind;   /* 0 */
            out[3] = 0; out[4] = built;
            return;
        }
        /* direct source */
        if ((((uint32_t)kind >> 6) & 0x3fffff) == tkind) {
            /* source kind already matches the target: passthrough */
            out[0] = kind >> 28;
            out[1] = 0; out[2] = 0; out[3] = 0;
            out[4] = kind;
            return;
        }
        if ((flag & 1) == 0) {
            /* no build requested: null result */
            out[0] = 0; out[1] = 0; out[2] = 0; out[3] = 0;
            out[4] = kind;
            return;
        }
        /* build an indirect span holding both the source cap and the new cap */
        {
            uint64_t slot = sk_vas_capslot_alloc();
            err = sk_vas_cap_insert((uint64_t *)slot, kind, 8, 0);
            if ((err.flags & 0xff) != 0)
                goto insert_err;
            err = sk_vas_cap_insert((uint64_t *)slot,
                                    ((uint64_t)tkind << 6 | 1) | (a4 << 28), 8, 0);
            if ((err.flags & 0xff) != 0)
                goto insert_err;
            out[0] = a4;
            *((uint8_t *)out + 1) = 1;
            out[1] = 0; out[2] = 0; out[3] = 0;
            out[4] = (slot << 28) | 10;   /* indirect (low2=2, ikind=2) */
            return;
        }
    }

    /* ---------- indirect (low2==2) or multi (low2==3) source ---------- */
    {
        uint64_t *span = (uint64_t *)(kind >> 28);
        if (span == NULL || span + 8 < span || (uint64_t)((span + 8) - span) < 0x39)
            SK_ASRT_PANIC(0x36008);

        if ((kind & 3) == 2) {
            /* indirect source */
            uint64_t *end = span + 8;
            unsigned i;
            /* scan for an existing entry of the target kind */
            for (i = 0; i < 8; i++) {
                uint64_t e = span[i];
                if ((e & 3) == 1) {
                    if ((((uint32_t)e >> 6) & 0x3fffff) == tkind) {
                        /* found: passthrough */
                        out[0] = e >> 28;
                        out[1] = 0; out[2] = 0; out[3] = 0;
                        out[4] = kind;
                        return;
                    }
                } else if ((e & 3) == 0) break;
            }
            if ((flag & 1) != 0) {
                uint64_t newcap = ((uint64_t)tkind << 6 | 1) | (a4 << 28);
                uint32_t ikind = s_low >> 2 & 0xf;
                bool small = (uint64_t)(end - span) < 0x39;
                if (ikind < 8) {
                    /* small kind fits in this span: insert directly */
                    if (span != NULL && small)
                        SK_ASRT_PANIC(0x36008);
                    err = sk_vas_cap_insert(span, newcap, 8, 0);
                    if ((err.flags & 0xff) != 0)
                        goto insert_err;
                    out[0] = a4;
                    *((uint8_t *)out + 1) = 1;
                    built = kind & 0xffffffffffffffc3 | (uint64_t)(ikind * 4 + 4);
                    out[1] = 0; out[2] = 0; out[3] = 0;
                    out[4] = built;
                    return;
                }
                /* ikind >= 8: grow a chained (multi) span, migrating the entries */
                if (span != NULL && small)
                    SK_ASRT_PANIC(0x36008);
                {
                    uint64_t *nspan = (uint64_t *)sk_vas_capslot_alloc();
                    uint64_t *cursor = nspan;
                    if (nspan == NULL || nspan + 8 < nspan)
                        SK_ASRT_PANIC(0x36008);
                    nspan[0] = (nspan[0] & ~0x3cull) | 0xc;   /* mark chain head */
                    for (i = 0; i < 8; i++) {
                        uint64_t e = span[i];
                        if ((e & 3) == 1) {
                            if (cursor == NULL || cursor + 8 < cursor || cursor + 9 < cursor + 8)
                                SK_ASRT_PANIC(0x36008);
                            cursor = (uint64_t *)sk_vas_cap_slot_alloc((uint64_t)cursor, 0);
                            if (cursor == NULL)
                                SK_ASRT_PANIC(0x36008);
                        }
                    }
                    sk_capslot_free((uint64_t)span);
                    if (cursor == NULL || cursor + 8 < cursor || cursor + 9 < cursor + 8)
                        SK_ASRT_PANIC(0x36008);
                    uint64_t base = (uint64_t)cursor & 0xfffffffff;
                    if (base + 0x40 < base || (base != 0 && (base + 0x40) - base < 0x39))
                        SK_ASRT_PANIC(0x36008);
                    uint64_t slot = sk_vas_cap_slot_alloc(base, newcap);
                    built = (uint64_t)(ikind * 0x40 + 0x40);
                    out[0] = a4;
                    *((uint8_t *)out + 1) = 1;
                    built = built | (slot << 28) | 3;   /* multi-span */
                    out[1] = 0; out[2] = 0; out[3] = 0;
                    out[4] = built;
                    return;
                }
            }
        } else {
            /* multi source */
            uint64_t entry;
            uint64_t rspan = sk_cap_desc_resolve(span, tkind, &entry);
            if ((entry & 0xf8) == 0) {
                uint64_t *res = (uint64_t *)rspan;
                uint64_t *e = res + (entry & 7);
                if (res == NULL || (uint64_t)((res + 8) - res) < 0x39 ||
                    e < res || e + 1 < e || e + 1 > res + 8)
                    SK_ASRT_PANIC(0x36008);
                uint64_t b = *e >> 28;
                if (b != 0 && ((((uint32_t)*e >> 6) & 0x3fffff) == tkind)) {
                    /* found existing entry: passthrough */
                    out[0] = b;
                    out[1] = 0; out[2] = 0; out[3] = 0;
                    out[4] = kind;
                    return;
                }
            }
            if ((flag & 1) != 0) {
                uint64_t newcap = ((uint64_t)tkind << 6 | 1) | (a4 << 28);
                uint64_t slot = sk_vas_cap_slot_alloc((uint64_t)span, newcap);
                built = (uint64_t)(s_low + 0x40) & 0xfffffc0;
                out[0] = a4;
                *((uint8_t *)out + 1) = 1;
                built = built | (slot << 28) | 3;   /* multi-span */
                out[1] = 0; out[2] = 0; out[3] = 0;
                out[4] = built;
                return;
            }
        }
        /* not found / no build: null result */
        out[0] = 0; out[1] = 0; out[2] = 0; out[3] = 0;
        out[4] = kind;
        return;
    }

insert_err:
    out[0] = 0; out[1] = 0;
    out[2] = err.flags; out[3] = err.counter;
    out[4] = kind;
    return;
}

/* FUN_00036008 @ 0x00036008  (est. sk_vas_span_map)
 * Ghidra: void FUN_00036008(void)
 * Forwards a span map to the core capability encoder. The Ghidra decompile
 * dropped all arguments; they are forwarded positionally.
 * Confidence: high
 * Notes: forwards to FUN_00035bac. */
static void sk_vas_span_map(uint64_t *out, uint64_t span, uint64_t phys, uint64_t a4, uint64_t a5)
{
    sk_vas_cap_build(out, span, phys, a4, (uint32_t)a5);
}

/* FUN_00036010 @ 0x00036010  (est. sk_vas_cap_get)
 * Ghidra: ulong FUN_00036010(ulong param_1)
 * Returns the underlying capability word of a cap: a direct cap returns itself,
 * a null returns 0, an indirect cap returns its first span entry, and a
 * multi-span cap walks the chain following entry-0 links until it reaches the
 * span whose first entry carries the 0xc chain marker and returns it.
 * Confidence: medium
 * Notes: SK_ASRT_PANIC at 0x36118 on a malformed chain. */
static uint64_t sk_vas_cap_get(uint64_t cap)
{
    uint32_t low = (uint32_t)cap & 3;
    if (low == 1 || (cap & 3) == 0) {
        return (cap & 3) ? cap : 0;
    }
    if (low == 2) {
        uint64_t *span = (uint64_t *)(cap >> 28);
        if (span != NULL && span + 8 >= span && (uint64_t)((span + 8) - span) > 0x38) {
            if (span <= span + 1 && span + 1 <= span + 8)
                return *span;
        }
    } else {
        uint64_t *span = (uint64_t *)(cap >> 28);
        if (span != NULL && span + 8 >= span && (uint64_t)((span + 8) - span) > 0x38) {
            uint64_t *end = span + 8;
            if (span <= end && (span == NULL || (uint64_t)(end - span) > 0x38)) {
                for (;;) {
                    if (span != NULL && span + 8 >= span) {
                        if (span + 1 <= span + 8) {
                            uint64_t e = *span;
                            if ((e & 0x3c) == 0xc)
                                return e;               /* chain marker entry */
                            span = (uint64_t *)(e >> 28); /* follow entry-0 link */
                            if (span != NULL && span + 8 < (uint64_t *)(e >> 28))
                                break;
                            if (span != NULL && (uint64_t)((span + 8) - span) < 0x39)
                                break;
                        } else break;
                    } else break;
                }
            }
        }
    }
    SK_ASRT_PANIC(0x36118);
}

/* FUN_0003611c @ 0x0003611c  (est. sk_vas_cap_lookup)
 * Ghidra: void FUN_0003611c(undefined8 *param_1, ulong param_2, uint param_3,
 *                           code *param_4)
 * Looks up (and removes) a capability of the given kind from a cap. Direct caps
 * return their badge and clear the slot; indirect caps remove the matching
 * span entry (collapsing the span when it empties, else bumping the indirect
 * kind); multi caps compact the chain via sk_vas_slot_compact and rebuild the
 * reduced cap. On not-found an error string is returned; the callback, when
 * given, is invoked with the removed badge.
 * Confidence: medium
 * Notes: DAT_004bc1d0/8 not-found and DAT_004bc1c0/8 compact error strings. */
static void sk_vas_cap_lookup(uint64_t *out, uint64_t cap, uint32_t kind, void (*cb)(uint64_t))
{
    uint32_t low = (uint32_t)cap & 3;
    uint64_t errlo = sk_dbg_err_notfound_lo;
    uint64_t errhi = sk_dbg_err_notfound_hi;

    if (low == 1 || (cap & 3) == 0) {
        /* direct or null */
        if ((cap & 3) != 0 && ((((uint32_t)cap >> 6) & 0x3fffff) == kind)) {
            if (cb)
                cb(cap >> 28);
            out[0] = 0; out[1] = 0; out[2] = 0;
            return;
        }
        goto notfound;
    }

    if (low == 2) {
        /* indirect */
        uint64_t *span = (uint64_t *)(cap >> 28);
        if (span != NULL && span + 8 >= span && (uint64_t)((span + 8) - span) > 0x38) {
            uint64_t *end = span + 8;
            unsigned i;
            for (i = 0; i < 8; i++) {
                uint64_t e = span[i];
                if ((e & 3) == 1 && ((((uint32_t)e >> 6) & 0x3fffff) == kind)) {
                    if (cb)
                        cb(e >> 28);
                    if ((uint64_t)(end - span) < 0x39)
                        SK_ASRT_PANIC(0x362b0);
                    sk_vas_slot_remove(span, i, 8);
                    if ((((uint32_t)cap + 0x3c) & 0x3c) == 4) {
                        /* span emptied of its single kind group: collapse the
                         * remaining direct entries into one direct cap */
                        uint64_t lkind = 0, lbadge = 0;
                        unsigned j;
                        for (j = 0; j < 8; j++) {
                            uint64_t v = span[j];
                            uint32_t vk;
                            uint64_t vb;
                            if ((v & 3) == 1) { vk = (uint32_t)(v >> 6) & 0x3fffff; vb = v >> 28; }
                            else { vk = (uint32_t)lkind; vb = lbadge; }
                            lbadge = vb; lkind = vk;
                        }
                        if (span == NULL || (span + 1 <= span + 8 && span <= span + 1)) {
                            sk_capslot_free((uint64_t)span);
                            uint64_t newcap = (lkind << 6) | (lbadge << 28) | 1;
                            out[0] = 0; out[1] = 0; out[2] = newcap;
                            return;
                        }
                        SK_ASRT_PANIC(0x362b0);
                    }
                    /* plain single-entry removal: rebuild the indirect cap */
                    out[0] = 0; out[1] = 0;
                    out[2] = e | (cap & 0xffffffffffffffc3);
                    return;
                }
            }
            goto notfound;
        }
    } else {
        /* multi */
        uint64_t head = cap >> 28;
        if (head != 0 && head + 0x40 >= head && (head + 0x40) - head > 0x38) {
            uint64_t h2 = head ? head + 0x40 : 0;
            if (head <= h2 && (head == 0 || h2 - head > 0x38) && head + 8 <= h2) {
                sk_vas_lock_tok_t lt = sk_vas_slot_compact((uint64_t *)head, kind, NULL);
                uint64_t *sp = (uint64_t *)lt.counter;
                if ((lt.flags & 0xff) == 1) {
                    /* compact reported an error: return the compact error string */
                    if (sp == NULL || (sp + 8 >= sp && (uint64_t)((sp + 8) - sp) > 0x38)) {
                        *out = sk_dbg_err_compact_lo;
                        out[1] = sk_dbg_err_compact_hi;
                        out[2] = cap;
                        return;
                    }
                } else if (sp != NULL && (sp + 8 >= sp && (uint64_t)((sp + 8) - sp) > 0x38) &&
                           sp + 1 <= sp + 8) {
                    uint64_t newcap;
                    if ((*sp & 0x3f) == 0xc) {
                        /* still a chained span: free it and yield null */
                        sk_capslot_free((uint64_t)sp);
                        newcap = 0;
                    } else {
                        /* single span left: rebuild an indirect cap */
                        newcap = (cap & 0x3f) | ((uint64_t)sp << 28);
                        newcap |= (cap + 0xfffffc0) & 0xfffffc0;
                    }
                    out[0] = 0; out[1] = 0; out[2] = newcap;
                    return;
                }
            }
        }
    }
    SK_ASRT_PANIC(0x362b0);

notfound:
    *out = errlo;
    out[1] = errhi;
    out[2] = cap;
    return;
}

/* FUN_000363ac @ 0x000363ac  (est. sk_vas_cap_describe)
 * Ghidra: void FUN_000363ac(undefined8 *param_1, ulong param_2, uint param_3)
 * Builds a capability-descriptor iterator in out (tag + cursor + span pointer
 * + original cap) over the direct entries of `cap` whose kind is >= `kind`.
 * Direct caps yield at most one entry; indirect caps set the cursor to the
 * first span entry with kind >= `kind`; multi caps resolve the chained span via
 * sk_cap_desc_resolve. The iterator is consumed by sk_vas_cap_next.
 * Confidence: medium
 * Notes: multi describe resolves through the void desc_walk (FUN_0003652c). */
static void sk_vas_cap_describe(uint64_t *out, uint64_t cap, uint32_t kind)
{
    uint32_t low = (uint32_t)cap & 3;
    if (low == 1 || (cap & 3) == 0) {
        if ((cap & 3) != 0) {
            out[0] = 1;
            *((uint8_t *)out + 1) = ((((uint32_t)cap >> 6) & 0x3fffff) < kind) ? 1 : 0;
            out[1] = 0;
            out[2] = cap;
            return;
        }
        out[0] = 0; out[1] = 0; out[2] = 0;
        return;
    }
    if (low == 3) {
        uint64_t head = cap >> 28;
        uint64_t hend = head + 0x40;
        if (head <= hend && (head == 0 || hend - head > 0x38)) {
            uint64_t h2 = head ? hend : 0;
            if (head <= h2 && (head == 0 || h2 - head > 0x38)) {
                uint64_t entry;
                uint64_t span = sk_cap_desc_resolve((uint64_t *)head, kind, &entry);
                uint64_t send = span + 0x40;
                if (span <= send && (span == 0 || send - span > 0x38)) {
                    out[0] = 3;
                    *((uint8_t *)out + 1) = (uint8_t)entry;
                    out[1] = span;
                    out[2] = 0;
                    return;
                }
            }
        }
    } else {
        /* indirect: entries are read as low-word pairs (uint stride 2) */
        uint32_t *span = (uint32_t *)(cap >> 28);
        uint32_t *end = span ? span + 0x10 : 0;
        if (span + 0x10 < span)
            SK_ASRT_PANIC(0x3652c);
        {
            uint32_t idx = 0;
            uint32_t *e = span;
            for (;;) {
                if (e < span || end < e + 2 || e + 2 < e)
                    SK_ASRT_PANIC(0x3652c);
                if (!((((uint32_t)*e >> 6) & 0x3fffff) < kind))
                    break;
                idx++;
                e += 2;
                if (idx == 8)
                    break;
            }
            if (span == NULL || (uint64_t)(end - span) > 0x38) {
                out[0] = 2;
                *((uint8_t *)out + 1) = (uint8_t)idx;
                out[1] = (uint64_t)span;
                out[2] = 0;
                return;
            }
        }
    }
    SK_ASRT_PANIC(0x3652c);
}

/* FUN_0003652c @ 0x0003652c  (est. sk_vas_cap_desc_walk)
 * Ghidra: void FUN_0003652c(ulong *param_1, uint param_2)
 * Walks the linked span chain rooted at `cap` to position at the first entry of
 * kind >= `kind`, validating each span. The header declares this void because
 * Ghidra dropped the return; the describe/build callers read the resolved
 * span+index pair from x0/x1 and therefore use sk_cap_desc_resolve directly.
 * This wrapper performs the same walk and validates the resolved span is a
 * full 8-entry table.
 * Confidence: low
 * Notes: decompiler recursion (FUN_0003652c()) is unrecoverable; resolve
 *   reconstructed from call sites. */
static void sk_vas_cap_desc_walk(uint64_t *cap, uint32_t kind)
{
    uint64_t entry;
    uint64_t span = sk_cap_desc_resolve(cap, kind, &entry);
    if (span == 0 || span + 0x40 < span || (span + 0x40) - span < 0x39)
        SK_ASRT_PANIC(0x3667c);
}

/* FUN_0003667c @ 0x0003667c  (est. sk_vas_cap_next)
 * Ghidra: ulong FUN_0003667c(char *param_1)
 * Advances a capability-descriptor iterator (built by sk_vas_cap_describe) and
 * returns the next direct cap entry, or 0 when exhausted. A direct descriptor
 * yields its original cap once; an indirect descriptor yields span entries from
 * the cursor; a multi descriptor walks the span chain, crossing from span[7] to
 * the next span via its link, and returns only direct entries.
 * Confidence: high
 * Notes: SK_ASRT_PANIC at 0x36798 on a malformed span. */
static uint64_t sk_vas_cap_next(char *it)
{
    sk_cap_desc_t *d = (sk_cap_desc_t *)it;
    switch (d->tag) {
    case 1:   /* direct */
        if (d->flag == 0) {
            d->flag = 1;
            return d->orig;
        }
        return 0;
    case 2: { /* indirect */
        uint64_t idx = d->flag;
        if (idx < 8) {
            d->flag = (uint8_t)(idx + 1);
            uint64_t *span = (uint64_t *)d->ptr;
            uint64_t *e = span + idx;
            if (span <= e && e + 1 <= span + 8 && e <= e + 1)
                return *e;
            SK_ASRT_PANIC(0x36798);
        }
        return 0;
    }
    case 3: { /* multi */
        uint64_t idx = d->flag;
        uint64_t *span = (uint64_t *)d->ptr;
        for (;;) {
            if (idx > 6) {
                /* cross to the next span via the entry-7 link */
                if (span == NULL || span + 8 < span)
                    SK_ASRT_PANIC(0x36798);
                uint64_t next = span[7] >> 28;
                if (next == 0)
                    return 0;
                if (span + 8 < (uint64_t *)next)
                    SK_ASRT_PANIC(0x36798);
                span = (uint64_t *)next;
                idx = 0;
                d->ptr = (uint64_t)span;
            }
            d->flag = (uint8_t)(idx + 1);
            uint64_t e;
            if (span + idx + 1 < span + idx)
                SK_ASRT_PANIC(0x36798);
            e = span[idx];
            if ((e & 3) == 1)
                return e;
            idx = d->flag;
        }
    }
    default:
        return 0;
    }
}

/* FUN_000367a8 @ 0x000367a8  (est. sk_vas_cap_merge)
 * Ghidra: void FUN_000367a8(undefined8 *param_1, long param_2, undefined8 param_3)
 * Merges capability a into b: the cap with the smaller kind is iterated, each of
 * its entries is checked for an existing same-kind entry in the larger cap
 * (cap_build with flag 0); if any duplicates, the merge fails with error
 * 0x2de0007. Otherwise all entries of the smaller cap are absorbed into the
 * larger (flag 1), the smaller is freed, and the merged cap is returned.
 * Confidence: medium
 * Notes: error marker 0x2de0007; no assertion in the body. */
static void sk_vas_cap_merge(uint64_t *out, uint64_t a, uint64_t b)
{
    uint32_t lowa = (uint32_t)a & 3, ka = lowa;
    if (ka > 1) { if (ka == 3) ka = (uint32_t)(a >> 6) & 0x3fffff; else ka = (uint32_t)(a >> 2) & 0xf; }
    uint32_t lowb = (uint32_t)b & 3, kb = lowb;
    if (kb > 1) { if (kb == 3) kb = (uint32_t)(b >> 6) & 0x3fffff; else kb = (uint32_t)(b >> 2) & 0xf; }

    uint64_t smaller, larger;
    if (ka <= kb) { smaller = a; larger = b; }
    else          { smaller = b; larger = a; }

    uint64_t u = sk_vas_cap_get(smaller);
    uint32_t gkind = (uint32_t)(u >> 6) & 0x3fffff;
    uint64_t it[3] = {0, 0, 0};
    uint64_t e, w[5];

    sk_vas_cap_describe(it, smaller, gkind);
    do {
        e = sk_vas_cap_next((char *)it);
        if ((e & 3) == 0) {
            /* no duplicate kind in the larger cap: absorb all entries */
            sk_vas_cap_describe(it, smaller, gkind);
            while ((e = sk_vas_cap_next((char *)it), (e & 3) != 0)) {
                w[0] = 0; w[1] = 0; w[2] = 0; w[3] = 0; w[4] = 0;
                sk_vas_cap_build(w, larger, (uint32_t)(e >> 6) & 0x3fffff, e >> 28, 1);
                larger = w[4];
            }
            sk_vas_cap_free(smaller, NULL);
            out[0] = 0; out[1] = 0; out[2] = larger;
            return;
        }
        w[0] = 0; w[1] = 0; w[2] = 0; w[3] = 0; w[4] = 0;
        sk_vas_cap_build(w, larger, (uint32_t)(e >> 6) & 0x3fffff, 0, 0);
    } while (w[0] == 0);

    /* a duplicate-kind entry already exists in the larger cap: merge fails */
    out[0] = 0x2de0007ull;
    out[1] = 0; out[2] = 0;
    return;
}

/* FUN_000368f8 @ 0x000368f8  (est. sk_vas_cap_kind)
 * Ghidra: uint FUN_000368f8(uint param_1)
 * Returns the capability kind: 0 for null, 1 for direct, the 4-bit small kind
 * for indirect, and the 22-bit kind for multi-span caps.
 * Confidence: high
 * Notes: none. */
static uint32_t sk_vas_cap_kind(uint32_t cap)
{
    uint32_t low = cap & 3;
    if (low > 1) {
        if (low != 3)
            return (cap >> 2) & 0xf;          /* indirect small kind */
        low = (cap >> 6) & 0x3fffff;          /* multi kind */
    }
    return low;
}

/* FUN_00036920 @ 0x00036920  (est. sk_vas_cap_free)
 * Ghidra: void FUN_00036920(ulong param_1, code *param_2)
 * Frees a capability and, when a callback is supplied, invokes it with the
 * badge of each released direct entry. Direct caps invoke the callback with
 * their own badge; indirect caps walk their span entries then free the span
 * table; multi caps release the whole chained span via sk_vas_span_free.
 * Confidence: high
 * Notes: SK_ASRT_PANIC at 0x36a94 on a malformed span. */
static void sk_vas_cap_free(uint64_t cap, void (*cb)(uint64_t))
{
    uint32_t low = (uint32_t)cap & 3;
    if (low == 1 || (cap & 3) == 0) {
        if ((cap & 3) != 0 && cb)
            cb(cap >> 28);
        return;
    }
    if (low == 2) {
        uint64_t *span = (uint64_t *)(cap >> 28);
        if (span != NULL && span + 8 >= span && (uint64_t)((span + 8) - span) > 0x38) {
            uint64_t *end = span + 8;
            unsigned i;
            for (i = 0; i < 8; i++) {
                uint64_t *e = span + i;
                if (e < span || end < e + 1 || e + 1 < e)
                    SK_ASRT_PANIC(0x36a94);
                if (cb && ((span[i] & 3) == 1))
                    cb(span[i] >> 28);
            }
            if (span == NULL || (span + 1 <= span + 8 && span <= span + 1)) {
                sk_capslot_free((uint64_t)span);
                return;
            }
        }
    } else {
        uint64_t head = cap >> 28;
        uint64_t h1 = head + 0x40;
        if (head <= h1 && (head == 0 || h1 - head > 0x38)) {
            uint64_t h2 = head ? h1 : 0;
            if (head <= h2 && (head == 0 || h2 - head > 0x38)) {
                sk_vas_span_free((uint64_t *)head, cb);
                return;
            }
        }
    }
    SK_ASRT_PANIC(0x36a94);
}

/* FUN_00036a94 @ 0x00036a94  (est. sk_vas_cap_clone)
 * Ghidra: void FUN_00036a94(undefined8 *param_1, undefined8 param_2, ulong param_3)
 * Splits an indirect/multi cap: a new capability is built holding every entry
 * whose kind is < n, and each of those entries is then removed from the original
 * cap via sk_vas_cap_lookup. On success out[2] is the clone and out[3] the
 * reduced original; a direct cap yields error 0x3010005 and a removal miss
 * yields the lookup error.
 * Confidence: medium
 * Notes: error markers 0x3010005; no assertion in the body. */
static void sk_vas_cap_clone(uint64_t *out, uint64_t cap, uint64_t n)
{
    if ((((uint32_t)cap >> 1) & 1) == 0) {
        /* not an indirect/multi cap (bit 1 clear) */
        out[0] = 0x3010005ull;
        out[1] = 0;
    } else {
        uint64_t u = sk_vas_cap_get(cap);
        uint64_t it[3] = {0, 0, 0};
        uint64_t e, clone = 0, w[5];
        sk_vas_cap_describe(it, cap, (uint32_t)(u >> 6) & 0x3fffff);
        e = sk_vas_cap_next((char *)it);
        if ((e & 3) != 0) {
            clone = 0;
            do {
                uint64_t k = (uint32_t)(e >> 6) & 0x3fffff;
                if (n <= k)
                    break;   /* keep only entries of kind < n */
                w[0] = 0; w[1] = 0; w[2] = 0; w[3] = 0; w[4] = 0;
                sk_vas_cap_build(w, clone, k, e >> 28, 1);
                clone = w[4];
                e = sk_vas_cap_next((char *)it);
            } while ((e & 3) != 0);
        }
        u = sk_vas_cap_get(clone);
        it[0] = 0; it[1] = 0; it[2] = 0;
        sk_vas_cap_describe(it, clone, (uint32_t)(u >> 6) & 0x3fffff);
        for (;;) {
            e = sk_vas_cap_next((char *)it);
            if ((e & 3) == 0) {
                out[0] = 0; out[1] = 0;
                out[2] = clone; out[3] = cap;
                return;
            }
            {
                uint64_t lr[3] = {0, 0, 0};
                sk_vas_cap_lookup(lr, cap, (uint32_t)(e >> 6) & 0x3fffff, NULL);
                cap = lr[2];
                if ((uint8_t)lr[0] != 0) {   /* removal miss in the original */
                    out[0] = lr[0]; out[1] = lr[1];
                    break;
                }
            }
        }
    }
    out[2] = 0; out[3] = 0;
    return;
}

/* FUN_00036bd4 @ 0x00036bd4  (est. sk_vas_cap_insert)
 * Ghidra: undefined1[16] FUN_00036bd4(ulong *param_1, ulong param_2,
 *                                     uint param_3, uint param_4)
 * Inserts capability `cap` into the span table `slots` at the kind-sorted
 * position, shifting entries right with sk_memmove to make room (capacity n).
 * When flag bit 0 is clear the slot at index n-1 must be empty. Returns a
 * lock-token pair whose low word is 0 on success, 0x910002 if the span is full
 * (tail slot occupied) or 0x990001 if a same-kind entry already exists.
 * Confidence: high
 * Notes: sk_memmove FUN_00117d14; SK_ASRT_PANIC at 0x36d14. */
static sk_vas_lock_tok_t sk_vas_cap_insert(uint64_t *slots, uint64_t cap, uint32_t n, uint32_t flag)
{
    sk_vas_lock_tok_t r = {0, 0};
    uint64_t *end = slots + 8;

    if ((flag & 1) == 0) {
        /* pre-check: the tail slot (index n-1) must be empty */
        uint64_t *last = slots + (uint32_t)(n - 1);
        if (last < slots || end < last + 1 || last + 1 < last)
            SK_ASRT_PANIC(0x36d14);
        if ((*last & 3) != 0) {
            r.flags = 0x910002;   /* span full */
            r.counter = 0;
            return r;
        }
    }

    {
        uint32_t ck = (uint32_t)(cap >> 6) & 0x3fffff;   /* kind of cap to insert */
        uint64_t i = 0, idx = 0;
        uint64_t *p = slots;
        r.flags = 0x990001;   /* default: duplicate-kind error */
        r.counter = 0;
        for (;;) {
            if (p < slots || end < p + 1 || p + 1 < p)
                SK_ASRT_PANIC(0x36d14);
            idx = i;
            if ((*p & 3) == 0)
                break;   /* empty slot: insert here */
            uint32_t ek = (uint32_t)(*p >> 6) & 0x3fffff;
            if (ck == ek)
                return r;   /* duplicate kind */
            if (ck < ek)
                break;      /* insert before this entry */
            i++;
            idx = n - 1;
            p++;
            if (n == i)
                break;      /* scanned all n slots */
        }
        {
            uint64_t *pos = slots + (idx & 0xff);
            uint64_t *dst = pos + 1;
            if (slots <= dst && dst <= end && pos <= end && slots <= pos) {
                long count = (long)n - (long)(idx & 0xff);
                uint64_t bytes = (uint64_t)count * 8;
                uint64_t lim = (uint64_t)(idx & 0xff) * 8;
                if ((bytes <= 0x40 - lim) && (bytes <= 0x38 - lim)) {
                    sk_memmove(dst, pos, bytes);
                    if (dst <= dst + count && pos <= dst) {
                        *pos = (cap & 0xffffffffffffffc0) | (*pos & 0x3c) | 1;
                        r.flags = 0;
                        r.counter = 0;
                        return r;
                    }
                }
            }
        }
    }
    SK_ASRT_PANIC(0x36d14);
}
