/* Recreated from cl4_kernel.raw (cL4 Secure Kernel, arm64e, image base 0) —
 * the cL4 microkernel (GL1). Ground truth: Ghidra FUN_ names + addresses in
 * the cl4_kernel.raw program. All names are estimates unless string/header
 * matched.
 * Slice R03: 0x3a6c28-0x3ba390.
 * This slice is the tagged-value stream serializer/deserializer: a
 * Tightbeam-style compact-data subsystem that turns a byte stream (read
 * through a stream-context at +0x38 data / +0x40 end / +0x48 pos) into a
 * tree of tagged value nodes, and back. Every node is a small block: [0] data
 * pointer, [1] count/value word, [2] = 16-bit tag at +0x10, [3] = a one-byte
 * sub-type/flags at +0x12. A per-context value stack (array at +0x58, count at
 * +0x60) is used to build/consume nested values. Register-argument functions
 * (x20 "self", x21 "flag") model those args as explicit leading parameters;
 * Ghidra's unaff_x20/x21 are noted in comments. */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "sk_internal.h"

/* A tagged value node: [0]=data/child pointer, [1]=count/value word,
 * [2]=16-bit tag at +0x10, byte at +0x12 = sub-type/flags. */
typedef uint64_t sk_node;

/* Stream context (param_1 of the reader/writer entry points):
 *   +0x38 data base, +0x40 end, +0x48 position,
 *   +0x58 value-stack array, +0x60 value-stack count. */

/* ------------------------------------------------------------------ *
 * Shared stream / node helpers (extern; owned by sibling slices).
 * Signatures match the observed call sites; names are estimates.
 * ------------------------------------------------------------------ */
extern void *sk_node_alloc(void *st, long n);              /* FUN_003a3898 */
extern void sk_node_add(void *parent, void *child, void *st); /* FUN_003a3460 */
extern void *sk_node_push(void *st, int tag, void *node);  /* FUN_003a4b38 */
extern void sk_node_finalize(void *node, int flag);        /* FUN_003a36d8 */
extern void sk_stream_err(void *st, int code, ...);        /* FUN_003a4b98 */
extern void sk_out_str(void *out, const char *str, long len); /* FUN_00112e8c */
extern void *sk_stream_dispatch(void *st);                 /* FUN_003a672c */
extern uint64_t sk_val_get(uint64_t v);                    /* FUN_003a663c */
extern void *sk_stream_pop(void *st);                      /* FUN_003a58b0 */
extern long sk_tag_simple(int tag);                        /* FUN_003a3040 */
extern void *sk_alloc_scalar(void *st, long n);            /* FUN_00365660 */
extern void sk_lock(void *lock, long op);                  /* thunk_FUN_00012568 */
extern long sk_query_flag(void);                           /* FUN_003b903c */
extern void sk_raw(void *a, void *b);                      /* FUN_003a3a70 */
extern void sk_canary_panic(void) __attribute__((noreturn)); /* FUN_0011d7e8 */
extern void sk_fatal(void) __attribute__((noreturn));      /* FUN_004b89f8 */
extern void sk_print1(void *a, int b, void *c);            /* FUN_001145b0 */
extern void sk_ctx_op(void *a, ...);                       /* FUN_003a4c14 (5-arg) */
extern void *sk_tag_convert(void *st, void *node, int tag);/* FUN_003a4d5c */
extern void sk_log_msg(void *a, void *b);                  /* FUN_00112db4 */
extern long sk_len_query(void);                            /* FUN_00115080 */
extern void sk_grow_buf(void *a, void *b, uint32_t *c, int n); /* FUN_003a3aec */
extern void sk_node_make(void *node, int flag);            /* FUN_003a3a10 */
extern void sk_ctx_setup(void *a, long b, void *c);        /* FUN_003a3a10-ish */