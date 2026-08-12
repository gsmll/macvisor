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
extern void thunk_FUN_00012568(unsigned long, ...); /* free w/ size tag 0x12568 */
extern void cL4_stack_fail(void) __attribute__((noreturn));      /* FUN_0011d7e8 */
extern void cL4_ref_acquire(unsigned long obj);                  /* FUN_0037a48c */
extern void cL4_ref_release(unsigned long obj);                  /* FUN_0037aed8 */
extern void cL4_release(unsigned long obj);                      /* FUN_0037a978 */
extern unsigned long *cL4_obj_alloc(void);                       /* FUN_0037a7f8 */
extern void cL4_node_wait_init(unsigned long *wq, unsigned long v); /* FUN_0037a850 */
extern void cL4_obj_hw_init(void);                               /* FUN_0036c3e0 */
extern long *cL4_zone_get(long *obj);                            /* FUN_00362ea4 */
extern void cL4_ipc_obj_publish(long *d, long a, long b);        /* FUN_003a3814 */
extern void cL4_percpu_ctx_table(void *out);                     /* FUN_0036e878 */
extern long cL4_mr_ctx_init2(void *ctx);                         /* FUN_0037e528 */
extern void cL4_msg_free(void *msg);                             /* FUN_0037f9f8 */
extern unsigned long cL4_mr_copy6(unsigned long reg, unsigned long acc0, unsigned long n,
                                  unsigned long opts, unsigned long *src5, unsigned long *src6); /* FUN_00380ad4 */
extern void cL4_simd_copy_begin(void *ctx, void *p, unsigned long imm); /* FUN_0037e58c */
extern void cL4_simd_copy_loop(void *ctx, void *p);             /* FUN_0037e614 */
extern long cL4_obj_copy_simple(long dst, long src, unsigned long op); /* FUN_00117cc4 */
extern void cL4_obj_copy2(unsigned long *, unsigned long, unsigned long);   /* FUN_00117cc8 */
extern unsigned long FUN_00380ad4(void *, ...); /* MR copy6 0x380ad4 */
extern int cL4_waiter_next(unsigned long *word, unsigned long start, int mode); /* FUN_0035b178 */
extern unsigned long cL4_waiter_hash(unsigned long key);        /* FUN_0035b588 */
extern int thunk_FUN_00114e50(unsigned long a, unsigned long b, long c);
extern unsigned long thunk_FUN_00115080(unsigned long cap);
extern void cL4_wordlist_grow(long *list, long *slot, unsigned long n, unsigned int tag); /* FUN_003a294c */

/* Binary globals referenced by these bodies (declared extern; they live in the
 * kernel image at the given addresses). */
extern volatile unsigned long _DAT_006adee0;
#define DAT_006adee0 _DAT_006adee0
extern volatile unsigned char DAT_006aded1;
extern unsigned char DAT_003697c0[1];
extern unsigned long DAT_004f2710;
extern unsigned long _DAT_004f2700;
extern unsigned long uRam00000000004f2708;
extern unsigned long __thread_bss_dummy;
#define __thread_bss __thread_bss_dummy
extern volatile unsigned long _DAT_006c0970;
extern volatile unsigned long _DAT_006c0910;
extern volatile unsigned long _DAT_006c0900;
extern volatile unsigned long _DAT_006c08e0;
extern volatile unsigned long _DAT_006c08e4;
extern volatile unsigned long _DAT_006c08e8;
extern volatile unsigned long _DAT_006c08f0;
extern volatile unsigned long _DAT_006c0938;
extern volatile unsigned long _DAT_006c0940;
extern volatile unsigned long _DAT_006c0920;
extern volatile unsigned long _DAT_006c09e0;
extern volatile unsigned long _DAT_006c09d0;
extern volatile unsigned long _DAT_006c09d8;
extern volatile unsigned long _DAT_006c0a00;
extern unsigned long DAT_006c09e0;
extern unsigned long DAT_006c09d0;
extern unsigned long DAT_006c0a00;
extern unsigned long DAT_006c08e8;
extern unsigned long DAT_006c08f0;
extern unsigned long DAT_006c08e4;
extern unsigned long DAT_006c0940;
extern unsigned long DAT_006c0938;
extern unsigned long DAT_006c0920;
extern unsigned char DAT_0036e518[1];

/* Mangled-name / error string literals. */
extern const char s_failed_type_lookup_for____s___s_005d523f[];
extern const char s_unknown_error_005d5481[];
extern const char s_Demangling_failed_005d5260[];
extern const char s_NULL_type_but_no_error_provided_005d5272[];
extern const char s_This_entry_point_is_only_for_pac_005d5292[];
extern const char s_Cannot_demangle_a_free_standing_p_005d545c[];
extern const char s___mtx_init__handle_mutex____mtx__005d3f10[];
extern const char s___mtx_lock__handle_mutex__failed_005d3ee0[];
extern const char s_TypeDecoder_h__u__Node_kind__u___005d54b8[];
extern const char s_TypeDecoder_h__u__Node_kind__u___005d54f0[];
extern const char s_TypeDecoder_h__u__Node_kind__u___005d553f[];
extern const char s_TypeDecoder_h__u__Node_kind__u___005d558c[];
extern const char s_TypeDecoder_h__u__Node_kind__u___005d568b[];
extern const char s_TypeDecoder_h__u__Node_kind__u___005d5713[];
extern const char s_TypeDecoder_h__u__Node_kind__u___005d587a[];
extern const char s_TypeDecoder_h__u__Node_kind__u___005d5915[];
extern const char s_TypeDecoder_h__u__Node_kind__u___005d5989[];
extern const char s_TypeDecoder_h__u__Node_kind__u___005d59f4[];
extern const char s_TypeDecoder_h__u__Node_kind__u___005d5a51[];
extern const char s_Mangled_type_is_too_complex_005d548f[];
extern const char s_Node_is_NULL_005d54ab[];
extern const char s_is_not_requirement_list_005d5673[];
extern const char s_Metatype_ExistentialMetatype_Nod_005d55f9[];
extern const char s_Global_actor_node_is_missing_chi_005d56cd[];
extern const char s_Thrown_error_node_is_missing_chi_005d56f0[];
extern const char s_unexpected_kind_005d586a[];
extern const char s_unexpected_kind_or_no_index_005d59d8[];
extern const char s_not_enough_children_005d5640[];
extern const char s_no_children_005d55ed[];
extern const char s_no_children__005d54e3[];
extern const char s_failed_to_decode_protocol_type_005d5654[];
extern const char s_failed_to_decode_coroutine_kind_005d57c4[];
extern const char s_failed_to_decode_function_parame_005d57e4[];
extern const char s_failed_to_decode_function_result_005d5829[];
extern const char s_failed_to_decode_function_yields_005d5808[];
extern const char s_failed_to_decode_function_part_005d584b[];
extern const char s_expected_text_005d5763[];
extern const char s_expected_grandchildren_005d5771[];
extern const char s_expected_convention_name_005d5788[];
extern const char s_expected_type_list_005d58dd[];
extern const char s_expected_dependent_generic_signa_005d58f0[];
extern const char s_expected_layout_005d5964[];
extern const char s_unhandled_field_type_005d5974[];
extern const char s_pack_expansion_type_in_unsupport_005d58b1[];
extern const char s_advancePackExpansion___without_b_005d5db6[];
extern const char s_endPackExpansion___without_begin_005d5deb[];
extern const char s_wrong_node_kind_or_no_text_005d55d2[];
extern unsigned char DAT_005be7c0[1];
extern unsigned long DAT_004f2700;
extern unsigned long DAT_004f2710;
extern unsigned long DAT_004f2718;
extern unsigned long DAT_004f2740;
extern unsigned long DAT_004f27d0, DAT_004f27d8, DAT_004f27e0, DAT_004f27e8, DAT_004f27f0;
extern unsigned long DAT_004f27f8, DAT_004f2800, DAT_004f2808, DAT_004f2810, DAT_004f2818;
extern unsigned long DAT_004f2820, DAT_004f2828, DAT_004f2830, DAT_004f2838, DAT_004f2840;
extern unsigned long DAT_004f2848, DAT_004f2850, DAT_004f2858, DAT_004f2860, DAT_004f2868;
extern unsigned long DAT_004f2870, DAT_004f2878, DAT_004f2880, DAT_004f2888, DAT_004f2890;
extern unsigned long DAT_004f2898, DAT_004f28a0, DAT_004f28a8, DAT_004f28b0, DAT_004f28b8;
extern unsigned long DAT_004f28c0, DAT_004f28c8, DAT_004f28d0, DAT_004f28d8, DAT_004f28e0;
extern unsigned long DAT_004f28e8, DAT_004f28f0, DAT_004f2900[8];
extern void (*FUN_0037f9f8)(void);
extern void (*FUN_00397f0c)(void);
extern void (*FUN_00397fc0)(void);
extern void (*FUN_00398108)(void);
extern void (*FUN_00398074)(void);
extern unsigned long sk_type_metadata_get_3963b8(unsigned long, unsigned long, unsigned long);

/* Swift runtime TypeDecoder error / string-buffer primitives. */
extern void *cL4_strbuf_alloc(long size);                        /* FUN_00112db4 */
extern void *cL4_strbuf_print(void *buf, unsigned long v);       /* FUN_00112e8c */
extern unsigned long (*FUN_0037f9f4)(void); /* vtable slot 0x37f9f4 */
extern void cL4_log_printf(unsigned long a, unsigned long b);    /* FUN_004b9ed8 */
extern void cL4_diag_log(unsigned long *c, unsigned long *s, unsigned long x); /* FUN_003d3dd8 */
extern void cL4_printf2(unsigned long a, unsigned long b);       /* FUN_004b9ed8 */

/* In-slice forward declarations (defined later in this file). These are
 * opaque cross-references between the R50 decoder functions; declared
 * variadic so the reconstruction compiles against call sites whose exact
 * Ghidra signatures were not all recovered. */
