/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel,
 * arm64e, image base 0) — the cL4 microkernel (GL1), "cL4 (679.100.61)".
 * Ground truth: Ghidra FUN_ names + addresses in program cl4_kernel.raw.
 * Slice R50: 0x380864-0x397a98 (120 functions). This is the embedded Swift
 * standard-library / runtime TypeDecoder + demangler: the recursive metadata
 * decoder (FUN_0038f0a8, the large coroutine/type-graph decoder), the
 * string-buffer error reporting helpers (FUN_00112db4/00112e8c), the
 * `TypeDecoder.decode` public entry points (FUN_003895e0 and its siblings),
 * and the type-name / mangled-name lookup machinery. All names are estimates
 * unless string-matched. */

#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdbool.h>

/* cL4 returns many values as a 16-byte pair (two 64-bit words in x0/x1). */
typedef struct { unsigned long lo, hi; } cL4_w16_t;

/* ------------------------------------------------------------------ *
 * Externs for the shared cL4 runtime / Swift metadata helpers called by
 * these bodies (they live elsewhere in the kernel image).
 * ------------------------------------------------------------------ */
extern void *cL4_alloc(unsigned long size, unsigned long tag);   /* FUN_00111890 */
extern void cL4_free(void *p, unsigned long size);               /* thunk_FUN_00012568 */
extern void cL4_stack_fail(void) __attribute__((noreturn));      /* FUN_0011d7e8 */
extern void cL4_ref_acquire(unsigned long obj);                  /* FUN_0037a48c */
extern void cL4_ref_release(unsigned long obj);                  /* FUN_0037aed8 */
extern void cL4_release(unsigned long obj);                      /* FUN_0037a978 */
extern unsigned long *cL4_obj_alloc(void);                       /* FUN_0037a7f8 */
extern void cL4_node_wait_init(unsigned long *wq, unsigned long v); /* FUN_0037a850 */
extern void cL4_obj_hw_init(void);                               /* FUN_0036c3e0 */
extern long cL4_zone_get(void);                                  /* FUN_00362ea4 */
extern void cL4_ipc_obj_publish(long *d, long a, long b);        /* FUN_003a3814 */
extern void cL4_percpu_ctx_table(void *out);                     /* FUN_0036e878 */
extern long cL4_mr_ctx_init2(void *ctx);                         /* FUN_0037e528 */
extern void cL4_msg_free(void *msg);                             /* FUN_0037f9f8 */
extern unsigned long cL4_mr_copy6(unsigned long reg, unsigned long acc0, unsigned long n,
                                  unsigned long opts, unsigned long *src5, unsigned long *src6); /* FUN_00380ad4 */
extern void cL4_simd_copy_begin(void *ctx, void *p, unsigned long imm); /* FUN_0037e58c */
extern void cL4_simd_copy_loop(void *ctx, void *p);             /* FUN_0037e614 */
extern long cL4_obj_copy_simple(long dst, long src, unsigned long op); /* FUN_00117cc4 */
extern int cL4_waiter_next(unsigned long *word, unsigned long start, int mode); /* FUN_0035b178 */
extern unsigned long cL4_waiter_hash(unsigned long key);        /* FUN_0035b588 */
extern int thunk_FUN_00114e50(unsigned long a, unsigned long b, long c);
extern unsigned long thunk_FUN_00115080(unsigned long cap);
extern void cL4_wordlist_grow(long *list, long *slot, unsigned long n, unsigned int tag); /* FUN_003a294c */

/* Swift runtime TypeDecoder error / string-buffer primitives. */
extern void *cL4_strbuf_alloc(long size);                        /* FUN_00112db4 */
extern void *cL4_strbuf_print(void *buf, unsigned long v);       /* FUN_00112e8c */
extern unsigned long cL4_strbuf_join(unsigned long a, unsigned long b); /* FUN_0037f9f4 */
extern void cL4_log_printf(unsigned long a, unsigned long b);    /* FUN_004b9ed8 */

/* In-slice forward declarations (defined later in this file). */
extern unsigned long sk_type_lookup_389940(unsigned long, unsigned long, unsigned long, unsigned long);
extern void sk_type_lookup_core_3895e0(unsigned long *, unsigned long, long, unsigned long,
                                       unsigned long, unsigned long, unsigned long);
EOF

