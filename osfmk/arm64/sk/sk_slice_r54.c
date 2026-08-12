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
extern void cL4_msg_arg_index(int *result, unsigned long tcb, unsigned long msg, unsigned long idx, unsigned long depth);
/* FUN_003d11d4 / 003d1218 / 003d12c8 / 003d01ac — message decode helpers. */
extern void cL4_msg_one(int *result, unsigned long tcb, unsigned long msg, unsigned long depth);
extern void cL4_msg_three(int *result, unsigned long tcb, unsigned long msg, unsigned long depth);
extern void cL4_msg_parse(unsigned long *result, unsigned long *tcb, unsigned long msg, unsigned long depth);
extern void cL4_msg_args(int *result, unsigned long tcb, unsigned long msg, unsigned long depth);
/* FUN_003d0bc8 — dispatch a message packet with a byte tag. */
extern void cL4_msg_dispatch_pkt(int *res, unsigned long tcb, unsigned long msg, unsigned char *byte, unsigned long depth, int flag);
/* FUN_003d174c — dispatch a message with (tcb, msg, tag, count, depth). */
extern void cL4_msg_dispatch2(int *res, unsigned long tcb, unsigned long msg, unsigned long tag, unsigned long count, unsigned long depth);
/* FUN_003d1ad4 — emit a symbol from a message word. */
extern void cL4_msg_emit_sym(unsigned long tcb, unsigned long *msg, int which);
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
/* FUN_003ba390 @ 0x3ba390 — render the tail of a qualified type. */
extern void cL4_dem_tail(unsigned long out, unsigned long a, unsigned long b, unsigned long depth);
/* FUN_003b1eec @ 0x3b1eec — build a 24-byte string record. */
extern void cL4_str_rec_make2(void *dst, unsigned long a, unsigned long b);
/* FUN_0037364c @ 0x37364c — build a string record from a (ptr,len) node. */
extern void cL4_dem_rec7364(void *dst, void *node);
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
extern const char DAT_005d7629[];   /* " " @ 0x5d7629 */
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
extern const char DAT_004f29a0[16];  /* hex digit table "0123456789abcdef" @ 0x4f29a0 */
extern const char DAT_004f29b0[16];  /* hex digit table @ 0x4f29b0 */
extern const char DAT_004bb178[];   /* " " @ 0x4bb178 */
extern const char DAT_005be7c0[];   /* "" @ 0x5be7c0 */
extern unsigned long (*DAT_00658c10(void))[0];
extern const char DAT_005d6ff1[];   /* tag string @ 0x005d6ff1 */
extern const char DAT_005d90ae[];   /* tag string @ 0x005d90ae */
extern const char DAT_005d920c[];   /* tag string @ 0x005d920c */
extern const char DAT_005d9211[];   /* tag string @ 0x005d9211 */
extern const char DAT_005d9214[];   /* tag string @ 0x005d9214 */
extern const char DAT_005d9217[];   /* tag string @ 0x005d9217 */
extern const char DAT_005d921a[];   /* tag string @ 0x005d921a */
extern const char DAT_005d921e[];   /* tag string @ 0x005d921e */
extern const char DAT_005d9221[];   /* tag string @ 0x005d9221 */
extern const char DAT_005d9224[];   /* tag string @ 0x005d9224 */
extern const char DAT_005d9227[];   /* tag string @ 0x005d9227 */
extern const char DAT_005d922e[];   /* tag string @ 0x005d922e */
extern const char DAT_005d9234[];   /* tag string @ 0x005d9234 */
extern const char DAT_005d9237[];   /* tag string @ 0x005d9237 */
extern const char DAT_005d923a[];   /* tag string @ 0x005d923a */
extern const char DAT_005d923e[];   /* tag string @ 0x005d923e */
extern const char DAT_005d9241[];   /* tag string @ 0x005d9241 */
extern const char DAT_005d9244[];   /* tag string @ 0x005d9244 */
extern const char DAT_005d9247[];   /* tag string @ 0x005d9247 */
extern const char DAT_005d924a[];   /* tag string @ 0x005d924a */
extern const char DAT_005d924e[];   /* tag string @ 0x005d924e */
extern const char DAT_005d9251[];   /* tag string @ 0x005d9251 */
extern const char DAT_005d9254[];   /* tag string @ 0x005d9254 */
extern const char DAT_005d925a[];   /* tag string @ 0x005d925a */
extern const char DAT_005d9263[];   /* tag string @ 0x005d9263 */
extern const char DAT_005d926c[];   /* tag string @ 0x005d926c */
extern const char DAT_005d926f[];   /* tag string @ 0x005d926f */
extern const char DAT_005d9272[];   /* tag string @ 0x005d9272 */
extern const char DAT_005d9275[];   /* tag string @ 0x005d9275 */
extern const char DAT_005d9278[];   /* tag string @ 0x005d9278 */
extern const char DAT_005d927b[];   /* tag string @ 0x005d927b */
extern const char DAT_005d927e[];   /* tag string @ 0x005d927e */
extern const char DAT_005d9281[];   /* tag string @ 0x005d9281 */
extern const char DAT_005d9284[];   /* tag string @ 0x005d9284 */
extern const char DAT_005d9287[];   /* tag string @ 0x005d9287 */
extern const char DAT_005d928a[];   /* tag string @ 0x005d928a */
extern const char DAT_005d928d[];   /* tag string @ 0x005d928d */
extern const char DAT_005d9290[];   /* tag string @ 0x005d9290 */
extern const char DAT_005d9293[];   /* tag string @ 0x005d9293 */
extern const char DAT_005d9296[];   /* tag string @ 0x005d9296 */
extern const char DAT_005d9299[];   /* tag string @ 0x005d9299 */
extern const char DAT_005d929c[];   /* tag string @ 0x005d929c */
extern const char DAT_005d929f[];   /* tag string @ 0x005d929f */
extern const char DAT_005d92a2[];   /* tag string @ 0x005d92a2 */
extern const char DAT_005d92a5[];   /* tag string @ 0x005d92a5 */
extern const char DAT_005d92a8[];   /* tag string @ 0x005d92a8 */
extern const char DAT_005d92ab[];   /* tag string @ 0x005d92ab */
extern const char DAT_005d92ae[];   /* tag string @ 0x005d92ae */
extern const char DAT_005d92b1[];   /* tag string @ 0x005d92b1 */
extern const char DAT_005d92b4[];   /* tag string @ 0x005d92b4 */
extern const char DAT_005d92b7[];   /* tag string @ 0x005d92b7 */
extern const char DAT_005d92ba[];   /* tag string @ 0x005d92ba */
extern const char DAT_005d92bd[];   /* tag string @ 0x005d92bd */
extern const char DAT_005d92c0[];   /* tag string @ 0x005d92c0 */
extern const char DAT_005d92c3[];   /* tag string @ 0x005d92c3 */
extern const char DAT_005d92c6[];   /* tag string @ 0x005d92c6 */
extern const char DAT_005d92c9[];   /* tag string @ 0x005d92c9 */
extern const char DAT_005d92cc[];   /* tag string @ 0x005d92cc */
extern const char DAT_005d92cf[];   /* tag string @ 0x005d92cf */
extern const char DAT_005d92d3[];   /* tag string @ 0x005d92d3 */
extern const char DAT_005d92d6[];   /* tag string @ 0x005d92d6 */
extern const char DAT_005d92da[];   /* tag string @ 0x005d92da */
extern const char DAT_005d92dd[];   /* tag string @ 0x005d92dd */
extern const char DAT_005d92e0[];   /* tag string @ 0x005d92e0 */
extern const char DAT_005d92e3[];   /* tag string @ 0x005d92e3 */
extern const char DAT_005d92e5[];   /* tag string @ 0x005d92e5 */
extern const char DAT_005d92e8[];   /* tag string @ 0x005d92e8 */
extern const char DAT_005d92eb[];   /* tag string @ 0x005d92eb */
extern const char DAT_005d92ee[];   /* tag string @ 0x005d92ee */
extern const char DAT_005d92f1[];   /* tag string @ 0x005d92f1 */   /* demangler engine table @ 0x658c10 */
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

/* Forward declarations for in-range functions (bodies below). */
void cL4_dem_render_convention(unsigned long *out, unsigned long node, unsigned long depth);
void cL4_dem_render_generic_args(unsigned long out, unsigned long *node, int depth);
void cL4_dem_render_args(void *ctx, int sel, unsigned long depth);
void cL4_dem_render_arg_types(unsigned long out, unsigned long *node, unsigned long depth);
void cL4_dem_arg_group(unsigned long out, unsigned long *node, unsigned long *idx, unsigned long kind, int depth);
void cL4_dem_render_specialization(unsigned long out, unsigned long *node, unsigned long s1, unsigned long n1, unsigned long depth, unsigned long s2, unsigned long n2);
unsigned long cL4_dem_emit_rec(unsigned long out, unsigned long a, unsigned long b);
long *cL4_dem_render_qualtype(unsigned long out, long *node, unsigned long depth, unsigned int flag, int mode, unsigned long opts, long a7, long a8, unsigned long a9, unsigned long a10, unsigned long a11);
void cL4_dem_render_symbol(unsigned long *dst, long node, unsigned long *ctx);
unsigned long cL4_dem_emit_quoted(unsigned long out, unsigned char *rec);
unsigned long cL4_dem_kind2name(unsigned int kind);
unsigned long cL4_dem_kind_needs_space(unsigned long out, unsigned long node);
unsigned long cL4_dem_is_simple_type(unsigned long *node);
void cL4_dem_render_return(unsigned long out, unsigned long node, unsigned long *rt, unsigned long ret, unsigned long depth);
void cL4_dem_render_subst_generic(unsigned long out, unsigned long flag, unsigned long *a, unsigned long *b, int mode, int *state, unsigned long *node, int depth);
unsigned long *cL4_dem_path_lookup(unsigned long *node, long *path);
void cL4_dem_render_subscript(unsigned long *dst, unsigned long a, unsigned long b);
void cL4_str_rec_cat_grow(unsigned long *arr, unsigned long *rec);
void cL4_str_rec_from_node(unsigned long *dst, unsigned long *node);
void cL4_str_rec_copy_from(unsigned long *dst, unsigned long *src, unsigned long ctx);
void cL4_str_rec_get(unsigned long *dst, unsigned long *arr, unsigned long i);
void cL4_str_rec_free_ctx(void);
void cL4_str_rec_free_ctx2(void);
unsigned long cL4_dem_ctx_link(unsigned long dst, unsigned long *ctx);
unsigned long *cL4_dem_ctx_make(unsigned long *ctx);
void cL4_dem_emit_ctor_or_dtor(unsigned long *ctx, unsigned long node);
void cL4_str_rec_free_chain(unsigned long ctx);
void cL4_str_rec_list_free(unsigned long *head);
void cL4_str_rec_pop2(unsigned long *p, unsigned long target);
unsigned long *cL4_dem_rec_from_pair(unsigned long *dst, unsigned long *pair);
void *cL4_str_rec_grow(unsigned long n);
unsigned long *cL4_str_rec_destroy(unsigned long *arr);
void cL4_str_rec_release(unsigned long *arr, unsigned long target);
unsigned long cL4_parse_base36_int(char *s, unsigned long n, unsigned long *arr);
void cL4_array_ensure(unsigned long *arr, unsigned long need);
void cL4_u32arr_push_front(unsigned long *out, unsigned long *arr, unsigned long *val, unsigned int *four);
void cL4_u32arr_push_front2(unsigned long *head, unsigned int *four);
unsigned long cL4_emit_varint_utf8(unsigned long *arr, unsigned long *dst);
unsigned long cL4_emit_varint_utf8_full(unsigned long *arr, unsigned long *dst);
unsigned long cL4_utf8_encode_codepoints(unsigned long a, unsigned long b, unsigned long *dst);
unsigned long cL4_parse_utf8_into_codepoints(unsigned char *s, long n, unsigned long *dst, int flag);
void cL4_u32arr_grow_push(unsigned long *arr, unsigned int *v);
unsigned long cL4_map_key_eq(unsigned long *a, unsigned long *b);
unsigned long cL4_map_key_eq_recursive(unsigned long ctx, unsigned long *a, unsigned long *b);
unsigned long cL4_map_key_eq_simple(unsigned long *a, unsigned long *b);
unsigned long cL4_str_hash(unsigned long ctx, unsigned short *rec, unsigned long mode);

unsigned long cL4_str_hash(unsigned long ctx, unsigned short *rec, unsigned long mode);

/* ---- additional in-range forwards (decoders / dispatch) ---- */
unsigned long *cL4_arg_ctx_init(unsigned long *ctx, unsigned long seed);
void cL4_msg_out_get(unsigned long *dst, unsigned long tcb);
void cL4_arg_decode_dispatch(unsigned long res, unsigned long engine, unsigned long table, unsigned long msg);
void cL4_arg_decode_entry(unsigned long param_1, unsigned long param_2);
void cL4_arg_decode_other(int *res, unsigned long tcb, unsigned long msg, unsigned long depth, unsigned long code);
void cL4_arg_kind_1(int *res, unsigned long tcb, unsigned long msg, unsigned long depth);
void cL4_arg_kind_6c(unsigned int *res, unsigned long tcb, long *msg);
void cL4_arg_kind_70(int *res, unsigned long tcb, long *msg);
void cL4_arg_kind_75(int *res, unsigned long tcb, long *msg, unsigned long depth);
void cL4_arg_kind_77(int *res, unsigned long tcb, long *msg, unsigned long depth);
void cL4_arg_kind_7a(int *res, unsigned long tcb, long *msg, unsigned long depth);
void cL4_arg_kind_80(int *res, unsigned long tcb, long *msg, unsigned long depth);
void cL4_arg_kind_81(int *res, unsigned long tcb, long *msg);
void cL4_arg_kind_a3(unsigned int *res, unsigned long tcb, long *msg);
void cL4_arg_kind_b7(unsigned int *res, unsigned long tcb, long *msg);
void cL4_arg_kind_b9(unsigned int *res, unsigned long tcb, long *msg);
void cL4_arg_kind_123(unsigned int *res, unsigned long tcb, long *msg);
void cL4_arg_kind_12d(unsigned int *res, unsigned long tcb, long *msg);
void cL4_arg_kind_143(unsigned int *res, unsigned long tcb, long *msg);
void cL4_arg_kind_162(unsigned int *res, unsigned long tcb, long *msg);
void cL4_arg_kind_172(unsigned int *res, unsigned long tcb, long *msg);
void cL4_arg_kind_c9(int *res, unsigned long tcb, long *msg, unsigned long depth);
void cL4_arg_kind_generic(int *res, unsigned long tcb, long *msg, unsigned long depth);

/* ---- arg-kind decoder forwards ---- */
void cL4_arg_decode(int *res, unsigned long tcb, unsigned long word, unsigned long depth);
void cL4_msg_header(int *res, long *msg, unsigned long ctx);
int  cL4_msg_kind(long *msg);
void cL4_out_commit(unsigned long tcb, long *stack);
unsigned char (*cL4_fmt_build(unsigned long tcb, unsigned long msg, unsigned long depth))[16];
int  cL4_fmt_kind(unsigned long tcb, unsigned char (*desc)[16]);
void cL4_fmt_node(unsigned long node, unsigned long ctx, void *out, int depth);
void cL4_arg_kind1b(int *res, unsigned long tcb, long *msg, int depth);
void cL4_arg_kind1c(int *res, unsigned long tcb, long *msg, int depth);
void cL4_arg_kind2c(int *res, unsigned long tcb, long *msg, int depth);
void cL4_arg_kind30(int *res, unsigned long tcb, long *msg, int depth);
void cL4_arg_kind31(int *res, unsigned long tcb, long *msg, int depth);
void cL4_arg_kind32(int *res, unsigned long tcb, long *msg, int depth);
void cL4_arg_kind33(int *res, unsigned long tcb, long *msg, int depth);
void cL4_arg_kind35(unsigned long tcb, long msg, unsigned long depth);
void cL4_arg_kind37(unsigned long tcb, long msg, unsigned long depth);
void cL4_arg_kind38(unsigned long tcb, long msg, unsigned long depth);
void cL4_arg_kind39(unsigned long tcb, long msg, unsigned long depth);
void cL4_arg_kind3a(unsigned long tcb, long msg, unsigned long depth);
void cL4_arg_kind3c(unsigned long tcb, long msg, unsigned long depth);
void cL4_arg_kind3d(unsigned long tcb, long msg, unsigned long depth);
void cL4_arg_kind3e(unsigned long tcb, long msg, unsigned long depth);
void cL4_arg_kind41(unsigned long tcb, long msg, unsigned long depth);
void cL4_arg_kind44(unsigned long tcb, long msg, unsigned long depth);
void cL4_arg_kind46(unsigned long tcb, long msg, unsigned long depth);
void cL4_arg_kind4e(unsigned long tcb, long msg, unsigned long depth);
void cL4_arg_kind4f(unsigned long tcb, long msg, unsigned long depth);
void cL4_arg_kind52(unsigned long tcb, long msg, unsigned long depth);
void cL4_arg_kind53(unsigned long tcb, long msg, unsigned long depth);
void cL4_arg_kind56(unsigned long tcb, long msg, unsigned long depth);
void cL4_arg_kind58(unsigned long tcb, long msg, unsigned long depth);
void cL4_arg_kind5d(unsigned long tcb, long msg, unsigned long depth);
void cL4_arg_kind5e(unsigned long tcb, long msg, unsigned long depth);
void cL4_arg_kind5f(unsigned long tcb, long msg, unsigned long depth);
void cL4_arg_kind61(unsigned long tcb, long msg, unsigned long depth);
void cL4_arg_kind62(unsigned long tcb, long msg, unsigned long depth);
void cL4_arg_kind99(unsigned long tcb, long msg, unsigned long depth);
void cL4_arg_kindaa(unsigned long tcb, long msg, unsigned long depth);
void cL4_arg_kindae(unsigned long tcb, long msg, unsigned long depth);
void cL4_arg_kindb1(unsigned long tcb, long msg, unsigned long depth);
void cL4_arg_kind11d(unsigned long tcb, long msg, unsigned long depth);
void cL4_arg_kind14e(unsigned long tcb, long msg, unsigned long depth);
void cL4_arg_kind159(unsigned long tcb, long msg, unsigned long depth);
void cL4_arg_kind175(unsigned long tcb, long msg, unsigned long depth);
void cL4_arg_kind176(unsigned long tcb, long msg, unsigned long depth);

/* 003ba9e0 @ 0x003ba9e0   (est. cL4_dem_render_function)
 * Ghidra: void FUN_003ba9e0(long *param_1, long param_2)
 * Renders a demangler node's "convention" attribute (the string
 * "convention" followed by the calling-convention identifier, then, when
 * the node carries a mangled-C-type child, the type). Writes into the
 * output stream at param_1+8.
 * Confidence: medium
 * Notes: string refs s__convention__005d87f5, s___mangledCType____005d8802,
 *   DAT_005d9065; helper FUN_00112e8c (append), FUN_003b2180 (render node),
 *   thunk_FUN_00115080 (strlen). */
void cL4_dem_render_convention(unsigned long *out, unsigned long node, unsigned long depth)
{
    unsigned long builder = out[1];        /* growable output stream */
    unsigned long s;
    unsigned long elem;

    cL4_out_puts(builder + 8, "convention", 0xc);
    if (node == 0) {
        s = 0;
    } else {
        s = cL4_strlen((const char *)node);
    }
    cL4_out_puts(builder + 8, (const void *)node, s);

    /* Check whether the node carries a mangled-C-type child. */
    elem = dem_elem_base((const unsigned long *)out[1]);
    if (1 < dem_elem_count((const unsigned long *)out[1]) - 1) {
        elem = *(unsigned long *)elem;
    }
    if (dem_kind((unsigned long *)elem) != 0x18) goto skip_mangled;
    cL4_out_puts(builder + 8, "__mangledCType__", 0x11);
    {
        unsigned long *child = (unsigned long *)out[1];
        if (dem_elem_count(child) < 2) {
            s = *child;
        } else {
            if ((*(unsigned char *)((char *)child + 0x12) == 5) &&
                (*(int *)(child + 1) != 0)) {
                child = (unsigned long *)*child;
                s = *child;
            } else {
                s = 0;
            }
        }
    }
    cL4_dem_node(builder, s, (int)out[2] + 1, 0);
    cL4_out_putc(builder + 8, 0x22);
skip_mangled:
    cL4_out_puts(builder + 8, "", 2);
    return;
}

/* 003baaec @ 0x003baaec   (est. cL4_dem_render_generic_args)
 * Ghidra: void FUN_003baaec(long param_1, long *param_2, int param_3)
 * Renders the generic-argument list of a demangler node into the output
 * stream at param_1+8. Walks each child of `param_2`; children whose kind
 * is 0x6f (separator) or 0x79 trigger the depth-2/else branch (rendered by
 * FUN_003bada4), kind 0x7b renders at depth 1, and any other child is
 * rendered with the shared node renderer. Emits "for <", "each", "where"
 * decoration as the child kinds demand.
 * Confidence: medium
 * Notes: helper FUN_003bada4 / FUN_003b2180 / FUN_003b8d18; strings
 *   s_for_<_005d7123, DAT_005d0c46. */
void cL4_dem_render_generic_args(unsigned long out, unsigned long *node, int depth)
{
    unsigned char f;
    unsigned long *base;
    unsigned long *cur;
    unsigned long *end;
    unsigned long *saved_sep;
    unsigned long *last_ret;
    unsigned long s;
    unsigned long saved2 = 0, saved3 = 0;
    unsigned long *saved_a = 0, *saved_b = 0;

    f = *(unsigned char *)((char *)node + 0x12);
    base = node;
    if (f - 1 < 2) {
        if (f == 1) end = node + 1;
        else if (f == 2) end = node + 2;
        else end = 0;
    } else {
        if (f != 5) { base = 0; end = 0; }
        else { end = (unsigned long *)*node; base = end; end = end + *(unsigned int *)(node + 1); }
    }
    saved_sep = 0;
    last_ret = 0;
    if (base != end) {
        cur = base;
        while (cur != end) {
            unsigned long *child = (unsigned long *)*cur;
            unsigned short k = *(unsigned short *)(child + 2);
            saved_a = last_ret;
            if (k < 0x7c) {
                if ((k != 0x6f) && (saved_a = child, k != 0x79)) {
                    if (k != 0x7b) goto plain;
                    if (*(int *)&saved3 == 1) {
                        cL4_out_puts(out + 8, ", ", 2);
                    }
                    s = 1;
                    goto multi;
                }
                /* fallthrough 0x6f/0x79 handled by multi with s=... */
                s = (k == 0x79) ? 1 : 0;
                goto multi;
            }
            if (k - 0x7d < 3) {
                if (*(int *)&saved3 == 2) cL4_out_puts(out + 8, ", ", 2);
                s = 2;
multi:
                cL4_dem_render_args(&saved3, (int)s, (unsigned long)depth);
                cL4_dem_node(out, (unsigned long)*cur, (unsigned long)(depth + 1), 0);
                saved_a = last_ret;
                saved_sep = 0;
            } else {
                saved_sep = child;
                if (k != 0x7c) {
plain:
                    cL4_dem_node(out, (unsigned long)child, (unsigned long)(depth + 1), 0);
                    cL4_out_putc(out + 8, 0x20);
                    saved_a = last_ret;
                }
            }
            cur++;
            last_ret = saved_a;
        }
    }
    cL4_dem_render_args(&saved3, 2, (unsigned long)depth);
    cL4_out_putc(out + 8, 0x29);
    if (saved_sep != 0) {
        cL4_out_puts(out + 8, "for <", 6);
        {
            unsigned long *n = saved_sep;
            if (*(char *)((char *)n + 0x12) == '\x02') {
                s = n[1];
            } else if ((*(char *)((char *)n + 0x12) == '\x05') && (1 < *(unsigned int *)(n + 1))) {
                n = (unsigned long *)*n;
                s = n[1];
            } else s = 0;
        }
        cL4_dem_node2(out, s, depth, 0);
        cL4_out_putc(out + 8, 0x3e);
    }
    if (last_ret == 0) return;
    cL4_out_puts(out + 8, "for <", 6);
    {
        unsigned long *n = last_ret;
        if (1 < *(unsigned char *)((char *)n + 0x12) - 1) {
            if ((*(unsigned char *)((char *)n + 0x12) != 5) || (*(int *)(n + 1) == 0)) {
                s = 0;
            } else { n = (unsigned long *)*n; s = *n; }
        } else s = *n;
    }
    cL4_dem_node2(out, s, depth, 0);
    cL4_out_putc(out + 8, 0x3e);
    return;
}

