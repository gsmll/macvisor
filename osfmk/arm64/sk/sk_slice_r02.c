/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel,
 * arm64e, image base 0) — the cL4 microkernel (GL1), "cL4 (679.100.61)".
 * Ground truth: Ghidra FUN_ names + addresses in program cl4_kernel.raw.
 * This slice (0x39fcc4-0x3a68a4) is the Swift type-metadata demangler /
 * demangle-tree parser used by the embedded Swift runtime: it turns a mangled
 * type string into a tree of demangle nodes (each a "Node" with a 16-bit
 * kind code and a payload/child-array) that the runtime then prints or
 * reflects on. All names are estimates unless string-matched. */

#include <stdint.h>
#include <stddef.h>
#include <string.h>

/* cL4 returns many values as a 16-byte pair (two 64-bit words in x0/x1). */
typedef struct { unsigned long lo, hi; } cL4_w16_t;

/* ------------------------------------------------------------------ *
 * Out-of-slice helper declarations (declared extern with a one-line note;
 * their bodies are reconstructed by the range worker that owns them).
 * ------------------------------------------------------------------ */

/* FUN_0006e064 @ 0x6e064 — validate a descriptor index. */
extern int cL4_index_ok(long rec);
/* FUN_0000456c @ 0x456c — read a per-CPU / hardware value (used by
 * FUN_003a0dec to seed a 16-bit token). */
extern unsigned int cL4_hw_seed(void);
/* FUN_00019850 @ 0x19850 — read/write the 16-bit object at *p; used as a
 * token reserve/commit pair in FUN_003a0dec. */
extern long cL4_token_ops(unsigned short *p);
/* FUN_00118cf8 @ 0x118cf8 — convert an object/string into a cL4 handle. */
extern unsigned long cL4_make_handle(unsigned long obj);
/* FUN_001145b0 @ 0x1145b0 (thunk) — string compare (length-prefixed). */
extern int cL4_str_compare(unsigned long a, unsigned long b, unsigned long n);
/* FUN_00114c60 @ 0x114c60 (thunk) — Swift two-arg reallocation. */
extern void *cL4_swift_realloc2(void *p, unsigned long size);
/* FUN_00115080 @ 0x115080 (thunk) — retain/increment refcount of an object,
 * returning its length/refcount. */
extern unsigned long cL4_obj_retain_length(unsigned long obj);
/* FUN_00012568 @ 0x12568 (thunk) — cL4 free with size tag. */
extern void cL4_free(void *p, unsigned long size);
/* FUN_00116bb4 @ 0x116bb4 — Swift String builtin: format into a buffer;
 * returns length or -1. (format machinery for __file__/__line__ strings) */
extern long cL4_swift_format(void *buf, unsigned long cap, const char *fmt, ...);
/* FUN_000101a0 @ 0x101a0 — Swift allocation with magic tag. */
extern void *cL4_swift_alloc(unsigned long size, unsigned long tag);
/* FUN_000102f4 @ 0x102f4 — Swift reallocation. */
extern void *cL4_swift_realloc(void *p, unsigned long size, unsigned long tag);
/* FUN_00117cc8 @ 0x117cc8 — memcpy (src,dst n) form. */
extern void *cL4_memcpy(void *dst, const void *src, unsigned long n);
/* FUN_00117cc4 @ 0x117cc4 — memcpy. */
extern void cL4_memcpy_v(unsigned long dst, unsigned long src, unsigned long n);
/* FUN_0011d7e8 @ 0x11d7e8 — Swift runtime error: noreturn trap on a
 * corrupted value/object (stack-canary mismatch). */
extern void cL4_swift_fatal(void) __attribute__((noreturn));
/* FUN_0035bd48 @ 0x35bd48 — fetch the thread's Swift metadata / MR block. */
extern long cL4_mr_block(void);
/* FUN_00361528 @ 0x361528 — print/warn helper (runtime warning). */
extern void cL4_runtime_warn(unsigned long msg, int flag);
/* FUN_00362ea4 @ 0x362ea4 — release/destroy a small Swift object. */
extern void cL4_small_release(void *obj);
/* FUN_00363f70 @ 0x363f70 — demangler: emit a fixed kind node with a raw
 * string slice payload. */
extern void cL4_dem_node_slice(long state, unsigned short kind,
                               const char *base, unsigned long len);
/* FUN_00365660 @ 0x365660 — demangler: reserve a raw string buffer in state. */
extern void *cL4_dem_strbuf(long state, unsigned long n);
/* FUN_0036805c / FUN_003680cc @ 0x36805c/0x3680cc — release small buffers. */
extern void cL4_small_release_a(void *obj);
extern void cL4_small_release_b(void *obj);
/* FUN_00369b04/0c/18 @ 0x369b04-8 — Swift runtime internals for the
 * "bad mangled name" crash reporter. */
extern void cL4_crash_emit(int n, long buf, void *code);
extern int  cL4_crash_check(void);
extern unsigned long cL4_crash_lookup(unsigned long i, unsigned long x);
/* FUN_0036a358 @ 0x36a358 — resolve a Node child reference. */
extern void *cL4_node_child_ref(long *node);
/* FUN_0036aae4 @ 0x36aae4 — copy/duplicate a small value (returns w16). */
extern cL4_w16_t cL4_small_copy(long obj);
/* FUN_0036b118 @ 0x36b118 — release/teardown a small object. */
extern void cL4_small_release_x(long obj);
/* FUN_0036b250 @ 0x36b250 — read a word from a Node payload. */
extern unsigned long cL4_node_word(unsigned long node);
/* FUN_0036b2d0/0340 @ 0x36b2d0/0x36b340 — release variants. */
extern void cL4_small_release_y(unsigned long obj);
extern void cL4_small_release_z(unsigned long obj);
/* FUN_0036b5c4 @ 0x36b5c4 — retain a Node. */
extern void cL4_node_retain(long node);
/* FUN_0036b8b0 @ 0x36b8b0 — copy a Node reference. */
extern long cL4_node_copy(long *node);
/* FUN_0036f878 @ 0x36f878 — read a per-thread Node field (deferred). */
extern void cL4_node_field_get(void);
/* FUN_0037364c @ 0x37364c — copy a String value into out. */
extern void cL4_string_copy(long *out, void *src);
/* FUN_003743d0/74d80/74de4 @ 0x3743d0-4e4 — Node index/child resolve. */
extern void *cL4_node_index(void *p);
extern void *cL4_node_child(void *p, void *q);
extern void *cL4_node_ptr(long *p, void *q);
/* FUN_003766b4 @ 0x3766b4 — copy a Node (returns pointer + out). */
extern long cL4_node_copy_r(long node, void *out);
/* FUN_003766fc @ 0x3766fc — release a Node. */
extern void cL4_node_release(long node);
/* FUN_0037d1d8 @ 0x37d1d8 — build a Swift metadata descriptor. */
extern void cL4_meta_build(void *out, unsigned long obj);
/* FUN_0037e58c/e614/e8e8/eb4c @ 0x37e58c+ — Swift array bulk-copy helpers. */
extern void cL4_arr_copy_begin(void *ctx, unsigned long p, unsigned long imm);
extern void cL4_arr_copy_loop(void *ctx, unsigned long p);
extern void cL4_arr_copy_small(unsigned long p, unsigned long n);
extern void cL4_arr_copy_finish(void *ctx, unsigned long n);
/* FUN_003895e0 @ 0x3895e0 — build a metadata value from a descriptor. */
extern void cL4_meta_value(void *out, int n, unsigned long a, unsigned long b,
                           unsigned long c, void *x, void *y);
/* FUN_003ad810 @ 0x3ad810 — push a Node onto the state's node stack
 * (state+0x58 / count at +0x60, or +0x68/+0x70 for the second stack). */
extern void cL4_dem_stack_push(long state, void **node, long st);
/* FUN_003ac430 @ 0x3ac430 — demangler: parse a numeric length. */
extern long cL4_dem_number(long state);
/* FUN_003ac4a4 @ 0x3ac4a4 — demangler: parse a numeric value. */
extern long cL4_dem_value(long state);
/* FUN_003ac580 @ 0x3ac580 — demangler: parse an identifier-ish entity. */
extern long cL4_dem_ident(long state, unsigned long cur, long c);
/* FUN_003acda0 @ 0x3acda0 — demangler: is this a mangling-token char. */
extern int cL4_dem_token(unsigned short kind);
/* FUN_003ace08/050/0fc @ 0x3ace08-0fc — demangler: parse operand nodes. */
extern long cL4_dem_op_a(long state);
extern long cL4_dem_op_b(long state);
extern long cL4_dem_op_c(long state);
/* FUN_003acfb4 @ 0x3acfb4 — demangler: finish a node. */
extern void cL4_dem_finish(long state, long node, long child, int flag);
/* FUN_003ad478 @ 0x3ad478 — demangler: parse a generic node. */
extern long cL4_dem_generic(long state);
/* FUN_003ad560 @ 0x3ad560 — demangler: pop an operand. */
extern long cL4_dem_pop(long state);
/* FUN_003ad5a4 @ 0x3ad5a4 — demangler: fresh "context" node. */
extern long cL4_dem_ctx(void);
/* FUN_003ad61c @ 0x3ad61c — demangler: parse a node. */
extern long cL4_dem_parse(long state);
/* FUN_003ad724 @ 0x3ad724 — demangler: parse an attribute node. */
extern int cL4_dem_attr(long state, void *a, void *b);
/* FUN_003ad874 @ 0x3ad874 — demangler: apply a substitution. */
extern long cL4_dem_subst(long state, long node, void *a, int b);
/* FUN_003b02dc/03c0/05c8 @ 0x3b02dc-0x3b05c8 — demangler: node helpers. */
extern long cL4_dem_help_a(long state);
extern void cL4_dem_help_b(long state, long node);
extern long cL4_dem_help_c(long state, unsigned short kind);
/* FUN_003b0b7c @ 0x3b0b7c — demangler: finalize/release a node buffer. */
extern void cL4_dem_nodebuf_release(void *node);
/* FUN_003b0e1c @ 0x3b0e1c — Swift small-vector reserve. */
extern void *cL4_smallvec_reserve(long vec, unsigned long cap);
/* FUN_003b0ec4 @ 0x3b0ec4 — Swift integer-to-string. */
extern int cL4_itoa(unsigned long v, char *out);
/* FUN_003b0f48 @ 0x3b0f48 — copy a small-vector header. */
extern void cL4_smallvec_copy_hdr(void *dst, void *src);
/* FUN_003b0fb8 @ 0x3b0fb8 — copy a small-vector. */
extern void cL4_smallvec_copy(void *dst, void *src);
/* FUN_003bc9a4 @ 0x3bc9a4 — convert a node to a String. */
extern void cL4_node_to_string(void *out, long node, unsigned long extra);
/* FUN_003bd1f4 @ 0x3bd1f4 — string construction helper. */
extern void cL4_str_construct(void *out, unsigned long obj, unsigned long tag);
/* FUN_003bed8c @ 0x3bed8c — Swift string decode (mangled ident). */
extern int cL4_str_decode(unsigned long s, unsigned long n, void *out);
/* FUN_003d2b40 @ 0x3d2b40 — Swift runtime metadata build. */
extern void cL4_runtime_meta(void *out, unsigned long obj);
/* FUN_003d3dd8 @ 0x3d3dd8 — OSLog / printf-style reporter. */
extern void cL4_report(unsigned long *log, unsigned long *fmt);
/* FUN_004b9ccc/d68/e2c/ed8 @ 0x4b9ccc-0x4b9ed8 — runtime diagnostics
 * (assertion failure / string-print). */
extern void cL4_diag_a(int n);
extern void cL4_diag_b(int n, unsigned long buf);
extern void cL4_diag_c(int n, unsigned long msg, void *stack);
extern void cL4_diag_d(int n, const char *msg);
/* FUN_004ba3a8 @ 0x4ba3a8 — noreturn fatal with a string + flag. */
extern void cL4_fatal_str(const char *s, int flag) __attribute__((noreturn));
/* FUN_004ba5a4 @ 0x4ba5a4 — format/query helper returning a token. */
extern unsigned long cL4_token_format(int n, const char *fmt, ...);

/* Global: the current thread / TCB pointer (_DAT_006c0380). */
extern unsigned long cL4_current_thread;  /* _DAT_006c0380 */

/* Global runtime diagnostic gate _DAT_006c0b18 and flag _DAT_006c0b10. */
extern long cL4_report_gate;   /* _DAT_006c0b18 */
extern unsigned char cL4_report_flag;  /* _DAT_006c0b10 */

/* Globals for the runtime metadata table (DAT_004f2740/48/60). */
extern unsigned long cL4_meta_none;   /* DAT_004f2740 */
extern unsigned long cL4_meta_empty;  /* DAT_004f2748 */
extern unsigned long cL4_meta_builtin_table[]; /* DAT_004f2960 */

/* ------------------------------------------------------------------ *
 * Shared demangler data structures
 * ------------------------------------------------------------------ */

/* A demangle-tree Node: a 16-bit kind code plus a payload. The tag byte at
 * +0x12 selects the layout: 0=empty; 1=one child (word0); 2=two children
 * (word0,word1); 3={payload,count}; 4=payload only; 5=array of children. */
typedef struct dem_node {
    unsigned long  w0;      /* +0x00 */
    unsigned long  w1;      /* +0x08 */
    unsigned short kind;    /* +0x10 */
    unsigned char  tag;     /* +0x12 */
    unsigned char  rsvd;    /* +0x13 */
    unsigned int   count;   /* +0x14 */
    unsigned int   cap;     /* +0x18 */
} dem_node_t;

/* Demangler parse state (param_1 of the parse routines). */
typedef struct dem_state {
    unsigned long  pad0[7];         /* +0x00..+0x37 */
    const char    *src;             /* +0x38 */
    unsigned long  src_end;         /* +0x40 */
    unsigned long  pos;             /* +0x48 */
    unsigned char  flag50;          /* +0x50 */
    unsigned char  flag51;          /* +0x51 */
    unsigned long  pad52;           /* +0x52 */
    dem_node_t   **stack;           /* +0x58 */
    unsigned int   stack_count;     /* +0x60 */
    unsigned int   pad64;
    dem_node_t   **stack2;          /* +0x68 */
    unsigned int   stack2_count;    /* +0x70 */
    unsigned int   pad74;
    unsigned long  locals[26][2];   /* +0x78 sub-identifier table */
    unsigned int   local_count;     /* +0x218 */
    unsigned int   pad21c;
    unsigned long  collect[2];      /* +0x220 */
    unsigned long  cb;              /* +0x238 */
} dem_state_t;

/* ------------------------------------------------------------------ *
 * In-slice forward declarations (mutual recursion).
 * ------------------------------------------------------------------ */
