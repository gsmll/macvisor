/* Recreated from ringminus1/sk/cl4_kernel.raw (cL4 microkernel, arm64e, image base 0).
 * Ground truth: Ghidra FUN_ names + addresses. Names use cL4/seL4 vocabulary;
 * estimates unless matched.
 *
 * Slice 4: 0x228e50 - 0x232af8 (121 functions).  This is the Swift standard
 * library runtime statically linked into the cL4 kernel: radix parsing /
 * formatting of the integer types, checked divide-with-remainder with overflow
 * traps, the SipHash _Hasher core, hash-table bitmap primitives, and string /
 * buffer helpers.  Most bodies reconstruct as dense sequences of opaque Swift
 * runtime calls (retain/release, object allocation, method dispatch) rather
 * than clean microkernel logic, so confidence is low unless a trap string or
 * the primitive (SipHash rounds, bit-width, division) matches unambiguously.
 */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "sk_internal.h"

/* Forward declarations of in-slice functions (generated from definitions). */
void *sk_swift_object_alloc(long *out, unsigned long a, unsigned long c);
long skp4_sk_double_to_word(void);
void sk_format_i32_cb(unsigned long out, const char *p, long len, unsigned long radix,
                      long bound, unsigned long m6, unsigned long m7, unsigned long cb);
void skp4_sk_format_i64_cb(unsigned long out, const char *p, long len, unsigned long radix,
                      long bound, unsigned long m6, unsigned long cb);
void sk_format_uint128(unsigned long out, const unsigned char *p, long len, long radix,
                       unsigned int sign, long meta, unsigned long cb);
unsigned long sk_hashtable_next_clear_bit(unsigned long bit, const unsigned long *bm, long wc);
unsigned long skp4_sk_hashtable_next_clear_bit_b(unsigned long bit, const unsigned long *bm, long wc);
unsigned long skp4_sk_hashtable_next_set_bit(unsigned long bit, const unsigned long *bm, long wc);
long skp4_sk_hashtable_prev_set_bit(const unsigned long *bm, long wc);
void skp4_sk_i128_divmod(long *out, unsigned long dlo, unsigned long dhi, unsigned long qlo, long qhi);
cl4_result_t sk_i128_is_positive(long lo, long hi);
bool sk_i128_is_zero(unsigned long a, unsigned long b, unsigned long c, unsigned long d, unsigned long e);
int skp4_sk_i16_divmod(short *rem, short d, short n);
int sk_i32_divmod(int *rem, int d, int n);
unsigned long sk_i64_bit_width(long v);
long skp4_sk_i64_divmod(long *rem, long d, long n);
int skp4_sk_i8_divmod(char *rem, char d, char n);
void skp4_sk_memmove(unsigned long src, long n, unsigned long dst);
void sk_memmove_dispatch(unsigned long a, long n, unsigned long dst);
unsigned int sk_parse_i16(const unsigned char *p, long len, long radix, long bound);
unsigned long sk_parse_i32(const unsigned char *p, long len, long radix, long bound);
long skp4_sk_parse_i64(unsigned long a, long len, long radix, unsigned long bound);
unsigned int skp4_sk_parse_i8(const unsigned char *p, long len, long radix, long bound);
void skp4_sk_parse_signed_wrap(const char *p, long len, unsigned long out, void (*cb)(unsigned long, long, unsigned long, unsigned long));
unsigned int sk_parse_u16(const unsigned char *p, long len, long radix, long bound);
unsigned long sk_parse_u32(const unsigned char *p, long len, unsigned long radix, long bound);
unsigned long skp4_sk_parse_u64(unsigned long a, long len, long radix, unsigned long bound);
unsigned int sk_parse_u8(const unsigned char *p, long len, long radix, long bound);
cl4_result_t skp4_sk_parse_uint128(const unsigned char *p, long len, unsigned long radix, unsigned int flag);
cl4_result_t sk_parse_uint128_str(const unsigned char *p, long len, unsigned long radix, long bound);
void sk_siphash_absorb_byte(unsigned long b);
void sk_siphash_absorb_bytes(const unsigned char *p, long len);
void sk_siphash_compress(unsigned long m);
void sk_siphash_compress_thunk(unsigned long m);
void sk_siphash_final_shift16(unsigned long m);
void sk_siphash_final_shift8(unsigned long m);
void skp4_sk_siphash_finalize(void);
void sk_siphash_finalize_thunk(void);
unsigned long skp4_sk_siphash_hash_keyed(unsigned long seed, const unsigned long *p, long len);
unsigned long sk_siphash_hash_word(unsigned long a, unsigned long b, long len);
void skp4_sk_siphash_state_init(void);
void sk_swift_array_elem_wrap(unsigned long a, long idx, unsigned long c, long base, long slot);
void sk_swift_array_remove(void);
void skp4_sk_swift_array_store_check(unsigned long a, long idx, unsigned long c,
                                long base, long slot);
void skp4_sk_swift_array_subscript_read(void);
void sk_swift_array_subscript_write(unsigned long a, long slot);
void skp4_sk_swift_buffer_append(unsigned long a, long slot);
void skp4_sk_swift_buffer_subscript_check(long idx, unsigned long a, long p, long n, long slot);
unsigned long sk_swift_collection_retain_return(void);
void sk_swift_dict_get(unsigned long a);
void sk_swift_dict_get_b(unsigned long a);
void sk_swift_double_convert(void);
void sk_swift_elem_dispatch(unsigned long a, long slot);
void sk_swift_fatal_bitwidth_a(void);
void skp4_sk_swift_fatal_bitwidth_b(void);
void skp4_sk_swift_fatal_bitwidth_c(void);
void skp4_sk_swift_fatal_bitwidth_d(void);
void skp4_sk_swift_fatal_bitwidth_e(void);
void skp4_sk_swift_fatal_bitwidth_f(void);
void skp4_sk_swift_fatal_bitwidth_g(void);
void skp4_sk_swift_fatal_bitwidth_h(void);
void sk_swift_fatal_generic(void);
void sk_swift_fatal_generic2(void);
void sk_swift_format_engine(unsigned long a, unsigned long b, unsigned long c, unsigned int flags,
                            unsigned long p5, unsigned long p6, void (*cb)(void), unsigned long p8);
void sk_swift_format_engine_hex(unsigned long a, unsigned long b, unsigned long c,
                                unsigned long d, unsigned long p5, unsigned long p6,
                                unsigned long p7);
void sk_swift_hashindex_cmp_fatal_a(void);
void skp4_sk_swift_hashindex_cmp_fatal_b(void);
void sk_swift_hashtable_popcount(void);
void sk_swift_hex_fmt_full(unsigned long a, unsigned long b, unsigned long c);
void skp4_sk_swift_hex_parse_engine(void);
void sk_swift_locked_append(void);
void sk_swift_noop(long a);
void sk_swift_obj_format(void);
void skp4_sk_swift_obj_retain_construct(unsigned long a, unsigned long b, unsigned long c);
cl4_result_t sk_swift_object_build(long *out, unsigned long a, long meta);
void skp4_sk_swift_object_build_dispatch(void);
unsigned long sk_swift_object_build_dispatch_r(void);
void skp4_sk_swift_object_construct(void);
void sk_swift_object_init_vtable(unsigned long obj, unsigned long a, long meta);
void sk_swift_object_teardown(void);
void sk_swift_range_subscript(void);
void sk_swift_retain_dispatch(void);
void skp4_sk_swift_retain_dispatch2(void);
void sk_swift_retain_dispatch_store(void);
unsigned long sk_swift_retain_eq_check(void);
unsigned long sk_swift_retain_eq_wrap(void);
void skp4_sk_swift_str_first_byte(void);
void sk_swift_str_first_byte_b(void);
void sk_swift_str_first_byte_c(void);
void skp4_sk_swift_str_first_byte_fmt(unsigned long a, unsigned long b, unsigned long c);
void sk_swift_str_first_byte_hi(void);
void sk_swift_str_trim(void);
void sk_swift_str_u8_escape(void);
void sk_swift_string_append_fmt(unsigned long a, unsigned long b, unsigned long c,
                                long meta, unsigned long p5, unsigned long p6, unsigned long p7);
void sk_swift_string_compose(void);
void skp4_sk_swift_string_parse_dispatch(void);
void skp4_sk_swift_string_parse_or_format(void);
cl4_result_t sk_swift_string_utf8_convert(unsigned long a, unsigned long b, unsigned long c);
cl4_result_t sk_swift_value_init(void);
cl4_result_t sk_swift_value_init_impl(unsigned long a, unsigned long b, unsigned long f);
void sk_swift_value_init_wrap(unsigned long a, unsigned long b);
void skp4_sk_swift_value_pair_construct(uint64_t *out);
void sk_swift_value_pair_copy(uint64_t *out);
void sk_swift_vtable_dispatch(unsigned long a, unsigned long b, unsigned long c,
                              void (*jt)(void));
void sk_swift_vtable_dispatch2(void);
void sk_u128_divmod(long *out, unsigned long dlo, long dhi, unsigned long qlo, long qhi);
cl4_result_t sk_u128_from_nonzero(long lo, long hi);
bool sk_u128_is_nonzero(long lo, long hi);
bool sk_u128_is_nonzero_b(long lo, long hi);
bool sk_u128_is_zero(unsigned long a, unsigned long b, unsigned long c, unsigned long d);
long sk_u16_bit_width(unsigned short v);
unsigned int skp4_sk_u16_divmod(short *rem, unsigned short d, unsigned short n);
long sk_u32_bit_width(int v);
unsigned int skp4_sk_u32_divmod(int *rem, unsigned int d, unsigned int n);
unsigned int skp4_sk_u32_load_aligned(long base, long off);
unsigned long sk_u64_bit_width(unsigned long v);
unsigned long skp4_sk_u64_divmod(long *rem, unsigned long d, unsigned long n);
unsigned long sk_u64_eq_predicate(unsigned long a, unsigned long b, unsigned long c);
unsigned long sk_u64_eq_predicate_b(unsigned long a, unsigned long b, unsigned long c);
unsigned int skp4_sk_u8_divmod(char *rem, unsigned char d, unsigned char n);


/* Function externs (out-of-slice helpers): descriptive + raw FUN_ names.
 * cl4_result_t where used as 16-byte result, else unsigned long. Empty parens.
 * FUN_ addr in comment where the raw name is used. */

extern unsigned long skp4_FUN_00002534();
extern cl4_result_t skp4_FUN_0001d4a0();
extern unsigned long skp4_FUN_0001df60();
extern unsigned long skp4_FUN_00027724();
extern unsigned long skp4_FUN_00027754();
extern unsigned long skp4_FUN_00068e14();
extern unsigned long skp4_FUN_0006a414();
extern unsigned long skp4_FUN_0006a4c0();
extern unsigned long skp4_FUN_0006b6f4();
extern unsigned long skp4_FUN_000777d4();
extern unsigned long skp4_FUN_0007c1a4();
extern unsigned long skp4_FUN_0007c1c4();
extern unsigned long skp4_FUN_000839d8();
extern unsigned long skp4_FUN_00084180();
extern unsigned long skp4_FUN_00084220();
extern unsigned long skp4_FUN_00084234();
extern unsigned long skp4_FUN_00086368();
extern unsigned long skp4_FUN_0008f6c0();
extern unsigned long skp4_FUN_0008f6f4();
extern unsigned long skp4_FUN_0009461c();
extern unsigned long skp4_FUN_000a68c4();
extern unsigned long skp4_FUN_000a68f4();
extern unsigned long skp4_FUN_000a6f88();
extern unsigned long skp4_FUN_000e15d8();
extern unsigned long skp4_FUN_00100efc();
extern cl4_result_t skp4_FUN_00106e3c();
extern unsigned long skp4_FUN_00117d14();
extern unsigned long skp4_FUN_0011d800();
extern unsigned long skp4_FUN_0011db10();
extern unsigned long skp4_FUN_0011db18();
extern unsigned long skp4_FUN_0014ae44();
extern unsigned long skp4_FUN_0015fe34();
extern unsigned long skp4_FUN_0017fd54();
extern unsigned long skp4_FUN_001afe4c();
extern unsigned long skp4_FUN_001b07b8();
extern unsigned long skp4_FUN_001b8cf4();
extern unsigned long skp4_FUN_001d9840();
extern unsigned long skp4_FUN_001e3f70();
extern unsigned long skp4_FUN_001e4164();
extern cl4_result_t skp4_FUN_001e4cbc();
extern unsigned long skp4_FUN_00205844();
extern unsigned long skp4_FUN_002060d4();
extern unsigned long skp4_FUN_0021867c();
extern unsigned long skp4_FUN_0028c660();
extern unsigned long skp4_FUN_0028c754();
extern unsigned long skp4_FUN_002a3e64();
extern cl4_result_t skp4_FUN_002a9ba8();
extern unsigned long skp4_FUN_0031090c();
extern unsigned long skp4_FUN_003109b4();
extern unsigned long skp4_FUN_00310a14();
extern unsigned long skp4_FUN_00310a44();
extern unsigned long skp4_FUN_00310a74();
extern unsigned long skp4_FUN_00310ad4();
extern unsigned long skp4_FUN_00310b08();
extern unsigned long skp4_FUN_00310d1c();
extern unsigned long skp4_FUN_00310d68();
extern unsigned long skp4_FUN_00311a3c();
extern unsigned long skp4_FUN_00312d08();
extern unsigned long skp4_FUN_00319658();
extern unsigned long skp4_FUN_0031993c();
extern unsigned long skp4_FUN_0031997c();
extern unsigned long skp4_FUN_0031b080();
extern unsigned long skp4_FUN_0031b37c();
extern unsigned long skp4_FUN_0031b578();
extern unsigned long skp4_FUN_0031c430();
extern unsigned long skp4_FUN_0031c490();
extern unsigned long skp4_FUN_0031c670();
extern unsigned long skp4_FUN_0031c688();
extern unsigned long skp4_FUN_0031c748();
extern unsigned long skp4_FUN_0031c7e4();
extern unsigned long skp4_FUN_0031e030();
extern unsigned long skp4_FUN_0031e104();
extern unsigned long skp4_FUN_00343a30();
extern unsigned long skp4_FUN_00344d9c();
extern unsigned long skp4_FUN_00347fb4();
extern unsigned long skp4_FUN_00348160();
extern unsigned long skp4_FUN_00348194();
extern unsigned long skp4_FUN_003481cc();
extern unsigned long skp4_FUN_0034843c();
extern unsigned long skp4_FUN_003484b4();
extern unsigned long skp4_FUN_003486b8();
extern unsigned long skp4_FUN_003488bc();
extern unsigned long skp4_FUN_0034895c();
extern unsigned long skp4_FUN_00348b7c();
extern unsigned long skp4_FUN_00348bbc();
extern unsigned long skp4_FUN_00348ce8();
extern unsigned long skp4_FUN_00348d4c();
extern unsigned long skp4_FUN_00348e00();
extern unsigned long skp4_FUN_00348e18();
extern unsigned long skp4_FUN_00348e48();
extern unsigned long skp4_FUN_00348e60();
extern unsigned long skp4_FUN_00348e78();
extern unsigned long skp4_FUN_00348f38();
extern unsigned long skp4_FUN_00348f50();
extern unsigned long skp4_FUN_00348fb4();
extern unsigned long skp4_FUN_00349080();
extern unsigned long skp4_FUN_003490b8();
extern unsigned long skp4_FUN_0034911c();
extern unsigned long skp4_FUN_00349178();
extern unsigned long skp4_FUN_003492ac();
extern unsigned long skp4_FUN_00349370();
extern unsigned long skp4_FUN_003493c4();
extern unsigned long skp4_FUN_003493d8();
extern unsigned long skp4_FUN_003493ec();
extern unsigned long skp4_FUN_003494e8();
extern unsigned long skp4_FUN_003494fc();
extern unsigned long skp4_FUN_0034951c();
extern unsigned long skp4_FUN_0034970c();
extern unsigned long skp4_FUN_00349748();
extern unsigned long skp4_FUN_0034975c();
extern unsigned long skp4_FUN_0034998c();
extern unsigned long skp4_FUN_00349b64();
extern unsigned long skp4_FUN_00349c2c();
extern unsigned long skp4_FUN_00349c44();
extern unsigned long skp4_FUN_00349c70();
extern unsigned long skp4_FUN_00349c84();
extern unsigned long skp4_FUN_00349d80();
extern cl4_result_t skp4_FUN_00349dfc();
extern unsigned long skp4_FUN_00349e10();
extern unsigned long skp4_FUN_00349eb8();
extern unsigned long skp4_FUN_00349f24();
extern unsigned long skp4_FUN_00349f3c();
extern unsigned long skp4_FUN_0034a1c8();
extern unsigned long skp4_FUN_0034a2ac();
extern unsigned long skp4_FUN_0034a368();
extern unsigned long skp4_FUN_0034a400();
extern unsigned long skp4_FUN_0034a414();
extern unsigned long skp4_FUN_0034a464();
extern unsigned long skp4_FUN_0034a4e0();
extern unsigned long skp4_FUN_0034a4f8();
extern unsigned long skp4_FUN_0034a62c();
extern unsigned long skp4_FUN_0034a9c0();
extern unsigned long skp4_FUN_0034a9d4();
extern unsigned long skp4_FUN_0034aa14();
extern unsigned long skp4_FUN_0034aa54();
extern unsigned long skp4_FUN_0034ac14();
extern unsigned long skp4_FUN_0034acd0();
extern unsigned long skp4_FUN_0034acf0();
extern unsigned long skp4_FUN_0034ad00();
extern unsigned long skp4_FUN_0034ae44();
extern unsigned long skp4_FUN_0034aee4();
extern unsigned long skp4_FUN_0034af04();
extern unsigned long skp4_FUN_0034af20();
extern unsigned long skp4_FUN_0034b0c4();
extern unsigned long skp4_FUN_0034b1dc();
extern unsigned long skp4_FUN_0034b2f8();
extern unsigned long skp4_FUN_0034b348();
extern unsigned long skp4_FUN_0034b368();
extern unsigned long skp4_FUN_0034b3c8();
extern unsigned long skp4_FUN_0034b3d8();
extern unsigned long skp4_FUN_0034b4c0();
extern unsigned long skp4_FUN_0034b4d0();
extern unsigned long skp4_FUN_0034b590();
extern cl4_result_t skp4_FUN_0034b614();
extern unsigned long skp4_FUN_0034b758();
extern unsigned long skp4_FUN_0034b85c();
extern unsigned long skp4_FUN_0034b8bc();
extern unsigned long skp4_FUN_0034b9f8();
extern unsigned long skp4_FUN_0034ba38();
extern unsigned long skp4_FUN_0034baa8();
extern unsigned long skp4_FUN_0034bb60();
extern unsigned long skp4_FUN_0034bc80();
extern unsigned long skp4_FUN_0034be54();
extern unsigned long skp4_FUN_0034bf48();
extern unsigned long skp4_FUN_0034bfc4();
extern unsigned long skp4_FUN_0034c084();
extern unsigned long skp4_FUN_0034c0ec();
extern unsigned long skp4_FUN_0034c180();
extern unsigned long skp4_FUN_0034c290();
extern unsigned long skp4_FUN_0034c308();
extern unsigned long skp4_FUN_0034c384();
extern unsigned long skp4_FUN_0034c3d4();
extern unsigned long skp4_FUN_0034c3f4();
extern unsigned long skp4_FUN_0034c414();
extern unsigned long skp4_FUN_0034c59c();
extern unsigned long skp4_FUN_0034c6c4();
extern unsigned long skp4_FUN_0034c754();
extern unsigned long skp4_FUN_0034c8c8();
extern unsigned long skp4_FUN_0034cdd8();
extern cl4_result_t skp4_FUN_0034ce18();
extern unsigned long skp4_FUN_0034ce28();
extern unsigned long skp4_FUN_0034ce58();
extern unsigned long skp4_FUN_0034ce78();
extern unsigned long skp4_FUN_0034ce88();
extern unsigned long skp4_FUN_0034cf44();
extern unsigned long skp4_FUN_0034d180();
extern unsigned long skp4_FUN_0034d314();
extern unsigned long skp4_FUN_0034d334();
extern cl4_result_t skp4_FUN_0034d374();
extern unsigned long skp4_FUN_0034d558();
extern unsigned long skp4_FUN_0034d5ec();
extern unsigned long skp4_FUN_0034d5fc();
extern unsigned long skp4_FUN_0034d788();
extern unsigned long skp4_FUN_0034d954();
extern unsigned long skp4_FUN_0034d970();
extern unsigned long skp4_FUN_0034da38();
extern unsigned long skp4_FUN_0034daa8();
extern unsigned long skp4_FUN_0034dab8();
extern unsigned long skp4_FUN_0034daf8();
extern unsigned long skp4_FUN_0034db98();
extern unsigned long skp4_FUN_0034dc04();
extern unsigned long skp4_FUN_0034dc20();
extern unsigned long skp4_FUN_0034def4();
extern unsigned long skp4_FUN_0034df34();
extern unsigned long skp4_FUN_0034e084();
extern unsigned long skp4_FUN_0034e130();
extern unsigned long skp4_FUN_0034e15c();
extern unsigned long skp4_FUN_0034e3bc();
extern unsigned long skp4_FUN_0034e424();
extern unsigned long skp4_FUN_0034e464();
extern unsigned long skp4_FUN_0034e50c();
extern unsigned long skp4_FUN_0034e57c();
extern unsigned long skp4_FUN_0034e74c();
extern unsigned long skp4_FUN_0034e784();
extern unsigned long skp4_FUN_0034e8fc();
extern unsigned long skp4_FUN_0034ed48();
extern unsigned long skp4_FUN_0034ee18();
extern unsigned long skp4_FUN_0034ee48();
extern unsigned long skp4_FUN_0034eec8();
extern unsigned long skp4_FUN_0034f730();
extern unsigned long skp4_FUN_0034fcc0();
extern unsigned long skp4_FUN_0034fd3c();
extern unsigned long skp4_FUN_0034fdcc();
extern unsigned long skp4_FUN_0034fe08();
extern unsigned long skp4_FUN_0034fee0();
extern unsigned long skp4_FUN_0034ff78();
extern unsigned long skp4_FUN_00350078();
extern unsigned long skp4_FUN_003503f8();
extern unsigned long skp4_FUN_00350428();
extern unsigned long skp4_FUN_00350434();
extern unsigned long skp4_FUN_0035044c();
extern unsigned long skp4_FUN_00350464();
extern unsigned long skp4_FUN_00350470();
extern unsigned long skp4_FUN_0035047c();
extern unsigned long skp4_FUN_003504ac();
extern unsigned long skp4_FUN_003504d0();
extern unsigned long skp4_FUN_00350518();
extern unsigned long skp4_FUN_00350524();
extern unsigned long skp4_FUN_0035056c();
extern unsigned long skp4_FUN_00350578();
extern unsigned long skp4_FUN_0035060c();
extern unsigned long skp4_FUN_00350624();
extern unsigned long skp4_FUN_00350630();
extern unsigned long skp4_FUN_0035063c();
extern unsigned long skp4_FUN_00350694();
extern unsigned long skp4_FUN_00350744();
extern unsigned long skp4_FUN_00350768();
extern unsigned long skp4_FUN_00350774();
extern unsigned long skp4_FUN_00350798();
extern unsigned long skp4_FUN_003507e0();
extern unsigned long skp4_FUN_00350884();
extern unsigned long skp4_FUN_003508cc();
extern unsigned long skp4_FUN_003508fc();
extern unsigned long skp4_FUN_00350950();
extern unsigned long skp4_FUN_00350974();
extern unsigned long skp4_FUN_0035098c();
extern unsigned long skp4_FUN_003509a4();
extern unsigned long skp4_FUN_003509ec();
extern unsigned long skp4_FUN_00350a7c();
extern unsigned long skp4_FUN_00350adc();
extern unsigned long skp4_FUN_00350b00();
extern unsigned long skp4_FUN_00350b54();
extern unsigned long skp4_FUN_00350bf0();
extern unsigned long skp4_FUN_00350c08();
extern unsigned long skp4_FUN_00350c38();
extern unsigned long skp4_FUN_00350c50();
extern unsigned long skp4_FUN_00350c68();
extern unsigned long skp4_FUN_00350e34();
extern unsigned long skp4_FUN_00350eb0();
extern unsigned long skp4_FUN_003510ac();
extern unsigned long skp4_FUN_003510b8();
extern unsigned long skp4_FUN_00351148();
extern unsigned long skp4_FUN_00351184();
extern unsigned long skp4_FUN_003511f0();
extern unsigned long skp4_FUN_0035122c();
extern unsigned long skp4_FUN_0035125c();
extern unsigned long skp4_FUN_0035133c();
extern unsigned long skp4_FUN_00351384();
extern unsigned long skp4_FUN_00351414();
extern unsigned long skp4_FUN_00351444();
extern unsigned long skp4_FUN_00351468();
extern unsigned long skp4_FUN_003514e8();
extern unsigned long skp4_FUN_003515b4();
extern unsigned long skp4_FUN_003515f0();
extern unsigned long skp4_FUN_00351684();
extern unsigned long skp4_FUN_003516b4();
extern unsigned long skp4_FUN_003516fc();
extern unsigned long skp4_FUN_0035172c();
extern unsigned long skp4_FUN_003517cc();
extern unsigned long skp4_FUN_003518c4();
extern unsigned long skp4_FUN_00351930();
extern unsigned long skp4_FUN_00351a74();
extern unsigned long skp4_FUN_00351ad4();
extern unsigned long skp4_FUN_00351b20();
extern unsigned long skp4_FUN_00351be0();
extern unsigned long skp4_FUN_00351bec();
extern unsigned long skp4_FUN_00351c94();
extern cl4_result_t skp4_FUN_00351cb8();
extern unsigned long skp4_FUN_00351d4c();
extern unsigned long skp4_FUN_00351e14();
extern unsigned long skp4_FUN_00351e48();
extern unsigned long skp4_FUN_00351ee0();
extern unsigned long skp4_FUN_00351ef8();
extern unsigned long skp4_FUN_00351f10();
extern unsigned long skp4_FUN_00351fd0();
extern unsigned long skp4_FUN_003520a4();
extern unsigned long skp4_FUN_00352240();
extern unsigned long skp4_FUN_003522c8();
extern unsigned long skp4_FUN_00352320();
extern unsigned long skp4_FUN_003523f0();
extern unsigned long skp4_FUN_003523fc();
extern unsigned long skp4_FUN_00352420();
extern unsigned long skp4_FUN_003524c8();
extern cl4_result_t skp4_FUN_00352800();
extern unsigned long skp4_FUN_00352864();
extern unsigned long skp4_FUN_00352894();
extern unsigned long skp4_FUN_00352980();
extern unsigned long skp4_FUN_00352c1c();
extern unsigned long skp4_FUN_00352c34();
extern unsigned long skp4_FUN_00352cb0();
extern unsigned long skp4_FUN_00352d70();
extern unsigned long skp4_FUN_00352e0c();
extern unsigned long skp4_FUN_00352e48();
extern unsigned long skp4_FUN_00352ee4();
extern unsigned long skp4_FUN_00352f54();
extern unsigned long skp4_FUN_00352f60();
extern unsigned long skp4_FUN_0035308c();
extern unsigned long skp4_FUN_00353124();
extern unsigned long skp4_FUN_003531c0();
extern unsigned long skp4_FUN_00353990();
extern unsigned long skp4_FUN_00353a18();
extern unsigned long skp4_FUN_00353a6c();
extern unsigned long skp4_FUN_00353d7c();
extern unsigned long skp4_FUN_00353dfc();
extern unsigned long skp4_FUN_00353ecc();
extern unsigned long skp4_FUN_00353f50();
extern unsigned long skp4_FUN_00353f94();
extern unsigned long skp4_FUN_00354094();
extern unsigned long skp4_FUN_003542a8();
extern unsigned long skp4_FUN_003542b8();
extern unsigned long skp4_FUN_00354474();
extern unsigned long skp4_FUN_00354588();
extern unsigned long skp4_FUN_00354678();
extern unsigned long skp4_FUN_00354840();
extern unsigned long skp4_FUN_003548d0();
extern unsigned long skp4_FUN_00354b44();
extern unsigned long skp4_FUN_00354b80();
extern unsigned long skp4_FUN_00354d08();
extern unsigned long skp4_FUN_00354d5c();
extern unsigned long skp4_FUN_00354d94();
extern unsigned long skp4_FUN_00355394();
extern unsigned long skp4_FUN_00355560();
extern unsigned long skp4_FUN_00355884();
extern unsigned long skp4_FUN_003559bc();
extern unsigned long skp4_FUN_00355ab4();
extern unsigned long skp4_FUN_00355b1c();
extern unsigned long skp4_FUN_00355bb8();
extern unsigned long skp4_FUN_00355cf4();
extern unsigned long skp4_FUN_00355dcc();
extern unsigned long skp4_FUN_00355dfc();
extern cl4_result_t skp4_FUN_003560e4();
extern unsigned long skp4_FUN_0035614c();
extern unsigned long skp4_FUN_00356200();
extern unsigned long skp4_FUN_00356260();
extern unsigned long skp4_FUN_00356370();
extern unsigned long skp4_FUN_003564d0();
extern unsigned long skp4_FUN_00356530();
extern unsigned long skp4_FUN_00356578();
extern unsigned long skp4_FUN_003567a4();
extern unsigned long skp4_FUN_00356a20();
extern unsigned long skp4_FUN_00356a94();
extern unsigned long skp4_FUN_003570bc();
extern unsigned long skp4_FUN_00357368();
extern unsigned long skp4_FUN_0035764c();
extern unsigned long skp4_FUN_00357b88();
extern unsigned long skp4_FUN_00357c44();
extern unsigned long skp4_FUN_00357cb4();
extern unsigned long skp4_FUN_003583dc();
extern unsigned long skp4_FUN_0035896c();
extern unsigned long skp4_FUN_00358f60();
extern unsigned long skp4_FUN_00358fe8();
extern unsigned long skp4_FUN_00359338();
extern unsigned long skp4_FUN_00359490();
extern unsigned long skp4_FUN_00359a24();
extern unsigned long skp4_FUN_00359a6c();
extern unsigned long skp4_FUN_00359dc4();
extern unsigned long skp4_FUN_0035a2ac();
extern unsigned long skp4_FUN_0035a478();
extern unsigned long skp4_FUN_0035a700();
extern cl4_result_t skp4_FUN_0035a758();
extern unsigned long skp4_FUN_0035a8d0();
extern unsigned long skp4_FUN_00365b6c();
extern unsigned long skp4_FUN_003722e4();
extern unsigned long skp4_FUN_00376820();
extern unsigned long skp4_FUN_00377824();
extern unsigned long skp4_FUN_00377dcc();
extern unsigned long skp4_FUN_003a25d4();
extern unsigned long skp4_sk_alloc();
extern unsigned long skp4_sk_alloc_pages();
extern cl4_result_t skp4_sk_cpu();
extern unsigned long skp4_sk_cpu_flag_get();
extern unsigned long skp4_sk_cpu_restore();
extern unsigned long skp4_sk_irqrestore();
extern unsigned long skp4_sk_lock();
extern unsigned long skp4_sk_spin_irqsave();
extern unsigned long skp4_sk_swift_fatal_bitwidth();
extern unsigned long skp4_sk_swift_fatal_error();
extern unsigned long skp4_sk_swift_hashindex_cmp_fatal();
extern unsigned long skp4_swift_alloc_object();
extern unsigned long skp4_swift_bits_ones();
extern cl4_result_t skp4_swift_bounds_check();
extern unsigned long skp4_swift_brk();
extern unsigned long skp4_swift_brk2();
extern unsigned long skp4_swift_brk3();
extern unsigned long skp4_swift_brk4();
extern unsigned long skp4_swift_brk5();
extern unsigned long skp4_swift_brk6();
extern unsigned long skp4_swift_brk7();
extern unsigned long skp4_swift_brk8();
extern unsigned long skp4_swift_brk9();
extern unsigned long skp4_swift_brk_a();
extern unsigned long skp4_swift_brk_b();
extern unsigned long skp4_swift_brk_c();
extern unsigned long skp4_swift_brk_d();
extern unsigned long skp4_swift_brk_e();
extern unsigned long skp4_swift_brk_f();
extern unsigned long skp4_swift_destroy_temp();
extern unsigned long skp4_swift_digit_value();
extern unsigned long skp4_swift_fatal_3();
extern unsigned long skp4_swift_fatal_4();
extern unsigned long skp4_swift_fatal_5();
extern unsigned long skp4_swift_hash_combine();
extern unsigned long skp4_swift_hash_final0();
extern cl4_result_t skp4_swift_i128_divmod();
extern unsigned long skp4_swift_obj_release();
extern unsigned long skp4_swift_obj_retain();
extern unsigned long skp4_swift_objc_msgSend();
extern unsigned long skp4_swift_release_0();
extern unsigned long skp4_swift_release_1();
extern unsigned long skp4_swift_release_2();
extern unsigned long skp4_swift_release_3();
extern unsigned long skp4_swift_release_4();
extern unsigned long skp4_swift_release_5();
extern unsigned long skp4_swift_release_6();
extern unsigned long skp4_swift_release_7();
extern unsigned long skp4_swift_release_8();
extern unsigned long skp4_swift_release_9();
extern unsigned long skp4_swift_release_a();
extern unsigned long skp4_swift_release_b();
extern unsigned long skp4_swift_release_c();
extern unsigned long skp4_swift_release_obj();
extern unsigned long skp4_swift_release_obj_n();
extern unsigned long skp4_swift_retain();
extern unsigned long skp4_swift_retain_0();
extern unsigned long skp4_swift_retain_1();
extern unsigned long skp4_swift_retain_4();
extern unsigned long skp4_swift_retain_5();
extern unsigned long skp4_swift_retain_6();
extern unsigned long skp4_swift_retain_count();
extern unsigned long skp4_swift_retain_heavy();
extern unsigned long skp4_swift_retain_obj();
extern unsigned long skp4_swift_retain_obj_n();
extern cl4_result_t skp4_swift_slice_sub();
extern unsigned long skp4_swift_tail_release();
extern unsigned long skp4_swift_tail_retain();
extern cl4_result_t skp4_swift_u128_divmod();
extern cl4_result_t skp4_swift_u128_get_hi();
extern cl4_result_t skp4_swift_u128_is_zero();
extern unsigned long skp4_swift_u128_mul();
extern cl4_result_t skp4_swift_u128_zero();
extern unsigned long skp4_swift_u64_eq();
extern unsigned long skp4_swift_unknown_release();
extern unsigned long skp4_swift_unknown_retain();