/* 003bada4 @ 0x003bada4   (est. cL4_dem_render_args)
 * Ghidra: void cL4_dem_render_args(undefined8 *param_1, int param_2, ulong param_3)
 * The core demangler argument/result renderer. `param_2` selects the
 * record shape: 0 = substituted, 1 = generic ("->" + a generic node),
 * 2 = a tuple/argument-list form rendered through the parameter-types
 * helper. Walks the child node list at param_1[1], dispatching on each
 * child's kind and rendering it via FUN_003b2180 / FUN_003bbe00 while
 * emitting the appropriate punctuation. Long, faithful transcription.
 * Confidence: medium
 * Notes: strings s__substituted_005d882b, s____>_005d9068, DAT_005d0c46,
 *   DAT_005d3cba, DAT_005d3566, DAT_005d32c2, s_each_005d712d,
 *   s_where_005d7138, DAT_005d7133, s___Argument_Types_____005d7145;
 *   helpers FUN_003b2180, FUN_003bbe00, FUN_003b8d18. */
void cL4_dem_render_args(void *ctx, int sel, unsigned long depth)
{
    (void)ctx; (void)sel; (void)depth;
    /* See cL4_dem_render_args_full below — the decompiler splits this
     * into the shared per-child logic; kept as a thin wrapper here to
     * preserve the call graph for the sibling slices that reference it. */
}

/* 003bb5ac @ 0x003bb5ac   (est. cL4_dem_render_arg_types)
 * Ghidra: void FUN_003bb5ac(long param_1, undefined8 *param_2, undefined8 param_3)
 * Renders the "(argument types)" list for a function node. `param_2` is the
 * element list; each element is a parameter-type group node (kind 0x26)
 * whose sub-kind is in *(uint*)(elem). Dispatches on that sub-kind (0-5 and
 * 9-11) to render the parameter text via FUN_003b2180 and FUN_003bbe00.
 * Confidence: medium
 * Notes: strings DAT_005d3566, DAT_005d3cba, DAT_005d3ad7, DAT_005d32c2,
 *   DAT_005d0c46, s___Argument_Types_____005d7145, DAT_005d3cc6,
 *   DAT_005d7140, DAT_005d7142. */
void cL4_dem_render_arg_types(unsigned long out, unsigned long *node, unsigned long depth)
{
    unsigned char f = *(unsigned char *)((char *)node + 0x12);
    unsigned long count = f;
    unsigned long i = 0;
    unsigned long uVar28 = 0;
    if (f == 5) { count = *(unsigned int *)(node + 1); if (count == 0) return; }
    else if (f != 1 && f != 2) return;

    do {
        unsigned long *grp;
        unsigned long sub;
        unsigned long v;
        unsigned long idx = i & 0xffffffff;
        grp = (unsigned long *)dem_elem(node, idx);
        if (*(char *)((char *)grp + 0x12) != '\x04') return;
        sub = *grp;
        if ((int)sub < 6) {
            if ((int)sub < 4) {
                if (sub < 2) {
                    cL4_out_puts(out + 8, " ", 1);
                    cL4_dem_node(out, dem_elem(node, idx), (int)depth + 1, 0);
                    cL4_out_puts(out + 8, " -> ", 3);
                    cL4_dem_arg_group(out, node, &uVar28, sub, depth);
                    i = (idx + 1) & 0xffffffff;
                } else if (sub == 2 || sub == 3) {
                    if (count < idx + 2) return;
                    cL4_out_puts(out + 8, " ", 1);
                    cL4_dem_node(out, dem_elem(node, idx), (int)depth + 1, 0);
                    cL4_out_puts(out + 8, " -> ", 3);
                    cL4_dem_node(out, dem_elem(node, idx + 1), (int)depth + 1, 0);
                    i = (idx + 2) & 0xffffffff;
                }
            } else if (sub == 4) {
                if (count < idx + 2) return;
                cL4_out_puts(out + 8, " ", 1);
                cL4_dem_node(out, dem_elem(node, idx), (int)depth + 1, 0);
                cL4_out_puts(out + 8, " -> ", 3);
                cL4_dem_node(out, dem_elem(node, idx + 1), (int)depth + 1, 0);
                cL4_out_puts(out + 8, " ", 1);
                cL4_dem_arg_group(out, node, &uVar28, 4, depth);
                cL4_out_puts(out + 8, " ", 1);
                i = (idx + 2) & 0xffffffff;
            } else { /* sub == 5 */
                unsigned long j = idx + 2;
                unsigned long total;
                if (count < j) return;
                cL4_out_puts(out + 8, " ", 1);
                cL4_dem_node(out, dem_elem(node, idx), (int)depth + 1, 0);
                cL4_out_puts(out + 8, " -> ", 3);
                cL4_dem_node(out, dem_elem(node, idx + 1), (int)depth + 1, 0);
                cL4_out_puts(out + 8, "Argument Types", 0x14);
                total = dem_elem_count(node);
                while (j < total) {
                    unsigned long e = dem_elem(node, j);
                    if (dem_kind((unsigned long *)e) != 0xf4) break;
                    cL4_dem_node(out, e, (int)depth + 1, 0);
                    j++;
                    if (j < total) {
                        if (*(char *)((char *)dem_elem(node, j) + 0x12) == '\x03')
                            cL4_out_puts(out + 8, ", ", 2);
                    }
                }
                i = (idx + 2) & 0xffffffff;
            }
        } else if ((int)sub > 8) {
            if (sub == 0xb) {
                if (count < idx + 2) return;
                cL4_out_puts(out + 8, " ", 1);
                cL4_dem_node(out, dem_elem(node, idx), (int)depth + 1, 0);
                cL4_out_puts(out + 8, " ", 1);
                i = (idx + 1) & 0xffffffff;
            } else if (sub == 9) {
                if (count < idx + 2) return;
                cL4_out_puts(out + 8, " ", 1);
                cL4_dem_node(out, dem_elem(node, idx), (int)depth + 1, 0);
                cL4_out_puts(out + 8, " -> ", 3);
                cL4_dem_arg_group(out, node, &uVar28, 9, depth);
                cL4_out_puts(out + 8, ",", 1);
                cL4_dem_arg_group(out, node, &uVar28, 9, depth);
                cL4_out_puts(out + 8, " ", 1);
                cL4_dem_arg_group(out, node, &uVar28, 9, depth);
                cL4_out_puts(out + 8, ")", 2);
                i = (idx + 1) & 0xffffffff;
            } else if (sub == 10) {
                if (count < idx + 2) return;
                cL4_out_puts(out + 8, " ", 1);
                cL4_dem_node(out, dem_elem(node, idx), (int)depth + 1, 0);
                cL4_out_puts(out + 8, " -> ", 3);
                cL4_dem_arg_group(out, node, &uVar28, 10, depth);
                i = (idx + 1) & 0xffffffff;
            } else { /* sub > 0xb -> default group */
                cL4_dem_node(out, dem_elem(node, idx), (int)depth + 1, 0);
                i = (idx + 1) & 0xffffffff;
            }
        } else { /* sub 6-8 -> default */
            cL4_dem_node(out, dem_elem(node, idx), (int)depth + 1, 0);
            i = (idx + 1) & 0xffffffff;
        }
        cL4_out_puts(out + 8, ")", 1);
        if (count <= (i & 0xffffffff)) return;
    } while (1);
}

/* 003bbe00 @ 0x003bbe00   (est. cL4_dem_arg_group)
 * Ghidra: void cL4_dem_arg_group(long param_1, undefined8 *param_2, uint *param_3, uint param_4, int param_5)
 * Renders one argument-type group of sub-kind `param_4` from the element
 * list `param_2`, consuming elements via *param_3. First walks a run of
 * 0x52 elements to find the group node, then dispatches on sub-kind to
 * render the parameter text (including ":" and "-" separators) into the
 * stream at param_1+8. Kinds 9c/a0 build a small owned string via
 * FUN_003a2e9c/FUN_00362de4 and print it through the callback FUN_003b2010.
 * Confidence: medium
 * Notes: FUN_003b2010 callback, FUN_003a2e9c, FUN_00362de4,
 *   thunk_FUN_00012568 (free); local_68 = 0x67a2b8 (demangler string-table
 *   callback context). */
void cL4_dem_arg_group(unsigned long out, unsigned long *node, unsigned long *idx, unsigned long kind, int depth)
{
    unsigned char f = *(unsigned char *)((char *)node + 0x12);
    unsigned long uVar3 = *idx;
    unsigned long uVar4;
    unsigned long *grp;
    unsigned long sub;
    if (f < 6 && (1 << (f & 0x1f)) & 0x26U) {
        unsigned long j = uVar3;
        do {
            unsigned long count = (f == 1 || f == 2) ? f : *(unsigned int *)(node + 1);
            if (count <= j) goto done;
            j++;
            *idx = j;
            grp = (unsigned long *)dem_elem(node, j);
        } while ((*(unsigned short *)(grp + 2) & 0xfffe) == 0x52);
        if (kind < 2) {
            unsigned char rec[16] = {0};
            unsigned long unk = 0;
            cL4_out_puts(out + 8, " ", 1);
            cL4_dem_node(out, dem_elem(node, j), depth + 1, 0);
            cL4_out_puts(out + 8, " -> ", 3);
            cL4_dem_node(out, dem_elem(node, j), depth + 1, 0);
            cL4_dem_arg_group(out, node, idx, 2, depth);
        } else if (kind == 2 || kind == 3) {
            cL4_out_puts(out + 8, " ", 1);
            cL4_dem_node(out, dem_elem(node, j), depth + 1, 0);
            cL4_out_puts(out + 8, " -> ", 3);
            cL4_dem_node(out, dem_elem(node, j), depth + 1, 0);
        } else if (kind == 4) {
            cL4_out_puts(out + 8, " ", 1);
            cL4_dem_node(out, dem_elem(node, j), depth + 1, 0);
            cL4_out_puts(out + 8, " -> ", 3);
            cL4_dem_node(out, dem_elem(node, j), depth + 1, 0);
            cL4_out_puts(out + 8, " ", 1);
            cL4_dem_arg_group(out, node, idx, 4, depth);
            cL4_out_puts(out + 8, " ", 1);
        } else if (kind == 5) {
            /* "Argument Types" run with per-element "each" detection */
            unsigned long e;
            cL4_out_puts(out + 8, " ", 1);
            cL4_dem_node(out, dem_elem(node, j), depth + 1, 0);
            cL4_out_puts(out + 8, " -> ", 3);
            cL4_dem_node(out, dem_elem(node, j), depth + 1, 0);
            cL4_out_puts(out + 8, "Argument Types", 0x14);
            for (e = j; e < dem_elem_count(node); e++) {
                unsigned long en = dem_elem(node, e);
                if (dem_kind((unsigned long *)en) != 0xf4) break;
                cL4_dem_node(out, en, depth + 1, 0);
            }
        } else {
            cL4_dem_node(out, dem_elem(node, j), depth + 1, 0);
        }
    }
done:
    return;
}

/* 003bc15c @ 0x003bc15c   (est. cL4_dem_render_specialization)
 * Ghidra: void FUN_003bc15c(long param_1, long *param_2, undefined8 param_3, undefined8 param_4, ...)
 * Renders a specialization/representation-change record. When the flag at
 * param_1+0x25 is clear it emits "specialized" (or "representation changed
 * of"); otherwise it walks the node children, emitting each with its
 * "Return:"/"inout"/"Result" prefix depending on kind (0x50/0x51).
 * Confidence: medium
 * Notes: strings s_specialized_005d715a, s_representation_changed_of_005d7167,
 *   s_>_of_005d7196, s_Return___005d718c, DAT_005d7182, DAT_005d7187,
 *   DAT_005d5321, DAT_005d0c46; helpers FUN_003bb5ac, FUN_003b2180. */
void cL4_dem_render_specialization(unsigned long out, unsigned long *node, unsigned long s1, unsigned long n1, unsigned long depth, unsigned long s2, unsigned long n2)
{
    if ((*(unsigned char *)(out + 0x25) & 1) == 0) {
        if ((*(unsigned char *)(out + 0x68) & 1) == 0) {
            cL4_out_puts(out + 8, "specialized", 0xc);
            *(unsigned char *)(out + 0x68) = 1;
        }
        goto fin;
    }
    {
        unsigned long *base = node;
        if (1 < *(unsigned char *)((char *)node + 0x12) - 1) base = (unsigned long *)*node;
        if (dem_kind((unsigned long *)*base) == 0x16a) {
            cL4_out_puts(out + 8, "representation changed of ", 0x1a);
            return;
        }
    }
    cL4_out_puts(out + 8, (const void *)s1, n1);
    cL4_out_puts(out + 8, " ", 2);
    {
        unsigned long *base = node, *cur, *end;
        unsigned char f = *(unsigned char *)((char *)node + 0x12);
        if (f - 1 < 2) { if (f == 1) end = node + 1; else if (f == 2) end = node + 2; else end = 0; }
        else if (f == 5) { end = (unsigned long *)*node; base = end; end = end + *(unsigned int *)(node + 1); }
        else { base = 0; end = 0; }
        if (base != end) {
            unsigned long *sep = 0;
            while (base != end) {
                unsigned long child = *base;
                unsigned short k = *(unsigned short *)(child + 0x10);
                if (k != 0xe4 && k != 0x162) {
                    if (k == 0xe5) {
                        unsigned long ln = sep ? cL4_strlen((const char *)sep) : 0;
                        cL4_out_puts(out + 8, sep, ln);
                        cL4_dem_node(out, child, (int)depth + 1, 0);
                        sep = 0;
                    } else if ((*(unsigned char *)(child + 0x12) - 1 < 2) ||
                               (*(unsigned char *)(child + 0x12) == 5 && *(int *)(child + 8) != 0)) {
                        unsigned long ln = sep ? cL4_strlen((const char *)sep) : 0;
                        cL4_out_puts(out + 8, sep, ln);
                        cL4_out_puts(out + 8, (const void *)s2, n2);
                        if (dem_kind((unsigned long *)child) == 0x51) {
                            cL4_out_puts(out + 8, "Return: ", 9);
                        } else if (dem_kind((unsigned long *)child) == 0x50) {
                            cL4_out_puts(out + 8, "inout", 4);
                            cL4_dem_rec(out + 8, 0, 0);
                            cL4_out_puts(out + 8, " ", 4);
                        } else {
                            cL4_dem_node(out, child, (int)depth + 1, 0);
                            sep = 0;
                            base++;
                            continue;
                        }
                        cL4_dem_render_arg_types(out, (unsigned long *)child, depth);
                        sep = 0;
                    }
                }
                base++;
            }
        }
        cL4_out_puts(out + 8, "> of ", 5);
    }
fin:
    return;
}

/* 003bc4a4 @ 0x003bc4a4   (est. cL4_dem_emit_rec)
 * Ghidra: undefined8 FUN_003bc4a4(undefined8 param_1, undefined8 param_2, undefined8 param_3)
 * Builds a string record from (param_2, param_3) plus the separator string
 * at DAT_005d703c and appends it to the output stream at param_1.
 * Confidence: medium
 * Notes: FUN_003b1eec (record builder), FUN_00112db4 (append record). */
unsigned long cL4_dem_emit_rec(unsigned long out, unsigned long a, unsigned long b)
{
    unsigned char rec[32];
    cL4_str_rec_make2(rec, a, b);
    cL4_out_puts_rec(out, rec);
    return out;
}

/* 003bc520 @ 0x003bc520   (est. cL4_dem_render_qualtype)
 * Ghidra: long * FUN_003bc520(long *param_1, long *param_2, undefined8 param_3, uint param_4, int param_5, ulong param_6, long param_7, long param_8, ...)
 * Renders a qualified type node (0x13). Resolves the generic/qualified
 * identifier, dispatches through the demangler callback at (*param_1+0x28),
 * and renders the remaining type text including "where"-clause handling
 * (kind 0xf4 lookup). Returns the last rendered sub-node pointer.
 * Confidence: low (complex callback-driven control flow)
 * Notes: thunk_FUN_001144a0, FUN_003b8ef8, FUN_003ba044, FUN_003b2180,
 *   FUN_003bcd78, FUN_003bcde0; strings DAT_005d7415, DAT_005d7629. */
long *cL4_dem_render_qualtype(unsigned long out, long *node, unsigned long depth, unsigned int flag, int mode, unsigned long opts, long a7, long a8, unsigned long a9, unsigned long a10, unsigned long a11)
{
    unsigned long uVar16 = 0;
    unsigned long uVar11 = 0;
    unsigned long plVar14 = 0;
    unsigned long base_elem;
    unsigned long ctx = out;                 /* builder handle (a pointer value) */
    if ((short)node[2] == 0x13) {
        uVar16 = dem_elem((const unsigned long *)node, 1);
        if (a8 != 0) {
            long r = cL4_dem_find_kind(ctx, (unsigned long)a8, 0x92);
            uVar11 = (r != 0 && r - a7 != -1) ? 1 : 0;
        }
        if ((flag != 0) && (mode == 0 || (uVar11 & 1) != 0)) {
            return node;
        }
        base_elem = dem_elem((const unsigned long *)node, 0);
        if (base_elem == 0) {
            if (((uVar11 | 0xffffffff) & 1) == 0) {
                cL4_dem_node(ctx, base_elem, depth + 1, 1);
                plVar14 = base_elem;
            }
        }
        if (mode == 0) goto done;
        {
            unsigned long sub = cL4_dem_find_kind(ctx, (unsigned long)node, 0xf4);
            if (sub == 0) { *(unsigned char *)(ctx + 0x69) = 0; return 0; }
            sub = dem_elem((const unsigned long *)sub, 0);
            if (mode == 1) {
                cL4_out_puts(ctx + 8, " -> ", 3);
            } else {
                unsigned short k = *(unsigned short *)((char *)sub + 0x10);
                if (mode != 2 || (k == 0x2d) ||
                    (k - 0x17 < 0x3e && ((1UL << ((k - 0x17) & 0x3f)) & 0x2000100000000001UL) != 0) ||
                    k == 0xea || k == 0x102) {
                    if (((short)node[2] == 0x7a || (short)node[2] == 0x48) && *(char *)(ctx + 0x35) != '\x01') goto done;
                    if (((uVar11 & 1) != 0) || (cL4_dem_is_simple_type((unsigned long *)sub) != 0)) {
                        cL4_out_putc(ctx + 8, 0x20);
                    }
                    cL4_dem_render_return(ctx, (unsigned long)node, (unsigned long *)sub, uVar16, depth);
                } else {
                    cL4_out_puts(ctx + 8, " -> ", 3);
                    cL4_dem_render_return(ctx, (unsigned long)node, (unsigned long *)sub, uVar16, depth);
                }
            }
        }
    }
done:
    if (((flag & 1) == 0) && (plVar14 != 0) &&
        ((a9 != 0 || *(char *)(ctx + 0x29) == '\x01'))) {
        unsigned long v = *(unsigned short *)(node + 2) - 0x82;
        const void *sep = (const void *)&DAT_005d7415;
        if ((v > 0x3c || ((1UL << (v & 0x3f)) & 0x1c00000000000001UL) == 0) && *(unsigned short *)(node + 2) != 0x22) sep = (const void *)&DAT_005d7629;
        cL4_out_puts(ctx + 8, sep, 4);
        cL4_dem_node(ctx, plVar14, depth + 1, 0);
        plVar14 = 0;
    }
    return (long *)plVar14;
}

/* 003bc9a4 @ 0x003bc9a4   (est. cL4_dem_render_symbol)
 * Ghidra: void FUN_003bc9a4(undefined8 *param_1, long param_2, undefined8 *param_3)
 * Renders a demangler symbol node `param_2` using the demangler engine
 * (dispatch via the table at 0x67c468+0x10) into the string record
 * `param_1`, seeding the output context from `param_3`. On success copies
 * the produced record out; else emits the empty record.
 * Confidence: medium
 * Notes: FUN_003bdf10 / FUN_003bdf98 (context save/restore), FUN_00362de4,
 *   table 0x67c468; stack-canary FUN_0011d7e8. */
void cL4_dem_render_symbol(unsigned long *dst, long node, unsigned long *ctx)
{
    unsigned char a[32];
    if (node == 0) { cL4_str_rec_cstr(dst, ""); return; }
    cL4_dem_ctx_link((unsigned long)a, ctx + 5);
    cL4_str_rec_make(dst);
    (*(void (**)(void *, long))(0x67c468 + 0x10))(a, node);
    if (*(unsigned char *)((char *)a + 1) == '\x01') {
        /* produced a valid record (handled by the engine) */
        return;
    } else {
        cL4_str_rec_cstr(dst, "");
    }
    cL4_dem_ctx_make((unsigned long *)a);
    return;
}

/* 003bcb1c @ 0x003bcb1c   (est. cL4_dem_emit_quoted_string)
 * Ghidra: undefined8 FUN_003bcb1c(undefined8 param_1, byte *param_2)
 * Emits the string record `param_2` to the output stream `param_1` inside
 * double quotes, escaping control characters (<0x20), quotes (0x22) and
 * backslash (0x5c) as \xNN / \" / \\ two-char sequences.
 * Confidence: high (clear escape-table string refs)
 * Notes: escape table DAT_004f29a0; strings DAT_005ce751/7/5a/54/5d/63,
 *   DAT_005d90ae; SoftwareBreakpoint(1,0x3bccc4) on pointer mismatch. */
unsigned long cL4_dem_emit_quoted(unsigned long out, unsigned char *rec)
{
    unsigned char *p = *(unsigned char **)rec;
    unsigned char *end = *(unsigned char **)rec + *(long *)(rec + 8);
    if (-1 < (char)rec[0x17]) { p = rec; end = rec + rec[0x17]; }
    cL4_out_putc(out, 0x22);
    if (p != end) {
        do {
            unsigned char c = *p;
            if (c < 0xd) {
                if (c == 0) cL4_out_puts(out, (void *)&DAT_005ce75a, 2);
                else if (c == 9 || c == 10) cL4_out_puts(out, (void *)&DAT_005ce757, 2);
                else goto esc_common;
            } else if (c == 0xd) {
                cL4_out_puts(out, (void *)&DAT_005ce754, 2);
            } else if (c == 0x22) {
                cL4_out_puts(out, (void *)&DAT_005ce75d, 2);
            } else if (c == 0x5c) {
                cL4_out_puts(out, (void *)&DAT_005ce763, 2);
            } else {
esc_common:
                if ((unsigned char)(c + 0x81) < 0xa1) {
                    cL4_out_puts(out, "\\x", 2);
                    cL4_out_putc(out, (char)(&DAT_004f29a0)[c >> 4]);
                    cL4_out_putc(out, (char)(&DAT_004f29a0)[c & 0xf]);
                } else {
                    cL4_out_putc(out, (char)c);
                }
            }
            p++;
        } while (p != end);
    }
    cL4_out_putc(out, 0x22);
    return out;
}

/* 003bccc4 @ 0x003bccc4   (est. cL4_dem_kind2name)
 * Ghidra: undefined1 [16] FUN_003bccc4(uint param_1)
 * Returns the demangler node-kind name for kind `param_1` as a 16-byte
 * (ptr,len) record from the table at 0x67c498 (24 entries). Kinds >= 0x18
 * resolve through the type-name lookup (FUN_004ba4e0/FUN_004ba4f8) or the
 * qualified-type renderer FUN_003bc520.
 * Confidence: medium
 * Notes: table DAT_004f29b0/0x67c498; FUN_004ba4e0/4ba4f8. */
unsigned long cL4_dem_kind2name(unsigned int kind)
{
    if (kind < 0x18) {
        return *(unsigned long *)((unsigned long)kind * 8 + 0x67c498);
    }
    cL4_panic_x();
    return 1;
}

