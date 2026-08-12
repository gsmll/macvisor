/* Recreated from cl4_kernel.raw (cL4 Secure Kernel, arm64e, image base 0) —
 * the cL4 microkernel (GL1). Ground truth: Ghidra FUN_ names + addresses.
 * All names are estimates unless string/header matched.
 *
 * SK13 slice (0x65640-0x6a414): the cL4 device-tree parser (Apple
 * device_tree.c) together with the DeviceTreeKit node-name / property /
 * children-iterator primitives and the Swift-runtime growable-buffer helpers
 * (16/24/32-byte element vectors) they are built on.
 *
 * Vocabulary: a "range" is a 4-word struct { base, limit, cursor, end } used
 * to walk a contiguous region; "node" descriptors are 0x24-byte device-tree
 * entries; "iter" structs carry { base, limit, cursor, end, done } for child
 * enumeration.
 */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

typedef uint64_t word_t;

#define CL4_FATAL() __builtin_trap()   /* SoftwareBreakpoint(1,<addr>) path */

/* ---- shared kernel / Swift-runtime externs (not in this slice) ---- */
extern void   FUN_001150e0(word_t);              /* fatal: integer overflow msg */
extern void   FUN_00115424(word_t, word_t, word_t, int); /* assert-style fatal */
extern word_t FUN_00115080(word_t);              /* size getter (thunk) */
extern word_t FUN_00114d10(word_t, word_t);      /* key compare (thunk) */
extern word_t FUN_00114fe0(word_t, word_t);      /* size probe (thunk) */
extern word_t FUN_0036a940(word_t, word_t, word_t); /* Swift array buffer alloc */
extern word_t FUN_0036b270(word_t);              /* Swift object retain */
extern void   FUN_0036b118(word_t);              /* Swift object release */
extern void   FUN_003a25d4(word_t);              /* Swift release (masked) */
extern word_t FUN_003a261c(word_t);              /* buffer-unique check */
extern word_t FUN_003a26e8(word_t, word_t, word_t, word_t, word_t, word_t);
extern word_t FUN_00002534(word_t, word_t);      /* string cache lookup */
extern word_t FUN_00027614(word_t, word_t);      /* class/string builder */
extern word_t FUN_00376820(word_t, word_t);      /* closure adapter */
extern word_t FUN_0001a1c8(word_t);              /* identity/hash helper */
extern word_t FUN_0001cba4(word_t);              /* identity helper */
extern word_t FUN_00027724(word_t);              /* vt lookup */
extern void   FUN_0011d7e8(void);                /* fatal (Swift trap) */
extern void   FUN_00117cc4(word_t, word_t, word_t); /* memcpy */
extern void   FUN_00117d14(word_t, word_t, word_t); /* memmove */
extern void   FUN_0035b67c(word_t, word_t, word_t, word_t); /* memmove+log */
extern void   FUN_00229a3c(int);                 /* lock/bind select */
extern void   FUN_002298d4(word_t);              /* bind helper */
extern void   FUN_001a84f4(word_t, word_t);      /* scoped enter */
extern void   FUN_001a8564(void);                /* scoped exit */
extern void   FUN_0006b2ec(void);                /* nop (identity marker) */
extern void   FUN_000651bc(void);                /* nop */
extern void   FUN_0006b2dc(void);                /* nop */
extern void   FUN_0006b6f4(void);                /* nop */
extern void   FUN_0006b6ac(void);                /* nop */
extern void   FUN_0006b560(void);                /* nop */
extern void   FUN_0006b4d0(void);                /* nop */
extern void   FUN_0006b550(void);                /* nop */
extern void   FUN_0001df60(void);                /* nop */
extern void   FUN_001ba7d4(void);                /* nop */
extern void   FUN_002acbb8(word_t, word_t);      /* string append */
extern void   FUN_002a4ab4(int);                 /* fault builder */
extern void   FUN_00369efc(word_t, word_t, word_t); /* vector op */
extern word_t FUN_0006a374(word_t, word_t, word_t); /* vector realloc (16B elems) */
extern word_t FUN_0006a3cc(word_t, word_t, word_t, word_t); /* lazy init */
extern word_t FUN_000695e4(word_t, word_t, word_t, word_t, word_t, word_t, word_t);
extern word_t FUN_0006a414(void);                /* nop-ish store */
extern word_t FUN_0006b3e0(void);                /* empty-vec builder */
extern word_t FUN_0006b3f4(word_t);              /* vec teardown */
extern word_t FUN_0006b45c(word_t);              /* vec teardown */
extern word_t FUN_0006b42c(void);                /* vec grow */
extern word_t FUN_0006b6a0(void);                /* vec grow */
extern word_t FUN_0006b6d4(void);                /* vec grow */
extern word_t FUN_0006b6c0(void);                /* vec count bump */
extern word_t FUN_0006b620(void);                /* nop */
extern word_t FUN_0006b4c0(void);                /* nop */
extern word_t FUN_0006b4ac(void);                /* nop */
extern word_t FUN_0006b500(void);                /* nop */
extern word_t FUN_0006b528(void);                /* nop */
extern word_t FUN_0006b514(void);                /* nop */
extern word_t FUN_0006b540(void);                /* nop */
extern word_t FUN_0006b68c(void);                /* nop */
extern word_t FUN_0006b640(void);                /* nop */
extern word_t FUN_0006b700(void);                /* nop */
extern word_t FUN_0006b674(void);                /* nop */
extern word_t FUN_0006b610(void);                /* vec mark */
extern word_t FUN_0006b600(void);                /* vec mark */
extern word_t FUN_0006b5a0(void);                /* vec head */
extern word_t FUN_0006b2bc(void);                /* vec head */
extern word_t FUN_0006b2fc(void);                /* alloc */
extern word_t FUN_0006b440(word_t, word_t);      /* store char */
extern word_t FUN_0006b48c(void);                /* nop */
extern word_t FUN_0006b4a0(void);                /* nop */
extern word_t FUN_0006b3d0(void);                /* grow */
extern word_t FUN_0006b3a4(void);                /* nop */
extern word_t FUN_001ebfb0(void);                /* char encode */
extern word_t FUN_001eb088(void);                /* alloc */
extern word_t FUN_001b798c(void);                /* iter next */
extern word_t FUN_001b58b0(word_t, word_t, word_t, word_t); /* copy */
extern word_t FUN_00267510(void);                /* read word pair */
extern word_t FUN_0029fa0c(word_t, word_t);      /* pack */
extern word_t FUN_002a0cf8(word_t, word_t, word_t, word_t, word_t); /* eq check */
extern word_t FUN_0006ae9c(word_t, word_t);      /* tagged union build */
extern void   FUN_0006afb4(word_t, word_t);      /* set start */
extern void   FUN_0006afec(word_t);              /* set release */
extern void   FUN_0006abac(word_t, word_t, word_t); /* vec prep */
extern word_t FUN_001fac04(word_t, word_t);      /* buffer alloc */
extern word_t FUN_00115448(word_t);              /* char class */
extern word_t FUN_0006b680(void);                /* (10,0xe1...) const pair */
extern word_t FUN_0006b388(void);                /* stack buffer ptr */
extern word_t FUN_0006b584(word_t, word_t);      /* "name on(" const */
extern word_t FUN_0006b5c0(void);                /* alloc(8) */
extern word_t FUN_0006b5e0(void);                /* alloc(8) */
extern word_t FUN_0006b330(void);                /* alloc(8) */
extern void   FUN_0006b374(void);                /* string init */
extern void   FUN_0006b728(void);                /* nop */
extern void   FUN_0006b714(void);                /* nop */
extern void   FUN_0006b65c(void);                /* nop */
extern void   FUN_001bdb28(void);                /* nop */
extern void   FUN_001bea18(word_t, word_t, word_t); /* bind */
extern void   FUN_000026e8(word_t);              /* dealloc */
extern void   FUN_0006a4c0(word_t, word_t);      /* vec prep */
extern void   FUN_0006a4f0(word_t);              /* vec release */
extern void   FUN_0006a668(word_t);              /* vec release */
extern void   FUN_0006a520(void);                /* nop */
extern void   FUN_0006a5e4(void);                /* nop */
extern void   FUN_0006b404(void);                /* nop */
extern void   FUN_0006b6e0(void);                /* nop */
extern word_t FUN_0001a1c8(word_t);              /* hash */
extern word_t FUN_0001cba4(word_t);              /* hash */
extern void   FUN_0036b21c(void);                /* closure free */
extern word_t FUN_0006b360(word_t, word_t, word_t); /* vec wrap */
extern void   FUN_002060d4(word_t, word_t, word_t, word_t); /* str fmt */
extern void   FUN_002a3e64(word_t, word_t, word_t, word_t); /* str append */
extern word_t FUN_0006b6c0(void);
extern word_t FUN_001bc440(word_t, word_t, word_t, word_t); /* pair pack */
extern word_t FUN_0006b6f4(void);
extern word_t FUN_001b798c(void);
extern word_t FUN_0006b6a0(void);
extern word_t FUN_0006b42c(void);
extern void   FUN_0006b4c0(void);
extern word_t FUN_0006b5a0(void);
extern word_t FUN_0006b2bc(void);
extern word_t FUN_0006a3cc(word_t, word_t, word_t, word_t);
extern void   FUN_0006b700(void);
extern void   FUN_0006b640(void);
extern void   FUN_0006b674(void);
extern word_t FUN_0006b610(void);
extern word_t FUN_0006b600(void);
extern void   FUN_0006b540(void);
extern void   FUN_0006b68c(void);
extern word_t FUN_001ebfb0(void);
extern word_t FUN_0006b500(void);
extern word_t FUN_0006b528(void);
extern word_t FUN_0006b514(void);
extern word_t FUN_0006b3d0(void);
extern word_t FUN_0006b3f4(word_t);
extern word_t FUN_0006b45c(word_t);
extern word_t FUN_0006b4ac(void);
extern word_t FUN_0006b620(void);
extern word_t FUN_0006b6d4(void);
extern word_t FUN_0006b6e0(void);
extern word_t FUN_00229a3c(int);
extern word_t FUN_002298d4(word_t);
extern word_t FUN_001a84f4(word_t, word_t);
extern word_t FUN_001a8564(void);
extern word_t FUN_0001a1c8(word_t);
extern void   FUN_00369efc(word_t, word_t, word_t);
extern void   FUN_0006abac(word_t, word_t, word_t);
extern word_t FUN_001fac04(word_t, word_t);
extern void   FUN_0006a4c0(word_t, word_t);
extern void   FUN_0006a4f0(word_t);
extern void   FUN_0006a668(word_t);
extern void   FUN_0006a698(word_t);
extern void   FUN_0006a7c8(word_t);
extern void   FUN_0006a520(void);
extern void   FUN_0006a5e4(void);
extern void   FUN_0006b404(void);
extern void   FUN_0006b728(void);
extern void   FUN_0006b714(void);
extern void   FUN_0006b65c(void);
extern void   FUN_001bdb28(void);
extern void   FUN_001bea18(word_t, word_t, word_t);
extern void   FUN_000026e8(word_t);
extern void   FUN_0006b3a4(void);
extern word_t FUN_0006a374(word_t, word_t, word_t);
extern word_t FUN_0006a3cc(word_t, word_t, word_t, word_t);
extern void   FUN_0006b6f4(void);
extern word_t FUN_00115448(word_t);
extern word_t FUN_0006b584(word_t, word_t);
extern word_t FUN_0006b330(void);
extern word_t FUN_0006b5c0(void);
extern word_t FUN_0006b5e0(void);
extern void   FUN_0006b374(void);
extern word_t FUN_0006b680(void);
extern word_t FUN_0006b388(void);
extern void   FUN_0006b6ac(void);
extern word_t FUN_0006b3e0(void);
extern void   FUN_0006a414(void);

