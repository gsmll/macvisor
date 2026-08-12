/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel,
 * arm64e, image base 0) — the cL4 microkernel. Ground truth: Ghidra FUN_ names +
 * addresses in program cl4_kernel.raw. Version "cL4 microkernel (cL4
 * (679.100.61))". All names are estimates unless string/header-matched.
 *
 * This file covers wave batch SKR14, slice 0x00404ac0-0x00405a78: a cL4
 * message / IPC syscall-dispatch cluster. The functions share a per-CPU/thread
 * context carried in the callee-saved registers (x20/x21/x22/x23); the x20
 * context is the syscall message frame (words at 0x10/0x18/0x20 = info/cap
 * fields, 0x28+ = extended args). They build on a family of 0x003f5xxx
 * message-buffer getters plus 0x00406xxx/0x00407xxx/0x00408xxx helpers that own
 * the append/commit/error logic (those bodies live in the sibling slices that
 * own those ranges). The trivial bodies that only tail-call FUN_00021480 are
 * reserved/unbound syscall slots.
 *
 * Many `*extraout_*` locals are caller-saved registers the decompiler could not
 * attribute; they flow through indirect (vtable / async-trampoline) calls.
 * Ghidra register artifacts (unaff_x20/x21/... ) are described in comments.
 */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "sk_internal.h"

/* 16-byte (two-word) result used by the return-by-value helpers below. */
typedef struct sk_r14_pair { uint64_t lo, hi; } sk_r14_pair_t;

/* ------------------------------------------------------------------ *
 * Out-of-range cL4/Swift-runtime helpers referenced by this slice.
 * FUN_ addresses in comments; bodies owned by sibling SK range workers.
 * Names are estimates.
 * ------------------------------------------------------------------ */

/* Shared message/syscall trampolines and Swift/async runtime thunks. */
extern word_t sk_h_00021480(void);                                   /* FUN_00021480 (unbound-syscall trap trampoline) */
extern cl4_result_t sk_h_00351da8(void);                             /* FUN_00351da8 (16-byte key/selector getter) */
extern void sk_h_0034b7e4(word_t a, word_t b, word_t c);             /* FUN_0034b7e4 */
extern word_t sk_h_003504c4(word_t a);                               /* FUN_003504c4 */
extern void sk_h_00350624(void *p);                                  /* FUN_00350624 */
extern void sk_h_003509c8(word_t a, word_t b, word_t c);             /* FUN_003509c8 */
extern void sk_h_003515b4(word_t a, word_t b, word_t c);             /* FUN_003515b4 */
extern void sk_h_00351790(void);                                     /* FUN_00351790 */
extern void sk_h_00350618(void);                                     /* FUN_00350618 */
extern cl4_result_t sk_h_003f406c(void);                             /* FUN_003f406c */
extern cl4_result_t sk_h_003f7e8c(void);                             /* FUN_003f7e8c */
extern void sk_h_003f7d48(void);                                     /* FUN_003f7d48 */
extern void sk_h_00350738(void);                                     /* FUN_00350738 */
extern void sk_h_0031de7c(void);                                     /* FUN_0031de7c */
extern void sk_h_0031b37c(void);                                     /* FUN_0031b37c */
extern void sk_h_00376820(void);                                     /* FUN_00376820 */
extern void sk_h_00270d80(void *out, void *in, word_t a, word_t b);  /* FUN_00270d80 */
extern void sk_h_001bb7a0(void *out, word_t n, word_t a, word_t b);  /* FUN_001bb7a0 */
extern cl4_result_t sk_h_003f7b44(word_t a, word_t b);               /* FUN_003f7b44 */
extern void sk_h_0028e8fc(word_t a, word_t b, word_t c, word_t d,
                          word_t e);                                 /* FUN_0028e8fc */
extern void sk_h_000bd3a4(void);                                     /* FUN_000bd3a4 */
extern void sk_h_001a29a0(word_t a, word_t b, word_t c);             /* FUN_001a29a0 */
extern word_t sk_h_003722e4(void);                                   /* FUN_003722e4 */
extern void sk_h_0031e5c8(word_t a, word_t b);                       /* FUN_0031e5c8 */
extern void sk_h_003f9234(void);                                     /* FUN_003f9234 (13-arg varargs marshaller) */
extern cl4_result_t sk_h_0001a1c8(word_t a, word_t b, word_t c);     /* thunk_FUN_0001a1c8 */
extern word_t sk_h_0025177c(void);                                   /* FUN_0025177c */
extern void sk_h_0035860c(void);                                     /* FUN_0035860c */
extern void sk_h_0034bb84(void);                                     /* FUN_0034bb84 */
extern void sk_h_001a8564(void);                                     /* FUN_001a8564 */
extern void sk_h_00351db4(void);                                     /* FUN_00351db4 */

/* Message-buffer getters / capacity checks. */
extern void sk_h_003f5ee8(word_t *out, word_t a, word_t b, word_t c); /* FUN_003f5ee8 */
extern void sk_h_003f60e4(word_t *out, word_t a, word_t b, word_t c); /* FUN_003f60e4 */
extern word_t sk_h_003f5cf0(void);                                   /* FUN_003f5cf0 (capacity cap) */
extern word_t sk_h_003f5e68(void);                                   /* FUN_003f5e68 */
extern word_t sk_h_003f5e78(word_t a, word_t b);                     /* FUN_003f5e78 */
extern word_t sk_h_003f5c00(word_t a);                               /* FUN_003f5c00 */
extern void sk_h_003f5c54(void);                                     /* FUN_003f5c54 */
extern cl4_result_t sk_h_003f5cc4(void);                             /* FUN_003f5cc4 (16-byte) */
extern void sk_h_003f55a0(word_t a, word_t b, word_t c);             /* FUN_003f55a0 */
extern void sk_h_003f5998(word_t a, word_t b, word_t c, word_t d);   /* FUN_003f5998 */
extern void sk_h_003f5ad4(word_t a, word_t b, word_t c, word_t d);   /* FUN_003f5ad4 */
extern void sk_h_003f6560(word_t a, word_t b, word_t c, word_t d);   /* FUN_003f6560 */
extern void sk_h_003f6f3c(word_t a, word_t b, word_t c, word_t d);   /* FUN_003f6f3c */
extern void sk_h_003f6fec(word_t a, word_t b, word_t c, word_t d);   /* FUN_003f6fec */
extern void sk_h_003f70f8(word_t a, word_t b, word_t c, word_t d,
                          word_t e);                                 /* FUN_003f70f8 */
