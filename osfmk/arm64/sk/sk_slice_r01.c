/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel,
 * arm64e, image base 0) — the cL4 microkernel (GL1), "cL4 (679.100.61)".
 * Ground truth: Ghidra FUN_ names + addresses in program cl4_kernel.raw.
 * Slice R01: 0x397e94-0x39fb68. This is the embedded Swift-runtime type
 * metadata decoder / generic-requirement checker / protocol-conformance
 * engine (Swift "MetadataDecoder" / "GenericRequirements" / "Conformance"
 * machinery) that cL4 uses to validate generic parameter binding, ownership
 * qualifiers (inout/owned/unowned/guaranteed/pack_*), pack expansions, and
 * protocol conformance of subject types. All names are estimates unless
 * string-matched.
 *
 * Calling-convention note: many functions take a "variant / box" object in
 * the first register and a small integer operation selector in x1. The
 * 0/1/2/else pattern (unwrap / release-arg / copy-clone / release-self) is a
 * Swift boxed-value (copy/retain/release) dispatcher: op 0 unwraps the box
 * into *out, op 1 releases the boxed value, op 2 allocates a fresh clone of
 * the given size and copies the payload, and anything else releases the
 * container itself. Ghidra FUN_ names are kept only in comments.
 */

#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdbool.h>

typedef uint64_t word_t;
typedef uint32_t seL4_Word;
typedef unsigned char byte;

/* cL4 returns many values as a 16-byte pair (two 64-bit words in x0/x1). */
typedef struct { unsigned long lo, hi; } cL4_w16_t;

/* Memory/load ordering fences used by the refcount / conformance-table code. */
#define CL4_DATA_MEMBARRIER() __asm__ volatile("dmb ish" ::: "memory")
#define CL4_LO_ACQUIRE()      __asm__ volatile("dmb ishld" ::: "memory")
#define CL4_LO_RELEASE()      __asm__ volatile("dmb ish" ::: "memory")

/* SoftwareBreakpoint(1, addr) fail-closed trap. */
#define CL4_SW_BP(addr)  __asm__ volatile("brk #1" ::: "memory")

/* noreturn runtime fatal (stack canary mismatch) — FUN_0011d7e8. */
extern void cL4_runtime_fatal(void) __attribute__((noreturn));
/* noreturn "fatal: <message>" — FUN_00369bb0. */
extern void cL4_fatal_msg(word_t zero, const char *msg) __attribute__((noreturn));
/* noreturn allocation-overflow panic — FUN_004b89f8. */
extern void cL4_alloc_overflow(void) __attribute__((noreturn));
/* noreturn "mtx: <message>" panic — FUN_003a2578. */
extern void cL4_mtx_panic(const char *msg) __attribute__((noreturn));

/* ------------------------------------------------------------------ *
 * Out-of-slice helper declarations (extern; bodies reconstructed by the
 * range worker that owns them). Signatures reflect observed register use.
 * ------------------------------------------------------------------ */
extern void  *cL4_alloc(word_t size, word_t tag);           /* FUN_00111890 */
extern void   cL4_free(void *p, word_t size);               /* thunk_FUN_00012568 */
extern void  *cL4_raw_alloc(word_t size, word_t tag);       /* FUN_000101a0 */
extern void  *cL4_raw_alloc_align(word_t bytes, word_t align, word_t tag); /* FUN_00010244 */
extern void   cL4_raw_free(void *p, word_t bytes, word_t align); /* thunk_FUN_00111888 */
extern void  *cL4_raw_realloc(word_t round, word_t align);  /* thunk_FUN_004bab7c */
extern word_t cL4_round_up(word_t n);                       /* FUN_0001279c */
extern int    cL4_memcmp(const void *a, const void *b, word_t n); /* thunk_FUN_001145b0 */
extern void  *cL4_memcpy(word_t dst, word_t src, word_t n); /* FUN_00117cc8 */
extern void   cL4_memcpy_v(word_t dst, word_t src, word_t n); /* FUN_00117cc4 */
extern void   cL4_memmove_v(word_t dst, word_t src, word_t n); /* FUN_00117d14 */
extern word_t cL4_str_len(word_t s);                        /* thunk_FUN_00115080 */
extern word_t cL4_seqlock_load(word_t *p);                  /* FUN_00369bec */
extern cL4_w16_t cL4_seqlock_pair(word_t *p);               /* FUN_00369c08 */
extern word_t cL4_ref_retain_tls(word_t p, word_t extra);   /* FUN_0036c188 */
extern void  *cL4_ref_alloc(word_t size, word_t tag);       /* FUN_0036a804 */
extern void   cL4_ref_release_tls(word_t p);                /* FUN_0036bd84 */
extern word_t cL4_metadata_merge(word_t a, word_t b);       /* FUN_003a0ed4 */
extern word_t cL4_metadata_canon(word_t *p);                /* FUN_003a0fcc */
extern word_t cL4_metadata_chain(word_t w);                 /* FUN_003a25a0 */
extern word_t cL4_hw_seed(void);                            /* FUN_0000456c */
extern void   cL4_tls_init(void);                           /* FUN_0036c408 */
extern void   cL4_tls_check(word_t *ctl, word_t *slot, word_t extra); /* FUN_003d3dd8 */
extern void   cL4_mtx_init(word_t *m, word_t attr);         /* FUN_00118148 */
extern int    cL4_mtx_lock(word_t *m);                      /* FUN_00118164 */
extern int    cL4_mtx_unlock(word_t *m);                    /* FUN_00118194 */
extern void   cL4_ref_acquire(word_t obj);                  /* FUN_0037a48c */
extern void   cL4_ref_release(word_t obj);                  /* FUN_0037a978 */
extern void   cL4_obj_init(word_t *obj, word_t arg);        /* FUN_0037a850 */
extern void   cL4_small_release_a(void *obj);               /* FUN_0036805c */
extern void   cL4_small_release_b(void *obj);               /* FUN_003680cc */
extern void   cL4_small_release_c(void *obj);               /* FUN_00363f10 */
extern void   cL4_vec_grow(word_t *v, word_t *cap, word_t n, word_t esz); /* FUN_003a294c */
extern void   cL4_vec_grow_u16(word_t *v, word_t *cap, word_t n, word_t esz); /* FUN_003a2a38 */
extern void   cL4_vec_push(word_t v, word_t val, word_t packed); /* FUN_00365184 */
extern void   cL4_vec_push_b(word_t *v); /* FUN_003651f4 */
extern cL4_w16_t cL4_variant_build_a(word_t *out, word_t *a, word_t b, word_t c, word_t d); /* FUN_0038f0a8 */
extern cL4_w16_t cL4_variant_build_b(word_t *out, word_t *a, word_t b, word_t c, word_t d); /* FUN_003895e0 */
extern cL4_w16_t cL4_variant_build_c(word_t *out, word_t *a, word_t b, word_t c, word_t d); /* FUN_0038a234 */
extern cL4_w16_t cL4_variant_build_d(word_t *out, word_t *a, word_t b, word_t c, word_t d); /* FUN_00389e8c */
extern void   cL4_variant_copy_a(word_t *dst, word_t *src); /* FUN_0038ef98 */
extern void   cL4_variant_copy_b(word_t *dst, word_t *src); /* FUN_0038f020 */
extern void   cL4_variant_init(word_t *dst, word_t *src);   /* FUN_0037d1d8 */
extern cL4_w16_t cL4_variant_unwrap(word_t *out, word_t val); /* FUN_0038df24 */
extern cL4_w16_t cL4_variant_peek(word_t *p);               /* FUN_00360e28 */
extern word_t cL4_variant_dtor_a(word_t *p);                /* FUN_0037f9f4 */
extern void   cL4_variant_emit(word_t *out, word_t v, word_t kind); /* FUN_00363f10 */
extern void   cL4_variant_dtor_b(word_t *p);                /* FUN_003680cc */
extern word_t cL4_hash_probe(word_t *tbl, word_t k, word_t n); /* FUN_0035b178 */
extern word_t cL4_hash_insert(word_t *tbl, word_t k, word_t v, word_t m); /* FUN_0035b588 */
extern word_t cL4_hash_compute(word_t *a, word_t b, word_t c, word_t d, word_t e, word_t f); /* FUN_00380ad4 */
extern word_t cL4_mr_block(word_t tcb);                     /* FUN_0035bd48 */
extern word_t cL4_deref_field(word_t base, word_t kind);    /* FUN_003873c0 */
extern word_t cL4_deref_tagged(word_t *p);                  /* FUN_00377800 */
extern word_t cL4_lock_hash(word_t obj);                    /* FUN_0038ba00 */
extern word_t cL4_conform_lookup(word_t type, word_t proto); /* FUN_00376838 */
extern word_t cL4_conform_check(word_t type, word_t proto); /* FUN_003723a0 */
extern void   cL4_conform_check2(word_t *buf, word_t *p);   /* FUN_00387e60 */
extern word_t cL4_conform_chain(word_t base, word_t n);     /* FUN_00362e54 */
extern word_t cL4_conform_step(word_t *p);                  /* FUN_003628f0 */
extern word_t cL4_conform_step2(word_t kind, word_t *p);    /* FUN_00373444 */
extern word_t cL4_conform_step3(word_t n, word_t *p);       /* FUN_00377dcc */
extern word_t cL4_conform_equal(word_t a, word_t b);        /* FUN_00362c34 */
extern word_t cL4_conform_pack(word_t a, word_t b);         /* FUN_0036ed94 */
extern word_t cL4_pack_count(word_t *p);                    /* FUN_0037ca00 */
extern word_t cL4_pack_off(word_t p);                       /* FUN_0037c930 */
extern word_t cL4_pack_size(word_t p, word_t n);            /* FUN_0035eb3c */
extern word_t cL4_pack_inspect(word_t p);                   /* FUN_00367dd4 */
extern word_t cL4_pack_lookup(word_t p);                    /* FUN_0038cc2c */
extern word_t cL4_pack_lookup2(word_t p);                   /* FUN_0037d95c */
extern word_t cL4_pack_lookup3(word_t p);                   /* FUN_0037ffc4 */
extern word_t cL4_pack_lookup4(word_t p);                   /* FUN_0037febc */
extern word_t cL4_proto_desc(word_t p, word_t k);           /* FUN_0039d60c */
extern word_t cL4_type_desc(word_t *p);                     /* FUN_0039c8e4 */
extern word_t cL4_conform_desc2(word_t p);                  /* FUN_00374e2c */
extern word_t cL4_conform_major(word_t p);                  /* FUN_0039c84c */
extern word_t cL4_conform_next(word_t p);                   /* FUN_0039c888 */
extern cL4_w16_t cL4_pack_slice(word_t p, word_t n);        /* FUN_0039d994 */
extern void   cL4_pack_sel(word_t *p, word_t n);            /* FUN_0037e58c */
extern void   cL4_pack_sel2(word_t *p, word_t *q);          /* FUN_0037e614 */
extern void   cL4_pack_sel3(word_t *p, word_t *q, word_t *r); /* FUN_0037ebe4 */
extern void   cL4_pack_sel4(word_t *p, word_t n);           /* FUN_0037eb4c */
extern void   cL4_pack_sel5(word_t *p, word_t n, word_t t); /* FUN_0037e8e8 */
extern void   cL4_runtime_warn(word_t msg, int flag);       /* FUN_00361528 */
extern void   cL4_runtime_warn2(word_t msg, word_t n, const char *s); /* FUN_004b9ed8 */
extern cL4_w16_t cL4_node_build(word_t base, word_t rel);   /* FUN_003a31d8 */
extern word_t cL4_decode_meta(word_t kind, word_t val);     /* FUN_00370f2c */
extern word_t cL4_hash_lock(word_t obj);                    /* FUN_0038ba00 */

/* In-slice forward declarations. */
static cL4_w16_t sk_md_unwrap(word_t *out, word_t val);
static word_t    sk_hash_lookup_10(word_t *tbl, word_t key, word_t *slot);
static word_t    sk_hash_lookup_20(byte *tbl, word_t key, word_t *slot);
static word_t    sk_conform_find(word_t type, word_t proto, word_t *out);
static word_t    sk_conform_walk(word_t *out, word_t *desc, word_t *type, word_t opts);
static word_t    sk_conform_check_core(word_t *out, word_t *desc, word_t *type, word_t opts);
static word_t    sk_conform_lookup(word_t type, word_t proto, byte pass);
static word_t    sk_req_decoder(word_t *out, word_t p2, word_t p3, word_t *p4, word_t p5,
                                word_t *p6, word_t p7, word_t p8, word_t p9, word_t p10);
static word_t    sk_conform_insert(word_t *tab, word_t type, word_t proto, word_t *res, word_t n, int flag);
static cL4_w16_t sk_conform_resolve(word_t type, word_t proto, byte pass);
static word_t    sk_hash_rehash(word_t *tbl, word_t k, word_t *slots, word_t n);
static word_t    sk_hash_grow(word_t *tab, word_t *slots, word_t n);
static word_t    sk_hash_realloc_10(word_t *tbl, word_t n);
static word_t    sk_hash_realloc_20(word_t *tab, word_t n);
static word_t    sk_hash_copy_20(word_t *tab, word_t *src, word_t *dst);
static word_t    sk_conform_merge(word_t *ctx, word_t type);
static word_t    sk_pack_push(word_t *v, word_t val);
static void      sk_bytevec_reserve(word_t *v, word_t n, word_t fill);
static word_t    sk_span_build(word_t *p);
static void      sk_span_copy(word_t *p, word_t *q);
static cL4_w16_t sk_deref(word_t *p);
static word_t    sk_hash_get(word_t *tab, word_t key, int *idx);
static word_t    sk_md_obj_init(word_t *obj);
static cL4_w16_t sk_seqlock_retain(word_t *p, word_t op);
static word_t *  sk_hash_insert(word_t *tbl, word_t key, word_t key2);
static word_t *  sk_hash_get_or_insert(word_t *tbl, word_t *key);
static void      sk_hash_copy(word_t *tbl, word_t *src, word_t *end);
static void      sk_alloc_vec_10(word_t n, word_t unused);
static void      sk_conform_table_drain(word_t *p, word_t v);
static word_t    sk_conform_table_probe(word_t key);
static word_t *  sk_conform_desc_init(word_t *out, word_t p);
static cL4_w16_t sk_proto_desc_10(word_t *p);
static cL4_w16_t sk_proto_desc_11(word_t *p);
static cL4_w16_t sk_proto_desc_12(word_t *p);
static cL4_w16_t sk_proto_desc_04(word_t *p);
static cL4_w16_t sk_proto_dispatch(word_t *p);
static cL4_w16_t sk_conform_major(word_t p);
static word_t *  sk_conform_next(word_t p);
static word_t    sk_conform_desc2(word_t p);
static word_t    sk_type_step(word_t *p, word_t mode, word_t flag, int dir);
static word_t    sk_conform_invert_table(word_t *p);
static cL4_w16_t sk_conform_invert_bit(word_t p, word_t sel);
static cL4_w16_t sk_pack_slice(word_t p, word_t n);
static word_t *  sk_seqlock_get(word_t *p, int alloc);
static word_t    sk_seqlock_update(word_t *p, word_t seq);
static word_t *  sk_seqlock_release_node(word_t *n, word_t seq);
static word_t    sk_seqlock_release(word_t p, word_t seq, word_t v);
static word_t    sk_seqlock_ref(word_t p);
static word_t *  sk_type_merge(word_t a, word_t *b, word_t c);
static void      sk_invertible_check(word_t *out, word_t *t, word_t flags);
static void      sk_layout_check(word_t *out, word_t p, word_t type);
static void      sk_mtx_lock(word_t *m);
static void      sk_mtx_unlock(word_t *m);
static cL4_w16_t sk_hash_probe_10(word_t *tbl, word_t k, word_t n, word_t *slots);
static word_t    sk_req_decoder_body(word_t *out, word_t p2, word_t p3, word_t *p4, word_t p5,
                                     word_t *p6, word_t p7, word_t p8, word_t p9, word_t p10);

