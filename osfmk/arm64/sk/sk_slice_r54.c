/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel,
 * arm64e, image base 0) — the cL4 microkernel (GL1), "cL4 (679.100.61)".
 * Ground truth: Ghidra FUN_ names + addresses in program cl4_kernel.raw.
 * Slice R54: 0x3ba9e0-0x3c7a24. This is the Swift-runtime demangler /
 * type-description printer: the cL4 kernel renders mangled type metadata
 * nodes (parameter/result/generic-argument/substituted-type records) into a
 * growing output stream of printable characters, decoding argument
 * descriptor kinds (0x1b/0x1c/0x2c/0x30-0x33/...) and marshalling them into
 * the outbound message object. Many bodies are the demangler's shared
 * "append this node's text" helpers that walk the demangler node tree
 * (node header: *(uint16*)(node+0x10) = node kind, *(uint8*)(node+0x12) =
 * element-count/ref flag 1|2|5). All names are estimates unless
 * string-matched.
 *
 * Calling-convention note: the demangler output stream lives at `out+8`
 * (a growable buffer of chars); FUN_00112e8c appends `n` bytes and
 * FUN_001130a0 appends one char. The `node` arrays use the variant header
 * convention: count byte at +0x12 (1 = inline single element at node+8,
 * 2 = inline two elements, 5 = pointer to element array at *node with
 * element count at node+1). Ghidra FUN_ names are kept only in comments.
 */

#include <stdint.h>
#include <stddef.h>
#include <string.h>

/* ------------------------------------------------------------------ *
 * Out-of-range cL4 helpers (declared extern with a one-line note; their
 * bodies are reconstructed by the range worker that owns them).
 * ------------------------------------------------------------------ */

/* FUN_00112e8c @ 0x112e8c — append `n` bytes to the demangler output
 * stream at `out` (the buffer lives at out+8). */
extern void cL4_out_puts(unsigned long out, const void *s, unsigned long n);
/* FUN_001130a0 @ 0x1130a0 — append one character to the demangler stream. */
extern void cL4_out_putc(unsigned long out, char c);
/* FUN_00112db4 @ 0x112db4 — append a (ptr,len,flag) string record to the
 * output stream (used with the demangler's record helpers). */
extern unsigned long cL4_out_puts_rec(unsigned long out, const void *rec);
/* FUN_003b2180 @ 0x3b2180 — render demangler node `node` into the output
 * stream at `out`, at render `depth`; `last` flags terminator handling. */
extern void cL4_dem_node(unsigned long out, unsigned long node, unsigned long depth, unsigned long last);
/* FUN_003b8d18 @ 0x3b8d18 — render a generic/substituted demangler node
 * into `out` at `depth` (companion to cL4_dem_node). */
extern void cL4_dem_node2(unsigned long out, unsigned long node, unsigned long depth, unsigned long last);
/* FUN_003be2a8 @ 0x3be2a8 — append a string record (ptr,len) built from a
 * demangler node into `out`. */
extern void cL4_dem_rec(unsigned long out, void *dst, const void *node);
/* FUN_003b1eec @ 0x3b1eec — build a 24-byte string record descriptor. */
extern void cL4_str_rec_make(void *dst);
/* FUN_003bde74 / 003bde18 — string-record copy/append helpers. */
extern void cL4_str_rec_copy(void *dst, const void *src, unsigned long flag);
extern void cL4_str_rec_append(void *dst, const void *src, const void *rec);
/* FUN_003bdcb0 @ 0x3bdcb0 — build a string record from a (ptr,len) pair. */
extern void cL4_str_rec_from(void *dst, unsigned long ptr, unsigned long len);
/* FUN_003bdb80 @ 0x3bdb80 — append record `rec` to the string record `dst`. */
extern void cL4_str_rec_cat(void *dst, const void *rec);
/* FUN_00113240 @ 0x113240 — append a (ptr,len) record onto a string record. */
extern void *cL4_str_rec_push(const void *dst, unsigned long a, const void *ctx, unsigned long n);
/* FUN_00113368 @ 0x113368 — append a (ptr,len) record into a string record. */
extern void cL4_str_rec_push2(void *dst, unsigned long ptr, unsigned long len);
/* FUN_0036a5ac @ 0x36a5ac — build a string record from a C string. */
extern void cL4_str_rec_cstr(void *dst, const char *s);
/* FUN_003a3430 @ 0x3a3430 — IPC object field getter (token in arg). */
extern unsigned long cL4_obj_field_get(unsigned long a);
/* FUN_003a3460 @ 0x3a3460 — IPC object field setter. */
extern void cL4_obj_field_set(unsigned long val, unsigned long obj, unsigned long tok);
/* FUN_003a2e9c @ 0x3a2e9c — build an owned (ptr,len) string record from a
 * raw pointer+length pair (adopting ownership). */
