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
static unsigned long cL4_dem_pop_kind_node(dem_state_t *st, unsigned long (*fn)(unsigned short)); /* 3a4110 */
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
static unsigned long *cL4_dem_parse_word(dem_state_t *st)
{
    unsigned long pos, p2, len;
    unsigned char b;
    unsigned long *node = 0;
    pos = *(unsigned long *)((long)st + 0x48);
    if (pos >= *(unsigned long *)((long)st + 0x40)) return 0;
    b = *(unsigned char *)(*(long *)((long)st + 0x38) + pos);
    if (b - 0x30 < 10) {
        /* read the length (single digit) */
        len = (unsigned long)(b - 0x30);
        p2 = pos + 1;
        *(unsigned long *)((long)st + 0x48) = p2;
        /* skip an optional '_' separator */
        if (p2 < *(unsigned long *)((long)st + 0x40) &&
            *(char *)(*(long *)((long)st + 0x38) + p2) == '_') {
            p2 = p2 + 1;
            *(unsigned long *)((long)st + 0x48) = p2;
        }
        /* bounds-check the payload */
        if (*(unsigned long *)((long)st + 0x40) < p2 + len) return 0;
        /* emit a string node from the raw bytes */
        node = (unsigned long*)cL4_dem_node_reserve(st, 1);
        *(unsigned short*)(node + 2) = 0x67;
        *(unsigned char*)((long)node + 0x12) = 3;
        node[0] = *(long *)((long)st + 0x38) + p2;
        node[1] = len;
        *(unsigned long *)((long)st + 0x48) = p2 + len;
    }
    return node;
}

/* ------------------------------------------------------------------ *
 * Function bodies
 * ------------------------------------------------------------------ */

/* Walk the demangler "context chain": from a global context record, follow
 * the +8 link until the entry whose +0x28 field is non-null. */
static long cL4_dem_ctx_walk(void)
{
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
    long t;
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
            if (word == 0) { t = cL4_dem_ctx_walk(); (void)t; }
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
    if (word == 0) { t = cL4_dem_ctx_walk(); (void)t; }
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
    long t;
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
            if (word == 0) { t = cL4_dem_ctx_walk(); (void)t; }
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
    if (word == 0) { t = cL4_dem_ctx_walk(); (void)t; }
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
    long t;
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
            t = cL4_dem_ctx_walk(); (void)t;
            return 0;
        }
    } else if (kind != 0x305) {
        if ((1 < kind - 0x500U) && (kind != 0x400)) return 0;
        __asm__ volatile("brk #1" ::: "memory"); /* 0x3a0c90 */
    }
    t = cL4_dem_ctx_walk(); (void)t;
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