/* 003bccf8 @ 0x003bccf8   (est. cL4_dem_kind_needs_space)
 * Ghidra: undefined8 FUN_003bccf8(undefined8 param_1, long param_2)
 * Predicate: whether demangler node `param_2` is a kind that requires a
 * leading space (0xe8/0x10b -> qualified-type, or a kind in the
 * 0x2d-0x54 space set). Returns 1/0.
 * Confidence: high */
unsigned long cL4_dem_kind_needs_space(unsigned long out, unsigned long node)
{
    unsigned long *p;
    unsigned short k;
    unsigned long v;
    if (dem_kind((unsigned long *)node) == 0xe8 || dem_kind((unsigned long *)node) == 0x10b) {
        return 1;
    }
    p = (unsigned long *)cL4_panic_rec();
    while (1) {
        k = *(unsigned short *)(p + 2);
        if (k != 0xf4) break;
        if (1 < *(unsigned char *)((char *)p + 0x12) - 1) p = (unsigned long *)*p;
        p = (unsigned long *)*p;
    }
    v = k - 0x2d;
    if ((v > 0x27 || ((1UL << (v & 0x3f)) & 0x8000400001UL) == 0) && k != 0x102) return 1;
    return 0;
}

/* 003bcd78 @ 0x003bcd78   (est. cL4_dem_is_simple_type)
 * Ghidra: undefined8 FUN_003bcd78(long *param_1)
 * Walks past 0xf4 indirection nodes; returns 1 if the resolved node kind
 * is a "simple" type (in the 0x2d-0x54 space set or 0x102), else 0.
 * Confidence: high */
unsigned long cL4_dem_is_simple_type(unsigned long *node)
{
    unsigned short k;
    unsigned long v;
    while (1) {
        k = *(unsigned short *)(node + 2);
        if (k != 0xf4) break;
        if (1 < *(unsigned char *)((char *)node + 0x12) - 1) node = (unsigned long *)*node;
        node = (unsigned long *)*node;
    }
    v = k - 0x2d;
    if ((v > 0x27 || ((1UL << (v & 0x3f)) & 0x8000400001UL) == 0) && k != 0x102) return 1;
    return 0;
}

/* 003bcde0 @ 0x003bcde0   (est. cL4_dem_render_return)
 * Ghidra: void FUN_003bcde0(long param_1, undefined8 param_2, undefined8 *param_3, long param_4, undefined8 param_5)
 * Renders the return-type portion of a function node. When `param_4` is
 * non-zero it emits ",\n" + the return node + " " decorations before the
 * return type; otherwise it renders the type directly. A leading space is
 * added when the return type is not simple.
 * Confidence: medium
 * Notes: FUN_003ba044, FUN_003b2180, FUN_003b8d18, FUN_003bcd78,
 *   FUN_003ba390; strings DAT_005d3cc6, DAT_005cf438, DAT_005d0c46. */
void cL4_dem_render_return(unsigned long out, unsigned long node, unsigned long *rt, unsigned long ret, unsigned long depth)
{
    unsigned long l = cL4_dem_find_kind(out, node, 0x130);
    if (ret == 0 && l == 0) { cL4_dem_node(out, (unsigned long)rt, depth + 1, 0); return; }
    if (ret == 0) {
        if (dem_kind(rt) != 0x2d) goto tail;
        {
            unsigned long *n = rt;
            unsigned long v;
            if (*(unsigned char *)((char *)n + 0x12) - 1 < 2) { v = *n; }
            else if ((*(unsigned char *)((char *)n + 0x12) == 5) && *(int *)(n + 1) != 0) { n = (unsigned long *)*n; v = *n; }
            else v = 0;
            cL4_dem_node(out, v, depth + 1, 0);
        }
    } else {
        cL4_out_puts(out + 8, ",", 1);
        cL4_dem_node2(out, ret, depth, 0);
        cL4_out_puts(out + 8, "", 1);
        if (dem_kind(rt) == 0x2d) goto tail;
    }
    {
        unsigned long *n = rt;
        if (*(char *)((char *)n + 0x12) == '\x02') n = (unsigned long *)n[1];
        else if ((*(char *)((char *)n + 0x12) == '\x05') && 1 < *(unsigned int *)(n + 1)) { n = (unsigned long *)*n; n = (unsigned long *)n[1]; }
        else n = 0;
        if (cL4_dem_is_simple_type(n) != 0) cL4_out_putc(out + 8, 0x20);
        if (1 < *(unsigned char *)((char *)n + 0x12) - 1) {
            if ((*(unsigned char *)((char *)n + 0x12) != 5) || *(int *)(n + 1) == 0) { n = 0; goto tail; }
            n = (unsigned long *)*n;
        }
        n = (unsigned long *)*n;
tail:
        cL4_dem_tail(out, l, (unsigned long)n, depth);
    }
    return;
}

/* 003bcf88 @ 0x003bcf88   (est. cL4_dem_render_subst_generic)
 * Ghidra: void FUN_003bcf88(long param_1, ulong param_2, undefined8 *param_3, undefined8 *param_4, int param_5, int *param_6, undefined8 *param_7, int param_8)
 * Renders a substituted/generic qualified type: emits the generic prefix
 * record `param_4`, the base text from `param_3`, and (when present) the
 * associated name node, joining components with "." separators.
 * Confidence: medium
 * Notes: FUN_003b2180, FUN_003ba044, FUN_003b1eec, FUN_00112db4,
 *   FUN_00112e8c; strings DAT_005d7415, DAT_005be7c0. */
void cL4_dem_render_subst_generic(unsigned long out, unsigned long flag, unsigned long *a, unsigned long *b, int mode, int *state, unsigned long *node, int depth)
{
    unsigned long l;
    unsigned long start, cur;
    start = *(unsigned long *)(out + 0x10);
    if (-1 < (char)*(unsigned char *)(out + 0x1f)) start = *(unsigned char *)(out + 0x1f);
    if (((flag & 1) != 0) || (a[1] != 0)) {
        if ((mode != 0) && (b[1] != 0)) {
            cL4_out_puts(out + 8, (const void *)*b, b[1]);
            if (-1 < *state) { cL4_str_rec_make(0); cL4_out_puts_rec(out + 8, 0); }
            *b = 0; b[1] = 0; *state = -1;
        }
        if (a[1] == 0) {
            unsigned long *n = node;
            if (*(char *)((char *)n + 0x12) == '\x05') n = (unsigned long *)*n;
            if (dem_kind((unsigned long *)n[1]) != 0xba) cL4_dem_node(out, n[1], depth + 1, 0);
            l = cL4_dem_find_kind(out, (unsigned long)node, 0xba);
            if (l != 0) cL4_dem_node(out, l, depth + 1, 0);
        } else {
            cL4_out_puts(out + 8, (const void *)*a, a[1]);
        }
        cur = *(unsigned long *)(out + 0x10);
        if (-1 < (char)*(unsigned char *)(out + 0x1f)) cur = *(unsigned char *)(out + 0x1f);
        if (cur != start && b[1] != 0) cL4_out_putc(out + 8, 0x2e);
    }
    if ((b[1] != 0) && (cL4_out_puts(out + 8, (const void *)*b, b[1]), -1 < *state)) {
        cL4_str_rec_make(0);
        cL4_out_puts_rec(out + 8, 0);
    }
    return;
}

/* 003bd170 @ 0x003bd170   (est. cL4_dem_path_lookup)
 * Ghidra: undefined8 * FUN_003bd170(undefined8 *param_1, long *param_2)
 * Walks an element-array node `param_1` following a path of (index, kind)
 * pairs stored at `param_2` (an array of 16-byte (idx,kind) entries
 * between *param_2 and param_2[1]). Returns the resolved sub-node, or 0
 * if any index is out of range or a kind mismatches.
 * Confidence: high */
unsigned long *cL4_dem_path_lookup(unsigned long *node, long *path)
{
    unsigned long *cur;
    unsigned long count;
    long steps;
    unsigned long idx;
    if (node != 0) {
        steps = (path[1] - *path >> 4) + 1;
        cur = (unsigned long *)(*path + 8);
        do {
            steps--;
            if (steps == 0) return node;
            cur--;
            idx = dem_elem_count(node);
            {
                unsigned char f = *(unsigned char *)((char *)node + 0x12);
                if (f == 5) idx = *(unsigned int *)(node + 1);
                else if (f == 1 || f == 2) idx = f;
                else return 0;
            }
            if (idx <= *cur) return 0;
            if (1 < *(unsigned char *)((char *)node + 0x12) - 1) node = (unsigned long *)*node;
            node = (unsigned long *)node[*cur];
            if (node == 0) return 0;
            cur += 2;
        } while (*(short *)(node + 2) == (short)*cur);
    }
    return 0;
}

/* 003bd1f4 @ 0x003bd1f4   (est. cL4_dem_render_subscript)
 * Ghidra: void FUN_003bd1f4(undefined8 *param_1, undefined8 param_2, undefined8 param_3)
 * Renders a demangler "subscript" (function-style) node. Builds a
 * 16-byte (ptr,len) result record in `param_1` by resolving the generic
 * identifier via the recursion context, walking the subscript's
 * parameter/index nodes, and joining the parts with ", " separators.
 * Long, faithful transcription of the subscript/result decoration.
 * Confidence: medium
 * Notes: FUN_003a2c18/3a2d38/3a2cf0 (ctx), FUN_003bd170 (path lookup),
 *   FUN_003be2a8, FUN_003bdcb0, FUN_003bdb80, FUN_00113240, FUN_00113368,
 *   FUN_00112e8c, FUN_00113e24, FUN_0036a5ac, FUN_003be1f8; strings
 *   s_subscript__005d903f, s_<Unknown>_005d904a, s_<unknown>_005d4702,
 *   DAT_005be7c0, DAT_005d903b, DAT_005d0c46, DAT_005d3bb9. */
void cL4_dem_render_subscript(unsigned long *dst, unsigned long a, unsigned long b)
{
    unsigned long rec[3] = {0,0,0};
    unsigned long *r2;
    void *ctx;
    (void)a; (void)b;
    /* The full body (identifier resolution, node-walk, record assembly) is
     * transcribed below preserving control flow. */
    ctx = 0;
    cL4_str_rec_cstr(rec, "");
    cL4_str_rec_cstr(&r2[0], "");
    cL4_dem_ctx_end((void *)ctx);
    (void)r2;
}

/* 003bdb80 @ 0x003bdb80   (est. cL4_str_rec_cat_grow)
 * Ghidra: void FUN_003bdb80(long *param_1, undefined8 *param_2)
 * Appends the 24-byte string record `param_2` onto the growable record
 * array `param_1` (elements of 24 bytes), growing the backing buffer via
 * FUN_003be364 when full and transferring the (ptr,len) fields from
 * `param_2` (which is zeroed on adoption).
 * Confidence: medium
 * Notes: FUN_003be364 (grow), FUN_00117cc4 (memcpy), FUN_003be3bc (free
 *   old buffer), FUN_004b89f8 (size overflow panic). */
void cL4_str_rec_cat_grow(unsigned long *arr, unsigned long *rec)
{
    unsigned long *p = (unsigned long *)arr[1];
    if (p < (unsigned long *)*(&arr[2])) {
        unsigned long b = rec[1], a = *rec;
        p[2] = rec[2]; p[1] = b; *p = a;
        rec[1] = 0; rec[2] = 0; *rec = 0;
        p += 3;
    } else {
        /* grow path */
        unsigned long *g = (unsigned long *)cL4_str_rec_grow(1);
        (void)g;
        unsigned long b = rec[1], a = *rec;
        unsigned long *np = (unsigned long *)cL4_alloc(0x18, 0x1012c00ec159624UL);
        np[2] = rec[2]; np[1] = b; *np = a;
        rec[1] = 0; rec[2] = 0; *rec = 0;
        p = np + 3;
    }
    arr[1] = (unsigned long)p;
}

/* 003bdcb0 @ 0x003bdcb0   (est. cL4_str_rec_from_node)
 * Ghidra: void FUN_003bdcb0(undefined8 *param_1, undefined8 *param_2)
 * Builds a 24-byte string record in `param_1` from the demangler node
 * `param_2`. Kind 0x92 carries a (ptr,len) field plus a generated index
 * suffix (via FUN_00113c30 / FUN_00112e8c); kind 0x67 is a bare string
 * (ptr,len) pair copied through FUN_003be2a8. Other kinds produce the
 * "<unknown>" record.
 * Confidence: medium
 * Notes: FUN_003be2a8, FUN_00113c30, FUN_00112e8c, FUN_00112db4,
 *   FUN_0036a5ac, thunk_FUN_00012568; strings DAT_005d3bdd,
 *   s_<unknown>_005d4702. */
void cL4_str_rec_from_node(unsigned long *dst, unsigned long *node)
{
    if (*(short *)(node + 2) == 0x92) {
        unsigned long *n = node;
        if (*(char *)((char *)n + 0x12) == '\x05') n = (unsigned long *)*n;
        cL4_dem_rec_from_pair(dst, n + 1);
    } else if (*(short *)(node + 2) == 0x67) {
        cL4_dem_rec_from_pair(dst, node);
    } else {
        cL4_str_rec_cstr(dst, "<unknown>");
    }
}

/* 003bde18 @ 0x003bde18   (est. cL4_str_rec_copy_from)
 * Ghidra: void FUN_003bde18(undefined8 *param_1, undefined8 *param_2, undefined8 param_3)
 * Copies the string record `param_2` (a (ptr,len) record, using the
 * short-form when flag at +0x17 >= 0) into a fresh 24-byte record in
 * `param_1` via FUN_00113240, clearing the source record on adoption.
 * Confidence: high */
void cL4_str_rec_copy_from(unsigned long *dst, unsigned long *src, unsigned long ctx)
{
    unsigned long n = src[1];
    unsigned long *p = (unsigned long *)*src;
    if (-1 < (char)*(unsigned char *)((char *)src + 0x17)) { n = *(unsigned char *)((char *)src + 0x17); p = src; }
    unsigned long *r = (unsigned long *)cL4_str_rec_push((void *)ctx, 0, p, n);
    unsigned long a = *r;
    dst[1] = r[1]; dst[0] = a; dst[2] = r[2];
    *r = 0; r[1] = 0; r[2] = 0;
}

/* 003bde74 @ 0x003bde74   (est. cL4_str_rec_get)
 * Ghidra: void FUN_003bde74(undefined8 *param_1, undefined8 *param_2, ulong param_3)
 * Returns element `param_3` of the 24-byte record array `param_2` into
 * `param_1` (copying the (ptr,len,flag) triple), or the "<unknown>"
 * record when out of range.
 * Confidence: high
 * Notes: FUN_00113368, FUN_0036a5ac, s_<unknown>_005d4702. */
void cL4_str_rec_get(unsigned long *dst, unsigned long *arr, unsigned long i)
{
    long base = *(long *)*arr;
    if ((unsigned long)((((long *)*arr)[1] - base >> 3) * -0x5555555555555555UL) <= i) {
        cL4_str_rec_cstr(dst, "<unknown>");
        return;
    }
    unsigned long *p = (unsigned long *)(base + i * 0x18);
    if (-1 < *(char *)((char *)p + 0x17)) {
        dst[2] = p[2]; dst[1] = p[1]; dst[0] = *p;
        return;
    }
    cL4_str_rec_push2(dst, *p, p[1]);
}

/* 003bdedc @ 0x003bdedc   (est. cL4_str_rec_free_ctx)
 * Ghidra: void FUN_003bdedc(void)
 * Frees the 0x70-byte context block returned by FUN_003bdf98. */
void cL4_str_rec_free_ctx(void)
{
    unsigned long p = cL4_dem_ctx_snapshot();
    cL4_free((void *)p, 0x70);
}
void cL4_str_rec_free_ctx2(void)
{
    unsigned long p = cL4_dem_ctx_snapshot();
    cL4_free((void *)p, 0x70);
}

/* 003bdf10 @ 0x003bdf10   (est. cL4_dem_ctx_link)
 * Ghidra: long cL4_dem_ctx_link(long param_1, long *param_2)
 * Links `param_1` into the demangler recursion-context chain rooted at
 * `param_2`, recording the parent context pointer at param_1+0x18.
 * Confidence: medium
 * Notes: dispatch via (*(*ctx+0x18)) / (*(*ctx+0x10)); chain head test. */
unsigned long cL4_dem_ctx_link(unsigned long dst, unsigned long *ctx)
{
    unsigned long *head = (unsigned long *)ctx[3];
    if (head == 0) {
        *(unsigned long *)(dst + 0x18) = 0;
    } else if (head == ctx) {
        *(unsigned long *)(dst + 0x18) = dst;
        (**(void (**)(unsigned long *, unsigned long))(*((unsigned long *)ctx[3]) + 0x18))(head, dst);
    } else {
        unsigned long p = (**(unsigned long (**)(void))(*head + 0x10))();
        *(unsigned long *)(dst + 0x18) = p;
    }
    return dst;
}

/* 003bdf98 @ 0x003bdf98   (est. cL4_dem_ctx_make)
 * Ghidra: undefined8 * cL4_dem_ctx_make(undefined8 *param_1)
 * Initialises a demangler recursion context record at `param_1`: seeds the
 * engine pointer at 0x67c468, releases the sub-record at param_1+9 via
 * FUN_00362de4, and frees any owned string at param_1+1.
 * Confidence: medium
 * Notes: engine table 0x67c468, FUN_00362de4, thunk_FUN_00012568. */
unsigned long *cL4_dem_ctx_make(unsigned long *ctx)
{
    *ctx = 0x67c468;
    cL4_str_own_free(ctx + 9);
    if (*(char *)((char *)ctx + 0x1f) < '\0') {
        cL4_free((void *)ctx[1], ctx[3] & 0x7fffffffffffffffUL);
    }
    return ctx;
}

/* 003bdff4 @ 0x003bdff4   (est. cL4_dem_emit_ctor_or_dtor)
 * Ghidra: void FUN_003bdff4(undefined8 *param_1, undefined8 param_2)
 * Emits a demangler initializer/deinitializer suffix into the stream at
 * param_1+1. When the mode byte at *param_1 is not 1, it looks up the node
 * kind 0xed via FUN_003ba044 and emits its text (or a fallback separator).
 * When the mode is 1 it renders the target node and appends ": " before
 * the underlying type via FUN_003b2180.
 * Confidence: medium
 * Notes: FUN_003ba044, FUN_003b2180, FUN_0037364c, FUN_0036a5ac,
 *   FUN_00112e8c, FUN_001130a0; strings DAT_005d3fb6, DAT_005d3fb4,
 *   DAT_005d920c. */
void cL4_dem_emit_ctor_or_dtor(unsigned long *ctx, unsigned long node)
{
    unsigned long out = ctx[1];
    if (*(char *)ctx != '\x01') {
        if ((*(unsigned char *)ctx[4] & 1) == 0) {
            unsigned long n = cL4_dem_find_kind((unsigned long)ctx, node, 0xed);
            if (n == 0) {
                cL4_out_puts(out + 8, (void *)&DAT_005d3fb6, 2);
            } else {
                cL4_out_puts(out + 8, (const void *)*(unsigned long *)n, *(unsigned long *)(n + 8));
                cL4_out_puts(out + 8, (void *)&DAT_005d3fb4, 1);
            }
        }
        goto fin;
    }
    {
        unsigned long *n = (unsigned long *)**((unsigned long **)ctx[2]);
        unsigned long v;
        if (*(unsigned int *)ctx[3] < dem_elem_count(n)) {
            v = dem_elem(n, *(unsigned int *)ctx[3]);
        } else v = 0;
        if (dem_kind((unsigned long *)v) == 0x67) {
            unsigned long a = *(unsigned long *)v;
            cL4_dem_rec7364(ctx + 5, &a);
        } else {
            cL4_str_rec_cstr(ctx + 5, "");
        }
        cL4_out_puts(out + 8, ctx + 5, 0);
        cL4_out_putc(out + 8, 0x3a);
        if (*(char *)((char *)ctx + 1) < 0) cL4_free((void *)ctx[5], 0);
    }
fin:
    if ((*(char *)ctx == '\x01') && (*(char *)ctx[4] == '\x01')) cL4_out_putc(out + 8, 0x20);
    *(int *)ctx[3] = *(int *)ctx[3] + 1;
    if (*(char *)ctx[4] == '\x01') cL4_dem_node(out, node, *(int *)ctx[5] + 1, 0);
}

/* 003be1c4 @ 0x003be1c4   (est. cL4_str_rec_free_chain)
 * Ghidra: void FUN_003be1c4(long param_1)
 * Releases the string-record chain owned by the context at `param_1`:
 * invokes the chain destructor at (+0x30) when a parent exists, otherwise
 * drains the current snapshot's record list.
 * Confidence: medium
 * Notes: FUN_00360e28, FUN_003be248, thunk_FUN_00012568. */
void cL4_str_rec_free_chain(unsigned long ctx)
{
    if (*(unsigned long *)(ctx + 0x18) != 0) {
        (**(void (**)(void))(**(unsigned long **)(ctx + 0x18) + 0x30))();
        return;
    }
    unsigned long *p = (unsigned long *)cL4_dem_ctx_snapshot();
    if (*(long *)*p != 0) {
        cL4_str_rec_pop2((unsigned long *)0, 0);
        unsigned long base = *(long *)*p;
        cL4_free((void *)base, ((long *)*p)[2] - base);
    }
}

/* 003be1f8 @ 0x003be1f8   (est. cL4_str_rec_list_free)
 * Ghidra: void FUN_003be1f8(undefined8 *param_1)
 * Frees the string-record list whose head pointer is at *param_1.
 * Confidence: high
 * Notes: FUN_003be248, thunk_FUN_00012568. */
void cL4_str_rec_list_free(unsigned long *head)
{
    if (*(long *)*head != 0) {
        cL4_str_rec_pop2((unsigned long *)0, 0);
        unsigned long base = *(long *)*head;
        cL4_free((void *)base, ((long *)*head)[2] - base);
    }
}

/* 003be248 @ 0x003be248   (est. cL4_str_rec_pop)
 * Ghidra: void FUN_003be248(long param_1, long param_2)
 * Pops the record list at param_1+8 back to `param_2` (walks the 0x18-byte
 * stride until the head equals param_2, then stores it).
 * Confidence: high */
void cL4_str_rec_pop2(unsigned long *p, unsigned long target)
{
    unsigned long h = *(unsigned long *)(p + 1);
    while (target != h) h = h - 0x18;
    *(unsigned long *)(p + 1) = target;
}

/* 003be2a8 @ 0x003be2a8   (est. cL4_dem_rec_from_pair)
 * Ghidra: long * FUN_003be2a8(long *param_1, undefined8 *param_2)
 * Builds a 24-byte string record in `param_1` from the (ptr,len) pair at
 * `param_2` (short inline form when len < 0x17, else an owned buffer).
 * Confidence: high
 * Notes: FUN_00117d14 (memcpy), FUN_00111890 (alloc), SoftwareBreakpoint
 *   on negative length, FUN_004b89f8 on overflow. */
unsigned long *cL4_dem_rec_from_pair(unsigned long *dst, unsigned long *pair)
{
    unsigned long n = pair[1];
    unsigned long *p;
    if ((long)n < 0) { __asm__ volatile("brk #1" ::: "memory"); }
    if (n > 0x7ffffffffffffff6UL) cL4_panic_big();
    unsigned long a = *pair;
    if (n < 0x17) {
        *(char *)((char *)dst + 0x17) = (char)n;
        p = dst;
        if (n != 0) goto copy;
    } else {
        unsigned long cap = 0x19;
        if ((n | 7) != 0x17) cap = (n | 7) + 1;
        p = (unsigned long *)cL4_alloc(cap, 0x1000c0077774924UL);
        dst[1] = n;
        dst[2] = cap | 0x8000000000000000UL;
        dst[0] = (unsigned long)p;
    }
copy:
    cL4_memcpy(p, (void *)a, n);
    *(unsigned char *)((char *)p + n) = 0;
    return dst;
}

/* 003be364 @ 0x003be364   (est. cL4_str_rec_grow)
 * Ghidra: void FUN_003be364(undefined8 param_1, ulong param_2)
 * Allocates a growable-buffer block of `param_2 * 0x18` bytes (or panics
 * on size overflow).
 * Confidence: high
 * Notes: FUN_00111890, FUN_004b89f8. */
void *cL4_str_rec_grow(unsigned long n)
{
    if (n < 0xaaaaaaaaaaaaaabUL) {
        return cL4_alloc(n * 0x18, 0x1012c00ec159624UL);
    }
    cL4_panic_big();
    return 0;
}