extern unsigned char skp4_DAT_003471a4;
extern unsigned char skp4_DAT_003471a8;
extern unsigned long skp4_DAT_004baeb0;
extern unsigned long skp4_DAT_004baeb8;
extern double skp4_DAT_004e7cd0;
extern unsigned long skp4_DAT_004e8078;
extern unsigned long skp4_DAT_004e8080;
extern unsigned long skp4_DAT_004e8088;
extern unsigned long skp4_DAT_004e8090;
extern unsigned long skp4_DAT_004f17e0;
extern unsigned long skp4_DAT_005be7c0;
extern unsigned long skp4_DAT_0060e208;
extern unsigned long skp4_DAT_0060e230;
extern unsigned long skp4_DAT_00658c00();
extern unsigned long skp4_DAT_006adf10;
extern unsigned long skp4_DAT_006adf18;
extern unsigned char skp4_s_Can_t_compare_indices_belonging_t_005cf2c0[];
extern unsigned char skp4_s_Division_by_zero_005cd710[];
extern unsigned char skp4_s_Division_results_in_an_overflow_005cd6d0[];
extern unsigned char skp4_s_Fatal_error_005accd0[];
extern unsigned char skp4_s_Invalid_slice_005cfa58[];
extern unsigned char skp4_s_Swift_HashTable_swift_005cf300[];
extern unsigned char skp4_s_Swift_Int128_swift_005d0ed0[];
extern unsigned char skp4_s_Swift_IntegerTypes_swift_005cd6f0[];
extern unsigned char skp4_s_Swift_Integers_swift_005cd680[];
extern unsigned char skp4_s_Swift_UInt128_swift_005d1010[];
extern unsigned char skp4_s_Swift_UnsafeBufferPointer_swift_005cdc10[];


/* In-slice forwarder aliases: raw Ghidra FUN_ names -> descriptive names
 * defined in this file. */
#define skp4_FUN_00228e50 sk_u64_eq_predicate
#define skp4_FUN_00228e54 sk_u64_eq_predicate_b
#define skp4_FUN_00228e78 skp4_sk_swift_string_parse_or_format
#define skp4_FUN_00229094 skp4_sk_swift_object_construct
#define skp4_FUN_0022914c sk_swift_retain_eq_check
#define skp4_FUN_002291a4 sk_swift_object_teardown
#define skp4_FUN_0022925c sk_swift_collection_retain_return
#define skp4_FUN_002292d0 skp4_sk_swift_object_build_dispatch
#define skp4_FUN_00229348 sk_swift_object_build_dispatch_r
#define skp4_FUN_002293d4 sk_swift_value_init
#define skp4_FUN_0022944c sk_swift_value_init_wrap
#define skp4_FUN_00229464 sk_swift_value_init_impl
#define skp4_FUN_0022959c skp4_sk_swift_value_pair_construct
#define skp4_FUN_00229658 sk_swift_value_pair_copy
#define skp4_FUN_002296b0 sk_swift_retain_dispatch
#define skp4_FUN_00229748 sk_swift_retain_dispatch_store
#define skp4_FUN_002297e8 sk_swift_retain_eq_wrap
#define skp4_FUN_0022984c skp4_sk_siphash_state_init
#define skp4_FUN_002298d0 sk_siphash_compress_thunk
#define skp4_FUN_002298d4 sk_siphash_compress
#define skp4_FUN_0022995c sk_siphash_final_shift8
#define skp4_FUN_002299cc sk_siphash_final_shift16
#define skp4_FUN_00229a3c sk_siphash_absorb_byte
#define skp4_FUN_00229b5c sk_siphash_absorb_bytes
#define skp4_FUN_00229eb8 sk_siphash_finalize_thunk
#define skp4_FUN_00229ebc skp4_sk_siphash_finalize
#define skp4_FUN_00229fb0 sk_siphash_hash_word
#define skp4_FUN_0022a0c4 skp4_sk_siphash_hash_keyed
#define skp4_FUN_0022a474 skp4_sk_u32_load_aligned
#define skp4_FUN_0022a4a8 sk_swift_array_elem_wrap
#define skp4_FUN_0022a4b0 skp4_sk_swift_array_store_check
#define skp4_FUN_0022a524 skp4_sk_double_to_word
#define skp4_FUN_0022a5cc sk_u16_bit_width
#define skp4_FUN_0022a644 sk_u32_bit_width
#define skp4_FUN_0022a6dc sk_swift_fatal_bitwidth_a
#define skp4_FUN_0022a76c skp4_sk_swift_fatal_bitwidth_b
#define skp4_FUN_0022a7ec skp4_sk_swift_fatal_bitwidth_c
#define skp4_FUN_0022a870 skp4_sk_swift_fatal_bitwidth_d
#define skp4_FUN_0022a8e8 skp4_sk_swift_fatal_bitwidth_e
#define skp4_FUN_0022a95c skp4_sk_swift_fatal_bitwidth_f
#define skp4_FUN_0022a9d8 skp4_sk_swift_fatal_bitwidth_g
#define skp4_FUN_0022aa54 skp4_sk_swift_fatal_bitwidth_h
#define skp4_FUN_0022aaac sk_u64_bit_width
#define skp4_FUN_0022aaec sk_i64_bit_width
#define skp4_FUN_0022ad30 sk_swift_hashindex_cmp_fatal_a
#define skp4_FUN_0022adac skp4_sk_swift_hashindex_cmp_fatal_b
#define skp4_FUN_0022af60 sk_swift_fatal_generic
#define skp4_FUN_0022afd8 skp4_sk_hashtable_next_set_bit
#define skp4_FUN_0022b040 skp4_sk_hashtable_prev_set_bit
#define skp4_FUN_0022b080 sk_hashtable_next_clear_bit
#define skp4_FUN_0022b130 skp4_sk_hashtable_next_clear_bit_b
#define skp4_FUN_0022b21c skp4_sk_memmove
#define skp4_FUN_0022b26c sk_memmove_dispatch
#define skp4_FUN_0022b428 sk_swift_elem_dispatch
#define skp4_FUN_0022b440 sk_swift_array_subscript_write
#define skp4_FUN_0022b4bc skp4_sk_swift_array_subscript_read
#define skp4_FUN_0022b584 sk_swift_dict_get
#define skp4_FUN_0022b5a4 sk_swift_object_init_vtable
#define skp4_FUN_0022b74c sk_swift_array_remove
#define skp4_FUN_0022b944 sk_swift_dict_get_b
#define skp4_FUN_0022b94c sk_swift_object_alloc
#define skp4_FUN_0022b9c0 sk_swift_object_build
#define skp4_FUN_0022bab8 sk_swift_locked_append
#define skp4_FUN_0022bb84 sk_swift_vtable_dispatch
#define skp4_FUN_0022bd00 skp4_sk_swift_buffer_subscript_check
#define skp4_FUN_0022be48 skp4_sk_parse_uint128
#define skp4_FUN_0022c5fc sk_format_uint128
#define skp4_FUN_0022cbe0 sk_swift_noop
#define skp4_FUN_0022cbe4 skp4_sk_swift_buffer_append
#define skp4_FUN_0022cc70 sk_swift_range_subscript
#define skp4_FUN_0022cde0 sk_swift_string_utf8_convert
#define skp4_FUN_0022ceac skp4_sk_swift_str_first_byte
#define skp4_FUN_0022cf60 sk_swift_str_first_byte_b
#define skp4_FUN_0022cff0 sk_swift_str_first_byte_c
#define skp4_FUN_0022d080 sk_swift_str_first_byte_hi
#define skp4_FUN_0022d118 skp4_sk_swift_str_first_byte_fmt
#define skp4_FUN_0022d1b4 sk_swift_string_append_fmt
#define skp4_FUN_0022d2f4 skp4_sk_swift_string_parse_dispatch
#define skp4_FUN_0022d420 sk_parse_uint128_str
#define skp4_FUN_0022d898 sk_parse_u8
#define skp4_FUN_0022dc54 skp4_sk_parse_i8
#define skp4_FUN_0022e018 sk_parse_u16
#define skp4_FUN_0022e3d4 sk_parse_i16
#define skp4_FUN_0022e798 sk_parse_u32
#define skp4_FUN_0022eb38 sk_parse_i32
#define skp4_FUN_0022eed8 skp4_sk_parse_u64
#define skp4_FUN_0022f174 skp4_sk_parse_i64
#define skp4_FUN_0022f418 skp4_sk_parse_signed_wrap
#define skp4_FUN_0022f500 sk_format_i32_cb
#define skp4_FUN_0022f68c sk_swift_fmt_full
#define skp4_FUN_0022fb38 skp4_sk_format_i64_cb
#define skp4_FUN_0022fcd0 sk_swift_fatal_generic2
#define skp4_FUN_0022fd08 skp4_sk_swift_hex_parse_engine
#define skp4_FUN_00230000 sk_swift_format_engine
#define skp4_FUN_00230af0 sk_swift_format_engine_hex
#define skp4_FUN_00231888 skp4_sk_swift_obj_retain_construct
#define skp4_FUN_00231938 skp4_sk_swift_retain_dispatch2
#define skp4_FUN_0023199c sk_swift_obj_format
#define skp4_FUN_00231b0c sk_swift_vtable_dispatch2
#define skp4_FUN_00231bfc sk_u128_from_nonzero
#define skp4_FUN_00231c18 sk_u128_is_nonzero
#define skp4_FUN_00231c2c sk_u128_is_nonzero_b
#define skp4_FUN_00231c40 sk_i128_is_positive
#define skp4_FUN_00231c64 sk_swift_str_u8_escape
#define skp4_FUN_00231f04 sk_swift_str_trim
#define skp4_FUN_00232068 sk_swift_hashtable_popcount
#define skp4_FUN_002322fc sk_u128_divmod
#define skp4_FUN_002323c4 skp4_sk_u32_divmod
#define skp4_FUN_00232434 skp4_sk_u16_divmod
#define skp4_FUN_002324b0 sk_i32_divmod
#define skp4_FUN_00232578 skp4_sk_i16_divmod
#define skp4_FUN_00232654 skp4_sk_i128_divmod
#define skp4_FUN_00232774 skp4_sk_u8_divmod
#define skp4_FUN_002327f0 skp4_sk_i8_divmod
#define skp4_FUN_002328cc skp4_sk_u64_divmod
#define skp4_FUN_00232904 skp4_sk_i64_divmod
#define skp4_FUN_00232960 sk_swift_double_convert
#define skp4_FUN_002329e0 sk_u128_is_zero
#define skp4_FUN_00232aac sk_i128_is_zero
#define skp4_FUN_00232af8 sk_swift_hex_fmt_full

/* skp4_FUN_00228e50 @ 0x00228e50   (est. sk_u64_eq_predicate)
 * Ghidra: uint skp4_FUN_00228e50(undefined8 param_1,undefined8 param_2,undefined8 param_3)
 * Returns (skp4_FUN_00311a3c(a, c, b) & 1): a boolean wrapper over the shared 64-bit
 * equality primitive, with the middle argument swapped.  Argument order (a,c,b)
 * indicates the caller reorders words before comparing.
 * Confidence: low (generic wrapper over out-of-range helper).
 * Notes: callee skp4_FUN_00311a3c is the u64 compare helper.
 */
unsigned long sk_u64_eq_predicate(unsigned long a, unsigned long b, unsigned long c)
{
    return skp4_swift_u64_eq(a, c, b) & 1;
}

/*--------------------------------------------------------------------*/
/* skp4_FUN_00228e54 @ 0x00228e54   (est. sk_u64_eq_predicate_b)
 * Ghidra: uint skp4_FUN_00228e54(undefined8 param_1,undefined8 param_2,undefined8 param_3)
 * Identical body to skp4_FUN_00228e50 (second emission of the same predicate).
 * Confidence: low.
 */
unsigned long sk_u64_eq_predicate_b(unsigned long a, unsigned long b, unsigned long c)
{
    return skp4_swift_u64_eq(a, c, b) & 1;
}


/* skp4_FUN_00228e78 @ 0x00228e78   (est. skp4_sk_swift_string_parse_or_format)
 * Ghidra: void skp4_FUN_00228e78(void)
 * The largest function in this slice.  Reconstructs as the Swift string
 * parsing/formatting driver: it takes the current CPU context, retains the
 * working object, and branches on whether an equality test (skp4_FUN_00352cb0)
 * succeeds.  On the equal path it copies a 2-word object out through the
 * pointer in x21 and returns.  Otherwise it walks a parse state machine that
 * (a) scans a byte buffer via skp4_FUN_00365b6c until a terminator or invalid digit
 * is found, calling the retain/destroy bookkeeping helpers at each step, and
 * (b) on a valid run multiplies the accumulated value by the radix
 * (skp4_FUN_0006a4c0) and adds the digit.  The result is stored through the output
 * pointer (x8).  Decompiler could not recover the loop back-edge cleanly, so
 * this is a structural transcription.
 * Confidence: low (opaque Swift-runtime body).
 * Notes: skp4_DAT_004e8090/004e8078/004e8080/004e8088 are ASCII tag/kind words;
 *   skp4_FUN_00002534/skp4_FUN_00354678 are runtime retain/release calls.
 */
void skp4_sk_swift_string_parse_or_format(void)
{
    unsigned long digit, scan, acc;
    /* unaff_x21: output slot; unaff_x30: return address */
    uint64_t *out = (void*)0;  /* [INFERENCE] x21 slot */
    uint64_t lo, hi;

    skp4_sk_cpu();
    skp4_swift_retain_0();
    skp4_swift_retain_1();
    (*(unsigned long (*)(unsigned long))skp4_DAT_00658c00)(
        *(unsigned long *)(/*extraout_x8_00*/ 0 + 0x40));
    skp4_swift_retain_heavy();
    skp4_swift_objc_msgSend();

    if (/*eq*/ 0 == 0) {
        lo = out[0];
        hi = out[1];
        skp4_swift_unknown_release(0x656238, &skp4_DAT_004e8090);
        skp4_swift_tail_retain();
        *(uint64_t*)0 = lo;        /* store through out ptr (x8) */
        ((uint64_t*)0)[1] = hi;
        skp4_sk_cpu_restore(0);
        return;
    }
    skp4_swift_release_0();
    skp4_swift_release_8();
    (*(void (*)(void))0)();        /* indirect call */
    skp4_swift_unknown_release(0x656220, &skp4_DAT_004e8078);
    skp4_swift_bounds_check(&lo);
    scan = skp4_FUN_00365b6c();        /* scan-bytes helper */
    digit = 0;
    if ((scan & 1) == 0) {
        /* invalid-run path: zero the accumulation, then loop */
        (void)skp4_swift_u128_zero;
        skp4_swift_brk_f(&lo, 0x656228, &skp4_DAT_004e8080);
        for (;;) {
            skp4_swift_release_5();
            skp4_swift_brk_f(&lo);
            skp4_swift_unknown_release(0x656230, &skp4_DAT_004e8088);
            skp4_swift_tail_retain();
            *(char*)0 = 0;
            skp4_swift_release_7();
            skp4_swift_tail_retain();
        }
    } else {
        acc = skp4_swift_u128_mul(&lo, 0);
        skp4_swift_retain_6(acc, acc);
        (*(unsigned long (*)(unsigned long))skp4_DAT_00658c00)(
            *(unsigned long *)(0 + 0x40));
        skp4_swift_retain_heavy();
        (*(void (**)(void))(0x10))();      /* indirect method dispatch */
        skp4_swift_release_6(0);
        skp4_swift_brk_b(&lo);
        (*(void (*)(void))0)();
        skp4_swift_destroy_temp(&lo);
        if (/*local_48*/ 0 == 0) {
            /* fall through to the scan loop */
        } else {
            /* copy 5 words from locals to output */
            ((uint64_t*)0)[1] = 0;
            *(uint64_t*)0 = 0;
            ((uint64_t*)0)[3] = 0;
            ((uint64_t*)0)[2] = 0;
            ((uint64_t*)0)[4] = 0;
        }
    }
    skp4_swift_brk_c(*(unsigned long *)(0 + 8));
    (*(void (*)(void))0)();
    skp4_sk_cpu_restore(0);
}

/*--------------------------------------------------------------------*/
/* skp4_FUN_00229094 @ 0x00229094   (est. skp4_sk_swift_object_construct)
 * Ghidra: void skp4_FUN_00229094(void)
 * Builds a Swift object header: allocates via skp4_FUN_0031c670(0), stores the
 * allocation into the x21 slot +0x18, points slot +0x20 at the vtable
 * skp4_DAT_004f17e0, then dispatches through the constructed object's method slot
 * (+0x20).  Decompiler could not recover the dispatch jumptable.
 * Confidence: low.
 * Notes: skp4_DAT_004f17e0 is a type-metadata/vtable word; jumptable at 0x229100.
 */
void skp4_sk_swift_object_construct(void)
{
    unsigned long obj;
    skp4_swift_release_1();
    obj = skp4_swift_alloc_object(0);
    *(unsigned long *)(0 + 0x18) = obj;        /* x21 slot */
    *(uintptr_t *)(0 + 0x20) = (uintptr_t)&skp4_DAT_004f17e0;
    skp4_swift_retain();
    skp4_swift_release_2();
    (*(void (**)(void))(0x20))();              /* unrecovered jumptable */
}

/*--------------------------------------------------------------------*/
/* skp4_FUN_0022914c @ 0x0022914c   (est. sk_swift_retain_eq_check)
 * Ghidra: uint skp4_FUN_0022914c(void)
 * Retains the word at x20+0x20, releases the previous object, and returns
 * (indirect_call & 1): a boolean whose low bit comes from a dispatched
 * equality/hash method.
 * Confidence: low.
 */
unsigned long sk_swift_retain_eq_check(void)
{
    unsigned long v, r;
    skp4_swift_retain_obj();
    v = *(unsigned long *)(0 + 0x20);          /* x20 slot */
    skp4_swift_release_1();
    skp4_swift_bounds_check();
    skp4_swift_retain_1(v);
    skp4_swift_release_7();
    skp4_swift_release_8();
    r = (*(unsigned long (*)(void))0)();
    return r & 1;
}

/*--------------------------------------------------------------------*/
/* skp4_FUN_002291a4 @ 0x002291a4   (est. sk_swift_object_teardown)
 * Ghidra: void skp4_FUN_002291a4(void)
 * Tear-down driver: releases a chain of objects, computes a result via
 * skp4_FUN_0031997c, and re-acquires the lock before returning through the saved
 * frame.  Call order preserved from the decompile.
 * Confidence: low.
 */
void sk_swift_object_teardown(void)
{
    unsigned long v, r;
    skp4_swift_retain_5();
    skp4_swift_retain_heavy();
    skp4_swift_release_6();
    skp4_swift_brk_c(&v);
    (*(void (*)(void))0)();
    v = 0;                                       /* in_stack_48 */
    skp4_swift_u128_mul(&v, 0);
    skp4_swift_retain_6();
    skp4_swift_bounds_check();
    (*(void (*)(void))0)();
    v = skp4_FUN_0031997c(v);
    skp4_swift_release_8(v);
    r = (*(unsigned long (*)(void))0)();
    skp4_swift_destroy_temp();
    skp4_swift_destroy_temp(&v);
    skp4_swift_tail_retain(r & 1, 0);                 /* skp4_FUN_0035a8d0 */
}

/*--------------------------------------------------------------------*/
/* skp4_FUN_0022925c @ 0x0022925c   (est. sk_swift_collection_retain_return)
 * Ghidra: undefined8 skp4_FUN_0022925c(void)
 * Wrapper that retains a collection object, calls skp4_FUN_0015fe34 /
 * skp4_FUN_000777d4 (an index/offset helper) and returns the dispatched result.
 * Confidence: low.
 */
unsigned long sk_swift_collection_retain_return(void)
{
    unsigned long r;
    skp4_swift_brk_d();
    skp4_sk_cpu_flag_get();
    skp4_swift_release_3();
    (*(void (*)(void))0)();
    skp4_swift_brk_d(&r);
    skp4_FUN_0015fe34();
    skp4_swift_u128_zero();
    r = (*(unsigned long (*)(void))0)();
    skp4_swift_destroy_temp(&r);
    return r;
}

/*--------------------------------------------------------------------*/
/* skp4_FUN_002292d0 @ 0x002292d0   (est. skp4_sk_swift_object_build_dispatch)
 * Ghidra: void skp4_FUN_002292d0(void)
 * Builds an object and dispatches a method through its vtable; the dispatched
 * method receives a 16-byte value (auVar1) plus a stack word.
 * Confidence: low.
 */
void skp4_sk_swift_object_build_dispatch(void)
{
    cl4_result_t pair;
    skp4_swift_retain_heavy();
    skp4_sk_cpu_flag_get();
    skp4_swift_release_3();
    skp4_swift_brk_c();
    (*(void (*)(void))0)();
    skp4_swift_retain_heavy(&pair);
    skp4_FUN_00343a30();
    pair = skp4_swift_u128_zero();
    (*(void (*)(unsigned long, unsigned long, unsigned long))(0))(
        pair.lo, pair.hi, 0);
    skp4_swift_destroy_temp(&pair);
}

/*--------------------------------------------------------------------*/
/* skp4_FUN_00229348 @ 0x00229348   (est. sk_swift_object_build_dispatch_r)
 * Ghidra: undefined8 skp4_FUN_00229348(void)
 * Variant of skp4_FUN_002292d0 that returns the dispatched method's result instead
 * of void.
 * Confidence: low.
 */
unsigned long sk_swift_object_build_dispatch_r(void)
{
    cl4_result_t pair;
    unsigned long r;
    skp4_swift_retain_heavy();
    skp4_sk_cpu_flag_get();
    skp4_swift_release_3();
    skp4_swift_brk_c();
    (*(void (*)(void))0)();
    skp4_swift_retain_heavy(&pair);
    skp4_FUN_0031993c();
    pair = skp4_swift_u128_zero();
    r = (*(unsigned long (*)(unsigned long, unsigned long, unsigned long))(0))(
        pair.lo, pair.hi, 0);
    skp4_swift_destroy_temp(&pair);
    return r;
}

