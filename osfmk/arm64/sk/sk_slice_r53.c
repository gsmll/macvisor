/* Recreated from cl4_kernel.raw (cL4 Secure Kernel, arm64e, image base 0) —
 * the cL4 microkernel (GL1). Ground truth: Ghidra FUN_ names + addresses in
 * the cl4_kernel.raw program. All names are estimates unless string/header
 * matched.
 * Slice R53: 0x3a6c28-0x3ba390.
 * This slice is the tagged-value stream serializer/deserializer: a
 * Tightbeam-style compact-data subsystem that turns a byte stream (read
 * through a stream-context: +0x38 data, +0x40 end, +0x48 position) into a
 * tree of tagged value nodes, and back. Every node is a small block: [0] data
 * pointer, [1] count/value word, [2] = 16-bit tag at +0x10, byte at +0x12 =
 * sub-type/flags. A per-context value stack (array at +0x58, count at +0x60)
 * builds/consumes nested values. */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "sk_internal.h"

/* Node accessors (node = uint64_t*). */
#define NODE_TAG(n)    (*(uint16_t *)((char *)(n) + 0x10))
#define NODE_SUBT(n)   (*(uint8_t  *)((char *)(n) + 0x12))
#define NODE_DATA(n)   ((void *)((n)[0]))
#define NODE_VAL(n)    ((n)[1])
#define NODE_SETTAG(n,t) (*(uint16_t *)((char *)(n) + 0x10) = (t))
#define NODE_SETSUBT(n,t)(*(uint8_t  *)((char *)(n) + 0x12) = (t))

/* Stream context field accessors (st = uint64_t* stream context). */
#define STREAM_DATA(st)  (*(char **)((char *)(st) + 0x38))
#define STREAM_END(st)   (*(uint64_t *)((char *)(st) + 0x40))
#define STREAM_POS(st)   (*(uint64_t *)((char *)(st) + 0x48))
#define STACK_BASE(st)   (*(uint64_t **)((char *)(st) + 0x58))
#define STACK_CNT(st)    (*(uint32_t *)((char *)(st) + 0x60))
#define STACK_ELEM(st,i) ((uint64_t *)(STACK_BASE(st)[(i)]))
#define STACK_TOP(st)    STACK_ELEM(st, STACK_CNT(st)-1)

static void memcpy_placeholder(void *d, const void *s, unsigned long n)
{ volatile char *x = d; const char *y = s; unsigned long i; for (i = 0; i < n; i++) x[i] = y[i]; }

/* ------------------------------------------------------------------ *
 * Shared stream / node helpers (extern; owned by sibling slices).
 * ------------------------------------------------------------------ */
extern uint64_t *sk_node_alloc(uint64_t *st, long n);         /* FUN_003a3898 */
extern void sk_node_add(uint64_t *parent, uint64_t *child, uint64_t *st); /* FUN_003a3460 */
extern uint64_t *sk_node_push(uint64_t *st, int tag, uint64_t *node);  /* FUN_003a4b38 */
extern uint64_t *sk_node_push2(uint64_t *st, int tag, uint64_t *a, uint64_t *b); /* FUN_003a4b98 */
extern void sk_node_finalize(uint64_t *node, int flag);       /* FUN_003a36d8 */
extern void sk_out_str(uint64_t *out, const char *str, long len); /* FUN_00112e8c */
extern uint64_t *sk_stream_dispatch(uint64_t *st);            /* FUN_003a672c */
extern uint64_t sk_val_get(uint64_t *st);                     /* FUN_003a663c */
extern uint64_t *sk_stream_pop(uint64_t *st);                 /* FUN_003a58b0 */
extern long sk_tag_simple(int tag);                           /* FUN_003a3040 */
extern uint64_t *sk_alloc_scalar(uint64_t *st, long n);       /* FUN_00365660 */
extern void sk_lock(void *lock, long op);                     /* thunk_FUN_00012568 */
extern long sk_query_flag(void);                              /* FUN_003b903c */
extern void sk_canary_panic(void) __attribute__((noreturn));  /* FUN_0011d7e8 */
extern void sk_fatal(void) __attribute__((noreturn));         /* FUN_004b89f8 */
extern uint64_t sk_ctx_op(uint64_t *a, uint64_t b, uint64_t *c, uint64_t *d, uint64_t *e); /* FUN_003a4c14 */
extern uint64_t *sk_tag_convert(uint64_t *st, uint64_t *node, int tag); /* FUN_003a4d5c */
extern void sk_log_msg(uint64_t *a, uint64_t *b);             /* FUN_00112db4 */
extern long sk_len_query(uint64_t v);                         /* FUN_00115080 */
extern void sk_grow_buf(uint64_t *st, uint64_t *buf, uint32_t *cap, int n); /* FUN_003a3aec */
extern uint64_t *sk_node_make(uint64_t *st, int tag, void *arg); /* FUN_003a3a10 */
extern void sk_grow_ptrs(uint64_t *st, uint64_t *buf, uint32_t *cap, int n); /* FUN_003a3578 */
extern void sk_ctx_setup2(uint64_t *a, long b, uint64_t *c);  /* FUN_003a4110 */
extern void sk_ctx_op2(uint64_t *a, ...);                     /* FUN_003a4f5c / 003a4ca8 */
extern void sk_obj_lock(uint64_t obj, long op);               /* FUN_00116bb4 */
extern uint64_t *sk_val_get_alt(uint64_t *st, uint32_t tag);  /* FUN_003a6874 */
extern uint64_t *sk_003a3a70(uint64_t *st, void *src, uint64_t n, uint64_t *len); /* FUN_003a3a70 */
extern void sk_write_data3(void *st, void *tag, void *fn, void *out); /* FUN_003b0be0 */
extern void sk_write_data4(uint64_t *out);                            /* FUN_003b0d64 */
extern char DAT_005d37d2[]; extern char DAT_005d37e1[]; extern char DAT_005d37cb[];
extern char DAT_005d356c[]; extern char DAT_005d37d0[]; extern char DAT_005d37c9[];
extern char DAT_005d3568[]; extern char DAT_005d37d7[]; extern char DAT_005d37e5[];
extern char DAT_005d3810[]; extern char DAT_005d6b7d[]; extern char DAT_005d6c15[];
extern char s__callee_guaranteed_005d6e4e[]; extern char s__convention_thin__005d6e6f[];
extern char s__callee_owned_005d6e61[]; extern char s__callee_unowned_005d6e3e[];
extern char s_block_005d6e81[]; extern char DAT_005d6cd7[]; extern char s_closure_005d6e9a[];
extern char s_method_005d6e87[]; extern char s_objc_method_005d6e8e[]; extern char s_witness_method_005d6ea2[];
extern char s_yield_once_005d57a1[]; extern char s_yield_many_005d57b9[]; extern char s_yield_once_2_005d57ac[];
extern char s__Sendable_005d6eb1[]; extern char s__async_005d6ebb[]; extern char s_Optional_005d4e8b[];
extern char s___C_Synthesized_005d6ef6[];
extern char s__noDerivative_005d5f5d[]; extern char DAT_005be7c0[];
extern char s_sending_005d6e12[]; extern char s_isolated_005d6e1a[];
extern char s_sil_implicit_leading_param_005d6e23[];
extern char s__in_constant_005d5ee4[]; extern char s__deallocating_005d6df0[];
extern char s__guaranteed_005d5f28[]; extern char s__inout_005d5f00[];
extern char s__pack_inout_005d5f51[]; extern char s__in_guaranteed_005d5ef1[];
extern char s__pack_guaranteed_005d5f40[]; extern char s__pack_owned_005d5f34[];
extern char s__owned_005d5f18[]; extern char s__unowned_005d5f1f[];
extern char s__inout_aliasable_005d5f07[];
extern uint64_t DAT_004f2740;
extern uint64_t FUN_003a33cc(uint64_t *node);