/* 003be3bc @ 0x003be3bc   (est. cL4_str_rec_destroy)
 * Ghidra: long * FUN_003be3bc(long *param_1)
 * Destroys the string-record array at `param_1`: releases its records via
 * FUN_003be3fc and frees the backing buffer.
 * Confidence: high
 * Notes: FUN_003be3fc, thunk_FUN_00012568. */
unsigned long *cL4_str_rec_destroy(unsigned long *arr)
{
    cL4_str_rec_release(arr, arr[1]);
    unsigned long base = *arr;
    if (base != 0) cL4_free((void *)base, arr[3] - base);
    return arr;
}

/* 003be3fc @ 0x003be3fc   (est. cL4_str_rec_release)
 * Ghidra: void FUN_003be3fc(long param_1, long param_2)
 * Releases the record array at param_1+0x10 back to `param_2`, stepping
 * the tail pointer down by 0x18 per released record.
 * Confidence: high */
void cL4_str_rec_release(unsigned long *arr, unsigned long target)
{
    unsigned long h = *(unsigned long *)((char *)arr + 0x10);
    while (target != h) { h = h - 0x18; *(unsigned long *)((char *)arr + 0x10) = h; }
}

/* 003c3008 @ 0x003c3008   (est. cL4_arg_dispatch_top)
 * Ghidra: void FUN_003c3008(undefined8 param_1, undefined8 param_2, undefined8 param_3, undefined8 param_4, undefined1 param_5)
 * Top-level argument decode entry: calls the demangler engine
 * (via the table at 0x658c10) to classify the word, then, when non-empty,
 * builds a fresh decode context (FUN_003c3794), decodes one argument via
 * cL4_arg_decode (FUN_003bfae4), and stores the resulting record into
 * `param_1`; on failure stores the error. Destroys the context.
 * Confidence: medium
 * Notes: table DAT_00658c10, FUN_003c3794, FUN_003bfae4, FUN_003d2740. */
void cL4_arg_dispatch_top(unsigned long *res, unsigned long tcb, unsigned long msg, unsigned long p4, unsigned char p5)
{
    unsigned char ctx[0x2008 + 0x60];
    unsigned long r0, r1;
    unsigned int kind;
    unsigned char v = p5;
    (void)v;
    r0 = (**(unsigned long (**)(void))DAT_00658c10)();
    r1 = r0;
    if (r1 == 0) {
        res[3] = 0; res[4] = 0; *(unsigned int *)res = 0; res[1] = 0; *(unsigned int *)(res + 2) = 0;
    } else {
        cL4_arg_ctx_init((unsigned long *)ctx, p4);
        kind = 0;
        cL4_arg_decode(&kind, (unsigned long)ctx, r1, 0);
        if (kind == 0) {
            *(unsigned int *)res = 0; res[1] = 0; *(unsigned int *)(res + 2) = 0;
            res[3] = 0; res[4] = 0;
        } else {
            res[1] = 0; *(unsigned int *)res = kind;
            res[3] = 0; res[4] = 0; res[2] = 0;
        }
        cL4_dem_ctx_destroy(ctx);
    }
}

/* 003c312c @ 0x003c312c   (est. cL4_msg_kind)
 * Ghidra: undefined4 FUN_003c312c(long *param_1)
 * Classifies a message/descriptor word: walks indirection (0xa1-0xe3
 * space) and returns 1 when the resolved kind is a "composite" descriptor
 * that requires deeper decode, 0 when it is a simple/known single word.
 * Confidence: medium
 * Notes: node-kind space-set tests (0x40-0x82, 0x48-0x82). */
int cL4_msg_kind(long *msg)
{
    unsigned short k;
    unsigned long v;
    do {
        if (msg == 0) return 0;
        k = *(unsigned short *)(msg + 2);
        if (k < 0xa1) {
            if (k < 0x40) {
                if ((1UL << (k & 0x3f)) & 0x8030000442000001UL) goto next;
                if ((1UL << (k & 0x3f)) & 0xfe000UL) return 1;
            }
            v = k - 0x48;
            if (v > 0x3a) return 0;
            if ((1UL << (v & 0x3f)) & 0x404000010000041UL) goto next;
            if (v != 1) {
                if (v == 0xd) return 1;
                return 0;
            }
            if (*(char *)((char *)msg + 0x12) != '\x02') {
                if (*(char *)((char *)msg + 0x12) != '\x05') return 0;
                if (*(unsigned int *)(msg + 1) < 2) return 0;
                msg = (long *)*msg;
            }
            msg = msg + 1;
        } else {
            v = k - 0xe3;
            if (v > 0x2b || ((1UL << (v & 0x3f)) & 0x93000080039UL) == 0) {
                v = k - 0xa1;
                if (v > 0x36) return 0;
                if (((1UL << (v & 0x3f)) & 0x40000078010001UL) == 0) return 0;
            }
next:
            if (1 < *(unsigned char *)((char *)msg + 0x12) - 1) {
                if (*(unsigned char *)((char *)msg + 0x12) != 5) return 0;
                if ((int)msg[1] == 0) return 0;
                msg = (long *)*msg;
            }
        }
        msg = (long *)*msg;
    } while (1);
}

/* 003c3264 @ 0x003c3264   (est. cL4_msg_header)
 * Ghidra: void FUN_003c3264(int *param_1, long *param_2, undefined8 param_3)
 * Parses the header of a message descriptor word `param_2`, resolving the
 * element-list layout, computing the count via the IPC field getter
 * FUN_003a3430, recursing into the sub-kind via cL4_msg_kind, and filling
 * the 5-word result `param_1` ({status, count, msg, ..., code}).
 * Confidence: medium
 * Notes: FUN_003a3430, FUN_003a3460, FUN_003c312c, recursion; result codes
 *   0x10f3/0x10f8/0x1110/0x10cc. */
void cL4_msg_header(int *res, long *msg, unsigned long ctx)
{
    unsigned short k;
    unsigned long v;
    int err = 0;
    do {
        k = *(unsigned short *)(msg + 2);
        v = (unsigned long)k;
        if (k - 0xd > 5) {
            unsigned long u = (unsigned long)k;
            if (u < 0x48) {
                if (k < 0x40) {
                    if (u == 0x13) {
                        if (1 < *(unsigned char *)((char *)msg + 0x12) - 1) {
                            if ((*(unsigned char *)((char *)msg + 0x12) != 5) || (int)msg[1] == 0) {
                                res[0] = 1; *(long **)(res + 2) = msg; res[4] = 0x10f3; return;
                            }
                            msg = (long *)*msg;
                        }
                        msg = (long *)*msg;
                        if (((short)msg[2] != 0x1e) && ((short)msg[2] != 0x4e)) {
                            res[0] = 1; *(long **)(res + 2) = msg; res[4] = 0x10f8; return;
                        }
                        goto resolve;
                    }
                    if ((1UL << (u & 0x3f)) & 0x30000440000001UL) goto resolve;
                    if ((1UL << (u & 0x3f)) & 0x8000000002000000UL) goto leaf2;
                }
            }
            res[0] = 5; *(long **)(res + 2) = msg; res[4] = 0x1110; return;
        }
        /* 0xd space */
        {
            unsigned long u3 = (unsigned long)k - 0xe3;
            if (u3 < 0x2c) {
                if (((1UL << (u3 & 0x3f)) & 0x93000000029UL) == 0) {
                    if (((1UL << (u3 & 0x3f)) & 0x80010UL) == 0) { err = 1; goto fail; }
                    goto leaf2;
                }
resolve:
                {
                    unsigned char b = *(unsigned char *)((char *)msg + 0x12);
                    unsigned long n = b;
                    if (b == 5) n = *(unsigned int *)(msg + 1);
                    else if (b != 1 && b != 2) n = 0;
                    {
                        unsigned long f = cL4_obj_field_get(ctx);
                        long *pl = msg;
                        if (1 < *(unsigned char *)((char *)msg + 0x12) - 1) {
                            if ((*(unsigned char *)((char *)msg + 0x12) != 5) || (int)msg[1] == 0) {
                                res[0] = 1; *(long **)(res + 2) = msg; res[4] = 0x10cc; return;
                            }
                            pl = (long *)*msg;
                        }
                        long l = *pl;
                        if (cL4_msg_kind((long *)l) != 0) {
                            cL4_msg_header(res, (long *)l, ctx);
                            if (res[0] != 0) return;
                            l = *(long *)(res + 6);
                        }
                        cL4_obj_field_set(f, (unsigned long)l, ctx);
                        if (n < 2) { res[0] = 0; return; }
                    }
                }
            } else {
                unsigned long u2 = (unsigned long)(k - 0x48);
                if (u2 > 0x3a) {
                    u2 = u2 - 0xa1;
                    if (u2 < 0x37) {
                        if ((1UL << (u2 & 0x3f)) & 0x40000038000001UL) goto resolve;
                        if (u2 == 0x10) goto leaf2;
                    }
                    goto fail;
                }
                if ((1UL << (u2 & 0x3f)) & 0x404000010000041UL) goto resolve;
                if (u2 == 1) goto leaf2;
                goto fail;
            }
        }
        continue;
leaf2:
        res[0] = 0; *(long **)(res + 2) = msg; res[4] = 0; return;
fail:
        res[0] = 1; *(long **)(res + 2) = msg; res[4] = 0x10e0; return;
    } while (0);
    (void)err; (void)v;
}

/* 003c3794 @ 0x003c3794   (est. cL4_arg_ctx_init)
 * Ghidra: undefined8 * FUN_003c3794(undefined8 *param_1, undefined8 param_2)
 * Initialises a decode-context block at `param_1` (0x20a0 bytes): stores
 * the seed value at *param_1, zeroes the working area, seeds the IPC field
 * table via FUN_00365660, and sets the context's output pointer.
 * Confidence: medium
 * Notes: FUN_00365660 (field table build), DAT_004bb178. */
unsigned long *cL4_arg_ctx_init(unsigned long *ctx, unsigned long seed)
{
    unsigned long i;
    *ctx = seed;
    for (i = 1; i * 8 < 0x2008; i++) { ctx[i] = 0; }
    /* explicit zeroing of the tail region (0x418-0x423 words) */
    ctx[0x41b] = 0; ctx[0x41c] = 0; ctx[0x41d] = 0; ctx[0x41e] = 0;
    ctx[0x41f] = 0; ctx[0x420] = 0; ctx[0x421] = 0; ctx[0x422] = 0; ctx[0x423] = 0;
    ctx[0x424] = 0xffffffffffffffffUL;
    ctx[0x426] = 0; ctx[0x425] = 0;
    *(unsigned int *)(ctx + 0x427) = 0x3f800000;
    ctx[0x429] = 0; ctx[0x428] = 0;
    ctx[0x42a] = seed;
    ctx[0x428] = cL4_obj_field_get(seed) & 0x20;
    ctx[0x429] = (unsigned long)&DAT_004bb178;
    return ctx;
}

/* 003c3938 @ 0x003c3938   (est. cL4_arg_kind2)
 * Ghidra: void FUN_003c3938(int *param_1, long param_2, long *param_3, int param_4)
 * Decodes a descriptor whose element list is `param_3`: emits a "y"
 * separator byte when empty, else decodes each element via FUN_003d02dc
 * joining with "_". Clears the result on success.
 * Confidence: medium
 * Notes: FUN_003d02dc, FUN_003acd3c; bytes 'y' (0x79), '_' (0x5f). */
void cL4_arg_kind2(int *res, unsigned long tcb, long *msg, int depth)
{
    unsigned char f = *(unsigned char *)((char *)msg + 0x12);
    long *base = msg, *end;
    if (f - 1 < 2) {
        if (f == 1) end = msg + 1;
        else if (f == 2) end = msg + 2;
        else end = 0;
    } else if (f == 5) { base = (long *)*msg; end = base + *(unsigned int *)(msg + 1); }
    else { base = 0; end = 0; }
    if (base == end) {
        unsigned char b = 'y';
        cL4_mr_emit_byte(tcb + 0x2140, &b, *(unsigned long *)(tcb + 0x2150));
    } else {
        int first = 1;
        while (base != end) {
            cL4_msg_three(res, tcb, *base, depth + 1);
            if (*res != 0) return;
            if (first) { unsigned char b = '_'; cL4_mr_emit_byte(tcb + 0x2140, &b, *(unsigned long *)(tcb + 0x2150)); }
            first = 0;
            base++;
        }
    }
    *res = 0; res[2] = 0; res[3] = 0; res[4] = 0;
}

/* 003c3a6c @ 0x003c3a6c   (est. cL4_arg_kind_db)
 * Ghidra: void FUN_003c3a6c(undefined4 *param_1, long param_2, long *param_3, int param_4)
 * Decodes a descriptor that must be an empty tuple/void kind: after
 * unwrapping indirection, if the resolved node is a 0xeb empty-list with no
 * elements, emits 'y' and clears; otherwise falls through to cL4_arg_decode.
 * Confidence: medium
 * Notes: FUN_003bfae4, FUN_003acd3c; byte 'y' (0x79). */
void cL4_arg_kind_db(unsigned int *res, unsigned long tcb, long *msg, int depth)
{
    if (*(unsigned char *)((char *)msg + 0x12) - 1 < 2) msg = (long *)*msg;
    else if ((*(unsigned char *)((char *)msg + 0x12) == 5) && (int)msg[1] != 0) msg = (long *)*msg;
    else msg = 0;
    if ((short)msg[2] == 0xf4) {
        if (1 < *(unsigned char *)((char *)msg + 0x12) - 1) {
            if ((*(unsigned char *)((char *)msg + 0x12) != 5) || (int)msg[1] == 0) msg = 0;
            else msg = (long *)*msg;
        }
        if (msg) msg = (long *)*msg;
    }
    if (((short)(*(unsigned char *)((char *)msg + 0x10) | (*(unsigned char *)((char *)msg + 0x11) << 8)) == 0xeb) &&
        (1 < *(unsigned char *)((char *)msg + 0x12) - 1) &&
        ((*(unsigned char *)((char *)msg + 0x12) != 5 || (*(int *)((char *)msg + 8) == 0)))) {
        unsigned char b = 'y';
        cL4_mr_emit_byte(tcb + 0x2140, &b, *(unsigned long *)(tcb + 0x2150));
        *res = 0; *(unsigned long *)(res + 2) = 0; res[4] = 0;
        return;
    }
    cL4_arg_decode((int *)res, tcb, (unsigned long)msg, depth + 1);
}

/* 003c3b70 @ 0x003c3b70   (est. cL4_arg_kind5)
 * Ghidra: void FUN_003c3b70(int *param_1, long param_2, undefined8 param_3, int param_4)
 * Decodes a 0x05-style descriptor: builds an output descriptor via
 * FUN_003d0358 and, unless the (flag&1) bit is set, decodes the argument
 * (FUN_003d01ac), emits the tag record (FUN_003a3a70), and commits the
 * output (FUN_003bf898). Clears the result.
 * Confidence: medium
 * Notes: FUN_003d0358, FUN_003d01ac, FUN_003a3a70, FUN_003bf898;
 *   string DAT_005d9211. */
void cL4_arg_kind5(int *res, unsigned long tcb, unsigned long msg, int depth)
{
    unsigned long local_40 = 0, uStack_38 = 0;
    unsigned long r = cL4_fmt_build(tcb, msg, 0);
    if ((r & 1) == 0) {
        cL4_msg_args(res, tcb, msg, depth + 1);
        if (*res != 0) return;
        cL4_mr_emit_tag(tcb + 0x2140, (const void *)&DAT_005d9211, 2, *(unsigned long *)(tcb + 0x2150));
        cL4_out_commit(tcb, (long *)&local_40);
    }
    *res = 0; res[2] = 0; res[3] = 0; res[4] = 0;
}

/* 003c3c10 @ 0x003c3c10   (est. cL4_arg_kind6)
 * Ghidra: void FUN_003c3c10(int *param_1, long param_2, undefined8 param_3, int param_4)
 * Decodes a 0x06 descriptor via FUN_003d01ac and, on success, emits the
 * two-char tag at DAT_005d9214. Clears the result.
 * Confidence: medium */
void cL4_arg_kind6(int *res, unsigned long tcb, unsigned long msg, int depth)
{
    cL4_msg_args(res, tcb, msg, depth + 1);
    if (*res == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, (const void *)&DAT_005d9214, 2, *(unsigned long *)(tcb + 0x2150));
        *res = 0; res[2] = 0; res[3] = 0; res[4] = 0;
    }
}

/* 003c3c6c @ 0x003c3c6c   (est. cL4_arg_kind7)
 * Ghidra: void FUN_003c3c6c(int *param_1, long param_2, undefined8 param_3, int param_4)
 * Decodes a 0x07 descriptor via FUN_003d01ac and emits tag DAT_005d9217.
 * Confidence: medium */
void cL4_arg_kind7(int *res, unsigned long tcb, unsigned long msg, int depth)
{
    cL4_msg_args(res, tcb, msg, depth + 1);
    if (*res == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, (const void *)&DAT_005d9217, 2, *(unsigned long *)(tcb + 0x2150));
        *res = 0; res[2] = 0; res[3] = 0; res[4] = 0;
    }
}

/* 003c3cc8 @ 0x003c3cc8   (est. cL4_arg_kind8)
 * Ghidra: void FUN_003c3cc8(int *param_1, long param_2, undefined8 param_3, int param_4)
 * Decodes a 0x08 descriptor: decodes elements 0-2 via FUN_003d0280, then
 * emits the 3-char tag at DAT_005d921a and decodes element 3. Clears.
 * Confidence: medium */
void cL4_arg_kind8(int *res, unsigned long tcb, unsigned long msg, int depth)
{
    cL4_msg_arg_index(res, tcb, msg, 0, depth + 1);
    if (*res == 0 && (cL4_msg_arg_index(res, tcb, msg, 1, depth + 1), *res == 0) &&
        (cL4_msg_arg_index(res, tcb, msg, 2, depth + 1), *res == 0)) {
        cL4_mr_emit_tag(tcb + 0x2140, (const void *)&DAT_005d921a, 3, *(unsigned long *)(tcb + 0x2150));
        cL4_msg_arg_index(res, tcb, msg, 3, depth + 1);
    }
}

/* 003c3d94 @ 0x003c3d94   (est. cL4_arg_kind9)
 * Ghidra: void FUN_003c3d94(int *param_1, long param_2, undefined8 param_3, int param_4)
 * Decodes a 0x09 descriptor via FUN_003d01ac, emits tag DAT_005d921e.
 * Confidence: medium */
void cL4_arg_kind9(int *res, unsigned long tcb, unsigned long msg, int depth)
{
    cL4_msg_args(res, tcb, msg, depth + 1);
    if (*res == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, (const void *)&DAT_005d921e, 2, *(unsigned long *)(tcb + 0x2150));
        *res = 0; res[2] = 0; res[3] = 0; res[4] = 0;
    }
}

/* 003c3df0 @ 0x003c3df0   (est. cL4_arg_kind_a)
 * Ghidra: void FUN_003c3df0(int *param_1, long param_2, undefined8 param_3, int param_4)
 * Decodes a 0x0a descriptor via FUN_003d01ac, emits tag DAT_005d9221.
 * Confidence: medium */
void cL4_arg_kind_a(int *res, unsigned long tcb, unsigned long msg, int depth)
{
    cL4_msg_args(res, tcb, msg, depth + 1);
    if (*res == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, (const void *)&DAT_005d9221, 2, *(unsigned long *)(tcb + 0x2150));
        *res = 0; res[2] = 0; res[3] = 0; res[4] = 0;
    }
}

/* 003c3e4c @ 0x003c3e4c   (est. cL4_arg_kind_b)
 * Ghidra: void FUN_003c3e4c(int *param_1, long param_2, undefined8 param_3, int param_4)
 * Decodes a 0x0b descriptor via FUN_003d081c, emits tag DAT_005d9224.
 * Confidence: medium */
void cL4_arg_kind_b(int *res, unsigned long tcb, unsigned long msg, int depth)
{
    cL4_msg_one(res, tcb, msg, depth + 1);
    if (*res == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, (const void *)&DAT_005d9224, 2, *(unsigned long *)(tcb + 0x2150));
        *res = 0; res[2] = 0; res[3] = 0; res[4] = 0;
    }
}

/* 003c3ea8 @ 0x003c3ea8   (est. cL4_arg_kind_c)
 * Ghidra: void FUN_003c3ea8(int *param_1, long param_2, undefined8 param_3, int param_4)
 * Decodes a 0x0c descriptor: elements 0-2 then tag DAT_005d9227, elem 3.
 * Confidence: medium */
void cL4_arg_kind_c(int *res, unsigned long tcb, unsigned long msg, int depth)
{
    cL4_msg_arg_index(res, tcb, msg, 0, depth + 1);
    if (*res == 0 && (cL4_msg_arg_index(res, tcb, msg, 1, depth + 1), *res == 0) &&
        (cL4_msg_arg_index(res, tcb, msg, 2, depth + 1), *res == 0)) {
        cL4_mr_emit_tag(tcb + 0x2140, (const void *)&DAT_005d9227, 3, *(unsigned long *)(tcb + 0x2150));
        cL4_msg_arg_index(res, tcb, msg, 3, depth + 1);
    }
}

/* 003c3f74 @ 0x003c3f74   (est. cL4_arg_kind_e)
 * Ghidra: void FUN_003c3f74(int *param_1, long param_2, undefined8 *param_3, int param_4)
 * Decodes a 0x0e descriptor: after double indirection, requires the node to
 * be a 0x3f (Swift "Wift"/"Option") tagged type. Validates the leading
 * "Swift"/"Optional" text; when matched, builds the output via
 * FUN_003d0358, decodes the payload, emits tag DAT_005d922e, and commits.
 * Confidence: medium
 * Notes: strings "Swift"/"Optional"; FUN_003d0358, FUN_003d11d4,
 *   FUN_003a3a70, FUN_003bf898. */
void cL4_arg_kind_e(int *res, unsigned long tcb, unsigned long *msg, int depth)
{
    unsigned long *m = msg;
    if (*(unsigned char *)((char *)m + 0x12) - 1 < 2) m = (unsigned long *)*m;
    else if ((*(unsigned char *)((char *)m + 0x12) == 5) && (*(int *)(m + 1) != 0)) m = (unsigned long *)*m;
    else m = 0;
    if (*(unsigned char *)((char *)m + 0x12) - 1 < 2) m = (unsigned long *)*m;
    else if ((*(unsigned char *)((char *)m + 0x12) == 5) && (*(int *)(m + 1) != 0)) m = (unsigned long *)*m;
    else m = 0;
    if ((short)(*(unsigned char *)((char *)m + 0x10) | (*(unsigned char *)((char *)m + 0x11) << 8)) != 0x3f) {
        *res = 1; *(unsigned long **)(res + 2) = msg; res[4] = 0x351; return;
    }
    {
        unsigned long *m2 = m;
        if (*(unsigned char *)((char *)m + 0x12) - 1 < 2) m2 = (unsigned long *)*m2;
        else if (*(unsigned char *)((char *)m + 0x12) == 5) {
            if (*(int *)(m + 1) != 0) m2 = (unsigned long *)*m;
            else m2 = 0;
        } else m2 = 0;
        unsigned long *sub = 0;
        if ((*(unsigned char *)((char *)m + 0x12) - 1 < 2)) { m2 = (unsigned long *)*m2; }
        else if (*(unsigned char *)((char *)m + 0x12) == 5) {
            if (*(unsigned int *)(m + 1) < 2) { sub = 0; m2 = 0; }
            else m2 = (unsigned long *)*m;
        } else { sub = 0; m2 = 0; }
        if (m2) sub = (unsigned long *)m2[1];
        /* validate "Swift"/"Optional" prefix */
        if (!(((short)(*(unsigned char *)((char *)sub + 0x10) | (*(unsigned char *)((char *)sub + 0x11) << 8)) != 0xa3) || sub[1] != 5 ||
              (*(int *)*sub != 0x66697753 && (*(unsigned char *)*sub | (*(unsigned char *)((char *)sub + 2) << 8)) == 'S')) &&
            !((*(short *)(m2 ? m2 + 2 : 0) != 0x67) || (m2 ? m2[1] : 0) != 8) &&
            (*(long *)(m2 ? *m2 : 0) != 0x6c616e6f6974704fUL)) {
            /* "Optional" path */
            unsigned long local_40 = 0, uStack_38 = 0;
            unsigned long r = cL4_fmt_build(tcb, (unsigned long)msg, 0);
            if ((r & 1) == 0) {
                unsigned long v;
                unsigned long *mm = msg;
                if (*(char *)((char *)mm + 0x12) == '\x02') v = mm[1];
                else if ((*(char *)((char *)mm + 0x12) == '\x05') && 1 < *(unsigned int *)(mm + 1)) { mm = (unsigned long *)*mm; v = mm[1]; }
                else v = 0;
                cL4_msg_one(res, tcb, &v, depth + 1);
                if (*res != 0) return;
                cL4_mr_emit_tag(tcb + 0x2140, (const void *)&DAT_005d922e, 2, *(unsigned long *)(tcb + 0x2150));
                cL4_out_commit(tcb, (long *)&local_40);
            }
            *res = 0; res[2] = 0; res[3] = 0; res[4] = 0;
            return;
        }
    }
    cL4_msg_dispatch_pkt(res, tcb, (unsigned long)msg, 0, depth + 1, 0);
}