extern void sk_h_003f6e08(word_t a, word_t b, word_t c);             /* FUN_003f6e08 */
extern void sk_h_003f6ea8(word_t a, word_t b, word_t c);             /* FUN_003f6ea8 */
extern void sk_h_003f709c(word_t a, word_t b, word_t c);             /* FUN_003f709c */
extern void sk_h_003f8264(word_t a, word_t b, word_t c);             /* FUN_003f8264 */
extern void sk_h_003f8f60(cl4_result_t r, word_t a, word_t b);       /* FUN_003f8f60 */
extern void sk_h_003f540c(void (*fn)(void), word_t *out);            /* FUN_003f540c */

/* Cap retain/release (sk_alloc family from sibling slices). */
extern void sk_h_0036b270(word_t a);                                 /* FUN_0036b270 (cap retain) */
extern void sk_h_0036b118(word_t a);                                 /* FUN_0036b118 (cap release) */

/* Error/fatal paths (noreturn). */
extern void sk_h_0040633c(void);                                     /* FUN_0040633c (error trap) */
extern void sk_h_00406310(word_t code);                              /* FUN_00406310 (error trap w/ code) */
extern void sk_h_004063f4(word_t code);                              /* FUN_004063f4 (error trap w/ code) */
extern void sk_h_004070cc(void);                                     /* FUN_004070cc */
extern void sk_h_00408238(void);                                     /* FUN_00408238 (context/cap getter) */
extern void sk_h_00347da8(void);                                     /* FUN_00347da8 (fatal prelude) */
extern void sk_h_003504b8(void);                                     /* FUN_003504b8 (fatal prelude) */
extern void sk_h_001afa84(void) __attribute__((noreturn));           /* FUN_001afa84 (fatal, noreturn) */
extern void sk_h_001afe4c(void) __attribute__((noreturn));           /* FUN_001afe4c (fatal, noreturn) */

/* Buffer append / commit helpers owned by 0x00406xxx-0x00408xxx slices. */
extern void sk_h_004064f8(word_t a, word_t b, word_t c);             /* FUN_004064f8 (msg word append) */
extern void sk_h_0040695c(word_t a, word_t b, word_t c);             /* FUN_0040695c (msg word append) */
extern void sk_h_00407894(void);                                     /* FUN_00407894 (commit) */
extern word_t sk_h_003f6278(void);                                   /* FUN_003f6278 (msg word read) */
extern void sk_h_00407d44(void);                                     /* FUN_00407d44 */
extern void sk_h_00407d24(void);                                     /* FUN_00407d24 */
extern void sk_h_00407e20(void);                                     /* FUN_00407e20 */
extern void sk_h_0040668c(void);                                     /* FUN_0040668c */
extern void sk_h_004066a4(void);                                     /* FUN_004066a4 */
extern void sk_h_00407324(void);                                     /* FUN_00407324 */
extern void sk_h_00408524(void);                                     /* FUN_00408524 */
extern void sk_h_004084e8(word_t a);                                 /* FUN_004084e8 */
extern void sk_h_004082d4(word_t v);                                 /* FUN_004082d4 (setter: *self = v) */
extern void sk_h_00407170(void);                                     /* FUN_00407170 (noop thunk) */
extern void sk_h_00359024(word_t a, word_t b, word_t c);             /* FUN_00359024 */
extern void sk_h_00350744(word_t a);                                 /* FUN_00350744 */
extern void sk_h_0034ba48(void);                                     /* FUN_0034ba48 */
extern void sk_h_000839d8(word_t a, word_t b, word_t c, word_t d);   /* FUN_000839d8 */
extern void sk_h_00350500(void);                                     /* FUN_00350500 */

/* Global indirect function pointer used by the dispatch preamble. */
extern void (*sk_g_dispatch_00658c80)(void);                         /* DAT_00658c80 */
extern word_t sk_g_string_0067f358;                                  /* 0x67f358 (const string ptr) */

/* ================================================================== *
 * Slice bodies.
 * ================================================================== */

/* FUN_00404ac0 @ 0x00404ac0  (est. sk_f_00404ac0_msg_dispatch)
 * Ghidra: void FUN_00404ac0(undefined8 param_1, undefined8 param_2,
 *                           undefined8 *param_3, undefined8 param_4, undefined8 param_5)
 * Message dispatch preamble: fetches a 16-byte key/selector (FUN_00351da8),
 * folds it through FUN_0034b7e4, invokes the global indirect handler
 * DAT_00658c80, then performs a message-buffer commit on *param_3
 * (FUN_003f5c00), runs an async helper (FUN_00407d44), spills the stack to a
 * 16-byte-aligned frame, issues an indirect tail call, and finally calls
 * FUN_003504c4 with a word taken from a per-context slot (x16+0x20) and a second
 * indirect tail. The extraout_* values are un-attributable caller-saved
 * registers that flow through the indirect calls.
 * Confidence: medium
 * Notes: DAT_00658c80 indirect fn ptr; register-flow artifacts (extraout_x1/
 *   x8/x9/x12/x16) retained in the body as opaque word locals.
 */
void sk_f_00404ac0(word_t param_1, word_t param_2, word_t *param_3,
                   word_t param_4, word_t param_5)
{
    cl4_result_t key;
    word_t out1, out8, out9, out16;
    word_t out12;

    key = sk_h_00351da8();
    sk_h_0034b7e4(key.hi, key.lo, key.lo);
    sk_g_dispatch_00658c80();
    sk_h_003f5c00(*param_3, out1, out8, param_5);
    sk_h_00407d44();
    /* spill to a 16-byte-aligned frame; offset depends on out12 register. */
    (void)out12;
    sk_h_00350624((void *)(out12 & ~0xfU));
    sk_h_00407d44_out9(out9);
    sk_h_003504c4(*(word_t *)(out16 + 0x20));
    sk_h_00407d44_out8(out8);
}

