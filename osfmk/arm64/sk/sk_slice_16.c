/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel,
 * arm64e, image base 0) — the cL4 microkernel (GL1). Ground truth: Ghidra FUN_
 * names + addresses in program cl4_kernel.raw. Version "cL4 microkernel
 * (cL4 (679.100.61))". All names are estimates unless string/header-matched.
 *
 * This file covers the Swift-runtime DeviceTreeKit collection / observer /
 * accounting region at 0x70098 - 0x73af0: growable-array (vector) reserve and
 * element-move shims, sorted-set / dictionary probes over bit-indexed tables,
 * scope-bound lock-select emitters, retain/release glue, and the
 * InternalExclaveLauncher accounting fatal path.  Continuation of the 0x6xxxx
 * DeviceTreeKit slice (sk_slice_13.c) sharing the same Swift helper vocabulary.
 */

#ifndef _SK_SLICE_16_H_
#define _SK_SLICE_16_H_

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

/* 128-bit result word used by the SVC frame ABI (hi = high 64 bits). */
typedef struct { uint64_t lo; uint64_t hi; } sk_u128_t;
/* Function pointer rendered from Ghidra's "code *" type (unspecified args). */
typedef uint64_t (*sk_code_t)();
#define CONCAT11(a,b) ((((uint64_t)(a)) << 8) | ((uint64_t)(b)))
#define CONCAT12(a,b) ((((uint64_t)(a)) << 8) | ((uint64_t)(b)))
#define CONCAT23(a,b) ((((uint64_t)(a)) << 16) | ((uint64_t)(b)))
#define CONCAT32(a,b) ((((uint64_t)(a)) << 24) | ((uint64_t)(b)))
#define CONCAT41(a,b) ((((uint64_t)(a)) << 8) | ((uint64_t)(b)))
#define CONCAT44(a,b) ((((uint64_t)(a)) << 32) | ((uint64_t)(b)))
#define CARRY8(a,b) ((((uint64_t)(a)) + ((uint64_t)(b))) < ((uint64_t)(a)))
#define SCARRY8(a,b) ((__int128_t)((int64_t)(a)) + (__int128_t)((int64_t)(b)) != \
                      (__int128_t)((int64_t)(a) + (int64_t)(b)))
#define SUB168(a,b) ((((uint64_t)(a)) >> 8) ^ ((uint64_t)(b)))
#define LZCOUNT(a) ((unsigned)__builtin_clzll((uint64_t)(a)))

/* Supervisor-call + debug intrinsics. */
extern uint64_t sk_break(uintptr_t a, ...);      /* SoftwareBreakpoint */
extern void sk_lo_release(void);                 /* LORelease */

/* ---- Swift runtime helpers shared with the other SK slices ----
 * Each carries the Ghidra FUN_/thunk address in the comment. */
/* FUN_0036b118 */ extern void sk_swift_release(uint64_t obj);
/* FUN_003a25d4 */ extern void sk_swift_release_masked(uint64_t obj);
/* FUN_0036b270 */ extern uint64_t sk_swift_retain(uint64_t obj);
/* FUN_0036a940 */ extern uint64_t sk_array_alloc(uint64_t key, uint64_t bytes, uint64_t tag);
/* FUN_0036a9a0 */ extern uint64_t sk_record_alloc(uint64_t key, uint64_t *out);
/* FUN_0036b6ac */ extern void sk_swift_barrier(void);
/* FUN_0036b588 */ extern void sk_record_ref(uint64_t obj);
/* thunk_FUN_002acbb8 */ extern void sk_str_append();
/* thunk_FUN_002298d4 */ extern void sk_lock_select(uint64_t n);
/* FUN_001a84f4 */ extern void sk_scope_enter();
/* FUN_001a8564 */ extern uint64_t sk_scope_exit(void);
/* FUN_00117d14 */ extern void sk_memmove(uint64_t dst, uint64_t src, uint64_t n);
/* FUN_001a1564 */ extern void sk_vec_push();
/* FUN_001a0774 */ extern void sk_vec_reserve();
/* FUN_0001a1c8 */ extern uint64_t sk_identity_hash();
/* FUN_0001c294 */ extern uint64_t sk_key_hasheq(uint64_t a, uint64_t b);
/* FUN_0001c2a4 */ extern void sk_key_eq(uint64_t a, uint64_t b);
/* FUN_00002534 */ extern uint64_t sk_string_cache(uint64_t a, uint64_t b);
/* FUN_0006a4c0 */ extern void sk_vec_prep(uint64_t vec, uint64_t val);
/* FUN_001f0130 */ extern uint64_t sk_class_vt(uint64_t a, uint64_t b, uint64_t c, uint64_t d);
/* FUN_00157308 */ extern uint64_t sk_int_udiv(uint64_t a);
/* FUN_00055a24 */ extern uint64_t sk_int_zero(void);
/* FUN_001bc440 */ extern sk_u128_t sk_pair_pack(uint64_t a, uint64_t b, uint64_t c, uint64_t d);
/* FUN_00258c60 */ extern uint64_t sk_set_insert(uint64_t set, uint64_t n, uint64_t key);
/* FUN_002591b4 */ extern void sk_fatal_ret(uint64_t addr);
/* FUN_002a0cf8 */ extern uint64_t sk_pair_eq(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t e);
/* FUN_002a4ab4 */ extern void sk_fault_builder(uint64_t n);
/* FUN_00138b08 */ extern uint64_t sk_obj_hasheq(uint64_t a, uint64_t b);
/* FUN_001394c8 */ extern void sk_obj_retain0(uint64_t n);
/* FUN_0035bc70 */ extern void sk_memcpy3(uint64_t a, uint64_t b, uint64_t c);
/* FUN_001b9084 */ extern void sk_ctx_pair(uint64_t *out, uint64_t a, uint64_t b);
/* FUN_0012097c */ extern sk_u128_t sk_ctx_make(uint64_t a);
/* FUN_00229a3c */ extern uint64_t sk_lock_bind_select(int n);
/* FUN_0022995c */ extern void sk_lock_opt(uint64_t n);
/* FUN_00229ebc */ extern uint64_t sk_lock_opt2(uint64_t a, uint64_t b);
/* FUN_001afa84 */ extern void sk_fatal_msg(uint64_t a, int b, int c, uint64_t d, uint64_t e,
                                            uint64_t f, uint64_t g, int h, int i, int j);
/* FUN_00002688 */ extern void sk_obj_done(void);
/* FUN_00002804 */ extern void sk_obj_emit(uint64_t obj);
/* FUN_00002828 */ extern void sk_obj_read(uint64_t *out, uint64_t *slot);
/* FUN_00002834 */ extern void sk_obj_next(void);
/* FUN_00027724 */ extern uint64_t sk_vt_lookup(uint64_t key);
/* FUN_0006ff84 */ extern void sk_nop2(uint64_t a, uint64_t b);
/* FUN_00077604 */ extern void sk_nop3(void);
/* FUN_0036a20c */ extern uint64_t sk_array_meta(void);
/* FUN_0036a1a0 */ extern uint64_t sk_array_meta2(void);
/* FUN_00077088 */ extern uint64_t sk_vt_77088(uint64_t a);
/* FUN_000770b8 */ extern uint64_t sk_vt_770b8(void);
/* FUN_00077118 */ extern uint64_t sk_vt_77118(uint64_t a);
/* FUN_00077148 */ extern void sk_vt_77148(uint64_t a);
/* FUN_00077178 */ extern void sk_vt_77178(void);
/* FUN_000778d4 */ extern void sk_ret_trap(void);
/* FUN_00077934 */ extern uint64_t sk_get_field(void);
/* FUN_00077960 */ extern uint64_t sk_get_field2(void);
/* FUN_0007780c */ extern uint64_t sk_empty_vec(void);
/* FUN_000778fc */ extern void sk_str_tbl(void);
/* FUN_00076fc0 */ extern void sk_const_store(void);
/* FUN_000778a0 */ extern uint64_t sk_const_677830(void);
/* FUN_00077894 */ extern void sk_scope_ctx2(void);
/* FUN_00077708 */ extern void sk_done3(void);
/* FUN_00077870 */ extern void sk_scope_ctx(void);
/* FUN_00077848 */ extern void sk_scope_ctx3(void);
/* FUN_00077718 */ extern void sk_release_and_zero(void);
/* FUN_00077570 */ extern void sk_ret0(void);
/* FUN_00077560 */ extern void sk_ret0b(void);
/* FUN_00077550 */ extern void sk_ret0c(void);
/* FUN_0007752c */ extern uint64_t sk_ret0d(void);
/* FUN_00077580 */ extern uint64_t sk_ptr_plus(void);
/* FUN_00077624 */ extern void sk_check_ovf(void);
/* FUN_000776d8 */ extern void sk_chk0(void);
/* FUN_000776cc */ extern void sk_chk1(void);
/* FUN_0007764c */ extern void sk_meta(void);
/* FUN_000776f8 */ extern void sk_alloc_meta(void);
/* FUN_00077630 */ extern void sk_round(void);
/* FUN_0007766c */ extern void sk_store_size(uint64_t n);
/* FUN_000775dc */ extern void sk_store_size2(uint64_t n);
/* FUN_00077540 */ extern void sk_memmove5(uint64_t a);
/* FUN_0007791c */ extern void sk_alloc_bytes(uint64_t n, uint64_t a);
/* FUN_00074a28 */ extern void sk_copy4(uint64_t a, uint64_t b, uint64_t c, uint64_t d);
/* FUN_000758d8 */ extern void sk_copy5(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t e);
/* FUN_000750bc */ extern void sk_copy8(void);
/* FUN_00074a98 */ extern void sk_copy16(void);
/* FUN_00075c50 */ extern void sk_copy24(void);
/* FUN_00074b08 */ extern void sk_copy32(void);
/* FUN_00075b2c */ extern void sk_copy40(void);
/* FUN_00074b78 */ extern void sk_copy48(void);
/* FUN_00075784 */ extern void sk_copy56(void);
/* FUN_00074c14 */ extern void sk_copy64(void);
/* FUN_00074cb8 */ extern void sk_copy72(void);
/* FUN_00074d54 */ extern void sk_copy80(void);
/* FUN_00074dc8 */ extern void sk_copy88(void);
/* FUN_00074e34 */ extern void sk_copy96(void);
/* FUN_00074f28 */ extern void sk_copy104(void);
/* FUN_000751b4 */ extern void sk_copy112(void);
/* FUN_00075018 */ extern void sk_copy120(void);
/* FUN_00069770 */ extern void sk_vec_copy16(void);
/* FUN_00069970 */ extern void sk_vec_memmove16(void);
/* FUN_000699a4 */ extern void sk_vec_memmove32(void);
/* FUN_000697e4 */ extern void sk_vec_copy32(void);
/* FUN_000721b0 */ extern void sk_move8(void);
/* FUN_00072150 */ extern void sk_move16(void);
/* FUN_000723c0 */ extern void sk_move24(void);
/* FUN_0007201c */ extern void sk_move4(void);
/* FUN_00072044 */ extern void sk_move16b(void);
/* FUN_0007206c */ extern void sk_move40(void);
/* FUN_00072358 */ extern void sk_move24b(void);
/* FUN_000720a8 */ extern void sk_move1(void);
/* FUN_00072178 */ extern void sk_move80(void);
/* FUN_00072114 */ extern void sk_move64(void);
/* FUN_00071fe4 */ extern void sk_move4m(void);
/* FUN_000721d8 */ extern void sk_move8m(void);
/* FUN_0007220c */ extern void sk_move24m(void);
/* FUN_00072270 */ extern void sk_move56(void);
/* FUN_000722b0 */ extern void sk_move56b(void);
/* FUN_00072320 */ extern void sk_move72(void);
/* FUN_000723f4 */ extern void sk_move48(void);
/* FUN_00072b44 */ static void sk_set_byte_skip(char c, uint64_t idx);

/* Fixed-string / format globals. */
#define STR_FATAL_ERROR      ((uint64_t)0x5accd0)   /* "Fatal error" */
#define STR_LAUNCHER_ACCT    ((uint64_t)0x5bfc00)   /* "InternalExclaveLauncher Accounti..." */
#define DAT_005bfc10         ((uint64_t)0x5bfc10)
#define DAT_0067b200         ((uint64_t)0x67b200)
#define DAT_00657778         ((uint64_t)0x657778)   /* empty-vector sentinel */
#define DAT_00657788         ((uint64_t)0x657788)
#define DAT_00671800         ((uint64_t)0x671800)
#define DAT_0064e030         ((uint64_t)0x64e030)
#define DAT_0064e038         ((uint64_t)0x64e038)
#define DAT_0064c040         ((uint64_t)0x64c040)
#define DAT_0064e108         ((uint64_t)0x64e108)
#define DAT_0064e5b8         ((uint64_t)0x64e5b8)
#define DAT_0064e110         ((uint64_t)0x64e110)
#define DAT_0064e118         ((uint64_t)0x64e118)
#define DAT_0064e630         ((uint64_t)0x64e630)
#define DAT_0064e638         ((uint64_t)0x64e638)
#define DAT_0064e640         ((uint64_t)0x64e640)
#define DAT_0064e648         ((uint64_t)0x64e648)
#define DAT_0064e658         ((uint64_t)0x64e658)
#define DAT_0064e660         ((uint64_t)0x64e660)
#define DAT_0064e670         ((uint64_t)0x64e670)
#define DAT_0064e678         ((uint64_t)0x64e678)
#define DAT_0064e6a8         ((uint64_t)0x64e6a8)
#define DAT_0064e6b8         ((uint64_t)0x64e6b8)
#define DAT_0064e6d8         ((uint64_t)0x64e6d8)
#define DAT_0064e738         ((uint64_t)0x64e738)
#define DAT_0064e758         ((uint64_t)0x64e758)
#define DAT_0064e7a8         ((uint64_t)0x64e7a8)
#define DAT_0064e7b8         ((uint64_t)0x64e7b8)
#define DAT_0064e7f8         ((uint64_t)0x64e7f8)
#define DAT_0064e830         ((uint64_t)0x64e830)
#define DAT_0064e848         ((uint64_t)0x64e848)
#define DAT_0064e860         ((uint64_t)0x64e860)
#define DAT_0064e868         ((uint64_t)0x64e868)
#define DAT_0064e870         ((uint64_t)0x64e870)
#define DAT_0064e888         ((uint64_t)0x64e888)
#define DAT_0064e890         ((uint64_t)0x64e890)
#define DAT_0064e898         ((uint64_t)0x64e898)
#define DAT_0064e8b0         ((uint64_t)0x64e8b0)
#define DAT_0064e8c0         ((uint64_t)0x64e8c0)
#define DAT_0064e8d0         ((uint64_t)0x64e8d0)
#define DAT_0064e8d8         ((uint64_t)0x64e8d8)
#define DAT_0064e8e0         ((uint64_t)0x64e8e0)
#define DAT_0064e8f0         ((uint64_t)0x64e8f0)
#define DAT_004bbf40         ((uint64_t)0x4bbf40)
#define DAT_004be900         ((uint64_t)0x4be900)
#define DAT_004be910         ((uint64_t)0x4be910)
#define DAT_004bedf0         ((uint64_t)0x4bedf0)
#define DAT_004c03b0         ((uint64_t)0x4c03b0)
#define DAT_004c0480         ((uint64_t)0x4c0480)
#define DAT_004c0490         ((uint64_t)0x4c0490)
#define DAT_004c04a0         ((uint64_t)0x4c04a0)
#define DAT_004c04a8         ((uint64_t)0x4c04a8)
#define DAT_004c04b0         ((uint64_t)0x4c04b0)
#define DAT_004c04b8         ((uint64_t)0x4c04b8)
#define DAT_004c04c0         ((uint64_t)0x4c04c0)
#define DAT_004c04d0         ((uint64_t)0x4c04d0)
#define DAT_004c04f0         ((uint64_t)0x4c04f0)
#define DAT_004c0508         ((uint64_t)0x4c0508)
#define DAT_004c0588         ((uint64_t)0x4c0588)
#define DAT_004c05b0         ((uint64_t)0x4c05b0)
#define DAT_004c0600         ((uint64_t)0x4c0600)
#define DAT_004c0650         ((uint64_t)0x4c0650)
#define DAT_004c06a0         ((uint64_t)0x4c06a0)
#define DAT_004c06b8         ((uint64_t)0x4c06b8)
#define DAT_004c06c0         ((uint64_t)0x4c06c0)
#define DAT_004c06c8         ((uint64_t)0x4c06c8)
#define DAT_004c06e0         ((uint64_t)0x4c06e0)
#define DAT_004c06f0         ((uint64_t)0x4c06f0)
#define DAT_004c0708         ((uint64_t)0x4c0708)
#define DAT_004c0718         ((uint64_t)0x4c0718)
#define DAT_004c0728         ((uint64_t)0x4c0728)
#define DAT_004c0730         ((uint64_t)0x4c0730)
#define DAT_004c0738         ((uint64_t)0x4c0738)
#define DAT_004c0750         ((uint64_t)0x4c0750)
#define DAT_004c2600         ((uint64_t)0x4c2600)
#define DAT_004c25d0         ((uint64_t)0x4c25d0)
#define DAT_004c2e90         ((uint64_t)0x4c2e90)
#define DAT_004c3ec0         ((uint64_t)0x4c3ec0)
#define DAT_004e68b0         ((uint64_t)0x4e68b0)
#define DAT_004f1980         ((uint64_t)0x4f1980)
#define DAT_004baeb0         ((uint64_t)0x4baeb0)
#define DAT_004baeb8         ((uint64_t)0x4baeb8)