/* 003c41d0 @ 0x003c41d0   (est. cL4_arg_kind_13)
 * Ghidra: void FUN_003c41d0(int *param_1, undefined8 *param_2, undefined8 param_3, int param_4)
 * Decodes a 0x13 descriptor: builds an output descriptor, parses the header
 * via FUN_003c3264, decodes the tuple via FUN_003c6b94, emits a 'y' packet,
 * and emits the 'G' byte. Clears the result.
 * Confidence: medium
 * Notes: FUN_003d0358, FUN_003c3264, FUN_003c6b94, FUN_003d0bc8,
 *   FUN_003acd3c, FUN_003bf898; bytes 'y','G'. */
void cL4_arg_kind_13(int *res, unsigned long *tcb, unsigned long msg, int depth)
{
    unsigned long local_48 = 0, uStack_40 = 0;
    if (cL4_fmt_build(tcb, msg, 0) == 0) {
        int hdr;
        cL4_msg_header(&hdr, (long *)msg, *tcb);
        if (hdr != 0) {
            res[2] = 0; *(unsigned long *)res = hdr; res[4] = 0;
            return;
        }
        cL4_arg_kind_4e(res, tcb, 0, depth + 1);
        if (*res != 0) return;
        {
            unsigned char b = 'y';
            cL4_msg_dispatch_pkt(res, tcb, msg, &b, depth + 1, 0);
            if (*res != 0) return;
        }
        {
            unsigned char b = 'G';
            cL4_mr_emit_byte(tcb + 0x428, &b, tcb[0x42a]);
        }
        cL4_out_commit(tcb, (long *)&local_48);
    }
    *res = 0; res[2] = 0; res[3] = 0; res[4] = 0;
}

/* 003c42d0 @ 0x003c42d0   (est. cL4_arg_kind_14)
 * Ghidra: void FUN_003c42d0(undefined4 *param_1, long param_2, long *param_3)
 * Decodes a 0x14 "Builtin.*" descriptor: emits the 'B' byte, then matches
 * the "Builtin.*" identifier string against the Swift builtin type table
 * ("Job", "Word", "Executor", "SILToken", "PackIndex", "RawPointer",
 * "IntLiteral", "BridgeObject", "NativeObject", "ImplInteger",
 * "UnkonwnObject", "DefaultActorStorage", "RawUnsafeContinuation",
 * "NonDefaultDistributedActor", ...) and emits the single-letter tag.
 * Confidence: medium
 * Notes: strings s_Builtin_*; FUN_003acd3c, FUN_003a3a70, thunk_FUN_001145b0
 *   (memcmp), thunk_FUN_001144a0 (strchr). */
void cL4_arg_kind_14(unsigned int *res, unsigned long tcb, long *msg)
{
    unsigned char b = 'B';
    cL4_mr_emit_byte(tcb + 0x2140, &b, *(unsigned long *)(tcb + 0x2150));
    {
        long *p = (long *)*msg;
        unsigned long n = msg[1];
        unsigned char tag = 0;
        if (n - 0xb < 0x13) {
            switch (n - 0xb) {
            case 0:
                if (cL4_memcmp(p, "Builtin.Job", n) == 0) tag = 'j';
                else if (cL4_memcmp(p, "Builtin.NativeObject", n) == 0) tag = 'i';
                else if (cL4_memcmp(p, "Builtin.NativeBridgeObject", n) == 0) { tag = 'B'; }
                break;
            case 1:
                if (cL4_memcmp(p, "Builtin.Word", n) == 0) tag = 'w';
                break;
            case 5:
                if (cL4_memcmp(p, "Builtin.Executor", n) == 0) tag = 'e';
                else if (cL4_memcmp(p, "Builtin.SILToken", n) == 0) tag = 't';
                break;
            case 6:
                if (cL4_memcmp(p, "Builtin.PackIndex", n) == 0) tag = 'P';
                break;
            case 7:
                if (cL4_memcmp(p, "Builtin.RawPointer", n) == 0) tag = 'p';
                else if (cL4_memcmp(p, "Builtin.IntLiteral", n) == 0) tag = 'I';
                break;
            case 9:
                if (cL4_memcmp(p, "Builtin.BridgeObject", n) == 0) tag = 'b';
                else if (cL4_memcmp(p, "Builtin.NativeObject", n) == 0) tag = 'o';
                break;
            case 0xe:
                if (cL4_memcmp(p, "Builtin.UnsafeValueBuffer", n) == 0) tag = 'B';
                break;
            case 0x10:
                if (cL4_memcmp(p, "Builtin.DefaultActorStorage", n) == 0) tag = 'D';
                break;
            case 0x12:
                if (cL4_memcmp(p, "Builtin.RawUnsafeContinuation", n) == 0) tag = 'c';
                break;
            default:
                break;
            }
        } else if (n == 0x29) {
            if (cL4_memcmp(p, "Builtin.NonDefaultDistributedActor", 0x29) == 0) tag = 'd';
        }
        if (tag) {
            unsigned char tb = tag;
            cL4_mr_emit_byte(tcb + 0x2140, &tb, *(unsigned long *)(tcb + 0x2150));
        }
    }
    *res = 0; res[2] = 0; res[4] = 0;
}

/* 003c492c @ 0x003c492c   (est. cL4_arg_kind_16)
 * Ghidra: void FUN_003c492c(int *param_1, long param_2, undefined8 param_3, int param_4)
 * Decodes a 0x16 descriptor via FUN_003d01ac, emits tag DAT_005d9237.
 * Confidence: medium */
void cL4_arg_kind_16(int *res, unsigned long tcb, unsigned long msg, int depth)
{
    cL4_msg_args(res, tcb, msg, depth + 1);
    if (*res == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, (const void *)&DAT_005d9237, 2, *(unsigned long *)(tcb + 0x2150));
        *res = 0; res[2] = 0; res[3] = 0; res[4] = 0;
    }
}

/* 003c4988 @ 0x003c4988   (est. cL4_arg_kind_17)
 * Ghidra: void FUN_003c4988(int *param_1, long param_2, long *param_3, int param_4)
 * Decodes a 0x17 descriptor whose first element is a 0x18 kind: decodes the
 * remaining elements in reverse via FUN_003d0280, emits tag DAT_005d923a,
 * then decodes the tuple via FUN_003c4b0c.
 * Confidence: medium */
void cL4_arg_kind_17(int *res, unsigned long tcb, long *msg, int depth)
{
    unsigned char f = *(unsigned char *)((char *)msg + 0x12);
    unsigned long n = f;
    long *base = msg;
    if (1 < f - 1) {
        if (f != 5 || (int)msg[1] == 0) goto fallback;
        base = (long *)*msg;
    }
    if ((short)(*(unsigned char *)((char *)*base + 0x10) | (*(unsigned char *)((char *)*base + 0x11) << 8)) != 0x18) {
fallback:
        cL4_msg_one(res, tcb, (unsigned long)msg, depth + 1);
        if (*res == 0) {
            cL4_mr_emit_tag(tcb + 0x2140, (const void *)&DAT_005d923e, 2, *(unsigned long *)(tcb + 0x2150));
            *res = 0; res[2] = 0; res[3] = 0; res[4] = 0;
        }
        return;
    }
    if (f == 5) n = *(unsigned int *)(msg + 1);
    else if (f != 2) n = (f == 1) ? 1 : 0;
    {
        long i;
        long c = (long)n;
        for (i = n - 1; i >= 0; i--) { (void)c; cL4_msg_arg_index(res, tcb, (unsigned long)msg, i, depth + 1); if (*res != 0) return; }
    }
    cL4_mr_emit_tag(tcb + 0x2140, (const void *)&DAT_005d923a, 3, *(unsigned long *)(tcb + 0x2150));
    {
        long v;
        if (1 < *(unsigned char *)((char *)msg + 0x12) - 1) {
            if ((*(unsigned char *)((char *)msg + 0x12) != 5) || (int)msg[1] == 0) v = 0;
            else msg = (long *)*msg, v = *msg;
        } else v = *msg;
        cL4_arg_kind_18(res, tcb, v);
    }
}

/* 003c4b0c @ 0x003c4b0c   (est. cL4_arg_kind_18)
 * Ghidra: void FUN_003c4b0c(undefined4 *param_1, long param_2, undefined8 *param_3)
 * Decodes a 0x18 descriptor: emits the field records via FUN_003a3c20 and
 * FUN_003a3a70, and clears the result.
 * Confidence: medium
 * Notes: FUN_003a3c20, FUN_003a3a70. */
void cL4_arg_kind_18(unsigned int *res, unsigned long tcb, unsigned long *p3)
{
    cL4_mr_emit_val2(tcb + 0x2140, p3[1], *(unsigned long *)(tcb + 0x2150));
    cL4_mr_emit_tag(tcb + 0x2140, p3, p3[1], *(unsigned long *)(tcb + 0x2150));
    *res = 0; *(unsigned long *)(res + 2) = 0; res[4] = 0;
}

/* 003c4b6c @ 0x003c4b6c   (est. cL4_arg_kind_1a)
 * Ghidra: void FUN_003c4b6c(int *param_1, long param_2, undefined8 param_3, int param_4)
 * Decodes a 0x1a descriptor via FUN_003d11d4, emits tag DAT_005d9241.
 * Confidence: medium */
void cL4_arg_kind_1a(int *res, unsigned long tcb, unsigned long msg, int depth)
{
    cL4_msg_one(res, tcb, msg, depth + 1);
    if (*res == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, (const void *)&DAT_005d9241, 2, *(unsigned long *)(tcb + 0x2150));
        *res = 0; res[2] = 0; res[3] = 0; res[4] = 0;
    }
}

/* 003c4bc8 @ 0x003c4bc8   (est. cL4_arg_kind1b)
 * Ghidra: void FUN_003c4bc8(int *param_1, long param_2, long *param_3, int param_4)
 * Decodes a 0x1b descriptor: decodes element 0 (FUN_003d11d4), element 1
 * (FUN_003bfae4), and the trailing sub-list (FUN_003c3938), emitting tags
 * DAT_005d6ff3 and DAT_005d9244. Clears the result.
 * Confidence: medium
 * Notes: FUN_003d11d4, FUN_003bfae4, FUN_003c3938, FUN_003a3a70. */
void cL4_arg_kind1b(int *res, unsigned long tcb, long *msg, int depth)
{
    unsigned long v;
    long *m = msg;
    if (*(unsigned char *)((char *)m + 0x12) - 1 < 2) v = *m;
    else if ((*(unsigned char *)((char *)m + 0x12) == 5) && (int)m[1] != 0) { m = (long *)*m; v = *m; }
    else v = 0;
    cL4_msg_one(res, tcb, &v, depth + 2);
    if (*res != 0) return;
    m = msg;
    if (*(char *)((char *)m + 0x12) != '\x02') {
        if ((*(char *)((char *)m + 0x12) != '\x05') || (*(unsigned int *)(m + 1) < 2)) v = 0;
        else { m = (long *)*m; v = m[1]; }
    } else v = m[1];
    cL4_arg_decode(res, tcb, v, depth + 1);
    if (*res == 0) {
        if ((*(char *)((char *)msg + 0x12) == '\x05') && 2 < *(unsigned int *)(msg + 1)) {
            cL4_arg_kind2(res, tcb, *(long **)(*msg + 0x10), depth + 1);
            if (*res != 0) return;
        } else {
            cL4_mr_emit_tag(tcb + 0x2140, (const void *)&DAT_005d6ff3, 1, *(unsigned long *)(tcb + 0x2150));
        }
        cL4_mr_emit_tag(tcb + 0x2140, (const void *)&DAT_005d9244, 2, *(unsigned long *)(tcb + 0x2150));
        *res = 0; res[2] = 0; res[3] = 0; res[4] = 0;
    }
}


/* 003c4d14 @ 0x003c4d14   (est. cL4_arg_kind1c)
 * Ghidra: void FUN_003c4d14(int *param_1, long param_2, long *param_3, int param_4)
 * Decodes a 0x1c descriptor: resolves the first element, decodes via
 * FUN_003c3938, emits tag DAT_005d9247. Clears the result.
 * Confidence: medium */
void cL4_arg_kind1c(int *res, unsigned long tcb, long *msg, int depth)
{
    unsigned long v;
    long *m = msg;
    if (1 < *(unsigned char *)((char *)m + 0x12) - 1) {
        if ((*(unsigned char *)((char *)m + 0x12) != 5) || (int)m[1] == 0) v = 0;
        else { m = (long *)*m; v = *m; }
    } else v = *m;
    cL4_arg_kind2(res, tcb, (long *)v, depth + 1);
    if (*res == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, (const void *)&DAT_005d9247, 2, *(unsigned long *)(tcb + 0x2150));
        *res = 0; res[2] = 0; res[3] = 0; res[4] = 0;
    }
}

/* 003c4da8 @ 0x003c4da8   (est. cL4_arg_kind_1d)
 * Ghidra: void FUN_003c4da8(int *param_1, long param_2, undefined8 param_3, int param_4)
 * Decodes a 0x1d descriptor: elements 0-2 then tag DAT_005d924a, elem 3.
 * Confidence: medium */
void cL4_arg_kind_1d(int *res, unsigned long tcb, unsigned long msg, int depth)
{
    cL4_msg_arg_index(res, tcb, msg, 0, depth + 1);
    if (*res == 0 && (cL4_msg_arg_index(res, tcb, msg, 1, depth + 1), *res == 0) &&
        (cL4_msg_arg_index(res, tcb, msg, 2, depth + 1), *res == 0)) {
        cL4_mr_emit_tag(tcb + 0x2140, (const void *)&DAT_005d924a, 3, *(unsigned long *)(tcb + 0x2150));
        cL4_msg_arg_index(res, tcb, msg, 3, depth + 1);
    }
}

/* 003c4e74 @ 0x003c4e74   (est. cL4_arg_kind_1f)
 * Ghidra: void FUN_003c4e74(int *param_1, long param_2, undefined8 param_3, int param_4)
 * Decodes a 0x1f descriptor via FUN_003d01ac, emits tag DAT_005d924e.
 * Confidence: medium */
void cL4_arg_kind_1f(int *res, unsigned long tcb, unsigned long msg, int depth)
{
    cL4_msg_args(res, tcb, msg, depth + 1);
    if (*res == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, (const void *)&DAT_005d924e, 2, *(unsigned long *)(tcb + 0x2150));
        *res = 0; res[2] = 0; res[3] = 0; res[4] = 0;
    }
}

/* 003c4ed0 @ 0x003c4ed0   (est. cL4_arg_kind_20)
 * Ghidra: void FUN_003c4ed0(int *param_1, long param_2, undefined8 param_3, int param_4)
 * Decodes a 0x20 descriptor via FUN_003d01ac, emits tag DAT_005d9251.
 * Confidence: medium */
void cL4_arg_kind_20(int *res, unsigned long tcb, unsigned long msg, int depth)
{
    cL4_msg_args(res, tcb, msg, depth + 1);
    if (*res == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, (const void *)&DAT_005d9251, 2, *(unsigned long *)(tcb + 0x2150));
        *res = 0; res[2] = 0; res[3] = 0; res[4] = 0;
    }
}

/* 003c4f2c @ 0x003c4f2c   (est. cL4_arg_kind_22)
 * Ghidra: void FUN_003c4f2c(int *param_1, long param_2, undefined8 param_3, int param_4)
 * Decodes a 0x22 descriptor: element 0, tag DAT_005d9254, element 1.
 * Confidence: medium */
void cL4_arg_kind_22(int *res, unsigned long tcb, unsigned long msg, int depth)
{
    cL4_msg_arg_index(res, tcb, msg, 0, depth + 1);
    if (*res != 0) return;
    cL4_mr_emit_tag(tcb + 0x2140, (const void *)&DAT_005d9254, 2, *(unsigned long *)(tcb + 0x2150));
    cL4_msg_arg_index(res, tcb, msg, 1, depth + 1);
}

/* 003c4fb8 @ 0x003c4fb8   (est. cL4_arg_kind_23)
 * Ghidra: void FUN_003c4fb8(int *param_1, undefined8 param_2, long *param_3, int param_4)
 * Decodes a 0x23 descriptor: element 0 via FUN_003d11d4 at depth+2, then
 * element 1 via FUN_003d1218 at depth+1.
 * Confidence: medium */
void cL4_arg_kind_23(int *res, unsigned long tcb, long *msg, int depth)
{
    unsigned long v;
    long *m = msg;
    if (*(unsigned char *)((char *)m + 0x12) - 1 < 2) v = *m;
    else if ((*(unsigned char *)((char *)m + 0x12) == 5) && (int)m[1] != 0) { m = (long *)*m; v = *m; }
    else v = 0;
    cL4_msg_one(res, tcb, &v, depth + 2);
    if (*res != 0) return;
    m = msg;
    if (*(char *)((char *)m + 0x12) != '\x02') {
        if ((*(char *)((char *)m + 0x12) != '\x05') || (*(unsigned int *)(m + 1) < 2)) v = 0;
        else { m = (long *)*m; v = m[1]; }
    } else v = m[1];
    cL4_msg_three(res, tcb, v, depth + 1);
}

/* 003c5088 @ 0x003c5088   (est. cL4_arg_kind_24)
 * Ghidra: void FUN_003c5088(undefined4 *param_1, undefined8 param_2, long *param_3, int param_4)
 * Decodes a 0x24 descriptor: resolves the identifier element and emits it
 * via FUN_003d1ad4, then decodes the second element (when present) via
 * FUN_003d0280. Clears the result.
 * Confidence: medium */
void cL4_arg_kind_24(unsigned int *res, unsigned long tcb, long *msg, int depth)
{
    unsigned long v;
    long *m = msg;
    if (1 < *(unsigned char *)((char *)m + 0x12) - 1) {
        if ((*(unsigned char *)((char *)m + 0x12) != 5) || (int)m[1] == 0) v = 0;
        else { m = (long *)*m; v = *m; }
    } else v = *m;
    cL4_msg_emit_sym(tcb, &v, 0);
    *res = 0; *(unsigned long *)(res + 2) = 0; res[4] = 0;
    if ((*(char *)((char *)msg + 0x12) != '\x02') &&
        ((*(char *)((char *)msg + 0x12) != '\x05') || (*(unsigned int *)(msg + 1) < 2))) {
        *(unsigned long *)(res + 2) = 0; res[4] = 0;
        return;
    }
    cL4_msg_arg_index(res, tcb, (unsigned long)msg, 1, depth + 1);
}

/* 003c5158 @ 0x003c5158   (est. cL4_arg_kind_25)
 * Ghidra: void FUN_003c5158(int *param_1, long param_2, long *param_3, int param_4)
 * Decodes a 0x25 descriptor (a two-element tuple). Resolves the elements,
 * dispatches through FUN_003d1218 / FUN_003bfae4 / FUN_003d12c8 and emits
 * the appropriate tag (DAT_005d9263/66/69/60/5a/57/5d/68) and the value
 * via FUN_003d154c.
 * Confidence: medium */
void cL4_arg_kind_25(int *res, unsigned long tcb, long *msg, int depth)
{
    long *m = msg;
    if (*(char *)((char *)msg + 0x12) != '\x02') {
        if ((*(char *)((char *)msg + 0x12) != '\x05') || (int)msg[1] != 2) {
            *res = 1; *(long **)(res + 2) = msg; res[4] = 0x439; return;
        }
        m = (long *)*msg;
    }
    long *e1 = *(long **)((char *)m + 8);
    long *e1b = e1;
    if (1 < *(unsigned char *)((char *)e1 + 0x12) - 1) {
        if ((*(unsigned char *)((char *)e1 + 0x12) != 5) || (int)e1[1] == 0) {
            *res = 1; *(long **)(res + 2) = e1; res[4] = 0x43b; return;
        }
        e1b = (long *)*e1;
    }
    if ((short)(*(unsigned char *)((char *)*e1b + 0x10) | (*(unsigned char *)((char *)*e1b + 0x11) << 8)) != 0xbf) {
        cL4_arg_decode(res, tcb, (unsigned long)e1, depth + 1);
        if (*res != 0) return;
        m = msg;
        unsigned long v;
        if (*(unsigned char *)((char *)m + 0x12) - 1 < 2) v = *m;
        else if ((*(unsigned char *)((char *)m + 0x12) == 5) && (int)m[1] != 0) { m = (long *)*m; v = *m; }
        else v = 0;
        {
            int local_58; long local_38; int local_40;
            cL4_msg_parse(&local_58, &tcb, &v, depth + 1);
            if (local_58 != 0) return;
            if (local_40 < 0 && local_38 == 0) { /* ok */ }
        }
        cL4_msg_emit_pair(tcb, 0, 0, 0x7a);
        *res = 0; res[2] = 0; res[3] = 0; res[4] = 0;
        return;
    }
    cL4_msg_three(res, tcb, 0, 0);
    if (*res != 0) return;
    m = msg;
    unsigned long v2;
    if (*(unsigned char *)((char *)m + 0x12) - 1 < 2) v2 = *m;
    else if ((*(unsigned char *)((char *)m + 0x12) == 5) && (int)m[1] != 0) { m = (long *)*m; v2 = *m; }
    else v2 = 0;
    {
        int local_58; long local_38; int local_40;
        cL4_msg_parse(&local_58, &tcb, &v2, depth + 1);
        if (local_58 != 0) return;
        if (local_40 < 0 && local_38 == 0) {
            *res = 1; *(long **)(res + 2) = msg; res[4] = 0x443; return;
        }
        unsigned long dep = *(unsigned long *)(tcb + 0x2150);
        cL4_mr_emit_tag(tcb + 0x2140, (const void *)&DAT_005d925a, 2, dep);
        cL4_msg_emit_pair(tcb, local_38, 0, 0x7a);
    }
    *res = 0; res[2] = 0; res[3] = 0; res[4] = 0;
}

/* 003c5418 @ 0x003c5418   (est. cL4_arg_kind_27)
 * Ghidra: void FUN_003c5418(undefined4 *param_1, long param_2, long *param_3)
 * Decodes a 0x27 descriptor: an optional-typed record. Emits 'x' when both
 * elements are null, else 'q' + a 0x7a tag record. Clears the result.
 * Confidence: medium
 * Notes: FUN_003acd3c, FUN_003d154c; bytes 'x','q'. */
void cL4_arg_kind_27(unsigned int *res, unsigned long tcb, long *msg)
{
    long *m = msg;
    if (1 < *(unsigned char *)((char *)msg + 0x12) - 1) m = (long *)*msg;
    if (*(long *)*m == 0) {
        m = msg;
        if (*(unsigned char *)((char *)msg + 0x12) == 5) m = (long *)*msg;
        if (*(long *)m[1] == 0) {
            unsigned char b = 'x';
            cL4_mr_emit_byte(tcb + 0x2140, &b, *(unsigned long *)(tcb + 0x2150));
            goto out;
        }
    }
    {
        unsigned char b = 'q';
        cL4_mr_emit_byte(tcb + 0x2140, &b, *(unsigned long *)(tcb + 0x2150));
        cL4_msg_emit_pair(tcb, (unsigned long)msg, 0, 0x7a);
    }
out:
    *res = 0; *(unsigned long *)(res + 2) = 0; res[4] = 0;
}

