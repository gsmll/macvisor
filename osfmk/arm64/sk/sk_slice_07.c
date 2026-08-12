/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel,
 * arm64e, image base 0) — the cL4 microkernel (GL1), "cL4 (679.100.61)".
 * Ground truth: Ghidra FUN_ names + addresses in program cl4_kernel.raw.
 * Slice 07: 0x38220-0x43780 — the VSpace / page-table region: the vspace span
 * tree (AVL-style), the per-vspace lock collection (free lists), the
 * virtual->physical page-walk / map / unmap primitives, the shadow-space
 * (page-table level array) setup/teardown, and the COW fault path. All names
 * are estimates unless string/header-matched. Uses seL4/cL4 vocabulary.
 * NOTE on calling convention: the decompiler shows most helpers as `void
 * FUN(void)` because args pass in registers; we model the collection `this`
 * pointer explicitly and give signatures matching observed register use.
 */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

typedef uint64_t word_t;
typedef uint32_t seL4_Word;

/* 16-byte result: lo = status/error code, hi = pointer/type tag. */
typedef struct sk_pair { uint64_t lo; uint64_t hi; } sk_pair_t;

#define SK_FATAL() __builtin_trap()       /* SoftwareBreakpoint(1,<addr>) */
#define SK_ABORT(str) __builtin_trap()    /* FUN_004afae4(str) noreturn VAS abort */

#define SK_VCAP_SPAN  0x65b5c8ull
#define SK_VCAP       0x65b648ull
#define SK_VCAP_BUFFER 0x65b6a0ull

/* ------------------------------------------------------------------ *
 * Out-of-range cL4 helpers (bodies reconstructed by range workers that own
 * them). Signatures reflect observed register use.
 * ------------------------------------------------------------------ */
extern void   FUN_004afae4(const char *);              /* noreturn VAS abort */
extern void   FUN_0011d7e8(word_t, ...);               /* noreturn panic */
extern sk_pair_t FUN_004b31c4(void);
extern sk_pair_t FUN_004b318c(void);
extern sk_pair_t FUN_004b2fc8(void);
extern sk_pair_t FUN_004b2fe0(word_t, word_t, void*);
extern void   FUN_004b2f80(word_t, void*);
extern void   FUN_004b2f58(void);
extern void   FUN_004b3154(void);
extern sk_pair_t FUN_004b311c(void);
extern void   FUN_004b30ac(void);
extern sk_pair_t FUN_004b30e4(void);
extern void   FUN_004b3064(word_t, void*);
extern word_t FUN_00032cd0(word_t);
extern word_t FUN_00032cec(void);
extern word_t FUN_00032e44(void);
extern word_t FUN_00030cc8(word_t);
extern word_t FUN_00033594(void);
extern word_t FUN_000334f0(void);
extern word_t FUN_0003344c(void);
extern void   FUN_00033148(word_t);
extern void   FUN_000335e0(void);
extern void   FUN_0003353c(void);
extern void   FUN_00033498(void);
extern int    FUN_00118164(void*);
extern int    FUN_00118194(void*, ...);
extern int    FUN_00118148(void*, int);
extern void   FUN_001143a0(void*, word_t, int);
extern void   FUN_0000178c(word_t*, word_t);
extern word_t FUN_0005acac(word_t, int, int);
extern word_t FUN_0005baac(int, int);
extern void   FUN_0005ba5c(word_t);
extern word_t FUN_00054de4(void);
extern word_t FUN_00034ba4(word_t);
extern sk_pair_t FUN_00034bd8(word_t);
extern void   FUN_00034b10(word_t, word_t, int);
extern word_t FUN_00034f70(void);
extern word_t FUN_000553e4(word_t, word_t);
extern word_t FUN_0005530c(void);
extern word_t FUN_00055360(void);
extern word_t FUN_00055344(void);
extern word_t FUN_00034a2c(void);
extern void   FUN_00035ba0(word_t*, word_t, int);
extern void   FUN_000287e4(word_t*, word_t, int);
extern void   FUN_000363ac(word_t*, word_t, int);
extern void   FUN_00036a94(word_t*, word_t, int);
extern word_t FUN_0003667c(word_t*);
extern word_t FUN_000368f8(word_t);
extern void   FUN_0003611c(word_t*, word_t, int, word_t);
extern word_t FUN_00035b98(void);
extern void   FUN_00034dec(word_t, word_t*, word_t, word_t);
extern void   FUN_00044ff4(word_t, word_t*);
extern void   FUN_00044be0(word_t, word_t);
extern void   FUN_00044c94(word_t, word_t, word_t);
extern void   FUN_00044dec(word_t, word_t*, word_t, word_t);
extern void   FUN_00043e88(void);
extern word_t FUN_00043c74(word_t, word_t, word_t, word_t);
extern word_t FUN_00043be8(word_t, word_t, word_t, word_t, word_t, word_t);
extern word_t FUN_00043b44(word_t);
extern word_t FUN_00043f28(word_t, word_t, word_t, int);
extern word_t FUN_000555ac(word_t, word_t, word_t);
extern void   FUN_000457f8(word_t*, word_t, void*);
extern void   FUN_00045728(word_t*, word_t, word_t, word_t, int, void*);
extern void   FUN_000458a0(word_t*, word_t, void*, void*);
extern void   FUN_00045908(word_t*, word_t, void*, word_t, void*);
extern int    FUN_00045cb8(void*);
extern void   FUN_000446ec(word_t);
extern word_t FUN_00053470(void);
extern void   FUN_00117f8c(word_t*, word_t, word_t);
extern word_t FUN_00031594(word_t, word_t);
extern word_t FUN_00116c78(word_t*, int);
extern void   FUN_0005b190(int, const char*);
extern word_t FUN_000559b8(char);
extern void   FUN_00033b50(void*);
extern word_t FUN_00034334(word_t);
extern void   FUN_000304c4(word_t, word_t, word_t);
extern void   FUN_00036920(word_t, word_t);
extern void   FUN_00114790(word_t, word_t, word_t);
extern void   FUN_00118b28(const char*);
extern void   FUN_004b23d8(void*);
extern void   FUN_004b2820(word_t);
extern void   FUN_004b3a58(word_t, word_t, const char*, int, const char*, const char*, ...);
extern void   FUN_004b3ac8(void);
extern void   FUN_004b3bf8(void);
extern void   FUN_004b3bc0(void);
extern void   FUN_004b3c24(void);
extern void   FUN_004b3c4c(void);
extern void   FUN_004b3af4(void);
extern void   FUN_004b3d2c(void);
extern void   FUN_004b3d7c(void);
extern sk_pair_t FUN_004b3cd0(word_t, void*);
extern void   FUN_004b3e30(void);
extern void   FUN_004b3e5c(word_t, word_t);
extern void   FUN_004b3da4(word_t, word_t, word_t, word_t);
extern sk_pair_t FUN_004b3d54(word_t, void*);
extern sk_pair_t FUN_004b3ec4(void);
extern void   FUN_004b350c(void);
extern void   FUN_004b363c(void*, void*);
extern void   FUN_004b3768(word_t, int);
extern void   FUN_004b377c(word_t, word_t);
extern void   FUN_004b3790(void);
extern void   FUN_004b37a4(void);
extern void   FUN_004b3538(word_t, word_t, word_t, word_t);
extern void   FUN_004b35a0(word_t, void*);
extern word_t FUN_004b35f4(void);
extern word_t FUN_004b38a8(word_t, void*);
extern word_t FUN_004b38f8(word_t, void*);
extern word_t FUN_004b3940(word_t, void*);
extern word_t FUN_004b3988(word_t, void*);
extern word_t FUN_004b37b8(word_t, void*);
extern word_t FUN_004b3808(word_t, void*);
extern word_t FUN_004b3858(word_t, void*);
extern word_t FUN_004b36c8(word_t, void*);
extern word_t FUN_004b3718(word_t, void*);
extern void   FUN_004b3a08(void);
extern void   FUN_004b3a30(void);
extern void   FUN_004b3b08(word_t, void*);
extern void   FUN_004b3b64(word_t, void*);
extern void   FUN_004b339c(void);
extern void   FUN_004b33c4(void);
extern void   FUN_004b33ec(void);
extern void   FUN_004b3414(void);
extern void   FUN_004b343c(void);
extern word_t FUN_004b3464(void);
extern void   FUN_004b349c(void);
extern void   FUN_004b32bc(word_t, int);
extern void   FUN_004b32f4(void);
extern void   FUN_004b332c(void);
extern void   FUN_004b326c(void);
extern void   FUN_004b3294(void);
extern void   FUN_004b3364(void);
extern void   FUN_004b34d4(void);
extern void   FUN_004b30ac(void);
extern sk_pair_t FUN_0004ba18(void);
extern void   FUN_001185ec(word_t, const char*);
extern void   FUN_0011858c(word_t);
extern void   FUN_0011d7e8(word_t, ...);
extern word_t FUN_00032514(void);
extern void   FUN_00033684(void*);
extern void   FUN_000539fc(void*);
extern void   FUN_0004b8d0(word_t, int);
extern void   FUN_00034d5c(word_t, word_t, word_t);
extern word_t FUN_00032cd0(word_t);

/* globals / constants referenced (addresses from Ghidra) */
extern word_t DAT_006af198, DAT_006ad39c, DAT_006ad304, DAT_006ad308;
extern word_t DAT_006ad30c, DAT_006ad31c, DAT_006ad320, DAT_006ad328;
extern word_t DAT_006ad330, DAT_006ad310, DAT_006ad314, DAT_006ad334;
extern word_t DAT_006ad33c, DAT_006ad338, DAT_006ad340;
extern word_t DAT_006af2b8, DAT_006af298;
extern char  DAT_006af2b9, DAT_006af2ba, DAT_006af2bb;
extern word_t DAT_0064c3f0, DAT_0064c450, DAT_0064cba0, DAT_0064cb80;
extern word_t DAT_004bb180, DAT_004bc1f0, DAT_004bb178, DAT_004bc208;
extern word_t DAT_004bbfd8, DAT_004bc210;

#define CARRY8(a,b) ((__uint128_t)(a)+(__uint128_t)(b) > (__uint128_t)0xffffffffffffffffULL)

/* Supervisor-call and per-cpu pointer used by the page-walk paths. */
#define CallSupervisor(n) __asm__ volatile("svc #0" : : "r"((long)(n)))
/* tpidrro_el0 (TPIDRRO_EL0, the read-only per-cpu pointer): read it via asm
 * into a word_t variable. Code uses `word_t *tp = (word_t *)tpidrro_el0`. */
#define tpidrro_el0 ({ word_t _v; __asm__ volatile("mrs %0, tpidrro_el0" : "=r"(_v)); _v; })

/* ------------------------------------------------------------------ *
 * Forward declarations for in-file static helpers (mutually recursive /
 * used-before-defined).
 * ------------------------------------------------------------------ */
static bool sk_lock_collection_alloc(word_t *, word_t, word_t, word_t, word_t, word_t);
static void sk_lock_collection_free(word_t *);
static word_t *sk_lock_pop_primary(word_t);
static word_t *sk_lock_pop_secondary(word_t);
static word_t *sk_lock_pop_tertiary(word_t);
static word_t *sk_lock_pop_quaternary(word_t);
static word_t *sk_lock_pop_quinary(word_t);
static void sk_lock_push_primary(word_t, word_t *);
static void sk_lock_push_tertiary(word_t, word_t *);
static void sk_lock_push_quaternary(word_t, word_t *);
static void sk_lock_push_quinary(word_t, word_t *);
static void sk_span_tree_rebalance(word_t *, int);
static void sk_span_teardown_node(word_t);
static void sk_span_tree_update_extent(word_t, word_t);
static sk_pair_t sk_vspace_span_merge(word_t *, word_t, void *, void *, word_t *, word_t *);
static void sk_span_encode_meta(char *);
static sk_pair_t sk_vspace_span_split(void *, word_t, void *, word_t, word_t *, word_t *);
static void sk_spanmap_walk(word_t *, word_t *, word_t, word_t *);
static void sk_span_prefetch_pages(char *, word_t, word_t);
static word_t sk_span_leaf_walk(char *, word_t, word_t);
static word_t sk_span_leaf_walk_v2(char *, word_t, word_t, word_t, word_t, int, uint32_t);
static word_t sk_span_map_page_walk(word_t, word_t, word_t, word_t, word_t, int, word_t);
static word_t sk_span_map_check(word_t, word_t *, word_t *);
static sk_pair_t sk_span_map_check_window(word_t, word_t *, word_t *, int);
static void sk_vspace_unmap_range(word_t, word_t, word_t, word_t, word_t);
static void sk_spanmap_unmap_one(word_t, word_t, int, int, int);
static sk_pair_t sk_vspace_region_create(word_t, uint32_t, char *, word_t *, uint32_t *, word_t *);
static word_t sk_populate_level(word_t, word_t, word_t);
static word_t sk_populate_level_rec(word_t, word_t, word_t);
static void sk_span_tree_insert_caller(word_t *, word_t);
static word_t sk_span_tree_remove(word_t *, word_t);
static word_t sk_vspace_find_region(word_t *, word_t);
static word_t sk_vspace_find_nonempty(word_t, word_t);
static word_t sk_span_merge_caller(word_t *, word_t, word_t, word_t);
static sk_pair_t sk_span_destroy_impl(word_t *);
static void sk_vspace_region_apply(word_t, word_t, word_t);
static sk_pair_t sk_vspace_lookup_map(word_t, word_t, word_t *, word_t *);
static void sk_l4_error_string(word_t *, uint8_t);
static void sk_spanmap_level_cb(word_t, word_t);
static void sk_spanmap_level_cb2(word_t, word_t, word_t, word_t);
static void sk_span_retire_page(word_t);
static word_t sk_vspace_lock_enter(word_t *, word_t, word_t, word_t);
static void sk_vspace_lock_exit(word_t *, word_t);
static void sk_lock_collection_attach(word_t *, word_t *, word_t, word_t);
static sk_pair_t sk_faulf_dispatch(word_t, word_t, word_t, word_t, uint8_t *);
static sk_pair_t sk_faulf_handler_run(word_t);
static void sk_startfault_cow(word_t, word_t, uint32_t, word_t, void *);
static void sk_startfault_done(word_t, word_t, word_t);
static word_t sk_span_map_page_walk(word_t, word_t, word_t, word_t, word_t, int, word_t);
static word_t sk_vspace_layout_compute(word_t, int, word_t, word_t, word_t, word_t);
static void sk_vspace_span_split_simple(word_t, word_t);


/* ================================================================== *
 * VSpace lock collection (FUN_0003b820 / 0003bca0 / 0003bac0 / 0003be18 /
 * 0003beec / 0003be88 / 0003bfb8 / 0003bd70) and its free-list push/pop
 * primitives (FUN_0003b340/410/478/548/5b0/648/6ac, 0003c21c, 0003e640).
 * ================================================================== */

/* FUN_0003b820 @ 0x3b820  (est. sk_lock_collection_alloc)
 * Build a lock-collection record at param_1 for vspace param_2: allocate up to
 * param_3 primary tokens, param_4 secondary, param_5 tertiary and param_6
 * quaternary tokens, chaining each onto its free list (heads at +8/+0x10/
 * +0x18/+0x20/+0x28, counts at +0x30..+0x38). Each count must be <= 3. On any
 * allocation failure the partial record is freed via sk_lock_collection_free
 * and 0 returned. Returns 1 on success.
 * Confidence: high */
static bool sk_lock_collection_alloc(word_t *rec, word_t vspace,
                                     word_t np, word_t ns, word_t nt, word_t nq)
{
    if (3 < np || 3 < ns || 3 < nt) SK_ABORT("VAS abort");
    *rec = vspace;
    rec[6] = 0; rec[5] = 0; rec[2] = 0; rec[1] = 0;
    rec[4] = 0; rec[3] = 0; rec[7] = 0;
    *(uint16_t *)(rec + 8) = (uint16_t)np | (uint16_t)(ns << 4)
        | (uint16_t)(nt << 8) | (uint16_t)(nq << 12);
    *(uint32_t *)((word_t)rec + 0x42) = 0;
    *(uint16_t *)((word_t)rec + 0x46) = 0;
    while (*(uint8_t *)(rec + 6) < np) {
        word_t tok = FUN_00032e44();
        if (tok == 0) goto fail;
        sk_lock_push_primary((word_t)rec, (word_t *)tok);
    }
    word_t i = *(uint8_t *)((word_t)rec + 0x31);
    while (i < ns) {
        word_t *tok = (word_t *)FUN_00030cc8(vspace);
        if (tok == (word_t *)0) goto fail;
        *(uint8_t *)(tok + 3) = 0;
        uint8_t b = *(uint8_t *)((word_t)rec + 0x31);
        if (2 < b) SK_ABORT("VAS abort");
        *tok = rec[2];
        rec[2] = (word_t)tok;
        i = (word_t)b + 1;
        *(uint8_t *)((word_t)rec + 0x31) = (uint8_t)i;
    }
    while (*(uint8_t *)((word_t)rec + 0x32) < nt) {
        word_t tok = FUN_00033594();
        if (tok == 0) goto fail;
        sk_lock_push_tertiary((word_t)rec, (word_t *)tok);
    }
    if (nq != 0 || nt != 0) {
        word_t tok = FUN_000334f0();
        if (tok == 0) goto fail;
        sk_lock_push_quaternary((word_t)rec, (word_t *)tok);
    }
    while (nq > (word_t)rec[7]) {
        word_t tok = FUN_0003344c();
        if (tok == 0) break;
        sk_lock_push_quinary((word_t)rec, (word_t *)tok);
    }
    return true;
fail:
    sk_lock_collection_free(rec);
    return false;
}

/* FUN_0003bac0 @ 0x3bac0  (est. sk_lock_collection_free)
 * Release every token in the collection's free lists back to its zone, in
 * reverse order of acquisition. Asserts each intermediate list is exhausted
 * between passes. The tail is zeroed via FUN_001143a0.
 * Confidence: high */
static void sk_lock_collection_free(word_t *rec)
{
    word_t vspace = rec[0];
    uint8_t n = *(uint8_t *)(rec + 6);
    while (n != 0) {
        word_t *tok = sk_lock_pop_primary((word_t)rec);
        if ((word_t)tok + 0xb0 < (word_t)tok) SK_FATAL();
        *(word_t *)((word_t)tok + 0x50) = 0;
        FUN_00033148((word_t)tok);
        n = *(uint8_t *)(rec + 6);
    }
    if (rec[1] != 0) SK_ABORT("VAS abort");
    while (*(uint8_t *)((word_t)rec + 0x31) != 0) {
        sk_lock_pop_secondary((word_t)rec);
        FUN_000335e0();
    }
    if (rec[2] != 0) SK_ABORT("VAS abort");
    while (*(uint8_t *)((word_t)rec + 0x32) != 0) {
        sk_lock_pop_tertiary((word_t)rec);
        FUN_0003353c();
    }
    if (rec[3] != 0) SK_ABORT("VAS abort");
    while (rec[7] != 0) {
        sk_lock_pop_quinary((word_t)rec);
        FUN_00033498();
    }
    if (rec[4] != 0) SK_ABORT("VAS abort");
    FUN_001143a0(rec, 0xffffffc0, 8);
}

/* FUN_0003bca0 @ 0x3bca0  (est. sk_lock_collection_attach)
 * Attach a pre-built lock collection to vspace param_2 by linking rec into
 * vspace+0x50. The special DAT_0064c3f0 context is torn down first.
 * Confidence: high */
static void sk_lock_collection_attach(word_t *rec, word_t *vspace,
                                      word_t a3, word_t a4)
{
    if ((word_t *)*rec != vspace) SK_ABORT("VAS abort");
    if (vspace == (word_t *)&DAT_0064c3f0) FUN_00043e88();
    FUN_00044c94((word_t)vspace, a3, a4);
    if (vspace[10] == 0) { vspace[10] = (word_t)rec; return; }
    SK_ABORT("VAS abort");
}

/* FUN_0003bd70 @ 0x3bd70  (est. sk_lock_collection_relink)
 * Re-link rec into the vspace's live-collection slot (vspace+0x50).
 * Confidence: high */
static void sk_lock_collection_relink(word_t *rec, word_t vspace, word_t a3)
{
    if (*rec != vspace) SK_ABORT("VAS abort");
    FUN_00044be0(vspace, a3);
    if (*(word_t *)(vspace + 0x50) == 0) { *(word_t **)(vspace + 0x50) = rec; return; }
    SK_ABORT("VAS abort");
}

/* FUN_0003be18 @ 0x3be18  (est. sk_lock_collection_alloc_attach)
 * Allocate a lock collection and, on success, attach it to the vspace.
 * Confidence: high */
static word_t sk_lock_collection_alloc_attach(word_t *rec, word_t vspace,
                                              word_t a3, word_t a4,
                                              word_t np, word_t ns, word_t nt, word_t nq)
{
    word_t r = sk_lock_collection_alloc(rec, vspace, np, ns, nt, nq);
    if ((int)r != 0) sk_lock_collection_attach(rec, (word_t *)vspace, a3, a4);
    return r;
}

/* FUN_0003beec @ 0x3beec  (est. sk_lock_collection_enter_checked)
 * Bounds-checked lock entry: requires thread ctx type 0x65b5c8 and span type
 * 0x65b648, an unlocked ctx (ctx+8==0) with no existing collection
 * (ctx+0x130==0), and vspace end within 0x400000000. Stores vspace into
 * ctx+0x130. Returns error code or 0.
 * Confidence: medium */
static sk_pair_t sk_lock_collection_enter_checked(word_t ctx, word_t ctx_type,
                                                  word_t vspace, word_t span_type)
{
    word_t err;
    if (ctx_type == 0x65b5c8 && span_type == 0x65b648) {
        if (*(uint8_t *)(ctx + 8) == 0) {
            if (*(word_t *)(ctx + 0x130) == 0) {
                if (0x400000000 < (word_t)(*(word_t *)(vspace + 0x10) + *(word_t *)(vspace + 8)))
                    SK_ABORT("VAS abort");
                err = 0;
                *(word_t *)(ctx + 0x130) = vspace;
            } else err = 0x2400001;
        } else err = 0x23e0001;
    } else err = 0x23b0001;
    return (sk_pair_t){ err, 0 };
}

/* FUN_0003be88 @ 0x3be88  (est. sk_vspace_lock_enter)
 * Enter the VSpace lock scope: build a collection, attach it, and validate the
 * current thread context before storing the vspace into ctx+0x130.
 * Confidence: medium */
static word_t sk_vspace_lock_enter(word_t *rec, word_t vspace, word_t a3, word_t a4)
{
    if ((sk_lock_collection_alloc(rec, vspace, 1, 0, 0, 0) & 1) != 0)
        return sk_lock_collection_alloc_attach(rec, vspace, a3, a4, 1, 0, 0, 0);
    SK_ABORT("VAS abort");
}

/* FUN_0003bfb8 @ 0x3bfb8  (est. sk_vspace_lock_exit)
 * Leave the VSpace lock scope: the live collection rec must be linked in the
 * vspace's +0x50 slot; clears it, drains any pending buf via FUN_00118194,
 * then frees the collection.
 * Confidence: high */
static void sk_vspace_lock_exit(word_t *rec, word_t vspace)
{
    if (vspace != rec[0]) SK_ABORT("VAS abort");
    if (*(word_t **)(vspace + 0x50) == rec) {
        *(word_t *)(vspace + 0x50) = 0;
        if (FUN_00118194((void *)(vspace + 0x40)) == 0) {
            sk_lock_collection_free(rec);
            return;
        }
        SK_ABORT("VAS abort");
    }
    SK_ABORT("VAS abort");
}

/* FUN_0003c21c @ 0x3c21c  (est. sk_lock_pop_primary) */
static word_t *sk_lock_pop_primary(word_t rec)
{
    uint8_t n = *(uint8_t *)(rec + 0x30);
    if (n == 0) SK_ABORT("VAS abort");
    if (n < 4) {
        *(uint8_t *)(rec + 0x30) = n - 1;
        word_t *tok = *(word_t **)(rec + 8);
        if (tok != (word_t *)0) { *(word_t *)(rec + 8) = *tok; *tok = 0; return tok; }
        SK_ABORT("VAS abort");
    }
    SK_ABORT("VAS abort");
}

/* FUN_0003e640 @ 0x3e640  (est. sk_lock_pop_secondary) */
static word_t *sk_lock_pop_secondary(word_t rec)
{
    uint8_t n = *(uint8_t *)(rec + 0x31);
    if (n == 0) SK_ABORT("VAS abort");
    if (n < 4) {
        *(uint8_t *)(rec + 0x31) = n - 1;
        word_t *tok = *(word_t **)(rec + 0x10);
        if (tok != (word_t *)0) { *(word_t *)(rec + 0x10) = *tok; *tok = 0; return tok; }
        SK_ABORT("VAS abort");
    }
    SK_ABORT("VAS abort");
}

/* FUN_0003b340 @ 0x3b340  (est. sk_lock_pop_tertiary) */
static word_t *sk_lock_pop_tertiary(word_t rec)
{
    uint8_t n = *(uint8_t *)(rec + 0x32);
    if (n == 0) SK_ABORT("VAS abort");
    if (n < 4) {
        *(uint8_t *)(rec + 0x32) = n - 1;
        word_t *tok = *(word_t **)(rec + 0x18);
        if (tok != (word_t *)0) { *(word_t *)(rec + 0x18) = *tok; *tok = 0; return tok; }
        SK_ABORT("VAS abort");
    }
    SK_ABORT("VAS abort");
}

/* FUN_0003b478 @ 0x3b478  (est. sk_lock_pop_quaternary) */
static word_t *sk_lock_pop_quaternary(word_t rec)
{
    uint8_t n = *(uint8_t *)(rec + 0x33);
    if (n == 0) SK_ABORT("VAS abort");
    if (n < 4) {
        *(uint8_t *)(rec + 0x33) = n - 1;
        word_t *tok = *(word_t **)(rec + 0x20);
        if (tok != (word_t *)0) { *(word_t *)(rec + 0x20) = *tok; *tok = 0; return tok; }
        SK_ABORT("VAS abort");
    }
    SK_ABORT("VAS abort");
}

/* FUN_0003b5b0 @ 0x3b5b0  (est. sk_lock_pop_quinary) */
static word_t *sk_lock_pop_quinary(word_t rec)
{
    if (*(word_t *)(rec + 0x38) == 0) SK_ABORT("VAS abort");
    *(word_t *)(rec + 0x38) = *(word_t *)(rec + 0x38) - 1;
    word_t *tok = *(word_t **)(rec + 0x28);
    if (tok != (word_t *)0) { *(word_t *)(rec + 0x28) = *tok; *tok = 0; return tok; }
    SK_ABORT("VAS abort");
}

/* FUN_0003b410 @ 0x3b410  (est. sk_lock_push_tertiary) */
static void sk_lock_push_tertiary(word_t rec, word_t *tok)
{
    if (tok != (word_t *)0) {
        uint8_t n = *(uint8_t *)(rec + 0x32);
        if (2 < n) SK_ABORT("VAS abort");
        *tok = *(word_t *)(rec + 0x18);
        *(word_t **)(rec + 0x18) = tok;
        *(uint8_t *)(rec + 0x32) = n + 1;
    }
}

/* FUN_0003b548 @ 0x3b548  (est. sk_lock_push_quaternary) */
static void sk_lock_push_quaternary(word_t rec, word_t *tok)
{
    if (tok != (word_t *)0) {
        uint8_t n = *(uint8_t *)(rec + 0x33);
        if (2 < n) SK_ABORT("VAS abort");
        *tok = *(word_t *)(rec + 0x20);
        *(word_t **)(rec + 0x20) = tok;
        *(uint8_t *)(rec + 0x33) = n + 1;
    }
}

/* FUN_0003b648 @ 0x3b648  (est. sk_lock_push_quinary) */
static void sk_lock_push_quinary(word_t rec, word_t *tok)
{
    if (tok != (word_t *)0) {
        word_t n = *(word_t *)(rec + 0x38);
        if (n == (word_t)-1) SK_ABORT("VAS abort");
        *tok = *(word_t *)(rec + 0x28);
        *(word_t **)(rec + 0x28) = tok;
        *(word_t *)(rec + 0x38) = n + 1;
    }
}

/* FUN_0003b6ac @ 0x3b6ac  (est. sk_lock_pop_quinary_if) */
static word_t sk_lock_pop_quinary_if(word_t rec)
{
    if (*(word_t *)(rec + 0x38) != 0) return (word_t)sk_lock_pop_quinary(rec);
    return 0;
}

/* FUN_0003b6c0 @ 0x3b6c0  (est. sk_lock_collection_refill) */
static bool sk_lock_collection_refill(word_t rec, word_t vspace,
                                      word_t a3, word_t a4, word_t target)
{
    if (*(word_t *)(vspace + 0x50) != rec) SK_ABORT("VAS abort");
    bool ok;
    if (*(word_t *)(rec + 0x38) < target) {
        *(word_t *)(vspace + 0x50) = 0;
        if (FUN_00118194((void *)(vspace + 0x40)) != 0) SK_ABORT("VAS abort");
        if (*(word_t *)(rec + 0x38) < target) {
            do {
                word_t tok = FUN_0003344c();
                ok = tok != 0;
                if (tok == 0) break;
                sk_lock_push_quinary((word_t)rec, (word_t *)tok);
            } while (*(word_t *)(rec + 0x38) < target);
        } else ok = true;
        FUN_00044c94((word_t)vspace, a3, a4);
        if (*(word_t *)(vspace + 0x50) != 0) SK_ABORT("VAS abort");
        *(word_t *)(vspace + 0x50) = rec;
    } else ok = true;
    return ok;
}


/* ================================================================== *
 * VSpace span tree (FUN_0003dd68, 000405d0, 0003f0dc, 0003f6c8, 0003f804,
 * 0003c2ec, 00040870, 0003c32c, 0003c3bc, 0003c4c0, 0003e5f0, 0003e440,
 * 0003e4c0)
 * ================================================================== */

/* FUN_0003dd68 @ 0x3dd68  (est. sk_vspace_find_region)
 * Walk the VSpace span tree rooted at the current thread's tree root to find
 * the region containing address param_2. Left/right children at +0x58/+0x60
 * (or +0x60/+0x68 for the 0x1000000000-wide sentinel root). Returns the
 * matching region or 0.
 * Confidence: high */
static word_t sk_vspace_find_region(word_t *rec, word_t addr)
{
    if (*rec + 0x2a0 < *rec) SK_FATAL();
    word_t node = FUN_00032cec();
    do {
        if (node == 0) return 0;
        word_t child;
        if (addr < *(word_t *)(node + 8)) child = 0x58;
        else if (addr < *(word_t *)(node + 0x10) + *(word_t *)(node + 8)) {
            if (node + 0xb0 < node) return node;   /* sentinel */
            SK_FATAL();
        } else child = 0x60;
        node = *(word_t *)(node + child);
    } while (true);
}