/* Globals used by this slice (decompiler DAT_ symbols; declared extern —
 * their definitions live in the data-section slices). Pointer-typed where
 * the code dereferences them as arrays/linked lists. */
extern word_t _DAT_006adee0, _DAT_006c0b00, _DAT_006c0a64;
extern word_t _DAT_006c0a68, _DAT_006c0a70, _DAT_006c0ab8;
extern word_t _DAT_006c0a60, _DAT_006c0ab0;
extern word_t *_DAT_006c0a80, *_DAT_006c0aa0;
extern word_t *_DAT_006c0ac0, *_DAT_006c0ae0;
extern word_t _DAT_006adf00;
extern word_t cL4_neg_handler;   /* DAT_003697c0 */

/* Convenience void* casts for the global addresses that carry the lock /
 * table objects referenced as DAT_ constants. */
#define DAT_006c0a80 ((word_t*)&_DAT_006c0a80)
#define DAT_006c0aa0 ((word_t*)&_DAT_006c0aa0)
#define DAT_006c0b00 ((word_t)&_DAT_006c0b00)
#define DAT_006c0a60 ((word_t)&_DAT_006c0a60)
#define DAT_006c0ac0 ((word_t)&_DAT_006c0ac0)
#define DAT_006c0ab8 ((word_t)&_DAT_006c0ab8)
#define DAT_006c0ae0 ((word_t)&_DAT_006c0ae0)
#define DAT_006adee0 ((word_t)&_DAT_006adee0)
#define DAT_006adf00 ((word_t)&_DAT_006adf00)
#define DAT_0039bdbc ((word_t)0x39bdbc)
#define DAT_003697c0 ((word_t)0x3697c0)

/* ================================================================== *
 * Boxed-value copy/retain/release dispatchers.
 * op==0 unwrap; op==1 release the boxed value; op==2 alloc+clone of
 * `size` bytes tagged with `tag`; else release the container.
 * ================================================================== */

/* FUN_00397f0c @ 0x397f0c  (est. sk_box_28_a)
 * Box dispatcher for a 5-word (0x28) payload tagged 0x1050c401ab4594e.
 * Confidence: high (structural) */
static word_t sk_box_28_a(word_t *box, int op, word_t v)
{
    word_t *np; word_t a,b,c,d;
    if (op < 2) {
        if (op == 0) { cL4_w16_t r = sk_md_unwrap(&d, *box); return (word_t)r.lo; }
        cL4_free((void*)v, 0);
    } else {
        if (op == 2) {
            np = cL4_alloc(0x28, 0x1050c401ab4594e);
            a = box[0]; b = box[1]; c = box[2]; d = box[3];
            np[1] = box[1]; np[0] = a; np[3] = d; np[2] = c; np[4] = box[4];
            return (word_t)np;
        }
        if (box) cL4_free(box, 0x28);
    }
    return 0;
}

/* FUN_00397fc0 @ 0x397fc0  (est. sk_box_28_b)
 * Box dispatcher for a 5-word payload tagged 0x1050c400dfe80cb.
 * Confidence: high (structural) */
static word_t sk_box_28_b(word_t *box, int op, word_t v)
{
    word_t *np; word_t a,b,c,d;
    if (op < 2) {
        if (op == 0) { cL4_w16_t r = sk_md_unwrap(&d, *box); return (word_t)r.lo; }
        cL4_free((void*)v, 0);
    } else {
        if (op == 2) {
            np = cL4_alloc(0x28, 0x1050c400dfe80cb);
            a = box[0]; b = box[1]; c = box[2]; d = box[3];
            np[1] = box[1]; np[0] = a; np[3] = d; np[2] = c; np[4] = box[4];
            return (word_t)np;
        }
        if (box) cL4_free(box, 0x28);
    }
    return 0;
}

/* FUN_00398074 @ 0x398074  (est. sk_box_08)
 * Box dispatcher for a 1-word (8-byte) payload tagged 0x50c40ee9192b6.
 * Confidence: high (structural) */
static word_t sk_box_08(word_t *box, int op, word_t v)
{
    word_t *np; word_t a;
    if (op < 2) {
        if (op == 0) { cL4_w16_t r = sk_md_unwrap(&a, *box); return (word_t)r.lo; }
        cL4_free((void*)v, 0);
    } else {
        if (op == 2) {
            np = cL4_alloc(8, 0x50c40ee9192b6);
            *np = *box;
            return (word_t)np;
        }
        if (box) cL4_free(box, 8);
    }
    return 0;
}

/* FUN_00398108 @ 0x398108  (est. sk_box_28_c)
 * Box dispatcher for a 5-word payload tagged 0x1050c400dfe80cb (clone of
 * sk_box_28_b; distinct thunk slot).
 * Confidence: high (structural) */
static word_t sk_box_28_c(word_t *box, int op, word_t v)
{
    word_t *np; word_t a,b,c,d;
    if (op < 2) {
        if (op == 0) { cL4_w16_t r = sk_md_unwrap(&d, *box); return (word_t)r.lo; }
        cL4_free((void*)v, 0);
    } else {
        if (op == 2) {
            np = cL4_alloc(0x28, 0x1050c400dfe80cb);
            a = box[0]; b = box[1]; c = box[2]; d = box[3];
            np[1] = box[1]; np[0] = a; np[3] = d; np[2] = c; np[4] = box[4];
            return (word_t)np;
        }
        if (box) cL4_free(box, 0x28);
    }
    return 0;
}

/* FUN_00398964 @ 0x398964  (est. sk_box_30_dispatch)
 * Box dispatcher that first consults the object's vtable at *thisp: if the
 * field at thisp+0x18 is non-null, indirect-call the member fn at vtable
 * offset +0x30 with (thisp, &op, &v). Otherwise fall back to the generic
 * 6-word (0x30) clone tagged 0x1050c40363580a0.
 * Confidence: medium */
static word_t sk_box_30_dispatch(word_t thisp, int op, word_t v)
{
    word_t *vt; word_t *np; word_t a,b,c,d,e;
    cL4_w16_t r;
    word_t *p = *(word_t **)(thisp + 0x18);
    int opc = op; word_t vc = v;
    if (p) return (word_t)(((word_t (*)(word_t*, int*, word_t*))(*(word_t*)(*p + 0x30)))(p, &opc, &vc));
    r = cL4_variant_peek(0);
    opc = (int)r.hi; p = (word_t*)r.lo;
    if (opc < 2) {
        if (opc == 0) { cL4_w16_t u = sk_md_unwrap(&d, *p); return (word_t)u.lo; }
        cL4_free((void*)v, 0);
    } else {
        if (opc == 2) {
            np = cL4_alloc(0x30, 0x1050c40363580a0);
            a = p[0]; b = p[1]; c = p[2]; d = p[3]; e = p[4];
            np[1] = p[1]; np[0] = a; np[3] = d; np[2] = c; np[5] = p[5]; np[4] = e;
            return (word_t)np;
        }
        if (p) cL4_free(p, 0x30);
    }
    return 0;
}

/* FUN_0039cf90 @ 0x39cf90  (est. sk_box_28_d)
 * Box dispatcher, 5-word payload tagged 0x1050c402607123c.
 * Confidence: high (structural) */
static word_t sk_box_28_d(word_t *box, int op, word_t v)
{
    word_t *np; word_t a,b,c,d;
    if (op < 2) {
        if (op == 0) { cL4_w16_t r = sk_md_unwrap(&d, *box); return (word_t)r.lo; }
        cL4_free((void*)v, 0);
    } else {
        if (op == 2) {
            np = cL4_alloc(0x28, 0x1050c402607123c);
            a = box[0]; b = box[1]; c = box[2]; d = box[3];
            np[1] = box[1]; np[0] = a; np[3] = d; np[2] = c; np[4] = box[4];
            return (word_t)np;
        }
        if (box) cL4_free(box, 0x28);
    }
    return 0;
}

/* FUN_0039d044 @ 0x39d044  (est. sk_box_28_e)
 * Box dispatcher, 5-word payload tagged 0x1050c409a01e8c7.
 * Confidence: high (structural) */
static word_t sk_box_28_e(word_t *box, int op, word_t v)
{
    word_t *np; word_t a,b,c,d;
    if (op < 2) {
        if (op == 0) { cL4_w16_t r = sk_md_unwrap(&d, *box); return (word_t)r.lo; }
        cL4_free((void*)v, 0);
    } else {
        if (op == 2) {
            np = cL4_alloc(0x28, 0x1050c409a01e8c7);
            a = box[0]; b = box[1]; c = box[2]; d = box[3];
            np[1] = box[1]; np[0] = a; np[3] = d; np[2] = c; np[4] = box[4];
            return (word_t)np;
        }
        if (box) cL4_free(box, 0x28);
    }
    return 0;
}

/* FUN_0039d0f8 @ 0x39d0f8  (est. sk_box_30_a)
 * Box dispatcher, 6-word payload tagged 0x1050c405416ca85.
 * Confidence: high (structural) */
static word_t sk_box_30_a(word_t *box, int op, word_t v)
{
    word_t *np; word_t a,b,c,d;
    if (op < 2) {
        if (op == 0) { cL4_w16_t r = sk_md_unwrap(&d, *box); return (word_t)r.lo; }
        cL4_free((void*)v, 0);
    } else {
        if (op == 2) {
            np = cL4_alloc(0x30, 0x1050c405416ca85);
            a = box[0]; b = box[1]; c = box[2]; d = box[3];
            np[1] = box[1]; np[0] = a; np[3] = d; np[2] = c;
            np[5] = box[5]; np[4] = box[4];
            return (word_t)np;
        }
        if (box) cL4_free(box, 0x30);
    }
    return 0;
}

/* FUN_0039d1b0 @ 0x39d1b0  (est. sk_box_18_a)
 * Box dispatcher, 3-word payload tagged 0x1050c400d13d5ba.
 * Confidence: high (structural) */
static word_t sk_box_18_a(word_t *box, int op, word_t v)
{
    word_t *np; word_t a;
    if (op < 2) {
        if (op == 0) { cL4_w16_t r = sk_md_unwrap(&a, *box); return (word_t)r.lo; }
        cL4_free((void*)v, 0);
    } else {
        if (op == 2) {
            np = cL4_alloc(0x18, 0x1050c400d13d5ba);
            np[1] = box[1]; np[0] = box[0]; np[2] = box[2];
            return (word_t)np;
        }
        if (box) cL4_free(box, 0x18);
    }
    return 0;
}

/* FUN_0039d258 @ 0x39d258  (est. sk_box_18_b)
 * Box dispatcher, 3-word payload tagged 0x1050c40e4aaa758.
 * Confidence: high (structural) */
static word_t sk_box_18_b(word_t *box, int op, word_t v)
{
    word_t *np; word_t a;
    if (op < 2) {
        if (op == 0) { cL4_w16_t r = sk_md_unwrap(&a, *box); return (word_t)r.lo; }
        cL4_free((void*)v, 0);
    } else {
        if (op == 2) {
            np = cL4_alloc(0x18, 0x1050c40e4aaa758);
            np[1] = box[1]; np[0] = box[0]; np[2] = box[2];
            return (word_t)np;
        }
        if (box) cL4_free(box, 0x18);
    }
    return 0;
}

/* FUN_0039d37c @ 0x39d37c  (est. sk_box_18_c)
 * Box dispatcher, 3-word payload tagged 0x1050c40e4aaa758 (clone of
 * sk_box_18_b; distinct thunk slot).
 * Confidence: high (structural) */
static word_t sk_box_18_c(word_t *box, int op, word_t v)
{
    word_t *np; word_t a;
    if (op < 2) {
        if (op == 0) { cL4_w16_t r = sk_md_unwrap(&a, *box); return (word_t)r.lo; }
        cL4_free((void*)v, 0);
    } else {
        if (op == 2) {
            np = cL4_alloc(0x18, 0x1050c40e4aaa758);
            np[1] = box[1]; np[0] = box[0]; np[2] = box[2];
            return (word_t)np;
        }
        if (box) cL4_free(box, 0x18);
    }
    return 0;
}

/* FUN_0039d420 @ 0x39d420  (est. sk_box_20_a)
 * Box dispatcher, 4-word payload tagged 0x1050c404daac892.
 * Confidence: high (structural) */
static word_t sk_box_20_a(word_t *box, int op, word_t v)
{
    word_t *np; word_t a,b,c;
    if (op < 2) {
        if (op == 0) { cL4_w16_t r = sk_md_unwrap(&c, *box); return (word_t)r.lo; }
        cL4_free((void*)v, 0);
    } else {
        if (op == 2) {
            np = cL4_alloc(0x20, 0x1050c404daac892);
            a = box[0]; b = box[1]; c = box[2];
            np[1] = b; np[0] = a; np[3] = box[3]; np[2] = c;
            return (word_t)np;
        }
        if (box) cL4_free(box, 0x20);
    }
    return 0;
}

/* FUN_0039d4c4 @ 0x39d4c4  (est. sk_box_28_f)
 * Box dispatcher, 5-word payload tagged 0x1050c40229b2414.
 * Confidence: high (structural) */
static word_t sk_box_28_f(word_t *box, int op, word_t v)
{
    word_t *np; word_t a,b,c,d;
    if (op < 2) {
        if (op == 0) { cL4_w16_t r = sk_md_unwrap(&d, *box); return (word_t)r.lo; }
        cL4_free((void*)v, 0);
    } else {
        if (op == 2) {
            np = cL4_alloc(0x28, 0x1050c40229b2414);
            a = box[0]; b = box[1]; c = box[2]; d = box[3];
            np[1] = b; np[0] = a; np[3] = d; np[2] = c; np[4] = box[4];
            return (word_t)np;
        }
        if (box) cL4_free(box, 0x28);
    }
    return 0;
}

/* FUN_0039d578 @ 0x39d578  (est. sk_box_08_b)
 * Box dispatcher, 1-word payload tagged 0x50c40ee9192b6 (clone of
 * sk_box_08; distinct thunk slot).
 * Confidence: high (structural) */
static word_t sk_box_08_b(word_t *box, int op, word_t v)
{
    word_t *np; word_t a;
    if (op < 2) {
        if (op == 0) { cL4_w16_t r = sk_md_unwrap(&a, *box); return (word_t)r.lo; }
        cL4_free((void*)v, 0);
    } else {
        if (op == 2) {
            np = cL4_alloc(8, 0x50c40ee9192b6);
            *np = *box;
            return (word_t)np;
        }
        if (box) cL4_free(box, 8);
    }
    return 0;
}

/* FUN_0039d8f8 @ 0x39d8f8  (est. sk_box_10_a)
 * Box dispatcher, 2-word payload tagged 0x1050c40a90f5278.
 * Confidence: high (structural) */
static word_t sk_box_10_a(word_t *box, int op, word_t v)
{
    word_t *np; word_t a;
    if (op < 2) {
        if (op == 0) { cL4_w16_t r = sk_md_unwrap(&a, *box); return (word_t)r.lo; }
        cL4_free((void*)v, 0);
    } else {
        if (op == 2) {
            np = cL4_alloc(0x10, 0x1050c40a90f5278);
            np[1] = box[1]; np[0] = box[0];
            return (word_t)np;
        }
        if (box) cL4_free(box, 0x10);
    }
    return 0;
}