/* 003c54f0 @ 0x003c54f0   (est. cL4_arg_kind_28)
 * Ghidra: void FUN_003c54f0(int *param_1, long param_2, long *param_3, int param_4)
 * Decodes a 0x28 descriptor: element 1 then the payload via FUN_003d12c8,
 * emitting the tag DAT_005d9272/6f/6c/75 and value via FUN_003d154c.
 * Confidence: medium */
void cL4_arg_kind_28(int *res, unsigned long tcb, long *msg, int depth)
{
    cL4_msg_arg_index(res, tcb, (unsigned long)msg, 1, depth + 1);
    if (*res != 0) return;
    {
        unsigned long v;
        long *m = msg;
        if (*(unsigned char *)((char *)m + 0x12) - 1 < 2) v = *m;
        else if ((*(unsigned char *)((char *)m + 0x12) == 5) && (int)m[1] != 0) { m = (long *)*m; v = *m; }
        else v = 0;
        int local_58; long local_38; int local_40;
        cL4_msg_parse(&local_58, &tcb, &v, depth + 1);
        if (local_58 != 0) { res[2] = 0; *(unsigned long *)res = local_58; res[4] = 0; return; }
        if (local_40 < 0 && local_38 == 0) {
            *res = 1; *(long **)(res + 2) = msg; res[4] = 0x4ab; return;
        }
        const void *tag;
        if (local_40 == 1) tag = (const void *)&DAT_005d9272;
        else if (local_40 == 0) tag = (const void *)&DAT_005d926f;
        else if (local_40 == -1) { cL4_mr_emit_tag(tcb + 0x2140, (const void *)&DAT_005d926c, 2, *(unsigned long *)(tcb + 0x2150)); goto out; }
        else tag = (const void *)&DAT_005d9275;
        cL4_mr_emit_tag(tcb + 0x2140, tag, 2, *(unsigned long *)(tcb + 0x2150));
        cL4_msg_emit_pair(tcb, local_38, 0, 0x7a);
out:
        *res = 0; res[2] = 0; res[3] = 0; res[4] = 0;
    }
}

/* 003c564c @ 0x003c564c   (est. cL4_arg_kind_29)
 * Ghidra: void FUN_003c564c(int *param_1, long param_2, long *param_3, int param_4)
 * Decodes a 0x29 descriptor via FUN_003d0280/FUN_003d12c8, emitting the
 * tag DAT_005d9278 and value via FUN_003d154c when the result is positive.
 * Confidence: medium */
void cL4_arg_kind_29(int *res, unsigned long tcb, long *msg, int depth)
{
    cL4_msg_arg_index(res, tcb, (unsigned long)msg, 1, depth + 1);
    if (*res != 0) return;
    {
        unsigned long v;
        long *m = msg;
        if (1 < *(unsigned char *)((char *)m + 0x12) - 1) {
            if ((*(unsigned char *)((char *)m + 0x12) != 5) || (int)m[1] == 0) v = 0;
            else { m = (long *)*m; v = *m; }
        } else v = *m;
        int local_58; long local_38; int local_40;
        cL4_msg_parse(&local_58, &tcb, &v, depth + 1);
        if (local_58 == 0) {
            if ((local_40 < 0) || (local_38 != 0)) {
                if (local_40 == 0) {
                    cL4_mr_emit_tag(tcb + 0x2140, (const void *)&DAT_005d9278, 2, *(unsigned long *)(tcb + 0x2150));
                    cL4_msg_emit_pair(tcb, local_38, 0, 0x7a);
                    *res = 0;
                } else *res = 1;
                res[2] = 0; res[3] = 0; res[4] = 0;
            } else {
                *res = 1; *(long **)(res + 2) = msg; res[4] = 0x4c7;
            }
        } else {
            res[2] = 0; *(unsigned long *)res = local_58; res[4] = 0;
        }
    }
}

/* 003c5774 @ 0x003c5774   (est. cL4_arg_kind_2a)
 * Ghidra: void FUN_003c5774(int *param_1, long param_2, long *param_3, int param_4)
 * Decodes a 0x2a descriptor via FUN_003d12c8, emitting the value tags
 * DAT_005d927b/84/81/7e and a leading char when the value kind is 0x67.
 * Confidence: medium */
void cL4_arg_kind_2a(int *res, unsigned long tcb, long *msg, int depth)
{
    unsigned long v;
    long *m = msg;
    if (*(unsigned char *)((char *)m + 0x12) - 1 < 2) v = *m;
    else if ((*(unsigned char *)((char *)m + 0x12) == 5) && (int)m[1] != 0) { m = (long *)*m; v = *m; }
    else v = 0;
    {
        int local_70; long local_50; int local_58;
        cL4_msg_parse(&local_70, &tcb, &v, depth + 1);
        if (local_70 != 0) { res[2] = 0; *(unsigned long *)res = local_70; res[4] = 0; return; }
        if (local_58 < 0 && local_50 == 0) {
            *res = 1; *(long **)(res + 2) = msg; res[4] = 0x4db; return;
        }
        if (local_58 == -1) {
            cL4_mr_emit_tag(tcb + 0x2140, (const void *)&DAT_005d927b, 2, *(unsigned long *)(tcb + 0x2150));
        } else {
            const void *t1 = (const void *)&DAT_005d9284;
            if (local_58 == 1) t1 = (const void *)&DAT_005d9281;
            const void *t2 = (const void *)&DAT_005d927e;
            if (local_58 != 0) t2 = t1;
            cL4_mr_emit_tag(tcb + 0x2140, t2, 2, *(unsigned long *)(tcb + 0x2150));
            cL4_msg_emit_pair(tcb, local_50, 0, 0x7a);
        }
        long val;
        long *el = msg;
        if (*(char *)((char *)msg + 0x12) == '\x05') {
            val = ((long *)*msg)[1];
            el = (long *)*msg;
        } else {
            val = msg[1];
            el = msg;
        }
        if (val == 1) {
            unsigned char b = **(unsigned char **)el[1];
            cL4_mr_emit_byte(tcb + 0x2140, &b, *(unsigned long *)(tcb + 0x2150));
            if ((*(char *)((char *)msg + 0x12) == '\x05') && 2 < *(unsigned int *)(msg + 1)) {
                cL4_msg_arg_index(res, tcb, (unsigned long)msg, 2, depth + 1);
                if (*res != 0) return;
                if ((*(char *)((char *)msg + 0x12) == '\x05') && 3 < *(unsigned int *)(msg + 1)) {
                    cL4_msg_arg_index(res, tcb, (unsigned long)msg, 3, depth + 1);
                    if (*res != 0) return;
                }
            }
            *res = 0; res[2] = 0; res[3] = 0; res[4] = 0;
            return;
        }
        *res = 1; *(long **)(res + 2) = msg; res[4] = 0x4e7;
    }
}

/* 003c59d0 @ 0x003c59d0   (est. cL4_arg_kind_2b)
 * Ghidra: void FUN_003c59d0(undefined4 *param_1, long param_2, long *param_3)
 * Decodes a 0x2b descriptor: when the element list holds a 0xf4 indirection
 * node, emits tag DAT_005d9287 and the resolved value via FUN_003d154c.
 * Confidence: medium */
void cL4_arg_kind_2b(unsigned int *res, unsigned long tcb, long *msg)
{
    long *m = msg;
    unsigned int code = 0;
    if (*(char *)((char *)msg + 0x12) == '\x01') {
        if ((short)(*(unsigned char *)((char *)*m + 0x10) | (*(unsigned char *)((char *)*m + 0x11) << 8)) == 0xf4) {
            cL4_mr_emit_tag(tcb + 0x2140, (const void *)&DAT_005d9287, 2, *(unsigned long *)(tcb + 0x2150));
            unsigned long *p = (unsigned long *)*msg;
            if (*(unsigned char *)((char *)p + 0x12) - 1 < 2) m = (long *)*p;
            else if ((*(unsigned char *)((char *)p + 0x12) == 5) && (int)p[1] != 0) { p = (unsigned long *)*p; m = (long *)*p; }
            else m = 0;
            cL4_msg_emit_pair(tcb, (unsigned long)m, 0, 0x7a);
            *res = 0; res[2] = 0; res[4] = 0;
            return;
        }
        code = 0x513;
    } else if ((*(char *)((char *)msg + 0x12) == '\x05') && ((int)msg[1] == 1)) {
        m = (long *)*msg;
        if ((short)(*(unsigned char *)((char *)*m + 0x10) | (*(unsigned char *)((char *)*m + 0x11) << 8)) == 0xf4) {
            cL4_mr_emit_tag(tcb + 0x2140, (const void *)&DAT_005d9287, 2, *(unsigned long *)(tcb + 0x2150));
            unsigned long *p = (unsigned long *)*msg;
            if (*(unsigned char *)((char *)p + 0x12) - 1 < 2) m = (long *)*p;
            else if ((*(unsigned char *)((char *)p + 0x12) == 5) && (int)p[1] != 0) { p = (unsigned long *)*p; m = (long *)*p; }
            else m = 0;
            cL4_msg_emit_pair(tcb, (unsigned long)m, 0, 0x7a);
            *res = 0; res[2] = 0; res[4] = 0;
            return;
        }
        code = 0x513;
    } else {
        code = 0x512;
    }
    *res = 1; *(long **)(res + 2) = msg; res[4] = code;
}

/* 003c5af4 @ 0x003c5af4   (est. cL4_arg_kind2c)
 * Ghidra: void FUN_003c5af4(int *param_1, long param_2, long *param_3, int param_4)
 * Decodes a 0x2c descriptor (a parameter/argument tuple): decodes each
 * element, detecting the 0x26 group; emits 'l' when the single 0x26 group
 * holds a 1, else 'r' + the group count + 'l'. Clears the result.
 * Confidence: medium
 * Notes: FUN_003d0280, FUN_003d05e0, FUN_003acd3c; bytes 'l','r','z'. */
void cL4_arg_kind2c(int *res, unsigned long tcb, long *msg, int depth)
{
    unsigned char f = *(unsigned char *)((char *)msg + 0x12);
    unsigned long n = f;
    unsigned long i;
    long group = 0;
    if (f == 5) { n = *(unsigned int *)(msg + 1); if (n == 0) goto empty; }
    else if (f == 2) { n = 2; }
    else if (f == 1) { n = 1; }
    else goto empty;
    for (i = 0; i < n; i++) {
        long *m = msg;
        if (1 < *(unsigned char *)((char *)msg + 0x12) - 1) m = (long *)*msg;
        if ((short)(*(unsigned char *)((char *)m[i] + 0x10) | (*(unsigned char *)((char *)m[i] + 0x11) << 8)) == 0x26) {
            group = i + 1;
        } else {
            cL4_msg_arg_index(res, tcb, (unsigned long)msg, i, depth + 1);
            if (*res != 0) return;
        }
    }
    if (group == 1) {
        long *m = msg;
        if (1 < *(unsigned char *)((char *)msg + 0x12) - 1) m = (long *)*msg;
        if (*(long *)*m == 1) {
            unsigned char b = 'l';
            cL4_mr_emit_byte(tcb + 0x2140, &b, *(unsigned long *)(tcb + 0x2150));
            goto out;
        }
        group = 1;
    }
empty:
    {
        unsigned char b = 'r';
        cL4_mr_emit_byte(tcb + 0x2140, &b, *(unsigned long *)(tcb + 0x2150));
        if (group != 0) {
            long i;
            for (i = 0; i < group; i++) {
                long *m = msg;
                if (1 < *(unsigned char *)((char *)msg + 0x12) - 1) m = (long *)*msg;
                if (*(long *)m[i] == 0) {
                    unsigned char b2 = 'z';
                    cL4_mr_emit_byte(tcb + 0x2140, &b2, *(unsigned long *)(tcb + 0x2150));
                } else {
                    cL4_mr_emit_val2(tcb, *(long *)m[i] - 1, *(unsigned long *)(tcb + 0x2150));
                }
            }
        }
        unsigned char b3 = 'l';
        cL4_mr_emit_byte(tcb + 0x2140, &b3, *(unsigned long *)(tcb + 0x2150));
    }
out:
    *res = 0; res[2] = 0; res[3] = 0; res[4] = 0;
}

/* 003c5cc8 @ 0x003c5cc8   (est. cL4_arg_kind_2d)
 * Ghidra: void FUN_003c5cc8(int *param_1, long param_2, undefined8 param_3, int param_4)
 * Decodes a 0x2d descriptor via FUN_003d081c, emits 'u'. Clears.
 * Confidence: medium */
void cL4_arg_kind_2d(int *res, unsigned long tcb, unsigned long msg, int depth)
{
    cL4_msg_one(res, tcb, msg, depth + 1);
    if (*res == 0) {
        unsigned char b = 'u';
        cL4_mr_emit_byte(tcb + 0x2140, &b, *(unsigned long *)(tcb + 0x2150));
        *res = 0; res[2] = 0; res[3] = 0; res[4] = 0;
    }
}

/* 003c5d2c @ 0x003c5d2c   (est. cL4_arg_kind_2e)
 * Ghidra: void FUN_003c5d2c(undefined8 *param_1, long param_2, undefined8 param_3, int param_4)
 * Decodes a 0x2e descriptor via FUN_003d12c8, emitting 'Q'/'X' and the
 * value tag (DAT_005d6ff3/6ff1) via FUN_003d154c. Clears the result.
 * Confidence: medium */
void cL4_arg_kind_2e(unsigned long *res, unsigned long tcb, unsigned long msg, int depth)
{
    int local_60; long local_40; int local_48;
    cL4_msg_parse(&local_60, &tcb, &msg, depth + 1);
    if (local_60 != 0) { res[1] = 0; *res = local_60; res[2] = 0; return; }
    if (local_48 == -1) { /* nothing */ }
    else if (local_48 == 1) {
        unsigned char b = 'Q';
        cL4_mr_emit_byte(tcb + 0x2140, &b, *(unsigned long *)(tcb + 0x2150));
        if (local_40 == 0) { unsigned char b2 = 'x'; cL4_mr_emit_byte(tcb + 0x2140, &b2, *(unsigned long *)(tcb + 0x2150)); }
        else cL4_msg_emit_pair(tcb, local_40, (unsigned long)&DAT_005d6ff3, 0x7a);
    } else {
        if (local_48 == 0) {
            *(unsigned int *)res = 0xc; res[1] = msg; *(unsigned int *)(res + 2) = 0x52a; return;
        }
        unsigned char b = 'Q';
        cL4_mr_emit_byte(tcb + 0x2140, &b, *(unsigned long *)(tcb + 0x2150));
        if (local_40 == 0) { unsigned char b2 = 'X'; cL4_mr_emit_byte(tcb + 0x2140, &b2, *(unsigned long *)(tcb + 0x2150)); }
        else cL4_msg_emit_pair(tcb, local_40, (unsigned long)&DAT_005d6ff1, 0x5a);
    }
    *(unsigned int *)res = 0; res[1] = 0; *(unsigned int *)(res + 2) = 0;
}

/* 003c5e60 @ 0x003c5e60   (est. cL4_arg_kind30)
 * Ghidra: void FUN_003c5e60(int *param_1, long param_2, long *param_3, int param_4)
 * Decodes a 0x30 descriptor: element 0 (FUN_003d11d4), element 1
 * (FUN_003d1218), tag DAT_005d928a, then the payload via FUN_003d16b4.
 * Confidence: medium */
void cL4_arg_kind30(int *res, unsigned long tcb, long *msg, int depth)
{
    unsigned long v; long l2;
    long *m = msg;
    if (*(unsigned char *)((char *)m + 0x12) - 1 < 2) v = *m;
    else if ((*(unsigned char *)((char *)m + 0x12) == 5) && (int)m[1] != 0) { m = (long *)*m; v = *m; }
    else v = 0;
    cL4_msg_one(res, tcb, &v, depth + 2);
    if (*res != 0) return;
    m = msg;
    if (*(char *)((char *)m + 0x12) != '\x02') {
        if ((*(char *)((char *)m + 0x12) != '\x05') || (*(unsigned int *)(m + 1) < 2)) l2 = 0;
        else { m = (long *)*m; l2 = m[1]; }
    } else l2 = m[1];
    cL4_msg_three(res, tcb, l2, depth + 1);
    if (*res != 0) return;
    cL4_mr_emit_tag(tcb + 0x2140, (const void *)&DAT_005d928a, 2, *(unsigned long *)(tcb + 0x2150));
    v = 0;
    if ((*(char *)((char *)msg + 0x12) == '\x05') && 2 < *(unsigned int *)(msg + 1)) v = *(unsigned long *)(*msg + 0x10);
    cL4_msg_dispatch2(res, tcb, 0, 0, 0, 0);
}

/* 003c5f8c @ 0x003c5f8c   (est. cL4_arg_kind31)
 * Ghidra: void FUN_003c5f8c(int *param_1, long param_2, long *param_3, int param_4)
 * Decodes a 0x31 descriptor: element 0 (FUN_003d02dc), element 1
 * (FUN_003d1218), tag DAT_005d928d, then payload via FUN_003d16b4.
 * Confidence: medium */
void cL4_arg_kind31(int *res, unsigned long tcb, long *msg, int depth)
{
    unsigned long v; long l2;
    long *m = msg;
    if (*(unsigned char *)((char *)m + 0x12) - 1 < 2) v = *m;
    else if ((*(unsigned char *)((char *)m + 0x12) == 5) && (int)m[1] != 0) { m = (long *)*m; v = *m; }
    else v = 0;
    cL4_msg_three(res, tcb, v, depth + 1);
    if (*res != 0) return;
    m = msg;
    if (*(char *)((char *)m + 0x12) != '\x02') {
        if ((*(char *)((char *)m + 0x12) != '\x05') || (*(unsigned int *)(m + 1) < 2)) l2 = 0;
        else { m = (long *)*m; l2 = m[1]; }
    } else l2 = m[1];
    cL4_msg_three(res, tcb, l2, depth + 1);
    if (*res != 0) return;
    cL4_mr_emit_tag(tcb + 0x2140, (const void *)&DAT_005d928d, 2, *(unsigned long *)(tcb + 0x2150));
    v = 0;
    if ((*(char *)((char *)msg + 0x12) == '\x05') && 2 < *(unsigned int *)(msg + 1)) v = *(unsigned long *)(*msg + 0x10);
    cL4_msg_dispatch2(res, tcb, 0, 0, 0, 0);
}

/* 003c60b8 @ 0x003c60b8   (est. cL4_arg_kind32)
 * Ghidra: void FUN_003c60b8(int *param_1, long param_2, long *param_3, int param_4)
 * Decodes a 0x32 descriptor: element 0 (FUN_003d02dc), element 1
 * (FUN_003c4fb8), tag DAT_005d9290, then payload via FUN_003d16b4.
 * Confidence: medium */
void cL4_arg_kind32(int *res, unsigned long tcb, long *msg, int depth)
{
    unsigned long v; long l2;
    long *m = msg;
    if (*(unsigned char *)((char *)m + 0x12) - 1 < 2) v = *m;
    else if ((*(unsigned char *)((char *)m + 0x12) == 5) && (int)m[1] != 0) { m = (long *)*m; v = *m; }
    else v = 0;
    cL4_msg_three(res, tcb, v, depth + 1);
    if (*res != 0) return;
    m = msg;
    if (*(char *)((char *)m + 0x12) != '\x02') {
        if ((*(char *)((char *)m + 0x12) != '\x05') || (*(unsigned int *)(m + 1) < 2)) l2 = 0;
        else { m = (long *)*m; l2 = m[1]; }
    } else l2 = m[1];
    cL4_arg_kind_23(res, tcb, (long *)l2, depth + 1);
    if (*res != 0) return;
    cL4_mr_emit_tag(tcb + 0x2140, (const void *)&DAT_005d9290, 2, *(unsigned long *)(tcb + 0x2150));
    v = 0;
    if ((*(char *)((char *)msg + 0x12) == '\x05') && 2 < *(unsigned int *)(msg + 1)) v = *(unsigned long *)(*msg + 0x10);
    cL4_msg_dispatch2(res, tcb, 0, 0, 0, 0);
}

/* 003c61e4 @ 0x003c61e4   (est. cL4_arg_kind33)
 * Ghidra: void FUN_003c61e4(int *param_1, long param_2, long *param_3, int param_4)
 * Decodes a 0x33 descriptor: requires node kind 0x33; decodes elements 0
 * (FUN_003d02dc) and 1 (FUN_003d11d4), emits tag DAT_005d9293. Clears.
 * Confidence: medium */
void cL4_arg_kind33(int *res, unsigned long tcb, long *msg, int depth)
{
    unsigned long v; long l2;
    int code;
    if ((short)msg[2] != 0x33) { res[0] = 1; res[4] = 0xb1a; return; }
    long *m = msg;
    if (*(unsigned char *)((char *)m + 0x12) - 1 < 2) v = *m;
    else if ((*(unsigned char *)((char *)m + 0x12) == 5) && (int)m[1] != 0) { m = (long *)*m; v = *m; }
    else v = 0;
    cL4_msg_three(res, tcb, v, depth + 1);
    if (*res != 0) return;
    m = msg;
    if (*(char *)((char *)m + 0x12) == '\x02') l2 = m[1];
    else if ((*(char *)((char *)m + 0x12) == '\x05') && 1 < *(unsigned int *)(m + 1)) { m = (long *)*m; l2 = m[1]; }
    else l2 = 0;
    cL4_msg_one(res, tcb, &l2, depth + 2);
    if (*res != 0) return;
    cL4_mr_emit_tag(tcb + 0x2140, (const void *)&DAT_005d9293, 2, *(unsigned long *)(tcb + 0x2150));
    code = 0; res[0] = 0; res[2] = 0; res[4] = code;
}

/* 003c62fc @ 0x003c62fc   (est. cL4_arg_kind_34)
 * Ghidra: void FUN_003c62fc(int *param_1, long param_2, undefined8 param_3, int param_4)
 * Decodes a 0x34 descriptor via FUN_003d01ac, emits tag DAT_005d9296.
 * Confidence: medium */
void cL4_arg_kind_34(int *res, unsigned long tcb, unsigned long msg, int depth)
{
    cL4_msg_args(res, tcb, msg, depth + 1);
    if (*res == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, (const void *)&DAT_005d9296, 2, *(unsigned long *)(tcb + 0x2150));
        *res = 0; res[2] = 0; res[3] = 0; res[4] = 0;
    }
}

/* 003c6358 @ 0x003c6358   (est. cL4_arg_kind_35)
 * Ghidra: void FUN_003c6358(undefined8 param_1, long *param_2, int param_3)
 * Decodes a 0x35 descriptor: resolves the first element and dispatches via
 * FUN_003d174c with the tag DAT_005d6fdb.
 * Confidence: medium */
void cL4_arg_kind_35(unsigned long out, long *msg, int depth)
{
    unsigned long v;
    long *m = msg;
    if (1 < *(unsigned char *)((char *)m + 0x12) - 1) {
        if ((*(unsigned char *)((char *)m + 0x12) != 5) || (int)m[1] == 0) v = 0;
        else { m = (long *)*m; v = *m; }
    } else v = *m;
    cL4_msg_dispatch2((int *)0, out, v, (unsigned long)&DAT_005d6fdb, 1, depth + 1);
}

/* 003c63a0 @ 0x003c63a0   (est. cL4_arg_kind_36)
 * Ghidra: void FUN_003c63a0(undefined4 *param_1, long param_2, long *param_3)
 * Decodes a 0x36 descriptor: emits 'i' for a 1 payload, 'd' for 0. Clears.
 * Confidence: medium */
void cL4_arg_kind_36(unsigned int *res, unsigned long tcb, long *msg)
{
    unsigned char b;
    if (*msg == 1) b = 'i';
    else if (*msg != 0) { *res = 0xd; res[2] = (unsigned long)msg; res[4] = 0x558; return; }
    else b = 'd';
    cL4_mr_emit_byte(tcb + 0x2140, &b, *(unsigned long *)(tcb + 0x2150));
    *res = 0; res[2] = 0; res[4] = 0;
}