/*============================================================================
 * Forward declarations within this slice
 *==========================================================================*/
static uint64_t sk_emit_field(uint64_t name_key, uint64_t value, uint64_t tag);
static void sk_scope_emit_pair(uint64_t a, uint64_t b, char tag);
static void sk_scope_emit_ctx(uint64_t a, char tag);
static void sk_scope_emit_ctx_r(void);
static void sk_field_count(void);
static void sk_vec_push_elem(uint64_t obj, uint64_t val);
static void sk_vec_push_elem2(uint64_t obj, uint64_t val);
static void sk_pair_copy_hash(uint64_t *out, uint64_t *in);
static void sk_hash2_copy(uint64_t *out, uint64_t *in);
static void sk_field_emit_big(uint64_t a, uint64_t b);
static void sk_observer_wrap(uint64_t a, uint64_t b, uint64_t c);
static void sk_fatal_launcher(void);
static sk_u128_t sk_set_next(void);
static void sk_set_iter_init(long *out, long set, long cb, long ctx);
static void sk_do_emit(void);
static void sk_emit_one(uint64_t a);
static void sk_emit_two(void);
static void sk_emit_three(void);
static void sk_emit_four(void);
static void sk_emit_five(void);
static void sk_emit_six(void);
static void sk_emit_seven(void);
static void sk_emit_eight(void);
static void sk_emit_nine(void);
static void sk_emit_ten(void);
static sk_u128_t sk_set_find(uint64_t key, char tag, uint64_t idx);
static void sk_set_skip(char c, uint64_t idx);
static void sk_set_skip_pair(long a, long b, uint64_t idx);
static sk_u128_t sk_set_find_int(int key, uint64_t idx);
static sk_u128_t sk_set_find_word(long key, uint64_t idx);
static sk_u128_t sk_set_find_obj(uint64_t key, uint64_t idx);
static void sk_apply_first(uint64_t *out, uint64_t a, uint64_t b, uint64_t tag);
static void sk_reserve_grow_u8(uint64_t n);
static void sk_reserve_grow_word(uint64_t n);
static void sk_reserve_grow_byte(uint64_t n);
static void sk_reserve_grow_ptr(uint64_t n);
static uint64_t sk_vec_alloc(uint64_t count, uint64_t cap, uint64_t unit,
                             uint64_t key, uint64_t dat);
static void sk_move_elems(uint64_t src, int64_t n, uint64_t dst, uint64_t unit);
static uint64_t sk_reserve(uint64_t unique, uint64_t count, uint64_t grow, uint64_t vec,
                           uint64_t key, uint64_t dat);
static uint64_t sk_reserve_flex(uint64_t unique, uint64_t count, uint64_t grow, uint64_t vec,
                                sk_code_t alloc, sk_code_t copyfn, sk_code_t movefn);
static sk_u128_t sk_reserve_u8(uint64_t a, uint64_t b, uint64_t c);
static sk_u128_t sk_reserve_word(uint64_t a, uint64_t b, uint64_t c);
static sk_u128_t sk_reserve_ptr(uint64_t a, uint64_t b, uint64_t c);
static sk_u128_t sk_reserve_u16(uint64_t a, uint64_t b, uint64_t c);
static sk_u128_t sk_reserve_u32(uint64_t a, uint64_t b, uint64_t c);
static sk_u128_t sk_reserve_u64(uint64_t a, uint64_t b, uint64_t c);
static void sk_set_probe2(unsigned long flag);
static void sk_set_first_probe(uint64_t a, uint64_t b, uint64_t c);
static void sk_iter_probe(long *out, long set, long a, long b);

/*============================================================================

/* ---- out-of-region helpers ---- */
/* Out-of-region kernel/Swift helpers referenced by this slice. */
/* Ghidra FUN_00002534 */ extern uint64_t sk_ext_00002534();
/* Ghidra FUN_00002688 */ extern uint64_t sk_ext_00002688();
/* Ghidra FUN_00002804 */ extern uint64_t sk_ext_00002804();
/* Ghidra FUN_00002828 */ extern uint64_t sk_ext_00002828();
/* Ghidra FUN_00002834 */ extern uint64_t sk_ext_00002834();
/* Ghidra FUN_0001a1c8 */ extern uint64_t sk_ext_0001a1c8();
/* Ghidra FUN_0001c294 */ extern uint64_t sk_ext_0001c294();
/* Ghidra FUN_0001c2a4 */ extern uint64_t sk_ext_0001c2a4();
/* Ghidra FUN_00027724 */ extern uint64_t sk_ext_00027724();
/* Ghidra FUN_00055a24 */ extern uint64_t sk_ext_00055a24();
/* Ghidra FUN_00069770 */ extern uint64_t sk_ext_00069770();
/* Ghidra FUN_000697e4 */ extern uint64_t sk_ext_000697e4();
/* Ghidra FUN_00069970 */ extern uint64_t sk_ext_00069970();
/* Ghidra FUN_000699a4 */ extern uint64_t sk_ext_000699a4();
/* Ghidra FUN_0006a374 */ extern uint64_t sk_ext_0006a374();
/* Ghidra FUN_0006a4c0 */ extern uint64_t sk_ext_0006a4c0();
/* Ghidra FUN_0006fdbc */ extern uint64_t sk_ext_0006fdbc();
/* Ghidra FUN_0006ff84 */ extern uint64_t sk_ext_0006ff84();
/* Ghidra FUN_00074a28 */ extern uint64_t sk_ext_00074a28();
/* Ghidra FUN_00074a98 */ extern uint64_t sk_ext_00074a98();
/* Ghidra FUN_00074b08 */ extern uint64_t sk_ext_00074b08();
/* Ghidra FUN_00074b78 */ extern uint64_t sk_ext_00074b78();
/* Ghidra FUN_00074c14 */ extern uint64_t sk_ext_00074c14();
/* Ghidra FUN_00074cb8 */ extern uint64_t sk_ext_00074cb8();
/* Ghidra FUN_00074d54 */ extern uint64_t sk_ext_00074d54();
/* Ghidra FUN_00074dc8 */ extern uint64_t sk_ext_00074dc8();
/* Ghidra FUN_00074e34 */ extern uint64_t sk_ext_00074e34();
/* Ghidra FUN_00074f28 */ extern uint64_t sk_ext_00074f28();
/* Ghidra FUN_00074fa4 */ extern uint64_t sk_ext_00074fa4();
/* Ghidra FUN_00075018 */ extern uint64_t sk_ext_00075018();
/* Ghidra FUN_000750bc */ extern uint64_t sk_ext_000750bc();
/* Ghidra FUN_000751b4 */ extern uint64_t sk_ext_000751b4();
/* Ghidra FUN_00075784 */ extern uint64_t sk_ext_00075784();
/* Ghidra FUN_000758d8 */ extern uint64_t sk_ext_000758d8();
/* Ghidra FUN_00075b2c */ extern uint64_t sk_ext_00075b2c();
/* Ghidra FUN_00075c50 */ extern uint64_t sk_ext_00075c50();
/* Ghidra FUN_00075cb4 */ extern uint64_t sk_ext_00075cb4();
/* Ghidra FUN_00076ac8 */ extern uint64_t sk_ext_00076ac8();
/* Ghidra FUN_00076d08 */ extern uint64_t sk_ext_00076d08();
/* Ghidra FUN_00076f74 */ extern uint64_t sk_ext_00076f74();
/* Ghidra FUN_00076fc0 */ extern uint64_t sk_ext_00076fc0();
/* Ghidra FUN_00077024 */ extern uint64_t sk_ext_00077024();
/* Ghidra FUN_00077070 */ extern uint64_t sk_ext_00077070();
/* Ghidra FUN_00077088 */ extern uint64_t sk_ext_00077088();
/* Ghidra FUN_000770b8 */ extern uint64_t sk_ext_000770b8();
/* Ghidra FUN_000770e8 */ extern uint64_t sk_ext_000770e8();
/* Ghidra FUN_00077118 */ extern uint64_t sk_ext_00077118();
/* Ghidra FUN_00077148 */ extern uint64_t sk_ext_00077148();
/* Ghidra FUN_00077178 */ extern uint64_t sk_ext_00077178();
/* Ghidra FUN_0007752c */ extern uint64_t sk_ext_0007752c();
/* Ghidra FUN_00077540 */ extern uint64_t sk_ext_00077540();
/* Ghidra FUN_00077550 */ extern uint64_t sk_ext_00077550();
/* Ghidra FUN_00077560 */ extern uint64_t sk_ext_00077560();
/* Ghidra FUN_00077570 */ extern uint64_t sk_ext_00077570();
/* Ghidra FUN_00077580 */ extern uint64_t sk_ext_00077580();
/* Ghidra FUN_00077590 */ extern uint64_t sk_ext_00077590();
/* Ghidra FUN_000775dc */ extern uint64_t sk_ext_000775dc();
/* Ghidra FUN_00077604 */ extern uint64_t sk_ext_00077604();
/* Ghidra FUN_00077624 */ extern uint64_t sk_ext_00077624();
/* Ghidra FUN_00077630 */ extern uint64_t sk_ext_00077630();
/* Ghidra FUN_0007764c */ extern uint64_t sk_ext_0007764c();
/* Ghidra FUN_0007766c */ extern uint64_t sk_ext_0007766c();
/* Ghidra FUN_000776cc */ extern uint64_t sk_ext_000776cc();
/* Ghidra FUN_000776d8 */ extern uint64_t sk_ext_000776d8();
/* Ghidra FUN_000776f8 */ extern uint64_t sk_ext_000776f8();
/* Ghidra FUN_00077708 */ extern uint64_t sk_ext_00077708();
/* Ghidra FUN_00077718 */ extern uint64_t sk_ext_00077718();
/* Ghidra FUN_00077724 */ extern uint64_t sk_ext_00077724();
/* Ghidra FUN_00077744 */ extern uint64_t sk_ext_00077744();
/* Ghidra FUN_000777d4 */ extern uint64_t sk_ext_000777d4();
/* Ghidra FUN_0007780c */ extern uint64_t sk_ext_0007780c();
/* Ghidra FUN_00077848 */ extern uint64_t sk_ext_00077848();
/* Ghidra FUN_00077870 */ extern uint64_t sk_ext_00077870();
/* Ghidra FUN_00077894 */ extern uint64_t sk_ext_00077894();
/* Ghidra FUN_000778a0 */ extern uint64_t sk_ext_000778a0();
/* Ghidra FUN_000778d4 */ extern uint64_t sk_ext_000778d4();
/* Ghidra FUN_000778fc */ extern uint64_t sk_ext_000778fc();
/* Ghidra FUN_0007791c */ extern uint64_t sk_ext_0007791c();
/* Ghidra FUN_00077934 */ extern uint64_t sk_ext_00077934();
/* Ghidra FUN_00077960 */ extern uint64_t sk_ext_00077960();
/* Ghidra FUN_00117d14 */ extern uint64_t sk_ext_00117d14();
/* Ghidra FUN_0012097c */ extern uint64_t sk_ext_0012097c();
/* Ghidra FUN_001394c8 */ extern uint64_t sk_ext_001394c8();
/* Ghidra FUN_00157308 */ extern uint64_t sk_ext_00157308();
/* Ghidra FUN_001a0774 */ extern uint64_t sk_ext_001a0774();
/* Ghidra FUN_001a1564 */ extern uint64_t sk_ext_001a1564();
/* Ghidra FUN_001a84f4 */ extern uint64_t sk_ext_001a84f4();
/* Ghidra FUN_001a8564 */ extern uint64_t sk_ext_001a8564();
/* Ghidra FUN_001afa84 */ extern uint64_t sk_ext_001afa84();
/* Ghidra FUN_001b9084 */ extern uint64_t sk_ext_001b9084();
/* Ghidra FUN_001bc440 */ extern uint64_t sk_ext_001bc440();
/* Ghidra FUN_001f0130 */ extern uint64_t sk_ext_001f0130();
/* Ghidra FUN_0022995c */ extern uint64_t sk_ext_0022995c();
/* Ghidra FUN_00229a3c */ extern uint64_t sk_ext_00229a3c();
/* Ghidra FUN_00258c60 */ extern uint64_t sk_ext_00258c60();
/* Ghidra FUN_002591b4 */ extern uint64_t sk_ext_002591b4();
/* Ghidra FUN_002a0cf8 */ extern uint64_t sk_ext_002a0cf8();
/* Ghidra FUN_002a4ab4 */ extern uint64_t sk_ext_002a4ab4();
/* Ghidra FUN_0035bc70 */ extern uint64_t sk_ext_0035bc70();
/* Ghidra FUN_0036a1a0 */ extern uint64_t sk_ext_0036a1a0();
/* Ghidra FUN_0036a20c */ extern uint64_t sk_ext_0036a20c();
/* Ghidra FUN_0036a940 */ extern uint64_t sk_ext_0036a940();
/* Ghidra FUN_0036a9a0 */ extern uint64_t sk_ext_0036a9a0();
/* Ghidra FUN_0036b118 */ extern uint64_t sk_ext_0036b118();
/* Ghidra FUN_0036b270 */ extern uint64_t sk_ext_0036b270();

/* Ghidra FUN_0036a1a0 */ extern void sk_reserve_slot(uint64_t p, uint64_t tmp, uint64_t sz, uint64_t fl);
/* Ghidra FUN_0036a20c */ extern void sk_commit_slot(uint64_t tmp);
/* Ghidra FUN_00075cb4 */ extern void sk_counted_insert(uint64_t a, uint64_t b, uint64_t c);