extern void cL4_str_own(void *dst, unsigned long ptr, unsigned long len);
/* FUN_00362de4 @ 0x362de4 — release/destroy an owned string record. */
extern void cL4_str_own_free(void *rec);
/* FUN_003a2c18 @ 0x3a2c18 — begin a demangler recursion context (returns a
 * 8-byte handle). */
extern unsigned long cL4_dem_ctx_begin(void *out);
/* FUN_003a2cf0 @ 0x3a2cf0 — end a demangler recursion context. */
extern void cL4_dem_ctx_end(void *ctx);
/* FUN_003a2d38 @ 0x3a2d38 — push a node onto the demangler recursion stack. */
extern unsigned long cL4_dem_ctx_push(unsigned long ctx, unsigned long a, unsigned long b);
/* FUN_00360e28 @ 0x360e28 — snapshot the current demangler output context. */
extern unsigned long cL4_dem_ctx_snapshot(void);
/* FUN_0036a5ac @ 0x36a5ac — build a string record from a C string. */
/* (declared above as cL4_str_rec_cstr) */
/* FUN_003995cc @ 0x3995cc — realloc/grow the output stream buffer. */
extern void *cL4_out_grow(unsigned long out);
/* FUN_00111890 @ 0x111890 — allocate `size` bytes with allocator tag. */
extern void *cL4_alloc(unsigned long size, unsigned long tag);
/* FUN_00117cc4 — memcpy (buffer copy). */
extern void *cL4_memcpy(void *dst, const void *src, unsigned long n);
/* thunk_FUN_00012568 @ 0x12568 — free. */
extern void cL4_free(void *p, unsigned long size);
/* FUN_001145b0 — memcmp. */
extern int cL4_memcmp(const void *a, const void *b, unsigned long n);
/* FUN_00115080 — strlen. */
extern unsigned long cL4_strlen(const char *s);
/* FUN_0011d7e8 @ 0x11d7e8 — noreturn stack-canary failure handler. */
extern void cL4_stack_fail(void) __attribute__((noreturn));
/* FUN_004b89f8 @ 0x4b89f8 — noreturn allocation-size panic. */
extern void cL4_panic_big(void) __attribute__((noreturn));
/* FUN_00113e24 @ 0x113e24 — append a (ptr,len) record into a string rec. */
extern void cL4_str_rec_fmt(void *dst, const void *rec, const void *fmt);

/* ---- IPC / argument-marshalling helpers owned by sibling slices ---- */

/* FUN_003d0280 @ 0x3d0280 (R06) — decode argument `idx` of message `msg`
 * into `*result` (cleared on success), at `depth`; used by the arg printers. */
extern void cL4_msg_arg_index(int *result, unsigned long tcb, unsigned long *msg, unsigned long idx, unsigned long depth);
/* FUN_003d11d4 / 003d1218 / 003d12c8 / 003d01ac — message decode helpers. */
extern void cL4_msg_one(int *result, unsigned long tcb, unsigned long *msg, unsigned long depth);
extern void cL4_msg_three(int *result, unsigned long tcb, unsigned long *msg, unsigned long depth);
extern void cL4_msg_parse(unsigned long *result, unsigned long *tcb, unsigned long *msg, unsigned long depth);
extern void cL4_msg_args(int *result, unsigned long tcb, unsigned long *msg, unsigned long depth);
/* FUN_003d154c — emit a tag byte pair record. */
extern void cL4_msg_emit_pair(unsigned long tcb, unsigned long *msg, unsigned long tag, unsigned char byte);
/* FUN_003a3a70 — emit a tagged IPC message-register record into `obj`. */
extern void cL4_mr_emit_tag(long obj, const void *tag, unsigned long count, unsigned long val);
/* FUN_003acd3c — emit a single data byte into the outbound object. */
extern void cL4_mr_emit_byte(long obj, const void *byte, unsigned long val);
/* FUN_003a3c20 — emit a count-sized value record into the outbound object. */
extern void cL4_mr_emit_val2(long obj, long count, unsigned long val);
/* FUN_003a3430 — IPC object field getter (declared above). */
/* FUN_003bf898 @ 0x3bf898 — release/commit the temporary output record. */
extern void cL4_out_commit(unsigned long tcb, long *stack);
/* FUN_003bf718 / 003bf7e4 — build/read an output descriptor. */
extern unsigned char (*cL4_fmt_build(unsigned long tcb, unsigned long msg, unsigned long depth))[16];
extern int cL4_fmt_kind(unsigned long tcb, unsigned char (*desc)[16]);
/* FUN_003bea1c — demangler arg-kind-flag predicate. */
extern int cL4_dem_flags(unsigned long a);
/* FUN_003ba044 @ 0x3ba044 — find/emit a named demangler node by kind. */
extern unsigned long cL4_dem_find_kind(unsigned long out, unsigned long node, unsigned long kind);
/* FUN_003b1178 @ 0x3b1178 — demangler helper (render index/type). */
extern unsigned long cL4_dem_index(unsigned long out, unsigned long node);
/* FUN_003d2740 — destroy the demangler recursion context. */
extern void cL4_dem_ctx_destroy(void *ctx);
/* FUN_003b2010 — demangler string-record callback. */
extern void cL4_dem_str_cb(void);
/* FUN_004ba4b0 / 004ba4c8 / 004ba4e0 / 004ba4f8 — noreturn panic helpers. */
extern void cL4_panic_x(void) __attribute__((noreturn));
extern unsigned long cL4_panic_rec(void);

