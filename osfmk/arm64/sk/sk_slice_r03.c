
extern void sk_grow_ptrs(void *st, void *buf, uint32_t *cap, int n); /* FUN_003a3578 */
extern void sk_write_data3(void *a, void *b, void *fn, void *c);   /* FUN_003b0be0 */
extern void sk_write_data4(void *a);                                /* FUN_003b0d64 */
extern void sk_ctx_setup2(void *a, long b, void *c);                /* FUN_003a4110 */
extern void sk_ctx_op2(void *a, void *b, void *c, void *d, void *e); /* FUN_003a4f5c */
extern void sk_obj_lock(uint64_t obj, long op);                     /* FUN_00116bb4 */

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
 * builds/consumes nested values. Register-argument functions (x20 "self",
 * x21 "flag") model those args as explicit leading parameters. */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "sk_internal.h"

/* A tagged value node: [0]=data/child pointer, [1]=count/value word,
 * [2]=16-bit tag at +0x10, byte at +0x12 = sub-type/flags. */
typedef uint64_t sk_node;

/* Node accessors. */
#define NODE_TAG(n)    (*(uint16_t *)((char *)(n) + 0x10))
#define NODE_SUBT(n)   (*(uint8_t  *)((char *)(n) + 0x12))
#define NODE_DATA(n)   ((void *)((n)[0]))
#define NODE_VAL(n)    ((n)[1])
#define NODE_SETTAG(n,t) (*(uint16_t *)((char *)(n) + 0x10) = (t))
#define NODE_SETSUBT(n,t)(*(uint8_t  *)((char *)(n) + 0x12) = (t))

/* Stream context field accessors (st = uint64_t*). */
#define STREAM_DATA(st)  (*(char **)((char *)(st) + 0x38))
#define STREAM_END(st)   (*(uint64_t *)((char *)(st) + 0x40))
#define STREAM_POS(st)   (*(uint64_t *)((char *)(st) + 0x48))
#define STACK_BASE(st)   (*(uint64_t **)((char *)(st) + 0x58))
#define STACK_CNT(st)    (*(uint32_t *)((char *)(st) + 0x60))

/* ------------------------------------------------------------------ *
 * Shared stream / node helpers (extern; owned by sibling slices).
 * Signatures match the observed call sites; names are estimates.
 * ------------------------------------------------------------------ */
extern void *sk_node_alloc(void *st, long n);               /* FUN_003a3898 */
extern void sk_node_add(void *parent, void *child, void *st); /* FUN_003a3460 */
extern void *sk_node_push(void *st, int tag, void *node);   /* FUN_003a4b38 */
extern void sk_node_finalize(void *node, int flag);         /* FUN_003a36d8 */
extern void sk_stream_err(void *st, int code, ...);         /* FUN_003a4b98 */
extern void sk_out_str(void *out, const char *str, long len); /* FUN_00112e8c */
extern void *sk_stream_dispatch(void *st);                  /* FUN_003a672c */
extern uint64_t sk_val_get(uint64_t v);                     /* FUN_003a663c */
extern void *sk_stream_pop(void *st);                       /* FUN_003a58b0 */
extern long sk_tag_simple(int tag);                         /* FUN_003a3040 */
extern void *sk_alloc_scalar(void *st, long n);             /* FUN_00365660 */
extern void sk_lock(void *lock, long op);                   /* thunk_FUN_00012568 */
extern long sk_query_flag(void);                            /* FUN_003b903c */
extern void sk_raw(void *a, void *b);                       /* FUN_003a3a70 */
extern void sk_canary_panic(void) __attribute__((noreturn));/* FUN_0011d7e8 */
extern void sk_fatal(void) __attribute__((noreturn));       /* FUN_004b89f8 */
extern void sk_print1(void *a, int b, void *c);             /* FUN_001145b0 */
extern void sk_ctx_op(void *a, ...);                        /* FUN_003a4c14 */
extern void *sk_tag_convert(void *st, void *node, int tag); /* FUN_003a4d5c */
extern void sk_log_msg(void *a, void *b);                   /* FUN_00112db4 */
extern long sk_len_query(void);                             /* FUN_00115080 */
extern void sk_grow_buf(void *a, void *b, uint32_t *c, int n); /* FUN_003a3aec */
extern void *sk_node_make(void *st, int tag, void *arg);    /* FUN_003a3a10 */

