/* sk_slice_06_frag_pool.c — VAS page-pool freelist allocators (0x32e44-0x33728).
 *
 * The VAS subsystem keeps a set of fixed-block-size page pools, each backed by
 * a 0x3e0-byte heap object.  A per-pool metadata block (meta) records the block
 * size, an in-flight count with low-water mark, a freelist (head/tail/secondary
 * links) and allocation counters.  The core allocator (sk_pool_alloc) first
 * tries to pop a block from the freelist, else carves one from a chained list
 * of free regions grown out of sk_vas_heap_alloc(); the core free
 * (sk_pool_free) pushes the returned block back onto the freelist.  Each
 * _N wrapper resolves the same backing object (sk_vspace_alloc) and binds the
 * metadata to a fixed byte offset inside it, then defers to the core pair.
 * Ground truth: Ghidra FUN_ names + addresses; metadata/freelist field offsets
 * inferred from the decompile (DAT_0x6af180 = the backing-object output
 * slot). */

#include "sk_slice_06_shared.h"

/* FUN_00032e44 @ 0x00032e44  (est. sk_pool_alloc_0)
 * Ghidra: void FUN_00032e44(void)
 * Allocates the 0x3e0-byte backing object and runs the core allocator with the
 * pool metadata located at offset +0x158.  Returns nothing; the block stays in
 * the per-pool freelist.
 * Confidence: high
 * Notes: bounds checks are the overflow/size sanity guards (block 0x3e0,
 *   meta window 0x158..0x190). */
static void sk_pool_alloc_0(void)
{
    uint64_t pool;
    sk_vspace_alloc(&pool, 4, 0xd);                 /* FUN_0005acac */
    if (pool <= pool + 0x3e0 && pool + 0x158 <= pool + 400) {
        sk_pool_alloc(pool, (uint16_t *)(pool + 0x158), 1);
        return;
    }
    SK_ASRT_PANIC(0x32e90);
}

/* FUN_00032e90 @ 0x00032e90  (est. sk_pool_alloc)
 * Ghidra: ulong * FUN_00032e90(ulong param_1, ushort *param_2, int param_3)
 * Core page-pool allocator.  Takes the pool base, the pool's metadata block and
 * a "grab" flag.  When grab is set and the freelist is non-empty, the head
 * block is popped, its in-flight count decremented (with low-water update) and
 * the block is zeroed and returned.  Otherwise (grab clear or empty freelist)
 * a block of size meta[0] is carved out of the front of a free region; the
 * region list is walked, growing a fresh 0x4000-byte region from the heap when
 * exhausted.  Region headers hold {next, size}; carving either consumes the
 * region entirely or re-links the tail remainder as the new head region.
 * Returns the zeroed block, or NULL when the heap yields no new region.
 * Confidence: high
 * Notes: magic 0x6db6db6db6db6db7 = signed ÷7 scale of the meta offset sanity
 *   check (metadata must sit within the pool's +0xe8.. window).  Lock token
 *   from FUN_00034bd8, released via FUN_00034d5c. */