/* String/data constants referenced by this slice (addresses in comments). */
extern const char DAT_005d9065[];   /* "" (empty) @ 0x5d9065 */
extern const char DAT_005d0c46[];   /* ", " @ 0x5d0c46 */
extern const char DAT_005d021c[];   /* " " @ 0x5d021c */
extern const char DAT_005d3bb7[];   /* "" @ 0x5d3bb7 */
extern const char DAT_005d3566[];   /* " " @ 0x5d3566 */
extern const char DAT_005d3cba[];   /* " -> " @ 0x5d3cba */
extern const char DAT_005d3ad7[];   /* " " @ 0x5d3ad7 */
extern const char DAT_005d32c2[];   /* ")" @ 0x5d32c2 */
extern const char DAT_005d3cc6[];   /* "," @ 0x5d3cc6 */
extern const char DAT_005d7140[];   /* " " @ 0x5d7140 */
extern const char DAT_005d7142[];   /* ")" @ 0x5d7142 */
extern const char DAT_005d712a[];   /* " " @ 0x5d712a */
extern const char DAT_005d7415[];   /* " " @ 0x5d7415 */
extern const char DAT_005d3bb9[];   /* " " @ 0x5d3bb9 */
extern const char DAT_005d7133[];   /* " " @ 0x5d7133 */
extern const char DAT_005d6ff3[];   /* " " @ 0x5d6ff3 */
extern const char DAT_005d6fcf[];   /* " " @ 0x5d6fcf */
extern const char DAT_005d6fd3[];   /* " " @ 0x5d6fd3 */
extern const char DAT_005d6fe5[];   /* " " @ 0x5d6fe5 */
extern const char DAT_005d6fe1[];   /* " " @ 0x5d6fe1 */
extern const char DAT_005d6fcb[];   /* " " @ 0x5d6fcb */
extern const char DAT_005d6fc7[];   /* " " @ 0x5d6fc7 */
extern const char DAT_005d6fc5[];   /* " " @ 0x5d6fc5 */
extern const char DAT_005d6fdb[];   /* " " @ 0x5d6fdb */
extern const char DAT_005d70ae[];   /* " " @ 0x5d70ae */
extern const char DAT_005d703c[];   /* " " @ 0x5d703c */
extern const char DAT_005d6ecf[];   /* " " @ 0x5d6ecf */
extern const char DAT_005d6ecb[];   /* " " @ 0x5d6ecb */
extern const char DAT_005d7187[];   /* " " @ 0x5d7187 */
extern const char DAT_005d7182[];   /* " " @ 0x5d7182 */
extern const char DAT_005d7133[];   /* " " @ 0x5d7133 */
extern const char DAT_005d68c3[];   /* " " @ 0x5d68c3 */
extern const char DAT_005d68c0[];   /* " " @ 0x5d68c0 */
extern const char DAT_005d5321[];   /* " " @ 0x5d5321 */
extern const char DAT_005d3fb6[];   /* " " @ 0x5d3fb6 */
extern const char DAT_005d3fb4[];   /* " " @ 0x5d3fb4 */
extern const char DAT_005d3bdd[];   /* " " @ 0x5d3bdd */
extern const char DAT_005d3bb7[];   /* " " @ 0x5d3bb7 */
extern const char DAT_005d3819[];   /* " " @ 0x5d3819 */
extern const char DAT_005d37f0[];   /* " " @ 0x5d37f0 */
extern const char DAT_005d37d7[];   /* " " @ 0x5d37d7 */
extern const char DAT_005d3568[];   /* " " @ 0x5d3568 */
extern const char DAT_005cf438[];   /* " " @ 0x5cf438 */
extern const char DAT_005cef08[];   /* " " @ 0x5cef08 */
extern const char DAT_005ce788[];   /* " " @ 0x5ce788 */
extern const char DAT_005ce763[];   /* " " @ 0x5ce763 */
extern const char DAT_005ce75d[];   /* " " @ 0x5ce75d */
extern const char DAT_005ce75a[];   /* " " @ 0x5ce75a */
extern const char DAT_005ce757[];   /* " " @ 0x5ce757 */
extern const char DAT_005ce754[];   /* " " @ 0x5ce754 */
extern const char DAT_005ce751[];   /* " " @ 0x5ce751 */
extern const char DAT_005c9984[];   /* " " @ 0x5c9984 */
extern const char DAT_004f29a0[];   /* " " @ 0x4f29a0 */
extern const char DAT_004f29b0[];   /* " " @ 0x4f29b0 */
extern const char DAT_004bb178[];   /* " " @ 0x4bb178 */
extern const char DAT_005be7c0[];   /* "" @ 0x5be7c0 */
extern const char DAT_005d903b[];   /* " " @ 0x5d903b */
extern const char DAT_005d903f[];   /* "subscript" @ 0x5d903f */
extern const char DAT_005d904a[];   /* "<Unknown>" @ 0x5d904a */
extern const char DAT_005d4702[];   /* "<unknown>" @ 0x5d4702 */
extern const char DAT_005d9055[];   /* " " @ 0x5d9055 */
extern const char DAT_005d9068[];   /* "-> " @ 0x5d9068 */
extern const char DAT_005d882b[];   /* "substituted" @ 0x5d882b */
extern const char DAT_005d8802[];   /* "mangledCType" @ 0x5d8802 */
extern const char DAT_005d87f5[];   /* "convention" @ 0x5d87f5 */
extern const char DAT_005d7145[];   /* "Argument Types" @ 0x5d7145 */
extern const char DAT_005d712d[];   /* "each" @ 0x5d712d */
extern const char DAT_005d7138[];   /* "where" @ 0x5d7138 */
extern const char DAT_005d7123[];   /* "for <" @ 0x5d7123 */
extern const char DAT_005d712a[];   /* ", " @ 0x5d712a */
extern const char DAT_005d7140[];   /* " " @ 0x5d7140 */
extern const char DAT_005d7142[];   /* " " @ 0x5d7142 */
extern const char DAT_005d7145[];   /* "Argument Types" @ 0x5d7145 */