/* ------------------------------------------------------------------ *
 * Forward declarations for this slice's own functions (in address order).
 * ------------------------------------------------------------------ */

/* Reader/dispatch entry points (stream context st = uint64_t*). */
static uint64_t *sk_parse_function_type(uint64_t *st);       /* FUN_003a6c28 */
static uint64_t *sk_parse_ident_char(uint64_t *st);          /* FUN_003a75e4 */
static uint64_t *sk_parse_token_A(uint64_t *st);             /* FUN_003a7818 */
static uint64_t *sk_parse_token_letter(uint64_t *st);        /* FUN_003a7d9c */
static uint64_t *sk_parse_token_b(uint64_t *st, uint64_t a, uint64_t b); /* FUN_003a81e8 */
static uint64_t *sk_parse_string(uint64_t *st);              /* FUN_003a8868 */
static uint64_t *sk_parse_value_compound(uint64_t *st);      /* FUN_003a8ab4 */
static uint64_t *sk_parse_fn_header(uint64_t *st);           /* FUN_003a9944 */
static uint64_t *sk_parse_list(uint64_t *st);                /* FUN_003aa804 */
static void sk_emit_2tag(uint64_t *st, uint16_t tag, int flag); /* FUN_003ab218 */
static uint64_t *sk_parse_char(uint64_t *st);                /* FUN_003ab40c */
static void sk_emit_da(uint64_t *st);                        /* FUN_003ab780 */
static uint64_t *sk_pop_ba(uint64_t *st);                    /* FUN_003ab7f4 */
static uint64_t *sk_parse_comma_list(uint64_t *st, int flag);/* FUN_003ab948 */
static uint64_t *sk_parse_escaped(uint64_t *st);             /* FUN_003abad0 */
static void sk_parse_z_s(uint64_t *st);                      /* FUN_003abc48 */
static uint64_t *sk_parse_eb(uint64_t *st);                  /* FUN_003abd1c */
static void sk_pop_comma(uint64_t *st);                      /* FUN_003abef0 */
static uint64_t *sk_read_char(uint64_t *st);                 /* FUN_003abf88 */
static uint64_t *sk_make_range(uint64_t *st, uint32_t lo, uint32_t hi); /* FUN_003ac2d0 */
static void sk_parse_n(uint64_t *st);                        /* FUN_003ac394 */
static int sk_read_digits(uint64_t *st);                     /* FUN_003ac430 */
static int sk_read_ident(uint64_t *st);                      /* FUN_003ac4a4 */
static uint64_t *sk_parse_ab(uint64_t *st);                  /* FUN_003ac52c */
static uint64_t *sk_build_children(uint64_t *st, int n, uint64_t base); /* FUN_003ac580 */
static void sk_err_ab(uint64_t *st, uint64_t code, uint64_t a); /* FUN_003ac600 */
static const char *sk_typename(int tag, uint32_t flags);     /* FUN_003ac6b4 */
static void sk_buf_byte(uint64_t *buf, uint8_t *p, uint64_t st); /* FUN_003acd3c */
static bool sk_is_printable(int tag);                        /* FUN_003acda0 */
static uint64_t *sk_pop_a3(uint64_t *st);                    /* FUN_003ace08 */
static uint64_t *sk_pop_f4(uint64_t *st);                    /* FUN_003ace50 */
static uint64_t *sk_pop_value(uint64_t *st);                 /* FUN_003acefc */
static uint64_t sk_tag_is_leaf(uint32_t tag);                /* FUN_003acf38 */
static uint64_t *sk_write_bytes(uint64_t st, uint64_t a, uint64_t b, uint8_t c); /* FUN_003acfb4 */
static uint64_t *sk_parse_string_token(uint64_t *st);        /* FUN_003ad048 */
static void sk_emit_f4(uint64_t *st, uint64_t tag);          /* FUN_003ad0f0 */
static uint64_t *sk_parse_ee(uint64_t *st);                  /* FUN_003ad188 */
static uint64_t *sk_parse_di(uint64_t *st);                  /* FUN_003ad278 */
static uint64_t *sk_parse_f7(uint64_t *st);                  /* FUN_003ad3a0 */
static uint64_t *sk_parse_pair2(uint64_t *st);               /* FUN_003ad478 */
static void sk_err_c4(uint64_t *st);                         /* FUN_003ad560 */
static uint64_t *sk_parse_ident_103(uint64_t *st);           /* FUN_003ad5a4 */
static void sk_err_val(uint64_t *st);                        /* FUN_003ad61c */
static uint64_t *sk_collect_da(uint64_t *st);                /* FUN_003ad67c */
static uint64_t *sk_parse_value(uint64_t *st, uint64_t ctx, uint64_t *out); /* FUN_003ad724 */
static void sk_buf_push(uint64_t *buf, uint64_t *p, uint64_t st); /* FUN_003ad810 */
static uint64_t *sk_merge_values(uint64_t st, uint64_t *a, uint64_t *b, uint64_t n); /* FUN_003ad874 */
static uint64_t sk_is_printable2(uint64_t *node);            /* FUN_003adcd8 */
static uint64_t *sk_parse_group(uint64_t *st, uint64_t tag); /* FUN_003add54 */
static uint64_t *sk_parse_group2(uint64_t *st, uint64_t tag);/* FUN_003adf20 */
static uint64_t *sk_parse_arg1(uint64_t *st);                /* FUN_003adff0 */
static uint64_t *sk_parse_arg2(uint64_t *st);                /* FUN_003ae05c */
static uint64_t *sk_parse_arg3(uint64_t *st);                /* FUN_003ae0c8 */
static uint64_t *sk_parse_arg4(uint64_t *st);                /* FUN_003ae134 */
static uint64_t *sk_pop_list(uint64_t *st);                  /* FUN_003ae1b4 */
static uint64_t *sk_pop_value2(uint64_t *st);                /* FUN_003ae36c */
static void sk_err_lc(uint64_t *st, uint64_t tag);           /* FUN_003ae414 */
static uint64_t *sk_pop_pair(uint64_t *st, uint64_t tag);    /* FUN_003ae4c8 */
static uint64_t *sk_pop_f4_2(uint64_t *st);                  /* FUN_003ae658 */
static uint64_t *sk_parse_value2(uint64_t *st, uint64_t a, uint64_t *out); /* FUN_003ae734 */
static uint64_t *sk_pop_value3(uint64_t *st);                /* FUN_003ae8a0 */
static uint64_t *sk_emit_tag(uint64_t *st, uint16_t tag);    /* FUN_003ae9e0 */
static uint64_t *sk_pop_f4_3(uint64_t *st);                  /* FUN_003aebb0 */
static uint64_t *sk_parse_n3(uint64_t *st, uint64_t a, uint64_t n); /* FUN_003aef74 */
static void sk_buf_write(uint64_t *buf, uint64_t *p);        /* FUN_003aefe4 */
static void sk_buf_free(uint64_t *buf, uint64_t st);         /* FUN_003af0cc */
static uint64_t *sk_pop_compound(uint64_t *st);              /* FUN_003af238 */
static uint64_t *sk_pop_compound2(uint64_t *st);             /* FUN_003af3c4 */
static uint64_t *sk_emit_f4_4(uint64_t *st, uint16_t tag);   /* FUN_003af4d4 */
static uint64_t *sk_parse_str_18(uint64_t *st);              /* FUN_003af614 */
static uint64_t *sk_pop_compound3(uint64_t *st);             /* FUN_003af6ac */
static uint64_t *sk_pop_compound4(uint64_t *st);             /* FUN_003af7a4 */
static uint64_t *sk_emit_f4_5(uint64_t *st, uint16_t tag);   /* FUN_003af99c */
static uint64_t *sk_parse_n3b(uint64_t *st, uint64_t a, uint64_t n); /* FUN_003aff04 */
static void sk_init_buf(uint64_t *st, int n);                /* FUN_003b0004 */
static uint64_t *sk_pop_simple(uint64_t *st);                /* FUN_003b0078 */
static uint64_t *sk_parse_str_2(uint64_t *st);               /* FUN_003b0174 */
static uint64_t *sk_pop_simple2(uint64_t *st);               /* FUN_003b0220 */
static uint64_t *sk_pop_simple3(uint64_t *st);               /* FUN_003b02dc */
static uint64_t *sk_pop_simple4(uint64_t *st, uint64_t a);   /* FUN_003b03c0 */
static void sk_err_msg(uint64_t *st, uint64_t a);            /* FUN_003b05c8 */
static uint64_t *sk_pop_simple5(uint64_t *st);               /* FUN_003b06ac */
static bool sk_is_tw(uint32_t tag);                          /* FUN_003b0a64 */
static bool sk_is_tw2(int tag);                              /* FUN_003b0aa4 */
static void sk_acquire_38(void);                             /* FUN_003b0b08 */
static void sk_acquire_38b(void);                            /* FUN_003b0b0c */
static void sk_init_obj(uint64_t *obj);                      /* FUN_003b0b28 */
static uint64_t *sk_lock(uint64_t *lock);                    /* FUN_003b0b7c */
static void sk_write_data(uint64_t a, uint16_t *b, void *fn, uint64_t c); /* FUN_003b0be0 */
static void sk_write_data2(uint64_t *a);                     /* FUN_003b0d64 */
static void sk_err2(uint64_t a, uint64_t b);                 /* FUN_003b0e1c */
static uint64_t sk_strlen(uint64_t a, uint8_t *b);           /* FUN_003b0ec4 */
static uint64_t sk_cmp(uint64_t a, uint64_t b);              /* FUN_003b0f48 */
static uint64_t sk_cmp2(uint64_t a, uint64_t b);             /* FUN_003b0fb8 */
static uint64_t *sk_release(uint64_t *obj);                  /* FUN_003b1034 */
static void sk_alloc_bits(uint64_t a, uint64_t n);           /* FUN_003b10a8 */
static uint64_t *sk_str_read(uint8_t *p, uint64_t n);        /* FUN_003b10f0 */
static uint64_t *sk_query_obj(uint64_t a);                   /* FUN_003b1178 */
static void sk_write_str(uint64_t *a, char *b, uint64_t c);  /* FUN_003b12cc */
static void sk_write_str2(uint64_t *a, uint64_t *b, uint64_t c, int d); /* FUN_003b1328 */
static uint64_t *sk_call3(uint64_t a, uint64_t b, uint64_t c); /* FUN_003b1e74 */
static void sk_printf4(uint64_t a, uint64_t b, uint64_t c, uint64_t d); /* FUN_003b1eec */
static uint64_t *sk_call3b(uint64_t a, uint64_t b, uint64_t c); /* FUN_003b1f20 */
static uint64_t *sk_call3c(uint64_t a, uint64_t b, uint64_t c); /* FUN_003b1f98 */
static void sk_write_all(uint64_t *a, uint64_t b, uint64_t c, uint64_t d); /* FUN_003b2010 */
static void sk_write6(uint64_t a, uint64_t *b, uint64_t *c, int d, uint64_t e); /* FUN_003b20f4 */
static void sk_print_tree(uint64_t *out, uint64_t *node, uint64_t depth, uint32_t flag); /* FUN_003b2180 */
static void sk_print_leaf(uint64_t a, uint64_t *b, uint64_t c, uint64_t d); /* FUN_003b8d18 */
static void sk_print_leaf2(uint64_t a, uint64_t *b, uint64_t c); /* FUN_003b8d94 */
static void sk_print_leaf3(uint64_t a, uint64_t b);          /* FUN_003b8e48 */
static uint8_t sk_byte(uint64_t a, uint64_t *b);             /* FUN_003b8ef8 */
static uint64_t sk_query2(uint64_t a, uint64_t *b);          /* FUN_003b903c */
static void sk_print4(uint64_t a, uint64_t b, int c);        /* FUN_003b9794 */
static uint64_t *sk_print5(uint64_t a, uint64_t *b);         /* FUN_003b982c */
static bool sk_is_leaf(uint64_t *a, uint64_t b, uint64_t c); /* FUN_003b9c14 */
static bool sk_is_leaf2(uint64_t *a);                        /* FUN_003b9c6c */
static void sk_write7(uint64_t a, uint64_t *b, uint64_t c);  /* FUN_003b9cb4 */
static uint64_t sk_write8(uint64_t a, uint64_t *b, uint32_t c); /* FUN_003ba044 */
static void sk_write9(uint64_t a, uint64_t b, uint64_t *c, int d, int e); /* FUN_003ba114 */
static void sk_write10(uint64_t *a, uint64_t b, uint64_t *c, uint64_t d); /* FUN_003ba390 */