/* FUN_00404b8c @ 0x00404b8c  (est. sk_f_00404b8c_reserved_syscall)
 * Ghidra: void FUN_00404b8c(void)
 * Reserved/unbound syscall slot: simply tail-calls the shared unbound-syscall
 * trap trampoline FUN_00021480.
 * Confidence: medium
 */
void sk_f_00404b8c(void)
{
    sk_h_00021480();
}

/* FUN_00404ba4 @ 0x00404ba4  (est. sk_f_00404ba4)
 * Ghidra: void FUN_00404ba4(void)
 * Runs the noop thunk FUN_00407170, reads the message-info word at ctx+0x10 and
 * a value from ctx+0x18, resolves it through FUN_003f5c00, folds it with
 * FUN_003509c8, then makes an indirect call through a vtable slot (x16+0x10)
 * passing the message-info word. Registers unaff_x20 (ctx) and x16 (vtable).
 * Confidence: medium
 */
void sk_f_00404ba4(void)
{
    word_t info = sk_h_0035860c_msg_info(NULL);
    word_t info2 = 0, val;

    sk_h_00407170();
    info = sk_h_0035860c_get(ctx + 0x10);
    val = sk_h_003f5c00(sk_h_0035860c_get(ctx + 0x18));
    sk_h_003509c8(info, val, val);
    sk_h_00407d44_vtable_x16_10(info);
}

/* FUN_00404c08 @ 0x00404c08  (est. sk_f_00404c08)
 * Ghidra: void FUN_00404c08(void)
 * Reads the current context (x20) and a slot at ctx+0x18. Calls FUN_003f5e68 to
 * obtain a candidate value; if it equals the stored value at slot+8, or is zero,
 * writes 0 to the output byte (*x22); otherwise stores the candidate into
 * slot+8 and slot+0x10 and writes 1 to *x22 (a "state changed" flag).
 * Confidence: medium
 */
void sk_f_00404c08(void)
{
    long *slot = (long *)(ctx + 0x18);
    word_t candidate;
    uint8_t flag;

    sk_h_0035860c();
    candidate = sk_h_003f5e68();
    if (candidate == 0 || candidate == *(word_t *)(slot + 1)) {
        flag = 0;
    } else {
        *(word_t *)(slot + 1) = 0;
        *(word_t *)(slot + 2) = candidate;
        flag = 1;
    }
    *out_x22 = flag;
}

/* FUN_00404c60 @ 0x00404c60  (est. sk_f_00404c60)
 * Ghidra: void FUN_00404c60(void)
 * Thin wrapper that forwards to FUN_00404e60 (message-cap transfer).
 * Confidence: medium
 */
void sk_f_00404c60(void)
{
    sk_f_00404e60(0, 0, NULL);
}

/* FUN_00404c78 @ 0x00404c78  (est. sk_f_00404c78_msg_range)
 * Ghidra: void FUN_00404c78(undefined8 *param_1, long param_2)
 * Builds a message-range descriptor into the three-word output param_1
 * {cap, offset, size}. The input param_2 is a message descriptor holding a base
 * length at +8 and an offset at +0x10; total = base + offset. When the total is
 * non-negative, the output cap comes from ctx+0x18 (x20), the size is the total
 * capped by the buffer capacity (FUN_003f5cf0), and the cap is retained
 * (FUN_0036b270). A negative total triggers the error trap FUN_0040633c followed
 * by the noreturn fatal FUN_001afa84.
 * Confidence: medium
 */
void sk_f_00404c78(word_t *param_1, word_t *param_2)
{
    long offset = (long)param_2[2];          /* @ +0x10 */
    ulong total = (ulong)param_2[1] + (ulong)offset;  /* base @ +8 */

    if ((long)total >= 0) {
        word_t cap = *(word_t *)(ctx + 0x18);
        ulong size = sk_h_003f5cf0();
        if (total <= size) {
            size = total;
        }
        param_1[0] = cap;
        param_1[1] = (word_t)offset;
        param_1[2] = size;
        sk_h_0036b270(cap);
        return;
    }
    sk_h_0040633c();
    sk_h_001afa84();           /* noreturn */
}

/* FUN_00404cf4 @ 0x00404cf4  (est. sk_f_00404cf4_reserved_syscall)
 * Ghidra: void FUN_00404cf4(void)
 * Reserved/unbound syscall slot: tail-calls FUN_00021480.
 * Confidence: medium
 */
void sk_f_00404cf4(void)
{
    sk_h_00021480();
}

/* FUN_00404d0c @ 0x00404d0c  (est. sk_f_00404d0c_reserved_syscall)
 * Ghidra: void FUN_00404d0c(void)
 * Reserved/unbound syscall slot: tail-calls FUN_00021480.
 * Confidence: medium
 */
void sk_f_00404d0c(void)
{
    sk_h_00021480();
}

/* FUN_00404d24 @ 0x00404d24  (est. sk_f_00404d24)
 * Ghidra: void FUN_00404d24(undefined8 param_1, undefined8 param_2, undefined8 param_3)
 * Noop thunk, then forwards the message through FUN_003f5ad4 with the slot cap
 * (ctx+0x18), the incoming word param_3, and the info word (ctx+0x10), then runs
 * the setter FUN_004082d4.
 * Confidence: medium
 */
void sk_f_00404d24(word_t param_1, word_t param_2, word_t param_3)
{
    word_t out1 = 0;

    sk_h_00407170();
    sk_h_003f5ad4(*(word_t *)(ctx + 0x18), out1, param_3,
                  *(word_t *)(ctx + 0x10));
    sk_h_004082d4(0);
}

/* FUN_00404d54 @ 0x00404d54  (est. sk_f_00404d54)
 * Ghidra: void FUN_00404d54(undefined8 param_1, undefined8 param_2, undefined8 param_3)
 * Same shape as FUN_00404d24 but forwards through FUN_003f5998.
 * Confidence: medium
 */
void sk_f_00404d54(word_t param_1, word_t param_2, word_t param_3)
{
    word_t out1 = 0;

    sk_h_00407170();
    sk_h_003f5998(*(word_t *)(ctx + 0x18), out1, param_3,
                  *(word_t *)(ctx + 0x10));
    sk_h_004082d4(0);
}

