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
extern void cL4_panic_big(void);
extern void cL4_list_push_363f10();
#define CONCAT17(h,l)  ((unsigned long)(h) & 0xff | ((unsigned long)(l) << 8))
#define CONCAT44(h,l)  (((unsigned long)(l) & 0xffffffff) | ((unsigned long)(h) << 32))
#define CONCAT71(h,l)  ((unsigned long)(h) & 0x7f | ((unsigned long)(l) << 7))
#define CONCAT11(h,l)  ((unsigned long)(h) & 0xff | ((unsigned long)(l) << 8))

/* ------------------------------------------------------------------ *
 * Externs for the shared cL4 runtime / Swift metadata helpers called by
 * these bodies (they live elsewhere in the kernel image).
 * ------------------------------------------------------------------ */
extern void *cL4_alloc(unsigned long size, unsigned long tag);   /* FUN_00111890 */
extern void cL4_free(void *p, unsigned long size);
extern void thunk_FUN_00012568(unsigned long, ...);               /* thunk_FUN_00012568 */
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
extern volatile unsigned long *_DAT_006c0940;
extern volatile unsigned long _DAT_006c0920;
extern volatile unsigned long *_DAT_006c09e0;
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
extern long sk_strbuf_copy_38ef98();
extern long sk_strbuf_copy_38f020();
extern long sk_type_field_get_3a3430();
extern unsigned long sk_type_strfield_3a63f70();
extern long sk_type_a32a0_3a32a0();
extern unsigned long FUN_00377dcc();
extern unsigned long sk_type_metadata_get_3963b8();
extern long sk_type_parse_signature_395638();
extern unsigned long sk_type_realloc_38d9b4();
extern unsigned long sk_type_lookup_field_398f40();
extern long sk_type_decode_param_396aec();
extern long sk_type_decode_result_396d48();
extern cL4_w16_t sk_type_name_split_38cbb8();
extern cL4_w16_t sk_type_waiter_scan_38c640();
extern unsigned long sk_type_waiter_hash2_38c750();
extern unsigned long sk_type_capcmp_387fbc();
extern cL4_w16_t sk_type_read_3a31d8();
extern unsigned long sk_type_cap_build_3a32a0();
extern unsigned long *sk_vector_grow_399094(unsigned long, unsigned long, unsigned long);





/* Forward declarations (old-style) for in-file R50 functions. */
extern long sk_hashtable_chain_find_38c750();
extern unsigned long sk_hashtable_index_lookup2_38cae4();
extern unsigned long sk_hashtable_index_lookup3_38d690();
extern unsigned long sk_hashtable_index_lookup_38c920();
extern void sk_hashtable_unlink_38bf8c();
extern unsigned long sk_mangled_scan_valid_389da0();
extern void sk_mr_send_scan_match_380930();
extern void sk_mr_send_word_replace_380864();
extern unsigned long sk_pack_length_38d8dc();
extern long sk_strbuf_copy_38ef98();
extern long sk_strbuf_copy_38f020();
extern long sk_string_align_38cd54();
extern void sk_string_alloc_38c584();
extern unsigned long sk_string_base_38cdb4();
extern void sk_string_bucket_18_38c7bc();
extern void sk_string_bucket_60_38c87c();
extern void sk_string_bucket_60_38d52c();
extern void sk_string_bucket_a8_38c980();
extern void sk_string_bucket_a8_38d5ec();
extern void sk_string_bucket_f0_38ca40();
extern void sk_string_elem_at_38cbb8();
extern unsigned int sk_string_entcnt2_38d45c();
extern unsigned int sk_string_entcnt_38d07c();
extern unsigned int sk_string_entcnt_38d3b8();
extern long sk_string_fixed_38ccf8();
extern unsigned short sk_string_flag_08_38cfd8();
extern unsigned short sk_string_flag_0e_38cf50();
extern unsigned short sk_string_flag_10_38cecc();
extern unsigned short sk_string_flag_h17c_38d17c();
extern long sk_string_hdr_38cc7c();
extern unsigned short sk_string_len8_38ce48();
extern unsigned long sk_string_namebytes_38d204();
extern unsigned short sk_string_namecnt_38d330();
extern cL4_w16_t sk_string_namedesc_38d294();
extern long sk_string_tbl_base_38cc2c();
extern unsigned long sk_stringbuf_data_38c460();
extern cL4_w16_t sk_stringbuf_get_small_38c3ac();
extern unsigned short sk_stringbuf_len_38c4f4();
extern void sk_stringbuf_release_free2_38cb38();
extern void sk_stringbuf_release_free_38c32c();
extern void sk_tail_call_dispatch_38b4cc();
extern void sk_type_ctx_init_389130();
extern long sk_type_dbltbl_hash_38d6e4();
extern void sk_type_decode_38f0a8();
extern unsigned long sk_type_lookup_389940();
extern bool sk_type_lookup_check_3885e4();
extern void sk_type_lookup_core_3895e0();
extern void sk_type_lookup_dispatch2_389910();
extern void sk_type_lookup_dispatch3_389b4c();
extern cL4_w16_t sk_type_lookup_name_38a914();
extern unsigned long sk_type_lookup_quiet_389b64();
extern void sk_type_resolve_38a518();
extern void sk_vec_alloc_38d9b4();
extern void sk_vec_append_range_38e114();
extern void sk_vec_reserve_38d974();
extern void sk_vec_resize_38e198();
extern void sk_vector_push_back_38b814();
extern void sk_wordlist_append_389370();

extern unsigned long sk_type_field_set_3a3460();
extern void sk_type_build_sig_395f3c();
extern void sk_type_materialize_exist_39517c();
extern void sk_type_materialize_exist_3950a4();
extern void sk_type_generic_args_396440();
extern void sk_type_build_bound_generic_396784();
extern unsigned long sk_type_metadata_of_3bf904();
extern unsigned long sk_type_unpack_pair_37364c();
extern void sk_type_materialize_394c40();
extern void sk_type_materialize_397358();
extern unsigned long sk_type_build_pair_397e94();
extern void sk_type_decode_sig_394404();
extern void sk_type_build_func_394724();
extern void sk_type_build_protocol_3973e4();
extern void sk_type_decode_sig_394734();
extern void sk_type_build_func_3952c4();
extern void sk_type_build_owned_395dec();
extern long sk_type_decl_record_39779c();
extern unsigned long sk_type_list_push_363f10();
extern long sk_type_push8_39780c();
extern void sk_type_field_push_39787c();
extern void sk_type_flatpair_3978b0();
extern unsigned long * sk_type_push98_397998();
extern void sk_type_build_bound_397a98();
extern void sk_type_materialize_req_3972cc();
extern void sk_type_materialize_req2_3971e8();
extern void sk_type_build_reqlist_396f78();
extern unsigned long sk_type_65184_365184();
extern unsigned long sk_type_pushreq_39951c();
extern void sk_hashtable_hash_38ba00();
extern void sk_err_ctx_38dd44();
extern unsigned long sk_err_u64_113a3c();

extern long sk_cap_next_3658e8(unsigned long);
extern long sk_cap_meta_35eb3c(unsigned long);
extern void FUN_00114330(unsigned long, unsigned long);

/* SKR50 tail-batch forward declarations (correct return types). */
extern void sk_type_bucket_9f0_38ea44();
extern void sk_type_bucket_a38_38eb60();
extern void sk_type_bucket_a80_38ec3c();
extern void sk_type_build_decl_394968();
extern void sk_type_build_generic_38ad64();
extern void sk_type_cache_add_range_388fb0();
extern long sk_type_cache_lookup_388630();
extern void sk_type_decl_alloc_388c60();
extern long sk_type_decode_param_396aec();
extern long sk_type_decode_result_396d48();
extern void sk_type_demangle_resolve2_38a234();
extern void sk_type_demangle_resolve_389e8c();
extern unsigned long sk_type_elem_at_38bbf4();
extern unsigned long * sk_type_err_gen_arg_mismatch_38ece8();
extern unsigned long * sk_type_err_generic_args_38dfc8();
extern unsigned long * sk_type_err_generic_count_38e214();
extern unsigned long * sk_type_err_meta_pack_38e624();
extern unsigned long * sk_type_err_meta_type_38e458();
extern unsigned long * sk_type_err_unexpected_kind_38e7f0();
extern cL4_w16_t sk_type_flatpair_get_38bd54();
extern unsigned long sk_type_generic_scan_38a950();
extern bool sk_type_is_c_header_38ef30();
extern int sk_type_len8_add_38b948();
extern unsigned long sk_type_lookup_wrap_3893d0();
extern unsigned long sk_type_mangled_count_38b578();
extern unsigned long sk_type_mangled_push_389180();
extern unsigned long sk_type_metadata_get_3963b8();
extern void sk_type_table_release_38c0e8();
extern void sk_type_utf8_decode_38df24();
extern int sk_type_utf8_hi_38b85c();
extern unsigned long * sk_type_vec_insert_range_38d754();

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
    sk_type_decode_38f0a8(&meta, &c0, (unsigned long)ctx, 0, 0);
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
void sk_type_decode_38f0a8(void *outp, unsigned long *ctx, unsigned long nodev,
                           unsigned long depth, unsigned long flag)
{
    char c; short s; unsigned int u; unsigned char *pb; bool b5; bool b6; int i7;
    long l8; unsigned long **pp9; unsigned long *pu10; unsigned long *pu11;
    unsigned long u13; unsigned int u14; unsigned int u15; unsigned short *pu16;
    unsigned long u17; char *pc18; void (*pc19)(void);
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
    unsigned long **pp12; unsigned long **pp52; unsigned long u3; unsigned char *pu4;
    unsigned long local_1f0; unsigned long u_v51;
    unsigned long *out = (unsigned long *)outp;
    unsigned long *node = (unsigned long *)nodev;

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
joined_r8c8:
        if (pp9 == 0) {
            *out = (unsigned long)s_unknown_error_005d5481;
            out[1] = (unsigned long)FUN_0037f9f4;
            *(unsigned short *)(out + 2) = 1;
        }
        goto fin;
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
            goto l93930;
l93930:
            ((void (*)(unsigned long, int, unsigned long))pc19)((unsigned long)(unsigned long)pp9, 3, 0);
            goto fin;
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
                pc19 = (void (*)(void))stk_298;
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
                        if (1 < *(unsigned int *)(node + 4)) { pu25 = *(unsigned short **)node; goto l8f9bc; }
l8f9bc:
                        pu10 = *(unsigned long **)pu25;
                        u43 = *(unsigned short *)(pu10 + 2);
                        if (u43 != 0x9b) {
                            if (*(char *)((long)pu10 + 0x12) == 3) { u47 = *(unsigned int *)(pu10 + 1); pu48 = (unsigned char *)*pu10; }
                            else { u47 = 0; }
                            pu10 = (unsigned long *)cL4_alloc(0x28, 0x1050c401ab4594e);
                            *pu10 = (unsigned long)s_TypeDecoder_h__u__Node_kind__u___005d54b8;
                            *(unsigned int *)(pu10 + 1) = 799;
                            *(unsigned int *)((long)pu10 + 0xc) = (unsigned int)u43;
                            *(unsigned int *)(pu10 + 2) = u47;
                            pc18 = (char *)s_wrong_node_kind_or_no_text_005d55d2;
                            goto l92940;
                        }
                        node = (unsigned short *)pu10;
                        goto follow_child;
                        if (*(unsigned int *)(node + 4) != 0) { l8 = 0; goto l91644; }
                        u47 = 0; pu48 = (unsigned char *)&DAT_005be7c0;
                    }
                    goto l90cd8;
                    goto l90cd8;
l90cd8:
                    pu10 = (unsigned long *)cL4_alloc(0x28, 0x1050c401ab4594e);
                    *pu10 = (unsigned long)s_TypeDecoder_h__u__Node_kind__u___005d54b8;
                    u14 = 0x327;
                    goto l91754;
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
                if (*(int *)(node + 4) == 0) pd34 = (unsigned int *)0;
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
                        l8 = ((unsigned long (*)(unsigned long, int, unsigned long))stk_f8)((unsigned long)local_100, 2, 0);
                        *out = l8;
l92810:
                        ((void (*)(unsigned long, int, unsigned long))pp42)((unsigned long)pp12, 3, 0);
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
                            ((void (*)(unsigned long, int, unsigned long))stk_298)((unsigned long)local_2a0, 3, 0);
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
                u14 = (unsigned int)(unsigned long)local_200;
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
                ((void (*)(unsigned long, int, unsigned long))stk_f8)((unsigned long)local_100, 3, 0);
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
                l8 = ((unsigned long (*)(unsigned long, int, unsigned long))stk_208)((unsigned long)local_210, 2, 0);
                *out = l8;
                ((void (*)(unsigned long, int, unsigned long))pp12)((unsigned long)pp9, 3, 0);
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
            pc19 = (void (*)(void))stk_208;
            s = (short)local_200;
            goto joined_32e0;
        }
err_28:
        pu10[1] = u13;
        *(unsigned int *)(pu10 + 2) = u47;
        pu10[3] = (unsigned long)pu48;
        pc18 = (char *)s_no_children_005d55ed;
        goto l92944;
l925f0:
        pu10[4] = u37;
l925f4:
        u13 = 0x1050c400dfe80cb;
        *(unsigned short *)(out + 2) = 1;
        pc19 = FUN_00397fc0;
        goto l92960;
    }
f2fc:
        node = (unsigned short *)*node;
        goto l8f3e4;
l8f3e4:
follow_child:
        node = (unsigned short *)*node;
        depth = (unsigned long)(i41 + 1U);
        if (i41 + 1U == 0x401) goto too_complex;
        goto dispatch;
    /* ---- node kinds >= 0x77 ---- */
    if (u36 != 0x134 && 0x133 < u43) {
        if (u36 != 0x13a && 0x139 < u43) {
            if (0x16a < u43) {
case_16b:
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
                l8 = ((unsigned long (*)(unsigned long, int, unsigned long))stk_f8)((unsigned long)local_100, 2, 0);
                *out = l8;
                ((void (*)(unsigned long, int, unsigned long))pp12)((unsigned long)pp9, 3, 0);
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
l8f8e8:
    pu10 = (unsigned long *)cL4_alloc(0x28, 0x1050c400dfe80cb);
    *pu10 = (unsigned long)s_TypeDecoder_h__u__Node_kind__u___005d54f0;
    u14 = 0x3b8;
l8ffe4:
    *(unsigned int *)(pu10 + 1) = u14;
    *(unsigned int *)((long)pu10 + 0xc) = u44;
    *(unsigned int *)(pu10 + 2) = u47;
    pu10[3] = (unsigned long)pu48;
    goto fin;
l90d60:
    pu10 = (unsigned long *)cL4_alloc(0x28, 0x1050c400dfe80cb);
    *pu10 = (unsigned long)s_TypeDecoder_h__u__Node_kind__u___005d54f0;
    u13 = DAT_004f28d8;
l91948:
    pu10[1] = u13;
    *(unsigned int *)(pu10 + 2) = u47;
    pu10[3] = (unsigned long)pu48;
    goto fin;
l91b14:
    pu10 = (unsigned long *)cL4_alloc(0x28, 0x1050c400dfe80cb);
    *pu10 = (unsigned long)s_TypeDecoder_h__u__Node_kind__u___005d54f0;
    u13 = DAT_004f28c0;
    goto l925e4;
l91a64:
    pu10 = (unsigned long *)cL4_alloc(0x28, 0x1050c400dfe80cb);
    *pu10 = (unsigned long)s_TypeDecoder_h__u__Node_kind__u___005d54f0;
    u13 = DAT_004f27d0;
    goto l925e4;
l91ab4:
    pu10 = (unsigned long *)cL4_alloc(0x28, 0x1050c400dfe80cb);
    *pu10 = (unsigned long)s_TypeDecoder_h__u__Node_kind__u___005d54f0;
    u13 = DAT_004f2840;
    goto l925e4;
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
l929a4:
    cL4_free(pu10, u13);
    return;
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
                    pc19 = (void (*)(void))stk_f8;
                    if ((short)local_f0 == 1) {
                        node = (unsigned short *)((unsigned long (*)(unsigned long, int, unsigned long))stk_f8)((unsigned long)local_100, 2, 0);
                        b6 = false; b5 = true;
                    } else {
                        pp9 = local_100;
                        if ((short)local_f0 != 0) pp9 = 0;
                        l8 = sk_type_lookup_field_398f40(*ctx, pp9);
                        if (l8 == 0) { b5 = false; pc19 = (void (*)(void))0; }
                        else {
                            l49 = 0; b5 = false; pc19 = (void (*)(void))0;
                            do {
                                l35 = *(long *)(*ctx + 0x58);
                                if (*(long *)(*ctx + 0x50) == l35) goto l94250;
                                *(long *)(l35 + -8) = l49;
                                sk_type_decode_38f0a8(&local_2a0, ctx, u13, i41 + 1, 1);
                                pp9 = stk_298;
                                s = (short)local_290[0];
                                if ((short)local_290[0] == 1) {
                                    node = (unsigned short *)((unsigned long (*)(unsigned long, int, unsigned long))stk_298)((unsigned long)local_2a0, 2, 0);
                                    b5 = true;
                                    pc19 = (void (*)(void))pp9;
                                } else {
                                    pp9 = local_2a0;
                                    if ((short)local_290[0] != 0) pp9 = 0;
                                    cL4_list_push_363f10(&local_210, pp9);
                                }
                                if ((short)local_290[0] == 1) ((void (*)(unsigned long, int, unsigned long))stk_298)((unsigned long)local_2a0, 3, 0);
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
                    if ((short)local_f0 == 1) ((void (*)(unsigned long, int, unsigned long))stk_f8)((unsigned long)local_100, 3, 0);
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
            l8 = ((unsigned long (*)(unsigned long, int, unsigned long))pc19)((unsigned long)node, 2, 0);
            *out = l8;
            ((void (*)(unsigned long, int, unsigned long))pc19)((unsigned long)node, 3, 0);
            goto l92054;
        }
        sk_type_decode_38f0a8(&local_100, ctx, (unsigned long)pu10, i41 + 1, 0);
        pc19 = (void (*)(void))stk_f8;
        s = (short)local_f0;
        if ((short)local_f0 == 1) {
            node = (unsigned short *)((unsigned long (*)(unsigned long, int, unsigned long))stk_f8)((unsigned long)local_100, 2, 0);
        } else {
            pp9 = local_100;
            if ((short)local_f0 != 0) pp9 = 0;
            cL4_list_push_363f10(&local_210, pp9);
            pc19 = (void (*)(void))0;
        }
        if ((short)local_f0 == 1) ((void (*)(unsigned long, int, unsigned long))stk_f8)((unsigned long)local_100, 3, 0);
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
                local_3d8 = (unsigned long *)((unsigned long (*)(unsigned long, int, unsigned long))stk_298)((unsigned long)local_2a0, 2, 0);
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
                            local_3d8 = (unsigned long *)((unsigned long (*)(unsigned long, int, unsigned long))local_328)((unsigned long)local_330, 2, 0);
                            b5 = true;
                        } else {
                            pp12 = local_330;
                            if (local_320[0] != 0) pp12 = 0;
                            cL4_list_push_363f10(&local_100, pp12);
                            sk_type_65184_365184(&local_210, local_360, stk_358);
                        }
                        if (local_320[0] == 1) ((void (*)(unsigned long, int, unsigned long))local_328)((unsigned long)local_330, 3, 0);
                        if (s == 1) goto l91f0c;
                        l49 = l49 + 1;
                    } while (l8 != l49);
                }
                l8 = *ctx;
                if (*(long *)(l8 + 0x50) == *(long *)(l8 + 0x58)) goto l94260;
                *(long *)(l8 + 0x58) = *(long *)(l8 + 0x58) + -0x10;
                b6 = true;
            }
            if ((short)local_290[0] == 1) ((void (*)(unsigned long, int, unsigned long))stk_298)((unsigned long)local_2a0, 3, 0);
            if (b6) goto l91f38;
            if (b5) goto l93610;
        } else {
            sk_type_decode_38f0a8(&local_2a0, ctx, (unsigned long)pu10, i41 + 1, 0);
            pp12 = stk_298;
            s = (short)local_290[0];
            if ((short)local_290[0] == 1) {
                local_3d8 = (unsigned long *)((unsigned long (*)(unsigned long, int, unsigned long))stk_298)((unsigned long)local_2a0, 2, 0);
            } else {
                pp12 = local_2a0;
                if ((short)local_290[0] != 0) pp12 = 0;
                sk_type_pushreq_39951c(&local_3c0, pp12);
            }
            if ((short)local_290[0] == 1) ((void (*)(unsigned long, int, unsigned long))stk_298)((unsigned long)local_2a0, 3, 0);
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
joined_32e0:
    if (s == 1) goto l93930;
    goto fin;
l922b0:
    u43 = *(unsigned short *)(pu10 + 2);
    if (b22 != 3) { u47 = 0; pu48 = (unsigned char *)&DAT_005be7c0; goto l922b0_set; }
    u47 = *(unsigned int *)(pu10 + 1); pu48 = (unsigned char *)*pu10;
l922b0_set:
    pu10 = (unsigned long *)cL4_alloc(0x28, 0x1050c401ab4594e);
    *pu10 = (unsigned long)s_TypeDecoder_h__u__Node_kind__u___005d54b8;
    *(unsigned int *)(pu10 + 1) = 0x3d9;
    *(unsigned int *)((long)pu10 + 0xc) = (unsigned int)u43;
    *(unsigned int *)(pu10 + 2) = u47;
    pc18 = (char *)s_Global_actor_node_is_missing_chi_005d56cd;
    pu10[3] = (unsigned long)pu48;
    pu10[4] = (unsigned long)pc18;
    *(unsigned short *)(out + 2) = 1;
    out[1] = (unsigned long)FUN_00397f0c;
    pu11 = (unsigned long *)cL4_alloc(0x28, 0x1050c401ab4594e);
    u13 = *pu10; u53 = pu10[3]; u28 = pu10[2];
    pu11[1] = pu10[1]; *pu11 = u13; pu11[3] = u53; pu11[2] = u28;
    pu11[4] = pu10[4];
    *out = (unsigned long)pu11;
    goto fin;
l93148:
    u43 = *(unsigned short *)(pu10 + 2);
    if (b22 != 3) { u47 = 0; pu48 = (unsigned char *)&DAT_005be7c0; goto l93148_set; }
    u47 = *(unsigned int *)(pu10 + 1); pu48 = (unsigned char *)*pu10;
l93148_set:
    pu10 = (unsigned long *)cL4_alloc(0x28, 0x1050c401ab4594e);
    *pu10 = (unsigned long)s_TypeDecoder_h__u__Node_kind__u___005d54b8;
    *(unsigned int *)(pu10 + 1) = 0x413;
    *(unsigned int *)((long)pu10 + 0xc) = (unsigned int)u43;
    *(unsigned int *)(pu10 + 2) = u47;
    pc18 = (char *)s_Thrown_error_node_is_missing_chi_005d56f0;
    pu10[3] = (unsigned long)pu48;
    pu10[4] = (unsigned long)pc18;
    *(unsigned short *)(out + 2) = 1;
    out[1] = (unsigned long)FUN_00397f0c;
    pu11 = (unsigned long *)cL4_alloc(0x28, 0x1050c401ab4594e);
    u13 = *pu10; u53 = pu10[3]; u28 = pu10[2];
    pu11[1] = pu10[1]; *pu11 = u13; pu11[3] = u53; pu11[2] = u28;
    pu11[4] = pu10[4];
    *out = (unsigned long)pu11;
    goto fin;
l8f3dc:
    node = (unsigned short *)*node;
    goto l8f3e4;
l8f3e0:
    node = (unsigned short *)(node + 4);
    goto l8f3e4;
l8f298:
    pu26 = *(unsigned short **)node;
    goto l8f298_cont;
l8f298_cont:
    goto follow_child;
l8f6cc:
    stk_208 = (unsigned long **)DAT_004f2710;
    goto l8f6cc_cont;
l8f6cc_cont:
    goto follow_child;
l8fdb8:
    if (u17 <= u37) goto l8fdd8;
    pu26 = (unsigned short *)node;
    if (1 < u36 - 1) pu26 = *(unsigned short **)node;
    pl45 = *(long **)(pu26 + u37 * 4);
    goto l8fdd8;
l8fe84:
    if (*(short *)(*pl32 + 0x10) == 0x76) {
        if (u36 < 2) {
            if (*(char *)(*pl45 + 0x12) != 3) { u47 = 0; pu48 = (unsigned char *)&DAT_005be7c0; goto l93bdc; }
        } else if (*(char *)(*(long *)*pl45 + 0x12) != 3) goto l8ff88;
        goto fin;
    }
    goto l8ff88;
l90104:
    if (b22 == 1) pu16 = (unsigned short *)node + 4;
    else {
        pu16 = (unsigned short *)node + 8;
        if (b22 != 2) {
            if (b22 == 5) { pu16 = *(unsigned short **)node; goto l90120; }
            pu16 = 0;
        }
    }
    goto l90120;
l904bc:
    u13 = *pu10;
    sk_type_decode_38f0a8(&local_100, ctx, pu10[1], i41 + 1, 1);
    pc19 = (void (*)(void))stk_f8;
    if ((short)local_f0 == 1) {
        node = (unsigned short *)((unsigned long (*)(unsigned long, int, unsigned long))stk_f8)((unsigned long)local_100, 2, 0);
        b6 = false; b5 = true;
    } else {
        pp9 = local_100;
        if ((short)local_f0 != 0) pp9 = 0;
        l8 = sk_type_lookup_field_398f40(*ctx, pp9);
        if (l8 == 0) { b5 = false; pc19 = (void (*)(void))0; }
        else {
            l49 = 0; b5 = false; pc19 = (void (*)(void))0;
            do {
                l35 = *(long *)(*ctx + 0x58);
                if (*(long *)(*ctx + 0x50) == l35) goto l94250;
                *(long *)(l35 + -8) = l49;
                sk_type_decode_38f0a8(&local_2a0, ctx, u13, i41 + 1, 1);
                pp9 = stk_298;
                s = (short)local_290[0];
                if ((short)local_290[0] == 1) {
                    node = (unsigned short *)((unsigned long (*)(unsigned long, int, unsigned long))stk_298)((unsigned long)local_2a0, 2, 0);
                    b5 = true; pc19 = (void (*)(void))pp9;
                } else {
                    pp9 = local_2a0;
                    if ((short)local_290[0] != 0) pp9 = 0;
                    cL4_list_push_363f10(&local_210, (unsigned long)pp9);
                }
                if ((short)local_290[0] == 1) ((void (*)(unsigned long, int, unsigned long))stk_298)((unsigned long)local_2a0, 3, 0);
                if (s == 1) { b6 = false; goto l9063c; }
                l49 = l49 + 1;
            } while (l8 != l49);
        }
        l8 = *ctx;
        if (*(long *)(l8 + 0x50) == *(long *)(l8 + 0x58)) goto l94260;
        *(long *)(l8 + 0x58) = *(long *)(l8 + 0x58) + -0x10;
        b6 = true;
    }
    goto l9063c;
l91324:
    sk_type_build_owned_395dec(out, local_210, (unsigned long)stk_208 & 0xffffffff, l8, b5);
    goto l9248c;
l913ac:
    *out = (unsigned long)s_unknown_error_005d5481;
    out[1] = (unsigned long)FUN_0037f9f4;
    *(unsigned short *)(out + 2) = 1;
    goto fin;
l914d0:
    if (b22 == 1) pu25 = (unsigned short *)node + 4;
    else if (b22 == 2) pu25 = (unsigned short *)node + 8;
    else {
        if (b22 == 5) { pu25 = *(unsigned short **)node; goto l914ec; }
        pu25 = 0;
    }
    goto l914ec;
l91810:
    pu48 = pu4;
    pu10 = (unsigned long *)cL4_alloc(0x28, 0x1050c401ab4594e);
    *pu10 = (unsigned long)s_TypeDecoder_h__u__Node_kind__u___005d54b8;
    pu10[1] = DAT_004f2810;
    *(unsigned int *)(pu10 + 2) = u47;
    pc18 = (char *)s_no_children_005d55ed;
    goto l93508;
l91f0c:
    b6 = false;
    goto l91f38;
l92550:
    pp9 = 0;
    *(unsigned short *)(out + 2) = 1;
    out[1] = (unsigned long)stk_208;
    *out = (unsigned long)local_210;
    pc19 = (void (*)(void))FUN_0037f9f8;
    local_210 = 0;
    stk_208 = (unsigned long **)FUN_0037f9f8;
    goto l93930;
l92e54:
    b5 = true;
    sk_type_decode_38f0a8(out, ctx, *(unsigned long *)(node + 4), i41 + 1, 1);
    if ((short)out[2] != 1) {
        if ((short)out[2] == 0) l8 = *out; else l8 = 0;
        goto l91324;
    }
    goto l9248c;
l92f48:
    if (u17 <= u37) goto l92f68;
    pu10 = pu11;
    if (1 < u36 - 1) pu10 = (unsigned long *)*pu11;
    ps20 = (short *)pu10[u37];
    goto l92f68;
l92fa8:
    if (b22 == 1) ps29 = ps20 + 4;
    else if (b22 != 2) {
        if (b22 == 5) { ps29 = *(short **)ps20; goto l92fc4; }
        ps29 = 0;
    }
    goto l92fc4;
l93308:
    if (b22 == 1) pu26 = (unsigned short *)node + 4;
    else if (b22 != 2) {
        if (b22 == 5) { pu26 = *(unsigned short **)node; goto l93324; }
        pu26 = 0;
    }
    goto l93324;
l93428:
    pu10[1] = u13;
    *(unsigned int *)(pu10 + 2) = 0;
    pc18 = (char *)s_expected_text_005d5763;
    pu10[3] = (unsigned long)&DAT_005be7c0;
    pu10[4] = (unsigned long)pc18;
    *(unsigned short *)(out + 2) = 1;
    out[1] = (unsigned long)FUN_00397f0c;
    pu11 = (unsigned long *)cL4_alloc(0x28, 0x1050c401ab4594e);
    u13 = *pu10; u53 = pu10[3]; u28 = pu10[2];
    pu11[1] = pu10[1]; *pu11 = u13; pu11[3] = u53; pu11[2] = u28;
    pu11[4] = pu10[4];
    *out = (unsigned long)pu11;
    goto fin;
l935c0:
    local_3d8 = (unsigned long *)cL4_alloc(0x28, 0x1050c400dfe80cb);
    *local_3d8 = (unsigned long)s_TypeDecoder_h__u__Node_kind__u___005d54f0;
    local_3d8[1] = DAT_004f2858;
    *(unsigned int *)(local_3d8 + 2) = u47;
    local_3d8[3] = (unsigned long)pu48;
    local_3d8[4] = u37;
    goto l93610;
l93710:
    if (b22 == 1) pu25 = (unsigned short *)pu26 + 4;
    else if (b22 != 2) {
        if (b22 == 5) { pu25 = *(unsigned short **)pu26; goto l93f7c; }
        pu25 = 0;
    }
    goto l93f7c;
l93ef4:
    u13 = 0x1050c400dfe80cb;
    pu10 = (unsigned long *)cL4_alloc(0x28, 0x1050c400dfe80cb);
    *pu10 = (unsigned long)s_TypeDecoder_h__u__Node_kind__u___005d5915;
    pu10[1] = DAT_004f2808;
    *(unsigned int *)(pu10 + 2) = u47;
    pu10[3] = (unsigned long)pu48;
    pu10[4] = 0;
    *(unsigned short *)(out + 2) = 1;
    pc19 = (void (*)(void))FUN_00397fc0;
    goto l93524;
l9412c:
    if (u17 <= u37) goto l9414c;
    pu11 = pu10;
    if (1 < u15 - 1) pu11 = (unsigned long *)*pu10;
    u13 = pu11[u37];
    goto l9414c;
l8f5bc:
    l8 = *(long *)(pu26 + 4);
l8f5c0:
    stk_208 = (unsigned long **)DAT_004f2710;
    local_210 = &local_200;
    sk_type_decode_sig_394734(&local_100, ctx, l8, i41 + 1, &local_210);
    if ((char)local_f0 == 1) {
        *(unsigned short *)(out + 2) = 1;
        out[1] = (unsigned long)stk_f8;
        l8 = ((unsigned long (*)(unsigned long, int, unsigned long))stk_f8)((unsigned long)local_100, 2, 0);
        *out = l8;
        ((void (*)(unsigned long, int, unsigned long))stk_f8)((unsigned long)local_100, 3, 0);
        goto fin;
    }
    sk_type_build_owned_395dec(out, &local_210, (unsigned long)stk_208 & 0xffffffff, 0, 0);
    goto fin;
l8f564:
    *(unsigned short *)(out + 2) = 0;
    *out = (unsigned long)pp9;
    if (pp9 == 0) goto l913ac;
    goto fin;
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
    cL4_release(c[0]);
    cL4_release(out);
    if (pkeep != stack) thunk_FUN_00012568(0);
    if (canary != -0x2c8502b44bfffed6) cL4_stack_fail();
    r.hi = (unsigned long)pc;
    r.lo = u;
    return r;
}