/* FUN_000405d0 @ 0x405d0  (est. sk_vspace_find_nonempty)
 * Starting at region param_2, walk the tree via sk_vspace_find_region to the
 * first region with a nonzero allocation count (word at +0x20). Returns 0 once
 * the whole 0x1000000000 range is exhausted.
 * Confidence: medium */
static word_t sk_vspace_find_nonempty(word_t rec, word_t region)
{
    while (true) {
        if (region == 0) return 0;
        if (*(int *)(region + 0x20) != 0) break;
        if (*(word_t *)(region + 0x10) + *(word_t *)(region + 8) == 0x1000000000) return 0;
        region = sk_vspace_find_region((word_t *)rec, 0);
    }
    return region;
}

/* FUN_0003f0dc @ 0x3f0dc  (est. sk_span_tree_update_extent)
 * Recompute the subtree extent (max of children extents + own size) for node
 * param_2 and its ancestors down the path from param_1.
 * Confidence: medium */
static void sk_span_tree_update_extent(word_t root, word_t node)
{
    if (root == 0 || node == 0) return;
    word_t child;
    if (*(word_t *)(node + 8) < *(word_t *)(root + 8)) child = 0x58;
    else {
        if (*(word_t *)(node + 8) == *(word_t *)(root + 8)) goto here;
        child = 0x60;
    }
    sk_span_tree_update_extent(*(word_t *)(root + child), node);
here:
    word_t sz = (*(int *)(root + 0x20) == 0) ? *(word_t *)(root + 0x10) : 0;
    word_t m = 0;
    if (*(word_t *)(root + 0x58) != 0) m = *(word_t *)(*(word_t *)(root + 0x58) + 0x68);
    word_t m2 = 0;
    if (*(word_t *)(root + 0x60) != 0) m2 = *(word_t *)(*(word_t *)(root + 0x60) + 0x68);
    if (m <= m2) m = m2;
    if (sz <= m) sz = m;
    *(word_t *)(root + 0x68) = sz;
}

/* FUN_0003f6c8 @ 0x3f6c8  (est. sk_span_tree_remove)
 * Remove region param_2 from the span tree rooted at *param_1, rebalancing
 * (AVL height +0x24, extent +0x68). Returns a rotation indicator (0xfffffffe /
 * 2) or 1 when the root itself was removed. Recurses down the proper child.
 * Confidence: medium */
static word_t sk_span_tree_remove(word_t *root, word_t node)
{
    word_t r = *root;
    if (r == 0) return 0;
    if (r == node) {
        word_t right = *(word_t *)(r + 0x60);
        if (*(word_t *)(r + 0x58) == 0) {
            if (right != 0) { sk_span_tree_rebalance(root, -2); }
        } else {
            if (right != 0 && *(uint8_t *)(*(word_t *)(r + 0x58) + 0x24) < *(uint8_t *)(right + 0x24))
                sk_span_tree_rebalance(root, -2);
            else sk_span_tree_rebalance(root, 2);
        }
    }
    r = *root;
    if (r == node) { *root = 0; return 1; }
    word_t side, slot;
    if (*(word_t *)(node + 8) < *(word_t *)(r + 8)) { side = r + 0x58; slot = r + 0x60; }
    else { side = r + 0x60; slot = r + 0x68; }
    if (slot < side) SK_FATAL();
    word_t ret = sk_span_tree_remove((word_t *)side, node);
    r = *root;
    word_t l = *(word_t *)(r + 0x58);
    word_t lh = (l == 0) ? 0 : *(uint8_t *)(l + 0x24) + 1;
    word_t rr = *(word_t *)(r + 0x60);
    word_t rh = (rr == 0) ? 0 : *(uint8_t *)(rr + 0x24) + 1;
    if (lh <= rh) lh = rh;
    *(uint8_t *)(r + 0x24) = (uint8_t)lh;
    word_t sz = (*(int *)(r + 0x20) == 0) ? *(word_t *)(r + 0x10) : 0;
    word_t m = 0;
    if (l != 0) m = *(word_t *)(l + 0x68);
    word_t m2 = 0;
    if (rr != 0) m2 = *(word_t *)(rr + 0x68);
    if (m <= m2) m = m2;
    if (sz <= m) sz = m;
    *(word_t *)(r + 0x68) = sz;
    return ret;
}

/* FUN_0003f804 @ 0x3f804  (est. sk_span_tree_rebalance)
 * AVL rebalance of the span tree rooted at *param_1 given a balance factor
 * param_2 (2 = right, -2 = left rotation). Rotates the root against its
 * appropriate child, then recomputes heights/extents for both nodes.
 * Confidence: medium */
static void sk_span_tree_rebalance(word_t *root, int balance)
{
    word_t r = *root;
    if (r == 0) return;
    word_t nr = r;
    if (balance < -1) {
        word_t c = *(word_t *)(r + 0x60);
        if (c != 0) {
            *(word_t *)(r + 0x60) = *(word_t *)(c + 0x58);
            if (r + 0xb0 < r) SK_FATAL();
            *(word_t *)(c + 0x58) = r;
            if (c + 0xb0 < c) SK_FATAL();
            *root = c;
            nr = c;
        }
    } else if (1 < balance) {
        word_t c = *(word_t *)(r + 0x58);
        if (c != 0) {
            *(word_t *)(r + 0x58) = *(word_t *)(c + 0x60);
            if (r + 0xb0 < r) SK_FATAL();
            *(word_t *)(c + 0x60) = r;
            if (c + 0xb0 < c) SK_FATAL();
            *root = c;
            nr = c;
        }
    }
    if (!(r <= r + 0xb0)) SK_FATAL();
    word_t l = *(word_t *)(r + 0x58);
    word_t lh = (l == 0) ? 0 : *(uint8_t *)(l + 0x24) + 1;
    word_t rr = *(word_t *)(r + 0x60);
    word_t rh = (rr == 0) ? 0 : *(uint8_t *)(rr + 0x24) + 1;
    if (lh <= rh) lh = rh;
    *(uint8_t *)(r + 0x24) = (uint8_t)lh;
    word_t m = 0;
    if (l != 0) m = *(word_t *)(l + 0x68);
    word_t m2 = 0;
    if (rr != 0) m2 = *(word_t *)(rr + 0x68);
    if (m <= m2) m = m2;
    word_t sz = (*(int *)(r + 0x20) == 0) ? *(word_t *)(r + 0x10) : 0;
    if (sz <= m) sz = m;
    *(word_t *)(r + 0x68) = sz;
    word_t nl = *(word_t *)(nr + 0x58);
    word_t nlh = (nl == 0) ? 0 : *(uint8_t *)(nl + 0x24) + 1;
    word_t nrr = *(word_t *)(nr + 0x60);
    word_t nrh = (nrr == 0) ? 0 : *(uint8_t *)(nrr + 0x24) + 1;
    if (nlh <= nrh) nlh = nrh;
    *(uint8_t *)(nr + 0x24) = (uint8_t)nlh;
    word_t nm = 0;
    if (nl != 0) nm = *(word_t *)(nl + 0x68);
    word_t nm2 = 0;
    if (nrr != 0) nm2 = *(word_t *)(nrr + 0x68);
    if (nm <= nm2) nm = nm2;
    word_t nsz = (*(int *)(nr + 0x20) == 0) ? *(word_t *)(nr + 0x10) : 0;
    if (nsz <= nm) nsz = nm;
    *(word_t *)(nr + 0x68) = nsz;
}

/* FUN_00040870 @ 0x40870  (est. sk_span_tree_insert)
 * Insert region param_2 into the tree rooted at *param_1 (recursive), then
 * adjust heights/extents and rebalance along the path.
 * Confidence: medium */
static void sk_span_tree_insert(word_t *root, word_t node)
{
    word_t r = *root;
    if (r == 0) {
        *root = node;
        word_t sz = (*(int *)(node + 0x20) == 0) ? *(word_t *)(node + 0x10) : 0;
        word_t m = 0;
        if (*(word_t *)(node + 0x58) != 0) m = *(word_t *)(*(word_t *)(node + 0x58) + 0x68);
        word_t m2 = 0;
        if (*(word_t *)(node + 0x60) != 0) m2 = *(word_t *)(*(word_t *)(node + 0x60) + 0x68);
        if (m <= m2) m = m2;
        if (sz <= m) sz = m;
        *(word_t *)(node + 0x68) = sz;
        return;
    }
    word_t child;
    if (*(word_t *)(node + 8) < *(word_t *)(r + 8)) {
        if (r + 0xb0 < r || r + 0x60 < r + 0x58) SK_FATAL();
        sk_span_tree_insert((word_t *)(r + 0x58), node);
        child = *(word_t *)(r + 0x58);
    } else {
        if (r + 0xb0 < r || r + 0x68 < r + 0x60) SK_FATAL();
        sk_span_tree_insert((word_t *)(r + 0x60), node);
        child = *(word_t *)(r + 0x60);
    }
    if (*(uint8_t *)(r + 0x24) <= *(uint8_t *)(child + 0x24))
        *(uint8_t *)(r + 0x24) = *(uint8_t *)(child + 0x24) + 1;
    int bal = 0;
    if (*(word_t *)(r + 0x58) != 0) bal = *(uint8_t *)(*(word_t *)(r + 0x58) + 0x24) + 1;
    uint32_t bal2 = 0;
    if (*(word_t *)(r + 0x60) != 0) bal2 = ~(uint32_t)*(uint8_t *)(*(word_t *)(r + 0x60) + 0x24);
    sk_span_tree_rebalance(root, bal2 + bal);
}

/* FUN_0003c2ec @ 0x3c2ec  (est. sk_span_tree_insert_caller) */
static void sk_span_tree_insert_caller(word_t *rec, word_t region)
{
    if (*rec <= *rec + 0x2a0) {
        word_t root = FUN_00032cec();
        sk_span_tree_insert((word_t *)root, region);
        return;
    }
    SK_FATAL();
}

/* FUN_0003c32c @ 0x3c32c  (est. sk_span_tree_destroy)
 * Recursively destroy the span tree rooted at *param_1: frees children, tears
 * down leaf buffers, releases buf cookies and vspace links, returns nodes to
 * the allocator. Sets *param_1 = 0.
 * Confidence: medium */
static void sk_span_tree_destroy(word_t *root)
{
    word_t node = *root;
    if (node != 0) {
        if (*(word_t *)(node + 0x58) != 0) {
            if ((word_t *)(node + 0x60) < (word_t *)(node + 0x58)) SK_FATAL();
            sk_span_tree_destroy((word_t *)(node + 0x58));
        }
        if (*(word_t *)(node + 0x60) != 0) {
            if ((word_t *)(node + 0x68) < (word_t *)(node + 0x60)) SK_FATAL();
            sk_span_tree_destroy((word_t *)(node + 0x60));
        }
        if (*(word_t *)(node + 0x70) != 0) {
            FUN_00031594(*(word_t *)(node + 0x50), 0);
            *(word_t *)(node + 0x70) = 0;
        }
        sk_span_teardown_node(node);
        *(word_t *)(node + 0x50) = 0;
        FUN_00033148(node);
        *root = 0;
    }
}

/* FUN_0003c3bc @ 0x3c3bc  (est. sk_span_teardown_node)
 * Tear down a span node's page-table buffers: if the owner is a two-stage mmu
 * (bit 0 at owner+0x290), walk and invalidate intermediate level entries via
 * FUN_000304c4; then free the +0xa0 and +0x78 buffers.
 * Confidence: low (no string anchor) */
static void sk_span_teardown_node(word_t node)
{
    word_t owner = *(word_t *)(node + 0x50);
    word_t saved = DAT_004bc1f0;
    if ((*(uint8_t *)(owner + 0x290) & 1) != 0) {
        word_t dom = FUN_00032cd0(0);
        word_t state[3] = {0,0,0};
        FUN_000363ac(state, *(word_t *)(node + 0xa0), 0);
        word_t v = FUN_0003667c(state);
        if ((v & 3) != 0) {
            if (dom + 0xd0 < dom) SK_FATAL();
            do {
                word_t slot = owner + 0x208;
                if (owner + 0x290U < slot) SK_FATAL();
                FUN_000304c4(slot, v >> 0x1c,
                    (v & 0xfffffc0) * 0x100 + *(word_t *)(dom + 0x28) + -0x4000);
                v = FUN_0003667c(state);
            } while ((v & 3) != 0);
        }
        FUN_00036920(*(word_t *)(node + 0xa0), 0);
        *(word_t *)(node + 0xa0) = DAT_004bc1f0;
    }
    FUN_00036920(*(word_t *)(node + 0x78), (word_t)FUN_004b23d8);
    *(word_t *)(node + 0x78) = saved;
}

/* FUN_0003c4c0 @ 0x3c4c0  (est. sk_span_is_allocated) */
static bool sk_span_is_allocated(word_t vspace, word_t vt, word_t region, word_t st)
{
    if (vt == 0x65b5c8 && st == 0x65b648 && vspace != 0 && region != 0 &&
        *(word_t *)(region + 0x50) == vspace)
        return *(int *)(region + 0x20) != 0;
    return false;
}

/* FUN_0003e5f0 @ 0x3e5f0  (est. sk_vspace_release_buf)
 * Clear a buffer's "allocated" flag (bit 0x8000000) and return it to the
 * 0x18-byte slot allocator. Returns 0 or 0x113a0001 if null.
 * Confidence: medium */
static seL4_Word sk_vspace_release_buf(word_t *slot)
{
    word_t b = *slot;
    if (b != 0) {
        *(uint32_t *)(b + 0x20) = *(uint32_t *)(b + 0x20) & 0xf7ffffff;
        FUN_00117f8c(slot, 0x18, 0xffffffffffffffff);
        return 0;
    }
    return 0x113a0001;
}

/* FUN_0003e440 @ 0x3e440  (est. sk_vspace_grab_buf)
 * Grab a VSpace buffer for region param_2: requires a live page table and the
 * "has mapping" bit (1<<0x1a) with nonzero size. Sets "in-use" bit, records
 * region/spanmap cookie in param_1[0..2]. Returns 0 / 6 / 0x10f70001.
 * Confidence: medium */
static seL4_Word sk_vspace_grab_buf(word_t *out, word_t region)
{
    uint32_t f = *(uint32_t *)(region + 0x20);
    if (f == 0) return 6;
    if (((f >> 0x1a) & 1) != 0 && *(word_t *)(region + 0x10) != 0) {
        *(uint32_t *)(region + 0x20) = f | 0x8000000;
        out[0] = region;
        out[1] = *(word_t *)(region + 0x78);
        out[2] = FUN_000368f8(*(word_t *)(region + 0x78)) & 0xffffffff;
        return 0;
    }
    return 0x10f70001;
}

/* FUN_0003e4c0 @ 0x3e4c0  (est. sk_vspace_buf_validate)
 * Validate a grabbed buffer and fetch the pte for offset param_2. Verifies the
 * spanmap cookie generation still matches; on success copies the spanmap entry
 * into param_3. On mismatch (preemption) falls back to the free list and tears
 * the buffer down (returns 0x113a0001 on empty).
 * Confidence: low (no strong identity) */
static seL4_Word sk_vspace_buf_validate(word_t *hint, word_t off, word_t *pte)
{
    word_t region = *hint;
    if (region == 0) return 0x11100001;
    if (((*(uint8_t *)(region + 0x23) >> 3) & 1) == 0) { FUN_004b349c(); SK_FATAL(); }
    if (*(word_t *)(region + 0x10) <= (off & 0xffffffffffffc000)) return 0x111c0001;
    word_t d = hint[1] ^ *(word_t *)(region + 0x78);
    if ((d >> 0x1c) == 0) {
        if (0x3f < d || (d & 3) != 0 || *(word_t *)(region + 0x78) != hint[1]) goto stale;
        word_t cookie = FUN_000368f8(*(word_t *)(region + 0x78));
        if (hint[2] == (cookie & 0xffffffff)) {
            word_t dom = FUN_00032cd0(*(word_t *)(region + 0x50));
            word_t l[5] = {0,0,0,0,0};
            if (dom + 0xd0 < dom) SK_FATAL();
            FUN_00035ba0(l, *(word_t *)(region + 0x78),
                (int)((*(word_t *)(region + 8) + (off & 0xffffffffffffc000)
                       - *(word_t *)(dom + 0x28)) >> 0xe) + 1);
            if ((uint8_t)l[1] != 1) { *pte = l[0]; return 0; }
            goto stale;
        }
    } else FUN_004b339c();
stale:
    FUN_004b343c();
    word_t *list = (word_t *)FUN_004b3464();
    word_t b = *list;
    if (b == 0) return 0x113a0001;
    *(uint32_t *)(b + 0x20) = *(uint32_t *)(b + 0x20) & 0xf7ffffff;
    FUN_00117f8c(list, 0x18, 0xffffffffffffffff);
    return 0;
}


/* ================================================================== *
 * Region creation / span split+merge (FUN_0003c56c, 0003e73c, 0003ee4c,
 * 0003f41c, 0003eab4, 0003ed4c, 0003e984, 0003ea28, 0003e918, 0003f324,
 * 0003b258, 0003e308, 0003e14c, 0003d2b8, 0003d330, 0003d438, 0003d904,
 * 0003d9d4, 0003da18, 0003df84, 0003a550, 0003a4a0, 0003a1e0)
 * ================================================================== */

/* FUN_0003ea28 @ 0x3ea28  (est. sk_span_encode_meta)
 * Encode a span node's metadata word into its buffer (+0x70): a packed word
 * combining the node's type + flag bits from +0x20 with the "slot" encoding
 * (page-table level), written as a record at the buffer.
 * Confidence: medium */
static void sk_span_encode_meta(char *node)
{
    word_t *buf = *(word_t **)(node + 0x70);
    word_t base = *(word_t *)(node + 8);
    uint8_t rtype = node[0x18];
    uint32_t f = *(uint32_t *)(node + 0x20);
    uint32_t meta = (*node == 4) ? 8 : 0;
    meta = (f >> 0x11 & 4) | (f >> 3 & 3) | (f >> 6 & 0x40000) | meta;
    if (2 < rtype - 4) {
        if (rtype == 0x11) meta |= 0x20000;
        else if (rtype != 1) goto done;
    }
    meta |= 0x10000;
done:
    buf[1] = *(word_t *)(node + 0x10);
    *buf = base;
    *(uint8_t *)(buf + 3) = 0;
    buf[2] = 0;
    *(uint8_t *)((word_t)buf + 0x19) = rtype;
    *(uint16_t *)((word_t)buf + 0x1a) = 0;
    *(uint32_t *)((word_t)buf + 0x1c) = meta;
    *(uint32_t *)(buf + 3) = 1;
}

/* FUN_0003e918 @ 0x3e918  (est. sk_rand_mod)
 * Return a pseudo-random value in [0, param_1), drawing 8 random bytes via
 * FUN_00116c78 and discarding values that introduce modulo bias.
 * Confidence: medium */
static word_t sk_rand_mod(word_t n)
{
    if (n < 2) return 0;
    word_t rem;
    do { rem = 0; FUN_00116c78(&rem, 8); }
    while (rem < (word_t)-(long)n);
    return rem % n;
}

/* FUN_0003eab4 @ 0x3eab4  (est. sk_span_alloc_range)
 * Allocate a range of span nodes for the vspace state param_1: find a free
 * aligned window in [st+0x30, st+0x40) big enough for region param_2's size,
 * honoring base alignment at st+0x48, and update the next-free pointer.
 * Returns 0 on success or 1 if no window fits.
 * Confidence: low (stateful allocator) */
static word_t sk_span_alloc_range(word_t st, word_t region)
{
    if (*(int *)(region + 0x20) != 0) { FUN_004b34d4(); SK_ABORT("VAS abort"); }
    word_t size = *(word_t *)(st + 0x30);
    if (size <= *(word_t *)(region + 0x10)) {
        word_t rbase = *(word_t *)(region + 8);
        word_t lo = *(word_t *)(st + 0x38);
        word_t rend = rbase + *(word_t *)(region + 0x10);
        if (rend < lo) SK_ABORT("VAS abort");
        word_t start = (rbase <= lo) ? lo : rbase;
        word_t end = (*(word_t *)(st + 0x40) <= rend) ? *(word_t *)(st + 0x40) : rend;
        if (end < start || end - start < size) SK_ABORT("VAS abort");
        word_t align = *(uint8_t *)(st + 0x48);
        word_t mask = (word_t)1 << (align & 0x3f);
        word_t add = 0;
        if ((mask - 1U & start) != 0) add = mask;
        word_t top = ((word_t)-1 << (align & 0x3f)) & (end - size);
        word_t s = add + (start & -mask);
        if (s <= top) {
            if (s < rbase || rend < s + size || rend < top + size) SK_ABORT("VAS abort");
            word_t n = (top - s >> (align & 0x3f)) + 1;
            word_t cookie = *(word_t *)(*(word_t *)(st + 0x20) + 8);
            if (*(uint8_t *)(cookie + 0x18) == 1) {
                word_t fn = *(word_t *)(*(word_t *)(st + 0x28) + 8);
                word_t have = *(word_t *)(fn + 0x18);
                if (have < n) {
                    if (*(uint8_t *)(cookie + 0x19) == 1) *(word_t *)(fn + 0x18) = n - have;
                    *(word_t *)(cookie + 0x38) = region;
                    *(word_t *)(*(word_t *)(st + 0x20) + 0x40) =
                        (*(word_t *)(*(word_t *)(st + 0x28) + 0x18) << (align & 0x3f)) + s;
                    return 0;
                }
                *(word_t *)(fn + 0x18) = have - n;
            } else if (*(uint8_t *)(cookie + 0x18) == 0) {
                *(word_t *)(cookie + 0x30) = *(word_t *)(cookie + 0x30) + n;
            }
        }
        return 1;
    }
    SK_ABORT("VAS abort");
}

/* FUN_0003ed4c @ 0x3ed4c  (est. sk_span_tree_find_free)
 * Recursively search the span tree from node param_1 for a free region of at
 * least param_4 bytes within [param_2, param_3), pruning via subtree extents
 * and invoking callback param_5+0x10 per candidate. Returns 0 when a region
 * satisfies the size constraint.
 * Confidence: low */
static word_t sk_span_tree_find_free(word_t node, word_t lo, word_t hi,
                                     word_t min_sz, word_t cb)
{
    if (node == 0) return 1;
    if (min_sz <= *(word_t *)(node + 0x68)) {
        word_t rbase = *(word_t *)(node + 8);
        if (lo < rbase) {
            word_t r = sk_span_tree_find_free(*(word_t *)(node + 0x58), lo, hi, min_sz, cb);
            if ((int)r == 0) return r;
            rbase = *(word_t *)(node + 8);
        }
        word_t s = (rbase <= lo) ? lo : rbase;
        word_t e = *(word_t *)(node + 0x10) + rbase;
        word_t top = (hi <= e) ? hi : e;
        word_t sz = (s <= top) ? top - s : 0;
        if (*(int *)(node + 0x20) == 0 && min_sz <= sz) {
            word_t r = (*(word_t (**)(word_t, word_t))(cb + 0x10))(cb, node);
            if ((int)r == 0) return r;
            e = *(word_t *)(node + 0x10) + *(word_t *)(node + 8);
        }
        if (e < hi) {
            word_t r = sk_span_tree_find_free(*(word_t *)(node + 0x60), lo, hi, min_sz, cb);
            if ((int)r == 0) return r;
        }
    }
    return 1;
}

/* FUN_0003e984 @ 0x3e984  (est. sk_span_merge_check)
 * Validate region param_3 is free before a merge. Panics on error.
 * Confidence: low */
static void sk_span_merge_check(word_t a1, word_t a2, word_t region)
{
    if (*(int *)(region + 0x20) != 0) SK_ABORT("VAS abort");
    word_t err = sk_vspace_span_merge((word_t*)&a1, a2, (void*)0, (void*)0, NULL, NULL).lo;
    if ((err & 0xff) == 0) return;
    SK_ABORT("VAS abort");
}

/* FUN_0003f41c @ 0x3f41c  (est. sk_vspace_span_merge)
 * Merge adjacent span region param_4 into param_3 (same vspace, flags and
 * contiguous). Absorbs param_4's size, migrates its buf cookie, relinks parent
 * buffers, and removes param_4 from the tree. On success *param_5=param_3,
 * *param_6=param_4.
 * Confidence: medium */
static sk_pair_t sk_vspace_span_merge(word_t *rec, word_t vspace, void *r3,
                                      void *r4, word_t *oa, word_t *ob)
{
    word_t p3 = (word_t)r3, p4 = (word_t)r4;
    word_t end4 = *(word_t *)(p4 + 8);
    if (end4 < *(word_t *)(p3 + 8)) SK_ABORT("VAS abort");
    word_t err;
    if (*(word_t *)(p3 + 0x50) == *(word_t *)(p4 + 0x50)) {
        if (*(uint32_t *)(p3 + 0x20) == *(uint32_t *)(p4 + 0x20)) {
            if ((*(uint32_t *)(p3 + 0x20) & 0xd000800) == 0) {
                if (end4 == 0) err = 0x75c0001;
                else {
                    err = 0;
                    if (*(word_t *)(p3 + 0x10) + *(word_t *)(p3 + 8) != end4) err = 0x75d0001;
                }
            } else err = 0x75b0001;
        } else err = 0x75a0001;
    } else err = 0x7590001;
    if ((err & 0xff) == 0) {
        uint32_t f = *(uint32_t *)(p3 + 0x20);
        if ((f >> 0x10 & 1) != 0) FUN_000458a0(rec, vspace, r3, r4);
        *(word_t *)(p3 + 0x10) = *(word_t *)(p3 + 0x10) + *(word_t *)(p4 + 0x10);
        if (f == 0) {
            sk_span_tree_update_extent(*(word_t *)(*rec + 0x58), p3);
        } else {
            word_t *b3 = *(word_t **)(p3 + 0x70);
            word_t *b4 = *(word_t **)(p4 + 0x70);
            word_t nb = (word_t)sk_lock_pop_secondary(*rec);
            *(word_t *)(p3 + 0x70) = nb;
            *(word_t *)(p4 + 0x70) = 0;
            sk_span_encode_meta((char *)p3);
            if (b3 + 4 < b3) SK_FATAL();
            *(uint8_t *)(b3 + 3) = 0;
            uint8_t c = *(uint8_t *)((word_t)rec + 0x31);
            if (2 < c) SK_ABORT("VAS abort");
            *b3 = rec[2]; rec[2] = (word_t)b3;
            *(uint8_t *)((word_t)rec + 0x31) = c + 1;
            if (b4 + 4 < b4) SK_FATAL();
            *(uint8_t *)(b4 + 3) = 0;
            c = *(uint8_t *)((word_t)rec + 0x31);
            if (2 < c) SK_ABORT("VAS abort");
            *b4 = rec[2]; rec[2] = (word_t)b4;
            *(uint8_t *)((word_t)rec + 0x31) = c + 1;
        }
        if (*rec + 0x2a0 < *rec) SK_FATAL();
        word_t root = FUN_00032cec();
        if ((sk_span_tree_remove((word_t *)root, p4) & 1) == 0) SK_ABORT("VAS abort");
        err = 0;
        *oa = p3; *ob = p4;
    }
    return (sk_pair_t){ err, 0 };
}

/* FUN_0003f324 @ 0x3f324  (est. sk_span_merge_caller)
 * Merge two adjacent regions then push the leftover into the collection.
 * Returns the merged region pointer; panics on failure.
 * Confidence: low */
static word_t sk_span_merge_caller(word_t *rec, word_t vspace, word_t r3, word_t r4)
{
    if (*(int *)(r3 + 0x20) != 0 || *(int *)(r4 + 0x20) != 0) SK_ABORT("VAS abort");
    word_t oa = 0, ob = 0;
    word_t err = sk_vspace_span_merge(rec, vspace, (void *)r3, (void *)r4, &oa, &ob).lo;
    if ((err & 0xff) == 0) { sk_lock_push_quinary((word_t)rec, (word_t *)ob); return oa; }
    SK_ABORT("VAS abort");
}

/* FUN_0003ee4c @ 0x3ee4c  (est. sk_vspace_span_split)
 * Split span region param_3 into two, cutting off a leading window of
 * param_4 bytes. Validates flags, allocates a new span node (param_5/param_6
 * receive the two regions), relinks the vspace buffer list, and returns both.
 * Confidence: low (large stateful split) */
static sk_pair_t sk_vspace_span_split(void *rec, word_t vspace, void *r3,
                                      word_t cut, word_t *o1, word_t *o2)
{
    word_t *p3 = (word_t *)r3;
    uint32_t f = *(uint32_t *)((word_t)p3 + 4);
    word_t perr;
    if ((f & 0xd000800) == 0) {
        word_t err = (cut != 0) ? 0 : 0x7fb0001;
        perr = (cut < (word_t)p3[2]) ? err : 0x7f80001;
    } else perr = 0x7f60001;
    if ((perr & 0xff) != 0) return (sk_pair_t){ perr, 0 };
    word_t *nb = (word_t *)sk_lock_pop_primary((word_t)rec);
    word_t *nb2 = nb + 0x16;
    uint32_t f2 = *(uint32_t *)(p3 + 4);
    if ((f2 >> 0x10 & 1) != 0) {
        if (nb2 < nb) SK_FATAL();
        FUN_00045908(rec, vspace, r3, cut, nb);
        f2 = *(uint32_t *)(p3 + 4);
    }
    word_t *oldbuf = (word_t *)p3[0xe];
    word_t head, tail, headsz, meta;
    if (f2 == 0) { head = 0; tail = 0; headsz = 0x20; meta = 0; }
    else {
        head = (word_t)sk_lock_pop_secondary((word_t)rec);
        headsz = head + 0x20;
        if (*(int *)(p3 + 4) == 0) { tail = 0; meta = 0; }
        else {
            tail = (word_t)sk_lock_pop_secondary((word_t)rec);
            if (tail + 0x20 < tail) SK_FATAL();
            meta = *(uint32_t *)(p3 + 4);
        }
    }
    nb[0xe] = tail;
    *(uint32_t *)(nb + 4) = meta;
    word_t a = *p3, b = p3[3], c = p3[2];
    nb[1] = p3[1]; *nb = a; nb[3] = b; nb[2] = c;
    nb[1] = nb[1] + cut;
    nb[2] = nb[2] - cut;
    nb[10] = p3[10];
    p3[2] = cut;
    if (head <= headsz) {
        p3[0xe] = head;
        if (*(int *)(p3 + 4) != 0) {
            sk_span_encode_meta((char *)p3);
            if (nb2 < nb) SK_FATAL();
            sk_span_encode_meta((char *)nb);
            if (oldbuf + 4 < oldbuf) SK_FATAL();
            *(uint8_t *)(oldbuf + 3) = 0;
            uint8_t cc = *(uint8_t *)((word_t)rec + 0x31);
            if (2 < cc) SK_ABORT("VAS abort");
            *oldbuf = rec[2]; rec[2] = (word_t)oldbuf;
            *(uint8_t *)((word_t)rec + 0x31) = cc + 1;
            if ((*(uint32_t *)(p3 + 4) >> 6 & 1) != 0) {
                word_t *hi = p3, *hiend = p3 + 0x16;
                word_t *lo = nb, *loend = nb2;
                if ((*(uint32_t *)(p3 + 4) >> 7 & 1) == 0) { hi = nb; hiend = nb2; lo = p3; loend = p3 + 0x16; }
                if (loend < hi + 0x16) SK_FATAL();
                word_t top = p3[9];
                word_t losz = lo[2];
                word_t gap = top - losz;
                if (top < losz || gap == 0) { lo[9] = top; if (hiend < hi + 0x16) SK_FATAL(); gap = 0; }
                else { lo[9] = losz; if (hiend < hi + 0x16) SK_FATAL(); }
                hi[9] = gap;
            }
        }
        if (nb <= nb2) {
            sk_span_tree_insert_caller((word_t *)rec, (word_t)nb);
            *o1 = (word_t)p3; *o2 = (word_t)nb;
            return (sk_pair_t){ 0, 0 };
        }
    }
    SK_FATAL();
}