static unsigned long cL4_dem_field1(long p);   /* 3a13c4 */
static unsigned long cL4_dem_field2(long p, unsigned long idx);   /* 3a1480 */
static unsigned long cL4_dem_field5(long p);   /* 3a2044 */
static long   cL4_dem_sizeof(long *p);         /* 3a2290 */
static void   cL4_dem_copy(long *p, long n);   /* 3a232c */
static cL4_w16_t cL4_dem_copy2(unsigned long *dst, unsigned long src, unsigned long x, unsigned long *a, unsigned long *b); /* 3a23b4 */
static int    cL4_dem_has_extra(long p);       /* 3a2468 */
static void   cL4_dem_build_extra(unsigned long *out, long p); /* 3a24d0 */
static unsigned long cL4_dem_load(unsigned long *p);   /* 3a25a0 */
static unsigned long cL4_dem_load2(unsigned long *p);  /* 3a25b8 */
static unsigned long cL4_dem_capacity(unsigned long c, long n); /* 3a28e8 */
static void   cL4_dem_reserve1(long *vec, long buf, unsigned long n, long sz); /* 3a294c */
static void   cL4_dem_reserve2(long *vec, long buf, unsigned long n, long sz); /* 3a2a38 */
static unsigned long cL4_dem_node_reserve(dem_state_t *st, unsigned long n);  /* 3a3898 */
static void   cL4_dem_emit_bare(dem_state_t *st, unsigned short k, unsigned long p); /* 3a3944 */
static void   cL4_dem_emit_pair(dem_state_t *st, unsigned short k, unsigned long a, unsigned long b); /* 3a3980 */
static void   cL4_dem_emit_pairw(dem_state_t *st, unsigned short k, unsigned long *p); /* 3a39c8 */
static dem_node_t *cL4_dem_emit_str(dem_state_t *st, unsigned short k, unsigned long s); /* 3a3a10 */
static void   cL4_dem_node_push_child(dem_state_t *st, dem_node_t *n, unsigned long child); /* 3a3460 */
static void   cL4_dem_array_push(dem_state_t *st, long *vec, unsigned int *cnt, unsigned long n); /* 3a3578 */
static void   cL4_dem_string_push(dem_state_t *st, long *s, unsigned long data, long n); /* 3a3a70 */
static void   cL4_dem_string_reserve(dem_state_t *st, long *s, unsigned int *cnt, unsigned long n); /* 3a3aec */
static long   cL4_dem_save_state(dem_state_t *st, long obj, unsigned long a, unsigned long b, unsigned long c); /* 3a3d18 */
static long   cL4_dem_restore_state(dem_state_t *st);  /* 3a3de4 */
static long   cL4_dem_parse_node(dem_state_t *st, short *sub, unsigned long len, unsigned long c); /* 3a3e54 */
static unsigned long cL4_dem_parse_until(dem_state_t *st);  /* 3a4094 */
static unsigned long cL4_dem_pop_kind_node(dem_state_t *st, void *fn); /* 3a4110 */
static void   cL4_dem_dispatch(dem_state_t *st);   /* 3a4180 */
static dem_node_t *cL4_dem_node1(dem_state_t *st, unsigned short k, long child); /* 3a4b38 */
static dem_node_t *cL4_dem_node2(dem_state_t *st, unsigned short k, long a, long b); /* 3a4b98 */
static dem_node_t *cL4_dem_node3(dem_state_t *st, unsigned short k, long a, long b, long c); /* 3a4c14 */
static dem_node_t *cL4_dem_node4(dem_state_t *st, unsigned short k, long a, long b, long c, long d); /* 3a4ca8 */
static dem_node_t *cL4_dem_node_copy_children(dem_state_t *st, dem_node_t *src, unsigned short k); /* 3a4d5c */
static dem_node_t *cL4_dem_node_f4(dem_state_t *st);  /* 3a4ea4 */
static long   cL4_dem_node_pattern(dem_state_t *st, long *sub);  /* 3a4f5c */
static long   cL4_dem_operand(dem_state_t *st, int k);  /* 3a5518 */
static long   cL4_dem_parse_simple(dem_state_t *st);  /* 3a56a0 */
static unsigned long cL4_dem_pop_f4(dem_state_t *st); /* 3a58b0 */
static unsigned long *cL4_dem_parse_intchar(dem_state_t *st); /* 3a5908 */
static unsigned long cL4_dem_parse_ident(dem_state_t *st); /* 3a599c */
static unsigned long cL4_dem_parse_builtin(dem_state_t *st); /* 3a5aa0 */
static long   cL4_dem_parse_fixed(dem_state_t *st, unsigned long k); /* 3a6090 */
static long   cL4_dem_parse_attrib(dem_state_t *st);  /* 3a613c */
static void   cL4_dem_parse_special(dem_state_t *st); /* 3a61d8 */
static long   cL4_dem_parse_attr2(dem_state_t *st);   /* 3a62f8 */
static void   cL4_dem_emit_0x32(dem_state_t *st);     /* 3a63d8 */
static void   cL4_dem_emit_0x1b(dem_state_t *st);     /* 3a644c */
static void   cL4_dem_emit_0x30(dem_state_t *st);     /* 3a64f0 */
static void   cL4_dem_emit_0x31(dem_state_t *st);     /* 3a6560 */
static void   cL4_dem_emit_0x33(dem_state_t *st);     /* 3a65d4 */
static dem_node_t *cL4_dem_emit_0xbf(dem_state_t *st); /* 3a663c */
static long   cL4_dem_emit_0xc1(dem_state_t *st);     /* 3a672c */
static void   cL4_dem_emit_kind(dem_state_t *st, unsigned long k); /* 3a6874 */
static unsigned long *cL4_dem_parse_word(dem_state_t *st); /* 3a68a4 */
static void cL4_dem_str_empty(long *out);  /* 3a1310 */
static void cL4_dem_warn(unsigned long msg);  /* 3a18c8 */
static void cL4_dem_skip_string(unsigned char *s);  /* 3a31d8 */
static void cL4_dem_badstr(long *out);  /* 3a27f0 */
static unsigned long cL4_dem_is_qualified_kind(unsigned int k);  /* 3a3040 */
/* Additional in-slice prototypes for the kind-dispatch helpers. */
static void   cL4_dem_str_build(long *out, unsigned long desc, unsigned long idx); /* 3a160c */
static cL4_w16_t cL4_dem_str_slot(long p, unsigned long idx, long *oa, unsigned long *ob); /* 3a1098 */
static int    cL4_dem_has_child(long p);        /* 3a1cbc */
static unsigned long cL4_dem_field_d(long p);   /* 3a1f60 */
static void   cL4_dem_vt_apply3(unsigned long *out, long *vt, unsigned long a, unsigned long b, unsigned long cc); /* 3a11c0 */
static void   cL4_dem_vt_apply2(unsigned long *out, long *vt, unsigned long a); /* 3a156c */
static void   cL4_dem_vt_apply4(long *vt, unsigned long p1, unsigned long p4, unsigned long p5, unsigned long p6); /* 3a21f4 */
static void   cL4_dem_kind_apply_d(unsigned long *vt, unsigned long p1, unsigned long meta, unsigned long p5, unsigned long p6); /* 3a1dac */
static void   cL4_dem_kind_apply_a(unsigned long *vt, unsigned long p1, unsigned long p4, unsigned long p5, unsigned long p6); /* 3a1b0c */
static long   cL4_dem_index_get(long p, unsigned long idx); /* 3a20cc */
static cL4_w16_t cL4_dem_field3(long p, unsigned long p2, unsigned long *a, unsigned long *b); /* 3a1518 */
static cL4_w16_t cL4_dem_field3b(long p, unsigned long p2, unsigned long *a, unsigned long *b); /* 3a21a0 */


/* ------------------------------------------------------------------ */

/* Walk the demangler "context chain": from a global context record, follow
 * the +8 link until the entry whose +0x28 field is non-null. (Ghidra
 * collapses the root argument to the loader, so read the runtime context.) */
static long cL4_dem_ctx_walk(void)
{
    /* Start from the runtime context record (cL4_current_thread/_DAT_006c0380)
     * and follow the +8 link until the +0x28 field is non-null. */
    long t = cL4_dem_load(&cL4_current_thread);
    while ((*(long *)(t + 0x28) == 0 || *(long *)(t + 0x28) == 0)) {
        long link = *(long *)(t + 8);
        t = 0;
        if (link != 0) t = link;
    }
    return t;
}

/* FUN_0039fcc4 @ 0x0039fcc4   (est. cL4_dem_opcode)
 * Ghidra: ulong FUN_0039fcc4(ulong *param_1)
 * Returns the low 32 bits of the operation word when it is a valid
 * (< 0x800) demangle token, else 0.
 * Confidence: medium
 */
unsigned long cL4_dem_opcode(unsigned long *word)
{
    unsigned long v = 0;
    if (*word < 0x800) v = *word & 0xffffffff;
    return v;
}

/* FUN_003a0ed4 @ 0x003a0ed4   (est. cL4_dem_resolve)
 * Ghidra: undefined1[16] FUN_003a0ed4(ulong *param_1, undefined8 *param_2)
 * Resolves a demangle operand pair into a {base, meta} word pair, following
 * indirect child references. Kind 0x303 follows two child pointers; kind
 * 0x307 dispatches on the tag byte at *param_1[1]: 0 = index through
 * param_2[3], 1 = value via cL4_dem_load2, 2 = re-resolve through
 * FUN_003743d0(*param_2), 3 = fail-closed trap. Non-special kinds return
 * {param_1, param_2} directly.
 * Confidence: low
 */
cL4_w16_t cL4_dem_resolve(unsigned long *word, unsigned long *meta)
{
    cL4_w16_t r;
    unsigned long *nw;
    unsigned char b;

    for (;;) {
        int kind = 0;
        if (*word < 0x800) kind = (int)*word;
        for (;;) {
            if (kind != 0x307) {
                if (kind != 0x303) {
                    r.lo = (unsigned long)word;
                    r.hi = (unsigned long)meta;
                    return r;
                }
                nw = (unsigned long *)cL4_node_ptr((long*)word, (void*)meta);
                meta = (unsigned long *)cL4_node_child((void*)word, (void*)meta);
                word = nw;
                break;
            }
            b = *(unsigned char *)word[1];
            if (b < 2) break;
            if (b == 2) { word = (unsigned long *)cL4_node_index((void*)*meta); break; }
            if (b == 3) { __asm__ volatile("brk #1" ::: "memory"); /* 0x3a0fc0 */ }
        }
        if (b == 0) {
            word = (unsigned long *)meta[3];
            meta = (unsigned long *)cL4_node_child_ref((long*)meta);
            continue;
        }
        /* b == 1 */
        word = (unsigned long *)cL4_dem_load2((unsigned long*)*meta);
    }
}

/* FUN_0039fcd8 @ 0x0039fcd8   (est. cL4_dem_kind_get)
 * Ghidra: ulong FUN_0039fcd8(undefined8 param_1, ulong *param_2, undefined8 param_3)
 * Dispatches on the resolved operation kind and returns a demangle node kind
 * from the runtime table (0x67c1c8 / 0x67c0d0 / 0x67b0a8 / 0x67c230).
 * Out-of-range tokens hit a fail-closed SoftwareBreakpoint(1) trap.
 * Confidence: low
 */
unsigned long cL4_dem_kind_get(unsigned long op, unsigned long *word,
                               unsigned long x)
{
    unsigned long r;
    cL4_w16_t rv;
    unsigned long *cand, *base;
    long t, link;
    long kind;

    rv = cL4_dem_resolve((unsigned long*)x, (unsigned long*)op);
    cand = (unsigned long*)rv.hi;
    base = (unsigned long*)rv.lo;
    if (word != 0) base = word;

    kind = 0;
    if (*base < 0x800) kind = (int)*base;

    if (kind < 0x203) {
        if (kind - 0x201U < 2) { r = 0x67c1c8; return cL4_dem_field1((long)&r); }
        if (kind != 0) {
            if (kind != 0x200) return 0;
            r = 0x67c0d0; return cL4_dem_field1((long)&r);
        }
    } else if (kind < 0x301) {
        if (kind != 0x203) {
            if (kind != 0x300) return 0;
            if ((base != (unsigned long*)0x67b0a8) ||
                (0xfffffffffffff800 < **(long **)*cand - 0x800U)) return 0;
            if (word == 0) {
                t = cL4_dem_ctx_walk();
            }
            cand = (unsigned long*)0x67b0a8;
            base = (unsigned long*)0x67b0a8;
            goto use230;
        }
    } else {
        if (kind < 0x305) { if (kind != 0x301) return 0; return base[1]; }
        if (kind != 0x305) {
            if ((1 < kind - 0x500U) && (kind != 0x400)) return 0;
            __asm__ volatile("brk #1" ::: "memory"); /* 0x39fd58 */
        }
    }
    if (word == 0) {
        t = cL4_dem_ctx_walk();
    }
    cand = &r;
use230:
    r = 0x67c230;
    return cL4_dem_field5((long)cand);
}

/* FUN_0039ff2c @ 0x0039ff2c   (est. cL4_dem_kind_get2)
 * Ghidra: ulong FUN_0039ff2c(ulong *param_1)
 * Companion of cL4_dem_kind_get with a single operand (the same table
 * dispatch over the resolved operation kind).
 * Confidence: low
 */
unsigned long cL4_dem_kind_get2(unsigned long *word, unsigned long x)
{
    unsigned long r;
    cL4_w16_t rv;
    unsigned long *cand, *base;
    long t, link;
    long kind;

    rv = cL4_dem_resolve(word, (unsigned long*)0);
    cand = (unsigned long*)rv.hi;
    base = (unsigned long*)rv.lo;
    if (word != 0) base = word;

    kind = 0;
    if (*base < 0x800) kind = (int)*base;

    if (kind < 0x203) {
        if (kind - 0x201U < 2) { r = 0x67c1c8; return cL4_dem_field1((long)&r); }
        if (kind != 0) {
            if (kind != 0x200) return 0;
            r = 0x67c0d0; return cL4_dem_field1((long)&r);
        }
    } else if (kind < 0x301) {
        if (kind != 0x203) {
            if (kind != 0x300) return 0;
            if ((base != (unsigned long*)0x67b0a8) ||
                (0xfffffffffffff800 < **(long **)*cand - 0x800U)) return 0;
            if (word == 0) {
                t = cL4_dem_ctx_walk();
            }
            cand = (unsigned long*)0x67b0a8;
            base = (unsigned long*)0x67b0a8;
            goto use230;
        }
    } else {
        if (kind < 0x305) { if (kind != 0x301) return 0; return base[1]; }
        if (kind != 0x305) {
            if ((1 < kind - 0x500U) && (kind != 0x400)) return 0;
            __asm__ volatile("brk #1" ::: "memory"); /* 0x39ffa8 */
        }
    }
    if (word == 0) {
        t = cL4_dem_ctx_walk();
    }
    cand = &r;
use230:
    r = 0x67c230;
    return cL4_dem_field5((long)cand);
}

