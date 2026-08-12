/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel,
 * arm64e, image base 0) — the cL4 microkernel (GL1), "cL4 (679.100.61)".
 * Ground truth: Ghidra FUN_ names + addresses in program cl4_kernel.raw.
 * This region (0x3cc000-0x3d2e80) is the IPC message-register packer:
 * helpers that decode a message descriptor word and re-emit its fields as
 * tagged IPC message-register records, plus a demangler node-printer and an
 * internal hash map used by the symbol index. All names are estimates unless
 * string-matched. */

#include <stdint.h>
#include <stddef.h>
#include <string.h>

/* ------------------------------------------------------------------ *
 * Out-of-range cL4 helpers (declared extern with a one-line note; their
 * bodies are reconstructed by the range worker that owns them).
 * ------------------------------------------------------------------ */

/* FUN_003a3a70 @ 0x3a3a70 — emit a tagged IPC message-register record into
 * the outbound message object at `obj`: appends the 2/3-char tag string
 * `tag` followed by `count` data words, using the outbound depth/state word
 * `val` (obj+0x10 slot). */
extern void cL4_mr_emit_tag(long obj, const void *tag, unsigned long count, unsigned long val);
/* FUN_003acd3c @ 0x3acd3c — emit a single data byte (pointed to by `byte`)
 * into the outbound message object at `obj`; `val` is the outbound depth word. */
extern void cL4_mr_emit_byte(long obj, const void *byte, unsigned long val);
/* FUN_003a3b9c @ 0x3a3b9c — emit a count-sized value record (`count`-1 data
 * words) into the outbound object at `obj`. */
extern void cL4_mr_emit_val(long obj, long count, unsigned long val);
/* FUN_003a3c20 @ 0x3a3c20 — emit a count-sized value record into the outbound
 * object at `obj` (variant used by the tag emitters). */
extern void cL4_mr_emit_val2(long obj, long count, unsigned long val);
/* FUN_003bfae4 @ 0x3bfae4 — decode one argument `word` and emit it into the
 * outbound message, honoring `depth`; sets `*res` on error (non-zero) and
 * clears the 4-word result on success. Central arg-marshalling primitive. */
extern void cL4_arg_decode(int *res, unsigned long tcb, unsigned long word, unsigned long depth);
/* FUN_003bf898 @ 0x3bf898 — release/commit the temporary output record whose
 * descriptor is `*stack` (built by the cL4 format helpers). */
extern void cL4_out_commit(unsigned long tcb, long *stack);
/* FUN_003bf718 @ 0x3bf718 — build an output descriptor for `tcb`/`msg`
 * (returns a 16-byte record); FUN_003bf7e4 reads the descriptor's kind. */
extern unsigned char (*cL4_fmt_build(unsigned long tcb, unsigned long msg, unsigned long depth))[16];
extern int cL4_fmt_kind(unsigned long tcb, unsigned char (*desc)[16]);
/* FUN_003b1328 @ 0x3b1328 — construct an output buffer from a (ptr,len,flag)
 * triple into a 16-byte record; used by the tag/string emitters. */
extern void cL4_fmt_make(unsigned char out[16], unsigned long a, unsigned long b, int flag);
/* FUN_003b12cc @ 0x3b12cc — construct an output buffer from a (ptr,len) pair. */
extern void cL4_fmt_make2(void *out, unsigned long a, unsigned long b);
/* FUN_003bef24 @ 0x3bef24 — format a demangler node into an output buffer. */
extern void cL4_fmt_node(unsigned long node, unsigned long ctx, void *out, int depth);
/* FUN_003b10f0 @ 0x3b10f0 — predicate: whether `node` needs special quoting
 * in the demangler output. */
extern int cL4_fmt_need_quote(unsigned long node, unsigned long ctx);
/* FUN_003ad810 @ 0x3ad810 — emit an array of argument words. */
extern void cL4_fmt_args(void *res, unsigned long *words, unsigned long ctx);
/* FUN_003adcd8 @ 0x3adcd8 — decode/advance one message word. */
extern int cL4_fmt_advance(long msg);
/* FUN_003c5af4 @ 0x3c5af4 — decode an argument of descriptor kind 0x2c. */
extern void cL4_arg_kind2c(int *res, unsigned long tcb, long msg, unsigned long depth);
/* FUN_003c4bc8 / 003c4d14 / 003c5e60 / 003c5f8c / 003c60b8 / 003c61e4 —
 * decode arguments of descriptor kinds 0x1b / 0x1c / 0x30 / 0x31 / 0x32 / 0x33. */
extern void cL4_arg_kind1b(unsigned long tcb, long msg, unsigned long depth);
extern void cL4_arg_kind1c(unsigned long tcb, long msg, unsigned long depth);
extern void cL4_arg_kind30(unsigned long tcb, long msg, unsigned long depth);
extern void cL4_arg_kind31(unsigned long tcb, long msg, unsigned long depth);
extern void cL4_arg_kind32(unsigned long tcb, long msg, unsigned long depth);
extern void cL4_arg_kind33(unsigned long tcb, long msg, unsigned long depth);
/* FUN_003c312c @ 0x3c312c — query message kind (returns 0 for a known
 * single-word descriptor, non-zero for a composite). */
extern int cL4_msg_kind(long msg);
/* FUN_003c3264 @ 0x3c3264 — parse/validate a message header. */
extern int cL4_msg_header(int *res, long msg, unsigned long ctx);
/* FUN_003bf2d0 / 003bf40c — compare two map keys (the "hash equals" for the
 * associative container). */
extern unsigned long cL4_map_key_eq_a(unsigned long a, unsigned long b);
extern unsigned long cL4_map_key_eq_b(unsigned long *slot, unsigned long a, unsigned long b);
/* FUN_0037d700 @ 0x37d700 — rehash/resize the associative container `map`. */
extern void cL4_map_resize(long *map, unsigned long new_cap);
/* FUN_00111890 @ 0x111890 — allocate `size` bytes with allocator tag. */
extern void *cL4_alloc(unsigned long size, unsigned long tag);
/* FUN_00117cc4 — memcpy (buffer copy). */
extern void *cL4_memcpy(void *dst, const void *src, unsigned long n);
/* FUN_00116bb4 @ 0x116bb4 — snprintf-style: returns bytes needed (or -1). */
extern long cL4_snprintf(char *buf, unsigned long cap, const char *fmt, ...);
/* FUN_001130a0 @ 0x1130a0 — append one char to the demangler output stream. */
extern void cL4_out_putc(unsigned long out, char c);
/* FUN_00112e8c @ 0x112e8c — append `n` bytes to the demangler output stream. */
extern void cL4_out_puts(unsigned long out, const void *s, unsigned long n);
/* FUN_001145b0 — memcmp. */
extern int cL4_memcmp(const void *a, const void *b, unsigned long n);
/* FUN_00115080 — strlen. */
extern unsigned long cL4_strlen(const char *s);
/* FUN_000101a0 @ 0x101a0 — allocate a growable-buffer block with tag. */
extern void *cL4_alloc_grow(unsigned long size, unsigned long tag);
/* thunk_FUN_00012568 @ 0x12568 — free. */
extern void cL4_free(void *p, unsigned long size);
/* FUN_00369b0c — whether console logging is enabled. */
extern int cL4_log_enabled(void);
/* thunk_FUN_00369b04 — emit a log line. */
extern void cL4_log(int level, const char *msg, unsigned long x);
/* FUN_004b9d68 @ 0x4b9d68 — emit a printf-style log line. */
extern void cL4_log_fmt(unsigned long x, unsigned long fmt);
/* FUN_0038df24 — build a formatted string into an output buffer. */
extern void cL4_fmt_build_str(void *out, const char *fmt, ...);

/* In-range prototypes (bodies below). */
extern void cL4_mr_emit_num(unsigned long tcb, long n);        /* FUN_003d05e0 */
extern unsigned long cL4_fmt_begin(unsigned long tcb, unsigned long msg, unsigned char (*desc)[16], unsigned long depth); /* FUN_003d0358 */
extern unsigned long cL4_fmt_emit_letter(unsigned long *state, unsigned long tcb, unsigned char *text, unsigned long count, unsigned int flag); /* FUN_003d0650 */
extern unsigned char cL4_msg_decode(unsigned long tcb, unsigned long *msg);  /* FUN_003d0458 */
extern void cL4_msg_args(int *res, unsigned long tcb, unsigned long *msg, unsigned long depth); /* FUN_003d01ac */
extern void cL4_msg_one(int *res, unsigned long tcb, unsigned long *msg, unsigned long depth);  /* FUN_003d11d4 */
extern void cL4_msg_three(int *res, unsigned long tcb, unsigned long *msg, unsigned long depth);/* FUN_003d1218 */
extern void cL4_msg_parse(unsigned long *res, unsigned long *tcb, unsigned long *msg, unsigned long depth);/* FUN_003d12c8 */
extern void cL4_msg_emit_pair(unsigned long tcb, unsigned long *msg, unsigned long tag, unsigned char byte); /* FUN_003d154c */
extern void cL4_msg_dispatch2(int *res, unsigned long tcb, unsigned long msg, unsigned long tag, unsigned long count, unsigned long depth); /* FUN_003d174c */
extern unsigned long *cL4_map_put(unsigned long *map, unsigned long key, unsigned long *node); /* FUN_003d28d8 */
extern long cL4_map_find(unsigned long *map, unsigned long key);  /* FUN_003d27ec */
extern void cL4_map_destroy(unsigned long *map);                  /* FUN_003d2740 */
extern unsigned long cL4_map_keyeq(unsigned long *slot, unsigned long *key); /* FUN_003d27a0 */
extern const char *cL4_demangle_kind(unsigned int kind); /* FUN_003d2b1c */
extern void cL4_demangle_node(unsigned long out, unsigned long *node, unsigned long depth); /* FUN_003d2b90 */
extern long cL4_demangle_snprintf_alloc(long *out, unsigned long a, unsigned long b); /* FUN_003d2d34 */
extern void cL4_demangle_emit(unsigned long a, unsigned long b, unsigned long c, unsigned long d); /* FUN_003d2e80 */

/* The demangler node-kind name table lives at 0x67c558 (indexed by kind). */
extern const char *g_demangle_kind_names[0x17a]; /* _DAT_0067c558 */

/* The empty separator string (used as the default tag for 0-arg records). */
extern const char DAT_005be7c0[]; /* _DAT_005be7c0 = "" */

/* Forward declarations for in-file helpers defined later in this slice. */
void cL4_msg_emit_sym_raw(unsigned long *tcb, long start, long end);      /* FUN_003d1b88 */
void cL4_grow_buffer(unsigned long *buf, unsigned long *entry, unsigned long ctx); /* FUN_003d2058 */
void cL4_grow_buffer_ensure(unsigned long alloc_ctx, unsigned long *buf, unsigned int *cap, unsigned long need); /* FUN_003d20bc */
unsigned long cL4_grow_alloc(unsigned long buf, unsigned long elems);     /* FUN_003d216c */
void cL4_fmt_put_index(unsigned long out, unsigned long index);          /* FUN_003b1e74 @ 0x3b1e74 */
void cL4_msg_dispatch_tag(int *result, unsigned long tcb, unsigned long msg, unsigned long tag, unsigned long count, unsigned long depth); /* FUN_003d1128 */
void cL4_msg_dispatch_full(int *result, unsigned long *tcb, unsigned long msg, unsigned long depth); /* FUN_003d08c4 */
void cL4_msg_dispatch_pkt(int *result, unsigned long tcb, unsigned long msg, unsigned char *byte, unsigned long depth, int flag); /* FUN_003d0bc8 */
void cL4_msg_emit_sym(unsigned long tcb, unsigned long *msg, int which);   /* FUN_003d1ad4 */

/* 003ccd3c @ 0x003ccd3c   (est. cL4_ipc_emit_mb)
 * Ghidra: void FUN_003ccd3c(int *result, long tcb, void *msg, int depth)
 * Decode the single message word in `msg` (kind-1/5 check) and emit it as a
 * tagged IPC message-register record with tag "MB"; on parse error leave
 * the result word set, else clear it. Confidence: medium. */