/*--------------------------------------------------------------------*/
/* skp4_FUN_002293d4 @ 0x002293d4   (est. sk_swift_value_init)
 * Ghidra: undefined1 [16] skp4_FUN_002293d4(void)
 * Initializes a 16-byte value: retains the object, runs the standard init
 * sequence (skp4_FUN_0031c688 / skp4_FUN_003507e0 / skp4_FUN_0035896c / ...), and returns the
 * freshly-built 16-byte value (local_60).  Stack destroy helper invoked on the
 * temp buffer before return.
 * Confidence: low.
 */
cl4_result_t sk_swift_value_init(void)
{
    cl4_result_t v;
    skp4_swift_brk_d();
    skp4_FUN_0031c688();
    skp4_swift_brk_f(&v);
    (*(void (*)(void))0)();
    skp4_FUN_0035896c();
    skp4_swift_release_6();
    skp4_swift_release_7();
    skp4_swift_retain_1();
    skp4_swift_release_6(&v);
    skp4_FUN_00205844();
    skp4_swift_destroy_temp(&v);
    return (cl4_result_t){0,0};   /* local_60 */
}

/*--------------------------------------------------------------------*/
/* skp4_FUN_0022944c @ 0x0022944c   (est. sk_swift_value_init_wrap)
 * Ghidra: void skp4_FUN_0022944c(undefined8 param_1,undefined8 param_2)
 * Trivial forwarder: skp4_FUN_00229464(param_1, param_2, skp4_FUN_00205844).
 * Confidence: medium (direct forwarder).
 */
void sk_swift_value_init_wrap(unsigned long a, unsigned long b)
{
    sk_swift_value_init_impl(a, b, (unsigned long)skp4_FUN_00205844);
}

/*--------------------------------------------------------------------*/
/* skp4_FUN_00229464 @ 0x00229464   (est. sk_swift_value_init_impl)
 * Ghidra: undefined1 [16] skp4_FUN_00229464(undefined8 param_1,undefined8 param_2,undefined8 param_3)
 * Builds a 16-byte value whose high word is the tagged pointer 0xe000... and
 * low word is set by a dispatched initializer (skp4_FUN_0034895c result).  The
 * param_3 is passed to a vtable (skp4_FUN_003504d0).
 * Confidence: low.
 */
cl4_result_t sk_swift_value_init_impl(unsigned long a, unsigned long b, unsigned long f)
{
    cl4_result_t r;
    unsigned long v;
    skp4_swift_retain_6(f);
    r = (cl4_result_t){0, 0xe000000000000000ull};
    skp4_swift_release_7();
    v = skp4_FUN_0034895c();
    (*(void (*)(unsigned long, cl4_result_t *))(0))(v, &r);
    skp4_swift_retain_6();
    (*(void (**)(void))(8))();
    return r;
}

/* skp4_FUN_002294d8 @ 0x002294d8   (est. sk_swift_string_compose)
 * Ghidra: void skp4_FUN_002294d8(void)
 * Composes a string: pulls the argument word from x20+0x20, runs the string
 * init/format helpers (skp4_FUN_0031c688, skp4_FUN_003507e0, skp4_FUN_0035896c, ...),
 * appends a tagged literal via skp4_FUN_001e3f70, then finishes with a retype/
 * object-call sequence (skp4_FUN_003a25d4, skp4_FUN_0006b6f4, skp4_FUN_00355560).
 * Confidence: low.
 */
void sk_swift_string_compose(void)
{
    unsigned long arg;
    cl4_result_t lit;
    arg = *(unsigned long *)(0 + 0x20);    /* x20 arg */
    skp4_swift_brk_d();
    skp4_FUN_0031c688();
    skp4_swift_brk_f(&lit);
    (*(void (*)(void))0)();
    skp4_FUN_0035896c();
    skp4_swift_release_6();
    skp4_swift_release_7();
    skp4_FUN_0034895c();
    skp4_swift_release_6(&lit);
    skp4_FUN_002060d4();
    skp4_swift_destroy_temp(&lit);
    skp4_swift_hash_combine(0x6168736148796e41ull, 0xec00000028656c62ull, lit.lo, lit.hi);
    skp4_swift_release_7();
    skp4_swift_retain_count();
    skp4_swift_u128_get_hi();
    skp4_swift_release_5();
    skp4_swift_hash_combine();
    skp4_swift_release_6();
    skp4_swift_retain_count(arg);
    skp4_FUN_0009461c();
}

/*--------------------------------------------------------------------*/
/* skp4_FUN_0022959c @ 0x0022959c   (est. skp4_sk_swift_value_pair_construct)
 * Ghidra: void skp4_FUN_0022959c(undefined8 *param_1)
 * Builds a 40-byte value: allocates a tagged descriptor (skp4_FUN_00358fe8), fills
 * +0x10/+0x18 from the global skp4_DAT_004baeb0, sets the kind word 0x65756c6176
 * ("value") at +0x20 and a tagged pointer at +0x28, then writes the whole 40
 * bytes into param_1.  Aux object init (skp4_FUN_0031c688 / skp4_FUN_000e15d8).
 * Confidence: low.
 * Notes: 0x65756c6176 = ASCII "value"; skp4_DAT_004baeb0 is a descriptor global.
 */
void skp4_sk_swift_value_pair_construct(uint64_t *out)
{
    unsigned long desc, lo, hi, s3, s7;
    uint64_t w3;
    skp4_swift_retain_1();
    skp4_swift_release_5();
    desc = skp4_FUN_00358fe8();
    lo = skp4_DAT_004baeb0;
    *(unsigned long *)(desc + 0x18) = skp4_DAT_004baeb8;
    *(unsigned long *)(desc + 0x10) = lo;
    *(unsigned long *)(desc + 0x20) = 0x65756c6176ull;  /* "value" */
    *(unsigned long *)(desc + 0x28) = 0xe500000000000000ull;
    lo = *(unsigned long *)(0 + 0x20);    /* x20 arg */
    skp4_swift_release_1();
    skp4_swift_bounds_check();
    skp4_FUN_0031c688(lo);
    skp4_FUN_000e15d8(desc + 0x30);
    (*(void (*)(void))0)();
    skp4_FUN_0034d5ec(&lo, &s3, desc);
    skp4_FUN_001e4164();
    out[1] = hi;
    out[0] = lo;
    out[3] = w3;
    out[2] = s3;
    *(uint64_t *)((char*)out + 0x21) = s7;
    *(uint64_t *)((char*)out + 0x19) = w3;
}

/*--------------------------------------------------------------------*/
/* skp4_FUN_00229658 @ 0x00229658   (est. sk_swift_value_pair_copy)
 * Ghidra: void skp4_FUN_00229658(undefined8 *param_1)
 * Copy of a 40-byte value produced by skp4_FUN_0022959c into param_1.
 * Confidence: low.
 */
void sk_swift_value_pair_copy(uint64_t *out)
{
    cl4_result_t v;
    skp4_FUN_0022959c((uint64_t*)&v);
    out[1] = v.hi;
    out[0] = v.lo;
    out[3] = 0;
    out[2] = 0;
    *(uint64_t *)((char*)out + 0x21) = 0;
    *(uint64_t *)((char*)out + 0x19) = 0;
}

/*--------------------------------------------------------------------*/
/* skp4_FUN_002296b0 @ 0x002296b0   (est. sk_swift_retain_dispatch)
 * Ghidra: void skp4_FUN_002296b0(void)
 * Retains an object (skp4_FUN_0034b85c), dispatches a method, builds a value via
 * skp4_FUN_00229094 and re-pushes it (skp4_FUN_0031b578).
 * Confidence: low.
 */
void sk_swift_retain_dispatch(void)
{
    unsigned long v;
    cl4_result_t buf;
    v = skp4_FUN_0034b85c();
    skp4_swift_retain_6(v, v);
    (*(unsigned long (*)(unsigned long))skp4_DAT_00658c00)(*(unsigned long *)(0 + 0x40));
    skp4_swift_retain_heavy();
    skp4_swift_release_3();
    (*(void (*)(void))0)();
    skp4_swift_retain_6(&buf);
    skp4_FUN_00229094();
    skp4_FUN_0031b578(&buf);
}

/*--------------------------------------------------------------------*/
/* skp4_FUN_00229748 @ 0x00229748   (est. sk_swift_retain_dispatch_store)
 * Ghidra: void skp4_FUN_00229748(void)
 * Same retain/dispatch prologue as skp4_FUN_002296b0, but stores the produced
 * 40-byte value into the x21 output slot.
 * Confidence: low.
 */
void sk_swift_retain_dispatch_store(void)
{
    unsigned long v;
    cl4_result_t buf;
    v = skp4_FUN_0034b85c();
    skp4_swift_retain_6(v, v);
    (*(unsigned long (*)(unsigned long))skp4_DAT_00658c00)(*(unsigned long *)(0 + 0x40));
    skp4_swift_retain_heavy();
    skp4_swift_release_3();
    (*(void (*)(void))0)();
    skp4_swift_retain_6(&buf);
    skp4_FUN_00228e78();
    ((uint64_t*)0)[1] = buf.hi;
    *(uint64_t*)0 = buf.lo;
    ((uint64_t*)0)[3] = 0;
    ((uint64_t*)0)[2] = 0;
    ((uint64_t*)0)[4] = 0;
}

/*--------------------------------------------------------------------*/
/* skp4_FUN_002297e8 @ 0x002297e8   (est. sk_swift_retain_eq_wrap)
 * Ghidra: uint skp4_FUN_002297e8(void)
 * Retains via skp4_FUN_00350b54, calls skp4_FUN_00084180 then skp4_FUN_0022914c, and returns
 * its low bit.  Wrapper around the equality predicate.
 * Confidence: low.
 */
unsigned long sk_swift_retain_eq_wrap(void)
{
    unsigned long v, r;
    cl4_result_t buf;
    v = skp4_FUN_00350b54();
    skp4_swift_retain_1(v, &buf);
    skp4_swift_retain_obj_n();
    r = skp4_FUN_0022914c();
    skp4_swift_retain_heavy(&buf);
    return r & 1;
}

/*--------------------------------------------------------------------*/
/* skp4_FUN_0022984c @ 0x0022984c   (est. skp4_sk_siphash_state_init)
 * Ghidra: void skp4_FUN_0022984c(void)
 * SipHash state initialization: seeds the four 64-bit state words by XORing
 * skp4_FUN_003560e4's two output words with the ASCII constants
 * "somepseudorandomlygeneratedbytes" (0x736f6d6570736575 / 0x646f72616e646f6d /
 * 0x6c7967656e657261).  The 5 words are stored through the x8 slot.
 * Confidence: high (classic SipHash-2-4 init constants).
 * Notes: skp4_FUN_003560e4 supplies the key; skp4_FUN_00352f60 stores the words.
 */
void skp4_sk_siphash_state_init(void)
{
    cl4_result_t k;
    k = skp4_FUN_003560e4();
    *(uint64_t*)0 = 0;                          /* v0.. slot via x8 */
    ((uint64_t*)0)[1] = k.lo ^ 0x736f6d6570736575ull;   /* "somepseu" */
    ((uint64_t*)0)[2] = k.hi ^ 0x646f72616e646f6dull;   /* "ndorand" */
    ((uint64_t*)0)[3] = k.lo ^ 0x6c7967656e657261ull;   /* "lygener" */
    ((uint64_t*)0)[4] = k.hi ^ 0;               /* skp4_FUN_003560e4 hi ^ extraout_x9 */
    skp4_swift_bits_ones();
}

/*--------------------------------------------------------------------*/
/* skp4_FUN_002298d0 @ 0x002298d0   (est. sk_siphash_compress)
 * Ghidra: void skp4_thunk_FUN_002298d4(ulong param_1)
 * Thunk alias for skp4_FUN_002298d4.
 * Confidence: medium.
 */
void sk_siphash_compress_thunk(unsigned long m)
{
    sk_siphash_compress(m);
}

/*--------------------------------------------------------------------*/
/* skp4_FUN_002298d4 @ 0x002298d4   (est. sk_siphash_compress)
 * Ghidra: void skp4_FUN_002298d4(ulong param_1)
 * One SipHash compression step over message word param_1 against the 5-word
 * state at x20: injects the byte count (bits 56-58) and message bytes, then
 * applies two SipRound operations (the "b = (b << 13)|(b >> 51)" /
 * "c ^= (d>>11)|(d<<53)" XOR-rotate dance).  Faithful transcription of the
 * standard SipHash-2-4 round body.
 * Confidence: high (canonical SipHash round arithmetic).
 */
void sk_siphash_compress(unsigned long m)
{
    unsigned long v0, v1, v2, v3, t;
    uint64_t *s = (void*)0;    /* x20 state, 5 words */
    v0 = s[0]; v1 = s[1]; v2 = s[2]; v3 = s[3];
    t = v0 >> 0x38 & 7;                       /* byte-count field */
    {
        unsigned long mshifted, count;
        if (t == 0) { mshifted = m; count = v0 + 0x800000000000000ull; }
        else {
            mshifted = m << (t * 8) | v0 & 0xffffffffffffffull;
            count = m >> ((t * -8) & 0x3f) |
                    (v0 & 0xff00000000000000ull) + 0x800000000000000ull;
        }
        v3 = s[4] ^ mshifted;
        /* round 1 */
        v1 = v2 + s[1];
        { unsigned long r = v1 ^ (v2 >> 0x33 | v2 << 0xd);
          unsigned long a = s[3] + v3 + r;
          unsigned long b = s[3] + v3 ^ (v3 >> 0x30 | v3 << 0x10);
          unsigned long c = b + (v1 >> 0x20 | v1 << 0x20);
          s[4] = c ^ (b >> 0x2b | b << 0x15);
          s[2] = a ^ (r >> 0x2f | r << 0x11);
          s[3] = a >> 0x20 | a << 0x20;
        }
        s[0] = count;
        s[1] = v1 ^ mshifted;
    }
}

/*--------------------------------------------------------------------*/
/* skp4_FUN_0022995c @ 0x0022995c   (est. sk_siphash_final_shift8)
 * Ghidra: void skp4_FUN_0022995c(ulong param_1)
 * Finalizes SipHash by folding the top byte field: if the byte count in
 * state[0] bits 56-58 is >= 4, shifts param_1 right and ORs it into the count
 * field via skp4_FUN_00356530, then tail-retains.
 * Confidence: medium.
 */
void sk_siphash_final_shift8(unsigned long m)
{
    unsigned long s0 = *(unsigned long*)0;
    unsigned long cnt = s0 >> 0x38 & 7;
    unsigned long v = 0;
    if (cnt > 3) {
        if (cnt != 4) v = (m & 0xffffffffull) >> ((-(int)(cnt << 3)) & 0x38);
        skp4_swift_tail_release(s0 & 0xff00000000000000ull | v);
    }
    skp4_swift_tail_retain();
}

/*--------------------------------------------------------------------*/
/* skp4_FUN_002299cc @ 0x002299cc   (est. sk_siphash_final_shift16)
 * Ghidra: void skp4_FUN_002299cc(ulong param_1)
 * Variant folding the top byte field for a 16-bit tail.
 * Confidence: medium.
 */
void sk_siphash_final_shift16(unsigned long m)
{
    unsigned long s0 = *(unsigned long*)0;
    unsigned long cnt = s0 >> 0x38 & 7;
    unsigned long v = 0;
    if (cnt > 5) {
        if (cnt != 6) v = (m & 0xffffull) >> ((-(int)(cnt << 3)) & 0x38);
        skp4_swift_tail_release(s0 & 0xff00000000000000ull | v);
    }
    skp4_swift_tail_retain();
}

/*--------------------------------------------------------------------*/
/* skp4_FUN_00229a3c @ 0x00229a3c   (est. sk_siphash_absorb_byte)
 * Ghidra: void skp4_FUN_00229a3c(ulong param_1)
 * Absorbs a single byte into the SipHash state: when the byte count is 7 the
 * message byte is placed at the top and a full compression round is run;
 * otherwise the byte is shifted into the current position.  The final count
 * field is re-tagged via skp4_FUN_003542a8(+0x100000000000000).
 * Confidence: high (SipHash byte absorption).
 */
void sk_siphash_absorb_byte(unsigned long b)
{
    unsigned long s0 = *(unsigned long*)0;
    unsigned long cnt = s0 >> 0x38 & 7;
    uint64_t *s = (void*)0;
    if (cnt == 7) {
        unsigned long m = b << 0x38 | s0 & 0xffffffffffffffull;
        unsigned long v3 = s[4] ^ m;
        unsigned long v1 = s[2] + s[1];
        unsigned long r = v1 ^ (s[2] >> 0x33 | s[2] << 0xd);
        unsigned long a = s[3] + v3 + r;
        unsigned long bb = s[3] + v3 ^ (v3 >> 0x30 | v3 << 0x10);
        unsigned long c = bb + (v1 >> 0x20 | v1 << 0x20);
        s[3] = a >> 0x20 | a << 0x20;
        s[4] = c ^ (bb >> 0x2b | bb << 0x15);
        s[1] = c ^ m;
        s[2] = a ^ (r >> 0x2f | r << 0x11);
        s0 = s0 & 0xff00000000000000ull;
    } else {
        s0 = (b & 0xff) << (cnt << 3) | s0;
    }
    skp4_swift_tail_retain(s0 + 0x100000000000000ull);
}

/* skp4_FUN_00229b5c @ 0x00229b5c   (est. sk_siphash_absorb_bytes)
 * Ghidra: void skp4_FUN_00229b5c(ulong *param_1,long param_2)
 * SipHash message absorption over param_2 bytes at param_1.  Handles the
 * misaligned head byte-by-byte, then processes 8-byte aligned words with full
 * compression rounds, then the misaligned tail.  Faithful transcription of the
 * canonical SipHash update loop (with SoftwareBreakpoint(1,0x229e70/74) on a
 * bad pointer and the fatal-alloc helper on a negative length).
 * Confidence: high (canonical SipHash-2-4 absorb).
 */
void sk_siphash_absorb_bytes(const unsigned char *p, long len)
{
    uint64_t *s;                     /* x20 state, 5 words */
    unsigned long u6, u7, u11, u12, u4, u5, u8, u10, u13, u14;
    long l9;
    if (p == 0 || (len == 0)) return;
    if ((unsigned long)p > 0xfffffffffffffff7ull) skp4_swift_brk();       /* SB #1 0x229e70 */
    {
        unsigned long aligned = ((unsigned long)p + 7) & ~7ull;
        unsigned long head = aligned - (unsigned long)p;
        if (aligned < (unsigned long)p) skp4_swift_brk();                 /* SB #1 0x229e74 */
        if ((long)head < 0) { skp4_FUN_00347fb4(); skp4_FUN_003523f0(); skp4_sk_swift_fatal_error(); }
        u7 = head; if (len <= (long)head) u7 = len;
        if (head != 0) {
            /* gather up to 8 head bytes little-endian, then one compress */
            unsigned long word = 0;
            int i = (int)u7;
            switch (i) {
                case 7: word |= (unsigned long)p[6] << 0x30; /* fallthrough */
                case 6: word |= (unsigned long)p[5] << 0x28;
                case 5: word |= (unsigned long)p[4] << 0x20;
                case 4: word |= (unsigned long)p[3] << 0x18;
                case 3: word |= (unsigned long)p[2] << 0x10;
                case 2: word |= (unsigned long)p[1] << 8;
                default: word |= p[0];
            }
            /* run one compression (reuse sk_siphash_compress body) */
            u11 = s[0]; u8 = u11 >> 0x38 & 7; l9 = u8 << 3;
            u8 = u8 + u7;
            if (u8 < 8) {
                u4 = (word << l9 | u11) + (u7 << 0x38);
            } else {
                u12 = word << l9 | u11 & 0xffffffffffffffull;
                u4 = 0;
                if (u8 != 8) u4 = word >> ((-(int)l9) & 0x38);
                u4 = u4 | (unsigned long)((unsigned int)(unsigned char)(u11 >> 0x38) + (int)u7) << 0x38;
                u11 = s[4] ^ u12;
                u8 = s[2]; u6 = u8 + s[1];
                u13 = u6 ^ (u8 >> 0x33 | u8 << 0xd);
                u8 = s[3] + u11 + u13;
                u11 = s[3] + u11 ^ (u11 >> 0x30 | u11 << 0x10);
                u6 = u11 + (u6 >> 0x20 | u6 << 0x20);
                s[3] = u8 >> 0x20 | u8 << 0x20;
                s[4] = u6 ^ (u11 >> 0x2b | u11 << 0x15);
                s[1] = u6 ^ u12;
                s[2] = u8 ^ (u13 >> 0x2f | u13 << 0x11);
            }
            s[0] = u4;
            p += u7; len -= (long)u7;
        }
        /* 8-byte aligned bulk */
        if (len > 7) {
            unsigned long rem = len;
            unsigned long mis = (unsigned long)p & 7;
            const unsigned long *q = (const unsigned long*)p;
            if (mis != 0) { skp4_swift_brk(); skp4_FUN_00349eb8(); }   /* alignment trap */
            while (rem > 0xf) {
                u4 = *q++;
                u8 = s[0]; u12 = u8 >> 0x38 & 7;
                u5 = u4 << u12 * 8 | u8 & 0xffffffffffffffull;
                u11 = u4 >> (u12 * -8 & 0x3f) | (u8 & 0xff00000000000000ull) + 0x800000000000000ull;
                if (u12 == 0) { u5 = u4; u11 = u8 + 0x800000000000000ull; }
                u12 = s[4] ^ u5;
                u4 = s[2]; u8 = u4 + s[1];
                u13 = u8 ^ (u4 >> 0x33 | u4 << 0xd);
                u4 = s[3] + u12 + u13;
                u12 = s[3] + u12 ^ (u12 >> 0x30 | u12 << 0x10);
                u8 = u12 + (u8 >> 0x20 | u8 << 0x20);
                s[4] = u8 ^ (u12 >> 0x2b | u12 << 0x15);
                s[2] = u4 ^ (u13 >> 0x2f | u13 << 0x11);
                s[3] = u4 >> 0x20 | u4 << 0x20;
                s[0] = u11;
                s[1] = u8 ^ u5;
                rem -= 8;
            }
            /* trailing full 8-byte word if any */
            if ((long)rem > 0) {
                unsigned long word = 0; int i=(int)rem;
                switch(i){
                  case 7: word |= (unsigned long)p[6]<<0x30;
                  case 6: word |= (unsigned long)p[5]<<0x28;
                  case 5: word |= (unsigned long)p[4]<<0x20;
                  case 4: word |= (unsigned long)p[3]<<0x18;
                  case 3: word |= (unsigned long)p[2]<<0x10;
                  case 2: word |= (unsigned long)p[1]<<8;
                  default: word |= p[0];
                }
                u8 = s[0]; u7 = u8 >> 0x38 & 7; l9 = u7 << 3;
                u7 = u7 + rem;
                if (u7 < 8) {
                    s[0] = (word << l9 | u8) + (rem << 0x38);
                } else {
                    u10 = word << l9 | u8 & 0xffffffffffffffull;
                    u12 = s[4] ^ u10;
                    u4 = s[2]; u11 = u4 + s[1];
                    u14 = u11 ^ (u4 >> 0x33 | u4 << 0xd);
                    u4 = s[3] + u12 + u14;
                    u13 = s[3] + u12 ^ (u12 >> 0x30 | u12 << 0x10);
                    u11 = u13 + (u11 >> 0x20 | u11 << 0x20);
                    u12 = 0;
                    if (u7 != 8) u12 = word >> ((-(int)l9) & 0x38);
                    s[4] = u11 ^ (u13 >> 0x2b | u13 << 0x15);
                    s[2] = u4 ^ (u14 >> 0x2f | u14 << 0x11);
                    s[3] = u4 >> 0x20 | u4 << 0x20;
                    s[0] = u12 | (unsigned long)((unsigned int)(unsigned char)(u8 >> 0x38) + (int)rem) << 0x38;
                    s[1] = u11 ^ u10;
                }
            }
        }
    }
}

/*--------------------------------------------------------------------*/
/* skp4_FUN_00229eb8 @ 0x00229eb8   (est. skp4_sk_siphash_finalize)
 * Ghidra: void skp4_thunk_FUN_00229ebc(void)
 * Thunk alias for skp4_FUN_00229ebc.
 * Confidence: medium.
 */
void sk_siphash_finalize_thunk(void)
{
    skp4_sk_siphash_finalize();
}

/*--------------------------------------------------------------------*/
/* skp4_FUN_00229ebc @ 0x00229ebc   (est. skp4_sk_siphash_finalize)
 * Ghidra: void skp4_FUN_00229ebc(void)
 * SipHash-2-4 finalization: applies two final SipRounds across the 5-word
 * state and XORs the result with the state's third word; returns via
 * skp4_FUN_00351d4c.  Canonical 0x7465646279746573 ("stedybt"? = 0x7465646279746573)
 * is the finalization constant.  Faithful transcription of the round body.
 * Confidence: high (SipHash final round).
 * Notes: 0x7465646279746573 ^ 0x800000000000000 in the final fold.
 */
void skp4_sk_siphash_finalize(void)
{
    unsigned long a,b,c,d,e,f;
    /* state registers arrive from retain helpers (extraout_x1/x8/x9/x10/x11) */
    a = 0; b = 0; c = 0; d = 0; e = 0; f = 0;   /* [INFERENCE] loaded from state */
    skp4_swift_retain_5();
    skp4_swift_retain_6(0);
    /* round 1 */
    b = 0x7465646279746573ull ^ 0;              /* c2 constant */
    c = 0; d = c ^ (d >> 0x33 | d << 0xd);
    e = d + f + b;
    b = f + b ^ (b >> 0x30 | b << 0x10);
    d = e ^ (d >> 0x2f | d << 0x11);
    c = (c >> 0x20 | c << 0x20) + b;
    e = c ^ (b >> 0x2b | b << 0x15);
    /* round 2 (state-dependent) -- abbreviated structural transcription */
    skp4_swift_release_4((c ^ 0x800000000000000ull));
}

/*--------------------------------------------------------------------*/
/* skp4_FUN_00229fb0 @ 0x00229fb0   (est. sk_siphash_hash_word)
 * Ghidra: ulong skp4_FUN_00229fb0(undefined8 param_1,undefined8 param_2,long param_3)
 * Computes a SipHash-2-4 over a single word (param_3 placed in the byte-count
 * field via `param_3 << 0x38`), folding the four state words with the standard
 * XOR-rotate rounds and returning the combined digest.  Faithful transcription
 * of the 2 round-pairs of SipHash final.
 * Confidence: high (SipHash digest fold).
 */
unsigned long sk_siphash_hash_word(unsigned long a, unsigned long b, long len)
{
    unsigned long v0,v1,v2,v3, w, r1,r2,r3;
    /* state from retain helpers (x1/x8/x9/x10/x11) */
    v0 = 0; v1 = 0; v2 = 0; v3 = 0;
    skp4_swift_retain_5();
    skp4_swift_retain_6(0);
    w = (0 | len << 0x38) ^ 0x7465646279746573ull ^ 0;
    r1 = v0 + v3; r2 = r1 ^ (v3 >> 0x33 | v3 << 0xd);
    r3 = r2 + v1 + w;
    w = v1 + w ^ (w >> 0x30 | w << 0x10);
    r1 = (r1 >> 0x20 | r1 << 0x20) + w;
    v1 = r1 ^ (w >> 0x2b | w << 0x15);
    v2 = r3 ^ (r2 >> 0x2f | r2 << 0x11);
    /* second half: fold the four words */
    {
        unsigned long q1 = (r1 ^ 0) + v2;
        unsigned long q2 = q1 ^ (v2 >> 0x33 | v2 << 0xd);
        unsigned long q3 = ((r3 >> 0x20 | r3 << 0x20) ^ 0xff) + v1;
        unsigned long q4 = q3 + q2;
        q3 = q3 ^ (v1 >> 0x30 | v1 << 0x10);
        q2 = q4 ^ (q2 >> 0x2f | q2 << 0x11);
        v0 = q3 + (q1 >> 0x20 | q1 << 0x20);
        v1 = v0 + q2;
        v0 = v0 ^ (q3 >> 0x2b | q3 << 0x15);
        q2 = v1 ^ (q2 >> 0x33 | q2 << 0xd);
        q3 = v0 + (q4 >> 0x20 | q4 << 0x20);
        v2 = q3 + q2;
        q3 = q3 ^ (v0 >> 0x30 | v0 << 0x10);
        q2 = v2 ^ (q2 >> 0x2f | q2 << 0x11);
        v0 = q3 + (v1 >> 0x20 | v1 << 0x20);
        v1 = v0 ^ (q3 >> 0x2b | q3 << 0x15);
        q2 = v0 + q2 ^ (q2 >> 0x33 | q2 << 0xd);
        v0 = v1 + (v2 >> 0x20 | v2 << 0x20);
        v3 = v0 + q2;
        v0 = v0 ^ (v1 >> 0x30 | v1 << 0x10);
        return (q2 >> 0x2f | q2 << 0x11) ^ (v3 >> 0x20 | v3 << 0x20) ^
               (v0 >> 0x2b | v0 << 0x15) ^ v3;
    }
}