/* Forward declarations (all 120 slice functions; st = stream ctx). */
static uint64_t sk_003a6c28(uint64_t * st); /* FUN_003a6c28 */
static uint64_t sk_003a75e4(uint64_t * st); /* FUN_003a75e4 */
static uint64_t sk_003a7818(uint64_t * st); /* FUN_003a7818 */
static uint64_t sk_003a7d9c(uint64_t * st); /* FUN_003a7d9c */
static uint64_t sk_003a81e8(uint64_t * st, uint64_t p2, uint64_t p3); /* FUN_003a81e8 */
static uint64_t * sk_003a8868(uint64_t * st); /* FUN_003a8868 */
static uint64_t * sk_003a8ab4(uint64_t * st); /* FUN_003a8ab4 */
static uint64_t sk_003a9944(uint64_t * st); /* FUN_003a9944 */
static uint64_t sk_003aa804(uint64_t * st); /* FUN_003aa804 */
static void sk_003ab218(uint64_t * st, uint16_t p2, int32_t p3); /* FUN_003ab218 */
static uint64_t sk_003ab40c(uint64_t * st); /* FUN_003ab40c */
static void sk_003ab780(uint64_t * st); /* FUN_003ab780 */
static uint64_t sk_003ab7f4(uint64_t * st); /* FUN_003ab7f4 */
static uint64_t sk_003ab948(uint64_t * st, int32_t p2); /* FUN_003ab948 */
static uint64_t * sk_003abad0(uint64_t * st); /* FUN_003abad0 */
static uint64_t sk_003abc48(uint64_t *st); /* FUN_003abc48 (x0 returns value despite void decl) */
static uint64_t sk_003abd1c(uint64_t * st); /* FUN_003abd1c */
static void sk_003abef0(uint64_t * st); /* FUN_003abef0 */
static uint64_t sk_003abf88(uint64_t * st); /* FUN_003abf88 */
static uint64_t sk_003ac2d0(uint64_t * st, uint32_t p2, uint32_t p3); /* FUN_003ac2d0 */
static void sk_003ac394(uint64_t * st); /* FUN_003ac394 */
static int32_t sk_003ac430(uint64_t * st); /* FUN_003ac430 */
static int32_t sk_003ac4a4(uint64_t * st); /* FUN_003ac4a4 */
static uint64_t * sk_003ac52c(uint64_t * st); /* FUN_003ac52c */
static uint64_t sk_003ac580(uint64_t * st, int32_t p2, uint64_t p3); /* FUN_003ac580 */
static uint64_t sk_003ac600(uint64_t * st, uint64_t p2, uint64_t p3); /* FUN_003ac600 */
static uint64_t sk_003ac6b4(uint64_t * st, int32_t p2, uint32_t p3); /* FUN_003ac6b4 */
static void sk_003acd3c(uint64_t *buf, uint8_t *p, uint64_t *st); /* FUN_003acd3c */
static bool sk_003acda0(int32_t tag); /* FUN_003acda0 */
static uint64_t sk_003ace08(uint64_t * st); /* FUN_003ace08 */
static uint64_t * sk_003ace50(uint64_t * st); /* FUN_003ace50 */
static uint64_t sk_003acefc(void); /* FUN_003acefc */
static uint64_t sk_003acf38(uint32_t tag); /* FUN_003acf38 */
static uint64_t sk_003acfb4(uint64_t * st, uint64_t p2, uint64_t p3, uint8_t p4); /* FUN_003acfb4 */
static uint64_t * sk_003ad048(uint64_t * st); /* FUN_003ad048 */
static void sk_003ad0f0(uint64_t * st, uint64_t p2); /* FUN_003ad0f0 */
static uint64_t sk_003ad188(uint64_t * st); /* FUN_003ad188 */
static uint64_t sk_003ad278(uint64_t * st); /* FUN_003ad278 */
static uint64_t sk_003ad3a0(uint64_t * st); /* FUN_003ad3a0 */
static uint64_t sk_003ad478(uint64_t * st); /* FUN_003ad478 */
static void sk_003ad560(uint64_t * st); /* FUN_003ad560 */
static uint64_t * sk_003ad5a4(uint64_t * st); /* FUN_003ad5a4 */
static void sk_003ad61c(uint64_t * st); /* FUN_003ad61c */
static uint64_t sk_003ad67c(uint64_t * st); /* FUN_003ad67c */
static uint64_t sk_003ad724(uint64_t * st, uint64_t p2, uint64_t * p3); /* FUN_003ad724 */
static void sk_003ad810(uint64_t *buf, uint64_t *p, uint64_t *st); /* FUN_003ad810 */
static uint64_t * sk_003ad874(uint64_t * st, uint64_t * p2, uint64_t * p3, uint64_t p4); /* FUN_003ad874 */
static uint64_t sk_003adcd8(uint64_t *node); /* FUN_003adcd8 */
static uint64_t sk_003add54(uint64_t * st, uint64_t p2); /* FUN_003add54 */
static uint64_t sk_003adf20(uint64_t * st, uint64_t p2); /* FUN_003adf20 */
static uint64_t * sk_003adff0(uint64_t * st); /* FUN_003adff0 */
static uint64_t * sk_003ae05c(uint64_t * st); /* FUN_003ae05c */
static uint64_t * sk_003ae0c8(uint64_t * st); /* FUN_003ae0c8 */
static uint64_t * sk_003ae134(uint64_t * st); /* FUN_003ae134 */
static uint64_t sk_003ae1b4(uint64_t * st); /* FUN_003ae1b4 */
static uint64_t sk_003ae36c(uint64_t * st); /* FUN_003ae36c */
static uint64_t sk_003ae414(uint64_t *st, uint64_t p2); /* FUN_003ae414 (x0 returns value) */
static uint64_t sk_003ae4c8(uint64_t * st, uint64_t p2); /* FUN_003ae4c8 */
static uint64_t sk_003ae658(uint64_t * st); /* FUN_003ae658 */
static uint64_t sk_003ae734(uint64_t * st, uint64_t p2, uint64_t * p3); /* FUN_003ae734 */
static uint64_t sk_003ae8a0(uint64_t * st); /* FUN_003ae8a0 */
static uint64_t sk_003ae9e0(uint64_t * st, uint16_t p2); /* FUN_003ae9e0 */
static uint64_t * sk_003aebb0(uint64_t * st); /* FUN_003aebb0 */
static uint64_t sk_003aef74(uint64_t * st, uint64_t p2, uint64_t p3); /* FUN_003aef74 */
static void sk_003aefe4(uint64_t *buf, uint64_t *p); /* FUN_003aefe4 */
static void sk_003af0cc(uint64_t *buf, uint64_t *st); /* FUN_003af0cc */
static uint64_t sk_003af238(uint64_t * st); /* FUN_003af238 */
static uint64_t sk_003af3c4(uint64_t * st); /* FUN_003af3c4 */
static uint64_t sk_003af4d4(uint64_t * st, uint16_t p2); /* FUN_003af4d4 */
static uint64_t * sk_003af614(uint64_t * st); /* FUN_003af614 */
static uint64_t sk_003af6ac(uint64_t * st); /* FUN_003af6ac */
static uint64_t sk_003af7a4(uint64_t * st); /* FUN_003af7a4 */
static uint64_t sk_003af99c(uint64_t * st, uint16_t p2); /* FUN_003af99c */
static uint64_t sk_003aff04(uint64_t * st, uint64_t p2, uint64_t p3); /* FUN_003aff04 */
static void sk_003b0004(uint64_t * st, int32_t p2); /* FUN_003b0004 */
static uint64_t sk_003b0078(uint64_t * st); /* FUN_003b0078 */
static uint64_t * sk_003b0174(uint64_t * st); /* FUN_003b0174 */
static uint64_t sk_003b0220(uint64_t * st); /* FUN_003b0220 */
static uint64_t sk_003b02dc(uint64_t * st); /* FUN_003b02dc */
static uint64_t sk_003b03c0(uint64_t * st, uint64_t p2); /* FUN_003b03c0 */
static void sk_003b05c8(uint64_t * st, uint64_t p2); /* FUN_003b05c8 */
static uint64_t sk_003b06ac(uint64_t * st); /* FUN_003b06ac */
static bool sk_003b0a64(uint32_t tag); /* FUN_003b0a64 */
static bool sk_003b0aa4(int32_t tag); /* FUN_003b0aa4 */
static void sk_003b0b08(void); /* FUN_003b0b08 */
static void sk_003b0b0c(void); /* FUN_003b0b0c */
static void sk_003b0b28(uint64_t *obj); /* FUN_003b0b28 */
static uint64_t * sk_003b0b7c(uint64_t *lock); /* FUN_003b0b7c */
static void sk_003b0be0(uint64_t * st, uint16_t *param_2, void *param_3, uint64_t p4); /* FUN_003b0be0 */
static uint8_t sk_003b0d64(uint64_t *buf); /* FUN_003b0d64 */
extern uint64_t sk_003b0e1c(uint64_t * st, uint64_t p2); /* FUN_003b0e1c */
static uint64_t sk_003b0ec4(uint64_t a, uint8_t *b); /* FUN_003b0ec4 */
static uint64_t sk_003b0f48(uint64_t * st, uint64_t p2); /* FUN_003b0f48 */
static uint64_t sk_003b0fb8(uint64_t * st, uint64_t p2); /* FUN_003b0fb8 */
static uint64_t * sk_003b1034(uint64_t *obj); /* FUN_003b1034 */
static void sk_003b10a8(uint64_t * st, uint64_t p2); /* FUN_003b10a8 */
static uint64_t sk_003b10f0(uint8_t *p, uint64_t n); /* FUN_003b10f0 */
static uint64_t sk_003b1178(uint64_t * st); /* FUN_003b1178 */
static void sk_003b12cc(uint64_t *a, char *b, uint64_t c); /* FUN_003b12cc */
static void sk_003b1328(uint64_t *a, uint64_t *b, uint64_t c, int32_t d); /* FUN_003b1328 */
static uint64_t sk_003b1e74(uint64_t * st, uint64_t p2, uint64_t p3); /* FUN_003b1e74 */
static void sk_003b1eec(uint64_t * st, uint64_t p2, uint64_t p3, uint64_t p4); /* FUN_003b1eec */
static uint64_t sk_003b1f20(uint64_t * st, uint64_t p2, uint64_t p3); /* FUN_003b1f20 */
static uint64_t sk_003b1f98(uint64_t * st, uint64_t p2, uint64_t p3); /* FUN_003b1f98 */
static void sk_003b2010(uint64_t *a, uint64_t b, uint64_t c, uint64_t d); /* FUN_003b2010 */
static void sk_003b20f4(uint64_t * st, uint64_t * p2, uint64_t * p3, int32_t p4, uint64_t p5); /* FUN_003b20f4 */
static void sk_003b2180(uint64_t *out, uint64_t *node, uint64_t depth, uint32_t flag); /* FUN_003b2180 */
static void sk_003b8d18(uint64_t * st, uint64_t * p2, uint64_t p3, uint64_t p4); /* FUN_003b8d18 */
static void sk_003b8d94(uint64_t * st, uint64_t * p2, uint64_t p3); /* FUN_003b8d94 */
static void sk_003b8e48(uint64_t * st, uint64_t p2); /* FUN_003b8e48 */
static uint8_t sk_003b8ef8(uint64_t * st, uint64_t * p2); /* FUN_003b8ef8 */
static uint64_t sk_003b903c(uint64_t a, uint64_t *b); /* FUN_003b903c */
static void sk_003b9794(uint64_t * st, uint64_t p2, int32_t p3); /* FUN_003b9794 */
static uint64_t sk_003b982c(uint64_t * st, uint64_t * p2); /* FUN_003b982c */
static bool sk_003b9c14(uint64_t *a, uint64_t b, uint64_t c); /* FUN_003b9c14 */
static bool sk_003b9c6c(uint64_t *a); /* FUN_003b9c6c */
static void sk_003b9cb4(uint64_t * st, uint64_t * p2, uint64_t p3); /* FUN_003b9cb4 */
static uint64_t sk_003ba044(uint64_t * st, uint64_t * p2, uint32_t p3); /* FUN_003ba044 */
static void sk_003ba114(uint64_t * st, uint64_t p2, uint64_t * p3, int32_t p4, int32_t p5); /* FUN_003ba114 */
static void sk_003ba390(uint64_t *a, uint64_t b, uint64_t *c, uint64_t d); /* FUN_003ba390 */

/* ===== BODIES ===== */
/* FUN_003ac2d0 @ 0x3ac2d0   (est. sk_make_range)
 * Builds a 0x27 node with two 0x68 scalar children (p2, p3); returns NULL if
 * either is negative (sign bit set).
 * Confidence: high */
static uint64_t sk_003ac2d0(uint64_t *st, uint32_t p2, uint32_t p3)
{
    if ((int32_t)(p3 | p2) < 0) return 0;
    uint64_t *node = sk_node_alloc(st, 1);
    NODE_SETTAG(node, 0x27); NODE_SETSUBT(node, 0);
    uint64_t *a = sk_node_alloc(st, 1);
    NODE_SETTAG(a, 0x68); NODE_SETSUBT(a, 4);
    a[0] = p2;
    sk_node_add(node, a, st);
    uint64_t *b = sk_node_alloc(st, 1);
    NODE_SETTAG(b, 0x68); NODE_SETSUBT(b, 4);
    b[0] = p3;
    sk_node_add(node, b, st);
    return (uint64_t)node;
}

/* FUN_003ac394 @ 0x3ac394   (est. sk_parse_n)
 * Reads an optional 'n' prefix and an '_N_' identifier; emits a scalar node
 * (tag 0x173 if prefixed, 0x172 otherwise, sub 4) holding the negated value,
 * pushed as 0xf4.
 * Confidence: medium */
static void sk_003ac394(uint64_t *st)
{
    uint64_t pos = STREAM_POS(st);
    int32_t v;
    uint16_t tag;
    if (pos < STREAM_END(st) && STREAM_DATA(st)[pos] == 'n') {
        STREAM_POS(st) = pos + 1;
        v = -sk_003ac4a4(st);
        tag = 0x173;
    } else {
        v = sk_003ac4a4(st);
        tag = 0x172;
    }
    uint64_t *n = sk_node_alloc(st, 1);
    NODE_SETTAG(n, tag); NODE_SETSUBT(n, 4);
    n[0] = (uint64_t)v;
    sk_node_push(st, 0xf4, n);
}

/* FUN_003ac430 @ 0x3ac430   (est. sk_read_digits)
 * Reads a run of ASCII decimal digits at the current stream position;
 * returns the accumulated integer, or -1000 on overflow/no digits.
 * Confidence: high */
static int32_t sk_003ac430(uint64_t *st)
{
    uint64_t pos = STREAM_POS(st);
    int32_t acc = 0;
    if (pos < STREAM_END(st)) {
        uint8_t c = STREAM_DATA(st)[pos];
        if (c - 0x30 < 10) {
            do {
                uint8_t d = STREAM_DATA(st)[pos];
                if (9 < d - 0x30) return acc;
                int32_t nv = d + acc * 10 - 0x30;
                if (nv < acc) return -1000;      /* overflow */
                pos += 1; STREAM_POS(st) = pos;
                acc = nv;
            } while (STREAM_END(st) != pos);
            return acc;
        }
    }
    return -1000;
}

/* FUN_003ac4a4 @ 0x3ac4a4   (est. sk_read_ident)
 * Reads a '_..._' identifier: bare '_' returns 0; '_N_' returns N+1; else
 * -1000. Consumes the trailing '_'.
 * Confidence: high */
static int32_t sk_003ac4a4(uint64_t *st)
{
    uint64_t pos = STREAM_POS(st);
    if (pos < STREAM_END(st) && STREAM_DATA(st)[pos] == '_') {
        STREAM_POS(st) = pos + 1;
        return 0;
    }
    int32_t v = sk_003ac430(st);
    if (v < 0) return v;
    pos = STREAM_POS(st);
    if (STREAM_END(st) <= pos || STREAM_DATA(st)[pos] != '_') return -1000;
    STREAM_POS(st) = pos + 1;
    return v + 1;
}

/* FUN_003ac52c @ 0x3ac52c   (est. sk_parse_ab)
 * Parses an '_N_' identifier into a scalar node (tag 0xab, sub 4), or NULL.
 * Confidence: high */
static uint64_t *sk_003ac52c(uint64_t *st)
{
    int32_t v = sk_003ac4a4(st);
    if (v < 0) return NULL;
    uint64_t *n = sk_node_alloc(st, 1);
    NODE_SETTAG(n, 0xab); NODE_SETSUBT(n, 4);
    n[0] = (uint64_t)v;
    return n;
}

/* FUN_003ac580 @ 0x3ac580   (est. sk_build_children)
 * Reads a result pointer from the stream's result buffer (+0x68) at index
 * p3 (bounds-checked vs +0x70 count, p2 < 0x801), then pushes it onto the
 * value stack (p2-1) times. Returns the result pointer.
 * Confidence: medium */
static uint64_t sk_003ac580(uint64_t *st, int32_t p2, uint64_t p3)
{
    uint64_t v = 0;
    if (p2 < 0x801 && p3 < *(uint32_t *)((char *)st + 0x70)) {
        uint64_t *rbuf = *(uint64_t **)((char *)st + 0x68);
        v = rbuf[p3];
        if (1 < p2) {
            uint32_t k = p2 + 1;
            do {
                uint64_t *slot = &v;
                sk_003ad810(st + 11, slot, st);
                k = k - 1;
            } while (2 < k);
        }
    }
    return v;
}

/* FUN_003ac600 @ 0x3ac600   (est. sk_err_ab)
 * Builds an error node: allocates a 5-byte "Swift" magic buffer, wraps it in
 * an 0xa3 string node, calls sk_node_make(st,0x67,p3) for the message and
 * sk_node_push2(st,p2,...), then pushes the result as 0xf4.
 * Confidence: medium */