/* ---- forward declarations within this slice ---- */
static void sk_vec_counted_insert(uint64_t delta, uint64_t key, uint64_t tag);
static void sk_vec_retain_push(uint64_t obj);
static void sk_vec_push_elem(uint64_t obj, uint64_t val);
static void sk_scope_emit_pair(uint64_t a, uint64_t b, char tag);
static sk_u128_t sk_set_find_pair(long a, long b, long c, long d, uint64_t idx);
static void sk_emit_run(void);
static void sk_fatal_launcher(void);
static sk_u128_t sk_set_next(void);
static void sk_set_iter_init(long *out, long set, long cb, long ctx);

/*============================================================================
 * 0x70098 - 0x70960 : field emitters, vector push, set builder
 *==========================================================================*/

/* FUN_00070098 @ 0x70098  (est. sk_emit_field)
 * Emit an accounting {name, value} field: resolve the name via the vt lookup
 * (0x671df8) and const table, append a "name" marker, then dispatch on the
 * `tag` byte: tag 0 -> unsigned-divide value and reject negatives (fatal
 * 0x701c4); tag 1 -> unchanged; else value=1.  Then multiply value*value with
 * a high-half overflow trap (fatal 0x701c0) and pass the product to sk_nop2
 * before finalizing with a "value" marker.  Returns the {const,key} pair low
 * word.  Confidence: medium (Swift format-string machinery). */
static uint64_t sk_emit_field(uint64_t name_key, uint64_t value, uint64_t tag)
{
    sk_u128_t field;
    uint64_t u;

    sk_vt_lookup(0x671df8);
    u = sk_const_677830();
    field = sk_pair_pack(u, 0x671df8, 0, 0);
    sk_str_append(0x20, 0xe100000000000000);
    sk_nop2(value, tag);
    sk_str_append();
    sk_swift_release_masked(0);
    sk_str_append(0x2820, 0xe200000000000000);
    if ((tag & 0xff) == 0) {
        value = sk_int_udiv(value);
        if ((int64_t)value < 0) {
            sk_break(1, 0x701c4); /* fatal: negative */
        }
        value = sk_int_zero();
    } else {
        if (((uint8_t)tag & 0xff) != 1) {
            value = 1;
        }
    }
    /* auVar1._8_8_=0, auVar1._0_8_=value; auVar2=value; SUB168(value*value,0) */
    if (((value * value) >> 8) == 0) {
        sk_nop2(value * value, ((uint8_t)tag & 0xff) != 1);
        sk_str_append();
        sk_swift_release_masked(0);
        sk_str_append(0x29, 0xe100000000000000);
        return field.lo;
    }
    sk_break(1, 0x701c0); /* fatal: overflow */
    return 0;
}

/* FUN_0007021c @ 0x7021c  (est. sk_scope_emit_pair)
 * Scope-bound emitter: tag==0 -> lock-select 0 then emit key-pair {a,b};
 * tag==1 -> lock-select 1; else set b=2 then lock-select(b).
 * Confidence: medium. */
static void sk_scope_emit_pair(uint64_t a, uint64_t b, char tag)
{
    if (tag != '\0') {
        if (tag == '\x01') {
            sk_lock_select(1);
        } else {
            b = 2;
        }
        sk_lock_select(b);
        return;
    }
    sk_lock_select(0);
    sk_key_eq(a, b);
}

/* FUN_00070288 @ 0x70288  (est. sk_scope_emit_ctx)
 * Scope-entered variant of sk_scope_emit_pair: enter a scope frame, dispatch
 * on tag to lock-select + optional key-eq, then exit the scope.
 * Confidence: medium. */
static void sk_scope_emit_ctx(uint64_t a, char tag)
{
    uint64_t frame[9];
    sk_scope_enter(frame, 0);
    if (tag == '\0') {
        sk_lock_select(0);
        sk_key_eq((uint64_t)frame, a);
    } else {
        if (tag == '\x01') {
            sk_lock_select(1);
        } else {
            a = 2;
        }
        sk_lock_select(a);
    }
    sk_scope_exit();
}

/* FUN_0007032c @ 0x7032c  (est. sk_scope_emit_ctx_r)
 * Scope-entered emitter that pulls {value, tag} from the record at x20, then
 * enters/exits a scope around sk_scope_emit_pair(value, tag).
 * Confidence: medium. */
static void sk_scope_emit_ctx_r(void)
{
    uint64_t value = *(uint64_t *)0;
    char tag = *(char *)((uint64_t)0 + 8);
    uint64_t frame[9];
    sk_scope_enter(frame);
    sk_scope_emit_pair((uint64_t)frame, value, tag);
    sk_scope_exit();
}

/* FUN_00070390 @ 0x70390  (est. sk_field_count)
 * Wrap sk_ret_pack(1,0,2) then sk_scope_emit_pair(1,0,2): a counting emitter
 * used by the observer/accounting path.  Confidence: medium. */
static void sk_field_count(void)
{
    sk_vec_counted_insert(1, 0, 2);
    sk_scope_emit_pair(1, 0, 2);
}

/* FUN_00070594 @ 0x70594  (est. sk_vec_push_elem)
 * Growable-array push of one 8-byte element: reserve capacity when count
 * reaches half capacity, then store val at vec[count] and bump count.
 * Confidence: medium (FUN_001a1564/1a0774 vector reserve/push). */
static void sk_vec_push_elem(uint64_t obj, uint64_t val)
{
    uint64_t count;
    uint64_t *base = (uint64_t *)*(uint64_t *)0;

    sk_vec_push(obj, val);
    count = base[2];
    if (base[3] >> 1 <= count) {
        sk_vec_reserve(base[3] > 1, count + 1, 1);
        base = (uint64_t *)*(uint64_t *)0;
    }
    base[2] = count + 1;
    base[count * 2 + 4] = val;
}

/* FUN_000705f8 @ 0x705f8  (est. sk_vec_push_elem2) */
static void sk_vec_push_elem2(uint64_t obj, uint64_t val)
{
    sk_vec_push_elem(obj, val);
}

/* FUN_0007063c @ 0x7063c  (est. sk_vec_pack_init)
 * Initialize a two-word vector record: set obj[2]=vt, obj[3]=empty sentinel.
 * Confidence: medium (FUN_001f0130 vt lookup). */
static void sk_vec_pack_init(void)
{
    uint64_t u = sk_class_vt(0, 0, 0, 0);
    *(uint64_t *)((uint64_t)0 + 0x10) = u;
    *(uint64_t *)((uint64_t)0 + 0x18) = DAT_00657778;
}

/* FUN_00070674 @ 0x70674  (est. sk_vec_counted_insert)
 * Insert `delta` into the counted array at x20[2] keyed by {key,tag}: look up
 * the pair via sk_set_find (0x724cc); if absent read the current count and
 * add `delta` (fatal 0x70754 on overflow), else 0.  Then reserve a 0x21-byte
 * slot and call sk_counted_insert(total, key, tag).  Confidence: medium. */
static void sk_vec_counted_insert(uint64_t delta, uint64_t key, uint64_t tag)
{
    uint64_t *vec = (uint64_t *)*(uint64_t *)0;
    uint64_t base, idx, total;
    sk_u128_t res;
    uint64_t tmp[3];

    sk_reserve_slot((uint64_t)vec + 0x10, (uint64_t)tmp, 0x20, 0);
    base = vec[2];
    if (*(uint64_t *)(base + 0x10) == 0) {
        total = 0;
    } else {
        sk_swift_retain(base);
        res = sk_set_find(key, (char)tag, 0);
        if ((res.hi & 1) == 0) {
            total = 0;
        } else {
            total = *(uint64_t *)(*(uint64_t *)(base + 0x38) + res.lo * 8);
        }
        sk_swift_release_masked(base);
    }
    sk_commit_slot((uint64_t)tmp);
    if (!CARRY8(total, delta)) {
        sk_reserve_slot((uint64_t)vec + 0x10, (uint64_t)tmp, 0x21, 0);
        sk_counted_insert(total + delta, key, tag);
        sk_commit_slot((uint64_t)tmp);
        return;
    }
    sk_break(1, 0x70754); /* fatal: overflow */
}

/* FUN_00070754 @ 0x70754  (est. sk_vec_retain_push)
 * Reserve a 0x21-byte slot in the second vector (x20+0x18), retain obj, push
 * one element, then commit the slot.  Confidence: medium. */
static void sk_vec_retain_push(uint64_t obj)
{
    uint64_t *vec = (uint64_t *)*(uint64_t *)0;
    uint64_t tmp[3];
    sk_reserve_slot((uint64_t)vec + 0x18, (uint64_t)tmp, 0x21, 0);
    sk_swift_retain(obj);
    sk_vec_push_elem(obj, 0);
    sk_commit_slot((uint64_t)tmp);
}

/* FUN_000707a8 @ 0x707a8  (est. sk_vec_pair_make)
 * Build a two-vector {names, values} pair iterator from the container at x20:
 * empty-vec vt, then if flag x21 set wrap the first vector through
 * FUN_00076d08/vt-callback; if flag x23 set iterate the second vector and
 * build an index (fatal 0x70920 on overrun).  Confidence: medium. */
static void sk_vec_pair_make(uint64_t *out, uint64_t a, uint64_t b)
{
    (void)out; (void)a; (void)b;
    sk_empty_vec();
    sk_vec_pack_init();
    sk_class_vt(0, 0, 0, 0);
}
/* Ghidra FUN_0036b588 */ extern uint64_t sk_ext_0036b588();
/* Ghidra FUN_0036b6ac */ extern uint64_t sk_ext_0036b6ac();
/* Ghidra FUN_003a25d4 */ extern uint64_t sk_ext_003a25d4();
/* Ghidra FUN_003a261c */ extern uint64_t sk_ext_003a261c();
/* Ghidra thunk_FUN_000126e8 */ extern uint64_t sk_ext_000126e8();
/* Ghidra thunk_FUN_00138b08 */ extern uint64_t sk_ext_00138b08();
/* Ghidra thunk_FUN_002298d4 */ extern uint64_t sk_ext_002298d4();
/* Ghidra thunk_FUN_00229ebc */ extern uint64_t sk_ext_00229ebc();
/* Ghidra thunk_FUN_002acbb8 */ extern uint64_t sk_ext_002acbb8();
/* Ghidra thunk_FUN_0036b270 */ extern uint64_t sk_ext_0036b270();

/* Ghidra FUN_0036a1a0 */ extern void sk_reserve_slot(uint64_t p, uint64_t tmp, uint64_t sz, uint64_t fl);
/* Ghidra FUN_0036a20c */ extern void sk_commit_slot(uint64_t tmp);
/* Ghidra FUN_00075cb4 */ extern void sk_counted_insert(uint64_t a, uint64_t b, uint64_t c);

/* FUN_00070920 @ 0x70920  (est. sk_pair_copy_hash)
 * Copy a {hash, tag} pair: out[0]=hash(in[0], in[1]); out[1]=tag; out[2]=in[2].
 * Confidence: high (structural). */
static void sk_pair_copy_hash(uint64_t *out, uint64_t *in)
{
    uint64_t h = sk_identity_hash(in[0], (uint64_t)*(uint8_t *)(in + 1));
    out[0] = h;
    *(uint8_t *)(out + 1) = (uint8_t)h;   /* tag byte */
    out[2] = in[2];
}

/* FUN_00070cc8 @ 0x70cc8  (est. sk_hash2_copy)
 * out[0]=hash(in[0], in[8]); out[8]=tag.  Confidence: high (structural). */
static void sk_hash2_copy(uint64_t *out, uint64_t *in)
{
    uint64_t h = sk_identity_hash(in[0], in[1]);
    *(uint8_t *)out = (uint8_t)h;
    out[1] = h;                            /* tag */
}

/* FUN_00070cfc @ 0x70cfc  (est. sk_hash3_copy) */
static void sk_hash3_copy(uint64_t *out, uint64_t *in)
{
    sk_hash2_copy(out, in);
}

/* FUN_00070de4 @ 0x70de4  (est. sk_children_get)
 * Fetch the children record for a node: build {base, tag} and return the
 * 128-bit {value, flag} result.  Confidence: medium (structural). */
static sk_u128_t sk_children_get(uint64_t a, uint64_t b, uint64_t c)
{
    (void)a; (void)b; (void)c;
    return sk_pair_pack(0, 0, 0, 0);
}

/* FUN_000713dc @ 0x713dc  (est. sk_release_pair)
 * Release the two retained objects of a pair: masked-release obj[1], release
 * obj[2].  Confidence: high (structural). */
static void sk_release_pair(void)
{
    uint64_t *o = (uint64_t *)*(uint64_t *)0;
    sk_swift_release_masked(o[1]);
    sk_swift_release(o[2]);
}

/* FUN_00071404 @ 0x71404  (est. sk_teardown_pair)
 * Release the pair, advance the iterator, then Swift barrier.
 * Confidence: medium. */
static void sk_teardown_pair(void)
{
    sk_release_pair();
    sk_ext_00002834();
    sk_swift_barrier();
}

/* FUN_00071408 @ 0x71408  (est. sk_teardown_pair2) */
static void sk_teardown_pair2(void)
{
    sk_release_pair();
    sk_ext_00002834();
    sk_swift_barrier();
}

/* FUN_00071428 @ 0x71428  (est. sk_hash3_copy_wrap) */
static void sk_hash3_copy_wrap(void)
{
    sk_hash2_copy((uint64_t *)0, (uint64_t *)0);
}

/* FUN_0007144c @ 0x7144c  (est. sk_record_bind)
 * Bind a record: set out[4]=meta, out[5]=ctx, run the vt-init through
 * FUN_00077024, call the class init (*meta-8 + 0x10), store out[0]=key and
 * retain it.  Confidence: medium. */
static void sk_record_bind(uint64_t *out, uint64_t key, int64_t meta, uint64_t ctx)
{
    out[4] = (uint64_t)meta;
    out[5] = ctx;
    sk_ext_00077024((uint64_t)(out + 1));
    (*(sk_code_t)(*(uint64_t *)(meta - 8) + 0x10))();
    out[0] = key;
    sk_swift_retain(key);
}

/* FUN_000714bc @ 0x714bc  (est. sk_record_set_ctx)
 * out[0]=ctx; build out[1..] via FUN_00077070.  Confidence: medium. */
static void sk_record_set_ctx(uint64_t *out, uint64_t a, uint64_t ctx)
{
    sk_ext_00077070(a, (uint64_t)(out + 1));
    out[0] = ctx;
}

/* FUN_000714f4 @ 0x714f4  (est. sk_invoke_vt3)
 * Fetch {data, vtab} from x20, prep the vector, then invoke the vtable
 * function FUN_00077088(vtab) with (a,b,c,data,vtab); if flag x21 clear call
 * the release-trap.  Returns the call result.  Confidence: medium. */
static uint64_t sk_invoke_vt3(uint64_t a, uint64_t b, uint64_t c)
{
    uint64_t *o = (uint64_t *)*(uint64_t *)0;
    uint64_t data = o[4];
    uint64_t vtab = o[5];
    sk_vec_prep((uint64_t)o + 8, data);
    sk_code_t fn = (sk_code_t)sk_ext_00077088(vtab);
    uint64_t r = fn(a, b, c, data, vtab);
    if (*(uint64_t *)*(uint64_t *)0 == 0) {
        sk_ret_trap();
    }
    return r;
}

/* FUN_00071598 @ 0x71598  (est. sk_invoke_vt0)
 * Fetch {data,vtab} and invoke FUN_00077088() with no args; conditional trap.
 * Confidence: medium. */
static uint64_t sk_invoke_vt0(void)
{
    sk_ext_00077934();
    sk_code_t fn = (sk_code_t)sk_ext_00077088();
    uint64_t r = fn();
    if (*(uint64_t *)*(uint64_t *)0 == 0) {
        sk_ret_trap();
    }
    return r;
}

