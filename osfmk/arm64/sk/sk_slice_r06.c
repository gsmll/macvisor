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
extern void cL4_mr_emit_num(long tcb, long n);        /* FUN_003d05e0 */
extern unsigned long cL4_fmt_begin(unsigned long tcb, unsigned long msg, unsigned char (*desc)[16], unsigned long depth); /* FUN_003d0358 */
extern unsigned long cL4_fmt_emit_letter(unsigned long a, unsigned long tcb, char letter[3], unsigned long count, unsigned int flag); /* FUN_003d0650 */
extern unsigned char cL4_msg_decode(long tcb, long *msg);  /* FUN_003d0458 */
extern void cL4_msg_args(int *res, unsigned long tcb, long *msg, unsigned long depth); /* FUN_003d01ac */
extern void cL4_msg_one(int *res, unsigned long tcb, long *msg, unsigned long depth);  /* FUN_003d11d4 */
extern void cL4_msg_three(int *res, unsigned long tcb, long *msg, unsigned long depth);/* FUN_003d1218 */
extern void cL4_msg_parse(int *res, unsigned long *tcb, long *msg, unsigned long depth);/* FUN_003d12c8 */
extern void cL4_msg_emit_pair(unsigned long tcb, long *msg, unsigned long tag, unsigned char byte); /* FUN_003d154c */
extern void cL4_msg_dispatch2(int *res, unsigned long tcb, unsigned long msg, unsigned long tag, unsigned long count, unsigned long depth); /* FUN_003d174c */
extern void cL4_map_put(unsigned long map, long *node, unsigned long ctx); /* FUN_003d28d8 */
extern long cL4_map_find(long *map, unsigned long key);  /* FUN_003d27ec */
extern void cL4_map_destroy(long *map);                  /* FUN_003d2740 */
extern unsigned long cL4_map_keyeq(unsigned long *slot, unsigned long *key); /* FUN_003d27a0 */
extern const char *cL4_demangle_kind(unsigned int kind); /* FUN_003d2b1c */
extern void cL4_demangle_node(unsigned long out, unsigned long *node, unsigned long depth); /* FUN_003d2b90 */
extern long cL4_demangle_snprintf_alloc(long *out, unsigned long a, unsigned long b); /* FUN_003d2d34 */
extern void cL4_demangle_emit(unsigned long a, unsigned long b, unsigned long c, unsigned long d); /* FUN_003d2e80 */

/* The demangler node-kind name table lives at 0x67c558 (indexed by kind). */
extern const char *g_demangle_kind_names[0x17a]; /* _DAT_0067c558 */
/* 003ccd3c @ 0x003ccd3c   (est. cL4_ipc_emit_mb)
 * Ghidra: void FUN_003ccd3c(int *result, long tcb, void *msg, int depth)
 * Decode the single message word in `msg` (kind-1/5 check) and emit it as a
 * tagged IPC message-register record with tag "MB"; on parse error leave
 * the result word set, else clear it. Confidence: medium. Notes:  */
