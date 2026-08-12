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
/* thunk_FUN_002acbb8 */ extern void sk_str_append(uint64_t tag, uint64_t val);
/* thunk_FUN_002298d4 */ extern void sk_lock_select(uint64_t n);
/* FUN_001a84f4 */ extern void sk_scope_enter(uint64_t *frame, uint64_t ctx);
/* FUN_001a8564 */ extern uint64_t sk_scope_exit(void);
/* FUN_00117d14 */ extern void sk_memmove(uint64_t dst, uint64_t src, uint64_t n);
/* FUN_001a1564 */ extern void sk_vec_push(uint64_t obj, uint64_t val);
/* FUN_001a0774 */ extern void sk_vec_reserve(uint64_t grow, uint64_t count, uint64_t unit);
/* FUN_0001a1c8 */ extern uint64_t sk_identity_hash(uint64_t obj);
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
/* FUN_00070de4 */ extern sk_u128_t sk_children_get(uint64_t a, uint64_t b, uint64_t c);
/* FUN_00070960 */ extern void sk_set_build(void);
/* FUN_000707a8 */ extern void sk_vec_pair_make(uint64_t *out, uint64_t a, uint64_t b);
/* FUN_0007198c */ extern void sk_iter_init(long *out, long set, long a, long b);
/* FUN_000718b8 */ extern sk_u128_t sk_iter_next(void);
/* FUN_00072464 */ extern void sk_set_probe_flag(uint64_t flag);

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
static sk_u128_t sk_set_find(long key, char tag, uint64_t idx);
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
static void sk_set_probe2(ulong flag);
static void sk_set_first_probe(uint64_t a, uint64_t b, uint64_t c);
static void sk_iter_probe(long *out, long set, long a, long b);