/* ------------------------------------------------------------------ *
 * Demangler node-tree helpers. A node is a small header + an element
 * array. The byte at +0x12 selects the element layout:
 *   1 = a single inline element at node+8 (count 1)
 *   2 = two inline elements at node+8 (count 2)
 *   5 = pointer to an external element array (*node) with element count
 *       stored in the uint32 at node+1
 *   any other value = empty (count 0, no valid elements)
 * The uint16 at node+0x10 is the node kind. These mirror the repeated
 * inline patterns in the Ghidra decompiles.
 * ------------------------------------------------------------------ */

static inline unsigned long dem_elem_count(const unsigned long *node)
{
    unsigned char f = *(unsigned char *)((const char *)node + 0x12);
    if (f == 1 || f == 2) return f;
    if (f == 5) return *(unsigned int *)(node + 1);
    return 0;
}

static inline unsigned long dem_elem_base(const unsigned long *node)
{
    unsigned char f = *(unsigned char *)((const char *)node + 0x12);
    if (f == 5) return *node;
    return (unsigned long)node;
}

/* Fetch element `i` of the node's element array, or 0 if out of range. */
static inline unsigned long dem_elem(const unsigned long *node, unsigned long i)
{
    unsigned char f = *(unsigned char *)((const char *)node + 0x12);
    unsigned long base;
    unsigned long n;
    if (f == 1 || f == 2) { n = f; base = (unsigned long)node; }
    else if (f == 5) { n = *(unsigned int *)(node + 1); base = *node; }
    else return 0;
    if (i >= n) return 0;
    return *(unsigned long *)(base + i * 8);
}

/* The node kind (uint16 at +0x10). */
static inline unsigned long dem_kind(const unsigned long *node)
{
    return *(unsigned short *)((const char *)node + 0x10);
}

/* In-range function prototypes (bodies below). */

/* end of prelude */