/* FUN_00071620 @ 0x71620  (est. sk_invoke_vt1)
 * Fetch {data,vtab} and invoke FUN_000770b8(); on clear flag call the counted
 * insert (1,param_2,1).  Confidence: medium. */
static uint64_t sk_invoke_vt1(uint64_t a, uint64_t b)
{
    (void)a;
    sk_ext_00077934();
    sk_code_t fn = (sk_code_t)sk_ext_000770b8();
    uint64_t r = fn();
    if (*(uint64_t *)*(uint64_t *)0 == 0) {
        sk_vec_counted_insert(1, b, 1);
    }
    return r;
}

/* FUN_000716b4 @ 0x716b4  (est. sk_fatal_launcher)
 * Fatal: report "Fatal error" with the InternalExclaveLauncher Accounting
 * context string (0x5bfc00) and the 0x5bfc10 detail; never returns.
 * Confidence: high (string refs). */
static void sk_fatal_launcher(void)
{
    sk_fatal_msg(STR_FATAL_ERROR, 0xb, 2, 0xd000000000000034, 0x80000000005bfc10,
                 STR_LAUNCHER_ACCT, 0x28, 2, 0xec, 0);
}

/* FUN_00071710 @ 0x71710  (est. sk_emit_run)
 * Emit a run record: fetch {data,vtab}, invoke FUN_000770e8, then the
 * iterator-finalize (0x777d4) and return through the tail call.
 * Confidence: medium. */
static void sk_emit_run(void)
{
    sk_ext_00077960();
    sk_ext_000770e8();
    sk_ext_000777d4();
}

/* FUN_0007174c @ 0x7174c  (est. sk_invoke_vt1b)
 * Counted insert (1,0,2), then invoke FUN_00077118(vtab) with (a,data,vtab).
 * Confidence: medium. */
static void sk_invoke_vt1b(uint64_t a)
{
    uint64_t *o = (uint64_t *)*(uint64_t *)0;
    uint64_t data = o[4];
    uint64_t vtab = o[5];
    sk_vec_counted_insert(1, 0, 2);
    sk_vec_prep((uint64_t)o + 8, data);
    sk_code_t fn = (sk_code_t)sk_ext_00077118(vtab);
    fn(a, data, vtab);
}

/* FUN_000717c8 @ 0x717c8  (est. sk_emit_run2)
 * Fetch {data,vtab}, prep vector, invoke FUN_00077148(vtab) and the
 * iterator-finalize.  Confidence: medium. */
static void sk_emit_run2(void)
{
    uint64_t *o = (uint64_t *)*(uint64_t *)0;
    uint64_t vtab = o[5];
    sk_vec_prep((uint64_t)o + 8, o[4]);
    sk_ext_00077148(vtab);
    sk_ext_000777d4();
}

/* FUN_00071814 @ 0x71814  (est. sk_emit_run3)
 * Fetch {data,vtab}, invoke FUN_00077178 and the iterator-finalize.
 * Confidence: medium. */
static void sk_emit_run3(void)
{
    sk_ext_00077960();
    sk_ext_00077178();
    sk_ext_000777d4();
}

/* FUN_00071850 @ 0x71850  (est. sk_thunk_invoke0) */
static void sk_thunk_invoke0(void) { sk_invoke_vt0(); }

/* FUN_00071854 @ 0x71854  (est. sk_thunk_invoke0b) */
static void sk_thunk_invoke0b(void) { sk_invoke_vt0(); }

/* FUN_00071868 @ 0x71868  (est. sk_thunk_invoke3) */
static void sk_thunk_invoke3(void) { sk_invoke_vt3(0, 0, 0); }

/* FUN_0007186c @ 0x7186c  (est. sk_thunk_invoke3b) */
static void sk_thunk_invoke3b(void) { sk_invoke_vt3(0, 0, 0); }

/* FUN_00071880 @ 0x71880  (est. sk_thunk_invoke1) */
static void sk_thunk_invoke1(void) { sk_invoke_vt1(0, 0); }

/* FUN_00071884 @ 0x71884  (est. sk_thunk_invoke1b) */
static void sk_thunk_invoke1b(void) { sk_invoke_vt1(0, 0); }

/* FUN_00071898 @ 0x71898  (est. sk_fatal_launcher_emit)
 * Fatal launcher accounting then emit.  Confidence: medium. */
static void sk_fatal_launcher_emit(void)
{
    sk_fatal_launcher();
    sk_emit_run();
}

/* FUN_0007189c @ 0x7189c  (est. sk_fatal_launcher_emit2) */
static void sk_fatal_launcher_emit2(void)
{
    sk_fatal_launcher();
    sk_emit_run();
}

/* FUN_000718b8 @ 0x718b8  (est. sk_set_next)
 * Advance a set iterator at x20: skip empty bit-words, then decode the next
 * set bit (bit-reverse + LZCOUNT), fetch the {tag,key} slot and value, store
 * the cursor, and invoke the per-element callback stored at x20[5].
 * Returns the {value, flag} pair (flag 0xff at end).  Confidence: medium. */
static sk_u128_t sk_set_next(void)
{
    uint64_t *it = (uint64_t *)*(uint64_t *)0;
    uint64_t word, bitpos, v, slot;
    uint64_t wordidx;
    sk_u128_t out;

    wordidx = it[3];
    v = it[4];
    if (v == 0) {
        do {
            wordidx = wordidx + 1;
            if (SCARRY8(wordidx - 1, 1)) {
                sk_break(1, 0x71988); /* fatal: cursor overflow */
            }
            if ((int64_t)((it[2] + 0x40) >> 6) <= (int64_t)wordidx) {
                out.lo = 0;
                it[3] = wordidx - 1;
                it[4] = 0;
                out.hi = 0xff;               /* end sentinel */
                return out;
            }
            v = *(uint64_t *)(it[1] + wordidx * 8);
            wordidx = wordidx + 1;
        } while (v == 0);
    }
    /* bit-reverse v to find the highest set bit -> element position */
    word = (v & 0xaaaaaaaaaaaaaaaaULL) >> 1 | (v & 0x5555555555555555ULL) << 1;
    word = (word & 0xccccccccccccccccULL) >> 2 | (word & 0x3333333333333333ULL) << 2;
    word = (word & 0xf0f0f0f0f0f0f0f0ULL) >> 4 | (word & 0xf0f0f0f0f0f0f0fULL) << 4;
    word = (word & 0xff00ff00ff00ff00ULL) >> 8 | (word & 0xff00ff00ff00ffULL) << 8;
    word = (word & 0xffff0000ffff0000ULL) >> 16 | (word & 0xffff0000ffffULL) << 16;
    bitpos = LZCOUNT(word >> 32 | word << 32) | (wordidx - 1) << 6;
    slot = *(uint64_t *)(*(uint64_t *)it[0] + 0x30 + bitpos * 0x10);
    out.lo = slot;
    out.hi = *(uint64_t *)(*(uint64_t *)it[0] + 0x38 + bitpos * 8);
    it[3] = wordidx - 1;
    it[4] = v - 1 & v;
    ((sk_code_t)it[5])(&out.lo, (uint64_t *)(*(uint64_t *)it[0] + 0x30 + bitpos * 0x10 + 8));
    out.hi = (uint64_t)*(uint8_t *)&out.hi;
    return out;
}

/* FUN_0007198c @ 0x7198c  (est. sk_set_iter_init)
 * Initialize a set iterator: out[0]=set, out[1]=set+0x40, out[2]=~mask,
 * out[3]=0, out[4]=first word masked, out[5]=cb, out[6]=ctx.
 * Confidence: high (structural). */
static void sk_set_iter_init(long *out, long set, long cb, long ctx)
{
    uint64_t mask = -1L << ((uint64_t)*(uint8_t *)(set + 0x20) & 0x3f);
    uint64_t first = *(uint64_t *)(set + 0x40);
    uint64_t neg = -mask;
    uint64_t m = 0xffffffffffffffffULL;
    if (neg < 0x40) {
        m = ~(-1L << (neg & 0x3f));
    }
    out[0] = set;
    out[1] = set + 0x40;
    out[2] = ~mask;
    out[3] = 0;
    out[4] = m & first;
    out[5] = cb;
    out[6] = ctx;
}

/* FUN_000719dc @ 0x719dc  (est. sk_set_emit_str)
 * Emit the string key for a set element via sk_apply_first(..., s___cstring).
 * Confidence: medium. */
static void sk_set_emit_str(uint64_t a, uint64_t b)
{
    sk_apply_first((uint64_t *)0, a, b, DAT_0064e108);
}

/* FUN_000719f0 @ 0x719f0  (est. sk_set_emit_str2) */
static void sk_set_emit_str2(uint64_t a, uint64_t b)
{
    sk_apply_first((uint64_t *)0, a, b, DAT_0064e638);
}

/* FUN_00071a04 @ 0x71a04  (est. sk_vec_alloc_0x04)
 * Allocate a vector with 4-byte elements: if n==0 empty; else alloc the
 * buffer and store {count, cap}.  Confidence: medium. */
static void sk_vec_alloc_0x04(uint64_t n)
{
    (void)n;
    sk_ext_000776d8();
    if (*(uint64_t *)0 == 0) {
        sk_ext_000776cc();
    } else {
        sk_ext_0007764c();
        sk_alloc_bytes(*(uint64_t *)0 << 2, 0);
        sk_ext_00077630();
        sk_ext_0007766c(0);
    }
}

/* FUN_00071a4c @ 0x71a4c  (est. sk_vec_alloc_0x10)
 * Allocate a 0x10-byte-element vector: n==0 -> empty, else alloc via
 * sk_array_alloc and set {count, cap} with unit=0x10.  Confidence: medium. */
static uint64_t sk_vec_alloc_0x10(uint64_t n, uint64_t cap)
{
    (void)cap;
    sk_ext_000776d8();
    if (*(uint64_t *)0 == 0) {
        sk_ext_000776cc();
        return 0;
    } else {
        uint64_t u = sk_ext_0007764c();
        uint64_t v = sk_array_alloc(u, *(uint64_t *)0 + 0x20, 7);
        *(uint64_t *)(v + 0x10) = n;
        *(uint64_t *)(v + 0x18) = (*(uint64_t *)0) * 2 - 0x40;
        return v;
    }
}

/* FUN_00071aa0 @ 0x71aa0  (est. sk_vec_alloc_0xf8)
 * Allocate a vector of 0xf8-byte records: count/cap units, 0xf8 stride.
 * Confidence: medium. */
static uint64_t sk_vec_alloc_0xf8(uint64_t count, uint64_t cap)
{
    if (cap <= count) cap = count;
    if (cap == 0) return DAT_00657778;
    uint64_t k = sk_string_cache(DAT_0064e870, DAT_004c06c8);
    uint64_t v = sk_array_alloc(k, cap * 0xf8 + 0x20, 7);
    *(uint64_t *)(v + 0x10) = count;
    *(uint64_t *)(v + 0x18) = ((*(uint64_t *)0 - 0x20) / 0xf8) << 1;
    return v;
}

/* FUN_00071b24 @ 0x71b24  (est. sk_vec_grow_0x40)
 * Grow a 0x40-byte-element vector.  Confidence: medium. */
static void sk_vec_grow_0x40(uint64_t n)
{
    (void)n;
    sk_ext_000776d8();
    if (*(uint64_t *)0 == 0) {
        sk_ext_000776cc();
    } else {
        sk_ext_0007764c();
        sk_array_alloc(0, *(uint64_t *)0 << 6 | 0x20, 7);
        sk_ext_00077630();
        sk_ext_0007766c(0);
    }
}

/* FUN_00071b74 @ 0x71b74  (est. sk_vec_grow_0x50)
 * Grow a 0x50-byte-element vector.  Confidence: medium. */
static void sk_vec_grow_0x50(uint64_t n)
{
    (void)n;
    sk_ext_000776d8();
    if (*(uint64_t *)0 == 0) {
        sk_ext_000776cc();
    } else {
        sk_ext_0007764c();
        sk_ext_000776f8();
        sk_ext_000775dc(0);
    }
}

/* FUN_00071bd0 @ 0x71bd0  (est. sk_vec_alloc_0x02)
 * Allocate a vector of 2-byte elements.  Confidence: medium. */
static uint64_t sk_vec_alloc_0x02(uint64_t count, uint64_t cap)
{
    if (cap <= count) cap = count;
    if (cap == 0) return DAT_00657778;
    uint64_t k = sk_string_cache(DAT_0064e7f8, DAT_004c0650);
    uint64_t v = sk_array_alloc(k, cap * 2 + 0x20, 7);
    *(uint64_t *)(v + 0x10) = count;
    *(uint64_t *)(v + 0x18) = ((*(uint64_t *)0 - 0x20) / 2) << 1;
    return v;
}

/* FUN_00071c4c @ 0x71c4c  (est. sk_vec_grow_0x50b) */
static void sk_vec_grow_0x50b(uint64_t n)
{
    (void)n;
    sk_ext_000776d8();
    if (*(uint64_t *)0 == 0) {
        sk_ext_000776cc();
    } else {
        sk_ext_0007764c();
        sk_ext_000776f8();
        sk_ext_000775dc(0);
    }
}

/* FUN_00071c94 @ 0x71c94  (est. sk_vec_alloc_0x58)
 * Allocate a vector of 0x58-byte records.  Confidence: medium. */
static uint64_t sk_vec_alloc_0x58(uint64_t count, uint64_t cap)
{
    if (cap <= count) cap = count;
    if (cap == 0) return DAT_00657778;
    uint64_t k = sk_string_cache(DAT_0064e6b8, DAT_004c0508);
    uint64_t v = sk_array_alloc(k, cap * 0x58 + 0x20, 7);
    *(uint64_t *)(v + 0x10) = count;
    *(uint64_t *)(v + 0x18) = ((*(uint64_t *)0 - 0x20) / 0x58) << 1;
    return v;
}

/* FUN_00071d18 @ 0x71d18  (est. sk_vec_grow_ptr) */
static void sk_vec_grow_ptr(uint64_t n)
{
    (void)n;
    sk_ext_000776d8();
    if (*(uint64_t *)0 == 0) {
        sk_ext_000776cc();
    } else {
        sk_string_cache(DAT_0064e758, DAT_004c2e90);
        sk_ext_000776f8();
        sk_ext_000775dc(0);
    }
}

/* FUN_00071d74 @ 0x71d74  (est. sk_vec_grow_byte) */
static void sk_vec_grow_byte(uint64_t n)
{
    (void)n;
    sk_ext_000776d8();
    if (*(uint64_t *)0 == 0) {
        sk_ext_000776cc();
    } else {
        sk_ext_0007764c();
        sk_ext_000776f8();
        sk_ext_000775dc(0);
    }
}

/* FUN_00071dbc @ 0x71dbc  (est. sk_vec_grow_0x20)
 * Grow a 0x20-byte-element vector.  Confidence: medium. */
static void sk_vec_grow_0x20(uint64_t n)
{
    (void)n;
    sk_ext_000776d8();
    if (*(uint64_t *)0 == 0) {
        sk_ext_000776cc();
    } else {
        sk_ext_0007764c();
        sk_alloc_bytes(*(uint64_t *)0 << 5, 0);
        sk_ext_00077630();
        sk_ext_0007766c(0);
    }
}

/* FUN_00071e04 @ 0x71e04  (est. sk_vec_grow_0x08) */
static void sk_vec_grow_0x08(uint64_t n)
{
    (void)n;
    sk_ext_000776d8();
    if (*(uint64_t *)0 == 0) {
        sk_ext_000776cc();
    } else {
        sk_ext_0007764c();
        sk_alloc_bytes(*(uint64_t *)0 << 3, 0);
        sk_ext_00077630();
        sk_ext_0007766c(0);
    }
}