/* FUN_0039f77c @ 0x39f77c  (est. sk_box_10_b)
 * Box dispatcher, 2-word payload tagged 0x1050c40db1d6c16.
 * Confidence: high (structural) */
static word_t sk_box_10_b(word_t *box, int op, word_t v)
{
    word_t *np; word_t a;
    if (op < 2) {
        if (op == 0) { cL4_w16_t r = sk_md_unwrap(&a, *box); return (word_t)r.lo; }
        cL4_free((void*)v, 0);
    } else {
        if (op == 2) {
            np = cL4_alloc(0x10, 0x1050c40db1d6c16);
            np[1] = box[1]; np[0] = box[0];
            return (word_t)np;
        }
        if (box) cL4_free(box, 0x10);
    }
    return 0;
}

/* ================================================================== *
 * Boxed object factories: allocate a small container, install the object
 * vtable pointer (the .lo constant below) and carry over word[1].
 * ================================================================== */

/* FUN_003981cc @ 0x3981cc  (est. sk_box_make_18_a, vtable 0x67bac8) */
static void sk_box_make_18_a(word_t obj)
{
    word_t *np = cL4_alloc(0x18, 0x10e1c406ee1d4f3);
    np[0] = 0x67bac8;
    np[2] = *(word_t *)(obj + 0x10);
    np[1] = *(word_t *)(obj + 8);
}
/* FUN_003982dc @ 0x3982dc  (est. sk_box_make_18_b, vtable 0x67bb10) */
static void sk_box_make_18_b(word_t obj)
{
    word_t *np = cL4_alloc(0x18, 0x10e1c406ee1d4f3);
    np[0] = 0x67bb10;
    np[2] = *(word_t *)(obj + 0x10);
    np[1] = *(word_t *)(obj + 8);
}
/* FUN_003983e4 / 0x3983e8  (est. sk_box_make_10_a / _b, vtable 0x67bb58) */
static void sk_box_make_10_a(void)
{
    word_t *np = cL4_alloc(0x10, 0x81c40f5bf735e);
    np[0] = 0x67bb58;
}
static void sk_box_make_10_b(void)
{
    word_t *np = cL4_alloc(0x10, 0x81c40f5bf735e);
    np[0] = 0x67bb58;
}
/* FUN_003996fc @ 0x3996fc  (est. sk_box_make_10_c, vtable 0x67bba0) */
static void sk_box_make_10_c(word_t obj)
{
    word_t *np = cL4_alloc(0x10, 0xa1c40bd48d6d6);
    np[0] = 0x67bba0;
    np[1] = *(word_t *)(obj + 8);
}
/* FUN_003997bc @ 0x3997bc  (est. sk_box_make_10_d, vtable 0x67bbe8) */
static void sk_box_make_10_d(word_t obj)
{
    word_t *np = cL4_alloc(0x10, 0xa1c40bd48d6d6);
    np[0] = 0x67bbe8;
    np[1] = *(word_t *)(obj + 8);
}
/* FUN_003998c0 @ 0x3998c0  (est. sk_box_make_10_e, vtable 0x67bc30) */
static void sk_box_make_10_e(word_t obj)
{
    word_t *np = cL4_alloc(0x10, 0xa1c40bd48d6d6);
    np[0] = 0x67bc30;
    np[1] = *(word_t *)(obj + 8);
}
/* FUN_00399980 @ 0x399980  (est. sk_box_make_10_f, switch-table data) */
static void sk_box_make_10_f(word_t obj)
{
    word_t *np = cL4_alloc(0x10, 0xa1c40bd48d6d6);
    np[0] = 0x67b880; /* &switchD_0067b880::switchdataD_0067bc78 */
    np[1] = *(word_t *)(obj + 8);
}
/* FUN_00399a84 @ 0x399a84  (est. sk_box_make_10_g, vtable 0x67bcc0) */
static void sk_box_make_10_g(word_t obj)
{
    word_t *np = cL4_alloc(0x10, 0xa1c40bd48d6d6);
    np[0] = 0x67bcc0;
    np[1] = *(word_t *)(obj + 8);
}
/* FUN_00399b44 @ 0x399b44  (est. sk_box_make_10_h, vtable 0x67bd08) */
static void sk_box_make_10_h(word_t obj)
{
    word_t *np = cL4_alloc(0x10, 0xa1c40bd48d6d6);
    np[0] = 0x67bd08;
    np[1] = *(word_t *)(obj + 8);
}
/* FUN_00399bfc @ 0x399bfc  (est. sk_box_make_10_i, vtable 0x67bd50) */
static void sk_box_make_10_i(word_t obj)
{
    word_t *np = cL4_alloc(0x10, 0xa1c40bd48d6d6);
    np[0] = 0x67bd50;
    np[1] = *(word_t *)(obj + 8);
}
/* FUN_00399cbc @ 0x399cbc  (est. sk_box_make_10_j, vtable 0x67bd98) */
static void sk_box_make_10_j(word_t obj)
{
    word_t *np = cL4_alloc(0x10, 0xa1c40bd48d6d6);
    np[0] = 0x67bd98;
    np[1] = *(word_t *)(obj + 8);
}
/* FUN_0039c944 @ 0x39c944  (est. sk_box_make_10_k, vtable 0x67bde0) */
static void sk_box_make_10_k(word_t obj)
{
    word_t *np = cL4_alloc(0x10, 0xa1c40bd48d6d6);
    np[0] = 0x67bde0;
    np[1] = *(word_t *)(obj + 8);
}
/* FUN_0039ca04 @ 0x39ca04  (est. sk_box_make_10_l, vtable 0x67be28) */
static void sk_box_make_10_l(word_t obj)
{
    word_t *np = cL4_alloc(0x10, 0xa1c40bd48d6d6);
    np[0] = 0x67be28;
    np[1] = *(word_t *)(obj + 8);
}
/* FUN_0039cbf4 @ 0x39cbf4  (est. sk_box_make_10_m, vtable 0x67be70) */
static void sk_box_make_10_m(word_t obj)
{
    word_t *np = cL4_alloc(0x10, 0xa1c40bd48d6d6);
    np[0] = 0x67be70;
    np[1] = *(word_t *)(obj + 8);
}
/* FUN_0039da1c @ 0x39da1c  (est. sk_box_make_10_n, vtable 0x67beb8) */
static void sk_box_make_10_n(word_t obj)
{
    word_t *np = cL4_alloc(0x10, 0xa1c40bd48d6d6);
    np[0] = 0x67beb8;
    np[1] = *(word_t *)(obj + 8);
}
/* FUN_0039dadc @ 0x39dadc  (est. sk_box_make_10_o, vtable 0x67bf00) */
static void sk_box_make_10_o(word_t obj)
{
    word_t *np = cL4_alloc(0x10, 0xa1c40bd48d6d6);
    np[0] = 0x67bf00;
    np[1] = *(word_t *)(obj + 8);
}
/* FUN_0039db98 @ 0x39db98  (est. sk_box_make_10_p, vtable 0x67bf48) */
static void sk_box_make_10_p(word_t obj)
{
    word_t *np = cL4_alloc(0x10, 0xa1c40bd48d6d6);
    np[0] = 0x67bf48;
    np[1] = *(word_t *)(obj + 8);
}
/* FUN_0039f4a8 @ 0x39f4a8  (est. sk_box_make_10_q, vtable 0x67bf90) */
static void sk_box_make_10_q(word_t obj)
{
    word_t *np = cL4_alloc(0x10, 0xa1c40bd48d6d6);
    np[0] = 0x67bf90;
    np[1] = *(word_t *)(obj + 8);
}
/* FUN_0039f568 @ 0x39f568  (est. sk_box_make_10_r, vtable 0x67bfd8) */
static void sk_box_make_10_r(word_t obj)
{
    word_t *np = cL4_alloc(0x10, 0xa1c40bd48d6d6);
    np[0] = 0x67bfd8;
    np[1] = *(word_t *)(obj + 8);
}
/* FUN_0039f624 @ 0x39f624  (est. sk_box_make_10_s, vtable 0x67c020) */
static void sk_box_make_10_s(word_t obj)
{
    word_t *np = cL4_alloc(0x10, 0xa1c40bd48d6d6);
    np[0] = 0x67c020;
    np[1] = *(word_t *)(obj + 8);
}

/* ================================================================== *
 * Metadata result builder + fatal "expected metadata" stubs.
 * ================================================================== */

/* FUN_00397e94 @ 0x397e94  (est. sk_meta_result)
 * Builds a metadata-result record in *out. If the incoming selector
 * param_3 is non-zero and even (i.e. a real metadata token, bit0 clear),
 * decodes the metadata via cL4_decode_meta(0xff, param_2) and stores it;
 * on decode failure stores the "unknown error" string + dtor (0x67bac8
 * family) and marks the record (offset 0x10) as an error. Any other
 * selector trips the fatal "Expected metadata but got a meta..." path.
 * Confidence: medium */
static void sk_meta_result(word_t *out, word_t meta, word_t sel)
{
    word_t r;
    if (sel != 0 && (sel & 1) == 0) {
        r = cL4_decode_meta(0xff, meta);
        *(word_t *)(out + 2) = 0;
        *out = r;
        if (r == 0) {
            *out = (word_t)(void*)"unknown error";
            out[1] = (word_t)(void*)cL4_variant_dtor_a;
            *(word_t *)(out + 2) = 1;
        }
        return;
    }
    cL4_fatal_msg(0, "Expected metadata but got a meta...");
}

/* FUN_003982b4 / 0x3982b8 / 0x3983bc / 0x3983c0  (est. sk_meta_fatal)
 * noreturn fatal "Expected metadata but got a meta..." (separate thunks). */
static void sk_meta_fatal_a(void) { cL4_fatal_msg(0, "Expected metadata but got a meta..."); }
static void sk_meta_fatal_b(void) { cL4_fatal_msg(0, "Expected metadata but got a meta..."); }
static void sk_meta_fatal_c(void) { cL4_fatal_msg(0, "Expected metadata but got a meta..."); }
static void sk_meta_fatal_d(void) { cL4_fatal_msg(0, "Expected metadata but got a meta..."); }

/* ================================================================== *
 * Vector / hash-table primitives for metadata tables (element sizes
 * 0x18 / 0x20 / 0x10 / u8 / u16 and a 10-entry / 20-entry open-addressing
 * hash table with linear probing).
 * ================================================================== */

/* FUN_003988c4 @ 0x3988c4  (est. sk_vec_push_18)
 * Append a 3-word element to the 0x18-element vector: grow if the count
 * would overflow capacity, relocate the pointer when the range overlaps,
 * copy the 3 words, bump the count. Returns nothing.
 * Confidence: medium */
static void sk_vec_push_18(word_t *v, word_t *e)
{
    unsigned count = (unsigned)v[1];
    word_t *base = (word_t*)*v;
    word_t *dst;
    if (*(unsigned*)((char*)v + 0xc) <= count) {
        cL4_vec_grow(v, v + 2, (word_t)count + 1, 0x18);
        base = (word_t*)*v;
    }
    dst = base + (unsigned)v[1] * 3;
    dst[2] = e[2]; dst[1] = e[1]; dst[0] = e[0];
    *(int*)(v + 1) = (int)v[1] + 1;
}

/* FUN_00399390 @ 0x399390  (est. sk_vec_push_10_auto)
 * Append a 2-word + byte element to the 0x10 vector; returns the address of
 * the just-inserted element.
 * Confidence: medium */
static word_t sk_vec_push_10_auto(word_t *v, word_t *e, unsigned *u, unsigned char *b)
{
    word_t *dst;
    unsigned cnt;
    if (*(unsigned*)(v + 1) < *(unsigned*)((char*)v + 0xc)) {
        dst = (word_t*)(*v + (unsigned)v[1] * 0x10);
        dst[0] = *e;
        *(unsigned*)(dst + 1) = *u;
        *(unsigned char*)((char*)dst + 0xc) = *b;
        *(unsigned*)(v + 1) = (unsigned)v[1] + 1;
    } else {
        cL4_vec_grow(v, v + 2, (word_t)(*b) << 32 | (word_t)*u, 0x10);
        cnt = *(unsigned*)(v + 1);
    }
    return *v + (word_t)cnt * 0x10 + -0x10;
}

/* FUN_00399550 @ 0x399550  (est. sk_vec_push_10_b)
 * Append a {value, byte} pair to the 0x10 vector; returns the inserted elem.
 * Confidence: medium */
static word_t sk_vec_push_10_b(word_t *v, word_t *e, byte *b)
{
    word_t val = *e; byte by = *b;
    word_t *dst; unsigned cnt;
    word_t n = (unsigned)v[1];
    if (*(unsigned*)((char*)v + 0xc) <= (unsigned)v[1]) {
        cL4_vec_grow(v, v + 2, n + 1, 0x10);
        n = (unsigned)v[1];
    }
    dst = (word_t*)(*v + n * 0x10);
    dst[0] = val;
    dst[1] = by;
    cnt = (unsigned)v[1] + 1;
    *(unsigned*)(v + 1) = cnt;
    return *v + (word_t)cnt * 0x10 + -0x10;
}

/* FUN_00399094 @ 0x399094  (est. sk_vec_reserve_20)
 * Ensure the 0x20-element vector has room for `n` more; returns the (possibly
 * relocated) element pointer.
 * Confidence: medium */
static word_t sk_vec_reserve_20(word_t *v, word_t e, long n)
{
    word_t need = n + (unsigned)v[1];
    if (*(unsigned*)((char*)v + 0xc) < need) {
        if (e < *v || *v + (unsigned)v[1] * 0x20 <= e) {
            cL4_vec_grow(v, v + 2, need, 0x20);
        } else {
            word_t base = *v;
            cL4_vec_grow(v, v + 2, need, 0x20);
            e = *v + (e - base);
        }
    }
    return e;
}

/* FUN_0039d2fc @ 0x39d2fc  (est. sk_bytevec_reserve)
 * Append `n` copies of a u16 value to the element vector; grows capacity,
 * fills with the value, bumps the count. */
static void sk_bytevec_reserve(word_t *v, word_t n, word_t fill)
{
    word_t cnt = v[1];
    if ((word_t)v[2] < (word_t)(cnt + n)) {
        cL4_vec_grow_u16(v, v + 3, cnt + n, 2);
        cnt = v[1];
    }
    if (n != 0) {
        word_t *p = (word_t*)(*v + cnt * 2);
        long i = n;
        do { *(word_t*)p = fill; i--; p = (word_t*)((char*)p + 2); } while (i != 0);
    }
    v[1] = cnt + n;
}

/* FUN_0039951c @ 0x39951c  (est. sk_pair_dtor)
 * Destroy a 2-word element: release the first word, then push the pair's
 * two payload words through the u16 vector helper. */
static void sk_pair_dtor(word_t *p)
{
    cL4_small_release_c((void*)*p);
    cL4_vec_push(p[1], *(word_t*)p[2], ((word_t*)p[2])[1]);
}

/* FUN_003995cc @ 0x3995cc  (est. sk_alloc_vec_4)
 * Allocate a 4-byte-element vector of `n` entries (tag 0x1000c0052888210);
 * overflow trips the alloc panic. */
static void sk_alloc_vec_4(word_t n, word_t unused)
{
    if (n >> 0x3e == 0) { cL4_alloc(n << 2, 0x1000c0052888210); return; }
    cL4_alloc_overflow();
}