/* FUN_003a0b04 @ 0x003a0b04   (est. cL4_dem_kind_bool)
 * Ghidra: undefined8 FUN_003a0b04(undefined8 param_1, undefined8 param_2)
 * Dispatch on the resolved operation kind; returns 1 for the "named
 * children" kinds (0x201/0x202), else 0 after walking the context chain.
 * Confidence: low
 */
unsigned long cL4_dem_kind_bool(unsigned long op, unsigned long word)
{
    cL4_w16_t rv;
    unsigned long r, *cand, *base;
    long t, link;
    long kind;

    rv = cL4_dem_resolve((unsigned long*)word, (unsigned long*)op);
    base = (unsigned long*)rv.lo;
    cand = (unsigned long*)rv.hi;

    kind = 0;
    if (*base < 0x800) kind = (int)*base;

    if (kind < 0x203) {
        if (kind - 0x201U < 2) { r = 0x67c1c8; return cL4_dem_field1((long)&r); }
        if (kind != 0) return 0;
    } else if (kind < 0x305) {
        if (kind != 0x203) {
            if (kind != 0x300) return 0;
            if (base != (unsigned long*)0x67b0a8) return 0;
            if (0xfffffffffffff800 < **(long **)*cand - 0x800U) return 0;
            t = cL4_dem_ctx_walk();
            return 0;
        }
    } else if (kind != 0x305) {
        if ((1 < kind - 0x500U) && (kind != 0x400)) return 0;
        __asm__ volatile("brk #1" ::: "memory"); /* 0x3a0c90 */
    }
    t = cL4_dem_ctx_walk();
    return 0;
}

/* FUN_003a13c4 @ 0x003a13c4   (est. cL4_dem_field1)
 * Ghidra: undefined4 FUN_003a13c4(long param_1)
 * Returns the field at +0x14 of the descriptor reached via param_1+8 -> +8,
 * or 0 when that descriptor is empty/invalid.
 * Confidence: low
 */
unsigned long cL4_dem_field1(long p)
{
    long d = *(long *)(*(long *)(p + 8) + 8);
    long d2 = (d == 0) ? 0 : d;
    if (*(int *)(d2 + 0x10) != 0 &&
        (long)*(int *)(d2 + 0x10) != -0x10 - d2) {
        long d3 = (d == 0) ? 0 : d;
        return *(unsigned long *)(d3 + 0x14);
    }
    return 0;
}

/* FUN_003a1480 @ 0x003a1480   (est. cL4_dem_field2)
 * Ghidra: undefined4 FUN_003a1480(long param_1, ulong param_2)
 * Indexed field fetch: bounds-check param_2 against the descriptor count,
 * then return the element at index param_2 of the descriptor's array
 * (+0x18-scaled). Out of range -> fail-closed trap.
 * Confidence: low
 */
unsigned long cL4_dem_field2(long p, unsigned long idx)
{
    long d, d2;
    if ((long)idx < 0) goto trap;
    d = *(long *)(*(long *)(p + 8) + 8);
    if (d == 0 || d == 0) {
        /* (Ghidra's __thread_bss.sizeofcmds term collapses to the empty
         * descriptor case; treat as d2=0 when idx is within bounds.) */
        d2 = 0;
        goto fetch;
    } else if (idx <= *(unsigned int *)(d + 0x14)) {
        goto fetch;
    }
trap:
    __asm__ volatile("brk #1" ::: "memory");   /* 0x3a1518 */
fetch:
    return *(unsigned long *)(*(long *)(p + 8) +
             (unsigned long)*(unsigned int *)(d2 + 0x18) * 8 + idx * 4);
}

/* FUN_003a2044 @ 0x003a2044   (est. cL4_dem_field5)
 * Ghidra: undefined4 FUN_003a2044(long param_1)
 * Returns the field at +0x24 of the descriptor reached via param_1+8 -> +0x28.
 * Confidence: low
 */
unsigned long cL4_dem_field5(long p)
{
    long d = *(long *)(*(long *)(p + 8) + 0x28);
    long d2 = (d == 0) ? 0 : d;
    if (*(int *)(d2 + 0x10) == 0 ||
        (long)*(int *)(d2 + 0x10) == -0x10 - d2) return 0;
    long d3 = (d == 0) ? 0 : d;
    return *(unsigned long *)(d3 + 0x24);
}

/* FUN_003a25a0 @ 0x003a25a0   (est. cL4_dem_load)
 * Ghidra: undefined8 FUN_003a25a0(undefined8 *param_1)
 * Load the word at *p.
 * Confidence: high
 */
unsigned long cL4_dem_load(unsigned long *p) { return *p; }

/* FUN_003a25b8 @ 0x003a25b8   (est. cL4_dem_load2)
 * Ghidra: undefined8 FUN_003a25b8(undefined8 *param_1)
 * Load the word at *p.
 * Confidence: high
 */
unsigned long cL4_dem_load2(unsigned long *p) { return *p; }

/* FUN_003a25d4 @ 0x003a25d4   (est. cL4_dem_release_masked1)
 * Ghidra: void FUN_003a25d4(ulong param_1)
 * Release an object with the low tag bits masked off.
 * Confidence: medium
 */
void cL4_dem_release_masked1(unsigned long obj)
{
    cL4_small_release_y(obj & 0x8ffffffffffffff8);
}

/* FUN_003a25e0 @ 0x003a25e0   (est. cL4_dem_release_masked2)
 * Ghidra: ulong FUN_003a25e0(ulong param_1)
 * Release an object with the low tag bits masked off; returns the input.
 * Confidence: medium
 */
unsigned long cL4_dem_release_masked2(unsigned long obj)
{
    cL4_small_release_z(obj & 0x8ffffffffffffff8);
    return obj;
}

/* FUN_003a2610 @ 0x003a2610   (est. cL4_dem_release_masked3)
 * Ghidra: void FUN_003a2610(ulong param_1)
 * Release an object with the low tag bits masked off.
 * Confidence: medium
 */
void cL4_dem_release_masked3(unsigned long obj)
{
    cL4_small_release_x(obj & 0x8ffffffffffffff8);
}

/* FUN_003a261c @ 0x003a261c   (est. cL4_dem_issmall1)
 * Ghidra: bool FUN_003a261c(long param_1)
 * True when the value is a small / non-allocated demangle token: for a
 * negative length field the tagged pointer is -1 (empty) or its stored
 * length is zero and not-large; for a non-negative field the high 32 bits
 * are zero.
 * Confidence: low
 */
int cL4_dem_issmall1(long p)
{
    int r;
    unsigned long v = *(unsigned long *)(p + 8);
    if ((long)v < 0) {
        if ((int)v == -1) return 0;
        v = *(unsigned long *)(v * 8 + 0x10);
        r = (v & 0x100000000) == 0 && v >> 0x21 == 0;
    } else {
        r = v >> 0x20 == 0;
    }
    return r;
}

/* FUN_003a265c @ 0x003a265c   (est. cL4_dem_issmall2)
 * Ghidra: bool FUN_003a265c(long param_1)
 * Same as cL4_dem_issmall1 but guards a null param_1.
 * Confidence: low
 */
int cL4_dem_issmall2(long p)
{
    int r = 0;
    unsigned long v;
    if (p != 0) {
        v = *(unsigned long *)(p + 8);
        if ((long)v < 0) {
            if ((int)v == -1) return 0;
            v = *(unsigned long *)(v * 8 + 0x10);
            r = (v & 0x100000000) == 0 && v >> 0x21 == 0;
        } else {
            r = v >> 0x20 == 0;
        }
    }
    return r;
}

/* FUN_003a26a0 @ 0x003a26a0   (est. cL4_dem_issmall3)
 * Ghidra: bool FUN_003a26a0(ulong param_1)
 * Same as cL4_dem_issmall1 applied to a tagged pointer (tag bits masked).
 * Confidence: low
 */
int cL4_dem_issmall3(unsigned long word)
{
    int r;
    unsigned long v = *(unsigned long *)((word & 0x8ffffffffffffff8) + 8);
    if ((long)v < 0) {
        if ((int)v == -1) return 0;
        v = *(unsigned long *)(v * 8 + 0x10);
        r = (v & 0x100000000) == 0 && v >> 0x21 == 0;
    } else {
        r = v >> 0x20 == 0;
    }
    return r;
}

/* FUN_003a0c90 @ 0x003a0c90   (est. cL4_dem_kind_name)
 * Ghidra: char * FUN_003a0c90(ulong *param_1)
 * Returns a human-readable name for a demangle value kind code read from
 * *param_1: 0x200/0x201/0x202/0x204 = NULL; 0x203="Foreign Class";
 * 0x204="Foreign Reference Type"; 0x300="Opaque Value"; 0x301="Tuple";
 * 0x302="Function"; 0x303="Existential"; 0x304=NULL; 0x305="Objective-C
 * Class Wrapper"; 0x306="Existential Metatype"; 0x307="Extended
 * Existential"; 0x400="Heap Local Variable"; 0x500="Heap Generic Local
 * Variable"; 0x501="ErrorType Object"; else "Unknown".
 * Confidence: high (string-matched)
 */
const char *cL4_dem_kind_name(unsigned long *word)
{
    int k = 0;
    if (*word < 0x800) k = (int)*word;
    if (k < 0x302) {
        if (k < 0x203) {
            if (k - 0x200U < 3 || k == 0) return (const char*)0x0;
        } else if (k < 0x300) {
            if (k == 0x203) return "Foreign Class";       /* s__Foreign_Class__005d6550 */
            if (k == 0x204) return "Foreign Reference Type"; /* 005d6560 */
        } else {
            if (k == 0x300) return "Opaque Value";        /* 005d64ed */
            if (k == 0x301) return "Tuple";               /* 005d64fc */
        }
    } else if (k < 0x306) {
        if (k < 0x304) {
            if (k == 0x302) return "Function";            /* 005d6504 */
            if (k == 0x303) return "Existential";         /* 005d650f */
        } else {
            if (k == 0x304) return (const char*)0x0;
            if (k == 0x305) return "Objective-C Class Wrapper"; /* 005d651d */
        }
    } else if (k < 0x400) {
        if (k == 0x306) return "Existential Metatype";    /* 005d6539 */
        if (k == 0x307) return "Extended Existential";    /* 005d65c0 */
    } else {
        if (k == 0x400) return "Heap Local Variable";     /* 005d6579 */
        if (k == 0x500) return "Heap Generic Local Variable"; /* 005d658f */
        if (k == 0x501) return "ErrorType Object";        /* 005d65ad */
    }
    return "Unknown";                                     /* 005d65d7 */
}

/* FUN_003a0dec @ 0x003a0dec   (est. cL4_dem_token_reserve)
 * Ghidra: undefined8 FUN_003a0dec(void)
 * Reserves a fresh demangle token: reads a per-CPU seed, checks a flag bit
 * (bit 8), then reserves the 16-bit token via cL4_token_ops and validates it
 * (bit 0x100) before producing a handle.
 * Confidence: low
 */
unsigned long cL4_dem_token_reserve(void)
{
    unsigned long r;
    unsigned short tok;
    unsigned int seed = cL4_hw_seed();
    tok = (unsigned short)seed;
    if ((seed >> 8 & 1) == 0) {
        r = 0;
    } else {
        long h = cL4_token_ops(&tok);
        r = 0;
        if (h != 0) {
            if ((tok & 0x100) == 0) {
                __asm__ volatile("brk #1" ::: "memory");   /* 0x3a0e40 */
            }
            cL4_token_ops(&tok);
            r = cL4_make_handle(0);
        }
    }
    return r;
}

/* FUN_003a0e44 @ 0x003a0e44   (est. cL4_dem_str_alloc)
 * Ghidra: undefined8 FUN_003a0e44(undefined8 param_1)
 * Allocates a Swift String from a source object: constructs the string
 * (tagged or heap) and returns a handle to it.
 * Confidence: low
 */
unsigned long cL4_dem_str_alloc(unsigned long obj)
{
    unsigned long u;
    unsigned long local_38;
    long local_30;
    unsigned char local_28[8];
    char cStack_21;

    u = cL4_obj_retain_length(obj);
    cL4_str_construct(&local_38, obj, u);
    if (cStack_21 < '\0') {
        /* tagged / indirect string: retain the tail */
        if (local_30 == 0) u = 0;
        else u = cL4_make_handle(local_38);
        cL4_free((void*)local_38, (*(unsigned long*)local_28 & 0x7fffffffffffffff));
    } else if (cStack_21 == '\0') {
        u = 0;
    } else {
        u = cL4_make_handle((unsigned long)&local_38);
    }
    return u;
}

/* FUN_003a0fcc @ 0x003a0fcc   (est. cL4_dem_ctx_value)
 * Ghidra: undefined8 FUN_003a0fcc(undefined8 *param_1)
 * Returns the runtime context value: if the first context field is null,
 * resolve it through the context chain; then return the value at the
 * second context field.
 * Confidence: low
 */
unsigned long cL4_dem_ctx_value(unsigned long *p)
{
    long t, link;
    if (*(long *)*p == 0) {
        t = cL4_dem_ctx_walk();
        *(long *)*p = t;
    }
    return **(unsigned long **)p[2];
}


/* FUN_003a017c @ 0x003a017c   (est. cL4_dem_kind_fetch3)
 * Ghidra: undefined8 FUN_003a017c(ulong *param_1, undefined8 param_2, undefined8 *param_3)
 * Resolves the demangle operand and dispatches on its kind to write a
 * {value, length, flags} triple into param_3:
 *   0x201/0x202 -> {flags=1}
 *   0x200 -> cL4_dem_str_build descriptor fill
 *   0x203/0x305 -> 0x67c230 table through cL4_dem_copy2
 *   0x300 -> 0x67b0a8 table through cL4_dem_copy2 (after ctx walk)
 *   0x301 -> 0x67c068 table through cL4_dem_str_slot
 * Unknown kinds fail closed (trap).
 * Confidence: low
 */