extern unsigned long sk_type_lookup_389940(unsigned long, unsigned long, unsigned long, unsigned long);
extern void sk_type_lookup_core_3895e0(unsigned long *, unsigned long, long, unsigned long, unsigned long, void *, void *);
extern long sk_strbuf_copy_38ef98(long, void *);
extern long sk_strbuf_copy_38f020(long, void *);
extern void sk_type_resolve_38a518(unsigned long *, unsigned long, unsigned long, unsigned long *, unsigned long, unsigned long, unsigned long);
extern long sk_type_field_get_3a3430(unsigned long, ...);
extern void sk_type_field_set_3a3460(unsigned long, ...);
extern unsigned long sk_type_strfield_3a63f70(unsigned long, ...);
extern long sk_type_a32a0_3a32a0(unsigned long, ...);
extern void sk_type_decode_38f0a8(unsigned long *, unsigned long *, unsigned long *, unsigned long, unsigned long);
extern unsigned long FUN_00377dcc(unsigned long, ...);
extern void FUN_003a2578(unsigned long, ...);
extern void cL4_panic_big(unsigned long, ...);
extern void cL4_list_push_363f10(unsigned long, ...);
extern unsigned long sk_type_metadata_get_3963b8(unsigned long, ...);
extern void sk_type_materialize_exist_39517c(unsigned long, ...);
extern void sk_type_materialize_exist_3950a4(unsigned long, ...);
extern void sk_type_build_sig_395f3c(unsigned long, ...);
extern void sk_type_build_owned_395dec(unsigned long, ...);
extern void sk_type_generic_args_396440(unsigned long, ...);
extern void sk_type_build_bound_generic_396784(unsigned long, ...);
extern void sk_type_metadata_of_3bf904(unsigned long, ...);
extern void sk_type_unpack_pair_37364c(unsigned long, ...);
extern void sk_type_materialize_394c40(unsigned long, ...);
extern void sk_type_materialize_397358(unsigned long, ...);
extern void sk_type_build_pair_397e94(unsigned long, ...);
extern void sk_type_decode_sig_394404(unsigned long, ...);
extern void sk_type_build_func_394724(unsigned long, ...);
extern unsigned long sk_type_parse_signature_395638(unsigned long, ...);
extern void sk_type_build_protocol_3973e4(unsigned long, ...);
extern void sk_type_decode_sig_394734(unsigned long, ...);
extern void sk_type_build_func_3952c4(unsigned long, ...);
extern void sk_type_decl_record_39779c(unsigned long, ...);
extern void sk_type_push8_39780c(unsigned long, ...);
extern void sk_type_field_push_39787c(unsigned long, ...);
extern unsigned long sk_type_realloc_38d9b4(unsigned long, ...);
extern void sk_type_flatpair_3978b0(unsigned long, ...);
extern void sk_type_push98_397998(unsigned long, ...);
extern void sk_type_build_bound_397a98(unsigned long, ...);
extern unsigned long sk_type_lookup_field_398f40(unsigned long, ...);
extern void sk_type_materialize_req_3972cc(unsigned long, ...);
extern void sk_type_materialize_req2_3971e8(unsigned long, ...);
extern void sk_type_build_reqlist_396f78(unsigned long, ...);
extern void sk_type_65184_365184(unsigned long, ...);
extern void sk_type_pushreq_39951c(unsigned long, ...);
extern long sk_type_decode_param_396aec(unsigned long, ...);
extern long sk_type_decode_result_396d48(unsigned long, ...);
extern void sk_type_wordlist_grow_3a294c(unsigned long, ...);
extern void sk_type_build_decl_39779c(unsigned long, ...);
extern cL4_w16_t sk_type_name_split_38cbb8(unsigned long, ...);
extern long sk_type_waiter_scan_38c640(unsigned long, ...);
extern unsigned long sk_type_waiter_hash2_38c750(unsigned long, ...);
extern unsigned long sk_type_capcmp_387fbc(unsigned long, ...);
extern void sk_type_dbltbl_grow_38d90c(unsigned long, ...);
extern unsigned long sk_type_dbltbl_hash_38d6e4(unsigned long, ...);
extern void sk_type_insert_38c3ac(unsigned long, ...);
extern cL4_w16_t sk_type_read_3a31d8(unsigned long, ...);
extern unsigned long sk_type_cap_build_3a32a0(unsigned long, ...);
extern void sk_type_wordlist_append_389370(unsigned long, ...);
extern void FUN_0038e214(unsigned long, ...);
extern void FUN_0038e458(unsigned long, ...);
extern void FUN_0038e624(unsigned long, ...);
extern void FUN_0038e7f0(unsigned long, ...);
extern void FUN_0038ece8(unsigned long, ...);
extern void FUN_0038d9fc(unsigned long, ...);
extern void sk_type_dbltbl_op_38d90c(unsigned long, ...);
extern void sk_type_release_obj(unsigned long, ...);

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
            cL4_obj_copy2((unsigned long *)ctx, (unsigned long)&local_34 + n, 0);
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
    cL4_release(ctx[0]);
    cL4_release(ctx[1]);
    if (kind == 1) {
        if (-1 < _DAT_006adee0) {
            cL4_diag_log(&DAT_006adee0, &DAT_003697c0, 0);
        }
        if (DAT_006aded1 == 1) {
            pdiag = (unsigned int *)fn;
            if (kind != 1) pdiag = (unsigned int *)&__thread_bss_dummy;
            r = (*(unsigned long (**)(unsigned long, int, unsigned long))pdiag)(out, 0, 0);
            cL4_log_printf(0, (unsigned long)s_failed_type_lookup_for____s___s_005d523f);
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
    cL4_release(ctx[0]);
    cL4_release(ctx[1]);
    if (kind == 1) {
        if (-1 < _DAT_006adee0) cL4_diag_log(&DAT_006adee0, &DAT_003697c0, 0);
        if (DAT_006aded1 == 1) {
            pdiag = (unsigned int *)fn;
            if (kind != 1) pdiag = (unsigned int *)&__thread_bss_dummy;
            r = (*(unsigned long (**)(unsigned long, int, unsigned long))pdiag)(out, 0, 0);
            cL4_log_printf(0, (unsigned long)s_failed_type_lookup_for____s___s_005d523f);
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

/* FUN_00389da0 @ 0x389da0   (est. sk_mangled_scan_valid)
 * Ghidra: undefined8 FUN_00389da0(byte *param_1, long param_2)
 * Validates a mangled-name prefix: every byte of the length-limited run must
 * be printable (>= 0x20). When the whole run passes, performs a type lookup
 * (FUN_003895e0) over the region and returns the resolved metadata or the
 * error code. Returns 0 for any control character.
 * Confidence: low */
unsigned long sk_mangled_scan_valid_389da0(unsigned char *s, long len)
{
    long n; unsigned char *p; unsigned long r; unsigned char stk_88[24];
    unsigned long ctx; unsigned char stk_68[24]; unsigned long out; unsigned long (*fn)(unsigned long, int, unsigned long);
    short kind; long canary;

    canary = -0x2c8502b44bfffed6;
    n = len;
    p = s;
    do {
        if (n == 0) {
            ctx = 0;
            stk_88[0] = 0;
            sk_type_lookup_core_3895e0(&out, 0, (long)s, len, 0, stk_68, stk_88);
            if (kind == 1) {
                fn(out, 3, 0);
                r = 0;
            } else {
                r = 0;
                if (kind == 0) r = out;
            }
            cL4_release((unsigned long)stk_88);
            cL4_release((unsigned long)stk_68);
            if (canary == -0x2c8502b44bfffed6) return r;
            cL4_stack_fail();
        }
        if (0xffffffe0 < *p - 0x20) {
            r = 0;
            if (canary == -0x2c8502b44bfffed6) return r;
            cL4_stack_fail();
        }
        n = n - 1;
        p = p + 1;
    } while (true);
}

/* FUN_003895e0 @ 0x3895e0   (est. sk_type_lookup_core)
 * Ghidra: void FUN_003895e0(undefined8 *param_1, undefined8 param_2, long param_3,
 *                           ulong param_4, undefined8 param_5, undefined8 param_6,
 *                           undefined8 param_7)
 * The generic type-lookup dispatcher. It sets up the decoder context
 * (0x67b938 object + string buckets from FUN_0038ef98/0038f020), splits the
 * mangled name at its first '.' separator into module + base parts via the
 * 0xa3/0x67 field lookups (FUN_00363f70 / FUN_003a3430 / FUN_003a3460), then
 * drives the metadata resolver FUN_0038a518. Any empty/too-short input falls
 * to the "unknown error" path. Returns its result through param_1/param_2.
 * Confidence: medium
 * Notes: the 0x67b938 object vtable; _DAT_004f2700/_004f2708 read. */
void sk_type_lookup_core_3895e0(unsigned long *out, unsigned long flags, long name,
                                unsigned long len, unsigned long err, void *b6,
                                void *b7)
{
    unsigned long w; bool dot; long p; unsigned long q; unsigned long r; unsigned long s;
    unsigned long t; unsigned long u; unsigned char b08[32]; unsigned char b28[32];
    unsigned char ae8[32]; unsigned long ctx; unsigned char *pkeep; unsigned long *pstack;
    unsigned long desc; unsigned long res; long v; unsigned long a; unsigned char a98;
    unsigned long a90; unsigned long a88; unsigned long a80; unsigned long a78; unsigned long a70;
    unsigned long a68; unsigned long a60; unsigned long a58; unsigned long a50; unsigned long a48;
    unsigned long a40; unsigned long a38; unsigned long a30; unsigned long a28; unsigned long a20;
    unsigned long a18; unsigned long a10; unsigned long a08; unsigned long a00; unsigned long g98;
    unsigned long g90; unsigned long g88; unsigned long g80; unsigned long g78; unsigned long g70;
    unsigned long g68; unsigned long g60; unsigned long g58; unsigned long g50; unsigned long g48;
    unsigned long g40; unsigned long g38; unsigned long g30; unsigned long g28; unsigned long g20;
    unsigned long g18; unsigned long g10; unsigned long g08; unsigned long g00; unsigned long f98;
    unsigned long f90; unsigned long f88; unsigned long f80; unsigned long f78; unsigned long f70;
    unsigned long f68; unsigned long f60; unsigned long f58; unsigned long f50; unsigned long f48;
    unsigned long f40; unsigned long f38; unsigned long f30; unsigned long f28; unsigned long f20;
    unsigned long f18; unsigned long f10; unsigned long f08; unsigned long f00; unsigned int e90;
    unsigned char e88[24]; unsigned long e60; unsigned char e58[2048]; unsigned long canary;

    canary = -0x2c8502b44bfffed6;
    sk_strbuf_copy_38ef98((long)b08, b6);
    sk_strbuf_copy_38f020((long)b28, b7);
    a78 = uRam00000000004f2708;
    a80 = _DAT_004f2700;
    v = 0;
    a98 = 0;
    e60 = 0;
    a88 = 0;
    a80 = 0;
    a70 = 0;
    a58 = 0;
    a60 = 0;
    a50 = 0;
    a48 = 0;
    a40 = 0;
    a38 = 0;
    a30 = 0;
    a28 = 0;
    a20 = 0;
    a18 = 0;
    a10 = 0;
    a08 = 0;
    a00 = 0;
    g98 = 0; g90 = 0; g88 = 0; g80 = 0; g78 = 0; g70 = 0; g68 = 0; g60 = 0;
    g58 = 0; g50 = 0; g48 = 0; g40 = 0; g38 = 0; g30 = 0; g28 = 0; g20 = 0;
    g18 = 0; g10 = 0; g08 = 0; g00 = 0;
    f98 = 0; f90 = 0; f88 = 0; f80 = 0; f78 = 0; f70 = 0; f68 = 0; f60 = 0;
    f58 = 0; f50 = 0; f48 = 0; f40 = 0; f38 = 0; f30 = 0; f28 = 0; f20 = 0;
    f18 = 0; f10 = 0; f08 = 0; f00 = 0;
    e90 = 0;
    pkeep = e58;
    pstack = &a90;
    ctx = 0x67b938;
    if (len == 0) goto unknown;
    q = 0xffffffffffffffff;
    r = 1;
    t = 0;
    do {
        s = r;
        if (*(unsigned char *)(name + t) == 0x2e) {
            dot = q != 0xffffffffffffffff;
            q = t;
            if (dot) goto unknown;
        } else if (*(unsigned char *)(name + t) < 0x20) goto unknown;
        r = (unsigned long)((int)s + 1);
        t = s;
    } while (s < len);
    if (q == 0xffffffffffffffff) goto unknown;
    p = sk_type_field_get_3a3430((unsigned long)&ctx, 0x19);
    w = len;
    if (q <= len) w = q;
    r = sk_type_strfield_3a63f70((unsigned long)&ctx, 0xa3, (unsigned long)name, w);
    w = len;
    if (q + 1 <= len) w = q + 1;
    s = sk_type_strfield_3a63f70((unsigned long)&ctx, 0x67, (unsigned long)(name + w), len - w);
    sk_type_field_set_3a3460((unsigned long)p, r, (unsigned long)&ctx);
    sk_type_field_set_3a3460((unsigned long)p, s, (unsigned long)&ctx);
    /* fall through to resolution */
    sk_type_resolve_38a518((unsigned long (*)[16])out, flags, (unsigned long)&ctx, (unsigned long *)&ctx, err, (unsigned long)&a90, (unsigned long)ae8);
    cL4_release((unsigned long)ae8);
    cL4_release((unsigned long)&a90);
    goto done;
unknown:
    a90 = 0x67b7d0;
    pstack = &ctx;
    res = sk_type_a32a0_3a32a0((unsigned long)&ctx, (unsigned long)name, len, (unsigned long)&a90);
    cL4_zone_get((long *)&a90);
    if (res == 0) {
        *(unsigned char *)(out + 2) = 0;
        *out = (unsigned long)s_unknown_error_005d5481;
        out[1] = (unsigned long)FUN_0037f9f4;
        *(unsigned short *)(out + 3) = 1;
        goto done;
    }
    sk_strbuf_copy_38ef98((long)&a90, b08);
    sk_strbuf_copy_38f020((long)ae8, b28);
    sk_type_resolve_38a518((unsigned long (*)[16])out, flags, (unsigned long)&ctx, (unsigned long *)&ctx, err, (unsigned long)&a90, (unsigned long)ae8);
    cL4_release((unsigned long)ae8);
    cL4_release((unsigned long)&a90);
done:
    ctx = 0x67c398;
    cL4_zone_get((long *)e88);
    ctx = 0x67c370;
    cL4_ipc_obj_publish((long *)a80, 0, 0);
    if (v != 0) *(unsigned char *)(v + 0x30) = 0;
    cL4_release((unsigned long)b28);
    cL4_release((unsigned long)b08);
    if (canary != -0x2c8502b44bfffed6) cL4_stack_fail();
}

/* FUN_0038ef98 @ 0x38ef98   (est. sk_strbuf_copy)
 * Ghidra: long FUN_0038ef98(long param_1, long *param_2)
 * Copies a Swift string-buffer object from param_2 into the slot param_1,
 * handling the three storage kinds: unowned-empty (zeroed), owned-inline
 * (keeps the buffer at param_1 and notifies via the object's +0x18 vtable
 * slot), and shared-owner (dereferences the owner's +0x10 slot).
 * Confidence: medium */
long sk_strbuf_copy_38ef98(long dst, void *srcp)
{
    long *owner; unsigned long v; long *src = (long *)srcp;

    owner = (long *)src[3];
    if (owner == (long *)0) {
        *(unsigned long *)(dst + 0x18) = 0;
    } else if (owner == src) {
        *(long *)(dst + 0x18) = dst;
        ((void (*)(long *, long))((*(unsigned long **)src[3])[3]))(src, dst);
    } else {
        v = ((unsigned long (*)(void))((*(unsigned long **)owner)[2]))();
        *(unsigned long *)(dst + 0x18) = v;
    }
    return dst;
}

/* FUN_0038f020 @ 0x38f020   (est. sk_strbuf_copy2)
 * Ghidra: long FUN_0038f020(long param_1, long *param_2)
 * Identical storage-kind dispatch to FUN_0038ef98 (shared string-copy
 * helper); a separate symbol for the second buffer in each pair.
 * Confidence: medium */
long sk_strbuf_copy_38f020(long dst, void *srcp)
{
    long *owner; unsigned long v; long *src = (long *)srcp;

    owner = (long *)src[3];
    if (owner == (long *)0) {
        *(unsigned long *)(dst + 0x18) = 0;
    } else if (owner == src) {
        *(long *)(dst + 0x18) = dst;
        ((void (*)(long *, long))((*(unsigned long **)src[3])[3]))(src, dst);
    } else {
        v = ((unsigned long (*)(void))((*(unsigned long **)owner)[2]))();
        *(unsigned long *)(dst + 0x18) = v;
    }
    return dst;
}

/* FUN_0038a518 @ 0x38a518   (est. sk_type_resolve)
 * Ghidra: void FUN_0038a518(undefined1 (*param_1)[16], undefined8 param_2,
 *                           undefined8 param_3, undefined8 *param_4, undefined8 param_5,
 *                           undefined8 param_6, undefined8 param_7)
 * Resolves a parsed type node into concrete metadata. For the 0x13a "direct"
 * node kind it invokes the node's own resolve callback and packages the result
 * into the 16-byte output pair. Otherwise it hands the node to the big
 * metadata decoder FUN_0038f0a8, mapping the returned kind: 1 -> error node
 * (extract message via vtable +2), 0 with nonnull metadata -> demangled value
 * (via FUN_00377dcc), otherwise the "cannot demangle a free-standing pack" /
 * "NULL type" error strings.
 * Confidence: medium
 * Notes: FUN_0038f0a8 = the recursive type decoder; 0x13a = direct kind. */
void sk_type_resolve_38a518(unsigned long *out, unsigned long flags, unsigned long node,
                            unsigned long *ctx, unsigned long err, unsigned long b6,
                            unsigned long b7)
{
    /* out is the 3-word result slot {value, vtable, kind}; the decompile models
     * it as undefined1[16] with kind at +2 (short). */
    long r; unsigned long v; char *msg; unsigned char s138[32]; unsigned char s158[32];
    unsigned long meta; unsigned long (*fn)(unsigned long, int, unsigned long);
    short kind; unsigned char s100[32]; unsigned char se0[32]; unsigned long c0;
    unsigned char sb8[32]; unsigned char s98[32]; unsigned char s78;
    long v70; long v68; long v60; long canary;

    canary = -0x2c8502b44bfffed6;
    sk_strbuf_copy_38ef98((long)s138, (void *)b6);
    sk_strbuf_copy_38f020((long)s158, (void *)b7);
    if (*(short *)(ctx + 2) == 0x13a) {
        r = (*(unsigned long (**)(unsigned long))(*ctx))(flags);
        *(unsigned short *)(out + 2) = 0;
        *(long *)out = r;
        out[1] = 0;
        s78 = 0;
        if (r == 0) {
            *(char **)out = (char *)s_unknown_error_005d5481;
            out[1] = (unsigned long)FUN_0037f9f4;
            *(unsigned short *)(out + 2) = 1;
        }
        goto out;
    }
    sk_strbuf_copy_38ef98((long)se0, (void *)s138);
    sk_strbuf_copy_38f020((long)s100, (void *)s158);
    c0 = node;
    sk_strbuf_copy_38ef98((long)sb8, (void *)se0);
    sk_strbuf_copy_38f020((long)s98, (void *)s100);
    s78 = 0; v68 = 0; v60 = 0; v70 = 0;
    cL4_release((unsigned long)s100);
    cL4_release((unsigned long)se0);
    sk_type_decode_38f0a8(&meta, &c0, ctx, 0, 0);
    if (kind == 0) {
        if (meta == 0) goto null_err;
        if ((meta & 1) == 0) {
            *(unsigned long *)out = FUN_00377dcc(flags);
            *(unsigned short *)(out + 2) = 0;
            out[1] = s78;
            if (*(unsigned long *)out == 0) {
                *(char **)out = (char *)s_unknown_error_005d5481;
                out[1] = (unsigned long)FUN_0037f9f4;
                *(unsigned short *)(out + 2) = 1;
            }
            goto fin;
        }
        *(unsigned short *)(out + 2) = 1;
        msg = (char *)s_Cannot_demangle_a_free_standing_p_005d545c;
err_set:
        *(char **)out = msg;
        out[1] = (unsigned long)FUN_0037f9f4;
    } else {
        if (kind != 1) {
null_err:
            *(unsigned short *)(out + 2) = 1;
            msg = (char *)s_NULL_type_but_no_error_provided_005d5272;
            goto err_set;
        }
        *(unsigned short *)(out + 2) = 1;
        out[1] = (unsigned long)fn;
        v = fn(meta, 2, 0);
        *(unsigned long *)out = v;
    }
fin:
    if (kind == 1) fn(meta, 3, 0);
    if (v70 != 0) {
        v68 = v70;
        thunk_FUN_00012568((unsigned long)v70, (unsigned long)(v60 - v70));
    }
    cL4_release((unsigned long)s98);
    cL4_release((unsigned long)sb8);
out:
    cL4_release((unsigned long)s158);
    cL4_release((unsigned long)s138);
    if (canary != -0x2c8502b44bfffed6) cL4_stack_fail();
}

/* FUN_0038f0a8 @ 0x38f0a8   (est. sk_type_decode)
 * Ghidra: void FUN_0038f0a8(long *param_1, long *param_2, ushort *param_3, ulong param_4)
 * The recursive Swift runtime type-decoder: walks a Demangle-tree node graph
 * (param_3 is the current node) and materializes the concrete type metadata
 * for param_2's decode context, writing the result {value, error-info} pair
 * into param_1. The node kind (param_3[8]) selects the handling: leaf
 * metadata kinds (0x57/0x172/0x173 direct materialization), composite kinds
 * (0x47/0x9a/0xca/0xcb existential + type-list folding via 0xf7 0xf8 kind
 * tables), generic bindings (0xaf/0x17/0xea), protocol/requirement lists
 * (0xdf, 0xde), and the coroutine/function-signature node kinds (0x6b-0x7f:
 * coroutine kind 0x78, function params/results/yields/parts 0x7b-0x7f).
 * Every error path builds a TypeDecoder error descriptor via FUN_00111890
 * (0x28/0x30 alloc) with the `TypeDecoder.h: <node kind>` string, sets
 * param_1[2]=1 (error) and a vtable in param_1[1]. Depth is capped at 0x400
 * (too-complex error). Unreachable blocks at 0x39390c/0x390ebc were removed
 * by the decompiler; type propagation did not settle.
 * Confidence: medium
 * Notes: recursion bounded by param_4 (depth); helper callees 0x3895e0-style
 *   node decoders, 0x39xxxx materializers; DAT_005be7c0 = null text sentinel. */
void sk_type_decode_38f0a8(unsigned long *out, unsigned long *ctx, unsigned long *node,
                           unsigned long depth, unsigned long flag)
{
    char c; short s; unsigned int u; unsigned char *pb; bool b5; bool b6; int i7;
    long l8; unsigned long **pp9; unsigned long *pu10; unsigned long *pu11;
    unsigned long u13; unsigned int u14; unsigned int u15; unsigned short *pu16;
    unsigned long u17; char *pc18; void (*pc19)(unsigned long, int, unsigned long);
    short *ps20; unsigned int *pu21; unsigned char b22; unsigned char u23;
    unsigned long *pu24; unsigned short *pu25; unsigned short *pu26; unsigned long u27;
    unsigned long u28; short *ps29; unsigned char *pu30; unsigned int u31; long *pl32;
    unsigned long u33; unsigned int *pd34; long l35; unsigned int u36; unsigned long u37;
    unsigned long u38; unsigned long *pp39; unsigned short *pu40; int i41;
    unsigned long **pp42; unsigned short u43; unsigned int u44; long *pl45; unsigned long u46;
    unsigned int u47; unsigned char *pu48; long l49; short *ps50; unsigned long u51;
    unsigned long u53; unsigned long rv[16]; unsigned long **local_410;
    unsigned char *local_408; char *local_3f0; unsigned long *local_3d8; unsigned long local_3d0;
    long local_3c8; unsigned long **local_3c0; unsigned long **local_3b8; unsigned long **local_3b0[6];
    unsigned char *local_380; unsigned long **local_378; unsigned char local_370[16];
    unsigned long **local_360; unsigned long **stk_358; unsigned long **appc_350[4];
    unsigned long **local_330; unsigned long **local_328; short local_320[64];
    unsigned long **local_2a0; unsigned long **stk_298; unsigned long **local_290[16];
    unsigned long **local_210; unsigned long **stk_208; unsigned long **local_200;
    unsigned long **local_1f8; unsigned long local_1e8; char c1e1; unsigned long **local_100;
    unsigned long **stk_f8; unsigned long local_f0; long canary;

    canary = -0x2c8502b44bfffed6;
    if (0x400 < (unsigned int)depth) {
too_complex:
        *(unsigned short *)(out + 2) = 1;
        pc18 = (char *)s_Mangled_type_is_too_complex_005d548f;
err_set:
        *out = (unsigned long)pc18;
        out[1] = (unsigned long)FUN_0037f9f4;
        goto fin;
    }
    pu48 = (unsigned char *)&DAT_005be7c0;
dispatch:
    if (node == 0) {
        *(unsigned short *)(out + 2) = 1;
        pc18 = (char *)s_Node_is_NULL_005d54ab;
        goto err_set;
    }
    u43 = ((unsigned short *)node)[8];
    u44 = (unsigned int)u43;
    u15 = (unsigned int)u43;
    u36 = (unsigned int)u43;
    i41 = (int)depth;
    if (u43 < 0x77) {
        /* ---- node kinds 0x00-0x76 ---- */
        if (0x3e < u43) {
            if (0x54 < u43) {
                if (u36 == 0x65) {
                    b22 = (unsigned char)((unsigned short *)node)[9];
                    if (b22 - 1 < 2) { node = *(unsigned short **)node; goto follow_child; }
                    if (b22 == 5) {
                        if (*(int *)(node + 4) != 0) { node = *(unsigned short **)node; goto f2fc; }
                        u47 = 0;
                    } else if (b22 != 3) {
                        u47 = 0;
                    } else {
                        u47 = *(unsigned int *)(node + 4);
                        pu48 = *(unsigned char **)node;
                    }
                    pu10 = (unsigned long *)cL4_alloc(0x28, 0x1050c401ab4594e);
                    *pu10 = (unsigned long)s_TypeDecoder_h__u__Node_kind__u___005d54b8;
                    u13 = DAT_004f28f0;
                    goto err_28;
                }
                if (u36 != 0x55) {
                    if (u44 != 0x57) goto case_c;
                    pp9 = (unsigned long **)sk_type_metadata_get_3963b8(*ctx, 0, 0);
                    *(unsigned short *)(out + 2) = 0;
                    *out = (unsigned long)pp9;
                    goto joined_r8c8;
                }
                u37 = 0; u47 = 0;
                b22 = (unsigned char)((unsigned short *)node)[9];
                pu48 = (unsigned char *)&DAT_005be7c0;
                if (2 < b22) {
                    if (b22 == 3) { u37 = 0; u47 = *(unsigned int *)(node + 4); pu48 = *(unsigned char **)node; }
                    else if (b22 == 5) {
                        u37 = (unsigned long)*(unsigned int *)(node + 4);
                        if (1 < *(unsigned int *)(node + 4)) { pu26 = *(unsigned short **)node; goto l92654; }
                        u47 = 0;
                    }
                    goto l91b14;
                }
                pu48 = (unsigned char *)&DAT_005be7c0;
                if (b22 == 1) { u47 = 0; u37 = 1; goto l91b14; }
                pu26 = (unsigned short *)node;
                if (b22 != 2) goto l91b14;
l92654:
                sk_type_decode_38f0a8(&local_2a0, ctx, *(unsigned long *)pu26, i41 + 1, 1);
                if ((short)local_290[0] == 1) {
                    pp9 = 0;
                    *(unsigned short *)(out + 2) = 1;
                    out[1] = (unsigned long)stk_298;
                    *out = (unsigned long)local_2a0;
                    pc19 = FUN_0037f9f8;
                    local_2a0 = 0;
                    stk_298 = (unsigned long **)FUN_0037f9f8;
                    goto l93930;
                }
                stk_208 = (unsigned long **)DAT_004f2710;
                stk_f8 = (unsigned long **)DAT_004f2710;
                if ((char)((unsigned short *)node)[9] == 2) {
l926f4:
                    pu10 = *(unsigned long **)(node + 4);
                } else {
                    if (((char)((unsigned short *)node)[9] == 5) && (1 < *(unsigned int *)(node + 4))) {
                        node = *(unsigned short **)node; goto l926f4;
                    }
                    pu10 = 0;
                }
                u43 = *(unsigned short *)(pu10 + 2);
                local_210 = &local_200;
                local_100 = &local_f0;
                if (u43 == 0x56) {
                    sk_type_build_sig_395f3c(pu10, &local_210, &local_100, *ctx);
                    *out = (unsigned long)s_unknown_error_005d5481;
                    out[1] = (unsigned long)FUN_0037f9f4;
                    *(unsigned short *)(out + 2) = 1;
                } else {
                    if (*(char *)((long)pu10 + 0x12) == 3) {
                        u47 = *(unsigned int *)(pu10 + 1);
                        pu48 = (unsigned char *)*pu10;
                    } else { u47 = 0; pu48 = (unsigned char *)&DAT_005be7c0; }
                    pu10 = (unsigned long *)cL4_alloc(0x28, 0x1050c401ab4594e);
                    *pu10 = (unsigned long)s_TypeDecoder_h__u__Node_kind__u___005d54b8;
                    *(unsigned int *)(pu10 + 1) = 899;
                    *(unsigned int *)((long)pu10 + 0xc) = (unsigned int)u43;
                    *(unsigned int *)(pu10 + 2) = u47;
                    pu10[3] = (unsigned long)pu48;
                    pu10[4] = (unsigned long)s_is_not_requirement_list_005d5673;
                    *(unsigned short *)(out + 2) = 1;
                    out[1] = (unsigned long)FUN_00397f0c;
                    pu11 = (unsigned long *)cL4_alloc(0x28, 0x1050c401ab4594e);
                    u13 = *pu10; u53 = pu10[3]; u28 = pu10[2];
                    pu11[1] = pu10[1]; *pu11 = u13; pu11[3] = u53; pu11[2] = u28;
                    pu11[4] = pu10[4];
                    *out = (unsigned long)pu11;
                    cL4_free(pu10, 0x28);
                }
                if (local_100 != &local_f0) cL4_free(0, 0);
                if ((unsigned long **)local_210 != &local_200) cL4_free(0, 0);
                pp9 = local_2a0;
                pc19 = (void (*)(unsigned long, int, unsigned long))stk_298;
                s = (short)local_290[0];
                goto joined_32e0;
            }
            if (u36 != 0x46 && 0x45 < u43) {
                if (u15 != 0x47) {
                    if (u15 == 0x54) goto case_b;
                    goto case_c;
                }
l8f7ec:
                u47 = 0;
                b22 = (unsigned char)((unsigned short *)node)[9];
                pu48 = (unsigned char *)&DAT_005be7c0;
                pu26 = (unsigned short *)node;
                if (2 < b22) {
                    if (b22 == 3) { u47 = *(unsigned int *)(node + 4); pu48 = *(unsigned char **)node; }
                    else if (b22 == 5) {
                        if (1 < *(unsigned int *)(node + 4)) { pu25 = *(unsigned short **)node; goto l8f9bc; }
                        if (*(unsigned int *)(node + 4) != 0) { l8 = 0; goto l91644; }
                        u47 = 0; pu48 = (unsigned char *)&DAT_005be7c0;
                    }
                    goto l90cd8;
                }
                if (b22 == 1) { l8 = 0; goto l91648; }
                if (b22 != 2) goto l90cd8;
                l8 = 0;
l91644:
                pu26 = *(unsigned short **)node;
l91648:
                u13 = *(unsigned long *)(pu26 + l8 * 4);
l9164c:
                sk_type_decode_38f0a8(&local_210, ctx, u13, i41 + 1, 1);
                if ((short)local_200 == 1) {
                    *(unsigned short *)(out + 2) = 1;
                    out[1] = (unsigned long)stk_208;
                    *out = (unsigned long)local_210;
                    stk_208 = (unsigned long **)FUN_0037f9f8;
                    local_210 = 0;
                } else {
                    u43 = ((unsigned short *)node)[8];
                    if (u43 == 0x47) {
                        pp9 = local_210;
                        if ((short)local_200 != 0) pp9 = 0;
                        sk_type_materialize_exist_39517c(out, pp9);
                    } else if (u43 == 0x9a) {
                        pp9 = local_210;
                        if ((short)local_200 != 0) pp9 = 0;
                        sk_type_materialize_exist_3950a4(out, pp9);
                    } else {
                        if ((char)((unsigned short *)node)[9] == 3) {
                            u47 = *(unsigned int *)(node + 4);
                            pu48 = *(unsigned char **)node;
                        } else { u47 = 0; pu48 = (unsigned char *)&DAT_005be7c0; }
                        pu10 = (unsigned long *)cL4_alloc(0x28, 0x1050c401ab4594e);
                        *pu10 = (unsigned long)s_TypeDecoder_h__u__Node_kind__u___005d54b8;
                        *(unsigned int *)(pu10 + 1) = 0x335;
                        *(unsigned int *)((long)pu10 + 0xc) = (unsigned int)u43;
                        *(unsigned int *)(pu10 + 2) = u47;
                        pu10[3] = (unsigned long)pu48;
                        pu10[4] = (unsigned long)s_Metatype_ExistentialMetatype_Nod_005d55f9;
                        *(unsigned short *)(out + 2) = 1;
                        out[1] = (unsigned long)FUN_00397f0c;
                        pu11 = (unsigned long *)cL4_alloc(0x28, 0x1050c401ab4594e);
                        u13 = *pu10; u53 = pu10[3]; u28 = pu10[2];
                        pu11[1] = pu10[1]; *pu11 = u13; pu11[3] = u53; pu11[2] = u28;
                        pu11[4] = pu10[4];
                        *out = (unsigned long)pu11;
                        cL4_free(pu10, 0x28);
                    }
                }
                goto l9391c;
            }
            if (1 < u15 - 0x42) {
                if (u15 == 0x3f) goto case_19;
                goto case_c;
            }
case_b:
            u37 = 0; u47 = 0;
            b22 = (unsigned char)((unsigned short *)node)[9];
            u17 = (unsigned long)b22;
            pu48 = (unsigned char *)&DAT_005be7c0;
            if (2 < b22) {
                if (b22 == 3) { u37 = 0; u47 = *(unsigned int *)(node + 4); pu48 = *(unsigned char **)node; }
                else if (b22 == 5) {
                    u37 = (unsigned long)*(unsigned int *)(node + 4);
                    if (1 < *(unsigned int *)(node + 4)) goto l8f78c;
                    u47 = 0;
                }
                goto l8f8e8;
            }
            pu48 = (unsigned char *)&DAT_005be7c0;
            if (b22 == 1) { u47 = 0; u37 = 1; goto l8f8e8; }
            if (b22 != 2) goto l8f8e8;
l8f78c:
            if (u36 - 0xaf < 2) u37 = 0x10000;
            else if (u36 == 0x17) u37 = 0x30000;
            else if (u44 == 0xea) u37 = 0x20000;
            else u37 = 0;
            if (b22 == 5) {
                pu26 = *(unsigned short **)node;
                if (*(int *)(node + 4) == 0) pd34 = (unsigned int *)&__thread_bss.ncmds;
                else pd34 = (unsigned int *)(*(long *)pu26 + 0x10);
                b5 = (short)*pd34 == 0x18;
                b6 = *(short *)(*(long *)(pu26 + (unsigned long)b5 * 4) + 0x10) != 0x89;
                u36 = 0x10; if (b6) u36 = 0;
                u15 = (unsigned int)b5;
                if (!b6) u15 = u15 + 1;
                u51 = (unsigned long)u15;
                s = *(short *)(*(long *)(pu26 + u51 * 4) + 0x10);
                pu25 = (unsigned short *)pu26;
            } else {
                pu26 = *(unsigned short **)node;
                b5 = *(short *)(*(long *)(node + (unsigned long)(pu26[8] == 0x18) * 4) + 0x10) != 0x89;
                u36 = 0x10; if (b5) u36 = 0;
                u15 = (unsigned int)(pu26[8] == 0x18);
                if (!b5) u15 = u15 + 1;
                u51 = (unsigned long)u15;
                s = *(short *)(*(long *)(node + u51 * 4) + 0x10);
                pu25 = (unsigned short *)node;
            }
            if (s == 0x45) {
                if (b22 == 2) {
l90818:
                    if (u17 <= u51) goto l90844;
                    pu10 = *(unsigned long **)(pu25 + u51 * 4);
                } else {
                    if (b22 == 5) { u17 = (unsigned long)*(unsigned int *)(node + 4); goto l90818; }
l90844:
                    pu10 = 0;
                }
                b22 = *(unsigned char *)((long)pu10 + 0x12);
                if (1 < b22 - 1) {
                    if (b22 == 5) {
                        if (*(int *)(pu10 + 1) != 0) { pu10 = (unsigned long *)*pu10; goto l9086c; }
                        u43 = *(unsigned short *)(pu10 + 2);
                        goto l922b0;
                    } else {
                        u43 = *(unsigned short *)(pu10 + 2);
                        if (b22 != 3) goto l922b0;
                        u47 = *(unsigned int *)(pu10 + 1);
                        pu48 = (unsigned char *)*pu10;
                    }
                    pu10 = (unsigned long *)cL4_alloc(0x28, 0x1050c401ab4594e);
                    *pu10 = (unsigned long)s_TypeDecoder_h__u__Node_kind__u___005d54b8;
                    *(unsigned int *)(pu10 + 1) = 0x3d9;
                    *(unsigned int *)((long)pu10 + 0xc) = (unsigned int)u43;
                    *(unsigned int *)(pu10 + 2) = u47;
                    pc18 = (char *)s_Global_actor_node_is_missing_chi_005d56cd;
l93190:
                    pu10[3] = (unsigned long)pu48;
                    pu10[4] = (unsigned long)pc18;
                    *(unsigned short *)(out + 2) = 1;
                    out[1] = (unsigned long)FUN_00397f0c;
                    pu11 = (unsigned long *)cL4_alloc(0x28, 0x1050c401ab4594e);
                    u13 = *pu10; u53 = pu10[3]; u28 = pu10[2];
                    pu11[1] = pu10[1]; *pu11 = u13; pu11[3] = u53; pu11[2] = u28;
                    pu11[4] = pu10[4];
                    *out = (unsigned long)pu11;
                    goto l92984;
                }
l9086c:
                sk_type_decode_38f0a8(out, ctx, *pu10, i41 + 1, 1);
                if ((short)out[2] != 1) {
                    if ((short)out[2] == 0) l8 = *out; else l8 = 0;
                    u51 = (unsigned long)((int)u51 + 1);
                    u17 = (unsigned long)(unsigned char)((unsigned short *)node)[9];
                    goto l91044;
                }
                goto fin;
            }
            if (*(short *)(*(long *)(pu25 + u51 * 4) + 0x10) == 0x87) {
                u36 = u36 | 2;
            } else {
                pu25 = (unsigned short *)node;
                if (b22 == 5) pu25 = pu26;
                if (*(short *)(*(long *)(pu25 + u51 * 4) + 0x10) != 0x88) { l8 = 0; goto l91044; }
                u36 = u36 | 4;
            }
            l8 = 0;
            u51 = (unsigned long)((int)u51 + 1);
l91044:
            i7 = (int)u17;
            b5 = 1 < i7 - 1U;
            pu26 = (unsigned short *)node;
            if (b5) pu26 = *(unsigned short **)node;
            if (*(short *)(*(long *)(pu26 + u51 * 4) + 0x10) == 0x46) {
                pu26 = (unsigned short *)node;
                if (b5) pu26 = *(unsigned short **)node;
                u44 = **(unsigned char **)(pu26 + u51 * 4) - 100 >> 1 & 0x7f;
                u15 = (**(unsigned char **)(pu26 + u51 * 4) - 100) * 0x80;
                if ((u44 | u15 & 0xff) < 8) l49 = *(long *)(&DAT_004f2900 + ((unsigned long)(u44 | u15) & 0xff) * 8);
                else l49 = 0;
                u51 = (unsigned long)((int)u51 + 1);
            } else l49 = 0;
            pu26 = (unsigned short *)node;
            if (b5) pu26 = *(unsigned short **)node;
            if (*(short *)(*(long *)(pu26 + u51 * 4) + 0x10) == 0x11e) {
                l35 = 0;
l910f0:
                u51 = (unsigned long)((int)u51 + 1);
                u46 = 0x1000000;
            } else {
                pu26 = (unsigned short *)node;
                if (b5) pu26 = *(unsigned short **)node;
                if (*(short *)(*(long *)(pu26 + u51 * 4) + 0x10) == 0x11f) {
                    if (i7 == 1) {
l9233c:
                        if (u17 <= u51) goto l92358;
                        pu26 = (unsigned short *)node;
                        if (b5) pu26 = *(unsigned short **)node;
                        pu10 = *(unsigned long **)(pu26 + u51 * 4);
                    } else {
                        if (i7 == 5) { u17 = (unsigned long)*(unsigned int *)(node + 4); goto l9233c; }
                        if (i7 == 2) { u17 = 2; goto l9233c; }
l92358:
                        pu10 = 0;
                    }
                    b22 = *(unsigned char *)((long)pu10 + 0x12);
                    if (1 < b22 - 1) {
                        if (b22 == 5) {
                            if (*(int *)(pu10 + 1) != 0) { pu10 = (unsigned long *)*pu10; goto l9238c; }
                            u43 = *(unsigned short *)(pu10 + 2);
                            goto l93148;
                        } else {
                            u43 = *(unsigned short *)(pu10 + 2);
                            if (b22 != 3) goto l93148;
                            u47 = *(unsigned int *)(pu10 + 1);
                            pu48 = (unsigned char *)*pu10;
                        }
                        pu10 = (unsigned long *)cL4_alloc(0x28, 0x1050c401ab4594e);
                        *pu10 = (unsigned long)s_TypeDecoder_h__u__Node_kind__u___005d54b8;
                        *(unsigned int *)(pu10 + 1) = 0x413;
                        *(unsigned int *)((long)pu10 + 0xc) = (unsigned int)u43;
                        *(unsigned int *)(pu10 + 2) = u47;
                        pc18 = (char *)s_Thrown_error_node_is_missing_chi_005d56f0;
                        goto l93190;
                    }
l9238c:
                    sk_type_decode_38f0a8(out, ctx, *pu10, i41 + 1, 1);
                    if ((short)out[2] != 1) {
                        if ((short)out[2] == 0) l35 = *out; else l35 = 0;
                        u36 = u36 | 1;
                        u17 = (unsigned long)(unsigned char)((unsigned short *)node)[9];
                        goto l910f0;
                    }
                    goto fin;
                }
                l35 = 0;
                u46 = 0;
            }
            i7 = (int)u17;
            if (i7 == 1) {
                u47 = 0;
                u15 = 2;
                if (*(short *)(*(long *)(node + (unsigned long)(*(short *)(*(long *)(node + u51 * 4) + 0x10) == 0x44) * 4) + 0x10) == 0x11d) u15 = 3;
                u36 = (unsigned int)((unsigned short *)node)[8];
                pu48 = (unsigned char *)&DAT_005be7c0;
                u17 = 1;
            } else {
                u44 = (unsigned int)u51;
                if (i7 == 2) {
                    b5 = *(short *)(*(long *)(node + u51 * 4) + 0x10) == 0x44;
                    if (b5) u44 = u44 + 1;
                    u51 = 0x40000000; if (!b5) u51 = 0;
                    b5 = *(short *)(*(long *)(node + (unsigned long)u44 * 4) + 0x10) == 0x11d;
                    if (b5) u44 = u44 + 1;
                    u27 = 0x20000000; if (!b5) u27 = 0;
                    u38 = 0; if (l49 != 0) u38 = 0x8000000;
                    b6 = true; u31 = 2;
                } else {
                    b6 = false;
                    u31 = *(unsigned int *)(node + 4);
                    b5 = *(short *)(*(long *)(*(long *)node + u51 * 8) + 0x10) == 0x44;
                    if (b5) u44 = u44 + 1;
                    u51 = 0x40000000; if (!b5) u51 = 0;
                    b5 = *(short *)(*(long *)(*(long *)node + (unsigned long)u44 * 8) + 0x10) == 0x11d;
                    if (b5) u44 = u44 + 1;
                    u27 = 0x20000000; if (!b5) u27 = 0;
                    u38 = 0; if (l49 != 0) u38 = 0x8000000;
                }
                u15 = u44 + 2;
                if (u15 <= u31) {
                    local_330 = (unsigned long **)((unsigned long)local_330 & 0xffffffffffffff00);
                    stk_208 = (unsigned long **)DAT_004f2710;
                    if (i7 == 2) {
l91b50:
                        if (u17 <= u44) goto l91b70;
                        pu26 = (unsigned short *)node;
                        if (!b6) pu26 = *(unsigned short **)node;
                        u13 = *(unsigned long *)(pu26 + (unsigned long)u44 * 4);
                    } else {
                        if (i7 == 5) { u17 = (unsigned long)*(unsigned int *)(node + 4); goto l91b50; }
l91b70:
                        u13 = 0;
                    }
                    local_210 = &local_200;
                    sk_type_generic_args_396440(&local_100, ctx, u13, i41 + 1, &local_210, &local_330);
                    pp42 = stk_f8;
                    pp12 = local_100;
                    pp9 = stk_208;
                    if ((char)local_f0 == 1) {
                        *(unsigned short *)(out + 2) = 1;
                        out[1] = (unsigned long)stk_f8;
                        l8 = ((unsigned long (*)(unsigned long, int, unsigned long))stk_f8)(local_100, 2, 0);
                        *out = l8;
l92810:
                        ((void (*)(unsigned long, int, unsigned long))pp42)(pp12, 3, 0);
                    } else {
                        u43 = ((unsigned short *)node)[8];
                        u17 = 0x4000000;
                        if (((u43 != 0x42) && (u43 != 0x54)) && (u17 = 0x4000000, u43 != 0xb0)) u17 = 0;
                        b22 = (unsigned char)((unsigned short *)node)[9];
                        if (b22 == 2) {
                            u33 = 2;
l92700:
                            if (u33 <= u44 + 1) goto l92724;
                            if (1 < b22 - 1) node = *(unsigned short **)node;
                            u13 = *(unsigned long *)(node + (unsigned long)(u44 + 1) * 4);
                        } else {
                            if (b22 == 5) { u33 = (unsigned long)*(unsigned int *)(node + 4); goto l92700; }
l92724:
                            u13 = 0;
                        }
                        u33 = (unsigned long)local_330 & 0xff;
                        sk_type_decode_38f0a8(&local_2a0, ctx, u13, i41 + 1, 0);
                        if ((short)local_290[0] == 1) {
                            *(unsigned short *)(out + 2) = 1;
                            out[1] = (unsigned long)stk_298;
                            *out = (unsigned long)local_2a0;
                            local_2a0 = 0;
                            stk_298 = (unsigned long **)FUN_0037f9f8;
l927f0:
                            ((void (*)(unsigned long, int, unsigned long))stk_298)(local_2a0, 3, 0);
                        } else {
                            u27 = u46 | u37 | u38 | u51 | (unsigned long)pp9 & 0xf9ffffff | u33 << 0x19 | u17 | u27;
                            if (u36 != 0) u27 = u27 | 0x80000000;
                            pp9 = local_2a0;
                            if ((short)local_290[0] != 0) pp9 = 0;
                            sk_type_build_bound_generic_396784(out, local_210, (unsigned long)stk_208 & 0xffffffff, pp9, u27, u36, l49, l8, l35);
                            if ((short)local_290[0] == 1) goto l927f0;
                        }
                        pp42 = stk_f8;
                        pp12 = local_100;
                        if ((char)local_f0 == 1) goto l92810;
                    }
                    if ((unsigned long **)local_210 != &local_200) goto l9366c;
                    goto fin;
                }
                u36 = (unsigned int)((unsigned short *)node)[8];
                if (i7 != 2) {
                    if (i7 == 5) u17 = (unsigned long)*(unsigned int *)(node + 4);
                    else {
                        if (i7 == 3) {
                            u17 = 0; u47 = *(unsigned int *)(node + 4); pu48 = *(unsigned char **)node;
                            goto l9216c;
                        }
                        u17 = 0;
                    }
                }
                u47 = 0;
                pu48 = (unsigned char *)&DAT_005be7c0;
            }
l9216c:
            pu10 = (unsigned long *)cL4_alloc(0x30, 0x1050c40363580a0);
            *pu10 = (unsigned long)s_TypeDecoder_h__u__Node_kind__u___005d5713;
            *(unsigned int *)(pu10 + 1) = 0x436;
            *(unsigned int *)((long)pu10 + 0xc) = u36;
            *(unsigned int *)(pu10 + 2) = u47;
            pu10[3] = (unsigned long)pu48;
            pu10[4] = u17;
            *(unsigned int *)(pu10 + 5) = u15;
            *(unsigned short *)(out + 2) = 1;
            out[1] = 0x3989b8;
            pu11 = (unsigned long *)cL4_alloc(0x30, 0x1050c40363580a0);
            u13 = *pu10; u53 = pu10[3]; u28 = pu10[2];
            pu11[1] = pu10[1]; *pu11 = u13; pu11[3] = u53; pu11[2] = u28;
            u13 = pu10[4]; pu11[5] = pu10[5]; pu11[4] = u13;
            *out = (unsigned long)pu11;
            if (canary == -0x2c8502b44bfffed6) { u13 = 0x30; goto l929a4; }
            goto canary_fail;
        }
        if (0x23 < u44 - 0xb) {
            if (u36 == 3) {
                b22 = (unsigned char)((unsigned short *)node)[9];
                if (b22 - 1 < 2) { node = *(unsigned short **)node; goto follow_child; }
                if (b22 == 5) {
                    if (*(int *)(node + 4) != 0) { node = *(unsigned short **)node; goto f2fc; }
                    u47 = 0;
                } else {
                    if (b22 != 3) { u47 = 0; goto l9031c; }
                    u47 = *(unsigned int *)(node + 4); pu48 = *(unsigned char **)node;
                }
                pu10 = (unsigned long *)cL4_alloc(0x28, 0x1050c401ab4594e);
                *pu10 = (unsigned long)s_TypeDecoder_h__u__Node_kind__u___005d54b8;
                u13 = DAT_004f2880;
                goto l90354;
l9031c:
                u47 = 0;
                pu10 = (unsigned long *)cL4_alloc(0x28, 0x1050c401ab4594e);
                *pu10 = (unsigned long)s_TypeDecoder_h__u__Node_kind__u___005d54b8;
                u13 = DAT_004f2880;
                goto l90354;
            }
            if (u36 != 0x3b) goto case_c;
            u37 = 0; u47 = 0;
            b22 = (unsigned char)((unsigned short *)node)[9];
            pu48 = (unsigned char *)&DAT_005be7c0;
            if (b22 < 3) {
                if (b22 == 1) goto l90c6c;
                pu48 = (unsigned char *)&DAT_005be7c0;
                if (b22 == 2) { u47 = 0; u37 = 2; }
            } else if (b22 == 3) {
                u37 = 0; u47 = *(unsigned int *)(node + 4); pu48 = *(unsigned char **)node;
            } else if (b22 == 5) {
                u37 = (unsigned long)*(unsigned int *)(node + 4);
                if (*(unsigned int *)(node + 4) == 1) goto l90c68;
                u47 = 0;
            }
            pu10 = (unsigned long *)cL4_alloc(0x28, 0x1050c400dfe80cb);
            *pu10 = (unsigned long)s_TypeDecoder_h__u__Node_kind__u___005d568b;
            u13 = DAT_004f28b8;
l925e4:
            pu10[1] = u13;
            *(unsigned int *)(pu10 + 2) = u47;
            pu10[3] = (unsigned long)pu48;
            goto l925f0;
        }
        switch (u44) {
        default:
            goto case_b;
        case 0xc: case 0x13: case 0x15: case 0x18: case 0x1a: case 0x1b: case 0x1c:
        case 0x1d: case 0x1e: case 0x1f: case 0x20: case 0x21: case 0x22: case 0x23:
        case 0x25: case 0x26: case 0x28: case 0x29: case 0x2a: case 0x2b: case 0x2c:
            goto case_c;
        case 0xd: case 0xe: case 0xf: case 0x11: case 0x12:
            u37 = 0; u47 = 0;
            b22 = (unsigned char)((unsigned short *)node)[9];
            pu48 = (unsigned char *)&DAT_005be7c0;
            if (b22 < 3) {
                pu48 = (unsigned char *)&DAT_005be7c0;
                if (b22 == 1) { u47 = 0; u37 = 1; }
                else {
                    pu26 = (unsigned short *)node;
                    if (b22 == 2) {
                        l8 = *(long *)(pu26 + 4);
                        goto l8f5c0;
                    }
                }
            } else if (b22 == 3) {
                u37 = 0; u47 = *(unsigned int *)(node + 4); pu48 = *(unsigned char **)node;
            } else if (b22 == 5) {
                u37 = (unsigned long)*(unsigned int *)(node + 4);
                if (1 < *(unsigned int *)(node + 4)) {
                    if (1 < *(unsigned int *)(node + 4)) { pu26 = *(unsigned short **)node; goto l8f5bc; }
                    l8 = 0; goto l8f5c0;
                }
                u47 = 0;
            }
            pu10 = (unsigned long *)cL4_alloc(0x28, 0x1050c400dfe80cb);
            *pu10 = (unsigned long)s_TypeDecoder_h__u__Node_kind__u___005d54f0;
            u14 = 0x2c9;
            goto l8ffe4;
        case 0x10:
            b22 = (unsigned char)((unsigned short *)node)[9];
            if (b22 < 3) {
                if (b22 != 2) {
                    if (b22 == 1) { u47 = 0; pu48 = (unsigned char *)&DAT_005be7c0; u37 = 1; }
                    else { u37 = 0; u47 = 0; pu48 = (unsigned char *)&DAT_005be7c0; }
                    goto l90d60;
                }
            } else {
                if (b22 != 5) {
                    if (b22 != 3) { u37 = 0; u47 = 0; pu48 = (unsigned char *)&DAT_005be7c0; goto l90d60; }
                    u37 = 0; u47 = *(unsigned int *)(node + 4); pu48 = *(unsigned char **)node;
                    goto l90d60;
                }
                u37 = (unsigned long)*(unsigned int *)(node + 4);
                if (*(unsigned int *)(node + 4) < 2) { u47 = 0; pu48 = (unsigned char *)&DAT_005be7c0; }
                else node = *(unsigned short **)node;
            }
            pu10 = *(unsigned long **)(node + 4);
            c = *(char *)((long)pu10 + 0x12);
            if (c == 1) { node = (unsigned short *)*pu10; goto l8f3e4; }
            if (c == 5) {
                u37 = (unsigned long)*(unsigned int *)(pu10 + 1);
                if (*(unsigned int *)(pu10 + 1) == 1) { pu10 = (unsigned long *)*pu10; node = (unsigned short *)*pu10; goto l8f3e4; }
                u43 = *(unsigned short *)(pu10 + 2);
                u36 = (unsigned int)u43; u47 = 0; pu48 = (unsigned char *)&DAT_005be7c0;
            } else if (c == 2) {
                u47 = 0; u36 = (unsigned int)*(unsigned short *)(pu10 + 2);
                pu48 = (unsigned char *)&DAT_005be7c0; u37 = 2;
            } else {
                u43 = *(unsigned short *)(pu10 + 2);
                u36 = (unsigned int)u43;
                if (c != 3) { u37 = 0; u47 = 0; pu48 = (unsigned char *)&DAT_005be7c0; }
                else { u37 = 0; u47 = *(unsigned int *)(pu10 + 1); pu48 = (unsigned char *)*pu10; }
            }
            pu10 = (unsigned long *)cL4_alloc(0x28, 0x1050c400dfe80cb);
            *pu10 = (unsigned long)s_TypeDecoder_h__u__Node_kind__u___005d553f;
            *(unsigned int *)(pu10 + 1) = 0x305;
            *(unsigned int *)((long)pu10 + 0xc) = u36;
            *(unsigned int *)(pu10 + 2) = u47;
            pu10[3] = (unsigned long)pu48;
            pu10[4] = u37;
            goto l925f4;
        case 0x14:
            sk_type_metadata_of_3bf904(&local_210, node, 0);
            i41 = (int)local_210;
            if ((int)local_210 == 0) {
                stk_298 = *(unsigned long ***)(node + 4);
                local_2a0 = *(unsigned long **)node;
                sk_type_unpack_pair_37364c(&local_100, &local_2a0);
                pp9 = local_1f8;
                if (-1 < (long)c1e1) pp9 = &local_1f8;
                if (-1 < c1e1) local_1f0 = (long)c1e1;
                sk_type_materialize_394c40(out, pp9, local_1f0);
            } else {
                u43 = ((unsigned short *)node)[8];
                if ((char)((unsigned short *)node)[9] == 3) { u47 = *(unsigned int *)(node + 4); pu48 = *(unsigned char **)node; }
                else { u47 = 0; pu48 = (unsigned char *)&DAT_005be7c0; }
                u14 = local_200[0];
                pu10 = (unsigned long *)cL4_alloc(0x28, 0x1050c400dfe80cb);
                *pu10 = (unsigned long)s_TypeDecoder_h__u__Node_kind__u___005d558c;
                *(unsigned int *)(pu10 + 1) = 0x30f;
                *(unsigned int *)((long)pu10 + 0xc) = (unsigned int)u43;
                *(unsigned int *)(pu10 + 2) = u47;
                pu10[3] = (unsigned long)pu48;
                *(int *)(pu10 + 4) = i41;
                *(unsigned int *)((long)pu10 + 0x24) = u14;
                *(unsigned short *)(out + 2) = 1;
                out[1] = (unsigned long)FUN_00398108;
                pu11 = (unsigned long *)cL4_alloc(0x28, 0x1050c400dfe80cb);
                u13 = *pu10; u53 = pu10[3]; u28 = pu10[2];
                pu11[1] = pu10[1]; *pu11 = u13; pu11[3] = u53; pu11[2] = u28;
                pu11[4] = pu10[4];
                *out = (unsigned long)pu11;
                cL4_free(pu10, 0x28);
            }
            if (-1 < c1e1) goto fin;
            u37 = (CONCAT17(c1e1, local_1e8) & 0x7fffffffffffffff);
            goto l91030;
        case 0x16:
            u37 = 0; u47 = 0;
            b22 = (unsigned char)((unsigned short *)node)[9];
            pu48 = (unsigned char *)&DAT_005be7c0;
            if (2 < b22) {
                if (b22 == 3) { u37 = 0; u47 = *(unsigned int *)(node + 4); pu48 = *(unsigned char **)node; }
                else if (b22 == 5) {
                    u37 = (unsigned long)*(unsigned int *)(node + 4);
                    if (1 < *(unsigned int *)(node + 4)) { pu26 = *(unsigned short **)node; goto l924d0; }
                    u47 = 0;
                }
                goto l91a64;
            }
            pu48 = (unsigned char *)&DAT_005be7c0;
            if (b22 == 1) { u47 = 0; u37 = 1; goto l91a64; }
            pu26 = (unsigned short *)node;
            if (b22 != 2) goto l91a64;
l924d0:
            sk_type_decode_38f0a8(&local_210, ctx, *(unsigned long *)pu26, i41 + 1, 1);
            if ((short)local_200 != 1) {
                if ((char)((unsigned short *)node)[9] == 2) { l8 = *(long *)(node + 4); }
                else {
                    if (((char)((unsigned short *)node)[9] == 5) && (1 < *(unsigned int *)(node + 4))) { node = *(unsigned short **)node; l8 = *(long *)(node + 4); }
                    else l8 = 0;
                }
                sk_type_decode_38f0a8(&local_100, ctx, l8, i41 + 1, 1);
                if ((short)local_f0 == 1) {
                    *(unsigned short *)(out + 2) = 1;
                    out[1] = (unsigned long)stk_f8;
                    *out = (unsigned long)local_100;
                    local_100 = 0;
                    stk_f8 = (unsigned long **)FUN_0037f9f8;
                } else {
                    pp9 = local_210; if ((short)local_200 != 0) pp9 = 0;
                    pp12 = local_100; if ((short)local_f0 != 0) pp12 = 0;
                    sk_type_build_pair_397e94(out, pp9, pp12);
                    if ((short)local_f0 != 1) goto l9391c;
                }
                ((void (*)(unsigned long, int, unsigned long))stk_f8)(local_100, 3, 0);
                goto l9391c;
            }
            goto l92550;
        case 0x19:
case_19:
            local_100 = 0;
            local_2a0 = 0;
            sk_type_decode_sig_394404(&local_210, ctx, node, depth, &local_100, &local_2a0);
            pp12 = stk_208;
            pp9 = local_210;
            if ((char)local_200 == 1) {
                *(unsigned short *)(out + 2) = 1;
                out[1] = (unsigned long)stk_208;
                l8 = ((unsigned long (*)(unsigned long, int, unsigned long))stk_208)(local_210, 2, 0);
                *out = l8;
                ((void (*)(unsigned long, int, unsigned long))pp12)(pp9, 3, 0);
            } else {
                sk_type_build_func_394724(out, *ctx, local_100, local_2a0);
            }
            goto fin;
        case 0x24:
        case 0x2d:
            b22 = (unsigned char)((unsigned short *)node)[9];
            if (b22 < 3) {
                if (b22 == 2) { node = *(unsigned short **)(node + 4); goto l8f3e4; }
                if (b22 != 1) { u37 = 0; u47 = 0; pu48 = (unsigned char *)&DAT_005be7c0; }
                else { u47 = 0; pu48 = (unsigned char *)&DAT_005be7c0; u37 = 1; }
            } else if (b22 == 5) {
                u37 = (unsigned long)*(unsigned int *)(node + 4);
                if (1 < *(unsigned int *)(node + 4)) { node = *(unsigned short **)node; goto l8f3dc; }
                u47 = 0; pu48 = (unsigned char *)&DAT_005be7c0;
            } else {
                if (b22 != 3) { u37 = 0; u47 = 0; pu48 = (unsigned char *)&DAT_005be7c0; }
                else { u37 = 0; u47 = *(unsigned int *)(node + 4); pu48 = *(unsigned char **)node; }
            }
            pu10 = (unsigned long *)cL4_alloc(0x28, 0x1050c400dfe80cb);
            *pu10 = (unsigned long)s_TypeDecoder_h__u__Node_kind__u___005d54f0;
            u13 = DAT_004f2848;
            goto l91948;
        case 0x27:
            pu26 = (unsigned short *)node;
            pu25 = (unsigned short *)node;
            if ((1 < (unsigned char)((unsigned short *)node)[9] - 1) &&
                (pu25 = *(unsigned short **)node, pu26 = pu25, (unsigned char)((unsigned short *)node)[9] != 5)) {
                pu26 = (unsigned short *)node;
            }
            l8 = sk_type_metadata_get_3963b8(*ctx, **(unsigned int **)pu25, **(unsigned int **)(pu26 + 4));
            *(unsigned short *)(out + 2) = 0;
            *out = l8;
            goto fin;
        case 0x2e:
            u37 = 0; u47 = 0;
            b22 = (unsigned char)((unsigned short *)node)[9];
            pu48 = (unsigned char *)&DAT_005be7c0;
            if (2 < b22) {
                if (b22 == 3) { u37 = 0; u47 = *(unsigned int *)(node + 4); pu48 = *(unsigned char **)node; }
                else if (b22 == 5) {
                    u37 = (unsigned long)*(unsigned int *)(node + 4);
                    if (1 < *(unsigned int *)(node + 4)) { pu26 = *(unsigned short **)node; goto l92528; }
                    u47 = 0;
                }
                goto l91ab4;
            }
            pu48 = (unsigned char *)&DAT_005be7c0;
            if (b22 == 1) { u47 = 0; u37 = 1; goto l91ab4; }
            pu26 = (unsigned short *)node;
            if (b22 != 2) goto l91ab4;
l92528:
            sk_type_decode_38f0a8(&local_210, ctx, *(unsigned long *)pu26, i41 + 1, 1);
            if ((short)local_200 == 1) goto l92550;
            if ((char)((unsigned short *)node)[9] == 2) { pu10 = *(unsigned long **)(node + 4); }
            else {
                if (((char)((unsigned short *)node)[9] == 5) && (1 < *(unsigned int *)(node + 4))) { node = *(unsigned short **)node; pu10 = *(unsigned long **)(node + 4); }
                else pu10 = 0;
            }
            b22 = *(unsigned char *)((long)pu10 + 0x12);
            pu11 = pu10;
            if (1 < b22 - 1) pu11 = (unsigned long *)*pu10;
            stk_298 = (unsigned long **)((long *)*pu11)[1];
            local_2a0 = *(unsigned long **)*pu11;
            if (b22 != 2) {
                if ((b22 != 5) || (*(unsigned int *)(pu10 + 1) < 2)) {
                    sk_type_unpack_pair_37364c(&local_100, &local_2a0);
                    sk_type_materialize_397358(out);
                    goto l9391c;
                }
                pu10 = (unsigned long *)*pu10;
            }
            l8 = sk_type_parse_signature_395638(ctx, pu10[1], i41 + 1);
            if (l8 == 0) {
                *out = (unsigned long)s_unknown_error_005d5481;
                out[1] = (unsigned long)FUN_0037f9f4;
                *(unsigned short *)(out + 2) = 1;
            } else {
                sk_type_unpack_pair_37364c(&local_100, &local_2a0);
                pp9 = local_100;
                if (-1 < (long)local_f0) pp9 = (unsigned long **)(long)(unsigned char)local_f0;
                pp12 = stk_f8;
                if (-1 < (long)local_f0) pp12 = (unsigned long **)(long)(unsigned char)local_f0;
                pp42 = local_210; if ((short)local_200 != 0) pp42 = 0;
                sk_type_build_protocol_3973e4(out, pp9, pp12, pp42, l8);
            }
l9391c:
            pp9 = local_210;
            pc19 = (void (*)(unsigned long, int, unsigned long))stk_208;
            s = (short)local_200;
            goto joined_32e0;
        }
l925f0:
        pu10[4] = u37;
l925f4:
        u13 = 0x1050c400dfe80cb;
        *(unsigned short *)(out + 2) = 1;
        pc19 = FUN_00397fc0;
        goto l92960;
    }
    /* ---- node kinds >= 0x77 ---- */
    if (u36 != 0x134 && 0x133 < u43) {
        if (u36 != 0x13a && 0x139 < u43) {
            if (0x16a < u43) {
                if (u36 == 0x16b) {
                    local_210 = (unsigned long **)sk_type_parse_signature_395638(ctx, node, i41 + 1);
                    if (local_210 == 0) {
                        u43 = ((unsigned short *)node)[8];
                        if ((char)((unsigned short *)node)[9] == 3) { u47 = *(unsigned int *)(node + 4); pu48 = *(unsigned char **)node; }
                        else { u47 = 0; pu48 = (unsigned char *)&DAT_005be7c0; }
                        pu10 = (unsigned long *)cL4_alloc(0x28, 0x1050c401ab4594e);
                        *pu10 = (unsigned long)s_TypeDecoder_h__u__Node_kind__u___005d54b8;
                        *(unsigned int *)(pu10 + 1) = 0x399;
                        *(unsigned int *)((long)pu10 + 0xc) = (unsigned int)u43;
                        *(unsigned int *)(pu10 + 2) = u47;
                        pc18 = (char *)s_failed_to_decode_protocol_type_005d5654;
                        goto l91544;
                    }
                    sk_type_build_owned_395dec(out, &local_210, 1, 0, 0);
                } else if (u36 == 0x172) {
                    l8 = *(long *)node;
                    *(unsigned short *)(out + 2) = 0;
                    *out = l8;
                } else {
                    if (u36 != 0x173) goto case_c;
                    pp9 = *(unsigned long **)node;
                    goto l8f564;
                }
                goto fin;
            }
            if (u36 == 0x13b) {
                b22 = (unsigned char)((unsigned short *)node)[9];
                u37 = (unsigned long)b22;
                if (b22 < 3) {
                    if (b22 == 1) { u47 = 0; pu48 = (unsigned char *)&DAT_005be7c0; }
                    else if (b22 != 2) { u37 = 0; u47 = 0; pu48 = (unsigned char *)&DAT_005be7c0; }
                    else { u47 = 0; pu48 = (unsigned char *)&DAT_005be7c0; u37 = 2; }
                    goto l91914;
                }
                if (b22 == 3) { u37 = 0; u47 = *(unsigned int *)(node + 4); pu48 = *(unsigned char **)node; goto l91914; }
                if (b22 != 5) { u37 = 0; u47 = 0; pu48 = (unsigned char *)&DAT_005be7c0; }
                else {
                    u37 = (unsigned long)*(unsigned int *)(node + 4);
                    if (*(unsigned int *)(node + 4) < 3) { u47 = 0; pu48 = (unsigned char *)&DAT_005be7c0; }
                    else {
                        pu10 = (unsigned long *)(*(unsigned long **)node)[1];
                        u43 = *(unsigned short *)(pu10 + 2);
                        if (u43 != 0x68 || *(char *)((long)pu10 + 0x12) != 4) {
                            if (*(char *)((long)pu10 + 0x12) == 3) { u47 = *(unsigned int *)(pu10 + 1); pu48 = (unsigned char *)*pu10; }
                            else { u47 = 0; pu48 = (unsigned char *)&DAT_005be7c0; }
                            pu10 = (unsigned long *)cL4_alloc(0x28, 0x1050c401ab4594e);
                            *pu10 = (unsigned long)s_TypeDecoder_h__u__Node_kind__u___005d54b8;
                            *(unsigned int *)(pu10 + 1) = 0x62b;
                            *(unsigned int *)((long)pu10 + 0xc) = (unsigned int)u43;
                            *(unsigned int *)(pu10 + 2) = u47;
                            pc18 = (char *)s_unexpected_kind_or_no_index_005d59d8;
                            goto l92940;
                        }
                        pu11 = 0;
                        u28 = **(unsigned long **)node;
                        u13 = *pu10;
                        stk_208 = 0; local_210 = 0; local_200 = 0; stk_f8 = 0;
                        local_f0 = 0; local_100 = 0;
                        if (2 < *(unsigned int *)(node + 4)) pu11 = *(unsigned long **)(*(long *)node + 0x10);
                        u37 = 0;
                        goto l92ed0;
                    }
                }
l91914:
                pu10 = (unsigned long *)cL4_alloc(0x28, 0x1050c400dfe80cb);
                *pu10 = (unsigned long)s_TypeDecoder_h__u__Node_kind__u___005d5989;
                u13 = DAT_004f27d8;
                goto l91948;
            }
            if (u36 != 0x161) goto case_c;
            c = (char)((unsigned short *)node)[9];
            if (c != 2) {
                if (c == 3) { u47 = *(unsigned int *)(node + 4); pu48 = *(unsigned char **)node; }
                else {
                    if ((c == 5) && (1 < *(unsigned int *)(node + 4))) {
                        l8 = **(long **)node;
                        if (1 < *(unsigned int *)(node + 4)) { node = *(unsigned short **)node; l49 = *(long *)(node + 4); goto l9156c; }
                        l49 = 0; goto l9156c;
                    }
                    u47 = 0; pu48 = (unsigned char *)&DAT_005be7c0;
                }
                pu10 = (unsigned long *)cL4_alloc(0x28, 0x1050c401ab4594e);
                *pu10 = (unsigned long)s_TypeDecoder_h__u__Node_kind__u___005d54b8;
                pu10[1] = DAT_004f28d0;
                *(unsigned int *)(pu10 + 2) = u47;
                pc18 = (char *)s_not_enough_children_005d5640;
                goto l91544;
            }
            l8 = *(long *)node;
            l49 = *(long *)(node + 4);
l9156c:
            stk_208 = (unsigned long **)DAT_004f2710;
            local_210 = &local_200;
            sk_type_decode_sig_394734(&local_100, ctx, l49, i41 + 1, &local_210);
            pp12 = stk_f8;
            pp9 = local_100;
            if ((char)local_f0 == 1) {
                *(unsigned short *)(out + 2) = 1;
                out[1] = (unsigned long)stk_f8;
                l8 = ((unsigned long (*)(unsigned long, int, unsigned long))stk_f8)(local_100, 2, 0);
                *out = l8;
                ((void (*)(unsigned long, int, unsigned long))pp12)(pp9, 3, 0);
            } else {
                sk_type_build_func_3952c4(out, l8, local_210, (unsigned long)stk_208 & 0xffffffff);
            }
            goto l92054;
        }
        if (u43 < 0x137) {
            if (u36 != 0x135) {
                if (u36 == 0x136) {
                    u47 = 0;
                    b22 = (unsigned char)((unsigned short *)node)[9];
                    pu48 = (unsigned char *)&DAT_005be7c0;
                    if (b22 < 3) {
                        if ((b22 == 1) || (b22 == 2)) goto l90c6c;
                    } else if (b22 == 3) {
                        u47 = *(unsigned int *)(node + 4); pu48 = *(unsigned char **)node;
                    } else if (b22 == 5) {
                        if (*(int *)(node + 4) != 0) goto l90c68;
                        u47 = 0; pu48 = (unsigned char *)&DAT_005be7c0;
                    }
                    pu10 = (unsigned long *)cL4_alloc(0x28, 0x1050c401ab4594e);
                    *pu10 = (unsigned long)s_TypeDecoder_h__u__Node_kind__u___005d54b8;
                    u13 = DAT_004f27f8;
                    goto l92930;
                }
                goto case_c;
            }
            u47 = 0;
            b22 = (unsigned char)((unsigned short *)node)[9];
            pu48 = (unsigned char *)&DAT_005be7c0;
            if (b22 < 3) {
                if ((b22 == 1) || (b22 == 2)) {
l90c6c:
                    sk_type_decode_38f0a8(&local_210, ctx, *(unsigned long *)node, i41 + 1, 1);
                    pp9 = stk_208;
                    if ((short)local_200 != 1) pp9 = (unsigned long **)FUN_0037f9f4;
                    pp12 = local_210;
                    if ((short)local_200 != 1) pp12 = (unsigned long **)s_unknown_error_005d5481;
                    *(unsigned short *)(out + 2) = 1;
                    *out = (unsigned long)pp12;
                    out[1] = (unsigned long)pp9;
                    goto fin;
                }
            } else if (b22 == 3) {
                u47 = *(unsigned int *)(node + 4); pu48 = *(unsigned char **)node;
            } else if (b22 == 5) {
                if (*(int *)(node + 4) != 0) {
l90c68:
                    node = *(unsigned short **)node;
                    goto l90c6c;
                }
                u47 = 0; pu48 = (unsigned char *)&DAT_005be7c0;
            }
            pu10 = (unsigned long *)cL4_alloc(0x28, 0x1050c401ab4594e);
            *pu10 = (unsigned long)s_TypeDecoder_h__u__Node_kind__u___005d54b8;
            u13 = DAT_004f2800;
            goto l92930;
        }
        pu26 = (unsigned short *)node;
        if (u36 == 0x137) {
            u37 = 0; u47 = 0;
            b22 = (unsigned char)((unsigned short *)node)[9];
            pu48 = (unsigned char *)&DAT_005be7c0;
            if (b22 < 3) {
                pu48 = (unsigned char *)&DAT_005be7c0;
                if (b22 == 1) { u47 = 0; u37 = 1; }
                else if (b22 == 2) goto l9195c;
            } else if (b22 == 3) {
                u37 = 0; u47 = *(unsigned int *)(node + 4); pu48 = *(unsigned char **)node;
            } else if (b22 == 5) {
                u37 = (unsigned long)*(unsigned int *)(node + 4);
                if (1 < *(unsigned int *)(node + 4)) goto l91958;
                u47 = 0;
            }
            pu10 = (unsigned long *)cL4_alloc(0x28, 0x1050c400dfe80cb);
            *pu10 = (unsigned long)s_TypeDecoder_h__u__Node_kind__u___005d54f0;
            u13 = DAT_004f27e8;
            goto l925e4;
l91958:
            pu26 = *(unsigned short **)node;
l9195c:
            sk_type_decode_38f0a8(&local_210, ctx, *(unsigned long *)pu26, i41 + 1, 1);
            if ((short)local_200 == 1) goto l92550;
            if ((char)((unsigned short *)node)[9] == 2) { l8 = *(long *)(node + 4); }
            else {
                if (((char)((unsigned short *)node)[9] == 5) && (1 < *(unsigned int *)(node + 4))) { node = *(unsigned short **)node; l8 = *(long *)(node + 4); }
                else l8 = 0;
            }
            sk_type_decode_38f0a8(&local_100, ctx, l8, i41 + 1, 1);
            pp9 = stk_f8;
            if ((short)local_f0 != 1) pp9 = (unsigned long **)FUN_0037f9f4;
            pp12 = local_100;
            if ((short)local_f0 != 1) pp12 = (unsigned long **)s_unknown_error_005d5481;
            *(unsigned short *)(out + 2) = 1;
            *out = (unsigned long)pp12;
            out[1] = (unsigned long)pp9;
            goto l9391c;
        }
        if (u15 == 0x138) {
            u37 = 0; u47 = 0;
            b22 = (unsigned char)((unsigned short *)node)[9];
            pu48 = (unsigned char *)&DAT_005be7c0;
            if (b22 < 3) {
                if (b22 == 1) { u47 = 0; u37 = 1; }
                else if (b22 == 2) goto l9195c;
            } else if (b22 == 3) {
                u37 = 0; u47 = *(unsigned int *)(node + 4); pu48 = *(unsigned char **)node;
            } else {
                pu48 = (unsigned char *)&DAT_005be7c0;
                if (b22 == 5) {
                    u37 = (unsigned long)*(unsigned int *)(node + 4);
                    if (1 < *(unsigned int *)(node + 4)) goto l91958;
                    u47 = 0;
                }
            }
            pu10 = (unsigned long *)cL4_alloc(0x28, 0x1050c400dfe80cb);
            *pu10 = (unsigned long)s_TypeDecoder_h__u__Node_kind__u___005d54f0;
            u13 = DAT_004f27f0;
            goto l925e4;
        }
        if (u15 == 0x139) {
            u47 = 0;
            b22 = (unsigned char)((unsigned short *)node)[9];
            pu48 = (unsigned char *)&DAT_005be7c0;
            if (b22 < 3) {
                if ((b22 == 1) || (b22 == 2)) {
l90b54:
                    sk_type_decode_38f0a8(&local_210, ctx, *(unsigned long *)node, i41 + 1, 1);
                    pp9 = local_210;
                    if ((short)local_200 == 0) goto l8f564;
                    if ((short)local_200 != 1) goto l913ac;
                    *(unsigned short *)(out + 2) = 1;
                    goto l90aa0;
                }
            } else if (b22 == 3) {
                u47 = *(unsigned int *)(node + 4); pu48 = *(unsigned char **)node;
            } else if (b22 == 5) {
                if (*(int *)(node + 4) != 0) { node = *(unsigned short **)node; goto l90b54; }
                u47 = 0; pu48 = (unsigned char *)&DAT_005be7c0;
            }
            pu10 = (unsigned long *)cL4_alloc(0x28, 0x1050c401ab4594e);
            *pu10 = (unsigned long)s_TypeDecoder_h__u__Node_kind__u___005d54b8;
            u13 = DAT_004f27e0;
            goto l92930;
        }
case_c:
        if ((char)((unsigned short *)node)[9] == 3) { u47 = *(unsigned int *)(node + 4); pu48 = *(unsigned char **)node; }
        else { u47 = 0; pu48 = (unsigned char *)&DAT_005be7c0; }
        pu10 = (unsigned long *)cL4_alloc(0x28, 0x1050c401ab4594e);
        *pu10 = (unsigned long)s_TypeDecoder_h__u__Node_kind__u___005d54b8;
        *(unsigned int *)(pu10 + 1) = 0x666;
        *(unsigned int *)((long)pu10 + 0xc) = u44;
        *(unsigned int *)(pu10 + 2) = u47;
        pc18 = (char *)s_unexpected_kind_005d586a;
l91544:
        pu10[3] = (unsigned long)pu48;
        goto l92944;
    }
    if (u43 < 0xdb) {
        u31 = u15 - 0xaf;
        if (0x1c < u31) {
            if (u15 != 0x77) {
                if (u36 == 0x9a) goto l8f7ec;
                goto case_c;
            }
            u37 = 0;
            stk_208 = (unsigned long **)DAT_004f2710;
            stk_f8 = (unsigned long **)DAT_004f2710;
            stk_298 = (unsigned long **)DAT_004f2710;
            local_328 = (unsigned long **)DAT_004f2710;
            local_330 = (unsigned long **)local_320;
            local_2a0 = (unsigned long **)local_290;
            local_210 = &local_200;
            local_100 = &local_f0;
            goto l8fd5c;
        }
        u3 = 1 << (unsigned long)(u31 & 0x1f);
        if ((u3 & 0x1c000000) == 0) {
            if ((u3 & 3) != 0) goto case_b;
            if ((1 << (unsigned long)(u31 & 0x1f) & 0x30000U) != 0) goto case_16b;
            if (u15 != 0x77) {
                if (u36 == 0x9a) goto l8f7ec;
                goto case_c;
            }
            u37 = 0;
            stk_208 = (unsigned long **)DAT_004f2710;
            stk_f8 = (unsigned long **)DAT_004f2710;
            stk_298 = (unsigned long **)DAT_004f2710;
            local_328 = (unsigned long **)DAT_004f2710;
            local_330 = (unsigned long **)local_320;
            local_2a0 = (unsigned long **)local_290;
            local_210 = &local_200;
            local_100 = &local_f0;
            goto l8fd5c;
        }
        u47 = 0;
        b22 = (unsigned char)((unsigned short *)node)[9];
        pu48 = (unsigned char *)&DAT_005be7c0;
        if (b22 < 3) {
            pu26 = (unsigned short *)node;
            if ((b22 == 1) || (b22 == 2)) {
                pu10 = *(unsigned long **)pu26;
                goto l8f6cc;
            }
        } else if (b22 == 3) {
            u47 = *(unsigned int *)(node + 4); pu48 = *(unsigned char **)node;
        } else if (b22 == 5) {
            if (*(int *)(node + 4) != 0) {
                if (*(int *)(node + 4) != 0) { pu26 = *(unsigned short **)node; pu10 = *(unsigned long **)pu26; goto l8f6cc; }
                pu10 = 0; goto l8f6cc;
            }
            u47 = 0; pu48 = (unsigned char *)&DAT_005be7c0;
        }
        pu10 = (unsigned long *)cL4_alloc(0x28, 0x1050c401ab4594e);
        *pu10 = (unsigned long)s_TypeDecoder_h__u__Node_kind__u___005d54b8;
        u14 = 0x348;
l91754:
        *(unsigned int *)(pu10 + 1) = u14;
        *(unsigned int *)((long)pu10 + 0xc) = u44;
l91758:
        *(unsigned int *)(pu10 + 2) = u47;
        pc18 = (char *)s_no_children_005d55ed;
        goto l91764;
    }
    if (0x2b < u36 - 0xdb) goto case_c;
    switch (u36) {
    default:
        b22 = (unsigned char)((unsigned short *)node)[9];
        if (b22 - 1 < 2) { node = *(unsigned short **)node; goto l8f3e4; }
        if (b22 == 5) {
            if (*(int *)(node + 4) != 0) { node = *(unsigned short **)node; goto f2fc; }
            u47 = 0;
        } else {
            if (b22 != 3) { u47 = 0; goto l902a4; }
            u47 = *(unsigned int *)(node + 4); pu48 = *(unsigned char **)node;
        }
l902a4:
        pu10 = (unsigned long *)cL4_alloc(0x28, 0x1050c401ab4594e);
        *pu10 = (unsigned long)s_TypeDecoder_h__u__Node_kind__u___005d54b8;
        u13 = DAT_004f2878;
        goto l90354;
    case 0xdc: case 0xdd: case 0xe0: case 0xe1: case 0xe2: case 0xe3: case 0xe4:
    case 0xe5: case 0xe6: case 0xe8: case 0xe9: case 0xed: case 0xf2: case 0xf3:
    case 0xf7: case 0xf9: case 0xfa: case 0xfb: case 0xfc: case 0xfd: case 0xfe:
    case 0xff: case 0x100: case 0x101: case 0x102: case 0x103:
        goto case_c;
    case 0xde:
        u47 = 0;
        b22 = (unsigned char)((unsigned short *)node)[9];
        pu48 = (unsigned char *)&DAT_005be7c0;
        if (b22 < 3) {
            if ((b22 == 1) || (b22 == 2)) goto l90c6c;
        } else if (b22 == 3) {
            u47 = *(unsigned int *)(node + 4); pu48 = *(unsigned char **)node;
        } else if (b22 == 5) {
            if (*(int *)(node + 4) != 0) goto l90c68;
            u47 = 0; pu48 = (unsigned char *)&DAT_005be7c0;
        }
        pu10 = (unsigned long *)cL4_alloc(0x28, 0x1050c401ab4594e);
        *pu10 = (unsigned long)s_TypeDecoder_h__u__Node_kind__u___005d54b8;
        u13 = DAT_004f2818;
        break;
    case 0xdf:
        u47 = 0;
        pp9 = (unsigned long **)local_290;
        stk_298 = (unsigned long **)DAT_004f2740;
        local_328 = (unsigned long **)DAT_004f2740;
        stk_f8 = (unsigned long **)DAT_004f2740;
        stk_208 = (unsigned long **)DAT_004f2710;
        stk_358 = (unsigned long **)DAT_004f2740;
        pu48 = (unsigned char *)&DAT_005be7c0;
        b22 = (unsigned char)((unsigned short *)node)[9];
        pu4 = pu48;
        local_360 = (unsigned long **)appc_350;
        local_330 = (unsigned long **)local_320;
        local_2a0 = pp9;
        local_210 = &local_200;
        local_100 = &local_f0;
        if (2 < b22) {
            if (b22 == 3) { u47 = *(unsigned int *)(node + 4); pu4 = *(unsigned char **)node; }
            else if (b22 == 5) {
                u36 = *(unsigned int *)(node + 4);
                u47 = 0; pu4 = (unsigned char *)&DAT_005be7c0;
                if (u36 != 0) {
                    if (u36 != 1) {
                        if (u36 < 3) goto l8fba0;
                        pu10 = *(unsigned long **)(*(long *)node + 0x10);
                        goto l8fba4;
                    }
                    goto l909bc;
                }
            }
            goto l91810;
        }
        if (b22 == 1) goto l909c0;
        if (b22 != 2) goto l91810;
l8fba0:
        pu10 = 0;
l8fba4:
        u43 = *(unsigned short *)(pu10 + 2);
        if (u43 != 0xf7) {
            if (*(char *)((long)pu10 + 0x12) == 3) { u47 = *(unsigned int *)(pu10 + 1); pu48 = (unsigned char *)*pu10; }
            else u47 = 0;
            pu10 = (unsigned long *)cL4_alloc(0x28, 0x1050c401ab4594e);
            *pu10 = (unsigned long)s_TypeDecoder_h__u__Node_kind__u___005d54b8;
            *(unsigned int *)(pu10 + 1) = 0x58a;
            *(unsigned int *)((long)pu10 + 0xc) = (unsigned int)u43;
            *(unsigned int *)(pu10 + 2) = u47;
            pc18 = (char *)s_expected_type_list_005d58dd;
            goto l93508;
        }
        pu26 = (unsigned short *)node;
        if (b22 == 2) { pu26 = *(unsigned short **)(pu26 + 4); }
        else {
            if ((b22 == 5) && (1 < *(unsigned int *)(node + 4))) { pu26 = *(unsigned short **)node; pu26 = *(unsigned short **)(pu26 + 4); }
            else pu26 = 0;
        }
        pu25 = pu26 + 8;
        u43 = *pu25;
        if (u43 != 0x2c) {
            if ((char)pu26[9] == 3) { u47 = *(unsigned int *)(pu26 + 4); pu48 = *(unsigned char **)pu26; }
            else { u47 = 0; pu48 = (unsigned char *)&DAT_005be7c0; }
            pu10 = (unsigned long *)cL4_alloc(0x28, 0x1050c401ab4594e);
            *pu10 = (unsigned long)s_TypeDecoder_h__u__Node_kind__u___005d54b8;
            *(unsigned int *)(pu10 + 1) = 0x590;
            *(unsigned int *)((long)pu10 + 0xc) = (unsigned int)u43;
            *(unsigned int *)(pu10 + 2) = u47;
            pc18 = (char *)s_expected_dependent_generic_signa_005d58f0;
            goto l93508;
        }
        b22 = (unsigned char)pu26[9];
        if (b22 - 1 < 2) {
            local_380 = (unsigned char *)local_370;
            local_378 = (unsigned long **)DAT_004f2740;
            pu40 = pu26 + 4;
            pu16 = pu26;
            if (b22 != 1) pu40 = pu25;
            goto l9369c;
        }
        if (b22 == 3) {
            u47 = *(unsigned int *)(pu26 + 4);
            pu48 = *(unsigned char **)pu26;
            goto l93ef4;
        }
        if (b22 != 5) { u47 = 0; pu48 = (unsigned char *)&DAT_005be7c0; goto l93ef4; }
        if (*(int *)(pu26 + 4) == 0) { u47 = 0; pu48 = (unsigned char *)&DAT_005be7c0; goto l93ef4; }
        local_380 = (unsigned char *)local_370;
        local_378 = (unsigned long **)DAT_004f2740;
        if (*(unsigned int *)(pu26 + 4) == 0) goto l93f70;
        pu40 = *(unsigned short **)pu26 + (unsigned long)*(unsigned int *)(pu26 + 4) * 4;
        pu16 = *(unsigned short **)pu26;
l9369c:
        do {
            pu21 = *(unsigned int **)pu16;
            if ((*(short *)(pu21 + 4) == 0x26) && (*(char *)((long)pu21 + 0x12) == 4)) {
                sk_wordlist_append_389370(&local_380, *pu21);
            }
            pu16 = pu16 + 4;
        } while (pu16 != pu40);
        b22 = (unsigned char)pu26[9];
        local_3c0 = (unsigned long **)local_3b0;
        local_3b8 = (unsigned long **)DAT_004f2718;
        pu16 = pu26;
        if (b22 - 1 < 2) {
            if (b22 == 1) pu25 = pu26 + 4;
            else if (b22 != 2) {
                if (b22 == 5) { pu25 = *(unsigned short **)pu26; goto l93f7c; }
                pu25 = 0;
            }
        } else {
            if (b22 != 5) { pu16 = 0; goto l93710; }
l93f70:
            pu25 = *(unsigned short **)pu26;
            pu16 = pu25;
            local_3b8 = (unsigned long **)DAT_004f2718;
l93f7c:
            local_410 = (unsigned long **)local_3b0;
            pu25 = pu25 + (unsigned long)*(unsigned int *)(pu26 + 4) * 4;
            DAT_004f2718 = (unsigned long)local_3b8;
            local_3c0 = local_410;
        }
        while (true) {
            local_410 = (unsigned long **)local_3b0;
            local_408 = (unsigned char *)local_370;
            if (pu16 == pu25) break;
            pu11 = *(unsigned long **)pu16;
            if (*(short *)(pu11 + 2) == 0x2b) {
                if (*(unsigned char *)((long)pu11 + 0x12) - 1 < 2) { pu11 = (unsigned long *)*pu11; }
                else {
                    if ((*(unsigned char *)((long)pu11 + 0x12) == 5) && (*(int *)(pu11 + 1) != 0)) { pu11 = (unsigned long *)*pu11; }
                    else pu11 = 0;
                }
                if (*(unsigned char *)((long)pu11 + 0x12) - 1 < 2) { pu11 = (unsigned long *)*pu11; }
                else {
                    if ((*(unsigned char *)((long)pu11 + 0x12) == 5) && (*(int *)(pu11 + 1) != 0)) { pu11 = (unsigned long *)*pu11; }
                    else pu11 = 0;
                }
                if (*(unsigned char *)((long)pu11 + 0x12) - 1 < 2) local_3c8 = *(long *)*pu11;
                else {
                    local_3c8 = **(long **)*pu11;
                    if (*(unsigned char *)((long)pu11 + 0x12) == 5) pu11 = (unsigned long *)*pu11;
                }
                local_3d0 = *(unsigned long *)pu11[1];
                sk_type_decl_record_39779c(&local_3c0, &local_3c8, &local_3d0);
            }
            pu16 = pu16 + 4;
        }
        u37 = (unsigned long)local_378 & 0xffffffff;
        if ((int)local_378 != 0) {
            u17 = 0;
            pu30 = (unsigned char *)local_380;
            do {
                if (*(int *)(pu30 + u17 * 4) != 0) {
                    u36 = 0;
                    do {
                        u13 = sk_type_metadata_get_3963b8(*ctx, u17, u36);
                        sk_type_list_push_363f10(&local_360, u13);
                        u36 = u36 + 1;
                    } while (u36 < *(unsigned int *)(local_380 + u17 * 4));
                    u37 = (unsigned long)local_378 & 0xffffffff;
                    pu30 = (unsigned char *)local_380;
                }
                u17 = u17 + 1;
            } while (u17 < u37);
        }
        sk_type_build_sig_395f3c(pu26, &local_100, &local_210, *ctx);
        b22 = *(unsigned char *)((long)pu10 + 0x12);
        u36 = (unsigned int)b22;
        if (b22 == 1) {
l940f8:
            l8 = 0;
            u37 = 0;
            do {
                b22 = *(unsigned char *)((long)pu10 + 0x12);
                u17 = (unsigned long)b22;
                u15 = (unsigned int)b22;
                if (u15 == 1) {
                    if (u17 <= u37) goto l9414c;
                    pu11 = pu10;
                    if (1 < u15 - 1) pu11 = (unsigned long *)*pu10;
                    u13 = pu11[u37];
                } else {
                    if (u15 == 5) { u17 = (unsigned long)*(unsigned int *)(pu10 + 1); goto l9412c; }
                    if (b22 == 2) { u17 = 2; goto l9412c; }
l9414c:
                    u13 = 0;
                }
                sk_type_decode_38f0a8(out, ctx, u13, i41 + 1, 0);
                b5 = (short)out[2] == 1;
                if (b5) break;
                local_3c8 = *out;
                if ((short)out[2] != 0) local_3c8 = 0;
                sk_type_push8_39780c(&local_330, (long)local_360 + l8, &local_3c8);
                if ((short)out[2] == 1) ((void (*)(unsigned long, int, unsigned long))out[1])(*out, 3, 0);
                u37 = u37 + 1;
                l8 = l8 + 8;
            } while (u36 != u37);
        } else {
            if (b22 == 5) {
                u36 = *(unsigned int *)(pu10 + 1);
                if (u36 != 0) goto l940f8;
            } else if (b22 == 2) goto l940f8;
            b5 = false;
        }
        if (local_3c0 != local_410) cL4_free(0, 0);
        if (local_380 != local_408) cL4_free(0, 0);
        if (!b5) {
            if ((unsigned char)((unsigned short *)node)[9] - 1 < 2) {
l909c0:
                node = *(unsigned short **)node;
            } else if ((unsigned char)((unsigned short *)node)[9] == 5) {
                if (*(int *)(node + 4) != 0) {
l909bc:
                    node = *(unsigned short **)node;
                    goto l909c0;
                }
                node = 0;
            } else node = 0;
            pu26 = (unsigned short *)node + 8;
            u43 = *pu26;
            if (u43 == 0xe0) {
                b22 = (unsigned char)((unsigned short *)node)[9];
                pu25 = (unsigned short *)node;
                if (b22 - 1 < 2) {
                    if (b22 == 1) pu26 = (unsigned short *)node + 4;
                    else if (b22 != 2) {
                        if (b22 == 5) { pu26 = *(unsigned short **)node; goto l93324; }
                        pu26 = 0;
                    }
                } else {
                    if (b22 != 5) { pu25 = 0; goto l93308; }
                    pu26 = *(unsigned short **)node;
                    pu25 = pu26;
l93324:
                    pu26 = pu26 + (unsigned long)*(unsigned int *)(node + 4) * 4;
                }
                if (pu25 != pu26) {
                    pu48 = (unsigned char *)&DAT_005be7c0;
                    do {
                        pu10 = *(unsigned long **)pu25;
                        u43 = *(unsigned short *)(pu10 + 2);
                        if (u43 != 0xe1) {
                            if (u43 == 0xe2) { u23 = 0; goto l93778; }
                            local_3f0 = (char *)s_unhandled_field_type_005d5974;
                            u14 = 0x5ce;
                            u47 = 0x5ce;
                            if (*(char *)((long)pu10 + 0x12) == 3) {
                                u14 = u47;
                                u47 = *(unsigned int *)(pu10 + 1);
                                pu48 = (unsigned char *)*pu10;
                            } else { u47 = 0; pu48 = (unsigned char *)&DAT_005be7c0; }
l93e3c:
                            pu10 = (unsigned long *)cL4_alloc(0x28, 0x1050c401ab4594e);
                            *pu10 = (unsigned long)s_TypeDecoder_h__u__Node_kind__u___005d54b8;
                            *(unsigned int *)(pu10 + 1) = u14;
                            *(unsigned int *)((long)pu10 + 0xc) = (unsigned int)u43;
                            *(unsigned int *)(pu10 + 2) = u47;
                            pu10[3] = (unsigned long)pu48;
                            pu10[4] = (unsigned long)local_3f0;
                            *(unsigned short *)(out + 2) = 1;
                            out[1] = (unsigned long)FUN_00397f0c;
                            pu11 = (unsigned long *)cL4_alloc(0x28, 0x1050c401ab4594e);
                            u13 = *pu10; u53 = pu10[3]; u28 = pu10[2];
                            pu11[1] = pu10[1]; *pu11 = u13; pu11[3] = u53; pu11[2] = u28;
                            pu11[4] = pu10[4];
                            *out = (unsigned long)pu11;
                            cL4_free(pu10, 0x28);
                            goto l93554;
                        }
                        u23 = 1;
l93778:
                        local_380 = (unsigned char *)((unsigned long)local_380 & 0xffffffffffffff00 | u23);
                        b22 = *(unsigned char *)((long)pu10 + 0x12);
                        if (1 < b22 - 1) {
                            if (b22 == 5) {
                                if (*(int *)(pu10 + 1) != 0) { pu10 = (unsigned long *)*pu10; goto l937a0; }
                                local_3f0 = (char *)s_no_children_005d55ed;
                                u47 = 0;
                                u14 = 0x5d1;
                            } else {
                                local_3f0 = (char *)s_no_children_005d55ed;
                                if (b22 == 3) { local_3f0 = (char *)s_no_children_005d55ed; u47 = 0x5d1; u14 = 0x5ce; goto l93e3c; }
                                u47 = 0;
                                u14 = 0x5d1;
                            }
                            goto l93e3c;
                        }
l937a0:
                        sk_type_decode_38f0a8(out, ctx, *pu10, i41 + 1, 1);
                        if ((short)out[2] == 1) goto l93554;
                        local_3c0 = (unsigned long **)*out;
                        if ((short)out[2] != 0) local_3c0 = 0;
                        sk_type_field_push_39787c(&local_2a0, &local_3c0, &local_380);
                        if ((short)out[2] == 1) ((void (*)(unsigned long, int, unsigned long))out[1])(*out, 3, 0);
                        pu25 = pu25 + 4;
                    } while (pu25 != pu26);
                }
                *out = (unsigned long)s_unknown_error_005d5481;
                out[1] = (unsigned long)FUN_0037f9f4;
                *(unsigned short *)(out + 2) = 1;
            } else {
                if ((char)((unsigned short *)node)[9] == 3) { u47 = *(unsigned int *)(node + 4); pu48 = *(unsigned char **)node; }
                else { u47 = 0; pu48 = (unsigned char *)&DAT_005be7c0; }
                pu10 = (unsigned long *)cL4_alloc(0x28, 0x1050c401ab4594e);
                *pu10 = (unsigned long)s_TypeDecoder_h__u__Node_kind__u___005d54b8;
                *(unsigned int *)(pu10 + 1) = 0x5c7;
                *(unsigned int *)((long)pu10 + 0xc) = (unsigned int)u43;
                *(unsigned int *)(pu10 + 2) = u47;
                pc18 = (char *)s_expected_layout_005d5964;
l93508:
                u13 = 0x1050c401ab4594e;
                pu10[3] = (unsigned long)pu48;
                pu10[4] = (unsigned long)pc18;
                *(unsigned short *)(out + 2) = 1;
                pc19 = FUN_00397f0c;
l93524:
                out[1] = (unsigned long)pc19;
                pu11 = (unsigned long *)cL4_alloc(0x28, u13);
                u13 = *pu10; u53 = pu10[3]; u28 = pu10[2];
                pu11[1] = pu10[1]; *pu11 = u13; pu11[3] = u53; pu11[2] = u28;
                pu11[4] = pu10[4];
                *out = (unsigned long)pu11;
                cL4_free(pu10, 0x28);
            }
        }
l93554:
        if (local_360 != (unsigned long **)appc_350) cL4_free(0, 0);
        if ((unsigned long **)local_210 != &local_200) cL4_free(0, 0);
        if (local_100 != &local_f0) cL4_free(0, 0);
        pp12 = local_2a0;
        if (local_330 != (unsigned long **)local_320) { cL4_free(0, 0); pp12 = local_2a0; }
l9359c:
        if (pp12 == pp9) goto fin;
        goto l9366c;
    case 0xe7: case 0xf5: case 0xf6:
        goto case_19;
    case 0xea:
        goto case_b;
    case 0xeb:
        pp9 = &local_f0;
        stk_f8 = (unsigned long **)DAT_004f2710;
        stk_208 = (unsigned long **)DAT_004f2710;
        b22 = (unsigned char)((unsigned short *)node)[9];
        pu26 = (unsigned short *)node;
        if (b22 - 1 < 2) {
            if (b22 == 1) pu25 = (unsigned short *)node + 4;
            else if (b22 == 2) pu25 = (unsigned short *)node + 8;
            else {
                if (b22 == 5) { pu25 = *(unsigned short **)node; goto l914ec; }
                pu25 = 0;
            }
        } else {
            if (b22 != 5) { pu26 = 0; goto l914d0; }
            pu25 = *(unsigned short **)node;
            pu26 = pu25;
l914ec:
            pu25 = pu25 + (unsigned long)*(unsigned int *)(node + 4) * 4;
        }
        local_210 = &local_200;
        local_100 = pp9;
        if (pu26 != pu25) goto l91c30;
        u17 = 0;
        u37 = 0;
        goto l91f7c;
    case 0xec:
        b22 = (unsigned char)((unsigned short *)node)[9];
        u36 = b22 - 1;
        pu26 = (unsigned short *)node;
        if (u36 < 2) {
            if (*(short *)(*(long *)pu26 + 0x10) == 0xed) {
                if (b22 < 3) {
                    if (b22 == 2) goto l8f3e0;
                    if (b22 != 1) { u37 = 0; goto l91770; }
                    u47 = 0; pu48 = (unsigned char *)&DAT_005be7c0; u37 = 1;
                } else if (b22 == 5) {
                    u37 = (unsigned long)*(unsigned int *)(node + 4);
                    if (1 < *(unsigned int *)(node + 4)) goto l8f3dc;
l91770:
                    u47 = 0; pu48 = (unsigned char *)&DAT_005be7c0;
                } else {
                    if (b22 != 3) { u37 = 0; goto l91770; }
                    u37 = 0; u47 = *(unsigned int *)(node + 4); pu48 = *(unsigned char **)node;
                }
                pu10 = (unsigned long *)cL4_alloc(0x28, 0x1050c400dfe80cb);
                *pu10 = (unsigned long)s_TypeDecoder_h__u__Node_kind__u___005d54f0;
                u13 = DAT_004f2860;
                goto l91948;
            }
            if (u36 < 2) { node = *(unsigned short **)node; goto l8f3e4; }
            if ((b22 == 5) && (*(int *)(node + 4) != 0)) { node = *(unsigned short **)node; goto f2fc; }
            node = 0;
            goto l8f3e4;
        }
        if (b22 == 5) {
            if (*(int *)(node + 4) != 0) { pu26 = *(unsigned short **)node; goto l8f298; }
            u47 = 0;
        } else {
            if (b22 != 3) { u47 = 0; goto l90268; }
            u47 = *(unsigned int *)(node + 4); pu48 = *(unsigned char **)node;
        }
l90268:
        pu10 = (unsigned long *)cL4_alloc(0x28, 0x1050c401ab4594e);
        *pu10 = (unsigned long)s_TypeDecoder_h__u__Node_kind__u___005d54b8;
        u13 = DAT_004f2868;
l90354:
        pu10[1] = u13;
l91758_2:
        *(unsigned int *)(pu10 + 2) = u47;
        pc18 = (char *)s_no_children_005d55ed;
l91764:
        pu10[3] = (unsigned long)pu48;
        goto l92944;
    case 0xee: case 0xef: case 0xf0:
        pu26 = (unsigned short *)node + 8;
        local_210 = &local_200;
        stk_208 = (unsigned long **)DAT_004f2710;
        b22 = (unsigned char)((unsigned short *)node)[9];
        pu25 = (unsigned short *)node;
        if (b22 - 1 < 2) {
            if (b22 == 1) pu16 = (unsigned short *)node + 4;
            else {
                pu16 = pu26;
                if (b22 != 2) {
                    if (b22 == 5) { pu16 = *(unsigned short **)node; goto l90120; }
                    pu16 = 0;
                }
            }
        } else {
            if (b22 != 5) { pu25 = 0; goto l90104; }
            pu16 = *(unsigned short **)node;
            pu25 = pu16;
l90120:
            pu16 = pu16 + (unsigned long)*(unsigned int *)(node + 4) * 4;
        }
        if (pu25 != pu16) goto l90420;
        u37 = 0;
        goto l90694;
    case 0xf1:
        if ((char)((unsigned short *)node)[9] == 3) { u47 = *(unsigned int *)(node + 4); pu48 = *(unsigned char **)node; }
        else { u47 = 0; pu48 = (unsigned char *)&DAT_005be7c0; }
        pu10 = (unsigned long *)cL4_alloc(0x28, 0x1050c401ab4594e);
        *pu10 = (unsigned long)s_TypeDecoder_h__u__Node_kind__u___005d54b8;
        pu10[1] = DAT_004f2850;
        *(unsigned int *)(pu10 + 2) = u47;
        pc18 = (char *)s_pack_expansion_type_in_unsupport_005d58b1;
        goto l91544;
    case 0xf4:
        b22 = (unsigned char)((unsigned short *)node)[9];
        if (b22 - 1 < 2) { node = *(unsigned short **)node; goto l8f3e4; }
        if (b22 == 5) {
            if (*(int *)(node + 4) != 0) { node = *(unsigned short **)node; goto f2fc; }
            u47 = 0;
        } else {
            if (b22 != 3) { u47 = 0; goto l902e0; }
            u47 = *(unsigned int *)(node + 4); pu48 = *(unsigned char **)node;
        }
l902e0:
        pu10 = (unsigned long *)cL4_alloc(0x28, 0x1050c401ab4594e);
        *pu10 = (unsigned long)s_TypeDecoder_h__u__Node_kind__u___005d54b8;
        u13 = DAT_004f28e0;
        goto l903a8;
    case 0xf8:
        b22 = (unsigned char)((unsigned short *)node)[9];
        if (b22 - 1 < 2) { node = *(unsigned short **)node; goto l8f3e4; }
        if (b22 == 5) {
            if (*(int *)(node + 4) != 0) { node = *(unsigned short **)node; goto f2fc; }
            u47 = 0;
        } else {
            if (b22 != 3) { u47 = 0; goto l9022c; }
            u47 = *(unsigned int *)(node + 4); pu48 = *(unsigned char **)node;
        }
l9022c:
        pu10 = (unsigned long *)cL4_alloc(0x28, 0x1050c401ab4594e);
        *pu10 = (unsigned long)s_TypeDecoder_h__u__Node_kind__u___005d54b8;
        u13 = DAT_004f28e8;
l903a8:
        pu10[1] = u13;
        *(unsigned int *)(pu10 + 2) = u47;
        pc18 = (char *)s_no_children__005d54e3;
        goto l91764;
    case 0x104:
        u47 = 0;
        b22 = (unsigned char)((unsigned short *)node)[9];
        pu48 = (unsigned char *)&DAT_005be7c0;
        if (b22 < 3) {
            if ((b22 == 1) || (b22 == 2)) {
l90960:
                sk_type_decode_38f0a8(&local_210, ctx, *(unsigned long *)node, i41 + 1, 1);
                if ((short)local_200 == 1) goto l90a9c;
                l8 = *ctx;
                if ((short)local_200 == 0) { b22 = *(unsigned char *)(l8 + 0x48) | 1; goto l9263c; }
                b22 = *(unsigned char *)(l8 + 0x48) | 1;
l913a8:
                *(unsigned char *)(l8 + 0x48) = b22;
                goto l913ac;
            }
        } else if (b22 == 3) {
            u47 = *(unsigned int *)(node + 4); pu48 = *(unsigned char **)node;
        } else if (b22 == 5) {
            if (*(int *)(node + 4) != 0) { node = *(unsigned short **)node; goto l90960; }
            u47 = 0; pu48 = (unsigned char *)&DAT_005be7c0;
        }
        pu10 = (unsigned long *)cL4_alloc(0x28, 0x1050c401ab4594e);
        *pu10 = (unsigned long)s_TypeDecoder_h__u__Node_kind__u___005d54b8;
        u13 = DAT_004f2820;
        break;
    case 0x105:
        u47 = 0;
        b22 = (unsigned char)((unsigned short *)node)[9];
        pu48 = (unsigned char *)&DAT_005be7c0;
        if (b22 < 3) {
            if ((b22 == 1) || (b22 == 2)) {
l90908:
                sk_type_decode_38f0a8(&local_210, ctx, *(unsigned long *)node, i41 + 1, 1);
                if ((short)local_200 != 1) {
                    l8 = *ctx;
                    if ((short)local_200 != 0) { b22 = *(unsigned char *)(l8 + 0x48) | 2; goto l913a8; }
                    b22 = *(unsigned char *)(l8 + 0x48) | 2;
l9263c:
                    *(unsigned char *)(l8 + 0x48) = b22;
                    *(unsigned short *)(out + 2) = 0;
                    *out = (unsigned long)local_210;
                    pp9 = local_210;
                    goto joined_r8c8;
                }
l90a9c:
                *(unsigned short *)(out + 2) = 1;
l90aa0:
                out[1] = (unsigned long)stk_208;
                *out = (unsigned long)local_210;
                goto fin;
            }
        } else if (b22 == 3) {
            u47 = *(unsigned int *)(node + 4); pu48 = *(unsigned char **)node;
        } else if (b22 == 5) {
            if (*(int *)(node + 4) != 0) { node = *(unsigned short **)node; goto l90908; }
            u47 = 0; pu48 = (unsigned char *)&DAT_005be7c0;
        }
        pu10 = (unsigned long *)cL4_alloc(0x28, 0x1050c401ab4594e);
        *pu10 = (unsigned long)s_TypeDecoder_h__u__Node_kind__u___005d54b8;
        u13 = DAT_004f2830;
        break;
    case 0x106:
        u47 = 0;
        b22 = (unsigned char)((unsigned short *)node)[9];
        pu48 = (unsigned char *)&DAT_005be7c0;
        if (b22 < 3) {
            if ((b22 == 1) || (b22 == 2)) {
l90a74:
                sk_type_decode_38f0a8(&local_210, ctx, *(unsigned long *)node, i41 + 1, 1);
                if ((short)local_200 == 1) goto l90a9c;
                l8 = *ctx;
                if ((short)local_200 == 0) { b22 = *(unsigned char *)(l8 + 0x48) | 4; goto l9263c; }
                b22 = *(unsigned char *)(l8 + 0x48) | 4;
                goto l913a8;
            }
        } else if (b22 == 3) {
            u47 = *(unsigned int *)(node + 4); pu48 = *(unsigned char **)node;
        } else if (b22 == 5) {
            if (*(int *)(node + 4) != 0) { node = *(unsigned short **)node; goto l90a74; }
            u47 = 0; pu48 = (unsigned char *)&DAT_005be7c0;
        }
        pu10 = (unsigned long *)cL4_alloc(0x28, 0x1050c401ab4594e);
        *pu10 = (unsigned long)s_TypeDecoder_h__u__Node_kind__u___005d54b8;
        u13 = DAT_004f2828;
    }
l92930:
    pu10[1] = u13;
    *(unsigned int *)(pu10 + 2) = u47;
    pc18 = (char *)s_no_children_005d55ed;
l92940:
    pu10[3] = (unsigned long)pu48;
l92944:
    u13 = 0x1050c401ab4594e;
    pu10[4] = (unsigned long)pc18;
    *(unsigned short *)(out + 2) = 1;
    pc19 = FUN_00397f0c;
l92960:
    out[1] = (unsigned long)pc19;
    pu11 = (unsigned long *)cL4_alloc(0x28, u13);
    u13 = *pu10; u53 = pu10[3]; u28 = pu10[2];
    pu11[1] = pu10[1]; *pu11 = u13; pu11[3] = u53; pu11[2] = u28;
    pu11[4] = pu10[4];
    *out = (unsigned long)pu11;
l92984:
    if (canary == -0x2c8502b44bfffed6) { u13 = 0x28; goto l929a4; }
    goto canary_fail;
l92ed0:
    b22 = *(unsigned char *)((long)pu11 + 0x12);
    u17 = (unsigned long)b22;
    if (b22 != 1) {
        if (b22 == 5) u17 = (unsigned long)*(unsigned int *)(pu11 + 1);
        else {
            if (b22 != 2) goto l93cf8;
            u17 = 2;
        }
    }
    if (u17 <= u37) goto l93cf8;
    local_2a0 = (unsigned long **)CONCAT44(local_2a0, (int)((unsigned long)((long)stk_208 - (long)local_210) >> 3));
    sk_type_flatpair_3978b0(&local_100, &local_2a0);
    b22 = *(unsigned char *)((long)pu11 + 0x12);
    u17 = (unsigned long)b22;
    u36 = (unsigned int)b22;
    if (u36 == 1) {
        if (u17 <= u37) goto l92f68;
        pu10 = pu11;
        if (1 < u36 - 1) pu10 = (unsigned long *)*pu11;
        ps20 = (short *)pu10[u37];
    } else {
        if (u36 == 5) { u17 = (unsigned long)*(unsigned int *)(pu11 + 1); goto l92f48; }
        if (b22 == 2) { u17 = 2; goto l92f48; }
l92f68:
        ps20 = 0;
    }
    ps29 = ps20 + 8;
    if (*ps29 != 0xf7) goto l93cf8;
    b22 = *(unsigned char *)(ps20 + 9);
    ps50 = ps20;
    if (b22 - 1 < 2) {
        if (b22 == 1) ps29 = ps20 + 4;
        else if (b22 != 2) {
            if (b22 == 5) { ps29 = *(short **)ps20; goto l92fc4; }
            ps29 = 0;
        }
    } else {
        if (b22 != 5) { ps50 = 0; goto l92fa8; }
        ps29 = *(short **)ps20;
        ps50 = ps29;
l92fc4:
        ps29 = ps29 + (unsigned long)*(unsigned int *)(ps20 + 4) * 4;
    }
    for (; ps50 != ps29; ps50 = ps50 + 4) {
        sk_type_decode_38f0a8(out, ctx, *(unsigned long *)ps50, i41 + 1, 0);
        if ((short)out[2] == 0) pp39 = (unsigned long *)*out;
        else {
            if ((short)out[2] == 1) goto l93dd8;
            pp39 = 0;
        }
        if (stk_208 < local_200) {
            pp52 = stk_208 + 1;
            *stk_208 = pp39;
            pp42 = local_210;
            pp9 = local_200;
        } else {
            l8 = (long)stk_208 - (long)local_210;
            u17 = (l8 >> 3) + 1;
            if (u17 >> 0x3d != 0) cL4_panic_big();
            u51 = (long)local_200 - (long)local_210 >> 2;
            if (u51 <= u17) u51 = u17;
            if (0x7ffffffffffffff7 < (unsigned long)((long)local_200 - (long)local_210)) u51 = 0x1fffffffffffffff;
            if (u51 == 0) rv[0] = 0;
            else { rv[0] = sk_type_realloc_38d9b4(&local_200); rv[1] = 0; }
            pl45 = (long *)(rv[0] + l8);
            pp9 = (unsigned long **)(rv[0] + rv[1] * 8);
            pp52 = (unsigned long **)(pl45 + 1);
            *pl45 = (long)pp39;
            pp42 = (unsigned long **)((long)pl45 - ((long)stk_208 - (long)local_210));
            cL4_obj_copy_simple((long)pp42, 0, 0);
            pp12 = local_210;
            if (local_210 != 0) {
                l8 = (long)local_200 - (long)local_210;
                local_210 = pp42;
                stk_208 = pp52;
                local_200 = pp9;
                cL4_free(pp12, l8);
                pp42 = local_210;
                pp9 = local_200;
            }
        }
        local_200 = pp9;
        local_210 = pp42;
        stk_208 = pp52;
        if ((short)out[2] == 1) ((void (*)(unsigned long, int, unsigned long))out[1])(*out, 3, 0);
    }
    u37 = u37 + 1;
    goto l92ed0;
l93cf8:
    local_2a0 = (unsigned long **)CONCAT44(local_2a0, (int)((unsigned long)((long)stk_208 - (long)local_210) >> 3));
    sk_type_flatpair_3978b0(&local_100, &local_2a0);
    local_2a0 = 0;
    stk_298 = 0;
    local_290[0] = 0;
    if ((long)stk_f8 - (long)local_100 != 4) {
        u51 = (long)stk_f8 - (long)local_100 >> 2;
        u37 = 0;
        u17 = 1;
        do {
            if ((u51 <= u37) || (u51 <= u17)) {
                cL4_stack_fail();
            }
            u36 = *(unsigned int *)((long)local_100 + u37 * 4);
            local_330 = local_210 + u36;
            local_3c0 = (unsigned long **)CONCAT44(local_3c0, *(int *)((long)local_100 + u17 * 4) - u36);
            sk_type_push98_397998(&local_2a0, &local_330, &local_3c0);
            u51 = (long)stk_f8 - (long)local_100 >> 2;
            b5 = u17 < u51 - 1;
            u37 = u17;
            u17 = (unsigned long)((int)u17 + 1);
        } while (b5);
    }
    sk_type_build_bound_397a98(out, *ctx, u28, local_2a0, (long)stk_298 - (long)local_2a0 >> 4, u13);
    if (local_2a0 != 0) {
        stk_298 = local_2a0;
        cL4_free(local_2a0, (long)local_290[0] - (long)local_2a0);
    }
l93dd8:
    if (local_100 != 0) {
        stk_f8 = local_100;
        cL4_free(local_100, (long)local_f0 - (long)local_100);
    }
    if (local_210 != 0) {
        u37 = (long)local_200 - (long)local_210;
        local_1f8 = local_210;
        stk_208 = local_210;
l91030:
        cL4_free(local_1f8, u37);
    }
    goto fin;
l8fd5c:
    b22 = (unsigned char)((unsigned short *)node)[9];
    u17 = (unsigned long)b22;
    u36 = (unsigned int)b22;
    if (b22 != 1) {
        if (b22 == 5) { u51 = (unsigned long)*(unsigned int *)(node + 4); goto l8fd8c; }
        if (u36 == 2) { u51 = 2; goto l8fd8c; }
l903c8:
        u37 = (unsigned long)local_328 & 0xffffffff;
        if ((unsigned int)local_328 < 2) {
            *out = (unsigned long)s_unknown_error_005d5481;
            out[1] = (unsigned long)FUN_0037f9f4;
            *(unsigned short *)(out + 2) = 1;
        } else {
            u43 = ((unsigned short *)node)[8];
            if (b22 == 3) { u47 = *(unsigned int *)(node + 4); pu48 = *(unsigned char **)node; }
            else { u47 = 0; pu48 = (unsigned char *)&DAT_005be7c0; }
            pu10 = (unsigned long *)cL4_alloc(0x28, 0x1050c400dfe80cb);
            *pu10 = (unsigned long)s_TypeDecoder_h__u__Node_kind__u___005d587a;
            *(unsigned int *)(pu10 + 1) = 0x4c6;
            *(unsigned int *)((long)pu10 + 0xc) = (unsigned int)u43;
            *(unsigned int *)(pu10 + 2) = u47;
            pu10[3] = (unsigned long)pu48;
            pu10[4] = u37;
            *(unsigned short *)(out + 2) = 1;
            out[1] = (unsigned long)FUN_00397fc0;
            pu11 = (unsigned long *)cL4_alloc(0x28, 0x1050c400dfe80cb);
            u13 = *pu10; u53 = pu10[3]; u28 = pu10[2];
            pu11[1] = pu10[1]; *pu11 = u13; pu11[3] = u53; pu11[2] = u28;
            pu11[4] = pu10[4];
            *out = (unsigned long)pu11;
            cL4_free(pu10, 0x28);
        }
        goto l93c70;
    }
    u51 = 1;
l8fd8c:
    if (u51 <= u37) goto l903c8;
    if (u36 == 1) {
        if (u17 <= u37) goto l8fdd8;
        pu26 = (unsigned short *)node;
        if (1 < u36 - 1) pu26 = *(unsigned short **)node;
        pl45 = *(long **)(pu26 + u37 * 4);
    } else {
        if (b22 == 5) { u17 = (unsigned long)*(unsigned int *)(node + 4); goto l8fdb8; }
        if (b22 == 2) { u17 = 2; goto l8fdb8; }
l8fdd8:
        pl45 = 0;
    }
    u36 = (unsigned int)*(unsigned short *)(pl45 + 2);
    if (0x14 < u36 - 0x6b) goto case_70;
    switch (u36) {
    case 0x6c:
        if (*(char *)((long)pl45 + 0x12) != 3) {
            pu10 = (unsigned long *)cL4_alloc(0x28, 0x1050c401ab4594e);
            *pu10 = (unsigned long)s_TypeDecoder_h__u__Node_kind__u___005d54b8;
            u13 = DAT_004f28b0;
            goto l93428;
        }
        break;
    case 0x70: case 0x71: case 0x72: case 0x73: case 0x76: case 0x77: case 0x79:
    case 0x7a: case 0x7c:
        goto case_70;
    case 0x74:
        if (*(char *)((long)pl45 + 0x12) != 3) {
            pu10 = (unsigned long *)cL4_alloc(0x28, 0x1050c401ab4594e);
            *pu10 = (unsigned long)s_TypeDecoder_h__u__Node_kind__u___005d54b8;
            u13 = DAT_004f2898;
            goto l93428;
        }
        break;
    case 0x75:
        b22 = *(unsigned char *)((long)pl45 + 0x12);
        u36 = b22 - 1;
        pl32 = pl45;
        if (u36 < 2) {
            if (*(short *)(*pl32 + 0x10) == 0x76) {
                if (u36 < 2) {
                    if (*(char *)(*pl45 + 0x12) != 3) { u47 = 0; pu48 = (unsigned char *)&DAT_005be7c0; goto l93bdc; }
                } else if (*(char *)(*(long *)*pl45 + 0x12) != 3) goto l8ff88;
                break;
            }
l8ff88:
            if (b22 == 3) { u47 = (unsigned int)pl45[1]; pu48 = (unsigned char *)*pl45; }
            else { u47 = 0; pu48 = (unsigned char *)&DAT_005be7c0; }
l93bdc:
            pu10 = (unsigned long *)cL4_alloc(0x28, 0x1050c401ab4594e);
            *pu10 = (unsigned long)s_TypeDecoder_h__u__Node_kind__u___005d54b8;
            pu10[1] = DAT_004f28a0;
            *(unsigned int *)(pu10 + 2) = u47;
            pc18 = (char *)s_expected_convention_name_005d5788;
        } else {
            if (b22 == 5) {
                if ((int)pl45[1] != 0) { pl32 = (long *)*pl45; goto l8fe84; }
                u47 = 0; pu48 = (unsigned char *)&DAT_005be7c0;
            } else {
                if (b22 != 3) { u47 = 0; pu48 = (unsigned char *)&DAT_005be7c0; }
                else { u47 = (unsigned int)pl45[1]; pu48 = (unsigned char *)*pl45; }
            }
            pu10 = (unsigned long *)cL4_alloc(0x28, 0x1050c401ab4594e);
            *pu10 = (unsigned long)s_TypeDecoder_h__u__Node_kind__u___005d54b8;
            pu10[1] = DAT_004f28a8;
            *(unsigned int *)(pu10 + 2) = u47;
            pc18 = (char *)s_expected_grandchildren_005d5771;
        }
        pu10[3] = (unsigned long)pu48;
        goto l93c24;
    case 0x78:
        if (*(char *)((long)pl45 + 0x12) != 3) {
            pu10 = (unsigned long *)cL4_alloc(0x28, 0x1050c401ab4594e);
            *pu10 = (unsigned long)s_TypeDecoder_h__u__Node_kind__u___005d54b8;
            u13 = DAT_004f2888;
            goto l93428;
        }
        pl32 = (long *)*pl45;
        l8 = pl45[1];
        if (l8 == 0xc) {
            u36 = *(unsigned int *)(pl32 + 1);
            b5 = *pl32 == 0x6e6f5f646c656979;
            u15 = 0x325f6563;
l8ff68:
            if (b5 && u36 == u15) break;
        } else if (l8 == 10) {
            if (*pl32 == 0x6e6f5f646c656979 && (short)pl32[1] == 0x6563) break;
            u36 = (unsigned int)*(unsigned short *)(pl32 + 1);
            b5 = *pl32 == 0x616d5f646c656979;
            u15 = 0x796e;
            goto l8ff68;
        }
        pu10 = (unsigned long *)cL4_alloc(0x28, 0x1050c401ab4594e);
        *pu10 = (unsigned long)s_TypeDecoder_h__u__Node_kind__u___005d54b8;
        pu10[1] = DAT_004f2890;
        *(int *)(pu10 + 2) = (int)l8;
        pc18 = (char *)s_failed_to_decode_coroutine_kind_005d57c4;
        pu10[3] = (unsigned long)pl32;
l93444:
        pu10[4] = (unsigned long)pc18;
        *(unsigned short *)(out + 2) = 1;
        out[1] = (unsigned long)FUN_00397f0c;
        pu11 = (unsigned long *)cL4_alloc(0x28, 0x1050c401ab4594e);
        u13 = *pu10; u53 = pu10[3]; u28 = pu10[2];
        pu11[1] = pu10[1]; *pu11 = u13; pu11[3] = u53; pu11[2] = u28;
        pu11[4] = pu10[4];
        *out = (unsigned long)pu11;
        cL4_free(pu10, 0x28);
        goto l93c70;
    case 0x7b:
        i7 = sk_type_decode_param_396aec(ctx, pl45, i41 + 1, &local_210);
        if (i7 != 0) {
            u43 = *(unsigned short *)(pl45 + 2);
            if (*(char *)((long)pl45 + 0x12) == 3) { u47 = (unsigned int)pl45[1]; pu48 = (unsigned char *)*pl45; }
            else { u47 = 0; pu48 = (unsigned char *)&DAT_005be7c0; }
            pu10 = (unsigned long *)cL4_alloc(0x28, 0x1050c401ab4594e);
            *pu10 = (unsigned long)s_TypeDecoder_h__u__Node_kind__u___005d54b8;
            *(unsigned int *)(pu10 + 1) = 0x4ab;
            *(unsigned int *)((long)pu10 + 0xc) = (unsigned int)u43;
            *(unsigned int *)(pu10 + 2) = u47;
            pc18 = (char *)s_failed_to_decode_function_parame_005d57e4;
            goto l93bc0;
        }
        break;
    case 0x7d:
        i7 = sk_type_decode_result_396d48(ctx, pl45, i41 + 1, &local_2a0);
        if (i7 != 0) {
            u43 = *(unsigned short *)(pl45 + 2);
            if (*(char *)((long)pl45 + 0x12) == 3) { u47 = (unsigned int)pl45[1]; pu48 = (unsigned char *)*pl45; }
            else { u47 = 0; pu48 = (unsigned char *)&DAT_005be7c0; }
            pu10 = (unsigned long *)cL4_alloc(0x28, 0x1050c401ab4594e);
            *pu10 = (unsigned long)s_TypeDecoder_h__u__Node_kind__u___005d54b8;
            *(unsigned int *)(pu10 + 1) = 0x4b3;
            *(unsigned int *)((long)pu10 + 0xc) = (unsigned int)u43;
            *(unsigned int *)(pu10 + 2) = u47;
            pc18 = (char *)s_failed_to_decode_function_result_005d5829;
            goto l93bc0;
        }
        break;
    case 0x7e:
        i7 = sk_type_decode_param_396aec(ctx, pl45, i41 + 1, &local_100);
        if (i7 != 0) {
            u43 = *(unsigned short *)(pl45 + 2);
            if (*(char *)((long)pl45 + 0x12) == 3) { u47 = (unsigned int)pl45[1]; pu48 = (unsigned char *)*pl45; }
            else { u47 = 0; pu48 = (unsigned char *)&DAT_005be7c0; }
            pu10 = (unsigned long *)cL4_alloc(0x28, 0x1050c401ab4594e);
            *pu10 = (unsigned long)s_TypeDecoder_h__u__Node_kind__u___005d54b8;
            *(unsigned int *)(pu10 + 1) = 0x4af;
            *(unsigned int *)((long)pu10 + 0xc) = (unsigned int)u43;
            *(unsigned int *)(pu10 + 2) = u47;
            pc18 = (char *)s_failed_to_decode_function_yields_005d5808;
            goto l93bc0;
        }
        break;
    case 0x7f:
        i7 = sk_type_decode_result_396d48(ctx, pl45, i41 + 1, &local_330);
        if (i7 != 0) {
            u43 = *(unsigned short *)(pl45 + 2);
            if (*(char *)((long)pl45 + 0x12) == 3) { u47 = (unsigned int)pl45[1]; pu48 = (unsigned char *)*pl45; }
            else { u47 = 0; pu48 = (unsigned char *)&DAT_005be7c0; }
            pu10 = (unsigned long *)cL4_alloc(0x28, 0x1050c401ab4594e);
            *pu10 = (unsigned long)s_TypeDecoder_h__u__Node_kind__u___005d54b8;
            *(unsigned int *)(pu10 + 1) = 0x4b7;
            *(unsigned int *)((long)pu10 + 0xc) = (unsigned int)u43;
            *(unsigned int *)(pu10 + 2) = u47;
            pc18 = (char *)s_failed_to_decode_function_part_005d584b;
            goto l93bc0;
        }
    }
    u37 = u37 + 1;
    goto l8fd5c;
case_70:
    if (*(char *)((long)pl45 + 0x12) == 3) { u47 = (unsigned int)pl45[1]; pu48 = (unsigned char *)*pl45; }
    else { u47 = 0; pu48 = (unsigned char *)&DAT_005be7c0; }
    pu10 = (unsigned long *)cL4_alloc(0x28, 0x1050c401ab4594e);
    *pu10 = (unsigned long)s_TypeDecoder_h__u__Node_kind__u___005d54b8;
    *(unsigned int *)(pu10 + 1) = 0x4b9;
    *(unsigned int *)((long)pu10 + 0xc) = u36;
    *(unsigned int *)(pu10 + 2) = u47;
    pc18 = (char *)s_unexpected_kind_005d586a;
l93bc0:
    pu10[3] = (unsigned long)pu48;
l93c24:
    pu10[4] = (unsigned long)pc18;
    *(unsigned short *)(out + 2) = 1;
    out[1] = (unsigned long)FUN_00397f0c;
    pu11 = (unsigned long *)cL4_alloc(0x28, 0x1050c401ab4594e);
    u13 = *pu10; u53 = pu10[3]; u28 = pu10[2];
    pu11[1] = pu10[1]; *pu11 = u13; pu11[3] = u53; pu11[2] = u28;
    pu11[4] = pu10[4];
    *out = (unsigned long)pu11;
    cL4_free(pu10, 0x28);
l93c70:
    if (local_330 != (unsigned long **)local_320) cL4_free(0, 0);
    if (local_2a0 != (unsigned long **)local_290) cL4_free(0, 0);
    if (local_100 != &local_f0) cL4_free(0, 0);
    if ((unsigned long **)local_210 == &local_200) goto fin;
    goto l9366c;
    /* pack-expansion field walk (loop body for the 0xec protocol list) */
    while (cL4_list_push_363f10(&local_210, l8), pu11 = pu10, pu10 != pu24) {
        pu10 = pu11 + 1;
        pu11 = (unsigned long *)*pu11;
        l8 = sk_type_parse_signature_395638(ctx, pu11, i41 + 1);
        if (l8 == 0) {
            u43 = *(unsigned short *)(pu11 + 2);
            if (*(char *)((long)pu11 + 0x12) == 3) { u47 = *(unsigned int *)(pu11 + 1); pu48 = (unsigned char *)*pu11; }
            else { u47 = 0; pu48 = (unsigned char *)&DAT_005be7c0; }
            u13 = 0x1050c401ab4594e;
            pu10 = (unsigned long *)cL4_alloc(0x28, 0x1050c401ab4594e);
            *pu10 = (unsigned long)s_TypeDecoder_h__u__Node_kind__u___005d54b8;
            *(unsigned int *)(pu10 + 1) = 0x358;
            *(unsigned int *)((long)pu10 + 0xc) = (unsigned int)u43;
            *(unsigned int *)(pu10 + 2) = u47;
            pu10[3] = (unsigned long)pu48;
            pu10[4] = (unsigned long)s_failed_to_decode_protocol_type_005d5654;
            *(unsigned short *)(out + 2) = 1;
            pc19 = FUN_00397f0c;
            goto l9245c;
        }
    }
    u43 = ((unsigned short *)node)[8];
l912e0:
    if (u43 == 0xca) {
        u37 = 0; u47 = 0;
        b22 = (unsigned char)((unsigned short *)node)[9];
        pu48 = (unsigned char *)&DAT_005be7c0;
        if (b22 < 3) {
            pu48 = (unsigned char *)&DAT_005be7c0;
            if (b22 == 1) { u47 = 0; u37 = 1; }
            else if (b22 == 2) goto l92e54;
        } else if (b22 == 3) {
            u37 = 0; u47 = *(unsigned int *)(node + 4); pu48 = *(unsigned char **)node;
        } else if (b22 == 5) {
            u37 = (unsigned long)*(unsigned int *)(node + 4);
            if (1 < *(unsigned int *)(node + 4)) { node = *(unsigned short **)node; goto l92e54; }
            u47 = 0;
        }
        u13 = 0x1050c400dfe80cb;
        pu10 = (unsigned long *)cL4_alloc(0x28, 0x1050c400dfe80cb);
        *pu10 = (unsigned long)s_TypeDecoder_h__u__Node_kind__u___005d54f0;
        pu10[1] = DAT_004f28c8;
        *(unsigned int *)(pu10 + 2) = u47;
        pu10[3] = (unsigned long)pu48;
        pu10[4] = u37;
        *(unsigned short *)(out + 2) = 1;
        pc19 = FUN_00397fc0;
l9245c:
        out[1] = (unsigned long)pc19;
        pu11 = (unsigned long *)cL4_alloc(0x28, u13);
        u13 = *pu10; u53 = pu10[3]; u28 = pu10[2];
        pu11[1] = pu10[1]; *pu11 = u13; pu11[3] = u53; pu11[2] = u28;
        pu11[4] = pu10[4];
        *out = (unsigned long)pu11;
        cL4_free(pu10, 0x28);
    } else {
        l8 = 0;
        b5 = u43 == 0xcb;
        goto l91324;
    }
l9248c:
    if ((unsigned long **)local_210 == &local_200) goto fin;
    goto l9366c;
    /* 0xee/0xef/0xf0 protocol-requirement list body */
l90420:
    do {
        pu10 = *(unsigned long **)pu25;
        s = *(short *)(pu10 + 2);
        if (s == 0xf4) {
            if (1 < *(unsigned char *)((long)pu10 + 0x12) - 1) pu10 = (unsigned long *)*pu10;
            pu10 = (unsigned long *)*pu10;
            s = *(short *)(pu10 + 2);
        }
        if (s == 0xf1) {
            b22 = *(unsigned char *)((long)pu10 + 0x12);
            if (b22 < 3) {
                if (b22 == 2) {
                    u13 = *pu10;
                    sk_type_decode_38f0a8(&local_100, ctx, pu10[1], i41 + 1, 1);
                    pc19 = (void (*)(unsigned long, int, unsigned long))stk_f8;
                    if ((short)local_f0 == 1) {
                        node = (unsigned short *)((unsigned long (*)(unsigned long, int, unsigned long))stk_f8)(local_100, 2, 0);
                        b6 = false; b5 = true;
                    } else {
                        pp9 = local_100;
                        if ((short)local_f0 != 0) pp9 = 0;
                        l8 = sk_type_lookup_field_398f40(*ctx, pp9);
                        if (l8 == 0) { b5 = false; pc19 = (void (*)(unsigned long, int, unsigned long))0; }
                        else {
                            l49 = 0; b5 = false; pc19 = (void (*)(unsigned long, int, unsigned long))0;
                            do {
                                l35 = *(long *)(*ctx + 0x58);
                                if (*(long *)(*ctx + 0x50) == l35) goto l94250;
                                *(long *)(l35 + -8) = l49;
                                sk_type_decode_38f0a8(&local_2a0, ctx, u13, i41 + 1, 1);
                                pp9 = stk_298;
                                s = (short)local_290[0];
                                if ((short)local_290[0] == 1) {
                                    node = (unsigned short *)((unsigned long (*)(unsigned long, int, unsigned long))stk_298)(local_2a0, 2, 0);
                                    b5 = true;
                                    pc19 = (void (*)(unsigned long, int, unsigned long))pp9;
                                } else {
                                    pp9 = local_2a0;
                                    if ((short)local_290[0] != 0) pp9 = 0;
                                    cL4_list_push_363f10(&local_210, pp9);
                                }
                                if ((short)local_290[0] == 1) ((void (*)(unsigned long, int, unsigned long))stk_298)(local_2a0, 3, 0);
                                if (s == 1) { b6 = false; goto l9063c; }
                                l49 = l49 + 1;
                            } while (l8 != l49);
                        }
                        l8 = *ctx;
                        if (*(long *)(l8 + 0x50) == *(long *)(l8 + 0x58)) goto l94260;
                        *(long *)(l8 + 0x58) = *(long *)(l8 + 0x58) + -0x10;
                        b6 = true;
                    }
l9063c:
                    if ((short)local_f0 == 1) ((void (*)(unsigned long, int, unsigned long))stk_f8)(local_100, 3, 0);
                    if (b6) goto l90660;
                    if (b5) goto l92018;
                    goto l9066c;
                }
                if (b22 == 1) { u47 = 0; pu48 = (unsigned char *)&DAT_005be7c0; u37 = 1; }
                else { u37 = 0; u47 = 0; pu48 = (unsigned char *)&DAT_005be7c0; }
            } else {
                if (b22 == 5) {
                    u37 = (unsigned long)*(unsigned int *)(pu10 + 1);
                    if (*(unsigned int *)(pu10 + 1) < 2) { u47 = 0; pu48 = (unsigned char *)&DAT_005be7c0; }
                    else { pu10 = (unsigned long *)*pu10; goto l904bc; }
                } else {
                    if (b22 != 3) { u37 = 0; u47 = 0; pu48 = (unsigned char *)&DAT_005be7c0; }
                    else { u37 = 0; u47 = *(unsigned int *)(pu10 + 1); pu48 = (unsigned char *)*pu10; }
                }
            }
            node = (unsigned short *)cL4_alloc(0x28, 0x1050c400dfe80cb);
            *(char **)node = (char *)s_TypeDecoder_h__u__Node_kind__u___005d54f0;
            *(long *)(node + 4) = DAT_004f2858;
            *(unsigned int *)(node + 8) = u47;
            *(unsigned char **)(node + 0xc) = pu48;
            *(unsigned long *)(node + 0x10) = u37;
            pc19 = FUN_00397fc0;
l92018:
            *(unsigned short *)(out + 2) = 1;
            out[1] = (unsigned long)pc19;
            l8 = ((unsigned long (*)(unsigned long, int, unsigned long))pc19)(node, 2, 0);
            *out = l8;
            ((void (*)(unsigned long, int, unsigned long))pc19)(node, 3, 0);
            goto l92054;
        }
        sk_type_decode_38f0a8(&local_100, ctx, pu10, i41 + 1, 0);
        pc19 = (void (*)(unsigned long, int, unsigned long))stk_f8;
        s = (short)local_f0;
        if ((short)local_f0 == 1) {
            node = (unsigned short *)((unsigned long (*)(unsigned long, int, unsigned long))stk_f8)(local_100, 2, 0);
        } else {
            pp9 = local_100;
            if ((short)local_f0 != 0) pp9 = 0;
            cL4_list_push_363f10(&local_210, pp9);
            pc19 = (void (*)(unsigned long, int, unsigned long))0;
        }
        if ((short)local_f0 == 1) ((void (*)(unsigned long, int, unsigned long))stk_f8)(local_100, 3, 0);
        if (s == 1) goto l92018;
l90660:
        node = (unsigned short *)((unsigned long)node & 0xffffffffffffff00);
l9066c:
        pu25 = pu25 + 4;
    } while (pu25 != pu16);
    u43 = *pu26;
    u37 = (unsigned long)stk_208 & 0xffffffff;
l90694:
    if ((u43 == 0xf0) || (u43 == 0xef)) sk_type_materialize_req_3972cc(out);
    else sk_type_materialize_req2_3971e8(out, local_210, u37);
l92054:
    pp9 = &local_200;
    pp12 = local_210;
    goto l93664;
l94250:
    pc18 = (char *)s_advancePackExpansion___without_b_005d5db6;
    goto l94258;
l94260:
    pc18 = (char *)s_endPackExpansion___without_begin_005d5deb;
l94258:
    cL4_stack_fail();
    /* 0xeb protocol-requirement list loop */
    while (pu26 = pu26 + 4, pu26 != pu25) {
l91c30:
        pu10 = *(unsigned long **)pu26;
        if (*(short *)(pu10 + 2) != 0xec) {
            u43 = ((unsigned short *)node)[8];
            if ((char)((unsigned short *)node)[9] == 3) { u47 = *(unsigned int *)(node + 4); pu48 = *(unsigned char **)node; }
            else { u47 = 0; pu48 = (unsigned char *)&DAT_005be7c0; }
            pu11 = (unsigned long *)cL4_alloc(0x28, 0x1050c401ab4594e);
            *pu11 = (unsigned long)s_TypeDecoder_h__u__Node_kind__u___005d54b8;
            *(unsigned int *)(pu11 + 1) = 0x4e5;
            *(unsigned int *)((long)pu11 + 0xc) = (unsigned int)u43;
            *(unsigned int *)(pu11 + 2) = u47;
            pu11[3] = (unsigned long)pu48;
            pu11[4] = (unsigned long)s_unexpected_kind_005d586a;
            *(unsigned short *)(out + 2) = 1;
            out[1] = (unsigned long)FUN_00397f0c;
            pu10 = (unsigned long *)cL4_alloc(0x28, 0x1050c401ab4594e);
            u13 = *pu11; u53 = pu11[3]; u28 = pu11[2];
            pu10[1] = pu11[1]; *pu10 = u13; pu10[3] = u53; pu10[2] = u28;
            pu10[4] = pu11[4];
            *out = (unsigned long)pu10;
l92d30:
            cL4_free(pu11, 0x28);
            goto l93650;
        }
        if (1 < *(unsigned char *)((long)pu10 + 0x12) - 1) pu10 = (unsigned long *)*pu10;
        pu10 = (unsigned long *)*pu10;
        if (*(short *)(pu10 + 2) == 0x122) {
            if (*(char *)((long)pu10 + 0x12) == 3) { u47 = *(unsigned int *)(pu10 + 1); pu48 = (unsigned char *)*pu10; }
            else { u47 = 0; pu48 = (unsigned char *)&DAT_005be7c0; }
            pu11 = (unsigned long *)cL4_alloc(0x28, 0x1050c401ab4594e);
            *pu11 = (unsigned long)s_TypeDecoder_h__u__Node_kind__u___005d54b8;
            pu11[1] = DAT_004f2870;
            *(unsigned int *)(pu11 + 2) = u47;
            pu11[3] = (unsigned long)pu48;
            pu11[4] = (unsigned long)s_no_children_005d55ed;
            *(unsigned short *)(out + 2) = 1;
            out[1] = (unsigned long)FUN_00397f0c;
            pu10 = (unsigned long *)cL4_alloc(0x28, 0x1050c401ab4594e);
            u13 = *pu11; u53 = pu11[3]; u28 = pu11[2];
            pu10[1] = pu11[1]; *pu10 = u13; pu10[3] = u53; pu10[2] = u28;
            pu10[4] = pu11[4];
            *out = (unsigned long)pu10;
            goto l92d30;
        }
        local_360 = 0;
        stk_358 = 0;
        pu10 = *(unsigned long **)pu26;
        u36 = *(unsigned char *)((long)pu10 + 0x12) - 1;
        if (u36 < 2) pu11 = (unsigned long *)*pu10;
        else pu11 = *(unsigned long **)*pu10;
        if (*(short *)(pu11 + 2) == 0xed) {
            stk_358 = (unsigned long **)pu11[1];
            local_360 = (unsigned long *)*pu11;
        }
        if (1 < u36) pu10 = (unsigned long *)*pu10;
        pu10 = (unsigned long *)pu10[*(short *)(pu11 + 2) == 0xed];
        local_3b0[0] = &local_360;
        s = *(short *)(pu10 + 2);
        if (s == 0xf4) {
            if (1 < *(unsigned char *)((long)pu10 + 0x12) - 1) pu10 = (unsigned long *)*pu10;
            pu10 = (unsigned long *)*pu10;
            s = *(short *)(pu10 + 2);
        }
        local_3c0 = &local_100;
        local_3b8 = &local_210;
        if (s == 0xf1) {
            b22 = *(unsigned char *)((long)pu10 + 0x12);
            if (b22 < 3) {
                if (b22 != 2) {
                    if (b22 == 1) { u47 = 0; pu48 = (unsigned char *)&DAT_005be7c0; u37 = 1; }
                    else { u37 = 0; u47 = 0; pu48 = (unsigned char *)&DAT_005be7c0; }
                    goto l935c0;
                }
            } else {
                if (b22 != 5) {
                    if (b22 != 3) { u37 = 0; u47 = 0; pu48 = (unsigned char *)&DAT_005be7c0; goto l935c0; }
                    u37 = 0; u47 = *(unsigned int *)(pu10 + 1); pu48 = (unsigned char *)*pu10;
                    goto l935c0;
                }
                u37 = (unsigned long)*(unsigned int *)(pu10 + 1);
                if (*(unsigned int *)(pu10 + 1) < 2) { u47 = 0; pu48 = (unsigned char *)&DAT_005be7c0; }
                else pu10 = (unsigned long *)*pu10;
            }
            u13 = *pu10;
            sk_type_decode_38f0a8(&local_2a0, ctx, pu10[1], i41 + 1, 1);
            pp12 = stk_298;
            if ((short)local_290[0] == 1) {
                local_3d8 = (unsigned long *)((unsigned long (*)(unsigned long, int, unsigned long))stk_298)(local_2a0, 2, 0);
                b5 = true;
                goto l91f0c;
            } else {
                pp12 = local_2a0;
                if ((short)local_290[0] != 0) pp12 = 0;
                l8 = sk_type_lookup_field_398f40(*ctx, pp12);
                if (l8 == 0) b5 = false;
                else {
                    l49 = 0; b5 = false;
                    do {
                        l35 = *(long *)(*ctx + 0x58);
                        if (*(long *)(*ctx + 0x50) == l35) goto l94250;
                        *(long *)(l35 + -8) = l49;
                        sk_type_decode_38f0a8(&local_330, ctx, u13, i41 + 1, 1);
                        s = local_320[0];
                        pp12 = local_328;
                        if (local_320[0] == 1) {
                            local_3d8 = (unsigned long *)((unsigned long (*)(unsigned long, int, unsigned long))local_328)(local_330, 2, 0);
                            b5 = true;
                        } else {
                            pp12 = local_330;
                            if (local_320[0] != 0) pp12 = 0;
                            cL4_list_push_363f10(&local_100, pp12);
                            sk_type_65184_365184(&local_210, local_360, stk_358);
                        }
                        if (local_320[0] == 1) ((void (*)(unsigned long, int, unsigned long))local_328)(local_330, 3, 0);
                        if (s == 1) goto l91f0c;
                        l49 = l49 + 1;
                    } while (l8 != l49);
                }
                l8 = *ctx;
                if (*(long *)(l8 + 0x50) == *(long *)(l8 + 0x58)) goto l94260;
                *(long *)(l8 + 0x58) = *(long *)(l8 + 0x58) + -0x10;
                b6 = true;
            }
            if ((short)local_290[0] == 1) ((void (*)(unsigned long, int, unsigned long))stk_298)(local_2a0, 3, 0);
            if (b6) goto l91f38;
            if (b5) goto l93610;
        } else {
            sk_type_decode_38f0a8(&local_2a0, ctx, pu10, i41 + 1, 0);
            pp12 = stk_298;
            s = (short)local_290[0];
            if ((short)local_290[0] == 1) {
                local_3d8 = (unsigned long *)((unsigned long (*)(unsigned long, int, unsigned long))stk_298)(local_2a0, 2, 0);
            } else {
                pp12 = local_2a0;
                if ((short)local_290[0] != 0) pp12 = 0;
                sk_type_pushreq_39951c(&local_3c0, pp12);
            }
            if ((short)local_290[0] == 1) ((void (*)(unsigned long, int, unsigned long))stk_298)(local_2a0, 3, 0);
            if (s == 1) {
l93610:
                *(unsigned short *)(out + 2) = 1;
                out[1] = (unsigned long)0;
                l8 = 0;
                *out = l8;
                goto l93650;
            }
l91f38:
            local_3d8 = (unsigned long *)((unsigned long)local_3d8 & 0xffffffffffffff00);
        }
    }
    u37 = (unsigned long)stk_f8 & 0xffffffff;
    u17 = (unsigned long)stk_208 & 0xffffffff;
l91f7c:
    sk_type_build_reqlist_396f78(out, local_100, u37, local_210, u17);
l93650:
    pp12 = local_100;
    if ((unsigned long **)local_210 != &local_200) { cL4_free(0, 0); pp12 = local_100; }
l93664:
    if (pp12 == pp9) goto fin;
l9366c:
    cL4_free(0, 0);
fin:
    if (canary == -0x2c8502b44bfffed6) return;
canary_fail:
    cL4_stack_fail();
}

/* FUN_0038a914 @ 0x38a914   (est. sk_type_lookup_name)
 * Ghidra: undefined1[16] FUN_0038a914(undefined8, long, undefined8)
 * Looks up a type by name: resolves the (possibly dotted) name via
 * FUN_0038cbb8, then drives the generic lookup core FUN_003895e0 with the
 * 0x67b960/0x67b9a8 string buckets, returning the 16-byte {metadata,error}
 * pair. On error (kind!=0) returns a null pair.
 * Confidence: medium */
cL4_w16_t sk_type_lookup_name_38a914(unsigned long a, long name, unsigned long b)
{
    unsigned long u; void (*fn)(unsigned long, int, unsigned long); cL4_w16_t r;
    unsigned long c[2]; unsigned int *p0; unsigned long *s1; unsigned long x; unsigned int *p2;
    unsigned long *s3; unsigned long out; void (*pc)(unsigned long, int, unsigned long);
    short kind; unsigned int state[2]; long v; unsigned long w; unsigned char *pkeep;
    unsigned long meta; unsigned char stack[256]; unsigned long scratch; long canary;

    if ((name == 0) || (name == 0)) name = 0;
    canary = -0x2c8502b44bfffed6;
    r = sk_type_name_split_38cbb8(name, b);
    if (name == 0) name = 0;
    state[0] = 0;
    p0 = state;
    meta = DAT_004f2710;
    scratch = 0;
    s3 = &out;
    out = 0x67b960;
    s1 = &c[0];
    c[0] = 0x67b9a8;
    p2 = p0;
    v = name;
    w = a;
    pkeep = stack;
    sk_type_lookup_core_3895e0(&x, 0, r.lo, r.hi, a, &out, &c[0]);
    if (kind == 1) pc(x, 3, 0);
    else {
        u = x;
        pc = (void (*)(unsigned long, int, unsigned long))0;
        if (kind == 0) goto out_lbl;
    }
    u = 0;
out_lbl:
    cL4_release(&c[0]);
    cL4_release(&out);
    if (pkeep != stack) thunk_FUN_00012568(0);
    if (canary != -0x2c8502b44bfffed6) cL4_stack_fail();
    r.hi = (unsigned long)pc;
    r.lo = u;
    return r;
}