/* FUN_00404d84 @ 0x00404d84  (est. sk_f_00404d84)
 * Ghidra: void FUN_00404d84(void)
 * Reads a 16-byte value from the context (FUN_0035860c), forwards it through
 * FUN_003f55a0 with the info word (ctx+0x10), then runs FUN_004082d4.
 * Confidence: medium
 */
void sk_f_00404d84(void)
{
    cl4_result_t v;

    v = sk_h_0035860c_pair();
    sk_h_003f55a0(v.lo, v.hi, *(word_t *)(ctx + 0x10));
    sk_h_004082d4(0);
}

/* FUN_00404dc8 @ 0x00404dc8  (est. sk_f_00404dc8)
 * Ghidra: void FUN_00404dc8(void)
 * Two-phase message fill. Reads the slot cap at ctx+0x18 and builds a message
 * via FUN_003f5ee8 with the extended args (ctx+0x20, ctx+0x10); commits the first
 * word through FUN_004064f8 (target slot+0x10) and FUN_00407894, then reads a
 * guard word with FUN_003f6278. Unless the guard byte local_48 equals 1, a second
 * word is committed and the guard re-read. (The *x20 context carries the
 * message buffer; local_48 is the "more messages" flag.)
 * Confidence: medium
 */
void sk_f_00404dc8(void)
{
    long slot = *(long *)(ctx + 0x18);
    word_t w0[4];
    uint8_t more = 0;
    word_t g;

    sk_h_003f5ee8(w0, (word_t)slot, *(word_t *)(ctx + 0x20),
                  *(word_t *)(ctx + 0x10));
    sk_h_004064f8(*(word_t *)(slot + 2), w0[0], w0[1]);
    sk_h_00407894();
    g = sk_h_003f6278();
    if (more != 1) {
        sk_h_004064f8(g, w0[2], w0[3]);
        sk_h_00407894();
        sk_h_003f6278();
    }
}

/* FUN_00404e60 @ 0x00404e60  (est. sk_f_00404e60_cap_transfer)
 * Ghidra: void FUN_00404e60(undefined8 param_1, undefined8 param_2, long *param_3)
 * Cap transfer: makes an indirect call through the handler at ctx+0x20 (x20);
 * if register x21 (a callee-saved result) is non-zero, stores it into *param_3.
 * Confidence: medium
 * Notes: unaff_x21 is a callee-saved register result (cap id / errno).
 */
void sk_f_00404e60(word_t param_1, word_t param_2, word_t *param_3)
{
    word_t x21 = ((void (*)(void))(*(word_t *)(ctx + 0x20)))();
    if (x21 != 0) {
        *param_3 = x21;
    }
}

/* FUN_00404e98 @ 0x00404e98  (est. sk_f_00404e98)
 * Ghidra: void FUN_00404e98(void)
 * Reads the info word (ctx+0x10) and a capability id from FUN_0025177c, then
 * writes the triple {cap, info, 0} to the output (*x22).
 * Confidence: medium
 */
void sk_f_00404e98(void)
{
    word_t info = *(word_t *)(ctx + 0x10);
    word_t cap;

    sk_h_0035860c();
    cap = sk_h_0025177c();
    out_x22[0] = cap;
    out_x22[1] = info;
    out_x22[2] = 0;
}

/* FUN_00404ed8 @ 0x00404ed8  (est. sk_f_00404ed8)
 * Ghidra: void FUN_00404ed8(void)
 * Two-phase message fill (mirror of FUN_00404dc8) using FUN_003f60e4 to build
 * the message and FUN_0040695c to commit words. Reads the slot cap at ctx+0x18
 * and the extended args (ctx+0x20, ctx+0x10); the local_38 guard byte controls
 * the second commit.
 * Confidence: medium
 */
void sk_f_00404ed8(void)
{
    long slot = *(long *)(ctx + 0x18);
    word_t w0[4];
    uint8_t more = 0;
    word_t g;

    g = sk_h_003f60e4(w0, (word_t)slot, *(word_t *)(ctx + 0x20),
                      *(word_t *)(ctx + 0x10));
    sk_h_0040695c(g, w0[0], w0[1]);
    sk_h_00407894();
    g = sk_h_003f6278();
    if (more != 1) {
        sk_h_0040695c(g, w0[2], w0[3]);
        sk_h_00407894();
        sk_h_003f6278();
    }
}

/* FUN_00404f60 @ 0x00404f60  (est. sk_f_00404f60)
 * Ghidra: void FUN_00404f60(void)
 * Reads the context (x20), builds a 16-byte result by calling thunk_FUN_0001a1c8
 * with the context's first two words and the info word (ctx+0x10), and stores
 * the result into the output (*x22).
 * Confidence: medium
 */
void sk_f_00404f60(void)
{
    word_t *ctx_words = (word_t *)ctx;
    cl4_result_t r;

    sk_h_0035860c();
    r = sk_h_0001a1c8(ctx_words[0], ctx_words[1], *(word_t *)(ctx + 0x10));
    out_x22_pair = r;
}

/* FUN_00404f98 @ 0x00404f98  (est. sk_f_00404f98)
 * Ghidra: void FUN_00404f98(void)
 * Reads a capability id from FUN_0025177c and a word from the slot at ctx+0x10
 * (+8), then writes the triple {cap, slot_word, 0} to the output (*x22).
 * Confidence: medium
 */
void sk_f_00404f98(void)
{
    long slot = *(long *)(ctx + 0x10);
    word_t cap;

    sk_h_0035860c();
    cap = sk_h_0025177c();
    out_x22[0] = cap;
    out_x22[1] = *(word_t *)(slot + 1);
    out_x22[2] = 0;
}

/* FUN_00404fdc @ 0x00404fdc  (est. sk_f_00404fdc)
 * Ghidra: void FUN_00404fdc(long param_1)
 * Validates a message-descriptor against the current slot (x20): succeeds only
 * when the caller's +8 field equals the slot's (ctx+0x18)+8 field and the +0x10
 * field is zero. On success builds the message with FUN_003f5ee8, commits a
 * first word through FUN_004064f8 and FUN_004084e8(0), and unless the local_38
 * guard is 1 commits a second word. On mismatch calls the error trap
 * FUN_004070cc + FUN_00406310(0x112) and the noreturn fatal FUN_001afa84.
 * Confidence: medium
 * Notes: 0x112 = error code constant.
 */
