/* Recreated from cl4_kernel.raw (cL4 Secure Kernel, arm64e, image base 0) —
 * the cL4 microkernel (GL1). Ground truth: Ghidra FUN_ names + addresses.
 * All names are estimates unless string/header matched.
 * Slice 08: 0x339ca8-0x344290 syscall/exception-entry region. */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "sk_internal.h"
#include "sk_region_syscalls.h"

/* Ghidra undefined* type aliases (fixed-width), kept for decompile fidelity. */
typedef uint8_t   undefined1;
typedef uint16_t  undefined2;
typedef uint32_t  undefined4;
typedef uint64_t  undefined8;
typedef unsigned long ulong;

/* Global lazy-init dispatch slots (DAT_006575xx) written by thunks/inits. */
extern word_t DAT_006575b0, DAT_006575c8, DAT_006575d0, DAT_006575d8;
extern word_t DAT_006575e0, DAT_006575e8;

/* Forward declarations (functions defined later in this file). */
word_t sk_ctx_thunk_6574f0(void);   /* FUN_00342a38 */
word_t sk_ctx_thunk_6574f8(void);   /* FUN_00342ab4 */
word_t sk_ctx_thunk_657500(void);   /* FUN_00342b10 */
word_t sk_ctx_thunk_657508(void);   /* FUN_00342b68 */
word_t sk_ctx_thunk_657528(void);   /* FUN_00342c9c */
word_t sk_ctx_thunk_657530(void);   /* FUN_00342d18 */
word_t sk_ctx_thunk_657540(void);   /* FUN_00342e50 */
word_t sk_ctx_thunk_657558(void);   /* FUN_00342f2c */
word_t sk_ctx_thunk_657560(void);   /* FUN_00342fa8 */
void sk_ctx_dispatch_20(void);      /* FUN_00343d18 */

/* In-region callees (0x300000-0x380000) reconstructed by sibling SK workers.
 * Names are estimates; FUN_ address in comment is ground truth. */
extern void *sk_cpu_enter(void);             /* FUN_00084220: returns ctx (extraout_x16) */
extern void *sk_ctx_aquire(void);            /* FUN_00348c64: returns ctx */
extern void sk_ctx_set_tag(uint8_t tag);     /* FUN_0034cce0 */
extern void sk_cpu_exit(void *ret, ...);     /* FUN_00084234 */
extern void sk_obj_complete(void);           /* FUN_000839d8 */
extern int sk_queue_complete(void *q, unsigned long op, ...); /* FUN_000839f8 */
extern word_t sk_try_acquire(word_t);        /* FUN_0006b6f4 */
extern unsigned long sk_object_lock(unsigned long a, unsigned long b,
                                    unsigned long c, void *dbg1, void *dbg2); /* FUN_00377824 */
extern void sk_lock_release(unsigned long a, ...);        /* FUN_00377dcc */
extern void sk_free(void *ptr);              /* FUN_0036b118 */
extern void sk_retain(void *obj);            /* FUN_0036b270 / thunk_FUN_0036b270 */
extern void sk_ref_release(unsigned long a, unsigned long b); /* FUN_00376820 */
extern void sk_obj_meta(word_t v);           /* FUN_003a25d4 */
extern void sk_obj_method(void);             /* FUN_00349530 */
extern cl4_result_t sk_obj_resolve(word_t a, void *b);   /* FUN_00349394 */
extern unsigned long sk_lock_state_check(void);          /* FUN_00354ce4 */
extern void sk_cpu_enter_kernel(void);       /* FUN_0034c7c4 */
extern void sk_state_enter(void);            /* FUN_003504d0 */
extern void sk_syscall_op(unsigned long a, unsigned long b, unsigned long op); /* FUN_003728b8 */
extern cl4_result_t sk_state_fetch(void);    /* FUN_003538f0 */
extern void sk_rec_acquire(void);            /* FUN_000a93e4 */
extern void sk_rec_release_hi(word_t a, word_t b);   /* FUN_000a9454 */
extern void sk_obj_path(void *dst, void *src);        /* FUN_00349b00 */
extern void sk_obj_read(void);               /* FUN_00355938 */
extern void sk_region_resolve(void);         /* FUN_0034f7d8 */
extern void sk_alloc_page_ref(void *obj);    /* FUN_0036b270 (retain/alloc) */
extern void sk_sched_notify(unsigned long a, void *b); /* FUN_00349e24 */
extern cl4_result_t sk_object_alloc2(void);  /* FUN_0034c16c */
extern void sk_irq_restore2(void);           /* FUN_0035884c */
extern void sk_cpu_enter_syscall(void);      /* FUN_003504d0 */

/* Generic context fetch/enter helpers (FUN_ addr in comment = ground truth).
 * Names collapsed to reduce estimate noise; each maps to one Ghidra FUN_. */
extern void *sk_ctx_fetch(void);            /* single-context fetchers */
extern cl4_result_t sk_ctx_fetch_pair(void);/* pair-returning fetchers */
extern void sk_state_enter2(void);          /* enter/transition helpers */

/*--------------------------------------------------------------------*/
/* FUN_00339ca8 @ 0x00339ca8   (est. sk_syscall_ctl)
 * Ghidra: undefined8 FUN_00339ca8(undefined8, undefined8, undefined8)
 * Syscall handler: releases the caller lock, re-checks scheduler state, and on
 * the ready path allocates a kernel object (selector 3) and runs a syscall op
 * with selector 3 before restoring IRQ state. Returns the op result (default 3).
 * Confidence: low (callee bodies not yet reconstructed; branch gated by
 *   condition flags from sk_lock_state_check).
 */
unsigned long sk_syscall_ctl(unsigned long p1, unsigned long p2,
                             unsigned long result)
{
    void *ctx = NULL;                   /* unaff_x19: caller-saved context reg */

    sk_cpu_enter_kernel();              /* FUN_0034c7c4 */
    sk_lock_release(0);                 /* FUN_00377dcc */
    if (sk_lock_state_check()) {        /* FUN_00354ce4 */
        sk_sched_notify(sk_lock_state_check(), (void *)(ctx + 0x18)); /* FUN_00349e24 */
        sk_object_lock(0x13f, 0, 0, NULL, NULL);       /* FUN_00377824 */
        if (sk_lock_state_check()) {    /* FUN_00354ce4 */
            cl4_result_t obj = sk_object_alloc2();     /* FUN_0034c16c */
            result = 3;
            sk_syscall_op(obj.lo, obj.hi, 3);          /* FUN_003728b8 */
            sk_irq_restore2();                         /* FUN_0035884c */
        }
    }
    return result;
}

/*--------------------------------------------------------------------*/
/* FUN_00339d44 @ 0x00339d44   (est. sk_syscall_ctl_path)
 * Ghidra: void FUN_00339d44(undefined8, undefined8, long param_3)
 * Syscall handler with a capability-path operation. Fetches a context record,
 * resolves an object path (sk_obj_resolve + sk_object_lock), then either
 * dispatches through the context's method table (offset +0x10) or, on the
 * bounds-check failure path, copies a record and releases.
 * Confidence: low (heavy extraout_* register aliasing; method-dispatch via
 *   context-relative function pointer table).
 * Notes: callees FUN_00351e20 / FUN_00349b00 / FUN_00349394 / FUN_00377824 /
 *   FUN_000a6f88 / FUN_00350968 / FUN_003504f4 / FUN_00358bb4 / FUN_0036b270 /
 *   FUN_00351d30.
 */
void sk_syscall_ctl_path(unsigned long p1, unsigned long p2, unsigned long p3)
{
    void *ctxA;                      /* extraout_x16 */
    void *ctxB;                      /* extraout_x16_00 */
    void *dst;                       /* auVar11._0_8_ */
    word_t val;
    word_t countA, countB;
    word_t maskA, maskB;
    long baseA;                      /* extraout_x8 + 0x40 */
    word_t cap;                      /* FUN_000a6f88 */

    dst = (void *)sk_state_fetch().lo;            /* FUN_00351e20: pair base */
    val = *(word_t *)(p3 + 0x10);
    sk_obj_path(dst, (void *)(p3 + 0x18));        /* FUN_00349b00 */
    baseA = *(long *)(ctxA + 0x40);
    countA = (word_t)*(uint8_t *)(ctxA + 0x50);
    maskA = countA & 0xff;
    countB = (word_t)*(uint8_t *)(ctxB + 0x50);
    maskB = countB & 0xff;

    {
        cl4_result_t r = sk_obj_resolve(0, 0);    /* FUN_00349394 */
        sk_object_lock(r.lo, r.hi, val, NULL, NULL);  /* FUN_00377824 */
    }
    cap = 0;                                       /* FUN_000a6f88 (unrecovered) */

    if (((maskB | maskA) < 8 && ((countB | countA) & 0x100000) == 0) &&
        ((baseA + (uint8_t)countB + (baseA + (uint8_t)countA & ~maskA) & ~maskB) +
         *(long *)(ctxA + 0x40)) < 0x19) {
        void (*meth)(void) = *(void (**)(void))(ctxA + 0x10);
        meth();                                    /* FUN_00350968 path */
        cl4_result_t r2 = sk_obj_resolve(0, 0);    /* FUN_003504f4 */
        meth();
        (*(void (**)(word_t, word_t, word_t))(ctxB + 0x10))
            ((baseA + (long)dst & ~maskA) + baseA + maskB & ~maskB,
             (baseA + (long)dst & ~maskA) + baseA + maskB & ~maskB, cap);
    } else {
        *(word_t *)dst = 0;                        /* *dst = auVar11._8_8_ */
        dst = (void *)(0 + 0);                     /* FUN_00358bb4 + extraout_x8_01 */
        sk_retain(dst);                            /* FUN_0036b270 */
    }
    sk_cpu_exit(dst);                              /* FUN_00351d30 */
}

/*--------------------------------------------------------------------*/
/* FUN_00339eb8 @ 0x00339eb8   (est. sk_syscall_ctl_method)
 * Ghidra: void FUN_00339eb8(void)
 * Syscall handler: enter state, fetch a value from the context (+0x10),
 * resolve a context (+0x40/0x50), dispatch through the method table at +8.
 * Indirect-jump table (FUN_0034bf0c) prevents full control-flow recovery.
 * Confidence: low.
 * Notes: callees FUN_003504d0 / FUN_0034b3c8 / FUN_0006b6f4 / FUN_00349394 /
 *   FUN_00377824 / FUN_0034bf0c; WARNING "could not recover jumptable".
 */
void sk_syscall_ctl_method(void)
{
    void *ctxA;                      /* extraout_x16 */
    void *ctxB;                      /* extraout_x16_00 */
    word_t val;
    long base;                       /* extraout_x16 + 0x40 */
    uint8_t tag;                     /* +0x50 byte */

    sk_state_enter();                /* FUN_003504d0 */
    val = *(word_t *)(0 + 0x10);     /* extraout_x1 + 0x10 */
    { cl4_result_t r = sk_obj_resolve(0, 0); (void)r; }  /* FUN_0034b3c8 */
    void (*meth)(void) = *(void (**)(void))(ctxA + 8);
    meth();
    base = *(long *)(ctxA + 0x40);
    tag = *(uint8_t *)(ctxA + 0x50);
    sk_try_acquire(0);               /* FUN_0006b6f4 */
    meth();
    { cl4_result_t r = sk_obj_resolve(0, 0); (void)r; }  /* FUN_00349394 */
    sk_object_lock(0, 0, val, NULL, NULL);          /* FUN_00377824 */
    /* FUN_0034bf0c: indirect jump table (jumptable) */
    (*(void (**)(word_t))(ctxB + 8))
        ((base + 0 + (word_t)tag & ~((word_t)tag)) +
         base + (word_t)*(uint8_t *)(ctxB + 0x50) &
         ~((word_t)*(uint8_t *)(ctxB + 0x50)));
}

/*--------------------------------------------------------------------*/
/* FUN_00339f70 @ 0x00339f70   (est. sk_syscall_method_10)
 * Ghidra: void FUN_00339f70(void)
 * Syscall handler dispatching through the context method table at offset
 * +0x10. Acquires the per-CPU context (FUN_00084220), resolves and locks the
 * object (sk_obj_resolve + sk_object_lock), then calls the method with two
 * address-aligned operands. Paired enter/exit (FUN_00084220/FUN_00084234).
 * Confidence: low (extraout_* register aliasing; indirect method dispatch).
 * Notes: callees FUN_00084220 / FUN_00348c64 / FUN_0034cce0 / FUN_00349394 /
 *   FUN_00377824 / FUN_00349530 / FUN_00084234.
 */
void sk_syscall_method_10(void)
{
    void *ctxA = sk_cpu_enter();     /* FUN_00084220 */
    void *ctxB = sk_ctx_aquire();    /* FUN_00348c64 */
    void (*meth)(void);
    long base;
    uint8_t tag;

    meth = *(void (**)(void))(ctxA + 0x10);
    meth();
    base = *(long *)(ctxA + 0x40);
    sk_ctx_set_tag(*(uint8_t *)(ctxA + 0x50));    /* FUN_0034cce0 */
    meth();
    { cl4_result_t r = sk_obj_resolve(0, 0); (void)r; }  /* FUN_00349394 */
    sk_object_lock(0, 0, 0, NULL, NULL);         /* FUN_00377824 */
    sk_obj_method();                 /* FUN_00349530 */
    tag = *(uint8_t *)(ctxB + 0x50);
    base += tag;
    (*(void (**)(word_t, word_t))(ctxB + 0x10))
        (base + 0 & ~((word_t)tag), base + 0 & ~((word_t)tag));
    sk_cpu_exit(0);                  /* FUN_00084234 */
}

/*--------------------------------------------------------------------*/
/* FUN_0033a01c @ 0x0033a01c   (est. sk_syscall_method_18)
 * Ghidra: void FUN_0033a01c(void)
 * Same template as sk_syscall_method_10 but dispatches through the method
 * table slot at +0x18.
 * Confidence: low.
 */
void sk_syscall_method_18(void)
{
    void *ctxA = sk_cpu_enter();     /* FUN_00084220 */
    void *ctxB = sk_ctx_aquire();    /* FUN_00348c64 */
    void (*meth)(void);
    long base;
    uint8_t tag;

    meth = *(void (**)(void))(ctxA + 0x18);
    meth();
    base = *(long *)(ctxA + 0x40);
    sk_ctx_set_tag(*(uint8_t *)(ctxA + 0x50));    /* FUN_0034cce0 */
    meth();
    { cl4_result_t r = sk_obj_resolve(0, 0); (void)r; }  /* FUN_00349394 */
    sk_object_lock(0, 0, 0, NULL, NULL);         /* FUN_00377824 */
    sk_obj_method();                 /* FUN_00349530 */
    tag = *(uint8_t *)(ctxB + 0x50);
    base += tag;
    (*(void (**)(word_t, word_t))(ctxB + 0x18))
        (base + 0 & ~((word_t)tag), base + 0 & ~((word_t)tag));
    sk_cpu_exit(0);                  /* FUN_00084234 */
}

/*--------------------------------------------------------------------*/
/* FUN_0033a0c8 @ 0x0033a0c8   (est. sk_syscall_method_20)
 * Ghidra: void FUN_0033a0c8(void)
 * Same template dispatching through the method table slot at +0x20.
 * Confidence: low.
 */
void sk_syscall_method_20(void)
{
    void *ctxA = sk_cpu_enter();     /* FUN_00084220 */
    void *ctxB = sk_ctx_aquire();    /* FUN_00348c64 */
    void (*meth)(void);
    long base;
    uint8_t tag;

    meth = *(void (**)(void))(ctxA + 0x20);
    meth();
    base = *(long *)(ctxA + 0x40);
    sk_ctx_set_tag(*(uint8_t *)(ctxA + 0x50));    /* FUN_0034cce0 */
    meth();
    { cl4_result_t r = sk_obj_resolve(0, 0); (void)r; }  /* FUN_00349394 */
    sk_object_lock(0, 0, 0, NULL, NULL);         /* FUN_00377824 */
    sk_obj_method();                 /* FUN_00349530 */
    tag = *(uint8_t *)(ctxB + 0x50);
    base += tag;
    (*(void (**)(word_t, word_t))(ctxB + 0x20))
        (base + 0 & ~((word_t)tag), base + 0 & ~((word_t)tag));
    sk_cpu_exit(0);                  /* FUN_00084234 */
}

/*--------------------------------------------------------------------*/
/* FUN_0033a174 @ 0x0033a174   (est. sk_syscall_method_28)
 * Ghidra: void FUN_0033a174(void)
 * Same template dispatching through the method table slot at +0x28.
 * Confidence: low.
 */
void sk_syscall_method_28(void)
{
    void *ctxA = sk_cpu_enter();     /* FUN_00084220 */
    void *ctxB = sk_ctx_aquire();    /* FUN_00348c64 */
    void (*meth)(void);
    long base;
    uint8_t tag;

    meth = *(void (**)(void))(ctxA + 0x28);
    meth();
    base = *(long *)(ctxA + 0x40);
    sk_ctx_set_tag(*(uint8_t *)(ctxA + 0x50));    /* FUN_0034cce0 */
    meth();
    { cl4_result_t r = sk_obj_resolve(0, 0); (void)r; }  /* FUN_00349394 */
    sk_object_lock(0, 0, 0, NULL, NULL);         /* FUN_00377824 */
    sk_obj_method();                 /* FUN_00349530 */
    tag = *(uint8_t *)(ctxB + 0x50);
    base += tag;
    (*(void (**)(word_t, word_t))(ctxB + 0x28))
        (base + 0 & ~((word_t)tag), base + 0 & ~((word_t)tag));
    sk_cpu_exit(0);                  /* FUN_00084234 */
}

/*--------------------------------------------------------------------*/
/* FUN_0033ab24 @ 0x0033ab24   (est. sk_ctx_copy_tag)
 * Ghidra: void FUN_0033ab24(void)
 * Copies the trailing 3 bytes (0x20..0x22) of the source context record to
 * the destination record after the enter/retain/meta sequence.
 * Confidence: low (helper bodies not yet reconstructed).
 * Notes: helpers FUN_0034b264 / FUN_00352028 / FUN_0036b270 / FUN_003a25d4 /
 *   FUN_0035270c.
 */
void sk_ctx_copy_tag(void)
{
    void *src = (void *)0;          /* unaff_x19 */
    void *dst = (void *)0;          /* unaff_x20 */

    sk_state_enter2();              /* FUN_0034b264 */
    sk_state_enter2();              /* FUN_00352028 */
    sk_retain(0);                   /* thunk_FUN_0036b270 */
    sk_obj_meta(0);                 /* FUN_003a25d4 */
    sk_state_enter2();              /* FUN_0035270c */
    *(uint16_t *)(dst + 0x20) = *(uint16_t *)(src + 0x20);
    *(uint8_t *)(dst + 0x22) = *(uint8_t *)(src + 0x22);
}

/*--------------------------------------------------------------------*/
/* FUN_0033ab88 @ 0x0033ab88   (est. sk_ctx_copy_full)
 * Ghidra: void FUN_0033ab88(void)
 * Copies the full record (fields 0x10/0x18/0x20/0x22) between contexts after
 * the state-enter helpers.
 * Confidence: low.
 * Notes: helpers FUN_003504d0 / FUN_00359124.
 */
void sk_ctx_copy_full(void)
{
    void *src = (void *)0;          /* unaff_x19 */
    void *dst = (void *)0;          /* unaff_x20 */

    sk_state_enter();               /* FUN_003504d0 */
    sk_ctx_fetch_pair();            /* FUN_00359124 */
    *(word_t *)(dst + 0x10) = *(word_t *)(src + 0x10);
    *(word_t *)(dst + 0x18) = *(word_t *)(src + 0x18);
    *(uint16_t *)(dst + 0x20) = *(uint16_t *)(src + 0x20);
    *(uint8_t *)(dst + 0x22) = *(uint8_t *)(src + 0x22);
}

/*--------------------------------------------------------------------*/
/* FUN_0033ac5c @ 0x0033ac5c   (est. sk_ctx_swap_field8)
 * Ghidra: void FUN_0033ac5c(void)
 * Swaps the 8-byte field at +8 of the record with the fetched context's field,
 * retaining the new value and releasing metadata on the old.
 * Confidence: low.
 * Notes: helpers FUN_0034f2f4 / FUN_0036b270 / FUN_003a25d4.
 */
void sk_ctx_swap_field8(void)
{
    void *ctx = (void *)0;          /* unaff_x19 */
    word_t old;

    ctx = sk_ctx_fetch();           /* FUN_0034f2f4 */
    old = *(word_t *)(ctx + 8);
    *(word_t *)(ctx + 8) = *(word_t *)(ctx + 8);   /* extraout_x1 + 8 */
    sk_retain(ctx);                 /* thunk_FUN_0036b270 */
    sk_obj_meta(old);               /* FUN_003a25d4 */
}

/*--------------------------------------------------------------------*/
/* FUN_0033aed8 @ 0x0033aed8   (est. sk_lock_ctl_threshold)
 * Ghidra: void FUN_0033aed8(void)
 * Enters the kernel, releases the caller lock, and when the returned count
 * value is below 0x40 runs a small housekeeping sequence.
 * Confidence: low.
 * Notes: helpers FUN_0034c7c4 / FUN_00377dcc / FUN_0034d1c0 / FUN_00368980 /
 *   FUN_00019858; threshold on extraout_x1.
 */
void sk_lock_ctl_threshold(void)
{
    word_t n;

    sk_cpu_enter_kernel();          /* FUN_0034c7c4 */
    sk_lock_release(0);             /* FUN_00377dcc */
    n = 0;                          /* extraout_x1 */
    if (n < 0x40) {
        sk_ctx_fetch();             /* FUN_0034d1c0 */
        sk_ctx_fetch();             /* FUN_00368980 */
        sk_try_acquire(0);          /* FUN_00019858 */
    }
}

/*--------------------------------------------------------------------*/
/* FUN_0033af48 @ 0x0033af48   (est. sk_encode_varlen)
 * Ghidra: long FUN_0033af48(void)
 * Encodes a variable-length field into the buffer at x19 at offset x20.
 * Reads a size byte; if > 1 reads 1-4 bytes and shifts them into a value, then
 * either writes the result (single byte via FUN_0035504c, or 0 via FUN_00352c04)
 * or returns an error. Bounds check rejects offsets > 0x18.
 * Confidence: low (register aliasing; conditional flag semantics).
 * Notes: callees FUN_00349d3c / FUN_00357ec4 / FUN_0035556c / FUN_0036b270 /
 *   FUN_0035504c / FUN_00352c04 / FUN_00117cc4; software-breakpoint absent.
 */
long sk_encode_varlen(void)
{
    void *buf = (void *)0;          /* unaff_x19 */
    uint32_t off = 0;               /* unaff_x20 */
    void *ctx;                      /* extraout_x8 */
    word_t base;
    uint8_t size_byte;
    uint32_t val;

    sk_ctx_fetch();                 /* FUN_00349d3c */
    sk_ctx_fetch();                 /* FUN_00357ec4 */
    base = *(word_t *)(ctx + 0x50);
    if ((base & 0x1000f8) != 0 || 0x18 < off + 1U) {
        long err = 0;               /* FUN_0035556c(base & 0xf8) */
        sk_retain(0);               /* FUN_0036b270 */
        return err + ((0 + 0x17 & ~0U) & 0x1f8);
    }
    size_byte = *(uint8_t *)((char *)buf + off);
    val = size_byte;
    if (1 < size_byte) {
        uint32_t shift = (off & 3) << 3;
        uint32_t width = 4;
        if (off < 4) width = off;
        switch (width) {
        case 1: val = (uint8_t)*(uint8_t *)buf; break;
        case 2: val = (uint16_t)*(uint16_t *)buf; break;
        case 3: val = (uint32_t)*(uint32_t *)buf & 0xffffff; break;
        default: val = *(uint32_t *)buf; break;
        }
        val = (val | (size_byte - 2) << shift);
        if (off > 3) val = *(uint32_t *)buf;
        val += 2;
    }
    if (val == 1) {
        sk_ctx_fetch();             /* FUN_0035504c */
        *(uint8_t *)((char *)buf + off) = 0;   /* extraout_w8 */
    } else if (val == 0) {
        sk_ctx_fetch();             /* FUN_00352c04 */
        (*(void (**)(void))ctx)();  /* extraout_x9 */
        *(uint8_t *)((char *)buf + off) = 0;
    } else {
        return 0;                   /* FUN_00117cc4 error path */
    }
    return (long)buf;
}

/*--------------------------------------------------------------------*/
/* FUN_0033bce4 @ 0x0033bce4   (est. sk_ctx_release_field30)
 * Ghidra: void FUN_0033bce4(void)
 * Releases the object field at +0x30 of the record after the meta/enter steps.
 * Confidence: low.
 * Notes: helpers FUN_00358c20 / FUN_003a25d4 / FUN_0036b118.
 */
void sk_ctx_release_field30(void)
{
    void *ctx = (void *)0;          /* unaff_x19 */

    sk_ctx_fetch();                 /* FUN_00358c20 */
    sk_obj_meta(0);                 /* FUN_003a25d4 */
    sk_free((void *)*(word_t *)(ctx + 0x30));   /* FUN_0036b118 */
}

/*--------------------------------------------------------------------*/
/* FUN_0033bd10 @ 0x0033bd10   (est. sk_ctx_copy_rest)
 * Ghidra: void FUN_0033bd10(void)
 * Copies the trailing record fields (0x30/0x38/0x3c/0x3f/0x43) from the
 * fetched context into the local record, then retains twice.
 * Confidence: low.
 * Notes: helpers FUN_00350e04 / FUN_003577f0 / FUN_0036b270.
 */
void sk_ctx_copy_rest(void)
{
    void *ctx = (void *)0;          /* unaff_x19 */
    word_t v;

    sk_ctx_fetch_pair();            /* FUN_00350e04 */
    sk_ctx_fetch();                 /* FUN_003577f0 */
    v = *(word_t *)(ctx + 0x30);
    *(word_t *)(ctx + 0x30) = v;
    *(uint8_t *)(ctx + 0x38) = *(uint8_t *)(ctx + 0x38);
    *(uint32_t *)(ctx + 0x3c) = *(uint32_t *)(ctx + 0x3c);
    *(uint32_t *)(ctx + 0x3f) = *(uint32_t *)(ctx + 0x3f);
    *(uint8_t *)(ctx + 0x43) = *(uint8_t *)(ctx + 0x43);
    sk_retain(ctx);                 /* thunk_FUN_0036b270 */
    sk_retain(ctx);                 /* FUN_0036b270 */
}

/*--------------------------------------------------------------------*/
/* FUN_0033bd6c @ 0x0033bd6c   (est. sk_ctx_merge_rest)
 * Ghidra: void FUN_0033bd6c(void)
 * Merges the trailing record fields from one context into another, retaining
 * new values and releasing replaced ones.
 * Confidence: low.
 * Notes: helpers FUN_0034b264 / FUN_0034f7d8 / FUN_0036b270 / FUN_003a25d4 /
 *   FUN_00354f98 / FUN_0036b118.
 */
void sk_ctx_merge_rest(void)
{
    void *src = (void *)0;          /* unaff_x19 */
    void *dst = (void *)0;          /* unaff_x20 */
    word_t old;

    sk_state_enter2();              /* FUN_0034b264 */
    sk_region_resolve();            /* FUN_0034f7d8 */
    old = *(word_t *)(dst + 0x18);
    *(word_t *)(dst + 0x18) = *(word_t *)(src + 0x18);
    sk_retain(dst);                 /* thunk_FUN_0036b270 */
    sk_obj_meta(old);               /* FUN_003a25d4 */
    sk_ctx_fetch();                 /* FUN_00354f98 */
    old = *(word_t *)(dst + 0x30);
    *(word_t *)(dst + 0x30) = *(word_t *)(src + 0x30);
    sk_retain(dst);                 /* FUN_0036b270 */
    sk_free((void *)old);           /* FUN_0036b118 */
    *(uint8_t *)(dst + 0x38) = *(uint8_t *)(src + 0x38);
    *(uint32_t *)(dst + 0x3c) = *(uint32_t *)(src + 0x3c);
    *(uint32_t *)(dst + 0x3f) = *(uint32_t *)(src + 0x3f);
    *(uint8_t *)(dst + 0x43) = *(uint8_t *)(src + 0x43);
}

/*--------------------------------------------------------------------*/
/* FUN_0033bdf8 @ 0x0033bdf8   (est. sk_ctx_set_rest)
 * Ghidra: void FUN_0033bdf8(void)
 * Sets the trailing record fields (0x10/0x18) from a fetched pair and copies
 * the rest (0x30..0x43), releasing the replaced 0x30 field.
 * Confidence: low.
 * Notes: helpers FUN_003504d0 / FUN_00355118 / FUN_003a25d4 / FUN_00354f98 /
 *   FUN_0036b118.
 */
void sk_ctx_set_rest(void)
{
    void *src = (void *)0;          /* unaff_x19 */
    void *dst = (void *)0;          /* unaff_x20 */
    word_t old;

    sk_state_enter();               /* FUN_003504d0 */
    *(word_t *)(dst + 0x10) = 0;    /* FUN_00355118 -> extraout_x8 */
    *(word_t *)(dst + 0x18) = 0;    /* extraout_x9 */
    sk_obj_meta(0);                 /* FUN_003a25d4 */
    sk_ctx_fetch();                 /* FUN_00354f98 */
    old = *(word_t *)(dst + 0x30);
    *(word_t *)(dst + 0x30) = *(word_t *)(src + 0x30);
    sk_free((void *)old);           /* FUN_0036b118 */
    *(uint8_t *)(dst + 0x38) = *(uint8_t *)(src + 0x38);
    *(uint32_t *)(dst + 0x3c) = *(uint32_t *)(src + 0x3c);
    *(uint32_t *)(dst + 0x3f) = *(uint32_t *)(src + 0x3f);
    *(uint8_t *)(dst + 0x43) = *(uint8_t *)(src + 0x43);
}

/*--------------------------------------------------------------------*/
/* FUN_0033befc @ 0x0033befc   (est. sk_ctx_swap_10)
 * Ghidra: void FUN_0033befc(void)
 * Swaps the 0x10/0x18 fields of the record with the fetched context, retaining.
 * Confidence: low.
 * Notes: helpers FUN_00350e04 / FUN_0036b270.
 */
