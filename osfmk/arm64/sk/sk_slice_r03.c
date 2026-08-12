
extern char DAT_005d37d2[]; extern char DAT_005d37e1[]; extern char DAT_005d37cb[];
extern char DAT_005d356c[]; extern char DAT_005d37d0[]; extern char DAT_005d37c9[];
extern char DAT_005d3568[]; extern char DAT_005d37d7[]; extern char DAT_005d37e5[];
extern char DAT_005d3810[]; extern char DAT_005d6b7d[]; extern char DAT_005d6c15[];

extern void sk_write_data3(void *st, void *tag, void *fn, void *out); /* FUN_003b0be0 */
extern void sk_write_data4(uint64_t *out);                            /* FUN_003b0d64 */
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
static void sk_003abc48(uint64_t * st); /* FUN_003abc48 */
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
static uint64_t sk_003ad724(uint64_t * st, uint64_t p2, uint64_t *param_3); /* FUN_003ad724 */
static void sk_003ad810(uint64_t *buf, uint64_t *p, uint64_t *st); /* FUN_003ad810 */
static uint64_t * sk_003ad874(uint64_t * st, uint64_t *param_2, uint64_t *param_3, uint64_t p4); /* FUN_003ad874 */
static uint64_t sk_003adcd8(uint64_t * st); /* FUN_003adcd8 */
static uint64_t sk_003add54(uint64_t * st, uint64_t p2); /* FUN_003add54 */
static uint64_t sk_003adf20(uint64_t * st, uint64_t p2); /* FUN_003adf20 */
static uint64_t * sk_003adff0(uint64_t * st); /* FUN_003adff0 */
static uint64_t * sk_003ae05c(uint64_t * st); /* FUN_003ae05c */
static uint64_t * sk_003ae0c8(uint64_t * st); /* FUN_003ae0c8 */
static uint64_t * sk_003ae134(uint64_t * st); /* FUN_003ae134 */
static uint64_t sk_003ae1b4(uint64_t * st); /* FUN_003ae1b4 */
static uint64_t sk_003ae36c(uint64_t * st); /* FUN_003ae36c */
static void sk_003ae414(uint64_t * st, uint64_t p2); /* FUN_003ae414 */
static uint64_t sk_003ae4c8(uint64_t * st, uint64_t p2); /* FUN_003ae4c8 */
static uint64_t sk_003ae658(uint64_t * st); /* FUN_003ae658 */
static uint64_t sk_003ae734(uint64_t * st, uint64_t p2, uint64_t *param_3); /* FUN_003ae734 */
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
static uint64_t *sk_003b0b7c(uint64_t *lock); /* FUN_003b0b7c */
static void sk_003b0be0(uint64_t * st, uint16_t *param_2, void *param_3, uint64_t p4); /* FUN_003b0be0 */
static uint8_t sk_003b0d64(uint64_t *buf); /* FUN_003b0d64 */
static void sk_003b0e1c(uint64_t * st, uint64_t p2); /* FUN_003b0e1c */
static uint64_t sk_003b0ec4(uint64_t a, uint8_t *b); /* FUN_003b0ec4 */
static uint64_t sk_003b0f48(uint64_t * st, uint64_t p2); /* FUN_003b0f48 */
static uint64_t sk_003b0fb8(uint64_t * st, uint64_t p2); /* FUN_003b0fb8 */
static uint64_t *sk_003b1034(uint64_t *obj); /* FUN_003b1034 */
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
static void sk_003b20f4(uint64_t * st, uint64_t *param_2, uint64_t *param_3, int32_t p4, uint64_t p5); /* FUN_003b20f4 */
static void sk_003b2180(uint64_t *out, uint64_t *node, uint64_t depth, uint32_t flag); /* FUN_003b2180 */
static void sk_003b8d18(uint64_t * st, uint64_t *param_2, uint64_t p3, uint64_t p4); /* FUN_003b8d18 */
static void sk_003b8d94(uint64_t * st, uint64_t *param_2, uint64_t p3); /* FUN_003b8d94 */
static void sk_003b8e48(uint64_t * st, uint64_t p2); /* FUN_003b8e48 */
static uint8_t sk_003b8ef8(uint64_t * st, uint64_t *param_2); /* FUN_003b8ef8 */
static uint64_t sk_003b903c(uint64_t a, uint64_t *b); /* FUN_003b903c */
static void sk_003b9794(uint64_t * st, uint64_t p2, int32_t p3); /* FUN_003b9794 */
static uint64_t sk_003b982c(uint64_t * st, uint64_t *param_2); /* FUN_003b982c */
static bool sk_003b9c14(uint64_t *a, uint64_t b, uint64_t c); /* FUN_003b9c14 */
static bool sk_003b9c6c(uint64_t *a); /* FUN_003b9c6c */
static void sk_003b9cb4(uint64_t * st, uint64_t *param_2, uint64_t p3); /* FUN_003b9cb4 */
static uint64_t sk_003ba044(uint64_t * st, uint64_t *param_2, uint32_t p3); /* FUN_003ba044 */
static void sk_003ba114(uint64_t * st, uint64_t p2, uint64_t *param_3, int32_t p4, int32_t p5); /* FUN_003ba114 */
static void sk_003ba390(uint64_t *a, uint64_t b, uint64_t *c, uint64_t d); /* FUN_003ba390 */

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
 * Parses one tagged value into *out (with the optional trailing value in the
 * caller's scratch slot). Creates a fresh 0xf7 node, fills it from the
 * serializer (FUN_003ad810 path), then pops 0xf4 elements off the stack as
 * children. Expects a trailing 0x120 (true) or 0x121 (false) terminator;
 * returns 1 on success (0x120) / 0 otherwise, looping on 0x121.
 * Confidence: medium */
static uint64_t sk_003ad724(uint64_t *st, uint64_t p2, uint64_t *p3)
{
    uint64_t *scratch = (uint64_t *)p2;   /* out buffer base (result slot) */
    uint64_t term;
    uint64_t *node;
    *p3 = 0;
    do {
        node = sk_node_alloc(st, 1);
        NODE_SETTAG(node, 0xf7); NODE_SETSUBT(node, 0);
        sk_003ad810(scratch, (uint64_t *)&node, st);   /* record into result buffer */
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
            if (t == 0x121) { STACK_CNT(st) = STACK_CNT(st) - 1; continue; } /* loop */
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
    if (i == 0 || NODE_TAG(STACK_BASE(st)[i-1]) != 0x120) {
        int16_t term = 0;
        for (;;) {
            uint32_t cnt = STACK_CNT(st);
            if (cnt == 0) return 0;
            uint32_t j = cnt - 1;
            term = NODE_TAG(STACK_BASE(st)[j]);
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
    if (i == 0 || NODE_TAG(STACK_BASE(st)[i-1]) != 0x120) {
        int16_t term = 0;
        for (;;) {
            uint32_t cnt = STACK_CNT(st);
            if (cnt == 0) return 0;
            uint32_t j = cnt - 1;
            term = NODE_TAG(STACK_BASE(st)[j]);
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
    if (i == 0 || NODE_TAG(STACK_BASE(st)[i-1]) != 0x120) {
        int16_t term = 0;
        for (;;) {
            uint32_t cnt = STACK_CNT(st);
            if (cnt == 0) return 0;
            uint32_t j = cnt - 1;
            term = NODE_TAG(STACK_BASE(st)[j]);
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
    if (i == 0 || NODE_TAG(STACK_BASE(st)[i-1]) != 0x120) {
        int16_t term = 0;
        for (;;) {
            uint32_t cnt = STACK_CNT(st);
            if (cnt == 0) return 0;
            uint32_t j = cnt - 1;
            term = NODE_TAG(STACK_BASE(st)[j]);
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

/* FUN_003acefc @ 0x3acefc   (est. sk_pop_value)
 * Pops a value via sk_003ace50; returns it only if it is a printable leaf,
 * else 0. (No args.)
 * Confidence: medium */
/* FUN_003acefc @ 0x3acefc   (est. sk_pop_value_tls)
 * Pops the thread-local stream's value via sk_stream_pop(); returns it only
 * if it is a printable leaf (sk_tag_is_leaf), else 0.
 * Confidence: medium */
static uint64_t sk_003acefc(void)
{
    uint64_t *v = sk_stream_pop(NULL);
    if (v == 0) return 0;
    uint64_t leaf = sk_003acf38(NODE_TAG(v));
    if ((leaf & 1) == 0) v = 0;
    return (uint64_t)v;
}

/* FUN_003acfb4 @ 0x3acfb4   (est. sk_write_bytes)
 * Serializes a value block (param_2) with a tag into the output buffer via
 * FUN_003b0be0/FUN_003b0d64, returning the number of bytes written; locks on
 * a negative length. Returns 0 if either input is null.
 * Confidence: medium */
static uint64_t sk_003acfb4(uint64_t *st, uint64_t p2, uint64_t p3, uint8_t p4)
{
    if (p2 != 0 && p3 != 0) {
        uint64_t buf = 0, len = 0;
        uint8_t tag = p4;
        uint64_t result = p2;
        sk_write_data3(st, (void *)p3, sk_write_data4, &buf);
        if ((int64_t)len < 0) sk_lock((void *)buf, len & 0x7fffffffffffffffULL);
        return result;
    }
    return 0;
}

/* FUN_003ac580 @ 0x3ac580   (est. sk_build_children)
 * Reads a result pointer from the stream's result buffer (+0x68) at index
 * param_3 (bounds-checked vs +0x70 count, param_2 < 0x801), then pushes it
 * onto the value stack (param_2-1) times. Returns the result pointer.
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
                sk_003ad810(rbuf + 2, slot, st);   /* push onto stack buf */
                k = k - 1;
            } while (2 < k);
        }
    }
    return v;
}

/* FUN_003ac600 @ 0x3ac600   (est. sk_err_ab)
 * Builds an error node: allocates a 5-byte "Swift" magic buffer, wraps it in
 * an 0xa3 string node, calls sk_node_make(st,0x67,param_3) for the message
 * and sk_node_push2(st,param_2,...), then pushes the result as 0xf4.
 * Confidence: medium */
static void sk_003ac600(uint64_t *st, uint64_t p2, uint64_t p3)
{
    uint32_t *magic = (uint32_t *)sk_alloc_scalar(st, 5);
    magic[0] = 0x66697753;                 /* 'Swi' + 'f' */
    *(uint8_t *)(magic + 1) = 0x74;        /* 't' */
    uint64_t *s = sk_node_alloc(st, 1);
    NODE_SETTAG(s, 0xa3); NODE_SETSUBT(s, 3);
    s[0] = (uint64_t)magic; s[1] = 5;
    uint64_t *msg = sk_node_make(st, 0x67, (void *)p3);
    uint64_t *r = sk_node_push2(st, (int)p2, s, msg);
    sk_node_push(st, 0xf4, r);
}

/* FUN_003ac2d0 @ 0x3ac2d0   (est. sk_make_range)
 * Builds a 0x27 node with two 0x68 scalar children (param_2, param_3);
 * returns NULL if either is negative (sign bit set).
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

/* FUN_003ad61c @ 0x3ad61c   (est. sk_err_val)
 * Reports error 0x23 pairing the popped 0xf4 element with sk_val_get(st).
 * Confidence: medium */
static void sk_003ad61c(uint64_t *st)
{
    uint64_t v = sk_val_get(st);
    uint64_t *e = 0;
    if (STACK_CNT(st) != 0) {
        uint32_t i = STACK_CNT(st) - 1;
        e = STACK_ELEM(st, i);
        if (NODE_TAG(e) == 0xf4) { STACK_CNT(st) = i; goto emit; }
    }
    e = 0;
emit:
    sk_node_push2(st, 0x23, e, (uint64_t *)v);
}

/* FUN_003a81e8 @ 0x3a81e8   (est. sk_parse_token_b)
 * Reads a single letter (B..V, c..v) and dispatches on it to build a value
 * node with a per-letter kind code (uVar11) and a popped/parsed element.
 * Kinds: 0=scalar from FUN_003a663c; 1=pop 0xf4; 2/3=pop 0xf4; 4=attributed
 * string (reads a 2-letter kind + ident into a 0x2a node); 5=pop two;
 * 6=identifier; 7=... Each path builds a node via sk_node_push2 with the
 * selected tag (0x25/0x28/0x29/0x2b/0x171/0x174/0x2a).
 * Confidence: medium */
static uint64_t sk_003a81e8(uint64_t *st, uint64_t p2, uint64_t p3)
{
    uint64_t pos = STREAM_POS(st);
    uint32_t kind = 0;
    uint64_t *a = 0;      /* first popped/parsed element */
    uint64_t *b = 0;      /* second element */
    uint64_t *built = 0;  /* pre-built node */
    if (STREAM_END(st) <= pos) goto default_kind;
    uint64_t np = pos + 1;
    STREAM_POS(st) = np;
    uint8_t c = STREAM_DATA(st)[pos];
    if (0x14 < c - 0x42) {
        if (0x14 < c - 0x62) goto default_kind;
        switch (c) {
        case 'm': kind = 4; goto build_zc;      /* via 4f? handled below */
        case 'p': kind = 0; goto build_zc;
        case 't': kind = 2; goto build_zc;
        case 's': kind = 2; a = 0; break;
        case 'h': kind = 3; a = 0; break;
        case 'l': kind = 4; a = 0; break;
        case 'i': a = sk_003ac52c(st); if (!a) return 0; kind = 6; break;
        default: goto default_kind;   /* c,d,e,f,g,j,k,n,o,q,r,u -> default */
        }
        goto dispatch;
    }
    /* uppercase B..V */
    kind = 7; a = 0; b = 0;
    switch (c) {
    case 'C': case 'D': case 'E': case 'F': case 'G': case 'H': case 'J':
    case 'K': case 'N': case 'O': case 'R': case 'U':
        goto default_kind;
    case 'I': a = sk_003ac52c(st); if (!a) return 0; kind = 6; break;
    case 'L': kind = 4; a = 0; break;
    case 'M': kind = 4; goto build_zc;
    case 'P': kind = 0; goto build_zc;
    case 'Q': kind = 0; a = 0; break;
    case 'S': kind = 2; a = 0; break;
    case 'T': kind = 2; goto build_zc;
    case 'V': default: goto dispatch_special;
    }
    goto dispatch;
build_zc:
    /* m/M/p/P/t/T: build via sk_parse_z_s + sk_emit_tag */
    {
        uint64_t *z = (uint64_t *)sk_003abc48(st);
        uint64_t *v = (uint64_t *)sk_003ae414(st, (uint64_t)z);
        built = v;
        if (v) {
            uint64_t *slot = &v;
            sk_003ad810(st + 13, slot, st);   /* append to result buf +0x68 */
        }
        a = 0;
        goto dispatch;
    }
default_kind:
    STREAM_POS(st) = (STREAM_END(st) <= pos) ? pos : np - 1;
    a = 0;
    goto dispatch;
dispatch_special:
    /* V: dispatch, built = pop(z) */
    {
        uint64_t *z = (uint64_t *)sk_003abc48(st);
        a = 0;
        goto dispatch;
    }
dispatch:
    {
        uint32_t k = kind;
        uint64_t *v = 0;
        if (k < 4) {
            if (k < 2) {
                if (k == 0) {
                    v = (uint64_t *)sk_val_get(st);
                } else {
                    if (STACK_CNT(st) != 0) {
                        uint32_t i = STACK_CNT(st) - 1;
                        v = STACK_BASE(st)[i];
                        if (NODE_TAG(v) == 0xf4) { STACK_CNT(st) = i; goto emit25; }
                    }
                    v = 0;
                }
            emit25:
                return (uint64_t)sk_node_push2(st, 0x25, (uint64_t *)built, v);
            }
            if (k != 2) {
                if (STACK_CNT(st) == 0) v = 0;
                else { uint32_t i = STACK_CNT(st) - 1; v = STACK_BASE(st)[i];
                       if (NODE_TAG(v) != 0xf4) v = 0; else STACK_CNT(st) = i; }
                return (uint64_t)sk_node_push2(st, 0x29, (uint64_t *)built, v);
            }
            if (STACK_CNT(st) == 0) v = 0;
            else { uint32_t i = STACK_CNT(st) - 1; v = STACK_BASE(st)[i];
                   if (NODE_TAG(v) != 0xf4) v = 0; else STACK_CNT(st) = i; }
            return (uint64_t)sk_node_push2(st, 0x28, (uint64_t *)built, v);
        }
        if (k < 6) {
            if (k != 4) return (uint64_t)sk_node_push2(st, 0x2b, (uint64_t *)built, a);
            /* kind 4: attributed string with a 2-letter kind + idents */
            pos = STREAM_POS(st);
            if (pos < STREAM_END(st)) {
                STREAM_POS(st) = pos + 1;
                uint8_t c2 = STREAM_DATA(st)[pos];
                uint64_t *id1 = 0, *id2 = 0;
                const char *name;
                if (c2 - 0x42 < 0x14) {
                    switch (c2) {
                    case 'B': id1 = 0; id2 = 0; name = DAT_005d37d2; break;
                    case 'C': id1 = 0; id2 = 0; name = DAT_005d37e1; break;
                    case 'D': id1 = 0; id2 = 0; name = DAT_005d37cb; break;
                    case 'E': id1 = sk_003ac52c(st); if (!id1) return 0; id2 = sk_003ac52c(st); name = DAT_005d356c; break;
                    case 'F': case 'G': case 'H': case 'I': case 'J': case 'K':
                    case 'L': case 'O': case 'P': case 'Q': return 0;
                    case 'M': id1 = sk_003ac52c(st); if (!id1) return 0; id2 = sk_003ac52c(st); name = DAT_005d37d0; break;
                    case 'N': id1 = 0; id2 = 0; name = DAT_005d37c9; break;
                    case 'R': id1 = 0; id2 = 0; name = DAT_005d3568; break;
                    case 'S': id1 = sk_003ac52c(st); if (!id1) return 0; id2 = 0; name = DAT_005d37d7; break;
                    case 'T': id1 = 0; id2 = 0; name = DAT_005d37e5; break;
                    default: id1 = 0; id2 = 0; name = DAT_005d3810; break;   /* 'U' and others */
                    }
                } else if (c2 == 'e') {
                    id1 = sk_003ac52c(st); if (!id1) return 0; id2 = 0; name = DAT_005d6b7d;
                } else if (c2 == 'm') {
                    id1 = sk_003ac52c(st); if (!id1) return 0; id2 = 0; name = DAT_005d6c15;
                } else return 0;
                uint64_t *s = sk_node_alloc(st, 1);
                NODE_SETTAG(s, 0x67); NODE_SETSUBT(s, 3);
                s[0] = (uint64_t)name; s[1] = 1;
                uint64_t *r = sk_node_push2(st, 0x2a, (uint64_t *)built, s);
                if (id1) { if (!r) return 0; sk_node_add(r, id1, st); }
                if (id2) { if (r) { sk_node_add(r, id2, st); return (uint64_t)r; } }
                return (uint64_t)r;
            }
            return 0;
        }
        if (k == 6) return (uint64_t)sk_node_push2(st, 0x171, (uint64_t *)built, a);
        if (STACK_CNT(st) == 0) v = 0;
        else { uint32_t i = STACK_CNT(st) - 1; v = STACK_BASE(st)[i];
               if (NODE_TAG(v) != 0xf4) v = 0; else STACK_CNT(st) = i; }
        return (uint64_t)sk_node_push2(st, 0x174, (uint64_t *)built, v);
    }
}