void sk_f_00404fdc(word_t param_1)
{
    word_t w0[4];
    uint8_t more = 0;
    word_t g;

    if ((*(word_t *)(param_1 + 8) == *(word_t *)(*(word_t *)(ctx + 0x18) + 8)) &&
        (*(word_t *)(param_1 + 0x10) == 0)) {
        g = sk_h_003f5ee8(w0, *(long *)(ctx + 0x18), *(word_t *)(ctx + 0x20),
                          *(word_t *)(ctx + 0x10));
        sk_h_004064f8(g, w0[0], w0[1]);
        g = sk_h_004084e8(0);
        if (more != 1) {
            sk_h_004064f8(g, w0[2], w0[3]);
            sk_h_004084e8(0);
        }
        return;
    }
    sk_h_004070cc();
    sk_h_00406310(0x112);
    sk_h_001afa84();          /* noreturn */
}

/* FUN_00405088 @ 0x00405088  (est. sk_f_00405088)
 * Ghidra: void FUN_00405088(undefined8 param_1, undefined8 param_2, undefined8 param_3)
 * Noop thunk, then forwards through FUN_003f6560 with the slot cap (ctx+0x18),
 * the incoming word param_3, and the info word (ctx+0x10).
 * Confidence: medium
 */
void sk_f_00405088(word_t param_1, word_t param_2, word_t param_3)
{
    word_t out1 = 0;

    sk_h_00407170();
    sk_h_003f6560(*(word_t *)(ctx + 0x18), out1, param_3,
                  *(word_t *)(ctx + 0x10));
}

/* FUN_004050b4 @ 0x004050b4  (est. sk_f_004050b4)
 * Ghidra: void FUN_004050b4(undefined8 param_1, undefined8 param_2, long *param_3)
 * Message append with bounds check. Computes end = param_3[1] + (ctx+0x10);
 * a negative end is a fatal error (FUN_0040633c + FUN_001afa84). If the buffer
 * start *param_3 is below end the message is appended (FUN_000839d8); otherwise
 * an in-capacity check against the buffer (ctx+0x10) either traps as a bounds
 * violation (FUN_00347da8 + FUN_003504b8 + fatal FUN_001afe4c) or, if the
 * indirect handler at ctx+0x20 accepts it (and register x21 is zero), appends
 * with the slot cap from ctx+0x18.
 * Confidence: medium
 * Notes: unaff_x21 register result; FUN_003f5c64 = capacity probe.
 */
void sk_f_004050b4(word_t param_1, word_t param_2, word_t *param_3)
{
    long ctxbuf = (long)(ctx + 0x10);
    long end = (long)param_3[1] + *(long *)(ctxbuf);
    word_t flag = 0;
    word_t out8;

    if (end < 0) {
        sk_h_0040633c();
        sk_h_001afa84();      /* noreturn */
    }
    {
        word_t slot_cap = *(word_t *)(ctx + 0x18);
        if ((long)*param_3 < end) {
            flag = 1;
        } else if (end < *(long *)(ctxbuf)) {
            sk_h_00347da8();
            sk_h_003504b8();
            sk_h_001afe4c();  /* noreturn */
        } else {
            void (*handler)(word_t) = *(void (**)(word_t))(ctx + 0x20);
            word_t x21;
            sk_h_003f5c64();
            x21 = handler(out8);
            if (x21 != 0) {
                return;
            }
            flag = 0;
        }
        sk_h_000839d8(out8, flag, 1, slot_cap);
    }
}

/* FUN_00405180 @ 0x00405180  (est. sk_f_00405180)
 * Ghidra: void FUN_00405180(undefined1 (*param_1)[16], undefined8 param_2,
 *                           undefined8 param_3)
 * Full message-buffer fill with growth. Reads the four context fields (info at
 * +0x10, slot cap at +0x18, base at +0x20, and a spare at +0x28). Builds a
 * message with FUN_003f5ee8, computes a working length (min of the context base
 * and a stack upper bound), and issues a first write batch
 * (FUN_00350500/FUN_0031de7c/FUN_00408524/FUN_00407324/FUN_00376820/FUN_0040668c/
 * FUN_00270d80/FUN_00407d24) into a 16-byte scratch. When the context base
 * exceeds the upper bound (and the local_68 guard is not 1) a second overrun
 * batch is appended (FUN_00350738/FUN_0028e8fc/FUN_001bb7a0/...). Finally the
 * cap is retained (FUN_0036b270) and the 16-byte result {cap_ptr, info, length}
 * is stored through param_1. Overflow is checked with SBORROW/SCARRY and the
 * fatal path FUN_00347da8+FUN_003504b8+FUN_001afe4c.
 * Confidence: medium
 * Notes: SoftwareBreakpoint(1, 0x405360/0x405364) overflow traps; heavy
 *   register-flow (extraout_*), structures approximated.
 */
void sk_f_00405180(sk_r14_pair_t *param_1, word_t param_2, word_t param_3)
{
    word_t info = *(word_t *)(ctx + 0x10);
    word_t slot = *(word_t *)(ctx + 0x18);
    long base = *(long *)(ctx + 0x20);
    word_t spare = *(word_t *)(ctx + 0x28);
    word_t w0[4];
    long len, len2;
    cl4_result_t r1, r2;
    sk_r14_pair_t out = {0, 0};

    sk_h_003f5ee8(w0, param_2, param_3, info);
    len = base;
    if (upper_bound <= base) {
        len = upper_bound;
    }
    /* First write batch. */
    sk_h_00350500();
    sk_h_0031de7c();
    sk_h_00408524();
    sk_h_00407324();
    sk_h_00376820(0, 0);
    sk_h_0040668c();
    sk_h_00270d80(&scratch, &len, 0, 0);
    sk_h_00407d24();
    r1 = sk_h_003f406c();
    sk_h_00350500();
    sk_h_0031b37c();
    sk_h_004066a4();
    sk_h_00376820(0, 0);
    sk_h_001bb7a0(&scratch, len, 0, 0);
    sk_h_00407d24();
    r2 = sk_h_003f7e8c();
    sk_h_003f7d48(r2.lo, r2.hi, r1.lo, r1.hi, info);

    len2 = len;
    if ((upper_bound < base) && (more_guard != 1)) {
        if (base - len < 0) { sk_h_overflow_trap_405360(); }
        len2 = base - len;
        if (cap2 <= base - len) { len2 = cap2; }
        if (len + len2 < len) {
            sk_h_00347da8();
            sk_h_003504b8();
            sk_h_001afe4c();  /* noreturn */
        }
        r1 = sk_h_00350738();
        sk_h_0028e8fc(r1.lo, r1.hi, slot, (word_t)base, info);
        r1 = sk_h_003f406c();
        sk_h_001bb7a0(&scratch, len2, 0, 0);
        sk_h_00407d24();
        r2 = sk_h_003f7e8c();
        sk_h_003f7d48(r2.lo, r2.hi, r1.lo, r1.hi, info);
    }
    {
        word_t cap = sk_h_0036b270(spare);
        sk_r14_pair_t res = sk_h_003f7b44(cap, (word_t)(len + len2));
        param_1->lo = res.lo;
        param_1->hi = res.hi;
    }
}