/* FUN_0038a1bc @ 0x38a1bc   (est. sk_stringbuf_release)
 * Ghidra: undefined8 * FUN_0038a1bc(undefined8 *param_1)
 * Releases the two ownership objects (0x67c398 / 0x67c370 vtables) of a
 * string-buffer object and clears the child flag. Returns the buffer.
 * Confidence: medium */
unsigned long *sk_stringbuf_release_38a1bc(unsigned long *buf)
{
    *buf = 0x67c398;
    cL4_zone_get((long *)(buf + 0x44));
    *buf = 0x67c370;
    cL4_ipc_obj_publish((long *)buf[3], 0, 0);
    if (buf[5] != 0) *(unsigned char *)(buf[5] + 0x30) = 0;
    return buf;
}

/* FUN_0038b4cc @ 0x38b4cc   (est. sk_tail_call_dispatch)
 * Ghidra: void FUN_0038b4cc(undefined8 *param_1, undefined8, undefined8 *param_3, long)
 * Tail-call dispatcher: invokes the function pointer *param_1 with 0..3
 * arguments extracted from param_3 (or a lone pointer for the 1-arg form).
 * A trampoline used by the decoder's dynamic calls.
 * Confidence: low */
void sk_tail_call_dispatch_38b4cc(unsigned long *fn, unsigned long a, unsigned long *args, long n)
{
    void (*f)(void);
    if (n < 2) {
        if (n == 0) { ((void (*)(unsigned long))*fn)(a); return; }
        if (n == 1) {
            args = (unsigned long *)*args;
            f = (void (*)(void))*fn;
            ((void (*)(unsigned long, unsigned long *))f)(a, args);
            return;
        }
    } else {
        if (n == 2) { ((void (*)(unsigned long, unsigned long, unsigned long))*fn)(a, *args, args[1]); return; }
        if (n == 3) { ((void (*)(unsigned long, unsigned long, unsigned long, unsigned long))*fn)(a, *args, args[1], args[2]); return; }
    }
    f = (void (*)(void))*fn;
    ((void (*)(unsigned long, unsigned long *))f)(a, args);
}

/* FUN_0038b814 @ 0x38b814   (est. sk_vector_push_back)
 * Ghidra: void FUN_0038b814(long *param_1, undefined8 param_2)
 * Appends a 4-word element to the growable vector described by param_1
 * (buffer at *param_1, count at param_1[1], stride 0x20), growing via
 * FUN_00399094 and copying the 4 words.
 * Confidence: medium */
void sk_vector_push_back_38b814(long *vec, unsigned long val)
{
    unsigned long *slot; unsigned long *src; unsigned long w0, w1, w2;

    src = (unsigned long *)sk_vector_grow_399094((unsigned long)vec, val, 1);
    slot = (unsigned long *)(*vec + (unsigned long)*(unsigned int *)(vec + 1) * 0x20);
    w0 = *src; w1 = src[3]; w2 = src[2];
    slot[1] = src[1]; *slot = w0; slot[3] = w1; slot[2] = w2;
    *(int *)(vec + 1) = (int)vec[1] + 1;
}

/* FUN_0038bf8c @ 0x38bf8c   (est. sk_hashtable_unlink)
 * Ghidra: void FUN_0038bf8c(int *param_1)
 * Removes the element referenced by param_1 from a pointer-chained hash
 * bucket (relative-offset links): splices it out of its chain and, when the
 * low bit isn't set, splices its next pointer into the free-list head.
 * Confidence: low */
void sk_hashtable_unlink_38bf8c(int *entry)
{
    long *node; long *next; long *freelist;

    node = (long *)(((long)*entry & 0xfffffffffffffffe) + (long)entry);
    if (((((long)*entry & 1) == 0) || (node = *(long **)node, node != 0)) && (node != 0)) {
        next = (long *)((long)*node + (long)node);
        if (((*(unsigned char *)(entry + 3) & 1) == 0) && (freelist = (long *)next[1], freelist != 0)) {
            next[1] = freelist[1];
            *next = *freelist;
        }
        freelist = (long *)((long)entry[2] + (long)(entry + 2));
        *freelist = *next;
        freelist[1] = next[1];
        next[1] = (long)freelist;
        *next = (long)entry[1] + (long)(entry + 1);
    }
}

/* FUN_0038c32c @ 0x38c32c   (est. sk_stringbuf_release_free)
 * Ghidra: void FUN_0038c32c(undefined8 *param_1)
 * Like FUN_0038a1bc but additionally frees the 0x240-byte buffer block.
 * Confidence: medium */
void sk_stringbuf_release_free_38c32c(unsigned long *buf)
{
    *buf = 0x67c398;
    cL4_zone_get((long *)(buf + 0x44));
    *buf = 0x67c370;
    cL4_ipc_obj_publish((long *)buf[3], 0, 0);
    if (buf[5] != 0) *(unsigned char *)(buf[5] + 0x30) = 0;
    cL4_free(buf, 0x240);
}

/* FUN_0038c3ac @ 0x38c3ac   (est. sk_stringbuf_get_small)
 * Ghidra: undefined1[16] FUN_0038c3ac(char *param_1)
 * Returns the 16-byte descriptor of an inline (small) Swift string: the
 * data pointer from FUN_0038c460, the 2-byte length (param_1+0xe), zero pad.
 * Confidence: medium */
cL4_w16_t sk_stringbuf_get_small_38c3ac(unsigned long sv)
{
    cL4_w16_t r;
    char *s = (char *)sv; char *p = s;
    if (s == 0) p = 0;
    if (*p < 0) {
        if (s == 0) s = 0;
        r.lo = sk_stringbuf_data_38c460(s);
        r.hi = *(unsigned short *)(s + 0xe);
        return r;
    }
    r.lo = 0; r.hi = 0;
    return r;
}

/* FUN_0038c460 @ 0x38c460   (est. sk_stringbuf_data)
 * Ghidra: ulong FUN_0038c460(uint *param_1)
 * Computes the aligned data pointer of an inline Swift string buffer:
 * base + flags-derived offset (param_1[0]>>7 & 1 adds 8) rounded to 4.
 * Confidence: medium */
unsigned long sk_stringbuf_data_38c460(unsigned long sv)
{
    unsigned long n; unsigned int *s = (unsigned int *)sv; unsigned int *p;
    p = s + 3;
    if (p == 0) p = 0;
    if (s == 0) s = 0;
    n = *s;
    return (long)p + sk_stringbuf_len_38c4f4() + ((unsigned long)(n >> 7) & 1) * 8 + 3 & 0xfffffffffffffffc;
}

/* FUN_0038c4f4 @ 0x38c4f4   (est. sk_stringbuf_len)
 * Ghidra: undefined2 FUN_0038c4f4(char *param_1)
 * Returns the length field (param_1+0xc) of an inline Swift string.
 * Confidence: low */
unsigned short sk_stringbuf_len_38c4f4(unsigned long sv)
{
    char *s = (char *)sv; char *p = s;
    if (s == 0) p = 0;
    if (*p < 0) {
        if (s == 0) s = 0;
        return *(unsigned short *)(s + 0xc);
    }
    return 0;
}

/* FUN_0038c584 @ 0x38c584   (est. sk_string_alloc)
 * Ghidra: void FUN_0038c584(long param_1)
 * Allocates a 0x10-byte small-string node holding the owner word from
 * param_1+8, tagged with the 0x67b7d0 vtable.
 * Confidence: low */
void sk_string_alloc_38c584(long a)
{
    unsigned long *n;
    n = (unsigned long *)cL4_alloc(0x10, 0xa1c40bd48d6d6);
    *n = 0x67b7d0;
    n[1] = *(unsigned long *)(a + 8);
}

/* FUN_0038c750 @ 0x38c750   (est. sk_hashtable_chain_find)
 * Ghidra: long FUN_0038c750(uint *param_1)
 * Walks a hash-bucket header to find the chained element whose tag matches,
 * following the (offset) link in the low-2-bit-tagged first word.
 * Confidence: low */
long sk_hashtable_chain_find_38c750(unsigned int *h)
{
    unsigned long w; long r;
    w = *h;
    if ((w & 3) == 1) {
        r = *(long *)(((long)(int)w & 0xfffffffffffffffc) + (long)h);
        if (r != 0) return r;
    } else if (((w & 3) == 0) &&
               (r = ((long)(int)w & 0xfffffffffffffffc) + (long)h, r != 0)) {
        return r;
    }
    return 0;
}

/* FUN_0038c7bc @ 0x38c7bc / 0x38c87c / 0x38c980 / 0x38ca40  (est. sk_string_bucket)
 * Ghidra: void FUN_0038c7bc(long) etc.
 * Family of small-string constructors: allocate a 0x10-byte node tagged with
 * a distinct string-bucket vtable (0x67b818/0x67b860/0x67b8a8/0x67b8f0) and
 * store the owner word from param_1+8.
 * Confidence: medium */
void sk_string_bucket_18_38c7bc(long a) { unsigned long *n; n = (unsigned long *)cL4_alloc(0x10, 0xa1c40bd48d6d6); *n = 0x67b818; n[1] = *(unsigned long *)(a + 8); }
void sk_string_bucket_60_38c87c(long a) { unsigned long *n; n = (unsigned long *)cL4_alloc(0x10, 0xa1c40bd48d6d6); *n = 0x67b860; n[1] = *(unsigned long *)(a + 8); }
void sk_string_bucket_a8_38c980(long a) { unsigned long *n; n = (unsigned long *)cL4_alloc(0x10, 0xa1c40bd48d6d6); *n = 0x67b8a8; n[1] = *(unsigned long *)(a + 8); }
void sk_string_bucket_f0_38ca40(long a) { unsigned long *n; n = (unsigned long *)cL4_alloc(0x10, 0xa1c40bd48d6d6); *n = 0x67b8f0; n[1] = *(unsigned long *)(a + 8); }

/* FUN_0038c920 @ 0x38c920 / 0x38cae4  (est. sk_hashtable_index_lookup)
 * Ghidra: undefined8 FUN_0038c920(long, undefined8, int *param_3)
 * Looks up an element in the hash table whose owner is at param_1+8: hashes
 * the key (FUN_0038ba00) and returns the word at the (base + index*8) slot,
 * or 0 when the bucket array is null.
 * Confidence: low */
unsigned long sk_hashtable_index_lookup_38c920(long a, unsigned long k, int *key)
{
    int i; unsigned long r; long tbl;
    tbl = *(long *)(a + 8);
    if (*(long *)(tbl + 0x10) == 0) return 0;
    i = *key;
    sk_hashtable_hash_38ba00(tbl);
    r = *(unsigned long *)(*(long *)(tbl + 0x10) +
        (unsigned long)(unsigned int)(*(int *)(tbl + 0x128) + i + *(int *)(tbl + 300)) * 8);
    return r;
}
unsigned long sk_hashtable_index_lookup2_38cae4(long a, unsigned long k, int *key)
{
    int i; unsigned long r; long tbl;
    tbl = *(long *)(a + 8);
    if (*(long *)(tbl + 0x10) == 0) return 0;
    i = *key;
    sk_hashtable_hash_38ba00(tbl);
    r = *(unsigned long *)(*(long *)(tbl + 0x10) +
        (unsigned long)(unsigned int)(*(int *)(tbl + 0x128) + i + *(int *)(tbl + 300)) * 8);
    return r;
}

/* FUN_0038cb38 @ 0x38cb38   (est. sk_stringbuf_release_free2)
 * Ghidra: void FUN_0038cb38(undefined8 *param_1)
 * Like FUN_0038c32c but frees a 0xa40-byte buffer block.
 * Confidence: medium */
void sk_stringbuf_release_free2_38cb38(unsigned long *buf)
{
    *buf = 0x67c398;
    cL4_zone_get((long *)(buf + 0x44));
    *buf = 0x67c370;
    cL4_ipc_obj_publish((long *)buf[3], 0, 0);
    if (buf[5] != 0) *(unsigned char *)(buf[5] + 0x30) = 0;
    cL4_free(buf, 0xa40);
}

/* FUN_0038cbb8 @ 0x38cbb8   (est. sk_string_elem_at)
 * Ghidra: void FUN_0038cbb8(long param_1, ulong param_2)
 * Returns the string element at index param_2 by resolving the relative
 * offset table (FUN_0038cc2c) and decoding the element via FUN_003a31d8.
 * Confidence: low */
void sk_string_elem_at_38cbb8(long base, unsigned long idx)
{
    int *slot; int v; long r;
    if (base == 0) base = 0;
    r = sk_string_tbl_base_38cc2c(base);
    slot = (int *)(r + (idx & 0xffffffff) * 4);
    v = *slot;
    r = 0;
    if (v != 0) r = (long)v + (long)slot;
    sk_type_read_3a31d8((unsigned long)r);
}

/* FUN_0038cc2c @ 0x38cc2c   (est. sk_string_tbl_base)
 * Ghidra: long FUN_0038cc2c(undefined8 param_1)
 * Computes the element table base offset: header size + name-count*4 +
 * entry-count*4.
 * Confidence: low */
long sk_string_tbl_base_38cc2c(unsigned long a)
{
    return sk_string_hdr_38cc7c() + sk_string_namecnt_38d330(a) * 4 + sk_string_entcnt_38d3b8(a) * 4;
}

/* FUN_0038cc7c @ 0x38cc7c   (est. sk_string_hdr)
 * Ghidra: long FUN_0038cc7c(undefined8 param_1)
 * Computes the string-table header size: aligned (fixed + name-bytes*2) plus
 * the element-count*0xc array.
 * Confidence: low */
long sk_string_hdr_38cc7c(unsigned long a)
{
    long base; unsigned long nb; unsigned long cnt; unsigned long r[2];
    base = sk_string_fixed_38ccf8();
    nb = sk_string_namebytes_38d204(a);
    { cL4_w16_t _d = sk_string_namedesc_38d294(a); r[0]=_d.lo; r[1]=_d.hi; }
    if (r[1] == 0) cnt = 0;
    else cnt = (unsigned long)*(unsigned short *)(r[0] + r[1] * 2 - 2);
    return (base + (nb & 0xffffffff) * 2 + 3 & 0xfffffffffffffffc) + cnt * 0xc;
}

/* FUN_0038ccf8 @ 0x38ccf8   (est. sk_strhdr_namebytes_off)
 * Ghidra: long FUN_0038ccf8(undefined8)
 * name-bytes offset = fixed-hdr + namebytes*2.
 * Confidence: low */
long sk_string_fixed_38ccf8(unsigned long a)
{
    return sk_string_align_38cd54() + (sk_string_flag_h17c_38d17c(a) & 0xffffffff) * 2;
}

/* FUN_0038cd54 @ 0x38cd54   (est. sk_strhdr_fixed)
 * Ghidra: long FUN_0038cd54(undefined8)
 * fixed header size = base + elem*0xc + namecnt*4 + entcnt*8.
 * Confidence: low */
long sk_string_align_38cd54(unsigned long a)
{
    return sk_string_base_38cdb4() + sk_string_flag_10_38cecc(a) * 0xc +
           sk_string_flag_0e_38cf50(a) * 4 + sk_string_flag_08_38cfd8(a) * 8;
}

/* FUN_0038cdb4 @ 0x38cdb4   (est. sk_strhdr_base)
 * Ghidra: ulong FUN_0038cdb4(uint *param_1)
 * Aligned base pointer of the string header (like FUN_0038c460).
 * Confidence: low */
unsigned long sk_string_base_38cdb4(unsigned long sv)
{
    unsigned long n; unsigned int *s = (unsigned int *)sv; unsigned int *p;
    p = s + 2;
    if (p == 0) p = 0;
    if (s == 0) s = 0;
    n = *s;
    return (long)p + sk_string_len8_38ce48() + ((unsigned long)(n >> 7) & 1) * 8 + 3 & 0xfffffffffffffffc;
}

/* FUN_0038ce48 @ 0x38ce48   (est. sk_strhdr_len8)
 * Length field at param_1+8.
 * Confidence: low */
unsigned short sk_string_len8_38ce48(unsigned long sv)
{
    char *s = (char *)sv; char *p = s; if (s == 0) p = 0;
    if (*p < 0) { if (s == 0) s = 0; return *(unsigned short *)(s + 8); }
    return 0;
}

/* FUN_0038cecc @ 0x38cecc   (est. sk_strhdr_count10)
 * Count field at param_1+10 (element count).
 * Confidence: low */
unsigned short sk_string_flag_10_38cecc(unsigned long sv)
{
    char *s = (char *)sv; char *c = s; char *p = s; if (s == 0) p = 0;
    if (*p < 0) { if (s == 0) s = 0; return *(unsigned short *)(c + 10); }
    return 0;
}

/* FUN_0038cf50 @ 0x38cf50   (est. sk_strhdr_namecnt)
 * Name-count field: bit0 of the 0xe flags word.
 * Confidence: low */
unsigned short sk_string_flag_0e_38cf50(unsigned long sv)
{
    char *s = (char *)sv; char *c = s; char *p = s; if (s == 0) p = 0;
    if (*p < 0) { if (s == 0) s = 0; return *(unsigned short *)(c + 0xe) & 1; }
    return 0;
}

/* FUN_0038cfd8 @ 0x38cfd8   (est. sk_strhdr_entcnt_present)
 * Returns the entry-count when the 0xe bit0 is set (via FUN_0038d07c).
 * Confidence: low */
unsigned short sk_string_flag_08_38cfd8(unsigned long sv)
{
    char *s = (char *)sv; char *c = s; unsigned short r; char *p = s;
    p = s; if (s == 0) p = 0;
    if (*p < 0) {
        if (s == 0) s = 0;
        if ((*(unsigned short *)(c + 0xe) & 1) != 0) {
            r = sk_string_entcnt_38d07c();
            return r;
        }
    }
    return 0;
}

/* FUN_0038d07c @ 0x38d07c   (est. sk_strhdr_entcnt)
 * Reads the entry-count (two packed 16-bit words) from the element array.
 * Confidence: low */
unsigned int sk_string_entcnt_38d07c(unsigned long sv)
{
    unsigned long base; long off; unsigned short *p; unsigned int lo, hi;
    char *s = (char *)sv; char *q = s; if (s == 0) q = 0;
    if (*q < 0) {
        q = s; if (s == 0) q = 0;
        if ((*(unsigned short *)(q + 0xe) & 1) != 0) {
            if (s == 0) s = 0;
            base = sk_string_base_38cdb4((unsigned long)s);
            off = sk_string_flag_10_38cecc((unsigned long)s);
            p = (unsigned short *)(base + off * 0xc);
            lo = (unsigned int)*p;
            hi = (unsigned int)p[1] << 0x10;
            return hi | lo;
        }
    }
    return 0;
}

/* FUN_0038d17c @ 0x38d17c   (est. sk_strhdr_flag17c)
 * Flags field: bit1 of the 0xe word.
 * Confidence: low */
unsigned short sk_string_flag_h17c_38d17c(unsigned long sv)
{
    char *s = (char *)sv; char *c = s; char *p = s; if (s == 0) p = 0;
    if (*p < 0) { if (s == 0) s = 0; return *(unsigned short *)(c + 0xe) >> 1 & 1; }
    return 0;
}

/* FUN_0038d204 @ 0x38d204   (est. sk_strhdr_namebytes)
 * When the 0xe bit1 flag is set, popcounts the packed name-byte lengths to
 * derive the name-bytes count.
 * Confidence: low */
unsigned long sk_string_namebytes_38d204(unsigned long a)
{
    unsigned long f; unsigned short *p; long x; char c;
    x = a; if (a == 0) x = 0;
    f = sk_string_flag_h17c_38d17c(x);
    if ((int)f != 0) {
        if (a == 0) a = 0;
        p = (unsigned short *)sk_string_align_38cd54(a);
        c = (char)((unsigned short)*p >> 8);
        f = (unsigned long)CONCAT11(c, __builtin_popcount((char)*p) + c);
    }
    return f;
}

/* FUN_0038d294 @ 0x38d294   (est. sk_strhdr_namedesc)
 * Returns the {data,count} pair describing the name array.
 * Confidence: low */
cL4_w16_t sk_string_namedesc_38d294(unsigned long a)
{
    int f; unsigned long d; unsigned long n; cL4_w16_t r; long x;
    x = a; if (a == 0) x = 0;
    f = sk_string_flag_h17c_38d17c(x);
    if (f == 0) { d = 0; n = 0; }
    else {
        x = a; if (a == 0) x = 0;
        d = sk_string_fixed_38ccf8(x);
        n = sk_string_namebytes_38d204(a);
        n = n & 0xffffffff;
    }
    r.lo = d; r.hi = n;
    return r;
}

/* FUN_0038d330 @ 0x38d330   (est. sk_strhdr_namecnt2)
 * Name-count: bit2 of the 0xe flags word.
 * Confidence: low */
unsigned short sk_string_namecnt_38d330(unsigned long sv)
{
    char *s = (char *)sv; char *c = s; char *p = s; if (s == 0) p = 0;
    if (*p < 0) { if (s == 0) s = 0; return *(unsigned short *)(c + 0xe) >> 2 & 1; }
    return 0;
}

/* FUN_0038d3b8 @ 0x38d3b8   (est. sk_strhdr_entcnt2)
 * Entry-count: bit2 flag -> FUN_0038d45c.
 * Confidence: low */
unsigned int sk_string_entcnt_38d3b8(unsigned long sv)
{
    char *s = (char *)sv; unsigned int r; char *p = s; if (s == 0) p = 0;
    if (*p < 0) {
        if (s == 0) s = 0;
        if ((*(unsigned short *)(s + 0xe) >> 2 & 1) != 0) {
            r = sk_string_entcnt2_38d45c();
            return r;
        }
    }
    return 0;
}

/* FUN_0038d45c @ 0x38d45c   (est. sk_strhdr_entcnt_raw)
 * Reads the raw entry-count word at the aligned element array.
 * Confidence: low */
unsigned int sk_string_entcnt2_38d45c(unsigned long sv)
{
    unsigned int *p; char *s = (char *)sv; char *q = s; if (s == 0) q = 0;
    if (*q < 0) {
        q = s; if (s == 0) q = 0;
        if ((*(unsigned short *)(q + 0xe) >> 2 & 1) != 0) {
            if (s == 0) s = 0;
            p = (unsigned int *)sk_string_hdr_38cc7c((unsigned long)s);
            return *p;
        }
    }
    return 0;
}

/* FUN_0038d52c @ 0x38d52c / 0x38d5ec  (est. sk_string_bucket2)
 * Small-string constructors tagged 0x67b960 / 0x67b9a8.
 * Confidence: medium */