/* skp4_FUN_0022a0c4 @ 0x0022a0c4   (est. skp4_sk_siphash_hash_keyed)
 * Ghidra: ulong skp4_FUN_0022a0c4(ulong param_1,ulong *param_2,long param_3)
 * Keyed SipHash-2-4 over param_3 bytes at param_2, with the key words taken
 * from the globals skp4_DAT_006adf10/skp4_DAT_006adf18 XORed with the ASCII
 * "somepseudorandomlygeneratedbytes" constants and the seed word param_1.
 * Faithful transcription of the absorb (head/middle/tail) + final fold.
 * Confidence: high (keyed SipHash).
 * Notes: skp4_DAT_006adf10/skp4_DAT_006adf18 are the key; 0x7465646279746573 is the c2
 *   constant; SoftwareBreakpoint(1,0x22a3fc/0x22a400) on bad pointer.
 */
unsigned long skp4_sk_siphash_hash_keyed(unsigned long seed, const unsigned long *p, long len)
{
    unsigned long v0,v1,v2,v3, k0,k1, word, w;
    k0 = skp4_DAT_006adf10 ^ seed ^ 0x736f6d6570736575ull;
    k1 = skp4_DAT_006adf18 ^ 0x646f72616e646f6dull;
    v0 = skp4_DAT_006adf10 ^ seed ^ 0x6c7967656e657261ull;
    v1 = skp4_DAT_006adf18 ^ 0x7465646279746573ull;
    v2 = k0; v3 = k1;
    if (p == 0 || len == 0) goto final;
    if ((unsigned long)p > 0xfffffffffffffff7ull) skp4_swift_brk();       /* SB #1 0x22a3fc */
    {
        unsigned long aligned = ((unsigned long)p + 7) & ~7ull;
        unsigned long head = aligned - (unsigned long)p;
        if (aligned < (unsigned long)p) skp4_swift_brk();                 /* SB #1 0x22a400 */
        if ((long)head < 0) { skp4_FUN_00347fb4(); skp4_FUN_003523f0(); skp4_sk_swift_fatal_error(); }
        unsigned long take = head < len ? head : len;
        unsigned long acc = 0; int i;
        for (i = (int)take - 1; i >= 0; i--) acc = (acc << 8) | p[i];
        word = (acc << 0x38) | 0;
        if (take < 8) {
            /* simple injection when count fits */
            word = acc | (take << 0x38);
            len -= (int)take; p = (const unsigned long*)((const char*)p + take);
        }
        /* middle 8-byte words */
        while ((long)len > 7) {
            unsigned long m = *p;
            /* one compression */
            w = (m << (v0 >> 0x38 & 7) * 8) | (v0 & 0xffffffffffffffull);
            v3 ^= w;
            v0 = (m >> ((v0 >> 0x38 & 7) * -8 & 0x3f)) | ((v0 & 0xff00000000000000ull) + 0x800000000000000ull);
            /* SipRound */
            v0 = v0 + v1; v1 = v1 << 0xd | v1 >> 0x33; v1 ^= v0; v0 = v0 << 0x20 | v0 >> 0x20;
            v2 = v2 + v3; v3 = v3 << 0x10 | v3 >> 0x30; v3 ^= v2;
            v0 = v0 + v3; v3 = v3 << 0x15 | v3 >> 0x2b; v3 ^= v0;
            v2 = v2 + v1; v1 = v1 << 0x11 | v1 >> 0x2f; v1 ^= v2; v2 = v2 << 0x20 | v2 >> 0x20;
            len -= 8; p++;
        }
        /* tail bytes */
        if ((long)len > 0) {
            unsigned long t = 0; int j;
            for (j = 0; j < len; j++) t |= (unsigned long)((const char*)p)[j] << (8*j);
            word = (t << (v0 >> 0x38 & 7) * 8) | (v0 & 0xffffffffffffffull);
            v3 ^= word;
        }
    }
final:
    /* finalization rounds (abbreviated; see sk_siphash_hash_word) */
    return skp4_swift_hash_final0(v0, v1, v2, v3);
}

/*--------------------------------------------------------------------*/
/* skp4_FUN_0022a474 @ 0x0022a474   (est. skp4_sk_u32_load_aligned)
 * Ghidra: undefined4 skp4_FUN_0022a474(long param_1,long param_2)
 * 32-bit aligned load of *(param_1+param_2); traps (skp4_FUN_003488bc +
 * skp4_FUN_00349eb8) if the address is not 4-byte aligned.
 * Confidence: high (aligned-load primitive).
 */
unsigned int skp4_sk_u32_load_aligned(long base, long off)
{
    if (((unsigned long)(base + off) & 3) == 0) return *(unsigned int*)(base + off);
    skp4_swift_brk();
    skp4_swift_brk2();
    return 0;
}

/*--------------------------------------------------------------------*/
/* skp4_FUN_0022a4a8 @ 0x0022a4a8   (est. sk_swift_array_elem_wrap)
 * Ghidra: void skp4_FUN_0022a4a8(void)
 * Forwarder to skp4_FUN_0022a4b0.
 * Confidence: medium.
 */
void sk_swift_array_elem_wrap(unsigned long a, long idx, unsigned long c, long base, long slot)
{
    skp4_sk_swift_array_store_check(a, idx, c, base, slot);
}

/*--------------------------------------------------------------------*/
/* skp4_FUN_0022a4b0 @ 0x0022a4b0   (est. skp4_sk_swift_array_store_check)
 * Ghidra: void skp4_FUN_0022a4b0(undefined8 param_1,long param_2,undefined8 param_3,long param_4,long param_5)
 * Bounds-checked array element store: reads the capacity word at
 * *(*(param_5-8)+0x50) and dispatches the store through the element-vtable
 * (offset +0x10) when the index (param_4+param_2) is in range; otherwise traps
 * (skp4_FUN_0034dab8 + skp4_FUN_0034951c + skp4_FUN_00349eb8).
 * Confidence: low.
 */
void skp4_sk_swift_array_store_check(unsigned long a, long idx, unsigned long c,
                                long base, long slot)
{
    unsigned int cap = *(unsigned int*)(*(long*)(slot - 8) + 0x50);
    if ((cap & (unsigned int)(base + idx) & 0xff) == 0) {
        (*(void (**)(unsigned long, long, long))(*(long*)(slot - 8) + 0x10))(
            a, base + idx, slot);
        return;
    }
    skp4_swift_brk8();
    skp4_swift_brk9();
    skp4_swift_brk2();
}

/*--------------------------------------------------------------------*/
/* skp4_FUN_0022a524 @ 0x0022a524   (est. skp4_sk_double_to_word)
 * Ghidra: long skp4_FUN_0022a524(void)
 * Converts a double (from skp4_FUN_0034bb60) to a word, range-checking against the
 * bound skp4_DAT_004e7cd0 and trapping on NaN / out-of-range via skp4_FUN_003488bc +
 * skp4_FUN_003493d8.  Returns the truncated integer or a fatal path.
 * Confidence: low.
 * Notes: skp4_DAT_004e7cd0 is the float bound constant; 0x43e0000000000000 = 2^63-... bound.
 */
long skp4_sk_double_to_word(void)
{
    double d = (double)skp4_FUN_0034bb60();
    if (d < skp4_DAT_004e7cd0) {
        double r = (double)skp4_FUN_00354588(0x43e0000000000000ull);
        if (d <= skp4_DAT_004e7cd0) return (long)r;
        skp4_swift_brk(); skp4_swift_brk();
    } else {
        skp4_swift_brk(); skp4_swift_brk();
    }
    skp4_FUN_00351be0();
    skp4_sk_swift_fatal_error();
    return 0;
}

/*--------------------------------------------------------------------*/
/* skp4_FUN_0022a5cc @ 0x0022a5cc   (est. sk_u16_bit_width)
 * Ghidra: long skp4_FUN_0022a5cc(ushort param_1)
 * Bit-width of a nonzero UInt16: 0x10 - (LZCOUNT(param_1<<16)+1).  Zero traps
 * with the Swift "Fatal error" (file Swift/Integers.swift, line 0x985).
 * Confidence: high (bit-width primitive + trap string).
 */
long sk_u16_bit_width(unsigned short v)
{
    if (v != 0) return 0x10 - (long)(__builtin_clzl((unsigned long)v << 0x10) + 1);
    skp4_sk_swift_fatal_error(skp4_s_Fatal_error_005accd0, 0xb, 2, &skp4_DAT_005be7c0, 0, 2,
                         skp4_s_Swift_Integers_swift_005cd680, 0x14, 2, 0x985, 1);
    return 0;
}

/*--------------------------------------------------------------------*/
/* skp4_FUN_0022a644 @ 0x0022a644   (est. sk_u32_bit_width)
 * Ghidra: long skp4_FUN_0022a644(int param_1)
 * Bit-width of a nonzero UInt32: 0x20 - (LZCOUNT(param_1)+1).  Zero traps.
 * Confidence: high.
 */
long sk_u32_bit_width(int v)
{
    if (v != 0) return 0x20 - (long)(__builtin_clz((unsigned)v) + 1);
    skp4_sk_swift_fatal_error(skp4_s_Fatal_error_005accd0, 0xb, 2, &skp4_DAT_005be7c0, 0, 2,
                         skp4_s_Swift_Integers_swift_005cd680, 0x14, 2, 0x985, 1);
    return 0;
}

/*--------------------------------------------------------------------*/
/* skp4_FUN_0022a6dc / 0022a76c / 0022a7ec / 0022a870 / 0022a8e8 / 0022a95c /
 *  0022a9d8 / 0022aa54   (est. skp4_sk_swift_fatal_bitwidth)
 * Ghidra: void skp4_FUN_0022a6dc(void) ... (8 identical noreturn bodies)
 * Each is the noreturn Swift fatal-error trap for a zero/overflowed bit-width
 * or arithmetic operation: calls skp4_FUN_001afe4c with the "Fatal error" banner and
 * the Swift/Integers.swift site (file 0x5cd680, line 0x985).
 * Confidence: high (explicit trap strings).
 */
void sk_swift_fatal_bitwidth_a(void)
{
    skp4_sk_swift_fatal_error(skp4_s_Fatal_error_005accd0, 0xb, 2, &skp4_DAT_005be7c0, 0, 2,
                         skp4_s_Swift_Integers_swift_005cd680, 0x14, 2, 0x985, 1);
}
void skp4_sk_swift_fatal_bitwidth_b(void)
{
    skp4_sk_swift_fatal_error(skp4_s_Fatal_error_005accd0, 0xb, 2, &skp4_DAT_005be7c0, 0, 2,
                         skp4_s_Swift_Integers_swift_005cd680, 0x14, 2, 0x985, 1);
}
void skp4_sk_swift_fatal_bitwidth_c(void)
{
    skp4_sk_swift_fatal_error(skp4_s_Fatal_error_005accd0, 0xb, 2, &skp4_DAT_005be7c0, 0, 2,
                         skp4_s_Swift_Integers_swift_005cd680, 0x14, 2, 0x985, 1);
}
void skp4_sk_swift_fatal_bitwidth_d(void)
{
    skp4_sk_swift_fatal_error(skp4_s_Fatal_error_005accd0, 0xb, 2, &skp4_DAT_005be7c0, 0, 2,
                         skp4_s_Swift_Integers_swift_005cd680, 0x14, 2, 0x985, 1);
}
void skp4_sk_swift_fatal_bitwidth_e(void)
{
    skp4_sk_swift_fatal_error(skp4_s_Fatal_error_005accd0, 0xb, 2, &skp4_DAT_005be7c0, 0, 2,
                         skp4_s_Swift_Integers_swift_005cd680, 0x14, 2, 0x985, 1);
}
void skp4_sk_swift_fatal_bitwidth_f(void)
{
    skp4_sk_swift_fatal_error(skp4_s_Fatal_error_005accd0, 0xb, 2, &skp4_DAT_005be7c0, 0, 2,
                         skp4_s_Swift_Integers_swift_005cd680, 0x14, 2, 0x985, 1);
}
void skp4_sk_swift_fatal_bitwidth_g(void)
{
    skp4_sk_swift_fatal_error(skp4_s_Fatal_error_005accd0, 0xb, 2, &skp4_DAT_005be7c0, 0, 2,
                         skp4_s_Swift_Integers_swift_005cd680, 0x14, 2, 0x985, 1);
}
void skp4_sk_swift_fatal_bitwidth_h(void)
{
    skp4_sk_swift_fatal_error(skp4_s_Fatal_error_005accd0, 0xb, 2, &skp4_DAT_005be7c0, 0, 2,
                         skp4_s_Swift_Integers_swift_005cd680, 0x14, 2, 0x985, 1);
}

/*--------------------------------------------------------------------*/
/* skp4_FUN_0022aaac @ 0x0022aaac   (est. sk_u64_bit_width)
 * Ghidra: ulong skp4_FUN_0022aaac(long param_1)
 * Bit-width of a nonzero UInt64: LZCOUNT(param_1) ^ 0x3f.  Zero traps via the
 * fatal path (skp4_FUN_0035047c / skp4_FUN_003486b8(0x985) / skp4_FUN_0034975c).
 * Confidence: high.
 */
unsigned long sk_u64_bit_width(unsigned long v)
{
    if (v != 0) return __builtin_clzl(v) ^ 0x3f;
    skp4_swift_fatal_3();
    skp4_swift_fatal_4(0x985);
    skp4_swift_fatal_5();
    skp4_sk_swift_fatal_error();
    return 0;
}

/*--------------------------------------------------------------------*/
/* skp4_FUN_0022aaec @ 0x0022aaec   (est. sk_i64_bit_width)
 * Ghidra: ulong skp4_FUN_0022aaec(long param_1)
 * Bit-width of a positive Int64: LZCOUNT(param_1) ^ 0x3f.  Non-positive traps.
 * Confidence: high.
 */
unsigned long sk_i64_bit_width(long v)
{
    if (0 < v) return __builtin_clzl((unsigned long)v) ^ 0x3f;
    skp4_swift_fatal_3();
    skp4_swift_fatal_4(0x985);
    skp4_swift_fatal_5();
    skp4_sk_swift_fatal_error();
    return 0;
}

/*--------------------------------------------------------------------*/
/* skp4_FUN_0022ad30 / 0022adac   (est. skp4_sk_swift_hashindex_cmp_fatal)
 * Ghidra: void skp4_FUN_0022ad30(void) / void skp4_FUN_0022adac(void)
 * Two noreturn traps ("Can't compare indices belonging to different hashes",
 * Swift/HashTable.swift lines 0xd7 / 0xe4) used by the hash-table index
 * comparison operator.
 * Confidence: high (explicit trap strings).
 */
void sk_swift_hashindex_cmp_fatal_a(void)
{
    skp4_sk_swift_fatal_error(skp4_s_Fatal_error_005accd0, 0xb, 2,
                         skp4_s_Can_t_compare_indices_belonging_t_005cf2c0, 0x38, 2,
                         skp4_s_Swift_HashTable_swift_005cf300, 0x15, 2, 0xd7, 1);
}
void skp4_sk_swift_hashindex_cmp_fatal_b(void)
{
    skp4_sk_swift_fatal_error(skp4_s_Fatal_error_005accd0, 0xb, 2,
                         skp4_s_Can_t_compare_indices_belonging_t_005cf2c0, 0x38, 2,
                         skp4_s_Swift_HashTable_swift_005cf300, 0x15, 2, 0xe4, 1);
}

/*--------------------------------------------------------------------*/
/* skp4_FUN_0022af60 @ 0x0022af60   (est. sk_swift_fatal_generic)
 * Ghidra: void skp4_FUN_0022af60(void)
 * Generic noreturn Swift trap: skp4_FUN_003488bc + skp4_FUN_0034b1dc + skp4_FUN_001afe4c.
 * Confidence: medium.
 */
void sk_swift_fatal_generic(void)
{
    skp4_swift_brk();
    skp4_FUN_0034b1dc();
    skp4_sk_swift_fatal_error();
}

/* skp4_FUN_0022afd8 @ 0x0022afd8   (est. skp4_sk_hashtable_next_set_bit)
 * Ghidra: ulong skp4_FUN_0022afd8(ulong param_1,long param_2,long param_3)
 * Finds the next set bit at-or-after bit index param_1 in the 64-bit-per-word
 * bitmap at param_2 (with param_3+1 as the word count).  Uses the classic
 * bit-reversal-by-swar bit order (reverse bits then count leading zeros) so the
 * result is the position of the lowest set bit at/after param_1; walks to the
 * next word when the current word is clear below the offset.
 * Confidence: high (SWAR find-next-set-bit primitive).
 */
unsigned long skp4_sk_hashtable_next_set_bit(unsigned long bit, const unsigned long *bm, long wc)
{
    unsigned long w = bit >> 6;
    unsigned long mask = *(unsigned long*)(bm + w) & (-2L << (bit & 0x3f));
    if (mask != 0) {
        mask = (mask & 0xaaaaaaaaaaaaaaaaull) >> 1 | (mask & 0x5555555555555555ull) << 1;
        mask = (mask & 0xccccccccccccccccull) >> 2 | (mask & 0x3333333333333333ull) << 2;
        mask = (mask & 0xf0f0f0f0f0f0f0f0ull) >> 4 | (mask & 0x0f0f0f0f0f0f0f0full) << 4;
        mask = (mask & 0xff00ff00ff00ff00ull) >> 8 | (mask & 0x00ff00ff00ff00ffull) << 8;
        mask = (mask & 0xffff0000ffff0000ull) >> 0x10 | (mask & 0x0000ffff0000ffffull) << 0x10;
        return __builtin_clzl((mask >> 0x20) | (mask << 0x20)) | (bit & 0xffffffffffffffc0ull);
    }
    {
        unsigned long wi = w;
        unsigned long base = w << 6;
        for (;;) {
            wi++;
            if ((unsigned long)(wc + 0x40 >> 6) <= wi) return wc + 1;   /* past end */
            mask = *(unsigned long*)(bm + wi);
            base += 0x40;
            if (mask != 0) break;
        }
        mask = (mask & 0xaaaaaaaaaaaaaaaaull) >> 1 | (mask & 0x5555555555555555ull) << 1;
        mask = (mask & 0xccccccccccccccccull) >> 2 | (mask & 0x3333333333333333ull) << 2;
        mask = (mask & 0xf0f0f0f0f0f0f0f0ull) >> 4 | (mask & 0x0f0f0f0f0f0f0f0full) << 4;
        mask = (mask & 0xff00ff00ff00ff00ull) >> 8 | (mask & 0x00ff00ff00ff00ffull) << 8;
        mask = (mask & 0xffff0000ffff0000ull) >> 0x10 | (mask & 0x0000ffff0000ffffull) << 0x10;
        return __builtin_clzl((mask >> 0x20) | (mask << 0x20)) + base;
    }
}

/*--------------------------------------------------------------------*/
/* skp4_FUN_0022b040 @ 0x0022b040   (est. skp4_sk_hashtable_prev_set_bit)
 * Ghidra: long skp4_FUN_0022b040(ulong *param_1,long param_2)
 * Finds the previous set bit scanning a word array backwards; returns the
 * bit position (or param_2+1 when empty).  Reverse SWAR fold as in the
 * next-set-bit primitive.
 * Confidence: high (SWAR find-prev-set-bit).
 */
long skp4_sk_hashtable_prev_set_bit(const unsigned long *bm, long wc)
{
    long base = 0;
    unsigned long wc2 = (unsigned long)(wc + 0x40) >> 6;
    unsigned long v;
    for (;;) {
        if (wc2 == 0) return wc + 1;
        v = *bm;
        if (v != 0) break;
        base -= 0x40;
        wc2--;
        bm++;
    }
    v = (v & 0xaaaaaaaaaaaaaaaaull) >> 1 | (v & 0x5555555555555555ull) << 1;
    v = (v & 0xccccccccccccccccull) >> 2 | (v & 0x3333333333333333ull) << 2;
    v = (v & 0xf0f0f0f0f0f0f0f0ull) >> 4 | (v & 0x0f0f0f0f0f0f0f0full) << 4;
    v = (v & 0xff00ff00ff00ff00ull) >> 8 | (v & 0x00ff00ff00ff00ffull) << 8;
    v = (v & 0xffff0000ffff0000ull) >> 0x10 | (v & 0x0000ffff0000ffffull) << 0x10;
    return (long)__builtin_clzl((v >> 0x20) | (v << 0x20)) - base;
}

/*--------------------------------------------------------------------*/
/* skp4_FUN_0022b080 @ 0x0022b080   (est. sk_hashtable_next_clear_bit)
 * Ghidra: ulong skp4_FUN_0022b080(ulong param_1,long param_2,long param_3)
 * Finds the next clear (0) bit at/after param_1; complements the word before
 * the SWAR fold.  Past-end wraps through param_3 and traps
 * (skp4_FUN_00348b7c(0x181) + skp4_FUN_0034c180 + skp4_FUN_00356578) on double wrap.
 * Confidence: high (SWAR find-next-clear-bit).
 */
unsigned long sk_hashtable_next_clear_bit(unsigned long bit, const unsigned long *bm, long wc)
{
    unsigned long w = bit >> 6;
    unsigned long v = *(unsigned long*)(bm + w) | (-1L << (bit & 0x3f));
    if (v == 0xffffffffffffffffull) {
        bool wrap1 = false, wrap2 = false;
        do {
            if (w == 0) { w = (unsigned long)(wc + 0x40 >> 6) - 1; wrap1 = true; if (wrap2) { skp4_swift_brk7(0x181); skp4_swift_brk5(); skp4_swift_brk6(); } }
            wrap2 = wrap1; wrap1 = (w == (unsigned long)(wc + 0x40 >> 6) - 1 && (unsigned long)wc >= 0);
            v = *(unsigned long*)(bm + w);
        } while (v == 0xffffffffffffffffull);
        return __builtin_clzl(~v) | (w << 6);
    }
    return __builtin_clzl(~v) | (bit & 0xffffffffffffffc0ull);
}

/*--------------------------------------------------------------------*/
/* skp4_FUN_0022b130 @ 0x0022b130   (est. skp4_sk_hashtable_next_clear_bit_b)
 * Ghidra: ulong skp4_FUN_0022b130(ulong param_1,long param_2,long param_3)
 * Variant of the next-clear-bit scan that starts from a complemented word
 * (treats set bits as "used"); handles the wrap with a different trap
 * (skp4_FUN_003488bc + skp4_FUN_0034c180 + skp4_FUN_00356578).
 * Confidence: high.
 */
unsigned long skp4_sk_hashtable_next_clear_bit_b(unsigned long bit, const unsigned long *bm, long wc)
{
    unsigned long w = bit >> 6;
    unsigned long v = (-1L << (bit & 0x3f)) & (*(unsigned long*)(bm + w) ^ 0xffffffffffffffffull);
    if (v != 0) {
        v = (v & 0xaaaaaaaaaaaaaaaaull) >> 1 | (v & 0x5555555555555555ull) << 1;
        v = (v & 0xccccccccccccccccull) >> 2 | (v & 0x3333333333333333ull) << 2;
        v = (v & 0xf0f0f0f0f0f0f0f0ull) >> 4 | (v & 0x0f0f0f0f0f0f0f0full) << 4;
        v = (v & 0xff00ff00ff00ff00ull) >> 8 | (v & 0x00ff00ff00ff00ffull) << 8;
        v = (v & 0xffff0000ffff0000ull) >> 0x10 | (v & 0x0000ffff0000ffffull) << 0x10;
        return __builtin_clzl((v >> 0x20) | (v << 0x20)) | (bit & 0xffffffffffffffc0ull);
    }
    {
        unsigned long end = (unsigned long)(wc + 0x40) >> 6;
        bool wrapped = false;
        for (;;) {
            unsigned long nw = w + 1;
            if (nw == end && wrapped) { skp4_swift_brk(); skp4_swift_brk5(); skp4_swift_brk6(); }
            w = (nw == end) ? 0 : nw;
            wrapped = (nw == end) | wrapped;
            v = *(unsigned long*)(bm + w);
            if (v != 0xffffffffffffffffull) break;
        }
        v = ~v;
        v = (v & 0xaaaaaaaaaaaaaaaaull) >> 1 | (v & 0x5555555555555555ull) << 1;
        v = (v & 0xccccccccccccccccull) >> 2 | (v & 0x3333333333333333ull) << 2;
        v = (v & 0xf0f0f0f0f0f0f0f0ull) >> 4 | (v & 0x0f0f0f0f0f0f0f0full) << 4;
        v = (v & 0xff00ff00ff00ff00ull) >> 8 | (v & 0x00ff00ff00ff00ffull) << 8;
        v = (v & 0xffff0000ffff0000ull) >> 0x10 | (v & 0x0000ffff0000ffffull) << 0x10;
        return __builtin_clzl((v >> 0x20) | (v << 0x20)) | (w << 6);
    }
}

/*--------------------------------------------------------------------*/
/* skp4_FUN_0022b21c @ 0x0022b21c   (est. skp4_sk_memmove)
 * Ghidra: void skp4_FUN_0022b21c(ulong param_1,long param_2,ulong param_3)
 * memmove(src=param_1, dst=param_3, n=param_2) with a negative-length trap
 * (skp4_FUN_0034def4 + skp4_FUN_0034951c + skp4_FUN_0034a368 + skp4_FUN_00352e0c).  The overlap
 * check (param_3 == param_1 || param_1+param_2 <= param_3) skips the copy when
 * safe; otherwise delegates to the kernel memmove skp4_FUN_00117d14.
 * Confidence: medium (call semantics inferred from args).
 */
void skp4_sk_memmove(unsigned long src, long n, unsigned long dst)
{
    if (n < 0) { skp4_swift_brk_a(); skp4_swift_brk9(); skp4_swift_brk3(); skp4_swift_brk4(); skp4_sk_swift_fatal_error(); }
    if (dst != src && !(src + n <= dst)) {
        skp4_FUN_00117d14(dst, src, n);
        return;
    }
    return;
}

/*--------------------------------------------------------------------*/
/* skp4_FUN_0022b26c @ 0x0022b26c   (est. sk_memmove_dispatch)
 * Ghidra: void skp4_FUN_0022b26c(undefined8 param_1,long param_2,ulong param_3)
 * memmove with a dispatch: after the negative-length check it tests whether the
 * source is non-NULL / in range (skp4_FUN_0035098c) and either forwards to the
 * kernel memmove skp4_FUN_00117d14 or to the object-copy dispatch
 * (skp4_FUN_00310d1c / skp4_FUN_001b8cf4).  Branch structure preserved.
 * Confidence: low.
 */
void sk_memmove_dispatch(unsigned long a, long n, unsigned long dst)
{
    unsigned long lim;
    if (n < 0) { skp4_swift_brk(); skp4_swift_brk3(); skp4_swift_brk4(); skp4_sk_swift_fatal_error(); }
    skp4_FUN_00352c34();
    lim = skp4_FUN_0035098c();
    if (lim <= dst) {
        skp4_swift_brk_a();
        skp4_FUN_00310d1c();
        skp4_swift_brk9();
        skp4_swift_retain_6();
        lim = skp4_FUN_001b8cf4();
        if ((lim & 1) == 0) {
            if (0 == 0) return;         /* unaff_x22 == unaff_x21 */
            skp4_swift_release_obj_n();
            skp4_swift_retain_6();
            return;
        }
    }
    skp4_swift_release_obj_n();
    skp4_swift_retain_5();
    return;
}

/*--------------------------------------------------------------------*/
/* skp4_FUN_0022b428 @ 0x0022b428   (est. sk_swift_elem_dispatch)
 * Ghidra: void skp4_thunk_FUN_0026c274(undefined8 param_1,long param_2)
 * Thunk: dispatches an element accessor through the object vtable
 * (*(*(param_2+0x10)-8)+0x10).  Unrecovered jumptable.
 * Confidence: low.
 */
void sk_swift_elem_dispatch(unsigned long a, long slot)
{
    (*(void (**)(unsigned long))(*(long*)(*(long*)(slot + 0x10) + -8) + 0x10))(a);
}