unsigned long cL4_dem_kind_fetch3(unsigned long *word, unsigned long x,
                                  unsigned long *out)
{
    cL4_w16_t rv;
    unsigned long *base, *meta;
    long t;
    unsigned long r;
    int k;

    rv = cL4_dem_resolve(word, (unsigned long*)0);
    meta = (unsigned long*)rv.hi;
    base = (unsigned long*)rv.lo;
    if (word != 0) base = word;

    k = 0;
    if (*base < 0x800) k = (int)*base;

    if (k < 0x203) {
        if (k - 0x201U < 2) { *(unsigned short*)(out + 2) = 1; return 0; }
        if (k != 0) {
            if (k != 0x200) goto L_fail;
            cL4_dem_str_build((long*)out, (unsigned long)base, x);
            out[1] = 0;
            *(int*)(out + 2) = 0;
            *(unsigned char*)((long)out + 0x11) = ((base[0] >> 8) & 1);
            return (unsigned long)base[0];
        }
    } else if (k < 0x301) {
        if (k == 0x203) goto L_230;
        if ((k != 0x300) || (base != (unsigned long*)0x67b0a8) ||
            (0xfffffffffffff800 < **(long **)*meta - 0x800U)) goto L_fail;
        t = cL4_dem_ctx_walk();
        (void)t;
        base = (unsigned long*)0x67b0a8;
        goto L_230;
    } else {
        if (k < 0x305) {
            if (k != 0x301) { __asm__ volatile("brk #1" ::: "memory"); /* 0x3a0440 */ }
            goto L_301;
        }
        if (0x304 < k) {
            if (0x305 < k) {
                if ((1 < k - 0x500U) && (k != 0x306)) {
                    __asm__ volatile("brk #1" ::: "memory"); /* 0x3a01fc */
                }
                goto L_fail;
            }
            goto L_230;
        }
        if (k != 0x301) { __asm__ volatile("brk #1" ::: "memory"); /* 0x3a0440 */ }
    }
L_230:
    out[0] = 0x67c230;
    out[1] = (unsigned long)meta;
    rv = cL4_dem_copy2(out, (unsigned long)out, x, out, out + 1);
    goto L_done;
L_301:
    out[0] = 0x67c068;
    out[1] = (unsigned long)meta;
    rv = cL4_dem_str_slot((long)out, 0, out, out + 1);
L_done:
    *(int*)(out + 2) = ((rv.hi & 0xff0000) == 0);
    *(unsigned char*)((long)out + 0x11) = ((rv.hi >> 8) & 1);
    return (unsigned long)rv.lo;
L_fail:
    __asm__ volatile("brk #1" ::: "memory");   /* 0x3a0438 / 0x3a02e8 */
    return 0;
}

/* FUN_003a0440 @ 0x003a0440   (est. cL4_dem_kind_fetch4)
 * Ghidra: ulong FUN_003a0440(ulong *param_1, ulong param_2)
 * Two-operand table fetch over the resolved kind, with an index: for kind
 * 0x301 indexes into the operand array (bounds-checked); other kinds route
 * through the 0x67c0d0 / 0x67c230 table lookups. Fail-closed traps.
 * Confidence: low
 */
unsigned long cL4_dem_kind_fetch4(unsigned long *word, unsigned long idx)
{
    unsigned long r;
    cL4_w16_t rv;
    unsigned long *cand, *base;
    long t;
    long k;

    rv = cL4_dem_resolve(word, (unsigned long*)0);
    cand = (unsigned long*)rv.hi;
    base = (unsigned long*)rv.lo;
    if (word != 0) base = word;

    k = 0;
    if (*base < 0x800) k = (int)*base;

    if (k < 0x203) {
        if (k - 0x201U < 2) return 0;
        if (k != 0) {
            if (k == 0x200) { r = 0x67c0d0; return cL4_dem_field1((long)&r); }
            goto L_fail;
        }
    } else if (k < 0x301) {
        if (k != 0x203) {
            if ((k != 0x300) || (base != (unsigned long*)0x67b0a8) ||
                (0xfffffffffffff800 < **(long **)*cand - 0x800U)) goto L_fail;
            t = cL4_dem_ctx_walk();
            (void)t;
            base = (unsigned long*)0x67b0a8;
            goto L_230;
        }
    } else {
        if (k < 0x305) {
            if (k != 0x301) { __asm__ volatile("brk #1" ::: "memory"); /* 0x3a0690 */ }
            if ((long)idx < 0 || idx > base[1]) return 0;
            return base[(idx & 0xffffffff) * 2 + 4];
        }
        if (0x305 < k) {
            if ((1 < k - 0x500U) && (k != 0x306)) {
                __asm__ volatile("brk #1" ::: "memory"); /* 0x3a04bc */
            }
            goto L_fail;
        }
    }
    t = cL4_dem_ctx_walk();
    (void)t;
L_230:
    r = 0x67c230;
    return cL4_dem_field5((long)&r);
L_fail:
    __asm__ volatile("brk #1" ::: "memory");   /* 0x3a0688 */
    return 0;
}

/* FUN_003a0690 @ 0x003a0690   (est. cL4_dem_kind_apply)
 * Ghidra: void FUN_003a0690(undefined8 p1, undefined8 p2, ulong *param_3, ...)
 * Void application of a demangle operation: resolves the kind and calls the
 * matching handler:
 *   0x201/0x202 -> cL4_dem_kind_apply_d; 0x200 -> cL4_dem_kind_apply_a;
 *   0x301 -> cL4_dem_vt_apply3; 0x300/0x305/0x203 -> cL4_dem_vt_apply4.
 * Unknown kinds fail closed.
 * Confidence: low
 */
void cL4_dem_kind_apply(unsigned long p1, unsigned long p2,
                        unsigned long *word, unsigned long p4,
                        unsigned long p5, unsigned long p6, unsigned long p7)
{
    cL4_w16_t rv;
    unsigned long *base, *meta;
    long t;
    unsigned long r;
    int k;

    rv = cL4_dem_resolve((unsigned long*)p7, (unsigned long*)p2);
    meta = (unsigned long*)rv.hi;
    base = (unsigned long*)rv.lo;
    if (word != 0) base = word;

    k = 0;
    if (*base < 0x800) k = (int)*base;

    if (k < 0x203) {
        if (k - 0x201U < 2) { r = 0x67c1c8; cL4_dem_kind_apply_d(&r, p1, (unsigned long)meta, p5, p6); return; }
        if (k != 0) {
            if (k == 0x200) { r = 0x67c0d0; cL4_dem_kind_apply_a(&r, p1, p4, p5, p6); return; }
            goto L_fail;
        }
    } else if (k < 0x301) {
        if (k != 0x203) {
            if ((k != 0x300) || (base != (unsigned long*)0x67b0a8) ||
                (0xfffffffffffff800 < **(long **)*meta - 0x800U)) goto L_fail;
            t = cL4_dem_ctx_walk();
            (void)t;
            base = (unsigned long*)0x67b0a8;
            goto L_230;
        }
    } else {
        if (k < 0x305) {
            if (k == 0x301) { unsigned long o[4]; r = 0x67c068; cL4_dem_vt_apply3(o, &r, p1, p4, p5); return; }
            __asm__ volatile("brk #1" ::: "memory");   /* 0x3a0968 */
        }
        if (0x305 < k) {
            if ((1 < k - 0x500U) && (k != 0x306)) {
                __asm__ volatile("brk #1" ::: "memory"); /* 0x3a0720 */
            }
            goto L_fail;
        }
    }
    t = cL4_dem_ctx_walk();
    (void)t;
L_230:
    r = 0x67c230;
    cL4_dem_vt_apply4(&r, p1, p4, p5, p6);
    return;
L_fail:
    __asm__ volatile("brk #1" ::: "memory");   /* 0x3a0960 */
}

/* FUN_003a0968 @ 0x003a0968   (est. cL4_dem_kind_char)
 * Ghidra: undefined8 FUN_003a0968(undefined8 param_1, undefined8 param_2)
 * Maps a demangle value kind code (from the resolved operand) to the ASCII
 * character used to encode it in a mangled name:
 *   0x200 -> 's'(0x73); 0x201/0x202 -> 'e'(0x65); 0x204 -> 'f'(0x66);
 *   0x301 -> 't'(0x74); 0x300 -> 99 ('c') after ctx walk; else 0.
 * Confidence: low
 */
unsigned long cL4_dem_kind_char(unsigned long op, unsigned long word)
{
    cL4_w16_t rv;
    unsigned long *base, *meta;
    long t;
    int k;

    rv = cL4_dem_resolve((unsigned long*)word, (unsigned long*)op);
    meta = (unsigned long*)rv.hi;
    base = (unsigned long*)rv.lo;
    unsigned long v = *base;
    k = 0;
    if (v < 0x800) k = (int)v;

    if (k < 0x300) {
        if (k < 0x201) {
            if (k != 0) { if (k != 0x200) return 0; return 0x73; }
        } else {
            if (k - 0x201U < 2) return 0x65;
            if (k != 0x203) {
                if (k != 0x204) return 0;
                return 0x66;
            }
        }
    } else {
        if (k < 0x305) {
            if (k != 0x300) {
                if (k != 0x301) return 0;
                return 0x74;
            }
            if (base == (unsigned long*)0x67b0a8) {
                if (**(long **)*meta - 0x800U < 0xfffffffffffff801) {
                    t = cL4_dem_ctx_walk();
                    (void)t;
                    return 99;
                }
                return 0;
            }
            return 0;
        }
        if (0x305 < k) {
            if (k == 0x306) return 0;
            if ((1 < k - 0x500U) && (k != 0x400)) return 0;
            __asm__ volatile("brk #1" ::: "memory");   /* 0x3a0a08 */
        }
    }
    t = cL4_dem_ctx_walk();
    (void)t;
    return 99;
}

/* FUN_003a1098 @ 0x003a1098   (est. cL4_dem_str_slot)
 * Ghidra: undefined1[16] FUN_003a1098(long param_1, ulong param_2, long *param_3, undefined8 *param_4)
 * Builds a string node from the descriptor table at param_1+8: validates
 * param_2 < the table's count, walks a sub-string table, and allocates a
 * copied string. Writes the result buffer into *param_3 and a method-table
 * slot into *param_4; returns {data, 0x100}.
 * Confidence: low
 */
cL4_w16_t cL4_dem_str_slot(long p, unsigned long idx, long *oa, unsigned long *ob)
{
    cL4_w16_t r;
    long base = *(long *)(p + 8);
    long tab, ln, prev, cur, sub, buf;
    unsigned long n;

    if ((long)idx < 0 || (n = *(unsigned long *)(base + 8), n < idx)) {
        __asm__ volatile("brk #1" ::: "memory");   /* 0x3a11c0 */
    }
    tab = *(long *)(base + 0x10);
    if (tab != 0) {
        ln = (long)cL4_swift_realloc2((void*)tab, 0x20);   /* thunk_FUN_00114c60(tab,0x20) */
        n = idx;
        while ((cur = ln, n != 0 && (cur = 0, ln != 0))) {
            n = n - 1;
            tab = ln + 1;
            ln = (long)cL4_swift_realloc2((void*)tab, 0x20);
        }
        if (ln != 0 && tab != cur) {
            prev = cur - tab;
            buf = (long)cL4_swift_alloc(prev + 1, 0x100004077774924);
            cL4_memcpy((void*)buf, (void*)tab, prev);
            *(unsigned char *)(buf + prev) = 0;
            *oa = buf;
            goto done;
        }
    }
    cL4_dem_str_empty((long*)oa);
done:
    *ob = 0;
    r.lo = *(unsigned long *)(base + (idx & 0xffffffff) * 0x10 + 0x18);
    r.hi = 0x100;
    return r;
}

/* FUN_003a11c0 @ 0x003a11c0   (est. cL4_dem_vt_apply3)
 * Ghidra: void FUN_003a11c0(undefined8 *param_1, long *param_2, ...)
 * Invokes the vtable method slots at param_2 (offset +0x10 and +0x18) to
 * build a 4-word result into param_1.
 * Confidence: low
 */
void cL4_dem_vt_apply3(unsigned long *out, long *vt, unsigned long a,
                       unsigned long b, unsigned long cc)
{
    long r0 = (**(long (**)(void))(*vt + 0x10))();
    long r1 = (**(long (**)(long*,unsigned long,unsigned long,unsigned long))(*vt + 0x18))
                    (vt, a, b, cc);
    long base = vt[2];
    unsigned long u = cL4_node_copy_r(r1, (void*)&out[0]);
    (**(void (**)(unsigned long, unsigned long))(*(long *)(r1 + -8) + 0x10))
        (u, base + r0);
    out[1] = out[3];
    out[0] = out[2];
    out[3] = r1;
    out[2] = out[4];
    (void)b; (void)cc;
}

/* FUN_003a12d8 @ 0x003a12d8   (est. cL4_dem_vt_call)
 * Ghidra: void FUN_003a12d8(long *param_1)
 * Calls the vtable method slot at *param_1 + 0x18 with no extra arguments.
 * Confidence: low
 */
void cL4_dem_vt_call(long *vt)
{
    (**(void (**)(void))(*vt + 0x18))();
}

/* FUN_003a1310 @ 0x003a1310   (est. cL4_dem_str_empty)
 * Ghidra: void FUN_003a1310(long *param_1)
 * Builds an empty Swift String into *out: formats the format-string
 * (s____s__file____s__line__u__column / "…") to learn its length, allocates,
 * formats again, and stores the pointer on success.
 * Confidence: low
 */
void cL4_dem_str_empty(long *out)
{
    long n;
    int r = cL4_swift_format(0, 0, "%s %s %u %u", "dummy", "", 0, 0);
    *out = 0;
    if (r >= 0) {
        long buf = (long)cL4_swift_alloc(r + 1, 0x100004077774924);
        if (buf != 0) {
            int r2 = cL4_swift_format((void*)buf, r + 1, "%s %s %u %u", "dummy", "", 0, 0);
            if (r2 < 0) cL4_free((void*)buf, 0);
            else *out = buf;
        }
    }
}

/* FUN_003a1518 @ 0x003a1518   (est. cL4_dem_field3)
 * Ghidra: undefined1[16] FUN_003a1518(long param_1, undefined8 p2, undefined8 *p3, undefined8 *p4)
 * Builds a string descriptor from param_1+8 via cL4_dem_str_build, writes
 * the {ptr} into *p3 and 0 into *p4; returns a 16-byte scratch value.
 * Confidence: low
 */
cL4_w16_t cL4_dem_field3(long p, unsigned long p2, unsigned long *oa, unsigned long *ob)
{
    cL4_w16_t r;
    unsigned long local_40[2];
    cL4_dem_str_build((long*)local_40, *(unsigned long *)(p + 8), 0);
    *oa = local_40[0];
    *ob = 0;
    r.lo = 0;
    r.hi = 0;
    return r;
}

/* FUN_003a156c @ 0x003a156c   (est. cL4_dem_vt_apply2)
 * Ghidra: void FUN_003a156c(undefined8 param_1, long *param_2, undefined8 param_3)
 * Calls the vtable method slots (+0x18 then +0x10) and routes the result
 * through cL4_dem_kind_apply_a into param_1.
 * Confidence: low
 */
void cL4_dem_vt_apply2(unsigned long *out, long *vt, unsigned long a)
{
    cL4_w16_t rv;
    long r0 = (**(long (**)(void))(*vt + 0x18))();
    long base = vt[2];
    long r1 = (**(long (**)(long*,unsigned long))(*vt + 0x10))(vt, a);
    cL4_dem_kind_apply_a((unsigned long*)out, base + r0, rv.hi & 0xffffff, 0, 0);
    (void)rv;
}