/* FUN_003ac430 @ 0x3ac430   (est. sk_read_digits)
 * Reads a run of ASCII decimal digits starting at the current stream
 * position; returns the accumulated integer, or -1000 if the run overflows
 * or no digits are present. Advances the stream position past the digits.
 * Confidence: high */
static int sk_read_digits(uint64_t *st)
{
    uint64_t pos = STREAM_POS(st);
    int acc = 0;
    if (pos < STREAM_END(st)) {
        uint8_t c = STREAM_DATA(st)[pos];
        if (c - 0x30 < 10) {
            do {
                uint8_t d = STREAM_DATA(st)[pos];
                if (9 < d - 0x30) return acc;
                int nv = d + acc * 10 - 0x30;
                if (nv < acc) return -1000;      /* overflow */
                pos += 1;
                STREAM_POS(st) = pos;
                acc = nv;
            } while (STREAM_END(st) != pos);
            return acc;
        }
    }
    return -1000;
}

/* FUN_003ac4a4 @ 0x3ac4a4   (est. sk_read_ident)
 * Reads a '_..._' identifier: an optional leading '_', then digits (via
 * sk_read_digits), then a required trailing '_'. Returns the digit value +1
 * for an explicit '_N_' form, 0 for a bare '_', or -1000 on malformed input.
 * Confidence: high */