static uint64_t *sk_pool_alloc(uint64_t pool, uint16_t *meta, int grab)
{
    sk_vas_lock_tok_t tok;
    uint64_t block_size, count, region_size, remaining;
    uint64_t *block, *block_end, *link;
    uint64_t *free_head, *free_end;
    uint64_t *region, *region_end, *rest;

    if (pool > pool + 0x30)                         /* base overflow guard */
        goto abort_330b0;

    tok = sk_vas_lock_acquire(pool);                /* FUN_00034bd8 */

    /* Sanity: the meta offset relative to the pool must sit inside the
     * supported metadata window ((meta - (pool + 0xe8)) scaled by ÷7 <= 0xc). */
    if (0xc < (uint64_t)(((long)((long)meta + (-0xe8 - (long)pool)) >> 3) *
                         0x6db6db6db6db6db7L))
        sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5b0855);

    block_size = (uint64_t)meta[0];                 /* +0x00: block size */
    if (0x3fff < block_size)                        /* size field > 14 bits */
        sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5b08b2);

    if (grab != 0) {
        /* Try to reuse a block from the freelist first. */
        block = (uint64_t *)*(uint64_t *)((uint8_t *)meta + 0x20); /* freelist head */
        if (block != 0) {
            block_end = (uint64_t *)*(uint64_t *)((uint8_t *)meta + 0x28); /* tail */
            if ((block + 3 <= block_end) &&
                (link = (uint64_t *)*(uint64_t *)((uint8_t *)meta + 0x30),
                 link <= block)) {                          /* secondary link */
                uint64_t *fwd = (uint64_t *)block[0];
                uint64_t *back = (uint64_t *)block[1];
                *(uint64_t *)((uint8_t *)meta + 0x30) = block[2];
                *(uint64_t *)((uint8_t *)meta + 0x28) = (uint64_t)back;
                *(uint64_t *)((uint8_t *)meta + 0x20) = (uint64_t)fwd;
                count = *(int64_t *)((uint8_t *)meta + 8) - 1; /* in-flight count */
                *(uint64_t *)((uint8_t *)meta + 8) = count;
                if (count < *(uint8_t *)((uint8_t *)meta + 3))   /* low-water */
                    *((uint8_t *)meta + 3) = (uint8_t)count;
                /* block_end = pre-pop tail; link = pre-pop secondary link. */
                goto finalize_33064;
            }
            goto abort_330b0;
        }
    }

    /* Freelist empty or grab clear: carve block_size bytes from a free region. */
    free_head = (uint64_t *)(pool + 200);           /* pool + 0xc8: region list head */
    free_end  = (uint64_t *)(pool + 0xd0);          /* pool + 0xd0: list end marker */

    for (;;) {
        region = (uint64_t *)*free_head;
        if (region == 0) {
            /* Region list exhausted: allocate a fresh 0x4000-byte heap region. */
            region = (uint64_t *)sk_vas_heap_alloc();   /* FUN_00033f1c */
            region_end = region + 0x800;                /* 0x800 ulongs = 0x4000 bytes */
            if (region >= region_end)
                break;
            if (region == 0) {
                sk_vas_lock_release(pool, (uint8_t)tok.flags, tok.counter);
                return 0;
            }
            if (region + 2 <= region_end && region <= region + 2) {
                region[0] = 0;                      /* region->next = 0 */
                region[1] = 0x4000;                 /* region->size = 0x4000 */
                if (free_head + 1 <= free_end && free_head <= free_head + 1) {
                    *free_head = (uint64_t)region;
                    region_size = 0x4000;
                    goto carve_32fe8;
                }
            }
            break;
        }
        region_end = region + 2;                    /* region data start */
        region_size = region[1];                    /* region->size */
        if (block_size <= region_size)
            goto carve_32fe8;
        free_head = region;                         /* advance to next region */
        free_end  = region + 1;
        if (region > region_end)
            break;
    }
    goto abort_330b0;

carve_32fe8:
    if (region + 2 <= region_end) {
        uint64_t *next = (uint64_t *)region[0];     /* region->next */
        remaining = region_size - block_size;       /* bytes left after carve */
        rest = (uint64_t *)((long)region + block_size);
        block = region;                             /* returned block = region base */
        block_end = rest;
        link = region;
        if (remaining < 0x10) {
            /* Region fully consumed: drop it from the list. */
            if (next <= next + 0x10 && free_head + 1 <= free_end &&
                free_head <= free_head + 1) {
                *free_head = (uint64_t)next;
                goto finalize_33064;
            }
        } else if (next <= next + 0x10 &&
                   rest + 2 <= (uint64_t *)((long)rest + remaining)) {
            /* Split: re-link the tail remainder as the new head region. */
            rest[0] = (uint64_t)next;               /* remainder->next */
            rest[1] = remaining;                    /* remainder->size */
            if (rest <= rest + 2 && free_head + 1 <= free_end &&
                free_head <= free_head + 1) {
                *free_head = (uint64_t)rest;
                goto finalize_33064;
            }
        }
    }
    goto abort_330b0;

finalize_33064:
    if (block <= block_end && link <= block &&
        block_size <= (uint64_t)((long)block_end - (long)block)) {
        sk_mem_zero(block, 0, block_size);          /* FUN_001143a0 */
        *(int64_t *)((uint8_t *)meta + 0x10) += 1;  /* alloc counter */
        sk_vas_lock_release(pool, (uint8_t)tok.flags, tok.counter);
        if (block < block_end)
            return block;
    }
    /* fall through to abort */

abort_330b0:
    SK_ASRT_PANIC(0x330b4);
}

/* FUN_00033148 @ 0x00033148  (est. sk_pool_free_0)
 * Ghidra: void FUN_00033148(undefined8 param_1)
 * Releases a page back to the pool whose metadata lives at +0x158 of the
 * 0x3e0-byte backing object, via the core free.
 * Confidence: high
 * Notes: meta window 0x158..0x190. */
