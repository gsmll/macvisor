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
extern cl4_result_t sk_h_003f406c();                                 /* FUN_003f406c (varargs) */
extern cl4_result_t sk_h_003f7e8c(void);                             /* FUN_003f7e8c */
extern void sk_h_003f7d48();                                         /* FUN_003f7d48 (varargs) */
extern cl4_result_t sk_h_00350738();                                 /* FUN_00350738 (16-byte result) */
extern void sk_h_0031de7c(void);                                     /* FUN_0031de7c */
extern void sk_h_0031b37c(void);                                     /* FUN_0031b37c */
extern void sk_h_00376820();                                         /* FUN_00376820 (varargs) */
extern void sk_h_00270d80(void *out, void *in, word_t a, word_t b);  /* FUN_00270d80 */
extern void sk_h_001bb7a0(void *out, word_t n, word_t a, word_t b);  /* FUN_001bb7a0 */
extern cl4_result_t sk_h_003f7b44(word_t a, word_t b);               /* FUN_003f7b44 */
extern void sk_h_0028e8fc(word_t a, word_t b, word_t c, word_t d,
                          word_t e);                                 /* FUN_0028e8fc */
extern void sk_h_000bd3a4();                                           /* FUN_000bd3a4 (varargs) */
extern void sk_h_001a29a0(word_t a, word_t b, word_t c);             /* FUN_001a29a0 */
extern word_t sk_h_003722e4(void);                                   /* FUN_003722e4 */
extern void sk_h_0031e5c8(word_t a, word_t b);                       /* FUN_0031e5c8 */
extern void sk_h_003f9234();                                           /* FUN_003f9234 (13-arg varargs marshaller) */
extern cl4_result_t sk_h_0001a1c8(word_t a, word_t b, word_t c);     /* thunk_FUN_0001a1c8 */
extern word_t sk_h_0025177c(void);                                   /* FUN_0025177c */
extern void sk_h_0035860c(void);                                     /* FUN_0035860c */
extern cl4_result_t sk_h_0035860c_pair(void);                        /* FUN_0035860c (16-byte reg pair) */
extern word_t sk_h_003f5c64();                                       /* FUN_003f5c64 (capacity probe) */
extern void sk_h_0034bb84(void);                                     /* FUN_0034bb84 */
extern word_t sk_h_001a8564();                                        /* FUN_001a8564 (returns word) */
extern void sk_h_00351db4(void);                                     /* FUN_00351db4 */

/* Message-buffer getters / capacity checks. */
extern word_t sk_h_003f5ee8(word_t *out, word_t a, word_t b, word_t c); /* FUN_003f5ee8 */
extern word_t sk_h_003f60e4(word_t *out, word_t a, word_t b, word_t c); /* FUN_003f60e4 */
extern word_t sk_h_003f5cf0();                                         /* FUN_003f5cf0 (capacity cap, varargs) */
extern word_t sk_h_003f5e68();                                         /* FUN_003f5e68 (varargs) */
extern word_t sk_h_003f5e78();                                         /* FUN_003f5e78 (varargs) */
extern word_t sk_h_003f5c00();                                /* FUN_003f5c00 (varargs) */
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
extern void sk_h_003f540c(void (*fn)(), word_t *out);                /* FUN_003f540c */

/* Cap retain/release (sk_alloc family from sibling slices). */
extern word_t sk_h_0036b270();                                         /* FUN_0036b270 (cap retain, varargs) */
extern void sk_h_0036b118();                                          /* FUN_0036b118 (cap release, varargs) */

/* Error/fatal paths (noreturn). */
extern void sk_h_0040633c(void);                                     /* FUN_0040633c (error trap) */
extern void sk_h_00406310(word_t code);                              /* FUN_00406310 (error trap w/ code) */
extern void sk_h_004063f4(word_t code);                              /* FUN_004063f4 (error trap w/ code) */
extern void sk_h_004070cc(void);                                     /* FUN_004070cc */
extern word_t sk_h_00408238(void);                                     /* FUN_00408238 (context/cap getter) */
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
extern void sk_h_00407d44_vtable_x16_10();                           /* (**(code **)(x16+0x10))() */
extern void sk_h_00407d44_vtable_x16_18();                           /* (**(code **)(x16+0x18))() */
extern void sk_h_00407d24(void);                                     /* FUN_00407d24 */
extern word_t sk_h_00407e20();                                        /* FUN_00407e20 (returns value) */
extern void sk_h_0040668c(void);                                     /* FUN_0040668c */
extern void sk_h_004066a4(void);                                     /* FUN_004066a4 */
extern void sk_h_00407324(void);                                     /* FUN_00407324 */
extern void sk_h_00408524(void);                                     /* FUN_00408524 */
extern word_t sk_h_004084e8(word_t a);                                /* FUN_004084e8 */
extern void sk_h_004082d4(word_t v);                                 /* FUN_004082d4 (setter: *self = v) */
extern void sk_h_00407170(void);                                     /* FUN_00407170 (noop thunk) */
extern void sk_h_00359024(word_t a, word_t b, word_t c);             /* FUN_00359024 */
extern void sk_h_00350744(word_t a);                                 /* FUN_00350744 */
extern void sk_h_0034ba48(void);                                     /* FUN_0034ba48 */
extern void sk_h_000839d8(word_t a, word_t b, word_t c, word_t d);   /* FUN_000839d8 */
extern void sk_h_00350500(void);                                     /* FUN_00350500 */
extern void sk_h_000a6e14();                                         /* FUN_000a6e14 */

/* SoftwareBreakpoint(1, addr) guard-rail traps used by this slice. */
extern void sk_h_overflow_trap_405360(void);                         /* SB(1,0x405360) */
extern void sk_h_overflow_trap_4055d4(void);                         /* SB(1,0x4055d4) */
extern void sk_h_overflow_trap_4055dc(void);                         /* SB(1,0x4055dc) */
extern void sk_h_overflow_trap_405afc(void);                         /* SB(1,0x405afc) */
extern void sk_h_overflow_trap_405364(void);                         /* SB(1,0x405364) */

/* Global indirect function pointer used by the dispatch preamble. */
extern void (*sk_g_dispatch_00658c80)(void);                         /* DAT_00658c80 */
extern word_t sk_g_string_0067f358;                                  /* 0x67f358 (const string ptr) */

/* ================================================================== *
 * Slice bodies.
 * ================================================================== */

void sk_f_0040548c(word_t param_1, word_t param_2); /* fwd (callback) */

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
    word_t out1, out8, out16;
    word_t out12;
    void (*out9)(void);    /* extraout_x9 (register-held code ptr) */
    void (*out8p)(void);   /* extraout_x8_00 (register-held code ptr) */

    key = sk_h_00351da8();
    sk_h_0034b7e4(key.hi, key.lo, key.lo);
    sk_g_dispatch_00658c80();
    sk_h_003f5c00(*param_3, out1, out8, param_5);
    sk_h_00407d44();
    /* spill to a 16-byte-aligned frame; offset depends on out12 register. */
    (void)out12;
    sk_h_00350624((void *)(out12 & ~0xfU));
    /* indirect tail calls through register-held code pointers (extraout_x9 /
     * extraout_x8_00) */
    out9();
    sk_h_003504c4(*(word_t *)(out16 + 0x20));
    out8p();
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
    long ctx;                    /* unaff_x20 (context, register artifact) */
    long x16;                    /* extraout_x16 (vtable, register artifact) */
    word_t info, val;
    void (*vcall)(word_t, word_t, word_t); /* (**(code **)(x16+0x10)) */

    sk_h_00407170();
    info = *(word_t *)(ctx + 0x10);
    val = sk_h_003f5c00(*(word_t *)(ctx + 0x18));
    sk_h_003509c8(info, val, val);
    vcall = *(void (**)(word_t, word_t, word_t))(x16 + 0x10);
    vcall(0, 0, info);           /* (**(code **)(x16+0x10))(x8,x1,info) */
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
    long ctx;                    /* unaff_x20 (context, register artifact) */
    uint8_t *out_x22;            /* unaff_x22 (output byte ptr, register artifact) */
    long *slot;
    word_t candidate;
    uint8_t flag;

    sk_h_0035860c();
    slot = (long *)(ctx + 0x18);
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
void sk_f_00404e60(word_t param_1, word_t param_2, word_t *param_3); /* fwd */
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
    long ctx;                              /* unaff_x20 (context, register artifact) */
    long offset = (long)param_2[2];          /* @ +0x10 */
    unsigned long total = (unsigned long)param_2[1] + (unsigned long)offset;  /* base @ +8 */

    if ((long)total >= 0) {
        word_t cap = *(word_t *)(ctx + 0x18);
        unsigned long size = sk_h_003f5cf0();
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
    long ctx;                    /* unaff_x20 (context, register artifact) */
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
    long ctx;                    /* unaff_x20 (context, register artifact) */
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
    long ctx;                    /* unaff_x20 (context, register artifact) */
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
    long ctx;                    /* unaff_x20 (context, register artifact) */
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
    long ctx;                    /* unaff_x20 (context, register artifact) */
    word_t x21 = ((word_t (*)(void))(*(word_t *)(ctx + 0x20)))();
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
    long ctx;                    /* unaff_x20 (context, register artifact) */
    word_t *out_x22;             /* unaff_x22 (output ptr, register artifact) */
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
    long ctx;                    /* unaff_x20 (context, register artifact) */
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
    long ctx;                    /* unaff_x20 (context, register artifact) */
    cl4_result_t *out_x22_pair;  /* unaff_x22 (16-byte output ptr, reg artifact) */
    word_t *ctx_words = (word_t *)ctx;
    cl4_result_t r;

    sk_h_0035860c();
    r = sk_h_0001a1c8(ctx_words[0], ctx_words[1], *(word_t *)(ctx + 0x10));
    out_x22_pair[0] = r;
}

/* FUN_00404f98 @ 0x00404f98  (est. sk_f_00404f98)
 * Ghidra: void FUN_00404f98(void)
 * Reads a capability id from FUN_0025177c and a word from the slot at ctx+0x10
 * (+8), then writes the triple {cap, slot_word, 0} to the output (*x22).
 * Confidence: medium
 */