static uint64_t sk_003ac600(uint64_t *st, uint64_t p2, uint64_t p3)
{
    uint32_t *magic = (uint32_t *)sk_alloc_scalar(st, 5);
    magic[0] = 0x66697753;
    *(uint8_t *)(magic + 1) = 0x74;
    uint64_t *s = sk_node_alloc(st, 1);
    NODE_SETTAG(s, 0xa3); NODE_SETSUBT(s, 3);
    s[0] = (uint64_t)magic; s[1] = 5;
    uint64_t *msg = sk_node_make(st, 0x67, (void *)p3);
    uint64_t *r = sk_node_push2(st, (int)p2, s, msg);
    return (uint64_t)sk_node_push(st, 0xf4, r);
}

/* FUN_003acd3c @ 0x3acd3c   (est. sk_buf_byte)
 * Appends a byte to a growing byte buffer (buf[0]=ptr, [1]=count, +0xc=cap).
 * Confidence: high */
static void sk_003acd3c(uint64_t *buf, uint8_t *p, uint64_t *st)
{
    uint32_t cnt = *(uint32_t *)(buf + 1);
    if (*(uint32_t *)((char *)buf + 0xc) <= cnt) {
        sk_grow_buf(st, buf, (uint32_t *)((char *)buf + 0xc), 1);
        cnt = *(uint32_t *)(buf + 1);
    }
    uint8_t b = *p;
    *(uint32_t *)(buf + 1) = cnt + 1;
    *(uint8_t *)(buf[0] + cnt) = b;
}

/* FUN_003acda0 @ 0x3acda0   (est. sk_is_printable)
 * Returns true when the tag is in the printable/scalar set.
 * Confidence: medium */
static bool sk_003acda0(int32_t tag)
{
    uint32_t u = (uint32_t)(tag - 0xb7);
    if (!(0x3e < u || ((1ULL << (u & 0x3f)) & 0x400000040000020dULL) == 0)) return true;
    u = (uint32_t)(tag - 0x67);
    if (!(0x2b < u || ((1ULL << (u & 0x3f)) & 0x80004000001ULL) == 0)) return true;
    return tag == 0x16b;
}

/* FUN_003ace08 @ 0x3ace08   (est. sk_pop_a3)
 * Pops the top element: returns it if tag 0xa3, or converts a 0x67 element to
 * 0xa3 (sk_tag_convert) and returns it; else returns 0.
 * Confidence: medium */
static uint64_t sk_003ace08(uint64_t *st)
{
    if (STACK_CNT(st) != 0) {
        uint32_t i = STACK_CNT(st) - 1;
        uint64_t *e = STACK_ELEM(st, i);
        if (NODE_TAG(e) == 0xa3) { STACK_CNT(st) = i; return (uint64_t)e; }
        if (NODE_TAG(e) == 0x67) {
            STACK_CNT(st) = i;
            uint64_t *r = sk_tag_convert(st, e, 0xa3);
            return (uint64_t)r;
        }
    }
    return 0;
}

/* FUN_003ace50 @ 0x3ace50   (est. sk_pop_f4)
 * Pops a compound (0xf4) element: if it wraps a single 0x67 scalar or a
 * 5-subtype chain whose inner element is a printable leaf, returns the inner
 * leaf; else returns 0. Also accepts a printable non-0xf4 element directly.
 * Confidence: medium */
static uint64_t *sk_003ace50(uint64_t *st)
{
    uint64_t *e = (uint64_t *)sk_003ace08(st);
    if (e) return e;
    if (STACK_CNT(st) != 0) {
        uint32_t i = STACK_CNT(st) - 1;
        e = STACK_ELEM(st, i);
        if (NODE_TAG(e) == 0xf4) {
            STACK_CNT(st) = i;
            uint8_t sub = NODE_SUBT(e);
            if (sub != 1) {
                if (sub != 5) return NULL;
                if ((int32_t)e[1] != 1) return NULL;
                e = (uint64_t *)NODE_DATA(e);
            }
            e = (uint64_t *)NODE_DATA(e);
            if (!sk_003acf38(NODE_TAG(e))) return NULL;
            return e;
        }
        if (sk_003acf38(NODE_TAG(e)) != 0) {
            STACK_CNT(st) = i;
            return e;
        }
    }
    return NULL;
}

/* FUN_003acf38 @ 0x3acf38   (est. sk_tag_is_leaf)
 * Returns 1 when the tag denotes a leaf scalar (no children), else 0.
 * Confidence: medium */
static uint64_t sk_003acf38(uint32_t tag)
{
    if ((int32_t)tag < 0xbf) {
        if (tag < 0x40 && ((1ULL << (tag & 0x3f)) & 0x8000000002200000ULL) != 0) return 1;
        if (tag == 0xb1) return 1;
    } else if (((tag - 0xbf < 0x38) &&
                ((1ULL << ((tag - 0xbf) & 0x3f)) & 0xc0010000000003ULL) != 0) ||
               (tag == 0x16b)) {
        return 1;
    }
    return 0;
}

/* FUN_003acfb4 @ 0x3acfb4   (est. sk_write_bytes)
 * Serializes a value block (p2) with a tag into the output buffer via
 * FUN_003b0be0/FUN_003b0d64, returning the block pointer; locks on a negative
 * length. Returns 0 if either input is null.
 * Confidence: medium */
static uint64_t sk_003acfb4(uint64_t *st, uint64_t p2, uint64_t p3, uint8_t p4)
{
    if (p2 != 0 && p3 != 0) {
        uint64_t buf = 0, len = 0;
        uint8_t tag = p4;
        uint64_t result = p2;
        sk_write_data3(st, (void *)p3, (void *)sk_write_data4, &buf);
        if ((int64_t)len < 0) sk_lock((void *)buf, len & 0x7fffffffffffffffULL);
        return result;
    }
    return 0;
}

/* FUN_003ad048 @ 0x3ad048   (est. sk_parse_string_token)
 * Reads a decimal length (sk_003ac430); if >=1 and within the stream, copies
 * those bytes out (FUN_003a3a70), advances, returns a string node (tag 0x18,
 * sub 3) holding the copied bytes. NULL on empty/overflow.
 * Confidence: high */
static uint64_t *sk_003ad048(uint64_t *st)
{
    int32_t n = sk_003ac430(st);
    if (n < 1 || STREAM_END(st) < STREAM_POS(st) + (uint64_t)n) return NULL;
    uint64_t len = 0;
    uint64_t *data = sk_003a3a70(st, STREAM_DATA(st) + STREAM_POS(st), (uint64_t)n, &len);
    STREAM_POS(st) = STREAM_POS(st) + (uint64_t)n;
    uint64_t *node = sk_node_alloc(st, 1);
    NODE_SETTAG(node, 0x18); NODE_SETSUBT(node, 3);
    node[0] = (uint64_t)data;
    node[1] = len & 0xffffffff;
    return node;
}

/* FUN_003ad0f0 @ 0x3ad0f0   (est. sk_emit_f4)
 * Pops the top element: 0xf4 kept as-is; 0x120 replaced by a fresh 0xeb node
 * pushed as 0xf4. Pushes the result under the given tag.
 * Confidence: medium */
static void sk_003ad0f0(uint64_t *st, uint64_t p2)
{
    uint64_t *v;
    if (STACK_CNT(st) != 0) {
        uint32_t i = STACK_CNT(st) - 1;
        v = STACK_ELEM(st, i);
        if (NODE_TAG(v) == 0xf4) { STACK_CNT(st) = i; goto emit; }
        if (NODE_TAG(v) == 0x120) {
            STACK_CNT(st) = i;
            uint64_t *n = sk_node_alloc(st, 1);
            NODE_SETTAG(n, 0xeb); NODE_SETSUBT(n, 0);
            v = sk_node_push(st, 0xf4, n);
            goto emit;
        }
    }
    v = 0;
emit:
    sk_node_push(st, (int)p2, v);
}

/* FUN_003ad188 @ 0x3ad188   (est. sk_parse_ee)
 * Builds an 0xee node; if the stack top is not a 0x120 terminator, drains
 * 0xf4 elements (bounded by a 0x121 terminator) as children; finalizes and
 * pushes as 0xf4. Returns the pushed node or 0 on malformed drain.
 * Confidence: medium */
static uint64_t sk_003ad188(uint64_t *st)
{
    uint64_t *node = sk_node_alloc(st, 1);
    NODE_SETTAG(node, 0xee); NODE_SETSUBT(node, 0);
    uint32_t i = STACK_CNT(st);
    if (i == 0 || NODE_TAG(STACK_ELEM(st, i-1)) != 0x120) {
        int16_t term = 0;
        for (;;) {
            uint32_t cnt = STACK_CNT(st);
            if (cnt == 0) return 0;
            uint32_t j = cnt - 1;
            term = NODE_TAG(STACK_ELEM(st, j));
            if (term == 0x121) {
                STACK_CNT(st) = j;
                if (j == 0) return 0;
                cnt = STACK_CNT(st);
            }
            {
                uint64_t *e = STACK_ELEM(st, cnt-1);
                if (NODE_TAG(e) != 0xf4) return 0;
                STACK_CNT(st) = cnt - 1;
                sk_node_add(node, e, st);
            }
            if (term != 0x121) break;
        }
        sk_node_finalize(node, 0);
    }
    return (uint64_t)sk_node_push(st, 0xf4, node);
}

/* FUN_003ad278 @ 0x3ad278   (est. sk_parse_di)
 * Reads 'd'/'i' -> tag 0xef/0xf0; drains 0xf4 elements (bounded by 0x121)
 * into the node, finalizes, pushes as 0xf4.
 * Confidence: medium */
static uint64_t sk_003ad278(uint64_t *st)
{
    uint64_t pos = STREAM_POS(st);
    if (STREAM_END(st) <= pos) return 0;
    STREAM_POS(st) = pos + 1;
    char c = STREAM_DATA(st)[pos];
    uint16_t tag;
    if (c == 'd') tag = 0xef;
    else if (c != 'i') return 0;
    else tag = 0xf0;
    uint64_t *node = sk_node_alloc(st, 1);
    NODE_SETTAG(node, tag); NODE_SETSUBT(node, 0);
    uint32_t i = STACK_CNT(st);
    if (i == 0 || NODE_TAG(STACK_ELEM(st, i-1)) != 0x120) {
        int16_t term = 0;
        for (;;) {
            uint32_t cnt = STACK_CNT(st);
            if (cnt == 0) return 0;
            uint32_t j = cnt - 1;
            term = NODE_TAG(STACK_ELEM(st, j));
            if (term == 0x121) {
                STACK_CNT(st) = j;
                if (j == 0) return 0;
                cnt = STACK_CNT(st);
            }
            {
                uint64_t *e = STACK_ELEM(st, cnt-1);
                if (NODE_TAG(e) != 0xf4) return 0;
                STACK_CNT(st) = cnt - 1;
                sk_node_add(node, e, st);
            }
            if (term != 0x121) break;
        }
        sk_node_finalize(node, 0);
    }
    return (uint64_t)sk_node_push(st, 0xf4, node);
}

/* FUN_003ad3a0 @ 0x3ad3a0   (est. sk_parse_f7)
 * Builds an 0xf7 node; drains 0xf4 elements (bounded by 0x121); finalizes and
 * returns the node (no push).
 * Confidence: medium */
static uint64_t sk_003ad3a0(uint64_t *st)
{
    uint64_t *node = sk_node_alloc(st, 1);
    NODE_SETTAG(node, 0xf7); NODE_SETSUBT(node, 0);
    uint32_t i = STACK_CNT(st);
    if (i == 0 || NODE_TAG(STACK_ELEM(st, i-1)) != 0x120) {
        int16_t term = 0;
        for (;;) {
            uint32_t cnt = STACK_CNT(st);
            if (cnt == 0) return 0;
            uint32_t j = cnt - 1;
            term = NODE_TAG(STACK_ELEM(st, j));
            if (term == 0x121) {
                STACK_CNT(st) = j;
                if (j == 0) return 0;
                cnt = STACK_CNT(st);
            }
            {
                uint64_t *e = STACK_ELEM(st, cnt-1);
                if (NODE_TAG(e) != 0xf4) return 0;
                STACK_CNT(st) = cnt - 1;
                sk_node_add(node, e, st);
            }
            if (term != 0x121) break;
        }
        sk_node_finalize(node, 0);
    }
    return (uint64_t)node;
}

/* FUN_003ad478 @ 0x3ad478   (est. sk_parse_pair2)
 * Builds a tag-2 node; drains elements with tags in {0x30..0x33,0x1c,0x1d}
 * bounded by 0x121; finalizes and returns the node.
 * Confidence: medium */