/* FUN_003a160c @ 0x003a160c   (est. cL4_dem_str_build)
 * Ghidra: void FUN_003a160c(long *param_1, undefined8 param_2, ulong param_3)
 * Builds a Swift String value (pointer + length + flags) into param_1 from
 * the descriptor at param_2, indexed by param_3. On an empty/invalid
 * descriptor emits the fallback "unknown" string. On a valid one it reads the
 * type's name/count, handling both the direct (inline) and allocated (via a
 * Swift runtime reflection hook FUN_003895e0) paths, and fills the standard
 * {ptr,length,flag words} triple.
 * Confidence: low
 */
void cL4_dem_str_build(long *out, unsigned long desc, unsigned long idx)
{
    int count, i;
    long base, name, len, src;
    unsigned long flags;
    unsigned int w;
    long node;

    /* stack canary check slot */
    long canary = -0x2c8502b44bfffed6;

    base = cL4_mr_block();
    if (base == 0 ||
        (count = *(int *)(base + 0x10), base = base + 0x10 + count, count == 0 || base == 0))
    {
        cL4_runtime_warn(desc, 1);
        cL4_dem_warn((unsigned long)0x5d668b);   /* "warning: the Swift runtime found..." */
        out[0] = (long)0x5d671d;                 /* "unknown" */
        out[1] = 7;
        out[2] = 0x67b148;
        *(unsigned short*)(out + 3) = 0;
        *(unsigned char*)((long)out + 0x1a) = 0;
        return;
    }
    base = base + (idx & 0xffffffff) * 0xc;
    count = *(int *)(base + 0x18);
    name = 0;
    if (count != 0) name = (long)count + base + 0x18;
    len = (name == 0) ? 0 : cL4_obj_retain_length((unsigned long)name);

    /* descriptor size / pointer */
    int *pp = (int *)(base + 0x14);
    count = *pp;
    if (count == 0 || (long)count == -(long)pp) {
        w = *(unsigned int *)(base + 0x10);
        out[0] = name;
        out[1] = len;
        out[2] = 0;
        *(unsigned char*)((long)out + 0x1a) = 0;
        *(unsigned short*)(out + 3) = (unsigned short)w & 1;
        return;
    }
    /* allocated path: build via the reflection hook */
    cL4_dem_skip_string((unsigned char*)((long)count + (long)pp));
    cL4_w16_t rr; rr.lo = rr.hi = 0;
    cL4_meta_build(&out[4], desc);
    src = 0x67c180;
    node = 0x67c138;
    cL4_meta_value(&out[8], 0, rr.lo, rr.hi, out[8], (void*)&node, (void*)&src);
    cL4_small_release_b((void*)&src);
    cL4_small_release_a((void*)&node);
    /* ... complete the result fields */
    out[0] = name;
    out[1] = len;
    out[2] = 0;
    *(unsigned char*)(out + 3) = *(unsigned char*)(base + 0x10) & 1;
    *(unsigned char*)((long)out + 0x19) = *(unsigned char*)(base + 0x10) >> 1 & 1;
    *(unsigned char*)((long)out + 0x1a) = 0;
    (void)canary;
    return;
}

/* FUN_003a18c8 @ 0x003a18c8   (est. cL4_dem_warn)
 * Ghidra: void FUN_003a18c8(undefined8 param_1)
 * Emits a runtime warning: if the report gate is non-negative, feeds the
 * message format through the reporter; if the report flag is set, prints the
 * message with the stack pointer.
 * Confidence: low
 */
void cL4_dem_warn(unsigned long msg)
{
    if (cL4_report_gate >= 0) {
        /* FUN_003d3dd8(&DAT_006c0b18, &DAT_003a1acc): report format record. */
        cL4_report((unsigned long*)&cL4_report_gate, (unsigned long*)0x3a1acc);
    }
    if (cL4_report_flag == 0x01) {
        /* FUN_004b9e2c(0, msg, &stack0x00000000) */
        cL4_diag_c(0, msg, (void*)0);
    }
}

/* FUN_003a1958 @ 0x003a1958   (est. cL4_dem_alloc_node_a)
 * Ghidra: void FUN_003a1958(long param_1)
 * Allocates a 16-byte node record with header 0x67c138 and the field from
 * param_1+8.
 * Confidence: low
 */
void cL4_dem_alloc_node_a(long p)
{
    unsigned long *n = (unsigned long *)cL4_swift_alloc(0x10, 0xa1c40bd48d6d6);
    unsigned long v = *(unsigned long *)(p + 8);
    n[0] = 0x67c138;
    n[1] = v;
}

/* FUN_003a1a18 @ 0x003a1a18   (est. cL4_dem_alloc_node_b)
 * Ghidra: void FUN_003a1a18(long param_1)
 * Same as cL4_dem_alloc_node_a but header 0x67c180.
 * Confidence: low
 */
void cL4_dem_alloc_node_b(long p)
{
    unsigned long *n = (unsigned long *)cL4_swift_alloc(0x10, 0xa1c40bd48d6d6);
    unsigned long v = *(unsigned long *)(p + 8);
    n[0] = 0x67c180;
    n[1] = v;
}

/* FUN_003a1ae4 @ 0x003a1ae4   (est. cL4_dem_teardown)
 * Ghidra: void FUN_003a1ae4(long param_1)
 * Releases the object at param_1+8 and stores the "is-empty" boolean.
 * Confidence: low
 */
void cL4_dem_teardown(long p)
{
    cL4_small_release_x(*(unsigned long *)(p + 8));
}

/* FUN_003a1b0c @ 0x003a1b0c   (est. cL4_dem_kind_apply_a)
 * Ghidra: void FUN_003a1b0c(undefined8 *param_1, long *param_2, long *param_3, ulong param_4)
 * Copies a demangle value: dispatches on the source node's kind tag. For a
 * reference-bearing kind it copies the payload words; otherwise it emits a
 * "Value with unrecognized reference" diagnostic. Writes a 4-word result.
 * Confidence: low
 */
void cL4_dem_kind_apply_a(unsigned long *out, unsigned long p2,
                          unsigned long p4, unsigned long p5, unsigned long p6)
{
    long *node = (long*)p2;
    long *dst = (long*)cL4_node_copy_r((long)p2, (void*)&out[0]);
    unsigned int u;
    unsigned long l;
    (void)p5; (void)p6;

    if (*node == 0x304) {
        unsigned long v = *(unsigned long *)node[1];
        int k = 0;
        if (v < 0x800) k = (int)v;
        if ((2 < k - 0x301U) && (2 < k - 0x200U)) goto check_flags;
        /* 0x301-0x303 or 0x200-0x202: indirect through node[-1]+0x10 */
        void (*fn)(long,long*,long*) = *(void (**)(long,long*,long*))(node[-1] + 0x10);
        fn((long)dst, node + 1, node);
        goto done;
    }
check_flags:
    u = (unsigned int)(p4 >> 0x10) & 0xff;
    if (u == 1 || (p4 & 0xff0000) == 0) {
        if ((p4 & 0xff0000) == 0) {
            void (*fn)(long,long*,long*) = *(void (**)(long,long*,long*))(node[-1] + 0x10);
            fn((long)dst, node + 1, node);
            goto done;
        }
        if (u != 1) goto diag;
        l = cL4_node_copy(node);
        *dst = l;
        l = *(long *)(node[-1] + 0x40);
        cL4_memcpy_v((unsigned long)(dst + 1), (unsigned long)(node + 1), l - 8);
    } else {
        if (u != 2) {
            if (u != 4) goto diag;
            void (*fn)(long,long*,long*) = *(void (**)(long,long*,long*))(node[-1] + 0x10);
            fn((long)dst, node + 1, node);
            goto done;
        }
        l = *node;
        cL4_node_retain(l);
        *dst = l;
        l = *(long *)(node[-1] + 0x40);
        cL4_memcpy_v((unsigned long)(dst + 1), (unsigned long)(node + 1), l - 8);
    }
    goto done;
diag:
    cL4_diag_d(0, "Value with unrecognized reference");   /* 005d6725 */
    cL4_node_release((long)node);
    node = (long*)0x67b148;
done:
    out[1] = out[3];
    out[0] = out[2];
    out[3] = (unsigned long)node;
    out[2] = out[4];
}

/* FUN_003a1cbc @ 0x003a1cbc   (est. cL4_dem_has_child)
 * Ghidra: bool FUN_003a1cbc(long param_1)
 * True when the node at param_1 has a usable child: the descriptor is valid
 * and the child field at +0x10 is non-null, resolved through the type's name
 * accessor.
 * Confidence: low
 */
int cL4_dem_has_child(long p)
{
    int r;
    long d = *(long *)(*(long *)(p + 8) + 8);
    long d2 = (d == 0) ? 0 : d;
    if (*(int *)(d2 + 0x10) == 0 || (long)*(int *)(d2 + 0x10) == -0x10 - d2) {
        r = 0;
    } else {
        r = 0;
        if (*(long *)(p + 0x10) != 0) {
            unsigned long u = (**(unsigned long (**)(void))(*(long *)(*(long *)(p + 8) + -8) + 0x58))();
            cL4_dem_str_build((long*)&r, *(unsigned long *)(p + 8), u);
            r = (long)*(long*)&r != 0;   /* local_30 != 0 */
        }
    }
    return r;
}

/* FUN_003a1dac @ 0x003a1dac   (est. cL4_dem_kind_apply_d)
 * Ghidra: void FUN_003a1dac(undefined8 *param_1, long param_2, undefined8 param_3, ...)
 * Named-children variant: reads the type's name accessor, builds a string
 * descriptor, copies the node, invokes the vtable slots, and records the
 * resulting pointer. Writes a 4-word result.
 * Confidence: low
 */
void cL4_dem_kind_apply_d(unsigned long *vt, unsigned long p1,
                          unsigned long meta, unsigned long p5, unsigned long p6)
{
    unsigned long local_80[2];
    unsigned long local_70;
    unsigned char local_68;
    long src = (long)vt;
    (void)p1; (void)meta; (void)p5; (void)p6;

    unsigned long u = (**(unsigned long (**)(unsigned long))(*(long *)(*(long *)(src + 8) + -8) + 0x58))(*(unsigned long *)(src + 0x10));
    cL4_dem_str_build((long*)local_80, *(unsigned long *)(src + 8), u);
    u = cL4_node_copy_r(*(unsigned long *)(src + 8), (void*)local_80);
    (**(void (**)(unsigned long, unsigned long))(*(long *)(*(long *)(src + 8) + -8) + 0x10))(u, *(unsigned long *)(src + 0x10));
    long lVar1 = 0x67b0a8;
    if ((local_68 & 1) == 0) lVar1 = (long)local_70;
    cL4_w16_t rv = cL4_small_copy(lVar1);
    unsigned long *puVar3 = (unsigned long*)rv.hi;
    (**(void (**)(unsigned long))(*(long *)(*(long *)(src + 8) + -8) + 0x60))(u);
    (**(void (**)(unsigned long, unsigned long, long))(*(long *)(lVar1 + -8) + 0x20))((unsigned long)puVar3, u, lVar1);
    cL4_node_release(*(unsigned long *)(src + 8));
    *(unsigned long **)(src + 0x10) = puVar3;
    if ((local_68 & 1) != 0) {
        *(unsigned long *)(src + 0x10) = cL4_node_word(*puVar3);
    }
}

/* FUN_003a1f60 @ 0x003a1f60   (est. cL4_dem_field_d)
 * Ghidra: undefined8 FUN_003a1f60(long param_1)
 * Returns the descriptor word at param_1+8's +8 record's +0x14 (or 0).
 * Confidence: low
 */
unsigned long cL4_dem_field_d(long p)
{
    unsigned long local_40[4];
    long d = *(long *)(*(long *)(p + 8) + 8);
    long d2 = (d == 0) ? 0 : d;
    if (*(int *)(d2 + 0x10) == 0 || (long)*(int *)(d2 + 0x10) == -0x10 - d2) {
        local_40[0] = 0;
    } else {
        unsigned long u = (**(unsigned long (**)(unsigned long))(*(long *)(*(long *)(p + 8) + -8) + 0x58))(*(unsigned long *)(p + 0x10));
        cL4_dem_str_build((long*)local_40, *(unsigned long *)(p + 8), u);
    }
    return local_40[0];
}

/* FUN_003a20cc @ 0x003a20cc   (est. cL4_dem_index_get)
 * Ghidra: undefined8 FUN_003a20cc(long param_1, ulong param_2)
 * Indexed element get from the descriptor at param_1+8: bounds-checks
 * param_2, then reads element param_2 from the record (+0x28-scaled).
 * Out of range -> fail-closed trap.
 * Confidence: low
 */
long cL4_dem_index_get(long p, unsigned long idx)
{
    long rec = *(long *)(p + 8);
    if (((long)idx >= 0 && idx <= *(unsigned int *)(*(long *)(rec + 0x28) + 0x24)) &&
        cL4_index_ok(rec)) {
        long d = *(long *)(rec + 0x28);
        long d2 = (d == 0) ? 0 : d;
        unsigned int u;
        if ((*(unsigned char *)(d2 + 3) >> 5 & 1) == 0) {
            u = *(unsigned int *)(d2 + 0x28);
        } else {
            cL4_node_field_get();
            u = *(int *)(d2 + 0x28) + (int)(0 >> 3);
        }
        return *(long *)(rec + (unsigned long)u * 8 + idx * 8);
    }
    __asm__ volatile("brk #1" ::: "memory");   /* 0x3a21a0 */
    return 0;
}

/* FUN_003a21a0 @ 0x003a21a0   (est. cL4_dem_field3b)
 * Ghidra: undefined1[16] FUN_003a21a0(long param_1, undefined8 p2, undefined8 *p3, undefined8 *p4)
 * Companion of cL4_dem_field3 (builds a string descriptor into *p3).
 * Confidence: low
 */
cL4_w16_t cL4_dem_field3b(long p, unsigned long p2, unsigned long *oa, unsigned long *ob)
{
    cL4_w16_t r;
    unsigned long local_40[2];
    cL4_dem_str_build((long*)local_40, *(unsigned long *)(p + 8), 0);
    *oa = local_40[0];
    *ob = 0;
    r.lo = 0;
    r.hi = 0;
    return r;
}

/* FUN_003a21f4 @ 0x003a21f4   (est. cL4_dem_vt_apply4)
 * Ghidra: void FUN_003a21f4(undefined8 param_1, long *param_2, undefined8 param_3)
 * Calls the vtable method slots (+0x18 then +0x10) and routes the result
 * through cL4_dem_kind_apply_a.
 * Confidence: low
 */
void cL4_dem_vt_apply4(long *vt, unsigned long p1, unsigned long p4,
                       unsigned long p5, unsigned long p6)
{
    long r0 = (**(long (**)(void))(*vt + 0x18))();
    long base = vt[2];
    long r1 = (**(long (**)(long*,unsigned long))(*vt + 0x10))(vt, p1);
    cL4_dem_kind_apply_a((unsigned long*)0, (unsigned long)(base + r1), p4, p5, p6);
}