/* FUN_00071e74 @ 0x71e74  (est. sk_vec_grow_0x10) */
static void sk_vec_grow_0x10(uint64_t n)
{
    (void)n;
    sk_ext_000776d8();
    if (*(uint64_t *)0 == 0) {
        sk_ext_000776cc();
    } else {
        sk_ext_0007764c();
        sk_alloc_bytes(*(uint64_t *)0 << 4, 0);
        sk_ext_00077630();
        sk_ext_0007766c(0);
    }
}

/* FUN_00071ebc @ 0x71ebc  (est. sk_vec_alloc_0x90)
 * Allocate a vector of 0x90-byte records.  Confidence: medium. */
static uint64_t sk_vec_alloc_0x90(uint64_t count, uint64_t cap)
{
    if (cap <= count) cap = count;
    if (cap == 0) return DAT_00657778;
    uint64_t k = sk_string_cache(DAT_0064e738, DAT_004c0588);
    uint64_t v = sk_array_alloc(k, cap * 0x90 + 0x20, 7);
    *(uint64_t *)(v + 0x10) = count;
    *(uint64_t *)(v + 0x18) = ((*(uint64_t *)0 - 0x20) / 0x90) << 1;
    return v;
}

/* FUN_00071f54 @ 0x71f54  (est. sk_vec_grow_ptr2) */
static void sk_vec_grow_ptr2(uint64_t n)
{
    (void)n;
    sk_ext_000776d8();
    if (*(uint64_t *)0 == 0) {
        sk_ext_000776cc();
    } else {
        sk_ext_0007764c();
        sk_ext_000776f8();
        sk_ext_000775dc(0);
    }
}

/* FUN_00071f9c @ 0x71f9c  (est. sk_vec_grow_ptr3) */
static void sk_vec_grow_ptr3(uint64_t n)
{
    (void)n;
    sk_ext_000776d8();
    if (*(uint64_t *)0 == 0) {
        sk_ext_000776cc();
    } else {
        sk_ext_0007764c();
        sk_ext_000776f8();
        sk_ext_000775dc(0);
    }
}

/*============================================================================
 * 0x71fe4 - 0x72424 : element-move (memmove) shims
 *==========================================================================*/

/* FUN_00071fe4 @ 0x71fe4  (est. sk_move_0x04)
 * memmove of n 4-byte elements (memmove when dst != src and ranges distinct);
 * fatal 0x72018 on negative n.  Confidence: high (structural). */
static void sk_move_0x04(uint64_t src, int64_t n, uint64_t dst)
{
    if (n < 0) sk_break(1, 0x72018);
    if (dst != src && src + n * 4 <= dst) sk_memmove(dst, src, (uint64_t)n << 2);
}

/* FUN_0007201c @ 0x7201c  (est. sk_move_0x04b) */
static void sk_move_0x04b(uint64_t src, int64_t n, uint64_t dst)
{
    if (n < 0) sk_break(1, 0x72044);
    if (dst != src && src + n * 4 <= dst) sk_memmove5(src);
}

/* FUN_00072044 @ 0x72044  (est. sk_move_0x10) */
static void sk_move_0x10(uint64_t src, int64_t n, uint64_t dst)
{
    if (n < 0) sk_break(1, 0x7206c);
    if (dst != src && src + n * 0x10 <= dst) sk_memmove5(src);
}

/* FUN_0007206c @ 0x7206c  (est. sk_move_0x28) */
static void sk_move_0x28(uint64_t src, int64_t n, uint64_t dst)
{
    if (n < 0) sk_break(1, 0x720a8);
    if (dst != src && src + n * 0x28 <= dst) sk_memmove(dst, src, (uint64_t)n * 0x28);
}

/* FUN_000720a8 @ 0x720a8  (est. sk_move_0x01) */
static void sk_move_0x01(uint64_t src, int64_t n, uint64_t dst)
{
    if (n < 0) sk_break(1, 0x720d8);
    if (dst != src && src + n <= dst) sk_memmove(dst, src, (uint64_t)n);
}

/* FUN_00072114 @ 0x72114  (est. sk_move_0x50) */
static void sk_move_0x50(uint64_t src, int64_t n, uint64_t dst)
{
    if (n < 0) sk_break(1, 0x72150);
    if (dst != src && src + n * 0x50 <= dst) sk_memmove(dst, src, (uint64_t)n * 0x50);
}

/* FUN_00072150 @ 0x72150  (est. sk_move_0x40) */
static void sk_move_0x40(uint64_t src, int64_t n, uint64_t dst)
{
    if (n < 0) sk_break(1, 0x72178);
    if (dst != src && src + n * 0x40 <= dst) sk_memmove5(src);
}

/* FUN_00072178 @ 0x72178  (est. sk_move_0x50b) */
static void sk_move_0x50b(uint64_t src, int64_t n, uint64_t dst)
{
    if (n < 0) sk_break(1, 0x721b0);
    if (dst != src && src + n * 0x50 <= dst) sk_memmove(dst, src, (uint64_t)n * 0x50);
}

/* FUN_000721b0 @ 0x721b0  (est. sk_move_0x08) */
static void sk_move_0x08(uint64_t src, int64_t n, uint64_t dst)
{
    if (n < 0) sk_break(1, 0x721d8);
    if (dst != src && src + n * 8 <= dst) sk_memmove5(src);
}

/* FUN_000721d8 @ 0x721d8  (est. sk_move_0x08b) */
static void sk_move_0x08b(uint64_t src, int64_t n, uint64_t dst)
{
    if (n < 0) sk_break(1, 0x7220c);
    if (dst != src && src + n * 8 <= dst) sk_memmove(dst, src, (uint64_t)n << 3);
}

/* FUN_0007220c @ 0x7220c  (est. sk_move_0x18) */
static void sk_move_0x18(uint64_t src, int64_t n, uint64_t dst)
{
    if (n < 0) sk_break(1, 0x7223c);
    if (dst != src && src + n * 0x18 <= dst) sk_memmove5(src);
}

/* FUN_00072270 @ 0x72270  (est. sk_move_0x38) */
static void sk_move_0x38(uint64_t src, int64_t n, uint64_t dst)
{
    if (n < 0) sk_break(1, 0x722ac);
    if (dst != src && src + n * 0x38 <= dst) sk_memmove(dst, src, (uint64_t)n * 0x38);
}

/* FUN_000722b0 @ 0x722b0  (est. sk_move_0x38b) */
static void sk_move_0x38b(uint64_t src, int64_t n, uint64_t dst)
{
    if (n < 0) sk_break(1, 0x722e8);
    if (dst != src && src + n * 0x38 <= dst) sk_memmove(dst, src, (uint64_t)n * 0x38);
}

/* FUN_00072320 @ 0x72320  (est. sk_move_0x48) */
static void sk_move_0x48(uint64_t src, int64_t n, uint64_t dst)
{
    if (n < 0) sk_break(1, 0x72358);
    if (dst != src && src + n * 0x48 <= dst) sk_memmove(dst, src, (uint64_t)n * 0x48);
}

/* FUN_00072358 @ 0x72358  (est. sk_move_0x18b) */
static void sk_move_0x18b(uint64_t src, int64_t n, uint64_t dst)
{
    if (n < 0) sk_break(1, 0x72384);
    if (dst != src && src + n * 0x18 <= dst) sk_memmove5(src);
}

/* FUN_000723c0 @ 0x723c0  (est. sk_move_0x28b) */
static void sk_move_0x28b(uint64_t src, int64_t n, uint64_t dst)
{
    if (n < 0) sk_break(1, 0x723f0);
    if (dst != src && src + n * 0x28 <= dst) sk_memmove5(src);
}

/* FUN_000723f4 @ 0x723f4  (est. sk_move_0x30) */
static void sk_move_0x30(uint64_t src, int64_t n, uint64_t dst)
{
    if (n < 0) sk_break(1, 0x72420);
    if (dst != src && src + n * 0x30 <= dst) sk_memmove5(src);
}

/* FUN_00072424 @ 0x72424  (est. sk_memcpy_record)
 * memcpy3(obj+0x20, obj+0x10, 0x67b200): copy the record body.
 * Confidence: high (structural). */
static void sk_memcpy_record(void)
{
    uint64_t *o = (uint64_t *)*(uint64_t *)0;
    sk_memcpy3((uint64_t)o + 0x20, o[1], DAT_0067b200);
}

/* FUN_00072454 @ 0x72454  (est. sk_set_count_cap)
 * Store {count, cap} into a vector header.  Confidence: high. */
static void sk_set_count_cap(uint64_t *h, uint64_t count)
{
    h[1] = count;
    h[2] = count << 1;
}

/*============================================================================
 * 0x72464 - 0x72b9c : set probe / find / skip primitives
 *==========================================================================*/

/* FUN_00072464 @ 0x72464  (est. sk_set_probe_flag)
 * Scope-bound probe dispatch: enter scope, lock-select(flag&0xff), exit, then
 * call sk_set_find(flag, result).  Confidence: medium. */
static void sk_set_probe_flag(uint64_t flag)
{
    uint64_t frame[9];
    uint64_t u;
    sk_scope_enter(frame, *(uint64_t *)((uint64_t)0 + 0x28));
    sk_lock_select(flag & 0xff);
    u = sk_scope_exit();
    sk_set_find((long)(flag & 0xff), 0, u);
}

/* FUN_000724cc @ 0x724cc  (est. sk_set_find)
 * Probe the set at x20 for a {key, tag} entry starting at index `param_2`:
 * scan occupied slots, comparing the entry's {key, tag} against {param_1,
 * param_2&0xff}; returns the {index, found-flag} pair.  Fatal traps 0x72a10.
 * Confidence: medium. */
static sk_u128_t sk_set_find(uint64_t key, char tag, uint64_t idx)
{
    uint64_t *set = (uint64_t *)*(uint64_t *)0;
    uint64_t mask = -1L << ((uint64_t)*(uint8_t *)(set + 0x20) & 0x3f);
    sk_u128_t out;
    uint64_t found = 0;
    idx &= ~mask;
    if ((*(uint64_t *)(set + 0x40 + (idx >> 6) * 8) >> (idx & 0x3f) & 1) != 0) {
        do {
            uint64_t *ent = (uint64_t *)(*(uint64_t *)(set + 0x30) + idx * 0x10);
            uint64_t k = ent[0];
            char t = (char)(ent[1] & 0xff);
            if (t == '\0') {
                if (tag == '\0' && (sk_key_hasheq(k, key) & 1) != 0) { found = 1; break; }
            } else if (t == '\x01') {
                if (tag == '\x01' && k == key) { found = 1; break; }
            } else if (tag == '\x02' && key == 0) { found = 1; break; }
            idx = (idx + 1) & ~mask;
        } while ((*(uint64_t *)(set + 0x40 + (idx >> 6) * 8) >> (idx & 0x3f) & 1) != 0);
    }
    out.lo = idx;
    out.hi = found;
    return out;
}

/* FUN_00072570 @ 0x72570  (est. sk_set_find_int_wrap)
 * Scope-bound int-key find: scope, lock-opt(param_1), then sk_set_find_int.
 * Confidence: medium. */
static void sk_set_find_int_wrap(uint64_t key)
{
    uint64_t u;
    sk_scope_ctx();
    sk_lock_opt(key);
    u = sk_scope_exit();
    sk_set_find_int((int)key, u);
}

/* FUN_000725c8 @ 0x725c8  (est. sk_set_emit_str_wrap)
 * Scope-bound emitter building a {a,b} ctx pair; then either lock-bind-select
 * 0 or 1 + FUN_00077894, exit scope, emit, and probe the result.
 * Confidence: medium. */
static void sk_set_emit_str_wrap(uint64_t a, uint64_t b, uint64_t c, int64_t n)
{
    uint64_t frame[9];
    sk_scope_ctx();
    sk_ctx_pair(frame, a, b);
    if (n == 0) {
        sk_lock_bind_select(0);
    } else {
        sk_lock_bind_select(1);
        sk_scope_ctx2();
        sk_ctx_pair(frame, 0, 0);
    }
    sk_scope_exit();
    sk_done3();
    sk_set_find_pair(0,0,0,0,0);
}

/* FUN_00072664 @ 0x72664  (est. sk_set_find_word_wrap)
 * lock-opt2(obj+0x28, key) then sk_set_find_word(key, result).
 * Confidence: medium. */
static void sk_set_find_word_wrap(uint64_t key)
{
    uint64_t u = sk_lock_opt2(*(uint64_t *)((uint64_t)0 + 0x28), key);
    sk_set_find_word((long)key, u);
}

/* FUN_000726a0 @ 0x726a0  (est. sk_set_find_obj_wrap)
 * Scope-bound object-key find: call the object's own vtable fn (*(*set+0xd8)),
 * then sk_set_find_obj.  Confidence: medium. */
static void sk_set_find_obj_wrap(uint64_t *set)
{
    uint64_t u;
    uint64_t frame[9];
    sk_scope_ctx();
    (**(sk_code_t **)(*set + 0xd8))(frame);
    u = sk_scope_exit();
    sk_set_find_obj((uint64_t)set, u);
}

/* FUN_00072710 @ 0x72710  (est. sk_set_emit_ctx_obj)
 * Scope-bound: build a {a, tag} ctx pair via sk_ctx_make, bind it, release,
 * then sk_set_find(a, result).  Confidence: medium. */
static void sk_set_emit_ctx_obj(uint64_t a)
{
    uint64_t frame[9];
    sk_u128_t pr;
    uint64_t u;
    sk_scope_ctx();
    pr = sk_ctx_make(a);
    sk_ctx_pair(frame, pr.lo, pr.hi);
    sk_swift_release_masked(pr.hi);
    u = sk_scope_exit();
    sk_set_find(a, 0, u);
}

/* FUN_0007278c @ 0x7278c  (est. sk_set_skip_wrap)
 * Scope-bound: scope-ctx, lock-select twice, exit, then sk_set_skip_pair.
 * Confidence: medium. */
static void sk_set_skip_wrap(void)
{
    uint64_t u;
    sk_scope_ctx3();
    sk_lock_select(0);
    sk_lock_select(0);
    u = sk_scope_exit();
    sk_set_skip_pair(0, 0, u);
}

/* FUN_000727ec @ 0x727ec  (est. sk_set_find_impl)
 * Probe the set at x20 for the first occupied slot at/after `param_3` whose
 * entry matches {param_1, param_2} (tag-based equality: 0 -> hasheq, 1 ->
 * word-eq, 2 -> key==0).  Returns {index, found}.  Fatal 0x728b4.
 * Confidence: medium. */
static sk_u128_t sk_set_find_impl(long key, char tag, uint64_t idx)
{
    uint64_t *set = (uint64_t *)*(uint64_t *)0;
    uint64_t mask = -1L << ((uint64_t)*(uint8_t *)(set + 0x20) & 0x3f);
    uint64_t found = 0;
    idx &= ~mask;
    if ((*(uint64_t *)(set + 0x40 + (idx >> 6) * 8) >> (idx & 0x3f) & 1) != 0) {
        do {
            uint64_t *ent = (uint64_t *)(*(uint64_t *)(set + 0x30) + idx * 0x10);
            uint64_t k = ent[0];
            char t = (char)(ent[1] & 0xff);
            if (t == '\0') {
                if (tag == '\0' && (sk_key_hasheq(k, (uint64_t)key) & 1) != 0) { found = 1; break; }
            } else if (t == '\x01') {
                if (tag == '\x01' && (long)k == key) { found = 1; break; }
            } else if (tag == '\x02' && key == 0) { found = 1; break; }
            idx = (idx + 1) & ~mask;
        } while ((*(uint64_t *)(set + 0x40 + (idx >> 6) * 8) >> (idx & 0x3f) & 1) != 0);
    }
    sk_u128_t out; out.lo = idx; out.hi = found; return out;
}

