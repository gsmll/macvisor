/* sk_slice_06_frag_capsplit.c — capability/span split for the VAS subsystem. */

#include "sk_slice_06_shared.h"

/* FUN_0002fb88 @ 0x0002fb88  (est. sk_cap_split)
 * Ghidra: void FUN_0002fb88(undefined8 *param_1,long *param_2,undefined8 param_3,
 *                           ulong param_4,int param_5)
 * Splits a capability/span: asks the VAS page-table counter (0x30780) how many
 * units the requested offset requires, then either finds an existing carve node
 * in the span's +0x60 list with enough headroom or allocates a fresh node via
 * the span vtable. It copies the requested window into the node and maps the
 * physical range into it with sk_vas_span_map, linking the node into the
 * span's active lists. On success out[2] holds the node; error codes:
 * 0x12f0007 (null span / zero offset), 0x1350005 (flag != 0), 0x1510002
 * (bad unit count), 0x1610002 (no node / empty node), 0x1880001 (map result
 * not marked done).
 * Confidence: medium
 * Notes: the 0x30780 (sk_vas_pt_count) and 0x36008 (sk_vas_span_map) call sites
 * set only the leading argument registers (disasm 0x2fc70, 0x2fec8); the extra
 * trailing arguments of the header-declared signatures are therefore passed as
 * 0 here. DAT_004bc1fc = VAS unit stride; DAT_004bc020 = node seed word. */