void sk_ctx_swap_10(void)
{
    void *ctx = (void *)0;          /* unaff_x19 */
    word_t v;

    sk_ctx_fetch_pair();            /* FUN_00350e04 */
    v = *(word_t *)(ctx + 0x18);
    *(word_t *)(ctx + 0x10) = *(word_t *)(ctx + 0x10);
    *(word_t *)(ctx + 0x18) = v;
    sk_retain(ctx);                 /* thunk_FUN_0036b270 */
}

/*--------------------------------------------------------------------*/
/* FUN_0033bf2c @ 0x0033bf2c   (est. sk_ctx_swap_18)
 * Ghidra: long FUN_0033bf2c(long param_1)
 * Swaps the +0x18 field of the record with the fetched context, retaining the
 * new value and releasing metadata on the old; returns the record.
 * Confidence: low.
 * Notes: helpers FUN_0034e86c / FUN_0036b270 / FUN_003a25d4.
 */
long sk_ctx_swap_18(long rec)
{
    word_t old;

    sk_ctx_fetch();                 /* FUN_0034e86c */
    old = *(word_t *)(rec + 0x18);
    *(word_t *)(rec + 0x18) = *(word_t *)(rec + 0x18);   /* extraout_x1 + 0x18 */
    sk_retain((void *)rec);         /* thunk_FUN_0036b270 */
    sk_obj_meta(old);               /* FUN_003a25d4 */
    return rec;
}

/*--------------------------------------------------------------------*/
/* FUN_0033bf6c @ 0x0033bf6c   (est. sk_ctx_fetch_copy_10)
 * Ghidra: void FUN_0033bf6c(void)
 * Fetches a context pair, copies fields 0x10/0x18 into the record, and
 * releases metadata on the previous 0x18 value.
 * Confidence: low.
 * Notes: helpers FUN_00350e04 / FUN_003a25d4.
 */
void sk_ctx_fetch_copy_10(void)
{
    void *ctx = (void *)0;          /* unaff_x19 */
    word_t old;

    cl4_result_t p = sk_ctx_fetch_pair();   /* FUN_00350e04 */
    *(word_t *)(ctx + 0x10) = *(word_t *)(ctx + 0x10);
    *(word_t *)(ctx + 0x18) = *(word_t *)(ctx + 0x18);
    sk_obj_meta(0);                 /* FUN_003a25d4 */
}

/*--------------------------------------------------------------------*/
/* FUN_0033c02c @ 0x0033c02c   (est. sk_ctx_release_fields)
 * Ghidra: void FUN_0033c02c(void)
 * Releases the object fields at +0x38 and +0x50 of the record.
 * Confidence: low.
 * Notes: helpers FUN_00358c20 / FUN_003a25d4 / FUN_0036b118.
 */
void sk_ctx_release_fields(void)
{
    void *ctx = (void *)0;          /* unaff_x19 */

    sk_ctx_fetch();                 /* FUN_00358c20 */
    sk_obj_meta(0);                 /* FUN_003a25d4 */
    sk_free((void *)*(word_t *)(ctx + 0x38));   /* FUN_0036b118 */
    sk_free((void *)*(word_t *)(ctx + 0x50));   /* FUN_0036b118 */
}

/*--------------------------------------------------------------------*/
/* FUN_0033c060 @ 0x0033c060   (est. sk_ctx_copy_wide)
 * Ghidra: void FUN_0033c060(void)
 * Copies the wide trailing record (fields 0x29..0x60) from the fetched context
 * into the local record, retaining the two object fields (+0x38, +0x50).
 * Confidence: low.
 * Notes: helpers FUN_00350e04 / FUN_003577f0 / FUN_0036b270.
 */
void sk_ctx_copy_wide(void)
{
    void *ctx = (void *)0;          /* unaff_x19 */

    sk_ctx_fetch_pair();            /* FUN_00350e04 */
    sk_ctx_fetch();                 /* FUN_003577f0 */
    *(uint16_t *)(ctx + 0x29) = *(uint16_t *)(ctx + 0x29);
    *(uint8_t *)(ctx + 0x30) = *(uint8_t *)(ctx + 0x30);
    *(word_t *)(ctx + 0x38) = *(word_t *)(ctx + 0x38);
    *(uint8_t *)(ctx + 0x40) = *(uint8_t *)(ctx + 0x40);
    *(uint32_t *)(ctx + 0x44) = *(uint32_t *)(ctx + 0x44);
    *(uint32_t *)(ctx + 0x47) = *(uint32_t *)(ctx + 0x47);
    *(uint8_t *)(ctx + 0x4b) = *(uint8_t *)(ctx + 0x4b);
    *(word_t *)(ctx + 0x50) = *(word_t *)(ctx + 0x50);
    *(uint8_t *)(ctx + 0x58) = *(uint8_t *)(ctx + 0x58);
    *(uint32_t *)(ctx + 0x5c) = *(uint32_t *)(ctx + 0x5c);
    *(uint8_t *)(ctx + 0x60) = *(uint8_t *)(ctx + 0x60);
    sk_retain(ctx);                 /* thunk_FUN_0036b270 */
    sk_retain(ctx);                 /* FUN_0036b270 (field +0x38) */
    sk_retain(ctx);                 /* FUN_0036b270 (field +0x50) */
}

/*--------------------------------------------------------------------*/
/* FUN_0033c0fc @ 0x0033c0fc   (est. sk_ctx_merge_wide)
 * Ghidra: void FUN_0033c0fc(void)
 * Merges the wide trailing record fields from one context into another,
 * retaining/ref-releasing the object fields (+0x18, +0x38, +0x50).
 * Confidence: low.
 * Notes: helpers FUN_00350c5c / FUN_0034e86c / FUN_0036b270 / FUN_003a25d4 /
 *   FUN_0036b118.
 */
void sk_ctx_merge_wide(void)
{
    void *src = (void *)0;          /* unaff_x20 */
    void *dst = (void *)0;          /* unaff_x19 */
    word_t old;

    sk_ctx_fetch();                 /* FUN_00350c5c */
    sk_ctx_fetch();                 /* FUN_0034e86c */
    old = *(word_t *)(dst + 0x18);
    *(word_t *)(dst + 0x18) = *(word_t *)(dst + 0x18);
    sk_retain(dst);                 /* thunk_FUN_0036b270 */
    sk_obj_meta(old);               /* FUN_003a25d4 */
    *(word_t *)(dst + 0x20) = *(word_t *)(src + 0x20);
    *(uint8_t *)(dst + 0x28) = *(uint8_t *)(src + 0x28);
    *(uint8_t *)(dst + 0x29) = *(uint8_t *)(src + 0x29);
    *(uint8_t *)(dst + 0x2a) = *(uint8_t *)(src + 0x2a);
    *(uint8_t *)(dst + 0x30) = *(uint8_t *)(src + 0x30);
    old = *(word_t *)(dst + 0x38);
    *(word_t *)(dst + 0x38) = *(word_t *)(src + 0x38);
    sk_retain(dst);                 /* FUN_0036b270 */
    sk_free((void *)old);           /* FUN_0036b118 */
    *(uint8_t *)(dst + 0x40) = *(uint8_t *)(src + 0x40);
    *(uint32_t *)(dst + 0x44) = *(uint32_t *)(src + 0x44);
    *(uint32_t *)(dst + 0x47) = *(uint32_t *)(src + 0x47);
    *(uint8_t *)(dst + 0x4b) = *(uint8_t *)(src + 0x4b);
    old = *(word_t *)(dst + 0x50);
    *(word_t *)(dst + 0x50) = *(word_t *)(src + 0x50);
    sk_retain(dst);                 /* FUN_0036b270 */
    sk_free((void *)old);           /* FUN_0036b118 */
    *(uint8_t *)(dst + 0x58) = *(uint8_t *)(src + 0x58);
    *(uint32_t *)(dst + 0x5c) = *(uint32_t *)(src + 0x5c);
    *(uint8_t *)(dst + 0x60) = *(uint8_t *)(src + 0x60);
}

/*--------------------------------------------------------------------*/
/* FUN_0033c1dc @ 0x0033c1dc   (est. sk_ctx_set_wide)
 * Ghidra: void FUN_0033c1dc(void)
 * Sets the wide trailing record fields from another context, releasing the
 * replaced object fields (+0x38, +0x50).
 * Confidence: low.
 * Notes: helpers FUN_003504d0 / FUN_00355118 / FUN_003a25d4 / FUN_00354f98 /
 *   FUN_0036b118.
 */
void sk_ctx_set_wide(void)
{
    void *src = (void *)0;          /* unaff_x19 */
    void *dst = (void *)0;          /* unaff_x20 */
    word_t old;

    sk_state_enter();               /* FUN_003504d0 */
    *(word_t *)(dst + 0x10) = 0;    /* FUN_00355118 -> extraout_x8 */
    *(word_t *)(dst + 0x18) = 0;    /* extraout_x9 */
    sk_obj_meta(0);                 /* FUN_003a25d4 */
    sk_ctx_fetch();                 /* FUN_00354f98 */
    *(uint8_t *)(dst + 0x29) = *(uint8_t *)(src + 0x29);
    *(uint8_t *)(dst + 0x2a) = *(uint8_t *)(src + 0x2a);
    *(uint8_t *)(dst + 0x30) = *(uint8_t *)(src + 0x30);
    old = *(word_t *)(dst + 0x38);
    *(word_t *)(dst + 0x38) = *(word_t *)(src + 0x38);
    sk_free((void *)old);           /* FUN_0036b118 */
    *(uint8_t *)(dst + 0x40) = *(uint8_t *)(src + 0x40);
    *(uint32_t *)(dst + 0x44) = *(uint32_t *)(src + 0x44);
    *(uint32_t *)(dst + 0x47) = *(uint32_t *)(src + 0x47);
    *(uint8_t *)(dst + 0x4b) = *(uint8_t *)(src + 0x4b);
    old = *(word_t *)(dst + 0x50);
    *(word_t *)(dst + 0x50) = *(word_t *)(src + 0x50);
    sk_free((void *)old);           /* FUN_0036b118 */
    *(uint8_t *)(dst + 0x58) = *(uint8_t *)(src + 0x58);
    *(uint32_t *)(dst + 0x5c) = *(uint32_t *)(src + 0x5c);
    *(uint8_t *)(dst + 0x60) = *(uint8_t *)(src + 0x60);
}

/*--------------------------------------------------------------------*/
/* FUN_0033c5cc @ 0x0033c5cc   (est. sk_cap_free_dispatch)
 * Ghidra: void FUN_0033c5cc(int *param_1)
 * Frees a capability/object record based on its tag byte. Tag > 0x12 falls
 * through; specific tags free the object (+0x0) and/or release metadata.
 * Tags 5-0x10 delegate to FUN_000026e8; tag 0x12 frees +0 and metadata +0x20.
 * Confidence: low.
 * Notes: callees FUN_000026e8 / FUN_0036b118 / FUN_003a25d4.
 */
void sk_cap_free_dispatch(int *rec)
{
    word_t meta;
    uint32_t tag = (uint32_t)*(uint8_t *)(rec + 8);

    if (0x12 < *(uint8_t *)(rec + 8)) {
        tag = *rec + 0x13;
    }
    switch (tag) {
    case 1: case 2: case 3: case 4: case 10: case 0xb:
    case 0xc: case 0xd: case 0xe:
        return;
    case 5: case 6: case 7: case 8: case 9: case 0xf: case 0x10:
        sk_try_acquire(0);          /* FUN_000026e8(rec) */
        return;
    case 0x12:
        sk_free((void *)*(word_t *)rec);        /* FUN_0036b118 */
        meta = *(word_t *)(rec + 4);
        break;
    default:
        meta = *(word_t *)(rec + 2);
        break;
    }
    sk_obj_meta(meta);              /* FUN_003a25d4 */
}

/*--------------------------------------------------------------------*/
/* FUN_0033cf9c @ 0x0033cf9c   (est. sk_ctx_free8)
 * Ghidra: void FUN_0033cf9c(void)
 * Frees the record's +8 object field after the fetch/meta steps.
 * Confidence: low.
 * Notes: helpers FUN_00352b20 / FUN_0036b118.
 */
void sk_ctx_free8(void)
{
    void *ctx = (void *)0;          /* unaff_x19 */

    sk_ctx_fetch();                 /* FUN_00352b20 */
    sk_free(0);                     /* FUN_0036b118 */
    sk_free((void *)*(word_t *)(ctx + 8));      /* FUN_0036b118 */
}

/*--------------------------------------------------------------------*/
/* FUN_0033cfc8 @ 0x0033cfc8   (est. sk_ctx_double_retain)
 * Ghidra: void FUN_0033cfc8(void)
 * Retains the fetched context twice.
 * Confidence: low.
 * Notes: helpers FUN_00358c38 / FUN_0036b270.
 */
void sk_ctx_double_retain(void)
{
    sk_ctx_fetch();                 /* FUN_00358c38 */
    sk_retain(0);                   /* FUN_0036b270 */
    sk_retain(0);                   /* FUN_0036b270 */
}

/*--------------------------------------------------------------------*/
/* FUN_0033cff8 @ 0x0033cff8   (est. sk_ctx_swap8)
 * Ghidra: void FUN_0033cff8(void)
 * Swaps the +8 object field between two contexts, retaining new / freeing old.
 * Confidence: low.
 * Notes: helpers FUN_0034b044 / FUN_0036b270 / FUN_0036b118.
 */
void sk_ctx_swap8(void)
{
    void *src = (void *)0;          /* unaff_x19 */
    void *dst = (void *)0;          /* unaff_x20 */
    word_t old;

    sk_ctx_fetch();                 /* FUN_0034b044 */
    sk_retain(0);                   /* FUN_0036b270 */
    sk_free(0);                     /* FUN_0036b118 */
    old = *(word_t *)(dst + 8);
    *(word_t *)(dst + 8) = *(word_t *)(src + 8);
    sk_retain(dst);                 /* FUN_0036b270 */
    sk_free((void *)old);           /* FUN_0036b118 */
}

/*--------------------------------------------------------------------*/
/* FUN_0033d060 @ 0x0033d060   (est. sk_panic_record_ctx)
 * Ghidra: void FUN_0033d060(void)
 * Enters the kernel, releases the lock; when the returned count is < 0x40,
 * formats two panic-record buffers (format FUN_003718ec with the strings at
 * 0x67a6f0 / DAT_004effd8) then runs the housekeeping sequence.
 * Confidence: low.
 * Notes: helpers FUN_0034c7c4 / FUN_00377dcc / FUN_003718ec / FUN_0034d1c0 /
 *   FUN_00368980 / FUN_00019858; string refs 0x67a6f0, DAT_004effd8.
 */
void sk_panic_record_ctx(void)
{
    void *ctx;                      /* auVar2._0_8_ */
    word_t n;
    char buf1[32], buf2[32];        /* auStack_90 / auStack_70 */

    sk_cpu_enter_kernel();          /* FUN_0034c7c4 */
    cl4_result_t r = { 0, 0 };      /* FUN_00377dcc */
    n = r.hi;
    ctx = (void *)r.lo;
    if (n < 0x40) {
        long base = *(long *)((char *)ctx - 8);
        sk_ctx_fetch();             /* FUN_003718ec(buf1, 0x67a6f0, base+0x40, &DAT_004effd8) */
        sk_ctx_fetch();             /* FUN_003718ec(buf2, 0x67a6f0, base+0x40, &DAT_004effd8) */
        sk_ctx_fetch();             /* FUN_0034d1c0 */
        sk_ctx_fetch();             /* FUN_00368980 */
        sk_try_acquire(0);          /* FUN_00019858 */
    }
}

/*--------------------------------------------------------------------*/
/* FUN_0033d118 @ 0x0033d118   (est. sk_encode_flag)
 * Ghidra: void FUN_0033d118(void)
 * Encodes a 1-byte flag into the output buffer at x19: computes an aligned
 * offset, validates it (offset+10 < 0x19 and count < 8), reads a size byte,
 * writes a boolean flag, and issues a metadata op. On invalid offset frees.
 * Confidence: low (register aliasing).
 * Notes: callees FUN_00349d3c / FUN_0006b6f4 / FUN_0034c764 / FUN_0034e974 /
 *   FUN_0036b270.
 */
void sk_encode_flag(void)
{
    void *buf = (void *)0;          /* unaff_x19 */
    void *ctx;                      /* extraout_x16 */
    void *ctx2;                     /* extraout_x9 */
    word_t tag;                     /* +0x50 byte */
    long off;

    sk_ctx_fetch();                 /* FUN_00349d3c */
    tag = (word_t)*(uint32_t *)(ctx + 0x50) & 0xff;
    off = *(long *)(ctx2 + 0x40) + 7;
    off = (off + (tag + 8 & ~tag)) & ~0x7ull;
    if ((tag < 8 && (*(uint32_t *)(ctx + 0x50) & 0x100000) == 0) && off + 10 < 0x19) {
        uint8_t size_byte = *(uint8_t *)((char *)0 + off);
        uint32_t val = size_byte;
        if (1 < size_byte) {
            if ((off & ~0x7ull) == 0) {
                val = (size_byte << 8 | (uint8_t)*(uint8_t *)0) - 0x1fe;
            } else {
                val = *(uint32_t *)0 + 2;
            }
        }
        *(word_t *)buf = *(word_t *)0;
        sk_try_acquire(0);          /* FUN_0006b6f4 */
        (*(void (**)(void))ctx2)(); /* extraout_x9_00 */
        sk_ctx_fetch();             /* FUN_0034c764 */
        *(uint8_t *)((char *)buf + off) = (val == 1);
    } else {
        sk_ctx_fetch();             /* FUN_0034e974 */
        sk_retain(0);               /* FUN_0036b270 */
    }
}

/*--------------------------------------------------------------------*/
/* FUN_0033d23c @ 0x0033d23c   (est. sk_encode_flag2)
 * Ghidra: long FUN_0033d23c(long param_1)
 * Encodes a boolean flag (value==1) into the byte at param_1+off after reading
 * a 1-2 byte size field; returns param_1.
 * Confidence: low.
 * Notes: callees FUN_00355288 / FUN_0035772c / FUN_00355e08 / FUN_0006b6f4 /
 *   FUN_0034c764.
 */
long sk_encode_flag2(long rec)
{
    void *ctx;                      /* extraout_x9 */
    long off = 0;                   /* unaff_x22 */
    long base = 0;                  /* unaff_x23 */
    uint32_t val;

    sk_ctx_fetch();                 /* FUN_00355288 */
    sk_ctx_fetch();                 /* FUN_0035772c */
    val = 0;                        /* extraout_w11 */
    if (/* CY flag */ true) {
        if ((off & ~0x7ull) == 0) {
            val = (*(uint8_t *)0 | 0 << 8) - 0x1fe;
        } else {
            val = *(int *)0 + 2;
        }
    }
    sk_ctx_fetch();                 /* FUN_00355e08 */
    sk_try_acquire(0);              /* FUN_0006b6f4 */
    (*(void (**)(void))ctx)();      /* extraout_x9 */
    sk_ctx_fetch();                 /* FUN_0034c764 */
    *(bool *)(rec + off) = (val == 1);
    return rec;
}

/*--------------------------------------------------------------------*/
/* FUN_0033d2fc @ 0x0033d2fc   (est. sk_syscall_flag_path)
 * Ghidra: void FUN_0033d2fc(undefined8, undefined8, long param_3)
 * Syscall handler: when the CPU base is nonzero, resolves the object path
 * (sk_obj_path), dispatches through the context method table at +8, and
 * encodes a result flag; wraps with per-CPU enter/exit (FUN_0008e518/e500).
 * Confidence: low.
 * Notes: callees FUN_0008e518 / FUN_00354ccc / FUN_00349b00 / FUN_003503e0 /
 *   FUN_00358b30 / FUN_0034c694 / FUN_0034c764 / FUN_0008e500.
 */
void sk_syscall_flag_path(unsigned long p1, unsigned long p2, unsigned long p3)
{
    void *ctxA, *ctxB;              /* extraout_x16 / extraout_x16_00 */
    word_t tag;
    long base;                      /* extraout_x8 + 0x40 */
    word_t val;
    long off;

    sk_cpu_enter();                 /* FUN_0008e518 */
    sk_ctx_fetch();                 /* FUN_00354ccc */
    if (/* ZR flag cleared */ true) {
        val = *(word_t *)(p3 + 0x10);
        sk_obj_path(0, 0);          /* FUN_00349b00 */
        tag = (word_t)*(uint8_t *)(ctxA + 0x50);
        base = *(long *)(ctxB + 0x40) + 7;
        off = (base + (tag + 8 & ~tag) & ~0x7ull) + 9;
        tag = tag + 8 + 0 & ~tag;
        sk_ctx_fetch();             /* FUN_003503e0 */
        (*(void (**)(word_t, word_t))(ctxA + 8))(tag, val);
        uint8_t size_byte = *(uint8_t *)((char *)0 + off);
        uint32_t v = size_byte;
        if (1 < size_byte) {
            if ((off & ~0x7ull) == 0) {
                v = (size_byte << 8 | (uint8_t)*(uint8_t *)0) - 0x1fe;
            } else {
                v = *(uint32_t *)0 + 2;
            }
        }
        sk_ctx_fetch();             /* FUN_00358b30 */
        sk_ctx_fetch();             /* FUN_0034c694 */
        (*(void (**)(void))ctxB)(); /* extraout_x8_00 */
        sk_ctx_fetch();             /* FUN_0034c764 */
        *(bool *)(0 + off) = (v == 1);
    }
    sk_cpu_exit(0);                 /* FUN_0008e500 */
}

/*--------------------------------------------------------------------*/
/* FUN_0033d404 @ 0x0033d404   (est. sk_encode_flag3)
 * Ghidra: long FUN_0033d404(long param_1)
 * Identical template to sk_encode_flag2; encodes a boolean flag into byte
 * param_1+off after reading a 1-2 byte size field.
 * Confidence: low.
 */
long sk_encode_flag3(long rec)
{
    void *ctx;                      /* extraout_x9 */
    long off = 0;                   /* unaff_x22 */
    long base = 0;                  /* unaff_x23 */
    uint32_t val;

    sk_ctx_fetch();                 /* FUN_00355288 */
    sk_ctx_fetch();                 /* FUN_0035772c */
    val = 0;                        /* extraout_w11 */
    if (/* CY flag */ true) {
        if ((off & ~0x7ull) == 0) {
            val = (*(uint8_t *)0 | 0 << 8) - 0x1fe;
        } else {
            val = *(int *)0 + 2;
        }
    }
    sk_ctx_fetch();                 /* FUN_00355e08 */
    sk_try_acquire(0);              /* FUN_0006b6f4 */
    (*(void (**)(void))ctx)();      /* extraout_x9 */
    sk_ctx_fetch();                 /* FUN_0034c764 */
    *(bool *)(rec + off) = (val == 1);
    return rec;
}

/*--------------------------------------------------------------------*/
/* FUN_0033d948 @ 0x0033d948   (est. sk_encode_varlen_field)
 * Ghidra: void FUN_0033d948(int *param_1)
 * Encodes a variable-length field value into the buffer at param_1: writes a
 * length tag byte, then a 1-4 byte little-endian payload for values >= 2.
 * Confidence: low.
 * Notes: callees FUN_0034e34c / FUN_0009461c / FUN_00114330.
 */
void sk_encode_varlen_field(int *buf)
{
    void *ctx;                      /* extraout_x16 */
    void *ctx2;                     /* extraout_x8 */
    word_t tag;                     /* +0x50 byte */
    long off;
    uint32_t val;

    sk_ctx_fetch();                 /* FUN_0034e34c */
    tag = (word_t)*(uint8_t *)(ctx + 0x50);
    off = *(long *)(ctx2 + 0x40) + 7 +
          ((tag + 8) & ~tag) & ~0x7ull;
    val = 0;                        /* extraout_w1 */
    if (val < 2) {
        *(char *)((char *)buf + off + 9) = (char)val;
    } else {
        long pos = off + 9;
        int32_t i = val - 2;
        uint32_t p = (uint32_t)pos;
        char tag_c = '\x02';
        if (p < 4) {
            tag_c = (char)((uint32_t)i >> 8) + '\x02';
        }
        *(char *)((char *)buf + pos) = tag_c;
        sk_ctx_fetch();             /* FUN_0009461c */
        sk_obj_meta(0);             /* FUN_00114330 */
        if (p < 4) {
            *(char *)buf = (char)i;
        } else {
            *buf = i;
        }
    }
}

/*--------------------------------------------------------------------*/
/* FUN_0033da14 @ 0x0033da14   (est. sk_panic_ctl_a)
 * Ghidra: void FUN_0033da14(void)
 * Kernel-enter, lock-release, then if count < 0x40 runs a panic/housekeeping
 * sequence (FUN_00353424 + FUN_0034d034 + FUN_003728b8 + FUN_00019858).
 * Confidence: low.
 * Notes: helpers FUN_0034c7c4 / FUN_00377dcc / FUN_00353424 / FUN_0034d034 /
 *   FUN_003728b8 / FUN_00019858.
 */
void sk_panic_ctl_a(void)
{
    void *ctx;                      /* auVar1._0_8_ */
    word_t n;

    sk_cpu_enter_kernel();          /* FUN_0034c7c4 */
    cl4_result_t r = { 0, 0 };      /* FUN_00377dcc */
    n = r.hi; ctx = (void *)r.lo;
    if (n < 0x40) {
        sk_ctx_fetch();             /* FUN_00353424(*(ctx-8) + 0x40) */
        sk_ctx_fetch();             /* FUN_0034d034 */
        sk_syscall_op(0, 0, 0);     /* FUN_003728b8 */
        sk_try_acquire(0);          /* FUN_00019858 */
    }
}

/*--------------------------------------------------------------------*/
/* FUN_0033da78 @ 0x0033da78   (est. sk_panic_ctl_b)
 * Ghidra: void FUN_0033da78(void)
 * Same template as sk_panic_ctl_a but the lock-release helper is FUN_00310d68.
 * Confidence: low.
 */
void sk_panic_ctl_b(void)
{
    void *ctx;
    word_t n;

    sk_cpu_enter_kernel();          /* FUN_0034c7c4 */
    cl4_result_t r = { 0, 0 };      /* FUN_00310d68 */
    n = r.hi; ctx = (void *)r.lo;
    if (n < 0x40) {
        sk_ctx_fetch();             /* FUN_00353424(*(ctx-8) + 0x40) */
        sk_ctx_fetch();             /* FUN_0034d034 */
        sk_syscall_op(0, 0, 0);     /* FUN_003728b8 */
        sk_try_acquire(0);          /* FUN_00019858 */
    }
}

/*--------------------------------------------------------------------*/
/* FUN_0033dadc @ 0x0033dadc   (est. sk_queue_op_path)
 * Ghidra: undefined8 * FUN_0033dadc(void)
 * Queues/validates an object path operation. On the valid path (queue op
 * FUN_000839f8 succeeds) allocates a record via FUN_00117cc4; on the failure
 * path copies a record and retains.
 * Confidence: low.
 * Notes: callees FUN_00351a38 / FUN_00349b00 / FUN_003594a8 / FUN_0035163c /
 *   FUN_000839f8 / FUN_003507e0 / FUN_00117cc4 / FUN_0034bf1c / FUN_0034b744 /
 *   FUN_000839d8 / FUN_00358bb4 / FUN_0036b270.
 */
undefined8 *sk_queue_op_path(void)
{
    void *ctx;                      /* extraout_x16 */
    void *ctx2;                     /* extraout_x8 */
    undefined8 *dst = 0;            /* unaff_x19 */
    undefined8 *src = 0;            /* unaff_x21 */
    word_t n;
    bool is_zero;

    sk_ctx_fetch();                 /* FUN_00351a38 */
    sk_obj_path(0, 0);              /* FUN_00349b00 */
    n = *(word_t *)(ctx2 + 0x40);
    is_zero = *(int *)(ctx + 0x54) == 0;
    if (is_zero) {
        n = n + 1;
    }
    sk_ctx_fetch();                 /* FUN_003594a8 */
    if ((is_zero && 0 == 0) && n < 0x19) {
        sk_ctx_fetch();             /* FUN_0035163c */
        if (sk_queue_complete(0, 0)) {      /* FUN_000839f8 */
            cl4_result_t p = sk_obj_resolve(0, 0);  /* FUN_003507e0 */
            return (undefined8 *)sk_try_acquire(0); /* FUN_00117cc4(p.lo, p.hi, n) */
        }
        sk_ctx_fetch();             /* FUN_0034bf1c(*(ctx+0x10)) */
        (*(void (**)(void))ctx)();  /* extraout_x8_01 */
        sk_ctx_fetch();             /* FUN_0034b744 */
        sk_obj_complete();          /* FUN_000839d8 */
    } else {
        *dst = *src;
        dst = (undefined8 *)(0 + 0);        /* FUN_00358bb4 */
        sk_retain(dst);             /* FUN_0036b270 */
    }
    return dst;
}

/*--------------------------------------------------------------------*/
/* FUN_0033dbb8 @ 0x0033dbb8   (est. sk_queue_op_dispatch)
 * Ghidra: void FUN_0033dbb8(undefined8 param_1, long param_2)
 * Dispatches a queue operation through the context method table at +8 after a
 * queue check; the indirect jump table at 0x0033dc14 prevents full recovery.
 * Confidence: low.
 * Notes: callees FUN_00351390 / FUN_000839f8 / FUN_00350bcc; jumptable warning.
 */
void sk_queue_op_dispatch(unsigned long p1, long p2)
{
    void *ctx;                      /* extraout_x16 */
    word_t val = *(word_t *)(p2 + 0x10);

    sk_ctx_fetch();                 /* FUN_00351390 */
    if (sk_queue_complete(0, 0)) {  /* FUN_000839f8 */
        return;
    }
    sk_ctx_fetch();                 /* FUN_00350bcc */
    /* WARNING: jumptable at 0x0033dc14 (too many branches) */
    (*(void (**)(unsigned long, word_t))(ctx + 8))(p1, val);
}