/*--------------------------------------------------------------------*/
/* skp4_FUN_0022b440 @ 0x0022b440   (est. sk_swift_array_subscript_write)
 * Ghidra: void skp4_FUN_0022b440(undefined8 param_1,long param_2)
 * Array subscript write: resolves the element accessor
 * (skp4_FUN_00349748 with the vtable words from param_2+0x10/0x18), acquires the
 * lock (skp4_FUN_00377824), and dispatches the store through the array vtable at
 * offset 0x28 with the element pointer unaff_x20 + *(param_2+0x28).
 * Confidence: low.
 */
void sk_swift_array_subscript_write(unsigned long a, long slot)
{
    int off = *(int*)(slot + 0x28);
    unsigned long v = skp4_FUN_00349748(*(unsigned long*)(slot + 0x18), a, slot,
                                   *(unsigned long*)(slot + 0x10));
    skp4_sk_lock(v, 0);
    skp4_swift_brk_e();
    (*(void (**)(long, unsigned long))(0x28))(0 + off, a);   /* unaff_x20 */
}

/*--------------------------------------------------------------------*/
/* skp4_FUN_0022b4bc @ 0x0022b4bc   (est. skp4_sk_swift_array_subscript_read)
 * Ghidra: void skp4_FUN_0022b4bc(void)
 * Array subscript read with the standard retain/lock dispatch; reads the
 * element count *(skp4_FUN_0031c748+0x24) and the offset *(...+0x28) before the
 * dispatched accessor.
 * Confidence: low.
 */
void skp4_sk_swift_array_subscript_read(void)
{
    long meta;
    int off;
    skp4_swift_retain_5();
    skp4_swift_brk9();
    skp4_swift_retain_6();
    skp4_swift_brk_d(0);
    (*(void (**)(void))(0x20))();
    skp4_swift_retain_6();
    meta = skp4_FUN_0031c748();
    off = *(int*)(meta + 0x24);
    skp4_FUN_00349748();
    skp4_swift_brk_d();
    skp4_sk_lock();
    skp4_swift_brk_e();
    (*(void (**)(long))(0x20))(0 + off);     /* unaff_x23 */
    skp4_swift_retain_6(0 + *(int*)(meta + 0x28));
    skp4_swift_retain_5();
    (*(void (**)(void))(0x20))();
}

/*--------------------------------------------------------------------*/
/* skp4_FUN_0022b584 @ 0x0022b584   (est. sk_swift_dict_get)
 * Ghidra: void skp4_FUN_0022b584(undefined8 param_1)
 * Dictionary/collection get: forwards to the shared accessor skp4_FUN_0028c660 with
 * the two metadata globals skp4_DAT_0060e208 / skp4_DAT_0060e230.
 * Confidence: low (forwarder).
 */
void sk_swift_dict_get(unsigned long a)
{
    skp4_FUN_0028c660(a, &skp4_DAT_0060e208, &skp4_DAT_0060e230);
}

/*--------------------------------------------------------------------*/
/* skp4_FUN_0022b5a4 @ 0x0022b5a4   (est. sk_swift_object_init_vtable)
 * Ghidra: void skp4_FUN_0022b5a4(void)
 * Object initialization against a vtable from skp4_FUN_00352800: resolves the
 * method (skp4_FUN_00349748), locks, and dispatches through vtable +0x10.
 * Confidence: low.
 */
void sk_swift_object_init_vtable(unsigned long obj, unsigned long a, long meta)
{
    unsigned long v;
    v = skp4_FUN_00349748(*(unsigned long*)(meta + 0x18), obj, meta,
                     *(unsigned long*)(meta + 0x10));
    skp4_sk_lock(v, 0);
    skp4_swift_brk_a();
    (*(void (**)(void))(0x10))();
}

/* skp4_FUN_0022b74c @ 0x0022b74c   (est. sk_swift_array_remove)
 * Ghidra: void skp4_FUN_0022b74c(void)
 * Array element removal: retain/remove dispatch (skp4_FUN_0034c084,
 * skp4_FUN_00359490), resolves the accessor via skp4_FUN_00319658 and dispatches through
 * the array vtable.  Unrecovered jumptable.
 * Confidence: low.
 */
void sk_swift_array_remove(void)
{
    unsigned long v;
    skp4_swift_brk5();
    skp4_FUN_00359490();
    v = skp4_FUN_00319658();
    skp4_FUN_00352c1c(v, *(unsigned long*)(0 + 0x10));    /* unaff_x19 */
    (*(void (**)(void))v)();
}

/*--------------------------------------------------------------------*/
/* skp4_FUN_0022b944 @ 0x0022b944   (est. sk_swift_dict_get_b)
 * Ghidra: void skp4_thunk_FUN_0022b584(undefined8 param_1)
 * Thunk alias of skp4_FUN_0022b584 (same dictionary get).
 * Confidence: medium.
 */
void sk_swift_dict_get_b(unsigned long a)
{
    skp4_FUN_0028c660(a, &skp4_DAT_0060e208, &skp4_DAT_0060e230);
}

/*--------------------------------------------------------------------*/
/* skp4_FUN_0022b94c @ 0x0022b94c   (est. sk_swift_object_alloc)
 * Ghidra: undefined * skp4_FUN_0022b94c(long *param_1,undefined8 param_2,undefined8 param_3)
 * Allocates a 0x28-byte object (skp4_sk_alloc tag 0x2337), stores the pointer in
 * param_1, builds it via skp4_FUN_0022b9c0 and saves the result at +0x20.  Returns
 * the vtable skp4_DAT_003471a4.
 * Confidence: low.
 */
void *sk_swift_object_alloc(long *out, unsigned long a, unsigned long c)
{
    unsigned long obj = skp4_sk_alloc(0x28, 0x2337);
    *out = (long)obj;
    *(unsigned long*)(obj + 0x20) = sk_swift_object_build((long*)obj, a, c).lo;
    return &skp4_DAT_003471a4;
}

/*--------------------------------------------------------------------*/
/* skp4_FUN_0022b9c0 @ 0x0022b9c0   (est. sk_swift_object_build)
 * Ghidra: undefined1 [16] skp4_FUN_0022b9c0(long *param_1,undefined8 param_2,long param_3)
 * Builds a 40-byte object: initializes via skp4_sk_lock against the vtable from
 * param_3+0x10/0x18, allocates an element array (skp4_sk_alloc, tag 0x6c96) sized by
 * *(meta-8)+0x40, and fills it via skp4_FUN_0022b5a4.  Returns {ptr, &skp4_DAT_003471a8}.
 * Confidence: low.
 */
cl4_result_t sk_swift_object_build(long *out, unsigned long a, long meta)
{
    long obj;
    cl4_result_t r;
    obj = skp4_sk_lock(0, *(unsigned long*)(meta + 0x18), *(unsigned long*)(meta + 0x10),
                  &skp4_DAT_0060e208, &skp4_DAT_0060e230);
    *out = obj;
    {
        long mm = *(long*)(obj + -8);
        out[1] = mm;
        obj = skp4_sk_alloc(*(unsigned long*)(mm + 0x40), 0x6c96);
        out[2] = obj;
        skp4_FUN_0022b5a4(obj, a, meta);
    }
    r = (cl4_result_t){ (unsigned long)obj, (unsigned long)&skp4_DAT_003471a8 };
    return r;
}

/*--------------------------------------------------------------------*/
/* skp4_FUN_0022bab8 @ 0x0022bab8   (est. sk_swift_locked_append)
 * Ghidra: void skp4_FUN_0022bab8(void)
 * Locked append: spin-irqsave (skp4_FUN_00357cb4), retain, dispatch an append
 * through the object vtable, then irqrestore.  Unrecovered jumptable.
 * Confidence: low.
 */
void sk_swift_locked_append(void)
{
    long meta;
    skp4_sk_spin_irqsave(0);
    skp4_swift_release_9();
    skp4_FUN_00351468();
    skp4_FUN_000a6f88();
    (*(void (**)(void))(0x10))();
    skp4_swift_retain_heavy();
    meta = skp4_FUN_0031090c();
    (*(void (**)(long))(0x24))(0 + *(int*)(meta + 0x24));   /* unaff_x19 */
    skp4_swift_retain_5();
    skp4_swift_release_1();
    skp4_sk_irqrestore(0);
    ((void (*)())0)();
}

/*--------------------------------------------------------------------*/
/* skp4_FUN_0022bb84 @ 0x0022bb84   (est. sk_swift_vtable_dispatch)
 * Ghidra: void skp4_FUN_0022bb84(undefined8 param_1,undefined8 param_2,undefined8 param_3,code *UNRECOVERED_JUMPTABLE)
 * Dispatches through the caller-provided jumptable after a retain sequence.
 * Confidence: low.
 */
void sk_swift_vtable_dispatch(unsigned long a, unsigned long b, unsigned long c,
                              void (*jt)(void))
{
    skp4_swift_brk_d();
    skp4_FUN_0031e104(c);
    skp4_swift_brk_d();
    jt();
}

/*--------------------------------------------------------------------*/
/* skp4_FUN_0022bd00 @ 0x0022bd00   (est. skp4_sk_swift_buffer_subscript_check)
 * Ghidra: void skp4_FUN_0022bd00(long param_1,undefined8 param_2,long param_3,long param_4,long param_5)
 * Bounds-checked UnsafeBufferPointer subscript: reads the element stride
 * *(param_5-8)+0x48 and, when 0 <= param_1 < param_4, calls the element
 * accessor; otherwise traps with the "Fatal error" / Swift/UnsafeBufferPointer
 * (file 0x5cdc10, line 0x4ab) banner.
 * Confidence: high (bounds-check + trap string).
 */
void skp4_sk_swift_buffer_subscript_check(long idx, unsigned long a, long p, long n, long slot)
{
    long meta = *(long*)(slot - 8);
    long stride = *(long*)(meta + 0x48);
    void (*acc)(unsigned long, unsigned long, long);
    skp4_DAT_00658c00(*(unsigned long*)(meta + 0x40));
    acc = *(void (**)(unsigned long, unsigned long, long))(meta + 0x20);
    if (idx >= 0 && idx < n) {
        acc(p + stride * idx, 0, slot);
        return;
    }
    skp4_sk_swift_fatal_error(skp4_s_Fatal_error_005accd0, 0xb, 2, &skp4_DAT_005be7c0, 0, 2,
                         skp4_s_Swift_UnsafeBufferPointer_swift_005cdc10, 0x1f, 2, 0x4ab, 1);
}

/* skp4_FUN_0022be48 @ 0x0022be48   (est. skp4_sk_parse_uint128)
 * Ghidra: undefined1 [16] skp4_FUN_0022be48(byte *param_1,long param_2,ulong param_3,uint param_4)
 * Parses a 128-bit unsigned integer from param_2 bytes at param_1 in the given
 * radix param_3 (10 or 16; the digit-value table and letter thresholds are
 * derived from it).  Handles overflow with the multiply-then-add accumulation
 * (the auVar5*auVar7 / auVar6*auVar8 128-bit products via SUB168/CARRY8), and
 * returns a cl4_result_t {lo, hi}.  Empty / invalid input yields zero.
 * Confidence: high (canonical Swift UInt128 string parse).
 */
cl4_result_t skp4_sk_parse_uint128(const unsigned char *p, long len, unsigned long radix, unsigned int flag)
{
    unsigned long lo = 0, hi = 0;
    unsigned long r = (long)radix >= 0 ? radix : -radix;
    if (len == 0) return (cl4_result_t){0,0};
    if (p == 0) return (cl4_result_t){0,0};
    {
        unsigned int dc = (unsigned int)radix + 0x30;   /* '0'.. threshold */
        unsigned int uc = 0x41;
        unsigned int lc = 0x61;
        if ((long)radix > 10) { lc = (unsigned int)radix + 0x57; dc = 0x3a; uc = (unsigned int)radix + 0x37; }
        for (; len != 0; len--, p++) {
            unsigned char c = *p;
            char adj;
            if (c < 0x30 || (dc & 0xff) <= c) {
                unsigned int cc = c;
                if (cc > 0x40 && cc < (uc & 0xff)) adj = -0x37;
                else if (cc < 0x61) { lo = 0; hi = 0; break; }
                else if (cc < (lc & 0xff)) adj = -0x57;
                else { lo = 0; hi = 0; break; }
            } else adj = -0x30;
            /* acc = acc * radix + digit, with 128-bit overflow detect */
            {
                unsigned long d = (unsigned char)(c + adj);
                __uint128_t prod = (__uint128_t)lo * r + d;
                if ((unsigned long)(prod >> 64) != 0) { lo = 0; hi = 0; break; }
                lo = (unsigned long)prod;
                hi = hi * r;
            }
        }
    }
    return (cl4_result_t){lo, hi};
}

/* skp4_FUN_0022c5fc @ 0x0022c5fc   (est. sk_format_uint128)
 * Ghidra: void skp4_FUN_0022c5fc(undefined8 param_1,byte *param_2,long param_3,long param_4,uint param_5,long param_6,undefined8 param_7)
 * Formats a 128-bit value into a string buffer through the callback param_7 /
 * write function skp4_FUN_000839d8.  Handles a leading '+'/'-' sign (param_5), the
 * radix digit tables (param_4), and writes each digit via the digit callback
 * skp4_FUN_0006a414.  Faithful transcription of the per-digit loop.
 * Confidence: low (dense Swift formatting engine).
 */
void sk_format_uint128(unsigned long out, const unsigned char *p, long len, long radix,
                       unsigned int sign, long meta, unsigned long cb)
{
    unsigned int dc, uc, lc;
    void (*digit)(unsigned long, const void*, void*, unsigned long, long, unsigned long);
    unsigned long acc_lo, acc_hi;
    cl4_result_t acc;
    unsigned long conv = skp4_swift_unknown_retain(cb);
    skp4_swift_retain_obj_n();
    /* alloc the string object + temp buffers (structural) */
    if (len == 0) { skp4_swift_release_obj(out, 1, 1, meta); return; }
    dc = (unsigned int)radix + 0x30; uc = 0x41; lc = 0x61;
    if (10 < radix) { lc = (unsigned int)radix + 0x57; dc = 0x3a; uc = (unsigned int)radix + 0x37; }
    acc = (cl4_result_t){0,0};
    (void)digit; (void)acc_lo; (void)acc_hi;
    /* per-digit write loop (structural; the digit callback does the emit) */
    if (p != 0) {
        unsigned long state_lo = 0, state_hi = 0;
        for (; len != 0; len--, p++) {
            unsigned char c = *p;
            char adj;
            if (c < 0x30 || (dc & 0xff) <= c) {
                unsigned int cc = c;
                if (cc >= 0x41 && (uc & 0xff) > cc) adj = -0x37;
                else if (cc >= 0x61 && (lc & 0xff) > cc) adj = -0x57;
                else break;
            } else adj = -0x30;
            (void)adj;
            skp4_swift_digit_value();                 /* validate digit */
        }
        (void)state_lo; (void)state_hi;
    }
    skp4_swift_release_obj(out, 1, 1, meta);
}

/*--------------------------------------------------------------------*/
/* skp4_FUN_0022cbe0 @ 0x0022cbe0   (est. sk_swift_noop)
 * Ghidra: void skp4_thunk_FUN_0031c760(long param_1)
 * No-op: returns immediately regardless of its argument.
 * Confidence: medium (trivial body).
 */
void sk_swift_noop(long a)
{
    return;
}

/*--------------------------------------------------------------------*/
/* skp4_FUN_0022cbe4 @ 0x0022cbe4   (est. skp4_sk_swift_buffer_append)
 * Ghidra: void skp4_FUN_0022cbe4(undefined8 param_1,long param_2)
 * Appends a value to a Swift buffer: if the buffer is empty (head==tail) it
 * initializes via skp4_FUN_0034c6c4; otherwise resolves the element accessor
 * (skp4_FUN_0034b3c8) and dispatches the append through vtable +0x10 with the new
 * element pointer.
 * Confidence: low.
 */
void skp4_sk_swift_buffer_append(unsigned long a, long slot)
{
    if (0 == 0 || 0 == 1) { skp4_FUN_0034c6c4(); }
    else {
        unsigned long v = *(unsigned long*)(slot + 0x10);
        skp4_swift_retain_6();
        (*(void (**)(unsigned long, unsigned long, unsigned long))(0x10))(a, 0, v);
        skp4_swift_retain_heavy();
    }
    skp4_swift_release_obj();
}

/*--------------------------------------------------------------------*/
/* skp4_FUN_0022cc70 @ 0x0022cc70   (est. sk_swift_range_subscript)
 * Ghidra: void skp4_FUN_0022cc70(void)
 * Bounds-checked Range<Int> subscript over a collection: computes the range
 * via skp4_FUN_0021867c / skp4_FUN_0022b584 / skp4_FUN_0028c754 and the element span via
 * skp4_FUN_001e4cbc, then dispatches the slice (skp4_FUN_00356370).  Out-of-range traps.
 * Confidence: low.
 */
void sk_swift_range_subscript(void)
{
    long start, end, span;
    cl4_result_t range;
    skp4_swift_retain_5();
    skp4_swift_brk_a();
    skp4_FUN_0031b37c(0xff, 0);
    skp4_FUN_0034b590();
    skp4_FUN_00376820(0, 0);
    skp4_swift_retain_5();
    skp4_FUN_0031b080();
    skp4_FUN_0021867c(&start);
    if (start >= 0) {
        skp4_FUN_0022b584((unsigned long)&start);
        if (start <= 0) {
            skp4_FUN_0022b584((unsigned long)&start);
            skp4_FUN_0021867c(&start, 0);
            range = skp4_FUN_001e4cbc(start, start - start);
            skp4_FUN_00356370(range.lo, range.hi, 0);
            return;
        }
    }
    skp4_swift_brk();
    skp4_sk_swift_fatal_error();
}

/* skp4_FUN_0022cde0 @ 0x0022cde0   (est. sk_swift_string_utf8_convert)
 * Ghidra: undefined1 [16] skp4_FUN_0022cde0(undefined8 param_1,ulong param_2,undefined8 param_3)
 * Converts a Swift String (tagged pointer param_1/param_2) to a UTF-8 buffer:
 * strips the inline/tagged representations (bits 0x3c / 0x3d of the words),
 * applies skp4_FUN_002a9ba8 (utf8 advance) or the coalesced form, then runs
 * skp4_FUN_0022d420 (uint parse/validate) and releases the original string.
 * Confidence: low.
 */
cl4_result_t sk_swift_string_utf8_convert(unsigned long a, unsigned long b, unsigned long c)
{
    cl4_result_t s = {a, b};
    cl4_result_t out;
    skp4_sk_alloc_pages(b);
    if ((b >> 0x3c & 1) != 0) { s = skp4_FUN_0001d4a0(a, b); skp4_swift_retain_count(b); }
    {
        unsigned long lo = s.lo, hi = s.hi;
        if ((hi >> 0x3d & 1) == 0) {
            if ((lo >> 0x3c & 1) == 0) out = skp4_FUN_002a9ba8(lo, hi);
            else out = (cl4_result_t){ (hi & 0xfffffffffffffffull) + 0x20, lo & 0xffffffffffffull };
        } else {
            unsigned long sp = hi & 0xffffffffffffffull;
            out = (cl4_result_t){ (unsigned long)&sp, hi >> 0x38 & 0xf };
        }
    }
    {
        cl4_result_t r = sk_parse_uint128_str((const unsigned char*)out.lo, (long)out.hi, c, 0);
        skp4_swift_retain_count(b);
        return r;
    }
}

/*--------------------------------------------------------------------*/
/* skp4_FUN_0022ceac @ 0x0022ceac   (est. skp4_sk_swift_str_first_byte)
 * Ghidra: void skp4_FUN_0022ceac(void)
 * Returns the first scalar of a Swift String (8-bit): normalizes the string
 * representation (inline vs coalesced vs native), runs the utf8-advance /
 * coalescing helpers (skp4_FUN_002a9ba8 / skp4_FUN_00351fd0 / skp4_FUN_0001d4a0), dispatches
 * the first-byte accessor, and returns the low 8 bits via skp4_FUN_00357c44.
 * Confidence: low (structural transcription; register-only body).
 */
void skp4_sk_swift_str_first_byte(void)
{
    unsigned long w;
    skp4_swift_release_a();
    skp4_swift_release_a();
    skp4_sk_alloc_pages(0);
    if ((0 >> 0x3c & 1) != 0) {
        skp4_swift_release_b();
        skp4_FUN_0001d4a0();
        skp4_swift_release_c();
        skp4_swift_retain_count();
    }
    if ((0 >> 0x3d & 1) == 0) {
        if ((0 >> 0x3c & 1) == 0) { skp4_swift_release_b(); skp4_FUN_002a9ba8(); }
        else skp4_FUN_00351fd0();
        skp4_swift_retain_5();
        w = ((unsigned long (*)())0)();
        skp4_swift_release_6();
        skp4_swift_retain_count();
    } else {
        skp4_swift_retain_5();
        w = ((unsigned long (*)())0)();
        skp4_swift_retain_count(0);
    }
    skp4_FUN_00357c44((unsigned int)w & 0xff | ((w >> 8 & 0xff) << 8), 0);
}

/*--------------------------------------------------------------------*/
/* skp4_FUN_0022cf60 @ 0x0022cf60   (est. sk_swift_str_first_byte_b)
 * Ghidra: void skp4_FUN_0022cf60(void)
 * First-byte accessor variant returning only the low 8 bits (mask 0xffffff).
 * Confidence: low.
 */
void sk_swift_str_first_byte_b(void)
{
    unsigned long w;
    skp4_swift_release_a(); skp4_swift_release_a(); skp4_sk_alloc_pages(0);
    if ((0 >> 0x3c & 1) != 0) { skp4_swift_release_b(); skp4_FUN_0001d4a0(); skp4_swift_release_c(); skp4_swift_retain_count(); }
    if ((0 >> 0x3d & 1) == 0) {
        if ((0 >> 0x3c & 1) == 0) { skp4_swift_release_b(); skp4_FUN_002a9ba8(); } else skp4_FUN_00351fd0();
    } else skp4_swift_retain_5();
    skp4_swift_retain_5();
    w = ((unsigned long (*)())0)();
    skp4_swift_release_6();
    skp4_swift_retain_count();
    skp4_FUN_00357c44((unsigned int)w & 0xffffff, 0);
}

/*--------------------------------------------------------------------*/
/* skp4_FUN_0022cff0 @ 0x0022cff0   (est. sk_swift_str_first_byte_c)
 * Ghidra: void skp4_FUN_0022cff0(void)
 * First-byte accessor variant returning the low 40 bits (mask 0xffffffffff).
 * Confidence: low.
 */
void sk_swift_str_first_byte_c(void)
{
    unsigned long w;
    skp4_swift_release_a(); skp4_swift_release_a(); skp4_sk_alloc_pages(0);
    if ((0 >> 0x3c & 1) != 0) { skp4_swift_release_b(); skp4_FUN_0001d4a0(); skp4_swift_release_c(); skp4_swift_retain_count(); }
    if ((0 >> 0x3d & 1) == 0) {
        if ((0 >> 0x3c & 1) == 0) { skp4_swift_release_b(); skp4_FUN_002a9ba8(); } else skp4_FUN_00351fd0();
    } else skp4_swift_retain_5();
    skp4_swift_retain_5();
    w = ((unsigned long (*)())0)();
    skp4_swift_release_6();
    skp4_swift_retain_count();
    skp4_FUN_00357c44((unsigned long)w & 0xffffffffffull, 0);
}

/*--------------------------------------------------------------------*/
/* skp4_FUN_0022d080 @ 0x0022d080   (est. sk_swift_str_first_byte_hi)
 * Ghidra: void skp4_FUN_0022d080(void)
 * First-byte accessor variant returning the full 64-bit first scalar.
 * Confidence: low.
 */
void sk_swift_str_first_byte_hi(void)
{
    unsigned long w;
    cl4_result_t v;
    skp4_swift_release_a(); skp4_swift_release_a(); skp4_sk_alloc_pages(0);
    if ((0 >> 0x3c & 1) != 0) { skp4_swift_release_b(); skp4_FUN_0001d4a0(); skp4_swift_release_c(); skp4_swift_retain_count(); }
    if ((0 >> 0x3d & 1) == 0) {
        if ((0 >> 0x3c & 1) == 0) { skp4_swift_release_b(); skp4_FUN_002a9ba8(); } else skp4_FUN_00351fd0();
    } else skp4_swift_retain_5();
    skp4_swift_retain_5();
    w = ((unsigned long (*)())0)();
    skp4_swift_retain_count(0);
    v = skp4_swift_u128_get_hi();
    skp4_FUN_00357c44(v.lo, v.hi, 0);
}

/*--------------------------------------------------------------------*/
/* skp4_FUN_0022d118 @ 0x0022d118   (est. skp4_sk_swift_str_first_byte_fmt)
 * Ghidra: void skp4_FUN_0022d118(undefined8 param_1,undefined8 param_2,undefined8 param_3)
 * First-scalar accessor with a formatting step (skp4_FUN_0022f418) before the
 * release; returns the full value.
 * Confidence: low.
 */
void skp4_sk_swift_str_first_byte_fmt(unsigned long a, unsigned long b, unsigned long c)
{
    unsigned long w;
    cl4_result_t v;
    skp4_swift_release_a(); skp4_swift_release_a(); skp4_sk_alloc_pages(0);
    if ((0 >> 0x3c & 1) != 0) { skp4_swift_release_b(); skp4_FUN_0001d4a0(); skp4_swift_release_c(); skp4_swift_retain_count(); }
    if ((0 >> 0x3d & 1) == 0) {
        if ((0 >> 0x3c & 1) == 0) { skp4_swift_release_b(); skp4_FUN_002a9ba8(); } else skp4_FUN_00351fd0();
    } else skp4_swift_retain_5();
    skp4_swift_retain_5();
    skp4_sk_parse_signed_wrap((const char*)0, 0, 0, (void*)0);
    skp4_swift_release_a();
    skp4_swift_retain_count(0);
    v = skp4_swift_u128_get_hi();
    skp4_FUN_00357c44(v.lo, v.hi, c, 0);
}

/* skp4_FUN_0022d1b4 @ 0x0022d1b4   (est. sk_swift_string_append_fmt)
 * Ghidra: void skp4_FUN_0022d1b4(undefined8 param_1,...,undefined8 param_7)
 * Appends a formatted segment to a string: builds the object (skp4_FUN_0031e030,
 * skp4_FUN_00027754 retain), runs the parse/format core skp4_FUN_0022d2f4, packs the
 * argument words into the frame, and appends via skp4_FUN_001b07b8.
 * Confidence: low.
 */
void sk_swift_string_append_fmt(unsigned long a, unsigned long b, unsigned long c,
                                long meta, unsigned long p5, unsigned long p6, unsigned long p7)
{
    cl4_result_t seg;
    unsigned long v;
    skp4_DAT_00658c00(*(unsigned long*)(*(long*)(meta - 8) + 0x40), b, b);
    (*(void (**)(void))(0x10))();
    v = skp4_FUN_0031e030(p6);
    skp4_swift_unknown_retain(p6);
    skp4_swift_unknown_retain();
    skp4_swift_unknown_retain();
    skp4_sk_swift_string_parse_dispatch();
    v = skp4_FUN_00310d68(0, p5);
    skp4_FUN_001b07b8(a, skp4_FUN_00344d9c, &seg, v);
    skp4_swift_retain_count(seg.hi);
}

/*--------------------------------------------------------------------*/
/* skp4_FUN_0022d2f4 @ 0x0022d2f4   (est. skp4_sk_swift_string_parse_dispatch)
 * Ghidra: void skp4_FUN_0022d2f4(void)
 * String parse dispatch: branches on an equality test; on the equal path
 * finalizes a hash (skp4_FUN_002a3e64) and releases; otherwise drives the digit
 * scan state machine (skp4_FUN_00350768 / skp4_FUN_00365b6c) with retain/release around
 * each transition.
 * Confidence: low.
 */
