/* sk_slice_06_frag_spanmap.c — VAS span-mapping fragment (region 0x0002ff40-0x000304c4).
 * Recreated from the cL4 Secure Kernel (arm64e) via Ghidra decompiles. Ground
 * truth: Ghidra FUN_ names + addresses. All names are estimates unless a
 * string/header match pins them. This fragment owns:
 *   FUN_0002ff40 -> sk_vas_span_map_thunk
 *   FUN_0002ff48 -> sk_vas_span_map2
 *   FUN_000304c4 -> sk_vas_span_map3
 */
#include "sk_slice_06_shared.h"

/* ---- VAS object vtable (first word of *vas points here). ---- */
typedef void (*sk_vas_vcb_t)(void *span);
typedef void (*sk_vas_valloc_t)(uint64_t size, uint64_t *out);
typedef void (*sk_vas_vmap_t)(uint64_t *out, uint64_t idx);
typedef struct {
    void            *unused0;   /* +0x00 (not dispatched) */
    sk_vas_vcb_t     release;   /* +0x08  (*vas+0x08): release span resources */
    sk_vas_valloc_t  alloc;     /* +0x10  (*vas+0x10): alloc a 0x40000 granule */
    sk_vas_vmap_t    map;       /* +0x18  (*vas+0x18): map page at idx, updates out */
    sk_vas_vcb_t     finalize;  /* +0x20  (*vas+0x20): finalize/commit span */
} sk_vas_vtab_t;

/* ---- Page-table sizing globals (Ghidra DAT_004bc1fc / DAT_004bc200). ---- */
extern uint32_t sk_pt_region_bytes;  /* DAT_004bc1fc: pt region size in bytes (>>2 = words) */
extern uint64_t sk_pt_region_limit;  /* DAT_004bc200: pt table limit offset */

/* FUN_0002ff40 @ 0x0002ff40  (est. sk_vas_span_map_thunk)
 * Ghidra: void FUN_0002ff40(void)
 * Pure tail-call forwarding thunk: it branches straight into the full
 * 5-argument mapper FUN_0002ff48 (sk_vas_span_map2), passing its incoming
 * x0-x4 registers through untouched. Ghidra renders the call with no
 * arguments because they arrive in registers; the shared-header signature
 * (void) therefore hides them.
 * Confidence: high
 * Notes: body is `FUN_0002ff48();`; header signature (void) loses the real
 *   register-passed args, so the delegate is invoked via a type-punned cast. */
static void sk_vas_span_map_thunk(void)
{
    /* Register-pass-through thunk: forward (vas, span, phys, pt, write) to the
     * real mapper without inspecting any of them. */
    ((void (*)(void))sk_vas_span_map2)();
}

/* FUN_0002ff48 @ 0x0002ff48  (est. sk_vas_span_map2)
 * Ghidra: undefined1 [16] FUN_0002ff48(long *param_1, ulong *param_2,
 *         undefined8 param_3, undefined4 *param_4, int param_5)
 * Maps (and, when write != 0, installs page-table entries for) the physical
 * range `phys` into the VAS span `span`, which belongs to the VAS object `vas`.
 * It first resolves the covering granule via sk_vas_map_lookup, updates the
 * span/cap accounting on the VAS object, and either extends the current
 * granule in place, grows it into a fresh 0x40000-byte granule when it fills
 * (copying the live pages over), or tears the mapping down when the resolved
 * cap no longer carries a usable kind. Returns a lock token {status, 0}: zero
 * status on success, otherwise one of the encoded error tokens (0x1a60007 /
 * 0x1aa0007 / 0x1b20004 / 0x1cf0007).
 * Confidence: high
 * Notes: vtable dispatch via *vas (+0x08/+0x10/+0x18/+0x20); span[6] packs a
 *   low-dword in-granule used count and a high-dword (byte offset 0x34) second
 *   counter; span[7] low byte is the large-granule-list flag; span[8]/[9] and
 *   span[10]/[0xb] are two unlink lists (prev links at +0x48/+0x58);
 *   sk_vas_span_map(36008) writes out[4]=cap handle (via cap_build 35bac);
 *   DAT_004bc1fc/004bc200 are the pt sizing globals. */