/* ---- forward decls within this slice ---- */
static word_t dt_find_entry(word_t list_head, word_t key, word_t *out_payload);
static word_t dt_range_make(word_t base, word_t size, word_t *out_range);
static word_t dt_range_end(word_t *range);
static word_t dt_range_advance(word_t *range);
static word_t dt_range_set(word_t base, word_t size, word_t *out_range);
static word_t dt_node_next(word_t *iter);
static word_t dt_node_get(word_t *iter, word_t *out_node, word_t *out_size);
static word_t dt_node_name_eq(word_t *iter, word_t name);
static word_t dt_node_name_propcount(word_t *iter, word_t *out_name, word_t *out_nprop);
static word_t dt_find_child(word_t *iter, word_t name, word_t *out_node, word_t *out_nprop);
static word_t dt_iter_end(word_t *iter);
static word_t dt_iter_advance(word_t *iter);
static word_t dt_children(word_t *node, word_t *out_iter);
static word_t dt_iter_current(word_t *iter);
static word_t dt_walk(word_t root, word_t *iter, word_t cb, word_t ctx);
static word_t dt_list_at(word_t *head, word_t idx, word_t *out);
static word_t dt_list_len(word_t *head);
static void   dt_overflow_fatal(void);
static void   dt_nop(void);
static word_t dt_parse_root(word_t *out_root);
static word_t dt_validate(word_t base, word_t size, word_t *out);
static word_t dt_validate_range(word_t base, word_t size, word_t *out);
static word_t dt_walk_cb(word_t base, word_t size, word_t cb, word_t ctx);
static word_t dt_integrity_parse(word_t base, word_t size, word_t *out);
static word_t dt_iterator_next(word_t base, word_t limit, word_t *out_iter);
static word_t dt_name_compare(word_t *iter, word_t name);
static word_t dt_next_plain(word_t *iter);