static uint64_t sk_003ad478(uint64_t *st)
{
    uint64_t *node = sk_node_alloc(st, 1);
    NODE_SETTAG(node, 2); NODE_SETSUBT(node, 0);
    uint32_t i = STACK_CNT(st);
    if (i == 0 || NODE_TAG(STACK_ELEM(st, i-1)) != 0x120) {
        int16_t term = 0;
        for (;;) {
            uint32_t cnt = STACK_CNT(st);
            if (cnt == 0) return 0;
            uint32_t j = cnt - 1;
            term = NODE_TAG(STACK_ELEM(st, j));
            if (term == 0x121) {
                STACK_CNT(st) = j;
                if (j == 0) return 0;
                cnt = STACK_CNT(st);
            }
            {
                uint64_t *e = STACK_ELEM(st, cnt-1);
                uint32_t t = NODE_TAG(e);
                if ((3 < t - 0x30) && (1 < t - 0x1b)) return 0;
                STACK_CNT(st) = cnt - 1;
                sk_node_add(node, e, st);
            }
            if (term != 0x121) break;
        }
        sk_node_finalize(node, 0);
    }
    return (uint64_t)node;
}

/* FUN_003ad560 @ 0x3ad560   (est. sk_err_c4)
 * Reports error 0xc4 pairing sk_pop_a3 with sk_val_get(st).
 * Confidence: medium */
static void sk_003ad560(uint64_t *st)
{
    uint64_t *a = (uint64_t *)sk_003ace08(st);
    uint64_t v = sk_val_get(st);
    sk_node_push2(st, 0xc4, (uint64_t *)v, a);
}

/* FUN_003ad5a4 @ 0x3ad5a4   (est. sk_parse_ident_103)
 * Reads an '_N_' identifier: <1 -> NULL; ==1 -> bare 0x103 node; else an
 * 0x68 scalar holding (N-2).
 * Confidence: high */
static uint64_t *sk_003ad5a4(uint64_t *st)
{
    int32_t v = sk_003ac4a4(st);
    if (v < 1) return NULL;
    uint64_t *n = sk_node_alloc(st, 1);
    if (v == 1) {
        NODE_SETTAG(n, 0x103); NODE_SETSUBT(n, 0);
    } else {
        NODE_SETTAG(n, 0x68); NODE_SETSUBT(n, 4);
        n[0] = (uint64_t)(v - 2);
    }
    return n;
}

/* FUN_003ad67c @ 0x3ad67c   (est. sk_collect_da)
 * Pops consecutive 0xda elements from the stack into a new 0xf7 node;
 * finalizes and returns it (0 if none / non-0xda stops the run).
 * Confidence: medium */
static uint64_t sk_003ad67c(uint64_t *st)
{
    uint32_t cnt = STACK_CNT(st);
    uint64_t *node = 0;
    if (cnt == 0) return 0;
    do {
        uint64_t *e = STACK_TOP(st);
        if (NODE_TAG(e) != 0xda) { if (!node) return 0; break; }
        STACK_CNT(st) = cnt - 1;
        if (!node) { node = sk_node_alloc(st, 1); NODE_SETTAG(node, 0xf7); NODE_SETSUBT(node, 0); }
        sk_node_add(node, e, st);
        cnt = STACK_CNT(st);
    } while (cnt != 0);
    sk_node_finalize(node, 0);
    return (uint64_t)node;
}

/* FUN_003ad724 @ 0x3ad724   (est. sk_parse_value)
 * Parses one tagged value into the caller's scratch; creates a fresh 0xf7
 * node, records it into the result buffer, then pops 0xf4 elements off the
 * stack as children. Expects a trailing 0x120 (true) or 0x121 (false)
 * terminator; returns 1 on success (0x120) / 0 otherwise, looping on 0x121.
 * Confidence: medium */
static uint64_t sk_003ad724(uint64_t *st, uint64_t p2, uint64_t *p3)
{
    uint64_t *scratch = (uint64_t *)p2;
    uint64_t term;
    uint64_t *node;
    *p3 = 0;
    do {
        node = sk_node_alloc(st, 1);
        NODE_SETTAG(node, 0xf7); NODE_SETSUBT(node, 0);
        sk_003ad810(scratch, (uint64_t *)&node, st);
        while (true) {
            if (STACK_CNT(st) == 0) break;
            uint64_t *e = STACK_TOP(st);
            if (NODE_TAG(e) != 0xf4) break;
            STACK_CNT(st) = STACK_CNT(st) - 1;
            sk_node_add(node, e, st);
        }
        sk_node_finalize(node, 0);
        if (STACK_CNT(st) == 0) { term = 0; break; }
        {
            uint64_t *e = STACK_TOP(st);
            int16_t t = NODE_TAG(e);
            if (t == 0x121) { STACK_CNT(st) = STACK_CNT(st) - 1; continue; }
            if (t == 0x120) { STACK_CNT(st) = STACK_CNT(st) - 1; term = 1; break; }
            term = 0; break;
        }
    } while (true);
    return term;
}

/* FUN_003ad810 @ 0x3ad810   (est. sk_buf_push)
 * Appends one 64-bit word to a growing word buffer (buf[0]=ptr,[1]=cnt,+0xc=cap).
 * Confidence: high */
static void sk_003ad810(uint64_t *buf, uint64_t *p, uint64_t *st)
{
    uint32_t cnt = *(uint32_t *)(buf + 1);
    if (*(uint32_t *)((char *)buf + 0xc) <= cnt) {
        sk_grow_ptrs(st, buf, (uint32_t *)((char *)buf + 0xc), 1);
        cnt = *(uint32_t *)(buf + 1);
    }
    uint64_t w = *p;
    *(uint32_t *)(buf + 1) = cnt + 1;
    *(uint64_t *)(buf[0] + (uint64_t)cnt * 8) = w;
}

/* FUN_003adcd8 @ 0x3adcd8   (est. sk_node_is_compound)
 * Returns 1 when the node must be recursed into (not a printable leaf).
 * Confidence: medium */
static uint64_t sk_003adcd8(uint64_t *node)
{
    uint32_t u = NODE_TAG(node);
    if (NODE_TAG(node) < 0xbc) {
        if (!(0x3a < u - 0x48 || ((1ULL << ((u - 0x48) & 0x3f)) & 0x404000000000001ULL) == 0) ||
            u == 0x22) return 0;
    } else if (!(2 < u - 0xbc) ||
               (0x25 < u - 0xe6 || ((1ULL << ((u - 0xe6) & 0x3f)) & 0x2000000005ULL) == 0)) {
        return 0;
    }
    return 1;
}

/* FUN_003add54 @ 0x3add54   (est. sk_parse_group)
 * Reads a letter token selecting a Swift calling-convention attribute string
 * (inout/owned/unowned/guaranteed/... from a table at 0x5d5ee0), builds a
 * 0x6c string node and pushes it under the given tag. 'X' maps to a fixed
 * constant. Returns the pushed node or 0 when the char does not match.
 * Confidence: medium */
static uint64_t sk_003add54(uint64_t *st, uint64_t p2)
{
    uint64_t pos = STREAM_POS(st);
    uint64_t pc = 0;
    if (pos < STREAM_END(st)) {
        uint64_t np = pos + 1;
        STREAM_POS(st) = np;
        uint32_t c = STREAM_DATA(st)[pos];
        if (c - 0x62 < 0x18) {
            switch (c) {
            case 'c': pc = (uint64_t)s__in_constant_005d5ee4; break;
            case 'd': case 'f': case 'h': case 'j': case 'k': case 'o':
            case 'q': case 'r': case 's': case 't': case 'u': case 'w':
                goto bad;
            case 'e': pc = (uint64_t)s__deallocating_005d6df0; break;
            case 'g': pc = (uint64_t)s__guaranteed_005d5f28; break;
            case 'i': break;                     /* defaults to 0x5d5ee0 */
            case 'l': pc = (uint64_t)s__inout_005d5f00; break;
            case 'm': pc = (uint64_t)s__pack_inout_005d5f51; break;
            case 'n': pc = (uint64_t)s__in_guaranteed_005d5ef1; break;
            case 'p': pc = (uint64_t)s__pack_guaranteed_005d5f40; break;
            case 'v': pc = (uint64_t)s__pack_owned_005d5f34; break;
            case 'x': pc = (uint64_t)s__owned_005d5f18; break;
            case 'y': pc = (uint64_t)s__unowned_005d5f1f; break;
            default: pc = (uint64_t)s__inout_aliasable_005d5f07; break;
            }
            if (pc == 0) pc = (uint64_t)0x5d5ee0;
            goto emit;
        }
        if (c == 'X') { pc = (uint64_t)0x5d6de8; goto emit; }
    }
bad:
    STREAM_POS(st) = STREAM_POS(st) - 1;
    return 0;
emit:
    {
        uint64_t *n = sk_node_alloc(st, 1);
        NODE_SETTAG(n, 0x6c); NODE_SETSUBT(n, 3);
        n[0] = pc;
        n[1] = (uint64_t)sk_len_query(pc);
        return (uint64_t)sk_node_push(st, (int)p2, n);
    }
}

/* FUN_003adf20 @ 0x3adf20   (est. sk_parse_group2)
 * Reads a lowercase letter; if it is in the attribute set (bitmask
 * 0x125c49 over a 21-entry table at 0x67c3b0), builds a 0x6c string node
 * holding the selected string and pushes it under the given tag. Else backs
 * up the stream and returns 0.
 * Confidence: medium */
static uint64_t sk_003adf20(uint64_t *st, uint64_t p2)
{
    uint64_t pos = STREAM_POS(st);
    if (pos < STREAM_END(st)) {
        uint64_t np = pos + 1;
        STREAM_POS(st) = np;
        uint32_t c = STREAM_DATA(st)[pos] - 0x61;
        if (c < 0x15 && ((0x125c49U >> (c & 0x1f)) & 1) != 0) {
            uint64_t pc = *(uint64_t *)((uint64_t)(c & 0xff) * 8 + 0x67c3b0);
            uint64_t *n = sk_node_alloc(st, 1);
            NODE_SETTAG(n, 0x6c); NODE_SETSUBT(n, 3);
            n[0] = pc;
            n[1] = (uint64_t)sk_len_query(pc);
            return (uint64_t)sk_node_push(st, (int)p2, n);
        }
    }
    STREAM_POS(st) = STREAM_POS(st) - 1;
    return 0;
}

/* FUN_003adff0 @ 0x3adff0   (est. sk_arg_sending)
 * If the next stream char is 'T' (sending), consumes it and returns a 0x71
 * string node holding "sending"; else returns NULL.
 * Confidence: high */
static uint64_t *sk_003adff0(uint64_t *st)
{
    uint64_t pos = STREAM_POS(st);
    if (pos < STREAM_END(st) && STREAM_DATA(st)[pos] == 'T') {
        STREAM_POS(st) = pos + 1;
        uint64_t *n = sk_node_alloc(st, 1);
        NODE_SETTAG(n, 0x71); NODE_SETSUBT(n, 3);
        n[0] = (uint64_t)s_sending_005d6e12; n[1] = 7;
        return n;
    }
    return NULL;
}

/* FUN_003ae05c @ 0x3ae05c   (est. sk_arg_isolated)
 * If the next stream char is 'I' (isolated), consumes it and returns a 0x72
 * string node holding "isolated"; else returns NULL.
 * Confidence: high */
static uint64_t *sk_003ae05c(uint64_t *st)
{
    uint64_t pos = STREAM_POS(st);
    if (pos < STREAM_END(st) && STREAM_DATA(st)[pos] == 'I') {
        STREAM_POS(st) = pos + 1;
        uint64_t *n = sk_node_alloc(st, 1);
        NODE_SETTAG(n, 0x72); NODE_SETSUBT(n, 3);
        n[0] = (uint64_t)s_isolated_005d6e1a; n[1] = 8;
        return n;
    }
    return NULL;
}

/* FUN_003ae0c8 @ 0x3ae0c8   (est. sk_arg_silImplicitLeadingParam)
 * If the next stream char is 'L', consumes it and returns a 0x73 string node
 * holding "_sil_implicit_leading_param" (26 bytes); else returns NULL.
 * Confidence: high */
static uint64_t *sk_003ae0c8(uint64_t *st)
{
    uint64_t pos = STREAM_POS(st);
    if (pos < STREAM_END(st) && STREAM_DATA(st)[pos] == 'L') {
        STREAM_POS(st) = pos + 1;
        uint64_t *n = sk_node_alloc(st, 1);
        NODE_SETTAG(n, 0x73); NODE_SETSUBT(n, 3);
        n[0] = (uint64_t)s_sil_implicit_leading_param_005d6e23; n[1] = 0x1a;
        return n;
    }
    return NULL;
}

/* FUN_003ae134 @ 0x3ae134   (est. sk_arg_noDerivative)
 * If the next stream char is 'w' (noDerivative marker), consumes it and
 * returns a 0x70 string node holding "_noDerivative"; else returns a 0x70
 * string node holding the empty-string constant DAT_005be7c0.
 * Confidence: high */