/* FUN_003a2290 @ 0x003a2290   (est. cL4_dem_sizeof)
 * Ghidra: long FUN_003a2290(long *param_1)
 * Computes the byte size of a node: if the descriptor has extra layout,
 * recurse through the extra-node and add the vtable size; else return the
 * vtable size directly.
 * Confidence: low
 */
long cL4_dem_sizeof(long *vt)
{
    long extra, sz;
    unsigned long stub[24];
    if (cL4_dem_has_extra((long)vt) != 0) {
        cL4_dem_build_extra(stub, (long)vt);
        extra = cL4_dem_sizeof((long*)stub);
        sz = (**(long (**)(long*))(*vt + 8))(vt);
        return sz + extra;
    }
    return (**(long (**)(long*))(*vt + 8))(vt);
}

/* FUN_003a232c @ 0x003a232c   (est. cL4_dem_copy)
 * Ghidra: void FUN_003a232c(long *param_1, long param_2)
 * Byte-copies `param_2` bytes into the node buffer, splitting into the extra
 * node when the descriptor carries one. Calls vtable slot +0x10.
 * Confidence: low
 */
void cL4_dem_copy(long *vt, long n)
{
    long extra, diff;
    unsigned long stub[24];
    if (cL4_dem_has_extra((long)vt) != 0) {
        cL4_dem_build_extra(stub, (long)vt);
        extra = cL4_dem_sizeof((long*)stub);
        diff = n - extra;
        if (n < extra) {
            cL4_dem_copy((long*)stub, n);
            return;
        }
    } else {
        diff = n;
    }
    (**(void (**)(long*,long))(*vt + 0x10))(vt, diff);
}

/* FUN_003a23b4 @ 0x003a23b4   (est. cL4_dem_copy2)
 * Ghidra: void FUN_003a23b4(long *param_1, long param_2, undefined8 param_3, undefined8 param_4)
 * Variant of cL4_dem_copy that also passes two extra words to the vtable
 * slot +0x18.
 * Confidence: low
 */
cL4_w16_t cL4_dem_copy2(unsigned long *dst, unsigned long src, unsigned long x,
                        unsigned long *a, unsigned long *b)
{
    long *vt = (long*)src;
    long extra, diff;
    unsigned long stub[24];
    cL4_w16_t r; r.lo = r.hi = 0;
    if (cL4_dem_has_extra((long)vt) != 0) {
        cL4_dem_build_extra(stub, (long)vt);
        extra = cL4_dem_sizeof((long*)stub);
        diff = (long)x - extra;
        if ((long)x < extra) {
            cL4_dem_copy2(dst, src, x, a, b);
            return r;
        }
    } else {
        diff = (long)x;
    }
    (**(void (**)(long*,long,unsigned long,unsigned long))(*vt + 0x18))(vt, diff, (unsigned long)a, (unsigned long)b);
    return r;
}

/* FUN_003a2468 @ 0x003a2468   (est. cL4_dem_has_extra)
 * Ghidra: bool FUN_003a2468(long param_1)
 * True when the node at param_1 has an extra/layout record: the descriptor
 * field is valid and its +8 child is non-null.
 * Confidence: low
 */
int cL4_dem_has_extra(long p)
{
    long d = *(long *)(*(long *)(p + 8) + 0x28);
    int n = *(int *)(d + 0x14);
    if ((n != 0 && (long)n != -0x14 - d) &&
        (d = *(long *)(*(long *)(p + 8) + 8), d != 0)) {
        return d != 0;
    }
    return 0;
}

/* FUN_003a24d0 @ 0x003a24d0   (est. cL4_dem_build_extra)
 * Ghidra: void FUN_003a24d0(undefined8 *param_1, long param_2)
 * Builds the extra-node descriptor into *out from the node at param_2; traps
 * if the node has no extra record.
 * Confidence: low
 */
void cL4_dem_build_extra(unsigned long *out, long p)
{
    long d = *(long *)(*(long *)(p + 8) + 0x28);
    int n = *(int *)(d + 0x14);
    if (((n != 0 && (long)n != -0x14 - d) &&
         (d = *(long *)(*(long *)(p + 8) + 8), d != 0)) && (d != 0)) {
        out[0] = 0x67c230;
        out[1] = (unsigned long)d;
        out[2] = 0;
        return;
    }
    __asm__ volatile("brk #1" ::: "memory");   /* 0x3a2554 */
}

/* FUN_003a2554 @ 0x003a2554   (est. cL4_dem_thread_var)
 * Ghidra: void FUN_003a2554(void)
 * Indirect call through the thread-local variable pointer.
 * Confidence: low
 */
void cL4_dem_thread_var(void)
{
    /* __thread_vars: per-thread variable block; call its code ptr */
    __builtin_trap();
}

/* FUN_003a2578 @ 0x003a2578   (est. cL4_dem_lookup_word)
 * Ghidra: undefined8 FUN_003a2578(undefined8 param_1)
 * Looks up a word through the runtime lookup helper FUN_00369b18.
 * Confidence: low
 */
unsigned long cL4_dem_lookup_word(unsigned long x)
{
    unsigned long *p = (unsigned long *)cL4_crash_lookup(0, x);
    return *p;
}

/* FUN_003a26e8 @ 0x003a26e8   (est. cL4_dem_validate)
 * Ghidra: undefined8 FUN_003a26e8(long param_1)
 * Validates a demangle token (param_1): returns 0 when the value is a
 * small/empty token, else emits a "bad mangled name" diagnostic (with the
 * code bytes) and returns 1. Frees the diagnostic buffer.
 * Confidence: low
 */
unsigned long cL4_dem_validate(long p)
{
    unsigned long local_80[8], *buf;
    int r, i;
    if (p == 0) return 0;
    unsigned long v = *(unsigned long *)(p + 8);
    if ((long)v < 0) {
        if ((int)v == -1) return 0;
        v = *(unsigned long *)(v * 8 + 0x10);
        if (v >> 0x21 == 0 && (v & 0x100000000) == 0) return 0;
    } else if (v >> 0x20 == 0) {
        return 0;
    }
    cL4_dem_badstr((long*)&local_80[0]);
    cL4_diag_a(2);
    r = cL4_crash_check();
    if (r != 0) {
        /* embed the crashing instruction bytes */
        local_80[1] = 0x710196df94000340;
        local_80[2] = 0x52808001910023e0;
        local_80[3] = 0x71019adf54000240;
        local_80[4] = 0x71019edf540005a0;
        local_80[5] = 0x940001c937000048;
        local_80[6] = 0x39400288540007c1;
        local_80[7] = 0x540000607101b11f;
        cL4_crash_emit(1, (long)&local_80[0], (void*)&local_80[1]);
    }
    buf = (unsigned long*)local_80[0];
    cL4_diag_b(1, (unsigned long)buf);
    cL4_free((void*)buf, 0);
    return 1;
}

/* FUN_003a27f0 @ 0x003a27f0   (est. cL4_dem_badstr)
 * Ghidra: void FUN_003a27f0(long *param_1)
 * Builds the "…: file …, line …, column …" diagnostic string into *out.
 * Confidence: low
 */
void cL4_dem_badstr(long *out)
{
    int r = cL4_swift_format(0, 0, "%s %s %s", "", "", "");
    *out = 0;
    if (r >= 0) {
        long buf = (long)cL4_swift_alloc(r + 1, 0x100004077774924);
        if (buf != 0) {
            int r2 = cL4_swift_format((void*)buf, r + 1, "%s %s %s", "", "", "");
            if (r2 < 0) cL4_free((void*)buf, 0);
            else *out = buf;
        }
    }
}

/* FUN_003a2898 @ 0x003a2898   (est. cL4_dem_pair)
 * Ghidra: undefined1[16] FUN_003a2898(long param_1)
 * Returns a {count, length} pair from the record at param_1: count from
 * +0x14, length = +0x18 - count.
 * Confidence: medium
 */
cL4_w16_t cL4_dem_pair(long p)
{
    cL4_w16_t r;
    unsigned long cnt = (unsigned long)*(unsigned int *)(p + 0x14);
    r.lo = cnt;
    r.hi = *(unsigned int *)(p + 0x18) - cnt;
    return r;
}

/* FUN_003a28a8 @ 0x003a28a8   (est. cL4_dem_noop)
 * Ghidra: void FUN_003a28a8(void)
 * No-op.
 * Confidence: high
 */
void cL4_dem_noop(void) { return; }

/* FUN_003a28ac @ 0x003a28ac   (est. cL4_dem_format)
 * Ghidra: void FUN_003a28ac(undefined8 param_1, undefined8 param_2, undefined8 param_3, undefined8 param_4)
 * Formats a Swift string with capacity 0x400 from the format string param_4.
 * Confidence: low
 */
void cL4_dem_format(unsigned long p1, unsigned long p2, unsigned long p3,
                    unsigned long p4)
{
    cL4_swift_format((void*)p1, 0x400, (const char*)p4);
    (void)p2; (void)p3;
}

/* FUN_003a28e8 @ 0x003a28e8   (est. cL4_dem_capacity)
 * Ghidra: ulong FUN_003a28e8(ulong param_1, long param_2)
 * Computes a small-vector capacity: given a current length param_1 and a
 * requested count param_2, returns max(param_1, 2*param_2+1) capped at
 * 0xffffffff. Fails (noreturn) if param_1 has a nonzero high word (overflow)
 * or param_2 is -1 (unable to grow).
 * Confidence: medium
 */
unsigned long cL4_dem_capacity(unsigned long cur, long req)
{
    const char *msg;
    if (cur >> 0x20 == 0) {
        if (req != -1) {
            if (cur < (unsigned long)(req << 1 | 1U)) cur = (unsigned long)(req * 2 + 1);
            if (0xfffffffe < cur) cur = 0xffffffff;
            return cur;
        }
        msg = "SmallVector capacity unable to grow";   /* 005d6896 */
    } else {
        msg = "SmallVector capacity overflow during growth";  /* 005d6866 */
    }
    cL4_fatal_str(msg, 1);
}

/* FUN_003a294c @ 0x003a294c   (est. cL4_dem_reserve1)
 * Ghidra: void FUN_003a294c(long *param_1, long param_2, undefined8 param_3, long param_4)
 * Ensures the small vector at param_1 has room for the given element count
 * (param_4-scaled); allocates or reallocates the backing store, copying the
 * existing elements. Updates the capacity field at +0xc.
 * Confidence: medium
 */
void cL4_dem_reserve1(long *vec, long buf, unsigned long n, long sz)
{
    long cap = cL4_dem_capacity(n, *(unsigned int *)((long)vec + 0xc));
    long bytes = cap * sz;
    long dst;
    if (*vec == buf) {
        dst = (long)cL4_swift_alloc(bytes, 0x8c556d9c);
        if (dst == 0) {
            if (bytes != 0) goto fail;
            bytes = 1;
            dst = (long)cL4_swift_alloc(1, 0x8c556d9c);
            if (dst == 0) goto fail;
        }
        cL4_memcpy((void*)dst, (void*)*vec, sz * (unsigned long)*(unsigned int *)(vec + 1));
    } else {
        dst = (long)cL4_swift_realloc((void*)*vec, bytes, 0x48319b8);
        if ((dst == 0) && ((bytes != 0 ||
            (dst = (long)cL4_swift_alloc(1, 0x8c556d9c), dst == 0)))) goto fail;
    }
    *vec = dst;
    *(int *)((long)vec + 0xc) = (int)cap;
    return;
fail:
    cL4_fatal_str("Allocation failed", 1);   /* 005d6854 */
}

/* FUN_003a2a38 @ 0x003a2a38   (est. cL4_dem_reserve2)
 * Ghidra: void FUN_003a2a38(long *param_1, long param_2, ulong param_3, long param_4)
 * Variant of cL4_dem_reserve1 using the +0x10 capacity field.
 * Confidence: medium
 */
void cL4_dem_reserve2(long *vec, long buf, unsigned long n, long sz)
{
    long cap = vec[2];
    long dst, bytes;
    const char *msg;
    if (cap == -1) {
        msg = "SmallVector capacity unable to grow";   /* 005d6896 */
        goto fail;
    }
    if (n < (unsigned long)(cap << 1 | 1U)) n = (unsigned long)(cap * 2 + 1);
    bytes = n * sz;
    if (*vec == buf) {
        dst = (long)cL4_swift_alloc(bytes, 0x8c556d9c);
        if (dst != 0) {
            cL4_memcpy((void*)dst, (void*)*vec, vec[1] * sz);
            goto set;
        }
        if (bytes == 0) { bytes = 1; dst = (long)cL4_swift_alloc(1, 0x8c556d9c); if (dst != 0) { cL4_memcpy((void*)dst,(void*)*vec,0); goto set; } }
    } else {
        dst = (long)cL4_swift_realloc((void*)*vec, bytes, 0x48319b8);
        if ((dst != 0) || (bytes == 0 && (dst = (long)cL4_swift_alloc(1, 0x8c556d9c), dst != 0))) goto set;
    }
    msg = "Allocation failed";   /* 005d6854 */
fail:
    cL4_fatal_str(msg, 1);
set:
    *vec = dst;
    vec[2] = (long)n;
}

/* FUN_003a2b38 @ 0x003a2b38   (est. cL4_dem_bulk_copy)
 * Ghidra: void FUN_003a2b38(long param_1, long param_2)
 * Bulk byte-copies a buffer range (param_1..param_1+param_2) using the
 * SIMD/vector copy helpers, handling >64-byte regions in 64-byte chunks.
 * Confidence: low
 */
void cL4_dem_bulk_copy(long dst, long n)
{
    unsigned long len = n;
    unsigned char stub[56];
    long end = dst + n;
    if (len > 0x40) {
        unsigned long chunks = len & 0xffffffffffffffc0;
        cL4_arr_copy_begin(stub, dst, 0xf9000a63a9000a61);
        while ((chunks -= 0x40) != 0) {
            dst += 0x40;
            cL4_arr_copy_loop(stub, dst);
        }
        if ((len & 0x3f) != 0) cL4_arr_copy_loop(stub, end - 0x40);
        cL4_arr_copy_finish(stub, len);
        return;
    }
    cL4_arr_copy_small(dst, len);
    (void)end;
}

/* FUN_003a2c18 @ 0x003a2c18   (est. cL4_dem_alloc_storage)
 * Ghidra: undefined8 * FUN_003a2c18(undefined8 *param_1)
 * Allocates and zero-initializes a 0x240-byte demangle storage block (header
 * 0x67c398, field count 0x960) and stores it into *param_1.
 * Confidence: low
 */
unsigned long *cL4_dem_alloc_storage(unsigned long *out)
{
    unsigned long *p = (unsigned long *)cL4_swift_alloc(0x240, 0x10f1c40caa97c64);
    p[1] = 0; p[2] = 0; p[3] = 0; p[4] = 0x960; p[5] = 0;
    *(unsigned char*)(p + 6) = 0;
    p[0] = 0x67c398;
    p[0x47] = 0; p[8] = 0; p[9] = 0; p[7] = 0;
    *(unsigned short*)(p + 10) = 0;
    for (int i = 0xb; i < 0x45; i++) p[i] = 0;
    *(unsigned int *)(p + 0x43) = 0;
    *out = (unsigned long)p;
    return out;
}