static void sk_pool_free_0(uint64_t page)
{
    uint64_t pool;
    sk_vspace_alloc(&pool, 4, 0xd);                 /* FUN_0005acac */
    if (pool <= pool + 0x3e0 && pool + 0x158 <= pool + 400) {
        sk_pool_free(pool, (uint16_t *)(pool + 0x158), (uint64_t *)page);
        return;
    }
    SK_ASRT_PANIC(0x331a0);
}

/* FUN_000331a0 @ 0x000331a0  (est. sk_pool_free)
 * Ghidra: void FUN_000331a0(ulong param_1, ushort *param_2, undefined8 *param_3)
 * Core page-pool free.  Pushes the returned block (param_3) onto the pool's
 * freelist: its three link words capture the current head/tail/secondary
 * pointers, the freelist head/tail/secondary are re-pointed at the block (with
 * the tail set to block+size), the in-flight count and a free counter are
 * incremented.  NULL pages are ignored.
 * Confidence: high
 * Notes: metadata layout shared with sk_pool_alloc (FUN_00032e90). */
static void sk_pool_free(uint64_t pool, uint16_t *meta, uint64_t *page)
{
    sk_vas_lock_tok_t tok;
    uint16_t block_size;
    uint64_t *head, *tail, *mid;

    if (page == 0)
        return;
    if (pool > pool + 0x30)                         /* base overflow guard */
        goto abort_33288;

    tok = sk_vas_lock_acquire(pool);                /* FUN_00034bd8 */

    /* Same meta-offset sanity check as the allocator. */
    if (0xc < (uint64_t)(((long)((long)meta + (-0xe8 - (long)pool)) >> 3) *
                         0x6db6db6db6db6db7L))
        sk_vas_abort("VAS abort in function %s at line %d", __func__, 0x5b0855);

    block_size = meta[0];                           /* +0x00: block size */
    if (page + 3 <= (uint64_t *)((long)page + block_size)) {  /* block fits pool */
        tail = (uint64_t *)*(uint64_t *)((uint8_t *)meta + 0x28); /* freelist tail */
        head = (uint64_t *)*(uint64_t *)((uint8_t *)meta + 0x20); /* freelist head */
        mid  = (uint64_t *)*(uint64_t *)((uint8_t *)meta + 0x30); /* secondary link */
        page[2] = (uint64_t)mid;
        page[1] = (uint64_t)tail;
        page[0] = (uint64_t)head;
        *(uint64_t *)((uint8_t *)meta + 0x28) = (uint64_t)((long)page + block_size);
        *(uint64_t *)((uint8_t *)meta + 0x30) = (uint64_t)page;
        *(int64_t *)((uint8_t *)meta + 8) += 1;     /* in-flight count++ */
        *(int64_t *)((uint8_t *)meta + 0x18) += 1;  /* free counter++ */
        *(uint64_t *)((uint8_t *)meta + 0x20) = (uint64_t)page;
        sk_vas_lock_release(pool, (uint8_t)tok.flags, tok.counter);
        return;
    }

abort_33288:
    SK_ASRT_PANIC(0x33288);
}

/* FUN_000332b8 @ 0x000332b8  (est. sk_pool_alloc_1)
 * Ghidra: void FUN_000332b8(void)
 * Pool-1 allocator; metadata at +400 (0x190) of the backing object.
 * Confidence: high
 * Notes: meta window 0x190..0x1c8. */
static void sk_pool_alloc_1(void)
{
    uint64_t pool;
    sk_vspace_alloc(&pool, 4, 0xd);                 /* FUN_0005acac */
    if (pool <= pool + 0x3e0 && pool + 400 <= pool + 0x1c8) {
        sk_pool_alloc(pool, (uint16_t *)(pool + 400), 1);
        return;
    }
    SK_ASRT_PANIC(0x33304);
}

/* FUN_00033304 @ 0x00033304  (est. sk_pool_free_1)
 * Ghidra: void FUN_00033304(undefined8 param_1)
 * Pool-1 free; metadata at +400 (0x190) of the backing object.
 * Confidence: high
 * Notes: meta window 0x190..0x1c8. */
static void sk_pool_free_1(uint64_t page)
{
    uint64_t pool;
    sk_vspace_alloc(&pool, 4, 0xd);                 /* FUN_0005acac */
    if (pool <= pool + 0x3e0 && pool + 400 <= pool + 0x1c8) {
        sk_pool_free(pool, (uint16_t *)(pool + 400), (uint64_t *)page);
        return;
    }
    SK_ASRT_PANIC(0x3335c);
}