/* FUN_000728d4 @ 0x728d4  (est. sk_set_find_int)
 * Scan set at x20 from `idx` for the slot whose int value equals `key`; wraps
 * index modulo mask.  Returns {index, found}.  Confidence: medium. */
static sk_u128_t sk_set_find_int(int key, uint64_t idx)
{
    uint64_t *set = (uint64_t *)*(uint64_t *)0;
    uint64_t mask = -1L << ((uint64_t)*(uint8_t *)(set + 0x20) & 0x3f);
    sk_u128_t out;
    uint64_t b;
    while (1) {
        idx &= ~mask;
        b = 1UL << (idx & 0x3f) & *(uint64_t *)(set + 0x40 + (idx >> 6) * 8);
        if (b == 0 || *(int *)(*(uint64_t *)(set + 0x30) + idx * 4) == key) break;
        idx = idx + 1;
    }
    out.lo = idx; out.hi = b != 0; return out;
}

/* FUN_0007292c @ 0x7292c  (est. sk_set_find_pair)
 * Probe set at x20 for an entry whose first word-pair equals {a,b} and whose
 * optional second pair equals {c,d}; returns {index, found}.  Fatal 0x72a0c.
 * Confidence: medium. */
static sk_u128_t sk_set_find_pair(long a, long b, long c, long d, uint64_t idx)
{
    uint64_t *set = (uint64_t *)*(uint64_t *)0;
    uint64_t mask = -1L << ((uint64_t)*(uint8_t *)(set + 0x20) & 0x3f);
    uint64_t found = 0;
    idx &= ~mask;
    if ((*(uint64_t *)(set + 0x40 + (idx >> 6) * 8) >> (idx & 0x3f) & 1) != 0) {
        uint64_t base = *(uint64_t *)(set + 0x30);
        do {
            uint64_t *ent = (uint64_t *)(base + idx * 0x20);
            if ((ent[0] == (uint64_t)a && ent[1] == (uint64_t)b) ||
                (sk_pair_eq(ent[0], ent[1], (uint64_t)a, (uint64_t)b, 0) & 1) != 0) {
                if (ent[3] == 0) {
                    if (d == 0) { found = 1; break; }
                } else if (d != 0 && (ent[2] == (uint64_t)c && ent[3] == (uint64_t)d ||
                         (sk_pair_eq(ent[2], ent[3], (uint64_t)c, (uint64_t)d, 0) & 1) != 0)) {
                    found = 1; break;
                }
            }
            idx = (idx + 1) & ~mask;
        } while ((*(uint64_t *)(set + 0x40 + (idx >> 6) * 8) >> (idx & 0x3f) & 1) != 0);
    }
    sk_u128_t out; out.lo = idx; out.hi = found; return out;
}

/* FUN_00072a30 @ 0x72a30  (est. sk_set_find_word)
 * Scan set at x20 for the slot whose word value equals `key`.
 * Confidence: medium. */
static sk_u128_t sk_set_find_word(long key, uint64_t idx)
{
    uint64_t *set = (uint64_t *)*(uint64_t *)0;
    uint64_t mask = -1L << ((uint64_t)*(uint8_t *)(set + 0x20) & 0x3f);
    sk_u128_t out;
    uint64_t b;
    while (1) {
        idx &= ~mask;
        b = 1UL << (idx & 0x3f) & *(uint64_t *)(set + 0x40 + (idx >> 6) * 8);
        if (b == 0 || *(int64_t *)(*(uint64_t *)(set + 0x30) + idx * 8) == key) break;
        idx = idx + 1;
    }
    out.lo = idx; out.hi = b != 0; return out;
}

/* FUN_00072a88 @ 0x72a88  (est. sk_set_find_obj)
 * Scan set at x20 for the slot whose retained object compares equal to `key`
 * (retain, hasheq, release per slot).  Returns {index, found}.
 * Confidence: medium. */
static sk_u128_t sk_set_find_obj(uint64_t key, uint64_t idx)
{
    uint64_t *set = (uint64_t *)*(uint64_t *)0;
    uint64_t mask = -1L << ((uint64_t)*(uint8_t *)(set + 0x20) & 0x3f);
    sk_u128_t out;
    uint64_t b;
    while (1) {
        idx &= ~mask;
        b = 1UL << (idx & 0x3f) & *(uint64_t *)(set + 0x40 + (idx >> 6) * 8);
        if (b == 0) break;
        sk_obj_retain0(0);
        uint64_t v = *(uint64_t *)(*(uint64_t *)(set + 0x30) + idx * 8);
        uint64_t r = sk_swift_retain(v);
        uint64_t eq = sk_obj_hasheq(r, key);
        sk_swift_release(v);
        if ((eq & 1) != 0) break;
        idx = idx + 1;
    }
    out.lo = idx; out.hi = b != 0; return out;
}

/* FUN_00072b44 @ 0x72b44  (est. sk_set_skip)
 * Advance `idx` past occupied slots whose byte value != `c` (find next slot
 * with value == c or unoccupied).  Confidence: medium. */
static void sk_set_skip(char c, uint64_t idx)
{
    uint64_t *set = (uint64_t *)*(uint64_t *)0;
    uint64_t mask = -1L << ((uint64_t)*(uint8_t *)(set + 0x20) & 0x3f);
    for (; ; idx = idx + 1) {
        idx &= ~mask;
        if ((1UL << (idx & 0x3f) & *(uint64_t *)(set + 0x40 + (idx >> 6) * 8)) == 0) break;
        if (*(char *)(*(uint64_t *)(set + 0x30) + idx) == c) break;
    }
}

/* FUN_00072b9c @ 0x72b9c  (est. sk_set_skip_pair)
 * Advance `idx` past occupied slots whose first word-pair != {a,b}; stop at
 * the first matching pair or an empty slot.  Confidence: medium. */
static void sk_set_skip_pair(long a, long b, uint64_t idx)
{
    uint64_t *set = (uint64_t *)*(uint64_t *)0;
    uint64_t mask = -1L << ((uint64_t)*(uint8_t *)(set + 0x20) & 0x3f);
    idx &= ~mask;
    if ((*(uint64_t *)(set + 0x40 + (idx >> 6) * 8) >> (idx & 0x3f) & 1) != 0) {
        do {
            uint64_t *ent = (uint64_t *)(*(uint64_t *)(set + 0x30) + idx * 0x10);
            if (ent[0] == (uint64_t)a && ent[1] == (uint64_t)b) return;
            idx = (idx + 1) & ~mask;
        } while ((*(uint64_t *)(set + 0x40 + (idx >> 6) * 8) >> (idx & 0x3f) & 1) != 0);
    }
}

/*============================================================================
 * 0x72c0c - 0x73af0 : vector reserve + element-copy dispatchers
 *==========================================================================*/

/* FUN_00072c0c @ 0x72c0c  (est. sk_reserve_u8)
 * Reserve `count` 0x10-byte elements in a growable vector: on the `grow` flag
 * check the current count and optionally grow (fatal 0x72c98), then call the
 * u8-stride allocator and either a no-copy or a copy+release path.
 * Returns the vector.  Confidence: medium (Swift Array reserve/copy). */
static sk_u128_t sk_reserve_u8(uint64_t a, uint64_t b, uint64_t grow)
{
    uint64_t u;
    uint64_t *obj = (uint64_t *)*(uint64_t *)0;
    (void)a; (void)b;
    sk_ret0();
    u = (uint64_t)*(uint64_t *)0;
    if ((grow & 1) != 0) {
        sk_ret0b();
        if (1 /* in_NG != in_OV */) {
            sk_check_ovf();
            if (1 /* in_NG */) sk_break(1, 0x72c98);
            sk_ret0c();
            u = (uint64_t)*(uint64_t *)0;
        }
    }
    u = sk_vec_alloc_0x10(obj[1], u);
    if ((*(uint64_t *)0 & 1) == 0) {
        sk_ret0d();
        sk_ext_00069770();
    } else {
        sk_ptr_plus();
        sk_ext_00069970();
        sk_release_and_zero();
    }
    sk_u128_t r; r.lo = u; r.hi = 0; return r;
}

/* FUN_00072c98 @ 0x72c98  (est. sk_reserve_impl)
 * Reserve `count` elements with overflow growth checks (fatal 0x72d5c on
 * capacity overflow); then either copy (no unique) or move-and-release
 * (unique).  Returns the new vector.  Confidence: medium. */
static uint64_t sk_reserve_impl(uint64_t unique, uint64_t count, uint64_t grow, uint64_t vec)
{
    uint64_t cap = count;
    uint64_t u, v;
    if ((grow & 1) != 0) {
        cap = *(uint64_t *)(vec + 0x18) >> 1;
        if ((int64_t)cap < (int64_t)count) {
            if ((int64_t)(cap + 0x4000000000000000) < 0) sk_break(1, 0x72d5c);
            cap = *(uint64_t *)(vec + 0x18) & 0xfffffffffffffffe;
            if ((int64_t)cap <= (int64_t)count) cap = count;
        }
    }
    u = *(uint64_t *)(vec + 0x10);
    v = sk_vec_alloc_0x10(u, cap);
    if ((unique & 1) == 0) {
        sk_copy4(0, u, v + 0x20, vec);
    } else {
        sk_move_0x04(vec + 0x20, u, v + 0x20);
        *(uint64_t *)(vec + 0x10) = 0;
        sk_swift_release(vec);
    }
    return v;
}

/* FUN_00072d5c @ 0x72d5c  (est. sk_reserve_u16) */
static sk_u128_t sk_reserve_u16(uint64_t a, uint64_t b, uint64_t grow)
{
    uint64_t u;
    uint64_t *obj = (uint64_t *)*(uint64_t *)0;
    (void)a; (void)b;
    sk_ret0();
    u = (uint64_t)*(uint64_t *)0;
    if ((grow & 1) != 0) {
        sk_ret0b();
        if (1) {
            sk_check_ovf();
            if (1) sk_break(1, 0x72de8);
            sk_ret0c();
            u = (uint64_t)*(uint64_t *)0;
        }
    }
    u = sk_vec_alloc_0x10(obj[1], u);
    if ((*(uint64_t *)0 & 1) == 0) {
        sk_ret0d();
        sk_ext_000750bc();
    } else {
        sk_ptr_plus();
        sk_move_0x08(0,0,0);
        sk_release_and_zero();
    }
    sk_u128_t r; r.lo = u; r.hi = 0; return r;
}

/* FUN_00072de8 @ 0x72de8  (est. sk_reserve_u32) */
static sk_u128_t sk_reserve_u32(uint64_t a, uint64_t b, uint64_t grow)
{
    uint64_t u;
    uint64_t *obj = (uint64_t *)*(uint64_t *)0;
    (void)a; (void)b;
    sk_ret0();
    u = (uint64_t)*(uint64_t *)0;
    if ((grow & 1) != 0) {
        sk_ret0b();
        if (1) {
            sk_check_ovf();
            if (1) sk_break(1, 0x72e74);
            sk_ret0c();
            u = (uint64_t)*(uint64_t *)0;
        }
    }
    u = sk_vec_alloc_0x10(obj[1], u);
    if ((*(uint64_t *)0 & 1) == 0) {
        sk_ret0d();
        sk_ext_00074a98();
    } else {
        sk_ptr_plus();
        sk_move_0x40(0,0,0);
        sk_release_and_zero();
    }
    sk_u128_t r; r.lo = u; r.hi = 0; return r;
}

/* FUN_00072e74 @ 0x72e74  (est. sk_reserve_ptr2) */
static sk_u128_t sk_reserve_ptr2(uint64_t a, uint64_t b, uint64_t grow)
{
    uint64_t u;
    uint64_t *obj = (uint64_t *)*(uint64_t *)0;
    (void)a; (void)b;
    sk_ret0();
    u = (uint64_t)*(uint64_t *)0;
    if ((grow & 1) != 0) {
        sk_ret0b();
        if (1) {
            sk_check_ovf();
            if (1) sk_break(1, 0x72f00);
            sk_ret0c();
            u = (uint64_t)*(uint64_t *)0;
        }
    }
    u = sk_vec_alloc_0x10(obj[1], u);
    if ((*(uint64_t *)0 & 1) == 0) {
        sk_ret0d();
        sk_ext_00075c50();
    } else {
        sk_ptr_plus();
        sk_move_0x28b(0,0,0);
        sk_release_and_zero();
    }
    sk_u128_t r; r.lo = u; r.hi = 0; return r;
}

/* FUN_00072f00 @ 0x72f00  (est. sk_reserve_pair) */
static sk_u128_t sk_reserve_pair(uint64_t a, uint64_t b, uint64_t grow)
{
    uint64_t u;
    uint64_t *obj = (uint64_t *)*(uint64_t *)0;
    (void)a; (void)b;
    sk_ret0();
    u = (uint64_t)*(uint64_t *)0;
    if ((grow & 1) != 0) {
        sk_ret0b();
        if (1) {
            sk_check_ovf();
            if (1) sk_break(1, 0x72f8c);
            sk_ret0c();
            u = (uint64_t)*(uint64_t *)0;
        }
    }
    u = sk_vec_alloc_0x10(obj[1], u);
    if ((*(uint64_t *)0 & 1) == 0) {
        sk_ret0d();
        sk_ext_00074b08();
    } else {
        sk_ptr_plus();
        sk_ext_000699a4();
        sk_release_and_zero();
    }
    sk_u128_t r; r.lo = u; r.hi = 0; return r;
}

/* FUN_00072f8c @ 0x72f8c  (est. sk_reserve_u16b) */
static sk_u128_t sk_reserve_u16b(uint64_t a, uint64_t b, uint64_t grow)
{
    uint64_t u;
    uint64_t *obj = (uint64_t *)*(uint64_t *)0;
    (void)a; (void)b;
    sk_ret0();
    u = (uint64_t)*(uint64_t *)0;
    if ((grow & 1) != 0) {
        sk_ret0b();
        if (1) {
            sk_check_ovf();
            if (1) sk_break(1, 0x73018);
            sk_ret0c();
            u = (uint64_t)*(uint64_t *)0;
        }
    }
    u = sk_vec_alloc_0x10(obj[1], u);
    if ((*(uint64_t *)0 & 1) == 0) {
        sk_ret0d();
        sk_ext_000750bc();
    } else {
        sk_ptr_plus();
        sk_move_0x08(0,0,0);
        sk_release_and_zero();
    }
    sk_u128_t r; r.lo = u; r.hi = 0; return r;
}

/* FUN_00073018 @ 0x73018  (est. sk_reserve_u8b) */
static sk_u128_t sk_reserve_u8b(uint64_t a, uint64_t b, uint64_t grow)
{
    uint64_t u;
    uint64_t *obj = (uint64_t *)*(uint64_t *)0;
    (void)a; (void)b;
    sk_ret0();
    u = (uint64_t)*(uint64_t *)0;
    if ((grow & 1) != 0) {
        sk_ret0b();
        if (1) {
            sk_check_ovf();
            if (1) sk_break(1, 0x730a4);
            sk_ret0c();
            u = (uint64_t)*(uint64_t *)0;
        }
    }
    u = sk_vec_alloc_0x10(obj[1], u);
    if ((*(uint64_t *)0 & 1) == 0) {
        sk_ret0d();
        sk_ext_00074a28();
    } else {
        sk_ptr_plus();
        sk_move_0x04b(0,0,0);
        sk_release_and_zero();
    }
    sk_u128_t r; r.lo = u; r.hi = 0; return r;
}