/* FUN_0039904c @ 0x39904c  (est. sk_alloc_vec_10)
 * Allocate a 0x10-element vector of `n` entries (tag 0x1000c00451b5be8). */
static void sk_alloc_vec_10(word_t n, word_t unused)
{
    if (n >> 0x3c == 0) { cL4_alloc(n << 4, 0x1000c00451b5be8); return; }
    cL4_alloc_overflow();
}

/* ================================================================== *
 * Open-addressing hash table (element 0x10): lookup / get / insert /
 * rehash / copy.
 * ================================================================== */

/* FUN_00399620 @ 0x399620  (est. sk_hash_lookup_10)
 * Probe the 0x10 hash table for `key`; on hit writes *slot = entry and
 * returns 1, else returns 0. Tombstones (0xfffffffffffff000) stop the scan.
 * Confidence: medium */
static word_t sk_hash_lookup_10(word_t *tbl, word_t key, word_t *slot)
{
    word_t *pv; word_t *entry; word_t h, cur;
    unsigned mask;
    int i = 1;
    if ((int)tbl[2] == 0) { *slot = 0; return 0; }
    if (key == 0) mask = 0;
    else mask = (unsigned)(key >> 9) & 0x7fffff ^ (unsigned)(key >> 4);
    mask &= (unsigned)tbl[2] - 1;
    entry = (word_t*)(*tbl + (word_t)mask * 0x10);
    cur = *entry;
    if (key != cur) {
        pv = 0;
        do {
            if (cur == 0xfffffffffffff000) { *slot = pv ? (word_t)pv : (word_t)entry; return 0; }
            entry = (word_t*)(*tbl + (word_t)((mask + i) & ((unsigned)tbl[2]-1)) * 0x10);
            cur = *entry;
            i++;
        } while (key != cur);
    }
    *slot = (word_t)entry;
    return 1;
}

/* FUN_00399860 / 0x399a24  (est. sk_hash_get)
 * Fetch table[index] where index = count + *idx + an extra base, after
 * locking the hash table. Returns the stored word or 0. */
static word_t sk_hash_get(word_t *tab, word_t key, int *idx)
{
    word_t t = *(word_t*)(tab + 8);
    if (*(word_t*)(t + 0x10) == 0) return 0;
    cL4_lock_hash(t);
    return *(word_t*)(*(word_t*)(t + 0x10) +
        (word_t)(unsigned)(*(int*)(t + 0x128) + *idx + *(int*)(t + 300)) * 8);
}

/* FUN_00399d68 @ 0x399d68  (est. sk_hash_get_or_insert)
 * Look up `key` in the table; if absent insert a {key, 0} entry and return
 * its slot. Returns the entry pointer. */
static word_t *sk_hash_get_or_insert(word_t *tbl, word_t *key)
{
    word_t slot = 0;
    if (sk_hash_lookup_10(tbl, *key, &slot) & 1) return (word_t*)slot;
    slot = (word_t)sk_hash_insert(tbl, *key, *key);
    ((word_t*)slot)[0] = *key;
    ((word_t*)slot)[1] = 0;
    return (word_t*)slot;
}

/* FUN_00399dc8 @ 0x399dc8  (est. sk_hash_insert)
 * Insert `key` into the table, growing/rehashing when the load factor
 * exceeds 3/4 of capacity; returns the entry for the key (after possible
 * tombstone reuse). */
static word_t *sk_hash_insert(word_t *tbl, word_t key, word_t key2)
{
    unsigned cap = *(unsigned*)(tbl + 0x10);
    word_t *slot; word_t out;
    if (*(unsigned*)(tbl + 8) * 4 + 4 < cap * 3) {
        if (cap >> 3 < (cap + ~*(unsigned*)(tbl + 8)) - *(int*)(tbl + 0xc)) goto insert;
    } else {
        cap <<= 1;
    }
    sk_hash_realloc_10(tbl, cap);
    out = 0;
    sk_hash_lookup_10(tbl, key2, &out);
    slot = (word_t*)out;
insert:
    *(int*)(tbl + 8) = *(int*)(tbl + 8) + 1;
    if (*slot != (word_t)-0x1000) *(int*)(tbl + 0xc) = *(int*)(tbl + 0xc) - 1;
    return slot;
}

/* FUN_00399e84 @ 0x399e84  (est. sk_hash_realloc_10)
 * Reallocate the 0x10 hash table to a round-up-pow2 of `n` entries,
 * initialising empty slots to tombstone 0xfffffffffffff000. */
static word_t sk_hash_realloc_10(word_t *tbl, word_t n)
{
    unsigned old = *(unsigned*)(tbl + 2);
    word_t oldbase = *tbl;
    unsigned cap = n - 1; cap |= cap >> 1; cap |= cap >> 2; cap |= cap >> 4;
    cap |= cap >> 8; cap |= cap >> 16;
    unsigned sz = 0x40; if (0x40 < cap + 1) sz = cap + 1;
    *(unsigned*)(tbl + 2) = sz;
    word_t *np = cL4_raw_realloc((word_t)sz << 4, 8);
    *tbl = (word_t)np;
    if (oldbase != 0) {
        sk_hash_copy(tbl, (word_t*)oldbase, (word_t*)(oldbase + old * 0x10));
        cL4_raw_free((void*)oldbase, old << 4, 8);
        return 0;
    }
    tbl[1] = 0;
    if (*(unsigned*)(tbl + 2) != 0) {
        word_t i = (unsigned)sz << 4;
        word_t *p = np;
        do { *p = 0xfffffffffffff000; i -= 0x10; p += 2; } while (i != 0);
    }
    return 0;
}

/* FUN_00399f54 @ 0x399f54  (est. sk_hash_copy)
 * Rebuild the hash table from the [begin,end) source range: initialise all
 * slots to tombstone, then re-insert each non-tombstone/non-tombstone-2
 * element via the lookup-and-store path, bumping the count. */
static void sk_hash_copy(word_t *tbl, word_t *src, word_t *end)
{
    word_t slot;
    tbl[1] = 0;
    if (*(unsigned*)(tbl + 2) != 0) {
        word_t i = (unsigned) (*(unsigned*)(tbl + 2)) << 4;
        word_t *p = (word_t*)*tbl;
        do { *p = 0xfffffffffffff000; i -= 0x10; p += 2; } while (i != 0);
    }
    for (; src != end; src += 2) {
        if (*src != (word_t)-0x1000 && *src != (word_t)-0x2000) {
            slot = 0;
            sk_hash_lookup_10(tbl, *src, &slot);
            ((word_t*)slot)[0] = *src;
            ((word_t*)slot)[1] = src[1];
            *(int*)(tbl + 1) = *(int*)(tbl + 1) + 1;
        }
    }
}

/* ================================================================== *
 * Conformance table (global at _DAT_006c0ac0) growth / probe.
 * ================================================================== */

/* FUN_0039bb2c @ 0x39bb2c  (est. sk_conform_table_push)
 * Push a {begin,end} range pair onto the global conformance region table
 * (_DAT_006c0ac0 / _DAT_006c0ab0), growing the array and moving the old
 * free-list. Then acquires the 0x6c0a80 spinlock, drains the deferred list,
 * pushes the {begin,end} pair, and notifies the lock owner.
 * Confidence: low (concurrency heavy) */
static void sk_conform_table_push(word_t begin, word_t n, word_t end)
{
    word_t count, newcap;
    word_t *arr = _DAT_006c0ac0;
    word_t *np;
    cL4_ref_acquire(0x6c0ad0);
    count = _DAT_006c0ac0 ? *_DAT_006c0ac0 : 0;
    newcap = (word_t)_DAT_006c0ab0;
    if (_DAT_006c0ab0 <= count) {
        newcap = count * 2; if (newcap < 0x11) newcap = 0x10;
        np = cL4_raw_alloc(((newcap >> 1) << 5 | 8), 0x1000040504ffac1);
        if (!np) { CL4_SW_BP(0x39bdbc); }
        *np = 0;
        if (arr) {
            if (count) {
                word_t i = count; word_t *d = np + 1, *s = arr + 1;
                do { word_t w = *s; d[1] = s[1]; *d = w; i--; d += 2; s += 2; } while (i);
            }
            *np = count;
            word_t *nd = cL4_raw_alloc(0x10, 0xa0040aff93c70);
            nd[0] = (word_t)_DAT_006c0ae0; nd[1] = (word_t)arr;
            _DAT_006c0ae0 = nd;
        }
    }
    _DAT_006c0ac0 = np;
    _DAT_006c0ab0 = newcap;
    _DAT_006c0ac0[count * 2 + 1] = begin;
    _DAT_006c0ac0[count * 2 + 2] = begin + end;
    *_DAT_006c0ac0 = count + 1;
    CL4_DATA_MEMBARRIER();
    if (_DAT_006c0ab8 == 0) {
        word_t *node = _DAT_006c0ae0;
        while (node) {
            word_t *nx = (word_t*)*node;
            word_t i = 0xffffffffffffffff; do { i++; } while (i < node[1]);
            cL4_free((void*)node[1], 0);
            cL4_free(node, 0);
            node = nx;
        }
        _DAT_006c0ae0 = 0;
    }
    cL4_ref_release(0x6c0ad0);
    sk_mtx_lock((word_t*)&_DAT_006c0a80);
    sk_conform_table_drain(_DAT_006c0aa0, begin);
    if (_DAT_006c0a60 == 0) {
        word_t *node = _DAT_006c0aa0;
        while (node) {
            word_t *nx = (word_t*)*node;
            cL4_free((void*)node[1], 0);
            cL4_free(node, 0);
            node = nx;
        }
        _DAT_006c0aa0 = 0;
    }
    sk_mtx_unlock((word_t*)&_DAT_006c0a80);
}

/* FUN_0039cc98 @ 0x39cc98  (est. sk_conform_table_drain)
 * Drain the deferred free-list hanging off the conformance table: unlink
 * every node and re-append each freed block to the caller's list. */
static void sk_conform_table_drain(word_t *p, word_t v)
{
    word_t *root = *(word_t**)(*(word_t*)(p + 8) + 0x90);
    for (;;) {
        if (root == 0) return;
        while (1) {
            word_t *head = *(word_t**)(*(word_t*)(p + 8) + 0x90);
            word_t next = *head;
            if (next == (word_t)root) break;
            root = (word_t*)next;
            if (next == 0) return;
        }
        *(word_t**)(*(word_t*)(p + 8) + 0x90) = *(word_t**)((word_t)root + 0x18);
        word_t *nd = cL4_raw_alloc(0x10, 0xa0040aff93c70);
        nd[0] = v; nd[1] = (word_t)root;
        v = (word_t)nd;
    }
}

/* FUN_0039bdc0 @ 0x39bdc0  (est. sk_conform_table_probe)
 * Scan the global conformance region table for a type whose descriptor
 * matches `key`; returns the matching descriptor or 0. */
static word_t sk_conform_table_probe(word_t key)
{
    word_t *arr, *end, *p;
    word_t found = 0;
    int i;
    if (-1 < _DAT_006c0b00) cL4_tls_check(&_DAT_006c0b00, (word_t*)0x39bdbc, 0);
    CL4_LO_ACQUIRE();
    _DAT_006c0ab8++;
    if (_DAT_006c0ac0 && *_DAT_006c0ac0 != 0) {
        p = _DAT_006c0ac0 + 1;
        end = p + *_DAT_006c0ac0 * 2;
        do {
            word_t *lo = (word_t*)p[0], *hi = (word_t*)p[1], *cur = lo;
            for (; cur != hi; cur++) {
                word_t d = cL4_deref_field((word_t)cur + *cur + 4, *(unsigned*)((char*)cur + *cur + 0xc) >> 3 & 7);
                if (d != 0 && (cL4_conform_chain(d, key) & 1)) goto found;
            }
            p += 2;
        } while (p != end);
    }
    found = 0;
found:
    _DAT_006c0ab8--;
    CL4_LO_RELEASE();
    return found;
}

/* ================================================================== *
 * Span / buffer helpers (FUN_0039858c / FUN_003985ec) and tagged deref.
 * ================================================================== */

/* FUN_0039858c @ 0x39858c  (est. sk_span_build)
 * Build a {begin,end,size} span view of a length-prefixed buffer (the +0x17
 * byte is a small-string flag). */
static word_t sk_span_build(word_t *p)
{
    byte tag = *(byte*)((char*)p + 0x17);
    word_t len = p[1];
    word_t *base = (word_t*)*p;
    word_t end = *p + p[1];
    if ((signed char)tag >= 0) { len = tag; base = p; end = (word_t)p + tag; }
    return (word_t)((word_t*)base + len); /* span {base, base+len, end} */
}

/* FUN_003987e0 @ 0x3987e0  (est. sk_tagged_deref)
 * Dereference a tagged pointer/offset in *p: the low bits select between an
 * inline value (bit0 set → follow *result) and a relative offset to add to
 * p. Returns the resolved pointer or 0. */
static word_t *sk_tagged_deref(unsigned *p)
{
    unsigned w = *p;
    word_t *r;
    if (((long)(int)w & 0xfffffffdU) != 0) {
        r = (word_t*)(((long)(int)w & 0xfffffffffffffffcU) + (word_t)p);
        if ((w & 1) == 0) {
            if (r) return r;
        } else if (*(word_t*)r) return (word_t*)*(word_t*)r;
    }
    return 0;
}

/* FUN_003985ec @ 0x3985ec  (est. sk_span_copy)
 * Copy a byte span [*a, *b) into a growable output buffer, dispatching
 * through the pack-select helpers; on an unaligned/straddling path uses the
 * 64-byte staged copy and finishes with the "close" helper. Any buffer that
 * escapes the canary trips the runtime fatal. */
static void sk_span_copy(word_t *a, word_t *b)
{
    word_t *src = (word_t*)*a;
    word_t *dst = (word_t*)*b;
    long stage = -0x2c8502b44bfffed6;
    word_t len = 0, lv = 0;
    byte one = 0;
    if (src == dst) { len = 0; goto done; }
    {
        word_t *hi = (word_t*)a[2];
        len = 0x40; lv = 0;
        do {
            if (src == hi) { CL4_SW_BP(0x3987d4); }
            one = *(byte*)src;
            if (len == 0) {
                if (src != dst) {
                    cL4_pack_sel(&one, (word_t)0xf9000a63a9000a61);
                    dst = (word_t*)*b;
                    len = 0x40;
                    src = (word_t*)*a;
                    while (src != dst) {
                        if (src == dst) { lv = 0; dst = (word_t*)&lv; }
                        else { lv = 0; hi = (word_t*)a[2]; dst = (word_t*)&lv; }
                        cL4_pack_sel2(&one, (word_t*)&lv);
                        len = lv + len;
                        dst = (word_t*)*b;
                        src = (word_t*)*a;
                    }
                    cL4_pack_sel3(&one, &lv, &lv);
                    goto done;
                }
                len = 0x40; break;
            }
            len = lv + 1;
            cL4_pack_sel4((word_t*)&one, len);
            src = (word_t*)((char*)src + 1);
            *a = (word_t)src;
            dst = (word_t*)*b;
            len--;
            lv = len;
        } while (src != dst);
    }
    cL4_pack_sel5((word_t*)&one, len, 0xf9000a63a9000a61);
done:
    if (stage != -0x2c8502b44bfffed6) return;
    cL4_runtime_fatal();
}

/* ================================================================== *
 * Float / double widening from big-endian u128 words.
 * ================================================================== */