static sk_vas_lock_tok_t sk_vas_span_map2(uint64_t *vas, uint64_t *span, uint64_t phys,
                                          uint32_t *pt, int write)
{
    uint64_t token = 0x1a60007;   /* default token: null arg / no-op */
    sk_vas_vtab_t *vt;

    if (vas == NULL || span == NULL)
        goto out;

    vt = *(sk_vas_vtab_t **)vas;

    /* A write mapping requires a page-table pointer. */
    if (write != 0 && pt == NULL) {
        token = 0x1aa0007;
        goto out;
    }

    {
        uint64_t lookup[6];
        uint32_t level;
        uint64_t granule_idx;   /* granule index within the span */
        uint32_t granule_off;   /* byte offset within the granule */

        lookup[0] = lookup[1] = lookup[2] = lookup[3] = lookup[4] = lookup[5] = 0;
        sk_vas_map_lookup(lookup, span[5], phys);   /* FUN_00035ba0 */
        token = lookup[0];
        if (lookup[0] == 0) {
            token = 0x1b20004;   /* no covering mapping */
            goto out;
        }

        span[5] = lookup[4];                        /* refreshed cap handle */
        granule_idx = (lookup[0] >> 0xe) & 0xfffff; /* granule index */
        granule_off = (uint32_t)lookup[0] & 0x3fff; /* byte offset in granule */

        if (write != 0) {
            /* Page-table-level selector carried in bits [35:34] of the lookup. */
            level = (uint32_t)(lookup[0] >> 0x22) & 3;
            if (level == 1) {
                /* Level-1: single 4-byte entry write. */
                uint64_t base = span[0];
                uint64_t end  = base != 0 ? base + span[1] : 0;
                uint64_t dst  = base + granule_idx;
                /* Defensive overflow bounds (compiler-emitted): the entry slot
                 * [dst, dst+4) must lie inside [base, end); the pte pointer
                 * range and the map region [vas[1], vas[1]+span[2]) must not
                 * wrap. The pte-range half can never fire. */
                if (((dst != 0 && (dst < base || dst + 4 < dst)) || (end < dst + 4)) ||
                    (pt != NULL && (pt + 1 < pt ||
                                    (uint32_t *)((uintptr_t)pt + sk_pt_region_limit) < pt + 1)) ||
                    (vas[1] != 0 && (vas[1] + 4 < vas[1] || vas[1] + span[2] < vas[1] + 4)))
                    goto panic;
                sk_vas_pt_write((uint32_t *)dst, pt, (uint8_t *)vas[1], granule_off); /* FUN_000304d0 */
            } else if (level != 0) {
                token = 0x1cf0007;   /* invalid page-table level */
                goto out;
            } else {
                /* Level-0: replicate one page-table word across the whole pt
                 * region (span[0] is the source table, pt the destination). */
                uint32_t *tbl     = (uint32_t *)span[0];
                uint32_t *tbl_end = (uint32_t *)((char *)tbl + span[1]);
                uint32_t *slot    = (uint32_t *)((char *)tbl + granule_idx);
                if (slot < tbl || slot + 1 < slot || tbl_end < slot + 1)
                    goto panic;
                {
                    uint32_t *pt_end = NULL;
                    if (pt != NULL)
                        pt_end = (uint32_t *)((uintptr_t)pt + sk_pt_region_limit);
                    if (3 < sk_pt_region_bytes) {
                        uint32_t fill = *slot;
                        uint64_t n    = sk_pt_region_bytes >> 2;   /* word count */
                        uint32_t *d   = pt;
                        do {
                            if (d < pt || pt_end < d + 1 || d + 1 < d)
                                goto panic;
                            *d = fill;
                            n--;
                            d++;
                        } while (n != 0);
                    }
                }
            }
        }

        /* ---- Common accounting path. ---- */
        {
            uint64_t cap_out = 0;
            int kind;

            /* Refresh the cap and consult the VAS object's cap accounting. */
            sk_vas_cap_lookup(&cap_out, span[5], (uint32_t)phys, 0); /* thunk_FUN_0003611c */
            span[5] = cap_out;
            /* VAS object: high dword @ +0x6c of the vas[0xd] slot decremented. */
            *((int32_t *)((char *)vas + 0x6c)) -= 1;

            kind = (int)sk_vas_cap_kind((uint32_t)span[5]);   /* FUN_000368f8 */
            if (kind == 0) {
                /* The resolved cap has no usable kind: the span was torn down.
                 * Unlink it from both lists and release all its resources. */
                /* (defensive span+0xc < span bound check omitted: always false) */
                *((int32_t *)&vas[0xd]) -= 1;   /* low dword @ +0x68 */
                {
                    uint64_t used = span[6];
                    uint32_t hi   = *(uint32_t *)((char *)span + 0x34); /* high dword of span[6] */
                    vas[0xe]  -= span[2];
                    vas[0xf]  -= (uint64_t)hi;
                    vas[0x10] -= (uint64_t)(0x40000u - (hi + (uint32_t)(int32_t)used));
                }
                if ((int8_t)span[7] == 1) {
                    uint64_t prev = span[10];
                    uint64_t *next = (uint64_t *)span[0xb];
                    if (prev != 0)
                        *(uint64_t **)(prev + 0x58) = next;
                    *next = prev;
                    *(uint8_t *)&span[7] = 0;
                }
                {
                    uint64_t prev = span[8];
                    uint64_t *next = (uint64_t *)span[9];
                    if (prev != 0)
                        *(uint64_t **)(prev + 0x48) = next;
                    *next = prev;
                }
                sk_vas_cap_free(span[5], 0);   /* thunk_FUN_00036920 */
                vt->finalize(span);            /* (*vas + 0x20) */
                vt->release(span);             /* (*vas + 0x08) */
            } else {
                /* Valid cap kind: extend the mapping in place. */
                uint32_t used = (uint32_t)span[6];   /* low dword: in-granule used count */

                if ((uint32_t)(int32_t)granule_idx + (uint32_t)granule_off < 0x40000u - used) {
                    /* Fits within the current granule. */
                    uint32_t hi = *(uint32_t *)((char *)span + 0x34);
                    hi += granule_off;
                    *(uint32_t *)((char *)span + 0x34) = hi;
                    vas[0xf]  += granule_off;
                    vas[0x10] -= granule_off;

                    if (0xffff < hi) {
                        /* Used space within the granule grew past the 64K
                         * watermark: grow into a fresh 0x40000-byte granule. */
                        /* (defensive span+0xc < span bound check omitted) */
                        uint64_t new_span[5] = { 0, 0, 0, 0, 0 };
                        vt->alloc(0x40000, new_span);   /* (*vas + 0x10) */
                        if (new_span[0] == 0) {
                            used = (uint32_t)span[6];
                        } else {
                            uint64_t newcap = sk_capslot_alloc_zero();   /* FUN_00035b98 */
                            uint64_t it = 0;
                            uint64_t cur;
                            sk_vas_cap_describe(&it, span[5], 0);        /* FUN_000363ac */
                            cur = sk_vas_cap_next((char *)&it);          /* FUN_0003667c */
                            if ((cur & 3) == 0) {
                                used = 0x40000;
                            } else {
                                uint64_t off = 0;
                                do {
                                    uint64_t len = (cur >> 0x1c) & 0x3fff;
                                    used = (uint32_t)len + (uint32_t)off;
                                    vt->map(new_span, (uint64_t)used);   /* (*vas + 0x18) */
                                    {
                                        uint64_t new_end = new_span[0] != 0 ? new_span[0] + new_span[1] : 0;
                                        uint64_t old_base = span[0];
                                        uint64_t old_end  = old_base != 0 ? old_base + span[1] : 0;
                                        uint64_t dst = new_span[0] + off;
                                        uint64_t src = old_base + ((cur >> 0x2a) & 0xfffff);
                                        bool c = old_end - src < len;
                                        bool a = (dst < new_span[0] || src < old_base);
                                        bool b = old_end < src;
                                        bool d = new_end <= dst;
                                        bool e = dst != new_end;
                                        if (((a || b || c || d) && (a || b || c || e)) ||
                                            (new_end - dst < len))
                                            goto panic;
                                        sk_memcpy(dst, src, len);   /* FUN_00117cc4 */
                                        if (dst + len < dst)
                                            goto panic;
                                    }
                                    {
                                        uint64_t so[5] = { 0, 0, 0, 0, 0 };
                                        sk_vas_span_map(so, newcap,
                                                        (uint32_t)cur >> 6 & 0x3fffff,
                                                        (cur >> 0x1c & 0xc00000000) |
                                                            ((uint64_t)((uint32_t)off & 0xfffff) << 0xe) |
                                                            len,
                                                        0);   /* a5 unset at this call site */
                                        newcap = so[4];   /* out[4] = cap handle (uVar12 = local_c0) */
                                    }
                                    cur = sk_vas_cap_next((char *)&it);
                                    off = used;
                                } while ((cur & 3) != 0);
                                used = 0x40000u - used;
                            }
                            /* Commit the grown granule into the span. */
                            {
                                uint64_t old_size = span[2];
                                uint64_t e = vas[0xe];
                                uint64_t f = vas[0xf];
                                uint32_t hi_old = *(uint32_t *)((char *)span + 0x34);
                                sk_vas_cap_free(span[5], 0);   /* thunk_FUN_00036920 */
                                vt->finalize(span);            /* (*vas + 0x20) */
                                span[1] = new_span[1];
                                span[0] = new_span[0];
                                span[3] = new_span[3];
                                span[2] = new_span[2];
                                span[4] = new_span[4];
                                span[5] = newcap;
                                *(uint32_t *)&span[6] = used;          /* low dword */
                                *(uint32_t *)((char *)span + 0x34) = 0; /* high dword */
                                vas[0xe] = (e - old_size) + new_span[2];
                                vas[0xf] = f - (uint64_t)hi_old;
                            }
                        }
                    }
                } else {
                    /* Doesn't fit: bump the used count, shrink the quota. */
                    used = used + (uint32_t)granule_off;
                    *(uint32_t *)&span[6] = used;   /* low dword of span[6] */
                    vas[0x10] -= granule_off;
                }

                /* Register the span in the VAS object's large-granule list once
                 * the used count crosses 0x118c and it is not yet linked. */
                if (0x118c < used && (span[7] & 1) == 0) {
                    uint64_t *head = vas + 0xc;
                    uint64_t first = *head;
                    uint64_t *node = span + 10;   /* span[10] = prev, span[0xb] = next */
                    *node = first;
                    if (first != 0)
                        *(uint64_t **)(first + 0x58) = node;
                    *head = (uint64_t)span;
                    span[0xb] = (uint64_t)head;
                    *(uint8_t *)&span[7] = 1;
                }
            }
        }
    }

    token = 0;   /* success */
out:
    return (sk_vas_lock_tok_t){ .flags = token, .counter = 0 };
panic:
    SK_ASRT_PANIC(0x30460);   /* SoftwareBreakpoint(0x5519, 0x30460); noreturn */
}

/* FUN_000304c4 @ 0x000304c4  (est. sk_vas_span_map3)
 * Ghidra: void FUN_000304c4(void)
 * Pure tail-call forwarding thunk: identical to FUN_0002ff40, it branches
 * directly into the full 5-argument mapper FUN_0002ff48 (sk_vas_span_map2),
 * passing its incoming x0-x4 registers through untouched. Ghidra renders the
 * call with no arguments because they arrive in registers; the shared-header
 * signature exposes the real argument list, which this forwards verbatim.
 * Confidence: high
 * Notes: body is `FUN_0002ff48();`; the header signature (5 args + 16-byte
 *   lock-token return) matches the register-passed contract. */
static sk_vas_lock_tok_t sk_vas_span_map3(uint64_t *vas, uint64_t *span, uint64_t phys,
                                          uint32_t *pt, int write)
{
    /* Register-pass-through thunk: forward the full argument list to the real
     * mapper. */
    return sk_vas_span_map2(vas, span, phys, pt, write);
}
