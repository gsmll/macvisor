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

/* FUN_0000456c @ 0x456c — read a per-CPU / hardware value (used by
 * FUN_003a0dec to seed a 16-bit token). */
extern unsigned int cL4_hw_seed(void);
/* FUN_00019850 @ 0x19850 — read/write the 16-bit object at *p; used as a
 * token reserve/commit pair in FUN_003a0dec. */
extern long cL4_token_ops(unsigned short *p);
/* FUN_00118cf8 @ 0x118cf8 — convert an object/string into a cL4 handle. */
extern unsigned long cL4_make_handle(unsigned long obj);
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
extern unsigned long cL4_node_word(unsigned long *node);
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