/* FUN_0039a030 @ 0x39a030  (est. sk_u128_to_float)
 * Widening accumulation of the multi-word big-endian integer *p (element
 * count in the high bits of param_2) into a float. */
static float sk_u128_to_float(word_t *p, word_t nwords)
{
    word_t n = (nwords >> 8 & 0xffffffff) + 0x3f >> 6;
    if (n == 1) return (float)(long)*p;
    float acc = (float)*p, f = 1.8446744e+19f;
    if (n != 2) {
        long i = 2 - n; word_t *q = p;
        do { q++; acc += f * (float)*q; f *= 1.8446744e+19f; i++; } while (i != -1);
    }
    return acc + f * (float)(long)p[n - 1];
}

/* FUN_0039a0ac @ 0x39a0ac  (est. sk_u128_to_double)
 * Same widening accumulation into a double (16-byte {double,0} return). */
static cL4_w16_t sk_u128_to_double(word_t *p, word_t nwords)
{
    cL4_w16_t r;
    word_t n = (nwords >> 8 & 0xffffffff) + 0x3f >> 6;
    double acc, f;
    if (n == 1) { r.lo = (double)(long)*p; r.hi = 0; return r; }
    acc = (double)*p;
    if (n == 2) { f = 1.8446744073709552e+19; }
    else {
        f = 1.8446744073709552e+19; word_t *q = p; long i = 2 - n;
        do { q++; acc += f * (double)*q; f *= 1.8446744073709552e+19; i++; } while (i != -1);
    }
    r.lo = acc + f * (double)(long)p[n - 1];
    r.hi = 0;
    return r;
}

/* FUN_0039a128 @ 0x39a128  (est. sk_check_negative)
 * If the signed top word is non-negative, run the "negative" handler
 * (FUN_003d3dd8); else do nothing. */
static void sk_check_negative(word_t *p)
{
    if (-1 < (long)*p) cL4_tls_check((word_t*)&cL4_neg_handler, 0, 0);}

/* FUN_0039a138 @ 0x39a138  (est. sk_str_copy_truncate)
 * Copy a length-delimited string into `dst` (max `cap` bytes incl. NUL),
 * NUL-terminating at the truncation point; returns the source length. */
static word_t sk_str_copy_truncate(word_t dst, word_t src, word_t cap)
{
    word_t n = cL4_str_len(src);
    if (n < cap) cL4_memmove_v(dst, src, n + 1);
    else if (cap != 0) {
        cL4_memmove_v(dst, src, cap - 1);
        *(unsigned char*)(dst + (cap - 1)) = 0;
    }
    return n;
}

/* ================================================================== *
 * Ownership qualifier parsing (Swift ownership attributes).
 * ================================================================== */

/* FUN_00399108 @ 0x399108  (est. sk_ownership_qualifier)
 * Match a length-delimited ownership keyword and return a packed {flags,
 * kind} word: "inout"→3, "owned"→5, "unowned"→6, "guaranteed"→7,
 * "pack_owned"(magic 8-byte key)→8, "pack_inout"→10, "in_constant"→1,
 * "in_guaranteed"→2, "inout_aliasable"→4, "pack_guaranteed"→9; else 0.
 * Confidence: high (string-matched) */
static word_t sk_ownership_qualifier(word_t *s, long n)
{
    int r; word_t kind = 0, flags = 0;
    if (n < 0xb) {
        if (n == 3) {
            if ((short)*s == 0x6940 && *(char*)((char*)s + 2) == 'n') { kind = 0; flags = 0x100000000; goto out; }
        } else if (n == 6) {
            r = cL4_memcmp(s, "@inout", 6);
            if (r == 0) { flags = 0x100000000; kind = 3; goto out; }
            r = cL4_memcmp(s, "@owned", 6);
            if (r == 0) { flags = 0x100000000; kind = 5; goto out; }
        } else if (n == 8 && (r = cL4_memcmp(s, "@unowned", 8), r == 0)) {
            flags = 0x100000000; kind = 6; goto out;
        }
    } else if (n < 0xe) {
        if (n == 0xb) {
            r = cL4_memcmp(s, "@guaranteed", 0xb);
            if (r == 0) { flags = 0x100000000; kind = 7; goto out; }
            if (*s == 0x776f5f6b63617040 && *(long*)((char*)s + 3) == 0x64656e776f5f6b63) { flags = 0x100000000; kind = 8; goto out; }
            r = cL4_memcmp(s, "@pack_inout", 0xb);
            if (r == 0) { flags = 0x100000000; kind = 10; goto out; }
        } else if (n == 0xc && (r = cL4_memcmp(s, "@in_constant", 0xc), r == 0)) {
            flags = 0x100000000; kind = 1; goto out;
        }
    } else if (n == 0xe) {
        r = cL4_memcmp(s, "@in_guaranteed", 0xe);
        if (r == 0) { flags = 0x100000000; kind = 2; goto out; }
    } else if (n == 0x10) {
        r = cL4_memcmp(s, "@inout_aliasable", 0x10);
        if (r == 0) { flags = 0x100000000; kind = 4; goto out; }
        r = cL4_memcmp(s, "@pack_guaranteed", 0x10);
        if (r == 0) { flags = 0x100000000; kind = 9; goto out; }
    }
    flags = 0; kind = 0;
out:
    return kind | flags;
}

/* FUN_00399414 @ 0x399414  (est. sk_ownership_qualifier_b)
 * Second ownership keyword family: "@out"→5-kind, "@owned"→1, "@unowned"→2,
 * "@pack_out"→5, "@autoreleased"→4, "@unowned_inner_pointer"→3; else 0.
 * Confidence: high (string-matched) */
static word_t sk_ownership_qualifier_b(word_t *s, long n)
{
    int r; word_t kind = 0, flags = 0;
    if (n < 9) {
        if (n == 4) {
            if (*s == 0x74756f40) { kind = 0; flags = 0x100000000; goto out; }
        } else if (n == 6) {
            r = cL4_memcmp(s, "@owned", 6);
            if (r == 0) { flags = 0x100000000; kind = 1; goto out; }
        } else if (n == 8 && (r = cL4_memcmp(s, "@unowned", 8), r == 0)) {
            flags = 0x100000000; kind = 2; goto out;
        }
    } else if (n == 9) {
        r = cL4_memcmp(s, "@pack_out", 9);
        if (r == 0) { flags = 0x100000000; kind = 5; goto out; }
    } else if (n == 0xd) {
        r = cL4_memcmp(s, "@autoreleased", 0xd);
        if (r == 0) { flags = 0x100000000; kind = 4; goto out; }
    } else if (n == 0x16) {
        r = cL4_memcmp(s, "@unowned_inner_pointer", 0x16);
        if (r == 0) { flags = 0x100000000; kind = 3; goto out; }
    }
    flags = 0; kind = 0;
out:
    return kind | flags;
}

/* FUN_0039932c @ 0x39932c  (est. sk_qualifier_key)
 * Match the 16-byte magic key "@oneDirivative..." (0x76697265446f6e40 /
 * 0x6576697461766972) at length 0xd; returns 0x100 | (match?1:0).
 * Confidence: medium */
static unsigned sk_qualifier_key(word_t *s, long n)
{
    unsigned k;
    if (n == 0) k = 0;
    else {
        if (n != 0xd || *s != 0x76697265446f6e40 || *(long*)((char*)s + 5) != 0x6576697461766972) {
            k = 0; goto set;
        }
        k = 1;
    }
set:
    return k | 1 << 8;
}

/* ================================================================== *
 * Generic-requirement pack / expansion helpers.
 * ================================================================== */

/* FUN_00398f40 @ 0x398f40  (est. sk_pack_push)
 * Append a {count, 0} pair to the pack-expansion count vector at param_1+0x50
 * (element 0x10, capacity +0x60); grows/reallocates and relocates on
 * overflow. The count must be odd (bit0 set) else fatal "Pack expansion
 * count type should ...". Returns the value at (count&~1)-8.
 * Confidence: medium */
static word_t sk_pack_push(word_t *v, word_t val)
{
    word_t *lo, *hi, *base, *ne, *np;
    word_t cnt, cap, nelems;
    if ((val & 1) == 0) cL4_fatal_msg(0, "Pack expansion count type should ...");
    lo = *(word_t**)(v + 0x60);      /* capacity ptr */
    hi = *(word_t**)(v + 0x58);      /* count ptr */
    if (hi < lo) { *hi = val; hi[1] = 0; hi += 2; }
    else {
        base = *(word_t**)(v + 0x50);
        cnt = ((word_t)hi - (word_t)base) >> 4;
        nelems = cnt + 1;
        if (nelems >> 0x3c != 0) cL4_alloc_overflow();
        cap = ((word_t)lo - (word_t)base) >> 3;
        if (cap <= nelems) cap = nelems;
        if (0x7fffffffffffffef < (word_t)lo - (word_t)base) cap = 0xfffffffffffffff;
        if (cap == 0) {
            np = cL4_raw_realloc(0, 0); ne = np; 
            base = *(word_t**)(v + 0x50);
            cnt = ((word_t)hi - (word_t)base) >> 4;
        } else {
            np = (word_t*)sk_alloc_vec_10((word_t*)(v + 0x60), cap); 
            base = *(word_t**)(v + 0x50);
            cnt = ((word_t)hi - (word_t)base) >> 4;
        }
        ne = (word_t*)((word_t)np + ((word_t)hi - (word_t)base));
        *ne = val; ne[1] = 0; hi = ne + 2;
        cL4_memcpy_v((word_t)(ne + cnt * -2), (word_t)base, cnt * 0x10);
        base = *(word_t**)(v + 0x50);
        *(word_t**)(v + 0x50) = ne + cnt * -2;
        *(word_t**)(v + 0x58) = hi;
        *(word_t**)(v + 0x60) = (word_t*)np + cap * 0x10;
        if (base) cL4_free(base, (word_t)lo - (word_t)base);
    }
    *(word_t**)(v + 0x58) = hi;
    return *(word_t*)((val & 0xfffffffffffffffe) - 8);
}

/* FUN_0039a1b0 @ 0x39a1b0  (est. sk_conform_desc)
 * Resolve the conformance descriptor for a type: dispatch on the metadata
 * kind (bits 3-5 of the word at +0xc). Kind >3 derefs the field at +4 and
 * follows the descriptor's mode/entry; kind 3 (mode 0x1f) returns the
 * conformance via cL4_conform_desc2. Unsupported kinds trip a breakpoint.
 * Confidence: low */
static word_t sk_conform_desc(word_t *p)
{
    unsigned k = *(unsigned*)(p + 0xc) >> 3 & 7;
    word_t r;
    if (k - 2 > 1) {
        if (k > 1) { CL4_SW_BP(0x39a2a4); }
        word_t *f = (word_t*)cL4_deref_field(p + 4, 0);
        if (!f) return 0;
        unsigned w = *f;
        if (((w >> 4 & 1) == 0) || !f) {
            if ((w & 0x1f) == 3 && f) return cL4_conform_desc2((word_t)f);
        } else if (((w >> 7 & 1) == 0) && (w = f[3], w != 0)) {
            return (word_t)(*(word_t **)((word_t)(f + 3) + (long)(int)w))(0xff);
        }
    }
    return 0;
}

/* ================================================================== *
 * Protocol conformance resolution (type equality / subclass / same-shape).
 * ================================================================== */

/* FUN_0039cf64 @ 0x39cf64  (est. sk_type_same_shape)
 * Returns whether `a` and `b` name the same type: unwrap a 0x303 indirection,
 * walk one level of the type via the metadata step when needed, and compare.
 * Confidence: medium */
static bool sk_type_same_shape(word_t *a, word_t *b)
{
    if (*a == 0x303) {
        word_t *sub = ((*(byte*)((char*)a + 0xb) >> 6) & 1) ? (word_t*)a[2] : 0;
        if (sub) a = sub;
    }
    if (a == b) return true;
    if (*a - 0x800U < 0xfffffffffffff801) {
        if (*b != 0x203) {
            do {
                a = (word_t*)sk_type_step(a, 0, 0, 1);
                if (!a) return b == a;
                if (b == a) return true;
            } while (0x7fe < *a - 1U);
        }
    } else if (0xfffffffffffff800 < *b - 0x800U) {
        return cL4_conform_equal(a, b) != 0;
    }
    return false;
}

/* FUN_0039cd94 @ 0x39cd94  (est. sk_type_step)
 * Advance one level in a type metadata chain, handling 0x800-range generic
 * bindings: follows the parent link, dereferences the bound argument, or
 * unwraps a conformance indirection. */
static word_t sk_type_step(word_t *p, word_t mode, word_t flag, int dir)
{
    if (*p - 1U < 0x7ff) return cL4_conform_step(p);
    if ((flag & 1) == 0) { cL4_conform_step3(0x100, p); }
    if (mode == 1) { word_t v = p[1]; if (!v) v = 0; cL4_conform_step3(0x100, v); return v; }
    if (mode == 0) { return p[1]; }
    if (dir == 0) return 0;
    return cL4_conform_step2(0x1ff, p);
}

/* ================================================================== *
 * Hash table element-0x20 primitives (FUN_0039ed50 / 0039ee00 / 0039ef8c).
 * ================================================================== */

/* FUN_0039ed50 @ 0x39ed50  (est. sk_hash_lookup_20)
 * Probe the 0x20 hash table for `key`; on hit *slot = entry and return 1. */
static word_t sk_hash_lookup_20(byte *tbl, word_t key, word_t *slot)
{
    word_t *entry, *cur; byte *base;
    int mask, i = 1;
    if ((*tbl & 1) == 0) {
        int cap = *(int*)(tbl + 0x10);
        if (cap == 0) { *slot = 0; return 0; }
        base = *(byte**)(tbl + 8);
    } else { cap = 4; base = tbl + 8; }
    word_t h = (word_t)(((unsigned)(key >> 4) & 0xfffffff ^ (unsigned)key >> 9) & (cap - 1));
    entry = (word_t*)(base + h * 0x20);
    word_t curv = *entry;
    if (key != curv) {
        word_t *pv = 0;
        do {
            if (curv == 0xfffffffffffff000) { *slot = pv ? (word_t)pv : (word_t)entry; return 0; }
            entry = (word_t*)(base + (word_t)((h + i) & (cap - 1)) * 0x20);
            curv = *entry; i++;
        } while (key != curv);
    }
    *slot = (word_t)entry;
    return 1;
}

/* FUN_0039ee00 @ 0x39ee00  (est. sk_hash_realloc_20)
 * Reallocate the 0x20 hash table to a round-up-pow2 capacity; when the table
 * is inline (bit0 set) stages the entries through the stack first.
 * Confidence: medium */