void sk_string_bucket_60_38d52c(long a) { unsigned long *n; n = (unsigned long *)cL4_alloc(0x10, 0xa1c40bd48d6d6); *n = 0x67b960; n[1] = *(unsigned long *)(a + 8); }
void sk_string_bucket_a8_38d5ec(long a) { unsigned long *n; n = (unsigned long *)cL4_alloc(0x10, 0xa1c40bd48d6d6); *n = 0x67b9a8; n[1] = *(unsigned long *)(a + 8); }

/* FUN_0038d690 @ 0x38d690   (est. sk_hashtable_index_lookup3)
 * Duplicate of FUN_0038c920 (hash-table index lookup).
 * Confidence: low */
unsigned long sk_hashtable_index_lookup3_38d690(long a, unsigned long k, int *key)
{
    int i; unsigned long r; long tbl;
    tbl = *(long *)(a + 8);
    if (*(long *)(tbl + 0x10) == 0) return 0;
    i = *key;
    sk_hashtable_hash_38ba00(tbl);
    r = *(unsigned long *)(*(long *)(tbl + 0x10) +
        (unsigned long)(unsigned int)(*(int *)(tbl + 0x128) + i + *(int *)(tbl + 300)) * 8);
    return r;
}

/* FUN_0038d6e4 @ 0x38d6e4   (est. sk_string_count_delta)
 * Difference between the total name count and the nested/sub-name count.
 * Confidence: low */
long sk_type_dbltbl_hash_38d6e4(unsigned long sv)
{
    char *s = (char *)sv; long p; unsigned long n;
    if (-1 < *s) return 0;
    p = sk_cap_next_3658e8((unsigned long)(s + 4));
    if ((p == 0) || (p = sk_cap_meta_35eb3c((unsigned long)s), p == 0)) n = 0;
    else n = (unsigned long)*(unsigned short *)(p + 4);
    p = sk_cap_meta_35eb3c((unsigned long)s);
    return *(unsigned short *)(p + 4) - n;
}

/* FUN_0038d8dc @ 0x38d8dc   (est. sk_pack_length)
 * Returns the length of an on-stack pack (bit0 tagged) or panics.
 * Confidence: low */
unsigned long sk_pack_length_38d8dc(unsigned long *p)
{
    if ((*p & 1) != 0) return *(unsigned long *)((*p & 0xfffffffffffffffe) - 8);
    cL4_stack_fail();
}

/* FUN_0038d90c @ 0x38d90c   (est. sk_vec_from_range)
 * Builds a growable vector over the element range [param_2, param_3).
 * Confidence: low */
unsigned long *sk_type_dbltbl_grow_38d90c(unsigned long *vec, unsigned long *start, unsigned long *end)
{
    unsigned long *p; unsigned long *q; unsigned long *n;
    *vec = 0; vec[1] = 0; vec[2] = 0;
    if ((long)end - (long)start != 0) {
        sk_vec_reserve_38d974(vec, (long)end - (long)start >> 3);
        p = (unsigned long *)vec[1];
        do {
            q = start + 1; n = p + 1;
            *p = *start;
            p = n; start = q;
        } while (q != end);
        vec[1] = (unsigned long)n;
    }
    return vec;
}

/* FUN_0038d974 @ 0x38d974   (est. sk_vec_reserve)
 * Reserves capacity for a vector (grows via FUN_0038d9b4).
 * Confidence: low */
void sk_vec_reserve_38d974(long *vec, unsigned long n)
{
    unsigned long r[2]; long p;
    if (n >> 0x3d == 0) {
        r[0] = sk_type_realloc_38d9b4(vec + 2);
        p = r[0];
        *vec = p;
        vec[1] = p;
        vec[2] = p + r[1] * 8;
        return;
    }
    cL4_panic_big();
}

/* FUN_0038d9b4 @ 0x38d9b4   (est. sk_vec_alloc)
 * Allocates the element backing array for a vector.
 * Confidence: low */
void sk_vec_alloc_38d9b4(unsigned long a, unsigned long n)
{
    if (n >> 0x3d == 0) {
        cL4_alloc(n << 3, 0xc0c00b8aa526d);
        return;
    }
    cL4_panic_big();
}

/* FUN_0038e114 @ 0x38e114   (est. sk_vec_append_range)
 * Appends the element range [param_2,param_3) to the vector, growing via
 * FUN_003a294c, then bumps the count.
 * Confidence: medium */
void sk_vec_append_range_38e114(long *vec, unsigned long *start, unsigned long *end)
{
    unsigned long n; unsigned long total; unsigned long *dst; unsigned long *src;
    n = (unsigned long)*(unsigned int *)(vec + 1);
    total = n + ((long)end - (long)start >> 3);
    if (*(unsigned int *)((long)vec + 0xc) < total) {
        cL4_wordlist_grow(vec, vec + 2, total, 8);
        n = (unsigned long)*(unsigned int *)(vec + 1);
    }
    if (start != end) {
        dst = (unsigned long *)(*vec + n * 8);
        src = start;
        do { *dst = *src; dst++; src++; } while (src != end);
    }
    *(int *)(vec + 1) = (int)n + (int)((unsigned long)((long)end - (long)start) >> 3);
}

/* FUN_0038e198 @ 0x38e198   (est. sk_vec_resize)
 * Resizes the vector to exactly param_2 elements, zero-filling newly added
 * slots (FUN_00114330).
 * Confidence: low */
void sk_vec_resize_38e198(long *vec, unsigned long n)
{
    unsigned long cur;
    cur = (unsigned long)*(unsigned int *)(vec + 1);
    if (cur <= n) {
        if (n == cur) return;
        if (*(unsigned int *)((long)vec + 0xc) < n) {
            cL4_wordlist_grow(vec, vec + 2, n, 8);
            cur = (unsigned long)*(unsigned int *)(vec + 1);
        }
        if (n - cur != 0) {
            FUN_00114330(*vec + cur * 8, (n - cur) * 8);
        }
    }
    *(int *)(vec + 1) = (int)n;
}

/* FUN_0038d9fc @ 0x38d9fc   (est. sk_generic_err_incorrect_args)
 * Ghidra: undefined8 * FUN_0038d9fc(undefined8 *param_1, int param_2, undefined8)
 * Builds the "incorrect number of generic args" diagnostic string by
 * concatenating the gather-generic-parameters context with the actual count,
 * using the string-buffer helpers (FUN_00112db4/00112e8c). For param_2==2 it
 * copies the descriptor; otherwise frees it. Decompiler removed unreachable
 * blocks (0x38dbfc/0x38dbb4/0x38dbe4/0x38dc2c).
 * Confidence: low */
unsigned long *sk_generic_err_incorrect_38d9fc(unsigned long *p, int n, unsigned long a)
{
    unsigned long *s; unsigned long x[2]; unsigned long sb[2]; unsigned long out;
    unsigned long q[2]; unsigned long r[2]; unsigned long t[2]; unsigned long u;
    unsigned long v[2]; unsigned long w[2]; unsigned long y[2]; unsigned long z;
    unsigned char b[16]; unsigned char b2[16]; unsigned char b3[16]; unsigned long canary;
    if (n < 2) {
        if (n == 0) {
            sk_err_ctx_38dd44(x, p);
            s = (unsigned long *)cL4_strbuf_alloc((unsigned long)x);
            y[0] = *s; z = s[1]; u = s[2]; s[1] = 0; s[2] = 0; *s = 0;
            sk_err_u64_113a3c(&b3, p[4]);
            if (-1 < (char)b3[8]) q[0] = (unsigned long)b3[8]; else { q[0] = (unsigned long)&b3; }
            s = (unsigned long *)cL4_strbuf_print(&y[0], (unsigned long)q);
            r[0] = *s; w[0] = s[1]; t[0] = s[2]; s[1] = 0; s[2] = 0; *s = 0;
            s = (unsigned long *)cL4_strbuf_alloc((unsigned long)&r[0]);
            out = s[0];
            if ((long)u < 0) cL4_free((void *)y[0], u & 0x7fffffffffffffff);
            return (unsigned long *)out;
        }
        thunk_FUN_00012568(a);
    } else {
        if (n == 2) {
            s = (unsigned long *)cL4_alloc(0x38, 0x1060c40d29be02f);
            s[0] = p[0]; s[1] = p[1]; s[2] = p[2]; s[3] = p[3];
            s[4] = p[4]; s[5] = p[5]; s[6] = p[6];
            return s;
        }
        if (p == 0) return 0;
        thunk_FUN_00012568((unsigned long)p, 0x38);
    }
    return 0;
}

/* ------------------------------------------------------------------ *
 * SKR50 tail batch — 57 functions reclaimed from stale tightbeam claim.
 * Additional externs / shims / strings / globals needed by these bodies.
 * ------------------------------------------------------------------ */

/* LSE / breakpoint primitives (Apple EL0 opcodes, not callable functions).
 * LOAcquire/LORelease are lock-object acquire/release (LSE); kept as no-ops
 * with the surrounding global-state manipulation faithfully transcribed.
 * SoftwareBreakpoint is a trap that never returns. */
static inline void LOAcquire(void) { /* LSE lock-object acquire opcode */ }
static inline void LORelease(void) { /* LSE lock-object release opcode */ }
static inline void DataMemoryBarrier(int a, int b) { (void)a; (void)b; }
static inline void *SoftwareBreakpoint(int kind, unsigned long addr)
{ (void)kind; (void)addr; cL4_stack_fail(); }

static inline cL4_w16_t ZEXT816(unsigned long v)
{ cL4_w16_t r; r.lo = v; r.hi = 0; return r; }

/* Hash/vector/metadata helpers referenced by the R50 decoder bodies. */
extern cL4_w16_t FUN_003a31d8(unsigned long);          /* string view (len,ptr) reader */
extern unsigned long FUN_003a32a0(unsigned long, unsigned long, unsigned long, unsigned long *); /* cap build */
extern unsigned long FUN_003a2b38(unsigned long, unsigned long);   /* djb-like hash */
extern void FUN_0035b228(unsigned long *);            /* hash-table lock release */
extern unsigned long FUN_0035b588(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long); /* waiter insert */
extern void FUN_00367ccc(unsigned long *, unsigned long *, unsigned long *); /* vector build from range */
extern long FUN_0035bd48(unsigned long);              /* demangle-tree child resolve */
extern long FUN_0035eae4(unsigned long);              /* demangle-tree data base */
extern long FUN_003658a0(unsigned long);              /* demangle-tree index table */
extern long FUN_00369bb0(unsigned long, unsigned long) __attribute__((noreturn)); /* fatal "expected metadata" panic */
extern unsigned long FUN_00371950(unsigned long, unsigned long, unsigned long *, unsigned long, unsigned long); /* tuple type builder */
extern unsigned long FUN_00370dfc(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long); /* function-type builder */
extern long FUN_003743d0(void);                       /* builtin metatype builder */
extern long FUN_00374838(void);                       /* builtin existential metatype builder */
extern long FUN_00375420(unsigned long);              /* extended-existential base */
extern long FUN_00375934(unsigned long, unsigned long); /* extended-existential build */
extern unsigned long FUN_00374e2c(unsigned long *);    /* indirect/independent type resolve */
extern unsigned long FUN_00374e88(unsigned long, unsigned long, unsigned long, unsigned long *); /* protocol composition build */
extern unsigned long FUN_00377dcc(unsigned long);     /* metadata allocation */
extern void FUN_0037de18(unsigned long *, unsigned long); /* string-of value */
extern unsigned long FUN_00377824(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long *); /* protocol witness materialize */
extern unsigned long FUN_0039c740(unsigned long, unsigned long); /* reqlist/req resolve */
extern long FUN_0036e878(unsigned long);              /* on-stack pack build */
extern void FUN_0036805c(unsigned long *);            /* stringbuf release */
extern void FUN_003680cc(unsigned long *);            /* stringbuf release free */
extern unsigned long FUN_0036805c_2(void);
extern cL4_w16_t FUN_00387868(unsigned long, unsigned long); /* vector grow (16-byte) */
extern cL4_w16_t FUN_003995cc(unsigned long, unsigned long);  /* vector grow (4-byte) */
extern unsigned long FUN_00365184(unsigned long, unsigned long, unsigned long); /* vec push 16 */
extern void FUN_00399550(void);                       /* vec push 16-flag (abort) */
extern unsigned long FUN_00398964(unsigned long);     /* pack length word */
extern unsigned long FUN_0039bdc0(unsigned long, unsigned long); /* type-decl chain lookup */
extern cL4_w16_t FUN_0038cbb8(unsigned long, unsigned long);   /* string elem-at pair */
extern unsigned long FUN_00398474(unsigned long *, unsigned long, unsigned long, unsigned long *); /* type cache lookup */
extern unsigned long FUN_003987e0(unsigned long);     /* type-decl chain hash resolve */
extern unsigned long FUN_0039a6fc(unsigned long *, unsigned long, unsigned long, unsigned long, unsigned short, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long); /* type-list materialize */
extern unsigned long FUN_00398074_2(void);
extern void FUN_003988c4(unsigned long, unsigned long *); /* witness-table attach */
extern unsigned long FUN_00398834(unsigned long, unsigned long, unsigned long); /* type metadata of */
extern unsigned long FUN_00398a70(unsigned long *, unsigned long *, unsigned long, unsigned long *); /* generic-args decode */
extern unsigned long FUN_00399108(unsigned long, unsigned long); /* param kinds decode */
extern unsigned long FUN_0039932c(unsigned long, unsigned long); /* pack kind flag */
extern unsigned long FUN_00399414(unsigned long, unsigned long); /* result kinds decode */
extern void FUN_00399390(unsigned long, unsigned long *, unsigned long *, unsigned long *); /* pack-params write */
extern unsigned long FUN_003995cc_2(void);
extern unsigned long FUN_00399d68(unsigned long, unsigned long *); /* hash node alloc */
extern unsigned long FUN_00399620(unsigned long, unsigned long *, unsigned long *); /* hash lookup */
extern unsigned long FUN_003a2578(unsigned long) __attribute__((noreturn)); /* panic */
extern void FUN_00118148(unsigned long, unsigned long); /* mutex init */
extern void FUN_00118164(unsigned long);               /* mutex lock (fatal on fail) */
extern void FUN_003c3008(unsigned long *, unsigned long, unsigned long, ...); /* type-decl ctx decode */
extern unsigned long FUN_003c312c(unsigned long);       /* metadata pack check */
extern void FUN_003c3264(unsigned long *, unsigned long, unsigned long); /* type-decl ctx resolve */
extern void FUN_004b89f8(void) __attribute__((noreturn)); /* int overflow fatal */
extern unsigned long FUN_00387fbc(unsigned long, unsigned long); /* cap/type compare */
extern unsigned long FUN_00113368(unsigned long *, unsigned long, unsigned long); /* string pack (kind) */
extern unsigned long FUN_001137f8(unsigned long *, unsigned long);   /* string uint (kind) */
extern unsigned long FUN_0011394c(unsigned long *, unsigned long);   /* string ushort (kind) */
extern unsigned long FUN_00113a3c(unsigned long *, unsigned long);   /* string uint (kind 2) */
extern unsigned long FUN_00112c38(unsigned long *, unsigned long, unsigned long); /* string concat */
extern unsigned long FUN_001130a0(unsigned long *, unsigned long);   /* string append word */
extern unsigned long FUN_00116bb4(unsigned long, unsigned long, unsigned long, void *); /* utf8 decode len */
extern unsigned long FUN_00117d14(unsigned long, unsigned long, unsigned long); /* memmove */
extern unsigned long FUN_000101a0(unsigned long, unsigned long);     /* kmem_alloc */
extern unsigned long FUN_00010244(unsigned long, unsigned long, unsigned long); /* aligned alloc */
extern unsigned long FUN_0001279c(unsigned long);      /* size calc */
extern unsigned long *FUN_00112db4(unsigned long, ...); /* stringbuf append error text */
extern unsigned long *FUN_00112e8c(unsigned long, ...); /* stringbuf append word */
extern unsigned long *FUN_00118cf8(unsigned long, ...); /* stringbuf finalize */
extern long cL4_pack_build(unsigned long, ...);         /* FUN_0036e878: on-stack pack build */
extern void FUN_00367d50(unsigned long *, unsigned long); /* stringbuf value */
extern void FUN_0067aff0(void);                         /* builtin metatype vtable @ 0x67aff0 */
extern unsigned long FUN_0011d7e8_2(void);
extern unsigned long FUN_00398a70_2(void);
extern unsigned long FUN_00397f0c_2(void);
extern unsigned long FUN_00397fc0_2(void);

extern void FUN_00387d50(void);
extern void FUN_003d3dd8(unsigned long *, unsigned long *, ...); /* diag log */                         /* type-decl cache init */
extern void FUN_0038c324(void);                         /* lock init sibling @ 0x38c324 */
extern void FUN_00399614(void);                         /* lock init sibling @ 0x399614 */
extern unsigned long thunk_FUN_001144a0(unsigned long, unsigned long, unsigned long);
extern unsigned long thunk_FUN_001145b0(unsigned long, unsigned long, ...);
extern unsigned long FUN_00115080(unsigned long, ...);
extern unsigned long FUN_001144a0(unsigned long, unsigned long, unsigned long);
extern unsigned long FUN_001145b0(unsigned long, unsigned long, ...);
extern cL4_w16_t FUN_0038c640(unsigned long *, unsigned long, unsigned long, long); /* waiter scan */
extern unsigned long FUN_0038c750(unsigned long, ...);  /* hashtable chain find */
extern cL4_w16_t FUN_0038c3ac(unsigned long);           /* stringbuf get small */
extern void FUN_003895e0(unsigned long *, ...);         /* type lookup core */
extern void FUN_0038d9fc(void);                         /* generic err descriptor @ 0x38d9fc */
extern unsigned long FUN_0038a950(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long); /* generic scan */
extern unsigned long FUN_00387fbc(unsigned long, unsigned long); /* cap/type compare */

/* Newly needed string literals. */
extern const char s_failed_to_get_parent_context_s_w_005d533b[];
extern const char s_generic_arguments_005d5362[];
extern const char s_have_005d5375[];
extern const char s_generic_args__expected_005d537b[];
extern const char s_param_005d5393[];
extern const char s_expected_metadata_but_got_a_meta_005d539a[];
extern const char s_expected_a_metadata_pack_but_got_005d53c5[];
extern const char s_has_unexpected_kind_005d5413[];
extern const char s_generic_argument_count_mismatch__005d5429[];
extern const char s___have_005d5454[];
extern const char s_s_generic_arg_count_mismatch_005d52d0[];
extern const char s__gatherGenericParameters__contex_005d52fa[];
extern const char s_parent__005d5327[];
extern const char s_unknown_node_005d5d7d[];
extern const char s_Mangled_type_is_too_complex_005d548f_2[];
extern const char s_Failed_to_unspecialize_type_005d5ab7[];
extern const char s_Failed_to_create_type_decl_005d5ad3[];
extern const char s_is_not_TypeList_005d5aee[];
extern const char s_Tried_to_build_a_bound_generic_t_005d5afe[];
extern const char s_Length_mismatch_building_an_exte_005d5cd1[];
extern const char s_Tried_to_build_an_extended_exist_005d5c83[];
extern const char s_Tried_to_build_a_metatype_from_a_005d5bbb[];
extern const char s_Tried_to_build_an_existential_me_005d5be1[];
extern const char s_Tried_to_build_an_existential_me_005d5c14[];
extern const char s_Tried_to_build_a_protocol_compos_005d5d0b[];
extern const char s_Pack_index__zu_exceeds_pack_leng_005d5d55[];
extern const char s_Expected_a_metadata_pack_but_got_005d42f6[];
extern const char s_Expected_metadata_but_got_a_meta_005d40ee[];
extern const char s_Tried_to_build_a_function_type_w_005d5e1c[];
extern const char s_Tried_to_build_a_function_type_w_005d5e5b[];
extern const char s_Tried_to_build_a_function_type_w_005d5e9b[];
extern const char s_Tried_to_build_a_tuple_type_wher_005d5f9f[];
extern const char s_Can_t_have_nested_metadata_packs_005d5fdb[];
extern const char s_Cannot_have_an_on_stack_pack_her_005d5ffc[];
extern const char s_Lowered_SILPackType_cannot_be_de_005d601f[];
extern const char s_Unbound_dependent_member_type_ca_005d6047[];
extern const char s_Bi16__005d5b51[];
extern const char s_Bi32__005d5b57[];
extern const char s_Bi63__005d5b5d[];
extern const char s_Bi64__005d5b63[];
extern const char s_Bi128__005d5b69[];
extern const char s_Bi256__005d5b70[];
extern const char s_Bi512__005d5b77[];
extern const char s_Bf16__005d5b81[];
extern const char s_Bf32__005d5b87[];
extern const char s_Bf64__005d5b8d[];
extern const char s_Bf80__005d5b93[];
extern const char s_Bf128__005d5b99[];

extern unsigned long FUN_0000456c(unsigned long, ...);       /* generic arg count */
extern unsigned long FUN_00019850(unsigned long);         /* identifier string */
extern const char s__gatherGenericParameters__contex_005d52fa[];
extern const char s_parent__005d5327[];
extern const char s_null_005d5330[];

/* Newly needed binary data / globals. */
extern unsigned long DAT_004f28f8;
extern unsigned char DAT_005d021c[1];
extern unsigned char DAT_005d0c46[1];
extern unsigned char DAT_005d37d4[1];
extern unsigned char DAT_005d531e[1];
extern unsigned char DAT_005d5321[1];
extern unsigned char DAT_005d5324[1];
extern unsigned char DAT_005d5337[1];
extern unsigned char DAT_005d5b42[1];
extern unsigned char DAT_005d5b47[1];
extern unsigned char DAT_005d5b4c[1];
extern unsigned char DAT_005d5b7e[1];
extern unsigned char DAT_005d5ba0[1];
extern unsigned char DAT_005d5ba3[1];
extern unsigned char DAT_005d5ba6[1];
extern unsigned char DAT_005d5ba9[1];
extern unsigned char DAT_005d5bac[1];
extern unsigned char DAT_005d5baf[1];
extern unsigned char DAT_005d5bb2[1];
extern unsigned char DAT_005d5bb5[1];
extern unsigned char DAT_005d5bb8[1];
extern unsigned char DAT_0067afe0[1];
extern unsigned char UINT_0067bd50[1], UINT_0067bd98[1], UINT_0067bcc0[1], UINT_0067bd08[1];
extern volatile unsigned long _DAT_006c0980;
extern volatile unsigned long _DAT_006c0984;
extern volatile unsigned long _DAT_006c0988;
extern volatile unsigned long _DAT_006c0990;
extern volatile unsigned long _DAT_006c09b0;
extern volatile unsigned long _DAT_006c09c0;
extern volatile unsigned long _DAT_006c0a10;
extern volatile unsigned long _DAT_006c0a30;
extern volatile unsigned long _DAT_006c0a40;
extern volatile unsigned long _DAT_006c0a50;
extern volatile unsigned long _DAT_006c0a58;
#define DAT_006c0970 _DAT_006c0970
#define DAT_006c0990 _DAT_006c0990
#define DAT_006c0a10 _DAT_006c0a10
#define DAT_006c0a30 _DAT_006c0a30
#define DAT_006c0a40 _DAT_006c0a40
#define DAT_006c0a50 _DAT_006c0a50
#define DAT_006c0a58 _DAT_006c0a58
#define DAT_006c0980 _DAT_006c0980
#define DAT_006c0984 _DAT_006c0984
#define DAT_006c0988 _DAT_006c0988
#define DAT_006c09b0 _DAT_006c09b0
#define DAT_006c09c0 _DAT_006c09c0

/* ================================================================== *
 * SKR50 tail batch bodies (reclaimed from stale tightbeam claim).
 * ================================================================== */

/* FUN_00388630 @ 0x388630   (est. sk_type_cache_lookup)
 * Ghidra: long FUN_00388630(long *param_1, undefined8 param_2)
 * Looks up (and inserts) a type-decl node in the process-wide type-decl
 * cache. Unwraps a singleton/free-standing indirection (kind 0xf4), returns
 * the cached decl for a 0xf5 "missing" node, else computes the 64-bit hash
 * via sk_type_waiter_scan_38c640 against the open-addressed table at
 * DAT_006c08e8 and returns the stored value on a hit. On a miss it scans the
 * secondary (start,len) chain cache, resolves the decl, grows the table
 * (FUN_00010244 aligned alloc) as needed and inserts {node, value} under the
 * hash. Uses the LSE lock-object protocol over _DAT_006c08e0 and a side
 * mutex (DAT_006c0900, FUN_00118148/00118164) around the insert.
 * Confidence: medium
 * Notes: SoftwareBreakpoint(1,0x388c50) fatal on alloc failure. */