/* FUN_0003e73c @ 0x3e73c  (est. sk_spanmap_walk)
 * Walk the spanmap for a region described by param_3 (addr/size/type words),
 * computing the aligned start, page count and type. mode param_4[0] is 0
 * (forward) or 1 (reverse). Runs the walk callback FUN_0003eab4 over the tree
 * and returns the 5-word result in param_1.
 * Confidence: low */
static void sk_spanmap_walk(word_t *out, word_t *rec, word_t region, word_t *mode)
{
    word_t local[9] = {0,0,0,0,0,0,0,0,0};
    local[0] = *mode; local[1] = mode[1]; local[2] = mode[2]; local[3] = mode[3]; local[4] = mode[4];
    uint8_t align = *(uint8_t *)(region + 0x1a);
    word_t size = *(word_t *)(region + 0x10);
    word_t add = (size & 0x3fff) ? 0x4000 : 0;
    word_t mask = (word_t)1 << (*(uint8_t *)(region + 0x1b) & 0x3f);
    if (*(uint8_t *)(region + 0x1b) - 0x40 < 0xffffffc1) mask = (word_t)-1;
    word_t lo = local[0] & 0xff;
    local[6] = local[1];
    if ((int8_t)local[0] == 0) { /* forward */ }
    else if ((int8_t)local[0] == 1) { local[4] = 0; lo = (word_t)-1; }
    else FUN_0005b190(0, "unsupported walkinfo mode");
    word_t end = add + (size & 0xffffffffffffc000);
    word_t cookie = *(uint8_t *)(region + 0x1c);
    word_t cmask = (word_t)1 << (cookie & 0x3f);
    if (0x3f < cookie) cmask = (word_t)-1;
    word_t cval = (cookie != 0) ? cmask : 0;
    if ((int8_t)local[2] == 1 && cval <= *(word_t *)(region + 8)) cval = *(word_t *)(region + 8);
    if (align < 0xf) align = 0xe;
    word_t cb[8] = { 0x6ad3a8, DAT_004bb180, sk_span_alloc_range, 0x65b6e0, 0, end, cval, mask };
    if (*rec + 0x2a0 < *rec) SK_FATAL();
    word_t root = FUN_00032cec();
    sk_span_tree_find_free(*(word_t *)root, cval, mask, end, (word_t)cb);
    out[1] = local[4]; out[0] = local[3]; out[3] = local[6]; out[2] = local[5];
    out[5] = local[8]; out[4] = local[7];
}

/* FUN_0003c56c @ 0x3c56c  (est. sk_vspace_region_create)
 * Create a new span region in vspace param_1 covering [base, base+size) with
 * the attributes packed in param_2, parsed from descriptor param_3. Validates
 * descriptor flags against the region type, computes the aligned window,
 * allocates a span node, splits free spans, builds page-table buffers, encodes
 * region meta, links into the span tree + vspace LRU, and walks/allocates the
 * page-table levels. *param_4 receives the created region (type 0x65b648).
 * Confidence: low (large stateful factory) */
static sk_pair_t sk_vspace_region_create(word_t vspace, uint32_t rf, char *desc,
                                         word_t *out_region, uint32_t *out_flags,
                                         word_t *out_buf)
{
    word_t local[9]; int i;
    for (i = 0; i < 9; i++) local[i] = 0;
    sk_pair_t result = { 0, 0 };
    word_t err;
    if ((sk_lock_collection_alloc(local, vspace, 2, 1, rf >> 0x10 & 1, 0) & 1) == 0) {
        result.lo = 0x49b0002; goto out;
    }
    sk_lock_collection_attach((word_t *)local, (word_t *)vspace, 0, 0);
    char rtype = *desc;
    word_t base = *(word_t *)(desc + 8);
    word_t size = *(word_t *)(desc + 0x10);
    char tl = desc[0x18], th = desc[0x19];
    uint8_t align = desc[0x1a], align_hi = desc[0x1b];
    uint32_t c4 = *(uint32_t *)(desc + 0x1c);
    word_t type_idx = FUN_000559b8(rtype);
    word_t *node = 0;
    err = 0;
    if (type_idx == 0xe) {
        if ((rf & 0xc0) == 0x80) { err = 0x3cd0001; }
        else if (((rf >> 9) & 1) == 0 || (rf & 0x400010) == 0) {
            if (((rf ^ 0xffffffff) & 0x60) == 0) err = 0x3d10001;
            else if (((rf ^ 0xffffffff) & 0x81000) == 0) err = 0x3d30001;
            else if ((rf >> 0xc & 1) == 0) {
                if (((rf >> 0x13 & 1) == 0) || (rf & 0x108f0) == 0x10800) {
                    if (((rf >> 0x10 & 1) == 0) && (rf & 0x2300000) != 0) err = 0x3e60001;
                    else if (align < 0x24) {
                        if ((rf & 1) == 0) {
                            if (align_hi == 0 || 0xffffffcd < align_hi - 0x40) {
                                word_t sub = sk_region_type_slot(tl);
                                if (sub == 0) err = 0x3f60001;
                                else if (*(word_t *)(desc + 0x10) == 0) err = 0x3f80001;
                                else if ((rf >> 0x16 & 1) == 0) {
                                    word_t add2 = (size & 0x3fff) ? 0x4000 : 0;
                                    word_t win = add2 + (size & 0xffffffffffffc000);
                                    word_t win_lo, win_hi;
                                    if ((rf & 1) == 0) {
                                        if (th == 0) {
                                            /* direct alloc: aligned base */
                                            word_t a = (base >> 0xe) << 0xe;
                                            win_lo = a;
                                            win_hi = a + win;
                                        } else {
                                            /* type-specific walk (collapsed) */
                                            win_lo = base;
                                            win_hi = base + win;
                                        }
                                    } else { win_lo = base & 0xffffffffffffc000; win_hi = win_lo + win; }
                                    /* find covering span */
                                    word_t found = sk_vspace_find_region(local, win_lo);
                                    if (found != 0) {
                                        if (*(int *)(found + 0x20) == 0) {
                                            /* carve the exact window */
                                            if (win_lo != *(word_t *)(found + 8))
                                                sk_span_split_simple(found, win_lo);
                                            if (win_hi < *(word_t *)(found + 0x10))
                                                sk_span_split_simple(found, win_hi);
                                            node = (word_t *)found;
                                        } else { node = 0; err = 0x44c0003; }
                                    } else err = 0x44c0003;
                                    if (node != 0 && err == 0) {
                                        int k;
                                        for (k = 0; k < 0x30; k++) ((char *)node)[k+0x28] = 0;
                                        *node = rtype;
                                        *(uint32_t *)(node + 4) = *(uint32_t *)(desc + 1) & 0xffff;
                                        *(word_t *)(node + 8) = win_lo;
                                        *(word_t *)(node + 0x10) = win_hi;
                                        for (k = 0; k < 8; k++) ((char *)node)[k+0x48] = 0;
                                        *(word_t *)(node + 0x70) =
                                            (word_t)sk_lock_pop_secondary((word_t)local);
                                        sk_span_encode_meta((char *)node);
                                        sk_span_tree_insert_caller((word_t *)local, (word_t)node);
                                        if ((rf >> 0x10 & 1) != 0)
                                            FUN_00045728(local, vspace, win_lo, win_hi, rf >> 0x17 & 4, node);
                                    }
                                } else err = 0x3e20001;
                            } else err = 0x3f30001;
                        } else if (th == 0) {
                            err = ((base & ((word_t)-1 << (align & 0x3f) ^ (word_t)-1)) != 0)
                                ? 0x3ee0001 : 0x3ec0001;
                        } else err = 0x3ec0001;
                    } else err = 0x3e90001;
                } else err = 0x3e20001;
            } else if ((rf & 0x8e0) == 0x800) {
                err = (((rf ^ 0xffffffff) & 0x10008) != 0) ? 0x3dc0001 : 0x3dc0001;
            } else err = 0x3d70001;
        } else err = 0x3cf0001;
    } else err = 0x3cb0001;
out:
    sk_vspace_lock_exit(local, vspace);
    if ((err & 0xff) == 0 && node != 0) {
        if ((*(uint32_t *)(node + 0x20) & 0x2010000) == 0x10000)
            sk_span_prefetch_pages((char *)node, 0, *(word_t *)(node + 0x10));
        if (FUN_00118148((void *)(node + 0x80), 0) != 0) SK_ABORT("VAS abort");
        *(word_t *)(node + 0x78) = FUN_00035b98();
        *(word_t *)(node + 0xa0) = FUN_00035b98();
        if ((rf & 1) != 0) {
            if (FUN_00118164((void *)(node + 0x80)) != 0) SK_ABORT("VAS abort");
            word_t b = *(word_t *)(node + 8), sz = *(word_t *)(node + 0x10);
            word_t dom = FUN_00032cd0(vspace);
            *(word_t *)(node + 0x78) = FUN_00043c74(*(word_t *)(node + 0x78), b, sz, dom);
            if (FUN_00118194((void *)(node + 0x80)) != 0) SK_ABORT("VAS abort");
        }
        if (FUN_00045cb8((void *)node) != 0) {
            word_t *list = (word_t *)(vspace + 0x1f0);
            word_t *tail = (word_t *)(vspace + 0x200);
            if (FUN_00118164(list) != 0) SK_ABORT("VAS abort");
            word_t old = *tail;
            *(word_t *)(node + 0x90) = old;
            if (old != 0) *(word_t **)(old + 0x98) = (word_t *)(node + 0x90);
            *(word_t **)(vspace + 0x200) = (word_t *)node;
            *(word_t **)(node + 0x98) = tail;
            if (FUN_00118194(list) != 0) SK_ABORT("VAS abort");
        }
        if ((rf >> 0x1a & 1) != 0) sk_span_prefetch_pages((char *)node, 0, *(word_t *)(node + 0x10));
        if ((rf >> 5 & 1) != 0) {
            word_t off = 0, len = *(word_t *)(node + 0x10);
            if ((sk_span_map_check(node, &off, &len).lo & 0xff) != 0) {
                if ((sk_span_destroy_impl(&node).lo & 0xff) != 0) SK_FATAL();
                goto out;
            }
        }
        if (out_flags) *out_flags = *(uint32_t *)(node + 0x20);
        if (out_buf) {
            word_t a = *(word_t *)node, bb = *(word_t *)(node + 0x18), cc = *(word_t *)(node + 0x10);
            out_buf[1] = *(word_t *)(node + 8); out_buf[0] = a;
            out_buf[3] = bb; out_buf[2] = cc;
        }
        result.lo = 0;
        *out_region = (word_t)node;
        out_region[1] = 0x65b648;
    }
    return result;
}


/* ================================================================== *
 * Unmap / retire / destroy / release (FUN_0003d2b8, 0003d330, 0003d438,
 * 0003d904, 0003d9d4, 0003da18, 0003df84, 0003a550, 0003a4a0, 0003a1e0,
 * 0003b258, 00039d2c, 00039e34, 0003e308, 0003e14c, 0003e710)
 * ================================================================== */

/* FUN_0003e710 @ 0x3e710  (est. sk_region_type_slot)
 * Return the type descriptor for region type char param_1 (indexed from a
 * table at 0x65b790), or 0 if out of range.
 * Confidence: high (table lookup) */
static word_t sk_region_type_slot(char type)
{
    if ((uint8_t)(type + 5U) < 0x19)
        return *(word_t *)((uint8_t)(type + 5U) * 8 + 0x65b790);
    return 0;
}

/* FUN_0003d2b8 @ 0x3d2b8  (est. sk_region_set_pending)
 * Record a pending unmap for region param_1: requires the span type tag and a
 * live allocation with the "has mapping" bit. Stores the window, backing base
 * and flags into param_1+0x28..0x40. Returns 0 or an error code.
 * Confidence: medium */
static seL4_Word sk_region_set_pending(word_t region, word_t st, word_t *window,
                                       word_t flags)
{
    if (st != 0x65b648) return 0x5050001;
    if (*(uint32_t *)(region + 0x20) != 0) {
        if ((*(uint32_t *)(region + 0x20) & 0x81000) != 0) {
            word_t a = *window;
            *(word_t *)(region + 0x30) = window[1];
            *(word_t *)(region + 0x28) = a;
            *(word_t *)(region + 0x38) = flags;
            *(word_t *)(region + 0x40) = *(word_t *)(region + 8);
            return 0;
        }
        return 0x50b0001;
    }
    return 0x50a0001;
}

/* FUN_0003d330 @ 0x3d330  (est. sk_vspace_region_bounds)
 * Compute the address range covered by region param_1: find the predecessor
 * span (just below param_1's base) and successor span (just after its end) and
 * write the covered [start, end) into param_2/param_3.
 * Confidence: low */
static void sk_vspace_region_bounds(word_t region, word_t *start, word_t *end)
{
    word_t local[9] = {0,0,0,0,0,0,0,0,0};
    sk_vspace_lock_enter(local, *(word_t *)(region + 0x50), 0, 0);
    word_t lo;
    if (*(word_t *)(region + 8) < 0x4000) lo = region;
    else {
        word_t r = sk_vspace_find_region(local, *(word_t *)(region + 8) - 0x4000);
        if (r == 0 || *(int *)(r + 0x20) != 0) lo = region; else lo = r;
    }
    if (lo + 0xb0 < region + 0xb0) SK_FATAL();
    *start = *(word_t *)(lo + 8);
    word_t hi;
    if (*(word_t *)(region + 0x10) + *(word_t *)(region + 8) == 0x1000000000) hi = region;
    else {
        word_t r = sk_vspace_find_region(local, 0);
        if (r == 0 || *(int *)(r + 0x20) != 0) hi = region; else hi = r;
    }
    if (region + 0xb0 <= hi + 0xb0) {
        *end = *(word_t *)(hi + 0x10) + *(word_t *)(hi + 8);
        sk_vspace_lock_exit(local, *(word_t *)(region + 0x50));
        return;
    }
    SK_FATAL();
}

/* FUN_0003d438 @ 0x3d438  (est. sk_vspace_unmap_range)
 * Unmap the physical range [param_1, param_2) from vspace param_3: walk the
 * page-table levels for the affected pages, dropping each mapping and, when
 * param_5 (sync) is set, refilling the shadow-space entry. Emits per-level
 * unmap callbacks (FUN_0003da18). Used by the span retire path.
 * Confidence: low (stateful multi-level unmap) */
static void sk_vspace_unmap_range(word_t base, word_t end, word_t vspace,
                                  word_t flags, word_t sync)
{
    word_t dom = FUN_00032cd0(*(word_t *)(vspace + 0x50));
    word_t total = base + end;
    if (CARRY8(base, end)) SK_ABORT("VAS abort");
    base = base & 0xffffffffffffc000;
    if (base < *(word_t *)(dom + 0x28)) SK_ABORT("VAS abort");
    if (*(word_t *)(dom + 0x30) < total) SK_ABORT("VAS abort");
    word_t add = (total & 0x3fff) ? 0x4000 : 0;
    if (FUN_00118164((void *)(vspace + 0x80)) != 0) SK_ABORT("VAS abort");
    word_t aend = add + (total & 0xffffffffffffc000);
    word_t st1[3] = {0,0,0};
    FUN_000363ac(st1, *(word_t *)(vspace + 0x78),
        (int)(base - *(word_t *)(dom + 0x28) >> 0xe) + 1);
    word_t st2[3] = {0,0,0};
    word_t state = FUN_0003667c(st2);
    while (((uint32_t)state & 3) != 0 &&
           ((state & 0xfffffc0) * 0x100 + *(word_t *)(dom + 0x28)) - 0x4000 < aend) {
        sk_spanmap_unmap_one(state, vspace, (int)flags, (int)flags, (int)sync);
        if ((int)sync != 0) {
            word_t st4[3] = {0,0,0};
            FUN_000363ac(st4, *(word_t *)(vspace + 0x78), (uint32_t)state >> 6 & 0x3fffff);
            st1[0] = st4[0];
        }
        state = FUN_0003667c(st1);
    }
    if (FUN_00118194((void *)(vspace + 0x80)) != 0) SK_ABORT("VAS abort");
}

/* FUN_0003da18 @ 0x3da18  (est. sk_spanmap_unmap_one)
 * Drop a single page mapping: notify the vspace owner (+0x10 callback of the
 * domain at +0xb8) when sync, then either unconditionally free the level-0
 * slot (param_4==0) or free it only if the spanmap walk reports success
 * (param_4!=0). Loops on the preempted result.
 * Confidence: low */
static void sk_spanmap_unmap_one(word_t state, word_t vspace, int notify,
                                 int sync, int mode)
{
    uint32_t level = (uint32_t)state >> 6 & 0x3fffff;
    if (mode != 0 && notify == 0) {
        word_t dom = FUN_00032cd0(*(word_t *)(vspace + 0x50));
        (*(void (**)(void))(*(word_t *)(dom + 0xb8) + 0x10))
            (*(word_t *)(dom + 0xb0), state >> 0x1c);
    }
    if (sync == 0) {
        word_t l[5] = {0,0,0,0,0};
        FUN_00035ba0(l, *(word_t *)(vspace + 0x78), level);
        if (l[0] == 0 && (l[2] & 0xff) != 0) SK_FATAL();
        *(word_t *)(vspace + 0x78) = l[4];
        do { CallSupervisor(4); } while (l[0] == 1);
    } else {
        word_t l[3] = {0,0,0};
        FUN_0003611c(l, *(word_t *)(vspace + 0x78), level, (word_t)FUN_004b23d8);
        if ((l[0] & 0xff) != 0) SK_FATAL();
        *(word_t *)(vspace + 0x78) = l[2];
    }
}

/* FUN_0003d904 @ 0x3d904  (est. sk_spanmap_next_level)
 * Advance the spanmap state: pop the next page-table level index from the
 * state stack (param_1+0x20..0x38 chain), updating the count. Returns the
 * level shift of the previous entry.
 * Confidence: low */
static word_t sk_spanmap_next_level(word_t st)
{
    word_t prev = *(word_t *)(*(word_t *)(st + 0x28) + 8);
    if (prev + 0x18U <= prev + 0x30U) {
        word_t slot = *(word_t *)(*(word_t *)(st + 0x20) + 8) + 0x18;
        word_t nv = FUN_0003667c(NULL);
        *(word_t *)slot = nv;
        *(uint32_t *)(*(word_t *)(*(word_t *)(st + 0x30) + 8) + 0x18) =
            (*(word_t *)slot) >> 6 & 0x3fffff;
        return (*(word_t *)slot) >> 0x1c;
    }
    SK_FATAL();
}

/* FUN_0003d9d4 @ 0x3d9d4  (est. sk_spanmap_free_states)
 * Free the three spanmap state buffers (offsets +0x20/+0x28/+0x30).
 * Confidence: medium */
static void sk_spanmap_free_states(word_t st)
{
    FUN_0004b8d0(*(word_t *)(st + 0x30), 8);
    FUN_0004b8d0(*(word_t *)(st + 0x28), 8);
    FUN_0004b8d0(*(word_t *)(st + 0x20), 8);
}

/* FUN_0003df84 @ 0x3df84  (est. sk_span_prefetch_pages)
 * Prefetch / retire the page range [param_2, param_2+param_3) of a
 * two-stage-mmu span (param_1): walk the shadow-space entries for the 32 MB
 * granules covered and, per 16 KB page, issue the retire callback
 * (FUN_00040f80) for the leaf level, via the owner's callbacks.
 * Confidence: low */
static void sk_span_prefetch_pages(char *span, word_t off, word_t len)
{
    word_t owner = *(word_t *)(span + 0x50);
    char *shadow = (char *)(owner + 0x130);
    if (*span != 0x11 || shadow == 0 || span == (char *)shadow) return;
    if (off < *(word_t *)(span + 0x10)) {
        if (len - 1U < *(word_t *)(span + 0x10) - off) {
            word_t vend = *(word_t *)(span + 8) + off + len;
            word_t vstart = (*(word_t *)(span + 8) + off) >> 3 & 0x1fffffffffffc000;
            word_t add = (vend & 0x1fff8) ? 0x4000 : 0;
            word_t venda = add + (vend >> 0x11) * 0x4000;
            word_t rel = vstart - *(word_t *)(shadow + 8);
            if (rel < *(word_t *)(shadow + 0x10)) {
                word_t delta = venda - vstart;
                if (*(word_t *)(shadow + 0x10) - rel < delta) SK_ABORT("VAS abort");
                if (venda == vstart) return;
                word_t i = 0;
                do {
                    word_t cb[8] = { 0x6ad3a8, owner, sk_span_retire_page, 0x65b770, rel, i, (word_t)shadow, delta };
                    if (owner == (word_t)&DAT_0064c3f0) FUN_00033b50(&cb);
                    else sk_span_retire_page(&cb);
                    i += 0x4000;
                } while (i < delta);
                return;
            }
            SK_ABORT("VAS abort");
        }
    } else FUN_004b326c();
    FUN_004b3294();
    SK_ABORT("VAS abort");
}

/* FUN_0003a550 @ 0x3a550  (est. sk_span_map_check)
 * Validate and align a map request [*param_2, *param_2+*param_3) on span
 * param_1: round the window down to 16 KB, then walk the leaf levels (via
 * sk_span_leaf_walk) to ensure mappings are present. On a leaf miss with a
 * two-stage mmu, re-walk the shadow space and repopulate via FUN_0003fa94.
 * Returns an error code (0 on success).
 * Confidence: low (nested page-walk) */
static void sk_span_map_check(word_t span, word_t *off, word_t *len)
{
    uint32_t f = *(uint32_t *)(span + 0x20);
    if (f != 0 && (f & 0x81000) == 0) {
        word_t o = *off;
        if (o < *(word_t *)(span + 0x10) && *len <= *(word_t *)(span + 0x10) - o) {
            word_t pbase = *(word_t *)(span + 8) + o & 0xffffffffffffc000;
            *len = (*len + o + *(word_t *)(span + 8)) - pbase;
            *off = pbase - *(word_t *)(span + 8);
            word_t add = (*len & 0x3fff) ? 0x4000 : 0;
            *len = add + (*len & 0xffffffffffffc000);
            sk_span_prefetch_pages((char *)span, *off);
            word_t r = sk_span_leaf_walk((char *)span, pbase, *len + pbase);
            uint32_t rl = (uint32_t)r & 0xff;
            if (rl == 2) { FUN_0011d7e8(0x68f0002, 0); return; }
            if (rl != 8 && (r & 0xff) != 0 && ((*(uint32_t *)(span + 0x20) >> 0x12) & 1) == 0) {
                word_t lv;
                sk_pair_t ctx = FUN_004b2fe0(r, pbase, &lv);
                if ((*(uint8_t *)(lv + 0x21) >> 4 & 1) != 0 && *(word_t *)(lv + 0x10) > ctx.hi) {
                    sk_span_prefetch_pages((char *)lv, ctx.hi & 0xffffffffffffc000, 0x4000);
                    word_t r2 = sk_span_map_page_walk(lv, *(word_t *)(lv + 8) + ctx.hi, lv, 0);
                    if ((long)r2 < 7) {
                        if (r2 == 0) FUN_0011d7e8(0, 0);
                        else if (r2 == 2) FUN_0011d7e8(0x80020002, 0);
                        else if (r2 == 5) FUN_0011d7e8(0x80050003, 0);
                        else FUN_004b3064(r2, NULL);
                    } else {
                        if (r2 != 7 && r2 != 0x307 && r2 != 0x207) {
                            FUN_004b3064(r2, NULL);
                            sk_span_map_check_window(NULL, 0, 0, 0);
                            return;
                        }
                        FUN_0011d7e8((r2 & 0x7fff) << 0x10 | 0x80000001, 0);
                    }
                }
                FUN_0011d7e8(0x6230001, 0);
            }
            FUN_0011d7e8(0, 0);
            return;
        }
    }
    FUN_0011d7e8(0x6800001, 0);
}

/* FUN_0003a4a0 @ 0x3a4a0  (est. sk_span_sync_advance)
 * Advance the span sync cursor: given a desired address (in x9/x10), either
 * return the current cursor (span+0x48) or, if past the end, update the cursor
 * via sk_span_map_check and return the new aligned address in *param_2.
 * Returns 0 or an error code.
 * Confidence: low */
static word_t sk_span_sync_advance(word_t span, word_t *out)
{
    word_t want = 0;
    if (*(word_t *)(span + 0x10) < want) return 0x6010001;
    word_t cursor = *(word_t *)(span + 0x48);
    word_t delta = want - cursor;
    if (want < cursor || delta == 0) { *out = cursor; return 0; }
    if ((0 >> 7 & 1) != 0) cursor = *(word_t *)(span + 0x10) - want;
    word_t o = cursor, l = delta;
    word_t r = sk_span_map_check(span, &o, &l).lo;
    if ((r & 0xff) == 0) { *(word_t *)(span + 0x48) = want; *out = want; return 0; }
    return r;
}

/* FUN_0003a1e0 @ 0x3a1e0  (est. sk_span_set_flags)
 * Update a span's flag word (param_1+0x20): clear bits requested by param_2
 * (masked against current flags); if any mapping/prefetch bits changed, re-walk
 * the affected pages to downgrade leaf mappings. Uses the tpidrro_el0 per-cpu
 * mode and the page-level walk.
 * Confidence: low (large flag-transition handler) */
static void sk_span_set_flags(word_t span, uint32_t clear)
{
    uint32_t f = *(uint32_t *)(span + 0x20);
    if ((clear & (f ^ 0xffffffff)) == 0) {
        uint32_t keep = f & (clear ^ 0xffffffff);
        if ((keep & 0xd08d9c1) == 0) {
            f &= clear;
            *(uint32_t *)(span + 0x20) = f;
            if ((keep & 0x18) != 0) {
                word_t cur = *(word_t *)(span + 8);
                word_t end = *(word_t *)(span + 0x10) + *(word_t *)(span + 8);
                if ((f >> 7 & 1) != 0)
                    end = (*(word_t *)(span + 0x10) - *(word_t *)(span + 0x48)) + *(word_t *)(span + 8);
                word_t i = *(word_t *)(span + 8);
                while (true) {
                    word_t step = ((f & 0x40) != 0) ? 0x48 : 0x10;
                    if (*(word_t *)(span + step) <= (word_t)(end - i)) break;
                    word_t dom = FUN_00032cd0(*(word_t *)(span + 0x50));
                    if (span + 0x90U < span + 0x80) SK_FATAL();
                    if (FUN_00118164((void *)(span + 0x80)) != 0) SK_ABORT("VAS abort");
                    word_t l[5] = {0,0,0,0,0};
                    if (dom + 0xd0 < dom) SK_FATAL();
                    FUN_00035ba0(l, *(word_t *)(span + 0x78),
                        (int)((word_t)(end - *(word_t *)(dom + 0x28)) >> 0xe) + 1);
                    word_t node = l[0];
                    *(word_t *)(span + 0x78) = l[4];
                    if (l[0] != 0) {
                        word_t mode = (f >> 3 & 3);
                        word_t *tp = (word_t *)tpidrro_el0;
                        *tp = mode; CallSupervisor(0); *tp = mode;
                        if (FUN_00118194((void *)(span + 0x80)) != 0) SK_ABORT("VAS abort");
                        if ((l[0] & 0xff) != 4) FUN_004b2f80(l[0], l);
                    } else {
                        if (FUN_00118194((void *)(span + 0x80)) != 0) SK_ABORT("VAS abort");
                        if ((int8_t)l[1] != 0) { FUN_004b2fc8(); SK_ABORT("VAS abort"); }
                    }
                    end += 0x4000;
                    f = *(uint32_t *)(span + 0x20);
                    if ((f >> 7 & 1) != 0) break;
                }
            }
            FUN_0011d7e8(0, 0);
            return;
        }
        FUN_0011d7e8(0x5e70001, 0);
        return;
    }
    FUN_0011d7e8(0x5df0001, 0);
}

/* FUN_0003b258 @ 0x3b258  (est. sk_span_destroy_impl)
 * Destroy a single span: lock its vspace, verify it is allocated, then find
 * the next non-empty region in the tree. On success, unlock and decrement the
 * vspace's live-span counter (_DAT_006af198); returns the region handle
 * (type 0x65b648) or the empty handle.
 * Confidence: medium */
static sk_pair_t sk_span_destroy_impl(word_t *slot)
{
    word_t region = *slot;
    if (region != 0) {
        word_t local[9] = {0,0,0,0,0,0,0,0,0};
        word_t vspace = *(word_t *)(region + 0x50);
        sk_vspace_lock_enter(local, vspace, 0, 0);
        if (*(int *)(region + 0x20) == 0) return (sk_pair_t){ 0, 0 };
        word_t next = (*(word_t *)(region + 0x10) + *(word_t *)(region + 8) == 0x1000000000)
            ? 0 : sk_vspace_find_region(local, 0);
        word_t found = sk_vspace_find_nonempty((word_t)local, next);
        *slot = found;
        sk_vspace_lock_exit(local, vspace);
        if (found == 0) DAT_006af198 = DAT_006af198 - 1;
    }
    return (sk_pair_t){ region, 0x65b648 };
}