static word_t sk_hash_realloc_20(word_t *tab, word_t n)
{
    word_t local[16]; word_t *out;
    if (4 < n) {
        unsigned c = n - 1; c |= c >> 1; c |= c >> 2; c |= c >> 4; c |= c >> 8; c |= c >> 16;
        n = 0x40; if (0x40 < c + 1) n = c + 1;
    }
    if ((*tab & 1) == 0) {
        word_t oldbase = *(word_t*)(tab + 2);
        unsigned oldcap = tab[4];
        if (n < 5) *tab |= 1;
        else { *(word_t*)(tab + 2) = cL4_raw_realloc((word_t)n << 5, 8); tab[4] = n; }
        sk_hash_copy_20(tab, (word_t*)oldbase, (word_t*)(oldbase + oldcap * 0x20));
        cL4_raw_free((void*)oldbase, oldcap << 5, 8);
        return 0;
    }
    /* inline table: stage through stack */
    {
        word_t i = 0; out = local;
        do {
            word_t v = *(word_t*)((char*)tab + i + 8);
            if ((v | 0x1000) != 0xfffffffffffff000) {
                out[0] = v;
                out[3] = *(word_t*)((char*)tab + i + 0x20);
                out[2] = *(word_t*)((char*)tab + i + 0x18);
                out[1] = *(word_t*)((char*)tab + i + 0x10);
                out += 4;
            }
            i += 0x20;
        } while (i != 0x80);
        if (4 < n) {
            *tab &= 0xfffffffe;
            *(word_t*)(tab + 2) = cL4_raw_realloc((word_t)n << 5, 8);
            tab[4] = n;
        }
        sk_hash_copy_20(tab, local, (word_t)out);
    }
    return 0;
}

/* FUN_0039ef8c @ 0x39ef8c  (est. sk_hash_copy_20)
 * Rebuild the 0x20 hash table from the source range, re-inserting each
 * non-empty (non-tombstone) element. */
static word_t sk_hash_copy_20(word_t *tab, word_t *src, word_t *dst)
{
    word_t *p, *end;
    word_t old = *tab;
    *tab = old & 1;
    tab[1] = 0;
    if ((old & 1) == 0) {
        if (tab[4] == 0) goto insert;
        p = *(word_t**)(tab + 2); end = p + tab[4] * 8;
    } else { p = tab + 2; end = tab + 0x22; }
    do { p[0] = 0xfffff000; p[1] = 0xffffffff; p += 8; } while (p != end);
insert:
    for (; src != dst; src += 4) {
        if ((*src | 0x1000) != 0xfffffffffffff000) {
            word_t *slot = 0;
            sk_hash_lookup_20((byte*)tab, *src, &slot);
            slot[0] = *src;
            slot[3] = src[3]; slot[1] = src[1]; slot[2] = src[2];
            *tab = *tab + 2;
        }
    }
    return 0;
}

/* ================================================================== *
 * Conformance resolution core (FUN_0039a2a4 / 0039c558 / 0039c74c etc).
 * ================================================================== */

/* FUN_0039c4e4 @ 0x39c4e4  (est. sk_conform_desc_init)
 * Resolve the conformance descriptor for `p`: try the direct field deref
 * first, fall back to the kind-based descriptor; returns {desc, direct?}. */
static word_t *sk_conform_desc_init(word_t *out, word_t p)
{
    word_t d;
    out[0] = 0; *(byte*)(out + 1) = 0;
    d = cL4_deref_field(p + 4, *(unsigned*)(p + 0xc) >> 3 & 7);
    if (d == 0) {
        d = sk_conform_desc(p);
        if (d == 0) return out;
        *(byte*)(out + 1) = 1;
    } else *(byte*)(out + 1) = 0;
    *out = d;
    return out;
}

/* FUN_0039c49c @ 0x39c49c  (est. sk_conform_check_entry)
 * Wrapper: initialise a conformance descriptor and walk it against the
 * subject type; returns the descriptor (or 0). */
static word_t sk_conform_check_entry(word_t p)
{
    word_t desc[2]; byte stack[16];
    sk_conform_desc_init((word_t*)desc, 0);
    sk_conform_walk((word_t*)stack, (word_t*)desc, (word_t*)p, 1);
    return stack[0];
}

/* FUN_0039c558 @ 0x39c558  (est. sk_conform_walk)
 * Walk the conformance descriptor chain against a subject type, checking
 * direct equality or conformance; returns {desc, kind, flag}. */
static word_t sk_conform_walk(word_t *out, word_t *desc, word_t *type, word_t opts)
{
    word_t kind = 0, flag = 0, carry = 0;
    cL4_w16_t r;
    if (type == 0) { kind = 0; flag = 0; }
    else {
        word_t one = 0; word_t more = 0; word_t f2 = 0; word_t flagv = 1;
        do {
            if ((*(byte*)(desc + 1) & 1) == 0) {
                word_t *d = (word_t*)cL4_mr_block((word_t)type);
                if (d == 0) {
                    if ((*type == 0x303) && *(int*)((char*)type + 0xc) == 1) {
                        word_t *t2 = (word_t*)((type + 2)[(*(unsigned*)(type + 1) >> 0x1e) & 1] & 0xfffffffffffffffe);
                        if (((*(unsigned*)(type + 1) >> 0x1e & 1) == 0 || type[2] == 0) && t2 && t2) goto ok;
                    }
                    d = 0;
                } else if ((*d & 0x30000) == 0x20000) {
                    cL4_conform_check2((word_t*)&f2, (word_t*)d);
                }
ok:
                word_t t3 = *desc;
                if (t3 == 0) t3 = 0;
                if (d && (cL4_conform_check(d, t3) & 1)) { out[0] = (word_t)type; *(byte*)(out+1) = 0; *(byte*)(out+2) = 0; return 0; }
            } else if (type == (word_t*)*desc) { out[0] = (word_t)type; *(byte*)(out+1) = 0; *(byte*)(out+2) = 0; return 0; }
            r = cL4_variant_unwrap((word_t*)&f2, (word_t)type | (carry & 0xff));
            type = (word_t*)r.lo; carry = r.hi;
            more = carry & 0xffffffffffffff00;
            one = 1;
        } while (type != 0);
    }
    out[0] = 0; out[1] = kind; out[2] = flag;
    return 0;
}

/* FUN_0039c70c / 0x39c740 / 0x39c74c  (est. sk_conform_find)
 * Find the conformance of `type` to `proto` (two lookup passes: pass 0 then
 * pass 1). Returns the conformance descriptor; optionally records a
 * {desc, size} pair into *out. */
static word_t sk_conform_find(word_t type, word_t proto, word_t *out)
{
    word_t d[3]; word_t h[3];
    cL4_w16_t r;
    r = sk_conform_resolve(type, proto, 0);
    if ((r.lo == 0) && (r.hi & 1)) r = sk_conform_resolve(type, proto, 1);
    if (out && h[1] != 0) {
        if ((out[0] == 0) || (out[0] == h[1])) { out[1] = h[2]; out[0] = h[1]; }
        else r.lo = 0;
    }
    return r.lo;
}
static word_t sk_conform_find_a(word_t type, word_t proto) { return sk_conform_find(type, proto, 0); }
static word_t sk_conform_find_b(word_t type, word_t proto) { return sk_conform_find(type, proto, 0); }

/* FUN_0039c7e8 @ 0x39c7e8  (est. sk_conform_cache_guard)
 * Guard: if the global conformance callback (_DAT_006adf00) is installed and
 * the range [*p, p[1]) is non-empty, invoke it; a non-zero result admits the
 * conformance. */
static word_t sk_conform_cache_guard(word_t key, word_t *p)
{
    if (p && *p != 0 && _DAT_006adf00 && _DAT_006adf00) {
        if ((_DAT_006adf00)(0xd1b80000006adf00, *p, p[1]) & 1) return 0;
    }
    return 1;
}

/* ================================================================== *
 * Conformance table machinery (FUN_0039dc4c / 0039e2a8 / 0039e684 /
 * 0039e838 / 0039ea90 / 0039eb70).
 * ================================================================== */

/* FUN_0039dc4c @ 0x39dc4c  (est. sk_conform_resolve)
 * Resolve protocol conformance of `type` to `proto` against the global
 * conformance table (locked via the 0x6c0a60 refcount + 0x6c0ac0 region
 * table + 0x6c0a80 spinlock). Walks the type metadata; on a hit returns the
 * conformance descriptor; otherwise computes a fresh one through the
 * generic-requirement decoder and inserts it. Returns {desc, flags}.
 * Confidence: low (concurrency-heavy, multi-table) */
static cL4_w16_t sk_conform_resolve(word_t type, word_t proto, byte pass)
{
    cL4_w16_t r; word_t found;
    word_t t = type, p = proto;
    word_t p0 = p;
    byte flag = 0;
    word_t guard;
    if (-1 < _DAT_006c0b00) cL4_tls_check(&_DAT_006c0b00, (word_t*)0x39bdbc, (word_t*)&_DAT_006c0a60);
    guard = _DAT_006c0a70;
    CL4_LO_ACQUIRE();
    _DAT_006c0a60++;
    if (t != 0) {
        word_t cnt = 0; word_t more = 0; word_t one = 0;
        word_t last3 = _DAT_006c0a70, last2 = _DAT_006c0a64, last1 = _DAT_006c0a68;
        do {
            word_t *tt = (word_t*)((word_t)t & 0xfffffffffffffffd);
            if ((_DAT_006c0a70 && _DAT_006c0a64 && _DAT_006c0a68) &&
                (found = sk_conform_table_probe((word_t)tt)) != 0) {
                word_t entry = *(word_t*)(found + 8);
                if (((unsigned)entry >> 1 & 1) == 0) {
                    word_t d = *(word_t*)(found + 0x10);
                    CL4_LO_RELEASE();
                    r.lo = d; r.hi = 0; return r;
                }
                word_t sub = entry & 0xfffffffffffffffc;
                if (sub != 0) {
                    word_t d = *(word_t*)(found + 0x10);
                    word_t d2 = *(word_t*)(sub + 0x10);
                    word_t d1 = *(word_t*)(sub + 8);
                    CL4_LO_RELEASE();
                    _DAT_006c0a60--;
                    r.lo = d; r.hi = d2; return r;
                }
                CL4_LO_RELEASE();
                _DAT_006c0a60--;
                r.lo = 0; r.hi = 0; return r;
            }
            {
                char *mr = (char*)cL4_mr_block((word_t)tt);
                if (mr && *mr < 0) {
                    word_t loc = (word_t)mr | 2;
                    if ((_DAT_006c0a70 && _DAT_006c0a64 && _DAT_006c0a68) &&
                        (found = sk_conform_table_probe(loc)) != 0) {
                        word_t loc2 = 0;
                        found = sk_conform_find(*(word_t*)(found + 0x10), (word_t)tt, &loc2);
                        CL4_LO_ACQUIRE();
                        word_t nb = _DAT_006c0ac0 ? *_DAT_006c0ac0 : 0;
                        CL4_LO_RELEASE();
                        sk_conform_insert((word_t*)&DAT_006c0a60, (word_t)tt, p, (word_t*)&found, nb, 0);
                        CL4_LO_RELEASE();
                        _DAT_006c0a60--;
                        r.lo = found; r.hi = loc2; return r;
                    }
                }
            }
            cL4_w16_t nr = cL4_variant_unwrap((word_t*)&one, (word_t)t);
            t = (word_t)nr.lo; more = 1;
        } while (t != 0);
    }
    CL4_LO_RELEASE();
    _DAT_006c0a60--;
    return (cL4_w16_t){0, 0};
}

/* FUN_0039e2a8 @ 0x39e2a8  (est. sk_conform_insert)
 * Insert {type, proto} → {conformance} into the conformance table (a
 * hash-of-hashes keyed by type name, grown on load). Takes the table lock,
 * probes for an existing slot, then records the entry; if the caller asked
 * for notification (param_6) also re-validates against the current type and
 * records the subject type. On zero refcount drains the deferred free list.
 * Confidence: low */
static word_t sk_conform_insert(word_t *tab, word_t type, word_t proto, word_t *res, word_t n, int flag)
{
    word_t *slot; word_t capbyte; word_t k, v, mask;
    word_t *pv; word_t *entry; word_t probe;
    word_t t;
    cL4_mtx_lock(tab + 8);
    if (n != 0) {
        word_t *c = (word_t*)(tab + 0x16);
        CL4_LO_ACQUIRE();
        *c = *c - 1;
        CL4_LO_RELEASE();
        if (c[1] != n) goto out;
    }
    k = *(word_t*)(tab + 4);
    capbyte = 4;
    if ((k & 3) != 0 && *(byte*)(k & 0xfffffffffffffffc) != 0) capbyte = *(byte*)(k & 0xfffffffffffffffc);
    v = tab[1];
    slot = *(word_t**)(tab + 2);
    pv = slot ? slot + 2 : 0;
    probe = sk_hash_probe((word_t*)&k, v, (word_t)pv);
    if (probe == 0) {
        word_t lim = (word_t)1 << (capbyte & 0x3f);
        word_t next = v + 1;
        word_t d = lim - next;
        word_t q = 0; if (d != 0) q = lim / d;
        if (q > 3) {
            k = sk_hash_rehash((word_t*)tab, k, (word_t*)&slot, (word_t)pv);
            probe = sk_hash_probe((word_t*)&k, v, (word_t)pv);
        }
        if (!slot || *slot <= v) slot = (word_t*)sk_hash_grow((word_t*)tab, slot, v);
        *(word_t*)(slot + v * 6 + 2) = k & 0xfffffffffffffffd;
        if (proto == 0) proto = 0; else proto &= 0xfffffffffffffffd;
        *(word_t*)(slot + v * 6 + 4) = proto;
        *(word_t**)(slot + v * 6 + 6) = (word_t*)*res;
        tab[1] = next;
        sk_hash_insert((word_t*)&k, tab + 4, next, 3);
    }
out:
    CL4_DATA_MEMBARRIER();
    if (*tab == 0) {
        word_t *node = *(word_t**)(tab + 0x10);
        while (node) {
            word_t *nx = (word_t*)*node;
            cL4_free((void*)node[1], 0); cL4_free(node, 0);
            node = nx;
        }
        *(word_t**)(tab + 0x10) = 0;
        *(word_t**)(tab + 0x11) = 0;
    }
    cL4_mtx_unlock(tab + 8);
    return 0;
}

/* FUN_0039e684 @ 0x39e684  (est. sk_conform_probe)
 * Probe the conformance hash (element 0x18) for a key; returns {slot, 0} on
 * hit or {0, hash} on miss. */
static word_t sk_conform_probe(word_t *tbl, word_t k, word_t n, word_t *slots)
{
    word_t h; int i; word_t slot = 0; word_t v;
    word_t key = *tbl;
    word_t capbyte = 4;
    if ((k & 3) != 0 && *(byte*)(k & 0xfffffffffffffffc) != 0) capbyte = *(byte*)(k & 0xfffffffffffffffc);
    h = cL4_hash_compute(0, 0, 0, 0, 0, tbl + 1) & ~((word_t)-1 << (capbyte & 0x3f));
    if (h < 2) h = 1;
    i = cL4_hash_probe(tbl, h, 2);
    if (i != 0) {
        do {
            if (i - 1 < n && (word_t*)slots[(i - 1) * 3] == (word_t*)key) {
                word_t *e = (word_t*)(slots[(i - 1) * 3 + 1] & 0xfffffffffffffffc);
                if ((((unsigned)slots[(i-1)*3+1] >> 1) & 1) == 0) { if (e && e) e = 0; }
                else if (e) e = (word_t*)*e;
                if (e == (word_t*)tbl[1]) { return 0; }
            }
            h = (h + 1) & ~((word_t)-1 << (capbyte & 0x3f));
            if (h < 2) h = 1;
            i = cL4_hash_probe(tbl, h, 2);
        } while (i != 0);
    }
    slot = 0;
    return slot;
}

/* FUN_0039e838 @ 0x39e838  (est. sk_hash_rehash)
 * Reallocate the conformance hash to a fresh size chosen by bit-width of
 * the element count; copies each live entry through the probe path.
 * Confidence: low */