/* FUN_003a2cf0 @ 0x003a2cf0   (est. cL4_dem_free_storage)
 * Ghidra: long * FUN_003a2cf0(long *param_1)
 * Releases the storage record if present (vtable slot +8).
 * Confidence: low
 */
long *cL4_dem_free_storage(long *p)
{
    if ((long *)*p != 0) {
        (**(void (**)(void))(*(long *)*p + 8))();
    }
    return p;
}

/* FUN_003a2d38 @ 0x003a2d38   (est. cL4_dem_call_parse)
 * Ghidra: undefined8 FUN_003a2d38(undefined8 *param_1, undefined8 param_2, undefined8 param_3)
 * Calls the demangler parse entry on the message registers and releases the
 * result.
 * Confidence: low
 */
unsigned long cL4_dem_call_parse(unsigned long *p, unsigned long a, unsigned long b)
{
    unsigned long r;
    unsigned char stub[24];
    long canary = -0x2c8502b44bfffed6;
    r = cL4_dem_parse_node((dem_state_t*)*p, (short*)a, b, (unsigned long)(long*)stub);
    cL4_small_release((void*)stub);
    if (canary != -0x2c8502b44bfffed6) cL4_swift_fatal();
    return r;
}

/* FUN_003a2da8 @ 0x003a2da8   (est. cL4_dem_parse_to_string)
 * Ghidra: void FUN_003a2da8(undefined8 *param_1, undefined8 *param_2, undefined8 param_3, undefined8 param_4, undefined8 param_5)
 * Parses a mangled string into a demangle node and converts it to a Swift
 * String: on parse failure copies the (empty) source; on success formats the
 * node and stores the {string, flags} result.
 * Confidence: low
 */
void cL4_dem_parse_to_string(unsigned long *out, unsigned long *src,
                             unsigned long a, unsigned long b, unsigned long extra)
{
    unsigned long local_68, uStack_60, local_58;
    unsigned long uStack_50;
    unsigned char local_48[8];
    char bStack_41;
    unsigned long local_40, local_38;
    long canary = -0x2c8502b44bfffed6;

    local_40 = 0;
    local_68 = a;
    uStack_60 = b;
    long r = cL4_dem_parse_node((dem_state_t*)*src, (short*)a, b, (unsigned long)&local_58);
    cL4_small_release(&local_58);
    if (r == 0) {
        cL4_string_copy((long*)out, &local_68);
    } else {
        cL4_node_to_string(&local_58, r, extra);
        unsigned long u = uStack_50;
        if ((signed char)bStack_41 < 0) u = (unsigned long)(unsigned char)bStack_41;
        if (u == 0) {
            cL4_string_copy((long*)out, &local_68);
            if ((signed char)bStack_41 < 0) {
                cL4_free((void*)local_58, (*(unsigned long*)local_48 & 0x7fffffffffffffff));
            }
        } else {
            out[1] = uStack_50;
            out[0] = local_58;
            out[2] = *(unsigned long*)local_48;
        }
    }
    if (canary != -0x2c8502b44bfffed6) cL4_swift_fatal();
    (void)local_38; (void)local_40;
}

/* FUN_003a2e9c @ 0x003a2e9c   (est. cL4_dem_alloc_and_parse)
 * Ghidra: void FUN_003a2e9c(undefined8 param_1, undefined8 param_2, undefined8 param_3, undefined8 param_4)
 * Allocates demangle storage, parses param_2/param_3 into a string, then
 * releases the storage.
 * Confidence: low
 */
void cL4_dem_alloc_and_parse(unsigned long p1, unsigned long p2,
                             unsigned long p3, unsigned long p4)
{
    long *st = (long*)cL4_swift_alloc(0x240, 0x10f1c40caa97c64);
    st[1] = 0; st[2] = 0; st[3] = 0; st[4] = 0x960; st[5] = 0;
    *(unsigned char*)(st + 6) = 0;
    st[0] = 0x67c398;
    st[0x47] = 0; st[8] = 0; st[9] = 0; st[7] = 0;
    *(unsigned short*)(st + 10) = 0;
    for (int i = 0xb; i < 0x45; i++) st[i] = 0;
    *(unsigned int *)(st + 0x43) = 0;
    long *lp = st;
    cL4_dem_parse_to_string((unsigned long*)p1, (unsigned long*)&lp, p2, p3, p4);
    (**(void (**)(long))(*st + 8))((long)st);
}

/* FUN_003a2fd4 @ 0x003a2fd4   (est. cL4_dem_is_qualified1)
 * Ghidra: undefined8 FUN_003a2fd4(undefined8 param_1, undefined8 param_2, undefined8 param_3)
 * True when the node kind (from param_3 metadata) belongs to a set of
 * qualified/reflection kinds (bitmask membership test).
 * Confidence: low
 */
unsigned long cL4_dem_is_qualified1(unsigned long p1, unsigned long p2,
                                    unsigned long p3)
{
    unsigned char stub[24];
    unsigned long token;
    cL4_runtime_meta(stub, p3);
    token = cL4_token_format(0, "assertion failed for Node %u");
    return cL4_dem_is_qualified_kind((unsigned int)token);
}

/* FUN_003a3040 @ 0x003a3040   (est. cL4_dem_is_qualified2)
 * Ghidra: undefined8 FUN_003a3040(uint param_1)
 * Bitmask membership test: true when the value kind (param_1) is one of a
 * specific set of kinds (the "is a qualified name" predicate). Uses two
 * 64-bit bitmasks over the low/high kind ranges.
 * Confidence: medium
 */
unsigned long cL4_dem_is_qualified_kind(unsigned int k)
{
    unsigned long r = 1;
    unsigned long mask;
    if ((int)k < 0x96) {
        if ((k - 0x48 < 0x3e) &&
            ((1UL << ((unsigned long)(k - 0x48) & 0x3f) & 0x2c04000650000043UL) != 0)) return r;
        if (0x3f < k) return 0;
        mask = 0x8030000542200003;
    } else {
        if ((k - 0x96 < 0x2b) &&
            ((1UL << ((unsigned long)(k - 0x96) & 0x3f) & 0x7c03803f801UL) != 0)) return r;
        if ((k - 0xd7 < 0x38) &&
            ((1UL << ((unsigned long)(k - 0xd7) & 0x3f) & 0x930000c0039003UL) != 0)) return r;
        k = k - 0x144;
        if (0x35 < k) return 0;
        mask = 0x30000000000801;
    }
    if ((1UL << ((unsigned long)k & 0x3f) & mask) != 0) return r;
    return 0;
}

/* FUN_003a3124 @ 0x003a3124   (est. cL4_dem_is_kind_set)
 * Ghidra: undefined8 FUN_003a3124(int param_1)
 * Another bitmask membership test over a narrower set of kind codes.
 * Confidence: medium
 */
unsigned long cL4_dem_is_kind_set(int k)
{
    unsigned long r = 1;
    unsigned int u;
    unsigned long mask;
    if (k < 0x99) {
        u = (unsigned int)(k - 0x37);
        if (0x2b < u) return 0;
        mask = 0xdc6010000ef;
    } else {
        if ((k - 0x14eU < 0x29) &&
            ((1UL << ((unsigned long)(k - 0x14eU) & 0x3f) & 0x18000206e01UL) != 0)) return r;
        if ((k - 0x99U < 0x1d) && ((1 << (k - 0x99U & 0x1f) & 0x18220001) != 0)) return r;
        u = (unsigned int)(k - 0x10d);
        if (0x21 < u) return 0;
        mask = 0x300400001;
    }
    if ((1UL << ((unsigned long)u & 0x3f) & mask) == 0) return 0;
    return r;
}

/* FUN_003a31d8 @ 0x003a31d8   (est. cL4_dem_skip_string)
 * Ghidra: void FUN_003a31d8(byte *param_1)
 * Skips past a length-prefixed identifier string (UTF-8 multibyte handling:
 * a 0x18-prefixed byte counts 8, else 0/4), stopping at the terminator.
 * Confidence: medium
 */
void cL4_dem_skip_string(unsigned char *s)
{
    unsigned char b;
    long step1, step2;
    if (s == 0) return;
    b = *s;
    while (b != 0) {
        step1 = 8;
        if ((b & 0xf8) != 0x18) step1 = 0;
        step2 = 4;
        if (0x17 < b) step2 = step1;
        s = s + step2 + 1;
        b = *s;
    }
}

/* FUN_003a3224 @ 0x003a3224   (est. cL4_dem_lookup_tag)
 * Ghidra: ulong FUN_003a3224(undefined8 param_1, ulong param_2)
 * Searches a runtime tag table (0x67c2e8, 8 entries of 2 words) for an
 * entry whose length matches param_2 and whose string (param_1) compares
 * equal; returns the matching length or 0.
 * Confidence: medium
 */
unsigned long cL4_dem_lookup_tag(unsigned long str, unsigned long len)
{
    if (len != 0) {
        unsigned long *p = (unsigned long*)0x67c2e8;
        long i = 0x80;
        do {
            unsigned long v = *p;
            if (v <= len) {
                if (v == 0) return 0;
                int r = cL4_str_compare(str, p[-1], v);
                if (r == 0) return v;
            }
            p += 2;
            i -= 0x10;
        } while (i != 0);
    }
    return 0;
}

/* FUN_003a32a0 @ 0x003a32a0   (est. cL4_dem_pop_subst)
 * Ghidra: undefined8 FUN_003a32a0(long param_1, undefined8 param_2, undefined8 param_3, undefined8 param_4)
 * Pops and returns the substitution at the top of the state's node stack,
 * validating the stack layout; returns 0 on an empty/invalid stack.
 * Confidence: low
 */
unsigned long cL4_dem_pop_subst(long p, unsigned long a, unsigned long b,
                                unsigned long c)
{
    unsigned char stub_c0[32], stub_a0[104];
    long canary = -0x2c8502b44bfffed6;
    cL4_smallvec_copy_hdr(stub_c0, (void*)c);
    cL4_dem_save_state((dem_state_t*)stub_a0, p, a, b, (unsigned long)stub_c0);
    cL4_small_release((void*)stub_c0);
    int n = cL4_dem_has_extra(p);
    unsigned long r;
    if (n == 0 || (n = *(int *)(p + 0x60), n == 0)) {
        r = 0;
    } else {
        unsigned int u = (unsigned int)(n - 1);
        r = *(unsigned long *)(*(long *)(p + 0x58) + (unsigned long)u * 8);
        *(unsigned int *)(p + 0x60) = u;
        if (u != 0) {
            long l = *(long *)(*(long *)(p + 0x58) + (unsigned long)(n - 2U) * 8);
            *(unsigned int *)(p + 0x60) = (unsigned int)(n - 2U);
            if (l != 0) r = 0;
        }
    }
    cL4_dem_restore_state((dem_state_t*)stub_a0);
    if (canary != -0x2c8502b44bfffed6) cL4_swift_fatal();
    return r;
}

/* FUN_003a3380 @ 0x003a3380   (est. cL4_dem_release_storage)
 * Ghidra: void FUN_003a3380(undefined8 *param_1)
 * Releases a demangle storage block: resets the header, releases the
 * collector small-vector, and tears down the node buffer.
 * Confidence: low
 */
void cL4_dem_release_storage(unsigned long *p)
{
    p[0] = 0x67c398;
    cL4_small_release((void*)(p + 0x44));
    cL4_dem_nodebuf_release((void*)p);
}

/* FUN_003a33cc @ 0x003a33cc   (est. cL4_dem_node_named)
 * Ghidra: undefined8 FUN_003a33cc(long *param_1)
 * Walks a node's child chain following the kind-0xf4 "named" wrapper, and
 * returns 1 if the chain ends on a 0xbf/0x16b kind node (a named type).
 * Confidence: low
 */
unsigned long cL4_dem_node_named(long *node)
{
    unsigned short k;
    for (;;) {
        if (node == 0) return 0;
        k = *(unsigned short *)(node + 2);
        if (k != 0xf4) {
            if ((1 < k - 0xbf) && (k != 0x16b)) return 0;
            return 1;
        }
        if (1 < *(unsigned char *)((long)node + 0x12) - 1) {
            if (*(unsigned char *)((long)node + 0x12) != 5) return 0;
            if ((int)node[1] == 0) return 0;
            node = (long*)*node;
        }
        node = (long*)*node;
    }
}

/* FUN_003a3430 @ 0x003a3430   (est. cL4_dem_emit_empty)
 * Ghidra: void FUN_003a3430(undefined8 param_1, undefined2 param_2)
 * Emits an empty (tag 0) node with the given kind into the state buffer.
 * Confidence: low
 */
void cL4_dem_emit_empty(dem_state_t *st, unsigned short kind)
{
        dem_node_t *n = (dem_node_t*)cL4_dem_node_reserve(st, 1);
    *(unsigned short*)((long)n + 0x10) = kind;
    *(unsigned char*)((long)n + 0x12) = 0;
}

/* FUN_003a3460 @ 0x003a3460   (est. cL4_dem_node_push_child)
 * Ghidra: void FUN_003a3460(uint *param_1, long param_2, undefined8 param_3)
 * Appends a child node to a demangle node, growing the backing store via the
 * state's collector as needed. The node's tag byte selects the child slot:
 * 0 -> word0, 1 -> word1, 2 -> convert to array(5), 5 -> array append.
 * Confidence: medium
 */
void cL4_dem_node_push_child(dem_state_t *st, dem_node_t *n, unsigned long child)
{
    unsigned char tag = n->tag;
    unsigned long *base;
    unsigned int cnt;
    if (child == 0) return;
    switch (tag) {
    case 0:
        n->w0 = child;
        n->tag = 1;
        return;
    case 1:
        n->w1 = child;
        n->tag = 2;
        return;
    case 5:
        base = (unsigned long*)n->w0;
        cnt = n->count;
        if (n->cap <= cnt) {
            cL4_dem_array_push(st, (long*)&n->w0, &n->count, 1);
            base = (unsigned long*)n->w0;
            cnt = n->count;
        }
        base[cnt] = child;
        n->count = cnt + 1;
        return;
    case 2:
        base = (unsigned long*)cL4_dem_node_reserve(st, 3);
        base[0] = n->w0;
        base[1] = n->w1;
        base[2] = child;
        n->w0 = (unsigned long)base;
        n->tag = 5;
        n->count = 3;
        return;
    default:
        return;
    }
}

/* FUN_003a3578 @ 0x003a3578   (est. cL4_dem_array_push)
 * Ghidra: void FUN_003a3578(long param_1, long *param_2, uint *param_3, ulong param_4)
 * Grows the backing array of a small-vector (param_1 = state, param_2 =
 * data ptr, param_3 = count ptr, param_4 = new capacity), copying existing
 * elements, and updates the count.
 * Confidence: medium
 */
