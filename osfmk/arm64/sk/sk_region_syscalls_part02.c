/* Recreated from cl4_kernel.raw (cL4 Secure Kernel, arm64e, image base 0) -
 * the cL4 microkernel (GL1), "cL4 (679.100.61)". Ground truth: Ghidra FUN_
 * names + addresses in program cl4_kernel.raw.
 * Slice 02: 0x312a44-0x31a96c syscall/exception-entry region.
 * All names are estimates unless string/header-matched. */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "sk_internal.h"

/* 128-bit unsigned value (lo = low 64 bits, hi = high 64 bits). */
typedef struct sk_u128 {
    uint64_t lo;
    uint64_t hi;
} sk_u128_t;

typedef uint64_t (*code_t)(void);

/* ------------------------------------------------------------------ *
 * Out-of-range cL4 helper declarations (declared extern with a one-line
 * note; their bodies are reconstructed by the range worker that owns them).
 * ------------------------------------------------------------------ */
extern uint64_t FUN_000026e8(void);
extern uint64_t FUN_00019858(void);
extern uint64_t FUN_0001a1c8(void);
extern uint64_t FUN_00021480(void);
extern uint64_t FUN_00041138(void);
extern uint64_t FUN_0006b674(void);
extern uint64_t FUN_0006b6f4(void);
extern uint64_t FUN_0006f768(void);
extern uint64_t FUN_00077770(void);
extern uint64_t FUN_0007c1a4(void);
extern uint64_t FUN_0008409c(void);
extern uint64_t FUN_000867a8(uint64_t, uint64_t);
extern uint64_t FUN_0008e500(uint64_t);
extern uint64_t FUN_0008e518(void);
extern uint64_t FUN_000b43d0(void);
extern uint64_t FUN_000b43e8(void);
extern uint64_t FUN_000f5e08(void);
extern uint64_t FUN_00106e3c(void);
extern uint64_t FUN_001a84f4(uint64_t);
extern uint64_t FUN_001a8564(void);
extern uint64_t FUN_001a89a8(uint64_t, uint64_t, uint64_t);
extern uint64_t FUN_001afa84(void);
extern uint64_t FUN_001afe4c(void);
extern uint64_t FUN_001d3a30(uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t FUN_001d9840(void);
extern uint64_t FUN_001df510(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t FUN_001e3210(void);
extern uint64_t FUN_001e4cbc(void);
extern uint64_t FUN_001e638c(void);
extern uint64_t FUN_001e6908(void);
extern uint64_t FUN_002298d4(void);
extern uint64_t FUN_0022d118(void);
extern uint64_t FUN_0022fb38(void);
extern uint64_t FUN_00231c2c(void);
extern uint64_t FUN_00231c40(void);
extern uint64_t FUN_0023b1a8(void);
extern uint64_t FUN_002412d4(void);
extern uint64_t FUN_0024304c(void);
extern uint64_t FUN_00243c60(void);
extern uint64_t FUN_002d3c28(void);
extern uint64_t FUN_002d49d0(void);
extern uint64_t FUN_002d49f4(uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t FUN_002d4a64(void);
extern uint64_t FUN_002e62f0(uint64_t);
extern uint64_t FUN_002e6330(void);
extern uint64_t FUN_002e6410(void);
extern uint64_t FUN_002e6474(void);
extern uint64_t FUN_002e648c(uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t FUN_003109b4(void);
extern uint64_t FUN_00310a44(void);
extern uint64_t FUN_00311ca0(uint64_t, uint64_t);
extern uint64_t FUN_00311cf8(uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t FUN_00311e34(void);
extern uint64_t FUN_00321ca0(void);
extern uint64_t FUN_0032b558(uint64_t, uint64_t);
extern uint64_t FUN_0032b924(void);
extern uint64_t FUN_0032b9dc(uint64_t, uint64_t);
extern uint64_t FUN_0032f900(uint64_t, uint64_t);
extern uint64_t FUN_00342b68(void);
extern uint64_t FUN_0034313c(void);
extern uint64_t FUN_00343d18(void);
extern uint64_t FUN_00347fb4(void);
extern uint64_t FUN_00348160(void);
extern uint64_t FUN_003482c4(void);
extern uint64_t FUN_003484b4(void);
extern uint64_t FUN_003488bc(uint64_t);
extern uint64_t FUN_0034951c(void);
extern uint64_t FUN_00349944(void);
extern uint64_t FUN_00349a54(void);
extern uint64_t FUN_00349d58(void);
extern uint64_t FUN_00349e8c(void);
extern uint64_t FUN_00349ea0(void);
extern uint64_t FUN_00349fcc(void);
extern uint64_t FUN_0034a43c(void);
extern uint64_t FUN_0034ab20(void);
extern uint64_t FUN_0034b804(void);
extern uint64_t FUN_0034bb84(void);
extern uint64_t FUN_0034be0c(uint64_t);
extern uint64_t FUN_0034c2a4(void);
extern uint64_t FUN_0034c434(void);
extern uint64_t FUN_0034c444(uint64_t);
extern uint64_t FUN_0034c7a8(void);
extern uint64_t FUN_0034daa8(void);
extern uint64_t FUN_0034def4(void);
extern uint64_t FUN_0034e53c(void);
extern uint64_t FUN_0034ea7c(void);
extern uint64_t FUN_0034ed08(void);
extern uint64_t FUN_00350230(uint64_t);
extern uint64_t FUN_00350240(void);
extern uint64_t FUN_00350258(void);
extern uint64_t FUN_00350470(void);
extern uint64_t FUN_0035047c(void);
extern uint64_t FUN_003504d0(void);
extern uint64_t FUN_00350630(void);
extern uint64_t FUN_00350974(uint64_t, uint64_t);
extern uint64_t FUN_00350aa0(void);
extern uint64_t FUN_00350aac(uint64_t, uint64_t);
extern uint64_t FUN_00350bd8(uint64_t);
extern uint64_t FUN_00350d94(uint64_t);
extern uint64_t FUN_00351124(void);
extern uint64_t FUN_003511b4(void);
extern uint64_t FUN_003513fc(void);
extern uint64_t FUN_00351790(void);
extern uint64_t FUN_003517b4(void);
extern uint64_t FUN_003518c4(void);
extern uint64_t FUN_00351be0(void);
extern uint64_t FUN_00351cc4(void);
extern uint64_t FUN_00351d30(uint64_t, uint64_t);
extern uint64_t FUN_00351e20(void);
extern uint64_t FUN_003521e4(void);
extern uint64_t FUN_0035237c(void);
extern uint64_t FUN_003523f0(uint64_t);
extern uint64_t FUN_00352498(void);
extern uint64_t FUN_003524c8(void);
extern uint64_t FUN_0035272c(void);
extern uint64_t FUN_00352764(void);
extern uint64_t FUN_00352950(void);
extern uint64_t FUN_0035295c(void);
extern uint64_t FUN_00352c74(void);
extern uint64_t FUN_00352cec(void);
extern uint64_t FUN_00352e60(void);
extern uint64_t FUN_00352e84(void);
extern uint64_t FUN_00353510(void);
extern uint64_t FUN_00353d34(uint64_t, uint64_t, uint64_t);
extern uint64_t FUN_00354318(void);
extern uint64_t FUN_00354720(void);
extern uint64_t FUN_00354a34(void);
extern uint64_t FUN_00354ef8(void);
extern uint64_t FUN_003553f4(void);
extern uint64_t FUN_00355458(void);
extern uint64_t FUN_003554e0(void);
extern uint64_t FUN_00355528(void);
extern uint64_t FUN_00355754(uint64_t);
extern uint64_t FUN_00355890(void);
extern uint64_t FUN_00355968(uint64_t);
extern uint64_t FUN_00355998(void);
extern uint64_t FUN_00355c00(void);
extern uint64_t FUN_00356584(void);
extern uint64_t FUN_003567c8(void);
extern uint64_t FUN_00356d20(void);
extern uint64_t FUN_00357074(void);
extern uint64_t FUN_0035723c(uint64_t);
extern uint64_t FUN_00357c44(void);
extern uint64_t FUN_00357c74(void);
extern uint64_t FUN_00357ca0(void);
extern uint64_t FUN_00357cb4(void);
extern uint64_t FUN_003583a4(void);
extern uint64_t FUN_0035847c(void);
extern uint64_t FUN_00358c20(void);
extern uint64_t FUN_00358fb4(void);
extern uint64_t FUN_00358fc8(uint64_t);
extern uint64_t FUN_00359284(uint64_t, uint64_t, uint64_t);
extern uint64_t FUN_00359380(uint64_t, uint64_t);
extern uint64_t FUN_00359424(void);
extern uint64_t FUN_003598b4(void);
extern uint64_t FUN_00359a90(void);
extern uint64_t FUN_00359b0c(void);
extern uint64_t FUN_00359e8c(void);
extern uint64_t FUN_0035aad8(void);
extern uint64_t FUN_0036298c(uint64_t);
extern uint64_t FUN_0036aae4(void);
extern uint64_t FUN_0036b118(uint64_t);
extern uint64_t FUN_0036b21c(void);
extern uint64_t FUN_00377824(uint64_t, uint64_t, uint64_t);
extern uint64_t FUN_003a25d4(uint64_t);


void sk_add128_checked(uint64_t *out, uint64_t *in);
void sk_checked_op(sk_u128_t *out, uint64_t a, uint64_t b, sk_u128_t (*op)(uint64_t,uint64_t,uint64_t,uint64_t), uint64_t code);
void sk_add128_checked_00312af8(uint64_t *out, uint64_t *in);
void sk_add_checked(sk_u128_t *a, uint64_t b_lo, int64_t b_hi);
void sk_add_checked_msg_a(sk_u128_t *a, sk_u128_t *b);
void sk_add_checked_msg_b(sk_u128_t *a, sk_u128_t *b);
long sk_clone_vtable(long dst, long src);
void sk_cpu_128_leaf(void);
void sk_cpu_128_leaf_00312c44(void);
void sk_div_checked_min(sk_u128_t *a, int64_t b_lo, int64_t b_hi);
void sk_div_checked_min2(int64_t a, int64_t b, int64_t c, int64_t d);
void sk_div_checked_min3(sk_u128_t *a, int64_t b_lo, int64_t b_hi);
sk_u128_t sk_divti3(uint64_t a, uint64_t b, uint64_t c);
sk_u128_t sk_divti3_b(uint64_t a, uint64_t b, uint64_t c);
sk_u128_t sk_divti3_wrap_a(sk_u128_t *a, sk_u128_t *b);
sk_u128_t sk_divti3_wrap_b(sk_u128_t *a, sk_u128_t *b);
void sk_divti3_wrap_c(void);
void sk_divti3_wrap_d(void);
void sk_double_to_i128(void);
long sk_field_ref_04(uint64_t obj);
long sk_field_ref_04_0031989c(uint64_t obj);
long sk_field_ref_08(uint64_t obj);
long sk_field_ref_08_0031a26c(uint64_t obj);
long sk_field_ref_0c(uint64_t obj);
long sk_field_ref_0c_003197a8(uint64_t obj);
long sk_field_ref_0c_0031986c(uint64_t obj);
long sk_field_ref_0c_00319aec(uint64_t obj);
long sk_field_ref_0c_00319b1c(uint64_t obj);
long sk_field_ref_0c_0031a17c(uint64_t obj);
long sk_field_ref_0c_0031a5dc(uint64_t obj);
long sk_field_ref_10(uint64_t obj);
long sk_field_ref_10_0031948c(uint64_t obj);
long sk_field_ref_10_003197d8(uint64_t obj);
long sk_field_ref_10_00319a90(uint64_t obj);
long sk_field_ref_10_00319b4c(uint64_t obj);
long sk_field_ref_10_00319b7c(uint64_t obj);
long sk_field_ref_14(uint64_t obj);
long sk_field_ref_14_003196e8(uint64_t obj);
long sk_field_ref_14_003198fc(uint64_t obj);
long sk_field_ref_14_0031993c(uint64_t obj);
long sk_field_ref_14_00319bac(uint64_t obj);
long sk_field_ref_14_00319bdc(uint64_t obj);
long sk_field_ref_14_0031a2cc(uint64_t obj);
long sk_field_ref_14_0031a60c(uint64_t obj);
long sk_field_ref_18(uint64_t obj);
long sk_field_ref_18_00319c3c(uint64_t obj);
long sk_field_ref_18_0031a2fc(uint64_t obj);
long sk_field_ref_18_0031a63c(uint64_t obj);
long sk_field_ref_1c(uint64_t obj);
long sk_field_ref_1c_00319718(uint64_t obj);
long sk_field_ref_1c_0031a32c(uint64_t obj);
long sk_field_ref_1c_0031a66c(uint64_t obj);
long sk_field_ref_20(uint64_t obj);
long sk_field_ref_20_0031a35c(uint64_t obj);
long sk_field_ref_20_0031a69c(uint64_t obj);
long sk_field_ref_24(uint64_t obj);
long sk_field_ref_24_0031a6cc(uint64_t obj);
long sk_field_ref_28(uint64_t obj);
long sk_field_ref_2c(uint64_t obj);
long sk_field_ref_2c_00319628(uint64_t obj);
long sk_field_ref_2c_00319688(uint64_t obj);
long sk_field_ref_30(uint64_t obj);
long sk_field_ref_34(uint64_t obj);
long sk_field_ref_34_0031a44c(uint64_t obj);
long sk_field_ref_38(uint64_t obj);
long sk_field_ref_3c(uint64_t obj);
long sk_field_ref_40(uint64_t obj);
long sk_field_ref_44(uint64_t obj);
long sk_field_ref_48(uint64_t obj);
long sk_field_ref_4c(uint64_t obj);
long sk_field_ref_4c_0031a11c(uint64_t obj);
long sk_field_ref_4c_0031a56c(uint64_t obj);
long sk_field_ref_50(uint64_t obj);
long sk_field_ref_58(uint64_t obj);
long sk_field_ref_5c(uint64_t obj);
long sk_field_ref_5c_0031a96c(uint64_t obj);
long sk_field_ref_6c(uint64_t obj);
uint32_t sk_flag_test_a(void);
uint32_t sk_flag_test_b(void);
uint32_t sk_flag_test_b_003190c8(void);
void sk_float_mul_add(uint64_t *out);
void sk_forward2_a(uint64_t a, uint64_t b);
void sk_forward2_b(uint64_t a, uint64_t b);
void sk_forward2_c(uint64_t a, uint64_t b);
uint64_t sk_forward2_d(uint64_t a);
void sk_fp_init_a(void);
void sk_fp_init_b(void);
void sk_fp_seq_a(void);
void sk_fp_seq_b(void);
void sk_fp_seq_c(sk_u128_t *out);
void sk_fp_seq_d(uint64_t *out);
sk_u128_t sk_i128_neg(int64_t lo, int64_t hi);
void sk_i128_to_double(void);
void sk_i128_to_double_00314644(void);
void sk_i128_to_double_003180bc(void);
uint64_t sk_identity_ret(uint64_t a);
uint64_t sk_index_select(uint64_t index, uint64_t a, uint64_t b);
sk_u128_t sk_index_select_ld128(sk_u128_t *out, uint64_t *sel);
void sk_indirect_ld128_a(sk_u128_t *out);
void sk_indirect_ld128_b(sk_u128_t *out);
void sk_init_128_zero(sk_u128_t *out);
void sk_ld128_alt(sk_u128_t *out);
void sk_ld128_aux(sk_u128_t *out);
void sk_ld128_flag_a(sk_u128_t *out, uint64_t a, uint32_t flag);
void sk_ld128_flag_b(uint64_t a, uint64_t b, uint32_t flag);
void sk_ld128_fn(sk_u128_t *out);
void sk_ld128_fp_a(sk_u128_t *out);
void sk_ld128_fp_b(sk_u128_t *out);
void sk_ld128_fp_c(sk_u128_t *out);
void sk_ld128_fp_d(sk_u128_t *out);
void sk_ld128_math(sk_u128_t *out);
void sk_ld128_neg(sk_u128_t *out);
void sk_ld128_saved(sk_u128_t *out);
void sk_ld128_shl_thunk(sk_u128_t *out);
void sk_ld128_store_byte(sk_u128_t *out, uint64_t p2, uint64_t p3, uint8_t val);
void sk_ld128_store_flag(sk_u128_t *out, uint64_t a, uint64_t b, uint8_t flag);
uint64_t sk_ld_obj_if_flag(uint64_t *out);
void sk_ld_zero_ext(sk_u128_t *out);
sk_u128_t sk_ldexp_guard1(uint64_t a, uint64_t b, int64_t hi, int64_t lo);
void sk_ldexp_guard2(sk_u128_t *out, int64_t hi, int64_t lo);
sk_u128_t sk_ldexp_guard3(uint64_t a, uint64_t b, int64_t hi, int64_t lo);
void sk_ldexp_guard4(sk_u128_t *out, int64_t hi, int64_t lo);
void sk_ldexp_variant(sk_u128_t *out);
void sk_ldexp_variant2(sk_u128_t *out);
void sk_leaf_43d18(void);
void sk_math_binop_a(sk_u128_t *a, sk_u128_t *b);
void sk_math_binop_b(sk_u128_t *a, sk_u128_t *b);
void sk_math_binop_c(void);
void sk_math_binop_d(void);
void sk_math_binop_e(void);
void sk_math_op2a(void);
void sk_math_op2b(void);
void sk_math_seq(void);
void sk_math_seq2(void);
void sk_math_unop_a(void);
void sk_math_unop_b(void);
void sk_msg_forward(uint64_t a, uint64_t b, uint64_t c);
void sk_msg_leaf_a(void);
void sk_msg_leaf_b(void);
void sk_msg_setup_vtable(void);
void sk_msg_teardown(void);
int64_t sk_mul128_low_signed(uint64_t a, uint64_t b, int64_t hi, uint64_t sh);
void sk_mul128_signed_checked(uint64_t a_lo, uint64_t a_hi, uint64_t b_lo, uint64_t b_hi);
void sk_mul128_signed_low(void);
void sk_mul_acc128(sk_u128_t *out, uint64_t *acc, uint64_t *m);
void sk_mul_checked_msg_a(sk_u128_t *out, sk_u128_t *b);
void sk_mul_checked_msg_b(sk_u128_t *out, sk_u128_t *b);
sk_u128_t sk_multi3(uint64_t b_lo, uint64_t a_hi, uint64_t a_lo, uint64_t b_hi);
void sk_multi3_full(uint64_t a_lo, uint64_t a_hi, uint64_t b_lo, uint64_t b_hi);
void sk_neg128_abs(sk_u128_t *out, int64_t *in);
void sk_neg_checked(uint64_t *out);
void sk_neg_panic_if_neg(uint64_t a, int64_t b);
void sk_nop_leaf(void);
void sk_nop_leaf_00319230(void);
void sk_nop_leaf_00319308(void);
void sk_nop_leaf_00319320(void);
void sk_nop_leaf_00319338(void);
void sk_nop_leaf_003193f4(void);
void sk_nop_leaf_003194e0(void);
void sk_nop_leaf_00319598(void);
void sk_nop_leaf_003195b0(void);
void sk_nop_leaf_003199d4(void);
void sk_nop_leaf_003199ec(void);
void sk_nop_leaf_0031a1dc(void);
void sk_nop_leaf_0031a1f4(void);
void sk_nop_leaf_0031a29c(void);
void sk_nop_leaf_0031a2b4(void);
void sk_panic_noreturn(void);
void sk_parse_int_fmt(sk_u128_t *out, uint64_t fmt, uint64_t *p);
void sk_resolve_ref_p2(uint64_t count, uint64_t p2);
uint64_t sk_shl64_checked(uint64_t index, uint64_t a, uint64_t b);
sk_u128_t sk_shl64_select(sk_u128_t *out, uint64_t *sel);
void sk_shl_dispatch_a(sk_u128_t *a, sk_u128_t *b, uint64_t sh);
void sk_shl_dispatch_b(sk_u128_t *a, sk_u128_t *b, uint64_t sh);
void sk_shr_dispatch_a(sk_u128_t *a, sk_u128_t *b, uint64_t sh);
void sk_shr_dispatch_b(sk_u128_t *a, sk_u128_t *b, uint64_t sh);
void sk_sub_checked(sk_u128_t *a, uint64_t b_lo, int64_t b_hi);
void sk_sub_checked_msg_a(sk_u128_t *a, sk_u128_t *b);
void sk_sub_checked_msg_b(sk_u128_t *a, sk_u128_t *b);
uint64_t sk_u128_shl(uint64_t *out_lo, uint64_t hi, uint64_t lo, uint64_t sh);
uint64_t sk_u128_shl7(uint64_t *out_lo, uint64_t hi, uint64_t lo, uint64_t sh);
sk_u128_t sk_u128_shl_ret(uint64_t lo, uint64_t hi, uint64_t sh);
int64_t sk_u128_shr_arith(uint64_t *out_lo, int64_t hi, uint64_t lo, uint64_t sh);
uint64_t sk_u128_shr_logical(uint64_t *out_lo, uint64_t hi, uint64_t lo, uint64_t sh);
sk_u128_t sk_u128_shr_ret(uint64_t lo, uint64_t hi, uint64_t sh);
void sk_u128_sub(uint64_t a_lo, uint64_t a_hi, uint64_t b_lo, uint64_t b_hi);
void sk_u128_to_double(void);
void sk_u128_to_double_00314cac(void);
void sk_u128_to_double_00317b50(void);
void sk_u128_to_double_00318718(void);
void sk_u128_to_double_b(void);
sk_u128_t sk_udiv128(uint64_t a, uint64_t b, uint64_t c, uint64_t d);
sk_u128_t sk_udivmodti4(uint64_t a, uint64_t b, uint64_t c, uint64_t d);
void sk_udivmodti4_core(sk_u128_t *q, sk_u128_t *r, uint64_t n0, uint64_t n1,
                             uint64_t n2, uint64_t d0, uint64_t d1);
void sk_udivti3_core(void);
sk_u128_t sk_udivti3_ret(void);
sk_u128_t sk_udivti3_ret2(void);
uint64_t sk_validate_ret(uint64_t a, uint64_t b);
void sk_vtable_call(void);
void sk_vtable_call_b(void);

/* FUN_00312a44 @ 0x00312a44   (est. sk_multi3)
 * Ghidra: FUN_00312a44
 * 128-bit multiply (__multi3). operands (param_2:param_3)*(param_4:param_1).
 * Confidence: high
 */
sk_u128_t sk_multi3(uint64_t b_lo, uint64_t a_hi, uint64_t a_lo, uint64_t b_hi)
{
    /* low 64 bits: a_lo * b_lo; high: cross terms + carry of the low product */
    sk_u128_t r;
    __uint128_t lo = (__uint128_t)a_lo * (__uint128_t)b_lo;
    r.lo = (uint64_t)lo;
    r.hi = (uint64_t)(lo >> 64) + a_hi * b_lo + a_lo * b_hi;
    return r;
}


/* FUN_00312a88 @ 0x00312a88   (est. sk_ld128_store_byte)
 * Ghidra: FUN_00312a88
 * Loads a 128-bit value from FUN_00311e34, stores it, then writes byte param_4 at offset +8.
 * Confidence: medium
 */
void sk_ld128_store_byte(sk_u128_t *out, uint64_t p2, uint64_t p3, uint8_t val)
{
    /* out-of-range helper FUN_00311e34 supplies the 128-bit operand */
    out->lo = FUN_00311e34();
    out->hi = 0;
    ((uint8_t *)out)[8] = val;   /* write param_4 into byte 8 of the 16-byte result */
}


/* FUN_00312ab4 @ 0x00312ab4   (est. sk_ld128_saved)
 * Ghidra: FUN_00312ab4
 * Loads a 128-bit value from FUN_0001a1c8 and stores to the x19 output.
 * Confidence: medium
 */
void sk_ld128_saved(sk_u128_t *out)
{
    FUN_00353510();
    out->lo = FUN_0001a1c8();
    out->hi = 0;
}


/* FUN_00312af4 @ 0x00312af4   (est. sk_add128_checked)
 * Ghidra: FUN_00312af4
 * 128-bit add via FUN_003163d8 with overflow handler FUN_00312a44, panic code 0xae.
 * Confidence: medium
 */
void sk_add128_checked(uint64_t *out, uint64_t *in)
{
    sk_checked_op((sk_u128_t *)out, in[0], in[1], sk_multi3, 0xae);
}


/* FUN_00312af8 @ 0x00312af8   (est. sk_add128_checked_00312af8)
 * Ghidra: FUN_00312af8
 * 128-bit add via FUN_003163d8 with overflow handler FUN_00312a44, panic code 0xae.
 * Confidence: medium
 */
void sk_add128_checked_00312af8(uint64_t *out, uint64_t *in)
{
    sk_checked_op((sk_u128_t *)out, in[0], in[1], sk_multi3, 0xae);
}


/* FUN_00312b2c @ 0x00312b2c   (est. sk_init_128_zero)
 * Ghidra: FUN_00312b2c
 * FUN_00351124 then FUN_002e62f0; stores 128-bit value with hi=0.
 * Confidence: medium
 */
void sk_init_128_zero(sk_u128_t *out)
{
    FUN_00351124();
    out->lo = FUN_002e62f0(0);
    out->hi = 0;
}


/* FUN_00312b54 @ 0x00312b54   (est. sk_index_select)
 * Ghidra: FUN_00312b54
 * Returns param_3 when index>1 panics; when index==1 returns param_3 else param_2.
 * Confidence: medium
 */
uint64_t sk_index_select(uint64_t index, uint64_t a, uint64_t b)
{
    if (1 < index) {
        FUN_003488bc(1);
        FUN_00355890();
        FUN_00349e8c();
        FUN_00351be0();
        FUN_001afe4c();   /* no-return */
    }
    if (index != 0)
        a = b;
    return a;
}


/* FUN_00312b98 @ 0x00312b98   (est. sk_u128_shr_logical)
 * Ghidra: FUN_00312b98
 * Logical shift right of 128-bit (hi:lo) by sh; *out_lo=lo, returns hi.
 * Confidence: high
 */
uint64_t sk_u128_shr_logical(uint64_t *out_lo, uint64_t hi, uint64_t lo, uint64_t sh)
{
    if (sh < 0x40) {
        if (sh == 0) {
            *out_lo = lo;
        } else {
            *out_lo = (hi << (uint64_t)(~sh & 0x3f)) | (lo >> (sh & 0x3f));
            hi = hi >> (sh & 0x3f);
        }
    } else {
        uint64_t h = hi >> (sh & 0x3f);
        hi = 0;
        *out_lo = h;
    }
    return hi;
}


/* FUN_00312be0 @ 0x00312be0   (est. sk_u128_shr_arith)
 * Ghidra: FUN_00312be0
 * Arithmetic shift right of 128-bit (hi:lo) by sh&0x7f; *out_lo=lo, returns hi (sign-filled).
 * Confidence: high
 */
int64_t sk_u128_shr_arith(uint64_t *out_lo, int64_t hi, uint64_t lo, uint64_t sh)
{
    uint64_t u = sh & 0x7f;
    if (u < 0x40) {
        if (u == 0) {
            *out_lo = lo;
        } else {
            *out_lo = ((uint64_t)hi << (uint64_t)(-u & 0x3f)) | (lo >> (sh & 0x3f));
            hi = hi >> (sh & 0x3f);
        }
    } else {
        uint64_t v = (uint64_t)hi >> (sh & 0x3f);
        hi = hi >> 0x3f;          /* sign-fill */
        *out_lo = v;
    }
    return hi;
}


/* FUN_00312c40 @ 0x00312c40   (est. sk_cpu_128_leaf)
 * Ghidra: FUN_00312c40
 * Two-leaf helper: FUN_00359424 + FUN_001e6908.
 * Confidence: medium
 */
void sk_cpu_128_leaf(void)
{
    FUN_00359424();
    FUN_001e6908();
}


/* FUN_00312c44 @ 0x00312c44   (est. sk_cpu_128_leaf_00312c44)
 * Ghidra: FUN_00312c44
 * Two-leaf helper: FUN_00359424 + FUN_001e6908.
 * Confidence: medium
 */
void sk_cpu_128_leaf_00312c44(void)
{
    FUN_00359424();
    FUN_001e6908();
}


/* FUN_00312c70 @ 0x00312c70   (est. sk_index_select_ld128)
 * Ghidra: FUN_00312c70
 * sk_index_select on x20 words, stores result; returns {FUN_0001a1c8, out}.
 * Confidence: medium
 */
sk_u128_t sk_index_select_ld128(sk_u128_t *out, uint64_t *sel)
{
    uint64_t v = sk_index_select(sel[0], ((uint64_t *)0)[0], ((uint64_t *)0)[1]);
    out->lo = v;
    sk_u128_t r;
    r.lo = (uint64_t)FUN_0001a1c8;
    r.hi = (uint64_t)out;
    return r;
}


/* FUN_00312cc4 @ 0x00312cc4   (est. sk_udiv128)
 * Ghidra: FUN_00312cc4
 * 128-bit unsigned divide wrapper: FUN_00312d08 with 6 args, packs {lo,hi}.
 * Confidence: medium
 */
sk_u128_t sk_udiv128(uint64_t a, uint64_t b, uint64_t c, uint64_t d)
{
    /* 128-bit divide; quotient/remainder returned via registers (sk_udivti3_core) */
    sk_udivti3_core();
    sk_u128_t r = {0, 0};   /* register-forwarded quotient */
    return r;
}


/* FUN_00312d08 @ 0x00312d08   (est. sk_udivti3_core)
 * Ghidra: FUN_00312d08
 * 128-bit unsigned divide core (__udivti3). Panics 'Division by zero' 0x4d9 on zero divisor. Writes quotient via x20, remainder via x21, hi via x19.
 * Confidence: low
 */
/* 128-bit unsigned division. Registers x3:x4 = dividend (hi:lo), x5:x6 = divisor.
 * Returns quotient in x20 (low) / x19 (high); remainder low in x21.
 * Decompiler collapses register-forwarding; keep the panic + result structure. */
void sk_udivti3_core(void)
{
    /* out-of-range helpers implement the long-division steps */
    FUN_00351e20();
    if (/* in_x5 */ 0 == 0 && /* in_x6 */ 0 == 0) {
        FUN_00355754((uint64_t)(uintptr_t)"Division by zero");
        FUN_001a89a8(0, 0, 0);
        FUN_00355c00();
        FUN_00350d94(0x4d9);
        FUN_0006f768();
        FUN_001afa84();   /* no-return */
    }
    /* long division by repeated normalization (see sk_u128_shr_logical / sk_u128_shr_arith helpers) */
    FUN_00351d30(0, 0);
}


/* FUN_00312f80 @ 0x00312f80   (est. sk_udivti3_ret)
 * Ghidra: FUN_00312f80
 * Unsigned 128-bit divide returning {lo,hi} via x3/x4; calls FUN_00312d08.
 * Confidence: low
 */
sk_u128_t sk_udivti3_ret(void)
{
    sk_u128_t r;
    FUN_00359e8c();
    sk_udivti3_core();
    r.lo = 0; r.hi = 0;   /* register-forwarded result */
    return r;
}


/* FUN_00312fd0 @ 0x00312fd0   (est. sk_udivti3_ret2)
 * Ghidra: FUN_00312fd0
 * Unsigned 128-bit divide variant; FUN_00312d08.
 * Confidence: low
 */
sk_u128_t sk_udivti3_ret2(void)
{
    sk_u128_t r;
    FUN_00359e8c();
    FUN_00355528();
    sk_udivti3_core();
    r.lo = 0; r.hi = 0;
    return r;
}


/* FUN_0031301c @ 0x0031301c   (est. sk_multi3_full)
 * Ghidra: FUN_0031301c
 * Full 128x128->128 multiply with carries; sends 256-bit partial to FUN_00359284.
 * Confidence: high
 */
void sk_multi3_full(uint64_t a_lo, uint64_t a_hi, uint64_t b_lo, uint64_t b_hi)
{
    /* standard 128-bit multiply: split into 64-bit pieces */
    __uint128_t lolo = (__uint128_t)a_lo * b_lo;
    __uint128_t lohi = (__uint128_t)a_lo * b_hi;
    __uint128_t hilo = (__uint128_t)a_hi * b_lo;
    __uint128_t hihi = (__uint128_t)a_hi * b_hi;
    uint64_t c1 = (uint64_t)(lolo >> 64);
    uint64_t mid = (uint64_t)lohi + (uint64_t)hilo + c1;
    uint64_t carry = (uint64_t)(lohi >> 64) + (uint64_t)(hilo >> 64) + (mid < c1 || (mid - c1 < (uint64_t)hilo) ? 1 : 0);
    FUN_00359284((uint64_t)lolo, mid, (uint64_t)hihi + (uint64_t)(lohi >> 64) + (uint64_t)(hilo >> 64) + carry + (uint64_t)(lolo >> 64));
}


/* FUN_00313068 @ 0x00313068   (est. sk_udivmodti4)
 * Ghidra: FUN_00313068
 * Unsigned 128/128 divide with remainder via FUN_003130bc; packs {lo,hi}.
 * Confidence: low
 */
sk_u128_t sk_udivmodti4(uint64_t a, uint64_t b, uint64_t c, uint64_t d)
{
    /* 128/128 divide-with-remainder; quotient/remainder register-forwarded */
    sk_u128_t r = {0, 0};
    return r;
}


/* FUN_003130bc @ 0x003130bc   (est. sk_udivmodti4_core)
 * Ghidra: FUN_003130bc
 * 128/128 unsigned divide-with-remainder core. Panics 'Division by zero' 0x501 and 'Division results in an overflow' 0x504.
 * Confidence: low
 */
void sk_udivmodti4_core(sk_u128_t *q, sk_u128_t *r, uint64_t n0, uint64_t n1,
                             uint64_t n2, uint64_t d0, uint64_t d1)
{
    FUN_00351e20();
    if (d1 == 0 && /* in_stack */ 0 == 0) {
        FUN_00355754((uint64_t)(uintptr_t)"Division by zero");
        FUN_001a89a8(0, 0, 0);
        FUN_00355c00();
        FUN_00350d94(0x501);
        FUN_0006f768();
        FUN_001afa84();   /* no-return */
    }
    if (n2 > d1 || (n2 == d1 && n1 > 0)) {   /* quotient would overflow 128 bits */
        FUN_001a89a8((uint64_t)(uintptr_t)"Division results in an overflow", 0x1f, 1);
        FUN_00355c00();
        FUN_00350d94(0x504);
        FUN_001afa84();   /* no-return */
    }
    if (n2 == 0 && n1 == 0) {
        FUN_00352498();
        sk_udivti3_core();
        return;
    }
    /* normalized long division via sk_u128_shr_logical / sk_u128_shr_arith shift helpers */
    FUN_00351d30(0, 0);
}


/* FUN_003135ac @ 0x003135ac   (est. sk_u128_shl)
 * Ghidra: FUN_003135ac
 * Shift left of 128-bit (hi:lo) by sh; writes lo, returns hi.
 * Confidence: high
 */
uint64_t sk_u128_shl(uint64_t *out_lo, uint64_t hi, uint64_t lo, uint64_t sh)
{
    uint64_t l = lo << (sh & 0x3f);
    uint64_t h = (hi << (sh & 0x3f)) | ((lo >> 1) >> (uint64_t)(~sh & 0x3f));
    uint64_t rl = l;
    if (0x3f < sh) { rl = 0; h = l; }
    *out_lo = rl;
    return h;
}


/* FUN_003135dc @ 0x003135dc   (est. sk_u128_shl7)
 * Ghidra: FUN_003135dc
 * Shift left of 128-bit (hi:lo) by sh&0x7f; writes lo, returns hi.
 * Confidence: high
 */
uint64_t sk_u128_shl7(uint64_t *out_lo, uint64_t hi, uint64_t lo, uint64_t sh)
{
    uint64_t u = sh & 0x7f;
    uint64_t h = hi;
    if (u != 0) {
        hi = (lo >> (uint64_t)(-u & 0x3f)) | (hi << (sh & 0x3f));
        h = lo << (sh & 0x3f);
    }
    uint64_t rl = lo << (sh & 0x3f);
    uint64_t rh = 0;
    if (u < 0x40) { rl = hi; rh = h; }
    *out_lo = rh;
    return rl;
}


/* FUN_0031361c @ 0x0031361c   (est. sk_ldexp_guard1)
 * Ghidra: FUN_0031361c
 * Guard: if hi/lo (param_3,param_4) nonzero compute FUN_003583a4 else panic 1/0x49e8c.
 * Confidence: low
 */
sk_u128_t sk_ldexp_guard1(uint64_t a, uint64_t b, int64_t hi, int64_t lo)
{
    if (lo != 0 || hi != 0) {
        sk_u128_t r;
        r.lo = FUN_003583a4();   /* register-forwarded 128-bit result */
        r.hi = 0;
        return r;
    }
    FUN_003488bc(1);
    FUN_00349e8c();
    FUN_00351be0();
    FUN_001afe4c();   /* no-return */
    return (sk_u128_t){0, 0};
}


/* FUN_003136d0 @ 0x003136d0   (est. sk_ldexp_guard3)
 * Ghidra: FUN_003136d0
 * Guard: if hi/lo (param_3,param_4) nonzero compute FUN_003583a4 else panic 1/0x49e8c.
 * Confidence: low
 */
sk_u128_t sk_ldexp_guard3(uint64_t a, uint64_t b, int64_t hi, int64_t lo)
{
    if (lo != 0 || hi != 0) {
        sk_u128_t r;
        r.lo = FUN_003583a4();   /* register-forwarded 128-bit result */
        r.hi = 0;
        return r;
    }
    FUN_003488bc(1);
    FUN_00349e8c();
    FUN_00351be0();
    FUN_001afe4c();   /* no-return */
    return (sk_u128_t){0, 0};
}


/* FUN_00313674 @ 0x00313674   (est. sk_ldexp_guard2)
 * Ghidra: FUN_00313674
 * Guard: if nonzero FUN_00357074 writes 128-bit result else panic.
 * Confidence: low
 */
void sk_ldexp_guard2(sk_u128_t *out, int64_t hi, int64_t lo)
{
    if (lo != 0 || hi != 0) {
        FUN_00357074();
        out->lo = 0; out->hi = 0;
        return;
    }
    FUN_003488bc(1);
    FUN_00349e8c();
    FUN_00351be0();
    FUN_001afe4c();   /* no-return */
}


/* FUN_00313728 @ 0x00313728   (est. sk_ldexp_guard4)
 * Ghidra: FUN_00313728
 * Guard: if nonzero FUN_00357074 writes 128-bit result else panic.
 * Confidence: low
 */
void sk_ldexp_guard4(sk_u128_t *out, int64_t hi, int64_t lo)
{
    if (lo != 0 || hi != 0) {
        FUN_00357074();
        out->lo = 0; out->hi = 0;
        return;
    }
    FUN_003488bc(1);
    FUN_00349e8c();
    FUN_00351be0();
    FUN_001afe4c();   /* no-return */
}


/* FUN_003137fc @ 0x003137fc   (est. sk_mul_acc128)
 * Ghidra: FUN_003137fc
 * FUN_0008409c; multiplies via FUN_0031301c into x21, forwards x20 words.
 * Confidence: medium
 */
void sk_mul_acc128(sk_u128_t *out, uint64_t *acc, uint64_t *m)
{
    FUN_0008409c();
    /* register-forwarded 128-bit multiply (sk_multi3_full) */
    sk_multi3_full(m[0], m[1], ((uint64_t *)0)[2], ((uint64_t *)0)[3]);
    *out = (sk_u128_t){0, 0};
    acc[0] = ((uint64_t *)0)[0];
    acc[1] = ((uint64_t *)0)[1];
}


/* FUN_003138a8 @ 0x003138a8   (est. sk_fp_init_a)
 * Ghidra: FUN_003138a8
 * Floating init sequence FUN_00349fcc/00342b68/0034ea7c + FUN_0024304c/0024320c.
 * Confidence: low
 */
void sk_fp_init_a(void)
{
    FUN_00349fcc();
    FUN_00342b68();
    FUN_0034ea7c();
    FUN_0024304c();
}


/* FUN_00313958 @ 0x00313958   (est. sk_fp_init_b)
 * Ghidra: FUN_00313958
 * Floating init sequence FUN_00349fcc/00342b68/0034ea7c + FUN_0024304c/0024320c.
 * Confidence: low
 */
void sk_fp_init_b(void)
{
    FUN_00349fcc();
    FUN_00342b68();
    FUN_0034ea7c();
    FUN_0024304c();
}


/* FUN_00313900 @ 0x00313900   (est. sk_ld128_alt)
 * Ghidra: FUN_00313900
 * Loads 128-bit via FUN_002e6330.
 * Confidence: medium
 */
void sk_ld128_alt(sk_u128_t *out)
{
    out->lo = FUN_002e6330();
    out->hi = 0;
}


/* FUN_003139e8 @ 0x003139e8   (est. sk_ldexp_variant)
 * Ghidra: FUN_003139e8
 * FUN_0034ed08 then FUN_00311cf8 with FUN_002e62f0 results; float/exponent assembly.
 * Confidence: low
 */
void sk_ldexp_variant(sk_u128_t *out)
{
    FUN_0034ed08();
    uint64_t v = FUN_002e62f0(0);
    FUN_00311cf8(((uint64_t *)0)[0], ((uint64_t *)0)[1], v, 0);
    FUN_0006b674();
    v = FUN_002e62f0(1);
    FUN_00350974(v, 0);
    out->lo = FUN_00311cf8(0, 0, 0, 0);
    out->hi = 0;
}


/* FUN_00313a40 @ 0x00313a40   (est. sk_i128_to_double)
 * Ghidra: FUN_00313a40
 * Signed int128->double conversion (see shared skeleton).
 * Confidence: low
 */
/* Signed 128-bit integer <-> double conversion. Control flow:
 *   - sign bit (param_3 bit 63) drives a negate via sk_i128_neg
 *   - exponent extracted from the float; range checks against 0x40, 0x80, 0x81
 *     decide fast-path (FUN_00310a44 / FUN_003109b4) vs slow path
 *     (FUN_00352950 slow-rounded), clamping to 0x80 / 0xffffffffffffff80 on
 *     overflow; the final shift uses sk_u128_shr_logical / sk_u128_shr_arith / sk_u128_shl_ret.
 *   - overflow paths panic via FUN_003523f0 (no return).
 * The decompiler collapses the FP dispatch into indirect calls
 * ((*DAT_00658c00)() and register-forwarded code pointers); only the
 * recognizable structure is preserved below. Confidence: low. */
void sk_i128_to_double(void)
{
    FUN_0008e518();
    FUN_0034ab20();
    FUN_0007c1a4();
    /* sign + exponent normalization; range checks vs 0x40/0x80/0x81 */
    if ((/* in_x3 */ 0L & 1) == 0) {
        FUN_0034a43c();
    } else {
        FUN_00310a44();
    }
    FUN_003517b4();
    FUN_002e62f0(0);
    /* final 128-bit shift normalization */
    FUN_0035723c(0x7f);
    FUN_00355998();
    FUN_0008e500(0);
}


/* FUN_00314644 @ 0x00314644   (est. sk_i128_to_double_00314644)
 * Ghidra: FUN_00314644
 * Signed int128->double conversion (see shared skeleton).
 * Confidence: low
 */
/* Signed 128-bit integer <-> double conversion. Control flow:
 *   - sign bit (param_3 bit 63) drives a negate via sk_i128_neg
 *   - exponent extracted from the float; range checks against 0x40, 0x80, 0x81
 *     decide fast-path (FUN_00310a44 / FUN_003109b4) vs slow path
 *     (FUN_00352950 slow-rounded), clamping to 0x80 / 0xffffffffffffff80 on
 *     overflow; the final shift uses sk_u128_shr_logical / sk_u128_shr_arith / sk_u128_shl_ret.
 *   - overflow paths panic via FUN_003523f0 (no return).
 * The decompiler collapses the FP dispatch into indirect calls
 * ((*DAT_00658c00)() and register-forwarded code pointers); only the
 * recognizable structure is preserved below. Confidence: low. */
void sk_i128_to_double_00314644(void)
{
    FUN_0008e518();
    FUN_0034ab20();
    FUN_0007c1a4();
    /* sign + exponent normalization; range checks vs 0x40/0x80/0x81 */
    if ((/* in_x3 */ 0L & 1) == 0) {
        FUN_0034a43c();
    } else {
        FUN_00310a44();
    }
    FUN_003517b4();
    FUN_002e62f0(0);
    /* final 128-bit shift normalization */
    FUN_0035723c(0x7f);
    FUN_00355998();
    FUN_0008e500(0);
}


/* FUN_003180bc @ 0x003180bc   (est. sk_i128_to_double_003180bc)
 * Ghidra: FUN_003180bc
 * Signed int128->double conversion (see shared skeleton).
 * Confidence: low
 */
/* Signed 128-bit integer <-> double conversion. Control flow:
 *   - sign bit (param_3 bit 63) drives a negate via sk_i128_neg
 *   - exponent extracted from the float; range checks against 0x40, 0x80, 0x81
 *     decide fast-path (FUN_00310a44 / FUN_003109b4) vs slow path
 *     (FUN_00352950 slow-rounded), clamping to 0x80 / 0xffffffffffffff80 on
 *     overflow; the final shift uses sk_u128_shr_logical / sk_u128_shr_arith / sk_u128_shl_ret.
 *   - overflow paths panic via FUN_003523f0 (no return).
 * The decompiler collapses the FP dispatch into indirect calls
 * ((*DAT_00658c00)() and register-forwarded code pointers); only the
 * recognizable structure is preserved below. Confidence: low. */
void sk_i128_to_double_003180bc(void)
{
    FUN_0008e518();
    FUN_0034ab20();
    FUN_0007c1a4();
    /* sign + exponent normalization; range checks vs 0x40/0x80/0x81 */
    if ((/* in_x3 */ 0L & 1) == 0) {
        FUN_0034a43c();
    } else {
        FUN_00310a44();
    }
    FUN_003517b4();
    FUN_002e62f0(0);
    /* final 128-bit shift normalization */
    FUN_0035723c(0x7f);
    FUN_00355998();
    FUN_0008e500(0);
}


/* FUN_003140c4 @ 0x003140c4   (est. sk_u128_to_double)
 * Ghidra: FUN_003140c4
 * Unsigned int128->double conversion (shared skeleton, FUN_003135dc shift).
 * Confidence: low
 */
/* Signed 128-bit integer <-> double conversion. Control flow:
 *   - sign bit (param_3 bit 63) drives a negate via sk_i128_neg
 *   - exponent extracted from the float; range checks against 0x40, 0x80, 0x81
 *     decide fast-path (FUN_00310a44 / FUN_003109b4) vs slow path
 *     (FUN_00352950 slow-rounded), clamping to 0x80 / 0xffffffffffffff80 on
 *     overflow; the final shift uses sk_u128_shr_logical / sk_u128_shr_arith / sk_u128_shl_ret.
 *   - overflow paths panic via FUN_003523f0 (no return).
 * The decompiler collapses the FP dispatch into indirect calls
 * ((*DAT_00658c00)() and register-forwarded code pointers); only the
 * recognizable structure is preserved below. Confidence: low. */
void sk_u128_to_double(void)
{
    FUN_0008e518();
    FUN_0034ab20();
    FUN_0007c1a4();
    /* sign + exponent normalization; range checks vs 0x40/0x80/0x81 */
    if ((/* in_x3 */ 0L & 1) == 0) {
        FUN_0034a43c();
    } else {
        FUN_00310a44();
    }
    FUN_003517b4();
    FUN_002e62f0(0);
    /* final 128-bit shift normalization */
    FUN_0035723c(0x7f);
    FUN_00355998();
    FUN_0008e500(0);
}


/* FUN_00314cac @ 0x00314cac   (est. sk_u128_to_double_00314cac)
 * Ghidra: FUN_00314cac
 * Unsigned int128->double conversion (shared skeleton, FUN_003135dc shift).
 * Confidence: low
 */
/* Signed 128-bit integer <-> double conversion. Control flow:
 *   - sign bit (param_3 bit 63) drives a negate via sk_i128_neg
 *   - exponent extracted from the float; range checks against 0x40, 0x80, 0x81
 *     decide fast-path (FUN_00310a44 / FUN_003109b4) vs slow path
 *     (FUN_00352950 slow-rounded), clamping to 0x80 / 0xffffffffffffff80 on
 *     overflow; the final shift uses sk_u128_shr_logical / sk_u128_shr_arith / sk_u128_shl_ret.
 *   - overflow paths panic via FUN_003523f0 (no return).
 * The decompiler collapses the FP dispatch into indirect calls
 * ((*DAT_00658c00)() and register-forwarded code pointers); only the
 * recognizable structure is preserved below. Confidence: low. */
void sk_u128_to_double_00314cac(void)
{
    FUN_0008e518();
    FUN_0034ab20();
    FUN_0007c1a4();
    /* sign + exponent normalization; range checks vs 0x40/0x80/0x81 */
    if ((/* in_x3 */ 0L & 1) == 0) {
        FUN_0034a43c();
    } else {
        FUN_00310a44();
    }
    FUN_003517b4();
    FUN_002e62f0(0);
    /* final 128-bit shift normalization */
    FUN_0035723c(0x7f);
    FUN_00355998();
    FUN_0008e500(0);
}


/* FUN_00317b50 @ 0x00317b50   (est. sk_u128_to_double_00317b50)
 * Ghidra: FUN_00317b50
 * Unsigned int128->double conversion (shared skeleton, FUN_003135dc shift).
 * Confidence: low
 */
/* Signed 128-bit integer <-> double conversion. Control flow:
 *   - sign bit (param_3 bit 63) drives a negate via sk_i128_neg
 *   - exponent extracted from the float; range checks against 0x40, 0x80, 0x81
 *     decide fast-path (FUN_00310a44 / FUN_003109b4) vs slow path
 *     (FUN_00352950 slow-rounded), clamping to 0x80 / 0xffffffffffffff80 on
 *     overflow; the final shift uses sk_u128_shr_logical / sk_u128_shr_arith / sk_u128_shl_ret.
 *   - overflow paths panic via FUN_003523f0 (no return).
 * The decompiler collapses the FP dispatch into indirect calls
 * ((*DAT_00658c00)() and register-forwarded code pointers); only the
 * recognizable structure is preserved below. Confidence: low. */
void sk_u128_to_double_00317b50(void)
{
    FUN_0008e518();
    FUN_0034ab20();
    FUN_0007c1a4();
    /* sign + exponent normalization; range checks vs 0x40/0x80/0x81 */
    if ((/* in_x3 */ 0L & 1) == 0) {
        FUN_0034a43c();
    } else {
        FUN_00310a44();
    }
    FUN_003517b4();
    FUN_002e62f0(0);
    /* final 128-bit shift normalization */
    FUN_0035723c(0x7f);
    FUN_00355998();
    FUN_0008e500(0);
}


/* FUN_00318718 @ 0x00318718   (est. sk_u128_to_double_00318718)
 * Ghidra: FUN_00318718
 * Unsigned int128->double conversion (shared skeleton, FUN_003135dc shift).
 * Confidence: low
 */
/* Signed 128-bit integer <-> double conversion. Control flow:
 *   - sign bit (param_3 bit 63) drives a negate via sk_i128_neg
 *   - exponent extracted from the float; range checks against 0x40, 0x80, 0x81
 *     decide fast-path (FUN_00310a44 / FUN_003109b4) vs slow path
 *     (FUN_00352950 slow-rounded), clamping to 0x80 / 0xffffffffffffff80 on
 *     overflow; the final shift uses sk_u128_shr_logical / sk_u128_shr_arith / sk_u128_shl_ret.
 *   - overflow paths panic via FUN_003523f0 (no return).
 * The decompiler collapses the FP dispatch into indirect calls
 * ((*DAT_00658c00)() and register-forwarded code pointers); only the
 * recognizable structure is preserved below. Confidence: low. */
void sk_u128_to_double_00318718(void)
{
    FUN_0008e518();
    FUN_0034ab20();
    FUN_0007c1a4();
    /* sign + exponent normalization; range checks vs 0x40/0x80/0x81 */
    if ((/* in_x3 */ 0L & 1) == 0) {
        FUN_0034a43c();
    } else {
        FUN_00310a44();
    }
    FUN_003517b4();
    FUN_002e62f0(0);
    /* final 128-bit shift normalization */
    FUN_0035723c(0x7f);
    FUN_00355998();
    FUN_0008e500(0);
}


/* FUN_00315264 @ 0x00315264   (est. sk_ld128_aux)
 * Ghidra: FUN_00315264
 * FUN_00353510 then FUN_00231c2c loads 128-bit.
 * Confidence: medium
 */
void sk_ld128_aux(sk_u128_t *out)
{
    FUN_00353510();
    out->lo = FUN_00231c2c();
    out->hi = 0;
}


/* FUN_003152b8 @ 0x003152b8   (est. sk_neg_checked)
 * Ghidra: FUN_003152b8
 * Negates a value with overflow check; SoftwareBreakpoint on MIN negate.
 * Confidence: medium
 */
void sk_neg_checked(uint64_t *out)
{
    uint64_t v = FUN_00357ca0();
    FUN_0034c444(v);
    if ((FUN_002e6474() & 1) == 0) {
        FUN_0034c444(v);
        int64_t n = (int64_t)FUN_002e648c(0, 0, 0, 0);
        FUN_003553f4();
        *out = (uint64_t)n;
    } else {
        int64_t n = (int64_t)FUN_002e648c(0, 0, 0, 0);
        if (-n < 0) __builtin_trap();  /* MIN negate trap (SoftwareBreakpoint 1 @0x315318) */
        *out = (uint64_t)(-n);
    }
    FUN_00357c44();
}


/* FUN_00315374 @ 0x00315374   (est. sk_neg128_abs)
 * Ghidra: FUN_00315374
 * Negates 128-bit if param_2[0]<0 else FUN_002e6410; stores result.
 * Confidence: medium
 */
void sk_neg128_abs(sk_u128_t *out, int64_t *in)
{
    if (*in < 0) {
        out->lo = FUN_002e648c(((uint64_t *)0)[0], ((uint64_t *)0)[1], (uint64_t)(-*in), 0);
        out->hi = 0;
    } else {
        out->lo = FUN_002e6410();
        out->hi = 0;
    }
}


/* FUN_003153f4 @ 0x003153f4   (est. sk_math_op2a)
 * Ghidra: FUN_003153f4
 * FUN_00352764 + FUN_002d49d0/f4.
 * Confidence: medium
 */
void sk_math_op2a(void)
{
    FUN_00352764();
    FUN_002d49d0();
}


/* FUN_0031540c @ 0x0031540c   (est. sk_math_op2b)
 * Ghidra: FUN_0031540c
 * FUN_00352764 + FUN_002d49d0/f4.
 * Confidence: medium
 */
void sk_math_op2b(void)
{
    FUN_00352764();
    FUN_002d49d0();
}


/* FUN_00315424 @ 0x00315424   (est. sk_math_binop_a)
 * Ghidra: FUN_00315424
 * Binary op FUN_002d49f4 on 128-bit pair + FUN_00356d20.
 * Confidence: medium
 */
void sk_math_binop_a(sk_u128_t *a, sk_u128_t *b)
{
    FUN_002d49f4(b->lo, b->hi, a->lo, a->hi);
    FUN_00356d20();
}


/* FUN_00315428 @ 0x00315428   (est. sk_math_binop_b)
 * Ghidra: FUN_00315428
 * Binary op FUN_002d49f4 on 128-bit pair + FUN_00356d20.
 * Confidence: medium
 */
void sk_math_binop_b(sk_u128_t *a, sk_u128_t *b)
{
    FUN_002d49f4(b->lo, b->hi, a->lo, a->hi);
    FUN_00356d20();
}


/* FUN_00315448 @ 0x00315448   (est. sk_math_binop_c)
 * Ghidra: FUN_00315448
 * FUN_00352764 + FUN_002d49f4 + FUN_00356d20.
 * Confidence: medium
 */
void sk_math_binop_c(void)
{
    FUN_00352764();
    FUN_002d49f4(0, 0, 0, 0);
    FUN_00356d20();
}


/* FUN_0031544c @ 0x0031544c   (est. sk_math_binop_d)
 * Ghidra: FUN_0031544c
 * FUN_00352764 + FUN_002d49f4 + FUN_00356d20.
 * Confidence: medium
 */
void sk_math_binop_d(void)
{
    FUN_00352764();
    FUN_002d49f4(0, 0, 0, 0);
    FUN_00356d20();
}


/* FUN_0031547c @ 0x0031547c   (est. sk_math_unop_a)
 * Ghidra: FUN_0031547c
 * FUN_00311ca0 on x20 128-bit pair.
 * Confidence: medium
 */
void sk_math_unop_a(void)
{
    FUN_00311ca0(((uint64_t *)0)[0], ((uint64_t *)0)[1]);
}


/* FUN_00315480 @ 0x00315480   (est. sk_math_unop_b)
 * Ghidra: FUN_00315480
 * FUN_00311ca0 on x20 128-bit pair.
 * Confidence: medium
 */
void sk_math_unop_b(void)
{
    FUN_00311ca0(((uint64_t *)0)[0], ((uint64_t *)0)[1]);
}


/* FUN_0031549c @ 0x0031549c   (est. sk_math_seq)
 * Ghidra: FUN_0031549c
 * Sequence of FP helpers FUN_001a84f4/003567c8/002298d4/00355458/001a8564.
 * Confidence: low
 */
void sk_math_seq(void)
{
    uint8_t buf[72];
    FUN_001a84f4((uint64_t)(uintptr_t)buf);
    FUN_003567c8();
    FUN_002298d4();
    FUN_00355458();
    FUN_002298d4();
    FUN_001a8564();
}


/* FUN_003154ec @ 0x003154ec   (est. sk_u128_sub)
 * Ghidra: FUN_003154ec
 * 128-bit subtract with borrow; result sent to FUN_00359380 or FUN_00353d34.
 * Confidence: medium
 */
void sk_u128_sub(uint64_t a_lo, uint64_t a_hi, uint64_t b_lo, uint64_t b_hi)
{
    if (b_lo < a_lo) {
        if ((int64_t)b_hi - a_hi < 0)
            FUN_00359380(b_lo - a_lo, (b_hi - a_hi) - 1);
    } else if ((int64_t)b_hi - a_hi < 0) {
        FUN_00353d34(b_lo - a_lo, a_hi, 1);
    }
}


/* FUN_0031552c @ 0x0031552c   (est. sk_sub_checked)
 * Ghidra: FUN_0031552c
 * 128-bit checked subtract; on underflow panics 'Overflow in' (0x262).
 * Confidence: medium
 */
void sk_sub_checked(sk_u128_t *a, uint64_t b_lo, int64_t b_hi)
{
    uint64_t h = a->hi - b_hi;
    if (a->lo < b_lo) {
        if (h != 0x8000000000000000ULL && !((int64_t)a->hi - b_hi < 0))
            h -= 1;
        else {
            FUN_0034def4(); FUN_0034951c(); FUN_00349e8c(); FUN_00351be0(); FUN_001afe4c();
        }
        a->lo -= b_lo;
        a->hi = h;
    } else if ((int64_t)a->hi - b_hi >= 0) {
        a->lo -= b_lo;
        a->hi = h;
    } else {
        FUN_0034def4(); FUN_0034951c(); FUN_00349e8c(); FUN_00351be0(); FUN_001afe4c();
    }
}


/* FUN_003155b8 @ 0x003155b8   (est. sk_add_checked)
 * Ghidra: FUN_003155b8
 * 128-bit checked add; on overflow panics 'Overflow in' (0x26e).
 * Confidence: medium
 */
void sk_add_checked(sk_u128_t *a, uint64_t b_lo, int64_t b_hi)
{
    uint64_t lo = a->lo;
    int64_t hi = a->hi + b_hi;
    if (((int64_t)a->hi >= 0 && b_hi >= 0 && hi < 0) ||
        (a->hi >= 0 && b_hi < 0)) {
        /* overflow path */
        if (!(hi != 0x7fffffffffffffffLL || lo + b_lo < lo))
            goto ok;
        FUN_0034def4(); FUN_0034951c(); FUN_00349e8c(); FUN_00351be0(); FUN_001afe4c();
    }
ok:
    a->lo = lo + b_lo;
    a->hi = (uint64_t)(hi + (lo + b_lo < lo));
}


/* FUN_0031562c @ 0x0031562c   (est. sk_indirect_ld128_a)
 * Ghidra: FUN_0031562c
 * FUN_00350240 then calls indirect fn in x4, stores 128-bit.
 * Confidence: low
 */
void sk_indirect_ld128_a(sk_u128_t *out)
{
    FUN_00350240();
    out->lo = ((code_t)0)();   /* indirect fn pointer in x4 */
    out->hi = 0;
}


/* FUN_003171d0 @ 0x003171d0   (est. sk_indirect_ld128_b)
 * Ghidra: FUN_003171d0
 * FUN_00350240 then calls indirect fn in x4, stores 128-bit.
 * Confidence: low
 */
void sk_indirect_ld128_b(sk_u128_t *out)
{
    FUN_00350240();
    out->lo = ((code_t)0)();   /* indirect fn pointer in x4 */
    out->hi = 0;
}


/* FUN_00315658 @ 0x00315658   (est. sk_add_checked_msg_a)
 * Ghidra: FUN_00315658
 * Checked add wrapper: FUN_003155b8 with 'Overflow in ...' (0x26e).
 * Confidence: medium
 */
void sk_add_checked_msg_a(sk_u128_t *a, sk_u128_t *b)
{
    sk_add_checked(a, b->lo, (int64_t)b->hi);   /* panic "Overflow in" 0x26e */
}


/* FUN_0031565c @ 0x0031565c   (est. sk_add_checked_msg_b)
 * Ghidra: FUN_0031565c
 * Checked add wrapper: FUN_003155b8 with 'Overflow in ...' (0x26e).
 * Confidence: medium
 */
void sk_add_checked_msg_b(sk_u128_t *a, sk_u128_t *b)
{
    sk_add_checked(a, b->lo, (int64_t)b->hi);   /* panic "Overflow in" 0x26e */
}


/* FUN_003156a0 @ 0x003156a0   (est. sk_sub_checked_msg_a)
 * Ghidra: FUN_003156a0
 * Checked sub wrapper: FUN_0031552c with 'Overflow in ...' (0x262).
 * Confidence: medium
 */
void sk_sub_checked_msg_a(sk_u128_t *a, sk_u128_t *b)
{
    sk_sub_checked(a, b->lo, (int64_t)b->hi);   /* panic "Overflow in" 0x262 */
}


/* FUN_003156a4 @ 0x003156a4   (est. sk_sub_checked_msg_b)
 * Ghidra: FUN_003156a4
 * Checked sub wrapper: FUN_0031552c with 'Overflow in ...' (0x262).
 * Confidence: medium
 */
void sk_sub_checked_msg_b(sk_u128_t *a, sk_u128_t *b)
{
    sk_sub_checked(a, b->lo, (int64_t)b->hi);   /* panic "Overflow in" 0x262 */
}


/* FUN_003156d0 @ 0x003156d0   (est. sk_i128_neg)
 * Ghidra: FUN_003156d0
 * 128-bit two's complement negation.
 * Confidence: high
 */
sk_u128_t sk_i128_neg(int64_t lo, int64_t hi)
{
    int64_t h = -(hi + (lo != 0));
    int64_t l = -lo;
    if (hi >= 0) { h = hi; l = lo; }
    sk_u128_t r;
    r.hi = (uint64_t)h;
    r.lo = (uint64_t)l;
    return r;
}


/* FUN_003156e8 @ 0x003156e8   (est. sk_neg_panic_if_neg)
 * Ghidra: FUN_003156e8
 * If param_2 < 0, panic (no return); else return.
 * Confidence: medium
 */
void sk_neg_panic_if_neg(uint64_t a, int64_t b)
{
    if (b >= 0) return;
    FUN_00347fb4();
    FUN_003523f0(0);   /* no-return */
}


/* FUN_0031570c @ 0x0031570c   (est. sk_double_to_i128)
 * Ghidra: FUN_0031570c
 * double->signed int128 conversion (shared FP skeleton, FUN_003156d0 negate).
 * Confidence: low
 */
/* Signed 128-bit integer <-> double conversion. Control flow:
 *   - sign bit (param_3 bit 63) drives a negate via sk_i128_neg
 *   - exponent extracted from the float; range checks against 0x40, 0x80, 0x81
 *     decide fast-path (FUN_00310a44 / FUN_003109b4) vs slow path
 *     (FUN_00352950 slow-rounded), clamping to 0x80 / 0xffffffffffffff80 on
 *     overflow; the final shift uses sk_u128_shr_logical / sk_u128_shr_arith / sk_u128_shl_ret.
 *   - overflow paths panic via FUN_003523f0 (no return).
 * The decompiler collapses the FP dispatch into indirect calls
 * ((*DAT_00658c00)() and register-forwarded code pointers); only the
 * recognizable structure is preserved below. Confidence: low. */
void sk_double_to_i128(void)
{
    FUN_0008e518();
    FUN_0034ab20();
    FUN_0007c1a4();
    /* sign + exponent normalization; range checks vs 0x40/0x80/0x81 */
    if ((/* in_x3 */ 0L & 1) == 0) {
        FUN_0034a43c();
    } else {
        FUN_00310a44();
    }
    FUN_003517b4();
    FUN_002e62f0(0);
    /* final 128-bit shift normalization */
    FUN_0035723c(0x7f);
    FUN_00355998();
    FUN_0008e500(0);
}


/* FUN_003162cc @ 0x003162cc   (est. sk_panic_noreturn)
 * Ghidra: FUN_003162cc
 * Panic stub: FUN_003482c4 + FUN_003523f0 (no return).
 * Confidence: medium
 */
void sk_panic_noreturn(void)
{
    FUN_003482c4();
    FUN_003523f0(0);   /* no-return */
}


/* FUN_003162e0 @ 0x003162e0   (est. sk_mul128_low_signed)
 * Ghidra: FUN_003162e0
 * Signed 128x128 multiply; returns low 64 bits; negates result if sign mismatch.
 * Confidence: medium
 */
int64_t sk_mul128_low_signed(uint64_t a, uint64_t b, int64_t hi, uint64_t sh)
{
    bool neg = false;
    if (sh == 0) {
        neg = false;
        if (hi >= 0 || /* param_3 */ 0 == 0) goto done;
    } else {
        if (hi != 0) sh ^= hi;
        if (hi < 0) { neg = false; goto done; }
    }
    neg = (hi != 0 || /* param_4 */ 0 != 0);
done:
    FUN_00355968(0);
    sk_i128_neg(0, 0);          /* register-forwarded negate */
    sk_multi3(0, 0, 0, 0);      /* register-forwarded 128-bit multiply */
    int64_t r = 0;              /* low 64 of register-forwarded sk_multi3 */
    if (neg) r = -r;
    return r;
}


/* FUN_003163d8 @ 0x003163d8   (est. sk_checked_op)
 * Ghidra: FUN_003163d8
 * Runs op fn on 128-bit value; if low-bit set (overflow flag) panics 0x2aa.
 * Confidence: medium
 */
void sk_checked_op(sk_u128_t *out, uint64_t a, uint64_t b, sk_u128_t (*op)(uint64_t,uint64_t,uint64_t,uint64_t), uint64_t code)
{
    uint64_t flag = out->lo;
    sk_u128_t r = op(a, b, flag, out->hi);
    if ((flag & 1) == 0) {
        *out = r;
        return;
    }
    FUN_0035047c();
    FUN_0034951c();
    FUN_00349e8c();
    FUN_00351be0();
    FUN_001afe4c();   /* no-return */
}


/* FUN_0031644c @ 0x0031644c   (est. sk_ld128_store_flag)
 * Ghidra: FUN_0031644c
 * Loads via FUN_0031570c, stores, writes byte param_4 at +8.
 * Confidence: medium
 */
void sk_ld128_store_flag(sk_u128_t *out, uint64_t a, uint64_t b, uint8_t flag)
{
    sk_double_to_i128();
    out->lo = 0; out->hi = 0;   /* register-forwarded conversion */
    ((uint8_t *)out)[8] = flag;
}


/* FUN_00316478 @ 0x00316478   (est. sk_ld128_neg)
 * Ghidra: FUN_00316478
 * FUN_00353510 then FUN_003156d0 negate.
 * Confidence: medium
 */
void sk_ld128_neg(sk_u128_t *out)
{
    FUN_00353510();
    sk_u128_t rn = sk_i128_neg(0, 0);
    *out = rn;
}


/* FUN_003164b8 @ 0x003164b8   (est. sk_mul_checked_msg_a)
 * Ghidra: FUN_003164b8
 * Checked multiply via FUN_003163d8 + FUN_003162e0, code 0x2aa.
 * Confidence: medium
 */
void sk_mul_checked_msg_a(sk_u128_t *out, sk_u128_t *b)
{
    sk_checked_op(out, b->lo, b->hi, (sk_u128_t (*)(uint64_t,uint64_t,uint64_t,uint64_t))sk_mul128_low_signed, 0x2aa);
}


/* FUN_003164bc @ 0x003164bc   (est. sk_mul_checked_msg_b)
 * Ghidra: FUN_003164bc
 * Checked multiply via FUN_003163d8 + FUN_003162e0, code 0x2aa.
 * Confidence: medium
 */
void sk_mul_checked_msg_b(sk_u128_t *out, sk_u128_t *b)
{
    sk_checked_op(out, b->lo, b->hi, (sk_u128_t (*)(uint64_t,uint64_t,uint64_t,uint64_t))sk_mul128_low_signed, 0x2aa);
}


/* FUN_003164f0 @ 0x003164f0   (est. sk_ld128_shl_thunk)
 * Ghidra: FUN_003164f0
 * FUN_00351124 then FUN_0035723c (shift-left thunk).
 * Confidence: medium
 */
void sk_ld128_shl_thunk(sk_u128_t *out)
{
    FUN_00351124();
    out->lo = FUN_0035723c(0);
    out->hi = 0;
}


/* FUN_00316518 @ 0x00316518   (est. sk_shl64_checked)
 * Ghidra: FUN_00316518
 * If index>1 panic; else FUN_00312be0 shift-left by index<<6, returns lo.
 * Confidence: medium
 */
uint64_t sk_shl64_checked(uint64_t index, uint64_t a, uint64_t b)
{
    if (1 < index) {
        FUN_003488bc(1); FUN_00355890(); FUN_00349e8c(); FUN_00351be0(); FUN_001afe4c();
    }
    return sk_u128_shr_arith(&b, b, a, index << 6);
}


/* FUN_00316578 @ 0x00316578   (est. sk_ld128_fn)
 * Ghidra: FUN_00316578
 * FUN_00350258 then FUN_001e638c.
 * Confidence: medium
 */
void sk_ld128_fn(sk_u128_t *out)
{
    FUN_00350258();
    out->lo = FUN_001e638c();
}


/* FUN_003165a0 @ 0x003165a0   (est. sk_shl64_select)
 * Ghidra: FUN_003165a0
 * sk_shl64_checked over x20 words; stores; returns {FUN_0001a1c8,out}.
 * Confidence: medium
 */
sk_u128_t sk_shl64_select(sk_u128_t *out, uint64_t *sel)
{
    uint64_t v = sk_shl64_checked(sel[0], ((uint64_t *)0)[0], ((uint64_t *)0)[1]);
    out->lo = v;
    sk_u128_t r;
    r.lo = (uint64_t)FUN_0001a1c8;
    r.hi = (uint64_t)out;
    return r;
}


/* FUN_003165f0 @ 0x003165f0   (est. sk_math_binop_e)
 * Ghidra: FUN_003165f0
 * FUN_00352e84 + FUN_001d3a30 + FUN_003554e0.
 * Confidence: medium
 */
void sk_math_binop_e(void)
{
    FUN_00352e84();
    FUN_001d3a30(((uint64_t *)0)[0], ((uint64_t *)0)[1], ((uint64_t *)0)[2], ((uint64_t *)0)[3]);
    FUN_003554e0();
}


/* FUN_0031662c @ 0x0031662c   (est. sk_math_seq2)
 * Ghidra: FUN_0031662c
 * FUN_0034c434 + FUN_001e3210 + FUN_0035272c.
 * Confidence: low
 */
void sk_math_seq2(void)
{
    FUN_0034c434();
    FUN_001e3210();
    FUN_0035272c();
}


/* FUN_00316668 @ 0x00316668   (est. sk_mul128_signed_checked)
 * Ghidra: FUN_00316668
 * Signed 128x128 multiply; on overflow calls FUN_00359380 (no return).
 * Confidence: low
 */
void sk_mul128_signed_checked(uint64_t a_lo, uint64_t a_hi, uint64_t b_lo, uint64_t b_hi)
{
    bool a_neg = (b_hi & 0x8000000000000000ULL) == 0;
    uint64_t na_lo = b_lo, na_hi = b_hi;
    if (!a_neg) {
        /* negate 128-bit a */
        uint64_t t = -(na_hi + (na_lo != 0));
        na_lo = -na_lo;
        na_hi = t;
    }
    /* 128x128 -> 256 partial, checked for overflow (FUN_00359380 = overflow panic) */
    __uint128_t lolo = (__uint128_t)a_lo * na_lo;
    __uint128_t lohi = (__uint128_t)a_lo * na_hi;
    __uint128_t hilo = (__uint128_t)a_hi * na_lo;
    __uint128_t hihi = (__uint128_t)a_hi * na_hi;
    uint64_t c1 = (uint64_t)(lolo >> 64);
    uint64_t mid = (uint64_t)lohi + (uint64_t)hilo + c1;
    uint64_t hi = (uint64_t)hihi + (uint64_t)(lohi >> 64) + (uint64_t)(hilo >> 64) + (mid < c1);
    if ((hi >> 63) != (a_hi >> 63))   /* sign overflow */
        FUN_00359380(0, 0);           /* no-return */
}


/* FUN_003167cc @ 0x003167cc   (est. sk_divti3)
 * Ghidra: FUN_003167cc
 * Signed 128/128 divide (__divti3). Handles signs, MIN/-1 overflow, zero divisor panic.
 * Confidence: low
 */
sk_u128_t sk_divti3(uint64_t a, uint64_t b, uint64_t c)
{
    FUN_00357ca0();
    FUN_003518c4();
    FUN_00355968(0);
    sk_i128_neg(0, 0);          /* register-forwarded negate */
    sk_udivti3_core();          /* register-forwarded unsigned divide */
    if (((int64_t)c ^ (int64_t)a) < 0) {
        sk_neg_panic_if_neg(0, 0);
        FUN_00351790();
        FUN_00019858();
        FUN_002d4a64();
    } else {
        sk_neg_panic_if_neg(0, 0);
    }
    FUN_00352c74();
    sk_u128_t r;
    r.lo = 0; r.hi = 0;
    return r;
}


/* FUN_003168cc @ 0x003168cc   (est. sk_divti3_wrap_a)
 * Ghidra: FUN_003168cc
 * Signed divide wrapper around FUN_003167cc.
 * Confidence: low
 */
sk_u128_t sk_divti3_wrap_a(sk_u128_t *a, sk_u128_t *b)
{
    return sk_divti3(b->lo, b->hi, a->lo);
}


/* FUN_003168d0 @ 0x003168d0   (est. sk_divti3_wrap_b)
 * Ghidra: FUN_003168d0
 * Signed divide wrapper around FUN_003167cc.
 * Confidence: low
 */
sk_u128_t sk_divti3_wrap_b(sk_u128_t *a, sk_u128_t *b)
{
    return sk_divti3(b->lo, b->hi, a->lo);
}


/* FUN_00316934 @ 0x00316934   (est. sk_divti3_wrap_c)
 * Ghidra: FUN_00316934
 * FUN_003167cc then FUN_00355968(0).
 * Confidence: low
 */
void sk_divti3_wrap_c(void)
{
    sk_divti3(0, 0, 0);   /* register-forwarded signed divide */
    FUN_00355968(0);
}


/* FUN_00316938 @ 0x00316938   (est. sk_divti3_wrap_d)
 * Ghidra: FUN_00316938
 * FUN_003167cc then FUN_00355968(0).
 * Confidence: low
 */
void sk_divti3_wrap_d(void)
{
    sk_divti3(0, 0, 0);   /* register-forwarded signed divide */
    FUN_00355968(0);
}


/* FUN_00316964 @ 0x00316964   (est. sk_mul128_signed_low)
 * Ghidra: FUN_00316964
 * Signed 128x128 multiply returning low 128 bits, negating per sign.
 * Confidence: low
 */
void sk_mul128_signed_low(void)
{
    FUN_003504d0();
    FUN_00355968(0);
    sk_i128_neg(0, 0);          /* register-forwarded negate */
    sk_multi3(0, 0, 0, 0);      /* register-forwarded multiply */
    FUN_003513fc();
}


/* FUN_00316ac8 @ 0x00316ac8   (est. sk_divti3_b)
 * Ghidra: FUN_00316ac8
 * Signed 128/128 divide variant (__divti3); zero divisor panic.
 * Confidence: low
 */
sk_u128_t sk_divti3_b(uint64_t a, uint64_t b, uint64_t c)
{
    FUN_00357ca0();
    FUN_00352cec();
    sk_i128_neg(a, c);
    FUN_00355528();
    FUN_00354318();
    /* register-forwarded unsigned divide-with-remainder (sk_udivmodti4_core) */
    FUN_00350aa0();
    FUN_00357c44();
    sk_u128_t r;
    r.lo = 0; r.hi = 0;
    return r;
}


/* FUN_00316c88 @ 0x00316c88   (est. sk_binop_dispatch)
 * Ghidra: FUN_00316c88
 * Runs 128-bit binary op via param_4 fn pointer on param_1's two words.
 * Confidence: medium
 */
void sk_binop_dispatch(sk_u128_t *a, uint64_t b_lo, uint64_t b_hi, uint64_t (*op)(uint64_t*,uint64_t,uint64_t,uint64_t))
{
    uint64_t newhi = op(&a->lo, a->hi, a->lo, b_lo);
    a->hi = newhi;
}


/* FUN_00316cd0 @ 0x00316cd0   (est. sk_u128_shl_ret)
 * Ghidra: FUN_00316cd0
 * Shift left of 128-bit by sh&0x7f returning full 128-bit result.
 * Confidence: high
 */
sk_u128_t sk_u128_shl_ret(uint64_t lo, uint64_t hi, uint64_t sh)
{
    uint64_t u = sh & 0x7f;
    uint64_t nlo = lo;
    if (u != 0) {
        nlo = lo << (sh & 0x3f);
        hi = (lo >> (uint64_t)(-u & 0x3f)) | (hi << (sh & 0x3f));
    }
    uint64_t rlo = lo << (sh & 0x3f);
    if (u < 0x40) rlo = hi;
    uint64_t rhi = 0;
    if (u < 0x40) rhi = nlo;
    sk_u128_t r;
    r.lo = rhi;
    r.hi = rlo;
    return r;
}


/* FUN_00316d08 @ 0x00316d08   (est. sk_u128_shr_ret)
 * Ghidra: FUN_00316d08
 * Shift right of 128-bit by FUN_00312be0; returns full result.
 * Confidence: high
 */
sk_u128_t sk_u128_shr_ret(uint64_t lo, uint64_t hi, uint64_t sh)
{
    uint64_t rlo = sk_u128_shr_arith(&hi, hi, lo, sh);
    sk_u128_t r;
    r.lo = hi;
    r.hi = rlo;
    return r;
}


/* FUN_00316d3c @ 0x00316d3c   (est. sk_div_checked_min)
 * Ghidra: FUN_00316d3c
 * Signed divide; panics on MIN/-1 overflow or zero divisor.
 * Confidence: low
 */
void sk_div_checked_min(sk_u128_t *a, int64_t b_lo, int64_t b_hi)
{
    if ((b_hi == -1 && b_lo == -1 && (int64_t)a->hi == -0x8000000000000000LL && a->lo == 0) ||
        (b_hi == 0 && b_lo == 0)) {
        FUN_003488bc(1); FUN_00349e8c(); FUN_00351be0(); FUN_001afe4c();
    }
    uint64_t dlo = FUN_00106e3c(), dhi = FUN_00106e3c();
    *a = sk_divti3(dlo, dhi, 0);
}


/* FUN_00316dc0 @ 0x00316dc0   (est. sk_div_checked_min2)
 * Ghidra: FUN_00316dc0
 * Signed divide with MIN/-1 and zero divisor checks.
 * Confidence: low
 */
void sk_div_checked_min2(int64_t a, int64_t b, int64_t c, int64_t d)
{
    if (d == -1) {
        c = a;
        if (b != -0x8000000000000000LL) goto calc;
    } else if (d != 0) goto calc;
    if (c == 0) {
        FUN_003488bc(1); FUN_00349e8c(); FUN_00351be0(); FUN_001afe4c();
    }
calc:
    sk_divti3(FUN_00355968(0), FUN_00355968(0), 0);
    FUN_00355968(0);
}


/* FUN_00316e44 @ 0x00316e44   (est. sk_div_checked_min3)
 * Ghidra: FUN_00316e44
 * Signed divide in place with MIN/-1 / zero divisor checks.
 * Confidence: low
 */
void sk_div_checked_min3(sk_u128_t *a, int64_t b_lo, int64_t b_hi)
{
    int64_t h = (int64_t)a->hi;
    if ((b_hi == -1 && b_lo == -1 && h == -0x8000000000000000LL && a->lo == 0) ||
        (b_hi == 0 && b_lo == 0)) {
        FUN_003488bc(1); FUN_00349e8c(); FUN_00351be0(); FUN_001afe4c();
    }
    FUN_00106e3c();
    sk_divti3(0, 0, 0);   /* register-forwarded signed divide */
    a->lo = (uint64_t)0;
    a->hi = (uint64_t)h;
}


/* FUN_00316f28 @ 0x00316f28   (est. sk_checked_op_flag_a)
 * Ghidra: FUN_00316f28
 * Runs op fn; returns low-bit of flag as uint (overflow indicator).
 * Confidence: medium
 */
uint32_t sk_checked_op_flag_a(sk_u128_t *out, sk_u128_t *b, sk_u128_t (*op)(uint64_t,uint64_t,uint64_t,uint64_t))
{
    uint64_t flag = ((uint64_t *)0)[0];
    *out = op(b->lo, b->hi, flag, ((uint64_t *)0)[1]);
    return (uint32_t)(flag & 1);
}


/* FUN_00316f90 @ 0x00316f90   (est. sk_checked_op_flag_b)
 * Ghidra: FUN_00316f90
 * Runs op fn; returns low-bit of flag as uint (overflow indicator).
 * Confidence: medium
 */
uint32_t sk_checked_op_flag_b(sk_u128_t *out, sk_u128_t *b, sk_u128_t (*op)(uint64_t,uint64_t,uint64_t,uint64_t))
{
    uint64_t flag = ((uint64_t *)0)[0];
    *out = op(b->lo, b->hi, flag, ((uint64_t *)0)[1]);
    return (uint32_t)(flag & 1);
}


/* FUN_00316ff8 @ 0x00316ff8   (est. sk_ternary_dispatch)
 * Ghidra: FUN_00316ff8
 * FUN_0008409c; runs 6-arg op on 3 128-bit operands, stores result + forwards.
 * Confidence: medium
 */
void sk_ternary_dispatch(sk_u128_t *out, sk_u128_t *a, sk_u128_t *b, sk_u128_t *c, sk_u128_t (*op)(uint64_t,uint64_t,uint64_t,uint64_t,uint64_t,uint64_t))
{
    FUN_0008409c();
    *out = op(a->lo, a->hi, b->lo, b->hi, ((uint64_t *)0)[0], ((uint64_t *)0)[1]);
}


/* FUN_0031703c @ 0x0031703c   (est. sk_ld_zero_ext)
 * Ghidra: FUN_0031703c
 * Loads FUN_00077770 as lo, hi=0.
 * Confidence: medium
 */
void sk_ld_zero_ext(sk_u128_t *out)
{
    out->lo = FUN_00077770();
    out->hi = 0;
}


/* FUN_00317074 @ 0x00317074   (est. sk_ld128_fp_a)
 * Ghidra: FUN_00317074
 * FUN_0035237c/00353510 then FUN_0023b1a8.
 * Confidence: low
 */
void sk_ld128_fp_a(sk_u128_t *out)
{
    FUN_0035237c();
    out->lo = FUN_0023b1a8();
    out->hi = 0;
}


/* FUN_003170c4 @ 0x003170c4   (est. sk_ld128_fp_b)
 * Ghidra: FUN_003170c4
 * FUN_0035237c/00353510 then FUN_0023b1a8.
 * Confidence: low
 */
void sk_ld128_fp_b(sk_u128_t *out)
{
    FUN_0035237c();
    out->lo = FUN_0023b1a8();
    out->hi = 0;
}


/* FUN_0031709c @ 0x0031709c   (est. sk_ld128_fp_c)
 * Ghidra: FUN_0031709c
 * FUN_0035237c then FUN_0001a1c8.
 * Confidence: low
 */
void sk_ld128_fp_c(sk_u128_t *out)
{
    FUN_0035237c();
    out->lo = FUN_0001a1c8();
    out->hi = 0;
}


/* FUN_00317104 @ 0x00317104   (est. sk_shr_dispatch_a)
 * Ghidra: FUN_00317104
 * FUN_00316c88 with FUN_00312be0 (arithmetic shift right).
 * Confidence: medium
 */
void sk_shr_dispatch_a(sk_u128_t *a, sk_u128_t *b, uint64_t sh)
{
    sk_binop_dispatch(a, b->lo, sh, (uint64_t (*)(uint64_t*,uint64_t,uint64_t,uint64_t))sk_u128_shr_arith);
}


/* FUN_00317108 @ 0x00317108   (est. sk_shr_dispatch_b)
 * Ghidra: FUN_00317108
 * FUN_00316c88 with FUN_00312be0 (arithmetic shift right).
 * Confidence: medium
 */
void sk_shr_dispatch_b(sk_u128_t *a, sk_u128_t *b, uint64_t sh)
{
    sk_binop_dispatch(a, b->lo, sh, (uint64_t (*)(uint64_t*,uint64_t,uint64_t,uint64_t))sk_u128_shr_arith);
}


/* FUN_0031714c @ 0x0031714c   (est. sk_unop_dispatch)
 * Ghidra: FUN_0031714c
 * Runs unary op fn on 128-bit a, stores to out.
 * Confidence: medium
 */
void sk_unop_dispatch(sk_u128_t *out, sk_u128_t *a, sk_u128_t *b, sk_u128_t (*op)(uint64_t,uint64_t,uint64_t))
{
    *out = op(a->lo, a->hi, b->lo);
}


/* FUN_00317188 @ 0x00317188   (est. sk_shl_dispatch_a)
 * Ghidra: FUN_00317188
 * FUN_00316c88 with FUN_003135dc (shift left, 7-bit count).
 * Confidence: medium
 */
void sk_shl_dispatch_a(sk_u128_t *a, sk_u128_t *b, uint64_t sh)
{
    sk_binop_dispatch(a, b->lo, sh, sk_u128_shl7);
}


/* FUN_0031718c @ 0x0031718c   (est. sk_shl_dispatch_b)
 * Ghidra: FUN_0031718c
 * FUN_00316c88 with FUN_003135dc (shift left, 7-bit count).
 * Confidence: medium
 */
void sk_shl_dispatch_b(sk_u128_t *a, sk_u128_t *b, uint64_t sh)
{
    sk_binop_dispatch(a, b->lo, sh, sk_u128_shl7);
}


/* FUN_003171fc @ 0x003171fc   (est. sk_fp_seq_a)
 * Ghidra: FUN_003171fc
 * FUN_00349fcc/0034313c/0034ea7c + FUN_0024304c/0024320c.
 * Confidence: low
 */
void sk_fp_seq_a(void)
{
    FUN_00349fcc();
    FUN_0034313c();
    FUN_0034ea7c();
    FUN_0024304c();
}


/* FUN_00317400 @ 0x00317400   (est. sk_fp_seq_b)
 * Ghidra: FUN_00317400
 * FUN_00349fcc/0034313c/0034ea7c + FUN_0024304c/0024320c.
 * Confidence: low
 */
void sk_fp_seq_b(void)
{
    FUN_00349fcc();
    FUN_0034313c();
    FUN_0034ea7c();
    FUN_0024304c();
}


/* FUN_00317254 @ 0x00317254   (est. sk_fp_seq_c)
 * Ghidra: FUN_00317254
 * FUN_00041138 + indirect x5 call + FUN_003a25d4; stores 128-bit via FUN_002e6330.
 * Confidence: low
 */
void sk_fp_seq_c(sk_u128_t *out)
{
    FUN_00041138();
    FUN_0034c7a8();
    ((code_t)0)();
    FUN_00350230((uint64_t)(uintptr_t)&out->lo);
    FUN_002412d4();
    FUN_003598b4();
    out->lo = FUN_002e6330();
    out->hi = 0;
}


/* FUN_0031738c @ 0x0031738c   (est. sk_fp_seq_d)
 * Ghidra: FUN_0031738c
 * FUN_00357cb4 + indirect x5; stores two stack words.
 * Confidence: low
 */
void sk_fp_seq_d(uint64_t *out)
{
    FUN_00357cb4();
    FUN_00349944();
    ((code_t)0)();
    FUN_0034e53c();
    FUN_00243c60();
    FUN_0034b804();
    out[0] = 0;
    out[1] = 0;
    FUN_00357c74();
}


/* FUN_00317498 @ 0x00317498   (est. sk_ldexp_variant2)
 * Ghidra: FUN_00317498
 * FUN_0034ed08 + FUN_0035723c + FUN_003154ec + FUN_0006b674 + FUN_00350974.
 * Confidence: low
 */
void sk_ldexp_variant2(sk_u128_t *out)
{
    FUN_0034ed08();
    FUN_0035723c(0);
    FUN_00351790();
    sk_u128_sub(((uint64_t *)0)[0], ((uint64_t *)0)[1], 0, 0);   /* register-forwarded */
    FUN_0006b674();
    FUN_0035723c(1);
    FUN_00350974(0, 0);
    *out = (sk_u128_t){0, 0};   /* register-forwarded subtract */
}


/* FUN_0031753c @ 0x0031753c   (est. sk_u128_to_double_b)
 * Ghidra: FUN_0031753c
 * Unsigned int128->double conversion (shared FP skeleton).
 * Confidence: low
 */
/* Signed 128-bit integer <-> double conversion. Control flow:
 *   - sign bit (param_3 bit 63) drives a negate via sk_i128_neg
 *   - exponent extracted from the float; range checks against 0x40, 0x80, 0x81
 *     decide fast-path (FUN_00310a44 / FUN_003109b4) vs slow path
 *     (FUN_00352950 slow-rounded), clamping to 0x80 / 0xffffffffffffff80 on
 *     overflow; the final shift uses sk_u128_shr_logical / sk_u128_shr_arith / sk_u128_shl_ret.
 *   - overflow paths panic via FUN_003523f0 (no return).
 * The decompiler collapses the FP dispatch into indirect calls
 * ((*DAT_00658c00)() and register-forwarded code pointers); only the
 * recognizable structure is preserved below. Confidence: low. */
void sk_u128_to_double_b(void)
{
    FUN_0008e518();
    FUN_0034ab20();
    FUN_0007c1a4();
    /* sign + exponent normalization; range checks vs 0x40/0x80/0x81 */
    if ((/* in_x3 */ 0L & 1) == 0) {
        FUN_0034a43c();
    } else {
        FUN_00310a44();
    }
    FUN_003517b4();
    FUN_002e62f0(0);
    /* final 128-bit shift normalization */
    FUN_0035723c(0x7f);
    FUN_00355998();
    FUN_0008e500(0);
}


/* FUN_00318c9c @ 0x00318c9c   (est. sk_binop2_dispatch)
 * Ghidra: FUN_00318c9c
 * FUN_0008409c; runs 2-arg op, stores result + forwards x20 words.
 * Confidence: medium
 */
void sk_binop2_dispatch(sk_u128_t *out, sk_u128_t *a, sk_u128_t (*op)(uint64_t,uint64_t))
{
    FUN_0008409c();
    *out = op(a->lo, a->hi);
    ((uint64_t *)0)[0] = a->lo;
    ((uint64_t *)0)[1] = a->hi;
}


/* FUN_00318cec @ 0x00318cec   (est. sk_ld128_fp_d)
 * Ghidra: FUN_00318cec
 * FUN_00353510 then FUN_00231c40.
 * Confidence: low
 */
void sk_ld128_fp_d(sk_u128_t *out)
{
    FUN_00353510();
    out->lo = FUN_00231c40();
    out->hi = 0;
}


/* FUN_00318d40 @ 0x00318d40   (est. sk_parse_int_fmt)
 * Ghidra: FUN_00318d40
 * Number-format parse: reads sign char +/- (FUN_001d9840), base-10 conversion, returns {base,val,flags}.
 * Confidence: medium
 */
void sk_parse_int_fmt(sk_u128_t *out, uint64_t fmt, uint64_t *p)
{
    FUN_00041138();
    uint64_t v = FUN_003521e4();
    if (/* extraout */ 0 == 0) {
        FUN_003a25d4(0);
        FUN_00356584();
        out->lo = 0;
        out->hi = 0;
        ((uint8_t *)out)[16] = 1;
        FUN_0035847c();
        return;
    }
    if ((fmt >> 0x3c & 1) != 0) {
        uint32_t base = 10;
        FUN_0022d118();
        FUN_000b43e8();
        out->lo = 0; out->hi = 0;
        ((uint8_t *)out)[16] = 1;
        FUN_0035847c();
        return;
    }
    if ((fmt >> 0x3d & 1) == 0) {
        /* optional sign handling via FUN_001d9840 / FUN_001e4cbc */
        FUN_0034daa8();
        FUN_00348160();
    } else {
        /* signed string parse */
        FUN_00359a90();
        FUN_003484b4();
    }
    FUN_003524c8();
    FUN_001afe4c();   /* no-return */
}


/* FUN_00318ed0 @ 0x00318ed0   (est. sk_float_mul_add)
 * Ghidra: FUN_00318ed0
 * Float multiply-add with sign handling and SoftwareBreakpoint on MIN.
 * Confidence: low
 */
void sk_float_mul_add(uint64_t *out)
{
    FUN_00354a34();
    uint64_t a = FUN_00350470();
    FUN_000867a8(0, 0);
    uint32_t x = FUN_002d49f4(0, 0, 0, 0);
    FUN_00350630();
    FUN_000867a8(0, 0);
    uint32_t y = FUN_002d49f4(0, 0, 0, 0);
    if (((x ^ y) & 1) == 0) {
        FUN_0034be0c(a);
        sk_u128_sub(0, 0, 0, 0);   /* register-forwarded subtract */
        FUN_00351790();
        sk_u128_sub(1, 0, 0, 0);   /* register-forwarded */
        FUN_0006b6f4();
        if ((FUN_002d49f4(0, 0, 0, 0) & 1) == 0) {
            FUN_00350aac(0x7fffffffffffffffLL, 0);
            if ((FUN_002d49f4(0, 0, 0, 0) & 1) == 0) { *out = 0; return; }
        }
    } else {
        sk_i128_neg(0, 0);   /* register-forwarded negate */
        int64_t n = (int64_t)FUN_002e6410();
        FUN_003553f4();
        if ((FUN_002e6474() & 1) == 0) {
            if (-n < 0) __builtin_trap();  /* MIN negate trap (SoftwareBreakpoint 1 @0x318f5c) */
            *out = (uint64_t)n;
            FUN_00354ef8();
            return;
        }
    }
    FUN_003488bc(1);
    FUN_00349a54();
    FUN_003523f0(0);   /* no-return */
}


/* FUN_00318ff0 @ 0x00318ff0   (est. sk_ld128_math)
 * Ghidra: FUN_00318ff0
 * FUN_00351124 + FUN_0035723c + FUN_00351790 + FUN_000b43d0 + FUN_002d3c28.
 * Confidence: low
 */
void sk_ld128_math(sk_u128_t *out)
{
    FUN_00351124();
    FUN_0035723c(0);
    FUN_00351790();
    FUN_000b43d0();
    out->lo = FUN_002d3c28();
    out->hi = 0;
}


/* FUN_00319040 @ 0x00319040   (est. sk_flag_test_a)
 * Ghidra: FUN_00319040
 * FUN_00359b0c then FUN_0035aad8; returns low bit.
 * Confidence: low
 */
uint32_t sk_flag_test_a(void)
{
    FUN_00359b0c();
    return (uint32_t)(FUN_0035aad8() & 1);
}


/* FUN_00319090 @ 0x00319090   (est. sk_flag_test_b)
 * Ghidra: FUN_00319090
 * FUN_00321ca0; returns low bit.
 * Confidence: low
 */
uint32_t sk_flag_test_b(void)
{
    return (uint32_t)(FUN_00321ca0() & 1);
}


/* FUN_003190c8 @ 0x003190c8   (est. sk_flag_test_b_003190c8)
 * Ghidra: FUN_003190c8
 * FUN_00321ca0; returns low bit.
 * Confidence: low
 */
uint32_t sk_flag_test_b_003190c8(void)
{
    return (uint32_t)(FUN_00321ca0() & 1);
}


/* FUN_00319100 @ 0x00319100   (est. sk_ld128_flag_a)
 * Ghidra: FUN_00319100
 * FUN_0035237c + FUN_000867a8 + FUN_003154ec; if param_3 bit0 set panics.
 * Confidence: medium
 */
void sk_ld128_flag_a(sk_u128_t *out, uint64_t a, uint32_t flag)
{
    FUN_0035237c();
    FUN_000867a8(0, 0);
    sk_u128_sub(0, 0, 0, 0);   /* register-forwarded subtract */
    out->lo = 0; out->hi = 0;
    if ((flag & 1) != 0) {
        FUN_003488bc(1);
        FUN_00349d58();
        FUN_001afe4c();   /* no-return */
    }
}


/* FUN_00319160 @ 0x00319160   (est. sk_ld128_flag_b)
 * Ghidra: FUN_00319160
 * FUN_000867a8 + FUN_003154ec; if param_3 bit0 set panics.
 * Confidence: medium
 */
void sk_ld128_flag_b(uint64_t a, uint64_t b, uint32_t flag)
{
    FUN_000867a8(((uint64_t *)0)[0], ((uint64_t *)0)[1]);
    sk_u128_sub(0, 0, 0, 0);   /* register-forwarded subtract */
    if ((flag & 1) != 0) {
        FUN_003488bc(1);
        FUN_00349d58();
        FUN_001afe4c();   /* no-return */
    }
}


/* FUN_003191e8 @ 0x003191e8   (est. sk_field_ref_20)
 * Ghidra: FUN_003191e8
 * Object relative-reference accessor at +0x20; tagged-pointer aware.
 * Confidence: high
 */
long sk_field_ref_20(uint64_t obj)
{
    /* tagged-pointer deref: bit0 set -> load real pointer through masked address */
    if (obj & 1) obj = *(uint64_t *)(obj & ~1ULL);
    return (long)(obj + 0x20) + (long)*(int *)(obj + 0x20);
}


/* FUN_00319248 @ 0x00319248   (est. sk_field_ref_10)
 * Ghidra: FUN_00319248
 * Object relative-reference accessor at +0x10; tagged-pointer aware.
 * Confidence: high
 */
long sk_field_ref_10(uint64_t obj)
{
    /* tagged-pointer deref: bit0 set -> load real pointer through masked address */
    if (obj & 1) obj = *(uint64_t *)(obj & ~1ULL);
    return (long)(obj + 0x10) + (long)*(int *)(obj + 0x10);
}


/* FUN_00319278 @ 0x00319278   (est. sk_field_ref_44)
 * Ghidra: FUN_00319278
 * Object relative-reference accessor at +0x44; tagged-pointer aware.
 * Confidence: high
 */
long sk_field_ref_44(uint64_t obj)
{
    /* tagged-pointer deref: bit0 set -> load real pointer through masked address */
    if (obj & 1) obj = *(uint64_t *)(obj & ~1ULL);
    return (long)(obj + 0x44) + (long)*(int *)(obj + 0x44);
}


/* FUN_003192a8 @ 0x003192a8   (est. sk_field_ref_34)
 * Ghidra: FUN_003192a8
 * Object relative-reference accessor at +0x34; tagged-pointer aware.
 * Confidence: high
 */
long sk_field_ref_34(uint64_t obj)
{
    /* tagged-pointer deref: bit0 set -> load real pointer through masked address */
    if (obj & 1) obj = *(uint64_t *)(obj & ~1ULL);
    return (long)(obj + 0x34) + (long)*(int *)(obj + 0x34);
}


/* FUN_003192d8 @ 0x003192d8   (est. sk_field_ref_48)
 * Ghidra: FUN_003192d8
 * Object relative-reference accessor at +0x48; tagged-pointer aware.
 * Confidence: high
 */
long sk_field_ref_48(uint64_t obj)
{
    /* tagged-pointer deref: bit0 set -> load real pointer through masked address */
    if (obj & 1) obj = *(uint64_t *)(obj & ~1ULL);
    return (long)(obj + 0x48) + (long)*(int *)(obj + 0x48);
}


/* FUN_0031945c @ 0x0031945c   (est. sk_field_ref_0c)
 * Ghidra: FUN_0031945c
 * Object relative-reference accessor at +0xc; tagged-pointer aware.
 * Confidence: high
 */
long sk_field_ref_0c(uint64_t obj)
{
    /* tagged-pointer deref: bit0 set -> load real pointer through masked address */
    if (obj & 1) obj = *(uint64_t *)(obj & ~1ULL);
    return (long)(obj + 0xc) + (long)*(int *)(obj + 0xc);
}


/* FUN_0031948c @ 0x0031948c   (est. sk_field_ref_10_0031948c)
 * Ghidra: FUN_0031948c
 * Object relative-reference accessor at +0x10; tagged-pointer aware.
 * Confidence: high
 */
long sk_field_ref_10_0031948c(uint64_t obj)
{
    /* tagged-pointer deref: bit0 set -> load real pointer through masked address */
    if (obj & 1) obj = *(uint64_t *)(obj & ~1ULL);
    return (long)(obj + 0x10) + (long)*(int *)(obj + 0x10);
}


/* FUN_003194f8 @ 0x003194f8   (est. sk_field_ref_04)
 * Ghidra: FUN_003194f8
 * Object relative-reference accessor at +0x4; tagged-pointer aware.
 * Confidence: high
 */
long sk_field_ref_04(uint64_t obj)
{
    /* tagged-pointer deref: bit0 set -> load real pointer through masked address */
    if (obj & 1) obj = *(uint64_t *)(obj & ~1ULL);
    return (long)(obj + 0x4) + (long)*(int *)(obj + 0x4);
}


/* FUN_00319538 @ 0x00319538   (est. sk_field_ref_14)
 * Ghidra: FUN_00319538
 * Object relative-reference accessor at +0x14; tagged-pointer aware.
 * Confidence: high
 */
long sk_field_ref_14(uint64_t obj)
{
    /* tagged-pointer deref: bit0 set -> load real pointer through masked address */
    if (obj & 1) obj = *(uint64_t *)(obj & ~1ULL);
    return (long)(obj + 0x14) + (long)*(int *)(obj + 0x14);
}


/* FUN_00319568 @ 0x00319568   (est. sk_field_ref_40)
 * Ghidra: FUN_00319568
 * Object relative-reference accessor at +0x40; tagged-pointer aware.
 * Confidence: high
 */
long sk_field_ref_40(uint64_t obj)
{
    /* tagged-pointer deref: bit0 set -> load real pointer through masked address */
    if (obj & 1) obj = *(uint64_t *)(obj & ~1ULL);
    return (long)(obj + 0x40) + (long)*(int *)(obj + 0x40);
}


/* FUN_003195c8 @ 0x003195c8   (est. sk_field_ref_2c)
 * Ghidra: FUN_003195c8
 * Object relative-reference accessor at +0x2c; tagged-pointer aware.
 * Confidence: high
 */
long sk_field_ref_2c(uint64_t obj)
{
    /* tagged-pointer deref: bit0 set -> load real pointer through masked address */
    if (obj & 1) obj = *(uint64_t *)(obj & ~1ULL);
    return (long)(obj + 0x2c) + (long)*(int *)(obj + 0x2c);
}


/* FUN_003195f8 @ 0x003195f8   (est. sk_field_ref_1c)
 * Ghidra: FUN_003195f8
 * Object relative-reference accessor at +0x1c; tagged-pointer aware.
 * Confidence: high
 */
long sk_field_ref_1c(uint64_t obj)
{
    /* tagged-pointer deref: bit0 set -> load real pointer through masked address */
    if (obj & 1) obj = *(uint64_t *)(obj & ~1ULL);
    return (long)(obj + 0x1c) + (long)*(int *)(obj + 0x1c);
}


/* FUN_00319628 @ 0x00319628   (est. sk_field_ref_2c_00319628)
 * Ghidra: FUN_00319628
 * Object relative-reference accessor at +0x2c; tagged-pointer aware.
 * Confidence: high
 */
long sk_field_ref_2c_00319628(uint64_t obj)
{
    /* tagged-pointer deref: bit0 set -> load real pointer through masked address */
    if (obj & 1) obj = *(uint64_t *)(obj & ~1ULL);
    return (long)(obj + 0x2c) + (long)*(int *)(obj + 0x2c);
}


/* FUN_00319658 @ 0x00319658   (est. sk_field_ref_5c)
 * Ghidra: FUN_00319658
 * Object relative-reference accessor at +0x5c; tagged-pointer aware.
 * Confidence: high
 */
long sk_field_ref_5c(uint64_t obj)
{
    /* tagged-pointer deref: bit0 set -> load real pointer through masked address */
    if (obj & 1) obj = *(uint64_t *)(obj & ~1ULL);
    return (long)(obj + 0x5c) + (long)*(int *)(obj + 0x5c);
}


/* FUN_00319688 @ 0x00319688   (est. sk_field_ref_2c_00319688)
 * Ghidra: FUN_00319688
 * Object relative-reference accessor at +0x2c; tagged-pointer aware.
 * Confidence: high
 */
long sk_field_ref_2c_00319688(uint64_t obj)
{
    /* tagged-pointer deref: bit0 set -> load real pointer through masked address */
    if (obj & 1) obj = *(uint64_t *)(obj & ~1ULL);
    return (long)(obj + 0x2c) + (long)*(int *)(obj + 0x2c);
}


/* FUN_003196e8 @ 0x003196e8   (est. sk_field_ref_14_003196e8)
 * Ghidra: FUN_003196e8
 * Object relative-reference accessor at +0x14; tagged-pointer aware.
 * Confidence: high
 */
long sk_field_ref_14_003196e8(uint64_t obj)
{
    /* tagged-pointer deref: bit0 set -> load real pointer through masked address */
    if (obj & 1) obj = *(uint64_t *)(obj & ~1ULL);
    return (long)(obj + 0x14) + (long)*(int *)(obj + 0x14);
}


/* FUN_00319718 @ 0x00319718   (est. sk_field_ref_1c_00319718)
 * Ghidra: FUN_00319718
 * Object relative-reference accessor at +0x1c; tagged-pointer aware.
 * Confidence: high
 */
long sk_field_ref_1c_00319718(uint64_t obj)
{
    /* tagged-pointer deref: bit0 set -> load real pointer through masked address */
    if (obj & 1) obj = *(uint64_t *)(obj & ~1ULL);
    return (long)(obj + 0x1c) + (long)*(int *)(obj + 0x1c);
}


/* FUN_00319748 @ 0x00319748   (est. sk_field_ref_30)
 * Ghidra: FUN_00319748
 * Object relative-reference accessor at +0x30; tagged-pointer aware.
 * Confidence: high
 */
long sk_field_ref_30(uint64_t obj)
{
    /* tagged-pointer deref: bit0 set -> load real pointer through masked address */
    if (obj & 1) obj = *(uint64_t *)(obj & ~1ULL);
    return (long)(obj + 0x30) + (long)*(int *)(obj + 0x30);
}


/* FUN_00319778 @ 0x00319778   (est. sk_field_ref_6c)
 * Ghidra: FUN_00319778
 * Object relative-reference accessor at +0x6c; tagged-pointer aware.
 * Confidence: high
 */
long sk_field_ref_6c(uint64_t obj)
{
    /* tagged-pointer deref: bit0 set -> load real pointer through masked address */
    if (obj & 1) obj = *(uint64_t *)(obj & ~1ULL);
    return (long)(obj + 0x6c) + (long)*(int *)(obj + 0x6c);
}


/* FUN_003197a8 @ 0x003197a8   (est. sk_field_ref_0c_003197a8)
 * Ghidra: FUN_003197a8
 * Object relative-reference accessor at +0xc; tagged-pointer aware.
 * Confidence: high
 */
long sk_field_ref_0c_003197a8(uint64_t obj)
{
    /* tagged-pointer deref: bit0 set -> load real pointer through masked address */
    if (obj & 1) obj = *(uint64_t *)(obj & ~1ULL);
    return (long)(obj + 0xc) + (long)*(int *)(obj + 0xc);
}


/* FUN_003197d8 @ 0x003197d8   (est. sk_field_ref_10_003197d8)
 * Ghidra: FUN_003197d8
 * Object relative-reference accessor at +0x10; tagged-pointer aware.
 * Confidence: high
 */
long sk_field_ref_10_003197d8(uint64_t obj)
{
    /* tagged-pointer deref: bit0 set -> load real pointer through masked address */
    if (obj & 1) obj = *(uint64_t *)(obj & ~1ULL);
    return (long)(obj + 0x10) + (long)*(int *)(obj + 0x10);
}


/* FUN_0031986c @ 0x0031986c   (est. sk_field_ref_0c_0031986c)
 * Ghidra: FUN_0031986c
 * Object relative-reference accessor at +0xc; tagged-pointer aware.
 * Confidence: high
 */
long sk_field_ref_0c_0031986c(uint64_t obj)
{
    /* tagged-pointer deref: bit0 set -> load real pointer through masked address */
    if (obj & 1) obj = *(uint64_t *)(obj & ~1ULL);
    return (long)(obj + 0xc) + (long)*(int *)(obj + 0xc);
}


/* FUN_0031989c @ 0x0031989c   (est. sk_field_ref_04_0031989c)
 * Ghidra: FUN_0031989c
 * Object relative-reference accessor at +0x4; tagged-pointer aware.
 * Confidence: high
 */
long sk_field_ref_04_0031989c(uint64_t obj)
{
    /* tagged-pointer deref: bit0 set -> load real pointer through masked address */
    if (obj & 1) obj = *(uint64_t *)(obj & ~1ULL);
    return (long)(obj + 0x4) + (long)*(int *)(obj + 0x4);
}


/* FUN_003198fc @ 0x003198fc   (est. sk_field_ref_14_003198fc)
 * Ghidra: FUN_003198fc
 * Object relative-reference accessor at +0x14; tagged-pointer aware.
 * Confidence: high
 */
long sk_field_ref_14_003198fc(uint64_t obj)
{
    /* tagged-pointer deref: bit0 set -> load real pointer through masked address */
    if (obj & 1) obj = *(uint64_t *)(obj & ~1ULL);
    return (long)(obj + 0x14) + (long)*(int *)(obj + 0x14);
}


/* FUN_0031993c @ 0x0031993c   (est. sk_field_ref_14_0031993c)
 * Ghidra: FUN_0031993c
 * Object relative-reference accessor at +0x14; tagged-pointer aware.
 * Confidence: high
 */
long sk_field_ref_14_0031993c(uint64_t obj)
{
    /* tagged-pointer deref: bit0 set -> load real pointer through masked address */
    if (obj & 1) obj = *(uint64_t *)(obj & ~1ULL);
    return (long)(obj + 0x14) + (long)*(int *)(obj + 0x14);
}


/* FUN_0031997c @ 0x0031997c   (est. sk_field_ref_08)
 * Ghidra: FUN_0031997c
 * Object relative-reference accessor at +0x8; tagged-pointer aware.
 * Confidence: high
 */
long sk_field_ref_08(uint64_t obj)
{
    /* tagged-pointer deref: bit0 set -> load real pointer through masked address */
    if (obj & 1) obj = *(uint64_t *)(obj & ~1ULL);
    return (long)(obj + 0x8) + (long)*(int *)(obj + 0x8);
}


/* FUN_00319a90 @ 0x00319a90   (est. sk_field_ref_10_00319a90)
 * Ghidra: FUN_00319a90
 * Object relative-reference accessor at +0x10; tagged-pointer aware.
 * Confidence: high
 */
long sk_field_ref_10_00319a90(uint64_t obj)
{
    /* tagged-pointer deref: bit0 set -> load real pointer through masked address */
    if (obj & 1) obj = *(uint64_t *)(obj & ~1ULL);
    return (long)(obj + 0x10) + (long)*(int *)(obj + 0x10);
}


/* FUN_00319aec @ 0x00319aec   (est. sk_field_ref_0c_00319aec)
 * Ghidra: FUN_00319aec
 * Object relative-reference accessor at +0xc; tagged-pointer aware.
 * Confidence: high
 */
long sk_field_ref_0c_00319aec(uint64_t obj)
{
    /* tagged-pointer deref: bit0 set -> load real pointer through masked address */
    if (obj & 1) obj = *(uint64_t *)(obj & ~1ULL);
    return (long)(obj + 0xc) + (long)*(int *)(obj + 0xc);
}


/* FUN_00319b1c @ 0x00319b1c   (est. sk_field_ref_0c_00319b1c)
 * Ghidra: FUN_00319b1c
 * Object relative-reference accessor at +0xc; tagged-pointer aware.
 * Confidence: high
 */
long sk_field_ref_0c_00319b1c(uint64_t obj)
{
    /* tagged-pointer deref: bit0 set -> load real pointer through masked address */
    if (obj & 1) obj = *(uint64_t *)(obj & ~1ULL);
    return (long)(obj + 0xc) + (long)*(int *)(obj + 0xc);
}


/* FUN_00319b4c @ 0x00319b4c   (est. sk_field_ref_10_00319b4c)
 * Ghidra: FUN_00319b4c
 * Object relative-reference accessor at +0x10; tagged-pointer aware.
 * Confidence: high
 */
long sk_field_ref_10_00319b4c(uint64_t obj)
{
    /* tagged-pointer deref: bit0 set -> load real pointer through masked address */
    if (obj & 1) obj = *(uint64_t *)(obj & ~1ULL);
    return (long)(obj + 0x10) + (long)*(int *)(obj + 0x10);
}


/* FUN_00319b7c @ 0x00319b7c   (est. sk_field_ref_10_00319b7c)
 * Ghidra: FUN_00319b7c
 * Object relative-reference accessor at +0x10; tagged-pointer aware.
 * Confidence: high
 */
long sk_field_ref_10_00319b7c(uint64_t obj)
{
    /* tagged-pointer deref: bit0 set -> load real pointer through masked address */
    if (obj & 1) obj = *(uint64_t *)(obj & ~1ULL);
    return (long)(obj + 0x10) + (long)*(int *)(obj + 0x10);
}


/* FUN_00319bac @ 0x00319bac   (est. sk_field_ref_14_00319bac)
 * Ghidra: FUN_00319bac
 * Object relative-reference accessor at +0x14; tagged-pointer aware.
 * Confidence: high
 */
long sk_field_ref_14_00319bac(uint64_t obj)
{
    /* tagged-pointer deref: bit0 set -> load real pointer through masked address */
    if (obj & 1) obj = *(uint64_t *)(obj & ~1ULL);
    return (long)(obj + 0x14) + (long)*(int *)(obj + 0x14);
}


/* FUN_00319bdc @ 0x00319bdc   (est. sk_field_ref_14_00319bdc)
 * Ghidra: FUN_00319bdc
 * Object relative-reference accessor at +0x14; tagged-pointer aware.
 * Confidence: high
 */
long sk_field_ref_14_00319bdc(uint64_t obj)
{
    /* tagged-pointer deref: bit0 set -> load real pointer through masked address */
    if (obj & 1) obj = *(uint64_t *)(obj & ~1ULL);
    return (long)(obj + 0x14) + (long)*(int *)(obj + 0x14);
}


/* FUN_00319c0c @ 0x00319c0c   (est. sk_field_ref_18)
 * Ghidra: FUN_00319c0c
 * Object relative-reference accessor at +0x18; tagged-pointer aware.
 * Confidence: high
 */
long sk_field_ref_18(uint64_t obj)
{
    /* tagged-pointer deref: bit0 set -> load real pointer through masked address */
    if (obj & 1) obj = *(uint64_t *)(obj & ~1ULL);
    return (long)(obj + 0x18) + (long)*(int *)(obj + 0x18);
}


/* FUN_00319c3c @ 0x00319c3c   (est. sk_field_ref_18_00319c3c)
 * Ghidra: FUN_00319c3c
 * Object relative-reference accessor at +0x18; tagged-pointer aware.
 * Confidence: high
 */
long sk_field_ref_18_00319c3c(uint64_t obj)
{
    /* tagged-pointer deref: bit0 set -> load real pointer through masked address */
    if (obj & 1) obj = *(uint64_t *)(obj & ~1ULL);
    return (long)(obj + 0x18) + (long)*(int *)(obj + 0x18);
}


/* FUN_00319f3c @ 0x00319f3c   (est. sk_field_ref_38)
 * Ghidra: FUN_00319f3c
 * Object relative-reference accessor at +0x38; tagged-pointer aware.
 * Confidence: high
 */
long sk_field_ref_38(uint64_t obj)
{
    /* tagged-pointer deref: bit0 set -> load real pointer through masked address */
    if (obj & 1) obj = *(uint64_t *)(obj & ~1ULL);
    return (long)(obj + 0x38) + (long)*(int *)(obj + 0x38);
}


/* FUN_0031a0ec @ 0x0031a0ec   (est. sk_field_ref_4c)
 * Ghidra: FUN_0031a0ec
 * Object relative-reference accessor at +0x4c; tagged-pointer aware.
 * Confidence: high
 */
long sk_field_ref_4c(uint64_t obj)
{
    /* tagged-pointer deref: bit0 set -> load real pointer through masked address */
    if (obj & 1) obj = *(uint64_t *)(obj & ~1ULL);
    return (long)(obj + 0x4c) + (long)*(int *)(obj + 0x4c);
}


/* FUN_0031a11c @ 0x0031a11c   (est. sk_field_ref_4c_0031a11c)
 * Ghidra: FUN_0031a11c
 * Object relative-reference accessor at +0x4c; tagged-pointer aware.
 * Confidence: high
 */
long sk_field_ref_4c_0031a11c(uint64_t obj)
{
    /* tagged-pointer deref: bit0 set -> load real pointer through masked address */
    if (obj & 1) obj = *(uint64_t *)(obj & ~1ULL);
    return (long)(obj + 0x4c) + (long)*(int *)(obj + 0x4c);
}


/* FUN_0031a14c @ 0x0031a14c   (est. sk_field_ref_50)
 * Ghidra: FUN_0031a14c
 * Object relative-reference accessor at +0x50; tagged-pointer aware.
 * Confidence: high
 */
long sk_field_ref_50(uint64_t obj)
{
    /* tagged-pointer deref: bit0 set -> load real pointer through masked address */
    if (obj & 1) obj = *(uint64_t *)(obj & ~1ULL);
    return (long)(obj + 0x50) + (long)*(int *)(obj + 0x50);
}


/* FUN_0031a17c @ 0x0031a17c   (est. sk_field_ref_0c_0031a17c)
 * Ghidra: FUN_0031a17c
 * Object relative-reference accessor at +0xc; tagged-pointer aware.
 * Confidence: high
 */
long sk_field_ref_0c_0031a17c(uint64_t obj)
{
    /* tagged-pointer deref: bit0 set -> load real pointer through masked address */
    if (obj & 1) obj = *(uint64_t *)(obj & ~1ULL);
    return (long)(obj + 0xc) + (long)*(int *)(obj + 0xc);
}


/* FUN_0031a1ac @ 0x0031a1ac   (est. sk_field_ref_58)
 * Ghidra: FUN_0031a1ac
 * Object relative-reference accessor at +0x58; tagged-pointer aware.
 * Confidence: high
 */
long sk_field_ref_58(uint64_t obj)
{
    /* tagged-pointer deref: bit0 set -> load real pointer through masked address */
    if (obj & 1) obj = *(uint64_t *)(obj & ~1ULL);
    return (long)(obj + 0x58) + (long)*(int *)(obj + 0x58);
}


/* FUN_0031a26c @ 0x0031a26c   (est. sk_field_ref_08_0031a26c)
 * Ghidra: FUN_0031a26c
 * Object relative-reference accessor at +0x8; tagged-pointer aware.
 * Confidence: high
 */
long sk_field_ref_08_0031a26c(uint64_t obj)
{
    /* tagged-pointer deref: bit0 set -> load real pointer through masked address */
    if (obj & 1) obj = *(uint64_t *)(obj & ~1ULL);
    return (long)(obj + 0x8) + (long)*(int *)(obj + 0x8);
}


/* FUN_0031a2cc @ 0x0031a2cc   (est. sk_field_ref_14_0031a2cc)
 * Ghidra: FUN_0031a2cc
 * Object relative-reference accessor at +0x14; tagged-pointer aware.
 * Confidence: high
 */
long sk_field_ref_14_0031a2cc(uint64_t obj)
{
    /* tagged-pointer deref: bit0 set -> load real pointer through masked address */
    if (obj & 1) obj = *(uint64_t *)(obj & ~1ULL);
    return (long)(obj + 0x14) + (long)*(int *)(obj + 0x14);
}


/* FUN_0031a2fc @ 0x0031a2fc   (est. sk_field_ref_18_0031a2fc)
 * Ghidra: FUN_0031a2fc
 * Object relative-reference accessor at +0x18; tagged-pointer aware.
 * Confidence: high
 */
long sk_field_ref_18_0031a2fc(uint64_t obj)
{
    /* tagged-pointer deref: bit0 set -> load real pointer through masked address */
    if (obj & 1) obj = *(uint64_t *)(obj & ~1ULL);
    return (long)(obj + 0x18) + (long)*(int *)(obj + 0x18);
}


/* FUN_0031a32c @ 0x0031a32c   (est. sk_field_ref_1c_0031a32c)
 * Ghidra: FUN_0031a32c
 * Object relative-reference accessor at +0x1c; tagged-pointer aware.
 * Confidence: high
 */
long sk_field_ref_1c_0031a32c(uint64_t obj)
{
    /* tagged-pointer deref: bit0 set -> load real pointer through masked address */
    if (obj & 1) obj = *(uint64_t *)(obj & ~1ULL);
    return (long)(obj + 0x1c) + (long)*(int *)(obj + 0x1c);
}


/* FUN_0031a35c @ 0x0031a35c   (est. sk_field_ref_20_0031a35c)
 * Ghidra: FUN_0031a35c
 * Object relative-reference accessor at +0x20; tagged-pointer aware.
 * Confidence: high
 */
long sk_field_ref_20_0031a35c(uint64_t obj)
{
    /* tagged-pointer deref: bit0 set -> load real pointer through masked address */
    if (obj & 1) obj = *(uint64_t *)(obj & ~1ULL);
    return (long)(obj + 0x20) + (long)*(int *)(obj + 0x20);
}


/* FUN_0031a38c @ 0x0031a38c   (est. sk_field_ref_24)
 * Ghidra: FUN_0031a38c
 * Object relative-reference accessor at +0x24; tagged-pointer aware.
 * Confidence: high
 */
long sk_field_ref_24(uint64_t obj)
{
    /* tagged-pointer deref: bit0 set -> load real pointer through masked address */
    if (obj & 1) obj = *(uint64_t *)(obj & ~1ULL);
    return (long)(obj + 0x24) + (long)*(int *)(obj + 0x24);
}


/* FUN_0031a44c @ 0x0031a44c   (est. sk_field_ref_34_0031a44c)
 * Ghidra: FUN_0031a44c
 * Object relative-reference accessor at +0x34; tagged-pointer aware.
 * Confidence: high
 */
long sk_field_ref_34_0031a44c(uint64_t obj)
{
    /* tagged-pointer deref: bit0 set -> load real pointer through masked address */
    if (obj & 1) obj = *(uint64_t *)(obj & ~1ULL);
    return (long)(obj + 0x34) + (long)*(int *)(obj + 0x34);
}


/* FUN_0031a4ac @ 0x0031a4ac   (est. sk_field_ref_3c)
 * Ghidra: FUN_0031a4ac
 * Object relative-reference accessor at +0x3c; tagged-pointer aware.
 * Confidence: high
 */
long sk_field_ref_3c(uint64_t obj)
{
    /* tagged-pointer deref: bit0 set -> load real pointer through masked address */
    if (obj & 1) obj = *(uint64_t *)(obj & ~1ULL);
    return (long)(obj + 0x3c) + (long)*(int *)(obj + 0x3c);
}


/* FUN_0031a56c @ 0x0031a56c   (est. sk_field_ref_4c_0031a56c)
 * Ghidra: FUN_0031a56c
 * Object relative-reference accessor at +0x4c; tagged-pointer aware.
 * Confidence: high
 */
long sk_field_ref_4c_0031a56c(uint64_t obj)
{
    /* tagged-pointer deref: bit0 set -> load real pointer through masked address */
    if (obj & 1) obj = *(uint64_t *)(obj & ~1ULL);
    return (long)(obj + 0x4c) + (long)*(int *)(obj + 0x4c);
}


/* FUN_0031a5dc @ 0x0031a5dc   (est. sk_field_ref_0c_0031a5dc)
 * Ghidra: FUN_0031a5dc
 * Object relative-reference accessor at +0xc; tagged-pointer aware.
 * Confidence: high
 */
long sk_field_ref_0c_0031a5dc(uint64_t obj)
{
    /* tagged-pointer deref: bit0 set -> load real pointer through masked address */
    if (obj & 1) obj = *(uint64_t *)(obj & ~1ULL);
    return (long)(obj + 0xc) + (long)*(int *)(obj + 0xc);
}


/* FUN_0031a60c @ 0x0031a60c   (est. sk_field_ref_14_0031a60c)
 * Ghidra: FUN_0031a60c
 * Object relative-reference accessor at +0x14; tagged-pointer aware.
 * Confidence: high
 */
long sk_field_ref_14_0031a60c(uint64_t obj)
{
    /* tagged-pointer deref: bit0 set -> load real pointer through masked address */
    if (obj & 1) obj = *(uint64_t *)(obj & ~1ULL);
    return (long)(obj + 0x14) + (long)*(int *)(obj + 0x14);
}


/* FUN_0031a63c @ 0x0031a63c   (est. sk_field_ref_18_0031a63c)
 * Ghidra: FUN_0031a63c
 * Object relative-reference accessor at +0x18; tagged-pointer aware.
 * Confidence: high
 */
long sk_field_ref_18_0031a63c(uint64_t obj)
{
    /* tagged-pointer deref: bit0 set -> load real pointer through masked address */
    if (obj & 1) obj = *(uint64_t *)(obj & ~1ULL);
    return (long)(obj + 0x18) + (long)*(int *)(obj + 0x18);
}


/* FUN_0031a66c @ 0x0031a66c   (est. sk_field_ref_1c_0031a66c)
 * Ghidra: FUN_0031a66c
 * Object relative-reference accessor at +0x1c; tagged-pointer aware.
 * Confidence: high
 */
long sk_field_ref_1c_0031a66c(uint64_t obj)
{
    /* tagged-pointer deref: bit0 set -> load real pointer through masked address */
    if (obj & 1) obj = *(uint64_t *)(obj & ~1ULL);
    return (long)(obj + 0x1c) + (long)*(int *)(obj + 0x1c);
}


/* FUN_0031a69c @ 0x0031a69c   (est. sk_field_ref_20_0031a69c)
 * Ghidra: FUN_0031a69c
 * Object relative-reference accessor at +0x20; tagged-pointer aware.
 * Confidence: high
 */
long sk_field_ref_20_0031a69c(uint64_t obj)
{
    /* tagged-pointer deref: bit0 set -> load real pointer through masked address */
    if (obj & 1) obj = *(uint64_t *)(obj & ~1ULL);
    return (long)(obj + 0x20) + (long)*(int *)(obj + 0x20);
}


/* FUN_0031a6cc @ 0x0031a6cc   (est. sk_field_ref_24_0031a6cc)
 * Ghidra: FUN_0031a6cc
 * Object relative-reference accessor at +0x24; tagged-pointer aware.
 * Confidence: high
 */
long sk_field_ref_24_0031a6cc(uint64_t obj)
{
    /* tagged-pointer deref: bit0 set -> load real pointer through masked address */
    if (obj & 1) obj = *(uint64_t *)(obj & ~1ULL);
    return (long)(obj + 0x24) + (long)*(int *)(obj + 0x24);
}


/* FUN_0031a6fc @ 0x0031a6fc   (est. sk_field_ref_28)
 * Ghidra: FUN_0031a6fc
 * Object relative-reference accessor at +0x28; tagged-pointer aware.
 * Confidence: high
 */
long sk_field_ref_28(uint64_t obj)
{
    /* tagged-pointer deref: bit0 set -> load real pointer through masked address */
    if (obj & 1) obj = *(uint64_t *)(obj & ~1ULL);
    return (long)(obj + 0x28) + (long)*(int *)(obj + 0x28);
}


/* FUN_0031a96c @ 0x0031a96c   (est. sk_field_ref_5c_0031a96c)
 * Ghidra: FUN_0031a96c
 * Object relative-reference accessor at +0x5c; tagged-pointer aware.
 * Confidence: high
 */
long sk_field_ref_5c_0031a96c(uint64_t obj)
{
    /* tagged-pointer deref: bit0 set -> load real pointer through masked address */
    if (obj & 1) obj = *(uint64_t *)(obj & ~1ULL);
    return (long)(obj + 0x5c) + (long)*(int *)(obj + 0x5c);
}


/* FUN_00319218 @ 0x00319218   (est. sk_nop_leaf)
 * Ghidra: FUN_00319218
 * Leaf stub: FUN_00021480.
 * Confidence: low
 */
void sk_nop_leaf(void)
{
    FUN_00021480();
}


/* FUN_00319230 @ 0x00319230   (est. sk_nop_leaf_00319230)
 * Ghidra: FUN_00319230
 * Leaf stub: FUN_00021480.
 * Confidence: low
 */
void sk_nop_leaf_00319230(void)
{
    FUN_00021480();
}


/* FUN_00319308 @ 0x00319308   (est. sk_nop_leaf_00319308)
 * Ghidra: FUN_00319308
 * Leaf stub: FUN_00021480.
 * Confidence: low
 */
void sk_nop_leaf_00319308(void)
{
    FUN_00021480();
}


/* FUN_00319320 @ 0x00319320   (est. sk_nop_leaf_00319320)
 * Ghidra: FUN_00319320
 * Leaf stub: FUN_00021480.
 * Confidence: low
 */
void sk_nop_leaf_00319320(void)
{
    FUN_00021480();
}


/* FUN_00319338 @ 0x00319338   (est. sk_nop_leaf_00319338)
 * Ghidra: FUN_00319338
 * Leaf stub: FUN_00021480.
 * Confidence: low
 */
void sk_nop_leaf_00319338(void)
{
    FUN_00021480();
}


/* FUN_003193f4 @ 0x003193f4   (est. sk_nop_leaf_003193f4)
 * Ghidra: FUN_003193f4
 * Leaf stub: FUN_00021480.
 * Confidence: low
 */
void sk_nop_leaf_003193f4(void)
{
    FUN_00021480();
}


/* FUN_003194e0 @ 0x003194e0   (est. sk_nop_leaf_003194e0)
 * Ghidra: FUN_003194e0
 * Leaf stub: FUN_00021480.
 * Confidence: low
 */
void sk_nop_leaf_003194e0(void)
{
    FUN_00021480();
}


/* FUN_00319598 @ 0x00319598   (est. sk_nop_leaf_00319598)
 * Ghidra: FUN_00319598
 * Leaf stub: FUN_00021480.
 * Confidence: low
 */
void sk_nop_leaf_00319598(void)
{
    FUN_00021480();
}


/* FUN_003195b0 @ 0x003195b0   (est. sk_nop_leaf_003195b0)
 * Ghidra: FUN_003195b0
 * Leaf stub: FUN_00021480.
 * Confidence: low
 */
void sk_nop_leaf_003195b0(void)
{
    FUN_00021480();
}


/* FUN_003199d4 @ 0x003199d4   (est. sk_nop_leaf_003199d4)
 * Ghidra: FUN_003199d4
 * Leaf stub: FUN_00021480.
 * Confidence: low
 */
void sk_nop_leaf_003199d4(void)
{
    FUN_00021480();
}


/* FUN_003199ec @ 0x003199ec   (est. sk_nop_leaf_003199ec)
 * Ghidra: FUN_003199ec
 * Leaf stub: FUN_00021480.
 * Confidence: low
 */
void sk_nop_leaf_003199ec(void)
{
    FUN_00021480();
}


/* FUN_0031a1dc @ 0x0031a1dc   (est. sk_nop_leaf_0031a1dc)
 * Ghidra: FUN_0031a1dc
 * Leaf stub: FUN_00021480.
 * Confidence: low
 */
void sk_nop_leaf_0031a1dc(void)
{
    FUN_00021480();
}


/* FUN_0031a1f4 @ 0x0031a1f4   (est. sk_nop_leaf_0031a1f4)
 * Ghidra: FUN_0031a1f4
 * Leaf stub: FUN_00021480.
 * Confidence: low
 */
void sk_nop_leaf_0031a1f4(void)
{
    FUN_00021480();
}


/* FUN_0031a29c @ 0x0031a29c   (est. sk_nop_leaf_0031a29c)
 * Ghidra: FUN_0031a29c
 * Leaf stub: FUN_00021480.
 * Confidence: low
 */
void sk_nop_leaf_0031a29c(void)
{
    FUN_00021480();
}


/* FUN_0031a2b4 @ 0x0031a2b4   (est. sk_nop_leaf_0031a2b4)
 * Ghidra: FUN_0031a2b4
 * Leaf stub: FUN_00021480.
 * Confidence: low
 */
void sk_nop_leaf_0031a2b4(void)
{
    FUN_00021480();
}


/* FUN_00319350 @ 0x00319350   (est. sk_resolve_ref_p2)
 * Ghidra: FUN_00319350
 * If param_1 >= 2 resolves via FUN_0036b118 else returns.
 * Confidence: medium
 */
void sk_resolve_ref_p2(uint64_t count, uint64_t p2)
{
    if (count < 2) return;
    FUN_0036b118(p2);
}


/* FUN_00319380 @ 0x00319380   (est. sk_msg_setup_vtable)
 * Ghidra: FUN_00319380
 * Msg setup: reads +0x18/+0x20, builds via FUN_00377824/FUN_00349ea0, stores +0x28, indirect vtable call.
 * Confidence: low
 */
void sk_msg_setup_vtable(void)
{
    FUN_00351cc4();
    uint64_t a = *(uint64_t *)(0 + 0x20);
    uint64_t b = *(uint64_t *)(0 + 0x18);
    *(uint64_t *)(0 + 0x10) = 0;
    *(uint64_t *)(0 + 0x18) = 0;
    FUN_00350bd8(a);
    uint64_t n0 = FUN_00349ea0(), n1 = FUN_00349ea0();
    FUN_00377824(n0, n1, b);
    *(uint64_t *)(0 + 0x28) = 0;
    uint64_t obj_tmp;
    sk_ld_obj_if_flag(&obj_tmp);
    FUN_003511b4();
    (**(code_t **)(0 + 0x10))();   /* indirect dispatch */
}


/* FUN_0031940c @ 0x0031940c   (est. sk_vtable_call)
 * Ghidra: FUN_0031940c
 * Indirect call through +0x18; if x21 nonzero FUN_00354720.
 * Confidence: low
 */
void sk_vtable_call(void)
{
    (**(code_t **)(0 + 0x18))();
    if (0 != 0)
        FUN_00354720();
}


/* FUN_003194bc @ 0x003194bc   (est. sk_msg_forward)
 * Ghidra: FUN_003194bc
 * FUN_001df510 with 7 args from x20 offsets.
 * Confidence: low
 */
void sk_msg_forward(uint64_t a, uint64_t b, uint64_t c)
{
    FUN_001df510(a, b, *(uint64_t *)(0 + 0x20), *(uint64_t *)(0 + 0x28),
                 *(uint64_t *)(0 + 0x10), *(uint64_t *)(0 + 0x18), c);
}


/* FUN_003196b8 @ 0x003196b8   (est. sk_vtable_call_b)
 * Ghidra: FUN_003196b8
 * Indirect call through +0x18.
 * Confidence: low
 */
void sk_vtable_call_b(void)
{
    (**(code_t **)(0 + 0x18))();
}


/* FUN_00319808 @ 0x00319808   (est. sk_clone_vtable)
 * Ghidra: FUN_00319808
 * Copies +0x18, calls vtable fn (via *(lVar1-8)) to clone src into dst.
 * Confidence: low
 */
long sk_clone_vtable(long dst, long src)
{
    long v = *(long *)(src + 0x18);
    *(long *)(dst + 0x18) = v;
    /* vtable dispatch: call the function pointer stored at *(v-8) (PAC'd) */
    typedef void (*clone_fn_t)(long, long);
    (*(clone_fn_t *)(*(uint64_t *)(v + -8)))(dst, src);
    return dst;
}


/* FUN_003198cc @ 0x003198cc   (est. sk_validate_ret)
 * Ghidra: FUN_003198cc
 * If FUN_0036298c(param_2)==0 returns 0 else param_1.
 * Confidence: medium
 */
uint64_t sk_validate_ret(uint64_t a, uint64_t b)
{
    if (FUN_0036298c(b) == 0) a = 0;
    return a;
}


/* FUN_0031996c @ 0x0031996c   (est. sk_forward2_a)
 * Ghidra: FUN_0031996c
 * FUN_0032f900(b, a).
 * Confidence: low
 */
void sk_forward2_a(uint64_t a, uint64_t b)
{
    FUN_0032f900(b, a);
}


/* FUN_003199ac @ 0x003199ac   (est. sk_identity_ret)
 * Ghidra: FUN_003199ac
 * FUN_000026e8; returns param_1 unchanged.
 * Confidence: low
 */
uint64_t sk_identity_ret(uint64_t a)
{
    FUN_000026e8();
    return a;
}


/* FUN_00319a04 @ 0x00319a04   (est. sk_forward2_b)
 * Ghidra: FUN_00319a04
 * FUN_0032b558(b, a).
 * Confidence: low
 */
void sk_forward2_b(uint64_t a, uint64_t b)
{
    FUN_0032b558(b, a);
}


/* FUN_00319a14 @ 0x00319a14   (est. sk_forward2_c)
 * Ghidra: FUN_00319a14
 * FUN_0032b9dc(b, a).
 * Confidence: low
 */
void sk_forward2_c(uint64_t a, uint64_t b)
{
    FUN_0032b9dc(b, a);
}


/* FUN_00319a24 @ 0x00319a24   (est. sk_forward2_d)
 * Ghidra: FUN_00319a24
 * FUN_0032b924; returns param_1.
 * Confidence: low
 */
uint64_t sk_forward2_d(uint64_t a)
{
    FUN_0032b924();
    return a;
}


/* FUN_00319a4c @ 0x00319a4c   (est. sk_ld_obj_if_flag)
 * Ghidra: FUN_00319a4c
 * FUN_00358c20 + FUN_0035295c; if (+0x52>>1)&1 loads via FUN_0036aae4.
 * Confidence: low
 */
uint64_t sk_ld_obj_if_flag(uint64_t *out)
{
    FUN_00358c20();
    FUN_0035295c();
    if ((*(uint8_t *)(0 + 0x52) >> 1 & 1) != 0) {
        *out = FUN_0036aae4();          /* register-forwarded lo */
        return FUN_0036aae4();          /* register-forwarded hi */
    }
    return 0;
}


/* FUN_00319ac0 @ 0x00319ac0   (est. sk_msg_leaf_a)
 * Ghidra: FUN_00319ac0
 * FUN_003a25d4(+0x18) + FUN_0036b21c.
 * Confidence: low
 */
void sk_msg_leaf_a(void)
{
    FUN_003a25d4(*(uint64_t *)(0 + 0x18));
    FUN_0036b21c();
}


/* FUN_00319ac4 @ 0x00319ac4   (est. sk_msg_leaf_b)
 * Ghidra: FUN_00319ac4
 * FUN_003a25d4(+0x18) + FUN_0036b21c.
 * Confidence: low
 */
void sk_msg_leaf_b(void)
{
    FUN_003a25d4(*(uint64_t *)(0 + 0x18));
    FUN_0036b21c();
}


/* FUN_0031a20c @ 0x0031a20c   (est. sk_msg_teardown)
 * Ghidra: FUN_0031a20c
 * Teardown sequence FUN_00358fb4/0034bb84/000f5e08/0034c2a4/00352e60/0022fb38 + FUN_00358fc8.
 * Confidence: low
 */
void sk_msg_teardown(void)
{
    FUN_00358fb4();
    FUN_0034bb84();
    FUN_000f5e08();
    FUN_0034c2a4();
    FUN_00352e60();
    FUN_0022fb38();
    FUN_00358fc8(0);
}


/* FUN_00319440 @ 0x00319440   (est. sk_leaf_43d18)
 * Ghidra: FUN_00319440
 * Leaf: FUN_00343d18.
 * Confidence: low
 */
void sk_leaf_43d18(void)
{
    FUN_00343d18();
}