static int sk_read_ident(uint64_t *st)
{
    uint64_t pos = STREAM_POS(st);
    if (pos < STREAM_END(st) && STREAM_DATA(st)[pos] == '_') {
        STREAM_POS(st) = pos + 1;
        return 0;                                    /* bare '_' */
    }
    int v = sk_read_digits(st);
    if (v < 0) return v;
    pos = STREAM_POS(st);
    if (STREAM_END(st) <= pos || STREAM_DATA(st)[pos] != '_') return -1000;
    STREAM_POS(st) = pos + 1;
    return v + 1;
}

/* FUN_003ac52c @ 0x3ac52c   (est. sk_parse_ab)
 * Parses an '_N_' identifier into a scalar node (tag 0xab, sub 4) holding the
 * value, or returns NULL when the identifier is invalid (negative).
 * Confidence: high */
static uint64_t *sk_parse_ab(uint64_t *st)
{
    int v = sk_read_ident(st);
    if (v < 0) return NULL;
    uint64_t *n = sk_node_alloc(st, 1);
    NODE_SETTAG(n, 0xab); NODE_SETSUBT(n, 4);
    n[0] = (uint64_t)v;
    return n;
}

/* FUN_003acf38 @ 0x3acf38   (est. sk_tag_is_leaf)
 * Returns 1 when the tag denotes a leaf scalar (a value with no children),
 * 0 otherwise. Tested against bitmask tables of leaf tags.
 * Confidence: medium */