/*============================================================================
 * Device-tree parser core
 *==========================================================================*/

/* FUN_00065640 @ 0x65640  (est. dt_find_entry)
 * Walk a singly-linked list of variable-size entries (each entry stores its
 * own size at offset 0x10 and its next-entry delta in word 0).  Compare each
 * entry's key (at 0x10) with the supplied key; on match write the entry's
 * first word to *out_payload and return the payload pointer (entry base + 8
 * aligned up), else 0.
 * Confidence: medium (structural; FUN_00115080=size, FUN_00114d10=compare) */
static word_t dt_find_entry(word_t list_head, word_t key, word_t *out_payload)
{
    word_t node = list_head;

    while (node != 0) {
        word_t keyptr = node + 0x10;
        word_t sz = FUN_00115080(keyptr);
        word_t payload = (sz + keyptr) & ~7ull;   /* align up to 8 */
        payload += 8;
        if (FUN_00114d10(keyptr, key) == 0) {      /* match */
            if (out_payload != 0)
                *out_payload = *(word_t *)node;
            return payload;
        }
        if (*(word_t *)(node + 8) == 0)            /* end of list */
            return 0;
        node = payload + (*(word_t *)node + 7) & ~7ull;
    }
    return 0;
}

/* FUN_000656d8 @ 0x656d8  (est. dt_set_list_head)
 * Store the device-tree root handle into the global list-head slot used by
 * dt_find_entry's wrapper.  Confidence: high (structural) */
static void dt_set_list_head(word_t root)
{
    *(volatile word_t *)0x6b2738 = root;
}

/* FUN_000656e4 @ 0x656e4  (est. dt_lookup_root)
 * Look up an entry by key in the globally cached device-tree list.
 * Confidence: high (structural) */
static word_t dt_lookup_root(word_t key, word_t *out_payload)
{
    return dt_find_entry(*(word_t *)0x6b2738, key, out_payload);
}

/* FUN_000656f8 @ 0x656f8  (est. dt_build_root_iter)
 * Build a device-tree iterator from the global root pointer/size slots
 * (DAT_006b2740/48/50).  If the cache flag is not yet set, validate the
 * device tree (dt_validate) and, on success, fill the global cache and the
 * caller's {base,limit} out pair.
 * Confidence: medium */
static word_t dt_build_root_iter(word_t *out)
{
    word_t root = *(word_t *)0x6b2748;
    if (*(volatile char *)0x6b2740 == 1) {
        out[1] = *(word_t *)0x6b2750;
        out[0] = root;
        return 1;
    }
    if (*(word_t *)(0x68a4c8 + 6) == 0) {
        return 0;
    }
    {
        word_t rng[2] = { 0, 0 };
        if ((word_t)(0x68a4c8 + 6) + (word_t)0x6b2748 < (word_t)0x6b2748)
            CL4_FATAL();                            /* SoftwareBreakpoint 0x5519 */
        word_t rc = dt_validate(0x6b2748, *(word_t *)(0x68a4c8 + 6), rng);
        if ((int)rc != 0) {
            *(word_t *)0x6b2750 = rng[1];
            *(word_t *)0x6b2748 = rng[0];
            *(volatile char *)0x6b2740 = 1;
            out[1] = rng[1];
            out[0] = rng[0];
        }
        return rc;
    }
}

/* FUN_000657ac @ 0x657ac  (est. dt_validate_root)
 * Validate a base/size device-tree region: run dt_validate then walk the
 * tree applying dt_integrity_parse (integrity parse call).  On success write
 * {base,size} to *out.
 * Confidence: medium */
static word_t dt_validate_root(word_t base, word_t size, word_t *out)
{
    word_t rng[2] = { 0, 0 };
    if (dt_validate_range(base, size, rng) != 0) {
        char ctx[16];
        word_t a[2] = { rng[0], rng[1] };
        ctx[0] = 1;
        dt_walk_cb(rng[0], rng[1], (word_t)dt_integrity_parse, (word_t)&ctx);
        if (ctx[0] == 1) {
            out[0] = base;
            out[1] = size;
        }
    }
    return 0;
}

/* FUN_00065838 @ 0x65838  (est. dt_validate_range)
 * Validate that base/size is a well-formed device-tree region (size > 8):
 * build a range, iterate it to its end to confirm it parses, then write
 * {base, validated_size} to *out and return success.
 * Confidence: medium */
static word_t dt_validate_range(word_t base, word_t size, word_t *out)
{
    word_t rng[4] = { 0, 0, 0, 0 };
    word_t rc = dt_range_make(base, size, rng);
    if ((int)rc != 0) {
        while (!(dt_range_end(rng) & 1))
            dt_range_advance(rng);
        if (size < rng[2]) {
            return 0;
        } else {
            out[0] = base;
            out[1] = rng[2];
            return 1;
        }
    }
    return 0;
}

/* FUN_000658c4 @ 0x658c4  (est. dt_walk_root_cb)
 * Walk the whole device-tree region {base,size} calling cb for every node.
 * Confidence: high (structural) */
static word_t dt_walk_root_cb(word_t base, word_t size, word_t cb, word_t ctx)
{
    word_t rng[2];
    rng[0] = base;
    rng[1] = size;
    return dt_walk(base, rng, cb, ctx);
}