static uint64_t *sk_003ae134(uint64_t *st)
{
    uint64_t pos = STREAM_POS(st);
    const char *s;
    if (pos < STREAM_END(st) && STREAM_DATA(st)[pos] == 'w') {
        STREAM_POS(st) = pos + 1;
        s = s__noDerivative_005d5f5d;
    } else {
        s = (const char *)DAT_005be7c0;
    }
    uint64_t *n = sk_node_alloc(st, 1);
    NODE_SETTAG(n, 0x70); NODE_SETSUBT(n, 3);
    n[0] = (uint64_t)s;
    n[1] = (uint64_t)sk_len_query((uint64_t)s);
    return n;
}

/* FUN_003ae1b4 @ 0x3ae1b4   (est. sk_pop_list)
 * Reads a letter and builds a list/attr node: 'A' -> sk_003ae36c result
 * wrapped in a 0x134 pair with a popped 0xf4 element; 'E' -> pop_f4 into
 * 0x132; 'M' -> pop_a3 into 0x131; 'X'/'Y' -> pop into 0x133 (Y adds a
 * second pop_f4 child). Returns the node or 0 on malformed input.
 * Confidence: medium */
static uint64_t sk_003ae1b4(uint64_t *st)
{
    uint64_t pos = STREAM_POS(st);
    if (STREAM_END(st) <= pos) return 0;
    STREAM_POS(st) = pos + 1;
    uint8_t c = STREAM_DATA(st)[pos];
    uint64_t *v, *n, *e;
    uint16_t tag;
    if (c < 0x4d) {
        if (c == 'A') {
            uint64_t *r = (uint64_t *)sk_003ae36c(st);
            if (r && STACK_CNT(st) != 0) {
                uint32_t i = STACK_CNT(st) - 1;
                v = STACK_ELEM(st, i);
                if (NODE_TAG(v) == 0xf4) {
                    STACK_CNT(st) = i;
                    return (uint64_t)sk_node_push2(st, 0x134, v, r);
                }
            }
            return 0;
        }
        if (c != 'E') return 0;
        v = sk_003ace50(st);
        if (!v) return 0;
        n = sk_node_alloc(st, 1);
        tag = 0x132;
    } else if (c == 'M') {
        v = (uint64_t *)sk_003ace08(st);
        if (!v) return 0;
        n = sk_node_alloc(st, 1);
        tag = 0x131;
    } else {
        if (c != 'X') {
            if (c != 'Y') return 0;
            if (STACK_CNT(st) == 0) return 0;
            uint32_t i = STACK_CNT(st) - 1;
            v = STACK_ELEM(st, i);
            STACK_CNT(st) = i;
            if (!v) return 0;
            e = sk_003ace50(st);
            if (!e) return 0;
            n = sk_node_alloc(st, 1);
            NODE_SETTAG(n, 0x133); NODE_SETSUBT(n, 0);
            sk_node_add(n, e, st);
            goto attach_v;
        }
        v = sk_003ace50(st);
        if (!v) return 0;
        n = sk_node_alloc(st, 1);
        tag = 0x133;
    }
    NODE_SETTAG(n, tag); NODE_SETSUBT(n, 0);
attach_v:
    sk_node_add(n, v, st);
    return (uint64_t)n;
}

/* FUN_003ae36c @ 0x3ae36c   (est. sk_parse_12f)
 * Builds a 0x12f node and drains consecutive elements returned by
 * sk_003ae658 (bounded by a 0x121 terminator) as children; finalizes on the
 * terminator. Returns the node or 0.
 * Confidence: medium */
static uint64_t sk_003ae36c(uint64_t *st)
{
    uint64_t *node = sk_node_alloc(st, 1);
    NODE_SETTAG(node, 0x12f); NODE_SETSUBT(node, 0);
    while (true) {
        bool term;
        if (STACK_CNT(st) == 0) term = true;
        else {
            uint32_t i = STACK_CNT(st) - 1;
            if (NODE_TAG(STACK_ELEM(st, i)) != 0x121) term = true;
            else { term = false; STACK_CNT(st) = i; }
        }
        uint64_t *e = (uint64_t *)sk_003ae658(st);
        if (!e) break;
        sk_node_add(node, e, st);
        if (!term) { sk_node_finalize(node, 0); return (uint64_t)node; }
    }
    return 0;
}

/* FUN_003ae4c8 @ 0x3ae4c8   (est. sk_pop_pair)
 * Drains consecutive sk_003ae658 results (bounded by a 0x121 terminator)
 * into a local buffer, then builds a 0xf4 node (either the popped 0xf4
 * element or a fresh node holding param_2) and re-wraps each buffered result
 * in a 0x2e node with it, pushing each as 0xf4. Returns the last pushed node.
 * Confidence: medium */
static uint64_t sk_003ae4c8(uint64_t *st, uint64_t p2)
{
    uint64_t local_50[4];
    uint64_t *node;
    local_50[1] = (uint64_t)sk_003b0e1c(st, 4);
    local_50[0] = DAT_004f2740;
    bool term;
    do {
        if (STACK_CNT(st) == 0) term = true;
        else {
            uint32_t i = STACK_CNT(st) - 1;
            if (NODE_TAG(STACK_ELEM(st, i)) != 0x121) term = true;
            else { term = false; STACK_CNT(st) = i; }
        }
        uint64_t *e = (uint64_t *)sk_003ae658(st);
        if (!e) return 0;
        sk_003ad810((uint64_t *)(local_50 + 1), (uint64_t *)&e, st);
    } while (!term);
    if (p2 == 0) {
        if (STACK_CNT(st) != 0) {
            uint32_t i = STACK_CNT(st) - 1;
            node = STACK_ELEM(st, i);
            if (NODE_TAG(node) == 0xf4) { STACK_CNT(st) = i; goto have; }
        }
        node = 0;
    } else {
        node = sk_node_alloc(st, 1);
        NODE_SETTAG(node, 0xf4); NODE_SETSUBT(node, 0);
        sk_node_add(node, (uint64_t *)p2, st);
    }
have:
    while (local_50[0] != 0) {
        uint64_t *item = (uint64_t *)local_50[local_50[0] - 1];
        local_50[0] -= 1;
        if (!item) break;
        uint64_t *n = sk_node_alloc(st, 1);
        NODE_SETTAG(n, 0x2e); NODE_SETSUBT(n, 0);
        uint64_t *res = 0;
        if (node && n) {
            sk_node_add(n, node, st);
            sk_node_add(n, item, st);
            res = n;
        }
        node = sk_node_push(st, 0xf4, res);
    }
    return (uint64_t)node;
}

/* FUN_003ae658 @ 0x3ae658   (est. sk_pop_attr)
 * Pops the top element: if tag 0xc0/0x16b it is used; if tag 0xf4 and
 * FUN_003a33cc accepts it, unwrap and use it; then pop a second 0x67 element.
 * Builds a 0x24 node holding both and pushes it. Returns 0 on empty.
 * Confidence: medium */
static uint64_t sk_003ae658(uint64_t *st)
{
    uint32_t cnt = STACK_CNT(st);
    uint64_t *a = 0, *b = 0;
    if (cnt != 0) {
        uint32_t i = cnt - 1;
        a = STACK_ELEM(st, i);
        int16_t t = NODE_TAG(a);
        if (t == 0xc0 || t == 0x16b) {
            STACK_CNT(st) = i;
            cnt = i;
            if (i == 0) goto no_b;
        } else if (t == 0xf4) {
            STACK_CNT(st) = i;
            uint64_t u = FUN_003a33cc(a);
            if ((u & 1) == 0) return 0;
            cnt = i;
            if (i == 0) goto no_b;
        } else a = 0;
        b = STACK_ELEM(st, cnt - 1);
        if (NODE_TAG(b) == 0x67) {
            STACK_CNT(st) = cnt - 1;
            goto have_b;
        }
    }
no_b:
    b = 0;
have_b:
    {
        uint64_t *n = sk_node_push(st, 0x24, b);
        if (a && n) sk_node_add(n, a, st);
        return (uint64_t)n;
    }
}

/* FUN_003a75e4 @ 0x3a75e4   (est. sk_parse_scalar_or_special)
 * Parses a single-letter scalar/special token from the stream into a node:
 * 'l' pops a 0x67 element and pushes as 0xba; 'L' pops 0x67 + printable and
 * pushes 0xba; an uppercase/hex-alnum letter builds a 0xd9 node wrapping a
 * 0x67 byte scalar plus the popped element; '_'/'N' parses an ident into a
 * 0x92 node with the printable stack top. Returns the resulting node.
 * Confidence: medium */
static uint64_t sk_003a75e4(uint64_t *st)
{
    uint64_t pos = STREAM_POS(st);
    if (pos < STREAM_END(st)) {
        uint8_t c = STREAM_DATA(st)[pos];
        if (c == 'l') {
            STREAM_POS(st) = pos + 1;
            uint64_t *top = 0;
            if (STACK_CNT(st) != 0) {
                uint32_t i = STACK_CNT(st) - 1;
                uint64_t *e = STACK_ELEM(st, i);
                if (NODE_TAG(e) == 0x67) {
                    STACK_CNT(st) = i;
                    top = e;
                }
            }
            return (uint64_t)sk_node_push(st, 0xba, top);
        }
        if (c == 'L') {
            STREAM_POS(st) = pos + 1;
            uint64_t *a = 0, *b = 0;
            if (STACK_CNT(st) != 0) {
                uint32_t i = STACK_CNT(st) - 1;
                a = STACK_ELEM(st, i);
                if (NODE_TAG(a) == 0x67) {
                    STACK_CNT(st) = i;
                    if (i == 0) b = 0;
                    else {
                        uint32_t j = i - 1;
                        b = STACK_ELEM(st, j);
                        if (sk_003acda0(NODE_TAG(b)) == 0) b = 0;
                        else STACK_CNT(st) = j;
                    }
                } else {
                    a = 0;
                }
            }
            return (uint64_t)sk_node_push2(st, 0xba, a, b);
        }
        if ((char)c >= 'a') {
            if (c < 'k') goto ident;
        } else if (c - 0x41 < 10) goto ident;
        goto fallback;
    }
fallback:
    {
        uint64_t *node = sk_003ac52c(st);
        uint64_t *b = 0;
        if (STACK_CNT(st) != 0) {
            uint32_t i = STACK_CNT(st) - 1;
            b = STACK_ELEM(st, i);
            if (sk_003acda0(NODE_TAG(b)) == 0) b = 0;
            else STACK_CNT(st) = i;
        }
        return (uint64_t)sk_node_push2(st, 0x92, node, b);
    }
ident:
    STREAM_POS(st) = pos + 1;
    uint8_t ch = STREAM_DATA(st)[pos];
    uint64_t *sc = sk_alloc_scalar(st, 1);
    *(uint8_t *)sc = ch;
    uint64_t *n = sk_node_alloc(st, 1);
    NODE_SETTAG(n, 0x67); NODE_SETSUBT(n, 3);
    n[0] = (uint64_t)sc;
    n[1] = 1;
    uint64_t *top = 0;
    if (STACK_CNT(st) != 0) {
        uint32_t i = STACK_CNT(st) - 1;
        top = STACK_ELEM(st, i);
        STACK_CNT(st) = i;
    }
    uint64_t *node = sk_node_alloc(st, 1);
    NODE_SETTAG(node, 0xd9); NODE_SETSUBT(node, 0);
    sk_node_add(node, n, st);
    if (top) sk_node_add(node, top, st);
    return (uint64_t)node;
}

/* FUN_003a7818 @ 0x3a7818   (est. sk_dispatch_letter)
 * Dispatches on an ASCII letter at the stream position, mapping it to a tag
 * and building a node: most letters push the popped stack element (or the
 * stream dispatch / value) under a fixed tag; 'X' delegates to
 * sk_003ae1b4; letters without a case mapping return 0. Returns the node.
 * Confidence: medium */