static uint64_t sk_tag_is_leaf(uint32_t tag)
{
    if ((int)tag < 0xbf) {
        if (tag < 0x40 && ((1ULL << (tag & 0x3f)) & 0x8000000002200000ULL) != 0)
            return 1;
        if (tag == 0xb1) return 1;
    } else if (((tag - 0xbf < 0x38) &&
                ((1ULL << ((tag - 0xbf) & 0x3f)) & 0xc0010000000003ULL) != 0) ||
               (tag == 0x16b)) {
        return 1;
    }
    return 0;
}

/* FUN_003acda0 @ 0x3acda0   (est. sk_is_printable)
 * Returns true when the tag is in the printable/scalar set (used by the
 * printer to decide whether a node is emitted inline).
 * Confidence: medium */
static bool sk_is_printable(int tag)
{
    uint32_t u = (uint32_t)(tag - 0xb7);
    if (!(0x3e < u || ((1ULL << (u & 0x3f)) & 0x400000040000020dULL) == 0)) return true;
    u = (uint32_t)(tag - 0x67);
    if (!(0x2b < u || ((1ULL << (u & 0x3f)) & 0x80004000001ULL) == 0)) return true;
    return tag == 0x16b;
}

/* FUN_003adcd8 @ 0x3adcd8   (est. sk_is_printable2)
 * Compound test used by the tree printer: returns 1 when the node is NOT a
 * printable leaf and must be recursed into (checks a second tag set).
 * Confidence: medium */