/* FUN_000730a4 @ 0x730a4  (est. sk_reserve_ptr3) */
static sk_u128_t sk_reserve_ptr3(uint64_t a, uint64_t b, uint64_t grow)
{
    uint64_t u;
    uint64_t *obj = (uint64_t *)*(uint64_t *)0;
    (void)a; (void)b;
    sk_ret0();
    u = (uint64_t)*(uint64_t *)0;
    if ((grow & 1) != 0) {
        sk_ret0b();
        if (1) {
            sk_check_ovf();
            if (1) sk_break(1, 0x73140);
            sk_ret0c();
            u = (uint64_t)*(uint64_t *)0;
        }
    }
    u = sk_vec_alloc_0x10(obj[1], u);
    if ((*(uint64_t *)0 & 1) == 0) {
        sk_ret0d();
        sk_ext_00075b2c();
    } else {
        sk_ptr_plus();
        sk_move_0x28b(0,0,0);
        sk_release_and_zero();
    }
    sk_u128_t r; r.lo = u; r.hi = 0; return r;
}

/* FUN_00073140 @ 0x73140  (est. sk_reserve_ptr4) */
static sk_u128_t sk_reserve_ptr4(uint64_t a, uint64_t b, uint64_t grow)
{
    uint64_t u;
    uint64_t *obj = (uint64_t *)*(uint64_t *)0;
    (void)a; (void)b;
    sk_ret0();
    u = (uint64_t)*(uint64_t *)0;
    if ((grow & 1) != 0) {
        sk_ret0b();
        if (1) {
            sk_check_ovf();
            if (1) sk_break(1, 0x731dc);
            sk_ret0c();
            u = (uint64_t)*(uint64_t *)0;
        }
    }
    u = sk_vec_alloc_0x10(obj[1], u);
    if ((*(uint64_t *)0 & 1) == 0) {
        sk_ret0d();
        sk_ext_00075b2c();
    } else {
        sk_ptr_plus();
        sk_move_0x28b(0,0,0);
        sk_release_and_zero();
    }
    sk_u128_t r; r.lo = u; r.hi = 0; return r;
}

/* FUN_000731dc @ 0x731dc  (est. sk_reserve_u64) */
static sk_u128_t sk_reserve_u64(uint64_t a, uint64_t b, uint64_t grow)
{
    uint64_t u;
    uint64_t *obj = (uint64_t *)*(uint64_t *)0;
    (void)a; (void)b;
    sk_ret0();
    u = (uint64_t)*(uint64_t *)0;
    if ((grow & 1) != 0) {
        sk_ret0b();
        if (1) {
            sk_check_ovf();
            if (1) sk_break(1, 0x73268);
            sk_ret0c();
            u = (uint64_t)*(uint64_t *)0;
        }
    }
    u = sk_vec_alloc_0x10(obj[1], u);
    if ((*(uint64_t *)0 & 1) == 0) {
        sk_ret0d();
        sk_ext_00074b78();
    } else {
        sk_ptr_plus();
        sk_move_0x10(0,0,0);
        sk_release_and_zero();
    }
    sk_u128_t r; r.lo = u; r.hi = 0; return r;
}

/* FUN_00073268 @ 0x73268  (est. sk_reserve_octo) */
static sk_u128_t sk_reserve_octo(uint64_t a, uint64_t b, uint64_t grow)
{
    uint64_t u;
    uint64_t *obj = (uint64_t *)*(uint64_t *)0;
    (void)a; (void)b;
    sk_ret0();
    u = (uint64_t)*(uint64_t *)0;
    if ((grow & 1) != 0) {
        sk_ret0b();
        if (1) {
            sk_check_ovf();
            if (1) sk_break(1, 0x732f4);
            sk_ret0c();
            u = (uint64_t)*(uint64_t *)0;
        }
    }
    u = sk_vec_alloc_0x10(obj[1], u);
    if ((*(uint64_t *)0 & 1) == 0) {
        sk_ret0d();
        sk_ext_00075784();
    } else {
        sk_ptr_plus();
        sk_move_0x18b(0,0,0);
        sk_release_and_zero();
    }
    sk_u128_t r; r.lo = u; r.hi = 0; return r;
}

/* FUN_000732f4 @ 0x732f4  (est. sk_reserve_ptr5) */
static sk_u128_t sk_reserve_ptr5(uint64_t a, uint64_t b, uint64_t grow)
{
    uint64_t u;
    uint64_t *obj = (uint64_t *)*(uint64_t *)0;
    (void)a; (void)b;
    sk_ret0();
    u = (uint64_t)*(uint64_t *)0;
    if ((grow & 1) != 0) {
        sk_ret0b();
        if (1) {
            sk_check_ovf();
            if (1) sk_break(1, 0x73380);
            sk_ret0c();
            u = (uint64_t)*(uint64_t *)0;
        }
    }
    u = sk_vec_alloc_0x10(obj[1], u);
    if ((*(uint64_t *)0 & 1) == 0) {
        sk_ret0d();
        sk_ext_00074c14();
    } else {
        sk_ptr_plus();
        sk_move_0x28(0,0,0);
        sk_release_and_zero();
    }
    sk_u128_t r; r.lo = u; r.hi = 0; return r;
}

/* FUN_00073380 @ 0x73380  (est. sk_reserve_u16c) */
static sk_u128_t sk_reserve_u16c(uint64_t a, uint64_t b, uint64_t grow)
{
    uint64_t u;
    uint64_t *obj = (uint64_t *)*(uint64_t *)0;
    (void)a; (void)b;
    sk_ret0();
    u = (uint64_t)*(uint64_t *)0;
    if ((grow & 1) != 0) {
        sk_ret0b();
        if (1) {
            sk_check_ovf();
            if (1) sk_break(1, 0x7340c);
            sk_ret0c();
            u = (uint64_t)*(uint64_t *)0;
        }
    }
    u = sk_vec_alloc_0x10(obj[1], u);
    if ((*(uint64_t *)0 & 1) == 0) {
        sk_ret0d();
        sk_ext_000750bc();
    } else {
        sk_ptr_plus();
        sk_move_0x08(0,0,0);
        sk_release_and_zero();
    }
    sk_u128_t r; r.lo = u; r.hi = 0; return r;
}

/* FUN_0007340c @ 0x7340c  (est. sk_reserve_u64b) */
static sk_u128_t sk_reserve_u64b(uint64_t a, uint64_t b, uint64_t grow)
{
    uint64_t u;
    uint64_t *obj = (uint64_t *)*(uint64_t *)0;
    (void)a; (void)b;
    sk_ret0();
    u = (uint64_t)*(uint64_t *)0;
    if ((grow & 1) != 0) {
        sk_ret0b();
        if (1) {
            sk_check_ovf();
            if (1) sk_break(1, 0x73498);
            sk_ret0c();
            u = (uint64_t)*(uint64_t *)0;
        }
    }
    u = sk_vec_alloc_0x10(obj[1], u);
    if ((*(uint64_t *)0 & 1) == 0) {
        sk_ret0d();
        sk_ext_00074cb8();
    } else {
        sk_ptr_plus();
        sk_move_0x10(0,0,0);
        sk_release_and_zero();
    }
    sk_u128_t r; r.lo = u; r.hi = 0; return r;
}

/* FUN_00073498 @ 0x73498  (est. sk_reserve_u16d) */
static sk_u128_t sk_reserve_u16d(uint64_t a, uint64_t b, uint64_t grow)
{
    uint64_t u;
    uint64_t *obj = (uint64_t *)*(uint64_t *)0;
    (void)a; (void)b;
    sk_ret0();
    u = (uint64_t)*(uint64_t *)0;
    if ((grow & 1) != 0) {
        sk_ret0b();
        if (1) {
            sk_check_ovf();
            if (1) sk_break(1, 0x73524);
            sk_ret0c();
            u = (uint64_t)*(uint64_t *)0;
        }
    }
    u = sk_vec_alloc_0x10(obj[1], u);
    if ((*(uint64_t *)0 & 1) == 0) {
        sk_ret0d();
        sk_ext_00074d54();
    } else {
        sk_ptr_plus();
        sk_move_0x08(0,0,0);
        sk_release_and_zero();
    }
    sk_u128_t r; r.lo = u; r.hi = 0; return r;
}

/* FUN_00073524 @ 0x73524  (est. sk_reserve_big_u64)
 * Reserve u64 elements with overflow growth; copy via FUN_000758d8 or move via
 * 0x72044.  Confidence: medium. */
static uint64_t sk_reserve_big_u64(uint64_t unique, uint64_t count, uint64_t grow, uint64_t vec)
{
    uint64_t cap = count;
    uint64_t u, v;
    if ((grow & 1) != 0) {
        cap = *(uint64_t *)(vec + 0x18) >> 1;
        if ((int64_t)cap < (int64_t)count) {
            if ((int64_t)(cap + 0x4000000000000000) < 0) sk_break(1, 0x73604);
            cap = *(uint64_t *)(vec + 0x18) & 0xfffffffffffffffe;
            if ((int64_t)cap <= (int64_t)count) cap = count;
        }
    }
    u = *(uint64_t *)(vec + 0x10);
    v = sk_vec_alloc_0x10(u, cap);
    if ((unique & 1) == 0) {
        sk_copy5(0, u, v + 0x20, vec, 0x6728f0);
    } else {
        sk_move_0x10(vec + 0x20, u, v + 0x20);
        sk_release_and_zero();
    }
    return v;
}

/* FUN_00073604 @ 0x73604  (est. sk_reserve_u128) */
static sk_u128_t sk_reserve_u128(uint64_t a, uint64_t b, uint64_t grow)
{
    uint64_t u;
    uint64_t *obj = (uint64_t *)*(uint64_t *)0;
    (void)a; (void)b;
    sk_ret0();
    u = (uint64_t)*(uint64_t *)0;
    if ((grow & 1) != 0) {
        sk_ret0b();
        if (1) {
            sk_check_ovf();
            if (1) sk_break(1, 0x73690);
            sk_ret0c();
            u = (uint64_t)*(uint64_t *)0;
        }
    }
    u = sk_vec_alloc_0x10(obj[1], u);
    if ((*(uint64_t *)0 & 1) == 0) {
        sk_ret0d();
        sk_ext_00074dc8();
    } else {
        sk_ptr_plus();
        sk_move_0x01(0,0,0);
        sk_release_and_zero();
    }
    sk_u128_t r; r.lo = u; r.hi = 0; return r;
}

/* FUN_00073690 @ 0x73690  (est. sk_reserve_quad) */
static sk_u128_t sk_reserve_quad(uint64_t a, uint64_t b, uint64_t grow)
{
    uint64_t u;
    uint64_t *obj = (uint64_t *)*(uint64_t *)0;
    (void)a; (void)b;
    sk_ret0();
    u = (uint64_t)*(uint64_t *)0;
    if ((grow & 1) != 0) {
        sk_ret0b();
        if (1) {
            sk_check_ovf();
            if (1) sk_break(1, 0x7371c);
            sk_ret0c();
            u = (uint64_t)*(uint64_t *)0;
        }
    }
    u = sk_vec_alloc_0x10(obj[1], u);
    if ((*(uint64_t *)0 & 1) == 0) {
        sk_ret0d();
        sk_ext_000697e4();
    } else {
        sk_ptr_plus();
        sk_ext_000699a4();
        sk_release_and_zero();
    }
    sk_u128_t r; r.lo = u; r.hi = 0; return r;
}

/* FUN_0007371c @ 0x7371c  (est. sk_reserve_octo2) */
static sk_u128_t sk_reserve_octo2(uint64_t a, uint64_t b, uint64_t grow)
{
    uint64_t u;
    uint64_t *obj = (uint64_t *)*(uint64_t *)0;
    (void)a; (void)b;
    sk_ret0();
    u = (uint64_t)*(uint64_t *)0;
    if ((grow & 1) != 0) {
        sk_ret0b();
        if (1) {
            sk_check_ovf();
            if (1) sk_break(1, 0x737a8);
            sk_ret0c();
            u = (uint64_t)*(uint64_t *)0;
        }
    }
    u = sk_vec_alloc_0x10(obj[1], u);
    if ((*(uint64_t *)0 & 1) == 0) {
        sk_ret0d();
        sk_ext_00074e34();
    } else {
        sk_ptr_plus();
        sk_move_0x18b(0,0,0);
        sk_release_and_zero();
    }
    sk_u128_t r; r.lo = u; r.hi = 0; return r;
}

/* FUN_000737a8 @ 0x737a8  (est. sk_reserve_flex_wrap) */
static void sk_reserve_flex_wrap(void)
{
    sk_reserve_flex(0, 0, 0, 0, 0, 0, 0);
}

/* FUN_000737e8 @ 0x737e8  (est. sk_reserve_flex)
 * Generic vector reserve driven by three function pointers (allocator,
 * move-copy, copy): compute cap with overflow growth (fatal 0x738b0), call the
 * allocator, then either the copy or the move+release path.
 * Confidence: medium. */
static uint64_t sk_reserve_flex(uint64_t unique, uint64_t count, uint64_t grow, uint64_t vec,
                                sk_code_t alloc, sk_code_t copyfn, sk_code_t movefn)
{
    uint64_t cap = count;
    uint64_t u, v;
    if ((grow & 1) != 0) {
        cap = *(uint64_t *)(vec + 0x18) >> 1;
        if ((int64_t)cap < (int64_t)count) {
            if ((int64_t)(cap + 0x4000000000000000) < 0) sk_break(1, 0x738b0);
            cap = *(uint64_t *)(vec + 0x18) & 0xfffffffffffffffe;
            if ((int64_t)cap <= (int64_t)count) cap = count;
        }
    }
    u = *(uint64_t *)(vec + 0x10);
    v = alloc(u, cap);
    if ((unique & 1) == 0) {
        copyfn(0, u, v + 0x20, vec);
    } else {
        movefn(vec + 0x20, u, v + 0x20);
        sk_release_and_zero();
    }
    return v;
}

/* FUN_000738b0 @ 0x738b0  (est. sk_reserve_u32b) */
static sk_u128_t sk_reserve_u32b(uint64_t a, uint64_t b, uint64_t grow)
{
    uint64_t u;
    uint64_t *obj = (uint64_t *)*(uint64_t *)0;
    (void)a; (void)b;
    sk_ret0();
    u = (uint64_t)*(uint64_t *)0;
    if ((grow & 1) != 0) {
        sk_ret0b();
        if (1) {
            sk_check_ovf();
            if (1) sk_break(1, 0x7393c);
            sk_ret0c();
            u = (uint64_t)*(uint64_t *)0;
        }
    }
    u = sk_vec_alloc_0x10(obj[1], u);
    if ((*(uint64_t *)0 & 1) == 0) {
        sk_ret0d();
        sk_ext_00074f28();
    } else {
        sk_ptr_plus();
        sk_move_0x50(0,0,0);
        sk_release_and_zero();
    }
    sk_u128_t r; r.lo = u; r.hi = 0; return r;
}

/* FUN_0007393c @ 0x7393c  (est. sk_reserve_octo3) */
static sk_u128_t sk_reserve_octo3(uint64_t a, uint64_t b, uint64_t grow)
{
    uint64_t u;
    uint64_t *obj = (uint64_t *)*(uint64_t *)0;
    (void)a; (void)b;
    sk_ret0();
    u = (uint64_t)*(uint64_t *)0;
    if ((grow & 1) != 0) {
        sk_ret0b();
        if (1) {
            sk_check_ovf();
            if (1) sk_break(1, 0x739d8);
            sk_ret0c();
            u = (uint64_t)*(uint64_t *)0;
        }
    }
    u = sk_vec_alloc_0x10(obj[1], u);
    if ((*(uint64_t *)0 & 1) == 0) {
        sk_ret0d();
        sk_ext_000751b4();
    } else {
        sk_ptr_plus();
        sk_move_0x18b(0,0,0);
        sk_release_and_zero();
    }
    sk_u128_t r; r.lo = u; r.hi = 0; return r;
}