long sk_type_cache_lookup_388630(unsigned long *node, unsigned long ctx)
{
    unsigned long *p; unsigned long *q; unsigned long *tbl;
    unsigned long lv; unsigned long u; long found; int i; long canary2;
    unsigned long n0; cL4_w16_t vb; unsigned long *deferred; unsigned long cap;

    p = node;
    if ((short)node[2] == 0xf4) {
        if (1 < *(unsigned char *)((long)node + 0x12) - 1) {
            if ((*(unsigned char *)((long)node + 0x12) != 5) || ((int)node[1] == 0)) {
                p = 0; goto lk_a0;
            }
            p = (unsigned long *)*node;
        }
        p = (unsigned long *)*p;
    }
lk_a0:
    if ((short)p[2] == 0xf5) { lv = *p; return lv; }
    if (-1 < (long)_DAT_006c0970)
        FUN_003d3dd8(&_DAT_006c0970, (unsigned long *)FUN_00387d50, 0);
    if ((short)p[2] == 0x27) return 0;

    {
        unsigned long namew = ctx;
        FUN_003c3008(&i, (unsigned long)node, (unsigned long)&DAT_0036e518, (unsigned long)&namew, ctx, 0);
        if (i != 0) return 0;
    }
    /* first-tier lookup */
    LOAcquire();
    _DAT_006c08e0 = _DAT_006c08e0 + 1;
    if ((_DAT_006c08e8 != 0 && _DAT_006c08f0 != 0) && _DAT_006c08e4 != 0) {
        vb = FUN_0038c640(&ctx, _DAT_006c08f0, _DAT_006c08e4, (long)_DAT_006c08e8 + 2);
        if (vb.lo != 0) {
            LORelease();
            _DAT_006c08e0 = _DAT_006c08e0 - 1;
            return *(long *)(vb.lo + 0x10);
        }
    }
    _DAT_006c08e0 = _DAT_006c08e0 - 1;
    LORelease();

    /* second-tier (start,len) chain scan */
    LOAcquire();
    _DAT_006c0938 = _DAT_006c0938 + 1;
    if ((_DAT_006c0940 != 0) && (*_DAT_006c0940 != 0)) {
        q = (unsigned long *)(_DAT_006c0940 + 1);
        tbl = q + *_DAT_006c0940 * 2;
        do {
            lv = q[1];
            for (found = (long)*q; found != (long)lv; found += 4) {
                u = FUN_0038c750(found);
                if (u != 0 && (FUN_00387fbc(u, (unsigned long)node) & 1)) {
                    _DAT_006c0938 = _DAT_006c0938 - 1;
                    LORelease();
                    goto found_88884;
                }
            }
            q += 2;
        } while (q != tbl);
    }
    lv = _DAT_006c0938;
    _DAT_006c0938 = _DAT_006c0938 - 1;
    LORelease();
    found = FUN_0039bdc0(lv, (unsigned long)node);
    if (found == 0) return 0;

found_88884:
    /* insert {node, value} under hash into the open-addressed table */
    {
        unsigned long count = _DAT_006c08e4;
        unsigned long cap2 = _DAT_006c08f0;
        unsigned long eltsz;
        unsigned char *base = (unsigned char *)(cap2 & 0xfffffffffffffffc);
        unsigned long *pt = (unsigned long *)_DAT_006c08e8;
        unsigned long *slots;
        unsigned long newmask;
        unsigned long acc;
        n0 = ctx;
        eltsz = ((base != 0) && ((cap2 & 3) != 0)) ? (unsigned long)*base : 4;
        slots = (pt != 0) ? pt + 2 : 0;
        vb = FUN_0038c640(&n0, cap2, count, (long)slots);
        if (vb.lo == 0) {
            unsigned long mask2 = 1UL << (eltsz & 0x3f);
            unsigned long n2 = count + 1;
            unsigned long rem = mask2 - n2;
            unsigned long ratio = (rem != 0) ? (mask2 / rem) : 0;
            unsigned long newtbl;
            if (3 < ratio) {
                /* grow the table capacity */
                unsigned char *nbuf;
                unsigned long ne = eltsz + 1;
                unsigned long nb = ne & 0xff;
                int bsz = (0x10 < nb) ? 4 : ((nb < 9) ? 1 : 2);
                acc = (unsigned long)bsz;
                nbuf = (unsigned char *)FUN_00010244(2UL << (eltsz & 0x3f), acc, 0x48dda4ae);
                if (nbuf == 0) { LOAcquire(); cL4_stack_fail(); }
                if (bsz != 1) acc = (bsz == 4) ? 3 : 2;
                acc |= (unsigned long)nbuf;
                *nbuf = (unsigned char)ne;
                _DAT_006c08f0 = acc;
                if (base != 0) {
                    deferred = (unsigned long *)FUN_000101a0(0x10, 0xa0040aff93c70);
                    *deferred = _DAT_006c0920; deferred[1] = (unsigned long)base;
                    _DAT_006c0920 = (unsigned long)deferred;
                }
                newmask = acc;
                vb = FUN_0038c640(&n0, acc, count, (long)slots);
                cap2 = acc;
            } else {
                newmask = cap2;
            }
            /* grow the slot array if needed */
            if ((pt == 0) || (*(unsigned int *)pt <= count)) {
                unsigned long sz = (unsigned long)(count >> 2);
                if (sz < 2) sz = 1;
                sz = FUN_0001279c((sz + count) * 0x18 + 8);
                newtbl = (unsigned long)FUN_000101a0(sz, 0x1070040d224386b);
                if (newtbl == 0) cL4_stack_fail();
                *(unsigned int *)newtbl = (unsigned int)((sz - 8) / 0x18);
                if (pt != 0) {
                    long csz = (7 < sz) ? (sz - 8) : 0;
                    cL4_obj_copy2((unsigned long *)(newtbl + 2), (unsigned long)(pt + 2),
                                  (unsigned long)count * 0x18);
                    deferred = (unsigned long *)FUN_000101a0(0x10, 0xa0040aff93c70);
                    *deferred = _DAT_006c0920; deferred[1] = (unsigned long)pt;
                    _DAT_006c0920 = (unsigned long)deferred;
                }
                pt = (unsigned long *)newtbl;
                _DAT_006c08e8 = newtbl;
            }
            *(long *)(pt + count * 6 + 6) = found;
            {
                unsigned long copy = FUN_000101a0(ctx, 0x100004077774924);
                cL4_obj_copy_simple(copy, ctx, ctx);
                *(unsigned long *)(pt + count * 6 + 2) = copy;
                *(unsigned long *)(pt + count * 6 + 4) = ctx;
            }
            _DAT_006c08e4 = n2;
            FUN_0035b588((unsigned long)&newmask, (unsigned long)&DAT_006c08f0, n2, vb.hi & 0xffffffff, 3);
        }
    }
    DataMemoryBarrier(2, 3);
    deferred = (unsigned long *)_DAT_006c0920;
    if (_DAT_006c08e0 == 0) {
        while (deferred != 0) {
            unsigned long *nx = (unsigned long *)*deferred;
            thunk_FUN_00012568(deferred[1]);
            thunk_FUN_00012568((unsigned long)deferred);
            deferred = nx;
        }
        _DAT_006c0920 = 0;
    }
    FUN_0035b228(&n0);
    return found;
}

/* FUN_00388c60 @ 0x388c60   (est. sk_type_decl_alloc)
 * Ghidra: void FUN_00388c60(uint *param_1, undefined8 param_2, long *param_3)
 * Builds a type-decl node for the mangled name param_2. Validates the source
 * node header ((*param_1 & 0x1f) == 1), extracts the string-buffer children
 * (FUN_003a31d8) and, if one is a 'x' single-char marker matching the current
 * name, reuses the resolved decl. Otherwise allocates a decl (FUN_003a32a0),
 * unwraps a singleton/5-list indirection, validates metadata via
 * FUN_003c312c/003c3264 and finally stores the decl via
 * sk_type_cache_lookup_388630.
 * Confidence: medium
 * Notes: node kind 0xf4 indirection; canary -0x2c8502b44bfffed6. */
void sk_type_decl_alloc_388c60(unsigned int *node, unsigned long ctx, long *out)
{
    unsigned long u2, lv; unsigned long *pl; long r;
    unsigned long *p6; unsigned long w; unsigned long canary;
    cL4_w16_t vb, vq, vb2; long lc; int *pi; long base; long l9;

    canary = -0x2c8502b44bfffed6;
    if (node == 0 || (*node & 0x1f) != 1) goto ret_88ec0;
    if (node != 0) {
        w = node[2];
        l9 = 0;
        if (w != 0) l9 = (long)(node + 2) + (long)(int)w;
        vb = FUN_003a31d8(l9);
        vq = FUN_0038c3ac((unsigned long)node);
        if (vq.hi != 0) {
            lv = vq.hi * 0xc;
            pi = (int *)(vq.lo + 8);
            base = vq.lo + 4;
            do {
                if ((pi[-2] & 0x1f) == 1) {
                    vq = FUN_003a31d8(base + pi[-1]);
                    if ((vq.hi == 1 && *(char *)vq.lo == 'x')) {
                        vb2 = FUN_003a31d8(base + *pi + 4);
                        if (vb2.lo == vb.lo) goto ret_88e9c;
                    }
                }
                pi += 3; base += 0xc; lv -= 0xc;
            } while (lv != 0);
        }
        {
            unsigned long ctxw = ctx;
            pl = (unsigned long *)FUN_003a32a0((unsigned long)&ctxw, vb.lo, vb.hi, &ctx);
            if (out == 0) {
                cL4_zone_get(&ctx);
                p6 = pl;
            } else {
                *out = (long)pl;
                cL4_zone_get(&ctx);
                pl = 0;
                p6 = (unsigned long *)*out;
            }
        }
        if (p6 != 0) {
            if (*(short *)(p6 + 2) == 0xf4) {
                pl = p6;
                if (out != 0) pl = (unsigned long *)*out;
                if ((1 < *(unsigned char *)((long)pl + 0x12) - 1) &&
                    (*(unsigned char *)((long)pl + 0x12) != 5 || ((int)pl[1] == 0))) goto ret_88e9c;
                if (out != 0) pl = (unsigned long *)*out;
                if (*(unsigned char *)((long)pl + 0x12) - 1 < 2) {
                ind_88e40:
                    pl = (unsigned long *)*pl;
                } else {
                    if (*(unsigned char *)((long)pl + 0x12) == 5 && (int)pl[1] != 0) {
                        pl = (unsigned long *)*pl; goto ind_88e40;
                    }
                    pl = 0;
                }
                if (out != 0) { *out = (long)pl; goto chk_88e64; }
                goto chk_88e78;
            } else {
                if (out == 0) goto chk_88e78;
                pl = (unsigned long *)*out;
chk_88e64:
                u2 = FUN_003c312c((unsigned long)pl);
                if ((u2 & 1) != 0) {
                    pl = (unsigned long *)*out;
chk_88e84:
                    FUN_003c3264(&r, (unsigned long)pl, ctx);
                    if (r != 0) goto ret_88e9c;
                    pl = (unsigned long *)r;
                    if (out == 0) goto ret_88eb4;
                    *out = r;
                }
                pl = (unsigned long *)*out;
            }
chk_88e78:
            u2 = FUN_003c312c((unsigned long)pl);
            if ((u2 & 1) != 0) goto chk_88e84;
            pl = (unsigned long *)*out;
        }
ret_88eb4:
        u2 = (unsigned long)sk_type_cache_lookup_388630(pl, ctx);
        goto ret_88ec0;
    }
ret_88e9c:
    u2 = 0;
ret_88ec0:
    if (canary != -0x2c8502b44bfffed6) cL4_stack_fail();
}

/* FUN_00388fb0 @ 0x388fb0   (est. sk_type_cache_add_range)
 * Ghidra: void FUN_00388fb0(undefined8 param_1, ulong param_2, long param_3)
 * Appends the byte range [param_2, param_2+param_3) to the process-wide
 * type-name range cache (_DAT_006c09e0 / _DAT_006c09d0), growing the array
 * (FUN_000101a0) when full, under the lock-object at _DAT_006c09f0
 * (cL4_ref_acquire/cL4_release). Each entry stores {start, end} pairs plus a
 * count at offset 0.
 * Confidence: medium
 * Notes: SoftwareBreakpoint fatal on alloc failure; deferred free-list drain
 *   via _DAT_006c0a00. */
void sk_type_cache_add_range_388fb0(unsigned long ctx, unsigned long start, long len)
{
    unsigned long *dst; unsigned long *arr; unsigned long n, cap;
    unsigned long *src; unsigned long i; unsigned long *deferred; unsigned long *p;

    cL4_ref_acquire(0x6c09f0);
    arr = (unsigned long *)_DAT_006c09e0;
    n = (arr != 0) ? *arr : 0;
    cap = _DAT_006c09d0;
    if (_DAT_006c09d0 <= n) {
        cap = n * 2;
        if (cap < 0x11) cap = 0x10;
        dst = (unsigned long *)FUN_000101a0((cap >> 1) << 5 | 8, 0x1000040504ffac1);
        if (dst == 0) cL4_stack_fail();
        *dst = 0;
        if (arr != 0) {
            if (n != 0) {
                src = arr + 1; dst = dst + 1;
                for (i = n; i != 0; i--) {
                    dst[1] = src[1]; *dst = *src;
                    dst += 2; src += 2;
                }
            }
            *dst = n;
            deferred = (unsigned long *)FUN_000101a0(0x10, 0xa0040aff93c70);
            *deferred = _DAT_006c0a00; deferred[1] = (unsigned long)arr;
            _DAT_006c0a00 = (unsigned long)deferred;
        }
    }
    _DAT_006c09e0 = dst;
    _DAT_006c09d0 = cap;
    p = (unsigned long *)_DAT_006c09e0;
    _DAT_006c09e0[n * 2 + 1] = start;
    p[n * 2 + 2] = start + (unsigned long)len;
    *p = n + 1;
    DataMemoryBarrier(2, 3);
    deferred = (unsigned long *)_DAT_006c0a00;
    if (_DAT_006c09d8 == 0) {
        while (deferred != 0) {
            unsigned long *nx = (unsigned long *)*deferred;
            thunk_FUN_00012568(*(unsigned long *)deferred[1]);
            thunk_FUN_00012568((unsigned long)deferred);
            deferred = nx;
        }
        _DAT_006c0a00 = 0;
    }
    cL4_release(0x6c09f0);
}

/* FUN_00389180 @ 0x389180   (est. sk_type_mangled_push)
 * Ghidra: undefined8 FUN_00389180(char *param_1, undefined8 param_2, long param_3)
 * Recursive mangled-name scanner: resolves the type-decl node (via
 * sk_type_decl_alloc_388c60), and when the name carries a mangled-length
 * marker (< 0) recurses on the suffix; on encountering a new unique prefix it
 * appends the name to the shared word-list via sk_wordlist_append_389370 and
 * reports 1 (newly added), else 0.
 * Confidence: medium
 * Notes: node kind 0xf4 unwrap; canary -0x2c8502b44bfffed6. */
unsigned long sk_type_mangled_push_389180(char *name, unsigned long ctx, long mode)
{
    char *pc; unsigned long u2; long l3; unsigned short u4;
    unsigned long canary;

    canary = -0x2c8502b44bfffed6;
    {
        long frame[64] = {0};
        frame[0] = 0x67b7a8;
        *(char *)(mode + 0x30) = 1;
        frame[2] = *(unsigned long *)(mode + 0x10);
        frame[1] = *(unsigned long *)(mode + 8);
        sk_type_decl_alloc_388c60((unsigned int *)name, (unsigned long)&frame[0], 0);
    }
    if (*name < 0) {
        u2 = sk_cap_next_3658e8((unsigned long)(name + 4));
        sk_type_mangled_push_389180((char *)u2, ctx, (long)&canary);
        l3 = sk_cap_meta_35eb3c(u2);
        u4 = (l3 == 0) ? 0 : *(unsigned short *)(l3 + 4);
        l3 = sk_cap_meta_35eb3c((unsigned long)name);
        if ((l3 != 0) && (u4 < *(unsigned short *)(l3 + 4))) {
            sk_wordlist_append_389370((long *)ctx, (unsigned int)u2);
            return 1;
        }
    }
    return 0;
}

/* FUN_003893d0 @ 0x3893d0   (est. sk_type_lookup_wrap)
 * Ghidra: undefined8 FUN_003893d0(undefined8 param_1, undefined8 param_2, undefined8 param_3, undefined8 param_4)
 * Public TypeDecoder entry: wraps sk_type_lookup_core_3895e0 with an
 * error-reporting context and, on failure, prints "failed type lookup for
 * %s" via cL4_log_printf and destroys the lookup result.
 * Confidence: medium
 * Notes: __thread_bss.cpusubtype guard for the print. */
unsigned long sk_type_lookup_wrap_3893d0(unsigned long a, unsigned long b, unsigned long c, unsigned long d)
{
    unsigned long v; unsigned long ctx[2]; long canary;

    canary = -0x2c8502b44bfffed6;
    ctx[0] = 1;
    ctx[1] = (unsigned long)&ctx[0];
    FUN_003895e0(&v, 0, a, b, d, (unsigned long)&ctx[0], (unsigned long)&ctx[0]);
    FUN_0036805c(&ctx[0]);
    FUN_003680cc(&ctx[0]);
    return (ctx[0] == 1) ? 0 : v;
}

/* FUN_0038a950 @ 0x38a950   (est. sk_type_generic_scan)
 * Ghidra: undefined8 FUN_0038a950(long param_1, long param_2, undefined8 param_3, long *param_4, undefined8 param_5)
 * Scans a generic-type demangle tree: for each generic argument whose UTF-8
 * continuation flags indicate a sub-word, appends the argument to the word
 * list param_4 (cL4_list_push_363f10) and, when the argument is itself a
 * bound-generic/metatype requiring deep resolution, materializes it via
 * sk_type_demangle_resolve_389e8c and stores the resolved metadata into the
 * list. Returns 1 on success.
 * Confidence: low
 * Notes: complex kind-flag walk; canary -0x2c8502b44bfffed6. */
unsigned long sk_type_generic_scan_38a950(long base, long tree, unsigned long args, long *list, unsigned long mode)
{
    char *pc1; unsigned short u4; long l5; unsigned long u12; long canary;
    char *pc14; unsigned long u8;

    canary = -0x2c8502b44bfffed6;
    if (base == 0) return 0;
    l5 = sk_cap_meta_35eb3c(base);
    if ((l5 != 0) && (u4 = *(unsigned short *)(l5 + 4), (unsigned long)u4 != 0)) {
        u12 = 0;
        pc1 = (char *)(l5 + 0xc);
        pc14 = pc1;
        do {
            cL4_list_push_363f10(list, *(unsigned long *)(tree + u12 * 8));
            u12 = (unsigned long)((int)u12 + 1);
            pc14 = pc14 + 1;
        } while (pc14 != pc1 + u4);
        u8 = 1;
        if (canary != -0x2c8502b44bfffed6) cL4_stack_fail();
        return u8;
    }
    return 1;
}

/* FUN_0038ad64 @ 0x38ad64   (est. sk_type_build_generic)
 * Ghidra: void FUN_0038ad64(undefined8 *param_1, undefined8 param_2, long param_3, ulong param_4, long param_5, long *param_6, long *param_7, undefined8 param_8)
 * Builds a generic (bound) type node: validates the generic argument list,
 * computes the expected argument count via sk_type_dbltbl_hash_38d6e4, and
 * either records the decl directly or materializes each bound argument via
 * sk_type_generic_scan_38a950 into the type list. Writes an error descriptor
 * on any inconsistency (sk_type_err_*_38e2xx family).
 * Confidence: low
 * Notes: FUN_0038e214/0038e458/0038e624/0038e7f0 are the specific error
 *   descriptors chosen by kind flag; canary -0x2c8502b44bfffed6. */
void sk_type_build_generic_38ad64(unsigned long *out, unsigned long tree, long args, unsigned long nargs,
                                  long flags, long *gv, long *types, unsigned long ctx)
{
    unsigned long u4; long l5; unsigned long canary;
    unsigned long pu[8]; long *res;

    canary = -0x2c8502b44bfffed6;
    sk_type_mangled_push_389180((char *)tree, (unsigned long)gv, ctx);
    if (*(unsigned int *)(gv + 1) == 0) {
        l5 = sk_cap_meta_35eb3c(tree);
        u4 = (l5 == 0) ? 0 : (unsigned int)*(unsigned short *)(l5 + 4);
    } else {
        u4 = *(unsigned int *)(*gv + (unsigned long)*(unsigned int *)(gv + 1) * 4 + -4);
    }
    if ((nargs != sk_type_dbltbl_hash_38d6e4(tree)) &&
        ((flags != 0 || (nargs != u4)))) {
        /* argument-count mismatch: record an error descriptor */
        pu[0] = tree; pu[1] = (unsigned long)args; pu[2] = nargs;
        pu[3] = (unsigned long)flags; pu[4] = nargs; pu[5] = tree;
        *(unsigned int *)(pu + 6) = u4;
        *out = (unsigned long)pu;
        out[1] = (unsigned long)sk_type_err_generic_count_38e214;
        *(unsigned char *)(out + 2) = 1;
        goto done_8b490;
    }
    if ((int)gv[1] == 0) {
        *(unsigned char *)out = 0;
        *(unsigned char *)(out + 2) = 0;
        goto done_8b490;
    }
    /* materialize bound args into the types list */
    {
        long lv = args + nargs * 8;
        unsigned short u3 = *(unsigned short *)(l5 + 4);
        unsigned long *dst = (unsigned long *)types;
        if (u3 != u4) {
            pu[0] = tree; pu[1] = (unsigned long)args; pu[2] = nargs;
            pu[3] = (unsigned long)flags; pu[4] = (unsigned long)*(unsigned int *)(types + 1);
            *(unsigned int *)(pu + 5) = (unsigned int)u3;
            *out = (unsigned long)pu;
            out[1] = (unsigned long)sk_type_err_generic_args_38dfc8;
            *(unsigned char *)(out + 2) = 1;
            goto done_8b490;
        }
        sk_type_generic_scan_38a950(l5, (long)args, 0, (long *)dst, ctx);
        *(unsigned char *)out = 0;
        *(unsigned char *)(out + 2) = 0;
    }
done_8b490:
    if (canary != -0x2c8502b44bfffed6) cL4_stack_fail();
}

/* FUN_0038b578 @ 0x38b578   (est. sk_type_mangled_count)
 * Ghidra: ulong FUN_0038b578(long param_1, char *param_2, long param_3)
 * Recursive mangled-name counter: resolves the type-decl for the name
 * (sk_type_decl_alloc_388c60), recurses on the suffix, and when the name
 * carries the mangled-length marker (< 0) appends the UTF-8 high-bit count of
 * the suffix region into the string buffer at param_1+0x18. Returns the total
 * high-bit count. Used by sk_hashtable_hash_38ba00 to seed the hash.
 * Confidence: medium
 * Notes: canary -0x2c8502b44bfffed6. */
unsigned long sk_type_mangled_count_38b578(long base, char *name, long mode)
{
    unsigned int u1; char *pc2; unsigned long u3; long l5, l6; unsigned int u7;
    unsigned long u8; char *pc9; unsigned long u10; int i11; unsigned char b12;
    long canary; long lc0[8];

    canary = -0x2c8502b44bfffed6;
    if (name == 0) return 0;
    {
        long frame[64] = {0};
        frame[0] = 0x67b7a8;
        *(char *)(mode + 0x30) = 1;
        frame[2] = *(unsigned long *)(mode + 0x10);
        frame[1] = *(unsigned long *)(mode + 8);
        sk_type_decl_alloc_388c60((unsigned int *)name, (unsigned long)&frame[0], 0);
    }
    u3 = sk_cap_next_3658e8((unsigned long)(name + 4));
    u3 = sk_type_mangled_count_38b578(base, (char *)u3, (long)&lc0[0]);
    if (*name < 0) {
        l5 = sk_cap_meta_35eb3c(*(unsigned long *)(base + 8));
        l6 = sk_cap_meta_35eb3c(u3);
        u10 = (l6 == 0) ? 0 : (unsigned long)*(unsigned short *)(l6 + 4);
        l6 = sk_cap_meta_35eb3c((unsigned long)name);
        u7 = (l6 == 0) ? 0 : (unsigned int)*(unsigned short *)(l6 + 4);
        pc9 = (char *)(l5 + 0xc + u10);
        u1 = u7 - (unsigned int)u10;
        i11 = 0; b12 = 0;
        if (u1 != 0) {
            u8 = (unsigned long)u1; pc2 = pc9;
            do {
                i11 = i11 + (((int)*pc2 & 0x80U) >> 7);
                b12 = (unsigned int)(int)*pc2 < 0x80000000 | b12;
                u8--; pc2++;
            } while (u8 != 0);
        }
        if ((unsigned int)u10 < u7) {
            {
                long v[8]; unsigned long len = u1; unsigned int n = (unsigned int)u1;
                long nn = (long)sk_cap_meta_35eb3c((unsigned long)name);
                v[0] = (long)pc9; v[1] = (unsigned long)u1;
                v[4] = (nn == 0) ? 0 : (unsigned int)*(unsigned short *)(nn + 4);
                v[5] = (long)u3; v[6] = i11; v[7] = b12;
                sk_vector_push_back_38b814((long *)(base + 0x18), (unsigned long)&v[0]);
            }
        }
        u3 = (unsigned long)(unsigned int)(i11 + (int)u3);
    }
    if (canary != -0x2c8502b44bfffed6) cL4_stack_fail();
    return u3;
}

/* FUN_0038b85c @ 0x38b85c   (est. sk_type_utf8_hi)
 * Ghidra: int FUN_0038b85c(long param_1, uint *param_2)
 * Counts the UTF-8 continuation / high-bit bytes in a string buffer param_2
 * (a length-prefixed list of (len, flags) string views) and accumulates the
 * count, appending each view to the buffer at param_1+0x18.
 * Confidence: medium */
int sk_type_utf8_hi_38b85c(long base, unsigned int *buf)
{
    unsigned int *p6; long l2; unsigned int u3; unsigned long u4;
    unsigned int *p5; int i7; unsigned int u8; long v[8]; int count;

    p6 = buf + 1;
    l2 = ((unsigned long)*buf & 0xfff) * 2;
    if ((int)l2 == 0) return 0;
    p5 = (unsigned int *)((long)p6 + l2);
    u3 = 0; i7 = 0;
    do {
        u8 = (unsigned int)(unsigned short)*p6;
        if (u8 - u3 == 0) {
            v[3] = 0; v[4] = 0;
        } else {
            unsigned long rem = u8 - u3; unsigned int *q = p5; int hi = 0; int bad = 0;
            do {
                hi += (((int)(char)*q & 0x80U) >> 7);
                bad = (unsigned int)(int)*q < 0x80000000 | bad;
                rem--; q = (unsigned int *)((long)q + 1);
            } while (rem != 0);
            v[3] = 0; v[4] = 0;
        }
        {
            long nn = (long)sk_cap_meta_35eb3c(0);
            v[0] = (long)p5; v[1] = u8 - u3;
            v[2] = u8;
            v[6] = i7 + (int)v[3];
            sk_vector_push_back_38b814((long *)(base + 0x18), (unsigned long)&v[0]);
        }
        p6 = (unsigned int *)((long)p6 + 2);
        u3 = u8;
        i7 = i7 + (int)v[3];
    } while (p6 != p5);
    return i7;
}

/* FUN_0038b948 @ 0x38b948   (est. sk_type_len8_add)
 * Ghidra: int FUN_0038b948(long param_1, undefined8 param_2)
 * Sums the lengths of a two-part string buffer (param_2) and appends the
 * combined view to the buffer at param_1+0x18. Returns the total length.
 * Confidence: medium */
int sk_type_len8_add_38b948(long base, unsigned long sv)
{
    int i1; unsigned short u2; long v[8]; long lc;

    FUN_0037de18((unsigned long *)&v[0], sv);
    u2 = (unsigned short)v[0];
    if ((unsigned long)(unsigned short)v[0] == 0) {
        v[2] = 0;
    } else {
        v[6] = v[1];
        v[2] = (unsigned int)(unsigned short)v[0];
        v[3] = 0; v[4] = 0;
        v[7] = (unsigned long)(unsigned short)v[0];
        v[5] = v[2];
        sk_vector_push_back_38b814((long *)(base + 0x18), (unsigned long)&v[0]);
        v[2] = (unsigned int)(unsigned short)v[0];
    }
    FUN_00367d50(&v[0], sv);
    v[7] = v[7] + (unsigned short)v[0];
    {
        long n2 = (v[0] & 0xffff) - (unsigned long)(unsigned short)v[0];
        i1 = (int)n2 + (unsigned int)u2;
        v[4] = 0;
        v[6] = i1;
        sk_vector_push_back_38b814((long *)(base + 0x18), (unsigned long)&v[0]);
        return i1;
    }
}

/* FUN_0038ba00 @ 0x38ba00   (est. sk_hashtable_hash)
 * Ghidra: void FUN_0038ba00(int *param_1)
 * Hash-seed dispatcher: selects the hash computation by the string-buffer
 * size class at param_1[8]. Size 2 uses sk_type_len8_add_38b948, size 1 uses
 * sk_type_utf8_hi_38b85c, and size 0 recursively counts via
 * sk_type_mangled_count_38b578 (also recording the argument count at
 * param_1[0x4b]). The computed hash is stored at param_1[0x4a].
 * Confidence: medium
 * Notes: canary -0x2c8502b44bfffed6. */
void sk_hashtable_hash_38ba00(int *h)
{
    int i1; long l2; unsigned int u3; long canary;

    canary = -0x2c8502b44bfffed6;
    if (h[8] == 0) {
        i1 = *h;
        if (i1 == 2) {
            i1 = sk_type_len8_add_38b948((long)h, *(unsigned long *)(h + 2));
        } else if (i1 != 1) {
            if (i1 == 0) {
                {
                    long frame[2048] = {0};
                    frame[0] = 0x67b938;
                    i1 = (int)sk_type_mangled_count_38b578((long)h, *(char **)(h + 2), (long)&frame[0]);
                }
                h[0x4a] = i1;
                l2 = sk_cap_meta_35eb3c(*(unsigned long *)(h + 2));
                if (l2 != 0) {
                    if ((*(unsigned short *)(l2 + 10) & 1) == 0) u3 = 0;
                    else u3 = (unsigned int)*(unsigned short *)
                        ((l2 + (unsigned long)*(unsigned short *)(l2 + 4) + 0xf & 0xfffffffffffffffc) +
                         (unsigned long)*(unsigned short *)(l2 + 6) * 0xc + 2);
                    h[0x4b] = u3;
                }
                goto done_8bbc4;
            }
            goto done_8bbc4;
        }
        h[0x4a] = i1;
    }
done_8bbc4:
    if (canary != -0x2c8502b44bfffed6) cL4_stack_fail();
}

