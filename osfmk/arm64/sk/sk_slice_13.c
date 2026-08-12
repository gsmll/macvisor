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

/* Fixed-address globals (Ghidra DAT_ symbols) used by the DeviceTreeKit
 * region; kept as literal addresses since the binary image base is 0. */
#define DTK_EMPTY_VEC   0x657778   /* DAT_00657778: empty-vector sentinel */
#define DTK_VEC_STORE   0x657798   /* DAT_00657798: element storage */
#define DTK_VEC_COUNT   (*(volatile word_t *)0x657788) /* child-collect count */
#define DTK_VEC_CAP     (*(volatile word_t *)0x657790) /* child-collect cap   */
#define DTK_NAME_TBL    0x5c99ee   /* DAT_005c99ee: name table         */
#define DTK_SCOPE_META  0x5be7c0   /* DAT_005be7c0                     */
#define DTK_OBS_META    0x65d290   /* UINT_0065d290                    */
#define DTK_OBS_TBL     0x4bee78   /* DAT_004bee78                     */
#define DTK_STR_A       0x4be908   /* DAT_004be908                     */
#define DTK_STR_B       0x4ead58   /* DAT_004ead58                     */
#define DTK_EMIT_VT     0x4bed40   /* DAT_004bed40                     */
#define DTK_META_A   0x4be918   /* DAT_004be918                     */
#define DTK_META_B   0x4bedf0   /* DAT_004bedf0                     */
#define DTK_META_C   0x4bedd0   /* DAT_004bedd0                     */
#define DTK_META_D   0x4bedc8   /* DAT_004bedc8                     */
#define DTK_META_E   0x4bedb8   /* DAT_004bedb8                     */
#define DTK_META_F   0x4bedf8   /* DAT_004bedf8                     */

/* ---- shared kernel / Swift-runtime externs (not in this slice) ---- */
extern void FUN_001150e0(word_t); /* fatal: integer overflow msg */
extern void FUN_00115424(word_t, word_t, word_t, int); /* assert-style fatal */
extern word_t FUN_00115080(word_t); /* size getter (thunk) */
extern word_t FUN_00114d10(word_t, word_t); /* key compare (thunk) */
extern word_t FUN_00114fe0(word_t, word_t); /* size probe (thunk) */
extern word_t FUN_0036a940(word_t, word_t, word_t); /* Swift array buffer alloc */
extern word_t FUN_0036b270(word_t); /* Swift object retain */
extern void FUN_0036b118(word_t); /* Swift object release */
extern void FUN_003a25d4(word_t); /* Swift release (masked) */
extern word_t FUN_003a261c(word_t); /* buffer-unique check */
extern word_t FUN_003a26e8(word_t, word_t, word_t, word_t, word_t, word_t);
extern word_t FUN_00002534(word_t, word_t); /* string cache lookup */
extern word_t FUN_00027614(word_t, word_t); /* class/string builder */
extern word_t FUN_00376820(word_t, word_t); /* closure adapter */
extern word_t FUN_0001a1c8(word_t); /* identity/hash helper */
extern word_t FUN_0001cba4(word_t); /* identity helper */
extern word_t FUN_00027724(word_t); /* vt lookup */
extern void FUN_0011d7e8(void); /* fatal (Swift trap) */
extern void FUN_00117cc4(word_t, word_t, word_t); /* memcpy */
extern void FUN_00117d14(word_t, word_t, word_t); /* memmove */
extern void FUN_0035b67c(word_t, word_t, word_t, word_t); /* memmove+log */
extern word_t FUN_00229a3c(int); /* lock/bind select */
extern word_t FUN_002298d4(word_t); /* bind helper */
extern word_t FUN_001a84f4(word_t, word_t); /* scoped enter */
extern word_t FUN_001a8564(void); /* scoped exit */
extern word_t FUN_0006b2ec(word_t, word_t, word_t, word_t, word_t); /* nop (identity marker) */
extern word_t FUN_000651bc(word_t, word_t, word_t, word_t, word_t); /* nop */
extern word_t FUN_0006b2dc(word_t, word_t, word_t, word_t, word_t); /* nop */
extern word_t FUN_0006b6f4(word_t, word_t, word_t, word_t, word_t); /* nop */
extern word_t FUN_0006b6ac(word_t, word_t, word_t, word_t, word_t); /* nop */
extern word_t FUN_0006b560(word_t, word_t, word_t, word_t, word_t); /* nop */
extern word_t FUN_0006b4d0(word_t, word_t, word_t, word_t, word_t); /* nop */
extern word_t FUN_0006b550(word_t, word_t, word_t, word_t, word_t); /* nop */
extern word_t FUN_0001df60(word_t, word_t, word_t, word_t, word_t); /* nop */
extern word_t FUN_001ba7d4(word_t, word_t, word_t, word_t, word_t); /* nop */
extern void FUN_002acbb8(word_t, word_t); /* string append */
extern void FUN_002a4ab4(int); /* fault builder */
extern void FUN_00369efc(word_t, word_t, word_t); /* vector op */
extern word_t FUN_0006a374(word_t, word_t, word_t); /* vector realloc (16B elems) */
extern word_t FUN_0006a3cc(word_t, word_t, word_t, word_t); /* lazy init */
extern word_t FUN_000695e4(word_t, word_t, word_t, word_t, word_t, word_t, word_t);
extern word_t FUN_0006a414(void);
extern void FUN_001afa84(word_t, int, int, word_t, word_t, word_t, int, int, int, int); /* fatal msg */
extern word_t FUN_000126e8(void); /* thunk: size/round */
extern word_t FUN_0006b630(word_t, word_t, word_t, word_t, word_t); /* nop */
extern word_t FUN_0006a468(word_t, word_t, word_t); /* vector realloc (16B) */
extern word_t FUN_003a25e0(word_t, int); /* masked release */
extern word_t FUN_001fac04(word_t, word_t); /* buffer alloc */
extern void FUN_0006b720(void); /* nop */                /* nop-ish store */
extern word_t FUN_0006b3e0(void); /* empty-vec builder */
extern word_t FUN_0006b3f4(word_t); /* vec teardown */
extern word_t FUN_0006b45c(word_t); /* vec teardown */
extern word_t FUN_0006b42c(word_t, word_t, word_t, word_t, word_t); /* vec grow */
extern word_t FUN_0006b6a0(word_t, word_t, word_t, word_t, word_t); /* vec grow */
extern word_t FUN_0006b6d4(void); /* vec grow */
extern word_t FUN_0006b6c0(word_t, word_t, word_t, word_t, word_t); /* vec count bump */
extern word_t FUN_0006b620(word_t, word_t, word_t, word_t, word_t); /* nop */
extern word_t FUN_0006b4c0(word_t, word_t, word_t, word_t, word_t); /* nop */
extern word_t FUN_0006b4ac(word_t, word_t, word_t, word_t, word_t); /* nop */
extern word_t FUN_0006b500(word_t, word_t, word_t, word_t, word_t); /* nop */
extern word_t FUN_0006b528(word_t, word_t, word_t, word_t, word_t); /* nop */
extern word_t FUN_0006b514(word_t, word_t, word_t, word_t, word_t); /* nop */
extern word_t FUN_0006b540(word_t, word_t, word_t, word_t, word_t); /* nop */
extern word_t FUN_0006b68c(word_t, word_t, word_t, word_t, word_t); /* nop */
extern word_t FUN_0006b640(word_t, word_t, word_t, word_t, word_t); /* nop */
extern word_t FUN_0006b700(word_t, word_t, word_t, word_t, word_t); /* nop */
extern word_t FUN_0006b674(word_t, word_t, word_t, word_t, word_t); /* nop */
extern word_t FUN_0006b610(void); /* vec mark */
extern word_t FUN_0006b600(void); /* vec mark */
extern word_t FUN_0006b5a0(void); /* vec head */
extern word_t FUN_0006b2bc(void); /* vec head */
extern word_t FUN_0006b2fc(void); /* alloc */
extern word_t FUN_0006b440(word_t, word_t); /* store char */
extern word_t FUN_0006b48c(void); /* nop */
extern word_t FUN_0006b4a0(void); /* nop */
extern word_t FUN_0006b3d0(word_t, word_t, word_t, word_t, word_t); /* grow */
extern word_t FUN_0006b3a4(word_t, word_t, word_t, word_t, word_t); /* nop */
extern word_t FUN_001ebfb0(void); /* char encode */
extern word_t FUN_001eb088(void); /* alloc */
extern word_t FUN_001b798c(void); /* iter next */
extern word_t FUN_001b58b0(word_t, word_t, word_t, word_t); /* copy */
extern word_t FUN_00267510(void); /* read word pair */
extern word_t FUN_0029fa0c(word_t, word_t); /* pack */
extern word_t FUN_002a0cf8(word_t, word_t, word_t, word_t, word_t); /* eq check */
extern word_t FUN_0006ae9c(word_t, word_t); /* tagged union build */
extern void FUN_0006afb4(word_t, word_t); /* set start */
extern void FUN_0006afec(word_t); /* set release */
extern void FUN_0006abac(word_t, word_t, word_t); /* vec prep */
extern word_t FUN_00115448(word_t); /* char class */
extern word_t FUN_0006b680(void); /* (10,0xe1...) const pair */
extern word_t FUN_0006b388(void); /* stack buffer ptr */
extern word_t FUN_0006b584(word_t, word_t); /* "name on(" const */
extern word_t FUN_0006b5c0(void); /* alloc(8) */
extern word_t FUN_0006b5e0(void); /* alloc(8) */
extern word_t FUN_0006b330(void); /* alloc(8) */
extern void FUN_0006b374(void); /* string init */
extern word_t FUN_0006b728(word_t, word_t, word_t, word_t, word_t); /* nop */
extern word_t FUN_0006b714(word_t, word_t, word_t, word_t, word_t); /* nop */
extern word_t FUN_0006b65c(word_t, word_t, word_t, word_t, word_t); /* nop */
extern word_t FUN_001bdb28(word_t, word_t, word_t, word_t, word_t); /* nop */
extern void FUN_001bea18(word_t, word_t, word_t); /* bind */
extern void FUN_000026e8(word_t); /* dealloc */
extern word_t FUN_0006a4c0(word_t, word_t, word_t, word_t, word_t); /* vec prep */
extern word_t FUN_0006a4f0(word_t, word_t, word_t, word_t, word_t); /* vec release */
extern word_t FUN_0006a668(word_t, word_t, word_t, word_t, word_t); /* vec release */
extern word_t FUN_0006a520(word_t, word_t, word_t, word_t, word_t); /* nop */
extern word_t FUN_0006a5e4(word_t, word_t, word_t, word_t, word_t); /* nop */
extern word_t FUN_0006b404(word_t, word_t, word_t, word_t, word_t); /* nop */
extern word_t FUN_0006b6e0(word_t, word_t, word_t, word_t, word_t); /* nop */
extern void FUN_0036b21c(void); /* closure free */
extern word_t FUN_0006b360(word_t, word_t, word_t); /* vec wrap */
extern void FUN_002060d4(word_t, word_t, word_t, word_t); /* str fmt */
extern void FUN_002a3e64(word_t, word_t, word_t, word_t); /* str append */
extern word_t FUN_001bc440(word_t, word_t, word_t, word_t); /* pair pack */
extern word_t FUN_0006a698(word_t, word_t, word_t, word_t, word_t);
extern word_t FUN_0006a7c8(word_t, word_t, word_t, word_t, word_t);
/* ---- forward decls within this slice ---- */
static word_t dtk_prop_apply(void);
static word_t dtk_prop_apply_wrap(void);
static word_t dt_name_resolve_id(word_t table, word_t name);
static void   dtk_scope_enter(void);
static void   dtk_scope_close(void);
static word_t dt_compare_key(word_t a, word_t b);
static word_t dt_compare_val(word_t a, word_t b);
static word_t dtk_lookup_node_fatal(word_t idx);
static word_t dtk_dump_child(void);
static void   dtk_dump_next(word_t *out);
static void   dtk_begin_dump(word_t *out, word_t a, word_t b);
static void   dtk_end_dump(word_t *out, word_t a, word_t b);
static word_t dtk_vec_alloc16(word_t count, word_t cap, word_t tag, word_t meta);
static word_t dtk_vec_reserve16(word_t flags, word_t count, word_t grow, word_t vec,
                                word_t tag, word_t meta, word_t copy, word_t freefn);