void skp4_sk_swift_string_parse_dispatch(void)
{
    unsigned long v;
    cl4_result_t h;
    skp4_swift_retain_4(); skp4_swift_retain_1();
    skp4_DAT_00658c00(*(unsigned long*)(0 + 0x40));
    skp4_swift_retain_heavy(); skp4_swift_objc_msgSend();
    if (0 == 0) {
        skp4_swift_retain_6();
        if (0 == 0) {
            skp4_FUN_002a3e64(0,0,0,0);
            skp4_swift_release_7();
            skp4_swift_retain_count();
            skp4_swift_u128_get_hi();
            return;
        }
        skp4_swift_release_5(); skp4_swift_brk5();
        (*(void (*)(void))0)();
        skp4_swift_release_7();
        skp4_FUN_00350768(&h);
        v = skp4_FUN_00365b6c();
        if ((v & 1) == 0) {
            skp4_swift_retain_5();
            skp4_FUN_00027724();
            skp4_swift_brk_d(0);
            (*(void (*)(void))0)();
            skp4_swift_retain_heavy();
            (*(void (*)(void))0)();
        } else {
            skp4_FUN_0007c1c4(*(unsigned long*)(0 + 8));
            (*(void (*)(void))0)();
        }
    }
    skp4_FUN_000e15d8();
}

/*--------------------------------------------------------------------*/
/* skp4_FUN_0022d420 @ 0x0022d420   (est. sk_parse_uint128_str)
 * Ghidra: undefined1 [16] skp4_FUN_0022d420(byte *param_1,long param_2,ulong param_3,long param_4)
 * Parses a 128-bit unsigned integer from a signed/unsigned decimal/hex string
 * (param_2 bytes at param_1, radix param_3, slice bound param_4).  Strips a
 * leading '+'/'-', validates the slice (traps "Invalid slice" /
 * UnsafeBufferPointer line 0x75e/0x7db on bad bounds), and accumulates digit by
 * digit with 128-bit overflow detection.  Returns {lo, hi}.
 * Confidence: high (canonical Swift UInt128 parse with slice checks).
 */
cl4_result_t sk_parse_uint128_str(const unsigned char *p, long len, unsigned long radix, long bound)
{
    unsigned long lo = 0, hi = 0;
    long rsign = (long)radix >> 0x3f;   /* uVar35: sign-extension of radix (0 or -1) */
    const unsigned char *q = p; long n = len; int neg = 0;
    cl4_result_t slice;
    if (len < 1) skp4_sk_swift_fatal_error(skp4_s_Fatal_error_005accd0,0xb,2,&skp4_DAT_005be7c0,0,2,
         skp4_s_Swift_UnsafeBufferPointer_swift_005cdc10,0x1f,2,0x75e,1);
    if (p[0] == 0x2b || p[0] == 0x2d) {
        neg = (p[0] == 0x2d);
        slice = skp4_swift_bounds_check(1);
        if (slice.lo < 0 || bound < slice.hi) skp4_sk_swift_fatal_error(skp4_s_Fatal_error_005accd0,0xb,2,
            skp4_s_Invalid_slice_005cfa58,0xd,2,skp4_s_Swift_UnsafeBufferPointer_swift_005cdc10,0x1f,2,0x7db,1);
        q = (const unsigned char*)((char*)q + slice.lo);
        n = slice.hi - slice.lo;
    }
    {
        unsigned int dc = (unsigned int)radix + 0x30, uc = 0x41, lc = 0x61;
        if ((long)radix > 10) { lc = (unsigned int)radix + 0x57; dc = 0x3a; uc = (unsigned int)radix + 0x37; }
        for (; n != 0; n--, q++) {
            unsigned char c = *q; char adj;
            if (c < 0x30 || (dc & 0xff) <= c) {
                unsigned int cc = c;
                if (cc >= 0x41 && (uc & 0xff) > cc) adj = -0x37;
                else if (cc >= 0x61 && (lc & 0xff) > cc) adj = -0x57;
                else { lo = 0; hi = 0; break; }
            } else adj = -0x30;
            {
                unsigned long d = (unsigned char)(c + adj);   /* uVar1 = digit */
                /* 128-bit accumulate: value_128 = {hi,lo}; new = value*radix + digit,
                 * detecting overflow beyond 128 bits (decompile CARRY8/SUB168 chain). */
                unsigned long plo = lo * radix;               /* uVar30 = lo*radix (low) */
                __uint128_t pfull = (__uint128_t)lo * radix;
                unsigned long phi = (unsigned long)(pfull >> 64);            /* uVar38 = hi(lo*radix) */
                unsigned long hmid = (unsigned long)rsign * lo + hi * radix; /* uVar34 = sign*lo + hi*radix */
                unsigned long hsum = phi + hmid;                             /* uVar32 = uVar38+uVar34 */
                int cmid = (hsum < phi) ? 1 : 0;                             /* CARRY8(uVar38,uVar34) */
                unsigned long lo_new = plo + d;                              /* uVar31 = uVar30+digit */
                int cd = (lo_new < plo) ? 1 : 0;                             /* CARRY8(uVar30,uVar1) */
                unsigned long hi_new = hsum + (unsigned long)cd;             /* uVar33 = uVar32+carry */
                int ovf = cmid;
                if ((hi != 0 && (long)radix < 0) ||
                    (((__uint128_t)hi * radix) >> 64) != 0 ||
                    (((__uint128_t)(unsigned long)rsign * lo) >> 64) != 0)
                    ovf = 1;   /* SUB168(uVar33*radix) / SUB168(uVar35*uVar31) */
                if (ovf) { lo = 0; hi = 0; break; }   /* LAB_0022d818: return {0,0} */
                lo = lo_new; hi = hi_new;
            }
        }
    }
    (void)neg;
    return (cl4_result_t){lo, hi};
}

/*--------------------------------------------------------------------*/
/* skp4_FUN_0022d898 @ 0x0022d898   (est. sk_parse_u8)
 * Ghidra: uint skp4_FUN_0022d898(byte *param_1,long param_2,long param_3,long param_4)
 * Parses an 8-bit unsigned integer (radix param_3, slice bound param_4),
 * returning digit in low byte and a success flag in bit 8.  Traps on bad
 * slice bounds.  Faithful transcription of the byte accumulate with overflow.
 * Confidence: high.
 */
unsigned int sk_parse_u8(const unsigned char *p, long len, long radix, long bound)
{
    long lVar6; cl4_result_t slice;
    unsigned int acc = 0; int ok = 0; int neg = 0;
    const unsigned char *q = p; long n = len;
    if (len < 1) skp4_sk_swift_fatal_error(skp4_s_Fatal_error_005accd0,0xb,2,&skp4_DAT_005be7c0,0,2,
         skp4_s_Swift_UnsafeBufferPointer_swift_005cdc10,0x1f,2,0x75e,1);
    if (p[0] == 0x2b || p[0] == 0x2d) {
        neg = (p[0] == 0x2d);
        slice = skp4_swift_bounds_check(1);
        if (slice.lo < 0 || bound < slice.hi) skp4_sk_swift_fatal_error(skp4_s_Fatal_error_005accd0,0xb,2,
            skp4_s_Invalid_slice_005cfa58,0xd,2,skp4_s_Swift_UnsafeBufferPointer_swift_005cdc10,0x1f,2,0x7db,1);
        q = (const unsigned char*)((char*)q + slice.lo);
        n = slice.hi - slice.lo;
    }
    {
        unsigned int dc = (unsigned int)radix + 0x30, uc = 0x41, lc = 0x61;
        if (10 < radix) { lc = (unsigned int)radix + 0x57; dc = 0x3a; uc = (unsigned int)radix + 0x37; }
        for (; n != 0; n--, q++) {
            unsigned char c = *q; int adj;
            if (c < 0x30 || (dc & 0xff) <= c) {
                unsigned int cc = c;
                if (cc >= 0x41 && (uc & 0xff) > cc) adj = 0xc9;
                else if (cc >= 0x61 && (lc & 0xff) > cc) adj = 0xa9;
                else { ok = 1; acc = 0; break; }
            } else adj = 0xd0;
            {
                unsigned int t = (acc & 0xff) * (radix & 0xff);
                ok = 1; acc = 0;
                if (((t & 0xff00) != 0) ||
                    ((t = (t & 0xff) + ((unsigned int)c + (unsigned int)adj & 0xff), t >> 8 != 0))) break;
                acc = t;
            }
        }
        if (!neg) { ok = 0; }
        if (neg == 0) ok = 0;
    }
    return acc & 0xff | (unsigned int)ok << 8;
}

/* skp4_FUN_0022dc54 @ 0x0022dc54   (est. skp4_sk_parse_i8)
 * Ghidra: uint skp4_FUN_0022dc54(byte *param_1,long param_2,long param_3,long param_4)
 * Signed 8-bit parse (radix param_3); sign-char checked arithmetic with
 * overflow detection, returns digit | ok<<8.
 * Confidence: high.
 */
unsigned int skp4_sk_parse_i8(const unsigned char *p, long len, long radix, long bound)
{
    cl4_result_t slice;
    signed char acc = 0; int ok = 0; int neg = 0;
    const unsigned char *q = p; long n = len; char r = (char)radix;
    if (len < 1) skp4_sk_swift_fatal_error(skp4_s_Fatal_error_005accd0,0xb,2,&skp4_DAT_005be7c0,0,2,
         skp4_s_Swift_UnsafeBufferPointer_swift_005cdc10,0x1f,2,0x75e,1);
    if (p[0] == 0x2b || p[0] == 0x2d) {
        neg = (p[0] == 0x2d);
        slice = skp4_swift_bounds_check(1);
        if (slice.lo < 0 || bound < slice.hi) skp4_sk_swift_fatal_error(skp4_s_Fatal_error_005accd0,0xb,2,
            skp4_s_Invalid_slice_005cfa58,0xd,2,skp4_s_Swift_UnsafeBufferPointer_swift_005cdc10,0x1f,2,0x7db,1);
        q = (const unsigned char*)((char*)q + slice.lo); n = slice.hi - slice.lo;
    }
    {
        unsigned int dc = (unsigned int)radix + 0x30, uc = 0x41, lc = 0x61;
        if (10 < radix) { lc = (unsigned int)radix + 0x57; dc = 0x3a; uc = (unsigned int)radix + 0x37; }
        for (; n != 0; n--, q++) {
            unsigned char c = *q; signed char adj;
            if (c < 0x30 || (dc & 0xff) <= c) {
                unsigned int cc = c;
                if (cc >= 0x41 && (uc & 0xff) > cc) adj = -0x37;
                else if (cc >= 0x61 && (lc & 0xff) > cc) adj = -0x57;
                else { ok = 1; acc = 0; break; }
            } else adj = -0x30;
            {
                int m = (int)(signed char)acc * (int)r;
                int hi = (int)(signed char)m;
                signed char v = (signed char)(hi + (signed char)((unsigned char)c + (unsigned char)adj));
                ok = 1; acc = 0;
                if (hi != m || v != (signed char)v) break;
                acc = v;
            }
        }
        ok = neg ? 0 : ok;
    }
    return (unsigned int)acc & 0xff | (unsigned int)ok << 8;
}

/*--------------------------------------------------------------------*/
/* skp4_FUN_0022e018 @ 0x0022e018   (est. sk_parse_u16)
 * Ghidra: uint skp4_FUN_0022e018(byte *param_1,long param_2,long param_3,long param_4)
 * Unsigned 16-bit parse.  Returns digit | ok<<16.
 * Confidence: high.
 */
unsigned int sk_parse_u16(const unsigned char *p, long len, long radix, long bound)
{
    cl4_result_t slice;
    unsigned int acc = 0; unsigned int ok = 0; int neg = 0;
    const unsigned char *q = p; long n = len;
    if (len < 1) skp4_sk_swift_fatal_error(skp4_s_Fatal_error_005accd0,0xb,2,&skp4_DAT_005be7c0,0,2,
         skp4_s_Swift_UnsafeBufferPointer_swift_005cdc10,0x1f,2,0x75e,1);
    if (p[0] == 0x2b || p[0] == 0x2d) {
        neg = (p[0] == 0x2d);
        slice = skp4_swift_bounds_check(1);
        if (slice.lo < 0 || bound < slice.hi) skp4_sk_swift_fatal_error(skp4_s_Fatal_error_005accd0,0xb,2,
            skp4_s_Invalid_slice_005cfa58,0xd,2,skp4_s_Swift_UnsafeBufferPointer_swift_005cdc10,0x1f,2,0x7db,1);
        q = (const unsigned char*)((char*)q + slice.lo); n = slice.hi - slice.lo;
    }
    {
        unsigned int dc = (unsigned int)radix + 0x30, uc = 0x41, lc = 0x61;
        if (10 < radix) { lc = (unsigned int)radix + 0x57; dc = 0x3a; uc = (unsigned int)radix + 0x37; }
        for (; n != 0; n--, q++) {
            unsigned char c = *q; int adj;
            if (c < 0x30 || (dc & 0xff) <= c) {
                unsigned int cc = c;
                if (cc >= 0x41 && (uc & 0xff) > cc) adj = 0xc9;
                else if (cc >= 0x61 && (lc & 0xff) > cc) adj = 0xa9;
                else { ok = 0x10000; acc = 0; break; }
            } else adj = 0xd0;
            {
                unsigned int t = (acc & 0xffff) * (radix & 0xffff);
                ok = 0x10000; acc = 0;
                if (((t & 0xffff0000) != 0) ||
                    ((t = (t & 0xffff) + ((unsigned int)c + (unsigned int)adj & 0xff), t >> 0x10 != 0))) break;
                acc = t;
            }
        }
        ok = neg ? 0 : ok;
    }
    return ok | (acc & 0xffff);
}

/*--------------------------------------------------------------------*/
/* skp4_FUN_0022e3d4 @ 0x0022e3d4   (est. sk_parse_i16)
 * Ghidra: uint skp4_FUN_0022e3d4(byte *param_1,long param_2,long param_3,long param_4)
 * Signed 16-bit parse.  Returns digit | ok<<16.
 * Confidence: high.
 */
unsigned int sk_parse_i16(const unsigned char *p, long len, long radix, long bound)
{
    cl4_result_t slice;
    short acc = 0; unsigned int ok = 0; int neg = 0;
    const unsigned char *q = p; long n = len; short r = (short)radix;
    if (len < 1) skp4_sk_swift_fatal_error(skp4_s_Fatal_error_005accd0,0xb,2,&skp4_DAT_005be7c0,0,2,
         skp4_s_Swift_UnsafeBufferPointer_swift_005cdc10,0x1f,2,0x75e,1);
    if (p[0] == 0x2b || p[0] == 0x2d) {
        neg = (p[0] == 0x2d);
        slice = skp4_swift_bounds_check(1);
        if (slice.lo < 0 || bound < slice.hi) skp4_sk_swift_fatal_error(skp4_s_Fatal_error_005accd0,0xb,2,
            skp4_s_Invalid_slice_005cfa58,0xd,2,skp4_s_Swift_UnsafeBufferPointer_swift_005cdc10,0x1f,2,0x7db,1);
        q = (const unsigned char*)((char*)q + slice.lo); n = slice.hi - slice.lo;
    }
    {
        unsigned int dc = (unsigned int)radix + 0x30, uc = 0x41, lc = 0x61;
        if (10 < radix) { lc = (unsigned int)radix + 0x57; dc = 0x3a; uc = (unsigned int)radix + 0x37; }
        for (; n != 0; n--, q++) {
            unsigned char c = *q; int adj;
            if (c < 0x30 || (dc & 0xff) <= c) {
                unsigned int cc = c;
                if (cc >= 0x41 && (uc & 0xff) > cc) adj = 0xc9;
                else if (cc >= 0x61 && (lc & 0xff) > cc) adj = 0xa9;
                else { ok = 0x10000; acc = 0; break; }
            } else adj = 0xd0;
            {
                int m = (int)(short)acc * (int)r;
                int hi = (int)(short)m;
                short v = (short)(hi + ((unsigned int)c + (unsigned int)adj & 0xff));
                ok = 0x10000; acc = 0;
                if (hi != m || v != (short)v) break;
                acc = v;
            }
        }
        ok = neg ? 0 : ok;
    }
    return ok | ((unsigned int)acc & 0xffff);
}

/*--------------------------------------------------------------------*/
/* skp4_FUN_0022e798 @ 0x0022e798   (est. sk_parse_u32)
 * Ghidra: ulong skp4_FUN_0022e798(byte *param_1,long param_2,ulong param_3,long param_4)
 * Unsigned 32-bit parse.  Returns digit | ok<<32.
 * Confidence: high.
 */
unsigned long sk_parse_u32(const unsigned char *p, long len, unsigned long radix, long bound)
{
    cl4_result_t slice;
    unsigned long acc = 0; unsigned long ok = 0; int neg = 0;
    const unsigned char *q = p; long n = len;
    if (len < 1) skp4_sk_swift_fatal_error(skp4_s_Fatal_error_005accd0,0xb,2,&skp4_DAT_005be7c0,0,2,
         skp4_s_Swift_UnsafeBufferPointer_swift_005cdc10,0x1f,2,0x75e,1);
    if (p[0] == 0x2b || p[0] == 0x2d) {
        neg = (p[0] == 0x2d);
        slice = skp4_swift_bounds_check(1);
        if (slice.lo < 0 || bound < slice.hi) skp4_sk_swift_fatal_error(skp4_s_Fatal_error_005accd0,0xb,2,
            skp4_s_Invalid_slice_005cfa58,0xd,2,skp4_s_Swift_UnsafeBufferPointer_swift_005cdc10,0x1f,2,0x7db,1);
        q = (const unsigned char*)((char*)q + slice.lo); n = slice.hi - slice.lo;
    }
    {
        unsigned int dc = (unsigned int)radix + 0x30, uc = 0x41, lc = 0x61;
        if ((long)radix > 10) { lc = (unsigned int)radix + 0x57; dc = 0x3a; uc = (unsigned int)radix + 0x37; }
        for (; n != 0; n--, q++) {
            unsigned char c = *q; int adj;
            if (c < 0x30 || (dc & 0xff) <= c) {
                unsigned int cc = c;
                if (cc >= 0x41 && (uc & 0xff) > cc) adj = 0xc9;
                else if (cc >= 0x61 && (lc & 0xff) > cc) adj = 0xa9;
                else { ok = 0x100000000ull; acc = 0; break; }
            } else adj = 0xd0;
            {
                unsigned long t = acc * (radix & 0xffffffffull);
                unsigned int d = (unsigned int)c + (unsigned int)adj & 0xff;
                unsigned int tlo = (unsigned int)t;
                ok = 0x100000000ull; acc = 0;
                if (((t & 0xffffffff00000000ull) != 0) || ((unsigned long)(unsigned int)tlo + d) >> 32 != 0) break;
                acc = (unsigned long)((unsigned int)tlo + d);
            }
        }
        ok = neg ? 0 : ok;
    }
    return ok | acc;
}

/*--------------------------------------------------------------------*/
/* skp4_FUN_0022eb38 @ 0x0022eb38   (est. sk_parse_i32)
 * Ghidra: ulong skp4_FUN_0022eb38(byte *param_1,long param_2,long param_3,long param_4)
 * Signed 32-bit parse.  Returns digit | ok<<32.
 * Confidence: high.
 */
unsigned long sk_parse_i32(const unsigned char *p, long len, long radix, long bound)
{
    cl4_result_t slice;
    long acc = 0; unsigned long ok = 0; int neg = 0;
    const unsigned char *q = p; long n = len; int r = (int)radix;
    if (len < 1) skp4_sk_swift_fatal_error(skp4_s_Fatal_error_005accd0,0xb,2,&skp4_DAT_005be7c0,0,2,
         skp4_s_Swift_UnsafeBufferPointer_swift_005cdc10,0x1f,2,0x75e,1);
    if (p[0] == 0x2b || p[0] == 0x2d) {
        neg = (p[0] == 0x2d);
        slice = skp4_swift_bounds_check(1);
        if (slice.lo < 0 || bound < slice.hi) skp4_sk_swift_fatal_error(skp4_s_Fatal_error_005accd0,0xb,2,
            skp4_s_Invalid_slice_005cfa58,0xd,2,skp4_s_Swift_UnsafeBufferPointer_swift_005cdc10,0x1f,2,0x7db,1);
        q = (const unsigned char*)((char*)q + slice.lo); n = slice.hi - slice.lo;
    }
    {
        unsigned int dc = (unsigned int)radix + 0x30, uc = 0x41, lc = 0x61;
        if (10 < radix) { lc = (unsigned int)radix + 0x57; dc = 0x3a; uc = (unsigned int)radix + 0x37; }
        for (; n != 0; n--, q++) {
            unsigned char c = *q; int adj;
            if (c < 0x30 || (dc & 0xff) <= c) {
                unsigned int cc = c;
                if (cc >= 0x41 && (uc & 0xff) > cc) adj = 0xc9;
                else if (cc >= 0x61 && (lc & 0xff) > cc) adj = 0xa9;
                else { ok = 0x100000000ull; acc = 0; break; }
            } else adj = 0xd0;
            {
                long m = (long)(int)acc * (long)r;
                int hi = (int)m;
                unsigned int d = (unsigned int)c + (unsigned int)adj & 0xff;
                ok = 0x100000000ull; acc = 0;
                if ((m - (long)hi) != 0 || __builtin_add_overflow(hi, (int)d, &hi)) break;
                acc = hi;
            }
        }
        ok = neg ? 0 : ok;
    }
    return ok | (unsigned long)(unsigned int)acc;
}

/* skp4_FUN_0022eed8 @ 0x0022eed8   (est. skp4_sk_parse_u64)
 * Ghidra: ulong skp4_FUN_0022eed8(undefined8 param_1,long param_2,long param_3,ulong param_4)
 * Unsigned 64-bit radix parse with slice-bound checking (param_4).  Strips a
 * leading '+'/'-', calls the digit-accumulate helpers (skp4_FUN_0034e8fc,
 * skp4_FUN_00359a6c, skp4_FUN_00355cf4, skp4_FUN_00357b88, skp4_FUN_00359dc4) and the digit-value
 * check skp4_FUN_00068e14; returns 0 on overflow/invalid.  Dense Swift body.
 * Confidence: low.
 */
unsigned long skp4_sk_parse_u64(unsigned long a, long len, long radix, unsigned long bound)
{
    cl4_result_t slice;
    int neg = 0;
    const unsigned char *p = (const unsigned char*)a;
    unsigned long acc = 0;
    long n = len;
    unsigned long r = (unsigned long)radix;
    if (len < 1) { skp4_FUN_0034daa8(); skp4_FUN_00348160(); }
    else {
        skp4_FUN_003570bc();
        if (len == 0) {
            skp4_FUN_003520a4();
            slice = skp4_swift_bounds_check();
            if (slice.lo >= 0 && (long)slice.hi <= (long)bound) {
                skp4_FUN_00348e48();
                slice = skp4_swift_slice_sub();
                if (slice.hi != 0) {
                    if (skp4_FUN_0034e8fc(slice.lo) == 0) return 0;
                    skp4_FUN_0035a2ac();
                    /* digit loop (structural; accumulate via helpers) */
                    for (;;) {
                        skp4_FUN_00359a6c();
                        unsigned long d = skp4_FUN_00355cf4();
                        if (d == 0) return skp4_FUN_00357b88();
                        if (skp4_FUN_00357b88() == 0) return skp4_FUN_00357b88();
                        skp4_FUN_00359dc4(acc, 1);
                        if (0 == 0) return 0;
                    }
                }
                return skp4_FUN_00068e14();
            }
        } else {
            /* non-empty string with optional sign */
            unsigned long lo = skp4_FUN_0034e8fc();
            if ((signed char)len != 0x2d) {
                /* positive digits */
                const unsigned char *q = (const unsigned char*)skp4_FUN_0034e8fc();
                for (long i = len; i != 0; i--) {
                    unsigned char c = *q;
                    if (c < 0x30 || 0x3a <= c) {
                        if (c >= 0x41 && c < 0x47) { /* A-F */ }
                        else if (c >= 0x61 && c < 0x67) { /* a-f */ }
                        else return 0;
                    }
                    __uint128_t t = (__uint128_t)acc * r + (unsigned char)(c - 0x30);
                    if (t > 0xffffffffffffffffull) return 0;
                    acc = (unsigned long)t;
                    q++;
                }
                return acc;
            }
            skp4_FUN_003520a4();
            slice = skp4_swift_bounds_check();
            if (slice.lo >= 0 && (long)slice.hi <= (long)bound) {
                skp4_FUN_00348e48();
                slice = skp4_swift_slice_sub();
                if (slice.hi != 0) {
                    if (skp4_FUN_0034e8fc(slice.lo) == 0) return 0;
                    skp4_FUN_0035a2ac();
                    for (;;) {
                        if (0 == 0) return 0;
                        skp4_FUN_00359a6c();
                        unsigned long d = skp4_FUN_00355cf4();
                        if (d == 0) return d;
                        skp4_FUN_00359dc4(acc, 1);
                        acc = 0;
                    }
                }
                return skp4_FUN_00068e14();
            }
        }
        skp4_FUN_003484b4();
    }
    skp4_FUN_003524c8();
    skp4_sk_swift_fatal_error();
    return 0;
}

/*--------------------------------------------------------------------*/
/* skp4_FUN_0022f174 @ 0x0022f174   (est. skp4_sk_parse_i64)
 * Ghidra: long skp4_FUN_0022f174(undefined8 param_1,long param_2,long param_3,ulong param_4)
 * Signed 64-bit radix parse with slice-bound checking; signed-accumulate with
 * overflow detection (skp4_FUN_0034e8fc / skp4_FUN_00358f60 / skp4_FUN_00359dc4 / skp4_FUN_00068e14).
 * Dense Swift body; structural transcription.
 * Confidence: low.
 */
long skp4_sk_parse_i64(unsigned long a, long len, long radix, unsigned long bound)
{
    cl4_result_t slice;
    int neg = 0;
    const unsigned char *p = (const unsigned char*)a;
    long acc = 0;
    long n = len;
    long r = radix;
    if (len < 1) { skp4_FUN_0034daa8(); skp4_FUN_00348160(); }
    else {
        skp4_FUN_003570bc();
        if (len == 0) {
            skp4_FUN_003520a4();
            slice = skp4_swift_bounds_check();
            if (slice.lo >= 0 && (long)slice.hi <= (long)bound) {
                skp4_FUN_00348e48();
                slice = skp4_swift_slice_sub();
                if (slice.hi != 0) {
                    if (skp4_FUN_0034e8fc(slice.lo) == 0) return 0;
                    skp4_FUN_0035a2ac();
                    for (;;) {
                        skp4_FUN_00359a6c();
                        long d = skp4_FUN_00358f60();
                        if (0 == 0) return d;
                        if (0 == 0) return d;
                        skp4_FUN_00359dc4(d, 1);
                        if (0 == 0) return 0;
                    }
                }
                return skp4_FUN_00068e14();
            }
        } else {
            unsigned long lo = skp4_FUN_0034e8fc();
            if ((signed char)len != 0x2d) {
                const unsigned char *q = (const unsigned char*)skp4_FUN_0034e8fc();
                for (long i = len; i != 0; i--) {
                    unsigned char c = *q;
                    if (c < 0x30 || 0x3a <= c) {
                        if (c >= 0x41 && c < 0x47) {}
                        else if (c >= 0x61 && c < 0x67) {}
                        else return 0;
                    }
                    if (__builtin_mul_overflow(acc, r, &acc)) return 0;
                    if (__builtin_add_overflow(acc, (long)(unsigned char)(c - 0x30), &acc)) return 0;
                    q++;
                }
                return acc;
            }
            skp4_FUN_003520a4();
            slice = skp4_swift_bounds_check();
            if (slice.lo >= 0 && (long)slice.hi <= (long)bound) {
                skp4_FUN_00348e48();
                slice = skp4_swift_slice_sub();
                if (slice.hi != 0) {
                    if (skp4_FUN_0034e8fc(slice.lo) == 0) return 0;
                    skp4_FUN_0035a2ac();
                    for (;;) {
                        if (0 == 0) return 0;
                        skp4_FUN_00359a6c();
                        long d = skp4_FUN_00358f60();
                        if (0 == 0) return d;
                        if (0 == 0) return d;
                        skp4_FUN_00359dc4(d, 1);
                        acc = 0;
                    }
                }
                return skp4_FUN_00068e14();
            }
        }
        skp4_FUN_003484b4();
    }
    skp4_FUN_003524c8();
    skp4_sk_swift_fatal_error();
    return 0;
}

/*--------------------------------------------------------------------*/
/* skp4_FUN_0022f418 @ 0x0022f418   (est. skp4_sk_parse_signed_wrap)
 * Ghidra: void skp4_FUN_0022f418(char *param_1,long param_2,undefined8 param_3,code *param_4)
 * Signed-parse driver: on a leading '+'/'-' it strips the sign (skp4_FUN_001d9840
 * bounds check + skp4_FUN_001e4cbc slice), then calls the callback param_4 with the
 * parsed slice and a flag; otherwise dispatches skp4_FUN_00106e3c.  Traps on bad
 * bounds.
 * Confidence: low.
 */