/* FUN_0038bbf4 @ 0x38bbf4   (est. sk_type_elem_at)
 * Ghidra: undefined8 FUN_0038bbf4(long param_1, uint param_2, uint param_3)
 * Indexed element lookup in a type-decl string table: resolves the hash seed
 * (sk_hashtable_hash_38ba00), then walks the name array at param_1+0x18 to
 * the param_2-th entry, adds the UTF-8/byte offset param_3, and returns the
 * word at (base + (offset+param_3)*8).
 * Confidence: medium */
unsigned long sk_type_elem_at_38bbf4(long base, unsigned int idx, unsigned int sub)
{
    unsigned long u2; unsigned int u3; unsigned char *pb4; unsigned long u5;
    unsigned long *pu1;

    if (*(long *)(base + 0x10) == 0) return 0;
    sk_hashtable_hash_38ba00((int *)base);
    if ((idx < *(unsigned int *)(base + 0x20)) &&
        (pu1 = (unsigned long *)(*(long *)(base + 0x18) + (unsigned long)idx * 0x20),
         sub < *(unsigned int *)(pu1 + 2))) {
        u3 = *(int *)(base + 300) + *(int *)((long)pu1 + 0x14);
        if (*(char *)((long)pu1 + 0x1c) == '\x01') {
            if (-1 < (char)((unsigned char *)*pu1)[sub]) goto out_8bc68;
            if (sub != 0) {
                u5 = (unsigned long)sub; pb4 = (unsigned char *)*pu1;
                do { u3 += (*pb4 >> 7); u5--; pb4++; } while (u5 != 0);
            }
        } else {
            u3 += sub;
        }
        u2 = *(unsigned long *)(*(long *)(base + 0x10) + (unsigned long)u3 * 8);
    } else {
out_8bc68:
        u2 = 0;
    }
    return u2;
}

/* FUN_0038bd54 @ 0x38bd54   (est. sk_type_flatpair_get)
 * Ghidra: undefined1 [16] FUN_0038bd54(undefined8 param_1, undefined8 param_2)
 * Builds a demangle node for (param_1,param_2), unwraps singleton/list
 * indirections, and when the node kind is 0x27 (an identifier) returns the
 * 16-byte pair {name-with-flags, 1}; otherwise returns {0,0}.
 * Confidence: medium
 * Notes: canary -0x2c8502b44bfffed6. */
cL4_w16_t sk_type_flatpair_get_38bd54(unsigned long a, unsigned long b)
{
    long *pl1; unsigned long u6, u5; cL4_w16_t r; long canary;

    canary = -0x2c8502b44bfffed6;
    {
        unsigned long frame[1024] = {0};
        frame[0] = 0x67a300;
        pl1 = (long *)FUN_003a32a0((unsigned long)&frame[0], a, b, (unsigned long *)&frame[8]);
        cL4_zone_get(&frame[8]);
    }
    if (pl1 != 0) {
        if ((short)pl1[2] == 0xf4) {
            if (1 < *(unsigned char *)((long)pl1 + 0x12) - 1) {
                if ((*(unsigned char *)((long)pl1 + 0x12) != 5) || ((int)pl1[1] == 0)) {
                    pl1 = 0; goto lb_8bea0;
                }
                pl1 = (long *)*pl1;
            }
            pl1 = (long *)*pl1;
        }
lb_8bea0:
        if ((short)pl1[2] == 0x27) {
            unsigned long *p3 = (unsigned long *)*pl1;
            unsigned long *p2 = (unsigned long *)pl1[1];
            u6 = (*p3 & 0xffffff00) | (*p2 << 0x20);
            u5 = *p3 & 0xff;
            r.hi = 1;
            r.lo = u6 | u5;
            goto out_8bf04;
        }
    }
    r.hi = 0; r.lo = 0;
out_8bf04:
    if (canary != -0x2c8502b44bfffed6) cL4_stack_fail();
    return r;
}

/* FUN_0038c0e8 @ 0x38c0e8   (est. sk_type_table_release)
 * Ghidra: void FUN_0038c0e8(undefined8 param_1, int *param_2, long param_3, ulong param_4, long param_5)
 * Releases a type-decl table's element chains: for each row it walks the
 * relative-offset chains (sk_hashtable_unlink_38bf8c) and for the auxiliary
 * buffer it walks its entries unlinking each node, under the lock-object at
 * DAT_006c0a20 (cL4_ref_acquire/cL4_release).
 * Confidence: medium
 * Notes: locks DAT_006c0a30 / DAT_006c0a58 initialised on demand. */
void sk_type_table_release_38c0e8(unsigned long ctx, int *table, long a, unsigned long b, long c)
{
    unsigned int u1; int *p2; long l3; unsigned long u4, u5; long l6; unsigned long u7;
    long l8; int *p9; long l10; long *lslot;
    unsigned long nrows; int *trow; long ncell;

    ncell = (c == 0) ? 0 : ((unsigned long)*(unsigned int *)(b + 4) * 8 + 8);
    if (-1 < (long)_DAT_006c0a30) cL4_diag_log(&_DAT_006c0a30, (unsigned long *)&FUN_0038c324, 0);
    cL4_ref_acquire(0x6c0a20);
    if (a != 0) {
        nrows = (unsigned long)(unsigned int)table[1];
        trow = table;
        while (1) {
            if (nrows != 0) {
                p9 = trow;
                do {
                    p9 += 2;
                    u1 = *(unsigned int *)((long)p9 + (long)*p9 + 4);
                    if (u1 != 0) {
                        l10 = (unsigned long)u1 << 4;
                        l8 = (long)p9 + (long)*p9 + 8;
                        do { sk_hashtable_unlink_38bf8c((int *)l8); l8 += 0x10; l10 -= 0x10; }
                        while (l10 != 0);
                    }
                } while (p9 != trow + nrows * 2);
            }
            l8 = (unsigned long)nrows * 2;
            if ((int *)((long)table + a) <= trow + l8 + 2) break;
            nrows = (unsigned long)(unsigned int)trow[nrows * 2 + 3];
            trow = trow + l8 + 2;
        }
    }
    if (c != 0) {
        u7 = b + c;
        nrows = (unsigned long)*(unsigned int *)(b + 4);
        while (1) {
            if (nrows != 0) {
                l8 = 0;
                do {
                    if (-1 < (long)_DAT_006c0a58) cL4_diag_log(&_DAT_006c0a58, (unsigned long *)&FUN_00399614, (unsigned long)&_DAT_006c0a40);
                    u5 = (unsigned long)*(int *)(b + 8 + l8);
                    lslot = (long *)(b + l8 + (u5 & 0xfffffffffffffffe) + 8);
                    if ((u5 & 1) != 0) lslot = (long *)*lslot;
                    if (lslot == 0) lslot = 0;
                    l10 = b + l8 + (long)*(int *)(b + 8 + l8 + 4) + 0xc;
                    if (l10 == 0) l10 = 0;
                    l3 = FUN_00399d68((unsigned long)&_DAT_006c0a40, &lslot);
                    *(long *)(l3 + 8) = l10;
                    l8 += 8;
                } while (nrows * 8 - l8 != 0);
            }
            b += ncell;
            if (u7 <= b) break;
            nrows = (unsigned long)*(unsigned int *)(b + 4);
            ncell = nrows * 8 + 8;
        }
    }
    cL4_release(0x6c0a20);
}

/* FUN_0038d754 @ 0x38d754   (est. sk_type_vec_insert_range)
 * Ghidra: undefined8 * FUN_0038d754(long *param_1, long param_2, undefined8 *param_3, undefined8 *param_4)
 * Inserts the element range [param_3, param_4) into a growable vector at
 * position param_2. Grows via FUN_00367ccc / sk_wordlist_grow_38a294c
 * (FUN_003a294c) and memmoves the tail to make room.
 * Confidence: medium */
unsigned long *sk_type_vec_insert_range_38d754(long *vec, long pos, unsigned long *start, unsigned long *end)
{
    unsigned long *p3; long l4; unsigned long *p5; unsigned long u6; unsigned long *p7;
    unsigned long u8; long l9; unsigned long u10; long l11; unsigned long n;
    unsigned long *base; unsigned long *newelem;

    l4 = *vec;
    l9 = pos - l4;
    n = (unsigned long)*(unsigned int *)(vec + 1);
    if (pos == l4 + n * 8) {
        FUN_00367ccc((unsigned long *)vec, (unsigned long *)start, (unsigned long *)end);
        return (unsigned long *)(*vec + l9);
    }
    u8 = (unsigned long)end - (unsigned long)start;
    u10 = n + ((long)u8 >> 3);
    if (*(unsigned int *)((long)vec + 0xc) < u10) {
        cL4_wordlist_grow((unsigned long *)vec, (unsigned long *)(vec + 2), u10, 8);
        l4 = *vec;
        n = (unsigned long)*(unsigned int *)(vec + 1);
    }
    p3 = (unsigned long *)(l4 + l9);
    l11 = n * 8;
    l9 = l4 + n * 8;
    u10 = (l11 - l9) >> 3;
    if (u10 < (unsigned long)((long)u8 >> 3)) {
        unsigned int u1 = (unsigned int)n + (unsigned int)(u8 >> 3);
        *(unsigned int *)(vec + 1) = u1;
        if (l11 - l9 != 0) {
            cL4_obj_copy_simple(l4 + (unsigned long)u1 * 8 + u10 * -8, (unsigned long)p3, 0);
            p5 = p3; p7 = start;
            do { start = p7 + 1; *p5 = *p7; u10--; p5++; p7 = start; } while (u10 != 0);
        }
        if (start != end) cL4_obj_copy_simple(l9, (unsigned long)start, (unsigned long)end - (unsigned long)start);
    } else {
        sk_vec_append_range_38e114(vec, (unsigned long *)(l9 - u8), (unsigned long *)l9);
        if ((unsigned long *)(l9 - u8) != p3) {
            FUN_00117d14(l9 - (l11 - (l9 + u8)), (unsigned long)p3, 0);
        }
        if (end != start) {
            p3 = (unsigned long *)FUN_00117d14((unsigned long)p3, (unsigned long)start, u8);
            return p3;
        }
    }
    return p3;
}

/* FUN_0038df24 @ 0x38df24   (est. sk_type_utf8_decode)
 * Ghidra: void FUN_0038df24(long *param_1, undefined8 param_2)
 * Decodes a UTF-8 string (param_2) into a freshly allocated NUL-terminated
 * buffer, storing the pointer in *param_1 (0 on failure). First pass with a
 * null buffer measures the length, second allocates and fills.
 * Confidence: medium */
void sk_type_utf8_decode_38df24(long *out, unsigned long s)
{
    int i1; long l2;
    i1 = FUN_00116bb4(0, 0, s, &l2);
    *out = 0;
    if (-1 < i1) {
        l2 = FUN_000101a0(i1 + 1, 0x100004077774924);
        if (l2 != 0) {
            i1 = FUN_00116bb4(l2, i1 + 1, s, &l2);
            if (i1 < 0) thunk_FUN_00012568(l2);
            else *out = l2;
        }
    }
}

/* FUN_0038dfc8 @ 0x38dfc8   (est. sk_type_err_generic_args)
 * Ghidra: undefined8 * FUN_0038dfc8(undefined8 *param_1, int param_2, undefined8 param_3)
 * Error-descriptor builder: builds "failed to get parent context, <generic
 * arguments>" (param_2==0 path) or clones the node (param_2==2 path) into a
 * freshly allocated 0x20-byte descriptor.
 * Confidence: medium */
unsigned long *sk_type_err_generic_args_38dfc8(unsigned long *node, int mode, unsigned long v)
{
    unsigned long *p4; unsigned long u3; unsigned long *lslot;
    if (mode < 2) {
        if (mode == 0) {
            unsigned long lerr[4];
            sk_err_ctx_38dd44(lerr, (unsigned long *)node);
            p4 = FUN_00112db4((unsigned long)lerr, (unsigned long)s_failed_to_get_parent_context_s_w_005d533b);
            u3 = p4[2];
            { unsigned long w0 = *p4, w1 = p4[1]; p4[1] = 0; p4[2] = 0; *p4 = 0;
              p4 = FUN_00112db4(w0, (unsigned long)s_generic_arguments_005d5362); }
            if ((long)u3 < 0) thunk_FUN_00012568(0, u3 & 0x7fffffffffffffff);
            lslot = (unsigned long *)p4[2];
            return (unsigned long *)FUN_00118cf8((unsigned long)&lslot);
        }
        thunk_FUN_00012568(v);
    } else {
        if (mode == 2) {
            p4 = cL4_alloc(0x20, 0x1060c404361888d);
            p4[1] = node[1]; *p4 = *node; p4[3] = node[3]; p4[2] = node[2];
            return p4;
        }
        if (node == 0) return 0;
        thunk_FUN_00012568((unsigned long)node, 0x20);
    }
    return 0;
}

/* FUN_0038e214 @ 0x38e214   (est. sk_type_err_generic_count)
 * Ghidra: undefined8 * FUN_0038e214(undefined8 *param_1, int param_2, undefined8 param_3)
 * Error-descriptor builder: "<have> <N> generic args, expected <M>" for the
 * param_2==0 path, or clones the node (0x30-byte) for param_2==2.
 * Confidence: medium */
unsigned long *sk_type_err_generic_count_38e214(unsigned long *node, int mode, unsigned long v)
{
    unsigned long *p4;
    if (mode < 2) {
        if (mode == 0) {
            unsigned long lerr[4]; unsigned long a0[4], a1[4];
            sk_err_ctx_38dd44(lerr, (unsigned long *)node);
            p4 = FUN_00112db4((unsigned long)lerr, (unsigned long)s_have_005d5375);
            a0[0] = p4[2]; { unsigned long w0=*p4,w1=p4[1]; p4[1]=0;p4[2]=0;*p4=0;
              FUN_00113a3c(&a1[0], node[4]);
              p4 = FUN_00112db4(w0, (unsigned long)a1); }
            a1[0] = p4[2];
            p4 = FUN_00112db4(*p4, (unsigned long)s_generic_args__expected_005d537b);
            a0[0] = p4[2];
            { unsigned long w0=*p4,w1=p4[1]; p4[1]=0;p4[2]=0;*p4=0;
              FUN_0011394c(&a1[0], *(unsigned int *)(node + 5));
              p4 = FUN_00112db4(w0, (unsigned long)a1); }
            if ((long)a0[0] < 0) thunk_FUN_00012568(0, a0[0] & 0x7fffffffffffffff);
            { unsigned long *lslot = (unsigned long *)p4[2];
              return (unsigned long *)FUN_00118cf8((unsigned long)&lslot); }
        }
        thunk_FUN_00012568(v);
    } else {
        if (mode == 2) {
            p4 = cL4_alloc(0x30, 0x1060c40e00dce36);
            p4[1] = node[1]; *p4 = *node; p4[3] = node[3]; p4[2] = node[2];
            p4[5] = node[5]; p4[4] = node[4];
            return p4;
        }
        if (node == 0) return 0;
        thunk_FUN_00012568((unsigned long)node, 0x30);
    }
    return 0;
}

/* FUN_0038e458 @ 0x38e458   (est. sk_type_err_meta_type)
 * Ghidra: undefined8 * FUN_0038e458(undefined8 *param_1, int param_2, undefined8 param_3)
 * Error-descriptor builder: "<param> <N> expected metadata but got a
 * metatype" (param_2==0), or clones the node (0x28-byte).
 * Confidence: medium */
unsigned long *sk_type_err_meta_type_38e458(unsigned long *node, int mode, unsigned long v)
{
    unsigned long *p4;
    if (mode < 2) {
        if (mode == 0) {
            unsigned long lerr[4]; unsigned long a0[4], a1[4];
            sk_err_ctx_38dd44(lerr, (unsigned long *)node);
            p4 = FUN_00112db4((unsigned long)lerr, (unsigned long)s_param_005d5393);
            { unsigned long w0=*p4,w1=p4[1]; p4[1]=0;p4[2]=0;*p4=0;
              FUN_0011394c(&a1[0], *(unsigned int *)(node + 4));
              p4 = FUN_00112db4(w0, (unsigned long)a1); }
            a1[0] = p4[2];
            p4 = FUN_00112db4(*p4, (unsigned long)s_expected_metadata_but_got_a_meta_005d539a);
            if ((long)a1[0] < 0) thunk_FUN_00012568(0, a1[0] & 0x7fffffffffffffff);
            { unsigned long *lslot = (unsigned long *)p4[2];
              return (unsigned long *)FUN_00118cf8((unsigned long)&lslot); }
        }
        thunk_FUN_00012568(v);
    } else {
        if (mode == 2) {
            p4 = cL4_alloc(0x28, 0x1060c40fbdf1fb7);
            p4[1] = node[1]; *p4 = *node; p4[3] = node[3]; p4[2] = node[2];
            p4[4] = node[4];
            return p4;
        }
        if (node == 0) return 0;
        thunk_FUN_00012568((unsigned long)node, 0x28);
    }
    return 0;
}

/* FUN_0038e624 @ 0x38e624   (est. sk_type_err_meta_pack)
 * Ghidra: undefined8 * FUN_0038e624(undefined8 *param_1, int param_2, undefined8 param_3)
 * Error-descriptor builder: "<param> <N> expected a metadata pack but got
 * ..." (param_2==0), or clones the node (0x28-byte).
 * Confidence: medium */
unsigned long *sk_type_err_meta_pack_38e624(unsigned long *node, int mode, unsigned long v)
{
    unsigned long *p4;
    if (mode < 2) {
        if (mode == 0) {
            unsigned long lerr[4]; unsigned long a0[4], a1[4];
            sk_err_ctx_38dd44(lerr, (unsigned long *)node);
            p4 = FUN_00112db4((unsigned long)lerr, (unsigned long)s_param_005d5393);
            { unsigned long w0=*p4,w1=p4[1]; p4[1]=0;p4[2]=0;*p4=0;
              FUN_0011394c(&a1[0], *(unsigned int *)(node + 4));
              p4 = FUN_00112db4(w0, (unsigned long)a1); }
            a1[0] = p4[2];
            p4 = FUN_00112db4(*p4, (unsigned long)s_expected_a_metadata_pack_but_got_005d53c5);
            if ((long)a1[0] < 0) thunk_FUN_00012568(0, a1[0] & 0x7fffffffffffffff);
            { unsigned long *lslot = (unsigned long *)p4[2];
              return (unsigned long *)FUN_00118cf8((unsigned long)&lslot); }
        }
        thunk_FUN_00012568(v);
    } else {
        if (mode == 2) {
            p4 = cL4_alloc(0x28, 0x1060c40fbdf1fb7);
            p4[1] = node[1]; *p4 = *node; p4[3] = node[3]; p4[2] = node[2];
            p4[4] = node[4];
            return p4;
        }
        if (node == 0) return 0;
        thunk_FUN_00012568((unsigned long)node, 0x28);
    }
    return 0;
}

/* FUN_0038e7f0 @ 0x38e7f0   (est. sk_type_err_unexpected_kind)
 * Ghidra: undefined8 * FUN_0038e7f0(undefined8 *param_1, int param_2, undefined8 param_3)
 * Error-descriptor builder: "<param> <N> has unexpected kind <K>"
 * (param_2==0), or clones the node (0x28-byte).
 * Confidence: medium */
unsigned long *sk_type_err_unexpected_kind_38e7f0(unsigned long *node, int mode, unsigned long v)
{
    unsigned long *p4;
    if (mode < 2) {
        if (mode == 0) {
            unsigned long lerr[4]; unsigned long a0[4], a1[4];
            sk_err_ctx_38dd44(lerr, (unsigned long *)node);
            p4 = FUN_00112db4((unsigned long)lerr, (unsigned long)s_param_005d5393);
            { unsigned long w0=*p4,w1=p4[1]; p4[1]=0;p4[2]=0;*p4=0;
              FUN_0011394c(&a1[0], *(unsigned int *)(node + 4));
              p4 = FUN_00112db4(w0, (unsigned long)a1); }
            a1[0] = p4[2];
            p4 = FUN_00112db4(*p4, (unsigned long)s_has_unexpected_kind_005d5413);
            { unsigned long w0=*p4,w1=p4[1]; p4[1]=0;p4[2]=0;*p4=0;
              FUN_001137f8(&a1[0], *(unsigned char *)((long)node + 0x24) & 0x3f);
              p4 = FUN_00112db4(w0, (unsigned long)a1); }
            if ((long)a1[0] < 0) thunk_FUN_00012568(0, a1[0] & 0x7fffffffffffffff);
            { unsigned long *lslot = (unsigned long *)p4[2];
              return (unsigned long *)FUN_00118cf8((unsigned long)&lslot); }
        }
        thunk_FUN_00012568(v);
    } else {
        if (mode == 2) {
            p4 = cL4_alloc(0x28, 0x1060c4063e0ddf5);
            p4[1] = node[1]; *p4 = *node; p4[3] = node[3]; p4[2] = node[2];
            p4[4] = node[4];
            return p4;
        }
        if (node == 0) return 0;
        thunk_FUN_00012568((unsigned long)node, 0x28);
    }
    return 0;
}

/* FUN_0038ece8 @ 0x38ece8   (est. sk_type_err_gen_arg_mismatch)
 * Ghidra: undefined8 * FUN_0038ece8(undefined8 *param_1, int param_2, undefined8 param_3)
 * Error-descriptor builder: "generic argument count mismatch, <have> <N>"
 * (param_2==0), or clones the node (0x30-byte).
 * Confidence: medium */
unsigned long *sk_type_err_gen_arg_mismatch_38ece8(unsigned long *node, int mode, unsigned long v)
{
    unsigned long *p4;
    if (mode < 2) {
        if (mode == 0) {
            unsigned long lerr[4]; unsigned long a0[4], a1[4], a2[4];
            sk_err_ctx_38dd44(lerr, (unsigned long *)node);
            p4 = FUN_00112db4((unsigned long)lerr, (unsigned long)s_generic_argument_count_mismatch__005d5429);
            { unsigned long w0=*p4,w1=p4[1]; p4[1]=0;p4[2]=0;*p4=0;
              FUN_0011394c(&a1[0], *(unsigned short *)(node[4] + 8));
              p4 = FUN_00112db4(w0, (unsigned long)a1); }
            a1[0] = p4[2];
            p4 = FUN_00112db4(*p4, (unsigned long)s___have_005d5454);
            a2[0] = p4[2];
            { unsigned long w0=*p4,w1=p4[1]; p4[1]=0;p4[2]=0;*p4=0;
              FUN_00113a3c(&a1[0], node[5]);
              p4 = FUN_00112db4(w0, (unsigned long)a1); }
            if ((long)a1[0] < 0) thunk_FUN_00012568(0, a1[0] & 0x7fffffffffffffff);
            { unsigned long *lslot = (unsigned long *)p4[2];
              return (unsigned long *)FUN_00118cf8((unsigned long)&lslot); }
        }
        thunk_FUN_00012568(v);
    } else {
        if (mode == 2) {
            p4 = cL4_alloc(0x30, 0x1060c4032852127);
            p4[1] = node[1]; *p4 = *node; p4[3] = node[3]; p4[2] = node[2];
            p4[5] = node[5]; p4[4] = node[4];
            return p4;
        }
        if (node == 0) return 0;
        thunk_FUN_00012568((unsigned long)node, 0x30);
    }
    return 0;
}

/* FUN_0038ef30 @ 0x38ef30   (est. sk_type_is_c_header)
 * Ghidra: bool FUN_0038ef30(long param_1)
 * Tests whether the identifier string at param_1 is the Swift "@_cdecl"-style
 * "__C" header marker: kind (offset +8) resolves to 3 and the short reads
 * 0x5f5f ('__') followed by 'C'.
 * Confidence: high (string-matched "__C") */
bool sk_type_is_c_header_38ef30(long p)
{
    short *ps;
    ps = (short *)(p + 8 + (long)*(int *)(p + 8));
    if ((ps == 0) || (FUN_00115080((unsigned long)ps) != 3)) return false;
    return (*ps == 0x5f5f && (char)ps[1] == 'C');
}

/* FUN_0038ea44 @ 0x38ea44   (est. sk_type_bucket_9f0)
 * Ghidra: void FUN_0038ea44(long param_1)
 * Allocates a 0x10-byte bucket node tagged 0xa1c40bd48d6d6, sets its kind
 * word to 0x67b9f0 and links the caller's value at param_1+8.
 * Confidence: medium */
void sk_type_bucket_9f0_38ea44(long a)
{
    unsigned long *n;
    n = (unsigned long *)cL4_alloc(0x10, 0xa1c40bd48d6d6);
    *n = 0x67b9f0; n[1] = *(unsigned long *)(a + 8);
}

/* FUN_0038eb60 @ 0x38eb60   (est. sk_type_bucket_a38)
 * Ghidra: void FUN_0038eb60(long param_1)
 * Bucket node tagged 0xa1c40bd48d6d6, kind word 0x67ba38.
 * Confidence: medium */
void sk_type_bucket_a38_38eb60(long a)
{
    unsigned long *n;
    n = (unsigned long *)cL4_alloc(0x10, 0xa1c40bd48d6d6);
    *n = 0x67ba38; n[1] = *(unsigned long *)(a + 8);
}

/* FUN_0038ec3c @ 0x38ec3c   (est. sk_type_bucket_a80)
 * Ghidra: void FUN_0038ec3c(long param_1)
 * Bucket node tagged 0xa1c40bd48d6d6, kind word 0x67ba80.
 * Confidence: medium */
void sk_type_bucket_a80_38ec3c(long a)
{
    unsigned long *n;
    n = (unsigned long *)cL4_alloc(0x10, 0xa1c40bd48d6d6);
    *n = 0x67ba80; n[1] = *(unsigned long *)(a + 8);
}

/* FUN_00394404 @ 0x394404   (est. sk_type_decode_sig)
 * Ghidra: void FUN_00394404(undefined8 *param_1, undefined8 *param_2, undefined8 *param_3, uint param_4, long *param_5, undefined8 *param_6)
 * Recursively decodes a generic signature node (param_3) into a concrete
 * type-decl (param_5) and result (param_6), bounded by depth param_4 (<
 * 0x401). Unwraps singleton/list indirections (kind 0xf4/0xf5), on a
 * free-standing node resolves via sk_type_cache_lookup_388630, and otherwise
 * recurses through sk_type_decode_38f0a8 / sk_type_decl_ctx_resolve
 * (FUN_003c3264). Errors carry the "TypeDecoder.h: <N> node kind <K>"
 * descriptor.
 * Confidence: medium
 * Notes: node kind byte at +0x12; canary -0x2c8502b44bfffed6. */