/* FUN_00405374 @ 0x00405374  (est. sk_f_00405374)
 * Ghidra: void FUN_00405374(undefined8 *param_1, long param_2)
 * Message-range getter. Validates the context offset (ctx+0x18) against the
 * descriptor length at param_2+8; on success computes the start via
 * FUN_003f5e78(ctx+0x18, param_2) and the size (FUN_003f5e68 / FUN_003f5cf0,
 * capped at the buffer limit), fills the output {cap(ctx+0x20), start, size},
 * and retains the cap (FUN_0036b270). Out-of-range triggers FUN_004070cc +
 * FUN_004063f4(0x2f) + noreturn fatal FUN_001afa84.
 * Confidence: medium
 * Notes: 0x2f = error code constant.
 */
void sk_f_00405374(word_t *param_1, word_t *param_2)
{
    long off = *(long *)(ctx + 0x18);
    word_t cap = *(word_t *)(ctx + 0x20);
    word_t start, size;

    if ((off >= 0) && (off <= (long)param_2[1])) {
        start = sk_h_003f5e78((word_t)off, (word_t)param_2);
        size = start;
        if ((off != (long)param_2[1]) &&
            (size = sk_h_003f5e68((word_t)param_2), size <= start)) {
            size = sk_h_003f5cf0((word_t)param_2);
        }
        param_1[0] = cap;
        param_1[1] = start;
        param_1[2] = size;
        sk_h_0036b270(cap);
        return;
    }
    sk_h_004070cc();
    sk_h_004063f4(0x2f);
    sk_h_001afa84();          /* noreturn */
}

/* FUN_0040542c @ 0x0040542c  (est. sk_f_0040542c)
 * Ghidra: void FUN_0040542c(undefined8 param_1, undefined8 param_2)
 * Registers FUN_0040548c as a callback via FUN_003f540c and runs the deferred
 * body FUN_00359024 with the two args plus the slot cap (ctx+0x18). The context
 * info (ctx+0x10) and the two params are staged on the stack for the callback.
 * Confidence: medium
 */
void sk_f_0040542c(word_t param_1, word_t param_2)
{
    word_t staged[3];

    staged[0] = *(word_t *)(ctx + 0x10);
    staged[1] = param_1;
    staged[2] = param_2;
    sk_h_00359024(param_1, param_2, *(word_t *)(ctx + 0x18));
    sk_h_003f540c(sk_f_0040548c, (word_t *)&staged);
}

/* FUN_0040548c @ 0x0040548c  (est. sk_f_0040548c)
 * Ghidra: void FUN_0040548c(long param_1, undefined8 param_2)
 * Message-buffer fill used as a deferred callback. Builds a message with
 * FUN_003f5ee8 (context info +0x10, slot cap at ctx+0x18), performs a first
 * write batch (FUN_00350500/FUN_0031de7c/FUN_00408524/FUN_00407324/
 * FUN_00376820/FUN_0040668c/FUN_00270d80), folds with FUN_003f406c/
 * FUN_00351790/FUN_00350618/FUN_003f7d48, then advances a running length counter
 * at ctx+0x20 by the written amount (with SCARRY overflow traps). Unless the
 * local_68 guard is 1, a second overrun batch (FUN_0028e8fc) appends the excess.
 * Finally asserts the total length equals param_1+8, else the error trap
 * FUN_004070cc + FUN_004063f4(0x6a) + noreturn fatal FUN_001afa84.
 * Confidence: medium
 * Notes: 0x6a = error code; SoftwareBreakpoint(1, 0x4055d4/0x4055d8/0x4055dc)
 *   overflow traps.
 */
void sk_f_0040548c(word_t param_1, word_t param_2)
{
    word_t info = *(word_t *)(ctx + 0x10);
    word_t *slot_cap = *(word_t **)(ctx + 0x18);
    word_t *counter = *(word_t **)(ctx + 0x20);
    word_t w0[4];
    uint8_t more = 0;
    word_t total;

    sk_h_003f5ee8(w0, param_1, param_2, info);
    /* First write batch. */
    sk_h_00350500();
    sk_h_0031de7c();
    sk_h_00408524();
    sk_h_00407324();
    sk_h_00376820(0, 0);
    sk_h_0040668c();
    sk_h_00270d80(&scratch, &w0, 0, 0);
    sk_h_003f406c(0, 0, 0, 0, info);
    sk_h_00351790();
    sk_h_00350618();
    sk_h_003f7d48();
    if ((word_t)(*counter) + (word_t)(w0_len) < (word_t)(*counter)) {
        sk_h_overflow_trap_4055d4();
    }
    *counter += w0_len;
    if (more != 1) {
        if (w0_len + w0_over < w0_len) {
            sk_h_00347da8();
            sk_h_003504b8();
            sk_h_001afe4c();  /* noreturn */
        }
        sk_h_0028e8fc(w0_len, w0_len + w0_over, slot_cap[0], slot_cap[1], info);
        sk_h_003f406c();
        sk_h_00351790();
        sk_h_000a6e14();
        sk_h_003f7d48();
        if ((word_t)(*counter) + (word_t)w0_over < (word_t)(*counter)) {
            sk_h_overflow_trap_4055dc();
        }
        *counter += w0_over;
    }
    total = *counter;
    if (total == *(word_t *)(param_1 + 8)) {
        return;
    }
    sk_h_004070cc();
    sk_h_004063f4(0x6a);
    sk_h_001afa84();          /* noreturn */
}