static void sk_cap_split(uint64_t *out, uint64_t *span, uint64_t phys,
                         uint64_t off, int flag)
{
    uint64_t *node;
    uint64_t result = 0;
    uint64_t vtable;
    uint64_t count, seed, stride_end, head_end, src, end, dst, delta, next, back;
    uint32_t headroom;
    uint64_t local_90, uStack_88, uStack_80, uStack_78, local_70;

    /* Entry validation: a null span or a zero offset fails up front. */
    if (span == NULL || off == 0) {
        result = 0x12f0007;
        goto finish;
    }
    /* Only the flag==0 form is supported. */
    if (flag != 0) {
        result = 0x1350005;
        goto finish;
    }

    /* Bounds-check the requested range against the span's two windows and the
     * global unit stride (DAT_004bc1fc). */
    {
        uint64_t base, len;
        stride_end = off + (uint64_t)*(volatile uint32_t *)0x4bc1fc;
        if (off + 4 < off || stride_end < off + 4)
            SK_ASRT_PANIC(0x2fe54);
        base = span[6];
        if (base != 0 && (base + 4 < base || base + span[7] < base + 4))
            SK_ASRT_PANIC(0x2fe54);
        base = span[1];
        if (base != 0 && (base + 4 < base || base + span[2] < base + 4))
            SK_ASRT_PANIC(0x2fe54);
    }

    /* How many VAS units the offset occupies (0x30780; only x0 set at site). */
    count = sk_vas_pt_count((uint32_t *)(uintptr_t)off, NULL, NULL, 0);
    if (count == 0) {
        /* count==0: source stays `off`, window end stays off+stride. */
        seed = 0;
        src = off;
        head_end = stride_end;
        count = 4;
    } else if ((int)count < 1) {
        result = 0x1510002;
        goto finish;
    } else {
        /* count >= 1: source window is span[6]..span[6]+span[7]. */
        src = span[6];
        head_end = (span[6] == 0) ? 0 : span[6] + span[7];
        seed = 0x400000000;
    }

    /* Search the span's +0x60 list for a carve node with headroom >= count. */
    {
        uint64_t **list = (uint64_t **)(span + 0xc);
        for (node = *list; node != NULL; node = (uint64_t *)node[0xa]) {
            if (count <= (uint32_t)node[6]) {
                headroom = 0x40000 - (uint32_t)node[6];
                goto use_node;
            }
        }
    }

    /* No fit: allocate a fresh carve node through the span vtable. */
    vtable = *span;
    node = (uint64_t *)(*(uint64_t *(**)(void))(vtable))();
    if (node != NULL) {
        if (node + 0xc < node || node + 5 < node)
            SK_ASRT_PANIC(0x2fe54);
        (*(void (**)(uint64_t, uint64_t))(vtable + 0x10))(0x40000, (uint64_t)node);
        if (node[0] != 0) {
            /* Seed the node: new capability slot + present flag, then link it
             * into both the +0x58 and +0x60 intrusive lists. */
            node[5] = sk_capslot_alloc_zero();           /* 0x35b98 */
            node[6] = *(uint64_t *)0x4bc020;             /* DAT_004bc020 seed */
            *((uint8_t *)node + 0x38) = 1;               /* node[7] = present */
            {
                uint64_t **head = (uint64_t **)(span + 0xb); /* &span[0xb] */
                uint64_t *old = *head;
                node[8] = (uint64_t)old;                  /* node+0x40 = old head */
                if (old != 0) {
                    if (node + 9 < node + 8)
                        SK_ASRT_PANIC(0x2fe54);
                    *(uint64_t **)(old + 9) = node + 8;   /* old->+0x48 = &node[8] */
                }
                *head = node;                             /* span[0xb] = node */
            }
            if (span + 0xc < span + 0xb)
                SK_ASRT_PANIC(0x2fe54);
            {
                uint64_t **list = (uint64_t **)(span + 0xc);
                uint64_t *old = *list;
                node[0xa] = (uint64_t)old;                /* node+0x50 = old head */
                node[9] = (uint64_t)(span + 0xb);         /* node+0x48 = &span[0xb] */
                if (old != 0) {
                    if (node + 0xb < node + 0xa)
                        SK_ASRT_PANIC(0x2fe54);
                    *(uint64_t **)(old + 0xb) = node + 0xa; /* old->+0x58 = &node[10] */
                }
                *list = node;                             /* span[0xc] = node */
            }
            if (span + 0xd < span + 0xc)
                SK_ASRT_PANIC(0x2fe54);
            headroom = 0;
            node[0xb] = (uint64_t)(span + 0xc);           /* node+0x58 = &span[0xc] */
            (*(int *)(span + 0xd))++;                     /* *(int*)(span+0x68)++ */
            goto use_node;
        } else {
            /* Empty node: release it back through vtable[8]. */
            (*(void (**)(uint64_t))(vtable + 8))((uint64_t)node);
        }
        /* Fall through with 0x1610002 when the node was empty. */
    }

    out[2] = 0;
    result = 0x1610002;
    goto finish;

use_node:
    if (node + 0xc < node)
        SK_ASRT_PANIC(0x2fe54);
    /* Grow the node's used counter by (headroom + count) via vtable[0x18]. */
    delta = node[2];
    (*(void (**)(uint64_t, uint64_t))(vtable + 0x18))((uint64_t)node,
                                                      (uint64_t)headroom + count);
    span[0xe] += node[2] - delta;                        /* span+0x70 accumulator */
    end = (node[0] == 0) ? 0 : node[0] + node[1];        /* node window end */
    /* Copy `count` units from the source window into the node's carve point. */
    if (head_end < src || (head_end - src) < count ||
        (dst = node[0] + headroom, dst < node[0]) ||
        (end < dst || (end - dst) < count ||
         (sk_memcpy(dst, src, count), dst + count < dst)))
        SK_ASRT_PANIC(0x2fe54);
    *(uint32_t *)(node + 6) = (uint32_t)node[6] - (uint32_t)count; /* node[6]-=count */

    /* Zero the 32-byte span-map result block and map the physical range. */
    local_90 = 0; uStack_88 = 0; uStack_80 = 0; uStack_78 = 0; local_70 = 0;
    sk_vas_span_map(&local_90, node[5], phys,
                    (uint64_t)(count & 0x3fff) |
                        (uint64_t)(headroom & 0xfffff) << 0xe | seed,
                    0);
    if (local_90 == 0)
        sk_boot_fatal2();                                 /* 0x116d60, noreturn */
    if ((uStack_88 & 1) != 0) {
        /* Map done: adopt the returned capability, bump the span counters, and
         * if the node fell below 0x118d unlink it from the +0x60 list. */
        node[5] = local_70;
        (*(int *)(span + 0x6c))++;
        span[0x10] += count;                              /* span+0x80 accumulator */
        if ((uint32_t)node[6] < 0x118d) {
            next = node[0xa];
            back = node[0xb];
            if (next != 0)
                *(uint64_t *)(next + 0xb) = back;         /* next->+0x58 = backlink */
            *(uint64_t *)back = next;                     /* *backlink = next */
            *((uint8_t *)node + 0x38) = 0;                /* node[7] = 0 */
        }
        out[0] = 0;
        out[1] = 0;
        out[2] = (uint64_t)node;
        return;
    }
    result = 0x1880001;
    /* fall through to finish */

finish:
    out[0] = result;
    out[1] = 0;
    out[2] = 0;
    return;
}