/* FUN_00039d2c @ 0x39d2c  (est. sk_vspace_span_free)
 * Free a span object: verify ownership, release its page-table buffers
 * (sk_vspace_span_release), tear down the buf cookie and meta/state buffers,
 * and return the object to the allocator — unless it is a two-stage live
 * mapping (byte at +0xa1 == 1), which must be torn down via the abort path.
 * Returns {0,0} on success.
 * Confidence: low */
static sk_pair_t sk_vspace_span_free(word_t vspace, word_t *span)
{
    DAT_006ad39c = DAT_006ad39c + 1;
    if (span[10] != vspace) SK_ABORT("VAS abort");
    if (*(uint8_t *)((word_t)span + 0xa1) == 1) { FUN_004b2f58(); }
    else {
        sk_span_destroy_impl((word_t *)&span[0xb]);
        sk_span_destroy_impl((word_t *)&span[0xe]);
        FUN_004b23d8((void *)span[0x12]);
        FUN_004b23d8((void *)span[0x13]);
        if (*(uint8_t *)(span + 8) != 1) {
            FUN_000539fc(span + 6);
            for (int i = 0; i < 24; i++) span[i] = 0;
            FUN_00033684(span);
            return (sk_pair_t){ 0, 0 };
        }
    }
    SK_ABORT("VAS abort");
}

/* FUN_00039e34 @ 0x39e34  (est. sk_vspace_span_release)
 * Release a span's page-table: unlink from the vspace LRU, unmap the mapping
 * window (sk_span_map_check_window / sk_vspace_unmap_range), tear down the
 * leaf buffer (sk_span_teardown_node), and re-link the span into the
 * collection's secondary list after clearing its flags. Refuses to release a
 * span still referenced (bit 3 at +0x23).
 * Confidence: low (large teardown) */
static sk_pair_t sk_vspace_span_release(void *span)
{
    word_t p = (word_t)span;
    word_t vspace = *(word_t *)(p + 0x50);
    word_t local[9] = {0,0,0,0,0,0,0,0,0};
    word_t err;
    if (((*(uint8_t *)(p + 0x23) >> 3) & 1) == 0) {
        if (FUN_00045cb8((void *)p) != 0) {
            word_t *list = (word_t *)(vspace + 0x1f0);
            if (FUN_00118164(list) != 0) SK_ABORT("VAS abort");
            word_t prev = *(word_t *)(p + 0x90);
            word_t *next = *(word_t **)(p + 0x98);
            if (prev != 0) *(word_t **)(prev + 0x98) = next;
            *next = prev;
            if (FUN_00118194(list) != 0) SK_ABORT("VAS abort");
        }
        word_t lo = *(word_t *)(p + 8);
        if ((*(uint32_t *)(p + 0x20) >> 7 & 1) != 0)
            lo = (*(word_t *)(p + 0x10) - *(word_t *)(p + 0x48)) + lo;
        word_t hi = (*(uint32_t *)(p + 0x20) & 0x40) ? *(word_t *)(p + 0x48) : *(word_t *)(p + 0x10);
        sk_span_map_check_window(p, &lo, &hi, 1);
        if (p + 0x90 < p + 0x80) SK_FATAL();
        if (FUN_00118164((void *)(p + 0x80)) != 0) SK_ABORT("VAS abort");
        sk_span_teardown_node(p);
        if (FUN_00118194((void *)(p + 0x80)) != 0) SK_ABORT("VAS abort");
        sk_vspace_lock_enter(local, vspace, *(word_t *)(p + 8), *(word_t *)(p + 0x10));
        if ((*(uint32_t *)(p + 0x20) >> 0x18 & 1) == 0) {
            if ((*(uint32_t *)(p + 0x20) >> 0x10 & 1) != 0) FUN_000457f8(local, vspace, span);
            word_t *buf = *(word_t **)(p + 0x70);
            if (buf == (word_t *)0) SK_ABORT("VAS abort");
            *(uint8_t *)(buf + 3) = 0;
            if (2 < (uint8_t)(*(uint8_t *)((word_t)local + 0x31))) SK_ABORT("VAS abort");
            *buf = local[2]; local[2] = (word_t)buf;
            *(uint8_t *)((word_t)local + 0x31) = *(uint8_t *)((word_t)local + 0x31) + 1;
            *(word_t *)(p + 0x70) = 0;
            *(uint32_t *)(p + 0x20) = 0;
            *(word_t *)p = 0; *(word_t *)(p + 0x30) = 0;
            *(word_t *)(p + 0x28) = 0; *(word_t *)(p + 0x40) = 0; *(word_t *)(p + 0x38) = 0;
            sk_span_tree_update_extent(*(word_t *)(local[0] + 0x58), p);
            if (0x3fff < *(word_t *)(p + 8)) {
                word_t r = sk_vspace_find_region(local, *(word_t *)(p + 8) - 0x4000);
                if (r != 0 && *(int *)(r + 0x20) == 0) {
                    if (r + 0xb0 < r) SK_FATAL();
                    sk_span_merge_caller(local, vspace, r, p);
                }
            }
            if (*(word_t *)(p + 0x10) + *(word_t *)(p + 8) != 0x1000000000) {
                word_t r = sk_vspace_find_region(local, 0);
                if (r != 0 && *(int *)(r + 0x20) == 0) {
                    if (r + 0xb0 < r) SK_FATAL();
                    sk_span_merge_caller(local, vspace, p, r);
                }
            }
            err = 0;
        } else err = 0x5660001;
        sk_vspace_lock_exit(local, vspace);
    } else {
        FUN_00118b28("WARNING: failed attempt to destroy referenced span");
        err = 0x5b10001;
    }
    return (sk_pair_t){ err, 0 };
}

/* FUN_0003e308 @ 0x3e308  (est. sk_span_sync_unmap)
 * Synchronously unmap the page at offset param_2 of the span at param_1:
 * locate the leaf entry and CallSupervisor(4) until the unmap lands.
 * Returns 0 or an error code.
 * Confidence: low */
static sk_pair_t sk_span_sync_unmap(word_t span, word_t off)
{
    if (*(word_t *)(span + 8) == 0) return (sk_pair_t){ 0x10bb0001, 0 };
    word_t inner = *(word_t *)(span + 0x10);
    if (!(off < *(word_t *)(inner + 0x10)) || !(0x3fff < *(word_t *)(inner + 0x10) - off))
        return (sk_pair_t){ 0x10c40001, 0 };
    word_t dom = FUN_00032cd0((word_t)&DAT_0064c3f0);
    word_t l[5] = {0,0,0,0,0};
    if (dom + 0xd0 < dom) SK_FATAL();
    FUN_00035ba0(l, *(word_t *)(inner + 0x78),
        (int)((*(word_t *)(*(word_t *)(span + 0x10) + 8) + off & 0xffffffffffffc000)
              - *(word_t *)(dom + 0x28) >> 0xe) + 1);
    if (((l[4] ^ *(word_t *)(inner + 0x78)) >> 0x1c) == 0) {
        if (l[0] != 0) {
            do { CallSupervisor(4); if (l[0] == 0) return (sk_pair_t){ 0, 0 }; }
            while (l[0] == 1);
            return (sk_pair_t){ (l[0] & 0x7fff) << 0x10 | 0x80000001, 0 };
        }
    } else FUN_004b3364();
    SK_ABORT("VAS abort");
}

/* FUN_0003e14c @ 0x3e14c  (est. sk_span_leaf_unmap)
 * Unmap a single leaf page at offset param_3 of the span described by
 * param_1: find the level-1 entry (32 MB granule), CallSupervisor(2) then
 * CallSupervisor(4) until the mapping is dropped. Returns the error code.
 * Confidence: low */
static sk_pair_t sk_span_leaf_unmap(word_t *span, word_t a2, word_t off)
{
    if (span[1] == 0) return (sk_pair_t){ 0x107a0001, 0 };
    word_t inner = span[2];
    if (*(word_t *)(inner + 0x10) <= off || *(word_t *)(inner + 0x10) - off < 0x4000)
        return (sk_pair_t){ 0x10810001, 0 };
    word_t vaddr = *(word_t *)(inner + 8) + off;
    word_t idx = (vaddr - (*(word_t *)(inner + 8) & 0xfffffffffe000000)) >> 0x19;
    if (idx < (word_t)span[1]) {
        word_t entry = *(word_t *)(*span + idx * 8);
        if (entry == 0) { FUN_004b332c(); SK_FATAL(); }
        uint32_t f = *(uint32_t *)(inner + 0x20);
        word_t dom = FUN_00032cd0((word_t)&DAT_0064c3f0);
        word_t cookie = FUN_000368f8(*(word_t *)(inner + 0x78));
        word_t l[5] = {0,0,0,0,0};
        if (dom + 0xd0 < dom) SK_FATAL();
        word_t page = vaddr & 0xffffffffffffc000;
        FUN_00035ba0(l, *(word_t *)(inner + 0x78),
            (int)(page - *(word_t *)(dom + 0x28) >> 0xe) + 1);
        if (FUN_000368f8(*(word_t *)(inner + 0x78)) == cookie) {
            if (l[0] != 0) {
                CallSupervisor(2);
                if (a2 == 0) {
                    word_t r = FUN_00043be8(dom, entry, l[0], page, f >> 3 & 3, 0);
                    if (r == 0) return (sk_pair_t){ 0, 0 };
                    do { CallSupervisor(4); } while (l[0] == 1);
                    return (sk_pair_t){ (r & 0x7fff) << 0x10 | 0x80000001, 0 };
                }
                return (sk_pair_t){ (a2 & 0x7fff) << 0x10 | 0x80000001, 0 };
            }
            SK_FATAL();
        }
        FUN_004b32f4();
        SK_ABORT("VAS abort");
    }
    FUN_004b32bc(0x10810001, 0);
    SK_ABORT("VAS abort");
}


/* ================================================================== *
 * Page-walk / translate (FUN_0003ff00, 0003fcc8, 0003fa94, 0003f980,
 * 0003f170, 00040630, 000402b4, 000403b0, 00040980, 00040f80)
 * ================================================================== */

/* FUN_0003f980 @ 0x3f980  (est. sk_l4_error_string)
 * Fill a 4-word record with the L4 error-code name for code param_2 (from the
 * table at 0x4bc218). Codes > 9 copy a default message.
 * Confidence: high (string-table matched) */
static void sk_l4_error_string(word_t *out, uint8_t code)
{
    const char *s;
    if (9 < code) {
        s = (const char *)0x4bc208;
        out[1] = *(word_t *)(s + 8);
        *out = *(word_t *)s;
        out[3] = *(word_t *)(s + 0x18);
        out[2] = *(word_t *)(s + 0x10);
        FUN_0000178c(out, 0x20);
        return;
    }
    switch (code) {
    default: s = (const char *)0x4bc218; break; /* Success */
    case 1:  s = (const char *)0x4bc238; break; /* Preempted */
    case 2:  s = (const char *)0x4bc258; break; /* Canceled */
    case 3:  s = (const char *)0x4bc278; break; /* Truncated */
    case 4:  s = (const char *)0x4bc298; break; /* CapInvalid */
    case 5:  s = (const char *)0x4bc2b8; break; /* SlotInvalid */
    case 6:  s = (const char *)0x4bc2d8; break; /* MethodInvalid */
    case 7:  s = (const char *)0x4bc2f8; break; /* ArgumentInvalid */
    case 8:  s = (const char *)0x4bc318; break; /* OperationInvalid */
    case 9:  s = (const char *)0x4bc338; break; /* PermissionInvalid */
    }
    out[1] = *(word_t *)(s + 8);
    *out = *(word_t *)s;
    out[3] = *(word_t *)(s + 0x18);
    out[2] = *(word_t *)(s + 0x10);
}

/* FUN_00042640 @ 0x42640  (est. sk_l4_error_string2)
 * Duplicate of sk_l4_error_string using the second error-name table (base
 * 0x4bc3c0).
 * Confidence: high (string-table matched) */
static void sk_l4_error_string2(word_t *out, uint8_t code)
{
    const char *s;
    if (9 < code) {
        s = (const char *)0x4bc500;
        out[1] = *(word_t *)(s + 8);
        *out = *(word_t *)s;
        out[3] = *(word_t *)(s + 0x18);
        out[2] = *(word_t *)(s + 0x10);
        FUN_0000178c(out, 0x20);
        return;
    }
    switch (code) {
    default: s = (const char *)0x4bc3c0; break;
    case 1:  s = (const char *)0x4bc3e0; break;
    case 2:  s = (const char *)0x4bc400; break;
    case 3:  s = (const char *)0x4bc420; break;
    case 4:  s = (const char *)0x4bc440; break;
    case 5:  s = (const char *)0x4bc460; break;
    case 6:  s = (const char *)0x4bc480; break;
    case 7:  s = (const char *)0x4bc4a0; break;
    case 8:  s = (const char *)0x4bc4c0; break;
    case 9:  s = (const char *)0x4bc4e0; break;
    }
    out[1] = *(word_t *)(s + 8);
    *out = *(word_t *)s;
    out[3] = *(word_t *)(s + 0x18);
    out[2] = *(word_t *)(s + 0x10);
}

/* FUN_0003ff00 @ 0x3ff00  (est. sk_span_leaf_walk)
 * Walk the leaf page-table levels for the physical range [param_2, param_3) of
 * span param_1, issuing the per-level populate callbacks (FUN_000402b4 /
 * FUN_000403b0) for each 32 MB granule and, within it, each 16 KB page.
 * Returns the final aligned extent (or 2 on failure).
 * Confidence: low */
static word_t sk_span_leaf_walk(char *span, word_t pbase, word_t pend)
{
    word_t add = (pend & 0x3fff) ? 0x4000 : 0;
    word_t dom = FUN_00032cd0(*(word_t *)(span + 0x50));
    if (!(dom <= dom + 0xd0)) SK_FATAL();
    word_t end_al = add + (pend & 0xffffffffffffc000);
    for (word_t gran = pbase & 0xfffffffffe000000; gran < end_al; gran += 0x2000000) {
        word_t cap = FUN_00042abc(dom, 1, gran);
        if ((FUN_00042c20(dom, cap) & 1) == 0) return 2;
    }
    if (!(span + 0x80 <= span + 0x90)) SK_FATAL();
    if (FUN_00118164((void *)(span + 0x80)) != 0) SK_ABORT("VAS abort");
    word_t base = pbase & 0xffffffffffffc000;
    char rtype = *span;
    uint32_t f = *(uint32_t *)(span + 0x20);
    word_t lvl = (f >> 0xd) & 1;
    if (rtype != 0x11) lvl = 0;
    word_t attr = (f >> 0x11 & 0x20) | lvl;
    word_t sa[3] = {0,0,0}, sb[3] = {0,0,0};
    word_t cbA[5] = { 0x6ad3a8, DAT_004bb180, FUN_000402b4, 0x65b710, dom };
    word_t cbB[5] = { 0x6ad3a8, DAT_004bb180, FUN_000403b0, 0x65b740, dom };
    word_t cur = base;
    if ((f >> 0x1a & 1) == 0) {
        word_t n = end_al - base >> 0xe;
        word_t v = *(word_t *)(dom + 0xb0);
        word_t *ops = *(word_t **)(dom + 0xb8);
        if (ops[9] == 0) {
            if (end_al != base)
                for (word_t i = 0; i < n; i++) {
                    word_t r1 = FUN_000402b4(&cbA, i);
                    word_t r2 = (*(word_t *)*ops)(v, rtype, r1, r1, attr);
                    FUN_000403b0(&cbB, r2, i, r1);
                }
        } else (*(void (**)(void))(ops[9]))(v, rtype, attr, n, &cbA, &cbB);
    } else {
        while (end_al != cur) {
            rtype = *span;
            word_t v = *(word_t *)(dom + 0xb0);
            word_t *ops = *(word_t **)(dom + 0xb8);
            if (ops[9] == 0) {
                word_t r1 = FUN_000402b4(&cbA, 0);
                v = (*(word_t *)*ops)(v, rtype, r1, r1, attr);
                FUN_000403b0(&cbB, v, 0, r1);
            } else (*(void (**)(void))(ops[9]))(v, rtype, attr, 1, &cbA, &cbB);
            if (sb[3] != 0) break;
            word_t s = sa[3];
            sa[3] = s + 0x4000U;
            cur = s + 0x4000U;
        }
    }
    if (FUN_00118194((void *)(span + 0x80)) != 0) SK_ABORT("VAS abort");
    return sb[3];
}

/* FUN_000402b4 @ 0x402b4  (est. sk_spanmap_level_cb)
 * Per-granule callback: map the leaf level for index param_2 of the spanmap,
 * storing the result into the walk state. Records error 0x102 if missing.
 * Confidence: low */
static void sk_spanmap_level_cb(word_t cb, word_t idx)
{
    word_t l[5] = {0,0,0,0,0};
    word_t dom = *(word_t *)(cb + 0x38);
    if (dom != 0 && (dom + 0xd0 < dom ||
        *(word_t *)(cb + 0x40) < dom + 0xd0 || dom < *(word_t *)(cb + 0x48))) SK_FATAL();
    FUN_000287e4(l, *(word_t *)(*(word_t *)(cb + 0x30) + 0x78),
        (int)((word_t)((*(word_t *)(*(word_t *)(*(word_t *)(cb + 0x20) + 8) + 0x18) +
                       idx * 0x4000) - *(word_t *)(dom + 0x28)) >> 0xe) + 1);
    *(word_t *)(*(word_t *)(cb + 0x30) + 0x78) = l[4];
    if (l[0] == 0) {
        if ((l[2] & 0xff) != 0) SK_ABORT("spanmap get cap invalid");
        word_t cnt = *(word_t *)(*(word_t *)(cb + 0x28) + 8);
        if (*(word_t *)(cnt + 0x18) == 0) *(word_t *)(cnt + 0x18) = 0x102;
    }
}

/* FUN_000403b0 @ 0x403b0  (est. sk_spanmap_level_cb2)
 * Second per-granule callback: on success (param_2 == 0) populate the leaf via
 * the pte-map path (FUN_0003fcc8) and record the result; on failure report the
 * L4 error. Called from the walk loop for each page.
 * Confidence: low */
static void sk_spanmap_level_cb2(word_t cb, word_t r, word_t idx, word_t pte)
{
    word_t cur = *(word_t *)(*(word_t *)(*(word_t *)(cb + 0x20) + 8) + 0x18) + idx * 0x4000;
    if (r == 0) {
        word_t dom = *(word_t *)(cb + 0x30);
        if (dom == 0 || (dom <= dom + 0xd0 && dom + 0xd0 <= *(word_t *)(cb + 0x38) &&
            *(word_t *)(cb + 0x40) <= dom)) {
            word_t cap = FUN_00042abc(dom, 1, cur);
            dom = *(word_t *)(cb + 0x30);
            if (dom == 0 || (dom <= dom + 0xd0 && dom + 0xd0 <= *(word_t *)(cb + 0x38) &&
                *(word_t *)(cb + 0x40) <= dom)) {
                word_t r2 = sk_span_leaf_walk_v2((char *)*(word_t *)(cb + 0x48), cur, dom, pte, cap, 0, 1);
                if (r2 != 0) {
                    dom = *(word_t *)(cb + 0x30);
                    if (*(word_t *)(cb + 0x38) < dom + 0xd0 || dom < *(word_t *)(cb + 0x40)) SK_FATAL();
                    FUN_004b3538(dom, pte, cb, r2);
                }
                return;
            }
        }
    } else {
        if (r == 0x107) return;
        if ((r & 0xfd) == 0) {
            word_t dom = *(word_t *)(cb + 0x30);
            if (*(word_t *)(cb + 0x38) < dom + 0xd0 || dom < *(word_t *)(cb + 0x40)) SK_FATAL();
            word_t rr = (*(word_t (**)(void))(*(word_t *)(dom + 0xb8) + 0x10))
                (*(word_t *)(dom + 0xb0), pte);
            if ((rr & 0xff) == 0) {
                word_t cnt = *(word_t *)(*(word_t *)(cb + 0x28) + 8);
                if (*(word_t *)(cnt + 0x18) == 0) *(word_t *)(cnt + 0x18) = r;
                return;
            }
            FUN_004b35a0(rr, NULL);
        }
        word_t buf[32];
        sk_l4_error_string(buf, r);
        if (*(word_t *)(cb + 0x30) + 0xd0 <= *(word_t *)(cb + 0x38) &&
            *(word_t *)(cb + 0x40) <= *(word_t *)(cb + 0x30)) {
            FUN_004b2820(0xeb1a02bf914012ba);
            sk_l4_error_string(buf, r);
            FUN_004afae4("Unexpected L4 Error: %s %zu err");
        }
    }
}

/* FUN_00040f80 @ 0x40f80  (est. sk_span_retire_page)
 * Retire a single 16 KB page: unmap the [base, base+0x4000) window of the
 * span at param_1+0x30 via sk_span_map_check. Used as the per-page retire
 * callback. Aborts on any error.
 * Confidence: medium */
static void sk_span_retire_page(word_t st)
{
    word_t base = *(word_t *)(st + 0x28) + *(word_t *)(st + 0x20);
    word_t len = 0x4000;
    word_t r = sk_span_map_check(*(word_t *)(st + 0x30), &base, &len).lo;
    if (r != 0) SK_ABORT("VAS abort");
    if (base != *(word_t *)(st + 0x28) + *(word_t *)(st + 0x20)) SK_ABORT("VAS abort");
    if (len != 0x4000) SK_ABORT("VAS abort");
}

/* FUN_0003f170 @ 0x3f170  (est. sk_span_map_check_window)
 * Validate a span's map window against [*param_2, *param_2+*param_3): align
 * the window down, ensure flags don't forbid mapping (bit 0x4000000), and
 * unmap the window via sk_vspace_unmap_range when the span is a two-stage mmu.
 * Adjusts *param_2/*param_3 to the aligned window. Returns 0 or an error.
 * Confidence: low */
static sk_pair_t sk_span_map_check_window(word_t span, word_t *off, word_t *len,
                                          int param_4)
{
    word_t dom = FUN_00032cd0(*(word_t *)(span + 0x50));
    uint32_t f = *(uint32_t *)(span + 0x20);
    if ((f & 0x4000000) == 0) param_4 = 1;
    word_t o = *off;
    if (*(word_t *)(span + 0x10) <= o || *(word_t *)(span + 0x10) - o < *len ||
        (f & 0x8000000) != 0) return (sk_pair_t){ 0x7210001, 0 };
    word_t v = *(word_t *)(span + 8) + o;
    word_t add = (v & 0x3fff) ? 0x4000 : 0;
    word_t aligned = add + (v & 0xffffffffffffc000);
    *len = (v + *len) - aligned;
    *off = aligned - *(word_t *)(span + 8);
    word_t aend = *len & 0xffffffffffffc000;
    *len = aend;
    sk_vspace_unmap_range(aligned, aend, span, f >> 0xc & 1, param_4);
    if (param_4 != 0) {
        bool b5 = (*off == 0) ? (*len == *(word_t *)(span + 0x10)) : false;
        bool b6 = false;
        if ((*(uint32_t *)(span + 0x20) >> 6 & 1) != 0) {
            word_t s = *(word_t *)(span + 8);
            word_t e = s;
            if ((*(uint32_t *)(span + 0x20) >> 7 & 1) != 0)
                e = (*(word_t *)(span + 0x10) - *(word_t *)(span + 0x48)) + s;
            if (*off == e - s) b6 = (*len == *(word_t *)(span + 0x48));
        }
        word_t target = (b5 || b6) ? (span + 0xb0) : 0;
        if (dom + 0xd0 < dom || (target != 0 && (target < span + 0xb0 || span + 0xb0 < span)))
            SK_FATAL();
        FUN_00043f28(dom, aligned, aend, (f & 0x1000) == 0);
    }
    return (sk_pair_t){ 0, 0 };
}

/* FUN_00040630 @ 0x40630  (est. sk_vspace_map_phys)
 * Map physical page param_2 into vspace param_1: resolve the span covering the
 * page, walk its leaf buffer, and install the pte (via the domain's +0x18
 * callback). On a two-stage mmu (bit 4 at +0x21) falls back to the direct
 * mapping callback at +0x28. *param_3 receives the pte. Returns {error, pte}.
 * Confidence: medium */
static sk_pair_t sk_vspace_map_phys(word_t vspace, word_t paddr, word_t *pte_out)
{
    if (*(word_t *)(vspace + 0x10) <= (paddr & 0xffffffffffffc000) - *(word_t *)(vspace + 8))
        SK_ABORT("VAS abort");
    word_t pte = *(word_t *)(vspace + 0x40);
    *pte_out = (word_t)-1;
    if ((*(uint8_t *)(vspace + 0x21) >> 4 & 1) == 0) {
        word_t dom = FUN_00032cd0(*(word_t *)(vspace + 0x50));
        if (vspace + 0x90U < vspace + 0x80) SK_FATAL();
        if (FUN_00118164((void *)(vspace + 0x80)) != 0) SK_ABORT("VAS abort");
        word_t l[5] = {0,0,0,0,0};
        if (dom + 0xd0 < dom) SK_FATAL();
        FUN_00035ba0(l, *(word_t *)(vspace + 0x78),
            (int)(paddr - *(word_t *)(dom + 0x28) >> 0xe) + 1);
        *(word_t *)(vspace + 0x78) = l[4];
        if (l[0] == 0) {
            if (FUN_00118194((void *)(vspace + 0x80)) != 0) SK_ABORT("VAS abort");
            bool b = (l[2] & 0xff) != 0;
            return (sk_pair_t){ b ? l[2] : 0x9370002, b ? l[3] : 0 };
        }
        word_t r = (*(word_t (**)(void))(*(word_t *)(dom + 0xb8) + 0x18))
            (*(word_t *)(dom + 0xb0), l[0], pte_out);
        if (FUN_00118194((void *)(vspace + 0x80)) != 0) SK_ABORT("VAS abort");
        if (r != 0) return (sk_pair_t){ 0x93e0001, 0 };
        return (sk_pair_t){ 0, 0 };
    }
    if (*(word_t **)(vspace + 0x28) != (word_t *)0) {
        word_t r = (*(word_t (**)(void))(*(word_t *)(vspace + 0x28)))
            (*(word_t *)(vspace + 0x38), (paddr & 0xffffffffffffc000) - pte, pte_out);
        if ((r & 1) == 0) return (sk_pair_t){ 0x9280001, 0 };
        return (sk_pair_t){ 0, 0 };
    }
    return (sk_pair_t){ 0x9260001, 0 };
}

/* FUN_00040980 @ 0x40980  (est. sk_startfault_cow)
 * Copy-on-write fault handler for a two-stage vspace: resolve the faulting
 * span's leaf mapping; if the page is a COW shared page, map a fresh private
 * copy (FUN_0003fa94), fix up the pte and record the fault result into the
 * fault record param_5. Tracks per-path counters (_DAT_006ad3xx). Handles the
 * preemption loop via CallSupervisor(4).
 * Confidence: low (stat-heavy fault path) */
static void sk_startfault_cow(word_t vspace, word_t faddr, uint32_t a3,
                              word_t span, void *fault_rec)
{
    DAT_006ad304 = DAT_006ad304 + 1;
    if ((*(uint8_t *)(vspace + 0xa0) & 1) == 0) {
        word_t *faulting = (word_t *)(vspace + 0x90);
        if (*faulting != 0) {
            if (*(word_t *)(vspace + 0x98) != 0) {
                word_t dom = FUN_00032cd0(*(word_t *)(span + 0x50));
                if (span + 0x90U < span + 0x80) SK_FATAL();
                if ((int)FUN_00118164((void *)(span + 0x80)) != 0) goto abort;
                word_t l[5] = {0,0,0,0,0};
                if (dom + 0xd0 < dom) SK_FATAL();
                FUN_000287e4(l, *(word_t *)(span + 0x78),
                    (int)((word_t)(faddr - *(word_t *)(dom + 0x28)) >> 0xe) + 1);
                word_t leaf = l[0];
                *(word_t *)(span + 0x78) = l[4];
                word_t lk = FUN_00118194((void *)(span + 0x80));
                if (leaf == 0) {
                    if ((int)lk != 0) FUN_004afae4("abort spanmap_lock");
                    sk_startfault_done((word_t)fault_rec, (l[2] & 0xff) ? l[2] : 0xe280002,
                                       (l[2] & 0xff) ? l[3] : 0);
                    return;
                }
                if ((int)lk != 0) FUN_004afae4("abort spanmap_lock");
                if (1 < a3) { DAT_006ad308 = DAT_006ad308 + 1;
                    sk_startfault_done((word_t)fault_rec, 0xe360001, 0); return; }
                word_t mode = (*(uint32_t *)(span + 0x20) >> 3) & 3;
                word_t *tp = (word_t *)tpidrro_el0;
                *tp = mode; CallSupervisor(0); *tp = mode;
                if (leaf == 0) { DAT_006ad30c = DAT_006ad30c + 1;
                    sk_startfault_done((word_t)fault_rec, 0, 0); return; }
                do { CallSupervisor(4); } while (*faulting == 1);
                word_t cb = 0;
                *tp = 0; CallSupervisor(0); *tp = 0;
                if (leaf != 0) {
                    if (*(word_t **)(span + 0x30) == (word_t *)0) {
                        FUN_004b3768(leaf, 0); FUN_004b3790();
                        goto coalesce;
                    }
                    DAT_006ad31c = DAT_006ad31c + 1;
                    word_t cbres = (*(word_t **)(span + 0x30))
                        (*(word_t *)(span + 0x38), faddr - *(word_t *)(span + 0x40), *faulting, &cb);
                    int cr = (int)cbres;
                    if (cr < 2) {
                        if (cr == 0) { DAT_006ad320 = DAT_006ad320 + 1;
                            sk_startfault_done((word_t)fault_rec, 0xe690001, 0); return; }
                        if (cr != 1) goto badres;
                        FUN_004b3790(); goto coalesce;
                    }
                    if (cr != 2) {
                        if (cr != 3) goto badres;
                        FUN_004b37a4(); goto coalesce;
                    }
                    DAT_006ad328 = DAT_006ad328 + 1;
                    if (a3 != 0) goto coalesce;
                    DAT_006ad330 = DAT_006ad330 + 1;
                    if ((char)sk_span_map_page_walk(span, faddr, *faulting, 1, 0, 0, 0) == 0) {
                        FUN_004b363c(faulting, NULL);
                        sk_startfault_done((word_t)fault_rec, 0, 0); return;
                    }
                    goto badres;
                }
                DAT_006ad310 = DAT_006ad310 + 1;
                if (a3 == 0) { DAT_006ad314 = DAT_006ad314 + 1;
                    sk_startfault_done((word_t)fault_rec, 0, 0); return; }
                CallSupervisor(0); *tp = 0; CallSupervisor(1);
                FUN_004b377c(0, *faulting);
coalesce:
                DAT_006ad334 = DAT_006ad334 + 1;
                do { CallSupervisor(4); } while (*(word_t *)(vspace + 0x98) == 1);
                word_t r = (*(word_t **)*(word_t *)(dom + 0xb8))
                    (*(word_t *)(dom + 0xb0), 0x11, leaf, *(word_t *)(vspace + 0x98), 0);
                if ((r & 0xff) == 0) {
                    word_t r2 = sk_span_map_page_walk(*(word_t *)(vspace + 0x58),
                        *(word_t *)(vspace + 0x60), *(word_t *)(vspace + 0x98), 0, 0, 0, 0);
                    if ((r2 & 0xff) != 0) goto badres;
                    word_t r3 = *(word_t *)(vspace + 0x98);
                    do { CallSupervisor(4); } while (r3 == 1);
                    if ((r3 & 0xff) == 0) {
                        DAT_006ad33c = DAT_006ad33c + 1;
                        sk_span_map_page_walk(span, faddr, *(word_t *)(vspace + 0x68), 0, 0, 0, 0);
                        word_t r4 = *(word_t *)(vspace + 0x68);
                        do { CallSupervisor(4); } while (r4 == 1);
                        if ((r4 & 0xff) == 0) { sk_startfault_done((word_t)fault_rec, 0, 0); return; }
                        goto badres;
                    }
                } else goto badres;
            }
        }
        FUN_004b3a08();
        goto badres;
    } else FUN_004b3a30();
    FUN_004b3a08();
badres:
    FUN_004afae4("VAS SPANFAULT CBRESULT VALID COW");
abort:
    FUN_004afae4("abort spanmap_lock");
}