/* FUN_00380864 @ 0x380864   (est. sk_mr_send_word_replace)
 * Ghidra: void FUN_00380864(ulong *param_1, undefined8 *param_2, long, long)
 * Replaces the message-register word descriptor pointed at by param_2 with a
 * freshly allocated node (FUN_0037a7f8) when the incumbent isn't a singleton,
 * copies the two payload words into the node, and records the node pointer +
 * kind byte (offset +0x11) in the caller's result word. Frees the replaced
 * node when it was displaced.
 * Confidence: medium
 * Notes: calls FUN_0037a978/0037aed8 (release) and thunk_FUN_00012568 (free). */
void sk_mr_send_word_replace_380864(unsigned long *out, unsigned long *slot,
                                    unsigned long w0, unsigned long w1)
{
    long *cur;          /* plVar5 */
    long *node;         /* plVar1 */
    unsigned long old;  /* uVar4 */
    long *released;     /* plVar1 */
    long a, b;          /* lVar2/lVar3 */

    old = *(unsigned long *)*slot;
    cL4_ref_acquire(old);
    cur = (long *)slot[1];
    node = cur;
    if (*cur != 1) {
        node = (long *)cL4_obj_alloc();
        a = cur[4];
        cur[4] = 0;
        b = node[4];
        node[4] = a;
        if (b != 0) cL4_free((void *)b, 0x20);
    }
    node[5] = w0;
    node[6] = w1;
    *out = (unsigned long)*(unsigned char *)((char *)slot + 0x11) | (unsigned long)node | 8;
    if (node != cur) {
        cL4_release(slot[1] + 0x10);
        cL4_ref_release(slot[1]);
        slot[1] = (unsigned long)node;
    }
    cL4_release(old);
}

/* FUN_00380930 @ 0x380930   (est. sk_mr_send_scan_match)
 * Ghidra: void FUN_00380930(long *param_1, ulong param_2, ulong param_3, long param_4)
 * Scans the message-wait/blocked table for a waiter whose registered word
 * sequence matches the caller's list, using the waiter-hash table
 * (FUN_0035b178) and a per-entry word comparison. On success returns (via
 * param_4) the matched slot; otherwise zeroes param_4. This is the
 * send-side waiter-match path of the MR copy engine.
 * Confidence: low
 * Notes: FUN_0035b178 = waiter iterator; local_e0 holds the incoming word. */
void sk_mr_send_scan_match_380930(long *list, unsigned long word, unsigned long count,
                                  long *out_slot)
{
    bool eq; unsigned long i; unsigned long cur; unsigned long w; unsigned long *pw;
    unsigned long hi; unsigned long lo; unsigned long idx; long slot; unsigned long u;
    long v; unsigned long *pslot; unsigned long k; unsigned long mask; unsigned long b;
    unsigned long stk_e0; unsigned long stk_d0; unsigned long stk_d8; unsigned char stack_c8[64];
    unsigned char stack_88[64]; long canary;

    canary = -0x2c8502b44bfffed6;
    stk_d0 = 0;
    stk_e0 = word;
    if (list[1] != 0) {
        v = 0;
        do {
            stk_d8 = *(unsigned long *)(*list + v * 8);
            cL4_mr_ctx_init2(stack_c8);
            stk_d0 = FUN_00380ad4(stack_c8, 0, stack_c8, stack_88, &stk_d0, &stk_d8);
            v = v + 1;
        } while (v != list[1]);
    }
    cur = 4;
    if (((word & 3) != 0) && ((unsigned char *)(word & 0xfffffffffffffffc) != 0)) {
        cur = (unsigned long)*(unsigned char *)(word & 0xfffffffffffffffc);
    }
    mask = -1L << (cur & 0x3f);
    cur = stk_d0 & (mask ^ 0xffffffffffffffff);
    if (cur < 2) cur = 1;
    slot = cL4_waiter_next(&stk_e0, cur, 2);
    if (slot != 0) {
        do {
            w = (unsigned long)(slot - 1);
            if (w < count) {
                pslot = *(unsigned long **)(out_slot + w * 8);
                u = list[1];
                if (u == *pslot) {
                    if (u == 0) {
                        cur = 0; out_slot = out_slot + w * 8; goto out;
                    }
                    i = 0; k = 1;
                    while (*(unsigned long *)(*list + i * 8) == pslot[i + 1]) {
                        eq = u == k;
                        i = k;
                        k = (unsigned long)((int)k + 1);
                        if (eq) goto match;
                    }
                }
            }
            cur = cur + 1 & ~mask;
            if (cur < 2) cur = 1;
            slot = cL4_waiter_next(&stk_e0, cur, 2);
        } while (slot != 0);
    }
    out_slot = 0;
    cur = cur & 0xffffffff;
out:
    if (canary != -0x2c8502b44bfffed6) {
        cL4_stack_fail();
    }
    return;
match:
    cur = 0;
    out_slot = out_slot + w * 8;
    goto out;
}