/* FUN_000739d8 @ 0x739d8  (est. sk_reserve_u32c) */
static sk_u128_t sk_reserve_u32c(uint64_t a, uint64_t b, uint64_t grow)
{
    uint64_t u;
    uint64_t *obj = (uint64_t *)*(uint64_t *)0;
    (void)a; (void)b;
    sk_ret0();
    u = (uint64_t)*(uint64_t *)0;
    if ((grow & 1) != 0) {
        sk_ret0b();
        if (1) {
            sk_check_ovf();
            if (1) sk_break(1, 0x73a64);
            sk_ret0c();
            u = (uint64_t)*(uint64_t *)0;
        }
    }
    u = sk_vec_alloc_0x10(obj[1], u);
    if ((*(uint64_t *)0 & 1) == 0) {
        sk_ret0d();
        sk_ext_00075018();
    } else {
        sk_ptr_plus();
        sk_move_0x50b(0,0,0);
        sk_release_and_zero();
    }
    sk_u128_t r; r.lo = u; r.hi = 0; return r;
}

/* FUN_00073a64 @ 0x73a64  (est. sk_reserve_u32d) */
static sk_u128_t sk_reserve_u32d(uint64_t a, uint64_t b, uint64_t grow)
{
    uint64_t u;
    uint64_t *obj = (uint64_t *)*(uint64_t *)0;
    (void)a; (void)b;
    sk_ret0();
    u = (uint64_t)*(uint64_t *)0;
    if ((grow & 1) != 0) {
        sk_ret0b();
        if (1) {
            sk_check_ovf();
            if (1) sk_break(1, 0x73af0);
            sk_ret0c();
            u = (uint64_t)*(uint64_t *)0;
        }
    }
    u = sk_vec_alloc_0x10(obj[1], u);
    if ((*(uint64_t *)0 & 1) == 0) {
        sk_ret0d();
        sk_ext_00075018();
    } else {
        sk_ptr_plus();
        sk_move_0x50b(0,0,0);
        sk_release_and_zero();
    }
    sk_u128_t r; r.lo = u; r.hi = 0; return r;
}

/* FUN_00073af0 @ 0x73af0  (est. sk_reserve_u32e) */
static sk_u128_t sk_reserve_u32e(uint64_t a, uint64_t b, uint64_t grow)
{
    uint64_t u;
    uint64_t *obj = (uint64_t *)*(uint64_t *)0;
    (void)a; (void)b;
    sk_ret0();
    u = (uint64_t)*(uint64_t *)0;
    if ((grow & 1) != 0) {
        sk_ret0b();
        if (1) {
            sk_check_ovf();
            if (1) sk_break(1, 0x73b7c);
            sk_ret0c();
            u = (uint64_t)*(uint64_t *)0;
        }
    }
    u = sk_vec_alloc_0x10(obj[1], u);
    if ((*(uint64_t *)0 & 1) == 0) {
        sk_ret0d();
        sk_ext_00075018();
    } else {
        sk_ptr_plus();
        sk_move_0x50b(0,0,0);
        sk_release_and_zero();
    }
    sk_u128_t r; r.lo = u; r.hi = 0; return r;
}

#endif /* _SK_SLICE_16_H_ */

/* FUN_00070960 @ 0x70960  (est. sk_set_build)
 * Build a fresh set/dictionary: with flag x21 set, iterate the occupied-bitmap
 * of the source set at x20+0x10, decode each set element's {key, tag} and
 * stored value, scale the value by its count (unsigned-divide + overflow
 * traps at 0x70ca8/0x70cac/0x70cb0/0x70cb4/0x70ca0), then insert the {scaled
 * value, key} pair into the growing result set lVar11 via sk_set_insert
 * (0x258c60), filling its bitmap + value arrays.  With flag x23 set, iterate
 * the second source vector (x20+0x18), retain each element, recursively call
 * sk_set_build(&local, 1, 1), and fold the result through FUN_00076ac8.
 * Finalize: *x19 = result set, x19[1] = sk_hash2_copy (0x70cc8), x19[2] = 0.
 * Confidence: medium (bitmap bit-reversal set iteration, string-cache keys). */
static void sk_set_build(void)
{
    uint64_t u = sk_empty_vec();
    uint64_t dict = sk_class_vt(u, 0x65f260, 0x677830, 0x65f178);
    uint64_t *dst = (uint64_t *)*(uint64_t *)0;
    uint64_t res = 0;
    uint64_t wordidx;
    if ((*(uint64_t *)*(uint64_t *)0 & 1) != 0) {   /* flag x21 */
        uint64_t src, setbase, w;
        sk_ext_00002828((uint64_t)dst + 0x10, &src);
        setbase = *(uint64_t *)(dst + 0x10);
        src = *(uint64_t *)(setbase + 0x40);   /* first bitmap word */
        setbase = sk_ext_00077724(src);
        wordidx = 0;
        do {
            while (src != 0) {
                /* lowest set bit via bit-reverse + LZCOUNT */
                uint64_t t = (src & 0xaaaaaaaaaaaaaaaaULL) >> 1 | (src & 0x5555555555555555ULL) << 1;
                t = (t & 0xccccccccccccccccULL) >> 2 | (t & 0x3333333333333333ULL) << 2;
                t = (t & 0xf0f0f0f0f0f0f0f0ULL) >> 4 | (t & 0xf0f0f0f0f0f0f0fULL) << 4;
                t = (t & 0xff00ff00ff00ff00ULL) >> 8 | (t & 0xff00ff00ff00ffULL) << 8;
                t = (t & 0xffff0000ffff0000ULL) >> 16 | (t & 0xffff0000ffffULL) << 16;
                uint64_t pos = LZCOUNT(t >> 32 | t << 32) | wordidx << 6;
                uint64_t *ent = (uint64_t *)(*(uint64_t *)(setbase + 0x30) + pos * 0x10);
                uint64_t key = ent[0];
                uint64_t tag = ent[1] & 0xff;
                uint64_t val = *(uint64_t *)(*(uint64_t *)(setbase + 0x38) + pos * 8);
                uint64_t u17, u21, scale;
                bool b8;
                if (*(int64_t *)(dict + 0x10) == 0) {
                    u17 = 0;
                    if (tag == 0) { key = sk_int_udiv(key); if ((int64_t)key < 0) sk_break(1, 0x70cb8); key = sk_int_zero(); b8 = false; }
                    else { b8 = tag != 1; if (b8) key = 1; }
                } else {
                    sk_u128_t pr = sk_set_find(tag > 1 ? 1 : 0, 0, 0);
                    if ((pr.hi & 1) == 0) { u17 = 0; if (tag == 0) { key = sk_int_udiv(key); if ((int64_t)key < 0) sk_break(1, 0x70cb8); key = sk_int_zero(); b8 = false; } else { b8 = tag != 1; if (b8) key = 1; } }
                    else {
                        u17 = *(uint64_t *)(*(uint64_t *)(dict + 0x38) + pr.lo * 8);
                        if (tag == 0) { key = sk_int_udiv(key); if ((int64_t)key < 0) sk_break(1, 0x70cb8); key = sk_int_zero(); b8 = false; }
                        else { b8 = tag != 1; if (b8) key = 1; }
                    }
                }
                u21 = key;
                scale = val;
                if (((u21 * scale) >> 8) != 0) sk_break(1, 0x70ca8);
                u21 = u21 * scale;
                u17 = u17 + u21;
                if (CARRY8(u17, u21)) sk_break(1, 0x70cac);
                uint64_t r2 = sk_ext_003a261c(dict);
                uint64_t save = dict;
                sk_u128_t pr2 = sk_set_find(b8, 0, 0);
                u21 = pr2.lo;
                scale = ~pr2.hi & 1;
                int64_t newcount = *(int64_t *)(dict + 0x10) + scale;
                uint64_t newcount_eq0 = newcount == 0;
                if (SCARRY8(*(int64_t *)(dict + 0x10), scale)) sk_break(1, 0x70cb0);
                uint64_t k2 = sk_string_cache(0x64e5b8, DAT_004c03b0);
                uint64_t ins = sk_set_insert(r2, newcount, k2);
                if ((ins & 1) != 0) {
                    sk_set_find(b8, 0, 0);
                    sk_ext_00077604();
                    if (!newcount_eq0) sk_fatal_ret(0x65f260);
                }
                if ((pr2.hi & 1) == 0) {
                    uint64_t *base = (uint64_t *)(save + (u21 >> 6) * 8);
                    base[8] = base[8] | 1UL << (u21 & 0x3f);
                    *(bool *)(*(uint64_t *)(save + 0x30) + u21) = b8;
                    *(uint64_t *)(*(uint64_t *)(save + 0x38) + u21 * 8) = u17;
                    if (SCARRY8(*(int64_t *)(save + 0x10), 1)) sk_break(1, 0x70cb4);
                    *(int64_t *)(save + 0x10) = *(int64_t *)(save + 0x10) + 1;
                } else {
                    *(uint64_t *)(*(uint64_t *)(save + 0x38) + u21 * 8) = u17;
                }
                dict = save;
                src = src - 1 & src;
            }
            if (SCARRY8(wordidx, 1)) sk_break(1, 0x70ca0);
            wordidx = wordidx + 1;
            if ((int64_t)(((uint64_t)0 + 0x3f) >> 6) <= (int64_t)wordidx) goto build_done;
            src = *(uint64_t *)(*(uint64_t *)(dst + 0x10) + 0x40 + wordidx * 8);
        } while (1);
    }
build_done:
    if ((*(uint64_t *)*(uint64_t *)0 & 1) != 0) {   /* flag x23 */
        uint64_t v, n, i, obj;
        sk_ext_00002828((uint64_t)dst + 0x18, &v);
        n = *(uint64_t *)(v + 0x10);
        sk_swift_retain(v);
        for (i = 0; n != i; i = i + 1) {
            if (*(uint64_t *)(v + 0x10) <= i) sk_break(1, 0x70ca4);
            obj = *(uint64_t *)(v + i * 8 + 0x20);
            sk_swift_retain(obj);
            sk_set_build();
            sk_ext_00076ac8(0, 0, 0, 0, &dict);
            sk_swift_release(obj);
        }
        sk_swift_release(v);
    }
    *(uint64_t *)0 = dict;
    *(uint64_t *)((uint64_t)0 + 8) = (uint64_t)sk_hash2_copy;
    *(uint64_t *)((uint64_t)0 + 0x10) = 0;
}

/* FUN_00071050 @ 0x71050  (est. sk_emit_borrow_report)
 * Emit the full "borrow report" for a (name, value) accounting pair: build a
 * set of children (sk_set_build 1,0), fetch its child records, release the
 * intermediates, then build a format record from the global const pair
 * (_DAT_004baeb0/b8) and the string cache; store param_1/param_2 with a retain
 * of param_2, append the "borrow(" markers, and iterate two child sets
 * emitting each field via sk_emit_field (0x70098) — the second pass appends
 * the "borrow(...)" / "error(...)" markers (0x776f72726f622820,0xeb00000000296465
 * = "borrow(" ... ")").  Emits each record (0x2804) and finalizes.
 * Confidence: medium (string markers + retain/release chain). */
static void sk_emit_borrow_report(uint64_t a, uint64_t b)
{
    uint64_t set, u, k, rec, u3, u2;
    sk_u128_t pr;
    uint64_t local_b0, uStack_a8, local_a0, uStack_98, local_90, uStack_88, local_80;
    uint64_t v, u1;

    /* build children set (1,0) */
    sk_set_build();
    u = sk_children_get(0, 0, 0).lo;
    sk_swift_release(local_a0);
    sk_swift_release_masked(local_b0);
    local_b0 = u;
    /* const pair {0x202c, 0xe2...} */
    pr = sk_pair_pack(0x202c, 0xe200000000000000, 0, 0);
    sk_swift_release(u);
    k = sk_string_cache(DAT_0064c040, DAT_004bbf40);
    rec = sk_record_alloc(k, (uint64_t *)&local_b0);
    u3 = *(uint64_t *)0x4baeb8;   /* _DAT_004baeb8 */
    u2 = *(uint64_t *)0x4baeb0;   /* _DAT_004baeb0 */
    *(uint64_t *)(rec + 0x18) = u3;
    *(uint64_t *)(rec + 0x10) = u2;
    local_b0 = a;
    uStack_a8 = b;
    sk_swift_retain(b);
    sk_str_append(0x203a, 0xe200000000000000);
    sk_str_append(pr.lo, pr.hi);
    sk_swift_release_masked(pr.hi);
    *(uint64_t *)(rec + 0x38) = 0x6753a0;
    *(uint64_t *)(rec + 0x20) = local_b0;
    *(uint64_t *)(rec + 0x28) = uStack_a8;
    sk_obj_emit(rec);
    sk_record_ref(rec);
    sk_obj_done();
    sk_ext_00002834();
    sk_swift_barrier();

    /* first child set iteration (1,0) */
    sk_vec_pair_make((uint64_t *)&local_b0, 1, 0);
    sk_set_iter_init((long *)&local_b0, local_b0, uStack_a8, local_a0);
    u = local_b0;
    while (1) {
        pr = sk_set_next();
        u1 = local_b0;
        v = pr.hi;
        if ((~(uint32_t)pr.hi & 0xff) == 0) break;
        rec = sk_record_alloc(k, (uint64_t *)&local_b0);
        *(uint64_t *)(rec + 0x18) = u3;
        *(uint64_t *)(rec + 0x10) = u2;
        local_b0 = 0x202d20;
        uStack_a8 = 0xe300000000000000;
        sk_emit_field(v, pr.lo, 0);
        sk_str_append();
        sk_swift_release_masked(0);
        *(uint64_t *)(rec + 0x38) = 0x6753a0;
        *(uint64_t *)(rec + 0x20) = local_b0;
        *(uint64_t *)(rec + 0x28) = uStack_a8;
        sk_obj_emit(rec);
        sk_record_ref(rec);
        sk_obj_done();
        sk_ext_00002834();
        sk_swift_barrier();
        v = u1;
    }
    sk_swift_release(local_80);
    sk_swift_release(u1);

    /* second child set iteration (0,1) with borrow/error markers */
    sk_vec_pair_make((uint64_t *)&local_b0, 0, 1);
    sk_set_iter_init((long *)&local_b0, local_b0, uStack_a8, local_a0);
    u = local_b0;
    while (1) {
        pr = sk_set_next();
        u1 = local_b0;
        v = pr.hi;
        if ((~(uint32_t)pr.hi & 0xff) == 0) break;
        rec = sk_record_alloc(k, (uint64_t *)&local_b0);
        *(uint64_t *)(rec + 0x18) = u3;
        *(uint64_t *)(rec + 0x10) = u2;
        local_b0 = 0;
        uStack_a8 = 0xe000000000000000;
        sk_fault_builder(0x10);
        sk_swift_release_masked(uStack_a8);
        local_b0 = 0x202d20;
        uStack_a8 = 0xe300000000000000;
        sk_emit_field(v, pr.lo, 0);
        sk_str_append();
        sk_swift_release_masked(0);
        sk_str_append(0x776f72726f622820, 0xeb00000000296465); /* "borrow(...)" */
        *(uint64_t *)(rec + 0x38) = 0x6753a0;
        *(uint64_t *)(rec + 0x20) = local_b0;
        *(uint64_t *)(rec + 0x28) = uStack_a8;
        sk_obj_emit(rec);
        sk_record_ref(rec);
        sk_obj_done();
        sk_ext_00002834();
        sk_swift_barrier();
        v = u1;
    }
    sk_swift_release(local_80);
    sk_swift_release(u1);
}