/* helper: fold the fault result into the fault record then return */
static void sk_startfault_done(word_t rec, word_t err, word_t e2)
{
    *(word_t *)(rec + 0x28) = err;
    *(word_t *)(rec + 0x30) = e2;
    FUN_0011d7e8(err, e2);
}


/* ================================================================== *
 * Shadow-space / page-table-level setup (FUN_00041308, 0004137c, 000413c4,
 * 00041434, 0004158c, 00041d9c, 00041f8c, 00041fbc, 00042754, 00042808,
 * 00042abc, 00042c20, 00042d04, 00042ed0, 000436fc, 00043780) and vspace
 * read/notify/next/lookup wrappers (00038220, 0003838c, 00038390, 000383dc,
 * 000384c4, 0003859c, 0003c09c, 0003c0e4, 0003c510, 0003dbc0).
 * ================================================================== */

/* FUN_00038220 @ 0x38220  (est. sk_vspace_read)
 * Read bytes out of a vspace (copy-out from a mapped region): locate the span
 * covering param_2, walk its leaf pages (sk_vspace_map_phys) in 16 KB steps,
 * and verify the target window stays in-bounds. Writes the resulting (ptr,
 * len) into param_3/param_4. Returns an error code.
 * Confidence: medium */
static word_t sk_vspace_read(word_t a1, word_t addr, word_t *out_ptr, word_t *out_len)
{
    word_t local[11];
    int i;
    for (i = 0; i < 11; i++) local[i] = (i == 10) ? (word_t)-1 : 0;
    word_t want = *out_len;
    sk_vspace_lock_enter(local, a1, 0, 0);
    word_t span = sk_vspace_find_region(local, addr);
    if (span != 0) {
        if (span + 0xb0 < span) SK_FATAL();
        if (*(int *)(span + 0x20) != 0) {
            word_t avail = (*(word_t *)(span + 8) - addr) + *(word_t *)(span + 0x10);
            if (avail <= want) want = avail;
            sk_vspace_lock_exit(local, a1);
            word_t r = sk_vspace_map_phys(span, addr, &local[10]).lo;
            if ((r & 0xff) != 0) return r;
            local[10] = local[10] + (addr & 0x3fff);
            *out_ptr = local[10];
            word_t off = -(addr & 0x3fff);
            while (off = off + 0x4000, off < want) {
                word_t pg = 0;
                if ((sk_vspace_map_phys(span, addr + off, &pg).lo & 0xff) != 0 ||
                    off + local[10] != pg) break;
            }
            if (want <= off) off = want;
            *out_len = off;
            return 0;
        }
    }
    sk_vspace_lock_exit(local, a1);
    return 0x9580001;
}

/* FUN_0003838c @ 0x3838c  (est. sk_vspace_notify) */
static void sk_vspace_notify(void)
{
    word_t ctx = FUN_00032cd0();
    FUN_00042abc(ctx, 2, 0);
}

/* FUN_00038390 @ 0x38390  (est. sk_vspace_notify2) */
static void sk_vspace_notify2(void)
{
    word_t ctx = FUN_00032cd0();
    FUN_00042abc(ctx, 2, 0);
}

/* FUN_000383dc @ 0x383dc  (est. sk_vspace_next_span)
 * Advance to the next live span of the current vspace: locks the vspace, walks
 * the span tree, and returns the next non-empty region (type 0x65b648).
 * Decrements the live-span counter if no region remains.
 * Confidence: medium */
static sk_pair_t sk_vspace_next_span(word_t a1)
{
    DAT_006af198 = DAT_006af198 + 1;
    word_t local[10];
    int i;
    for (i = 0; i < 10; i++) local[i] = 0;
    sk_vspace_lock_enter(local, a1, 0, 0);
    if (local[0] <= local[0] + 0x2a0) {
        word_t root = FUN_00032cec();
        word_t node = *(word_t *)root;
        while (node != 0 && *(word_t *)(node + 0x58) != 0) node = *(word_t *)(node + 0x58);
        if (node != 0 && node + 0xb0 >= node) {
            if (*(int *)(node + 0x20) != 0) {
                word_t found = sk_vspace_find_nonempty((word_t)local, node);
                sk_vspace_lock_exit(local, a1);
                if (found == 0) DAT_006af198 = DAT_006af198 - 1;
                return (sk_pair_t){ found, 0x65b648 };
            }
        }
    }
    SK_FATAL();
}

/* FUN_000384c4 @ 0x384c4  (est. sk_vspace_span_lookup)
 * Look up a span by address param_2 in vspace param_1 and copy out its 4-word
 * descriptor into param_4 (plus flags into param_3). Returns {span, type}.
 * Confidence: medium */
static sk_pair_t sk_vspace_span_lookup(word_t *rec, word_t addr, int *flags,
                                       word_t *out)
{
    word_t local[9];
    int i;
    for (i = 0; i < 9; i++) local[i] = 0;
    sk_vspace_lock_enter(local, rec[0], 0, 0);
    word_t span = sk_vspace_find_region(local, addr);
    word_t hi;
    if (span == 0) hi = 0;
    else {
        if (span + 0x16 < span) SK_FATAL();
        if (*(int *)(span + 4) == 0) { hi = 0; span = 0; }
        else {
            if (span + 0x16 <= span) SK_FATAL();
            if (flags) *flags = *(int *)(span + 4);
            if (out) {
                word_t a = *(word_t *)span, b = span[3], c = span[2];
                out[1] = span[1]; out[0] = a; out[3] = b; out[2] = c;
            }
            hi = 0x65b648;
        }
    }
    sk_vspace_lock_exit(local, rec[0]);
    return (sk_pair_t){ span, hi };
}

/* FUN_0003859c @ 0x3859c  (est. sk_vspace_enter_el2)
 * Enter the two-stage (EL2) context for span param_2: validate the span, set
 * the per-cpu EL2 pointer (tpidrro_el0) and CallSupervisor(3). In single-vspace
 * mode (param_3 == 1) requires the span not be a leaf. Returns 0 or an error.
 * Confidence: medium */
static word_t sk_vspace_enter_el2(word_t a1, word_t span, int mode)
{
    word_t ptr = 0, r = 0;
    word_t err = sk_vspace_lookup_map(a1, span, &ptr, &r).lo;
    if ((err & 0xff) == 0) {
        if (mode == 1 && ((*(uint8_t *)(r + 0x20) >> 3 & 1) == 0)) err = 0x9cb0001;
        else {
            word_t *tp = (word_t *)tpidrro_el0;
            *tp = (word_t)(mode == 1);
            CallSupervisor(3);
            err = (ptr == 0) ? 0 : (ptr & 0x7fff) << 0x10 | 0x80000001;
        }
    }
    return err;
}

/* FUN_0003c09c @ 0x3c09c  (est. sk_vspace_region_init)
 * Initialize the vspace region geometry: resolve the current context, fetch the
 * address limits, and apply them.
 * Confidence: low */
static void sk_vspace_region_init(void)
{
    word_t ctx = FUN_00032514();
    sk_pair_t limits = FUN_000411dc(0, 0);
    sk_vspace_region_apply(ctx, limits.lo, limits.hi);
}

/* FUN_0003c0e4 @ 0x3c0e4  (est. sk_vspace_region_apply)
 * Record the [param_2, param_3) address limits into vspace param_1 and create
 * the root span node covering that range, inserting it into the span tree.
 * Confidence: medium */
static void sk_vspace_region_apply(word_t vspace, word_t lo, word_t hi)
{
    word_t local[9];
    int i;
    for (i = 0; i < 9; i++) local[i] = 0;
    word_t r = sk_lock_collection_alloc(local, vspace, 1, 0, 0, 0);
    if ((r & 1) == 0) SK_ABORT("VAS abort");
    sk_lock_collection_attach((word_t *)local, (word_t *)vspace, 0, 0);
    word_t *node = sk_lock_pop_primary((word_t)local);
    word_t size = hi - lo;
    if (lo <= hi && size != 0) {
        *(word_t *)(vspace + 0x28) = lo;
        *(word_t *)(vspace + 0x30) = hi;
        if (node <= node + 0x16) {
            node[0] = 0; node[1] = lo; node[2] = size;
            node[4] = 0; node[3] = 0; node[6] = 0; node[5] = 0;
            node[8] = 0; node[7] = 0; node[9] = 0; node[10] = vspace;
            node[0xb] = 0; node[0xc] = 0; node[0xd] = size;
            node[0xf] = 0; node[0xe] = 0; node[0x11] = 0; node[0x10] = 0;
            node[0x13] = 0; node[0x12] = 0; node[0x15] = 0; node[0x14] = 0;
            sk_span_tree_insert_caller((word_t *)local, (word_t)node);
            sk_vspace_lock_exit(local, vspace);
            return;
        }
        SK_FATAL();
    }
    SK_ABORT("VAS abort");
}

/* FUN_0003c510 @ 0x3c510  (est. sk_vspace_region_map_wrapper)
 * Thin wrapper: resolve the current context then call the region factory.
 * Confidence: medium */
static void sk_vspace_region_map_wrapper(word_t a1, word_t a2, word_t a3,
                                         word_t a4, word_t a5)
{
    word_t ctx = FUN_00032514();
    sk_vspace_region_create(ctx, (uint32_t)a1, (char *)a2, (word_t *)a3,
                            (uint32_t *)a4, (word_t *)a5);
}

/* FUN_0003dbc0 @ 0x3dbc0  (est. sk_vspace_lookup_map)
 * Look up the span covering address param_2 and resolve its physical mapping
 * cookie: walk the leaf, returning {cookie, span}. Used by EL2 enter / map.
 * Confidence: medium */
static sk_pair_t sk_vspace_lookup_map(word_t a1, word_t addr, word_t *cookie,
                                      word_t *span_out)
{
    word_t local[9];
    int i;
    for (i = 0; i < 9; i++) local[i] = 0;
    sk_vspace_lock_enter(local, a1, 0, 0);
    word_t span = sk_vspace_find_region(local, addr);
    sk_vspace_lock_exit(local, a1);
    if (span == 0) return (sk_pair_t){ 0x9b10001, 0 };
    if (span + 0xb0 < span || span + 0x90 < span + 0x80) SK_FATAL();
    if (FUN_00118164((void *)(span + 0x80)) != 0) SK_ABORT("VAS abort");
    word_t l[5] = {0,0,0,0,0};
    word_t dom = FUN_00032cd0(*(word_t *)(span + 0x50));
    FUN_000287e4(l, *(word_t *)(span + 0x78),
        (int)((word_t)(addr - *(word_t *)(dom + 0x28)) >> 0xe) + 1);
    *(word_t *)(span + 0x78) = l[4];
    if (FUN_00118194((void *)(span + 0x80)) != 0) SK_ABORT("VAS abort");
    if (l[0] == 0) {
        if ((int8_t)l[1] != 0) { /* re-walk (collapsed) */ }
        return (sk_pair_t){ 0x9a90002, 0 };
    }
    *cookie = l[0];
    if (span_out) *span_out = span;
    return (sk_pair_t){ 0, 0 };
}


/* FUN_00041308 @ 0x41308  (est. sk_vspace_geometry_init)
 * One-time geometry setup: lazily initializes the vspace zone (FUN_0005baac
 * size 4/0xc) and the address-space limits from FUN_0005530c/60/44, then
 * returns the page-level count from the shadow-space record.
 * Confidence: medium */
static uint8_t sk_vspace_geometry_init(void)
{
    if ((DAT_006af2b8 & 1) == 0) {
        word_t z = FUN_0005baac(4, 0xc);
        if (z == 0) {
            DAT_006af2b9 = FUN_0005530c();
            DAT_006af2ba = FUN_00055360();
            DAT_006af2bb = FUN_00055344();
            FUN_0005ba5c((word_t)&DAT_0064cba0);
        }
        DAT_006af2b8 = 1;
    }
    uint8_t *rec = (uint8_t *)FUN_00041f8c();
    return *rec;
}

/* FUN_0004137c @ 0x4137c  (est. sk_vspace_limit)
 * Return the address-space low limit for mode param_1 (0..2) from a table.
 * Confidence: medium */
static word_t sk_vspace_limit(uint32_t mode)
{
    if (mode < 3) return *(word_t *)((word_t)&DAT_004bc520 + (word_t)mode * 8);
    FUN_004afae4("VAS abort");
}

/* FUN_000413c4 @ 0x413c4  (est. sk_vspace_limit_hi)
 * Return the address-space high limit for mode param_1: fixed 0x1000000000 for
 * mode 0, 0x40000000000 for mode 2, and 1<<(shadow+1) for mode 1.
 * Confidence: medium */
static word_t sk_vspace_limit_hi(int mode)
{
    if (mode == 0) return 0x1000000000;
    if (mode == 2) return 0x40000000000;
    if (mode != 1) FUN_004afae4("VAS abort");
    word_t rec = FUN_00041f8c();
    return (word_t)1 << (*(uint8_t *)(rec + 1) & 0x3f);
}

/* FUN_00041434 @ 0x41434  (est. sk_vspace_layout_compute)
 * Compute the shadow-space (page-table level array) layout for a vspace: given
 * the mode param_2, base param_3, size param_4 and domain callbacks
 * param_5/param_6, fill the level descriptor table at param_1+0x38 (0x18-byte
 * entries per level) and return the total table size. The level count derives
 * from the geometry (mode 1) or is 2/3 for modes 0/2.
 * Confidence: low */
static word_t sk_vspace_layout_compute(word_t rec, int mode, word_t base,
                                       word_t size, word_t cb1, word_t cb2)
{
    *(uint8_t *)(rec + 0x98) = (char)mode;
    *(word_t *)(rec + 0x28) = base;
    *(word_t *)(rec + 0x30) = size;
    *(word_t *)(rec + 0xb0) = cb1;
    *(word_t *)(rec + 0xb8) = cb2;
    word_t levels;
    if (mode == 0) levels = 2;
    else if (mode == 2) levels = 3;
    else {
        if (mode != 1) FUN_004afae4("VAS abort");
        word_t g = FUN_00041f8c();
        word_t t = (word_t)*(uint8_t *)(g + 1) - 0xe;
        levels = t / 0xb;
        if (t % 0xb != 0) levels = levels + 1;
    }
    word_t total = 0, idx = 0, shift = 0;
    do {
        word_t *slot = (word_t *)(rec + 0x38) + idx * 3;
        if (slot < (word_t *)(rec + 0x38) || (word_t *)(rec + 0x98) < slot + 3 || slot + 3 < slot)
            SK_FATAL();
        word_t mask = ((word_t)-1 << ((word_t)((int)shift * 0xb + 0x16) & 0x3f)) & base;
        word_t count = (size + ~((word_t)-0x4000 << (idx * 0xb & 0x3f))) - mask
            >> (idx * 0xb + 0xe & 0x3f);
        slot[1] = mask;
        slot[2] = count;
        word_t add = (count & 0xff) ? 0x100 : 0;
        total += (add + (count & 0x3ffffffffffff00)) * 0x40;
        idx = (word_t)((int)shift + 1);
        shift = idx;
    } while ((uint8_t)idx <= levels);
    return total;
}

/* FUN_0004158c @ 0x4158c  (est. sk_vspace_init)
 * Initialize the shadow-space and page-table-level state: lazily init the
 * vspace zone, compute the layout, walk the cap table (FUN_00053470) rewriting
 * cap type tags to their vspace level indices, then fill the level slot arrays
 * with fresh PMM allocations. Registers the vspace callback (FUN_000446ec) and
 * re-walks the caps to fix up mappings. Marks init done (byte at +0x100).
 * Confidence: low (large one-time init) */
static void sk_vspace_init(word_t a1, word_t a2, word_t a3)
{
    word_t z = FUN_0005baac(4, 0xb);
    if (z == 0) {
        DAT_006af298 = (word_t)&DAT_0064c450;
        FUN_0005ba5c((word_t)&DAT_0064cb80);
    }
    word_t rec = FUN_0005acac(0x6af2b0, 4, 0xb);
    if ((*(uint8_t *)(rec + 0x100) & 1) != 0) return;
    word_t vspace = *(word_t *)(rec + 0xf8);
    if (vspace <= vspace + 0xd0) {
        sk_pair_t lo = FUN_000411dc(0, 0);
        sk_pair_t cb = FUN_0004ba18();
        FUN_00041434(vspace, 0, lo.lo, lo.hi, cb.lo, cb.hi);
        if (*(word_t *)(vspace + 0x48) >> 0xe == 0) FUN_004afae4("VAS abort");
        word_t node = FUN_00053470();
        word_t rec2 = FUN_0005acac(0x6af2b0, 4, 0xb);
        word_t vspace2 = *(word_t *)(rec2 + 0xf8);
        if (vspace2 <= vspace2 + 0xd0) {
            word_t *mode_p = (word_t *)(vspace2 + 0x98);
            char mode = *(char *)mode_p;
            word_t levels;
            if (mode == 0) levels = 2;
            else if (mode == 2) levels = 3;
            else {
                if (mode != 1) FUN_004afae4("VAS abort");
                word_t g = FUN_00041f8c();
                word_t t = (word_t)*(uint8_t *)(g + 1) - 0xe;
                levels = t / 0xb;
                if (t % 0xb != 0) levels = levels + 1;
            }
            if (node != (word_t)-1) {
                word_t *last_slot = (word_t *)(vspace2 + 0x38) + levels * 3;
                do {
                    if (node + 0x800 < node) SK_FATAL();
                    word_t cnt = *(word_t *)node;
                    if (cnt != 0) {
                        word_t *e = node + 4;
                        do {
                            if (e != 0 && (e < node + 4 || node + 0x800 < e + 4 || e + 4 < e)) SK_FATAL();
                            if (mode != 2) {
                                word_t cap = *e;
                                uint8_t type = (uint8_t)(cap >> 0x38);
                                if (mode == 1) {
                                    if ((cap >> 0x38 == 0x11) || (FUN_00041f8c() + 2) == type) {
                                        FUN_004b3af4(); SK_FATAL();
                                    }
                                } else {
                                    if (mode != 0) SK_FATAL();
                                    uint8_t t2 = type - 4;
                                    if (((t2 & 0xff) < 0xe) && ((0x3f01U >> (t2 & 0x1f) & 1) != 0) &&
                                        *(word_t *)((word_t)&DAT_004bc538 + (t2 & 0xff) * 8) == levels) {
                                        if (*last_slot == 0) *last_slot = cap & 0xffffffffffffff;
                                    }
                                }
                            }
                            e += 4; cnt -= 1;
                        } while (cnt != 0);
                    }
                    node = *(word_t *)node + 1;
                } while (node != (word_t)-1);
            }
            word_t hi = a2 + a3 * 0x40;
            word_t lo = hi - 0x4000;
            if ((word_t)(a3 * 0x40) < 0x4001) lo = a2;
            word_t *slots = (word_t *)(vspace2 + 0x38);
            word_t *top = slots + levels * 3;
            if (slots <= top && top + 3 <= mode_p && top <= top + 3) {
                if (*top == 0) FUN_004afae4("VAS abort");
                word_t k = levels - 1;
                if (k != 0) {
                    word_t *s = (word_t *)(vspace2 + levels * 0x18 + 0x20);
                    do {
                        if (s < slots || mode_p < s + 3 || s + 3 < s) SK_FATAL();
                        word_t n = s[2];
                        if (0xff < n) break;
                        if (hi - lo < n) FUN_004afae4("VAS abort");
                        hi += n * -0x40;
                        *s = hi;
                        k -= 1; s -= 3;
                    } while (k != 0);
                }
                if (hi - lo < 0x240) FUN_004afae4("VAS abort");
                word_t i = 0;
                do {
                    word_t *a = (word_t *)(rec + i + 0x30);
                    word_t *b = (word_t *)(rec + i + 0x38);
                    if ((word_t *)(rec + 0x60) < b || b < a) SK_FATAL();
                    *a = hi; hi -= 0x40; i += 8;
                } while (i != 0x30);
                i = 0;
                *(word_t *)(rec + 0x78) = 6;
                *(uint8_t *)(rec + 0x101) = 6;
                word_t *p = (word_t *)(rec + 0x60);
                do {
                    if ((word_t *)(rec + 0x78) < p + 1 || p + 1 < p) SK_FATAL();
                    *p = hi + i; i += -0x40; p += 1;
                } while (i != -0xc0);
                *(word_t *)(rec + 0x80) = 3;
                if (rec <= rec + 0x110) {
                    FUN_00034b10(rec, FUN_000446ec, 0);
                    for (word_t *n2 = (word_t *)FUN_00053470(); n2 != (word_t *)-1; n2 = (word_t *)n2[1]) {
                        if (n2 + 0x800 < n2) SK_FATAL();
                        word_t c = *n2;
                        if (c != 0) {
                            word_t *e = n2 + 4;
                            do {
                                if (e != 0 && (e < n2 + 4 || n2 + 0x800 < e + 4 || e + 4 < e)) SK_FATAL();
                                char m = *(char *)mode_p;
                                if (m != 2) {
                                    word_t cap = *e;
                                    char t2 = (char)(cap >> 0x38);
                                    if (m == 1) {
                                        if ((cap >> 0x38 == 0x11) || (FUN_00041f8c() + 2) == (uint8_t)t2) {
                                            FUN_004b3af4(); SK_FATAL();
                                        }
                                    } else {
                                        if (m != 0) SK_FATAL();
                                        if (((uint8_t)(t2 - 0xc) < 5) &&
                                            levels < *(word_t *)((word_t)&DAT_004bc5a8 + (uint8_t)(t2 - 0xc) * 8)) {
                                            word_t want = cap & 0xffffffffffffff;
                                            word_t lv = *(word_t *)((word_t)&DAT_004bc5a8 + (uint8_t)(t2 - 0xc) * 8);
                                            word_t got = FUN_00042abc(vspace2, lv, (e[2] & 0xffffffffff) << 0xc);
                                            if (want != got) {
                                                CallSupervisor(1);
                                                if ((cap & 0xff) != 0) { FUN_004b3b08(want, NULL); SK_FATAL(); }
                                                *e = got & 0xffffffffffffff |
                                                     (word_t)*(uint8_t *)((word_t)e + 7) << 0x38;
                                            }
                                        }
                                    }
                                }
                                e += 4; c -= 1;
                            } while (c != 0);
                        }
                    }
                    for (word_t *n3 = (word_t *)FUN_00053470(); n3 != (word_t *)-1; n3 = (word_t *)n3[1]) {
                        word_t c = *n3;
                        if (c != 0) {
                            word_t k2 = 0;
                            word_t *e = n3 + 4;
                            do {
                                if (e != 0 && (e < n3 + 4 || n3 + 0x800 < e + 4 || e + 4 < e)) SK_FATAL();
                                char m = *(char *)(vspace2 + 0x98);
                                if (m != 2) {
                                    word_t cap = *e;
                                    char t2 = (char)(cap >> 0x38);
                                    if (m == 1) {
                                        if ((cap >> 0x38 == 0x11) || (FUN_00041f8c() + 2) == (uint8_t)t2) {
                                            FUN_004b3af4(); SK_FATAL();
                                        }
                                    } else {
                                        if (m != 0) SK_FATAL();
                                        if ((uint8_t)(t2 - 0xc) < 5) {
                                            word_t want = cap & 0xffffffffffffff;
                                            word_t lv = *(word_t *)((word_t)&DAT_004bc5a8 + (uint8_t)(t2 - 0xc) * 8);
                                            word_t got = FUN_00042abc(vspace2, lv, (e[2] & 0xffffffffff) << 0xc);
                                            if (want != got) {
                                                CallSupervisor(1);
                                                if ((cap & 0xff) == 5) {
                                                    if ((FUN_00042c20(vspace2, got) & 1) == 0) {
                                                        FUN_004b3b64(want, NULL); SK_FATAL();
                                                    }
                                                    CallSupervisor(1);
                                                }
                                                if ((cap & 0xff) != 0) { FUN_004b3b64(want, NULL); SK_FATAL(); }
                                                *e = got & 0xffffffffffffff |
                                                     (word_t)*(uint8_t *)((word_t)e + 7) << 0x38;
                                            }
                                        }
                                    }
                                }
                                k2 += 1; e += 4;
                            } while (c != k2);
                        }
                    }
                    *(uint8_t *)(rec + 0x100) = 1;
                    return;
                }
            }
        }
    }
    SK_FATAL();
}

/* FUN_00041d9c @ 0x41d9c  (est. sk_vspace_teardown_layout)
 * Release every PMM allocation backing the shadow-space level slots (the
 * 0x30..0x78 array) and then free the per-level spans for each level of the
 * vspace, tearing down the page-table buffers.
 * Confidence: low */
static void sk_vspace_teardown_layout(void)
{
    word_t slot = 0x30;
    do {
        word_t rec = FUN_0005acac(0x6af2b0, 4, 0xb);
        word_t *p = (word_t *)(rec + slot);
        if ((word_t *)(rec + 0x60U) < p + 1 || p + 1 < p) SK_FATAL();
        FUN_00034334(*p);
        slot += 8;
    } while (slot != 0x60);
    slot = 0x60;
    do {
        word_t rec = FUN_0005acac(0x6af2b0, 4, 0xb);
        word_t *p = (word_t *)(rec + slot);
        if ((word_t *)(rec + 0x78U) < p + 1 || p + 1 < p) SK_FATAL();
        FUN_00034334(*p);
        slot += 8;
    } while (slot != 0x78);
    word_t rec = FUN_0005acac(0x6af2b0, 4, 0xb);
    word_t vspace = *(word_t *)(rec + 0xf8);
    if (vspace <= vspace + 0xd0) {
        char *mode_p = (char *)(vspace + 0x98);
        char mode = *mode_p;
        word_t levels;
        if (mode == 0) levels = 1;
        else if (mode == 2) levels = 2;
        else {
            if (mode != 1) FUN_004afae4("VAS abort");
            word_t g = FUN_00041f8c();
            word_t t = (word_t)*(uint8_t *)(g + 1) - 0xe;
            word_t q = t / 0xb;
            if (t % 0xb != 0) q = q + 1;
            levels = q - 1;
        }
        char *slotp = (char *)(vspace + 0x38);
        char *endp = slotp + levels * 0x18;
        if (slotp <= endp && endp + 0x18 <= mode_p && endp <= endp + 0x18) {
            do {
                word_t count = *(word_t *)(vspace + 0x48 + levels * 0x18);
                if (0xff < count) return;
                if (count != 0) {
                    word_t p = *(word_t *)(slotp + levels * 0x18);
                    do { FUN_00034334(p); p += 0x40; count -= 1; } while (count != 0);
                }
                levels -= 1;
                endp = slotp + levels * 0x18;
            } while (slotp <= endp && endp + 0x18 <= mode_p && endp <= endp + 0x18);
        }
    }
    SK_FATAL();
}


/* FUN_00041f8c @ 0x41f8c  (est. sk_shadow_space_setup)
 * Build the shadow space (page-table level array) for the current domain:
 * lazily init the geometry, compute the layout, allocate the level slot
 * buffers from the PMM, install the vspace callbacks, and populate the first
 * level (with the "shadow" flag 0xfb / 0xfc). Used at vspace creation.
 * Confidence: low (large multi-path init) */