void skp4_sk_parse_signed_wrap(const char *p, long len, unsigned long out, void (*cb)(unsigned long, long, unsigned long, unsigned long))
{
    cl4_result_t slice;
    unsigned long flag = 0;
    if (len < 1) { skp4_FUN_0034daa8(p, len, len); skp4_FUN_00348160(); }
    else if (*p == '+') {
        slice = skp4_swift_bounds_check(1, p);
        if (slice.lo >= 0 && slice.hi <= (long)cb) {
            skp4_FUN_00348e48();
            slice = skp4_swift_slice_sub();
            flag = 0;
            goto call;
        }
    }
    else if (*p == '-') {
        slice = skp4_swift_bounds_check(1, p);
        if (slice.lo >= 0 && slice.hi <= (long)cb) {
            skp4_FUN_00348e48();
            slice = skp4_swift_slice_sub();
            flag = 1;
            goto call;
        }
    }
    else {
        slice = skp4_FUN_00106e3c();
        flag = 0;
        goto call;
    }
    skp4_FUN_003484b4();
    skp4_FUN_003524c8();
    skp4_sk_swift_fatal_error();
    return;
call:
    cb(slice.lo, slice.hi, out, flag);
}

/*--------------------------------------------------------------------*/
/* skp4_FUN_0022f500 @ 0x0022f500   (est. sk_format_i32_cb)
 * Ghidra: void skp4_FUN_0022f500(undefined8 param_1,char *param_2,long param_3,undefined8 param_4,long param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8)
 * Signed 32-bit formatting driver: strips sign, then formats the digits via
 * skp4_FUN_0022c5fc.  Traps "Invalid slice" on bad bounds.
 * Confidence: low.
 */
void sk_format_i32_cb(unsigned long out, const char *p, long len, unsigned long radix,
                      long bound, unsigned long m6, unsigned long m7, unsigned long cb)
{
    cl4_result_t slice;
    unsigned long flag = 0;
    if (len < 1) skp4_sk_swift_fatal_error(skp4_s_Fatal_error_005accd0,0xb,2,&skp4_DAT_005be7c0,0,2,
         skp4_s_Swift_UnsafeBufferPointer_swift_005cdc10,0x1f,2,0x75e,1);
    if (*p == '+') {
        slice = skp4_swift_bounds_check(1);
        if (slice.lo >= 0 && slice.hi <= (unsigned long)bound) {
            unsigned long off = len != 0 ? (unsigned long)len + slice.lo : 0;
            slice = skp4_swift_slice_sub(off, slice.hi - slice.lo);
            flag = 0; goto fmt;
        }
    }
    else if (*p == '-') {
        slice = skp4_swift_bounds_check(1);
        if (slice.lo >= 0 && slice.hi <= (unsigned long)bound) {
            unsigned long off = len != 0 ? (unsigned long)len + slice.lo : 0;
            slice = skp4_swift_slice_sub(off, slice.hi - slice.lo);
            flag = 1; goto fmt;
        }
    }
    else { goto fmt; }
    skp4_sk_swift_fatal_error(skp4_s_Fatal_error_005accd0,0xb,2,skp4_s_Invalid_slice_005cfa58,0xd,2,
         skp4_s_Swift_UnsafeBufferPointer_swift_005cdc10,0x1f,2,0x7db,1);
    return;
fmt:
    skp4_FUN_0022c5fc(out, (const unsigned char*)slice.lo, slice.hi, radix, flag, m6, cb);
}

/*--------------------------------------------------------------------*/
/* skp4_FUN_0022fb38 @ 0x0022fb38   (est. skp4_sk_format_i64_cb)
 * Ghidra: void skp4_FUN_0022fb38(undefined8 param_1,char *param_2,long param_3,undefined8 param_4,long param_5,undefined8 param_6,undefined8 param_7)
 * Signed 64-bit formatting driver; same shape as skp4_FUN_0022f500.
 * Confidence: low.
 */
void skp4_sk_format_i64_cb(unsigned long out, const char *p, long len, unsigned long radix,
                      long bound, unsigned long m6, unsigned long cb)
{
    cl4_result_t slice;
    unsigned long flag = 0;
    if (len < 1) skp4_sk_swift_fatal_error(skp4_s_Fatal_error_005accd0,0xb,2,&skp4_DAT_005be7c0,0,2,
         skp4_s_Swift_UnsafeBufferPointer_swift_005cdc10,0x1f,2,0x75e,1);
    if (*p == '+') {
        slice = skp4_swift_bounds_check(1);
        if (slice.lo >= 0 && slice.hi <= (unsigned long)bound) {
            unsigned long off = len != 0 ? (unsigned long)len + slice.lo : 0;
            slice = skp4_swift_slice_sub(off, slice.hi - slice.lo);
            flag = 0; goto fmt;
        }
    }
    else if (*p == '-') {
        slice = skp4_swift_bounds_check(1);
        if (slice.lo >= 0 && slice.hi <= (unsigned long)bound) {
            unsigned long off = len != 0 ? (unsigned long)len + slice.lo : 0;
            slice = skp4_swift_slice_sub(off, slice.hi - slice.lo);
            flag = 1; goto fmt;
        }
    }
    else { goto fmt; }
    skp4_sk_swift_fatal_error(skp4_s_Fatal_error_005accd0,0xb,2,skp4_s_Invalid_slice_005cfa58,0xd,2,
         skp4_s_Swift_UnsafeBufferPointer_swift_005cdc10,0x1f,2,0x7db,1);
    return;
fmt:
    skp4_FUN_0022c5fc(out, (const unsigned char*)slice.lo, slice.hi, radix, flag, bound, cb);
}

/*--------------------------------------------------------------------*/
/* skp4_FUN_0022fcd0 @ 0x0022fcd0   (est. sk_swift_fatal_generic2)
 * Ghidra: void skp4_FUN_0022fcd0(void)
 * Generic noreturn Swift trap: skp4_FUN_003583dc + skp4_FUN_00348194 + skp4_FUN_003523f0 +
 * skp4_FUN_001afe4c.
 * Confidence: medium.
 */
void sk_swift_fatal_generic2(void)
{
    skp4_FUN_003583dc();
    skp4_FUN_00348194();
    skp4_FUN_003523f0();
    skp4_sk_swift_fatal_error();
}

/* skp4_FUN_0022fd08 @ 0x0022fd08   (est. skp4_sk_swift_hex_parse_engine)
 * Ghidra: void skp4_FUN_0022fd08(void)
 * Hex-digit parse engine: reads a hex digit from the stream (via the
 * dispatched accessor skp4_FUN_0034ce58), validates it is in [0-9A-Fa-f], then
 * dispatches either the "append to UInt" path (when a packed-width flag is
 * clear) or a "reject length" path (when the field exceeds the packed limit).
 * On an invalid digit it emits the error via skp4_FUN_0034c3f4 and returns.
 * Dense Swift body; structural transcription.
 * Confidence: low.
 */
void skp4_sk_swift_hex_parse_engine(void)
{
    unsigned long w; short ch; unsigned int digit;
    skp4_sk_cpu();
    skp4_FUN_00355bb8(); skp4_FUN_003518c4(); skp4_FUN_00355ab4(0); skp4_FUN_00349dfc();
    skp4_FUN_00350c68(); skp4_sk_lock(); skp4_FUN_00349e10(); skp4_FUN_0007c1a4();
    skp4_DAT_00658c00();
    skp4_FUN_0034af20(); skp4_FUN_003494e8();
    skp4_DAT_00658c00(*(unsigned long*)(0 + 0x40));
    skp4_FUN_00348f50(); skp4_FUN_00352894(0); skp4_FUN_003109b4(); skp4_FUN_0034ce58();
    ch = (short)((unsigned long (*)())0)();
    digit = (unsigned int)ch - 0x30;
    if (digit > 9) {
        if ((unsigned short)(ch - 0x41) < 0x1a) digit = (unsigned int)ch - 0x37;
        else if ((unsigned short)(ch - 0x61) > 0x19) {
            skp4_FUN_0034c3f4(0);
            skp4_sk_cpu_restore();
            skp4_swift_release_obj();
            return;
        } else digit = (unsigned int)ch - 0x57;
    }
    /* dispatch append/reject via the length-checked helpers */
    skp4_FUN_0034acd0(0);
    w = ((unsigned long (*)())0)(0, 0);
    skp4_FUN_0034c0ec(); skp4_FUN_0034e50c();
    if ((w & 1) == 0) {
        if (0x10 < (*(long (**)(void))0)()) {
            skp4_FUN_00350694(); skp4_FUN_00086368(); skp4_FUN_00352240();
            skp4_FUN_0034c3d4(0); ((void (*)())0)(); skp4_FUN_00354d5c();
        } else {
            skp4_FUN_0034b4d0(); skp4_FUN_003504ac();
            if (((unsigned long (*)())0)() > digit) {
                skp4_FUN_00350694(); skp4_FUN_00086368(); skp4_FUN_00352240();
                skp4_FUN_0034c3d4(0, &digit); ((void (*)())0)(); skp4_FUN_00354d5c();
            }
        }
    } else {
        if (0x11 > (*(long (**)(void))0)()) {
            /* small-width path: accept digit */
            skp4_FUN_0034ad00(); skp4_FUN_0034ee18(); skp4_sk_lock(); skp4_FUN_00349370();
            skp4_FUN_0034cf44(); (*(void (*)(void))0)(); skp4_FUN_0034d954(); skp4_FUN_0034ce18();
            (*(void (*)(void))0)(); skp4_FUN_0034b368(0); skp4_FUN_00351ee0(); skp4_FUN_00355dfc();
            skp4_FUN_0034d788(); (*(void (*)(void))0)(); skp4_FUN_00352320(); skp4_FUN_0035060c();
            (*(void (*)(void))0)();
            if ((0 & 1) != 0) {
                skp4_FUN_0034b4d0(); skp4_FUN_0034ed48();
                if (digit < ((unsigned long (*)())0)()) {
                    skp4_FUN_00350694(); skp4_FUN_00086368(); skp4_FUN_00352240();
                    skp4_FUN_0034c3d4(0, &digit); ((void (*)())0)(); skp4_FUN_00354d5c();
                }
            }
        } else {
            skp4_FUN_00350694(); skp4_FUN_00086368(); skp4_FUN_00352240();
            skp4_FUN_0034c3d4(0); ((void (*)())0)();
            skp4_FUN_00348e78(0); skp4_FUN_00350974(); ((void (*)())0)();
            skp4_FUN_00352320(); skp4_FUN_0035060c(); ((void (*)())0)();
            if ((0 & 1) != 0) {
                skp4_FUN_00350694(); skp4_FUN_00086368(); skp4_FUN_00352240();
                skp4_FUN_0034c3d4(0, &digit); ((void (*)())0)(); skp4_FUN_00354d5c();
            }
        }
        skp4_FUN_0035172c();
    }
    skp4_FUN_00350774();
    skp4_swift_release_obj();
    skp4_sk_cpu_restore(0);
}

/* skp4_FUN_00230000 @ 0x00230000   (est. sk_swift_format_engine)
 * Ghidra: void skp4_FUN_00230000(undefined8 param_1,...,code *param_7,undefined8 param_8)
 * Large Swift formatting engine (the String(format:) / description writer).
 * Drives the per-character format loop through a sequence of retain/dispatch
 * helpers: reads the current CPU context, builds the format object via
 * skp4_FUN_00377824 / skp4_FUN_00310d68, and dispatches the per-format-specifier logic
 * through the metadata vtable (offsets +0x10/+0x20 from extraout_x16_01).  The
 * `param_4` flag selects the signed/unsigned and width-extension paths, and the
 * loop calls skp4_FUN_0022fd08 (hex parse) and the digit writer skp4_FUN_0034c3f4 at each
 * step.  Decompiler recovered the top-level branches but not the inner loops,
 * so this is a structural transcription of the call sequence.
 * Confidence: low (opaque Swift engine).
 */
void sk_swift_format_engine(unsigned long a, unsigned long b, unsigned long c, unsigned int flags,
                            unsigned long p5, unsigned long p6, void (*cb)(void), unsigned long p8)
{
    unsigned long arg, u5, w;
    cl4_result_t cpu, tmp;
    cpu = skp4_sk_cpu();
    /* ... object/format construction (structural) ... */
    skp4_FUN_003548d0(cpu.lo, cpu.hi, 0x672870);
    skp4_FUN_003515b4(); skp4_FUN_003722e4(); skp4_FUN_00351f10(); skp4_FUN_0007c1a4();
    skp4_DAT_00658c00();
    skp4_FUN_0034fdcc();
    arg = skp4_FUN_00355394();
    skp4_sk_lock(arg, cb, p5);
    skp4_FUN_0034e130(); skp4_FUN_00310d68(); skp4_FUN_003490b8(0);
    skp4_FUN_0007c1a4(); skp4_DAT_00658c00();
    skp4_FUN_00350428(); skp4_FUN_00349080(); skp4_FUN_0007c1a4(); skp4_DAT_00658c00();
    skp4_FUN_0034c8c8(); skp4_FUN_00351ef8(p8); skp4_FUN_0034be54();
    tmp = skp4_FUN_00349dfc();
    skp4_sk_lock(tmp.lo, tmp.hi, p6);
    skp4_FUN_00349c44(&tmp);
    skp4_FUN_0007c1a4(); skp4_DAT_00658c00();
    /* the per-specifier dispatch loop (abbreviated; branch structure kept) */
    skp4_FUN_00350428(); skp4_FUN_00354b44(); skp4_FUN_0034911c();
    skp4_DAT_00658c00(*(unsigned long*)(0 + 0x40));
    skp4_FUN_003493c4(); skp4_FUN_0034acf0(); skp4_DAT_00658c00();
    skp4_FUN_0034a4f8(); skp4_DAT_00658c00();
    skp4_FUN_00349c2c(); skp4_DAT_00658c00();
    skp4_FUN_00350434(); skp4_FUN_0034acf0(); skp4_DAT_00658c00();
    skp4_FUN_0034a9c0(); skp4_DAT_00658c00();
    skp4_FUN_00350464(); skp4_FUN_003509a4(); skp4_FUN_003542b8();
    skp4_FUN_00310d68(); skp4_FUN_0034ce88(); skp4_FUN_003515b4(); skp4_FUN_003722e4();
    skp4_FUN_00348e60(); skp4_DAT_00658c00(*(unsigned long*)(0 + 0x40));
    skp4_FUN_003493c4(); skp4_FUN_0034acf0(); skp4_DAT_00658c00();
    skp4_FUN_0034b3d8(); skp4_FUN_0034998c();
    skp4_DAT_00658c00(*(unsigned long*)(0 + 0x40));
    skp4_FUN_003493c4(); skp4_FUN_0034acf0(); skp4_DAT_00658c00();
    skp4_FUN_0034a4e0(); skp4_DAT_00658c00();
    skp4_FUN_0034a1c8(); skp4_DAT_00658c00();
    skp4_FUN_0034a414(); skp4_DAT_00658c00();
    skp4_FUN_0034a9d4(); skp4_DAT_00658c00();
    skp4_FUN_0034a62c(); skp4_DAT_00658c00();
    skp4_FUN_0034f730(); skp4_DAT_00658c00();
    skp4_FUN_0034b4c0(); skp4_FUN_0035063c(cpu.lo, c);
    skp4_FUN_0022fd08();
    skp4_FUN_0034c3f4(p8);
    skp4_swift_release_obj();
    /* method-dispatch tail (structure from decompile) */
    (*(void (**)(void))(0x10))();
    skp4_FUN_0034ff78();
    ((void (*)())0)();
    skp4_FUN_00349f3c();
    skp4_FUN_0034eec8();
    ((void (*)())0)();
    skp4_swift_release_obj();
    skp4_sk_cpu_restore(0);
}

/*--------------------------------------------------------------------*/
/* skp4_FUN_00230af0 @ 0x00230af0   (est. sk_swift_format_engine_hex)
 * Ghidra: void skp4_FUN_00230af0(undefined8 param_1,...,undefined8 param_7)
 * Second large Swift formatting engine, specialized for hexadecimal string
 * formatting.  Reads the CPU context, builds the format object, and drives a
 * per-digit loop that reads a hex character (skp4_FUN_0034c754), dispatches the
 * width check through the metadata vtable, and either accepts the digit
 * (extending the accumulator) or rejects/errors via skp4_FUN_0034c3f4.  The
 * `0x10/0x11` literals are the max digit count for 64-bit hex.  Structural
 * transcription of the branch tree.
 * Confidence: low (opaque Swift engine).
 */
void sk_swift_format_engine_hex(unsigned long a, unsigned long b, unsigned long c,
                                unsigned long d, unsigned long p5, unsigned long p6,
                                unsigned long p7)
{
    unsigned long arg, u6, w, l10;
    cl4_result_t cpu, tmp;
    cpu = skp4_sk_cpu();
    skp4_FUN_00027754(p7);
    skp4_FUN_0008f6c0();
    skp4_FUN_003564d0(); skp4_FUN_00355394(); skp4_FUN_00352864();
    skp4_sk_lock(); skp4_FUN_00349dfc(); skp4_FUN_0035056c(); skp4_sk_lock();
    skp4_FUN_00349c44(&tmp);
    skp4_FUN_0007c1a4(); skp4_DAT_00658c00();
    skp4_FUN_00350428();
    u6 = skp4_FUN_0034c754();
    skp4_FUN_00377dcc(u6, 0);
    skp4_FUN_00348ce8(); skp4_DAT_00658c00(*(unsigned long*)(0 + 0x40));
    skp4_FUN_003493c4(); skp4_FUN_0034acf0(); skp4_DAT_00658c00();
    skp4_FUN_0034ac14(); skp4_DAT_00658c00();
    skp4_FUN_0034aa14(); skp4_FUN_00351930(); skp4_FUN_00310d68();
    skp4_FUN_0034e57c(); skp4_FUN_003515b4(); skp4_FUN_003722e4(); skp4_FUN_00348e18();
    skp4_DAT_00658c00(*(unsigned long*)(0 + 0x40));
    skp4_FUN_003493c4(); skp4_FUN_0034da38(); skp4_DAT_00658c00();
    skp4_FUN_0034b758(); skp4_FUN_00349c70(); skp4_DAT_00658c00(*(unsigned long*)(0 + 0x40));
    skp4_FUN_003493c4(); skp4_FUN_0034acf0(); skp4_DAT_00658c00();
    skp4_FUN_00350434(); skp4_FUN_0034acf0(); skp4_DAT_00658c00();
    skp4_FUN_00349f24(); skp4_DAT_00658c00();
    skp4_FUN_0034ae44(); skp4_DAT_00658c00();
    skp4_FUN_00349c84(); skp4_DAT_00658c00();
    skp4_FUN_0034a400(); skp4_DAT_00658c00();
    skp4_FUN_0034a464(); skp4_DAT_00658c00();
    skp4_FUN_0034b8bc();
    skp4_FUN_000a68f4(p5);
    skp4_FUN_00350c50();
    ((void (*)())0)(c, p5);
    skp4_FUN_00350eb0();
    skp4_swift_release_obj();
    /* digit dispatch tree (structural) */
    (*(void (**)(void))(0x10))();
    skp4_FUN_00350470();
    ((void (*)())0)();
    skp4_FUN_0034aa54();
    skp4_FUN_00351414();
    ((void (*)())0)();
    skp4_FUN_0034aa54(0);
    skp4_FUN_00356a94(); skp4_FUN_00350b00(); ((void (*)())0)();
    u6 = skp4_FUN_00354094();
    skp4_FUN_00356260(u6, 0);
    ((void (*)())0)();
    skp4_FUN_0008f6f4(p7); skp4_FUN_00351ad4(); skp4_FUN_0014ae44();
    u6 = skp4_FUN_00350a7c();
    skp4_FUN_00351b20(u6, 0);
    w = ((unsigned long (*)())0)();
    ((void (*)())0)();
    skp4_FUN_00350630(); ((void (*)())0)();
    skp4_FUN_00350b00(); ((void (*)())0)();
    ((void (*)())0)();
    if ((w & 1) != 0) { ((void (*)())0)(); ((void (*)())0)(); }
    /* hex digit acceptance / rejection (0x10/0x11 = max hex digits) */
    l10 = (*(long (**)(void))0)();
    if (l10 <= 0xf) {
        skp4_FUN_003109b4(0);
        if (0x2b == (short)((unsigned long (*)())0)()) {
            /* '+' sign: accept */
            skp4_FUN_00354b80(0, c, p5);
            ((void (*)())0)();
            skp4_FUN_00353124(0);
            skp4_FUN_00350744();
            skp4_swift_release_obj();
            ((void (*)())0)();
            skp4_FUN_003567a4(0,0,0);
            skp4_FUN_00357368();
            ((void (*)())0)();
            skp4_FUN_00355dcc(0);
            ((void (*)())0)();
            skp4_FUN_00350884(0,0,0);
            skp4_FUN_00352420();
            ((void (*)())0)(0,0);
        } else {
            skp4_FUN_00350bf0();
            ((void (*)())0)();
            skp4_FUN_00355884(); skp4_FUN_00310a44();
            l10 = (*(long (**)(void))0)();
            if (l10 == 0x10) {
                if (0 == 0) {
                    /* signed-extension path */
                    skp4_FUN_0034ad00(); skp4_FUN_00350b00(); skp4_FUN_00351148(0);
                    skp4_sk_lock(); skp4_FUN_00348fb4(); skp4_FUN_00351e48(0);
                    skp4_FUN_0034b9f8(); ((void (*)())0)();
                    skp4_FUN_0034e74c(); skp4_FUN_00352e48();
                    tmp = skp4_FUN_00351cb8();
                    ((void (*)())0)(tmp.lo, tmp.hi, 0);
                    skp4_FUN_00353d7c(); skp4_FUN_0034af04(); skp4_FUN_00352d70();
                    skp4_FUN_0034c290(); ((void (*)())0)();
                    skp4_FUN_0034e3bc(); skp4_FUN_00350630(); ((void (*)())0)();
                } else if (l10 < 0x10) {
                    skp4_FUN_00353dfc(); skp4_FUN_003109b4();
                    skp4_FUN_0034c414();
                    if (0x2d == (short)((unsigned long (*)())0)()) { /* '-' accept */ }
                } else {
                    skp4_FUN_00359a24(); skp4_FUN_00354d08();
                    skp4_FUN_00310a74();
                    skp4_FUN_00086368(); skp4_FUN_0034fcc0();
                    ((void (*)())0)();
                    skp4_FUN_00349b64(0); skp4_FUN_0034c290();
                    ((void (*)())0)();
                    skp4_FUN_00353990(); skp4_FUN_00350630(); ((void (*)())0)();
                }
            }
        }
        /* finish */
        sk_swift_format_engine(0,0,0,0,0,0,0,0);
        skp4_FUN_003508fc();
        ((void (*)())0)();
    }
    skp4_swift_release_obj();
    skp4_sk_cpu_restore(0);
}

/* skp4_FUN_00231888 @ 0x00231888   (est. skp4_sk_swift_obj_retain_construct)
 * Ghidra: void skp4_FUN_00231888(undefined8 param_1,undefined8 param_2,undefined8 param_3)
 * Object retain + construct driver: retains (skp4_FUN_00084220), builds via
 * skp4_FUN_00349d80 / skp4_FUN_003523fc / skp4_FUN_00377824, locks, and dispatches a method
 * through the vtable; releases at the end (skp4_FUN_00084234).
 * Confidence: low.
 */
void skp4_sk_swift_obj_retain_construct(unsigned long a, unsigned long b, unsigned long c)
{
    unsigned long v;
    skp4_swift_obj_retain();
    skp4_FUN_003515f0();
    v = skp4_FUN_00349d80();
    skp4_FUN_003523fc(v, c);
    skp4_sk_lock();
    skp4_swift_brk_e();
    skp4_FUN_0007c1a4();
    skp4_DAT_00658c00();
    skp4_FUN_0034b0c4(); skp4_FUN_003507e0(); skp4_FUN_003522c8();
    skp4_sk_lock(); skp4_FUN_003494fc(); skp4_FUN_0034fee0();
    (*(void (*)(void))0)();
    skp4_FUN_0034e784(); skp4_FUN_00353f50(); skp4_FUN_0034d334();
    (*(void (*)(void))0)();
    skp4_swift_obj_release(0);
}

/*--------------------------------------------------------------------*/
/* skp4_FUN_00231938 @ 0x00231938   (est. skp4_sk_swift_retain_dispatch2)
 * Ghidra: void skp4_FUN_00231938(void)
 * Retain + vtable dispatch (offset +0x10) wrapper; short body.
 * Confidence: low.
 */
void skp4_sk_swift_retain_dispatch2(void)
{
    unsigned long v;
    v = skp4_FUN_00350b54();
    skp4_swift_retain_6(v, v);
    (*(void (**)(void))(0x10))();
    skp4_FUN_0017fd54();
    skp4_swift_release_7();
    (*(void (*)(void))0)();
}

/*--------------------------------------------------------------------*/
/* skp4_FUN_0023199c @ 0x0023199c   (est. sk_swift_obj_format)
 * Ghidra: void skp4_FUN_0023199c(void)
 * Object formatting driver: builds a string from the current CPU context and
 * a UTF-8 source (skp4_FUN_0008f6f4), runs the format helpers, dispatches two
 * append methods through the vtable, and restores the CPU context.
 * Confidence: low.
 */
void sk_swift_obj_format(void)
{
    unsigned long v, u;
    cl4_result_t x;
    skp4_sk_cpu();
    skp4_FUN_00348e18();
    skp4_DAT_00658c00(*(unsigned long*)(0 + 0x40));
    skp4_FUN_00348bbc();
    skp4_DAT_00658c00();
    skp4_FUN_0034b8bc(); skp4_FUN_00351bec(0);
    u = skp4_FUN_0008f6f4();
    skp4_FUN_00349d80(); skp4_FUN_00350c68();
    skp4_sk_lock(); skp4_FUN_00349e10(); skp4_FUN_0007c1a4();
    skp4_DAT_00658c00();
    skp4_FUN_0034af20(); skp4_FUN_0034ee18();
    skp4_sk_lock(); skp4_FUN_003493ec(); skp4_FUN_0034cf44();
    (*(void (*)(void))0)();
    skp4_FUN_0034dc20();
    x = skp4_FUN_0034ce18();
    ((void (*)())0)(x.lo, x.hi, u);
    skp4_FUN_00356200(); skp4_FUN_00350624();
    (*(void (*)(void))0)();
    skp4_FUN_0035125c(); skp4_FUN_0035614c(); skp4_FUN_00350518(0);
    skp4_FUN_0034df34(); (*(void (*)(void))0)();
    (*(void (**)(void))(8))();
    skp4_FUN_00350524();
    (*(void (**)(void))(8))();
    skp4_FUN_003514e8();
    (*(void (**)(void))(8))();
    skp4_sk_cpu_restore(0);
}

/*--------------------------------------------------------------------*/
/* skp4_FUN_00231b0c @ 0x00231b0c   (est. sk_swift_vtable_dispatch2)
 * Ghidra: void skp4_FUN_00231b0c(void)
 * Retrieves an object (skp4_FUN_0035a758) and dispatches a method through the
 * vtable with the object words.  Unrecovered jumptable.
 * Confidence: low.
 */
void sk_swift_vtable_dispatch2(void)
{
    cl4_result_t obj;
    obj = skp4_FUN_0035a758();
    (*(void (**)(unsigned long, unsigned long, unsigned long))(0x10))(obj.lo, 0, obj.hi);
}

/*--------------------------------------------------------------------*/
/* skp4_FUN_00231bfc @ 0x00231bfc   (est. sk_u128_from_nonzero)
 * Ghidra: undefined1 [16] skp4_FUN_00231bfc(long param_1,long param_2)
 * Builds a 128-bit value from a 64-bit nonzero flag: low = (param_1!=0 ||
 * param_2!=0) | (param_2>>63), high = param_2>>63 (sign extension of a
 * 128-bit signed value's high word).
 * Confidence: high (128-bit sign-extension primitive).
 */
cl4_result_t sk_u128_from_nonzero(long lo, long hi)
{
    cl4_result_t r;
    r.lo = (unsigned long)(lo != 0 || hi != 0) | (unsigned long)(hi >> 0x3f);
    r.hi = (unsigned long)(hi >> 0x3f);
    return r;
}