/* FUN_00405604 @ 0x00405604  (est. sk_f_00405604)
 * Ghidra: void FUN_00405604(void)
 * Dispatch helper: FUN_0034bb84, reads info (ctx+0x10), computes a value via
 * FUN_003f5e78(ctx+0x18) and FUN_000bd3a4, resolves FUN_003f5c00, folds with
 * FUN_003509c8, and makes an indirect call through vtable slot x16+0x10.
 * Confidence: medium
 */
void sk_f_00405604(void)
{
    word_t info = *(word_t *)(ctx + 0x10);
    word_t val;

    sk_h_0034bb84();
    sk_h_003f5e78(*(word_t *)(ctx + 0x18), 0);
    sk_h_000bd3a4();
    val = sk_h_003f5c00(0);
    sk_h_003509c8(info, val, val);
    sk_h_00407d44_vtable_x16_10(info);
}

/* FUN_0040567c @ 0x0040567c  (est. sk_f_0040567c)
 * Ghidra: void FUN_0040567c(undefined8 param_1, undefined8 param_2, long *param_3)
 * Cap-send append with bounds. Computes end = param_3[1] + (ctx+0x10); a
 * negative end is fatal (FUN_0040633c + FUN_001afa84). If the buffer start
 * *param_3 is below end the cap is appended (FUN_00350744 + FUN_000839d8);
 * otherwise a 16-byte cap descriptor is built via FUN_003f5cc4 and sent through
 * the indirect handler at ctx+0x20. If register x21 is zero, the descriptor is
 * folded with FUN_0034ba48 and appended (FUN_000839d8); finally FUN_003f8f60
 * re-validates the descriptor. In-capacity violation traps with the fatal path
 * FUN_00347da8+FUN_003504b8+FUN_001afe4c.
 * Confidence: medium
 */
void sk_f_0040567c(word_t param_1, word_t param_2, word_t *param_3)
{
    long ctxbuf = (long)(ctx + 0x10);
    long end = (long)param_3[1] + *(long *)(ctxbuf);

    if (end < 0) {
        sk_h_0040633c();
        sk_h_001afa84();      /* noreturn */
    }
    if ((long)*param_3 < end) {
        sk_h_00350744(0);
        sk_h_000839d8(0, 0, 0, 0);
    } else {
        if (end < *(long *)(ctxbuf)) {
            sk_h_00347da8();
            sk_h_003504b8();
            sk_h_001afe4c();  /* noreturn */
        }
        {
            cl4_result_t desc = sk_h_003f5cc4();
            void (*handler)(word_t, cl4_result_t) =
                *(void (**)(word_t, cl4_result_t))(ctx + 0x20);
            word_t x21;
            x21 = handler(0, desc);
            if (x21 == 0) {
                sk_h_0034ba48();
                sk_h_000839d8(0, 0, 0, 0);
            }
            sk_h_003f8f60(desc, desc.lo, desc.hi);
        }
    }
}

/* FUN_00405778 @ 0x00405778  (est. sk_f_00405778)
 * Ghidra: void FUN_00405778(void)
 * Chains several message helpers: FUN_00407e20, FUN_003f5e78, FUN_003504c4,
 * FUN_003f5c54, FUN_00351790, and finally FUN_0031e5c8 with the two values.
 * Confidence: medium
 */
void sk_f_00405778(void)
{
    word_t a = sk_h_00407e20();
    word_t b = sk_h_003f5e78(0, 0);

    sk_h_003504c4(0);
    sk_h_003f5c54();
    sk_h_00351790();
    sk_h_0031e5c8(a, b);
}

/* FUN_004057e0 @ 0x004057e0  (est. sk_f_004057e0)
 * Ghidra: void FUN_004057e0(undefined8 param_1, undefined8 param_2)
 * Marshals thirteen words from the context (x20 offsets 0x10..0x60) plus the two
 * explicit params into the variadic helper FUN_003f9234 (a 13-arg marshaller).
 * Confidence: medium
 */
void sk_f_004057e0(word_t param_1, word_t param_2)
{
    sk_h_003f9234(param_1, param_2,
                  *(word_t *)(ctx + 0x28), *(word_t *)(ctx + 0x30),
                  *(word_t *)(ctx + 0x38), *(word_t *)(ctx + 0x40),
                  *(word_t *)(ctx + 0x48), *(word_t *)(ctx + 0x50),
                  *(word_t *)(ctx + 0x58), *(word_t *)(ctx + 0x60),
                  *(word_t *)(ctx + 0x10), *(word_t *)(ctx + 0x18),
                  *(word_t *)(ctx + 0x20));
}

/* FUN_00405830 @ 0x00405830  (est. sk_f_00405830_reserved_syscall)
 * Ghidra: void FUN_00405830(void)
 * Reserved/unbound syscall slot: tail-calls FUN_00021480.
 * Confidence: medium
 */
void sk_f_00405830(void)
{
    sk_h_00021480();
}

/* FUN_00405848 @ 0x00405848  (est. sk_f_00405848)
 * Ghidra: void FUN_00405848(void)
 * Dispatch helper referencing a global string at 0x67f358. Reads info (ctx+0x10)
 * and a value via FUN_003f5e78(ctx+0x18), calls FUN_003515b4(0, 0x67f358, info),
 * reads a per-CPU slot at FUN_003722e4()+0x30 into an index, writes the value to
 * *x24, folds with FUN_000bd3a4 + FUN_003f5c00, and calls FUN_001a29a0 on the
 * indexed output.
 * Confidence: medium
 * Notes: 0x67f358 const-string reference; FUN_003722e4 = per-CPU base.
 */
void sk_f_00405848(void)
{
    word_t info = *(word_t *)(ctx + 0x10);
    word_t val = sk_h_003f5e78(*(word_t *)(ctx + 0x18), 0);
    int idx;

    sk_h_0034bb84();
    sk_h_003515b4(0, sk_g_string_0067f358, info);
    idx = *(int *)(sk_h_003722e4() + 0x30);
    out_x24 = val;
    sk_h_000bd3a4(val);
    val = sk_h_003f5c00(0);
    sk_h_001a29a0((word_t)(out_x24_ptr) + (word_t)idx, val, info);
}