void cL4_ipc_emit_mb(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_one(result, tcb, (unsigned long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, "MB", 2, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003ccd98 @ 0x003ccd98   (est. cL4_ipc_emit_mf)
 * Ghidra: void FUN_003ccd98(int *result, long tcb, void *msg, int depth)
 * Decode the single message word in `msg` (kind-1/5 check) and emit it as a
 * tagged IPC message-register record with tag "MF"; on parse error leave
 * the result word set, else clear it. Confidence: medium. */
void cL4_ipc_emit_mf(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_one(result, tcb, (unsigned long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, "MF", 2, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003ccdf4 @ 0x003ccdf4   (est. cL4_ipc_emit_ma)
 * Ghidra: void FUN_003ccdf4(int *result, long tcb, void *msg, int depth)
 * Decode the single message word in `msg` (kind-1/5 check) and emit it as a
 * tagged IPC message-register record with tag "MA"; on parse error leave
 * the result word set, else clear it. Confidence: medium. */
void cL4_ipc_emit_ma(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_one(result, tcb, (unsigned long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, "MA", 2, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003cce50 @ 0x003cce50   (est. cL4_ipc_emit_mc)
 * Ghidra: void FUN_003cce50(int *result, long tcb, void *msg, int depth)
 * Decode the single message word in `msg` (kind-1/5 check) and emit it as a
 * tagged IPC message-register record with tag "MC"; on parse error leave
 * the result word set, else clear it. Confidence: medium. */
void cL4_ipc_emit_mc(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_one(result, tcb, (unsigned long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, "MC", 2, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003ccf08 @ 0x003ccf08   (est. cL4_ipc_emit_tc)
 * Ghidra: void FUN_003ccf08(int *result, long tcb, void *msg, int depth)
 * Decode the single message word in `msg` (kind-1/5 check) and emit it as a
 * tagged IPC message-register record with tag "Tc"; on parse error leave
 * the result word set, else clear it. Confidence: medium. */
void cL4_ipc_emit_tc(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_one(result, tcb, (unsigned long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, "Tc", 2, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003ccfe0 @ 0x003ccfe0   (est. cL4_ipc_emit_tj)
 * Ghidra: void FUN_003ccfe0(int *result, long tcb, void *msg, int depth)
 * Decode the single message word in `msg` (kind-1/5 check) and emit it as a
 * tagged IPC message-register record with tag "Tj"; on parse error leave
 * the result word set, else clear it. Confidence: medium. */
void cL4_ipc_emit_tj(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_one(result, tcb, (unsigned long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, "Tj", 2, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003cd03c @ 0x003cd03c   (est. cL4_ipc_emit_tq)
 * Ghidra: void FUN_003cd03c(int *result, long tcb, void *msg, int depth)
 * Decode the single message word in `msg` (kind-1/5 check) and emit it as a
 * tagged IPC message-register record with tag "Tq"; on parse error leave
 * the result word set, else clear it. Confidence: medium. */
void cL4_ipc_emit_tq(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_one(result, tcb, (unsigned long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, "Tq", 2, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003ce4f8 @ 0x003ce4f8   (est. cL4_ipc_emit_mq)
 * Ghidra: void FUN_003ce4f8(int *result, long tcb, void *msg, int depth)
 * Decode the single message word in `msg` (kind-1/5 check) and emit it as a
 * tagged IPC message-register record with tag "MQ"; on parse error leave
 * the result word set, else clear it. Confidence: medium. */
void cL4_ipc_emit_mq(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_one(result, tcb, (unsigned long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, "MQ", 2, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003ce554 @ 0x003ce554   (est. cL4_ipc_emit_ho)
 * Ghidra: void FUN_003ce554(int *result, long tcb, void *msg, int depth)
 * Decode the single message word in `msg` (kind-1/5 check) and emit it as a
 * tagged IPC message-register record with tag "Ho"; on parse error leave
 * the result word set, else clear it. Confidence: medium. */
void cL4_ipc_emit_ho(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_one(result, tcb, (unsigned long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, "Ho", 2, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003ce5b0 @ 0x003ce5b0   (est. cL4_ipc_emit_mg)
 * Ghidra: void FUN_003ce5b0(int *result, long tcb, void *msg, int depth)
 * Decode the single message word in `msg` (kind-1/5 check) and emit it as a
 * tagged IPC message-register record with tag "Mg"; on parse error leave
 * the result word set, else clear it. Confidence: medium. */
void cL4_ipc_emit_mg(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_one(result, tcb, (unsigned long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, "Mg", 2, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003ce60c @ 0x003ce60c   (est. cL4_ipc_emit_mh)
 * Ghidra: void FUN_003ce60c(int *result, long tcb, void *msg, int depth)
 * Decode the single message word in `msg` (kind-1/5 check) and emit it as a
 * tagged IPC message-register record with tag "Mh"; on parse error leave
 * the result word set, else clear it. Confidence: medium. */
void cL4_ipc_emit_mh(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_one(result, tcb, (unsigned long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, "Mh", 2, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003ce668 @ 0x003ce668   (est. cL4_ipc_emit_mj)
 * Ghidra: void FUN_003ce668(int *result, long tcb, void *msg, int depth)
 * Decode the single message word in `msg` (kind-1/5 check) and emit it as a
 * tagged IPC message-register record with tag "Mj"; on parse error leave
 * the result word set, else clear it. Confidence: medium. */
void cL4_ipc_emit_mj(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_one(result, tcb, (unsigned long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, "Mj", 2, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003ce6c4 @ 0x003ce6c4   (est. cL4_ipc_emit_mk)
 * Ghidra: void FUN_003ce6c4(int *result, long tcb, void *msg, int depth)
 * Decode the single message word in `msg` (kind-1/5 check) and emit it as a
 * tagged IPC message-register record with tag "Mk"; on parse error leave
 * the result word set, else clear it. Confidence: medium. */
void cL4_ipc_emit_mk(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_one(result, tcb, (unsigned long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, "Mk", 2, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003ce8e4 @ 0x003ce8e4   (est. cL4_ipc_emit_mb2)
 * Ghidra: void FUN_003ce8e4(int *result, long tcb, void *msg, int depth)
 * Decode the single message word in `msg` (kind-1/5 check) and emit it as a
 * tagged IPC message-register record with tag "Mb"; on parse error leave
 * the result word set, else clear it. Confidence: medium. */
void cL4_ipc_emit_mb2(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_one(result, tcb, (unsigned long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, "Mb", 2, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003ce940 @ 0x003ce940   (est. cL4_ipc_emit_mk2)
 * Ghidra: void FUN_003ce940(int *result, long tcb, void *msg, int depth)
 * Decode the single message word in `msg` (kind-1/5 check) and emit it as a
 * tagged IPC message-register record with tag "MK"; on parse error leave
 * the result word set, else clear it. Confidence: medium. */
void cL4_ipc_emit_mk2(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_one(result, tcb, (unsigned long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, "MK", 2, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003ce99c @ 0x003ce99c   (est. cL4_ipc_emit_mn)
 * Ghidra: void FUN_003ce99c(int *result, long tcb, void *msg, int depth)
 * Decode the single message word in `msg` (kind-1/5 check) and emit it as a
 * tagged IPC message-register record with tag "MN"; on parse error leave
 * the result word set, else clear it. Confidence: medium. */
void cL4_ipc_emit_mn(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_one(result, tcb, (unsigned long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, "MN", 2, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003ce9f8 @ 0x003ce9f8   (est. cL4_ipc_emit_mj2)
 * Ghidra: void FUN_003ce9f8(int *result, long tcb, void *msg, int depth)
 * Decode the single message word in `msg` (kind-1/5 check) and emit it as a
 * tagged IPC message-register record with tag "MJ"; on parse error leave
 * the result word set, else clear it. Confidence: medium. */
void cL4_ipc_emit_mj2(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_one(result, tcb, (unsigned long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, "MJ", 2, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003cec20 @ 0x003cec20   (est. cL4_ipc_emit_mz)
 * Ghidra: void FUN_003cec20(int *result, long tcb, void *msg, int depth)
 * Decode the single message word in `msg` (kind-1/5 check) and emit it as a
 * tagged IPC message-register record with tag "Mz"; on parse error leave
 * the result word set, else clear it. Confidence: medium. */
void cL4_ipc_emit_mz(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_one(result, tcb, (unsigned long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, "Mz", 2, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003cf160 @ 0x003cf160   (est. cL4_ipc_emit_yk)
 * Ghidra: void FUN_003cf160(int *result, long tcb, void *msg, int depth)
 * Decode the single message word in `msg` (kind-1/5 check) and emit it as a
 * tagged IPC message-register record with tag "Yk"; on parse error leave
 * the result word set, else clear it. Confidence: medium. */
void cL4_ipc_emit_yk(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_one(result, tcb, (unsigned long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, "Yk", 2, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003cf28c @ 0x003cf28c   (est. cL4_ipc_emit_yt)
 * Ghidra: void FUN_003cf28c(int *result, long tcb, void *msg, int depth)
 * Decode the single message word in `msg` (kind-1/5 check) and emit it as a
 * tagged IPC message-register record with tag "Yt"; on parse error leave
 * the result word set, else clear it. Confidence: medium. */
void cL4_ipc_emit_yt(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_one(result, tcb, (unsigned long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, "Yt", 2, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003d003c @ 0x003d003c   (est. cL4_ipc_emit_yg)
 * Ghidra: void FUN_003d003c(int *result, long tcb, void *msg, int depth)
 * Decode the single message word in `msg` (kind-1/5 check) and emit it as a
 * tagged IPC message-register record with tag "Yg"; on parse error leave
 * the result word set, else clear it. Confidence: medium. */
void cL4_ipc_emit_yg(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_one(result, tcb, (unsigned long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, "Yg", 2, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003cceac @ 0x003cceac   (est. cL4_ipc_emit_fp)
 * Ghidra: void FUN_003cceac(int *result, long tcb, void *msg, int depth)
 * Decode the argument LIST in `msg` (each word via cL4_arg_decode) and emit a
 * tagged IPC record with tag "fp" carrying 2 words; clear result on
 * success. Confidence: medium. */
void cL4_ipc_emit_fp(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_args(result, tcb, (unsigned long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, "fp", 2, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003cd4e0 @ 0x003cd4e0   (est. cL4_ipc_emit_yk2)
 * Ghidra: void FUN_003cd4e0(int *result, long tcb, void *msg, int depth)
 * Decode the argument LIST in `msg` (each word via cL4_arg_decode) and emit a
 * tagged IPC record with tag "YK" carrying 2 words; clear result on
 * success. Confidence: medium. */
void cL4_ipc_emit_yk2(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_args(result, tcb, (unsigned long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, "YK", 2, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003ce888 @ 0x003ce888   (est. cL4_ipc_emit_mm)
 * Ghidra: void FUN_003ce888(int *result, long tcb, void *msg, int depth)
 * Decode the argument LIST in `msg` (each word via cL4_arg_decode) and emit a
 * tagged IPC record with tag "MM" carrying 2 words; clear result on
 * success. Confidence: medium. */
void cL4_ipc_emit_mm(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_args(result, tcb, (unsigned long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, "MM", 2, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003cea54 @ 0x003cea54   (est. cL4_ipc_emit_wz)
 * Ghidra: void FUN_003cea54(int *result, long tcb, void *msg, int depth)
 * Decode the argument LIST in `msg` (each word via cL4_arg_decode) and emit a
 * tagged IPC record with tag "WZ" carrying 2 words; clear result on
 * success. Confidence: medium. */
void cL4_ipc_emit_wz(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_args(result, tcb, (unsigned long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, "WZ", 2, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003ceab0 @ 0x003ceab0   (est. cL4_ipc_emit_wz2)
 * Ghidra: void FUN_003ceab0(int *result, long tcb, void *msg, int depth)
 * Decode the argument LIST in `msg` (each word via cL4_arg_decode) and emit a
 * tagged IPC record with tag "Wz" carrying 2 words; clear result on
 * success. Confidence: medium. */
void cL4_ipc_emit_wz2(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_args(result, tcb, (unsigned long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, "Wz", 2, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003cd5bc @ 0x003cd5bc   (est. cL4_ipc_emit_woy)
 * Ghidra: void FUN_003cd5bc(int *result, long tcb, void *msg, int depth)
 * Decode the argument LIST in `msg` (each word via cL4_arg_decode) and emit a
 * tagged IPC record with tag "WOy" carrying 3 words; clear result on
 * success. Confidence: medium. */
void cL4_ipc_emit_woy(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_args(result, tcb, (unsigned long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, "WOy", 3, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003cd674 @ 0x003cd674   (est. cL4_ipc_emit_wor)
 * Ghidra: void FUN_003cd674(int *result, long tcb, void *msg, int depth)
 * Decode the argument LIST in `msg` (each word via cL4_arg_decode) and emit a
 * tagged IPC record with tag "WOr" carrying 3 words; clear result on
 * success. Confidence: medium. */
void cL4_ipc_emit_wor(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_args(result, tcb, (unsigned long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, "WOr", 3, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003cd6d0 @ 0x003cd6d0   (est. cL4_ipc_emit_wos)
 * Ghidra: void FUN_003cd6d0(int *result, long tcb, void *msg, int depth)
 * Decode the argument LIST in `msg` (each word via cL4_arg_decode) and emit a
 * tagged IPC record with tag "WOs" carrying 3 words; clear result on
 * success. Confidence: medium. */
void cL4_ipc_emit_wos(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_args(result, tcb, (unsigned long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, "WOs", 3, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003cd72c @ 0x003cd72c   (est. cL4_ipc_emit_wob)
 * Ghidra: void FUN_003cd72c(int *result, long tcb, void *msg, int depth)
 * Decode the argument LIST in `msg` (each word via cL4_arg_decode) and emit a
 * tagged IPC record with tag "WOb" carrying 3 words; clear result on
 * success. Confidence: medium. */
void cL4_ipc_emit_wob(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_args(result, tcb, (unsigned long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, "WOb", 3, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003cd788 @ 0x003cd788   (est. cL4_ipc_emit_woc)
 * Ghidra: void FUN_003cd788(int *result, long tcb, void *msg, int depth)
 * Decode the argument LIST in `msg` (each word via cL4_arg_decode) and emit a
 * tagged IPC record with tag "WOc" carrying 3 words; clear result on
 * success. Confidence: medium. */
void cL4_ipc_emit_woc(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_args(result, tcb, (unsigned long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, "WOc", 3, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003cd7e4 @ 0x003cd7e4   (est. cL4_ipc_emit_wod)
 * Ghidra: void FUN_003cd7e4(int *result, long tcb, void *msg, int depth)
 * Decode the argument LIST in `msg` (each word via cL4_arg_decode) and emit a
 * tagged IPC record with tag "WOd" carrying 3 words; clear result on
 * success. Confidence: medium. */
void cL4_ipc_emit_wod(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_args(result, tcb, (unsigned long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, "WOd", 3, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003cd840 @ 0x003cd840   (est. cL4_ipc_emit_wof)
 * Ghidra: void FUN_003cd840(int *result, long tcb, void *msg, int depth)
 * Decode the argument LIST in `msg` (each word via cL4_arg_decode) and emit a
 * tagged IPC record with tag "WOf" carrying 3 words; clear result on
 * success. Confidence: medium. */
void cL4_ipc_emit_wof(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_args(result, tcb, (unsigned long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, "WOf", 3, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003cd89c @ 0x003cd89c   (est. cL4_ipc_emit_woh)
 * Ghidra: void FUN_003cd89c(int *result, long tcb, void *msg, int depth)
 * Decode the argument LIST in `msg` (each word via cL4_arg_decode) and emit a
 * tagged IPC record with tag "WOh" carrying 3 words; clear result on
 * success. Confidence: medium. */
void cL4_ipc_emit_woh(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_args(result, tcb, (unsigned long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, "WOh", 3, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003cfa08 @ 0x003cfa08   (est. cL4_ipc_emit_wog)
 * Ghidra: void FUN_003cfa08(int *result, long tcb, void *msg, int depth)
 * Decode the argument LIST in `msg` (each word via cL4_arg_decode) and emit a
 * tagged IPC record with tag "WOg" carrying 3 words; clear result on
 * success. Confidence: medium. */
void cL4_ipc_emit_wog(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_args(result, tcb, (unsigned long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, "WOg", 3, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003cfa64 @ 0x003cfa64   (est. cL4_ipc_emit_wob2)
 * Ghidra: void FUN_003cfa64(int *result, long tcb, void *msg, int depth)
 * Decode the argument LIST in `msg` (each word via cL4_arg_decode) and emit a
 * tagged IPC record with tag "WOB" carrying 3 words; clear result on
 * success. Confidence: medium. */
void cL4_ipc_emit_wob2(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_args(result, tcb, (unsigned long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, "WOB", 3, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003cfac0 @ 0x003cfac0   (est. cL4_ipc_emit_woc2)
 * Ghidra: void FUN_003cfac0(int *result, long tcb, void *msg, int depth)
 * Decode the argument LIST in `msg` (each word via cL4_arg_decode) and emit a
 * tagged IPC record with tag "WOC" carrying 3 words; clear result on
 * success. Confidence: medium. */
void cL4_ipc_emit_woc2(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_args(result, tcb, (unsigned long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, "WOC", 3, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003cfb1c @ 0x003cfb1c   (est. cL4_ipc_emit_wod2)
 * Ghidra: void FUN_003cfb1c(int *result, long tcb, void *msg, int depth)
 * Decode the argument LIST in `msg` (each word via cL4_arg_decode) and emit a
 * tagged IPC record with tag "WOD" carrying 3 words; clear result on
 * success. Confidence: medium. */
void cL4_ipc_emit_wod2(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_args(result, tcb, (unsigned long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, "WOD", 3, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003cfb78 @ 0x003cfb78   (est. cL4_ipc_emit_wof2)
 * Ghidra: void FUN_003cfb78(int *result, long tcb, void *msg, int depth)
 * Decode the argument LIST in `msg` (each word via cL4_arg_decode) and emit a
 * tagged IPC record with tag "WOF" carrying 3 words; clear result on
 * success. Confidence: medium. */
void cL4_ipc_emit_wof2(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_args(result, tcb, (unsigned long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, "WOF", 3, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003cfbd4 @ 0x003cfbd4   (est. cL4_ipc_emit_woh2)
 * Ghidra: void FUN_003cfbd4(int *result, long tcb, void *msg, int depth)
 * Decode the argument LIST in `msg` (each word via cL4_arg_decode) and emit a
 * tagged IPC record with tag "WOH" carrying 3 words; clear result on
 * success. Confidence: medium. */
void cL4_ipc_emit_woh2(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_args(result, tcb, (unsigned long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, "WOH", 3, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003cd098 @ 0x003cd098   (est. cL4_ipc_emit_tl)
 * Ghidra: void FUN_003cd098(int *result, long tcb, long *msg, int depth)
 * Read the first word of `msg` (deref through kind-5 array), decode it via
 * cL4_arg_decode, and emit tag "TL" (3 words) on success. Confidence:
 * medium. */
void cL4_ipc_emit_tl(int *result, unsigned long tcb, unsigned long *msg, unsigned long depth)
{
    unsigned long word;
    if (1 < *(unsigned char *)((long)msg + 0x12) - 1) {
        if ((*(unsigned char *)((long)msg + 0x12) != 5) || ((int)msg[1] == 0)) {
            word = 0; goto emit;
        }
        msg = (unsigned long*)*msg;
    }
    word = *msg;
emit:
    cL4_arg_decode(result, tcb, word, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, "TL", 3, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003cdb7c @ 0x003cdb7c   (est. cL4_ipc_emit_mxm)
 * Ghidra: void FUN_003cdb7c(int *result, long tcb, long *msg, int depth)
 * Read the first word of `msg` (deref through kind-5 array), decode it via
 * cL4_arg_decode, and emit tag "MXM" (3 words) on success. Confidence:
 * medium. */
void cL4_ipc_emit_mxm(int *result, unsigned long tcb, unsigned long *msg, unsigned long depth)
{
    unsigned long word;
    if (1 < *(unsigned char *)((long)msg + 0x12) - 1) {
        if ((*(unsigned char *)((long)msg + 0x12) != 5) || ((int)msg[1] == 0)) {
            word = 0; goto emit;
        }
        msg = (unsigned long*)*msg;
    }
    word = *msg;
emit:
    cL4_arg_decode(result, tcb, word, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, "MXM", 3, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003cdc10 @ 0x003cdc10   (est. cL4_ipc_emit_mxe)
 * Ghidra: void FUN_003cdc10(int *result, long tcb, long *msg, int depth)
 * Read the first word of `msg` (deref through kind-5 array), decode it via
 * cL4_arg_decode, and emit tag "MXE" (3 words) on success. Confidence:
 * medium. */
void cL4_ipc_emit_mxe(int *result, unsigned long tcb, unsigned long *msg, unsigned long depth)
{
    unsigned long word;
    if (1 < *(unsigned char *)((long)msg + 0x12) - 1) {
        if ((*(unsigned char *)((long)msg + 0x12) != 5) || ((int)msg[1] == 0)) {
            word = 0; goto emit;
        }
        msg = (unsigned long*)*msg;
    }
    word = *msg;
emit:
    cL4_arg_decode(result, tcb, word, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, "MXE", 3, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003ce7f4 @ 0x003ce7f4   (est. cL4_ipc_emit_qo)
 * Ghidra: void FUN_003ce7f4(int *result, long tcb, long *msg, int depth)
 * Read the first word of `msg` (deref through kind-5 array), decode it via
 * cL4_arg_decode, and emit tag "QO" (2 words) on success. Confidence:
 * medium. */
void cL4_ipc_emit_qo(int *result, unsigned long tcb, unsigned long *msg, unsigned long depth)
{
    unsigned long word;
    if (1 < *(unsigned char *)((long)msg + 0x12) - 1) {
        if ((*(unsigned char *)((long)msg + 0x12) != 5) || ((int)msg[1] == 0)) {
            word = 0; goto emit;
        }
        msg = (unsigned long*)*msg;
    }
    word = *msg;
emit:
    cL4_arg_decode(result, tcb, word, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, "QO", 2, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003cf418 @ 0x003cf418   (est. cL4_ipc_emit_mq2)
 * Ghidra: void FUN_003cf418(int *result, long tcb, long *msg, int depth)
 * Read the first word of `msg` (deref through kind-5 array), decode it via
 * cL4_arg_decode, and emit tag "Mq" (2 words) on success. Confidence:
 * medium. */
void cL4_ipc_emit_mq2(int *result, unsigned long tcb, unsigned long *msg, unsigned long depth)
{
    unsigned long word;
    if (1 < *(unsigned char *)((long)msg + 0x12) - 1) {
        if ((*(unsigned char *)((long)msg + 0x12) != 5) || ((int)msg[1] == 0)) {
            word = 0; goto emit;
        }
        msg = (unsigned long*)*msg;
    }
    word = *msg;
emit:
    cL4_arg_decode(result, tcb, word, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, "Mq", 2, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}
/* 003d01ac @ 0x3d01ac   (est. cL4_msg_args)
 * Ghidra: void FUN_003d01ac(int *result, undefined8 tcb, long *msg, undefined8 depth)
 * Decode every argument word in the message descriptor `msg` by calling
 * cL4_arg_decode for each. The descriptor encodes its shape in the byte at
 * +0x12 (kind 1 = one inline word; kind 2 = two words; kind 5 = a heap array
 * whose element count is at msg[1]). Iterates the array bounds and stops on
 * the first decode error. Confidence: high (structural). */
void cL4_msg_args(int *result, unsigned long tcb, unsigned long *msg, unsigned long depth)
{
    unsigned char kind = *(unsigned char *)((long)msg + 0x12);
    unsigned long *cur = msg, *end;

    if (kind - 1 < 2) {
        if (kind == 1)      end = msg + 1;
        else if (kind == 2) end = msg + 2;
        else if (kind == 5) end = (unsigned long*)*msg;
        else                end = 0;
    } else {
        if (kind != 5) { cur = 0; end = 0; }
        else           { end = (unsigned long*)*msg; cur = end; }
        end = end + *(unsigned int *)(msg + 1);
    }
    do {
        if (cur == end) {
            *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
            return;
        }
        cL4_arg_decode(result, tcb, *cur, depth);
        cur = cur + 1;
    } while (*result == 0);
}

/* 003d11d4 @ 0x3d11d4   (est. cL4_msg_one)
 * Ghidra: void FUN_003d11d4(undefined4 *result, undefined8 tcb, long *msg)
 * Decode a single required argument from `msg` (kind 1, or a kind-5 array of
 * exactly one element). If the descriptor is neither, set result to error 10
 * with the descriptor pointer and code 0x142. Confidence: high. */
void cL4_msg_one(int *result, unsigned long tcb, unsigned long *msg, unsigned long depth)
{
    if (*(char *)((long)msg + 0x12) != 1) {
        if ((*(char *)((long)msg + 0x12) != 5) || ((int)msg[1] != 1)) {
            *result = 10;
            *(unsigned long **)(result + 2) = msg;
            result[4] = 0x142;
            return;
        }
        msg = (unsigned long*)*msg;
    }
    cL4_arg_decode(result, tcb, *msg, 0);
}

/* 003d1218 @ 0x3d1218   (est. cL4_msg_three)
 * Ghidra: void FUN_003d1218(undefined4 *result, undefined8 tcb, long *msg, undefined8 depth)
 * Decode a message descriptor that may carry up to three arguments. A
 * descriptor whose embedded type word (msg[2]) is 0xf4 is dereferenced first.
 * Uses the "Swift-if-magic" decoder cL4_msg_decode; if it reports a match,
 * clear the result; otherwise fall back to cL4_msg_args. Confidence: medium. */
void cL4_msg_three(int *result, unsigned long tcb, unsigned long *msg, unsigned long depth)
{
    if ((short)msg[2] == 0xf4) {
        if (1 < *(unsigned char *)((long)msg + 0x12) - 1) {
            if ((*(unsigned char *)((long)msg + 0x12) != 5) || ((int)msg[1] == 0)) {
                msg = 0; goto decode;
            }
            msg = (unsigned long*)*msg;
        }
        msg = (unsigned long*)*msg;
    }
decode:
    if (cL4_msg_decode(tcb, msg)) {
        *result = 0; result[2] = 0; result[4] = 0;
        return;
    }
    cL4_msg_args(result, tcb, msg, depth);
}

/* 003d174c @ 0x3d174c   (est. cL4_msg_dispatch2)
 * Ghidra: void FUN_003d174c(int *result, long tcb, long msg, undefined8 tag, undefined8 count, int depth)
 * Decode the argument list in `msg`, then dispatch on the message's type word
 * (msg+0x10): for type 0xe8 emit a tag "i", for type 0x10b emit "v", each
 * followed by the caller's `tag`/`count` record. Any other type returns error
 * code 0x2ce with err=6. Confidence: medium (tag identity via DAT refs). */
void cL4_msg_dispatch2(int *result, unsigned long tcb, unsigned long msg, unsigned long tag,
                       unsigned long count, unsigned long depth)
{
    const char *sel; int err, code;
    cL4_msg_args(result, tcb, (unsigned long*)msg, depth + 1);
    if (*result != 0) return;
    if (*(short *)(msg + 0x10) == 0xe8) {
        sel = "i";
    } else if (*(short *)(msg + 0x10) != 0x10b) {
        code = 0x2ce; err = 6; goto done;
    } else {
        sel = "v";
    }
    cL4_mr_emit_tag(tcb + 0x2140, sel, 1, *(unsigned long *)(tcb + 0x2150));
    cL4_mr_emit_tag(tcb + 0x2140, (const void*)tag, count, *(unsigned long *)(tcb + 0x2150));
    err = 0; msg = 0; code = 0;
done:
    *result = err;
    *(unsigned long *)(result + 2) = msg;
    result[4] = code;
}

/* 003d05e0 @ 0x3d05e0   (est. cL4_mr_emit_num)
 * Ghidra: void FUN_003d05e0(long tcb, long n)
 * Emit a numeric-marker field: if n==0 emit a lone "_"; otherwise emit a
 * "_"-terminated value record for n-1 via cL4_mr_emit_val2. Confidence: high. */
void cL4_mr_emit_num(unsigned long tcb, long n)
{
    char c;
    if (n == 0) {
        c = '_';
        cL4_mr_emit_byte(tcb + 0x2140, &c, *(unsigned long *)(tcb + 0x2150));
    } else {
        cL4_mr_emit_val2(tcb + 0x2140, n - 1, *(unsigned long *)(tcb + 0x2150));
        c = '_';
        cL4_mr_emit_byte(tcb + 0x2140, &c, *(unsigned long *)(tcb + 0x2150));
    }
}

/* 003d0358 @ 0x3d0358   (est. cL4_fmt_begin)
 * Ghidra: undefined8 FUN_003d0358(long tcb, undefined8 msg, undefined1 (*out)[16], undefined8 depth)
 * Begin an output record: build a format descriptor for (tcb,msg) into `out`;
 * if its kind is < 0x1a emit a single base-26 letter tag 'A'+kind; otherwise
 * emit an index into the numeric table. Returns 1 once the record is flushed
 * (or the precheck says skip), 0 when it must be committed by the caller.
 * Confidence: medium (letter-tag encoding inferred from 0x1a bound + 'A'). */
unsigned long cL4_fmt_begin(unsigned long tcb, unsigned long msg, unsigned char (*out)[16], unsigned long depth)
{
    unsigned char desc[16], letter[3]; unsigned long r;
    unsigned int kind;

    if (!(cL4_msg_decode(tcb, (unsigned long*)msg) & 1)) {
        /* build output descriptor into *out */
        memcpy(desc, cL4_fmt_build(tcb, msg, depth), 16);
        memcpy(*out, desc, 16);
        kind = cL4_fmt_kind(tcb, out);
        if ((int)kind < 0) return 0;
        if (kind < 0x1a) {
            letter[0] = (char)kind + 'A';
            r = cL4_fmt_emit_letter((unsigned long*)(tcb + 0x2180), tcb, letter, 1, 0);
            if (!(r & 1)) {
                letter[2] = 'A';
                cL4_mr_emit_byte(tcb + 0x2140, letter + 2, *(unsigned long *)(tcb + 0x2150));
                cL4_mr_emit_tag(tcb + 0x2140, letter, 1, *(unsigned long *)(tcb + 0x2150));
            }
        } else {
            letter[1] = 'A';
            cL4_mr_emit_byte(tcb + 0x2140, letter + 1, *(unsigned long *)(tcb + 0x2150));
            cL4_mr_emit_num(tcb, kind - 0x1a);
        }
    }
    return 1;
}
/* 003d0458 @ 0x3d0458   (est. cL4_msg_decode)
 * Ghidra: byte FUN_003d0458(long tcb, long *msg)
 * Detect and decode a "Swift"-tagged message descriptor. Accepts only the
 * message type words 0x19 / 0x3f / 0xe7 / 0xbf. When the descriptor's payload
 * begins with the little-endian magic "Swift" (0x66697753) followed by 't'
 * and its element type is 0x67, it formats the nested (ptr,len) value into a
 * buffer and emits it as an identifier-letter via cL4_fmt_emit_letter, then
 * returns 1 (message fully consumed). Otherwise returns 0. A failure past the
 * magic hits a SoftwareBreakpoint (0x3d05e0) trap. Confidence: high
 * (magic string is explicit). */
unsigned char cL4_msg_decode(unsigned long tcb, unsigned long *msg)
{
    unsigned short type = *(unsigned short *)(msg + 2);
    unsigned char kind; unsigned long *cur; unsigned long *payload;
    unsigned char buf[16]; char byte; unsigned long r;
    int magic;

    if (type < 0xbf) {
        if ((type != 0x19) && (type != 0x3f)) return 0;
    } else if ((type != 0xe7) && (type != 0xbf)) {
        return 0;
    }

    kind = *(unsigned char *)((long)msg + 0x12);
    cur = msg;
    if (kind - 1 < 2) {
        payload = (unsigned long*)*cur;
    } else if ((kind == 5) && ((int)msg[1] != 0)) {
        cur = (unsigned long*)*msg;
        payload = (unsigned long*)*cur;
    } else {
        payload = 0;
    }

    magic = (int)*payload;
    if ((*(short *)(payload + 2) == 0xa3) && (payload[1] == 5) &&
        (magic == 0x66697753) && (((char *)&magic)[1] == 't')) {
        /* "Swift" magic — nested value */
        if (kind == 5) {
            if (*(short *)(*(unsigned long *)(*msg + 8) + 0x10) == 0x67) {
                cur = (unsigned long*)*msg;
                goto fmt;
            }
        } else if (*(short *)(msg[1] + 0x10) == 0x67) {
            goto fmt;
        }
    }
    return 0;
fmt:
    cL4_fmt_make(buf, *(unsigned long*)cur[1], ((unsigned long*)cur[1])[1], 1);
    if (buf[0] != 1) return buf[0];
    r = cL4_fmt_emit_letter((unsigned long*)(tcb + 0x2180), tcb, buf, ((unsigned long*)cur[1])[1], 1);
    if ((r & 1) != 0) return 1;
    byte = 'S';
    cL4_mr_emit_byte(tcb + 0x2140, &byte, *(unsigned long *)(tcb + 0x2150));
    if ((buf[0] & 1) != 0) {
        cL4_mr_emit_tag(tcb + 0x2140, buf, ((unsigned long*)cur[1])[1], *(unsigned long *)(tcb + 0x2150));
        return 1;
    }
    /* WARNING: does not return (SoftwareBreakpoint 0x3d05e0) */
    return 0;
}

/* 003d0650 @ 0x3d0650   (est. cL4_fmt_emit_letter)
 * Ghidra: undefined8 FUN_003d0650(ulong *state, long tcb, undefined8 text, ulong len, uint flag)
 * Attempt to append `text`/`len` to the in-progress output record without
 * re-emission. `state` is the record cursor {base, count, tag, flag}; tcb
 * carries the outbound depth (tcb+0x2148) and object (tcb+0x2140). When the
 * pending buffer already holds `len` ASCII digits, the new text is fused;
 * otherwise the buffered numeric field is flushed as a "_"-terminated value
 * and the letter/flag is re-emitted. Returns 1 when the record is flushed,
 * 0 when it must be committed. Confidence: medium (fuse/flush logic inferred
 * from the digit-buffer walk). */
unsigned long cL4_fmt_emit_letter(unsigned long *state, unsigned long tcb, unsigned char *text,
                                  unsigned long len, unsigned int flag)
{
    unsigned long n = *(unsigned int *)(tcb + 0x2148);
    unsigned long ndigits = state[2];
    unsigned long base = *state, count = state[1], fused;
    long p; unsigned long k; char c; unsigned long r;

    if (ndigits - 1 < 0x7ff) {
        unsigned long a = *state, b = state[1];
        if ((b + a != n) || ((unsigned char)state[3] != flag)) goto fail;
        p = 0;
        if (b <= n) p = n - b;
        p = *(long *)(tcb + 0x2140) + p;
        if (n <= b) b = n;
        if (b == 0) {
            if (len == 0) goto done;
        } else {
            k = 0;
            while (9 >= *(unsigned char *)(p + k) - 0x30) { k = k + 1; if (b == k) break; }
            k = (k <= b) ? k : b;
            if (b - k == len) {
                if (b <= k) goto done;
                r = cL4_memcmp((void*)(p + k), text, len);
                if (((flag & 1) != 0) || (r == 0)) {
                    if (r != 0) goto fail;
                    goto done;
                }
                goto flush;
            }
        }
        if ((flag & 1) == 0) {
flush:
            *state = n;
            state[2] = 1;
            *(unsigned int *)(tcb + 0x2148) = (unsigned int)n - 1;
            c = *(char *)(p + b + -1) + ' ';
            cL4_mr_emit_byte(tcb + 0x2140, &c, *(unsigned long *)(tcb + 0x2150));
            cL4_mr_emit_tag(tcb + 0x2140, text, len, *(unsigned long *)(tcb + 0x2150));
            state[1] = 1;
            return 1;
        }
    }
fail:
    *state = n + 1;
    state[1] = len;
    state[2] = 1;
    *(unsigned char *)(state + 3) = (unsigned char)flag;
    return 0;
done:
    ndigits = ndigits + 1;
    state[2] = ndigits;
    *(int *)(tcb + 0x2148) = (int)*state;
    cL4_mr_emit_val2(tcb + 0x2140, ndigits, *(unsigned long *)(tcb + 0x2150));
    cL4_mr_emit_tag(tcb + 0x2140, text, len, *(unsigned long *)(tcb + 0x2150));
    state[1] = (unsigned long)*(unsigned int *)(tcb + 0x2148) - *state;
    return 1;
}

/* 003d0280 @ 0x3d0280   (est. cL4_msg_arg_index)
 * Ghidra: void FUN_003d0280(undefined4 *result, undefined8 tcb, undefined8 *msg, ulong idx, undefined8 depth)
 * Decode the argument at index `idx` of the message descriptor `msg`. When
 * idx is within bounds, the descriptor is dereferenced through its kind and
 * that element is decoded with cL4_arg_decode; otherwise the result is
 * cleared (empty slot). Confidence: high (structural). */
void cL4_msg_arg_index(int *result, unsigned long tcb, unsigned long *msg, unsigned long idx, unsigned long depth)
{
    unsigned char kind = *(unsigned char *)((long)msg + 0x12);
    unsigned long n = (unsigned long)kind;
    unsigned int uk = kind;

    if (uk != 1) {
        if (uk == 5) n = (unsigned long)*(unsigned int *)(msg + 1);
        else if (kind != 2) goto clear;
        else n = 2;
    }
    if ((idx & 0xffffffff) < n) {
        if (1 < uk - 1) msg = (unsigned long*)*msg;
        cL4_arg_decode(result, tcb, msg[idx & 0xffffffff], depth);
        return;
    }
clear:
    *result = 0; result[2] = 0; result[4] = 0;
}

/* 003d02dc @ 0x3d02dc   (est. cL4_msg_arg_kind_dispatch)
 * Ghidra: void FUN_003d02dc(undefined4 *result, undefined8 tcb, long msg, int depth)
 * Dispatch a message whose type word (msg+0x10) is one of 0x1b/0x1c/0x30-0x33
 * to the matching kind-specific arg decoder; any other type clears the
 * result. Confidence: high (dispatch table explicit). */
void cL4_msg_arg_kind_dispatch(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    unsigned short t = *(unsigned short *)(msg + 0x10);
    if (t < 0x31) {
        if (t == 0x1b) { cL4_arg_kind1b(tcb, msg, depth + 1); return; }
        if (t == 0x1c) { cL4_arg_kind1c(tcb, msg, depth + 1); return; }
        if (t == 0x30) { cL4_arg_kind30(tcb, msg, depth + 1); return; }
    } else {
        if (t == 0x31) { cL4_arg_kind31(tcb, msg, depth + 1); return; }
        if (t == 0x32) { cL4_arg_kind32(tcb, msg, depth + 1); return; }
        if (t == 0x33) { cL4_arg_kind33(tcb, msg, depth + 1); return; }
    }
    *result = 0; result[2] = 0; result[4] = 0;
}

/* 003d081c @ 0x3d081c   (est. cL4_msg_args_reverse)
 * Ghidra: void FUN_003d081c(int *result, undefined8 tcb, long msg, undefined8 depth)
 * Decode the message's arguments in REVERSE order (index n-1 down to 0) via
 * cL4_msg_arg_index, then clear the result. Confidence: high (loop direction
 * explicit). */
void cL4_msg_args_reverse(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    unsigned char kind = *(unsigned char *)(msg + 0x12);
    unsigned long n, i; long neg;

    if (kind != 1) {
        if (kind == 5) {
            n = (unsigned long)*(unsigned int *)(msg + 8);
            if (*(unsigned int *)(msg + 8) == 0) goto clear;
        } else {
            if (kind != 2) goto clear;
            n = 2;
        }
    } else {
        n = 1;
    }
    neg = -(long)n;
    i = (int)n;
    do {
        i = i - 1;
        cL4_msg_arg_index(result, tcb, (unsigned long*)msg, i, depth);
        if (*result != 0) return;
        neg = neg + 1;
    } while (neg != -1);
clear:
    *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
}
/* 003cccf4 @ 0x3cccf4   (est. cL4_ipc_emit_w)
 * Ghidra: void FUN_003cccf4(undefined8 result, long *msg, int depth)
 * Read the first word of the message descriptor, then dispatch it through the
 * tagged emitter cL4_msg_dispatch2 with tag "w". The decompile drops/reorders
 * the tcb/msg args of the FUN_003d174c call (register-arg artifact common in
 * this region), so the exact tcb binding is low confidence; the intent is a
 * single-tagged emit of the first argument. */
void cL4_ipc_emit_w(int *result, unsigned long msg, unsigned long depth)
{
    unsigned long first;
    if (1 < *(unsigned char *)((long)msg + 0x12) - 1) {
        if ((*(unsigned char *)((long)msg + 0x12) != 5) || ((int)*(unsigned long *)msg == 0)) {
            first = 0; goto d;
        }
        msg = *(unsigned long *)msg;
    }
    first = *(unsigned long *)msg;
d:
    cL4_msg_dispatch2(result, 0, first, (unsigned long)"w", 1, depth + 1);
}

/* 003ccf64 @ 0x3ccf64   (est. cL4_ipc_emit_tt)
 * Ghidra: void FUN_003ccf64(int *result, long tcb, void *msg, int depth)
 * Decode a single message word and emit two records: tag "TT" (2 words) then
 * tag "I" (1 word). Confidence: medium. */
void cL4_ipc_emit_tt(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_one(result, tcb, (unsigned long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, "TT", 2, *(unsigned long *)(tcb + 0x2150));
        cL4_mr_emit_tag(tcb + 0x2140, "I", 1, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003cd12c @ 0x3cd12c   (est. cL4_ipc_emit_tn)
 * Ghidra: void FUN_003cd12c(int *result, long tcb, long *msg, int depth)
 * Decode up to three arguments: first via cL4_arg_decode, second via
 * cL4_arg_decode, third via cL4_msg_three, then emit tag "Tn" (3 words).
 * Confidence: medium. */
void cL4_ipc_emit_tn(int *result, unsigned long tcb, unsigned long *msg, unsigned long depth)
{
    unsigned long a0, a1, a2; unsigned long *cur = msg;
    if (1 < *(unsigned char *)((long)msg + 0x12) - 1) {
        if ((*(unsigned char *)((long)msg + 0x12) != 5) || ((int)msg[1] == 0)) { a0 = 0; goto l1; }
        cur = (unsigned long*)*msg;
    }
    a0 = *cur;
l1:
    cL4_arg_decode(result, tcb, a0, depth + 1);
    if (*result != 0) return;
    cur = msg;
    if (*(char *)((long)msg + 0x12) != 2) {
        if ((*(char *)((long)msg + 0x12) != 5) || (*(unsigned int *)(msg + 1) < 2)) { a1 = 0; goto l2; }
        cur = (unsigned long*)*msg;
    }
    a1 = cur[1];
l2:
    cL4_arg_decode(result, tcb, a1, depth + 1);
    if (*result == 0) {
        if ((*(char *)((long)msg + 0x12) == 5) && (2 < *(unsigned int *)(msg + 1))) a2 = *(unsigned long *)(*msg + 0x10);
        else a2 = 0;
        cL4_msg_three(result, tcb, (unsigned long*)a2, depth + 1);
        if (*result == 0) {
            cL4_mr_emit_tag(tcb + 0x2140, "Tn", 3, *(unsigned long *)(tcb + 0x2150));
            *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
        }
    }
}

/* 003cd260 @ 0x3cd260   (est. cL4_ipc_emit_tN)
 * Ghidra: void FUN_003cd260(int *result, long tcb, long *msg, int depth)
 * Same shape as cL4_ipc_emit_tn (three args) but emits tag "TN".
 * Confidence: medium. */
void cL4_ipc_emit_tN(int *result, unsigned long tcb, unsigned long *msg, unsigned long depth)
{
    unsigned long a0, a1, a2; unsigned long *cur = msg;
    if (1 < *(unsigned char *)((long)msg + 0x12) - 1) {
        if ((*(unsigned char *)((long)msg + 0x12) != 5) || ((int)msg[1] == 0)) { a0 = 0; goto l1; }
        cur = (unsigned long*)*msg;
    }
    a0 = *cur;
l1:
    cL4_arg_decode(result, tcb, a0, depth + 1);
    if (*result != 0) return;
    cur = msg;
    if (*(char *)((long)msg + 0x12) != 2) {
        if ((*(char *)((long)msg + 0x12) != 5) || (*(unsigned int *)(msg + 1) < 2)) { a1 = 0; goto l2; }
        cur = (unsigned long*)*msg;
    }
    a1 = cur[1];
l2:
    cL4_arg_decode(result, tcb, a1, depth + 1);
    if (*result == 0) {
        if ((*(char *)((long)msg + 0x12) == 5) && (2 < *(unsigned int *)(msg + 1))) a2 = *(unsigned long *)(*msg + 0x10);
        else a2 = 0;
        cL4_msg_three(result, tcb, (unsigned long*)a2, depth + 1);
        if (*result == 0) {
            cL4_mr_emit_tag(tcb + 0x2140, "TN", 3, *(unsigned long *)(tcb + 0x2150));
            *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
        }
    }
}

/* 003cd394 @ 0x3cd394   (est. cL4_ipc_emit_tb)
 * Ghidra: void FUN_003cd394(int *result, long tcb, long *msg, int depth)
 * Decode first arg via cL4_arg_decode, second via cL4_msg_three, then emit
 * tag "Tb" (3 words). Confidence: medium. */
void cL4_ipc_emit_tb(int *result, unsigned long tcb, unsigned long *msg, unsigned long depth)
{
    unsigned long a0, a1; unsigned long *cur = msg;
    if (1 < *(unsigned char *)((long)msg + 0x12) - 1) {
        if ((*(unsigned char *)((long)msg + 0x12) != 5) || ((int)msg[1] == 0)) { a0 = 0; goto l1; }
        cur = (unsigned long*)*msg;
    }
    a0 = *cur;
l1:
    cL4_arg_decode(result, tcb, a0, depth + 1);
    if (*result != 0) return;
    cur = msg;
    if (*(char *)((long)msg + 0x12) != 2) {
        if ((*(char *)((long)msg + 0x12) != 5) || (*(unsigned int *)(msg + 1) < 2)) { a1 = 0; goto l2; }
        cur = (unsigned long*)*msg;
    }
    a1 = cur[1];
l2:
    cL4_msg_three(result, tcb, (unsigned long*)a1, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, "Tb", 3, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003cd53c @ 0x3cd53c   (est. cL4_ipc_emit_te)
 * Ghidra: void FUN_003cd53c(undefined4 *result, long tcb, undefined8 *msg)
 * Emit tag "Te" (2 words), then the two words pointed to by msg[0]/msg[1],
 * then a "_" terminator (1 word). Confidence: medium. */
void cL4_ipc_emit_te(int *result, unsigned long tcb, unsigned long *msg)
{
    cL4_mr_emit_tag(tcb + 0x2140, "Te", 2, *(unsigned long *)(tcb + 0x2150));
    cL4_mr_emit_tag(tcb + 0x2140, (const void*)msg[0], msg[1], *(unsigned long *)(tcb + 0x2150));
    cL4_mr_emit_tag(tcb + 0x2140, "_", 1, *(unsigned long *)(tcb + 0x2150));
    *result = 0; *(unsigned long *)(result + 2) = 0; result[4] = 0;
}

/* 003cd8f8 @ 0x3cd8f8   (est. cL4_ipc_emit_tv)
 * Ghidra: void FUN_003cd8f8(undefined4 *result, long tcb, undefined8 *msg)
 * Emit tag "Tv" (2 words), then a numeric marker for msg[0]. Confidence: medium. */
void cL4_ipc_emit_tv(int *result, unsigned long tcb, unsigned long *msg)
{
    cL4_mr_emit_tag(tcb + 0x2140, "Tv", 2, *(unsigned long *)(tcb + 0x2150));
    cL4_mr_emit_num(tcb, (long)msg[0]);
    *result = 0; *(unsigned long *)(result + 2) = 0; result[4] = 0;
}

/* 003cd95c @ 0x3cd95c   (est. cL4_ipc_emit_tv_r)
 * Ghidra: void FUN_003cd95c(undefined4 *result, long tcb, undefined8 *msg)
 * Emit tag "Tv" (2 words), a numeric marker for msg[0], then a "r" byte.
 * Confidence: medium. */
void cL4_ipc_emit_tv_r(int *result, unsigned long tcb, unsigned long *msg)
{
    char c = 'r';
    cL4_mr_emit_tag(tcb + 0x2140, "Tv", 2, *(unsigned long *)(tcb + 0x2150));
    cL4_mr_emit_num(tcb, (long)msg[0]);
    cL4_mr_emit_byte(tcb + 0x2140, &c, *(unsigned long *)(tcb + 0x2150));
    *result = 0; *(unsigned long *)(result + 2) = 0; result[4] = 0;
}

/* 003cd9e0 @ 0x3cd9e0   (est. cL4_ipc_emit_list)
 * Ghidra: void FUN_003cd9e0(int *result, long tcb, long *msg, int depth)
 * Decode every argument in `msg` as a list, emitting a "_" separator after
 * the first element, then clear the result. Confidence: high (loop + separator
 * explicit). */
void cL4_ipc_emit_list(int *result, unsigned long tcb, unsigned long *msg, unsigned long depth)
{
    unsigned char kind = *(unsigned char *)((long)msg + 0x12);
    unsigned long *cur = msg, *end; int first = 1; char c;
    if (kind - 1 < 2) {
        if (kind == 1) end = msg + 1;
        else if (kind == 2) end = msg + 2;
        else if (kind == 5) end = (unsigned long*)*msg;
        else end = 0;
    } else {
        if (kind != 5) { cur = 0; end = 0; }
        else { end = (unsigned long*)*msg; cur = end; }
        end = end + *(unsigned int *)(msg + 1);
    }
    if (cur != end) {
        do {
            cL4_arg_decode(result, tcb, *cur, depth + 1);
            if (*result != 0) return;
            if (first) { c = '_'; cL4_mr_emit_byte(tcb + 0x2140, &c, *(unsigned long *)(tcb + 0x2150)); }
            first = 0;
            cur = cur + 1;
        } while (cur != end);
    }
    *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
}

/* 003cdaf4 @ 0x3cdaf4   (est. cL4_ipc_emit_cond_list)
 * Ghidra: void FUN_003cdaf4(int *result, long tcb, long msg, int depth)
 * If the descriptor is a small list (kind 1/2/5) or a kind-5 array with a
 * non-empty count, decode the whole argument list; otherwise emit a single
 * "y" byte. Either way clear the result. Confidence: high (conditional shape
 * explicit). */
void cL4_ipc_emit_cond_list(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    char c = 'y';
    unsigned char kind = *(unsigned char *)(msg + 0x12);
    if ((kind - 1 < 2) || ((kind == 5) && (*(int *)(msg + 8) != 0))) {
        cL4_msg_args(result, tcb, (unsigned long*)msg, depth + 1);
        if (*result != 0) return;
    } else {
        cL4_mr_emit_byte(tcb + 0x2140, &c, *(unsigned long *)(tcb + 0x2150));
    }
    *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
}

/* 003cdca4 @ 0x3cdca4   (est. cL4_ipc_emit_mxx)
 * Ghidra: void FUN_003cdca4(int *result, long tcb, long *msg, int depth)
 * Decode the first arg, then branch on the descriptor kind: for kind 1 (or a
 * kind-5 single element) emit tag "MXX"; otherwise pull the second element,
 * run it through cL4_msg_emit_sym (FUN_003d1ad4) and emit tag "MXY". The tag
 * distinguishes a bare vs. subscripted symbol record. Confidence: medium. */
void cL4_ipc_emit_mxx(int *result, unsigned long tcb, unsigned long *msg, unsigned long depth)
{
    unsigned long a0, second = 0; unsigned long *cur = msg; const char *tag;
    unsigned char c;
    if (1 < *(unsigned char *)((long)msg + 0x12) - 1) {
        if ((*(unsigned char *)((long)msg + 0x12) != 5) || ((int)msg[1] == 0)) { a0 = 0; goto l1; }
        cur = (unsigned long*)*msg;
    }
    a0 = *cur;
l1:
    cL4_arg_decode(result, tcb, a0, depth + 1);
    if (*result != 0) return;
    c = *(unsigned char *)((long)msg + 0x12);
    if (c == 1) { tag = "MXX"; goto emit; }
    if (c == 2) {
        second = msg[1];
    } else if ((c == 5) && ((int)msg[1] != 0)) {
        if ((int)msg[1] == 1) { tag = "MXX"; goto emit; }
        msg = (unsigned long*)*msg;
        second = msg[1];
    }
    cL4_msg_emit_sym(tcb, (unsigned long*)second, 0);
    *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    tag = "MXY";
emit:
    cL4_mr_emit_tag(tcb + 0x2140, tag, 3, *(unsigned long *)(tcb + 0x2150));
    *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
}

/* 003cddac @ 0x3cddac   (est. cL4_ipc_emit_mxa)
 * Ghidra: void FUN_003cddac(int *result, long tcb, long *msg, int depth)
 * Decode the first arg via cL4_msg_one, then decode a nested list (second
 * element) via cL4_ipc_emit_list, then emit tag "MXA" (3 words).
 * Confidence: medium. */
void cL4_ipc_emit_mxa(int *result, unsigned long tcb, unsigned long *msg, unsigned long depth)
{
    unsigned long a0, a1; unsigned long *cur = msg;
    if (1 < *(unsigned char *)((long)msg + 0x12) - 1) {
        if ((*(unsigned char *)((long)msg + 0x12) != 5) || ((int)msg[1] == 0)) { a0 = 0; goto l1; }
        cur = (unsigned long*)*msg;
    }
    a0 = *cur;
l1:
    cL4_msg_one(result, tcb, (unsigned long*)a0, depth + 2);
    if (*result != 0) return;
    cur = msg;
    if (*(char *)((long)msg + 0x12) != 2) {
        if ((*(char *)((long)msg + 0x12) != 5) || (*(unsigned int *)(msg + 1) < 2)) { a1 = 0; goto l2; }
        cur = (unsigned long*)*msg;
    }
    a1 = cur[1];
l2:
    cL4_ipc_emit_list(result, tcb, (unsigned long*)a1, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, "MXA", 3, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003ceb0c @ 0x3ceb0c   (est. cL4_ipc_emit_list_y)
 * Ghidra: void FUN_003ceb0c(int *result, long tcb, undefined8 *msg, int depth)
 * Decode the elements of the descriptor as a list, emitting a "_" separator
 * after each element. Loops `count` times per the descriptor shape (kind 1 = 1,
 * kind 2 = 2, kind 5 = array count). Confidence: medium. */
void cL4_ipc_emit_list_y(int *result, unsigned long tcb, unsigned long *msg, unsigned long depth)
{
    unsigned char kind; unsigned long n, i = 0; char marker;
    kind = *(unsigned char *)((long)msg + 0x12);
    if (kind != 1) {
        if (kind == 5) { n = *(unsigned int *)(msg + 1); if (n == 0) goto clear; }
        else if (kind != 2) goto clear;
        else n = 2;
    } else {
        n = 1;
    }
    do {
        unsigned long word;
        kind = *(unsigned char *)((long)msg + 0x12);
        if (kind == 1) {
            if (n <= i) word = 0;
            else { unsigned long *p = msg; if (1 < kind - 1) p = (unsigned long*)*msg; word = p[i]; }
        } else if (kind == 5) {
            n = *(unsigned int *)(msg + 1);
            word = ((unsigned long*)*msg)[i];
        } else if (kind == 2) {
            n = 2;
            word = msg[i];
        } else {
            word = 0;
        }
        cL4_arg_decode(result, tcb, word, depth + 1);
        if (*result != 0) return;
        marker = '_';
        cL4_mr_emit_byte(tcb + 0x2140, &marker, *(unsigned long *)(tcb + 0x2150));
        i = i + 1;
    } while (n != i);
clear:
    *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
}

/* 003cec7c @ 0x3cec7c   (est. cL4_ipc_emit_tjo)
 * Ghidra: void FUN_003cec7c(int *result, long tcb, undefined8 *msg, int depth)
 * Decode the first three words: word0 and word1 via cL4_arg_decode; if
 * word2's type is 0x2c it is decoded via cL4_arg_kind2c, else left as-is.
 * Emits tag "TJO" (3 words) plus the third element. Confidence: low (arg
 * attribution partly inferred). */
void cL4_ipc_emit_tjo(int *result, unsigned long tcb, unsigned long *msg, unsigned long depth)
{
    unsigned long *pl;
    if (1 < *(unsigned char *)((long)msg + 0x12) - 1) msg = (unsigned long*)*msg;
    cL4_arg_decode(result, tcb, msg[0], depth + 1);
    if ((*result == 0) && (cL4_arg_decode(result, tcb, msg[1], depth + 1), *result == 0)) {
        pl = msg + 2;
        if (*(short *)(*pl + 0x10) == 0x2c) {
            cL4_arg_kind2c(result, tcb, *pl, depth + 1);
            if (*result != 0) return;
            pl = msg + 3;
        }
        cL4_mr_emit_tag(tcb + 0x2140, "TJO", 3, *(unsigned long *)(tcb + 0x2150));
        cL4_arg_decode(result, tcb, *pl, depth + 1);
    }
}
/* 003ced78 @ 0x3ced78   (est. cL4_ipc_emit_tjs)
 * Ghidra: void FUN_003ced78(int *result, long tcb, long *msg, int depth)
 * Walk the argument list, decoding each element until an element of type
 * 0x150 is found (the terminating sentinel). Then emit tag "TJS" (3 words),
 * decode the sentinel and the next three elements, separated by "p", "r", "P"
 * markers. Confidence: medium (sentinel walk + markers). */
void cL4_ipc_emit_tjs(int *result, unsigned long tcb, unsigned long *msg, unsigned long depth)
{
    unsigned long *cur = msg, *end; char c;
    if (1 < *(unsigned char *)((long)msg + 0x12) - 1) {
        if (*(unsigned char *)((long)msg + 0x12) == 5) cur = (unsigned long*)*msg;
        else cur = 0;
    }
    while (1) {
        unsigned char k = *(char *)((long)msg + 0x12);
        if (k == 5) end = (unsigned long*)(*msg + (unsigned long)*(unsigned int *)(msg + 1) * 8);
        else { unsigned long *p = 0; if (k == 1) p = msg + 1; end = msg + 2; if (k != 2) end = p; }
        if ((cur == end) || (*(short *)(*cur + 0x10) == 0x150)) break;
        cur = cur + 1;
        cL4_arg_decode(result, tcb, *cur, depth + 1);
        if (*result != 0) return;
    }
    cL4_mr_emit_tag(tcb + 0x2140, "TJS", 3, *(unsigned long *)(tcb + 0x2150));
    cL4_arg_decode(result, tcb, *cur, depth + 1);
    if (*result != 0) return;
    cL4_arg_decode(result, tcb, cur[1], depth + 1);
    if (*result != 0) return;
    c = 'p'; cL4_mr_emit_byte(tcb + 0x2140, &c, *(unsigned long *)(tcb + 0x2150));
    cL4_arg_decode(result, tcb, cur[2], depth + 1);
    if (*result != 0) return;
    c = 'r'; cL4_mr_emit_byte(tcb + 0x2140, &c, *(unsigned long *)(tcb + 0x2150));
    cL4_arg_decode(result, tcb, cur[3], depth + 1);
    if (*result != 0) return;
    c = 'P'; cL4_mr_emit_byte(tcb + 0x2140, &c, *(unsigned long *)(tcb + 0x2150));
    *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
}

/* 003cef38 @ 0x3cef38   (est. cL4_ipc_emit_wj)
 * Ghidra: void FUN_003cef38(int *result, long tcb, uint *msg, int depth)
 * Walk the argument list until an element of type 0x68 is found, decoding
 * each prior element. Emits tag "WJ" (2 words) plus the sentinel's first byte,
 * the following element (after "p"), and the next (after "r").
 * Confidence: medium. */
void cL4_ipc_emit_wj(int *result, unsigned long tcb, unsigned long *msg, unsigned long depth)
{
    unsigned long *cur = msg, *end; unsigned char k; unsigned long v; char c;
    if (1 < *(unsigned char *)((long)msg + 0x12) - 1) {
        if (*(unsigned char *)((long)msg + 0x12) == 5) cur = (unsigned long*)*msg;
        else cur = 0;
    }
    while (1) {
        k = *(char *)((long)msg + 0x12);
        if (k == 5) end = (unsigned long*)(*(unsigned long*)msg + (unsigned long)msg[2] * 8);
        else { unsigned long *p = 0; if (k == 1) p = msg + 2; end = msg + 4; if (k != 2) end = p; }
        if ((cur == end) || (*(short *)(*cur + 0x10) == 0x68)) break;
        cur = cur + 2;
        cL4_arg_decode(result, tcb, *cur, depth + 1);
        if (*result != 0) return;
    }
    cL4_mr_emit_tag(tcb + 0x2140, "WJ", 2, *(unsigned long *)(tcb + 0x2150));
    { unsigned char b = (unsigned char)**(unsigned long **)cur; cL4_mr_emit_byte(tcb + 0x2140, &b, *(unsigned long *)(tcb + 0x2150)); }
    cL4_arg_decode(result, tcb, *(unsigned long *)(cur + 2), depth + 1);
    if (*result != 0) return;
    c = 'p'; cL4_mr_emit_byte(tcb + 0x2140, &c, *(unsigned long *)(tcb + 0x2150));
    cL4_arg_decode(result, tcb, *(unsigned long *)(cur + 4), depth + 1);
    if (*result != 0) return;
    c = 'r'; cL4_mr_emit_byte(tcb + 0x2140, &c, *(unsigned long *)(tcb + 0x2150));
    *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
}

/* 003ce720 @ 0x3ce720   (est. cL4_ipc_emit_qr)
 * Ghidra: void FUN_003ce720(undefined4 *result, long tcb, long *msg)
 * Inspect the type of the descriptor's first element: if it is 0x164 emit
 * tag "QR" (2 words) plus a numeric marker; otherwise emit tag "Qr" (2
 * words). Confidence: medium. */
void cL4_ipc_emit_qr(int *result, unsigned long tcb, unsigned long *msg)
{
    unsigned long *cur = msg;
    if (*(unsigned char *)((long)msg + 0x12) - 1 < 2) {
        if (*(short *)(*cur + 0x10) == 0x164) {
            cL4_mr_emit_tag(tcb + 0x2140, "QR", 2, *(unsigned long *)(tcb + 0x2150));
            if (1 < *(unsigned char *)((long)msg + 0x12) - 1) msg = (unsigned long*)*msg;
            cL4_mr_emit_num(tcb, (long)*msg);
            goto done;
        }
    } else if ((*(unsigned char *)((long)msg + 0x12) == 5) && ((int)msg[1] != 0)) {
        cur = (unsigned long*)*msg;
        if (*(short *)(*cur + 0x10) == 0x164) {
            cL4_mr_emit_tag(tcb + 0x2140, "QR", 2, *(unsigned long *)(tcb + 0x2150));
            if (1 < *(unsigned char *)((long)msg + 0x12) - 1) msg = (unsigned long*)*msg;
            cL4_mr_emit_num(tcb, (long)*msg);
            goto done;
        }
    }
    cL4_mr_emit_tag(tcb + 0x2140, "Qr", 2, *(unsigned long *)(tcb + 0x2150));
done:
    *result = 0; *(unsigned long *)(result + 2) = 0; result[4] = 0;
}

/* 003cf1bc @ 0x3cf1bc   (est. cL4_ipc_emit_tq2)
 * Ghidra: void FUN_003cf1bc(undefined8 result, long tcb, undefined8 msg, int depth)
 * Emit tag "TQ" (2 words), then decode message argument 0 via
 * cL4_msg_arg_index. Confidence: medium. */
void cL4_ipc_emit_tq2(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_mr_emit_tag(tcb + 0x2140, "TQ", 2, *(unsigned long *)(tcb + 0x2150));
    cL4_msg_arg_index(result, tcb, (unsigned long*)msg, 0, depth + 1);
}

/* 003cf224 @ 0x3cf224   (est. cL4_ipc_emit_ty)
 * Ghidra: void FUN_003cf224(undefined8 result, long tcb, undefined8 msg, int depth)
 * Emit tag "TY" (2 words), then decode message argument 0 via
 * cL4_msg_arg_index. Confidence: medium. */
void cL4_ipc_emit_ty(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_mr_emit_tag(tcb + 0x2140, "TY", 2, *(unsigned long *)(tcb + 0x2150));
    cL4_msg_arg_index(result, tcb, (unsigned long*)msg, 0, depth + 1);
}

/* 003cf2e8 @ 0x3cf2e8   (est. cL4_ipc_emit_xg)
 * Ghidra: void FUN_003cf2e8(int *result, long tcb, long *msg, int depth)
 * Decode up to two message words. Emits tag "XG" when the first word is
 * non-zero, else "Xg", then decodes the second word. Confidence: medium. */
void cL4_ipc_emit_xg(int *result, unsigned long tcb, unsigned long *msg, unsigned long depth)
{
    unsigned long w1 = 0, w2 = 0; unsigned char c = *(unsigned char *)((long)msg + 0x12);
    unsigned long *cur; const char *tag;
    if (c == 1) {
        w1 = *msg;
    } else {
        cur = msg;
        if (c == 2) {
            w2 = *cur;
        } else if (c == 5) {
            if ((int)msg[1] == 0) { w1 = 0; goto after; }
            if ((int)msg[1] == 1) { msg = (unsigned long*)*msg; w1 = *msg; goto emit; }
            cur = (unsigned long*)*msg; w2 = *cur;
        } else {
            w2 = 0;
        }
        if (c == 2) {
            w1 = msg[1];
        } else if ((c == 5) && (1 < *(unsigned int *)(msg + 1))) {
            msg = (unsigned long*)*msg; w1 = msg[1];
        } else {
            w1 = 0;
        }
        if (w2 != 0) {
            cL4_arg_decode(result, tcb, w2, depth + 1);
            if (*result != 0) return;
            tag = "XG"; goto emit;
        }
    }
after:
    tag = "Xg";
emit:
    cL4_arg_decode(result, tcb, w1, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, tag, 2, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003cf4ac @ 0x3cf4ac   (est. cL4_ipc_emit_lists)
 * Ghidra: void FUN_003cf4ac(int *result, undefined8 tcb, long *msg, int depth)
 * Decode the first message word, then (for a kind-2/5 descriptor) decode the
 * second slot as a list, and for a kind-5 descriptor of >= 3 elements also
 * decode the third slot list. No tag is emitted; the result is cleared.
 * Confidence: medium (pure decode-list helper). */
void cL4_ipc_emit_lists(int *result, unsigned long tcb, unsigned long *msg, unsigned long depth)
{
    unsigned long w0, slot; unsigned long *cur; unsigned char c, k;
    unsigned long *lcur, *lend;
    if (1 < *(unsigned char *)((long)msg + 0x12) - 1) {
        if ((*(unsigned char *)((long)msg + 0x12) == 5) && ((int)msg[1] != 0)) cur = (unsigned long*)*msg;
        else cur = 0;
        w0 = (cur ? *cur : 0);
    } else {
        w0 = *msg;
    }
    cL4_arg_decode(result, tcb, w0, depth + 1);
    if (*result != 0) return;
    c = *(unsigned char *)((long)msg + 0x12);
    cur = msg;
    if (c == 2) {
        slot = cur[1];
    } else if ((c == 5) && (1 < *(unsigned int *)(msg + 1))) {
        cur = (unsigned long*)*msg; slot = cur[1];
    } else {
        slot = 0;
    }
    {
        unsigned long *p = (unsigned long*)slot;
        if (p) {
            k = *(unsigned char *)((long)p + 0x12);
            lcur = p;
            if (k - 1 < 2) {
                if (k == 1) lend = p + 1;
                else if (k == 2) lend = p + 2;
                else if (k == 5) lend = (unsigned long*)*p;
                else lend = 0;
            } else {
                if (k != 5) { lcur = 0; lend = 0; }
                else { lend = (unsigned long*)*p; lcur = lend; }
                lend = lend + *(unsigned int *)(p + 1);
            }
            while (lcur != lend) {
                cL4_arg_decode(result, tcb, *lcur, depth + 1);
                lcur = lcur + 1;
                if (*result != 0) return;
            }
        }
    }
    if ((c == 5) && (*(unsigned int *)(msg + 1) >= 3)) {
        unsigned long *p = *(unsigned long **)(*msg + 0x10);
        if (p) {
            k = *(unsigned char *)((long)p + 0x12);
            lcur = p;
            if (k - 1 < 2) {
                if (k == 1) lend = p + 1;
                else if (k == 2) lend = p + 2;
                else if (k == 5) lend = (unsigned long*)*p;
                else lend = 0;
            } else {
                if (k != 5) { lcur = 0; lend = 0; }
                else { lend = (unsigned long*)*p; lcur = lend; }
                lend = lend + *(unsigned int *)(p + 1);
            }
            while (lcur != lend) {
                cL4_arg_decode(result, tcb, *lcur, depth + 1);
                lcur = lcur + 1;
                if (*result != 0) return;
            }
        }
    }
    *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
}

/* 003cf6b8 @ 0x3cf6b8   (est. cL4_ipc_emit_t)
 * Ghidra: void FUN_003cf6b8(undefined4 *result, long tcb, int *msg)
 * Emit tag "t" (1 word), then, if the count is positive, a value record for
 * count-1. Confidence: medium. */
void cL4_ipc_emit_t(int *result, unsigned long tcb, int *msg)
{
    cL4_mr_emit_tag(tcb + 0x2140, "t", 1, *(unsigned long *)(tcb + 0x2150));
    if (0 < *msg) cL4_mr_emit_val(tcb + 0x2140, *msg - 1, *(unsigned long *)(tcb + 0x2150));
    *result = 0; *(unsigned long *)(result + 2) = 0; result[4] = 0;
}

/* 003cf728 @ 0x3cf728   (est. cL4_ipc_emit_woi)
 * Ghidra: void FUN_003cf728(int *result, long tcb, long *msg, int depth)
 * Decode one or two message words (depending on descriptor kind), emit tag
 * "WOi" (3 words), then a numeric marker of the final word. Confidence:
 * medium. */
void cL4_ipc_emit_woi(int *result, unsigned long tcb, unsigned long *msg, unsigned long depth)
{
    unsigned char c = *(unsigned char *)((long)msg + 0x12);
    unsigned long *cur = msg; unsigned long w2;
    if (c != 1) {
        if (c != 2) {
            if ((c != 5) || ((int)msg[1] == 0)) { w2 = 0; goto dec2; }
            if ((int)msg[1] != 2) { cur = (unsigned long*)*msg; goto dec1; }
            cur = (unsigned long*)*msg;
        }
        cL4_arg_decode(result, tcb, *cur, depth + 1);
        if (*result != 0) return;
        cL4_mr_emit_tag(tcb + 0x2140, "WOi", 3, *(unsigned long *)(tcb + 0x2150));
        if (*(char *)((long)msg + 0x12) == 5) msg = (unsigned long*)*msg;
        msg = msg + 1;
        goto num;
    }
dec1:
    w2 = *cur;
dec2:
    cL4_arg_decode(result, tcb, w2, depth + 1);
    if (*result != 0) return;
    cur = msg;
    if (*(char *)((long)msg + 0x12) == 2) {
        w2 = cur[1];
    } else if ((*(char *)((long)msg + 0x12) == 5) && (1 < *(unsigned int *)(msg + 1))) {
        cur = (unsigned long*)*msg; w2 = cur[1];
    } else {
        w2 = 0;
    }
    cL4_arg_decode(result, tcb, w2, depth + 1);
    if (*result != 0) return;
    cL4_mr_emit_tag(tcb + 0x2140, "WOi", 3, *(unsigned long *)(tcb + 0x2150));
    msg = (unsigned long*)(*msg + 0x10);
num:
    cL4_mr_emit_num(tcb, (long)*msg);
    *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
}

/* 003cf898 @ 0x3cf898   (est. cL4_ipc_emit_woj)
 * Ghidra: void FUN_003cf898(int *result, long tcb, long *msg, int depth)
 * Identical shape to cL4_ipc_emit_woi but emits tag "WOj". Confidence: medium. */
void cL4_ipc_emit_woj(int *result, unsigned long tcb, unsigned long *msg, unsigned long depth)
{
    unsigned char c = *(unsigned char *)((long)msg + 0x12);
    unsigned long *cur = msg; unsigned long w2;
    if (c != 1) {
        if (c != 2) {
            if ((c != 5) || ((int)msg[1] == 0)) { w2 = 0; goto dec2; }
            if ((int)msg[1] != 2) { cur = (unsigned long*)*msg; goto dec1; }
            cur = (unsigned long*)*msg;
        }
        cL4_arg_decode(result, tcb, *cur, depth + 1);
        if (*result != 0) return;
        cL4_mr_emit_tag(tcb + 0x2140, "WOj", 3, *(unsigned long *)(tcb + 0x2150));
        if (*(char *)((long)msg + 0x12) == 5) msg = (unsigned long*)*msg;
        msg = msg + 1;
        goto num;
    }
dec1:
    w2 = *cur;
dec2:
    cL4_arg_decode(result, tcb, w2, depth + 1);
    if (*result != 0) return;
    cur = msg;
    if (*(char *)((long)msg + 0x12) == 2) {
        w2 = cur[1];
    } else if ((*(char *)((long)msg + 0x12) == 5) && (1 < *(unsigned int *)(msg + 1))) {
        cur = (unsigned long*)*msg; w2 = cur[1];
    } else {
        w2 = 0;
    }
    cL4_arg_decode(result, tcb, w2, depth + 1);
    if (*result != 0) return;
    cL4_mr_emit_tag(tcb + 0x2140, "WOj", 3, *(unsigned long *)(tcb + 0x2150));
    msg = (unsigned long*)(*msg + 0x10);
num:
    cL4_mr_emit_num(tcb, (long)*msg);
    *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
}

/* 003ce238 @ 0x3ce238   (est. cL4_ipc_emit_qo_complex)
 * Ghidra: void FUN_003ce238(int *result, long tcb, long *msg, int depth)
 * Decode a variable-length argument list (kind-5 array of >= 3 elements):
 * after the first element, every element of the second slot is decoded via
 * cL4_arg_decode and separated by "_"/"y" markers; the third slot's elements
 * are then decoded. Emits tag "Qo" (2 words) plus a numeric marker before
 * committing the temp record. Errors set result code 0xf7b. Confidence: low
 * (long, register-heavy loop; element-walk faithfully transcribed). */
void cL4_ipc_emit_qo_complex(int *result, unsigned long tcb, unsigned long *msg, unsigned long depth)
{
    unsigned long a0; int err = 0; unsigned long tail = 0;
    unsigned char *slot2, *slot3; unsigned char kind; unsigned long n2, n3, i;
    unsigned long tmp[2] = {0,0}; unsigned long r;
    char marker;

    r = cL4_fmt_begin(tcb, (unsigned long)msg, (unsigned char(*)[16])tmp, 0);
    if ((r & 1) != 0) { err = 0; tail = 0; goto out; }
    if ((*(char *)((long)msg + 0x12) != 5) || (*(unsigned int *)(msg + 1) < 3)) {
        err = 1; tail = 0xf7b; goto out;
    }
    cL4_arg_decode(result, tcb, *(unsigned long *)*msg, depth + 1);
    if (*result != 0) return;
    slot2 = (*(unsigned char **)(*msg + 0x10));
    if ((*(char *)((long)msg + 0x12) == 5) && (2 < *(unsigned int *)(msg + 1))) slot2 = *(unsigned char **)(*msg + 0x10);
    else slot2 = 0;
    i = 0;
    while (1) {
        kind = slot2[0x12];
        n2 = kind;
        if (kind == 1) goto walk2;
        if (kind == 5) { n2 = *(unsigned int *)(slot2 + 1); goto walk2; }
        if (kind == 2) { n2 = 2; goto walk2; }
        break;
walk2:
        if (n2 <= i) break;
        marker = (i != 0) ? '_' : 'y';
        cL4_mr_emit_byte(tcb + 0x2140, &marker, *(unsigned long *)(tcb + 0x2150));
        kind = slot2[0x12];
        n2 = kind;
        {
            unsigned long word;
            if (kind == 1) { if (n2 <= i) word = 0; else { unsigned char *p = slot2; if (1 < kind - 1) p = (unsigned char*)*((unsigned long*)slot2); word = ((unsigned long*)p)[i]; } }
            else if (kind == 5) { n2 = *(unsigned int *)(slot2 + 1); word = ((unsigned long*)*((unsigned long*)slot2))[i]; }
            else if (kind == 2) { n2 = 2; word = ((unsigned long*)slot2)[i]; }
            else word = 0;
            cL4_arg_decode(result, tcb, word, depth + 1);
        }
        i = i + 1;
        if (*result != 0) return;
    }
    if ((*(char *)((long)msg + 0x12) == 5) && (3 < *(unsigned int *)(msg + 1))) {
        slot3 = *(unsigned char **)(*msg + 0x18);
        i = 0;
        while (1) {
            kind = slot3[0x12];
            if (kind == 1) n3 = 1;
            else if (kind == 5) n3 = *(unsigned int *)(slot3 + 1);
            else if (kind != 2) break;
            else n3 = 2;
            if (n3 <= i) break;
            {
                unsigned long word;
                if (kind == 1) { if (n3 <= i) word = 0; else { unsigned char *p = slot3; if (1 < kind - 1) p = (unsigned char*)*((unsigned long*)slot3); word = ((unsigned long*)p)[i]; } }
                else if (kind == 5) { n3 = *(unsigned int *)(slot3 + 1); word = ((unsigned long*)*((unsigned long*)slot3))[i]; }
                else if (kind == 2) { n3 = 2; word = ((unsigned long*)slot3)[i]; }
                else word = 0;
                cL4_arg_decode(result, tcb, word, depth + 1);
            }
            i = i + 1;
            if (*result != 0) return;
        }
    }
    cL4_mr_emit_tag(tcb + 0x2140, "Qo", 2, *(unsigned long *)(tcb + 0x2150));
    if (*(char *)((long)msg + 0x12) == 5) msg = (unsigned long*)*msg;
    cL4_mr_emit_num(tcb, (long)msg[1]);
    cL4_out_commit(tcb, (long*)tmp);
out:
    *result = err;
    *(unsigned long *)(result + 2) = tail;
    result[4] = err ? 0xf7b : 0;
}
/* 003cde9c @ 0x003cde9c   (est. cL4_ipc_emit_xsq)
 * Ghidra: void FUN_003cde9c(int *result, long tcb, long *msg, int depth)
 * Decode the first message word via cL4_msg_one and emit tag "XSq" (3
 * words) on success. Confidence: medium. */
void cL4_ipc_emit_xsq(int *result, unsigned long tcb, unsigned long *msg, unsigned long depth)
{
    unsigned long a0; unsigned long *cur = msg;
    if (1 < *(unsigned char *)((long)msg + 0x12) - 1) {
        if ((*(unsigned char *)((long)msg + 0x12) != 5) || ((int)msg[1] == 0)) { a0 = 0; goto l1; }
        cur = (unsigned long*)*msg;
    }
    a0 = *cur;
l1:
    cL4_msg_one(result, tcb, (unsigned long*)a0, depth + 2);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, "XSq", 3, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}
/* 003cdf30 @ 0x003cdf30   (est. cL4_ipc_emit_xsa)
 * Ghidra: void FUN_003cdf30(int *result, long tcb, long *msg, int depth)
 * Decode the first message word via cL4_msg_one and emit tag "XSa" (3
 * words) on success. Confidence: medium. */
void cL4_ipc_emit_xsa(int *result, unsigned long tcb, unsigned long *msg, unsigned long depth)
{
    unsigned long a0; unsigned long *cur = msg;
    if (1 < *(unsigned char *)((long)msg + 0x12) - 1) {
        if ((*(unsigned char *)((long)msg + 0x12) != 5) || ((int)msg[1] == 0)) { a0 = 0; goto l1; }
        cur = (unsigned long*)*msg;
    }
    a0 = *cur;
l1:
    cL4_msg_one(result, tcb, (unsigned long*)a0, depth + 2);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, "XSa", 3, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}
/* 003ce1a4 @ 0x003ce1a4   (est. cL4_ipc_emit_xsp)
 * Ghidra: void FUN_003ce1a4(int *result, long tcb, long *msg, int depth)
 * Decode the first message word via cL4_msg_one and emit tag "XSp" (3
 * words) on success. Confidence: medium. */
void cL4_ipc_emit_xsp(int *result, unsigned long tcb, unsigned long *msg, unsigned long depth)
{
    unsigned long a0; unsigned long *cur = msg;
    if (1 < *(unsigned char *)((long)msg + 0x12) - 1) {
        if ((*(unsigned char *)((long)msg + 0x12) != 5) || ((int)msg[1] == 0)) { a0 = 0; goto l1; }
        cur = (unsigned long*)*msg;
    }
    a0 = *cur;
l1:
    cL4_msg_one(result, tcb, (unsigned long*)a0, depth + 2);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, "XSp", 3, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}
/* 003cdfc4 @ 0x003cdfc4   (est. cL4_ipc_emit_xsd)
 * Ghidra: void FUN_003cdfc4(int *result, long tcb, long *msg, int depth)
 * Decode two message words (each via cL4_msg_one at depth+2), then emit tag
 * "XSD" (3 words) on success. Confidence: medium. */
void cL4_ipc_emit_xsd(int *result, unsigned long tcb, unsigned long *msg, unsigned long depth)
{
    unsigned long a0, a1; unsigned long *cur = msg;
    if (1 < *(unsigned char *)((long)msg + 0x12) - 1) {
        if ((*(unsigned char *)((long)msg + 0x12) != 5) || ((int)msg[1] == 0)) { a0 = 0; goto l1; }
        cur = (unsigned long*)*msg;
    }
    a0 = *cur;
l1:
    cL4_msg_one(result, tcb, (unsigned long*)a0, depth + 2);
    if (*result != 0) return;
    cur = msg;
    if (*(char *)((long)msg + 0x12) != 2) {
        if ((*(char *)((long)msg + 0x12) != 5) || (*(unsigned int *)(msg + 1) < 2)) { a1 = 0; goto l2; }
        cur = (unsigned long*)*msg;
    }
    a1 = cur[1];
l2:
    cL4_msg_one(result, tcb, (unsigned long*)a1, depth + 2);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, "XSD", 3, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}
/* 003ce0b4 @ 0x003ce0b4   (est. cL4_ipc_emit_xsa2)
 * Ghidra: void FUN_003ce0b4(int *result, long tcb, long *msg, int depth)
 * Decode two message words (each via cL4_msg_one at depth+2), then emit tag
 * "XSA" (3 words) on success. Confidence: medium. */
void cL4_ipc_emit_xsa2(int *result, unsigned long tcb, unsigned long *msg, unsigned long depth)
{
    unsigned long a0, a1; unsigned long *cur = msg;
    if (1 < *(unsigned char *)((long)msg + 0x12) - 1) {
        if ((*(unsigned char *)((long)msg + 0x12) != 5) || ((int)msg[1] == 0)) { a0 = 0; goto l1; }
        cur = (unsigned long*)*msg;
    }
    a0 = *cur;
l1:
    cL4_msg_one(result, tcb, (unsigned long*)a0, depth + 2);
    if (*result != 0) return;
    cur = msg;
    if (*(char *)((long)msg + 0x12) != 2) {
        if ((*(char *)((long)msg + 0x12) != 5) || (*(unsigned int *)(msg + 1) < 2)) { a1 = 0; goto l2; }
        cur = (unsigned long*)*msg;
    }
    a1 = cur[1];
l2:
    cL4_msg_one(result, tcb, (unsigned long*)a1, depth + 2);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, "XSA", 3, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}
/* 003cfc30 @ 0x3cfc30   (est. cL4_ipc_emit_r)
 * Ghidra: void FUN_003cfc30(undefined8 *result, long tcb, long *msg, int depth)
 * Parse a message via cL4_msg_parse; on parse error propagate the result.
 * Otherwise branch on the parsed sign word (local_40): +1 emits tag "Rj",
 * 0 emits "Ri", -1 emits "RI" plus a numeric marker, any other value emits
 * "RJ" plus a numeric marker; the parsed value word is then passed to
 * cL4_msg_emit_pair. Non-decodable shapes set error code 0x470/0x479.
 * Confidence: low (register-heavy; sign-word semantics inferred). */
void cL4_ipc_emit_r(unsigned long *result, unsigned long tcb, unsigned long *msg, unsigned long depth)
{
    unsigned long *cur = msg; const char *tag;
    int perr, pval; unsigned long pdata[4];

    if (*(char *)((long)msg + 0x12) != 2) {
        if ((*(char *)((long)msg + 0x12) != 5) || ((int)msg[1] != 2)) {
            result[0] = 1; result[1] = (unsigned long)msg; result[2] = 0x470;
            return;
        }
        cur = (unsigned long*)*msg;
    }
    cL4_msg_parse(pdata, (unsigned long*)tcb, (unsigned long*)*cur, depth + 1);
    perr = (int)pdata[0];
    if (perr != 0) {
        result[1] = pdata[1]; result[0] = pdata[0]; result[2] = pdata[2];
        return;
    }
    if ((-1 < pdata[3]) && (pdata[3] == 0)) {
        result[0] = 1; result[1] = (unsigned long)msg; result[2] = 0x479;
        return;
    }
    pval = (int)pdata[3];
    if (pval == 1) {
        tag = "Rj";
    } else if (pval == 0) {
        tag = "Ri";
    } else {
        if (pval == -1) {
            cL4_mr_emit_tag(tcb + 0x2140, "RI", 2, *(unsigned long *)(tcb + 0x2150));
            if (*(char *)((long)msg + 0x12) == 5) msg = (unsigned long*)*msg;
            cL4_mr_emit_num(tcb, (long)**(unsigned long **)((long)msg + 8));
            goto done;
        }
        tag = "RJ";
    }
    cL4_mr_emit_tag(tcb + 0x2140, tag, 2, *(unsigned long *)(tcb + 0x2150));
    if (*(char *)((long)msg + 0x12) == 5) msg = (unsigned long*)*msg;
    cL4_mr_emit_num(tcb, (long)**(unsigned long **)((long)msg + 8));
    cL4_msg_emit_pair(tcb, (unsigned long*)pdata[3], (unsigned long)&DAT_005be7c0, 0x7a);
done:
    result[0] = 0; result[1] = 0; result[2] = 0;
}

/* 003cfdc4 @ 0x3cfdc4   (est. cL4_ipc_emit_dollar)
 * Ghidra: void FUN_003cfdc4(undefined4 *result, long tcb, undefined8 *msg)
 * Emit tag "$" (1 word), then a numeric marker of msg[0]. Confidence: medium. */
void cL4_ipc_emit_dollar(int *result, unsigned long tcb, unsigned long *msg)
{
    cL4_mr_emit_tag(tcb + 0x2140, "$", 1, *(unsigned long *)(tcb + 0x2150));
    cL4_mr_emit_num(tcb, (long)msg[0]);
    *result = 0; *(unsigned long *)(result + 2) = 0; result[4] = 0;
}

/* 003cfe28 @ 0x3cfe28   (est. cL4_ipc_emit_dollar_n)
 * Ghidra: void FUN_003cfe28(undefined4 *result, long tcb, long *msg)
 * Emit tag "$n" (2 words), then a numeric marker of the negated msg[0].
 * Confidence: medium. */
void cL4_ipc_emit_dollar_n(int *result, unsigned long tcb, long *msg)
{
    cL4_mr_emit_tag(tcb + 0x2140, "$n", 2, *(unsigned long *)(tcb + 0x2150));
    cL4_mr_emit_num(tcb, -*msg);
    *result = 0; *(unsigned long *)(result + 2) = 0; result[4] = 0;
}

/* 003cfe90 @ 0x3cfe90   (est. cL4_ipc_emit_rv)
 * Ghidra: void FUN_003cfe90(int *result, long tcb, long *msg, int depth)
 * Validate a two-level message shape (a 0x27-typed element whose payload is a
 * 0xf4-typed element). On success decodes the nested arg and emits tag "RV"
 * (2 words) plus the parsed value; on shape failure sets error code 0x1034/
 * 0x1035/0x1036 with err=1. Confidence: low (deeply nested shape check). */
void cL4_ipc_emit_rv(int *result, unsigned long tcb, unsigned long *msg, unsigned long depth)
{
    unsigned char c = *(unsigned char *)((long)msg + 0x12);
    unsigned long *cur = msg; unsigned long a0, v; int code, err;

    if (c == 2) {
        cur = (unsigned long*)*cur;
        if (1 < *(unsigned char *)((long)cur + 0x12) - 1) cur = (unsigned long*)*cur;
        if (*(short *)(*cur + 0x10) == 0x27) {
            cur = msg;
            if (c == 5) cur = (unsigned long*)*msg;
            if (*(short *)(cur[1] + 0x10) == 0xf4) {
                cur = msg;
                if (c == 2) {
                    v = cur[1];
                } else if ((c == 5) && (1 < *(unsigned int *)(msg + 1))) {
                    cur = (unsigned long*)*msg; v = cur[1];
                } else {
                    v = 0;
                }
                cL4_msg_one(result, tcb, (long*)v, depth + 2);
                if (*result != 0) return;
                cL4_mr_emit_tag(tcb + 0x2140, "RV", 2, *(unsigned long *)(tcb + 0x2150));
                {
                    unsigned long *p = msg; unsigned long word;
                    if (1 < *(unsigned char *)((long)msg + 0x12) - 1) {
                        if ((*(unsigned char *)((long)msg + 0x12) == 5) && ((int)msg[1] != 0)) p = (unsigned long*)*msg;
                        else p = 0;
                    }
                    if (*(unsigned char *)((long)p + 0x12) - 1 < 2) {
                        word = *p;
                    } else {
                        if ((*(unsigned char *)((long)p + 0x12) == 5) && (*(int *)(p + 1) != 0)) p = (unsigned long*)*p;
                        word = 0;
                    }
                    cL4_msg_emit_pair(tcb, (long*)word, (unsigned long)&DAT_005be7c0, 0x7a);
                }
                err = 0; a0 = 0; code = 0;
                goto out;
            }
            code = 0x1036;
        } else {
            code = 0x1035;
        }
    } else {
        if ((c == 5) && ((int)msg[1] == 2)) {
            cur = (unsigned long*)*msg;
            goto redispatch;
        }
        code = 0x1034;
    }
    err = 1;
out:
    *result = err;
    *(unsigned long *)(result + 2) = (unsigned long)msg;
    result[4] = code;
    return;
redispatch:
    /* fall through to the shape walk above for the kind-5 case */
    code = 0;
    goto out;
}

/* 003d0098 @ 0x3d0098   (est. cL4_ipc_emit_b)
 * Ghidra: void FUN_003d0098(undefined8 result, long *msg, int depth)
 * Read the first message word and dispatch it through cL4_msg_dispatch2 with
 * tag "b". Confidence: low (arg attribution per this region's convention). */
void cL4_ipc_emit_b(int *result, unsigned long *msg, int depth)
{
    unsigned long word;
    if (1 < *(unsigned char *)((long)msg + 0x12) - 1) {
        if ((*(unsigned char *)((long)msg + 0x12) != 5) || ((int)msg[1] == 0)) { word = 0; goto d; }
        msg = (unsigned long*)*msg;
    }
    word = *msg;
d:
    cL4_msg_dispatch2(result, 0, word, (unsigned long)"b", 1, depth + 1);
}

/* 003d00e0 @ 0x3d00e0   (est. cL4_ipc_emit_z)
 * Ghidra: void FUN_003d00e0(undefined8 result, long *msg, int depth)
 * Read the first message word and dispatch it through cL4_msg_dispatch2 with
 * tag "z". Confidence: low. */
void cL4_ipc_emit_z(int *result, unsigned long *msg, int depth)
{
    unsigned long word;
    if (1 < *(unsigned char *)((long)msg + 0x12) - 1) {
        if ((*(unsigned char *)((long)msg + 0x12) != 5) || ((int)msg[1] == 0)) { word = 0; goto d; }
        msg = (unsigned long*)*msg;
    }
    word = *msg;
d:
    cL4_msg_dispatch2(result, 0, word, (unsigned long)"z", 1, depth + 1);
}

/* 003d0128 @ 0x3d0128   (est. cL4_ipc_emit_byte_tag)
 * Ghidra: void FUN_003d0128(int *result, long tcb, undefined8 msg, undefined1 byte, int depth)
 * Decode the message arguments, emit tag "b" (1 word), then the caller's
 * `byte`. Confidence: medium. */
void cL4_ipc_emit_byte_tag(int *result, unsigned long tcb, unsigned long msg, unsigned char byte, unsigned long depth)
{
    char c = (char)byte;
    cL4_msg_args(result, tcb, (long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, "b", 1, *(unsigned long *)(tcb + 0x2150));
        cL4_mr_emit_byte(tcb + 0x2140, &c, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}
void cL4_msg_dispatch_full(int *result, unsigned long *tcb, unsigned long msg, unsigned long depth)
{
    unsigned short type; const char *tag; unsigned long count = 1;
    unsigned long tmp[2] = {0,0}; unsigned char b;
    unsigned long *mp = (unsigned long*)msg;

    if (0x400 < (unsigned int)depth) {
        *result = 3;
        *(unsigned long **)(result + 2) = (unsigned long*)msg;
        result[4] = 0x223;
        return;
    }
    if (!cL4_msg_kind(msg)) {
        type = *(unsigned short *)(msg + 2);
        if (type < 0xe7) {
            if (type == 0x19) { tag = "C"; }
            else if (type == 0x3f) { tag = "O"; }
            else if (type == 0xb1) { tag = "XY"; count = 2; goto emit; }
            else goto unknown;
        } else if (type == 0xf6) {
            tag = "a";
        } else if (type == 0xf5) {
            {
                unsigned long (*cb)(unsigned long, unsigned long, unsigned long) =
                    (unsigned long (*)(unsigned long, unsigned long, unsigned long))tcb[0x434];
                unsigned long v = cb(tcb[0x435], 0, *mp);
                cL4_arg_decode(result, (unsigned long)tcb, v, depth + 1);
            }
            return;
        } else if (type == 0xe7) {
            tag = "V";
        } else {
            goto unknown;
        }
        goto emit;
    }
    tmp[0] = 0; tmp[1] = 0;
    if (cL4_fmt_begin((unsigned long)tcb, msg, (unsigned char(*)[16])tmp, 0)) goto done;
    if (cL4_msg_header((int*)&b, msg, *tcb) != 0) {
        /* propagate header result */
        result[1] = tmp[1]; *result = tmp[0]; result[2] = tmp[2];
        return;
    }
    cL4_msg_dispatch_full(result, tcb, tmp[2], depth + 1);
    if (*result != 0) return;
    b = 0x79;
    cL4_msg_dispatch_pkt(result, (unsigned long)tcb, msg, &b, depth + 1, 0);
    if (*result != 0) return;
    if ((*(char *)(msg + 0x12) != 5) || ((int)((unsigned long*)msg)[1] != 3)) goto fin;
    {
        unsigned long slot = *(unsigned long *)(*(unsigned long*)msg + 0x10);
        unsigned long *sp = (unsigned long*)slot;
        unsigned char k; unsigned long n, i;
        k = *(unsigned char *)(slot + 0x12);
        n = k;
        if (k == 1) {
            i = 0;
            do {
                unsigned long word;
                k = *(unsigned char *)(slot + 0x12);
                if (k == 1) { if (n <= i) word = 0; else { unsigned long *p = sp; if (1 < k - 1) p = (unsigned long*)*sp; word = p[i]; } }
                else if (k == 5) { n = *(unsigned int *)(slot + 1); word = ((unsigned long*)*sp)[i]; }
                else if (k == 2) { n = 2; word = sp[i]; }
                else word = 0;
                cL4_arg_decode(result, (unsigned long)tcb, word, depth + 1);
                if (*result != 0) return;
                i = i + 1;
            } while (n != i);
        } else if (k == 5) {
            n = *(unsigned int *)(slot + 1);
            if (*(unsigned int *)(slot + 1) != 0) { i = 0; goto l1; }
        } else if (k == 2) {
            n = 2; i = 0; goto l1;
        }
        goto fin;
    l1: ;
    }
fin:
    b = 0x47;
    cL4_mr_emit_byte((unsigned long)tcb + 0x428, &b, tcb[0x42a]);
    cL4_out_commit((unsigned long)tcb, (long*)tmp);
done:
    *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    return;
emit:
    cL4_msg_dispatch_tag(result, (unsigned long)tcb, msg, (unsigned long)tag, count, depth);
    return;
unknown:
    *result = 5;
    *(unsigned long **)(result + 2) = (unsigned long*)msg;
    result[4] = 0x24d;
}

/* 003d0bc8 @ 0x3d0bc8   (est. cL4_msg_dispatch_pkt)
 * Ghidra: void FUN_003d0bc8(int *result, long tcb, long *msg, undefined1 *byte, int depth, int flag)
 * Packet dispatch for a message whose type word selects a nested packet
 * handler. Several type words recurse into the first element (kind-1/5) with
 * a separator byte emitted from *byte; type 0x13 requires the payload type to
 * be 0x4e/0x1e; types 0x12/0x1e recurse with the byte/flags updated. Errors
 * set result codes 0x2b0/0x293. Confidence: low (large register-heavy switch;
 * recursions faithfully transcribed). */
void cL4_msg_dispatch_pkt(int *result, unsigned long tcb, unsigned long msg, unsigned char *byte,
                          unsigned long depth, int flag)
{
    unsigned long *mp = (unsigned long*)msg;
    unsigned short type = *(unsigned short *)(msg + 2);
    unsigned int t9 = (unsigned int)type;
    int err = 0; unsigned long tail = 0; unsigned char c; unsigned long v;
    unsigned long cur; unsigned long payload;
    unsigned char k;

    if (0xa0 < type) {
        unsigned int u = t9 - 0xe3;
        if (u < 0x2c) {
            if ((1ull << (u & 0x3f) & 0x93000000029ull) != 0) goto group_big;
            if ((1ull << (u & 0x3f) & 0x80010ull) != 0) goto group_rec;
        }
        u = t9 - 0xa1;
        if (0x36 < u) goto out;
        if ((1ull << (u & 0x3f) & 0x40000038000001ull) != 0) goto group_big;
        err = 0;
        if ((unsigned long)u != 0x1e) goto out;
        goto group_rec;
    }
    if (type < 0x22) {
        if ((t9 != 0x12) && (0x11 < type)) {
            if (t9 != 0x13) {
                if (t9 == 0x19) goto group_rec;
                err = 0;
                if (t9 != 0x1e) goto out;
                goto group_big;
            }
            cur = msg;
            if (*(unsigned char *)(msg + 0x12) - 1 < 2) {
                payload = *(unsigned long*)cur;
            } else if ((*(unsigned char *)(msg + 0x12) == 5) && ((int)((unsigned long*)msg)[1] != 0)) {
                cur = *(unsigned long*)msg;
                payload = *(unsigned long*)cur;
            } else {
                payload = 0;
            }
            if ((*(short *)(payload + 2) != 0x4e) && (*(short *)(payload + 2) != 0x1e)) {
                err = 0x2b0; tail = msg; goto out2;
            }
            if (*(unsigned char *)(payload + 0x12) - 1 < 2) {
                v = *(unsigned long*)payload;
            } else if ((*(unsigned char *)(payload + 0x12) == 5) && (*(int *)(payload + 1) != 0)) {
                payload = *(unsigned long*)payload;
                v = *(unsigned long*)payload;
            } else {
                v = 0;
            }
            cL4_msg_dispatch_pkt(result, tcb, v, byte, depth + 1, 1);
            if (*result != 0) return;
            c = *byte;
            cL4_mr_emit_byte(tcb + 0x2140, &c, *(unsigned long *)(tcb + 0x2150));
            *byte = '_';
            {
                unsigned long p = msg; unsigned long w;
                if (*(char *)(msg + 0x12) == 2) { w = ((unsigned long*)p)[1]; }
                else if ((*(char *)(msg + 0x12) == 5) && (1 < *(unsigned int *)(msg + 1))) { p = *(unsigned long*)msg; w = ((unsigned long*)p)[1]; }
                else w = 0;
                cL4_msg_args(result, tcb, (unsigned long*)p, depth + 1);
            }
            goto fin2;
        }
        if (t9 - 0xd < 6) {
            if (t9 == 0x12) flag = 1;
            cur = msg;
            if (*(unsigned char *)(msg + 0x12) - 1 < 2) {
                payload = *(unsigned long*)cur;
            } else if ((*(unsigned char *)(msg + 0x12) == 5) && ((int)((unsigned long*)msg)[1] != 0)) {
                cur = *(unsigned long*)msg;
                payload = *(unsigned long*)cur;
            } else {
                payload = 0;
            }
            if (*(short *)(payload + 2) != 0xf4) { err = 0x293; tail = msg; goto out2; }
            if (*(unsigned char *)(payload + 0x12) - 1 < 2) {
                payload = *(unsigned long*)payload;
            } else if ((*(unsigned char *)(payload + 0x12) == 5) && (*(int *)(payload + 1) != 0)) {
                payload = *(unsigned long*)payload;
                payload = *(unsigned long*)payload;
            } else {
                payload = 0;
            }
            if (*(short *)(payload + 2) == 0xf5) {
                unsigned long (*cb)(unsigned long, unsigned long, unsigned long) =
                    (unsigned long (*)(unsigned long, unsigned long, unsigned long))*(unsigned long **)(tcb + 0x21a0);
                unsigned long *r = (unsigned long*)cb(*(unsigned long *)(tcb + 0x21a8), 0, *(unsigned long*)payload);
                if (1 < *(unsigned char *)((long)r + 0x12) - 1) {
                    if ((*(unsigned char *)((long)r + 0x12) != 5) || ((int)r[1] == 0)) { payload = 0; goto after_payload; }
                    r = (unsigned long*)*r;
                }
                payload = (unsigned long)r;
            }
after_payload:
            if (*(unsigned char *)(payload + 0x12) - 1 < 2) {
                v = *(unsigned long*)payload;
            } else if ((*(unsigned char *)(payload + 0x12) == 5) && (*(int *)(payload + 1) != 0)) {
                payload = *(unsigned long*)payload;
                v = *(unsigned long*)payload;
            } else {
                v = 0;
            }
            cL4_msg_dispatch_pkt(result, tcb, v, byte, depth + 1, flag);
            if (*result != 0) return;
            c = *byte;
            cL4_mr_emit_byte(tcb + 0x2140, &c, *(unsigned long *)(tcb + 0x2150));
            *byte = '_';
            {
                unsigned long p = msg; unsigned long w;
                if (*(char *)(msg + 0x12) == 2) { w = ((unsigned long*)p)[1]; }
                else if ((*(char *)(msg + 0x12) == 5) && (1 < *(unsigned int *)(msg + 1))) { p = *(unsigned long*)msg; w = ((unsigned long*)p)[1]; }
                else w = 0;
                cL4_msg_args(result, tcb, (unsigned long*)p, depth + 1);
            }
            goto fin2;
        }
        err = 0;
        if (t9 != 0) goto out;
group_big:
        if (flag != 0) {
            cur = msg;
            if (*(unsigned char *)(msg + 0x12) - 1 < 2) {
                v = *(unsigned long*)cur;
            } else if ((*(unsigned char *)(msg + 0x12) == 5) && ((int)((unsigned long*)msg)[1] != 0)) {
                cur = *(unsigned long*)msg;
                v = *(unsigned long*)cur;
            } else {
                v = 0;
            }
            cL4_msg_dispatch_pkt(result, tcb, v, byte, depth + 1, 1);
            if (*result != 0) return;
            err = cL4_fmt_advance(msg);
            if (err == 0) goto fin2;
            c = *byte;
            cL4_mr_emit_byte(tcb + 0x2140, &c, *(unsigned long *)(tcb + 0x2150));
            goto fin2;
        }
        goto out;
    }
    if (type < 0x48) {
        if ((1 < t9 - 0x34) && (t9 != 0x22)) {
            err = 0;
            if (t9 != 0x3f) goto out;
            goto group_rec;
        }
        goto group_big;
    }
    {
        unsigned long u = (unsigned long)(t9 - 0x48);
        if (0x3a < t9 - 0x48) goto out;
        if ((1ull << (u & 0x3f) & 0x404000010000041ull) != 0) goto group_big;
        if (u != 1) {
            err = 0;
            if (u != 0xd) goto out;
            c = *byte;
            cL4_mr_emit_byte(tcb + 0x2140, &c, *(unsigned long *)(tcb + 0x2150));
            goto fin2;
        }
        {
            unsigned long p = msg; unsigned long w;
            if (*(char *)(msg + 0x12) == 2) { w = ((unsigned long*)p)[1]; }
            else if ((*(char *)(msg + 0x12) == 5) && (1 < *(unsigned int *)(msg + 1))) { p = *(unsigned long*)msg; w = ((unsigned long*)p)[1]; }
            else w = 0;
            cL4_msg_dispatch_pkt(result, tcb, w, byte, depth + 1, flag);
        }
        if (*result != 0) return;
        goto fin2;
    }
group_rec:
    if (*(unsigned char *)(msg + 0x12) - 1 < 2) {
        v = *(unsigned long*)msg;
    } else if ((*(unsigned char *)(msg + 0x12) == 5) && ((int)((unsigned long*)msg)[1] != 0)) {
        v = *(unsigned long *)*(unsigned long*)msg;
    } else {
        v = 0;
    }
    cL4_msg_dispatch_pkt(result, tcb, v, byte, depth + 1, flag);
    if (*result != 0) return;
    c = *byte;
    cL4_mr_emit_byte(tcb + 0x2140, &c, *(unsigned long *)(tcb + 0x2150));
    *byte = '_';
    tail = 0; err = 0;
    goto out2;
fin2:
    err = 0; tail = 0;
out2:
    *result = err;
    *(unsigned long *)(result + 2) = tail;
    result[4] = (int)tail ? (int)tail : err;
    return;
out:
    *result = err;
    *(unsigned long *)(result + 2) = tail;
    result[4] = 0;
}

/* 003d1128 @ 0x3d1128   (est. cL4_msg_dispatch_tag)
 * Ghidra: void FUN_003d1128(int *result, long tcb, undefined8 msg, undefined8 tag, undefined8 count, int depth)
 * When the message is not pre-flushed by cL4_fmt_begin, decode the argument
 * list and emit the caller-supplied `tag`/`count` record, then commit the
 * temp output. Confidence: medium. */
void cL4_msg_dispatch_tag(int *result, unsigned long tcb, unsigned long msg, unsigned long tag,
                          unsigned long count, unsigned long depth)
{
    unsigned long tmp[2] = {0,0};
    if (!(cL4_fmt_begin(tcb, msg, (unsigned char(*)[16])tmp, 0) & 1)) {
        cL4_msg_args(result, tcb, (long*)msg, depth + 1);
        if (*result != 0) return;
        cL4_mr_emit_tag(tcb + 0x2140, (const void*)tag, count, *(unsigned long *)(tcb + 0x2150));
        cL4_out_commit(tcb, (long*)tmp);
    }
    *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
}
/* 003d12c8 @ 0x3d12c8   (est. cL4_msg_parse)
 * Ghidra: void FUN_003d12c8(long *result, undefined8 *tcb, long *msg, int depth)
 * Parse a message into a 5-word result {err, argA, argB, count, msgptr}.
 * Handles the composite type 0x2e (an argument array: collects each element
 * into a temporary list and emits them in reverse) and the identity types
 * 0x27/0x57; any other type is decoded as a single argument via cL4_arg_decode
 * (error path returns {err,..,0}). A 0xf4-typed descriptor is dereferenced
 * first. Confidence: low (register-heavy; field meanings inferred). */
void cL4_msg_parse(unsigned long *result, unsigned long *tcb, unsigned long *msg, unsigned long depth)
{
    unsigned long local[5];
    unsigned short type; unsigned long v, cnt;
    unsigned long tmp[2] = {0,0}; unsigned long arr = 0, n = 0;
    unsigned long w; int err; unsigned long nxt;

    if ((short)msg[2] == 0xf4) {
        if (1 < *(unsigned char *)((long)msg + 0x12) - 1) {
            if ((*(unsigned char *)((long)msg + 0x12) != 5) || ((int)msg[1] == 0)) { msg = 0; goto parse; }
            msg = (unsigned long*)*msg;
        }
        msg = (unsigned long*)*msg;
    }
parse:
    tmp[0] = 0; tmp[1] = 0;
    if (cL4_fmt_begin((unsigned long)tcb, (unsigned long)msg, (unsigned char(*)[16])tmp, 0)) {
        result[0] = 0; result[1] = 0; result[2] = 0; result[3] = 0xffffffff;
        result[4] = 0;
        return;
    }
    arr = 0; n = 0;
parse_loop:
    type = (unsigned short)msg[2];
    if (type == 0x2e) {
        unsigned long *p = msg; unsigned long w0;
        if (*(char *)((long)msg + 0x12) == 2) { w0 = p[1]; }
        else if ((*(char *)((long)msg + 0x12) == 5) && (1 < *(unsigned int *)(msg + 1))) { p = (unsigned long*)*msg; w0 = p[1]; }
        else w0 = 0;
        cL4_fmt_args(&arr, &w0, *tcb);
        {
            unsigned long *q = msg;
            if (*(unsigned char *)((long)msg + 0x12) - 1 < 2) {
                w = *q;
            } else if ((*(unsigned char *)((long)msg + 0x12) == 5) && ((int)msg[1] != 0)) {
                q = (unsigned long*)*msg; w = *q;
            } else {
                w = 0;
            }
            if (1 < *(unsigned char *)((long)w + 0x12) - 1) { msg = 0; goto arr_redir; }
            msg = (unsigned long*)w;
        }
        goto parse_loop;
    }
    if ((type == 0x27) || (type == 0x57)) {
        if ((unsigned int)n == 0) { result[3] = 0; goto done; }
    } else {
        cL4_arg_decode((int*)&err, (unsigned long)tcb, (unsigned long)msg, depth + 1);
        if (err != 0) {
            result[0] = err; result[1] = 0; result[2] = 0; result[3] = 0; result[4] = (unsigned long)msg;
            return;
        }
        if ((unsigned int)n == 0) { result[0]=0; result[1]=0; result[2]=0; result[3]=0xffffffff; result[4]=0; return; }
        msg = 0;
        n = (unsigned int)n;
    }
    {
        /* emit collected args in reverse */
        unsigned int u8 = (unsigned int)n, u9;
        const void *sep = &DAT_005be7c0; unsigned int i = 1; unsigned long slen;
        for (u9 = u8 - 1; i <= u8; u9 = u9 - 1, i = i + 1) {
            cL4_arg_decode((int*)&err, (unsigned long)tcb, *(unsigned long *)(arr + (unsigned long)u9 * 8), depth + 1);
            if (err != 0) { result[0]=err; result[1]=0; result[2]=0; result[3]=0; result[4]=(unsigned long)msg; return; }
            slen = cL4_strlen(sep);
            cL4_mr_emit_tag((unsigned long)tcb + 0x428, sep, slen, tcb[0x42a]);
            sep = &DAT_005be7c0;
        }
        if ((unsigned int)n != 0) {
            cL4_out_commit((unsigned long)tcb, (long*)tmp);
            result[3] = (unsigned int)n;
        } else {
            result[3] = 0;
        }
        goto done;
    }
arr_redir:
    {
        /* 0x2e with a nested array payload */
        unsigned long *q;
        if ((*(unsigned char *)((long)msg + 0x12) == 5) && (*(int *)(msg + 1) != 0)) {
            q = (unsigned long*)*msg; v = *q;
        } else {
            v = 0;
        }
        msg = (unsigned long*)v;
        goto parse_loop;
    }
done:
    result[0] = 0; result[1] = 0; result[2] = 0;
    result[3] = 0;
    result[4] = (unsigned long)msg;
}

/* 003d154c @ 0x3d154c   (est. cL4_msg_emit_pair)
 * Ghidra: void FUN_003d154c(long tcb, long *msg, long tag, undefined1 byte)
 * Emit a symbol/string pair: for a type-0x57 message emit a single "s" byte;
 * otherwise emit the caller's `tag` record followed by two numeric markers of
 * the message's two words, or a single marker when only one is present, or the
 * fallback `byte` when both are zero. Confidence: medium. */
void cL4_msg_emit_pair(unsigned long tcb, unsigned long *msg, unsigned long tag, unsigned char byte)
{
    unsigned long *cur = msg, *second; unsigned long w0, w1, tlen; char c;
    if ((short)msg[2] == 0x57) {
        c = 's';
        cL4_mr_emit_byte(tcb + 0x2140, &c, *(unsigned long *)(tcb + 0x2150));
        return;
    }
    if ((1 < *(unsigned char *)((long)msg + 0x12) - 1) &&
        (msg = (unsigned long*)*msg, cur = msg, *(unsigned char *)((long)msg + 0x12) != 5)) {
        cur = msg;
    }
    w0 = *(unsigned long *)*cur;
    w1 = *(unsigned long *)cur[1];
    if (w0 != 0) {
        tlen = tag ? cL4_strlen((const char*)tag) : 0;
        cL4_mr_emit_tag(tcb + 0x2140, (const void*)tag, tlen, *(unsigned long *)(tcb + 0x2150));
        c = 'd'; cL4_mr_emit_byte(tcb + 0x2140, &c, *(unsigned long *)(tcb + 0x2150));
        cL4_mr_emit_num(tcb, (long)w0 - 1);
        cL4_mr_emit_num(tcb, (long)w1);
        return;
    }
    if (w1 != 0) {
        tlen = tag ? cL4_strlen((const char*)tag) : 0;
        cL4_mr_emit_tag(tcb + 0x2140, (const void*)tag, tlen, *(unsigned long *)(tcb + 0x2150));
        cL4_mr_emit_num(tcb, (long)w1 - 1);
        return;
    }
    cL4_mr_emit_byte(tcb + 0x2140, &byte, *(unsigned long *)(tcb + 0x2150));
}

/* 003d16b4 @ 0x3d16b4   (est. cL4_msg_emit_l)
 * Ghidra: void FUN_003d16b4(undefined4 *result, undefined8 tcb, long *msg)
 * Emit a numeric marker for a type-0x103/0x68 message (count = 1 for an
 * inline word, or the first payload word for kind-4); otherwise set error
 * code 0xb10/0xb12 with err=1. Confidence: medium. */
void cL4_msg_emit_l(int *result, unsigned long tcb, unsigned long *msg)
{
    short t = (short)msg[2];
    unsigned long v; int err = 0; unsigned long tail = 0; int code = 0;
    if ((t == 0x103) || (t == 0x68)) {
        if ((t != 0x68) != (*(char *)((long)msg + 0x12) == 4)) {
            if (*(char *)((long)msg + 0x12) == 4) v = *msg + 2;
            else v = 1;
            cL4_mr_emit_num(tcb, (long)v);
            goto out;
        }
        code = 0xb12;
    } else {
        code = 0xb10;
    }
    err = 1;
out:
    *result = err;
    *(unsigned long *)(result + 2) = tail;
    result[4] = code;
}

/* 003d1810 @ 0x3d1810   (est. cL4_msg_emit_tc2)
 * Ghidra: void FUN_003d1810(int *result, long tcb, long *msg, undefined1 byte, int depth)
 * Multi-slot emit: walk the argument list decoding each element of type 0x60
 * (emitting a "_" separator after the first), then for the remaining slots
 * emit the trailing byte and decode elements of type 0x162 and then all other
 * types. Failure to find any 0x60 element sets error code 0x6cf with err=1.
 * Confidence: low (multi-pass slot classification). */
void cL4_msg_emit_tc2(int *result, unsigned long tcb, unsigned long *msg, unsigned char byte, unsigned long depth)
{
    unsigned char k = *(unsigned char *)((long)msg + 0x12);
    unsigned long *cur = msg, *end; int first = 1, saw60 = 0; char c; int err = 0; unsigned long tail = 0; int code = 0;

    if (k - 1 < 2) {
        if (k == 1) end = msg + 1;
        else if (k == 2) end = msg + 2;
        else if (k == 5) end = (unsigned long*)*msg;
        else end = 0;
    } else {
        if (k != 5) { cur = 0; end = 0; }
        else { end = (unsigned long*)*msg; cur = end; }
        end = end + *(unsigned int *)(msg + 1);
    }
    if (cur != end) {
        do {
            if (*(short *)(*cur + 0x10) == 0x60) {
                cL4_msg_arg_index(result, tcb, (unsigned long*)*cur, 0, depth + 1);
                if (*result != 0) return;
                if (first) { c = '_'; cL4_mr_emit_byte(tcb + 0x2140, &c, *(unsigned long *)(tcb + 0x2150)); }
                first = 0; saw60 = 1;
            }
            cur = cur + 1;
        } while (cur != end);
        if (!saw60) { err = 1; code = 0x6cf; goto out; }
        c = 'T'; cL4_mr_emit_byte(tcb + 0x2140, &c, *(unsigned long *)(tcb + 0x2150));
        /* second pass: type 0x162 */
        {
            unsigned long *c2 = msg, *e2; unsigned char k2;
            k2 = *(unsigned char *)((long)msg + 0x12);
            if (k2 - 1 < 2) { if (k2==1) e2=msg+1; else if (k2==2) e2=msg+2; else if (k2==5) e2=(unsigned long*)*msg; else e2=0; }
            else { if (k2!=5){c2=0;e2=0;} else { e2=(unsigned long*)*msg; c2=e2; } e2=e2+*(unsigned int*)(msg+1); }
            for (; c2 != e2; c2 = c2 + 1) {
                if ((*(short *)(*c2 + 0x10) == 0x162) && (cL4_arg_decode(result, tcb, *c2, depth + 1), *result != 0)) return;
            }
        }
        cL4_mr_emit_byte(tcb + 0x2140, &byte, *(unsigned long *)(tcb + 0x2150));
        /* third pass: all other types */
        {
            unsigned long *c3 = msg, *e3; unsigned char k3; short s;
            k3 = *(unsigned char *)((long)msg + 0x12);
            if (k3 - 1 < 2) { if (k3==1) e3=msg+1; else if (k3==2) e3=msg+2; else if (k3==5) e3=(unsigned long*)*msg; else e3=0; }
            else { if (k3!=5){c3=0;e3=0;} else { e3=(unsigned long*)*msg; c3=e3; } e3=e3+*(unsigned int*)(msg+1); }
            for (; c3 != e3; c3 = c3 + 1) {
                s = *(short *)(*c3 + 0x10);
                if (((s != 0x60) && (s != 0x162)) && (cL4_arg_decode(result, tcb, *c3, depth + 1), *result != 0)) return;
            }
        }
        err = 0; tail = 0; code = 0;
    } else {
        err = 1; code = 0x6cf;
    }
out:
    *result = err;
    *(unsigned long *)(result + 2) = tail;
    result[4] = code;
}

/* 003d1ad4 @ 0x3d1ad4   (est. cL4_msg_emit_sym)
 * Ghidra: void FUN_003d1ad4(undefined8 tcb, undefined8 *msg, int which)
 * Emit a symbol name from the message: for `which`==0 use the raw (ptr,len)
 * pair; otherwise format it through cL4_fmt_make2 (handling negative-length
 * temporary ownership) before emitting. Commits the temp record.
 * Confidence: medium. */
void cL4_msg_emit_sym(unsigned long tcb, unsigned long *msg, int which)
{
    unsigned long tmp[2] = {0,0}; void *out; unsigned long len;
    if (cL4_fmt_begin(tcb, (unsigned long)msg, (unsigned char(*)[16])tmp, 1) & 1) return;
    if (which == 0) {
        cL4_msg_emit_sym_raw((unsigned long*)tcb, (long)msg[0], (long)msg[1]);
    } else {
        void *buf[2];
        cL4_fmt_make2(buf, msg[0], msg[1]);
        if (buf[0] == (void*)-1) out = buf;
        else out = buf[0];
        cL4_msg_emit_sym_raw((unsigned long*)tcb, (long)out, (long)buf[1]);
    }
    cL4_out_commit(tcb, (long*)tmp);
}
/* 003d1b88 @ 0x3d1b88   (est. cL4_msg_emit_sym_raw)
 * Ghidra: void FUN_003d1b88(undefined8 *tcb, long start, byte ******end)
 * The demangler symbol-emitter with back-references. When the object needs
 * special quoting it formats the node via cL4_fmt_node and emits it as a "00"
 * tagged record. Otherwise it scans the mangled identifier range
 * [start, end), tokenizing on `_`/punctuation, building an index table at
 * tcb+0x42c of {offset,len} entries, and emits each distinct identifier once
 * with a back-reference letter for repeats. Runs of repeated identifiers
 * between runs are collapsed. Confidence: low (complex two-pass tokenizer;
 * decompiler type noise on the pointer types). */
void cL4_msg_emit_sym_raw(unsigned long *tcb, long start, long end)
{
    unsigned int n = *(unsigned int *)(tcb + 0x42d);
    unsigned long nn = n;
    unsigned long tmp[3] = {0,0,0}; unsigned char c; long p;

    if ((*(char *)((long)tcb + 0x2159) == 1) && (cL4_fmt_need_quote(start, (unsigned long)end) != 0)) {
        unsigned long node[3] = {0,0,0}; unsigned long nn2;
        tmp[0] = 0; tmp[1] = 0; tmp[2] = 0;
        cL4_fmt_node(start, (unsigned long)end, &node, 1);
        nn2 = (node[1] >= 0) ? node[1] : (unsigned long)node[2];
        cL4_mr_emit_tag((unsigned long)tcb + 0x428, "00", 2, tcb[0x42a]);
        cL4_mr_emit_val2((unsigned long)tcb + 0x428, nn2, tcb[0x42a]);
        {
            char *s = (char*)((node[0] >= 0) ? (long)node[0] : (long)&node);
            if ((*s == '_') || ((unsigned char)*s - 0x30 < 10)) {
                c = '_';
                cL4_mr_emit_byte((unsigned long)tcb + 0x428, &c, tcb[0x42a]);
            }
            cL4_mr_emit_tag((unsigned long)tcb + 0x428, (char*)node[0], nn2, tcb[0x42a]);
        }
        return;
    }
    /* tokenizer pass: build index table of distinct identifiers */
    p = 0;
    {
        long run_start = -1; long last = 0; long i;
        for (i = 0; ; i = i + 1) {
            unsigned char ch = (p + start < end) ? *(unsigned char *)(p + start) : 0;
            if (run_start == -1) {
                /* not in a run */
                if (ch == 0) break;
                if ((ch == '_') || ((ch - 0x41 < 0x1a) && (*(unsigned char *)(p + start - 1) < 0x5b))) {
                    /* identifier start */
                    run_start = p;
                } else {
                    p = p + 1;
                    continue;
                }
            } else {
                /* inside a run */
                if (ch == 0) { /* run ends at end */ }
                else if ((ch == '_') || (ch == 0)) { /* end of token */ }
                else { p = p + 1; continue; }
            }
            /* emit the token [run_start, p) with dedup */
            {
                long tok = run_start, toklen = p - run_start;
                unsigned long j;
                int found = -1;
                for (j = 0; j < nn && j < n; j++) {
                    unsigned long e0 = *(unsigned long *)(tcb[0x42c] + 8 + j * 16);
                    if (*(unsigned long *)(tcb[0x42c] + j * 16) == 0 && e0 == 0) break;
                }
                /* search existing entries */
                for (j = 0; j < (unsigned long)n; j++) {
                    unsigned long *ent = (unsigned long*)(tcb[0x42c] + j * 16);
                    if ((toklen == ent[1]) &&
                        ((toklen == 0) || (cL4_memcmp((void*)(tok + start), (void*)(ent[0] + start), toklen) == 0))) {
                        found = (int)j; break;
                    }
                }
                if (found < 0) {
                    /* new entry */
                    unsigned long *ent = (unsigned long*)(tcb[0x42c] + n * 16);
                    ent[0] = tok; ent[1] = toklen;
                    n = n + 1;
                    cL4_grow_buffer(tcb + 0x42c, (unsigned long*)&ent, *tcb);
                } else {
                    /* back-reference */
                    unsigned long *ent = (unsigned long*)(tcb[0x42c] + found * 16);
                    cL4_grow_buffer(tcb + 0x42e, (unsigned long*)&ent, *tcb);
                }
            }
            run_start = -1;
            if (ch == 0) break;
            p = p + 1;
        }
    }
    /* emission pass */
    {
        unsigned int count = *(unsigned int *)(tcb + 0x42f);
        unsigned long k;
        if (count != 0) {
            c = '0'; cL4_mr_emit_byte((unsigned long)tcb + 0x428, &c, tcb[0x42a]);
        }
        for (k = 0; k < (unsigned long)count; k++) {
            unsigned long *ent = (unsigned long *)(tcb[0x42e] + k * 0x10);
            long run0 = (long)ent[0], run1;
            for (run1 = run0; run1 < (long)end; run1++) {
                unsigned char bv = *(unsigned char *)(run1 + start);
                unsigned long m;
                /* prefix-matched identifier letters */
                if (((bv & 1) ? 0 : (unsigned char)bv - 0x30) < 10) c = 'X';
                else c = (char)bv;
                cL4_mr_emit_byte((unsigned long)tcb + 0x428, &c, tcb[0x42a]);
            }
        }
        *(unsigned int *)(tcb + 0x42f) = 0;
    }
}

/* 003d2058 @ 0x3d2058   (est. cL4_grow_buffer)
 * Ghidra: void FUN_003d2058(long *buf, undefined8 *entry, undefined8 ctx)
 * Append a {ptr,len} entry to the growable 16-byte-element buffer `buf`
 * (guaranteeing capacity via cL4_grow_buffer_ensure), updating the count.
 * Confidence: high (structural). */
void cL4_grow_buffer(unsigned long *buf, unsigned long *entry, unsigned long ctx)
{
    unsigned int count = *(unsigned int *)(buf + 1);
    if (*(unsigned int *)((long)buf + 0xc) <= count) {
        cL4_grow_buffer_ensure(ctx, buf, (unsigned int *)((long)buf + 0xc), 1);
        count = *(unsigned int *)(buf + 1);
    }
    *(unsigned int *)(buf + 1) = count + 1;
    {
        unsigned long *dst = (unsigned long *)(*buf + (unsigned long)count * 0x10);
        dst[0] = entry[0];
        dst[1] = entry[1];
    }
}

/* 003d20bc @ 0x3d20bc   (est. cL4_grow_buffer_ensure)
 * Ghidra: void FUN_003d20bc(long alloc_ctx, long *buf, uint *cap, ulong need)
 * Ensure the growable buffer has room for `need` more 16-byte elements,
 * reallocating and copying existing elements when the inline tail has run
 * out. Confidence: high (classic growable-vector logic). */
void cL4_grow_buffer_ensure(unsigned long alloc_ctx, unsigned long *buf, unsigned int *cap, unsigned long need)
{
    unsigned int cur = *cap;
    unsigned long n = cur, newsize;
    if ((*buf + n * 0x10 == *(long *)(alloc_ctx + 8)) &&
        (newsize = *(long *)(alloc_ctx + 8) + need * 0x10, newsize <= *(unsigned long *)(alloc_ctx + 0x10))) {
        *(unsigned long *)(alloc_ctx + 8) = newsize;
    } else {
        if (need <= n << 1) need = (unsigned long)(n << 1);
        if (need < 5) need = 4;
        {
            unsigned long nb = cL4_grow_alloc(alloc_ctx, need + n);
            if (n != 0) cL4_memcpy((void*)nb, (void*)*buf, n << 4);
            *buf = nb;
            cur = *cap;
        }
    }
    *cap = cur + (int)need;
}

/* 003d216c @ 0x3d216c   (est. cL4_grow_alloc)
 * Ghidra: void FUN_003d216c(long buf, long elems)
 * Resize the growable buffer backing region to hold `elems` 16-byte elements,
 * updating the region's capacity pointers; allocates a fresh block when the
 * current tail cannot absorb the request. Confidence: high. */
unsigned long cL4_grow_alloc(unsigned long buf, unsigned long elems)
{
    unsigned long want = elems * 0x10;
    unsigned long tail = *(long *)(buf + 8) + 7 & 0xfffffffffffffff8;
    *(unsigned long *)(buf + 8) = tail;
    if ((tail == 0) || (*(unsigned long *)(buf + 0x10) < tail + want)) {
        unsigned long grow = *(long *)(buf + 0x20) * 2;
        unsigned long need = want | 8;
        if (grow < need || grow - need == 0) grow = need;
        *(unsigned long *)(buf + 0x20) = grow;
        {
            unsigned long *blk = (unsigned long*)cL4_alloc_grow(grow + 8, 0x2004093837f09);
            *blk = *(unsigned long *)(buf + 0x18);
            tail = (unsigned long)blk + 0xf & 0xfffffffffffffff8;
            *(unsigned long *)(buf + 0x10) = (unsigned long)blk + grow + 8;
            *(unsigned long **)(buf + 0x18) = blk;
        }
    }
    *(unsigned long *)(buf + 8) = tail + want;
    return tail;
}
/* 003d2214 @ 0x3d2214   (est. cL4_msg_emit_split)
 * Ghidra: void FUN_003d2214(int *result, long tcb, long *msg, undefined8 tag, undefined8 count, int depth)
 * Emit a two-phase split record: first decode every list element whose type
 * is not 0xe5 (emitting the caller's tag/count), then decode the remaining
 * 0xe5-typed elements. Confidence: medium. */
void cL4_msg_emit_split(int *result, unsigned long tcb, unsigned long *msg, unsigned long tag,
                        unsigned long count, unsigned long depth)
{
    unsigned char k = *(unsigned char *)((long)msg + 0x12);
    unsigned long *cur = msg, *end;
    if (k - 1 < 2) {
        if (k == 1) end = msg + 1;
        else if (k == 2) end = msg + 2;
        else if (k == 5) end = (unsigned long*)*msg;
        else end = 0;
    } else {
        if (k != 5) { cur = 0; end = 0; }
        else { end = (unsigned long*)*msg; cur = end; }
        end = end + *(unsigned int *)(msg + 1);
    }
    for (; cur != end; cur = cur + 1) {
        if ((*(short *)(*cur + 0x10) != 0xe5) && (cL4_arg_decode(result, tcb, *cur, depth + 1), *result != 0)) return;
    }
    cL4_mr_emit_tag(tcb + 0x2140, (const void*)tag, count, *(unsigned long *)(tcb + 0x2150));
    k = *(unsigned char *)((long)msg + 0x12);
    cur = msg;
    if (k - 1 < 2) {
        if (k == 1) end = msg + 1;
        else if (k == 2) end = msg + 2;
        else if (k == 5) end = (unsigned long*)*msg;
        else end = 0;
    } else {
        if (k != 5) { cur = 0; end = 0; }
        else { end = (unsigned long*)*msg; cur = end; }
        end = end + *(unsigned int *)(msg + 1);
    }
    while (1) {
        if (cur == end) { *result = 0; result[2] = 0; result[3] = 0; result[4] = 0; return; }
        if ((*(short *)(*cur + 0x10) == 0xe5) && (cL4_arg_decode(result, tcb, *cur, depth + 1), *result != 0)) break;
        cur = cur + 1;
    }
}

/* 003d23c4 @ 0x3d23c4   (est. cL4_msg_emit_pkt2)
 * Ghidra: void FUN_003d23c4(int *result, long tcb, long *msg, long nested, int flag, int depth)
 * Emit a packet: read the first element as a nested argument list, decode each
 * via cL4_msg_three (with "_" separators), then if `nested` is present decode
 * it via cL4_msg_one and emit tag "Xc"; otherwise emit tag "Xl" or a lone "p"
 * depending on `flag`. Confidence: low (nested-list walk). */
void cL4_msg_emit_pkt2(int *result, unsigned long tcb, unsigned long *msg, unsigned long nested,
                       int flag, unsigned long depth)
{
    unsigned long *elem; unsigned char b; unsigned long val; const char *tag; char c;
    if (1 < *(unsigned char *)((long)msg + 0x12) - 1) {
        if ((*(unsigned char *)((long)msg + 0x12) == 5) && ((int)msg[1] != 0)) msg = (unsigned long*)*msg;
        else msg = 0;
    }
    elem = (unsigned long*)*msg;
    b = *(unsigned char *)((long)elem + 0x12);
    {
        unsigned long *cur = elem, *end;
        if (b - 1 < 2) {
            if (b == 1) end = elem + 1;
            else if (b == 2) end = elem + 2;
            else if (b == 5) end = (unsigned long*)*elem;
            else end = 0;
        } else {
            if (b != 5) { cur = 0; end = 0; }
            else { end = (unsigned long*)*elem; cur = end; }
            end = end + *(unsigned int *)(elem + 1);
        }
        if (cur == end) {
            c = 0x79; cL4_mr_emit_byte(tcb + 0x2140, &c, *(unsigned long *)(tcb + 0x2150));
            if (nested != 0) goto nested_case;
            goto flag_case;
        }
        {
            int first = 1;
            do {
                cL4_msg_three(result, tcb, (long*)*cur, depth + 1);
                if (*result != 0) return;
                if (first) { c = '_'; cL4_mr_emit_byte(tcb + 0x2140, &c, *(unsigned long *)(tcb + 0x2150)); }
                first = 0;
                cur = cur + 1;
            } while (cur != end);
        }
        if (nested == 0) goto flag_case;
nested_case:
        cL4_msg_one(result, tcb, (long*)nested, depth + 2);
        if (*result != 0) return;
        val = *(unsigned long *)(tcb + 0x2150);
        tag = "Xc";
        goto emit;
flag_case:
        if (flag == 0) {
            c = 0x70; cL4_mr_emit_byte(tcb + 0x2140, &c, *(unsigned long *)(tcb + 0x2150));
            goto done;
        }
        val = *(unsigned long *)(tcb + 0x2150);
        tag = "Xl";
emit:
        cL4_mr_emit_tag(tcb + 0x2140, tag, 2, val);
    }
done:
    *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
}

/* 003d25a8 @ 0x3d25a8   (est. cL4_msg_emit_nested)
 * Ghidra: void FUN_003d25a8(int *result, long tcb, long *msg, undefined8 tag, undefined8 count, int depth)
 * Walk the argument list until an element of type 0x150 (sentinel) is found,
 * emitting the caller's tag/count, then decode the sentinel and the next three
 * elements separated by "p"/"r" markers. Confidence: medium. */
void cL4_msg_emit_nested(int *result, unsigned long tcb, unsigned long *msg, unsigned long tag,
                         unsigned long count, unsigned long depth)
{
    unsigned long *cur = msg, *end; unsigned char k; unsigned long v; char c;
    if (1 < *(unsigned char *)((long)msg + 0x12) - 1) {
        if (*(unsigned char *)((long)msg + 0x12) == 5) cur = (unsigned long*)*msg;
        else cur = 0;
    }
    while (1) {
        k = *(char *)((long)msg + 0x12);
        if (k == 5) end = (unsigned long*)(*msg + (unsigned long)*(unsigned int *)(msg + 1) * 8);
        else { unsigned long *p = 0; if (k == 1) p = msg + 1; end = msg + 2; if (k != 2) end = p; }
        if ((cur == end) || (*(short *)(*cur + 0x10) == 0x150)) break;
        cur = cur + 1;
        cL4_arg_decode(result, tcb, *cur, depth + 1);
        if (*result != 0) return;
    }
    cL4_mr_emit_tag(tcb + 0x2140, (const void*)tag, count, *(unsigned long *)(tcb + 0x2150));
    cL4_arg_decode(result, tcb, *cur, depth + 1);
    if (*result != 0) return;
    cL4_arg_decode(result, tcb, cur[1], depth + 1);
    if (*result != 0) return;
    c = 0x70; cL4_mr_emit_byte(tcb + 0x2140, &c, *(unsigned long *)(tcb + 0x2150));
    cL4_arg_decode(result, tcb, cur[2], depth + 1);
    if (*result != 0) return;
    c = 0x72; cL4_mr_emit_byte(tcb + 0x2140, &c, *(unsigned long *)(tcb + 0x2150));
    *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
}

/* 003d2740 @ 0x3d2740   (est. cL4_map_destroy)
 * Ghidra: long * FUN_003d2740(long *map)
 * Destroy the associative container: free every node in the overflow chains
 * hanging off the bucket array (each a 0x28-byte block), free the bucket
 * array, and reset the map to empty. Confidence: high (structural). */
void cL4_map_destroy(unsigned long *map)
{
    unsigned long *node = (unsigned long*)map[3]; unsigned long nxt;
    while (node != 0) {
        nxt = *node;
        cL4_free(node, 0x28);
        node = (unsigned long*)nxt;
    }
    {
        unsigned long base = *map;
        *map = 0;
        map[2] = -1;
        if (base != 0) cL4_free((void*)base, map[1] << 3);
    }
}

/* 003d27a0 @ 0x3d27a0   (est. cL4_map_keyeq)
 * Ghidra: undefined8 FUN_003d27a0(ulong *slot, ulong *key)
 * Compare a stored node's key payload against a lookup key: equal when the
 * stored hash (slot[1]) matches and the type-tag bits agree, dispatching to
 * the type-specific compare. Confidence: medium. */
unsigned long cL4_map_keyeq(unsigned long *slot, unsigned long *key)
{
    if (slot[1] == key[1]) {
        if ((((unsigned int)(*slot >> 2) & 1) == ((unsigned int)(*key >> 2) & 1))) {
            if ((((unsigned int)*slot >> 2) & 1) != 0)
                return cL4_map_key_eq_a(*slot & 0xfffffffffffffff8, *key & 0xfffffffffffffff8);
            return cL4_map_key_eq_b(slot, *slot & 0xfffffffffffffff8, *key & 0xfffffffffffffff8);
        }
    }
    return 0;
}

/* 003d27ec @ 0x3d27ec   (est. cL4_map_find)
 * Ghidra: long FUN_003d27ec(long *map, long key)
 * Look up `key` in the associative container, walking the bucket chain and
 * returning the matching node, or 0. Traps (SoftwareBreakpoint 0x3d28d8)
 * when the computed bucket index overflows the table. Confidence: medium. */
long cL4_map_find(unsigned long *map, unsigned long key)
{
    unsigned long cap = map[1], idx, hv = *(unsigned long *)(key + 8);
    if ((cap != 0) && (map[4] != 0)) {
        unsigned long mask = cap - 1;
        unsigned long *node;
        if ((cap & mask) == 0) idx = hv & mask;
        else { idx = hv; if (cap <= hv) { unsigned long d = 0; if (cap != 0) d = hv / cap; idx = hv - d * cap; } }
        if ((unsigned long)map[2] <= idx) { /* SoftwareBreakpoint trap 0x3d28d8 */ }
        node = *(unsigned long **)(*map + idx * 8);
        if (node != 0) {
            node = (unsigned long*)*node;
            do {
                if (node == 0) return 0;
                if (node[1] == hv) {
                    if ((cL4_map_keyeq(node + 2, (unsigned long*)key) & 1) != 0) return (long)node;
                } else {
                    unsigned long v = node[1];
                    if ((cap & mask) == 0) v = v & mask;
                    else if (cap <= v) { unsigned long d = 0; if (cap != 0) d = v / cap; v = v - d * cap; }
                    if (v != idx) return 0;
                }
                node = (unsigned long*)*node;
            } while (1);
        }
    }
    return 0;
}

/* 003d28d8 @ 0x3d28d8   (est. cL4_map_put)
 * Ghidra: long * FUN_003d28d8(long *map, long key, long *node)
 * Insert `node` (a 5-word {next, hash, k0, k1, k2} block) into the map keyed
 * by hash `key`, or return the existing node whose key compares equal. Grows
 * and rehashes when the load factor is exceeded. Traps (SoftwareBreakpoint
 * 0x3d2b14) on an out-of-range bucket index. Confidence: low (load-factor
 * growth + overflow-chain logic). */
unsigned long *cL4_map_put(unsigned long *map, unsigned long key, unsigned long *node)
{
    unsigned long hv = *(unsigned long *)(key + 8);
    unsigned long cap = map[1], idx; unsigned long *head;
    if (cap != 0) {
        unsigned long mask = cap - 1;
        if ((cap & mask) == 0) idx = mask & hv;
        else { idx = hv; if (cap <= hv) { unsigned long d = 0; if (cap != 0) d = hv / cap; idx = hv - d * cap; } }
        if ((unsigned long)map[2] <= idx) goto trap;
        head = *(unsigned long **)(*map + idx * 8);
        if (head != 0) {
            unsigned long *it = (unsigned long*)*head;
            for (; it != 0; it = (unsigned long*)*it) {
                unsigned long v = it[1];
                if (v == hv) {
                    if ((cL4_map_keyeq(it + 2, (unsigned long*)key) & 1) != 0) return it;
                } else {
                    if ((cap & mask) == 0) v = v & mask;
                    else if (cap <= v) { unsigned long d = 0; if (cap != 0) d = v / cap; v = v - d * cap; }
                    if (v != idx) break;
                }
            }
        }
    }
    node = (unsigned long*)cL4_alloc(0x28, 0x1020c006e8f4065);
    *node = 0;
    node[1] = hv;
    node[3] = node ? key : 0;
    {
        unsigned long *src = (unsigned long*)key;
        node[2] = src[0];
        node[4] = src[2];
    }
    if ((cap == 0) || (*(float *)(map + 5) * (float)cap < (float)(map[4] + 1))) {
        unsigned long nc;
        idx = 1;
        if (2 < cap) idx = (unsigned long)((cap & cap - 1) != 0);
        idx = idx | cap << 1;
        {
            unsigned long want = (float)(map[4] + 1) / *(float *)(map + 5);
            if (idx <= want) idx = want;
        }
        cL4_map_resize(map, idx);
        cap = map[1];
        {
            unsigned long mask = cap - 1;
            if ((cap & mask) == 0) idx = mask & hv;
            else { idx = hv; if (cap <= hv) { unsigned long d = 0; if (cap != 0) d = hv / cap; idx = hv - d * cap; } }
        }
    }
    {
        unsigned long count = map[2];
        if (idx < count) {
            unsigned long *slot = *(unsigned long **)(*map + idx * 8);
            if (slot == 0) {
                unsigned long *sent = map + 3;
                *node = *sent;
                *sent = (unsigned long)node;
                *(unsigned long **)(*map + idx * 8) = sent;
                if (*node != 0) {
                    unsigned long v = *(unsigned long *)(*node + 8);
                    unsigned long mask = cap - 1;
                    if ((cap & mask) == 0) v = v & mask;
                    else if (cap <= v) { unsigned long d = 0; if (cap != 0) d = v / cap; v = v - d * cap; }
                    if (count <= v) goto trap;
                    *(unsigned long **)(*map + v * 8) = node;
                }
            } else {
                *node = *slot;
                *slot = (unsigned long)node;
            }
            map[4] = map[4] + 1;
            return node;
        }
    }
trap:
    /* WARNING: does not return — SoftwareBreakpoint(1, 0x3d2b14) */
    return node;
}

/* 003d2b1c @ 0x3d2b1c   (est. cL4_demangle_kind)
 * Ghidra: char * FUN_003d2b1c(uint kind)
 * Return the printable name of a demangler node kind, looked up in the
 * 0x67c558 name table; kinds >= 0x17a fall back to the "Demangle::Node::"
 * placeholder. Confidence: high (string-table ref explicit). */
const char *cL4_demangle_kind(unsigned int kind)
{
    if (kind < 0x17a) return g_demangle_kind_names[kind];
    return "Demangle::Node::";
}

/* 003d2b40 @ 0x3d2b40   (est. cL4_demangle_node_ctx)
 * Ghidra: void FUN_003d2b40(undefined8 *out, undefined8 node)
 * Print a demangler node into the 3-word output record by delegating to
 * cL4_demangle_node at depth 0. Confidence: medium. */
void cL4_demangle_node_ctx(unsigned long *out, unsigned long node)
{
    unsigned long r[3] = {0,0,0};
    cL4_demangle_node((unsigned long)&r, (unsigned long*)node, 0);
    out[1] = r[1]; out[0] = r[0]; out[2] = r[2];
}

/* 003d2b90 @ 0x3d2b90   (est. cL4_demangle_node)
 * Ghidra: void FUN_003d2b90(undefined8 out, undefined8 *node, int depth)
 * Recursively print a demangler AST node into the output stream `out`:
 * indent by `depth` levels of spaces, print "kind=" plus the node's kind name,
 * and (for kind 3) its text payload, then recurse into children.
 * Confidence: high (string refs "kind=", ", text=\"", ", index=" explicit). */
void cL4_demangle_node(unsigned long out, unsigned long *node, unsigned long depth)
{
    unsigned int i;
    unsigned char k;
    for (i = (unsigned int)(depth << 1); i != 0; i = i - 1) cL4_out_putc(out, 0x20);
    if (node == 0) {
        cL4_out_puts(out, "<<NULL>>", 8);
        return;
    }
    cL4_out_puts(out, "kind=", 5);
    {
        const char *name = cL4_demangle_kind(*(unsigned short *)(node + 2));
        cL4_out_puts(out, name, cL4_strlen(name));
    }
    k = *(char *)((long)node + 0x12);
    if (k == 3) {
        cL4_out_puts(out, ", text=\"", 8);
        cL4_out_puts(out, (void*)node[0], node[1]);
        cL4_out_putc(out, 0x22);
        k = *(char *)((long)node + 0x12);
    }
    if (k == 4) {
        cL4_out_puts(out, ", index=", 8);
        cL4_fmt_put_index(out, node[0]);
    }
    cL4_out_putc(out, 10);
    {
        unsigned char b = *(unsigned char *)((long)node + 0x12);
        unsigned long *cur = node, *end;
        if (b - 1 < 2) {
            if (b == 1) end = node + 1;
            else if (b == 2) end = node + 2;
            else if (b == 5) end = (unsigned long*)*node;
            else end = 0;
        } else {
            if (b != 5) { cur = 0; end = 0; }
            else { end = (unsigned long*)*node; cur = end; }
            end = end + *(unsigned int *)(node + 1);
        }
        for (; cur != end; cur = cur + 1) cL4_demangle_node(out, (unsigned long*)*cur, depth + 1);
    }
}

/* 003d2d34 @ 0x3d2d34   (est. cL4_demangle_snprintf_alloc)
 * Ghidra: undefined8 FUN_003d2d34(long *out, undefined8 a, undefined8 b)
 * Format (a,b) with cL4_snprintf into a freshly allocated buffer sized to the
 * returned length; returns the byte count, or -1 on failure. Confidence: high
 * (snprintf-two-pass pattern). */
long cL4_demangle_snprintf_alloc(long *out, unsigned long a, unsigned long b)
{
    long n = cL4_snprintf(0, 0, (const char*)a, b);
    *out = 0;
    if (n >= 0) {
        char *buf = (char*)cL4_alloc_grow(n + 1, 0x100004077774924);
        if (buf != 0) {
            long r = cL4_snprintf(buf, n + 1, (const char*)a, b);
            if ((int)r >= 0) { *out = (long)buf; return r; }
            cL4_free(buf, 0);
        }
    }
    return 0xffffffff;
}

/* 003d2dd4 @ 0x3d2dd4   (est. cL4_log_sprintf)
 * Ghidra: void FUN_003d2dd4(undefined8 a, undefined8 b, undefined8 c, undefined8 d)
 * Build a "%s:%u: %s%s%" formatted message, log it, free the buffer, then
 * delegate to cL4_demangle_emit. Confidence: low (format exactness). */
void cL4_log_sprintf(unsigned long a, unsigned long b, unsigned long c, unsigned long d)
{
    unsigned long msg;
    cL4_fmt_build_str(&msg, "%.*s:%u: %.*s%s%", a, b, c, d);
    cL4_log_fmt(msg, msg);
    cL4_free((void*)msg, 0);
    cL4_demangle_emit(a, b, c, d);
}

/* 003d2e80 @ 0x3d2e80   (est. cL4_demangle_emit)
 * Ghidra: void FUN_003d2e80(void)
 * When logging is enabled, emit a formatted "%.*s" (or "%.*s: %.*s") record
 * depending on the third argument, then free it. Confidence: medium. */
void cL4_demangle_emit(unsigned long a, unsigned long b, unsigned long c, unsigned long d)
{
    unsigned long msg;
    const char *fmt;
    if (cL4_log_enabled() != 0) {
        msg = 0;
        if (c == 0) fmt = "%.*s";
        else fmt = "%.*s: %.*s";
        cL4_fmt_build_str(&msg, fmt, a, b, c, d);
        cL4_log(1, (const char*)msg, 0);
        cL4_free((void*)msg, 0);
    }
}

/* 003d1ad4 helper cL4_msg_emit_sym_raw is defined above (003d1b88). */