/* FUN_0003335c @ 0x0003335c  (est. sk_pool_alloc_2)
 * Ghidra: void FUN_0003335c(void)
 * Pool-2 allocator; metadata at +0x1c8 of the backing object.
 * Confidence: high
 * Notes: meta window 0x1c8..0x200. */
static void sk_pool_alloc_2(void)
{
    uint64_t pool;
    sk_vspace_alloc(&pool, 4, 0xd);                 /* FUN_0005acac */
    if (pool <= pool + 0x3e0 && pool + 0x1c8 <= pool + 0x200) {
        sk_pool_alloc(pool, (uint16_t *)(pool + 0x1c8), 1);
        return;
    }
    SK_ASRT_PANIC(0x333a8);
}

/* FUN_000333a8 @ 0x000333a8  (est. sk_pool_alloc_3)
 * Ghidra: void FUN_000333a8(void)
 * Pool-3 allocator; metadata at +0x270 of the backing object.
 * Confidence: high
 * Notes: meta window 0x270..0x2a8. */
static void sk_pool_alloc_3(void)
{
    uint64_t pool;
    sk_vspace_alloc(&pool, 4, 0xd);                 /* FUN_0005acac */
    if (pool <= pool + 0x3e0 && pool + 0x270 <= pool + 0x2a8) {
        sk_pool_alloc(pool, (uint16_t *)(pool + 0x270), 1);
        return;
    }
    SK_ASRT_PANIC(0x333f4);
}

/* FUN_000333f4 @ 0x000333f4  (est. sk_pool_free_3)
 * Ghidra: void FUN_000333f4(undefined8 param_1)
 * Pool-3 free; metadata at +0x270 of the backing object.
 * Confidence: high
 * Notes: meta window 0x270..0x2a8. */
static void sk_pool_free_3(uint64_t page)
{
    uint64_t pool;
    sk_vspace_alloc(&pool, 4, 0xd);                 /* FUN_0005acac */
    if (pool <= pool + 0x3e0 && pool + 0x270 <= pool + 0x2a8) {
        sk_pool_free(pool, (uint16_t *)(pool + 0x270), (uint64_t *)page);
        return;
    }
    SK_ASRT_PANIC(0x3344c);
}

/* FUN_0003344c @ 0x0003344c  (est. sk_pool_alloc_4)
 * Ghidra: void FUN_0003344c(void)
 * Pool-4 allocator; metadata at +0x2a8 of the backing object.
 * Confidence: high
 * Notes: meta window 0x2a8..0x2e0. */
static void sk_pool_alloc_4(void)
{
    uint64_t pool;
    sk_vspace_alloc(&pool, 4, 0xd);                 /* FUN_0005acac */
    if (pool <= pool + 0x3e0 && pool + 0x2a8 <= pool + 0x2e0) {
        sk_pool_alloc(pool, (uint16_t *)(pool + 0x2a8), 1);
        return;
    }
    SK_ASRT_PANIC(0x33498);
}

/* FUN_00033498 @ 0x00033498  (est. sk_pool_free_4)
 * Ghidra: void FUN_00033498(undefined8 param_1)
 * Pool-4 free; metadata at +0x2a8 of the backing object.
 * Confidence: high
 * Notes: meta window 0x2a8..0x2e0. */
static void sk_pool_free_4(uint64_t page)
{
    uint64_t pool;
    sk_vspace_alloc(&pool, 4, 0xd);                 /* FUN_0005acac */
    if (pool <= pool + 0x3e0 && pool + 0x2a8 <= pool + 0x2e0) {
        sk_pool_free(pool, (uint16_t *)(pool + 0x2a8), (uint64_t *)page);
        return;
    }
    SK_ASRT_PANIC(0x334f0);
}

/* FUN_000334f0 @ 0x000334f0  (est. sk_pool_alloc_5)
 * Ghidra: void FUN_000334f0(void)
 * Pool-5 allocator; metadata at +0x2e0 of the backing object.
 * Confidence: high
 * Notes: meta window 0x2e0..0x318. */
static void sk_pool_alloc_5(void)
{
    uint64_t pool;
    sk_vspace_alloc(&pool, 4, 0xd);                 /* FUN_0005acac */
    if (pool <= pool + 0x3e0 && pool + 0x2e0 <= pool + 0x318) {
        sk_pool_alloc(pool, (uint16_t *)(pool + 0x2e0), 1);
        return;
    }
    SK_ASRT_PANIC(0x3353c);
}

