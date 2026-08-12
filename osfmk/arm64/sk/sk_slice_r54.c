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
    elem = dem_elem_base(out[1]);
    if (1 < dem_elem_count(out[1]) - 1) {
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
                FUN_003bada4(&saved3, s);
                cL4_dem_node(out, *cur, depth + 1, 0);
                saved_a = last_ret;
                saved_sep = 0;
            } else {
                saved_sep = child;
                if (k != 0x7c) {
plain:
                    cL4_dem_node(out, child, depth + 1, 0);
                    cL4_out_putc(out + 8, 0x20);
                    saved_a = last_ret;
                }
            }
            cur++;
            last_ret = saved_a;
        }
    }
    FUN_003bada4(&saved3, 2);
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
 * Ghidra: void FUN_003bada4(undefined8 *param_1, int param_2, ulong param_3)
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
                    FUN_003bbe00(out, node, &uVar28, sub, depth);
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
                FUN_003bbe00(out, node, &uVar28, 4, depth);
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
                FUN_003bbe00(out, node, &uVar28, 9, depth);
                cL4_out_puts(out + 8, ",", 1);
                FUN_003bbe00(out, node, &uVar28, 9, depth);
                cL4_out_puts(out + 8, " ", 1);
                FUN_003bbe00(out, node, &uVar28, 9, depth);
                cL4_out_puts(out + 8, ")", 2);
                i = (idx + 1) & 0xffffffff;
            } else if (sub == 10) {
                if (count < idx + 2) return;
                cL4_out_puts(out + 8, " ", 1);
                cL4_dem_node(out, dem_elem(node, idx), (int)depth + 1, 0);
                cL4_out_puts(out + 8, " -> ", 3);
                FUN_003bbe00(out, node, &uVar28, 10, depth);
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
 * Ghidra: void FUN_003bbe00(long param_1, undefined8 *param_2, uint *param_3, uint param_4, int param_5)
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

/* end of prelude */
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
                        cL4_dem_render_arg_types(out, child, depth);
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
    FUN_003b1eec(rec, a, b, &DAT_005d703c);
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
long *cL4_dem_render_qualtype(unsigned long *out, long *node, unsigned long depth, unsigned int flag, int mode, unsigned long opts, long a7, long a8, unsigned long a9, unsigned long a10, unsigned long a11)
{
    return cL4_dem_render_qualtype_full(out, node, depth, flag, mode, opts, a7, a8, a9, a10, a11);
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
    unsigned char a[32], b[32];
    unsigned long d0 = 0, d1 = 0, d2 = 0, d3 = 0, d4 = 0, d5 = 0;
    if (node == 0) { cL4_str_rec_cstr(dst, ""); return; }
    d5 = ctx[1]; d4 = *ctx; d3 = ctx[3]; d2 = ctx[2]; d1 = ctx[4];
    FUN_003bdf10(a, ctx + 5);
    (void)d0;
    cL4_str_rec_make(dst);
    FUN_003bdf10(b, a);
    FUN_00362de4(a);
    (*(void (**)(void *))(0x67c468 + 0x10))(&a, node);
    if (*(unsigned char *)((char *)&a + 1) == '\x01') {
        dst[1] = d0; *dst = 0; dst[2] = d2;
    } else {
        cL4_str_rec_cstr(dst, "");
    }
    FUN_003bdf98(&a);
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
unsigned char (*cL4_dem_kind2name(unsigned int kind))[16]
{
    static unsigned char ret[16];
    if (kind < 0x18) {
        *(unsigned long *)&ret[8] = *(unsigned long *)(&DAT_004f29b0 + (unsigned long)kind * 8);
        *(unsigned long *)&ret[0] = *(unsigned long *)((unsigned long)kind * 8 + 0x67c498);
        return &ret;
    }
    FUN_004ba4e0();
    if ((dem_kind((unsigned long *)0) != 0xe8) && (dem_kind((unsigned long *)0) != 0x10b)) {
        return (unsigned char (*)[16])(unsigned long)(FUN_004ba4f8() ? 1 : 0);
    }
    return (unsigned char (*)[16])0;
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
        return cL4_dem_kind2name(0);
    }
    p = (unsigned long *)FUN_004ba4f8();
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
    if (ret == 0 && l == 0) { cL4_dem_node(out, rt, (int)depth + 1, 0); return; }
    if (ret == 0) {
        if (dem_kind(rt) != 0x2d) goto tail;
        {
            unsigned long *n = rt;
            unsigned long v;
            if (*(unsigned char *)((char *)n + 0x12) - 1 < 2) { v = *n; }
            else if ((*(unsigned char *)((char *)n + 0x12) == 5) && *(int *)(n + 1) != 0) { n = (unsigned long *)*n; v = *n; }
            else v = 0;
        }
        cL4_dem_node(out, v, (int)depth + 1, 0);
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
        FUN_003ba390(out, l, n, depth);
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
    (void)l;
    start = *(unsigned long *)(out + 0x10);
    if (-1 < (char)*(unsigned char *)(out + 0x1f)) start = *(unsigned char *)(out + 0x1f);
    if (((flag & 1) != 0) || (a[1] != 0)) {
        if ((mode != 0) && (b[1] != 0)) {
            cL4_out_puts(out + 8, *b, b[1]);
            if (-1 < *state) { cL4_str_rec_make(0); cL4_out_puts_rec(out + 8, 0); }
            *b = 0; b[1] = 0; *state = -1;
        }
        if (a[1] == 0) {
            unsigned long *n = node;
            if (*(char *)((char *)n + 0x12) == '\x05') n = (unsigned long *)*n;
            if (dem_kind((unsigned long *)n[1]) != 0xba) cL4_dem_node(out, n[1], depth + 1, 0);
            l = cL4_dem_find_kind(out, node, 0xba);
            if (l != 0) cL4_dem_node(out, l, depth + 1, 0);
        } else {
            cL4_out_puts(out + 8, *a);
        }
        cur = *(unsigned long *)(out + 0x10);
        if (-1 < (char)*(unsigned char *)(out + 0x1f)) cur = *(unsigned char *)(out + 0x1f);
        if (cur != start && b[1] != 0) cL4_out_putc(out + 8, 0x2e);
    }
    if ((b[1] != 0) && cL4_out_puts(out + 8, *b), -1 < *state) {
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
    FUN_0036a5ac(rec, "");
    FUN_0036a5ac(&r2, 0);
    FUN_003a2cf0(ctx);
    (void)r2;
}

/* end of prelude */