void sk_f_00404f98(void)
{
    long ctx;                    /* unaff_x20 (context, register artifact) */
    word_t *out_x22;             /* unaff_x22 (output ptr, register artifact) */
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
    long ctx;                    /* unaff_x20 (context, register artifact) */
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
    long ctx;                    /* unaff_x20 (context, register artifact) */
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
    long ctx;                    /* unaff_x20 (context, register artifact) */
    long ctxbuf;                 /* lVar3 from FUN_00408238 (context getter) */
    long end;
    word_t flag = 0;
    word_t out8;
    word_t x21;                  /* unaff_x21 (callee-saved register result) */

    ctxbuf = (long)sk_h_00408238();
    end = (long)param_3[1] + *(long *)(ctxbuf + 0x10);
    if (end < 0) {
        sk_h_0040633c();
        sk_h_001afa84();      /* noreturn */
    }
    {
        word_t slot_cap = *(word_t *)(ctx + 0x18);
        if ((long)*param_3 < end) {
            flag = 1;
        } else if (end < *(long *)(ctxbuf + 0x10)) {
            sk_h_00347da8();
            sk_h_003504b8();
            sk_h_001afe4c();  /* noreturn */
        } else {
            void (*handler)(word_t) = *(void (**)(word_t))(ctx + 0x20);
            sk_h_003f5c64();
            handler(out8);
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
    long ctx;                    /* unaff_x20 (context, register artifact) */
    word_t info = *(word_t *)(ctx + 0x10);
    word_t slot = *(word_t *)(ctx + 0x18);
    long base = *(long *)(ctx + 0x20);
    word_t spare = *(word_t *)(ctx + 0x28);
    word_t w0[4];
    long len, len2;
    long upper_bound;            /* lStack_80 (stack upper bound, reg artifact) */
    long cap2;                   /* local_70 (second cap, reg artifact) */
    uint8_t more_guard;          /* local_68 (guard byte, reg artifact) */
    word_t scratch[4];           /* auStack_b8 (16-byte scratch buffer) */
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
        cl4_result_t res = sk_h_003f7b44(cap, (word_t)(len + len2));
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
    long ctx;                    /* unaff_x20 (context, register artifact) */
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
    long ctx;                    /* unaff_x20 (context, register artifact) */
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
    long ctx;                    /* unaff_x20 (context, register artifact) */
    word_t info = *(word_t *)(ctx + 0x10);
    word_t *slot_cap = *(word_t **)(ctx + 0x18);
    word_t *counter = *(word_t **)(ctx + 0x20);
    word_t w0[4];
    word_t scratch[4];           /* auStack (scratch buffer) */
    word_t w0_len, w0_over;      /* length / overrun register artifacts */
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
    long ctx;                    /* unaff_x20 (context, register artifact) */
    word_t info = *(word_t *)(ctx + 0x10);
    word_t val;

    sk_h_0034bb84();
    sk_h_003f5e78(*(word_t *)(ctx + 0x18));
    sk_h_000bd3a4();
    val = sk_h_003f5c00();
    sk_h_003509c8(info, val, val);
    sk_h_00407d44_vtable_x16_10();
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
    long ctx;                    /* unaff_x20 (context, register artifact) */
    long ctxbuf;                 /* lVar3 from FUN_00408238 (context getter) */
    long end;
    word_t x21;                  /* unaff_x21 (callee-saved register result) */

    ctxbuf = (long)sk_h_00408238();
    end = (long)param_3[1] + *(long *)(ctxbuf + 0x10);
    if (end < 0) {
        sk_h_0040633c();
        sk_h_001afa84();      /* noreturn */
    }
    if ((long)*param_3 < end) {
        sk_h_00350744(0);
        sk_h_000839d8(0, 0, 0, 0);
    } else {
        if (end < *(long *)(ctxbuf + 0x10)) {
            sk_h_00347da8();
            sk_h_003504b8();
            sk_h_001afe4c();  /* noreturn */
        }
        {
            cl4_result_t desc = sk_h_003f5cc4();
            void (*handler)(word_t, cl4_result_t) =
                *(void (**)(word_t, cl4_result_t))(ctx + 0x20);
            handler(0, desc);
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
    long ctx;                    /* unaff_x20 (context, register artifact) */
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
    long ctx;                    /* unaff_x20 (context, register artifact) */
    word_t *out_x24;             /* unaff_x24 (output ptr, register artifact) */
    word_t info = *(word_t *)(ctx + 0x10);
    word_t val = sk_h_003f5e78(*(word_t *)(ctx + 0x18));
    int idx;

    sk_h_0034bb84();
    sk_h_003515b4(0, sk_g_string_0067f358, info);
    idx = *(int *)(sk_h_003722e4() + 0x30);
    *out_x24 = val;
    sk_h_000bd3a4(val);
    val = sk_h_003f5c00();
    sk_h_001a29a0((word_t)out_x24 + (word_t)idx, val, info);
}

/* FUN_004058d4 @ 0x004058d4  (est. sk_f_004058d4)
 * Ghidra: void FUN_004058d4(undefined8 param_1, undefined8 param_2)
 * Forwards to the dispatch preamble FUN_00404ac0 with the context's slot
 * (ctx+0x18), extended arg (ctx+0x20), and info (ctx+0x10).
 * Confidence: medium
 */
void sk_f_004058d4(word_t param_1, word_t param_2)
{
    long ctx;                    /* unaff_x20 (context, register artifact) */
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
    long ctx;                    /* unaff_x20 (context, register artifact) */
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
    long ctx;                    /* unaff_x20 (context, register artifact) */
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
    long ctx;                    /* unaff_x20 (context, register artifact) */
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
    long ctx;                    /* unaff_x20 (context, register artifact) */
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
    long ctx;                    /* unaff_x20 (context, register artifact) */
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
    long ctx;                    /* unaff_x20 (context, register artifact) */
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
    long ctx;                    /* unaff_x20 (context, register artifact) */
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

/* ================================================================== *
 * Appended slice bodies for batch SKR14 addresses 0x0041a048-0x0041d788.
 * Transcribed from Ghidra decompiles (program cl4_kernel.raw). Helper
 * externs are prototype-less () per convention; register artifacts are
 * commented locals.
 * ================================================================== */

extern void sk_sw_breakpoint(unsigned long, unsigned long);

extern word_t sk_h_00002818();  /* helper */
extern word_t sk_h_00002874();  /* helper */
extern word_t sk_h_0006a374();  /* helper */
extern word_t sk_h_0006b42c();  /* helper */
extern word_t sk_h_0006b6a0();  /* helper */
extern word_t sk_h_0006e064();  /* helper */
extern word_t sk_h_000722b0();  /* helper */
extern word_t sk_h_00077894();  /* helper */
extern cl4_result_t sk_h_00084220();  /* helper */
extern word_t sk_h_00084234();  /* helper */
extern word_t sk_h_0008e500();  /* helper */
extern cl4_result_t sk_h_0008e518();  /* helper */
extern word_t sk_h_0009461c();  /* helper */
extern word_t sk_h_000a6fe0();  /* helper */
extern word_t sk_h_000b43e8();  /* helper */
extern word_t sk_h_000b45b0();  /* helper */
extern word_t sk_h_00100c04();  /* helper */
extern word_t sk_h_00100e34();  /* helper */
extern word_t sk_h_00100efc();  /* helper */
extern word_t sk_h_00117cc4();  /* helper */
extern word_t sk_h_001a6a8c();  /* helper */
extern word_t sk_h_001a84f4();  /* helper */
extern word_t sk_h_001b9084();  /* helper */
extern word_t sk_h_001bc440();  /* helper */
extern word_t sk_h_001ed960();  /* helper */
extern word_t sk_h_00205844();  /* helper */
extern word_t sk_h_002298d4();  /* helper */
extern word_t sk_h_00229a3c();  /* helper */
extern word_t sk_h_00268540();  /* helper */
extern word_t sk_h_002a0cf8();  /* helper */
extern word_t sk_h_002a4ab4();  /* helper */
extern word_t sk_h_002acbb8();  /* helper */
extern word_t sk_h_002ad78c();  /* helper */
extern word_t sk_h_002cb61c();  /* helper */
extern word_t sk_h_00349a18();  /* helper */
extern word_t sk_h_0034c444();  /* helper */
extern word_t sk_h_0034d868();  /* helper */
extern word_t sk_h_00350470();  /* helper */
extern cl4_result_t sk_h_003504d0();  /* helper */
extern word_t sk_h_0035053c();  /* helper */
extern word_t sk_h_003505c4();  /* helper */
extern word_t sk_h_003505e8();  /* helper */
extern word_t sk_h_003507e0();  /* helper */
extern word_t sk_h_00350980();  /* helper */
extern word_t sk_h_0035098c();  /* helper */
extern word_t sk_h_003509ec();  /* helper */
extern word_t sk_h_00350a04();  /* helper */
extern word_t sk_h_00350b18();  /* helper */
extern word_t sk_h_00350c5c();  /* helper */
extern word_t sk_h_003511f0();  /* helper */
extern word_t sk_h_003514e8();  /* helper */
extern word_t sk_h_00351aec();  /* helper */
extern word_t sk_h_00351b78();  /* helper */
extern word_t sk_h_00351d30();  /* helper */
extern word_t sk_h_00351dc0();  /* helper */
extern word_t sk_h_003523fc();  /* helper */
extern word_t sk_h_00353bc4();  /* helper */
extern word_t sk_h_003544c8();  /* helper */
extern word_t sk_h_00354744();  /* helper */
extern word_t sk_h_00354828();  /* helper */
extern word_t sk_h_003552a0();  /* helper */
extern word_t sk_h_003567c8();  /* helper */
extern word_t sk_h_00356c6c();  /* helper */
extern word_t sk_h_003593c0();  /* helper */
extern word_t sk_h_0036a940();  /* helper */
extern word_t sk_h_003a25d4();  /* helper */
extern word_t sk_h_004080b0();  /* helper */
extern word_t sk_h_0041001c();  /* helper */
extern word_t sk_h_00410414();  /* helper */
extern word_t sk_h_00411290();  /* helper */
extern word_t sk_h_00411308();  /* helper */
extern word_t sk_h_0041aab4();  /* helper */
extern word_t sk_h_0041aee4();  /* helper */
extern word_t sk_h_0041b01c();  /* helper */
extern word_t sk_h_0041baa4();  /* helper */
extern word_t sk_h_0041c1d8();  /* helper */
extern word_t sk_h_0044929c();  /* helper */
extern word_t sk_h_0044ca60();  /* helper */
extern word_t sk_h_00455f60();  /* helper */
extern word_t sk_h_0045636c();  /* helper */
extern word_t sk_h_00456858();  /* helper */
extern word_t sk_h_004578dc();  /* helper */
extern word_t sk_h_00457994();  /* helper */
extern word_t sk_h_0045811c();  /* helper */
extern word_t sk_h_00458278();  /* helper */
extern word_t sk_h_00458c98();  /* helper */
extern word_t sk_h_00458cb8();  /* helper */
extern word_t sk_h_00458cd4();  /* helper */
extern word_t sk_h_00458d68();  /* helper */
extern word_t sk_h_00458d78();  /* helper */
extern word_t sk_h_00458da0();  /* helper */
extern word_t sk_h_00458e28();  /* helper */
extern word_t sk_h_00458e80();  /* helper */
extern word_t sk_h_0045908c();  /* helper */
extern word_t sk_h_004590e0();  /* helper */
extern word_t sk_h_00460d94();  /* helper */
extern word_t sk_h_0046134c();  /* helper */
extern word_t sk_h_004613d4();  /* helper */
extern word_t sk_h_00462728();  /* helper */
extern word_t sk_h_00462898();  /* helper */
extern word_t sk_h_0046299c();  /* helper */
extern word_t sk_h_00462b6c();  /* helper */
extern word_t sk_h_00462d5c();  /* helper */
extern word_t sk_h_00462e0c();  /* helper */
extern word_t sk_h_00463210();  /* helper */
extern word_t sk_h_004632a4();  /* helper */
extern word_t sk_h_004632f4();  /* helper */
extern word_t sk_h_004633f4();  /* helper */
extern word_t sk_h_00463558();  /* helper */
extern word_t sk_h_00463600();  /* helper */
extern word_t sk_h_00463708();  /* helper */
extern word_t sk_h_004637b4();  /* helper */
extern word_t sk_h_004637dc();  /* helper */
extern word_t sk_h_00463878();  /* helper */
extern word_t sk_h_00463998();  /* helper */
extern word_t sk_h_00463ab8();  /* helper */
extern word_t sk_h_00463af8();  /* helper */
extern word_t sk_h_00463dc8();  /* helper */
extern word_t sk_h_00463df8();  /* helper */
extern word_t sk_h_00464308();  /* helper */
extern word_t sk_h_004643cc();  /* helper */
extern word_t sk_h_004644e8();  /* helper */
extern word_t sk_h_004645ec();  /* helper */
extern word_t sk_h_004647b4();  /* helper */
extern word_t sk_h_004648fc();  /* helper */
extern word_t sk_h_00464a08();  /* helper */
extern word_t sk_h_00464a38();  /* helper */
extern word_t sk_h_00464a44();  /* helper */
extern word_t sk_h_00464ad0();  /* helper */
extern word_t sk_h_00464d0c();  /* helper */
extern word_t sk_h_00464d68();  /* helper */
extern word_t sk_h_00464e1c();  /* helper */
extern word_t sk_h_00464eb0();  /* helper */
extern word_t sk_h_00464f58();  /* helper */
extern word_t sk_h_004650e4();  /* helper */
extern word_t sk_h_004651a8();  /* helper */
extern word_t sk_h_00465234();  /* helper */
extern word_t sk_h_00465240();  /* helper */
extern word_t sk_h_00465264();  /* helper */
extern word_t sk_h_004652a0();  /* helper */
extern word_t sk_h_004652f4();  /* helper */
extern word_t sk_h_004653c0();  /* helper */
extern word_t sk_h_00465488();  /* helper */
extern word_t sk_h_00465800();  /* helper */
extern word_t sk_h_00465884();  /* helper */
extern word_t sk_h_004658a8();  /* helper */
extern word_t sk_h_00465944();  /* helper */
extern word_t sk_h_00465a14();  /* helper */
extern word_t sk_h_00465b58();  /* helper */
extern word_t sk_h_00465c5c();  /* helper */
extern word_t sk_h_00465c74();  /* helper */
extern word_t sk_h_00465d1c();  /* helper */
extern word_t sk_h_00465d3c();  /* helper */
extern word_t sk_h_00465db0();  /* helper */
extern word_t sk_h_00465fb4();  /* helper */
extern word_t sk_h_00465fe0();  /* helper */
extern word_t sk_h_0046622c();  /* helper */
extern word_t sk_h_00466528();  /* helper */
extern word_t sk_h_00466580();  /* helper */
extern word_t sk_h_00466660();  /* helper */
extern word_t sk_h_004666e4();  /* helper */
extern word_t sk_h_004666f8();  /* helper */
extern word_t sk_h_0067f9a0();  /* helper */

typedef unsigned long ulong;
typedef unsigned int uint;
extern cl4_result_t sk_h_00077888();  /* FUN_00077888 (16-byte) */
extern uint32_t sk_h_0041a9e4();      /* FUN_0041a9e4 */
extern uint32_t sk_h_0041ae14();      /* FUN_0041ae14 */
extern word_t sk_h_00448fd0();        /* FUN_00448fd0 */
extern word_t sk_h_00465968();        /* FUN_00465968 */
extern word_t sk_h_00350b54();          /* FUN_00350b54 */
extern cl4_result_t sk_h_00463e04();  /* FUN_00463e04 (16-byte) */
extern cl4_result_t sk_h_0044bd08();  /* FUN_0044bd08 (16-byte) */
extern cl4_result_t sk_h_00466568();  /* FUN_00466568 (16-byte) */
extern cl4_result_t sk_h_0046647c();  /* FUN_0046647c (16-byte) */
extern cl4_result_t sk_h_000b4390();  /* FUN_000b4390 (16-byte) */
extern cl4_result_t sk_h_000b4594();  /* FUN_000b4594 (16-byte) */
extern cl4_result_t sk_h_00002534();  /* FUN_00002534 (16-byte) */
extern cl4_result_t sk_h_000b43d0();  /* FUN_000b43d0 (16-byte) */
extern uint32_t sk_h_004114fc();      /* FUN_004114fc */
extern cl4_result_t sk_h_00350518();  /* FUN_00350518 (16-byte) */
extern cl4_result_t sk_h_00351e20();  /* FUN_00351e20 (16-byte) */
extern cl4_result_t sk_h_003207d4();  /* FUN_003207d4 (16-byte) */
extern cl4_result_t sk_h_000dbd0c();  /* FUN_000dbd0c (16-byte) */
extern cl4_result_t sk_h_00084220();  /* FUN_00084220 (16-byte) */
extern cl4_result_t sk_h_0008e518();  /* FUN_0008e518 (16-byte) */

/* global data symbols referenced by the transcribed bodies */
extern word_t DAT_00657778;
extern char s___resetsCurrentOptions__005dd260;
extern word_t _DAT_005a1820;
extern word_t uRam00000000005a1828;
extern unsigned char DAT_004e80a0;
extern char s_Cannot_encode_a_capture_structur_005e1f50;
extern word_t _DAT_004be5e0;
extern word_t uRam00000000004be5e8;
extern unsigned char DAT_005a3520;
void sk_f_0041a048(void)
{
    sk_h_004637b4();
    sk_h_0045908c();
    return;
}
word_t sk_f_0041a068(void)
{
    word_t uVar1;
    long unaff_x20; 
    uVar1 = *(word_t *)(unaff_x20 + 0x68);
    sk_h_0036b270(uVar1 & 0xfffffffffffffff);
    return uVar1;
}
void sk_f_0041a094(void)
{
    long extraout_x8; 
    word_t unaff_x19; 
    word_t unaff_x20; 
    cl4_result_t auVar1;
    auVar1 = sk_h_00077888();
    sk_h_00117cc4(extraout_x8, auVar1.lo, 0x68);
    *(long *)(extraout_x8 + 0x68) = auVar1.hi;
    *(word_t *)(extraout_x8 + 0x70) = unaff_x20;
    *(word_t *)(extraout_x8 + 0x78) = unaff_x19;
    return;
}
uint32_t sk_f_0041a0dc(long *param_1, long *param_2)
{
    word_t uVar1;
    long lVar2;
    long lVar3;
    word_t uVar4;
    word_t uVar5;
    long lVar6;
    long lVar7;
    long lVar8;
    word_t uVar9;
    bool bVar10;
    uint32_t uVar11;
    long lVar12;
    word_t uVar13;
    long extraout_x1;       
    long *extraout_x1_00;   
    long extraout_x1_01;    
    long extraout_x1_02;    
    long *extraout_x1_03;   
    long *extraout_x1_04;   
    long *extraout_x1_05;   
    long *extraout_x1_06;   
    long *extraout_x1_07;   
    long *extraout_x1_08;   
    long *extraout_x1_09;   
    long *extraout_x1_10;   
    long *extraout_x1_11;   
    long *extraout_x1_12;   
    long *plVar14;
    long extraout_x8;       
    long extraout_x8_00;    
    long extraout_x9;       
    long lVar15;
    long lVar16;
    unsigned char auStack_80[80];
    lVar12 = *param_1;
    lVar16 = param_1[1];
    uVar5 = param_1[2];
    uVar1 = param_1[3];
    lVar6 = param_1[4];
    lVar2 = param_1[5];
    lVar7 = param_1[6];
    lVar3 = param_1[7];
    lVar8 = param_1[8];
    lVar15 = param_1[9];
    bVar10 = (char)param_1[10] == '\x03';
    switch((char)param_1[10]) {
    default:
        if ((char)param_2[10] == '\0') {
            uVar4 = param_2[2];
            uVar9 = param_2[3];
            if (lVar12 == *param_2 && lVar16 == param_2[1]) {
                if (((uVar4 ^ uVar5) >> 0xe) == 0) goto LAB_0041a258;
            }
            else {
                uVar13 = sk_h_00465c5c();
                if (((uVar13 & 1) != 0) && ((uVar4 ^ uVar5) < 0x4000)) {
LAB_0041a258:
                    if ((uVar9 ^ uVar1) < 0x4000) goto LAB_0041a3b8;
                }
            }
        }
        break;
    case '\x01':
        sk_h_00465fe0();
        if (*(char *)(extraout_x1_01 + 0x50) == '\x01') {
            uVar11 = sk_h_0041a9e4(auStack_80);
            goto LAB_0041a3c4;
        }
        break;
    case '\x02':
        sk_h_00465fe0();
        if (*(char *)(extraout_x1 + 0x50) == '\x02') {
            uVar11 = sk_h_0041ae14(auStack_80);
            goto LAB_0041a3c4;
        }
        break;
    case '\x03':
        if ((((uVar5 == 0 && lVar16 == 0) && (lVar12 == 0 && uVar1 == 0)) &&
            ((lVar6 == 0 && lVar2 == 0) && lVar7 == 0)) &&
            ((lVar3 == 0 && lVar8 == 0) && lVar15 == 0)) {
            sk_h_00463dc8();
            if ((bVar10) &&
               (lVar16 = sk_h_00463558(*(word_t *)(extraout_x1_02 + 8),
                                       *(word_t *)(extraout_x1_02 + 0x30),
                                       *(word_t *)(extraout_x1_02 + 0x40),
                                       *(word_t *)(extraout_x1_02 + 0x10),
                                       *(word_t *)(extraout_x1_02 + 0x20)),
                (lVar16 == 0 && extraout_x8 == 0) && extraout_x9 == 0)) {
LAB_0041a3b8:
                uVar11 = 1;
                goto LAB_0041a3c4;
            }
        }
        else {
            bVar10 = lVar12 == 1;
            if ((bVar10) &&
               ((((uVar5 == 0 && lVar16 == 0) && uVar1 == 0) &&
                ((lVar6 == 0 && lVar2 == 0) && lVar7 == 0)) &&
                ((lVar3 == 0 && lVar8 == 0) && lVar15 == 0))) {
                sk_h_00463dc8();
                if ((bVar10) && (plVar14 = extraout_x1_00, *extraout_x1_00 == 1))
                goto LAB_0041a39c;
            }
            else {
                bVar10 = lVar12 == 2;
                if ((bVar10) &&
                   ((((uVar5 == 0 && lVar16 == 0) && uVar1 == 0) &&
                    ((lVar6 == 0 && lVar2 == 0) && lVar7 == 0)) &&
                    ((lVar3 == 0 && lVar8 == 0) && lVar15 == 0))) {
                    sk_h_00463dc8();
                    if ((bVar10) && (plVar14 = extraout_x1_03, *extraout_x1_03 == 2))
                    goto LAB_0041a39c;
                }
                else {
                    bVar10 = lVar12 == 3;
                    if ((bVar10) &&
                       ((((uVar5 == 0 && lVar16 == 0) && uVar1 == 0) &&
                        ((lVar6 == 0 && lVar2 == 0) && lVar7 == 0)) &&
                        ((lVar3 == 0 && lVar8 == 0) && lVar15 == 0))) {
                        sk_h_00463dc8();
                        if ((bVar10) && (plVar14 = extraout_x1_04, *extraout_x1_04 == 3))
                        goto LAB_0041a39c;
                    }
                    else {
                        bVar10 = lVar12 == 4;
                        if ((bVar10) &&
                           ((((uVar5 == 0 && lVar16 == 0) && uVar1 == 0) &&
                            ((lVar6 == 0 && lVar2 == 0) && lVar7 == 0)) &&
                            ((lVar3 == 0 && lVar8 == 0) && lVar15 == 0))) {
                            sk_h_00463dc8();
                            if ((bVar10) && (plVar14 = extraout_x1_05, *extraout_x1_05 == 4))
                            goto LAB_0041a39c;
                        }
                        else {
                            bVar10 = lVar12 == 5;
                            if ((bVar10) &&
                               ((((uVar5 == 0 && lVar16 == 0) && uVar1 == 0) &&
                                ((lVar6 == 0 && lVar2 == 0) && lVar7 == 0)) &&
                                ((lVar3 == 0 && lVar8 == 0) && lVar15 == 0))) {
                                sk_h_00463dc8();
                                if ((bVar10) && (plVar14 = extraout_x1_06, *extraout_x1_06 == 5))
                                goto LAB_0041a39c;
                            }
                            else {
                                bVar10 = lVar12 == 6;
                                if ((bVar10) &&
                                   ((((uVar5 == 0 && lVar16 == 0) && uVar1 == 0) &&
                                    ((lVar6 == 0 && lVar2 == 0) && lVar7 == 0)) &&
                                    ((lVar3 == 0 && lVar8 == 0) && lVar15 == 0))) {
                                    sk_h_00463dc8();
                                    if ((bVar10) && (plVar14 = extraout_x1_07, *extraout_x1_07 == 6))
                                    goto LAB_0041a39c;
                                }
                                else {
                                    bVar10 = lVar12 == 7;
                                    if ((bVar10) &&
                                       ((((uVar5 == 0 && lVar16 == 0) && uVar1 == 0) &&
                                        ((lVar6 == 0 && lVar2 == 0) && lVar7 == 0)) &&
                                        ((lVar3 == 0 && lVar8 == 0) && lVar15 == 0))) {
                                        sk_h_00463dc8();
                                        if ((bVar10) && (plVar14 = extraout_x1_08, *extraout_x1_08 == 7))
                                        goto LAB_0041a39c;
                                    }
                                    else {
                                        bVar10 = lVar12 == 8;
                                        if ((bVar10) &&
                                           ((((uVar5 == 0 && lVar16 == 0) && uVar1 == 0) &&
                                            ((lVar6 == 0 && lVar2 == 0) && lVar7 == 0)) &&
                                            ((lVar3 == 0 && lVar8 == 0) && lVar15 == 0))) {
                                            sk_h_00463dc8();
                                            if ((bVar10) && (plVar14 = extraout_x1_09, *extraout_x1_09 == 8))
                                            goto LAB_0041a39c;
                                        }
                                        else {
                                            bVar10 = lVar12 == 9;
                                            if ((bVar10) &&
                                               ((((uVar5 == 0 && lVar16 == 0) && uVar1 == 0) &&
                                                ((lVar6 == 0 && lVar2 == 0) && lVar7 == 0)) &&
                                                ((lVar3 == 0 && lVar8 == 0) && lVar15 == 0))) {
                                                sk_h_00463dc8();
                                                if ((bVar10) && (plVar14 = extraout_x1_10, *extraout_x1_10 == 9))
                                                goto LAB_0041a39c;
                                            }
                                            else {
                                                bVar10 = lVar12 == 10;
                                                if ((bVar10) &&
                                                   ((((uVar5 == 0 && lVar16 == 0) && uVar1 == 0) &&
                                                    ((lVar6 == 0 && lVar2 == 0) && lVar7 == 0)) &&
                                                    ((lVar3 == 0 && lVar8 == 0) && lVar15 == 0))) {
                                                    sk_h_00463dc8();
                                                    if ((bVar10) && (plVar14 = extraout_x1_11, *extraout_x1_11 == 10)) {
LAB_0041a39c:
                                                        lVar16 = sk_h_00463558(plVar14[1], plVar14[6],
                                                                              plVar14[8], plVar14[2],
                                                                              plVar14[4]);
                                                        if (lVar16 == 0 && extraout_x8_00 == 0)
                                                        goto LAB_0041a3b8;
                                                    }
                                                }
                                                else {
                                                    sk_h_00463dc8();
                                                    if ((bVar10) && (plVar14 = extraout_x1_12, *extraout_x1_12 == 0xb))
                                                    goto LAB_0041a39c;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    uVar11 = 0;
LAB_0041a3c4:
    return uVar11 & 1;
}
void sk_f_0041a3ec(long *unaff_x20) 
{
    long lVar1;
    word_t uVar2;
    long lVar3;
    long lVar4;
    long lVar5;
    long lVar6;
    word_t uVar7;
    long lVar8;
    long lVar9;
    long lVar10;
    word_t uVar11;
    word_t extraout_x1; 
    sk_h_004666f8();
    lVar1 = *unaff_x20;
    lVar6 = unaff_x20[1];
    uVar2 = unaff_x20[2];
    uVar7 = unaff_x20[3];
    lVar3 = unaff_x20[4];
    lVar8 = unaff_x20[5];
    lVar4 = unaff_x20[6];
    lVar9 = unaff_x20[7];
    lVar5 = unaff_x20[8];
    lVar10 = unaff_x20[9];
    switch((char)unaff_x20[10]) {
    default:
        sk_h_00464e1c();
        sk_h_002298d4();
        sk_h_00462e0c();
        sk_h_001b9084();
        sk_h_002298d4(uVar2 >> 0xe);
        sk_h_002298d4(uVar7 >> 0xe);
        break;
    case '\x01':
        sk_h_00465fb4();
        sk_h_00465b58();
        sk_h_004650e4();
        sk_h_0041aab4();
        break;
    case '\x02':
        sk_h_00465fb4();
        sk_h_002298d4(0xe);
        sk_h_004650e4();
        sk_h_0041aee4();
        break;
    case '\x03':
        if ((((uVar2 == 0 && lVar6 == 0) && (lVar1 == 0 && uVar7 == 0)) &&
            ((lVar3 == 0 && lVar8 == 0) && lVar4 == 0)) &&
            ((lVar9 == 0 && lVar5 == 0) && lVar10 == 0)) {
            uVar11 = 0;
        }
        else if ((lVar1 == 1) &&
                ((((uVar2 == 0 && lVar6 == 0) && uVar7 == 0) &&
                 ((lVar3 == 0 && lVar8 == 0) && lVar4 == 0)) &&
                 ((lVar9 == 0 && lVar5 == 0) && lVar10 == 0))) {
            uVar11 = 3;
        }
        else if ((lVar1 == 2) &&
                ((((uVar2 == 0 && lVar6 == 0) && uVar7 == 0) &&
                 ((lVar3 == 0 && lVar8 == 0) && lVar4 == 0)) &&
                 ((lVar9 == 0 && lVar5 == 0) && lVar10 == 0))) {
            uVar11 = 4;
        }
        else if ((lVar1 == 3) &&
                ((((uVar2 == 0 && lVar6 == 0) && uVar7 == 0) &&
                 ((lVar3 == 0 && lVar8 == 0) && lVar4 == 0)) &&
                 ((lVar9 == 0 && lVar5 == 0) && lVar10 == 0))) {
            uVar11 = 5;
        }
        else if ((lVar1 == 4) &&
                ((((uVar2 == 0 && lVar6 == 0) && uVar7 == 0) &&
                 ((lVar3 == 0 && lVar8 == 0) && lVar4 == 0)) &&
                 ((lVar9 == 0 && lVar5 == 0) && lVar10 == 0))) {
            uVar11 = 6;
        }
        else if ((lVar1 == 5) &&
                ((((uVar2 == 0 && lVar6 == 0) && uVar7 == 0) &&
                 ((lVar3 == 0 && lVar8 == 0) && lVar4 == 0)) &&
                 ((lVar9 == 0 && lVar5 == 0) && lVar10 == 0))) {
            uVar11 = 7;
        }
        else if ((lVar1 == 6) &&
                ((((uVar2 == 0 && lVar6 == 0) && uVar7 == 0) &&
                 ((lVar3 == 0 && lVar8 == 0) && lVar4 == 0)) &&
                 ((lVar9 == 0 && lVar5 == 0) && lVar10 == 0))) {
            uVar11 = 8;
        }
        else if ((lVar1 == 7) &&
                ((((uVar2 == 0 && lVar6 == 0) && uVar7 == 0) &&
                 ((lVar3 == 0 && lVar8 == 0) && lVar4 == 0)) &&
                 ((lVar9 == 0 && lVar5 == 0) && lVar10 == 0))) {
            uVar11 = 9;
        }
        else if ((lVar1 == 8) &&
                ((((uVar2 == 0 && lVar6 == 0) && uVar7 == 0) &&
                 ((lVar3 == 0 && lVar8 == 0) && lVar4 == 0)) &&
                 ((lVar9 == 0 && lVar5 == 0) && lVar10 == 0))) {
            uVar11 = 10;
        }
        else if ((lVar1 == 9) &&
                ((((uVar2 == 0 && lVar6 == 0) && uVar7 == 0) &&
                 ((lVar3 == 0 && lVar8 == 0) && lVar4 == 0)) &&
                 ((lVar9 == 0 && lVar5 == 0) && lVar10 == 0))) {
            uVar11 = 0xb;
        }
        else if ((lVar1 == 10) &&
                ((((uVar2 == 0 && lVar6 == 0) && uVar7 == 0) &&
                 ((lVar3 == 0 && lVar8 == 0) && lVar4 == 0)) &&
                 ((lVar9 == 0 && lVar5 == 0) && lVar10 == 0))) {
            uVar11 = 0xc;
        }
        else {
            uVar11 = 0xd;
        }
        sk_h_002298d4(uVar11);
    }
    sk_h_004666e4(extraout_x1);
    return;
}
void sk_f_0041a5cc(void)
{
    unsigned char auStack_68[72];
    sk_h_004080b0();
    sk_f_0041a3ec((long *)auStack_68);
    sk_h_001a8564();
    return;
}
void sk_f_0041a60c(void)
{
    unsigned char auStack_68[72];
    sk_h_001a84f4(auStack_68);
    sk_f_0041a3ec((long *)auStack_68);
    sk_h_001a8564();
    return;
}
word_t sk_f_0041a64c(void)
{
    uint8_t in_CY;          
    word_t uVar1;
    word_t uVar2;
    word_t extraout_x8;     
    long extraout_x8_00;    
    long extraout_x8_01;    
    long extraout_x8_02;    
    long unaff_x19;         
    long unaff_x20;         
    sk_h_00350c5c();
    sk_f_0041a0dc((long *)unaff_x19, (long *)unaff_x20);
    uVar1 = sk_h_00464a08();
    if ((((extraout_x8 & 1) != 0) && (uVar1 = sk_h_00464ad0(), extraout_x8_00 == 0)) &&
       (uVar1 = sk_h_0046622c(), extraout_x8_01 == 0)) {
        uVar2 = sk_h_0041001c(*(word_t *)(unaff_x19 + 0x68), *(word_t *)(unaff_x20 + 0x68));
        if ((((uVar2 & 1) == 0) ||
            (sk_h_00464d0c(*(word_t *)(unaff_x19 + 0x70)), extraout_x8_02 != 0)) ||
           (sk_h_00465264(*(word_t *)(unaff_x20 + 0x78)), (bool)in_CY)) {
            uVar1 = 0;
        }
        else {
            uVar1 = 1;
        }
    }
    return uVar1;
}
void sk_f_0041a6dc(void)
{
    word_t uVar1;
    long unaff_x19; 
    long unaff_x20; 
    sk_h_00464a38();
    uVar1 = *(word_t *)(unaff_x20 + 0x60);
    sk_f_0041a3ec((long *)unaff_x20);
    sk_h_00466660();
    sk_h_002298d4(uVar1 >> 0xe);
    sk_h_00410414();
    uVar1 = *(word_t *)(unaff_x19 + 0x78);
    sk_h_002298d4(*(word_t *)(unaff_x19 + 0x70) >> 0xe);
    sk_h_002298d4(uVar1 >> 0xe);
    return;
}
void sk_f_0041a740(void)
{
    word_t uVar1;
    long unaff_x19; 
    long unaff_x20; 
    unsigned char auStack_78[72];
    sk_h_004644e8();
    uVar1 = *(word_t *)(unaff_x20 + 0x60);
    sk_f_0041a3ec((long *)auStack_78);
    sk_h_004652a0();
    sk_h_002298d4(uVar1 >> 0xe);
    sk_h_00410414(auStack_78, *(word_t *)(unaff_x19 + 0x68));
    sk_h_00465234(*(word_t *)(unaff_x19 + 0x70));
    sk_h_00464eb0();
    sk_h_001a8564();
    return;
}

void sk_f_0041a7cc(void)
{
    void (*unaff_x19)(unsigned char *); 
    unsigned char auStack_68[72];
    sk_h_004653c0();
    unaff_x19(auStack_68);
    sk_h_001a8564();
    return;
}
void sk_f_0041a80c(void)
{
    long unaff_x20; 
    if ((*(char *)(unaff_x20 + 0x50) == '\0') ||
       ((*(char *)(unaff_x20 + 0x50) == '\x01' && (*(long *)(unaff_x20 + 8) != 0)))) {
        sk_h_0036b270(*(long *)(unaff_x20 + 8));
    }
    sk_h_003507e0();
    return;
}
word_t sk_f_0041a868(void)
{
    word_t uVar1;
    long extraout_x8; 
    long extraout_x9; 
    word_t *unaff_x20; 
    long lVar2;
    if (*(char *)(unaff_x20 + 10) == '\x03') {
        lVar2 = sk_h_00463558(*unaff_x20, unaff_x20[6], unaff_x20[8], unaff_x20[2], unaff_x20[4]);
        if (extraout_x8 == 4 && (lVar2 == 0 && extraout_x9 == 0)) {
            return 0x101;
        }
        if (extraout_x8 == 5 && (lVar2 == 0 && extraout_x9 == 0)) {
            uVar1 = sk_h_0006e064();
            return uVar1;
        }
        if (extraout_x8 == 7 && (lVar2 == 0 && extraout_x9 == 0)) {
            return 0x100;
        }
        if ((extraout_x8 == 8) && (lVar2 == 0 && extraout_x9 == 0)) {
            return 0;
        }
    }
    return 2;
}
void sk_f_0041a8f4(void)
{
    long unaff_x20; 
    sk_h_0036b270(*(word_t *)(unaff_x20 + 0x38));
    sk_h_00462d5c();
    return;
}
void sk_f_0041a92c(void)
{
    word_t unaff_x19; 
    long unaff_x20;   
    word_t unaff_x21; 
    word_t unaff_x22; 
    word_t unaff_x23; 
    sk_h_00349a18();
    sk_h_003a25d4(*(word_t *)(unaff_x20 + 0x38));
    *(word_t *)(unaff_x20 + 0x30) = unaff_x23;
    *(word_t *)(unaff_x20 + 0x38) = unaff_x22;
    *(word_t *)(unaff_x20 + 0x40) = unaff_x21;
    *(word_t *)(unaff_x20 + 0x48) = unaff_x19;
    return;
}
void sk_f_0041a96c(word_t param_1, word_t param_2, word_t param_3, word_t param_4,
                   word_t param_5, word_t param_6, word_t param_7, word_t param_8,
                   word_t param_9, word_t param_10, word_t param_11)
{
    unsigned char auStack_110[80];
    word_t local_c0;
    word_t uStack_b8;
    word_t local_b0;
    word_t uStack_a8;
    word_t local_a0;
    word_t uStack_98;
    word_t local_90;
    word_t uStack_88;
    word_t local_80;
    word_t uStack_78;
    word_t local_70;
    word_t uStack_68;
    word_t local_60;
    word_t uStack_58;
    word_t local_50;
    word_t uStack_48;
    word_t local_40;
    word_t uStack_38;
    word_t local_30;
    word_t uStack_28;
    local_80 = param_10;
    uStack_78 = param_11;
    local_30 = param_10;
    uStack_28 = param_11;
    local_c0 = param_2;
    uStack_b8 = param_3;
    local_b0 = param_4;
    uStack_a8 = param_5;
    local_a0 = param_6;
    uStack_98 = param_7;
    local_90 = param_8;
    uStack_88 = param_9;
    local_70 = param_2;
    uStack_68 = param_3;
    local_60 = param_4;
    uStack_58 = param_5;
    local_50 = param_6;
    uStack_48 = param_7;
    local_40 = param_8;
    uStack_38 = param_9;
    sk_h_00458d68(&local_c0, auStack_110);
    sk_h_00458d78(&local_70);
    sk_h_00117cc4(param_1, &local_c0, 0x50);
    return;
}
uint32_t sk_f_0041a9e4(void)
{
    uint32_t uVar1;
    uint32_t uVar2;
    uint32_t uVar3;
    long lVar4;
    word_t uVar5;
    word_t uVar6;
    word_t extraout_x8;    
    long extraout_x8_00;   
    long extraout_x8_01;   
    long extraout_x8_02;   
    long *unaff_x19;       
    long *unaff_x20;       
    lVar4 = (long)sk_h_003504d0().lo;
    uVar5 = *(word_t *)(lVar4 + 8);
    uVar6 = unaff_x19[1];
    if (uVar5 == 0) {
        if (uVar6 == 0) {
LAB_0041aa60:
            sk_h_00464d0c(unaff_x20[4]);
            if ((extraout_x8_01 == 0) && (sk_h_00464d0c(unaff_x19[5]), extraout_x8_02 == 0)) {
                uVar3 = sk_h_00448fd0(unaff_x20[6], unaff_x20[7], unaff_x20[8], unaff_x20[9], unaff_x19[6],
                                      unaff_x19[7], unaff_x19[8], unaff_x19[9]);
                goto LAB_0041aa9c;
            }
        }
    }
    else if (uVar6 != 0) {
        uVar1 = *unaff_x20 == *unaff_x19 && uVar6 <= uVar5;
        if (*unaff_x20 == *unaff_x19 && uVar5 == uVar6) {
            sk_h_00464ad0();
            uVar2 = uVar1;
            if (extraout_x8_00 != 0) goto LAB_0041aa98;
        }
        else {
            sk_h_002a0cf8();
            uVar3 = sk_h_00464a08();
            if ((extraout_x8 & 1) == 0) goto LAB_0041aa9c;
            uVar3 = sk_h_00465968();
            uVar2 = 0;
            if ((bool)uVar1) goto LAB_0041aa9c;
        }
        sk_h_004658a8();
        if (!(bool)uVar2) goto LAB_0041aa60;
    }
LAB_0041aa98:
    uVar3 = 0;
LAB_0041aa9c:
    return uVar3 & 1;
}
void sk_f_0041aab4(void)
{
    word_t uVar1;
    word_t uVar2;
    long unaff_x19; 
    sk_h_00464a44();
    if (*(long *)(unaff_x19 + 8) == 0) {
        sk_h_00229a3c(0);
    }
    else {
        uVar1 = *(word_t *)(unaff_x19 + 0x10);
        uVar2 = *(word_t *)(unaff_x19 + 0x18);
        sk_h_00229a3c(1);
        sk_h_00077894();
        sk_h_001b9084();
        sk_h_002298d4(uVar1 >> 0xe);
        sk_h_002298d4(uVar2 >> 0xe);
    }
    uVar1 = *(word_t *)(unaff_x19 + 0x28);
    sk_h_002298d4(*(word_t *)(unaff_x19 + 0x20) >> 0xe);
    sk_h_002298d4(uVar1 >> 0xe);
    uVar1 = *(word_t *)(unaff_x19 + 0x40);
    uVar2 = *(word_t *)(unaff_x19 + 0x48);
    sk_h_001b9084();
    sk_h_002298d4(uVar1 >> 0xe);
    sk_h_002298d4(uVar2 >> 0xe);
    return;
}
void sk_f_0041ab70(void)
{
    void (*unaff_x19)(unsigned char *); 
    unsigned char auStack_68[72];
    sk_h_004648fc();
    unaff_x19(auStack_68);
    sk_h_001a8564();
    return;
}
void sk_f_0041abcc(void)
{
    void (*unaff_x19)(unsigned char *); 
    unsigned char auStack_68[72];
    sk_h_004653c0();
    unaff_x19(auStack_68);
    sk_h_001a8564();
    return;
}

void sk_f_0041ac6c(word_t param_1, uint32_t param_2, word_t param_3, word_t param_4)
{
    sk_h_002298d4(param_2);
    sk_h_002298d4(param_3 >> 0xe);
    sk_h_002298d4(param_4 >> 0xe);
}
void sk_f_0041acb4(void)
{
    uint32_t uVar1;
    uVar1 = sk_h_00350b54();
    sk_h_004080b0();
    sk_h_002298d4(uVar1);
    sk_h_004652a0();
    sk_h_00464eb0();
    sk_h_001a8564();
}
void sk_f_0041ad20(void)
{
    word_t uVar1;
    word_t uVar2;
    uint32_t uVar3;
    unsigned char *unaff_x20;   
    unsigned char auStack_78[72];
    uVar1 = *(word_t *)(unaff_x20 + 8);
    uVar2 = *(word_t *)(unaff_x20 + 0x10);
    uVar3 = *unaff_x20;
    sk_h_001a84f4(auStack_78);
    sk_f_0041ac6c((word_t)auStack_78, uVar3, uVar1, uVar2);
    sk_h_001a8564();
}
void sk_f_0041adbc(word_t param_1)
{
    long unaff_x20;   
    sk_h_0036b118(*(word_t *)(unaff_x20 + 0x38));
    *(word_t *)(unaff_x20 + 0x38) = param_1;
}
bool sk_f_0041ae04(void)
{
    long unaff_x20;   
    return *(char *)(unaff_x20 + 0x10) != '\x01';
}
word_t sk_f_0041ae14(void)
{
    char cVar1;
    bool bVar2;
    uint32_t uVar3;
    word_t uVar4;
    word_t uVar5;
    long extraout_x8;      
    word_t *unaff_x19;     
    word_t *unaff_x20;     
    cl4_result_t auVar6;
    auVar6 = sk_h_003504d0();
    cVar1 = *(char *)(auVar6.hi + 0x10);
    if (*(char *)(auVar6.lo + 0x10) == '\x01') {
        if (cVar1 != '\x01') {
            return 0;
        }
    } else {
        bVar2 = cVar1 != '\x01';
        if (cVar1 == '\x01' || (*unaff_x20 ^ *unaff_x19) >> 0xe != 0) {
            return 0;
        }
        sk_h_00465264(unaff_x19[1]);
        if (bVar2) {
            return 0;
        }
    }
    uVar4 = sk_h_00411290(unaff_x20[3], unaff_x19[3]);
    if ((uVar4 & 1) != 0) {
        cVar1 = (char)unaff_x19[6];
        if ((char)unaff_x20[6] == '\x01') {
            if (cVar1 == '\x01') {
                goto LAB_0041aebc;
            }
        } else {
            uVar3 = cVar1 != '\0';
            if ((cVar1 != '\x01') && (sk_h_004637dc(), extraout_x8 == 0) &&
                (sk_h_00465264(unaff_x19[5]), !(bool)uVar3)) {
                goto LAB_0041aebc;
            }
        }
    }
    return 0;
LAB_0041aebc:
    uVar5 = sk_h_00411290(unaff_x20[7], unaff_x19[7]);
    return uVar5;
}
void sk_f_0041aee4(void)
{
    word_t uVar1;
    word_t uVar2;
    word_t *unaff_x19;   
    sk_h_00464a44();
    if ((char)unaff_x19[2] == '\x01') {
        sk_h_00229a3c(0);
    } else {
        uVar1 = unaff_x19[0];
        uVar2 = unaff_x19[1];
        sk_h_00229a3c(1);
        sk_h_002298d4(uVar1 >> 0xe);
        sk_h_002298d4(uVar2 >> 0xe);
    }
    sk_h_00458278();
    if ((char)unaff_x19[6] == '\x01') {
        sk_h_00229a3c(0);
    } else {
        uVar1 = unaff_x19[4];
        uVar2 = unaff_x19[5];
        sk_h_00229a3c(1);
        sk_h_002298d4(uVar1 >> 0xe);
        sk_h_002298d4(uVar2 >> 0xe);
    }
    sk_h_00458278();
}
void sk_f_0041afc8(word_t *param_1, word_t param_2)
{
    param_1[0] = 0;
    param_1[1] = 0;
    *((uint8_t *)(param_1 + 2)) = 1;
    param_1[4] = 0;
    param_1[5] = 0;
    param_1[3] = param_2;
    *((uint8_t *)(param_1 + 6)) = 1;
    param_1[7] = (word_t)&DAT_00657778;
}
void sk_f_0041aff0(word_t *param_1, word_t param_2)
{
    param_1[0] = 0;
    param_1[1] = 0;
    *((uint8_t *)(param_1 + 2)) = 1;
    param_1[4] = 0;
    param_1[5] = 0;
    param_1[3] = (word_t)&DAT_00657778;
    *((uint8_t *)(param_1 + 6)) = 1;
    param_1[7] = param_2;
}
cl4_result_t sk_f_0041b01c(void)
{
    cl4_result_t auVar1;
    unsigned char local_21;
    cl4_result_t local_20;
    auVar1 = sk_h_00463e04();
    local_21 = (unsigned char)auVar1.lo;
    sk_h_00463df8(auVar1.lo, auVar1.hi, 0x6847e8);
    sk_h_00462728();
    sk_h_00205844(&local_21, &local_20);
    return local_20;
}

void sk_f_0041b068(void)
{
    unsigned char *unaff_x20;   
    sk_h_0041b01c(*unaff_x20, *(word_t *)(unaff_x20 + 8), *(word_t *)(unaff_x20 + 0x10));
    return;
}
void sk_f_0041b06c(void)
{
    unsigned char *unaff_x20;   
    sk_h_0041b01c(*unaff_x20, *(word_t *)(unaff_x20 + 8), *(word_t *)(unaff_x20 + 0x10));
    return;
}
cl4_result_t sk_f_0041b088(void)
{
    word_t uVar1;
    word_t uVar2;
    cl4_result_t auVar3;
    bool bVar4;
    word_t extraout_x1;   
    long unaff_x20;   
    word_t local_38;
    sk_h_00100c04();
    sk_h_002a4ab4(0x32);
    sk_h_003a25d4(local_38);
    sk_h_001a6a8c(*(word_t *)(unaff_x20 + 0x18), 0x684750);
    sk_h_002acbb8();
    sk_h_003a25d4(extraout_x1);
    sk_h_002acbb8(0x69766f6d6572202c, 0xec000000203a676e);
    sk_h_001a6a8c(*(word_t *)(unaff_x20 + 0x38), 0x684750);
    sk_h_00465944();
    sk_h_002acbb8();
    sk_h_003a25d4(0x684750);
    sk_h_004643cc(s___resetsCurrentOptions__005dd260);
    sk_h_002acbb8(0xd000000000000018);
    bVar4 = *(char *)(unaff_x20 + 0x10) != '\x01';
    uVar1 = 0x65736c6166;
    if (bVar4) {
        uVar1 = 0x65757274;
    }
    uVar2 = 0xe500000000000000;
    if (bVar4) {
        uVar2 = 0xe400000000000000;
    }
    sk_h_00465c74(uVar1);
    sk_h_003a25d4(uVar2);
    auVar3.lo = 0x203a676e69646461;
    auVar3.hi = 0xe800000000000000;
    return auVar3;
}
void sk_f_0041b1a8(void)
{
    sk_h_004632f4();
    sk_f_0041b088();
    return;
}
word_t sk_f_0041b1d4(long param_1, word_t param_2, word_t param_3, word_t param_4, long param_5,
                     long param_6, word_t param_7, word_t param_8)
{
    bool bVar1;
    word_t uVar2;
    uint32_t uVar3;
    uVar3 = (uint32_t)((word_t)param_6 >> 0x20);
    switch(param_2 >> 0x3d) {
    default:
        if (uVar3 >> 0x1d != 0) {
            return 0;
        }
        break;
    case 1:
        if (uVar3 >> 0x1d != 1) {
            return 0;
        }
        break;
    case 2:
        if (uVar3 >> 0x1d != 2) {
            return 0;
        }
        break;
    case 3:
        if (uVar3 >> 0x1d != 3) {
            return 0;
        }
        goto LAB_0041b230;
    case 4:
        if (-0x6000000000000001 < param_6) {
            return 0;
        }
LAB_0041b230:
        return (word_t)((((uint32_t)param_5 ^ (uint32_t)param_1) & 0xff) == 0);
    case 5:
        if ((param_2 == 0xa000000000000000) && ((param_4 == 0 && param_3 == 0) && param_1 == 0)) {
            if (uVar3 >> 0x1d != 5 || param_6 != -0x6000000000000000) {
                return 0;
            }
            if ((param_8 != 0 || param_7 != 0) || param_5 != 0) {
                return 0;
            }
            goto LAB_0041b3b8;
        }
        if ((param_2 == 0xa000000000000000 && param_1 == 1) && (param_4 == 0 && param_3 == 0)) {
            bVar1 = uVar3 >> 0x1d == 5 && param_5 == 1;
LAB_0041b388:
            if (!bVar1 || param_6 != -0x6000000000000000) {
                return 0;
            }
        }
        else {
            if ((param_2 == 0xa000000000000000 && param_1 == 2) && (param_4 == 0 && param_3 == 0)) {
                bVar1 = uVar3 >> 0x1d == 5 && param_5 == 2;
                goto LAB_0041b388;
            }
            if ((param_2 == 0xa000000000000000 && param_1 == 3) && (param_4 == 0 && param_3 == 0)) {
                bVar1 = uVar3 >> 0x1d == 5 && param_5 == 3;
                goto LAB_0041b388;
            }
            if ((param_2 == 0xa000000000000000 && param_1 == 4) && (param_4 == 0 && param_3 == 0)) {
                bVar1 = uVar3 >> 0x1d == 5 && param_5 == 4;
                goto LAB_0041b388;
            }
            if ((param_2 == 0xa000000000000000 && param_1 == 5) && (param_4 == 0 && param_3 == 0)) {
                bVar1 = uVar3 >> 0x1d == 5 && param_5 == 5;
                goto LAB_0041b388;
            }
            if ((param_2 == 0xa000000000000000 && param_1 == 6) && (param_4 == 0 && param_3 == 0)) {
                bVar1 = false;
                if (uVar3 >> 0x1d == 5) {
                    bVar1 = param_5 == 6;
                }
                goto LAB_0041b388;
            }
            if ((uVar3 >> 0x1d != 5 || param_5 != 7) || param_6 != -0x6000000000000000) {
                return 0;
            }
        }
        if (param_8 != 0 || param_7 != 0) {
            return 0;
        }
        goto LAB_0041b3b8;
    }
    uVar3 = (uint32_t)param_6 & 0xff;
    if ((param_2 & 0xff) == 1) {
        if (uVar3 != 1) {
            return 0;
        }
    }
    else if (uVar3 == 1 || param_1 != param_5) {
        return 0;
    }
    if ((((param_7 ^ param_3) >> 0xe) != 0) || (0x3fff < (param_8 ^ param_4))) {
        return 0;
    }
LAB_0041b3b8:
    uVar2 = sk_h_0006e064();
    return uVar2;
}
void sk_f_0041b3d4(word_t param_1, word_t param_2, word_t param_3, word_t param_4, word_t param_5)
{
    word_t uVar1;
    (void)param_1;
    switch(param_3 >> 0x3d) {
    default:
        uVar1 = 0;
        break;
    case 1:
        uVar1 = 1;
        break;
    case 2:
        uVar1 = 2;
        break;
    case 3:
        uVar1 = 0xb;
        goto LAB_0041b440;
    case 4:
        uVar1 = 0xc;
LAB_0041b440:
        sk_h_002298d4(uVar1);
        param_2 = param_2 & 0xff;
LAB_0041b448:
        sk_h_002298d4(param_2);
        return;
    case 5:
        if ((param_3 == 0xa000000000000000) && ((param_5 == 0 && param_4 == 0) && param_2 == 0)) {
            param_2 = 3;
        }
        else if ((param_3 == 0xa000000000000000 && param_2 == 1) && (param_5 == 0 && param_4 == 0)) {
            param_2 = 4;
        }
        else if ((param_3 == 0xa000000000000000 && param_2 == 2) && (param_5 == 0 && param_4 == 0)) {
            param_2 = 5;
        }
        else if ((param_3 == 0xa000000000000000 && param_2 == 3) && (param_5 == 0 && param_4 == 0)) {
            param_2 = 6;
        }
        else if ((param_3 == 0xa000000000000000 && param_2 == 4) && (param_5 == 0 && param_4 == 0)) {
            param_2 = 7;
        }
        else if ((param_3 == 0xa000000000000000 && param_2 == 5) && (param_5 == 0 && param_4 == 0)) {
            param_2 = 8;
        }
        else if ((param_3 == 0xa000000000000000 && param_2 == 6) && (param_5 == 0 && param_4 == 0)) {
            param_2 = 9;
        }
        else {
            param_2 = 10;
        }
        goto LAB_0041b448;
    }
    sk_h_002298d4(uVar1);
    if ((param_3 & 0xff) == 1) {
        sk_h_00229a3c(0);
    }
    else {
        sk_h_00229a3c(1);
        sk_h_002298d4(param_2);
    }
    sk_h_002298d4(param_4 >> 0xe);
    sk_h_002298d4(param_5 >> 0xe);
    return;
}
void sk_f_0041b58c(void)
{
    word_t uVar1;
    void (*unaff_x19)();   
    word_t unaff_x30;   
    word_t stack0x00000008;   
    sk_h_004666f8();
    sk_h_00351da8();
    uVar1 = sk_h_00350980();
    sk_h_004080b0();
    sk_h_00351b78(&stack0x00000008, uVar1);
    unaff_x19();
    uVar1 = sk_h_001a8564();
    sk_h_004666e4(uVar1, unaff_x30);
    return;
}
word_t sk_f_0041b64c(void)
{
    bool in_CY;   
    word_t *puVar1;
    word_t uVar2;
    word_t uVar3;
    long extraout_x8;   
    long unaff_x19;   
    word_t *unaff_x20;
    puVar1 = (word_t *)sk_h_00350c5c();
    uVar2 = sk_f_0041b1d4(*puVar1, *(word_t *)(unaff_x19 + 8), *(word_t *)(unaff_x19 + 0x10),
                          *(word_t *)(unaff_x19 + 0x18), *unaff_x20, unaff_x20[1], unaff_x20[2],
                          unaff_x20[3]);
    extraout_x8 = sk_h_004637dc();
    if ((((uVar2 & 1) == 0) || (extraout_x8 != 0)) ||
        (sk_h_00465264(unaff_x20[5]), (bool)in_CY)) {
        uVar3 = 0;
    }
    else {
        uVar3 = 1;
    }
    return uVar3;
}
void sk_f_0041b6ac(word_t param_1)
{
    word_t uVar1;
    word_t *unaff_x20;
    sk_f_0041b3d4(param_1, *unaff_x20, unaff_x20[1], unaff_x20[2], unaff_x20[3]);
    uVar1 = unaff_x20[5];
    sk_h_004647b4(unaff_x20[4]);
    sk_h_002298d4();
    sk_h_002298d4(uVar1 >> 0xe);
    return;
}
void sk_f_0041b6f4(void)
{
    word_t *unaff_x20;
    unsigned char auStack_68[72];
    sk_h_004080b0();
    sk_f_0041b3d4((word_t)auStack_68, *unaff_x20, unaff_x20[1], unaff_x20[2], unaff_x20[3]);
    sk_h_00465234(unaff_x20[4]);
    sk_h_00464eb0();
    sk_h_001a8564();
    return;
}

static void sk_neon_ext8_1(unsigned char *dst, const unsigned char *a, const unsigned char *b)
{
    int i;
    for (i = 0; i < 8; i++) dst[i] = a[i + 8];
    for (i = 0; i < 8; i++) dst[8 + i] = b[i];
}
void sk_f_0041b760(void)
{
    void (*unaff_x19)(void *); 
    unsigned char auStack_68[72];
    sk_h_004653c0();
    unaff_x19(auStack_68);
    sk_h_001a8564();
}
void sk_f_0041b7b8(void)
{
    word_t uVar1;
    uint8_t extraout_w1; 
    word_t in_x4; 
    word_t in_x5; 
    word_t in_x6; 
    word_t in_x7; 
    long extraout_x8; 
    word_t extraout_x9; 
    word_t unaff_x23; 
    word_t unaff_x24; 
    sk_h_00084220();
    uVar1 = sk_h_00351dc0();
    sk_h_00117cc4(extraout_x8, uVar1, 0x50);
    *(uint8_t *)(extraout_x8 + 0x50) = extraout_w1;
    *(word_t *)(extraout_x8 + 0x58) = unaff_x24;
    *(word_t *)(extraout_x8 + 0x60) = unaff_x23;
    *(word_t *)(extraout_x8 + 0x68) = in_x4;
    *(word_t *)(extraout_x8 + 0x70) = in_x5;
    *(word_t *)(extraout_x8 + 0x78) = in_x6;
    *(word_t *)(extraout_x8 + 0x80) = in_x7;
    sk_h_00084234(extraout_x9);
}
word_t sk_f_0041b820(long *param_1, long *param_2)
{
    uint uVar1;
    long lVar2;
    ulong uVar3;
    long lVar4;
    ulong uVar5;
    ulong uVar6;
    ulong uVar7;
    ulong uVar8;
    unsigned char auVar9[16];
    unsigned char auVar10[16];
    unsigned char auVar11[16];
    word_t uVar12;
    ulong uVar13;
    unsigned char bVar14;
    unsigned char bVar15;
    unsigned char bVar16;
    unsigned char bVar17;
    unsigned char bVar18;
    unsigned char bVar19;
    unsigned char bVar20;
    unsigned char bVar21;
    unsigned char bVar22;
    unsigned char bVar23;
    unsigned char bVar24;
    unsigned char bVar25;
    unsigned char bVar26;
    unsigned char bVar27;
    unsigned char bVar28;
    unsigned char bVar29;
    unsigned char auVar30[16];
    word_t acc;
    lVar2 = *param_1;
    uVar6 = param_1[1];
    uVar3 = param_1[2];
    uVar13 = param_1[3];
    lVar4 = param_1[4];
    uVar7 = param_1[5];
    uVar5 = param_1[6];
    uVar8 = param_1[7];
    switch(uVar7 >> 0x3d) {
    default:
        if ((ulong)param_2[5] >> 0x3d != 0) {
            return 0;
        }
        break;
    case 1:
        if ((ulong)param_2[5] >> 0x3d != 1) {
            return 0;
        }
        break;
    case 2:
        if ((ulong)param_2[5] >> 0x3d != 2) {
            return 0;
        }
        break;
    case 3:
        if ((ulong)param_2[5] >> 0x3d != 3) {
            return 0;
        }
        if ((uVar6 & 0xff) == 1) {
            if ((char)param_2[1] != '\x01') {
                return 0;
            }
        }
        else if ((char)param_2[1] == '\x01' || lVar2 != *param_2) {
            return 0;
        }
        param_1 = (long *)0x0;
        if ((param_2[2] ^ uVar3) >> 0xe != 0) {
            return 0;
        }
        if ((param_2[3] ^ uVar13) >> 0xe != 0) {
            return 0;
        }
        uVar1 = (uint)param_2[5] & 0xff;
        if ((uVar7 & 0xff) == 1) {
            if (uVar1 != 1) {
                return 0;
            }
        }
        else if (uVar1 == 1 || lVar4 != param_2[4]) {
            return 0;
        }
        if ((param_2[6] ^ uVar5) >> 0xe != 0) {
            return 0;
        }
        uVar13 = param_2[7] ^ uVar8;
        goto lab_b974;
    case 4:
        if (uVar7 == 0x8000000000000000 &&
            (((uVar3 == 0 && uVar6 == 0) && (lVar2 == 0 && uVar13 == 0)) &&
             ((lVar4 == 0 && uVar5 == 0) && uVar8 == 0))) {
            if (-0x6000000000000001 < param_2[5]) {
                return 0;
            }
            if (param_2[5] != (long)0x8000000000000000UL) {
                return 0;
            }
            lVar4 = param_2[4];
            lVar2 = param_2[3];
            bVar14 = *(unsigned char *)(param_2 + 1) | (unsigned char)lVar2;
            bVar15 = *(unsigned char *)((long)param_2 + 9) | (unsigned char)((ulong)lVar2 >> 8);
            bVar16 = *(unsigned char *)((long)param_2 + 10) | (unsigned char)((ulong)lVar2 >> 0x10);
            bVar17 = *(unsigned char *)((long)param_2 + 0xb) | (unsigned char)((ulong)lVar2 >> 0x18);
            bVar18 = *(unsigned char *)((long)param_2 + 0xc) | (unsigned char)((ulong)lVar2 >> 0x20);
            bVar19 = *(unsigned char *)((long)param_2 + 0xd) | (unsigned char)((ulong)lVar2 >> 0x28);
            bVar20 = *(unsigned char *)((long)param_2 + 0xe) | (unsigned char)((ulong)lVar2 >> 0x30);
            bVar21 = *(unsigned char *)((long)param_2 + 0xf) | (unsigned char)((ulong)lVar2 >> 0x38);
            bVar22 = *(unsigned char *)(param_2 + 2) | (unsigned char)lVar4;
            bVar23 = *(unsigned char *)((long)param_2 + 0x11) | (unsigned char)((ulong)lVar4 >> 8);
            bVar24 = *(unsigned char *)((long)param_2 + 0x12) | (unsigned char)((ulong)lVar4 >> 0x10);
            bVar25 = *(unsigned char *)((long)param_2 + 0x13) | (unsigned char)((ulong)lVar4 >> 0x18);
            bVar26 = *(unsigned char *)((long)param_2 + 0x14) | (unsigned char)((ulong)lVar4 >> 0x20);
            bVar27 = *(unsigned char *)((long)param_2 + 0x15) | (unsigned char)((ulong)lVar4 >> 0x28);
            bVar28 = *(unsigned char *)((long)param_2 + 0x16) | (unsigned char)((ulong)lVar4 >> 0x30);
            bVar29 = *(unsigned char *)((long)param_2 + 0x17) | (unsigned char)((ulong)lVar4 >> 0x38);
            auVar30[1] = bVar15;
            auVar30[0] = bVar14;
            auVar30[2] = bVar16;
            auVar30[3] = bVar17;
            auVar30[4] = bVar18;
            auVar30[5] = bVar19;
            auVar30[6] = bVar20;
            auVar30[7] = bVar21;
            auVar30[8] = bVar22;
            auVar30[9] = bVar23;
            auVar30[10] = bVar24;
            auVar30[0xb] = bVar25;
            auVar30[0xc] = bVar26;
            auVar30[0xd] = bVar27;
            auVar30[0xe] = bVar28;
            auVar30[0xf] = bVar29;
            auVar11[1] = bVar15;
            auVar11[0] = bVar14;
            auVar11[2] = bVar16;
            auVar11[3] = bVar17;
            auVar11[4] = bVar18;
            auVar11[5] = bVar19;
            auVar11[6] = bVar20;
            auVar11[7] = bVar21;
            auVar11[8] = bVar22;
            auVar11[9] = bVar23;
            auVar11[10] = bVar24;
            auVar11[0xb] = bVar25;
            auVar11[0xc] = bVar26;
            auVar11[0xd] = bVar27;
            auVar11[0xe] = bVar28;
            auVar11[0xf] = bVar29;
            sk_neon_ext8_1(auVar30, auVar30, auVar11);
            acc = (word_t)(bVar14 | auVar30[0])
                | (word_t)(bVar15 | auVar30[1]) << 8
                | (word_t)(bVar16 | auVar30[2]) << 16
                | (word_t)(bVar17 | auVar30[3]) << 24
                | (word_t)(bVar18 | auVar30[4]) << 32
                | (word_t)(bVar19 | auVar30[5]) << 40
                | (word_t)(bVar20 | auVar30[6]) << 48
                | (word_t)(bVar21 | auVar30[7]) << 56;
            if (acc != 0 || param_2[6] != 0 || param_2[7] != 0 || *param_2 != 0) {
                return 0;
            }
        }
        else {
            if ((uVar7 == 0x8000000000000000 && lVar2 == 1) &&
                (((uVar3 == 0 && uVar6 == 0) && uVar13 == 0) &&
                 ((lVar4 == 0 && uVar5 == 0) && uVar8 == 0))) {
                if (-0x6000000000000001 < param_2[5]) {
                    return 0;
                }
                if (param_2[6] != 0 || param_2[7] != 0) {
                    return 0;
                }
                if (param_2[5] != (long)0x8000000000000000UL || *param_2 != 1) {
                    return 0;
                }
            }
            else {
                if (-0x6000000000000001 < param_2[5]) {
                    return 0;
                }
                if (param_2[6] != 0 || param_2[7] != 0) {
                    return 0;
                }
                if (param_2[5] != (long)0x8000000000000000UL || *param_2 != 2) {
                    return 0;
                }
            }
            lVar4 = param_2[4];
            lVar2 = param_2[3];
            bVar14 = *(unsigned char *)(param_2 + 1) | (unsigned char)lVar2;
            bVar15 = *(unsigned char *)((long)param_2 + 9) | (unsigned char)((ulong)lVar2 >> 8);
            bVar16 = *(unsigned char *)((long)param_2 + 10) | (unsigned char)((ulong)lVar2 >> 0x10);
            bVar17 = *(unsigned char *)((long)param_2 + 0xb) | (unsigned char)((ulong)lVar2 >> 0x18);
            bVar18 = *(unsigned char *)((long)param_2 + 0xc) | (unsigned char)((ulong)lVar2 >> 0x20);
            bVar19 = *(unsigned char *)((long)param_2 + 0xd) | (unsigned char)((ulong)lVar2 >> 0x28);
            bVar20 = *(unsigned char *)((long)param_2 + 0xe) | (unsigned char)((ulong)lVar2 >> 0x30);
            bVar21 = *(unsigned char *)((long)param_2 + 0xf) | (unsigned char)((ulong)lVar2 >> 0x38);
            bVar22 = *(unsigned char *)(param_2 + 2) | (unsigned char)lVar4;
            bVar23 = *(unsigned char *)((long)param_2 + 0x11) | (unsigned char)((ulong)lVar4 >> 8);
            bVar24 = *(unsigned char *)((long)param_2 + 0x12) | (unsigned char)((ulong)lVar4 >> 0x10);
            bVar25 = *(unsigned char *)((long)param_2 + 0x13) | (unsigned char)((ulong)lVar4 >> 0x18);
            bVar26 = *(unsigned char *)((long)param_2 + 0x14) | (unsigned char)((ulong)lVar4 >> 0x20);
            bVar27 = *(unsigned char *)((long)param_2 + 0x15) | (unsigned char)((ulong)lVar4 >> 0x28);
            bVar28 = *(unsigned char *)((long)param_2 + 0x16) | (unsigned char)((ulong)lVar4 >> 0x30);
            bVar29 = *(unsigned char *)((long)param_2 + 0x17) | (unsigned char)((ulong)lVar4 >> 0x38);
            auVar9[1] = bVar15;
            auVar9[0] = bVar14;
            auVar9[2] = bVar16;
            auVar9[3] = bVar17;
            auVar9[4] = bVar18;
            auVar9[5] = bVar19;
            auVar9[6] = bVar20;
            auVar9[7] = bVar21;
            auVar9[8] = bVar22;
            auVar9[9] = bVar23;
            auVar9[10] = bVar24;
            auVar9[0xb] = bVar25;
            auVar9[0xc] = bVar26;
            auVar9[0xd] = bVar27;
            auVar9[0xe] = bVar28;
            auVar9[0xf] = bVar29;
            auVar10[1] = bVar15;
            auVar10[0] = bVar14;
            auVar10[2] = bVar16;
            auVar10[3] = bVar17;
            auVar10[4] = bVar18;
            auVar10[5] = bVar19;
            auVar10[6] = bVar20;
            auVar10[7] = bVar21;
            auVar10[8] = bVar22;
            auVar10[9] = bVar23;
            auVar10[10] = bVar24;
            auVar10[0xb] = bVar25;
            auVar10[0xc] = bVar26;
            auVar10[0xd] = bVar27;
            auVar10[0xe] = bVar28;
            auVar10[0xf] = bVar29;
            sk_neon_ext8_1(auVar30, auVar9, auVar10);
            acc = (word_t)(bVar14 | auVar30[0])
                | (word_t)(bVar15 | auVar30[1]) << 8
                | (word_t)(bVar16 | auVar30[2]) << 16
                | (word_t)(bVar17 | auVar30[3]) << 24
                | (word_t)(bVar18 | auVar30[4]) << 32
                | (word_t)(bVar19 | auVar30[5]) << 40
                | (word_t)(bVar20 | auVar30[6]) << 48
                | (word_t)(bVar21 | auVar30[7]) << 56;
            if (acc != 0) {
                return 0;
            }
        }
        goto lab_ba1c;
    }
    if ((uVar6 & 0xff) == 1) {
        if ((char)param_2[1] != '\x01') {
            return 0;
        }
    }
    else if ((char)param_2[1] == '\x01' || lVar2 != *param_2) {
        return 0;
    }
    if ((param_2[2] ^ uVar3) >> 0xe == 0) {
        uVar13 = param_2[3] ^ uVar13;
    lab_b974:
        if (uVar13 < 0x4000) {
        lab_ba1c:
            uVar12 = sk_h_0006e064(param_1);
            return uVar12;
        }
    }
    return 0;
}
void sk_f_0041baa4(void)
{
    long lVar1;
    ulong uVar2;
    long lVar3;
    ulong uVar4;
    ulong uVar5;
    ulong uVar6;
    ulong uVar7;
    ulong uVar8;
    word_t uVar9;
    word_t extraout_x1; 
    long *unaff_x20; 
    sk_h_0008e518();
    lVar1 = *unaff_x20;
    uVar5 = unaff_x20[1];
    uVar2 = unaff_x20[2];
    uVar6 = unaff_x20[3];
    lVar3 = unaff_x20[4];
    uVar7 = unaff_x20[5];
    uVar4 = unaff_x20[6];
    uVar8 = unaff_x20[7];
    switch(uVar7 >> 0x3d) {
    default:
        uVar9 = 3;
        break;
    case 1:
        uVar9 = 4;
        break;
    case 2:
        uVar9 = 5;
        break;
    case 3:
        sk_h_002298d4(6);
        if ((uVar5 & 0xff) == 1) {
            sk_h_00229a3c(0);
        }
        else {
            sk_h_00229a3c(1);
            sk_h_002298d4(lVar1);
        }
        sk_h_002298d4(uVar2 >> 0xe);
        sk_h_002298d4(uVar6 >> 0xe);
        if ((uVar7 & 0xff) == 1) {
            sk_h_00229a3c(0);
        }
        else {
            sk_h_00229a3c(1);
            sk_h_002298d4(lVar3);
        }
        sk_h_002298d4(uVar4 >> 0xe);
        goto lab_bc08;
    case 4:
        if (uVar7 == 0x8000000000000000 &&
            (((uVar2 == 0 && uVar5 == 0) && (lVar1 == 0 && uVar6 == 0)) &&
             ((lVar3 == 0 && uVar4 == 0) && uVar8 == 0))) {
            uVar9 = 0;
        }
        else if ((uVar7 == 0x8000000000000000 && lVar1 == 1) &&
                 (((uVar2 == 0 && uVar5 == 0) && uVar6 == 0) &&
                  ((lVar3 == 0 && uVar4 == 0) && uVar8 == 0))) {
            uVar9 = 1;
        }
        else {
            uVar9 = 2;
        }
        sk_h_002298d4(uVar9);
        goto lab_bc18;
    }
    sk_h_002298d4(uVar9);
    if ((uVar5 & 0xff) == 1) {
        sk_h_00229a3c(0);
    }
    else {
        sk_h_00229a3c(1);
        sk_h_002298d4(lVar1);
    }
    sk_h_002298d4(uVar2 >> 0xe);
    uVar8 = uVar6;
lab_bc08:
    sk_h_002298d4(uVar8 >> 0xe);
lab_bc18:
    sk_h_0008e500(extraout_x1);
}
void sk_f_0041bc58(void)
{
    void (*unaff_x19)(void *); 
    unsigned char auStack_68[72];
    sk_h_004648fc();
    unaff_x19(auStack_68);
    sk_h_001a8564();
}
void sk_f_0041bcb4(void)
{
    void (*unaff_x19)(void *); 
    unsigned char auStack_68[72];
    sk_h_004653c0();
    unaff_x19(auStack_68);
    sk_h_001a8564();
}
word_t sk_f_0041bcf4(word_t x0, word_t x1)
{
    word_t unaff_x20 = x0; 
    sk_h_00356c6c();
    sk_h_002ad78c(0x67f928);
    sk_h_00465240();
    if (2 < unaff_x20) {
        unaff_x20 = 3;
    }
    return unaff_x20;
}
void sk_f_0041bd34(unsigned char *param_1, word_t *param_2)
{
    uint8_t uVar1;
    uVar1 = (uint8_t)sk_f_0041bcf4(*param_2, param_2[1]);
    *param_1 = uVar1;
}
void sk_f_0041bd68(cl4_result_t *param_1)
{
    unsigned char *unaff_x20; 
    cl4_result_t auVar1;
    auVar1 = sk_h_0044bd08(*unaff_x20);
    *param_1 = auVar1;
}
word_t sk_f_0041bdac(void)
{
    word_t uVar1;
    word_t uVar2;
    long extraout_x8; 
    long extraout_x8_00; 
    long extraout_x8_01; 
    long extraout_x8_02; 
    long extraout_x8_03; 
    long extraout_x8_04; 
    long unaff_x19; 
    long unaff_x20; 
    sk_h_003504d0();
    uVar1 = sk_f_0041b820((long *)unaff_x19, (long *)unaff_x20);
    if (((uVar1 & 1) != 0) &&
        (sk_h_00464ad0(), extraout_x8 == 0) &&
        (sk_h_0046622c(), extraout_x8_00 == 0) &&
        (*(char *)(unaff_x20 + 0x50) == *(char *)(unaff_x19 + 0x50) &&
         (sk_h_00464d0c(*(word_t *)(unaff_x19 + 0x58)), extraout_x8_01 == 0)) &&
        (sk_h_00464d0c(*(word_t *)(unaff_x19 + 0x60)), extraout_x8_02 == 0 &&
         ((uVar1 = sk_h_0041001c(*(word_t *)(unaff_x20 + 0x68), *(word_t *)(unaff_x19 + 0x68)),
           (uVar1 & 1) != 0 &&
           (sk_h_00464d0c(*(word_t *)(unaff_x20 + 0x70)), extraout_x8_03 == 0)))) &&
        (sk_h_00464d0c(*(word_t *)(unaff_x19 + 0x78)), extraout_x8_04 == 0)) {
        uVar2 = sk_h_00411308(*(word_t *)(unaff_x20 + 0x80), *(word_t *)(unaff_x19 + 0x80));
        return uVar2;
    }
    return 0;
}

void sk_f_0041be80(void)
{
    word_t uVar1;
    long unaff_x19;   
    long unaff_x20;   
    sk_h_00464a38();
    uVar1 = *(word_t *)(unaff_x20 + 0x48);
    sk_h_0041baa4();
    sk_h_00466660();
    sk_h_002298d4(uVar1 >> 0xe);
    sk_h_0044929c();
    sk_h_00410414();
    uVar1 = *(word_t *)(unaff_x19 + 0x78);
    sk_h_002298d4(*(word_t *)(unaff_x19 + 0x70) >> 0xe);
    sk_h_002298d4(uVar1 >> 0xe);
    sk_h_0045811c();
    return;
}
void sk_f_0041bf18(void)
{
    void (*unaff_x19)(void *);  
    unsigned char auStack_68[72];
    sk_h_004648fc();
    unaff_x19(auStack_68);
    sk_h_001a8564();
    return;
}
void sk_f_0041bf74(void)
{
    void (*unaff_x19)(void *);  
    unsigned char auStack_68[72];
    sk_h_004653c0();
    unaff_x19(auStack_68);
    sk_h_001a8564();
    return;
}
cl4_result_t sk_f_0041bfb4(void)
{
    word_t uVar1;              
    cl4_result_t *unaff_x20;   
    cl4_result_t auVar2;       
    uVar1 = *(word_t *)((unsigned char *)&unaff_x20[2] + 8);
    switch (uVar1 >> 0x3d) {
    default:
        return *unaff_x20;
    case 1:
        return *unaff_x20;
    case 2:
        return (cl4_result_t){0, 0};
    case 3:
        return *unaff_x20;
    case 4:
        break;
    }
    if (uVar1 == 0x8000000000000000 &&
        (((*(long *)&unaff_x20[2] == 0 && *(long *)((unsigned char *)&unaff_x20[0] + 8) == 0) &&
         (*(long *)&unaff_x20[0] == 0 && *(long *)((unsigned char *)&unaff_x20[3] + 8) == 0)) &&
        ((*(long *)&unaff_x20[3] == 0 && *(long *)((unsigned char *)&unaff_x20[1] + 8) == 0) &&
        *(long *)&unaff_x20[1] == 0))) {
        uVar1 = 0;
    }
    else {
        if ((uVar1 != 0x8000000000000000 || *(long *)&unaff_x20[0] != 1) ||
           (((*(long *)&unaff_x20[2] != 0 || *(long *)((unsigned char *)&unaff_x20[0] + 8) != 0) ||
            *(long *)((unsigned char *)&unaff_x20[3] + 8) != 0) ||
            ((*(long *)&unaff_x20[3] != 0 || *(long *)((unsigned char *)&unaff_x20[1] + 8) != 0) ||
            *(long *)&unaff_x20[1] != 0))) {
            return (cl4_result_t){0, 0};
        }
        uVar1 = 1;
    }
    auVar2.hi = 0;
    auVar2.lo = uVar1;
    return auVar2;
}
void sk_f_0041c0c0(void)
{
    word_t *puVar1;
    long extraout_x8;          
    long lVar2;
    long *unaff_x20;           
    long unaff_x25;            
    word_t uVar3;
    word_t uVar4;
    word_t uVar5;
    word_t uVar6;
    word_t uVar7;
    word_t uVar8;
    cl4_result_t auVar9;       
    long stack0x00000008;      
    auVar9 = sk_h_00466568();
    puVar1 = (word_t *)auVar9.lo;
    sk_h_00458da0(puVar1, &stack0x00000008);
    sk_h_004578dc(sk_h_00455f60, sk_h_000722b0, sk_h_00456858, sk_h_0045636c);
    sk_h_00463708();
    sk_h_00462b6c();
    sk_h_00457994();
    sk_h_00463ab8();
    lVar2 = extraout_x8 + unaff_x25 * 0x38;
    uVar4 = puVar1[1];
    uVar3 = puVar1[0];
    uVar6 = puVar1[3];
    uVar5 = puVar1[2];
    uVar8 = puVar1[5];
    uVar7 = puVar1[4];
    *(unsigned char *)(lVar2 + 0x50) = *(unsigned char *)(puVar1 + 6);
    *(word_t *)(lVar2 + 0x38) = uVar6;
    *(word_t *)(lVar2 + 0x30) = uVar5;
    *(word_t *)(lVar2 + 0x48) = uVar8;
    *(word_t *)(lVar2 + 0x40) = uVar7;
    *(word_t *)(lVar2 + 0x28) = uVar4;
    *(word_t *)(lVar2 + 0x20) = uVar3;
    *unaff_x20 = extraout_x8;
    sk_h_00466528(auVar9.hi);
    return;
}
void sk_f_0041c190(void)
{
    long unaff_x20;   
    sk_h_0036b270(*(word_t *)(unaff_x20 + 8));
    sk_h_0009461c();
    return;
}
void sk_f_0041c1c4(word_t *param_1, word_t param_2, word_t param_3, word_t param_4,
                   word_t param_5, unsigned char param_6, word_t param_7, word_t param_8)
{
    *param_1 = param_2;
    param_1[1] = param_3;
    param_1[2] = param_4;
    param_1[3] = param_5;
    param_1[4] = param_7;
    param_1[5] = param_8;
    *(unsigned char *)(param_1 + 6) = param_6;
    return;
}
cl4_result_t sk_f_0041c1d8(word_t param_1, word_t param_2, long param_3)
{
    word_t uVar1;
    word_t uVar2;
    long lVar3;
    long unaff_x20;   
    long unaff_x21;   
    long lVar4;
    long *plVar5;
    cl4_result_t auVar6;
    lVar4 = *(long *)(param_3 + 0x10);
    if (lVar4 != 0) {
        sk_h_0035098c();
        lVar3 = 0;
        plVar5 = (long *)(param_3 + 0x28);
        do {
            if ((*plVar5 != 0) &&
               ((plVar5[-1] == unaff_x21 && *plVar5 == unaff_x20 ||
                (uVar1 = sk_h_004633f4(), (uVar1 & 1) != 0)))) {
                uVar2 = 0;
                goto LAB_0041c244;
            }
            lVar3 = lVar3 + 1;
            plVar5 = plVar5 + 7;
        } while (lVar4 != lVar3);
    }
    lVar3 = 0;
    uVar2 = 1;
LAB_0041c244:
    auVar6.hi = uVar2;
    auVar6.lo = lVar3;
    return auVar6;
}
cl4_result_t sk_f_0041c25c(void)
{
    return (cl4_result_t){0, 0x10f800};
}
bool sk_f_0041c26c(void)
{
    unsigned char in_ZR = 0;  
    long unaff_x20;           
    sk_f_0041c1d8(0, 0, unaff_x20);
    sk_h_00351db4();
    return !(bool)in_ZR;
}

    uint64_t lo;
    uint64_t hi;

bool sk_f_0041c270(void)
{
    bool in_ZR;   
    sk_h_0041c1d8();
    sk_h_00351db4();
    return !in_ZR;
}
cl4_result_t sk_f_0041c28c(uint32_t param_1)
{
    cl4_result_t r;
    r.lo = 0;
    r.hi = (word_t)(param_1 & 1);
    return r;
}
long sk_f_0041c29c(long param_1, word_t param_2, long param_3)
{
    if (!__builtin_add_overflow(param_1, param_3, (long *)0)) {
        return param_1 + param_3;
    }
    sk_sw_breakpoint(1, 0x41c2ac);
    return 0;   
}
cl4_result_t sk_f_0041c2ac(word_t param_1, word_t param_2, long param_3)
{
    bool bVar2;
    cl4_result_t auVar3;
    if ((param_2 & 1) != 0) {
        bVar2 = __builtin_add_overflow((long)param_1, param_3, (long *)0);
        param_1 = param_1 + (word_t)param_3;
        if (bVar2) {
            sk_sw_breakpoint(1, 0x41c2c8);
        }
    }
    auVar3.hi = 0;
    auVar3.lo = param_1;
    return auVar3;
}
void sk_f_0041c2c8(word_t param_1, word_t param_2, long param_3)
{
    if (((param_2 & 1) != 0) && __builtin_add_overflow(param_3, 1, (long *)0)) {
        sk_sw_breakpoint(1, 0x41c2d8);
    }
    return;
}
void sk_f_0041c2e4(word_t param_1, word_t param_2, word_t param_3, long param_4, uint8_t param_5)
{
    word_t uVar1;
    word_t uVar5;
    word_t uVar6;
    word_t uVar7;
    word_t uVar8;
    word_t uVar9;
    word_t uVar10;
    int iVar3;
    word_t uVar4;
    long lVar11;
    long lVar12;
    long extraout_x8;      
    long extraout_x8_00;   
    long extraout_x8_01;   
    long extraout_x8_02;   
    long extraout_x8_03;   
    long extraout_x9;      
    long extraout_x9_00;   
    long extraout_x9_01;   
    long extraout_x12;     
    long *unaff_x20;       
    word_t unaff_x30;      
    cl4_result_t auVar13;
    word_t local_118;
    long lStack_110;
    word_t local_108;
    word_t local_f8;
    word_t local_e8;
    word_t local_d8;
    char local_c8;
    unsigned char auStack_88[136];
    auVar13 = sk_h_0008e518();
    lVar11 = (long)auVar13.hi;
    uVar9 = auVar13.lo;
    uVar7 = (word_t)(uint32_t)param_3;
    switch (uVar9 >> 0x3c) {
    default:
        uVar8 = *(word_t *)(uVar9 + 0x10);
        lVar11 = *(long *)(uVar8 + 0x10);
        if (lVar11 == 0) break;
        sk_h_0036b270(uVar8);
        lVar12 = 0x20;
        do {
            if ((uVar7 & (word_t)__builtin_add_overflow((long)param_4, 1, (long *)0)) != 0) {
                sk_sw_breakpoint(1, 0x41c9e0);
            }
            uVar9 = *(word_t *)(uVar8 + lVar12);
            auVar13.lo = sk_h_0036b270(uVar9 & 0xfffffffffffffff); auVar13.hi = 0;
            sk_h_00464308(auVar13.lo, auVar13.hi, uVar7 & 1);
            sk_f_0041c2e4(param_1, param_2, param_3, param_4, param_5);   
            sk_h_0036b118(uVar9 & 0xfffffffffffffff);
            lVar12 = lVar12 + 8;
            lVar11 = lVar11 + -1;
        } while (lVar11 != 0);
        goto LAB_0041c89c;
    case 1:
        uVar8 = *(word_t *)((uVar9 & 0xfffffffffffffff) + 0x10);
        lVar11 = *(long *)(uVar8 + 0x10);
        if (lVar11 != 0) {
            sk_h_0036b270(uVar8);
            lVar12 = 0x20;
            do {
                uVar9 = *(word_t *)(uVar8 + lVar12);
                auVar13.lo = sk_h_0036b270(uVar9 & 0xfffffffffffffff); auVar13.hi = 0;
                sk_h_00464308(auVar13.lo, auVar13.hi, uVar7 & 1);
                sk_f_0041c2e4(param_1, param_2, param_3, param_4, param_5);   
                sk_h_0036b118(uVar9 & 0xfffffffffffffff);
                lVar12 = lVar12 + 8;
                lVar11 = lVar11 + -1;
            } while (lVar11 != 0);
            goto LAB_0041c89c;
        }
        break;
    case 2:
        sk_h_00117cc4(&local_118, (uVar9 & 0xfffffffffffffff) + 0x10, 0x68);
        uVar8 = *(word_t *)((uVar9 & 0xfffffffffffffff) + 0x78);
        if (local_c8 == '\0') {
            if (__builtin_add_overflow(lVar11, param_4, (long *)0)) {
                sk_sw_breakpoint(1, 0x41c9f0);
            }
            sk_h_00464f58();
            sk_h_00351aec();
            sk_h_0045908c();
            sk_h_00464f58();
            sk_h_00351aec();
            sk_h_0045908c();
            sk_h_0036b270();
            sk_h_004578dc(sk_h_00455f60, sk_h_000722b0, sk_h_00456858, sk_h_0045636c);
            uVar4 = sk_h_00463708();
            sk_h_00457994(uVar4, sk_h_00455f60, sk_h_000722b0, sk_h_00456858, sk_h_0045636c);
            sk_h_00465a14();
            sk_h_00463ab8();
            *(word_t *)(extraout_x8_01 + 0x13c05da0) = local_118;
            *(long *)(extraout_x8_01 + 0x13c05da8) = lStack_110;
            sk_h_004652f4();
            lVar11 = extraout_x8_02;
            lVar12 = extraout_x9_00;
LAB_0041c9a4:
            *(uint8_t *)(lVar12 + 0x50) = param_5 & 1;
            *unaff_x20 = lVar11;
        } else {
            if (local_c8 == '\x01') {
                if (__builtin_add_overflow(lVar11, param_4, (long *)0)) {
                    sk_sw_breakpoint(1, 0x41c9ec);
                }
                uVar4 = 0;
                if (lStack_110 != 0) {
                    uVar4 = local_118;
                }
                sk_h_004637b4();
                sk_h_00464f58();
                sk_h_0045908c();
                sk_h_0036b270();
                sk_h_0036b270(lStack_110);   
                sk_h_004578dc(sk_h_00455f60, sk_h_000722b0, sk_h_00456858, sk_h_0045636c);
                lVar11 = *(long *)(*unaff_x20 + 0x10);
                sk_h_004632a4();
                sk_h_00457994();
                sk_h_00465a14();
                sk_h_00463ab8();
                lVar11 = extraout_x8 + lVar11 * 0x38;
                *(word_t *)(lVar11 + 0x20) = uVar4;
                *(long *)(lVar11 + 0x28) = lStack_110;
                sk_h_004652f4();
                lVar11 = extraout_x8_00;
                lVar12 = extraout_x9;
                goto LAB_0041c9a4;
            }
            if ((local_c8 == '\x03') &&
                (lVar12 = sk_h_00463558(local_e8, local_d8, local_108, local_f8),
                 (lVar12 == 0 && extraout_x12 == 0) && lStack_110 == 0)) {
                if (__builtin_add_overflow(lVar11, param_4, (long *)0)) {
                    sk_sw_breakpoint(1, 0x41c9f4);
                }
                sk_h_004637b4();
                sk_h_00464f58();
                sk_h_0045908c();
                sk_h_0036b270();
                sk_h_003a25d4(0);
                sk_h_004578dc(sk_h_00455f60, sk_h_000722b0, sk_h_00456858, sk_h_0045636c);
                lVar12 = *(long *)(*unaff_x20 + 0x10);
                sk_h_00353bc4(lVar12, sk_h_00455f60, sk_h_000722b0);
                sk_h_00457994();
                lVar11 = *unaff_x20;
                *(long *)(lVar11 + 0x10) = lVar12 + 1;
                lVar11 = lVar11 + lVar12 * 0x38;
                *(word_t *)(lVar11 + 0x20) = 0;
                *(word_t *)(lVar11 + 0x28) = 0;
                sk_h_004652f4();
                lVar11 = extraout_x8_03;
                lVar12 = extraout_x9_01;
                goto LAB_0041c9a4;
            }
            sk_h_0036b270(uVar8 & 0xfffffffffffffff);
        }
        sk_h_00464d68();
        sk_h_003505e8();
        sk_f_0041c2e4(param_1, param_2, param_3, param_4, param_5);   
        goto LAB_0041c9c0;
    case 3:
        uVar9 = uVar9 & 0xfffffffffffffff;
        sk_h_00117cc4(&local_118, uVar9 + 0x20, 0x90);
        uVar10 = *(word_t *)(uVar9 + 0xb0);
        uVar8 = *(word_t *)(uVar9 + 0xd0);
        sk_h_00117cc4(auStack_88, uVar9 + 0x20, 0x80);
        iVar3 = sk_h_00458cb8(&local_118);
        if (iVar3 == 3) {
            uVar4 = sk_h_00458cd4(auStack_88);
            sk_h_00465884(sk_h_0067f9a0);
            uVar9 = sk_h_0036a940();
            sk_h_00117cc4(uVar9 + 0x10, uVar4, 0x80);
            sk_h_00464f58();
            sk_h_00458c98();
            sk_h_00464f58();
            sk_h_00458c98();
            sk_h_0036b270(uVar8 & 0xfffffffffffffff);
            sk_h_0036b270(uVar10 & 0xfffffffffffffff);
            uVar4 = sk_h_00464d68(uVar9 | 0x2000000000000000);
            sk_f_0041c2e4(uVar4, lVar11, param_3, param_4, param_5);
            sk_h_0036b118(uVar9);
            sk_h_00458e28(&local_118);
            if ((param_3 & 1) != 0) goto LAB_0041c5cc;
LAB_0041c500:
            sk_h_00464308();
        } else {
            sk_h_0036b270(uVar8 & 0xfffffffffffffff);
            sk_h_0036b270(uVar10 & 0xfffffffffffffff);
            if ((param_3 & 1) == 0) goto LAB_0041c500;
LAB_0041c5cc:
            if (__builtin_add_overflow(param_4, 1, (long *)0)) {
                sk_sw_breakpoint(1, 0x41c9e4);
            }
            sk_h_0006b6a0(uVar10);
        }
        sk_f_0041c2e4(param_1, param_2, param_3, param_4, param_5);   
        sk_h_0036b118(uVar10 & 0xfffffffffffffff);
        sk_h_00464d68();
        sk_h_003514e8();
        sk_f_0041c2e4(param_1, param_2, param_3, param_4, param_5);   
LAB_0041c9c0:
        sk_h_0036b118(uVar8 & 0xfffffffffffffff);
        break;
    case 4:
        uVar9 = uVar9 & 0xfffffffffffffff;
        uVar10 = *(word_t *)(uVar9 + 0x10);
        uVar1 = *(word_t *)(uVar9 + 0x18);
        uVar5 = *(word_t *)(uVar9 + 0x38);
        uVar8 = *(word_t *)(uVar9 + 0x78);
        uVar6 = 0;
        switch (uVar5 >> 0x3d) {
        default:
            uVar6 = uVar10;
            if ((uVar1 & 0xff) != 1) goto switchD_0041c59c_caseD_2;
            break;
        case 4:
            if (uVar5 == 0x8000000000000000 &&
                (((uVar1 == 0 && uVar10 == 0) &&
                  (*(long *)(uVar9 + 0x48) == 0 && *(long *)(uVar9 + 0x40) == 0)) &&
                 ((*(long *)(uVar9 + 0x30) == 0 && *(long *)(uVar9 + 0x28) == 0) &&
                  *(long *)(uVar9 + 0x20) == 0))) {
                uVar6 = 0;
            } else {
                uVar6 = (word_t)((uVar10 == 1 &&
                                 (((*(long *)(uVar9 + 0x48) == 0 && uVar1 == 0) &&
                                   (*(long *)(uVar9 + 0x40) == 0 && *(long *)(uVar9 + 0x30) == 0)) &&
                                  (*(long *)(uVar9 + 0x28) == 0 && *(long *)(uVar9 + 0x20) == 0))) &&
                                uVar5 == 0x8000000000000000);
            }
        case 2:
switchD_0041c59c_caseD_2:
            if (((uVar6 == 0) && ((param_3 & 1) != 0)) &&
                __builtin_add_overflow(param_4, 1, (long *)0)) {
                sk_sw_breakpoint(1, 0x41c9e8);
            }
        }
        sk_h_0036b270(uVar8 & 0xfffffffffffffff);
        sk_h_00464d68();
        sk_h_003514e8();
        sk_f_0041c2e4(param_1, param_2, param_3, param_4, param_5);   
        uVar8 = uVar8 & 0xfffffffffffffff;
LAB_0041c89c:
        sk_h_0008e500(uVar8, unaff_x30);
        sk_h_0036b118();
        return;
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 0xb:
        break;
    case 10:
        uVar8 = *(word_t *)((uVar9 & 0xfffffffffffffff) + 0x38);
        if ((uVar8 & 6) == 2) {
            sk_h_0036b270(uVar8 & 0xffffffffffffff9);
            uVar4 = sk_h_00464d68(uVar8 & 0xfffffffffffffff9);
            sk_f_0041c2e4(uVar4, lVar11, param_3, param_4, param_5);
            uVar8 = uVar8 & 0xffffffffffffff9;
            goto LAB_0041c89c;
        }
        break;
    }
    sk_h_0008e500(unaff_x30);
    return;
}
long sk_f_0041ca38(void)
{
    word_t uVar1;
    long lVar2;
    word_t uVar3;
    long lVar4;
    sk_h_003a25d4(0);
    sk_h_00465488();
    lVar2 = sk_h_0045636c();
    uVar1 = *(word_t *)(lVar2 + 0x10);
    if (*(word_t *)(lVar2 + 0x18) >> 1 <= uVar1) {
        uVar3 = sk_h_0006b42c();
        lVar2 = sk_h_0045636c(uVar3, uVar1 + 1, 1);
    }
    *(word_t *)(lVar2 + 0x10) = uVar1 + 1;
    lVar4 = lVar2 + uVar1 * 0x38;
    *(word_t *)(lVar4 + 0x20) = 0;
    *(word_t *)(lVar4 + 0x28) = 0;
    *(word_t *)(lVar4 + 0x30) = 0x675c68;
    uVar3 = _DAT_005a1820;
    *(word_t *)(lVar4 + 0x40) = uRam00000000005a1828;
    *(word_t *)(lVar4 + 0x38) = uVar3;
    *(word_t *)(lVar4 + 0x48) = 0xf;
    *(uint8_t *)(lVar4 + 0x50) = 1;
    uVar3 = sk_h_003567c8();
    sk_f_0041c2e4(uVar3, 0, 0, 0, 1);
    return lVar2;
}
cl4_result_t sk_f_0041cb78(void)
{
    cl4_result_t auVar1;
    auVar1.hi = 0xf;
    auVar1.lo = 0xf;
    return auVar1;
}
word_t sk_f_0041cb8c(void)
{
    uint8_t uVar1;
    long lVar2;
    word_t uVar3;
    long lVar4;
    long extraout_x8;   
    long *unaff_x19;    
    long *unaff_x20;    
    lVar2 = (long)sk_h_003504d0().lo;
    lVar4 = unaff_x19[1];
    if (*(long *)(lVar2 + 8) == 0) {
        if (lVar4 != 0) {
            return 0;
        }
        sk_h_003552a0();
        sk_h_00458da0();
    } else {
        if (lVar4 == 0) {
            sk_h_003552a0();
            sk_h_00458da0();
            return 0;
        }
        if ((*unaff_x20 != *unaff_x19 || *(long *)(lVar2 + 8) != lVar4) &&
            (uVar3 = sk_h_002a0cf8(), (uVar3 & 1) == 0)) {
            return 0;
        }
    }
    if ((((unaff_x20[3] == unaff_x19[3]) &&
          (uVar1 = (uint8_t)((word_t)unaff_x19[2] <= (word_t)unaff_x20[2]),
           unaff_x20[2] == unaff_x19[2])) &&
         (sk_h_00464d0c(unaff_x20[4]), extraout_x8 == 0)) &&
        (sk_h_00465264(unaff_x19[5]), !(bool)uVar1)) {
        return 1;
    }
    return 0;
}
uint32_t sk_f_0041cc48(word_t param_1, word_t *param_2)
{
    uint32_t uVar1;
    word_t local_50;
    word_t uStack_48;
    word_t uStack_40;
    word_t uStack_38;
    word_t local_30;
    word_t uStack_28;
    uint8_t local_20;
    uStack_48 = param_2[1];
    local_50 = *param_2;
    uStack_38 = param_2[3];
    uStack_40 = param_2[2];
    uStack_28 = param_2[5];
    local_30 = param_2[4];
    local_20 = *(uint8_t *)((uint8_t *)param_2 + 48);
    uVar1 = (uint32_t)sk_f_0041cb8c();
    return uVar1 & 1;
}

static int sk_carry8(uint64_t a, uint64_t b) { return a > UINT64_MAX - b; }
static int sk_borrow8(uint64_t a, uint64_t b) { return a < b; }
static int sk_borrow4(uint32_t a, uint32_t b) { return a < b; }
void sk_f_0041d14c();
void sk_f_0041d180();
void sk_f_0041d4a4();
cl4_result_t sk_f_0041cc98(void)
{
    word_t uVar1;
    word_t uVar2;
    long unaff_x20; 
    cl4_result_t auVar3;
    word_t local_58;
    word_t local_50;
    word_t uStack_48;
    uStack_48 = *(word_t *)(unaff_x20 + 0x10);
    local_58 = 0;
    local_50 = 0xe000000000000000;
    auVar3 = sk_h_0046647c();
    sk_h_00465db0(auVar3.lo, auVar3.hi, auVar3.lo);
    sk_h_0046299c();
    sk_h_00205844(&uStack_48, &local_58);
    uVar2 = local_50;
    uVar1 = local_58;
    sk_h_001ed960(0x3f, 0xe100000000000000, *(word_t *)(unaff_x20 + 0x18));
    sk_h_000b43e8();
    local_58 = uVar1;
    local_50 = uVar2;
    sk_h_0036b270(uVar2);
    sk_h_000b4390();
    sk_h_002acbb8();
    sk_h_003a25d4(uVar2);
    sk_h_003a25d4();
    auVar3.hi = local_50;
    auVar3.lo = local_58;
    return auVar3;
}
void sk_f_0041cd40(void)
{
    long lVar1;
    word_t extraout_x1; 
    long unaff_x19; 
    word_t uVar2;
    long lVar3;
    word_t unaff_x22; 
    word_t *puVar4;
    cl4_result_t auVar5;
    cl4_result_t auVar6;
    word_t in_stack_00000018; 
    word_t in_stack_00000020; 
    word_t in_stack_00000028; 
    word_t in_stack_00000030; 
    word_t in_stack_00000038; 
    unsigned char in_stack_00000040; 
    auVar5 = sk_h_000b4594();
    lVar3 = *(long *)(auVar5.lo + 0x10);
    lVar1 = sk_h_000a6fe0();
    if (lVar3 != 0) {
        sk_h_004651a8();
        puVar4 = (word_t *)(lVar1 + 0x28);
        do {
            in_stack_00000038 = puVar4[4];
            in_stack_00000040 = *(unsigned char *)(puVar4 + 5);
            in_stack_00000020 = puVar4[1];
            in_stack_00000018 = *puVar4;
            in_stack_00000030 = puVar4[3];
            in_stack_00000028 = puVar4[2];
            uVar2 = puVar4[2];
            sk_h_0036b270(*puVar4);
            auVar6 = sk_h_00002534(0x656248, &DAT_004e80a0);
            sk_h_0046299c(auVar6.lo, auVar6.hi, auVar6.lo);
            sk_h_00205844(&in_stack_00000020);
            sk_h_001ed960(0x3f, 0xe100000000000000, uVar2);
            sk_h_0036b270(0xe000000000000000);
            sk_h_00350a04();
            sk_h_002acbb8();
            sk_h_003a25d4(0xe000000000000000);
            sk_h_003a25d4(extraout_x1);
            sk_h_003a25d4(in_stack_00000018);
            unaff_x22 = *(word_t *)(unaff_x19 + 0x10);
            if (*(word_t *)(unaff_x19 + 0x18) >> 1 <= unaff_x22) {
                sk_h_0006a374(1 < *(word_t *)(unaff_x19 + 0x18), unaff_x22 + 1, 1);
            }
            puVar4 = puVar4 + 7;
            *(word_t *)(unaff_x19 + 0x10) = unaff_x22 + 1;
            lVar1 = unaff_x19 + unaff_x22 * 0x10;
            *(word_t *)(lVar1 + 0x20) = 0;
            *(word_t *)(lVar1 + 0x28) = 0xe000000000000000;
            lVar3 = lVar3 + -1;
        } while (lVar3 != 0);
    }
    sk_h_00463210();
    uVar2 = sk_h_00462898();
    sk_h_001bc440(0x202c, 0xe200000000000000, unaff_x22, uVar2);
    sk_h_000b43e8();
    sk_h_0036b118(unaff_x19);
    sk_h_00465800(0x28);
    sk_h_000b4390();
    sk_h_002acbb8();
    sk_h_003a25d4(unaff_x22);
    sk_h_0036b270(in_stack_00000018);
    sk_h_00100e34();
    sk_h_002acbb8();
    sk_h_003a25d4(in_stack_00000018);
    sk_h_000b45b0(unaff_x19, in_stack_00000018, auVar5.hi);
    return;
}
uint32_t sk_f_0041cf18(word_t param_1, word_t param_2, long param_3, unsigned long param_4,
                   long param_5, long param_6, long param_7, unsigned long param_8)
{
    word_t uVar1;
    word_t uVar2;
    unsigned char uVar3;
    unsigned char uVar4;
    uint32_t uVar5;
    word_t uVar6;
    word_t extraout_x8; 
    word_t uVar7;
    word_t uVar8;
    cl4_result_t auVar9;
    cl4_result_t auVar10;
    auVar9 = sk_h_00084220();
    auVar10.hi = param_6;
    auVar10.lo = param_5;
    if ((param_4 & 0xff) == 0) {
        if ((param_8 & 0xff) == 0) {
            if (auVar9.hi == 0) {
                if (param_6 == 0) goto LAB_0041d018;
            }
            else if (param_6 != 0) {
                if ((auVar9.lo != auVar10.lo) || (auVar9.hi != auVar10.hi)) {
                    sk_h_00354828();
                    uVar6 = sk_h_002a0cf8();
                    if ((uVar6 & 1) == 0) goto LAB_0041d034;
                }
LAB_0041d018:
                if (param_3 == 0) {
                    if (param_7 == 0) goto LAB_0041d028;
                }
                else if ((param_7 != 0) && (param_3 == param_7)) {
LAB_0041d028:
                    uVar5 = 1;
                    goto LAB_0041d038;
                }
            }
        }
LAB_0041d034:
        uVar5 = 0;
    }
    else {
        if (((uint32_t)param_4 & 0xff) == 1) {
            if (((uint32_t)param_8 & 0xff) != 1) goto LAB_0041d034;
            uVar1 = *(word_t *)(auVar9.lo + 0x20);
            uVar7 = *(word_t *)(param_5 + 0x10);
            uVar2 = *(word_t *)(param_5 + 0x18);
            uVar8 = *(word_t *)(param_5 + 0x20);
            uVar3 = *(unsigned char *)(param_5 + 0x28);
            uVar4 = *(unsigned char *)(auVar9.lo + 0x28);
            sk_h_0034d868();
            sk_h_00460d94();
            auVar10 = sk_h_000b43d0();
            uVar5 = sk_f_0041cf18(auVar10.lo, auVar10.hi, uVar1, uVar4, uVar7, uVar2, uVar8, uVar3);
            sk_h_0034d868();
            sk_h_00458e80();
        }
        else {
            if (((uint32_t)param_8 & 0xff) != 2) goto LAB_0041d034;
            uVar7 = *(word_t *)(param_5 + 0x10);
            sk_h_0036b270(uVar7);
            sk_h_0009461c();
            uVar5 = sk_h_004114fc();
            sk_h_0036b118(uVar7);
        }
        uVar5 = uVar5 & 1;
    }
LAB_0041d038:
    sk_h_00084234(uVar5, extraout_x8);
    return uVar5;
}
void sk_f_0041d070(void)
{
    word_t in_x4; 
    uint32_t uVar1;
    word_t in_x5; 
    long unaff_x24; 
    word_t unaff_x30; 
    cl4_result_t auVar3;
    word_t uVar2;
    sk_h_00354744();
    uVar2 = in_x5;
    sk_h_00351dc0();
    uVar1 = (uint32_t)uVar2;
    sk_h_003504d0();
    sk_h_0035053c();
    sk_h_002cb61c();
    if (((uVar1 & 0xff) != 2) || (*(long *)(*(long *)(unaff_x24 + 0x10) + 0x10) != 0)) {
        auVar3 = sk_h_00350518();
        sk_f_0041d180(auVar3.lo, auVar3.hi, in_x4, in_x5, 1);
    }
    sk_h_0035053c(0, 2);
    sk_f_0041d14c();
    sk_h_003544c8(unaff_x30);
    return;
}
void sk_f_0041d14c(param_1, param_2, param_3, param_4)
unsigned char param_1;
long param_2;
long param_3;
long param_4;
{
    long lVar1;
    if (param_2 < 0) {
        sk_sw_breakpoint(1, 0x41d178);
    }
    if (!sk_carry8((uint64_t)param_2, 1)) {
        lVar1 = 0;
        if (param_3 != 0) {
            lVar1 = param_4 - param_3;
        }
        if (param_2 + 1 <= lVar1) {
            *(unsigned char *)(param_3 + param_2) = param_1;
            return;
        }
        sk_sw_breakpoint(1, 0x41d180);
    }
    sk_sw_breakpoint(1, 0x41d17c);
}
void sk_f_0041d180(param_1, param_2, param_3, param_4, param_5, param_6, param_7, param_8)
word_t param_1;
word_t param_2;
long param_3;
unsigned long param_4;
uint32_t param_5;
word_t param_6;
word_t param_7;
long *param_8;
{
    uint32_t uVar1;
    unsigned char uVar3;
    long lVar4;
    word_t extraout_x8;   
    long extraout_x8_00;  
    long extraout_x8_01;  
    long extraout_x8_02;  
    long extraout_x8_03;  
    long lVar5;
    long lVar6;
    unsigned char *puVar7;
    word_t uVar8;
    long lVar9;
    cl4_result_t auVar10;
    auVar10 = sk_h_00351e20();
    uVar1 = (uint32_t)param_4 & 0xff;
    uVar3 = 0;
    if ((param_4 & 0xff) == 0) {
        if (param_3 != 0) {
            sk_h_00002874(&s_Cannot_encode_a_capture_structur_005e1f50);
            sk_h_003593c0();
            sk_h_00002818();
            sk_h_001afa84();
        }
        if (auVar10.hi == 0) {
            sk_h_003523fc(1, *param_8);
            sk_f_0041d14c();
            sk_h_00465d3c();
            lVar6 = extraout_x8_03;
            if ((bool)uVar3) {
                sk_sw_breakpoint(1, 0x41d350);
            }
        }
        else {
            sk_h_003523fc(2, *param_8);
            sk_f_0041d14c();
            lVar6 = *param_8 + 1;
            if (sk_carry8((uint64_t)*param_8, 1)) {
                sk_sw_breakpoint(1, 0x41d398);
            }
            *param_8 = lVar6;
            sk_h_00350470();
            lVar9 = sk_h_00268540();
            lVar5 = *(long *)(lVar9 + 0x10);
            if (sk_carry8((uint64_t)lVar6, (uint64_t)lVar5)) {
                sk_sw_breakpoint(1, 0x41d39c);
            }
            if (lVar6 + lVar5 < lVar6) {
                sk_sw_breakpoint(1, 0x41d3a0);
            }
            sk_h_003523fc(lVar6);
            auVar10 = sk_h_003207d4();
            lVar6 = 0;
            if (param_3 != 0) {
                lVar6 = param_3 + auVar10.lo;
            }
            lVar4 = auVar10.hi - auVar10.lo;
            if (lVar4 < 0) {
                sk_sw_breakpoint(1, 0x41d3a4);
            }
            if (lVar4 == 0) {
                if (lVar6 != 0) goto LAB_0041d354;
                lVar4 = 0;
            }
            else {
                if (lVar6 == 0) {
                    sk_sw_breakpoint(1, 0x41d3b0);
                }
LAB_0041d354:
                lVar4 = lVar6 + lVar4;
            }
            sk_h_002cb61c(lVar9 + 0x20, lVar9 + 0x20 + *(long *)(lVar9 + 0x10), lVar6, lVar4);
            sk_h_0036b118(lVar9);
            lVar6 = *param_8 + lVar5;
            if (sk_carry8((uint64_t)*param_8, (uint64_t)lVar5)) {
                sk_sw_breakpoint(1, 0x41d3a8);
            }
        }
    }
    else {
        uVar3 = sk_borrow4(uVar1, 1);
        if (uVar1 == 1) {
            uVar8 = *(word_t *)(auVar10.lo + 0x10);
            sk_h_00350b18(uVar8);
            sk_h_00460d94();
            sk_h_00350b18(uVar8);
            sk_h_00466580();
            sk_h_00350b18(uVar8);
            sk_h_00458e80();
            sk_h_003523fc(4, *param_8);
            sk_f_0041d14c();
            sk_h_00465d3c();
            lVar6 = extraout_x8_00;
            if ((bool)uVar3) {
                sk_sw_breakpoint(1, 0x41d210);
            }
        }
        else {
            lVar6 = *(long *)(auVar10.lo + 0x10);
            if ((param_5 & 1) == 0) {
                sk_h_003523fc(5, *param_8);
                sk_f_0041d14c();
                sk_h_00465d3c();
                if ((bool)uVar3) {
                    sk_sw_breakpoint(1, 0x41d3ac);
                }
                *param_8 = extraout_x8_01;
                uVar3 = false;
            }
            lVar9 = *(long *)(lVar6 + 0x10);
            if (lVar9 != 0) {
                sk_h_0036b270(lVar6);
                puVar7 = (unsigned char *)(lVar6 + 0x38);
                do {
                    uVar8 = *(word_t *)(puVar7 + -8);
                    uVar3 = *puVar7;
                    auVar10 = sk_h_000dbd0c();
                    sk_h_00460d94(auVar10.lo, auVar10.hi, uVar8, uVar3);
                    auVar10 = sk_h_000dbd0c();
                    sk_h_00466580(auVar10.lo, auVar10.hi, uVar8, uVar3);
                    auVar10 = sk_h_000dbd0c();
                    sk_h_00458e80(auVar10.lo, auVar10.hi, uVar8, uVar3);
                    uVar3 = sk_borrow8((uint64_t)lVar9, 1);
                    lVar9 = lVar9 + -1;
                    puVar7 = puVar7 + 0x20;
                } while (lVar9 != 0);
                sk_h_0036b118(lVar6);
            }
            if ((param_5 & 1) != 0) goto LAB_0041d380;
            sk_h_003523fc(6, *param_8);
            sk_f_0041d14c();
            sk_h_00465d3c();
            lVar6 = extraout_x8_02;
            if ((bool)uVar3) {
                sk_sw_breakpoint(1, 0x41d338);
            }
        }
    }
    *param_8 = lVar6;
LAB_0041d380:
    sk_h_00351d30(extraout_x8);
    return;
}
void sk_f_0041d3e8(void)
{
    long lVar2;
    long *unaff_x20; 
    if (*(long *)(*unaff_x20 + 0x10) == 0) {
        sk_sw_breakpoint(1, 0x41d430);
    }
    lVar2 = sk_h_004613d4();
    if (lVar2 != 0) {
        return;
    }
    sk_h_0046134c(*(long *)(*unaff_x20 + 0x10) + -1);
    return;
}
void sk_f_0041d430(word_t param_1, word_t param_2, word_t param_3, word_t param_4)
{
    unsigned char auStack_88[32];
    word_t local_68;
    word_t uStack_60;
    word_t local_58;
    sk_h_00463998(param_1, param_1, param_2, param_3, param_4);
    uStack_60 = uRam00000000004be5e8;
    local_68 = _DAT_004be5e0;
    local_58 = 0xe000000000000000;
    sk_h_00463600();
    sk_f_0041d4a4(auStack_88);
    uStack_60 = 0;
    local_58 = 0xe000000000000000;
    sk_h_004590e0(auStack_88);
    sk_h_0009461c();
    return;
}
void sk_f_0041d4a4(param_1, param_2, param_3, param_4, param_5)
long param_1;
long param_2;
long param_3;
long param_4;
char param_5;
{
    unsigned char uVar2;
    unsigned char uVar3;
    word_t extraout_x8;   
    word_t extraout_x8_00; 
    long lVar4;
    word_t uVar5;
    long lVar6;
    long lVar7;
    cl4_result_t auVar8;
    long local_68[3];
    if (param_5 == '\0') {
        lVar6 = -0x16ffffffffffffc2;
        lVar4 = lVar6;
        if (param_3 != 0) {
            lVar4 = param_3;
        }
        if (param_4 == 0) {
            sk_h_00460d94(0x64656d616e6e753c, param_2, param_3, 0);
        }
        else {
            local_68[1] = 0;
            local_68[2] = -0x2000000000000000;
            local_68[0] = param_4;
            sk_h_00460d94(param_2, param_3, param_4, 0);
            auVar8 = sk_h_00002534(0x657ae0, &DAT_005a3520);
            sk_h_00465db0(auVar8.lo, auVar8.hi, auVar8.lo);
            sk_h_0046299c();
            sk_h_00205844(local_68, local_68 + 1);
            lVar6 = local_68[2];
        }
        sk_h_00465800(0x286d6f7441);
        sk_h_00100efc();
        sk_h_002acbb8();
        sk_h_003a25d4(lVar4);
        sk_h_002acbb8(0x203a, 0xe200000000000000);
        sk_h_00350518();
        sk_h_002acbb8();
        sk_h_003a25d4(lVar6);
        sk_h_00100e34();
        sk_h_002acbb8();
        lVar4 = local_68[2];
        sk_h_0044ca60();
        sk_h_0036b270(lVar4);
        sk_h_000b4390();
        sk_h_002acbb8();
        sk_h_003a25d4(lVar4);
        sk_h_00463af8();
        sk_h_003a25d4(lVar4);
    }
    else {
        if (param_5 == '\x01') {
            uVar5 = *(word_t *)(param_2 + 0x20);
            uVar3 = *(unsigned char *)(param_2 + 0x28);
            auVar8 = sk_h_000b4390();
            sk_h_00460d94(auVar8.lo, auVar8.hi, uVar5, uVar3);
            sk_h_0044ca60();
            sk_h_002acbb8(0x6c616e6f6974704f, 0xea00000000007b20);
            sk_h_00463af8();
            sk_h_004645ec();
            uVar2 = sk_carry8((uint64_t)*(long *)(param_1 + 0x40), 1);
            if ((bool)uVar2) {
                sk_sw_breakpoint(1, 0x41d770);
            }
            *(long *)(param_1 + 0x40) = *(long *)(param_1 + 0x40) + 1;
            sk_h_0034c444(param_1);
            sk_f_0041d4a4();
            auVar8 = sk_h_000b4390();
            sk_h_00458e80(auVar8.lo, auVar8.hi, uVar5, uVar3);
            sk_h_00465d1c();
            uVar5 = extraout_x8;
            if ((bool)uVar2) {
                sk_sw_breakpoint(1, 0x41d560);
            }
        }
        else {
            lVar4 = *(long *)(param_2 + 0x10);
            sk_h_0036b270(lVar4);
            sk_h_0044ca60();
            sk_h_002acbb8(0x7b20656c707554, 0xe700000000000000);
            sk_h_00463af8();
            sk_h_004645ec();
            if (sk_carry8((uint64_t)*(long *)(param_1 + 0x40), 1)) {
                sk_sw_breakpoint(1, 0x41d774);
            }
            *(long *)(param_1 + 0x40) = *(long *)(param_1 + 0x40) + 1;
            lVar6 = *(long *)(lVar4 + 0x10);
            uVar3 = false;
            if (lVar6 != 0) {
                lVar7 = lVar4 + 0x38;
                do {
                    uVar5 = *(word_t *)(lVar7 + -0x18);
                    lVar7 = lVar7 + 0x20;
                    sk_h_003505c4(uVar5);
                    sk_h_00460d94();
                    sk_h_0009461c();
                    sk_h_003511f0();
                    sk_f_0041d4a4();
                    sk_h_003505c4(uVar5);
                    sk_h_00458e80();
                    uVar3 = sk_borrow8((uint64_t)lVar6, 1);
                    lVar6 = lVar6 + -1;
                } while (lVar6 != 0);
            }
            sk_h_0036b118(lVar4);
            sk_h_00465d1c();
            uVar5 = extraout_x8_00;
            if ((bool)uVar3) {
                sk_sw_breakpoint(1, 0x41d778);
            }
        }
        *(word_t *)(param_1 + 0x40) = uVar5;
        sk_h_0044ca60();
        sk_h_00463878();
        sk_h_002acbb8();
        sk_h_00463af8();
    }
    sk_h_004645ec();
    return;
}
cl4_result_t sk_f_0041d778(void)
{
    cl4_result_t auVar1;
    long unaff_x20; 
    auVar1 = *(cl4_result_t *)(unaff_x20 + 0x28);
    *(word_t *)(unaff_x20 + 0x28) = 0;
    *(word_t *)(unaff_x20 + 0x30) = 0xe000000000000000;
    return auVar1;
}
void sk_f_0041d788(void)
{
    sk_h_003509ec();
    sk_h_0044ca60();
    sk_h_0036b270();
    sk_h_00100efc();
    sk_h_002acbb8();
    sk_h_003a25d4();
    sk_h_00463af8();
    sk_h_004645ec();
    return;
}