static uint64_t sk_003a7818(uint64_t *st)
{
    uint64_t pos = STREAM_POS(st);
    if (STREAM_END(st) <= pos) return 0;
    STREAM_POS(st) = pos + 1;
    uint8_t c = STREAM_DATA(st)[pos];
    if (0x39 < c - 0x41) return 0;      /* not in 'A'..'z' */
    switch (c) {
    default:
        {
            uint64_t *v = sk_stream_dispatch(st);
            return (uint64_t)sk_node_push(st, 0x111, v);
        }
    case 'B': {
        uint64_t *v = 0;
        if (STACK_CNT(st) != 0) {
            uint32_t i = STACK_CNT(st) - 1;
            uint64_t *e = STACK_ELEM(st, i);
            if (NODE_TAG(e) == 0xf4) { STACK_CNT(st) = i; v = e; }
        }
        return (uint64_t)sk_node_push(st, 0x10f, v);
    }
    case 'C': {
        if (STACK_CNT(st) == 0) return 0;
        uint32_t i = STACK_CNT(st) - 1;
        uint64_t *e = STACK_ELEM(st, i);
        if (NODE_TAG(e) != 0xf4) return 0;
        STACK_CNT(st) = i;
        uint8_t sub = NODE_SUBT(e);
        uint32_t u = sub - 1;
        uint64_t *p = e;
        if (1 < u) p = (uint64_t *)NODE_DATA(e);
        if (sk_003acf38(NODE_TAG(p)) == 0) return 0;
        uint64_t *leaf;
        if (u < 2) leaf = (uint64_t *)NODE_DATA(e);
        else if (sub == 5 && (int64_t)e[1] != 0) { e = (uint64_t *)NODE_DATA(e); leaf = (uint64_t *)NODE_DATA(e); }
        else leaf = 0;
        return (uint64_t)sk_node_push(st, 0x112, leaf);
    }
    case 'D': case 'd': return (uint64_t)sk_val_get_alt(st, 0xff);
    case 'F': {
        uint64_t *v = 0;
        if (STACK_CNT(st) != 0) {
            uint32_t i = STACK_CNT(st) - 1;
            uint64_t *e = STACK_ELEM(st, i);
            if (NODE_TAG(e) == 0xf4) { STACK_CNT(st) = i; v = e; }
        }
        return (uint64_t)sk_node_push(st, 0x110, v);
    }
    case 'I': return (uint64_t)sk_val_get_alt(st, 0xfc);
    case 'J': {
        uint64_t *v = 0;
        if (STACK_CNT(st) != 0) { uint32_t i = STACK_CNT(st)-1; v = STACK_ELEM(st, i); STACK_CNT(st) = i; }
        return (uint64_t)sk_node_push(st, 0x149, v);
    }
    case 'K': {
        uint64_t *v = 0;
        if (STACK_CNT(st) != 0) { uint32_t i = STACK_CNT(st)-1; v = STACK_ELEM(st, i); STACK_CNT(st) = i; }
        return (uint64_t)sk_node_push(st, 0x147, v);
    }
    case 'L': return (uint64_t)sk_val_get_alt(st, 0x101);
    case 'M': return (uint64_t)sk_val_get_alt(st, 0x145);
    case 'N': return (uint64_t)sk_val_get_alt(st, 0x148);
    case 'P': return (uint64_t)sk_val_get_alt(st, 99);
    case 'Q': {
        uint64_t *v = 0;
        if (STACK_CNT(st) != 0) { uint32_t i = STACK_CNT(st)-1; v = STACK_ELEM(st, i); STACK_CNT(st) = i; }
        return (uint64_t)sk_node_push(st, 0x13d, v);
    }
    case 'R': return (uint64_t)sk_val_get_alt(st, 0x100);
    case 'S': {
        uint64_t v = sk_val_get(st);
        return (uint64_t)sk_node_push(st, 0xcc, (uint64_t *)v);
    }
    case 'U': return (uint64_t)sk_val_get_alt(st, 0x9e);
    case 'V': {
        uint64_t *v = 0;
        if (STACK_CNT(st) != 0) {
            uint32_t i = STACK_CNT(st) - 1;
            uint64_t *e = STACK_ELEM(st, i);
            if (NODE_TAG(e) != 0xf4 && sk_tag_simple(0) == 0) goto VZ;
            STACK_CNT(st) = i; v = e;
        }
    VZ:
        return (uint64_t)sk_node_push(st, 0xbb, v);
    }
    case 'X': return (uint64_t)sk_003ae1b4(st);
    case 'a': return (uint64_t)sk_val_get_alt(st, 0xfa);
    case 'b': return (uint64_t)sk_val_get_alt(st, 0x146);
    case 'c': {
        uint64_t *v = sk_stream_dispatch(st);
        return (uint64_t)sk_node_push(st, 199, v);
    }
    case 'f': return (uint64_t)sk_val_get_alt(st, 0x4d);
    case 'g': {
        uint64_t *v = 0;
        if (STACK_CNT(st) != 0) { uint32_t i = STACK_CNT(st)-1; v = STACK_ELEM(st, i); STACK_CNT(st) = i; }
        return (uint64_t)sk_node_push(st, 0x13f, v);
    }
    case 'h': {
        uint64_t *v = 0;
        if (STACK_CNT(st) != 0) { uint32_t i = STACK_CNT(st)-1; v = STACK_ELEM(st, i); STACK_CNT(st) = i; }
        return (uint64_t)sk_node_push(st, 0x140, v);
    }
    case 'i': return (uint64_t)sk_val_get_alt(st, 0xfd);
    case 'j': {
        uint64_t *v = 0;
        if (STACK_CNT(st) != 0) { uint32_t i = STACK_CNT(st)-1; v = STACK_ELEM(st, i); STACK_CNT(st) = i; }
        return (uint64_t)sk_node_push(st, 0x141, v);
    }
    case 'k': {
        uint64_t *v = 0;
        if (STACK_CNT(st) != 0) { uint32_t i = STACK_CNT(st)-1; v = STACK_ELEM(st, i); STACK_CNT(st) = i; }
        return (uint64_t)sk_node_push(st, 0x142, v);
    }
    case 'l': return (uint64_t)sk_val_get_alt(st, 0xfe);
    case 'm': return (uint64_t)sk_val_get_alt(st, 0x9c);
    case 'n': return (uint64_t)sk_val_get_alt(st, 0xa8);
    case 'o': return (uint64_t)sk_val_get_alt(st, 0x1a);
    case 'p': {
        uint64_t v = sk_val_get(st);
        return (uint64_t)sk_node_push(st, 0xc5, (uint64_t *)v);
    }
    case 'q': {
        uint64_t *v = 0;
        if (STACK_CNT(st) != 0) { uint32_t i = STACK_CNT(st)-1; v = STACK_ELEM(st, i); STACK_CNT(st) = i; }
        return (uint64_t)sk_node_push(st, 0x15e, v);
    }
    case 'r': return (uint64_t)sk_val_get_alt(st, 0xfb);
    case 's': return (uint64_t)sk_val_get_alt(st, 0x9f);
    case 't': return (uint64_t)sk_val_get_alt(st, 0xa0);
    case 'u': return (uint64_t)sk_val_get_alt(st, 0x9d);
    case 'z': return (uint64_t)sk_val_get_alt(st, 0x14d);
    }
}

/* FUN_003a7d9c @ 0x3a7d9c   (est. sk_parse_construct)
 * Parses a construct token (one ASCII letter) from the stream into a node.
 * Handles 'S'(di), 'Y'/'Z' (abc48/c2d0 wrapped by ae4c8), 'O'(f4 pop via
 * ace50), 'P'(ad188), 'R'(ident scalar 0x164 wrapped 0x143), 'a'(f4 over
 * 0x5 stream pop + 0x67), 'e'(f2 over stream pop + f3 ident), 'o'(f7
 * collection of 0x13b with inline children + 0x68 ident), 'p'(f1 over two
 * stream pops), 'r'(empty 0x143), 'x'/'y'/'z'(lowercase variants). Pushes the
 * built node onto a scratch buffer at +0x68 and returns it.
 * Confidence: medium */
static uint64_t sk_003a7d9c(uint64_t *st)
{
    uint64_t pos = STREAM_POS(st);
    if (STREAM_END(st) <= pos) return 0;
    STREAM_POS(st) = pos + 1;
    uint8_t b = STREAM_DATA(st)[pos];
    uint64_t r, tmp;
    uint64_t *buf = (uint64_t *)((char *)st + 0x68);
    if (b < 0x61) {
        if (0x52 < b) {
            if (b < 0x59) {
                if (b == 'S') return (uint64_t)sk_003ad278(st);
                if (b != 'X') return 0;
                r = 0;
            } else if (b == 'Y') {
                r = sk_003abc48(st);
            } else {
                if (b != 'Z') return 0;
                r = sk_003ac2d0(st, 0, 0);
            }
            r = sk_003ae4c8(st, r);
            goto store;
        }
        if (b == 'O') {
            r = (uint64_t)sk_003ace50(st);
            return (uint64_t)sk_node_push(st, 0x144, (uint64_t *)r);
        }
        if (b == 'P') return (uint64_t)sk_003ad188(st);
        if (b != 'R') return 0;
        {
            int32_t v = sk_003ac4a4(st);
            if (v < 0) return 0;
            uint64_t *s = sk_node_alloc(st, 1);
            NODE_SETTAG(s, 0x164); NODE_SETSUBT(s, 4);
            s[0] = (uint64_t)v;
            return (uint64_t)sk_node_push(st, 0x143, s);
        }
    } else {
        if (0x71 < b) {
            if (b < 0x79) {
                if (b == 'r') {
                    uint64_t *n = sk_node_alloc(st, 1);
                    NODE_SETTAG(n, 0x143); NODE_SETSUBT(n, 0);
                    goto pushf4;
                }
                if (b != 'x') return 0;
                r = 0;
            } else if (b == 'y') {
                r = sk_003abc48(st);
            } else {
                if (b != 'z') return 0;
                r = sk_003ac2d0(st, 0, 0);
            }
            r = sk_003ae414(st, r);
            goto store;
        }
        if (b < 0x6f) {
            if (b == 'a') {
                uint64_t *top = 0;
                if (STACK_CNT(st) != 0) {
                    uint32_t i = STACK_CNT(st) - 1;
                    uint64_t *e = STACK_ELEM(st, i);
                    if (NODE_TAG(e) == 0x67) { STACK_CNT(st) = i; top = e; }
                }
                uint64_t *p = sk_stream_pop(st);
                uint64_t *n = sk_node_push2(st, 5, p, top);
                return (uint64_t)sk_node_push(st, 0xf4, n);
            }
            if (b != 'e') return 0;
            {
                uint64_t *p = sk_stream_pop(st);
                int32_t v = sk_003ac4a4(st);
                if (v < 0) return 0;
                uint64_t *s = sk_node_alloc(st, 1);
                NODE_SETTAG(s, 0xf3); NODE_SETSUBT(s, 4);
                s[0] = (uint64_t)v;
                return (uint64_t)sk_node_push2(st, 0xf2, p, s);
            }
        } else {
            if (b == 'o') {
                int32_t id = sk_003ac4a4(st);
                uint64_t scratch = 0;      /* child-buffer pointer field (local_48) */
                uint64_t slen = 0;         /* child count (local_40) */
                uint64_t s2 = 0;           /* single trailing child slot (local_50) */
                if (sk_003ad724(st, (uint64_t)(uintptr_t)&scratch, &s2) == 0 ||
                    STACK_CNT(st) == 0) return 0;
                uint32_t i = STACK_CNT(st) - 1;
                uint64_t *el = STACK_ELEM(st, i);
                STACK_CNT(st) = i;
                if (el == 0) return 0;
                uint64_t *w = sk_node_alloc(st, 1);
                NODE_SETTAG(w, 0x68); NODE_SETSUBT(w, 4);
                w[0] = (uint64_t)id;
                uint64_t *n = sk_node_push2(st, 0x13b, el, w);
                uint64_t *f7 = sk_node_alloc(st, 1);
                NODE_SETTAG(f7, 0xf7); NODE_SETSUBT(f7, 0);
                if (slen != 0) {
                    long ii = (slen & 0xffffffff) * 8 - 8;
                    do {
                        sk_node_add(f7, (uint64_t *)*(uint64_t *)(scratch + (uint64_t)ii), st);
                        ii -= 8;
                    } while (ii != -8);
                }
                sk_node_add(n, f7, st);
                if (s2) sk_node_add(n, (uint64_t *)s2, st);
                uint64_t *res = (uint64_t *)sk_node_push(st, 0xf4, n);
                if (res == 0) return 0;
                tmp = (uint64_t)res;
                sk_003ad810(buf, &tmp, st);
                return (uint64_t)res;
            }
            if (b != 'p') return 0;
            {
                uint64_t *a = sk_stream_pop(st);
                uint64_t *b2 = sk_stream_pop(st);
                return (uint64_t)sk_node_push2(st, 0xf1, b2, a);
            }
        }
        return 0;
    }
    /* unreachable fallthrough for lowercase - handled above */
    if (0) goto store;
store:
    {
        /* record the built node into the scratch buffer at +0x68 and return */
        uint64_t node = r;
        sk_003ad810(buf, &node, st);
        return r;
    }
pushf4:
    return (uint64_t)sk_node_push(st, 0xf4, (uint64_t *)0);
}

/* FUN_003a81e8 @ 0x3a81e8   (est. sk_parse_type_ref)
 * Parses a type-reference token (one ASCII letter, optionally lowercase)
 * from the stream. Most letters select a fixed tag; 'I'/'i' parse an ident
 * (0x171/0x174 build); 'T'/'t'/'M'/'m'/'P'/'p' select via abc48 + ae414/ae4c8;
 * 'h'/'H' (case 'l' branch) parses a small sub-schema of DAT_* string labels
 * into a 0x2a node wrapping two optional ident children. Returns the node.
 * Confidence: low */