/* FUN_000658f0 @ 0x658f0  (est. dt_integrity_parse)
 * Integrity parse of one device-tree region: fetch the root descriptor via
 * dt_list_at, walk its property and child entries, advancing a cursor so the
 * caller learns the region's true extent.  Panics on a NULL region, on an
 * integer overflow of the cursor, and on any malformed descriptor.
 * Confidence: medium (string refs: device_tree_integrity_parse_call) */
static word_t dt_integrity_parse(word_t base, word_t size, word_t *out)
{
    if (base == 0)
        FUN_00115424((word_t)"context is NULL", (word_t)"__AppleInternal/Library/BuildRoot",
                     (word_t)"device_tree_integrity_parse_call", 0x90);
    {
        word_t cursor = 0;
        word_t rng[4] = { 0, 0, 0, 0 };
        word_t rc = dt_list_at((word_t *)base, 0, &cursor);
        if ((rc & 1) && cursor != 0 && rng[1] != 0 && rng[1] > 7) {
            /* descriptor { base, limit, cursor, end } */
            rng[2] = cursor;
            if (*((word_t *)base) == cursor) {
                if (cursor > 0xfffffffffffffff7ull)
                    dt_overflow_fatal();
                *((word_t *)base) = cursor + 8;
                while (1) {
                    rc = dt_iter_end(&rng[2]);
                    if ((rc & 1) != 0)
                        return 0;
                    rng[0] = 0;
                    rng[1] = 0;
                    if (dt_node_get(&rng[2], &rng[0], &rng[1]) == 0 ||
                        *((word_t *)base) != rng[0])
                        break;
                    if (rng[0] > 0xffffffffffffffdbull)
                        dt_overflow_fatal();
                    *((word_t *)base) = rng[0] + 0x24;
                    {
                        word_t p[2] = { 0, 0 };
                        if (dt_node_name_propcount(&rng[2], &p[0], &p[1]) == 0 ||
                            *((word_t *)base) != p[0])
                            break;
                        {
                            word_t adv = (p[1] + 3) & ~3ull;
                            if (adv + p[0] < adv)
                                dt_overflow_fatal();
                            *((word_t *)base) = adv + p[0];
                        }
                        dt_iter_advance(&rng[2]);
                    }
                }
            }
        }
        *(volatile char *)((word_t *)base + 1) = 0;
    }
    return 1;
}

/* FUN_00065a3c @ 0x65a3c  (est. dt_range_make)
 * Build a 4-word range {base, limit, cursor=0, end} from base/size after
 * verifying base != 0, size > 8 and end <= limit.  Returns 1 on success.
 * Confidence: high (structural) */
static word_t dt_range_make(word_t base, word_t size, word_t *out)
{
    if ((base != 0) && (size != 0) && (size > 7)) {
        word_t end = *(word_t *)0x4be8e8;
        out[0] = base;
        out[1] = size;
        while (!(dt_iter_end(out) & 1))
            dt_iter_advance(out);
        if (end <= size) {
            out[0] = base;
            out[1] = size;
            out[2] = 0;
            out[3] = end;
            return 1;
        }
    }
    return 0;
}

/* FUN_00065ad0 @ 0x65ad0  (est. dt_range_end)
 * Return whether the range iterator has reached its end.
 * Confidence: high (structural) */
static word_t dt_range_end(word_t *range)
{
    return dt_iter_current(range) == 0;
}

/* FUN_00065af0 @ 0x65af0  (est. dt_range_advance)
 * Advance a children iterator one step: fetch the next child descriptor via
 * dt_node_next, validate it into a sub-range, accumulate its extent into
 * node->extent (param_1+0x18) and increment the child count (param_1+0x10).
 * Returns the iterator-end status.
 * Confidence: medium */
static word_t dt_range_advance(word_t *range)
{
    word_t node[2] = { 0, 0 };
    if (dt_node_next(range, node) == 0) {
        return 1;
    } else {
        word_t sub[4] = { 0, 0, 0, 0 };
        if ((int)dt_range_make(node[0], node[1], sub) != 0) {
            while (!(dt_range_end(sub) & 1))
                dt_range_advance(sub);
            if (sub[2] + *(word_t *)((word_t)range + 0x18) < sub[2])
                dt_overflow_fatal();
            *(word_t *)((word_t)range + 0x18) = sub[2] + *(word_t *)((word_t)range + 0x18);
            if (*(word_t *)((word_t)range + 0x10) > 0xfffffffffffffffeull)
                dt_overflow_fatal();
            *(word_t *)((word_t)range + 0x10) = *(word_t *)((word_t)range + 0x10) + 1;
            return dt_range_end(range);
        }
    }
    return 0;
}

/* FUN_00065b94 @ 0x65b94  (est. dt_range_set)
 * Fill a 4-word range {base, limit, cursor, end} from base/size without any
 * validation beyond base != 0 and size > 8.
 * Confidence: high (structural) */
static word_t dt_range_set(word_t base, word_t size, word_t *out)
{
    if ((base != 0 && size != 0) && size > 7) {
        out[0] = base;
        out[1] = size;
        out[2] = *(word_t *)0x4be8e0;
        out[3] = *(word_t *)0x4be8e8;
    }
    return 0;
}

/* FUN_00065bc4 @ 0x65bc4  (est. dt_node_get)
 * Fetch the current device-tree node descriptor: return its base in *out_node
 * and its size (the length field at +0x20 masked to 31 bits) in *out_size.
 * Panics if the descriptor overflows or exceeds the iterator limit.
 * Confidence: high (structural) */
static word_t dt_node_get(word_t *iter, word_t *out_node, word_t *out_size)
{
    word_t node = dt_node_next(iter);
    if (node != 0) {
        if ((node + 0x24 < node) || FUN_00114fe0(node, 0x20) > 0x20)
            CL4_FATAL();                            /* SoftwareBreakpoint 0x5519 */
        *out_node = node;
        *out_size = FUN_00114fe0(node, 0x20);
    }
    return node != 0;
}

/* FUN_00065c30 @ 0x65c30  (est. dt_node_next)
 * Return the current device-tree node descriptor pointer from the iterator,
 * advancing the internal cursor past it.  Bounds-validates every pointer
 * arithmetic against the iterator's base/limit and panics on overflow.
 * The node's length field (+0x20) is masked to 31 bits (bit 31 = continue
 * flag).
 * Confidence: medium */