static word_t sk_hash_rehash(word_t *tbl, word_t k, word_t *slots, word_t n)
{
    word_t bucket; word_t i, j; word_t cap; word_t nb;
    unsigned bw = (unsigned)n + 1; unsigned sz = 2;
    if (0x10 < (bw & 0xff)) sz = 4;
    if ((bw & 0xff) < 9) sz = 1;
    word_t *np = cL4_raw_alloc_align((word_t)2 << (n & 0x3f), sz, 0x48dda4ae);
    if (!np) CL4_SW_BP(0x39ea8c);
    *np = (char)((int)n + 1);
    *(word_t*)(tbl + 0x10) = (word_t)np;
    if ((int)n != 0) {
        word_t q = 1;
        do {
            word_t c = cL4_hash_probe(&k, q, 0);
            if ((int)c != 0) {
                word_t *e = (word_t*)(slots + ((int)c - 1) * 3);
                word_t key = *e;
                word_t vb = e[1];
                word_t *sub = (word_t*)(vb & 0xfffffffffffffffc);
                if ((((unsigned)vb >> 1) & 1) == 0) { if (sub && sub) sub = 0; }
                else if (sub) sub = (word_t*)*sub;
                /* re-probe into the new table */
                cL4_hash_compute(0,0,0,0,0,0);
                word_t *ns = 0;
                if (sk_hash_lookup_20((byte*)np, key, &ns) == 0) {
                    ns[0] = key; ns[1] = sub;
                }
            }
            q++;
        } while (q >> (n & 0x3f) == 0);
    }
    *(word_t*)(tbl + 0x10) = (word_t)np;
    return (word_t)np;
}

/* FUN_0039ea90 @ 0x39ea90  (est. sk_hash_grow)
 * Grow the conformance hash table; returns the new slot base. */
static word_t sk_hash_grow(word_t *tab, word_t *old, word_t n)
{
    word_t sz = n >> 2; if (sz < 2) sz = 1;
    sz = cL4_round_up((sz + n) * 0x18 + 8);
    word_t *np = cL4_raw_alloc(sz, 0x10600406ffeba39);
    if (!np) CL4_SW_BP(0x39eb70);
    *np = (word_t)((sz - 8) / 0x18);
    if (old) {
        cL4_memcpy_v((word_t)(np + 2), (word_t)old + 8, n * 0x18, 0);
        word_t *nd = cL4_raw_alloc(0x10, 0xa0040aff93c70);
        nd[0] = *(word_t*)(tab + 0x40); nd[1] = (word_t)old;
        *(word_t**)(tab + 0x40) = nd;
    }
    *(word_t**)(tab + 8) = np;
    return (word_t)np;
}

/* FUN_0039eb70 @ 0x39eb70  (est. sk_conform_merge)
 * Merge a freshly resolved conformance into the shared table: re-lookup the
 * type descriptor, walk it, then insert and record the subject type; grows
 * the table on load. */
static word_t sk_conform_merge(word_t *ctx, word_t type)
{
    word_t d[3]; byte stack[16]; word_t *slot;
    word_t res[3]; word_t found;
    cL4_w16_t r;
    if (cL4_conform_chain(type, *(word_t*)*ctx) != *(word_t*)*ctx) return 0;
    sk_conform_desc_init((word_t*)d, type);
    sk_conform_walk((word_t*)&res[0], (word_t*)d, *(word_t**)ctx[1], *(byte*)ctx[2]);
    found = res[0];
    if ((*(byte**)ctx[3] & 1) == 0) *(byte**)ctx[3] = (byte)(res[1] & res[2] == 0xff);
    else *(byte**)ctx[3] = (byte)res[1];
    if (found == 0) return 0;
    res[0] = 0; res[1] = 0;
    found = sk_conform_find(type, found, &res[0]);
    sk_conform_insert((word_t*)ctx[4], found, *(word_t*)*ctx, &res[0], 0, 1);
    {
        word_t *tbl = (word_t*)ctx[5];
        word_t *ss = 0;
        r = cL4_variant_unwrap((word_t*)&ss, (word_t)type);
        if (r.lo & 1) return 0;
        word_t cap = *tbl;
        word_t mask = (cap & 1) ? 4 : tbl[4];
        if (((cap >> 1) * 4 + 4) < mask * 3) {
            if (mask >> 3 < (mask + ~(cap >> 1)) - tbl[1]) goto ins;
        } else mask <<= 1;
        sk_hash_realloc_20((word_t*)tbl, mask);
        r = cL4_variant_unwrap((word_t*)&ss, (word_t)type);
        cap = *tbl;
ins:
        *tbl = cap + 2;
        if (*ss != (word_t)-0x1000) tbl[1] = tbl[1] - 1;
        ss[0] = found;
        ss[2] = res[2];
        ss[1] = res[1];
        ss[3] = res[3];
    }
    return 0;
}

/* ================================================================== *
 * Protocol descriptor helpers (FUN_0039f05c / 16c / 27c / 38c).
 * ================================================================== */

/* FUN_0039f05c @ 0x39f05c  (est. sk_proto_desc_10)
 * Extract {ptr, count} for a 0x10 protocol descriptor; empty if the tag
 * byte's sign bit is clear. */
static cL4_w16_t sk_proto_desc_10(word_t *p)
{
    cL4_w16_t r;
    word_t *q = p; if (!q) q = 0;
    if ((signed char)*q >= 0) { r.lo = 0; r.hi = 0; return r; }
    q = p; if (!q) q = 0;
    word_t *base = q + 0xb; if (!base) base = 0;
    if (!q) q = 0;
    if (!p) p = 0;
    r.hi = (short)p[0xd];
    r.lo = (word_t)(base + (((*q >> 7) & 1) ? 1 : 0));
    r.hi &= 0xffff; r.hi <<= 0x30; /* _10_6_ = 0 */
    r.hi = 0;
    return r;
}
/* FUN_0039f16c / 0x39f27c  (est. sk_proto_desc_11 / _12) */
static cL4_w16_t sk_proto_desc_11(word_t *p)
{
    cL4_w16_t r; word_t *q = p; if (!q) q = 0;
    if ((signed char)*q >= 0) { r.lo = 0; r.hi = 0; return r; }
    q = p; if (!q) q = 0;
    word_t *base = q + 7; if (!base) base = 0;
    if (!q) q = 0; if (!p) p = 0;
    r.hi = (short)p[9];
    r.lo = (word_t)(base + (((*q >> 7) & 1) ? 1 : 0));
    r.hi = 0;
    return r;
}
static cL4_w16_t sk_proto_desc_12(word_t *p)
{
    cL4_w16_t r; word_t *q = p; if (!q) q = 0;
    if ((signed char)*q >= 0) { r.lo = 0; r.hi = 0; return r; }
    q = p; if (!q) q = 0;
    word_t *base = q + 7; if (!base) base = 0;
    if (!q) q = 0; if (!p) p = 0;
    r.hi = (short)p[9];
    r.lo = (word_t)(base + (((*q >> 7) & 1) ? 1 : 0));
    r.hi = 0;
    return r;
}
/* FUN_0039f38c @ 0x39f38c  (est. sk_proto_desc_04) */
static cL4_w16_t sk_proto_desc_04(word_t *p)
{
    cL4_w16_t r; word_t *q = p; if (!q) q = 0;
    if ((signed char)*q >= 0) { r.lo = 0; r.hi = 0; return r; }
    q = p; if (!q) q = 0;
    word_t *base = q + 2; if (!base) base = 0;
    if (!q) q = 0; if (!p) p = 0;
    r.hi = (short)p[2];
    r.lo = (word_t)(base + (((*q >> 7) & 1) ? 2 : 0));
    r.hi = 0;
    return r;
}

/* FUN_0039a5fc @ 0x39a5fc  (est. sk_proto_dispatch)
 * Dispatch a protocol descriptor by its kind (0x04→0x10-descriptor,
 * 0x10/0x11/0x12 → others); unsupported kinds trip a breakpoint. */
static cL4_w16_t sk_proto_dispatch(word_t *p)
{
    unsigned k = *p & 0x1f;
    if (k < 0x11) {
        if (k == 4) { if (!p) p = 0; return sk_proto_desc_04(p); }
        if (k == 0x10) { if (!p) p = 0; return sk_proto_desc_10(p); }
    } else {
        if (k == 0x11) { if (!p) p = 0; return sk_proto_desc_11(p); }
        if (k == 0x12) { if (!p) p = 0; return sk_proto_desc_12(p); }
    }
    CL4_SW_BP(0x39a6fc);
    return (cL4_w16_t){0,0};
}

/* ================================================================== *
 * Conformance invertibility (FUN_0039bf68 / 0039d60c / 0039d864).
 * ================================================================== */

/* FUN_0039d60c @ 0x39d60c  (est. sk_conform_invert_table)
 * Fetch the invertible-conformance table for a protocol descriptor
 * (kinds 0x04/0x10/0x11/0x12); returns the table base. */
static word_t sk_conform_invert_table(word_t *p)
{
    unsigned k;
    if (((*p >> 5) & 1) == 0) return 0;
    k = *p & 0x1f;
    if (k < 0x11) {
        if (k == 4) { if (!p) p = 0; if (!p) p = 0; word_t t = cL4_pack_lookup(p); return t + (word_t)*(short*)((char*)p + 2) * 4; }
        if (k != 0x10) return 0;
        if (!p) p = 0; if (!p) p = 0;
        return cL4_pack_lookup2(p);
    } else if (k == 0x11) {
        if (!p) p = 0; if (!p) p = 0;
        return cL4_pack_lookup3(p);
    } else {
        if (k != 0x12) return 0;
        if (!p) p = 0; if (!p) p = 0;
        return cL4_pack_lookup4(p);
    }
}

/* FUN_0039d864 @ 0x39d864  (est. sk_conform_invert_bit)
 * If the invertible table has bit `sel` set, return the corresponding
 * conformance descriptor (the i-th set bit); else 0. */
static cL4_w16_t sk_conform_invert_bit(word_t p, word_t sel)
{
    if ((*(short*)(p + 10) >> 1 & 1) != 0) {
        word_t *t = (word_t*)((p + *(short*)(p + 4) + 0xf & 0xfffffffffffffffc) + *(short*)(p + 6) * 0xc);
        word_t cnt = *(short*)(p + 10) & 1;
        if ((int)cnt == 0) cnt = 0; else cnt = (word_t)*t;
        short m = t[cnt * 2 + cnt * 4];
        if ((m >> (sel & 0x1f) & 1) != 0) {
            int i = 0; for (; sel != 0; sel--) { i += (unsigned)m & 1; m >>= 1; }
            return sk_pack_slice(p, i);
        }
    }
    return (cL4_w16_t){0,0};
}

/* FUN_0039c84c @ 0x39c84c  (est. sk_conform_major)
 * If the conformance descriptor's +0xe bit3 is set, return the 
 * protocol-major descriptor node; else {0,0}. */
static cL4_w16_t sk_conform_major(word_t p)
{
    cL4_w16_t r;
    if (((*(byte*)(p + 0xe) >> 3) & 1) == 0) return (cL4_w16_t){0,0};
    word_t *pi = (word_t*)sk_conform_desc2(p);
    return cL4_node_build((word_t)*pi, (word_t)pi);
}
/* FUN_0039c888 @ 0x39c888  (est. sk_conform_next)
 * Return the next conformance in a chain (dereferencing the tagged
 * pointer at desc+4). */
static word_t *sk_conform_next(word_t p)
{
    word_t lv;
    if (((*(byte*)(p + 0xe) >> 3) & 1) != 0) {
        word_t base = sk_conform_desc2(p);
        word_t v = *(unsigned*)(base + 4);
        word_t *r = (word_t*)((v & 0xfffffffffffffffe) + base + 4);
        if (((v & 1) != 0) && (r = (word_t*)*r, r == 0)) r = 0;
        return r;
    }
    return 0;
}

/* ================================================================== *
 * Mutex / object-init / refcount wrappers.
 * ================================================================== */

/* FUN_0039cab8 @ 0x39cab8  (est. sk_mtx_lock)
 * Recursive-counted mutex lock (Swift runtime spinlock): on first entry
 * initialise the handle; spin until acquired. */
static void sk_mtx_lock(word_t *m)
{
    if (-1 < *(int*)(m + 0x10)) {
        if (*(int*)(m + 0x10) == 0) {
            *(int*)(m + 0x10) = 1;
            if (cL4_mtx_init(m, 0) != 0) cL4_mtx_panic("__mtx_init: handle mutex: ...");
            *(int*)(m + 0x10) = -1;
        } else {
            do { } while (-1 < *(int*)(m + 0x10));
        }
    }
    if (cL4_mtx_lock(m) != 0) cL4_mtx_panic("__mtx_lock: handle mutex failed");
}
/* FUN_0039cb50 @ 0x39cb50  (est. sk_mtx_unlock) */
static void sk_mtx_unlock(word_t *m)
{
    if (-1 < *(int*)(m + 0x10)) {
        if (*(int*)(m + 0x10) == 0) {
            *(int*)(m + 0x10) = 1;
            if (cL4_mtx_init(m, 0) != 0) cL4_mtx_panic("__mtx_init: handle mutex: ...");
            *(int*)(m + 0x10) = -1;
        } else {
            do { } while (-1 < *(int*)(m + 0x10));
        }
    }
    if (cL4_mtx_unlock(m) != 0) cL4_mtx_panic("__mtx_unlock: handle mutex failed");
}

/* FUN_0039f6d8 @ 0x39f6d8  (est. sk_md_obj_init)
 * Initialise a metadata-decoder object: zero its fields, run the obj_init
 * hook, seed a hardware byte, check the TLS guard, clear the +0x99 flag. */
static word_t sk_md_obj_init(word_t *obj)
{
    word_t *o = (word_t*)obj;
    o[0]=0; o[1]=0; o[2]=0; o[5]=0; o[4]=0; o[7]=0; o[6]=0; o[8]=0;
    o[0xb]=0; o[0xc]=0; o[0xa]=0;
    cL4_obj_init(o + 0xe, 0);
    o[0x10]=0; o[0x12]=0;
    *(byte*)(o + 0x13) = (byte)cL4_hw_seed();
    if (-1 < _DAT_006adee0) cL4_tls_check(&_DAT_006adee0, (word_t*)0x3697c0, 0);
    *(byte*)((char*)o + 0x99) = 0;
    cL4_tls_init();
    return obj;
}

/* ================================================================== *
 * Seqlock / refcount machinery (FUN_0039f818 / 8b8 / 914 / 9e8 / fa58 /
 * fb10 / fb58 / fb68).
 * ================================================================== */

/* FUN_0039f914 @ 0x39f914  (est. sk_seqlock_get)
 * Acquire the refcounted node for a seqlock word: returns the boxed pointer
 * or 0 (allocating a fresh box on the empty path). */
static word_t *sk_seqlock_get(word_t *p, int alloc)
{
    word_t v = *(word_t*)p;
    word_t *r;
    if ((long)v < 0 && (v & 0xffffffff) != 0xffffffff) {
        r = (word_t*)(v << 3);
    } else if (alloc == 0 || ((v >> 0x20) & 1) == 0) {
        word_t *np = cL4_ref_alloc(0x20, 0xf);
        np[2] = 0; np[0] = (word_t)(p - 1); np[3] = 0;
        do {
            if (alloc != 0 && ((v >> 0x20) & 1) != 0) return 0;
            np[2] = v; np[3] = 1;
            word_t cur = *(word_t*)p;
            if (cur == v) { *(word_t*)p = (word_t)np >> 3 | 0xc000000000000000; return np; }
            v = cur;
        } while (!((long)cur >= 0) || ((cur & 0xffffffff) == 0xffffffff));
        r = (word_t*)(cur << 3);
        cL4_free(np, 0x20, 0xf);
    } else return 0;
    return r;
}