static void sk_shadow_space_setup(word_t a3, word_t a4, word_t a5, word_t a6,
                                  word_t a7, word_t a8)
{
    if ((DAT_006af2b8 & 1) != 0) { FUN_0005acac(0x6af2c0, 4, 0xc); return; }
    sk_pair_t sp = FUN_004b3bc0();
    word_t rec = sp.lo;
    int mode = sp.hi & 0xffffffff;
    if (mode == 1 && (FUN_00041308() & 1) == 0) { FUN_004b3bf8(); return; }
    word_t table = FUN_00041434(rec, (sp.hi >> 32) & 0xff, a5, a6, a7, a8);
    word_t *mode_p = (word_t *)(rec + 0x98);
    char c = *(char *)mode_p;
    *(word_t *)(rec + 0x18) = a3;
    *(word_t *)(rec + 0x20) = a4;
    word_t levels;
    if (c == 0) levels = 2;
    else if (c == 2) levels = 3;
    else {
        if (c != 1) FUN_004afae4("VAS abort");
        word_t g = FUN_00041f8c();
        word_t t = (word_t)*(uint8_t *)(g + 1) - 0xe;
        levels = t / 0xb;
        if (t % 0xb != 0) levels = levels + 1;
    }
    *(uint32_t *)(rec + 0xc0) = 0;
    if (FUN_00118148((void *)(rec + 0xa0), 0) != 0) SK_ABORT("VAS abort");
    word_t desc[3] = { 4, 0, table };
    if (table < 0x4001) desc[2] = 0x4000;
    uint8_t flag = (mode != 1) ? 0xfc : 0xfb;
    word_t cb = FUN_00034a2c();
    word_t r = (*(word_t **)(cb + 8) + 6)(*(word_t *)cb, 0, &desc, rec, 0, &desc);
    r &= 0xff;
    if (r != 0) SK_FATAL();
    *(word_t *)(rec + 0x10) = desc[0];
    if (levels != 0) {
        word_t acc = 0;
        word_t *slot = (word_t *)(rec + 0x38);
        word_t i = levels;
        do {
            if (slot < (word_t *)(rec + 0x38) || mode_p < slot + 3 || slot + 3 < slot) SK_FATAL();
            *slot = desc[0] + acc * 0x40;
            acc = slot[2] + acc;
            slot += 3; i -= 1;
        } while (i != 0);
        if (table <= (word_t)(acc * 0x40) && acc * 0x40 - table != 0) FUN_004afae4("VAS abort");
    }
    if (a3 != 0) {
        if (mode != 2) {
            if (mode == 1) {
                if (a4 == 0) {
                    a4 = FUN_00034f70();
                    if (a4 == 0) { FUN_004b3c24(); FUN_004afae4("VAS abort"); }
                    word_t g = FUN_00041f8c();
                    uint8_t rt = *(uint8_t *)(g + 2);
                    while (true) {
                        word_t r2 = (*(word_t **)*(word_t *)(rec + 0xb8))
                            (*(word_t *)(rec + 0xb0), rt, a4, a4, *(uint32_t *)(rec + 0xc0));
                        if ((r2 & 0xff) != 0) {
                            word_t buf[32];
                            sk_l4_error_string(buf);
                            FUN_004b3a58(0xeb1a02bf914012ba, 0, "AppleInternal Library BuildRoot", 0x20e,
                                "vas_core_shadow_space_setup", "%s %zu pmm_alloc_flags_with_pm");
                            sk_l4_error_string(buf, r2);
                            FUN_004afae4("Unexpected L4 Error: %s %zu err");
                        }
                        r2 = FUN_000553e4(a3, a4);
                        if (r2 == 0) break;
                        if ((*(uint32_t *)(rec + 0xc0) & 1) != 0) break;
                        *(uint32_t *)(rec + 0xc0) = *(uint32_t *)(rec + 0xc0) | 1;
                        (*(word_t **)(*(word_t *)(rec + 0xb8) + 0x10))(*(word_t *)(rec + 0xb0), a4);
                        rt = *(uint8_t *)(g + 2);
                    }
                    if ((r2 & 0xff) != 0) {
                        word_t buf[32];
                        sk_l4_error_string(buf);
                        FUN_004b3a58(0xeb1a02bf914012ba, 0, "AppleInternal Library BuildRoot", 0x21a,
                            "vas_core_shadow_space_setup", "%s %zu xrt plat Dart SetRoot");
                        sk_l4_error_string(buf, r2);
                        FUN_004afae4("Unexpected L4 Error: %s %zu err");
                    }
                }
                word_t *slot = (word_t *)(rec + 0x38) + levels * 3;
                if ((word_t *)(rec + 0x38) <= slot && slot + 3 <= mode_p && slot <= slot + 3) {
                    *slot = a4;
                    return;
                }
                SK_FATAL();
            }
            if (mode != 0) FUN_004afae4("VAS abort");
        }
        word_t *slot = (word_t *)(rec + 0x38) + levels * 3;
        if ((word_t *)(rec + 0x38) <= slot && slot + 3 <= mode_p && slot <= slot + 3) {
            *slot = a3;
            return;
        }
        SK_FATAL();
    }
    if (((sp.hi >> 32) & 0xfffffffd) != 0) FUN_004afae4("VAS abort");
    word_t pm = FUN_00034f70();
    word_t *slot = (word_t *)(rec + 0x38) + levels * 3;
    if (slot < (word_t *)(rec + 0x38) || mode_p < slot + 3 || slot + 3 < slot) SK_FATAL();
    *slot = pm;
    if (pm != 0) {
        if (mode != 2) {
            char m = *(char *)mode_p;
            word_t type;
            if (m == 2) type = 0;
            else if (m == 1) {
                if (2 < levels - 1) FUN_004afae4("VAS abort");
                word_t g = FUN_00041f8c();
                type = (word_t)*(uint8_t *)(g + 2);
            } else {
                if (m != 0) { FUN_004b3c4c(); FUN_004afae4("VAS abort"); }
                type = (levels < 4) ? 0xc0d0e04 >> (((uint32_t)levels & 3) << 3) : 4;
            }
            word_t r2 = (*(word_t **)*(word_t *)(rec + 0xb8))
                (*(word_t *)(rec + 0xb0), type & 0xff, pm, pm, 0);
            if ((r2 & 0xff) != 0) {
                word_t buf[32];
                sk_l4_error_string(buf);
                FUN_00042754(rec, levels);
                FUN_004b3a58(0xeb1a02bf914012ba, 0, "AppleInternal Library BuildRoot", 0x237,
                    "vas_core_shadow_space_setup", "%s %zu pmm_alloc %d 0x%lx");
                sk_l4_error_string(buf, r2);
                FUN_004afae4("Unexpected L4 Error: %s %zu err");
            }
        }
        return;
    }
    FUN_004b3c4c();
    FUN_004afae4("VAS abort");
}

/* FUN_00041fbc @ 0x41fbc  (est. sk_shadow_space_setup_v2)
 * Variant of sk_shadow_space_setup taking an explicit shadow-space record
 * param_1 instead of resolving the current domain. Identical layout logic.
 * Confidence: low */
static void sk_shadow_space_setup_v2(word_t rec, word_t mode, word_t a3,
                                     word_t a4, word_t a5, word_t a6,
                                     word_t a7, word_t a8, uint32_t a9)
{
    int mi = (int)mode;
    if (mi == 1 && (FUN_00041308() & 1) == 0) { FUN_004b3bf8(); return; }
    word_t table = FUN_00041434(rec, mode, a5, a6, a7, a8);
    word_t *mode_p = (word_t *)(rec + 0x98);
    char c = *(char *)mode_p;
    *(word_t *)(rec + 0x18) = a3;
    *(word_t *)(rec + 0x20) = a4;
    word_t levels;
    if (c == 0) levels = 2;
    else if (c == 2) levels = 3;
    else {
        if (c != 1) FUN_004afae4("VAS abort");
        word_t g = FUN_00041f8c();
        word_t t = (word_t)*(uint8_t *)(g + 1) - 0xe;
        levels = t / 0xb;
        if (t % 0xb != 0) levels = levels + 1;
    }
    *(uint32_t *)(rec + 0xc0) = a9;
    if (FUN_00118148((void *)(rec + 0xa0), 0) != 0) SK_ABORT("VAS abort");
    word_t desc[3] = { 4, 0, table };
    if (table < 0x4001) desc[2] = 0x4000;
    word_t cb = FUN_00034a2c();
    word_t r = (*(word_t **)(cb + 8) + 6)(*(word_t *)cb, 0, &desc, rec, 0, &desc);
    r &= 0xff;
    if (r != 0) SK_FATAL();
    *(word_t *)(rec + 0x10) = desc[0];
    if (levels != 0) {
        word_t acc = 0;
        word_t *slot = (word_t *)(rec + 0x38);
        word_t i = levels;
        do {
            if (slot < (word_t *)(rec + 0x38) || mode_p < slot + 3 || slot + 3 < slot) SK_FATAL();
            *slot = desc[0] + acc * 0x40;
            acc = slot[2] + acc;
            slot += 3; i -= 1;
        } while (i != 0);
        if (table <= (word_t)(acc * 0x40) && acc * 0x40 - table != 0) FUN_004afae4("VAS abort");
    }
    if (a3 != 0) {
        if (mi != 2) {
            if (mi == 1) {
                if (a4 == 0) {
                    a4 = FUN_00034f70();
                    if (a4 == 0) { FUN_004b3c24(); FUN_004afae4("VAS abort"); }
                    word_t g = FUN_00041f8c();
                    uint8_t rt = *(uint8_t *)(g + 2);
                    while (true) {
                        word_t r2 = (*(word_t **)*(word_t *)(rec + 0xb8))
                            (*(word_t *)(rec + 0xb0), rt, a4, a4, *(uint32_t *)(rec + 0xc0));
                        if ((r2 & 0xff) != 0) {
                            word_t buf[32];
                            sk_l4_error_string(buf);
                            FUN_004b3a58(0xeb1a02bf914012ba, 0, "AppleInternal Library BuildRoot", 0x20e,
                                "vas_core_shadow_space_setup", "%s %zu pmm_alloc_flags_with_pm");
                            sk_l4_error_string(buf, r2);
                            FUN_004afae4("Unexpected L4 Error: %s %zu err");
                        }
                        r2 = FUN_000553e4(a3, a4);
                        if (r2 == 0) break;
                        if ((*(uint32_t *)(rec + 0xc0) & 1) != 0) break;
                        *(uint32_t *)(rec + 0xc0) = *(uint32_t *)(rec + 0xc0) | 1;
                        (*(word_t **)(*(word_t *)(rec + 0xb8) + 0x10))(*(word_t *)(rec + 0xb0), a4);
                        rt = *(uint8_t *)(g + 2);
                    }
                    if ((r2 & 0xff) != 0) {
                        word_t buf[32];
                        sk_l4_error_string(buf);
                        FUN_004b3a58(0xeb1a02bf914012ba, 0, "AppleInternal Library BuildRoot", 0x21a,
                            "vas_core_shadow_space_setup", "%s %zu xrt plat Dart SetRoot");
                        sk_l4_error_string(buf, r2);
                        FUN_004afae4("Unexpected L4 Error: %s %zu err");
                    }
                }
                word_t *slot = (word_t *)(rec + 0x38) + levels * 3;
                if ((word_t *)(rec + 0x38) <= slot && slot + 3 <= mode_p && slot <= slot + 3) {
                    *slot = a4; return;
                }
                SK_FATAL();
            }
            if (mi != 0) FUN_004afae4("VAS abort");
        }
        word_t *slot = (word_t *)(rec + 0x38) + levels * 3;
        if ((word_t *)(rec + 0x38) <= slot && slot + 3 <= mode_p && slot <= slot + 3) {
            *slot = a3; return;
        }
        SK_FATAL();
    }
    if ((mode & 0xfffffffd) != 0) FUN_004afae4("VAS abort");
    word_t pm = FUN_00034f70();
    word_t *slot = (word_t *)(rec + 0x38) + levels * 3;
    if (slot < (word_t *)(rec + 0x38) || mode_p < slot + 3 || slot + 3 < slot) SK_FATAL();
    *slot = pm;
    if (pm != 0) {
        if (mi != 2) {
            char m = *(char *)mode_p;
            word_t type;
            if (m == 2) type = 0;
            else if (m == 1) {
                if (2 < levels - 1) FUN_004afae4("VAS abort");
                word_t g = FUN_00041f8c();
                type = (word_t)*(uint8_t *)(g + 2);
            } else {
                if (m != 0) { FUN_004b3c4c(); FUN_004afae4("VAS abort"); }
                type = (levels < 4) ? 0xc0d0e04 >> (((uint32_t)levels & 3) << 3) : 4;
            }
            word_t r2 = (*(word_t **)*(word_t *)(rec + 0xb8))
                (*(word_t *)(rec + 0xb0), type & 0xff, pm, pm, 0);
            if ((r2 & 0xff) != 0) {
                word_t buf[32];
                sk_l4_error_string(buf);
                FUN_00042754(rec, levels);
                FUN_004b3a58(0xeb1a02bf914012ba, 0, "AppleInternal Library BuildRoot", 0x237,
                    "vas_core_shadow_space_setup", "%s %zu pmm_alloc %d 0x%lx");
                sk_l4_error_string(buf, r2);
                FUN_004afae4("Unexpected L4 Error: %s %zu err");
            }
        }
        return;
    }
    FUN_004b3c4c();
    FUN_004afae4("VAS abort");
}

/* FUN_00042754 @ 0x42754  (est. sk_level_pttype)
 * Return the page-table level type byte for level param_2 of vspace param_1:
 * mode-2 vspaces use type 0; mode-1 uses the geometry root type; mode-0 uses a
 * bitmasked nibble (0xc0d0e04 >> (level&3)*8, or 4 for level > 3).
 * Confidence: medium */
static uint32_t sk_level_pttype(word_t vspace, word_t level)
{
    char c = *(char *)(vspace + 0x98);
    uint32_t t;
    if (c == 2) t = 0;
    else if (c == 1) {
        if (2 < level - 1) FUN_004afae4("VAS abort");
        word_t g = FUN_00041f8c();
        t = (uint32_t)*(uint8_t *)(g + 2);
    } else {
        if (c != 0) FUN_004afae4("VAS abort");
        t = 0xc0d0e04 >> (((uint32_t)level & 3) << 3);
        if (3 < level) t = 4;
    }
    return t & 0xff;
}

/* FUN_00042808 @ 0x42808  (est. sk_vspace_destroy_levels)
 * Tear down the page-table levels of a shadow-space (param_1): for each level,
 * release the level-0 span mappings (via the +0x30 callback or the per-page
 * +0x10 callback), then free the shadow-space buffers and reset the record.
 * Returns 0 on success.
 * Confidence: low */
static word_t sk_vspace_destroy_levels(word_t *rec, word_t a2, word_t a3)
{
    word_t *mode_p = rec + 0x13;
    char c = *(char *)mode_p;
    word_t levels;
    if (c == 0) levels = 2;
    else if (c == 2) levels = 3;
    else {
        if (c != 1) FUN_004afae4("VAS abort");
        word_t g = FUN_00041f8c();
        word_t t = (word_t)*(uint8_t *)(g + 1) - 0xe;
        levels = t / 0xb;
        if (t % 0xb != 0) levels = levels + 1;
    }
    word_t lvl = 0, len = a3;
    do {
        word_t *slot = rec + 7 + lvl * 3;
        if (slot < rec + 7 || mode_p < slot + 3 || slot + 3 < slot) SK_FATAL();
        word_t base = *slot;
        len = slot[2];
        word_t vspace = rec[0x16];
        word_t ops = rec[0x17];
        word_t *cb = *(word_t **)(ops + 0x30);
        word_t count = len;
        if (cb == 0) {
            do {
                if (count == 0) break;
                word_t r = (*(word_t **)(ops + 0x10))(vspace, base);
                count -= 1;
                base += 0x40;
                if (r != 0x107 && r != 0) break;
            } while (true);
        } else {
            word_t r = (*cb)(vspace, base);
            if ((r & 0xff) != 0) { FUN_004b3c74(r, NULL); goto err; }
        }
        lvl += 1;
    } while (lvl != levels);
    if (rec[3] == 0 || (*mode_p == 1 && rec[4] == 0)) {
        word_t *slot = rec + 7 + levels * 3;
        if (slot < rec + 7 || mode_p < slot + 3 || slot + 3 < slot) SK_FATAL();
        word_t base = *slot;
        if (*mode_p != 2) {
            word_t r = (*(word_t **)(rec[0x17] + 0x10))(rec[0x16], base);
            if ((r & 0xff) != 0) {
                sk_pair_t sp = FUN_004b3cd0(r, NULL);
                word_t vspace = sp.lo;
                if (vspace == 0) FUN_004b3d2c();
                else {
                    word_t *s = (word_t *)(vspace + 0x38) + sp.hi * 3;
                    if (s < (word_t *)(vspace + 0x38) || (word_t *)(vspace + 0x98) < s + 3 || s + 3 < s)
                        SK_FATAL();
                    word_t idx = (word_t)(a3 - s[1]) >> (sp.hi * 0xb + 0xeU & 0x3f);
                    if (idx < (word_t)s[2]) {
                        word_t v = *s + idx * 0x40;
                        word_t r2 = FUN_0005acac(0x6af2b0, 4, 0xb);
                        if (vspace == *(word_t *)(r2 + 0xf8)) {
                            word_t n = *(word_t *)(r2 + 0xe8U);
                            if (n != 0) {
                                word_t i = *(word_t *)(r2 + 0xf0);
                                word_t *e = (word_t *)(r2 + i * 0x10);
                                do {
                                    word_t *en = e + (i / 6) * -0x60;
                                    if (en + 0x88U < (word_t *)(r2 + 0x88U) ||
                                        (word_t *)(r2 + 0xe8U) < en + 0x98U ||
                                        en + 0x98U < en + 0x88U) SK_FATAL();
                                    if (*(word_t *)(en + 0x90) == v)
                                        return *(word_t *)(e + (i / 6) * -0x60 + 0x88);
                                    e += 0x10; i += 1; n -= 1;
                                } while (n != 0);
                            }
                        }
                        return v;
                    }
                }
                FUN_004afae4("VAS abort");
            }
            FUN_004b23d8((void *)base);
        }
    }
    word_t r = (*(word_t **)rec[1])(rec[0]);
    word_t err = r & 0xff;
    if (err == 0) { for (int i = 0; i < 26; i++) rec[i] = 0; return r; }
err:
    FUN_004afae4("VAS abort");
}

/* FUN_00042abc @ 0x42abc  (est. sk_vspace_paddr_lookup)
 * Translate a virtual address param_3 to a physical address in the shadow
 * space param_1 at level param_2 (index base): index into the level slot array,
 * walk the vspace's level chain, and return the physical entry (or the raw
 * indexed address). Aborts on out-of-range.
 * Confidence: medium */
static word_t sk_vspace_paddr_lookup(word_t vspace, word_t level, word_t vaddr)
{
    if (vspace == 0) FUN_004b3d2c();
    word_t *slot = (word_t *)(vspace + 0x38U) + level * 3;
    if (slot < (word_t *)(vspace + 0x38U) || (word_t *)(vspace + 0x98U) < slot + 3 ||
        slot + 3 < slot) SK_FATAL();
    word_t idx = (word_t)(vaddr - slot[1]) >> (level * 0xb + 0xeU & 0x3f);
    if (idx < (word_t)slot[2]) {
        word_t pa = *slot + idx * 0x40;
        word_t rec = FUN_0005acac(0x6af2b0, 4, 0xb);
        if (vspace == *(word_t *)(rec + 0xf8)) {
            word_t n = *(word_t *)(rec + 0xe8U);
            if (n != 0) {
                word_t i = *(word_t *)(rec + 0xf0);
                word_t *e = (word_t *)(rec + i * 0x10);
                do {
                    word_t *en = e + (i / 6) * -0x60;
                    if (en + 0x88U < (word_t *)(rec + 0x88U) ||
                        (word_t *)(rec + 0xe8U) < en + 0x98U || en + 0x98U < en + 0x88U) SK_FATAL();
                    if (*(word_t *)(en + 0x90) == pa)
                        return *(word_t *)(e + (i / 6) * -0x60 + 0x88);
                    e += 0x10; i += 1; n -= 1;
                } while (n != 0);
            }
        }
        return pa;
    }
    FUN_004afae4("VAS abort");
}

/* FUN_00042c20 @ 0x42c20  (est. sk_vspace_lookup_cookie)
 * Resolve the mapping cookie for a physical address param_2 in the shadow
 * space param_1: for the self-referential vspace use sk_vspace_lookup_phys,
 * for a mode-2 vspace return 0, otherwise CallSupervisor(1) and validate the
 * cap. Returns 1 on success or an error code.
 * Confidence: low */
static word_t sk_vspace_lookup_cookie(word_t vspace, word_t paddr)
{
    if (vspace == 0) { FUN_004b3d7c(); SK_FATAL(); }
    sk_pair_t rec = FUN_0005acac(0x6af2b0, 4, 0xb);
    if (vspace == *(word_t *)(rec.lo + 0xf8)) {
        sk_pair_t r = FUN_00042ed0(paddr, 0);
        return (word_t)(r.lo != 0);
    }
    if (*(uint8_t *)(vspace + 0x98) == 2) return 0;
    CallSupervisor(1);
    if (paddr == 5) return 1;
    if ((paddr & 0xfb) == 0) { FUN_00042d04(vspace, paddr); paddr = 0; }
    return 1;
}

/* FUN_00042d04 @ 0x42d04  (est. sk_cap_validate)
 * Validate that the cap at physical address param_2 of vspace param_1 is
 * present and mapped: resolve the vspace's cap object and invoke its +0x20
 * callback to validate the entry; returns param_2 on success.
 * Confidence: low */
static word_t sk_cap_validate(word_t *vspace, word_t paddr)
{
    word_t len = 0x40;
    word_t rec = FUN_0005acac(0x6af2b0, 4, 0xb);
    if (vspace == *(word_t **)(rec + 0xf8)) FUN_004afae4("VAS abort");
    word_t off = paddr - vspace[2];
    if (paddr < (word_t)vspace[2]) FUN_004afae4("VAS abort");
    word_t *lock = vspace + 0x14;
    if (lock <= vspace + 0x16) {
        if (FUN_00118164(lock) != 0) SK_ABORT("VAS abort");
        uint8_t ok = (*(uint8_t **)(vspace[1] + 0x20))(vspace[0], &off, &len);
        if (FUN_00118194(lock) != 0) SK_ABORT("VAS abort");
        if (ok == 0) return paddr;
        FUN_004afae4("VAS abort");
    }
    SK_FATAL();
}

/* FUN_00042ed0 @ 0x42ed0  (est. sk_vspace_lookup_phys)
 * Physical-address lookup / level-0 free: if param_2 is the self-referential
 * vspace's level index, resolve the pte at the given physical address via the
 * cap table; otherwise CallSupervisor(1) and, on 5 (preempted), drain the
 * preemption queue. Returns {found, paddr}.
 * Confidence: low (interleaved queue drain) */
static word_t sk_vspace_lookup_phys(word_t paddr, word_t level)
{
    word_t rec = FUN_0005acac(0x6af2b0, 4, 0xb);
    word_t q = FUN_00054de4();
    if ((q & 1) == 0) {
        if (rec + 0x110 < rec || rec + 0x30 < rec) SK_FATAL();
        q = FUN_00034ba4(rec);
        if ((q & 1) == 0) FUN_00043e88();
    }
    if (rec + 0x110 < rec || rec + 0x30 < rec) SK_FATAL();
    sk_pair_t sp = FUN_00034bd8(rec);
    q = sp.lo;
    word_t vspace = *(word_t *)(rec + 0xf8);
    word_t lvl = level + 1;
    word_t mask = (word_t)-1 << (level * -3 + lvl * 0xe & 0x3f);
    word_t pte = FUN_00042abc(vspace, level, mask & paddr);
    CallSupervisor(1);
    word_t cur = pte;
    if (pte == 5) {
        if ((q & 1) != 0) goto done;
        goto drain;
    }
    if ((pte & 0xfb) != 0) { FUN_004b3d54(pte, NULL); FUN_004afae4("VAS abort"); }
    word_t rec2 = FUN_0005acac(0x6af2b0, 4, 0xb);
    if (rec2 + 0x30 < rec2) SK_FATAL();
    if (FUN_00034ba4() == 0) FUN_004afae4("VAS abort");
    if (*(word_t *)(rec2 + 0xf) == 0) { FUN_004b3e30(); FUN_004afae4("VAS abort"); }
    word_t n = *(word_t *)(rec2 + 0xf) - 1;
    *(word_t *)(rec2 + 0xf) = n;
    if (n < *(uint8_t *)((word_t)rec2 + 0x101)) *(uint8_t *)((word_t)rec2 + 0x101) = n;
    word_t *slot = (word_t *)(rec2 + 0x30) + n;
    if (slot < (word_t *)(rec2 + 0x30)) SK_FATAL();
    do { CallSupervisor(4); } while (*slot == 1);
    slot = (word_t *)(rec2 + 0x30) + *(word_t *)(rec2 + 0xf);
    if (slot < (word_t *)(rec2 + 0x30) || rec2 + 0x60 < (word_t *)(slot + 1) || slot + 1 < slot) SK_FATAL();
    word_t cap = *slot;
    char m = *(char *)(vspace + 0x98);
    word_t type;
    if (m == 2) type = 0;
    else if (m == 1) {
        if (2 < level - 1) FUN_004afae4("VAS abort");
        word_t g = FUN_00041f8c();
        type = (word_t)*(uint8_t *)(g + 2);
    } else {
        if (m != 0) FUN_004afae4("VAS abort");
        type = 0xc0d0e04 >> (((uint32_t)level & 3) << 3);
        if (3 < level) type = 4;
    }
    word_t r = (*(word_t **)*(word_t *)(vspace + 0xb8))
        (*(word_t *)(vspace + 0xb0), type & 0xff, pte, cap, 0);
    if (r != 0) {
        word_t rec3 = FUN_0005acac(0x6af2b0, 4, 0xb);
        if (rec3 + 0x30 < rec3) SK_FATAL();
        if (FUN_00034ba4() == 0) FUN_004afae4("VAS abort");
        word_t *s2 = (word_t *)(rec3 + 0x30) + *(word_t *)(rec3 + 0xf);
        if (s2 < (word_t *)(rec3 + 0x30) || rec3 + 0x60 < (word_t *)(s2 + 1) || s2 + 1 < s2) SK_FATAL();
        *s2 = cap;
        *(word_t *)(rec3 + 0xf) = *(word_t *)(rec3 + 0xf) + 1;
        if (r != 0x107) { FUN_004b3da4(vspace, level, mask & paddr, r); cur = 0; }
        goto drain;
    }
    word_t pa = FUN_00042abc(vspace, lvl, mask & paddr);
    word_t r2 = FUN_00043b44(vspace, pa, cap, mask & paddr);
    if ((r2 & 0xff) == 4) {
        word_t pa2 = FUN_00042ed0(mask & paddr, lvl);
        if (pa2 != 0) r2 = FUN_00043b44(vspace, pa2, cap, mask & paddr);
        else goto reclaim;
    }
    if (r2 != 0) goto reclaim;
    {
        word_t rec4 = FUN_0005acac(0x6af2b0, 4, 0xb);
        if (rec4 + 0x30 < rec4) SK_FATAL();
        if (FUN_00034ba4() == 0) FUN_004afae4("VAS abort");
        word_t cnt = *(word_t *)(rec4 + 0xe8);
        word_t *q2 = (word_t *)(rec4 + 0x88) + ((cnt + *(word_t *)(rec4 + 0xf0)) % 6) * 2;
        if (q2 < (word_t *)(rec4 + 0x88) || (word_t *)(rec4 + 0xe8) < q2 + 2 || q2 + 2 < q2) SK_FATAL();
        *q2 = cap; q2[1] = pa;
        *(word_t *)(rec4 + 0xe8) = cnt + 1;
    }
    if ((q & 1) == 0) goto drain;
done:
    if (cur != 0) goto ret;
    FUN_004b3e5c(mask & paddr, level);
    cur = 0;
ret:
    FUN_00034d5c(rec, q, sp.hi);
    return cur;
reclaim:
    (*(word_t **)(*(word_t *)(vspace + 0xb8) + 0x10))(*(word_t *)(vspace + 0xb0), pte);
    {
        word_t rec5 = FUN_0005acac(0x6af2b0, 4, 0xb);
        if (rec5 + 0x30 < rec5) SK_FATAL();
        if (FUN_00034ba4() == 0) FUN_004afae4("VAS abort");
        word_t *s3 = (word_t *)(rec5 + 0x30) + *(word_t *)(rec5 + 0xf);
        if (s3 < (word_t *)(rec5 + 0x30) || rec5 + 0x60 < (word_t *)(s3 + 1) || s3 + 1 < s3) SK_FATAL();
        cur = 0;
        *s3 = cap;
        *(word_t *)(rec5 + 0xf) = *(word_t *)(rec5 + 0xf) + 1;
    }
    goto done;
drain:
    {
        word_t rec6 = FUN_0005acac(0x6af2b0, 4, 0xb);
        if (rec6 + 0x30 < rec6) SK_FATAL();
        if (FUN_00034ba4() == 0) FUN_004afae4("VAS abort");
        word_t cnt = *(word_t *)(rec6 + 0xe8);
        if (cnt == 0) goto done;
        bool ok = true;
        word_t vs = *(word_t *)(rec6 + 0xf8);
        do {
            word_t *e = (word_t *)(rec6 + 0x88) + *(word_t *)(rec6 + 0xf0) * 2;
            if (e < (word_t *)(rec6 + 0x88) || (word_t *)(rec6 + 0xe8) < e + 2 || e + 2 < e) SK_FATAL();
            word_t c = *e;
            word_t pa = e[1];
            CallSupervisor(1);
            if ((c & 0xff) == 5) {
                word_t r = FUN_00042ed0(pa, 0);
                if (r != 0) { CallSupervisor(1); goto next; }
                do { CallSupervisor(4); } while (c == 1);
                (*(word_t **)(*(word_t *)(vs + 0xb8) + 0x10))(*(word_t *)(vs + 0xb0), pa);
                FUN_001185ec(0xeb1a02bf914012ba, "VAS error in function %s at %s");
                FUN_0011858c(0xeb1a02bf914012ba);
                ok = false;
            }
next:
            *(word_t *)(rec6 + 0xe8) = *(word_t *)(rec6 + 0xe8) - 1;
            *(word_t *)(rec6 + 0xf0) = (*(word_t *)(rec6 + 0xf0) + 1U) % 6;
            word_t rec7 = FUN_0005acac(0x6af2b0, 4, 0xb);
            word_t *q3 = (word_t *)(rec7 + 0x30);
            if (q3 < (word_t *)rec7) SK_FATAL();
            if (FUN_00034ba4() == 0) FUN_004afae4("VAS abort");
            word_t *s4 = q3 + 6 + rec7[0xf];
            if (s4 < q3 + 6 || rec7 + 0x60 < (word_t *)(s4 + 1) || s4 + 1 < s4) SK_FATAL();
            *s4 = c;
            rec7[0xf] = rec7[0xf] + 1;
        } while (*(word_t *)(rec6 + 0xe8) != 0);
        if (ok) goto done;
        cur = 0;
        goto ret;
    }
}


/* ================================================================== *
 * Fault handler / faulthandler (FUN_0003863c, 0003869c, 000387fc,
 * 00038bdc, 00039094) and abort wrappers (0003ba58, 0004108c..000411dc)
 * ================================================================== */

/* FUN_0003ba58 @ 0x3ba58  (est. sk_lock_push_primary) */
static void sk_lock_push_primary(word_t rec, word_t *tok)
{
    if (tok != (word_t *)0) {
        uint8_t n = *(uint8_t *)(rec + 0x30);
        if (2 < n) SK_ABORT("VAS abort");
        *tok = *(word_t *)(rec + 8);
        *(word_t **)(rec + 8) = tok;
        *(uint8_t *)(rec + 0x30) = n + 1;
    }
}

/* FUN_0003863c @ 0x3863c  (est. sk_fault_dispatch)
 * Resolve the current context and issue a supervisor call (mode 2) to enter
 * the fault path; encodes the preemption/error result. Returns error code.
 * Confidence: medium */
static sk_pair_t sk_fault_dispatch(void)
{
    word_t ctx = FUN_00032cd0();
    word_t r = FUN_00042abc(ctx, 2, 0);
    word_t err;
    if (r == 0) err = 0x9e60004;
    else {
        CallSupervisor(2);
        err = (r != 0) ? (r & 0x7fff) << 0x10 | 0x80000001 : 0;
    }
    return (sk_pair_t){ err, 0 };
}