static word_t dt_node_next(word_t *iter)
{
    word_t base = *(word_t *)iter;
    word_t limit = iter[1];
    if ((base != 0) && (limit != 0)) {
        if ((word_t)(base + limit) < base + 8 || base + 8 < base)
            CL4_FATAL();
        if (iter[2] < (word_t)*(unsigned int *)(base + 4)) {
            word_t off = iter[3];
            if (off > 0xffffffffffffffdbull)
                dt_overflow_fatal();
            if (off + 0x24 <= limit) {
                word_t node = base + off;
                if (node == 0)
                    return 0;
                if ((base <= node && node + 0x24 <= base + limit) && node <= node + 0x24)
                    return node;
                CL4_FATAL();
            }
        }
    }
    return 0;
}

/* FUN_00065d18 @ 0x65d18  (est. dt_name_compare)
 * Compare the current node's name string with the supplied name; return 1 if
 * equal (both NUL-terminated).  Confidence: medium */
static word_t dt_name_compare(word_t *iter, word_t name)
{
    word_t node;
    word_t namelen;
    dt_nop();
    if (dt_node_get(iter, &node, &namelen) != 0) {
        word_t i = 0;
        char c;
        while ((c = *(char *)(node + i), c != '\0') && i < namelen) {
            if (c != *(char *)(name + i))
                return 0;
            i = i + 1;
        }
        if (i < namelen)
            c = *(char *)(name + i);
        return (word_t)(c == '\0');
    }
    return 0;
}

/* FUN_00065d98 @ 0x65d98  (est. dt_node_name_propcount)
 * Fetch the current node's data pointer (*out_name = node + 0x24) and its
 * property count (the length field at +0x20, masked to 31 bits) in *out_nprop.
 * Confidence: high (structural) */
static word_t dt_node_name_propcount(word_t *iter, word_t *out_name, word_t *out_nprop)
{
    word_t node = dt_node_next(iter);
    if (node != 0) {
        if (node + 0x24 < node)
            CL4_FATAL();
        *out_name = node + 0x24;
        *out_nprop = (word_t)(*(unsigned int *)(node + 0x20) & 0x7fffffff);
    }
    return node != 0;
}

/* FUN_00065dec @ 0x65dec  (est. dt_find_child)
 * Iterate the children of the given node, returning the first child whose
 * name matches `name` (its node pointer and property count via out args).
 * Confidence: medium */
static word_t dt_find_child(word_t *iter, word_t name, word_t *out_node, word_t *out_nprop)
{
    if ((iter != 0) && (name != 0) && (name > 7)) {
        word_t range[4] = { 0, 0, 0, 0 };
        word_t base = iter[0];
        word_t limit = iter[1];
        range[0] = base;
        range[1] = limit;
        range[2] = *(word_t *)0x4be8e0;
        range[3] = *(word_t *)0x4be8e8;
        while (!(dt_iter_end(range) & 1)) {
            if (dt_name_compare(range, name) != 0)
                return dt_node_name_propcount(range, out_node, out_nprop);
            dt_iter_advance(range);
        }
    }
    return 0;
}

/* FUN_00065e90 @ 0x65e90  (est. dt_iter_end)
 * Return whether the children iterator is at its end (current node is 0).
 * Confidence: high (structural) */
static word_t dt_iter_end(word_t *iter)
{
    word_t node = dt_node_next(iter);
    if (node <= node + 0x24)
        return node == 0;
    CL4_FATAL();
}

/* FUN_00065ec0 @ 0x65ec0  (est. dt_iter_advance)
 * Advance the children iterator to the next sibling: add the current node's
 * size (length field masked to 31 bits, rounded up to 4) to the cursor and
 * increment the node index, returning the new end status.  Panics on cursor
 * overflow or index wraparound.
 * Confidence: medium */
static word_t dt_iter_advance(word_t *iter)
{
    word_t node = dt_node_next(iter);
    if (node == 0)
        return 1;
    if (node + 0x24 < node)
        CL4_FATAL();
    {
        word_t sz = ((*(unsigned int *)(node + 0x20) & 0x7fffffff) + 0x27) & ~3ull;
        if (iter[3] + sz < iter[3])
            dt_overflow_fatal();
        iter[3] = iter[3] + sz;
        if (iter[2] != (word_t)-1) {
            iter[2] = iter[2] + 1;
            return dt_iter_end(iter);
        }
        dt_overflow_fatal();
    }
}

/* FUN_00065f48 @ 0x65f48  (est. dt_children)
 * Start iterating the children of the node whose extent/limit live at
 * param_1+8 / param_1+0x18: build {base=node_children, limit, cursor, end}
 * into *out_iter.  Confidence: medium */
static word_t dt_children(word_t *node, word_t *out_iter)
{
    word_t cur = dt_iter_current(node);
    word_t rc = 0;
    if (cur != 0) {
        word_t nodebase = *(word_t *)((word_t)node + 8);
        word_t extent  = *(word_t *)((word_t)node + 0x18);
        if (nodebase < extent)
            FUN_00115424((word_t)"iterator > node_size > __iterator",
                         (word_t)"__AppleInternal/Library/BuildRoot",
                         (word_t)"device_tree_node_children_iterat", 0x239);
        if (cur + (nodebase - extent) < cur)
            CL4_FATAL();
        out_iter[0] = cur;
        out_iter[1] = nodebase - extent;
        {
            word_t sub[4] = { 0, 0, 0, 0 };
            rc = dt_range_make(cur, nodebase - extent, sub);
            if ((int)rc != 0) {
                while (!(dt_range_end(sub) & 1))
                    dt_range_advance(sub);
                if ((word_t)(nodebase - extent) < sub[2]) {
                    rc = 0;
                } else {
                    if (cur + sub[2] < cur)
                        CL4_FATAL();
                    out_iter[0] = cur;
                    out_iter[1] = sub[2];
                    rc = 1;
                }
            }
        }
    }
    return rc;
}

/* FUN_00066030 @ 0x66030  (est. dt_iter_current)
 * Return the current device-tree descriptor pointer from the iterator,
 * or 0 at end.  Bounds-validates against base/limit.
 * Confidence: high (structural) */
static word_t dt_iter_current(word_t *iter)
{
    word_t base = iter[0];
    if ((base == 0) || (iter[1] == 0))
        return 0;
    if (base + iter[1] < base + 8 || base + 8 < base)
        CL4_FATAL();
    if (iter[2] < (word_t)*(unsigned int *)(base + 4)) {
        word_t off = iter[3];
        if (off > 0xfffffffffffffff7ull)
            dt_overflow_fatal();
        if (off + 8 <= iter[1]) {
            word_t node = base + off;
            if (node == 0)
                return 0;
            if ((base <= node && node + 8 <= base + iter[1]) && node <= node + 8)
                return node;
            CL4_FATAL();
        }
    }
    return 0;
}