/*--------------------------------------------------------------------*/
/* FUN_0033dcb0 @ 0x0033dcb0   (est. sk_queue_dispatch_dual)
 * Ghidra: void FUN_0033dcb0(void)
 * Dual-path queue dispatch: branch on a state flag (unaff_w23) and a validity
 * result, dispatching through one of the context method slots (+0x18/+8 or
 * +0x10), then completing with FUN_000839d8 / FUN_00117cc4.
 * Confidence: low.
 * Notes: callees FUN_00350c5c / FUN_0034e178 / FUN_0034bfb4 / FUN_003507e0 /
 *   FUN_00355e44 / FUN_00354070 / FUN_0034aed0 / FUN_000839d8 / FUN_0009461c /
 *   FUN_00117cc4.
 */
void sk_queue_dispatch_dual(void)
{
    void *ctx;                      /* extraout_x16 */
    long n;
    int ok;
    bool state;                     /* unaff_w23 */

    sk_ctx_fetch();                 /* FUN_00350c5c */
    ok = 0;                         /* FUN_0034e178 */
    if (!state) {
        if (ok == 0) {
            sk_ctx_fetch();         /* FUN_0034bfb4(*(ctx+0x18)) */
            (*(void (**)(void))ctx)();  /* extraout_x8_01 */
            return;
        }
        sk_ctx_fetch();             /* FUN_003507e0(*(ctx+8)) */
        (*(void (**)(void))ctx)();  /* extraout_x8 */
        sk_ctx_fetch_pair();        /* FUN_00355e44 */
        n = 0; ok = 0;
    } else {
        if (ok == 0) {
            sk_ctx_fetch();         /* FUN_0034bfb4(*(ctx+0x10)) */
            (*(void (**)(void))ctx)();  /* extraout_x8_00 */
            sk_ctx_fetch();         /* FUN_0034aed0 */
            sk_obj_complete();      /* FUN_000839d8 */
            return;
        }
        sk_ctx_fetch_pair();        /* FUN_00354070 */
        n = 0; ok = 0;
    }
    if (ok == 0) {
        n = n + 1;
    }
    sk_ctx_fetch();                 /* FUN_0009461c */
    sk_try_acquire(0);              /* FUN_00117cc4 */
}

/*--------------------------------------------------------------------*/
/* FUN_0033dd7c @ 0x0033dd7c   (est. sk_queue_op_path2)
 * Ghidra: void FUN_0033dd7c(undefined8, undefined8, long param_3)
 * Queue-path syscall: validates the object at param_3+0x10, and on the success
 * path dispatches the method at record+0x20; else allocates via FUN_00117cc4.
 * Confidence: low.
 * Notes: callees FUN_00351a38 / FUN_0035163c / FUN_000839f8 / FUN_003507e0 /
 *   FUN_00117cc4 / FUN_0034b744 / FUN_000839d8.
 */
void sk_queue_op_path2(unsigned long p1, unsigned long p2, unsigned long p3)
{
    void *rec;                      /* lVar2 */
    long n;
    cl4_result_t r;

    sk_ctx_fetch();                 /* FUN_00351a38 */
    rec = (void *)(p3 + 0x10);
    sk_ctx_fetch();                 /* FUN_0035163c */
    r = sk_obj_resolve(0, 0);       /* FUN_000839f8 */
    rec = (void *)((char *)rec - 8);
    if (r.lo != 0) {
        n = *(long *)((char *)rec + 0x40);
        if (*(int *)((char *)rec + 0x54) == 0) {
            n = n + 1;
        }
        sk_ctx_fetch();             /* FUN_003507e0 */
        sk_try_acquire(0);          /* FUN_00117cc4 */
        return;
    }
    (*(void (**)(void))((char *)rec + 0x20))();
    sk_ctx_fetch();                 /* FUN_0034b744 */
    sk_obj_complete();              /* FUN_000839d8 */
}

/*--------------------------------------------------------------------*/
/* FUN_0033de14 @ 0x0033de14   (est. sk_queue_dispatch_dual2)
 * Ghidra: void FUN_0033de14(void)
 * Same template as sk_queue_dispatch_dual but the first-path method slot is
 * +0x28 and the second-path slot is +0x20.
 * Confidence: low.
 */
void sk_queue_dispatch_dual2(void)
{
    void *ctx;                      /* extraout_x16 */
    long n;
    int ok;
    bool state;                     /* unaff_w23 */

    sk_ctx_fetch();                 /* FUN_00350c5c */
    ok = 0;                         /* FUN_0034e178 */
    if (!state) {
        if (ok == 0) {
            sk_ctx_fetch();         /* FUN_0034bfb4(*(ctx+0x28)) */
            (*(void (**)(void))ctx)();  /* extraout_x8_01 */
            return;
        }
        sk_ctx_fetch();             /* FUN_003507e0(*(ctx+8)) */
        (*(void (**)(void))ctx)();  /* extraout_x8 */
        sk_ctx_fetch_pair();        /* FUN_00355e44 */
        n = 0; ok = 0;
    } else {
        if (ok == 0) {
            sk_ctx_fetch();         /* FUN_0034bfb4(*(ctx+0x20)) */
            (*(void (**)(void))ctx)();  /* extraout_x8_00 */
            sk_ctx_fetch();         /* FUN_0034aed0 */
            sk_obj_complete();      /* FUN_000839d8 */
            return;
        }
        sk_ctx_fetch_pair();        /* FUN_00354070 */
        n = 0; ok = 0;
    }
    if (ok == 0) {
        n = n + 1;
    }
    sk_ctx_fetch();                 /* FUN_0009461c */
    sk_try_acquire(0);              /* FUN_00117cc4 */
}

/*--------------------------------------------------------------------*/
/* FUN_0033dfc8 @ 0x0033dfc8   (est. sk_queue_op_tail_a)
 * Ghidra: void FUN_0033dfc8(void)
 * Runs a queue completion then a tail helper.
 * Confidence: low.
 * Notes: FUN_000839f8 / FUN_003585dc.
 */
void sk_queue_op_tail_a(void)
{
    sk_queue_complete(0, 0);        /* FUN_000839f8 */
    sk_ctx_fetch();                 /* FUN_003585dc */
}

/*--------------------------------------------------------------------*/
/* FUN_0033dfcc @ 0x0033dfcc   (est. sk_queue_op_tail_b)
 * Ghidra: void FUN_0033dfcc(void)
 * Identical template to sk_queue_op_tail_a.
 * Confidence: low.
 */
void sk_queue_op_tail_b(void)
{
    sk_queue_complete(0, 0);        /* FUN_000839f8 */
    sk_ctx_fetch();                 /* FUN_003585dc */
}

/*--------------------------------------------------------------------*/
/* FUN_0033e284 @ 0x0033e284   (est. sk_cap_copy)
 * Ghidra: ulong * FUN_0033e284(ulong *param_1, ulong *param_2)
 * Copies a capability record param_2 -> param_1. For small (size<0x1000) and
 * non-invalid (hi != 0xffffffff) caps calls FUN_00355e98; else copies both
 * words and retains.
 * Confidence: low.
 * Notes: callees FUN_00355e98 / FUN_0036b270.
 */
ulong *sk_cap_copy(ulong *dst, ulong *src)
{
    ulong v = *src;

    if (v < 0x1000 && (v & 0xffffffff) != 0xffffffff) {
        sk_ctx_fetch();             /* FUN_00355e98 */
    } else {
        dst[1] = src[1];
        *dst = v;
        sk_retain(dst);             /* FUN_0036b270 */
    }
    return dst;
}

/*--------------------------------------------------------------------*/
/* FUN_0033e2d4 @ 0x0033e2d4   (est. sk_cap_copy_cond)
 * Ghidra: void FUN_0033e2d4(void)
 * Conditionally copies a capability record with retain/free based on the size
 * and validity of the fetched source and a ZR flag.
 * Confidence: low.
 * Notes: callees FUN_00350c5c / FUN_00358504 / FUN_0036b270 / FUN_0036b118 /
 *   FUN_00353dc4.
 */
void sk_cap_copy_cond(void)
{
    undefined8 *dst = 0;            /* unaff_x19 */
    void *src = 0;                  /* unaff_x20 */
    word_t size;                    /* extraout_x10 */
    long inv;                       /* extraout_x11 */
    word_t v;
    bool zf;                        /* in_ZR */

    sk_ctx_fetch();                 /* FUN_00350c5c */
    sk_ctx_fetch();                 /* FUN_00358504 */
    if (size < 0x1000 && inv != 0xffffffff) {
        if (zf) {
            v = *(word_t *)((char *)src + 8);
            *dst = 0;               /* extraout_x8 */
            dst[1] = v;
            sk_retain(dst);         /* FUN_0036b270 */
            return;
        }
    } else {
        if (zf) {
            v = *(word_t *)((char *)src + 8);
            word_t old = dst[1];
            *dst = 0;               /* extraout_x8 */
            dst[1] = v;
            sk_retain(dst);         /* FUN_0036b270 */
            sk_free((void *)old);   /* FUN_0036b118 */
            return;
        }
        sk_free((void *)dst[1]);    /* FUN_0036b118 */
    }
    sk_ctx_fetch();                 /* FUN_00353dc4 */
}

/*--------------------------------------------------------------------*/
/* FUN_0033e350 @ 0x0033e350   (est. sk_cap_copy_cond2)
 * Ghidra: void FUN_0033e350(void)
 * Same template as sk_cap_copy_cond.
 * Confidence: low.
 */
void sk_cap_copy_cond2(void)
{
    undefined8 *dst = 0;            /* unaff_x19 */
    void *src = 0;                  /* unaff_x20 */
    word_t size;                    /* extraout_x10 */
    long inv;                       /* extraout_x11 */
    word_t v;
    bool zf;                        /* in_ZR */

    sk_ctx_fetch();                 /* FUN_00350c5c */
    sk_ctx_fetch();                 /* FUN_00358504 */
    if (size < 0x1000 && inv != 0xffffffff) {
        if (zf) {
            v = *(word_t *)((char *)src + 8);
            *dst = 0;               /* extraout_x8 */
            dst[1] = v;
            sk_retain(dst);         /* FUN_0036b270 */
            return;
        }
    } else {
        if (zf) {
            v = *(word_t *)((char *)src + 8);
            word_t old = dst[1];
            *dst = 0;               /* extraout_x8 */
            dst[1] = v;
            sk_retain(dst);         /* FUN_0036b270 */
            sk_free((void *)old);   /* FUN_0036b118 */
            return;
        }
        sk_free((void *)dst[1]);    /* FUN_0036b118 */
    }
    sk_ctx_fetch();                 /* FUN_00353dc4 */
}

/*--------------------------------------------------------------------*/
/* FUN_0033e448 @ 0x0033e448   (est. sk_cap_size)
 * Ghidra: int FUN_0033e448(ulong *param_1)
 * Returns the capability size+1 for small caps (word[0] < 0x1000), else 0.
 * Confidence: medium (self-contained).
 */
int sk_cap_size(ulong *cap)
{
    int n = 0;
    if (*cap < 0x1000) {
        n = (int)*cap + 1;
    }
    return n;
}

/*--------------------------------------------------------------------*/
/* FUN_0033e668 @ 0x0033e668   (est. sk_cap_retain_tag)
 * Ghidra: void FUN_0033e668(undefined8, ulong param_2, undefined8, undefined8 param_4)
 * Retains the record when the high tag bits (param_2 >> 0x3e) are clear.
 * Confidence: medium (self-contained).
 * Notes: thunk_FUN_0036b270.
 */
void sk_cap_retain_tag(unsigned long p1, ulong tag, unsigned long p3,
                       unsigned long p4)
{
    if (tag >> 0x3e == 0) {
        sk_retain((void *)p4);      /* thunk_FUN_0036b270 */
    }
}

/*--------------------------------------------------------------------*/
/* FUN_0033e68c @ 0x0033e68c   (est. sk_cap_meta_tag)
 * Ghidra: void FUN_0033e68c(undefined8, ulong param_2, undefined8, undefined8 param_4)
 * Releases metadata on the record when the high tag bits are clear.
 * Confidence: medium.
 * Notes: FUN_003a25d4.
 */
void sk_cap_meta_tag(unsigned long p1, ulong tag, unsigned long p3,
                     unsigned long p4)
{
    if (tag >> 0x3e == 0) {
        sk_obj_meta(p4);            /* FUN_003a25d4 */
    }
}

/*--------------------------------------------------------------------*/
/* FUN_0033e6a0 @ 0x0033e6a0   (est. sk_cap_copy4)
 * Ghidra: undefined8 * FUN_0033e6a0(undefined8 *param_1, undefined8 *param_2)
 * Copies a 4-word capability record param_2 -> param_1, retaining via tag.
 * Confidence: medium.
 * Notes: FUN_0034c444 / FUN_0033e668 (local).
 */
undefined8 *sk_cap_copy4(undefined8 *dst, undefined8 *src)
{
    undefined8 v0 = src[0], v1 = src[1], v2 = src[2], v3 = src[3];

    sk_ctx_fetch();                 /* FUN_0034c444(v0) */
    sk_cap_retain_tag(0, (ulong)v0, 0, 0);
    dst[0] = v0; dst[1] = v1; dst[2] = v2; dst[3] = v3;
    return dst;
}

/*--------------------------------------------------------------------*/
/* FUN_0033e6f0 @ 0x0033e6f0   (est. sk_cap_copy4_meta)
 * Ghidra: undefined8 * FUN_0033e6f0(undefined8 *param_1, undefined8 *param_2)
 * Copies a 4-word capability record, retaining via tag and releasing metadata
 * via tag; returns dst.
 * Confidence: medium.
 * Notes: FUN_0034c444 / FUN_00357228 / local FUN_0033e668 / FUN_0033e68c.
 */
undefined8 *sk_cap_copy4_meta(undefined8 *dst, undefined8 *src)
{
    undefined8 v0 = src[0], v1 = src[1], v2 = src[2], v3 = src[3];

    sk_ctx_fetch();                 /* FUN_0034c444(v0) */
    sk_cap_retain_tag(0, (ulong)v0, 0, 0);
    sk_ctx_fetch();                 /* FUN_00357228 */
    dst[0] = v0; dst[1] = v1; dst[2] = v2; dst[3] = v3;
    sk_cap_meta_tag(0, (ulong)v0, 0, 0);
    return dst;
}

/*--------------------------------------------------------------------*/
/* FUN_0033e748 @ 0x0033e748   (est. sk_cap_swap4)
 * Ghidra: void FUN_0033e748(void)
 * Swaps the 4-word capability record between the local context (unaff_x19)
 * and a fetched record, releasing metadata on the old value.
 * Confidence: low.
 * Notes: FUN_00352b20 / local FUN_0033e68c.
 */
void sk_cap_swap4(void)
{
    undefined8 *dst = 0;            /* unaff_x19 */

    cl4_result_t p = sk_ctx_fetch_pair();   /* FUN_00352b20 */
    undefined8 *src = (undefined8 *)p.hi;
    undefined8 old1 = dst[1], old2 = dst[2], old3 = dst[3];
    undefined8 n0 = src[0], n3 = src[3], n2 = src[2];
    dst[1] = src[1];
    dst[0] = n0; dst[3] = n3; dst[2] = n2;
    sk_cap_meta_tag(p.lo, (ulong)old1, (ulong)old2, (ulong)old3);
}

/*--------------------------------------------------------------------*/
/* FUN_0033e850 @ 0x0033e850   (est. sk_cap_free2)
 * Ghidra: void FUN_0033e850(long param_1)
 * Frees the +8 metadata and +0x10 object of a capability record.
 * Confidence: medium.
 * Notes: FUN_003a25d4 / FUN_0036b118.
 */
void sk_cap_free2(long rec)
{
    sk_obj_meta(*(word_t *)(rec + 8));      /* FUN_003a25d4 */
    sk_free((void *)*(word_t *)(rec + 0x10));       /* FUN_0036b118 */
}

/*--------------------------------------------------------------------*/
/* FUN_0033e880 @ 0x0033e880   (est. sk_cap_copy2)
 * Ghidra: void FUN_0033e880(void)
 * Copies the 2-word capability record from a fetched context, retaining both
 * words.
 * Confidence: low.
 * Notes: FUN_0034f2f4 / FUN_0036b270.
 */
void sk_cap_copy2(void)
{
    cl4_result_t p = sk_ctx_fetch_pair();   /* FUN_0034f2f4 */
    void *src = (void *)p.hi;
    word_t v0 = *(word_t *)((char *)src + 0x10);
    word_t v1 = *(word_t *)((char *)src + 8);
    *(word_t *)(p.lo + 0x10) = *(word_t *)((char *)src + 0x10);
    *(word_t *)(p.lo + 8) = v1;
    sk_retain((void *)v1);          /* thunk_FUN_0036b270 */
    sk_retain((void *)v0);          /* FUN_0036b270 */
}

/*--------------------------------------------------------------------*/
/* FUN_0033e8c0 @ 0x0033e8c0   (est. sk_cap_swap10)
 * Ghidra: void FUN_0033e8c0(void)
 * Swaps the +0x10 field between contexts, retaining new / freeing old.
 * Confidence: low.
 * Notes: FUN_0034b264 / FUN_00352028 / FUN_0036b270 / FUN_003a25d4 / FUN_0036b118.
 */
void sk_cap_swap10(void)
{
    void *src = 0;                  /* unaff_x19 */
    void *dst = 0;                  /* unaff_x20 */
    word_t old;

    sk_state_enter2();              /* FUN_0034b264 */
    sk_state_enter2();              /* FUN_00352028 */
    sk_retain(0);                   /* thunk_FUN_0036b270 */
    sk_obj_meta(0);                 /* FUN_003a25d4 */
    old = *(word_t *)((char *)dst + 0x10);
    *(word_t *)((char *)dst + 0x10) = *(word_t *)((char *)src + 0x10);
    sk_retain(dst);                 /* FUN_0036b270 */
    sk_free((void *)old);           /* FUN_0036b118 */
}

/*--------------------------------------------------------------------*/
/* FUN_0033e914 @ 0x0033e914   (est. sk_cap_merge8_10)
 * Ghidra: void FUN_0033e914(void)
 * Merges the +8 and +0x10 fields from src into dst, releasing the old +0x10.
 * Confidence: low.
 * Notes: FUN_0034b264 / FUN_003a25d4 / FUN_0036b118.
 */
void sk_cap_merge8_10(void)
{
    void *src = 0;                  /* unaff_x19 */
    void *dst = 0;                  /* unaff_x20 */
    word_t old;

    sk_state_enter2();              /* FUN_0034b264 */
    sk_obj_meta(*(word_t *)(0 + 8));        /* FUN_003a25d4 */
    old = *(word_t *)((char *)dst + 0x10);
    *(word_t *)((char *)dst + 0x10) = *(word_t *)((char *)src + 0x10);
    *(word_t *)((char *)dst + 8) = *(word_t *)((char *)src + 8);
    sk_free((void *)old);           /* FUN_0036b118 */
}

/*--------------------------------------------------------------------*/
/* FUN_0033e9a0 @ 0x0033e9a0   (est. sk_cap_copy_18)
 * Ghidra: void FUN_0033e9a0(void)
 * Copies the +0x18 field from the fetched context, retaining.
 * Confidence: low.
 * Notes: FUN_00353900 / FUN_0036b270.
 */
void sk_cap_copy_18(void)
{
    void *ctx = 0;                  /* unaff_x19 */

    sk_ctx_fetch();                 /* FUN_00353900 */
    *(word_t *)((char *)ctx + 0x18) = *(word_t *)((char *)ctx + 0x18);
    sk_retain(ctx);                 /* FUN_0036b270 */
}

/*--------------------------------------------------------------------*/
/* FUN_0033e9d0 @ 0x0033e9d0   (est. sk_cap_ctl_seq)
 * Ghidra: void FUN_0033e9d0(void)
 * Runs a fixed retain/free/enter sequence.
 * Confidence: low.
 * Notes: FUN_0034b044 / FUN_0036b270 / FUN_0036b118 / FUN_003566cc /
 *   FUN_0035270c.
 */
void sk_cap_ctl_seq(void)
{
    sk_ctx_fetch();                 /* FUN_0034b044 */
    sk_retain(0);                   /* FUN_0036b270 */
    sk_free(0);                     /* FUN_0036b118 */
    sk_ctx_fetch();                 /* FUN_003566cc */
    sk_state_enter2();              /* FUN_0035270c */
}

/*--------------------------------------------------------------------*/
/* FUN_0033ea80 @ 0x0033ea80   (est. sk_cap_ctl_alloc)
 * Ghidra: void FUN_0033ea80(long param_1)
 * Locks the object path (sk_object_lock(0x13f, param_1+0x18)) and when the
 * count is < 0x40 allocates an object (type 3) and runs a syscall op.
 * Confidence: low.
 * Notes: FUN_00377dcc / FUN_00357d44 / FUN_0034c16c / FUN_003728b8 /
 *   FUN_00019858.
 */
void sk_cap_ctl_alloc(long rec)
{
    void *ctx;
    word_t n;

    cl4_result_t r = { 0, 0 };      /* FUN_00377dcc(0x13f, *(rec+0x18)) */
    n = r.hi; ctx = (void *)r.lo;
    if (n < 0x40) {
        sk_ctx_fetch();             /* FUN_00357d44(*(ctx-8) + 0x40) */
        cl4_result_t obj = sk_object_alloc2();  /* FUN_0034c16c */
        sk_syscall_op(obj.lo, obj.hi, 3);       /* FUN_003728b8 */
        sk_try_acquire(0);          /* FUN_00019858 */
    }
}

/*--------------------------------------------------------------------*/
/* FUN_0033eafc @ 0x0033eafc   (est. sk_cap_op_validate)
 * Ghidra: void FUN_0033eafc(undefined8, undefined8, long param_3)
 * Validates a capability op against the object path at param_3+0x18. On the
 * success branch (ZR set, size < 0x19) runs the method sequence and copies a
 * field; else runs FUN_00349a9c; then retains.
 * Confidence: low.
 * Notes: callees FUN_00350c5c / FUN_0034b7e4 / FUN_0035510c / FUN_0034c144 /
 *   FUN_0034df14 / FUN_00349cd0 / FUN_003535e4 / FUN_00349a9c / FUN_0036b270.
 */
void sk_cap_op_validate(unsigned long p1, unsigned long p2, unsigned long p3)
{
    void *ctx;                      /* extraout_x16 */
    void *ctx2;                     /* extraout_x8 / extraout_x9 */
    word_t size;                    /* extraout_x10 */
    bool zf;                        /* in_ZR */

    cl4_result_t r = sk_ctx_fetch_pair();   /* FUN_00350c5c */
    sk_ctx_fetch();                 /* FUN_0034b7e4(r.lo, r.hi, *(p3+0x18)) */
    sk_ctx_fetch();                 /* FUN_0035510c */
    sk_ctx_fetch();                 /* FUN_0034c144 */
    if (zf && size < 0x19) {
        sk_ctx_fetch();             /* FUN_0034df14 */
        (*(void (**)(void))ctx2)();
        sk_ctx_fetch();             /* FUN_00349cd0 */
        sk_ctx_fetch();             /* FUN_003535e4 */
        *(uint8_t *)(ctx + 0x10) = *(uint8_t *)(ctx2 + 0x10);
    } else {
        sk_ctx_fetch();             /* FUN_00349a9c */
    }
    sk_retain(ctx);                 /* FUN_0036b270 */
}

/*--------------------------------------------------------------------*/
/* FUN_0033eb94 @ 0x0033eb94   (est. sk_cap_op_dispatch8)
 * Ghidra: void FUN_0033eb94(undefined8 param_1, long param_2)
 * Dispatches a cap op through the context method at +8, then releases fields.
 * Confidence: low.
 * Notes: callees FUN_0034ece8 / FUN_0034de54 / FUN_0036b118.
 */
void sk_cap_op_dispatch8(unsigned long p1, long p2)
{
    void *ctx;                      /* extraout_x16 */
    void *ctx2;                     /* extraout_x8 */

    sk_ctx_fetch();                 /* FUN_0034ece8(p1, *(p2+0x18)) */
    (*(void (**)(void))(ctx + 8))();
    sk_ctx_fetch();                 /* FUN_0034de54(*(ctx+0x40)) */
    sk_free((void *)*(word_t *)(ctx2 + 8)); /* FUN_0036b118 */
}

/*--------------------------------------------------------------------*/
/* FUN_0033ebe4 @ 0x0033ebe4   (est. sk_cap_op_method10)
 * Ghidra: void FUN_0033ebe4(undefined8, undefined8, long param_3)
 * Dispatches a cap op through the method table at +0x10 after validating the
 * object path at param_3+0x18.
 * Confidence: low.
 * Notes: callees FUN_003504d0 / FUN_0034b07c / FUN_00349104 / FUN_0034f22c /
 *   FUN_003594d4 / FUN_0036b270.
 */
void sk_cap_op_method10(unsigned long p1, unsigned long p2, unsigned long p3)
{
    void *ctx;                      /* extraout_x16 */

    cl4_result_t r = sk_ctx_fetch_pair();   /* FUN_003504d0 */
    sk_ctx_fetch();                 /* FUN_0034b07c(r.lo, r.hi, *(p3+0x18)) */
    (*(void (**)(void))(ctx + 0x10))();
    sk_ctx_fetch();                 /* FUN_00349104(*(ctx+0x40)) */
    sk_ctx_fetch();                 /* FUN_0034f22c */
    sk_ctx_fetch();                 /* FUN_003594d4 */
    sk_retain(ctx);                 /* FUN_0036b270 */
}

/*--------------------------------------------------------------------*/
/* FUN_0033ec44 @ 0x0033ec44   (est. sk_cap_op_method18)
 * Ghidra: void FUN_0033ec44(undefined8, undefined8, long param_3)
 * Dispatches through method slot +0x18, then swaps two words from an aligned
 * fetched record into the context (+0x18/+0x20), retaining/freeing and copying
 * a tag byte.
 * Confidence: low.
 * Notes: callees FUN_003504d0 / FUN_0034b07c / FUN_00351c04 / FUN_003594c8 /
 *   FUN_0036b270 / FUN_0036b118.
 */
void sk_cap_op_method18(unsigned long p1, unsigned long p2, unsigned long p3)
{
    void *ctx;                      /* extraout_x16 */
    word_t x8;

    cl4_result_t r = sk_ctx_fetch_pair();   /* FUN_003504d0 */
    sk_ctx_fetch();                 /* FUN_0034b07c(r.lo, r.hi, *(p3+0x18)) */
    (*(void (**)(void))(ctx + 0x18))();
    sk_ctx_fetch();                 /* FUN_00351c04(*(ctx+0x40)) */
    sk_ctx_fetch();                 /* FUN_003594c8 */
    undefined8 *p = (undefined8 *)(x8 & ~0x7ull);
    word_t old1 = *(word_t *)(ctx + 0x20);
    word_t n0 = *p;
    *(word_t *)(ctx + 0x20) = p[1];
    *(word_t *)(ctx + 0x18) = n0;
    sk_retain((void *)p[1]);        /* FUN_0036b270 */
    sk_free((void *)old1);          /* FUN_0036b118 */
    *(uint8_t *)(ctx + 0x28) = *(uint8_t *)(p + 2);
}

/*--------------------------------------------------------------------*/
/* FUN_0033ecc4 @ 0x0033ecc4   (est. sk_cap_op_method20)
 * Ghidra: void FUN_0033ecc4(undefined8, undefined8, long param_3)
 * Dispatches through method slot +0x20 after validating the object path.
 * Confidence: low.
 * Notes: callees FUN_003504d0 / FUN_0034b07c / FUN_00349104 / FUN_00352dac /
 *   FUN_003594d4.
 */
void sk_cap_op_method20(unsigned long p1, unsigned long p2, unsigned long p3)
{
    void *ctx;                      /* extraout_x16 */

    cl4_result_t r = sk_ctx_fetch_pair();   /* FUN_003504d0 */
    sk_ctx_fetch();                 /* FUN_0034b07c(r.lo, r.hi, *(p3+0x18)) */
    (*(void (**)(void))(ctx + 0x20))();
    sk_ctx_fetch();                 /* FUN_00349104(*(ctx+0x40)) */
    sk_ctx_fetch();                 /* FUN_00352dac */
    sk_ctx_fetch();                 /* FUN_003594d4 */
}

/*--------------------------------------------------------------------*/
/* FUN_0033ed20 @ 0x0033ed20   (est. sk_cap_op_method28)
 * Ghidra: void FUN_0033ed20(undefined8, undefined8, long param_3)
 * Dispatches through method slot +0x28, then swaps two words from an aligned
 * fetched record into the context (+0x28/+0x30), freeing the old +0x30.
 * Confidence: low.
 * Notes: callees FUN_003504d0 / FUN_0034b07c / FUN_00351c04 / FUN_003594c8 /
 *   FUN_0036b118.
 */
void sk_cap_op_method28(unsigned long p1, unsigned long p2, unsigned long p3)
{
    void *ctx;                      /* extraout_x16 */
    word_t x8;

    cl4_result_t r = sk_ctx_fetch_pair();   /* FUN_003504d0 */
    sk_ctx_fetch();                 /* FUN_0034b07c(r.lo, r.hi, *(p3+0x18)) */
    (*(void (**)(void))(ctx + 0x28))();
    sk_ctx_fetch();                 /* FUN_00351c04(*(ctx+0x40)) */
    sk_ctx_fetch();                 /* FUN_003594c8 */
    undefined8 *p = (undefined8 *)(x8 & ~0x7ull);
    word_t old = *(word_t *)(ctx + 0x30);
    word_t n0 = *p;
    *(word_t *)(ctx + 0x30) = p[1];
    *(word_t *)(ctx + 0x28) = n0;
    sk_free((void *)old);           /* FUN_0036b118 */
    *(uint8_t *)(ctx + 0x38) = *(uint8_t *)(p + 2);
}

/*--------------------------------------------------------------------*/
/* FUN_0033f0cc @ 0x0033f0cc   (est. sk_cap_ctl_path_alloc)
 * Ghidra: void FUN_0033f0cc(long param_1)
 * Nested capability-path control: locks the object path, and when the count is
 * < 0x40 walks a second path, allocates an object (type 3) and runs a syscall
 * op.
 * Confidence: low.
 * Notes: callees FUN_0034d4d4 / FUN_00377824 / FUN_00351244 / FUN_003728b8 /
 *   FUN_00019858.
 */