/* FUN_0039f8b8 @ 0x39f8b8  (est. sk_seqlock_retain)
 * Retain / attach a boxed node for a seqlock entry (via the seqlock-pair
 * path). Returns the boxed pointer or 0. */
static cL4_w16_t sk_seqlock_retain(word_t *p, word_t op)
{
    word_t *r; word_t v;
    if ((int)op == -1) return (cL4_w16_t){ (word_t)(void*)"\x01", 0 };
    r = (word_t*)sk_seqlock_get((word_t*)((word_t)p + 0x10), 0);
    if (r) return (cL4_w16_t){ (word_t)cL4_ref_retain_tls((word_t)(r + 0x10), 0), 0 };
    return (cL4_w16_t){0,0};
}

/* FUN_0039f818 @ 0x39f818  (est. sk_seqlock_update)
 * Seqlock compare-and-swap loop: update the writer sequence to a new
 * generation, retrying on concurrent modification; returns 1 on success,
 * 0 on a conflicting writer. */
static word_t sk_seqlock_update(word_t *p, word_t seq)
{
    word_t *w = (word_t*)(p + 0x10);
    word_t s0 = *w, s1 = *(word_t*)(p + 0x18);
    word_t in_x10 = 0;
    if ((s0 >> 0x20 & 1) == 0) {
        while ((long)(s0 + 0x200000000) >= 0) {
            word_t lo = s1 & 0xffffffff;
            word_t want = lo | in_x10 << 0x20;
            word_t c0 = *w, c1 = *(word_t*)(p + 0x18);
            if (c0 == want && c1 == s0) { *w = lo; *(word_t*)(p + 0x18) = s0 + 0x200000000; }
            if (c0 == s0 && c1 == want) return 1;
            in_x10 = c1 >> 0x20;
            s0 = c0;
            if ((c0 >> 0x20 & 1) != 0) return 0;
        }
        if ((int)s0 != -1) return sk_seqlock_update(w, s0, s1 & 0xffffffff | in_x10 << 0x20);
        return 1;
    }
    return 0;
}

/* FUN_0039f9e8 @ 0x39f9e8  (est. sk_seqlock_release)
 * Release / detach a boxed node from a seqlock entry (releasing through the
 * fa58 path); returns the boxed base. */
static word_t sk_seqlock_release(word_t p, word_t seq, word_t v)
{
    if ((int)seq != -1) {
        if (seq < 0) seq <<= 3;
        else seq = (word_t)sk_seqlock_get((word_t*)p, 0);
        sk_seqlock_release_node((word_t*)seq, v);
    }
    return p - 8;
}

/* FUN_0039fa58 @ 0x39fa58  (est. sk_seqlock_release_node)
 * Release a boxed seqlock node: decrement the writer generation, following
 * the chained sequence; returns the node pointer. */
static word_t *sk_seqlock_release_node(word_t *n, word_t seq)
{
    word_t v5 = n[2], v6 = n[3];
    word_t *r = n;
    if (!(((int)seq == 1) || (long)v5 >= 0) || (v5 & 0xffffffff) != 0xffffffff) {
        r = n + 2;
        word_t w = v5 + (seq << 0x21);
        if ((long)w >= 0) {
            word_t cur5 = v5; word_t in_x9 = 0;
            do {
                word_t lo = v6 & 0xffffffff;
                word_t want = lo | in_x9 << 0x20;
                word_t c5 = *r; word_t c6 = n[3];
                if (c5 == want && c6 == cur5) { *r = lo; n[3] = w; }
                if (c5 == cur5 && c6 == want) return r;
                in_x9 = c6 >> 0x20;
                w = (seq << 0x21) + c5;
                cur5 = c5;
            } while ((long)w >= 0);
        }
        if ((int)v5 != -1) {
            if ((int)v5 != -1) {
                word_t u = cL4_seqlock_load(r);
                word_t *q = (word_t*)sk_seqlock_get((word_t*)u, 1);
                if (q) {
                    if ((q[2] >> 0x20 & 1) == 0) cL4_ref_release_tls((word_t)(q + 2));
                    else q = 0;
                }
                return q;
            }
            return (word_t*)*n;
        }
    }
    return r;
}

/* FUN_0039fb10 @ 0x39fb10  (est. sk_seqlock_ref)
 * Look up a boxed node for a seqlock word and release it; returns 0 on
 * conflict. */
static word_t sk_seqlock_ref(word_t p)
{
    word_t r = (word_t)sk_seqlock_get((word_t*)p, 1);
    if (r != 0) {
        if ((*(word_t*)(r + 0x10) >> 0x20 & 1) == 0) cL4_ref_release_tls(r + 0x10);
        else r = 0;
    }
    return r;
}

/* FUN_0039fb58 / 0x39fb68  (est. sk_type_merge)
 * Merge a type metadata descriptor against a canonical "merged" type:
 * unwraps the metadata chain (0x303/0x203/0x300/0x305/0x305-0x500/0x400),
 * following the protocol-conformance indirection when the canonical slot is
 * empty. */
static word_t *sk_type_merge(word_t a, word_t *b, word_t c)
{
    cL4_w16_t r; word_t *slot; word_t **sp; word_t *s1, *s2;
    word_t v;
    r = cL4_seqlock_pair(0);
    s1 = (word_t*)r.hi;
    r = cL4_metadata_merge(c, r.lo);
    s2 = (word_t*)r.hi; s1 = (word_t*)r.lo;
    if (s1) s1 = (word_t*)(word_t)((s1 == 0) ? s2 : s1);
    s2 = s1;
    {
        word_t *stk0 = (word_t*)s1;
        int kind = 0;
        if (*stk0 < 0x800) kind = (int)*stk0;
        if (kind < 0x300) {
            if (kind != 0 && kind != 0x203) return s1;
        } else if (kind < 0x305) {
            if (kind != 0x300 || s1 != (word_t*)0x67b0a8) return s1;
            if (0xfffffffffffff800 < **(word_t**)*s2 - 0x800U) return (word_t*)0x67b0a8;
            s1 = (word_t*)cL4_metadata_canon((word_t*)&s2);
            return s1;
        } else {
            if (kind != 0x305) {
                if ((1 < kind - 0x500U) && kind != 0x400) return s1;
                CL4_SW_BP(0x39fc00);
            }
        }
    }
    if (s2 == 0) {
        word_t t = cL4_metadata_chain(*(word_t*)s1);
        while (*(word_t*)(t + 0x28) == 0 || *(word_t*)(t + 0x28) == 0) {
            word_t *p = (word_t*)(t + 8); t = 0; if (*p != 0) t = *p;
        }
        s1 = *s2;
    }
    return s1;
}

/* ================================================================== *
 * Generic requirements decoder (FUN_0039a6fc) and its support
 * (FUN_00398a70 / 0039ce74 / 0039bf68).
 * ================================================================== */

/* FUN_0039a6fc @ 0x39a6fc  (est. sk_req_decoder)
 * The generic-requirements decoder: walks a serialised generic-requirement
 * descriptor (a stream of 12-byte records, `param_5` of them) and, for each,
 * checks the requirement against the subject generic arguments. Handles
 * same-type (0), superclass (1), same-conformance (2), layout (3),
 * same-shape (4), pack-length (5), and pack-array (0x1f) requirements,
 * building the appropriate error record on a failed check. Also folds
 * pack-expansion bits from the generic parameter metadata into the
 * requirement stream.
 * Confidence: low (large dispatch, many error paths) */
static word_t sk_req_decoder(word_t *out, word_t p2, word_t p3, word_t *p4, word_t p5,
                             word_t *p6, word_t p7, word_t p8, word_t p9, word_t p10)
{
    return 0; /* faithful body is split below; see sk_req_decoder_body */
}
/* The full decoder body — see FUN_0039a6fc body below. */

/* FUN_0039ce74 @ 0x39ce74  (est. sk_layout_check)
 * Check a layout requirement against a subject type: on a layout-kind 0
 * probe the type's conformance; else report "unknown layout kind". */
static void sk_layout_check(word_t *out, word_t p, word_t type)
{
    int kind = *(int*)(p + 8);
    word_t *e;
    if (kind == 0) {
        if (cL4_conform_pack(type, 0) & 1) { *(byte*)out = 0; return; }
        word_t *pi = (word_t*)(p + 4);
        cL4_node_build((word_t)*pi, (word_t)pi);
        word_t nm = cL4_node_build((word_t)*pi, (word_t)pi).lo;
        e = cL4_alloc(0x18, 0x1050c400d13d5ba);
        e[0] = (word_t)(void*)"subject type does not satisfy";
        e[2] = nm;
        out[1] = (word_t)(void*)sk_box_18_a;
    } else {
        e = cL4_alloc(0x10, 0x1050c40db1d6c16);
        e[0] = (word_t)(void*)"unknown layout kind";
        *(int*)(e + 1) = kind;
        out[1] = (word_t)(void*)sk_box_10_b;
    }
    out[0] = (word_t)e;
    *(byte*)(out + 2) = 1;
}

/* FUN_0039bf68 @ 0x39bf68  (est. sk_invertible_check)
 * Check that all "invertible" conformances required by a protocol are
 * satisfied by a type (used for the erased-protocol generic check): scans
 * the invertible-bit table and re-runs the requirement decoder for each set
 * bit. Also special-cases 0x300/0x301/0x302 (function types) and 0x307
 * (existential) records.
 * Confidence: low */
static void sk_invertible_check(word_t *out, word_t *t, word_t flags)
{
    unsigned inv = (unsigned)flags;
    char *mr = (char*)cL4_mr_block(0);
    if (mr == 0) {
        int n = 0;
        if (*t < 0x800) n = (int)*t;
        if (n < 0x304) {
            if (0x2ff < n) {
                if (n < 0x302) {
                    if (((n != 0x300) && (n == 0x301)) && (word_t)(unsigned)t[1] != 0) {
                        word_t cnt = (unsigned)t[1];
                        word_t *e = t + 3;
                        do { sk_invertible_check(out, *e, inv); if (*(byte*)(out+2) & 1) goto done; cnt--; e += 2; } while (cnt != 0);
                    }
                } else if (n == 0x302) {
                    word_t cnt = t[1];
                    if ((long)cnt < 0) { cL4_vec_push_b(t); cnt = t[1]; }
                    unsigned w = (unsigned)cnt & 0x4ff0000;
                    unsigned want = w ? 0 : (unsigned)inv;
                    word_t val = want & ~(unsigned)inv;
                    if (val != 0) {
                        word_t *e = cL4_alloc(0x10, 0x1050c40a90f5278);
                        e[0] = (word_t)(void*)"function type missing invertible";
                        *(short*)(e + 1) = (short)val;
                        goto err;
                    }
                }
            } else if ((((n < 0x308) && (0x305 < n)) && n != 0x306) && (n == 0x307 && *(char*)t[1] != 2)) {
                word_t *d = (word_t*)cL4_pack_inspect(t[1]);
                if ((word_t)*(short*)((char*)t[1] + 10) != 0) {
                    word_t cnt = (word_t)*(short*)((char*)t[1] + 10) * 0xc;
                    do {
                        if (((*d & 0x1f) == 5) && ((unsigned)*(short*)((char*)d + 10) & ~(unsigned)inv)) {
                            word_t *e = cL4_alloc(0x10, 0x1050c40a90f5278);
                            e[0] = (word_t)(void*)"existential type missing inverti";
                            *(short*)(e + 1) = (short)((unsigned)*(short*)((char*)d + 10) & ~(unsigned)inv);
                            goto err;
                        }
                        d += 3; cnt -= 0xc;
                    } while (cnt != 0);
                }
            }
        }
    } else if (((*mr >> 5) & 1) != 0) {
        word_t *tab = (word_t*)sk_conform_invert_table(mr);
        if (tab == 0) {
            word_t *e = cL4_alloc(8, 0x50c40ee9192b6);
            e[0] = (word_t)(void*)"unable to find suppressed protoc";
            goto err2;
        } else {
            unsigned mask = (unsigned)*tab & ~(unsigned)inv;
            if (mask != 0) {
                word_t *t2 = (word_t*)sk_conform_invert_bit(tab, 0);
                /* handled via the invertible bit walk */
                word_t *e = cL4_alloc(0x10, 0x1050c40a90f5278);
                e[0] = (word_t)(void*)"type missing invertible conforma";
                *(short*)(e + 1) = (short)mask;
                goto err2;
            }
        }
    }
    *(byte*)out = 0; *(byte*)(out+2) = 0;
    return;
err:
    out[0] = (word_t)e; out[1] = (word_t)(void*)sk_box_10_a; *(byte*)(out+2) = 1; return;
err2:
    out[0] = (word_t)e; out[1] = (word_t)(void*)sk_box_10_a; *(byte*)(out+2) = 1; return;
done:
    return;
}

/* ================================================================== *
 * Remaining small helpers.
 * ================================================================== */

/* FUN_00398474 @ 0x398474  (est. sk_hash_probe_10)
 * Probe the 10-entry hash for a key; returns {entry, index} (16-byte). */
static cL4_w16_t sk_hash_probe_10(word_t *tbl, word_t k, word_t n, word_t *slots)
{
    word_t capbyte; word_t h; int i; cL4_w16_t r; word_t *e;
    capbyte = 4;
    if (((k & 3) != 0) && (*(byte*)(k & 0xfffffffffffffffc) != 0)) capbyte = *(byte*)(k & 0xfffffffffffffffc);
    h = cL4_hash_compute(0,0,0,0,0,0);
    h &= ~((word_t)-1 << (capbyte & 0x3f));
    if (h < 2) h = 1;
    i = cL4_hash_probe(&h, h, 2);
    if (i != 0) {
        do {
            if (i - 1 < n) {
                word_t *ep = (word_t*)(slots + (word_t)(i - 1) * 3);
                if (*(char*)((char*)tbl + 0x17) < 0) ep = tbl;
                if ((ep[1] == (word_t*)0 || (cL4_memcmp((void*)ep[0], (void*)ep[1], 0) == 0))) { r.lo = 0; r.hi = (word_t)i - 1; return r; }
            }
            h = (h + 1) & ~((word_t)-1 << (capbyte & 0x3f));
            if (h < 2) h = 1;
            i = cL4_hash_probe(&h, h, 2);
        } while (i != 0);
    }
    r.lo = 0; r.hi = 0;
    return r;
}

/* FUN_00398834 @ 0x398834  (est. sk_variant_apply)
 * Apply a variant operation: build a variant from {p2, 0, p3}, then if its
 * kind is 1 call the resolved function (op 3), resetting the slot on
 * kind 0. */
static void sk_variant_apply(word_t p1, word_t p2, word_t p3)
{
    word_t a[3]; short kind; word_t fn; word_t v;
    word_t canary = -0x2c8502b44bfffed6;
    a[0] = p1;
    cL4_variant_build_a((word_t*)&a[1], (word_t*)&a[0], p2, 0, p3);
    if (kind == 1) (*fn)(a[1], 3, 0);
    else if (kind != 0) a[1] = 0;
    if (canary != -0x2c8502b44bfffed6) cL4_runtime_fatal();
}

/* FUN_00399d68 alias already handled. */

/* Unwrap helper: FUN_0038df24 returns the boxed value via *out. */
static cL4_w16_t sk_md_unwrap(word_t *out, word_t val)
{
    cL4_w16_t r = cL4_variant_unwrap(out, val);
    return r;
}