/* FUN_000660bc @ 0x660bc  (est. dt_walk)
 * Recursively walk every descendant of the given device-tree region, invoking
 * cb(region) for each node; stop early if cb returns success (bit0 set).
 * Returns 1 if the walk completed (or was short-circuited) cleanly.
 * Confidence: medium */
static word_t dt_walk(word_t root, word_t *iter, word_t cb, word_t ctx)
{
    word_t region = root;
    word_t rc = ((word_t (*)(word_t, word_t))cb)(ctx, &region);
    if ((rc & 1) == 0) {
        word_t rng[4] = { 0, 0, 0, 0 };
        rc = dt_range_make(iter[0], iter[1], rng);
        if ((int)rc != 0) {
            word_t done;
            while (!((done = dt_range_end(rng)) & 1)) {
                word_t child[2] = { 0, 0 };
                rc = dt_children(rng, child);
                if ((int)rc == 0)
                    return rc;
                rc = dt_walk(region, child, cb, ctx);
                if ((rc & 1) != 0)
                    break;
                dt_range_advance(rng);
            }
            rc = (word_t)(done ^ 1);
        }
    } else {
        rc = 1;
    }
    return rc;
}

/* FUN_00066178 @ 0x66178  (est. dt_list_at)
 * Index into a singly-linked list of (next, payload) entries: return the
 * payload of the entry at index `idx` in *out (two words).  Panics on index
 * overflow (list longer than 2^64-2).
 * Confidence: medium */
static word_t dt_list_at(word_t *head, word_t idx, word_t *out)
{
    word_t i = 0;
    do {
        if (head == 0)
            return head != 0;
        if (idx == i) {
            out[0] = *(word_t *)head[1];
            out[1] = ((word_t *)head[1])[1];
            return head != 0;
        }
        if (i > 0xfffffffffffffffeull)
            dt_overflow_fatal();
        head = (word_t *)*head;
        i = i + 1;
    } while (1);
}

/* FUN_000661cc @ 0x661cc  (est. dt_list_len)
 * Return the length of a singly-linked list.  Panics on count overflow.
 * Confidence: high (structural) */
static word_t dt_list_len(word_t *head)
{
    word_t n = 0;
    while (1) {
        if (head == 0)
            return n;
        if (n > 0xfffffffffffffffeull)
            break;
        head = (word_t *)*head;
        n = n + 1;
    }
    dt_overflow_fatal();
}

/* FUN_00066204 @ 0x66204  (est. dt_overflow_fatal)
 * Fatal trap on integer overflow.  Noreturn.  Confidence: high (structural) */
static void dt_overflow_fatal(void)
{
    FUN_001150e0((word_t)"integer overflow");
}

/* FUN_00066210 @ 0x66210  (est. dt_nop)
 * No-op marker.  Confidence: high */
static void dt_nop(void)
{
    return;
}

/* FUN_00066224 @ 0x66224  (est. dt_thunk_build_root_iter) */
static void dt_thunk_build_root_iter(void) { dt_build_root_iter(); }

/* FUN_0006623c @ 0x6623c  (est. dt_thunk_validate_root) */
static void dt_thunk_validate_root(void) { dt_validate_root(); }

/* FUN_00066254 @ 0x66254  (est. dt_thunk_validate_range) */
static void dt_thunk_validate_range(void) { dt_validate_range(); }

/* FUN_0006626c @ 0x6626c  (est. dt_thunk_walk_root_cb) */
static void dt_thunk_walk_root_cb(void) { dt_walk_root_cb(); }

/* FUN_00066284 @ 0x66284  (est. dt_thunk_list_at) */
static void dt_thunk_list_at(void) { dt_list_at(); }

/* FUN_000662a0 @ 0x662a0  (est. dt_thunk_find_child) */
static void dt_thunk_find_child(void) { dt_find_child(); }

/* FUN_000662b8 @ 0x662b8  (est. dt_thunk_range_set) */
static void dt_thunk_range_set(void) { dt_range_set(); }

/* FUN_000662d0 @ 0x662d0  (est. dt_thunk_iter_advance) */
static void dt_thunk_iter_advance(void) { dt_iter_advance(); }

/* FUN_000662e8 @ 0x662e8  (est. dt_thunk_iter_end) */
static void dt_thunk_iter_end(void) { dt_iter_end(); }

/* FUN_00066300 @ 0x66300  (est. dt_thunk_node_get) */
static void dt_thunk_node_get(void) { dt_node_get(); }

/* FUN_00066318 @ 0x66318  (est. dt_thunk_node_name_propcount) */
static void dt_thunk_node_name_propcount(void) { dt_node_name_propcount(); }

/* FUN_00066330 @ 0x66330  (est. dt_thunk_range_make) */
static void dt_thunk_range_make(void) { dt_range_make(); }

/* FUN_00066348 @ 0x66348  (est. dt_thunk_range_end) */
static void dt_thunk_range_end(void) { dt_range_end(); }

/* FUN_00066360 @ 0x66360  (est. dt_thunk_range_advance) */
static void dt_thunk_range_advance(void) { dt_range_advance(); }

/* FUN_00066378 @ 0x66378  (est. dt_thunk_children) */
static void dt_thunk_children(void) { dt_children(); }

/*============================================================================
 * DeviceTreeKit node-name / property services
 *==========================================================================*/

/* FUN_00066390 @ 0x66390  (est. dtk_build_root_name_iter)
 * Build a root node iterator: allocate the root range (dt_build_root_iter)
 * and, if it succeeded, wrap it for the DeviceTreeKit name walker.  Fatal on
 * failure.  Confidence: medium (Swift runtime call pattern) */
static word_t dtk_build_root_name_iter(void)
{
    FUN_0006b2ec();
    FUN_000651bc();
    {
        word_t rng[2] = { 0, 0 };
        word_t rc = dt_build_root_iter(rng);
        bool ok = (rc & 1) != 0;
        word_t base = rng[0], limit = rng[1];
        if (!ok) { base = 0; limit = 0; }
        FUN_0006b360(base, rc, limit);
        if (!ok)
            FUN_0011d7e8();
    }
    return 0;
}