/* FUN_003810c4 @ 0x3810c4   (est. sk_mr_copy6_word_store)
 * Ghidra: undefined4 * FUN_003810c4(undefined4 *param_1, long *param_2, ...)
 * Message-register copy: consumes the source word range [param_3, param_4)
 * into the MR context param_1. When fewer than 16 bytes remain, copies the
 * partial tail into the running accumulator (FUN_0037e58c) or shifts it into
 * the next MR slot (FUN_0037e614); otherwise stores the full word directly.
 * Advances param_2 by the bytes consumed. Returns the next write pointer.
 * Confidence: medium
 * Notes: FUN_00117cc4 = bulk copy; FUN_0037e58c/0037e614 = SIMD copy begin. */
unsigned int *sk_mr_copy6_word_store_3810c4(unsigned int *ctx, long *adv,
                                             unsigned int *src, unsigned int *end,
                                             unsigned int w)
{
    unsigned int *next; long rem; unsigned int *p; long n; unsigned long acc[8];
    unsigned int local_34;

    next = src + 1;
    if (end < next) {
        n = (long)end - (long)src;
        local_34 = w;
        cL4_obj_copy_simple((long)src, (long)&local_34, n);
        if (*adv == 0) {
            cL4_simd_copy_begin(ctx, ctx, *(unsigned long *)(ctx + 0x1e));
            *(unsigned long *)(ctx + 0x12) = acc[1];
            *(unsigned long *)(ctx + 0x10) = acc[0];
            *(unsigned long *)(ctx + 0x16) = acc[3];
            *(unsigned long *)(ctx + 0x14) = acc[2];
            *(unsigned long *)(ctx + 0x1a) = acc[5];
            *(unsigned long *)(ctx + 0x18) = acc[4];
            *(unsigned long *)(ctx + 0x1c) = acc[6];
            n = 0x40;
        } else {
            cL4_simd_copy_loop(ctx + 0x10, ctx);
            n = *adv + 0x40;
        }
        *adv = n;
        next = (unsigned int *)((long)ctx + (4 - n));
        p = ctx;
        if (next <= end) {
            cL4_obj_copy_simple((long)ctx, (long)&local_34 + n);
            next = p;
        }
    } else {
        *src = w;
    }
    return next;
}

/* FUN_003885e4 @ 0x3885e4   (est. sk_type_lookup_check)
 * Ghidra: bool FUN_003885e4(undefined8, long, undefined8)
 * Reports whether the capability/metadata value in param_2 equals the resolved
 * word for param_3 (via thunk_FUN_00115080), returning false on any lookup
 * failure. A tiny equality gate used by the type-metadata cache.
 * Confidence: low
 * Notes: thunk_FUN_00115080 = cap resolve; thunk_FUN_00114e50 = validate. */
bool sk_type_lookup_check_3885e4(unsigned long a, long b, unsigned long c)
{
    bool eq; long w; int r;

    r = thunk_FUN_00114e50(a, c, b);
    if (r == 0) {
        w = thunk_FUN_00115080(c);
        eq = w == b;
    } else {
        eq = false;
    }
    return eq;
}

/* FUN_00388ef8 @ 0x388ef8   (est. sk_type_ctx_release)
 * Ghidra: undefined8 * FUN_00388ef8(undefined8 *param_1)
 * Tears down a per-thread type-decoder context block: releases the two
 * ownership objects (0x67c398 / 0x67c370 vtables) and clears the child pointer
 * flag. Returns the block.
 * Confidence: medium */
unsigned long *sk_type_ctx_release_388ef8(unsigned long *ctx)
{
    *ctx = 0x67c398;
    cL4_zone_get(ctx + 0x44);
    *ctx = 0x67c370;
    cL4_ipc_obj_publish((long *)ctx[3], 0, 0);
    if (ctx[5] != 0) *(unsigned char *)(ctx[5] + 0x30) = 0;
    return ctx;
}