void sk_type_decode_sig_394404(unsigned long *out, unsigned long *ctx, unsigned long *node,
                               unsigned int depth, long *decl, unsigned long *result)
{
    unsigned short u4; unsigned char b2; char c3; unsigned long u8, u9; unsigned int u10;
    unsigned long *pu6; char *pc7; long l5; long canary; int i1; long res; long lc;
    unsigned long *n;

    canary = -0x2c8502b44bfffed6;
    if (depth < 0x401) {
        i1 = depth + 1;
        do {
            u4 = *(unsigned short *)(node + 2);
            if (u4 != 0xf4) {
                if (u4 != 0xf5) {
                    u9 = 0; u10 = 0;
                    b2 = *(unsigned char *)((long)node + 0x12);
                    u8 = (unsigned long)b2;
                    n = (unsigned long *)&DAT_005be7c0;
                    if (b2 < 3) {
                        n = (unsigned long *)&DAT_005be7c0;
                        if (b2 == 1) { u10 = 0; u9 = 1; goto lb_945a4; }
                        pu6 = node;
                        if (b2 != 2) goto lb_945a4;
                        goto ind_945f4;
                    }
                    if (b2 == 3) {
                        u9 = 0; u10 = *(unsigned int *)(node + 1);
                        n = (unsigned long *)*node;
                    } else if (b2 == 5) {
                        u9 = (unsigned long)*(unsigned int *)(node + 1);
                        if (1 < *(unsigned int *)(node + 1)) { pu6 = (unsigned long *)*node; goto ind_945f4; }
                        u10 = 0;
                    }
lb_945a4:
                    pu6 = cL4_alloc(0x28, 0x1050c400dfe80cb);
                    *pu6 = (unsigned long)s_TypeDecoder_h__u__Node_kind__u___005d59f4;
                    *(unsigned int *)(pu6 + 1) = 0x72c;
                    *(unsigned int *)((long)pu6 + 0xc) = (unsigned int)u4;
                    *(unsigned int *)(pu6 + 2) = u10;
                    pu6[3] = (unsigned long)n;
                    pu6[4] = u9;
                    *out = (unsigned long)pu6;
                    out[1] = (unsigned long)FUN_00397fc0;
                    goto lb_944bc;
ind_945f4:
                    pu6 = (unsigned long *)*pu6;
                    if (*(short *)(pu6 + 2) == 0xa3) goto lb_94504;
                    if (*(short *)(pu6 + 2) == 0x49) {
                        c3 = *(char *)((long)pu6 + 0x12);
                        if (c3 == '\x02') { un_i_946a8: pu6 = (unsigned long *)pu6[1]; goto un_i_946ac; }
                        if (c3 == '\x03') { u10 = *(unsigned int *)(pu6 + 1); n = (unsigned long *)*pu6; }
                        else {
                            if ((c3 == '\x05') && (1 < *(unsigned int *)(pu6 + 1))) { pu6 = (unsigned long *)*pu6; goto un_i_946a8; }
                            u10 = 0; n = (unsigned long *)&DAT_005be7c0;
                        }
                        if (b2 != 2) u8 = (b2 == 5) ? (unsigned long)*(unsigned int *)(node + 1) : 0;
                        pu6 = cL4_alloc(0x28, 0x1050c400dfe80cb);
                        *pu6 = (unsigned long)s_TypeDecoder_h__u__Node_kind__u___005d5a51;
                        pu6[1] = DAT_004f28f8;
                        *(unsigned int *)(pu6 + 2) = u10;
                        pu6[3] = (unsigned long)n;
                        pu6[4] = u8;
                    } else {
                        /* 0x49/0xa3 child: recurse via decoder + ctx resolve */
                        FUN_003c3264(&res, (unsigned long)node, *(unsigned long *)*ctx);
                        if (res == 0) goto lb_94504;
                        pc7 = (char *)s_Failed_to_unspecialize_type_005d5ab7;
                        goto lb_944a8;
                    }
un_i_946ac:
                    sk_type_decode_38f0a8(&res, ctx, (unsigned long)pu6, i1, 1);
                    if (res == 0) *result = 0;
                    FUN_003c3264(&res, (unsigned long)node, *(unsigned long *)*ctx);
                    node = (unsigned long *)res;
                    if (res == 0) goto lb_94504;
                    pc7 = (char *)s_Failed_to_unspecialize_type_005d5ab7;
                    goto lb_944a8;
                }
lb_94504:
                l5 = sk_type_cache_lookup_388630(node, *(unsigned long *)*ctx);
                *decl = l5;
                if (l5 == 0) { pc7 = (char *)s_Failed_to_create_type_decl_005d5ad3; goto lb_944a8; }
                *(unsigned char *)out = 0;
                *(unsigned char *)(out + 2) = 0;
                goto lb_944c4;
            }
            if (*(unsigned char *)((long)node + 0x12) - 1 < 2) {
            ind_94488:
                node = (unsigned long *)*node;
            } else {
                if ((*(unsigned char *)((long)node + 0x12) == 5) && (*(int *)(node + 1) != 0)) {
                    node = (unsigned long *)*node; goto ind_94488;
                }
                node = 0;
            }
            i1 = i1 + 1;
        } while (i1 != 0x402);
    }
    pc7 = (char *)s_Mangled_type_is_too_complex_005d548f;
lb_944a8:
    *out = (unsigned long)pc7;
    out[1] = (unsigned long)FUN_0037f9f4;
lb_944bc:
    *(unsigned char *)(out + 2) = 1;
lb_944c4:
    if (canary != -0x2c8502b44bfffed6) cL4_stack_fail();
}

/* FUN_00394724 @ 0x394724   (est. sk_type_build_func)
 * Ghidra: void FUN_00394724(undefined8 param_1, undefined8 param_2, undefined8 param_3)
 * Thin wrapper: sk_type_build_decl_394968(param_1, param_2, 0, 0, param_3).
 * Confidence: medium */
void sk_type_build_func_394724(unsigned long a, unsigned long b, unsigned long c)
{
    sk_type_build_decl_394968((long *)a, (unsigned long *)b, 0, 0, c, 0);
}

/* FUN_00394734 @ 0x394734   (est. sk_type_decode_sig)
 * Ghidra: void FUN_00394734(undefined8 *param_1, undefined8 param_2, ushort *param_3, undefined8 param_4, undefined8 param_5)
 * Decodes a type-list node (param_3): if the node kind at param_3[8] isn't
 * 0xf7 (TypeList) it builds the "Node kind <K> is not TypeList" error; else
 * it walks each element (relative-offset list) recursing through
 * sk_type_decode_38f0a8 and appending the materialized result to param_5
 * (cL4_list_push_363f10). The first result is returned in param_1.
 * Confidence: medium
 * Notes: canary -0x2c8502b44bfffed6. */
void sk_type_decode_sig_394734(unsigned long *out, unsigned long ctx, unsigned short *node,
                               unsigned long a, unsigned long b)
{
    unsigned short *pu7, *pu11; unsigned short u3; unsigned char b2;
    unsigned long u10; unsigned long res; long canary; unsigned short *limit;
    unsigned long uVar1; unsigned int u8;

    canary = -0x2c8502b44bfffed6;
    pu7 = node + 8;
    u3 = *pu7;
    if (u3 != 0xf7) {
        unsigned long *pu6; unsigned char *pu9;
        unsigned int u8v = (*(char *)(node + 9) == '\x03') ? *(unsigned int *)(node + 4)
                                                          : (unsigned int)(unsigned long)0;
        pu9 = (*(char *)(node + 9) == '\x03') ? *(unsigned char **)node : (unsigned char *)&DAT_005be7c0;
        pu6 = cL4_alloc(0x28, 0x1050c401ab4594e);
        *pu6 = (unsigned long)s_TypeDecoder_h__u__Node_kind__u___005d54b8;
        *(unsigned int *)(pu6 + 1) = 0x70d;
        *(unsigned int *)((long)pu6 + 0xc) = (unsigned int)u3;
        *(unsigned int *)(pu6 + 2) = u8v;
        pu6[3] = (unsigned long)pu9;
        pu6[4] = (unsigned long)s_is_not_TypeList_005d5aee;
        *out = (unsigned long)pu6;
        out[1] = (unsigned long)FUN_00397f0c;
        *(unsigned char *)(out + 2) = 1;
        goto lb_9492c;
    }
    b2 = (unsigned char)node[9];
    pu11 = node;
    if (b2 - 1 < 2) {
lb_94834:
        if (b2 == 1) { pu7 = node + 4; goto lb_94870; }
        if (b2 != 2) {
            if (b2 == 5) { pu7 = *(unsigned short **)node; goto lb_94850; }
            pu7 = 0; goto lb_94870;
        }
        u10 = *out;
lb_9487c:
        {
            unsigned long *res2; unsigned long pcv;
            sk_type_decode_38f0a8(&res2, (unsigned long *)ctx, *(unsigned long *)pu11, a, 0);
            if (res2 == 1) {
                u10 = ((unsigned long (*)(unsigned long, unsigned long, unsigned long))out[1])((unsigned long)res2, 2, 0);
            } else {
                unsigned long v = (res2 != 0) ? (unsigned long)res2 : 0;
                cL4_list_push_363f10((long *)b, v);
            }
            if (res2 == 1) *(unsigned char *)(out + 2) = 1;
            pu11 += 4;
        }
        if (pu11 != pu7) goto lb_9487c;
    } else {
        if (b2 != 5) { pu11 = 0; goto lb_94834; }
        pu7 = *(unsigned short **)node;
        pu11 = pu7;
lb_94850:
        pu7 = pu7 + (unsigned long)*(unsigned int *)(node + 4) * 4;
lb_94870:
        u10 = *out;
        if (pu11 != pu7) goto lb_9487c;
    }
    *out = u10;
    *(unsigned char *)out = 0;
    *(unsigned char *)(out + 2) = 0;
lb_9492c:
    if (canary != -0x2c8502b44bfffed6) cL4_stack_fail();
}

/* FUN_00394968 @ 0x394968   (est. sk_type_build_decl)
 * Ghidra: void FUN_00394968(long *param_1, undefined8 *param_2, uint *param_3, undefined8 param_4, undefined8 param_5, ulong param_6)
 * Builds a type declaration: validates the source node (bit 4 of *param_3 for
 * bound-generic, else kind 3 for indirect), materializes the generic
 * arguments via sk_type_build_generic_38ad64 and dispatches the result via
 * sk_tail_call_dispatch_38b4cc. "Tried to build a bound generic type"
 * descriptor when param_6 is odd.
 * Confidence: medium
 * Notes: canary -0x2c8502b44bfffed6. */
void sk_type_build_decl_394968(long *out, unsigned long *tree, unsigned int *node,
                               unsigned long a, unsigned long b, unsigned long c)
{
    unsigned int u1; long l2; unsigned long u3; long l5; long canary;
    long lvar; unsigned long *gv, *types; unsigned long n2, n3;

    canary = -0x2c8502b44bfffed6;
    if (((node == 0) || ((*node >> 4 & 1) == 0)) || (node == 0)) {
        if (((node != 0) && ((*node & 0x1f) == 3)) && (node != 0)) {
            l5 = FUN_00374e2c(node);
            *(unsigned short *)(out + 2) = 0;
            *out = l5;
            if (l5 != 0) goto lb_94adc;
        }
        *out = (long)s_unknown_error_005d5481;
        out[1] = (long)FUN_0037f9f4;
        *(unsigned short *)(out + 2) = 1;
    } else {
        if ((c & 1) != 0) {
            unsigned long *pu;
            u3 = (unsigned long)cL4_alloc(8, 0x50c40ee9192b6);
            *(unsigned short *)(out + 2) = 1;
            out[1] = (long)FUN_00398074;
            pu = cL4_alloc(8, 0x50c40ee9192b6);
            *pu = (unsigned long)s_Tried_to_build_a_bound_generic_t_005d5afe;
            *out = (long)pu;
            if (canary == -0x2c8502b44bfffed6) { thunk_FUN_00012568(u3, 8); return; }
            goto lb_94c3c;
        }
        n2 = DAT_004f2710; n3 = DAT_004f2710;
        gv = (unsigned long *)&n2;
        types = (unsigned long *)&n3;
        sk_type_build_generic_38ad64(&lvar, (unsigned long)node, a, b, c, (long *)gv, (long *)types, *tree);
        l5 = lvar;
        if (l5 != 0) {
            u1 = node[3];
            if ((u1 != 0) && (l5 = (long)(int)u1 + (long)(node + 3), l5 != 0)) {
                sk_tail_call_dispatch_38b4cc((unsigned long *)&lvar, 0xff, (unsigned long *)types, (long)(n3 & 0xffffffff));
                l5 = (long)lvar;
                *(unsigned short *)(out + 2) = 0;
                *out = l5;
                if (l5 != 0) goto lb_94c18;
            }
            *out = (long)s_unknown_error_005d5481;
            out[1] = (long)FUN_0037f9f4;
            *(unsigned short *)(out + 2) = 1;
        }
lb_94c18:
        ;
    }
lb_94adc:
    if (canary != -0x2c8502b44bfffed6) return;
lb_94c3c:
    cL4_stack_fail();
}

/* FUN_00394c40 @ 0x394c40   (est. sk_type_materialize)
 * Ghidra: void FUN_00394c40(undefined8 *param_1, undefined8 param_2, undefined8 param_3)
 * Materializes a builtin type by matching the mangled name against the Swift
 * builtin primitive set (Bi16/Bi32/Bi63/Bi64/Bi128/Bi256/Bi512, Bf16/Bf32/
 * Bf64/Bf80/Bf128 and 0x5d37d4 special) via sk_type_lookup_check_3885e4,
 * selecting the matching vtable (0x67afa0..0x67b130) and storing
 * vtable+8 into *param_1.
 * Confidence: high (string-matched builtin names)
 * Notes: unknown name -> unknown_error descriptor. */
void sk_type_materialize_394c40(unsigned long *out, unsigned long a, unsigned long b)
{
    unsigned long vt;
    if (sk_type_lookup_check_3885e4(a, b, (unsigned long)&DAT_005d5b42)) vt = 0x67afa0;
    else if (sk_type_lookup_check_3885e4(a, b, (unsigned long)&DAT_005d5b47)) vt = 0x67afb0;
    else if (sk_type_lookup_check_3885e4(a, b, (unsigned long)&DAT_005d5b4c)) vt = 0x67afc0;
    else if (sk_type_lookup_check_3885e4(a, b, (unsigned long)s_Bi16__005d5b51)) vt = 0x67afd0;
    else if (sk_type_lookup_check_3885e4(a, b, (unsigned long)s_Bi32__005d5b57)) vt = 0x67afe0;
    else if (sk_type_lookup_check_3885e4(a, b, (unsigned long)s_Bi63__005d5b5d)) vt = (unsigned long)FUN_0067aff0;
    else if (sk_type_lookup_check_3885e4(a, b, (unsigned long)s_Bi64__005d5b63)) vt = 0x67b000;
    else if (sk_type_lookup_check_3885e4(a, b, (unsigned long)s_Bi128__005d5b69)) vt = 0x67b010;
    else if (sk_type_lookup_check_3885e4(a, b, (unsigned long)s_Bi256__005d5b70)) vt = 0x67b020;
    else if (sk_type_lookup_check_3885e4(a, b, (unsigned long)s_Bi512__005d5b77)) vt = 0x67b030;
    else if (sk_type_lookup_check_3885e4(a, b, (unsigned long)&DAT_005d5b7e)) vt = 0x67b040;
    else if (sk_type_lookup_check_3885e4(a, b, (unsigned long)s_Bf16__005d5b81)) vt = 0x67b050;
    else if (sk_type_lookup_check_3885e4(a, b, (unsigned long)s_Bf32__005d5b87)) vt = 0x67b060;
    else if (sk_type_lookup_check_3885e4(a, b, (unsigned long)s_Bf64__005d5b8d)) vt = 0x67b070;
    else if (sk_type_lookup_check_3885e4(a, b, (unsigned long)s_Bf80__005d5b93)) vt = 0x67b080;
    else if (sk_type_lookup_check_3885e4(a, b, (unsigned long)s_Bf128__005d5b99)) vt = 0x67b090;
    else if (sk_type_lookup_check_3885e4(a, b, (unsigned long)&DAT_005d5ba0)) vt = 0x67b0a0;
    else if (sk_type_lookup_check_3885e4(a, b, (unsigned long)&DAT_005d5ba3)) vt = 0x67b0b0;
    else if (sk_type_lookup_check_3885e4(a, b, (unsigned long)&DAT_005d5ba6)) vt = 0x67b0c0;
    else if (sk_type_lookup_check_3885e4(a, b, (unsigned long)&DAT_005d37d4)) vt = 0x67b0d0;
    else if (sk_type_lookup_check_3885e4(a, b, (unsigned long)&DAT_005d5ba9)) vt = 0x67b0e0;
    else if (sk_type_lookup_check_3885e4(a, b, (unsigned long)&DAT_005d5bac)) vt = 0x67b0f0;
    else if (sk_type_lookup_check_3885e4(a, b, (unsigned long)&DAT_005d5baf)) vt = 0x67b100;
    else if (sk_type_lookup_check_3885e4(a, b, (unsigned long)&DAT_005d5bb2)) vt = 0x67b110;
    else if (sk_type_lookup_check_3885e4(a, b, (unsigned long)&DAT_005d5bb5)) vt = 0x67b120;
    else if (sk_type_lookup_check_3885e4(a, b, (unsigned long)&DAT_005d5bb8)) vt = 0x67b130;
    else {
        *out = (unsigned long)s_unknown_error_005d5481;
        out[1] = (unsigned long)FUN_0037f9f4;
        *(unsigned short *)(out + 2) = 1;
        return;
    }
    *(unsigned short *)(out + 2) = 0;
    *out = vt + 8;
}

/* FUN_003950a4 @ 0x3950a4   (est. sk_type_materialize_exist)
 * Ghidra: void FUN_003950a4(long *param_1, ulong param_2)
 * Materializes an existential metatype from metadata pack param_2 (nonzero
 * even pointer). On failure returns "unknown error"; if param_2 is null/odd,
 * returns the "Tried to build a metatype from a value that is not a pack"
 * error descriptor.
 * Confidence: medium */
void sk_type_materialize_exist_3950a4(long *out, unsigned long m)
{
    long l1; unsigned long u2; unsigned long *pu3;
    if ((m != 0) && ((m & 1) == 0)) {
        l1 = FUN_003743d0();
        *(unsigned short *)(out + 2) = 0;
        *out = l1;
        if (l1 == 0) {
            *out = (long)s_unknown_error_005d5481;
            out[1] = (long)FUN_0037f9f4;
            *(unsigned short *)(out + 2) = 1;
        }
        return;
    }
    u2 = (unsigned long)cL4_alloc(8, 0x50c40ee9192b6);
    *(unsigned short *)(out + 2) = 1;
    out[1] = (long)FUN_00398074;
    pu3 = cL4_alloc(8, 0x50c40ee9192b6);
    *pu3 = (unsigned long)s_Tried_to_build_a_metatype_from_a_005d5bbb;
    *out = (long)pu3;
    thunk_FUN_00012568(u2, 8);
}

/* FUN_0039517c @ 0x39517c   (est. sk_type_materialize_exist)
 * Ghidra: void FUN_0039517c(long *param_1, ulong *param_2)
 * Materializes an existential-metatype descriptor for a pack whose kind word
 * (*param_2) is 0x303 or 0x306; otherwise builds the corresponding error.
 * Confidence: medium */
void sk_type_materialize_exist_39517c(long *out, unsigned long *m)
{
    long l1; unsigned long u2; unsigned long *pu3; int i4; char *pc5;
    if ((m == 0) || (((unsigned long)m & 1) != 0)) {
        u2 = (unsigned long)cL4_alloc(8, 0x50c40ee9192b6);
        *(unsigned short *)(out + 2) = 1;
        out[1] = (long)FUN_00398074;
        pu3 = cL4_alloc(8, 0x50c40ee9192b6);
        pc5 = (char *)s_Tried_to_build_an_existential_me_005d5be1;
    } else {
        i4 = 0;
        if (*m < 0x800) i4 = (int)*m;
        if ((i4 == 0x303) || (i4 == 0x306)) {
            l1 = FUN_00374838();
            *(unsigned short *)(out + 2) = 0;
            *out = l1;
            if (l1 == 0) {
                *out = (long)s_unknown_error_005d5481;
                out[1] = (long)FUN_0037f9f4;
                *(unsigned short *)(out + 2) = 1;
            }
            return;
        }
        u2 = (unsigned long)cL4_alloc(8, 0x50c40ee9192b6);
        *(unsigned short *)(out + 2) = 1;
        out[1] = (long)FUN_00398074;
        pu3 = cL4_alloc(8, 0x50c40ee9192b6);
        pc5 = (char *)s_Tried_to_build_an_existential_me_005d5c14;
    }
    *pu3 = (unsigned long)pc5;
    *out = (long)pu3;
    thunk_FUN_00012568(u2, 8);
}

/* FUN_003952c4 @ 0x3952c4   (est. sk_type_build_func)
 * Ghidra: void FUN_003952c4(long *param_1, long *param_2, ulong *param_3, ulong param_4)
 * Builds an extended-existential type: unwraps the signature (kind 0x160 via
 * FUN_00375420 or 0x15f direct), checks the argument count matches, then
 * materializes each generic arg (validating it's a metadata pack via
 * FUN_00363f10 / the type-list materializer FUN_0039a6fc) and builds the
 * final type via FUN_00375934.
 * Confidence: medium
 * Notes: "Length mismatch building an extended existential" on count
 *   mismatch; canary -0x2c8502b44bfffed6. */
void sk_type_build_func_3952c4(long *out, long *sig, unsigned long *args, unsigned long n)
{
    unsigned long u1; unsigned long *pu2; long l3, l4; unsigned long *pu5;
    long canary; long lvar; unsigned long lc; unsigned long res; unsigned short l140;

    canary = -0x2c8502b44bfffed6;
    l3 = ((short)sig[2] == 0x160) ? FUN_00375420(*sig) : ((short)sig[2] == 0x15f) ? *sig : -1;
    if (l3 == -1) {
        u1 = (unsigned long)cL4_alloc(8, 0x50c40ee9192b6);
        *(unsigned short *)(out + 2) = 1;
        out[1] = (long)FUN_00398074;
        pu2 = cL4_alloc(8, 0x50c40ee9192b6);
        *pu2 = (unsigned long)s_Tried_to_build_an_extended_exist_005d5c83;
        *out = (long)pu2;
        if (canary == -0x2c8502b44bfffed6) { thunk_FUN_00012568(u1, 8); return; }
        goto lb_95634;
    }
    l4 = l3;
    if (l3 == 0) l4 = 0;
    FUN_0037de18(&l140, l4);
    if (n == l140) {
        unsigned long *lc; unsigned long *ae, *be, *ce;
        lc = (unsigned long *)&DAT_004f2710;
        if (n == 0) {
            l140 = 0;
        } else {
            l4 = n << 3;
            pu5 = args;
            do {
                if (*pu5 == 0 || (*pu5 & 1) != 0)
                    FUN_00369bb0(0, (unsigned long)s_Expected_metadata_but_got_a_meta_005d40ee);
                cL4_list_push_363f10((long *)&lc);
                l4 -= 8;
                pu5++;
            } while (l4 != 0);
        }
        {
            unsigned long t1, t2, t3, t4;
            unsigned long resv;
            t1 = 0x67bac8; t2 = 0x67bb10; t3 = 0x67bb58; t4 = 0;
            FUN_0039a6fc(&lvar, (unsigned long)lc, l140, l140, l140 & 0xffff,
                         (unsigned long)&t1, (unsigned long)&t2, (unsigned long)&t3, 0, 0);
            resv = (unsigned long)lvar;
            res = (resv & 1) == 0 ? 0 : 1;
            FUN_0036805c(&t3);
            FUN_003680cc(&t2);
            FUN_003680cc(&t1);
            if (res == 0) {
                l3 = FUN_00375934(l3, (unsigned long)lc);
                *(unsigned short *)(out + 2) = 0;
                *out = l3;
                if (l3 == 0) {
                    *out = (long)s_unknown_error_005d5481;
                    out[1] = (long)FUN_0037f9f4;
                    *(unsigned short *)(out + 2) = 1;
                }
            } else {
                *(unsigned short *)(out + 2) = 1;
                out[1] = (long)FUN_00398074;
                *out = (long)s_unknown_error_005d5481;
            }
        }
        ;
    } else {
        u1 = (unsigned long)cL4_alloc(8, 0x50c40ee9192b6);
        *(unsigned short *)(out + 2) = 1;
        out[1] = (long)FUN_00398074;
        pu2 = cL4_alloc(8, 0x50c40ee9192b6);
        *pu2 = (unsigned long)s_Length_mismatch_building_an_exte_005d5cd1;
        *out = (long)pu2;
        thunk_FUN_00012568(u1, 8);
    }
    if (canary != -0x2c8502b44bfffed6) return;
lb_95634:
    cL4_stack_fail();
}

/* FUN_00395638 @ 0x395638   (est. sk_type_parse_signature)
 * Ghidra: long FUN_00395638(undefined8 *param_1, long *param_2, uint param_3)
 * Parses a generic signature: recursively unwraps the signature node (kinds
 * 0xbf/0xc0/0x16b), looks up the bound-generic type in the two-tier cache
 * (DAT_006c0988 / DAT_006c09e0 with lock-objects _DAT_006c0980/_DAT_006c09d8
 * and the DAT_006c09a0 mutex), inserting it if missing, and returns the type
 * metadata. Depth-bounded by param_3.
 * Confidence: low
 * Notes: shared-cache logic mirrors sk_type_cache_lookup_388630; the 
 *   SoftwareBreakpoint fatal at 0x395ddc on alloc failure. */
long sk_type_parse_signature_395638(unsigned long *ctx, long *node, unsigned int depth)
{
    unsigned int u10; unsigned char b9; long l27; unsigned long u18;
    long *pl26; long *pl4; long canary2; long found;
    unsigned long v, n; unsigned long *cache; cL4_w16_t vb;

    if (depth < 0x401) {
        int i16 = depth - 0x401;
        do {
            u10 = *(unsigned short *)(node + 2);
            b9 = *(unsigned char *)((long)node + 0x12);
            if (u10 != 0xf4) {
                if (b9 == 2) {
                    if (1 < u10 - 0xbf) { if (u10 != 0x16b) return 0; }
                } else if (b9 == 5) {
                    if ((*(unsigned int *)(node + 1) < 2 || u10 != 0xbf) && (u10 != 0xc0)) {
                        if (u10 != 0x16b) return 0;
                    }
                } else if ((u10 != 0x16b) && (u10 != 0xc0)) return 0;
                pl26 = node;
                if ((short)node[2] == 0xf4) {
                    if (1 < *(unsigned char *)((long)node + 0x12) - 1) {
                        if ((*(unsigned char *)((long)node + 0x12) != 5) || ((int)node[1] == 0)) {
                            pl26 = 0; goto lb_957ac;
                        }
                        pl26 = (long *)*node;
                    }
                    pl26 = (long *)*pl26;
                }
lb_957ac:
                if ((short)pl26[2] == 0xc0) {
                    l27 = *pl26;
                    if (l27 == 0) return 0;
                } else {
                    long local_c8[6]; unsigned long *ctx2 = ctx;
                    FUN_003c3008(local_c8, (unsigned long)node, (unsigned long)&DAT_0036e518, (unsigned long)&ctx2, (unsigned long)ctx, 0);
                    if (local_c8[0] != 0) return 0;
                    /* cache lookup via waiter_scan on _DAT_006c0988 */
                    LOAcquire();
                    _DAT_006c0980 = _DAT_006c0980 + 1;
                    if (((_DAT_006c0988 != 0 && _DAT_006c0990 != 0) && _DAT_006c0984 != 0) &&
                        (found = (long)FUN_00398474(&ctx2, _DAT_006c0990,
                                                    CONCAT44(0, _DAT_006c0984),
                                                    (unsigned long *)((long)_DAT_006c0988 + 2)), found != 0)) {
                        _DAT_006c0980 = _DAT_006c0980 - 1;
                        LORelease();
                        return *(long *)(found + 0x10);
                    }
                    _DAT_006c0980 = _DAT_006c0980 - 1;
                    LORelease();
                    LOAcquire();
                    _DAT_006c09d8 = _DAT_006c09d8 + 1;
                    if ((_DAT_006c09e0 != 0) && (*_DAT_006c09e0 != 0)) {
                        pl26 = (long *)(_DAT_006c09e0 + 1);
                        pl4 = pl26 + *_DAT_006c09e0 * 2;
                        do {
                            for (l27 = *pl26; l27 != pl26[1]; l27 += 4) {
                                u18 = FUN_003987e0(l27);
                                if ((u18 != 0) && (FUN_00387fbc(u18, (unsigned long)node) & 1)) {
                                    _DAT_006c09d8 = _DAT_006c09d8 - 1;
                                    LORelease();
                                    /* insert into first-tier cache under DAT_006c09a0 mutex */
                                    {
                                        FUN_00118148(0x6c09a0, 0);
                                        FUN_00118164(0x6c09a0);
                                        /* (insertion simplified: store found at end) */
                                        FUN_0035b228(&ctx2);
                                    }
                                    return l27;
                                }
                            }
                            pl26 += 2;
                        } while (pl26 != pl4);
                    }
                    found = 0;
                    _DAT_006c09d8 = _DAT_006c09d8 - 1;
                    LORelease();
                    return 0;
                }
                if (l27 == 0) return 0;
                return l27;
            }
            if (b9 - 1 < 2) {
            lb_9569c:
                node = (long *)*node;
            } else {
                if ((b9 == 5) && ((int)node[1] != 0)) { node = (long *)*node; goto lb_9569c; }
                node = 0;
            }
            i16 = i16 + 1;
        } while (i16 != -1);
    }
    return 0;
}