/* FUN_0003869c @ 0x3869c  (est. sk_faulf_handler_enter)
 * Enter the fault-handler: set up the fault record, call the fault dispatch
 * (FUN_00039094) for the span param_1, and on success/failure either return the
 * result or abort. Initializes the fault record lock via FUN_001180fc.
 * Confidence: low (fault-state wrapper) */
static sk_pair_t sk_faulf_handler_enter(word_t vspace, word_t span, word_t a3,
                                        word_t a4)
{
    DAT_006ad2c8 = DAT_006ad2c8 + 1;
    word_t rec[32] = {0};
    rec[0] = vspace; rec[4] = 1; rec[6] = 1;
    byte fault_flag[0x40] = {0};
    FUN_001180fc(&rec[6]);
    sk_pair_t r = sk_faulf_dispatch(vspace, &rec[0], a3, a4, fault_flag);
    if (fault_flag[0] == 1) FUN_004b28c0();
    else if ((int8_t)rec[1] != 1) {
        if (rec[0x13] != 1) {
            FUN_000539fc(&rec[6]);
            return r;
        }
        SK_ABORT("VAS abort");
    }
    FUN_004b2898();
    SK_ABORT("VAS abort");
}

/* FUN_00039094 @ 0x39094  (est. sk_faulf_dispatch)
 * The VAS fault dispatch hub: given a faulting vspace param_1 / span param_2
 * and the fault address param_3, dispatch to the managed/COW/frozen-page
 * handlers. Allocates two shadow spans (FUN_0003c56c), walks their spanmaps,
 * and routes by the span's fault-type bits (bits 0x12/0x13/0xc/0x14/0x15) to
 * sk_span_map_check_window, sk_startfault_managed or sk_startfault_cow, or
 * the frozen-page path. Fills the fault record param_5. Tracks per-path
 * counters (_DAT_006ad3xx). Returns error code.
 * Confidence: low (very large dispatch, decompiler dropped many paths) */
static sk_pair_t sk_faulf_dispatch(word_t vspace, word_t span, word_t fault_addr,
                                   word_t a4, byte *fault_rec)
{
    DAT_006ad378 = DAT_006ad378 + 1;
    word_t masked = fault_addr & 0xf0ffffffffffc000;
    for (int i = 0; i < 0x28; i++) fault_rec[i] = 0;
    word_t spanobj = 0, cookie = 0;
    byte fl2 = 0;
    word_t ok = FUN_00045a68(vspace, span, masked, &spanobj, &fl2);
    byte fl = fl2;
    word_t sp = spanobj;
    if ((ok & 1) == 0) { DAT_006ad37c = DAT_006ad37c + 1; return (sk_pair_t){ 0xfb20001, 0 }; }
    if (((fault_addr & 0xf00000000000000) != 0) &&
        ((*(uint8_t *)(spanobj + 0x22) >> 6 & 1) == 0)) {
        FUN_00045c98(vspace, span);
        DAT_006ad38c = DAT_006ad38c + 1;
        return (sk_pair_t){ 0xfbb0001, 0 };
    }
    DAT_006ad344 = DAT_006ad344 + 1;
    if (*(word_t *)(spanobj + 0x50) == vspace) {
        *(word_t *)(span + 0xb0) = spanobj;
        if ((*(uint8_t *)(spanobj + 0x22) & 1) == 0) { FUN_004b2da8(); return (sk_pair_t){ 0, 0 }; }
        sk_pair_t pr = FUN_000455b0(fl, a4);
        word_t u12 = pr.hi;
        if ((pr.lo & 1) == 0) { DAT_006ad348 = DAT_006ad348 + 1; return (sk_pair_t){ 0xf210001, u12 }; }
        uint32_t f = *(uint32_t *)(sp + 0x20);
        word_t err = 0;
        word_t res = 0;
        if (((f >> 0x14 & 1) == 0) || (0x4000 < masked - *(word_t *)(sp + 8))) {
            if (((f >> 0x15 & 1) == 0) ||
                (0x4000 < (*(word_t *)(sp + 8) - masked) + *(word_t *)(sp + 0x10))) {
                if (*(uint8_t *)(vspace + 0x290) != 1) {
                    /* non-frozen path */
                    if ((f >> 0xc & 1) == 0) {
                        if ((f >> 0x13 & 1) == 0) {
                            if ((f >> 6 & 1) == 0) {
                                DAT_006ad368 = DAT_006ad368 + 1;
                                word_t lvar21 = masked + 0x4000;
                                sk_pair_t w = sk_span_leaf_walk((char *)sp, masked, 0);
                                res = w.hi; u12 = w.lo;
                                if ((long)u12 < 7) {
                                    if (u12 == 0) { DAT_006ad36c = DAT_006ad36c + 1; u12 = 0; }
                                    else if (u12 == 2) { DAT_006ad374 = DAT_006ad374 + 1; res = 0x80020002; u12 = 0; }
                                    else goto mapfail;
                                } else {
                                    if (u12 != 7 && u12 != 0x207 && u12 != 0x307) goto mapfail;
                                    DAT_006ad370 = DAT_006ad370 + 1;
                                    res = (u12 & 0x7fff) << 0x10 | 0x80000001;
                                    u12 = 0;
                                }
                            } else {
                                DAT_006ad35c = DAT_006ad35c + 1;
                                word_t l_a0[2] = { *(word_t *)(sp + 0x48), 0 };
                                word_t v19 = (masked | 1) - *(word_t *)(sp + 8);
                                word_t add = (v19 & 0x3fff) ? 0x4000 : 0;
                                v19 = add + (v19 & 0xffffffffffffc000);
                                word_t l21 = v19 - l_a0[0];
                                if (v19 < l_a0[0]) { DAT_006ad360 = DAT_006ad360 + 1; u12 = 0; }
                                else {
                                    if ((f >> 7 & 1) != 0) l_a0[0] = *(word_t *)(sp + 0x10) - v19;
                                    word_t d0[2] = { l21, 0 };
                                    u12 = sk_span_map_check(sp, l_a0, d0).lo;
                                    if ((u12 & 0xff) == 0) { DAT_006ad364 = DAT_006ad364 + 1; *(word_t *)(sp + 0x48) = v19; }
                                }
                            }
                        } else {
                            DAT_006ad358 = DAT_006ad358 + 1;
                            sk_startfault_cow(vspace, masked, a4, sp, fault_rec);
                            u12 = 0;
                        }
                        goto fin;
                    }
                    /* managed fault (bit 0xc) */
                    word_t idx = (f >> 4 & 1) * 4;
                    *(int *)(idx + 0x6ad350) = *(int *)(idx + 0x6ad350) + 1;
                    DAT_006ad2d0 = DAT_006ad2d0 + 1;
                    if ((*(uint8_t *)(span + 0xa0) & 1) == 0) {
                        word_t *faulting = (word_t *)(span + 0x90);
                        if (*faulting != 0) {
                            DAT_006ad2d8 = DAT_006ad2d8 + 1;
                            word_t dom = FUN_00032cd0(*(word_t *)(sp + 0x50));
                            word_t *lock = (word_t *)(sp + 0x80);
                            if (sp + 0x90U < sp + 0x80) SK_FATAL();
                            word_t lk = FUN_00118164((void *)(sp + 0x80));
                            if ((int)lk != 0) FUN_004afae4("abort spanmap_lock");
                            word_t l[5] = {0,0,0,0,0};
                            if (dom + 0xd0 < dom) SK_FATAL();
                            FUN_000287e4(l, *(word_t *)(sp + 0x78),
                                (int)(masked - *(word_t *)(dom + 0x28) >> 0xe) + 1);
                            word_t leaf = l[0];
                            *(word_t *)(sp + 0x78) = l[4];
                            if (leaf == 0) {
                                DAT_006ad2dc = DAT_006ad2dc + 1;
                                u12 = FUN_00118194((void *)(sp + 0x80));
                                res = (l[2] & 0xff) ? l[2] : 0xdbf0002;
                                goto fin;
                            }
                            u12 = FUN_00118194((void *)(sp + 0x80));
                            f = *(uint32_t *)(sp + 0x20);
                            if ((int)a4 == 0) {
                                /* managed COW: enter mode, notify, retry */
                                word_t mode = (f >> 3) & 3;
                                word_t *tp = (word_t *)tpidrro_el0;
                                *tp = mode; CallSupervisor(0); *tp = mode;
                                if (leaf == 0) { DAT_006ad2e8 = DAT_006ad2e8 + 1; u12 = 0; }
                                else {
                                    word_t lvar21 = *faulting;
                                    do { CallSupervisor(4); } while (lvar21 == 1);
                                    word_t cb = 0;
                                    if (*(word_t **)(sp + 0x30) == (word_t *)0) {
                                        DAT_006ad2ec = DAT_006ad2ec + 1;
                                    } else {
                                        DAT_006ad2f0 = DAT_006ad2f0 + 1;
                                        sk_pair_t cr = (*(sk_pair_t(**)(word_t, word_t, word_t, word_t*))(*(word_t *)(sp + 0x30)))
                                            (*(word_t *)(sp + 0x38), masked - *(word_t *)(sp + 0x40), *faulting, &cb);
                                        int crr = (int)cr.lo & 0xf;
                                        if (crr != 0) {
                                            if (crr == 2) { DAT_006ad2f8 = DAT_006ad2f8 + 1; }
                                            else if (crr != 4) goto mapfail;
                                            DAT_006ad2fc = DAT_006ad2fc + 1;
                                        }
                                        if ((f >> 4 & 1) == 0) goto mapfail;
                                        DAT_006ad300 = DAT_006ad300 + 1;
                                        if ((sk_span_map_page_walk(sp, masked, *faulting, 0, 0, 0, 0).lo & 0xff) != 0) goto mapfail;
                                        FUN_004b2c84(faulting);
                                        u12 = 0;
                                        goto fin;
                                    }
                                    DAT_006ad2f4 = DAT_006ad2f4 + 1;
                                    res = 0xe000001; u12 = 0;
                                }
                            } else if ((int)a4 == 2) {
                                if ((f >> 4 & 1) != 0) goto managed_retry;
                                DAT_006ad2e0 = DAT_006ad2e0 + 1;
                                res = 0xdd20001; u12 = 0;
                            } else {
                                DAT_006ad2e4 = DAT_006ad2e4 + 1;
                                res = 0xdd60001; u12 = 0;
                            }
                            goto fin;
managed_retry:
                            goto fin;
                        }
                    } else FUN_004b2d38();
                    FUN_004b2d10();
                    SK_ABORT("abort spanmap_lock");
                }
                /* frozen page path */
                {
                    word_t dom = FUN_00032cd0(*(word_t *)(sp + 0x50));
                    word_t *lock = (word_t *)(sp + 0x80);
                    if (dom + 0xd0 < dom || sp + 0x90U < sp + 0x80) SK_FATAL();
                    word_t l21 = *(word_t *)(dom + 0x28);
                    if (FUN_00118164((void *)(sp + 0x80)) != 0) SK_ABORT("VAS abort");
                    int i1 = (int)(masked - l21 >> 0xe) + 1;
                    word_t l_a0[5] = {0,0,0,0,0};
                    FUN_00035ba0(l_a0, *(word_t *)(sp + 0xa0), i1);
                    word_t u8 = l_a0[0];
                    *(word_t *)(sp + 0xa0) = l_a0[4];
                    if (l_a0[0] == 0) {
                        u12 = FUN_00118194((void *)(sp + 0x80));
                        f = *(uint32_t *)(sp + 0x20);
                        goto nonfrozen;
                    }
                    word_t d0[5] = {0,0,0,0,0};
                    FUN_000287e4(d0, *(word_t *)(sp + 0x78), i1);
                    word_t lv21 = d0[0];
                    *(word_t *)(sp + 0x78) = d0[4];
                    if (d0[0] == 0) SK_ABORT("VAS abort");
                    if (FUN_00118194((void *)(sp + 0x80)) != 0) SK_ABORT("VAS abort");
                    do { CallSupervisor(4); } while (*(word_t *)(span + 0x98) == 1);
                    u12 = (*(word_t **)*(word_t *)(dom + 0xb8))
                        (*(word_t *)(dom + 0xb0), 0x11, lv21, *(word_t *)(span + 0x98), 0);
                    if ((u12 & 0xff) == 0) {
                        u12 = sk_span_map_page_walk(*(word_t *)(span + 0x58),
                            *(word_t *)(span + 0x60), *(word_t *)(span + 0x98), 0, 0, 0, 0).lo;
                        if ((u12 & 0xff) != 0) goto mapfail;
                        u12 = *(word_t *)(span + 0x98);
                        do { CallSupervisor(4); } while (u12 == 1);
                        if ((u12 & 0xff) != 0) goto mapfail;
                        if (*(word_t *)(span + 0x88) < (word_t)DAT_004bc200) SK_FATAL();
                        char c = FUN_0002ff40(vspace + 0x208, u8, i1, *(word_t *)(span + 0x60));
                        if (c != 0) goto mapfail;
                        if (sk_span_map_page_walk(sp, masked, *(word_t *)(span + 0x68),
                            (*(uint32_t *)(sp + 0x20) & 0x18) == 0, 0, 0, 0).lo != 0) goto mapfail;
                        do { CallSupervisor(4); } while (*(word_t *)(span + 0x68) == 1);
                        if (FUN_00118164((void *)(sp + 0x80)) != 0) SK_ABORT("VAS abort");
                        word_t e0[3] = {0,0,0};
                        FUN_0003611c(e0, *(word_t *)(sp + 0xa0), i1, 0);
                        *(word_t *)(sp + 0xa0) = e0[2];
                        if (FUN_00118194((void *)(sp + 0x80)) != 0) SK_ABORT("VAS abort");
                        DAT_006ad34c = DAT_006ad34c + 1;
                        u12 = 0;
                        goto fin;
                    }
                    goto mapfail;
                }
            }
        }
        res = 0xf2b0001; u12 = 0;
        goto fin;
    }
    FUN_004b2a84();
    FUN_004b2da8();
    u12 = 0;
fin:
nonfrozen:
    {
        word_t u15 = res, u19 = u12;
        if ((fault_rec[0] & 1) == 0) {
            FUN_00045c98(vspace, span);
            if ((u19 & 0xff) == 0) DAT_006ad380 = DAT_006ad380 + 1; else DAT_006ad384 = DAT_006ad384 + 1;
            return (sk_pair_t){ u19, u15 };
        }
        return (sk_pair_t){ u19, u15 };
    }
mapfail:
    FUN_004afae4("VAS SPANFAULT CBRESULT VALID");
}

/* FUN_00038bdc @ 0x38bdc  (est. sk_faulf_handler_run)
 * Run the fault handler for the given vspace: walk its LRU span list (offset
 * +0x200/+0x90) and, for each live span, drain the frozen-page COW states via
 * CallSupervisor(0/5), remapping each frozen page and dropping its level-0
 * mapping. Returns {0,0} on success, 0xccb0001 on null.
 * Confidence: low (large frozen-page sweep) */
static sk_pair_t sk_faulf_handler_run(word_t vspace)
{
    if (vspace == 0) return (sk_pair_t){ 0xccb0001, 0 };
    if ((*(uint8_t *)(vspace + 0x290) & 1) == 0) {
        if (vspace + 0x2a0 < vspace) SK_FATAL();
        char c = FUN_0002fa84(0x65b5a0, vspace + 0x208);
        *(uint8_t *)(vspace + 0x290) = (c == 0);
    }
    if (vspace + 0x2a0 < vspace) SK_FATAL();
    FUN_00032cd0(vspace);
    word_t local_b0 = 0;
    word_t *local_a8 = (word_t *)0;
    word_t ctx = FUN_00032514();
    sk_pair_t pr = sk_vspace_region_create(ctx, 0x1908, (char *)&DAT_004bc378, &local_b0, 0, 0);
    word_t u4 = local_b0;
    if ((pr.lo & 0xff) == 0) {
        word_t u13 = *(word_t *)(local_b0 + 8);
        if (FUN_00118164((void *)(vspace + 0x1f0)) != 0) SK_ABORT("VAS abort");
        word_t u14 = *(word_t *)(vspace + 0x200);
        if (u14 != 0) {
            word_t u12 = (word_t)DAT_004bc1fc;
            do {
                if ((*(uint8_t *)(u14 + 0x20) >> 3 & 1) != 0) {
                    if (u14 + 0xb0 < u14 || u14 + 0x90 < u14 + 0x80) SK_FATAL();
                    if (FUN_00118164((void *)(u14 + 0x80)) != 0) SK_ABORT("VAS abort");
                    word_t d0[3] = {0,0,0};
                    FUN_000363ac(d0, *(word_t *)(u14 + 0x78), 0);
                    sk_pair_t st = FUN_0003667c(d0);
                    word_t u8 = st.hi, u11 = st.lo;
                    if ((u11 & 3) != 0) {
                        word_t *tp = (word_t *)tpidrro_el0;
                        do {
                            *tp = 1; u8 = 0; CallSupervisor(0); *tp = 1;
                            if (u11 >> 0x1c == 0) {
                                word_t u2 = (uint32_t)u11 >> 6 & 0x3fffff;
                                *tp = 0; CallSupervisor(0); *tp = 0; CallSupervisor(5);
                                if (u4 <= u4 + 0xb0) {
                                    if (sk_span_map_page_walk(u4, u13, 0, 0, 0, 0, 0).lo == 0) {
                                        if (u13 + 0x4000 < u13 || (u13 + 0x4000) - u13 < u12) SK_FATAL();
                                        FUN_0002fb88(&d0, vspace + 0x208, u2, u13, 0);
                                        word_t lf = 0x4000, lo = 0;
                                        word_t w = sk_span_map_check_window(u4, &lo, &lf, 0).lo;
                                        if ((w & 0xff) == 0) {
                                            if ((int8_t)d0[0] == 0) {
                                                word_t a0[3] = {0,0,0};
                                                FUN_00036008(a0, *(word_t *)(u14 + 0xa0), u2, 0);
                                                *(word_t *)(u14 + 0xa0) = a0[0];
                                                sk_spanmap_unmap_one(u11, u14,
                                                    *(uint32_t *)(u14 + 0x20) >> 0xc & 1,
                                                    (*(uint32_t *)(u14 + 0x20) & 0x4000000) == 0, 0);
                                                FUN_000363ac(d0, *(word_t *)(u14 + 0x78), u2 + 1);
                                                st = FUN_0003667c(d0);
                                                u8 = 0;
                                            } else {
                                                u11 = FUN_0003667c(d0).lo;
                                                *tp = 1; CallSupervisor(0); *tp = 1;
                                                st.hi = 0; st.lo = u11;
                                            }
                                        } else goto fail;
                                    } else { FUN_004b29a0(&d0, 0); goto fail; }
                                } else SK_FATAL();
                            }
                            u8 = st.hi; u11 = st.lo;
                        } while ((u11 & 3) != 0);
                    }
                    if (FUN_00118194((void *)(u14 + 0x80)) != 0) SK_ABORT("VAS abort");
                }
                u14 = *(word_t *)(u14 + 0x90);
            } while (u14 != 0);
        }
        if (FUN_00118194((void *)(vspace + 0x1f0)) != 0) SK_ABORT("VAS abort");
        (*(void (**)(void))*local_a8)(u4);
        return (sk_pair_t){ 0, 0 };
    }
fail:
    FUN_004afae4("VAS abort");
}

/* FUN_000387fc @ 0x387fc  (est. sk_faulthandler_create)
 * Create the two faulthandler spans (the frozen-page shadow spans) for vspace
 * param_1, linking them into the fault record param_2. Creates a write span
 * (DAT_004bc398, flags 0x1908) and a read span (flags 0x1900), walks their
 * spanmaps, allocates two PMM buffers, and initializes the record via
 * FUN_001180fc. On success *param_2 receives the record (type 0x65b630).
 * Confidence: low (decompiler dropped many blocks) */
static sk_pair_t sk_faulthandler_create(word_t vspace, word_t *out)
{
    DAT_006ad2cc = DAT_006ad2cc + 1;
    word_t *rec = (word_t *)FUN_00033638();
    word_t wspan = 0, rspan = 0;
    word_t local[9] = {0,0,0,0,0,0,0,0,0};
    word_t pr = sk_vspace_region_create((word_t)&DAT_0064c3f0, 0x1908,
        (char *)&DAT_004bc398, &local[7], 0, 0).lo;
    word_t lvar17 = local[7];
    if ((pr & 0xff) != 0) SK_FATAL();
    word_t *lock = (word_t *)(local[7] + 0x80);
    if (local[7] + 0x90U < (word_t)lock) SK_FATAL();
    word_t u21 = *(word_t *)(local[7] + 8);
    if (FUN_00118164((void *)(local[7] + 0x80)) != 0) SK_ABORT("VAS abort");
    word_t u12 = FUN_00032cd0(*(word_t *)(lvar17 + 0x50));
    word_t b0[6] = {0,0,0,0,0,0};
    if (u12 + 0xd0 < u12) SK_FATAL();
    FUN_000287e4(b0, *(word_t *)(lvar17 + 0x78),
        (int)(u21 - *(word_t *)(u12 + 0x28) >> 0xe) + 1);
    word_t lvar6 = b0[0];
    *(word_t *)(lvar17 + 0x78) = b0[5];
    if (FUN_00118194((void *)(local[7] + 0x80)) != 0) SK_ABORT("VAS abort");
    word_t local2[9] = {0,0,0,0,0,0,0,0,0};
    word_t pr2 = sk_vspace_region_create((word_t)&DAT_0064c3f0, 0x1900,
        (char *)&DAT_004bc398, &local2[0], 0, 0).lo;
    word_t lvar5 = local2[0];
    if ((pr2 & 0xff) != 0) SK_FATAL();
    word_t u12b = *(word_t *)(local2[0] + 8);
    word_t u13 = FUN_00032cd0(*(word_t *)(local2[0] + 0x50));
    if (local2[0] + 0x90U < local2[0] + 0x80) SK_FATAL();
    if (FUN_00118164((void *)(local2[0] + 0x80)) != 0) SK_ABORT("VAS abort");
    word_t d8[3] = {0,0,0};
    if (u13 + 0xd0 < u13) SK_FATAL();
    FUN_000287e4(d8, *(word_t *)(lvar5 + 0x78),
        (int)(u12b - *(word_t *)(u13 + 0x28) >> 0xe) + 1);
    *(word_t *)(lvar5 + 0x78) = d8[1];
    if (FUN_00118194((void *)(local2[0] + 0x80)) != 0) SK_ABORT("VAS abort");
    word_t u11 = u21 + *(word_t *)(lvar17 + 0x10);
    word_t u14 = FUN_00034f70();
    word_t u15 = FUN_00034f70();
    word_t e0 = (word_t)out;
    if (u11 < u21 || u11 - u21 < 0x4000 || u12b + *(word_t *)(lvar5 + 0x10) < u12b ||
        (u12b + *(word_t *)(lvar5 + 0x10)) - u12b < 0x4000) SK_FATAL();
    rec[0xb] = lvar17; rec[0xc] = u21; rec[0xd] = lvar6;
    rec[0xe] = lvar5; rec[0xf] = u12b; rec[0x10] = d8[0];
    rec[0x11] = 0x4000; rec[0x12] = u14; rec[0x13] = u15;
    rec[0x15] = 0; rec[0x14] = 0; rec[0x17] = 0; rec[0x16] = 0;
    rec[0] = e0; rec[2] = 0; rec[1] = 0; rec[4] = 0; rec[3] = 0; rec[6] = 0; rec[5] = 0;
    *(uint8_t *)((word_t)rec + 0x41) = 1;
    rec[9] = 0; rec[10] = e0;
    FUN_001180fc(rec + 6);
    if (rec[0x12] == 0) FUN_004b2930();
    else if (rec[0x13] != 0) {
        out[0] = e0;
        out[1] = (word_t)rec;
        out[2] = 0x65b630;
        return (sk_pair_t){ 0, 0 };
    }
    FUN_004b28f8();
    return sk_faulf_handler_run(vspace);
}


/* ================================================================== *
 * Abort wrappers (FUN_0004108c..000411dc) and level-population
 * (FUN_000436fc, 00043780)
 * ================================================================== */

/* FUN_0004108c @ 0x4108c — log an error string on the stack. */
static void sk_log_err_stack8(void) { sk_l4_error_string((word_t *)&(word_t){0}); }

/* FUN_000410ac @ 0x410ac — log an error string on the stack. */
static void sk_log_err_stack9(void) { sk_l4_error_string((word_t *)&(word_t){0}); }

/* FUN_000410cc @ 0x410cc — empty stub. */
static void sk_abort_noop(void) { }

/* FUN_000410e4 @ 0x410e4 — noreturn abort with a saved context arg. */
static void sk_abort_ctx(word_t a) { (void)a; FUN_004afae4("VAS abort"); }

/* FUN_000410f8 @ 0x410f8 — empty stub. */
static void sk_abort_noop2(void) { }

/* FUN_00041110 @ 0x41110 — empty stub. */
static void sk_abort_noop3(void) { }

/* FUN_0004112c @ 0x4112c — log an error string on the stack. */
static void sk_log_err_stack10(void) { sk_l4_error_string((word_t *)&(word_t){0}); }

/* FUN_00041138 @ 0x41138 — empty stub. */
static void sk_abort_noop4(void) { }

/* FUN_0004114c @ 0x4114c — empty stub. */
static void sk_abort_noop5(void) { }

/* FUN_00041160 @ 0x41160 — noreturn abort on unexpected L4 error. */
static void sk_abort_unexpected(void) { FUN_004afae4("Unexpected L4 Error"); }

/* FUN_00041170 @ 0x41170 — noreturn VAS abort with a context arg. */
static void sk_abort_vas1(word_t a) { (void)a; FUN_004afae4("VAS abort"); }

/* FUN_00041184 @ 0x41184 — noreturn VAS abort with a context arg. */
static void sk_abort_vas2(word_t a) { (void)a; FUN_004afae4("VAS abort"); }

/* FUN_00041198 @ 0x41198 — noreturn VAS abort with a context arg. */
static void sk_abort_vas3(word_t a) { (void)a; FUN_004afae4("VAS abort"); }

/* FUN_000411ac @ 0x411ac — noreturn VAS abort with a context arg. */
static void sk_abort_vas4(word_t a) { (void)a; FUN_004afae4("VAS abort"); }

/* FUN_000411c0 @ 0x411c0 — empty stub. */
static void sk_abort_noop6(void) { }

/* FUN_000411dc @ 0x411dc  (est. sk_vspace_addr_limits)
 * Return the address-space [low, high) limits for the mode in param_1
 * (1 = geometry, else 0). For mode 1 it requires the geometry init to have
 * completed. Combines the low limit from FUN_0004137c and high from
 * FUN_000413c4, returning the spanned range. Aborts if the range is empty.
 * Confidence: medium */
static sk_pair_t sk_vspace_addr_limits(word_t mode, word_t *hint)
{
    int m = (int)mode;
    if (m == 1 && (sk_vspace_geometry_init() & 1) == 0) FUN_004b3ac8();
    word_t lo = (hint == 0) ? 0 : *hint;
    word_t hi = (hint == 0) ? (word_t)-1 : hint[1];
    word_t lo2 = sk_vspace_limit((uint32_t)mode);
    word_t hi2 = sk_vspace_limit_hi(m);
    word_t lo3 = (lo <= lo2) ? lo : lo2;
    word_t hi3 = (hi2 <= hi) ? hi : hi2;
    if (!(hi <= lo) && !(hi2 <= lo2) && !(hi3 <= lo3)) {
        if ((m - 1U < 2) || m == 0) return (sk_pair_t){ lo3, hi3 };
    }
    FUN_004afae4("VAS abort");
}

/* FUN_000436fc @ 0x436fc  (est. sk_populate_level)
 * Populate a page-table level: for the self-referential vspace (param_1 == 0)
 * delegate to the level-free path (sk_vspace_lookup_phys), otherwise recursively
 * populate the sub-level for the given physical window. Returns a success flag.
 * Confidence: low */
static word_t sk_populate_level(word_t vspace, word_t paddr, word_t level)
{
    if (vspace != 0) {
        word_t rec = FUN_0005acac(0x6af2b0, 4, 0xb);
        if (vspace == *(word_t *)(rec + 0xf8)) {
            word_t r = FUN_00042ed0(paddr, 1);
            return (word_t)(r != 0);
        }
        return sk_populate_level_rec(vspace, paddr, 1);
    }
    sk_pair_t sp = FUN_004b3ec4();
    word_t a = sp.hi;
    word_t vspace2 = sp.lo;
    word_t rec = FUN_0005acac(0x6af2b0, 4, 0xb);
    if (vspace2 == *(word_t *)(rec + 0xf8)) FUN_004afae4("VAS abort");
    char m = *(char *)(vspace2 + 0x98);
    word_t levels;
    if (m == 0) levels = 2;
    else if (m == 2) levels = 3;
    else {
        if (m != 1) FUN_004afae4("VAS abort");
        word_t g = FUN_00041f8c();
        word_t t = (word_t)*(uint8_t *)(g + 1) - 0xe;
        levels = t / 0xb;
        if (t % 0xb != 0) levels = levels + 1;
    }
    if (level == levels) FUN_004afae4("VAS abort");
    word_t lvl = level + 1;
    word_t mask = (word_t)-1 << (level * -3 + lvl * 0xe & 0x3f);
    word_t vaddr = mask & paddr;
    word_t pte = FUN_00042abc(vspace2, level, vaddr);
    FUN_00042d04(vspace2, pte);
    CallSupervisor(1);
    if (pte == 5) {
        sk_pair_t r = FUN_004b3d54(pte, NULL);
        pte = r.hi;
        char c2 = *(char *)(r.lo + 0x98);
        if (c2 == 2) pte = 4;
        else if (c2 == 1) pte = FUN_000555ac(pte, vaddr, a);
        else if (c2 == 0) {
            word_t *tp = (word_t *)tpidrro_el0;
            *tp = vaddr; tp[1] = a; tp[2] = 0; tp[3] = 0;
            CallSupervisor(0); *tp = vaddr;
        }
        return pte;
    }
    if ((pte & 0xfb) != 0) {
        sk_pair_t r = FUN_004b3d54(pte, NULL);
        pte = r.hi;
        char c2 = *(char *)(r.lo + 0x98);
        if (c2 == 2) pte = 4;
        else if (c2 == 1) return FUN_000555ac(pte, vaddr, a);
        else if (c2 == 0) {
            word_t *tp = (word_t *)tpidrro_el0;
            *tp = vaddr; tp[1] = a; tp[2] = 0; tp[3] = 0;
            CallSupervisor(0); *tp = vaddr;
        }
        return pte;
    }
    word_t sub = FUN_00042abc(vspace2, lvl, mask & paddr);
    word_t r = FUN_00043b44(vspace2, sub, pte, mask & paddr);
    if ((r & 0xff) == 4) {
        word_t sub2 = sk_populate_level_rec(vspace2, mask & paddr, lvl);
        if (sub2 != 0) r = FUN_00043b44(vspace2, sub2, pte, mask & paddr);
        else goto fail;
    }
    if (r != 0) goto fail;
    return 0;
fail:
    (*(word_t **)(*(word_t *)(vspace2 + 0xb8) + 0x10))(*(word_t *)(vspace2 + 0xb0), pte);
    return 0;
}