/* FUN_00066424 @ 0x66424  (est. dtk_build_root_validate_iter)
 * Validate the device-tree root and wrap it into a DeviceTreeKit iterator;
 * fatal on failure.  Confidence: medium */
static void dtk_build_root_validate_iter(void)
{
    word_t base = FUN_0006b2ec();
    if (base == 0) {
        FUN_000651bc();
    } else {
        word_t rng[2] = { 0, 0 };
        word_t rc = dt_validate_root(base, 0 - base, rng);
        bool ok = (rc & 1) != 0;
        word_t a = rng[0], b = rng[1];
        if (!ok) { a = 0; b = 0; }
        FUN_000651bc(0, a, b);
        if (ok)
            return;
        FUN_0011d7e8();
    }
}

/* FUN_0006649c @ 0x6649c  (est. dtk_validate_range_wrap)
 * Validate a device-tree range and wrap it for DeviceTreeKit; fatal on
 * failure.  Confidence: medium */
static word_t dtk_validate_range_wrap(void)
{
    word_t base = FUN_0006b2ec();
    word_t size = FUN_0006b2ec();
    {
        word_t rng[2] = { 0, 0 };
        word_t rc = dt_validate_range(base, size, rng);
        bool ok = (rc & 1) != 0;
        word_t a = rng[0], b = rng[1];
        if (!ok) { a = 0; b = 0; }
        FUN_0006b360(a, rc, b);
        if (!ok)
            FUN_0011d7e8();
    }
    return 0;
}

/* FUN_000664f8 @ 0x664f8  (est. dtk_prop_call)
 * Invoke a property callback stored in a two-word descriptor {fn, retainable};
 * retain the context object, call fn(ctx, key), then release it.  Returns
 * the callback's byte result, or 1 when the descriptor is NULL.
 * Confidence: medium (FUN_0036b270/3a... retain/release) */
static word_t dtk_prop_call(word_t *desc, word_t key)
{
    if (desc != 0) {
        word_t (*fn)(word_t, word_t) = (word_t (*)(word_t, word_t))desc[0];
        word_t ctx = desc[1];
        word_t out;
        FUN_0036b270(ctx);
        out = fn(&out, key);
        FUN_0036b118(ctx);
        return out;
    }
    return 1;
}

/* FUN_00066558 @ 0x66558  (est. dtk_prop_lookup)
 * Look up a device-tree property: build a {key,key} record and a {call,ctx}
 * closure, retain them, run dt_walk_root_cb, release, then verify the result
 * is valid via FUN_003a26e8.  Panics if the closure's verification fails.
 * Confidence: medium */
static word_t dtk_prop_lookup(word_t a, word_t b, word_t c, word_t d)
{
    FUN_0006b2ec();
    {
        word_t rec = FUN_0036a940(0x65c908, 0x20, 7);
        *(word_t *)(rec + 0x10) = a;
        *(word_t *)(rec + 0x18) = b;
        word_t clo = FUN_0036a940(0x65c930, 0x20, 7);
        *(word_t *)(clo + 0x10) = (word_t)dtk_lookup_apply;
        *(word_t *)(clo + 0x18) = rec;
        word_t cc[2];   /* {dt_walk_cb, clo} closure pair */
        cc[0] = (word_t)dtk_prop_thunk;
        cc[1] = clo;
        FUN_0036b270(rec);
        word_t rc = dt_walk_root_cb(c, d, (word_t)dtk_prop_thunk, (word_t)&cc);
        FUN_0036b118(clo);
        if (!(FUN_003a26e8(rec, &DAT_005be7c0, 0xd3, 0x5d, 9, 0) & 1))
            CL4_FATAL();
        FUN_0036b118(rec);
        FUN_000651bc();
        return rc & 1;
    }
}

/* FUN_00066690 @ 0x66690  (est. dtk_prop_apply)
 * Apply the stored property function (vtable at x20+0x10) and return its
 * low bit.  Confidence: medium */
static word_t dtk_prop_apply(void)
{
    return (**(word_t (***)(void))(0 + 0x10))() & 1;
}

/* FUN_000666bc @ 0x666bc  (est. dtk_prop_release)
 * Release the closure's captured record and free the closure.
 * Confidence: medium */
static void dtk_prop_release(void)
{
    FUN_0036b118(*(word_t *)(0 + 0x18));
    FUN_0036b21c();
}

/* FUN_000666c0 @ 0x666c0  (est. dtk_prop_release_2)
 * Release the closure's captured record and free the closure (variant).
 * Confidence: medium */
static void dtk_prop_release_2(void)
{
    FUN_0036b118(*(word_t *)(0 + 0x18));
    FUN_0036b21c();
}

/* FUN_000666e8 @ 0x666e8  (est. dtk_prop_call_byte)
 * Call the stored property function with the key and store the low bit of
 * the result into *out.  Confidence: medium */
static void dtk_prop_call_byte(word_t *out, word_t *key)
{
    word_t r = (**(word_t (***)(word_t))(0 + 0x10))(*key);
    *out = (word_t)(r & 1);
}

/* FUN_00066720 @ 0x66720  (est. dtk_prop_apply_wrap) */
static word_t dtk_prop_apply_wrap(void) { return dtk_prop_call(0, 0) & 1; }

/* FUN_00066724 @ 0x66724  (est. dtk_prop_apply_wrap_2) */
static word_t dtk_prop_apply_wrap_2(void) { return dtk_prop_call(0, 0) & 1; }

/* FUN_0006673c @ 0x6673c  (est. dtk_node_name_or_scope)
 * Return the node-name (or scoped-name) string for a device-tree entry keyed
 * by (kind, id).  Uses the appropriate name table (DAT_005c99ee) and the
 * DeviceTreeKit name resolver.  Panics if no name is produced.
 * Confidence: low (Swift call chain, exact string tables unknown) */
static word_t dtk_node_name_or_scope(word_t kind, word_t id)
{
    word_t res = dt_name_resolve(&DAT_005c99ee, kind);
    if ((id & 0xff) == 1) {
        return 0;
    } else {
        FUN_0006b374();
        FUN_000668a0();
        FUN_00066950();
        word_t nm = FUN_0006b330();
        if (FUN_0006b330() == 0)
            CL4_FATAL();
        return nm;
    }
}

/* FUN_00066804 @ 0x66804  (est. dt_name_resolve)
 * Resolve a device-tree node name: find the child matching `name` under the
 * given table, and produce the {base,limit} name range.  Panics if the child
 * exists but has no payload, or if the found payload is malformed.
 * Confidence: medium */