/* FUN_00395dec @ 0x395dec   (est. sk_type_build_owned)
 * Ghidra: void FUN_00395dec(long *param_1, ulong *param_2, long param_3, ulong param_4, ulong param_5)
 * Builds a protocol-composition type: validates that the witness flags
 * (param_5) are even and there are no owned generic args (param_4==0), then
 * materializes via FUN_00374e88. "Tried to build a protocol composition"
 * error if param_4 is odd.
 * Confidence: medium */
void sk_type_build_owned_395dec(long *out, unsigned long *m, long n, unsigned long a, unsigned long b)
{
    unsigned int u1; unsigned long u2; unsigned long *pu3; long l4; unsigned long *pu5;
    unsigned int *pu6; long lv;

    u1 = 0;
    if (((b & 1) == 0) && (a == 0)) {
        if (n == 0) { u1 = 1; goto lb_95e70; }
        lv = n * 8;
        pu5 = m;
        do {
            lv -= 8;
            pu6 = (unsigned int *)(*pu5 & 0xfffffffffffffffe);
            if (pu6 == 0) pu6 = 0;
            u1 = *pu6 >> 0x10 & 1;
        } while (((*pu6 >> 0x10 & 1) != 0) && (pu5++, lv != 0));
    }
    if ((a & 1) != 0) {
        u2 = (unsigned long)cL4_alloc(8, 0x50c40ee9192b6);
        *(unsigned short *)(out + 2) = 1;
        out[1] = (long)FUN_00398074;
        pu3 = cL4_alloc(8, 0x50c40ee9192b6);
        *pu3 = (unsigned long)s_Tried_to_build_a_protocol_compos_005d5d0b;
        *out = (long)pu3;
        thunk_FUN_00012568(u2, 8);
        return;
    }
lb_95e70:
    l4 = FUN_00374e88(u1, a, n, m);
    *(unsigned short *)(out + 2) = 0;
    *out = l4;
    if (l4 == 0) {
        *out = (long)s_unknown_error_005d5481;
        out[1] = (long)FUN_0037f9f4;
        *(unsigned short *)(out + 2) = 1;
    }
}

/* FUN_00395f3c @ 0x395f3c   (est. sk_type_build_sig)
 * Ghidra: void FUN_00395f3c(long *param_1, undefined8 param_2, long *param_3, undefined8 param_4)
 * Builds a generic signature requirement list: walks the signature node's
 * child requirement nodes (kinds 0x26/0x2b/0x174 etc.), resolves each
 * referenced type metadata via FUN_00398834, computes the requirement flags,
 * and appends {metadata, flags} pairs to the requirement vector param_3.
 * Confidence: low
 * Notes: complex kind-flag (0x2a/0x28/0x25/0x67) classification for
 *   associated-type witnesses. */
void sk_type_build_sig_395f3c(long *out, unsigned long a, long *reqs, unsigned long b)
{
    long *node; unsigned long *elems; long lc, l8;
    unsigned long u9, u10; long req;
    unsigned char *pbb; unsigned int wn; unsigned long cap; long idx;

    node = out;
    idx = 0;
    while (1) {
        if (idx >= (long)*(unsigned int *)(out + 1)) return;
        elems = (unsigned long *)*out;
        node = (long *)((long)elems + idx * 8);
        if (*(short *)(node + 2) == 0x26 || *(short *)(node + 2) == 0x2b || *(short *)(node + 2) == 0x174) {
            unsigned long tmeta;
            if (*(char *)((long)node + 0x12) == '\x02') {
                tmeta = *(unsigned long *)((long)node + 8);
            } else if ((*(char *)((long)node + 0x12) == '\x05') && (1 < *(unsigned int *)(node + 1))) {
                node = (long *)*node;
                tmeta = *(unsigned long *)((long)node + 8);
            } else tmeta = 0;
            req = FUN_00398834(b, tmeta, 1);
            if (req == 0) return;
            /* append {metadata, kind} pair */
            cap = (unsigned long)*(unsigned int *)(reqs + 1);
            if (*(unsigned int *)((long)reqs + 0xc) <= cap) {
                cL4_wordlist_grow((unsigned long *)reqs, (unsigned long *)(reqs + 2), cap + 1, 0x10);
                cap = (unsigned long)*(unsigned int *)(reqs + 1);
            }
            {
                unsigned long *dst = (unsigned long *)(*reqs + cap * 0x10);
                dst[0] = (unsigned long)req;
                dst[1] = 0;
                *(int *)(reqs + 1) = (int)reqs[1] + 1;
            }
        }
        idx++;
    }
}

/* FUN_003963b8 @ 0x3963b8   (est. sk_type_metadata_get)
 * Ghidra: ulong FUN_003963b8(long param_1)
 * Returns the pack element's type metadata from a metadata pack (param_1):
 * if the pack at +0x20 is nonempty, looks up the pack index via
 * FUN_00398964, bounds-checks against the pack length
 * (sk_pack_length_38d8dc), and returns the indexed metadata. Fatal
 * "Pack index %zu exceeds pack length" on overflow.
 * Confidence: medium */
unsigned long sk_type_metadata_get_3963b8(long p)
{
    unsigned long u1; unsigned long l28;
    if (*(long *)(p + 0x20) == 0) return 0;
    l28 = FUN_00398964(p + 8);
    if ((*(long *)(p + 0x50) != *(long *)(p + 0x58)) && ((l28 & 1) != 0)) {
        u1 = *(unsigned long *)(*(long *)(p + 0x58) + -8);
        if (*(unsigned long *)((l28 & 0xfffffffffffffffe) - 8) <= u1) {
            sk_pack_length_38d8dc(&l28);
            FUN_00369bb0(0, (unsigned long)s_Pack_index__zu_exceeds_pack_leng_005d5d55);
        }
        l28 = *(unsigned long *)((l28 & 0xfffffffffffffffe) + u1 * 8);
    }
    return l28;
}

/* FUN_00396440 @ 0x396440   (est. sk_type_generic_args)
 * Ghidra: void FUN_00396440(undefined8 *param_1, undefined8 param_2, undefined8 *param_3, uint param_4, undefined8 param_5, undefined1 *param_6)
 * Decodes a generic-argument list node (param_3) into a metadata pack.
 * Walks the child argument nodes (relative-offset list), recursing via
 * FUN_00398a70 for dependent/parameter nodes (kind 0xeb) and materializing
 * each via the type-list decoder, tracking a flags byte (param_6). Depth
 * bounded by param_4.
 * Confidence: low
 * Notes: node kind 0xeb = generic parameter; canary not used here. */
void sk_type_generic_args_396440(unsigned long *out, unsigned long a, unsigned long *node,
                                 unsigned int depth, unsigned long b, unsigned char *flag)
{
    unsigned long *pu5, *pu9; unsigned char b2; unsigned long u4; long canary;
    long lv; unsigned long res; unsigned int flags;

    if (depth < 0x401) {
        unsigned int d4 = depth;
        do {
            short s3 = *(short *)(node + 2);
            if (s3 != 0xf4 && s3 != 3) {
                unsigned long ctx[4]; unsigned long l70, l60, l58;
                if (s3 != 0xeb) {
                    FUN_00398a70(&res, &ctx, (unsigned long)node, &l70);
                    if ((*flag & 1) == 0) *(unsigned char *)out = 0;
                    else {
                        out[1] = *(unsigned long *)&FUN_00398074;
                        *out = (unsigned long)res;
                        *(unsigned char *)(out + 2) = !(*flag & 1) ^ 1;
                    }
                    return;
                }
                b2 = *(unsigned char *)((long)node + 0x12);
                pu9 = node;
                if (b2 - 1 < 2) {
                    if (b2 == 1) pu5 = node + 1;
                    else if (b2 == 2) pu5 = node + 2;
                    else if (b2 == 5) pu5 = (unsigned long *)*node;
                    else pu5 = 0;
                } else {
                    if (b2 != 5) { pu9 = 0; goto chk; }
                    pu5 = (unsigned long *)*node; pu9 = pu5;
                }
                pu5 = pu5 + *(unsigned int *)(node + 1);
chk:
                if (pu9 == pu5) { *(unsigned char *)out = 0; *(unsigned char *)(out + 2) = 0; return; }
                {
                    unsigned long *el = (unsigned long *)*pu9;
                    short s4 = *(short *)(el + 2);
                    if (s4 == 0xec) {
                        /* element is a dependent generic parameter: skip */
                        ;
                    } else if (s4 == 0xf4) {
                        unsigned long child = *el;
                        FUN_00398a70(&res, &ctx, child, &l70);
                        if ((*flag & 1) != 0) {
                            out[1] = *(unsigned long *)&FUN_00398074;
                            *out = (unsigned long)res;
                            *(unsigned char *)(out + 2) = 1;
                            return;
                        }
                    } else if (s4 == 0xed) {
                        /* generic parameter pack: record */
                        flags = 0;
                    } else {
                        unsigned long *pu7 = cL4_alloc(8, 0x50c40ee9192b6);
                        *pu7 = (unsigned long)s_unknown_node_005d5d7d;
                        out[1] = (unsigned long)FUN_00398074;
                        *out = (unsigned long)pu7;
                        *(unsigned char *)(out + 2) = 1;
                        return;
                    }
                }
                pu9 += 1;
                goto chk;
            }
            if (*(unsigned char *)((long)node + 0x12) - 1 < 2) {
            gi_964a4:
                node = (unsigned long *)*node;
            } else {
                if ((*(unsigned char *)((long)node + 0x12) == 5) && (*(int *)(node + 1) != 0)) {
                    node = (unsigned long *)*node; goto gi_964a4;
                }
                node = 0;
            }
            d4 = d4 + 1;
        } while (d4 != 0x401);
    }
    *(unsigned char *)out = 0;
    *(unsigned char *)(out + 2) = 0;
}

/* FUN_00396784 @ 0x396784   (est. sk_type_build_bound_generic)
 * Ghidra: void FUN_00396784(long *param_1, long param_2, ulong param_3, ulong param_4, ulong param_5, undefined8 param_6, undefined8 param_7, ulong param_8, ulong param_9)
 * Builds a bound-generic function type: validates the generic argument
 * metadata pack (param_4), gathers each argument into a word list
 * (cL4_list_push_363f10), and materializes the function type via
 * FUN_00370dfc. "Tried to build a function type with ..." error descriptors
 * on malformed arguments.
 * Confidence: low
 * Notes: canary -0x2c8502b44bfffed6. */
void sk_type_build_bound_generic_396784(long *out, long sig, unsigned long a, unsigned long b,
                                        unsigned long c, unsigned long d, unsigned long e,
                                        unsigned long f, unsigned long g)
{
    unsigned long u2; unsigned long *pu3; char *pc4; long l5; unsigned int u6;
    unsigned long u7; long canary; long lc[8];
    unsigned long *words; unsigned long *flags; unsigned long res;

    canary = -0x2c8502b44bfffed6;
    if ((b == 0) || ((b & 1) != 0)) {
        u2 = (unsigned long)cL4_alloc(8, 0x50c40ee9192b6);
        *(unsigned short *)(out + 2) = 1;
        out[1] = (long)FUN_00398074;
        pu3 = cL4_alloc(8, 0x50c40ee9192b6);
        *pu3 = (unsigned long)s_Tried_to_build_a_function_type_w_005d5e1c;
        *out = (long)pu3;
        if (canary == -0x2c8502b44bfffed6) { thunk_FUN_00012568(u2, 8); return; }
        goto lb_96ad8;
    }
    words = (unsigned long *)&DAT_004f2710;
    flags = (unsigned long *)&DAT_004f2710;
    if (a < 9) {
        if (a != 0) u6 = (unsigned int)(c >> 0x19) & 1;
    } else {
        cL4_wordlist_grow((unsigned long *)words, (unsigned long *)&flags, a, 8);
        u6 = (unsigned int)(c >> 0x19) & 1;
        if ((((unsigned int)c >> 0x19 & 1) != 0) && ((unsigned long)&DAT_004f2710 >> 0x20 < a))
            cL4_wordlist_grow((unsigned long *)flags, (unsigned long *)&words, a, 4);
        {
            long l5v = a << 5;
            unsigned int *p8 = (unsigned int *)(sig + 0x18);
            do {
                if (*(unsigned long *)(p8 + -2) == 0 || (*(unsigned long *)(p8 + -2) & 1) != 0) {
                    u2 = (unsigned long)cL4_alloc(8, 0x50c40ee9192b6);
                    *(unsigned short *)(out + 2) = 1;
                    out[1] = (long)FUN_00398074;
                    pu3 = cL4_alloc(8, 0x50c40ee9192b6);
                    pc4 = (char *)s_Tried_to_build_a_function_type_w_005d5e5b;
                    *pu3 = (unsigned long)pc4;
                    *out = (long)pu3;
                    thunk_FUN_00012568(u2, 8);
                    goto lb_96a6c;
                }
                cL4_list_push_363f10((long *)words);
                if (u6 != 0) sk_wordlist_append_389370((long *)flags, *p8);
                p8 += 8;
                l5v -= 0x20;
            } while (l5v != 0);
        }
    }
    u7 = c;
    if (f == 0) {
        if ((g & 1) != 0) FUN_00369bb0(0, (unsigned long)s_Expected_metadata_but_got_a_meta_005d40ee);
        l5 = FUN_00370dfc(u7, e, (unsigned long)words, 0, b, f, d, g);
        *(unsigned short *)(out + 2) = 0;
        *out = l5;
        if (l5 == 0) {
            *out = (long)s_unknown_error_005d5481;
            out[1] = (long)FUN_0037f9f4;
            *(unsigned short *)(out + 2) = 1;
        }
    } else {
        if ((f & 1) == 0) {
            u7 = c | 0x10000000;
            if ((g & 1) != 0) FUN_00369bb0(0, (unsigned long)s_Expected_metadata_but_got_a_meta_005d40ee);
            l5 = FUN_00370dfc(u7, e, (unsigned long)words, 0, b, f, d, g);
            *(unsigned short *)(out + 2) = 0;
            *out = l5;
            if (l5 == 0) { *out = (long)s_unknown_error_005d5481; out[1] = (long)FUN_0037f9f4; *(unsigned short *)(out + 2) = 1; }
        } else {
            u2 = (unsigned long)cL4_alloc(8, 0x50c40ee9192b6);
            *(unsigned short *)(out + 2) = 1;
            out[1] = (long)FUN_00398074;
            pu3 = cL4_alloc(8, 0x50c40ee9192b6);
            *pu3 = (unsigned long)s_Tried_to_build_a_function_type_w_005d5e9b;
            *out = (long)pu3;
            thunk_FUN_00012568(u2, 8);
        }
    }
lb_96a6c:
    if (canary != -0x2c8502b44bfffed6) return;
lb_96ad8:
    cL4_stack_fail();
}

/* FUN_00396aec @ 0x396aec   (est. sk_type_decode_param)
 * Ghidra: long FUN_00396aec(undefined8 param_1, undefined8 *param_2, uint param_3, undefined8 param_4)
 * Decodes a function parameter list node: validates it wraps a 0x6c
 * coroutine-kind node with 0xf4 result child, computes the parameter-kinds
 * word (FUN_00399108), recursively decodes the result type, and ORs the
 * per-argument kind flags (0x70/0x71/0x72/0x73) into a mask reported through
 * FUN_00399390. Returns 1 on success, 0 on decode failure.
 * Confidence: low
 * Notes: canary -0x2c8502b44bfffed6. */
long sk_type_decode_param_396aec(unsigned long a, unsigned long *node, unsigned int depth, unsigned long b)
{
    unsigned char b1; unsigned short u2; unsigned int u3; unsigned long u4, u5;
    unsigned long *pu6, *pu7; unsigned long u8; long l9, l11; long canary;
    unsigned long l60; unsigned long res; unsigned short kind; long r;
    unsigned int mask; unsigned long n;

    canary = -0x2c8502b44bfffed6;
    if (depth < 0x401) {
        l9 = 1;
        pu6 = node;
        if (*(char *)((long)node + 0x12) != '\x02') {
            if (*(char *)((long)node + 0x12) != '\x05') goto lb_96b24;
            if (*(unsigned int *)(node + 1) < 2) goto lb_96b20;
            l9 = (unsigned long)*(unsigned int *)(node + 1) - 1;
            pu6 = (unsigned long *)*node;
        }
        pu7 = (unsigned long *)*pu6;
        if ((*(short *)(pu7 + 2) == 0x6c) && (l11 = (long)pu6[l9], *(short *)(l11 + 0x10) == 0xf4)) {
            u4 = FUN_00399108(*pu7, pu7[1]);
            mask = (unsigned int)u4;
            l9 = 1;
            if ((u4 >> 0x20 & 1) == 0) goto lb_96b24;
            sk_type_decode_38f0a8(&res, (unsigned long *)a, (unsigned long)l11, depth + 1, 1);
            if (res != 1) {
                unsigned int f = 0;
                n = 1;
                do {
                    b1 = *(unsigned char *)((long)node + 0x12);
                    u5 = (unsigned long)b1;
                    u3 = (unsigned int)b1;
                    if (b1 != 2) {
                        if (b1 == 5) { u8 = (unsigned long)*(unsigned int *)(node + 1) - 1; goto c3c; }
                        if (u3 != 1) goto c84;
                        goto cec;
                    }
                    u8 = 1;
c3c:
                    if (u8 <= n) goto cec;
                    if (u3 != 2) {
                        if (u3 != 5) goto c84;
                        u5 = (unsigned long)*(unsigned int *)(node + 1);
                    }
                    if (n < u5) {
                        pu6 = node;
                        if (1 < u3 - 1) pu6 = (unsigned long *)*node;
                        pu6 = (unsigned long *)pu6[n];
                    } else { c84: pu6 = 0; }
                    u2 = *(unsigned short *)(pu6 + 2);
                    if (u2 == 0x70) {
                        u3 = FUN_0039932c(*pu6, pu6[1]);
                        if ((u3 >> 8 & 1) == 0) goto d3c;
                    } else if (u2 == 0x71) u3 = 2;
                    else if (u2 == 0x72) u3 = 4;
                    else if (u2 == 0x73) u3 = 8;
                    else goto d18;
                    f |= u3;
                    n++;
                } while (1);
cec:
                {
                    unsigned long lv = res;
                    if (res != 0) lv = 0;
                    FUN_00399390(b, &lv, &mask, &f);
                    l9 = 0;
                    goto d18;
                }
d3c:
                l9 = 1;
d18:
                if (res != 1) goto lb_96b24;
            }
            goto lb_96d24;
        }
    }
lb_96b20:
    l9 = 1;
    goto lb_96b24;
lb_96d24:
    ;
lb_96b24:
    if (canary != -0x2c8502b44bfffed6) cL4_stack_fail();
    return l9;
}

/* FUN_00396d48 @ 0x396d48   (est. sk_type_decode_result)
 * Ghidra: long FUN_00396d48(undefined8 param_1, undefined8 *param_2, uint param_3, undefined8 param_4)
 * Mirror of sk_type_decode_param_396aec for a function result list: validates
 * the 0x6c/0xf4 wrapper, computes result-kinds (FUN_00399414), decodes the
 * result type and ORs per-argument kind flags (0x70/0x71) via FUN_00399390.
 * Returns 1 on success.
 * Confidence: low
 * Notes: canary -0x2c8502b44bfffed6. */
long sk_type_decode_result_396d48(unsigned long a, unsigned long *node, unsigned int depth, unsigned long b)
{
    unsigned char b1; unsigned int u2; unsigned long u3, u4; unsigned long *pu5, *pu6;
    unsigned long u7; unsigned int u8; long l9, l10; long canary; unsigned long res;
    unsigned long l60; unsigned short kind; unsigned int mask; unsigned long n;

    canary = -0x2c8502b44bfffed6;
    if (depth < 0x401) {
        l9 = 1;
        pu5 = node;
        if (*(char *)((long)node + 0x12) != '\x02') {
            if (*(char *)((long)node + 0x12) != '\x05') goto lb_96d80;
            if (*(unsigned int *)(node + 1) < 2) goto lb_96d7c;
            l9 = (unsigned long)*(unsigned int *)(node + 1) - 1;
            pu5 = (unsigned long *)*node;
        }
        pu6 = (unsigned long *)*pu5;
        if ((*(short *)(pu6 + 2) == 0x6c) && (l10 = (long)pu5[l9], *(short *)(l10 + 0x10) == 0xf4)) {
            u3 = FUN_00399414(*pu6, pu6[1]);
            mask = (unsigned int)u3;
            l9 = 1;
            if ((u3 >> 0x20 & 1) == 0) goto lb_96d80;
            sk_type_decode_38f0a8(&res, (unsigned long *)a, (unsigned long)l10, depth + 1, 1);
            if (res != 1) {
                unsigned int f = 0;
                n = 1;
                do {
                    b1 = *(unsigned char *)((long)node + 0x12);
                    u4 = (unsigned long)b1;
                    u2 = (unsigned int)b1;
                    if (b1 == 2) { u7 = 1; goto e98; }
                    if (b1 == 5) { u7 = (unsigned long)*(unsigned int *)(node + 1) - 1; goto e98; }
                    if (u2 == 1) goto f1c;
                    goto ee0;
e98:
                    if (u7 <= n) goto f1c;
                    if (u2 != 2) {
                        if (u2 != 5) goto ee0;
                        u4 = (unsigned long)*(unsigned int *)(node + 1);
                    }
                    if (u4 <= n) goto ee0;
                    pu5 = node;
                    if (1 < u2 - 1) pu5 = (unsigned long *)*node;
                    pu5 = (unsigned long *)pu5[n];
ee0:
                    if (*(short *)(pu5 + 2) == 0x71) u2 = 2;
                    else if ((*(short *)(pu5 + 2) == 0x70) &&
                             (u2 = FUN_0039932c(*pu5, pu5[1]), (u2 >> 8 & 1) != 0)) goto f4c;
                    else goto f4c;
                    f |= u2;
                    n++;
                } while (1);
f1c:
                {
                    unsigned long lv = res;
                    if (res != 0) lv = 0;
                    FUN_00399390(b, &lv, &mask, &f);
                    l9 = 0;
                    goto f50;
                }
f4c:
                l9 = 1;
f50:
                if (res != 1) goto lb_96d80;
            }
            goto lb_96f5c;
        }
    }
lb_96d7c:
    l9 = 1;
    goto lb_96d80;
lb_96f5c:
    ;
lb_96d80:
    if (canary != -0x2c8502b44bfffed6) cL4_stack_fail();
    return l9;
}

/* FUN_00396f78 @ 0x396f78   (est. sk_type_build_reqlist)
 * Ghidra: void FUN_00396f78(ulong *param_1, ulong *param_2, ulong param_3, long param_4, ulong param_5)
 * Builds a tuple type from a metadata-pack list (param_2, param_3 entries):
 * validates each element is a metadata pack, optionally assembles a string of
 * the element flags via FUN_00112c38/FUN_00112e8c/FUN_001130a0, and
 * materializes via FUN_00371950.
 * Confidence: low
 * Notes: "Tried to build a tuple type where ..." error. */
void sk_type_build_reqlist_396f78(unsigned long *out, unsigned long *m, unsigned long n, long reqs, unsigned long a)
{
    unsigned long u1; unsigned long *pu2; unsigned long **pu3; unsigned long *pu4;
    unsigned int u5; unsigned long *pu6; long l8; unsigned long u9, u10;
    unsigned long canary2; unsigned long sbuf; unsigned long str; unsigned char s7;
    unsigned long *pu7; unsigned long res;

    pu6 = m;
    if (n == 1) {
        if (*(long *)(reqs + 8) == 0) {
            *(unsigned short *)(out + 2) = 0;
            u10 = *m;
            *out = u10;
            if (u10 != 0) return;
            *out = (unsigned long)s_unknown_error_005d5481;
            out[1] = (unsigned long)FUN_0037f9f4;
            *(unsigned short *)(out + 2) = 1;
            return;
        }
        pu4 = m + 1;
    } else {
        if (n == 0) goto lb_96fec;
        pu4 = m + n;
    }
    do {
        pu7 = pu6 + 1;
        if (*pu6 == 0 || (*pu6 & 1) != 0) {
            u9 = (unsigned long)cL4_alloc(8, 0x50c40ee9192b6);
            *(unsigned short *)(out + 2) = 1;
            out[1] = (unsigned long)FUN_00398074;
            pu2 = cL4_alloc(8, 0x50c40ee9192b6);
            *pu2 = (unsigned long)s_Tried_to_build_a_tuple_type_wher_005d5f9f;
            *out = (unsigned long)pu2;
            thunk_FUN_00012568(u9, 8);
            return;
        }
        pu6 = pu7;
    } while (pu7 != pu4);
lb_96fec:
    sbuf = 0; str = 0; s7 = 0;
    if (a != 0) {
        u10 = 0;
        do {
            pu2 = (unsigned long *)(reqs + (u10 & 0xffffffff) * 0x10);
            l8 = pu2[1];
            u1 = 0;
            if (l8 == 0) { ; }
            else {
                u9 = *pu2;
                FUN_00112c38(&sbuf, u10 & 0xffffffff, 0x20);
                FUN_00112e8c((unsigned long)&sbuf, u9, l8);
                FUN_001130a0(&sbuf, 0x20);
            }
            u10++;
        } while (a != u10);
        u5 = (unsigned int)(s7);
    }
    u10 = 0;
    if (u10 != 0) u10 = (unsigned long)u5;
    {
        unsigned long f = n & 0xffffffff;
        if (u10 != 0) f = n & 0xffffffff | 0x10000;
        res = FUN_00371950(0xff, f, m, 0, 0);
        *(unsigned short *)(out + 2) = 0;
        *out = res;
        if (res == 0) {
            *out = (unsigned long)s_unknown_error_005d5481;
            out[1] = (unsigned long)FUN_0037f9f4;
            *(unsigned short *)(out + 2) = 1;
        }
    }
    if ((long)str < 0) thunk_FUN_00012568(sbuf, str & 0x7fffffffffffffff);
}

/* FUN_003971e8 @ 0x3971e8   (est. sk_type_materialize_req2)
 * Ghidra: void FUN_003971e8(ulong *param_1, ulong *param_2, long param_3)
 * Materializes a metadata pack for a requirement list: validates each element
 * (param_2, param_3 entries) is a metadata pack, then builds the on-stack
 * pack via FUN_0036e878. Fatal "Cannot have an on-stack pack here" on
 * failure.
 * Confidence: medium */
void sk_type_materialize_req2_3971e8(unsigned long *out, unsigned long *m, long n)
{
    unsigned long u1; unsigned long u2; unsigned long *pu3;
    if (n != 0) {
        n = n << 3;
        do {
            if (*m == 0 || (*m & 1) != 0) {
                u2 = (unsigned long)cL4_alloc(8, 0x50c40ee9192b6);
                *(unsigned short *)(out + 2) = 1;
                out[1] = (unsigned long)FUN_00398074;
                pu3 = cL4_alloc(8, 0x50c40ee9192b6);
                *pu3 = (unsigned long)s_Can_t_have_nested_metadata_packs_005d5fdb;
                *out = (unsigned long)pu3;
                thunk_FUN_00012568(u2, 8);
                return;
            }
            n -= 8;
            m++;
        } while (n != 0);
    }
    u1 = cL4_pack_build(0);
    if ((u1 & 1) != 0) {
        *(unsigned short *)(out + 2) = 0;
        *out = u1;
        return;
    }
    FUN_00369bb0(0, (unsigned long)s_Cannot_have_an_on_stack_pack_her_005d5ffc);
}