/* FUN_00043780 @ 0x43780  (est. sk_populate_level_rec)
 * Recursive page-table level population: resolve the vspace's level chain for
 * the given physical window, allocate/validate the intermediate pte, and
 * descend one level via sk_populate_level. Shared with FUN_000436fc.
 * Confidence: low */
static word_t sk_populate_level_rec(word_t vspace, word_t paddr, word_t level)
{
    word_t rec = FUN_0005acac(0x6af2b0, 4, 0xb);
    if (vspace == *(word_t *)(rec + 0xf8)) FUN_004afae4("VAS abort");
    char m = *(char *)(vspace + 0x98);
    word_t levels;
    if (m == 0) levels = 2;
    else if (m == 2) levels = 3;
    else {
        if (m != 1) FUN_004afae4("VAS abort");
        word_t g = FUN_00041f8c();
        word_t t = (word_t)*(uint8_t *)(g + 1) - 0xe;
        levels = t / 0xb;
        if (t % 0xb != 0) levels = levels + 1;
    }
    if (level == levels) FUN_004afae4("VAS abort");
    word_t lvl = level + 1;
    word_t mask = (word_t)-1 << (level * -3 + lvl * 0xe & 0x3f);
    word_t vaddr = mask & paddr;
    word_t pte = FUN_00042abc(vspace, level, vaddr);
    FUN_00042d04(vspace, pte);
    CallSupervisor(1);
    if (pte == 5) {
        sk_pair_t r = FUN_004b3d54(pte, NULL);
        pte = r.hi;
        char c2 = *(char *)(r.lo + 0x98);
        if (c2 == 2) pte = 4;
        else if (c2 == 1) return FUN_000555ac(pte, vaddr, 0);
        else if (c2 == 0) {
            word_t *tp = (word_t *)tpidrro_el0;
            *tp = vaddr; tp[1] = 0; tp[2] = 0; tp[3] = 0;
            CallSupervisor(0); *tp = vaddr;
        }
        return pte;
    }
    if ((pte & 0xfb) != 0) {
        sk_pair_t r = FUN_004b3d54(pte, NULL);
        pte = r.hi;
        char c2 = *(char *)(r.lo + 0x98);
        if (c2 == 2) pte = 4;
        else if (c2 == 1) return FUN_000555ac(pte, vaddr, 0);
        else if (c2 == 0) {
            word_t *tp = (word_t *)tpidrro_el0;
            *tp = vaddr; tp[1] = 0; tp[2] = 0; tp[3] = 0;
            CallSupervisor(0); *tp = vaddr;
        }
        return pte;
    }
    word_t sub = FUN_00042abc(vspace, lvl, mask & paddr);
    word_t r = FUN_00043b44(vspace, sub, pte, mask & paddr);
    if ((r & 0xff) == 4) {
        word_t sub2 = sk_populate_level_rec(vspace, mask & paddr, lvl);
        if (sub2 != 0) r = FUN_00043b44(vspace, sub2, pte, mask & paddr);
        else goto fail;
    }
    if (r != 0) goto fail;
    return 0;
fail:
    (*(word_t **)(*(word_t *)(vspace + 0xb8) + 0x10))(*(word_t *)(vspace + 0xb0), pte);
    return 0;
}


/* ================================================================== *
 * Span-split callers (FUN_0003a7d4, 0003abf4, 0003afe4) and page-walk
 * variants (FUN_0003fcc8, 0003fa94)
 * ================================================================== */

/* FUN_0003a7d4 @ 0x3a7d4  (est. sk_span_split_caller)
 * Split a span at param_2's edge and produce two adjacent spans, then split
 * both further to isolate a requested window (the "split to [base, end]"
 * primitive). Validates the two spans are adjacent/contiguous, uses
 * sk_vspace_span_split to separate them, and re-walks the split points via
 * sk_spanmap_walk + sk_vspace_span_merge. Returns {region_a, region_b}.
 * Confidence: low (large split/merge tree surgery) */
static sk_pair_t sk_span_split_caller(word_t *p1, word_t *p2, word_t tag, word_t *out)
{
    if (tag == 0x65b648) {
        word_t a = 0, b = 0;
        word_t base = p1[1], end = p2[1];
        word_t b1 = base, b2 = end;
        word_t r1 = p1, r2 = p2;
        if (p2[1] < (word_t)p1[1]) {
            /* swap so r1 starts lower */
            b1 = p1[1]; b2 = p2[10];
            r2 = p1; r1 = p2;
            p2 = p1;
        }
        if (b1 == p2[10]) {
            if (*(uint32_t *)(r1 + 4) == *(uint32_t *)(p2 + 4)) {
                if ((*(uint32_t *)(r1 + 4) & 0xd000800) != 0) return (sk_pair_t){ 0x75b0001, 0 };
                word_t err;
                if (b2 == 0) err = 0x75c0001;
                else { err = 0; if (r1[2] + r1[1] != b2) err = 0x75d0001; }
                if ((err & 0xff) == 0) {
                    word_t f = *(uint32_t *)(r1 + 4) >> 0x10 & 1;
                    word_t local[9] = {0,0,0,0,0,0,0,0,0};
                    if (sk_lock_collection_alloc(local, (word_t)r1, 0,
                        (*(uint32_t *)(r1 + 4) != 0), f, f)) {
                        word_t lc[9] = {0,0,0,0,0,0,0,0,0};
                        FUN_00044dec((word_t)r1, lc + 1, r1[1], p2[2] + r1[2]);
                        word_t sp1, sp2;
                        sk_pair_t sr = sk_vspace_span_split(local, (word_t)r1, (void*)r1, 0, &sp1, &sp2);
                        sk_vspace_lock_exit(local, (word_t)r1);
                        word_t ra = lc[0], rb = 0;
                        if (ra != 0) {
                            word_t w[3] = {0,0,0};
                            sk_spanmap_walk(w, local, *(word_t *)(ra + 0x78), 0);
                            if ((w[0] & 0xff) != 0) SK_FATAL();
                            *(word_t *)(ra + 0x78) = w[2];
                            *(word_t *)(rb + 0x78) = DAT_004bc1f0;
                        }
                        FUN_00044ff4((word_t)r1, lc + 1);
                        if (sr.hi != 0) { *(word_t *)(sr.hi + 0x50) = 0; FUN_00033148(sr.hi); }
                        if ((sr.lo & 0xff) == 0) {
                            out[0] = ra;
                            out[1] = 0x65b648;
                            return sr;
                        }
                        if ((sr.lo & 0xff) != 0) FUN_004b30ac();
                        sk_pair_t sp3 = FUN_004b30e4();
                        word_t u13 = sp3.hi, l14 = sp3.lo;
                        word_t u5 = *(uint32_t *)(l14 + 0x20);
                        if ((u5 & 0xd000800) == 0) {
                            word_t e2 = (u13 != 0) ? 0 : 0x7fb0001;
                            word_t e3 = (u13 < *(word_t *)(l14 + 0x10)) ? e2 : 0x7f80001;
                            if ((e3 & 0xff) == 0) {
                                word_t vs = *(word_t *)(l14 + 0x50);
                                word_t n1 = (u5 != 0) ? 2 : 0;
                                word_t f2 = u5 >> 0x10 & 1;
                                word_t local2[9] = {0,0,0,0,0,0,0,0,0};
                                if (sk_lock_collection_alloc(local2, vs, 1, n1, f2, f2)) {
                                    word_t lc2[9] = {0,0,0,0,0,0,0,0,0};
                                    FUN_00044dec(vs, lc2 + 1, *(word_t *)(l14 + 8), *(word_t *)(l14 + 0x10));
                                    word_t spA, spB;
                                    sk_pair_t sr2 = sk_vspace_span_split(local2, vs, (void*)l14, u13, &spA, &spB);
                                    sk_vspace_lock_exit(local2, vs);
                                    word_t ra2 = lc2[0], rb2 = 0;
                                    if ((sr2.lo & 0xff) == 0) {
                                        if (ra2 == l14) {
                                            word_t u3 = rb2 + 0x80;
                                            word_t u11 = FUN_00032cd0(vs);
                                            word_t w2[3] = {0,0,0};
                                            if (u11 + 0xd0 < u11) SK_FATAL();
                                            FUN_00036a94(w2, *(word_t *)(l14 + 0x78),
                                                (int)((*(word_t *)(l14 + 8) + u13) - *(word_t *)(u11 + 0x28) >> 0xe) + 1);
                                            *(word_t *)(ra2 + 0x78) = w2[0];
                                            *(word_t *)(rb2 + 0x78) = w2[1];
                                        }
                                        FUN_00044ff4(vs, lc2 + 1);
                                        if (ra2 != 0 && rb2 != 0) {
                                            p1[0] = ra2; p1[1] = 0x65b648;
                                            p2[0] = rb2; p2[1] = 0x65b648;
                                        }
                                    }
                                    return sr2;
                                }
                                return (sk_pair_t){ 0x85f0002, 0 };
                            }
                        }
                    }
                    return (sk_pair_t){ 0x7bf0002, 0 };
                }
                return (sk_pair_t){ err, 0 };
            }
            return (sk_pair_t){ 0x75a0001, 0 };
        }
        return (sk_pair_t){ 0x7590001, 0 };
    }
    return (sk_pair_t){ 0x7a60001, 0 };
}

/* FUN_0003abf4 @ 0x3abf4  (est. sk_span_split_caller2)
 * Split a span and re-merge the pieces to isolate a requested window. Shared
 * validation and split/merge logic with sk_span_split_caller but targets an
 * explicit base param_2. Returns {region_a, region_b} in param_3/param_4.
 * Confidence: low */
static sk_pair_t sk_span_split_caller2(word_t span, word_t base, word_t *out_a,
                                       word_t *out_b)
{
    uint32_t f = *(uint32_t *)(span + 0x20);
    word_t perr = ((f & 0xd000800) != 0) ? 0x7f60001
        : ((base < *(word_t *)(span + 0x10)) ? ((base != 0) ? 0 : 0x7fb0001) : 0x7f80001);
    if ((perr & 0xff) != 0) return (sk_pair_t){ perr, 0 };
    word_t vs = *(word_t *)(span + 0x50);
    word_t n1 = (f != 0) ? 2 : 0;
    word_t f2 = f >> 0x10 & 1;
    word_t local[9] = {0,0,0,0,0,0,0,0,0};
    if (!sk_lock_collection_alloc(local, vs, 1, n1, f2, f2)) return (sk_pair_t){ 0x85f0002, 0 };
    word_t lc[9] = {0,0,0,0,0,0,0,0,0};
    FUN_00044dec(vs, lc + 1, *(word_t *)(span + 8), *(word_t *)(span + 0x10));
    word_t spA, spB;
    sk_pair_t sr = sk_vspace_span_split(local, vs, (void*)span, base, &spA, &spB);
    sk_vspace_lock_exit(local, vs);
    word_t ra = lc[0], rb = 0;
    if ((sr.lo & 0xff) == 0) {
        if (ra == span) {
            word_t u11 = FUN_00032cd0(vs);
            word_t w[3] = {0,0,0};
            if (u11 + 0xd0 < u11) SK_FATAL();
            FUN_00036a94(w, *(word_t *)(span + 0x78),
                (int)((*(word_t *)(span + 8) + base) - *(word_t *)(u11 + 0x28) >> 0xe) + 1);
            *(word_t *)(ra + 0x78) = w[0];
            *(word_t *)(rb + 0x78) = w[1];
        }
        FUN_00044ff4(vs, lc + 1);
        if (ra != 0 && rb != 0) {
            out_a[0] = ra; out_a[1] = 0x65b648;
            out_b[0] = rb; out_b[1] = 0x65b648;
        }
    }
    return sr;
}

/* FUN_0003afe4 @ 0x3afe4  (est. sk_span_resize)
 * Resize a span region (param_1) to [base, base+size): validate the requested
 * window against the span's bounds/alignment, split off the unwanted leading
 * and trailing pieces (sk_span_split_caller2), and re-create the span with the
 * new geometry via the region factory (sk_vspace_region_create). Returns the
 * new region or an error.
 * Confidence: low */
static sk_pair_t sk_span_resize(word_t *span, word_t base, uint32_t size, word_t *out)
{
    uint32_t f = *(uint32_t *)(span + 4);
    if ((f & 0xd000800) != 0) return (sk_pair_t){ 0x8940001, 0 };
    if (f == 0) return (sk_pair_t){ 0x8950001, 0 };
    word_t allow = (size ^ (f & 0x80) == 0);
    if (0x1000000000 - span[1] < base && allow) return (sk_pair_t){ 0x8960001, 0 };
    word_t e = span[2];
    if (!(base <= e + span[1]) && !(allow != 0)) return (sk_pair_t){ 0x8970001, 0 };
    if (size != 0 && (f >> 6 & 1) != 0) return (sk_pair_t){ 0x8980001, 0 };
    word_t cur = e - base;
    if (cur == 0) return (sk_pair_t){ 0, 0 };
    if (e < base) {
        /* extend: split leading piece off the front */
        word_t p = span[1];
        word_t a = *span;
        word_t rb = 0, ra = 0;
        if ((allow & 1) != 0) { p = p + e; goto split_to; }
        sk_pair_t sr = sk_span_split_caller2((word_t)span, cur, &ra, &rb);
        if ((sr.lo & 0xff) != 0) return sr;
        if (allow == 0) { base = cur; e = cur; }
        return sr;
split_to:
        {
            word_t rb2 = 0, ra2 = 0;
            sk_pair_t sr = sk_span_split_caller2((word_t)span, cur, &ra2, &rb2);
            if ((sr.lo & 0xff) != 0) return sr;
        }
        {
            word_t l[6] = {0,0,0,0,0,0};
            sk_pair_t sr = sk_vspace_region_create(span[10], f, (char*)&(word_t){0}, out, 0, 0);
            return sr;
        }
    }
    return (sk_pair_t){ 0, 0 };
}

/* FUN_0003fcc8 @ 0x3fcc8  (est. sk_span_leaf_walk_v2)
 * Variant of sk_span_leaf_walk taking the span, cookie and extra params; shares
 * the granule-presence pre-check and the per-page callback loop. Returns the
 * final extent (or 2 on failure).
 * Confidence: low */
static word_t sk_span_leaf_walk_v2(char *span, word_t a2, word_t a3,
                                   word_t pbase, word_t a5, int a6, uint32_t a7)
{
    word_t u5 = 0;
    uint32_t f = *(uint32_t *)(span + 0x20);
    if (a6 == 0) u5 = f >> 3 & 3;
    word_t attr = (uint32_t)((f & 0x2400) != 0);
    if ((f & 0x200) != 0) attr = 2;
    attr = attr | f >> 0x13 & 8;
    word_t cur = pbase;
    word_t r = (*span == 4) ? FUN_00043b44()
        : FUN_00043be8(a3, a5, pbase, a2, u5, attr);
    if ((r & 0xff) == 4) {
        if ((*(uint8_t *)(span + 0x23) >> 2 & 1) != 0) {
            sk_pair_t sp = FUN_004b350c();
            char *sp2 = (char *)sp.lo;
            word_t add = (cur & 0x3fff) ? 0x4000 : 0;
            word_t dom = FUN_00032cd0(*(word_t *)(sp2 + 0x50));
            if (dom <= dom + 0xd0) {
                word_t end_al = add + (cur & 0xffffffffffffc000);
                for (word_t gran = sp.hi & 0xfffffffffe000000; gran < end_al; gran += 0x2000000) {
                    word_t cap = FUN_00042abc(dom, 1, gran);
                    if ((FUN_00042c20(dom, cap) & 1) == 0) return 2;
                }
                if (sp2 + 0x80 <= sp2 + 0x90) {
                    if (FUN_00118164((void *)(sp2 + 0x80)) != 0) SK_ABORT("VAS abort");
                    word_t base = sp.hi & 0xffffffffffffc000;
                    char rtype = *sp2;
                    f = *(uint32_t *)(sp2 + 0x20);
                    word_t lvl = (f >> 0xd) & 1;
                    if (rtype != 0x11) lvl = 0;
                    word_t attr2 = (f >> 0x11 & 0x20) | lvl;
                    word_t sa[3] = {0,0,0}, sb[3] = {0,0,0};
                    word_t cbA[5] = { 0x6ad3a8, DAT_004bb180, FUN_000402b4, 0x65b710, dom };
                    word_t cbB[5] = { 0x6ad3a8, DAT_004bb180, FUN_000403b0, 0x65b740, dom };
                    word_t cur2 = base;
                    if ((f >> 0x1a & 1) == 0) {
                        word_t n = end_al - base >> 0xe;
                        word_t v = *(word_t *)(dom + 0xb0);
                        word_t *ops = *(word_t **)(dom + 0xb8);
                        if (ops[9] == 0) {
                            if (end_al != base)
                                for (word_t i = 0; i < n; i++) {
                                    word_t r1 = FUN_000402b4(&cbA, i);
                                    word_t r2 = (*(word_t *)*ops)(v, rtype, r1, r1, attr2);
                                    FUN_000403b0(&cbB, r2, i, r1);
                                }
                        } else (*(void (**)(void))(ops[9]))(v, rtype, attr2, n, &cbA, &cbB);
                    } else {
                        while (end_al != cur2) {
                            rtype = *sp2;
                            word_t v = *(word_t *)(dom + 0xb0);
                            word_t *ops = *(word_t **)(dom + 0xb8);
                            if (ops[9] == 0) {
                                word_t r1 = FUN_000402b4(&cbA, 0);
                                v = (*(word_t *)*ops)(v, rtype, r1, r1, attr2);
                                FUN_000403b0(&cbB, v, 0, r1);
                            } else (*(void (**)(void))(ops[9]))(v, rtype, attr2, 1, &cbA, &cbB);
                            if (sb[3] != 0) break;
                            word_t s = sa[3];
                            sa[3] = s + 0x4000U;
                            cur2 = s + 0x4000U;
                        }
                    }
                    if (FUN_00118194((void *)(sp2 + 0x80)) != 0) SK_ABORT("VAS abort");
                    return sb[3];
                }
            }
            SK_FATAL();
        }
        if (sk_populate_level(a3, a2, 0) == 0) return 2;
        r = (*span == 4) ? FUN_00043b44() : FUN_00043be8(a3, a5, pbase, a2, u5, attr);
    }
    if (r != 0) {
        word_t re = r & 0xff;
        if (a7 == 0 || re == 2) {
            if ((a7 & 1) != 0) goto out;
            if ((long)r < 0x207) { if (r == 2 || r == 7) goto out; }
            else if (r == 0x207 || r == 0x307) goto out;
        }
        if (re != 8 && re != 0 && (*(uint32_t *)(span + 0x20) & 0x40000) == 0) {
            word_t buf[32];
            sk_l4_error_string(buf);
            FUN_004b2820(0xeb1a02bf914012ba);
            sk_l4_error_string(buf, r);
            FUN_004afae4("Unexpected L4 Error: %s %zu err");
        }
    }
out:
    return r;
}

/* FUN_0003fa94 @ 0x3fa94  (est. sk_span_map_page_walk)
 * Map a page / walk the span page-table for physical address param_2: resolve
 * the span's domain, walk the leaf entry, and if the leaf is absent (error 4)
 * repopulate it via the granule walk, retrying the pte map. Handles the
 * preemption loop and error reporting. Returns error/status.
 * Confidence: low */
static word_t sk_span_map_page_walk(word_t span, word_t paddr, word_t a3,
                                    word_t a4, word_t a5, int a6, word_t a7)
{
    word_t u9 = a3, u12 = a4;
    word_t dom = FUN_00032cd0(*(word_t *)(span + 0x50));
    if (span + 0x90U < span + 0x80) SK_FATAL();
    if (FUN_00118164((void *)(span + 0x80)) != 0) SK_ABORT("VAS abort");
    word_t l[5] = {0,0,0,0,0};
    if (dom + 0xd0 < dom) SK_FATAL();
    FUN_000287e4(l, *(word_t *)(span + 0x78),
        (int)((word_t)(paddr - *(word_t *)(dom + 0x28)) >> 0xe) + 1);
    word_t l19 = l[0];
    *(word_t *)(span + 0x78) = l[4];
    if (l[0] != 0) {
        word_t dom2 = FUN_00032cd0(*(word_t *)(span + 0x50));
        if (dom2 <= dom2 + 0xd0) {
            word_t cap = FUN_00042abc(dom2, 1, paddr);
            if (FUN_00042c20(dom2, cap) == 0) return 2;
            if ((int)a4 == 0) CallSupervisor(2);
            else { word_t *tp = (word_t *)tpidrro_el0; *tp = 0; CallSupervisor(3); }
            word_t a3r = a3;
            if (a3 == 0) {
                sk_pair_t pr = sk_span_leaf_walk_v2((char *)span, paddr, dom2, l19, cap, a4, 0);
                a3r = pr.hi;
                if (pr.lo != 0) { do { CallSupervisor(4); } while (l19 == 1); }
            }
            if (FUN_00118194((void *)(span + 0x80)) != 0) SK_ABORT("VAS abort");
            return a3r;
        }
        SK_FATAL();
    }
    if (FUN_00118194((void *)(span + 0x80)) != 0) SK_ABORT("VAS abort");
    if ((int8_t)l[1] == 0) return 0x102;
    sk_pair_t sp = FUN_004b2fc8();
    char *sp2 = (char *)sp.lo;
    uint32_t f = *(uint32_t *)(sp2 + 0x20);
    word_t u5 = 0;
    if (a6 == 0) u5 = f >> 3 & 3;
    word_t attr = (uint32_t)((f & 0x2400) != 0);
    if ((f & 0x200) != 0) attr = 2;
    attr = attr | f >> 0x13 & 8;
    word_t cur = u12;
    word_t r = (*sp2 == 4) ? FUN_00043b44()
        : FUN_00043be8(dom, a5, u12, sp.hi, u5, attr);
    if ((r & 0xff) == 4) {
        if ((*(uint8_t *)(sp2 + 0x23) >> 2 & 1) != 0) {
            sk_pair_t sp3 = FUN_004b350c();
            sp2 = (char *)sp3.lo;
            word_t add = (cur & 0x3fff) ? 0x4000 : 0;
            word_t dom3 = FUN_00032cd0(*(word_t *)(sp2 + 0x50));
            if (dom3 <= dom3 + 0xd0) {
                word_t end_al = add + (cur & 0xffffffffffffc000);
                for (word_t gran = sp3.hi & 0xfffffffffe000000; gran < end_al; gran += 0x2000000) {
                    word_t cap = FUN_00042abc(dom3, 1, gran);
                    if ((FUN_00042c20(dom3, cap) & 1) == 0) return 2;
                }
                if (sp2 + 0x80 <= sp2 + 0x90) {
                    if (FUN_00118164((void *)(sp2 + 0x80)) != 0) SK_ABORT("VAS abort");
                    word_t base = sp3.hi & 0xffffffffffffc000;
                    char rtype = *sp2;
                    f = *(uint32_t *)(sp2 + 0x20);
                    word_t lvl = (f >> 0xd) & 1;
                    if (rtype != 0x11) lvl = 0;
                    word_t attr2 = (f >> 0x11 & 0x20) | lvl;
                    word_t sa[3] = {0,0,0}, sb[3] = {0,0,0};
                    word_t cbA[5] = { 0x6ad3a8, DAT_004bb180, FUN_000402b4, 0x65b710, dom3 };
                    word_t cbB[5] = { 0x6ad3a8, DAT_004bb180, FUN_000403b0, 0x65b740, dom3 };
                    word_t cur2 = base;
                    if ((f >> 0x1a & 1) == 0) {
                        word_t n = end_al - base >> 0xe;
                        word_t v = *(word_t *)(dom3 + 0xb0);
                        word_t *ops = *(word_t **)(dom3 + 0xb8);
                        if (ops[9] == 0) {
                            if (end_al != base)
                                for (word_t i = 0; i < n; i++) {
                                    word_t r1 = FUN_000402b4(&cbA, i);
                                    word_t r2 = (*(word_t *)*ops)(v, rtype, r1, r1, attr2);
                                    FUN_000403b0(&cbB, r2, i, r1);
                                }
                        } else (*(void (**)(void))(ops[9]))(v, rtype, attr2, n, &cbA, &cbB);
                    } else {
                        while (end_al != cur2) {
                            rtype = *sp2;
                            word_t v = *(word_t *)(dom3 + 0xb0);
                            word_t *ops = *(word_t **)(dom3 + 0xb8);
                            if (ops[9] == 0) {
                                word_t r1 = FUN_000402b4(&cbA, 0);
                                v = (*(word_t *)*ops)(v, rtype, r1, r1, attr2);
                                FUN_000403b0(&cbB, v, 0, r1);
                            } else (*(void (**)(void))(ops[9]))(v, rtype, attr2, 1, &cbA, &cbB);
                            if (sb[3] != 0) break;
                            word_t s = sa[3];
                            sa[3] = s + 0x4000U;
                            cur2 = s + 0x4000U;
                        }
                    }
                    if (FUN_00118194((void *)(sp2 + 0x80)) != 0) SK_ABORT("VAS abort");
                    return sb[3];
                }
            }
            SK_FATAL();
        }
        if (sk_populate_level(dom, sp.hi, 0) == 0) return 2;
        r = (*sp2 == 4) ? FUN_00043b44() : FUN_00043be8(dom, a5, u12, sp.hi, u5, attr);
    }
    if (r != 0) {
        word_t re = r & 0xff;
        if (a7 == 0 || re == 2) {
            if ((a7 & 1) != 0) goto out;
            if ((long)r < 0x207) { if (r == 2 || r == 7) goto out; }
            else if (r == 0x207 || r == 0x307) goto out;
        }
        if (re != 8 && re != 0 && (*(uint32_t *)(sp2 + 0x20) & 0x40000) == 0) {
            word_t buf[32];
            sk_l4_error_string(buf);
            FUN_004b2820(0xeb1a02bf914012ba);
            sk_l4_error_string(buf, r);
            FUN_004afae4("Unexpected L4 Error: %s %zu err");
        }
    }
out:
    return r;
}


/* FUN_0003dde8 @ 0x3dde8  (est. sk_spanmap_lock_build)
 * Build a locked spanmap cookie for the span param_2: verify the caller/span
 * types (ctx 0x65b5c8, span 0x65b648) and that the span is live (owner match,
 * allocated, mapped). Records {granule base, count, span} in param_1, then
 * walks each 32 MB granule of the span, resolving the level-0 entry (via
 * sk_vspace_paddr_lookup) and, for any missing granule, retiring the covered
 * pages (sk_span_prefetch_pages) so the cookie is fully mapped. Returns error.
 * Confidence: low */
static sk_pair_t sk_spanmap_lock_build(word_t *out, word_t span, word_t a3,
                                       word_t a4, word_t max_gran)
{
    sk_pair_t ctx = FUN_00034a2c();
    if (ctx.hi == 0x65b5c8 && a3 == 0x65b648) {
        word_t err = 6;
        if ((ctx.lo == 0) || (span == 0)) goto done;
        if ((*(word_t *)(span + 0x50) == ctx.lo) && (*(uint32_t *)(span + 0x20) != 0)) {
            if (((*(uint32_t *)(span + 0x20) >> 0x1a & 1) == 0) || (*(word_t *)(span + 0x10) == 0)) {
                err = 0x10490001;
            } else {
                word_t base = *(word_t *)(span + 8) & 0xfffffffffe000000;
                word_t end = *(word_t *)(span + 8) + *(word_t *)(span + 0x10);
                word_t n = (end - base) >> 0x19;
                if ((end & 0x1ffffff) != 0) n = n + 1;
                if (max_gran < n) err = 0x10500001;
                else {
                    out[0] = a4;
                    out[1] = n;
                    out[2] = span;
                    FUN_00032514(6, 0);
                    word_t dom = FUN_00032cd0();
                    if (out[1] != 0) {
                        if (dom + 0xd0 < dom) SK_FATAL();
                        word_t i = 0;
                        word_t gran = base;
                        do {
                            word_t pa = FUN_00042abc(dom, 1, gran);
                            word_t *slot = (word_t *)out[0];
                            if (slot + i < (word_t *)out[0] || (word_t *)(out[0] + out[1]) < slot + i + 1) SK_FATAL();
                            slot[i] = pa;
                            if (pa == 0) {
                                /* retire the covered pages of this granule */
                                sk_pair_t sp = FUN_004b3234();
                                word_t owner = *(word_t *)(sp.lo + 0x50);
                                char *shadow = (char *)(*(word_t **)(owner + 0x130));
                                if (*(char *)sp.lo == 0x11 && shadow != 0 && (char *)sp.lo != shadow) {
                                    if (sp.hi < *(word_t *)(sp.lo + 0x10)) {
                                        word_t vend = *(word_t *)(sp.lo + 8) + sp.hi + gran;
                                        word_t vstart = (*(word_t *)(sp.lo + 8) + sp.hi) >> 3 & 0x1fffffffffffc000;
                                        word_t add = (vend & 0x1fff8) ? 0x4000 : 0;
                                        word_t venda = add + (vend >> 0x11) * 0x4000;
                                        word_t rel = vstart - *(word_t *)(shadow + 8);
                                        if (rel < *(word_t *)(shadow + 0x10)) {
                                            word_t delta = venda - vstart;
                                            if (delta <= *(word_t *)(shadow + 0x10) - rel) {
                                                if (venda != vstart) {
                                                    word_t j = 0;
                                                    do {
                                                        word_t cb[8] = { 0x6ad3a8, DAT_004bbfd8, sk_span_retire_page, 0x65b770, rel, j, (word_t)shadow, delta };
                                                        if (*(word_t **)(sp.lo + 0x50) == (word_t *)&DAT_0064c3f0) FUN_00033b50(&cb);
                                                        else sk_span_retire_page(&cb);
                                                        j += 0x4000;
                                                    } while (j < delta);
                                                }
                                                return sp;
                                            }
                                            SK_ABORT("VAS abort");
                                        }
                                        SK_ABORT("VAS abort");
                                    } else { FUN_004b326c(); SK_ABORT("VAS abort"); }
                                }
                                return sp;
                            }
                            gran += 0x2000000;
                            i += 1;
                        } while (i < out[1]);
                        sk_span_prefetch_pages((char *)span, 0, *(word_t *)(span + 0x10));
                        err = 0;
                    }
                }
            }
        }
        goto done;
    }
    err = 6;
done:
    return (sk_pair_t){ err, 0 };
}