static uint64_t sk_003a81e8(uint64_t *st, uint64_t p2, uint64_t p3)
{
    uint64_t pos = STREAM_POS(st);
    if (STREAM_END(st) <= pos) goto default_case;
    uint8_t b = STREAM_DATA(st)[pos];
    STREAM_POS(st) = pos + 1;
    uint64_t u10 = 1, u11, l5 = 0, l6;
    uint64_t p1 = pos + 1;   /* saved new pos */
    if (0x14 < b - 0x42) {
        if (0x14 < b - 0x62) {
        default_case:
            u11 = 0;
            STREAM_POS(st) = p1 - 1;
            l5 = 0;
            goto post_56;
        }
        switch (b) {
        default: u11 = 1; l5 = 0; break;
        case 'c': goto case_c;
        case 'd': case 'e': case 'f': case 'g': case 'j': case 'k':
        case 'n': case 'o': case 'q': case 'r': case 'u':
            goto default_case;
        case 'h': u11 = 3; l5 = 0; break;
        case 'i':
            l5 = (uint64_t)sk_003ac52c(st);
            if (l5 == 0) return 0;
            u11 = 6; break;
        case 'l': u11 = 4; l5 = 0; break;
        case 'm': u10 = 4; goto case_c;
        case 'p': u10 = 0; goto case_c;
        case 's': u11 = 2; l5 = 0; break;
        case 't': u10 = 2;
        case_c: {
            uint64_t v = sk_003abc48(st);
            l5 = sk_003ae414(st, v);
            u11 = u10;
            goto post_a8;
        }
        case 'v': u11 = 5; l5 = 0; break;
        }
    post_56:
        l6 = l5;
        {
            uint64_t v = sk_003abc48(st);
            l5 = (uint64_t)sk_node_push(st, 0xf4, (uint64_t *)v);
        }
        goto post_c8;
    }
    l6 = 0;
    u11 = 7;
    l5 = 0;
    uint64_t u3 = 1;
    switch (b) {
    case 'C': goto case_C;
    case 'D': case 'E': case 'F': case 'G': case 'H': case 'J': case 'K':
    case 'N': case 'O': case 'R': case 'U':
        goto default_case;
    case 'I':
        l6 = (uint64_t)sk_003ac52c(st);
        if (l6 == 0) return 0;
        u3 = 6; break;
    case 'L': l6 = 0; u3 = 4; break;
    case 'M': u10 = 4; goto case_C;
    case 'P': u10 = 0; goto case_C;
    case 'Q': l6 = 0; u3 = 0; break;
    case 'S': l6 = 0; u3 = 2; break;
    case 'T': u10 = 2;
    case_C: {
        uint64_t v = sk_003abc48(st);
        l5 = sk_003ae4c8(st, v);
        u11 = u10;
    post_a8: {
        uint64_t loc = l5;
        if (l5 != 0) sk_003ad810((uint64_t *)((char *)st + 0x68), &loc, st);
        l6 = 0;
        goto post_c8;
    }
    }
    case 'V': goto post_56;
    }
    u11 = u3;
    if (STACK_CNT(st) == 0) { l5 = 0; }
    else {
        uint32_t i = STACK_CNT(st) - 1;
        l5 = (uint64_t)STACK_ELEM(st, i);
        if (NODE_TAG((uint64_t *)l5) != 0xf4) l5 = 0;
        else STACK_CNT(st) = i;
    }
post_c8:
    if (u11 < 4) {
        if (u11 < 2) {
            if (u11 == 0) {
                l6 = sk_val_get(st);
            } else {
                if (STACK_CNT(st) != 0) {
                    uint32_t i = STACK_CNT(st) - 1;
                    l6 = (uint64_t)STACK_ELEM(st, i);
                    if (NODE_TAG((uint64_t *)l6) == 0xf4) { STACK_CNT(st) = i; goto post_54c; }
                }
                l6 = 0;
            }
        post_54c:
            return (uint64_t)sk_node_push2(st, 0x25, (uint64_t *)l5, (uint64_t *)l6);
        }
        if (u11 != 2) {
            if (STACK_CNT(st) == 0) l6 = 0;
            else {
                uint32_t i = STACK_CNT(st) - 1;
                l6 = (uint64_t)STACK_ELEM(st, i);
                if (NODE_TAG((uint64_t *)l6) != 0xf4) l6 = 0;
                else STACK_CNT(st) = i;
            }
            return (uint64_t)sk_node_push2(st, 0x29, (uint64_t *)l5, (uint64_t *)l6);
        }
        if (STACK_CNT(st) == 0) l6 = 0;
        else {
            uint32_t i = STACK_CNT(st) - 1;
            l6 = (uint64_t)STACK_ELEM(st, i);
            if (NODE_TAG((uint64_t *)l6) != 0xf4) l6 = 0;
            else STACK_CNT(st) = i;
        }
        return (uint64_t)sk_node_push2(st, 0x28, (uint64_t *)l5, (uint64_t *)l6);
    }
    if (u11 < 6) {
        if (u11 != 4) {
            return (uint64_t)sk_node_push2(st, 0x2b, (uint64_t *)l5, (uint64_t *)l6);
        }
        /* 'l'/'L': parse a DAT_*-labelled sub-schema into a 0x2a node */
        uint64_t pp = STREAM_POS(st);
        if (pp < STREAM_END(st)) {
            l6 = 0;
            STREAM_POS(st) = pp + 1;
            uint8_t c2 = STREAM_DATA(st)[pp];
            uint32_t u8 = c2;
            char *label = DAT_005d3810;
            uint64_t l12 = 0;
            if (u8 - 0x42 < 0x14) {
                switch (u8) {
                default: l6 = 0; l12 = 0; label = DAT_005d37d2; break;
                case 'C': l6 = 0; l12 = 0; label = DAT_005d37e1; break;
                case 'D': l6 = 0; l12 = 0; label = DAT_005d37cb; break;
                case 'E':
                    l6 = (uint64_t)sk_003ac52c(st);
                    if (l6 == 0) return 0;
                    l12 = (uint64_t)sk_003ac52c(st);
                    label = DAT_005d356c; break;
                case 'F': case 'G': case 'H': case 'I': case 'J': case 'K':
                case 'L': case 'O': case 'P': case 'Q':
                    return 0;
                case 'M':
                    l6 = (uint64_t)sk_003ac52c(st);
                    if (l6 == 0) return 0;
                    l12 = (uint64_t)sk_003ac52c(st);
                    label = DAT_005d37d0; break;
                case 'N': l6 = 0; l12 = 0; label = DAT_005d37c9; break;
                case 'R': l6 = 0; l12 = 0; label = DAT_005d3568; break;
                case 'S':
                    l6 = (uint64_t)sk_003ac52c(st);
                    l12 = 0;
                    if (l6 == 0) return 0;
                    label = DAT_005d37d7; break;
                case 'T': l6 = 0; l12 = 0; label = DAT_005d37e5; break;
                case 'U': break;
                }
            } else if (u8 == 'e') {
                l6 = (uint64_t)sk_003ac52c(st);
                l12 = 0;
                if (l6 == 0) return 0;
                label = DAT_005d6b7d;
            } else {
                if (u8 != 'm') return 0;
                l6 = (uint64_t)sk_003ac52c(st);
                l12 = 0;
                if (l6 == 0) return 0;
                label = DAT_005d6c15;
            }
            uint64_t *s = sk_node_alloc(st, 1);
            NODE_SETTAG(s, 0x67); NODE_SETSUBT(s, 3);
            s[0] = (uint64_t)label;
            s[1] = 1;
            uint64_t *n = sk_node_push2(st, 0x2a, (uint64_t *)l5, s);
            if (l6 != 0) {
                if (n == 0) return 0;
                sk_node_add(n, (uint64_t *)l6, st);
            }
            if (l12 == 0) return (uint64_t)n;
            if (n != 0) {
                sk_node_add(n, (uint64_t *)l12, st);
                return (uint64_t)n;
            }
        }
        return 0;
    }
    if (u11 == 6) return (uint64_t)sk_node_push2(st, 0x171, (uint64_t *)l5, (uint64_t *)l6);
    if (STACK_CNT(st) == 0) l6 = 0;
    else {
        uint32_t i = STACK_CNT(st) - 1;
        l6 = (uint64_t)STACK_ELEM(st, i);
        if (NODE_TAG((uint64_t *)l6) != 0xf4) l6 = 0;
        else STACK_CNT(st) = i;
    }
    return (uint64_t)sk_node_push2(st, 0x174, (uint64_t *)l5, (uint64_t *)l6);
}

/* FUN_003a8868 @ 0x3a8868   (est. sk_parse_named_special)
 * Parses a special named token: 'C' builds an a3 node holding the
 * "__C_Synthesized" string (len 0xf); 'o' builds an a3 node with "__C" (len
 * 3); 'g' parses an Optional modifier (0x3f via ac600) wrapped in a 0xe/0xf7
 * f4 triple and records it in the +0x68 scratch; otherwise backs up and
 * reads a decimal length (ac430): if >0x800 returns NULL, else if followed
 * by 'c' sets a flag, reads one more byte, builds an ac6b4 node, and pushes
 * it onto the value stack (at +0x58) iVar2+1 times. Returns the node.
 * Confidence: medium */
static uint64_t *sk_003a8868(uint64_t *st)
{
    uint64_t pos = STREAM_POS(st);
    uint64_t p = pos;
    if (STREAM_END(st) <= pos) goto read_len;
    p = pos + 1;
    STREAM_POS(st) = p;
    char c = STREAM_DATA(st)[pos];
    if (c == 'C') {
        uint64_t *sc = sk_alloc_scalar(st, 0xf);
        memcpy_placeholder(sc, s___C_Synthesized_005d6ef6, 0xf);
        uint64_t *n = sk_node_alloc(st, 1);
        NODE_SETTAG(n, 0xa3); NODE_SETSUBT(n, 3);
        n[0] = (uint64_t)sc;
        n[1] = 0xf;
        return n;
    }
    if (c != 'g') {
        if (c != 'o') goto read_len;
        uint64_t *sc = sk_alloc_scalar(st, 3);
        *(uint16_t *)sc = 0x5f5f;          /* "__" */
        *(uint8_t *)((char *)sc + 2) = 'C';
        uint64_t *n = sk_node_alloc(st, 1);
        NODE_SETTAG(n, 0xa3); NODE_SETSUBT(n, 3);
        n[0] = (uint64_t)sc;
        n[1] = 3;
        return n;
    }
    /* 'g': Optional modifier */
    uint64_t mv = sk_003ac600(st, 0x3f, (uint64_t)s_Optional_005d4e8b);
    uint64_t *m = (uint64_t *)mv;
    uint64_t *top = 0;
    if (STACK_CNT(st) != 0) {
        uint32_t i = STACK_CNT(st) - 1;
        uint64_t *e = STACK_ELEM(st, i);
        if (NODE_TAG(e) == 0xf4) { STACK_CNT(st) = i; top = e; }
    }
    uint64_t *n1 = (uint64_t *)sk_node_push(st, 0xf7, top);
    uint64_t *n2 = (uint64_t *)sk_node_push2(st, 0xe, m, n1);
    uint64_t *n3 = (uint64_t *)sk_node_push(st, 0xf4, n2);
    if (n3 == 0) return 0;
    uint64_t loc = (uint64_t)n3;
    sk_003ad810((uint64_t *)((char *)st + 0x68), &loc, st);
    return n3;
read_len:
    STREAM_POS(st) = p - 1;
    int32_t n = sk_003ac430(st);
    if (0x800 < n) return 0;
    uint64_t q = STREAM_POS(st);
    uint64_t flag = 0;
    if (q < STREAM_END(st) && STREAM_DATA(st)[q] == 'c') {
        q = q + 1;
        STREAM_POS(st) = q;
        flag = 1;
    }
    char ch;
    if (q < STREAM_END(st)) {
        STREAM_POS(st) = q + 1;
        ch = STREAM_DATA(st)[q];
    } else {
        ch = '\0';
    }
    uint64_t nodev = sk_003ac6b4(st, (int)ch, (uint32_t)flag);
    uint64_t *node = (uint64_t *)nodev;
    if (node == 0) return 0;
    if (n < 2) return node;
    uint32_t k = n + 1;
    do {
        uint64_t loc = (uint64_t)node;
        sk_003ad810((uint64_t *)((char *)st + 0x58), &loc, st);
        k = k - 1;
    } while (2 < k);
    return node;
}

/* FUN_003a9944 @ 0x3a9944   (est. sk_parse_letter_node)
 * Parses a one-letter construct into a node. Many letters map to a fixed tag
 * and wrap either the popped single 0xf4 stack element or a 0x2c+0xf4 pair.
 * 'O' with an inner letter selects among many tags (16c..170, 124..12a, 166/167)
 * using the shared one-or-pair pop; 'Z'/'z' builds a 0x14c child collection
 * (0x14a/0x14b wrap); 'S','T','V','b' delegate to helpers. Returns the node.
 * Confidence: medium */