void sk_cap_ctl_path_alloc(long rec)
{
    void *ctx;
    word_t n;

    sk_ctx_fetch();                 /* FUN_0034d4d4(rec, *(rec+0x20), *(rec+0x10)) */
    cl4_result_t r = { 0, 0 };      /* FUN_00377824(0x13f) */
    n = r.hi; ctx = (void *)r.lo;
    if (n < 0x40) {
        sk_ctx_fetch();             /* FUN_0034d4d4(ctx-8, *(rec+0x28), *(rec+0x18)) */
        sk_object_lock(0x13f, 0, 0, NULL, NULL);    /* FUN_00377824 */
        if (0 < 0x40) {             /* extraout_x1 */
            cl4_result_t obj = sk_object_alloc2(); /* FUN_00351244 */
            sk_syscall_op(obj.lo, obj.hi, 3);       /* FUN_003728b8 */
            sk_try_acquire(0);      /* FUN_00019858 */
        }
    }
}

/*--------------------------------------------------------------------*/
/* FUN_0033f184 @ 0x0033f184   (est. sk_cap_op_validate2)
 * Ghidra: void FUN_0033f184(undefined8, undefined8, long param_3)
 * Syscall handler (per-CPU enter/exit FUN_0008e518/e500): validates two object
 * paths, and on the success branch (flags + size < 0x19) dispatches the two
 * method slots (+0x10 via extraout_x16 and extraout_x16_00) and copies a byte;
 * else runs the error path.
 * Confidence: low.
 * Notes: callees FUN_0008e518 / FUN_0034fc7c / FUN_003527e0 / FUN_00377824 /
 *   FUN_00348e00 / FUN_000a6f88 / FUN_0034d5d8 / FUN_0034bfb4 / FUN_00355800 /
 *   FUN_00350ed0 / FUN_0034de74 / FUN_0008e500.
 */
void sk_cap_op_validate2(unsigned long p1, unsigned long p2, unsigned long p3)
{
    void *ctxA, *ctxB;              /* extraout_x16 / extraout_x16_00 */
    long base;                      /* extraout_x8 + 0x40 */
    long dst;                       /* unaff_x21 */
    bool zf, cy;                    /* in_ZR / in_CY */
    int w10; word_t x11;

    sk_cpu_enter();                 /* FUN_0008e518 */
    sk_ctx_fetch();                 /* FUN_0034fc7c */
    sk_ctx_fetch();                 /* FUN_003527e0(0) */
    sk_object_lock(0, 0, 0, NULL, NULL);        /* FUN_00377824 */
    sk_ctx_fetch();                 /* FUN_00348e00 */
    sk_ctx_fetch();                 /* FUN_003527e0(0, *(p3+0x28), *(p3+0x18)) */
    sk_object_lock(0, 0, 0, NULL, NULL);        /* FUN_00377824 */
    sk_try_acquire(0);              /* FUN_000a6f88 */
    base = *(long *)(ctxB + 0x40);
    sk_ctx_fetch();                 /* FUN_0034d5d8(*(uint *)(ctxA+0x50) & 0xff) */
    if ((!cy || zf) && w10 == 0 && x11 < 0x19) {
        sk_ctx_fetch();             /* FUN_0034bfb4(*(ctxB+0x10)) */
        (*(void (**)(void))ctxA)();
        sk_ctx_fetch();             /* FUN_00355800 */
        sk_ctx_fetch();             /* FUN_00350ed0(*(ctxA+0x10)) */
        (*(void (**)(void))ctxB)();
        *(uint8_t *)(dst + base) = *(uint8_t *)(0 + base);  /* extraout_x1 */
    } else {
        sk_ctx_fetch();             /* FUN_0034de74 */
    }
    sk_cpu_exit(0);                 /* FUN_0008e500 */
}

/*--------------------------------------------------------------------*/
/* FUN_0033f2ac @ 0x0033f2ac   (est. sk_cap_op_dispatch8b)
 * Ghidra: void FUN_0033f2ac(void)
 * Two-path cap op: validates path (0x20, 0x10) then (0x28, 0x18), dispatching
 * through method slot +8; indirect jump table at 0x0033f360.
 * Confidence: low.
 * Notes: callees FUN_003504d0 / FUN_003515c0 / FUN_00377824 / FUN_000841a0 /
 *   FUN_0034bf0c; jumptable warning at 0x0033f360.
 */
void sk_cap_op_dispatch8b(void)
{
    void *ctxA, *ctxB;              /* extraout_x16 / extraout_x16_00 */
    long base;
    void *ctx = 0;                  /* unaff_x19 */
    void *dst = 0;                  /* unaff_x20 */

    sk_state_enter();               /* FUN_003504d0 */
    sk_ctx_fetch();                 /* FUN_003515c0(0, *(ctx+0x20), *(ctx+0x10)) */
    sk_object_lock(0, 0, 0, NULL, NULL);        /* FUN_00377824 */
    sk_ctx_fetch();                 /* FUN_000841a0 */
    (*(void (**)(void))(ctxA + 8))();
    base = *(long *)(ctxA + 0x40);
    sk_ctx_fetch();                 /* FUN_003515c0(0, *(ctx+0x28), *(ctx+0x18)) */
    sk_object_lock(0, 0, 0, NULL, NULL);        /* FUN_00377824 */
    /* FUN_0034bf0c: indirect jump table */
    (*(void (**)(word_t))(ctxB + 8))
        (base + (long)dst + (word_t)*(uint8_t *)(ctxB + 0x50) &
         ~(word_t)*(uint8_t *)(ctxB + 0x50));
}

/*--------------------------------------------------------------------*/
/* FUN_0033f414 @ 0x0033f414   (est. sk_cap_op_method18b)
 * Ghidra: void FUN_0033f414(void)
 * Cap op dispatching through method slot +0x18 after validating the object
 * path (0x28, 0x18); computes aligned operands.
 * Confidence: low.
 * Notes: callees FUN_0034ca7c / FUN_00349530 / FUN_00352c40 / FUN_00377824 /
 *   FUN_00355824.
 */
void sk_cap_op_method18b(void)
{
    void *ctxA, *ctxB;
    long base;
    void *src = 0;                  /* unaff_x20 */
    void *a = 0, *b = 0;            /* unaff_x19 / unaff_x21 */

    sk_ctx_fetch();                 /* FUN_0034ca7c */
    sk_obj_method();                /* FUN_00349530 */
    (*(void (**)(void))(ctxA + 0x18))();
    base = *(long *)(ctxA + 0x40);
    sk_ctx_fetch();                 /* FUN_00352c40(0, *(src+0x28), *(src+0x18)) */
    sk_object_lock(0, 0, 0, NULL, NULL);        /* FUN_00377824 */
    sk_obj_method();                /* FUN_00349530 */
    word_t tag = (word_t)*(uint8_t *)(ctxB + 0x50);
    base += tag;
    (*(void (**)(word_t, word_t))(ctxB + 0x18))
        (base + (long)a & ~tag, base + (long)b & ~tag);
    sk_ctx_fetch();                 /* FUN_00355824(*(ctxB+0x40)) */
}

/*--------------------------------------------------------------------*/
/* FUN_0033f4c4 @ 0x0033f4c4   (est. sk_cap_op_method20b)
 * Ghidra: void FUN_0033f4c4(void)
 * Same template as sk_cap_op_method18b but method slot +0x20.
 * Confidence: low.
 */
void sk_cap_op_method20b(void)
{
    void *ctxA, *ctxB;
    long base;
    void *src = 0;                  /* unaff_x20 */
    void *a = 0, *b = 0;            /* unaff_x19 / unaff_x21 */

    sk_ctx_fetch();                 /* FUN_0034ca7c */
    sk_obj_method();                /* FUN_00349530 */
    (*(void (**)(void))(ctxA + 0x20))();
    base = *(long *)(ctxA + 0x40);
    sk_ctx_fetch();                 /* FUN_00352c40(0, *(src+0x28), *(src+0x18)) */
    sk_object_lock(0, 0, 0, NULL, NULL);        /* FUN_00377824 */
    sk_obj_method();                /* FUN_00349530 */
    word_t tag = (word_t)*(uint8_t *)(ctxB + 0x50);
    base += tag;
    (*(void (**)(word_t, word_t))(ctxB + 0x20))
        (base + (long)a & ~tag, base + (long)b & ~tag);
    sk_ctx_fetch();                 /* FUN_00355824(*(ctxB+0x40)) */
}

/*--------------------------------------------------------------------*/
/* FUN_0033f574 @ 0x0033f574   (est. sk_cap_op_method28b)
 * Ghidra: void FUN_0033f574(void)
 * Same template as sk_cap_op_method18b but method slot +0x28.
 * Confidence: low.
 */
void sk_cap_op_method28b(void)
{
    void *ctxA, *ctxB;
    long base;
    void *src = 0;                  /* unaff_x20 */
    void *a = 0, *b = 0;            /* unaff_x19 / unaff_x21 */

    sk_ctx_fetch();                 /* FUN_0034ca7c */
    sk_obj_method();                /* FUN_00349530 */
    (*(void (**)(void))(ctxA + 0x28))();
    base = *(long *)(ctxA + 0x40);
    sk_ctx_fetch();                 /* FUN_00352c40(0, *(src+0x28), *(src+0x18)) */
    sk_object_lock(0, 0, 0, NULL, NULL);        /* FUN_00377824 */
    sk_obj_method();                /* FUN_00349530 */
    word_t tag = (word_t)*(uint8_t *)(ctxB + 0x50);
    base += tag;
    (*(void (**)(word_t, word_t))(ctxB + 0x28))
        (base + (long)a & ~tag, base + (long)b & ~tag);
    sk_ctx_fetch();                 /* FUN_00355824(*(ctxB+0x40)) */
}

/*--------------------------------------------------------------------*/
/* FUN_0033f624 @ 0x0033f624   (est. sk_syscall_varlen_ctl)
 * Ghidra: void FUN_0033f624(undefined8, undefined8, long param_3)
 * Complex syscall handler: validates two object paths, then walks a variable
 * length field (size byte, 1-4 byte payload with shift) to produce a result
 * that is returned through FUN_0008e500. Includes completion path via
 * FUN_000839f8.
 * Confidence: low (extensive register aliasing; control-flow complexity).
 * Notes: many callees; see comment block in decompile.
 */