static void dt_name_resolve(word_t table, word_t name, word_t base)
{
    FUN_0006b2dc(table);
    {
        word_t node = 0, nprop = 0;
        word_t rc = dt_find_child((word_t *)table, name, &nprop, &node);
        word_t a, b, ok;
        if ((rc & 1) == 0) {
            a = 0; b = 0; ok = 1;
        } else {
            if ((long)node < 0)
                CL4_FATAL();
            a = nprop;
            if (node == 0) {
                if (nprop == 0) { b = 0; ok = 0; }
                else { b = 0; ok = 0; }
            } else {
                ok = 0;
                b = node + nprop;
            }
        }
        FUN_000651bc(0, a, b, ok);
        return;
    }
}

/* FUN_000668a0 @ 0x668a0  (est. dtk_scope_enter)
 * Emit the scoped-name open marker into the global DeviceTreeKit scratch
 * (word at 0x64e010).  Confidence: low (opaque constant store) */
static void dtk_scope_enter(void)
{
    *(volatile word_t *)0x64e010 = 0x910d6108b0000348;
}

/* FUN_00066950 @ 0x66950  (est. dtk_scope_close)
 * Emit the scoped-name close marker into the global DeviceTreeKit scratch
 * (word at 0x64e028).  Confidence: low (opaque constant store) */
static void dtk_scope_close(void)
{
    *(volatile word_t *)0x64e028 = 0xd42aa320d65f0fff;
}

/* FUN_000669a4 @ 0x669a4  (est. dtk_hash_of)
 * Return the hash of the object at x20.  Confidence: medium */
static void dtk_hash_of(word_t *out)
{
    *out = FUN_0001a1c8(*(word_t *)0);
}

/* FUN_000669e8 @ 0x669e8  (est. dtk_lock_select)
 * Take (or skip) a lock depending on whether param_2 is non-NULL; if taking,
 * bind the lock to the given object.  Confidence: medium */
static void dtk_lock_select(word_t lock, word_t obj)
{
    if (obj == 0)
        FUN_00229a3c(0);
    else {
        FUN_00229a3c(1);
        FUN_002298d4(obj);
    }
}

/* FUN_00066a2c @ 0x66a2c  (est. dtk_lock_select_scoped)
 * Scoped lock acquisition with enter/exit frame; same select as
 * dtk_lock_select but wrapped in a scope.  Confidence: medium */
static void dtk_lock_select_scoped(word_t obj)
{
    word_t frame[9];
    FUN_001a84f4(frame, 0);
    if (obj == 0)
        FUN_00229a3c(0);
    else {
        FUN_00229a3c(1);
        FUN_002298d4(obj);
    }
    FUN_001a8564();
}

/* FUN_00066aa0 @ 0x66aa0  (est. dtk_lock_select_scoped_apply)
 * Scoped lock select on the object stored at x20.  Confidence: medium */
static void dtk_lock_select_scoped_apply(void)
{
    word_t obj = *(word_t *)0;
    word_t frame[9];
    FUN_001a84f4(frame);
    dtk_lock_select((word_t)frame, obj);
    FUN_001a8564();
}

/* FUN_00066ae4 @ 0x66ae4  (est. dtk_report_node_error)
 * Emit a "report" error line for a node: build the (name) prefix, the error
 * marker, and a "report is" suffix, then finalize the node.  Fatal on
 * invalid node state.  Confidence: low (string-constant reconstruction) */
static word_t dtk_report_node_error(word_t a, word_t b)
{
    FUN_002a4ab4(0x12);
    word_t name = dtk_node_name_or_scope(a, b);
    word_t r1 = FUN_0006b584();
    word_t v = 0xe900000000000029;
    if (1)
        v = FUN_0006b584();
    FUN_002acbb8(FUN_0006b584(), v);
    FUN_003a25d4(v);
    FUN_002acbb8(0x202d20, 0xe300000000000000);
    FUN_00069bdc(a, b);
    FUN_0036b118();
    FUN_0001df60();
    FUN_0006b550();
    FUN_001ba7d4();
    FUN_002acbb8();
    FUN_003a25d4(0);
    FUN_002acbb8(0x747265706f727020, 0xeb00000000736569);
    return (word_t)0xe000000000000000;
}

/* FUN_00066be4 @ 0x66be4  (est. dtk_dump_node_tree)
 * Recursively dump a device-tree subtree: emit each node's name/property
 * ranges, gather property and child entries into growable vectors, and print
 * the tree with indentation and separators.  The single largest function in
 * the DeviceTreeKit region; walks the node iterator and builds output lines.
 * Confidence: low (Swift formatter call chain, many opaque helpers) */
static void dtk_dump_node_tree(word_t a, word_t b)
{
    word_t ctx[4];
    word_t out[4];
    word_t it[2];
    word_t acc;
    FUN_0006b2ec();
    it[0] = 0;
    out[0] = 0xe000000000000000;
    FUN_0006673c();
    word_t name = FUN_0006b584();
    word_t namev = 0xe900000000000029;
    if (1)
        namev = FUN_0006b584();
    FUN_002acbb8(name, namev);
    FUN_003a25d4(namev);
    {
        word_t props[4];
        dtk_begin_props(&props, a, b);
        while (dtk_next_prop(&ctx), ctx[3] != 1) {
            /* emit a property range into the vector */
            word_t p = FUN_0006b388();
            FUN_002060d4(p, &it, 0x65cd58, 0x6753a0);
            word_t end = it[1];
            FUN_002acbb8(it[0], it[1]);
            FUN_003a25d4(end);
            /* growable property vector push */
            if (!(FUN_003a261c(props) & 1)) {
                FUN_0006b45c(*(word_t *)(props + 0x10));
                FUN_0006b3f4();
                props = FUN_0006b3e0();
            }
            word_t n = *(word_t *)(props + 0x10);
            if (*(word_t *)(props + 0x18) >> 1 <= n) {
                FUN_0006b42c();
                FUN_0006b6d4();
                props = FUN_0006b3e0();
            }
            *(word_t *)(props + 0x10) = n + 1;
            *(word_t *)(props + n * 0x10 + 0x20) = 0x2020207c20;
            *(word_t *)(props + n * 0x10 + 0x28) = 0xe500000000000000;
        }
        dtk_end_props(&props, a, b);
    }
}

/*__MORE__*/