/* FUN_00389130 @ 0x389130   (est. sk_type_ctx_init)
 * Ghidra: void FUN_00389130(undefined8 *param_1)
 * Initializes a fresh type-decoder context block: zeroes the 12 descriptor
 * words, installs a wait-queue head at +0x70 and clears the final slot, then
 * arms the object hardware-init hook (FUN_0036c3e0).
 * Confidence: medium */
void sk_type_ctx_init_389130(unsigned long *ctx)
{
    *ctx = 0; ctx[1] = 0; ctx[2] = 0; ctx[5] = 0; ctx[4] = 0;
    ctx[7] = 0; ctx[6] = 0; ctx[8] = 0; ctx[11] = 0; ctx[12] = 0; ctx[10] = 0;
    cL4_node_wait_init(ctx + 0xe, 0);
    ctx[0x10] = 0;
    cL4_obj_hw_init();
}

/* FUN_00389370 @ 0x389370   (est. sk_wordlist_append)
 * Ghidra: void FUN_00389370(long *param_1, undefined4 param_2)
 * Appends a 32-bit value to the growable word-list whose descriptor is
 * param_1 (list pointer at *param_1, count at param_1[1], capacity at
 * param_1[0xc] words). Grows via FUN_003a294c when the list is full.
 * Confidence: medium */
void sk_wordlist_append_389370(long *list, unsigned int w)
{
    unsigned long n;

    n = (unsigned long)*(unsigned int *)(list + 1);
    if (*(unsigned int *)((long)list + 0xc) <= *(unsigned int *)(list + 1)) {
        cL4_wordlist_grow(list, list + 2, n + 1, 4);   /* FUN_003a294c */
        n = (unsigned long)*(unsigned int *)(list + 1);
    }
    *(unsigned int *)(*list + n * 4) = w;
    *(int *)(list + 1) = (int)list[1] + 1;
}

/* FUN_00389910 @ 0x389910   (est. sk_type_lookup_dispatch2)
 * Ghidra: void FUN_00389910(undefined8, undefined8, long)
 * Type-lookup shim: forwards to FUN_00389940, collapsing a null length into a
 * zero-length request. The inner `param_3==0 && param_3==0` is a dead branch.
 * Confidence: low */
void sk_type_lookup_dispatch2_389910(unsigned long a, unsigned long b, long c)
{
    if ((c != 0) && (c == 0)) {
        sk_type_lookup_389940(a, b, 0, 0);
        return;
    }
    sk_type_lookup_389940(a, b, c, 0);
}

/* FUN_00389b4c @ 0x389b4c   (est. sk_type_lookup_dispatch3)
 * Ghidra: void FUN_00389b4c(undefined8, undefined8, undefined8)
 * Thin wrapper over FUN_00389940 (the full type-name lookup), forwarding all
 * three arguments unchanged.
 * Confidence: low */
void sk_type_lookup_dispatch3_389b4c(unsigned long a, unsigned long b, unsigned long c)
{
    sk_type_lookup_389940(a, b, c, 0);
}

/* FUN_00389940 @ 0x389940   (est. sk_type_lookup)
 * Ghidra: undefined8 FUN_00389940(undefined8, undefined8, undefined8, undefined8)
 * Core type-name lookup: builds a temporary metadata descriptor pair
 * (0x67b818 / 0x67b860 string buckets), invokes the generic lookup core
 * FUN_003895e0 with a zero error context, and converts the result into a
 * metadata pointer. On the "diagnostic logging enabled" path it prints the
 * `failed type lookup for ...` message through the logger (FUN_004b9ed8) and
 * returns null.
 * Confidence: medium
 * Notes: DAT_004f2710 read; local_190 flags the returned error kind. */