static uint64_t sk_is_printable2(uint64_t *node)
{
    uint32_t u = NODE_TAG(node);
    if (NODE_TAG(node) < 0xbc) {
        if (!(0x3a < u - 0x48 || ((1ULL << ((u - 0x48) & 0x3f)) & 0x404000000000001ULL) == 0) ||
            u == 0x22) {
            return 0;
        }
    } else if (!(2 < u - 0xbc) ||
               (0x25 < u - 0xe6 ||
                ((1ULL << ((u - 0xe6) & 0x3f)) & 0x2000000005ULL) == 0)) {
        return 0;
    }
    return 1;
}

/* FUN_003acd3c @ 0x3acd3c   (est. sk_buf_byte)
 * Appends a single byte to a growing byte buffer (buf[0]=ptr, [1]=count,
 * +0xc=capacity), growing via FUN_003a3aec when full.
 * Confidence: high */
static void sk_buf_byte(uint64_t *buf, uint8_t *p, uint64_t st)
{
    uint32_t cnt = *(uint32_t *)(buf + 1);
    if (*(uint32_t *)((char *)buf + 0xc) <= cnt) {
        sk_grow_buf((void *)st, buf, (uint32_t *)((char *)buf + 0xc), 1);
        cnt = *(uint32_t *)(buf + 1);
    }
    uint8_t b = *p;
    *(uint32_t *)(buf + 1) = cnt + 1;
    *(uint8_t *)(buf[0] + cnt) = b;
}

/* FUN_003ad810 @ 0x3ad810   (est. sk_buf_push)
 * Appends one 64-bit word to a growing pointer/word buffer (buf[0]=ptr,
 * [1]=count, +0xc=capacity), growing via FUN_003a3578 when full.
 * Confidence: high */
static void sk_buf_push(uint64_t *buf, uint64_t *p, uint64_t st)
{
    uint32_t cnt = *(uint32_t *)(buf + 1);
    if (*(uint32_t *)((char *)buf + 0xc) <= cnt) {
        sk_grow_ptrs((void *)st, buf, (uint32_t *)((char *)buf + 0xc), 1);
        cnt = *(uint32_t *)(buf + 1);
    }
    uint64_t w = *p;
    *(uint32_t *)(buf + 1) = cnt + 1;
    *(uint64_t *)(buf[0] + (uint64_t)cnt * 8) = w;
}