void cL4_dem_array_push(dem_state_t *st, long *vec, unsigned int *cntp,
                        unsigned long n)
{
    unsigned int old = *cntp;
    unsigned long len = (unsigned long)old;
    long dst;
    if ((*vec + len * 8 == *(long *)((long)st + 8)) &&
        (*(long *)((long)st + 8) + n * 8 <= *(unsigned long *)((long)st + 0x10))) {
        *(unsigned long *)((long)st + 8) = *(long *)((long)st + 8) + n * 8;
    } else {
        if (n <= (unsigned long)(old << 1)) n = (unsigned long)(old << 1);
        if (n < 5) n = 4;
        dst = (long)cL4_smallvec_reserve((long)st, n + len);
        if (old != 0) cL4_memcpy_v((unsigned long)dst, (unsigned long)*vec, len << 3);
        *vec = dst;
        old = *cntp;
    }
    *cntp = old + (unsigned int)n;
}

/* FUN_003a3628 @ 0x003a3628   (est. cL4_dem_node_remove_at)
 * Ghidra: void FUN_003a3628(long *param_1, uint param_2)
 * Removes the element at index param_2 from a node's child array (or single
 * child), shifting remaining elements down and shrinking the count.
 * Confidence: medium
 */
void cL4_dem_node_remove_at(dem_node_t *n, unsigned int idx)
{
    unsigned int cnt;
    char tag = (char)n->tag;
    if (tag == 5) {
        unsigned int i;
        cnt = (unsigned int)n->count - 1;
        if (idx != cnt) {
            do {
                i = idx + 1;
                *(unsigned long *)(n->w0 + (unsigned long)idx * 8) =
                    *(unsigned long *)(n->w0 + (unsigned long)i * 8);
                idx = i;
            } while (cnt != i);
            cnt = (unsigned int)n->count - 1;
        }
        n->count = cnt;
    } else if (tag == 2) {
        if (idx == 0) n->w0 = n->w1;
        n->tag = 1;
    } else if (tag == 1) {
        n->tag = 0;
    }
}

/* FUN_003a36a0 @ 0x003a36a0   (est. cL4_dem_node_set_at)
 * Ghidra: void FUN_003a36a0(long *param_1, uint param_2, long param_3)
 * Writes child `param_3` at index param_2 of a node, honoring its tag.
 * Confidence: medium
 */
void cL4_dem_node_set_at(dem_node_t *n, unsigned int idx, long child)
{
    char tag = (char)n->tag;
    if (tag == 5) {
        *(long *)(n->w0 + (unsigned long)idx * 8) = child;
    } else if (tag == 2) {
        (&n->w0)[idx] = (unsigned long)child;
    } else if (tag == 1) {
        n->w0 = (unsigned long)child;
    }
}

/* FUN_003a36d8 @ 0x003a36d8   (est. cL4_dem_node_reverse)
 * Ghidra: void FUN_003a36d8(undefined1 (*param_1)[16], ulong param_2)
 * Reverses a node's child array in place (tag 5), or swaps the two words for
 * a two-child node at index 0.
 * Confidence: medium
 */
void cL4_dem_node_reverse(dem_node_t *n, unsigned long idx)
{
    unsigned long *base, *a, *b, *a2, *b2, w;
    if (n->tag == 5) {
        base = (unsigned long*)n->w0;
        b = (unsigned long*)((n->w0 + (unsigned long)n->count * 8) - 8);
        if (idx != n->count && &base[idx] < b) {
            a = &base[idx];
            do {
                a2 = a + 1;
                w = *a;
                *a = *b;
                b2 = b - 1;
                *b = w;
                b = b2;
                a = a2;
            } while (a2 < b2);
        }
    } else if (n->tag == 2 && idx == 0) {
        w = n->w0;
        n->w0 = n->w1;
        n->w1 = w;
    }
}

/* FUN_003a3748 @ 0x003a3748   (est. cL4_dem_node_find)
 * Ghidra: ushort * FUN_003a3748(ushort *param_1, undefined8 param_2, int param_3)
 * Searches a node tree for a child whose key equals param_2, recursing to
 * depth param_3; returns the matching node or null.
 * Confidence: low
 */
unsigned short *cL4_dem_node_find(unsigned short *n, unsigned long key, int depth)
{
    unsigned char tag;
    unsigned short *p, *q, *r;
    if ((unsigned int)n[8] == (unsigned int)key) return n;
    if (depth < 1) return 0;
    tag = (unsigned char)n[9];
    p = n;
    if (tag - 1 < 2) {
find_again:
        if (tag == 1) { p = n + 4; goto loop; }
        q = p;
        if (tag == 2) goto iter;
        if (tag != 5) { p = 0; goto loop; }
        p = *(unsigned short **)n;
    } else {
        if (tag != 5) { p = 0; goto find_again; }
        p = *(unsigned short **)n;
        q = p;
    }
    p = p + (unsigned long)*(unsigned int *)(n + 4) * 4;
loop:
    do {
        q = p;
        if (p == (unsigned short*)0) return 0;
iter:
        p = q + 4;
        q = cL4_dem_node_find((unsigned short*)*(unsigned long*)q, key, depth - 1);
    } while (q == 0);
    return q;
}

/* FUN_003a3814 @ 0x003a3814   (est. cL4_dem_free_chain)
 * Ghidra: void FUN_003a3814(long *param_1)
 * Frees a linked chain of nodes.
 * Confidence: low
 */
void cL4_dem_free_chain(long *p)
{
    while (p != 0) {
        p = (long*)*p;
        cL4_free((void*)p, 0);
    }
}

/* FUN_003a3898 @ 0x003a3898   (est. cL4_dem_node_reserve)
 * Ghidra: void FUN_003a3898(long param_1, long param_2)
 * Reserves room in the demangle node buffer for param_2 entries (0x18 bytes
 * each), growing the backing store (state +0x18/+0x20) as needed; returns
 * the node pointer (in x0 per the callers).
 * Confidence: medium
 */
unsigned long cL4_dem_node_reserve(dem_state_t *st, unsigned long n)
{
    unsigned long need = n * 0x18;
    unsigned long cur = *(long *)((long)st + 8) + 7U & 0xfffffffffffffff8;
    *(unsigned long *)((long)st + 8) = cur;
    if ((cur == 0) || (*(unsigned long *)((long)st + 0x10) < cur + need)) {
        unsigned long newcap = *(long *)((long)st + 0x20) * 2;
        unsigned long m = need + 8;
        if (newcap < m || newcap - m == 0) newcap = m;
        *(unsigned long *)((long)st + 0x20) = newcap;
        unsigned long *nb = (unsigned long *)cL4_swift_alloc(newcap + 8, 0x2004093837f09);
        *nb = *(unsigned long *)((long)st + 0x18);
        unsigned long aligned = (unsigned long)nb + 0xfU & 0xfffffffffffffff8;
        *(unsigned long *)((long)st + 0x10) = (unsigned long)nb + newcap + 8;
        *(unsigned long **)((long)st + 0x18) = nb;
        cur = aligned;
    }
    *(unsigned long *)((long)st + 8) = cur + need;
    return cur;
}

/* FUN_003a3944 @ 0x003a3944   (est. cL4_dem_emit_bare)
 * Ghidra: void FUN_003a3944(undefined8 param_1, undefined2 param_2, undefined8 param_3)
 * Emits a tag-4 node (payload only) with the given kind and payload word.
 * Confidence: medium
 */
void cL4_dem_emit_bare(dem_state_t *st, unsigned short kind, unsigned long payload)
{
    unsigned long *n = (unsigned long*)cL4_dem_node_reserve(st, 1);
    *(unsigned short*)(n + 2) = kind;
    *(unsigned char*)((long)n + 0x12) = 4;
    *n = payload;
}

/* FUN_003a3980 @ 0x003a3980   (est. cL4_dem_emit_pair)
 * Ghidra: void FUN_003a3980(undefined8 param_1, undefined2 param_2, undefined8 param_3, undefined8 param_4)
 * Emits a tag-3 node (payload + count) with kind and two payload words.
 * Confidence: medium
 */
void cL4_dem_emit_pair(dem_state_t *st, unsigned short kind, unsigned long a,
                       unsigned long b)
{
    unsigned long *n = (unsigned long*)cL4_dem_node_reserve(st, 1);
    *(unsigned short*)(n + 2) = kind;
    *(unsigned char*)((long)n + 0x12) = 3;
    *n = a;
    n[1] = b;
}

/* FUN_003a39c8 @ 0x003a39c8   (est. cL4_dem_emit_pairw)
 * Ghidra: void FUN_003a39c8(undefined8 param_1, undefined2 param_2, undefined8 *param_3)
 * Emits a tag-3 node whose payload words come from the 16-byte buffer *param_3.
 * Confidence: medium
 */
void cL4_dem_emit_pairw(dem_state_t *st, unsigned short kind, unsigned long *src)
{
    unsigned long a = src[0];
    unsigned int b = *(unsigned int *)(src + 1);
    unsigned long *n = (unsigned long*)cL4_dem_node_reserve(st, 1);
    *(unsigned short*)(n + 2) = kind;
    *(unsigned char*)((long)n + 0x12) = 3;
    *n = a;
    n[1] = (unsigned long)b;
}

/* FUN_003a3a10 @ 0x003a3a10   (est. cL4_dem_emit_str)
 * Ghidra: long * FUN_003a3a10(undefined8 param_1, undefined2 param_2, long param_3)
 * Emits a tag-3 string node with kind, the string pointer, and its length.
 * Confidence: medium
 */
dem_node_t *cL4_dem_emit_str(dem_state_t *st, unsigned short kind, unsigned long s)
{
    unsigned long *n = (unsigned long*)cL4_dem_node_reserve(st, 1);
    unsigned long len;
    if (s == 0) len = 0;
    else len = cL4_obj_retain_length(s);
    *(unsigned short*)(n + 2) = kind;
    *(unsigned char*)((long)n + 0x12) = 3;
    *n = s;
    n[1] = len;
    return (dem_node_t*)n;
}

/* FUN_003a3a70 @ 0x003a3a70   (est. cL4_dem_string_push)
 * Ghidra: void FUN_003a3a70(long *param_1, undefined8 param_2, long param_3, undefined8 param_4)
 * Appends `param_3` bytes from param_2 to the string-builder (param_1),
 * growing the buffer (param_1+0xc) as needed.
 * Confidence: medium
 */
void cL4_dem_string_push(dem_state_t *st, long *s, unsigned long data, long n)
{
    unsigned long len = (unsigned long)*(unsigned int *)(s + 1);
    if ((unsigned long)*(unsigned int *)((long)s + 0xc) < (unsigned long)n + len) {
        cL4_dem_string_reserve(st, s, (unsigned int *)((long)s + 0xc), (unsigned long)n);
        len = (unsigned long)*(unsigned int *)(s + 1);
    }
    cL4_memcpy_v((unsigned long)(*s + len), data, (unsigned long)n);
    *(int *)(s + 1) = (int)s[1] + (int)n;
}

/* FUN_003a3aec @ 0x003a3aec   (est. cL4_dem_string_reserve)
 * Ghidra: void FUN_003a3aec(long param_1, long *param_2, uint *param_3, ulong param_4)
 * Grows the string builder buffer (byte-scaled variant of array_push).
 * Confidence: medium
 */
void cL4_dem_string_reserve(dem_state_t *st, long *s, unsigned int *cntp,
                            unsigned long n)
{
    unsigned int old = *cntp;
    unsigned long len = (unsigned long)old;
    long dst;
    if ((*s + len == *(long *)((long)st + 8)) &&
        (*(long *)((long)st + 8) + n <= *(unsigned long *)((long)st + 0x10))) {
        *(unsigned long *)((long)st + 8) = *(long *)((long)st + 8) + n;
    } else {
        if (n <= (unsigned long)(old << 1)) n = (unsigned long)(old << 1);
        if (n < 5) n = 4;
        dst = (long)cL4_smallvec_reserve((long)st, n + len);
        if (old != 0) cL4_memcpy_v((unsigned long)dst, (unsigned long)*s, len);
        *s = dst;
        old = *cntp;
    }
    *cntp = old + (unsigned int)n;
}

/* FUN_003a3b9c @ 0x003a3b9c   (est. cL4_dem_string_push_int)
 * Ghidra: void FUN_003a3b9c(long *param_1, ulong param_2, undefined8 param_3)
 * Appends a signed integer to the string builder (with '-' sign).
 * Confidence: medium
 */
void cL4_dem_string_push_int(dem_state_t *st, long *s, unsigned long v,
                             unsigned long p3)
{
    unsigned int cnt = *(unsigned int *)(s + 1);
    unsigned char *buf;
    int n;
    if (*(unsigned int *)((long)s + 0xc) < cnt + 0xb) {
        cL4_dem_string_reserve(st, s, (unsigned int *)((long)s + 0xc), 0xb);
        cnt = *(unsigned int *)(s + 1);
    }
    buf = (unsigned char *)(*s + (unsigned long)cnt);
    if ((long)v < 0) {
        *buf = 0x2d;
        v = (unsigned long)(unsigned int)-(int)v;
        buf += 1;
    }
    n = cL4_itoa(v, (char*)buf);
    *(int *)(s + 1) = (int)s[1] + n;
    (void)p3;
}

/* FUN_003a3c20 @ 0x003a3c20   (est. cL4_dem_string_push_uint)
 * Ghidra: void FUN_003a3c20(long *param_1, ulong param_2, undefined8 param_3)
 * Appends an unsigned integer in decimal to the string builder.
 * Confidence: medium
 */
void cL4_dem_string_push_uint(dem_state_t *st, long *s, unsigned long v,
                              unsigned long p3)
{
    unsigned char *lo, *hi, *b;
    unsigned int cnt = *(unsigned int *)(s + 1);
    int n = 0;
    if (*(unsigned int *)((long)s + 0xc) < cnt + 0x15) {
        cL4_dem_string_reserve(st, s, (unsigned int *)((long)s + 0xc), 0x15);
        cnt = *(unsigned int *)(s + 1);
    }
    lo = (unsigned char *)(*s + (unsigned long)cnt);
    if (v == 0) {
        lo[0] = 0x30;
        lo[1] = 0;
        n = 1;
    } else {
        n = 0;
        b = lo;
        do {
            unsigned char *b2 = b;
            b = b2 + 1;
            *b2 = (unsigned char)v + (unsigned char)(v / 10) * -10 | 0x30;
            n += 1;
            unsigned int cont = 9 < v;
            v = v / 10;
            if (!cont) break;
        } while (1);
        *b = 0;
        if (lo < b) {
            hi = b - 1;
            do {
                unsigned char t = *b;
                *b = *lo;
                *lo = t;
                unsigned int cont = lo + 1 < b;
                lo += 1;
                b -= 1;
                if (!cont) break;
            } while (1);
        }
    }
    *(int *)(s + 1) = (int)s[1] + n;
    (void)p3;
}