void cL4_ipc_emit_mb(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_one(result, tcb, (long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, &"MB", 2, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003ccd98 @ 0x003ccd98   (est. cL4_ipc_emit_mf)
 * Ghidra: void FUN_003ccd98(int *result, long tcb, void *msg, int depth)
 * Decode the single message word in `msg` (kind-1/5 check) and emit it as a
 * tagged IPC message-register record with tag "MF"; on parse error leave
 * the result word set, else clear it. Confidence: medium. Notes:  */
void cL4_ipc_emit_mf(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_one(result, tcb, (long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, &"MF", 2, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003ccdf4 @ 0x003ccdf4   (est. cL4_ipc_emit_ma)
 * Ghidra: void FUN_003ccdf4(int *result, long tcb, void *msg, int depth)
 * Decode the single message word in `msg` (kind-1/5 check) and emit it as a
 * tagged IPC message-register record with tag "MA"; on parse error leave
 * the result word set, else clear it. Confidence: medium. Notes:  */
void cL4_ipc_emit_ma(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_one(result, tcb, (long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, &"MA", 2, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003cce50 @ 0x003cce50   (est. cL4_ipc_emit_mc)
 * Ghidra: void FUN_003cce50(int *result, long tcb, void *msg, int depth)
 * Decode the single message word in `msg` (kind-1/5 check) and emit it as a
 * tagged IPC message-register record with tag "MC"; on parse error leave
 * the result word set, else clear it. Confidence: medium. Notes:  */
void cL4_ipc_emit_mc(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_one(result, tcb, (long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, &"MC", 2, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003ccf08 @ 0x003ccf08   (est. cL4_ipc_emit_tc)
 * Ghidra: void FUN_003ccf08(int *result, long tcb, void *msg, int depth)
 * Decode the single message word in `msg` (kind-1/5 check) and emit it as a
 * tagged IPC message-register record with tag "Tc"; on parse error leave
 * the result word set, else clear it. Confidence: medium. Notes:  */
void cL4_ipc_emit_tc(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_one(result, tcb, (long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, &"Tc", 2, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003ccfe0 @ 0x003ccfe0   (est. cL4_ipc_emit_tj)
 * Ghidra: void FUN_003ccfe0(int *result, long tcb, void *msg, int depth)
 * Decode the single message word in `msg` (kind-1/5 check) and emit it as a
 * tagged IPC message-register record with tag "Tj"; on parse error leave
 * the result word set, else clear it. Confidence: medium. Notes:  */
void cL4_ipc_emit_tj(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_one(result, tcb, (long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, &"Tj", 2, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003cd03c @ 0x003cd03c   (est. cL4_ipc_emit_tq)
 * Ghidra: void FUN_003cd03c(int *result, long tcb, void *msg, int depth)
 * Decode the single message word in `msg` (kind-1/5 check) and emit it as a
 * tagged IPC message-register record with tag "Tq"; on parse error leave
 * the result word set, else clear it. Confidence: medium. Notes:  */
void cL4_ipc_emit_tq(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_one(result, tcb, (long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, &"Tq", 2, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003ce4f8 @ 0x003ce4f8   (est. cL4_ipc_emit_mq)
 * Ghidra: void FUN_003ce4f8(int *result, long tcb, void *msg, int depth)
 * Decode the single message word in `msg` (kind-1/5 check) and emit it as a
 * tagged IPC message-register record with tag "MQ"; on parse error leave
 * the result word set, else clear it. Confidence: medium. Notes:  */
void cL4_ipc_emit_mq(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_one(result, tcb, (long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, &"MQ", 2, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003ce554 @ 0x003ce554   (est. cL4_ipc_emit_ho)
 * Ghidra: void FUN_003ce554(int *result, long tcb, void *msg, int depth)
 * Decode the single message word in `msg` (kind-1/5 check) and emit it as a
 * tagged IPC message-register record with tag "Ho"; on parse error leave
 * the result word set, else clear it. Confidence: medium. Notes:  */
void cL4_ipc_emit_ho(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_one(result, tcb, (long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, &"Ho", 2, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003ce5b0 @ 0x003ce5b0   (est. cL4_ipc_emit_mg)
 * Ghidra: void FUN_003ce5b0(int *result, long tcb, void *msg, int depth)
 * Decode the single message word in `msg` (kind-1/5 check) and emit it as a
 * tagged IPC message-register record with tag "Mg"; on parse error leave
 * the result word set, else clear it. Confidence: medium. Notes:  */
void cL4_ipc_emit_mg(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_one(result, tcb, (long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, &"Mg", 2, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003ce60c @ 0x003ce60c   (est. cL4_ipc_emit_mh)
 * Ghidra: void FUN_003ce60c(int *result, long tcb, void *msg, int depth)
 * Decode the single message word in `msg` (kind-1/5 check) and emit it as a
 * tagged IPC message-register record with tag "Mh"; on parse error leave
 * the result word set, else clear it. Confidence: medium. Notes:  */
void cL4_ipc_emit_mh(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_one(result, tcb, (long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, &"Mh", 2, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003ce668 @ 0x003ce668   (est. cL4_ipc_emit_mj)
 * Ghidra: void FUN_003ce668(int *result, long tcb, void *msg, int depth)
 * Decode the single message word in `msg` (kind-1/5 check) and emit it as a
 * tagged IPC message-register record with tag "Mj"; on parse error leave
 * the result word set, else clear it. Confidence: medium. Notes:  */
void cL4_ipc_emit_mj(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_one(result, tcb, (long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, &"Mj", 2, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003ce6c4 @ 0x003ce6c4   (est. cL4_ipc_emit_mk)
 * Ghidra: void FUN_003ce6c4(int *result, long tcb, void *msg, int depth)
 * Decode the single message word in `msg` (kind-1/5 check) and emit it as a
 * tagged IPC message-register record with tag "Mk"; on parse error leave
 * the result word set, else clear it. Confidence: medium. Notes:  */
void cL4_ipc_emit_mk(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_one(result, tcb, (long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, &"Mk", 2, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003ce8e4 @ 0x003ce8e4   (est. cL4_ipc_emit_mb2)
 * Ghidra: void FUN_003ce8e4(int *result, long tcb, void *msg, int depth)
 * Decode the single message word in `msg` (kind-1/5 check) and emit it as a
 * tagged IPC message-register record with tag "Mb"; on parse error leave
 * the result word set, else clear it. Confidence: medium. Notes:  */
void cL4_ipc_emit_mb2(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_one(result, tcb, (long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, &"Mb", 2, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003ce940 @ 0x003ce940   (est. cL4_ipc_emit_mk2)
 * Ghidra: void FUN_003ce940(int *result, long tcb, void *msg, int depth)
 * Decode the single message word in `msg` (kind-1/5 check) and emit it as a
 * tagged IPC message-register record with tag "MK"; on parse error leave
 * the result word set, else clear it. Confidence: medium. Notes:  */
void cL4_ipc_emit_mk2(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_one(result, tcb, (long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, &"MK", 2, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003ce99c @ 0x003ce99c   (est. cL4_ipc_emit_mn)
 * Ghidra: void FUN_003ce99c(int *result, long tcb, void *msg, int depth)
 * Decode the single message word in `msg` (kind-1/5 check) and emit it as a
 * tagged IPC message-register record with tag "MN"; on parse error leave
 * the result word set, else clear it. Confidence: medium. Notes:  */
void cL4_ipc_emit_mn(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_one(result, tcb, (long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, &"MN", 2, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003ce9f8 @ 0x003ce9f8   (est. cL4_ipc_emit_mj2)
 * Ghidra: void FUN_003ce9f8(int *result, long tcb, void *msg, int depth)
 * Decode the single message word in `msg` (kind-1/5 check) and emit it as a
 * tagged IPC message-register record with tag "MJ"; on parse error leave
 * the result word set, else clear it. Confidence: medium. Notes:  */
void cL4_ipc_emit_mj2(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_one(result, tcb, (long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, &"MJ", 2, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003cec20 @ 0x003cec20   (est. cL4_ipc_emit_mz)
 * Ghidra: void FUN_003cec20(int *result, long tcb, void *msg, int depth)
 * Decode the single message word in `msg` (kind-1/5 check) and emit it as a
 * tagged IPC message-register record with tag "Mz"; on parse error leave
 * the result word set, else clear it. Confidence: medium. Notes:  */
void cL4_ipc_emit_mz(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_one(result, tcb, (long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, &"Mz", 2, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003cf160 @ 0x003cf160   (est. cL4_ipc_emit_yk)
 * Ghidra: void FUN_003cf160(int *result, long tcb, void *msg, int depth)
 * Decode the single message word in `msg` (kind-1/5 check) and emit it as a
 * tagged IPC message-register record with tag "Yk"; on parse error leave
 * the result word set, else clear it. Confidence: medium. Notes:  */
void cL4_ipc_emit_yk(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_one(result, tcb, (long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, &"Yk", 2, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003cf28c @ 0x003cf28c   (est. cL4_ipc_emit_yt)
 * Ghidra: void FUN_003cf28c(int *result, long tcb, void *msg, int depth)
 * Decode the single message word in `msg` (kind-1/5 check) and emit it as a
 * tagged IPC message-register record with tag "Yt"; on parse error leave
 * the result word set, else clear it. Confidence: medium. Notes:  */
void cL4_ipc_emit_yt(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_one(result, tcb, (long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, &"Yt", 2, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003d003c @ 0x003d003c   (est. cL4_ipc_emit_yg)
 * Ghidra: void FUN_003d003c(int *result, long tcb, void *msg, int depth)
 * Decode the single message word in `msg` (kind-1/5 check) and emit it as a
 * tagged IPC message-register record with tag "Yg"; on parse error leave
 * the result word set, else clear it. Confidence: medium. Notes:  */
void cL4_ipc_emit_yg(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_one(result, tcb, (long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, &"Yg", 2, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003cceac @ 0x003cceac   (est. cL4_ipc_emit_fp)
 * Ghidra: void FUN_003cceac(int *result, long tcb, void *msg, int depth)
 * Decode the argument LIST in `msg` (each word via cL4_arg_decode) and emit a
 * tagged IPC record with tag "fp" carrying 2 words; clear result on
 * success. Confidence: medium. Notes:  */
void cL4_ipc_emit_fp(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_args(result, tcb, (long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, &"fp", 2, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003cd4e0 @ 0x003cd4e0   (est. cL4_ipc_emit_yk2)
 * Ghidra: void FUN_003cd4e0(int *result, long tcb, void *msg, int depth)
 * Decode the argument LIST in `msg` (each word via cL4_arg_decode) and emit a
 * tagged IPC record with tag "YK" carrying 2 words; clear result on
 * success. Confidence: medium. Notes:  */
void cL4_ipc_emit_yk2(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_args(result, tcb, (long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, &"YK", 2, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003ce888 @ 0x003ce888   (est. cL4_ipc_emit_mm)
 * Ghidra: void FUN_003ce888(int *result, long tcb, void *msg, int depth)
 * Decode the argument LIST in `msg` (each word via cL4_arg_decode) and emit a
 * tagged IPC record with tag "MM" carrying 2 words; clear result on
 * success. Confidence: medium. Notes:  */
void cL4_ipc_emit_mm(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_args(result, tcb, (long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, &"MM", 2, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003cea54 @ 0x003cea54   (est. cL4_ipc_emit_wz)
 * Ghidra: void FUN_003cea54(int *result, long tcb, void *msg, int depth)
 * Decode the argument LIST in `msg` (each word via cL4_arg_decode) and emit a
 * tagged IPC record with tag "WZ" carrying 2 words; clear result on
 * success. Confidence: medium. Notes:  */
void cL4_ipc_emit_wz(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_args(result, tcb, (long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, &"WZ", 2, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003ceab0 @ 0x003ceab0   (est. cL4_ipc_emit_wz2)
 * Ghidra: void FUN_003ceab0(int *result, long tcb, void *msg, int depth)
 * Decode the argument LIST in `msg` (each word via cL4_arg_decode) and emit a
 * tagged IPC record with tag "Wz" carrying 2 words; clear result on
 * success. Confidence: medium. Notes:  */
void cL4_ipc_emit_wz2(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_args(result, tcb, (long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, &"Wz", 2, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003cd5bc @ 0x003cd5bc   (est. cL4_ipc_emit_woy)
 * Ghidra: void FUN_003cd5bc(int *result, long tcb, void *msg, int depth)
 * Decode the argument LIST in `msg` (each word via cL4_arg_decode) and emit a
 * tagged IPC record with tag "WOy" carrying 3 words; clear result on
 * success. Confidence: medium. Notes:  */
void cL4_ipc_emit_woy(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_args(result, tcb, (long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, &"WOy", 3, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003cd674 @ 0x003cd674   (est. cL4_ipc_emit_wor)
 * Ghidra: void FUN_003cd674(int *result, long tcb, void *msg, int depth)
 * Decode the argument LIST in `msg` (each word via cL4_arg_decode) and emit a
 * tagged IPC record with tag "WOr" carrying 3 words; clear result on
 * success. Confidence: medium. Notes:  */
void cL4_ipc_emit_wor(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_args(result, tcb, (long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, &"WOr", 3, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003cd6d0 @ 0x003cd6d0   (est. cL4_ipc_emit_wos)
 * Ghidra: void FUN_003cd6d0(int *result, long tcb, void *msg, int depth)
 * Decode the argument LIST in `msg` (each word via cL4_arg_decode) and emit a
 * tagged IPC record with tag "WOs" carrying 3 words; clear result on
 * success. Confidence: medium. Notes:  */
void cL4_ipc_emit_wos(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_args(result, tcb, (long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, &"WOs", 3, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003cd72c @ 0x003cd72c   (est. cL4_ipc_emit_wob)
 * Ghidra: void FUN_003cd72c(int *result, long tcb, void *msg, int depth)
 * Decode the argument LIST in `msg` (each word via cL4_arg_decode) and emit a
 * tagged IPC record with tag "WOb" carrying 3 words; clear result on
 * success. Confidence: medium. Notes:  */
void cL4_ipc_emit_wob(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_args(result, tcb, (long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, &"WOb", 3, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003cd788 @ 0x003cd788   (est. cL4_ipc_emit_woc)
 * Ghidra: void FUN_003cd788(int *result, long tcb, void *msg, int depth)
 * Decode the argument LIST in `msg` (each word via cL4_arg_decode) and emit a
 * tagged IPC record with tag "WOc" carrying 3 words; clear result on
 * success. Confidence: medium. Notes:  */
void cL4_ipc_emit_woc(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_args(result, tcb, (long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, &"WOc", 3, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003cd7e4 @ 0x003cd7e4   (est. cL4_ipc_emit_wod)
 * Ghidra: void FUN_003cd7e4(int *result, long tcb, void *msg, int depth)
 * Decode the argument LIST in `msg` (each word via cL4_arg_decode) and emit a
 * tagged IPC record with tag "WOd" carrying 3 words; clear result on
 * success. Confidence: medium. Notes:  */
void cL4_ipc_emit_wod(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_args(result, tcb, (long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, &"WOd", 3, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003cd840 @ 0x003cd840   (est. cL4_ipc_emit_wof)
 * Ghidra: void FUN_003cd840(int *result, long tcb, void *msg, int depth)
 * Decode the argument LIST in `msg` (each word via cL4_arg_decode) and emit a
 * tagged IPC record with tag "WOf" carrying 3 words; clear result on
 * success. Confidence: medium. Notes:  */
void cL4_ipc_emit_wof(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_args(result, tcb, (long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, &"WOf", 3, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003cd89c @ 0x003cd89c   (est. cL4_ipc_emit_woh)
 * Ghidra: void FUN_003cd89c(int *result, long tcb, void *msg, int depth)
 * Decode the argument LIST in `msg` (each word via cL4_arg_decode) and emit a
 * tagged IPC record with tag "WOh" carrying 3 words; clear result on
 * success. Confidence: medium. Notes:  */
void cL4_ipc_emit_woh(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_args(result, tcb, (long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, &"WOh", 3, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003cfa08 @ 0x003cfa08   (est. cL4_ipc_emit_wog)
 * Ghidra: void FUN_003cfa08(int *result, long tcb, void *msg, int depth)
 * Decode the argument LIST in `msg` (each word via cL4_arg_decode) and emit a
 * tagged IPC record with tag "WOg" carrying 3 words; clear result on
 * success. Confidence: medium. Notes:  */
void cL4_ipc_emit_wog(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_args(result, tcb, (long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, &"WOg", 3, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003cfa64 @ 0x003cfa64   (est. cL4_ipc_emit_wob2)
 * Ghidra: void FUN_003cfa64(int *result, long tcb, void *msg, int depth)
 * Decode the argument LIST in `msg` (each word via cL4_arg_decode) and emit a
 * tagged IPC record with tag "WOB" carrying 3 words; clear result on
 * success. Confidence: medium. Notes:  */
void cL4_ipc_emit_wob2(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_args(result, tcb, (long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, &"WOB", 3, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003cfac0 @ 0x003cfac0   (est. cL4_ipc_emit_woc2)
 * Ghidra: void FUN_003cfac0(int *result, long tcb, void *msg, int depth)
 * Decode the argument LIST in `msg` (each word via cL4_arg_decode) and emit a
 * tagged IPC record with tag "WOC" carrying 3 words; clear result on
 * success. Confidence: medium. Notes:  */
void cL4_ipc_emit_woc2(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_args(result, tcb, (long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, &"WOC", 3, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003cfb1c @ 0x003cfb1c   (est. cL4_ipc_emit_wod2)
 * Ghidra: void FUN_003cfb1c(int *result, long tcb, void *msg, int depth)
 * Decode the argument LIST in `msg` (each word via cL4_arg_decode) and emit a
 * tagged IPC record with tag "WOD" carrying 3 words; clear result on
 * success. Confidence: medium. Notes:  */
void cL4_ipc_emit_wod2(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_args(result, tcb, (long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, &"WOD", 3, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003cfb78 @ 0x003cfb78   (est. cL4_ipc_emit_wof2)
 * Ghidra: void FUN_003cfb78(int *result, long tcb, void *msg, int depth)
 * Decode the argument LIST in `msg` (each word via cL4_arg_decode) and emit a
 * tagged IPC record with tag "WOF" carrying 3 words; clear result on
 * success. Confidence: medium. Notes:  */
void cL4_ipc_emit_wof2(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_args(result, tcb, (long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, &"WOF", 3, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003cfbd4 @ 0x003cfbd4   (est. cL4_ipc_emit_woh2)
 * Ghidra: void FUN_003cfbd4(int *result, long tcb, void *msg, int depth)
 * Decode the argument LIST in `msg` (each word via cL4_arg_decode) and emit a
 * tagged IPC record with tag "WOH" carrying 3 words; clear result on
 * success. Confidence: medium. Notes:  */
void cL4_ipc_emit_woh2(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_args(result, tcb, (long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, &"WOH", 3, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003cd098 @ 0x003cd098   (est. cL4_ipc_emit_tl)
 * Ghidra: void FUN_003cd098(int *result, long tcb, long *msg, int depth)
 * Read the first word of `msg` (deref through kind-5 array), decode it via
 * cL4_arg_decode, and emit tag "TL" (3 words) on success. Confidence:
 * medium. Notes:  */
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
        cL4_mr_emit_tag(tcb + 0x2140, &"TL", 3, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003cdb7c @ 0x003cdb7c   (est. cL4_ipc_emit_mxm)
 * Ghidra: void FUN_003cdb7c(int *result, long tcb, long *msg, int depth)
 * Read the first word of `msg` (deref through kind-5 array), decode it via
 * cL4_arg_decode, and emit tag "MXM" (3 words) on success. Confidence:
 * medium. Notes:  */
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
        cL4_mr_emit_tag(tcb + 0x2140, &"MXM", 3, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003cdc10 @ 0x003cdc10   (est. cL4_ipc_emit_mxe)
 * Ghidra: void FUN_003cdc10(int *result, long tcb, long *msg, int depth)
 * Read the first word of `msg` (deref through kind-5 array), decode it via
 * cL4_arg_decode, and emit tag "MXE" (3 words) on success. Confidence:
 * medium. Notes:  */
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
        cL4_mr_emit_tag(tcb + 0x2140, &"MXE", 3, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003ce7f4 @ 0x003ce7f4   (est. cL4_ipc_emit_qo)
 * Ghidra: void FUN_003ce7f4(int *result, long tcb, long *msg, int depth)
 * Read the first word of `msg` (deref through kind-5 array), decode it via
 * cL4_arg_decode, and emit tag "QO" (2 words) on success. Confidence:
 * medium. Notes:  */
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
        cL4_mr_emit_tag(tcb + 0x2140, &"QO", 2, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003cf418 @ 0x003cf418   (est. cL4_ipc_emit_mq2)
 * Ghidra: void FUN_003cf418(int *result, long tcb, long *msg, int depth)
 * Read the first word of `msg` (deref through kind-5 array), decode it via
 * cL4_arg_decode, and emit tag "Mq" (2 words) on success. Confidence:
 * medium. Notes:  */
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
        cL4_mr_emit_tag(tcb + 0x2140, &"Mq", 2, *(unsigned long *)(tcb + 0x2150));
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
        /* kind 1, 2, or 5 (small): elements follow the shape below */
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
void cL4_msg_one(int *result, unsigned long tcb, unsigned long *msg)
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
    if (cL4_msg_decode(tcb, (long*)msg)) {
        *result = 0; result[2] = 0; result[4] = 0;
        return;
    }
    cL4_msg_args(result, tcb, (long*)msg, depth);
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
    cL4_msg_args(result, tcb, (long*)msg, depth + 1);
    if (*result != 0) return;
    if (*(short *)(msg + 0x10) == 0xe8) {
        sel = "i";
    } else if (*(short *)(msg + 0x10) != 0x10b) {
        code = 0x2ce; err = 6; goto done;
    } else {
        sel = "v";
    }
    cL4_mr_emit_tag(tcb + 0x2140, sel, 1, *(unsigned long *)(tcb + 0x2150));
    cL4_mr_emit_tag(tcb + 0x2140, tag, count, *(unsigned long *)(tcb + 0x2150));
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

    if (!(cL4_msg_decode(tcb, (long*)msg) & 1)) {
        /* build output descriptor into *out */
        memcpy(desc, cL4_fmt_build(tcb, msg, depth), 16);
        memcpy(*out, desc, 16);
        kind = cL4_fmt_kind(tcb, out);
        if ((int)kind < 0) return 0;
        if (kind < 0x1a) {
            letter[0] = (char)kind + 'A';
            r = cL4_fmt_emit_letter(tcb + 0x2180, tcb, letter, 1, 0);
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
    unsigned long len;
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
    r = cL4_fmt_emit_letter(tcb + 0x2180, tcb, buf, ((unsigned long*)cur[1])[1], 1);
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
            k = (k <= b) ? k : b;   /* uVar2 = min */
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