static word_t dtk_dump_node_tree(word_t a, word_t b);
static void   dtk_children_finalize(word_t vec);
static word_t dtk_collect_children(void);
static word_t dtk_collect_props(void);
static word_t dtk_collect_names(void);
static word_t dtk_collect_from_list(word_t head);
static void   dtk_vec_store_realloc(void);
static word_t dtk_classify_report_child(word_t a, word_t b);
static void   dtk_classify_store(word_t *out);
static word_t dtk_hash_fn(void);
static void   dtk_vec_release_twice(word_t v);
static word_t dtk_vec_split(word_t v);
static word_t dtk_vec_alloc32(word_t count, word_t cap);
static word_t dtk_vec_alloc24(word_t count, word_t cap);
static word_t dtk_vec_reserve(word_t flags, word_t count, word_t grow, word_t vec,
                              word_t alloc, word_t copy, word_t freefn);
static void   dtk_lazy_init_once(word_t *slot, word_t a, word_t b, word_t c);
static void   dtk_scratch_store(void);

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
    if (dt_children(range, node) == 0) {
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
    word_t rc = ((word_t (*)(word_t, word_t *))cb)(ctx, &region);
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
static word_t dt_thunk_build_root_iter(word_t *out) { return dt_build_root_iter(out); }

/* FUN_0006623c @ 0x6623c  (est. dt_thunk_validate_root) */
static word_t dt_thunk_validate_root(word_t base, word_t size, word_t *out)
{ return dt_validate_root(base, size, out); }

/* FUN_00066254 @ 0x66254  (est. dt_thunk_validate_range) */
static word_t dt_thunk_validate_range(word_t base, word_t size, word_t *out)
{ return dt_validate_range(base, size, out); }

/* FUN_0006626c @ 0x6626c  (est. dt_thunk_walk_root_cb) */
static word_t dt_thunk_walk_root_cb(word_t base, word_t size, word_t cb, word_t ctx)
{ return dt_walk_root_cb(base, size, cb, ctx); }

/* FUN_00066284 @ 0x66284  (est. dt_thunk_list_at) */
static word_t dt_thunk_list_at(word_t *head, word_t idx, word_t *out)
{ return dt_list_at(head, idx, out); }

/* FUN_000662a0 @ 0x662a0  (est. dt_thunk_find_child) */
static word_t dt_thunk_find_child(word_t *iter, word_t name, word_t *out_node, word_t *out_nprop)
{ return dt_find_child(iter, name, out_node, out_nprop); }

/* FUN_000662b8 @ 0x662b8  (est. dt_thunk_range_set) */
static word_t dt_thunk_range_set(word_t base, word_t size, word_t *out)
{ return dt_range_set(base, size, out); }

/* FUN_000662d0 @ 0x662d0  (est. dt_thunk_iter_advance) */
static word_t dt_thunk_iter_advance(word_t *iter) { return dt_iter_advance(iter); }

/* FUN_000662e8 @ 0x662e8  (est. dt_thunk_iter_end) */
static word_t dt_thunk_iter_end(word_t *iter) { return dt_iter_end(iter); }

/* FUN_00066300 @ 0x66300  (est. dt_thunk_node_get) */
static word_t dt_thunk_node_get(word_t *iter, word_t *out_node, word_t *out_size)
{ return dt_node_get(iter, out_node, out_size); }

/* FUN_00066318 @ 0x66318  (est. dt_thunk_node_name_propcount) */
static word_t dt_thunk_node_name_propcount(word_t *iter, word_t *out_name, word_t *out_nprop)
{ return dt_node_name_propcount(iter, out_name, out_nprop); }

/* FUN_00066330 @ 0x66330  (est. dt_thunk_range_make) */
static word_t dt_thunk_range_make(word_t base, word_t size, word_t *out)
{ return dt_range_make(base, size, out); }

/* FUN_00066348 @ 0x66348  (est. dt_thunk_range_end) */
static word_t dt_thunk_range_end(word_t *range) { return dt_range_end(range); }

/* FUN_00066360 @ 0x66360  (est. dt_thunk_range_advance) */
static word_t dt_thunk_range_advance(word_t *range) { return dt_range_advance(range); }

/* FUN_00066378 @ 0x66378  (est. dt_thunk_children) */
static word_t dt_thunk_children(word_t *node, word_t *out_iter) { return dt_children(node, out_iter); }

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
 * Look up a device-tree property: build a {key,key} record object (0x65c908)
 * and a closure object (0x65c930) whose vtable dispatches through
 * dtk_prop_apply and whose context is the record, retain both, walk the
 * device tree with the dt_walk callback, then verify the result is a valid
 * object via FUN_003a26e8.  Panics if verification fails.
 * Confidence: medium (Swift closure / retain-release chain) */
static word_t dtk_prop_lookup(word_t a, word_t b, word_t c, word_t d)
{
    FUN_0006b2ec();
    {
        word_t rec = FUN_0036a940(0x65c908, 0x20, 7);
        *(word_t *)(rec + 0x10) = a;
        *(word_t *)(rec + 0x18) = b;
        word_t clo = FUN_0036a940(0x65c930, 0x20, 7);
        *(word_t *)(clo + 0x10) = (word_t)dtk_prop_apply;
        *(word_t *)(clo + 0x18) = rec;
        word_t cc[2] = { (word_t)dtk_prop_apply_wrap, clo };
        FUN_0036b270(rec);
        word_t rc = dt_walk_root_cb(c, d, (word_t)dtk_prop_apply_wrap, (word_t)&cc);
        FUN_0036b118(clo);
        if (!(FUN_003a26e8(rec, DTK_SCOPE_META, 0xd3, 0x5d, 9, 0) & 1))
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
 * by (kind, id).  Uses the DeviceTreeKit name table and resolver; panics if
 * no name is produced.
 * Confidence: low (Swift call chain, exact string tables unknown) */
static word_t dtk_node_name_or_scope(word_t kind, word_t id)
{
    word_t res = dt_name_resolve_id(DTK_NAME_TBL, kind);
    if ((id & 0xff) == 1) {
        return 0;
    } else {
        FUN_0006b374();
        dtk_scope_enter();
        dtk_scope_close();
        word_t nm = FUN_0006b330();
        if (FUN_0006b330() == 0)
            CL4_FATAL();
        return nm;
    }
}

/* FUN_00066804 @ 0x66804  (est. dt_name_resolve_id)
 * Resolve a device-tree node name under the given table: find the child
 * matching the name, and produce the resulting {base,limit} name range.
 * Panics if the found payload is malformed.
 * Confidence: medium */
static word_t dt_name_resolve_id(word_t table, word_t name)
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
        return ok;
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
    dtk_collect_props(a, b);
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
 * the tree with indentation, separators and path separators.  Walks the
 * children iterator and pushes (range, ext) pairs into the vectors.
 * Confidence: low (Swift formatter call chain, many opaque helpers) */
static void dtk_dump_node_tree(word_t a, word_t b)
{
    word_t ctx[4] = { 0 };
    word_t it[2];
    word_t vec = 0;
    FUN_0006b2ec();
    it[0] = 0;
    it[1] = 0xe000000000000000;
    dtk_node_name_or_scope(0,0);
    {
        word_t name = FUN_0006b584();
        word_t namev = 0xe900000000000029;
        if (1)
            namev = FUN_0006b584();
        FUN_002acbb8(name, namev);
        FUN_003a25d4(namev);
    }
    dtk_begin_dump(&ctx, a, b);
    while (dtk_dump_next(&ctx), ctx[3] != 1) {
        word_t p = FUN_0006b388();
        FUN_002060d4(p, &it, 0x65cd58, 0x6753a0);
        word_t end = it[1];
        FUN_002acbb8(it[0], it[1]);
        FUN_003a25d4(end);
        if (!(FUN_003a261c(vec) & 1)) {
            FUN_0006b45c(*(word_t *)(vec + 0x10));
            FUN_0006b3f4();
            vec = FUN_0006b3e0();
        }
        {
            word_t n = *(word_t *)(vec + 0x10);
            if (*(word_t *)(vec + 0x18) >> 1 <= n) {
                FUN_0006b42c();
                FUN_0006b6d4();
                vec = FUN_0006b3e0();
            }
            *(word_t *)(vec + 0x10) = n + 1;
            *(word_t *)(vec + n * 0x10 + 0x20) = 0x2020207c20;
            *(word_t *)(vec + n * 0x10 + 0x28) = 0xe500000000000000;
        }
    }
    dtk_end_dump(&ctx, a, b);
}

/* FUN_00067444 @ 0x67444  (est. dtk_begin_dump)
 * Start a device-tree dump: validate the root region (via dt_range_set) and
 * prepare the top-level children iterator.  Confidence: medium */
static void dtk_begin_dump(word_t *out, word_t a, word_t b)
{
    word_t rng[4];
    FUN_0006b2dc();
    if (1) {
        dt_children(out, rng);
        return;
    }
    FUN_0011d7e8();
}

/* FUN_0006749c @ 0x6749c  (est. dtk_dump_next)
 * Fetch the next node in a dump: if not done, advance the children iterator
 * and copy the node's {name,namelen,propdata,proplen} quadruple into *out,
 * clearing the done flag.  Returns done flag in out[4].
 * Confidence: medium */
static void dtk_dump_next(word_t *out)
{
    word_t saved[4];
    word_t done;
    FUN_0006b2ec();
    done = *(char *)((word_t)out + 4) == 1;
    if (done) {
        out[0] = 0; out[1] = 0; out[2] = 0; out[3] = 0; out[4] = 1;
        return;
    }
    saved[0] = out[0]; saved[1] = out[1]; saved[2] = out[2]; saved[3] = out[3];
    if ((dt_iter_end(out) & 1) == 0) {
        word_t a = 0, b = 0;
        if ((dt_node_get(out, &a, &b) & 1) != 0) {
            if (b > 0x1f)
                CL4_FATAL();
            {
                word_t c = 0, d = 0;
                if ((dt_node_name_propcount(out, &c, &d) & 1) != 0) {
                    if (a == 0) goto done_path;
                    if (c == 0) { a = 0; goto done2; }
                    word_t namelen = b + 1;
                    if (b + 1 < b || (long)namelen < 0 || (long)d < 0)
                        CL4_FATAL();
                    out[0] = a;
                    out[1] = namelen;
                    out[2] = c;
                    out[3] = d + c;
                    dt_iter_advance(out);
                    done = 0;
                    goto restore;
                }
            }
        }
        goto done_path;
    }
done_path:
    out[0] = 0;
done2:
    out[1] = 0;
    out[2] = 0;
    out[3] = 0;
    done = 1;
restore:
    out[0] = saved[0]; out[1] = saved[1]; out[2] = saved[2]; out[3] = saved[3];
    *(char *)((word_t)out + 4) = 0;
    if (done)
        out[4] = 1;
    else
        out[4] = 0;
    FUN_000651bc();
}

/* FUN_000675e8 @ 0x675e8  (est. dtk_end_dump)
 * Finish a dump: validate the region and finalize the iterator (dt_range_make).
 * Confidence: medium */
static void dtk_end_dump(word_t *out, word_t a, word_t b)
{
    word_t rng[4];
    FUN_0006b2dc();
    if (1) {
        dt_range_make(out, rng);
        return;
    }
    FUN_0011d7e8();
}

/* FUN_00067640 @ 0x67640  (est. dtk_dump_child)
 * Fetch one child node from the dump iterator into a {name,namelen} pair,
 * advancing the iterator and returning the done flag.
 * Confidence: medium */
static word_t dtk_dump_child(void)
{
    word_t saved[4];
    word_t rc, a, b;
    word_t done;
    FUN_0006b2ec();
    done = *(char *)(0 + 4) == 1;
    if (done) {
        a = 0; b = 0; rc = 1;
    } else {
        saved[0] = 0; saved[1] = 0; saved[2] = 0; saved[3] = 0;
        if ((dt_range_end(0) & 1) == 0) {
            word_t ca = 0, cb = 0;
            if ((dt_children(0, &ca) & 1) != 0) {
                b = 0; a = ca;
                dt_range_advance(0);
                rc = 0;
                goto done2;
            }
        }
        a = 0; b = 0; rc = 1;
    }
done2:
    *(char *)(0 + 4) = 0;
    if (done)
        return a;
    FUN_0011d7e8();
    return a;
}

/* FUN_00067704 @ 0x67704  (est. dtk_lookup_node_fatal)
 * Look up a device-tree entry by index in the global list; fatal on failure.
 * Confidence: medium */
static void dtk_lookup_node_fatal(word_t idx)
{
    word_t out[2] = { 0, 0 };
    FUN_0006b2ec();
    word_t rc = dt_list_at(0, idx, out);
    if ((rc & 1) == 0) {
        FUN_002a4ab4(0x16);
        FUN_003a25d4(0xe000000000000000);
        FUN_0006b6ac();
        FUN_0001df60();
        FUN_0006b550();
        FUN_001ba7d4();
        FUN_002acbb8();
        FUN_003a25d4(0);
        FUN_0006b560();
        FUN_002acbb8();
        FUN_0006b4d0();
        CL4_FATAL();
    }
    FUN_000651bc();
}

/* FUN_000677c8 @ 0x677c8  (est. dtk_range_of)
 * Build a {base,limit} range pair from a single base word; length is 0.
 * Confidence: medium */
static word_t dtk_range_of(word_t base)
{
    word_t out[2];
    dt_list_len();
    out[1] = 0;
    out[0] = base;
    return (word_t)out;
}

/* FUN_000677f8 @ 0x677f8  (est. dtk_record_store)
 * Build a 3-word record {range, tag, payload} from the iterator at x20.
 * Confidence: medium */
static void dtk_record_store(word_t *out, word_t a, word_t b, word_t payload)
{
    word_t r = dtk_range_of(*(word_t *)0);
    out[0] = r;
    out[1] = 0;
    out[2] = payload;
}

/* FUN_0006782c @ 0x6782c  (est. dtk_tag_of)
 * Return the fixed tag 2 for a record.  Confidence: high */
static word_t dtk_tag_of(void) { return 2; }

/* FUN_00067850 @ 0x67850  (est. dtk_collect_entries)
 * Collect `count` two-word entries from the list at param_4 into the output
 * array param_2 (each entry 0x10 bytes).  Fatal on any out-of-range lookup.
 * Confidence: medium */
static word_t dtk_collect_entries(word_t *out, word_t *dst, word_t count, word_t head)
{
    word_t len = dt_list_len((word_t *)head);
    word_t i = 0;
    word_t produced;
    if (count == 0) {
        produced = 0;
    } else {
        if ((long)count < 0)
            CL4_FATAL();
        produced = count;
        if (count != 0) {
            word_t n = 0;
            word_t want = len & ((long)len >> 0x3f ^ (word_t)-1);
            do {
                produced = want;
                if (want == n)
                    break;
                {
                    word_t e[2] = { 0, 0 };
                    produced = dt_list_at((word_t *)head, n, e);
                    if ((produced & 1) == 0)
                        FUN_001afa84((word_t)"Fatal error", 0xb, 2,
                                     0x207865646e49, 0xe600000000000000,
                                     (word_t)"DeviceTreeKit/DeviceTreeKit.swif", 0x21, 2, 0xa6, 0);
                    word_t *dstp = (word_t *)((word_t)dst + n * 0x10);
                    dstp[1] = e[1];
                    dstp[0] = e[0];
                    n = n + 1;
                    produced = count;
                }
            } while (count != n);
        }
    }
    out[0] = head;
    out[1] = produced;
    out[2] = len;
    return produced;
}

/* FUN_00067a04 @ 0x67a04  (est. dtk_forward)
 * Forward-apply the DeviceTreeKit copy helper.  Confidence: medium */
static void dtk_forward(word_t a, word_t b, word_t c, word_t d)
{
    FUN_001b58b0(a, b, d, c);
}

/* FUN_00067a28 @ 0x67a28  (est. dtk_dump_list)
 * Dump every entry in the device-tree list: for each, resolve its node name,
 * emit a "(name" open and a "report" line, then finalize.  Fatal on lookup
 * failure.  Confidence: medium */
static void dtk_dump_list(word_t head)
{
    word_t line[2] = { 0x2f, 0xe100000000000000 };
    word_t vec = 0;
    word_t save;
    FUN_0006b2ec();
    FUN_0006a374(0, 0, 0);
    {
        word_t n = dt_list_len((word_t *)head);
        word_t i = 0;
        do {
            if ((n & ((long)n >> 0x3f ^ (word_t)-1)) == i) {
                FUN_0006b6f4();
                FUN_00002534();
                word_t a = FUN_0006a3cc(0x64e048, 0x64e040, DTK_STR_A, DTK_STR_B);
                word_t pair = FUN_001bc440(0x2f, 0xe100000000000000, 0, a);
                FUN_0036b118(vec);
                FUN_002acbb8(pair, FUN_0006b584());
                FUN_003a25d4(FUN_0006b584());
                FUN_000651bc();
                return;
            }
            {
                word_t e[2] = { 0, 0 };
                word_t rc = dt_list_at((word_t *)head, i, e);
                if ((rc & 1) == 0)
                    CL4_FATAL();
                word_t node = e[0];
                word_t nr = 0, np = 0;
                rc = dt_find_child((word_t *)node, 0, &nr, &np);
                if ((rc & 1) == 0) {
                    FUN_002a4ab4(0x16);
                    FUN_003a25d4(0xe000000000000000);
                    FUN_0006b6ac();
                    FUN_0001df60();
                    FUN_0006b550();
                    FUN_001ba7d4();
                    FUN_002acbb8();
                    FUN_003a25d4(0);
                    FUN_0006b560();
                    FUN_002acbb8();
                    FUN_0006b4d0();
                    CL4_FATAL();
                }
                if (!(FUN_003a261c(vec) & 1)) {
                    FUN_0006b45c(*(word_t *)(vec + 0x10));
                    FUN_0006b3f4();
                    vec = FUN_0006b3e0();
                }
                word_t nn = *(word_t *)(vec + 0x10);
                if (*(word_t *)(vec + 0x18) >> 1 <= nn) {
                    FUN_0006b42c();
                    FUN_0006b6d4();
                    vec = FUN_0006b3e0();
                }
                *(word_t *)(vec + 0x10) = nn + 1;
                *(word_t *)(vec + nn * 0x10 + 0x20) = 0x656d616e206f6e28;
                i = i + 1;
            }
        } while (1);
    }
}

/* FUN_00067d4c @ 0x67d4c  (est. dtk_list_next)
 * Return the next list entry (lookup at cursor x20[1]) or 0 when exhausted.
 * Confidence: medium */
static word_t dtk_list_next(void)
{
    word_t cursor = 0[1];
    if (cursor < (long)0[2]) {
        word_t v = dtk_lookup_node_fatal(cursor);
        0[1] = cursor + 1;
        return v;
    } else {
        return 0;
    }
}

/* FUN_00067d9c @ 0x67d9c  (est. dtk_list_next_record)
 * Fetch the next record from a list iterator and tag it.
 * Confidence: medium */
static void dtk_list_next_record(word_t *out, word_t a, word_t b, word_t tag)
{
    word_t r = dtk_list_next();
    out[0] = r;
    out[1] = tag;
}

/* FUN_00067dc8 @ 0x67dc8  (est. dtk_child_range_begin)
 * Begin iterating a node's children: build the {base,limit,extent,count}
 * iterator from the node at x20.  Confidence: medium */
static void dtk_child_range_begin(word_t *out)
{
    word_t it[4];
    dtk_begin_dump(&it, *0, 0[1]);
    out[1] = it[1];
    out[0] = it[0];
    out[3] = it[3];
    out[2] = it[2];
    *(char *)((word_t)out + 4) = *(char *)((word_t)it + 4);
}

/* FUN_00067e2c @ 0x67e2c  (est. dtk_ensure_node)
 * Ensure the DeviceTreeKit node table is populated for the given range;
 * panics if the underlying allocation returns NULL.  Confidence: low */
static void dtk_ensure_node(word_t a, word_t b)
{
    if (a == 0) {
        FUN_0006b374();
        dtk_scope_enter();
        dtk_scope_close();
        FUN_0006b330();
        if (FUN_0006b330() == 0)
            CL4_FATAL();
    } else {
        if (b < 0)
            CL4_FATAL();
        FUN_0006b374();
        dtk_scope_enter();
        dtk_scope_close();
        FUN_0006b330();
        if (FUN_0006b330() == 0)
            CL4_FATAL();
    }
}

/* FUN_00067edc @ 0x67edc  (est. dtk_render_hex)
 * Render a byte buffer as a hex string into a DeviceTreeKit string: iterate
 * the bytes in forward and reverse order, emitting per-nibble hex characters
 * with separators, then the final line.  Large formatter with two passes
 * (low and high nibble collection into char vectors).  Confidence: low
 * (Swift string formatter, many opaque vector helpers) */
static word_t dtk_render_hex(word_t a, word_t b, word_t *data, word_t **out)
{
    word_t len = (word_t)out - (word_t)data;
    word_t vec;
    if (data == 0) {
        FUN_0006b630();
        vec = 0;
    } else if ((word_t)&__thread_bss.flags < len) {
        /* first pass: collect low nibbles */
        FUN_0006b630();
        vec = FUN_0006b4ac();
        {
            word_t i = 0;
            do {
                word_t c = FUN_00115448(data[i]);
                word_t ch, hi;
                if (c == 0) {
                    hi = 0xe100000000000000;
                    ch = 0x2e;
                } else {
                    word_t tmp = FUN_0006b2fc();
                    FUN_0006b440(tmp, 4 - 0);
                    FUN_002acbb8();
                    FUN_003a25d4(0);
                    ch = 0;
                    hi = 0;
                }
                /* push (ch,hi) into vec */
                word_t n = *(word_t *)(vec + 0x10);
                if ((word_t *)((ulong)vec[3] >> 1) <= (word_t *)n)
                    FUN_0006a374();
                vec[2] = (word_t)(n + 1);
                vec[n * 2 + 4] = ch;
                vec[n * 2 + 5] = hi;
                i = i + 1;
            } while (i != 8);
            FUN_0006b5a0();
            word_t h = FUN_0006b2bc();
            h = FUN_0006a3cc(h, (word_t)(n + 1), 0);
            word_t pair = FUN_0006b610();
            FUN_001bc440(pair, 0, h);
            FUN_0006b674();
            FUN_0036b118(vec);
            FUN_0006b540();
            FUN_003a25d4(h);
            FUN_0006b700();
            /* reverse pass: high nibbles */
            FUN_0006b4c0();
            {
                word_t j = 8;
                FUN_0006b4ac();
                do {
                    word_t c = FUN_00115448(data[j - 1]);
                    word_t ch, hi;
                    if (c == 0) { hi = 0xe100000000000000; ch = 0x2e; }
                    else {
                        word_t tmp = FUN_0006b2fc();
                        FUN_0006b440(tmp, 4 - 0);
                        FUN_002acbb8();
                        FUN_003a25d4(0);
                        ch = 0; hi = 0;
                    }
                    word_t n = *(word_t *)(vec + 0x10);
                    if ((word_t *)((ulong)vec[3] >> 1) <= (word_t *)n)
                        FUN_0006a374();
                    vec[2] = (word_t)(n + 1);
                    vec[n * 2 + 4] = ch;
                    vec[n * 2 + 5] = hi;
                    j = j - 1;
                } while (j != 0);
            }
            FUN_0006b610();
            FUN_001bc440(0, 0, 0);
            FUN_0006b674();
            FUN_0036b118(vec);
            FUN_0006b540();
            FUN_003a25d4(0);
            FUN_002acbb8(0x7c, 0xe100000000000000);
            FUN_002a4ab4(0x14);
            FUN_0006b4c0();
            FUN_0006b4ac();
            {
                word_t k = 0;
                do {
                    word_t by = data[k];
                    word_t out16;
                    if (by < 0x10) {
                        FUN_0006b528();
                        FUN_0006b514();
                        FUN_001ebfb0();
                        FUN_002acbb8();
                        FUN_003a25d4(0);
                        out16 = FUN_0006b3e0();
                    } else {
                        out16 = by;
                        FUN_0006a414();
                        FUN_0006b500();
                        out16 = FUN_001ebfb0();
                    }
                    FUN_0006b68c();
                    vec[2] = (word_t)((word_t)vec[2] + 1);
                    *(word_t *)(vec + (word_t)vec[2] * 2 + 4) = out16;
                    k = k + 1;
                } while (k != 8);
            }
            FUN_0006b600();
            FUN_001bc440(0, 0, 0);
            FUN_0006b674();
            FUN_0036b118(vec);
            FUN_0006b540();
            FUN_003a25d4(0);
            FUN_0006b700();
            FUN_0006b4c0();
            FUN_0006b4ac();
            {
                word_t m = 8;
                do {
                    word_t by = data[m - 1];
                    word_t out16;
                    if (by < 0x10) {
                        FUN_0006b528();
                        FUN_0006b514();
                        FUN_001ebfb0();
                        FUN_002acbb8();
                        FUN_003a25d4(0);
                        out16 = FUN_0006b3e0();
                    } else {
                        out16 = by;
                        FUN_0006a414();
                        FUN_0006b500();
                        out16 = FUN_001ebfb0();
                    }
                    FUN_0006b68c();
                    vec[2] = (word_t)((word_t)vec[2] + 1);
                    *(word_t *)(vec + (word_t)vec[2] * 2 + 4) = out16;
                    m = m - 1;
                } while (m != 0);
            }
            FUN_0006b600();
            FUN_001bc440(0, 0, 0);
            FUN_0006b674();
            FUN_0036b118(vec);
            FUN_0006b540();
            FUN_003a25d4(0);
            FUN_002acbb8(0x20, 0xe100000000000000);
            FUN_002acbb8(0, 0);
            FUN_003a25d4(0);
            FUN_0006b640();
        }
    }
    FUN_0001df60();
    FUN_0006b550();
    FUN_001ba7d4();
    FUN_002acbb8();
    FUN_003a25d4(0);
    FUN_002acbb8(0x5d, 0xe100000000000000);
    FUN_002acbb8(0x203a, 0xe200000000000000);
    FUN_002acbb8(0, 0);
    FUN_003a25d4(0);
    return 0;
}

/* FUN_0006869c @ 0x6869c  (est. dtk_hash_fn)
 * Return the device-tree hash function pointer.  Confidence: high */
static word_t dtk_hash_fn(void) { return (word_t)FUN_0001a1c8; }

/* FUN_000686bc @ 0x686bc  (est. dtk_next_record_copy)
 * Copy the current record {base,limit,extent,count} out of the iterator.
 * Confidence: high (structural) */
static void dtk_next_record_copy(word_t *out)
{
    word_t it[4];
    dtk_dump_next(&it);
    out[1] = it[1];
    out[0] = it[0];
    out[3] = it[3];
    out[2] = it[2];
    *(char *)((word_t)out + 4) = *(char *)((word_t)it + 4);
}

/* FUN_00068700 @ 0x68700  (est. dtk_call_and_wrap)
 * Invoke the callback in x9 with the range {base,limit} and mask the result
 * into a 5-word record; clears the result on failure.
 * Confidence: medium (register-passed callback) */
static void dtk_call_and_wrap(word_t *out, word_t base, word_t limit)
{
    word_t r[4] = { 0, 0, 0, 0 };
    word_t cb = 0;   /* callback in x9, unknown statically */
    FUN_0006b2ec();
    word_t ok = 0;
    if (cb)
        ok = ((word_t (*)(word_t, word_t, word_t *))cb)(base, limit, r) & 1;
    if (!ok)
        r[0] = r[1] = r[2] = r[3] = 0;
    out[0] = r[0];
    out[1] = r[1];
    out[2] = r[2];
    out[3] = r[3];
    *(char *)((word_t)out + 4) = (char)(ok ^ 0xff) & 1;
    FUN_000651bc();
}

/* FUN_00068780 @ 0x68780  (est. dtk_end_record_copy)
 * Copy the final record {base,limit,extent,count} out of the iterator.
 * Confidence: high (structural) */
static void dtk_end_record_copy(word_t *out)
{
    word_t it[4];
    dtk_end_dump(&it, *0, 0[1]);
    out[1] = it[1];
    out[0] = it[0];
    out[3] = it[3];
    out[2] = it[2];
    *(char *)((word_t)out + 4) = *(char *)((word_t)it + 4);
}

/* FUN_00068800 @ 0x68800  (est. dtk_child_record)
 * Fetch the next child record and tag it.  Confidence: medium */
static void dtk_child_record(word_t *out, word_t a, word_t b, word_t tag)
{
    word_t r = dtk_dump_child();
    out[0] = r;
    out[1] = tag;
}

/* FUN_00068838 @ 0x68838  (est. dtk_hash_value)
 * Compute the hash of the object at x20.  Confidence: medium */
static void dtk_hash_value(void)
{
    FUN_0001cba4(*0);
}

/* FUN_0006883c @ 0x6883c  (est. dtk_hash_value_2) */
static void dtk_hash_value_2(void)
{
    FUN_0001cba4(*0);
}

/* FUN_0006887c @ 0x6887c  (est. dtk_register_observer)
 * Register a DeviceTreeKit observer with a one-byte payload via the vector
 * primitive.  Confidence: low */
static void dtk_register_observer(word_t payload)
{
    word_t local = payload;
    FUN_00369efc(&local, DTK_OBS_META, DTK_OBS_TBL);
}

/* FUN_000688cc @ 0x688cc  (est. dtk_collect_children)
 * Collect every child of the current node into a growable vector of child
 * records, walking the full subtree.  Returns the vector {count, elements}.
 * Confidence: medium */
static word_t dtk_collect_children(void)
{
    word_t it[4];
    word_t vec = 0;
    word_t n = 0;
    word_t base;
    word_t rc;
    FUN_0006b2ec();
    dtk_begin_dump(&it);
    while (dtk_dump_next(&it), it[4] != 1) {
        word_t child = it[0];
        word_t childlen = it[1];
        word_t crec;
        if (child == 0) {
            word_t z[2] = { 0, 0 };
            FUN_0006b48c();
            dtk_scope_enter();
            dtk_scope_close();
            crec = FUN_0006b5e0();
            if (FUN_0006b5e0() == 0)
                CL4_FATAL();
        } else {
            if ((long)it[2] < 0)
                CL4_FATAL();
            FUN_0006b48c();
            dtk_scope_enter();
            dtk_scope_close();
            crec = FUN_0006b5e0();
            if (FUN_0006b5e0() == 0)
                CL4_FATAL();
        }
        /* push {crec, childbuf} into vec */
        word_t bufp;
        if (child == 0 || (childlen = childlen - child, childlen == 0)) {
            bufp = 0;
        } else {
            bufp = FUN_0036a940(0, childlen + 0x20, 7);
            FUN_00117cc4(bufp + 0x20, child, childlen);
        }
        if (!(FUN_003a261c(vec) & 1)) {
            FUN_0006b3f4(*(word_t *)(vec + 0x10));
            vec = FUN_000695e4();
        }
        word_t vn = *(word_t *)(vec + 0x10);
        if (*(word_t *)(vec + 0x18) >> 1 <= vn)
            vec = FUN_000695e4();
        *(word_t *)(vec + 0x10) = vn + 1;
        *(word_t *)(vec + vn * 0x18 + 0x20) = crec;
        *(word_t *)(vec + vn * 0x18 + 0x30) = bufp;
    }
    dtk_children_finalize(vec);
    FUN_0006a468(0, 0, 0);
    dtk_end_dump(&it);
    if (it[4] != 1) {
        while (1) {
            word_t ca = 0, cb = 0;
            if ((dt_iter_end(&it) & 1) != 0)
                break;
            if ((dt_children(&it, &ca) & 1) == 0)
                break;
            dt_iter_advance(&it);
            FUN_0006b6f4();
            word_t sub = dtk_collect_children();
            if (sub == 0) {
                FUN_0036b118((word_t)DTK_EMPTY_VEC);
                FUN_003a25d4(n);
                n = 0;
                break;
            }
            word_t idx = DTK_VEC_COUNT;
            if (DTK_VEC_CAP >> 1 <= DTK_VEC_COUNT)
                FUN_0006a468();
            DTK_VEC_COUNT = idx + 1;
            *(word_t *)(DTK_VEC_STORE + idx * 2) = sub;
        }
    }
    FUN_000651bc();
    return n;
}

/* FUN_00068c40 @ 0x68c40  (est. dtk_children_finalize)
 * Finalize a children vector: if it has elements, move them into a fresh
 * buffer and rebase the vector.  Confidence: medium */
static void dtk_children_finalize(word_t vec)
{
    word_t n = *(word_t *)(vec + 0x10);
    word_t *buf;
    if (n == 0) {
        buf = DTK_VEC_STORE;
    } else {
        buf = (word_t *)FUN_001fac04(n, 0x64e100);
    }
    FUN_0006abac(vec, 1, &buf);
    if (0 != 0)
        FUN_0036b118((word_t)buf);
}

/* FUN_00068cd0 @ 0x68cd0  (est. dtk_classify_report_child)
 * Classify a keyword pair: "report"/"reportis" -> 0, "child"/"child" -> 1,
 * else 2.  Confidence: high (string constants) */
static word_t dtk_classify_report_child(word_t a, word_t b)
{
    if ((a == 0x69747265706f7270 && b == (word_t)-0x15ffffffffff8c9b) ||
        (FUN_002a0cf8(0x69747265706f7270, 0xea00000000007365, a, b, 0) & 1) != 0) {
        FUN_003a25d4(b);
        return 0;
    } else if (a == 0x6e6572646c696863 && b == (word_t)-0x1800000000000000) {
        FUN_003a25d4(b);
        return 1;
    } else {
        word_t v = FUN_002a0cf8(0x6e6572646c696863, 0xe800000000000000, a, b, 0);
        FUN_003a25d4(b);
        return (v & 1) == 0 ? 2 : 1;
    }
}

/* FUN_00068de8 @ 0x68de8  (est. dtk_classify_store)
 * Classify the keyword pair and store the result as a byte.  Confidence: high */
static void dtk_classify_store(word_t *out)
{
    *out = (word_t)dtk_classify_report_child(0, 0);
}

/* FUN_00068e14 @ 0x68e14  (est. dtk_report_flag)
 * Return the constant "report" flag.  Confidence: high */
static word_t dtk_report_flag(void)
{
    return (word_t)1 << 0x40;
}

/* FUN_00068e4c @ 0x68e4c  (est. dtk_emit_report)
 * Emit a report line via the vtable at DAT_004bed40.  Confidence: low */
static void dtk_emit_report(void)
{
    word_t (*fn)(word_t, word_t) = (word_t (*)(word_t, word_t))FUN_00027724(DTK_EMIT_VT);
    fn(0x65d200, (word_t)DTK_EMIT_VT);
}

/* FUN_00068eac @ 0x68eac  (est. dtk_compare_pair)
 * Compare two {key,val} pairs for equality: key equality via dt_compare_key,
 * then value equality via dt_compare_val.  Confidence: medium */
static word_t dtk_compare_pair(word_t a, word_t b, word_t c, word_t d)
{
    if ((dt_compare_key(a, c) & 1) != 0)
        return dt_compare_val(b, d);
    return 0;
}

/* FUN_00068ef8 @ 0x68ef8  (est. dt_compare_key)
 * Deep-compare two device-tree keys: identical pointers, or equal length and
 * matching elements.  Uses a word-bitmap to walk a sorted index.  Confidence:
 * low (set/bitmap iteration, partial reconstruction) */
static word_t dt_compare_key(word_t a, word_t b)
{
    if (a == b) {
        return 1;
    } else {
        if (*(long *)(a + 0x10) == *(long *)(b + 0x10)) {
            word_t set[2], idx[2];
            FUN_0006afb4(&set, a);
            FUN_003a25e0(a, 2);
            FUN_0036b270(b);
            /* iterate the sorted index bitmap (decompiler collapsed); bail */
            FUN_003a25d4(b);
            FUN_003a25d4(a);
            return 0;
        }
        return 0;
    }
}

/* FUN_000690f0 @ 0x690f0  (est. dt_compare_val)
 * Deep-compare two device-tree values: equal length, then element-wise
 * (recursing on pairs).  Confidence: medium */
static word_t dt_compare_val(word_t a, word_t b)
{
    word_t n = *(long *)(a + 0x10);
    if (n == *(long *)(b + 0x10)) {
        if ((n == 0) || (a == b)) {
            return 1;
        } else {
            word_t *pa = (word_t *)(a + 0x28);
            word_t *pb = (word_t *)(b + 0x28);
            do {
                n = n - 1;
                word_t a0 = pa[-1], a1 = *pa;
                word_t b0 = pb[-1], b1 = *pb;
                FUN_0036b270(a0);
                FUN_0036b270(a1);
                FUN_0036b270(b0);
                FUN_0036b270(b1);
                if ((dt_compare_key(a0, b0) & 1) == 0) {
                    FUN_0036b118(a1);
                    FUN_003a25d4(a0);
                    FUN_0036b118(b1);
                    FUN_003a25d4(b0);
                    return 0;
                }
                word_t v = dt_compare_val(a1, b1);
                FUN_0036b118(a1);
                FUN_003a25d4(a0);
                FUN_0036b118(b1);
                FUN_003a25d4(b0);
                if ((v & 1) == 0)
                    return 0;
                pa += 2;
                pb += 2;
            } while (n != 0);
            return 1;
        }
    }
    return 0;
}

/* FUN_00069214 @ 0x69214  (est. dtk_vec_release_twice)
 * Release a two-part vector: release the element array (param_1+0x18) and the
 * buffer (param_1+0x20), then run the teardown path; if the flag at x21 is
 * clear, run the release path again.  Confidence: low */
static void dtk_vec_release_twice(word_t v)
{
    word_t buf = *(word_t *)(v + 0x20);
    FUN_0006a4c0(v, *(word_t *)(v + 0x18));
    FUN_0006a4f0(buf);
    FUN_0006b404();
    word_t r = 0;
    FUN_00002534(0x64e058, DTK_META_A);
    FUN_0006b728();
    FUN_0006a520();
    FUN_0006b65c();
    FUN_001bdb28();
    if (0 == 0) {
        FUN_0006b714();
        FUN_0006a5e4();
        FUN_0006b65c();
        FUN_001bdb28();
    }
    FUN_0036b118(r);
}

/* FUN_00069300 @ 0x69300  (est. dtk_vec_split)
 * Split a two-part vector into its element array (param_1+0x18) and buffer
 * (param_1+0x20): release them, then either rebind or deallocate.  Returns
 * the {result, extra} pair.  Confidence: low */
static word_t dtk_vec_split(word_t v)
{
    word_t elems = *(word_t *)(v + 0x18);
    word_t buf = *(word_t *)(v + 0x20);
    word_t out[2];
    word_t r;
    FUN_0006a4c0(v, elems);
    FUN_0006a668(buf);
    FUN_0006b404();
    r = 0;
    if (0 == 0) {
        word_t x = FUN_0006b728();
        FUN_0006a698();
        FUN_0006b3a4();
        FUN_001bea18(x, 0, r);
        x = FUN_0006b714();
        FUN_0006a7c8();
        FUN_0006b3a4();
        FUN_001bea18(x, 0, r);
        FUN_0036b118(r);
        FUN_000026e8(v);
        out[1] = 0;
        out[0] = 0;
    } else {
        FUN_000026e8(v);
        out[0] = elems;
        out[1] = 0;
    }
    return (word_t)out;
}

/* FUN_00069428 @ 0x69428  (est. dtk_vec_split_store)
 * Split a two-part vector and store the result if the flag is clear.
 * Confidence: low */
static void dtk_vec_split_store(word_t *out)
{
    word_t r = dtk_vec_split(0);
    if (0 == 0) {
        out[0] = r;
        out[1] = r;
    }
}

/* FUN_00069454 @ 0x69454  (est. dtk_vec_release_buf_a) */
static void dtk_vec_release_buf_a(word_t v) { dtk_vec_release_twice(v); }

/* FUN_00069458 @ 0x69458  (est. dtk_vec_release_buf_b) */
static void dtk_vec_release_buf_b(word_t v) { dtk_vec_release_twice(v); }

/* FUN_00069470 @ 0x69470  (est. dtk_vec_alloc32)
 * Allocate a growable vector with 0x20-byte elements, capacity max(count,
 * min) and a size field; empty sentinel when count == 0.
 * Confidence: medium */
static word_t dtk_vec_alloc32(word_t count, word_t cap)
{
    word_t buf;
    if (cap <= count)
        cap = count;
    if (cap == 0) {
        buf = (word_t)(word_t)DTK_EMPTY_VEC;
    } else {
        word_t tag = FUN_00002534(0x64e118, DTK_META_B);
        buf = FUN_0036a940(tag, cap * 0x20 + 0x20, 7);
        word_t sz = FUN_000126e8();
        *(word_t *)(buf + 0x10) = count;
        *(word_t *)(buf + 0x18) = (sz + -0x20) / 0x20 << 1;
    }
    return buf;
}

/* FUN_000694ec @ 0x694ec  (est. dtk_vec_alloc16)
 * Allocate a growable vector with 0x10-byte elements.  Confidence: medium */
static word_t dtk_vec_alloc16(word_t count, word_t cap, word_t tag, word_t meta)
{
    word_t buf;
    if (cap <= count)
        cap = count;
    if (cap == 0) {
        buf = (word_t)(word_t)DTK_EMPTY_VEC;
    } else {
        word_t t = FUN_00002534(tag, meta);
        buf = FUN_0036a940(t, cap * 0x10 + 0x20, 7);
        word_t sz = FUN_000126e8();
        *(word_t *)(buf + 0x10) = count;
        *(word_t *)(buf + 0x18) = (sz + -0x20) / 0x10 << 1;
    }
    return buf;
}

/* FUN_00069560 @ 0x69560  (est. dtk_vec_alloc24)
 * Allocate a growable vector with 0x18-byte elements.  Confidence: medium */
static word_t dtk_vec_alloc24(word_t count, word_t cap)
{
    word_t buf;
    if (cap <= count)
        cap = count;
    if (cap == 0) {
        buf = (word_t)(word_t)DTK_EMPTY_VEC;
    } else {
        word_t tag = FUN_00002534(0x64e0f0, DTK_META_C);
        buf = FUN_0036a940(tag, cap * 0x18 + 0x20, 7);
        word_t sz = FUN_000126e8();
        *(word_t *)(buf + 0x10) = count;
        *(word_t *)(buf + 0x18) = (sz + -0x20) / 0x18 << 1;
    }
    return buf;
}

/* FUN_000695e4 @ 0x695e4  (est. dtk_vec_reserve)
 * Reserve capacity in a growable vector (element size from the closure set):
 * grow to at least `count` elements (doubling when growing), copying the old
 * elements into the new buffer and releasing the old.  Confidence: medium */
static word_t dtk_vec_reserve(word_t flags, word_t count, word_t grow, word_t vec,
                              word_t alloc, word_t copy, word_t freefn)
{
    word_t cap = count;
    if ((grow & 1) != 0) {
        cap = *(word_t *)(vec + 0x18) >> 1;
        if ((long)cap < (long)count) {
            if ((long)(cap + 0x4000000000000000) < 0)
                CL4_FATAL();
            cap = *(word_t *)(vec + 0x18) & 0xfffffffffffffffe;
            if ((long)cap <= (long)count)
                cap = count;
        }
    }
    word_t old = *(word_t *)(vec + 0x10);
    word_t nb = ((word_t (*)(word_t, word_t))alloc)(old, cap);
    if ((flags & 1) == 0) {
        FUN_0006b6e0();
        ((word_t (*)(void))freefn)();
    } else {
        ((word_t (*)(word_t, word_t, word_t))copy)(vec + 0x20, old, nb + 0x20);
        *(word_t *)(vec + 0x10) = 0;
        FUN_0036b118(vec);
    }
    return nb;
}

/* FUN_000696a8 @ 0x696a8  (est. dtk_vec_reserve16)
 * Same reserve operation specialised for 0x10-byte element vectors.
 * Confidence: medium */
static word_t dtk_vec_reserve16(word_t flags, word_t count, word_t grow, word_t vec,
                                word_t tag, word_t meta, word_t copy, word_t freefn)
{
    word_t cap = count;
    if ((grow & 1) != 0) {
        cap = *(word_t *)(vec + 0x18) >> 1;
        if ((long)cap < (long)count) {
            if ((long)(cap + 0x4000000000000000) < 0)
                CL4_FATAL();
            cap = *(word_t *)(vec + 0x18) & 0xfffffffffffffffe;
            if ((long)cap <= (long)count)
                cap = count;
        }
    }
    word_t old = *(word_t *)(vec + 0x10);
    word_t nb = dtk_vec_alloc16(old, cap, tag, meta);
    if ((flags & 1) == 0) {
        FUN_0006b6e0();
        ((word_t (*)(void))freefn)();
    } else {
        ((word_t (*)(word_t, word_t, word_t))copy)(vec + 0x20, old, nb + 0x20);
        *(word_t *)(vec + 0x10) = 0;
        FUN_0036b118(vec);
    }
    return nb;
}

/* FUN_00069770 @ 0x69770  (est. dtk_vec_copy16_out)
 * Copy `len` 0x10-byte elements from the vector's storage at
 * param_4 + from*0x10 + 0x20 into param_3, then release the vector.
 * Returns the destination end.  Panics on overlap.
 * Confidence: medium */
static word_t dtk_vec_copy16_out(word_t from, word_t to, word_t dst, word_t vec)
{
    word_t len = to - from;
    if (to < from)
        CL4_FATAL();
    if ((long)len >= 0) {
        word_t src = vec + from * 0x10 + 0x20;
        word_t end = dst + len * 0x10;
        if (end <= src || src + len * 0x10 <= dst) {
            FUN_0035b67c(dst, src, len, 0x6753a0);
            FUN_0036b118(vec);
            return end;
        }
        CL4_FATAL();
    }
    CL4_FATAL();
}

/* FUN_000697e4 @ 0x697e4  (est. dtk_vec_copy32_out)
 * Copy `len` 0x20-byte elements out of the vector.  Confidence: medium */
static word_t dtk_vec_copy32_out(word_t from, word_t to, word_t dst, word_t vec)
{
    word_t len = to - from;
    if (to < from)
        CL4_FATAL();
    if ((long)len >= 0) {
        word_t src = vec + from * 0x20 + 0x20;
        word_t end = dst + len * 0x20;
        if (end <= src || src + len * 0x20 <= dst) {
            FUN_0035b67c(dst, src, len, 0x675c68);
            FUN_0036b118(vec);
            return end;
        }
        CL4_FATAL();
    }
    CL4_FATAL();
}

/* FUN_00069858 @ 0x69858  (est. dtk_vec_copy16_out_2)
 * Copy `len` 0x10-byte elements out of the vector (variant log string).
 * Confidence: medium */
static word_t dtk_vec_copy16_out_2(word_t from, word_t to, word_t dst, word_t vec)
{
    word_t len = to - from;
    if (to < from)
        CL4_FATAL();
    if ((long)len >= 0) {
        word_t src = vec + from * 0x10 + 0x20;
        word_t end = dst + len * 0x10;
        if (end <= src || src + len * 0x10 <= dst) {
            FUN_0035b67c(dst, src, len, 0x65cf58);
            FUN_0036b118(vec);
            return end;
        }
        CL4_FATAL();
    }
    CL4_FATAL();
}

/* FUN_000698cc @ 0x698cc  (est. dtk_vec_copy24_out)
 * Copy `len` 0x18-byte elements out of the vector.  Confidence: medium */
static word_t dtk_vec_copy24_out(word_t from, word_t to, word_t dst, word_t vec)
{
    word_t len = to - from;
    if (to < from)
        CL4_FATAL();
    if ((long)len >= 0) {
        word_t src = vec + from * 0x18 + 0x20;
        word_t end = dst + len * 0x18;
        if (end <= src || src + len * 0x18 <= dst) {
            word_t tag = FUN_00002534(0x64e0e8, DTK_META_D);
            FUN_0035b67c(dst, src, len, tag);
            FUN_0036b118(vec);
            return end;
        }
        CL4_FATAL();
    }
    CL4_FATAL();
}

/* FUN_00069970 @ 0x69970  (est. dtk_vec_memmove16)
 * Move `count` 0x10-byte elements from param_1 to param_3 (memmove, no-op on
 * exact self-copy with no overlap).  Panics on negative count.
 * Confidence: medium */
static void dtk_vec_memmove16(word_t src, word_t count, word_t dst)
{
    if ((long)count < 0)
        CL4_FATAL();
    if (dst != src || src + count * 0x10 <= dst)
        FUN_00117d14(dst, src, count << 4);
}

/* FUN_000699a4 @ 0x699a4  (est. dtk_vec_memmove32)
 * Move `count` 0x20-byte elements.  Confidence: medium */
static void dtk_vec_memmove32(word_t src, word_t count, word_t dst)
{
    if ((long)count < 0)
        CL4_FATAL();
    if (dst != src || src + count * 0x20 <= dst)
        FUN_00117d14(dst, src, count << 5);
}

/* FUN_000699d8 @ 0x699d8  (est. dtk_vec_memmove24)
 * Move `count` 0x18-byte elements.  Confidence: medium */
static void dtk_vec_memmove24(word_t src, word_t count, word_t dst)
{
    if ((long)count < 0)
        CL4_FATAL();
    if (dst != src || src + count * 0x18 <= dst)
        FUN_00117d14(dst, src, count * 0x18);
}

/* FUN_00069a14 @ 0x69a14  (est. dtk_collect_names)
 * Collect every child node name of the current node into a fresh 0x10-byte
 * element vector, growing it on demand.  Confidence: medium */
static word_t dtk_collect_names(void)
{
    word_t it[4];
    word_t vec = (word_t)(word_t)DTK_EMPTY_VEC;
    word_t *ptr = DTK_VEC_STORE;
    word_t room = 0;
    dtk_end_dump(it);
    if (it[4] != 1) {
        while (!(dt_iter_end(it) & 1)) {
            word_t nm[2] = { 0, 0 };
            if ((dt_children(it, nm) & 1) == 0)
                break;
            dt_iter_advance(it);
            word_t nv = nm[0], nl = nm[1];
            if (room == 0) {
                word_t cap = *(word_t *)(vec + 0x18) & 0xfffffffffffffffe;
                if ((long)*(word_t *)(vec + 0x18) < 2)
                    cap = 1;
                word_t tag = FUN_00002534(0x64e0d8, DTK_META_E);
                word_t nb = FUN_0036a940(tag, cap * 0x10 + 0x20, 7);
                word_t sz = FUN_000126e8();
                *(word_t *)(nb + 0x10) = cap;
                *(word_t *)(nb + 0x18) = (sz + -0x20) / 0x10 << 1;
                word_t oldn = *(word_t *)(vec + 0x18) >> 1;
                if (*(long *)(vec + 0x10) != 0) {
                    if (nb != vec || vec + 0x20 + oldn * 0x10 <= nb + 0x20)
                        FUN_00117d14(nb + 0x20, vec + 0x20, oldn << 4);
                    *(word_t *)(vec + 0x10) = 0;
                }
                ptr = (word_t *)(nb + 0x20 + oldn * 0x10);
                room = (sz & 0x7fffffffffffffff) / 0x10 - (*(word_t *)(vec + 0x18) >> 1);
                FUN_0036b118(vec);
                vec = nb;
            }
            room = room - 1;
            if (room + 1 < room)
                CL4_FATAL();
            *ptr = nv;
            ptr[1] = nl;
            ptr += 2;
        }
    }
    if (*(word_t *)(vec + 0x18) > 1) {
        word_t cap = *(word_t *)(vec + 0x18) >> 1;
        if (cap - room < cap)
            *(word_t *)(vec + 0x10) = cap - room;
    }
    return vec;
}

/* FUN_00069bdc @ 0x69bdc  (est. dtk_collect_props)
 * Collect every property of the current node into a fresh 0x20-byte element
 * vector (each entry: {name, namelen, data, datalen}).  Confidence: medium */
static word_t dtk_collect_props(void)
{
    word_t it[4];
    word_t vec = (word_t)(word_t)DTK_EMPTY_VEC;
    word_t *ptr = DTK_VEC_STORE;
    word_t room = 0;
    dtk_begin_dump(it);
    if (it[4] != 1) {
        while (!(dt_iter_end(it) & 1)) {
            word_t a = 0, b = 0, c = 0, d = 0;
            if ((dt_node_get(it, &b, &c) & 1) == 0)
                break;
            if (c > 0x1f)
                CL4_FATAL();
            if ((dt_node_name_propcount(it, &d, &a) & 1) == 0)
                break;
            if (b == 0)
                break;
            if (d == 0)
                break;
            word_t namelen = c + 1;
            if (c + 1 < c || (long)namelen < 0 || (long)a < 0)
                CL4_FATAL();
            dt_iter_advance(it);
            if (room == 0) {
                word_t cap = *(word_t *)(vec + 0x18) & 0xfffffffffffffffe;
                if ((long)*(word_t *)(vec + 0x18) < 2)
                    cap = 1;
                word_t tag = FUN_00002534(0x64e120, DTK_META_F);
                word_t nb = FUN_0036a940(tag, cap * 0x20 + 0x20, 7);
                word_t sz = FUN_000126e8();
                *(word_t *)(nb + 0x10) = cap;
                *(word_t *)(nb + 0x18) = (sz + -0x20) / 0x20 << 1;
                word_t oldn = *(word_t *)(vec + 0x18) >> 1;
                if (*(long *)(vec + 0x10) != 0) {
                    if (nb != vec || vec + 0x20 + oldn * 0x20 <= nb + 0x20)
                        FUN_00117d14(nb + 0x20, vec + 0x20, oldn << 5);
                    *(word_t *)(vec + 0x10) = 0;
                }
                ptr = (word_t *)(nb + 0x20 + oldn * 0x20);
                room = (sz & 0x7fffffffffffffff) / 0x20 - (*(word_t *)(vec + 0x18) >> 1);
                FUN_0036b118(vec);
                vec = nb;
            }
            room = room - 1;
            if (room + 1 < room)
                CL4_FATAL();
            ptr[0] = b;
            ptr[1] = namelen;
            ptr[2] = d;
            ptr[3] = a + d;
            ptr += 4;
        }
    }
    if (*(word_t *)(vec + 0x18) > 1) {
        word_t cap = *(word_t *)(vec + 0x18) >> 1;
        if (cap - room < cap)
            *(word_t *)(vec + 0x10) = cap - room;
    }
    return vec;
}

/* FUN_00069e10 @ 0x69e10  (est. dtk_collect_from_list)
 * Collect all two-word entries from a device-tree list into a fresh 0x10-byte
 * element vector.  Fatal on any out-of-range lookup.
 * Confidence: medium */
static word_t dtk_collect_from_list(word_t head)
{
    word_t n = dt_list_len((word_t *)head);
    word_t vec = (word_t)(word_t)DTK_EMPTY_VEC;
    word_t *ptr = DTK_VEC_STORE;
    word_t room = 0;
    word_t i = 0;
    while (1) {
        if ((n & ((long)n >> 0x3f ^ (word_t)-1)) == i) {
            if (*(word_t *)(vec + 0x18) > 1) {
                word_t cap = *(word_t *)(vec + 0x18) >> 1;
                if (cap - room < cap)
                    *(word_t *)(vec + 0x10) = cap - room;
            }
            return vec;
        }
        word_t e[2] = { 0, 0 };
        word_t rc = dt_list_at((word_t *)head, i, e);
        word_t a = e[0], b = e[1];
        if ((rc & 1) == 0)
            FUN_001afa84((word_t)"Fatal error", 0xb, 2, 0x207865646e49,
                         0xe600000000000000,
                         (word_t)"DeviceTreeKit/DeviceTreeKit.swif", 0x21, 2, 0xa6, 0);
        if (room == 0) {
            word_t cap = *(word_t *)(vec + 0x18) & 0xfffffffffffffffe;
            if ((long)*(word_t *)(vec + 0x18) < 2)
                cap = 1;
            word_t tag = FUN_00002534(0x64e0d8, DTK_META_E);
            word_t nb = FUN_0036a940(tag, cap * 0x10 + 0x20, 7);
            word_t sz = FUN_000126e8();
            *(word_t *)(nb + 0x10) = cap;
            *(word_t *)(nb + 0x18) = (sz + -0x20) / 0x10 << 1;
            word_t oldn = *(word_t *)(vec + 0x18) >> 1;
            if (*(long *)(vec + 0x10) != 0) {
                if (nb != vec || vec + 0x20 + oldn * 0x10 <= nb + 0x20)
                    FUN_00117d14(nb + 0x20, vec + 0x20, oldn << 4);
                *(word_t *)(vec + 0x10) = 0;
            }
            ptr = (word_t *)(nb + 0x20 + oldn * 0x10);
            room = (sz & 0x7fffffffffffffff) / 0x10 - (*(word_t *)(vec + 0x18) >> 1);
            FUN_0036b118(vec);
            vec = nb;
        }
        room = room - 1;
        if (room + 1 < room)
            CL4_FATAL();
        *ptr = a;
        ptr[1] = b;
        i = i + 1;
        ptr += 2;
    }
}

/* FUN_0006a078 @ 0x6a078  (est. dtk_flatten_props)
 * Flatten up to `count` properties into an output array of 0x20-byte records
 * (each {name, namelen, data, datalen}), walking the node's property iterator.
 * Returns the number produced.  Confidence: medium */
static word_t dtk_flatten_props(word_t *out, word_t *dst, word_t count, word_t base, word_t size)
{
    word_t rng[4] = { 0, 0, 0, 0 };
    word_t ok = dt_range_set(base, size, rng);
    word_t bad = (ok & 1) == 0;
    word_t a0 = rng[0], a1 = rng[1], a2 = rng[2], a3 = rng[3];
    if (bad) { a0 = a1 = a2 = a3 = 0; }
    word_t produced;
    if (dst == 0) {
        produced = 0;
    } else {
        if ((long)count < 0)
            CL4_FATAL();
        if (count != 0) {
            word_t i = 0;
            word_t notdone = ok ^ 1;
            do {
                if ((notdone & 1) != 0) {
                    produced = i;
                    goto done;
                }
                rng[0] = a0; rng[1] = a1; rng[2] = a2; rng[3] = a3;
                if ((dt_iter_end(rng) & 1) != 0) {
                    produced = i;
                    a0 = rng[0]; a1 = rng[1]; a2 = rng[2]; a3 = rng[3];
                    goto done;
                }
                word_t nm = 0, nl = 0;
                if ((dt_children(rng, &nm) & 1) == 0) {
                    produced = i;
                    a0 = rng[0]; a1 = rng[1]; a2 = rng[2]; a3 = rng[3];
                    goto done;
                }
                i = i + 1;
                dt_iter_advance(rng);
                notdone = 0;
                dst[0] = nm; dst[1] = nl; dst[2] = 0; dst[3] = nl;
                dst += 4;
                a0 = rng[0]; a1 = rng[1]; a2 = rng[2]; a3 = rng[3];
            } while (count != i);
            produced = 0;
        } else {
            produced = 0;
        }
    }
done:
    out[0] = a0;
    out[1] = a1;
    out[2] = a2;
    out[3] = a3;
    *(word_t *)((word_t)out + 4) = bad ? 1 : 0;
    return produced;
}

/* FUN_0006a224 @ 0x6a224  (est. dtk_flatten_names)
 * Flatten up to `count` node names into an output array of 0x10-byte records
 * (each {name, namelen}), walking the node's name iterator.
 * Returns the number produced.  Confidence: medium */
static word_t dtk_flatten_names(word_t *out, word_t *dst, word_t count, word_t base, word_t size)
{
    word_t rng[4] = { 0, 0, 0, 0 };
    word_t rc = dt_range_make(base, size, rng);
    word_t bad = (rc & 1) == 0;
    word_t a0 = rng[0], a1 = rng[1], a2 = rng[2], a3 = rng[3];
    if (bad) { a0 = a1 = a2 = a3 = 0; }
    word_t produced;
    if (dst == 0) {
        produced = 0;
    } else {
        if ((long)count < 0)
            CL4_FATAL();
        if (count != 0) {
            word_t i = 0;
            word_t notdone = rc ^ 1;
            do {
                if ((notdone & 1) != 0) {
                    produced = i;
                    goto done2;
                }
                rng[0] = a0; rng[1] = a1; rng[2] = a2; rng[3] = a3;
                if ((dt_range_end(rng) & 1) != 0) {
                    produced = i;
                    a0 = rng[0]; a1 = rng[1]; a2 = rng[2]; a3 = rng[3];
                    goto done2;
                }
                word_t nm[2] = { 0, 0 };
                if ((dt_children(rng, nm) & 1) == 0) {
                    produced = i;
                    a0 = rng[0]; a1 = rng[1]; a2 = rng[2]; a3 = rng[3];
                    goto done2;
                }
                i = i + 1;
                dt_iter_advance(rng);
                notdone = 0;
                dst[0] = nm[0];
                dst[1] = nm[1];
                dst += 2;
                a0 = rng[0]; a1 = rng[1]; a2 = rng[2]; a3 = rng[3];
            } while (count != i);
            produced = 0;
        } else {
            produced = 0;
        }
    }
done2:
    out[0] = a0;
    out[1] = a1;
    out[2] = a2;
    out[3] = a3;
    *(word_t *)((word_t)out + 4) = bad ? 1 : 0;
    return produced;
}

/* FUN_0006a374 @ 0x6a374  (est. dtk_vec_store_realloc)
 * Store the result of the 0x10-byte vector reserve into the object at x20.
 * Confidence: medium */
static void dtk_vec_store_realloc(void)
{
    *(word_t *)0 = dtk_vec_reserve16(0, 0, 0, 0, 0, 0, 0, 0);
}

/* FUN_0006a3cc @ 0x6a3cc  (est. dtk_lazy_init_once)
 * Lazy single-time initialisation: if *param_1 is empty, build the value via
 * FUN_00027614/FUN_00376820 and store it.  Confidence: medium */
static void dtk_lazy_init_once(word_t *slot, word_t a, word_t b, word_t c)
{
    if (*slot == 0) {
        word_t v = FUN_00027614(a, b);
        word_t r = FUN_00376820(c, v);
        *slot = r;
    }
}

/* FUN_0006a414 @ 0x6a414  (est. dtk_scratch_store)
 * Store an opaque constant into the DeviceTreeKit scratch word (0x64e050).
 * Confidence: low (opaque constant store) */
static void dtk_scratch_store(void)
{
    *(volatile word_t *)0x64e050 = 0xf9462d0890000588;
}

/*__MORE__*/