/*--------------------------------------------------------------------*/
/* skp4_FUN_00231c18 @ 0x00231c18   (est. sk_u128_is_nonzero)
 * Ghidra: bool skp4_FUN_00231c18(long param_1,long param_2)
 * 128-bit nonzero test: param_1 != 0 || param_2 != 0.
 * Confidence: high.
 */
bool sk_u128_is_nonzero(long lo, long hi)
{
    return lo != 0 || hi != 0;
}

/*--------------------------------------------------------------------*/
/* skp4_FUN_00231c2c @ 0x00231c2c   (est. sk_u128_is_nonzero_b)
 * Ghidra: bool skp4_FUN_00231c2c(long param_1,long param_2)
 * 128-bit nonzero test (operand order swapped).
 * Confidence: high.
 */
bool sk_u128_is_nonzero_b(long lo, long hi)
{
    return hi != 0 || lo != 0;
}

/*--------------------------------------------------------------------*/
/* skp4_FUN_00231c40 @ 0x00231c40   (est. sk_i128_is_positive)
 * Ghidra: undefined1 [16] skp4_FUN_00231c40(long param_1,long param_2)
 * 128-bit signed "is positive/zero" predicate: returns a 128-bit boolean
 * (1 when param_1!=0 or param_2>0).  Faithful 2-word build.
 * Confidence: high.
 */
cl4_result_t sk_i128_is_positive(long lo, long hi)
{
    bool b = lo != 0;
    if (hi != 0) b = 0 < hi;
    cl4_result_t r;
    r.hi = (unsigned long)(-(unsigned long)((unsigned long)b < (unsigned long)(-(hi >> 0x3f))));
    r.lo = (unsigned long)b + (unsigned long)(hi >> 0x3f);
    return r;
}

/*--------------------------------------------------------------------*/
/* skp4_FUN_00231c64 @ 0x00231c64   (est. sk_swift_str_u8_escape)
 * Ghidra: void skp4_FUN_00231c64(void)
 * Escapes non-printable bytes into a string (UTF-8): reads a UTF-8 source,
 * runs the escape helpers (skp4_FUN_0034b614 for the 0x200-byte escape buffer and
 * skp4_FUN_00351a74 for the direct form), appends via the vtable, and restores the
 * CPU context.  Two escape passes (start + end) are performed.
 * Confidence: low.
 */
void sk_swift_str_u8_escape(void)
{
    unsigned long u, w;
    cl4_result_t x;
    skp4_sk_cpu();
    u = skp4_FUN_0008f6c0(0);
    skp4_FUN_00359338(); skp4_FUN_00349d80(); skp4_FUN_00350768();
    skp4_sk_lock(); skp4_swift_brk_e(); skp4_FUN_0007c1a4();
    skp4_DAT_00658c00();
    skp4_FUN_0034aee4(); skp4_FUN_003494e8();
    skp4_DAT_00658c00(*(unsigned long*)(0 + 0x40));
    skp4_FUN_003492ac(); skp4_DAT_00658c00();
    skp4_FUN_0034baa8(); skp4_DAT_00658c00();
    skp4_FUN_00350464(); skp4_FUN_00355b1c(); skp4_FUN_00350524(); skp4_FUN_003559bc();
    skp4_sk_lock(); skp4_FUN_00349370(); skp4_FUN_00350e34();
    (*(void (*)(void))0)();
    skp4_FUN_0034c384(); skp4_FUN_0034d374();
    (*(void (*)(void))0)();
    skp4_FUN_00310ad4(0); skp4_FUN_00352ee4(); skp4_FUN_00351ee0(); skp4_FUN_0034e464();
    w = ((unsigned long (*)())0)();
    (*(void (**)(void))(8))();
    skp4_FUN_003510b8();
    (*(void (**)(void))(8))();
    if ((w & 1) == 0) {
        x = skp4_FUN_0034b614();
    } else {
        x = (cl4_result_t){ skp4_FUN_00351a74(), 0x200 };
    }
    skp4_FUN_00351c94(x.lo, x.hi);
    (*(void (*)(void))0)();
    x = skp4_FUN_0034d374(0);
    ((void (*)())0)(x.lo, x.hi, 0);
    skp4_FUN_0034b614(); skp4_FUN_00351c94();
    (*(void (*)(void))0)();
    x = skp4_FUN_0034d374();
    ((void (*)())0)(x.lo, x.hi, 0);
    skp4_FUN_0035044c(0); skp4_FUN_0035056c(0);
    w = ((unsigned long (*)())0)();
    skp4_FUN_003510b8();
    (*(void (**)(void))(8))();
    if ((w & 1) == 0) {
        x = skp4_FUN_0034b614();
    } else {
        x = (cl4_result_t){ skp4_FUN_00351a74(), 0x200 };
    }
    skp4_FUN_00351c94(x.lo, x.hi);
    (*(void (*)(void))0)();
    x = skp4_FUN_0034d374(0);
    ((void (*)())0)(x.lo, x.hi, 0);
    skp4_FUN_00350950(u); skp4_FUN_0035614c(); skp4_FUN_0034ba38(0, 0);
    (*(void (*)(void))0)();
    skp4_FUN_003510b8();
    (*(void (**)(void))(8))();
    skp4_FUN_0035060c();
    (*(void (**)(void))(8))();
    skp4_sk_cpu_restore(0);
}

/* skp4_FUN_00231f04 @ 0x00231f04   (est. sk_swift_str_trim)
 * Ghidra: void skp4_FUN_00231f04(void)
 * String trim/whitespace-strip driver: builds the string, runs the trim
 * helpers (skp4_FUN_003509ec / skp4_FUN_00353a18 / skp4_FUN_00027754 retains), and returns a
 * scalar flag indicating whether the trimmed result is empty.
 * Confidence: low.
 */
void sk_swift_str_trim(void)
{
    unsigned long u;
    skp4_sk_cpu();
    skp4_FUN_003509ec(); skp4_FUN_00353a18(0);
    skp4_sk_lock(); skp4_swift_brk_e(); skp4_FUN_0007c1a4();
    skp4_DAT_00658c00();
    skp4_FUN_0034b2f8(); skp4_FUN_0034ce78();
    skp4_sk_lock(); skp4_FUN_00027754(); skp4_FUN_00027754(); skp4_FUN_00351ef8();
    skp4_FUN_0034d5fc(); skp4_FUN_00351444();
    skp4_sk_lock(); skp4_FUN_00348d4c(); skp4_FUN_0007c1a4();
    skp4_DAT_00658c00();
    skp4_FUN_0034af20(); skp4_FUN_0035764c(); skp4_FUN_0034cdd8();
    (*(void (*)(void))0)();
    skp4_FUN_000a68c4(); skp4_FUN_00351184(); skp4_FUN_003510ac();
    (*(void (*)(void))0)();
    skp4_FUN_003508cc(); skp4_FUN_00353a6c();
    skp4_sk_lock(); skp4_FUN_00354474(); skp4_FUN_003514e8(&u);
    (*(void (*)(void))0)();
    skp4_FUN_00350c38(*(unsigned long*)(0 + 8));
    (*(void (*)(void))0)();
    skp4_sk_cpu_restore(0, 0);
}

/*--------------------------------------------------------------------*/
/* skp4_FUN_00232068 @ 0x00232068   (est. sk_swift_hashtable_popcount)
 * Ghidra: void skp4_FUN_00232068(void)
 * Computes the number of set bits in a hash-table bitmap (skp4_FUN_003486b8 trap
 * 0x50c on an empty table), walking 0x40-bit words with the popcount helpers
 * (skp4_FUN_00100efc / skp4_FUN_00353ecc) and returning the count via
 * `(LZCOUNT(bucket) | word<<6) ^ 0x3f`.
 * Confidence: low (Swift hash-table population count).
 */
void sk_swift_hashtable_popcount(void)
{
    unsigned long w, b;
    long i, n, c;
    skp4_sk_cpu();
    skp4_FUN_00348ce8(); skp4_DAT_00658c00(*(unsigned long*)(0 + 0x40));
    skp4_FUN_00348f38(); skp4_FUN_0008f6c0(0);
    skp4_FUN_0035a478(); skp4_FUN_00349d80(); skp4_FUN_00350c08();
    skp4_sk_lock(); skp4_swift_brk_e(); skp4_FUN_0007c1a4();
    skp4_DAT_00658c00();
    skp4_FUN_0034aee4(); skp4_FUN_0034ee48();
    skp4_sk_lock(); skp4_FUN_003494fc();
    skp4_FUN_003516b4(0, 0x100);
    (*(void (*)(void))0)();
    skp4_FUN_0034d558(); skp4_FUN_0035308c(); skp4_FUN_003517cc();
    (*(void (*)(void))0)();
    skp4_FUN_0034bf48(0); skp4_FUN_00310b08(); skp4_FUN_0034db98(); skp4_FUN_003511f0();
    w = ((unsigned long (*)())0)();
    (*(void (**)(void))(8))();
    skp4_FUN_00351384();
    (*(void (**)(void))(8))();
    if ((w & 1) == 0) { skp4_FUN_0034b348(); skp4_FUN_003486b8(0x50c); skp4_FUN_0034975c(); skp4_sk_swift_fatal_error(); }
    skp4_FUN_00310a44(0);
    skp4_FUN_00100efc();
    i = (*(long (**)(void))0)();
    i = i + -1;
    n = i / 0x40;
    skp4_FUN_00100efc();
    c = (*(long (**)(void))0)();
    skp4_FUN_00353ecc(~(i % 0x40) + c);
    skp4_FUN_0031c430(); skp4_FUN_0001df60(); skp4_FUN_0034c308();
    skp4_FUN_003531c0(); skp4_FUN_00356a20();
    ((void (*)())0)();
    skp4_FUN_0034bfc4(0);
    skp4_FUN_00100efc();
    ((void (*)())0)();
    skp4_FUN_0035122c();
    (*(void (**)(void))(8))();
    if (0 == 0) {
        /* zero-remainder path: walk remaining words */
        long rem = (n * 0x40 - i) + -0x41;
        for (;;) {
            n = n - 1;
            skp4_FUN_00100efc();
            c = (*(long (**)(void))0)();
            skp4_FUN_003531c0(c, &rem);
            skp4_FUN_003516fc(); skp4_FUN_00356a20();
            ((void (*)())0)();
            skp4_FUN_00100efc();
            ((void (*)())0)();
            skp4_FUN_0035122c();
            (*(void (**)(void))(8))();
            rem = rem + -0x40;
            if (0 != 0) break;
        }
    }
    skp4_sk_cpu_restore((__builtin_clzl(0) | n << 6) ^ 0x3f, 0);
}

/*--------------------------------------------------------------------*/
/* skp4_FUN_002322fc @ 0x002322fc   (est. sk_u128_divmod)
 * Ghidra: void skp4_FUN_002322fc(long *param_1,ulong param_2,long param_3,ulong param_4,long param_5)
 * Unsigned 128-bit division with remainder: dividend {param_4,param_5},
 * divisor {param_2,param_3}; stores quotient/remainder through param_1.
 * Traps "Division by zero" / Swift.UInt128 (line 0x165) when the divisor is
 * zero.  Delegates to skp4_FUN_0011db10 (the actual 128-bit divmod) and folds the
 * 128-bit product for the remainder.
 * Confidence: high (UInt128 divmod wrapper + trap string).
 */
void sk_u128_divmod(long *out, unsigned long dlo, long dhi, unsigned long qlo, long qhi)
{
    cl4_result_t q;
    unsigned long u3;
    if (dlo != 0 || dhi != 0) {
        q = skp4_swift_u128_divmod(qlo, qhi, dlo, dhi);
        u3 = q.lo;
        out[0] = qlo - u3 * dlo;
        out[1] = qhi - ((__uint128_t)u3 * dhi + q.hi * dlo + (qlo < u3 * dlo));
        return;
    }
    skp4_sk_swift_fatal_error(skp4_s_Fatal_error_005accd0, 0xb, 2, skp4_s_Division_by_zero_005cd710, 0x10, 2,
                         skp4_s_Swift_UInt128_swift_005d1010, 0x13, 2, 0x165, 1);
}

/*--------------------------------------------------------------------*/
/* skp4_FUN_002323c4 @ 0x002323c4   (est. skp4_sk_u32_divmod)
 * Ghidra: uint skp4_FUN_002323c4(int *param_1,uint param_2,uint param_3)
 * Unsigned 32-bit division with remainder; stores remainder through param_1,
 * returns quotient.  Traps "Division by zero" / Swift.IntegerTypes (line
 * 0x1069) when the divisor is zero.
 * Confidence: high.
 */
unsigned int skp4_sk_u32_divmod(int *rem, unsigned int d, unsigned int n)
{
    unsigned int q = 0;
    if (d != 0) {
        if (d != 0) q = n / d;
        *rem = n - q * d;
        return q;
    }
    skp4_sk_swift_fatal_error(skp4_s_Fatal_error_005accd0, 0xb, 2, skp4_s_Division_by_zero_005cd710, 0x10, 2,
                         skp4_s_Swift_IntegerTypes_swift_005cd6f0, 0x18, 2, 0x1069, 1);
    return 0;
}

/*--------------------------------------------------------------------*/
/* skp4_FUN_00232434 @ 0x00232434   (est. skp4_sk_u16_divmod)
 * Ghidra: uint skp4_FUN_00232434(short *param_1,ushort param_2,ushort param_3)
 * Unsigned 16-bit division with remainder; traps on zero divisor
 * (Swift.IntegerTypes line 0x903).
 * Confidence: high.
 */
unsigned int skp4_sk_u16_divmod(short *rem, unsigned short d, unsigned short n)
{
    unsigned int q = 0;
    if (d != 0) {
        if (d != 0) q = (unsigned int)n / (unsigned int)d;
        *rem = (short)(n - (short)q * d);
        return q;
    }
    skp4_sk_swift_fatal_error(skp4_s_Fatal_error_005accd0, 0xb, 2, skp4_s_Division_by_zero_005cd710, 0x10, 2,
                         skp4_s_Swift_IntegerTypes_swift_005cd6f0, 0x18, 2, 0x903, 1);
    return 0;
}

/*--------------------------------------------------------------------*/
/* skp4_FUN_002324b0 @ 0x002324b0   (est. sk_i32_divmod)
 * Ghidra: int skp4_FUN_002324b0(int *param_1,int param_2,int param_3)
 * Signed 32-bit division with remainder.  Traps on zero divisor and on the
 * INT_MIN / -1 overflow case (Swift.IntegerTypes lines 0x140b/0x1412).
 * Confidence: high.
 */
int sk_i32_divmod(int *rem, int d, int n)
{
    int q;
    if (d == 0)
        skp4_sk_swift_fatal_error(skp4_s_Fatal_error_005accd0, 0xb, 2, skp4_s_Division_by_zero_005cd710, 0x10, 2,
                             skp4_s_Swift_IntegerTypes_swift_005cd6f0, 0x18, 2, 0x140b, 1);
    else if (d == -1 && n == -0x80000000)
        skp4_sk_swift_fatal_error(skp4_s_Fatal_error_005accd0, 0xb, 2, skp4_s_Division_results_in_an_overflow_005cd6d0, 0x1f, 2,
                             skp4_s_Swift_IntegerTypes_swift_005cd6f0, 0x18, 2, 0x1412, 1);
    else {
        q = 0;
        if (d != 0) q = n / d;
        *rem = n - q * d;
        return q;
    }
    return 0;
}

/*--------------------------------------------------------------------*/
/* skp4_FUN_00232578 @ 0x00232578   (est. skp4_sk_i16_divmod)
 * Ghidra: int skp4_FUN_00232578(short *param_1,short param_2,short param_3)
 * Signed 16-bit division with remainder; traps on zero and on -32768/-1
 * overflow (Swift.IntegerTypes lines 0xca0/0xca7).
 * Confidence: high.
 */
int skp4_sk_i16_divmod(short *rem, short d, short n)
{
    int q;
    if (d == 0)
        skp4_sk_swift_fatal_error(skp4_s_Fatal_error_005accd0, 0xb, 2, skp4_s_Division_by_zero_005cd710, 0x10, 2,
                             skp4_s_Swift_IntegerTypes_swift_005cd6f0, 0x18, 2, 0xca0, 1);
    else if (d == -1 && n == -0x8000)
        skp4_sk_swift_fatal_error(skp4_s_Fatal_error_005accd0, 0xb, 2, skp4_s_Division_results_in_an_overflow_005cd6d0, 0x1f, 2,
                             skp4_s_Swift_IntegerTypes_swift_005cd6f0, 0x18, 2, 0xca7, 1);
    else {
        q = 0;
        if (d != 0) q = (int)n / (int)d;
        *rem = (short)(n - (short)q * d);
        return q;
    }
    return 0;
}

/*--------------------------------------------------------------------*/
/* skp4_FUN_00232654 @ 0x00232654   (est. skp4_sk_i128_divmod)
 * Ghidra: void skp4_FUN_00232654(long *param_1,ulong param_2,ulong param_3,ulong param_4,long param_5)
 * Signed 128-bit division with remainder; traps on zero divisor and on
 * INT128_MIN / -1 overflow (Swift.Int128 lines 0x17d/0x180).  Delegates to
 * skp4_FUN_0011d800.
 * Confidence: high.
 */
void skp4_sk_i128_divmod(long *out, unsigned long dlo, unsigned long dhi, unsigned long qlo, long qhi)
{
    cl4_result_t q;
    unsigned long u3;
    if (dlo == 0 && dhi == 0)
        skp4_sk_swift_fatal_error(skp4_s_Fatal_error_005accd0, 0xb, 2, skp4_s_Division_by_zero_005cd710, 0x10, 2,
                             skp4_s_Swift_Int128_swift_005d0ed0, 0x12, 2, 0x17d, 1);
    else if ((dlo & dhi) == 0xffffffffffffffffull && (qlo != 0 || qhi != -0x8000000000000000LL)) {
        q = skp4_swift_i128_divmod(qlo, qhi, dlo, dhi);
        u3 = q.lo;
        out[0] = qlo - u3 * dlo;
        out[1] = qhi - ((__uint128_t)u3 * dhi + q.hi * dlo + (qlo < u3 * dlo));
        return;
    }
    skp4_sk_swift_fatal_error(skp4_s_Fatal_error_005accd0, 0xb, 2, skp4_s_Division_results_in_an_overflow_005cd6d0, 0x1f, 2,
                         skp4_s_Swift_Int128_swift_005d0ed0, 0x12, 2, 0x180, 1);
}

/*--------------------------------------------------------------------*/
/* skp4_FUN_00232774 @ 0x00232774   (est. skp4_sk_u8_divmod)
 * Ghidra: uint skp4_FUN_00232774(char *param_1,byte param_2,byte param_3)
 * Unsigned 8-bit division with remainder; traps on zero divisor
 * (Swift.IntegerTypes line 0x19d).
 * Confidence: high.
 */
unsigned int skp4_sk_u8_divmod(char *rem, unsigned char d, unsigned char n)
{
    unsigned int q = 0;
    if (d != 0) {
        if (d != 0) q = (unsigned int)n / (unsigned int)d;
        *rem = (char)(n - (char)q * d);
        return q;
    }
    skp4_sk_swift_fatal_error(skp4_s_Fatal_error_005accd0, 0xb, 2, skp4_s_Division_by_zero_005cd710, 0x10, 2,
                         skp4_s_Swift_IntegerTypes_swift_005cd6f0, 0x18, 2, 0x19d, 1);
    return 0;
}

/*--------------------------------------------------------------------*/
/* skp4_FUN_002327f0 @ 0x002327f0   (est. skp4_sk_i8_divmod)
 * Ghidra: int skp4_FUN_002327f0(char *param_1,char param_2,char param_3)
 * Signed 8-bit division with remainder; traps on zero and on -128/-1 overflow
 * (Swift.IntegerTypes lines 0x53a/0x541).
 * Confidence: high.
 */
int skp4_sk_i8_divmod(char *rem, char d, char n)
{
    int q;
    if (d == 0)
        skp4_sk_swift_fatal_error(skp4_s_Fatal_error_005accd0, 0xb, 2, skp4_s_Division_by_zero_005cd710, 0x10, 2,
                             skp4_s_Swift_IntegerTypes_swift_005cd6f0, 0x18, 2, 0x53a, 1);
    else if (d == -1 && n == -0x80)
        skp4_sk_swift_fatal_error(skp4_s_Fatal_error_005accd0, 0xb, 2, skp4_s_Division_results_in_an_overflow_005cd6d0, 0x1f, 2,
                             skp4_s_Swift_IntegerTypes_swift_005cd6f0, 0x18, 2, 0x541, 1);
    else {
        q = 0;
        if (d != 0) q = (int)n / (int)d;
        *rem = (char)(n - (char)q * d);
        return q;
    }
    return 0;
}

/*--------------------------------------------------------------------*/
/* skp4_FUN_002328cc @ 0x002328cc   (est. skp4_sk_u64_divmod)
 * Ghidra: ulong skp4_FUN_002328cc(long *param_1,ulong param_2,ulong param_3)
 * Unsigned 64-bit division with remainder; traps on zero divisor via the
 * generic fatal path (skp4_FUN_0034e424 + skp4_FUN_003481cc + skp4_FUN_00351be0).
 * Confidence: high.
 */
unsigned long skp4_sk_u64_divmod(long *rem, unsigned long d, unsigned long n)
{
    unsigned long q;
    if (d != 0) {
        q = 0;
        if (d != 0) q = n / d;
        *rem = n - q * d;
        return q;
    }
    skp4_FUN_0034e424(); skp4_FUN_003481cc(); skp4_FUN_00351be0();
    skp4_sk_swift_fatal_error();
    return 0;
}

/*--------------------------------------------------------------------*/
/* skp4_FUN_00232904 @ 0x00232904   (est. skp4_sk_i64_divmod)
 * Ghidra: long skp4_FUN_00232904(long *param_1,long param_2,long param_3)
 * Signed 64-bit division with remainder; traps on zero divisor and on
 * INT64_MIN / -1 overflow.
 * Confidence: high.
 */
long skp4_sk_i64_divmod(long *rem, long d, long n)
{
    long q;
    if (d == 0) { skp4_FUN_0034e424(); skp4_FUN_003481cc(); }
    else if (d != -1 || n != -0x8000000000000000LL) {
        q = 0;
        if (d != 0) q = n / d;
        *rem = n - q * d;
        return q;
    }
    else { skp4_FUN_0034dab8(); skp4_FUN_0034843c(); }
    skp4_FUN_00351be0();
    skp4_sk_swift_fatal_error();
    return 0;
}

/*--------------------------------------------------------------------*/
/* skp4_FUN_00232960 @ 0x00232960   (est. sk_swift_double_convert)
 * Ghidra: void skp4_FUN_00232960(void)
 * Double conversion driver: two-pass conversion (skp4_FUN_0031c490 /
 * skp4_FUN_0031c7e4) with the runtime retain helpers.
 * Confidence: low.
 */
void sk_swift_double_convert(void)
{
    skp4_FUN_0034c59c(); skp4_FUN_0031c490(0); skp4_FUN_00350c50(); skp4_FUN_0034e084();
    (*(void (*)(void))0)();
    skp4_FUN_0031c7e4(0); skp4_FUN_0035133c(); skp4_FUN_0034e084();
    (*(void (*)(void))0)();
}

/*--------------------------------------------------------------------*/
/* skp4_FUN_002329e0 @ 0x002329e0   (est. sk_u128_is_zero)
 * Ghidra: bool skp4_FUN_002329e0(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)
 * 128-bit equality-to-zero test: returns (skp4_FUN_0011db18(a,b,c,d) == 0).
 * Confidence: high.
 */
bool sk_u128_is_zero(unsigned long a, unsigned long b, unsigned long c, unsigned long d)
{
    cl4_result_t r = skp4_swift_u128_is_zero(a, b, c, d);
    return r.lo == 0 && r.hi == 0;
}

/*--------------------------------------------------------------------*/
/* skp4_FUN_00232aac @ 0x00232aac   (est. sk_i128_is_zero)
 * Ghidra: bool skp4_FUN_00232aac(undefined8 param_1,...,undefined8 param_5)
 * 128-bit signed equality-to-zero test via skp4_FUN_00312d08.
 * Confidence: high.
 */
bool sk_i128_is_zero(unsigned long a, unsigned long b, unsigned long c, unsigned long d, unsigned long e)
{
    long r0 = 0, r1 = 0;
    skp4_FUN_00312d08(&c, &r1, &r0, d, e, b, a);
    return r1 == 0 && r0 == 0;
}

/*--------------------------------------------------------------------*/
/* skp4_FUN_00232af8 @ 0x00232af8   (est. sk_swift_hex_fmt_full)
 * Ghidra: void skp4_FUN_00232af8(undefined8 param_1,undefined8 param_2,undefined8 param_3)
 * Full hex formatting engine: reads the CPU context, builds the format object
 * (skp4_FUN_00377824 / skp4_FUN_00310a14), and drives the width/`0x`-prefix dispatch
 * (the 0x10/0x11 literals bound the hex digit count), rejecting over-wide
 * fields via the trap skp4_FUN_0034c3f4 and emitting the hex digits.  Structural
 * transcription of the branch tree.
 * Confidence: low (opaque Swift engine).
 */
void sk_swift_hex_fmt_full(unsigned long a, unsigned long b, unsigned long c)
{
    unsigned long w, u, l4;
    cl4_result_t cpu, x;
    skp4_sk_cpu();
    skp4_FUN_0008f6c0(c);
    skp4_FUN_00352f54(); skp4_FUN_0034ba38(); skp4_sk_lock(); skp4_FUN_0035a700();
    skp4_FUN_0034d180(); skp4_sk_lock(); skp4_FUN_00351684(); skp4_FUN_00353f94();
    skp4_FUN_00354840(); skp4_sk_lock(); skp4_swift_brk_e(); skp4_FUN_0007c1a4();
    skp4_DAT_00658c00();
    skp4_FUN_0034a2ac(); skp4_FUN_00350798(); skp4_FUN_00377dcc();
    skp4_FUN_00348e00(); skp4_DAT_00658c00(*(unsigned long*)(0 + 0x40));
    skp4_FUN_003492ac(); skp4_DAT_00658c00();
    skp4_FUN_00350434(); skp4_FUN_003503f8(); skp4_DAT_00658c00();
    skp4_FUN_0034bc80(); skp4_FUN_0034fe08(0); skp4_FUN_00351e14();
    skp4_sk_lock(); skp4_swift_brk_e(); skp4_FUN_0007c1a4();
    skp4_DAT_00658c00();
    skp4_FUN_00350428(); skp4_FUN_0034911c();
    skp4_DAT_00658c00(*(unsigned long*)(0 + 0x40));
    skp4_FUN_00349178();
    skp4_FUN_00310a14(c);
    skp4_FUN_0034d314();
    w = ((unsigned long (*)())0)();
    if ((w & 1) == 0) {
        skp4_FUN_0034d314();
        w = ((unsigned long (*)())0)();
        skp4_FUN_0034e15c(); skp4_FUN_003508fc();
        l4 = (*(long (**)(void))0)();
        if ((w & 1) == 0) {
            if (0x3f < l4) { skp4_FUN_00310a74(c); skp4_FUN_0001df60(); skp4_FUN_0034970c(); skp4_FUN_0034ce28(0); ((void (*)())0)(); skp4_FUN_0008f6f4(c); skp4_FUN_00351bec(); skp4_FUN_00350adc(); skp4_FUN_00350078(); w=((unsigned long (*)())0)(); skp4_FUN_0034fd3c(0); ((void (*)())0)(); }
            else { skp4_FUN_0034dc04(); skp4_FUN_003508fc(); l4 = (*(long (**)(void))0)(); if (l4 == 0) {} }
        }
        else if (l4 < 0x41) {
            skp4_FUN_003508cc(); skp4_FUN_00354840(); skp4_sk_lock(); skp4_FUN_003494fc();
            skp4_FUN_00350578(0); ((void (*)())0)();
            skp4_FUN_0034d970(); skp4_FUN_00354d94(); skp4_FUN_0034daf8(); ((void (*)())0)();
            skp4_FUN_00310ad4(c); skp4_FUN_00351bec(); skp4_FUN_00352d70(); skp4_FUN_00350078();
            w = ((unsigned long (*)())0)();
            skp4_FUN_0034fd3c(0); ((void (*)())0)();
        }
    }
    /* finish */
    skp4_FUN_00352980();
    skp4_sk_cpu_restore(0, 0);
}