unsigned long sk_type_lookup_389940(unsigned long a, unsigned long b, unsigned long c,
                                    unsigned long d)
{
    unsigned int *pdiag; unsigned long r; unsigned long ctx[2]; unsigned int *pstack;
    unsigned long *slot; unsigned long *err; unsigned long *buf; unsigned long out;
    unsigned long (*fn[2])(unsigned long, int, unsigned long); short kind;
    unsigned int state[2]; unsigned long desc0; unsigned long desc1; unsigned char *pkeep;
    unsigned long meta; unsigned char stack[256]; unsigned long scratch; long canary;

    canary = -0x2c8502b44bfffed6;
    state[0] = 0;
    pstack = state;
    meta = DAT_004f2710;
    scratch = 0;
    slot = &ctx[1];
    ctx[1] = 0x67b818;
    buf = &ctx[0];
    ctx[0] = 0x67b860;
    pdiag = pstack;
    desc0 = c;
    desc1 = d;
    pkeep = stack;
    sk_type_lookup_core_3895e0(&out, 0, a, b, d, &ctx[1], &ctx[0]);
    cL4_release(&ctx[0]);
    cL4_release(&ctx[1]);
    if (kind == 1) {
        if (-1 < _DAT_006adee0) {
            cL4_log_printf(&DAT_006adee0, &DAT_003697c0, 0);
        }
        if (DAT_006aded1 == 1) {
            pdiag = (unsigned int *)fn;
            if (kind != 1) pdiag = (unsigned int *)&__thread_bss.cpusubtype;
            r = (*(unsigned long (**)(unsigned long, int, unsigned long))pdiag)(out, 0, 0);
            cL4_log_printf(0, s_failed_type_lookup_for____s___s_005d523f);
            (*(unsigned long (**)(unsigned long, int, unsigned long))pdiag)(out, 1, r);
            r = 0;
            goto out;
        }
    }
    r = out;
    if (kind != 0) r = 0;
out:
    if (kind == 1) (*fn[0])(out, 3, 0);
    if (pkeep != stack) thunk_FUN_00012568(0);
    if (canary != -0x2c8502b44bfffed6) cL4_stack_fail();
    return r;
}

/* FUN_00389b64 @ 0x389b64   (est. sk_type_lookup_quiet)
 * Ghidra: undefined8 FUN_00389b64(ulong, undefined8, undefined8, long, undefined8)
 * Variant of FUN_00389940 with a flag suppressed (param_1 & ~0x100) and an
 * explicit length. Same metadata-descriptor setup and error handling.
 * Confidence: low */
unsigned long sk_type_lookup_quiet_389b64(unsigned long flags, unsigned long a,
                                          unsigned long b, long len, unsigned long d)
{
    unsigned int *pdiag; unsigned long r; unsigned long ctx[2]; unsigned int *pstack;
    unsigned long *slot; unsigned long *err; unsigned long *buf; unsigned long out;
    unsigned long (*fn[2])(unsigned long, int, unsigned long); short kind;
    unsigned int state[2]; long desc0; unsigned long desc1; unsigned char *pkeep;
    unsigned long meta; unsigned char stack[256]; unsigned long scratch; long canary;

    if ((len != 0) && (len == 0)) len = 0;
    canary = -0x2c8502b44bfffed6;
    state[0] = 0;
    pstack = state;
    meta = DAT_004f2710;
    scratch = 0;
    slot = &ctx[1];
    ctx[1] = 0x67b8a8;
    buf = &ctx[0];
    ctx[0] = 0x67b8f0;
    pdiag = pstack;
    desc0 = len;
    desc1 = d;
    pkeep = stack;
    sk_type_lookup_core_3895e0(&out, flags & 0xfffffffffffffeff, a, b, d, &ctx[1], &ctx[0]);
    cL4_release(&ctx[0]);
    cL4_release(&ctx[1]);
    if (kind == 1) {
        if (-1 < _DAT_006adee0) cL4_log_printf(&DAT_006adee0, &DAT_003697c0, 0);
        if (DAT_006aded1 == 1) {
            pdiag = (unsigned int *)fn;
            if (kind != 1) pdiag = (unsigned int *)&__thread_bss.cpusubtype;
            r = (*(unsigned long (**)(unsigned long, int, unsigned long))pdiag)(out, 0, 0);
            cL4_log_printf(0, s_failed_type_lookup_for____s___s_005d523f);
            (*(unsigned long (**)(unsigned long, int, unsigned long))pdiag)(out, 1, r);
            r = 0;
            goto out;
        }
    }
    r = out;
    if (kind != 0) r = 0;
out:
    if (kind == 1) (*fn[0])(out, 3, 0);
    if (pkeep != stack) thunk_FUN_00012568(0);
    if (canary != -0x2c8502b44bfffed6) cL4_stack_fail();
    return r;
}