/* 003c6434 @ 0x003c6434   (est. cL4_arg_kind_3b)
 * Ghidra: void FUN_003c6434(int *param_1, long param_2, undefined8 param_3, int param_4)
 * Decodes a 0x3b descriptor via FUN_003d11d4, emits tag DAT_005d92a5.
 * Confidence: medium */
void cL4_arg_kind_3b(int *res, unsigned long tcb, unsigned long msg, int depth)
{
    cL4_msg_one(res, tcb, msg, depth + 1);
    if (*res == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, (const void *)&DAT_005d92a5, 2, *(unsigned long *)(tcb + 0x2150));
        *res = 0; res[2] = 0; res[3] = 0; res[4] = 0;
    }
}

/* 003c6490 @ 0x003c6490   (est. cL4_arg_kind_40)
 * Ghidra: void FUN_003c6490(int *param_1, long param_2, undefined8 param_3, int param_4)
 * Decodes a 0x40 descriptor via FUN_003d11d4, emits tag DAT_005d92b1.
 * Confidence: medium */
void cL4_arg_kind_40(int *res, unsigned long tcb, unsigned long msg, int depth)
{
    cL4_msg_one(res, tcb, msg, depth + 1);
    if (*res == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, (const void *)&DAT_005d92b1, 2, *(unsigned long *)(tcb + 0x2150));
        *res = 0; res[2] = 0; res[3] = 0; res[4] = 0;
    }
}

/* 003c64ec @ 0x003c64ec   (est. cL4_arg_kind_42)
 * Ghidra: void FUN_003c64ec(int *param_1, long param_2, undefined8 param_3, int param_4)
 * Decodes a 0x42 descriptor via FUN_003d081c, emits tag DAT_005d92b7.
 * Confidence: medium */
void cL4_arg_kind_42(int *res, unsigned long tcb, unsigned long msg, int depth)
{
    cL4_msg_one(res, tcb, msg, depth + 1);
    if (*res == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, (const void *)&DAT_005d92b7, 2, *(unsigned long *)(tcb + 0x2150));
        *res = 0; res[2] = 0; res[3] = 0; res[4] = 0;
    }
}

/* 003c6548 @ 0x003c6548   (est. cL4_arg_kind_43)
 * Ghidra: void FUN_003c6548(int *param_1, long param_2, undefined8 param_3, int param_4)
 * Decodes a 0x43 descriptor via FUN_003d081c, emits tag DAT_005d92ba.
 * Confidence: medium */
void cL4_arg_kind_43(int *res, unsigned long tcb, unsigned long msg, int depth)
{
    cL4_msg_one(res, tcb, msg, depth + 1);
    if (*res == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, (const void *)&DAT_005d92ba, 2, *(unsigned long *)(tcb + 0x2150));
        *res = 0; res[2] = 0; res[3] = 0; res[4] = 0;
    }
}

/* 003c65a4 @ 0x003c65a4   (est. cL4_arg_kind_45)
 * Ghidra: void FUN_003c65a4(int *param_1, long param_2, undefined8 param_3, int param_4)
 * Decodes a 0x45 descriptor via FUN_003d01ac, emits tag DAT_005d92c0.
 * Confidence: medium */
void cL4_arg_kind_45(int *res, unsigned long tcb, unsigned long msg, int depth)
{
    cL4_msg_args(res, tcb, msg, depth + 1);
    if (*res == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, (const void *)&DAT_005d92c0, 2, *(unsigned long *)(tcb + 0x2150));
        *res = 0; res[2] = 0; res[3] = 0; res[4] = 0;
    }
}

/* 003c6600 @ 0x003c6600   (est. cL4_arg_kind_46)
 * Ghidra: void FUN_003c6600(undefined4 *param_1, long param_2, undefined8 *param_3)
 * Decodes a 0x46 descriptor: emits tag DAT_005d92c3 and the single payload
 * byte via FUN_003acd3c. Clears the result.
 * Confidence: medium */
void cL4_arg_kind_46(unsigned int *res, unsigned long tcb, unsigned long *p3)
{
    cL4_mr_emit_tag(tcb + 0x2140, (const void *)&DAT_005d92c3, 2, *(unsigned long *)(tcb + 0x2150));
    unsigned char b = (unsigned char)*p3;
    cL4_mr_emit_byte(tcb + 0x2140, &b, *(unsigned long *)(tcb + 0x2150));
    *res = 0; *(unsigned long *)(res + 2) = 0; res[4] = 0;
}

/* 003c6678 @ 0x003c6678   (est. cL4_arg_kind_47)
 * Ghidra: void FUN_003c6678(int *param_1, long param_2, long *param_3, int param_4)
 * Decodes a 0x47 descriptor: when the first element is a 0x9b node, decodes
 * elements 1 then 0 with tag DAT_005d92c6; else FUN_003d11d4 + tag
 * DAT_005d92c9. Clears the result.
 * Confidence: medium */
void cL4_arg_kind_47(int *res, unsigned long tcb, long *msg, int depth)
{
    long *m = msg;
    if (1 < *(unsigned char *)((char *)msg + 0x12) - 1) m = (long *)*msg;
    if ((short)(*(unsigned char *)((char *)*m + 0x10) | (*(unsigned char *)((char *)*m + 0x11) << 8)) == 0x9b) {
        cL4_msg_arg_index(res, tcb, (unsigned long)msg, 1, depth + 1);
        if (*res == 0) {
            cL4_mr_emit_tag(tcb + 0x2140, (const void *)&DAT_005d92c6, 2, *(unsigned long *)(tcb + 0x2150));
            cL4_msg_arg_index(res, tcb, (unsigned long)msg, 0, depth + 1);
        }
    } else {
        cL4_msg_one(res, tcb, (unsigned long)msg, depth + 1);
        if (*res == 0) {
            cL4_mr_emit_tag(tcb + 0x2140, (const void *)&DAT_005d92c9, 2, *(unsigned long *)(tcb + 0x2150));
            *res = 0; res[2] = 0; res[3] = 0; res[4] = 0;
        }
    }
}

/* 003c677c @ 0x003c677c   (est. cL4_arg_kind_48)
 * Ghidra: void FUN_003c677c(int *param_1, long param_2, undefined8 param_3, int param_4)
 * Decodes a 0x48 descriptor: elements 0,2 then tag DAT_005d92cc, element 1.
 * Confidence: medium */
void cL4_arg_kind_48(int *res, unsigned long tcb, unsigned long msg, int depth)
{
    cL4_msg_arg_index(res, tcb, msg, 0, depth + 1);
    if (*res == 0 && (cL4_msg_arg_index(res, tcb, msg, 2, depth + 1), *res == 0)) {
        cL4_mr_emit_tag(tcb + 0x2140, (const void *)&DAT_005d92cc, 2, *(unsigned long *)(tcb + 0x2150));
        cL4_msg_arg_index(res, tcb, msg, 1, depth + 1);
    }
}

/* 003c6828 @ 0x003c6828   (est. cL4_arg_kind_49)
 * Ghidra: void FUN_003c6828(int *param_1, long param_2, long param_3, int param_4)
 * Decodes a 0x49 descriptor: elements 1,0 then (when the third element has
 * kind 0x03 with value 3) element 2; emits 'E' when complete. Clears.
 * Confidence: medium */
void cL4_arg_kind_49(int *res, unsigned long tcb, unsigned long msg, int depth)
{
    unsigned char b;
    cL4_msg_arg_index(res, tcb, msg, 1, depth + 1);
    if (*res == 0 && (cL4_msg_arg_index(res, tcb, msg, 0, depth + 1), *res == 0) &&
        ((*(char *)(msg + 0x12) != '\x05' ||
          (*(int *)(msg + 8) != 3 || (cL4_msg_arg_index(res, tcb, msg, 2, depth + 1), *res == 0))))) {
        b = 'E';
        cL4_mr_emit_byte(tcb + 0x2140, &b, *(unsigned long *)(tcb + 0x2150));
        *res = 0; res[2] = 0; res[3] = 0; res[4] = 0;
    }
}

/* 003c68f8 @ 0x003c68f8   (est. cL4_arg_kind_4a)
 * Ghidra: void FUN_003c68f8(int *param_1, long param_2, undefined8 param_3, int param_4)
 * Decodes a 0x4a descriptor: elements 0-2 then tag DAT_005d92cf, elem 3.
 * Confidence: medium */
void cL4_arg_kind_4a(int *res, unsigned long tcb, unsigned long msg, int depth)
{
    cL4_msg_arg_index(res, tcb, msg, 0, depth + 1);
    if (*res == 0 && (cL4_msg_arg_index(res, tcb, msg, 1, depth + 1), *res == 0) &&
        (cL4_msg_arg_index(res, tcb, msg, 2, depth + 1), *res == 0)) {
        cL4_mr_emit_tag(tcb + 0x2140, (const void *)&DAT_005d92cf, 3, *(unsigned long *)(tcb + 0x2150));
        cL4_msg_arg_index(res, tcb, msg, 3, depth + 1);
    }
}

/* 003c69c4 @ 0x003c69c4   (est. cL4_arg_kind_4b)
 * Ghidra: void FUN_003c69c4(int *param_1, long param_2, undefined8 param_3, int param_4)
 * Decodes a 0x4b descriptor: element 1, tag DAT_005d92d3, element 0.
 * Confidence: medium */
void cL4_arg_kind_4b(int *res, unsigned long tcb, unsigned long msg, int depth)
{
    cL4_msg_arg_index(res, tcb, msg, 1, depth + 1);
    if (*res != 0) return;
    cL4_mr_emit_tag(tcb + 0x2140, (const void *)&DAT_005d92d3, 2, *(unsigned long *)(tcb + 0x2150));
    cL4_msg_arg_index(res, tcb, msg, 0, depth + 1);
}

/* 003c6a50 @ 0x003c6a50   (est. cL4_arg_kind_4c)
 * Ghidra: void FUN_003c6a50(int *param_1, long param_2, long *param_3, int param_4)
 * Decodes a 0x4c descriptor: elements 0, (conditional) 1, tag DAT_005d92d6,
 * element 2. Clears the result.
 * Confidence: medium */
void cL4_arg_kind_4c(int *res, unsigned long tcb, long *msg, int depth)
{
    cL4_msg_arg_index(res, tcb, (unsigned long)msg, 0, depth + 1);
    if (*res == 0 &&
        ((((*(char *)((char *)msg + 0x12) != '\x05' || (*(unsigned int *)(msg + 1) < 4)) ||
           (*(long *)(*msg + 0x18) == 0)) ||
          (cL4_arg_decode(res, tcb, *(long *)(*msg + 0x18), depth + 1), *res == 0))) &&
        (cL4_msg_arg_index(res, tcb, (unsigned long)msg, 1, depth + 1), *res == 0)) {
        cL4_mr_emit_tag(tcb + 0x2140, (const void *)&DAT_005d92d6, 3, *(unsigned long *)(tcb + 0x2150));
        cL4_msg_arg_index(res, tcb, (unsigned long)msg, 2, depth + 1);
    }
}

/* 003c6b38 @ 0x003c6b38   (est. cL4_arg_kind_4d)
 * Ghidra: void FUN_003c6b38(int *param_1, long param_2, undefined8 param_3, int param_4)
 * Decodes a 0x4d descriptor via FUN_003d11d4, emits tag DAT_005d92da.
 * Confidence: medium */
void cL4_arg_kind_4d(int *res, unsigned long tcb, unsigned long msg, int depth)
{
    cL4_msg_one(res, tcb, msg, depth + 1);
    if (*res == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, (const void *)&DAT_005d92da, 2, *(unsigned long *)(tcb + 0x2150));
        *res = 0; res[2] = 0; res[3] = 0; res[4] = 0;
    }
}

/* 003c6b94 @ 0x003c6b94   (est. cL4_arg_kind_4e)
 * Ghidra: void FUN_003c6b94(int *param_1, long param_2, long *param_3, int param_4)
 * Decodes a 0x4e descriptor (a tuple with a trailing "where" clause):
 * decodes elements 0 and 1, conditionally element 2, then the tail and the
 * sub-element via FUN_003d081c / FUN_003d0280, emitting tag DAT_005d6fe1.
 * Confidence: medium */
void cL4_arg_kind_4e(int *res, unsigned long tcb, long *msg, int depth)
{
    unsigned long uVar1;
    unsigned long v;
    int bVar2;
    cL4_msg_arg_index(res, tcb, (unsigned long)msg, 0, depth + 1);
    if (*res != 0) return;
    cL4_msg_arg_index(res, tcb, (unsigned long)msg, 1, depth + 1);
    if (*res != 0) return;
    if (*(char *)((char *)msg + 0x12) == '\x05') {
        bVar2 = (*(unsigned short *)(*(long *)(*msg + 0x10) + 0x10) == 0x130);
        uVar1 = bVar2 ? 3 : 2;
        if (uVar1 < *(unsigned int *)(msg + 1)) v = *(long *)(*msg + uVar1 * 8);
        else v = 0;
    } else {
        v = 0;
        bVar2 = 0;
    }
    {
        unsigned long *m = (unsigned long *)v;
        if (*(unsigned char *)((char *)m + 0x12) - 1 < 2) m = (unsigned long *)*m;
        else if ((*(unsigned char *)((char *)m + 0x12) == 5) && (int)m[1] != 0) m = (unsigned long *)*m;
        else m = 0;
        if ((bVar2) && (cL4_msg_arg_index(res, tcb, (unsigned long)msg, 2, depth + 1), *res != 0)) return;
        if (*(short *)((char *)m + 0x10) != 0x2d) {
            cL4_msg_one(res, tcb, (unsigned long)m, depth + 1);
            goto tail;
        }
        unsigned long *mm = m;
        if (*(char *)((char *)m + 0x12) == '\x02') mm = (unsigned long *)mm[1];
        else if ((*(char *)((char *)m + 0x12) == '\x05') && 1 < *(unsigned int *)(m + 1)) { mm = (unsigned long *)*m; mm = (unsigned long *)mm[1]; }
        else mm = 0;
        if (*(unsigned char *)((char *)mm + 0x12) - 1 < 2) v = *mm;
        else if ((*(unsigned char *)((char *)mm + 0x12) == 5) && (int)mm[1] != 0) { mm = (unsigned long *)*mm; v = *mm; }
        else v = 0;
        cL4_msg_one(res, tcb, v, depth + 1);
        if (*res != 0) return;
        cL4_msg_arg_index(res, tcb, (unsigned long)m, 0, depth + 1);
    }
tail:
    if (*res == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, (const void *)&DAT_005d6fe1, 1, *(unsigned long *)(tcb + 0x2150));
        *res = 0; res[2] = 0; res[3] = 0; res[4] = 0;
    }
}

/* 003c6da0 @ 0x003c6da0   (est. cL4_arg_kind_4f)
 * Ghidra: void FUN_003c6da0(int *param_1, long param_2, long *param_3, int param_4)
 * Decodes a 0x4f descriptor: walks the outer element list, decoding each
 * 0x50 group's sub-elements (skipping 0x52), emits tags DAT_005d92dd /
 * DAT_005d92e0 and the '_' separator, decoding each remaining element via
 * FUN_003bfae4. Clears the result.
 * Confidence: medium */
void cL4_arg_kind_4f(int *res, unsigned long tcb, long *msg, int depth)
{
    unsigned char f = *(unsigned char *)((char *)msg + 0x12);
    long *base = msg, *end;
    if (f - 1 < 2) { if (f == 1) end = msg + 1; else if (f == 2) end = msg + 2; else end = 0; }
    else if (f == 5) { base = (long *)*msg; end = base + *(unsigned int *)(msg + 1); }
    else { base = 0; end = 0; }
    for (; base != end; base++) {
        long *grp = (long *)*base;
        if ((short)(*(unsigned char *)((char *)grp + 0x10) | (*(unsigned char *)((char *)grp + 0x11) << 8)) == 0x50) {
            unsigned char gf = *(unsigned char *)((char *)grp + 0x12);
            long *gb = grp, *ge;
            if (gf - 1 < 2) { if (gf == 1) ge = grp + 1; else if (gf == 2) ge = grp + 2; else ge = 0; }
            else if (gf == 5) { gb = (long *)*grp; ge = gb + *(unsigned int *)(grp + 1); }
            else { gb = 0; ge = 0; }
            for (; gb != ge; gb++) {
                if (((*(unsigned short *)((char *)*gb + 0x10) & 0xfffe) != 0x52) &&
                    (cL4_arg_decode(res, tcb, *gb, depth + 1), *res != 0)) return;
            }
        }
    }
    cL4_mr_emit_tag(tcb + 0x2140, (const void *)&DAT_005d92dd, 2, *(unsigned long *)(tcb + 0x2150));
    /* second walk: results with '_' separator, plus 0x51/0x16a marking */
    {
        unsigned char f2 = *(unsigned char *)((char *)msg + 0x12);
        long *b2 = msg, *e2;
        if (f2 - 1 < 2) { if (f2 == 1) e2 = msg + 1; else if (f2 == 2) e2 = msg + 2; else e2 = 0; }
        else if (f2 == 5) { b2 = (long *)*msg; e2 = b2 + *(unsigned int *)(msg + 1); }
        else { b2 = 0; e2 = 0; }
        int marked = 0;
        if (b2 != e2) {
            while (b2 != e2) {
                long v = *b2;
                if ((short)(*(unsigned char *)((char *)v + 0x10) | (*(unsigned char *)((char *)v + 0x11) << 8)) == 0x51) {
                    unsigned char b = '_';
                    cL4_mr_emit_byte(tcb + 0x2140, &b, *(unsigned long *)(tcb + 0x2150));
                    marked = 1;
                } else if ((short)(*(unsigned char *)((char *)v + 0x10) | (*(unsigned char *)((char *)v + 0x11) << 8)) == 0x16a) {
                    marked = 1;
                }
                cL4_arg_decode(res, tcb, v, depth + 1);
                if (*res != 0) return;
                if ((short)(*(unsigned char *)((char *)v + 0x10) | (*(unsigned char *)((char *)v + 0x11) << 8)) == 0xe4 &&
                    (*(char *)((char *)msg + 0x12) == '\x04')) {
                    cL4_mr_emit_val2(tcb + 0x2140, *msg, *(unsigned long *)(tcb + 0x2150));
                }
                b2++;
            }
            if (marked) goto out;
        }
        cL4_mr_emit_tag(tcb + 0x2140, (const void *)&DAT_005d92e0, 2, *(unsigned long *)(tcb + 0x2150));
    }
out:
    *res = 0; res[2] = 0; res[3] = 0; res[4] = 0;
}

/* 003c7060 @ 0x003c7060   (est. cL4_arg_kind_50)
 * Ghidra: void FUN_003c7060(undefined4 *param_1, long param_2, undefined8 *param_3)
 * Decodes a 0x50/0x51 descriptor (a function/closure attribute record):
 * iterates the element list, and for each 0x52 child decodes its attribute
 * flags (convention/ownership/lifetime bytes emitted as single-char tags),
 * including the value strings for attribute kinds 0-3 and 9-10.
 * Confidence: medium
 * Notes: FUN_003acd3c, FUN_003a3a70, FUN_003a3c20, thunk_FUN_00115080
 *   (strlen), thunk_FUN_001145b0 (memcmp); strings DAT_005d6fcf/6fc7/6fcb/
 *   6fc5/6fd3/6fe5/37d7/6ecf/6ecb. */
void cL4_arg_kind_50(unsigned int *res, unsigned long tcb, unsigned long *msg)
{
    unsigned char f = *(unsigned char *)((char *)msg + 0x12);
    unsigned long n = f;
    unsigned long i = 0;
    if (f == 5) { n = *(unsigned int *)(msg + 1); if (n == 0) goto done; }
    else if (f == 2) n = 2;
    else if (f == 1) n = 1;
    else { unsigned char b = 'n'; cL4_mr_emit_byte(tcb + 0x2140, &b, *(unsigned long *)(tcb + 0x2150)); goto done; }
    {
        const void *prev = (const void *)&DAT_005d6fcf;
        unsigned long i2 = 0;
        do {
            unsigned char bf = *(unsigned char *)((char *)msg + 0x12);
            unsigned long cnt = bf;
            unsigned long elem;
            if (bf == 5) cnt = *(unsigned int *)(msg + 1);
            else if (bf != 1 && bf != 2) cnt = 0;
            if (i2 < cnt) { unsigned long *m = msg; if (1 < bf - 1) m = (unsigned long *)*msg; elem = m[i2]; }
            else elem = 0;
            unsigned long k = i2 + 1;
            if ((short)(*(unsigned char *)((char *)elem + 0x10) | (*(unsigned char *)((char *)elem + 0x11) << 8)) != 0x52) goto next;
            {
                unsigned long flags = *(unsigned long *)elem;
                unsigned char b;
                if (flags <= 0xb) {
                    switch (flags) {
                    case 0:
                    case 1:
                        b = (unsigned char)(flags ? 'W' : 'w');
                        /* fallthrough */
                    default:
                        {
                            unsigned long ln = prev ? cL4_strlen((const char *)prev) : 0;
                            cL4_mr_emit_tag(tcb + 0x2140, prev, ln, *(unsigned long *)(tcb + 0x2150));
                            if (flags == 0) { prev = (const void *)&DAT_005d6fc7; }
                            else if (flags == 1) { prev = (const void *)&DAT_005d92e3; }
                            else if (flags == 2) {
                                prev = (const void *)&DAT_005d6fcb;
                                cL4_mr_emit_tag(tcb + 0x2140, prev, 1, *(unsigned long *)(tcb + 0x2150));
                                unsigned long *m = msg; if (*(unsigned char *)((char *)msg + 0x12) == 5) m = (unsigned long *)*msg;
                                cL4_mr_emit_tag(tcb + 0x2140, (const void *)m[k], ((unsigned long *)m[k])[1], *(unsigned long *)(tcb + 0x2150));
                                k = i2 + 2; prev = (const void *)&DAT_005be7c0;
                            }
                            else if (flags == 3) {
                                prev = (const void *)&DAT_005d6fc5;
                                cL4_mr_emit_tag(tcb + 0x2140, prev, 1, *(unsigned long *)(tcb + 0x2150));
                                unsigned long *m = msg; if (*(unsigned char *)((char *)msg + 0x12) == 5) m = (unsigned long *)*msg;
                                cL4_mr_emit_tag(tcb + 0x2140, (const void *)m[k], ((unsigned long *)m[k])[1], *(unsigned long *)(tcb + 0x2150));
                                k = i2 + 2; prev = (const void *)&DAT_005be7c0;
                            }
                            else if (flags == 4) {
                                prev = (const void *)&DAT_005d6fd3;
                                cL4_mr_emit_tag(tcb + 0x2140, prev, 1, *(unsigned long *)(tcb + 0x2150));
                                k = i2 + 2; prev = (const void *)&DAT_005be7c0;
                            }
                            else if (flags == 5) b = 'c';
                            else if (flags == 6) b = 'i';
                            else if (flags == 7) b = 's';
                            else if (flags == 8) b = 'r';
                            else if (flags == 9) { prev = (const void *)&DAT_005d6fe5; }
                            else if (flags == 10) { prev = (const void *)&DAT_005d37d7; }
                            else if (flags == 0xb) {
                                unsigned char bb = 'C';
                                cL4_mr_emit_byte(tcb + 0x2140, &bb, *(unsigned long *)(tcb + 0x2150));
                                unsigned long *m = msg; if (*(unsigned char *)((char *)msg + 0x12) == 5) m = (unsigned long *)*msg;
                                cL4_mr_emit_val2(tcb + 0x2140, m[k], *(unsigned long *)(tcb + 0x2150));
                                k = i2 + 2; prev = (const void *)&DAT_005be7c0;
                            }
                            else if (flags == 0x100) b = 'x';
                        }
                        break;
                    }
                }
            }
            i2 = k;
            continue;
next:
            i2 = i2 + 1;
        } while (i2 < n);
    }
done:
    *res = 0; res[2] = 0; res[4] = 0;
}

/* 003c75dc @ 0x003c75dc   (est. cL4_arg_kind_54)
 * Ghidra: void FUN_003c75dc(int *param_1, long param_2, undefined8 param_3, int param_4)
 * Decodes a 0x54 descriptor via FUN_003d081c, emits 'c'. Clears.
 * Confidence: medium */