/* FUN_004058d4 @ 0x004058d4  (est. sk_f_004058d4)
 * Ghidra: void FUN_004058d4(undefined8 param_1, undefined8 param_2)
 * Forwards to the dispatch preamble FUN_00404ac0 with the context's slot
 * (ctx+0x18), extended arg (ctx+0x20), and info (ctx+0x10).
 * Confidence: medium
 */
void sk_f_004058d4(word_t param_1, word_t param_2)
{
    sk_f_00404ac0(param_1, param_2, (word_t *)(ctx + 0x18),
                  *(word_t *)(ctx + 0x20), *(word_t *)(ctx + 0x10));
}

/* FUN_00405904 @ 0x00405904  (est. sk_f_00405904)
 * Ghidra: void FUN_00405904(void)
 * Chains FUN_00407e20, FUN_000bd3a4, FUN_003f5c00, FUN_003509c8, then an indirect
 * call through vtable slot x16+0x18.
 * Confidence: medium
 */
void sk_f_00405904(void)
{
    sk_h_00407e20();
    sk_h_000bd3a4();
    sk_h_003f5c00(0);
    sk_h_003509c8(0, 0, 0);
    sk_h_00407d44_vtable_x16_18();
}

/* FUN_00405968 @ 0x00405968  (est. sk_f_00405968)
 * Ghidra: void FUN_00405968(undefined8 param_1, undefined8 param_2)
 * Forwards the two params plus the info word (ctx+0x10) through FUN_003f709c.
 * Confidence: medium
 */
void sk_f_00405968(word_t param_1, word_t param_2)
{
    sk_h_003f709c(param_1, param_2, *(word_t *)(ctx + 0x10));
}

/* FUN_00405994 @ 0x00405994  (est. sk_f_00405994)
 * Ghidra: void FUN_00405994(undefined8 param_1, undefined8 param_2, undefined8 param_3)
 * Noop thunk, then forwards through FUN_003f6f3c with the slot cap (ctx+0x18),
 * the incoming word param_3, and the info word (ctx+0x10).
 * Confidence: medium
 */
void sk_f_00405994(word_t param_1, word_t param_2, word_t param_3)
{
    word_t out1 = 0;

    sk_h_00407170();
    sk_h_003f6f3c(*(word_t *)(ctx + 0x18), out1, param_3,
                  *(word_t *)(ctx + 0x10));
}

/* FUN_004059c0 @ 0x004059c0  (est. sk_f_004059c0)
 * Ghidra: void FUN_004059c0(undefined8 param_1, undefined8 param_2)
 * Forwards the two params plus the info word (ctx+0x10) through FUN_003f6e08.
 * Confidence: medium
 */
void sk_f_004059c0(word_t param_1, word_t param_2)
{
    sk_h_003f6e08(param_1, param_2, *(word_t *)(ctx + 0x10));
}

/* FUN_004059ec @ 0x004059ec  (est. sk_f_004059ec)
 * Ghidra: void FUN_004059ec(undefined8 param_1, undefined8 param_2, undefined8 param_3)
 * Noop thunk, then forwards through FUN_003f6fec with the slot cap (ctx+0x18),
 * the incoming word param_3, and the info word (ctx+0x10).
 * Confidence: medium
 */
void sk_f_004059ec(word_t param_1, word_t param_2, word_t param_3)
{
    word_t out1 = 0;

    sk_h_00407170();
    sk_h_003f6fec(*(word_t *)(ctx + 0x18), out1, param_3,
                  *(word_t *)(ctx + 0x10));
}

/* FUN_00405a18 @ 0x00405a18  (est. sk_f_00405a18)
 * Ghidra: void FUN_00405a18(undefined8 param_1, undefined8 param_2)
 * Forwards the two params plus the info word (ctx+0x10) through FUN_003f6ea8.
 * Confidence: medium
 */
void sk_f_00405a18(word_t param_1, word_t param_2)
{
    sk_h_003f6ea8(param_1, param_2, *(word_t *)(ctx + 0x10));
}

/* FUN_00405a44 @ 0x00405a44  (est. sk_f_00405a44)
 * Ghidra: void FUN_00405a44(undefined8 param_1, undefined8 param_2,
 *                           undefined8 param_3, undefined8 param_4)
 * Calls FUN_00408238 (context getter), then forwards the two context caps
 * (ctx+0x18, ctx+0x20), the two explicit params, and the info word (ctx+0x10)
 * through FUN_003f70f8.
 * Confidence: medium
 */
void sk_f_00405a44(word_t param_1, word_t param_2, word_t param_3, word_t param_4)
{
    sk_h_00408238();
    sk_h_003f70f8(*(word_t *)(ctx + 0x18), *(word_t *)(ctx + 0x20),
                  param_3, param_4, *(word_t *)(ctx + 0x10));
}

/* FUN_00405a78 @ 0x00405a78  (est. sk_f_00405a78)
 * Ghidra: void FUN_00405a78(undefined8 param_1, undefined8 param_2)
 * Slice grow helper. Reads info (ctx+0x10) and a length (ctx+0x20), runs
 * FUN_003f8264 with the length, the first word of the slot cap (ctx+0x18), and
 * info; if length+1 does not overflow it forwards length, length+1, and the two
 * params through FUN_003f70f8; otherwise the fatal path FUN_00347da8 +
 * FUN_003504b8 + FUN_001afe4c. SCARRY overflow checked at 0x405afc.
 * Confidence: medium
 */
void sk_f_00405a78(word_t param_1, word_t param_2)
{
    word_t info = *(word_t *)(ctx + 0x10);
    long length = *(long *)(ctx + 0x20);

    sk_h_003f8264((word_t)length, **(word_t **)(ctx + 0x18), info);
    if ((word_t)length > (word_t)(length + 1)) {
        sk_h_overflow_trap_405afc();
    }
    if (length <= length + 1) {
        sk_h_003f70f8((word_t)length, (word_t)(length + 1), param_1, param_2,
                      info);
        return;
    }
    sk_h_00347da8();
    sk_h_003504b8();
    sk_h_001afe4c();          /* noreturn */
}