/* FUN_0003353c @ 0x0003353c  (est. sk_pool_free_5)
 * Ghidra: void FUN_0003353c(undefined8 param_1)
 * Pool-5 free; metadata at +0x2e0 of the backing object.
 * Confidence: high
 * Notes: meta window 0x2e0..0x318. */
static void sk_pool_free_5(uint64_t page)
{
    uint64_t pool;
    sk_vspace_alloc(&pool, 4, 0xd);                 /* FUN_0005acac */
    if (pool <= pool + 0x3e0 && pool + 0x2e0 <= pool + 0x318) {
        sk_pool_free(pool, (uint16_t *)(pool + 0x2e0), (uint64_t *)page);
        return;
    }
    SK_ASRT_PANIC(0x33594);
}

/* FUN_00033594 @ 0x00033594  (est. sk_pool_alloc_6)
 * Ghidra: void FUN_00033594(void)
 * Pool-6 allocator; metadata at +0x318 of the backing object.
 * Confidence: high
 * Notes: meta window 0x318..0x350. */
static void sk_pool_alloc_6(void)
{
    uint64_t pool;
    sk_vspace_alloc(&pool, 4, 0xd);                 /* FUN_0005acac */
    if (pool <= pool + 0x3e0 && pool + 0x318 <= pool + 0x350) {
        sk_pool_alloc(pool, (uint16_t *)(pool + 0x318), 1);
        return;
    }
    SK_ASRT_PANIC(0x335e0);
}

/* FUN_000335e0 @ 0x000335e0  (est. sk_pool_free_6)
 * Ghidra: void FUN_000335e0(undefined8 param_1)
 * Pool-6 free; metadata at +0x318 of the backing object.
 * Confidence: high
 * Notes: meta window 0x318..0x350. */
static void sk_pool_free_6(uint64_t page)
{
    uint64_t pool;
    sk_vspace_alloc(&pool, 4, 0xd);                 /* FUN_0005acac */
    if (pool <= pool + 0x3e0 && pool + 0x318 <= pool + 0x350) {
        sk_pool_free(pool, (uint16_t *)(pool + 0x318), (uint64_t *)page);
        return;
    }
    SK_ASRT_PANIC(0x33638);
}

/* FUN_00033638 @ 0x00033638  (est. sk_pool_alloc_7)
 * Ghidra: void FUN_00033638(void)
 * Pool-7 allocator; metadata at +0x350 of the backing object.
 * Confidence: high
 * Notes: meta window 0x350..0x388. */
static void sk_pool_alloc_7(void)
{
    uint64_t pool;
    sk_vspace_alloc(&pool, 4, 0xd);                 /* FUN_0005acac */
    if (pool <= pool + 0x3e0 && pool + 0x350 <= pool + 0x388) {
        sk_pool_alloc(pool, (uint16_t *)(pool + 0x350), 1);
        return;
    }
    SK_ASRT_PANIC(0x33684);
}

/* FUN_00033684 @ 0x00033684  (est. sk_pool_free_7)
 * Ghidra: void FUN_00033684(undefined8 param_1)
 * Pool-7 free; metadata at +0x350 of the backing object.
 * Confidence: high
 * Notes: meta window 0x350..0x388. */
static void sk_pool_free_7(uint64_t page)
{
    uint64_t pool;
    sk_vspace_alloc(&pool, 4, 0xd);                 /* FUN_0005acac */
    if (pool <= pool + 0x3e0 && pool + 0x350 <= pool + 0x388) {
        sk_pool_free(pool, (uint16_t *)(pool + 0x350), (uint64_t *)page);
        return;
    }
    SK_ASRT_PANIC(0x336dc);
}

/* FUN_000336e0 @ 0x000336e0  (est. sk_pool_alloc_8)
 * Ghidra: void FUN_000336e0(void)
 * Pool-8 allocator; metadata at +0x388 of the backing object.
 * Confidence: high
 * Notes: meta window 0x388..0x3c0. */
static void sk_pool_alloc_8(void)
{
    uint64_t pool;
    sk_vspace_alloc(&pool, 4, 0xd);                 /* FUN_0005acac */
    if (pool <= pool + 0x3e0 && pool + 0x388 <= pool + 0x3c0) {
        sk_pool_alloc(pool, (uint16_t *)(pool + 0x388), 1);
        return;
    }
    SK_ASRT_PANIC(0x33728);
}