/* Shared pop: pops either a single 0xf4 element (mode 1, *shallow set) or a
 * 0x2c element optionally followed by a 0xf4 element (mode 2, *deep = inner
 * f4, *shallow = the 0x2c element); mode 0 = nothing popped (0x2c alone still
 * consumed with deep=0). Mirrors the decompile's two-branch stack unwind. */
static int sk_pop_one_or_pair(uint64_t *st, uint64_t *deep, uint64_t *shallow)
{
    *deep = 0; *shallow = 0;
    int32_t cnt = STACK_CNT(st);
    if (cnt == 0) return 0;
    uint32_t i = cnt - 1;
    uint64_t top = (uint64_t)STACK_ELEM(st, i);
    uint16_t t = NODE_TAG((uint64_t *)top);
    if (t == 0xf4) { STACK_CNT(st) = i; *shallow = top; return 1; }
    if (t != 0x2c) return 0;
    STACK_CNT(st) = i;
    if (i == 0) return 2;
    uint64_t d = (uint64_t)STACK_ELEM(st, i - 1);
    if (NODE_TAG((uint64_t *)d) != 0xf4) return 2;
    STACK_CNT(st) = i - 1;
    *deep = d; *shallow = top;
    return 2;
}

static uint64_t sk_003a9944(uint64_t *st)
{
    uint64_t end = STREAM_END(st);
    uint64_t pos = STREAM_POS(st);
    if (end <= pos) return 0;
    uint64_t npos = pos + 1;
    STREAM_POS(st) = npos;
    uint8_t b = STREAM_DATA(st)[pos];
    uint32_t u = b;
    uint64_t l14, pu12, tag;
    if (0x6b < b) {
        if (b < 0x74) {
            if (u != 'l') {
                if (u == 'p') { l14 = (uint64_t)sk_stream_dispatch(st); return (uint64_t)sk_node_push(st, 0xd2, (uint64_t *)l14); }
                if (u != 'r') return 0;
                l14 = (uint64_t)sk_stream_dispatch(st); return (uint64_t)sk_node_push(st, 0x5c, (uint64_t *)l14);
            }
            l14 = (uint64_t)sk_stream_dispatch(st);
            pu12 = 0;
            if (STACK_CNT(st) != 0) {
                uint32_t i = STACK_CNT(st) - 1;
                uint64_t *e = STACK_ELEM(st, i);
                if (NODE_TAG(e) == 0xf4) { STACK_CNT(st) = i; pu12 = (uint64_t)e; }
            }
            return (uint64_t)sk_node_push2(st, 0x90, (uint64_t *)pu12, (uint64_t *)l14);
        }
        if (b != 't') {
            if (b != 'v') {
                if (u != 'z') return 0;
                goto case_z;
            }
            if (end <= npos) return 0;
            STREAM_POS(st) = pos + 2;
            uint64_t dir;
            if (STREAM_DATA(st)[npos] == 'd') dir = 0;
            else if (STREAM_DATA(st)[npos] != 'i') return 0;
            else dir = 1;
            uint64_t *s = sk_node_alloc(st, 1);
            NODE_SETTAG(s, 0x36); NODE_SETSUBT(s, 4);
            s[0] = dir;
            l14 = 0;
            if (STACK_CNT(st) != 0) {
                uint32_t i = STACK_CNT(st) - 1;
                uint64_t *e = STACK_ELEM(st, i);
                if (NODE_TAG(e) != 0xf4 && sk_tag_simple(0) == 0) goto V0;
                STACK_CNT(st) = i; l14 = (uint64_t)e;
            }
        V0:
            return (uint64_t)sk_node_push2(st, 0x4b, (uint64_t *)l14, s);
        }
        l14 = 0;
        if (STACK_CNT(st) != 0) {
            uint32_t i = STACK_CNT(st) - 1;
            uint64_t *e = STACK_ELEM(st, i);
            if (sk_003acda0(NODE_TAG(e)) == 0) l14 = 0;
            else { STACK_CNT(st) = i; l14 = (uint64_t)e; }
        }
        {
            uint64_t v = (uint64_t)sk_stream_dispatch(st);
            return (uint64_t)sk_node_push2(st, 6, (uint64_t *)v, (uint64_t *)l14);
        }
    }
    if (0x1f < u - 0x43) return 0;
    switch (u) {
    default:
        l14 = 0;
        if (STACK_CNT(st) != 0) {
            uint32_t i = STACK_CNT(st) - 1;
            uint64_t *e = STACK_ELEM(st, i);
            if (NODE_TAG(e) != 0xf4 && sk_tag_simple(0) == 0) goto D0;
            STACK_CNT(st) = i; l14 = (uint64_t)e;
        }
    D0:
        return (uint64_t)sk_node_push(st, 0x40, (uint64_t *)l14);
    case 'D': case 'E': case 'F': case 'H': case 'K': case 'M': case 'N':
    case 'Q': case 'R': case 'U': case 'W': case 'X': case 'Y':
    case '[': case '\\': case ']': case '^': case '_': case '`':
        return 0;
    case 'G': l14 = (uint64_t)sk_stream_dispatch(st); return (uint64_t)sk_node_push(st, 0x5a, (uint64_t *)l14);
    case 'I': l14 = (uint64_t)sk_stream_dispatch(st); return (uint64_t)sk_node_push(st, 0x5b, (uint64_t *)l14);
    case 'J': return (uint64_t)sk_003af7a4(st);
    case 'L':
        l14 = (uint64_t)sk_stream_dispatch(st);
        pu12 = 0;
        if (STACK_CNT(st) != 0) {
            uint32_t i = STACK_CNT(st) - 1;
            uint64_t *e = STACK_ELEM(st, i);
            if (NODE_TAG(e) == 0xf4) { STACK_CNT(st) = i; pu12 = (uint64_t)e; }
        }
        return (uint64_t)sk_node_push2(st, 0x91, (uint64_t *)pu12, (uint64_t *)l14);
    case 'O': {
        if (end <= npos) return 0;
        STREAM_POS(st) = pos + 2;
        b = STREAM_DATA(st)[npos];
        u = b;
        if (0x45 < b) {
            if (0x17 < u - 0x62) {
                if (b != 'F') {
                    if (b != 'H') return 0;
                    tag = 0x170;
                } else {
                    tag = 0x16f;
                }
                l14 = (uint64_t)sk_pop_one_or_pair(st, &pu12, &l14);
                if (l14 == 2) return (uint64_t)sk_node_push2(st, (int)tag, (uint64_t *)pu12, (uint64_t *)0);
                /* mode 1: single */
                return (uint64_t)sk_node_push2(st, (int)tag, (uint64_t *)pu12, (uint64_t *)l14);
            }
            switch (u) {
            case 'c': tag = 0x129; goto opair;
            case 'd': tag = 0x12a; goto opair;
            case 'e': tag = 0x125; goto opair;
            case 'f': tag = 299; goto opair;
            case 'g': tag = 0x168; goto opair;
            case 'h': tag = 300; goto opair;
            case 'r': tag = 0x126; goto opair;
            case 's': tag = 0x127; goto opair;
            case 'y': tag = 0x124; goto opair;
            case 'i': case 'j': {
                uint64_t *id = sk_003ac52c(st);
                tag = (u == 'i') ? 0x166 : 0x167;
                int m = sk_pop_one_or_pair(st, &pu12, &l14);
                if (m == 0) return (uint64_t)sk_node_push2(st, (int)tag, (uint64_t *)pu12, (uint64_t *)id);
                if (m == 2) return (uint64_t)sk_ctx_op(st, tag, (uint64_t *)pu12, (uint64_t *)id, 0);
                return (uint64_t)sk_node_push2(st, (int)tag, (uint64_t *)pu12, (uint64_t *)id);
            }
            case 'k': case 'l': case 'm': case 'n': case 'o': case 'p':
            case 'q': case 't': case 'u': case 'v': case 'w': case 'x':
                return 0;
            default: tag = 0x128; goto opair;
            }
        }
        if (b != 'B') {
            if (b != 'C') {
                if (u != 'D') return 0;
                tag = 0x16e;
            } else {
                tag = 0x16d;
            }
        } else {
            tag = 0x16c;
        }
        l14 = (uint64_t)sk_pop_one_or_pair(st, &pu12, &l14);
        if (l14 == 2) return (uint64_t)sk_node_push2(st, (int)tag, (uint64_t *)pu12, (uint64_t *)0);
        return (uint64_t)sk_node_push2(st, (int)tag, (uint64_t *)pu12, (uint64_t *)l14);
    opair: {
        int m = sk_pop_one_or_pair(st, &pu12, &l14);
        if (m == 0) return (uint64_t)sk_node_push(st, (int)tag, (uint64_t *)0);
        if (m == 2) return (uint64_t)sk_node_push2(st, (int)tag, (uint64_t *)pu12, (uint64_t *)0);
        return (uint64_t)sk_node_push2(st, (int)tag, (uint64_t *)pu12, (uint64_t *)l14);
    }
    }
    case 'P': l14 = (uint64_t)sk_stream_dispatch(st); return (uint64_t)sk_node_push(st, 0xd0, (uint64_t *)l14);
    case 'S': l14 = sk_val_get(st); return (uint64_t)sk_node_push(st, 0xce, (uint64_t *)l14);
    case 'T': {
        l14 = 0;
        if (STACK_CNT(st) != 0) {
            uint32_t i = STACK_CNT(st) - 1;
            uint64_t *e = STACK_ELEM(st, i);
            if (NODE_TAG(e) == 0xf4) { STACK_CNT(st) = i; l14 = (uint64_t)e; }
        }
        pu12 = (uint64_t)sk_003ae36c(st);
        uint64_t l16 = (uint64_t)sk_stream_dispatch(st);
        return (uint64_t)sk_ctx_op(st, 9, (uint64_t *)l16, (uint64_t *)pu12, (uint64_t *)l14);
    }
    case 'V':
        l14 = 0;
        if (STACK_CNT(st) != 0) {
            uint32_t i = STACK_CNT(st) - 1;
            uint64_t *e = STACK_ELEM(st, i);
            if (NODE_TAG(e) == 0xf4) { STACK_CNT(st) = i; l14 = (uint64_t)e; }
        }
        return (uint64_t)sk_node_push(st, 0x10a, (uint64_t *)l14);
    case 'Z':
    case_z: {
        uint64_t *n = sk_node_alloc(st, 1);
        NODE_SETTAG(n, 0x14c); NODE_SETSUBT(n, 0);
        uint64_t *l68 = 0, *l60 = 0, *l58 = 0;
        int32_t cnt = STACK_CNT(st);
        if (cnt != 0) {
            do {
                uint32_t i5 = cnt - 1;
                if (NODE_TAG(STACK_ELEM(st, i5)) != 0x121) break;
                STACK_CNT(st) = i5;
                if (i5 == 0) goto zb34;
                uint64_t *l16 = STACK_ELEM(st, cnt - 2);
                if (sk_003acda0(NODE_TAG(l16)) == 0) goto zb34;
                STACK_CNT(st) = cnt - 2;
                sk_003aefe4(&l68, &l16);
                cnt = STACK_CNT(st);
            } while (cnt != 0);
            uint64_t *pu7 = l58, *pu6 = l68, *pu12z = l60;
            if (l60 != l68) {
                uint64_t *pu17;
                do {
                    pu17 = pu12z - 1;
                    if (pu12z == pu6 || pu17 == pu7) sk_canary_panic();
                    sk_node_add(n, (uint64_t *)*pu17, st);
                    pu12z = pu17;
                } while (pu17 != l68);
            }
        }
        {
            uint64_t *l16 = sk_003ace50(st);
            uint64_t r;
            if (l16 == 0) { zb34: r = 0; }
            else {
                uint16_t t = (u == 'Z') ? 0x14a : 0x14b;
                r = (uint64_t)sk_node_push2(st, t, l16, n);
            }
            if (l68 == 0) return r;
            sk_lock(l68, (long)l58 - (long)l68);
            return r;
        }
    }
    case 'a': l14 = (uint64_t)sk_stream_dispatch(st); return (uint64_t)sk_node_push(st, 0xd1, (uint64_t *)l14);
    case 'b':
        l14 = 0;
        if (STACK_CNT(st) != 0) {
            uint32_t i = STACK_CNT(st) - 1;
            uint64_t *e = STACK_ELEM(st, i);
            if (NODE_TAG(e) == 0xf4) { STACK_CNT(st) = i; l14 = (uint64_t)e; }
        }
        pu12 = (uint64_t)sk_stream_dispatch(st);
        return (uint64_t)sk_node_push2(st, 10, (uint64_t *)pu12, (uint64_t *)l14);
    }
}