void sk_syscall_varlen_ctl(unsigned long p1, unsigned long p2, unsigned long p3)
{
    void *ctxA, *ctxB;              /* extraout_x16 / extraout_x16_00 */
    uint32_t *buf = 0;              /* unaff_x19 */
    uint32_t v3;                    /* *(ctxA+0x54) */
    long base;                      /* *(ctxB+0x40) */
    word_t v9, v11;
    uint32_t w10, w1, w14, w8, w9, w12;
    int res;

    sk_cpu_enter();                 /* FUN_0008e518 */
    sk_ctx_fetch();                 /* FUN_0034fc7c */
    sk_ctx_fetch();                 /* FUN_003527e0(0) */
    sk_object_lock(0, 0, 0, NULL, NULL);        /* FUN_00377824 */
    sk_ctx_fetch();                 /* FUN_00358f30 */
    v3 = *(uint32_t *)(ctxA + 0x54);
    sk_ctx_fetch();                 /* FUN_003527e0(0, *(p3+0x28), *(p3+0x18)) */
    sk_object_lock(0, 0, 0, NULL, NULL);        /* FUN_00377824 */
    sk_ctx_fetch();                 /* FUN_0034c11c */
    sk_ctx_fetch();                 /* FUN_003559c8 */
    cl4_result_t r = sk_ctx_fetch_pair();       /* FUN_00352e90 */
    word_t u3 = r.hi;
    base = *(long *)(ctxB + 0x40);

    if (w1 == 0) {
        res = 0;
    } else {
        v11 = 0 + v9;                       /* extraout_x11 + extraout_x9 */
        v9 = 0;
        uint32_t u7 = w10;
        if (w10 < w1) {
            long pos = base + (v11 & ~0) + 1;
            uint32_t p = (uint32_t)pos;
            bool b1 = 2 < p, b2 = p == 3;
            uint32_t u10;
            if (p < 4) {
                sk_ctx_fetch();             /* FUN_0034d5b8 */
                u3 = 0; base = 0; v9 = 0; v11 = 0; u7 = w10;
                if (!b1 || b2) {
                    if (w14 < 2) goto done;
                    goto byte_sz;
                }
                if (w14 >> 0x10 == 0) {
                    u10 = (uint32_t)*(uint16_t *)((char *)buf + 0);
                } else {
                    u10 = *(uint32_t *)((char *)buf + 0);
                }
            } else {
byte_sz:
                u10 = (uint32_t)*(uint8_t *)((char *)buf + pos);
            }
            if (u10 == 0) goto done;
            sk_ctx_fetch();                 /* FUN_003525b8 */
            if (w12 == 0) {
                v3 = 0; u7 = w8; res = 0;
            } else {
                sk_ctx_fetch();             /* FUN_003538d4 */
                u7 = w8; res = 0;
                switch (w9) {
                default: v3 = (uint32_t)*(uint8_t *)buf; break;
                case 2: v3 = (uint32_t)*(uint16_t *)buf; break;
                case 3:
                    sk_ctx_fetch();         /* FUN_0034e32c */
                    u7 = w8; v3 = w9; res = 0;
                    break;
                case 4: v3 = *buf; break;
                }
                res = res + (v3 | u7);
            }
        } else {
done:
            if (v3 == u7) {
                sk_ctx_fetch();             /* FUN_0034bf1c */
                sk_cpu_exit(0);             /* FUN_0008e500 */
                sk_queue_complete(0, 0);    /* FUN_000839f8 */
                return;
            }
            if ((uint32_t)u3 == u7) {
                sk_cpu_exit(0);             /* FUN_0008e500 */
                sk_queue_complete(0, 0);    /* FUN_000839f8 */
                return;
            }
            v3 = (uint32_t)*(uint8_t *)((v11 + (long)buf & ~v9) + base);
            if (v3 < 2) { res = 0; }
            else { v3 = (v3 + 0x7ffffffe) & 0x7fffffff; }
        }
        res = v3 + 1;
    }
    sk_cpu_exit((void *)(long)res);         /* FUN_0008e500 */
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_0033fd44 @ 0x0033fd44   (est. sk_cap_ctl_pair)
 * Ghidra: void FUN_0033fd44(void)
 * Runs two path-validation helpers.
 * Confidence: low.
 * Notes: FUN_0034d4d4 / FUN_00340588 (local later in slice).
 */
void sk_cap_ctl_pair(void)
{
    sk_ctx_fetch();                 /* FUN_0034d4d4 */
    sk_ctx_fetch();                 /* FUN_00340588 */
}

/*--------------------------------------------------------------------*/
/* FUN_0033fd64 @ 0x0033fd64   (est. sk_cap_copy_wide2)
 * Ghidra: long * FUN_0033fd64(void)
 * Validates and, on success, copies a wide capability record field-by-field,
 * retaining; on failure copies a single word and advances the output pointer.
 * Confidence: low.
 * Notes: callees FUN_0034d724 / FUN_00349444 / FUN_00377824 / FUN_0034b57c /
 *   FUN_0035510c / FUN_0034c144 / FUN_0034df14 / FUN_00349cd0 / FUN_0036b270.
 */
long *sk_cap_copy_wide2(void)
{
    void *ctx;                      /* extraout_x16 */
    undefined1 *src, *dst;          /* extraout_x9_00 / extraout_x8 */
    long *out = 0;                  /* unaff_x19 */
    long *tail = 0;                 /* unaff_x20 */
    word_t size;                    /* extraout_x10 */
    bool zf;                        /* in_ZR */

    sk_ctx_fetch();                 /* FUN_0034d724 */
    sk_ctx_fetch();                 /* FUN_00349444 */
    sk_object_lock(0, 0, 0, NULL, NULL);        /* FUN_00377824 */
    sk_ctx_fetch();                 /* FUN_0034b57c */
    sk_ctx_fetch();                 /* FUN_0035510c */
    cl4_result_t r = sk_ctx_fetch_pair();       /* FUN_0034c144 */
    if (zf && size < 0x19) {
        sk_ctx_fetch();             /* FUN_0034df14(r.lo, r.hi, r.lo) */
        (*(void (**)(void))ctx)();
        sk_ctx_fetch();             /* FUN_00349cd0 */
        src = (undefined1 *)0; dst = (undefined1 *)0;
        dst[0] = src[0]; dst[1] = src[1]; dst[2] = src[2];
        dst[8] = src[8];
        *(word_t *)(dst + 0x10) = *(word_t *)(src + 0x10);
        dst[0x18] = src[0x18];
        *(uint32_t *)(dst + 0x1c) = *(uint32_t *)(src + 0x1c);
        *(uint32_t *)(dst + 0x1f) = *(uint32_t *)(src + 0x1f);
        dst[0x23] = src[0x23];
        *(long *)(dst + 0x28) = *(long *)(src + 0x28);
        dst[0x30] = src[0x30];
        *(uint32_t *)(dst + 0x34) = *(uint32_t *)(src + 0x34);
        dst[0x38] = src[0x38];
        sk_retain(0);               /* FUN_0036b270 */
    } else {
        long v = *tail;
        *out = v;
        out = (long *)(v + ((0 & ~0x7ull) + 0x17 & ~0x7ull & 0x1f8));
    }
    sk_retain(0);                   /* FUN_0036b270 */
    return out;
}

/*--------------------------------------------------------------------*/
/* FUN_0033fe7c @ 0x0033fe7c   (est. sk_cap_free_fields)
 * Ghidra: void FUN_0033fe7c(void)
 * Dispatches through method slot +8 then frees the object fields at an aligned
 * offset (+0x10, +0x28).
 * Confidence: low.
 * Notes: callees FUN_003561f4 / FUN_00349444 / FUN_00377824 / FUN_000841a0 /
 *   FUN_0036b118.
 */
void sk_cap_free_fields(void)
{
    void *ctx;                      /* extraout_x16 */
    void *ctx2;                     /* extraout_x8 */
    void *buf = 0;                  /* unaff_x19 */

    sk_ctx_fetch();                 /* FUN_003561f4 */
    sk_ctx_fetch();                 /* FUN_00349444 */
    sk_object_lock(0, 0, 0, NULL, NULL);        /* FUN_00377824 */
    sk_ctx_fetch();                 /* FUN_000841a0 */
    (*(void (**)(void))(ctx + 8))();
    word_t off = (word_t)buf + *(long *)(ctx + 0x40) + 7 & ~0x7ull;
    sk_free((void *)*(word_t *)(off + 0x10));   /* FUN_0036b118 */
    sk_free((void *)*(word_t *)(off + 0x28));   /* FUN_0036b118 */
}

/*--------------------------------------------------------------------*/
/* FUN_0033fee8 @ 0x0033fee8   (est. sk_cap_copy_aligned)
 * Ghidra: void FUN_0033fee8(void)
 * Dispatches through method slot +0x10, copies an aligned capability record
 * between two buffers, retaining the object fields.
 * Confidence: low.
 * Notes: callees FUN_0034d724 / FUN_00349444 / FUN_00377824 / FUN_00349530 /
 *   FUN_0036b270.
 */
void sk_cap_copy_aligned(void)
{
    void *ctx;                      /* extraout_x16 */
    void *a = 0, *b = 0;            /* unaff_x19 / unaff_x20 */
    undefined1 *src, *dst;
    word_t v28;

    sk_ctx_fetch();                 /* FUN_0034d724 */
    sk_ctx_fetch();                 /* FUN_00349444 */
    sk_object_lock(0, 0, 0, NULL, NULL);        /* FUN_00377824 */
    sk_obj_method();                /* FUN_00349530 */
    (*(void (**)(void))(ctx + 0x10))();
    long base = *(long *)(ctx + 0x40) + 7;
    dst = (undefined1 *)(base + (long)a & ~0x7ull);
    src = (undefined1 *)(base + (long)b & ~0x7ull);
    dst[0] = src[0]; dst[1] = src[1]; dst[2] = src[2];
    dst[8] = src[8];
    *(word_t *)(dst + 0x10) = *(word_t *)(src + 0x10);
    dst[0x18] = src[0x18];
    *(uint32_t *)(dst + 0x1c) = *(uint32_t *)(src + 0x1c);
    *(uint32_t *)(dst + 0x1f) = *(uint32_t *)(src + 0x1f);
    dst[0x23] = src[0x23];
    v28 = *(word_t *)(src + 0x28);
    *(word_t *)(dst + 0x28) = v28;
    dst[0x30] = src[0x30];
    *(uint32_t *)(dst + 0x34) = *(uint32_t *)(src + 0x34);
    dst[0x38] = src[0x38];
    sk_retain(0);                   /* FUN_0036b270 */
    sk_retain((void *)v28);         /* FUN_0036b270 */
}

/*--------------------------------------------------------------------*/
/* FUN_0033ffcc @ 0x0033ffcc   (est. sk_cap_merge_aligned)
 * Ghidra: void FUN_0033ffcc(void)
 * Dispatches through method slot +0x18 and merges an aligned capability record
 * into the context, retaining/freeing the object fields (+0x28, +0x40).
 * Confidence: low.
 * Notes: callees FUN_0034d724 / FUN_00349444 / FUN_00377824 / FUN_00349530 /
 *   FUN_0035953c / FUN_0036b270 / FUN_0036b118.
 */
void sk_cap_merge_aligned(void)
{
    void *ctx;                      /* extraout_x16 */
    word_t x8;
    undefined1 *src;
    word_t old;

    sk_ctx_fetch();                 /* FUN_0034d724 */
    sk_ctx_fetch();                 /* FUN_00349444 */
    sk_object_lock(0, 0, 0, NULL, NULL);        /* FUN_00377824 */
    sk_obj_method();                /* FUN_00349530 */
    (*(void (**)(void))(ctx + 0x18))();
    sk_ctx_fetch();                 /* FUN_0035953c(*(ctx+0x40)) */
    src = (undefined1 *)(x8 & ~0x7ull);
    *(uint8_t *)(ctx + 0x18) = src[0];
    *(uint8_t *)(ctx + 0x19) = src[1];
    *(uint8_t *)(ctx + 0x1a) = src[2];
    *(uint8_t *)(ctx + 0x20) = src[8];
    old = *(word_t *)(ctx + 0x28);
    *(word_t *)(ctx + 0x28) = *(word_t *)(src + 0x10);
    sk_retain(ctx);                 /* FUN_0036b270 */
    sk_free((void *)old);           /* FUN_0036b118 */
    *(uint8_t *)(ctx + 0x30) = src[0x18];
    *(uint32_t *)(ctx + 0x34) = *(uint32_t *)(src + 0x1c);
    *(uint32_t *)(ctx + 0x37) = *(uint32_t *)(src + 0x1f);
    *(uint8_t *)(ctx + 0x3b) = src[0x23];
    old = *(word_t *)(ctx + 0x40);
    *(word_t *)(ctx + 0x40) = *(word_t *)(src + 0x28);
    sk_retain(ctx);                 /* FUN_0036b270 */
    sk_free((void *)old);           /* FUN_0036b118 */
    *(uint8_t *)(ctx + 0x48) = src[0x30];
    *(uint32_t *)(ctx + 0x4c) = *(uint32_t *)(src + 0x34);
    *(uint8_t *)(ctx + 0x50) = src[0x38];
}

/*--------------------------------------------------------------------*/
/* FUN_003400b8 @ 0x003400b8   (est. sk_cap_copy_wide3)
 * Ghidra: void FUN_003400b8(void)
 * Dispatches through method slot +0x20 and copies a wide capability record
 * between two fetched buffers.
 * Confidence: low.
 * Notes: callees FUN_0034dbd8 / FUN_00349444 / FUN_00377824 / FUN_00349530 /
 *   FUN_00349104.
 */
void sk_cap_copy_wide3(void)
{
    void *ctx;                      /* extraout_x16 */
    undefined8 *src, *dst;          /* extraout_x8 / extraout_x9 */

    sk_ctx_fetch();                 /* FUN_0034dbd8 */
    sk_ctx_fetch();                 /* FUN_00349444 */
    sk_object_lock(0, 0, 0, NULL, NULL);        /* FUN_00377824 */
    sk_obj_method();                /* FUN_00349530 */
    (*(void (**)(void))(ctx + 0x20))();
    sk_ctx_fetch();                 /* FUN_00349104(*(ctx+0x40)) */
    src = 0; dst = 0;
    undefined8 v5 = src[3], v4 = src[2], v2 = src[5], v1 = src[4];
    undefined8 v3 = *(word_t *)((char *)src + 0x29);
    undefined8 v7 = src[1], v6 = src[0];
    *(word_t *)((char *)dst + 0x31) = *(word_t *)((char *)src + 0x31);
    *(word_t *)((char *)dst + 0x29) = v3;
    dst[3] = v5; dst[2] = v4; dst[5] = v2; dst[4] = v1;
    dst[1] = v7; dst[0] = v6;
}

/*--------------------------------------------------------------------*/
/* FUN_00340130 @ 0x00340130   (est. sk_cap_merge_aligned28)
 * Ghidra: void FUN_00340130(void)
 * Dispatches through method slot +0x28 and merges an aligned capability record
 * into the context, freeing the replaced fields (+0x38, +0x50).
 * Confidence: low.
 * Notes: callees FUN_0034d724 / FUN_00349444 / FUN_00377824 / FUN_00349530 /
 *   FUN_0035953c / FUN_0036b118.
 */
void sk_cap_merge_aligned28(void)
{
    void *ctx;                      /* extraout_x16 */
    word_t x8;
    undefined1 *src;
    word_t old;

    sk_ctx_fetch();                 /* FUN_0034d724 */
    sk_ctx_fetch();                 /* FUN_00349444 */
    sk_object_lock(0, 0, 0, NULL, NULL);        /* FUN_00377824 */
    sk_obj_method();                /* FUN_00349530 */
    (*(void (**)(void))(ctx + 0x28))();
    sk_ctx_fetch();                 /* FUN_0035953c(*(ctx+0x40)) */
    src = (undefined1 *)(x8 & ~0x7ull);
    *(uint8_t *)(ctx + 0x28) = src[0];
    *(uint8_t *)(ctx + 0x29) = src[1];
    *(uint8_t *)(ctx + 0x2a) = src[2];
    *(uint8_t *)(ctx + 0x30) = src[8];
    old = *(word_t *)(ctx + 0x38);
    *(word_t *)(ctx + 0x38) = *(word_t *)(src + 0x10);
    sk_free((void *)old);           /* FUN_0036b118 */
    *(uint8_t *)(ctx + 0x40) = src[0x18];
    *(uint32_t *)(ctx + 0x44) = *(uint32_t *)(src + 0x1c);
    *(uint32_t *)(ctx + 0x47) = *(uint32_t *)(src + 0x1f);
    *(uint8_t *)(ctx + 0x4b) = src[0x23];
    old = *(word_t *)(ctx + 0x50);
    *(word_t *)(ctx + 0x50) = *(word_t *)(src + 0x28);
    sk_free((void *)old);           /* FUN_0036b118 */
    *(uint8_t *)(ctx + 0x58) = src[0x30];
    *(uint32_t *)(ctx + 0x5c) = *(uint32_t *)(src + 0x34);
    *(uint8_t *)(ctx + 0x60) = src[0x38];
}

/*--------------------------------------------------------------------*/
/* FUN_0034020c @ 0x0034020c   (est. sk_cap_lookup)
 * Ghidra: ulong FUN_0034020c(void)
 * Capability lookup/decoding: validates the record, then walks a variable
 * length field to compute a shift/mask result; on failure returns a size or a
 * queue-completion result. Contains a software-breakpoint (0x34033c) on a
 * reserved size class.
 * Confidence: low (register aliasing; control-flow complexity).
 * Notes: callees FUN_0034d724 / FUN_00349444 / FUN_00377824 / FUN_0034ada0 /
 *   FUN_00355008 / FUN_00356638 / FUN_00356e74 / FUN_00356e64 / FUN_0034de54 /
 *   FUN_000839f8; SoftwareBreakpoint(1, 0x34033c).
 */
ulong sk_cap_lookup(void)
{
    void *ctx;                      /* extraout_x16 */
    void *ctx2;                     /* extraout_x8 / extraout_x8_00 */
    void *buf = 0;                  /* unaff_x19 */
    uint32_t w20 = 0;               /* unaff_w20 */
    word_t v5, out;

    sk_ctx_fetch();                 /* FUN_0034d724 */
    sk_ctx_fetch();                 /* FUN_00349444 */
    sk_object_lock(0, 0, 0, NULL, NULL);        /* FUN_00377824 */
    word_t v = sk_try_acquire(0);   /* FUN_0034ada0 */
    cl4_result_t r = sk_ctx_fetch_pair();       /* FUN_00355008(v, *(ctx+0x54)) */
    v5 = r.hi;
    if (w20 == 0) {
        return 0;
    }
    if (0 < w20) {                  /* extraout_w9 < unaff_w20 */
        sk_ctx_fetch();             /* FUN_00356638(*(ctx2+0x40), r.lo, v5, r.lo) */
        sk_ctx_fetch();             /* FUN_00356e74 */
        uint32_t u2;
        if (0 < 0x100) { u2 = 1; }  /* extraout_w11 < 0x100 */
        else { u2 = 0; }
        uint32_t u1 = 0;
        if (1 < 0) { u1 = u2; }     /* 1 < extraout_w11 */
        v5 = 0;                     /* extraout_x1 */
        uint32_t u7;
        switch (u1) {
        case 1:
            u7 = (uint32_t)*(uint8_t *)((char *)buf + 0);
            if (*(uint8_t *)((char *)buf + 0) != 0) goto shift;
            break;
        case 2:
            u7 = (uint32_t)*(uint16_t *)((char *)buf + 0);
            if (*(uint16_t *)((char *)buf + 0) != 0) goto shift;
            break;
        case 3:
            /* WARNING: does not return: SoftwareBreakpoint(1, 0x34033c) */
            return 0;
        default:
            u7 = *(uint32_t *)((char *)buf + 0);
            if (u7 != 0) {
shift:
                int sh = (u7 - 1) << (((0 & 3) << 3));
                if (3 < 0) { sh = 0; }
                return (ulong)sk_ctx_fetch();   /* FUN_00356e64(sh) */
            }
            break;
        }
    }
    if ((uint32_t)v5 < 0x1000) {
        sk_ctx_fetch();             /* FUN_0034de54 */
        uint32_t n = 0;
        if (*(word_t *)(ctx2 + 0x10) < 0x1000) {
            n = (uint32_t)*(word_t *)(ctx2 + 0x10) + 1;
        }
        return n;
    }
    out = sk_queue_complete(0, 0);  /* FUN_000839f8 */
    return out;
}

/*--------------------------------------------------------------------*/
/* FUN_00340538 @ 0x00340538   (est. sk_ctl_guard)
 * Ghidra: void FUN_00340538(void)
 * Delegates to FUN_00021480.
 * Confidence: low.
 */
void sk_ctl_guard(void)
{
    sk_try_acquire(0);              /* FUN_00021480 */
}

/*--------------------------------------------------------------------*/
/* FUN_00340568 @ 0x00340568   (est. sk_cap_ctl_pair2)
 * Ghidra: void FUN_00340568(void)
 * Runs two path-validation helpers (the second is local FUN_00340588).
 * Confidence: low.
 * Notes: FUN_0034d4d4 / FUN_00340588 (local).
 */
void sk_cap_ctl_pair2(void)
{
    sk_ctx_fetch();                 /* FUN_0034d4d4 */
    sk_ctx_fetch();                 /* FUN_00340588 (local) */
}

/*--------------------------------------------------------------------*/
/* FUN_00340588 @ 0x00340588   (est. sk_cap_ctl_alloc2)
 * Ghidra: void FUN_00340588(long param_1)
 * Locks the object path (sk_object_lock(0x13f, param_1+0x18, param_1+0x10))
 * and when the count is < 0x40 allocates an object (type 2) and runs a syscall
 * op with selector 2.
 * Confidence: low.
 * Notes: callees FUN_00377824 / FUN_0034cdf8 / FUN_003728b8 / FUN_00019858.
 */
void sk_cap_ctl_alloc2(long rec)
{
    word_t n;

    sk_object_lock(0x13f, *(word_t *)(rec + 0x18), *(word_t *)(rec + 0x10),
                   NULL, NULL);     /* FUN_00377824 */
    n = 0;                          /* extraout_x1 */
    if (n < 0x40) {
        cl4_result_t obj = sk_object_alloc2();  /* FUN_0034cdf8 */
        sk_syscall_op(obj.lo, obj.hi, 2);       /* FUN_003728b8 */
        sk_try_acquire(0);          /* FUN_00019858 */
    }
}

/*--------------------------------------------------------------------*/
/* FUN_003405fc @ 0x003405fc   (est. sk_cap_copy_med)
 * Ghidra: void FUN_003405fc(void)
 * Validates and, on success, copies a medium capability record (fields up to
 * +0x1b), retaining; on failure runs the error path.
 * Confidence: low.
 * Notes: callees FUN_0034d724 / FUN_00349444 / FUN_00377824 / FUN_0034b57c /
 *   FUN_0035510c / FUN_0034c144 / FUN_0034df14 / FUN_00349cd0 / FUN_00349a9c /
 *   FUN_0036b270.
 */
void sk_cap_copy_med(void)
{
    undefined1 *src, *dst;          /* extraout_x9_00 / extraout_x8 */
    word_t size;                    /* extraout_x10 */
    bool zf;                        /* in_ZR */

    sk_ctx_fetch();                 /* FUN_0034d724 */
    sk_ctx_fetch();                 /* FUN_00349444 */
    sk_object_lock(0, 0, 0, NULL, NULL);        /* FUN_00377824 */
    sk_ctx_fetch();                 /* FUN_0034b57c */
    sk_ctx_fetch();                 /* FUN_0035510c */
    cl4_result_t r = sk_ctx_fetch_pair();       /* FUN_0034c144 */
    if (zf && size < 0x19) {
        sk_ctx_fetch();             /* FUN_0034df14(r.lo, r.hi, r.lo) */
        { void (*meth)(void) = (void (*)(void))0; /* extraout_x9 */ meth(); }
        sk_ctx_fetch();             /* FUN_00349cd0 */
        src = 0; dst = 0;
        dst[0] = src[0];
        *(word_t *)(dst + 8) = *(word_t *)(src + 8);
        dst[0x10] = src[0x10];
        *(uint32_t *)(dst + 0x14) = *(uint32_t *)(src + 0x14);
        *(uint32_t *)(dst + 0x17) = *(uint32_t *)(src + 0x17);
        dst[0x1b] = src[0x1b];
    } else {
        sk_ctx_fetch();             /* FUN_00349a9c */
    }
    sk_retain(0);                   /* FUN_0036b270 */
}

/*--------------------------------------------------------------------*/
/* FUN_003406d0 @ 0x003406d0   (est. sk_cap_op_path3)
 * Ghidra: void FUN_003406d0(void)
 * Dispatches a cap op through method slot +8 after validating the object path,
 * then releases the +8 field.
 * Confidence: low.
 * Notes: callees FUN_00355694 / FUN_003524bc / FUN_00377824 / FUN_000841a0 /
 *   FUN_0034de54 / FUN_0036b118.
 */
void sk_cap_op_path3(void)
{
    void *ctx;                      /* extraout_x16 */
    void *ctx2;                     /* extraout_x8 */

    cl4_result_t p = sk_ctx_fetch_pair();       /* FUN_00355694 */
    void *rec = (void *)p.hi;
    sk_ctx_fetch();                 /* FUN_003524bc(*(rec+0x18), p.lo, rec, *(rec+0x10)) */
    sk_object_lock(0, 0, 0, NULL, NULL);        /* FUN_00377824 */
    sk_ctx_fetch();                 /* FUN_000841a0 */
    (*(void (**)(void))(ctx + 8))();
    sk_ctx_fetch();                 /* FUN_0034de54(*(ctx+0x40)) */
    sk_free((void *)*(word_t *)(ctx2 + 8));     /* FUN_0036b118 */
}

/*--------------------------------------------------------------------*/
/* FUN_0034072c @ 0x0034072c   (est. sk_cap_copy_med10)
 * Ghidra: void FUN_0034072c(void)
 * Dispatches through method slot +0x10 and copies a medium capability record,
 * retaining.
 * Confidence: low.
 * Notes: callees FUN_0034dbd8 / FUN_00349444 / FUN_00377824 / FUN_00349530 /
 *   FUN_00349104 / FUN_0036b270.
 */
void sk_cap_copy_med10(void)
{
    void *ctx;                      /* extraout_x16 */
    undefined1 *src, *dst;          /* extraout_x8 / extraout_x9 */

    sk_ctx_fetch();                 /* FUN_0034dbd8 */
    sk_ctx_fetch();                 /* FUN_00349444 */
    sk_object_lock(0, 0, 0, NULL, NULL);        /* FUN_00377824 */
    sk_obj_method();                /* FUN_00349530 */
    (*(void (**)(void))(ctx + 0x10))();
    sk_ctx_fetch();                 /* FUN_00349104(*(ctx+0x40)) */
    src = 0; dst = 0;
    dst[0] = src[0];
    *(word_t *)(dst + 8) = *(word_t *)(src + 8);
    dst[0x10] = src[0x10];
    *(uint32_t *)(dst + 0x14) = *(uint32_t *)(src + 0x14);
    *(uint32_t *)(dst + 0x17) = *(uint32_t *)(src + 0x17);
    dst[0x1b] = src[0x1b];
    sk_retain(0);                   /* FUN_0036b270 */
}

/*--------------------------------------------------------------------*/
/* FUN_003407c0 @ 0x003407c0   (est. sk_cap_merge_med18)
 * Ghidra: void FUN_003407c0(void)
 * Dispatches through method slot +0x18 and merges a medium capability record
 * into the context, retaining the new +0x20 and freeing the old.
 * Confidence: low.
 * Notes: callees FUN_0034dbd8 / FUN_00349444 / FUN_00377824 / FUN_00349530 /
 *   FUN_00351c04 / FUN_003594c8 / FUN_0036b270 / FUN_0036b118.
 */
void sk_cap_merge_med18(void)
{
    void *ctx;                      /* extraout_x16 */
    word_t x8;
    undefined1 *src;
    word_t old;

    sk_ctx_fetch();                 /* FUN_0034dbd8 */
    sk_ctx_fetch();                 /* FUN_00349444 */
    sk_object_lock(0, 0, 0, NULL, NULL);        /* FUN_00377824 */
    sk_obj_method();                /* FUN_00349530 */
    (*(void (**)(void))(ctx + 0x18))();
    sk_ctx_fetch();                 /* FUN_00351c04(*(ctx+0x40)) */
    sk_ctx_fetch();                 /* FUN_003594c8 */
    src = (undefined1 *)(x8 & ~0x7ull);
    *(uint8_t *)(ctx + 0x18) = src[0];
    old = *(word_t *)(ctx + 0x20);
    *(word_t *)(ctx + 0x20) = *(word_t *)(src + 8);
    sk_retain(ctx);                 /* FUN_0036b270 */
    sk_free((void *)old);           /* FUN_0036b118 */
    *(uint8_t *)(ctx + 0x28) = src[0x10];
    *(uint32_t *)(ctx + 0x2c) = *(uint32_t *)(src + 0x14);
    *(uint32_t *)(ctx + 0x2f) = *(uint32_t *)(src + 0x17);
    *(uint8_t *)(ctx + 0x33) = src[0x1b];
}

/*--------------------------------------------------------------------*/
/* FUN_00340868 @ 0x00340868   (est. sk_cap_copy_med20)
 * Ghidra: void FUN_00340868(void)
 * Dispatches through method slot +0x20 and copies a medium capability record.
 * Confidence: low.
 * Notes: callees FUN_0034dbd8 / FUN_00349444 / FUN_00377824 / FUN_00349530 /
 *   FUN_00349104.
 */
void sk_cap_copy_med20(void)
{
    void *ctx;                      /* extraout_x16 */
    undefined8 *src, *dst;          /* extraout_x8 / extraout_x9 */

    sk_ctx_fetch();                 /* FUN_0034dbd8 */
    sk_ctx_fetch();                 /* FUN_00349444 */
    sk_object_lock(0, 0, 0, NULL, NULL);        /* FUN_00377824 */
    sk_obj_method();                /* FUN_00349530 */
    (*(void (**)(void))(ctx + 0x20))();
    sk_ctx_fetch();                 /* FUN_00349104(*(ctx+0x40)) */
    src = 0; dst = 0;
    word_t v2 = *(word_t *)((char *)src + 0x14);
    word_t v1 = *(word_t *)((char *)src + 0xc);
    word_t v3 = *src;
    dst[1] = src[1];
    *dst = v3;
    *(word_t *)((char *)dst + 0x14) = v2;
    *(word_t *)((char *)dst + 0xc) = v1;
}

/*--------------------------------------------------------------------*/
/* FUN_003408d8 @ 0x003408d8   (est. sk_cap_merge_med28)
 * Ghidra: void FUN_003408d8(void)
 * Dispatches through method slot +0x28 and merges a medium capability record
 * into the context, freeing the replaced +0x30 field.
 * Confidence: low.
 * Notes: callees FUN_0034dbd8 / FUN_00349444 / FUN_00377824 / FUN_00349530 /
 *   FUN_00351c04 / FUN_003594c8 / FUN_0036b118.
 */
void sk_cap_merge_med28(void)
{
    void *ctx;                      /* extraout_x16 */
    word_t x8;
    undefined1 *src;
    word_t old;

    sk_ctx_fetch();                 /* FUN_0034dbd8 */
    sk_ctx_fetch();                 /* FUN_00349444 */
    sk_object_lock(0, 0, 0, NULL, NULL);        /* FUN_00377824 */
    sk_obj_method();                /* FUN_00349530 */
    (*(void (**)(void))(ctx + 0x28))();
    sk_ctx_fetch();                 /* FUN_00351c04(*(ctx+0x40)) */
    sk_ctx_fetch();                 /* FUN_003594c8 */
    src = (undefined1 *)(x8 & ~0x7ull);
    *(uint8_t *)(ctx + 0x28) = src[0];
    old = *(word_t *)(ctx + 0x30);
    *(word_t *)(ctx + 0x30) = *(word_t *)(src + 8);
    sk_free((void *)old);           /* FUN_0036b118 */
    *(uint8_t *)(ctx + 0x38) = src[0x10];
    *(uint32_t *)(ctx + 0x3c) = *(uint32_t *)(src + 0x14);
    *(uint32_t *)(ctx + 0x3f) = *(uint32_t *)(src + 0x17);
    *(uint8_t *)(ctx + 0x43) = src[0x1b];
}

/*--------------------------------------------------------------------*/
/* FUN_00340978 @ 0x00340978   (est. sk_cap_lookup2)
 * Ghidra: ulong FUN_00340978(void)
 * Capability lookup similar to sk_cap_lookup: walks a variable-length field and
 * returns a computed size/index; on failure returns a size or queue result.
 * Confidence: low.
 * Notes: callees FUN_0034d724 / FUN_00349444 / FUN_00377824 / FUN_0034ada0 /
 *   FUN_00355008 / FUN_00356638 / FUN_0034de54 / FUN_000839f8.
 */
ulong sk_cap_lookup2(void)
{
    void *ctx;                      /* extraout_x16 */
    void *ctx2;                     /* extraout_x8 / extraout_x8_00 */
    void *buf = 0;                  /* unaff_x19 */
    uint32_t w20 = 0;               /* unaff_w20 */
    word_t v;
    ulong out;

    sk_ctx_fetch();                 /* FUN_0034d724 */
    sk_ctx_fetch();                 /* FUN_00349444 */
    sk_object_lock(0, 0, 0, NULL, NULL);        /* FUN_00377824 */
    word_t v0 = sk_try_acquire(0);  /* FUN_0034ada0 */
    cl4_result_t r = sk_ctx_fetch_pair();       /* FUN_00355008(v0, *(ctx+0x54)) */
    v = r.hi;
    if (w20 == 0) {
        out = 0;
    } else if (0 < w20) {
        sk_ctx_fetch();             /* FUN_00356638 */
        v = 0;                      /* extraout_x1 */
        if (*(char *)((char *)buf + 0x1c) != '\0') {
            out = (ulong)(0 + *(int *)buf + 1);  /* extraout_w9_00 + *unaff_x19 + 1 */
        } else {
            if (0xfff < (uint32_t)v) {
                out = sk_queue_complete(0, 0);      /* FUN_000839f8 */
                return out;
            }
            sk_ctx_fetch();         /* FUN_0034de54 */
            uint32_t n = 0;
            if (*(word_t *)(ctx2 + 8) < 0x1000) {
                n = (uint32_t)*(word_t *)(ctx2 + 8) + 1;
            }
            out = n;
        }
    } else {
        out = 0;
    }
    return out;
}

/*--------------------------------------------------------------------*/
/* FUN_00340a2c @ 0x00340a2c   (est. sk_cap_resize)
 * Ghidra: void FUN_00340a2c(undefined8, undefined8, uint param_3, long param_4)
 * Capability resize operation: validates the object path (param_4+0x18/0x10),
 * computes a new size, writes a length field and flag byte, and on the grow
 * path updates a size record; validates the 0xfff threshold with error paths.
 * Confidence: low (register aliasing; complex conditionals).
 * Notes: callees FUN_003504d0 / FUN_00349444 / FUN_00377824 / FUN_000a6f88 /
 *   FUN_00350af4 / FUN_00114330 / FUN_0007c1c4 / FUN_00355d60 / FUN_000839d8.
 */
void sk_cap_resize(unsigned long p1, unsigned long p2, unsigned int param_3, long param_4)
{
    void *ctx;                      /* extraout_x16 */
    void *ctx2;                     /* extraout_x8 */
    ulong *sizerec;                 /* extraout_x8_00 */
    int *buf = 0;                   /* unaff_x20 */
    uint32_t w19 = 0;               /* unaff_w19 */
    uint32_t cur, newsz;
    long base;
    long pos;

    sk_state_enter();               /* FUN_003504d0 */
    sk_ctx_fetch();                 /* FUN_00349444 */
    sk_object_lock(0, 0, 0, NULL, NULL);        /* FUN_00377824 */
    sk_try_acquire(0);              /* FUN_000a6f88 */
    cur = *(uint32_t *)(ctx + 0x54);
    newsz = cur;
    if (cur < 0x1001) {
        newsz = 0x1000;
    }
    base = *(long *)(ctx2 + 0x40);
    pos = (base + 7 & ~0x7ull) + 0x1c;
    if (newsz < w19) {
        sk_ctx_fetch();             /* FUN_00350af4 */
        sk_obj_meta(0);             /* FUN_00114330 */
        *buf = w19 + ~newsz;
        if (newsz < param_3) {
            *(uint8_t *)((char *)buf + pos) = 1;
        }
    } else {
        if (newsz < param_3) {
            *(uint8_t *)((char *)buf + pos) = 0;
        }
        if (w19 != 0) {
            if (0xfff < cur) {
                sk_try_acquire(0);  /* FUN_0007c1c4 */
                sk_obj_complete();  /* FUN_000839d8 */
                return;
            }
            sk_ctx_fetch();         /* FUN_00355d60((char *)buf + base) */
            if (w19 < 0x1001) {
                sizerec[1] = (ulong)(w19 - 1);
            } else {
                sizerec[1] = 0;
                sizerec[2] = 0;
                *(uint32_t *)(sizerec + 3) = 0;
                sizerec[0] = (ulong)(w19 - 0x1001);
            }
        }
    }
}

/*--------------------------------------------------------------------*/
/* FUN_00340b40 @ 0x00340b40   (est. sk_ctl_guard2)
 * Ghidra: void FUN_00340b40(void)
 * Delegates to FUN_00021480.
 * Confidence: low.
 */
void sk_ctl_guard2(void)
{
    sk_try_acquire(0);              /* FUN_00021480 */
}

/*--------------------------------------------------------------------*/
/* FUN_00340f18 @ 0x00340f18   (est. sk_cap_free2b)
 * Ghidra: void FUN_00340f18(long param_1)
 * Frees the +8 and +0x20 object fields of a capability record.
 * Confidence: medium.
 * Notes: FUN_0036b118.
 */
void sk_cap_free2b(long rec)
{
    sk_free((void *)*(word_t *)(rec + 8));      /* FUN_0036b118 */
    sk_free((void *)*(word_t *)(rec + 0x20));   /* FUN_0036b118 */
}

/*--------------------------------------------------------------------*/
/* FUN_00340f4c @ 0x00340f4c   (est. sk_cap_copy_med2)
 * Ghidra: long FUN_00340f4c(long param_1, long param_2)
 * Copies a medium capability record from param_2+8's fetched context into
 * param_1, retaining the object fields (+0x18, +0x20).
 * Confidence: low.
 * Notes: callees FUN_00355e98 / FUN_0036b270.
 */
long sk_cap_copy_med2(long dst, long src)
{
    word_t v1, v2;

    sk_ctx_fetch();                 /* FUN_00355e98(*(src+8)) */
    *(uint8_t *)(dst + 0x10) = *(uint8_t *)(0 + 0x10);  /* extraout_x1 */
    v1 = *(word_t *)(0 + 0x20);     /* extraout_x1 + 0x20 */
    v2 = *(word_t *)(0 + 0x18);     /* extraout_x1 + 0x18 */
    *(word_t *)(dst + 0x20) = *(word_t *)(0 + 0x20);
    *(word_t *)(dst + 0x18) = v2;
    *(uint8_t *)(dst + 0x28) = *(uint8_t *)(0 + 0x28);
    sk_retain((void *)dst);         /* FUN_0036b270 */
    sk_retain((void *)v1);          /* FUN_0036b270 */
    return dst;
}

/*--------------------------------------------------------------------*/
/* FUN_0034100c @ 0x0034100c   (est. sk_cap_merge10)
 * Ghidra: void FUN_0034100c(void)
 * Merges a capability record into the destination, freeing replaced fields.
 * Confidence: low.
 * Notes: callees FUN_003504d0 / FUN_0036b118 / FUN_00359cf8.
 */
void sk_cap_merge10(void)
{
    void *ctx = 0;                  /* unaff_x19 */
    undefined8 *dst = 0;            /* unaff_x20 */
    word_t old;

    cl4_result_t p = sk_ctx_fetch_pair();       /* FUN_003504d0 */
    undefined8 *psrc = (undefined8 *)p.hi;      /* auVar3._8_8_ */
    old = *(word_t *)(p.lo + 8);
    dst[1] = psrc[1];
    dst[0] = psrc[0];
    sk_free((void *)old);           /* FUN_0036b118 */
    sk_ctx_fetch();                 /* FUN_00359cf8 */
    old = dst[4];
    dst[4] = *(word_t *)(ctx + 0x20);
    dst[3] = *(word_t *)(ctx + 0x18);
    sk_free((void *)old);           /* FUN_0036b118 */
    *(uint8_t *)(dst + 5) = *(uint8_t *)(ctx + 0x28);
}

/*--------------------------------------------------------------------*/
/* FUN_00341258 @ 0x00341258   (est. sk_cap_release_meta8)
 * Ghidra: void FUN_00341258(void)
 * Releases metadata on the +8 field after the fetch/meta steps.
 * Confidence: low.
 * Notes: FUN_00352b20 / FUN_003a25d4.
 */
void sk_cap_release_meta8(void)
{
    void *ctx = 0;                  /* unaff_x19 */

    sk_ctx_fetch();                 /* FUN_00352b20 */
    sk_obj_meta(0);                 /* FUN_003a25d4 */
    sk_obj_meta(*(word_t *)(ctx + 8));      /* FUN_003a25d4 */
}

/*--------------------------------------------------------------------*/
/* FUN_003412a0 @ 0x003412a0   (est. sk_panic_ctl_c)
 * Ghidra: void FUN_003412a0(void)
 * Kernel-enter, lock-release, then if count < 0x40 formats a panic record and
 * runs the housekeeping sequence.
 * Confidence: low.
 * Notes: helpers FUN_0034c7c4 / FUN_00377dcc / FUN_00371758 / FUN_0034d034 /
 *   FUN_003728b8 / FUN_00019858.
 */
void sk_panic_ctl_c(void)
{
    void *ctx;
    word_t n;
    char buf[32];

    sk_cpu_enter_kernel();          /* FUN_0034c7c4 */
    cl4_result_t r = { 0, 0 };      /* FUN_00377dcc */
    n = r.hi; ctx = (void *)r.lo;
    if (n < 0x40) {
        long base = *(long *)((char *)ctx - 8);
        sk_ctx_fetch();             /* FUN_00371758(buf, base+0x40, base+0x40) */
        sk_ctx_fetch();             /* FUN_0034d034 */
        sk_syscall_op(0, 0, 0);     /* FUN_003728b8 */
        sk_try_acquire(0);          /* FUN_00019858 */
    }
}

/*--------------------------------------------------------------------*/
/* FUN_00341318 @ 0x00341318   (est. sk_cap_op_path4)
 * Ghidra: void FUN_00341318(undefined8, undefined8, long param_3)
 * Syscall handler (per-CPU enter/exit FUN_00084220/34): validates the object
 * path (param_3+0x10), and on the success branch dispatches the method at
 * ctx+0x10 with aligned operands; else copies a record and retains.
 * Confidence: low.
 * Notes: callees FUN_00084220 / FUN_00351a38 / FUN_00349b00 / FUN_0034bf1c /
 *   FUN_0036b270 / FUN_00084234.
 */
void sk_cap_op_path4(unsigned long p1, unsigned long p2, unsigned long p3)
{
    void *ctx;                      /* extraout_x16 */
    void *ctx2;                     /* extraout_x8 */
    long *dst = 0;                  /* unaff_x19 */
    long *src = 0;                  /* unaff_x21 */
    word_t val, tag, nottag;
    long base;

    sk_cpu_enter();                 /* FUN_00084220 */
    sk_ctx_fetch();                 /* FUN_00351a38 */
    val = *(word_t *)(p3 + 0x10);
    sk_obj_path(0, 0);              /* FUN_00349b00 */
    tag = (word_t)*(uint32_t *)(ctx + 0x50) & 0xff;
    nottag = ~tag;
    base = *(long *)(ctx2 + 0x40) + (word_t)(uint8_t)tag;
    if ((tag < 8 && (*(uint32_t *)(ctx + 0x50) & 0x100000) == 0) &&
        (base & nottag) + *(long *)(ctx2 + 0x40) < 0x19) {
        void (*meth)(void) = *(void (**)(void))(ctx + 0x10);
        sk_ctx_fetch();             /* FUN_0034bf1c */
        meth();
        (*(void (**)(word_t, word_t, word_t))(ctx + 0x10))
            (base + (long)dst & nottag, base + (long)src & nottag, val);
    } else {
        long v = *src;
        *dst = v;
        dst = (long *)(v + (tag + 0x10 & nottag));
        sk_retain(dst);             /* FUN_0036b270 */
    }
    sk_cpu_exit((void *)dst);       /* FUN_00084234 */
}

/*--------------------------------------------------------------------*/
/* FUN_003413f0 @ 0x003413f0   (est. sk_cap_op_dispatch8c)
 * Ghidra: void FUN_003413f0(long param_1, long param_2)
 * Dispatches a cap op through the method slot at +8 twice; indirect jump table
 * at 0x00341470 prevents full control-flow recovery.
 * Confidence: low.
 * Notes: callees FUN_0034b518; jumptable warning at 0x00341470.
 */
void sk_cap_op_dispatch8c(long p1, long p2)
{
    void *ctx;                      /* extraout_x16 */
    word_t val = *(word_t *)(p2 + 0x10);
    void (*meth)(void) = *(void (**)(void))(ctx + 8);

    sk_ctx_fetch();                 /* FUN_0034b518 */
    meth();
    /* WARNING: jumptable at 0x00341470 (too many branches) */
    (*(void (**)(word_t, word_t))(ctx + 8))
        (*(long *)(ctx + 0x40) + p1 + (word_t)*(uint8_t *)(ctx + 0x50) &
         ~(word_t)*(uint8_t *)(ctx + 0x50), val);
}

/*--------------------------------------------------------------------*/
/* FUN_003414e4 @ 0x003414e4   (est. sk_cap_op_method18c)
 * Ghidra: void FUN_003414e4(undefined8, undefined8, long param_3)
 * Dispatches a cap op through the method slot +0x18 with the validated object
 * path (param_3+0x10), then a helper on the context.
 * Confidence: low.
 * Notes: callees FUN_003504d0 / FUN_0034b3c8 / FUN_0034e8b8.
 */
void sk_cap_op_method18c(unsigned long p1, unsigned long p2, unsigned long p3)
{
    void *ctx;                      /* extraout_x16 */
    word_t val = *(word_t *)(p3 + 0x10);

    sk_state_enter();               /* FUN_003504d0 */
    cl4_result_t r = sk_ctx_fetch_pair();       /* FUN_0034b3c8 */
    (*(void (**)(word_t, word_t, word_t))(ctx + 0x18))(r.lo, r.hi, val);
    sk_ctx_fetch();                 /* FUN_0034e8b8(*(ctx+0x40)) */
    (*(void (**)(void))(ctx + 0x18))();
}

/*--------------------------------------------------------------------*/
/* FUN_00341554 @ 0x00341554   (est. sk_cap_op_method20c)
 * Ghidra: void FUN_00341554(undefined8, undefined8, long param_3)
 * Same template as sk_cap_op_method18c but method slot +0x20.
 * Confidence: low.
 */
void sk_cap_op_method20c(unsigned long p1, unsigned long p2, unsigned long p3)
{
    void *ctx;                      /* extraout_x16 */
    word_t val = *(word_t *)(p3 + 0x10);

    sk_state_enter();               /* FUN_003504d0 */
    cl4_result_t r = sk_ctx_fetch_pair();       /* FUN_0034b3c8 */
    (*(void (**)(word_t, word_t, word_t))(ctx + 0x20))(r.lo, r.hi, val);
    sk_ctx_fetch();                 /* FUN_0034e8b8(*(ctx+0x40)) */
    (*(void (**)(void))(ctx + 0x20))();
}

/*--------------------------------------------------------------------*/
/* FUN_003415c4 @ 0x003415c4   (est. sk_cap_op_method28c)
 * Ghidra: void FUN_003415c4(undefined8, undefined8, long param_3)
 * Same template as sk_cap_op_method18c but method slot +0x28.
 * Confidence: low.
 */
void sk_cap_op_method28c(unsigned long p1, unsigned long p2, unsigned long p3)
{
    void *ctx;                      /* extraout_x16 */
    word_t val = *(word_t *)(p3 + 0x10);

    sk_state_enter();               /* FUN_003504d0 */
    cl4_result_t r = sk_ctx_fetch_pair();       /* FUN_0034b3c8 */
    (*(void (**)(word_t, word_t, word_t))(ctx + 0x28))(r.lo, r.hi, val);
    sk_ctx_fetch();                 /* FUN_0034e8b8(*(ctx+0x40)) */
    (*(void (**)(void))(ctx + 0x28))();
}

/*--------------------------------------------------------------------*/
/* FUN_003416ec @ 0x003416ec   (est. sk_cap_lookup3)
 * Ghidra: undefined8 FUN_003416ec(void)
 * Capability lookup: reads a variable-length field at an offset and returns a
 * lookup result or a queue-completion result.
 * Confidence: low.
 * Notes: callees FUN_00355208 / FUN_00352f78 / FUN_000839f8.
 */
undefined8 sk_cap_lookup3(void)
{
    void *ctx;                      /* extraout_x8 */
    word_t w10 = 0;                 /* extraout_w10 */
    uint32_t v;
    cl4_result_t r;

    r = sk_ctx_fetch_pair();        /* FUN_00355208 */
    void *base = (void *)r.lo;
    if (w10 < 0x100) {
        if (w10 < 2) goto none;
        v = (uint32_t)*(uint8_t *)((char *)base + (long)ctx);
    } else if (w10 >> 0x10 == 0) {
        v = (uint32_t)*(uint16_t *)((char *)base + (long)ctx);
    } else {
        v = *(uint32_t *)((char *)base + (long)ctx);
    }
    if (v != 0) {
        return (undefined8)sk_ctx_fetch();      /* FUN_00352f78 */
    }
none:
    if (r.hi != 0) {
        return sk_queue_complete(0, 0);     /* FUN_000839f8 */
    }
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_00341924 @ 0x00341924   (est. sk_cap_ctl_nested)
 * Ghidra: void FUN_00341924(void)
 * Nested capability control: kernel-enter, lock-release, then a second
 * lock-release on the object path (0x13f) and when count < 0x40 runs the
 * housekeeping sequence.
 * Confidence: low.
 * Notes: callees FUN_0034c7c4 / FUN_00377dcc / FUN_003558b8 / FUN_0034d1c0 /
 *   FUN_003728b8 / FUN_00019858.
 */
void sk_cap_ctl_nested(void)
{
    void *ctx = 0;                  /* unaff_x19 */
    word_t n;

    sk_cpu_enter_kernel();          /* FUN_0034c7c4 */
    sk_lock_release(0);             /* FUN_00377dcc */
    n = 0;                          /* extraout_x1 */
    if (n < 0x40) {
        cl4_result_t r = { 0, 0 };  /* FUN_00377dcc(0x13f, *(ctx+0x18)) */
        n = r.hi;
        void *c = (void *)r.lo;
        if (n < 0x40) {
            sk_ctx_fetch();         /* FUN_003558b8(*(c-8) + 0x40) */
            sk_ctx_fetch();         /* FUN_0034d1c0 */
            sk_syscall_op(0, 0, 0); /* FUN_003728b8 */
            sk_try_acquire(0);      /* FUN_00019858 */
        }
    }
}

/*--------------------------------------------------------------------*/
/* FUN_003419b8 @ 0x003419b8   (est. sk_cap_op_path5)
 * Ghidra: long FUN_003419b8(void)
 * Syscall handler: validates the object path, and on the success branch
 * dispatches the method at lVar4+0x10 with aligned operands; else advances a
 * pointer and retains.
 * Confidence: low.
 * Notes: callees FUN_00350c5c / FUN_00356eb4 / FUN_0034df14 / FUN_00352778 /
 *   FUN_0036b270.
 */
long sk_cap_op_path5(void)
{
    void *ctx;                      /* extraout_x16 */
    void *ctx2;                     /* extraout_x9 */
    void *ctx3;                     /* extraout_x10 */
    long *dst = 0;                  /* unaff_x19 */
    long *src = 0;                  /* unaff_x20 */
    void *rec, *lrec;
    word_t tag, nottag;
    long base;

    sk_ctx_fetch();                 /* FUN_00350c5c */
    sk_ctx_fetch();                 /* FUN_00356eb4 */
    rec = (void *)*(long *)(ctx2 + 0x18);
    lrec = (void *)((char *)rec - 8);
    tag = *(uint32_t *)((char *)lrec + 0x50) & 0xff;
    base = *(long *)(ctx3 + 0x40) + (word_t)(uint8_t)tag;
    uint32_t t2 = *(uint32_t *)(ctx + 0x50) | tag;
    if (((t2 & 0xff) < 8 && (t2 & 0x100000) == 0) &&
        (base & ~(tag & 0xff)) + *(long *)((char *)lrec + 0x40) < 0x19) {
        nottag = ~(tag & 0xff);
        sk_ctx_fetch();             /* FUN_0034df14 */
        (*(void (**)(void))ctx2)();
        (*(void (**)(word_t, word_t, void *))((char *)lrec + 0x10))
            (base + (long)dst & nottag, base + (long)src & nottag, rec);
    } else {
        long base2 = 0;             /* FUN_00352778 */
        dst = (long *)(base2 + (0 + 0x10 & ~0));
        sk_retain(dst);             /* FUN_0036b270 */
    }
    return (long)dst;
}

/*--------------------------------------------------------------------*/
/* FUN_00341ad0 @ 0x00341ad0   (est. sk_cap_op_dispatch8d)
 * Ghidra: void FUN_00341ad0(void)
 * Dispatches a cap op through method slot +8 after resolving the object path;
 * indirect jump table at 0x00341b4c.
 * Confidence: low.
 * Notes: callees FUN_003504d0 / FUN_0034ece8; jumptable warning.
 */
void sk_cap_op_dispatch8d(void)
{
    void *ctx;                      /* extraout_x16 */
    void *dst = 0;                  /* unaff_x20 */
    void *ctx2 = 0;                 /* unaff_x19 */
    word_t tag;

    cl4_result_t p = sk_ctx_fetch_pair();       /* FUN_003504d0 */
    sk_ctx_fetch();                 /* FUN_0034ece8(p.lo, *(p.hi+0x10)) */
    (*(void (**)(void))(ctx + 8))();
    long base = *(long *)(*(long *)((char *)ctx2 + 0x18) + -8);
    tag = (word_t)*(uint8_t *)(base + 0x50);
    /* WARNING: jumptable at 0x00341b4c */
    (*(void (**)(word_t))(base + 8))
        (*(long *)(ctx + 0x40) + (long)dst + tag & ~tag);
}

/*--------------------------------------------------------------------*/
/* FUN_00341b54 @ 0x00341b54   (est. sk_cap_op_method10d)
 * Ghidra: void FUN_00341b54(void)
 * Dispatches through method slot +0x10, feeding the method result and the
 * context's +0x18 object into FUN_0034fbc4, then calls the method again with
 * aligned operands.
 * Confidence: low.
 * Notes: callees FUN_0034b430 / FUN_0034a054 / FUN_0034fbc4.
 */
void sk_cap_op_method10d(void)
{
    void *ctxA, *ctxB;              /* extraout_x16 / extraout_x16_00 */
    void *obj = 0;                  /* unaff_x19 */
    void *a = 0, *b = 0;            /* unaff_x21 / unaff_x20 */

    sk_ctx_fetch();                 /* FUN_0034b430 */
    sk_ctx_fetch();                 /* FUN_0034a054 */
    cl4_result_t r = (*(cl4_result_t (*)(void))(ctxA + 0x10))();
    sk_ctx_fetch();                 /* FUN_0034fbc4(*(ctxA+0x40), r.lo, r.hi, *(obj+0x18)) */
    word_t tag = (word_t)*(uint8_t *)(ctxB + 0x50);
    (*(void (**)(word_t, word_t))(ctxB + 0x10))
        (0 + tag + (long)b & ~tag, 0 + tag + (long)a & ~tag);
}

/*--------------------------------------------------------------------*/
/* FUN_00341bd8 @ 0x00341bd8   (est. sk_cap_op_method18d)
 * Ghidra: void FUN_00341bd8(void)
 * Same template as sk_cap_op_method10d but method slot +0x18.
 * Confidence: low.
 */
void sk_cap_op_method18d(void)
{
    void *ctxA, *ctxB;
    void *obj = 0;                  /* unaff_x19 */
    void *a = 0, *b = 0;

    sk_ctx_fetch();                 /* FUN_0034b430 */
    sk_ctx_fetch();                 /* FUN_0034a054 */
    cl4_result_t r = (*(cl4_result_t (*)(void))(ctxA + 0x18))();
    sk_ctx_fetch();                 /* FUN_0034fbc4(*(ctxA+0x40), r.lo, r.hi, *(obj+0x18)) */
    word_t tag = (word_t)*(uint8_t *)(ctxB + 0x50);
    (*(void (**)(word_t, word_t))(ctxB + 0x18))
        (0 + tag + (long)b & ~tag, 0 + tag + (long)a & ~tag);
}

/*--------------------------------------------------------------------*/
/* FUN_00341c5c @ 0x00341c5c   (est. sk_cap_op_method20d)
 * Ghidra: void FUN_00341c5c(void)
 * Same template as sk_cap_op_method10d but method slot +0x20.
 * Confidence: low.
 */
void sk_cap_op_method20d(void)
{
    void *ctxA, *ctxB;
    void *obj = 0;                  /* unaff_x19 */
    void *a = 0, *b = 0;

    sk_ctx_fetch();                 /* FUN_0034b430 */
    sk_ctx_fetch();                 /* FUN_0034a054 */
    cl4_result_t r = (*(cl4_result_t (*)(void))(ctxA + 0x20))();
    sk_ctx_fetch();                 /* FUN_0034fbc4(*(ctxA+0x40), r.lo, r.hi, *(obj+0x18)) */
    word_t tag = (word_t)*(uint8_t *)(ctxB + 0x50);
    (*(void (**)(word_t, word_t))(ctxB + 0x20))
        (0 + tag + (long)b & ~tag, 0 + tag + (long)a & ~tag);
}

/*--------------------------------------------------------------------*/
/* FUN_00341ce0 @ 0x00341ce0   (est. sk_cap_op_method28d)
 * Ghidra: void FUN_00341ce0(void)
 * Same template as sk_cap_op_method10d but method slot +0x28.
 * Confidence: low.
 */
void sk_cap_op_method28d(void)
{
    void *ctxA, *ctxB;
    void *obj = 0;                  /* unaff_x19 */
    void *a = 0, *b = 0;

    sk_ctx_fetch();                 /* FUN_0034b430 */
    sk_ctx_fetch();                 /* FUN_0034a054 */
    cl4_result_t r = (*(cl4_result_t (*)(void))(ctxA + 0x28))();
    sk_ctx_fetch();                 /* FUN_0034fbc4(*(ctxA+0x40), r.lo, r.hi, *(obj+0x18)) */
    word_t tag = (word_t)*(uint8_t *)(ctxB + 0x50);
    (*(void (**)(word_t, word_t))(ctxB + 0x28))
        (0 + tag + (long)b & ~tag, 0 + tag + (long)a & ~tag);
}

/*--------------------------------------------------------------------*/
/* FUN_00341f10 @ 0x00341f10   (est. sk_cap_resize_field)
 * Ghidra: void FUN_00341f10(ushort *param_1, uint param_2, uint param_3, long param_4)
 * Capability resize: reads two object sizes, computes a new size delta, and
 * writes a variable-length field (1-4 byte payload) into param_1. Includes a
 * software-breakpoint path on an invalid size class.
 * Confidence: low (register aliasing; complex shift/width logic).
 * Notes: callees FUN_0009461c / FUN_00114330 / FUN_0034e2a8 / FUN_0035667c.
 */
void sk_cap_resize_field(unsigned short *buf, unsigned int param_2, unsigned int param_3, long param_4)
{
    void *ra;                       /* param_4+0x10 */
    void *rb;                       /* param_4+0x18 */
    void *lrec;
    uint32_t curA, curB, maxsz;
    word_t tag;
    long base, off;
    uint32_t pos, sh;
    uint32_t delta;
    uint8_t width;
    uint32_t w;

    ra = (void *)*(long *)(param_4 + 0x10);
    rb = (void *)*(long *)(param_4 + 0x18);
    lrec = (void *)((char *)rb - 8);
    curA = *(uint32_t *)(*(long *)((char *)ra + -8) + 0x54);
    curB = *(uint32_t *)((char *)lrec + 0x54);
    maxsz = curB;
    if (curB <= curA) {
        maxsz = curA;
    }
    tag = (word_t)*(uint8_t *)((char *)lrec + 0x50);
    base = *(long *)(*(long *)((char *)ra + -8) + 0x40) + tag;
    off = (base & ~tag) + *(long *)((char *)lrec + 0x40);
    pos = (uint32_t)off;
    sh = pos << 3;
    if (param_3 < maxsz || param_3 - maxsz == 0) {
        width = 0;
    } else if (pos < 4) {
        uint32_t x = ((param_3 - maxsz) + ~(-1 << (sh & 0x1f)) >> (sh & 0x1f)) + 1;
        width = 2;
        if (0xffff < x) {
            width = 4;
        }
        if (x < 0x100) {
            width = (1 < x);
        }
    } else {
        width = 1;
    }
    if (maxsz < param_2) {
        delta = param_2 + ~maxsz;
        if (pos < 4) {
            w = (delta >> (sh & 0x1f)) + 1;
            if (pos != 0) {
                sk_ctx_fetch();     /* FUN_0009461c */
                sk_obj_meta(0);     /* FUN_00114330 */
                if (pos == 3) {
                    sk_ctx_fetch(); /* FUN_0034e2a8 */
                } else if (pos == 2) {
                    *buf = (unsigned short)delta & ((unsigned short)(-1 << (sh & 0x1f)) ^ 0xffff);
                } else {
                    *(char *)buf = (char)delta;
                }
            }
        } else {
            sk_ctx_fetch();         /* FUN_0009461c */
            sk_obj_meta(0);         /* FUN_00114330 */
            sk_ctx_fetch();         /* FUN_0035667c */
        }
    }
}

/*--------------------------------------------------------------------*/
/* FUN_00342190 @ 0x00342190   (est. sk_panic_ctl_d)
 * Ghidra: void FUN_00342190(void)
 * Same template as sk_panic_ctl_a (enter, release, threshold 0x40, housekeeping).
 * Confidence: low.
 * Notes: FUN_0034c7c4 / FUN_00377dcc / FUN_00353424 / FUN_0034d034 /
 *   FUN_003728b8 / FUN_00019858.
 */
void sk_panic_ctl_d(void)
{
    void *ctx;
    word_t n;

    sk_cpu_enter_kernel();          /* FUN_0034c7c4 */
    cl4_result_t r = { 0, 0 };      /* FUN_00377dcc */
    n = r.hi; ctx = (void *)r.lo;
    if (n < 0x40) {
        sk_ctx_fetch();             /* FUN_00353424(*(ctx-8) + 0x40) */
        sk_ctx_fetch();             /* FUN_0034d034 */
        sk_syscall_op(0, 0, 0);     /* FUN_003728b8 */
        sk_try_acquire(0);          /* FUN_00019858 */
    }
}

/*--------------------------------------------------------------------*/
/* FUN_003421f4 @ 0x003421f4   (est. sk_ctl_alloc1)
 * Ghidra: void FUN_003421f4(void)
 * Kernel-enter, lock-release, and when the count is < 0x40 allocate an object
 * (type 1) and run a syscall op with selector 1.
 * Confidence: low.
 * Notes: FUN_0034c7c4 / FUN_00377dcc / FUN_0034c16c / FUN_003728b8 /
 *   FUN_00019858.
 */
void sk_ctl_alloc1(void)
{
    word_t n;

    sk_cpu_enter_kernel();          /* FUN_0034c7c4 */
    sk_lock_release(0);             /* FUN_00377dcc */
    n = 0;                          /* extraout_x1 */
    if (n < 0x40) {
        cl4_result_t obj = sk_object_alloc2();  /* FUN_0034c16c */
        sk_syscall_op(obj.lo, obj.hi, 1);       /* FUN_003728b8 */
        sk_try_acquire(0);          /* FUN_00019858 */
    }
}

/*--------------------------------------------------------------------*/
/* FUN_00342258 @ 0x00342258   (est. sk_cap_op_dispatch)
 * Ghidra: long FUN_00342258(void)
 * Dispatches a cap op: on the success branch (flags + size < 0x19) runs the
 * method sequence; else advances a pointer and retains.
 * Confidence: low.
 * Notes: callees FUN_00349d3c / FUN_0035944c / FUN_00352c04 / FUN_0035556c /
 *   FUN_0036b270.
 */
long sk_cap_op_dispatch(void)
{
    void *ctx;                      /* extraout_x16 */
    void *ctx2;                     /* extraout_x9 */
    long *dst = 0;                  /* unaff_x19 */
    word_t size;                    /* extraout_x10 */
    int w11;                        /* extraout_w11 */
    bool zf, cy;                    /* in_ZR / in_CY */

    sk_ctx_fetch();                 /* FUN_00349d3c */
    sk_ctx_fetch();                 /* FUN_0035944c */
    if ((!cy || zf) && size < 0x19 && w11 == 0) {
        sk_ctx_fetch();             /* FUN_00352c04 */
        (*(void (**)(void))ctx2)();
    } else {
        long base = 0;              /* FUN_0035556c */
        dst = (long *)(base + (0 + 0x10 & ~0));
        sk_retain(dst);             /* FUN_0036b270 */
    }
    return (long)dst;
}

/*--------------------------------------------------------------------*/
/* FUN_00342334 @ 0x00342334   (est. sk_cap_op_method18e)
 * Ghidra: undefined8 FUN_00342334(undefined8 param_1)
 * Dispatches through method slot +0x18 and returns param_1.
 * Confidence: low.
 * Notes: FUN_0034a054.
 */
undefined8 sk_cap_op_method18e(undefined8 p1)
{
    void *ctx;                      /* extraout_x16 */

    sk_ctx_fetch();                 /* FUN_0034a054 */
    (*(void (**)(void))(ctx + 0x18))();
    return p1;
}

/*--------------------------------------------------------------------*/
/* FUN_00342370 @ 0x00342370   (est. sk_cap_op_method20e)
 * Ghidra: undefined8 FUN_00342370(undefined8 param_1)
 * Dispatches through method slot +0x20 and returns param_1.
 * Confidence: low.
 * Notes: FUN_0034a054.
 */
undefined8 sk_cap_op_method20e(undefined8 p1)
{
    void *ctx;                      /* extraout_x16 */

    sk_ctx_fetch();                 /* FUN_0034a054 */
    (*(void (**)(void))(ctx + 0x20))();
    return p1;
}

/*--------------------------------------------------------------------*/
/* FUN_003423ac @ 0x003423ac   (est. sk_cap_op_method28e)
 * Ghidra: undefined8 FUN_003423ac(undefined8 param_1)
 * Dispatches through method slot +0x28 and returns param_1.
 * Confidence: low.
 * Notes: FUN_0034a054.
 */
undefined8 sk_cap_op_method28e(undefined8 p1)
{
    void *ctx;                      /* extraout_x16 */

    sk_ctx_fetch();                 /* FUN_0034a054 */
    (*(void (**)(void))(ctx + 0x28))();
    return p1;
}

/*--------------------------------------------------------------------*/
/* FUN_003426d8 @ 0x003426d8   (est. sk_ctx_double_retain2)
 * Ghidra: void FUN_003426d8(void)
 * Retains the fetched context twice.
 * Confidence: low.
 * Notes: FUN_00358c38 / FUN_0036b270.
 */
void sk_ctx_double_retain2(void)
{
    sk_ctx_fetch();                 /* FUN_00358c38 */
    sk_retain(0);                   /* thunk_FUN_0036b270 */
    sk_retain(0);                   /* thunk_FUN_0036b270 */
}

/*--------------------------------------------------------------------*/
/* FUN_00342708 @ 0x00342708   (est. sk_cap_swap8b)
 * Ghidra: void FUN_00342708(void)
 * Swaps the +8 field between contexts, retaining new / releasing old metadata.
 * Confidence: low.
 * Notes: FUN_0034b044 / FUN_0036b270 / FUN_003a25d4.
 */
void sk_cap_swap8b(void)
{
    void *src = 0;                  /* unaff_x19 */
    void *dst = 0;                  /* unaff_x20 */
    word_t old;

    sk_ctx_fetch();                 /* FUN_0034b044 */
    sk_retain(0);                   /* thunk_FUN_0036b270 */
    sk_obj_meta(0);                 /* FUN_003a25d4 */
    old = *(word_t *)((char *)dst + 8);
    *(word_t *)((char *)dst + 8) = *(word_t *)((char *)src + 8);
    sk_retain(dst);                 /* thunk_FUN_0036b270 */
    sk_obj_meta(old);               /* FUN_003a25d4 */
}

/*--------------------------------------------------------------------*/
/* FUN_00342758 @ 0x00342758   (est. sk_cap_swap_pair)
 * Ghidra: void FUN_00342758(void)
 * Calls a helper with the fetched record's first word, swaps the two-word
 * record between contexts, then calls a method with the old word.
 * Confidence: low.
 * Notes: FUN_0034ee78.
 */
void sk_cap_swap_pair(void)
{
    void (*methA)(word_t) = 0;      /* unaff_x19 */
    void (*methB)(word_t) = 0;      /* in_x3 */
    undefined8 *dst = 0;            /* unaff_x21 */
    undefined8 *src = 0;            /* unaff_x20 */
    word_t old;

    undefined8 *rec = (undefined8 *)sk_ctx_fetch();    /* FUN_0034ee78 */
    methB(*rec);
    old = dst[1];
    dst[1] = src[1];
    dst[0] = src[0];
    methA(old);
}

/*--------------------------------------------------------------------*/
/* FUN_003427f4 @ 0x003427f4   (est. sk_cap_copy_10)
 * Ghidra: void FUN_003427f4(void)
 * Copies the +0x10/+0x18 fields from the fetched context, retaining.
 * Confidence: low.
 * Notes: FUN_00355938 / FUN_0036b270.
 */
void sk_cap_copy_10(void)
{
    void *ctx = 0;                  /* unaff_x19 */

    sk_obj_read();                  /* FUN_00355938 */
    *(word_t *)(ctx + 0x10) = *(word_t *)(0 + 0x10);
    *(uint8_t *)(ctx + 0x18) = *(uint8_t *)(0 + 0x18);
    sk_retain(ctx);                 /* thunk_FUN_0036b270 */
}

/*--------------------------------------------------------------------*/
/* FUN_00342830 @ 0x00342830   (est. sk_cap_copy_10b)
 * Ghidra: void FUN_00342830(void)
 * Copies the +0x10/+0x18 fields between contexts after the enter/retain/meta
 * sequence.
 * Confidence: low.
 * Notes: FUN_0034b264 / FUN_00352028 / FUN_0036b270 / FUN_003a25d4.
 */
void sk_cap_copy_10b(void)
{
    void *src = 0;                  /* unaff_x19 */
    void *dst = 0;                  /* unaff_x20 */
    word_t v;

    sk_state_enter2();              /* FUN_0034b264 */
    sk_state_enter2();              /* FUN_00352028 */
    sk_retain(0);                   /* thunk_FUN_0036b270 */
    sk_obj_meta(0);                 /* FUN_003a25d4 */
    v = *(word_t *)((char *)src + 0x10);
    *(uint8_t *)((char *)dst + 0x18) = *(uint8_t *)((char *)src + 0x18);
    *(word_t *)((char *)dst + 0x10) = v;
}

/*--------------------------------------------------------------------*/
/* FUN_00342880 @ 0x00342880   (est. sk_cap_copy_10c)
 * Ghidra: void FUN_00342880(void)
 * Copies the +0x10/+0x18 fields between contexts after the state-enter helpers.
 * Confidence: low.
 * Notes: FUN_003504d0 / FUN_00359124.
 */
void sk_cap_copy_10c(void)
{
    void *src = 0;                  /* unaff_x19 */
    void *dst = 0;                  /* unaff_x20 */

    sk_state_enter();               /* FUN_003504d0 */
    sk_ctx_fetch_pair();            /* FUN_00359124 */
    *(word_t *)((char *)dst + 0x10) = *(word_t *)((char *)src + 0x10);
    *(uint8_t *)((char *)dst + 0x18) = *(uint8_t *)((char *)src + 0x18);
}

/*--------------------------------------------------------------------*/
/* FUN_00342950 @ 0x00342950   (est. sk_ctx_seq3)
 * Ghidra: void FUN_00342950(void)
 * Runs three fixed context helpers.
 * Confidence: low.
 * Notes: FUN_00354e6c / FUN_00348990 / FUN_00356518.
 */
void sk_ctx_seq3(void)
{
    sk_ctx_fetch();                 /* FUN_00354e6c */
    sk_ctx_fetch();                 /* FUN_00348990 */
    sk_ctx_fetch();                 /* FUN_00356518 */
}

/*--------------------------------------------------------------------*/
/* FUN_00342984 @ 0x00342984   (est. sk_ctx_set8)
 * Ghidra: void FUN_00342984(void)
 * Stores a fetched reference value into the +8 field of the record.
 * Confidence: low.
 * Notes: FUN_0034b1c0 / FUN_00376820.
 */
void sk_ctx_set8(void)
{
    void *ctx = 0;                  /* unaff_x19 */

    sk_ctx_fetch();                 /* FUN_0034b1c0 */
    (void)sk_ref_release(0, 0);    /* FUN_00376820; value -> ctx+8 */
    *(word_t *)(ctx + 8) = 0;
}

/*--------------------------------------------------------------------*/
/* FUN_003429ac @ 0x003429ac   (est. sk_ctx_ref_ops)
 * Ghidra: void FUN_003429ac(undefined8 param_1)
 * Runs a sequence of reference helpers ending with a two-arg ref release.
 * Confidence: low.
 * Notes: FUN_00348eb4 / FUN_00376820 / FUN_00348ad8.
 */
void sk_ctx_ref_ops(undefined8 p1)
{
    sk_ctx_fetch();                 /* FUN_00348eb4 */
    sk_ref_release(0, 0);           /* FUN_00376820 */
    undefined8 v = (undefined8)sk_ctx_fetch();  /* FUN_00348ad8 */
    sk_ref_release(v, p1);          /* FUN_00376820 */
}

/*--------------------------------------------------------------------*/
/* FUN_003429ec @ 0x003429ec   (est. sk_ctx_store8)
 * Ghidra: void FUN_003429ec(void)
 * Stores a fetched reference value into the +8 field of the record.
 * Confidence: low.
 * Notes: FUN_00354e6c.
 */
void sk_ctx_store8(void)
{
    void *ctx = 0;                  /* unaff_x19 */

    *(word_t *)(ctx + 8) = (word_t)sk_ctx_fetch();      /* FUN_00354e6c */
}

/*--------------------------------------------------------------------*/
/* FUN_00342a10 @ 0x00342a10   (est. sk_ctx_set8_2)
 * Ghidra: void FUN_00342a10(long param_1)
 * Stores the result of the local thunk FUN_00342a38 into param_1+8.
 * Confidence: low.
 */
void sk_ctx_set8_2(long rec)
{
    *(word_t *)(rec + 8) = sk_ctx_thunk_6574f0();   /* FUN_00342a38 */
}

/*--------------------------------------------------------------------*/
/* FUN_00342a38 @ 0x00342a38   (est. sk_ctx_thunk_6574f0)
 * Ghidra: void FUN_00342a38(void)
 * Writes a constant instruction word (0x911ff21090000010) into the global
 * dispatch-table slot at 0x6574f0. Truncated thunk (unreachable block removed).
 * Confidence: low.
 * Notes: writes uRam@0x6574f0.
 */
word_t sk_ctx_thunk_6574f0(void)
{
    /* uRam@0x6574f0 = 0x911ff21090000010; (dispatch slot init) */
    return 0x911ff21090000010ull;
}

/*--------------------------------------------------------------------*/
/* FUN_00342a8c @ 0x00342a8c   (est. sk_ctx_set8_3)
 * Ghidra: void FUN_00342a8c(long param_1)
 * Stores the result of the local thunk FUN_00342ab4 into param_1+8.
 * Confidence: low.
 */
void sk_ctx_set8_3(long rec)
{
    *(word_t *)(rec + 8) = sk_ctx_thunk_6574f8();   /* FUN_00342ab4 */
}

/*--------------------------------------------------------------------*/
/* FUN_00342ab4 @ 0x00342ab4   (est. sk_ctx_thunk_6574f8)
 * Ghidra: void FUN_00342ab4(void)
 * Writes a constant instruction word (0xdac10230d29aa0f1) into the global slot
 * at 0x6574f8. Truncated thunk.
 * Confidence: low.
 */
word_t sk_ctx_thunk_6574f8(void)
{
    /* uRam@0x6574f8 = 0xdac10230d29aa0f1; */
    return 0xdac10230d29aa0f1ull;
}

/*--------------------------------------------------------------------*/
/* FUN_00342b10 @ 0x00342b10   (est. sk_ctx_thunk_657500)
 * Ghidra: void FUN_00342b10(void)
 * Writes a constant instruction word (0x39050028f900b830) into the global slot
 * at 0x657500. Truncated thunk.
 * Confidence: low.
 */
word_t sk_ctx_thunk_657500(void)
{
    /* uRam@0x657500 = 0x39050028f900b830; */
    return 0x39050028f900b830ull;
}

/*--------------------------------------------------------------------*/
/* FUN_00342b68 @ 0x00342b68   (est. sk_ctx_thunk_657508)
 * Ghidra: void FUN_00342b68(void)
 * Writes a constant instruction word (0xb9014429528000a9) into the global slot
 * at 0x657508. Truncated thunk.
 * Confidence: low.
 */
word_t sk_ctx_thunk_657508(void)
{
    /* uRam@0x657508 = 0xb9014429528000a9; */
    return 0xb9014429528000a9ull;
}

/*--------------------------------------------------------------------*/
/* FUN_00342bd0 @ 0x00342bd0   (est. sk_dispatch_slot_init_a)
 * Ghidra: void FUN_00342bd0(void)
 * Initializes the global dispatch slot 0x657510 with a ref (FUN_00376820 on
 * DAT_004f11a0 / 0x6792c0).
 * Confidence: low.
 */
void sk_dispatch_slot_init_a(void)
{
    /* uRam@0x657510 = FUN_00376820(&DAT_004f11a0, 0x6792c0); */
    sk_ref_release(0, 0);           /* FUN_00376820(&DAT_004f11a0, 0x6792c0) */
}

/*--------------------------------------------------------------------*/
/* FUN_00342bd4 @ 0x00342bd4   (est. sk_dispatch_slot_init_b)
 * Ghidra: void FUN_00342bd4(void)
 * Identical to sk_dispatch_slot_init_a.
 * Confidence: low.
 */
void sk_dispatch_slot_init_b(void)
{
    sk_ref_release(0, 0);           /* FUN_00376820(&DAT_004f11a0, 0x6792c0) */
}

/*--------------------------------------------------------------------*/
/* FUN_00342c28 @ 0x00342c28   (est. sk_dispatch_slot_init_c)
 * Ghidra: void FUN_00342c28(void)
 * Initializes the global dispatch slot 0x657518: resolves a name (0x657520) and
 * the local thunk FUN_00342c9c, then stores a ref via FUN_00376820.
 * Confidence: low.
 * Notes: FUN_00027614(0x657520, &DAT_004f1260); FUN_00342c9c (local);
 *   uRam@0x657518 = FUN_00376820(&DAT_004eb028, ...).
 */
void sk_dispatch_slot_init_c(void)
{
    undefined8 v = sk_try_acquire(0);   /* FUN_00027614(0x657520, &DAT_004f1260) */
    word_t t = sk_ctx_thunk_657528();   /* FUN_00342c9c */
    (void)v; (void)t;
    sk_ref_release(0, 0);           /* FUN_00376820(&DAT_004eb028, ...) */
}

/*--------------------------------------------------------------------*/
/* FUN_00342c9c @ 0x00342c9c   (est. sk_ctx_thunk_657528)
 * Ghidra: void FUN_00342c9c(void)
 * Writes a constant instruction word (0xa91828299128814a) into the global slot
 * at 0x657528. Truncated thunk.
 * Confidence: low.
 */
word_t sk_ctx_thunk_657528(void)
{
    /* uRam@0x657528 = 0xa91828299128814a; */
    return 0xa91828299128814aull;
}

/*--------------------------------------------------------------------*/
/* FUN_00342cf0 @ 0x00342cf0   (est. sk_ctx_set8_4)
 * Ghidra: void FUN_00342cf0(long param_1)
 * Stores the result of the local thunk FUN_00342d18 into param_1+8.
 * Confidence: low.
 */
void sk_ctx_set8_4(long rec)
{
    *(word_t *)(rec + 8) = 0;       /* FUN_00342d18 */
}

/*--------------------------------------------------------------------*/
/* FUN_00342d18 @ 0x00342d18   (est. sk_ctx_thunk_657530)
 * Ghidra: void FUN_00342d18(void)
 * Writes a constant instruction word (0x91252129b00002e9) into the global slot
 * at 0x657530. Truncated thunk.
 * Confidence: low.
 */
word_t sk_ctx_thunk_657530(void)
{
    /* uRam@0x657530 = 0x91252129b00002e9; */
    return 0x91252129b00002e9ull;
}

/*--------------------------------------------------------------------*/
/* FUN_00342d80 @ 0x00342d80   (est. sk_dispatch_slot_init_d)
 * Ghidra: void FUN_00342d80(void)
 * Initializes global dispatch slot 0x657538 via FUN_00376820 after resolving
 * a name (0x657520) and the local thunk FUN_00342b10.
 * Confidence: low.
 * Notes: FUN_00027614(0x657520, &DAT_004f1260); uRam@0x657538 =
 *   FUN_00376820(&DAT_004eb078, ...).
 */
void sk_dispatch_slot_init_d(void)
{
    sk_try_acquire(0);              /* FUN_00027614(0x657520, &DAT_004f1260) */
    sk_ctx_thunk_657500();          /* FUN_00342b10 */
    sk_ref_release(0, 0);           /* FUN_00376820(&DAT_004eb078, ...) */
}

/*--------------------------------------------------------------------*/
/* FUN_00342df4 @ 0x00342df4   (est. sk_ctx_set8_5)
 * Ghidra: void FUN_00342df4(long param_1)
 * Stores the local thunk FUN_00342c9c result into param_1+8.
 * Confidence: low.
 */
void sk_ctx_set8_5(long rec)
{
    *(word_t *)(rec + 8) = sk_ctx_thunk_657528();   /* FUN_00342c9c */
}

/*--------------------------------------------------------------------*/
/* FUN_00342e50 @ 0x00342e50   (est. sk_ctx_thunk_657540)
 * Ghidra: void FUN_00342e50(void)
 * Stores a function pointer (SUB_dac10230d294a3f1) into the global slot at
 * 0x657540. Truncated thunk.
 * Confidence: low.
 */
word_t sk_ctx_thunk_657540(void)
{
    /* puRam@0x657540 = &SUB_dac10230d294a3f1; */
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_00342eb8 @ 0x00342eb8   (est. sk_dispatch_slot_init_e)
 * Ghidra: void FUN_00342eb8(void)
 * Initializes global dispatch slot 0x657548 via FUN_00376820 after resolving
 * a name (0x657550) and the local thunk FUN_00342f2c.
 * Confidence: low.
 * Notes: FUN_00027614(0x657550, &DAT_004f1428); uRam@0x657548.
 */
void sk_dispatch_slot_init_e(void)
{
    sk_try_acquire(0);              /* FUN_00027614(0x657550, &DAT_004f1428) */
    sk_ctx_thunk_657558();          /* FUN_00342f2c */
    sk_ref_release(0, 0);           /* FUN_00376820(&DAT_004eb028, ...) */
}

/*--------------------------------------------------------------------*/
/* FUN_00342f2c @ 0x00342f2c   (est. sk_ctx_thunk_657558)
 * Ghidra: void FUN_00342f2c(void)
 * Writes a constant instruction word (0xf900d030dac10230) into the global slot
 * at 0x657558. Truncated thunk.
 * Confidence: low.
 */
word_t sk_ctx_thunk_657558(void)
{
    /* uRam@0x657558 = 0xf900d030dac10230; */
    return 0xf900d030dac10230ull;
}

/*--------------------------------------------------------------------*/
/* FUN_00342f80 @ 0x00342f80   (est. sk_ctx_set8_6)
 * Ghidra: void FUN_00342f80(long param_1)
 * Stores the local thunk FUN_00342fa8 result into param_1+8.
 * Confidence: low.
 */
void sk_ctx_set8_6(long rec)
{
    *(word_t *)(rec + 8) = sk_ctx_thunk_657560();   /* FUN_00342fa8 */
}

/*--------------------------------------------------------------------*/
/* FUN_00342fa8 @ 0x00342fa8   (est. sk_ctx_thunk_657560)
 * Ghidra: void FUN_00342fa8(void)
 * Writes a constant instruction word (0xf900d8283906a028) into the global slot
 * at 0x657560. Truncated thunk.
 * Confidence: low.
 */
word_t sk_ctx_thunk_657560(void)
{
    /* uRam@0x657560 = 0xf900d8283906a028; */
    return 0xf900d8283906a028ull;
}

/*--------------------------------------------------------------------*/
/* FUN_00343010 @ 0x00343010   (est. sk_dispatch_slot_init_f)
 * Ghidra: void FUN_00343010(void)
 * Initializes global dispatch slot 0x657568 via FUN_00376820 after resolving
 * a name (0x657550) and the local thunk FUN_00342e50.
 * Confidence: low.
 * Notes: uRam@0x657568 = FUN_00376820(&DAT_004eb078, ...).
 */
void sk_dispatch_slot_init_f(void)
{
    sk_try_acquire(0);              /* FUN_00027614(0x657550, &DAT_004f1428) */
    sk_ctx_thunk_657540();          /* FUN_00342e50 */
    sk_ref_release(0, 0);           /* FUN_00376820(&DAT_004eb078, ...) */
}

/*--------------------------------------------------------------------*/
/* FUN_00343084 @ 0x00343084   (est. sk_ctx_set8_7)
 * Ghidra: void FUN_00343084(long param_1)
 * Stores the local thunk FUN_00342f2c result into param_1+8.
 * Confidence: low.
 */
void sk_ctx_set8_7(long rec)
{
    *(word_t *)(rec + 8) = sk_ctx_thunk_657558();   /* FUN_00342f2c */
}

/*--------------------------------------------------------------------*/
/* FUN_003430dc @ 0x003430dc   (est. sk_obj_field_c)
 * Ghidra: long FUN_003430dc(ulong param_1)
 * Tagged-pointer object field accessor: if the tag bit (bit 0) is set,
 * dereferences the pointer at (param_1 & ~1); returns
 * (obj + 0xc) + *(int *)(obj + 0xc) — an offset-relative field location.
 * Confidence: medium (self-contained seL4 object field accessor).
 */
long sk_obj_field_c(ulong p)
{
    if ((p & 1) != 0) {
        p = *(ulong *)(p & 0xfffffffffffffffeull);
    }
    return (long)(p + 0xc) + (long)*(int *)(p + 0xc);
}

/*--------------------------------------------------------------------*/
/* FUN_0034310c @ 0x0034310c   (est. sk_obj_field_8)
 * Ghidra: long FUN_0034310c(ulong param_1)
 * Tagged-pointer object field accessor at offset +8.
 * Confidence: medium.
 */
long sk_obj_field_8(ulong p)
{
    if ((p & 1) != 0) {
        p = *(ulong *)(p & 0xfffffffffffffffeull);
    }
    return (long)(p + 8) + (long)*(int *)(p + 8);
}

/*--------------------------------------------------------------------*/
/* FUN_0034313c @ 0x0034313c   (est. sk_lazy_init_679340)
 * Ghidra: void FUN_0034313c(void)
 * Lazily initializes global DAT_006575b0 via FUN_00376820 if not already set.
 * Confidence: medium.
 * Notes: DAT_006575b0 = FUN_00376820(&DAT_004f1208, 0x679340).
 */
void sk_lazy_init_679340(void)
{
    if (DAT_006575b0 != 0) {
        return;
    }
    (void)sk_ref_release(0, 0);    /* FUN_00376820(&DAT_004f1208, 0x679340) */
    (void)DAT_006575b0;  /* dispatch slot holds the result */
}

/*--------------------------------------------------------------------*/
/* FUN_0034319c @ 0x0034319c   (est. sk_ctx_result5)
 * Ghidra: ulong FUN_0034319c(void)
 * Runs a fixed sequence (FUN_000a68f4 + FUN_0035037c + indirect) and returns a
 * 5-byte local value.
 * Confidence: low.
 */
ulong sk_ctx_result5(void)
{
    void *ctx = 0;                  /* unaff_x20 */
    void *f;

    sk_try_acquire(*(word_t *)((char *)ctx + 0x18));    /* FUN_000a68f4 */
    sk_ctx_fetch();                 /* FUN_0035037c */
    (*(void (**)(void))f)();        /* extraout_x9 */
    return 0;                       /* local_38 (5-byte) */
}

/*--------------------------------------------------------------------*/
/* FUN_003431f0 @ 0x003431f0   (est. sk_ctx_op_19cb68)
 * Ghidra: void FUN_003431f0(undefined8 param_1)
 * Calls FUN_0019cb68 with the context's +0x18 field, param_1, and +0x10 field.
 * Confidence: low.
 */
void sk_ctx_op_19cb68(undefined8 p1)
{
    void *ctx = 0;                  /* unaff_x20 */

    sk_ctx_fetch();                 /* FUN_0019cb68(*(ctx+0x18), p1, *(ctx+0x10)) */
}

/*--------------------------------------------------------------------*/
/* FUN_00343250 @ 0x00343250   (est. sk_obj_field_ac)
 * Ghidra: long FUN_00343250(ulong param_1)
 * Tagged-pointer object field accessor at offset +0xac.
 * Confidence: medium.
 */
long sk_obj_field_ac(ulong p)
{
    if ((p & 1) != 0) {
        p = *(ulong *)(p & 0xfffffffffffffffeull);
    }
    return (long)(p + 0xac) + (long)*(int *)(p + 0xac);
}

/*--------------------------------------------------------------------*/
/* FUN_00343640 @ 0x00343640   (est. sk_obj_field_a8)
 * Ghidra: long FUN_00343640(ulong param_1)
 * Tagged-pointer object field accessor at offset +0xa8.
 * Confidence: medium.
 */
long sk_obj_field_a8(ulong p)
{
    if ((p & 1) != 0) {
        p = *(ulong *)(p & 0xfffffffffffffffeull);
    }
    return (long)(p + 0xa8) + (long)*(int *)(p + 0xa8);
}

/*--------------------------------------------------------------------*/
/* FUN_00343a30 @ 0x00343a30   (est. sk_obj_field_10)
 * Ghidra: long FUN_00343a30(ulong param_1)
 * Tagged-pointer object field accessor at offset +0x10.
 * Confidence: medium.
 */
long sk_obj_field_10(ulong p)
{
    if ((p & 1) != 0) {
        p = *(ulong *)(p & 0xfffffffffffffffeull);
    }
    return (long)(p + 0x10) + (long)*(int *)(p + 0x10);
}

/*--------------------------------------------------------------------*/
/* FUN_00343a60 @ 0x00343a60   (est. sk_lazy_init_677740)
 * Ghidra: void FUN_00343a60(void)
 * Lazily initializes global DAT_006575c8 via FUN_00376820 if not already set.
 * Confidence: medium.
 * Notes: DAT_006575c8 = FUN_00376820(&DAT_004ed580, 0x677740).
 */
void sk_lazy_init_677740(void)
{
    if (DAT_006575c8 != 0) {
        return;
    }
    (void)sk_ref_release(0, 0);    /* FUN_00376820(&DAT_004ed580, 0x677740) */
    (void)DAT_006575c8;  /* dispatch slot holds the result */
}

/*--------------------------------------------------------------------*/
/* FUN_00343ab4 @ 0x00343ab4   (est. sk_lazy_init_6776a0)
 * Ghidra: void FUN_00343ab4(void)
 * Lazily initializes global DAT_006575d0 via FUN_00376820.
 * Confidence: medium.
 * Notes: DAT_006575d0 = FUN_00376820(&DAT_004ed270, 0x6776a0).
 */
void sk_lazy_init_6776a0(void)
{
    if (DAT_006575d0 != 0) {
        return;
    }
    (void)sk_ref_release(0, 0);    /* FUN_00376820(&DAT_004ed270, 0x6776a0) */
    (void)DAT_006575d0;  /* dispatch slot holds the result */
}

/*--------------------------------------------------------------------*/
/* FUN_00343b08 @ 0x00343b08   (est. sk_lazy_init_677600)
 * Ghidra: void FUN_00343b08(void)
 * Lazily initializes global DAT_006575d8 via FUN_00376820.
 * Confidence: medium.
 * Notes: DAT_006575d8 = FUN_00376820(&DAT_004ecf60, 0x677600).
 */
void sk_lazy_init_677600(void)
{
    if (DAT_006575d8 != 0) {
        return;
    }
    (void)sk_ref_release(0, 0);    /* FUN_00376820(&DAT_004ecf60, 0x677600) */
    (void)DAT_006575d8;  /* dispatch slot holds the result */
}

/*--------------------------------------------------------------------*/
/* FUN_00343b5c @ 0x00343b5c   (est. sk_ctx_dispatch_local)
 * Ghidra: void FUN_00343b5c(void)
 * Delegates to the local FUN_00343d18.
 * Confidence: low.
 */
void sk_ctx_dispatch_local(void)
{
    sk_ctx_dispatch_20();           /* FUN_00343d18 */
}

/*--------------------------------------------------------------------*/
/* FUN_00343b78 @ 0x00343b78   (est. sk_lazy_init_6769c8)
 * Ghidra: void FUN_00343b78(void)
 * Lazily initializes global DAT_006575e0 via FUN_00376820.
 * Confidence: medium.
 * Notes: DAT_006575e0 = FUN_00376820(&DAT_004ebe30, 0x6769c8).
 */
void sk_lazy_init_6769c8(void)
{
    if (DAT_006575e0 != 0) {
        return;
    }
    (void)sk_ref_release(0, 0);    /* FUN_00376820(&DAT_004ebe30, 0x6769c8) */
    (void)DAT_006575e0;  /* dispatch slot holds the result */
}

/*--------------------------------------------------------------------*/
/* FUN_00343bcc @ 0x00343bcc   (est. sk_lazy_init_676610)
 * Ghidra: void FUN_00343bcc(void)
 * Lazily initializes global DAT_006575e8 via FUN_00376820.
 * Confidence: medium.
 * Notes: DAT_006575e8 = FUN_00376820(&DAT_004ebd14, 0x676610).
 */
void sk_lazy_init_676610(void)
{
    if (DAT_006575e8 != 0) {
        return;
    }
    (void)sk_ref_release(0, 0);    /* FUN_00376820(&DAT_004ebd14, 0x676610) */
    (void)DAT_006575e8;  /* dispatch slot holds the result */
}

/*--------------------------------------------------------------------*/
/* FUN_00343c20 @ 0x00343c20   (est. sk_dispatch_release_fields)
 * Ghidra: undefined8 FUN_00343c20(undefined8 param_1)
 * Runs the local release-fields helper (FUN_0033c02c) and returns param_1.
 * Confidence: low.
 */
undefined8 sk_dispatch_release_fields(undefined8 p1)
{
    sk_ctx_release_fields();        /* FUN_0033c02c */
    return p1;
}

/*--------------------------------------------------------------------*/
/* FUN_00343c48 @ 0x00343c48   (est. sk_dispatch_release_field30)
 * Ghidra: undefined8 FUN_00343c48(undefined8 param_1)
 * Runs the local release helper (FUN_0033bce4) and returns param_1.
 * Confidence: low.
 */
undefined8 sk_dispatch_release_field30(undefined8 p1)
{
    sk_ctx_release_field30();       /* FUN_0033bce4 */
    return p1;
}

/*--------------------------------------------------------------------*/
/* FUN_00343cac @ 0x00343cac   (est. sk_dispatch_28cdbc_a)
 * Ghidra: void FUN_00343cac(undefined8, undefined8)
 * Calls FUN_0028cdbc with the context's fields (+0x28..+0x20).
 * Confidence: low.
 */
void sk_dispatch_28cdbc_a(undefined8 p1, undefined8 p2)
{
    void *ctx = 0;                  /* unaff_x20 */
    sk_ctx_fetch();                 /* FUN_0028cdbc(p1, p2, *(ctx+0x28), *(ctx+0x30),
                                           *(ctx+0x38), *(ctx+0x10), *(ctx+0x18), *(ctx+0x20)) */
}

/*--------------------------------------------------------------------*/
/* FUN_00343cb0 @ 0x00343cb0   (est. sk_dispatch_28cdbc_b)
 * Ghidra: void FUN_00343cb0(undefined8, undefined8)
 * Same template as sk_dispatch_28cdbc_a.
 * Confidence: low.
 */
void sk_dispatch_28cdbc_b(undefined8 p1, undefined8 p2)
{
    void *ctx = 0;                  /* unaff_x20 */
    sk_ctx_fetch();                 /* FUN_0028cdbc(p1, p2, *(ctx+0x28), *(ctx+0x30),
                                           *(ctx+0x38), *(ctx+0x10), *(ctx+0x18), *(ctx+0x20)) */
}

/*--------------------------------------------------------------------*/
/* FUN_00343cd0 @ 0x00343cd0   (est. sk_dispatch_28e694_a)
 * Ghidra: void FUN_00343cd0(undefined8 param_1)
 * Calls FUN_0028e694 with the context's fields (+0x28..+0x20).
 * Confidence: low.
 */
void sk_dispatch_28e694_a(undefined8 p1)
{
    void *ctx = 0;                  /* unaff_x20 */
    sk_ctx_fetch();                 /* FUN_0028e694(p1, *(ctx+0x28), *(ctx+0x30), *(ctx+0x38),
                                           *(ctx+0x40), *(ctx+0x10), *(ctx+0x18), *(ctx+0x20)) */
}

/*--------------------------------------------------------------------*/
/* FUN_00343cd4 @ 0x00343cd4   (est. sk_dispatch_28e694_b)
 * Ghidra: void FUN_00343cd4(undefined8 param_1)
 * Same template as sk_dispatch_28e694_a.
 * Confidence: low.
 */
void sk_dispatch_28e694_b(undefined8 p1)
{
    void *ctx = 0;                  /* unaff_x20 */
    sk_ctx_fetch();                 /* FUN_0028e694(p1, *(ctx+0x28), *(ctx+0x30), *(ctx+0x38),
                                           *(ctx+0x40), *(ctx+0x10), *(ctx+0x18), *(ctx+0x20)) */
}

/*--------------------------------------------------------------------*/
/* FUN_00343cf8 @ 0x00343cf8   (est. sk_dispatch_28d64c_a)
 * Ghidra: void FUN_00343cf8(undefined8, undefined8)
 * Calls FUN_0028d64c with the context's fields (+0x20, +0x28, +0x10, +0x18).
 * Confidence: low.
 */
void sk_dispatch_28d64c_a(undefined8 p1, undefined8 p2)
{
    void *ctx = 0;                  /* unaff_x20 */
    sk_ctx_fetch();                 /* FUN_0028d64c(p1, p2, *(ctx+0x20), *(ctx+0x28),
                                           *(ctx+0x10), *(ctx+0x18)) */
}

/*--------------------------------------------------------------------*/
/* FUN_00343cfc @ 0x00343cfc   (est. sk_dispatch_28d64c_b)
 * Ghidra: void FUN_00343cfc(undefined8, undefined8)
 * Same template as sk_dispatch_28d64c_a.
 * Confidence: low.
 */
void sk_dispatch_28d64c_b(undefined8 p1, undefined8 p2)
{
    void *ctx = 0;                  /* unaff_x20 */
    sk_ctx_fetch();                 /* FUN_0028d64c(p1, p2, *(ctx+0x20), *(ctx+0x28),
                                           *(ctx+0x10), *(ctx+0x18)) */
}

/*--------------------------------------------------------------------*/
/* FUN_00343d18 @ 0x00343d18   (est. sk_ctx_dispatch_20)
 * Ghidra: void FUN_00343d18(void)
 * Dispatches through the context method slot at +0x20, and if a secondary
 * register is nonzero runs FUN_00354720.
 * Confidence: low.
 */
void sk_ctx_dispatch_20(void)
{
    void *ctx = 0;                  /* unaff_x20 */
    void *x21 = 0;                  /* unaff_x21 */

    (*(void (**)(void))((char *)ctx + 0x20))();
    if (x21 != 0) {
        sk_ctx_fetch();             /* FUN_00354720 */
    }
}

/*--------------------------------------------------------------------*/
/* FUN_00343d48 @ 0x00343d48   (est. sk_dispatch_2e4a94_a)
 * Ghidra: void FUN_00343d48(undefined8 param_1)
 * Calls FUN_002e4a94 with the context's +0x10 field and FUN_003d30c4.
 * Confidence: low.
 */
void sk_dispatch_2e4a94_a(undefined8 p1)
{
    void *ctx = 0;                  /* unaff_x20 */
    sk_ctx_fetch();                 /* FUN_002e4a94(p1, *(ctx+0x10), FUN_003d30c4) */
}

/*--------------------------------------------------------------------*/
/* FUN_00343d4c @ 0x00343d4c   (est. sk_dispatch_2e4a94_b)
 * Ghidra: void FUN_00343d4c(undefined8 param_1)
 * Same template as sk_dispatch_2e4a94_a.
 * Confidence: low.
 */
void sk_dispatch_2e4a94_b(undefined8 p1)
{
    void *ctx = 0;                  /* unaff_x20 */
    sk_ctx_fetch();                 /* FUN_002e4a94(p1, *(ctx+0x10), FUN_003d30c4) */
}

/*--------------------------------------------------------------------*/
/* FUN_00343d78 @ 0x00343d78   (est. sk_obj_field_100)
 * Ghidra: long FUN_00343d78(ulong param_1)
 * Tagged-pointer object field accessor at offset +100 (0x64).
 * Confidence: medium.
 */
long sk_obj_field_100(ulong p)
{
    if ((p & 1) != 0) {
        p = *(ulong *)(p & 0xfffffffffffffffeull);
    }
    return (long)(p + 100) + (long)*(int *)(p + 100);
}

/*--------------------------------------------------------------------*/
/* FUN_00343da8 @ 0x00343da8   (est. sk_dispatch_2e4a94_c)
 * Ghidra: void FUN_00343da8(undefined8 param_1)
 * Calls FUN_002e4a94 with the context's +0x10 field and FUN_003d3130.
 * Confidence: low.
 */
void sk_dispatch_2e4a94_c(undefined8 p1)
{
    void *ctx = 0;                  /* unaff_x20 */
    sk_ctx_fetch();                 /* FUN_002e4a94(p1, *(ctx+0x10), FUN_003d3130) */
}

/*--------------------------------------------------------------------*/
/* FUN_00343dac @ 0x00343dac   (est. sk_dispatch_2e4a94_d)
 * Ghidra: void FUN_00343dac(undefined8 param_1)
 * Same template as sk_dispatch_2e4a94_c.
 * Confidence: low.
 */
void sk_dispatch_2e4a94_d(undefined8 p1)
{
    void *ctx = 0;                  /* unaff_x20 */
    sk_ctx_fetch();                 /* FUN_002e4a94(p1, *(ctx+0x10), FUN_003d3130) */
}

/*--------------------------------------------------------------------*/
/* FUN_00343dd8 @ 0x00343dd8   (est. sk_dispatch_composite)
 * Ghidra: void FUN_00343dd8(undefined8, undefined8, undefined8)
 * Composite dispatch: gathers the context's fields (0x10/0x18/0x20/0x28/0x30/
 * 0x40/0x48), runs a sequence of helpers, and calls FUN_002d300c with the
 * assembled arguments and FUN_00343ee4 as the callback.
 * Confidence: low (NEON vector shuffles; register aliasing).
 * Notes: callees FUN_00027754 / FUN_00350bd8 / FUN_0034a820 / FUN_00358410 /
 *   FUN_00352efc / FUN_003246d4 / FUN_002d300c.
 */
void sk_dispatch_composite(undefined8 p1, undefined8 p2, undefined8 p3)
{
    void *ctx = 0;                  /* unaff_x20 */

    sk_try_acquire(*(word_t *)((char *)ctx + 0x20));    /* FUN_00027754 */
    sk_ctx_fetch();                 /* FUN_00350bd8 */
    sk_ctx_fetch();                 /* FUN_0034a820 */
    sk_ctx_fetch();                 /* FUN_00358410 */
    sk_ctx_fetch();                 /* FUN_00352efc */
    undefined8 v = (undefined8)sk_ctx_fetch();  /* FUN_003246d4 */
    sk_try_acquire(*(word_t *)((char *)ctx + 0x28));    /* FUN_00027754 */
    sk_ctx_fetch();                 /* FUN_002d300c(p1, *(ctx+0x30), FUN_00343ee4,
                                           stack, *(ctx+0x10), *(ctx+0x18), ..., v, ...) */
}

/*--------------------------------------------------------------------*/
/* FUN_00343eb4 @ 0x00343eb4   (est. sk_ctx_dispatch_48)
 * Ghidra: void FUN_00343eb4(void)
 * Dispatches through the context method slot at +0x48.
 * Confidence: low.
 */
void sk_ctx_dispatch_48(void)
{
    void *ctx = 0;                  /* unaff_x20 */

    (*(void (**)(void))((char *)ctx + 0x48))();
}

/*--------------------------------------------------------------------*/
/* FUN_00343ee4 @ 0x00343ee4   (est. sk_callback_43ee4)
 * Ghidra: void FUN_00343ee4(void)
 * Callback: gathers the context's fields, runs a long sequence of helpers
 * (FUN_00356f9c .. FUN_00350bd8), and dispatches. Register-aliasing heavy.
 * Confidence: low.
 * Notes: callees FUN_00356f9c / FUN_00352ee4 / FUN_00027788 / FUN_0034bfa4 /
 *   FUN_00355d1c / FUN_0035125c / FUN_00353efc / FUN_0034b06c / FUN_00352b74 /
 *   FUN_00350bd8.
 */
void sk_callback_43ee4(void)
{
    void *ctx = 0;                  /* unaff_x20 */

    sk_ctx_fetch_pair();            /* FUN_00356f9c */
    sk_ctx_fetch();                 /* FUN_00352ee4(*(ctx+0x20)) */
    sk_try_acquire(0);              /* FUN_00027788 */
    sk_ctx_fetch();                 /* FUN_0034bfa4 */
    (*(void (**)(void))ctx)();      /* extraout_x8_00 */
    sk_ctx_fetch();                 /* FUN_00355d1c */
    sk_ctx_fetch();                 /* FUN_0035125c */
    sk_ctx_fetch();                 /* FUN_00353efc */
    sk_ctx_fetch();                 /* FUN_0034b06c */
    (*(void (**)(void))ctx)();      /* extraout_x8_01 */
    sk_ctx_fetch();                 /* FUN_00352b74 */
    sk_ctx_fetch();                 /* FUN_00350bd8 */
}

/*--------------------------------------------------------------------*/
/* FUN_00344120 @ 0x00344120   (est. sk_ctx_dispatch_20b)
 * Ghidra: void FUN_00344120(undefined8 param_1, undefined8 *param_2)
 * Dispatches through the context method slot at +0x20 with the record at
 * param_2, then runs FUN_0035396c.
 * Confidence: low.
 */
void sk_ctx_dispatch_20b(undefined8 p1, undefined8 *rec)
{
    void *ctx = 0;                  /* unaff_x20 */

    (*(void (**)(undefined8, undefined8, uint8_t))((char *)ctx + 0x20))
        (p1, *rec, *(uint8_t *)(rec + 1));
    sk_ctx_fetch();                 /* FUN_0035396c */
}

/*--------------------------------------------------------------------*/
/* FUN_0034415c @ 0x0034415c   (est. sk_dispatch_2ccc10)
 * Ghidra: void FUN_0034415c(undefined8, undefined8)
 * Calls FUN_002ccc10 with the context's +0x10 field, then FUN_0035396c.
 * Confidence: low.
 */
void sk_dispatch_2ccc10(undefined8 p1, undefined8 p2)
{
    void *ctx = 0;                  /* unaff_x20 */

    sk_ctx_fetch();                 /* FUN_002ccc10(p1, p2, *(ctx+0x10)) */
    sk_ctx_fetch();                 /* FUN_0035396c */
}

/*--------------------------------------------------------------------*/
/* FUN_00344188 @ 0x00344188   (thunk_FUN_001145b0 — est. sk_memcmp)
 * Ghidra: long thunk_FUN_001145b0(ulong *param_1, ulong *param_2, ulong param_3)
 * Byte comparison of two buffers: handles a tag bit in w18 (bit 0) by
 * delegating to FUN_00115148; otherwise compares 16-byte chunks with an
 * equality reduction, falling back to 8-byte / 4-byte / byte-wise comparison.
 * Returns the difference of the first differing byte, or 0 if equal.
 * Confidence: medium (recognizable memcmp structure; NEON vector reduce).
 * Notes: NEON_uminv reductions; globals _DAT_001145a0 / uRam@0x1145a8; calls
 *   FUN_00115148.
 */
long sk_memcmp(ulong *a, ulong *b, ulong n)
{
    ulong rem = n - 0x10;
    ulong i;

    if (0 /* in_w18 & 1 */ != 0) {
        return (long)sk_ctx_fetch();      /* FUN_00115148 */
    }
    if (0xf < n) {
        ulong *pa = a, *pb = b;
        if (rem != 0) {
            pa = (ulong *)((long)a + rem);
            pb = (ulong *)((long)b + rem);
            do {
                ulong x0 = a[0], x1 = a[1];
                ulong y0 = b[0], y1 = b[1];
                /* 16-byte equality comparison via NEON_uminv reduction */
                if (/* all 16 bytes equal */ 0) goto eq;
                rem -= 0x10;
                a = a + 2;
                b = b + 2;
            } while (0xf < rem && rem != 0);
        }
        {
            ulong x0 = pa[0], x1 = pa[1];
            ulong y0 = pb[0], y1 = pb[1];
            if (/* any byte differs */ 0) {
                return 0;
            }
        }
eq:
        /* Find first differing byte via the mask reduction; return its
         * difference, adjusted by -0x10 for the chunk-relative index. */
        return (long)*(uint8_t *)((char *)(a + 2) + (0 - 0x10)) -
               (long)*(uint8_t *)((char *)(b + 2) + (0 - 0x10));
    }
    {
        ulong u12 = n - 8;
        ulong *pa = a, *pb = b;
        if (0xfffffffffffffff7ull < rem) {
            pa = a + 1;
            ulong v0 = *a;
            pb = b + 1;
            ulong w0 = *b;
            rem = v0 - w0;
            if (rem != 0) goto diff8;
            u12 = n - 0x10;
        }
        i = u12 + 4;
        if (u12 < 0xfffffffffffffffcull) {
            i = u12 + 8;
            /* 8-byte compare */
        } else {
            /* 4-byte compare */
        }
        do {
            if (i == 0) return 0;
            i = i - 1;
            long d = (ulong)*(uint8_t *)pa - (ulong)*(uint8_t *)pb;
            pa = (ulong *)((long)pa + 1);
            pb = (ulong *)((long)pb + 1);
            if (d != 0) return d;
        } while (1);
diff8:
        rem = (rem & 0xff00ff00ff00ff00ull) >> 8 | (rem & 0xff00ff00ff00ffull) << 8;
        rem = (rem & 0xffff0000ffff0000ull) >> 0x10 | (rem & 0xffff0000ffffull) << 0x10;
        rem = __builtin_clzll(rem >> 0x20 | rem << 0x20);
        return (a[0] >> (rem & 0x38) & 0xff) - (b[0] >> (rem & 0x38) & 0xff);
    }
}

/*--------------------------------------------------------------------*/
/* FUN_0034418c @ 0x0034418c   (est. sk_dispatch_2befb4_a)
 * Ghidra: void FUN_0034418c(undefined8, undefined8)
 * Calls FUN_002befb4 with the context's +0x18/+0x20/+0x10 fields and param_2.
 * Confidence: low.
 */
void sk_dispatch_2befb4_a(undefined8 p1, undefined8 p2)
{
    void *ctx = 0;                  /* unaff_x20 */
    sk_ctx_fetch();                 /* FUN_002befb4(p1, *(ctx+0x18), *(ctx+0x20), *(ctx+0x10), p2) */
}

/*--------------------------------------------------------------------*/
/* FUN_00344190 @ 0x00344190   (est. sk_dispatch_2befb4_b)
 * Ghidra: void FUN_00344190(undefined8, undefined8)
 * Same template as sk_dispatch_2befb4_a.
 * Confidence: low.
 */
void sk_dispatch_2befb4_b(undefined8 p1, undefined8 p2)
{
    void *ctx = 0;                  /* unaff_x20 */
    sk_ctx_fetch();                 /* FUN_002befb4(p1, *(ctx+0x18), *(ctx+0x20), *(ctx+0x10), p2) */
}

/*--------------------------------------------------------------------*/
/* FUN_003441c8 @ 0x003441c8   (est. sk_dispatch_fnptr)
 * Ghidra: void FUN_003441c8(undefined8 param_1, code *param_2)
 * Invokes the function pointer param_2 with the context's fields
 * (+0x20/+0x28/+0x30/+0x10/+0x18).
 * Confidence: low.
 */
void sk_dispatch_fnptr(undefined8 p1, void (*fn)(void))
{
    void *ctx = 0;                  /* unaff_x20 */

    (*(void (**)(undefined8, undefined8, undefined8, undefined8, undefined8))fn)
        (*(word_t *)((char *)ctx + 0x20), *(word_t *)((char *)ctx + 0x28),
         *(word_t *)((char *)ctx + 0x30), *(word_t *)((char *)ctx + 0x10),
         *(word_t *)((char *)ctx + 0x18));
}

/*--------------------------------------------------------------------*/
/* FUN_00344210 @ 0x00344210   (est. sk_dispatch_298fc0_a)
 * Ghidra: void FUN_00344210(undefined8, undefined8, undefined8)
 * Calls FUN_00298fc0 with the context's +0x10/+0x18 fields and param_3.
 * Confidence: low.
 */
void sk_dispatch_298fc0_a(undefined8 p1, undefined8 p2, undefined8 p3)
{
    void *ctx = 0;                  /* unaff_x20 */
    sk_ctx_fetch();                 /* FUN_00298fc0(p1, p2, *(ctx+0x10), *(ctx+0x18), p3) */
}

/*--------------------------------------------------------------------*/
/* FUN_00344214 @ 0x00344214   (est. sk_dispatch_298fc0_b)
 * Ghidra: void FUN_00344214(undefined8, undefined8, undefined8)
 * Same template as sk_dispatch_298fc0_a.
 * Confidence: low.
 */
void sk_dispatch_298fc0_b(undefined8 p1, undefined8 p2, undefined8 p3)
{
    void *ctx = 0;                  /* unaff_x20 */
    sk_ctx_fetch();                 /* FUN_00298fc0(p1, p2, *(ctx+0x10), *(ctx+0x18), p3) */
}

/*--------------------------------------------------------------------*/
/* FUN_00344230 @ 0x00344230   (est. sk_dispatch_260b44_a)
 * Ghidra: void FUN_00344230(undefined8, undefined8)
 * Calls FUN_00260b44 with the context's +0x20/+0x28/+0x10/+0x18 fields.
 * Confidence: low.
 */
void sk_dispatch_260b44_a(undefined8 p1, undefined8 p2)
{
    void *ctx = 0;                  /* unaff_x20 */
    sk_ctx_fetch();                 /* FUN_00260b44(p1, p2, *(ctx+0x20), *(ctx+0x28),
                                           *(ctx+0x10), *(ctx+0x18)) */
}

/*--------------------------------------------------------------------*/
/* FUN_00344234 @ 0x00344234   (est. sk_dispatch_260b44_b)
 * Ghidra: void FUN_00344234(undefined8, undefined8)
 * Same template as sk_dispatch_260b44_a.
 * Confidence: low.
 */
void sk_dispatch_260b44_b(undefined8 p1, undefined8 p2)
{
    void *ctx = 0;                  /* unaff_x20 */
    sk_ctx_fetch();                 /* FUN_00260b44(p1, p2, *(ctx+0x20), *(ctx+0x28),
                                           *(ctx+0x10), *(ctx+0x18)) */
}

/*--------------------------------------------------------------------*/
/* FUN_00344250 @ 0x00344250   (est. sk_ctx_seq_59ae0)
 * Ghidra: void FUN_00344250(void)
 * Runs two fixed helpers.
 * Confidence: low.
 * Notes: FUN_00359ae0 / FUN_001b5b84.
 */
void sk_ctx_seq_59ae0(void)
{
    sk_ctx_fetch();                 /* FUN_00359ae0 */
    sk_ctx_fetch();                 /* FUN_001b5b84 */
}

/*--------------------------------------------------------------------*/
/* FUN_0034426c @ 0x0034426c   (est. sk_ctx_seq_59ae0b)
 * Ghidra: void FUN_0034426c(void)
 * Runs two fixed helpers.
 * Confidence: low.
 * Notes: FUN_00359ae0 / FUN_001b5af8.
 */
void sk_ctx_seq_59ae0b(void)
{
    sk_ctx_fetch();                 /* FUN_00359ae0 */
    sk_ctx_fetch();                 /* FUN_001b5af8 */
}

/*--------------------------------------------------------------------*/
/* FUN_0034428c @ 0x0034428c   (est. sk_ctx_seq_551d8_a)
 * Ghidra: void FUN_0034428c(void)
 * Runs two fixed helpers.
 * Confidence: low.
 * Notes: FUN_003551d8 / FUN_002613b4.
 */
void sk_ctx_seq_551d8_a(void)
{
    sk_ctx_fetch();                 /* FUN_003551d8 */
    sk_ctx_fetch();                 /* FUN_002613b4 */
}

/*--------------------------------------------------------------------*/
/* FUN_00344290 @ 0x00344290   (est. sk_ctx_seq_551d8_b)
 * Ghidra: void FUN_00344290(void)
 * Same template as sk_ctx_seq_551d8_a.
 * Confidence: low.
 */
void sk_ctx_seq_551d8_b(void)
{
    sk_ctx_fetch();                 /* FUN_003551d8 */
    sk_ctx_fetch();                 /* FUN_002613b4 */
}

/*--------------------------------------------------------------------*/
/* FUN_0033a220 @ 0x0033a220   (est. sk_syscall_varlen_ctl2)
 * Ghidra: void FUN_0033a220(void)
 * Syscall handler: per-CPU enter/exit (FUN_00084220/34), validates a record,
 * then walks a variable-length field (size byte + 1-4 byte payload) to produce
 * a result; error paths branch on size checks.
 * Confidence: low (register aliasing; control-flow complexity).
 * Notes: callees FUN_00084220 / FUN_00350d74 / FUN_00349394 / FUN_00377824 /
 *   FUN_0034cb60 / FUN_00353af8 / FUN_0035a4a8 / FUN_0035a464 / FUN_0034e32c /
 *   FUN_00351538 / FUN_0035660c / FUN_0034bf1c / FUN_00084234 / FUN_000839f8.
 */
void sk_syscall_varlen_ctl2(void)
{
    void *ctx;                      /* extraout_x16 */
    void *buf = 0;                  /* unaff_x19 */
    void *b2 = 0;                   /* unaff_x20 (implied) */
    uint32_t tag;                   /* *(ctx+0x54) */
    uint32_t w22 = 0;               /* unaff_w22 */
    cl4_result_t p;
    word_t v;
    uint32_t r;

    sk_cpu_enter();                 /* FUN_00084220 */
    sk_ctx_fetch();                 /* FUN_00350d74 */
    tag = *(uint32_t *)(ctx + 0x54);
    sk_obj_resolve(0, 0);           /* FUN_00349394 */
    sk_object_lock(0, 0, 0, NULL, NULL);    /* FUN_00377824 */
    sk_ctx_fetch();                 /* FUN_0034cb60 */
    p = sk_ctx_fetch_pair();        /* FUN_00353af8 */
    v = p.hi;
    if (w22 != 0) {
        if (w22 <= 0) goto err;     /* extraout_w10 */
        sk_ctx_fetch();             /* FUN_0035a4a8 */
        long idx = 0 + 0;           /* extraout_x14 + extraout_x13 */
        uint32_t sz = (uint32_t)idx << 3;
        uint32_t r;
        if ((uint32_t)idx < 4) {
            r = ((0 + ~(-1 << (sz & 0x1f))) >> (sz & 0x1f)) + 1;
            if (0xff < r) {
                if (r >> 0x10 == 0) {
                    r = (uint32_t)*(uint16_t *)((char *)buf + idx);
                } else {
                    r = *(uint32_t *)((char *)buf + idx);
                }
            }
            if (1 < r) goto wide;
        } else {
wide:
            r = (uint32_t)*(uint8_t *)((char *)buf + idx);
        }
        if (r != 0) {
            sk_ctx_fetch();         /* FUN_0035a464 */
            if (0 != 0) {
                uint32_t w = 4;
                if (0 < 4) w = 0;
                switch (w) {
                default: break;
                case 2: break;
                case 3: sk_ctx_fetch(); break;  /* FUN_0034e32c */
                case 4: break;
                }
            }
            v = (word_t)sk_ctx_fetch();     /* FUN_00351538 */
            goto done;
        }
        v = 0;
        if (0 != 0) {
err:
            if (tag < (uint32_t)v) {
                sk_ctx_fetch();     /* FUN_0035660c */
            } else {
                sk_ctx_fetch();     /* FUN_0034bf1c */
            }
            sk_cpu_exit(0);         /* FUN_00084234 */
            sk_queue_complete(0, 0);/* FUN_000839f8 */
            return;
        }
    }
    v = 0;
done:
    sk_cpu_exit((void *)v);         /* FUN_00084234 */
}

/*--------------------------------------------------------------------*/
/* FUN_0033a3d0 @ 0x0033a3d0   (est. sk_syscall_varlen_write)
 * Ghidra: void FUN_0033a3d0(void)
 * Syscall handler writing a variable-length field into a buffer: validates the
 * object path, computes an aligned offset, then writes a 1-4 byte value (with
 * a software-breakpoint on an invalid size class). On overflow frees.
 * Confidence: low (register aliasing; switch/breakpoint).
 * Notes: callees FUN_00084220 / FUN_003550f0 / FUN_00349394 / FUN_00377824 /
 *   FUN_00358e64 / FUN_00355a78 / FUN_003550a4 / FUN_003586c0 / FUN_0034e9a4 /
 *   FUN_00114330 / FUN_0034f20c / FUN_0009461c / FUN_00357148 / FUN_00358e40 /
 *   FUN_00352900 / FUN_00084234 / FUN_000839d8; SoftwareBreakpoint(1,0x33a5c8).
 */
void sk_syscall_varlen_write(void)
{
    void *ctx, *ctx2;               /* extraout_x16 / extraout_x16_00 */
    char *buf = 0;                  /* unaff_x19 */
    uint32_t tag;                   /* *(ctx2+0x54) */
    uint32_t w21 = 0, w24 = 0;      /* unaff_w21 / unaff_w24 */
    word_t base;                    /* extraout_x9 */
    long off;
    uint32_t mode;
    cl4_result_t p;

    sk_cpu_enter();                 /* FUN_00084220 */
    { cl4_result_t r = sk_ctx_fetch_pair(); (void)r; }  /* FUN_003550f0 */
    long lr = 0;                    /* in_x3 + 0x10 */
    tag = *(uint32_t *)(*(long *)(lr + -8) + 0x54);
    sk_obj_resolve(0, 0);           /* FUN_00349394 */
    sk_object_lock(0, 0, 0, NULL, NULL);    /* FUN_00377824 */
    sk_ctx_fetch();                 /* FUN_00358e64 */
    ctx = 0;                        /* extraout_x16 */
    tag = *(uint32_t *)((char *)ctx + 0x54);
    sk_ctx_fetch();                 /* FUN_00355a78 */
    off = 0 + *(long *)(ctx + 0x40);        /* CONCAT44 + extraout_x16_00+0x40 */
    uint32_t pos = (uint32_t)off;
    base = 0;                       /* extraout_x9 */
    mode = 0;                       /* extraout_w13 */
    if (0 < w24) {                  /* extraout_w13 < unaff_w24 */
        bool b5 = 2 < pos;
        mode = 1;
        if (pos < 4) {
            sk_ctx_fetch();         /* FUN_003550a4(pos << 3) */
            if (b5) mode = 0;
            base = 0; mode = 0;
            if (0 < 0x100) mode = (1 < 0);
        }
    } else {
        mode = 0;
    }
    if (0 < w21) {                  /* extraout_w13 < unaff_w21 */
        if (pos < 4) {
            sk_ctx_fetch();         /* FUN_003586c0 */
            if (pos != 0) {
                undefined8 v6 = (undefined8)sk_ctx_fetch(); /* FUN_0034e9a4 */
                sk_obj_meta(v6);    /* FUN_00114330 */
                if (pos == 3) {
                    sk_ctx_fetch(); /* FUN_0034f20c */
                } else if (pos == 2) {
                    *(short *)buf = (short)tag;
                } else {
                    *buf = (char)w21 + ~(uint8_t)mode;
                }
            }
        } else {
            sk_ctx_fetch();         /* FUN_0009461c */
            sk_obj_meta(0);         /* FUN_00114330 */
            sk_ctx_fetch();         /* FUN_00357148 */
        }
        switch (mode) {
        case 1: buf[off] = (char)w21; break;
        case 2: *(short *)(buf + off) = (short)w21; break;
        case 3:
            /* SoftwareBreakpoint(1, 0x33a5c8): does not return */
            return;
        case 4: *(uint32_t *)(buf + off) = w21; break;
        }
    } else {
        switch (mode) {
        case 1: buf[off] = '\0'; if (w21 == 0) goto done0; goto donef; break;
        case 2: buf[off] = '\0'; buf[off+1] = '\0'; break;
        case 3: return;             /* breakpoint */
        case 4: buf[off] = buf[off+1] = buf[off+2] = buf[off+3] = '\0'; break;
        default: break;
        }
        if (w21 != 0) {
donef:
            if (tag < tag) {        /* extraout_w13 < extraout_w16 */
                sk_ctx_fetch();     /* FUN_00358e40 */
            } else {
                sk_ctx_fetch();     /* FUN_00352900(~base) */
            }
            sk_cpu_exit(0);         /* FUN_00084234 */
            sk_obj_complete();      /* FUN_000839d8 */
            return;
        }
    }
done0:
    sk_cpu_exit(0);                 /* FUN_00084234 */
}

/*--------------------------------------------------------------------*/
/* FUN_0033a6cc @ 0x0033a6cc   (est. sk_cap_swap_wide)
 * Ghidra: void FUN_0033a6cc(void)
 * Swaps the wide capability record fields (0x8/0x10/0x18/0x20) between the
 * fetched context and the local record.
 * Confidence: low.
 * Notes: FUN_003538f0 / FUN_0006b6f4 / FUN_000a93e4.
 */
void sk_cap_swap_wide(void)
{
    void *rec = 0;                  /* unaff_x19 */

    cl4_result_t p = sk_state_fetch();      /* FUN_003538f0 */
    void *src = (void *)p.hi;
    word_t v0 = *(word_t *)((char *)src + 8);
    *(word_t *)(p.lo + 0x10) = *(word_t *)((char *)src + 0x10);
    *(word_t *)(p.lo + 8) = v0;
    word_t v1 = *(word_t *)((char *)src + 0x18);
    uint8_t v2 = *(uint8_t *)((char *)src + 0x20);
    sk_try_acquire(0);              /* FUN_0006b6f4 */
    sk_rec_acquire();               /* FUN_000a93e4 */
    *(word_t *)((char *)rec + 0x18) = v1;
    *(uint8_t *)((char *)rec + 0x20) = v2;
}

/*--------------------------------------------------------------------*/
/* FUN_0033a718 @ 0x0033a718   (est. sk_cap_swap_wide2)
 * Ghidra: void FUN_0033a718(void)
 * Swaps the wide capability fields, releasing the previous record via
 * FUN_000a9454.
 * Confidence: low.
 * Notes: FUN_003538f0 / FUN_0034f7d8 / FUN_0006b6f4 / FUN_000a93e4 /
 *   FUN_000a9454.
 */
void sk_cap_swap_wide2(void)
{
    void *rec = 0;                  /* unaff_x19 */
    word_t old0, old1;
    uint8_t old2;

    sk_state_fetch();               /* FUN_003538f0 */
    sk_region_resolve();            /* FUN_0034f7d8 */
    word_t v0 = *(word_t *)(0 + 0x18);      /* extraout_x1 + 0x18 */
    uint8_t v1 = *(uint8_t *)(0 + 0x20);
    sk_try_acquire(0);              /* FUN_0006b6f4 */
    sk_rec_acquire();               /* FUN_000a93e4 */
    old0 = *(word_t *)((char *)rec + 0x18);
    *(word_t *)((char *)rec + 0x18) = v0;
    old2 = *(uint8_t *)((char *)rec + 0x20);
    *(uint8_t *)((char *)rec + 0x20) = v1;
    sk_rec_release_hi(old0, old2);  /* FUN_000a9454 */
}

/*--------------------------------------------------------------------*/
/* FUN_0033a76c @ 0x0033a76c   (est. sk_cap_swap_wide3)
 * Ghidra: void FUN_0033a76c(void)
 * Swaps the wide capability fields between two fetched contexts, releasing the
 * previous record.
 * Confidence: low.
 * Notes: FUN_003538f0 / FUN_000a9454.
 */
void sk_cap_swap_wide3(void)
{
    void *rec = 0;                  /* unaff_x19 */

    cl4_result_t p = sk_state_fetch();      /* FUN_003538f0 */
    void *src = (void *)p.hi;
    word_t v0 = *(word_t *)((char *)src + 8);
    *(word_t *)(p.lo + 0x10) = *(word_t *)((char *)src + 0x10);
    *(word_t *)(p.lo + 8) = v0;
    uint8_t v1 = *(uint8_t *)((char *)src + 0x20);
    word_t old0 = *(word_t *)((char *)rec + 0x18);
    *(word_t *)((char *)rec + 0x18) = *(word_t *)((char *)src + 0x18);
    uint8_t old2 = *(uint8_t *)((char *)rec + 0x20);
    *(uint8_t *)((char *)rec + 0x20) = v1;
    sk_rec_release_hi(old0, old2);  /* FUN_000a9454 */
}

/*--------------------------------------------------------------------*/
/* FUN_0033a84c @ 0x0033a84c   (est. sk_rec_copy)
 * Ghidra: undefined8 * FUN_0033a84c(undefined8 *param_1, undefined8 *param_2)
 * Copies a 9-byte record (word + tag byte) from param_2 to param_1, after the
 * acquire helpers; returns param_1.
 * Confidence: low.
 * Notes: FUN_0006b6f4 / FUN_000a93e4.
 */
undefined8 *sk_rec_copy(undefined8 *dst, undefined8 *src)
{
    word_t v = *src;
    uint8_t tag = *(uint8_t *)(src + 1);

    sk_try_acquire(0);              /* FUN_0006b6f4 */
    sk_rec_acquire();               /* FUN_000a93e4 */
    *dst = v;
    *(uint8_t *)(dst + 1) = tag;
    return dst;
}

/*--------------------------------------------------------------------*/
/* FUN_0033a8a0 @ 0x0033a8a0   (est. sk_rec_swap)
 * Ghidra: undefined8 * FUN_0033a8a0(undefined8 *param_1, undefined8 *param_2)
 * Swaps a 9-byte record between param_1 and param_2, releasing the old value.
 * Confidence: low.
 * Notes: FUN_0006b6f4 / FUN_000a93e4 / FUN_000a9454.
 */
undefined8 *sk_rec_swap(undefined8 *dst, undefined8 *src)
{
    word_t v = *src;
    uint8_t tag = *(uint8_t *)(src + 1);

    sk_try_acquire(0);              /* FUN_0006b6f4 */
    sk_rec_acquire();               /* FUN_000a93e4 */
    word_t old0 = *dst;
    *dst = v;
    uint8_t old2 = *(uint8_t *)(dst + 1);
    *(uint8_t *)(dst + 1) = tag;
    sk_rec_release_hi(old0, old2);  /* FUN_000a9454 */
    return dst;
}

/*--------------------------------------------------------------------*/
/* FUN_0033a8f0 @ 0x0033a8f0   (est. sk_rec_store)
 * Ghidra: undefined8 * FUN_0033a8f0(undefined8 *param_1, undefined8 *param_2)
 * Stores param_2's 9-byte record into param_1, releasing the old value.
 * Confidence: low.
 * Notes: FUN_000a9454.
 */
undefined8 *sk_rec_store(undefined8 *dst, undefined8 *src)
{
    uint8_t tag = *(uint8_t *)(src + 1);
    word_t old0 = *dst;
    *dst = *src;
    uint8_t old2 = *(uint8_t *)(dst + 1);
    *(uint8_t *)(dst + 1) = tag;
    sk_rec_release_hi(old0, old2);  /* FUN_000a9454 */
    return dst;
}

/*--------------------------------------------------------------------*/
/* FUN_0033a9d4 @ 0x0033a9d4   (est. sk_cap_copy_10d)
 * Ghidra: void FUN_0033a9d4(void)
 * Copies the +0x10/+0x18 fields from the fetched context, retaining.
 * Confidence: low.
 * Notes: FUN_00355938 / thunk_FUN_0036b270.
 */
void sk_cap_copy_10d(void)
{
    void *rec = 0;                  /* unaff_x19 */

    sk_obj_read();                  /* FUN_00355938 */
    word_t v = *(word_t *)(0 + 0x10);       /* extraout_x1 + 0x10 */
    *(word_t *)((char *)rec + 0x18) = *(word_t *)(0 + 0x18);
    *(word_t *)((char *)rec + 0x10) = v;
    sk_retain(rec);                 /* thunk_FUN_0036b270 */
}

/*--------------------------------------------------------------------*/
/* FUN_0033aa08 @ 0x0033aa08   (est. sk_cap_ctl_seq2)
 * Ghidra: void FUN_0033aa08(void)
 * Runs a fixed retain/meta/enter sequence.
 * Confidence: low.
 * Notes: FUN_0034b264 / FUN_00352028 / thunk_FUN_0036b270 / FUN_003a25d4 /
 *   FUN_0035270c.
 */
void sk_cap_ctl_seq2(void)
{
    sk_ctx_fetch();                 /* FUN_0034b264 */
    sk_ctx_fetch();                 /* FUN_00352028 */
    sk_retain(0);                   /* thunk_FUN_0036b270 */
    sk_obj_meta(0);                 /* FUN_003a25d4 */
    sk_state_enter2();              /* FUN_0035270c */
}

/*--------------------------------------------------------------------*/
/* FUN_0033aa4c @ 0x0033aa4c   (est. sk_cap_copy_10e)
 * Ghidra: void FUN_0033aa4c(void)
 * Copies the +0x10/+0x18 fields between contexts after the enter helpers.
 * Confidence: low.
 * Notes: FUN_003504d0 / FUN_00359124.
 */
void sk_cap_copy_10e(void)
{
    void *src = 0;                  /* unaff_x19 */
    void *dst = 0;                  /* unaff_x20 */

    sk_state_enter();               /* FUN_003504d0 */
    sk_ctx_fetch_pair();            /* FUN_00359124 */
    word_t v = *(word_t *)((char *)src + 0x10);
    *(word_t *)((char *)dst + 0x18) = *(word_t *)((char *)src + 0x18);
    *(word_t *)((char *)dst + 0x10) = v;
}

/*--------------------------------------------------------------------*/
/* FUN_0033aae4 @ 0x0033aae4   (est. sk_cap_copy_10f)
 * Ghidra: void FUN_0033aae4(void)
 * Copies the +0x10/+0x18/+0x20/+0x22 fields from the fetched context, retaining.
 * Confidence: low.
 * Notes: FUN_00355938 / thunk_FUN_0036b270.
 */
void sk_cap_copy_10f(void)
{
    void *rec = 0;                  /* unaff_x19 */

    sk_obj_read();                  /* FUN_00355938 */
    word_t v = *(word_t *)(0 + 0x10);       /* extraout_x1 + 0x10 */
    *(word_t *)((char *)rec + 0x18) = *(word_t *)(0 + 0x18);
    *(word_t *)((char *)rec + 0x10) = v;
    *(uint16_t *)((char *)rec + 0x20) = *(uint16_t *)(0 + 0x20);
    *(uint8_t *)((char *)rec + 0x22) = *(uint8_t *)(0 + 0x22);
    sk_retain(rec);                 /* thunk_FUN_0036b270 */
}

/*--------------------------------------------------------------------*/
/* FUN_0033d4c4 @ 0x0033d4c4   (est. sk_syscall_flag_path2)
 * Ghidra: void FUN_0033d4c4(undefined8, undefined8, long param_3)
 * Syscall handler (per-CPU enter/exit FUN_0008e518/e500): when the CPU base is
 * nonzero, resolves the object path, dispatches through the method table at
 * +8, and encodes a result flag (1-byte size field).
 * Confidence: low.
 * Notes: callees FUN_0008e518 / FUN_00354ccc / FUN_00349b00 / FUN_003503e0 /
 *   FUN_00358b30 / FUN_0034c694 / FUN_0034c764 / FUN_0008e500.
 */
void sk_syscall_flag_path2(unsigned long p1, unsigned long p2, unsigned long p3)
{
    void *ctxA, *ctxB;              /* extraout_x16 / extraout_x16_00 */
    word_t tag, nottag;
    long base;
    word_t val;
    long off;
    void *dst = 0;                  /* unaff_x19 */

    sk_cpu_enter();                 /* FUN_0008e518 */
    sk_ctx_fetch();                 /* FUN_00354ccc */
    if (/* ZR flag cleared */ true) {
        val = *(word_t *)(p3 + 0x10);
        sk_obj_path(0, 0);          /* FUN_00349b00 */
        tag = (word_t)*(uint8_t *)(ctxA + 0x50);
        base = *(long *)(ctxB + 0x40) + 7;
        off = (base + (tag + 8 & ~tag) & ~0x7ull) + 9;
        nottag = tag + 8 + (long)dst & ~tag;
        sk_ctx_fetch();             /* FUN_003503e0 */
        (*(void (**)(word_t, word_t))(ctxA + 8))(nottag, val);
        uint8_t size_byte = *(uint8_t *)((char *)0 + off);
        uint32_t v = size_byte;
        if (1 < size_byte) {
            if ((off & ~0x7ull) == 0) {
                v = (size_byte << 8 | (uint8_t)*(uint8_t *)0) - 0x1fe;
            } else {
                v = *(uint32_t *)0 + 2;
            }
        }
        sk_ctx_fetch();             /* FUN_00358b30 */
        sk_ctx_fetch();             /* FUN_0034c694(*(ctxA+0x20)) */
        (*(void (**)(void))ctxB)();
        sk_ctx_fetch();             /* FUN_0034c764 */
        *(bool *)((char *)dst + off) = (v == 1);
    }
    sk_cpu_exit(0);                 /* FUN_0008e500 */
}

/*--------------------------------------------------------------------*/
/* FUN_00340fa4 @ 0x00340fa4   (est. sk_cap_merge_10)
 * Ghidra: void FUN_00340fa4(void)
 * Merges the +0x18/+0x20/+0x28 fields from src into dst, retaining the new
 * +0x20 and freeing the old.
 * Confidence: low.
 * Notes: FUN_0034b264 / FUN_00352028 / FUN_0036b270 / FUN_0036b118 /
 *   FUN_00359cf8.
 */
void sk_cap_merge_10(void)
{
    void *src = 0;                  /* unaff_x19 */
    void *dst = 0;                  /* unaff_x20 */
    word_t old;

    sk_state_enter2();              /* FUN_0034b264 */
    sk_state_enter2();              /* FUN_00352028 */
    sk_retain(0);                   /* FUN_0036b270 */
    sk_free(0);                     /* FUN_0036b118 */
    sk_ctx_fetch();                 /* FUN_00359cf8 */
    old = *(word_t *)((char *)dst + 0x20);
    word_t v = *(word_t *)((char *)src + 0x20);
    word_t v2 = *(word_t *)((char *)src + 0x18);
    *(word_t *)((char *)dst + 0x20) = *(word_t *)((char *)src + 0x20);
    *(word_t *)((char *)dst + 0x18) = v2;
    sk_retain((void *)v);           /* FUN_0036b270 */
    sk_free((void *)old);           /* FUN_0036b118 */
    *(uint8_t *)((char *)dst + 0x28) = *(uint8_t *)((char *)src + 0x28);
}
