/* Recreated from cl4_kernel.raw (cL4 Secure Kernel, arm64e, image base 0) —
 * the cL4 microkernel (GL1). Ground truth: Ghidra FUN_ names + addresses in
 * the cl4_kernel.raw program. All names are estimates unless string/header
 * matched.
 * Slice R03: 0x3a6c28-0x3ba390.
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
extern void sk_ctx_op(uint64_t *a, uint64_t *b, uint64_t *c, uint64_t *d, uint64_t *e); /* FUN_003a4c14 */
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

/* ------------------------------------------------------------------ *
 * Forward declarations for this slice (exact signatures; st = stream ctx).
 * ------------------------------------------------------------------ */
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
static void sk_003ac600(uint64_t * st, uint64_t p2, uint64_t p3); /* FUN_003ac600 */
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
static void sk_003b0e1c(uint64_t * st, uint64_t p2); /* FUN_003b0e1c */
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

/* ======================= BODY SECTIONS ======================= */

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

/* FUN_003acefc @ 0x3acefc   (est. sk_pop_value_tls)
 * Pops the thread-local stream's value via sk_stream_pop(); returns it only
 * if it is a printable leaf (sk_tag_is_leaf), else 0.
 * Confidence: medium */
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
static void sk_003ac600(uint64_t *st, uint64_t p2, uint64_t p3)
{
    uint32_t *magic = (uint32_t *)sk_alloc_scalar(st, 5);
    magic[0] = 0x66697753;
    *(uint8_t *)(magic + 1) = 0x74;
    uint64_t *s = sk_node_alloc(st, 1);
    NODE_SETTAG(s, 0xa3); NODE_SETSUBT(s, 3);
    s[0] = (uint64_t)magic; s[1] = 5;
    uint64_t *msg = sk_node_make(st, 0x67, (void *)p3);
    uint64_t *r = sk_node_push2(st, (int)p2, s, msg);
    sk_node_push(st, 0xf4, r);
}

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

/* FUN_003add54 @ 0x3add54   (est. sk_parse_group)
 * Reads a letter token selecting a Swift calling-convention attribute string
 * (inout/owned/unowned/guaranteed/... from a table at 0x5d5ee0), builds a
 * 0x6c string node and pushes it under the given tag. 'X' maps to a fixed
 * constant. Returns the pushed node or 0 when the char does not match.
 * Confidence: medium */
static uint64_t sk_003add54(uint64_t *st, uint64_t p2)
{
    uint64_t pos = STREAM_POS(st);
    if (pos < STREAM_END(st)) {
        uint64_t np = pos + 1;
        STREAM_POS(st) = np;
        uint32_t c = STREAM_DATA(st)[pos];
        uint64_t pc = 0;
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
        uint64_t *e = sk_003ae658(st);
        if (!e) break;
        sk_node_add(node, e, st);
        if (!term) { sk_node_finalize(node, 0); return (uint64_t)node; }
    }
    return 0;
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