/* FUN_003972cc @ 0x3972cc   (est. sk_type_materialize_req)
 * Ghidra: void FUN_003972cc(undefined8 *param_1)
 * Reports the "Lowered SILPackType cannot be decoded" error descriptor.
 * Confidence: high (string-matched) */
void sk_type_materialize_req_3972cc(unsigned long *out)
{
    unsigned long u1; unsigned long *pu2;
    u1 = (unsigned long)cL4_alloc(8, 0x50c40ee9192b6);
    *(unsigned short *)(out + 2) = 1;
    out[1] = (unsigned long)FUN_00398074;
    pu2 = cL4_alloc(8, 0x50c40ee9192b6);
    *pu2 = (unsigned long)s_Lowered_SILPackType_cannot_be_de_005d601f;
    *out = (unsigned long)pu2;
    thunk_FUN_00012568(u1, 8);
}

/* FUN_00397358 @ 0x397358   (est. sk_type_materialize)
 * Ghidra: void FUN_00397358(undefined8 *param_1)
 * Reports the "Unbound dependent member type cannot be decoded" error
 * descriptor.
 * Confidence: high (string-matched) */
void sk_type_materialize_397358(unsigned long *out)
{
    unsigned long u1; unsigned long *pu2;
    u1 = (unsigned long)cL4_alloc(8, 0x50c40ee9192b6);
    *(unsigned short *)(out + 2) = 1;
    out[1] = (unsigned long)FUN_00398074;
    pu2 = cL4_alloc(8, 0x50c40ee9192b6);
    *pu2 = (unsigned long)s_Unbound_dependent_member_type_ca_005d6047;
    *out = (unsigned long)pu2;
    thunk_FUN_00012568(u1, 8);
}

/* FUN_003973e4 @ 0x3973e4   (est. sk_type_build_protocol)
 * Ghidra: void FUN_003973e4(long *param_1, undefined8 param_2, ulong param_3, ulong param_4, ulong param_5)
 * Builds a protocol-conformance record: walks the demangle tree (param_5, a
 * protocol list) looking for the protocol matching param_3 (name/string
 * match via FUN_001144a0/FUN_001145b0), then materializes the conformance
 * witness for each protocol component (FUN_0039c740 + FUN_00377824),
 * producing the final metadata via FUN_0036e878. Falls to "unknown error" if
 * no match. A SoftwareBreakpoint at 0x3975e4 guards the walk.
 * Confidence: low
 * Notes: canary -0x2c8502b44bfffed6. */
void sk_type_build_protocol_3973e4(long *out, unsigned long a, unsigned long b, unsigned long c, unsigned long d)
{
    unsigned long u5, u1, u2, u8; long l6, l7; int i4, i12; long canary;
    long local_98; unsigned long local_90; unsigned long *pu11; long res;
    unsigned long proto; unsigned long plist; unsigned long *pc; unsigned long u9; unsigned long matches;

    canary = -0x2c8502b44bfffed6;
    d = d & 0xfffffffffffffffe;
    if (d == 0) d = 0;
    i12 = *(int *)(d + 0x14);
    l7 = (long)(d + 0x14) + (long)i12;
    if ((i12 != 0 && l7 != 0) && (u5 = FUN_00115080(l7), u5 != 0)) {
        i12 = 0;
        do {
            l6 = FUN_001144a0(l7, 0x20, u5);
            u1 = (u5 < (unsigned long)(l6 - l7)) ? u5 : (unsigned long)(l6 - l7);
            u2 = (l6 != 0) ? u1 : u5;
            if ((u2 == b) &&
                ((b == 0 || (FUN_001145b0(l7, a, b) == 0)))) {
                u5 = (unsigned long)*(unsigned int *)(d + 0x10);
                l7 = d + 0x18;
                if (l7 == 0) l7 = 0;
                if (*(unsigned int *)(d + 0x10) == 0) goto sw_975e0;
                i4 = 0;
                pc = (unsigned long *)(l7 + (unsigned long)*(unsigned int *)(d + 0xc) * 0xc);
                goto sw_975b8;
            }
            i12++;
            l7 = l7 + u2;
            l6 = u5 - u2;
            if (l6 != 0) l7 = l7 + 1;
            u5 = l6 - (unsigned long)(l6 != 0);
        } while (u5 != 0);
    }
lb_974e0:
    *out = (long)s_unknown_error_005d5481;
    out[1] = (long)FUN_0037f9f4;
    *(unsigned short *)(out + 2) = 1;
lb_97504:
    if (canary != -0x2c8502b44bfffed6) cL4_stack_fail();
    return;
sw_975b8:
    if ((*pc & 0xf) == 7) {
        if (i4 == i12) {
            if ((c == 0) || ((c & 1) != 0)) {
                if ((c & 1) == 0) FUN_00369bb0(0, (unsigned long)s_Expected_a_metadata_pack_but_got_005d42f6);
                local_90 = DAT_004f2740;
                pu11 = (unsigned long *)(c & 0xfffffffffffffffe);
                l7 = pu11[-1];
                local_98 = 0;
                if (l7 != 0) {
                    do {
                        u9 = *pu11;
                        l6 = FUN_0039c740(u9, d);
                        u8 = 0;
                        if (l6 != 0)
                            u8 = FUN_00377824(0xff, l6, u9, d + (unsigned long)*(unsigned int *)(d + 0xc) * 0xc + 0x10, pc);
                        cL4_list_push_363f10(&local_98, u8);
                        l7--;
                        pu11++;
                    } while (l7 != 0);
                    u5 = local_90 & 0xffffffff;
                }
                l7 = cL4_pack_build(0);
                *(unsigned short *)(out + 2) = 0;
                *out = l7;
                if (l7 == 0) {
                    *out = (long)s_unknown_error_005d5481;
                    out[1] = (long)FUN_0037f9f4;
                    *(unsigned short *)(out + 2) = 1;
                }
                if (local_98 != 0) thunk_FUN_00012568(0, 0);
                goto lb_97504;
            }
            l7 = FUN_0039c740(c, d);
            if (l7 == 0) goto lb_974e0;
            l7 = FUN_00377824(0xff, l7, c, d + (unsigned long)*(unsigned int *)(d + 0xc) * 0xc + 0x10, pc);
            *(unsigned short *)(out + 2) = 0;
            *out = l7;
            if (l7 != 0) goto lb_97504;
            goto lb_974e0;
        }
        i4++;
    }
    pc += 2;
    u5--;
    if (u5 == 0) { sw_975e0: cL4_stack_fail(); }
    goto sw_975b8;
}

/* FUN_0039779c @ 0x39779c   (est. sk_type_decl_record)
 * Ghidra: long FUN_0039779c(long *param_1, uint *param_2, long *param_3)
 * Appends a {value, flags} pair (from *param_2 and *param_3) to a growable
 * 8-byte-element vector (param_1), growing via cL4_list_push_363f10 when full.
 * Returns a pointer to the just-written element.
 * Confidence: medium */
long sk_type_decl_record_39779c(long *vec, unsigned int *p, long *q)
{
    unsigned int u3; long l2; unsigned int *pu1; long l4;
    u3 = *(unsigned int *)(vec + 1);
    if (u3 < *(unsigned int *)((long)vec + 0xc)) {
        l2 = *vec;
        pu1 = (unsigned int *)(l2 + (unsigned long)u3 * 8);
        l4 = *q;
        *pu1 = (int)*(unsigned long *)p;
        pu1[1] = (int)l4;
        u3++;
        *(unsigned int *)(vec + 1) = u3;
    } else {
        cL4_list_push_363f10(vec, (unsigned long)*p | (unsigned long)*q << 0x20);
        l2 = *vec;
        u3 = *(unsigned int *)(vec + 1);
    }
    return l2 + (unsigned long)u3 * 8 - 8;
}

/* FUN_0039780c @ 0x39780c   (est. sk_type_push8)
 * Ghidra: long FUN_0039780c(long *param_1, undefined8 *param_2, undefined8 *param_3)
 * Appends a 16-byte pair {*param_2, *param_3} to a 16-byte-element vector
 * (grow via FUN_00365184 when full). Returns a pointer to the written pair.
 * Confidence: medium */
long sk_type_push8_39780c(long *vec, unsigned long *a, unsigned long *b)
{
    unsigned long *pu1; unsigned int u2;
    u2 = *(unsigned int *)(vec + 1);
    if (u2 < *(unsigned int *)((long)vec + 0xc)) {
        pu1 = (unsigned long *)(*vec + (unsigned long)u2 * 0x10);
        *pu1 = *a;
        pu1[1] = *b;
        u2++;
        *(unsigned int *)(vec + 1) = u2;
    } else {
        FUN_00365184((unsigned long)vec, *a, *b);
        u2 = *(unsigned int *)(vec + 1);
    }
    return *vec + (unsigned long)u2 * 0x10 - 0x10;
}

/* FUN_0039787c @ 0x39787c   (est. sk_type_field_push)
 * Ghidra: void FUN_0039787c(long *param_1, undefined8 *param_2, undefined1 *param_3)
 * Appends {*param_2, *param_3} to a 16-byte-element vector, or aborts via
 * FUN_00399550 when full.
 * Confidence: medium */
void sk_type_field_push_39787c(long *vec, unsigned long *a, unsigned char *b)
{
    unsigned long *pu1; unsigned int u2; unsigned char u3;
    u2 = *(unsigned int *)(vec + 1);
    if (u2 < *(unsigned int *)((long)vec + 0xc)) {
        pu1 = (unsigned long *)(*vec + (unsigned long)u2 * 0x10);
        u3 = *b;
        *pu1 = *a;
        *(unsigned char *)(pu1 + 1) = u3;
        *(unsigned int *)(vec + 1) = u2 + 1;
        return;
    }
    FUN_00399550();
}

/* FUN_003978b0 @ 0x3978b0   (est. sk_type_flatpair)
 * Ghidra: void FUN_003978b0(long *param_1, undefined4 *param_2)
 * Appends a single 4-byte word (*param_2) to a growable int vector (param_1),
 * growing via FUN_003995cc when full and freeing the old buffer.
 * Confidence: medium */
void sk_type_flatpair_3978b0(long *vec, unsigned int *pair)
{
    unsigned int *p8, *p4, *p10; long l2, l3, l6, l9; unsigned long u1, u5, u7;
    cL4_w16_t v;

    p4 = (unsigned int *)vec[2];
    p8 = (unsigned int *)vec[1];
    if (p8 < p4) {
        p10 = p8 + 1;
        *p8 = *pair;
    } else {
        l2 = *vec;
        l9 = (long)p8 - l2;
        l6 = l9 >> 2;
        u1 = l6 + 1;
        if (u1 >> 0x3e != 0) FUN_004b89f8();
        u5 = (long)p4 - l2;
        u7 = (long)u5 >> 1;
        if (u7 <= u1) u7 = u1;
        if (0x7ffffffffffffffb < u5) u7 = 0x3fffffffffffffff;
        if (u7 == 0) { v = ZEXT816(0); l3 = l9; }
        else {
            v = FUN_003995cc((unsigned long)(vec + 2), u7);
            l2 = *vec;
            l6 = vec[1] - l2 >> 2;
            l3 = vec[1] - l2;
        }
        p4 = (unsigned int *)(v.lo + l9);
        p10 = p4 + 1;
        *p4 = *pair;
        cL4_obj_copy_simple((long)(p4 - l6), l2, l3);
        l2 = *vec;
        *vec = (long)(p4 - l6);
        vec[1] = (long)p10;
        l6 = vec[2];
        vec[2] = v.lo + v.hi * 4;
        if (l2 != 0) thunk_FUN_00012568(l2, l6 - l2);
    }
    vec[1] = (long)p10;
}

/* FUN_00397998 @ 0x397998   (est. sk_type_push98)
 * Ghidra: undefined8 * FUN_00397998(long *param_1, undefined8 *param_2, uint *param_3)
 * Appends {*param_2, *param_3} to a 16-byte-element vector, growing via
 * FUN_00387868 when full. Returns a pointer to the written pair.
 * Confidence: medium */
unsigned long *sk_type_push98_397998(long *vec, unsigned long *a, unsigned int *b)
{
    unsigned long *p5, *p7; unsigned int u2; unsigned long u1, u6, u9;
    long l3, l4, l8, l10; cL4_w16_t v;

    p5 = (unsigned long *)vec[2];
    p7 = (unsigned long *)vec[1];
    if (p7 < p5) {
        u2 = *b;
        *p7 = *a;
        p7[1] = (unsigned long)u2;
        p7 += 2;
    } else {
        l3 = *vec;
        l10 = (long)p7 - l3;
        l8 = l10 >> 4;
        u1 = l8 + 1;
        if (u1 >> 0x3c != 0) FUN_004b89f8();
        u6 = (long)p5 - l3;
        u9 = (long)u6 >> 3;
        if (u9 <= u1) u9 = u1;
        if (0x7fffffffffffffef < u6) u9 = 0xfffffffffffffff;
        if (u9 == 0) { v = ZEXT816(0); l4 = l10; }
        else {
            v = FUN_00387868((unsigned long)(vec + 2), u9);
            l3 = *vec;
            l8 = vec[1] - l3 >> 4;
            l4 = vec[1] - l3;
        }
        p5 = (unsigned long *)(v.lo + l10);
        u2 = *b;
        *p5 = *a;
        p5[1] = (unsigned long)u2;
        p7 = p5 + 2;
        cL4_obj_copy_simple((long)(p5 + l8 * -2), l3, l4);
        l3 = *vec;
        *vec = (long)(p5 + l8 * -2);
        vec[1] = (long)p7;
        l8 = vec[2];
        vec[2] = v.lo + v.hi * 0x10;
        if (l3 != 0) thunk_FUN_00012568(l3, l8 - l3);
    }
    vec[1] = (long)p7;
    return p7 - 2;
}

/* FUN_00397a98 @ 0x397a98   (est. sk_type_build_bound)
 * Ghidra: void FUN_00397a98(long *param_1, undefined8 *param_2, undefined8 *param_3, long *param_4, long param_5, undefined8 param_6)
 * Builds a bound generic type by looking up the mangled name (param_3, kind
 * 0x13c) in the type-decl chain table (DAT_006c0a40 via FUN_00399620, under
 * lock-object _DAT_006c0a20), gathering the generic argument range pairs into
 * a vector (FUN_00367ccc), materializing the generic decl via
 * sk_type_build_generic_38ad64 and resolving the resulting name through
 * sk_type_elem_at_38cbb8 + sk_type_lookup_core_3895e0. Falls to "unknown
 * error" when the name isn't found.
 * Confidence: low
 * Notes: locks DAT_006c0a30 / DAT_006c0a58 init on demand; canary
 *   -0x2c8502b44bfffed6. */
void sk_type_build_bound_397a98(long *out, unsigned long *tree, unsigned long *node,
                                long *gv, long n, unsigned long a)
{
    unsigned long u1; int i2; unsigned long u3, u5; long l4; unsigned long canary2;
    unsigned long *pc6; long canary; unsigned long *pc9; long res; long lvar; long l278;
    unsigned long *gv2, *types; unsigned long local; cL4_w16_t vp;

    canary = -0x2c8502b44bfffed6;
    if (*(short *)(node + 2) == 0x13c) {
        unsigned long *pc6b = (unsigned long *)*node;
        if ((pc6b == 0) || (pc6b == 0)) pc6b = 0;
        if (-1 < (long)_DAT_006c0a58) cL4_diag_log(&_DAT_006c0a58, (unsigned long *)&FUN_00399614, (unsigned long)&_DAT_006c0a40);
        if (-1 < (long)_DAT_006c0a30) cL4_diag_log(&_DAT_006c0a30, (unsigned long *)&FUN_0038c324, 0);
        cL4_ref_acquire(0x6c0a20);
        l278 = 0;
        i2 = FUN_00399620((unsigned long)&_DAT_006c0a40, &pc6b, &l278);
        pc9 = 0;
        if ((i2 != 0) && (l278 != _DAT_006c0a40 + _DAT_006c0a50 * 0x10)) pc9 = (unsigned long *)*(unsigned long *)(l278 + 8);
        cL4_release(0x6c0a20);
        if (pc9 != 0) pc6b = (unsigned long *)pc9;
        if (pc6b != 0) {
            u3 = sk_cap_next_3658e8((unsigned long)(pc6b + 4));
            gv2 = (unsigned long *)&DAT_004f2710;
            types = (unsigned long *)&DAT_004f2710;
            if (n != 0) {
                long *pv = gv; long *pv2;
                do {
                    pv2 = pv + 2;
                    FUN_00367ccc((unsigned long *)&gv2, (unsigned long *)*pv, (unsigned long *)(*pv + pv[1] * 8));
                    pv = pv2;
                } while (pv2 != gv + n * 2);
            }
            sk_type_build_generic_38ad64(&l278, u3, 0, 0, 0, (long *)&types, (long *)&gv2, *tree);
            if (((unsigned long)&types & 1) == 0) {
                vp = FUN_0038cbb8((unsigned long)pc6b, a);
                local = 0;
                sk_type_lookup_core_3895e0(&res, 0, vp.lo, vp.hi, (unsigned long)&types, &types, &gv2);
                lvar = res;
                if (res != 0) lvar = 0;
                *(unsigned short *)(out + 2) = 0;
                *out = lvar;
                if (lvar == 0) {
                    *out = (long)s_unknown_error_005d5481;
                    out[1] = (long)FUN_0037f9f4;
                    *(unsigned short *)(out + 2) = 1;
                }
                FUN_0036805c(&types);
                FUN_003680cc(&gv2);
            } else {
                *(unsigned short *)(out + 2) = 1;
                out[1] = (long)FUN_00398074;
                *out = (long)s_unknown_error_005d5481;
            }
            goto lb_97e54;
        }
    }
    *out = (long)s_unknown_error_005d5481;
    out[1] = (long)FUN_0037f9f4;
    *(unsigned short *)(out + 2) = 1;
lb_97e54:
    if (canary != -0x2c8502b44bfffed6) cL4_stack_fail();
}

/* FUN_0038c640 @ 0x38c640   (est. sk_type_waiter_scan)
 * Ghidra: undefined1 [16] FUN_0038c640(undefined8 *param_1, ulong param_2, ulong param_3, long param_4)
 * Open-addressed type-decl cache probe: hashes the {key0,key1} pair
 * (FUN_003a2b38), masks it to the table capacity (element-size byte at the
 * low tag), and linearly probes (cL4_waiter_next) for a matching entry among
 * the first param_3 slots of the 0x18-byte-stride table at param_4. Returns
 * the 16-byte pair {found-entry-or-0, slot-index}.
 * Confidence: medium */
cL4_w16_t sk_type_waiter_scan_38c640(unsigned long *key, unsigned long cap,
                                     unsigned long count, long slots)
{
    unsigned long h, u3; int i1; unsigned long *p4; cL4_w16_t r; unsigned long l58;

    l58 = cap;
    h = FUN_003a2b38(*key, key[1]);
    u3 = 4;
    if (((cap & 3) != 0) && ((unsigned char *)(cap & 0xfffffffffffffffc) != 0))
        u3 = (unsigned long)*(unsigned char *)(cap & 0xfffffffffffffffc);
    u3 = -1L << (u3 & 0x3f);
    h = h & (u3 ^ 0xffffffffffffffff);
    if (h < 2) h = 1;
    i1 = cL4_waiter_next(&l58, h, 2);
    if (i1 != 0) {
        do {
            if ((unsigned long)(i1 - 1) < count) {
                p4 = (unsigned long *)(slots + (unsigned long)(i1 - 1) * 0x18);
                if ((key[1] == p4[1]) &&
                    ((key[1] == 0 || (i1 = thunk_FUN_001145b0(*key, *p4), i1 == 0)))) {
                    h = 0; goto lb_8c730;
                }
            }
            h = h + 1 & ~u3;
            if (h < 2) h = 1;
            i1 = cL4_waiter_next(&l58, h, 2);
        } while (i1 != 0);
    }
    p4 = 0;
    h = h & 0xffffffff;
lb_8c730:
    r.hi = h; r.lo = (unsigned long)p4;
    return r;
}

/* FUN_0038dd44 @ 0x38dd44   (est. sk_err_ctx)
 * Ghidra: void FUN_0038dd44(undefined8 *param_1, long *param_2)
 * Builds the TypeDecoder "failed to get parent context" error string into the
 * string buffer param_1: "<_gatherGenericParameters> context <N>" followed by
 * the generic-arg indices and the parent context value.
 * Confidence: medium
 * Notes: uses FUN_0000456c (arg-count) / FUN_00019850 (identifier string). */
void sk_err_ctx_38dd44(unsigned long *out, unsigned long *err)
{
    unsigned long l5, u2, u3; unsigned short s70; unsigned long l58;

    out[0] = 0; out[1] = 0; out[2] = 0;
    FUN_00112db4((unsigned long)out, (unsigned long)s__gatherGenericParameters__contex_005d52fa);
    l5 = *err;
    if (l5 == 0) l5 = 0;
    u2 = FUN_0000456c(l5);
    s70 = (unsigned short)u2;
    if ((u2 >> 8 & 1) != 0) {
        u3 = FUN_00019850((unsigned long)&s70);
        FUN_00112db4((unsigned long)out, u3);
        FUN_00112db4((unsigned long)out, (unsigned long)&DAT_005d021c);
    }
    sk_type_utf8_decode_38df24(&l58, (unsigned long)&DAT_005d531e);
    FUN_00112db4((unsigned long)out, l58);
    thunk_FUN_00012568(l58);
    FUN_00112db4((unsigned long)out, (unsigned long)&DAT_005d5321);
    if (err[2] != 0) {
        l5 = err[2] << 3;
        {
            int first = 1;
            do {
                if (!first) FUN_00112db4((unsigned long)out, (unsigned long)&DAT_005d0c46);
                sk_type_utf8_decode_38df24(&l58, (unsigned long)&DAT_005d531e);
                FUN_00112db4((unsigned long)out, l58);
                first = 0;
                l5 -= 8;
            } while (l5 != 0);
        }
    }
    FUN_00112db4((unsigned long)out, (unsigned long)&DAT_005d5324);
    FUN_00112db4((unsigned long)out, (unsigned long)s_parent__005d5327);
    if (err[3] == 0)
        FUN_00112db4((unsigned long)out, (unsigned long)s_null_005d5330);
    else
        FUN_00112db4((unsigned long)out, err[3]);
    FUN_00112db4((unsigned long)out, (unsigned long)&DAT_005d5337);
}

/* FUN_00389e8c @ 0x389e8c   (est. sk_type_demangle_resolve)
 * Ghidra: void FUN_00389e8c(ulong *param_1, ...)
 * Public demangle+resolve entry: builds a demangle-tree node for the name
 * (a,b) via FUN_003a32a0, then calls the recursive decoder
 * sk_type_decode_38f0a8 to materialize metadata, writing {value, vtable,
 * kind} into out. On success (kind 0) the PAC'd pointer is returned directly;
 * on failure an error descriptor is built.
 * Confidence: medium
 * Notes: PAC entry-point error; canary -0x2c8502b44bfffed6. */
void sk_type_demangle_resolve_389e8c(unsigned long *out, unsigned long a, unsigned long b,
                                     unsigned long c, unsigned long d, unsigned long e)
{
    long l1; unsigned long res; long canary; unsigned long ctx, n2;
    unsigned long out3[4]; unsigned short kind;

    canary = -0x2c8502b44bfffed6;
    {
        unsigned long frame[2048] = {0};
        frame[0] = 0x67b938; ctx = 0x67b7d0;
        l1 = FUN_003a32a0((unsigned long)&frame[0], a, b, &ctx);
        cL4_zone_get(&ctx);
        if (l1 == 0) {
            *(unsigned short *)(out + 2) = 1;
            *out = (unsigned long)s_Demangling_failed_005d5260;
            out[1] = (unsigned long)FUN_0037f9f4;
        } else {
            sk_strbuf_copy_38ef98((long)&ctx, (void *)d);
            sk_strbuf_copy_38f020((long)&n2, (void *)e);
            sk_strbuf_copy_38ef98((long)&n2, (void *)&ctx);
            sk_strbuf_copy_38f020((long)&n2, (void *)&n2);
            FUN_0036805c(&n2);
            FUN_003680cc(&ctx);
            sk_type_decode_38f0a8(out3, &ctx, l1, 0, 0);
            res = out3[0]; kind = *(unsigned short *)(out3 + 2);
            if (kind == 1) {
                *(unsigned short *)(out + 2) = 1;
                out[1] = (unsigned long)FUN_0037f9f4;
                *out = res;
            } else if (kind == 0 && res != 0) {
                if ((res & 1) != 0) { *(unsigned short *)(out + 2) = 0; *out = res; }
                else {
                    *(unsigned short *)(out + 2) = 1;
                    *out = (unsigned long)s_This_entry_point_is_only_for_pac_005d5292;
                    out[1] = (unsigned long)FUN_0037f9f4;
                }
            } else {
                *(unsigned short *)(out + 2) = 1;
                *out = (unsigned long)s_NULL_type_but_no_error_provided_005d5272;
                out[1] = (unsigned long)FUN_0037f9f4;
            }
            FUN_0036805c(&n2);
            FUN_003680cc(&ctx);
        }
        ctx = 0x67c398; cL4_zone_get(&n2);
        ctx = 0x67c370; cL4_ipc_obj_publish(0, 0, 0);
    }
    if (canary != -0x2c8502b44bfffed6) cL4_stack_fail();
}

/* FUN_0038a234 @ 0x38a234   (est. sk_type_demangle_resolve2)
 * Ghidra: void FUN_0038a234(undefined8 *param_1, ...)
 * Variant of sk_type_demangle_resolve_389e8c used for the PAC entry-point
 * error path: same demangle+decode, but on decode success always reports
 * kind 0 with the raw value (no PAC check).
 * Confidence: medium
 * Notes: canary -0x2c8502b44bfffed6. */
void sk_type_demangle_resolve2_38a234(unsigned long *out, unsigned long a, unsigned long b,
                                      unsigned long c, unsigned long d, unsigned long e)
{
    long l1; unsigned long res; long canary; unsigned long ctx, n2;
    unsigned long out3[4]; unsigned short kind;

    canary = -0x2c8502b44bfffed6;
    {
        unsigned long frame[2048] = {0};
        frame[0] = 0x67b938; ctx = 0x67b7d0;
        l1 = FUN_003a32a0((unsigned long)&frame[0], a, b, &ctx);
        cL4_zone_get(&ctx);
        if (l1 == 0) {
            *(unsigned short *)(out + 2) = 1;
            *out = (unsigned long)s_Demangling_failed_005d5260;
            out[1] = (unsigned long)FUN_0037f9f4;
        } else {
            sk_strbuf_copy_38ef98((long)&ctx, (void *)d);
            sk_strbuf_copy_38f020((long)&n2, (void *)e);
            sk_strbuf_copy_38ef98((long)&n2, (void *)&ctx);
            sk_strbuf_copy_38f020((long)&n2, (void *)&n2);
            FUN_0036805c(&n2);
            FUN_003680cc(&ctx);
            sk_type_decode_38f0a8(out3, &ctx, l1, 0, 0);
            res = out3[0];
            *(unsigned short *)(out + 2) = 0;
            *out = res;
            FUN_0036805c(&n2);
            FUN_003680cc(&ctx);
        }
        ctx = 0x67c398; cL4_zone_get(&n2);
        ctx = 0x67c370; cL4_ipc_obj_publish(0, 0, 0);
    }
    if (canary != -0x2c8502b44bfffed6) cL4_stack_fail();
}