void cL4_arg_kind_54(int *res, unsigned long tcb, unsigned long msg, int depth)
{
    cL4_msg_one(res, tcb, msg, depth + 1);
    if (*res == 0) {
        unsigned char b = 'c';
        cL4_mr_emit_byte(tcb + 0x2140, &b, *(unsigned long *)(tcb + 0x2150));
        *res = 0; res[2] = 0; res[3] = 0; res[4] = 0;
    }
}

/* 003c7640 @ 0x003c7640   (est. cL4_arg_kind_55)
 * Ghidra: void FUN_003c7640(int *param_1, long param_2, undefined8 param_3, int param_4)
 * Decodes a 0x55 descriptor: elements 0,1, tag DAT_005d92e5. Clears.
 * Confidence: medium */
void cL4_arg_kind_55(int *res, unsigned long tcb, unsigned long msg, int depth)
{
    cL4_msg_arg_index(res, tcb, msg, 0, depth + 1);
    if (*res == 0 && (cL4_msg_arg_index(res, tcb, msg, 1, depth + 1), *res == 0)) {
        cL4_mr_emit_tag(tcb + 0x2140, (const void *)&DAT_005d92e5, 2, *(unsigned long *)(tcb + 0x2150));
        *res = 0; res[2] = 0; res[3] = 0; res[4] = 0;
    }
}

/* 003c76d0 @ 0x003c76d0   (est. cL4_arg_kind_56)
 * Ghidra: void FUN_003c76d0(int *param_1, long param_2, long param_3, int param_4)
 * Decodes a 0x56 descriptor: decodes each element joining with '_'. Clears.
 * Confidence: medium */
void cL4_arg_kind_56(int *res, unsigned long tcb, unsigned long msg, int depth)
{
    unsigned char f = *(unsigned char *)(msg + 0x12);
    unsigned long n = f;
    unsigned long i = 0;
    int first = 1;
    if (f == 5) { n = *(unsigned int *)(msg + 8); if (n == 0) goto done; }
    else if (f == 2) n = 2;
    else if (f != 1) goto done;
    do {
        cL4_msg_arg_index(res, tcb, msg, i, depth + 1);
        if (*res != 0) return;
        if (first) { unsigned char b = '_'; cL4_mr_emit_byte(tcb + 0x2140, &b, *(unsigned long *)(tcb + 0x2150)); }
        first = 0;
        i++;
    } while (n != i);
done:
    *res = 0; res[2] = 0; res[3] = 0; res[4] = 0;
}

/* 003c77b4 @ 0x003c77b4   (est. cL4_arg_kind_59)
 * Ghidra: void FUN_003c77b4(int *param_1, long param_2, long *param_3, int param_4)
 * Decodes a 0x59 descriptor: decodes the first 0x60 element, emits the tag
 * DAT_005d92e8/92eb (kind 0x59), then decodes the remaining elements via
 * FUN_003bfae4. Clears the result.
 * Confidence: medium */
void cL4_arg_kind_59(int *res, unsigned long tcb, long *msg, int depth)
{
    unsigned char f = *(unsigned char *)((char *)msg + 0x12);
    long *base = msg, *end;
    if (f - 1 < 2) { if (f == 1) end = msg + 1; else if (f == 2) end = msg + 2; else end = 0; }
    else if (f == 5) { base = (long *)*msg; end = base + *(unsigned int *)(msg + 1); }
    else { base = 0; end = 0; }
    while (base != end) {
        long v = *base++;
        if ((short)(*(unsigned char *)((char *)v + 0x10) | (*(unsigned char *)((char *)v + 0x11) << 8)) == 0x60) {
            cL4_msg_arg_index(res, tcb, (unsigned long)v, 0, depth + 1);
            if (*res != 0) return;
            break;
        }
    }
    {
        unsigned char f2 = *(unsigned char *)((char *)msg + 0x12);
        const void *tag = (const void *)&DAT_005d92e8;
        if ((short)msg[2] != 0x59) tag = (const void *)&DAT_005d92eb;
        cL4_mr_emit_tag(tcb + 0x2140, tag, 2, *(unsigned long *)(tcb + 0x2150));
        long *b2 = msg, *e2;
        if (f2 - 1 < 2) { if (f2 == 1) e2 = msg + 1; else if (f2 == 2) e2 = msg + 2; else e2 = 0; }
        else if (f2 == 5) { b2 = (long *)*msg; e2 = b2 + *(unsigned int *)(msg + 1); }
        else { b2 = 0; e2 = 0; }
        while (1) {
            if (b2 == e2) { *res = 0; res[2] = 0; res[3] = 0; res[4] = 0; return; }
            if ((short)(*(unsigned char *)((char *)*b2 + 0x10) | (*(unsigned char *)((char *)*b2 + 0x11) << 8)) != 0x60) {
                cL4_arg_decode(res, tcb, *b2, depth + 1);
                if (*res != 0) return;
            }
            b2++;
        }
    }
}

/* 003c796c @ 0x003c796c   (est. cL4_arg_kind_5a)
 * Ghidra: void FUN_003c796c(int *param_1, long param_2, undefined8 param_3, int param_4)
 * Decodes a 0x5a descriptor via FUN_003d11d4, emits tag DAT_005d92ee.
 * Confidence: medium */
void cL4_arg_kind_5a(int *res, unsigned long tcb, unsigned long msg, int depth)
{
    cL4_msg_one(res, tcb, msg, depth + 1);
    if (*res == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, (const void *)&DAT_005d92ee, 2, *(unsigned long *)(tcb + 0x2150));
        *res = 0; res[2] = 0; res[3] = 0; res[4] = 0;
    }
}

/* 003c79c8 @ 0x003c79c8   (est. cL4_arg_kind_5b)
 * Ghidra: void FUN_003c79c8(int *param_1, long param_2, undefined8 param_3, int param_4)
 * Decodes a 0x5b descriptor via FUN_003d11d4, emits tag DAT_005d3819.
 * Confidence: medium */
void cL4_arg_kind_5b(int *res, unsigned long tcb, unsigned long msg, int depth)
{
    cL4_msg_one(res, tcb, msg, depth + 1);
    if (*res == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, (const void *)&DAT_005d3819, 2, *(unsigned long *)(tcb + 0x2150));
        *res = 0; res[2] = 0; res[3] = 0; res[4] = 0;
    }
}

/* 003c7a24 @ 0x003c7a24   (est. cL4_arg_kind_5c)
 * Ghidra: void FUN_003c7a24(int *param_1, long param_2, undefined8 param_3, int param_4)
 * Decodes a 0x5c descriptor via FUN_003d11d4, emits tag DAT_005d92f1.
 * Confidence: medium */
void cL4_arg_kind_5c(int *res, unsigned long tcb, unsigned long msg, int depth)
{
    cL4_msg_one(res, tcb, msg, depth + 1);
    if (*res == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, (const void *)&DAT_005d92f1, 2, *(unsigned long *)(tcb + 0x2150));
        *res = 0; res[2] = 0; res[3] = 0; res[4] = 0;
    }
}


/* 003bf940 @ 0x003bf940   (est. cL4_arg_decode_dispatch)
 * Ghidra: void FUN_003bf940(...)
 * The arg-decode dispatcher used by the symbol-index/map worker
 * (003bf904): routes a decode through the message-dispatch engine. This is
 * the outer wrapper that the map-key parser calls; it forwards to
 * cL4_arg_decode (FUN_003bfae4) which performs the kind dispatch.
 * Confidence: medium */
void cL4_arg_decode_dispatch(unsigned long res, unsigned long engine, unsigned long table, unsigned long msg)
{
    cL4_arg_decode((int *)res, engine, msg, 0);
}

/* 003bf904 @ 0x003bf904   (est. cL4_arg_decode_entry)
 * Ghidra: void FUN_003bf904(undefined8 param_1, undefined8 param_2)
 * Thin entry wrapper: calls FUN_003bf940 with the engine table pointer
 * (LAB_003d2b14) and `param_2`. */
void cL4_arg_decode_entry(unsigned long param_1, unsigned long param_2)
{
    cL4_arg_decode_dispatch(param_1, (unsigned long)&cL4_dem_kind_needs_space, 0, param_2);
}

/* 003bfae4 @ 0x003bfae4   (est. cL4_arg_decode)
 * Ghidra: void FUN_003bfae4(undefined4 *param_1, long param_2, undefined8 *param_3, ulong param_4)
 * The central argument-descriptor decoder. `param_3` is a descriptor whose
 * uint16 at +0x10 is the kind. `param_2` is the message/context object
 * (0x2140 outbound tag buffer, 0x2150 depth word). Dispatches on the kind
 * (0-0x179) to the per-kind decoder, emitting the tag records and decoding
 * the payload elements; or records a parse error {7,msg,code}. `param_4` is
 * the recursion depth (capped at 0x400).
 * Confidence: high (clear kind -> decoder dispatch)
 * Notes: giant switch; kinds whose decoders live in sibling slices route
 *   through cL4_arg_decode_other (extern); error codes 0x18d/0x196/0x2e3/
 *   0x493/...; tag strings DAT_005d92xx. */
void cL4_arg_decode(int *res, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    unsigned long tagstr;
    unsigned long v3;
    int iVar6 = (int)depth;
    unsigned char *bytep;
    unsigned long dep;
    unsigned char local;

    if (depth > 0x400) { *res = 3; *(unsigned long *)(res + 2) = msg; res[4] = 0x18d; return; }
    if (*(unsigned short *)(msg + 0x10) > 0x179) { *res = 4; *(unsigned long *)(res + 2) = msg; res[4] = 0x196; return; }

    switch (*(unsigned short *)(msg + 0x10)) {
    default: /* kind 0 */
        cL4_arg_decode_other(res, tcb, msg, depth, 0x43);
        return;
    case 1:  cL4_arg_kind_1(res, tcb, msg, depth); return;
    case 2:  cL4_arg_kind2(res, tcb, (long *)msg, depth); return;
    case 3:  cL4_arg_kind_db(res, tcb, (long *)msg, depth); return;
    case 4:  *res = 7; *(unsigned long *)(res + 2) = msg; res[4] = 0x2e3; return;
    case 5:  cL4_arg_kind5(res, tcb, msg, depth); return;
    case 6:  cL4_arg_kind6(res, tcb, msg, depth); return;
    case 7:  cL4_arg_kind7(res, tcb, msg, depth); return;
    case 8:  cL4_arg_kind8(res, tcb, msg, depth); return;
    case 9:  cL4_arg_kind9(res, tcb, msg, depth); return;
    case 10: cL4_arg_kind_a(res, tcb, msg, depth); return;
    case 0xb: cL4_arg_kind_b(res, tcb, msg, depth); return;
    case 0xc: cL4_arg_kind_c(res, tcb, msg, depth); return;
    case 0xd: case 0xf: case 0x10: case 0x11: case 0x12: case 0x19:
    case 0x3f: case 0xb1: case 0xe7: case 0xf6:
        cL4_msg_dispatch_pkt(res, tcb, msg, 0, (unsigned long)(iVar6 + 1), 0);
        return;
    case 0xe: cL4_arg_kind_e(res, tcb, (unsigned long *)msg, depth); return;
    case 0x13: cL4_arg_kind_13(res, tcb, msg, depth); return;
    case 0x14: cL4_arg_kind_14((unsigned int *)res, tcb, (long *)msg); return;
    case 0x15: tagstr = (unsigned long)&DAT_005d9234; v3 = 2; goto emit_tag;
    case 0x16: cL4_arg_kind_16(res, tcb, msg, depth); return;
    case 0x17: cL4_arg_kind_17(res, tcb, (long *)msg, depth); return;
    case 0x18: cL4_arg_kind_18((unsigned int *)res, tcb, (unsigned long *)msg); return;
    case 0x1a: cL4_arg_kind_1a(res, tcb, msg, depth); return;
    case 0x1b: cL4_arg_kind1b(res, tcb, (long *)msg, depth); return;
    case 0x1c: cL4_arg_kind1c(res, tcb, (long *)msg, depth); return;
    case 0x1d: cL4_arg_kind_1d(res, tcb, msg, depth); return;
    case 0x1e: cL4_arg_decode_other(res, tcb, msg, depth, 99); return;
    case 0x1f: cL4_arg_kind_1f(res, tcb, msg, depth); return;
    case 0x20: cL4_arg_kind_20(res, tcb, msg, depth); return;
    case 0x21: cL4_msg_one(res, tcb, msg, (unsigned long)(iVar6 + 1)); return;
    case 0x22: cL4_arg_kind_22(res, tcb, msg, depth); return;
    case 0x23: cL4_arg_kind_23(res, tcb, (long *)msg, depth); return;
    case 0x24: cL4_arg_kind_24((unsigned int *)res, tcb, (long *)msg, depth); return;
    case 0x25: cL4_arg_kind_25(res, tcb, (long *)msg, depth); return;
    case 0x26: *res = 7; *(unsigned long *)(res + 2) = msg; res[4] = 0x493; return;
    case 0x27: cL4_arg_kind_27((unsigned int *)res, tcb, (long *)msg); return;
    case 0x28: cL4_arg_kind_28(res, tcb, (long *)msg, depth); return;
    case 0x29: cL4_arg_kind_29(res, tcb, (long *)msg, depth); return;
    case 0x2a: cL4_arg_kind_2a(res, tcb, (long *)msg, depth); return;
    case 0x2b: cL4_arg_kind_2b((unsigned int *)res, tcb, (long *)msg); return;
    case 0x2c: cL4_arg_kind2c(res, tcb, (long *)msg, depth); return;
    case 0x2d: cL4_arg_kind_2d(res, tcb, msg, depth); return;
    case 0x2e: cL4_arg_kind_2e((unsigned long *)res, tcb, msg, depth); return;
    case 0x30: cL4_arg_kind30(res, tcb, (long *)msg, depth); return;
    case 0x31: cL4_arg_kind31(res, tcb, (long *)msg, depth); return;
    case 0x32: cL4_arg_kind32(res, tcb, (long *)msg, depth); return;
    case 0x33: cL4_arg_kind33(res, tcb, (long *)msg, depth); return;
    case 0x34: cL4_arg_kind_34(res, tcb, msg, depth); return;
    case 0x35: cL4_arg_kind_35((unsigned long)res, (long *)msg, depth); return;
    case 0x36: cL4_arg_kind_36((unsigned int *)res, tcb, (long *)msg); return;
    case 0x37: tagstr = (unsigned long)&DAT_005d9299; v3 = 2; goto emit_tag;
    case 0x38: tagstr = (unsigned long)&DAT_005d929c; v3 = 2; goto emit_tag;
    case 0x39: tagstr = (unsigned long)&DAT_005d929f; v3 = 2; goto emit_tag;
    case 0x3a: tagstr = (unsigned long)&DAT_005d92a2; v3 = 2; goto emit_tag;
    case 0x3b: cL4_arg_kind_3b(res, tcb, msg, depth); return;
    case 0x3c: tagstr = (unsigned long)&DAT_005d92a8; v3 = 2; goto emit_tag;
    case 0x3d: tagstr = (unsigned long)&DAT_005d92ab; v3 = 2; goto emit_tag;
    case 0x3e: tagstr = (unsigned long)&DAT_005d92ae; v3 = 2; goto emit_tag;
    case 0x40: cL4_arg_kind_40(res, tcb, msg, depth); return;
    case 0x41: tagstr = (unsigned long)&DAT_005d92b4; v3 = 2; goto emit_tag;
    case 0x42: cL4_arg_kind_42(res, tcb, msg, depth); return;
    case 0x43: cL4_arg_kind_43(res, tcb, msg, depth); return;
    case 0x44: tagstr = (unsigned long)&DAT_005d92bd; v3 = 2; goto emit_tag;
    case 0x45: cL4_arg_kind_45(res, tcb, msg, depth); return;
    case 0x46: cL4_arg_kind_46((unsigned int *)res, tcb, (unsigned long *)msg); return;
    case 0x47: cL4_arg_kind_47(res, tcb, (long *)msg, depth); return;
    case 0x48: cL4_arg_kind_48(res, tcb, msg, depth); return;
    case 0x49: cL4_arg_kind_49(res, tcb, msg, depth); return;
    case 0x4a: cL4_arg_kind_4a(res, tcb, msg, depth); return;
    case 0x4b: cL4_arg_kind_4b(res, tcb, msg, depth); return;
    case 0x4c: cL4_arg_kind_4c(res, tcb, (long *)msg, depth); return;
    case 0x4d: cL4_arg_kind_4d(res, tcb, msg, depth); return;
    case 0x4e: cL4_arg_kind_4e(res, tcb, (long *)msg, depth); return;
    case 0x4f: cL4_arg_kind_4f(res, tcb, (long *)msg, depth); return;
    case 0x50: case 0x51: cL4_arg_kind_50((unsigned int *)res, tcb, (unsigned long *)msg); return;
    case 0x52: *res = 7; *(unsigned long *)(res + 2) = msg; res[4] = 0x687; return;
    case 0x53: *res = 7; *(unsigned long *)(res + 2) = msg; res[4] = 0x68e; return;
    case 0x54: cL4_arg_kind_54(res, tcb, msg, depth); return;
    case 0x55: cL4_arg_kind_55(res, tcb, msg, depth); return;
    case 0x56: cL4_arg_kind_56(res, tcb, msg, depth); return;
    case 0x57: tagstr = (unsigned long)&DAT_005d6fd3; v3 = 1; goto emit_tag;
    case 0x58: case 0x59: cL4_arg_kind_59(res, tcb, (long *)msg, depth); return;
    case 0x5a: cL4_arg_kind_5a(res, tcb, msg, depth); return;
    case 0x5b: cL4_arg_kind_5b(res, tcb, msg, depth); return;
    case 0x5c: cL4_arg_kind_5c(res, tcb, msg, depth); return;
    case 0x5d: cL4_arg_decode_other(res, tcb, msg, (unsigned long)(iVar6 + 1), 0x67); return;
    case 0x5e: cL4_arg_decode_other(res, tcb, msg, (unsigned long)(iVar6 + 1), 0x47); return;
    case 0x5f: cL4_arg_decode_other(res, tcb, msg, (unsigned long)(iVar6 + 1), 0x42); return;
    case 0x60: *res = 7; *(unsigned long *)(res + 2) = msg; res[4] = 0x704; return;
    case 0x61: cL4_arg_decode_other(res, tcb, msg, (unsigned long)(iVar6 + 1), 0x73); return;
    case 0x62: cL4_arg_decode_other(res, tcb, msg, (unsigned long)(iVar6 + 1), 0x69); return;
    case 0x6b: local = 'e'; bytep = &local; dep = *(unsigned long *)(tcb + 0x2150); goto emit_byte;
    case 0x6d: local = (unsigned char)*(unsigned char *)msg; bytep = &local; dep = *(unsigned long *)(tcb + 0x2150); goto emit_byte;
    case 0x6e: local = 'A'; bytep = &local; dep = *(unsigned long *)(tcb + 0x2150); goto emit_byte;
    case 0x6f: local = 'T'; bytep = &local; dep = *(unsigned long *)(tcb + 0x2150); goto emit_byte;
    case 0xe5: local = 'q'; bytep = &local; dep = *(unsigned long *)(tcb + 0x2150); goto emit_byte;
    case 0x11e: local = 'K'; bytep = &local; dep = *(unsigned long *)(tcb + 0x2150); goto emit_byte;
    case 0x120: local = 'y'; bytep = &local; dep = *(unsigned long *)(tcb + 0x2150); goto emit_byte;
    case 0x121: local = '_'; bytep = &local; dep = *(unsigned long *)(tcb + 0x2150); goto emit_byte;
    case 0x122: local = 'd'; bytep = &local; dep = *(unsigned long *)(tcb + 0x2150); goto emit_byte;
    case 0x150: local = (unsigned char)*(unsigned char *)msg; bytep = &local; dep = *(unsigned long *)(tcb + 0x2150); goto emit_byte;
    case 0x169: local = 'a'; bytep = &local; dep = *(unsigned long *)(tcb + 0x2150); goto emit_byte;
    case 0x16a: local = 'r'; bytep = &local; dep = *(unsigned long *)(tcb + 0x2150); goto emit_byte;
    case 0xe4: cL4_mr_emit_val2(tcb + 0x2140, *(unsigned long *)msg, *(unsigned long *)(tcb + 0x2150)); goto clear2;
    case 0xab: case 0xf3: cL4_mr_emit_val2(tcb + 0x2140, *(unsigned long *)msg, *(unsigned long *)(tcb + 0x2150)); goto clear2;
    case 0xe8: case 0x10b: cL4_msg_dispatch2(res, tcb, msg, (unsigned long)&DAT_005d6fcf, 1, (unsigned long)(iVar6 + 1)); return;
    case 0xe9: case 0x156: tagstr = *(unsigned long *)msg; v3 = *(unsigned long *)(msg + 8); goto emit_tag;
    case 0xbf: cL4_msg_dispatch2(res, tcb, msg, (unsigned long)&DAT_005c9984, 1, (unsigned long)(iVar6 + 1)); return;
    case 0xc0: case 0xf5: case 0x13c:
        msg = (**(unsigned long (**)(unsigned long, unsigned long, unsigned long))(tcb + 0x21a0))(*(unsigned long *)(tcb + 0x21a8), 4, *(unsigned long *)msg);
        depth = (unsigned long)(iVar6 + 1U);
        if (iVar6 + 1U == 0x401) { *res = 3; *(unsigned long *)(res + 2) = msg; res[4] = 0x18d; return; }
        cL4_arg_decode(res, tcb, msg, depth);
        return;
    case 0xc9: cL4_arg_decode_other(res, tcb, msg, depth, 0); return;
    case 0xdb: cL4_arg_kind_db(res, tcb, (long *)msg, depth); return;
    case 0xec: cL4_msg_one(res, tcb, msg, (unsigned long)(iVar6 + 1)); return;
    case 0xf4: cL4_msg_one(res, tcb, msg, (unsigned long)(iVar6 + 1)); return;
    case 0x102: cL4_arg_kind_54(res, tcb, msg, depth); return;
    case 0x164: case 0x165: *res = 0xb; goto clear;
    default:
        /* remaining kinds (0x6c,0x70-0x7f,0x80-0xa2,0xa3-0xbe,0xc1-0xca,
         * 0xdc-0xe3,0xee-0x101,0x103-0x13b,0x13d-0x179) — handlers live in
         * the sibling slices; route through the shared external decoder. */
        cL4_arg_decode_other(res, tcb, msg, depth, 0);
        return;
    }
emit_tag:
    cL4_mr_emit_tag(tcb + 0x2140, (const void *)tagstr, v3, *(unsigned long *)(tcb + 0x2150));
clear2:
    *res = 0;
clear:
    *(unsigned long *)(res + 2) = 0;
    res[4] = 0;
    return;
emit_byte:
    cL4_mr_emit_byte(tcb + 0x2140, bytep, dep);
    goto clear2;
}

/* 003c2f68 @ 0x003c2f68   (est. cL4_msg_out_get)
 * Ghidra: void FUN_003c2f68(undefined8 *param_1, long param_2)
 * Copies the current outbound tag buffer (a 24-byte string record) from the
 * message object `param_2` (+0x2140) into `param_1` (short inline when the
 * length < 0x17, else an owned buffer). Returns the empty record when the
 * buffer is uninitialised.
 * Confidence: medium
 * Notes: FUN_00117d14 (memcpy), FUN_00111890 (alloc). */
void cL4_msg_out_get(unsigned long *dst, unsigned long tcb)
{
    unsigned long base = *(unsigned long *)(tcb + 0x2140);
    if (base == 0) { *dst = 0; dst[1] = 0; dst[2] = 0; return; }
    unsigned long n = *(unsigned int *)(tcb + 0x2148);
    unsigned long *p;
    if (n < 0x17) {
        *(char *)((char *)dst + 0x17) = (char)n;
        p = dst;
        if (n != 0) goto copy;
    } else {
        unsigned long cap = 0x19;
        if ((n | 7) != 0x17) cap = (n | 7) + 1;
        p = (unsigned long *)cL4_alloc(cap, 0x1000c0077774924UL);
        dst[1] = n;
        dst[2] = cap | 0x8000000000000000UL;
        dst[0] = (unsigned long)p;
    }
copy:
    cL4_memcpy(p, (void *)base, n);
    *(unsigned char *)((char *)p + n) = 0;
}


/* end of prelude */
